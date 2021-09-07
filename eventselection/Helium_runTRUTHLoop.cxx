// Loop entries, make cuts, fill histograms.
// * Uses the New Systematics Framework and "Universe" objects.
// * loop universes, make cuts and fill histograms with the correct lateral
// shifts and weights for each universe.
// * TChain --> PlotUtils::ChainWrapper.
// * MnvHXD --> PlotUtils::HistWrapper.
// * Genie, flux, non-resonant pion, and some detector systematics calculated.
#include "Helium_runTRUTHLoop.h"

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

const bool m_RunCodeWithSystematics = true;


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


/*const auto TracksGreaterThan2 = {  NamedCategory<int>({3},   "ThirdTrack"),
                                   NamedCategory<int>({4},   "FourthTrack"),
                                   NamedCategory<int>({5},   "FifthTrack"),
                                   NamedCategory<int>({6},   "SixthTrack"),
                                   NamedCategory<int>({7},   "SevethTrack"),
                                   NamedCategory<int>({8},   "EighthTrack")

                                 };*/

const int n_flux_universes = 100;
std::map< std::string, std::vector<HeliumCVUniverse*> >
  GetErrorBands(PlotUtils::ChainWrapper* chain) {
    typedef std::map< std::string, std::vector<HeliumCVUniverse*> > SystMap;
    //const int n_flux_universes = 50;
    SystMap error_bands;

    // CV
    error_bands[std::string("cv")].push_back( new HeliumCVUniverse(chain) );

    //Detector systematics, lateral shifts

    if(m_RunCodeWithSystematics==true)
    {
      //Flux
      SystMap flux_systematics = PlotUtils::GetFluxSystematicsMap<HeliumCVUniverse>(chain,n_flux_universes);
      error_bands.insert(flux_systematics.begin(), flux_systematics.end());
      //GENIE
      SystMap genie_systematics = PlotUtils::GetGenieSystematicsMap<HeliumCVUniverse>(chain);
      error_bands.insert(genie_systematics.begin(), genie_systematics.end());
      //2p2h tune talk
      SystMap a2p2h_systematics = PlotUtils::Get2p2hSystematicsMap<HeliumCVUniverse>(chain);
      error_bands.insert(a2p2h_systematics.begin(), a2p2h_systematics.end());
      //RPA model
      SystMap RPA_systematics = PlotUtils::GetRPASystematicsMap<HeliumCVUniverse>(chain);
      error_bands.insert(RPA_systematics.begin(), RPA_systematics.end());

      SystMap HeliumTargetMass_systematics = GetHeliumTargetMassSystematicsMap<HeliumCVUniverse>(chain);
      error_bands.insert(HeliumTargetMass_systematics.begin(), HeliumTargetMass_systematics.end());

    }


        //SystMap LowQ2Pi_systematics = PlotUtils::GetLowQ2PiSystematicsMap<HeliumCVUniverse>(chain);
        //error_bands.insert(LowQ2Pi_systematics.begin(), LowQ2Pi_systematics.end());



  // Non-res pi
  //SystMap nonrespi_systematics =
  //  PlotUtils::GetNonResPiSystematicsMap<HeliumCVUniverse>(chain);
  //error_bands.insert(nonrespi_systematics.begin(), nonrespi_systematics.end());


  return error_bands;
}
//======================================================================
// Main
//======================================================================
void runEventLoop(ME_helium_Playlists &PlayList_iterator , bool &Run_EventLoopOnGrid) {
  // Make a chain of events
  loadLibs();
double POT[4];
const std::vector<ECutsTRUTH> kTRUTHCutsVector = GetTRUTHCutsVector();
const std::vector<ECutsTRUTH> kTRUTHCutsVector_Energy = GetTRUTHCutsVector_Energy();

//const std::vector<ME_helium_Playlists> kPlayListVector = GetPlayListVector();
//const std::vector< ME_helium_Playlists> kTRUEPlayListVector = GetTRUEPlayListVector();
const std::vector<Weights> kWeightVector = GetWeightVector();
const std::vector<MuonVar> kMuonVaribles_vector = GetMUONVaribles();
const std::vector<SecondTrkVar> ksecTrkVaribles_vector = GetPlayListSecondTrkVector();

const std::vector<CryoVertex> kCryoVertexVaribles_vector = GetCryoVertexVaribles();

const std::vector<Particle_type> kSecondary_particle_vector = GetParicle_type();

std::ofstream output("LogFile_TRUTH.txt",std::ofstream::app);

//======================================================================
////////////////////ADDING TO CHAIN wrapper ///////////////////////////
//======================================================================
bool is_mc= true;

std::vector <True_Event_info> Nu_mu_secTrkParticle;
std::vector <True_Event_info> Nu_e_secTrkParticle;
std::vector <True_Event_info> Electron_secTrkParticle;
std::vector <True_Event_info> Other_secTrkParticle;
std::vector <True_Event_info> fourHelium_secTrkParticle;
std::vector <True_Event_info> N_A_secTrkParticle;
std::vector <True_Event_info> secTrk_999_Particle;
std::vector <ALL_True_Event_info> ALL_EventInfoNu_e_secTrkParticle;
std::vector <ALL_True_Event_info> ALL_EventInfoNu_mu_secTrkParticle;



//or(auto PlayList_iterator:kPlayListVector ){

  MinervaUniverse::SetTruth(true);
  MinervaUniverse::SetNuEConstraint(true);
  MinervaUniverse::SetAnalysisNuPDG(14);
  MinervaUniverse::SetNFluxUniverses(n_flux_universes);
  MinervaUniverse::SetZExpansionFaReweight(false);
  MinervaUniverse::SetNonResPiReweight(true);
  MinervaUniverse::SetDeuteriumGeniePiTune(false);
  std::string playlist = GetPlaylist(PlayList_iterator);
  MinervaUniverse::SetPlaylist(playlist);


 std::string seestring = MinervaUniverse::GetPlaylist();
  //MinervaUniverse::Set_Multiple_resetPlaylist(true);
  HeliumPlayListInfo Playlist_Info(playlist);
    std::cout<<"Working with Playlist =  "<<   seestring <<std::endl;


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
for(auto band :error_bands ){std::cout<<"Checking Universe this is universe with name : " << band.first<<std::endl;}
std::vector<std::vector<HeliumCVUniverse*>> Error_Band_Universe_GROUPS = groupCompatibleUniverses(error_bands);

std::cout<< "error_bands.size() = " << error_bands.size()<<std::endl;
std::cout<< "Error_Band_GROUPS.size() = " << Error_Band_Universe_GROUPS.size()<<std::endl;


//double mcPOT = GetPOT(chw_MC, "MC");
std::cout<<"Number of Universes set is = "<< 	MinervaUniverse::GetNFluxUniverses()<<std::endl;
//std::string NumU = MinervaUniverse::GetNFluxUniverses()<<std::endl;
//Debug("Number of Universes set is = " );
//Debug(NumU);
//MinervaUniverse::SetNFluxUniverses(25);
POTCounter pot_counter;
//const std::string RootName = GetPlaylist_ROOT_path("1G_Bugfix",  is_mc );
//const std::string RootName = GetPlaylist_ROOT_path("1G_Bugfix",  is_mc );
//const std::string RootName = GetPlaylist_ROOT_path("1F_pdgcorrection_2",  is_mc );
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



//Bins for varibles //
//Muons ///////////////////
std::vector<double> Ebin_vector = GetBinMuonVector(kE);
std::vector<double> Pzbin_vector= GetBinMuonVector(kP_Z);
std::vector<double> PTbin_vector= GetBinMuonVector(kP_T);
std::vector<double> MuonThetabin_vector= GetBinMuonVector(kAngleWRTB);
std::cout<< "size MuonThetabin_vector =  "<< MuonThetabin_vector.size()<<std::endl;
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
std::vector<double> Vertex_secondTrkEbins= GetSecondTrkVarVector(ksecE); //GetSecondTrkVarVector(ksecE);,ksecE_Proton
std::vector<double> Vertex_secondTrkEbin_Proton_vector= GetSecondTrkVarVector(ksecE_Proton);
//std::sort(Vertex_secondTrkEbin_Proton_vector.begin(),Vertex_secondTrkEbin_Proton_vector.end());
std::vector<double> Vertex_secondTrkTheta_bins= GetSecondTrkVarVector(kThetamid);//GetSecondTrkVarVector(kFullAngle);
std::vector<double> Vertex_secondTrkDOCA_bins= GetSecondTrkVarVector(kDOCA);
std::vector<double> Vertex_secondTrkPathway_bins= GetSecondTrkVarVector(kPathway);

std::vector<double> Recoil_track_length_vector;
double recoil_bin_count=0.0;
for(int ww = 0; ww < 50; ww++ ){
Recoil_track_length_vector.push_back(recoil_bin_count);
recoil_bin_count = recoil_bin_count + 2.54; // bins in [cm]
}
////////////////
//muon Varibles///
////////////////

//PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE("h_MuonE", "Muon_{E} NEW Method", Ebin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE_TRUE("h_MuonE_TRUE", "Muon_{E} NEW Method", Ebin_vector , error_bands);
MnvH1D *h_MuonE_MFP_pi_TRUE         =    new MnvH1D("h_MuonE_MFP_pi_TRUE", "h_MuonE_MFP_pi_TRUE",  Ebin_vector.size()-1,  Ebin_vector.data());


PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonE_TRUE_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonE_TRUE_Material", Ebin_vector ,"MuonE_TRUE_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonE_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_MuonE_TRUE_Interaction", Ebin_vector ,"MuonE_TRUE_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_MuonE_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_MuonE_TRUE_Particle", Ebin_vector ,"MuonE_TRUE_Particle; [GeV];Events");


PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPZ_TRUE("h_MuonPZ_TRUE", "Muon_{PZ} NEW Method",  Pzbin_vector , error_bands);
MnvH1D *h_MuonPZ_MFP_pi_TRUE         =    new MnvH1D("h_MuonPZ_MFP_pi_TRUE", "h_MuonPZ_MFP_pi_TRUE",  Pzbin_vector.size()-1,  Pzbin_vector.data());



PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonPZ_TRUE_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonPZ_TRUE_Material", Pzbin_vector ,"h_MuonPZ_TRUE_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonPZ_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_MuonPZ_TRUE_Interaction", Pzbin_vector ,"h_MuonPZ_TRUE_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_MuonPZ_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_MuonPZ_TRUE_Particle", Pzbin_vector ,"h_MuonPZ_TRUE_Particle; [GeV];Events");


PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPT_TRUE("h_MuonPT_TRUE", "Muon_{PT} NEW Method",  PTbin_vector , error_bands);
MnvH1D *h_MuonPT_MFP_pi_TRUE         =    new MnvH1D("h_MuonPT_MFP_pi_TRUE", "h_MuonPT_MFP_pi_TRUE",  PTbin_vector.size()-1,  PTbin_vector.data());



PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonPT_TRUE_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonPT_TRUE_Material", PTbin_vector ,"h_MuonPT_TRUE_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonPT_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_MuonPT_TRUE_Interaction", PTbin_vector ,"h_MuonPT_TRUE_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_MuonPT_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_MuonPT_TRUE_Particle", PTbin_vector ,"h_MuonPT_TRUE_Particle; [GeV];Events");



PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonTheta_TRUE("h_MuonTheta_TRUE", "MuonTheta [Deg]",  MuonThetabin_vector , error_bands);
MnvH1D *h_MuonTheta_MFP_pi_TRUE         =    new MnvH1D("h_MuonTheta_MFP_pi_TRUE", "h_MuonTheta_MFP_pi_TRUE",  MuonThetabin_vector.size()-1,  MuonThetabin_vector.data());




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

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_TracksizeALL_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_TracksizeALL_TRUE_Particle", TrackSize_vector ,"h_TracksizeALL_TRUE_Particle; [Tracknumber];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_TracksizeALL_leadingTRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_TracksizeALL_leadingTRUE_Particle", TrackSize_vector ,"h_TracksizeALL_leadingTRUE_Particle; [Tracknumber];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_TracksizeALL_nonleadingTRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_TracksizeALL_nonleadingTRUE_Particle", TrackSize_vector ,"h_TracksizeALL_nonleadingTRUE_Particle; [Tracknumber];Events");



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
///
/// Proton
///

MnvH2D *h_2d_Theta_2ndTrkE_Proton_TRUE         =    new MnvH2D("h_2d_Theta_2ndTrkE_Proton_TRUE", "h_2d_Theta_2ndTrkE_Proton_TRUE", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );
MnvH2D *h_2d_muonE_2ndTrkE_Proton_TRUE         =    new MnvH2D("h_2d_muonE_2ndTrkE_Proton_TRUE", "h_2d_muonE_2ndTrkE_Proton_TRUE", Ebin_vector.size()-1, Ebin_vector.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );
MnvH2D *h_2d_muonPT_2ndTrkE_Proton_TRUE         =    new MnvH2D("h_2d_muonPT_2ndTrkE_Proton_TRUE", "h_2d_muonPT_2ndTrkE_Proton_TRUE",  PTbin_vector.size()-1,  PTbin_vector.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );
MnvH2D *h_2d_muonPZ_2ndTrkE_Proton_TRUE         =    new MnvH2D("h_2d_muonPZ_2ndTrkE_Proton_TRUE", "h_2d_muonPZ_2ndTrkE_Proton_TRUE",  Pzbin_vector.size()-1,  Pzbin_vector.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );

MnvH2D *h_2d_Theta_2ndTrkE_Pion_TRUE         =    new MnvH2D("h_2d_Theta_2ndTrkE_Pion_TRUE", "h_2d_Theta_2ndTrkE_Pion_TRUE", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );
MnvH2D *h_2d_muonE_2ndTrkE_Pion_TRUE         =    new MnvH2D("h_2d_muonE_2ndTrkE_Pion_TRUE", "h_2d_muonE_2ndTrkE_Pion_TRUE", Ebin_vector.size()-1, Ebin_vector.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );
MnvH2D *h_2d_muonPT_2ndTrkE_Pion_TRUE         =    new MnvH2D("h_2d_muonPT_2ndTrkE_Pion_TRUE", "h_2d_muonPT_2ndTrkE_Pion_TRUE",  PTbin_vector.size()-1,  PTbin_vector.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );
MnvH2D *h_2d_muonPZ_2ndTrkE_Pion_TRUE         =    new MnvH2D("h_2d_muonPZ_2ndTrkE_Pion_TRUE", "h_2d_muonPZ_2ndTrkE_Pion_TRUE",  Pzbin_vector.size()-1,  Pzbin_vector.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );



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
/////////////////////////////////////
//
/////////////////////////////////////
MnvH2D *h_2d_2ndtrkPathlength_2ndTrkE_TRUE    =    new MnvH2D("h_2d_2ndtrkPathlength_2ndTrkE_TRUE", "h_2d_2ndtrkPathlength_2ndTrkE_TRUE", Vertex_secondTrkPathway_bins.size()-1, Vertex_secondTrkPathway_bins.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );

MnvH2D *h_2d_2ndtrkPathlength_2ndTrkE_Proton_TRUE    =    new MnvH2D("h_2d_2ndtrkPathlength_2ndTrkE_Proton_TRUE", "h_2d_2ndtrkPathlength_2ndTrkE_Proton_TRUE", Vertex_secondTrkPathway_bins.size()-1, Vertex_secondTrkPathway_bins.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );

MnvH2D *h_2d_2ndtrkPathlength_2ndTrkE_Pion_TRUE    =    new MnvH2D("h_2d_2ndtrkPathlength_2ndTrkE_Pion_TRUE", "h_2d_2ndtrkPathlength_2ndTrkE_Pion_TRUE", Vertex_secondTrkPathway_bins.size()-1, Vertex_secondTrkPathway_bins.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );

//MnvH2D *h_2d_2ndtrkPathlength_2ndTrkE_dimuon_TRUE_RECO    =    new MnvH2D("h_2d_2ndtrkPathlength_2ndTrkE_dimuon_TRUE_RECO", "h_2d_2ndtrkPathlength_2ndTrkE_dimuon_TRUE_RECO", Vertex_secondTrkPathway_bins.size()-1, Vertex_secondTrkPathway_bins.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );
//////////////////
////
/////////////////
MnvH2D *h_2d_2ndtrkPathlength_2ndtrkangle_TRUE    =    new MnvH2D("h_2d_2ndtrkPathlength_2ndtrkangle_TRUE", "h_2d_2ndtrkPathlength_2ndtrkangle_TRUE", Vertex_secondTrkPathway_bins.size()-1, Vertex_secondTrkPathway_bins.data(),Vertex_secondTrkTheta_bins.size()-1, Vertex_secondTrkTheta_bins.data()  );

MnvH2D *h_2d_2ndtrkPathlength_2ndtrkangle_Proton_TRUE    =    new MnvH2D("h_2d_2ndtrkPathlength_2ndtrkangle_Proton_TRUE", "h_2d_2ndtrkPathlength_2ndtrkangle_Proton_TRUE", Vertex_secondTrkPathway_bins.size()-1, Vertex_secondTrkPathway_bins.data(),Vertex_secondTrkTheta_bins.size()-1, Vertex_secondTrkTheta_bins.data()  );

MnvH2D *h_2d_2ndtrkPathlength_2ndtrkangle_Pion_TRUE    =    new MnvH2D("h_2d_2ndtrkPathlength_2ndtrkangle_Pion_TRUE", "h_2d_2ndtrkPathlength_2ndtrkangle_Pion_TRUE", Vertex_secondTrkPathway_bins.size()-1, Vertex_secondTrkPathway_bins.data(),Vertex_secondTrkTheta_bins.size()-1, Vertex_secondTrkTheta_bins.data()  );

//MnvH2D *h_2d_2ndtrkPathlength_2ndtrkangle_dimuon_TRUE_RECO    =    new MnvH2D("h_2d_2ndtrkPathlength_2ndtrkangle_dimuon_TRUE_RECO", "h_2d_2ndtrkPathlength_2ndtrkangle_dimuon_TRUE_RECO", Vertex_secondTrkPathway_bins.size()-1, Vertex_secondTrkPathway_bins.data(),Vertex_secondTrkTheta_bins.size()-1, Vertex_secondTrkTheta_bins.data()  );


//MnvH2D *h_2d_Theta_PT_TRUE         =    new MnvH2D("h_2d_Theta_PT_TRUE", "h_2d_Theta_PT_TRUE", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),PTbin_vector.size()-1, PTbin_vector.data()  );
//MnvH2D *h_2d_Theta_PT_TRUE_RECO    =    new MnvH2D("h_2d_Theta_PT_TRUE_RECO", "h_2d_Theta_PT_TRUE_RECO", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),PTbin_vector.size()-1, PTbin_vector.data()  );
///////////////////////////////////////
//
///////////////////////////////////////

MnvH2D *h_2d_2ndtrkangle_2ndTrkE_TRUE         =    new MnvH2D("h_2d_2ndtrkangle_2ndTrkE_TRUE", "h_2d_2ndtrkangle_2ndTrkE_TRUE", Vertex_secondTrkTheta_bins.size()-1, Vertex_secondTrkTheta_bins.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );
MnvH2D *h_2d_2ndtrkangle_2ndTrkE_Proton_TRUE         =    new MnvH2D("h_2d_2ndtrkangle_2ndTrkE_Proton_TRUE", "h_2d_2ndtrkangle_2ndTrkE_Proton_TRUE", Vertex_secondTrkTheta_bins.size()-1, Vertex_secondTrkTheta_bins.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );
MnvH2D *h_2d_2ndtrkangle_2ndTrkE_Pion_TRUE         =    new MnvH2D("h_2d_2ndtrkangle_2ndTrkE_Pion_TRUE", "h_2d_2ndtrkangle_2ndTrkE_Pion_TRUE", Vertex_secondTrkTheta_bins.size()-1, Vertex_secondTrkTheta_bins.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );

MnvH2D *h_2d_2ndtrkangle_2ndTrkE_dimuon_TRUE         =    new MnvH2D("h_2d_2ndtrkangle_2ndTrkE_dimuon_TRUE", "h_2d_2ndtrkangle_2ndTrkE_dimuon_TRUE", Vertex_secondTrkTheta_bins.size()-1, Vertex_secondTrkTheta_bins.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );
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

MnvH2D *h_2d_vertexR_Z_MFP_pi_TRUE         =    new MnvH2D("h_2d_vertexR_Z_MFP_pi_TRUE", "h_2d_vertexR_Z_MFP_pi_TRUE", Vertex_Zbins.size()-1, Vertex_Zbins.data(),Vertex_Rbins.size()-1, Vertex_Rbins.data()  );



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
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Pathlength_PROTON_TRUE("h_secTrk_Pathlength_PROTON_TRUE", "h_secTrk_Pathlength_PROTON_TRUTH",  Vertex_secondTrkPathway_bins , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Pathlength_PION_TRUE("h_secTrk_Pathlength_PION_TRUE", "h_secTrk_Pathlength_PION_TRUTH",  Vertex_secondTrkPathway_bins , error_bands);

//PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_tracklength_TRUE("h_secTrk_tracklength_TRUE", "Recoil track length  [cm] ", Recoil_track_length_vector , error_bands);



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


PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_Theta_TRUE_leading_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_leadingvsnonleading_categories, "h_secTrk_Theta_TRUE_leading_Particle", Vertex_secondTrkTheta_bins ,"h_secTrk_Theta_TRUE_leading_Particle; [Deg];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_Theta_TRUE_Nonleading_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_leadingvsnonleading_categories, "h_secTrk_Theta_TRUE_Nonleading_Particle", Vertex_secondTrkTheta_bins ,"h_secTrk_Theta_TRUE_nonleading_Particle; [Deg];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_Theta_TRUE_leadingFULL_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_Theta_TRUE_leadingFULL_Particle", Vertex_secondTrkTheta_bins ,"h_secTrk_Theta_TRUE_leadingFULL_Particle; [Deg];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_Theta_TRUE_NonleadingFULL_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_Theta_TRUE_NonleadingFULL_Particle", Vertex_secondTrkTheta_bins ,"h_secTrk_Theta_TRUE_NonleadingFULL_Particle; [Deg];Events");



PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Energy_TRUE("h_secTrk_Energy_TRUE", "h_secTrk_Energy NEW Method",  Vertex_secondTrkEbins, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_EnergyFINEBinning_TRUE("h_secTrk_EnergyFINEBinning_TRUE", "h_secTrk_Energy NEW Method",  Vertex_secondTrkEbin_Proton_vector, error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_Energy_TRUE_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_Energy_TRUE_Material", Vertex_secondTrkEbins ,"h_secTrk_Energy_TRUE_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_secTrk_Energy_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_secTrk_Energy_TRUE_Interaction", Vertex_secondTrkEbins ,"h_secTrk_Energy_TRUE_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_Energy_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_Energy_TRUE_Particle", Vertex_secondTrkEbins ,"h_secTrk_Energy_TRUE_Particle; [GeV];Events");

/////////////////

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_ALLKE_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_ALLKE_TRUE_Particle", Vertex_secondTrkEbins ,"h_secTrk_ALLKE_TRUE_Particle; [Deg];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_ALLKEFULL_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories ,"h_secTrk_ALLKEFULL_TRUE_Particle", Vertex_secondTrkEbins ,"h_secTrk_ALLKEFULL_TRUE_Particle; [Deg];Events");


PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_KE_TRUE_leading_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_leadingvsnonleading_categories, "h_secTrk_KE_TRUE_leading_Particle", Vertex_secondTrkEbins ,"h_secTrk_KE_TRUE_leading_Particle; [Deg];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_KE_TRUE_Nonleading_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_leadingvsnonleading_categories, "h_secTrk_KE_TRUE_Nonleading_Particle", Vertex_secondTrkEbins ,"h_secTrk_KE_TRUE_nonleading_Particle; [Deg];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_KE_TRUE_leadingFULL_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_KE_TRUE_leadingFULL_Particle", Vertex_secondTrkEbins ,"h_secTrk_KE_TRUE_leadingFULL_Particle; [Deg];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_KE_TRUE_NonleadingFULL_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_KE_TRUE_NonleadingFULL_Particle", Vertex_secondTrkEbins ,"h_secTrk_KE_TRUE_NonleadingFULL_Particle; [Deg];Events");





PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Energy_PION_TRUE("h_secTrk_Energy_PION_TRUE", "h_secTrk_Energy PION (TRUE) ",  Vertex_secondTrkEbin_Proton_vector, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Theta_PION_TRUE("h_secTrk_Theta_PION_TRUE", "h_secTrk_Theta PION(TRUE)",  Vertex_secondTrkTheta_bins , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrkopenangle_PION_TRUE("h_secTrkopenangle_PION_TRUE", "h_secTrkopenangle PION (TRUE)",  Vertex_secondTrkTheta_bins , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Energy_PION0_TRUE("h_secTrk_Energy_PION0_TRUE", "h_secTrk_Energy PION0 (TRUE) ",  Vertex_secondTrkEbin_Proton_vector, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Theta_PION0_TRUE("h_secTrk_Theta_PION0_TRUE", "h_secTrk_Theta PION0(TRUE)",  Vertex_secondTrkTheta_bins , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrkopenangle_PION0_TRUE("h_secTrkopenangle_PION0_TRUE", "h_secTrkopenangle PION0 (TRUE)",  Vertex_secondTrkTheta_bins , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Energy_PION_neg_pos_TRUE("h_secTrk_Energy_PION_neg_pos_TRUE", "h_secTrk_Energy PION_neg_pos (TRUE) ",  Vertex_secondTrkEbin_Proton_vector, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Theta_PION_neg_pos_TRUE("h_secTrk_Theta_PION_neg_pos_TRUE", "h_secTrk_Theta PION_neg_pos(TRUE)",  Vertex_secondTrkTheta_bins , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrkopenangle_PION_neg_pos_TRUE("h_secTrkopenangle_PION_neg_pos_TRUE", "h_secTrkopenangle PION_neg_pos (TRUE)",  Vertex_secondTrkTheta_bins , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_ALLangles_TRUE("h_secTrk_ALLangles_TRUE", "h_secTrk_Theta PION0(TRUE)",  Vertex_secondTrkTheta_bins , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_ALLangles_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_ALLangles_TRUE_Particle", Vertex_secondTrkTheta_bins ,"h_secTrk_ALLangles_TRUE_Particle; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_ALLanglesFULL_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_ALLanglesFULL_TRUE_Particle", Vertex_secondTrkTheta_bins ,"h_secTrk_ALLanglesFULL_TRUE_Particle; [mm];Events");



PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Energy_PROTON_TRUE("h_secTrk_Energy_PROTON_TRUE", "h_secTrk_Energy Proton(TRUE)",  Vertex_secondTrkEbin_Proton_vector, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Theta_PROTON_TRUE("h_secTrk_Theta_PROTON_TRUE", "h_secTrk_Theta Proton(TRUE)",  Vertex_secondTrkTheta_bins , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrkopenangle_PROTON_TRUE("h_secTrkopenangle_PROTON_TRUE", "h_secTrkopenangle Proton(TRUE)",  Vertex_secondTrkTheta_bins , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Energy_Dimuon_TRUE("h_secTrk_Energy_Dimuon_TRUE", "h_secTrk_Energy Dimuon(TRUE)",  Vertex_secondTrkEbin_Proton_vector, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Theta_Dimuon_TRUE("h_secTrk_Theta_Dimuon_TRUE", "h_secTrk_Theta Dimuon(TRUE)",  Vertex_secondTrkTheta_bins , error_bands);



//PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_DOCA("h_secTrk_DOCA", "h_secTrk DOCA NEW Method",  Vertex_secondTrkDOCA_bins , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_DOCA_TRUE("h_secTrk_DOCA_TRUE", "h_secTrk DOCA NEW Method",  Vertex_secondTrkDOCA_bins , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_DOCA_TRUE_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_DOCA_TRUE_Material", Vertex_secondTrkDOCA_bins ,"h_secTrk_DOCA_TRUE_RECO_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_secTrk_DOCA_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_secTrk_DOCA_TRUE_Interaction", Vertex_secondTrkDOCA_bins ,"h_secTrk_DOCA_TRUE_RECO_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_DOCA_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_DOCA_TRUE_Particle", Vertex_secondTrkDOCA_bins ,"h_secTrk_DOCA_TRUE_RECO_Particle; [mm];Events");



PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_Particle_N_A_secTrk_Theta_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_Particle_N_A_secTrk_Theta_TRUE_Interaction", Vertex_secondTrkTheta_bins ,"h_Particle_N_A_secTrk_Theta_TRUE_Interaction; [Degs];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_Particle_OTHER_secTrk_Theta_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_Particle_OTHER_secTrk_Theta_TRUE_Interaction", Vertex_secondTrkTheta_bins ,"h_Particle_OTHER_secTrk_Theta_TRUE_Interaction; [Degs];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_Electron_secTrk_Theta_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_Electron_secTrk_Theta_TRUE_Interaction", Vertex_secondTrkTheta_bins ,"h_Electron_secTrk_Theta_TRUE_Interaction; [Degs];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_Muon_secTrk_Theta_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_Muon_secTrk_Theta_TRUE_Interaction", Vertex_secondTrkTheta_bins ,"h_Muon_secTrk_Theta_TRUE_Interaction; [Degs];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_Gamma_secTrk_Theta_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_Gamma_secTrk_Theta_TRUE_Interaction", Vertex_secondTrkTheta_bins ,"h_Gamma_secTrk_Theta_TRUE_Interaction; [Degs];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_Nu_mu_secTrk_Theta_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_Nu_mu_secTrk_Theta_TRUE_Interaction", Vertex_secondTrkTheta_bins ,"h_Nu_mu_secTrk_Theta_TRUE_Interaction; [Degs];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_Nu_e_secTrk_Theta_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_Nu_e_secTrk_Theta_TRUE_Interaction", Vertex_secondTrkTheta_bins ,"h_Nu_e_secTrk_Theta_TRUE_Interaction; [Degs];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_Anti_nu_secTrk_Theta_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_Anti_Nu_secTrk_Theta_TRUE_Interaction", Vertex_secondTrkTheta_bins ,"h_Anti_Nu_secTrk_Theta_TRUE_Interaction; [Degs];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_Kaon_secTrk_Theta_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_Kaon_secTrk_Theta_TRUE_Interaction", Vertex_secondTrkTheta_bins ,"h_Kaon_secTrk_Theta_TRUE_Interaction; [Degs];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_Pion0_secTrk_Theta_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_Pion0_secTrk_Theta_TRUE_Interaction", Vertex_secondTrkTheta_bins ,"h_Pion0_secTrk_Theta_TRUE_Interaction; [Degs];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_Pion_neg_secTrk_Theta_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_Pion_neg_secTrk_Theta_TRUE_Interaction", Vertex_secondTrkTheta_bins ,"h_Pion_neg_secTrk_Theta_TRUE_Interaction; [Degs];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_Pion_pos_secTrk_Theta_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_Pion_pos_secTrk_Theta_TRUE_Interaction", Vertex_secondTrkTheta_bins ,"h_Pion_pos_secTrk_Theta_TRUE_Interaction; [Degs];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_Proton_secTrk_Theta_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_Proton_secTrk_Theta_TRUE_Interaction", Vertex_secondTrkTheta_bins ,"h_Proton_secTrk_Theta_TRUE_Interaction; [Degs];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_Neutron_secTrk_Theta_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_Neutron_secTrk_Theta_TRUE_Interaction", Vertex_secondTrkTheta_bins ,"h_Neutron_secTrk_Theta_TRUE_Interaction; [Degs];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_4helium_secTrk_Theta_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_4helium_secTrk_Theta_TRUE_Interaction", Vertex_secondTrkTheta_bins ,"h_4helium_secTrk_Theta_TRUE_Interaction; [Degs];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_Lamdba_secTrk_Theta_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_Lamdba_secTrk_Theta_TRUE_Interaction", Vertex_secondTrkTheta_bins ,"h_Lamdba_secTrk_Theta_TRUE_Interaction; [Degs];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_Sigma_plus_secTrk_Theta_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_Sigma_plus_secTrk_Theta_TRUE_Interaction", Vertex_secondTrkTheta_bins ,"h_Sigma_plus_secTrk_Theta_TRUE_Interaction; [Degs];Events");


PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_lost999_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_lost999_Particle", Vertex_secondTrkTheta_bins ,"h_lost999_Particle; [Degs];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_lost999_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_lost999_Interaction", Vertex_secondTrkTheta_bins ,"h_lost999_Interaction; [Degs];Events");

// testing the neutrino Electron type

MnvH1D *h_mc_current_neturino_electron_TRUE           =    new MnvH1D("h_mc_current_neturino_electron_TRUE", "h_mc_current_neturino_electron_TRUE",6,-1.5,4.5 );
MnvH1D *h_mc_incoming_neturino_electron_TRUE           =    new MnvH1D("h_mc_incoming_neturino_electron_TRUE", "h_mc_incoming_neturino_electron_TRUE",37,-18.5,18.5 );

std::vector<double> weight_bins{0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 5.0, 10., 20., 30. , 50.0, 100};
MnvH1D *h_GENIE_MFP_Pi_weight           =    new MnvH1D("h_GENIE_MFP_Pi_weight", "h_GENIE_MFP_Pi_weight",weight_bins.size()-1, weight_bins.data() );





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

  TRUE_Cut_Map Truth_Cut_Map;
  FillingTruthCountingMap(kTRUTHCutsVector, Truth_Cut_Map);

  std::cout << "Truth_Cut_Map.size() = " << Truth_Cut_Map.size()<< std::endl;
  for(const auto & index :Truth_Cut_Map ){
  std::cout<<" Cut Name = " <<GetCutNameTRUTH(index.first).c_str() << " Amount = " << index.second << std::endl;


  }


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



  //double wgt0,wgt1,wgt2,wgt3,wgt4,wgt_total;

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
    if(ii%50000==0) std::cout << (ii/1000) << " k " << std::flush;

    //=========================================
    // For every systematic, loop over the universes, and fill the
    // appropriate histogram in the MnvH1D
    //=========================================


    for ( auto  Universe_GROUP: Error_Band_Universe_GROUPS){

//      std::vector<HeliumCVUniverse*> error_band_universes = band.second;
     Universe_GROUP.front()->SetEntry(ii);
//std::cout<<"Universe_GROUP.front()->GetTRUE_PTmu() = " << Universe_GROUP.front()->GetTRUE_PTmu()<<std::endl;
//   std::cout<<"Out side Truth Cuts "<< std::endl;
   if(PassesCutsTRUTH(*Universe_GROUP.front(), kTRUTHCutsVector, kWeightVector, Truth_Cut_Map)){
// std::cout<<"Inside Truth Cuts "<< std::endl;
//std::cout<<"NEW GROUP "<< std::endl;
      for (auto universe : Universe_GROUP){
        //std::cout<<"universe->ShortName() = " << universe->ShortName()<<std::endl;

        // Tell the Event which entry in the TChain it's looking at
        universe->SetEntry(ii);


        //std::cout<<"universe->ShortName() = " << universe->ShortName()<<std::endl;
        //wgt0 = 1.0;
        //wgt1 = universe->GetWeight(kweightFlux );
        //wgt2 = universe->GetWeight(kweightGenie);
        //wgt3 = universe->GetWeight(kweight2p2ptune );
        //wgt4 = universe->GetWeight(kweightRPA);
        //wgt_total = universe->GetWeight(kWeightVector);
        //std::cout<< "MINSO weight = "<< wgt2<<std::endl;

        //double wgt6 = universe->GetWeight(kweightLowQ2Pi);
        //EventCounter_TRUTH(*universe, kTRUTHCutsVector, EventCounter_weight_0, wgt0);
        //EventCounter_TRUTH(*universe, kTRUTHCutsVector, EventCounter_weight_1, wgt1);
        //EventCounter_TRUTH(*universe, kTRUTHCutsVector, EventCounter_weight_2, wgt2);
        //EventCounter_TRUTH(*universe, kTRUTHCutsVector, EventCounter_weight_3, wgt3);
        //EventCounter_TRUTH(*universe, kTRUTHCutsVector, EventCounter_weight_4, wgt4);
        //EventCounter_TRUTH(*universe, kTRUTHCutsVector, EventCounter_TRUTH_total, wgt_total );





//////////////////////////////////////////////////////////
//// CUTS HAVE BEEN APPLIED
///////////////////////////////////////////////////////////
             double V1weight = universe->GetWeight(kWeightVector);
             std::vector <int> PDG_trklist = universe->GETvector_PDG_FS_particles();
             std::vector <double> Angle_trklist = universe->GETvector_theta_wrtb_FS_particles();

             //std::vector <double> True_track_lenght_minerva = universe->MakeTRUE_VectorTrackLengthinMinerva_cm();
             std::vector <double> Energy_trklist   = universe->GETvector_KE_mc_FS_particles_GeV(pdg_DATABASEobject);

             //std::cout<< "PDG_trklist.size() =  "<< PDG_trklist.size()<<std::endl;
             //std::cout<< "True_track_lenght_minerva.size() =  "<< True_track_lenght_minerva.size()<<std::endl;


              if(PDG_trklist.size()==1){std::cout<<"ERROR"<<std::endl;assert(false);}
              int secondTrk = 999;
              //if(PDG_trklist.size()==0)continue;

              //std::cout<<" inside groups before secondTrk is found "<< std::endl;
              secondTrk = universe->Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_lessthanAngle(PDG_trklist, Energy_trklist, Angle_trklist);
              //secondTrk = universe->Returnindex_True_2ndTk_GreatestKE_lessthanAngle(PDG_trklist, Energy_trklist, Angle_trklist);
              //secondTrk = universe->Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_lessthanAngle_withKE_thresholdonProtonandPion(PDG_trklist, Energy_trklist, Angle_trklist );
              if(secondTrk==-999){
                std::cout<<" secondTrk =  "<< secondTrk<< std::endl;

                std::cout<<" PDG_trklist  "<< PDG_trklist.size()<< std::endl;
                std::cout<<"inside PDG_trklist"<<std::endl;
                for(auto pdg:PDG_trklist){std::cout<<"PrintDG_trklist pdg = "<< pdg<<std::endl; }
                std::cout<<" Energy_trklist  "<< Energy_trklist.size()<< std::endl;
                for(auto energy:Energy_trklist){std::cout<<"PrintDG_trklist Energy_trklist = "<< energy<<std::endl; }

                std::cout<<" Angle_trklist  "<< Angle_trklist.size()<< std::endl;
                for(auto angle:Angle_trklist){std::cout<<"PrintAngle_trklist angle  = "<< angle<<std::endl; }



              }
              int pdg_2ndTrk = PDG_trklist.at(secondTrk);
              double secTrkTrueEnergy = Energy_trklist.at(secondTrk);
              double secTrkTrueAngle = Angle_trklist.at(secondTrk);
              Particle_type Particle_type_Event = GetParticlegroup_type(pdg_2ndTrk);
              Interaction_type Interaction_type_Event =  universe->Get_InteractionStackType();
              Material_type Material_type_Event = universe->Get_MaterialStackType();


              ///////////////////////////////////////////
              ////
              ////  FILL CV
              ////
              ///
              ///////////////////////////////////////////
              if( universe->ShortName() == "GENIE_MFP_pi"){
                //std::cout<<"inside MFP_pi"<<std::endl;
                //std::cout<<"V1weight = "<<V1weight<<std::endl;
                double Genie_wgt = universe->GetWeight(kweightGenie);
                //std::cout<<"Genie_wgt = "<<Genie_wgt<<std::endl;
                h_GENIE_MFP_Pi_weight->Fill(Genie_wgt, V1weight);
                if(Genie_wgt > 10){
                  h_2d_vertexR_Z_MFP_pi_TRUE->Fill(universe->GetTRUE_Vertex_z(),universe->GetTRUE_Vertex_r(),V1weight);
                  h_MuonTheta_MFP_pi_TRUE->Fill(universe->GetTRUE_muANGLE_WRTB_DEG(),V1weight);
                  h_MuonPT_MFP_pi_TRUE->Fill(universe->GetTRUE_PTmu(),V1weight);
                  h_MuonPZ_MFP_pi_TRUE->Fill(universe->GetTRUE_PZmu(),V1weight);
                  h_MuonE_MFP_pi_TRUE->Fill(universe->GetTRUE_Emu(),V1weight);
                }


              }




              if( isCV(*universe)){

              if(secondTrk==-999 || secondTrk==0){
                non_leading_removed++;
                for(unsigned int j = 1; j != PDG_trklist.size(); ++j){
                  Particle_type Particle_999 = GetParticlegroup_type(PDG_trklist.at(j));
                  Interaction_type Interaction_999 =  universe->Get_InteractionStackType();
                  h_lost999_Particle.GetComponentHist(Particle_999)->Fill(Angle_trklist.at(j), V1weight);
                  h_lost999_Interaction.GetComponentHist(Interaction_999)->Fill(Angle_trklist.at(j), V1weight);

                }

                True_Event_info Event_with999{universe->Get_mc_incoming(),
                  universe->Get_mc_current(),
                  universe->GetIntactionType(),
                  universe->GetTargetType(),
                  secondTrk,
                  PDG_trklist,
                  Angle_trklist,
                  Energy_trklist
                };

                secTrk_999_Particle.push_back(Event_with999);
              }

              else{

                //double  secTrkTruetrackLength = True_track_lenght_minerva.at(secondTrk); //std::cout<< "True_track_lenght_minerva.size() =  "<< True_track_lenght_minerva.size()<<std::endl;

              //if(Particle_type_Event ==kProton && secTrkTrueEnergy < .115 ) continue;
              //EventCounter_TRUTH_total[kTRUTH_2ndTrkProtonEnergythreshold]+=wgt_total;
              //if((Particle_type_Event==kPion_neg||Particle_type_Event==kPion_pos) && secTrkTrueEnergy < .75 ) continue;
              //EventCounter_TRUTH_total[kTRUTH_2ndTrkPionEnergythreshold]+=wgt_total;


              for(unsigned int i = 0; i != PDG_trklist.size(); ++i ){
                auto leadinggrounptype = GetParticlegroup_typeProtonandpion_other(PDG_trklist.at(i));
                auto FULLParticle_type_Event = GetParticlegroup_type(PDG_trklist.at(i));

                h_secTrk_ALLangles_TRUE_Particle.GetComponentHist(leadinggrounptype)->Fill(Angle_trklist.at(i), V1weight);
                h_secTrk_ALLanglesFULL_TRUE_Particle.GetComponentHist(FULLParticle_type_Event)->Fill(Angle_trklist.at(i), V1weight);
                h_secTrk_ALLKE_TRUE_Particle.GetComponentHist(leadinggrounptype)->Fill(Energy_trklist.at(i), V1weight);
                h_secTrk_ALLKEFULL_TRUE_Particle.GetComponentHist(FULLParticle_type_Event)->Fill(Energy_trklist.at(i), V1weight);
                h_TracksizeALL_TRUE_Particle.GetComponentHist(FULLParticle_type_Event)->Fill(i, V1weight);

                if(i==secondTrk && i!= 0){
                  non_leading++;
                  h_secTrk_Theta_TRUE_leading_Particle.GetComponentHist(leadinggrounptype)->Fill(Angle_trklist.at(i), V1weight);
                  h_secTrk_Theta_TRUE_leadingFULL_Particle.GetComponentHist(FULLParticle_type_Event)->Fill(Angle_trklist.at(i), V1weight);
                  h_secTrk_KE_TRUE_leading_Particle.GetComponentHist(leadinggrounptype)->Fill(Energy_trklist.at(i), V1weight);
                  h_secTrk_KE_TRUE_leadingFULL_Particle.GetComponentHist(FULLParticle_type_Event)->Fill(Energy_trklist.at(i), V1weight);
                  h_TracksizeALL_leadingTRUE_Particle.GetComponentHist(FULLParticle_type_Event)->Fill(i, V1weight);
                }

                else{
                  h_secTrk_Theta_TRUE_Nonleading_Particle.GetComponentHist(leadinggrounptype)->Fill(Angle_trklist.at(i), V1weight);
                  h_secTrk_Theta_TRUE_NonleadingFULL_Particle.GetComponentHist(FULLParticle_type_Event)->Fill(Angle_trklist.at(i), V1weight);
                  h_secTrk_KE_TRUE_Nonleading_Particle.GetComponentHist(leadinggrounptype)->Fill(Energy_trklist.at(i), V1weight);
                  h_secTrk_KE_TRUE_NonleadingFULL_Particle.GetComponentHist(FULLParticle_type_Event)->Fill(Energy_trklist.at(i), V1weight);
                  h_TracksizeALL_nonleadingTRUE_Particle.GetComponentHist(FULLParticle_type_Event)->Fill(i, V1weight);
                }
              }

              h_MuonE_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetTRUE_Emu(), V1weight);
              h_MuonE_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetTRUE_Emu(), V1weight);
              h_MuonE_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetTRUE_Emu(), V1weight);

              h_MuonPZ_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetTRUE_PZmu(), V1weight);
              h_MuonPZ_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetTRUE_PZmu(), V1weight);
              h_MuonPZ_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetTRUE_PZmu(), V1weight);

              h_MuonPT_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetTRUE_PTmu(), V1weight);
              h_MuonPT_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetTRUE_PTmu(), V1weight);
              h_MuonPT_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetTRUE_PTmu(), V1weight);

              h_MuonTheta_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetTRUE_muANGLE_WRTB_DEG(), V1weight);
              h_MuonTheta_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetTRUE_muANGLE_WRTB_DEG(), V1weight);
              h_MuonTheta_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetTRUE_muANGLE_WRTB_DEG(), V1weight);

              h_MuonPhi_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetTRUE_Phimu(), V1weight);
              h_MuonPhi_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetTRUE_Phimu(), V1weight);
              h_MuonPhi_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetTRUE_Phimu(), V1weight);

              if(secondTrk!= 0){

              h_secTrk_Theta_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(secTrkTrueAngle, V1weight);
              h_secTrk_Theta_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(secTrkTrueAngle, V1weight);
              h_secTrk_Theta_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(secTrkTrueAngle, V1weight);

              h_secTrk_Energy_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetTRUE_NonmuTrkE(secondTrk), V1weight);
              h_secTrk_Energy_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetTRUE_NonmuTrkE(secondTrk), V1weight);
              h_secTrk_Energy_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetTRUE_NonmuTrkE(secondTrk), V1weight);
            //  std::cout<<"whats wrong 10 "<<std::endl;
              h_secTrk_DOCA_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetTRUE_nonMuonDOCA(secondTrk), V1weight);
              h_secTrk_DOCA_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetTRUE_nonMuonDOCA(secondTrk), V1weight);
              h_secTrk_DOCA_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetTRUE_nonMuonDOCA(secondTrk), V1weight);


              h_secTrk_Pathlength_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetTRUE_nonMuoncolumnarDensity(secondTrk), V1weight);
              h_secTrk_Pathlength_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetTRUE_nonMuoncolumnarDensity(secondTrk), V1weight);
              h_secTrk_Pathlength_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetTRUE_nonMuoncolumnarDensity(secondTrk), V1weight);

              h_2d_Theta_2ndTrkE_TRUE->Fill(universe->GetTRUE_muANGLE_WRTB_DEG(),secTrkTrueEnergy,V1weight);
              h_2d_muonE_2ndTrkE_TRUE->Fill(universe->GetTRUE_Emu(),secTrkTrueEnergy,V1weight);
              h_2d_muonPT_2ndTrkE_TRUE->Fill(universe->GetTRUE_PTmu(),secTrkTrueEnergy,V1weight);
              h_2d_muonPZ_2ndTrkE_TRUE->Fill(universe->GetTRUE_PZmu(),secTrkTrueEnergy,V1weight);
              h_2d_Theta_2ndTrKangle_TRUE->Fill(universe->GetTRUE_muANGLE_WRTB_DEG(),secTrkTrueEnergy,V1weight);
              h_2d_muonE_2ndTrkangle_TRUE->Fill(universe->GetTRUE_Emu(),secTrkTrueAngle,V1weight);
              h_2d_muonPT_2ndTrkangle_TRUE->Fill(universe->GetTRUE_PTmu(),secTrkTrueAngle,V1weight);
              h_2d_muonPZ_2ndTrkangle_TRUE->Fill(universe->GetTRUE_PZmu(),secTrkTrueAngle,V1weight);
              h_2d_2ndtrkangle_2ndTrkE_TRUE->Fill(secTrkTrueAngle,secTrkTrueEnergy,V1weight);
              h_2d_2ndtrkPathlength_2ndtrkangle_TRUE->Fill(universe->GetTRUE_nonMuoncolumnarDensity(secondTrk),secTrkTrueAngle,V1weight);
              h_2d_2ndtrkPathlength_2ndTrkE_TRUE->Fill(universe->GetTRUE_nonMuoncolumnarDensity(secondTrk),secTrkTrueEnergy,V1weight);

              if(Particle_type_Event==kSecondary_particle_vector[0]){
                h_2d_2ndtrkangle_2ndTrkE_Proton_TRUE->Fill(secTrkTrueAngle,secTrkTrueEnergy,V1weight);
                h_2d_Theta_2ndTrkE_Proton_TRUE->Fill(universe->GetTRUE_muANGLE_WRTB_DEG(),secTrkTrueEnergy,V1weight);
                h_2d_muonE_2ndTrkE_Proton_TRUE->Fill(universe->GetTRUE_Emu(),secTrkTrueEnergy,V1weight);
                h_2d_muonPT_2ndTrkE_Proton_TRUE->Fill(universe->GetTRUE_PTmu(),secTrkTrueEnergy,V1weight);
                h_2d_muonPZ_2ndTrkE_Proton_TRUE->Fill(universe->GetTRUE_PZmu(),secTrkTrueEnergy,V1weight);
                h_2d_2ndtrkPathlength_2ndtrkangle_Proton_TRUE->Fill(universe->GetTRUE_nonMuoncolumnarDensity(secondTrk),secTrkTrueAngle,V1weight);
                h_2d_2ndtrkPathlength_2ndTrkE_Proton_TRUE->Fill(universe->GetTRUE_nonMuoncolumnarDensity(secondTrk),secTrkTrueEnergy,V1weight);
              }
              if(Particle_type_Event==kSecondary_particle_vector[3]||Particle_type_Event==kSecondary_particle_vector[4]){
                // removed pi) Particle_type_Event==kSecondary_particle_vector[2]||
                h_2d_Theta_2ndTrkE_Pion_TRUE->Fill(universe->GetTRUE_muANGLE_WRTB_DEG(),secTrkTrueEnergy,V1weight);
                h_2d_muonE_2ndTrkE_Pion_TRUE->Fill(universe->GetTRUE_Emu(),secTrkTrueEnergy,V1weight);
                h_2d_muonPT_2ndTrkE_Pion_TRUE->Fill(universe->GetTRUE_PTmu(),secTrkTrueEnergy,V1weight);
                h_2d_muonPZ_2ndTrkE_Pion_TRUE->Fill(universe->GetTRUE_PZmu(),secTrkTrueEnergy,V1weight);
                h_2d_2ndtrkPathlength_2ndtrkangle_Pion_TRUE->Fill(universe->GetTRUE_nonMuoncolumnarDensity(secondTrk),secTrkTrueAngle,V1weight);
                h_2d_2ndtrkangle_2ndTrkE_Pion_TRUE ->Fill(secTrkTrueAngle,secTrkTrueEnergy,V1weight);
                h_2d_2ndtrkPathlength_2ndTrkE_Pion_TRUE->Fill(universe->GetTRUE_nonMuoncolumnarDensity(secondTrk),secTrkTrueEnergy,V1weight);

              }


              if(Particle_type_Event==kSecondary_particle_vector[1]){
                h_2d_2ndtrkangle_2ndTrkE_dimuon_TRUE->Fill(secTrkTrueAngle,secTrkTrueEnergy,V1weight);
              }


              if(Particle_type_Event== kElectron){h_Electron_secTrk_Theta_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(secTrkTrueAngle, V1weight);
                True_Event_info Electron_Event{universe->Get_mc_incoming(),
                  universe->Get_mc_current(),
                  universe->GetIntactionType(),
                  universe->GetTargetType(),
                  secondTrk,
                  PDG_trklist,
                  Angle_trklist,
                  Energy_trklist
                };
                Electron_secTrkParticle.push_back(Electron_Event);
              }

              else if(Particle_type_Event== kPion_0){h_Pion0_secTrk_Theta_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(secTrkTrueAngle, V1weight);}

              else if(Particle_type_Event== kPion_neg){h_Pion_neg_secTrk_Theta_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(secTrkTrueAngle, V1weight);}

              else if(Particle_type_Event== kPion_pos){h_Pion_pos_secTrk_Theta_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(secTrkTrueAngle, V1weight);}

              else if(Particle_type_Event== kKaon){h_Kaon_secTrk_Theta_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(secTrkTrueAngle, V1weight);}

              else if(Particle_type_Event== kProton){h_Proton_secTrk_Theta_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(secTrkTrueAngle, V1weight);}

              else if(Particle_type_Event== kNeutron){h_Neutron_secTrk_Theta_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(secTrkTrueAngle, V1weight);}

              else if(Particle_type_Event== kMuon){h_Muon_secTrk_Theta_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(secTrkTrueAngle, V1weight);}

              else if(Particle_type_Event== kParticle_OTHER){
                h_Particle_OTHER_secTrk_Theta_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(secTrkTrueAngle, V1weight);

                True_Event_info Other_Event{universe->Get_mc_incoming(),
                  universe->Get_mc_current(),
                  universe->GetIntactionType(),
                  universe->GetTargetType(),
                  secondTrk,
                  PDG_trklist,
                  Angle_trklist,
                  Energy_trklist
                };
                Other_secTrkParticle.push_back(Other_Event);



              }

              else if(Particle_type_Event== kGamma){h_Gamma_secTrk_Theta_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(secTrkTrueAngle, V1weight);}

              else if(Particle_type_Event== kNeutrino_muon){

                std::cout<< " NEUTRINO EVENT evevnt = " << ii << std::endl;
                h_Nu_mu_secTrk_Theta_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(secTrkTrueAngle, V1weight);
                True_Event_info Nu_mu_Event{universe->Get_mc_incoming(),
                  universe->Get_mc_current(),
                  universe->GetIntactionType(),
                  universe->GetTargetType(),
                  secondTrk,
                  PDG_trklist,
                  Angle_trklist,
                  Energy_trklist
                };


                auto TRUE_indexs = universe->Get_TRUE_indexs();
                auto ALLID = universe->Get_TRUE_vector_ALL_Event_PDG();
                ALL_True_Event_info Nu_E_Event_All{universe->Get_mc_incoming(),
                  universe->Get_mc_current(),
                  universe->GetIntactionType(),
                  universe->GetTargetType(),
                  secondTrk,
                  TRUE_indexs.at(0), // Mother id
                  TRUE_indexs.at(1), // Fdaugther
                  TRUE_indexs.at(2), // Ldaugther
                  PDG_trklist,
                  Angle_trklist,
                  Energy_trklist,
                  ALLID};


                ALL_EventInfoNu_mu_secTrkParticle.push_back(Nu_E_Event_All);
                Nu_mu_secTrkParticle.push_back(Nu_mu_Event);



              }

              else if(Particle_type_Event== kNeutrino_electron){
                h_Nu_e_secTrk_Theta_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(secTrkTrueAngle, V1weight);
                h_mc_current_neturino_electron_TRUE->Fill(universe->Get_mc_current(), V1weight);
                h_mc_incoming_neturino_electron_TRUE->Fill(universe->Get_mc_incoming(), V1weight);
                True_Event_info Nu_E_Event{universe->Get_mc_incoming(),
                  universe->Get_mc_current(),
                  universe->GetIntactionType(),
                  universe->GetTargetType(),
                  secondTrk,
                  PDG_trklist,
                  Angle_trklist,
                  Energy_trklist
                };

                auto TRUE_indexs = universe->Get_TRUE_indexs();
                auto ALLID = universe->Get_TRUE_vector_ALL_Event_PDG();
                ALL_True_Event_info Nu_E_Event_All{universe->Get_mc_incoming(),
                  universe->Get_mc_current(),
                  universe->GetIntactionType(),
                  universe->GetTargetType(),
                  secondTrk,
                  TRUE_indexs.at(0), // Mother id
                  TRUE_indexs.at(1), // Fdaugther
                  TRUE_indexs.at(2), // Ldaugther
                  PDG_trklist,
                  Angle_trklist,
                  Energy_trklist,
                  ALLID};


                ALL_EventInfoNu_e_secTrkParticle.push_back(Nu_E_Event_All);
                Nu_e_secTrkParticle.push_back(Nu_E_Event);
              }
              else if(Particle_type_Event== kAnti_Neutrino){h_Anti_nu_secTrk_Theta_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(secTrkTrueAngle, V1weight);}

              else if(Particle_type_Event== kParticle_N_A){
                h_Particle_N_A_secTrk_Theta_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(secTrkTrueAngle, V1weight);
                True_Event_info N_A_Event{universe->Get_mc_incoming(),
                  universe->Get_mc_current(),
                  universe->GetIntactionType(),
                  universe->GetTargetType(),
                  secondTrk,
                  PDG_trklist,
                  Angle_trklist,
                  Energy_trklist
                };
                N_A_secTrkParticle.push_back(N_A_Event);
              }

              else if(Particle_type_Event== kFourHelium){h_4helium_secTrk_Theta_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(secTrkTrueAngle, V1weight);

                True_Event_info fourhelium_Event{universe->Get_mc_incoming(),
                  universe->Get_mc_current(),
                  universe->GetIntactionType(),
                  universe->GetTargetType(),
                  secondTrk,
                  PDG_trklist,
                  Angle_trklist,
                  Energy_trklist
                };
                fourHelium_secTrkParticle.push_back(fourhelium_Event);
              }
              else if(Particle_type_Event== kLamdba){h_Lamdba_secTrk_Theta_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(secTrkTrueAngle, V1weight);}
              else if(Particle_type_Event== kSigma_plus){h_Sigma_plus_secTrk_Theta_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(secTrkTrueAngle, V1weight);}



            } // End of Second trk condition

              h_CryoVertex_X_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetTRUE_Vertex_x(), V1weight);
              h_CryoVertex_X_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetTRUE_Vertex_x(), V1weight);
              h_CryoVertex_X_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetTRUE_Vertex_x(), V1weight);

              h_CryoVertex_Y_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetTRUE_Vertex_y(), V1weight);
              h_CryoVertex_Y_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetTRUE_Vertex_y(), V1weight);
              h_CryoVertex_Y_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetTRUE_Vertex_y(), V1weight);

              h_CryoVertex_Z_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetTRUE_Vertex_z(), V1weight);
              h_CryoVertex_Z_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetTRUE_Vertex_z(), V1weight);
              h_CryoVertex_Z_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetTRUE_Vertex_z(), V1weight);

              h_CryoVertex_R_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetTRUE_Vertex_r(), V1weight);
              h_CryoVertex_R_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetTRUE_Vertex_r(), V1weight);
              h_CryoVertex_R_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetTRUE_Vertex_r(), V1weight);

              h_Tracksize_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetTRUE_Tracksize(), V1weight);
              h_Tracksize_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetTRUE_Tracksize(), V1weight);
              h_Tracksize_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetTRUE_Tracksize(), V1weight);


              h_2d_PZ_PT_TRUE->Fill(universe->GetTRUE_PZmu(),universe->GetTRUE_PTmu(),V1weight);
              h_2d_E_PZ_TRUE->Fill(universe->GetTRUE_Emu(),universe->GetTRUE_PZmu(),V1weight);
              h_2d_Theta_PZ_TRUE->Fill(universe->GetTRUE_muANGLE_WRTB_DEG(),universe->GetTRUE_PZmu(),V1weight);
              h_2d_E_PT_TRUE->Fill(universe->GetTRUE_Emu(),universe->GetTRUE_PTmu(),V1weight);
              h_2d_Theta_PT_TRUE->Fill(universe->GetTRUE_muANGLE_WRTB_DEG(),universe->GetTRUE_PTmu(),V1weight);
              h_2d_Theta_PZ_TRUE->Fill(universe->GetTRUE_muANGLE_WRTB_DEG(),universe->GetTRUE_PZmu(),V1weight);
            }// end of else for -999

          }//end of CV



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

