//File: Helium2D_runTRUTHLoop.cxx
//Brief: Given ntuple files from HeAnaTupleTool.cpp , extracts 2D TRUE EventSelction for Helium Nu interactions
//Writes a .root file Event Selection histograms.
//
//Usage: 2D TRUTH 2DEventSelection  <mc.root>
//
//Author: Christian Nguyen  christian2nguyen@ufl.edu

#include "Helium2D_runTRUTHLoop.h"

std::string OUTputRoot_pathway = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev";

//=====================================================
// Functions
//=====================================================
std::vector<ECuts> GetRECOCutsVector();
std::vector<ECutsTRUTH> GetTRUTHCutsVector();
std::vector<ME_helium_Playlists> GetPlayListVector();
std::vector<Weights> GetWeightVector();
std::vector<Particle_type>  GetParicle_type();

std::vector<FluxSlices> DaisyN{
  kheliumdaisy0,
  kheliumdaisy1,
  kheliumdaisy2,
  kheliumdaisy3,
  kheliumdaisy4,
  kheliumdaisy5,
  kheliumdaisy6,
  kheliumdaisy7,
  kheliumdaisy8,
  kheliumdaisy9,
  kheliumdaisy10,
  kheliumdaisy11
};

//=====================================================
// Run With error Sysematics
//=====================================================
const bool m_RunCodeWithSystematics = false;

//=====================================================
// Define Categories for Stack Plots
//=====================================================

const std::vector<PlotUtils::NamedCategory<Material_type>>
MaterialGroup_categories = {
PlotUtils::NamedCategory<Material_type>({kMaterial_OTHER}, "Other"),
PlotUtils::NamedCategory<Material_type>({kIron},           "Iron"),
PlotUtils::NamedCategory<Material_type>({kCarbon},         "Carbon"),
PlotUtils::NamedCategory<Material_type>({kLead},           "Lead"),
PlotUtils::NamedCategory<Material_type>({kAluminium},      "Aluminium"),
PlotUtils::NamedCategory<Material_type>({kHelium},         "Helium")

};
/*
const std::vector<PlotUtils::NamedCategory<Interaction_type>>
InteractionGroupDISBreakdown_categories = {
  PlotUtils::NamedCategory<Interaction_type>({kInteraction_OTHER},"Other"),
  PlotUtils::NamedCategory<Interaction_type>({kInteraction_NONE}, "None"),
  PlotUtils::NamedCategory<Interaction_type>({kDIS},              "DIS"),
  PlotUtils::NamedCategory<Interaction_type>({k2p2h},             "2p2h"),
  PlotUtils::NamedCategory<Interaction_type>({kRes_Coh_Pion},     "Res_Coh"),
  PlotUtils::NamedCategory<Interaction_type>({kElastic},          "Elastic")
};
*/

