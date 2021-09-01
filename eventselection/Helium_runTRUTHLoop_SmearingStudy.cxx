// Loop entries, make cuts, fill histograms.
// * Uses the New Systematics Framework and "Universe" objects.
// * loop universes, make cuts and fill histograms with the correct lateral
// shifts and weights for each universe.
// * TChain --> PlotUtils::ChainWrapper.
// * MnvHXD --> PlotUtils::HistWrapper.
// * Genie, flux, non-resonant pion, and some detector systematics calculated.
#include "Helium_runTRUTHLoop_SmearingStudy.h"

std::string OUTputRoot_pathway = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles";


//=====================================================
// Functions
//=====================================================
std::vector<ECuts> GetRECOCutsVector();
std::vector<ECutsTRUTH> GetTRUTHCutsVector();
std::vector<ECutsTRUTH> GetTRUTHCutsVector_Energy();
std::vector<MuonVar> GetMUONVaribles();
std::vector<SecondTrkVar> GetPlayListSecondTrkVector();
std::vector<CryoVertex> GetCryoVertexVaribles();
std::vector<ME_helium_Playlists> GetPlayListVector();
std::vector<Weights> GetWeightVector();
//std::vector<ME_helium_Playlists> GetTRUEPlayListVector();
std::vector<Particle_type>  GetParicle_type();


//double Mev_to_GeV=.001;

// Get container of systematics

const bool m_RunCodeWithSystematics = false;


const std::vector<PlotUtils::NamedCategory<Material_type>>
MaterialGroup_categories = {
PlotUtils::NamedCategory<Material_type>({kMaterial_OTHER}, "Other"),
PlotUtils::NamedCategory<Material_type>({kIron},           "Iron"),
PlotUtils::NamedCategory<Material_type>({kCarbon},         "Carbon"),
PlotUtils::NamedCategory<Material_type>({kLead},           "Lead"),
PlotUtils::NamedCategory<Material_type>({kAluminium},      "Aluminium"),
PlotUtils::NamedCategory<Material_type>({kHelium},         "Helium")

};
const std::vector<PlotUtils::NamedCategory<Interaction_type>>
InteractionGroup_categories = {
  PlotUtils::NamedCategory<Interaction_type>({kInteraction_OTHER},"Other"),
  PlotUtils::NamedCategory<Interaction_type>({kInteraction_NONE}, "None"),
  PlotUtils::NamedCategory<Interaction_type>({kDIS},              "DIS"),
  PlotUtils::NamedCategory<Interaction_type>({k2p2h},             "2p2h"),
  PlotUtils::NamedCategory<Interaction_type>({kRes_Coh_Pion},     "1Pion"),
  PlotUtils::NamedCategory<Interaction_type>({kElastic},          "Elastic")
};


const std::vector<PlotUtils::NamedCategory<Particle_type>>
ParticleGroup_categories = {
  PlotUtils::NamedCategory<Particle_type>({kParticle_N_A}, "N_A"),
  PlotUtils::NamedCategory<Particle_type>({kParticle_OTHER}, "Other"),
  PlotUtils::NamedCategory<Particle_type>({kElectron}, "Electron"),
  PlotUtils::NamedCategory<Particle_type>({kMuon},     "Muon"),
  PlotUtils::NamedCategory<Particle_type>({kGamma},    "Gamma"),
  PlotUtils::NamedCategory<Particle_type>({kNeutrino_muon}, "Neutrino_muon"),
  PlotUtils::NamedCategory<Particle_type>({kNeutrino_electron}, "Neutrino_electron"),
  PlotUtils::NamedCategory<Particle_type>({kAnti_Neutrino}, "Anti_Neutrino"),
  PlotUtils::NamedCategory<Particle_type>({kKaon},     "Kaon"),
  PlotUtils::NamedCategory<Particle_type>({kPion_0},     "Pi0"),
  PlotUtils::NamedCategory<Particle_type>({kPion_neg},     "Pi^{-}"),
  PlotUtils::NamedCategory<Particle_type>({kPion_pos},     "Pi^{+}"),
  PlotUtils::NamedCategory<Particle_type>({kProton},   "Proton"),
  PlotUtils::NamedCategory<Particle_type>({kNeutron},   "Neutron"),
  PlotUtils::NamedCategory<Particle_type>({kFourHelium},   "{}^{4}He"),
  PlotUtils::NamedCategory<Particle_type>({kLamdba},   "Lamdba"),
  PlotUtils::NamedCategory<Particle_type>({kSigma_plus},   "Sigma^{+}")

};





const std::vector<PlotUtils::NamedCategory<Particle_type>>
ParticleGroup_leadingvsnonleading_categories = {
  PlotUtils::NamedCategory<Particle_type>({kParticle_OTHER}, "Other"),
  PlotUtils::NamedCategory<Particle_type>({kPion_0},         "Pi0"),
  PlotUtils::NamedCategory<Particle_type>({kPion_neg},       "Pi^{-}"),
  PlotUtils::NamedCategory<Particle_type>({kPion_pos},       "Pi^{+}"),
  PlotUtils::NamedCategory<Particle_type>({kProton},         "Proton"),
  PlotUtils::NamedCategory<Particle_type>({kNeutron},   "Neutron")

};