/*

          double V1weight = universe->GetWeight(kWeightVector);
         std::vector <int> PDG_trklist = universe->GETvector_PDG_FS_particles();
         std::vector  <double> Angle_trklist = universe->GETvector_theta_wrtb_FS_particles();
         //std::vector <double> True_track_lenght_minerva = universe->MakeTRUE_VectorTrackLengthinMinerva_cm();

          for(auto cat : Angle_trklist){h_secTrk_ALLangles_TRUE.univHist(universe)->Fill(cat,V1weight);
          }
         std::vector <double> Energy_trklist   = universe->GETvector_KE_mc_FS_particles_GeV(pdg_DATABASEobject);


          int secondTrk = 999;
          if(PDG_trklist.size()==0)continue;
          secondTrk = universe->Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_lessthanAngle(PDG_trklist, Energy_trklist, Angle_trklist ) ;
          //secondTrk = universe->Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_lessthanAngle_withKE_thresholdonProtonandPion(PDG_trklist, Energy_trklist, Angle_trklist) ;
          //secondTrk = universe->Returnindex_True_2ndTk_GreatestKE_lessthanAngle(PDG_trklist, Energy_trklist, Angle_trklist);
          if(secondTrk == 0 || secondTrk == -999) continue; // remove 2nd trks that are leading muons
          int pdg_2ndTrk = PDG_trklist.at(secondTrk);
          Particle_type Particle_type_Event = GetParticlegroup_type(pdg_2ndTrk);
          double secTrkTrueEnergy = Energy_trklist.at(secondTrk);
          double secTrkTrueAngle = Angle_trklist.at(secondTrk);
          //double secTrkTruetrackLength = True_track_lenght_minerva.at(secondTrk);
*/



          h_MuonE_TRUE.univHist(universe)->Fill(universe->GetTRUE_Emu(),V1weight);

          h_MuonPZ_TRUE.univHist(universe)->Fill(universe->GetTRUE_PZmu(),V1weight);

          h_MuonPT_TRUE.univHist(universe)->Fill(universe->GetTRUE_PTmu(),V1weight);

          h_MuonTheta_TRUE.univHist(universe)->Fill(universe->GetTRUE_muANGLE_WRTB_DEG(),V1weight);

          h_CryoVertex_X_TRUE.univHist(universe)->Fill(universe->GetTRUE_Vertex_x(),V1weight);

          h_CryoVertex_Y_TRUE.univHist(universe)->Fill(universe->GetTRUE_Vertex_y(),V1weight);

          h_CryoVertex_Z_TRUE.univHist(universe)->Fill(universe->GetTRUE_Vertex_z(),V1weight);

          h_CryoVertex_R_TRUE.univHist(universe)->Fill(universe->GetTRUE_Vertex_r(),V1weight);

          h_Tracksize_TRUE.univHist(universe)->Fill(universe->GetTRUE_Tracksize(),V1weight);


          h_secTrk_DOCA_TRUE.univHist(universe)->Fill(universe->GetTRUE_nonMuonDOCA(secondTrk),V1weight);
          h_secTrk_Pathlength_TRUE.univHist(universe)->Fill(universe->GetTRUE_nonMuoncolumnarDensity(secondTrk),V1weight);
          h_secTrk_Energy_TRUE.univHist(universe)->Fill(secTrkTrueEnergy,V1weight);
          h_secTrk_EnergyFINEBinning_TRUE.univHist(universe)->Fill(secTrkTrueEnergy,V1weight);
          h_secTrk_Theta_TRUE.univHist(universe)->Fill(secTrkTrueAngle,V1weight);
          h_secTrk_Openangle_TRUE.univHist(universe)->Fill(universe->GetTRUE_NonmuTrkopenangle(secondTrk),V1weight);
          //h_secTrk_tracklength_TRUE.univHist(universe)->Fill(secTrkTruetrackLength,V1weight);


          if(Particle_type_Event==kSecondary_particle_vector[0]){
            h_secTrk_Energy_PROTON_TRUE.univHist(universe)->Fill(secTrkTrueEnergy,V1weight);
            h_secTrk_Theta_PROTON_TRUE.univHist(universe)->Fill(secTrkTrueAngle,V1weight);
            h_secTrkopenangle_PROTON_TRUE.univHist(universe)->Fill(universe->GetTRUE_NonmuTrkopenangle(secondTrk),V1weight);
            h_secTrk_Pathlength_PROTON_TRUE.univHist(universe)->Fill(universe->GetTRUE_nonMuoncolumnarDensity(secondTrk),V1weight);

          }
          if(Particle_type_Event==kSecondary_particle_vector[3]||Particle_type_Event==kSecondary_particle_vector[4])
          { // removed Particle_type_Event==kSecondary_particle_vector[2]
            h_secTrk_Energy_PION_TRUE.univHist(universe)->Fill(secTrkTrueEnergy,V1weight);
            h_secTrk_Theta_PION_TRUE.univHist(universe)->Fill(secTrkTrueAngle,V1weight);
            h_secTrkopenangle_PION_TRUE.univHist(universe)->Fill(universe->GetTRUE_NonmuTrkopenangle(secondTrk),V1weight);
            h_secTrk_Pathlength_PION_TRUE.univHist(universe)->Fill(universe->GetTRUE_nonMuoncolumnarDensity(secondTrk),V1weight);

          }

          if(Particle_type_Event==kSecondary_particle_vector[2])
          {
            h_secTrk_Energy_PION0_TRUE.univHist(universe)->Fill(secTrkTrueEnergy,V1weight);
            h_secTrk_Theta_PION0_TRUE.univHist(universe)->Fill(secTrkTrueAngle,V1weight);
            h_secTrkopenangle_PION0_TRUE.univHist(universe)->Fill(universe->GetTRUE_NonmuTrkopenangle(secondTrk),V1weight);
          }
          if(Particle_type_Event==kSecondary_particle_vector[3]||Particle_type_Event==kSecondary_particle_vector[4])
          {
            h_secTrk_Energy_PION_neg_pos_TRUE.univHist(universe)->Fill(secTrkTrueEnergy,V1weight);
            h_secTrk_Theta_PION_neg_pos_TRUE.univHist(universe)->Fill(secTrkTrueAngle,V1weight);
            h_secTrkopenangle_PION_neg_pos_TRUE.univHist(universe)->Fill(universe->GetTRUE_NonmuTrkopenangle(secondTrk),V1weight);
          }

          if(Particle_type_Event==kSecondary_particle_vector[1]){
            h_secTrk_Energy_Dimuon_TRUE.univHist(universe)->Fill(secTrkTrueEnergy,V1weight);
            h_secTrk_Theta_Dimuon_TRUE.univHist(universe)->Fill(secTrkTrueAngle,V1weight);
          }




        } //  End band's individual universe loop

      } ////END OF TRUTH PASS CUTS
    } // End Band Groups loop

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
    h_secTrk_EnergyFINEBinning_TRUE.SyncCVHistos();
    h_secTrk_Theta_TRUE.SyncCVHistos();
    h_secTrk_Openangle_TRUE.SyncCVHistos();
    h_secTrk_Theta_Dimuon_TRUE.SyncCVHistos();
    h_secTrk_Pathlength_TRUE.SyncCVHistos();
    h_secTrk_Pathlength_PROTON_TRUE.SyncCVHistos();
    h_secTrk_Pathlength_PION_TRUE.SyncCVHistos();
    //h_secTrk_tracklength_TRUE.SyncCVHistos();


    h_secTrk_Energy_Dimuon_TRUE.SyncCVHistos();
    h_secTrk_Energy_PROTON_TRUE.SyncCVHistos();
    h_secTrk_Theta_PROTON_TRUE.SyncCVHistos();
    h_secTrkopenangle_PROTON_TRUE.SyncCVHistos();
    h_secTrk_Energy_PION_TRUE.SyncCVHistos();
    h_secTrk_Theta_PION_TRUE.SyncCVHistos();
    h_secTrkopenangle_PION_TRUE.SyncCVHistos();
    h_secTrk_Energy_PION0_TRUE.SyncCVHistos();
    h_secTrk_Theta_PION0_TRUE.SyncCVHistos();
    h_secTrkopenangle_PION0_TRUE.SyncCVHistos();
    h_secTrk_Energy_PION_neg_pos_TRUE.SyncCVHistos();
    h_secTrk_Theta_PION_neg_pos_TRUE.SyncCVHistos();
    h_secTrkopenangle_PION_neg_pos_TRUE.SyncCVHistos();
    h_secTrk_ALLangles_TRUE.SyncCVHistos();
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
  //sprintf(EventRateName, "TRUE_Weight_ALL_Weights_TRUEMC_%s",c);
  //MakeEfficiencyCutCVS(EventCounter_EFF_TRUTH, EventCounter_EFF , kTRUTHCutsVector,c,mcPOT);
