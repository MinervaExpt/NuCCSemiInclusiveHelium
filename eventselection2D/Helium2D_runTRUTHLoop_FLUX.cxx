// File: Helium2D_runTRUTHLoop.cxx
// Brief: Given ntuple files from HeAnaTupleTool.cpp , extracts 2D TRUE
// EventSelction for Helium Nu interactions
// Writes a .root file Event Selection histograms.
//
// Usage: 2D TRUTH 2DEventSelection  <mc.root>
//
// Author: Christian Nguyen  christian2nguyen@ufl.edu

#include "Helium2D_runTRUTHLoop.h"

std::string OUTputRoot_pathway =
    "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles";

//=====================================================
// Functions
//=====================================================
std::vector<ECuts> GetRECOCutsVector();
std::vector<ECutsTRUTH> GetTRUTHCutsVector();
std::vector<ME_helium_Playlists> GetPlayListVector();
std::vector<Weights> GetWeightVector();
std::vector<Particle_type> GetParicle_type();

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
        PlotUtils::NamedCategory<Material_type>({kIron}, "Iron"),
        PlotUtils::NamedCategory<Material_type>({kCarbon}, "Carbon"),
        PlotUtils::NamedCategory<Material_type>({kLead}, "Lead"),
        PlotUtils::NamedCategory<Material_type>({kAluminium}, "Aluminium"),
        PlotUtils::NamedCategory<Material_type>({kHelium}, "Helium")

};
const std::vector<
    PlotUtils::NamedCategory<Interaction_type>> InteractionGroup_categories = {
    PlotUtils::NamedCategory<Interaction_type>({kInteraction_OTHER}, "Other"),
    PlotUtils::NamedCategory<Interaction_type>({kInteraction_NONE}, "None"),
    PlotUtils::NamedCategory<Interaction_type>({kDIS}, "DIS"),
    PlotUtils::NamedCategory<Interaction_type>({k2p2h}, "2p2h"),
    PlotUtils::NamedCategory<Interaction_type>({kRes_Coh_Pion}, "Res_Coh"),
    PlotUtils::NamedCategory<Interaction_type>({kElastic}, "Elastic")};

const std::vector<PlotUtils::NamedCategory<
    Interaction_type>> InteractionGroupDISBreakdown_categories = {
    PlotUtils::NamedCategory<Interaction_type>({kInteraction_OTHER}, "Other"),
    PlotUtils::NamedCategory<Interaction_type>({kInteraction_NONE}, "None"),
    PlotUtils::NamedCategory<Interaction_type>({kDISSoft}, "SoftDIS"),
    PlotUtils::NamedCategory<Interaction_type>({kDISHard}, "HardDIS"),
    PlotUtils::NamedCategory<Interaction_type>({kDISSIS}, "SIS"),
    PlotUtils::NamedCategory<Interaction_type>({k2p2h}, "2p2h"),
    PlotUtils::NamedCategory<Interaction_type>({kdeltaRES}, "#DeltaRes"),
    PlotUtils::NamedCategory<Interaction_type>({kHeavierRES}, "HeavierRes"),
    PlotUtils::NamedCategory<Interaction_type>({kElastic}, "QE")};

const std::vector<
    PlotUtils::NamedCategory<Particle_type>> ParticleGroup_categories = {
    PlotUtils::NamedCategory<Particle_type>({kParticle_N_A}, "N_A"),
    PlotUtils::NamedCategory<Particle_type>({kParticle_OTHER}, "Other"),
    PlotUtils::NamedCategory<Particle_type>({kElectron}, "Electron"),
    PlotUtils::NamedCategory<Particle_type>({kMuon}, "Muon"),
    PlotUtils::NamedCategory<Particle_type>({kGamma}, "Gamma"),
    PlotUtils::NamedCategory<Particle_type>({kNeutrino_muon}, "Neutrino_muon"),
    PlotUtils::NamedCategory<Particle_type>({kNeutrino_electron},
                                            "Neutrino_electron"),
    PlotUtils::NamedCategory<Particle_type>({kAnti_Neutrino}, "Anti_Neutrino"),
    PlotUtils::NamedCategory<Particle_type>({kKaon}, "Kaon"),
    PlotUtils::NamedCategory<Particle_type>({kPion_0}, "Pi0"),
    PlotUtils::NamedCategory<Particle_type>({kPion_neg}, "Pi^{-}"),
    PlotUtils::NamedCategory<Particle_type>({kPion_pos}, "Pi^{+}"),
    PlotUtils::NamedCategory<Particle_type>({kProton}, "Proton"),
    PlotUtils::NamedCategory<Particle_type>({kNeutron}, "Neutron"),
    PlotUtils::NamedCategory<Particle_type>({kFourHelium}, "{}^{4}He"),
    PlotUtils::NamedCategory<Particle_type>({kLamdba}, "Lamdba"),
    PlotUtils::NamedCategory<Particle_type>({kSigma_plus}, "Sigma^{+}")

};