const int n_flux_universes = 25;
std::map< std::string, std::vector<HeliumCVUniverse*> >
  GetErrorBands(PlotUtils::ChainWrapper* chain) {
    typedef std::map< std::string, std::vector<HeliumCVUniverse*> > SystMap;
    //const int n_flux_universes = 50;
    SystMap error_bands;

    // CV
    error_bands[std::string("CV")].push_back( new HeliumCVUniverse(chain) );

    //Detector systematics, lateral shifts

    if(m_RunCodeWithSystematics==true)
    {
      //GENIE
      SystMap genie_systematics = PlotUtils::GetGenieSystematicsMap<HeliumCVUniverse>(chain);
      error_bands.insert(genie_systematics.begin(), genie_systematics.end());

      SystMap a2p2h_systematics = PlotUtils::Get2p2hSystematicsMap<HeliumCVUniverse>(chain);
      error_bands.insert(a2p2h_systematics.begin(), a2p2h_systematics.end());

      SystMap RPA_systematics = PlotUtils::GetRPASystematicsMap<HeliumCVUniverse>(chain);
      error_bands.insert(RPA_systematics.begin(), RPA_systematics.end());
    }

  return error_bands;
}
//======================================================================
// Main
void runEventLoop() {
  // Make a chain of events
  loadLibs();
double POT[4];
const std::vector<ECutsTRUTH> kTRUTHCutsVector = GetTRUTHCutsVector();
const std::vector<ECutsTRUTH> kTRUTHCutsVector_Energy = GetTRUTHCutsVector_Energy();

const std::vector<ME_helium_Playlists> kPlayListVector = GetPlayListVector();
//const std::vector< ME_helium_Playlists> kTRUEPlayListVector = GetTRUEPlayListVector();
const std::vector<Weights> kWeightVector = GetWeightVector();
const std::vector<MuonVar> kMuonVaribles_vector = GetMUONVaribles();
const std::vector<SecondTrkVar> ksecTrkVaribles_vector = GetPlayListSecondTrkVector();

const std::vector<CryoVertex> kCryoVertexVaribles_vector = GetCryoVertexVaribles();

const std::vector<Particle_type> kSecondary_particle_vector = GetParicle_type();

std::vector<Vertex_XYZ> UpstreamBugle_vector;
std::vector<Vertex_XYZ> UpstreamBugle_vector_He;
std::vector<Vertex_XYZ> UpstreamBugle_vector_Al;

std::vector<Vertex_XYZ> DownstreamBugle_vector;
std::vector<Vertex_XYZ> DownstreamBugle_vector_He;
std::vector<Vertex_XYZ> DownstreamBugle_vector_Al;



std::vector<Vertex_XYZ> CenterBugle_vector;
std::vector<Vertex_XYZ> CenterBugle_vector_He;
std::vector<Vertex_XYZ> CenterBugle_vector_Al;


std::ofstream output("LogFile_TRUTH.txt",std::ofstream::app);

//======================================================================
////////////////////ADDING TO CHAIN wrapper ///////////////////////////
//======================================================================
bool is_mc= true;


for(auto PlayList_iterator:kPlayListVector ){

  MinervaUniverse::SetNuEConstraint(true);
  MinervaUniverse::SetAnalysisNuPDG(14);
  MinervaUniverse::SetNFluxUniverses(n_flux_universes);


  std::string playlist = GetPlaylist(PlayList_iterator);
  MinervaUniverse::SetPlaylist(playlist);


 std::string seestring = MinervaUniverse::GetPlaylist();
  //MinervaUniverse::Set_Multiple_resetPlaylist(true);
  HeliumPlayListInfo Playlist_Info(playlist);
    std::cout<<"Working with Playlist =  "<<   seestring <<std::endl;

  MinervaUniverse::SetNonResPiReweight(true);
  auto Playlist_txtFILEPath = GetPlaylist_txtFILE_path(PlayList_iterator, is_mc );
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"Adding to Chain Wrapper For Loop   "<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  PlotUtils::ChainWrapper* chw_MC = makeChainWrapperPtr(Playlist_txtFILEPath.c_str(), "Truth");
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"Adding to Chain Wrapper For POT counter   "<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  //PlotUtils::ChainWrapper* mcchainPOT = makeChainWrapperPtr(Playlist_txtFILEPath.c_str(), "Meta");

  //======================================================================
  ///////////////////Making/adding to error bands  ///////////////////////////
  //======================================================================
//std::map< std::string, std::vector<HeliumCVUniverse*> > error_bands = GetErrorBands(chw_FullMC);
std::map< std::string, std::vector<HeliumCVUniverse*> > error_bands= GetErrorBands(chw_MC);
//double mcPOT = GetPOT(chw_MC, "MC");
std::cout<<"Number of Universes set is = "<< 	MinervaUniverse::GetNFluxUniverses()<<std::endl;
//std::string NumU = MinervaUniverse::GetNFluxUniverses()<<std::endl;
//Debug("Number of Universes set is = " );
//Debug(NumU);
//MinervaUniverse::SetNFluxUniverses(25);
POTCounter pot_counter;

//const std::string RootName = GetPlaylist_ROOT_path("1G_pdgcorrection_2",  is_mc );
const std::string RootName = GetPlaylist_ROOT_path(PlayList_iterator,true);
//const std::string RootName = GetPlaylist_ROOT_path("1D_EnergyFix",  is_mc );
std::cout<<"The Playlist that is set is = "<< seestring <<std::endl;
std::cout<<"The Playlist Root = "<< RootName<<std::endl;
 ///pnfs/minerva/persistent/users/cnguyen/ME_G1_Merg/*.root



  auto mcscale = 1.0; //Data_POT_full/ MC_POT_full;
  time_t now = time(0);
  tm *ltm = localtime(&now);
   int m_datemonth = 1 + ltm->tm_mon;
   int m_datehour= ltm->tm_hour;
   int m_datemin=ltm->tm_min;
   int m_dateday=ltm->tm_mday;

  output<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  output<<"~~~~~~~~Helium Anaylsis Log File ~~~~~~~~~~~~~~~" << endl;
  output<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  output<<"~~~~~~~~~~~~Created By ~~~~~~~~~~~~~~" << endl;
  output<<"~~~~~~~~~~~Christian Nguyen ~~~~~~~~~~~" << endl;
  output<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  output<<"DateRan(min-hour-month-day-year): (" <<m_datemin<<"-"<<m_datehour<< "-"<<  m_datemonth<< "- "<<m_dateday << "-2020)"<<endl;
  output<<"EnergyType: LE" << endl;
  output<<"Playlist: " <<  GetPlaylist_Name(PlayList_iterator) << endl;
  output<<"Data TYPE : "<<  String_Reco_orTruth(false) << endl;
  output<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  int count=1;


  output<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  output<<"~~~~~Truth CUTS Applied for Efficiency Study ~~~~" << endl;
  output<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

  count=1;
  for(auto true_cut_name:kTRUTHCutsVector ){
  output<< count<<" TRUTHCUT name: "<<GetCutNameTRUTH(true_cut_name) <<endl;
  count++;
  }



  output<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  output<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  output<<"~~~~~WEIGHTS~~~~~~~~~~~~~" << endl;
  output<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

  output<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  output<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

  output<<"Weights Applied on Event by event"<< endl;
  for(auto Weight_name:kWeightVector )
  {
    output<<"  Weights type: " <<GetWeight_name(Weight_name) <<endl;
  }

  output<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  output<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

  //LogFile LOGFILE(PlayList_iterator ,kTRUTHCutsVector , kWeightVector, kTRUTHCutsVector, 1,true,_logfile);
  //LOGFILE<<"Number of Universes set is = "<< 	MinervaUniverse::GetNFluxUniverses()<<"/n";


//Bins for varibles //
//Muons ///////////////////
std::vector<double> Ebin_vector = GetBinMuonVector(kE);
std::vector<double> Pzbin_vector= GetBinMuonVector(kP_Z);
std::vector<double> PTbin_vector= GetBinMuonVector(kP_T);
std::vector<double> MuonThetabin_vector= GetBinMuonVector(kAngleWRTB);
std::vector<double> Muon_curvatureSig_vector= GetBinMuonVector(kcurvatureSig);
std::vector<double> MuonCharge_vector= GetBinMuonVector(kCharge);
std::vector<double> MuonMatchtoMinos_vector= GetBinMuonVector(kMuonMatchtoMinos);
std::vector<double> MuonMatchtoVeto_vector= GetBinMuonVector(kMuonMatchtoVeto);

std::vector<double> Minos_R_vector= GetBinMuonVector(kminos_R);
std::vector<double> AnglePhi_vector = GetBinMuonVector(kAnglePhi);

std::vector<double> Minos_Start_X_vector= GetBinMuonVector(kminosStart_X);
std::vector<double> Minos_Start_Y_vector= GetBinMuonVector(kminosStart_Y);
std::vector<double> Minos_Start_Z_vector= GetBinMuonVector(kminosStart_Z);

std::vector<double> Minos_End_X_vector= GetBinMuonVector(kminosEnd_X);
std::vector<double> Minos_End_Y_vector= GetBinMuonVector(kminosEnd_Y);
std::vector<double> Minos_End_Z_vector= GetBinMuonVector(kminosEnd_Z);

std::vector<double> Muon_StartNode_X_vector= GetBinMuonVector(kmuonFirstNodeX);
std::vector<double> Muon_StartNode_Y_vector= GetBinMuonVector(kmuonFirstNodeY);
std::vector<double> Muon_StartNode_Z_vector= GetBinMuonVector(kmuonFirstNodeZ);

std::vector<double> Muon_LastNode_X_vector= GetBinMuonVector(kmuonLastNodeX);
std::vector<double> Muon_LastNode_Y_vector= GetBinMuonVector(kmuonLastNodeY);
std::vector<double> Muon_LastNode_Z_vector= GetBinMuonVector(kmuonLastNodeZ);
std::vector<double> TrackSize_vector= GetBinMuonVector(ktracksize);

////////////////////////
std::vector<double> Vertex_Xbins= GetBinvertexVector(kX);
std::vector<double> Vertex_Ybins= GetBinvertexVector(kY);
std::vector<double> Vertex_Zbins= GetBinvertexVector(kZ);
std::vector<double> Vertex_Rbins= GetBinvertexVector(kR);

std::vector<double> Vertex_DOCAbins= GetBinMuonVector(kDOCA_muon);
std::vector<double> Vertex_secondTrkEbins= GetSecondTrkVarVector(ksecE_Proton); //GetSecondTrkVarVector(ksecE);
std::vector<double> Vertex_secondTrkEbin_Proton_vector= GetSecondTrkVarVector(ksecE_Proton);
std::sort(Vertex_secondTrkEbin_Proton_vector.begin(),Vertex_secondTrkEbin_Proton_vector.end());
std::vector<double> Vertex_secondTrkTheta_bins= GetSecondTrkVarVector(kFullAngle);
std::vector<double> Vertex_secondTrkDOCA_bins= GetSecondTrkVarVector(kDOCA);
std::vector<double> Vertex_secondTrkPathway_bins= GetSecondTrkVarVector(kPathway);

////////////////
//muon Varibles///
////////////////

//PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE("h_MuonE", "Muon_{E} NEW Method", Ebin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE_TRUE("h_MuonE_TRUE", "Muon_{E} NEW Method", Ebin_vector , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonE_TRUE_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonE_TRUE_Material", Ebin_vector ,"MuonE_TRUE_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonE_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_MuonE_TRUE_Interaction", Ebin_vector ,"MuonE_TRUE_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_MuonE_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_MuonE_TRUE_Particle", Ebin_vector ,"MuonE_TRUE_Particle; [GeV];Events");


PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPZ_TRUE("h_MuonPZ_TRUE", "Muon_{PZ} NEW Method",  Pzbin_vector , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonPZ_TRUE_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonPZ_TRUE_Material", Pzbin_vector ,"h_MuonPZ_TRUE_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonPZ_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_MuonPZ_TRUE_Interaction", Pzbin_vector ,"h_MuonPZ_TRUE_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_MuonPZ_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_MuonPZ_TRUE_Particle", Pzbin_vector ,"h_MuonPZ_TRUE_Particle; [GeV];Events");


PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPT_TRUE("h_MuonPT_TRUE", "Muon_{PT} NEW Method",  PTbin_vector , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonPT_TRUE_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonPT_TRUE_Material", PTbin_vector ,"h_MuonPT_TRUE_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonPT_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_MuonPT_TRUE_Interaction", PTbin_vector ,"h_MuonPT_TRUE_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_MuonPT_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_MuonPT_TRUE_Particle", PTbin_vector ,"h_MuonPT_TRUE_Particle; [GeV];Events");



PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonTheta_TRUE("h_MuonTheta_TRUE", "MuonTheta [Deg]",  MuonThetabin_vector , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonTheta_TRUE_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonTheta_TRUE_Material", MuonThetabin_vector ,"h_MuonTheta_TRUE_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonTheta_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_MuonTheta_TRUE_Interaction", MuonThetabin_vector ,"h_MuonTheta_TRUE_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_MuonTheta_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_MuonTheta_TRUE_Particle", MuonThetabin_vector ,"h_MuonTheta_TRUE_Particle; [GeV];Events");

PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPhi_TRUE("h_MuonPhi_TRUE", "MuonTheta [Deg]",  MuonThetabin_vector , error_bands);//
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonPhi_TRUE_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonPhi_TRUE_Material", AnglePhi_vector ,"h_MuonPhi_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonPhi_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_MuonPhi_TRUE_Interaction", AnglePhi_vector ,"h_MuonPhi_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_MuonPhi_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_MuonPhi_TRUE_Particle", AnglePhi_vector ,"h_MuonPhi_Particle; [GeV];Events");




PlotUtils::HistWrapper<HeliumCVUniverse> h_Tracksize_TRUE("h_Tracksize_TRUE", "Track size [N]",  TrackSize_vector , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Tracksize_TRUE_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Tracksize_TRUE_Material", TrackSize_vector ,"h_Tracksize_TRUE_Material; [Tracknumber];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_Tracksize_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_Tracksize_TRUE_Interaction", TrackSize_vector ,"h_Tracksize_TRUE_Interaction; [Tracknumber];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_Tracksize_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_Tracksize_TRUE_Particle", TrackSize_vector ,"h_Tracksize_TRUE_Particle; [Tracknumber];Events");

///////////////////////////////////////
//
///////////////////////////////////////
MnvH2D *h_2d_PZ_PT_TRUE            =    new MnvH2D("h_2d_PZ_PT_TRUE", "h_2d_PZ_PT_TRUE",Pzbin_vector.size()-1, Pzbin_vector.data() ,PTbin_vector.size()-1, PTbin_vector.data()  );

MnvH2D *h_2d_E_PZ_TRUE             =    new MnvH2D("h_2d_E_PZ_TRUE", "h_2d_E_PZ_TRUE", Ebin_vector.size()-1, Ebin_vector.data(),Pzbin_vector.size()-1, Pzbin_vector.data()  );

MnvH2D *h_2d_Theta_PZ_TRUE         =    new MnvH2D("h_2d_Theta_PZ_TRUE", "h_2d_Theta_PZ_TRUE", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),Pzbin_vector.size()-1, Pzbin_vector.data()  );

MnvH2D *h_2d_E_PT_TRUE             =    new MnvH2D("h_2d_E_PT_TRUE", "h_2d_E_PT_TRUE", Ebin_vector.size()-1, Ebin_vector.data(),PTbin_vector.size()-1, PTbin_vector.data()  );
MnvH2D *h_2d_Theta_PT_TRUE         =    new MnvH2D("h_2d_Theta_PT_TRUE", "h_2d_Theta_PT_TRUE", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),PTbin_vector.size()-1, PTbin_vector.data()  );
//MnvH2D *h_2d_Theta_PT_TRUE_RECO    =    new MnvH2D("h_2d_Theta_PT_TRUE_RECO", "h_2d_Theta_PT_TRUE_RECO", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),PTbin_vector.size()-1, PTbin_vector.data()  );

///////////////////////////////////////
//
///////////////////////////////////////
MnvH2D *h_2d_Theta_2ndTrkE_TRUE         =    new MnvH2D("h_2d_Theta_2ndTrkE_TRUE", "h_2d_Theta_2ndTrkE_TRUE", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );
MnvH2D *h_2d_muonE_2ndTrkE_TRUE         =    new MnvH2D("h_2d_muonE_2ndTrkE_TRUE", "h_2d_muonE_2ndTrkE_TRUE", Ebin_vector.size()-1, Ebin_vector.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );
MnvH2D *h_2d_muonPT_2ndTrkE_TRUE         =    new MnvH2D("h_2d_muonPT_2ndTrkE_TRUE", "h_2d_muonPT_2ndTrkE_TRUE",  PTbin_vector.size()-1,  PTbin_vector.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );
MnvH2D *h_2d_muonPZ_2ndTrkE_TRUE         =    new MnvH2D("h_2d_muonPZ_2ndTrkE_TRUE", "h_2d_muonPZ_2ndTrkE_TRUE",  Pzbin_vector.size()-1,  Pzbin_vector.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );
///////////////////////////////////////
//
///////////////////////////////////////
MnvH2D *h_2d_Theta_2ndTrKangle_TRUE         =    new MnvH2D("h_2d_Theta_2ndTrKangle_TRUE", "h_2d_Theta_2ndTrKangle_TRUE", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),Vertex_secondTrkTheta_bins.size()-1, Vertex_secondTrkTheta_bins.data()  );
MnvH2D *h_2d_muonE_2ndTrkangle_TRUE         =    new MnvH2D("h_2d_muonE_2ndTrkangle_TRUE", "h_2d_muonE_2ndTrkangle_TRUE", Ebin_vector.size()-1, Ebin_vector.data(),Vertex_secondTrkTheta_bins.size()-1, Vertex_secondTrkTheta_bins.data()  );
MnvH2D *h_2d_muonPT_2ndTrkangle_TRUE         =    new MnvH2D("h_2d_muonPT_2ndTrkangle_TRUE", "h_2d_muonPT_2ndTrkangle_TRUE",  PTbin_vector.size()-1,  PTbin_vector.data(),Vertex_secondTrkTheta_bins.size()-1, Vertex_secondTrkTheta_bins.data()  );
MnvH2D *h_2d_muonPZ_2ndTrkangle_TRUE         =    new MnvH2D("h_2d_muonPZ_2ndTrkangle_TRUE", "h_2d_muonPZ_2ndTrkangle_TRUE",  Pzbin_vector.size()-1,  Pzbin_vector.data(),Vertex_secondTrkTheta_bins.size()-1, Vertex_secondTrkTheta_bins.data()  );
///////////////////////////////////////
//
///////////////////////////////////////


//MnvH2D *h_2d_Theta_PT_TRUE         =    new MnvH2D("h_2d_Theta_PT_TRUE", "h_2d_Theta_PT_TRUE", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),PTbin_vector.size()-1, PTbin_vector.data()  );
//MnvH2D *h_2d_Theta_PT_TRUE_RECO    =    new MnvH2D("h_2d_Theta_PT_TRUE_RECO", "h_2d_Theta_PT_TRUE_RECO", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),PTbin_vector.size()-1, PTbin_vector.data()  );
///////////////////////////////////////
//
///////////////////////////////////////

MnvH2D *h_2d_2ndtrkangle_2ndTrkE_TRUE              =    new MnvH2D("h_2d_2ndtrkangle_2ndTrkE_TRUE", "h_2d_2ndtrkangle_2ndTrkE_TRUE", Vertex_secondTrkTheta_bins.size()-1, Vertex_secondTrkTheta_bins.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );
MnvH2D *h_2d_2ndtrkangle_2ndTrkE_Proton_TRUE       =  new MnvH2D("h_2d_2ndtrkangle_2ndTrkE_Proton_TRUE", "h_2d_2ndtrkangle_2ndTrkE_Proton_TRUE", Vertex_secondTrkTheta_bins.size()-1, Vertex_secondTrkTheta_bins.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );
MnvH2D *h_2d_2ndtrkangle_2ndTrkE_Pion_TRUE         =    new MnvH2D("h_2d_2ndtrkangle_2ndTrkE_Pion_TRUE", "h_2d_2ndtrkangle_2ndTrkE_Pion_TRUE", Vertex_secondTrkTheta_bins.size()-1, Vertex_secondTrkTheta_bins.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );
MnvH2D *h_2d_2ndtrkangle_2ndTrkE_Pion0_TRUE        =    new MnvH2D("h_2d_2ndtrkangle_2ndTrkE_Pion0_TRUE", "h_2d_2ndtrkangle_2ndTrkE_Pion0_TRUE", Vertex_secondTrkTheta_bins.size()-1, Vertex_secondTrkTheta_bins.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );
MnvH2D *h_2d_2ndtrkangle_2ndTrkE_Pion_neg_pos_TRUE =    new MnvH2D("h_2d_2ndtrkangle_2ndTrkE_Pion_neg_pos_TRUE", "h_2d_2ndtrkangle_2ndTrkE_Pion_neg_pos_TRUE", Vertex_secondTrkTheta_bins.size()-1, Vertex_secondTrkTheta_bins.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );
MnvH2D *h_2d_2ndtrkangle_2ndTrkE_dimuon_TRUE       =    new MnvH2D("h_2d_2ndtrkangle_2ndTrkE_dimuon_TRUE", "h_2d_2ndtrkangle_2ndTrkE_dimuon_TRUE", Vertex_secondTrkTheta_bins.size()-1, Vertex_secondTrkTheta_bins.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );
////////////////
//Vertex Hist///
////////////////
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_TRUE("h_CryoVertex_X_TRUE", "h_CryoVertex_X",  Vertex_Xbins , error_bands);
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_X_TRUE_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_X_TRUE_Material", Vertex_Xbins ,"h_CryoVertex_X_TRUE_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_CryoVertex_X_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_CryoVertex_X_TRUE_Interaction", Vertex_Xbins ,"h_CryoVertex_X_TRUE_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_CryoVertex_X_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_CryoVertex_X_TRUE_Particle", Vertex_Xbins ,"h_CryoVertex_X_TRUE_Particle; [mm];Events");

PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_TRUE("h_CryoVertex_Y_TRUE", "Vertex_Y",  Vertex_Ybins , error_bands);
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Y_TRUE_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Y_TRUE_Material", Vertex_Ybins ,"h_CryoVertex_Y_TRUE_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_CryoVertex_Y_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_CryoVertex_Y_TRUE_Interaction", Vertex_Ybins ,"h_CryoVertex_Y_TRUE_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_CryoVertex_Y_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_CryoVertex_Y_TRUE_Particle", Vertex_Ybins ,"h_CryoVertex_Y_TRUE_Particle; [mm];Events");


PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_TRUE("h_CryoVertex_Z_TRUE", "Vertex_Z",  Vertex_Zbins , error_bands);//
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Z_TRUE_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Z_TRUE_Material", Vertex_Zbins ,"h_CryoVertex_Z_TRUE_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_CryoVertex_Z_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_CryoVertex_Z_TRUE_Interaction", Vertex_Zbins ,"h_CryoVertex_Z_TRUE_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_CryoVertex_Z_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_CryoVertex_Z_TRUE_Particle", Vertex_Zbins ,"h_CryoVertex_Z_TRUE_Particle; [mm];Events");


PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_TRUE("h_CryoVertex_R_TRUE", "h_CryoVertex_R",  Vertex_Rbins , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_R_TRUE_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_R_TRUE_Material", Vertex_Rbins ,"h_CryoVertex_R_TRUE_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_CryoVertex_R_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_CryoVertex_R_TRUE_Interaction", Vertex_Rbins ,"h_CryoVertex_R_TRUE_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_CryoVertex_R_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_CryoVertex_R_TRUE_Particle", Vertex_Rbins ,"h_CryoVertex_R_TRUE_Particle; [mm];Events");




PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Openangle_TRUE("h_secTrk_Openangle_TRUE", "h_secTrk_TRUE_Openangle ",  Vertex_secondTrkTheta_bins , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_Openangle_TRUE_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_Openangle_TRUE_Material", Vertex_secondTrkTheta_bins ,"h_secTrk_Openangle_TRUE_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_secTrk_Openangle_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_secTrk_Openangle_TRUE_Interaction", Vertex_secondTrkTheta_bins ,"h_secTrk_Openangle_TRUE_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_Openangle_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_Openangle_TRUE_Particle", Vertex_secondTrkTheta_bins ,"h_secTrk_Openangle_TRUE_Particle; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_Openangle_TRUE_RECO_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_Openangle_TRUE_RECO_Material", Vertex_secondTrkTheta_bins ,"h_secTrk_Openangle_TRUE_Material; [mm];Events");



//PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Pathlength("h_secTrk_Pathlength", "h_secTrk Pathlength ",  Vertex_secondTrkPathway_bins , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Pathlength_TRUE("h_secTrk_Pathlength_TRUE", "h_secTrk Pathlength ",  Vertex_secondTrkPathway_bins , error_bands);
//PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Pathlength_TRUE_RECO("h_secTrk_Pathlength_TRUE_RECO", "h_secTrk Pathlength ",  Vertex_secondTrkPathway_bins , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_Pathlength_TRUE_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_Pathlength_TRUE_Material", Vertex_secondTrkPathway_bins ,"h_secTrk_Pathlength_TRUE_Material; [cm^2/g];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_secTrk_Pathlength_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_secTrk_Pathlength_TRUE_Interaction", Vertex_secondTrkPathway_bins ,"h_secTrk_Pathlength_TRUE_Interaction; [cm^2/g];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_Pathlength_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_Pathlength_TRUE_Particle", Vertex_secondTrkPathway_bins ,"h_secTrk_Pathlength_TRUE_Particle; [cm^2/g];Events");

PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Theta_TRUE("h_secTrk_Theta_TRUE", "h_secTrk_Theta NEW Method",  Vertex_secondTrkTheta_bins , error_bands);
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_Theta_TRUE_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_Theta_TRUE_Material", Vertex_secondTrkTheta_bins ,"h_secTrk_Theta_TRUE_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_secTrk_Theta_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_secTrk_Theta_TRUE_Interaction", Vertex_secondTrkTheta_bins ,"h_secTrk_Theta_TRUE_Interaction; [[GeV;Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_Theta_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_Theta_TRUE_Particle", Vertex_secondTrkTheta_bins ,"h_secTrk_Theta_TRUE_Particle; [GeV];Events");


PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Energy_TRUE("h_secTrk_Energy_TRUE", "h_secTrk_Energy NEW Method",  Vertex_secondTrkEbins, error_bands);
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_Energy_TRUE_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_Energy_TRUE_Material", Vertex_secondTrkEbins ,"h_secTrk_Energy_TRUE_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_secTrk_Energy_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_secTrk_Energy_TRUE_Interaction", Vertex_secondTrkEbins ,"h_secTrk_Energy_TRUE_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_Energy_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_Energy_TRUE_Particle", Vertex_secondTrkEbins ,"h_secTrk_Energy_TRUE_Particle; [GeV];Events");

/////////////////


PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_ALLangles_TRUE("h_secTrk_ALLangles_TRUE", "h_secTrk_Theta PION0(TRUE)",  Vertex_secondTrkTheta_bins , error_bands);


//PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_DOCA("h_secTrk_DOCA", "h_secTrk DOCA NEW Method",  Vertex_secondTrkDOCA_bins , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_DOCA_TRUE("h_secTrk_DOCA_TRUE", "h_secTrk DOCA NEW Method",  Vertex_secondTrkDOCA_bins , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_DOCA_TRUE_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_DOCA_TRUE_Material", Vertex_secondTrkDOCA_bins ,"h_secTrk_DOCA_TRUE_RECO_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_secTrk_DOCA_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_secTrk_DOCA_TRUE_Interaction", Vertex_secondTrkDOCA_bins ,"h_secTrk_DOCA_TRUE_RECO_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_DOCA_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_DOCA_TRUE_Particle", Vertex_secondTrkDOCA_bins ,"h_secTrk_DOCA_TRUE_RECO_Particle; [mm];Events");

std::vector<double> Vertex_Rbins_vectorMOREbins_vec = {0,50,100,150,200,250,300,350,400,450,500,550,600,650,700,750,800,850,900,950,1000 };
MnvH1D *h_Truth_SmearingCryoVertex_R      =    new MnvH1D("h_Truth_SmearingCryoVertex_R", "h_Truth_SmearingCryoVertex_R", Vertex_Rbins_vectorMOREbins_vec.size()-1, Vertex_Rbins_vectorMOREbins_vec.data());

std::vector<double> Bins_distance_to_Bulges ={-400,-375,-350,-325,-300,-275,-250,-225,-200,-175,-150,-125,-100,-75,-50,-25, 0,25,50,75,100,125,150,175,200,225,250,275,300,325,350,375,400};

MnvH1D *h_Truth_Vertex_distance_upstream      =    new MnvH1D("h_Truth_Vertex_distance_upstream", "h_Truth_Vertex_distance_upstream", Bins_distance_to_Bulges.size()-1, Bins_distance_to_Bulges.data());

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Truth_Vertex_distance_upstream_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Truth_Vertex_distance_upstream_Material", Bins_distance_to_Bulges ,"h_Truth_Vertex_distance_upstream_Material; [mm];Events");

//PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Truth_CryoVertex_Z_upstream_Material =
//PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Truth_CryoVertex_Z_upstream_Material", Vertex_Zbins , "h_Truth_CryoVertex_Z_upstream_Material; [mm];Events");

MnvH1D *h_Truth_CryoVertex_Z_upstream         =    new MnvH1D("h_Truth_CryoVertex_Z_upstream", "h_Truth_CryoVertex_Z_upstream", Vertex_Zbins.size()-1,Vertex_Zbins.data());

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Truth_CryoVertex_Z_upstream_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Truth_CryoVertex_Z_upstream_Material", Vertex_Zbins ,"h_Truth_CryoVertex_Z_upstream_Material; [mm];Events");

MnvH1D *h_Truth_Vertex_distance_downstream    =    new MnvH1D("h_Truth_Vertex_distance_downstream", "h_Truth_Vertex_distance_downstream", Bins_distance_to_Bulges.size()-1, Bins_distance_to_Bulges.data());

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Truth_Vertex_distance_downstream_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Truth_Vertex_distance_downstream_Material", Bins_distance_to_Bulges ,"h_Truth_Vertex_distance_downstream_Material; [mm];Events");



PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Truth_CryoVertex_Z_downstream_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Truth_CryoVertex_Z_downstream_Material", Vertex_Zbins ,"h_Truth_CryoVertex_Z_downstream_Material; [mm];Events");

//MnvH1D *h_Truth_Vertex_distance_other       =    new MnvH1D("h_Truth_Vertex_distance_other", "h_Truth_Vertex_distance_other", Bins_distance_to_Bulges.size()-1, Bins_distance_to_Bulges.data());
MnvH1D *h_Truth_CryoVertex_Z_downstream       =    new MnvH1D("h_Truth_CryoVertex_Z_downstream", "h_Truth_CryoVertex_Z_downstream", Vertex_Zbins.size()-1, Vertex_Zbins.data());

//PlotUtils::HistFolio<PlotUtils::MnvH1D,Material_type> h_Truth_CryoVertex_Z_downstream_Material =
//PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Truth_CryoVertex_Z_downstream_Material", Vertex_Zbins ,"h_Truth_CryoVertex_Z_downstream_Material; [mm];Events");

MnvH1D *h_Truth_CryoVertex_R_Center_Smearing      =    new MnvH1D("h_Truth_CryoVertex_R_Center_Smearing", "h_Truth_CryoVertex_R_Center_Smearing", Vertex_Rbins_vectorMOREbins_vec.size()-1, Vertex_Rbins_vectorMOREbins_vec.data());

PlotUtils::HistFolio<PlotUtils::MnvH1D,Material_type> h_Truth_CryoVertex_Z_Center_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Truth_CryoVertex_Z_Center_Material", Vertex_Zbins ,"h_Truth_CryoVertex_Z_Center_Material; [mm];Events");


// testing the neutrino Electron type


///////////
///Vetowall
///////////
/////////////////////////////////////////

  //=========================================
  // Entry Loop For MC
  //=========================================

  //std::vector<ECuts> kTRUTHCutsVector;


  bool is_counter = true;

  //EventCount_Truth EventCounter_EFF;
  //EventCount_RECO EventCounter_EFF_TRUTH;
  EventCount_Truth EventCounter_TRUTH_total;

  EventCount_Truth EventCounter_weight_0;
  EventCount_Truth EventCounter_weight_1;
  EventCount_Truth EventCounter_weight_2;
  EventCount_Truth EventCounter_weight_3;
  EventCount_Truth EventCounter_weight_4;

  for(auto cat : kTRUTHCutsVector_Energy){EventCounter_TRUTH_total[cat]=0;}
  for(auto cat : kTRUTHCutsVector){
    EventCounter_weight_0[cat]=0;
    EventCounter_weight_1[cat]=0;
    EventCounter_weight_2[cat]=0;
    EventCounter_weight_3[cat]=0;
    EventCounter_weight_4[cat]=0;
    }




  int counter_test=20;
  int kk=0;
  int non_leading_removed=0;
  int non_leading=0;



  double wgt0,wgt1,wgt2,wgt3,wgt4,wgt_total;

  ProcInfo_t procInfo;
  gSystem->GetProcInfo(&procInfo);

  std::cout << "Memory/time used so Far: " << procInfo.fMemResident/1000<< " MB" <<" time = "<<  procInfo.fCpuSys <<  " Sec"<<"\n";

  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"MC TRUTH LOOP  "<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
//////////////////
TDatabasePDG *pdg_DATABASEobject = TDatabasePDG::Instance();

  std::string sysmatics_status;
  if(m_RunCodeWithSystematics==true){sysmatics_status= "Systematics On";}
  else if (m_RunCodeWithSystematics==false){sysmatics_status= "Systematics Off";}
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;
  std::cout<<"~~~~~~~~~  "<< sysmatics_status <<" ~~~~~~~~~ "<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;


  for(int ii=0; ii<chw_MC->GetEntries(); ++ii){
    if(ii%50000==0) std::cout << (ii/1000) << " k " << std::endl;

    //=========================================
    // For every systematic, loop over the universes, and fill the
    // appropriate histogram in the MnvH1D
    //=========================================


    for (auto band : error_bands){

      std::vector<HeliumCVUniverse*> error_band_universes = band.second;
      for (auto universe : error_band_universes){

        // Tell the Event which entry in the TChain it's looking at
        universe->SetEntry(ii);
        ///////////////////////////////////////////
        ////
        ////  FILL CV
        ////
        ///
        ///////////////////////////////////////////


        wgt0 = 1.0;
        wgt1 = universe->GetWeight(kweightFlux );
        wgt2 = universe->GetWeight(kweightGenie);
        wgt3 = universe->GetWeight(kweight2p2ptune );
        wgt4 = universe->GetWeight(kweightRPA);
        wgt_total = universe->GetWeight(kWeightVector);
        //std::cout<< "MINSO weight = "<< wgt2<<std::endl;

        //double wgt6 = universe->GetWeight(kweightLowQ2Pi);
        EventCounter_TRUTH(*universe, kTRUTHCutsVector, EventCounter_weight_0, wgt0);
        EventCounter_TRUTH(*universe, kTRUTHCutsVector, EventCounter_weight_1, wgt1);
        EventCounter_TRUTH(*universe, kTRUTHCutsVector, EventCounter_weight_2, wgt2);
        EventCounter_TRUTH(*universe, kTRUTHCutsVector, EventCounter_weight_3, wgt3);
        EventCounter_TRUTH(*universe, kTRUTHCutsVector, EventCounter_weight_4, wgt4);
        EventCounter_TRUTH(*universe, kTRUTHCutsVector, EventCounter_TRUTH_total, wgt_total );

        if( universe->ShortName() == "cv"){

            if(PassesCutsTRUTH(*universe, kTRUTHCutsVector)){

//////////////////////////////////////////////////////////
//// CUTS HAVE BEEN APPLIED
///////////////////////////////////////////////////////////

             std::vector <int> PDG_trklist = universe->GETvector_PDG_FS_particles();
             std::vector  <double> Angle_trklist = universe->GETvector_theta_wrtb_FS_particles();
             std::vector <double> Energy_trklist   = universe->GETvector_KE_mc_FS_particles_GeV(pdg_DATABASEobject);
              if(PDG_trklist.size()==1){std::cout<<"ERROR"<<std::endl;assert(false);}
              int secondTrk = 999;
              //if(PDG_trklist.size()==0)continue;
              secondTrk = universe->Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_lessthanAngle(PDG_trklist, Energy_trklist, Angle_trklist);
              //secondTrk = universe->Returnindex_True_2ndTk_GreatestKE_lessthanAngle(PDG_trklist, Energy_trklist, Angle_trklist);
              //secondTrk = universe->Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_lessthanAngle_withKE_thresholdonProtonandPion(PDG_trklist, Energy_trklist, Angle_trklist);

              if(secondTrk==-999){
                continue;
              }

              else{

              int pdg_2ndTrk = PDG_trklist.at(secondTrk);
              double secTrkTrueEnergy = Energy_trklist.at(secondTrk);
              double secTrkTrueAngle = Angle_trklist.at(secondTrk);


              auto CryoTank_REGIONS_Truth =  Bulge_Regions_of_CryoTank(universe->GetTRUE_Vertex_z());
              auto CryoTank_Barrel_REGIONS_Truth = Barrel_Region_of_CryoTank(universe->GetTRUE_Vertex_z());
              Particle_type Particle_type_Event = GetParticlegroup_type(pdg_2ndTrk);
              Interaction_type Interaction_type_Event =  universe->Get_InteractionStackType();
              Material_type Material_type_Event = universe->Get_MaterialStackType();

              if(CryoTank_REGIONS_Truth==kUpstream_head){
                auto distance = DistanceFromUpStreamBulge(universe->GetTRUE_Vertex_z() , universe->GetTRUE_Vertex_r());
                h_Truth_Vertex_distance_upstream->Fill(distance, universe->GetWeight(kWeightVector));
                h_Truth_Vertex_distance_upstream_Material.GetComponentHist(Material_type_Event)->Fill(distance, universe->GetWeight(kWeightVector));

                h_Truth_CryoVertex_Z_upstream->Fill(universe->GetTRUE_Vertex_z(), universe->GetWeight(kWeightVector));
                h_Truth_CryoVertex_Z_upstream_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetTRUE_Vertex_r(), universe->GetWeight(kWeightVector));
                Vertex_XYZ XYZinput{universe->GetTRUE_Vertex_x(),universe->GetTRUE_Vertex_y(),universe->GetTRUE_Vertex_z()};
                UpstreamBugle_vector.push_back(XYZinput);

                if(Material_type_Event==kHelium){UpstreamBugle_vector_He.push_back(XYZinput);}
                else if(Material_type_Event==kAluminium){UpstreamBugle_vector_Al.push_back(XYZinput);}



              }
              else if(CryoTank_REGIONS_Truth==kDownstream_head){
                auto distance = DistanceFromDownStreamBulge(universe->GetTRUE_Vertex_z() , universe->GetTRUE_Vertex_r());
                 h_Truth_Vertex_distance_downstream->Fill(distance, universe->GetWeight(kWeightVector));
                 h_Truth_CryoVertex_Z_downstream->Fill(universe->GetTRUE_Vertex_z(), universe->GetWeight(kWeightVector));
                 h_Truth_CryoVertex_Z_downstream_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetTRUE_Vertex_r(), universe->GetWeight(kWeightVector));
                 h_Truth_Vertex_distance_downstream_Material.GetComponentHist(Material_type_Event)->Fill(distance, universe->GetWeight(kWeightVector));
                 Vertex_XYZ XYZinput{universe->GetTRUE_Vertex_x(),universe->GetTRUE_Vertex_y(),universe->GetTRUE_Vertex_z()};
                 DownstreamBugle_vector.push_back(XYZinput);
                 if(Material_type_Event==kHelium){DownstreamBugle_vector_He.push_back(XYZinput);}
                 else if(Material_type_Event==kAluminium){DownstreamBugle_vector_Al.push_back(XYZinput);}
               }
                 if(CryoTank_Barrel_REGIONS_Truth==kCenter){
                   h_Truth_CryoVertex_R_Center_Smearing->Fill(universe->GetTRUE_Vertex_r(), universe->GetWeight(kWeightVector));
                   h_Truth_CryoVertex_Z_Center_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetTRUE_Vertex_r(), universe->GetWeight(kWeightVector));
                   Vertex_XYZ XYZinput{universe->GetTRUE_Vertex_x(),universe->GetTRUE_Vertex_y(),universe->GetTRUE_Vertex_z()};
                   CenterBugle_vector.push_back(XYZinput);

                   if(Material_type_Event==kHelium){CenterBugle_vector_He.push_back(XYZinput);}
                   else if(Material_type_Event==kAluminium){CenterBugle_vector_Al.push_back(XYZinput);}
                 }

              h_MuonE_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetTRUE_Emu(), universe->GetWeight(kWeightVector));
              h_MuonE_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetTRUE_Emu(), universe->GetWeight(kWeightVector));
              h_MuonE_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetTRUE_Emu(), universe->GetWeight(kWeightVector));

              h_MuonPZ_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetTRUE_PZmu(), universe->GetWeight(kWeightVector));
              h_MuonPZ_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetTRUE_PZmu(), universe->GetWeight(kWeightVector));
              h_MuonPZ_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetTRUE_PZmu(), universe->GetWeight(kWeightVector));

              h_MuonPT_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetTRUE_PTmu(), universe->GetWeight(kWeightVector));
              h_MuonPT_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetTRUE_PTmu(), universe->GetWeight(kWeightVector));
              h_MuonPT_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetTRUE_PTmu(), universe->GetWeight(kWeightVector));

              h_MuonTheta_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetTRUE_muANGLE_WRTB_DEG(), universe->GetWeight(kWeightVector));
              h_MuonTheta_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetTRUE_muANGLE_WRTB_DEG(), universe->GetWeight(kWeightVector));
              h_MuonTheta_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetTRUE_muANGLE_WRTB_DEG(), universe->GetWeight(kWeightVector));

              h_MuonPhi_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetTRUE_Phimu(), universe->GetWeight(kWeightVector));
              h_MuonPhi_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetTRUE_Phimu(), universe->GetWeight(kWeightVector));
              h_MuonPhi_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetTRUE_Phimu(), universe->GetWeight(kWeightVector));

              if(secondTrk!= 0)
              {



              } // End of Second trk condition

              h_CryoVertex_X_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetTRUE_Vertex_x(), universe->GetWeight(kWeightVector));
              h_CryoVertex_X_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetTRUE_Vertex_x(), universe->GetWeight(kWeightVector));
              h_CryoVertex_X_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetTRUE_Vertex_x(), universe->GetWeight(kWeightVector));

              h_CryoVertex_Y_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetTRUE_Vertex_y(), universe->GetWeight(kWeightVector));
              h_CryoVertex_Y_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetTRUE_Vertex_y(), universe->GetWeight(kWeightVector));
              h_CryoVertex_Y_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetTRUE_Vertex_y(), universe->GetWeight(kWeightVector));

              h_CryoVertex_Z_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetTRUE_Vertex_z(), universe->GetWeight(kWeightVector));
              h_CryoVertex_Z_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetTRUE_Vertex_z(), universe->GetWeight(kWeightVector));
              h_CryoVertex_Z_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetTRUE_Vertex_z(), universe->GetWeight(kWeightVector));

              h_CryoVertex_R_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetTRUE_Vertex_r(), universe->GetWeight(kWeightVector));
              h_CryoVertex_R_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetTRUE_Vertex_r(), universe->GetWeight(kWeightVector));
              h_CryoVertex_R_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetTRUE_Vertex_r(), universe->GetWeight(kWeightVector));

              h_Tracksize_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetTRUE_Tracksize(), universe->GetWeight(kWeightVector));
              h_Tracksize_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetTRUE_Tracksize(), universe->GetWeight(kWeightVector));
              h_Tracksize_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetTRUE_Tracksize(), universe->GetWeight(kWeightVector));


              h_2d_PZ_PT_TRUE->Fill(universe->GetTRUE_PZmu(),universe->GetTRUE_PTmu(),universe->GetWeight(kWeightVector));
              h_2d_E_PZ_TRUE->Fill(universe->GetTRUE_Emu(),universe->GetTRUE_PZmu(),universe->GetWeight(kWeightVector));
              h_2d_Theta_PZ_TRUE->Fill(universe->GetTRUE_muANGLE_WRTB_DEG(),universe->GetTRUE_PZmu(),universe->GetWeight(kWeightVector));
              h_2d_E_PT_TRUE->Fill(universe->GetTRUE_Emu(),universe->GetTRUE_PTmu(),universe->GetWeight(kWeightVector));
              h_2d_Theta_PT_TRUE->Fill(universe->GetTRUE_muANGLE_WRTB_DEG(),universe->GetTRUE_PTmu(),universe->GetWeight(kWeightVector));
              h_2d_Theta_PZ_TRUE->Fill(universe->GetTRUE_muANGLE_WRTB_DEG(),universe->GetTRUE_PZmu(),universe->GetWeight(kWeightVector));
            }// end of else for -999

            }//end of Truth Cuts

        }


        ///////////////////////////////////////////
        ////
        ////  END OF CV
        ////
        ////
        ///////////////////////////////////////////



        //std::cout<< "GetMuonAngleWRTB() > 12.0" << universe->GetMuonAngleWRTB() <<std::endl;
        //=========================================
        // CUTS in each universe
        //=========================================
        ////////////
        ///TRUTH
        ///////////

        if(PassesCutsTRUTH(*universe, kTRUTHCutsVector)){

         std::vector <int> PDG_trklist = universe->GETvector_PDG_FS_particles();
         std::vector  <double> Angle_trklist = universe->GETvector_theta_wrtb_FS_particles();

          for(auto cat : Angle_trklist){h_secTrk_ALLangles_TRUE.univHist(universe)->Fill(cat,universe->GetWeight(kWeightVector));
          }
         std::vector <double> Energy_trklist   = universe->GETvector_KE_mc_FS_particles_GeV(pdg_DATABASEobject);


          int secondTrk = 999;
          if(PDG_trklist.size()==0)continue;
          secondTrk = universe->Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_lessthanAngle(PDG_trklist, Energy_trklist, Angle_trklist ) ;
          //secondTrk = universe->Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_lessthanAngle_withKE_thresholdonProtonandPion(PDG_trklist, Energy_trklist, Angle_trklist) ;
          //secondTrk = universe->Returnindex_True_2ndTk_GreatestKE_lessthanAngle(PDG_trklist, Energy_trklist, Angle_trklist);
          if(secondTrk == 0 || secondTrk == -999) continue; // remove 2nd trks that are leading muons
          int pdg_2ndTrk = PDG_trklist.at(secondTrk);
          double secTrkTrueEnergy = Energy_trklist.at(secondTrk);
          double secTrkTrueAngle = Angle_trklist.at(secondTrk);
          Particle_type Particle_type_Event = GetParticlegroup_type(pdg_2ndTrk);


          h_MuonE_TRUE.univHist(universe)->Fill(universe->GetTRUE_Emu(),universe->GetWeight(kWeightVector));

          h_MuonPZ_TRUE.univHist(universe)->Fill(universe->GetTRUE_PZmu(),universe->GetWeight(kWeightVector));

          h_MuonPT_TRUE.univHist(universe)->Fill(universe->GetTRUE_PTmu(),universe->GetWeight(kWeightVector));

          h_MuonTheta_TRUE.univHist(universe)->Fill(universe->GetTRUE_muANGLE_WRTB_DEG(),universe->GetWeight(kWeightVector));

          h_CryoVertex_X_TRUE.univHist(universe)->Fill(universe->GetTRUE_Vertex_x(),universe->GetWeight(kWeightVector));

          h_CryoVertex_Y_TRUE.univHist(universe)->Fill(universe->GetTRUE_Vertex_y(),universe->GetWeight(kWeightVector));

          h_CryoVertex_Z_TRUE.univHist(universe)->Fill(universe->GetTRUE_Vertex_z(),universe->GetWeight(kWeightVector));

          h_CryoVertex_R_TRUE.univHist(universe)->Fill(universe->GetTRUE_Vertex_r(),universe->GetWeight(kWeightVector));

          h_Tracksize_TRUE.univHist(universe)->Fill(universe->GetTRUE_Tracksize(),universe->GetWeight(kWeightVector));

          h_secTrk_DOCA_TRUE.univHist(universe)->Fill(universe->GetTRUE_nonMuonDOCA(secondTrk),universe->GetWeight(kWeightVector));
          h_secTrk_Pathlength_TRUE.univHist(universe)->Fill(universe->GetTRUE_nonMuoncolumnarDensity(secondTrk),universe->GetWeight(kWeightVector));
          h_secTrk_Energy_TRUE.univHist(universe)->Fill(secTrkTrueEnergy,universe->GetWeight(kWeightVector));
          h_secTrk_Theta_TRUE.univHist(universe)->Fill(secTrkTrueAngle,universe->GetWeight(kWeightVector));
          h_secTrk_Openangle_TRUE.univHist(universe)->Fill(universe->GetTRUE_NonmuTrkopenangle(secondTrk),universe->GetWeight(kWeightVector));

        }//END OF TRUTH PASS CUTS

      } // End band's universe loop
    } // End Band loop
  } //End entries loop

  gSystem->GetProcInfo(&procInfo);
  std::cout << " Done with loop Mem1: " << procInfo.fMemResident/1000 << " MB" << " time = "<<  procInfo.fCpuSys  <<  " sec""\n";
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
//EventCountMap[kPlayListVector[0]] = EventCounter_MCFull;
//EventCountMap[kPlayListVector[2]] = EventCounter_dataFull;
//EventCountMap[kPlayListVector[3]] = EventCounter_dataEmpty;