//  Make_cvsOfCutsRateTRUE(kTRUTHCutsVector , EventCounter_TRUTH_total, EventRateName, 1.0, 1.0);
/*
  sprintf(EventRateName, "TRUE_Weight_0_noWeight_TRUEMC_%s",c);
   Make_cvsOfCutsRateTRUE( kTRUTHCutsVector , EventCounter_weight_0, EventRateName  ,1.0 ,1.0 );
   sprintf(EventRateName, "TRUE_Weight_1_FLUX_MC_%s",c);
   Make_cvsOfCutsRateTRUE( kTRUTHCutsVector , EventCounter_weight_1, EventRateName  ,1.0 ,1.0);
   sprintf(EventRateName, "TRUE_Weight_2_GeniePion_TRUEMC_%s",c);
   Make_cvsOfCutsRateTRUE( kTRUTHCutsVector , EventCounter_weight_2, EventRateName  ,1.0 ,1.0);
   sprintf(EventRateName, "TRUE_Weight_3_2p2h_TRUEMC_%s",c);
   Make_cvsOfCutsRateTRUE( kTRUTHCutsVector , EventCounter_weight_3, EventRateName  ,1.0 ,1.0);
   sprintf(EventRateName, "TRUE_Weight_4_RPA_TRUEMC_%s",c);
   Make_cvsOfCutsRateTRUE( kTRUTHCutsVector , EventCounter_weight_4, EventRateName  ,1.0 ,1.0);

   sprintf(EventRateName, "TRUE_Weight_ALL_Weights_ENERGYcuts_TRUEMC_%s",c);
   Make_cvsOfCutsRateTRUE( kTRUTHCutsVector_Energy , EventCounter_TRUTH_total, EventRateName  ,1.0 ,1.0);



   MakeLatex_Tables_withTrue_Event_info(Nu_mu_secTrkParticle," ",  "Nu_MuFS", c, .5, "\\nu_{\\mu} in FS");
   MakeLatex_Tables_withTrue_Event_info(Nu_e_secTrkParticle," ",  "Nu_eFS", c, .5, "\\nu_{e} in FS");
   MakeLatex_Tables_withTrue_Event_info(Electron_secTrkParticle," ",  "electron_FS", c, .5, "e in FS");
   MakeLatex_Tables_withTrue_Event_info(Other_secTrkParticle," ",  "Other_FS", c, .5, "Other in FS");
   //MakeLatex_Tables_withTrue_Event_info(fourHelium_secTrkParticle," ",  "FourHelium_FS", c, .5, "4helium in FS");
   MakeLatex_Tables_withTrue_Event_info(N_A_secTrkParticle," ",  "N_A_FS", c, .5, "N_A in FS");
   MakeLatex_Tables_withTrue_Event_info(secTrk_999_Particle," ",  "type999", c, .5, "999 type");

   MakeLatex_Tables_withTrue_includingALL_IDEvent_info(ALL_EventInfoNu_e_secTrkParticle," ",  "ALL_EventInfoNu_e_secTrkParticle", c, .5, "Nu e scattering");
   MakeLatex_Tables_withTrue_includingALL_IDEvent_info(ALL_EventInfoNu_mu_secTrkParticle," ",  "ALL_EventInfoNu_mu_secTrkParticle", c, .5, "Nu Mu scatter");
*/

  //outFileName = "Histograms_test.root";
  //auto outFile = TFile::Open(outFileName);

    TGraph *Truth_Cuts =  Make_TruthCut_Tgraph_fromCutMap("Truth_Cuts", Truth_Cut_Map);


    for(auto cuts: Truth_Cut_Map){
      std::cout<<"Cut Name: " << GetCutNameTRUTH(cuts.first ) <<  " Amount = " << cuts.second << std::endl;


    }

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

    if(Run_EventLoopOnGrid==true){  sprintf(outFileName, "Histograms_%s_%s_%s.root",c,d,sysmatics_status_char);
  }
  else{
    sprintf(outFileName, "%s/Histograms_%s_%s_%s.root",rootpathway,c,d,sysmatics_status_char);
  }

  std::cout << "Writing output file to: " <<outFileName << std::endl;

  //TFile outFile(outFileName, "RECREATE");

  //TFile *outFile(outFileName, "RECREATE");
  TFile *outFile = new TFile(outFileName,"RECREATE");
  TChain POT_branch("Meta");
  POT_branch.Add(RootName.c_str());
  //TTree *oldtree = (TTree*)file->Get("Meta");
  TTree *clone = POT_branch.CloneTree();
  clone->Write();
  Truth_Cuts->Write();
  h_secTrk_DOCA_TRUE.hist->Write();
  h_secTrk_DOCA_TRUE_Material.WriteToFile(*outFile);
  h_secTrk_DOCA_TRUE_Interaction.WriteToFile(*outFile);
  h_secTrk_DOCA_TRUE_Particle.WriteToFile(*outFile);

  h_secTrk_Pathlength_TRUE.hist->Write();
  h_secTrk_Pathlength_TRUE_Material.WriteToFile(*outFile);
  h_secTrk_Pathlength_TRUE_Interaction.WriteToFile(*outFile);
  h_secTrk_Pathlength_TRUE_Particle.WriteToFile(*outFile);

