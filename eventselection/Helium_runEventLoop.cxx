// * Uses the New Systematics Framework and "Universe" objects.
// * loop universes, make cuts and fill histograms with the correct lateral
// shifts and weights for each universe.
// * TChain --> PlotUtils::ChainWrapper.
// * MnvHXD --> PlotUtils::HistWrapper.
// * Genie, flux, non-resonant pion, and some detector systematics calculated.
#include "Helium_runEventLoop.h"

std::string OUTputRoot_pathway = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles";
//=====================================================
// Functions
//=====================================================
std::vector<ECuts> GetRECOCutsVector();
std::vector<ECuts> GetRECOCutsForEffVector();
std::vector<ECutsTRUTH> GetTRUTHCutsVector();
std::vector<ECutsTRUTH> GetTRUTHCutsVector_Energy();
std::vector<MuonVar> GetMUONVaribles();
std::vector<SecondTrkVar> GetPlayListSecondTrkVector();
std::vector<CryoVertex> GetCryoVertexVaribles();
std::vector<ME_helium_Playlists> GetPlayListVector();
std::vector<ME_helium_Playlists> GetTRUEPlayListVector();
std::vector<Particle_type>  GetParicle_type();
std::vector<Weights> GetWeightVector();
std::vector<Weights> GetWeightVector_v2();
std::vector<Weights> GetWeightVector_mk();
//double Mev_to_GeV=.001;



// Get container of systematic
const bool m_RunCodeWithSystematics = true;

//vector <EventRunMAP> secTrkLowEnergy, secTrkHighAngle, secTrkLowEnergyAndHighAngle;

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

/*
const std::vector<PlotUtils::NamedCategory<Particle_type>>
ParticleGroup_categories = {
  PlotUtils::NamedCategory<Particle_type>({kParticle_N_A},   "N_A"),
  PlotUtils::NamedCategory<Particle_type>({kParticle_OTHER}, "Other"),
  PlotUtils::NamedCategory<Particle_type>({kElectron},       "Electron"),
  PlotUtils::NamedCategory<Particle_type>({kMuon},           "Muon"),
  PlotUtils::NamedCategory<Particle_type>({kGamma},          "Gamma"),
  PlotUtils::NamedCategory<Particle_type>({kNeutrino_muon}, "Neutrino_muon"),
  PlotUtils::NamedCategory<Particle_type>({kNeutrino_electron}, "Neutrino_electron"),
  PlotUtils::NamedCategory<Particle_type>({kAnti_Neutrino}, "Anti_Neutrino"),
  PlotUtils::NamedCategory<Particle_type>({kKaon},           "Kaon"),
  PlotUtils::NamedCategory<Particle_type>({kPion_0},         "Pi0"),
  PlotUtils::NamedCategory<Particle_type>({kPion_neg},       "Pi^{-}"),
  PlotUtils::NamedCategory<Particle_type>({kPion_pos},       "Pi^{+}"),
  PlotUtils::NamedCategory<Particle_type>({kProton},         "Proton"),
  PlotUtils::NamedCategory<Particle_type>({kNeutron},        "Neutron")
};
*/
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


const std::vector<PlotUtils::NamedCategory<Veto_status_type>>
Veto_PMT_status_Category = {
  PlotUtils::NamedCategory<Veto_status_type>({kPMTON}, "PMT_ON"),
  PlotUtils::NamedCategory<Veto_status_type>({kPMTOFF}, "PMT_OFF")
};

const std::vector<PlotUtils::NamedCategory<TrackType>>
TrackType_Category = {
  PlotUtils::NamedCategory<TrackType>({kShort},     "ShortTracks"),
  PlotUtils::NamedCategory<TrackType>({kLong},      "LongTracks"),
  PlotUtils::NamedCategory<TrackType>({kOtherLong}, "OtherLongTracks"),
  PlotUtils::NamedCategory<TrackType>({kNotdefinedTrack}, "NotDefinedTracks")
};


const std::vector<PlotUtils::NamedCategory<VertexOptions>>
VertexOptions_Category = {
  PlotUtils::NamedCategory<VertexOptions>({kOpt_1}, "VertexOpt1"),
  PlotUtils::NamedCategory<VertexOptions>({kOpt_2}, "VertexOpt2"),
  PlotUtils::NamedCategory<VertexOptions>({kOpt_3}, "VertexOpt3"),
  PlotUtils::NamedCategory<VertexOptions>({kOpt_4}, "VertexOpt4")
};


const std::vector<PlotUtils::NamedCategory<boolNTrack>>
boolNTrack_Category = {
  PlotUtils::NamedCategory<boolNTrack>({kone_Trk},    "OneTrkTrue"),
  PlotUtils::NamedCategory<boolNTrack>({ktwo_Trk},    "TwoTrkTrue"),
  PlotUtils::NamedCategory<boolNTrack>({kmore_Trk},   "morethan2TrkTrue"),
  PlotUtils::NamedCategory<boolNTrack>({kallfalseTrk},"AllfalseTrk")
};

/*const auto TracksGreaterThan2 = {  NamedCategory<int>({3},   "ThirdTrack"),
                                   NamedCategory<int>({4},   "FourthTrack"),
                                   NamedCategory<int>({5},   "FifthTrack"),
                                   NamedCategory<int>({6},   "SixthTrack"),
                                   NamedCategory<int>({7},   "SevethTrack"),
                                   NamedCategory<int>({8},   "EighthTrack")

                                 };*/
/*
const std::vector<PlotUtils::NamedCategory<Particle_type>>
ParticleGroup_leadingvsnonleading_categories = {
  PlotUtils::NamedCategory<Particle_type>({kParticle_OTHER}, "Other"),
  PlotUtils::NamedCategory<Particle_type>({kPion_0},         "Pi0"),
  PlotUtils::NamedCategory<Particle_type>({kPion_neg},       "Pi^{-}"),
  PlotUtils::NamedCategory<Particle_type>({kPion_pos},       "Pi^{+}"),
  PlotUtils::NamedCategory<Particle_type>({kProton},         "Proton"),
  PlotUtils::NamedCategory<Particle_type>({kNeutron},   "Neutron")
};
*/
const int n_flux_universes = 100;
std::vector<int> Helium9_colorScheme = {
    TColor::GetColor("#BBCCEE"),  // paleBlue
    TColor::GetColor("#CCEEFF"),  // pale cyan
    TColor::GetColor("#CCDDAA"),  // pale greeen
    TColor::GetColor("#EEEEBB"),  // pale yellow
    TColor::GetColor("#FFCCCC"), // pale red
    TColor::GetColor("#DDDDDD"),  // pale grey
    TColor::GetColor("#222255"),  // dark Blue
    TColor::GetColor("#225555"),  // dark cyan
    TColor::GetColor("#225522"),  // dark green
    TColor::GetColor("#666633"),  // dark yellow
    TColor::GetColor("#66333"),  // dark red
    TColor::GetColor("#555555")  // dark grey
};

//typedef std::map< std::string, std::vector<HeliumCVUniverse*> > UniverseMap;

UniverseMap GetErrorBands(PlotUtils::ChainWrapper* chain) {

    //return Map
    UniverseMap error_bands;

    // CV
    error_bands[std::string("cv")].push_back( new HeliumCVUniverse(chain) );

    //Detector systematics, lateral sh

if(m_RunCodeWithSystematics){

    //========================================================================
    // FLUX
    //========================================================================

    UniverseMap flux_systematics = PlotUtils::GetFluxSystematicsMap<HeliumCVUniverse>(chain,n_flux_universes);
    error_bands.insert(flux_systematics.begin(), flux_systematics.end());

    //========================================================================
    // Muons
    //========================================================================

    ///// MINOS ERROR systems
    // Muon reco in MINERvA -- Catchall systematic for pmu reco in minerva.
    // Lateral-only. Shifts pmu.

    UniverseMap MinervaMuon_systematics = PlotUtils::GetMinervaMuonSystematicsMap<HeliumCVUniverse>(chain);
    error_bands.insert(MinervaMuon_systematics.begin(), MinervaMuon_systematics.end());
    // Minerva Error System

    // Vertical only
    // MINOS efficiency

    UniverseMap MinosMuon_systematics = PlotUtils::GetMinosMuonSystematicsMap<HeliumCVUniverse>(chain);
    error_bands.insert(MinosMuon_systematics.begin(), MinosMuon_systematics.end());

    // Muon match efficiency
    UniverseMap MinosEff_systematics = PlotUtils::GetMinosEfficiencySystematicsMap<HeliumCVUniverse>(chain);
    error_bands.insert(MinosEff_systematics.begin(), MinosEff_systematics.end());


   // Beam Angle
    UniverseMap angle_systematics = PlotUtils::GetAngleSystematicsMap<HeliumCVUniverse>(chain);/*,NSFDefaults::beamThetaX_Err,NSFDefaults::beamThetaY_Err*/
    error_bands.insert(angle_systematics.begin(), angle_systematics.end());

    //========================================================================
    // GENIE
    //========================================================================
    // Standard

    UniverseMap genie_systematics = PlotUtils::GetGenieSystematicsMap<HeliumCVUniverse>(chain);
    error_bands.insert(genie_systematics.begin(), genie_systematics.end());

    //========================================================================
     // MnvTunes
     //========================================================================
     // 2p2h

    UniverseMap a2p2h_systematics = PlotUtils::Get2p2hSystematicsMap<HeliumCVUniverse>(chain);
    error_bands.insert(a2p2h_systematics.begin(), a2p2h_systematics .end());

    // RPA
    UniverseMap RPA_systematics = PlotUtils::GetRPASystematicsMap<HeliumCVUniverse>(chain);
    error_bands.insert(RPA_systematics.begin(), RPA_systematics.end());

    //========================================================================
    // Helium
    //========================================================================

    UniverseMap VertexSmearing_systematics = GetHELIUMVertexSmearingShiftSystematicsMap<HeliumCVUniverse>(chain);
    error_bands.insert(VertexSmearing_systematics.begin(), VertexSmearing_systematics.end());


    UniverseMap HeliumTargetMass_systematics = GetHeliumTargetMassSystematicsMap<HeliumCVUniverse>(chain);
    error_bands.insert(HeliumTargetMass_systematics.begin(), HeliumTargetMass_systematics.end());

    // response efficiency
    //UniverseMap recoil_systematics = PlotUtils::GetRecoilSystematicsMap<HeliumCVUniverse>(chain,true);
    //error_bands.insert(recoil_systematics.begin(), recoil_systematics.end());
    //Flux


    //UniverseMap LowQ2Pi_systematics = PlotUtils::GetLowQ2PiSystematicsMap<HeliumCVUniverse>(chain);
    //error_bands.insert(LowQ2Pi_systematics.begin(), LowQ2Pi_systematics.end());

}

  // Non-res pi
  //UniverseMap nonrespi_systematics =
  //  PlotUtils::GetNonResPiSystematicsMap<HeliumCVUniverse>(chain);
  //error_bands.insert(nonrespi_systematics.begin(), nonrespi_systematics.end());

  return error_bands;
}
//======================================================================
//void EventCounter(const HeliumCVUniverse& , std::vector<ECuts> cuts, EventCount_RECO &Event_map ,bool is_mc,HeliumPlayListInfo Info );