//////////////////////////////////////////////////////////////////////////
//End of Empty data
//////////////////////////////////////////////////////////////////////////


double countdata= 0.0;
double countmc= 0.0;

    h_MuonPZ_TRUE.SyncCVHistos();
    h_MuonPT_TRUE.SyncCVHistos();
    h_MuonE_TRUE.SyncCVHistos();
    h_MuonTheta_TRUE.SyncCVHistos();
    h_secTrk_DOCA_TRUE.SyncCVHistos();
    h_Tracksize_TRUE.SyncCVHistos();
//////////////////////////////////

    h_CryoVertex_X_TRUE.SyncCVHistos();
    h_CryoVertex_Y_TRUE.SyncCVHistos();
    h_CryoVertex_R_TRUE.SyncCVHistos();
    h_CryoVertex_Z_TRUE.SyncCVHistos();

    //////////////////////////////////
    h_secTrk_Energy_TRUE.SyncCVHistos();
    h_secTrk_Theta_TRUE.SyncCVHistos();
    h_secTrk_Openangle_TRUE.SyncCVHistos();
    h_secTrk_Pathlength_TRUE.SyncCVHistos();


    //////////////////////////////////
    //////////////////////////////////
    //MuonEnergymaterial.Write();
    //outFile.cd();
    //outFile.Write();
    //LOGFILE.Close();
  //=========================================
  // Plot stuff
  //=========================================

  // DrawMCWithErrorBand