//h_secTrk_tracklength_TRUE.hist->Write();

  h_secTrk_Pathlength_PROTON_TRUE.hist->Write();
  h_secTrk_Pathlength_PION_TRUE.hist->Write();

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
  h_secTrk_EnergyFINEBinning_TRUE.hist->Write();
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

  h_secTrk_Energy_Dimuon_TRUE.hist->Write();
  h_secTrk_Theta_Dimuon_TRUE.hist->Write();
  h_secTrk_Energy_PROTON_TRUE.hist->Write();
  h_secTrk_Theta_PROTON_TRUE.hist->Write();
  h_secTrkopenangle_PROTON_TRUE.hist->Write();
  h_secTrk_Energy_PION_TRUE.hist->Write();
  h_secTrk_Theta_PION_TRUE.hist->Write();
  h_secTrkopenangle_PION_TRUE.hist->Write();

  h_secTrk_Energy_PION0_TRUE.hist->Write();
  h_secTrk_Theta_PION0_TRUE.hist->Write();
  h_secTrkopenangle_PION0_TRUE.hist->Write();

  h_secTrk_Energy_PION_neg_pos_TRUE.hist->Write();
  h_secTrk_Theta_PION_neg_pos_TRUE.hist->Write();
  h_secTrkopenangle_PION_neg_pos_TRUE.hist->Write();

  h_secTrk_ALLangles_TRUE_Particle.WriteToFile(*outFile);
  h_secTrk_ALLanglesFULL_TRUE_Particle.WriteToFile(*outFile);

  h_secTrk_Theta_TRUE_leading_Particle.WriteToFile(*outFile);
  h_secTrk_Theta_TRUE_leadingFULL_Particle.WriteToFile(*outFile);
  h_secTrk_Theta_TRUE_Nonleading_Particle.WriteToFile(*outFile);
  h_secTrk_Theta_TRUE_NonleadingFULL_Particle.WriteToFile(*outFile);

  h_secTrk_KE_TRUE_leading_Particle.WriteToFile(*outFile);
  h_secTrk_KE_TRUE_leadingFULL_Particle.WriteToFile(*outFile);
  h_secTrk_KE_TRUE_Nonleading_Particle.WriteToFile(*outFile);

  h_secTrk_ALLKE_TRUE_Particle.WriteToFile(*outFile);
  h_secTrk_ALLKEFULL_TRUE_Particle.WriteToFile(*outFile);

  h_secTrk_KE_TRUE_NonleadingFULL_Particle.WriteToFile(*outFile);
  h_TracksizeALL_TRUE_Particle.WriteToFile(*outFile);
  h_TracksizeALL_leadingTRUE_Particle.WriteToFile(*outFile);
  h_TracksizeALL_nonleadingTRUE_Particle.WriteToFile(*outFile);

  h_Electron_secTrk_Theta_TRUE_Interaction.WriteToFile(*outFile);
  h_Pion0_secTrk_Theta_TRUE_Interaction.WriteToFile(*outFile);
  h_Pion_neg_secTrk_Theta_TRUE_Interaction.WriteToFile(*outFile);
  h_Pion_pos_secTrk_Theta_TRUE_Interaction.WriteToFile(*outFile);
  h_Kaon_secTrk_Theta_TRUE_Interaction.WriteToFile(*outFile);
  h_Proton_secTrk_Theta_TRUE_Interaction.WriteToFile(*outFile);
  h_Neutron_secTrk_Theta_TRUE_Interaction.WriteToFile(*outFile);
  h_Muon_secTrk_Theta_TRUE_Interaction.WriteToFile(*outFile);
  h_Particle_OTHER_secTrk_Theta_TRUE_Interaction.WriteToFile(*outFile);
  h_Gamma_secTrk_Theta_TRUE_Interaction.WriteToFile(*outFile);
  h_Nu_mu_secTrk_Theta_TRUE_Interaction.WriteToFile(*outFile);
  h_Nu_e_secTrk_Theta_TRUE_Interaction.WriteToFile(*outFile);
  h_Anti_nu_secTrk_Theta_TRUE_Interaction.WriteToFile(*outFile);
  h_Particle_N_A_secTrk_Theta_TRUE_Interaction.WriteToFile(*outFile);
  h_4helium_secTrk_Theta_TRUE_Interaction.WriteToFile(*outFile);
  h_Lamdba_secTrk_Theta_TRUE_Interaction.WriteToFile(*outFile);
  h_Sigma_plus_secTrk_Theta_TRUE_Interaction.WriteToFile(*outFile);
  h_lost999_Particle.WriteToFile(*outFile);
  h_lost999_Interaction.WriteToFile(*outFile);
  h_mc_current_neturino_electron_TRUE->Write();
  h_mc_incoming_neturino_electron_TRUE->Write();

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

  h_2d_Theta_2ndTrkE_Pion_TRUE->Write();
  h_2d_muonE_2ndTrkE_Pion_TRUE->Write();
  h_2d_muonPT_2ndTrkE_Pion_TRUE->Write();
  h_2d_muonPZ_2ndTrkE_Pion_TRUE->Write();

  h_2d_Theta_2ndTrkE_Proton_TRUE->Write();
  h_2d_muonE_2ndTrkE_Proton_TRUE->Write();
  h_2d_muonPT_2ndTrkE_Proton_TRUE->Write();
  h_2d_muonPZ_2ndTrkE_Proton_TRUE->Write();

  h_2d_Theta_2ndTrKangle_TRUE->Write();
  h_2d_muonE_2ndTrkangle_TRUE->Write();
  h_2d_muonPT_2ndTrkangle_TRUE->Write();
  h_2d_muonPZ_2ndTrkangle_TRUE->Write();

  h_2d_2ndtrkangle_2ndTrkE_TRUE->Write();
  h_2d_2ndtrkangle_2ndTrkE_Proton_TRUE->Write();
  h_2d_2ndtrkangle_2ndTrkE_Pion_TRUE->Write();
  h_2d_2ndtrkangle_2ndTrkE_dimuon_TRUE->Write();

  h_2d_2ndtrkPathlength_2ndtrkangle_TRUE->Write();
  h_2d_2ndtrkPathlength_2ndtrkangle_Proton_TRUE->Write();
  h_2d_2ndtrkPathlength_2ndtrkangle_Pion_TRUE->Write();

  h_2d_2ndtrkPathlength_2ndTrkE_TRUE->Write();
  h_2d_2ndtrkPathlength_2ndTrkE_Proton_TRUE->Write();
  h_2d_2ndtrkPathlength_2ndTrkE_Pion_TRUE->Write();

  h_GENIE_MFP_Pi_weight->Write();
  h_2d_vertexR_Z_MFP_pi_TRUE->Write();
  h_MuonTheta_MFP_pi_TRUE->Write();
  h_MuonPT_MFP_pi_TRUE->Write();
  h_MuonPZ_MFP_pi_TRUE->Write();
  h_MuonE_MFP_pi_TRUE->Write();

  outFile->Close();