// Main
void runEventLoop(bool &m_debugOn, ME_helium_Playlists &PlayList_iterator, bool &Run_EventLoopOnGid) {
  // Make a chain of events
  loadLibs();
//std::vector<ECuts> kCutsVector;
int Study_cap=40;
int Study_count=0;
double POT[4];
const std::vector<ECuts> kCutsVector = GetRECOCutsVector();
const std::vector<ECuts> kCutsVector_Eff = GetRECOCutsForEffVector();
const std::vector<ECutsTRUTH> kTRUTHCutsVector = GetTRUTHCutsVector_Energy();//GetTRUTHCutsVector();
const std::vector<ECutsTRUTH> kTRUTHCutsVector_Energy =  GetTRUTHCutsVector_Energy();


const std::vector<ME_helium_Playlists> kPlayListVector = GetPlayListVector();
const std::vector<ME_helium_Playlists> kTRUEPlayListVector = GetTRUEPlayListVector();

const std::vector<Weights> kWeights_v1tune= GetWeightVector();
const std::vector<Weights> kWeights_v2tune= GetWeightVector_v2();
const std::vector<Weights> kWeights_forMK = GetWeightVector_mk();
const std::vector<MuonVar> kMuonVaribles_vector = GetMUONVaribles();
const std::vector<SecondTrkVar> ksecTrkVaribles_vector = GetPlayListSecondTrkVector();

const std::vector<CryoVertex> kCryoVertexVaribles_vector = GetCryoVertexVaribles();
EventPlaylist_RecoCount EventCountMap;

const std::vector<Particle_type> kSecondary_particle_vector = GetParicle_type();
TH1::AddDirectory(kFALSE);

const double toDegs = 180.0/TMath::Pi();
//======================================================================
////////////////////ADDING TO CHAIN wrapper ///////////////////////////
//======================================================================
bool is_mc= true;
//PlotUtils::ChainWrapper* chw_FullMC = makeChainWrapperPtr("../playlists/playlist_MC_Mvn13C_ecoicaPlus_8_23_19.txt", "Muon");//
//PlotUtils::ChainWrapper* chw_MC = makeChainWrapperPtr("../playlists/MC_Playlist/ME_1G_MC.txt", "Muon");//
//PlotUtils::ChainWrapper* chw_MC = makeChainWrapperPtr("../playlists/MC_Playlist/ME_1A_MC.txt", "Muon");//
//PlotUtils::ChainWrapper* chw_MC = makeChainWrapperPtr("../playlists/MC_Playlist/ME_1A_MC.txt", "Muon");//

 TDatabasePDG *pdg_DATABASEobject = TDatabasePDG::Instance();

 MinervaUniverse::SetTruth(false);
  MinervaUniverse::SetDeuteriumGeniePiTune(false);
  MinervaUniverse::SetNuEConstraint(true);
  MinervaUniverse::SetZExpansionFaReweight(false);
  MinervaUniverse::SetAnalysisNuPDG(14);
  MinervaUniverse::SetNonResPiReweight(true);
  MinervaUniverse::SetNFluxUniverses(n_flux_universes);
  std::string playlist = GetPlaylist(PlayList_iterator);

  MinervaUniverse::SetPlaylist(playlist);
  int otherlongtrack=0;

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
  PlotUtils::ChainWrapper* chw_MC = makeChainWrapperPtr(Playlist_txtFILEPath.c_str(), "HeAnaTupleTool");
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"Adding to Chain Wrapper For POT counter   "<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  PlotUtils::ChainWrapper* mcchainPOT = makeChainWrapperPtr(Playlist_txtFILEPath.c_str(), "Meta");

  //======================================================================
  ///////////////////Making/adding to error bands  ///////////////////////////
  //======================================================================
//std::map< std::string, std::vector<HeliumCVUniverse*> > error_bands = GetErrorBands(chw_FullMC);
UniverseMap error_bands = GetErrorBands(chw_MC);
for(auto band :error_bands ){std::cout<<"Checking Universe this is universe with name : " << band.first<<std::endl;}
std::vector<std::vector<HeliumCVUniverse*>> Error_Band_Universe_GROUPS = groupCompatibleUniverses(error_bands);



double mcPOT = GetPOT_local(mcchainPOT, "MC");
std::cout<<"Number of Universes set is = "<< 	MinervaUniverse::GetNFluxUniverses()<<std::endl;
std::cout << "POT of this Playlist = "<< mcPOT <<std::endl;


static weightMK *weight_MK;
char *mparalocation = std::getenv("MPARAMFILESROOT");
string dir_data = string(mparalocation)+"/data/Reweight/";
weight_MK = new weightMK(dir_data + "output_ratio_genie_neut_for_MKmodel.root");

//MinervaUniverse::SetNFluxUniverses(25);
POTCounter pot_counter;


//MinervaUniverse::SetPlaylist_AGAIN(playlist);


const std::string RootName = GetPlaylist_ROOT_path(PlayList_iterator, is_mc );
//const std::string RootName = GetPlaylist_ROOT_path("1G_MC_vertexweightto10mm",  is_mc );
//const std::string RootName = GetPlaylist_ROOT_path("1F_Bugfix",  is_mc );
std::cout<<"The Playlist that is set is = "<< playlist.c_str()<<std::endl;
std::cout<<"The Playlist Root = "<< RootName<<std::endl;
 ///pnfs/minerva/persistent/users/cnguyen/ME_G1_Merg/*.rot


  auto mcscale = 1.0; //Data_POT_full/ MC_POT_full;


    HeliumPlayListInfo Playlist_Info(playlist);
    std::cout<<"Working with Playlist =  "<<  Playlist_Info.GetPlaylistname()<<std::endl;



//Bins for varibles //
//Muons ///////////////////
std::vector<double> Ebin_vector = GetBinMuonVector(kE);
std::vector<double> Pzbin_vector= GetBinMuonVector(kP_Z);
std::vector<double> PTbin_vector= GetBinMuonVector(kP_T);
std::vector<double> MuonThetabin_vector= GetBinMuonVector(kAngleWRTB);
std::vector<double> Muon_curvatureSig_vector= GetBinMuonVector(kcurvatureSig);
std::vector<double> MuonCharge_vector= GetBinMuonVector(kCharge);
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

std::vector<double> VectexTiming_vector = GetBinMuonVector(kmuonVertexTiming);
std::vector<double> Vertex_ChiSqFit_vector= GetBinvertexVector(kfitConverge);
////////////////////////
std::vector<double> Vertex_Xbin_vector= GetBinvertexVector(kX);
std::vector<double> Vertex_Ybin_vector= GetBinvertexVector(kY);
std::vector<double> Vertex_Zbin_vector= GetBinvertexVector(kZ);
std::vector<double> Vertex_Rbin_vector= GetBinvertexVector(kR);

std::vector<double> secTrk_Thetamidbin_vector= GetSecondTrkVarVector(kThetamid);
std::vector<double> secTrk_Theta_TRUEbin_vector = GetSecondTrkVarVector(kThetamid);//GetSecondTrkVarVector(kFullAngle);


std::vector<double> Vertex_DOCAbin_vector= GetBinMuonVector(kDOCA_muon);
std::vector<double> Vertex_secondTrkEbin_vector = GetSecondTrkVarVector(ksecE);  //GetSecondTrkVarVector(ksecE);,ksecE_Proton
std::vector<double> Vertex_secondTrkEbin_Proton_vector= GetSecondTrkVarVector(ksecE_Proton);
//std::sort(Vertex_secondTrkEbin_Proton_vector.begin(),Vertex_secondTrkEbin_Proton_vector.end());
std::vector<double> Vertex_secondTrkThetamidbin_vector= GetSecondTrkVarVector(kThetamid);
std::vector<double> secTrk_DOCA_vector= GetSecondTrkVarVector(kDOCA);
std::vector<double> secTrk_Pathway_vector= GetSecondTrkVarVector(kPathway);

std::vector<double> MuonMatchtoMinos_vector= GetBinMuonVector(kMuonMatchtoMinos);
std::vector<double> TrackSize_vector= GetBinMuonVector(ktracksize);
std::vector<double> MuonMatchtoVeto_vector= GetBinMuonVector(kMuonMatchtoVeto);

std::vector<double> Veto_PMTmap_vector = GetVetowall_BinVetor(kPMTMap);

std::vector<double> secTrk_StartNode_X_vector= GetSecondTrkVarVector(kFirstsecTrk_Xnode);
std::vector<double> secTrk_StartNode_Y_vector= GetSecondTrkVarVector(kFirstsecTrk_Ynode);
std::vector<double> secTrk_StartNode_Z_vector= GetSecondTrkVarVector(kFirstsecTrk_Znode);

std::vector<double> secTrk_LastNodeX_vector= GetSecondTrkVarVector(kLastsecTrk_Xnode);
std::vector<double> secTrk_LastNodeY_vector= GetSecondTrkVarVector(kLastsecTrk_Ynode);
std::vector<double> secTrk_LastNodeZ_vector= GetSecondTrkVarVector(kLastsecTrk_Znode);

std::vector <True_Event_info> N_A_secTrkParticle;
double greatest_Chisqrt =0.0;
std::vector<double> Recoil_track_length_vector;
double recoil_bin_count=0.0;
for(int ww = 0; ww < 50; ww++ ){
Recoil_track_length_vector.push_back(recoil_bin_count);
recoil_bin_count = recoil_bin_count + 2.54; // bins in [cm]
}

std::vector<double> pseudorapidity_muon_vector{1.0, 1.5, 2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5, 3.75, 4.0, 4.5, 5.0, 8.0};
std::vector<double> rapidity_muon_vector{2.25,  2.45,  2.65,   2.85,  3.05,  3.25, 3.45, 3.65};

////////////////
//muon Varibles///
////////////////
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<std::endl;
std::cout<<"Starting to initialize Bins "<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<std::endl;

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<std::endl;
std::cout<<"~~~~ initialize Muon Varibles  ~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<std::endl;

PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonCharge("h_MuonCharge", "Muon Charge", MuonCharge_vector , error_bands);

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<std::endl;
std::cout<<"~~~~ starting first set of HistFolio  ~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<std::endl;

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<std::endl;
std::cout<<"~~~~ starting Material HistFolio  ~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<std::endl;

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonCharge_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonCharge_Material", MuonCharge_vector  ,"h_MuonCharge_Material; [charge];Events");

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<std::endl;
std::cout<<"~~~~ starting Interaction HistFolio  ~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<std::endl;


PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonCharge_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_MuonCharge_Interaction", MuonCharge_vector  ,"h_MuonCharge_Interaction; [charge];Events");

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<std::endl;
std::cout<<"~~~~ starting Particle_type HistFolio  ~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<std::endl;

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_MuonCharge_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_MuonCharge_Particle", MuonCharge_vector ," h_MuonCharge_Particle; [charge];Events");

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<std::endl;
std::cout<<"~~~~ Finished 1 set  ~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<std::endl;


//h_MuonCharge_Particle.ApplyColorPalette(Helium9_colorScheme);

PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonMatchtoMinos("h_MuonMatchtoMinos", "Is It Matched (bool)", MuonMatchtoMinos_vector , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonMatchtoMinos_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonMatchtoMinos_Material", MuonMatchtoMinos_vector ,"h_MuonMatchtoMinos_Material; [bool];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonMatchtoMinos_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_MuonMatchtoMinos_Interaction",MuonMatchtoMinos_vector  ,"h_MuonMatchtoMinos_Interaction; [bool];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_MuonMatchtoMinos_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_MuonMatchtoMinos_Particle",MuonMatchtoMinos_vector ," h_MuonMatchtoMinos_Particle; [bool];Events");
//h_MuonMatchtoMinos_Particle.ApplyColorPalette(Helium9_colorScheme);

PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE("h_MuonE", "Muon_{E} NEW Method", Ebin_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE_Fake("h_MuonE_Fake", "Muon_{E} NEW Method", Ebin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE_Fake2("h_MuonE_Fake2", "Muon_{E} NEW Method", Ebin_vector , error_bands);
MnvH1D *h_MuonE_MKmodel    =    new MnvH1D("h_MuonE_MKmodel", "h_MuonE_MKmodel", Ebin_vector.size()-1, Ebin_vector.data() );
MnvH1D *h_MuonE_v2tune    =    new MnvH1D("h_MuonE_v2tune", "h_MuonE_v2tune", Ebin_vector.size()-1, Ebin_vector.data() );


PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE_TRUE_RECO("h_MuonE_TRUE_RECO", "Muon_{E} NEW Method", Ebin_vector , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonE_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonE_Material", Ebin_vector ,"MuonE_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_MuonE_Interaction", Ebin_vector ,"MuonE_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_MuonE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_MuonE_Particle", Ebin_vector ,"MuonE_Particle; [GeV];Events");

//h_MuonE_Particle.ApplyColorPalette(Helium9_colorScheme);


PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonE_TRUE_RECO_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonE_Material", Ebin_vector ,"MuonE_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonE_TRUE_RECO_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_MuonE_Interaction", Ebin_vector ,"MuonE_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_MuonE_TRUE_RECO_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_MuonE_Particle", Ebin_vector ,"MuonE_Particle; [GeV];Events");



PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPZ("h_MuonPZ", "Muon_{PZ} NEW Method",  Pzbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPZ_Fake("h_MuonPZ_Fake", "Muon_{PZ} NEW Method",  Pzbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPZ_Fake2("h_MuonPZ_Fake2", "Muon_{PZ} NEW Method",  Pzbin_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPZ_TRUE_RECO("h_MuonPZ_TRUE_RECO", "Muon_{PZ} NEW Method",  Pzbin_vector , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonPZ_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonPZ_Material", Pzbin_vector ,"h_MuonPZ_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonPZ_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_MuonPZ_Interaction", Pzbin_vector ,"h_MuonPZ_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_MuonPZ_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_MuonPZ_Particle", Pzbin_vector ,"h_MuonPZ_Particle; [GeV];Events");
//h_MuonPZ_Particle.ApplyColorPalette(Helium9_colorScheme);


PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPT("h_MuonPT", "Muon_{PT} NEW Method",  PTbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPT_Fake("h_MuonPT_Fake", "Muon_{PT} NEW Method",  PTbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPT_Fake2("h_MuonPT_Fake2", "Muon_{PT} NEW Method",  PTbin_vector , error_bands);


PlotUtils::HistWrapper<HeliumCVUniverse> h_Muon_pseudorapidity("h_Muon_pseudorapidity", "h_Muon_pseudorapidity", pseudorapidity_muon_vector  , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Muon_pseudorapidity_angle("h_Muon_pseudorapidity_angle", "h_Muon_pseudorapidity_angle", MuonThetabin_vector  , error_bands);


PlotUtils::HistWrapper<HeliumCVUniverse> h_Muon_rapidity("h_Muon_rapidity", "h_Muon_rapidity", rapidity_muon_vector  , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPT_TRUE_RECO("h_MuonPT_TRUE_RECO", "Muon_{PT} NEW Method",  PTbin_vector , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonPT_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonPT_Material", PTbin_vector ,"h_MuonPT_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonPT_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_MuonPT_Interaction", PTbin_vector ,"h_MuonPT_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_MuonPT_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_MuonPT_Particle", PTbin_vector ,"h_MuonPT_Particle; [GeV];Events");
//h_MuonPT_Particle.ApplyColorPalette(Helium9_colorScheme);

PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonCurvatureSig("h_MuonCurvatureSig", "(q/p) / #sigma(q/p)",  Muon_curvatureSig_vector , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonCurvatureSig_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonCurvatureSig_Material", Muon_curvatureSig_vector ,"h_MuonCurvatureSig_Material; [#sigma(q/p)];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonCurvatureSig_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_MuonCurvatureSig_Interaction", Muon_curvatureSig_vector ,"h_MuonCurvatureSig_Interaction; [#sigma(q/p)];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_MuonCurvatureSig_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_MuonCurvatureSig_Particle", Muon_curvatureSig_vector ,"h_MuonCurvatureSig_Particle; [];Events");
//h_MuonCurvatureSig_Particle.ApplyColorPalette(Helium9_colorScheme);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonTheta("h_MuonTheta", "MuonTheta [Deg]",  MuonThetabin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonTheta_Fake("h_MuonTheta_Fake", "MuonTheta [Deg]",  MuonThetabin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonTheta_Fake2("h_MuonTheta_Fake2", "MuonTheta [Deg]",  MuonThetabin_vector , error_bands);



PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonTheta_TRUE_RECO("h_MuonTheta_TRUE_RECO", "MuonTheta [Deg]",  MuonThetabin_vector , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonTheta_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonTheta_Material", MuonThetabin_vector ,"h_MuonTheta_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonTheta_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_MuonTheta_Interaction", MuonThetabin_vector ,"h_MuonTheta_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_MuonTheta_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_MuonTheta_Particle", MuonThetabin_vector ,"h_MuonTheta_Particle; [GeV];Events");
//h_MuonTheta_Particle.ApplyColorPalette(Helium9_colorScheme);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPhi("h_MuonPhi", "Muon Phi [Deg]",  AnglePhi_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPhi_TRUE_RECO("h_MuonPhi_TRUE_RECO", "Muon Phi [Deg]",  AnglePhi_vector , error_bands);


PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonPhi_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonPhi_Material", AnglePhi_vector ,"h_MuonPhi_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonPhi_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_MuonPhi_Interaction", AnglePhi_vector ,"h_MuonPhi_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_MuonPhi_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_MuonPhi_Particle", AnglePhi_vector ,"h_MuonPhi_Particle; [GeV];Events");

//h_MuonPhi_Particle.ApplyColorPalette(Helium9_colorScheme);

PlotUtils::HistWrapper<HeliumCVUniverse> h_Tracksize("h_Tracksize", "Track size [N]",  TrackSize_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Tracksize_TRUE_RECO("h_Tracksize_TRUE_RECO", "Tracksize_TRUE_RECO", TrackSize_vector , error_bands);


PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Tracksize_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Tracksize_Material", TrackSize_vector ,"h_Tracksize_Material; [Tracknumber];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_Tracksize_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_Tracksize_Interaction", TrackSize_vector ,"h_Tracksize_Interaction; [Tracknumber];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_Tracksize_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_Tracksize_Particle", TrackSize_vector ,"h_Tracksize_Particle; [Tracknumber];Events");
h_Tracksize_Particle.ApplyColorPalette(Helium9_colorScheme);

PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonDOCA("h_MuonDOCA", "Muon_DOCA",  Vertex_DOCAbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonDOCA_TRUE_RECO("h_MuonDOCA_TRUE_RECO", "Muon_DOCA",  Vertex_DOCAbin_vector , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonDOCA_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonDOCA_Material", Vertex_DOCAbin_vector ,"h_MuonDOCA_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonDOCA_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_MuonDOCA_Interaction", Vertex_DOCAbin_vector ,"h_MuonDOCA_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_MuonDOCA_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_MuonDOCA_Particle", Vertex_DOCAbin_vector ,"h_MuonDOCA_Particle; [mm];Events");
//h_MuonDOCA_Particle.ApplyColorPalette(Helium9_colorScheme);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Nonmuon_VertexTiming("h_Nonmuon_VertexTiming", "h_Nonmuon_VertexTiming",  VectexTiming_vector , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Nonmuon_VertexTiming_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Nonmuon_VertexTiming_Material", VectexTiming_vector ,"h_Nonmuon_VertexTiming_Material; [time];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_Nonmuon_VertexTiming_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_Nonmuon_VertexTiming_Interaction", VectexTiming_vector ,"h_Nonmuon_VertexTiming_Interaction; [time];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_Nonmuon_VertexTiming_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_Nonmuon_VertexTiming_Particle", VectexTiming_vector ,"h_Nonmuon_VertexTiming_Particle; [time];Events");
//h_Nonmuon_VertexTiming_Particle.ApplyColorPalette(Helium9_colorScheme);

//////////////////////////////////////
/////////////Minos/////////////////
//////////////////////////////////
PlotUtils::HistWrapper<HeliumCVUniverse> h_muon_MINOS_E("h_muon_MINOS_E", "Minos Muon_{E} [GeV] ", Ebin_vector , error_bands);
//Categorized<MnvH1D, int> h_muon_MINOS_E_material(    "h_muon_MINOS_E_material", "Minos Muon_{E} [GeV]", Materials, Ebin_vector  );
//Categorized<MnvH1D, int> h_muon_MINOS_E_interaction( "h_muon_MINOS_E_interaction", "Minos Muon_{E} [GeV]", Interaction, Ebin_vector  );

PlotUtils::HistWrapper<HeliumCVUniverse> h_muon_minosStart_X("h_muon_minosStart_X", "Minos Start X [mm] ", Minos_Start_X_vector , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_muon_minosStart_X_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_muon_minosStart_X_Material", Minos_Start_X_vector ,"h_muon_minosStart_X_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_muon_minosStart_X_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_muon_minosStart_X_Interaction", Minos_Start_X_vector ,"h_muon_minosStart_X_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_muon_minosStart_X_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_muon_minosStart_X_Particle", Minos_Start_X_vector ,"h_muon_minosStart_X_Particle; [mm];Events");

//h_muon_minosStart_X_Particle.ApplyColorPalette(Helium9_colorScheme);

PlotUtils::HistWrapper<HeliumCVUniverse> h_muon_minosStart_Y("h_muon_minosStart_Y", "Minos Start Y ", Minos_Start_Y_vector , error_bands);
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_muon_minosStart_Y_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_muon_minosStart_Y_Material", Minos_Start_Y_vector ,"h_muon_minosStart_Y_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_muon_minosStart_Y_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_muon_minosStart_Y_Interaction", Minos_Start_Y_vector ,"h_muon_minosStart_Y_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_muon_minosStart_Y_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_muon_minosStart_Y_Particle", Minos_Start_Y_vector ,"h_muon_minosStart_Y_Particle; [mm];Events");

//h_muon_minosStart_Y_Particle.ApplyColorPalette(Helium9_colorScheme);


PlotUtils::HistWrapper<HeliumCVUniverse> h_muon_minosStart_Z("h_muon_minosStart_Z", "Minos Start Z ", Minos_Start_Z_vector , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_muon_minosStart_Z_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_muon_minosStart_Z_Material", Minos_Start_Z_vector ,"h_muon_minosStart_Z_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_muon_minosStart_Z_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_muon_minosStart_Z_Interaction", Minos_Start_Z_vector ,"h_muon_minosStart_Z_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_muon_minosStart_Z_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_muon_minosStart_Z_Particle", Minos_Start_Z_vector ,"h_muon_minosStart_Z_Particle; [mm];Events");

//h_muon_minosStart_Z_Particle.ApplyColorPalette(Helium9_colorScheme);


PlotUtils::HistWrapper<HeliumCVUniverse> h_muon_minosEnd_X("h_muon_minosEnd_X", "Minos End X ", Minos_End_X_vector , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_muon_minosEnd_X_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_muon_minosEnd_X_Material", Minos_End_X_vector ,"h_muon_minosEnd_X_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_muon_minosEnd_X_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_muon_minosEnd_X_Interaction", Minos_End_X_vector ,"h_muon_minosEnd_X_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_muon_minosEnd_X_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_muon_minosEnd_X_Particle", Minos_End_X_vector ,"h_muon_minosEnd_X_Particle; [mm];Events");

//h_muon_minosEnd_X_Particle.ApplyColorPalette(Helium9_colorScheme);


PlotUtils::HistWrapper<HeliumCVUniverse> h_muon_minosEnd_Y("h_muon_minosEnd_Y", "Minos End Y ", Minos_End_Y_vector , error_bands);
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_muon_minosEnd_Y_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_muon_minosEnd_Y_Material", Minos_End_Y_vector ,"h_muon_minosEnd_Y_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_muon_minosEnd_Y_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_muon_minosEnd_Y_Interaction", Minos_End_Y_vector ,"h_muon_minosEnd_Y_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_muon_minosEnd_Y_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_muon_minosEnd_Y_Particle", Minos_End_Y_vector ,"h_muon_minosEnd_Y_Particle; [mm];Events");

//h_muon_minosEnd_Y_Particle.ApplyColorPalette(Helium9_colorScheme);

PlotUtils::HistWrapper<HeliumCVUniverse> h_muon_minosEnd_Z("h_muon_minosEnd_Z", "Minos End Z ", Minos_End_Z_vector , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_muon_minosEnd_Z_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_muon_minosEnd_Z_Material", Minos_End_Z_vector ,"h_muon_minosEnd_Z_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_muon_minosEnd_Z_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_muon_minosEnd_Z_Interaction", Minos_End_Z_vector ,"h_muon_minosEnd_Z_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_muon_minosEnd_Z_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_muon_minosEnd_Z_Particle", Minos_End_Z_vector ,"h_muon_minosEnd_Z_Particle; [mm];Events");

//h_muon_minosEnd_Z_Particle.ApplyColorPalette(Helium9_colorScheme);
/////////////////////////////////////////////////////


PlotUtils::HistWrapper<HeliumCVUniverse> h_muon_StartNode_X("h_muon_StartNode_X", "Muon Starting node X [mm] ",Muon_StartNode_X_vector , error_bands);
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_muon_StartNode_X_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_muon_StartNode_X_Material", Muon_StartNode_X_vector ,"h_muon_StartNode_X_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_muon_StartNode_X_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_muon_StartNode_X_Interaction", Muon_StartNode_X_vector ,"h_muon_StartNode_X_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_muon_StartNode_X_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_muon_StartNode_X_Particle", Muon_StartNode_X_vector ,"h_muon_StartNode_X_Particle; [mm];Events");

//h_muon_StartNode_X_Particle.ApplyColorPalette(Helium9_colorScheme);

PlotUtils::HistWrapper<HeliumCVUniverse> h_muon_StartNode_Y("h_muon_StartNode_Y", "Muon Starting node Y [mm] ", Muon_StartNode_X_vector , error_bands);
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_muon_StartNode_Y_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_muon_StartNode_Y_Material", Muon_StartNode_X_vector ,"h_muon_StartNode_Y_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_muon_StartNode_Y_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_muon_StartNode_Y_Interaction", Muon_StartNode_X_vector ,"h_muon_minosEnd_Y_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_muon_StartNode_Y_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_muon_StartNode_Y_Particle", Muon_StartNode_Y_vector ,"h_muon_StartNode_Y_Particle; [mm];Events");

//h_muon_StartNode_Y_Particle.ApplyColorPalette(Helium9_colorScheme);


PlotUtils::HistWrapper<HeliumCVUniverse> h_muon_StartNode_Z("h_muon_StartNode_Z", "Muon Starting node Z [mm] ", Muon_StartNode_Z_vector , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_muon_StartNode_Z_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_muon_StartNode_Z_Material", Muon_StartNode_Z_vector ,"h_muon_StartNode_Z_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_muon_StartNode_Z_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_muon_StartNode_Z_Interaction", Muon_StartNode_Z_vector ,"h_muon_StartNode_Z_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_muon_StartNode_Z_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_muon_StartNode_Z_Particle", Muon_StartNode_Z_vector ,"h_muon_StartNode_Z_Particle; [mm];Events");
//h_muon_StartNode_Z_Particle.ApplyColorPalette(Helium9_colorScheme);


PlotUtils::HistWrapper<HeliumCVUniverse> h_muon_LastNode_X("h_muon_LastNode_X", "Muon Last node X [mm] ", Muon_LastNode_X_vector , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_muon_LastNode_X_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_muon_LastNode_X_Material", Muon_LastNode_X_vector ,"h_muon_LastNode_X_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_muon_LastNode_X_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_muon_LastNode_X_Interaction", Muon_LastNode_X_vector , "h_muon_LastNode_X_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_muon_LastNode_X_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_muon_LastNode_X_Particle",Muon_LastNode_X_vector  ,"h_muon_LastNode_X_Particle; [mm];Events");

//h_muon_LastNode_X_Particle.ApplyColorPalette(Helium9_colorScheme);


PlotUtils::HistWrapper<HeliumCVUniverse> h_muon_LastNode_Y("h_muon_LastNode_Y", "Muon Last node Y [mm] ", Muon_LastNode_Y_vector , error_bands);
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_muon_LastNode_Y_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_muon_LastNode_Y_Material", Muon_LastNode_Y_vector ,"h_muon_LastNode_Y_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_muon_LastNode_Y_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_muon_LastNode_Y_Interaction", Muon_LastNode_Y_vector , "h_muon_LastNode_Y_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_muon_LastNode_Y_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_muon_LastNode_Y_Particle",Muon_LastNode_Y_vector  ,"h_muon_LastNode_Y_Particle; [mm];Events");

//h_muon_LastNode_Y_Particle.ApplyColorPalette(Helium9_colorScheme);

PlotUtils::HistWrapper<HeliumCVUniverse> h_muon_LastNode_Z("h_muon_LastNode_Z", "Muon Last node Z [mm] ", Muon_LastNode_Z_vector , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_muon_LastNode_Z_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_muon_LastNode_Z_Material", Muon_LastNode_Z_vector ,"h_muon_LastNode_Z_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_muon_LastNode_Z_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_muon_LastNode_Z_Interaction", Muon_LastNode_Z_vector , "h_muon_LastNode_Z_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_muon_LastNode_Z_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_muon_LastNode_Z_Particle",Muon_LastNode_Z_vector  ,"h_muon_LastNode_Z_Particle; [mm];Events");

//h_muon_LastNode_Z_Particle.ApplyColorPalette(Helium9_colorScheme);
// Track length
//
//
//
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_tracklength("h_secTrk_tracklength", "Recoil track length  [cm] ", Recoil_track_length_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_tracklength_TRUE_RECO("h_secTrk_tracklength_TRUE_RECO", "Recoil track length  [cm] ", Recoil_track_length_vector , error_bands);
//PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_tracklength_TRUE_TRUE_RECO("h_secTrk_tracklength_TRUE_TRUE_RECO", "Recoil track length  [cm] ", Recoil_track_length_vector , error_bands);


PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_tracklength_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_tracklength_Material", Recoil_track_length_vector ,"h_secTrk_tracklength_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_secTrk_tracklength_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_secTrk_tracklength_Interaction", Recoil_track_length_vector , "h_secTrk_tracklength_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_tracklength_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_tracklength_Particle",Recoil_track_length_vector  ,"h_secTrk_tracklength_Particle; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D,TrackType> h_secTrk_tracklength_Track =
PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType>(TrackType_Category, "h_secTrk_tracklength_Track",Recoil_track_length_vector  ,"h_secTrk_tracklength_Track; [mm];Events");




PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_tracklength_longtracker("h_secTrk_tracklength_longtracker", "Recoil track length  [cm] ", Recoil_track_length_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_tracklength_shorttracker("h_secTrk_tracklength_shorttracker", "Recoil track length  [cm] ", Recoil_track_length_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_tracklength_otherlongtracker("h_secTrk_tracklength_otherlongtracker", "Recoil track length  [cm] ", Recoil_track_length_vector , error_bands);


std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<std::endl;
std::cout<<"~~~~ initialize some 2D Varibles  ~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<std::endl;
///////////////////////////////////////
//
///////////////////////////////////////
MnvH2D *h_2d_PZ_PT_TRUE_RECO       =    new MnvH2D("h_2d_PZ_PT_TRUE_RECO", "h_2d_PZ_PT_TRUE_RECO" ,Pzbin_vector.size()-1, Pzbin_vector.data(),PTbin_vector.size()-1, PTbin_vector.data()  );

MnvH2D *h_2d_E_PZ_TRUE_RECO        =    new MnvH2D("h_2d_E_PZ_TRUE_RECO", "h_2d_E_PZ_TRUE_RECO", Ebin_vector.size()-1, Ebin_vector.data(),Pzbin_vector.size()-1, Pzbin_vector.data()  );

MnvH2D *h_2d_Theta_PZ_TRUE_RECO    =    new MnvH2D("h_2d_Theta_PZ_TRUE_RECO", "h_2d_Theta_PZ_TRUE_RECO", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),Pzbin_vector.size()-1, Pzbin_vector.data()  );

MnvH2D *h_2d_E_PT_TRUE_RECO        =    new MnvH2D("h_2d_E_PT_TRUE_RECO", "h_2d_E_PT_TRUE_RECO", Ebin_vector.size()-1, Ebin_vector.data(),PTbin_vector.size()-1, PTbin_vector.data()  );

//MnvH2D *h_2d_Theta_PZ_TRUE         =    new MnvH2D("h_2d_Theta_PZ_TRUE", "h_2d_Theta_PZ_TRUE", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),Pzbin_vector.size()-1, Pzbin_vector.data()  );
//MnvH2D *h_2d_Theta_PZ_TRUE_RECO    =    new MnvH2D("h_2d_Theta_PZ_TRUE_RECO", "h_2d_Theta_PZ_TRUE_RECO", .size()-1, MuonThetabin_vector.data(),Pzbin_vector.size()-1, Pzbin_vector.data()  );

MnvH2D *h_2d_Theta_PT_TRUE_RECO    =    new MnvH2D("h_2d_Theta_PT_TRUE_RECO", "h_2d_Theta_PT_TRUE_RECO", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),PTbin_vector.size()-1, PTbin_vector.data()  );

///////////////////////////////////////
//
///////////////////////////////////////
MnvH2D *h_2d_Theta_2ndTrkE_TRUE_RECO    =    new MnvH2D("h_2d_Theta_2ndTrkE_TRUE_RECO", "h_2d_Theta_2ndTrkE_TRUE_RECO", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );

MnvH2D *h_2d_muonE_2ndTrkE_TRUE_RECO    =    new MnvH2D("h_2d_muonE_2ndTrkE_TRUE_RECO", "h_2d_muonE_2ndTrkE_TRUE_RECO", Ebin_vector.size()-1, Ebin_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );

MnvH2D *h_2d_muonPT_2ndTrkE_TRUE_RECO    =    new MnvH2D("h_2d_muonPT_2ndTrkE_TRUE_RECO", "h_2d_muonPT_2ndTrkE_TRUE_RECO",  PTbin_vector.size()-1,  PTbin_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );

MnvH2D *h_2d_muonPZ_2ndTrkE_TRUE_RECO    =    new MnvH2D("h_2d_muonPZ_2ndTrkE_TRUE_RECO", "h_2d_muonPZ_2ndTrkE_TRUE_RECO",  Pzbin_vector.size()-1,  Pzbin_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );
////////
//Proton
/////////
MnvH2D *h_2d_Theta_2ndTrkE_Proton_TRUE_RECO    =    new MnvH2D("h_2d_Theta_2ndTrkE_Proton_TRUE_RECO", "h_2d_Theta_2ndTrkE_Proton_TRUE_RECO", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );

MnvH2D *h_2d_muonE_2ndTrkE_Proton_TRUE_RECO    =    new MnvH2D("h_2d_muonE_2ndTrkE_Proton_TRUE_RECO", "h_2d_muonE_2ndTrkE_Proton_TRUE_RECO", Ebin_vector.size()-1, Ebin_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );

MnvH2D *h_2d_muonPT_2ndTrkE_Proton_TRUE_RECO    =    new MnvH2D("h_2d_muonPT_2ndTrkE_Proton_TRUE_RECO", "h_2d_muonPT_2ndTrkE_Proton_TRUE_RECO",  PTbin_vector.size()-1,  PTbin_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );

MnvH2D *h_2d_muonPZ_2ndTrkE_Proton_TRUE_RECO    =    new MnvH2D("h_2d_muonPZ_2ndTrkE_Proton_TRUE_RECO", "h_2d_muonPZ_2ndTrkE_Proton_TRUE_RECO",  Pzbin_vector.size()-1,  Pzbin_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );
//////
//Pion
///////
MnvH2D *h_2d_Theta_2ndTrkE_Pion_TRUE_RECO    =    new MnvH2D("h_2d_Theta_2ndTrkE_Pion_TRUE_RECO", "h_2d_Theta_2ndTrkE_Pion_TRUE_RECO", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );

MnvH2D *h_2d_muonE_2ndTrkE_Pion_TRUE_RECO    =    new MnvH2D("h_2d_muonE_2ndTrkE_Pion_TRUE_RECO", "h_2d_muonE_2ndTrkE_Pion_TRUE_RECO", Ebin_vector.size()-1, Ebin_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );

MnvH2D *h_2d_muonPT_2ndTrkE_Pion_TRUE_RECO    =    new MnvH2D("h_2d_muonPT_2ndTrkE_Pion_TRUE_RECO", "h_2d_muonPT_2ndTrkE_Pion_TRUE_RECO",  PTbin_vector.size()-1,  PTbin_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );

MnvH2D *h_2d_muonPZ_2ndTrkE_Pion_TRUE_RECO    =    new MnvH2D("h_2d_muonPZ_2ndTrkE_Pion_TRUE_RECO", "h_2d_muonPZ_2ndTrkE_Pion_TRUE_RECO",  Pzbin_vector.size()-1,  Pzbin_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );

///////////////////////////////////////
//
///////////////////////////////////////
MnvH2D *h_2d_Theta_2ndTrKangle_TRUE_RECO    =    new MnvH2D("h_2d_Theta_2ndTrKangle_TRUE_RECO", "h_2d_Theta_2ndTrKangle_TRUE_RECO", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),secTrk_Theta_TRUEbin_vector.size()-1, secTrk_Theta_TRUEbin_vector.data()  );

MnvH2D *h_2d_muonE_2ndTrkangle_TRUE_RECO    =    new MnvH2D("h_2d_muonE_2ndTrkangle_TRUE_RECO", "h_2d_muonE_2ndTrkangle_TRUE_RECO", Ebin_vector.size()-1, Ebin_vector.data(),secTrk_Theta_TRUEbin_vector.size()-1, secTrk_Theta_TRUEbin_vector.data()  );

MnvH2D *h_2d_muonPT_2ndTrkangle_TRUE_RECO    =    new MnvH2D("h_2d_muonPT_2ndTrkangle_TRUE_RECO", "h_2d_muonPT_2ndTrkangle_TRUE_RECO",  PTbin_vector.size()-1,  PTbin_vector.data(),secTrk_Theta_TRUEbin_vector.size()-1, secTrk_Theta_TRUEbin_vector.data()  );

MnvH2D *h_2d_muonPZ_2ndTrkangle_TRUE_RECO    =    new MnvH2D("h_2d_muonPZ_2ndTrkangle_TRUE_RECO", "h_2d_muonPZ_2ndTrkangle_TRUE_RECO",  Pzbin_vector.size()-1,  Pzbin_vector.data(),secTrk_Theta_TRUEbin_vector.size()-1, secTrk_Theta_TRUEbin_vector.data()  );

///////////////////////////////////////
// low angle study
///////////////////////////////////////
/*
MnvH2D *h_2d_PZ_PT_LOWANGLE_TRUE_RECO       =    new MnvH2D("h_2d_PZ_PT_LOWANGLE_TRUE_RECO", "h_2d_PZ_PT_LOWANGLE_TRUE_RECO" ,Pzbin_vector.size()-1, Pzbin_vector.data(),PTbin_vector.size()-1, PTbin_vector.data()  );

MnvH2D *h_2d_E_PZ_LOWANGLE_TRUE_RECO        =    new MnvH2D("h_2d_E_PZ_LOWANGLE_TRUE_RECO", "h_2d_E_PZ_LOWANGLE_TRUE_RECO", Ebin_vector.size()-1, Ebin_vector.data(),Pzbin_vector.size()-1, Pzbin_vector.data()  );

MnvH2D *h_2d_Theta_PZ_LOWANGLE_TRUE_RECO    =    new MnvH2D("h_2d_Theta_PZ_LOWANGLE_TRUE_RECO", "h_2d_Theta_PZ_LOWANGLE_TRUE_RECO", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),Pzbin_vector.size()-1, Pzbin_vector.data()  );

MnvH2D *h_2d_E_PT_LOWANGLE_TRUE_RECO        =    new MnvH2D("h_2d_E_PT_LOWANGLE_TRUE_RECO", "h_2d_E_PT_LOWANGLE_TRUE_RECO", Ebin_vector.size()-1, Ebin_vector.data(),PTbin_vector.size()-1, PTbin_vector.data()  );

//MnvH2D *h_2d_Theta_PZ_TRUE         =    new MnvH2D("h_2d_Theta_PZ_TRUE", "h_2d_Theta_PZ_TRUE", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),Pzbin_vector.size()-1, Pzbin_vector.data()  );
//MnvH2D *h_2d_Theta_PZ_LOWANGLE_TRUE_RECO    =    new MnvH2D("h_2d_Theta_PZ_LOWANGLE_TRUE_RECO", "h_2d_Theta_PZ_LOWANGLE_TRUE_RECO", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),Pzbin_vector.size()-1, Pzbin_vector.data()  );

MnvH2D *h_2d_Theta_PT_LOWANGLE_TRUE_RECO    =    new MnvH2D("h_2d_Theta_PT_LOWANGLE_TRUE_RECO", "h_2d_Theta_PT_LOWANGLE_TRUE_RECO", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),PTbin_vector.size()-1, PTbin_vector.data()  );

///////////////////////////////////////
//
///////////////////////////////////////
MnvH2D *h_2d_Theta_2ndTrkE_LOWANGLE_TRUE_RECO    =    new MnvH2D("h_2d_Theta_2ndTrkE_LOWANGLE_TRUE_RECO", "h_2d_Theta_2ndTrkE_LOWANGLE_TRUE_RECO", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );

MnvH2D *h_2d_muonE_2ndTrkE_LOWANGLE_TRUE_RECO    =    new MnvH2D("h_2d_muonE_2ndTrkE_LOWANGLE_TRUE_RECO", "h_2d_muonE_2ndTrkE_LOWANGLE_TRUE_RECO", Ebin_vector.size()-1, Ebin_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );

MnvH2D *h_2d_muonPT_2ndTrkE_LOWANGLE_TRUE_RECO    =    new MnvH2D("h_2d_muonPT_2ndTrkE_LOWANGLE_TRUE_RECO", "h_2d_muonPT_2ndTrkE_LOWANGLE_TRUE_RECO",  PTbin_vector.size()-1,  PTbin_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );

MnvH2D *h_2d_muonPZ_2ndTrkE_LOWANGLE_TRUE_RECO    =    new MnvH2D("h_2d_muonPZ_2ndTrkE_LOWANGLE_TRUE_RECO", "h_2d_muonPZ_2ndTrkE_LOWANGLE_TRUE_RECO",  Pzbin_vector.size()-1,  Pzbin_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );

///////////////////////////////////////
//
///////////////////////////////////////
MnvH2D *h_2d_Theta_2ndTrKangle_LOWANGLE_TRUE_RECO    =    new MnvH2D("h_2d_Theta_2ndTrKangle_LOWANGLE_TRUE_RECO", "h_2d_Theta_2ndTrKangle_LOWANGLE_TRUE_RECO", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),secTrk_Theta_TRUEbin_vector.size()-1, secTrk_Theta_TRUEbin_vector.data()  );

MnvH2D *h_2d_muonE_2ndTrkangle_LOWANGLE_TRUE_RECO    =    new MnvH2D("h_2d_muonE_2ndTrkangle_LOWANGLE_TRUE_RECO", "h_2d_muonE_2ndTrkangle_LOWANGLE_TRUE_RECO", Ebin_vector.size()-1, Ebin_vector.data(),secTrk_Theta_TRUEbin_vector.size()-1, secTrk_Theta_TRUEbin_vector.data()  );

MnvH2D *h_2d_muonPT_2ndTrkangle_LOWANGLE_TRUE_RECO    =    new MnvH2D("h_2d_muonPT_2ndTrkangle_LOWANGLE_TRUE_RECO", "h_2d_muonPT_2ndTrkangle_LOWANGLE_TRUE_RECO",  PTbin_vector.size()-1,  PTbin_vector.data(),secTrk_Theta_TRUEbin_vector.size()-1, secTrk_Theta_TRUEbin_vector.data()  );

MnvH2D *h_2d_muonPZ_2ndTrkangle_LOWANGLE_TRUE_RECO    =    new MnvH2D("h_2d_muonPZ_2ndTrkangle_LOWANGLE_TRUE_RECO", "h_2d_muonPZ_2ndTrkangle_LOWANGLE_TRUE_RECO",  Pzbin_vector.size()-1,  Pzbin_vector.data(),secTrk_Theta_TRUEbin_vector.size()-1, secTrk_Theta_TRUEbin_vector.data()  );

////////////////////////////////////
//MnvH2D *h_2d_Theta_PT_TRUE         =    new MnvH2D("h_2d_Theta_PT_TRUE", "h_2d_Theta_PT_TRUE", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),PTbin_vector.size()-1, PTbin_vector.data()  );
//MnvH2D *h_2d_Theta_PT_LOWANGLE_TRUE_RECO    =    new MnvH2D("h_2d_Theta_PT_LOWANGLE_TRUE_RECO", "h_2d_Theta_PT_LOWANGLE_TRUE_RECO", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),PTbin_vector.size()-1, PTbin_vector.data()  );
///////////////////////////////////////
//
///////////////////////////////////////

MnvH2D *h_2d_2ndtrkangle_2ndTrkE_LOWANGLE_TRUE_RECO    =    new MnvH2D("h_2d_2ndtrkangle_2ndTrkE_LOWANGLE_TRUE_RECO", "h_2d_2ndtrkangle_2ndTrkE_LOWANGLE_TRUE_RECO", secTrk_Theta_TRUEbin_vector.size()-1, secTrk_Theta_TRUEbin_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );

MnvH2D *h_2d_2ndtrkangle_2ndTrkE_Proton_LOWANGLE_TRUE_RECO    =    new MnvH2D("h_2d_2ndtrkangle_2ndTrkE_Proton_LOWANGLE_TRUE_RECO", "h_2d_2ndtrkangle_2ndTrkE_Proton_LOWANGLE_TRUE_RECO", secTrk_Theta_TRUEbin_vector.size()-1, secTrk_Theta_TRUEbin_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );

MnvH2D *h_2d_2ndtrkangle_2ndTrkE_Pion_LOWANGLE_TRUE_RECO    =    new MnvH2D("h_2d_2ndtrkangle_2ndTrkE_Pion_LOWANGLE_TRUE_RECO", "h_2d_2ndtrkangle_2ndTrkE_Pion_LOWANGLE_TRUE_RECO", secTrk_Theta_TRUEbin_vector.size()-1, secTrk_Theta_TRUEbin_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );

MnvH2D *h_2d_2ndtrkangle_2ndTrkE_dimuon_LOWANGLE_TRUE_RECO    =    new MnvH2D("h_2d_2ndtrkangle_2ndTrkE_dimuon_LOWANGLE_TRUE_RECO", "h_2d_2ndtrkangle_2ndTrkE_dimuon_LOWANGLE_TRUE_RECO", secTrk_Theta_TRUEbin_vector.size()-1, secTrk_Theta_TRUEbin_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );
*/
/////////////////////////////////////
//
/////////////////////////////////////
MnvH2D *h_2d_2ndtrkPathlength_2ndTrkE_TRUE_RECO    =    new MnvH2D("h_2d_2ndtrkPathlength_2ndTrkE_TRUE_RECO", "h_2d_2ndtrkPathlength_2ndTrkE_TRUE_RECO", secTrk_Pathway_vector.size()-1, secTrk_Pathway_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );

MnvH2D *h_2d_2ndtrkPathlength_2ndTrkE_Proton_TRUE_RECO    =    new MnvH2D("h_2d_2ndtrkPathlength_2ndTrkE_Proton_TRUE_RECO", "h_2d_2ndtrkPathlength_2ndTrkE_Proton_TRUE_RECO", secTrk_Pathway_vector.size()-1, secTrk_Pathway_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );

MnvH2D *h_2d_2ndtrkPathlength_2ndTrkE_Pion_TRUE_RECO    =    new MnvH2D("h_2d_2ndtrkPathlength_2ndTrkE_Pion_TRUE_RECO", "h_2d_2ndtrkPathlength_2ndTrkE_Pion_TRUE_RECO", secTrk_Pathway_vector.size()-1, secTrk_Pathway_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );

//MnvH2D *h_2d_2ndtrkPathlength_2ndTrkE_dimuon_TRUE_RECO    =    new MnvH2D("h_2d_2ndtrkPathlength_2ndTrkE_dimuon_TRUE_RECO", "h_2d_2ndtrkPathlength_2ndTrkE_dimuon_TRUE_RECO", secTrk_Pathway_vector.size()-1, secTrk_Pathway_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );
//////////////////
////
/////////////////
MnvH2D *h_2d_2ndtrkPathlength_2ndtrkangle_TRUE_RECO    =    new MnvH2D("h_2d_2ndtrkPathlength_2ndtrkangle_TRUE_RECO", "h_2d_2ndtrkPathlength_2ndtrkangle_TRUE_RECO", secTrk_Pathway_vector.size()-1, secTrk_Pathway_vector.data(),secTrk_Theta_TRUEbin_vector.size()-1, secTrk_Theta_TRUEbin_vector.data()  );

MnvH2D *h_2d_2ndtrkPathlength_2ndtrkangle_Proton_TRUE_RECO    =    new MnvH2D("h_2d_2ndtrkPathlength_2ndtrkangle_Proton_TRUE_RECO", "h_2d_2ndtrkPathlength_2ndtrkangle_Proton_TRUE_RECO", secTrk_Pathway_vector.size()-1, secTrk_Pathway_vector.data(),secTrk_Theta_TRUEbin_vector.size()-1, secTrk_Theta_TRUEbin_vector.data()  );

MnvH2D *h_2d_2ndtrkPathlength_2ndtrkangle_Pion_TRUE_RECO    =    new MnvH2D("h_2d_2ndtrkPathlength_2ndtrkangle_Pion_TRUE_RECO", "h_2d_2ndtrkPathlength_2ndtrkangle_Pion_TRUE_RECO", secTrk_Pathway_vector.size()-1, secTrk_Pathway_vector.data(),secTrk_Theta_TRUEbin_vector.size()-1, secTrk_Theta_TRUEbin_vector.data()  );

//MnvH2D *h_2d_2ndtrkPathlength_2ndtrkangle_dimuon_TRUE_RECO    =    new MnvH2D("h_2d_2ndtrkPathlength_2ndtrkangle_dimuon_TRUE_RECO", "h_2d_2ndtrkPathlength_2ndtrkangle_dimuon_TRUE_RECO", secTrk_Pathway_vector.size()-1, secTrk_Pathway_vector.data(),secTrk_Theta_TRUEbin_vector.size()-1, secTrk_Theta_TRUEbin_vector.data()  );

MnvH2D *h_2d_2ndtrkPathlength_vertex_R    =    new MnvH2D("h_2d_2ndtrkPathlength_vertex_R", "h_2d_2ndtrkPathlength_vertex_R", secTrk_Pathway_vector.size()-1, secTrk_Pathway_vector.data(),Vertex_Rbin_vector.size()-1, Vertex_Rbin_vector.data());
MnvH2D *h_2d_2ndtrkPathlength_vertex_Z    =    new MnvH2D("h_2d_2ndtrkPathlength_vertex_Z", "h_2d_2ndtrkPathlength_vertex_Z", secTrk_Pathway_vector.size()-1, secTrk_Pathway_vector.data(),Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());

MnvH2D *h_2d_2ndtrkLength_vertex_R    =    new MnvH2D("h_2d_2ndtrkLength_vertex_R", "h_2d_2ndtrkLength_vertex_R", Recoil_track_length_vector.size()-1, Recoil_track_length_vector.data(),Vertex_Rbin_vector.size()-1, Vertex_Rbin_vector.data());
MnvH2D *h_2d_2ndtrkLength_vertex_Z    =    new MnvH2D("h_2d_2ndtrkLength_vertex_Z", "h_2d_2ndtrkLength_vertex_Z", Recoil_track_length_vector.size()-1, Recoil_track_length_vector.data(),Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());


MnvH2D *h2_FirstZnode_2ndTrklength    =    new MnvH2D("h2_FirstZnode_2ndTrklength", "h2_FirstZnode_2ndTrklength",  secTrk_StartNode_Z_vector.size()-1, secTrk_StartNode_Z_vector.data(), Recoil_track_length_vector.size()-1,  Recoil_track_length_vector.data()  );
MnvH2D *h2_LastZnode_2ndTrklength    =    new MnvH2D("h2_LastZnode_2ndTrklength", "h2_LastZnode_2ndTrklength",   secTrk_LastNodeZ_vector.size()-1, secTrk_LastNodeZ_vector.data(),Recoil_track_length_vector.size()-1,  Recoil_track_length_vector.data()  );



std::vector<double> bigAngle_bins{0.0, 15.0, 30.0, 45.0, 60.0};
MnvH2D *h_2d_2ndtrkLength_Angle    =    new MnvH2D("h_2d_2ndtrkLength_Angle", "h_2d_2ndtrkLength_Angle", Recoil_track_length_vector.size()-1, Recoil_track_length_vector.data(), bigAngle_bins.size()-1, bigAngle_bins.data());

std::vector<double> bigAngle_bins_finner{0.0, 5.0, 10.0, 15.0, 20.0, 25.0, 30.0, 45.0, 60.0};
MnvH2D *h_2d_2ndtrkLength_finerAngle    =    new MnvH2D("h_2d_2ndtrkLength_finerAngle", "h_2d_2ndtrkLength_finerAngle", Recoil_track_length_vector.size()-1, Recoil_track_length_vector.data(), bigAngle_bins_finner.size()-1, bigAngle_bins_finner.data());



/////////////////////////////////////
//
/////////////////////////////////////
MnvH2D *h_2d_2ndtrkangle_2ndTrkE_TRUE_RECO    =    new MnvH2D("h_2d_2ndtrkangle_2ndTrkE_TRUE_RECO", "h_2d_2ndtrkangle_2ndTrkE_TRUE_RECO", secTrk_Theta_TRUEbin_vector.size()-1, secTrk_Theta_TRUEbin_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );

MnvH2D *h_2d_2ndtrkangle_2ndTrkE_Proton_TRUE_RECO    =    new MnvH2D("h_2d_2ndtrkangle_2ndTrkE_Proton_TRUE_RECO", "h_2d_2ndtrkangle_2ndTrkE_Proton_TRUE_RECO", secTrk_Theta_TRUEbin_vector.size()-1, secTrk_Theta_TRUEbin_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );

MnvH2D *h_2d_2ndtrkangle_2ndTrkE_Pion_TRUE_RECO    =    new MnvH2D("h_2d_2ndtrkangle_2ndTrkE_Pion_TRUE_RECO", "h_2d_2ndtrkangle_2ndTrkE_Pion_TRUE_RECO", secTrk_Theta_TRUEbin_vector.size()-1, secTrk_Theta_TRUEbin_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );

////////////////////////////////////////
////Migration Studies
///////////////////////////////////////
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<std::endl;
std::cout<<"~~~~ initialize Some Migration  ~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<std::endl;

MnvH2D *h_Mig_MuonE      =   new MnvH2D("h_Mig_MuonE",     "h_Mig_MuonE",     Ebin_vector.size()-1,         Ebin_vector.data(),         Ebin_vector.size()-1,         Ebin_vector.data());
MnvH2D *h_Mig_MuonPZ     =   new MnvH2D("h_Mig_MuonPZ",    "h_Mig_MuonPZ",    Pzbin_vector.size()-1,        Pzbin_vector.data(),        Pzbin_vector.size()-1,        Pzbin_vector.data());
MnvH2D *h_Mig_MuonPT     =   new MnvH2D("h_Mig_MuonPT",    "h_Mig_MuonPT",    PTbin_vector.size()-1,        PTbin_vector.data(),        PTbin_vector.size()-1,        PTbin_vector.data());
MnvH2D *h_Mig_MuonTheta  =   new MnvH2D("h_Mig_MuonTheta", "h_Mig_MuonTheta", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(), MuonThetabin_vector.size()-1, MuonThetabin_vector.data());
MnvH2D *h_Mig_Vertex_X      =   new MnvH2D("h_Mig_Vertex_X",     "h_Mig_Vertex_X",  Vertex_Xbin_vector.size()-1, Vertex_Xbin_vector.data(), Vertex_Xbin_vector.size()-1, Vertex_Xbin_vector.data());
MnvH2D *h_Mig_Vertex_Y      =   new MnvH2D("h_Mig_Vertex_Y",     "h_Mig_Vertex_Y",  Vertex_Ybin_vector.size()-1, Vertex_Ybin_vector.data(), Vertex_Ybin_vector.size()-1, Vertex_Ybin_vector.data());
MnvH2D *h_Mig_Vertex_R      =   new MnvH2D("h_Mig_Vertex_R",     "h_Mig_Vertex_R",  Vertex_Rbin_vector.size()-1, Vertex_Rbin_vector.data(), Vertex_Rbin_vector.size()-1, Vertex_Rbin_vector.data());
MnvH2D *h_Mig_Vertex_Z      =   new MnvH2D("h_Mig_Vertex_Z",     "h_Mig_Vertex_Z",  Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data(), Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());




auto fraction = MakeBinVector(20, 0, 1);
MnvH2D *h_2d_Track_Fraction_Energy    =    new MnvH2D("h_2d_Track_Fraction_Energy", "h_2d_Track_Fraction_Energy", TrackSize_vector.size()-1,TrackSize_vector.data() ,fraction.size()-1, fraction.data()  );
MnvH2D *h_2d_Track_Fraction_Energy_Cuts    =    new MnvH2D("h_2d_Track_Fraction_Energy_Cuts", "h_2d_Track_Fraction_Energy_Cuts", TrackSize_vector.size()-1,TrackSize_vector.data() ,fraction.size()-1, fraction.data()  );
MnvH2D *h_2d_Track_Fraction_Energy_Second    =    new MnvH2D("h_2d_Track_Fraction_Energy_Second", "h_2d_Track_Fraction_Energy_Second", TrackSize_vector.size()-1,TrackSize_vector.data() ,fraction.size()-1, fraction.data()  );

////////////////
//Vertex Hist///
////////////////
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<std::endl;
std::cout<<"~~~~ initialize Vertex Varibles  ~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<std::endl;
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X("h_CryoVertex_X", "h_CryoVertex_X",  Vertex_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_TRUE_RECO("h_CryoVertex_X_TRUE_RECO", "h_CryoVertex_X",  Vertex_Xbin_vector , error_bands);


PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_X_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_X_Material", Vertex_Xbin_vector ,"h_CryoVertex_X_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_CryoVertex_X_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_CryoVertex_X_Interaction", Vertex_Xbin_vector ,"h_CryoVertex_X_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_CryoVertex_X_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_CryoVertex_X_Particle", Vertex_Xbin_vector ,"h_CryoVertex_X_Particle; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType> h_CryoVertex_X_Track =
PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType>(TrackType_Category, "h_CryoVertex_X_Track", Vertex_Xbin_vector ,"h_CryoVertex_X_Track; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack> h_CryoVertex_X_boolNTrack =
PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack>(boolNTrack_Category, "h_CryoVertex_X_boolNTrack", Vertex_Xbin_vector ,"h_CryoVertex_X_boolNTrack; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions> h_CryoVertex_X_VertexOptions =
PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions>(VertexOptions_Category, "h_CryoVertex_X_VertexOptions", Vertex_Xbin_vector ,"h_CryoVertex_X_VertexOptions; [mm];Events");


//h_CryoVertex_X_Particle.ApplyColorPalette(Helium9_colorScheme);


PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y("h_CryoVertex_Y", "Vertex_Y",  Vertex_Ybin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_TRUE_RECO("h_CryoVertex_Y_TRUE_RECO", "Vertex_Y",  Vertex_Ybin_vector , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Y_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Y_Material", Vertex_Ybin_vector ,"h_CryoVertex_Y_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_CryoVertex_Y_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_CryoVertex_Y_Interaction", Vertex_Ybin_vector ,"h_CryoVertex_Y_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_CryoVertex_Y_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_CryoVertex_Y_Particle", Vertex_Ybin_vector ,"h_CryoVertex_Y_Particle; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType> h_CryoVertex_Y_Track =
PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType>(TrackType_Category, "h_CryoVertex_Y_Track", Vertex_Ybin_vector ,"h_CryoVertex_Y_Track; [mm];Events");

//PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType> h_CryoVertex_Y_Track =
//PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType>(TrackType_Category, "h_CryoVertex_Y_Track", Vertex_Ybin_vector ,"h_CryoVertex_Y_Track; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack> h_CryoVertex_Y_boolNTrack =
PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack>(boolNTrack_Category, "h_CryoVertex_Y_boolNTrack", Vertex_Ybin_vector ,"h_CryoVertex_Y_boolNTrack; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions> h_CryoVertex_Y_VertexOptions =
PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions>(VertexOptions_Category, "h_CryoVertex_Y_VertexOptions", Vertex_Ybin_vector ,"h_CryoVertex_Y_VertexOptions; [mm];Events");



//h_CryoVertex_Y_Particle.ApplyColorPalette(Helium9_colorScheme);


PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z("h_CryoVertex_Z", "Vertex_Z",  Vertex_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_TRUE_RECO("h_CryoVertex_Z_TRUE_RECO", "Vertex_Z",  Vertex_Zbin_vector , error_bands);


PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Z_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Z_Material", Vertex_Zbin_vector ,"h_CryoVertex_Z_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_CryoVertex_Z_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_CryoVertex_Z_Interaction", Vertex_Zbin_vector ,"h_CryoVertex_Z_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_CryoVertex_Z_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_CryoVertex_Z_Particle", Vertex_Zbin_vector ,"h_CryoVertex_Z_Particle; [mm];Events");


PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType> h_CryoVertex_Z_Track =
PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType>(TrackType_Category, "h_CryoVertex_Z_Track", Vertex_Zbin_vector ,"h_CryoVertex_Z_Track; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack> h_CryoVertex_Z_boolNTrack =
PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack>(boolNTrack_Category, "h_CryoVertex_Z_boolNTrack", Vertex_Zbin_vector ,"h_CryoVertex_Z_boolNTrack; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions> h_CryoVertex_Z_VertexOptions =
PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions>(VertexOptions_Category, "h_CryoVertex_Z_VertexOptions", Vertex_Zbin_vector ,"h_CryoVertex_Z_VertexOptions; [mm];Events");


PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R("h_CryoVertex_R", "h_CryoVertex_R",  Vertex_Rbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_TRUE_RECO("h_CryoVertex_R_TRUE_RECO", "h_CryoVertex_R",  Vertex_Rbin_vector , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_R_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_R_Material", Vertex_Rbin_vector ,"h_CryoVertex_R_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_CryoVertex_R_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_CryoVertex_R_Interaction", Vertex_Rbin_vector ,"h_CryoVertex_R_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_CryoVertex_R_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_CryoVertex_R_Particle", Vertex_Rbin_vector ,"h_CryoVertex_R_Particle; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType> h_CryoVertex_R_Track =
PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType>(TrackType_Category, "h_CryoVertex_R_Track", Vertex_Rbin_vector ,"h_CryoVertex_R_Track; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack> h_CryoVertex_R_boolNTrack =
PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack>(boolNTrack_Category, "h_CryoVertex_R_boolNTrack", Vertex_Rbin_vector ,"h_CryoVertex_R_boolNTrack; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions> h_CryoVertex_R_VertexOptions =
PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions>(VertexOptions_Category, "h_CryoVertex_R_VertexOptions", Vertex_Rbin_vector ,"h_CryoVertex_R_VertexOptions; [mm];Events");


PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertexChiSqFit("h_CryoVertexChiSqFit", "h_CryoVertexChiSqFit",  Vertex_ChiSqFit_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertexChiSqFit_TRUE("h_CryoVertexChiSqFit_TRUE", "h_CryoVertexChiSqFit_TRUE",  Vertex_ChiSqFit_vector , error_bands);

MnvH1D *h_Efficiency_h_CryoVertexChiSqFit[3]; // 0 helium, 1 other, 2 total
Array1D(h_Efficiency_h_CryoVertexChiSqFit, 3, "h_Efficiency_h_CryoVertexChiSqFit", "h_Efficiency_h_CryoVertexChiSqFit", Vertex_ChiSqFit_vector);

MnvH1D *h_Efficiency_h_CryoVertexChiSqFit_short[3]; // 0 helium, 1 other, 2 total
Array1D(h_Efficiency_h_CryoVertexChiSqFit_short, 3, "h_Efficiency_h_CryoVertexChiSqFit_short", "h_Efficiency_h_CryoVertexChiSqFit_short", Vertex_ChiSqFit_vector);

MnvH1D *h_Efficiency_h_CryoVertexChiSqFit_long[3]; // 0 helium, 1 other, 2 total
Array1D(h_Efficiency_h_CryoVertexChiSqFit_long, 3, "h_Efficiency_h_CryoVertexChiSqFit_long", "h_Efficiency_h_CryoVertexChiSqFit_long", Vertex_ChiSqFit_vector);

MnvH1D *h_Efficiency_h_CryoVertexChiSqFit_otherlong[3]; // 0 helium, 1 other, 2 total
Array1D(h_Efficiency_h_CryoVertexChiSqFit_otherlong, 3, "h_Efficiency_h_CryoVertexChiSqFit_otherlong", "h_Efficiency_h_CryoVertexChiSqFit_otherlong", Vertex_ChiSqFit_vector);



PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertexChiSqFit_TRUE_RECO("h_CryoVertexChiSqFit_TRUE_RECO", "h_CryoVertexChiSqFit_TRUE_RECO",  Vertex_ChiSqFit_vector , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertexChiSqFit_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertexChiSqFit_Material", Vertex_ChiSqFit_vector ,"h_CryoVertexChiSqFit_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_CryoVertexChiSqFit_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_CryoVertexChiSqFit_Interaction", Vertex_ChiSqFit_vector ,"h_CryoVertexChiSqFit_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_CryoVertexChiSqFit_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_CryoVertexChiSqFit_Particle", Vertex_ChiSqFit_vector ,"h_CryoVertexChiSqFit_Particle; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType> h_CryoVertexChiSqFit_Track =
PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType>(TrackType_Category, "h_CryoVertexChiSqFit_Track", Vertex_ChiSqFit_vector ,"h_CryoVertexChiSqFit_Track; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType> h_CryoVertexChiSqFitgreater10_Track =
PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType>(TrackType_Category, "h_CryoVertexChiSqFitgreater10_Track", Vertex_ChiSqFit_vector ,"h_CryoVertexChiSqFitgreater10_Track; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack> h_CryoVertexChiSqFit_boolNTrack =
PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack>(boolNTrack_Category, "h_CryoVertexChiSqFit_boolNTrack", Vertex_ChiSqFit_vector ,"h_CryoVertexChiSqFit_boolNTrack; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions> h_CryoVertexChiSqFit_VertexOptions =
PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions>(VertexOptions_Category, "h_CryoVertexChiSqFit_VertexOptions", Vertex_ChiSqFit_vector ,"h_CryoVertexChiSqFit_VertexOptions; [mm];Events");



/////////////
//2nd Trk Plots
/////////////
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<std::endl;
std::cout<<"~~~~ initialize nonMuon Varibles  ~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<std::endl;

PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Openangle("h_secTrk_Openangle", "h_secTrk openangle NEW Method",  secTrk_Thetamidbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Openangle_TRUE_RECO("h_secTrk_Openangle_TRUE_RECO", "h_secTrk_Openangle ",  secTrk_Theta_TRUEbin_vector , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_Openangle_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_Openangle_Material", secTrk_Thetamidbin_vector ,"h_secTrk_Openangle_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_secTrk_Openangle_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_secTrk_Openangle_Interaction", secTrk_Thetamidbin_vector ,"h_secTrk_Openangle_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_Openangle_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_Openangle_Particle", secTrk_Thetamidbin_vector ,"h_secTrk_Openangle_Particle; [mm];Events");
//h_secTrk_Openangle_Particle.ApplyColorPalette(Helium9_colorScheme);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_Openangle_TRUE_RECO_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_Openangle_TRUE_RECO_Material", secTrk_Theta_TRUEbin_vector ,"h_secTrk_Openangle_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_secTrk_Openangle_TRUE_RECO_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_secTrk_Openangle_TRUE_RECO_Interaction", secTrk_Theta_TRUEbin_vector ,"h_secTrk_Openangle_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_Openangle_TRUE_RECO_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_Openangle_TRUE_RECO_Particle", secTrk_Theta_TRUEbin_vector ,"h_secTrk_Openangle_Particle; [mm];Events");
//h_secTrk_Openangle_TRUE_RECO_Particle.ApplyColorPalette(Helium9_colorScheme);

PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Pathlength("h_secTrk_Pathlength", "h_secTrk Pathlength ",  secTrk_Pathway_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Pathlength_TRUE_RECO("h_secTrk_Pathlength_TRUE_RECO", "h_secTrk Pathlength ",  secTrk_Pathway_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Pathlength_PROTON_TRUE_RECO("h_secTrk_Pathlength_PROTON_TRUE_RECO", "h_secTrk Pathlength Proton",  secTrk_Pathway_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Pathlength_PION_TRUE_RECO("h_secTrk_Pathlength_PION_TRUE_RECO", "h_secTrk Pathlength pion ",  secTrk_Pathway_vector , error_bands);


PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_Pathlength_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_Pathlength_Material", secTrk_Pathway_vector ,"h_secTrk_Pathlength_Material; [cm^2/g];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_secTrk_Pathlength_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_secTrk_Pathlength_Interaction", secTrk_Pathway_vector ,"h_secTrk_Pathlength_Interaction; [cm^2/g];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_Pathlength_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_Pathlength_Particle", secTrk_Pathway_vector ,"h_secTrk_Pathlength_Particle; [cm^2/g];Events");
//h_secTrk_Pathlength_Particle.ApplyColorPalette(Helium9_colorScheme);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_Pathlength_TRUE_RECO_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_Pathlength_TRUE_RECO_Material", secTrk_Pathway_vector ,"h_secTrk_Pathlength_TRUE_RECO_Material; [cm^2/g];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_secTrk_Pathlength_TRUE_RECO_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_secTrk_Pathlength_TRUE_RECO_Interaction", secTrk_Pathway_vector ,"h_secTrk_Pathlength_TRUE_RECO_Interaction; [cm^2/g];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_Pathlength_TRUE_RECO_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_Pathlength_TRUE_RECO_Particle", secTrk_Pathway_vector ,"h_secTrk_Pathlength_TRUE_RECO_Particle; [cm^2/g];Events");
//h_secTrk_Pathlength_TRUE_RECO_Particle.ApplyColorPalette(Helium9_colorScheme);


PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_MidTheta("h_secTrk_MidTheta", "h_secTrk_MidTheta NEW Method",  Vertex_secondTrkThetamidbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Theta_TRUE_RECO("h_secTrk_Theta_TRUE_RECO", "h_secTrk_MidTheta NEW Method",  secTrk_Theta_TRUEbin_vector , error_bands);


//PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_ThetaLeading_TRUE_RECO("h_secTrk_ThetaLeading_TRUE_RECO", "h_secTrk_ThetaLeading_TRUE_RECO",  secTrk_Theta_TRUEbin_vector , error_bands);


PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_MidTheta_leading_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_leadingvsnonleading_categories, "h_secTrk_MidTheta_leading_Particle", Vertex_secondTrkThetamidbin_vector ,"h_secTrk_MidTheta_leading_Particle; [Deg];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_MidTheta_Nonleading_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_leadingvsnonleading_categories, "h_secTrk_MidTheta_Nonleading_Particle", Vertex_secondTrkThetamidbin_vector ,"h_secTrk_MidTheta_Nonleading_Particle; [Deg];Events");


PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_MidTheta_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_MidTheta_Material", Vertex_secondTrkThetamidbin_vector ,"h_secTrk_MidTheta_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_secTrk_MidTheta_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_secTrk_MidTheta_Interaction", Vertex_secondTrkThetamidbin_vector ,"h_secTrk_MidTheta_Interaction; [[GeV;Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_MidTheta_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_MidTheta_Particle", Vertex_secondTrkThetamidbin_vector ,"h_secTrk_MidTheta_Particle; [GeV];Events");
//h_secTrk_MidTheta_Particle.ApplyColorPalette(Helium9_colorScheme);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_Theta_TRUE_RECO_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_Theta_TRUE_RECO_Material", secTrk_Theta_TRUEbin_vector ,"h_secTrk_Theta_TRUE_RECO_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_secTrk_Theta_TRUE_RECO_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_secTrk_Theta_TRUE_RECO_Interaction", secTrk_Theta_TRUEbin_vector ,"h_secTrk_Theta_TRUE_RECO_Interaction; [[GeV;Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_Theta_TRUE_RECO_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_Theta_TRUE_RECO_Particle", secTrk_Theta_TRUEbin_vector ,"h_secTrk_Theta_TRUE_RECO_Particle; [GeV];Events");
//h_secTrk_Theta_TRUE_RECO_Particle.ApplyColorPalette(Helium9_colorScheme);
/*
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_Theta_TRUE_RECO_LOWANGLE_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_Theta_TRUE_RECO_LOWANGLE_Material", secTrk_Theta_TRUEbin_vector ,"h_secTrk_Theta_TRUE_RECO_LOWANGLE_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_secTrk_Theta_TRUE_RECO_LOWANGLE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_secTrk_Theta_TRUE_RECO_LOWANGLE_Interaction", secTrk_Theta_TRUEbin_vector ,"h_secTrk_Theta_TRUE_RECO_LOWANGLE_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_Theta_TRUE_RECO_LOWANGLE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_Theta_TRUE_RECO_LOWANGLE_Particle", secTrk_Theta_TRUEbin_vector ,"h_secTrk_Theta_TRUE_RECO_LOWANGLE_Particle; [GeV];Events");
//h_secTrk_Theta_TRUE_RECO_LOWANGLE_Particle.ApplyColorPalette(Helium9_colorScheme);
*/



PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Energy("h_secTrk_Energy", "h_secTrk_Energy NEW Method",  Vertex_secondTrkEbin_vector, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Energy_TRUE_RECO("h_secTrk_Energy_TRUE_RECO", "h_secTrk_Energy NEW Method",  Vertex_secondTrkEbin_vector, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_EnergyFINEBinning_TRUE_RECO("h_secTrk_EnergyFINEBinning_TRUE_RECO", "h_secTrk_Energy NEW Method",  Vertex_secondTrkEbin_Proton_vector, error_bands);


PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_Energy_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_Energy_Material", Vertex_secondTrkEbin_vector ,"h_secTrk_Energy_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_secTrk_Energy_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_secTrk_Energy_Interaction", Vertex_secondTrkEbin_vector ,"h_secTrk_Energy_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_Energy_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_Energy_Particle", Vertex_secondTrkEbin_vector ,"h_secTrk_Energy_Particle; [GeV];Events");
//h_secTrk_Energy_Particle.ApplyColorPalette(Helium9_colorScheme);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_nonparentEnergy_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_nonparentEnergy_Particle", Vertex_secondTrkEbin_vector ,"h_secTrk_nonparentEnergy_Particle; [GeV];Events");




PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_Energy_TRUE_RECO_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_Energy_TRUE_RECO_Material", Vertex_secondTrkEbin_Proton_vector ,"h_secTrk_Energy_TRUE_RECO_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_secTrk_Energy_TRUE_RECO_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_secTrk_Energy_TRUE_RECO_Interaction", Vertex_secondTrkEbin_Proton_vector ,"h_secTrk_Energy_TRUE_RECO_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_Energy_TRUE_RECO_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_Energy_TRUE_RECO_Particle", Vertex_secondTrkEbin_Proton_vector ,"h_secTrk_Energy_TRUE_RECO_Particle; [GeV];Events");
//h_secTrk_Energy_TRUE_RECO_Particle.ApplyColorPalette(Helium9_colorScheme);

PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_DOCA("h_secTrk_DOCA", "h_secTrk DOCA NEW Method",  secTrk_DOCA_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_DOCA_TRUE_RECO("h_secTrk_DOCA_TRUE_RECO", "h_secTrk_DOCA_TRUE_RECO",  Vertex_DOCAbin_vector , error_bands);


PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_DOCA_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_DOCA_Material", secTrk_DOCA_vector ,"h_secTrk_DOCA_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_secTrk_DOCA_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_secTrk_DOCA_Interaction", secTrk_DOCA_vector ,"h_secTrk_DOCA_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_DOCA_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_DOCA_Particle", secTrk_DOCA_vector ,"h_secTrk_DOCA_Particle; [mm];Events");
//h_secTrk_DOCA_Particle.ApplyColorPalette(Helium9_colorScheme);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_DOCA_TRUE_RECO_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_DOCA_TRUE_RECO_Material", secTrk_DOCA_vector ,"h_secTrk_DOCA_TRUE_RECO_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_secTrk_DOCA_TRUE_RECO_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_secTrk_DOCA_TRUE_RECO_Interaction", secTrk_DOCA_vector ,"h_secTrk_DOCA_TRUE_RECO_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_DOCA_TRUE_RECO_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_DOCA_TRUE_RECO_Particle", secTrk_DOCA_vector ,"h_secTrk_DOCA_TRUE_RECO_Particle; [mm];Events");
//h_secTrk_DOCA_TRUE_RECO_Particle.ApplyColorPalette(Helium9_colorScheme);


PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Energy_PION_TRUE_RECO("h_secTrk_Energy_PION_TRUE_RECO", "h_secTrk_Energy PION(TRUE +RECO)",  Vertex_secondTrkEbin_Proton_vector, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Theta_PION_TRUE_RECO("h_secTrk_Theta_PION_TRUE_RECO", "h_secTrk_Theta PION (TRUE+RECO)",  secTrk_Theta_TRUEbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Openangle_PION_TRUE_RECO("h_secTrk_Openangle_PION_TRUE_RECO", "h_secTrk_Openangle  PION (TRUE+RECO)",  secTrk_Theta_TRUEbin_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Energy_PION0_TRUE_RECO("h_secTrk_Energy_PION0_TRUE_RECO", "h_secTrk_Energy PION(TRUE +RECO)",  Vertex_secondTrkEbin_Proton_vector, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Theta_PION0_TRUE_RECO("h_secTrk_Theta_PION0_TRUE_RECO", "h_secTrk_Theta PION (TRUE+RECO)",  secTrk_Theta_TRUEbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Openangle_PION0_TRUE_RECO("h_secTrk_Openangle_PION0_TRUE_RECO", "h_secTrk_Openangle  PION (TRUE+RECO)",  secTrk_Theta_TRUEbin_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Energy_PION_neg_pos_TRUE_RECO("h_secTrk_Energy_PION_neg_pos_TRUE_RECO", "h_secTrk_Energy PION(TRUE +RECO)",  Vertex_secondTrkEbin_Proton_vector, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Theta_PION_neg_pos_TRUE_RECO("h_secTrk_Theta_PION_neg_pos_TRUE_RECO", "h_secTrk_Theta PION (TRUE+RECO)",  secTrk_Theta_TRUEbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Openangle_PION_neg_pos_TRUE_RECO("h_secTrk_Openangle_PION_neg_pos_TRUE_RECO", "h_secTrk_Openangle  PION (TRUE+RECO)",  secTrk_Theta_TRUEbin_vector , error_bands);



PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Energy_PROTON_TRUE_RECO("h_secTrk_Energy_PROTON_TRUE_RECO", "h_secTrk_Energy Proton(TRUE+RECO)",  Vertex_secondTrkEbin_Proton_vector, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Theta_PROTON_TRUE_RECO("h_secTrk_Theta_PROTON_TRUE_RECO", "h_secTrk_Theta Proton(TRUE+RECO)",  secTrk_Theta_TRUEbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Openangle_PROTON_TRUE_RECO("h_secTrk_Openangle_PROTON_TRUE_RECO", "h_secTrk_Openangle Proton(TRUE+RECO) ",  secTrk_Theta_TRUEbin_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Energy_Dimuon_TRUE_RECO("h_secTrk_Energy_Dimuon_TRUE_RECO", "h_secTrk_Energy Dimuon(TRUE+RECO)",  Vertex_secondTrkEbin_Proton_vector, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Theta_Dimuon_TRUE_RECO("h_secTrk_Theta_Dimuon_TRUE_RECO", "h_secTrk_Theta Dimuon(TRUE+RECO)",  secTrk_Theta_TRUEbin_vector , error_bands);
 //PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Openangle_Dimuon_TRUE("h_secTrk_Openangle_Dimuon_TRUE", "h_secTrk_Openangle Dimuon(TRUE)",  secTrk_Theta_TRUEbin_vector , error_bands);
 //PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Openangle_Dimuon_TRUE_RECO("h_secTrk_Openangle_Dimuon_TRUE_RECO", "h_secTrk_Openangle Dimuon(TRUE+RECO) ",  secTrk_Theta_TRUEbin_vector , error_bands);
 PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_FirstNodeX("h_secTrk_FirstNodeX", "h_secTrk_FirstNodeX",  secTrk_StartNode_X_vector, error_bands);
 PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_FirstNodeX_Material =
 PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_FirstNodeX_Material", secTrk_StartNode_X_vector ,"h_secTrk_FirstNodeX_Material; [mm];Events");

 PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_secTrk_FirstNodeX_Interaction =
 PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_secTrk_FirstNodeX_Interaction", secTrk_StartNode_X_vector ,"h_secTrk_FirstNodeX_Interaction; [mm];Events");

 PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_FirstNodeX_Particle =
 PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_FirstNodeX_Particle", secTrk_StartNode_X_vector ,"h_secTrk_FirstNodeY_Particle; [mm];Events");


 PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_FirstNodeY("h_secTrk_FirstNodeY", "h_secTrk_FirstNodeY",  secTrk_StartNode_Y_vector, error_bands);
 PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_FirstNodeY_Material =
 PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_FirstNodeY_Material", secTrk_StartNode_Y_vector ,"h_secTrk_FirstNodeY_Material; [mm];Events");

 PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_secTrk_FirstNodeY_Interaction =
 PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_secTrk_FirstNodeY_Interaction", secTrk_StartNode_Y_vector ,"h_secTrk_FirstNodeY_Interaction; [mm];Events");

 PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_FirstNodeY_Particle =
 PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_FirstNodeY_Particle", secTrk_StartNode_Y_vector ,"h_secTrk_FirstNodeY_Particle; [mm];Events");


 PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_FirstNodeZ("h_secTrk_FirstNodeZ", "h_secTrk_FirstNodeZ",  secTrk_StartNode_Z_vector, error_bands);
 PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_FirstNodeZ_Material =
 PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_FirstNodeZ_Material", secTrk_StartNode_Z_vector ,"h_secTrk_FirstNodeZ_Material; [mm];Events");

 PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_secTrk_FirstNodeZ_Interaction =
 PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_secTrk_FirstNodeZ_Interaction", secTrk_StartNode_Z_vector ,"h_secTrk_FirstNodeZ_Interaction; [mm];Events");

 PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_FirstNodeZ_Particle =
 PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_FirstNodeZ_Particle", secTrk_StartNode_Z_vector ,"h_secTrk_FirstNodeZ_Particle; [mm];Events");

 PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_LastNodeX("h_secTrk_LastNodeX", "h_secTrk_LastNodeX",  secTrk_LastNodeX_vector, error_bands);

 PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_LastNodeX_Material =
 PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_LastNodeX_Material", secTrk_LastNodeX_vector ,"h_secTrk_LastNodeX_Material; [mm];Events");

 PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_secTrk_LastNodeX_Interaction =
 PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_secTrk_LastNodeX_Interaction", secTrk_LastNodeX_vector ,"h_secTrk_LastNodeX_Interaction; [mm];Events");

 PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_LastNodeX_Particle =
 PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_LastNodeX_Particle",secTrk_LastNodeX_vector ,"h_secTrk_LastNodeX_Particle; [mm];Events");


 PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_LastNodeY("h_secTrk_LastNodeY", "h_secTrk_LastNodeY",  secTrk_LastNodeY_vector, error_bands);
 PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_LastNodeY_Material =
 PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_LastNodeY_Material", secTrk_LastNodeY_vector ,"h_secTrk_LastNodeY_Material; [mm];Events");

 PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_secTrk_LastNodeY_Interaction =
 PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_secTrk_LastNodeY_Interaction", secTrk_LastNodeY_vector ,"h_secTrk_LastNodeY_Interaction; [mm];Events");

 PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_LastNodeY_Particle =
 PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_LastNodeY_Particle", secTrk_LastNodeY_vector ,"h_secTrk_LastNodeY_Particle; [mm];Events");


 PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_LastNodeZ("h_secTrk_LastNodeZ", "h_secTrk_LastNodeZ",  secTrk_LastNodeZ_vector, error_bands);
 PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_LastNodeZ_Material =
 PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_LastNodeZ_Material", secTrk_LastNodeZ_vector,"h_secTrk_LastNodeZ_Material; [mm];Events");

 PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_secTrk_LastNodeZ_Interaction =
 PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_secTrk_LastNodeZ_Interaction", secTrk_LastNodeZ_vector ,"h_secTrk_LastNodeZ_Interaction; [mm];Events");

 PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_LastNodeZ_Particle =
 PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_LastNodeZ_Particle", secTrk_LastNodeZ_vector ,"h_secTrk_LastNodeZ_Particle; [mm];Events");

///////////
///Vetowall
///////////
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<std::endl;
std::cout<<"~~~~ initialize Veto Varibles  ~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<std::endl;

PlotUtils::HistWrapper<HeliumCVUniverse> h_VetoWall_matchToVeto("h_VetoWall_matchToVeto", "h_VetoWall_matchToVeto", MuonMatchtoVeto_vector , error_bands);
//Categorized<MnvH1D, int> h_VetoWall_matchToVeto_material(    "h_VetoWall_matchToVeto_material", "Match to Veto", Materials, 2, -0.5, 1.5  ); //EbinN, Ebins
//Categorized<MnvH1D, int> h_VetoWall_matchToVeto_interaction( "h_VetoWall_matchToVeto_interaction", "Match to Veto", Interaction, 2, -0.5, 1.5  ); //EbinN, Ebins
//Categorized<MnvH1D, int> h_VetoWall_matchToVeto_particle(    "h_VetoWall_matchToVeto_particle", "Match to Veto", Particle, 2, -0.5, 1.5  ); //EbinN, Ebins



PlotUtils::HistWrapper<HeliumCVUniverse> h_VetoWall_NumbermatchToVeto("h_VetoWall_NumbermatchToVeto", "h_VetoWall_NumbermatchToVeto", 7, -1.5, 5.5 , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_VetoWall_vetoSixPush("h_VetoWall_vetoSixPush", "h_VetoWall_vetoSixPush", MuonMatchtoVeto_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_VetoWall_extrapnowalls("h_VetoWall_extrapnowalls","h_VetoWall_extrapnowalls", MuonMatchtoVeto_vector ,error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_VetoWall_extrapwall1("h_VetoWall_extrapwall1","h_VetoWall_extrapwall1", MuonMatchtoVeto_vector ,error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_VetoWall_extrapwall2("h_VetoWall_extrapwall2","h_VetoWall_extrapwall2", MuonMatchtoVeto_vector ,error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_VetoWall_extrapbothwalls("h_VetoWall_extrapbothwalls","h_VetoWall_extrapbothwalls", MuonMatchtoVeto_vector ,error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_VetoWall_MuonTrkMatchToVETOwalloff("h_VetoWall_MuonTrkMatchToVETOwalloff","h_VetoWall_MuonTrkMatchToVETOwalloff", MuonMatchtoVeto_vector ,error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_VetoWall_PMTmap_ON("h_VetoWall_PMTmap_ON","h_VetoWall_PMTmap_ON", Veto_PMTmap_vector ,error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_VetoWall_PMTmap_OFF("h_VetoWall_PMTmap_OFF","h_VetoWall_PMTmap_OFF", Veto_PMTmap_vector ,error_bands);


PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonMatchtoVeto("h_MuonMatchtoVeto", "Is It Matched (bool)", MuonMatchtoVeto_vector , error_bands);



PlotUtils::HistFolio<PlotUtils::MnvH1D, Veto_status_type> h_Veto_PMT_Map =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Veto_status_type>(Veto_PMT_status_Category, "h_Veto_PMT_Map", Veto_PMTmap_vector ,"h_Veto_PMT_Map;");



PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonMatchtoVeto_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonMatchtoVeto_Material", MuonMatchtoVeto_vector ,"h_MuonMatchtoVeto_Material; [bool];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonMatchtoVeto_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_MuonMatchtoVeto_Interaction",MuonMatchtoVeto_vector  ,"h_MuonMatchtoVeto_Interaction; [bool];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_MuonMatchtoVeto_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_MuonMatchtoVeto_Particle",MuonMatchtoVeto_vector ," h_MuonMatchtoVeto_Particle; [bool];Events");
//h_MuonMatchtoVeto_Particle.ApplyColorPalette(Helium9_colorScheme);

PlotUtils::HistWrapper<HeliumCVUniverse> h_VetoWall_PMTPaddleMap("h_VetoWall_PMTPaddleMap","h_VetoWall_PMTPaddleMap", MuonMatchtoVeto_vector ,error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_Qsquare_TRUE_RECO("h_Qsquare_TRUE_RECO", "Q^{2} NEW Method",  PTbin_vector , error_bands);




PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_Particle_N_A_secTrk_Theta_TRUE_RECO_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_Particle_N_A_secTrk_Theta_TRUE_RECO_Interaction", secTrk_Theta_TRUEbin_vector ,"h_Particle_N_A_secTrk_Theta_TRUE_RECO_Interaction; [Degs];Events");
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<std::endl;
std::cout<<"~~~~Finshed to initialize Histograms ~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<std::endl;

/////////////////////////////////////////

  //=========================================
  // Entry Loop For MC
  //=========================================

  //std::vector<ECuts> kCutsVector;
  std::vector  <ArachnesecTrk> arachneHigh_angle;
  std::vector  <ArachnesecTrk> arachneLow_KE;
  std::vector  <ArachnesecTrk> arachneBoth;
  std::vector <Arachne_alltracks> Arachne_alltrks;
  std::vector <Trajector> All_True_trajectors;
  std::vector <Trajector_withTrueEnergyFraction> All_RECO_trajectors;
  std::vector <TRUE_RECO_Energies_Trajectors> True_Reco_Energies;


  std::vector <Trajector_withTrueEnergyFraction> All_RECO_trajectors_Parent;
  std::vector <TRUE_RECO_Energies_Trajectors> True_Reco_Energies_Parent;




  ProcInfo_t procInfo;
  gSystem->GetProcInfo(&procInfo);

std::string sysmatics_status;
if(m_RunCodeWithSystematics==true){sysmatics_status= "Systematics On";}
else if (m_RunCodeWithSystematics==false){sysmatics_status= "Systematics Off";}
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;
std::cout<<"~~~~~~~~~ Systematics are =   "<< sysmatics_status <<" ~~~~~~~~~ "<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;


//RECO_Cut_Map CountMap_RECO_Eff = ConstuctRecoCountingMap(kCutsVector_Eff);


//TRUE_Cut_Map CountMap_TRUTH =  ConstuctTRUTHCountingMap(kTRUTHCutsVector);
RECO_Cut_Map CountMap_RECO;// = ConstuctRecoCountingMap(kCutsVector);
RECO_Cut_Map CountMap_RECO_Helium ;//= ConstuctRecoCountingMap(kCutsVector);
RECO_Cut_Map CountMap_RECO_nonHelium;// = ConstuctRecoCountingMap(kCutsVector);
RECO_Cut_Map CountMap_TRUE_RECO;
TRUE_Cut_Map Truth_Cut_Map;

FillingRecoCountingMap(kCutsVector, CountMap_RECO);
FillingRecoCountingMap(kCutsVector, CountMap_RECO_Helium);
FillingRecoCountingMap(kCutsVector, CountMap_RECO_nonHelium);
FillingRecoCountingMap(kCutsVector_Eff, CountMap_TRUE_RECO);
FillingTruthCountingMap(kTRUTHCutsVector, Truth_Cut_Map);

std::cout << "CountMap_RECO.size() = " << CountMap_RECO.size()<< std::endl;
for(const auto & index :CountMap_RECO ){
std::cout<<" Cut Name = " <<GetCutName(index.first).c_str() << " Amount = " << index.second << std::endl;


}



std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;
std::cout<<"~~~~~~~~~  THIS IS RECO 1D ~~~~~~~~~ "<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;


int PDG_notmatch=0;
int PDG_match=0;

  std::cout << "Memory/time used so Far: " << procInfo.fMemResident/1000<< " MB" <<" time = "<<  procInfo.fCpuSys <<  " Sec"<<"\n";

  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"MC LOOP  "<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  double Pi = 3.14159265358979323846;
  for(int ii=0; ii<chw_MC->GetEntries(); ++ii){

    if(ii%1000==0) std::cout << (ii/100) << " k " << std::flush;

    //=========================================
    // For every systematic, loop over the universes, and fill the
    // appropriate histogram in the MnvH1D
    //=========================================
/*
    for (auto band : error_bands)
    {
      std::vector<HeliumCVUniverse*> error_band_universes = band.second;
      for (auto universe : error_band_universes){
*/


    for (auto  Universe_GROUP: Error_Band_Universe_GROUPS){

//      std::vector<HeliumCVUniverse*> error_band_universes = band.second;
     Universe_GROUP.front()->SetEntry(ii);




    if(PassesCutsRECO(*Universe_GROUP.front(),  is_mc , kCutsVector,kWeights_v1tune, CountMap_RECO, CountMap_RECO_Helium, CountMap_RECO_nonHelium) ){
  // std::cout<<"Inside Truth Cuts "<< std::endl;
  //std::cout<<"NEW GROUP "<< std::endl;

        for (auto universe : Universe_GROUP){
          //std::cout<<"universe->ShortName() = " << universe->ShortName()<<std::endl;
        // Tell the Event which entry in the TChain it's looking at
        universe->SetEntry(ii);

        ///////////////////////////////////////////
        ////
        ////  Varibles that go into all universes
        ////
        ////
        ///////////////////////////////////////////

        double wgt_minerva_v1 = universe->GetWeight(kWeights_v1tune);

        double Theta = universe->GetThetamu();
        double Pmu = universe ->GetPmu()/1000;

        double pseduo_r = universe->pseudorapidity_muon();
        double pseduo_theta = 2 * atan(exp(-pseduo_r)) *TMath::RadToDeg();

        auto PDG_trklist = universe->GetVector_nonMuonTk_PDG_Parent();
        auto Energy_trklist = universe-> GetVector_nonMuonTk_Energy_GeV_Parent();
        auto Angle_trklist = universe->GetVector_nonMuonTk_Angle_wrtb_Degs_Parent();

        auto EnergyFraction_vector = universe->Get_TrueFractionE_vector();

        //int secondTrk = universe->Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_lessthanAngle_muonNotinlist(PDG_trklist, Energy_trklist, Angle_trklist, EnergyFraction_vector);
      //int secondTrk_nonparent = universe->Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_lessthanAngle_muonNotinlist(PDG_trklist_nonparent, Energy_trklist_nonparent, Angle_trklist_nonparent, EnergyFraction_vector);
      int secondTrk = universe->Getindex2ndTrackhighestKE();
      //  int secondTrk = universe-> Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_lessthanAngle_muonNotinlist_KE_proton_pion_thrusthold(PDG_trklist, Energy_trklist, Angle_trklist, EnergyFraction_vector);
        if(secondTrk==-9999 ||secondTrk==-999 )continue;

        ///////////////////////////////////////////
        ////
        ////  FILL CV
        ////
        ////
        ///////////////////////////////////////////
        if( isCV(*universe)){


            auto PDG_trklist_nonparent = universe->GetVector_nonMuonTk_PDG();
            auto Energy_trklist_nonparent = universe-> GetVector_nonMuonTk_Energy_GeV();
            auto Angle_trklist_nonparent = universe->GetVector_nonMuonTk_Angle_wrtb_Degs();



            //int secondTrk = universe->Getindex2ndTrackhighestKE();
            int fraction_count=1;
            for(auto fraction : EnergyFraction_vector ){

              h_2d_Track_Fraction_Energy->Fill(fraction_count,fraction,wgt_minerva_v1);
              fraction_count++;
            }


            //std::cout<<"fails 1"<<std::endl;
            Interaction_type Interaction_type_Event =  universe->Get_InteractionStackType();
            Material_type Material_type_Event = universe->Get_MaterialStackType();
            TrackType Track_type_Event = universe->GetTrackType();
            //Particle_type Particle_type_Event =  universe->Get_NonParticleStackType(secondTrk);
            int secTrk_PDG = PDG_trklist.at(secondTrk);
            //std::cout<<"fails 2"<<std::endl;
            int secTrk_PDG_nonpartent = PDG_trklist_nonparent.at(secondTrk);
            //std::cout<<"fails 3"<<std::endl;
            Particle_type Particle_type_Event_nonparent =  GetParticlegroup_type(secTrk_PDG_nonpartent);
            //std::cout<<"fails 4"<<std::endl;
            Particle_type Particle_type_Event =  GetParticlegroup_type(secTrk_PDG);
            //std::cout<<"fails 5"<<std::endl;
            ///////////////////////////////////////////
            ////
            ////  Apply RECO CUTS to CV
            ////
            ///////////////////////////////////////////

              for(auto fraction : EnergyFraction_vector ){

              h_2d_Track_Fraction_Energy_Cuts->Fill(fraction_count,fraction,wgt_minerva_v1);
                fraction_count++;
              }

              double weight_forMK = universe->GetWeight(kWeights_forMK);
              double MK_Weight = universe->GetMKmodelWeight_local(weight_MK);

              h_MuonE_v2tune->Fill(universe->GetMuonE_ECT(),universe->GetWeight(kWeights_v2tune));
              h_MuonE_MKmodel->Fill(universe->GetMuonE_ECT(),weight_forMK*weight_forMK);

              VertexOptions VertexOption_type = universe->GetVertex_optionType();
              boolNTrack boolNTrack_Type = universe->GetVertex_boolNTrack();

              //bool trk1 = universe->GetisOneTrk();
              //bool trk2 = universe->GetisTwoTrk();
              //bool trkgreater2 = universe->GetisTwoTrk();


              //if(trk2 != trkgreater2 ){std::cout << std::boolalpha <<"trk1 = " <<trk1 <<"  trk2 =  " <<trk2 <<"  trkgreater2 = "<< trkgreater2 << std::endl;}

              h_MuonE_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetEmu()*.001, wgt_minerva_v1);
              h_MuonE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetEmu()*.001, wgt_minerva_v1);
              h_MuonE_Particle.GetComponentHist(Particle_type_Event,false)->Fill(universe->GetEmu()*.001, wgt_minerva_v1);

              h_MuonPZ_Material.GetComponentHist(Material_type_Event)->Fill(Pmu*std::cos(Theta), wgt_minerva_v1);
              h_MuonPZ_Interaction.GetComponentHist(Interaction_type_Event)->Fill(Pmu*std::cos(Theta), wgt_minerva_v1);
              h_MuonPZ_Particle.GetComponentHist(Particle_type_Event)->Fill(Pmu*std::cos(Theta), wgt_minerva_v1);

              h_MuonPT_Material.GetComponentHist(Material_type_Event)->Fill(Pmu*std::sin(Theta), wgt_minerva_v1);
              h_MuonPT_Interaction.GetComponentHist(Interaction_type_Event)->Fill(Pmu*std::sin(Theta), wgt_minerva_v1);
              h_MuonPT_Particle.GetComponentHist(Particle_type_Event)->Fill(Pmu*std::sin(Theta), wgt_minerva_v1);

              h_MuonTheta_Material.GetComponentHist(Material_type_Event)->Fill(Theta*toDegs, wgt_minerva_v1);
              h_MuonTheta_Interaction.GetComponentHist(Interaction_type_Event)->Fill(Theta*toDegs, wgt_minerva_v1);
              h_MuonTheta_Particle.GetComponentHist(Particle_type_Event)->Fill(Theta*toDegs, wgt_minerva_v1);

              h_MuonPhi_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetPhimu()*toDegs, wgt_minerva_v1);
              h_MuonPhi_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetPhimu()*toDegs, wgt_minerva_v1);
              h_MuonPhi_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetPhimu()*toDegs, wgt_minerva_v1);

              h_MuonDOCA_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetDOCAmu(), wgt_minerva_v1);
              h_MuonDOCA_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetDOCAmu(), wgt_minerva_v1);
              h_MuonDOCA_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetDOCAmu(), wgt_minerva_v1);

              h_Tracksize_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetTracksize(), wgt_minerva_v1);
              h_Tracksize_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetTracksize(), wgt_minerva_v1);
              h_Tracksize_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetTracksize(), wgt_minerva_v1);


              h_muon_minosStart_X_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetMINOSStart_X(), wgt_minerva_v1);
              h_muon_minosStart_X_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetMINOSStart_X(), wgt_minerva_v1);
              h_muon_minosStart_X_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetMINOSStart_X(), wgt_minerva_v1);


              h_muon_minosStart_Y_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetMINOSStart_Y(), wgt_minerva_v1);
              h_muon_minosStart_Y_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetMINOSStart_Y(), wgt_minerva_v1);
              h_muon_minosStart_Y_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetMINOSStart_Y(), wgt_minerva_v1);


              h_muon_minosStart_Z_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetMINOSStart_Z(), wgt_minerva_v1);
              h_muon_minosStart_Z_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetMINOSStart_Z(), wgt_minerva_v1);
              h_muon_minosStart_Z_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetMINOSStart_Z(), wgt_minerva_v1);


              h_muon_minosEnd_X_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetMINOSEnd_X(), wgt_minerva_v1);
              h_muon_minosEnd_X_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetMINOSEnd_X(), wgt_minerva_v1);
              h_muon_minosEnd_X_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetMINOSEnd_X(), wgt_minerva_v1);


              h_muon_minosEnd_Y_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetMINOSEnd_Y(), wgt_minerva_v1);
              h_muon_minosEnd_Y_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetMINOSEnd_Y(), wgt_minerva_v1);
              h_muon_minosEnd_Y_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetMINOSEnd_Y(), wgt_minerva_v1);


              h_muon_minosEnd_Z_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetMINOSEnd_Z(), wgt_minerva_v1);
              h_muon_minosEnd_Z_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetMINOSEnd_Z(), wgt_minerva_v1);
              h_muon_minosEnd_Z_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetMINOSEnd_Z(), wgt_minerva_v1);


              h_muon_StartNode_X_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetMuon_firstNode_X(), wgt_minerva_v1);
              h_muon_StartNode_X_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetMuon_firstNode_X(), wgt_minerva_v1);
              h_muon_StartNode_X_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetMuon_firstNode_X(), wgt_minerva_v1);


              h_muon_StartNode_Y_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetMuon_firstNode_Y(), wgt_minerva_v1);
              h_muon_StartNode_Y_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetMuon_firstNode_Y(), wgt_minerva_v1);
              h_muon_StartNode_Y_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetMuon_firstNode_Y(), wgt_minerva_v1);


              h_muon_StartNode_Z_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetMuon_firstNode_Z(), wgt_minerva_v1);
              h_muon_StartNode_Z_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetMuon_firstNode_Z(), wgt_minerva_v1);
              h_muon_StartNode_Z_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetMuon_firstNode_Z(), wgt_minerva_v1);


              h_muon_LastNode_Y_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetMuon_lastNode_Y(), wgt_minerva_v1);
              h_muon_LastNode_Y_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetMuon_lastNode_Y(), wgt_minerva_v1);
              h_muon_LastNode_Y_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetMuon_lastNode_Y(), wgt_minerva_v1);

              h_muon_LastNode_X_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetMuon_lastNode_X(), wgt_minerva_v1);
              h_muon_LastNode_X_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetMuon_lastNode_X(), wgt_minerva_v1);
              h_muon_LastNode_X_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetMuon_lastNode_X(), wgt_minerva_v1);

              h_muon_LastNode_Z_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetMuon_lastNode_Z(), wgt_minerva_v1);
              h_muon_LastNode_Z_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetMuon_lastNode_Z(), wgt_minerva_v1);
              h_muon_LastNode_Z_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetMuon_lastNode_Z(), wgt_minerva_v1);

              h_MuonCurvatureSig_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetCurvatureSignificance(), wgt_minerva_v1);
              h_MuonCurvatureSig_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetCurvatureSignificance(), wgt_minerva_v1);
              h_MuonCurvatureSig_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetCurvatureSignificance(), wgt_minerva_v1);

              h_CryoVertex_X_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetVertex_x(), wgt_minerva_v1);
              h_CryoVertex_X_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetVertex_x(), wgt_minerva_v1);
              h_CryoVertex_X_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetVertex_x(), wgt_minerva_v1);
              h_CryoVertex_X_Track.GetComponentHist(Track_type_Event)->Fill(universe->GetVertex_x(), wgt_minerva_v1);
              h_CryoVertex_X_boolNTrack.GetComponentHist(boolNTrack_Type)->Fill(universe->GetVertex_x(), wgt_minerva_v1);
              h_CryoVertex_X_VertexOptions.GetComponentHist(VertexOption_type)->Fill(universe->GetVertex_x(), wgt_minerva_v1);




              h_CryoVertex_Y_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetVertex_y(), wgt_minerva_v1);
              h_CryoVertex_Y_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetVertex_y(), wgt_minerva_v1);
              h_CryoVertex_Y_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetVertex_y(), wgt_minerva_v1);
              h_CryoVertex_Y_Track.GetComponentHist(Track_type_Event)->Fill(universe->GetVertex_y(), wgt_minerva_v1);
              h_CryoVertex_Y_boolNTrack.GetComponentHist(boolNTrack_Type)->Fill(universe->GetVertex_y(), wgt_minerva_v1);
              h_CryoVertex_Y_VertexOptions.GetComponentHist(VertexOption_type)->Fill(universe->GetVertex_y(), wgt_minerva_v1);



              h_CryoVertex_Z_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetVertex_z(), wgt_minerva_v1);
              h_CryoVertex_Z_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetVertex_z(), wgt_minerva_v1);
              h_CryoVertex_Z_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetVertex_z(), wgt_minerva_v1);
              h_CryoVertex_Z_Track.GetComponentHist(Track_type_Event)->Fill(universe->GetVertex_z(), wgt_minerva_v1);
              h_CryoVertex_Z_boolNTrack.GetComponentHist(boolNTrack_Type)->Fill(universe->GetVertex_z(), wgt_minerva_v1);
              h_CryoVertex_Z_VertexOptions.GetComponentHist(VertexOption_type)->Fill(universe->GetVertex_z(), wgt_minerva_v1);


              h_CryoVertex_R_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetVertex_r(), wgt_minerva_v1);
              h_CryoVertex_R_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetVertex_r(), wgt_minerva_v1);
              h_CryoVertex_R_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetVertex_r(), wgt_minerva_v1);
              h_CryoVertex_R_Track.GetComponentHist(Track_type_Event)->Fill(universe->GetVertex_r(), wgt_minerva_v1);

              h_CryoVertex_R_boolNTrack.GetComponentHist(boolNTrack_Type)->Fill(universe->GetVertex_r(), wgt_minerva_v1);
              h_CryoVertex_R_VertexOptions.GetComponentHist(VertexOption_type)->Fill(universe->GetVertex_r(), wgt_minerva_v1);


              h_secTrk_Pathlength_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetNonmuTrkLength(secondTrk), wgt_minerva_v1);
              h_secTrk_Pathlength_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetNonmuTrkLength(secondTrk), wgt_minerva_v1);
              h_secTrk_Pathlength_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetNonmuTrkLength(secondTrk), wgt_minerva_v1);

              h_secTrk_tracklength_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetNonmuTrkLength_InMinerva_Incm(secondTrk), wgt_minerva_v1);
              h_secTrk_tracklength_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetNonmuTrkLength_InMinerva_Incm(secondTrk), wgt_minerva_v1);
              h_secTrk_tracklength_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetNonmuTrkLength_InMinerva_Incm(secondTrk), wgt_minerva_v1);
              h_secTrk_tracklength_Track.GetComponentHist(Track_type_Event)->Fill(universe->GetNonmuTrkLength_InMinerva_Incm(secondTrk), wgt_minerva_v1);


              h_secTrk_Energy_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetNonmuTrkE_GeV(secondTrk), wgt_minerva_v1);
              h_secTrk_Energy_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetNonmuTrkE_GeV(secondTrk), wgt_minerva_v1);
              h_secTrk_Energy_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetNonmuTrkE_GeV(secondTrk), wgt_minerva_v1);


              h_secTrk_nonparentEnergy_Particle.GetComponentHist(Particle_type_Event_nonparent)->Fill(universe->GetNonmuTrkE_GeV(secondTrk), wgt_minerva_v1);

              h_secTrk_DOCA_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetNonmuDOCA(secondTrk), wgt_minerva_v1);
              h_secTrk_DOCA_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetNonmuDOCA(secondTrk), wgt_minerva_v1);
              h_secTrk_DOCA_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetNonmuDOCA(secondTrk), wgt_minerva_v1);

              h_secTrk_MidTheta_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetNonmuTrkAngleWRTbeamMID(secondTrk), wgt_minerva_v1);
              h_secTrk_MidTheta_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetNonmuTrkAngleWRTbeamMID(secondTrk), wgt_minerva_v1);
              h_secTrk_MidTheta_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetNonmuTrkAngleWRTbeamMID(secondTrk), wgt_minerva_v1);

              double chisqt = universe->GetVertexChiSqrFit();
              h_CryoVertexChiSqFit_Material.GetComponentHist(Material_type_Event)->Fill(chisqt, wgt_minerva_v1);
              h_CryoVertexChiSqFit_Interaction.GetComponentHist(Interaction_type_Event)->Fill(chisqt, wgt_minerva_v1);
              h_CryoVertexChiSqFit_Particle.GetComponentHist(Particle_type_Event)->Fill(chisqt, wgt_minerva_v1);
              h_CryoVertexChiSqFit_Track.GetComponentHist(Track_type_Event)->Fill(chisqt, wgt_minerva_v1);
              h_CryoVertexChiSqFit_boolNTrack.GetComponentHist(boolNTrack_Type)->Fill(chisqt, wgt_minerva_v1);
              h_CryoVertexChiSqFit_VertexOptions.GetComponentHist(VertexOption_type)->Fill(chisqt, wgt_minerva_v1);

              if(chisqt>10.0){h_CryoVertexChiSqFitgreater10_Track.GetComponentHist(Track_type_Event)->Fill(chisqt, wgt_minerva_v1);}


              h_secTrk_FirstNodeX_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetFirstNodeX(secondTrk),wgt_minerva_v1);
              h_secTrk_FirstNodeX_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetFirstNodeX(secondTrk),wgt_minerva_v1);
              h_secTrk_FirstNodeX_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetFirstNodeX(secondTrk),wgt_minerva_v1);

              h_secTrk_FirstNodeY_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetFirstNodeY(secondTrk),wgt_minerva_v1);
              h_secTrk_FirstNodeY_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetFirstNodeY(secondTrk),wgt_minerva_v1);
              h_secTrk_FirstNodeY_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetFirstNodeY(secondTrk),wgt_minerva_v1);

              h_secTrk_FirstNodeZ_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetFirstNodeZ(secondTrk),wgt_minerva_v1);
              h_secTrk_FirstNodeZ_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetFirstNodeZ(secondTrk),wgt_minerva_v1);
              h_secTrk_FirstNodeZ_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetFirstNodeZ(secondTrk),wgt_minerva_v1);

              h_secTrk_LastNodeX_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetLastNodeX(secondTrk),wgt_minerva_v1);
              h_secTrk_LastNodeX_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetLastNodeX(secondTrk),wgt_minerva_v1);
              h_secTrk_LastNodeX_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetLastNodeX(secondTrk),wgt_minerva_v1);

              h_secTrk_LastNodeY_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetLastNodeY(secondTrk),wgt_minerva_v1);
              h_secTrk_LastNodeY_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetLastNodeY(secondTrk),wgt_minerva_v1);
              h_secTrk_LastNodeY_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetLastNodeY(secondTrk),wgt_minerva_v1);

              h_secTrk_LastNodeZ_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetLastNodeZ(secondTrk),wgt_minerva_v1);
              h_secTrk_LastNodeZ_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetLastNodeZ(secondTrk),wgt_minerva_v1);
              h_secTrk_LastNodeZ_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetLastNodeZ(secondTrk),wgt_minerva_v1);

              h_MuonCharge_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetChargemu(),wgt_minerva_v1);
              h_MuonCharge_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetChargemu(),wgt_minerva_v1);
              h_MuonCharge_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetChargemu(),wgt_minerva_v1);

              h_MuonMatchtoMinos_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetIntIsusableMuon(),wgt_minerva_v1);
              h_MuonMatchtoMinos_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetIntIsusableMuon(),wgt_minerva_v1);
              h_MuonMatchtoMinos_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetIntIsusableMuon(),wgt_minerva_v1);

              h_MuonMatchtoVeto_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetMatchToVeto(),wgt_minerva_v1);
              h_MuonMatchtoVeto_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetMatchToVeto(),wgt_minerva_v1);
              h_MuonMatchtoVeto_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetMatchToVeto(),wgt_minerva_v1);

              h_secTrk_Openangle_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetOpenAngle(secondTrk), wgt_minerva_v1);
              h_secTrk_Openangle_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetOpenAngle(secondTrk), wgt_minerva_v1);
              h_secTrk_Openangle_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetOpenAngle(secondTrk), wgt_minerva_v1);

              h_2d_2ndtrkPathlength_vertex_R->Fill(universe->GetNonmuTrkLength(secondTrk),universe->GetVertex_r(), wgt_minerva_v1);
              h_2d_2ndtrkPathlength_vertex_Z->Fill(universe->GetNonmuTrkLength(secondTrk),universe->GetVertex_z(), wgt_minerva_v1);

              h2_FirstZnode_2ndTrklength->Fill(universe->GetFirstNodeZ(secondTrk), universe->GetNonmuTrkLength(secondTrk), wgt_minerva_v1);
              h2_LastZnode_2ndTrklength->Fill(universe->GetLastNodeZ(secondTrk), universe->GetNonmuTrkLength(secondTrk), wgt_minerva_v1);

              h_2d_2ndtrkLength_vertex_R->Fill(universe->GetNonmuTrkLength_InMinerva_Incm(secondTrk),universe->GetVertex_r(), wgt_minerva_v1);
              h_2d_2ndtrkLength_vertex_Z->Fill(universe->GetNonmuTrkLength_InMinerva_Incm(secondTrk),universe->GetVertex_z(), wgt_minerva_v1);
              h_2d_2ndtrkLength_Angle->Fill(universe->GetNonmuTrkLength_InMinerva_Incm(secondTrk),universe->GetNonmuTrkAngleWRTbeamMID(secondTrk), wgt_minerva_v1);
              h_2d_2ndtrkLength_finerAngle->Fill(universe->GetNonmuTrkLength_InMinerva_Incm(secondTrk),universe->GetNonmuTrkAngleWRTbeamMID(secondTrk), wgt_minerva_v1);

              auto trackType = universe->GetTrackType();

              if(universe->GetTargetType()==2){
                h_Efficiency_h_CryoVertexChiSqFit[0]->Fill(universe->GetVertexChiSqrFit(),wgt_minerva_v1);
                h_Efficiency_h_CryoVertexChiSqFit[2]->Fill(universe->GetVertexChiSqrFit(),wgt_minerva_v1);

                if(kLong==trackType)
                {
                  h_Efficiency_h_CryoVertexChiSqFit_long[0]->Fill(universe->GetVertexChiSqrFit(),wgt_minerva_v1);
                  h_Efficiency_h_CryoVertexChiSqFit_long[2]->Fill(universe->GetVertexChiSqrFit(),wgt_minerva_v1);
                }

                else if (kShort==trackType){
                  h_Efficiency_h_CryoVertexChiSqFit_short[0]->Fill(universe->GetVertexChiSqrFit(),wgt_minerva_v1);
                  h_Efficiency_h_CryoVertexChiSqFit_short[2]->Fill(universe->GetVertexChiSqrFit(),wgt_minerva_v1);

                }
                else if(kOtherLong==trackType) {
                  h_Efficiency_h_CryoVertexChiSqFit_otherlong[0]->Fill(universe->GetVertexChiSqrFit(),wgt_minerva_v1);
                  h_Efficiency_h_CryoVertexChiSqFit_otherlong[2]->Fill(universe->GetVertexChiSqrFit(),wgt_minerva_v1);
                }

              }

              else{
                h_Efficiency_h_CryoVertexChiSqFit[1]->Fill(universe->GetVertexChiSqrFit(),wgt_minerva_v1);
                h_Efficiency_h_CryoVertexChiSqFit[2]->Fill(universe->GetVertexChiSqrFit(),wgt_minerva_v1);

                if(kLong==trackType)
                {
                  h_Efficiency_h_CryoVertexChiSqFit_long[1]->Fill(universe->GetVertexChiSqrFit(),wgt_minerva_v1);
                  h_Efficiency_h_CryoVertexChiSqFit_long[2]->Fill(universe->GetVertexChiSqrFit(),wgt_minerva_v1);
                }

                else if (kShort==trackType){
                  h_Efficiency_h_CryoVertexChiSqFit_short[1]->Fill(universe->GetVertexChiSqrFit(),wgt_minerva_v1);
                  h_Efficiency_h_CryoVertexChiSqFit_short[2]->Fill(universe->GetVertexChiSqrFit(),wgt_minerva_v1);

                }
                else if(kOtherLong==trackType) {
                  h_Efficiency_h_CryoVertexChiSqFit_otherlong[1]->Fill(universe->GetVertexChiSqrFit(),wgt_minerva_v1);
                  h_Efficiency_h_CryoVertexChiSqFit_otherlong[2]->Fill(universe->GetVertexChiSqrFit(),wgt_minerva_v1);
                }


                }



              if(universe->GetVertexChiSqrFit() > greatest_Chisqrt){greatest_Chisqrt =universe->GetVertexChiSqrFit(); }

            }//END of RECO CUTs for CV

            ///////////////////////////////////////////
            ////
            ////  END OF CV
            ////
            ///////////////////////////////////////////

            double weight_forMK = 1.0; //universe->GetWeight(kWeights_forMK);
            double MK_Weight = universe->GetMKmodelWeight_local(weight_MK);

            h_MuonE.univHist(universe)->Fill(universe->GetEmu()*.001,wgt_minerva_v1);
            h_MuonPZ.univHist(universe)->Fill(Pmu*std::cos(Theta),wgt_minerva_v1);
            h_MuonPT.univHist(universe)->Fill(Pmu*std::sin(Theta),wgt_minerva_v1);
            h_MuonTheta.univHist(universe)->Fill(Theta*TMath::RadToDeg(),wgt_minerva_v1);
            h_Muon_pseudorapidity.univHist(universe)->Fill(pseduo_r, wgt_minerva_v1);
            h_Muon_pseudorapidity_angle.univHist(universe)->Fill(pseduo_theta, wgt_minerva_v1);
            h_Muon_rapidity.univHist(universe)->Fill(universe->rapidity_muon(),wgt_minerva_v1);

          //std::cout<< "pseudorapidity_muon() = "<< universe->pseudorapidity_muon()<<std::endl;

          //std::cout<< "pseudorapidity_muon() angle = "<< pseduo_theta*TMath::RadToDeg()<<std::endl;

          ///std::cout<< "universe->rapidity_muon() = "<< universe->rapidity_muon()<<std::endl;

            //h_MuonE.univHist(universe)->Fill(universe->GetMuonE_ECT(),wgt_minerva_v1);

            //h_MuonPZ.univHist(universe)->Fill(universe->GetMuonPz_ECT(),wgt_minerva_v1);

            //h_MuonPT.univHist(universe)->Fill(universe->GetMuonPt_ECT(),wgt_minerva_v1);

            //h_MuonTheta.univHist(universe)->Fill(universe->GetmuAngleWRTB_Degs(),wgt_minerva_v1);

            h_MuonE_Fake.univHist(universe)->Fill(universe->GetMuonE_ECT(),universe->GetWeight(kWeights_v2tune));

            h_MuonPZ_Fake.univHist(universe)->Fill(universe->GetMuonPz_ECT(),universe->GetWeight(kWeights_v2tune));

            h_MuonPT_Fake.univHist(universe)->Fill(universe->GetMuonPt_ECT(),universe->GetWeight(kWeights_v2tune));

            h_MuonTheta_Fake.univHist(universe)->Fill(universe->GetmuAngleWRTB_Degs(),MK_Weight * universe->GetWeight(kWeights_v2tune));

            h_MuonE_Fake2.univHist(universe)->Fill(universe->GetMuonE_ECT(),MK_Weight*weight_forMK);

            h_MuonPZ_Fake2.univHist(universe)->Fill(universe->GetMuonPz_ECT(),MK_Weight*weight_forMK);

            h_MuonPT_Fake2.univHist(universe)->Fill(universe->GetMuonPt_ECT(),MK_Weight*weight_forMK);

            h_MuonTheta_Fake2.univHist(universe)->Fill(universe->GetmuAngleWRTB_Degs(),MK_Weight*weight_forMK);


            h_MuonPhi.univHist(universe)->Fill(universe->GetmuAngleWRTB_Degs(),wgt_minerva_v1);

            h_MuonDOCA.univHist(universe)->Fill(universe->GetDOCAmu(),wgt_minerva_v1);

            h_MuonCharge.univHist(universe)->Fill(universe->GetChargemu(),wgt_minerva_v1);

            h_MuonCurvatureSig.univHist(universe)->Fill(universe->GetCurvatureSignificance(),wgt_minerva_v1);

            h_muon_MINOS_E.univHist(universe)->Fill(universe->GetMINOS_Energy(),wgt_minerva_v1);

            h_muon_minosStart_X.univHist(universe)->Fill(universe->GetMINOSStart_X(),wgt_minerva_v1);

            h_muon_minosStart_Y.univHist(universe)->Fill(universe->GetMINOSStart_Y(),wgt_minerva_v1);

            h_muon_minosStart_Z.univHist(universe)->Fill(universe->GetMINOSStart_Z(),wgt_minerva_v1);

            h_muon_minosEnd_X.univHist(universe)->Fill(universe->GetMINOSEnd_X(),wgt_minerva_v1);

            h_muon_minosEnd_Y.univHist(universe)->Fill(universe->GetMINOSEnd_Y(),wgt_minerva_v1);

            h_muon_minosEnd_Z.univHist(universe)->Fill(universe->GetMINOSEnd_Z(),wgt_minerva_v1);

            h_muon_StartNode_X.univHist(universe)->Fill(universe->GetMuon_firstNode_X(),wgt_minerva_v1);
            h_muon_StartNode_Y.univHist(universe)->Fill(universe->GetMuon_firstNode_Y(),wgt_minerva_v1);
            h_muon_StartNode_Z.univHist(universe)->Fill(universe->GetMuon_firstNode_Z(),wgt_minerva_v1);

            h_muon_LastNode_X.univHist(universe)->Fill(universe->GetMuon_lastNode_X(),wgt_minerva_v1);
            h_muon_LastNode_Y.univHist(universe)->Fill(universe->GetMuon_lastNode_Y(),wgt_minerva_v1);
            h_muon_LastNode_Z.univHist(universe)->Fill(universe->GetMuon_lastNode_Z(),wgt_minerva_v1);

            //Vertex varibles

            h_CryoVertex_X.univHist(universe)->Fill(universe->GetVertex_x(),wgt_minerva_v1);

            h_CryoVertex_Y.univHist(universe)->Fill(universe->GetVertex_y(),wgt_minerva_v1);

            h_CryoVertex_Z.univHist(universe)->Fill(universe->GetVertex_z(),wgt_minerva_v1);

            h_CryoVertex_R.univHist(universe)->Fill(universe->GetVertex_r(),wgt_minerva_v1);

            h_CryoVertexChiSqFit.univHist(universe)->Fill(universe->GetVertexChiSqrFit(),wgt_minerva_v1);

            h_VetoWall_matchToVeto.univHist(universe)->Fill(universe->GetMatchToVeto(),wgt_minerva_v1);

            h_VetoWall_NumbermatchToVeto.univHist(universe)->Fill(universe->GetNumberMatchToVeto(),wgt_minerva_v1);

            h_VetoWall_vetoSixPush.univHist(universe)->Fill(universe->GetSixPush(),wgt_minerva_v1);

            h_VetoWall_extrapnowalls.univHist(universe)->Fill(universe->Getextrapnowalls(),wgt_minerva_v1);

            h_VetoWall_extrapwall1.univHist(universe)->Fill(universe->Getextrapwall1(),wgt_minerva_v1);

            h_VetoWall_extrapwall2.univHist(universe)->Fill(universe->Getextrapwall2(),wgt_minerva_v1);

            h_VetoWall_extrapbothwalls.univHist(universe)->Fill(universe->Getextrapbothwalls() ,wgt_minerva_v1);

            h_VetoWall_MuonTrkMatchToVETOwalloff.univHist(universe)->Fill(universe->GetMuonTrkMatchToVETOwalloff(),wgt_minerva_v1);

            auto PMTMap_vector=universe->GetVector_PMTVeto_Map();
            double pmt_count = 1;
            for(auto cat : PMTMap_vector ){
              if(cat == 1)h_VetoWall_PMTmap_ON.univHist(universe)->Fill(pmt_count, wgt_minerva_v1);
              if(cat == -1)h_VetoWall_PMTmap_OFF.univHist(universe)->Fill(pmt_count, wgt_minerva_v1);
              pmt_count++;
            }


            h_Tracksize.univHist(universe)->Fill(universe->GetTracksize(),wgt_minerva_v1);

            h_secTrk_FirstNodeX.univHist(universe)->Fill(universe->GetFirstNodeX(secondTrk),wgt_minerva_v1);
            h_secTrk_FirstNodeY.univHist(universe)->Fill(universe->GetFirstNodeY(secondTrk),wgt_minerva_v1);
            h_secTrk_FirstNodeZ.univHist(universe)->Fill(universe->GetFirstNodeZ(secondTrk),wgt_minerva_v1);

            h_secTrk_LastNodeX.univHist(universe)->Fill(universe->GetLastNodeX(secondTrk),wgt_minerva_v1);
            h_secTrk_LastNodeY.univHist(universe)->Fill(universe->GetLastNodeY(secondTrk),wgt_minerva_v1);
            h_secTrk_LastNodeZ.univHist(universe)->Fill(universe->GetLastNodeZ(secondTrk),wgt_minerva_v1);



            // Fill the MnvH1D's universe's histogram
            //int secondTrk = universe->Getindex2ndTrackhighestKE();
            h_secTrk_Energy.univHist(universe)->Fill(universe->GetNonmuTrkE_GeV(secondTrk),wgt_minerva_v1);
            h_secTrk_MidTheta.univHist(universe)->Fill(universe->GetNonmuTrkAngleWRTbeamMID(secondTrk),wgt_minerva_v1);
            h_secTrk_Openangle.univHist(universe)->Fill(universe->GetNonmuTrkAngleWRTmu(secondTrk),wgt_minerva_v1);

            h_secTrk_DOCA.univHist(universe)->Fill(universe->GetNonmuDOCA(secondTrk),wgt_minerva_v1);
            h_secTrk_Pathlength.univHist(universe)->Fill(universe->GetNonmuTrkLength(secondTrk),wgt_minerva_v1);
            h_secTrk_tracklength.univHist(universe)->Fill(universe->GetNonmuTrkLength_InMinerva_Incm(secondTrk) ,wgt_minerva_v1);

            auto tracktype = universe->GetTrackType();

            if (tracktype==kShort) {
            h_secTrk_tracklength_shorttracker.univHist(universe)->Fill(universe->GetNonmuTrkLength_InMinerva_Incm(secondTrk),wgt_minerva_v1);

            }
            else if (tracktype==kLong) {
            h_secTrk_tracklength_longtracker.univHist(universe)->Fill(universe->GetNonmuTrkLength_InMinerva_Incm(secondTrk),wgt_minerva_v1);
            }
            else if (tracktype==kOtherLong) {
              h_secTrk_tracklength_otherlongtracker.univHist(universe)->Fill(universe->GetNonmuTrkLength_InMinerva_Incm(secondTrk),wgt_minerva_v1);
            }

          }// End ALL Universe BANDS loop

        } // END of RECO Cuts

        ///////////////////////////////////////////
        ////
        ////  Apply TRUTH + RECO CUTS to each universe
        ////
        ///////////////////////////////////////////

        if(PassesCutsTRUTH(*Universe_GROUP.front(), kTRUTHCutsVector, kWeights_v1tune , Truth_Cut_Map)){
          // TRUTH ONLY Cuts
          for (auto universe : Universe_GROUP){
            universe->SetEntry(ii);
            h_CryoVertexChiSqFit_TRUE.univHist(universe)->Fill(universe->GetVertexChiSqrFit(), universe->GetWeight(kWeights_v1tune));
          }

          if(PassesCutsRECO(*Universe_GROUP.front(),  is_mc , kCutsVector_Eff ,kWeights_v1tune ,CountMap_TRUE_RECO ) ){

            for (auto universe : Universe_GROUP){
              //std::cout<<"universe->ShortName() = " << universe->ShortName()<<std::endl;
            // Tell the Event which entry in the TChain it's looking at
            universe->SetEntry(ii);

            auto PDG_trklist = universe->GetVector_nonMuonTk_PDG_Parent();
            auto Energy_trklist = universe-> GetVector_nonMuonTk_Energy_GeV_Parent();
            auto Angle_trklist = universe->GetVector_nonMuonTk_Angle_wrtb_Degs_Parent();
            auto EnergyFraction_vector = universe->Get_TrueFractionE_vector();
           //int secondTrk = universe->Getindex2ndTrackhighestKE();

            int secondTrk = universe->Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_lessthanAngle_muonNotinlist(PDG_trklist, Energy_trklist, Angle_trklist, EnergyFraction_vector);
            if(secondTrk==-999)continue;

            double secTrkTrueEnergy = Energy_trklist.at(secondTrk);
            double wgt_minerva_v1 = universe->GetWeight(kWeights_v1tune);

            int secTrk_PDG = PDG_trklist.at(secondTrk);
            double secTrkAngle  = Angle_trklist.at(secondTrk);
            double secTrkTrueAngle = universe->GetTRUE_NonmuTrkANGLE_WRTB(secondTrk);
            double Theta = universe->GetThetamu();
            double Pmu = universe -> GetPmu()/1000;


            //double secTrk_track_length = True_track_lenght_minerva.at(secondTrk);
          //  int secondTrk = universe->Getindex2ndTrackhighestKE();
          //  int secTrk_PDG = universe->GetPDG_2ndTrk_highestTRUEEnergy();

          //  double secTrkTrueEnergy = universe->GetTRUENonmuTrkE(secondTrk);
            //Particle_type Particle_type_Event =  universe->Get_NonParticleStackType(secondTrk);
            Particle_type GroupType = GetParticlegroup_type(secTrk_PDG);

        if(isCV(*universe)){

          //int secondTrk_true = universe->Getindex2ndTrack_TRUE_highestKE();
          //auto input_type =  universe->GetNon_muon_PDG(secondTrk_true);
          //auto PDG_trklist = universe->GetVector_nonMuonTk_PDG();
          //auto Energy_trklist = universe-> GetVector_nonMuonTk_Energy_GeV();

          //auto PDG_trklist = universe->GetVector_nonMuonTk_PDG_Parent();
          //auto Energy_trklist = universe-> GetVector_nonMuonTk_Energy_GeV_Parent();
          //auto Angle_trklist = universe->GetVector_nonMuonTk_Angle_wrtb_Degs_Parent();

          int index_trajector = universe->getindexTrueTrajectors_closestRECO();
          int pdg_trajector = universe->Get_index_Trajector_PDG(index_trajector);
          auto EnergyFraction_vector = universe->Get_TrueFractionE_vector();

          //int secondTrk = universe->Getindex2ndTrackhighestKE();
          //unsigned int secondTrk = universe->Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_lessthanAngle_muonNotinlist(PDG_trklist, Energy_trklist, Angle_trklist, EnergyFraction_vector);


          //unsigned int secondTrk = universe-> Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_lessthanAngle_muonNotinlist_KE_proton_pion_thrusthold(PDG_trklist, Energy_trklist, Angle_trklist, EnergyFraction_vector);
          if(secondTrk==-999 || secondTrk== -9999 )continue;
          // Turned off Energy function



          Particle_type Particle_type_Event = GetParticlegroup_type(secTrk_PDG);
          Interaction_type Interaction_type_Event =  universe->Get_InteractionStackType();
          Material_type Material_type_Event = universe->Get_MaterialStackType();

          int run = universe->GetRunN();
          int subrun = universe->GetSubRunN();
          int gate = universe->GetGateN();
          int slice  = universe->GetSliceN();

          // secondTrk = universe->Getindex2ndTrackhighestKE();
          //    int secTrk_PDG = universe->GetPDG_2ndTrk_highestTRUEEnergy();
          //double secTrkAngle = universe->GetTRUE_NonmuTrkANGLE_WRTB(secondTrk);
          //  double secTrkKE = universe->GetTRUENonmuTrkE(secondTrk);
          //  Particle_type Particle_type_Event =  universe->Get_NonParticleStackType(secondTrk);

          //auto PDG_trklist = universe->GetVector_nonMuonTk_PDG();
          int True_tracksize = PDG_trklist.size();


          //Particle_type Particle_type_Event = GetParticlegroup_type(secTrk_PDG);


          for(unsigned int i = 0; i != PDG_trklist.size(); ++i ){
            auto leadinggrounptype = GetParticlegroup_typeProtonandpion_other(PDG_trklist.at(i));
            if(i==secondTrk){
              h_secTrk_MidTheta_leading_Particle.GetComponentHist(leadinggrounptype)->Fill(universe->GetTRUE_NonmuTrkANGLE_WRTB(i), wgt_minerva_v1);
            }
            else{
              h_secTrk_MidTheta_Nonleading_Particle.GetComponentHist(leadinggrounptype)->Fill(universe->GetTRUE_NonmuTrkANGLE_WRTB(i), wgt_minerva_v1);

            }
          }

          ///////////////
          if(secTrkAngle > 70){arachneHigh_angle.push_back({run,subrun,gate,slice,secTrkAngle,secTrkTrueEnergy,secTrk_PDG});}
          if(secTrkTrueEnergy < .120){arachneLow_KE.push_back({run,subrun,gate,slice,secTrkAngle,secTrkTrueEnergy,secTrk_PDG});}

          h_2d_Track_Fraction_Energy_Second->Fill(secondTrk,EnergyFraction_vector.at(secondTrk),wgt_minerva_v1);
          //EnergyFraction_vector.at(secondTrk) > .6 && EnergyFraction_vector.at(secondTrk) < .8
          //if ((secTrkAngle > 45 || secTrkAngle < 0 ) && secTrkTrueEnergy < .120 && Study_count < Study_cap){
          double TrackLength = universe->GetNonmuTrkLength_InMinerva_Incm(secondTrk);

          //  if ( TrackLength < 100 && TrackLength > 25 && universe->GetTracksize()==3 && Study_count < Study_cap){
          /*
  if ( ){
    auto Trajectors_event = universe->GetVector_ALLTrajector();
    //auto Trajector_RecoEvent = universe->GetVector_ALLTrajector_ForWithRecoTracks();
    auto Trajector_RecoEvent = universe->GetVector_ALLTrajector_ForWithRecoTracks_withTrueEFraction();
    auto Trajector_Energies = universe->TRUE_RECO_Energies_TrajectorsStuct();
    auto Trajector_RecoEvent_Parent = universe->GetVector_ALLTrajector_ForWithRecoTracks_withTrueEFraction_Parent();
    auto Trajector_Energies_Parent = universe->TRUE_RECO_Energies_TrajectorsStuct_Parent();


    bool is_counter = true;
    All_True_trajectors.push_back(Trajectors_event);
    All_RECO_trajectors.push_back(Trajector_RecoEvent);
    True_Reco_Energies.push_back(Trajector_Energies);
    All_RECO_trajectors_Parent.push_back(Trajector_RecoEvent_Parent);
    True_Reco_Energies_Parent.push_back(Trajector_Energies_Parent);


    //vector<int>PDG_trklist = universe->GetVector_nonMuonTk_PDG();
    //vector <double> Angle_trklist = universe->GetVector_nonMuonTk_Angle_wrtb_Degs();
    //vector <double> Energy_trklist = universe->GetVector_nonMuonTk_Energy_GeV();
    //int NTrks = PDG_trklist.size();

    std::vector <int> PDG_trklist = universe->GETvector_PDG_FS_particles();
    std::vector  <double> Angle_trklist = universe->GETvector_theta_wrtb_FS_particles();
    std::vector  <double> Energy_trklist =  universe->GETvector_Energy_mc_FS_particles_MeVtoGeV();
    int NTrks = PDG_trklist.size();
    Arachne_alltrks.push_back({run, subrun,gate, slice,NTrks, PDG_trklist, Angle_trklist, Energy_trklist});

    arachneBoth.push_back({run,subrun,gate,slice,secTrkAngle,secTrkTrueEnergy,secTrk_PDG});



    h_2d_PZ_PT_LOWANGLE_TRUE_RECO->Fill(universe->GetPmuLongitudinalTrue(),universe->GetPmuTransverseTrue(),wgt_minerva_v1);
    h_2d_E_PZ_LOWANGLE_TRUE_RECO->Fill(universe->GetTRUE_Emu(),universe->GetPmuLongitudinalTrue(),wgt_minerva_v1);
    h_2d_Theta_PZ_LOWANGLE_TRUE_RECO->Fill(universe->GetTRUE_muANGLE_WRTB_DEG(),universe->GetPmuLongitudinalTrue(),wgt_minerva_v1);
    h_2d_Theta_PT_LOWANGLE_TRUE_RECO->Fill(universe->GetTRUE_muANGLE_WRTB_DEG(),universe->GetPmuTransverseTrue(),wgt_minerva_v1);
    h_2d_E_PT_LOWANGLE_TRUE_RECO->Fill(universe->GetTRUE_Emu(),universe->GetPmuTransverseTrue(),wgt_minerva_v1);
    h_2d_Theta_PZ_LOWANGLE_TRUE_RECO->Fill(universe->GetTRUE_muANGLE_WRTB_DEG(),universe->GetPmuLongitudinalTrue(),wgt_minerva_v1);
    h_2d_Theta_2ndTrkE_LOWANGLE_TRUE_RECO->Fill(universe->GetTRUE_muANGLE_WRTB_DEG(),universe->GetTRUENonmuTrkE(secondTrk),wgt_minerva_v1);
    h_2d_muonE_2ndTrkE_LOWANGLE_TRUE_RECO->Fill(universe->GetTRUE_Emu(),universe->GetTRUENonmuTrkE(secondTrk),wgt_minerva_v1);
    h_2d_muonPT_2ndTrkE_LOWANGLE_TRUE_RECO->Fill(universe->GetPmuTransverseTrue(),universe->GetTRUENonmuTrkE(secondTrk),wgt_minerva_v1);
    h_2d_muonPZ_2ndTrkE_LOWANGLE_TRUE_RECO->Fill(universe->GetPmuLongitudinalTrue(),universe->GetTRUENonmuTrkE(secondTrk),wgt_minerva_v1);
    h_2d_Theta_2ndTrKangle_LOWANGLE_TRUE_RECO->Fill(universe->GetTRUE_muANGLE_WRTB_DEG(),universe->GetTRUE_NonmuTrkANGLE_WRTB(secondTrk),wgt_minerva_v1);
    h_2d_muonE_2ndTrkangle_LOWANGLE_TRUE_RECO->Fill(universe->GetTRUE_Emu(),universe->GetTRUE_NonmuTrkANGLE_WRTB(secondTrk),wgt_minerva_v1);
    h_2d_muonPT_2ndTrkangle_LOWANGLE_TRUE_RECO->Fill(universe->GetPmuTransverseTrue(),universe->GetTRUE_NonmuTrkANGLE_WRTB(secondTrk),wgt_minerva_v1);
    h_2d_muonPZ_2ndTrkangle_LOWANGLE_TRUE_RECO->Fill(universe->GetPmuLongitudinalTrue(),universe->GetTRUE_NonmuTrkANGLE_WRTB(secondTrk),wgt_minerva_v1);
    h_2d_2ndtrkangle_2ndTrkE_LOWANGLE_TRUE_RECO->Fill(universe->GetTRUE_NonmuTrkANGLE_WRTB(secondTrk),universe->GetTRUENonmuTrkE(secondTrk),wgt_minerva_v1);

    h_secTrk_Theta_TRUE_RECO_LOWANGLE_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetTRUE_NonmuTrkANGLE_WRTB(secondTrk), wgt_minerva_v1);
    h_secTrk_Theta_TRUE_RECO_LOWANGLE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetTRUE_NonmuTrkANGLE_WRTB(secondTrk), wgt_minerva_v1);
    h_secTrk_Theta_TRUE_RECO_LOWANGLE_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetTRUE_NonmuTrkANGLE_WRTB(secondTrk), wgt_minerva_v1);

    Study_count++;
  }
  */
          h_MuonE_TRUE_RECO_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetEmu()*.001, wgt_minerva_v1);
          h_MuonE_TRUE_RECO_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetEmu()*.001, wgt_minerva_v1);
          h_MuonE_TRUE_RECO_Particle.GetComponentHist(Particle_type_Event,false)->Fill(universe->GetEmu()*.001, wgt_minerva_v1);


          h_secTrk_Openangle_TRUE_RECO_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetOpenAngle(secondTrk), wgt_minerva_v1);
          h_secTrk_Openangle_TRUE_RECO_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetOpenAngle(secondTrk), wgt_minerva_v1);
          h_secTrk_Openangle_TRUE_RECO_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetOpenAngle(secondTrk), wgt_minerva_v1);

          h_secTrk_Theta_TRUE_RECO_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetTRUE_NonmuTrkANGLE_WRTB(secondTrk), wgt_minerva_v1);
          h_secTrk_Theta_TRUE_RECO_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetTRUE_NonmuTrkANGLE_WRTB(secondTrk), wgt_minerva_v1);
          h_secTrk_Theta_TRUE_RECO_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetTRUE_NonmuTrkANGLE_WRTB(secondTrk), wgt_minerva_v1);

          h_secTrk_Energy_TRUE_RECO_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetTRUE_NonmuTrkE(secondTrk), wgt_minerva_v1);
          h_secTrk_Energy_TRUE_RECO_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetTRUE_NonmuTrkE(secondTrk), wgt_minerva_v1);
          h_secTrk_Energy_TRUE_RECO_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetTRUE_NonmuTrkE(secondTrk), wgt_minerva_v1);

          h_secTrk_DOCA_TRUE_RECO_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetTRUE_nonMuonDOCA(secondTrk), wgt_minerva_v1);
          h_secTrk_DOCA_TRUE_RECO_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetTRUE_nonMuonDOCA(secondTrk), wgt_minerva_v1);
          h_secTrk_DOCA_TRUE_RECO_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetTRUE_nonMuonDOCA(secondTrk), wgt_minerva_v1);

          h_secTrk_Pathlength_TRUE_RECO_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetTRUE_nonMuoncolumnarDensity(secondTrk), wgt_minerva_v1);
          h_secTrk_Pathlength_TRUE_RECO_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetTRUE_nonMuoncolumnarDensity(secondTrk), wgt_minerva_v1);
          h_secTrk_Pathlength_TRUE_RECO_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetTRUE_nonMuoncolumnarDensity(secondTrk), wgt_minerva_v1);

          auto PMTMap_vector=universe->GetVector_PMTVeto_Map();
          double pmt_count = 1;
          for(auto cat : PMTMap_vector ){
            if(cat ==1)h_Veto_PMT_Map.GetComponentHist(kPMTON)->Fill(pmt_count, wgt_minerva_v1);
            if(cat == -1)h_Veto_PMT_Map.GetComponentHist(kPMTOFF)->Fill(pmt_count, wgt_minerva_v1);
            pmt_count++;
          }




          if(GroupType== kParticle_N_A){
            h_Particle_N_A_secTrk_Theta_TRUE_RECO_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetTRUE_NonmuTrkANGLE_WRTB(secondTrk), wgt_minerva_v1);
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


          h_2d_PZ_PT_TRUE_RECO->Fill(universe->GetPmuLongitudinalTrue(),universe->GetPmuTransverseTrue(),wgt_minerva_v1);
          h_2d_E_PZ_TRUE_RECO->Fill(universe->GetTRUE_Emu(),universe->GetPmuLongitudinalTrue(),wgt_minerva_v1);
          h_2d_Theta_PZ_TRUE_RECO->Fill(universe->GetTRUE_muANGLE_WRTB_DEG(),universe->GetPmuLongitudinalTrue(),wgt_minerva_v1);
          h_2d_Theta_PT_TRUE_RECO->Fill(universe->GetTRUE_muANGLE_WRTB_DEG(),universe->GetPmuTransverseTrue(),wgt_minerva_v1);
          h_2d_E_PT_TRUE_RECO->Fill(universe->GetTRUE_Emu(),universe->GetPmuTransverseTrue(),wgt_minerva_v1);

          h_2d_Theta_2ndTrkE_TRUE_RECO->Fill(universe->GetTRUE_muANGLE_WRTB_DEG(),universe->GetTRUENonmuTrkE(secondTrk),wgt_minerva_v1);
          h_2d_muonE_2ndTrkE_TRUE_RECO->Fill(universe->GetTRUE_Emu(),universe->GetTRUENonmuTrkE(secondTrk),wgt_minerva_v1);
          h_2d_muonPT_2ndTrkE_TRUE_RECO->Fill(universe->GetPmuTransverseTrue(),universe->GetTRUENonmuTrkE(secondTrk),wgt_minerva_v1);
          h_2d_muonPZ_2ndTrkE_TRUE_RECO->Fill(universe->GetPmuLongitudinalTrue(),universe->GetTRUENonmuTrkE(secondTrk),wgt_minerva_v1);
          h_2d_Theta_2ndTrKangle_TRUE_RECO->Fill(universe->GetTRUE_muANGLE_WRTB_DEG(),universe->GetTRUENonmuTrkE(secondTrk),wgt_minerva_v1);
          h_2d_muonE_2ndTrkangle_TRUE_RECO->Fill(universe->GetTRUE_Emu(),universe->GetTRUE_NonmuTrkANGLE_WRTB(secondTrk),wgt_minerva_v1);
          h_2d_muonPT_2ndTrkangle_TRUE_RECO->Fill(universe->GetPmuTransverseTrue(),universe->GetTRUE_NonmuTrkANGLE_WRTB(secondTrk),wgt_minerva_v1);
          h_2d_muonPZ_2ndTrkangle_TRUE_RECO->Fill(universe->GetPmuLongitudinalTrue(),universe->GetTRUE_NonmuTrkANGLE_WRTB(secondTrk),wgt_minerva_v1);
          h_2d_2ndtrkangle_2ndTrkE_TRUE_RECO->Fill(universe->GetTRUE_NonmuTrkANGLE_WRTB(secondTrk),universe->GetTRUENonmuTrkE(secondTrk),wgt_minerva_v1);

          h_Mig_MuonE->Fill(universe->GetEmu()*.001,universe->GetTRUE_Emu(),wgt_minerva_v1);
          h_Mig_MuonPZ->Fill(Pmu*std::cos(Theta),universe->GetPmuLongitudinalTrue(),wgt_minerva_v1);
          h_Mig_MuonPT->Fill(Pmu*std::sin(Theta),universe->GetPmuTransverseTrue(),wgt_minerva_v1);
          h_Mig_MuonTheta->Fill(Theta*toDegs,universe->GetTRUE_muANGLE_WRTB_DEG(),wgt_minerva_v1);

          h_Mig_Vertex_X->Fill(universe->GetVertex_x(),universe->GetTRUE_Vertex_x(),wgt_minerva_v1);
          h_Mig_Vertex_Y->Fill(universe->GetVertex_y(),universe->GetTRUE_Vertex_y(),wgt_minerva_v1);
          h_Mig_Vertex_R->Fill(universe->GetVertex_r(),universe->GetTRUE_Vertex_r(),wgt_minerva_v1);
          h_Mig_Vertex_Z->Fill(universe->GetVertex_z(),universe->GetTRUE_Vertex_z(),wgt_minerva_v1);



          h_2d_2ndtrkPathlength_2ndTrkE_TRUE_RECO->Fill(universe->GetTRUE_nonMuoncolumnarDensity(secondTrk),universe->GetTRUENonmuTrkE(secondTrk),wgt_minerva_v1);
          h_2d_2ndtrkPathlength_2ndtrkangle_TRUE_RECO->Fill(universe->GetTRUE_nonMuoncolumnarDensity(secondTrk),universe->GetTRUE_NonmuTrkANGLE_WRTB(secondTrk),wgt_minerva_v1);

          //Old method GetTRUE_PTmu()
          if(GroupType==kSecondary_particle_vector[0]){
            h_2d_2ndtrkangle_2ndTrkE_Proton_TRUE_RECO->Fill(universe->GetTRUE_NonmuTrkANGLE_WRTB(secondTrk),universe->GetTRUENonmuTrkE(secondTrk),wgt_minerva_v1);
            h_2d_Theta_2ndTrkE_Proton_TRUE_RECO->Fill(universe->GetTRUE_muANGLE_WRTB_DEG(),universe->GetTRUENonmuTrkE(secondTrk),wgt_minerva_v1);
            h_2d_muonE_2ndTrkE_Proton_TRUE_RECO->Fill(universe->GetTRUE_Emu(),universe->GetTRUENonmuTrkE(secondTrk),wgt_minerva_v1);
            h_2d_muonPT_2ndTrkE_Proton_TRUE_RECO->Fill(universe->GetPmuTransverseTrue(),universe->GetTRUENonmuTrkE(secondTrk),wgt_minerva_v1);
            h_2d_muonPZ_2ndTrkE_Proton_TRUE_RECO->Fill(universe->GetPmuLongitudinalTrue(),universe->GetTRUENonmuTrkE(secondTrk),wgt_minerva_v1);
            h_2d_2ndtrkPathlength_2ndTrkE_Proton_TRUE_RECO->Fill(universe->GetTRUE_nonMuoncolumnarDensity(secondTrk),universe->GetTRUENonmuTrkE(secondTrk),wgt_minerva_v1);
            h_2d_2ndtrkPathlength_2ndtrkangle_Proton_TRUE_RECO->Fill(universe->GetTRUE_nonMuoncolumnarDensity(secondTrk),universe->GetTRUE_NonmuTrkANGLE_WRTB(secondTrk),wgt_minerva_v1);
          }

          if(GroupType==kSecondary_particle_vector[3]||GroupType==kSecondary_particle_vector[4]){
            h_2d_2ndtrkangle_2ndTrkE_Pion_TRUE_RECO ->Fill(universe->GetTRUE_NonmuTrkANGLE_WRTB(secondTrk),universe->GetTRUENonmuTrkE(secondTrk),wgt_minerva_v1);
            h_2d_Theta_2ndTrkE_Pion_TRUE_RECO->Fill(universe->GetTRUE_muANGLE_WRTB_DEG(),universe->GetTRUENonmuTrkE(secondTrk),wgt_minerva_v1);
            h_2d_muonE_2ndTrkE_Pion_TRUE_RECO->Fill(universe->GetTRUE_Emu(),universe->GetTRUENonmuTrkE(secondTrk),wgt_minerva_v1);
            h_2d_muonPT_2ndTrkE_Pion_TRUE_RECO->Fill(universe->GetPmuTransverseTrue(),universe->GetTRUENonmuTrkE(secondTrk),wgt_minerva_v1);
            h_2d_muonPZ_2ndTrkE_Pion_TRUE_RECO->Fill(universe->GetPmuLongitudinalTrue(),universe->GetTRUENonmuTrkE(secondTrk),wgt_minerva_v1);
            h_2d_2ndtrkPathlength_2ndTrkE_Pion_TRUE_RECO->Fill(universe->GetTRUE_nonMuoncolumnarDensity(secondTrk),universe->GetTRUENonmuTrkE(secondTrk),wgt_minerva_v1);
            h_2d_2ndtrkPathlength_2ndtrkangle_Pion_TRUE_RECO->Fill(universe->GetTRUE_nonMuoncolumnarDensity(secondTrk),universe->GetTRUE_NonmuTrkANGLE_WRTB(secondTrk),wgt_minerva_v1);

          }

          if(GroupType==kSecondary_particle_vector[1]){
            //h_2d_2ndtrkangle_2ndTrkE_dimuon_TRUE_RECO->Fill(universe->GetTRUE_NonmuTrkANGLE_WRTB(secondTrk),universe->GetTRUENonmuTrkE(secondTrk),wgt_minerva_v1);
          }

        } // END OF CV
        ///////////////////////////////////////////
        ////
        ////  END OF CV For TRUTH + RECO cuts
        ////
        ///////////////////////////////////////////





        //  if(GroupType ==kSecondary_particle_vector[0] && secTrkTrueEnergy < .115 ) continue;
        //if((GroupType==kSecondary_particle_vector[3]||GroupType==kSecondary_particle_vector[4]) && secTrkTrueEnergy < .75 ) continue;

        int True_tracksize = PDG_trklist.size();

        //std::cout<<"inside Loop True 2nd Trk E = "<<secTrkTrueEnergy<< std::endl;


        h_MuonE_TRUE_RECO.univHist(universe)->Fill(universe->GetTRUE_Emu(),wgt_minerva_v1);

        h_MuonPZ_TRUE_RECO.univHist(universe)->Fill(universe->GetPmuLongitudinalTrue(),wgt_minerva_v1);

        h_MuonPT_TRUE_RECO.univHist(universe)->Fill(universe->GetPmuTransverseTrue(),wgt_minerva_v1);

        h_MuonTheta_TRUE_RECO.univHist(universe)->Fill(universe->GetTRUE_muANGLE_WRTB_DEG(),wgt_minerva_v1);

        h_MuonDOCA_TRUE_RECO.univHist(universe)->Fill(universe->GetDOCAmu(),wgt_minerva_v1);

        h_MuonPhi_TRUE_RECO.univHist(universe)->Fill(universe->GetTRUE_Phimu(),wgt_minerva_v1);

        h_CryoVertex_X_TRUE_RECO.univHist(universe)->Fill(universe->GetTRUE_Vertex_x(),wgt_minerva_v1);

        h_CryoVertex_Y_TRUE_RECO.univHist(universe)->Fill(universe->GetTRUE_Vertex_y(),wgt_minerva_v1);

        h_CryoVertex_Z_TRUE_RECO.univHist(universe)->Fill(universe->GetTRUE_Vertex_z(),wgt_minerva_v1);

        h_CryoVertex_R_TRUE_RECO.univHist(universe)->Fill(universe->GetTRUE_Vertex_r(),wgt_minerva_v1);

        h_CryoVertexChiSqFit_TRUE_RECO.univHist(universe)->Fill(universe->GetVertexChiSqrFit(),wgt_minerva_v1);

        h_secTrk_DOCA_TRUE_RECO.univHist(universe)->Fill(universe->GetTRUE_nonMuonDOCA(secondTrk),wgt_minerva_v1);

        h_secTrk_Pathlength_TRUE_RECO.univHist(universe)->Fill(universe->GetTRUE_nonMuoncolumnarDensity(secondTrk),wgt_minerva_v1);

        h_Tracksize_TRUE_RECO.univHist(universe)->Fill(True_tracksize,wgt_minerva_v1);

        h_Qsquare_TRUE_RECO.univHist(universe)->Fill(universe->GetQ2True_GeV(),wgt_minerva_v1);

        h_secTrk_tracklength_TRUE_RECO.univHist(universe)->Fill(universe->GetNonmuTrkLength_InMinerva_Incm(secondTrk) ,wgt_minerva_v1);
        //  h_secTrk_tracklength_TRUE_TRUE_RECO.univHist(universe)->Fill(secTrk_track_length ,wgt_minerva_v1);


        h_secTrk_Energy_TRUE_RECO.univHist(universe)->Fill(secTrkTrueEnergy,wgt_minerva_v1);
        h_secTrk_EnergyFINEBinning_TRUE_RECO.univHist(universe)->Fill(secTrkTrueEnergy,wgt_minerva_v1);
        h_secTrk_Openangle_TRUE_RECO.univHist(universe)->Fill(universe->GetTRUE_NonmuTrkopenangle(secondTrk),wgt_minerva_v1);
        h_secTrk_Theta_TRUE_RECO.univHist(universe)->Fill(secTrkTrueAngle,wgt_minerva_v1);

        if(GroupType==kSecondary_particle_vector[0]){
          h_secTrk_Energy_PROTON_TRUE_RECO.univHist(universe)->Fill(secTrkTrueEnergy,wgt_minerva_v1);
          h_secTrk_Theta_PROTON_TRUE_RECO.univHist(universe)->Fill(secTrkTrueAngle,wgt_minerva_v1);
          h_secTrk_Openangle_PROTON_TRUE_RECO.univHist(universe)->Fill(universe->GetTRUE_NonmuTrkopenangle(secondTrk),wgt_minerva_v1);
          h_secTrk_Pathlength_PROTON_TRUE_RECO.univHist(universe)->Fill(universe->GetTRUE_nonMuoncolumnarDensity(secondTrk),wgt_minerva_v1);

        }
        if(GroupType==kSecondary_particle_vector[3]||GroupType==kSecondary_particle_vector[4])
        {
          h_secTrk_Energy_PION_TRUE_RECO.univHist(universe)->Fill(secTrkTrueEnergy,wgt_minerva_v1);
          h_secTrk_Theta_PION_TRUE_RECO.univHist(universe)->Fill(secTrkTrueAngle,wgt_minerva_v1);
          h_secTrk_Openangle_PION_TRUE_RECO.univHist(universe)->Fill(universe->GetTRUE_NonmuTrkopenangle(secondTrk),wgt_minerva_v1);
          h_secTrk_Pathlength_PION_TRUE_RECO.univHist(universe)->Fill(universe->GetTRUE_nonMuoncolumnarDensity(secondTrk),wgt_minerva_v1);

        }
        if(GroupType==kSecondary_particle_vector[2])
        {
          h_secTrk_Energy_PION0_TRUE_RECO.univHist(universe)->Fill(secTrkTrueEnergy,wgt_minerva_v1);
          h_secTrk_Theta_PION0_TRUE_RECO.univHist(universe)->Fill(secTrkTrueAngle,wgt_minerva_v1);
          h_secTrk_Openangle_PION0_TRUE_RECO.univHist(universe)->Fill(universe->GetTRUE_NonmuTrkopenangle(secondTrk),wgt_minerva_v1);
        }
        if(GroupType==kSecondary_particle_vector[3]||GroupType==kSecondary_particle_vector[4])
        {
          h_secTrk_Energy_PION_neg_pos_TRUE_RECO.univHist(universe)->Fill(secTrkTrueEnergy,wgt_minerva_v1);
          h_secTrk_Theta_PION_neg_pos_TRUE_RECO.univHist(universe)->Fill(secTrkTrueAngle,wgt_minerva_v1);
          h_secTrk_Openangle_PION_neg_pos_TRUE_RECO.univHist(universe)->Fill(universe->GetTRUE_NonmuTrkopenangle(secondTrk),wgt_minerva_v1);
        }

        if(GroupType==kSecondary_particle_vector[1]){
          h_secTrk_Energy_Dimuon_TRUE_RECO.univHist(universe)->Fill(secTrkTrueEnergy,wgt_minerva_v1);
          h_secTrk_Theta_Dimuon_TRUE_RECO.univHist(universe)->Fill(secTrkTrueAngle,wgt_minerva_v1);
        }

      }// END of Universe Groups

      }// END OF TRUTH + RECO CUTS
    }//END OF TRUTH PASS CUTS





  } // GROUPED universe loop
  ///////////////////////////////////////////
  ////
  ////  GROUPED universe loop
  ////
  ///////////////////////////////////////////
} //End entries loop