//  PlotCVAndError(Muon_PZ_FULLMC.hist, "TEST");



  char outFileName[1024];
  auto playlist_name = Playlist_Info.GetPlaylistname();
  std::string datatype = "TRUTH";
  char c[playlist_name.length() + 1];
  char d[datatype.length() + 1];

  char rootpathway[OUTputRoot_pathway.length()+1];
  strcpy(rootpathway, OUTputRoot_pathway.c_str());
  strcpy(c, playlist_name.c_str());
  strcpy(d, datatype.c_str());
  //PrintCutstoScreen( kTRUTHCutsVector , EventCounter_RECO, c, mcscale );
  char EventRateName[1024];
   sprintf(EventRateName, "TRUE_Weight_ALL_Weights_ENERGYcuts_TRUEMC_%s_SMEARING",c);
   Make_cvsOfCutsRateTRUE( kTRUTHCutsVector_Energy , EventCounter_TRUTH_total, EventRateName  ,1.0 ,1.0);


  //outFileName = "Histograms_test.root";
  //auto outFile = TFile::Open(outFileName);

  std::string systematics_status;
  if(m_RunCodeWithSystematics==true){
    sysmatics_status= "All_SysErrorsOn";
    std::cout<<"print to: "<< sysmatics_status <<std::endl ;
    }
  else if (m_RunCodeWithSystematics==false){
    sysmatics_status= "StatsONLY";}

    std::cout<<"print to: "<< sysmatics_status <<std::endl ;
    char sysmatics_status_char[sysmatics_status.length()+1];
    strcpy(sysmatics_status_char, sysmatics_status.c_str());

  sprintf(outFileName, "%s/Histograms_%s_%s_%s_SMEARING.root",rootpathway,c,d,sysmatics_status_char);

  std::cout << "Writing output file to: " <<outFileName << std::endl;

  //TFile outFile(outFileName, "RECREATE");

  //TFile *outFile(outFileName, "RECREATE");
  TFile *outFile = new TFile(outFileName,"RECREATE");
  TChain POT_branch("Meta");
  POT_branch.Add(RootName.c_str());
  //TTree *oldtree = (TTree*)file->Get("Meta");
  TTree *clone = POT_branch.CloneTree();
  clone->Write();

  h_secTrk_DOCA_TRUE.hist->Write();
  h_secTrk_DOCA_TRUE_Material.WriteToFile(*outFile);
  h_secTrk_DOCA_TRUE_Interaction.WriteToFile(*outFile);
  h_secTrk_DOCA_TRUE_Particle.WriteToFile(*outFile);

  h_secTrk_Pathlength_TRUE.hist->Write();
  h_secTrk_Pathlength_TRUE_Material.WriteToFile(*outFile);
  h_secTrk_Pathlength_TRUE_Interaction.WriteToFile(*outFile);
  h_secTrk_Pathlength_TRUE_Particle.WriteToFile(*outFile);


