//File: Helium2D_runTRUTHLoop.cxx
//Brief: Given ntuple files from HeAnaTupleTool.cpp , extracts 2D TRUE EventSelction for Helium Nu interactions
//Writes a .root file Event Selection histograms.
//
//Usage: 2D TRUTH 2DEventSelection  <mc.root>
//
//Author: Christian Nguyen  christian2nguyen@ufl.edu

#include "Helium2D_runTRUTHLoop.h"

std::string OUTputRoot_pathway = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles";

//=====================================================
// Functions
//=====================================================
std::vector<ECuts> GetRECOCutsVector();
std::vector<ECutsTRUTH> GetTRUTHCutsVector();
std::vector<ME_helium_Playlists> GetPlayListVector();
std::vector<Weights> GetWeightVector();
std::vector<Particle_type>  GetParicle_type();

//=====================================================
// Run With error Sysematics
//=====================================================
const bool m_RunCodeWithSystematics = true;

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
const std::vector<PlotUtils::NamedCategory<Interaction_type>>
InteractionGroup_categories = {
  PlotUtils::NamedCategory<Interaction_type>({kInteraction_OTHER},"Other"),
  PlotUtils::NamedCategory<Interaction_type>({kInteraction_NONE}, "None"),
  PlotUtils::NamedCategory<Interaction_type>({kDIS},              "DIS"),
  PlotUtils::NamedCategory<Interaction_type>({k2p2h},             "2p2h"),
  PlotUtils::NamedCategory<Interaction_type>({kRes_Coh_Pion},     "Res_Coh"),
  PlotUtils::NamedCategory<Interaction_type>({kElastic},          "Elastic")
};


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

  auto Playlist_txtFILEPath = GetPlaylist_txtFILE_path(PlayList_iterator, is_mc );
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
const std::string RootName = GetPlaylist_ROOT_path(PlayList_iterator,true);
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


std::vector<double> bigAngle_bins{0.0, 15.0, 30.0, 45.0, 60.0};


std::vector<double> MuonThetabin_vector= GetBinMuonVector(kAngleWRTB_2D);
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
std::vector<double> Vertex_secondTrkTheta_bins= GetSecondTrkVarVector(ksecTheta_2D);
std::vector<double> Vertex_secondTrkDOCA_bins= GetSecondTrkVarVector(kDOCA_2D);
std::vector<double> Vertex_secondTrkPathway_bins = GetSecondTrkVarVector(kPathway);

std::vector<double> SecTrk_Tracklength_vector = GetSecondTrkVarVector(ksec_tracklength_minerva_2D);
std::vector <double>  XandYBeamBins =  MakeBinVector(250, -1000, 1000);
//for(auto a :XandYBeamBins){std::cout<<"bins"<< a << std::endl;}
//======================================================================
//muon Varibles
//Set up TRUE muon Hist
//======================================================================
//std::vector<double> EnergyNu;//{0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0};
//
//double edge = 0;
//for(int i = 0; i < 1001; i ++ ){
//  EnergyNu.push_back(edge);
//  edge = edge + .1;
//}
//std::vector<double> EnergySlices{0.0,1.0,2.0,3.0,4.0};


//PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE("h_Enu_TRUE", "h_Enu_TRUE",                EnergyNu , error_bands);
//PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_signalDiff("h_Enu_TRUE_signalDiff", "h_Enu_TRUE_signalDiff",  EnergyNu , error_bands);
//
//PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Slice1("h_Enu_TRUE_Slice1", "h_Enu_TRUE_Slice1",                EnergyNu , error_bands);
//PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Slice2("h_Enu_TRUE_Slice2", "h_Enu_TRUE_Slice2",                EnergyNu , error_bands);
//PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Slice3("h_Enu_TRUE_Slice3", "h_Enu_TRUE_Slice3",                EnergyNu , error_bands);
//PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Slice4("h_Enu_TRUE_Slice4", "h_Enu_TRUE_Slice4",                EnergyNu , error_bands);
//
//PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Enu_Slice_TRUE("h_Enu_Slice_TRUE",    "h_Enu_Slice_TRUE",         EnergyNu,  EnergySlices,        error_bands);
//
////PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Enu_TRUE_vertex_X("h_Enu_TRUE_vertex_X",    "h_Enu_TRUE_vertex_X",       EnergyNu,  XandYBeamBins  ,      error_bands);
////PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Enu_TRUE_vertex_Y("h_Enu_TRUE_vertex_Y",    "h_Enu_TRUE_vertex_Y",       EnergyNu,  XandYBeamBins  ,      error_bands);
//
//MnvH2D *h_Enu_TRUE_vertex_X            =    new MnvH2D("h_Enu_TRUE_vertex_X", "h_Enu_TRUE_vertex_X",EnergyNu.size()-1, EnergyNu.data() ,XandYBeamBins.size()-1, XandYBeamBins.data()  );
//MnvH2D *h_Enu_TRUE_vertex_Y            =    new MnvH2D("h_Enu_TRUE_vertexY", "h_Enu_TRUE_vertex_Y",EnergyNu.size()-1, EnergyNu.data() ,XandYBeamBins.size()-1, XandYBeamBins.data()  );



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

PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type> h_Muon_PZ_PT_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type>(ParticleGroup_categories, "h_Muon_PZ_PT_Particle",  Pzbin_vector , PTbin_vector ,"h_Muon_PZ_PT_Particle; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type> h_Muon_E_theta_Material =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type>(MaterialGroup_categories, "h_Muon_E_theta_Material",  Ebin_vector , MuonThetabin_vector ,"E_theta_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type> h_Muon_E_theta_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_Muon_E_theta_Interaction",  Ebin_vector , MuonThetabin_vector ,"E_theta_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type> h_Muon_E_theta_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type>(ParticleGroup_categories, "h_Muon_E_theta_Particle",  Ebin_vector , MuonThetabin_vector ,"E_theta_Particle; [GeV];Events");

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
MnvH2D *h_2d_2ndtrkangle_2ndTrkE_TRUE         =    new MnvH2D("h_2d_2ndtrkangle_2ndTrkE_TRUE"       , "h_2d_2ndtrkangle_2ndTrkE_TRUE"       , Vertex_secondTrkTheta_bins.size()-1, Vertex_secondTrkTheta_bins.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );
MnvH2D *h_2d_2ndtrkangle_2ndTrkE_Proton_TRUE  =    new MnvH2D("h_2d_2ndtrkangle_2ndTrkE_Proton_TRUE", "h_2d_2ndtrkangle_2ndTrkE_Proton_TRUE", Vertex_secondTrkTheta_bins.size()-1, Vertex_secondTrkTheta_bins.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );
MnvH2D *h_2d_2ndtrkangle_2ndTrkE_Pion_TRUE    =    new MnvH2D("h_2d_2ndtrkangle_2ndTrkE_Pion_TRUE"  , "h_2d_2ndtrkangle_2ndTrkE_Pion_TRUE"  , Vertex_secondTrkTheta_bins.size()-1, Vertex_secondTrkTheta_bins.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );
MnvH2D *h_2d_2ndtrkangle_2ndTrkE_dimuon_TRUE  =    new MnvH2D("h_2d_2ndtrkangle_2ndTrkE_dimuon_TRUE", "h_2d_2ndtrkangle_2ndTrkE_dimuon_TRUE", Vertex_secondTrkTheta_bins.size()-1, Vertex_secondTrkTheta_bins.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );
////////////////
//Vertex Hist///
////////////////

PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_PZ_PT_TRUE("h_Muon_PZ_PT_TRUE",    "h_Muon_PZ_PT_TRUE",         Pzbin_vector, PTbin_vector,        error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_PT_theta_TRUE("h_Muon_PT_theta_TRUE",  "h_Muon_PT_theta_TRUE",  PTbin_vector, MuonThetabin_vector, error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_PZ_theta_TRUE("h_Muon_PZ_theta_TRUE",  "h_Muon_PZ_theta_TRUE",  Pzbin_vector, MuonThetabin_vector, error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_E_theta_TRUE("h_Muon_E_theta_TRUE",         "h_Muon_E_theta",        Ebin_vector,  MuonThetabin_vector, error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_E_PZ_TRUE("h_Muon_E_PZ_TRUE",          "h_Muon_E_PZ_TRUE",      Ebin_vector,  Pzbin_vector,        error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_E_PT_TRUE("h_Muon_E_PT_TRUE",          "h_Muon_E_PT_TRUE",      Ebin_vector,  PTbin_vector,        error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_cryoVertex_Z_R_TRUE("h_cryoVertex_Z_R_TRUE","h_cryoVertex_Z_R_TRUE", Vertex_Zbins, Vertex_Rbins ,       error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_2ndtrkangle_2ndTrkE_TRUE("h_2ndtrkangle_2ndTrkE_TRUE", "h_2ndtrkangle_2ndTrkE_TRUE",  bigAngle_bins, Vertex_secondTrkEbins , error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_theta_openAngle_TRUE("h_theta_openAngle_TRUE", "h_theta_openAngle_TRUE", MuonThetabin_vector, bigAngle_bins , error_bands);


PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_cryoVertex_Z_theta_TRUE("h_cryoVertex_Z_theta_TRUE", "h_cryoVertex_Z_theta_TRUE", Vertex_Zbins, MuonThetabin_vector , error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_cryoVertex_R_theta_TRUE("h_cryoVertex_R_theta_TRUE", "h_cryoVertex_R_theta_TRUE", Vertex_Rbins, MuonThetabin_vector , error_bands);


PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_cryoVertex_Z_X_TRUE("h_cryoVertex_Z_X_TRUE","h_cryoVertex_Z_X_TRUE", Vertex_Zbins, Vertex_Xbins ,       error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_cryoVertex_Z_Y_TRUE("h_cryoVertex_Z_Y_TRUE","h_cryoVertex_Z_Y_TRUE", Vertex_Zbins, Vertex_Ybins ,       error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_cryoVertex_X_Y_TRUE("h_cryoVertex_X_Y_TRUE","h_cryoVertex_X_Y_TRUE", Vertex_Xbins, Vertex_Ybins ,       error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_cryoVertex_Z_openAngle_TRUE("h_cryoVertex_Z_openAngle_TRUE", "h_cryoVertex_Z_openAngle_TRUE",Vertex_Zbins, bigAngle_bins , error_bands);


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
    if(ii%50000==0) std::cout << (ii/1000) << " k " << std::flush;

    //=========================================
    // For every systematic, loop over the universes, and fill the
    // appropriate histogram in the MnvH1D
    //=========================================
    for ( auto  Universe_GROUP: Error_Band_Universe_GROUPS){

     Universe_GROUP.front()->SetEntry(ii);


    if(PassesCutsTRUTH(*Universe_GROUP.front(), kTRUTHCutsVector, kTRUEWeights_v1tune , Truth_Cut_Map)){

     int secondTrk = -999;
     std::vector <int> PDG_trklist = Universe_GROUP.front()->GETvector_PDG_FS_particles();
     std::vector <double> Angle_trklist = Universe_GROUP.front()->GETvector_theta_wrtb_FS_particles();
     std::vector <double> Energy_trklist   = Universe_GROUP.front()->GETvector_KE_mc_FS_particles_GeV(pdg_DATABASEobject);


     secondTrk = Universe_GROUP.front()->Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_lessthanAngle(PDG_trklist, Energy_trklist, Angle_trklist);


     if(secondTrk==-999){std::cout<<"ERROR got -999 for secondtrk "<<std::endl; assert(false);};
     if(PDG_trklist.size()==0){std::cout<<"Have PDG of size 0 after Cuts ERROR"<<std::endl;assert(false);}
     if(PDG_trklist.size()==1){std::cout<<"Have PDG of size 1 after Cuts ERROR"<<std::endl;assert(false);}

     //secondTrk = universe->Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_lessthanAngle(PDG_trklist, Energy_trklist, Angle_trklist ) ;

      //secondTrk = Universe_GROUP.front()->Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE(PDG_trklist, Energy_trklist);


      int true_track_size = PDG_trklist.size();
      int pdg_2ndTrk = PDG_trklist.at(secondTrk);
      double SecTrkTrueEnergy = Energy_trklist.at(secondTrk);
      double SecTrkTrueAngle = Angle_trklist.at(secondTrk);
      double OpeningAngle = Universe_GROUP.front()-> GetTRUE_NonmuTrkopenangle(secondTrk);

        for (auto universe : Universe_GROUP){
          universe->SetEntry(ii);
          double Theta = universe->GetThetalepTrue();
          //double phi = Universe_GROUP.front()->GetPhilepTrue();
          //double Pmu = Universe_GROUP.front()->GetTRUE_Pmu();
          double Emu = universe->GetTRUE_Emu(); // is in GeV
          double theta_degs = Theta* TMath::RadToDeg();

          //double px = Pmu * std::sin(Theta) * std::cos(phi);
          //double py = Pmu * std::sin(Theta) * std::sin(phi);

         //     double PT = sqrt(px*px + py*py);
         //   double PZ = Pmu*std::cos(Theta);


               //double PZ = universe->GetPmuLongitudinalTrue(); //GeV
               //double PT = universe->GetPmuTransverseTrue(); // GeV

               double PT = universe->GetMuonPTTrue_new();
               double PZ = universe->GetMuonPzTrue_new();
               double ztrue = universe->GetTRUE_Vertex_z();
               double rtrue = universe->GetTRUE_Vertex_r();
               double xtrue = universe->GetTRUE_Vertex_x();
               double ytrue = universe->GetTRUE_Vertex_y();

          //std::cout<<"universe->ShortName() = "<< universe->ShortName()<<std::endl;
          double mvn1wgt = universe->GetWeight(kTRUEWeights_v1tune);

          h_Muon_PZ_PT_TRUE.univHist(universe)->         Fill(PZ, PT, mvn1wgt);
          h_Muon_PT_theta_TRUE.univHist(universe)->      Fill(PT, theta_degs,mvn1wgt);
          h_Muon_PZ_theta_TRUE.univHist(universe)->      Fill(PZ, theta_degs,mvn1wgt);
          h_Muon_E_theta_TRUE.univHist(universe)->       Fill(Emu,theta_degs, mvn1wgt);
          h_Muon_E_PZ_TRUE.univHist(universe)->          Fill(Emu, PZ, mvn1wgt);
          h_Muon_E_PT_TRUE.univHist(universe)->          Fill(Emu, PT, mvn1wgt);
          h_cryoVertex_Z_R_TRUE.univHist(universe)->     Fill(ztrue,rtrue , mvn1wgt);
          h_2ndtrkangle_2ndTrkE_TRUE.univHist(universe)->Fill(SecTrkTrueAngle, SecTrkTrueEnergy , mvn1wgt);
          h_theta_openAngle_TRUE.univHist(universe)->Fill(theta_degs, OpeningAngle , mvn1wgt);
          h_cryoVertex_Z_theta_TRUE.univHist(universe)->Fill(ztrue,theta_degs , mvn1wgt);
          h_cryoVertex_R_theta_TRUE.univHist(universe)->Fill(rtrue,theta_degs , mvn1wgt);
          h_cryoVertex_Z_X_TRUE.univHist(universe)->Fill(ztrue,xtrue , mvn1wgt);
          h_cryoVertex_Z_Y_TRUE.univHist(universe)->Fill(ztrue,ytrue , mvn1wgt);
          h_cryoVertex_X_Y_TRUE.univHist(universe)->Fill(xtrue,ytrue , mvn1wgt);
          h_cryoVertex_Z_openAngle_TRUE.univHist(universe)->Fill(ztrue,OpeningAngle, mvn1wgt);
          //h_Enu_TRUE_signalDiff.univHist(universe)->Fill(universe->GetEnuTrue()*.001, mvn1wgt);
          ///////////////////////////////////////////
          ////
          ////  FILL CV
          ////
          ///////////////////////////////////////////
          if( isCV(*universe)){


            Particle_type Particle_type_Event = GetParticlegroup_type(pdg_2ndTrk);
          //  Interaction_type Interaction_type_Event =  universe->Get_InteractionStackType();
            Material_type Material_type_Event = universe->Get_MaterialStackType();
            Interaction_type Interaction_type_Event =  universe->Get_Interaction_withDISbreakdown();

            h_2d_PZ_PT_TRUE->Fill(PZ,PT,mvn1wgt);
            h_2d_E_PZ_TRUE->Fill(Emu,PZ,mvn1wgt);
            h_2d_Theta_PZ_TRUE->Fill(theta_degs,PZ,mvn1wgt);
            h_2d_E_PT_TRUE->Fill(Emu,PT,mvn1wgt);
            h_2d_Theta_PT_TRUE->Fill(theta_degs,PT,mvn1wgt);
            h_2d_Theta_PZ_TRUE->Fill(theta_degs,PZ,mvn1wgt);
            h_2d_Theta_2ndTrkE_TRUE->Fill(theta_degs,SecTrkTrueEnergy,mvn1wgt);
            h_2d_muonE_2ndTrkE_TRUE->Fill(Emu,SecTrkTrueEnergy,mvn1wgt);
            h_2d_muonPT_2ndTrkE_TRUE->Fill(PT,SecTrkTrueEnergy,mvn1wgt);
            h_2d_muonPZ_2ndTrkE_TRUE->Fill(PZ,SecTrkTrueEnergy,mvn1wgt);
            h_2d_Theta_2ndTrKangle_TRUE->Fill(theta_degs,SecTrkTrueEnergy,mvn1wgt);
            h_2d_muonE_2ndTrkangle_TRUE->Fill(Emu,SecTrkTrueAngle,mvn1wgt);
            h_2d_muonPT_2ndTrkangle_TRUE->Fill(PT,SecTrkTrueAngle,mvn1wgt);
            h_2d_muonPZ_2ndTrkangle_TRUE->Fill(PZ,SecTrkTrueAngle,mvn1wgt);
            h_2d_2ndtrkangle_2ndTrkE_TRUE->Fill(SecTrkTrueAngle,SecTrkTrueEnergy,mvn1wgt);


            if(Particle_type_Event==kSecondary_particle_vector[0]){
              h_2d_2ndtrkangle_2ndTrkE_Proton_TRUE->Fill(SecTrkTrueAngle,SecTrkTrueEnergy,mvn1wgt);
            }
            if(Particle_type_Event==kSecondary_particle_vector[1]){
              h_2d_2ndtrkangle_2ndTrkE_Pion_TRUE ->Fill(SecTrkTrueAngle,SecTrkTrueEnergy,mvn1wgt);
            }
            if(Particle_type_Event==kSecondary_particle_vector[2]){
              h_2d_2ndtrkangle_2ndTrkE_dimuon_TRUE->Fill(SecTrkTrueAngle,SecTrkTrueEnergy,mvn1wgt);
            }


            h_Muon_PZ_PT_Interaction.GetComponentHist(Interaction_type_Event)->Fill(PZ, PT, mvn1wgt);
            h_Muon_PZ_PT_Particle.GetComponentHist(Particle_type_Event)->Fill(PZ, PT, mvn1wgt);
            h_Muon_E_theta_Interaction.GetComponentHist(Interaction_type_Event)->Fill(Emu,theta_degs,mvn1wgt);
            h_Muon_E_theta_Particle.GetComponentHist(Particle_type_Event)->Fill(Emu,theta_degs,mvn1wgt);



          }// end of CV

          ///////////////////////////////////////////
          ////  END OF CV
          ///////////////////////////////////////////



        }// ENd of Universe
      }// ENd of Cuts

/*
      if(Universe_GROUP.front()->Get_mc_incoming()==14){
      //  std::cout<< "Universe_GROUP.front()->Get_mc_incoming() "<< Universe_GROUP.front()->Get_mc_incoming()<<std::endl;
        if(Universe_GROUP.front()->Get_mc_current()==1){
          if (Universe_GROUP.front()->isHeliumInteraction()){
            if(TRUTH_IsINFiduicalVolume_new(*Universe_GROUP.front())){
            for (auto universe : Universe_GROUP){
              universe->SetEntry(ii);
              double mvn1wgt = universe->GetWeight(kTRUEWeights_v1tune);
              double Enu_input = universe->GetEnuTrue()*.001;
              h_Enu_TRUE.univHist(universe)->Fill(Enu_input, mvn1wgt);
              double xtrue = universe->GetTRUE_Vertex_x();
              double ytrue = universe->GetTRUE_Vertex_y();
              if(isCV(*universe)){
                h_Enu_TRUE_vertex_X->Fill(Enu_input,xtrue, mvn1wgt);
                h_Enu_TRUE_vertex_Y->Fill(Enu_input,ytrue, mvn1wgt);
              }

              auto Slicetype = universe->GetTRUERegionSliceHelium();
              if (Slicetype==kSlice1){h_Enu_TRUE_Slice1.univHist(universe)->Fill(Enu_input,mvn1wgt);
                h_Enu_Slice_TRUE.univHist(universe)->Fill(Enu_input,0.0 , mvn1wgt);

              }
              else if (Slicetype==kSlice2) {h_Enu_TRUE_Slice2.univHist(universe)->Fill(Enu_input,mvn1wgt);
                h_Enu_Slice_TRUE.univHist(universe)->Fill(Enu_input,1.0 , mvn1wgt);

              }
              else if (Slicetype==kSlice3) {h_Enu_TRUE_Slice3.univHist(universe)->Fill(Enu_input,mvn1wgt);
                h_Enu_Slice_TRUE.univHist(universe)->Fill(Enu_input,2.0 , mvn1wgt);

              }
              else if (Slicetype==kSlice4) {h_Enu_TRUE_Slice4.univHist(universe)->Fill(Enu_input,mvn1wgt);
                h_Enu_Slice_TRUE.univHist(universe)->Fill(Enu_input,3.0 , mvn1wgt);

              }
            }// End of Universe loop
          } // ENd of Trun Fiduical Volume
        } // is a neutrion helium
      }//  CC
    } // is Neutrino
*/



    } // End of Vertial Band group

  } //End entries loop

  gSystem->GetProcInfo(&procInfo);
  std::cout << " Done with loop Mem1: " << procInfo.fMemResident/1000 << " MB" << " time = "<<  procInfo.fCpuSys  <<  " sec""\n";
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

    h_Muon_PZ_PT_TRUE.SyncCVHistos();
    h_Muon_PT_theta_TRUE.SyncCVHistos();
    h_Muon_PZ_theta_TRUE.SyncCVHistos();
    h_Muon_E_theta_TRUE.SyncCVHistos();
    h_Muon_E_PZ_TRUE.SyncCVHistos();
    h_Muon_E_PT_TRUE.SyncCVHistos();
    h_cryoVertex_Z_R_TRUE.SyncCVHistos();
    h_2ndtrkangle_2ndTrkE_TRUE.SyncCVHistos();
    h_theta_openAngle_TRUE.SyncCVHistos();
    h_cryoVertex_Z_theta_TRUE.SyncCVHistos();
    h_cryoVertex_R_theta_TRUE.SyncCVHistos();
    h_cryoVertex_Z_X_TRUE.SyncCVHistos();
    h_cryoVertex_Z_Y_TRUE.SyncCVHistos();
    h_cryoVertex_X_Y_TRUE.SyncCVHistos();
    h_cryoVertex_Z_openAngle_TRUE.SyncCVHistos();
    //h_Enu_TRUE.SyncCVHistos();
    //h_Enu_TRUE_signalDiff.SyncCVHistos();
    //h_Enu_TRUE_Slice1.SyncCVHistos();
    //h_Enu_TRUE_Slice2.SyncCVHistos();
    //h_Enu_TRUE_Slice3.SyncCVHistos();
    //h_Enu_TRUE_Slice4.SyncCVHistos();
    //h_Enu_Slice_TRUE.SyncCVHistos();



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

  sprintf(outFileName, "%s/Histograms_2D_%s_%s_%s_Fid.root", rootpathway, c, d, sysmatics_status_char);

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
  h_Muon_PT_theta_TRUE.hist->Write();
  h_Muon_PZ_theta_TRUE.hist->Write();
  h_Muon_E_theta_TRUE.hist->Write();
  h_Muon_E_PZ_TRUE.hist->Write();
  h_Muon_E_PT_TRUE.hist->Write();
  h_cryoVertex_Z_R_TRUE.hist->Write();
  h_theta_openAngle_TRUE.hist->Write();
  h_2ndtrkangle_2ndTrkE_TRUE.hist->Write();
  h_cryoVertex_Z_theta_TRUE.hist->Write();
  h_cryoVertex_R_theta_TRUE.hist->Write();
  h_cryoVertex_Z_X_TRUE.hist->Write();
  h_cryoVertex_Z_Y_TRUE.hist->Write();
  h_cryoVertex_X_Y_TRUE.hist->Write();
  h_cryoVertex_Z_openAngle_TRUE.hist->Write();

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
  h_2d_2ndtrkangle_2ndTrkE_dimuon_TRUE->Write();

  h_Muon_PZ_PT_Interaction.WriteToFile(*outFile);
  h_Muon_PZ_PT_Particle.WriteToFile(*outFile);
  h_Muon_E_theta_Interaction.WriteToFile(*outFile);
  h_Muon_E_theta_Particle.WriteToFile(*outFile);

  //h_Enu_TRUE.hist->Write();
  //h_Enu_TRUE_signalDiff.hist->Write();
  //h_Enu_TRUE_Slice1.hist->Write();
  //h_Enu_TRUE_Slice2.hist->Write();
  //h_Enu_TRUE_Slice3.hist->Write();
  //h_Enu_TRUE_Slice4.hist->Write();
  //h_Enu_Slice_TRUE.hist->Write();
  //h_Enu_TRUE_vertex_X->Write();
  //h_Enu_TRUE_vertex_Y->Write();
  outFile->Close();


  for(auto band : error_bands){
    std::vector<HeliumCVUniverse*> band_universes = band.second;
    for(unsigned int i_universe = 0; i_universe < band_universes.size(); ++i_universe){ delete band_universes[i_universe];}
  }


  std::cout << "Success in TRUTH LOOP - You Da Man !?!?" << std::endl;

TCanvas *can = new TCanvas("can", "can",1800,1600);
sprintf(outFileName, "Histograms_2D_%s_%s_%s_Fid.pdf", c, d, sysmatics_status_char);
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
  True_vec.push_back(kTRUTHFiduical_new);
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