const std::vector<PlotUtils::NamedCategory<Interaction_type>>
InteractionGroupDISBreakdown_categories = {
  PlotUtils::NamedCategory<Interaction_type>({kInteraction_OTHER},"Other"),
  PlotUtils::NamedCategory<Interaction_type>({kInteraction_NONE}, "None"),
  PlotUtils::NamedCategory<Interaction_type>({kDISSoft},          "SoftDIS"),
  PlotUtils::NamedCategory<Interaction_type>({kDISHard},          "HardDIS"),
  PlotUtils::NamedCategory<Interaction_type>({kDISSIS},           "SIS"),
  PlotUtils::NamedCategory<Interaction_type>({k2p2h},             "2p2h"),
  PlotUtils::NamedCategory<Interaction_type>({kdeltaRES},         "#DeltaRes"),
  PlotUtils::NamedCategory<Interaction_type>({kHeavierRES},       "HeavierRes"),
  PlotUtils::NamedCategory<Interaction_type>({kElastic},          "QE")
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
ParticleGroup_reduced_categories = {
  PlotUtils::NamedCategory<Particle_type>({kParticle_N_A},          "N_A"),
  PlotUtils::NamedCategory<Particle_type>({kParticle_OTHER},        "Other"),
  PlotUtils::NamedCategory<Particle_type>({kParticle_neutral},      "Neutral"),
  PlotUtils::NamedCategory<Particle_type>({kMuon},                   "Muon"),
  PlotUtils::NamedCategory<Particle_type>({kPion_0_Electron_kGamma},"e^{-/+},#gamma,#pi^{0}"),
  PlotUtils::NamedCategory<Particle_type>({kPion_pos_neg},          "Pi^{-/+}"),
  PlotUtils::NamedCategory<Particle_type>({kProton},                "Proton")


};




/*const auto TracksGreaterThan2 = {  NamedCategory<int>({3},   "ThirdTrack"),
                                   NamedCategory<int>({4},   "FourthTrack"),
                                   NamedCategory<int>({5},   "FifthTrack"),
                                   NamedCategory<int>({6},   "SixthTrack"),
                                   NamedCategory<int>({7},   "SevethTrack"),
                                   NamedCategory<int>({8},   "EighthTrack")

                                 };*/

//=====================================================
// Define Number of Flux Universes to Apply for Error Bands
//=====================================================

const int n_flux_universes = 100;

//=====================================================
//=====================================================
// Constuct Error Universes
//=====================================================

std::map< std::string, std::vector<HeliumCVUniverse*> >
GetErrorBands(PlotUtils::ChainWrapper* chain) {
  typedef std::map< std::string, std::vector<HeliumCVUniverse*> > SystMap;

  SystMap error_bands;

  //========================================================================
  // CV
  //========================================================================

    error_bands[std::string("cv")].push_back( new HeliumCVUniverse(chain) );

    //========================================================================
    // Apply Other Error Universes
    //========================================================================

    if(m_RunCodeWithSystematics==true)
    {
      //========================================================================
      //Flux
      //========================================================================

      SystMap flux_systematics = PlotUtils::GetFluxSystematicsMap<HeliumCVUniverse>(chain,n_flux_universes);
      error_bands.insert(flux_systematics.begin(), flux_systematics.end());


      //========================================================================
      // GENIE FSI + CrossSection
      //========================================================================

      SystMap genie_systematics = PlotUtils::GetGenieSystematicsMap<HeliumCVUniverse>(chain);
      error_bands.insert(genie_systematics.begin(), genie_systematics.end());
      //========================================================================
       // MnvTunes
       //========================================================================
       // 2p2h

      SystMap a2p2h_systematics = PlotUtils::Get2p2hSystematicsMap<HeliumCVUniverse>(chain);
      error_bands.insert(a2p2h_systematics.begin(), a2p2h_systematics.end());

      //========================================================================
      // (RPA)random phase appox , long range Nuclear correlations modeling
      //========================================================================

      SystMap RPA_systematics = PlotUtils::GetRPASystematicsMap<HeliumCVUniverse>(chain);
      error_bands.insert(RPA_systematics.begin(), RPA_systematics.end());



              // Target Mass Systematics
      UniverseMap targetMass_systematics = PlotUtils::GetTargetMassSystematicsMap_forScintillator<HeliumCVUniverse>(chain);
      error_bands.insert(targetMass_systematics.begin(), targetMass_systematics.end());

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
// Main Event Loop
//======================================================================
void runEventLoop(ME_helium_Playlists &PlayList_iterator, bool &m_debugOn, bool &Run_EventLoopOnGrid) {
  // Make a chain of events
  loadLibs();

const std::vector<ECutsTRUTH> kTRUTHCutsVector = GetTRUTHCutsVector();
const std::vector<Weights> kTRUEWeights_v1tune = GetWeightVector();
const std::vector<Particle_type> kSecondary_particle_vector = GetParicle_type();
std::ofstream output("LogFile_TRUTH.txt",std::ofstream::app);

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"MC TRUTH LOOP  "<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
//////////////////
TDatabasePDG *pdg_DATABASEobject = TDatabasePDG::Instance();

//======================================================================
////////////////////ADDING TO CHAIN wrapper ///////////////////////////
//======================================================================
bool is_mc= true;

  std::string playlist = GetPlaylist(PlayList_iterator);
  //======================================================================
  // SET MINERVA Analysis Type and Universes
  //======================================================================
  MinervaUniverse::SetPlaylist(playlist);
 std::string seestring = MinervaUniverse::GetPlaylist();
  HeliumPlayListInfo Playlist_Info(playlist);
  std::cout<<"Working with Playlist =  "<<   seestring <<std::endl;
  MinervaUniverse::SetTruth(true);
  MinervaUniverse::SetNuEConstraint(true);
  MinervaUniverse::SetAnalysisNuPDG(14);
  MinervaUniverse::SetNFluxUniverses(n_flux_universes);
  MinervaUniverse::SetZExpansionFaReweight(true);
  MinervaUniverse::SetNonResPiReweight(true);
  MinervaUniverse::SetDeuteriumGeniePiTune(false);

  //======================================================================
  // SET Flux Parameters for Intergrated Flux hist
  //======================================================================

  int nu_pdg = MinervaUniverse::GetAnalysisNuPDG();
  std::string playlist_fluxreweighter = MinervaUniverse::GetPlaylist();
  bool useNuEconstraint = MinervaUniverse::UseNuEConstraint();
  int NFlux_universe = MinervaUniverse::GetNFluxUniverses();
  bool useMuonCorrelations = true;
  double Min_NuFluxEnergy = 0.0;
  double Max_NuFluxEnergy = 120.0;


  auto Playlist_txtFILEPath =  GetPlaylist_txtFILE_path_MasterAnaDev(PlayList_iterator, is_mc );
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"Adding to Chain Wrapper For Loop   "<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  PlotUtils::ChainWrapper* chw_MC = makeChainWrapperPtr(Playlist_txtFILEPath.c_str(), "Truth");
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"Adding to Chain Wrapper For POT counter   "<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

  //======================================================================
  ///////////////////Making/adding to error bands  ///////////////////////////
  //======================================================================

std::map< std::string, std::vector<HeliumCVUniverse*> > error_bands= GetErrorBands(chw_MC);

//======================================================================
// Group All Vertial Error Bands
//======================================================================

std::vector<std::vector<HeliumCVUniverse*>> Error_Band_Universe_GROUPS = groupCompatibleUniverses(error_bands);
std::cout<<"Number of Universes set is = "<< 	MinervaUniverse::GetNFluxUniverses()<<std::endl;
POTCounter pot_counter;
const std::string RootName =GetPlaylist_ROOT_path_MasterAnaDev(PlayList_iterator, is_mc );
//const std::string RootName = GetPlaylist_ROOT_path("1D_EnergyFix",  is_mc );
std::cout<<"The Playlist that is set is = "<< seestring <<std::endl;
std::cout<<"The Playlist Root = "<< RootName<<std::endl;
 ///pnfs/minerva/persistent/users/cnguyen/ME_G1_Merg/*.root

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
  for(auto Weight_name:kTRUEWeights_v1tune )
  {
    output<<"  Weights type: " <<GetWeight_name(Weight_name) <<endl;
  }

  output<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  output<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

  //LogFile LOGFILE(PlayList_iterator ,kTRUTHCutsVector , kTRUEWeights_v1tune, kTRUTHCutsVector, 1,true,_logfile);
  //LOGFILE<<"Number of Universes set is = "<< 	MinervaUniverse::GetNFluxUniverses()<<"/n";

  //======================================================================
  // SET Binning for Hist
  //======================================================================

std::vector<double> Ebin_vector = GetBinMuonVector(kE_2D);
std::vector<double> Pzbin_vector = GetBinMuonVector(kP_Z_2D);
std::vector<double> PTbin_vector = GetBinMuonVector(kP_T_2D);


std::vector<double> MuonThetabin_vector= GetBinMuonVector(kAngleWRTB);
std::vector<double> Ebin_1Dvector = GetBinMuonVector(kE);
std::vector<double> Pzbin_1Dvector= GetBinMuonVector(kP_Z);
std::vector<double> PTbin_1Dvector= GetBinMuonVector(kP_T);
//std::vector<double> MuonThetabin_1Dvector= GetBinMuonVector(kAngleWRTB);



std::vector<double> bigAngle_bins{0.0, 15.0, 30.0, 45.0, 60.0};

//std::vector<double> EnergyNu{0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0};

std::vector<double> EnergyNu;//{0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0};

double edge = 0;
for(int i = 0; i < 1001; i ++ ){
  EnergyNu.push_back(edge);
  edge = edge + .1;
}
std::vector<double> EnergySlices{0.0,1.0,2.0,3.0,4.0};

//std::vector<double> MuonThetabin_vector= GetBinMuonVector(kAngleWRTB_2D);
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

//////////////////////////
//std::vector<double> Vertex_Xbins= GetBinvertexVector(kX);
//std::vector<double> Vertex_Ybins= GetBinvertexVector(kY);
//std::vector<double> Vertex_Zbins= GetBinvertexVector(kZ);
//std::vector<double> Vertex_Rbins= GetBinvertexVector(kR);

std::vector<double> Vertex_Xbins = GetBinvertexVector(kX_2D);
std::vector<double> Vertex_Ybins = GetBinvertexVector(kY_2D);
std::vector<double> Vertex_Zbins = GetBinvertexVector(kZ_2D);
std::vector<double> Vertex_Rbins = GetBinvertexVector(kR_2D);


std::vector<double> Vertex_DOCAbins= GetBinMuonVector(kDOCA_muon_2D);
std::vector<double> Vertex_secondTrkEbins= GetSecondTrkVarVector(ksecE_2D);
std::vector<double> Vertex_secondTrkTheta_bins= GetSecondTrkVarVector(kThetamid);
std::vector<double> Vertex_secondTrkDOCA_bins= GetSecondTrkVarVector(kDOCA_2D);
std::vector<double> Vertex_secondTrkPathway_bins = GetSecondTrkVarVector(kPathway);

std::vector<double> SecTrk_Tracklength_vector = GetSecondTrkVarVector(ksec_tracklength_minerva_2D);

//======================================================================
//muon Varibles
//Set up TRUE muon Hist
//======================================================================

MnvH2D *h_2d_PZ_PT_TRUE            =    new MnvH2D("h_2d_PZ_PT_TRUE", "h_2d_PZ_PT_TRUE",Pzbin_vector.size()-1, Pzbin_vector.data() ,PTbin_vector.size()-1, PTbin_vector.data()  );
MnvH2D *h_2d_E_PZ_TRUE             =    new MnvH2D("h_2d_E_PZ_TRUE", "h_2d_E_PZ_TRUE", Ebin_vector.size()-1, Ebin_vector.data(),Pzbin_vector.size()-1, Pzbin_vector.data()  );
MnvH2D *h_2d_Theta_PZ_TRUE         =    new MnvH2D("h_2d_Theta_PZ_TRUE", "h_2d_Theta_PZ_TRUE", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),Pzbin_vector.size()-1, Pzbin_vector.data()  );
MnvH2D *h_2d_E_PT_TRUE             =    new MnvH2D("h_2d_E_PT_TRUE", "h_2d_E_PT_TRUE", Ebin_vector.size()-1, Ebin_vector.data(),PTbin_vector.size()-1, PTbin_vector.data()  );
MnvH2D *h_2d_Theta_PT_TRUE         =    new MnvH2D("h_2d_Theta_PT_TRUE", "h_2d_Theta_PT_TRUE", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),PTbin_vector.size()-1, PTbin_vector.data()  );
//MnvH2D *h_2d_Theta_PT_TRUE_RECO    =    new MnvH2D("h_2d_Theta_PT_TRUE_RECO", "h_2d_Theta_PT_TRUE_RECO", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),PTbin_vector.size()-1, PTbin_vector.data()  );

PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type> h_Muon_PZ_PT_Material =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type>(MaterialGroup_categories, "h_Muon_PZ_PT_Material",  Pzbin_vector , PTbin_vector ,"h_Muon_PZ_PT_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type> h_Muon_PZ_PT_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_Muon_PZ_PT_Interaction",  Pzbin_vector , PTbin_vector ,"h_Muon_PZ_PT_Interaction; [GeV];Events");
/////////////////////////////////////////////
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type> h_Muon_PZ_PT_Interaction_Daisy_0 =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_Muon_PZ_PT_Interaction_Daisy_0",  Pzbin_vector , PTbin_vector ,"h_Muon_PZ_PT_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type> h_Muon_PZ_PT_Interaction_Daisy_1 =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_Muon_PZ_PT_Interaction_Daisy_1",  Pzbin_vector , PTbin_vector ,"h_Muon_PZ_PT_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type> h_Muon_PZ_PT_Interaction_Daisy_2 =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_Muon_PZ_PT_Interaction_Daisy_2",  Pzbin_vector , PTbin_vector ,"h_Muon_PZ_PT_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type> h_Muon_PZ_PT_Interaction_Daisy_3 =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_Muon_PZ_PT_Interaction_Daisy_3",  Pzbin_vector , PTbin_vector ,"h_Muon_PZ_PT_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type> h_Muon_PZ_PT_Interaction_Daisy_4 =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_Muon_PZ_PT_Interaction_Daisy_4",  Pzbin_vector , PTbin_vector ,"h_Muon_PZ_PT_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type> h_Muon_PZ_PT_Interaction_Daisy_5 =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_Muon_PZ_PT_Interaction_Daisy_5",  Pzbin_vector , PTbin_vector ,"h_Muon_PZ_PT_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type> h_Muon_PZ_PT_Interaction_Daisy_6 =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_Muon_PZ_PT_Interaction_Daisy_6",  Pzbin_vector , PTbin_vector ,"h_Muon_PZ_PT_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type> h_Muon_PZ_PT_Interaction_Daisy_7 =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_Muon_PZ_PT_Interaction_Daisy_7",  Pzbin_vector , PTbin_vector ,"h_Muon_PZ_PT_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type> h_Muon_PZ_PT_Interaction_Daisy_8 =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_Muon_PZ_PT_Interaction_Daisy_8",  Pzbin_vector , PTbin_vector ,"h_Muon_PZ_PT_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type> h_Muon_PZ_PT_Interaction_Daisy_9 =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_Muon_PZ_PT_Interaction_Daisy_9",  Pzbin_vector , PTbin_vector ,"h_Muon_PZ_PT_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type> h_Muon_PZ_PT_Interaction_Daisy_10 =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_Muon_PZ_PT_Interaction_Daisy_10",  Pzbin_vector , PTbin_vector ,"h_Muon_PZ_PT_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type> h_Muon_PZ_PT_Interaction_Daisy_11 =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_Muon_PZ_PT_Interaction_Daisy_11",  Pzbin_vector , PTbin_vector ,"h_Muon_PZ_PT_Interaction; [GeV];Events");
std::map< FluxSlices, PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type>> h_Muon_PZ_PT_Interaction_Daisy_Map;

h_Muon_PZ_PT_Interaction_Daisy_Map.insert({kheliumdaisy0,  h_Muon_PZ_PT_Interaction_Daisy_0});
h_Muon_PZ_PT_Interaction_Daisy_Map.insert({kheliumdaisy1,  h_Muon_PZ_PT_Interaction_Daisy_1});
h_Muon_PZ_PT_Interaction_Daisy_Map.insert({kheliumdaisy2,  h_Muon_PZ_PT_Interaction_Daisy_2});
h_Muon_PZ_PT_Interaction_Daisy_Map.insert({kheliumdaisy3,  h_Muon_PZ_PT_Interaction_Daisy_3});
h_Muon_PZ_PT_Interaction_Daisy_Map.insert({kheliumdaisy4,  h_Muon_PZ_PT_Interaction_Daisy_4});
h_Muon_PZ_PT_Interaction_Daisy_Map.insert({kheliumdaisy5,  h_Muon_PZ_PT_Interaction_Daisy_5});
h_Muon_PZ_PT_Interaction_Daisy_Map.insert({kheliumdaisy6,  h_Muon_PZ_PT_Interaction_Daisy_6});
h_Muon_PZ_PT_Interaction_Daisy_Map.insert({kheliumdaisy7,  h_Muon_PZ_PT_Interaction_Daisy_7});
h_Muon_PZ_PT_Interaction_Daisy_Map.insert({kheliumdaisy8,  h_Muon_PZ_PT_Interaction_Daisy_8});
h_Muon_PZ_PT_Interaction_Daisy_Map.insert({kheliumdaisy9,  h_Muon_PZ_PT_Interaction_Daisy_9});
h_Muon_PZ_PT_Interaction_Daisy_Map.insert({kheliumdaisy10, h_Muon_PZ_PT_Interaction_Daisy_10});
h_Muon_PZ_PT_Interaction_Daisy_Map.insert({kheliumdaisy11, h_Muon_PZ_PT_Interaction_Daisy_11});
////////////
MnvH2D *h_Vertex_X_Y_Daisy_0  =   new MnvH2D("h_Vertex_X_Y_Daisy_0", "h_Vertex_X_Y_Daisy_0", Vertex_Xbins.size()-1, Vertex_Xbins.data(), Vertex_Ybins.size()-1, Vertex_Ybins.data());

MnvH2D *h_Vertex_X_Y_Daisy_1  =   new MnvH2D("h_Vertex_X_Y_Daisy_1", "h_Vertex_X_Y_Daisy_1", Vertex_Xbins.size()-1, Vertex_Xbins.data(), Vertex_Ybins.size()-1, Vertex_Ybins.data());
MnvH2D *h_Vertex_X_Y_Daisy_2  =   new MnvH2D("h_Vertex_X_Y_Daisy_2", "h_Vertex_X_Y_Daisy_2", Vertex_Xbins.size()-1, Vertex_Xbins.data(), Vertex_Ybins.size()-1, Vertex_Ybins.data());
MnvH2D *h_Vertex_X_Y_Daisy_3  =   new MnvH2D("h_Vertex_X_Y_Daisy_3", "h_Vertex_X_Y_Daisy_3", Vertex_Xbins.size()-1, Vertex_Xbins.data(), Vertex_Ybins.size()-1, Vertex_Ybins.data());
MnvH2D *h_Vertex_X_Y_Daisy_4  =   new MnvH2D("h_Vertex_X_Y_Daisy_4", "h_Vertex_X_Y_Daisy_4", Vertex_Xbins.size()-1, Vertex_Xbins.data(), Vertex_Ybins.size()-1, Vertex_Ybins.data());
MnvH2D *h_Vertex_X_Y_Daisy_5  =   new MnvH2D("h_Vertex_X_Y_Daisy_5", "h_Vertex_X_Y_Daisy_5", Vertex_Xbins.size()-1, Vertex_Xbins.data(), Vertex_Ybins.size()-1, Vertex_Ybins.data());
MnvH2D *h_Vertex_X_Y_Daisy_6  =   new MnvH2D("h_Vertex_X_Y_Daisy_6", "h_Vertex_X_Y_Daisy_6", Vertex_Xbins.size()-1, Vertex_Xbins.data(), Vertex_Ybins.size()-1, Vertex_Ybins.data());
MnvH2D *h_Vertex_X_Y_Daisy_7  =   new MnvH2D("h_Vertex_X_Y_Daisy_7", "h_Vertex_X_Y_Daisy_7", Vertex_Xbins.size()-1, Vertex_Xbins.data(), Vertex_Ybins.size()-1, Vertex_Ybins.data());
MnvH2D *h_Vertex_X_Y_Daisy_8  =   new MnvH2D("h_Vertex_X_Y_Daisy_8", "h_Vertex_X_Y_Daisy_8", Vertex_Xbins.size()-1, Vertex_Xbins.data(), Vertex_Ybins.size()-1, Vertex_Ybins.data());
MnvH2D *h_Vertex_X_Y_Daisy_9  =   new MnvH2D("h_Vertex_X_Y_Daisy_9", "h_Vertex_X_Y_Daisy_9", Vertex_Xbins.size()-1, Vertex_Xbins.data(), Vertex_Ybins.size()-1, Vertex_Ybins.data());
MnvH2D *h_Vertex_X_Y_Daisy_10  =   new MnvH2D("h_Vertex_X_Y_Daisy_10", "h_Vertex_X_Y_Daisy_10", Vertex_Xbins.size()-1, Vertex_Xbins.data(), Vertex_Ybins.size()-1, Vertex_Ybins.data());
MnvH2D *h_Vertex_X_Y_Daisy_11  =   new MnvH2D("h_Vertex_X_Y_Daisy_11", "h_Vertex_X_Y_Daisy_11", Vertex_Xbins.size()-1, Vertex_Xbins.data(), Vertex_Ybins.size()-1, Vertex_Ybins.data());


std::map< FluxSlices, PlotUtils::MnvH2D*> h_Vertex_X_Y_Daisy_Map;


h_Vertex_X_Y_Daisy_Map.insert({kheliumdaisy0,  h_Vertex_X_Y_Daisy_0});
h_Vertex_X_Y_Daisy_Map.insert({kheliumdaisy1,  h_Vertex_X_Y_Daisy_1});
h_Vertex_X_Y_Daisy_Map.insert({kheliumdaisy2,  h_Vertex_X_Y_Daisy_2});
h_Vertex_X_Y_Daisy_Map.insert({kheliumdaisy3,  h_Vertex_X_Y_Daisy_3});
h_Vertex_X_Y_Daisy_Map.insert({kheliumdaisy4,  h_Vertex_X_Y_Daisy_4});
h_Vertex_X_Y_Daisy_Map.insert({kheliumdaisy5,  h_Vertex_X_Y_Daisy_5});
h_Vertex_X_Y_Daisy_Map.insert({kheliumdaisy6,  h_Vertex_X_Y_Daisy_6});
h_Vertex_X_Y_Daisy_Map.insert({kheliumdaisy7,  h_Vertex_X_Y_Daisy_7});
h_Vertex_X_Y_Daisy_Map.insert({kheliumdaisy8,  h_Vertex_X_Y_Daisy_8});
h_Vertex_X_Y_Daisy_Map.insert({kheliumdaisy9,  h_Vertex_X_Y_Daisy_9});
h_Vertex_X_Y_Daisy_Map.insert({kheliumdaisy10, h_Vertex_X_Y_Daisy_10});
h_Vertex_X_Y_Daisy_Map.insert({kheliumdaisy11, h_Vertex_X_Y_Daisy_11});


//////////////////////////////////////////////
PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type> h_Muon_PZ_PT_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type>(ParticleGroup_reduced_categories, "h_Muon_PZ_PT_Particle",  Pzbin_vector , PTbin_vector ,"h_Muon_PZ_PT_Particle; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type> h_Muon_E_theta_Material =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type>(MaterialGroup_categories, "h_Muon_E_theta_Material",  Ebin_1Dvector , MuonThetabin_vector ,"E_theta_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type> h_Muon_E_theta_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_Muon_E_theta_Interaction",  Ebin_vector , MuonThetabin_vector ,"E_theta_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type> h_Muon_E_theta_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type>(ParticleGroup_reduced_categories, "h_Muon_E_theta_Particle",  Ebin_vector , MuonThetabin_vector ,"E_theta_Particle; [GeV];Events");

////////////////
// 1D
////////////////

PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE_TRUE("h_MuonE_TRUE", "Muon_{E} NEW Method", Ebin_1Dvector , error_bands);
//======================================================================
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE_TRUE_Daisy_0("h_MuonE_TRUE_Daisy_0", "Muon_{E} NEW Method", Ebin_1Dvector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE_TRUE_Daisy_1("h_MuonE_TRUE_Daisy_1", "Muon_{E} NEW Method", Ebin_1Dvector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE_TRUE_Daisy_2("h_MuonE_TRUE_Daisy_2", "Muon_{E} NEW Method", Ebin_1Dvector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE_TRUE_Daisy_3("h_MuonE_TRUE_Daisy_3", "Muon_{E} NEW Method", Ebin_1Dvector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE_TRUE_Daisy_4("h_MuonE_TRUE_Daisy_4", "Muon_{E} NEW Method", Ebin_1Dvector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE_TRUE_Daisy_5("h_MuonE_TRUE_Daisy_5", "Muon_{E} NEW Method", Ebin_1Dvector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE_TRUE_Daisy_6("h_MuonE_TRUE_Daisy_6", "Muon_{E} NEW Method", Ebin_1Dvector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE_TRUE_Daisy_7("h_MuonE_TRUE_Daisy_7", "Muon_{E} NEW Method", Ebin_1Dvector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE_TRUE_Daisy_8("h_MuonE_TRUE_Daisy_8", "Muon_{E} NEW Method", Ebin_1Dvector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE_TRUE_Daisy_9("h_MuonE_TRUE_Daisy_9", "Muon_{E} NEW Method", Ebin_1Dvector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE_TRUE_Daisy_10("h_MuonE_TRUE_Daisy_10", "Muon_{E} NEW Method", Ebin_1Dvector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE_TRUE_Daisy_11("h_MuonE_TRUE_Daisy_11", "Muon_{E} NEW Method", Ebin_1Dvector , error_bands);
//======================================================================
std::map< FluxSlices, PlotUtils::HistWrapper<HeliumCVUniverse>> h_MuonE_Daisy_Map;
h_MuonE_Daisy_Map.insert({kheliumdaisy0,  h_MuonE_TRUE_Daisy_0});
h_MuonE_Daisy_Map.insert({kheliumdaisy1,  h_MuonE_TRUE_Daisy_1});
h_MuonE_Daisy_Map.insert({kheliumdaisy2,  h_MuonE_TRUE_Daisy_2});
h_MuonE_Daisy_Map.insert({kheliumdaisy3,  h_MuonE_TRUE_Daisy_3});
h_MuonE_Daisy_Map.insert({kheliumdaisy4,  h_MuonE_TRUE_Daisy_4});
h_MuonE_Daisy_Map.insert({kheliumdaisy5,  h_MuonE_TRUE_Daisy_5});
h_MuonE_Daisy_Map.insert({kheliumdaisy6,  h_MuonE_TRUE_Daisy_6});
h_MuonE_Daisy_Map.insert({kheliumdaisy7,  h_MuonE_TRUE_Daisy_7});
h_MuonE_Daisy_Map.insert({kheliumdaisy8,  h_MuonE_TRUE_Daisy_8});
h_MuonE_Daisy_Map.insert({kheliumdaisy9,  h_MuonE_TRUE_Daisy_9});
h_MuonE_Daisy_Map.insert({kheliumdaisy10, h_MuonE_TRUE_Daisy_10});
h_MuonE_Daisy_Map.insert({kheliumdaisy11, h_MuonE_TRUE_Daisy_11});
//======================================================================
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPZ_TRUE("h_MuonPZ_TRUE", "Muon_{PZ} NEW Method",             Pzbin_1Dvector , error_bands);
//======================================================================
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPZ_TRUE_Daisy_0(  "h_MuonPZ_TRUE_Daisy_0",   "Muon_{PZ} ", Pzbin_1Dvector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPZ_TRUE_Daisy_1(  "h_MuonPZ_TRUE_Daisy_1",   "Muon_{PZ} ", Pzbin_1Dvector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPZ_TRUE_Daisy_2(  "h_MuonPZ_TRUE_Daisy_2",   "Muon_{PZ} ", Pzbin_1Dvector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPZ_TRUE_Daisy_3(  "h_MuonPZ_TRUE_Daisy_3",   "Muon_{PZ} ", Pzbin_1Dvector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPZ_TRUE_Daisy_4(  "h_MuonPZ_TRUE_Daisy_4",   "Muon_{PZ} ", Pzbin_1Dvector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPZ_TRUE_Daisy_5(  "h_MuonPZ_TRUE_Daisy_5",   "Muon_{PZ} ", Pzbin_1Dvector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPZ_TRUE_Daisy_6(  "h_MuonPZ_TRUE_Daisy_6",   "Muon_{PZ} ", Pzbin_1Dvector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPZ_TRUE_Daisy_7(  "h_MuonPZ_TRUE_Daisy_7",   "Muon_{PZ} ", Pzbin_1Dvector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPZ_TRUE_Daisy_8(  "h_MuonPZ_TRUE_Daisy_8",   "Muon_{PZ} ", Pzbin_1Dvector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPZ_TRUE_Daisy_9(  "h_MuonPZ_TRUE_Daisy_9",   "Muon_{PZ} ", Pzbin_1Dvector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPZ_TRUE_Daisy_10("h_MuonPZ_TRUE_Daisy_10", "Muon_{PZ}   ", Pzbin_1Dvector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPZ_TRUE_Daisy_11("h_MuonPZ_TRUE_Daisy_11", "Muon_{PZ}   ", Pzbin_1Dvector , error_bands);
//======================================================================
//======================================================================
std::map< FluxSlices, PlotUtils::HistWrapper<HeliumCVUniverse>> h_MuonPZ_Daisy_Map;
h_MuonPZ_Daisy_Map.insert({kheliumdaisy0,  h_MuonPZ_TRUE_Daisy_0});
h_MuonPZ_Daisy_Map.insert({kheliumdaisy1,  h_MuonPZ_TRUE_Daisy_1});
h_MuonPZ_Daisy_Map.insert({kheliumdaisy2,  h_MuonPZ_TRUE_Daisy_2});
h_MuonPZ_Daisy_Map.insert({kheliumdaisy3,  h_MuonPZ_TRUE_Daisy_3});
h_MuonPZ_Daisy_Map.insert({kheliumdaisy4,  h_MuonPZ_TRUE_Daisy_4});
h_MuonPZ_Daisy_Map.insert({kheliumdaisy5,  h_MuonPZ_TRUE_Daisy_5});
h_MuonPZ_Daisy_Map.insert({kheliumdaisy6,  h_MuonPZ_TRUE_Daisy_6});
h_MuonPZ_Daisy_Map.insert({kheliumdaisy7,  h_MuonPZ_TRUE_Daisy_7});
h_MuonPZ_Daisy_Map.insert({kheliumdaisy8,  h_MuonPZ_TRUE_Daisy_8});
h_MuonPZ_Daisy_Map.insert({kheliumdaisy9,  h_MuonPZ_TRUE_Daisy_9});
h_MuonPZ_Daisy_Map.insert({kheliumdaisy10, h_MuonPZ_TRUE_Daisy_10});
h_MuonPZ_Daisy_Map.insert({kheliumdaisy11, h_MuonPZ_TRUE_Daisy_11});
//======================================================================
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPT_TRUE("h_MuonPT_TRUE", "Muon_{PT} NEW Method",             PTbin_1Dvector , error_bands);
//======================================================================
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPT_TRUE_Daisy_0(  "h_MuonPT_TRUE_Daisy_0",   "Muon_{PT}[GeV]", PTbin_1Dvector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPT_TRUE_Daisy_1(  "h_MuonPT_TRUE_Daisy_1",   "Muon_{PT}[GeV]", PTbin_1Dvector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPT_TRUE_Daisy_2(  "h_MuonPT_TRUE_Daisy_2",   "Muon_{PT}[GeV]", PTbin_1Dvector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPT_TRUE_Daisy_3(  "h_MuonPT_TRUE_Daisy_3",   "Muon_{PT}[GeV]", PTbin_1Dvector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPT_TRUE_Daisy_4(  "h_MuonPT_TRUE_Daisy_4",   "Muon_{PT}[GeV]", PTbin_1Dvector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPT_TRUE_Daisy_5(  "h_MuonPT_TRUE_Daisy_5",   "Muon_{PT}[GeV]", PTbin_1Dvector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPT_TRUE_Daisy_6(  "h_MuonPT_TRUE_Daisy_6",   "Muon_{PT}[GeV]", PTbin_1Dvector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPT_TRUE_Daisy_7(  "h_MuonPT_TRUE_Daisy_7",   "Muon_{PT}[GeV]", PTbin_1Dvector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPT_TRUE_Daisy_8(  "h_MuonPT_TRUE_Daisy_8",   "Muon_{PT}[GeV]", PTbin_1Dvector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPT_TRUE_Daisy_9(  "h_MuonPT_TRUE_Daisy_9",   "Muon_{PT}[GeV]", PTbin_1Dvector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPT_TRUE_Daisy_10( "h_MuonPT_TRUE_Daisy_10",  "Muon_{PT}[GeV]", PTbin_1Dvector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPT_TRUE_Daisy_11( "h_MuonPT_TRUE_Daisy_11",  "Muon_{PT}[GeV]", PTbin_1Dvector , error_bands);
//======================================================================
//======================================================================
std::map< FluxSlices, PlotUtils::HistWrapper<HeliumCVUniverse>> h_MuonPT_Daisy_Map;
h_MuonPT_Daisy_Map.insert({kheliumdaisy0,  h_MuonPT_TRUE_Daisy_0});
h_MuonPT_Daisy_Map.insert({kheliumdaisy1,  h_MuonPT_TRUE_Daisy_1});
h_MuonPT_Daisy_Map.insert({kheliumdaisy2,  h_MuonPT_TRUE_Daisy_2});
h_MuonPT_Daisy_Map.insert({kheliumdaisy3,  h_MuonPT_TRUE_Daisy_3});
h_MuonPT_Daisy_Map.insert({kheliumdaisy4,  h_MuonPT_TRUE_Daisy_4});
h_MuonPT_Daisy_Map.insert({kheliumdaisy5,  h_MuonPT_TRUE_Daisy_5});
h_MuonPT_Daisy_Map.insert({kheliumdaisy6,  h_MuonPT_TRUE_Daisy_6});
h_MuonPT_Daisy_Map.insert({kheliumdaisy7,  h_MuonPT_TRUE_Daisy_7});
h_MuonPT_Daisy_Map.insert({kheliumdaisy8,  h_MuonPT_TRUE_Daisy_8});
h_MuonPT_Daisy_Map.insert({kheliumdaisy9,  h_MuonPT_TRUE_Daisy_9});
h_MuonPT_Daisy_Map.insert({kheliumdaisy10, h_MuonPT_TRUE_Daisy_10});
h_MuonPT_Daisy_Map.insert({kheliumdaisy11, h_MuonPT_TRUE_Daisy_11});
//======================================================================
//======================================================================
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonTheta_TRUE("h_MuonTheta_TRUE", "MuonTheta [Deg]",            MuonThetabin_vector , error_bands);
//======================================================================
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonTheta_TRUE_Daisy_0(  "h_MuonTheta_TRUE_Daisy_0",   "MuonTheta", MuonThetabin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonTheta_TRUE_Daisy_1(  "h_MuonTheta_TRUE_Daisy_1",   "MuonTheta", MuonThetabin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonTheta_TRUE_Daisy_2(  "h_MuonTheta_TRUE_Daisy_2",   "MuonTheta", MuonThetabin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonTheta_TRUE_Daisy_3(  "h_MuonTheta_TRUE_Daisy_3",   "MuonTheta", MuonThetabin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonTheta_TRUE_Daisy_4(  "h_MuonTheta_TRUE_Daisy_4",   "MuonTheta", MuonThetabin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonTheta_TRUE_Daisy_5(  "h_MuonTheta_TRUE_Daisy_5",   "MuonTheta", MuonThetabin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonTheta_TRUE_Daisy_6(  "h_MuonTheta_TRUE_Daisy_6",   "MuonTheta", MuonThetabin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonTheta_TRUE_Daisy_7(  "h_MuonTheta_TRUE_Daisy_7",   "MuonTheta", MuonThetabin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonTheta_TRUE_Daisy_8(  "h_MuonTheta_TRUE_Daisy_8",   "MuonTheta", MuonThetabin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonTheta_TRUE_Daisy_9(  "h_MuonTheta_TRUE_Daisy_9",   "MuonTheta", MuonThetabin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonTheta_TRUE_Daisy_10( "h_MuonTheta_TRUE_Daisy_10",  "MuonTheta", MuonThetabin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonTheta_TRUE_Daisy_11( "h_MuonTheta_TRUE_Daisy_11",  "MuonTheta", MuonThetabin_vector , error_bands);
//======================================================================
//======================================================================
std::map< FluxSlices, PlotUtils::HistWrapper<HeliumCVUniverse>> h_MuonTheta_Daisy_Map;
h_MuonTheta_Daisy_Map.insert({kheliumdaisy0,  h_MuonTheta_TRUE_Daisy_0});
h_MuonTheta_Daisy_Map.insert({kheliumdaisy1,  h_MuonTheta_TRUE_Daisy_1});
h_MuonTheta_Daisy_Map.insert({kheliumdaisy2,  h_MuonTheta_TRUE_Daisy_2});
h_MuonTheta_Daisy_Map.insert({kheliumdaisy3,  h_MuonTheta_TRUE_Daisy_3});
h_MuonTheta_Daisy_Map.insert({kheliumdaisy4,  h_MuonTheta_TRUE_Daisy_4});
h_MuonTheta_Daisy_Map.insert({kheliumdaisy5,  h_MuonTheta_TRUE_Daisy_5});
h_MuonTheta_Daisy_Map.insert({kheliumdaisy6,  h_MuonTheta_TRUE_Daisy_6});
h_MuonTheta_Daisy_Map.insert({kheliumdaisy7,  h_MuonTheta_TRUE_Daisy_7});
h_MuonTheta_Daisy_Map.insert({kheliumdaisy8,  h_MuonTheta_TRUE_Daisy_8});
h_MuonTheta_Daisy_Map.insert({kheliumdaisy9,  h_MuonTheta_TRUE_Daisy_9});
h_MuonTheta_Daisy_Map.insert({kheliumdaisy10, h_MuonTheta_TRUE_Daisy_10});
h_MuonTheta_Daisy_Map.insert({kheliumdaisy11, h_MuonTheta_TRUE_Daisy_11});
//======================================================================
//======================================================================
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Theta_TRUE("h_secTrk_Theta_TRUE", "h_secTrk_Theta_TRUE",  Vertex_secondTrkTheta_bins , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_MuonE_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_reduced_categories, "h_MuonE_TRUE_Particle", Ebin_1Dvector ,"MuonE_TRUE_Particle; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_MuonPZ_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_reduced_categories, "h_MuonPZ_TRUE_Particle", Pzbin_1Dvector ,"h_MuonPZ_TRUE_Particle; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_MuonPT_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_reduced_categories, "h_MuonPT_TRUE_Particle", PTbin_1Dvector ,"h_MuonPT_TRUE_Particle; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_MuonTheta_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_reduced_categories, "h_MuonTheta_TRUE_Particle", MuonThetabin_vector ,"h_MuonTheta_TRUE_Particle; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonE_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonE_TRUE_Interaction", Ebin_1Dvector ,"MuonE_TRUE_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonE_TRUE_Interaction_Daisy_0 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonE_TRUE_Interaction_Daisy_0", Ebin_1Dvector ,"MuonE_TRUE_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonE_TRUE_Interaction_Daisy_1 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonE_TRUE_Interaction_Daisy_1", Ebin_1Dvector ,"MuonE_TRUE_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonE_TRUE_Interaction_Daisy_2 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonE_TRUE_Interaction_Daisy_2", Ebin_1Dvector ,"MuonE_TRUE_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonE_TRUE_Interaction_Daisy_3 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonE_TRUE_Interaction_Daisy_3", Ebin_1Dvector ,"MuonE_TRUE_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonE_TRUE_Interaction_Daisy_4 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonE_TRUE_Interaction_Daisy_4", Ebin_1Dvector ,"MuonE_TRUE_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonE_TRUE_Interaction_Daisy_5 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonE_TRUE_Interaction_Daisy_5", Ebin_1Dvector ,"MuonE_TRUE_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonE_TRUE_Interaction_Daisy_6 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonE_TRUE_Interaction_Daisy_6", Ebin_1Dvector ,"MuonE_TRUE_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonE_TRUE_Interaction_Daisy_7 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonE_TRUE_Interaction_Daisy_7", Ebin_1Dvector ,"MuonE_TRUE_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonE_TRUE_Interaction_Daisy_8 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonE_TRUE_Interaction_Daisy_8", Ebin_1Dvector ,"MuonE_TRUE_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonE_TRUE_Interaction_Daisy_9 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonE_TRUE_Interaction_Daisy_9", Ebin_1Dvector ,"MuonE_TRUE_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonE_TRUE_Interaction_Daisy_10 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonE_TRUE_Interaction_Daisy_10", Ebin_1Dvector ,"MuonE_TRUE_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonE_TRUE_Interaction_Daisy_11 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonE_TRUE_Interaction_Daisy_11", Ebin_1Dvector ,"MuonE_TRUE_Interaction; [GeV];Events");
///////////////////////////////////////
std::map< FluxSlices, PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>> h_MuonE_Interaction_Daisy_Map;

h_MuonE_Interaction_Daisy_Map.insert({kheliumdaisy0,  h_MuonE_TRUE_Interaction_Daisy_0});
h_MuonE_Interaction_Daisy_Map.insert({kheliumdaisy1,  h_MuonE_TRUE_Interaction_Daisy_1});
h_MuonE_Interaction_Daisy_Map.insert({kheliumdaisy2,  h_MuonE_TRUE_Interaction_Daisy_2});
h_MuonE_Interaction_Daisy_Map.insert({kheliumdaisy3,  h_MuonE_TRUE_Interaction_Daisy_3});
h_MuonE_Interaction_Daisy_Map.insert({kheliumdaisy4,  h_MuonE_TRUE_Interaction_Daisy_4});
h_MuonE_Interaction_Daisy_Map.insert({kheliumdaisy5,  h_MuonE_TRUE_Interaction_Daisy_5});
h_MuonE_Interaction_Daisy_Map.insert({kheliumdaisy6,  h_MuonE_TRUE_Interaction_Daisy_6});
h_MuonE_Interaction_Daisy_Map.insert({kheliumdaisy7,  h_MuonE_TRUE_Interaction_Daisy_7});
h_MuonE_Interaction_Daisy_Map.insert({kheliumdaisy8,  h_MuonE_TRUE_Interaction_Daisy_8});
h_MuonE_Interaction_Daisy_Map.insert({kheliumdaisy9,  h_MuonE_TRUE_Interaction_Daisy_9});
h_MuonE_Interaction_Daisy_Map.insert({kheliumdaisy10, h_MuonE_TRUE_Interaction_Daisy_10});
h_MuonE_Interaction_Daisy_Map.insert({kheliumdaisy11, h_MuonE_TRUE_Interaction_Daisy_11});
///////////////////////////////////////
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonPZ_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonPZ_TRUE_Interaction", Pzbin_1Dvector ,"h_MuonPZ_TRUE_Interaction; [GeV];Events");
///////////////////////////////////////
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonPZ_TRUE_Interaction_Daisy_0 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonPZ_TRUE_Interaction_Daisy_0", Pzbin_1Dvector ,"MuonE_TRUE_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonPZ_TRUE_Interaction_Daisy_1 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonPZ_TRUE_Interaction_Daisy_1", Pzbin_1Dvector ,"MuonE_TRUE_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonPZ_TRUE_Interaction_Daisy_2 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonPZ_TRUE_Interaction_Daisy_2", Pzbin_1Dvector ,"MuonE_TRUE_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonPZ_TRUE_Interaction_Daisy_3 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonPZ_TRUE_Interaction_Daisy_3", Pzbin_1Dvector ,"MuonE_TRUE_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonPZ_TRUE_Interaction_Daisy_4 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonPZ_TRUE_Interaction_Daisy_4", Pzbin_1Dvector ,"MuonE_TRUE_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonPZ_TRUE_Interaction_Daisy_5 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonPZ_TRUE_Interaction_Daisy_5", Pzbin_1Dvector ,"MuonE_TRUE_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonPZ_TRUE_Interaction_Daisy_6 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonPZ_TRUE_Interaction_Daisy_6", Pzbin_1Dvector ,"MuonE_TRUE_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonPZ_TRUE_Interaction_Daisy_7 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonPZ_TRUE_Interaction_Daisy_7", Pzbin_1Dvector ,"MuonE_TRUE_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonPZ_TRUE_Interaction_Daisy_8 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonPZ_TRUE_Interaction_Daisy_8", Pzbin_1Dvector ,"MuonE_TRUE_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonPZ_TRUE_Interaction_Daisy_9 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonPZ_TRUE_Interaction_Daisy_9", Pzbin_1Dvector ,"MuonE_TRUE_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonPZ_TRUE_Interaction_Daisy_10 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonPZ_TRUE_Interaction_Daisy_10", Pzbin_1Dvector ,"MuonE_TRUE_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonPZ_TRUE_Interaction_Daisy_11 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonPZ_TRUE_Interaction_Daisy_11", Pzbin_1Dvector ,"MuonE_TRUE_Interaction; [GeV];Events");
///////////////////////////////////////
std::map< FluxSlices, PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>> h_MuonPZ_Interaction_Daisy_Map;

h_MuonPZ_Interaction_Daisy_Map.insert({kheliumdaisy0,  h_MuonPZ_TRUE_Interaction_Daisy_0});
h_MuonPZ_Interaction_Daisy_Map.insert({kheliumdaisy1,  h_MuonPZ_TRUE_Interaction_Daisy_1});
h_MuonPZ_Interaction_Daisy_Map.insert({kheliumdaisy2,  h_MuonPZ_TRUE_Interaction_Daisy_2});
h_MuonPZ_Interaction_Daisy_Map.insert({kheliumdaisy3,  h_MuonPZ_TRUE_Interaction_Daisy_3});
h_MuonPZ_Interaction_Daisy_Map.insert({kheliumdaisy4,  h_MuonPZ_TRUE_Interaction_Daisy_4});
h_MuonPZ_Interaction_Daisy_Map.insert({kheliumdaisy5,  h_MuonPZ_TRUE_Interaction_Daisy_5});
h_MuonPZ_Interaction_Daisy_Map.insert({kheliumdaisy6,  h_MuonPZ_TRUE_Interaction_Daisy_6});
h_MuonPZ_Interaction_Daisy_Map.insert({kheliumdaisy7,  h_MuonPZ_TRUE_Interaction_Daisy_7});
h_MuonPZ_Interaction_Daisy_Map.insert({kheliumdaisy8,  h_MuonPZ_TRUE_Interaction_Daisy_8});
h_MuonPZ_Interaction_Daisy_Map.insert({kheliumdaisy9,  h_MuonPZ_TRUE_Interaction_Daisy_9});
h_MuonPZ_Interaction_Daisy_Map.insert({kheliumdaisy10, h_MuonPZ_TRUE_Interaction_Daisy_10});
h_MuonPZ_Interaction_Daisy_Map.insert({kheliumdaisy11, h_MuonPZ_TRUE_Interaction_Daisy_11});




PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonPT_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonPT_TRUE_Interaction", PTbin_1Dvector ,"h_MuonPT_TRUE_Interaction; [GeV];Events");
/////////////////////////////////////
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonPT_TRUE_Interaction_Daisy_0 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonPT_TRUE_Interaction_Daisy_0", PTbin_1Dvector ,"MuonE_TRUE_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonPT_TRUE_Interaction_Daisy_1 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonPT_TRUE_Interaction_Daisy_1", PTbin_1Dvector ,"MuonE_TRUE_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonPT_TRUE_Interaction_Daisy_2 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonPT_TRUE_Interaction_Daisy_2", PTbin_1Dvector ,"MuonE_TRUE_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonPT_TRUE_Interaction_Daisy_3 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonPT_TRUE_Interaction_Daisy_3", PTbin_1Dvector ,"MuonE_TRUE_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonPT_TRUE_Interaction_Daisy_4 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonPT_TRUE_Interaction_Daisy_4", PTbin_1Dvector ,"MuonE_TRUE_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonPT_TRUE_Interaction_Daisy_5 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonPT_TRUE_Interaction_Daisy_5", PTbin_1Dvector ,"MuonE_TRUE_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonPT_TRUE_Interaction_Daisy_6 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonPT_TRUE_Interaction_Daisy_6", PTbin_1Dvector ,"MuonE_TRUE_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonPT_TRUE_Interaction_Daisy_7 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonPT_TRUE_Interaction_Daisy_7", PTbin_1Dvector ,"MuonE_TRUE_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonPT_TRUE_Interaction_Daisy_8 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonPT_TRUE_Interaction_Daisy_8", PTbin_1Dvector ,"MuonE_TRUE_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonPT_TRUE_Interaction_Daisy_9 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonPT_TRUE_Interaction_Daisy_9", PTbin_1Dvector ,"MuonE_TRUE_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonPT_TRUE_Interaction_Daisy_10 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonPT_TRUE_Interaction_Daisy_10", PTbin_1Dvector ,"MuonE_TRUE_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonPT_TRUE_Interaction_Daisy_11 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonPT_TRUE_Interaction_Daisy_11", PTbin_1Dvector ,"MuonE_TRUE_Interaction; [GeV];Events");
///////////////////////////////////////
std::map< FluxSlices, PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>> h_MuonPT_Interaction_Daisy_Map;

h_MuonPT_Interaction_Daisy_Map.insert({kheliumdaisy0,  h_MuonPT_TRUE_Interaction_Daisy_0});
h_MuonPT_Interaction_Daisy_Map.insert({kheliumdaisy1,  h_MuonPT_TRUE_Interaction_Daisy_1});
h_MuonPT_Interaction_Daisy_Map.insert({kheliumdaisy2,  h_MuonPT_TRUE_Interaction_Daisy_2});
h_MuonPT_Interaction_Daisy_Map.insert({kheliumdaisy3,  h_MuonPT_TRUE_Interaction_Daisy_3});
h_MuonPT_Interaction_Daisy_Map.insert({kheliumdaisy4,  h_MuonPT_TRUE_Interaction_Daisy_4});
h_MuonPT_Interaction_Daisy_Map.insert({kheliumdaisy5,  h_MuonPT_TRUE_Interaction_Daisy_5});
h_MuonPT_Interaction_Daisy_Map.insert({kheliumdaisy6,  h_MuonPT_TRUE_Interaction_Daisy_6});
h_MuonPT_Interaction_Daisy_Map.insert({kheliumdaisy7,  h_MuonPT_TRUE_Interaction_Daisy_7});
h_MuonPT_Interaction_Daisy_Map.insert({kheliumdaisy8,  h_MuonPT_TRUE_Interaction_Daisy_8});
h_MuonPT_Interaction_Daisy_Map.insert({kheliumdaisy9,  h_MuonPT_TRUE_Interaction_Daisy_9});
h_MuonPT_Interaction_Daisy_Map.insert({kheliumdaisy10, h_MuonPT_TRUE_Interaction_Daisy_10});
h_MuonPT_Interaction_Daisy_Map.insert({kheliumdaisy11, h_MuonPT_TRUE_Interaction_Daisy_11});
///////////////////////////////////////
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonTheta_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonTheta_TRUE_Interaction", MuonThetabin_vector ,"h_MuonTheta_TRUE_Interaction; [GeV];Events");
///////////////////////////////////////
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonTheta_TRUE_Interaction_Daisy_0 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonTheta_TRUE_Interaction_Daisy_0", MuonThetabin_vector ,"MuonE_TRUE_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonTheta_TRUE_Interaction_Daisy_1 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonTheta_TRUE_Interaction_Daisy_1", MuonThetabin_vector ,"MuonE_TRUE_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonTheta_TRUE_Interaction_Daisy_2 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonTheta_TRUE_Interaction_Daisy_2", MuonThetabin_vector ,"MuonE_TRUE_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonTheta_TRUE_Interaction_Daisy_3 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonTheta_TRUE_Interaction_Daisy_3", MuonThetabin_vector ,"MuonE_TRUE_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonTheta_TRUE_Interaction_Daisy_4 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonTheta_TRUE_Interaction_Daisy_4", MuonThetabin_vector ,"MuonE_TRUE_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonTheta_TRUE_Interaction_Daisy_5 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonTheta_TRUE_Interaction_Daisy_5", MuonThetabin_vector ,"MuonE_TRUE_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonTheta_TRUE_Interaction_Daisy_6 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonTheta_TRUE_Interaction_Daisy_6", MuonThetabin_vector ,"MuonE_TRUE_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonTheta_TRUE_Interaction_Daisy_7 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonTheta_TRUE_Interaction_Daisy_7", MuonThetabin_vector ,"MuonE_TRUE_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonTheta_TRUE_Interaction_Daisy_8 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonTheta_TRUE_Interaction_Daisy_8", MuonThetabin_vector ,"MuonE_TRUE_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonTheta_TRUE_Interaction_Daisy_9 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonTheta_TRUE_Interaction_Daisy_9", MuonThetabin_vector ,"MuonE_TRUE_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonTheta_TRUE_Interaction_Daisy_10 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonTheta_TRUE_Interaction_Daisy_10", MuonThetabin_vector ,"MuonE_TRUE_Interaction; [GeV];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonTheta_TRUE_Interaction_Daisy_11 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonTheta_TRUE_Interaction_Daisy_11", MuonThetabin_vector ,"MuonE_TRUE_Interaction; [GeV];Events");
////////////////

///////////////////////////////////////
std::map< FluxSlices, PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>> h_MuonTheta_Interaction_Daisy_Map;

h_MuonTheta_Interaction_Daisy_Map.insert({kheliumdaisy0,  h_MuonTheta_TRUE_Interaction_Daisy_0});
h_MuonTheta_Interaction_Daisy_Map.insert({kheliumdaisy1,  h_MuonTheta_TRUE_Interaction_Daisy_1});
h_MuonTheta_Interaction_Daisy_Map.insert({kheliumdaisy2,  h_MuonTheta_TRUE_Interaction_Daisy_2});
h_MuonTheta_Interaction_Daisy_Map.insert({kheliumdaisy3,  h_MuonTheta_TRUE_Interaction_Daisy_3});
h_MuonTheta_Interaction_Daisy_Map.insert({kheliumdaisy4,  h_MuonTheta_TRUE_Interaction_Daisy_4});
h_MuonTheta_Interaction_Daisy_Map.insert({kheliumdaisy5,  h_MuonTheta_TRUE_Interaction_Daisy_5});
h_MuonTheta_Interaction_Daisy_Map.insert({kheliumdaisy6,  h_MuonTheta_TRUE_Interaction_Daisy_6});
h_MuonTheta_Interaction_Daisy_Map.insert({kheliumdaisy7,  h_MuonTheta_TRUE_Interaction_Daisy_7});
h_MuonTheta_Interaction_Daisy_Map.insert({kheliumdaisy8,  h_MuonTheta_TRUE_Interaction_Daisy_8});
h_MuonTheta_Interaction_Daisy_Map.insert({kheliumdaisy9,  h_MuonTheta_TRUE_Interaction_Daisy_9});
h_MuonTheta_Interaction_Daisy_Map.insert({kheliumdaisy10, h_MuonTheta_TRUE_Interaction_Daisy_10});
h_MuonTheta_Interaction_Daisy_Map.insert({kheliumdaisy11, h_MuonTheta_TRUE_Interaction_Daisy_11});

////////////////

PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_PZ_PT_TRUE("h_Muon_PZ_PT_TRUE",    "h_Muon_PZ_PT_TRUE",         Pzbin_vector, PTbin_vector,        error_bands);
//======================================================================
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_PZ_PT_TRUE_Daisy_0("h_Muon_PZ_PT_TRUE_Daisy_0",    "h_Muon_PZ_PT_TRUE_Daisy_0",         Pzbin_vector, PTbin_vector,        error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_PZ_PT_TRUE_Daisy_1("h_Muon_PZ_PT_TRUE_Daisy_1",    "h_Muon_PZ_PT_TRUE_Daisy_1",         Pzbin_vector, PTbin_vector,        error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_PZ_PT_TRUE_Daisy_2("h_Muon_PZ_PT_TRUE_Daisy_2",    "h_Muon_PZ_PT_TRUE_Daisy_2",         Pzbin_vector, PTbin_vector,        error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_PZ_PT_TRUE_Daisy_3("h_Muon_PZ_PT_TRUE_Daisy_3",    "h_Muon_PZ_PT_TRUE_Daisy_3",         Pzbin_vector, PTbin_vector,        error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_PZ_PT_TRUE_Daisy_4("h_Muon_PZ_PT_TRUE_Daisy_4",    "h_Muon_PZ_PT_TRUE_Daisy_4",         Pzbin_vector, PTbin_vector,        error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_PZ_PT_TRUE_Daisy_5("h_Muon_PZ_PT_TRUE_Daisy_5",    "h_Muon_PZ_PT_TRUE_Daisy_5",         Pzbin_vector, PTbin_vector,        error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_PZ_PT_TRUE_Daisy_6("h_Muon_PZ_PT_TRUE_Daisy_6",    "h_Muon_PZ_PT_TRUE_Daisy_6",         Pzbin_vector, PTbin_vector,        error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_PZ_PT_TRUE_Daisy_7("h_Muon_PZ_PT_TRUE_Daisy_7",    "h_Muon_PZ_PT_TRUE_Daisy_7",         Pzbin_vector, PTbin_vector,        error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_PZ_PT_TRUE_Daisy_8("h_Muon_PZ_PT_TRUE_Daisy_8",    "h_Muon_PZ_PT_TRUE_Daisy_8",         Pzbin_vector, PTbin_vector,        error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_PZ_PT_TRUE_Daisy_9("h_Muon_PZ_PT_TRUE_Daisy_9",    "h_Muon_PZ_PT_TRUE_Daisy_9",         Pzbin_vector, PTbin_vector,        error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_PZ_PT_TRUE_Daisy_10("h_Muon_PZ_PT_TRUE_Daisy_10",    "h_Muon_PZ_PT_TRUE_Daisy_10",         Pzbin_vector, PTbin_vector,        error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_PZ_PT_TRUE_Daisy_11("h_Muon_PZ_PT_TRUE_Daisy_11",    "h_Muon_PZ_PT_TRUE_Daisy_11",         Pzbin_vector, PTbin_vector,        error_bands);
//======================================================================
//======================================================================
//======================================================================
std::map< FluxSlices, PlotUtils::Hist2DWrapper<HeliumCVUniverse>> h_Muon_PZ_PT_TRUE_Daisy_Map;
h_Muon_PZ_PT_TRUE_Daisy_Map.insert({kheliumdaisy0,  h_Muon_PZ_PT_TRUE_Daisy_0});
h_Muon_PZ_PT_TRUE_Daisy_Map.insert({kheliumdaisy1,  h_Muon_PZ_PT_TRUE_Daisy_1});
h_Muon_PZ_PT_TRUE_Daisy_Map.insert({kheliumdaisy2,  h_Muon_PZ_PT_TRUE_Daisy_2});
h_Muon_PZ_PT_TRUE_Daisy_Map.insert({kheliumdaisy3,  h_Muon_PZ_PT_TRUE_Daisy_3});
h_Muon_PZ_PT_TRUE_Daisy_Map.insert({kheliumdaisy4,  h_Muon_PZ_PT_TRUE_Daisy_4});
h_Muon_PZ_PT_TRUE_Daisy_Map.insert({kheliumdaisy5,  h_Muon_PZ_PT_TRUE_Daisy_5});
h_Muon_PZ_PT_TRUE_Daisy_Map.insert({kheliumdaisy6,  h_Muon_PZ_PT_TRUE_Daisy_6});
h_Muon_PZ_PT_TRUE_Daisy_Map.insert({kheliumdaisy7,  h_Muon_PZ_PT_TRUE_Daisy_7});
h_Muon_PZ_PT_TRUE_Daisy_Map.insert({kheliumdaisy8,  h_Muon_PZ_PT_TRUE_Daisy_8});
h_Muon_PZ_PT_TRUE_Daisy_Map.insert({kheliumdaisy9,  h_Muon_PZ_PT_TRUE_Daisy_9});
h_Muon_PZ_PT_TRUE_Daisy_Map.insert({kheliumdaisy10, h_Muon_PZ_PT_TRUE_Daisy_10});
h_Muon_PZ_PT_TRUE_Daisy_Map.insert({kheliumdaisy11, h_Muon_PZ_PT_TRUE_Daisy_11});
//======================================================================
//======================================================================


PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_PT_theta_TRUE("h_Muon_PT_theta_TRUE",  "h_Muon_PT_theta_TRUE",  PTbin_vector, MuonThetabin_vector, error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_PZ_theta_TRUE("h_Muon_PZ_theta_TRUE",  "h_Muon_PZ_theta_TRUE",  Pzbin_vector, MuonThetabin_vector, error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_E_theta_TRUE("h_Muon_E_theta_TRUE",         "h_Muon_E_theta",        Ebin_vector,  MuonThetabin_vector, error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_E_PZ_TRUE("h_Muon_E_PZ_TRUE",          "h_Muon_E_PZ_TRUE",      Ebin_vector,  Pzbin_vector,        error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_E_PT_TRUE("h_Muon_E_PT_TRUE",          "h_Muon_E_PT_TRUE",      Ebin_vector,  PTbin_vector,        error_bands);

//=========================================
// Entry Loop For MC
//=========================================

  bool is_counter = true;

  TRUE_Cut_Map Truth_Cut_Map;
  FillingTruthCountingMap(kTRUTHCutsVector, Truth_Cut_Map);

  ProcInfo_t procInfo;
  gSystem->GetProcInfo(&procInfo);

  std::cout << "Memory/time used so Far: " << procInfo.fMemResident/1000<< " MB" <<" time = "<<  procInfo.fCpuSys <<  " Sec"<<"\n";

  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"MC LOOP  "<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

  std::string sysmatics_status;
  if(m_RunCodeWithSystematics==true){sysmatics_status= "Systematics_On";}
  else if (m_RunCodeWithSystematics==false){sysmatics_status= "Systematics_Off";}
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;
  std::cout<<"~~~~~~~~~  "<< sysmatics_status <<" ~~~~~~~~~ "<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;

  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<" Starting TRUTH MC LOOP  "<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

  ///////////////////////////////////////////
  ////
  //// Main Event Selection Loop
  ////
  ///////////////////////////////////////////

  for(int ii=0; ii<chw_MC->GetEntries(); ++ii){

      if(ii%100000==0) std::cout << (ii/100000) << "K " << std::flush;

    //=========================================
    // For every systematic, loop over the universes, and fill the
    // appropriate histogram in the MnvH1D
    //=========================================

    for ( auto  Universe_GROUP: Error_Band_Universe_GROUPS){
  //std::cout<<" SetEntry  "<<std::endl;
     Universe_GROUP.front()->SetEntry(ii);

//  std::cout<<" Starting Cuts  "<<std::endl;

          if(!(14 == Universe_GROUP.front()->GetTruthNuPDG()))continue;
          if(!(Universe_GROUP.front()->GetTruthIsCC()))continue;
          if(!(Universe_GROUP.front()->IsTRUEMuonAngle_HeliumGood())) continue;
          if(!(Universe_GROUP.front()->isEmuGood_TRUE()))continue;
          if(!(Universe_GROUP.front()->PassTrueFiducial())) continue;
          if(!(Universe_GROUP.front()->TrackerOnlyTrue()))continue;
            //std::cout<<" End Cuts  "<<std::endl;
          if(!TRUTH_GreaterthanONEFS(*Universe_GROUP.front()))continue;
          if(!TRUTH_Is2ndTrk_maxiumAngle_threshold_No_Neutral_WITHProtonAndPion_thresholds(*Universe_GROUP.front()))continue;


    //if(PassesCutsTRUTH(*Universe_GROUP.front(), kTRUTHCutsVector, kTRUEWeights_v1tune , Truth_Cut_Map)){

     //int secondTrk = -999;
     std::vector <int> PDG_trklist = Universe_GROUP.front()->GETvector_PDG_FS_particles();
     std::vector <double> Angle_trklist = Universe_GROUP.front()->GETvector_theta_wrtb_FS_particles();
     std::vector <double> Energy_trklist   = Universe_GROUP.front()->GETvector_KE_mc_FS_particles_GeV(pdg_DATABASEobject);

     int secondTrk = Universe_GROUP.front()->Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_lessthanAngle(PDG_trklist, Energy_trklist, Angle_trklist);
//std::cout<< "secondTrk = " << secondTrk<< "  PDG_trklist.size() = " << PDG_trklist.size() << std::endl;
     int pdg_2ndTrk = PDG_trklist.at(secondTrk);
     double secTrkTrueAngle = Angle_trklist.at(secondTrk);
     Particle_type Particle_type_Event = GetParticlegroup_typeReduced(pdg_2ndTrk);
     double theta_degs =  Universe_GROUP.front()->GetTrueThetamuDegrees();
     //double phi = Universe_GROUP.front()->GetPhilepTrue();
     //double Pmu = Universe_GROUP.front()->GetTRUE_Pmu();
     double Emu =  Universe_GROUP.front()->GetElepTrue()*.001; // convert to GeV
     //double theta_degs = Theta* TMath::RadToDeg();

     double PT =  Universe_GROUP.front()->GetPmuTransverseTrue();
     double PZ =  Universe_GROUP.front()->GetPmuLongitudinalTrue();

     for (auto universe : Universe_GROUP){
          universe->SetEntry(ii);

          //double OpenAngle = Universe_GROUP.front()->GetTRUE_NonmuTrkopenangle(secondTrk);

          //std::cout<<"universe->ShortName() = "<< universe->ShortName()<<std::endl;
          double mvn1wgt = universe->GetWeight(kTRUEWeights_v1tune);
          //std::cout<<" mvn1wgt "<< mvn1wgt<<std::endl;
          h_Muon_PZ_PT_TRUE.univHist(universe)->         Fill(PZ, PT, mvn1wgt);
          h_Muon_E_theta_TRUE.univHist(universe)->       Fill(Emu,theta_degs, mvn1wgt);

          h_MuonE_TRUE.univHist(universe)->  Fill(Emu, mvn1wgt);
          h_MuonPZ_TRUE.univHist(universe)->  Fill(PZ, mvn1wgt);
          h_MuonPT_TRUE.univHist(universe)->  Fill(PT, mvn1wgt);
          h_MuonTheta_TRUE.univHist(universe)->  Fill(theta_degs , mvn1wgt);
          h_secTrk_Theta_TRUE.univHist(universe)->Fill(secTrkTrueAngle,mvn1wgt);

          auto Daisytype = universe->GetTRUERegion12DAISY_SliceHelium();

          h_Muon_PZ_PT_TRUE_Daisy_Map[Daisytype].univHist(universe)->         Fill(PZ, PT, mvn1wgt);
          h_MuonE_Daisy_Map[Daisytype].univHist(universe)->  Fill(Emu, mvn1wgt);
          h_MuonPZ_Daisy_Map[Daisytype].univHist(universe)->  Fill(PZ, mvn1wgt);
          h_MuonPT_Daisy_Map[Daisytype].univHist(universe)->  Fill(PT, mvn1wgt);
          h_MuonTheta_Daisy_Map[Daisytype].univHist(universe)->  Fill(theta_degs , mvn1wgt);

          ///////////////////////////////////////////
          ////
          ////  FILL CV
          ////
          ///////////////////////////////////////////
          if( isCV(*universe)){
          //  std::cout<<" Filling cv "<< mvn1wgt<<std::endl;
          //  Particle_type Particle_type_Event = GetParticlegroup_type(pdg_2ndTrk);
            //Material_type Material_type_Event = universe->Get_MaterialStackType();
            Interaction_type Interaction_type_Event =  universe->Get_Interaction_withDISbreakdown_AnaDev();

            auto Vertex = universe->GetTrueVertex();
            //std::cout<<" Got interction breakdown "<< mvn1wgt<<std::endl;
            h_2d_PZ_PT_TRUE->Fill(PZ,PT,mvn1wgt);

            h_Muon_PZ_PT_Interaction.GetComponentHist(Interaction_type_Event)->Fill(PZ, PT, mvn1wgt);
            h_Muon_PZ_PT_Particle.GetComponentHist(Particle_type_Event)->Fill(PZ, PT, mvn1wgt);
            h_Muon_E_theta_Interaction.GetComponentHist(Interaction_type_Event)->Fill(Emu,theta_degs,mvn1wgt);
            //h_Muon_E_theta_Particle.GetComponentHist(Particle_type_Event)->Fill(Emu,theta_degs,mvn1wgt);
            h_Vertex_X_Y_Daisy_Map[Daisytype]->Fill(Vertex.x(),Vertex.y(),mvn1wgt);

            //h_MuonE_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(Emu, mvn1wgt);
            h_MuonE_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(Emu, mvn1wgt);
            h_MuonPZ_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(PZ, mvn1wgt);
            //h_MuonPZ_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(PT, mvn1wgt);
            h_MuonPT_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(PT, mvn1wgt);
            //h_MuonPT_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(PT, mvn1wgt);
            h_MuonTheta_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(theta_degs, mvn1wgt);
            //h_MuonTheta_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(theta_degs, mvn1wgt);
            h_MuonE_Interaction_Daisy_Map[Daisytype].GetComponentHist(Interaction_type_Event)->Fill(Emu, mvn1wgt);
            h_MuonPZ_Interaction_Daisy_Map[Daisytype].GetComponentHist(Interaction_type_Event)->Fill(PZ, mvn1wgt);
            h_MuonPT_Interaction_Daisy_Map[Daisytype].GetComponentHist(Interaction_type_Event)->Fill(PT, mvn1wgt);
            h_MuonTheta_Interaction_Daisy_Map[Daisytype].GetComponentHist(Interaction_type_Event)->Fill(theta_degs, mvn1wgt);
          }// end of CV

          ///////////////////////////////////////////
          ////  END OF CV
          ///////////////////////////////////////////



        }// ENd of Universe
      } // end of Group
     } //End entries loop

     gSystem->GetProcInfo(&procInfo);
     std::cout << " Done with loop Mem1: " << procInfo.fMemResident/1000 << " MB" << " time = "<<  procInfo.fCpuSys  <<  " sec""\n";
        ///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

    h_Muon_PZ_PT_TRUE.SyncCVHistos();
    h_Muon_E_theta_TRUE.SyncCVHistos();

    //h_2ndtrkangle_2ndTrkE_TRUE.SyncCVHistos();
    //h_theta_openAngle_TRUE.SyncCVHistos();
    h_MuonE_TRUE.SyncCVHistos();
    h_MuonPZ_TRUE.SyncCVHistos();
    h_MuonPT_TRUE.SyncCVHistos();
    h_MuonTheta_TRUE.SyncCVHistos();
    h_secTrk_Theta_TRUE.SyncCVHistos();


for(auto Petal :DaisyN){
    h_Muon_PZ_PT_TRUE_Daisy_Map[Petal].SyncCVHistos();
    h_MuonE_Daisy_Map[Petal].SyncCVHistos();
    h_MuonPZ_Daisy_Map[Petal].SyncCVHistos();
    h_MuonPT_Daisy_Map[Petal].SyncCVHistos();
    h_MuonTheta_Daisy_Map[Petal].SyncCVHistos();
  }

  //=========================================
  // Writing Root File
  //=========================================
  std::string systematics_status;
  if(m_RunCodeWithSystematics==true)
  {
    sysmatics_status= "All_SysErrorsOn";
    std::cout<<"print to: "<< sysmatics_status <<std::endl ;
  }
  else if (m_RunCodeWithSystematics==false)
  {
    sysmatics_status= "StatsONLY";
  }

    std::cout<<"print to: "<< sysmatics_status <<std::endl ;
    char sysmatics_status_char[sysmatics_status.length()+1];
    strcpy(sysmatics_status_char, sysmatics_status.c_str());

  char outFileName[2024];
  auto playlist_name = Playlist_Info.GetPlaylistname();
  std::string datatype = "TRUTH";
  char c[playlist_name.length() + 1];
  char d[datatype.length() + 1];
  char rootpathway[OUTputRoot_pathway.length() + 1];
  char systematics_char[sysmatics_status.length() + 1];
  strcpy(rootpathway, OUTputRoot_pathway.c_str());
  strcpy(c, playlist_name.c_str());
  strcpy(d, datatype.c_str());

  sprintf(outFileName, "%s/Histograms_TRUTH_MasterAnaDev_%s_%s_%s_Fid.root", rootpathway, c, d, sysmatics_status_char);

  std::cout << " Writing output file to: " <<outFileName << std::endl;


  TGraph  *Truth_2DCuts  = Make_TruthCut_Tgraph_fromCutMap("Truth_2DCuts"        , Truth_Cut_Map);
  TFile *outFile = new TFile(outFileName,"RECREATE");

  Truth_2DCuts->Write();


  TChain POT_branch("Meta");
  POT_branch.Add(RootName.c_str());
  TTree *clone = POT_branch.CloneTree();
  clone->Write();

  ////////////////////////////////////////////////
  h_Muon_PZ_PT_TRUE.hist->Write();
  h_Muon_E_theta_TRUE.hist->Write();

  h_MuonE_TRUE.hist->Write();
  h_MuonPZ_TRUE.hist->Write();
  h_MuonPT_TRUE.hist->Write();
  h_MuonTheta_TRUE.hist->Write();
  h_secTrk_Theta_TRUE.hist->Write();

  for(auto Petal :DaisyN){
      h_Muon_PZ_PT_TRUE_Daisy_Map[Petal].hist->Write();
      h_MuonE_Daisy_Map[Petal].hist->Write();
      h_MuonPZ_Daisy_Map[Petal].hist->Write();
      h_MuonPT_Daisy_Map[Petal].hist->Write();
      h_MuonTheta_Daisy_Map[Petal].hist->Write();
      h_MuonE_Interaction_Daisy_Map[Petal].WriteToFile(*outFile);
      h_MuonPZ_Interaction_Daisy_Map[Petal].WriteToFile(*outFile);
      h_MuonPT_Interaction_Daisy_Map[Petal].WriteToFile(*outFile);
      h_MuonTheta_Interaction_Daisy_Map[Petal].WriteToFile(*outFile);
      h_Vertex_X_Y_Daisy_Map[Petal]->Write();
    }


  h_2d_PZ_PT_TRUE->Write();


  h_MuonE_TRUE_Particle.WriteToFile(*outFile);
  h_MuonPZ_TRUE_Particle.WriteToFile(*outFile);
  h_MuonPT_TRUE_Particle.WriteToFile(*outFile);
  h_MuonTheta_TRUE_Particle.WriteToFile(*outFile);

  h_Muon_PZ_PT_Interaction.WriteToFile(*outFile);
  h_Muon_PZ_PT_Particle.WriteToFile(*outFile);
  h_Muon_E_theta_Interaction.WriteToFile(*outFile);
  h_Muon_E_theta_Particle.WriteToFile(*outFile);
  h_MuonE_TRUE_Interaction.WriteToFile(*outFile);
  h_MuonPZ_TRUE_Interaction.WriteToFile(*outFile);
  h_MuonPT_TRUE_Interaction.WriteToFile(*outFile);
  h_MuonTheta_TRUE_Interaction.WriteToFile(*outFile);


  outFile->Close();


  for(auto band : error_bands){
    std::vector<HeliumCVUniverse*> band_universes = band.second;
    for(unsigned int i_universe = 0; i_universe < band_universes.size(); ++i_universe){ delete band_universes[i_universe];}
  }


  std::cout << "Success in TRUTH LOOP - You Da Man !?!?" << std::endl;

TCanvas *can = new TCanvas("can", "can",1800,1600);
sprintf(outFileName, "Histograms_MasterAnnDev_TRUTH_%s_%s_%s_Fid.pdf", c, d, sysmatics_status_char);
can -> Print(outFileName);
can ->Close();

}//END of Event Loop

//=========================================
//   //END of Main Event Loop Function
//=========================================
//////////////////////////////////////////////////////////////
std::vector<ECutsTRUTH> GetTRUTHCutsVector() {
  std::vector<ECutsTRUTH> True_vec;
  True_vec.push_back(kTRUTHNoCuts  );
  True_vec.push_back(kTRUTHneutrino);
  True_vec.push_back(kTRUTHCCInteraction );
  True_vec.push_back(kTRUTHtarget);
  True_vec.push_back(kTRUTHMuonEnergy );
  True_vec.push_back(kTRUTHMuonAngle );
  True_vec.push_back(kTRUTH_greaterthanoneFS);
  //True_vec.push_back(kTRUTH_secTrk_Angle_threshold);
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);
  True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold_withProtonanPionThresholds);
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
  Particle.push_back(kPion_0);
  Particle.push_back(kPion_neg);
  Particle.push_back(kPion_pos);
  Particle.push_back(kMuon);

  return Particle;
//#endif
}

//////////////////////////////////////////////////////////////////////////
//GET Weight Vector to apply
//////////////////////////////////////////////////////////////////////////
std::vector<Weights> GetWeightVector() {

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


  bool Run_EventLoopOnGrid = false;
  if(Run_EventLoopOnGrid==true){std::cout << "This Eventloop is step up to run on the Grid" << std::endl;}
  else{std::cout << "This Eventloop is step up to run locally" << std::endl;}

  runEventLoop(Playlist_to_run, m_debugOn,  Run_EventLoopOnGrid);
  return 0;
}




//#endif