////////////////////////////////////////////////
  h_MuonE_TRUE.hist->Write();
  h_MuonE_TRUE_Material.WriteToFile(*outFile);
  h_MuonE_TRUE_Interaction.WriteToFile(*outFile);
  h_MuonE_TRUE_Particle.WriteToFile(*outFile);

  h_MuonPZ_TRUE.hist->Write();
  h_MuonPZ_TRUE_Material.WriteToFile(*outFile);
  h_MuonPZ_TRUE_Interaction.WriteToFile(*outFile);
  h_MuonPZ_TRUE_Particle.WriteToFile(*outFile);

  h_MuonPT_TRUE.hist->Write();
  h_MuonPT_TRUE_Material.WriteToFile(*outFile);
  h_MuonPT_TRUE_Interaction .WriteToFile(*outFile);
  h_MuonPT_TRUE_Particle.WriteToFile(*outFile);

  h_MuonTheta_TRUE.hist->Write();
  h_MuonTheta_TRUE_Material.WriteToFile(*outFile);
  h_MuonTheta_TRUE_Interaction.WriteToFile(*outFile);
  h_MuonTheta_TRUE_Particle.WriteToFile(*outFile);


  h_CryoVertex_X_TRUE.hist->Write();
  h_CryoVertex_X_TRUE_Material.WriteToFile(*outFile);
  h_CryoVertex_X_TRUE_Interaction.WriteToFile(*outFile);
  h_CryoVertex_X_TRUE_Particle.WriteToFile(*outFile);

  h_CryoVertex_Y_TRUE.hist->Write();
  h_CryoVertex_Y_TRUE_Material.WriteToFile(*outFile);
  h_CryoVertex_Y_TRUE_Interaction.WriteToFile(*outFile);
  h_CryoVertex_Y_TRUE_Particle.WriteToFile(*outFile);

  h_CryoVertex_Z_TRUE.hist->Write();
  h_CryoVertex_Z_TRUE_Material.WriteToFile(*outFile);
  h_CryoVertex_Z_TRUE_Interaction.WriteToFile(*outFile);
  h_CryoVertex_Z_TRUE_Particle.WriteToFile(*outFile);

  h_CryoVertex_R_TRUE.hist->Write();
  h_CryoVertex_R_TRUE_Material.WriteToFile(*outFile);
  h_CryoVertex_R_TRUE_Interaction.WriteToFile(*outFile);
  h_CryoVertex_R_TRUE_Particle.WriteToFile(*outFile);


  h_secTrk_Openangle_TRUE.hist->Write();
  h_secTrk_Openangle_TRUE_Material.WriteToFile(*outFile);
  h_secTrk_Openangle_TRUE_Interaction.WriteToFile(*outFile);
  h_secTrk_Openangle_TRUE_Particle.WriteToFile(*outFile);

  h_secTrk_Energy_TRUE.hist->Write();
  h_secTrk_Energy_TRUE_Material.WriteToFile(*outFile);
  h_secTrk_Energy_TRUE_Interaction.WriteToFile(*outFile);
  h_secTrk_Energy_TRUE_Particle.WriteToFile(*outFile);

  h_secTrk_Theta_TRUE.hist->Write();
  h_secTrk_Theta_TRUE_Material.WriteToFile(*outFile);
  h_secTrk_Theta_TRUE_Interaction.WriteToFile(*outFile);
  h_secTrk_Theta_TRUE_Particle.WriteToFile(*outFile);

  h_secTrk_ALLangles_TRUE.hist->Write();

  h_Tracksize_TRUE.hist->Write();
  h_Tracksize_TRUE_Material.WriteToFile(*outFile);
  h_Tracksize_TRUE_Interaction.WriteToFile(*outFile);
  h_Tracksize_TRUE_Particle.WriteToFile(*outFile);

  h_2d_PZ_PT_TRUE->Write();
  h_2d_E_PZ_TRUE->Write();
  h_2d_Theta_PZ_TRUE->Write();
  h_2d_E_PT_TRUE->Write();
  h_2d_Theta_PZ_TRUE->Write();
  h_2d_Theta_PT_TRUE->Write();
  h_2d_Theta_2ndTrkE_TRUE->Write();
  h_2d_muonE_2ndTrkE_TRUE->Write();
  h_2d_muonPT_2ndTrkE_TRUE->Write();
  h_2d_muonPZ_2ndTrkE_TRUE->Write();
  h_2d_Theta_2ndTrKangle_TRUE->Write();
  h_2d_muonE_2ndTrkangle_TRUE->Write();
  h_2d_muonPT_2ndTrkangle_TRUE->Write();
  h_2d_muonPZ_2ndTrkangle_TRUE->Write();

  h_2d_2ndtrkangle_2ndTrkE_TRUE->Write();
  h_2d_2ndtrkangle_2ndTrkE_Proton_TRUE->Write();
  h_2d_2ndtrkangle_2ndTrkE_Pion_TRUE->Write();
  h_2d_2ndtrkangle_2ndTrkE_Pion0_TRUE->Write();
  h_2d_2ndtrkangle_2ndTrkE_Pion_neg_pos_TRUE->Write();
  h_2d_2ndtrkangle_2ndTrkE_dimuon_TRUE->Write();

  h_Truth_Vertex_distance_upstream->Write();
  h_Truth_Vertex_distance_downstream->Write();
  h_Truth_CryoVertex_R_Center_Smearing->Write();

  h_Truth_CryoVertex_Z_downstream->Write();
  h_Truth_CryoVertex_Z_upstream->Write();

  h_Truth_CryoVertex_Z_upstream_Material.WriteToFile(*outFile);
  h_Truth_CryoVertex_Z_downstream_Material.WriteToFile(*outFile);
  h_Truth_CryoVertex_Z_Center_Material.WriteToFile(*outFile);

  h_Truth_Vertex_distance_upstream_Material.WriteToFile(*outFile);
  h_Truth_Vertex_distance_downstream_Material.WriteToFile(*outFile);

  outFile->Close();

  char pdf_name[1024];
  char pdf_start[1024];
  char pdf_mid[1024];
  char pdf_end[1024];

  sprintf(pdf_name, "TRUTH_PLOTS_%s_%s_SmearingStudy",c,d);

  sprintf(pdf_start,"%s.pdf(",pdf_name);
  sprintf(pdf_mid,  "%s.pdf",pdf_name);
  sprintf(pdf_end,  "%s.pdf)",pdf_name);

  TCanvas *can = new TCanvas("", "");
  MnvPlotter *mnv_plotter = new MnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  can -> Print(pdf_start);

  DrawVertex_Cryotank_X_Y_R_Vs_Z(UpstreamBugle_vector , c, " [TRUTH] Upstream Bugle", pdf_name , can, mnv_plotter);
  DrawVertex_Cryotank_X_Y_R_Vs_Z(DownstreamBugle_vector , c, "[TRUTH] Downstream Bugle" ,pdf_name, can, mnv_plotter);
  DrawVertex_Cryotank_X_Y_R_Vs_Z(CenterBugle_vector, c, "[TRUTH] Center Bugle" ,pdf_name, can, mnv_plotter);

  DrawVertex_Cryotank_X_Y_R_Vs_Z(UpstreamBugle_vector_He ,UpstreamBugle_vector_Al, c, " [TRUTH] Upstream Bugle", pdf_name , can, mnv_plotter);
  DrawVertex_Cryotank_X_Y_R_Vs_Z(DownstreamBugle_vector_He,DownstreamBugle_vector_Al, c, "[TRUTH] Downstream Bugle" ,pdf_name, can, mnv_plotter);
  DrawVertex_Cryotank_X_Y_R_Vs_Z(CenterBugle_vector_He, CenterBugle_vector_Al,c, "[TRUTH] Center Bugle" ,pdf_name, can, mnv_plotter);

  can -> Print(pdf_end);