///////////////////////////////////////////
////
////  End entries loop
////
///////////////////////////////////////////



  gSystem->GetProcInfo(&procInfo);
  std::cout << " Done with loop Mem1: " << procInfo.fMemResident/1000 << " MB" << " time = "<<  procInfo.fCpuSys  <<  " sec""\n";
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
//EventCountMap[kPlayListVector[0]] = EventCounter_MCFull;
////EventCountMap[kPlayListVector[2]] = EventCounter_dataFull;
//EventCountMap[kPlayListVector[3]] = EventCounter_dataEmpty;
//////////////////////////////////////////////////////////////////////////
//End of Empty data
//////////////////////////////////////////////////////////////////////////


double countdata= 0.0;
double countmc= 0.0;

    h_MuonPZ.SyncCVHistos();
    h_MuonPT.SyncCVHistos();
    h_MuonE.SyncCVHistos();
    h_MuonTheta.SyncCVHistos();
    h_MuonPZ_Fake.SyncCVHistos();
    h_MuonPT_Fake.SyncCVHistos();
    h_MuonE_Fake.SyncCVHistos();
    h_MuonTheta_Fake.SyncCVHistos();
    h_MuonPZ_Fake2.SyncCVHistos();
    h_MuonPT_Fake2.SyncCVHistos();
    h_MuonE_Fake2.SyncCVHistos();
    h_MuonTheta_Fake2.SyncCVHistos();
    h_MuonDOCA.SyncCVHistos();
    h_MuonCurvatureSig.SyncCVHistos();
    h_muon_MINOS_E.SyncCVHistos();
    h_muon_minosStart_X.SyncCVHistos();
    h_muon_minosStart_Y.SyncCVHistos();
    h_muon_minosStart_Z.SyncCVHistos();
    h_muon_minosEnd_X.SyncCVHistos();
    h_muon_minosEnd_Y.SyncCVHistos();
    h_muon_minosEnd_Z.SyncCVHistos();
    h_muon_StartNode_X.SyncCVHistos();
    h_muon_StartNode_Y.SyncCVHistos();
    h_muon_StartNode_Z.SyncCVHistos();
    h_muon_LastNode_X.SyncCVHistos();
    h_muon_LastNode_Y.SyncCVHistos();
    h_muon_LastNode_Z.SyncCVHistos();
    h_secTrk_tracklength.SyncCVHistos();


    h_secTrk_tracklength_shorttracker.SyncCVHistos();
    h_secTrk_tracklength_longtracker.SyncCVHistos();
    h_secTrk_tracklength_otherlongtracker.SyncCVHistos();

    h_Muon_pseudorapidity.SyncCVHistos();
    h_Muon_pseudorapidity_angle.SyncCVHistos();
    h_Muon_rapidity.SyncCVHistos();

    h_MuonPZ_TRUE_RECO.SyncCVHistos();
    h_MuonPT_TRUE_RECO.SyncCVHistos();
    h_MuonE_TRUE_RECO.SyncCVHistos();
    h_MuonTheta_TRUE_RECO.SyncCVHistos();
    h_MuonDOCA_TRUE_RECO.SyncCVHistos();
    h_MuonPhi_TRUE_RECO.SyncCVHistos();
    h_secTrk_tracklength_TRUE_RECO.SyncCVHistos();
    //h_secTrk_tracklength_TRUE_TRUE_RECO.SyncCVHistos();