std::cout<< " the Number of on_leading = "<< non_leading<<std::endl;
std::cout<< " the Number of on_leading_removed = "<< non_leading_removed<<std::endl;




  for(auto band : error_bands){
    std::vector<HeliumCVUniverse*> band_universes = band.second;
    for(unsigned int i_universe = 0; i_universe < band_universes.size(); ++i_universe){ delete band_universes[i_universe];}
  }

  std::cout << "Success in TRUTH LOOP - Gotcha !?!?" << std::endl;

//}

TCanvas *can = new TCanvas("can", "can",1800,1600);
can -> Print("Test.pdf");


}//END of Event Loop

//=========================================
//=========================================
//////////////////////////////////////////////////////////////
std::vector<ECutsTRUTH> GetTRUTHCutsVector() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ECutsTRUTH> True_vec;
  True_vec.push_back(kTRUTHNoCuts  );
  True_vec.push_back(kTRUTHneutrino);
  True_vec.push_back(kTRUTHCCInteraction );
  True_vec.push_back(kTRUTHtarget);
  True_vec.push_back(kTRUTHMuonEnergy );
  True_vec.push_back(kTRUTHMuonAngle );
  True_vec.push_back(kTRUTHFiduical );
  True_vec.push_back(kTRUTH_greaterthanoneFS);
  //True_vec.push_back(kTRUTH_secTrk_Angle_threshold);
  True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold_withProtonanPionThresholds);
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
  True_vec.push_back(kTRUTHtarget);
  True_vec.push_back(kTRUTHMuonEnergy );
  True_vec.push_back(kTRUTHMuonAngle );
  True_vec.push_back(kTRUTHFiduical );
  True_vec.push_back(kTRUTH_greaterthanoneFS);
  //True_vec.push_back(kTRUTH_secTrk_Angle_threshold);
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold_withProtonanPionThresholds);
  True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);
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

  //EMPTY
    //Playlist.push_back(kME1G);
    //Playlist.push_back(kME1A);
    //Playlist.push_back(kME1L);
    //Playlist.push_back(kME1M);
    //Playlist.push_back(kME1N);
  //Full
    //Playlist.push_back(kME1P);

    //Playlist.push_back(kME1C);
    //Playlist.push_back(kME1D);
    //Playlist.push_back(kME1F);
    Playlist.push_back(kME1E);

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
  weight_vec.push_back(kweight_HeliumTargetMass);
  //weight_vec.push_back(kweightLowQ2Pi);

  return weight_vec;