std::cout<< " the Number of on_leading = "<< non_leading<<std::endl;
std::cout<< " the Number of on_leading_removed = "<< non_leading_removed<<std::endl;




  for(auto band : error_bands){
    std::vector<HeliumCVUniverse*> band_universes = band.second;
    for(unsigned int i_universe = 0; i_universe < band_universes.size(); ++i_universe){ delete band_universes[i_universe];}
  }

  std::cout << "Success in TRUTH LOOP - Gotcha !?!?" << std::endl;

}

TCanvas *can = new TCanvas("can", "can",1800,1600);
can -> Print("Test.pdf");


}//END of Event Loop

//=========================================
//=========================================
//////////////////////////////////////////////////////////////
std::vector<ECutsTRUTH> GetTRUTHCutsVector() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ECutsTRUTH> True_vec;
  True_vec.push_back(kTRUTHNoCuts   );
  True_vec.push_back(kTRUTHneutrino);
  True_vec.push_back(kTRUTHCCInteraction );
  //True_vec.push_back(kTRUTHtarget);
  True_vec.push_back(kTRUTHMuonEnergy );
  True_vec.push_back(kTRUTHMuonAngle );
  //True_vec.push_back(kTRUTHFiduical );
  True_vec.push_back(kTRUTHFiduical_ExtraShell);
  True_vec.push_back(kTRUTH_greaterthanoneFS);
  //True_vec.push_back(kTRUTH_secTrk_Angle_threshold);
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);
  True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold_withProtonanPionThresholds);
  True_vec.push_back(kAllTRUTHCuts);

  return True_vec;