//////////////////////////////////


    h_CryoVertex_X.SyncCVHistos();
    h_CryoVertex_Y.SyncCVHistos();
    h_CryoVertex_R.SyncCVHistos();
    h_CryoVertex_Z.SyncCVHistos();


    h_CryoVertex_X_TRUE_RECO.SyncCVHistos();
    h_CryoVertex_Y_TRUE_RECO.SyncCVHistos();
    h_CryoVertex_R_TRUE_RECO.SyncCVHistos();
    h_CryoVertex_Z_TRUE_RECO.SyncCVHistos();
    h_Tracksize_TRUE_RECO.SyncCVHistos();
    h_Tracksize.SyncCVHistos();
    //////////////////////////////////
    h_secTrk_Energy.SyncCVHistos();
    h_secTrk_MidTheta.SyncCVHistos();
    h_secTrk_Openangle.SyncCVHistos();
    h_secTrk_DOCA.SyncCVHistos();

    h_secTrk_FirstNodeX.SyncCVHistos();
    h_secTrk_FirstNodeY.SyncCVHistos();
    h_secTrk_FirstNodeZ.SyncCVHistos();
    h_secTrk_LastNodeX.SyncCVHistos();
    h_secTrk_LastNodeY.SyncCVHistos();
    h_secTrk_LastNodeZ.SyncCVHistos();

    h_secTrk_DOCA_TRUE_RECO.SyncCVHistos();
    h_secTrk_Theta_Dimuon_TRUE_RECO.SyncCVHistos();

    h_secTrk_Energy_TRUE_RECO.SyncCVHistos();
    h_secTrk_EnergyFINEBinning_TRUE_RECO.SyncCVHistos();
    h_secTrk_Theta_TRUE_RECO.SyncCVHistos();
    h_secTrk_Openangle_TRUE_RECO.SyncCVHistos();
    h_secTrk_DOCA_TRUE_RECO.SyncCVHistos();

    h_secTrk_Pathlength.SyncCVHistos();
    h_secTrk_Pathlength_TRUE_RECO.SyncCVHistos();
    h_secTrk_Pathlength_PROTON_TRUE_RECO.SyncCVHistos();
    h_secTrk_Pathlength_PION_TRUE_RECO.SyncCVHistos();



    h_secTrk_Energy_Dimuon_TRUE_RECO.SyncCVHistos();
    h_secTrk_Energy_PROTON_TRUE_RECO.SyncCVHistos();
    h_secTrk_Theta_PROTON_TRUE_RECO.SyncCVHistos();
    h_secTrk_Openangle_PROTON_TRUE_RECO.SyncCVHistos();
    h_secTrk_Energy_PION_TRUE_RECO.SyncCVHistos();
    h_secTrk_Theta_PION_TRUE_RECO.SyncCVHistos();
    h_secTrk_Openangle_PION_TRUE_RECO.SyncCVHistos();

    h_secTrk_Energy_PION0_TRUE_RECO.SyncCVHistos();
    h_secTrk_Theta_PION0_TRUE_RECO.SyncCVHistos();
    h_secTrk_Openangle_PION0_TRUE_RECO.SyncCVHistos();

    h_secTrk_Energy_PION_neg_pos_TRUE_RECO.SyncCVHistos();
    h_secTrk_Theta_PION_neg_pos_TRUE_RECO.SyncCVHistos();
    h_secTrk_Openangle_PION_neg_pos_TRUE_RECO.SyncCVHistos();

    h_CryoVertexChiSqFit.SyncCVHistos();
    h_CryoVertexChiSqFit_TRUE_RECO.SyncCVHistos();
    h_CryoVertexChiSqFit_TRUE.SyncCVHistos();