//#endif
}

/*
std::vector<std::vector<HeliumCVUniverse*>> groupCompatibleUniverses(const std::map<std::string, std::vector<HeliumCVUniverse*>> bands)
  {
    std::vector<std::vector<HeliumCVUniverse*>> groupedUnivs;
    std::vector<HeliumCVUniverse*> vertical;
    for(const auto& band: bands)
    {
      if(band.first == "cv") vertical.insert(vertical.begin(), band.second.begin(), band.second.end());
      else
      {
        for(const auto univ: band.second)
        {
          if(univ->IsVerticalOnly()) vertical.push_back(univ);
          else groupedUnivs.push_back(std::vector<HeliumCVUniverse*>{univ});
        }
      }
    }
    groupedUnivs.insert(groupedUnivs.begin(), vertical);
    return groupedUnivs;
  }
*/
//////////////////////////////////////////////////////////////////////////
//GET CryoTank Varibles
//////////////////////////////////////////////////////////////////////////


//////////////////////////
///Main
/////////////////////////
int main(int argc, char* argv[]){


 std::cout << "This is the playlist "<< argv[1] << std::endl;
std::string playlist_string(argv[1]);
ME_helium_Playlists Playlist_to_run = GetPlaylist_FromString(playlist_string);



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

  bool Run_EventLoopOnGrid = false;
  if(Run_EventLoopOnGrid==true){std::cout << "This Eventloop is step up to run on the Grid" << std::endl;}
  else{std::cout << "This Eventloop is step up to run locally" << std::endl;}
  //std::cin >> input_user;
  std::cout << input_user << std::endl;


  runEventLoop(Playlist_to_run, Run_EventLoopOnGrid);
  return 0;
}
//#endif
