// Loop entries, make cuts, fill histograms.
// * Uses the New Systematics Framework and "Universe" objects.
// * loop universes, make cuts and fill histograms with the correct lateral
// shifts and weights for each universe.
// * TChain --> PlotUtils::ChainWrapper.
// * MnvHXD --> PlotUtils::HistWrapper.
// * Genie, flux, non-resonant pion, and some detector systematics calculated.
#include "Helium_runTRUTHLoop_EfficiencyStudy.h"


std::string OUTputRoot_pathway = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles";


//=====================================================
// Functions
//=====================================================
std::vector<ECuts> GetRECOCutsVector();
std::vector<ECutsTRUTH> GetTRUTHCutsVector();
std::vector<ECutsTRUTH> GetTRUTHCutsVector_MuonEnergy();
std::vector<ECutsTRUTH> GetTRUTHCutsVector_MuonEnergy_noFiduical();
std::vector<ECutsTRUTH> GetTRUTHCutsVector_MuonTheta();
std::vector<ECutsTRUTH> GetTRUTHCutsVector_MuonTheta_noFid();
std::vector<ECutsTRUTH> GetTRUTHCutsVector_Fiduical();
std::vector<ECutsTRUTH> GetTRUTHCutsVector_2ndtrkEnergy();
std::vector<ECutsTRUTH> GetTRUTHCutsVector_2ndtrkAngle();
std::vector<ECutsTRUTH> GetTRUTHCutsVector_2ndtrkAngle_Fidiucal();
std::vector<ECutsTRUTH> GetTRUTHCutsVector_2ndtrkEnergy_Fiduical();
std::vector<ECutsTRUTH> GetTRUTHCutsVector_2ndtrkEnergy_2ndtrkAngle();
std::vector<MuonVar> GetMUONVaribles();
std::vector<SecondTrkVar> GetPlayListSecondTrkVector();
std::vector<CryoVertex> GetCryoVertexVaribles();
std::vector<ME_helium_Playlists> GetPlayListVector();
std::vector<Weights> GetWeightVector();
//std::vector<ME_helium_Playlists> GetTRUEPlayListVector();
std::vector<Particle_type>  GetParicle_type();
//std::vector<std::vector<HeliumCVUniverse*>> groupCompatibleUniverses(const std::map<std::string, std::vector<HeliumCVUniverse*>> bands);

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


/*const auto TracksGreaterThan2 = {  NamedCategory<int>({3},   "ThirdTrack"),
                                   NamedCategory<int>({4},   "FourthTrack"),
                                   NamedCategory<int>({5},   "FifthTrack"),
                                   NamedCategory<int>({6},   "SixthTrack"),
                                   NamedCategory<int>({7},   "SevethTrack"),
                                   NamedCategory<int>({8},   "EighthTrack")

                                 };*/


///////////////////////////////////
////// Number of Flux Universe
//////////////////////////////////

const int n_flux_universes = 100;

///////////////////////////////////
///
//////////////////////////////////


std::map< std::string, std::vector<HeliumCVUniverse*> >
  GetErrorBands(PlotUtils::ChainWrapper* chain) {
    typedef std::map< std::string, std::vector<HeliumCVUniverse*> > SystMap;
    //const int n_flux_universes = 50;
    SystMap error_bands;

    //========================================================================
    // CV
    //========================================================================

    error_bands[std::string("cv")].push_back( new HeliumCVUniverse(chain) );

    //Detector systematics, lateral shifts

    if(m_RunCodeWithSystematics==true)
    {
      //========================================================================
      // FLUX
      //========================================================================

      SystMap flux_systematics = PlotUtils::GetFluxSystematicsMap<HeliumCVUniverse>(chain,n_flux_universes);
      error_bands.insert(flux_systematics.begin(), flux_systematics.end());

      //========================================================================
      // GENIE Standards
      //========================================================================

      SystMap genie_systematics = PlotUtils::GetGenieSystematicsMap<HeliumCVUniverse>(chain);
      error_bands.insert(genie_systematics.begin(), genie_systematics.end());

      //========================================================================
      //  MnvTuned - 2p2h
      //========================================================================

      SystMap a2p2h_systematics = PlotUtils::Get2p2hSystematicsMap<HeliumCVUniverse>(chain);
      error_bands.insert(a2p2h_systematics.begin(), a2p2h_systematics.end());

      //========================================================================
      // (RPA)random phase appox , long range Nuclear correlations modeling
      //========================================================================

      SystMap RPA_systematics = PlotUtils::GetRPASystematicsMap<HeliumCVUniverse>(chain);
      error_bands.insert(RPA_systematics.begin(), RPA_systematics.end());

      //========================================================================
      // Helium Mass
      //========================================================================

      SystMap HeliumTargetMass_systematics = GetHeliumTargetMassSystematicsMap<HeliumCVUniverse>(chain);
      error_bands.insert(HeliumTargetMass_systematics.begin(), HeliumTargetMass_systematics.end());

    }


  return error_bands;
}
//======================================================================
//void EventCounter(const HeliumCVUniverse& , std::vector<ECuts> cuts, EventCount_Truth &Event_map ,bool is_mc,HeliumPlayListInfo Info );