//////////////////////////////////
//////////////////////////////////
    h_VetoWall_matchToVeto.SyncCVHistos();
    h_VetoWall_NumbermatchToVeto.SyncCVHistos();
    h_VetoWall_vetoSixPush.SyncCVHistos();
    h_VetoWall_extrapnowalls.SyncCVHistos();
    h_VetoWall_extrapwall1.SyncCVHistos();
    h_VetoWall_extrapwall2.SyncCVHistos();
    h_VetoWall_extrapbothwalls.SyncCVHistos();
    h_VetoWall_MuonTrkMatchToVETOwalloff.SyncCVHistos();

    h_VetoWall_PMTmap_ON.SyncCVHistos();
    h_VetoWall_PMTmap_OFF.SyncCVHistos();
    h_Qsquare_TRUE_RECO.SyncCVHistos();

    //MuonEnergymaterial.Write();
    //outFile.cd();
    //outFile.Write();

  //=========================================
  // Plot stuff
  //=========================================

  // DrawMCWithErrorBand
//  PlotCVAndError(Muon_PZ_FULLMC.hist, "TEST");
std::string systematics_status;
if(m_RunCodeWithSystematics==true){sysmatics_status= "All_SysErrorsOn";}
else if (m_RunCodeWithSystematics==false){sysmatics_status= "StatsONLYErrors";}


  char outFileName[1024];
  auto playlist_name = Playlist_Info.GetPlaylistname();
  auto datatype = String_ISMC(is_mc);
  char c[playlist_name.length() + 1];
  char d[datatype.length() + 1];
  char rootpathway[OUTputRoot_pathway.length()+1];
  char ErrorStatus[sysmatics_status.length()+1];
  strcpy(rootpathway, OUTputRoot_pathway.c_str());
  strcpy(c, playlist_name.c_str());
  strcpy(d, datatype.c_str());
  strcpy(ErrorStatus, sysmatics_status.c_str());
  std::string reco_true = "TRUTHcuts_RECOcuts_" + playlist_name;
  std::string true_Cuts = "TRUTHcuts" + playlist_name;
  char reco_true_char[reco_true.length()+1];
  char true_Cuts_char[true_Cuts.length()+1];
  strcpy(reco_true_char, reco_true.c_str());
  strcpy(true_Cuts_char, true_Cuts.c_str());

  PrintCutstoScreen( kCutsVector , CountMap_RECO, c, mcscale );
  PrintCutstoScreen( kCutsVector , CountMap_RECO_Helium, "Helium", mcscale );
  PrintCutstoScreen( kCutsVector , CountMap_RECO_nonHelium, "nonHelium", mcscale );
  RECOCutTableLatex(c,kCutsVector, CountMap_RECO, CountMap_RECO_Helium, CountMap_RECO_nonHelium );

  TGraph  *RECO_Cuts = Make_RECOCut_Tgraph_fromCutMap("RECO_Cuts", CountMap_RECO);
  TGraph  *RECO_Helium_Cuts = Make_RECOCut_Tgraph_fromCutMap("RECO_Helium_Cuts", CountMap_RECO_Helium);
  TGraph  *RECO_nonHelium_Cuts = Make_RECOCut_Tgraph_fromCutMap("RECO_nonHelium_Cuts", CountMap_RECO);

  TGraph  *TRUE_RECO_Cuts = Make_RECOCut_Tgraph_fromCutMap("TRUE_RECO_Cuts", CountMap_TRUE_RECO);

  TGraph *Truth_Cuts =  Make_TruthCut_Tgraph_fromCutMap("Truth_Cuts", Truth_Cut_Map);
  //MakeEfficiencyCutCVS(CountMap_RECO, CountMap_RECO_Eff , kCutsVector_Eff,c,mcPOT);
  //Make_cvsOfCutsRate( kCutsVector , CountMap_RECO, c, true, mcscale, mcPOT);
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~ RECO Eff cuts ~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;
  //Make_cvsOfCutsRateTRUE(kTRUTHCutsVector , CountMap_TRUTH, true_Cuts_char, mcscale, mcPOT);
  //Make_cvsOfCutsRate( kCutsVector_Eff, CountMap_RECO_Eff, reco_true_char, true, mcscale, mcPOT);
  //PrintCutstoScreen( kCutsVector_Eff , CountMap_RECO_Eff, c, mcscale );

  //outFileName = "Histograms_test.root";
  //auto outFile = TFile::Open(outFileName);
  if(Run_EventLoopOnGid==true){
    sprintf(outFileName, "%s_%s_%s_%s.root", "Histograms",c,d,ErrorStatus);
    std::cout << "Writing output file on Grid to: " <<outFileName << std::endl;

  }
  else{
    sprintf(outFileName, "%s/%s_%s_%s_%s.root", rootpathway, "Histograms",c,d,ErrorStatus);
    std::cout << "Writing output file to: " <<outFileName << std::endl;

  }


  //TFile outFile(outFileName, "RECREATE");
  MnvH1D *h_Mig_MuonE_px;
  MnvH1D *h_Mig_MuonPZ_px;
  MnvH1D *h_Mig_MuonPT_px;
  MnvH1D *h_Mig_MuonTheta_px;
  MnvH1D *h_Mig_MuonE_py;
  MnvH1D *h_Mig_MuonPZ_py;
  MnvH1D *h_Mig_MuonPT_py;
  MnvH1D *h_Mig_MuonTheta_py;

 h_Mig_MuonE_px = h_Mig_MuonE->ProjectionX("h_Mig_MuonE_px");
 h_Mig_MuonPZ_px = h_Mig_MuonPZ->ProjectionX("h_Mig_MuonPZ_px");
 h_Mig_MuonPT_px = h_Mig_MuonPT->ProjectionX("h_Mig_MuonPT_px");
 h_Mig_MuonTheta_px = h_Mig_MuonTheta->ProjectionX("h_Mig_MuonTheta_px");

 h_Mig_MuonE_py = h_Mig_MuonE->ProjectionY("h_Mig_MuonE_py");
 h_Mig_MuonPZ_py = h_Mig_MuonPZ->ProjectionY("h_Mig_MuonPZ_py");
 h_Mig_MuonPT_py = h_Mig_MuonPT->ProjectionY("h_Mig_MuonPT_py");
 h_Mig_MuonTheta_py = h_Mig_MuonTheta->ProjectionY("h_Mig_MuonTheta_py");


  //TFile *outFile(outFileName, "RECREATE");
  TFile *outFile = new TFile(outFileName,"RECREATE");
  TChain POT_branch("Meta");
  POT_branch.Add(RootName.c_str());
  //TTree *oldtree = (TTree*)file->Get("Meta");
  TTree *clone = POT_branch.CloneTree();
  clone->Write();

  RECO_Cuts->Write();
  TRUE_RECO_Cuts->Write();
  RECO_Helium_Cuts->Write();
  RECO_nonHelium_Cuts->Write();
  Truth_Cuts->Write();

  h_MuonE.hist->Write();
  PlotUtils::MnvH1D* h_MuonE_FluxIntegrated = PlotUtils::flux_reweighter(playlist_fluxreweighter, nu_pdg, useNuEconstraint, NFlux_universe).GetIntegratedFluxReweighted(nu_pdg, h_MuonE.hist, Min_NuFluxEnergy, Max_NuFluxEnergy, useMuonCorrelations);//GetRebinnedFluxReweighted (nu_pdg, h_MuonE.hist);
  h_MuonE_FluxIntegrated->Clone()->Write("h_MuonE_FluxIntegrated");
  h_MuonE_TRUE_RECO.hist->Write();

  h_MuonE_Material.WriteToFile(*outFile);
  h_MuonE_Interaction.WriteToFile(*outFile);
  h_MuonE_Particle.WriteToFile(*outFile);

  h_MuonE_TRUE_RECO_Material.WriteToFile(*outFile);
  h_MuonE_TRUE_RECO_Interaction.WriteToFile(*outFile);
  h_MuonE_TRUE_RECO_Particle.WriteToFile(*outFile);



  h_MuonCharge.hist->Write();
  h_MuonCharge_Material.WriteToFile(*outFile);
  h_MuonCharge_Interaction .WriteToFile(*outFile);
  h_MuonCharge_Particle.WriteToFile(*outFile);
  h_MuonPZ.hist->Write();
  PlotUtils::MnvH1D* h_MuonPZ_FluxIntegrated = PlotUtils::flux_reweighter(playlist_fluxreweighter, nu_pdg, useNuEconstraint, NFlux_universe).GetIntegratedFluxReweighted(nu_pdg, h_MuonPZ.hist, Min_NuFluxEnergy, Max_NuFluxEnergy, useMuonCorrelations); //GetRebinnedFluxReweighted (nu_pdg, h_MuonPZ.hist);
  h_MuonPZ_FluxIntegrated->Clone()->Write("h_MuonPZ_FluxIntegrated");


  h_MuonPZ_TRUE_RECO.hist->Write();
  h_MuonPZ_Material.WriteToFile(*outFile);
  h_MuonPZ_Interaction.WriteToFile(*outFile);
  h_MuonPZ_Particle.WriteToFile(*outFile);


  h_MuonPT.hist->Write();
  PlotUtils::MnvH1D* h_MuonPT_FluxIntegrated = PlotUtils::flux_reweighter(playlist_fluxreweighter, nu_pdg, useNuEconstraint, NFlux_universe).GetIntegratedFluxReweighted(nu_pdg, h_MuonPT.hist, Min_NuFluxEnergy, Max_NuFluxEnergy, useMuonCorrelations);//GetRebinnedFluxReweighted(nu_pdg, h_MuonPT.hist);
  h_MuonPT_FluxIntegrated->Clone()->Write("h_MuonPT_FluxIntegrated");

  h_MuonPT_TRUE_RECO.hist->Write();
  h_MuonPT_Material.WriteToFile(*outFile);
  h_MuonPT_Interaction .WriteToFile(*outFile);
  h_MuonPT_Particle.WriteToFile(*outFile);
  h_MuonTheta.hist->Write();

  PlotUtils::MnvH1D* h_MuonTheta_FluxIntegrated = PlotUtils::flux_reweighter(playlist_fluxreweighter, nu_pdg, useNuEconstraint, NFlux_universe).GetIntegratedFluxReweighted(nu_pdg, h_MuonTheta.hist, Min_NuFluxEnergy, Max_NuFluxEnergy, useMuonCorrelations); //GetRebinnedFluxReweighted(nu_pdg, h_MuonTheta.hist);
  h_MuonTheta_FluxIntegrated->Clone()->Write("h_MuonTheta_FluxIntegrated");

  h_MuonTheta_TRUE_RECO.hist->Write();
  h_MuonTheta_Material.WriteToFile(*outFile);
  h_MuonTheta_Interaction.WriteToFile(*outFile);
  h_MuonTheta_Particle.WriteToFile(*outFile);

  h_MuonPZ_Fake.hist->Write();
  h_MuonPT_Fake.hist->Write();
  h_MuonE_Fake.hist->Write();
  h_MuonTheta_Fake.hist->Write();

  h_MuonPZ_Fake2.hist->Write();
  h_MuonPT_Fake2.hist->Write();
  h_MuonE_Fake2.hist->Write();
  h_MuonTheta_Fake2.hist->Write();


  h_MuonPhi_TRUE_RECO.hist->Write();
  h_MuonDOCA.hist->Write();
  h_MuonDOCA_TRUE_RECO.hist->Write();


  h_MuonDOCA_Material.WriteToFile(*outFile);
  h_MuonDOCA_Interaction.WriteToFile(*outFile);
  h_MuonDOCA_Particle.WriteToFile(*outFile);

  h_muon_MINOS_E.hist->Write();
  h_muon_minosStart_X.hist->Write();
  h_muon_minosStart_X_Material.WriteToFile(*outFile);
  h_muon_minosStart_X_Interaction.WriteToFile(*outFile);
  h_muon_minosStart_X_Particle.WriteToFile(*outFile);
  h_muon_minosStart_Y.hist->Write();
  h_muon_minosStart_Y_Material.WriteToFile(*outFile);
  h_muon_minosStart_Y_Interaction.WriteToFile(*outFile);
  h_muon_minosStart_Y_Particle.WriteToFile(*outFile);
  h_muon_minosStart_Z.hist->Write();
  h_muon_minosStart_Z_Material.WriteToFile(*outFile);
  h_muon_minosStart_Z_Interaction.WriteToFile(*outFile);
  h_muon_minosStart_Z_Particle.WriteToFile(*outFile);
  h_muon_StartNode_X.hist->Write();
  h_muon_StartNode_X_Material.WriteToFile(*outFile);
  h_muon_StartNode_X_Interaction.WriteToFile(*outFile);
  h_muon_StartNode_X_Particle.WriteToFile(*outFile);
  h_muon_StartNode_Y.hist->Write();
  h_muon_StartNode_Y_Material.WriteToFile(*outFile);
  h_muon_StartNode_Y_Interaction.WriteToFile(*outFile);
  h_muon_StartNode_Y_Particle.WriteToFile(*outFile);
  h_muon_StartNode_Z.hist->Write();
  h_muon_StartNode_Z_Material.WriteToFile(*outFile);
  h_muon_StartNode_Z_Interaction.WriteToFile(*outFile);
  h_muon_StartNode_Z_Particle.WriteToFile(*outFile);
  h_muon_LastNode_X.hist->Write();
  h_muon_LastNode_X_Material.WriteToFile(*outFile);
  h_muon_LastNode_X_Interaction.WriteToFile(*outFile);
  h_muon_LastNode_X_Particle.WriteToFile(*outFile);
  h_muon_LastNode_Y.hist->Write();
  h_muon_LastNode_Y_Material.WriteToFile(*outFile);
  h_muon_LastNode_Y_Interaction.WriteToFile(*outFile);
  h_muon_LastNode_Y_Particle.WriteToFile(*outFile);
  h_muon_LastNode_Z.hist->Write();
  h_muon_LastNode_Z_Material.WriteToFile(*outFile);
  h_muon_LastNode_Z_Interaction.WriteToFile(*outFile);
  h_muon_LastNode_Z_Particle.WriteToFile(*outFile);

  h_secTrk_tracklength.hist->Write();
  h_secTrk_tracklength_shorttracker.hist->Write();
  h_secTrk_tracklength_longtracker.hist->Write();
  h_secTrk_tracklength_otherlongtracker.hist->Write();
  h_secTrk_tracklength_Material.WriteToFile(*outFile);
  h_secTrk_tracklength_Interaction.WriteToFile(*outFile);
  h_secTrk_tracklength_Particle.WriteToFile(*outFile);
  h_secTrk_tracklength_Track.WriteToFile(*outFile);

  h_muon_minosEnd_X.hist->Write();
  h_muon_minosEnd_X_Material.WriteToFile(*outFile);
  h_muon_minosEnd_X_Interaction.WriteToFile(*outFile);
  h_muon_minosEnd_X_Particle.WriteToFile(*outFile);

  h_muon_minosEnd_Y.hist->Write();
  h_muon_minosEnd_Y_Material.WriteToFile(*outFile);
  h_muon_minosEnd_Y_Interaction.WriteToFile(*outFile);
  h_muon_minosEnd_Y_Particle.WriteToFile(*outFile);

  h_muon_minosEnd_Z.hist->Write();
  h_muon_minosEnd_Z_Material.WriteToFile(*outFile);
  h_muon_minosEnd_Z_Interaction.WriteToFile(*outFile);
  h_muon_minosEnd_Z_Particle.WriteToFile(*outFile);


  h_MuonCurvatureSig.hist->Write();
  h_MuonCurvatureSig_Material.WriteToFile(*outFile);
  h_MuonCurvatureSig_Interaction.WriteToFile(*outFile);
  h_MuonCurvatureSig_Particle.WriteToFile(*outFile);



  h_secTrk_LastNodeX.hist->Write();
  h_secTrk_LastNodeX_Material.WriteToFile(*outFile);
  h_secTrk_LastNodeX_Interaction.WriteToFile(*outFile);
  h_secTrk_LastNodeX_Particle.WriteToFile(*outFile);
  h_secTrk_LastNodeY.hist->Write();
  h_secTrk_LastNodeY_Material.WriteToFile(*outFile);
  h_secTrk_LastNodeY_Interaction.WriteToFile(*outFile);
  h_secTrk_LastNodeY_Particle.WriteToFile(*outFile);
  h_secTrk_LastNodeZ.hist->Write();
  h_secTrk_LastNodeZ_Material.WriteToFile(*outFile);
  h_secTrk_LastNodeZ_Interaction.WriteToFile(*outFile);
  h_secTrk_LastNodeZ_Particle.WriteToFile(*outFile);
  h_secTrk_FirstNodeX.hist->Write();
  h_secTrk_FirstNodeX_Material.WriteToFile(*outFile);
  h_secTrk_FirstNodeX_Interaction.WriteToFile(*outFile);
  h_secTrk_FirstNodeX_Particle.WriteToFile(*outFile);
  h_secTrk_FirstNodeY.hist->Write();
  h_secTrk_FirstNodeY_Material.WriteToFile(*outFile);
  h_secTrk_FirstNodeY_Interaction.WriteToFile(*outFile);
  h_secTrk_FirstNodeY_Particle.WriteToFile(*outFile);
  h_secTrk_FirstNodeZ.hist->Write();
  h_secTrk_FirstNodeZ_Material.WriteToFile(*outFile);
  h_secTrk_FirstNodeZ_Interaction.WriteToFile(*outFile);
  h_secTrk_FirstNodeZ_Particle.WriteToFile(*outFile);

  h_CryoVertex_X.hist->Write();
  h_CryoVertex_X_TRUE_RECO.hist->Write();
  h_CryoVertex_X_Material.WriteToFile(*outFile);
  h_CryoVertex_X_Interaction.WriteToFile(*outFile);
  h_CryoVertex_X_Particle.WriteToFile(*outFile);
  h_CryoVertex_X_Track.WriteToFile(*outFile);

  h_CryoVertex_X_boolNTrack.WriteToFile(*outFile);
  h_CryoVertex_X_VertexOptions.WriteToFile(*outFile);



  h_CryoVertex_Y.hist->Write();
  h_CryoVertex_Y_TRUE_RECO.hist->Write();
  h_CryoVertex_Y_Material.WriteToFile(*outFile);
  h_CryoVertex_Y_Interaction.WriteToFile(*outFile);
  h_CryoVertex_Y_Particle.WriteToFile(*outFile);
  h_CryoVertex_Y_Track.WriteToFile(*outFile);

  h_CryoVertex_Y_boolNTrack.WriteToFile(*outFile);
  h_CryoVertex_Y_VertexOptions.WriteToFile(*outFile);


  h_CryoVertex_Z.hist->Write();
  h_CryoVertex_Z_TRUE_RECO.hist->Write();
  h_CryoVertex_Z_Material.WriteToFile(*outFile);
  h_CryoVertex_Z_Interaction.WriteToFile(*outFile);
  h_CryoVertex_Z_Particle.WriteToFile(*outFile);
  h_CryoVertex_Z_Track.WriteToFile(*outFile);

  h_CryoVertex_Z_boolNTrack.WriteToFile(*outFile);
  h_CryoVertex_Z_VertexOptions.WriteToFile(*outFile);


  h_CryoVertex_R.hist->Write();
  h_CryoVertex_R_TRUE_RECO.hist->Write();
  h_CryoVertex_R_Material.WriteToFile(*outFile);
  h_CryoVertex_R_Interaction.WriteToFile(*outFile);
  h_CryoVertex_R_Particle.WriteToFile(*outFile);
  h_CryoVertex_R_Track.WriteToFile(*outFile);

  h_CryoVertex_R_boolNTrack.WriteToFile(*outFile);
  h_CryoVertex_R_VertexOptions.WriteToFile(*outFile);

  h_CryoVertexChiSqFit.hist->Write();
  h_CryoVertexChiSqFit_TRUE.hist->Write();
  h_CryoVertexChiSqFit_TRUE_RECO.hist->Write();
  h_CryoVertexChiSqFit_Material.WriteToFile(*outFile);
  h_CryoVertexChiSqFit_Interaction.WriteToFile(*outFile);
  h_CryoVertexChiSqFit_Particle.WriteToFile(*outFile);
  h_CryoVertexChiSqFit_Track.WriteToFile(*outFile);
  h_CryoVertexChiSqFit_boolNTrack.WriteToFile(*outFile);
  h_CryoVertexChiSqFit_VertexOptions.WriteToFile(*outFile);
  h_CryoVertexChiSqFitgreater10_Track.WriteToFile(*outFile);
  h_secTrk_Energy.hist->Write();
  h_secTrk_Energy_TRUE_RECO.hist->Write();
  h_secTrk_EnergyFINEBinning_TRUE_RECO.hist->Write();
  h_secTrk_Energy_Material.WriteToFile(*outFile);
  h_secTrk_Energy_Interaction.WriteToFile(*outFile);
  h_secTrk_Energy_Particle.WriteToFile(*outFile);
  h_secTrk_nonparentEnergy_Particle.WriteToFile(*outFile);


  h_secTrk_Energy_TRUE_RECO_Material.WriteToFile(*outFile);
  h_secTrk_Energy_TRUE_RECO_Interaction.WriteToFile(*outFile);
  h_secTrk_Energy_TRUE_RECO_Particle.WriteToFile(*outFile);


  h_secTrk_Theta_TRUE_RECO_Material.WriteToFile(*outFile);
  h_secTrk_Theta_TRUE_RECO_Interaction.WriteToFile(*outFile);
  h_secTrk_Theta_TRUE_RECO_Particle.WriteToFile(*outFile);
  h_secTrk_Theta_TRUE_RECO.hist->Write();

  h_secTrk_MidTheta.hist->Write();
  h_secTrk_MidTheta_Material.WriteToFile(*outFile);
  h_secTrk_MidTheta_Interaction.WriteToFile(*outFile);
  h_secTrk_MidTheta_Particle.WriteToFile(*outFile);

  h_secTrk_Openangle.hist->Write();
  h_secTrk_Openangle_TRUE_RECO.hist->Write();
  h_secTrk_Openangle_Material.WriteToFile(*outFile);
  h_secTrk_Openangle_Interaction.WriteToFile(*outFile);
  h_secTrk_Openangle_Particle.WriteToFile(*outFile);

  h_secTrk_DOCA.hist->Write();
  h_secTrk_DOCA_TRUE_RECO.hist->Write();
  h_secTrk_DOCA_Material.WriteToFile(*outFile);
  h_secTrk_DOCA_Interaction.WriteToFile(*outFile);
  h_secTrk_DOCA_Particle.WriteToFile(*outFile);

  h_secTrk_DOCA_TRUE_RECO_Material.WriteToFile(*outFile);
  h_secTrk_DOCA_TRUE_RECO_Interaction.WriteToFile(*outFile);
  h_secTrk_DOCA_TRUE_RECO_Particle.WriteToFile(*outFile);

  h_secTrk_Pathlength.hist->Write();
  h_secTrk_Pathlength_TRUE_RECO.hist->Write();
  h_secTrk_Pathlength_PROTON_TRUE_RECO.hist->Write();
  h_secTrk_Pathlength_PION_TRUE_RECO.hist->Write();
  h_secTrk_Pathlength_Material.WriteToFile(*outFile);
  h_secTrk_Pathlength_Interaction.WriteToFile(*outFile);
  h_secTrk_Pathlength_Particle.WriteToFile(*outFile);

  h_secTrk_Pathlength_TRUE_RECO_Material.WriteToFile(*outFile);
  h_secTrk_Pathlength_TRUE_RECO_Interaction.WriteToFile(*outFile);
  h_secTrk_Pathlength_TRUE_RECO_Particle.WriteToFile(*outFile);

  h_secTrk_MidTheta_leading_Particle.WriteToFile(*outFile);
  h_secTrk_MidTheta_Nonleading_Particle.WriteToFile(*outFile);

  h_Particle_N_A_secTrk_Theta_TRUE_RECO_Interaction.WriteToFile(*outFile);
  ////////////////////////////////////////////////
  // Veto Wall + Others
  ////////////////////////////////////////////////
  h_Tracksize.hist->Write();
  h_Tracksize_TRUE_RECO.hist->Write();
  h_Tracksize_Material.WriteToFile(*outFile);
  h_Tracksize_Interaction.WriteToFile(*outFile);
  h_Tracksize_Particle.WriteToFile(*outFile);


  h_VetoWall_matchToVeto.hist->Write();
  h_VetoWall_NumbermatchToVeto.hist->Write();
  h_VetoWall_vetoSixPush.hist->Write();
  h_VetoWall_extrapnowalls.hist->Write();
  h_VetoWall_extrapwall1.hist->Write();
  h_VetoWall_extrapwall2.hist->Write();
  h_VetoWall_extrapbothwalls.hist->Write();
  h_VetoWall_MuonTrkMatchToVETOwalloff.hist->Write();