//#endif
}

std::vector<ECutsTRUTH> GetTRUTHCutsVector_Energy() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ECutsTRUTH> True_vec;
  True_vec.push_back(kTRUTHNoCuts   );
  True_vec.push_back(kTRUTHneutrino);
  True_vec.push_back(kTRUTHCCInteraction );
  //True_vec.push_back(kTRUTHtarget);
  True_vec.push_back(kTRUTHMuonEnergy );
  True_vec.push_back(kTRUTHMuonAngle );
  //True_vec.push_back(kTRUTHFiduical );
  True_vec.push_back(kTRUTHFiduical_ExtraShell);
  True_vec.push_back(kTRUTH_greaterthanoneFS);
  //True_vec.push_back(kTRUTH_secTrk_Angle_threshold);
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);
  True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold_withProtonanPionThresholds);

  //True_vec.push_back(kTRUTH_2ndTrkProtonEnergythreshold);
  //True_vec.push_back(kTRUTH_2ndTrkPionEnergythreshold);
  True_vec.push_back(kAllTRUTHCuts);


  //int n = sizeof(kCutsArray) / sizeof(kCutsArray[0]);
  //static std::vector<ECuts> ret_vec(kCutsArray, kCutsArray + n);
  return True_vec;
//#endif
}
//////////////////////////////////////////////////////////////////////////
//GET MUON Varibles
//////////////////////////////////////////////////////////////////////////
std::vector<MuonVar> GetMUONVaribles() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<MuonVar> MuonVars;

  MuonVars.push_back(kE );
  MuonVars.push_back(kP_Z);
  MuonVars.push_back(kP_T);
  MuonVars.push_back(kAngleWRTB);
  MuonVars.push_back(kDOCA_muon);

  MuonVars.push_back(kTRUTH_E );
  MuonVars.push_back(kTRUTH_P_Z);
  MuonVars.push_back(kTRUTH_P_T);
  MuonVars.push_back(kTRUTH_AngleWRTB);

  return MuonVars;