const std::vector<PlotUtils::NamedCategory<Particle_type>>
    ParticleGroup_reduced_categories = {
        PlotUtils::NamedCategory<Particle_type>({kParticle_N_A}, "N_A"),
        PlotUtils::NamedCategory<Particle_type>({kParticle_OTHER}, "Other"),
        PlotUtils::NamedCategory<Particle_type>({kParticle_neutral}, "Neutral"),
        PlotUtils::NamedCategory<Particle_type>({kMuon}, "Muon"),
        PlotUtils::NamedCategory<Particle_type>({kPion_0_Electron_kGamma},
                                                "e^{-/+},#gamma,#pi^{0}"),
        PlotUtils::NamedCategory<Particle_type>({kPion_pos_neg}, "Pi^{-/+}"),
        PlotUtils::NamedCategory<Particle_type>({kProton}, "Proton")

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

const int n_flux_universes = 500;

//=====================================================
//=====================================================
// Constuct Error Universes
//=====================================================

std::map<std::string, std::vector<HeliumCVUniverse *>> GetErrorBands(
    PlotUtils::ChainWrapper *chain) {
  typedef std::map<std::string, std::vector<HeliumCVUniverse *>> SystMap;

  SystMap error_bands;

  //========================================================================
  // CV
  //========================================================================

  error_bands[std::string("cv")].push_back(new HeliumCVUniverse(chain));

  //========================================================================
  // Apply Other Error Universes
  //========================================================================

  if (m_RunCodeWithSystematics == true) {
    //========================================================================
    // Flux
    //========================================================================

    SystMap flux_systematics =
        PlotUtils::GetFluxSystematicsMap<HeliumCVUniverse>(chain,
                                                           n_flux_universes);
    error_bands.insert(flux_systematics.begin(), flux_systematics.end());

    //========================================================================
    // GENIE FSI + CrossSection
    //========================================================================

    // SystMap genie_systematics =
    // PlotUtils::GetGenieSystematicsMap<HeliumCVUniverse>(chain);
    // error_bands.insert(genie_systematics.begin(), genie_systematics.end());
    //========================================================================
    // MnvTunes
    //========================================================================
    // 2p2h

    // SystMap a2p2h_systematics =
    // PlotUtils::Get2p2hSystematicsMap<HeliumCVUniverse>(chain);
    // error_bands.insert(a2p2h_systematics.begin(), a2p2h_systematics.end());

    //========================================================================
    // (RPA)random phase appox , long range Nuclear correlations modeling
    //========================================================================

    // SystMap RPA_systematics =
    // PlotUtils::GetRPASystematicsMap<HeliumCVUniverse>(chain);
    // error_bands.insert(RPA_systematics.begin(), RPA_systematics.end());
  }

  // SystMap LowQ2Pi_systematics =
  // PlotUtils::GetLowQ2PiSystematicsMap<HeliumCVUniverse>(chain);
  // error_bands.insert(LowQ2Pi_systematics.begin(), LowQ2Pi_systematics.end());

  // Non-res pi
  // SystMap nonrespi_systematics =
  //  PlotUtils::GetNonResPiSystematicsMap<HeliumCVUniverse>(chain);
  // error_bands.insert(nonrespi_systematics.begin(),
  // nonrespi_systematics.end());

  // GetAngleSystematicsMap

  return error_bands;
}

//======================================================================
// Main Event Loop
//======================================================================
void runEventLoop(ME_helium_Playlists &PlayList_iterator, bool &m_debugOn,
                  bool &Run_EventLoopOnGrid) {
  // Make a chain of events
  loadLibs();

  const std::vector<ECutsTRUTH> kTRUTHCutsVector = GetTRUTHCutsVector();
  const std::vector<Weights> kTRUEWeights_Base = GetWeightVector();
  const std::vector<Particle_type> kSecondary_particle_vector =
      GetParicle_type();
  std::ofstream output("LogFile_TRUTH.txt", std::ofstream::app);

  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
  std::cout << "MC TRUTH LOOP  " << std::endl;
  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
  //////////////////
  TDatabasePDG *pdg_DATABASEobject = TDatabasePDG::Instance();

  //======================================================================
  ////////////////////ADDING TO CHAIN wrapper ///////////////////////////
  //======================================================================
  bool is_mc = true;

  std::string playlist = GetPlaylist(PlayList_iterator);
  //======================================================================
  // SET MINERVA Analysis Type and Universes
  //======================================================================
  MinervaUniverse::SetPlaylist(playlist);
  std::string seestring = MinervaUniverse::GetPlaylist();
  HeliumPlayListInfo Playlist_Info(playlist);
  std::cout << "Working with Playlist =  " << seestring << std::endl;
  MinervaUniverse::SetTruth(true);
  MinervaUniverse::SetNuEConstraint(
      true);  // turns on all Flux weights , NC nuE+e + IMD
  MinervaUniverse::SetAnalysisNuPDG(14);
  MinervaUniverse::SetNFluxUniverses(n_flux_universes);
  MinervaUniverse::SetZExpansionFaReweight(false);
  MinervaUniverse::SetNonResPiReweight(false);
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

  auto Playlist_txtFILEPath =
      GetPlaylist_txtFILE_path(PlayList_iterator, is_mc);
  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
  std::cout << "Adding to Chain Wrapper For Loop   " << std::endl;
  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
  PlotUtils::ChainWrapper *chw_MC =
      makeChainWrapperPtr(Playlist_txtFILEPath.c_str(), "Truth");
  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
  std::cout << "Adding to Chain Wrapper For POT counter   " << std::endl;
  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

  //======================================================================
  ///////////////////Making/adding to error bands  ///////////////////////////
  //======================================================================

  std::map<std::string, std::vector<HeliumCVUniverse *>> error_bands =
      GetErrorBands(chw_MC);

  //======================================================================
  // Group All Vertial Error Bands
  //======================================================================

  std::vector<std::vector<HeliumCVUniverse *>> Error_Band_Universe_GROUPS =
      groupCompatibleUniverses(error_bands);
  std::cout << "Number of Universes set is = "
            << MinervaUniverse::GetNFluxUniverses() << std::endl;
  POTCounter pot_counter;
  const std::string RootName = GetPlaylist_ROOT_path(PlayList_iterator, true);
  // const std::string RootName = GetPlaylist_ROOT_path("1D_EnergyFix",  is_mc
  // );
  std::cout << "The Playlist that is set is = " << seestring << std::endl;
  std::cout << "The Playlist Root = " << RootName << std::endl;
  /// pnfs/minerva/persistent/users/cnguyen/ME_G1_Merg/*.root

  time_t now = time(0);
  tm *ltm = localtime(&now);
  int m_datemonth = 1 + ltm->tm_mon;
  int m_datehour = ltm->tm_hour;
  int m_datemin = ltm->tm_min;
  int m_dateday = ltm->tm_mday;

  output << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  output << "~~~~~~~~Helium Anaylsis Log File ~~~~~~~~~~~~~~~" << endl;
  output << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  output << "~~~~~~~~~~~~Created By ~~~~~~~~~~~~~~" << endl;
  output << "~~~~~~~~~~~Christian Nguyen ~~~~~~~~~~~" << endl;
  output << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  output << "DateRan(min-hour-month-day-year): (" << m_datemin << "-"
         << m_datehour << "-" << m_datemonth << "- " << m_dateday << "-2020)"
         << endl;
  output << "EnergyType: LE" << endl;
  output << "Playlist: " << GetPlaylist_Name(PlayList_iterator) << endl;
  output << "Data TYPE : " << String_Reco_orTruth(false) << endl;
  output << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  int count = 1;

  output << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  output << "~~~~~Truth CUTS Applied for Efficiency Study ~~~~" << endl;
  output << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

  count = 1;
  for (auto true_cut_name : kTRUTHCutsVector) {
    output << count << " TRUTHCUT name: " << GetCutNameTRUTH(true_cut_name)
           << endl;
    count++;
  }

  output << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  output << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  output << "~~~~~WEIGHTS~~~~~~~~~~~~~" << endl;
  output << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

  output << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  output << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

  output << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  output << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

  // LogFile LOGFILE(PlayList_iterator ,kTRUTHCutsVector , kTRUEWeights_v1tune,
  // kTRUTHCutsVector, 1,true,_logfile);
  // LOGFILE<<"Number of Universes set is = "<<
  // MinervaUniverse::GetNFluxUniverses()<<"/n";

  //======================================================================
  // SET Binning for Hist
  //======================================================================

  std::vector<double> Ebin_vector = GetBinMuonVector(kE_2D);
  std::vector<double> Pzbin_vector = GetBinMuonVector(kP_Z_2D);
  std::vector<double> PTbin_vector = GetBinMuonVector(kP_T_2D);

  std::vector<double> bigAngle_bins{0.0, 15.0, 30.0, 45.0, 60.0};

  std::vector<double> MuonThetabin_vector = GetBinMuonVector(kAngleWRTB_2D);
  std::vector<double> Muon_curvatureSig_vector =
      GetBinMuonVector(kcurvatureSig);
  std::vector<double> MuonCharge_vector = GetBinMuonVector(kCharge);
  std::vector<double> MuonMatchtoMinos_vector =
      GetBinMuonVector(kMuonMatchtoMinos);
  std::vector<double> MuonMatchtoVeto_vector =
      GetBinMuonVector(kMuonMatchtoVeto);

  std::vector<double> Minos_R_vector = GetBinMuonVector(kminos_R);
  std::vector<double> AnglePhi_vector = GetBinMuonVector(kAnglePhi);

  std::vector<double> Minos_Start_X_vector = GetBinMuonVector(kminosStart_X);
  std::vector<double> Minos_Start_Y_vector = GetBinMuonVector(kminosStart_Y);
  std::vector<double> Minos_Start_Z_vector = GetBinMuonVector(kminosStart_Z);

  std::vector<double> Minos_End_X_vector = GetBinMuonVector(kminosEnd_X);
  std::vector<double> Minos_End_Y_vector = GetBinMuonVector(kminosEnd_Y);
  std::vector<double> Minos_End_Z_vector = GetBinMuonVector(kminosEnd_Z);

  std::vector<double> Muon_StartNode_X_vector =
      GetBinMuonVector(kmuonFirstNodeX);
  std::vector<double> Muon_StartNode_Y_vector =
      GetBinMuonVector(kmuonFirstNodeY);
  std::vector<double> Muon_StartNode_Z_vector =
      GetBinMuonVector(kmuonFirstNodeZ);

  std::vector<double> Muon_LastNode_X_vector = GetBinMuonVector(kmuonLastNodeX);
  std::vector<double> Muon_LastNode_Y_vector = GetBinMuonVector(kmuonLastNodeY);
  std::vector<double> Muon_LastNode_Z_vector = GetBinMuonVector(kmuonLastNodeZ);
  std::vector<double> TrackSize_vector = GetBinMuonVector(ktracksize);

  //////////////////////////
  // std::vector<double> Vertex_Xbins= GetBinvertexVector(kX);
  // std::vector<double> Vertex_Ybins= GetBinvertexVector(kY);
  // std::vector<double> Vertex_Zbins= GetBinvertexVector(kZ);
  // std::vector<double> Vertex_Rbins= GetBinvertexVector(kR);

  std::vector<double> Vertex_Xbins = GetBinvertexVector(kX_2D);
  std::vector<double> Vertex_Ybins = GetBinvertexVector(kY_2D);
  std::vector<double> Vertex_Zbins = GetBinvertexVector(kZ_2D);
  std::vector<double> Vertex_Rbins = GetBinvertexVector(kR_2D);

  std::vector<double> Vertex_DOCAbins = GetBinMuonVector(kDOCA_muon_2D);
  std::vector<double> Vertex_secondTrkEbins = GetSecondTrkVarVector(ksecE_2D);
  std::vector<double> Vertex_secondTrkTheta_bins =
      GetSecondTrkVarVector(ksecTheta_2D);
  std::vector<double> Vertex_secondTrkDOCA_bins =
      GetSecondTrkVarVector(kDOCA_2D);
  std::vector<double> Vertex_secondTrkPathway_bins =
      GetSecondTrkVarVector(kPathway);

  std::vector<double> SecTrk_Tracklength_vector =
      GetSecondTrkVarVector(ksec_tracklength_minerva_2D);
  std::vector<double> XandYBeamBins = MakeBinVector(250, -1000, 1000);
  std::vector<double> XandYBeamBins_reduced = MakeBinVector(100, -1000, 1000);
  // for(auto a :XandYBeamBins){std::cout<<"bins"<< a << std::endl;}
  //======================================================================
  // muon Varibles
  // Set up TRUE muon Hist
  //======================================================================
  std::vector<double> EnergyNu;  //{0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0,
                                 //9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0,
                                 //16.0, 17.0, 18.0, 19.0, 20.0};
  std::vector<double> EnergyNu_reduced;
  std::vector<double> EnergyNu_reduced2;
  std::vector<double> EnergyNu_coarse{0, 1, 2,  3,  4,  5,  6,  7,
                                      8, 9, 10, 12, 14, 16, 18, 20};
  std::vector<double> EnergyNu_coarse_100{0, 1,  2,  3,  4,  5,  6,  7,  8,
                                          9, 10, 12, 14, 16, 18, 20, 100};
  double edge = 0;
  for (int i = 0; i < 1001; i++) {
    EnergyNu.push_back(edge);
    edge = edge + .1;
  }

  double edge1 = 2;
  for (int i = 0; i < 81; i++) {
    EnergyNu_reduced2.push_back(edge1);
    edge1 = edge1 + .1;
  }

  double edge2 = 0;
  for (int i = 0; i < 201; i++) {
    EnergyNu_reduced.push_back(edge2);
    edge2 = edge2 + .1;
  }

  std::vector<double> EnergySlices{0.0, 1.0, 2.0, 3.0, 4.0};
  std::vector<double> DaisySlices{0.0, 1.0, 2.0, 3.0, 4.0,  5.0,
                                  6.0, 7.0, 8.0, 9.0, 10.0, 11.0};

  PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE(
      "h_Enu_TRUE", "h_Enu_TRUE", EnergyNu, error_bands);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_signalDiff(
      "h_Enu_TRUE_signalDiff", "h_Enu_TRUE_signalDiff", EnergyNu, error_bands);

  PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Slice1(
      "h_Enu_TRUE_Slice1", "h_Enu_TRUE_Slice1", EnergyNu, error_bands);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Slice2(
      "h_Enu_TRUE_Slice2", "h_Enu_TRUE_Slice2", EnergyNu, error_bands);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Slice3(
      "h_Enu_TRUE_Slice3", "h_Enu_TRUE_Slice3", EnergyNu, error_bands);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Slice4(
      "h_Enu_TRUE_Slice4", "h_Enu_TRUE_Slice4", EnergyNu, error_bands);

  PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Slice1_coarse(
      "h_Enu_TRUE_Slice1_coarse", "h_Enu_TRUE_Slice1_coarse", EnergyNu_coarse,
      error_bands);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Slice2_coarse(
      "h_Enu_TRUE_Slice2_coarse", "h_Enu_TRUE_Slice2_coarse", EnergyNu_coarse,
      error_bands);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Slice3_coarse(
      "h_Enu_TRUE_Slice3_coarse", "h_Enu_TRUE_Slice3_coarse", EnergyNu_coarse,
      error_bands);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Slice4_coarse(
      "h_Enu_TRUE_Slice4_coarse", "h_Enu_TRUE_Slice4_coarse", EnergyNu_coarse,
      error_bands);

  PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Enu_Slice_TRUE(
      "h_Enu_Slice_TRUE", "h_Enu_Slice_TRUE", EnergyNu, EnergySlices,
      error_bands);
  PlotUtils::Hist2DWrapper<HeliumCVUniverse> h2_Enu_DAISY_TRUE(
      "h2_Enu_DAISY_TRUE", "h2_Enu_DAISY_TRUE", EnergyNu, DaisySlices,
      error_bands);

  PlotUtils::Hist2DWrapper<HeliumCVUniverse> h2_Enu_DAISY_coarse_TRUE(
      "h2_Enu_DAISY_coarse_TRUE", "h2_Enu_DAISY_coarse_TRUE",
      EnergyNu_coarse_100, DaisySlices, error_bands);

  MnvH2D *h_Enu_TRUE_vertex_X_reduced_Slice1 = new MnvH2D(
      "h_Enu_TRUE_vertex_X_reduced_Slice1",
      "h_Enu_TRUE_vertex_X_reduced_Slice1", EnergyNu_reduced.size() - 1,
      EnergyNu_reduced.data(), XandYBeamBins.size() - 1, XandYBeamBins.data());
  MnvH2D *h_Enu_TRUE_vertex_Y_reduced_Slice1 = new MnvH2D(
      "h_Enu_TRUE_vertex_Y_reduced_Slice1",
      "h_Enu_TRUE_vertex_Y_reduced_Slice1", EnergyNu_reduced.size() - 1,
      EnergyNu_reduced.data(), XandYBeamBins.size() - 1, XandYBeamBins.data());

  MnvH2D *h_Enu_TRUE_vertex_X_reduced_Slice2 = new MnvH2D(
      "h_Enu_TRUE_vertex_X_reduced_Slice2",
      "h_Enu_TRUE_vertex_X_reduced_Slice2", EnergyNu_reduced.size() - 1,
      EnergyNu_reduced.data(), XandYBeamBins.size() - 1, XandYBeamBins.data());
  MnvH2D *h_Enu_TRUE_vertex_Y_reduced_Slice2 = new MnvH2D(
      "h_Enu_TRUE_vertex_Y_reduced_Slice2",
      "h_Enu_TRUE_vertex_Y_reduced_Slice2", EnergyNu_reduced.size() - 1,
      EnergyNu_reduced.data(), XandYBeamBins.size() - 1, XandYBeamBins.data());

  MnvH2D *h_Enu_TRUE_vertex_X_reduced_Slice3 = new MnvH2D(
      "h_Enu_TRUE_vertex_X_reduced_Slice3",
      "h_Enu_TRUE_vertex_X_reduced_Slice3", EnergyNu_reduced.size() - 1,
      EnergyNu_reduced.data(), XandYBeamBins.size() - 1, XandYBeamBins.data());
  MnvH2D *h_Enu_TRUE_vertex_Y_reduced_Slice3 = new MnvH2D(
      "h_Enu_TRUE_vertex_Y_reduced_Slice3",
      "h_Enu_TRUE_vertex_Y_reduced_Slice3", EnergyNu_reduced.size() - 1,
      EnergyNu_reduced.data(), XandYBeamBins.size() - 1, XandYBeamBins.data());

  MnvH2D *h_Enu_TRUE_vertex_X_reduced_Slice4 = new MnvH2D(
      "h_Enu_TRUE_vertex_X_reduced_Slice4",
      "h_Enu_TRUE_vertex_X_reduced_Slice4", EnergyNu_reduced.size() - 1,
      EnergyNu_reduced.data(), XandYBeamBins.size() - 1, XandYBeamBins.data());
  MnvH2D *h_Enu_TRUE_vertex_Y_reduced_Slice4 = new MnvH2D(
      "h_Enu_TRUE_vertex_Y_reduced_Slice4",
      "h_Enu_TRUE_vertex_Y_reduced_Slice4", EnergyNu_reduced.size() - 1,
      EnergyNu_reduced.data(), XandYBeamBins.size() - 1, XandYBeamBins.data());

  // PlotUtils::Hist2DWrapper<HeliumCVUniverse>
  // h_Enu_TRUE_vertex_X("h_Enu_TRUE_vertex_X",    "h_Enu_TRUE_vertex_X",
  // EnergyNu,  XandYBeamBins  ,      error_bands);
  // PlotUtils::Hist2DWrapper<HeliumCVUniverse>
  // h_Enu_TRUE_vertex_Y("h_Enu_TRUE_vertex_Y",    "h_Enu_TRUE_vertex_Y",
  // EnergyNu,  XandYBeamBins  ,      error_bands);

  MnvH2D *h_Enu_TRUE_vertex_X = new MnvH2D(
      "h_Enu_TRUE_vertex_X", "h_Enu_TRUE_vertex_X", EnergyNu.size() - 1,
      EnergyNu.data(), XandYBeamBins.size() - 1, XandYBeamBins.data());
  MnvH2D *h_Enu_TRUE_vertex_Y = new MnvH2D(
      "h_Enu_TRUE_vertex_Y", "h_Enu_TRUE_vertex_Y", EnergyNu.size() - 1,
      EnergyNu.data(), XandYBeamBins.size() - 1, XandYBeamBins.data());

  MnvH2D *h_Enu_TRUE_vertex_X_reduced =
      new MnvH2D("h_Enu_TRUE_vertex_X_reduced", "h_Enu_TRUE_vertex_X_reduced",
                 EnergyNu_reduced.size() - 1, EnergyNu_reduced.data(),
                 XandYBeamBins.size() - 1, XandYBeamBins.data());
  MnvH2D *h_Enu_TRUE_vertex_Y_reduced =
      new MnvH2D("h_Enu_TRUE_vertex_Y_reduced", "h_Enu_TRUE_vertex_Y_reduced",
                 EnergyNu_reduced.size() - 1, EnergyNu_reduced.data(),
                 XandYBeamBins.size() - 1, XandYBeamBins.data());

  MnvH2D *h_Enu_TRUE_vertex_X_reduced1 =
      new MnvH2D("h_Enu_TRUE_vertex_X_reduced1", "h_Enu_TRUE_vertex_X_reduced1",
                 EnergyNu_reduced2.size() - 1, EnergyNu_reduced2.data(),
                 XandYBeamBins.size() - 1, XandYBeamBins.data());
  MnvH2D *h_Enu_TRUE_vertex_Y_reduced1 =
      new MnvH2D("h_Enu_TRUE_vertex_Y_reduced1", "h_Enu_TRUE_vertex_Y_reduced1",
                 EnergyNu_reduced2.size() - 1, EnergyNu_reduced2.data(),
                 XandYBeamBins.size() - 1, XandYBeamBins.data());

  PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Daisy0(
      "h_Enu_TRUE_Daisy0", "h_Enu_TRUE_Daisy0", EnergyNu, error_bands);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Daisy1(
      "h_Enu_TRUE_Daisy1", "h_Enu_TRUE_Daisy1", EnergyNu, error_bands);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Daisy2(
      "h_Enu_TRUE_Daisy2", "h_Enu_TRUE_Daisy2", EnergyNu, error_bands);

  PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Daisy3(
      "h_Enu_TRUE_Daisy3", "h_Enu_TRUE_Daisy3", EnergyNu, error_bands);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Daisy4(
      "h_Enu_TRUE_Daisy4", "h_Enu_TRUE_Daisy4", EnergyNu, error_bands);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Daisy5(
      "h_Enu_TRUE_Daisy5", "h_Enu_TRUE_Daisy5", EnergyNu, error_bands);

  PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Daisy6(
      "h_Enu_TRUE_Daisy6", "h_Enu_TRUE_Daisy6", EnergyNu, error_bands);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Daisy7(
      "h_Enu_TRUE_Daisy7", "h_Enu_TRUE_Daisy7", EnergyNu, error_bands);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Daisy8(
      "h_Enu_TRUE_Daisy8", "h_Enu_TRUE_Daisy8", EnergyNu, error_bands);

  PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Daisy9(
      "h_Enu_TRUE_Daisy9", "h_Enu_TRUE_Daisy9", EnergyNu, error_bands);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Daisy10(
      "h_Enu_TRUE_Daisy10", "h_Enu_TRUE_Daisy10", EnergyNu, error_bands);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Daisy11(
      "h_Enu_TRUE_Daisy11", "h_Enu_TRUE_Daisy11", EnergyNu, error_bands);

  //////////////////////////////////

  PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Daisy0_coarse(
      "h_Enu_TRUE_Daisy0_coarse", "h_Enu_TRUE_Daisy0_coarse", EnergyNu_coarse,
      error_bands);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Daisy1_coarse(
      "h_Enu_TRUE_Daisy1_coarse", "h_Enu_TRUE_Daisy1_coarse", EnergyNu_coarse,
      error_bands);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Daisy2_coarse(
      "h_Enu_TRUE_Daisy2_coarse", "h_Enu_TRUE_Daisy2_coarse", EnergyNu_coarse,
      error_bands);

  PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Daisy3_coarse(
      "h_Enu_TRUE_Daisy3_coarse", "h_Enu_TRUE_Daisy3_coarse", EnergyNu_coarse,
      error_bands);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Daisy4_coarse(
      "h_Enu_TRUE_Daisy4_coarse", "h_Enu_TRUE_Daisy4_coarse", EnergyNu_coarse,
      error_bands);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Daisy5_coarse(
      "h_Enu_TRUE_Daisy5_coarse", "h_Enu_TRUE_Daisy5_coarse", EnergyNu_coarse,
      error_bands);

  PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Daisy6_coarse(
      "h_Enu_TRUE_Daisy6_coarse", "h_Enu_TRUE_Daisy6_coarse", EnergyNu_coarse,
      error_bands);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Daisy7_coarse(
      "h_Enu_TRUE_Daisy7_coarse", "h_Enu_TRUE_Daisy7_coarse", EnergyNu_coarse,
      error_bands);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Daisy8_coarse(
      "h_Enu_TRUE_Daisy8_coarse", "h_Enu_TRUE_Daisy8_coarse", EnergyNu_coarse,
      error_bands);

  PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Daisy9_coarse(
      "h_Enu_TRUE_Daisy9_coarse", "h_Enu_TRUE_Daisy9_coarse", EnergyNu_coarse,
      error_bands);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Daisy10_coarse(
      "h_Enu_TRUE_Daisy10_coarse", "h_Enu_TRUE_Daisy10_coarse", EnergyNu_coarse,
      error_bands);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Daisy11_coarse(
      "h_Enu_TRUE_Daisy11_coarse", "h_Enu_TRUE_Daisy11_coarse", EnergyNu_coarse,
      error_bands);
  ///////////////////

  PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Daisy0_coarse_100(
      "h_Enu_TRUE_Daisy0_coarse_100", "h_Enu_TRUE_Daisy0_coarse_100",
      EnergyNu_coarse, error_bands);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Daisy1_coarse_100(
      "h_Enu_TRUE_Daisy1_coarse_100", "h_Enu_TRUE_Daisy1_coarse_100",
      EnergyNu_coarse, error_bands);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Daisy2_coarse_100(
      "h_Enu_TRUE_Daisy2_coarse_100", "h_Enu_TRUE_Daisy2_coarse_100",
      EnergyNu_coarse, error_bands);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Daisy3_coarse_100(
      "h_Enu_TRUE_Daisy3_coarse_100", "h_Enu_TRUE_Daisy3_coarse_100",
      EnergyNu_coarse, error_bands);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Daisy4_coarse_100(
      "h_Enu_TRUE_Daisy4_coarse_100", "h_Enu_TRUE_Daisy4_coarse_100",
      EnergyNu_coarse, error_bands);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Daisy5_coarse_100(
      "h_Enu_TRUE_Daisy5_coarse_100", "h_Enu_TRUE_Daisy5_coarse_100",
      EnergyNu_coarse, error_bands);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Daisy6_coarse_100(
      "h_Enu_TRUE_Daisy6_coarse_100", "h_Enu_TRUE_Daisy6_coarse_100",
      EnergyNu_coarse, error_bands);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Daisy7_coarse_100(
      "h_Enu_TRUE_Daisy7_coarse_100", "h_Enu_TRUE_Daisy7_coarse_100",
      EnergyNu_coarse, error_bands);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Daisy8_coarse_100(
      "h_Enu_TRUE_Daisy8_coarse_100", "h_Enu_TRUE_Daisy8_coarse_100",
      EnergyNu_coarse, error_bands);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Daisy9_coarse_100(
      "h_Enu_TRUE_Daisy9_coarse_100", "h_Enu_TRUE_Daisy9_coarse_100",
      EnergyNu_coarse, error_bands);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Daisy10_coarse_100(
      "h_Enu_TRUE_Daisy10_coarse_100", "h_Enu_TRUE_Daisy10_coarse_100",
      EnergyNu_coarse, error_bands);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_Daisy11_coarse_100(
      "h_Enu_TRUE_Daisy11_coarse_100", "h_Enu_TRUE_Daisy11_coarse_100",
      EnergyNu_coarse, error_bands);

  std::map<FluxSlices, PlotUtils::HistWrapper<HeliumCVUniverse>> Daisy_MAP;
  Daisy_MAP.insert({kheliumdaisy0, h_Enu_TRUE_Daisy0});
  Daisy_MAP.insert({kheliumdaisy1, h_Enu_TRUE_Daisy1});
  Daisy_MAP.insert({kheliumdaisy2, h_Enu_TRUE_Daisy2});
  Daisy_MAP.insert({kheliumdaisy3, h_Enu_TRUE_Daisy3});
  Daisy_MAP.insert({kheliumdaisy4, h_Enu_TRUE_Daisy4});
  Daisy_MAP.insert({kheliumdaisy5, h_Enu_TRUE_Daisy5});
  Daisy_MAP.insert({kheliumdaisy6, h_Enu_TRUE_Daisy6});
  Daisy_MAP.insert({kheliumdaisy7, h_Enu_TRUE_Daisy7});
  Daisy_MAP.insert({kheliumdaisy8, h_Enu_TRUE_Daisy8});
  Daisy_MAP.insert({kheliumdaisy9, h_Enu_TRUE_Daisy9});
  Daisy_MAP.insert({kheliumdaisy10, h_Enu_TRUE_Daisy10});
  Daisy_MAP.insert({kheliumdaisy11, h_Enu_TRUE_Daisy11});

  std::map<FluxSlices, PlotUtils::HistWrapper<HeliumCVUniverse>>
      Daisy_MAP_coarse;
  Daisy_MAP_coarse.insert({kheliumdaisy0, h_Enu_TRUE_Daisy0_coarse});
  Daisy_MAP_coarse.insert({kheliumdaisy1, h_Enu_TRUE_Daisy1_coarse});
  Daisy_MAP_coarse.insert({kheliumdaisy2, h_Enu_TRUE_Daisy2_coarse});
  Daisy_MAP_coarse.insert({kheliumdaisy3, h_Enu_TRUE_Daisy3_coarse});
  Daisy_MAP_coarse.insert({kheliumdaisy4, h_Enu_TRUE_Daisy4_coarse});
  Daisy_MAP_coarse.insert({kheliumdaisy5, h_Enu_TRUE_Daisy5_coarse});
  Daisy_MAP_coarse.insert({kheliumdaisy6, h_Enu_TRUE_Daisy6_coarse});
  Daisy_MAP_coarse.insert({kheliumdaisy7, h_Enu_TRUE_Daisy7_coarse});
  Daisy_MAP_coarse.insert({kheliumdaisy8, h_Enu_TRUE_Daisy8_coarse});
  Daisy_MAP_coarse.insert({kheliumdaisy9, h_Enu_TRUE_Daisy9_coarse});
  Daisy_MAP_coarse.insert({kheliumdaisy10, h_Enu_TRUE_Daisy10_coarse});
  Daisy_MAP_coarse.insert({kheliumdaisy11, h_Enu_TRUE_Daisy11_coarse});

  std::map<FluxSlices, PlotUtils::HistWrapper<HeliumCVUniverse>>
      Daisy_MAP_coarse_100;
  Daisy_MAP_coarse_100.insert({kheliumdaisy0, h_Enu_TRUE_Daisy0_coarse_100});
  Daisy_MAP_coarse_100.insert({kheliumdaisy1, h_Enu_TRUE_Daisy1_coarse_100});
  Daisy_MAP_coarse_100.insert({kheliumdaisy2, h_Enu_TRUE_Daisy2_coarse_100});
  Daisy_MAP_coarse_100.insert({kheliumdaisy3, h_Enu_TRUE_Daisy3_coarse_100});
  Daisy_MAP_coarse_100.insert({kheliumdaisy4, h_Enu_TRUE_Daisy4_coarse_100});
  Daisy_MAP_coarse_100.insert({kheliumdaisy5, h_Enu_TRUE_Daisy5_coarse_100});
  Daisy_MAP_coarse_100.insert({kheliumdaisy6, h_Enu_TRUE_Daisy6_coarse_100});
  Daisy_MAP_coarse_100.insert({kheliumdaisy7, h_Enu_TRUE_Daisy7_coarse_100});
  Daisy_MAP_coarse_100.insert({kheliumdaisy8, h_Enu_TRUE_Daisy8_coarse_100});
  Daisy_MAP_coarse_100.insert({kheliumdaisy9, h_Enu_TRUE_Daisy9_coarse_100});
  Daisy_MAP_coarse_100.insert({kheliumdaisy10, h_Enu_TRUE_Daisy10_coarse_100});
  Daisy_MAP_coarse_100.insert({kheliumdaisy11, h_Enu_TRUE_Daisy11_coarse_100});

  ///////////////////////////////////////
  //
  ///////////////////////////////////////
  ///////////////////////////////////////
  //
  ///////////////////////////////////////
  ///////////////////////////////////////
  //
  ///////////////////////////////////////
  // MnvH2D *h_2d_Theta_PT_TRUE         =    new MnvH2D("h_2d_Theta_PT_TRUE",
  // "h_2d_Theta_PT_TRUE", MuonThetabin_vector.size()-1,
  // MuonThetabin_vector.data(),PTbin_vector.size()-1, PTbin_vector.data()  );
  // MnvH2D *h_2d_Theta_PT_TRUE_RECO    =    new
  // MnvH2D("h_2d_Theta_PT_TRUE_RECO", "h_2d_Theta_PT_TRUE_RECO",
  // MuonThetabin_vector.size()-1,
  // MuonThetabin_vector.data(),PTbin_vector.size()-1, PTbin_vector.data()  );
  ///////////////////////////////////////
  //
  ///////////////////////////////////////
  ////////////////
  // Vertex Hist///
  ////////////////

  //=========================================
  // Entry Loop For MC
  //=========================================

  bool is_counter = true;

  TRUE_Cut_Map Truth_Cut_Map;
  FillingTruthCountingMap(kTRUTHCutsVector, Truth_Cut_Map);

  ProcInfo_t procInfo;
  gSystem->GetProcInfo(&procInfo);

  std::cout << "Memory/time used so Far: " << procInfo.fMemResident / 1000
            << " MB"
            << " time = " << procInfo.fCpuSys << " Sec"
            << "\n";

  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
  std::cout << "MC LOOP  " << std::endl;
  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

  std::string sysmatics_status;
  if (m_RunCodeWithSystematics == true) {
    sysmatics_status = "Systematics_On";
  } else if (m_RunCodeWithSystematics == false) {
    sysmatics_status = "Systematics_Off";
  }
  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
  std::cout << "~~~~~~~~~  " << sysmatics_status << " ~~~~~~~~~ " << std::endl;
  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
  std::cout << " Starting TRUTH MC LOOP  " << std::endl;
  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

  ///////////////////////////////////////////
  ////
  //// Main Event Selection Loop
  ////
  ///////////////////////////////////////////

  for (int ii = 0; ii < chw_MC->GetEntries(); ++ii) {
    if (ii % 50000 == 0) std::cout << (ii / 1000) << " k " << std::flush;

    //=========================================
    // For every systematic, loop over the universes, and fill the
    // appropriate histogram in the MnvH1D
    //=========================================
    for (auto Universe_GROUP : Error_Band_Universe_GROUPS) {
      Universe_GROUP.front()->SetEntry(ii);

      if (Universe_GROUP.front()->Get_mc_incoming() == 14) {
        //  std::cout<< "Universe_GROUP.front()->Get_mc_incoming() "<<
        //  Universe_GROUP.front()->Get_mc_incoming()<<std::endl;
        if (Universe_GROUP.front()->Get_mc_current() == 1) {
          if (Universe_GROUP.front()->isHeliumInteraction()) {
            if (Universe_GROUP.front()->GetIntactionType() != 8) {  // not 2p2h
              if (TRUTH_IsINFiduicalVolume_new(*Universe_GROUP.front())) {
                for (auto universe : Universe_GROUP) {
                  universe->SetEntry(ii);

                  double mvn1wgt = universe->GetTruthWeightFlux();
                  // std::cout<<"wgt = "<< mvn1wgt<<std::endl;
                  double Enu_input = universe->GetEnuTrue() * .001;
                  h_Enu_TRUE.univHist(universe)->Fill(Enu_input, mvn1wgt);
                  double xtrue = universe->GetTRUE_Vertex_x();
                  double ytrue = universe->GetTRUE_Vertex_y();
                  if (isCV(*universe)) {
                    h_Enu_TRUE_vertex_X->Fill(Enu_input, xtrue, mvn1wgt);
                    h_Enu_TRUE_vertex_Y->Fill(Enu_input, ytrue, mvn1wgt);
                    h_Enu_TRUE_vertex_X_reduced->Fill(Enu_input, xtrue,
                                                      mvn1wgt);
                    h_Enu_TRUE_vertex_Y_reduced->Fill(Enu_input, ytrue,
                                                      mvn1wgt);
                    h_Enu_TRUE_vertex_X_reduced1->Fill(Enu_input, xtrue,
                                                       mvn1wgt);
                    h_Enu_TRUE_vertex_Y_reduced1->Fill(Enu_input, ytrue,
                                                       mvn1wgt);
                  }

                  auto Slicetype = universe->GetTRUERegionSliceHelium();
                  auto Daisytype = universe->GetTRUERegion12DAISY_SliceHelium();
                  int inputslide = returnIntfromHeliumdaisyType(Daisytype);
                  Daisy_MAP[Daisytype].univHist(universe)->Fill(Enu_input,
                                                                mvn1wgt);
                  Daisy_MAP_coarse[Daisytype].univHist(universe)->Fill(
                      Enu_input, mvn1wgt);
                  Daisy_MAP_coarse_100[Daisytype].univHist(universe)->Fill(
                      Enu_input, mvn1wgt);
                  h2_Enu_DAISY_TRUE.univHist(universe)
                      ->Fill(Enu_input, inputslide, mvn1wgt);
                  h2_Enu_DAISY_coarse_TRUE.univHist(universe)
                      ->Fill(Enu_input, inputslide, mvn1wgt);

                  if (Slicetype == kSlice1) {
                    h_Enu_TRUE_Slice1.univHist(universe)
                        ->Fill(Enu_input, mvn1wgt);
                    h_Enu_TRUE_Slice1_coarse.univHist(universe)
                        ->Fill(Enu_input, mvn1wgt);
                    h_Enu_Slice_TRUE.univHist(universe)
                        ->Fill(Enu_input, 0.0, mvn1wgt);
                    if (isCV(*universe)) {
                      h_Enu_TRUE_vertex_X_reduced_Slice1->Fill(Enu_input, xtrue,
                                                               mvn1wgt);
                      h_Enu_TRUE_vertex_Y_reduced_Slice1->Fill(Enu_input, ytrue,
                                                               mvn1wgt);
                    }

                  } else if (Slicetype == kSlice2) {
                    h_Enu_TRUE_Slice2.univHist(universe)
                        ->Fill(Enu_input, mvn1wgt);
                    h_Enu_TRUE_Slice2_coarse.univHist(universe)
                        ->Fill(Enu_input, mvn1wgt);
                    h_Enu_Slice_TRUE.univHist(universe)
                        ->Fill(Enu_input, 1.0, mvn1wgt);
                    if (isCV(*universe)) {
                      h_Enu_TRUE_vertex_X_reduced_Slice2->Fill(Enu_input, xtrue,
                                                               mvn1wgt);
                      h_Enu_TRUE_vertex_Y_reduced_Slice2->Fill(Enu_input, ytrue,
                                                               mvn1wgt);
                    }

                  } else if (Slicetype == kSlice3) {
                    h_Enu_TRUE_Slice3.univHist(universe)
                        ->Fill(Enu_input, mvn1wgt);
                    h_Enu_TRUE_Slice3_coarse.univHist(universe)
                        ->Fill(Enu_input, mvn1wgt);
                    h_Enu_Slice_TRUE.univHist(universe)
                        ->Fill(Enu_input, 2.0, mvn1wgt);
                    if (isCV(*universe)) {
                      h_Enu_TRUE_vertex_X_reduced_Slice3->Fill(Enu_input, xtrue,
                                                               mvn1wgt);
                      h_Enu_TRUE_vertex_Y_reduced_Slice3->Fill(Enu_input, ytrue,
                                                               mvn1wgt);
                    }

                  } else if (Slicetype == kSlice4) {
                    h_Enu_TRUE_Slice4.univHist(universe)
                        ->Fill(Enu_input, mvn1wgt);
                    h_Enu_TRUE_Slice4_coarse.univHist(universe)
                        ->Fill(Enu_input, mvn1wgt);
                    h_Enu_Slice_TRUE.univHist(universe)
                        ->Fill(Enu_input, 3.0, mvn1wgt);
                    if (isCV(*universe)) {
                      h_Enu_TRUE_vertex_X_reduced_Slice4->Fill(Enu_input, xtrue,
                                                               mvn1wgt);
                      h_Enu_TRUE_vertex_Y_reduced_Slice4->Fill(Enu_input, ytrue,
                                                               mvn1wgt);
                    }
                  }
                }  // End of Universe loop
              }    // ENd of Trun Fiduical Volume
            }      // not 2p2h
          }        // is a neutrion helium
        }          //  CC
      }            // is Neutrino

    }  // End of Vertial Band group

  }  // End entries loop

  gSystem->GetProcInfo(&procInfo);
  std::cout << " Done with loop Mem1: " << procInfo.fMemResident / 1000 << " MB"
            << " time = " << procInfo.fCpuSys << " sec"
                                                 "\n";
  ///////////////////////////////////////////////////////////////////////////////
  //
  ///////////////////////////////////////////////////////////////////////////////

  h_Enu_TRUE.SyncCVHistos();
  h2_Enu_DAISY_coarse_TRUE.SyncCVHistos();
  h2_Enu_DAISY_TRUE.SyncCVHistos();
  h_Enu_TRUE_signalDiff.SyncCVHistos();
  h_Enu_TRUE_Slice1.SyncCVHistos();
  h_Enu_TRUE_Slice2.SyncCVHistos();
  h_Enu_TRUE_Slice3.SyncCVHistos();
  h_Enu_TRUE_Slice4.SyncCVHistos();
  h_Enu_Slice_TRUE.SyncCVHistos();
  h_Enu_TRUE_Daisy0.SyncCVHistos();
  h_Enu_TRUE_Daisy1.SyncCVHistos();
  h_Enu_TRUE_Daisy2.SyncCVHistos();
  h_Enu_TRUE_Daisy3.SyncCVHistos();
  h_Enu_TRUE_Daisy4.SyncCVHistos();
  h_Enu_TRUE_Daisy5.SyncCVHistos();
  h_Enu_TRUE_Daisy6.SyncCVHistos();
  h_Enu_TRUE_Daisy7.SyncCVHistos();
  h_Enu_TRUE_Daisy8.SyncCVHistos();
  h_Enu_TRUE_Daisy9.SyncCVHistos();
  h_Enu_TRUE_Daisy10.SyncCVHistos();
  h_Enu_TRUE_Daisy11.SyncCVHistos();

  h_Enu_TRUE_Daisy0_coarse.SyncCVHistos();
  h_Enu_TRUE_Daisy1_coarse.SyncCVHistos();
  h_Enu_TRUE_Daisy2_coarse.SyncCVHistos();
  h_Enu_TRUE_Daisy3_coarse.SyncCVHistos();
  h_Enu_TRUE_Daisy4_coarse.SyncCVHistos();
  h_Enu_TRUE_Daisy5_coarse.SyncCVHistos();
  h_Enu_TRUE_Daisy6_coarse.SyncCVHistos();
  h_Enu_TRUE_Daisy7_coarse.SyncCVHistos();
  h_Enu_TRUE_Daisy8_coarse.SyncCVHistos();
  h_Enu_TRUE_Daisy9_coarse.SyncCVHistos();
  h_Enu_TRUE_Daisy10_coarse.SyncCVHistos();
  h_Enu_TRUE_Daisy11_coarse.SyncCVHistos();

  h_Enu_TRUE_Daisy0_coarse_100.SyncCVHistos();
  h_Enu_TRUE_Daisy1_coarse_100.SyncCVHistos();
  h_Enu_TRUE_Daisy2_coarse_100.SyncCVHistos();
  h_Enu_TRUE_Daisy3_coarse_100.SyncCVHistos();
  h_Enu_TRUE_Daisy4_coarse_100.SyncCVHistos();
  h_Enu_TRUE_Daisy5_coarse_100.SyncCVHistos();
  h_Enu_TRUE_Daisy6_coarse_100.SyncCVHistos();
  h_Enu_TRUE_Daisy7_coarse_100.SyncCVHistos();
  h_Enu_TRUE_Daisy8_coarse_100.SyncCVHistos();
  h_Enu_TRUE_Daisy9_coarse_100.SyncCVHistos();
  h_Enu_TRUE_Daisy10_coarse_100.SyncCVHistos();
  h_Enu_TRUE_Daisy11_coarse_100.SyncCVHistos();

  //=========================================
  // Writing Root File
  //=========================================
  std::string systematics_status;
  if (m_RunCodeWithSystematics == true) {
    sysmatics_status = "All_SysErrorsOn";
    std::cout << "print to: " << sysmatics_status << std::endl;
  } else if (m_RunCodeWithSystematics == false) {
    sysmatics_status = "StatsONLY";
  }

  std::cout << "print to: " << sysmatics_status << std::endl;
  char sysmatics_status_char[sysmatics_status.length() + 1];
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

  sprintf(outFileName, "%s/Histograms_FLUX_%s_%s_%s_Fid.root", rootpathway, c,
          d, sysmatics_status_char);

  std::cout << " Writing output file to: " << outFileName << std::endl;

  TGraph *Truth_2DCuts =
      Make_TruthCut_Tgraph_fromCutMap("Truth_2DCuts", Truth_Cut_Map);
  TFile *outFile = new TFile(outFileName, "RECREATE");

  Truth_2DCuts->Write();

  TChain POT_branch("Meta");
  POT_branch.Add(RootName.c_str());
  TTree *clone = POT_branch.CloneTree();
  clone->Write();

  ////////////////////////////////////////////////

  h_Enu_TRUE.hist->Write();
  h_Enu_TRUE_signalDiff.hist->Write();
  h_Enu_TRUE_Slice1.hist->Write();
  h_Enu_TRUE_Slice2.hist->Write();
  h_Enu_TRUE_Slice3.hist->Write();
  h_Enu_TRUE_Slice4.hist->Write();
  h_Enu_Slice_TRUE.hist->Write();
  h_Enu_TRUE_vertex_X->Write();
  h_Enu_TRUE_vertex_Y->Write();
  h_Enu_TRUE_vertex_X_reduced->Write();
  h_Enu_TRUE_vertex_Y_reduced->Write();
  h_Enu_TRUE_vertex_X_reduced1->Write();
  h_Enu_TRUE_vertex_Y_reduced1->Write();
  h2_Enu_DAISY_TRUE.hist->Write();
  h2_Enu_DAISY_coarse_TRUE.hist->Write();
  h_Enu_TRUE_vertex_X_reduced_Slice1->Write();
  h_Enu_TRUE_vertex_Y_reduced_Slice1->Write();
  h_Enu_TRUE_vertex_X_reduced_Slice2->Write();
  h_Enu_TRUE_vertex_Y_reduced_Slice2->Write();
  h_Enu_TRUE_vertex_X_reduced_Slice3->Write();
  h_Enu_TRUE_vertex_Y_reduced_Slice3->Write();
  h_Enu_TRUE_vertex_X_reduced_Slice4->Write();
  h_Enu_TRUE_vertex_Y_reduced_Slice4->Write();
  h_Enu_TRUE_Daisy0.hist->Write();
  h_Enu_TRUE_Daisy1.hist->Write();
  h_Enu_TRUE_Daisy2.hist->Write();
  h_Enu_TRUE_Daisy3.hist->Write();
  h_Enu_TRUE_Daisy4.hist->Write();
  h_Enu_TRUE_Daisy5.hist->Write();
  h_Enu_TRUE_Daisy6.hist->Write();
  h_Enu_TRUE_Daisy7.hist->Write();
  h_Enu_TRUE_Daisy8.hist->Write();
  h_Enu_TRUE_Daisy9.hist->Write();
  h_Enu_TRUE_Daisy10.hist->Write();
  h_Enu_TRUE_Daisy11.hist->Write();

  h_Enu_TRUE_Daisy0_coarse.hist->Write();
  h_Enu_TRUE_Daisy1_coarse.hist->Write();
  h_Enu_TRUE_Daisy2_coarse.hist->Write();
  h_Enu_TRUE_Daisy3_coarse.hist->Write();
  h_Enu_TRUE_Daisy4_coarse.hist->Write();
  h_Enu_TRUE_Daisy5_coarse.hist->Write();
  h_Enu_TRUE_Daisy6_coarse.hist->Write();
  h_Enu_TRUE_Daisy7_coarse.hist->Write();
  h_Enu_TRUE_Daisy8_coarse.hist->Write();
  h_Enu_TRUE_Daisy9_coarse.hist->Write();
  h_Enu_TRUE_Daisy10_coarse.hist->Write();
  h_Enu_TRUE_Daisy11_coarse.hist->Write();

  h_Enu_TRUE_Daisy0_coarse_100.hist->Write();
  h_Enu_TRUE_Daisy1_coarse_100.hist->Write();
  h_Enu_TRUE_Daisy2_coarse_100.hist->Write();
  h_Enu_TRUE_Daisy3_coarse_100.hist->Write();
  h_Enu_TRUE_Daisy4_coarse_100.hist->Write();
  h_Enu_TRUE_Daisy5_coarse_100.hist->Write();
  h_Enu_TRUE_Daisy6_coarse_100.hist->Write();
  h_Enu_TRUE_Daisy7_coarse_100.hist->Write();
  h_Enu_TRUE_Daisy8_coarse_100.hist->Write();
  h_Enu_TRUE_Daisy9_coarse_100.hist->Write();
  h_Enu_TRUE_Daisy10_coarse_100.hist->Write();
  h_Enu_TRUE_Daisy11_coarse_100.hist->Write();

  outFile->Close();

  for (auto band : error_bands) {
    std::vector<HeliumCVUniverse *> band_universes = band.second;
    for (unsigned int i_universe = 0; i_universe < band_universes.size();
         ++i_universe) {
      delete band_universes[i_universe];
    }
  }

  std::cout << "Success in TRUTH LOOP - You Da Man !?!?" << std::endl;

  TCanvas *can = new TCanvas("can", "can", 1800, 1600);
  sprintf(outFileName, "Histograms_FLUX_%s_%s_%s_Fid.pdf", c, d,
          sysmatics_status_char);
  can->Print(outFileName);
  can->Close();

}  // END of Event Loop

//=========================================
//   //END of Main Event Loop Function
//=========================================
//////////////////////////////////////////////////////////////
std::vector<ECutsTRUTH> GetTRUTHCutsVector() {
  std::vector<ECutsTRUTH> True_vec;
  True_vec.push_back(kTRUTHNoCuts);
  True_vec.push_back(kTRUTHneutrino);
  True_vec.push_back(kTRUTHCCInteraction);
  True_vec.push_back(kTRUTHtarget);
  True_vec.push_back(kTRUTHMuonEnergy);
  True_vec.push_back(kTRUTHMuonAngle);
  True_vec.push_back(kTRUTHFiduical_new);
  True_vec.push_back(kTRUTH_greaterthanoneFS);
  // True_vec.push_back(kTRUTH_secTrk_Angle_threshold);
  // True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);
  True_vec.push_back(
      kTRUTH_No_Neutral_secTrk_Angle_threshold_withProtonanPionThresholds);
  True_vec.push_back(kAllTRUTHCuts);

  return True_vec;
  //#endif
}

//////////////////////////////////////////////////////////////////////////
// GET MUON Varibles
//////////////////////////////////////////////////////////////////////////
std::vector<MuonVar> GetMUONVaribles() {
  //#ifndef __CINT__ // related:
  //https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<MuonVar> MuonVars;

  MuonVars.push_back(kE);
  MuonVars.push_back(kP_Z);
  MuonVars.push_back(kP_T);
  MuonVars.push_back(kAngleWRTB);
  MuonVars.push_back(kDOCA_muon);

  MuonVars.push_back(kTRUTH_E);
  MuonVars.push_back(kTRUTH_P_Z);
  MuonVars.push_back(kTRUTH_P_T);
  MuonVars.push_back(kTRUTH_AngleWRTB);

  return MuonVars;
  //#endif
}

std::vector<Particle_type> GetParicle_type() {
  //#ifndef __CINT__ // related:
  //https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
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
// GET Weight Vector to apply
//////////////////////////////////////////////////////////////////////////
std::vector<Weights> GetWeightVector() {
  std::vector<Weights> weight_vec;

  weight_vec.push_back(kweightFlux);
  // weight_vec.push_back(kweightMinos ); Don't apply Minos efficiency weight to
  // truth
  weight_vec.push_back(kweightGenie);
  weight_vec.push_back(kweight2p2ptune);
  weight_vec.push_back(kweightRPA);
  // weight_vec.push_back(kweight_HeliumTargetMass);
  // weight_vec.push_back(kweightLowQ2Pi);

  return weight_vec;
  //#endif
}

//////////////////////////
/// Main
/////////////////////////

int main(int argc, char *argv[]) {
  std::cout << "This is the playlist " << argv[1] << std::endl;
  std::string playlist_string(argv[1]);
  ME_helium_Playlists Playlist_to_run = GetPlaylist_FromString(playlist_string);

  bool m_cutson = true;
  std::cout << "Run over cutsOn?  (0 = false, 1 = true) " << std::endl;
  // std::cin >> cutsOn;
  std::cout << std::boolalpha << m_cutson << std::endl;

  bool m_debugOn = true;
  std::cout << "Run in Debug Mode? (0 = NO, 1 = YES) " << std::endl;
  // std::cin >> my_debug;
  std::cout << std::boolalpha << m_debugOn << std::endl;

  bool Run_EventLoopOnGrid = false;
  if (Run_EventLoopOnGrid == true) {
    std::cout << "This Eventloop is step up to run on the Grid" << std::endl;
  } else {
    std::cout << "This Eventloop is step up to run locally" << std::endl;
  }

  runEventLoop(Playlist_to_run, m_debugOn, Run_EventLoopOnGrid);
  return 0;
}

//#endif