// Main
void runEventLoop(ME_helium_Playlists &PlayList_iterator , bool &Run_EventLoopOnGrid) {
  // Make a chain of events
  loadLibs();
double POT[4];
const std::vector<ECutsTRUTH> kTRUTHCutsVector_ALL = GetTRUTHCutsVector();
const std::vector<ECutsTRUTH> kTRUTHCutsVector_Energy = GetTRUTHCutsVector_MuonEnergy();
const std::vector<ECutsTRUTH> kTRUTHCutsVector_Energy_noFid = GetTRUTHCutsVector_MuonEnergy_noFiduical();
const std::vector<ECutsTRUTH> kTRUTHCutsVector_Theta = GetTRUTHCutsVector_MuonTheta();
const std::vector<ECutsTRUTH> kTRUTHCutsVector_Theta_nofid = GetTRUTHCutsVector_MuonTheta_noFid();
const std::vector<ECutsTRUTH> kTRUTHCutsVector_Fiduical = GetTRUTHCutsVector_Fiduical();
const std::vector<ECutsTRUTH> kTRUTHCutsVector_2ndtrkEnergy =  GetTRUTHCutsVector_2ndtrkEnergy();
const std::vector<ECutsTRUTH> kTRUTHCutsVector_2ndtrkAngle  =   GetTRUTHCutsVector_2ndtrkAngle();
const std::vector<ECutsTRUTH> kTRUTHCutsVector_2ndtrkAngle_Fidiucal  =  GetTRUTHCutsVector_2ndtrkAngle_Fidiucal();
const std::vector<ECutsTRUTH> kTRUTHCutsVector_2ndtrkEnergy_Fidiucal  = GetTRUTHCutsVector_2ndtrkEnergy_Fiduical();
const std::vector<ECutsTRUTH> kTRUTHCutsVector_2ndtrkEnergy_2ndTrkAngle  =  GetTRUTHCutsVector_2ndtrkEnergy_2ndtrkAngle();
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
//const std::string RootName = GetPlaylist_ROOT_path("1D_pdgfix",  is_mc );
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
  for(auto true_cut_name:kTRUTHCutsVector_ALL ){
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
//
std::vector<double> MuonThetabin_vector{0.0,1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0,14.0,15.0,16.0,17.0,18.0,19.0,20.0}; //= //GetBinMuonVector(kAngleWRTB);

std::cout<< "size MuonThetabin_vector =  "<< MuonThetabin_vector.size()<<std::endl;
std::vector<double> Muon_curvatureSig_vector= GetBinMuonVector(kcurvatureSig);
std::vector<double> MuonCharge_vector= GetBinMuonVector(kCharge);
std::vector<double> MuonMatchtoMinos_vector= GetBinMuonVector(kMuonMatchtoMinos);
std::vector<double> MuonMatchtoVeto_vector= GetBinMuonVector(kMuonMatchtoVeto);

std::vector<double> Minos_R_vector= GetBinMuonVector(kminos_R);
std::vector<double> AnglePhi_vector = GetBinMuonVector(kAnglePhi);


////////////////////////
std::vector<double> Vertex_Xbins  = GetBinvertexVector(kX);
std::vector<double> Vertex_Ybins  = GetBinvertexVector(kY);
std::vector<double> Vertex_Zbins  = GetBinvertexVector(kZ);
std::vector<double> Vertex_Rbins  = GetBinvertexVector(kR);
std::vector<double> Vertex_RRbins = GetBinvertexVector(kRR_eff);

std::vector<double> Vertex_DOCAbins = GetBinMuonVector(kDOCA_muon);
std::vector<double> Vertex_secondTrkEbins = GetSecondTrkVarVector(ksecE); //GetSecondTrkVarVector(ksecE);,ksecE_Proton
std::vector<double> Vertex_secondTrkEbin_Proton_vector= GetSecondTrkVarVector(ksecE_Proton);
//std::sort(Vertex_secondTrkEbin_Proton_vector.begin(),Vertex_secondTrkEbin_Proton_vector.end());
std::vector<double> Vertex_secondTrkTheta_bins= GetSecondTrkVarVector(kThetamid);//GetSecondTrkVarVector(kFullAngle);

std::vector<double> Vertex_secondTrkTheta_Coarse_bins{0 ,2 ,4 ,6 ,8 ,10 ,12 ,14 ,16 ,18 ,20 ,22 ,24 ,26 ,28 ,30 ,32 ,34 ,36 ,38 ,40 ,42 ,44 ,46 ,48 ,50 ,52 ,54 ,56 ,58 ,60 ,62};


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


PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_TRUE("h_CryoVertex_R_TRUE", "h_CryoVertex_R_TRUE",  Vertex_Rbins , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_RR_TRUE("h_CryoVertex_RR_TRUE", "h_CryoVertex_RR_TRUE",  Vertex_RRbins , error_bands);


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


PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Pathlength_TRUE("h_secTrk_Pathlength_TRUE", "h_secTrk Pathlength ",  Vertex_secondTrkPathway_bins , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Pathlength_PROTON_TRUE("h_secTrk_Pathlength_PROTON_TRUE", "h_secTrk_Pathlength_PROTON_TRUTH",  Vertex_secondTrkPathway_bins , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Pathlength_PION_TRUE("h_secTrk_Pathlength_PION_TRUE", "h_secTrk_Pathlength_PION_TRUTH",  Vertex_secondTrkPathway_bins , error_bands);


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


PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Energy_PROTON_TRUE("h_secTrk_Energy_PROTON_TRUE", "h_secTrk_Energy Proton(TRUE)",  Vertex_secondTrkEbin_Proton_vector, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Theta_PROTON_TRUE("h_secTrk_Theta_PROTON_TRUE", "h_secTrk_Theta Proton(TRUE)",  Vertex_secondTrkTheta_bins , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrkopenangle_PROTON_TRUE("h_secTrkopenangle_PROTON_TRUE", "h_secTrkopenangle Proton(TRUE)",  Vertex_secondTrkTheta_bins , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Energy_Dimuon_TRUE("h_secTrk_Energy_Dimuon_TRUE", "h_secTrk_Energy Dimuon(TRUE)",  Vertex_secondTrkEbin_Proton_vector, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Theta_Dimuon_TRUE("h_secTrk_Theta_Dimuon_TRUE", "h_secTrk_Theta Dimuon(TRUE)",  Vertex_secondTrkTheta_bins , error_bands);



//PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_DOCA("h_secTrk_DOCA", "h_secTrk DOCA NEW Method",  Vertex_secondTrkDOCA_bins , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_DOCA_TRUE("h_secTrk_DOCA_TRUE", "h_secTrk DOCA NEW Method",  Vertex_secondTrkDOCA_bins , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_DOCA_TRUE_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_DOCA_TRUE_Material", Vertex_secondTrkDOCA_bins ,"h_secTrk_DOCA_TRUE_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_secTrk_DOCA_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_secTrk_DOCA_TRUE_Interaction", Vertex_secondTrkDOCA_bins ,"h_secTrk_DOCA_TRUE_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_DOCA_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_DOCA_TRUE_Particle", Vertex_secondTrkDOCA_bins ,"h_secTrk_DOCA_TRUE_Particle; [mm];Events");


//PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_tracklength_TRUE("h_secTrk_tracklength_TRUE", "Recoil track length  [cm] ", Recoil_track_length_vector , error_bands);


///////////
///2D
///////////

//PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_secTrkTheta_cryoVertex_Z_TRUE("h_secTrkTheta_cryoVertex_Z_TRUE", "h_secTrkTheta_cryoVertex_Z_TRUE",Vertex_Zbins, Vertex_secondTrkTheta_bins, error_bands);
//PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_secTrkTheta_cryoVertex_R_TRUE("h_secTrkTheta_cryoVertex_R_TRUE", "h_secTrkTheta_cryoVertex_R_TRUE",Vertex_Rbins, Vertex_secondTrkTheta_bins,  error_bands);

MnvH2D *h_cryoVertex_Z_secTrkTheta_TRUE        =    new MnvH2D("h_cryoVertex_Z_secTrkTheta_TRUE", "h_cryoVertex_Z_secTrkTheta_TRUE",  Vertex_Zbins.size()-1,  Vertex_Zbins.data(), Vertex_secondTrkTheta_Coarse_bins.size()-1, Vertex_secondTrkTheta_Coarse_bins.data()  );
MnvH2D *h_cryoVertex_R_secTrkTheta_TRUE        =    new MnvH2D("h_cryoVertex_R_secTrkTheta_TRUE", "h_cryoVertex_R_secTrkTheta_TRUE",  Vertex_Rbins.size()-1,  Vertex_Rbins.data(), Vertex_secondTrkTheta_Coarse_bins.size()-1, Vertex_secondTrkTheta_Coarse_bins.data()  );
MnvH2D *h_cryoVertex_Z_R_TRUE                  =    new MnvH2D("h_cryoVertex_Z_R_TRUE", "h_cryoVertex_Z_R_TRUE", Vertex_Zbins.size()-1,  Vertex_Zbins.data(),  Vertex_Rbins.size()-1,  Vertex_Rbins.data()  );


MnvH2D *h_muonPT_2ndTrkangle_TRUE         =    new MnvH2D("h_muonPT_2ndTrkangle_TRUE", "h_muonPT_2ndTrkangle_TRUE",  PTbin_vector.size()-1,  PTbin_vector.data(),                     Vertex_secondTrkTheta_Coarse_bins.size()-1, Vertex_secondTrkTheta_Coarse_bins.data()  );
MnvH2D *h_muonPZ_2ndTrkangle_TRUE         =    new MnvH2D("h_muonPZ_2ndTrkangle_TRUE", "h_muonPZ_2ndTrkangle_TRUE",  Pzbin_vector.size()-1,  Pzbin_vector.data(),                     Vertex_secondTrkTheta_Coarse_bins.size()-1, Vertex_secondTrkTheta_Coarse_bins.data()  );
MnvH2D *h_muontheta_2ndTrkangle_TRUE      =    new MnvH2D("h_muontheta_2ndTrkangle_TRUE", "h_muontheta_2ndTrkangle_TRUE",  MuonThetabin_vector.size()-1,  MuonThetabin_vector.data(), Vertex_secondTrkTheta_Coarse_bins.size()-1, Vertex_secondTrkTheta_Coarse_bins.data()  );
//MnvH2D *h_2ndtrkPathlength_2ndTrkE_TRUE    =    new MnvH2D("h_2ndtrkPathlength_2ndTrkE_TRUE", "h_2ndtrkPathlength_2ndTrkE_TRUE", Vertex_secondTrkPathway_bins.size()-1, Vertex_secondTrkPathway_bins.data(), Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );

MnvH2D *h_2ndTrkE_2ndtrkangle_TRUE         =    new MnvH2D("h_2ndTrkE_2ndtrkangle_TRUE",        "h_2ndTrkE_2ndtrkangle_TRUE",        Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data(), Vertex_secondTrkTheta_Coarse_bins.size()-1, Vertex_secondTrkTheta_Coarse_bins.data()  );
MnvH2D *h_2ndTrkE_2ndtrkangle_Proton_TRUE  =    new MnvH2D("h_2ndTrkE_2ndtrkangle_Proton_TRUE", "h_2ndTrkE_2ndtrkangle_Proton_TRUE", Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data(), Vertex_secondTrkTheta_Coarse_bins.size()-1, Vertex_secondTrkTheta_Coarse_bins.data()  );
MnvH2D *h_2ndTrkE_2ndtrkangle_Pion_TRUE    =    new MnvH2D("h_2ndTrkE_2ndtrkangle_Pion_TRUE",   "h_2ndTrkE_2ndtrkangle_Pion_TRUE",   Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data(), Vertex_secondTrkTheta_Coarse_bins.size()-1, Vertex_secondTrkTheta_Coarse_bins.data()  );
///////

MnvH2D *h_cryoVertex_Z_Pathlength_TRUE        =    new MnvH2D("h_cryoVertex_Z_Pathlength_TRUE", "h_cryoVertex_Z_Pathlength_TRUE",  Vertex_Zbins.size()-1,  Vertex_Zbins.data(), Vertex_secondTrkPathway_bins.size()-1, Vertex_secondTrkPathway_bins.data()  );
MnvH2D *h_cryoVertex_R_Pathlength_TRUE        =    new MnvH2D("h_cryoVertex_R_Pathlength_TRUE", "h_cryoVertex_R_Pathlength_TRUE",  Vertex_Rbins.size()-1,  Vertex_Rbins.data(), Vertex_secondTrkPathway_bins.size()-1, Vertex_secondTrkPathway_bins.data()  );

MnvH2D *h_cryoVertex_Z_DOCA_TRUE        =    new MnvH2D("h_cryoVertex_Z_DOCA_TRUE", "h_cryoVertex_Z_DOCA_TRUE",  Vertex_Zbins.size()-1,  Vertex_Zbins.data(), Vertex_secondTrkDOCA_bins.size()-1, Vertex_secondTrkDOCA_bins.data()  );
MnvH2D *h_cryoVertex_R_DOCA_TRUE        =    new MnvH2D("h_cryoVertex_R_DOCA_TRUE", "h_cryoVertex_R_DOCA_TRUE",  Vertex_Rbins.size()-1,  Vertex_Rbins.data(), Vertex_secondTrkDOCA_bins.size()-1, Vertex_secondTrkDOCA_bins.data()  );

MnvH2D *h_cryoVertex_Z_2ndTrkE_TRUE        =    new MnvH2D("h_cryoVertex_Z_2ndTrkE_TRUE", "h_cryoVertex_Z_2ndTrkE_TRUE",  Vertex_Zbins.size()-1,  Vertex_Zbins.data(), Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );
MnvH2D *h_cryoVertex_R_2ndTrkE_TRUE        =    new MnvH2D("h_cryoVertex_R_2ndTrkE_TRUE", "h_cryoVertex_R_2ndTrkE_TRUE",  Vertex_Rbins.size()-1,  Vertex_Rbins.data(), Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );
std::vector<double> Distance_to_innerTank = GetBinvertexVector(kdistance_edge);

MnvH2D *h_distanceEdge_cryoVertex_R_TRUE  =    new MnvH2D("h_distanceEdge_cryoVertex_R_TRUE", "h_distanceEdge_cryoVertex_R_TRUE",Distance_to_innerTank.size()-1, Distance_to_innerTank.data(),  Vertex_Rbins.size()-1,  Vertex_Rbins.data()  );
MnvH2D *h_distanceEdge_cryoVertex_Z_TRUE  =    new MnvH2D("h_distanceEdge_cryoVertex_Z_TRUE", "h_distanceEdge_cryoVertex_Z_TRUE",Distance_to_innerTank.size()-1, Distance_to_innerTank.data(),  Vertex_Zbins.size()-1,  Vertex_Zbins.data()  );
MnvH2D *h_distanceEdge_DOCA_TRUE          =    new MnvH2D("h_distanceEdge_DOCA_TRUE",         "h_distanceEdge_DOCA_TRUE",        Distance_to_innerTank.size()-1, Distance_to_innerTank.data(),  Vertex_secondTrkDOCA_bins.size()-1,  Vertex_secondTrkDOCA_bins.data()  );
MnvH2D *h_distanceEdge_2ndTrkE_TRUE       =    new MnvH2D("h_distanceEdge_2ndTrkE_TRUE",      "h_distanceEdge_2ndTrkE_TRUE",     Distance_to_innerTank.size()-1, Distance_to_innerTank.data(),  Vertex_secondTrkEbins.size()-1,  Vertex_secondTrkEbins.data()  );
MnvH2D *h_distanceEdge_Pathlength_TRUE    =    new MnvH2D("h_distanceEdge_Pathlength_TRUE",   "h_distanceEdge_Pathlength_TRUE",  Distance_to_innerTank.size()-1, Distance_to_innerTank.data(),  Vertex_secondTrkPathway_bins.size()-1,  Vertex_secondTrkPathway_bins.data()  );
MnvH2D *h_distanceEdge_2ndTrkAngle_TRUE   =    new MnvH2D("h_distanceEdge_2ndTrkAngle_TRUE",  "h_distanceEdge_2ndTrkAngle_TRUE", Distance_to_innerTank.size()-1, Distance_to_innerTank.data(),  Vertex_secondTrkTheta_Coarse_bins.size()-1,  Vertex_secondTrkTheta_Coarse_bins.data()  );
MnvH2D *h_distanceEdge_MuonPT_TRUE        =    new MnvH2D("h_distanceEdge_MuonPT_TRUE",       "h_distanceEdge_MuonPT_TRUE",      Distance_to_innerTank.size()-1, Distance_to_innerTank.data(),  PTbin_vector.size()-1,  PTbin_vector.data()  );
MnvH2D *h_distanceEdge_MuonPZ_TRUE        =    new MnvH2D("h_distanceEdge_MuonPZ_TRUE",       "h_distanceEdge_MuonPZ_TRUE",      Distance_to_innerTank.size()-1, Distance_to_innerTank.data(),  Pzbin_vector.size()-1,  Pzbin_vector.data()  );
MnvH2D *h_distanceEdge_Muontheta_TRUE     =    new MnvH2D("h_distanceEdge_Muontheta_TRUE",    "h_distanceEdge_Muontheta_TRUE",   Distance_to_innerTank.size()-1, Distance_to_innerTank.data(),  MuonThetabin_vector.size()-1,  MuonThetabin_vector.data()  );
//std::vector<double> CutToSurface_bins{-350,-300,-290,-280,-270,-260,-250,-240,-230,-220,-210,-200,-190,-180,-170,-160,-150,-140,-130,-120,-110,-100,-90,-80,-70,-60,-50,-40,-30,-20,-10,0.0,20,30,40,50,60,70,80,90,100,110,120,130,140,150};
//std::vector<double> CutToSurface_bins{-400, -380, -360, -340, -320, -300, -280, -260, -240, -220, -200, -180, -160, -140, -120, -100, -80, -60, -40, -20, 0, 20, 40, 60, 80, 100, 120};


std::vector<double> CutToSurface_bins_finner = GetBinvertexVector(kdistance_edge);// {-400, -390, -380, -370, -360, -350, -340, -330, -320, -310, -300, -290, -280, -270, -260, -250, -240, -230, -220, -210, -200, -190, -180, -170, -160, -150, -140, -130, -120, -110, -100, -90, -80, -70, -60, -50, -40, -30, -20, -10, 0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120};
MnvH2D *h_FidiucalCut_cryoVertex_R_TRUE         =    new MnvH2D("h_FidiucalCut_cryoVertex_R_TRUE", "h_FidiucalCut_cryoVertex_R_TRUE",  CutToSurface_bins_finner.size()-1,  CutToSurface_bins_finner.data(), Vertex_Rbins.size()-1, Vertex_Rbins.data()  );
MnvH2D *h_FidiucalCut_cryoVertex_Z_TRUE         =    new MnvH2D("h_FidiucalCut_cryoVertex_Z_TRUE", "h_FidiucalCut_cryoVertex_Z_TRUE",  CutToSurface_bins_finner.size()-1,  CutToSurface_bins_finner.data(), Vertex_Zbins.size()-1, Vertex_Zbins.data()  );
PlotUtils::HistWrapper<HeliumCVUniverse> h_FidiucalCut_TRUE("h_FidiucalCut_TRUE", "h_FidiucalCut_TRUE",  CutToSurface_bins_finner, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_InnerTank_TRUE("h_Distance_to_InnerTank_TRUE", "h_Distance_to_InnerTank_TRUE",  Distance_to_innerTank, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_InnerTank_upstreamCap_TRUE("h_Distance_to_InnerTank_upstreamCap_TRUE", "h_Distance_to_InnerTank_upstreamCap_TRUE",  Distance_to_innerTank, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_InnerTank_barrel_TRUE("h_Distance_to_InnerTank_barrel_TRUE", "h_Distance_to_InnerTank_barrel_TRUE",  Distance_to_innerTank, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_InnerTank_downstreamCap_TRUE("h_Distance_to_InnerTank_downstreamCap_TRUE", "h_Distance_to_InnerTank_downstreamCap_TRUE",  Distance_to_innerTank, error_bands);


  //=========================================
  // Entry Loop For MC
  //=========================================

  //std::vector<ECuts> kTRUTHCutsVector;


  bool is_counter = true;

  //EventCount_Truth EventCounter_EFF;
  //EventCount_RECO EventCounter_EFF_TRUTH;
  EventCount_Truth EventCounter_TRUTH_total;

  TRUE_Cut_Map Truth_Cut_Map;
  TRUE_Cut_Map Truth_Cut_Map_Energy;
  TRUE_Cut_Map Truth_Cut_Map_Theta;
  TRUE_Cut_Map Truth_Cut_Map_Fiduical;
  TRUE_Cut_Map Truth_Cut_Map_2ndTrkEnergy;
  TRUE_Cut_Map Truth_Cut_Map_2ndTrkAngle;
  TRUE_Cut_Map Truth_Cut_Map_2ndTrkAngle_Fiduical;
  FillingTruthCountingMap(kTRUTHCutsVector_ALL, Truth_Cut_Map);
  FillingTruthCountingMap(kTRUTHCutsVector_Energy, Truth_Cut_Map_Energy);
  FillingTruthCountingMap(kTRUTHCutsVector_Theta, Truth_Cut_Map_Theta);
  FillingTruthCountingMap(kTRUTHCutsVector_Fiduical, Truth_Cut_Map_Fiduical);
  FillingTruthCountingMap(kTRUTHCutsVector_2ndtrkEnergy, Truth_Cut_Map_2ndTrkEnergy);
  FillingTruthCountingMap(kTRUTHCutsVector_2ndtrkAngle,  Truth_Cut_Map_2ndTrkAngle);

  std::cout << "Truth_Cut_Map.size() = " << Truth_Cut_Map.size()<< std::endl;
  for(const auto & index :Truth_Cut_Map ){
  std::cout<<" Cut Name = " <<GetCutNameTRUTH(index.first).c_str() << " Amount = " << index.second << std::endl;

  }


  int counter_test=20;
  int kk=0;
  //int non_leading_removed=0;
  //int non_leading=0;



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
  if(ii==0)std::cout<<"First Entrie Started"<<std::endl;
  if(ii%50000==0) std::cout << (ii/1000) << " k " << std::flush;

  //=========================================
  // For every systematic, loop over the universes, and fill the
  // appropriate histogram in the MnvH1D
  //=========================================


  for ( auto  Universe_GROUP: Error_Band_Universe_GROUPS){
  Universe_GROUP.front()->SetEntry(ii);


  //////////////////////////////////////////////////////////////////////////
  //                    Applying Truth Cuts
  //////////////////////////////////////////////////////////////////////////


  if(PassesCutsTRUTH(*Universe_GROUP.front(), kTRUTHCutsVector_Energy, kWeightVector, Truth_Cut_Map_Energy)){

    double Emu = Universe_GROUP.front()->GetTRUE_Emu();
    double muPT =  Universe_GROUP.front()->GetTRUE_PTmu();
    double muPZ =  Universe_GROUP.front()->GetTRUE_PZmu();

    for (auto universe : Universe_GROUP){

      universe->SetEntry(ii);

      double wgt_mvnV1 = universe->GetWeight(kWeightVector);

      h_MuonE_TRUE.univHist(universe)->Fill(Emu,wgt_mvnV1);

      h_MuonPZ_TRUE.univHist(universe)->Fill(muPZ,wgt_mvnV1);

      h_MuonPT_TRUE.univHist(universe)->Fill(muPT,wgt_mvnV1);

    } // end of Universes
  }// End of Truth Cuts


  //////////////////////////////////////////////////////////////////////////
  //                    Applying Truth Cuts
  //////////////////////////////////////////////////////////////////////////

if(PassesCutsTRUTH(*Universe_GROUP.front(), kTRUTHCutsVector_Energy_noFid, kWeightVector, Truth_Cut_Map_Energy)){

  double muPT =  Universe_GROUP.front()->GetTRUE_PTmu();
  double muPZ =  Universe_GROUP.front()->GetTRUE_PZmu();

  for (auto universe : Universe_GROUP){

    universe->SetEntry(ii);

    double wgt_mvnV1 = universe->GetWeight(kWeightVector);
    double True_distance = TRUE_Distance_to_innerTank(*universe);

    h_distanceEdge_MuonPT_TRUE->Fill(True_distance,universe->GetPmuTransverseTrue(),wgt_mvnV1);
    h_distanceEdge_MuonPZ_TRUE ->Fill(True_distance, universe->GetPmuLongitudinalTrue() ,wgt_mvnV1);

  } // end of Universes
}// End of Truth Cuts


//////////////////////////////////////////////////////////////////////////
//                    Applying Truth Cuts
//////////////////////////////////////////////////////////////////////////

if(PassesCutsTRUTH(*Universe_GROUP.front(), kTRUTHCutsVector_Theta, kWeightVector, Truth_Cut_Map_Theta)){

  double muTheta =Universe_GROUP.front()->GetTRUE_muANGLE_WRTB_DEG() ;

  for (auto universe : Universe_GROUP){
    universe->SetEntry(ii);
    double wgt_mvnV1 = universe->GetWeight(kWeightVector);

    h_MuonTheta_TRUE.univHist(universe)->Fill(muTheta, wgt_mvnV1);

    ///////////
    /// Fill CV
    //////////
    if(isCV(*universe)){
      std::vector <double> Angle_trklist = universe->GETvector_theta_wrtb_FS_particles();
      std::vector <int> PDG_trklist = universe->GETvector_PDG_FS_particles();
      std::vector <double> Energy_trklist   = universe->GETvector_KE_mc_FS_particles_GeV(pdg_DATABASEobject);
      int secondTrk = universe->Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE(PDG_trklist, Energy_trklist);

      h_muontheta_2ndTrkangle_TRUE->Fill(universe->GetTRUE_muANGLE_WRTB_DEG(), Angle_trklist.at(secondTrk ),wgt_mvnV1);
    } // end of CV

    ///////////
    /// End CV
    //////////
  } // end of Universes
}// End of Truth Cuts


//////////////////////////////////////////////////////////////////////////
//                    Applying Truth Cuts
//////////////////////////////////////////////////////////////////////////

if(PassesCutsTRUTH(*Universe_GROUP.front(), kTRUTHCutsVector_Theta_nofid, kWeightVector, Truth_Cut_Map_Theta)){

  for (auto universe : Universe_GROUP){
    universe->SetEntry(ii);
    double wgt_mvnV1 = universe->GetWeight(kWeightVector);


    if(isCV(*universe)){
      h_distanceEdge_Muontheta_TRUE->Fill(TRUE_Distance_to_innerTank(*universe), universe->GetTRUE_muANGLE_WRTB_DEG(),wgt_mvnV1);
    } // end of CV

    ///////////
    /// End CV
    //////////
  } // end of Universes
}// End of Truth Cuts


//////////////////////////////////////////////////////////////////////////
//                    Applying Truth Cuts
//////////////////////////////////////////////////////////////////////////

if(PassesCutsTRUTH(*Universe_GROUP.front(), kTRUTHCutsVector_Fiduical, kWeightVector, Truth_Cut_Map_Fiduical)){

  double VertexX = Universe_GROUP.front()->GetTRUE_Vertex_x();
  double VertexY = Universe_GROUP.front()->GetTRUE_Vertex_y();
  double VertexZ = Universe_GROUP.front()->GetTRUE_Vertex_z();
  double VertexR = Universe_GROUP.front()->GetTRUE_Vertex_r();
  double VertexRR = Universe_GROUP.front()->GetTRUE_Vertex_rr();

  double True_distance = TRUE_Distance_to_innerTank(*Universe_GROUP.front());
  CryoTank_REGIONS RegionType= Region_of_CryoTank(VertexZ);

  for (auto universe : Universe_GROUP){

    universe->SetEntry(ii);
    double wgt_mvnV1 = universe->GetWeight(kWeightVector);

    h_CryoVertex_X_TRUE.univHist(universe)->Fill(VertexX ,wgt_mvnV1);

    h_CryoVertex_Y_TRUE.univHist(universe)->Fill(VertexY,wgt_mvnV1);

    h_CryoVertex_Z_TRUE.univHist(universe)->Fill(VertexZ,wgt_mvnV1);

    h_CryoVertex_R_TRUE.univHist(universe)->Fill(VertexR,wgt_mvnV1);

    h_CryoVertex_RR_TRUE.univHist(universe)->Fill(VertexRR,wgt_mvnV1);

    h_Distance_to_InnerTank_TRUE.univHist(universe)->Fill(True_distance,wgt_mvnV1);

    if(RegionType==kUpstream_head){
      h_Distance_to_InnerTank_upstreamCap_TRUE.univHist(universe)->Fill(True_distance, wgt_mvnV1);
    }

    else if(RegionType==kCenter){
      h_Distance_to_InnerTank_barrel_TRUE.univHist(universe)->Fill(True_distance, wgt_mvnV1);
    }

    else if(RegionType==kDownstream_head){
      h_Distance_to_InnerTank_downstreamCap_TRUE.univHist(universe)->Fill(True_distance, wgt_mvnV1);
    }

///////////
/// Fill CV
//////////
for(auto Fid_Cut:CutToSurface_bins_finner ){
  //old if(IsInExtraFiduicalVolume_Non_seperated_Cryo_regions_TRUTH(*universe, Fid_Cut)){
  if(IsInFiducalVolumeFromtheInnerEdgeTRUTH_new(*universe, Fid_Cut)){
    h_FidiucalCut_TRUE.univHist(universe)->Fill(Fid_Cut, wgt_mvnV1);
  }
}


if(isCV(*universe)){
  std::vector <double> Angle_trklist = universe->GETvector_theta_wrtb_FS_particles();
  std::vector <int> PDG_trklist = universe->GETvector_PDG_FS_particles();
  std::vector <double> Energy_trklist   = universe->GETvector_KE_mc_FS_particles_GeV(pdg_DATABASEobject);


  int secondTrk = universe->Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_lessthanAngle(PDG_trklist, Energy_trklist, Angle_trklist);


  Particle_type Particle_type_Event = GetParticlegroup_type(PDG_trklist.at(secondTrk));
  Interaction_type Interaction_type_Event =  universe->Get_InteractionStackType();
  Material_type Material_type_Event = universe->Get_MaterialStackType();
  double True_distance = TRUE_Distance_to_innerTank(*universe);

  h_cryoVertex_Z_R_TRUE->Fill(VertexZ, VertexR, wgt_mvnV1);

  h_distanceEdge_cryoVertex_R_TRUE->Fill(True_distance, VertexR,wgt_mvnV1);
  h_distanceEdge_cryoVertex_Z_TRUE->Fill(True_distance, VertexZ,wgt_mvnV1);
  h_distanceEdge_DOCA_TRUE->Fill(True_distance, universe->GetTRUE_nonMuonDOCA(secondTrk),wgt_mvnV1);
  h_distanceEdge_Pathlength_TRUE->Fill(True_distance, universe->GetTRUE_nonMuoncolumnarDensity(secondTrk),wgt_mvnV1);

  h_CryoVertex_X_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(VertexX , wgt_mvnV1);
  h_CryoVertex_X_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(VertexX , wgt_mvnV1);
  h_CryoVertex_X_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(VertexX , wgt_mvnV1);

  h_CryoVertex_Y_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(VertexY, wgt_mvnV1);
  h_CryoVertex_Y_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(VertexY, wgt_mvnV1);
  h_CryoVertex_Y_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(VertexY, wgt_mvnV1);

  h_CryoVertex_Z_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(VertexZ, wgt_mvnV1);
  h_CryoVertex_Z_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(VertexZ, wgt_mvnV1);
  h_CryoVertex_Z_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(VertexZ, wgt_mvnV1);

  h_CryoVertex_R_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(VertexR, wgt_mvnV1);
  h_CryoVertex_R_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(VertexR, wgt_mvnV1);
  h_CryoVertex_R_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(VertexR, wgt_mvnV1);

  for(auto Fid_Cut:CutToSurface_bins_finner ){
    //old  if(IsInExtraFiduicalVolume_Non_seperated_Cryo_regions_TRUTH_new(*universe, Fid_Cut)){
    if(IsInFiducalVolumeFromtheInnerEdgeTRUTH_new(*universe, Fid_Cut)){
      h_FidiucalCut_cryoVertex_R_TRUE->Fill(Fid_Cut, VertexR,  wgt_mvnV1);
      h_FidiucalCut_cryoVertex_Z_TRUE->Fill(Fid_Cut, VertexZ,  wgt_mvnV1);

    } // end of Volume Cut
  } // End of loop

}

///////////
/// End CV
//////////

} // end of Universes group
}// End of Truth Cuts

//////////////////////////////////////////////////////////////////////////
//                    Applying Truth Cuts
//////////////////////////////////////////////////////////////////////////


if(PassesCutsTRUTH(*Universe_GROUP.front(), kTRUTHCutsVector_2ndtrkEnergy, kWeightVector, Truth_Cut_Map_2ndTrkEnergy)){

  std::vector <double> Angle_trklist = Universe_GROUP.front()->GETvector_theta_wrtb_FS_particles();
  std::vector <int> PDG_trklist = Universe_GROUP.front()->GETvector_PDG_FS_particles();
  std::vector <double> Energy_trklist   = Universe_GROUP.front()->GETvector_KE_mc_FS_particles_GeV(pdg_DATABASEobject);

  int secondTrk = Universe_GROUP.front()->Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_lessthanAngle(PDG_trklist, Energy_trklist, Angle_trklist);

  int pdg_2ndTrk = PDG_trklist.at(secondTrk);
  double secTrkTrueEnergy = Energy_trklist.at(secondTrk);
  double pathlength = Universe_GROUP.front()->GetTRUE_nonMuoncolumnarDensity(secondTrk);
  Particle_type Particle_type_Event = GetParticlegroup_type(pdg_2ndTrk);
  Interaction_type Interaction_type_Event =  Universe_GROUP.front()->Get_InteractionStackType();
  Material_type Material_type_Event = Universe_GROUP.front()->Get_MaterialStackType();

  for (auto universe : Universe_GROUP){
    universe->SetEntry(ii);
    double wgt_mvnV1 = universe->GetWeight(kWeightVector);

    ///===================
    // Fill CV
    ///===================
    if(isCV(*universe)){

      h_secTrk_Energy_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(secTrkTrueEnergy, wgt_mvnV1);
      h_secTrk_Energy_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(secTrkTrueEnergy, wgt_mvnV1);
      h_secTrk_Energy_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(secTrkTrueEnergy, wgt_mvnV1);

    }


    h_secTrk_Energy_TRUE.univHist(universe)->Fill(secTrkTrueEnergy,wgt_mvnV1);
    h_secTrk_EnergyFINEBinning_TRUE.univHist(universe)->Fill(secTrkTrueEnergy,wgt_mvnV1);

    if(Particle_type_Event==kSecondary_particle_vector[0])
    {
      h_secTrk_Energy_PROTON_TRUE.univHist(universe)->Fill(secTrkTrueEnergy,wgt_mvnV1);
      h_secTrk_Pathlength_PROTON_TRUE.univHist(universe)->Fill(pathlength,wgt_mvnV1);
    }

    else if(Particle_type_Event==kSecondary_particle_vector[3]||Particle_type_Event==kSecondary_particle_vector[4])
    {
      h_secTrk_Energy_PION_TRUE.univHist(universe)->Fill(secTrkTrueEnergy,wgt_mvnV1);
      h_secTrk_Pathlength_PION_TRUE.univHist(universe)->Fill(pathlength,wgt_mvnV1);
    }

    else if(Particle_type_Event==kSecondary_particle_vector[1])
    {
      h_secTrk_Energy_Dimuon_TRUE.univHist(universe)->Fill(secTrkTrueEnergy,wgt_mvnV1);
    }

  } // end of Universes
}// End of Truth Cuts

//////////////////////////////////////////////////////////////////////////
//                    Applying Truth Cuts
//////////////////////////////////////////////////////////////////////////

if(PassesCutsTRUTH(*Universe_GROUP.front(), kTRUTHCutsVector_2ndtrkAngle, kWeightVector, Truth_Cut_Map_2ndTrkAngle)){

  std::vector <double> Angle_trklist = Universe_GROUP.front()->GETvector_theta_wrtb_FS_particles();
  std::vector <int> PDG_trklist = Universe_GROUP.front()->GETvector_PDG_FS_particles();
  std::vector <double> Energy_trklist   = Universe_GROUP.front()->GETvector_KE_mc_FS_particles_GeV(pdg_DATABASEobject);

  int secondTrk = Universe_GROUP.front()->Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE(PDG_trklist, Energy_trklist);
  int pdg_2ndTrk = PDG_trklist.at(secondTrk);
  double secTrkTrueEnergy = Energy_trklist.at(secondTrk);
  double secTrkTrueAngle = Angle_trklist.at(secondTrk);
  double openAngle = Universe_GROUP.front()->GetTRUE_NonmuTrkopenangle(secondTrk);
  Particle_type Particle_type_Event = GetParticlegroup_type(pdg_2ndTrk);

  for (auto universe : Universe_GROUP){
    universe->SetEntry(ii);

    double wgt_mvnV1 = universe->GetWeight(kWeightVector);

  ///===================
  // Fill CV
  ///===================

  if(isCV(*universe)){

    Interaction_type Interaction_type_Event = universe->Get_InteractionStackType();
    Material_type Material_type_Event = universe->Get_MaterialStackType();

    h_secTrk_Theta_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(secTrkTrueAngle, wgt_mvnV1);
    h_secTrk_Theta_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(secTrkTrueAngle, wgt_mvnV1);
    h_secTrk_Theta_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(secTrkTrueAngle, wgt_mvnV1);

    h_muonPT_2ndTrkangle_TRUE->Fill(universe->GetTRUE_PTmu(),secTrkTrueAngle,wgt_mvnV1);
    h_muonPZ_2ndTrkangle_TRUE->Fill(universe->GetTRUE_PZmu(),secTrkTrueAngle,wgt_mvnV1);
  }
  ///===================
  // End CV
  ///===================


  h_secTrk_Theta_TRUE.univHist(universe)->Fill(secTrkTrueAngle,wgt_mvnV1);
  h_secTrk_Openangle_TRUE.univHist(universe)->Fill(openAngle,wgt_mvnV1);

  if(Particle_type_Event==kSecondary_particle_vector[0]){

    h_secTrk_Theta_PROTON_TRUE.univHist(universe)->Fill(secTrkTrueAngle,wgt_mvnV1);
    h_secTrkopenangle_PROTON_TRUE.univHist(universe)->Fill(openAngle,wgt_mvnV1);

  }
  if(Particle_type_Event==kSecondary_particle_vector[3]||Particle_type_Event==kSecondary_particle_vector[4])
  {
    h_secTrk_Theta_PION_TRUE.univHist(universe)->Fill(secTrkTrueAngle,wgt_mvnV1);
  }

  if(Particle_type_Event==kSecondary_particle_vector[1]){
    h_secTrk_Theta_Dimuon_TRUE.univHist(universe)->Fill(secTrkTrueAngle,wgt_mvnV1);
  }


} // end of Universes
}// End of Truth Cuts

//////////////////////////////////////////////////////////////////////////
//                    Applying Truth Cuts
//////////////////////////////////////////////////////////////////////////


if(PassesCutsTRUTH(*Universe_GROUP.front(), kTRUTHCutsVector_2ndtrkAngle_Fidiucal)){
  for (auto universe : Universe_GROUP){
    universe->SetEntry(ii);

    if(isCV(*universe)){

      double wgt_mvnV1 = universe->GetWeight(kWeightVector);
      std::vector <double> Angle_trklist = universe->GETvector_theta_wrtb_FS_particles();
      std::vector <int> PDG_trklist = universe->GETvector_PDG_FS_particles();
      std::vector <double> Energy_trklist   = universe->GETvector_KE_mc_FS_particles_GeV(pdg_DATABASEobject);
      //std::vector<double> Tracklength = universe->MakeTRUE_VectorTrackLengthinMinerva_cm();
      int secondTrk = universe->Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE(PDG_trklist, Energy_trklist);
      int pdg_2ndTrk = PDG_trklist.at(secondTrk);

      double secTrkTrueAngle = Angle_trklist.at(secondTrk);
      double secTrkTrueEnergy = Energy_trklist.at(secondTrk);

      ///===================
      // Fill CV
      ///===================


      Particle_type Particle_type_Event = GetParticlegroup_type(pdg_2ndTrk);

      double VertexR = universe->GetTRUE_Vertex_r();
      double VertexZ = universe->GetTRUE_Vertex_z();
      double nonMuonDOCA = universe->GetTRUE_nonMuonDOCA(secondTrk);
      double Pathlength =  universe->GetTRUE_nonMuoncolumnarDensity(secondTrk);
      //  double trackLength = Tracklength.at(secondTrk);
      h_cryoVertex_Z_Pathlength_TRUE->Fill(VertexZ, Pathlength, wgt_mvnV1);
      h_cryoVertex_R_Pathlength_TRUE->Fill(VertexR, Pathlength, wgt_mvnV1);
      h_cryoVertex_Z_DOCA_TRUE->Fill(VertexZ, nonMuonDOCA, wgt_mvnV1);
      h_cryoVertex_R_DOCA_TRUE->Fill(VertexR, nonMuonDOCA, wgt_mvnV1);
      h_cryoVertex_Z_secTrkTheta_TRUE->Fill(VertexZ, secTrkTrueAngle, wgt_mvnV1);
      h_cryoVertex_R_secTrkTheta_TRUE->Fill(VertexR, secTrkTrueAngle, wgt_mvnV1);
      h_distanceEdge_2ndTrkAngle_TRUE->Fill(TRUE_Distance_to_innerTank(*universe), secTrkTrueAngle,wgt_mvnV1);

    } // End of CV Universe

  } // end of Universes
}// End of Truth Cuts

//////////////////////////////////////////////////////////////////////////
//                    Applying Truth Cuts
//////////////////////////////////////////////////////////////////////////

if(PassesCutsTRUTH(*Universe_GROUP.front(), kTRUTHCutsVector_2ndtrkEnergy_Fidiucal)){
  for (auto universe : Universe_GROUP){
    universe->SetEntry(ii);

    if(isCV(*universe)){

      double wgt_mvnV1 = universe->GetWeight(kWeightVector);
      std::vector <double> Angle_trklist = universe->GETvector_theta_wrtb_FS_particles();
      std::vector <int> PDG_trklist = universe->GETvector_PDG_FS_particles();
      std::vector <double> Energy_trklist   = universe->GETvector_KE_mc_FS_particles_GeV(pdg_DATABASEobject);
      //std::vector<double> Tracklength = universe->MakeTRUE_VectorTrackLengthinMinerva_cm();
      int secondTrk = universe->Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE(PDG_trklist, Energy_trklist);
      int pdg_2ndTrk = PDG_trklist.at(secondTrk);
      double secTrkTrueEnergy = Energy_trklist.at(secondTrk);

      ///===================
      // Fill CV
      ///===================
      Particle_type Particle_type_Event = GetParticlegroup_type(pdg_2ndTrk);

      double VertexR = universe->GetTRUE_Vertex_r();
      double VertexZ = universe->GetTRUE_Vertex_z();
      //  double trackLength = Tracklength.at(secondTrk);
      h_cryoVertex_Z_2ndTrkE_TRUE->Fill(VertexZ, secTrkTrueEnergy, wgt_mvnV1);
      h_cryoVertex_R_2ndTrkE_TRUE->Fill(VertexR, secTrkTrueEnergy, wgt_mvnV1);
      h_distanceEdge_2ndTrkE_TRUE->Fill(TRUE_Distance_to_innerTank(*universe), secTrkTrueEnergy ,wgt_mvnV1);

    } // End of CV Universe

  } // end of Universes
}// End of Truth Cuts

//////////////////////////////////////////////////////////////////////////
//                    Applying Truth Cuts
//////////////////////////////////////////////////////////////////////////

if(PassesCutsTRUTH(*Universe_GROUP.front(), kTRUTHCutsVector_ALL, kWeightVector, Truth_Cut_Map_Energy)){

  std::vector <double> Angle_trklist = Universe_GROUP.front()->GETvector_theta_wrtb_FS_particles();
  std::vector <int> PDG_trklist = Universe_GROUP.front()->GETvector_PDG_FS_particles();
  //std::vector <int> PDG_trklist_trajector = Universe_GROUP.front()->FromTRUTH_branch_GetVector_ALLTrajectors_PDG(); // this is broken
  std::vector <double> Energy_trklist   = Universe_GROUP.front()->GETvector_KE_mc_FS_particles_GeV(pdg_DATABASEobject);

  int secondTrk = Universe_GROUP.front()->Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_lessthanAngle(PDG_trklist, Energy_trklist, Angle_trklist);

  double Pathlength2ndTrk = Universe_GROUP.front()->GetTRUE_nonMuoncolumnarDensity(secondTrk);
  double DOCA_2ndTrk = Universe_GROUP.front()->GetTRUE_nonMuonDOCA(secondTrk);
  //double pathLength_2ndTrk = PathLength.at(secondTrk);
  Particle_type Particle_type_Event = GetParticlegroup_type(PDG_trklist.at(secondTrk));
  Interaction_type Interaction_type_Event =  Universe_GROUP.front()->Get_InteractionStackType();
  Material_type Material_type_Event = Universe_GROUP.front()->Get_MaterialStackType();


  for (auto universe : Universe_GROUP){
    universe->SetEntry(ii);

    double wgt_mvnV1 = universe->GetWeight(kWeightVector);

    h_secTrk_Pathlength_TRUE.univHist(universe)->Fill(Pathlength2ndTrk,wgt_mvnV1);
    //h_secTrk_tracklength_TRUE.univHist(universe)->Fill(pathLength_2ndTrk,wgt_mvnV1);
    h_secTrk_DOCA_TRUE.univHist(universe)->Fill(DOCA_2ndTrk,wgt_mvnV1);

    if(Particle_type_Event==kSecondary_particle_vector[0]){
      h_secTrk_Pathlength_PROTON_TRUE.univHist(universe)->Fill(Pathlength2ndTrk,wgt_mvnV1);
    }

    if(Particle_type_Event==kSecondary_particle_vector[3]||Particle_type_Event==kSecondary_particle_vector[4])
    {
      h_secTrk_Pathlength_PION_TRUE.univHist(universe)->Fill(Pathlength2ndTrk,wgt_mvnV1);

    }

    if(isCV(*universe)){
      h_secTrk_Pathlength_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(Pathlength2ndTrk, wgt_mvnV1);
      h_secTrk_Pathlength_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(Pathlength2ndTrk, wgt_mvnV1);
      h_secTrk_Pathlength_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(Pathlength2ndTrk, wgt_mvnV1);
      h_secTrk_DOCA_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(DOCA_2ndTrk, wgt_mvnV1);
      h_secTrk_DOCA_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(DOCA_2ndTrk, wgt_mvnV1);
      h_secTrk_DOCA_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(DOCA_2ndTrk, wgt_mvnV1);
    }

  } // end of Universes
}// End of Truth Cuts

//////////////////////////////////////////////////////////////////////////
//                    Applying Truth Cuts
//////////////////////////////////////////////////////////////////////////

if(PassesCutsTRUTH(*Universe_GROUP.front(), kTRUTHCutsVector_2ndtrkEnergy_2ndTrkAngle)){
  for (auto universe : Universe_GROUP){

    universe->SetEntry(ii);

    if(isCV(*universe)){

      double wgt_mvnV1 = universe->GetWeight(kWeightVector);
      std::vector <double> Angle_trklist = universe->GETvector_theta_wrtb_FS_particles();
      std::vector <int> PDG_trklist = universe->GETvector_PDG_FS_particles();
      std::vector <double> Energy_trklist   = universe->GETvector_KE_mc_FS_particles_GeV(pdg_DATABASEobject);
      //std::vector<double> Tracklength = universe->MakeTRUE_VectorTrackLengthinMinerva_cm();
      int secondTrk = universe->Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE(PDG_trklist, Energy_trklist);
      int pdg_2ndTrk = PDG_trklist.at(secondTrk);
      double secTrkTrueEnergy = Energy_trklist.at(secondTrk);
      double secTrkTrueAngle = Angle_trklist.at(secondTrk);
      ///===================
      // Fill CV
      ///===================


      Particle_type Particle_type_Event = GetParticlegroup_type(pdg_2ndTrk);

      double VertexR = universe->GetTRUE_Vertex_r();
      double VertexZ = universe->GetTRUE_Vertex_z();
      //  double trackLength = Tracklength.at(secondTrk);

      h_2ndTrkE_2ndtrkangle_TRUE ->Fill(secTrkTrueEnergy, secTrkTrueAngle,wgt_mvnV1);

      if(Particle_type_Event==kSecondary_particle_vector[0]){
        h_2ndTrkE_2ndtrkangle_Proton_TRUE->Fill(secTrkTrueEnergy, secTrkTrueAngle,wgt_mvnV1);
      }

      if(Particle_type_Event==kSecondary_particle_vector[3]||Particle_type_Event==kSecondary_particle_vector[4])
      {
        h_2ndTrkE_2ndtrkangle_Pion_TRUE->Fill(secTrkTrueEnergy, secTrkTrueAngle,wgt_mvnV1);
      }



    } // End of CV Universe

  } // end of Universes
}// End of Truth Cuts




//////////////////////////////////////////////////////////////////////////
//                   END of Group Loop
//////////////////////////////////////////////////////////////////////////


} // End Band Groups loop


//////////////////////////////////////////////////////////////////////////
//                   END of Entire Loop
//////////////////////////////////////////////////////////////////////////


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

    //////////////////////////////////

    h_CryoVertex_X_TRUE.SyncCVHistos();
    h_CryoVertex_Y_TRUE.SyncCVHistos();
    h_CryoVertex_R_TRUE.SyncCVHistos();
    h_CryoVertex_RR_TRUE.SyncCVHistos();
    h_CryoVertex_Z_TRUE.SyncCVHistos();
    h_FidiucalCut_TRUE.SyncCVHistos();
    h_Distance_to_InnerTank_TRUE.SyncCVHistos();
    h_Distance_to_InnerTank_upstreamCap_TRUE.SyncCVHistos();
    h_Distance_to_InnerTank_barrel_TRUE.SyncCVHistos();
    h_Distance_to_InnerTank_downstreamCap_TRUE.SyncCVHistos();
    //////////////////////////////////
    h_secTrk_Energy_TRUE.SyncCVHistos();
    h_secTrk_EnergyFINEBinning_TRUE.SyncCVHistos();
    h_secTrk_Theta_TRUE.SyncCVHistos();
    h_secTrk_Openangle_TRUE.SyncCVHistos();
    h_secTrk_Theta_Dimuon_TRUE.SyncCVHistos();
    h_secTrk_Pathlength_TRUE.SyncCVHistos();
    h_secTrk_Pathlength_PROTON_TRUE.SyncCVHistos();
    h_secTrk_Pathlength_PION_TRUE.SyncCVHistos();

    h_secTrk_Energy_Dimuon_TRUE.SyncCVHistos();
    h_secTrk_Energy_PROTON_TRUE.SyncCVHistos();
    h_secTrk_Theta_PROTON_TRUE.SyncCVHistos();
    h_secTrkopenangle_PROTON_TRUE.SyncCVHistos();
    h_secTrk_Energy_PION_TRUE.SyncCVHistos();
    h_secTrk_Theta_PION_TRUE.SyncCVHistos();
    h_secTrkopenangle_PION_TRUE.SyncCVHistos();
    //h_secTrk_tracklength_TRUE.SyncCVHistos();
    //////////////////////////////////

    //h_secTrkTheta_cryoVertex_Z_TRUE.SyncCVHistos();
    //h_secTrkTheta_cryoVertex_R_TRUE.SyncCVHistos();

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

  //TGraph *Truth_Cuts =  Make_TruthCut_Tgraph_fromCutMap("Truth_Cuts", Truth_Cut_Map);

  TGraph *TGraph_Truth_Cut_Map_MuonEnergy =  Make_TruthCut_Tgraph_fromCutMap("TGraph_Truth_Cut_Map_MuonEnergy", Truth_Cut_Map_Energy);
  TGraph *TGraph_Truth_Cut_Map_MuonTheta    =  Make_TruthCut_Tgraph_fromCutMap("TGraph_Truth_Cut_Map_MuonTheta", Truth_Cut_Map_Theta);
  TGraph *TGraph_Truth_Cut_Map_Fiduical     =  Make_TruthCut_Tgraph_fromCutMap("TGraph_Truth_Cut_Map_Fiduical", Truth_Cut_Map_Fiduical);
  TGraph *TGraph_Truth_Cut_Map_2ndTrkEnergy =  Make_TruthCut_Tgraph_fromCutMap("TGraph_Truth_Cut_Map_2ndTrkEnergy", Truth_Cut_Map_2ndTrkEnergy);
  TGraph *TGraph_Truth_Cut_Map_2ndTrkAngle  =  Make_TruthCut_Tgraph_fromCutMap("TGraph_Truth_Cut_Map_2ndTrkAngle", Truth_Cut_Map_2ndTrkAngle);






    for(auto cuts: Truth_Cut_Map_Fiduical){
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
    sprintf(outFileName, "%s/Histograms_%s_%s_%s_Efficiency.root",rootpathway,c,d,sysmatics_status_char);
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
  //Truth_Cuts->Write();
  TGraph_Truth_Cut_Map_MuonEnergy->Write();
  TGraph_Truth_Cut_Map_MuonTheta->Write();
  TGraph_Truth_Cut_Map_Fiduical->Write();
  TGraph_Truth_Cut_Map_2ndTrkEnergy->Write();
  TGraph_Truth_Cut_Map_2ndTrkAngle->Write();
  ////////////////////////////////////////////////
  h_MuonE_TRUE.hist->Write();

  h_MuonPZ_TRUE.hist->Write();

  h_MuonPT_TRUE.hist->Write();

  h_MuonTheta_TRUE.hist->Write();

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


  h_CryoVertex_RR_TRUE.hist->Write();
  h_FidiucalCut_TRUE.hist->Write();
  h_Distance_to_InnerTank_TRUE.hist->Write();
  h_Distance_to_InnerTank_upstreamCap_TRUE.hist->Write();
  h_Distance_to_InnerTank_barrel_TRUE.hist->Write();
  h_Distance_to_InnerTank_downstreamCap_TRUE.hist->Write();

  h_secTrk_Openangle_TRUE.hist->Write();

  h_secTrk_Energy_TRUE.hist->Write();
  h_secTrk_EnergyFINEBinning_TRUE.hist->Write();

  h_secTrk_Energy_TRUE_Material.WriteToFile(*outFile);
  h_secTrk_Energy_TRUE_Interaction.WriteToFile(*outFile);
  h_secTrk_Energy_TRUE_Particle.WriteToFile(*outFile);


  h_secTrk_Theta_TRUE.hist->Write();

  h_secTrk_Theta_TRUE_Material.WriteToFile(*outFile);
  h_secTrk_Theta_TRUE_Interaction.WriteToFile(*outFile);
  h_secTrk_Theta_TRUE_Particle.WriteToFile(*outFile);

  h_secTrk_Pathlength_TRUE_Material.WriteToFile(*outFile);
  h_secTrk_Pathlength_TRUE_Interaction.WriteToFile(*outFile);
  h_secTrk_Pathlength_TRUE_Particle.WriteToFile(*outFile);
  h_secTrk_DOCA_TRUE_Material.WriteToFile(*outFile);
  h_secTrk_DOCA_TRUE_Interaction.WriteToFile(*outFile);
  h_secTrk_DOCA_TRUE_Particle.WriteToFile(*outFile);
  h_secTrk_DOCA_TRUE.hist->Write();


  h_secTrk_Energy_Dimuon_TRUE.hist->Write();
  h_secTrk_Theta_Dimuon_TRUE.hist->Write();
  h_secTrk_Energy_PROTON_TRUE.hist->Write();
  h_secTrk_Theta_PROTON_TRUE.hist->Write();
  h_secTrkopenangle_PROTON_TRUE.hist->Write();
  h_secTrk_Energy_PION_TRUE.hist->Write();
  h_secTrk_Theta_PION_TRUE.hist->Write();
  h_secTrkopenangle_PION_TRUE.hist->Write();

  h_secTrk_Pathlength_TRUE.hist->Write();
  h_secTrk_Pathlength_PROTON_TRUE.hist->Write();
  h_secTrk_Pathlength_PION_TRUE.hist->Write();

  //h_secTrkTheta_cryoVertex_Z_TRUE.hist->Write();
  //h_secTrkTheta_cryoVertex_R_TRUE.hist->Write();

  h_cryoVertex_Z_secTrkTheta_TRUE->Write();
  h_cryoVertex_R_secTrkTheta_TRUE->Write();
  h_cryoVertex_Z_R_TRUE->Write();

  h_muonPT_2ndTrkangle_TRUE->Write();
  h_muonPZ_2ndTrkangle_TRUE->Write();
  h_muontheta_2ndTrkangle_TRUE->Write();

  h_2ndTrkE_2ndtrkangle_TRUE->Write();
  h_2ndTrkE_2ndtrkangle_Proton_TRUE->Write();
  h_2ndTrkE_2ndtrkangle_Pion_TRUE->Write();


  h_cryoVertex_Z_Pathlength_TRUE->Write();
  h_cryoVertex_R_Pathlength_TRUE->Write();
  h_cryoVertex_Z_DOCA_TRUE->Write();
  h_cryoVertex_R_DOCA_TRUE->Write();
  h_cryoVertex_Z_2ndTrkE_TRUE->Write();
  h_cryoVertex_R_2ndTrkE_TRUE->Write();

  h_distanceEdge_cryoVertex_R_TRUE->Write();
  h_distanceEdge_cryoVertex_Z_TRUE->Write();
  h_distanceEdge_DOCA_TRUE->Write();
  h_distanceEdge_2ndTrkE_TRUE ->Write();
  h_distanceEdge_Pathlength_TRUE->Write();
  h_distanceEdge_2ndTrkAngle_TRUE ->Write();
  h_distanceEdge_MuonPT_TRUE ->Write();
  h_distanceEdge_MuonPZ_TRUE->Write();
  h_distanceEdge_Muontheta_TRUE->Write();


  outFile->Close();
  //std::cout<< " the Number of on_leading = "<< non_leading<<std::endl;
  //std::cout<< " the Number of on_leading_removed = "<< non_leading_removed<<std::endl;




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
  True_vec.push_back(kTRUTHFiduical_new );
  True_vec.push_back(kTRUTH_greaterthanoneFS);
  //True_vec.push_back(kTRUTH_secTrk_Angle_threshold);
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);
  True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold_withProtonanPionThresholds);
  True_vec.push_back(kAllTRUTHCuts);

  return True_vec;
//#endif
}

std::vector<ECutsTRUTH> GetTRUTHCutsVector_MuonEnergy() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ECutsTRUTH> True_vec;
  True_vec.push_back(kTRUTHNoCuts);
  True_vec.push_back(kTRUTHneutrino);
  True_vec.push_back(kTRUTHCCInteraction );
  True_vec.push_back(kTRUTHtarget);
  //True_vec.push_back(kTRUTHMuonEnergy );
  True_vec.push_back(kTRUTHMuonAngle );
  True_vec.push_back(kTRUTHFiduical_new );
  True_vec.push_back(kTRUTH_greaterthanoneFS);
  //True_vec.push_back(kTRUTH_secTrk_Angle_threshold);
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);
  True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold_withProtonanPionThresholds);
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);
  //True_vec.push_back(kTRUTH_2ndTrkProtonEnergythreshold);
  //True_vec.push_back(kTRUTH_2ndTrkPionEnergythreshold);
  True_vec.push_back(kAllTRUTHCuts);


  //int n = sizeof(kCutsArray) / sizeof(kCutsArray[0]);
  //static std::vector<ECuts> ret_vec(kCutsArray, kCutsArray + n);
  return True_vec;
//#endif
}

std::vector<ECutsTRUTH> GetTRUTHCutsVector_MuonEnergy_noFiduical() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ECutsTRUTH> True_vec;
  True_vec.push_back(kTRUTHNoCuts);
  True_vec.push_back(kTRUTHneutrino);
  True_vec.push_back(kTRUTHCCInteraction );
  True_vec.push_back(kTRUTHtarget);
  //True_vec.push_back(kTRUTHMuonEnergy );
  True_vec.push_back(kTRUTHMuonAngle );
  //True_vec.push_back(kTRUTHFiduical_new );
  True_vec.push_back(kTRUTH_greaterthanoneFS);
  //True_vec.push_back(kTRUTH_secTrk_Angle_threshold);
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);
  True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold_withProtonanPionThresholds);
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);
  //True_vec.push_back(kTRUTH_2ndTrkProtonEnergythreshold);
  //True_vec.push_back(kTRUTH_2ndTrkPionEnergythreshold);
  True_vec.push_back(kAllTRUTHCuts);


  //int n = sizeof(kCutsArray) / sizeof(kCutsArray[0]);
  //static std::vector<ECuts> ret_vec(kCutsArray, kCutsArray + n);
  return True_vec;
//#endif
}

std::vector<ECutsTRUTH> GetTRUTHCutsVector_MuonTheta() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ECutsTRUTH> True_vec;
  True_vec.push_back(kTRUTHNoCuts);
  True_vec.push_back(kTRUTHneutrino);
  True_vec.push_back(kTRUTHCCInteraction );
  True_vec.push_back(kTRUTHtarget);
  True_vec.push_back(kTRUTHMuonEnergy );
  //True_vec.push_back(kTRUTHMuonAngle );
  True_vec.push_back(kTRUTHFiduical_new );
  True_vec.push_back(kTRUTH_greaterthanoneFS);
  //True_vec.push_back(kTRUTH_atleastone_non_Neutral_secTrk);
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);
  True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold_withProtonanPionThresholds);
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);
  //True_vec.push_back(kTRUTH_2ndTrkProtonEnergythreshold);
  //True_vec.push_back(kTRUTH_2ndTrkPionEnergythreshold);
  True_vec.push_back(kAllTRUTHCuts);


  //int n = sizeof(kCutsArray) / sizeof(kCutsArray[0]);
  //static std::vector<ECuts> ret_vec(kCutsArray, kCutsArray + n);
  return True_vec;