////////////////////////////////////////////////

  h_secTrk_Openangle_TRUE_RECO_Material.WriteToFile(*outFile);
  h_secTrk_Openangle_TRUE_RECO_Interaction.WriteToFile(*outFile);
  h_secTrk_Openangle_TRUE_RECO_Particle.WriteToFile(*outFile);

  h_secTrk_Energy_Dimuon_TRUE_RECO.hist->Write();

  h_secTrk_Theta_Dimuon_TRUE_RECO.hist->Write();
  h_Muon_pseudorapidity.hist->Write();
  h_Muon_pseudorapidity_angle.hist->Write();
  h_Muon_rapidity.hist->Write();


  h_VetoWall_PMTmap_ON.hist->Write();
  h_VetoWall_PMTmap_OFF.hist->Write();
  h_Veto_PMT_Map.WriteToFile(*outFile);

  h_secTrk_Energy_PROTON_TRUE_RECO.hist->Write();
  h_secTrk_Theta_PROTON_TRUE_RECO.hist->Write();
  h_secTrk_Openangle_PROTON_TRUE_RECO.hist->Write();
  h_secTrk_Energy_PION_TRUE_RECO.hist->Write();
  h_secTrk_Theta_PION_TRUE_RECO.hist->Write();
  h_secTrk_Openangle_PION_TRUE_RECO.hist->Write();

  h_secTrk_Energy_PION0_TRUE_RECO.hist->Write();
  h_secTrk_Theta_PION0_TRUE_RECO.hist->Write();
  h_secTrk_Openangle_PION0_TRUE_RECO.hist->Write();

  h_secTrk_Energy_PION_neg_pos_TRUE_RECO.hist->Write();
  h_secTrk_Theta_PION_neg_pos_TRUE_RECO.hist->Write();
  h_secTrk_Openangle_PION_neg_pos_TRUE_RECO.hist->Write();

  h_Qsquare_TRUE_RECO.hist->Write();


  h_secTrk_tracklength_TRUE_RECO.hist->Write();
  //h_secTrk_tracklength_TRUE_TRUE_RECO.hist->Write();