//#endif
}

std::vector<Particle_type> GetParicle_type() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<Particle_type> Particle;
  Particle.push_back(kProton);
  Particle.push_back(kMuon);
  Particle.push_back(kPion_0);
  Particle.push_back(kPion_neg);
  Particle.push_back(kPion_pos);

  return Particle;
//#endif
}

//////////////////////////////////////////////////////////////////////////
//GET Vertex Varibles
//////////////////////////////////////////////////////////////////////////
std::vector<CryoVertex> GetCryoVertexVaribles() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<CryoVertex> CryoVertexVars;

  CryoVertexVars.push_back(kX);
  CryoVertexVars.push_back(kY);
  CryoVertexVars.push_back(kZ);
  CryoVertexVars.push_back(kR);


  CryoVertexVars.push_back(kTRUTH_X);
  CryoVertexVars.push_back(kTRUTH_Y);
  CryoVertexVars.push_back(kTRUTH_Z);
  CryoVertexVars.push_back(kTRUTH_R);

  return CryoVertexVars;
//#endif
}




std::vector<ME_helium_Playlists> GetPlayListVector() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ME_helium_Playlists> Playlist;

  //Playlist.push_back(kME1F);
  //Playlist.push_back(kME1P);
  //Playlist.push_back(kME1D);
  ///Playlist.push_back(kME1C);
  Playlist.push_back(kME1A);//
  //Playlist.push_back(kME1G);//
  //Playlist.push_back(kME1E);//

  return Playlist;
//#endif
}

std::vector<SecondTrkVar> GetPlayListSecondTrkVector() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<SecondTrkVar> Playlist;

  Playlist.push_back(ksecE);
  Playlist.push_back(kThetamid);

  return Playlist;
//#endif
}
std::vector<Weights> GetWeightVector() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<Weights> weight_vec;
  weight_vec.push_back(kweightFlux );
  //weight_vec.push_back(kweightMinos ); Don't apply Minos efficiency weight to truth
  weight_vec.push_back(kweightGenie);
  weight_vec.push_back(kweight2p2ptune );
  weight_vec.push_back(kweightRPA);

  //weight_vec.push_back(kweightLowQ2Pi);

  return weight_vec;
//#endif
}





//////////////////////////////////////////////////////////////////////////
//GET CryoTank Varibles
//////////////////////////////////////////////////////////////////////////


//////////////////////////
///Main
/////////////////////////
int main(){
  bool m_cutson = true;
  std::cout << "Run over cutsOn?  (0 = false, 1 = true) " << std::endl;
  //std::cin >> cutsOn;
  std::cout << std::boolalpha << m_cutson << std::endl;

  bool m_debugOn=true;
  std::cout << "Run in Debug Mode? (0 = NO, 1 = YES) " << std::endl;
  //std::cin >> my_debug;
  std::cout << std::boolalpha << m_debugOn << std::endl;


  std::string input_user= "cnguyen";
  std::cout << "What is the name of the user? " << std::endl;
  //std::cin >> input_user;
  std::cout << input_user << std::endl;


  runEventLoop();
  return 0;
}
//#endif