//#endif
}

std::vector<ECutsTRUTH> GetTRUTHCutsVector_MuonTheta_noFid() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ECutsTRUTH> True_vec;
  True_vec.push_back(kTRUTHNoCuts);
  True_vec.push_back(kTRUTHneutrino);
  True_vec.push_back(kTRUTHCCInteraction );
  True_vec.push_back(kTRUTHtarget);
  True_vec.push_back(kTRUTHMuonEnergy );
  //True_vec.push_back(kTRUTHMuonAngle );
  //True_vec.push_back(kTRUTHFiduical_new );
  True_vec.push_back(kTRUTH_greaterthanoneFS);
  //True_vec.push_back(kTRUTH_atleastone_non_Neutral_secTrk);
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);
  True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold_withProtonanPionThresholds);
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);
  //True_vec.push_back(kTRUTH_2ndTrkProtonEnergythreshold);
  //True_vec.push_back(kTRUTH_2ndTrkPionEnergythreshold);
  True_vec.push_back(kAllTRUTHCuts);


  //int n = sizeof(kCutsArray) / sizeof(kCutsArray[0]);
  //static std::vector<ECuts> ret_vec(kCutsArray, kCutsArray + n);
  return True_vec;
//#endif
}
std::vector<ECutsTRUTH> GetTRUTHCutsVector_Fiduical() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ECutsTRUTH> True_vec;
  True_vec.push_back(kTRUTHNoCuts);
  True_vec.push_back(kTRUTHneutrino);
  True_vec.push_back(kTRUTHCCInteraction );
  True_vec.push_back(kTRUTHtarget);
  True_vec.push_back(kTRUTHMuonEnergy );
  True_vec.push_back(kTRUTHMuonAngle );
  //True_vec.push_back(kTRUTHFiduical );
  True_vec.push_back(kTRUTH_greaterthanoneFS);
  //True_vec.push_back(kTRUTH_secTrk_Angle_threshold);
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);
  True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold_withProtonanPionThresholds);
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);
  //True_vec.push_back(kTRUTH_2ndTrkProtonEnergythreshold);
  //True_vec.push_back(kTRUTH_2ndTrkPionEnergythreshold);
  True_vec.push_back(kAllTRUTHCuts);


  //int n = sizeof(kCutsArray) / sizeof(kCutsArray[0]);
  //static std::vector<ECuts> ret_vec(kCutsArray, kCutsArray + n);
  return True_vec;