/////////////////
/////2D hists////
/////////////////
  h_2d_PZ_PT_TRUE_RECO->Write();
  h_2d_E_PZ_TRUE_RECO->Write();
  h_2d_Theta_PZ_TRUE_RECO->Write();
  h_2d_E_PT_TRUE_RECO->Write();
  h_2d_Theta_PT_TRUE_RECO->Write();
  h_2d_Theta_PZ_TRUE_RECO->Write();
  h_2d_Theta_2ndTrkE_TRUE_RECO->Write();
  h_2d_muonE_2ndTrkE_TRUE_RECO->Write();
  h_2d_muonPT_2ndTrkE_TRUE_RECO->Write();
  h_2d_muonPZ_2ndTrkE_TRUE_RECO->Write();

  h_2d_Theta_2ndTrkE_Proton_TRUE_RECO->Write();
  h_2d_muonE_2ndTrkE_Proton_TRUE_RECO->Write();
  h_2d_muonPT_2ndTrkE_Proton_TRUE_RECO->Write();
  h_2d_muonPZ_2ndTrkE_Proton_TRUE_RECO->Write();

  h_2d_Theta_2ndTrkE_Pion_TRUE_RECO->Write();
  h_2d_muonE_2ndTrkE_Pion_TRUE_RECO->Write();
  h_2d_muonPT_2ndTrkE_Pion_TRUE_RECO->Write();
  h_2d_muonPZ_2ndTrkE_Pion_TRUE_RECO->Write();

  h_2d_2ndtrkPathlength_2ndTrkE_TRUE_RECO->Write();
  h_2d_2ndtrkPathlength_2ndTrkE_Proton_TRUE_RECO->Write();
  h_2d_2ndtrkPathlength_2ndTrkE_Pion_TRUE_RECO->Write();

  h_2d_2ndtrkPathlength_2ndtrkangle_TRUE_RECO->Write();
  h_2d_2ndtrkPathlength_2ndtrkangle_Proton_TRUE_RECO->Write();
  h_2d_2ndtrkPathlength_2ndtrkangle_Pion_TRUE_RECO->Write();

  h_2d_Theta_2ndTrKangle_TRUE_RECO->Write();
  h_2d_muonE_2ndTrkangle_TRUE_RECO->Write();
  h_2d_muonPT_2ndTrkangle_TRUE_RECO->Write();
  h_2d_muonPZ_2ndTrkangle_TRUE_RECO->Write();