//#endif
}


std::vector<ECutsTRUTH> GetTRUTHCutsVector_2ndtrkEnergy() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ECutsTRUTH> True_vec;
  True_vec.push_back(kTRUTHNoCuts);
  True_vec.push_back(kTRUTHneutrino);
  True_vec.push_back(kTRUTHCCInteraction );
  True_vec.push_back(kTRUTHtarget);
  True_vec.push_back(kTRUTHMuonEnergy );
  True_vec.push_back(kTRUTHMuonAngle );
  True_vec.push_back(kTRUTHFiduical_new );
  True_vec.push_back(kTRUTH_greaterthanoneFS);
  //True_vec.push_back(kTRUTH_secTrk_Angle_threshold);
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold_withProtonanPionThresholds);
  True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);
  //True_vec.push_back(kTRUTH_2ndTrkProtonEnergythreshold);
  //True_vec.push_back(kTRUTH_2ndTrkPionEnergythreshold);
  True_vec.push_back(kAllTRUTHCuts);

  return True_vec;
//#endif
}
std::vector<ECutsTRUTH> GetTRUTHCutsVector_2ndtrkEnergy_2ndtrkAngle() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ECutsTRUTH> True_vec;
  True_vec.push_back(kTRUTHNoCuts);
  True_vec.push_back(kTRUTHneutrino);
  True_vec.push_back(kTRUTHCCInteraction );
  True_vec.push_back(kTRUTHtarget);
  True_vec.push_back(kTRUTHMuonEnergy );
  True_vec.push_back(kTRUTHMuonAngle );
  True_vec.push_back(kTRUTHFiduical_new );
  True_vec.push_back(kTRUTH_greaterthanoneFS);
  //True_vec.push_back(kTRUTH_secTrk_Angle_threshold);
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold_withProtonanPionThresholds); // Need to make a kTRUTH_No_Neutral
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);
  //True_vec.push_back(kTRUTH_2ndTrkProtonEnergythreshold);
  //True_vec.push_back(kTRUTH_2ndTrkPionEnergythreshold);
  True_vec.push_back(kTRUTH_atleastone_non_Neutral_secTrk);
  True_vec.push_back(kAllTRUTHCuts);

  return True_vec;