/*
  h_2d_PZ_PT_LOWANGLE_TRUE_RECO->Write();
  h_2d_E_PZ_LOWANGLE_TRUE_RECO->Write();
  h_2d_Theta_PZ_LOWANGLE_TRUE_RECO->Write();
  h_2d_E_PT_LOWANGLE_TRUE_RECO->Write();
  h_2d_Theta_PT_LOWANGLE_TRUE_RECO->Write();
  h_2d_Theta_2ndTrkE_LOWANGLE_TRUE_RECO->Write();
  h_2d_muonE_2ndTrkE_LOWANGLE_TRUE_RECO->Write();
  h_2d_muonPT_2ndTrkE_LOWANGLE_TRUE_RECO->Write();
  h_2d_muonPZ_2ndTrkE_LOWANGLE_TRUE_RECO->Write();
  h_2d_Theta_2ndTrKangle_LOWANGLE_TRUE_RECO->Write();
  h_2d_muonE_2ndTrkangle_LOWANGLE_TRUE_RECO->Write();
  h_2d_muonPT_2ndTrkangle_LOWANGLE_TRUE_RECO->Write();
  h_2d_muonPZ_2ndTrkangle_LOWANGLE_TRUE_RECO->Write();
  h_2d_2ndtrkangle_2ndTrkE_LOWANGLE_TRUE_RECO->Write();
  h_secTrk_Theta_TRUE_RECO_LOWANGLE_Material.WriteToFile(*outFile);
  h_secTrk_Theta_TRUE_RECO_LOWANGLE_Interaction.WriteToFile(*outFile);
  h_secTrk_Theta_TRUE_RECO_LOWANGLE_Particle.WriteToFile(*outFile);
*/


  h_2d_2ndtrkangle_2ndTrkE_TRUE_RECO->Write();
  h_2d_2ndtrkangle_2ndTrkE_Proton_TRUE_RECO->Write();
  h_2d_2ndtrkangle_2ndTrkE_Pion_TRUE_RECO->Write();
  //h_2d_2ndtrkangle_2ndTrkE_dimuon_TRUE_RECO->Write();



  h_Mig_MuonE->Write();
  h_Mig_MuonPZ->Write();
  h_Mig_MuonPT->Write();
  h_Mig_MuonTheta->Write();
  
  h_Mig_Vertex_X->Write();
  h_Mig_Vertex_Y->Write();
  h_Mig_Vertex_R->Write();
  h_Mig_Vertex_Z->Write();

  h_Mig_MuonE_py->Write();
  h_Mig_MuonPZ_py->Write();
  h_Mig_MuonPT_py->Write();
  h_Mig_MuonTheta_py->Write();
  h_Mig_MuonE_px->Write();
  h_Mig_MuonPZ_px->Write();
  h_Mig_MuonPT_px->Write();
  h_Mig_MuonTheta_px->Write();

  h_MuonE_v2tune->Write();
  h_MuonE_MKmodel->Write();

  h_2d_Track_Fraction_Energy->Write();
  h_2d_Track_Fraction_Energy_Cuts->Write();
  h_2d_Track_Fraction_Energy_Second->Write();

  h_2d_2ndtrkPathlength_vertex_R->Write();
  h_2d_2ndtrkPathlength_vertex_Z->Write();

  h_2d_2ndtrkLength_vertex_R->Write();
  h_2d_2ndtrkLength_vertex_Z->Write();
  h_2d_2ndtrkLength_Angle->Write();
  h_2d_2ndtrkLength_finerAngle->Write();



  h2_FirstZnode_2ndTrklength->Write();
  h2_LastZnode_2ndTrklength->Write();

for(int kk=0;kk<3;kk++){
  h_Efficiency_h_CryoVertexChiSqFit[kk]->Write();
  h_Efficiency_h_CryoVertexChiSqFit_long[kk]->Write();
  h_Efficiency_h_CryoVertexChiSqFit_short[kk]->Write();
  h_Efficiency_h_CryoVertexChiSqFit_otherlong[kk]->Write();
}



  outFile->Close();


  char playlistname_char[playlist.length()+1];
  strcpy(playlistname_char,playlist.c_str());
  char arachneName[1024];
/*
sprintf(arachneName, "Arachne_secTrkHighangle_%s",playlistname_char);
MakesecTrkArachne(arachneHigh_angle,arachneName);

sprintf(arachneName, "Arachne_secTrkHighangle_clean_%s",playlistname_char);
MakesecTrkArachneClean(arachneHigh_angle,arachneName);

sprintf(arachneName, "Arachne_secTrklowKE_%s",playlistname_char);
MakesecTrkArachne(arachneLow_KE,arachneName);

sprintf(arachneName, "rachne_secTrklowKE_clean_%s",playlistname_char);
MakesecTrkArachneClean(arachneLow_KE,arachneName);

sprintf(arachneName, "Arachne_secTrkBOTH_%s",playlistname_char);
MakesecTrkArachne(arachneBoth,arachneName);

sprintf(arachneName, "Arachne_secTrkBOTH_clean_%s",playlistname_char);
MakesecTrkArachneClean(arachneBoth, arachneName);

sprintf(arachneName, "TrueEnergy_lessthannine_%s",playlistname_char);
MakesecTrkArachne_TRKDetails(Arachne_alltrks, arachneName, false,true);


 MakeTrueTrajectorInfoTextfile(All_True_trajectors,"TrueEnergy_lessthannine" ,true);


  //PlotUtils::MnvPlotter *Plotter();

//MakeTrue_interactionPlots(All_True_trajectors,"ME1F" ,5.0 ,"TRUE_interactions_cryotank", can,mnv_plotter);
MakeTrue_interactionPlots_WithRECOtrajector(All_True_trajectors,All_RECO_trajectors,playlistname_char , 5.0 ,"TRUE_RECO_interactions_TrueEnergy_Muon", can,mnv_plotter);
MakeLatex_particleTraj_True_RECO_plots(All_True_trajectors,
                                       All_RECO_trajectors,
                                       True_Reco_Energies,
                                       "TRUE_RECO_interactions_TrueEnergy_Muon"  , "Latex_TRUE_RECO_interactions_TrueEnergy_Muon", playlistname_char);
  //=========================================
  MakeTrue_interactionPlots_WithRECOtrajector(All_True_trajectors,All_RECO_trajectors_Parent,playlistname_char , 5.0 ,"TRUE_RECO_interactions_TrueEnergy_muon_Parent", can,mnv_plotter);
  MakeLatex_particleTraj_True_RECO_plots(All_True_trajectors,
                                         All_RECO_trajectors_Parent,
                                         True_Reco_Energies_Parent,
                                         "TRUE_RECO_interactions_TrueEnergy_muon_Parent"  , "Latex_TRUE_RECO_interactions_TrueEnergy_muon_Parent", playlistname_char);





std::cout<<" PDG_notmatch = " << PDG_notmatch<< "  PDG_match = "<< PDG_match<< std::endl;
*/
TCanvas *can = new TCanvas("", "");
MnvPlotter *mnv_plotter = new MnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
//MakeTrue_interactionPlots_WithRECOtrajector(All_True_trajectors,All_RECO_trajectors_Parent,playlistname_char , 5.0 ,"RecoStudy_recoilTracks", can,mnv_plotter);
/*
MakeLatex_particleTraj_True_RECO_plots(All_True_trajectors,
                                       All_RECO_trajectors_Parent,
                                       True_Reco_Energies_Parent,
                                       "RecoStudy_recoilTracks"  , "Latex_RecoStudy_recoilTracks", playlistname_char);
*/


  char  pdfName[1024];
  char pdf_start[1024];
  char pdf_end[1024];
  char XaxisName[1024];
  sprintf(pdfName, "MuonVars");

  //sprintf(pdf_start, "Optimization_figures.pdf(");
  //sprintf(pdf_end, "Optimization_figures.pdf)");


  //dPlotUtils::MnvPlotter mvnPlotter(PlotUtils::kCCInclusiveHeliumStyle);

    //mnvPlotter.legend_n_columns = 2;
    //auto names= h_MuonTheta.hist->GetErrorBandNames();
    //auto names_lat= h_MuonTheta.hist->  GetLatErrorBandNames();
    //auto names_ver= h_MuonTheta.hist->  GetVertErrorBandNames();
    //std::cout<<"all error bands "<<std::endl;
    //for(auto cat:names){std::cout<<"ERROR names = "<< cat<<std::endl;}
    //std::cout<<"names_LAT "<<std::endl;
    //for(auto cat:names_lat){std::cout<<" LAT names = "<< cat<<std::endl;}
    //std::cout<<"names_Vert "<<std::endl;
    //for(auto cat:names_ver){std::cout<<" Vert names = "<< cat<<std::endl;}
    //PlotCVAndError(h_MuonPZ.hist, "h_MuonPZ");
  //  PlotErrorSummary(h_MuonPZ.hist, "h_MuonPZ_ERROR_SUMMARY" ,"Energy (GeV)",can);
  //  PlotCVAndError(h_MuonPT.hist, "h_MuonPT");
  //  PlotErrorSummary(h_MuonPT.hist, "h_MuonPT_ERROR_SUMMARY", "Energy (GeV)",can);
  //  PlotCVAndError(h_MuonE.hist, "h_MuonE");
    //PlotErrorSummary(h_MuonE.hist,"h_MuonE_ERROR_SUMMARY" ,"h_MuonE_ERROR_SUMMARY", "Energy (GeV)",can);
    //PlotVertBand("VertexSmearingR", "VertexSmearingR_ERROR", h_MuonE.hist);
    //PlotVertBand("VertexSmearingZ", "VertexSmearingZ_ERROR", h_MuonE.hist);

    //PlotLatBand("VertexSmearingR", "VertexSmearingR_ERROR", h_MuonE.hist);
    //PlotLatBand("VertexSmearingZ", "VertexSmearingZ_ERROR", h_MuonE.hist);


    //PlotCVAndError(h_CryoVertex_Z.hist, "h_CryoVertex_Z");
  //  PlotCVAndError(h_CryoVertex_X.hist, "h_CryoVertex_X");
  //  PlotCVAndError(h_CryoVertex_Y.hist, "h_CryoVertex_Y");
  //  PlotCVAndError(h_CryoVertex_R.hist, "h_CryoVertex_R");


    //PlotCVAndError(h_secTrk_Energy_PROTON_TRUE.hist, "h_secTrk_Energy_PROTON_TRUE");
    //PlotCVAndError(h_secTrk_Energy_PROTON_TRUE_RECO.hist, "h_secTrk_Energy_PROTON_TRUE_RECO");
    //PlotErrorSummary(h_secTrk_Energy_PROTON_TRUE.hist, "h_secTrk_Energy_PROTON_TRUE_ERRORSummary", "Energy (GeV)",can);
    //PlotErrorSummary(h_secTrk_Energy_PROTON_TRUE_RECO.hist, "h_secTrk_Energy_PROTON_TRUE_RECO_ERRORSUMMARY", "Energy (GeV)",can);

    //h_secTrk_Energy_PROTON_TRUE_RECO.hist ->Divide(h_secTrk_Energy_PROTON_TRUE_RECO.hist ,h_secTrk_Energy_PROTON_TRUE.hist,1.0,1.0,"");
    //PlotCVAndError(h_secTrk_Energy_PROTON_TRUE_RECO.hist , "Efficiency_secTrkEnergy_PROTON");
    //PlotErrorSummary(h_secTrk_Energy_PROTON_TRUE_RECO.hist , "Efficiency_secTrkEnergy_PROTON_ERRORSUMMARY", "vertex Z(mm)",can);

    //PlotCVAndError(h_secTrk_Energy_PION_TRUE.hist, "h_secTrk_Energy_PION_TRUE");
    //PlotCVAndError(h_secTrk_Energy_PION_TRUE_RECO.hist, "h_secTrk_Energy_PION_TRUE_RECO");
    //PlotErrorSummary(h_secTrk_Energy_PION_TRUE.hist, "h_secTrk_Energy_PION_TRUE_ERRORSummary", "Energy (GeV)",can);
    //PlotErrorSummary(h_secTrk_Energy_PION_TRUE_RECO.hist, "h_secTrk_Energy_PION_TRUE_RECO_ERRORSUMMARY", "Energy (GeV)",can);

  //  h_secTrk_Energy_PION_TRUE_RECO.hist->Divide(h_secTrk_Energy_PION_TRUE_RECO.hist ,h_secTrk_Energy_PION_TRUE.hist,1.0,1.0,"");
  //  PlotCVAndError(h_secTrk_Energy_PION_TRUE_RECO.hist, "Efficiency_secTrkEnergy_PION");
  //  PlotErrorSummary(h_secTrk_Energy_PION_TRUE_RECO.hist, "Efficiency_secTrkEnergy_PION_ERRORSUMMARY", "vertex Z(mm)",can);

    ///////////
  //  PlotCVAndError(h_secTrk_MidTheta_PROTON_TRUE.hist, "h_secTrk_MidTheta_PROTON_TRUE");
  //  PlotCVAndError(h_secTrk_MidTheta_PROTON_TRUE_RECO.hist, "h_secTrk_MidTheta_PROTON_TRUE_RECO");
  //  PlotErrorSummary(h_secTrk_MidTheta_PROTON_TRUE.hist, "h_secTrk_MidTheta_PROTON_TRUE_ERRORSummary", "Angle (Deg)",can);
  //  PlotErrorSummary(h_secTrk_MidTheta_PROTON_TRUE_RECO.hist, "h_secTrk_MidTheta_PROTON_TRUE_RECO_ERRORSUMMARY", "Angle (Deg)",can);

//    h_secTrk_MidTheta_PROTON_TRUE_RECO.hist ->Divide(h_secTrk_MidTheta_PROTON_TRUE_RECO.hist ,h_secTrk_MidTheta_PROTON_TRUE.hist,1.0,1.0,"");
//    PlotCVAndError(h_secTrk_MidTheta_PROTON_TRUE_RECO.hist , "Efficiencyh_secTrk_MidTheta_PROTON");
//    PlotErrorSummary(h_secTrk_MidTheta_PROTON_TRUE_RECO.hist , "Efficiencyh_secTrk_MidTheta_PROTON_ERRORSUMMARY", "Angle (Deg)",can);

//    PlotCVAndError(h_secTrk_MidTheta_PION_TRUE.hist, "h_secTrk_MidTheta_PION_TRUE");
//    PlotCVAndError(h_secTrk_MidTheta_PION_TRUE_RECO.hist, "h_secTrk_MidTheta_PION_TRUE_RECO");
//    PlotErrorSummary(h_secTrk_MidTheta_PION_TRUE.hist, "h_secTrk_MidTheta_PION_TRUE_ERRORSummary", "Angle (Deg)",can);
//    PlotErrorSummary(h_secTrk_MidTheta_PION_TRUE_RECO.hist, "h_secTrk_MidTheta_PION_TRUE_RECO_ERRORSUMMARY", "Angle (Deg)",can);

  //  h_secTrk_MidTheta_PION_TRUE_RECO.hist->Divide(h_secTrk_MidTheta_PION_TRUE_RECO.hist ,h_secTrk_MidTheta_PION_TRUE.hist,1.0,1.0,"");
  //  PlotCVAndError(h_secTrk_MidTheta_PION_TRUE_RECO.hist, "Efficiencyh_secTrk_MidTheta_PION");
  //  PlotErrorSummary(h_secTrk_MidTheta_PION_TRUE_RECO.hist, "Efficiencyh_secTrk_MidTheta_PION_ERRORSUMMARY", "Angle (Deg)",can);
    ////////////////////

    ///////////
  //  PlotCVAndError(h_secTrk_Openangle_PROTON_TRUE.hist, "h_secTrk_Openangle_PROTON_TRUE");
  //  PlotCVAndError(h_secTrk_Openangle_PROTON_TRUE_RECO.hist, "h_secTrk_Openangle_PROTON_TRUE_RECO");
  //  PlotErrorSummary(h_secTrk_Openangle_PROTON_TRUE.hist, "h_secTrk_Openangle_PROTON_TRUE_ERRORSummary", "Angle (Deg)",can);
  //  PlotErrorSummary(h_secTrk_Openangle_PROTON_TRUE_RECO.hist, "h_secTrk_Openangle_PROTON_TRUE_RECO_ERRORSUMMARY", "Angle (Deg)",can);

  //  h_secTrk_Openangle_PROTON_TRUE_RECO.hist ->Divide(h_secTrk_Openangle_PROTON_TRUE_RECO.hist ,h_secTrk_Openangle_PROTON_TRUE.hist,1.0,1.0,"");
  //  PlotCVAndError(h_secTrk_Openangle_PROTON_TRUE_RECO.hist , "Efficiency_h_secTrk_Openangle_PROTON");
  //  PlotErrorSummary(h_secTrk_Openangle_PROTON_TRUE_RECO.hist , "Efficiency_h_secTrk_Openangle_PROTON_ERRORSUMMARY", "Angle (Deg)",can);

  //  PlotCVAndError(h_secTrk_Openangle_PION_TRUE.hist, "h_secTrk_Openangle_PION_TRUE");
  //  PlotCVAndError(h_secTrk_Openangle_PION_TRUE_RECO.hist, "h_secTrk_Openangle_PION_TRUE_RECO");
  //  PlotErrorSummary(h_secTrk_Openangle_PION_TRUE.hist, "h_secTrk_Openangle_PION_TRUE_ERRORSummary", "Angle (Deg)",can);
  //  PlotErrorSummary(h_secTrk_Openangle_PION_TRUE_RECO.hist, "h_secTrk_Openangle_PION_TRUE_RECO_ERRORSUMMARY", "Angle (Deg)",can);

//    h_secTrk_Openangle_PION_TRUE_RECO.hist->Divide(h_secTrk_Openangle_PION_TRUE_RECO.hist ,h_secTrk_Openangle_PION_TRUE.hist,1.0,1.0,"");
//    PlotCVAndError(h_secTrk_Openangle_PION_TRUE_RECO.hist, "Efficiency_h_secTrk_Openangle_PION");
//    PlotErrorSummary(h_secTrk_Openangle_PION_TRUE_RECO.hist, "Efficiency__secTrkopenangle_PION_ERRORSUMMARY", "Angle (Deg)",can);
    ////////////////////





  //  PlotCVAndError(Muon_PZ_FULLMC.hist, "Muon_PZ_FULLMC");
    // Plot Error Summary
   //PlotErrorSummary(h_CryoVertex_Z.hist, "h_CryoVertex_Z_ERROR_SUMMARY", "vertex Z(mm)",can);

  //Plot individual universes

    //PlotVertUniverse("EmuRangeCurve", universe, "TEST_E 0", h_MuonE.hist);
  //  PlotVertUniverse("EmuRangeCurve", universe, "TEST_Pz", Muon_PZ_FULLMC.hist);

    //PlotVertUniverse("EmuRangeCurve", universe, "TEST", Muon_PZ_FULLMC.hist);
  //  PlotVertUniverse("EmuRangeCurve", universe, "TEST_E 1", h_MuonE.hist);
  //  PlotVertUniverse("EmuRangeCurve", universe, "TEST_Pz", Muon_PZ_FULLMC.hist);



    //for (int i = 0; i < 5; ++i){ PlotVertUniverse("Flux", 1, "TEST", Muon_E_FULLMC.hist);}

    //Plot the Bands
  //  PlotVertBand("EmuRangeCurve", "TEST", Muon_PZ_FULLMC.hist);
  //  PlotVertBand("Flux", "TEST", Muon_PZ_FULLMC.hist);

    //PlotTotalError(Muon_PZ_FULLMC.hist, "TEST");


  //PlotVertBand("EmuRangeCurve", "EmuRangeCurve", h_MuonE.hist);
  //PlotVertBand("Flux", "Flux", h_MuonE.hist);
  //PlotTotalError(Muon_E_EmptyMC.hist, "Muon_E_EmptyMC");

    std::cout << "END OF Plotting" << std::endl;

    std::cout << " THe Greatest  Chi sqrt value for Reco Cuts = "<< greatest_Chisqrt<< std::endl;
   //MakeLatex_Tables_withTrue_Event_info(N_A_secTrkParticle," ",  "N_A_FS_RECO", c, .5, "N_A in FS");
   std::cout << " this many Other long tracks  = "<< otherlongtrack<< std::endl;


  for(auto band : error_bands){
    std::vector<HeliumCVUniverse*> band_universes = band.second;
    for(unsigned int i_universe = 0; i_universe < band_universes.size(); ++i_universe){ delete band_universes[i_universe];}
  }

  std::cout << "Success" << std::endl;

//}


can -> Print("Test.pdf");

}//END of Eventloop Function

//=========================================
//=========================================
//////////////////////////////////////////////////////////////


std::vector<ECuts> GetRECOCutsVector() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ECuts> ret_vec;
  ret_vec.push_back(kNoCuts );
  ret_vec.push_back(kGoodEnergy );
  ret_vec.push_back(kUsableMuon);
  ret_vec.push_back(kMinosCoil );
  ret_vec.push_back(kMinosMatch);
  ret_vec.push_back(kMinosCurvature);
  ret_vec.push_back(kMinosCharge );

//ret_vec.push_back(kThetaMu );
  ret_vec.push_back(kMuonAngle );
  ret_vec.push_back(kMu_is_Plausible);

  ret_vec.push_back(kNTracks);
  ret_vec.push_back(kVertexConverge);
  ret_vec.push_back(kVertex_ConvergedfromAllTracks);
  ret_vec.push_back(kMaxChiSqrt_byTrackType);
  ret_vec.push_back(kFiducialVolume);

  ret_vec.push_back(kVeto );
  ret_vec.push_back(kSix );
  ret_vec.push_back(kMatchVetoDeadPaddle);

  ret_vec.push_back(kTrackForwardGoing);
  ret_vec.push_back(ksecTrkwrtblessthanMaxAngle);

  ret_vec.push_back(kAllCuts );





//  ret_vec.push_back(kMaxChiSqrt);




  //int n = sizeof(kCutsArray) / sizeof(kCutsArray[0]);
  //static std::vector<ECuts> ret_vec(kCutsArray, kCutsArray + n);
  return ret_vec;
//#endif
}



std::vector<ECuts> GetRECOCutsForEffVector() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ECuts> ret_vec;
  ret_vec.push_back(kNoCuts  );
  ret_vec.push_back(kGoodEnergy );
  //ret_vec.push_back(kThetaMu );
  ret_vec.push_back(kMuonAngle );
  ret_vec.push_back(kNTracks);
  ret_vec.push_back(kUsableMuon);
  ret_vec.push_back(kMu_is_Plausible);
  ret_vec.push_back(kNonMu_is_Plausible);
  ret_vec.push_back(kVeto );
  ret_vec.push_back(kSix );
  ret_vec.push_back(kMatchVetoDeadPaddle);

  ret_vec.push_back(kMinosCoil );
  ret_vec.push_back(kMinosMatch);
  ret_vec.push_back(kMinosCurvature);
  ret_vec.push_back(kMinosCharge );

  ret_vec.push_back(kVertexConverge);
  ret_vec.push_back(kFiducialVolume );
  ret_vec.push_back(kTrackForwardGoing );
  ret_vec.push_back(ksecTrkwrtblessthanMaxAngle);
  //ret_vec.push_back(kMaxChiSqrt);
  ret_vec.push_back(kVertex_ConvergedfromAllTracks);
  ret_vec.push_back(kMaxChiSqrt_byTrackType);
  ret_vec.push_back(kAllCuts );

  //int n = sizeof(kCutsArray) / sizeof(kCutsArray[0]);
  //static std::vector<ECuts> ret_vec(kCutsArray, kCutsArray + n);
  return ret_vec;
//#endif
}


std::vector<ECutsTRUTH> GetTRUTHCutsVector() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ECutsTRUTH> True_vec;
  True_vec.push_back(kTRUTHNoCuts   );
  True_vec.push_back(kTRUTHMuonEnergy );
  True_vec.push_back(kTRUTHMuonAngle );
  True_vec.push_back(kTRUTHneutrino);
  True_vec.push_back(kTRUTHCCInteraction );
  True_vec.push_back(kTRUTHtarget);
  True_vec.push_back(kTRUTH_greaterthanoneFS);
  //True_vec.push_back(kTRUTHFiduical );// no True Fiduical Cut on top
  //True_vec.push_back(kTRUTH_2ndTrkEnergythreshold );
  //True_vec.push_back(kTRUTH_2ndTrkAnlgethreshold );
  //True_vec.push_back(kTRUTH_secTrk_Angle_threshold);
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);
  True_vec.push_back(kTRUTH_NoNeutral_FS_2ndTrk_RECOBRANCH);
  //True_vec.push_back(kTRUTH_NoNeutral_FS_2ndTrk_withProtonanPionThresholds_RECOBRANCH);
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);
  True_vec.push_back(kAllTRUTHCuts);


  //int n = sizeof(kCutsArray) / sizeof(kCutsArray[0]);
  //static std::vector<ECuts> ret_vec(kCutsArray, kCutsArray + n);
  return True_vec;
//#endif
}

std::vector<ECutsTRUTH> GetTRUTHCutsVector_Energy() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ECutsTRUTH> True_vec;
  True_vec.push_back(kTRUTHNoCuts   );
  True_vec.push_back(kTRUTHMuonEnergy );
  True_vec.push_back(kTRUTHMuonAngle );
  True_vec.push_back(kTRUTHneutrino);
  True_vec.push_back(kTRUTHCCInteraction );
  True_vec.push_back(kTRUTHtarget);
  True_vec.push_back(kTRUTH_greaterthanoneFS);
  //True_vec.push_back(kTRUTHFiduical ); // dont' apply truth fiduical cut in Nomrateor
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);
  True_vec.push_back(kTRUTH_NoNeutral_FS_2ndTrk_RECOBRANCH);
  //True_vec.push_back(kTRUTH_NoNeutral_FS_2ndTrk_withProtonanPionThresholds_RECOBRANCH);
  //True_vec.push_back(kTRUTH_2ndTrkProtonEnergythreshold);
  //True_vec.push_back(kTRUTH_2ndTrkPionEnergythreshold);
  //True_vec.push_back(kTRUTH_secTrk_Angle_threshold);
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
   Playlist.push_back(kME1G);
    //Playlist.push_back(kME1A);
    //Playlist.push_back(kME1L);
    //Playlist.push_back(kME1M);
    //Playlist.push_back(kME1N);
  //Full
    //Playlist.push_back(kME1P);
    //Playlist.push_back(kME1C);
    //Playlist.push_back(kME1D);
    //Playlist.push_back(kME1F);
    //Playlist.push_back(kME1E);
  return Playlist;
//#endif
}

std::vector<ME_helium_Playlists> GetTRUEPlayListVector() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ME_helium_Playlists> Playlist;

  Playlist.push_back(kME1G_Truth);

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
  weight_vec.push_back(kweightMinos );
  weight_vec.push_back(kweightGenie);
  weight_vec.push_back(kweight2p2ptune );
  weight_vec.push_back(kweightRPA);
  weight_vec.push_back(kweight_HeliumTargetMass);

  return weight_vec;
//#endif
}

std::vector<Weights> GetWeightVector_v2() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<Weights> weight_vec;
  weight_vec.push_back(kweightFlux );
  weight_vec.push_back(kweightMinos );
  weight_vec.push_back(kweightGenie);
  weight_vec.push_back(kweight2p2ptune );
  weight_vec.push_back(kweightRPA);
  weight_vec.push_back(kweightLowQ2Pi);
  return weight_vec;
//#endif
}

std::vector<Weights> GetWeightVector_mk() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<Weights> weight_vec;
  weight_vec.push_back(kweightFlux );
  weight_vec.push_back(kweightMinos );
  //weight_vec.push_back(kweightGenie);
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
  TH1::AddDirectory(false);

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

  bool Run_EventLoopOnGid = false;
  if(Run_EventLoopOnGid==true){std::cout << "This Eventloop is step up to run on the Grid" << std::endl;}
  else{std::cout << "This Eventloop is step up locally" << std::endl;}
  //std::cin >> input_user;
  std::cout << input_user << std::endl;


  runEventLoop(m_debugOn, Playlist_to_run, Run_EventLoopOnGid);
  return 0;
}
//#endif