//#endif
}


std::vector<ECutsTRUTH> GetTRUTHCutsVector_2ndtrkAngle() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ECutsTRUTH> True_vec;
  True_vec.push_back(kTRUTHNoCuts);
  True_vec.push_back(kTRUTHneutrino);
  True_vec.push_back(kTRUTHCCInteraction );
  True_vec.push_back(kTRUTHtarget);
  True_vec.push_back(kTRUTHMuonEnergy );
  True_vec.push_back(kTRUTHMuonAngle );
  True_vec.push_back(kTRUTHFiduical_new );
  True_vec.push_back(kTRUTH_greaterthanoneFS);
  //True_vec.push_back(kTRUTH_secTrk_Angle_threshold);
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold_withProtonanPionThresholds);
  True_vec.push_back(kTRUTH_No_Neutral_KEthreshold_withProtonanPionThresholds);
  //True_vec.push_back(kTRUTH_2ndTrkProtonEnergythreshold);
  //True_vec.push_back(kTRUTH_2ndTrkPionEnergythreshold);
  True_vec.push_back(kAllTRUTHCuts);

  return True_vec;
//#endif
}

std::vector<ECutsTRUTH> GetTRUTHCutsVector_2ndtrkAngle_Fidiucal() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ECutsTRUTH> True_vec;
  True_vec.push_back(kTRUTHNoCuts);
  True_vec.push_back(kTRUTHneutrino);
  True_vec.push_back(kTRUTHCCInteraction );
  True_vec.push_back(kTRUTHtarget);
  True_vec.push_back(kTRUTHMuonEnergy );
  True_vec.push_back(kTRUTHMuonAngle );
  //True_vec.push_back(kTRUTHFiduical );
  True_vec.push_back(kTRUTH_greaterthanoneFS);
  //True_vec.push_back(kTRUTH_secTrk_Angle_threshold);
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold_withProtonanPionThresholds);
  True_vec.push_back(kTRUTH_No_Neutral_KEthreshold_withProtonanPionThresholds);
  //True_vec.push_back(kTRUTH_2ndTrkProtonEnergythreshold);
  //True_vec.push_back(kTRUTH_2ndTrkPionEnergythreshold);
  True_vec.push_back(kAllTRUTHCuts);

  return True_vec;
//#endif
}

std::vector<ECutsTRUTH> GetTRUTHCutsVector_2ndtrkEnergy_Fiduical() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ECutsTRUTH> True_vec;
  True_vec.push_back(kTRUTHNoCuts);
  True_vec.push_back(kTRUTHneutrino);
  True_vec.push_back(kTRUTHCCInteraction );
  True_vec.push_back(kTRUTHtarget);
  True_vec.push_back(kTRUTHMuonEnergy );
  True_vec.push_back(kTRUTHMuonAngle );
  //True_vec.push_back(kTRUTHFiduical_new );
  True_vec.push_back(kTRUTH_greaterthanoneFS);
  //True_vec.push_back(kTRUTH_secTrk_Angle_threshold);
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold_withProtonanPionThresholds);
  True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);
  //True_vec.push_back(kTRUTH_2ndTrkProtonEnergythreshold);
  //True_vec.push_back(kTRUTH_2ndTrkPionEnergythreshold);
  True_vec.push_back(kAllTRUTHCuts);

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
  weight_vec.push_back(kweight_HeliumTargetMass);
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
