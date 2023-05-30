
//File: Helium_runEventLoop_ShiftRZStudy.cxx
//Brief: THe Loop for making the hist for the Shift study
//Author: Christian Nguyen christian2nguyen@ufl.edu
// * Uses the New Systematics Framework and "Universe" objects.
// * loop universes, make cuts and fill histograms with the correct lateral
// shifts and weights for each universe.
// * TChain --> PlotUtils::ChainWrapper.
// * MnvHXD --> PlotUtils::HistWrapper.
// * Genie, flux, non-resonant pion, and some detector systematics calculated.
//

#include "Helium_runEventLoop_EfficiencyStudy.h"
//#include "Convolution_EventSelection_Values.h"
std::string OUTputRoot_pathway = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles";
//=====================================================
// Cuts applying Functions and Weights
//=====================================================
std::vector<ECuts> GetVectorRECOCuts_ALL();
std::vector<ECuts> GetVectorRECOCutsFidicual_Eff();

std::vector<ECutsTRUTH> GetTRUTHCutsVector_ALL();
std::vector<ECutsTRUTH> GetTRUTH_FidiucalMuCutsVector();
std::vector<Particle_type>  GetParicle_type();
std::vector<Weights> GetWeightVector();
std::vector<Weights> GetWeightVector_v2();
std::vector<Weights> GetWeightVector_mk();
//double Mev_to_GeV=.001;

// Get container of systematic
const bool m_RunCodeWithSystematics = false;
const bool m_RunCodeWith_Alwgts = false;

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
PlotUtils::NamedCategory<Particle_type>({kElectron}, "e^{-}"),
PlotUtils::NamedCategory<Particle_type>({kMuon},     "#mu"),
PlotUtils::NamedCategory<Particle_type>({kGamma},    "#gamma"),
PlotUtils::NamedCategory<Particle_type>({kNeutrino_muon}, "#nu_{#mu}"),
PlotUtils::NamedCategory<Particle_type>({kNeutrino_electron}, "#nu_{e}"),
PlotUtils::NamedCategory<Particle_type>({kAnti_Neutrino}, "#bar{#nu}"),
PlotUtils::NamedCategory<Particle_type>({kKaon},     "#Kappa"),
PlotUtils::NamedCategory<Particle_type>({kPion_0},     "#pi^{0}"),
PlotUtils::NamedCategory<Particle_type>({kPion_neg},     "#pi^{-}"),
PlotUtils::NamedCategory<Particle_type>({kPion_pos},     "#pi^{+}"),
PlotUtils::NamedCategory<Particle_type>({kProton},   "Proton"),
PlotUtils::NamedCategory<Particle_type>({kNeutron},   "Neutron"),
PlotUtils::NamedCategory<Particle_type>({kFourHelium},   "{}^{4}He"),
PlotUtils::NamedCategory<Particle_type>({kLamdba},       "#Lambda"),
PlotUtils::NamedCategory<Particle_type>({kSigma_plus},   "#Sigma^{+}")
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

typedef std::map< std::string, std::vector<HeliumCVUniverse*> > UniverseMap;

UniverseMap GetErrorBands(PlotUtils::ChainWrapper* chain) {

    //return Map
    UniverseMap error_bands;

    //========================================================================
    // CV
    //========================================================================

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
    // GENIE Standards
    //========================================================================


    UniverseMap genie_systematics = PlotUtils::GetGenieSystematicsMap<HeliumCVUniverse>(chain);
    error_bands.insert(genie_systematics.begin(), genie_systematics.end());

    //========================================================================
    //  MnvTuned - 2p2h
    //========================================================================

    UniverseMap a2p2h_systematics = PlotUtils::Get2p2hSystematicsMap<HeliumCVUniverse>(chain);
    error_bands.insert(a2p2h_systematics.begin(), a2p2h_systematics .end());

    //========================================================================
    // (RPA)random phase appox , long range Nuclear correlations modeling
    //========================================================================

    UniverseMap RPA_systematics = PlotUtils::GetRPASystematicsMap<HeliumCVUniverse>(chain);
    error_bands.insert(RPA_systematics.begin(), RPA_systematics.end());

    //========================================================================
     // Helium Vertex smearing
     //========================================================================

    UniverseMap VertexSmearing_systematics = GetHELIUMVertexSmearingShiftSystematicsMap<HeliumCVUniverse>(chain);
    error_bands.insert(VertexSmearing_systematics.begin(), VertexSmearing_systematics.end());

    //========================================================================
    // Helium Mass
    //========================================================================

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
const std::vector<ECuts> kCutsVector_ALL = GetVectorRECOCuts_ALL();
const std::vector<ECuts> kCutsVector_FiduicalEff = GetVectorRECOCutsFidicual_Eff();
const std::vector<ECutsTRUTH> kTRUTHCutsVector_Fiduical = GetTRUTH_FidiucalMuCutsVector();

const std::vector<Weights> kWeights_v1tune= GetWeightVector();
const std::vector<Weights> kWeights_v2tune= GetWeightVector_v2();
const std::vector<Weights> kWeights_forMK = GetWeightVector_mk();

const double ShiftX_major = 0.0; //return_shiftX();//5.0;//-44.0; // [mm]
const double ShiftY_major = 0.0; //return_shiftY();//50.0; // 41 [mm]
const double ShiftZ_major = 0.0; //return_shiftZ();//-4.0; // [mm]    //

std::default_random_engine generatorFit;

double vertex_X_mean;
double vertex_X_sigma;
double vertex_Y_mean;
double vertex_Y_sigma;
double vertex_Z_mean;
double vertex_Z_sigma;


  Fill_Convolution_BeforeShift(PlayList_iterator ,vertex_X_mean,
    vertex_X_sigma, vertex_Y_mean, vertex_Y_sigma, vertex_Z_mean, vertex_Z_sigma);


std::cout<<"vertex_X_mean = " << vertex_X_mean << std::endl;

std::cout<<"vertex_X_sigma = " << vertex_X_sigma << std::endl;
std::cout<<"vertex_Y_mean = " << vertex_Y_mean << std::endl;
std::cout<<"vertex_Y_sigma = " << vertex_Y_sigma << std::endl;

std::normal_distribution<double> vertexX_Convolution(vertex_X_mean, vertex_X_sigma);
std::normal_distribution<double> vertexY_Convolution(vertex_Y_mean, vertex_Y_sigma);




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

  MinervaUniverse::SetDeuteriumGeniePiTune(false);
  MinervaUniverse::SetNuEConstraint(true);
  MinervaUniverse::SetZExpansionFaReweight(false);
  MinervaUniverse::SetAnalysisNuPDG(14);
  MinervaUniverse::SetNonResPiReweight(true);
  MinervaUniverse::SetNFluxUniverses(n_flux_universes);
  std::string playlist = GetPlaylist(PlayList_iterator);

  MinervaUniverse::SetPlaylist(playlist);
  int otherlongtrack=0;
  //lotUtils::MnvH1D* h_Flux = nullptr;
  int nu_pdg = MinervaUniverse::GetAnalysisNuPDG();
  std::string playlist_fluxreweighter = MinervaUniverse::GetPlaylist();
  bool useNuEconstraint = MinervaUniverse::UseNuEConstraint();
  int NFlux_universe = MinervaUniverse::GetNFluxUniverses();
  bool useMuonCorrelations = true;
  double Min_NuFluxEnergy = 0.0;
  double Max_NuFluxEnergy = 120.0;
  //PlotUtils::MnvH1D* h_Flux = PlotUtils::flux_reweighter(playlist_fluxreweighter, nu_pdg, useNuEconstraint, NFlux_universe).GetFluxReweighted(nu_pdg	);

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


POTCounter pot_counter;

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
std::vector<double> Vertex_Zbin_vector = GetBinvertexVector(kZ);
std::vector<double> Vertex_Rbin_vector = GetBinvertexVector(kR);
std::vector<double> Vertex_Ybin_vector = GetBinvertexVector(kY);
std::vector<double> Vertex_Xbin_vector = GetBinvertexVector(kX);
std::vector<double> Distance_to_innerTank = GetBinvertexVector(kdistance_edge);

std::vector<double> Ebin_vector = GetBinMuonVector(kE);
std::vector<double> Pzbin_vector= GetBinMuonVector(kP_Z);
std::vector<double> PTbin_vector= GetBinMuonVector(kP_T);
std::vector<double> MuonThetabin_vector= GetBinMuonVector(kAngleWRTB);
std::vector<double> Vertex_DOCAbin_vector = GetBinMuonVector(kDOCA_muon);
std::vector<double> secTrk_DOCA_vector = GetSecondTrkVarVector(kDOCA);
std::vector<double> secTrk_Pathway_vector = GetSecondTrkVarVector(kPathway);
std::vector<double> Recoil_track_length_vector = GetSecondTrkVarVector(ksec_tracklength_minerva);
std::vector<double> Distance_to_Caps = GetBinvertexVector(kdistance_downstreamcap);

/*
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE("h_MuonE", "Muon_{E} NEW Method", Ebin_vector , error_bands);
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonE_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonE_Material", Ebin_vector ,"MuonE_Material; [GeV];Events");

PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPZ("h_MuonPZ", "Muon_{PZ} NEW Method",  Pzbin_vector , error_bands);
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonPZ_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonPZ_Material", Pzbin_vector ,"h_MuonPZ_Material; [GeV];Events");

PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPT("h_MuonPT", "Muon_{PT} NEW Method",  PTbin_vector , error_bands);
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonPT_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonPT_Material", PTbin_vector ,"h_MuonPT_Material; [GeV];Events");

PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonTheta("h_MuonTheta", "#theta_{#mu} NEW Method",  MuonThetabin_vector , error_bands);
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonTheta_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonTheta_Material", MuonThetabin_vector ,"h_MuonTheta_Material; [GeV];Events");
*/



PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X("h_CryoVertex_X", "Vertex_X",  Vertex_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_TRUE("h_CryoVertex_X_TRUE", "Vertex_X_TRUE",  Vertex_Xbin_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_upstreamCap(              "h_CryoVertex_X_upstreamCap",               "Vertex_X",       Vertex_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_upstreamCap_TRUE(         "h_CryoVertex_X_upstreamCap_TRUE",          "Vertex_X_TRUE",  Vertex_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_barrel(                   "h_CryoVertex_X_barrel",                    "Vertex_X",       Vertex_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_barrel_TRUE(              "h_CryoVertex_X_barrel_TRUE",               "Vertex_X_TRUE",  Vertex_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_downstreamCap(            "h_CryoVertex_X_downstreamCap",             "Vertex_X",       Vertex_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_downstreamCap_TRUE(       "h_CryoVertex_X_downstreamCap_TRUE",        "Vertex_X_TRUE",  Vertex_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_downstreamConcaveCap(     "h_CryoVertex_X_downstreamConcaveCap",      "Vertex_X",       Vertex_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_downstreamConcaveCap_TRUE("h_CryoVertex_X_downstreamConcaveCap_TRUE", "Vertex_X_TRUE",  Vertex_Xbin_vector , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_X_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_X_Material", Vertex_Xbin_vector ,"h_CryoVertex_X_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_X_upstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_X_upstreamCap_Material", Vertex_Xbin_vector ,"h_CryoVertex_X_upstreamCap_Material; [mm];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_X_barrel_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_X_barrel_Material", Vertex_Xbin_vector ,"h_CryoVertex_X_barrel_Material; [mm];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_X_downstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_X_downstreamCap_Material", Vertex_Xbin_vector ,"h_CryoVertex_X_downstreamCap_Material; [mm];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_X_downstreamConcaveCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_X_downstreamConcaveCap_Material", Vertex_Xbin_vector ,"h_CryoVertex_X_downstreamConcaveCap_Material; [mm];Events");




PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y("h_CryoVertex_Y", "Vertex_Y",  Vertex_Ybin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_TRUE("h_CryoVertex_Y_TRUE", "Vertex_Y_TRUE",  Vertex_Ybin_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_upstreamCap(              "h_CryoVertex_Y_upstreamCap", "Vertex_Y",  Vertex_Ybin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_upstreamCap_TRUE(         "h_CryoVertex_Y_upstreamCap_TRUE", "Vertex_Y_TRUE",  Vertex_Ybin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_barrel(                   "h_CryoVertex_Y_barrel", "Vertex_Y",  Vertex_Ybin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_barrel_TRUE(              "h_CryoVertex_Y_barrel_TRUE", "Vertex_Y_TRUE",  Vertex_Ybin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_downstreamCap(            "h_CryoVertex_Y_downstreamCap", "Vertex_Y",  Vertex_Ybin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_downstreamCap_TRUE(       "h_CryoVertex_Y_downstreamCap_TRUE", "Vertex_Y_TRUE",  Vertex_Ybin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_downstreamConcaveCap(     "h_CryoVertex_Y_downstreamConcaveCap", "Vertex_Y",  Vertex_Ybin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_downstreamConcaveCap_TRUE("h_CryoVertex_Y_downstreamConcaveCap_TRUE", "Vertex_Y_TRUE",  Vertex_Ybin_vector , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Y_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Y_Material", Vertex_Ybin_vector ,"h_CryoVertex_Y_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Y_upstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Y_upstreamCap_Material", Vertex_Ybin_vector ,"h_CryoVertex_Y_upstreamCap_Material; [mm];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Y_barrel_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Y_barrel_Material", Vertex_Ybin_vector ,"h_CryoVertex_Y_barrel_Material; [mm];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Y_downstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Y_downstreamCap_Material", Vertex_Ybin_vector ,"h_CryoVertex_Y_downstreamCap_Material; [mm];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Y_downstreamConcaveCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Y_downstreamConcaveCap_Material", Vertex_Ybin_vector ,"h_CryoVertex_Y_downstreamConcaveCap_Material; [mm];Events");


PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z(                          "h_CryoVertex_Z", "Vertex_Z",                                 Vertex_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_TRUE(                     "h_CryoVertex_Z_TRUE", "Vertex_Z_TRUE",                       Vertex_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_upstreamCap(              "h_CryoVertex_Z_upstreamCap", "Vertex_Z",                     Vertex_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_upstreamCap_TRUE(         "h_CryoVertex_Z_upstreamCap_TRUE", "Vertex_Z_TRUE",           Vertex_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_barrel(                   "h_CryoVertex_Z_barrel", "Vertex_Z",                          Vertex_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_barrel_TRUE(              "h_CryoVertex_Z_barrel_TRUE", "Vertex_Z_TRUE",                Vertex_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_downstreamCap(            "h_CryoVertex_Z_downstreamCap", "Vertex_Z",                   Vertex_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_downstreamCap_TRUE(       "h_CryoVertex_Z_downstreamCap_TRUE", "Vertex_Z_TRUE",         Vertex_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_downstreamConcaveCap(     "h_CryoVertex_Z_downstreamConcaveCap", "Vertex_Z",            Vertex_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_downstreamConcaveCap_TRUE("h_CryoVertex_Z_downstreamConcaveCap_TRUE", "Vertex_Z_TRUE",  Vertex_Zbin_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_RCut(                          "h_CryoVertex_Z_RCut",                           "Vertex_Z",       Vertex_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_RCut_TRUE(                     "h_CryoVertex_Z_RCut_TRUE",                      "Vertex_Z_TRUE",  Vertex_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_RCut_upstreamCap(              "h_CryoVertex_Z_RCut_upstreamCap",               "Vertex_Z",       Vertex_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_RCut_upstreamCap_TRUE(         "h_CryoVertex_Z_RCut_upstreamCap_TRUE",          "Vertex_Z_TRUE",  Vertex_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_RCut_barrel(                   "h_CryoVertex_Z_RCut_barrel",                    "Vertex_Z",       Vertex_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_RCut_barrel_TRUE(              "h_CryoVertex_Z_RCut_barrel_TRUE",               "Vertex_Z_TRUE",  Vertex_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_RCut_downstreamCap(            "h_CryoVertex_Z_RCut_downstreamCap",             "Vertex_Z",       Vertex_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_RCut_downstreamCap_TRUE(       "h_CryoVertex_Z_RCut_downstreamCap_TRUE",        "Vertex_Z_TRUE",  Vertex_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_RCut_downstreamConcaveCap(     "h_CryoVertex_Z_RCut_downstreamConcaveCap",      "Vertex_Z",       Vertex_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_RCut_downstreamConcaveCap_TRUE("h_CryoVertex_Z_RCut_downstreamConcaveCap_TRUE", "Vertex_Z_TRUE",  Vertex_Zbin_vector , error_bands);


PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Z_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Z_Material", Vertex_Zbin_vector ,"h_CryoVertex_Z_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Z_upstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Z_upstreamCap_Material", Vertex_Zbin_vector ,"h_CryoVertex_Z_upstreamCap_Material; [mm];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Z_barrel_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Z_barrel_Material", Vertex_Zbin_vector ,"h_CryoVertex_Z_barrel_Material; [mm];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Z_downstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Z_downstreamCap_Material", Vertex_Zbin_vector ,"h_CryoVertex_Z_downstreamCap_Material; [mm];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Z_downstreamConcaveCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Z_downstreamConcaveCap_Material", Vertex_Zbin_vector ,"h_CryoVertex_Z_downstreamConcaveCap_Material; [mm];Events");




PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R("h_CryoVertex_R", "h_CryoVertex_R",  Vertex_Rbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_TRUE("h_CryoVertex_R_TRUE", "Vertex_R_TRUE",  Vertex_Rbin_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_upstreamCap(              "h_CryoVertex_R_upstreamCap",       "h_CryoVertex_R",         Vertex_Rbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_upstreamCap_TRUE(         "h_CryoVertex_R_upstreamCap_TRUE",  "Vertex_R_TRUE",          Vertex_Rbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_barrel(                   "h_CryoVertex_R_barrel",            "h_CryoVertex_R",         Vertex_Rbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_barrel_TRUE(              "h_CryoVertex_R_barrel_TRUE",       "Vertex_R_TRUE",          Vertex_Rbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_downstreamCap(            "h_CryoVertex_R_downstreamCap",     "h_CryoVertex_R",         Vertex_Rbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_downstreamCap_TRUE(       "h_CryoVertex_R_downstreamCap_TRUE", "Vertex_R_TRUE",         Vertex_Rbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_downstreamConcaveCap     ("h_CryoVertex_R_downstreamConcaveCap", "h_CryoVertex_R",      Vertex_Rbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_downstreamConcaveCap_TRUE("h_CryoVertex_R_downstreamConcaveCap_TRUE", "Vertex_R_TRUE",  Vertex_Rbin_vector , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_R_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_R_Material", Vertex_Rbin_vector ,"h_CryoVertex_R_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_R_upstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_R_upstreamCap_Material", Vertex_Rbin_vector ,"h_CryoVertex_R_upstreamCap_Material; [mm];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_R_barrel_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_R_barrel_Material", Vertex_Rbin_vector ,"h_CryoVertex_R_barrel_Material; [mm];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_R_downstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_R_downstreamCap_Material", Vertex_Rbin_vector ,"h_CryoVertex_R_downstreamCap_Material; [mm];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_R_downstreamConcaveCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_R_downstreamConcaveCap_Material", Vertex_Rbin_vector ,"h_CryoVertex_R_downstreamConcaveCap_Material; [mm];Events");



PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_InnerTank(                          "h_Distance_to_InnerTank",                           "nearest wall",       Distance_to_innerTank, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_InnerTank_TRUE(                     "h_Distance_to_InnerTank_TRUE",                      "TRU nearest wall",   Distance_to_innerTank, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_InnerTank_upstreamCap(              "h_Distance_to_InnerTank_upstreamCap",               "nearest wall",       Distance_to_innerTank, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_InnerTank_upstreamCap_TRUE(         "h_Distance_to_InnerTank_upstreamCap_TRUE",          "TRUE nearest wall",  Distance_to_innerTank, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_InnerTank_barrel(                   "h_Distance_to_InnerTank_barrel",                    "nearest wall",       Distance_to_innerTank, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_InnerTank_barrel_TRUE(              "h_Distance_to_InnerTank_barrel_TRUE",               "TRUE nearest wall",  Distance_to_innerTank, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_InnerTank_downstreamCap(            "h_Distance_to_InnerTank_downstreamCap",             "nearest wall",       Distance_to_innerTank, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_InnerTank_downstreamCap_TRUE(       "h_Distance_to_InnerTank_downstreamCap_TRUE",        "TRUE nearest wall",  Distance_to_innerTank, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_InnerTank_downstreamConcaveCap     ("h_Distance_to_InnerTank_downstreamConcaveCap",      "nearest wall",       Distance_to_innerTank, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_InnerTank_downstreamConcaveCap_TRUE("h_Distance_to_InnerTank_downstreamConcaveCap_TRUE", "TRUE nearest wall",  Distance_to_innerTank, error_bands);





PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Distance_to_InnerTank_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Distance_to_InnerTank_Material",  Distance_to_innerTank  ,"h_Distance_to_InnerTank_Material");


PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Distance_to_InnerTank_upstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Distance_to_InnerTank_upstreamCap_Material", Distance_to_innerTank ,"h_Distance_to_InnerTank_upstreamCap_Material; [mm];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Distance_to_InnerTank_barrel_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Distance_to_InnerTank_barrel_Material", Distance_to_innerTank ,"h_Distance_to_InnerTank_barrel_Material; [mm];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Distance_to_InnerTank_downstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Distance_to_InnerTank_downstreamCap_Material", Distance_to_innerTank ,"h_Distance_to_InnerTank_downstreamCap_Material; [mm];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Distance_to_InnerTank_downstreamConcaveCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Distance_to_InnerTank_downstreamConcaveCap_Material", Distance_to_innerTank ,"h_Distance_to_InnerTank_downstreamConcaveCap_Material; [mm];Events");



PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_upstreamCap(                          "h_Distance_to_upstreamCap",                           "h_Distance_to_upstreamCap",                            Distance_to_Caps, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_upstreamCap_TRUE(                     "h_Distance_to_upstreamCap_TRUE",                      "h_Distance_to_upstreamCap_TRUE",                       Distance_to_Caps, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_upstreamCap_upstreamCap(              "h_Distance_to_upstreamCap_upstreamCap",               "h_Distance_to_upstreamCap_upstreamCap",                Distance_to_Caps, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_upstreamCap_upstreamCap_TRUE(         "h_Distance_to_upstreamCap_upstreamCap_TRUE",          "h_Distance_to_upstreamCap_upstreamCap_TRUE",           Distance_to_Caps, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_upstreamCap_barrel(                   "h_Distance_to_upstreamCap_barrel",                    "h_Distance_to_upstreamCap_barrel",                     Distance_to_Caps, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_upstreamCap_barrel_TRUE(              "h_Distance_to_upstreamCap_barrel_TRUE",               "h_Distance_to_upstreamCap_barrel_TRUE",                Distance_to_Caps, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_upstreamCap_downstreamCap(            "h_Distance_to_upstreamCap_downstreamCap",             "h_Distance_to_upstreamCap_downstreamCap",              Distance_to_Caps, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_upstreamCap_downstreamCap_TRUE(       "h_Distance_to_upstreamCap_downstreamCap_TRUE",        "h_Distance_to_upstreamCap_downstreamCap_TRUE",         Distance_to_Caps, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_upstreamCap_downstreamConcaveCap(     "h_Distance_to_upstreamCap_downstreamConcaveCap",      "h_Distance_to_upstreamCap_downstreamConcaveCap",       Distance_to_Caps, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_upstreamCap_downstreamConcaveCap_TRUE("h_Distance_to_upstreamCap_downstreamConcaveCap_TRUE", "h_Distance_to_upstreamCap_downstreamConcaveCap_TRUE",  Distance_to_Caps, error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_upstreamCap_RCut(                          "h_Distance_to_upstreamCap_RCut",                           "h_Distance_to_upstreamCap_RCut",                            Distance_to_Caps, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_upstreamCap_RCut_TRUE(                     "h_Distance_to_upstreamCap_RCut_TRUE",                      "h_Distance_to_upstreamCap_RCut_TRUE",                       Distance_to_Caps, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_upstreamCap_RCut_upstreamCap(              "h_Distance_to_upstreamCap_RCut_upstreamCap",               "h_Distance_to_upstreamCap_RCut_upstreamCap",                Distance_to_Caps, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_upstreamCap_RCut_upstreamCap_TRUE(         "h_Distance_to_upstreamCap_RCut_upstreamCap_TRUE",          "h_Distance_to_upstreamCap_RCut_upstreamCap_TRUE",           Distance_to_Caps, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_upstreamCap_RCut_barrel(                   "h_Distance_to_upstreamCap_RCut_barrel",                    "h_Distance_to_upstreamCap_RCut_barrel",                     Distance_to_Caps, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_upstreamCap_RCut_barrel_TRUE(              "h_Distance_to_upstreamCap_RCut_barrel_TRUE",               "h_Distance_to_upstreamCap_RCut_barrel_TRUE",                Distance_to_Caps, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_upstreamCap_RCut_downstreamCap(            "h_Distance_to_upstreamCap_RCut_downstreamCap",             "h_Distance_to_upstreamCap_RCut_downstreamCap",              Distance_to_Caps, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_upstreamCap_RCut_downstreamCap_TRUE(       "h_Distance_to_upstreamCap_RCut_downstreamCap_TRUE",        "h_Distance_to_upstreamCap_RCut_downstreamCap_TRUE",         Distance_to_Caps, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_upstreamCap_RCut_downstreamConcaveCap(     "h_Distance_to_upstreamCap_RCut_downstreamConcaveCap",      "h_Distance_to_upstreamCap_RCut_downstreamConcaveCap",       Distance_to_Caps, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_upstreamCap_RCut_downstreamConcaveCap_TRUE("h_Distance_to_upstreamCap_RCut_downstreamConcaveCap_TRUE", "h_Distance_to_upstreamCap_RCut_downstreamConcaveCap_TRUE",  Distance_to_Caps, error_bands);


PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_downstreamCap(                          "h_Distance_to_downstreamCap",                           "h_Distance_to_downstreamCap",                            Distance_to_Caps, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_downstreamCap_TRUE(                     "h_Distance_to_downstreamCap_TRUE",                      "h_Distance_to_downstreamCap_TRUE",                       Distance_to_Caps, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_downstreamCap_upstreamCap(              "h_Distance_to_downstreamCap_upstreamCap",               "h_Distance_to_downstreamCap_upstreamCap",                Distance_to_Caps, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_downstreamCap_upstreamCap_TRUE(         "h_Distance_to_downstreamCap_upstreamCap_TRUE",          "h_Distance_to_downstreamCap_upstreamCap_TRUE",           Distance_to_Caps, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_downstreamCap_barrel(                   "h_Distance_to_downstreamCap_barrel",                    "h_Distance_to_downstreamCap_barrel",                     Distance_to_Caps, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_downstreamCap_barrel_TRUE(              "h_Distance_to_downstreamCap_barrel_TRUE",               "h_Distance_to_downstreamCap_barrel_TRUE",                Distance_to_Caps, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_downstreamCap_downstreamCap(            "h_Distance_to_downstreamCap_downstreamCap",             "h_Distance_to_downstreamCap_downstreamCap",              Distance_to_Caps, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_downstreamCap_downstreamCap_TRUE(       "h_Distance_to_downstreamCap_downstreamCap_TRUE",        "h_Distance_to_downstreamCap_downstreamCap_TRUE",         Distance_to_Caps, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_downstreamCap_downstreamConcaveCap(     "h_Distance_to_downstreamCap_downstreamConcaveCap",      "h_Distance_to_downstreamCap_downstreamConcaveCap",       Distance_to_Caps, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_downstreamCap_downstreamConcaveCap_TRUE("h_Distance_to_downstreamCap_downstreamConcaveCap_TRUE", "h_Distance_to_downstreamCap_downstreamConcaveCap_TRUE",  Distance_to_Caps, error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_downstreamCap_RCut(                          "h_Distance_to_downstreamCap_RCut",                           "h_Distance_to_downstreamCap_RCut",                            Distance_to_Caps, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_downstreamCap_RCut_TRUE(                     "h_Distance_to_downstreamCap_RCut_TRUE",                      "h_Distance_to_downstreamCap_RCut_TRUE",                       Distance_to_Caps, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_downstreamCap_RCut_upstreamCap(              "h_Distance_to_downstreamCap_RCut_upstreamCap",               "h_Distance_to_downstreamCap_RCut_upstreamCap",                Distance_to_Caps, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_downstreamCap_RCut_upstreamCap_TRUE(         "h_Distance_to_downstreamCap_RCut_upstreamCap_TRUE",          "h_Distance_to_downstreamCap_RCut_upstreamCap_TRUE",           Distance_to_Caps, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_downstreamCap_RCut_barrel(                   "h_Distance_to_downstreamCap_RCut_barrel",                    "h_Distance_to_downstreamCap_RCut_barrel",                     Distance_to_Caps, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_downstreamCap_RCut_barrel_TRUE(              "h_Distance_to_downstreamCap_RCut_barrel_TRUE",               "h_Distance_to_downstreamCap_RCut_barrel_TRUE",                Distance_to_Caps, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_downstreamCap_RCut_downstreamCap(            "h_Distance_to_downstreamCap_RCut_downstreamCap",             "h_Distance_to_downstreamCap_RCut_downstreamCap",              Distance_to_Caps, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_downstreamCap_RCut_downstreamCap_TRUE(       "h_Distance_to_downstreamCap_RCut_downstreamCap_TRUE",        "h_Distance_to_downstreamCap_RCut_downstreamCap_TRUE",         Distance_to_Caps, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_downstreamCap_RCut_downstreamConcaveCap(     "h_Distance_to_downstreamCap_RCut_downstreamConcaveCap",      "h_Distance_to_downstreamCap_RCut_downstreamConcaveCap",       Distance_to_Caps, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_downstreamCap_RCut_downstreamConcaveCap_TRUE("h_Distance_to_downstreamCap_RCut_downstreamConcaveCap_TRUE", "h_Distance_to_downstreamCap_RCut_downstreamConcaveCap_TRUE",  Distance_to_Caps, error_bands);

//MnvH2D *h_2d_2ndtrkLength_finerAngle    =    new MnvH2D("h_2d_2ndtrkLength_finerAngle", "h_2d_2ndtrkLength_finerAngle", Recoil_track_length_vector.size()-1, Recoil_track_length_vector.data(), bigAngle_bins_finner.size()-1, bigAngle_bins_finner.data());
////////////////////////////////////////
NormalParaFit_Map ZShifts;
//NormalParaFit_Map RShifts;


double stddev_offset_Start_vertexZ = 0.0; //30.0;
double stddev_offset_Finish_vertexZ = 24.0; //48.0;
int stddev_steps = 12;
double mean_offset_Start_vertexZ = -50; //30.0;
double mean_offset_Finish_vertexZ = 50.0; //48.0;
int mean_steps = 50; // reduced my half



FillConvolutionShiftMap(ZShifts, stddev_offset_Start_vertexZ, stddev_offset_Finish_vertexZ,
  stddev_steps, mean_offset_Start_vertexZ, mean_offset_Finish_vertexZ, mean_steps, true);



normal_distribution_Map Normal_distrubution_map;

int mapcount = 0;
//int NBinZ =NumZSteps;

//int NBinX =NumXSteps;
//int NBinY = NumYSteps;

typename std::map<Index3, Normal_Fit_Parameters>::const_iterator dog;
std::cout<<"~~~~~~~~~~~~~~~Checking Map for X and Y  ~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

for ( dog = ZShifts.begin(); dog != ZShifts.end();++dog)
{
std::cout<<" index = " << mapcount << " key (i,j,k) =  (" << dog->first.i <<" , "<< dog->first.j<< " , "<< dog->first.k  <<")   OffSet (mean, stddev) =  ( " << dog->second.mean << " , " << dog->second.stddev <<" ) "<<std::endl;
mapcount++;
Index3 ijk{dog->first.i,dog->first.j,dog->first.k};
std::normal_distribution<double> input(dog->second.mean, dog->second.stddev);
Normal_distrubution_map.insert(std::make_pair(ijk, input));
}
std::default_random_engine generator;

for ( dog = ZShifts.begin(); dog != ZShifts.end();++dog)
{
  Index3 ijk{dog->first.i,dog->first.j,dog->first.k};
  double shift = Normal_distrubution_map[ijk](generator);

std::cout<<" key (i,j,k) =  (" << dog->first.i <<" , "<< dog->first.j<< " , "<< dog->first.k  <<"shift = "<< shift << std::endl;

}

MnvH1D_Map Hist1D_Map_DistanceEdgeIsoR;
MnvH1D_3indexMap Hist1D_Map_DistanceEdgeIsoZ;

//MnvH1D_Map Hist_MapR;
MnvH1D_Map Hist_MapZ;
MnvH1D_Map Hist_Map_DistanceEdge;
MnvH2D_Map Hist_Map_Z_R;


// changing x,y,z
MnvH1D_3indexMap  Hist_3index_Map_X;
MnvH1D_3indexMap  Hist_3index_Map_Y;
MnvH1D_3indexMap  Hist_3index_Map_R;
MnvH1D_3indexMap  Hist_3index_Map_Z;
MnvH1D_3indexMap  Hist_3index_DistanceEdge;
MnvH1D_3indexMap  Hist_3index_Map_DistanceupstreamCap_RCut;
MnvH1D_3indexMap  Hist_3index_Map_DistancedownstreamCap_RCut;
MnvH1D_3indexMap  Hist_3index_Map_DistanceupstreamCap;
MnvH1D_3indexMap  Hist_3index_Map_DistancedownstreamCap;


MnvH1D_3indexMap  Hist_3index_Map_X_TRUE;
MnvH1D_3indexMap  Hist_3index_Map_Y_TRUE;
MnvH1D_3indexMap  Hist_3index_Map_R_TRUE;
MnvH1D_3indexMap  Hist_3index_Map_Z_TRUE;
MnvH1D_3indexMap  Hist_3index_Map_Z_RCut_TRUE;
MnvH1D_3indexMap  Hist_3index_Map_Z_RCut;
MnvH1D_3indexMap  Hist_3index_DistanceEdge_TRUE;
MnvH1D_3indexMap  Hist_3index_Map_DistanceupstreamCap_RCut_TRUE;
MnvH1D_3indexMap  Hist_3index_Map_DistancedownstreamCap_RCut_TRUE;
MnvH1D_3indexMap  Hist_3index_Map_DistanceupstreamCap_TRUE;
MnvH1D_3indexMap  Hist_3index_Map_DistancedownstreamCap_TRUE;

MnvH1D_3indexMap  Hist_3index_Map_X_upstreamCap;
MnvH1D_3indexMap  Hist_3index_Map_Y_upstreamCap;
MnvH1D_3indexMap  Hist_3index_Map_R_upstreamCap;
MnvH1D_3indexMap  Hist_3index_Map_Z_upstreamCap;
MnvH1D_3indexMap  Hist_3index_DistanceEdge_upstreamCap;
MnvH1D_3indexMap  Hist_3index_Map_DistanceupstreamCap_upstream_RCut;
MnvH1D_3indexMap  Hist_3index_Map_DistancedownstreamCap_upstream_RCut;
MnvH1D_3indexMap  Hist_3index_Map_DistanceupstreamCap_upstream;
MnvH1D_3indexMap  Hist_3index_Map_DistancedownstreamCap_upstream;

MnvH1D_3indexMap  Hist_3index_Map_X_upstreamCap_TRUE;
MnvH1D_3indexMap  Hist_3index_Map_Y_upstreamCap_TRUE;
MnvH1D_3indexMap  Hist_3index_Map_R_upstreamCap_TRUE;
MnvH1D_3indexMap  Hist_3index_Map_Z_upstreamCap_TRUE;
MnvH1D_3indexMap  Hist_3index_Map_Z_RCut_upstreamCap_TRUE;
MnvH1D_3indexMap  Hist_3index_Map_Z_RCut_upstreamCap;
MnvH1D_3indexMap  Hist_3index_DistanceEdge_upstreamCap_TRUE;
MnvH1D_3indexMap  Hist_3index_Map_DistanceupstreamCap_upstream_RCut_TRUE;
MnvH1D_3indexMap  Hist_3index_Map_DistancedownstreamCap_upstream_RCut_TRUE;
MnvH1D_3indexMap  Hist_3index_Map_DistanceupstreamCap_upstream_TRUE;
MnvH1D_3indexMap  Hist_3index_Map_DistancedownstreamCap_upstream_TRUE;

MnvH1D_3indexMap  Hist_3index_muonE_upstreamCap;
MnvH1D_3indexMap  Hist_3index_PT_upstreamCap;
MnvH1D_3indexMap  Hist_3index_PZ_upstreamCap;
MnvH1D_3indexMap  Hist_3index_muontheta_upstreamCap;
MnvH1D_3indexMap  Hist_3index_muonDoca_upstreamCap;
MnvH1D_3indexMap  Hist_3index_recoilDoca_upstreamCap;
MnvH1D_3indexMap  Hist_3index_Tracklength_upstreamCap;


MnvH1D_3indexMap  Hist_3index_Map_X_barrel;
MnvH1D_3indexMap  Hist_3index_Map_Y_barrel;
MnvH1D_3indexMap  Hist_3index_Map_R_barrel;
MnvH1D_3indexMap  Hist_3index_Map_Z_barrel;
MnvH1D_3indexMap  Hist_3index_DistanceEdge_barrel;
MnvH1D_3indexMap  Hist_3index_Map_DistanceupstreamCap_barrel_RCut;
MnvH1D_3indexMap  Hist_3index_Map_DistancedownstreamCap_barrel_RCut;
MnvH1D_3indexMap  Hist_3index_Map_DistanceupstreamCap_barrel;
MnvH1D_3indexMap  Hist_3index_Map_DistancedownstreamCap_barrel;


MnvH1D_3indexMap  Hist_3index_Map_X_barrel_TRUE;
MnvH1D_3indexMap  Hist_3index_Map_Y_barrel_TRUE;
MnvH1D_3indexMap  Hist_3index_Map_R_barrel_TRUE;
MnvH1D_3indexMap  Hist_3index_Map_Z_barrel_TRUE;
MnvH1D_3indexMap  Hist_3index_Map_Z_RCut_barrel_TRUE;
MnvH1D_3indexMap  Hist_3index_Map_Z_RCut_barrel;
MnvH1D_3indexMap  Hist_3index_DistanceEdge_barrel_TRUE;
MnvH1D_3indexMap  Hist_3index_Map_DistanceupstreamCap_barrel_RCut_TRUE;
MnvH1D_3indexMap  Hist_3index_Map_DistancedownstreamCap_barrel_RCut_TRUE;
MnvH1D_3indexMap  Hist_3index_Map_DistanceupstreamCap_barrel_TRUE;
MnvH1D_3indexMap  Hist_3index_Map_DistancedownstreamCap_barrel_TRUE;

//MnvH1D_3indexMap  Hist_3index_PT_barrel;
//MnvH1D_3indexMap  Hist_3index_PZ_barrel;
//MnvH1D_3indexMap  Hist_3index_muonE_barrel;
//MnvH1D_3indexMap  Hist_3index_muontheta_barrel;
//MnvH1D_3indexMap  Hist_3index_muonDoca_barrel;
//MnvH1D_3indexMap  Hist_3index_recoilDoca_barrel;
//MnvH1D_3indexMap  Hist_3index_Tracklength_barrel;

MnvH1D_3indexMap  Hist_3index_Map_X_downstreamCap;
MnvH1D_3indexMap  Hist_3index_Map_Y_downstreamCap;
MnvH1D_3indexMap  Hist_3index_Map_R_downstreamCap;
MnvH1D_3indexMap  Hist_3index_Map_Z_downstreamCap;
MnvH1D_3indexMap  Hist_3index_DistanceEdge_downstreamCap;
MnvH1D_3indexMap  Hist_3index_Map_DistanceupstreamCap_downstreamCap_RCut;
MnvH1D_3indexMap  Hist_3index_Map_DistancedownstreamCap_downstreamCap_RCut;
MnvH1D_3indexMap  Hist_3index_Map_DistanceupstreamCap_downstreamCap;
MnvH1D_3indexMap  Hist_3index_Map_DistancedownstreamCap_downstreamCap;


MnvH1D_3indexMap  Hist_3index_Map_X_downstreamCap_TRUE;
MnvH1D_3indexMap  Hist_3index_Map_Y_downstreamCap_TRUE;
MnvH1D_3indexMap  Hist_3index_Map_R_downstreamCap_TRUE;
MnvH1D_3indexMap  Hist_3index_Map_Z_downstreamCap_TRUE;
MnvH1D_3indexMap  Hist_3index_Map_Z_RCut_downstreamCap_TRUE;
MnvH1D_3indexMap  Hist_3index_Map_Z_RCut_downstreamCap;
MnvH1D_3indexMap  Hist_3index_DistanceEdge_downstreamCap_TRUE;
MnvH1D_3indexMap  Hist_3index_Map_DistanceupstreamCap_downstreamCap_RCut_TRUE;
MnvH1D_3indexMap  Hist_3index_Map_DistancedownstreamCap_downstreamCap_RCut_TRUE;
MnvH1D_3indexMap  Hist_3index_Map_DistanceupstreamCap_downstreamCap_TRUE;
MnvH1D_3indexMap  Hist_3index_Map_DistancedownstreamCap_downstreamCap_TRUE;
//MnvH1D_3indexMap  Hist_3index_PT_downstreamCap;
//MnvH1D_3indexMap  Hist_3index_muonE_downstreamCap;
//MnvH1D_3indexMap  Hist_3index_PZ_downstreamCap;
//MnvH1D_3indexMap  Hist_3index_muontheta_downstreamCap;
//MnvH1D_3indexMap  Hist_3index_muonDoca_downstreamCap;
//MnvH1D_3indexMap  Hist_3index_recoilDoca_downstreamCap;
//MnvH1D_3indexMap  Hist_3index_Tracklength_downstreamCap;


MnvH1D_3indexMap  Hist_3index_Map_X_downstreamconcavecap;
MnvH1D_3indexMap  Hist_3index_Map_Y_downstreamconcavecap;
MnvH1D_3indexMap  Hist_3index_Map_R_downstreamconcavecap;
MnvH1D_3indexMap  Hist_3index_Map_Z_downstreamconcavecap;
MnvH1D_3indexMap  Hist_3index_DistanceEdge_downstreamconcavecap;
MnvH1D_3indexMap  Hist_3index_Map_DistanceupstreamCap_downstreamconcavecap_RCut;
MnvH1D_3indexMap  Hist_3index_Map_DistancedownstreamCap_downstreamconcavecap_RCut;
MnvH1D_3indexMap  Hist_3index_Map_DistanceupstreamCap_downstreamconcavecap;
MnvH1D_3indexMap  Hist_3index_Map_DistancedownstreamCap_downstreamconcavecap;


MnvH1D_3indexMap  Hist_3index_Map_X_downstreamconcavecap_TRUE;
MnvH1D_3indexMap  Hist_3index_Map_Y_downstreamconcavecap_TRUE;
MnvH1D_3indexMap  Hist_3index_Map_R_downstreamconcavecap_TRUE;
MnvH1D_3indexMap  Hist_3index_Map_Z_downstreamconcavecap_TRUE;
MnvH1D_3indexMap  Hist_3index_Map_Z_RCut_downstreamconcavecap_TRUE;
MnvH1D_3indexMap  Hist_3index_Map_Z_RCut_downstreamconcavecap;
MnvH1D_3indexMap  Hist_3index_DistanceEdge_downstreamconcavecap_TRUE;
MnvH1D_3indexMap  Hist_3index_Map_DistanceupstreamCap_downstreamconcavecap_RCut_TRUE;
MnvH1D_3indexMap  Hist_3index_Map_DistancedownstreamCap_downstreamconcavecap_RCut_TRUE;
MnvH1D_3indexMap  Hist_3index_Map_DistanceupstreamCap_downstreamconcavecap_TRUE;
MnvH1D_3indexMap  Hist_3index_Map_DistancedownstreamCap_downstreamconcavecap_TRUE;

////////////////////////////
//// hist Folio for material type
///////////////////////////


HistFolio_material_type_3indexMap HistFolio_3index_Map_X_upstreamcap;
HistFolio_material_type_3indexMap HistFolio_3index_Map_Y_upstreamcap;
HistFolio_material_type_3indexMap HistFolio_3index_Map_Z_upstreamcap;
HistFolio_material_type_3indexMap HistFolio_3index_Map_R_upstreamcap;

HistFolio_material_type_3indexMap HistFolio_3index_Map_X_barrel;
HistFolio_material_type_3indexMap HistFolio_3index_Map_Y_barrel;
HistFolio_material_type_3indexMap HistFolio_3index_Map_Z_barrel;
HistFolio_material_type_3indexMap HistFolio_3index_Map_R_barrel;


HistFolio_material_type_3indexMap HistFolio_3index_Map_X_downstreamcap;
HistFolio_material_type_3indexMap HistFolio_3index_Map_Y_downstreamcap;
HistFolio_material_type_3indexMap HistFolio_3index_Map_Z_downstreamcap;
HistFolio_material_type_3indexMap HistFolio_3index_Map_R_downstreamcap;



HistFolio_material_type_3indexMap HistFolio_3index_Map_X_downstreamconcavecap;
HistFolio_material_type_3indexMap HistFolio_3index_Map_Y_downstreamconcavecap;
HistFolio_material_type_3indexMap HistFolio_3index_Map_Z_downstreamconcavecap;
HistFolio_material_type_3indexMap HistFolio_3index_Map_R_downstreamconcavecap;

std::cout<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;
std::cout<< "~~~~~~~~~~initialize Histograms~~~~~~~~~~ "<< std::endl;
std::cout<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;

//changing Z


  char tempName[1024];
  char tempName_2[1024];






std::cout<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;
std::cout<< "~~~~~~~~~~initialize Histograms~~~~~~~~~~ "<< std::endl;
std::cout<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;



int fillHisindex = 0;

  for ( dog = ZShifts.begin(); dog != ZShifts.end();++dog)
  {

    int i = dog->first.i;
    int j = dog->first.j;
    int k = dog->first.k;

    Index3 ijk{dog->first.i,dog->first.j,dog->first.k};


    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_Y", i,j,k);
    PlotUtils::MnvH1D *hist_Y = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Ybin_vector.size()-1,Vertex_Ybin_vector.data());
    Hist_3index_Map_Y.insert(std::make_pair(ijk, hist_Y ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_X", i,j,k);
    PlotUtils::MnvH1D *hist_X = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Xbin_vector.size()-1,Vertex_Xbin_vector.data());
    Hist_3index_Map_X.insert(std::make_pair(ijk, hist_X ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_R", i,j,k);
    PlotUtils::MnvH1D *hist_R = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Rbin_vector.size()-1,Vertex_Rbin_vector.data());
    Hist_3index_Map_R.insert(std::make_pair(ijk, hist_R ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_Z", i,j,k);
    PlotUtils::MnvH1D *hist_Z = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Zbin_vector.size()-1,Vertex_Zbin_vector.data());
    Hist_3index_Map_Z.insert(std::make_pair(ijk, hist_Z ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_DistanceEdge", i,j,k);
    PlotUtils::MnvH1D *hist_DistanceEdge = new PlotUtils::MnvH1D(tempName, tempName, Distance_to_innerTank.size()-1,Distance_to_innerTank.data());
    Hist_3index_DistanceEdge.insert(std::make_pair(ijk, hist_DistanceEdge ));


    //////////////////////////////////
    //// TRUTH
    ////////////////////////////

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_Y_TRUE", i,j,k);
    PlotUtils::MnvH1D *hist_Y_TRUE = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Ybin_vector.size()-1,Vertex_Ybin_vector.data());
    Hist_3index_Map_Y_TRUE.insert(std::make_pair(ijk, hist_Y_TRUE ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_X_TRUE", i,j,k);
    PlotUtils::MnvH1D *hist_X_TRUE = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Xbin_vector.size()-1,Vertex_Xbin_vector.data());
    Hist_3index_Map_X_TRUE.insert(std::make_pair(ijk, hist_X_TRUE ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_R_TRUE", i,j,k);
    PlotUtils::MnvH1D *hist_R_TRUE = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Rbin_vector.size()-1,Vertex_Rbin_vector.data());
    Hist_3index_Map_R_TRUE.insert(std::make_pair(ijk, hist_R_TRUE ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_Z_TRUE", i,j,k);
    PlotUtils::MnvH1D *hist_Z_TRUE = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Zbin_vector.size()-1,Vertex_Zbin_vector.data());
    Hist_3index_Map_Z_TRUE.insert(std::make_pair(ijk, hist_Z_TRUE ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_Z_RCut_TRUE", i,j,k);
    PlotUtils::MnvH1D *hist_Z_RCut_TRUE = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Zbin_vector.size()-1,Vertex_Zbin_vector.data());
    Hist_3index_Map_Z_RCut_TRUE.insert(std::make_pair(ijk, hist_Z_RCut_TRUE ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_Z_RCut", i,j,k);
    PlotUtils::MnvH1D *hist_Z_RCut = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Zbin_vector.size()-1,Vertex_Zbin_vector.data());
    Hist_3index_Map_Z_RCut.insert(std::make_pair(ijk, hist_Z_RCut ));


    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_DistanceEdge_TRUE", i,j,k);
    PlotUtils::MnvH1D *hist_DistanceEdge_TRUE = new PlotUtils::MnvH1D(tempName, tempName, Distance_to_innerTank.size()-1,Distance_to_innerTank.data());
    Hist_3index_DistanceEdge_TRUE.insert(std::make_pair(ijk, hist_DistanceEdge_TRUE ));
    /////////////////////////////////////////////////////////////////////////////////
    //// upstream
    //////////////////////////////////////////////////////////////////////////////

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_X_upstreamCap", i,j,k);
    PlotUtils::MnvH1D *hist_X_upstreamCap = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Xbin_vector.size()-1,Vertex_Xbin_vector.data());
    Hist_3index_Map_X_upstreamCap.insert(std::make_pair(ijk, hist_X_upstreamCap ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_Y_upstreamCap", i,j,k);
    PlotUtils::MnvH1D *hist_Y_upstreamCap = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Ybin_vector.size()-1,Vertex_Ybin_vector.data());
    Hist_3index_Map_Y_upstreamCap.insert(std::make_pair(ijk, hist_Y_upstreamCap ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_R_upstreamCap", i,j,k);
    PlotUtils::MnvH1D *hist_R_upstreamCap = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Rbin_vector.size()-1,Vertex_Rbin_vector.data());
    Hist_3index_Map_R_upstreamCap.insert(std::make_pair(ijk, hist_R_upstreamCap ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_Z_upstreamCap", i,j,k);
    PlotUtils::MnvH1D *hist_Z_upstreamCap = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Zbin_vector.size()-1,Vertex_Zbin_vector.data());
    Hist_3index_Map_Z_upstreamCap.insert(std::make_pair(ijk, hist_Z_upstreamCap ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_Map_DistanceEdge_upstreamCap", i,j,k);
    PlotUtils::MnvH1D *hist_edge_upstreamCap = new PlotUtils::MnvH1D(tempName, tempName, Distance_to_innerTank.size()-1,Distance_to_innerTank.data());
    Hist_3index_DistanceEdge_upstreamCap.insert(std::make_pair(ijk, hist_edge_upstreamCap ));

    ////////////////////////
    //// TRUTH
    //////////////////////

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_X_upstreamCap_TRUE", i,j,k);
    PlotUtils::MnvH1D *hist_X_upstreamCap_TRUE = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Xbin_vector.size()-1,Vertex_Xbin_vector.data());
    Hist_3index_Map_X_upstreamCap_TRUE.insert(std::make_pair(ijk, hist_X_upstreamCap_TRUE ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_Y_upstreamCap_TRUE", i,j,k);
    PlotUtils::MnvH1D *hist_Y_upstreamCap_TRUE = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Ybin_vector.size()-1,Vertex_Ybin_vector.data());
    Hist_3index_Map_Y_upstreamCap_TRUE.insert(std::make_pair(ijk, hist_Y_upstreamCap_TRUE ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_R_upstreamCap_TRUE", i,j,k);
    PlotUtils::MnvH1D *hist_R_upstreamCap_TRUE = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Rbin_vector.size()-1,Vertex_Rbin_vector.data());
    Hist_3index_Map_R_upstreamCap_TRUE.insert(std::make_pair(ijk, hist_R_upstreamCap_TRUE ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_Z_upstreamCap_TRUE", i,j,k);
    PlotUtils::MnvH1D *hist_Z_upstreamCap_TRUE = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Zbin_vector.size()-1,Vertex_Zbin_vector.data());
    Hist_3index_Map_Z_upstreamCap_TRUE.insert(std::make_pair(ijk, hist_Z_upstreamCap_TRUE ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_Z_RCut_upstreamCap_TRUE", i,j,k);
    PlotUtils::MnvH1D *hist_Z_upstreamCap_RCut_TRUE = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Zbin_vector.size()-1,Vertex_Zbin_vector.data());
    Hist_3index_Map_Z_RCut_upstreamCap_TRUE.insert(std::make_pair(ijk, hist_Z_upstreamCap_RCut_TRUE ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_Z_RCut_upstreamCap", i,j,k);
    PlotUtils::MnvH1D *hist_Z_upstreamCap_RCut = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Zbin_vector.size()-1,Vertex_Zbin_vector.data());
    Hist_3index_Map_Z_RCut_upstreamCap.insert(std::make_pair(ijk, hist_Z_upstreamCap_RCut ));



    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_Map_DistanceEdge_upstreamCap_TRUE", i,j,k);
    PlotUtils::MnvH1D *hist_edge_upstreamCap_TRUE = new PlotUtils::MnvH1D(tempName, tempName, Distance_to_innerTank.size()-1,Distance_to_innerTank.data());
    Hist_3index_DistanceEdge_upstreamCap_TRUE.insert(std::make_pair(ijk, hist_edge_upstreamCap_TRUE ));


//////////////////////////////////////
/// RCut , distance to caps upstream and downstream
////////////////////////////////////

    sprintf(tempName,"%s_i_j_k_%d_%d_%d", "h_Map_DistanceupstreamCap_RCut", i,j,k);
    PlotUtils::MnvH1D *hist_Distance_upstreamCap_RCut= new PlotUtils::MnvH1D(tempName, tempName, Distance_to_Caps.size()-1,Distance_to_Caps.data());
    Hist_3index_Map_DistanceupstreamCap_RCut.insert(std::make_pair(ijk, hist_Distance_upstreamCap_RCut ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d", "h_Map_DistancedownstreamCap_RCut", i,j,k);
    PlotUtils::MnvH1D *hist_Distance_downstreamCap_RCut = new PlotUtils::MnvH1D(tempName, tempName, Distance_to_Caps.size()-1,Distance_to_Caps.data());
    Hist_3index_Map_DistancedownstreamCap_RCut.insert(std::make_pair(ijk, hist_Distance_downstreamCap_RCut ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d", "h_Map_DistanceupstreamCap_RCut_TRUE", i,j,k);
    PlotUtils::MnvH1D *hist_Distance_upstreamCap_TRUE_RCut = new PlotUtils::MnvH1D(tempName, tempName, Distance_to_Caps.size()-1,Distance_to_Caps.data());
    Hist_3index_Map_DistanceupstreamCap_RCut_TRUE.insert(std::make_pair(ijk, hist_Distance_upstreamCap_TRUE_RCut ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d", "h_Map_DistancedownstreamCap_RCut_TRUE", i,j,k);
    PlotUtils::MnvH1D *hist_Distance_downstreamCap_TRUE_RCut = new PlotUtils::MnvH1D(tempName, tempName, Distance_to_Caps.size()-1,Distance_to_Caps.data());
    Hist_3index_Map_DistancedownstreamCap_RCut_TRUE.insert(std::make_pair(ijk, hist_Distance_downstreamCap_TRUE_RCut ));


    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_Map_DistanceupstreamCap_RCut_upstreamCap", i,j,k);
    PlotUtils::MnvH1D *hist_upstream_Distance_upstreamCap_RCut= new PlotUtils::MnvH1D(tempName, tempName, Distance_to_Caps.size()-1,Distance_to_Caps.data());
    Hist_3index_Map_DistanceupstreamCap_upstream_RCut.insert(std::make_pair(ijk, hist_upstream_Distance_upstreamCap_RCut ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_Map_DistancedownstreamCap_RCut_upstreamCap", i,j,k);
    PlotUtils::MnvH1D *hist_upstream_Distance_downstreamCap_RCut = new PlotUtils::MnvH1D(tempName, tempName, Distance_to_Caps.size()-1,Distance_to_Caps.data());
    Hist_3index_Map_DistancedownstreamCap_upstream_RCut.insert(std::make_pair(ijk, hist_upstream_Distance_downstreamCap_RCut ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_Map_DistanceupstreamCap_RCut_upstreamCap_TRUE", i,j,k);
    PlotUtils::MnvH1D *hist_upstream_Distance_upstreamCap_TRUE_RCut = new PlotUtils::MnvH1D(tempName, tempName, Distance_to_Caps.size()-1,Distance_to_Caps.data());
    Hist_3index_Map_DistanceupstreamCap_upstream_RCut_TRUE.insert(std::make_pair(ijk, hist_upstream_Distance_upstreamCap_TRUE_RCut ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_Map_DistancedownstreamCap_RCut_upstreamCap_TRUE", i,j,k);
    PlotUtils::MnvH1D *hist_upstream_Distance_downstreamCap_TRUE_RCut = new PlotUtils::MnvH1D(tempName, tempName, Distance_to_Caps.size()-1,Distance_to_Caps.data());
    Hist_3index_Map_DistancedownstreamCap_upstream_RCut_TRUE.insert(std::make_pair(ijk, hist_upstream_Distance_downstreamCap_TRUE_RCut ));
    //

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_Map_DistanceupstreamCap_RCut_barrel", i,j,k);
    PlotUtils::MnvH1D *hist_barrel_Distance_upstreamCap_RCut= new PlotUtils::MnvH1D(tempName, tempName, Distance_to_Caps.size()-1,Distance_to_Caps.data());
    Hist_3index_Map_DistanceupstreamCap_barrel_RCut.insert(std::make_pair(ijk, hist_barrel_Distance_upstreamCap_RCut ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_Map_DistancedownstreamCap_RCut_barrel", i,j,k);
    PlotUtils::MnvH1D *hist_barrel_Distance_downstreamCap_RCut = new PlotUtils::MnvH1D(tempName, tempName, Distance_to_Caps.size()-1,Distance_to_Caps.data());
    Hist_3index_Map_DistancedownstreamCap_barrel_RCut.insert(std::make_pair(ijk, hist_barrel_Distance_downstreamCap_RCut ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_Map_DistanceupstreamCap_RCut_barrel_TRUE", i,j,k);
    PlotUtils::MnvH1D *hist_barrel_Distance_upstreamCap_TRUE_RCut = new PlotUtils::MnvH1D(tempName, tempName, Distance_to_Caps.size()-1,Distance_to_Caps.data());
    Hist_3index_Map_DistanceupstreamCap_barrel_RCut_TRUE.insert(std::make_pair(ijk, hist_barrel_Distance_upstreamCap_TRUE_RCut ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_Map_DistancedownstreamCap_RCut_barrel_TRUE", i,j,k);
    PlotUtils::MnvH1D *hist_barrel_Distance_downstreamCap_TRUE_RCut = new PlotUtils::MnvH1D(tempName, tempName, Distance_to_Caps.size()-1,Distance_to_Caps.data());
    Hist_3index_Map_DistancedownstreamCap_barrel_RCut_TRUE.insert(std::make_pair(ijk, hist_barrel_Distance_downstreamCap_TRUE_RCut ));

  //

  sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_Map_DistanceupstreamCap_RCut_downstreamCap", i,j,k);
  PlotUtils::MnvH1D *hist_downstreamCap_Distance_upstreamCap_RCut= new PlotUtils::MnvH1D(tempName, tempName, Distance_to_Caps.size()-1,Distance_to_Caps.data());
  Hist_3index_Map_DistanceupstreamCap_downstreamCap_RCut.insert(std::make_pair(ijk, hist_downstreamCap_Distance_upstreamCap_RCut ));

  sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_Map_DistancedownstreamCap_RCut_downstreamCap", i,j,k);
  PlotUtils::MnvH1D *hist_downstreamCap_Distance_downstreamCap_RCut = new PlotUtils::MnvH1D(tempName, tempName, Distance_to_Caps.size()-1,Distance_to_Caps.data());
  Hist_3index_Map_DistancedownstreamCap_downstreamCap_RCut.insert(std::make_pair(ijk, hist_downstreamCap_Distance_downstreamCap_RCut ));

  sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_Map_DistanceupstreamCap_RCut_downstreamCap_TRUE", i,j,k);
  PlotUtils::MnvH1D *hist_downstreamCap_Distance_upstreamCap_TRUE_RCut = new PlotUtils::MnvH1D(tempName, tempName, Distance_to_Caps.size()-1,Distance_to_Caps.data());
  Hist_3index_Map_DistanceupstreamCap_downstreamCap_RCut_TRUE.insert(std::make_pair(ijk, hist_downstreamCap_Distance_upstreamCap_TRUE_RCut ));

  sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_Map_DistancedownstreamCap_RCut_downstreamCap_TRUE", i,j,k);
  PlotUtils::MnvH1D *hist_downstreamCap_Distance_downstreamCap_TRUE_RCut = new PlotUtils::MnvH1D(tempName, tempName, Distance_to_Caps.size()-1,Distance_to_Caps.data());
  Hist_3index_Map_DistancedownstreamCap_downstreamCap_RCut_TRUE.insert(std::make_pair(ijk, hist_downstreamCap_Distance_downstreamCap_TRUE_RCut ));
//

//

sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_Map_DistanceupstreamCap_RCut_downstreamConcaveCap", i,j,k);
PlotUtils::MnvH1D *hist_downstreamconcavecap_Distance_upstreamCap_RCut= new PlotUtils::MnvH1D(tempName, tempName, Distance_to_Caps.size()-1,Distance_to_Caps.data());
Hist_3index_Map_DistanceupstreamCap_downstreamconcavecap_RCut.insert(std::make_pair(ijk, hist_downstreamconcavecap_Distance_upstreamCap_RCut ));

sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_Map_DistancedownstreamCap_RCut_downstreamConcaveCap", i,j,k);
PlotUtils::MnvH1D *hist_downstreamconcavecap_Distance_downstreamCap_RCut = new PlotUtils::MnvH1D(tempName, tempName, Distance_to_Caps.size()-1,Distance_to_Caps.data());
Hist_3index_Map_DistancedownstreamCap_downstreamconcavecap_RCut.insert(std::make_pair(ijk, hist_downstreamconcavecap_Distance_downstreamCap_RCut ));

sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_Map_DistanceupstreamCap_RCut_downstreamConcaveCap_TRUE", i,j,k);
PlotUtils::MnvH1D *hist_downstreamconcavecap_Distance_upstreamCap_TRUE_RCut = new PlotUtils::MnvH1D(tempName, tempName, Distance_to_Caps.size()-1,Distance_to_Caps.data());
Hist_3index_Map_DistanceupstreamCap_downstreamconcavecap_RCut_TRUE.insert(std::make_pair(ijk, hist_downstreamconcavecap_Distance_upstreamCap_TRUE_RCut ));

sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_Map_DistancedownstreamCap_RCut_downstreamConcaveCap_TRUE", i,j,k);
PlotUtils::MnvH1D *hist_downstreamconcavecap_Distance_downstreamCap_TRUE_RCut = new PlotUtils::MnvH1D(tempName, tempName, Distance_to_Caps.size()-1,Distance_to_Caps.data());
Hist_3index_Map_DistancedownstreamCap_downstreamconcavecap_RCut_TRUE.insert(std::make_pair(ijk, hist_downstreamconcavecap_Distance_downstreamCap_TRUE_RCut ));
/////////////////////////////////////
//// no RCut applied
////////////////////////////////////

sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_Map_DistanceupstreamCap", i,j,k);
PlotUtils::MnvH1D *hist_Distance_upstreamCap= new PlotUtils::MnvH1D(tempName, tempName, Distance_to_Caps.size()-1,Distance_to_Caps.data());
Hist_3index_Map_DistanceupstreamCap.insert(std::make_pair(ijk, hist_Distance_upstreamCap ));

sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_Map_DistancedownstreamCap", i,j,k);
PlotUtils::MnvH1D *hist_Distance_downstreamCap = new PlotUtils::MnvH1D(tempName, tempName, Distance_to_Caps.size()-1,Distance_to_Caps.data());
Hist_3index_Map_DistancedownstreamCap.insert(std::make_pair(ijk, hist_Distance_downstreamCap ));

sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_Map_DistanceupstreamCap_TRUE", i,j,k);
PlotUtils::MnvH1D *hist_Distance_upstreamCap_TRUE = new PlotUtils::MnvH1D(tempName, tempName, Distance_to_Caps.size()-1,Distance_to_Caps.data());
Hist_3index_Map_DistanceupstreamCap_TRUE.insert(std::make_pair(ijk, hist_Distance_upstreamCap_TRUE ));

sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_Map_DistancedownstreamCap_TRUE", i,j,k);
PlotUtils::MnvH1D *hist_Distance_downstreamCap_TRUE = new PlotUtils::MnvH1D(tempName, tempName, Distance_to_Caps.size()-1,Distance_to_Caps.data());
Hist_3index_Map_DistancedownstreamCap_TRUE.insert(std::make_pair(ijk, hist_Distance_downstreamCap_TRUE ));

//

sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_Map_DistanceupstreamCap_upstreamCap", i,j,k);
PlotUtils::MnvH1D *hist_upstream_Distance_upstreamCap= new PlotUtils::MnvH1D(tempName, tempName, Distance_to_Caps.size()-1,Distance_to_Caps.data());
Hist_3index_Map_DistanceupstreamCap_upstream.insert(std::make_pair(ijk, hist_upstream_Distance_upstreamCap ));

sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_Map_DistancedownstreamCap_upstreamCap", i,j,k);
PlotUtils::MnvH1D *hist_upstream_Distance_downstreamCap = new PlotUtils::MnvH1D(tempName, tempName, Distance_to_Caps.size()-1,Distance_to_Caps.data());
Hist_3index_Map_DistancedownstreamCap_upstream.insert(std::make_pair(ijk, hist_upstream_Distance_downstreamCap ));

sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_Map_DistanceupstreamCap_upstreamCap_TRUE", i,j,k);
PlotUtils::MnvH1D *hist_upstream_Distance_upstreamCap_TRUE = new PlotUtils::MnvH1D(tempName, tempName, Distance_to_Caps.size()-1,Distance_to_Caps.data());
Hist_3index_Map_DistanceupstreamCap_upstream_TRUE.insert(std::make_pair(ijk, hist_upstream_Distance_upstreamCap_TRUE ));

sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_Map_DistancedownstreamCap_upstreamCap_TRUE", i,j,k);
PlotUtils::MnvH1D *hist_upstream_Distance_downstreamCap_TRUE = new PlotUtils::MnvH1D(tempName, tempName, Distance_to_Caps.size()-1,Distance_to_Caps.data());
Hist_3index_Map_DistancedownstreamCap_upstream_TRUE.insert(std::make_pair(ijk, hist_upstream_Distance_downstreamCap_TRUE ));
//

sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_Map_DistanceupstreamCap_barrel", i,j,k);
PlotUtils::MnvH1D *hist_barrel_Distance_upstreamCap= new PlotUtils::MnvH1D(tempName, tempName, Distance_to_Caps.size()-1,Distance_to_Caps.data());
Hist_3index_Map_DistanceupstreamCap_barrel.insert(std::make_pair(ijk, hist_barrel_Distance_upstreamCap ));

sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_Map_DistancedownstreamCap_barrel", i,j,k);
PlotUtils::MnvH1D *hist_barrel_Distance_downstreamCap = new PlotUtils::MnvH1D(tempName, tempName, Distance_to_Caps.size()-1,Distance_to_Caps.data());
Hist_3index_Map_DistancedownstreamCap_barrel.insert(std::make_pair(ijk, hist_barrel_Distance_downstreamCap ));

sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_Map_DistanceupstreamCap_barrel_TRUE", i,j,k);
PlotUtils::MnvH1D *hist_barrel_Distance_upstreamCap_TRUE = new PlotUtils::MnvH1D(tempName, tempName, Distance_to_Caps.size()-1,Distance_to_Caps.data());
Hist_3index_Map_DistanceupstreamCap_barrel_TRUE.insert(std::make_pair(ijk, hist_barrel_Distance_upstreamCap_TRUE ));

sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_Map_DistancedownstreamCap_barrel_TRUE", i,j,k);
PlotUtils::MnvH1D *hist_barrel_Distance_downstreamCap_TRUE = new PlotUtils::MnvH1D(tempName, tempName, Distance_to_Caps.size()-1,Distance_to_Caps.data());
Hist_3index_Map_DistancedownstreamCap_barrel_TRUE.insert(std::make_pair(ijk, hist_barrel_Distance_downstreamCap_TRUE ));

//

sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_Map_DistanceupstreamCap_downstreamCap", i,j,k);
PlotUtils::MnvH1D *hist_downstreamCap_Distance_upstreamCap= new PlotUtils::MnvH1D(tempName, tempName, Distance_to_Caps.size()-1,Distance_to_Caps.data());
Hist_3index_Map_DistanceupstreamCap_downstreamCap.insert(std::make_pair(ijk, hist_downstreamCap_Distance_upstreamCap ));

sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_Map_DistancedownstreamCap_downstreamCap", i,j,k);
PlotUtils::MnvH1D *hist_downstreamCap_Distance_downstreamCap = new PlotUtils::MnvH1D(tempName, tempName, Distance_to_Caps.size()-1,Distance_to_Caps.data());
Hist_3index_Map_DistancedownstreamCap_downstreamCap.insert(std::make_pair(ijk, hist_downstreamCap_Distance_downstreamCap ));


sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_Map_DistanceupstreamCap_downstreamCap_TRUE", i,j,k);
PlotUtils::MnvH1D *hist_downstreamCap_Distance_upstreamCap_TRUE = new PlotUtils::MnvH1D(tempName, tempName, Distance_to_Caps.size()-1,Distance_to_Caps.data());
Hist_3index_Map_DistanceupstreamCap_downstreamCap_TRUE.insert(std::make_pair(ijk, hist_downstreamCap_Distance_upstreamCap_TRUE ));

sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_Map_DistancedownstreamCap_downstreamCap_TRUE", i,j,k);
PlotUtils::MnvH1D *hist_downstreamCap_Distance_downstreamCap_TRUE = new PlotUtils::MnvH1D(tempName, tempName, Distance_to_Caps.size()-1,Distance_to_Caps.data());
Hist_3index_Map_DistancedownstreamCap_downstreamCap_TRUE.insert(std::make_pair(ijk, hist_downstreamCap_Distance_downstreamCap_TRUE ));
//
//

sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_Map_DistanceupstreamCap_downstreamConcaveCap", i,j,k);
PlotUtils::MnvH1D *hist_downstreamconcavecap_Distance_upstreamCap= new PlotUtils::MnvH1D(tempName, tempName, Distance_to_Caps.size()-1,Distance_to_Caps.data());
Hist_3index_Map_DistanceupstreamCap_downstreamconcavecap.insert(std::make_pair(ijk, hist_downstreamconcavecap_Distance_upstreamCap ));

sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_Map_DistancedownstreamCap_downstreamConcaveCap", i,j,k);
PlotUtils::MnvH1D *hist_downstreamconcavecap_Distance_downstreamCap = new PlotUtils::MnvH1D(tempName, tempName, Distance_to_Caps.size()-1,Distance_to_Caps.data());
Hist_3index_Map_DistancedownstreamCap_downstreamconcavecap.insert(std::make_pair(ijk, hist_downstreamconcavecap_Distance_downstreamCap ));


sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_Map_DistanceupstreamCap_downstreamConcaveCap_TRUE", i,j,k);
PlotUtils::MnvH1D *hist_downstreamconcavecap_Distance_upstreamCap_TRUE = new PlotUtils::MnvH1D(tempName, tempName, Distance_to_Caps.size()-1,Distance_to_Caps.data());
Hist_3index_Map_DistanceupstreamCap_downstreamconcavecap_TRUE.insert(std::make_pair(ijk, hist_downstreamconcavecap_Distance_upstreamCap_TRUE ));

sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_Map_DistancedownstreamCap_downstreamConcaveCap_TRUE", i,j,k);
PlotUtils::MnvH1D *hist_downstreamconcavecap_Distance_downstreamCap_TRUE = new PlotUtils::MnvH1D(tempName, tempName, Distance_to_Caps.size()-1,Distance_to_Caps.data());
Hist_3index_Map_DistancedownstreamCap_downstreamconcavecap_TRUE.insert(std::make_pair(ijk, hist_downstreamconcavecap_Distance_downstreamCap_TRUE ));


/////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
//// upstream
//////////////////////////////////////////////////////////////////////////////

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_Y_barrel", i,j,k);
    PlotUtils::MnvH1D *hist_Y_barrel = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Ybin_vector.size()-1,Vertex_Ybin_vector.data());
    Hist_3index_Map_Y_barrel.insert(std::make_pair(ijk, hist_Y_barrel ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_X_barrel", i,j,k);
    PlotUtils::MnvH1D *hist_X_barrel = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Xbin_vector.size()-1,Vertex_Xbin_vector.data());
    Hist_3index_Map_X_barrel.insert(std::make_pair(ijk, hist_X_barrel ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_R_barrel", i,j,k);
    PlotUtils::MnvH1D *hist_R_barrel = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Rbin_vector.size()-1,Vertex_Rbin_vector.data());
    Hist_3index_Map_R_barrel.insert(std::make_pair(ijk, hist_R_barrel ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_Z_barrel", i,j,k);
    PlotUtils::MnvH1D *hist_Z_barrel = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Zbin_vector.size()-1,Vertex_Zbin_vector.data());
    Hist_3index_Map_Z_barrel.insert(std::make_pair(ijk, hist_Z_barrel ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_Map_DistanceEdge_barrel", i,j,k);
    PlotUtils::MnvH1D *hist_edge_barrel = new PlotUtils::MnvH1D(tempName, tempName, Distance_to_innerTank.size()-1,Distance_to_innerTank.data());
    Hist_3index_DistanceEdge_barrel.insert(std::make_pair(ijk, hist_edge_barrel ));

    /////////////////////////////
    // TRUTH
    ///////////////////////////

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_Y_barrel_TRUE", i,j,k);
    PlotUtils::MnvH1D *hist_Y_barrel_TRUE = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Ybin_vector.size()-1,Vertex_Ybin_vector.data());
    Hist_3index_Map_Y_barrel_TRUE.insert(std::make_pair(ijk, hist_Y_barrel_TRUE ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_X_barrel_TRUE", i,j,k);
    PlotUtils::MnvH1D *hist_X_barrel_TRUE = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Xbin_vector.size()-1,Vertex_Xbin_vector.data());
    Hist_3index_Map_X_barrel_TRUE.insert(std::make_pair(ijk, hist_X_barrel_TRUE ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_R_barrel_TRUE", i,j,k);
    PlotUtils::MnvH1D *hist_R_barrel_TRUE = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Rbin_vector.size()-1,Vertex_Rbin_vector.data());
    Hist_3index_Map_R_barrel_TRUE.insert(std::make_pair(ijk, hist_R_barrel_TRUE ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_Z_barrel_TRUE", i,j,k);
    PlotUtils::MnvH1D *hist_Z_barrel_TRUE = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Zbin_vector.size()-1,Vertex_Zbin_vector.data());
    Hist_3index_Map_Z_barrel_TRUE.insert(std::make_pair(ijk, hist_Z_barrel_TRUE ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_Z_RCut_barrel_TRUE", i,j,k);
    PlotUtils::MnvH1D *hist_Z_RCut_barrel_TRUE = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Zbin_vector.size()-1,Vertex_Zbin_vector.data());
    Hist_3index_Map_Z_RCut_barrel_TRUE.insert(std::make_pair(ijk, hist_Z_RCut_barrel_TRUE ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_Z_RCut_barrel", i,j,k);
    PlotUtils::MnvH1D *hist_Z_RCut_barrel = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Zbin_vector.size()-1,Vertex_Zbin_vector.data());
    Hist_3index_Map_Z_RCut_barrel.insert(std::make_pair(ijk, hist_Z_RCut_barrel ));



    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_Map_DistanceEdge_barrel_TRUE", i,j,k);
    PlotUtils::MnvH1D *hist_edge_barrel_TRUE = new PlotUtils::MnvH1D(tempName, tempName, Distance_to_innerTank.size()-1,Distance_to_innerTank.data());
    Hist_3index_DistanceEdge_barrel_TRUE.insert(std::make_pair(ijk, hist_edge_barrel_TRUE ));

    /////////////////////////////////////////////////////////////////////////////


    ///////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////
    //// downstream
    //////////////////////////////////////////////////////////////////////////////

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_Y_downstreamCap", i,j,k);
    PlotUtils::MnvH1D *hist_Y_downstreamCap = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Ybin_vector.size()-1,Vertex_Ybin_vector.data());
    Hist_3index_Map_Y_downstreamCap.insert(std::make_pair(ijk, hist_Y_downstreamCap ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_X_downstreamCap", i,j,k);
    PlotUtils::MnvH1D *hist_X_downstreamCap = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Xbin_vector.size()-1,Vertex_Xbin_vector.data());
    Hist_3index_Map_X_downstreamCap.insert(std::make_pair(ijk, hist_X_downstreamCap ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_R_downstreamCap", i,j,k);
    PlotUtils::MnvH1D *hist_R_downstreamCap = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Rbin_vector.size()-1,Vertex_Rbin_vector.data());
    Hist_3index_Map_R_downstreamCap.insert(std::make_pair(ijk, hist_R_downstreamCap ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_Z_downstreamCap", i,j,k);
    PlotUtils::MnvH1D *hist_Z_downstreamCap = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Zbin_vector.size()-1,Vertex_Zbin_vector.data());
    Hist_3index_Map_Z_downstreamCap.insert(std::make_pair(ijk, hist_Z_downstreamCap ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_Map_DistanceEdge_downstreamCap", i,j,k);
    PlotUtils::MnvH1D *hist_edge_downstreamCap = new PlotUtils::MnvH1D(tempName, tempName, Distance_to_innerTank.size()-1,Distance_to_innerTank.data());
    Hist_3index_DistanceEdge_downstreamCap.insert(std::make_pair(ijk, hist_edge_downstreamCap ));

    ///////////////////////
    /// TRUTH
    /////////////////////
    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_Y_downstreamCap_TRUE", i,j,k);
    PlotUtils::MnvH1D *hist_Y_downstreamCap_TRUE = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Ybin_vector.size()-1,Vertex_Ybin_vector.data());
    Hist_3index_Map_Y_downstreamCap_TRUE.insert(std::make_pair(ijk, hist_Y_downstreamCap_TRUE ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_X_downstreamCap_TRUE", i,j,k);
    PlotUtils::MnvH1D *hist_X_downstreamCap_TRUE = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Xbin_vector.size()-1,Vertex_Xbin_vector.data());
    Hist_3index_Map_X_downstreamCap_TRUE.insert(std::make_pair(ijk, hist_X_downstreamCap_TRUE ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_R_downstreamCap_TRUE", i,j,k);
    PlotUtils::MnvH1D *hist_R_downstreamCap_TRUE = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Rbin_vector.size()-1,Vertex_Rbin_vector.data());
    Hist_3index_Map_R_downstreamCap_TRUE.insert(std::make_pair(ijk, hist_R_downstreamCap_TRUE ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_Z_downstreamCap_TRUE", i,j,k);
    PlotUtils::MnvH1D *hist_Z_downstreamCap_TRUE = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Zbin_vector.size()-1,Vertex_Zbin_vector.data());
    Hist_3index_Map_Z_downstreamCap_TRUE.insert(std::make_pair(ijk, hist_Z_downstreamCap_TRUE ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_Z_RCut_downstreamCap_TRUE", i,j,k);
    PlotUtils::MnvH1D *hist_Z_RCut_downstreamCap_TRUE = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Zbin_vector.size()-1,Vertex_Zbin_vector.data());
    Hist_3index_Map_Z_RCut_downstreamCap_TRUE.insert(std::make_pair(ijk, hist_Z_RCut_downstreamCap_TRUE ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_Z_RCut_downstreamCap", i,j,k);
    PlotUtils::MnvH1D *hist_Z_RCut_downstreamCap = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Zbin_vector.size()-1,Vertex_Zbin_vector.data());
    Hist_3index_Map_Z_RCut_downstreamCap.insert(std::make_pair(ijk, hist_Z_RCut_downstreamCap ));



    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_Map_DistanceEdge_downstreamCap_TRUE", i,j,k);
    PlotUtils::MnvH1D *hist_edge_downstreamCap_TRUE = new PlotUtils::MnvH1D(tempName, tempName, Distance_to_innerTank.size()-1,Distance_to_innerTank.data());
    Hist_3index_DistanceEdge_downstreamCap_TRUE.insert(std::make_pair(ijk, hist_edge_downstreamCap_TRUE ));

    /////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////
    //// downstreamconcavecap
    //////////////////////////////////////////////////////////////////////////////

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_Y_downstreamConcaveCap", i,j,k);
    PlotUtils::MnvH1D *hist_Y_downstreamconcavecap = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Ybin_vector.size()-1,Vertex_Ybin_vector.data());
    Hist_3index_Map_Y_downstreamconcavecap.insert(std::make_pair(ijk, hist_Y_downstreamconcavecap ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_X_downstreamConcaveCap", i,j,k);
    PlotUtils::MnvH1D *hist_X_downstreamconcavecap = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Xbin_vector.size()-1,Vertex_Xbin_vector.data());
    Hist_3index_Map_X_downstreamconcavecap.insert(std::make_pair(ijk, hist_X_downstreamconcavecap ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_R_downstreamConcaveCap", i,j,k);
    PlotUtils::MnvH1D *hist_R_downstreamconcavecap = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Rbin_vector.size()-1,Vertex_Rbin_vector.data());
    Hist_3index_Map_R_downstreamconcavecap.insert(std::make_pair(ijk, hist_R_downstreamconcavecap ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_Z_downstreamConcaveCap", i,j,k);
    PlotUtils::MnvH1D *hist_Z_downstreamconcavecap = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Zbin_vector.size()-1,Vertex_Zbin_vector.data());
    Hist_3index_Map_Z_downstreamconcavecap.insert(std::make_pair(ijk, hist_Z_downstreamconcavecap ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_Map_DistanceEdge_downstreamConcaveCap", i,j,k);
    PlotUtils::MnvH1D *hist_edge_downstreamconcavecap = new PlotUtils::MnvH1D(tempName, tempName, Distance_to_innerTank.size()-1,Distance_to_innerTank.data());
    Hist_3index_DistanceEdge_downstreamconcavecap.insert(std::make_pair(ijk, hist_edge_downstreamconcavecap ));

    //////////////
    /// TRUTH
    //////////////

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_Y_downstreamConcaveCap_TRUE", i,j,k);
    PlotUtils::MnvH1D *hist_Y_downstreamconcavecap_TRUE = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Ybin_vector.size()-1,Vertex_Ybin_vector.data());
    Hist_3index_Map_Y_downstreamconcavecap_TRUE.insert(std::make_pair(ijk, hist_Y_downstreamconcavecap_TRUE ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_X_downstreamConcaveCap_TRUE", i,j,k);
    PlotUtils::MnvH1D *hist_X_downstreamconcavecap_TRUE = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Xbin_vector.size()-1,Vertex_Xbin_vector.data());
    Hist_3index_Map_X_downstreamconcavecap_TRUE.insert(std::make_pair(ijk, hist_X_downstreamconcavecap_TRUE ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_R_downstreamConcaveCap_TRUE", i,j,k);
    PlotUtils::MnvH1D *hist_R_downstreamconcavecap_TRUE = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Rbin_vector.size()-1,Vertex_Rbin_vector.data());
    Hist_3index_Map_R_downstreamconcavecap_TRUE.insert(std::make_pair(ijk, hist_R_downstreamconcavecap_TRUE ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_Z_downstreamConcaveCap_TRUE", i,j,k);
    PlotUtils::MnvH1D *hist_Z_downstreamconcavecap_TRUE = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Zbin_vector.size()-1,Vertex_Zbin_vector.data());
    Hist_3index_Map_Z_downstreamconcavecap_TRUE.insert(std::make_pair(ijk, hist_Z_downstreamconcavecap_TRUE ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_Z_RCut_downstreamConcaveCap_TRUE", i,j,k);
    PlotUtils::MnvH1D *hist_Z_RCut_downstreamconcavecap_TRUE = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Zbin_vector.size()-1,Vertex_Zbin_vector.data());
    Hist_3index_Map_Z_RCut_downstreamconcavecap_TRUE.insert(std::make_pair(ijk, hist_Z_RCut_downstreamconcavecap_TRUE ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_Z_RCut_downstreamConcaveCap", i,j,k);
    PlotUtils::MnvH1D *hist_Z_RCut_downstreamconcavecap = new PlotUtils::MnvH1D(tempName, tempName, Vertex_Zbin_vector.size()-1,Vertex_Zbin_vector.data());
    Hist_3index_Map_Z_RCut_downstreamconcavecap.insert(std::make_pair(ijk, hist_Z_RCut_downstreamconcavecap ));


    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_Map_DistanceEdge_downstreamConcaveCap_TRUE", i,j,k);
    PlotUtils::MnvH1D *hist_edge_downstreamconcavecap_TRUE = new PlotUtils::MnvH1D(tempName, tempName, Distance_to_innerTank.size()-1,Distance_to_innerTank.data());
    Hist_3index_DistanceEdge_downstreamconcavecap_TRUE.insert(std::make_pair(ijk, hist_edge_downstreamconcavecap_TRUE ));


    /////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////


    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_Map_DistanceEdge", i,j,k);
    PlotUtils::MnvH1D *hist_edge = new PlotUtils::MnvH1D(tempName, tempName, Distance_to_innerTank.size()-1,Distance_to_innerTank.data());
    Hist_3index_DistanceEdge.insert(std::make_pair(ijk, hist_edge ));

    /////////
    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_X_upstreamcap_Material", i,j,k);
    PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_X_Material_upstreamcap =
    PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, tempName, Vertex_Xbin_vector ,"h_offset_Vertex_X_Material; [mm];Events:");
    HistFolio_3index_Map_X_upstreamcap.insert(std::make_pair(ijk, h_CryoVertex_X_Material_upstreamcap ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_Y_upstreamcap_Material", i,j,k);
    PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Y_Material_upstreamcap =
    PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, tempName, Vertex_Ybin_vector ,"h_offset_Vertex_Y_Material; [mm];Events:");
    HistFolio_3index_Map_Y_upstreamcap.insert(std::make_pair(ijk, h_CryoVertex_Y_Material_upstreamcap ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_Z_upstreamcap_Material", i,j,k);
    PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Z_Material_upstreamcap =
    PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, tempName, Vertex_Zbin_vector ,"h_offset_Vertex_Z_Material; [mm];Events:");
    HistFolio_3index_Map_Z_upstreamcap.insert(std::make_pair(ijk, h_CryoVertex_Z_Material_upstreamcap ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_R_upstreamcap_Material", i,j,k);
    PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_R_Material_upstreamcap =
    PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, tempName, Vertex_Rbin_vector ,"h_offset_Vertex_R_Material; [mm];Events:");
    HistFolio_3index_Map_R_upstreamcap.insert(std::make_pair(ijk, h_CryoVertex_R_Material_upstreamcap ));



    /////////////////////////////////////////////////////////////////////////////////
    //// barrel
    //////////////////////////////////////////////////////////////////////////////

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_X_barrel_Material", i,j,k);
    PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_X_Material_barrel =
    PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, tempName, Vertex_Xbin_vector ,"h_offset_Vertex_X_Material; [mm];Events:");
    HistFolio_3index_Map_X_barrel.insert(std::make_pair(ijk, h_CryoVertex_X_Material_barrel ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_Y_barrel_Material", i,j,k);
    PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Y_Material_barrel =
    PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, tempName, Vertex_Ybin_vector ,"h_offset_Vertex_Y_Material; [mm];Events:");
    HistFolio_3index_Map_Y_barrel.insert(std::make_pair(ijk, h_CryoVertex_Y_Material_barrel ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_Z_barrel_Material", i,j,k);
    PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Z_Material_barrel =
    PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, tempName, Vertex_Zbin_vector ,"h_offset_Vertex_Z_Material; [mm];Events:");
    HistFolio_3index_Map_Z_barrel.insert(std::make_pair(ijk, h_CryoVertex_Z_Material_barrel ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_R_barrel_Material", i,j,k);
    PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_R_Material_barrel =
    PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, tempName, Vertex_Rbin_vector ,"h_offset_Vertex_R_Material; [mm];Events:");
    HistFolio_3index_Map_R_barrel.insert(std::make_pair(ijk, h_CryoVertex_R_Material_barrel ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_X_downstreamcap_Material", i,j,k);
    PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_X_Material_downstreamcap =
    PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, tempName, Vertex_Xbin_vector ,"h_offset_Vertex_x_Material; [mm];Events:");
    HistFolio_3index_Map_X_downstreamcap.insert(std::make_pair(ijk, h_CryoVertex_X_Material_downstreamcap ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_Y_downstreamcap_Material", i,j,k);
    PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Y_Material_downstreamcap =
    PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, tempName, Vertex_Ybin_vector ,"h_offset_Vertex_Y_Material; [mm];Events:");
    HistFolio_3index_Map_Y_downstreamcap.insert(std::make_pair(ijk, h_CryoVertex_Y_Material_downstreamcap ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_Z_downstreamcap_Material", i,j,k);
    PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Z_Material_downstreamcap =
    PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, tempName, Vertex_Zbin_vector ,"h_offset_Vertex_Z_Material; [mm];Events:");
    HistFolio_3index_Map_Z_downstreamcap.insert(std::make_pair(ijk, h_CryoVertex_Z_Material_downstreamcap ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_R_downstreamcap_Material", i,j,k);
    PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_R_Material_downstreamcap =
    PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, tempName, Vertex_Rbin_vector ,"h_offset_Vertex_R_Material; [mm];Events:");
    HistFolio_3index_Map_R_downstreamcap.insert(std::make_pair(ijk, h_CryoVertex_R_Material_downstreamcap ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_X_downstreamconcavecap_Material", i,j,k);
        PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_X_Material_downstreamconcavecap =
        PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, tempName, Vertex_Xbin_vector ,"h_offset_Vertex_X_Material; [mm];Events:");
        HistFolio_3index_Map_X_downstreamconcavecap.insert(std::make_pair(ijk, h_CryoVertex_X_Material_downstreamconcavecap ));

    sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_Y_downstreamconcavecap_Material", i,j,k);
        PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Y_Material_downstreamconcavecap =
        PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, tempName, Vertex_Ybin_vector ,"h_offset_Vertex_Y_Material; [mm];Events:");
        HistFolio_3index_Map_Y_downstreamconcavecap.insert(std::make_pair(ijk, h_CryoVertex_Y_Material_downstreamconcavecap ));

        sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_Z_downstreamconcavecap_Material", i,j,k);
        PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Z_Material_downstreamconcavecap =
        PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, tempName, Vertex_Zbin_vector ,"h_offset_Vertex_Z_Material; [mm];Events:");
        HistFolio_3index_Map_Z_downstreamconcavecap.insert(std::make_pair(ijk, h_CryoVertex_Z_Material_downstreamconcavecap ));

        sprintf(tempName,"%s_i_j_k_%d_%d_%d","h_offset_Vertex_R_downstreamconcavecap_Material", i,j,k);
        PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_R_Material_downstreamconcavecap =
        PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, tempName, Vertex_Rbin_vector ,"h_offset_Vertex_R_Material; [mm];Events:");
        HistFolio_3index_Map_R_downstreamconcavecap.insert(std::make_pair(ijk, h_CryoVertex_R_Material_downstreamconcavecap ));


    //if(fillHisindex%25==0)
    std::cout<< "Finished (" << fillHisindex  <<  ") Set for index = (i,j,k) = (" << i <<" , "<< j<< " , "<< k  <<") " <<std::endl;

    fillHisindex++;

  }






////////////////
//Vertex Hist///
////////////////

/////////////////////////////////////////
//2D
/////////////////////////////////////////

  //=========================================
  // Entry Loop For MC
  //=========================================

  RECO_Cut_Map CountMap_Fiduical;
  FillingRecoCountingMap(kCutsVector_FiduicalEff, CountMap_Fiduical);
  RECO_Cut_Map CountMap_ALL;
  FillingRecoCountingMap(kCutsVector_ALL, CountMap_ALL);

  TRUE_Cut_Map Truth_Cut_Map_Fiduical;
  TRUE_Cut_Map Truth_Cut_Map_ALL;

  FillingTruthCountingMap(kTRUTHCutsVector_Fiduical,     Truth_Cut_Map_Fiduical);

  ProcInfo_t procInfo;
  gSystem->GetProcInfo(&procInfo);

std::string sysmatics_status;
if(m_RunCodeWithSystematics==true){sysmatics_status= "Systematics On";}
else if (m_RunCodeWithSystematics==false){sysmatics_status= "Systematics Off";}
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;
std::cout<<"~~~~~~~~~ Systematics are =   "<< sysmatics_status <<" ~~~~~~~~~ "<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;


std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;
std::cout<<"~~~~~~~~~  THIS IS RECO 1D ~~~~~~~~~ "<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;
if(m_RunCodeWith_Alwgts==true) {PrintWgtsBeingUSED();}

  std::cout << "Memory/time used so Far: " << procInfo.fMemResident/1000<< " MB" <<" time = "<<  procInfo.fCpuSys <<  " Sec"<<"\n";

  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<" Starting MC LOOP  for Playlist: "<<  Playlist_Info.GetPlaylistname()<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

  for(int ii=0; ii<chw_MC->GetEntries(); ++ii){

    if(ii%1000==0) std::cout << (ii/100) << " k " << std::flush;

    //=========================================
    // For every systematic, loop over the universes, and fill the
    // appropriate histogram in the MnvH1D
    //=========================================

    for (auto  Universe_GROUP: Error_Band_Universe_GROUPS){

//      std::vector<HeliumCVUniverse*> error_band_universes = band.second;
     Universe_GROUP.front()->SetEntry(ii);

        ///////////////////////////////////////////
        ////
        ////  Apply TRUTH + RECO CUTS to each universe
        ////
        ///////////////////////////////////////////


      if(PassesCutsRECO(*Universe_GROUP.front(),  is_mc , kCutsVector_FiduicalEff , kWeights_v1tune, CountMap_Fiduical ) ){
        for (auto universe : Universe_GROUP){
          universe->SetEntry(ii);

          Material_type Material_type_Event = universe->Get_MaterialStackType();

          double wgt_minerva_v1 = universe->GetWeight(kWeights_v1tune);
          //if(Material_type_Event==kAluminium){ wgt_minerva_v1*=1.40;}

          double ShiftX  = ShiftX_major;
          double ShiftY  = ShiftY_major;
          double ShiftZ  = ShiftZ_major;

          if(Material_type_Event!=kAluminium && Material_type_Event!=kHelium){
            ShiftX=0;
            ShiftY=0;
            ShiftZ=0;}


          double x= universe->GetVertex_x() + ShiftX;
          double y= universe->GetVertex_y() + ShiftY;
          double z= universe->GetVertex_z() + ShiftZ;
          double r =  sqrt(x * x + y * y );


          double x_TRUE= universe->GetTRUE_Vertex_x();
          double y_TRUE= universe->GetTRUE_Vertex_y();
          double z_TRUE= universe->GetTRUE_Vertex_z();
          double r_TRUE =  sqrt(x_TRUE * x_TRUE + y_TRUE * y_TRUE );

          double Theta = universe->GetThetamu();
          double Pmu = universe ->GetPmu()/1000;
          double phi = universe->GetPhimu();


          double px = Pmu * std::sin(Theta) * std::cos(phi);
          double py = Pmu * std::sin(Theta) * std::sin(phi);

          double PT = sqrt(px*px + py*py);
          double PZ = Pmu*std::cos(Theta);



          double Reco_distance_nearestWall = RECO_Distance_to_innerTank( r, z );
          double TRUE_distance_nearestWall = RECO_Distance_to_innerTank( r_TRUE, z_TRUE );

          double dist_upstreamCap = DistanceFromUpStreamBulge(z , r);
          double dist_downstreamCap = DistanceFromDownStreamBulge(z , r);

          double dist_upstreamCap_TRUE = DistanceFromUpStreamBulge(z_TRUE , r_TRUE);
          double dist_downstreamCap_TRUE = DistanceFromDownStreamBulge(z_TRUE , r_TRUE);


          CryoTank_REGIONS CryoTankRegion_type = FourRegion_of_CryoTank(z_TRUE);


          //if(m_RunCodeWith_Alwgts==true &&  Material_type_Event == kAluminium && CryoTankRegion_type==kUpstream_head){             wgt_minerva_v1 *=Al_wgts::upstream;}
          //else if(m_RunCodeWith_Alwgts==true &&  Material_type_Event == kAluminium && CryoTankRegion_type==kCenter){               wgt_minerva_v1 *=Al_wgts::barrel;}
          //else if(m_RunCodeWith_Alwgts==true &&  Material_type_Event == kAluminium && CryoTankRegion_type==kDownstream_head ){     wgt_minerva_v1 *=Al_wgts::downstream;}
          //else if(m_RunCodeWith_Alwgts==true &&  Material_type_Event == kAluminium && CryoTankRegion_type==kDownstream_ConcaveCap ){wgt_minerva_v1 *=Al_wgts::concave;}

          double Al_wgt = 1.0;
          if(m_RunCodeWith_Alwgts==true){Al_wgt = return_AlWgt(CryoTankRegion_type, Material_type_Event  );}
            wgt_minerva_v1*=Al_wgt;

          if(CryoTankRegion_type==kUpstream_head)
          {
            h_CryoVertex_X.univHist(universe)->Fill(x ,wgt_minerva_v1);

            h_CryoVertex_Y.univHist(universe)->Fill(y ,wgt_minerva_v1);

            h_CryoVertex_Z.univHist(universe)->Fill(z ,wgt_minerva_v1);

            h_CryoVertex_R.univHist(universe)->Fill(r,wgt_minerva_v1);

            h_CryoVertex_X_TRUE.univHist(universe)->Fill(x_TRUE ,wgt_minerva_v1);

            h_CryoVertex_Y_TRUE.univHist(universe)->Fill(y_TRUE ,wgt_minerva_v1);

            h_CryoVertex_Z_TRUE.univHist(universe)->Fill(z_TRUE ,wgt_minerva_v1);

            h_CryoVertex_R_TRUE.univHist(universe)->Fill(r_TRUE,wgt_minerva_v1);

            h_Distance_to_InnerTank.univHist(universe)->Fill(Reco_distance_nearestWall,wgt_minerva_v1);

            h_Distance_to_InnerTank_TRUE.univHist(universe)->Fill(TRUE_distance_nearestWall,wgt_minerva_v1);

            h_Distance_to_upstreamCap.univHist(universe)->Fill(dist_upstreamCap,wgt_minerva_v1);

            h_Distance_to_upstreamCap_TRUE.univHist(universe)->Fill(dist_upstreamCap_TRUE,wgt_minerva_v1);

            h_Distance_to_downstreamCap.univHist(universe)->Fill(dist_downstreamCap,wgt_minerva_v1);

            h_Distance_to_downstreamCap_TRUE.univHist(universe)->Fill(dist_downstreamCap_TRUE,wgt_minerva_v1);

            if(Cylindrical_CutAboutZero(r)== true){

              h_Distance_to_upstreamCap_RCut.univHist(universe)->Fill(dist_upstreamCap,wgt_minerva_v1);

              h_Distance_to_upstreamCap_RCut_TRUE.univHist(universe)->Fill(dist_upstreamCap_TRUE,wgt_minerva_v1);

              h_Distance_to_downstreamCap_RCut.univHist(universe)->Fill(dist_downstreamCap,wgt_minerva_v1);

              h_Distance_to_downstreamCap_RCut_TRUE.univHist(universe)->Fill(dist_downstreamCap_TRUE,wgt_minerva_v1);

              h_CryoVertex_Z_RCut.univHist(universe)->Fill(z ,wgt_minerva_v1);

              h_CryoVertex_Z_RCut_TRUE.univHist(universe)->Fill(z_TRUE ,wgt_minerva_v1);

            }

            h_CryoVertex_X_upstreamCap.univHist(universe)->Fill(x ,wgt_minerva_v1);

            h_CryoVertex_Y_upstreamCap.univHist(universe)->Fill(y ,wgt_minerva_v1);

            h_CryoVertex_Z_upstreamCap.univHist(universe)->Fill(z ,wgt_minerva_v1);

            h_CryoVertex_R_upstreamCap.univHist(universe)->Fill(r,wgt_minerva_v1);

            h_CryoVertex_X_upstreamCap_TRUE.univHist(universe)->Fill(x_TRUE ,wgt_minerva_v1);

            h_CryoVertex_Y_upstreamCap_TRUE.univHist(universe)->Fill(y_TRUE ,wgt_minerva_v1);

            h_CryoVertex_Z_upstreamCap_TRUE.univHist(universe)->Fill(z_TRUE ,wgt_minerva_v1);

            h_CryoVertex_R_upstreamCap_TRUE.univHist(universe)->Fill(r_TRUE,wgt_minerva_v1);

            h_Distance_to_InnerTank_upstreamCap.univHist(universe)->Fill(Reco_distance_nearestWall,wgt_minerva_v1);

            h_Distance_to_InnerTank_upstreamCap_TRUE.univHist(universe)->Fill(TRUE_distance_nearestWall,wgt_minerva_v1);

            h_Distance_to_upstreamCap_upstreamCap.univHist(universe)->Fill(dist_upstreamCap,wgt_minerva_v1);

            h_Distance_to_upstreamCap_upstreamCap_TRUE.univHist(universe)->Fill(dist_upstreamCap_TRUE,wgt_minerva_v1);

            h_Distance_to_downstreamCap_upstreamCap.univHist(universe)->Fill(dist_downstreamCap,wgt_minerva_v1);

            h_Distance_to_downstreamCap_upstreamCap_TRUE.univHist(universe)->Fill(dist_downstreamCap_TRUE,wgt_minerva_v1);

            if(Cylindrical_CutAboutZero(r)== true){
              h_Distance_to_upstreamCap_RCut_upstreamCap.univHist(universe)->Fill(dist_upstreamCap,wgt_minerva_v1);

              h_Distance_to_upstreamCap_RCut_upstreamCap_TRUE.univHist(universe)->Fill(dist_upstreamCap_TRUE,wgt_minerva_v1);

              h_Distance_to_downstreamCap_RCut_upstreamCap.univHist(universe)->Fill(dist_downstreamCap,wgt_minerva_v1);

              h_Distance_to_downstreamCap_RCut_upstreamCap_TRUE.univHist(universe)->Fill(dist_downstreamCap_TRUE,wgt_minerva_v1);

              h_CryoVertex_Z_RCut_upstreamCap.univHist(universe)->Fill(z ,wgt_minerva_v1);
              h_CryoVertex_Z_RCut_upstreamCap_TRUE.univHist(universe)->Fill(z_TRUE ,wgt_minerva_v1);



            }



          }
          else if(CryoTankRegion_type==kCenter)
          {

            h_CryoVertex_X.univHist(universe)->Fill(x ,wgt_minerva_v1);

            h_CryoVertex_Y.univHist(universe)->Fill(y ,wgt_minerva_v1);

            h_CryoVertex_Z.univHist(universe)->Fill(z ,wgt_minerva_v1);

            h_CryoVertex_R.univHist(universe)->Fill(r,wgt_minerva_v1);

            h_CryoVertex_X_TRUE.univHist(universe)->Fill(x_TRUE ,wgt_minerva_v1);

            h_CryoVertex_Y_TRUE.univHist(universe)->Fill(y_TRUE ,wgt_minerva_v1);

            h_CryoVertex_Z_TRUE.univHist(universe)->Fill(z_TRUE ,wgt_minerva_v1);

            h_CryoVertex_R_TRUE.univHist(universe)->Fill(r_TRUE,wgt_minerva_v1);

            h_Distance_to_InnerTank.univHist(universe)->Fill(Reco_distance_nearestWall,wgt_minerva_v1);

            h_Distance_to_InnerTank_TRUE.univHist(universe)->Fill(TRUE_distance_nearestWall,wgt_minerva_v1);

            h_Distance_to_upstreamCap.univHist(universe)->Fill(dist_upstreamCap,wgt_minerva_v1);

            h_Distance_to_upstreamCap_TRUE.univHist(universe)->Fill(dist_upstreamCap_TRUE,wgt_minerva_v1);

            h_Distance_to_downstreamCap.univHist(universe)->Fill(dist_downstreamCap,wgt_minerva_v1);

            h_Distance_to_downstreamCap_TRUE.univHist(universe)->Fill(dist_downstreamCap_TRUE,wgt_minerva_v1);

            if(Cylindrical_CutAboutZero(r)== true){

              h_Distance_to_upstreamCap_RCut.univHist(universe)->Fill(dist_upstreamCap,wgt_minerva_v1);

              h_Distance_to_upstreamCap_RCut_TRUE.univHist(universe)->Fill(dist_upstreamCap_TRUE,wgt_minerva_v1);

              h_Distance_to_downstreamCap_RCut.univHist(universe)->Fill(dist_downstreamCap,wgt_minerva_v1);

              h_Distance_to_downstreamCap_RCut_TRUE.univHist(universe)->Fill(dist_downstreamCap_TRUE,wgt_minerva_v1);

              h_CryoVertex_Z_RCut.univHist(universe)->Fill(z ,wgt_minerva_v1);

              h_CryoVertex_Z_RCut_TRUE.univHist(universe)->Fill(z_TRUE ,wgt_minerva_v1);

            }


            h_CryoVertex_X_barrel.univHist(universe)->Fill(x ,wgt_minerva_v1);

            h_CryoVertex_Y_barrel.univHist(universe)->Fill(y ,wgt_minerva_v1);

            h_CryoVertex_Z_barrel.univHist(universe)->Fill(z ,wgt_minerva_v1);

            h_CryoVertex_R_barrel.univHist(universe)->Fill(r,wgt_minerva_v1);

            h_CryoVertex_X_barrel_TRUE.univHist(universe)->Fill(x_TRUE ,wgt_minerva_v1);

            h_CryoVertex_Y_barrel_TRUE.univHist(universe)->Fill(y_TRUE ,wgt_minerva_v1);

            h_CryoVertex_Z_barrel_TRUE.univHist(universe)->Fill(z_TRUE ,wgt_minerva_v1);

            h_CryoVertex_R_barrel_TRUE.univHist(universe)->Fill(r_TRUE,wgt_minerva_v1);

            h_Distance_to_upstreamCap_barrel.univHist(universe)->Fill(dist_upstreamCap,wgt_minerva_v1);

            h_Distance_to_upstreamCap_barrel_TRUE.univHist(universe)->Fill(dist_upstreamCap_TRUE,wgt_minerva_v1);

            h_Distance_to_downstreamCap_barrel.univHist(universe)->Fill(dist_downstreamCap,wgt_minerva_v1);

            h_Distance_to_downstreamCap_barrel_TRUE.univHist(universe)->Fill(dist_downstreamCap_TRUE,wgt_minerva_v1);

            h_Distance_to_InnerTank_barrel.univHist(universe)->Fill(Reco_distance_nearestWall,wgt_minerva_v1);

            h_Distance_to_InnerTank_barrel_TRUE.univHist(universe)->Fill(TRUE_distance_nearestWall,wgt_minerva_v1);

            if(Cylindrical_CutAboutZero(r)== true){

              h_Distance_to_upstreamCap_RCut_barrel.univHist(universe)->Fill(dist_upstreamCap,wgt_minerva_v1);

              h_Distance_to_upstreamCap_RCut_barrel_TRUE.univHist(universe)->Fill(dist_upstreamCap_TRUE,wgt_minerva_v1);

              h_Distance_to_downstreamCap_RCut_barrel.univHist(universe)->Fill(dist_downstreamCap,wgt_minerva_v1);

              h_Distance_to_downstreamCap_RCut_barrel_TRUE.univHist(universe)->Fill(dist_downstreamCap_TRUE,wgt_minerva_v1);

              h_CryoVertex_Z_RCut_barrel.univHist(universe)->Fill(z ,wgt_minerva_v1);

              h_CryoVertex_Z_RCut_barrel_TRUE.univHist(universe)->Fill(z_TRUE ,wgt_minerva_v1);


            }
          }

          else if(CryoTankRegion_type==kDownstream_head)
          {
            h_CryoVertex_X.univHist(universe)->Fill(x ,wgt_minerva_v1);

            h_CryoVertex_Y.univHist(universe)->Fill(y ,wgt_minerva_v1);

            h_CryoVertex_Z.univHist(universe)->Fill(z ,wgt_minerva_v1);

            h_CryoVertex_R.univHist(universe)->Fill(r,wgt_minerva_v1);

            h_CryoVertex_X_TRUE.univHist(universe)->Fill(x_TRUE ,wgt_minerva_v1);

            h_CryoVertex_Y_TRUE.univHist(universe)->Fill(y_TRUE ,wgt_minerva_v1);

            h_CryoVertex_Z_TRUE.univHist(universe)->Fill(z_TRUE ,wgt_minerva_v1);

            h_CryoVertex_R_TRUE.univHist(universe)->Fill(r_TRUE,wgt_minerva_v1);

            h_Distance_to_InnerTank.univHist(universe)->Fill(Reco_distance_nearestWall,wgt_minerva_v1);

            h_Distance_to_InnerTank_TRUE.univHist(universe)->Fill(TRUE_distance_nearestWall,wgt_minerva_v1);

            h_Distance_to_upstreamCap.univHist(universe)->Fill(dist_upstreamCap,wgt_minerva_v1);

            h_Distance_to_upstreamCap_TRUE.univHist(universe)->Fill(dist_upstreamCap_TRUE,wgt_minerva_v1);

            h_Distance_to_downstreamCap.univHist(universe)->Fill(dist_downstreamCap,wgt_minerva_v1);

            h_Distance_to_downstreamCap_TRUE.univHist(universe)->Fill(dist_downstreamCap_TRUE,wgt_minerva_v1);

            if(Cylindrical_CutAboutZero(r)== true){

              h_Distance_to_upstreamCap_RCut.univHist(universe)->Fill(dist_upstreamCap,wgt_minerva_v1);

              h_Distance_to_upstreamCap_RCut_TRUE.univHist(universe)->Fill(dist_upstreamCap_TRUE,wgt_minerva_v1);

              h_Distance_to_downstreamCap_RCut.univHist(universe)->Fill(dist_downstreamCap,wgt_minerva_v1);

              h_Distance_to_downstreamCap_RCut_TRUE.univHist(universe)->Fill(dist_downstreamCap_TRUE,wgt_minerva_v1);

              h_CryoVertex_Z_RCut.univHist(universe)->Fill(z ,wgt_minerva_v1);

              h_CryoVertex_Z_RCut_TRUE.univHist(universe)->Fill(z_TRUE ,wgt_minerva_v1);

            }

            h_CryoVertex_X_downstreamCap.univHist(universe)->Fill(x ,wgt_minerva_v1);

            h_CryoVertex_Y_downstreamCap.univHist(universe)->Fill(y ,wgt_minerva_v1);

            h_CryoVertex_Z_downstreamCap.univHist(universe)->Fill(z ,wgt_minerva_v1);

            h_CryoVertex_R_downstreamCap.univHist(universe)->Fill(r,wgt_minerva_v1);

            h_CryoVertex_X_downstreamCap_TRUE.univHist(universe)->Fill(x_TRUE ,wgt_minerva_v1);

            h_CryoVertex_Y_downstreamCap_TRUE.univHist(universe)->Fill(y_TRUE ,wgt_minerva_v1);

            h_CryoVertex_Z_downstreamCap_TRUE.univHist(universe)->Fill(z_TRUE ,wgt_minerva_v1);

            h_CryoVertex_R_downstreamCap_TRUE.univHist(universe)->Fill(r_TRUE,wgt_minerva_v1);

            h_Distance_to_upstreamCap_downstreamCap.univHist(universe)->Fill(dist_upstreamCap,wgt_minerva_v1);

            h_Distance_to_upstreamCap_downstreamCap_TRUE.univHist(universe)->Fill(dist_upstreamCap_TRUE,wgt_minerva_v1);

            h_Distance_to_downstreamCap_downstreamCap.univHist(universe)->Fill(dist_downstreamCap,wgt_minerva_v1);

            h_Distance_to_downstreamCap_downstreamCap_TRUE.univHist(universe)->Fill(dist_downstreamCap_TRUE,wgt_minerva_v1);

            h_Distance_to_InnerTank_downstreamCap.univHist(universe)->Fill(Reco_distance_nearestWall,wgt_minerva_v1);

            h_Distance_to_InnerTank_downstreamCap_TRUE.univHist(universe)->Fill(TRUE_distance_nearestWall,wgt_minerva_v1);


            if(Cylindrical_CutAboutZero(r)== true){

              h_Distance_to_upstreamCap_RCut_downstreamCap.univHist(universe)->Fill(dist_upstreamCap,wgt_minerva_v1);

              h_Distance_to_upstreamCap_RCut_downstreamCap_TRUE.univHist(universe)->Fill(dist_upstreamCap_TRUE,wgt_minerva_v1);

              h_Distance_to_downstreamCap_RCut_downstreamCap.univHist(universe)->Fill(dist_downstreamCap,wgt_minerva_v1);

              h_Distance_to_downstreamCap_RCut_downstreamCap_TRUE.univHist(universe)->Fill(dist_downstreamCap_TRUE,wgt_minerva_v1);

              h_CryoVertex_Z_RCut_downstreamCap.univHist(universe)->Fill(z ,wgt_minerva_v1);

              h_CryoVertex_Z_RCut_downstreamCap_TRUE.univHist(universe)->Fill(z_TRUE ,wgt_minerva_v1);

            }

          }

          else if(CryoTankRegion_type==kDownstream_ConcaveCap)
          {

            h_CryoVertex_X.univHist(universe)->Fill(x ,wgt_minerva_v1);

            h_CryoVertex_Y.univHist(universe)->Fill(y ,wgt_minerva_v1);

            h_CryoVertex_Z.univHist(universe)->Fill(z ,wgt_minerva_v1);

            h_CryoVertex_R.univHist(universe)->Fill(r,wgt_minerva_v1);

            h_CryoVertex_X_TRUE.univHist(universe)->Fill(x_TRUE ,wgt_minerva_v1);

            h_CryoVertex_Y_TRUE.univHist(universe)->Fill(y_TRUE ,wgt_minerva_v1);

            h_CryoVertex_Z_TRUE.univHist(universe)->Fill(z_TRUE ,wgt_minerva_v1);

            h_CryoVertex_R_TRUE.univHist(universe)->Fill(r_TRUE,wgt_minerva_v1);

            h_Distance_to_InnerTank.univHist(universe)->Fill(Reco_distance_nearestWall,wgt_minerva_v1);

            h_Distance_to_InnerTank_TRUE.univHist(universe)->Fill(TRUE_distance_nearestWall,wgt_minerva_v1);

            h_Distance_to_upstreamCap.univHist(universe)->Fill(dist_upstreamCap,wgt_minerva_v1);

            h_Distance_to_upstreamCap_TRUE.univHist(universe)->Fill(dist_upstreamCap_TRUE,wgt_minerva_v1);

            h_Distance_to_downstreamCap.univHist(universe)->Fill(dist_downstreamCap,wgt_minerva_v1);

            h_Distance_to_downstreamCap_TRUE.univHist(universe)->Fill(dist_downstreamCap_TRUE,wgt_minerva_v1);

            if(Cylindrical_CutAboutZero(r)== true){

              h_Distance_to_upstreamCap_RCut.univHist(universe)->Fill(dist_upstreamCap,wgt_minerva_v1);

              h_Distance_to_upstreamCap_RCut_TRUE.univHist(universe)->Fill(dist_upstreamCap_TRUE,wgt_minerva_v1);

              h_Distance_to_downstreamCap_RCut.univHist(universe)->Fill(dist_downstreamCap,wgt_minerva_v1);

              h_Distance_to_downstreamCap_RCut_TRUE.univHist(universe)->Fill(dist_downstreamCap_TRUE,wgt_minerva_v1);

              h_CryoVertex_Z_RCut.univHist(universe)->Fill(z ,wgt_minerva_v1);

              h_CryoVertex_Z_RCut_TRUE.univHist(universe)->Fill(z_TRUE ,wgt_minerva_v1);

            }

            h_CryoVertex_X_downstreamConcaveCap.univHist(universe)->Fill(x ,wgt_minerva_v1);

            h_CryoVertex_Y_downstreamConcaveCap.univHist(universe)->Fill(y ,wgt_minerva_v1);

            h_CryoVertex_Z_downstreamConcaveCap.univHist(universe)->Fill(z ,wgt_minerva_v1);

            h_CryoVertex_R_downstreamConcaveCap.univHist(universe)->Fill(r,wgt_minerva_v1);

            h_CryoVertex_X_downstreamConcaveCap_TRUE.univHist(universe)->Fill(x_TRUE ,wgt_minerva_v1);

            h_CryoVertex_Y_downstreamConcaveCap_TRUE.univHist(universe)->Fill(y_TRUE ,wgt_minerva_v1);

            h_CryoVertex_Z_downstreamConcaveCap_TRUE.univHist(universe)->Fill(z_TRUE ,wgt_minerva_v1);

            h_CryoVertex_R_downstreamConcaveCap_TRUE.univHist(universe)->Fill(r_TRUE,wgt_minerva_v1);

            h_Distance_to_upstreamCap_downstreamConcaveCap.univHist(universe)->Fill(dist_upstreamCap,wgt_minerva_v1);

            h_Distance_to_upstreamCap_downstreamConcaveCap_TRUE.univHist(universe)->Fill(dist_upstreamCap_TRUE,wgt_minerva_v1);

            h_Distance_to_downstreamCap_downstreamConcaveCap.univHist(universe)->Fill(dist_downstreamCap,wgt_minerva_v1);

            h_Distance_to_downstreamCap_downstreamConcaveCap_TRUE.univHist(universe)->Fill(dist_downstreamCap_TRUE,wgt_minerva_v1);

            h_Distance_to_InnerTank_downstreamConcaveCap.univHist(universe)->Fill(Reco_distance_nearestWall,wgt_minerva_v1);

            h_Distance_to_InnerTank_downstreamConcaveCap_TRUE.univHist(universe)->Fill(TRUE_distance_nearestWall,wgt_minerva_v1);

            if(Cylindrical_CutAboutZero(r)== true){

              h_Distance_to_upstreamCap_RCut_downstreamConcaveCap.univHist(universe)->Fill(dist_upstreamCap,wgt_minerva_v1);

              h_Distance_to_upstreamCap_RCut_downstreamConcaveCap_TRUE.univHist(universe)->Fill(dist_upstreamCap_TRUE,wgt_minerva_v1);

              h_Distance_to_downstreamCap_RCut_downstreamConcaveCap.univHist(universe)->Fill(dist_downstreamCap,wgt_minerva_v1);

              h_Distance_to_downstreamCap_RCut_downstreamConcaveCap_TRUE.univHist(universe)->Fill(dist_downstreamCap_TRUE,wgt_minerva_v1);

              h_CryoVertex_Z_RCut_downstreamConcaveCap.univHist(universe)->Fill(z ,wgt_minerva_v1);

              h_CryoVertex_Z_RCut_downstreamConcaveCap_TRUE.univHist(universe)->Fill(z_TRUE ,wgt_minerva_v1);


            }

          }
          else{
            std::cout<<"Event not in a region Category: Something is wrong "<<std::endl;assert(false);
          }

          if(isCV(*universe)){



            h_CryoVertex_X_Material.GetComponentHist(Material_type_Event)->Fill(x, wgt_minerva_v1);
            h_CryoVertex_Y_Material.GetComponentHist(Material_type_Event)->Fill(y, wgt_minerva_v1);
            h_CryoVertex_Z_Material.GetComponentHist(Material_type_Event)->Fill(z, wgt_minerva_v1);
            h_Distance_to_InnerTank_Material.GetComponentHist(Material_type_Event)->Fill(Reco_distance_nearestWall, wgt_minerva_v1);
            h_CryoVertex_R_Material.GetComponentHist(Material_type_Event)->Fill(r, wgt_minerva_v1);



            if(CryoTankRegion_type==kUpstream_head)
            {
              h_CryoVertex_X_upstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(x, wgt_minerva_v1);
              h_CryoVertex_Y_upstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(y, wgt_minerva_v1);
              h_CryoVertex_Z_upstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(z, wgt_minerva_v1);
              h_Distance_to_InnerTank_upstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(Reco_distance_nearestWall, wgt_minerva_v1);
              h_CryoVertex_R_upstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(r, wgt_minerva_v1);
            }
            else if(CryoTankRegion_type==kCenter)
            {
              h_CryoVertex_X_barrel_Material.GetComponentHist(Material_type_Event)->Fill(x, wgt_minerva_v1);
              h_CryoVertex_Y_barrel_Material.GetComponentHist(Material_type_Event)->Fill(y, wgt_minerva_v1);
              h_CryoVertex_Z_barrel_Material.GetComponentHist(Material_type_Event)->Fill(z, wgt_minerva_v1);
              h_Distance_to_InnerTank_barrel_Material.GetComponentHist(Material_type_Event)->Fill(Reco_distance_nearestWall, wgt_minerva_v1);
              h_CryoVertex_R_barrel_Material.GetComponentHist(Material_type_Event)->Fill(r, wgt_minerva_v1);
            }
            else if(CryoTankRegion_type==kDownstream_head)
            {
              h_CryoVertex_X_downstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(x, wgt_minerva_v1);
              h_CryoVertex_Y_downstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(y, wgt_minerva_v1);
              h_CryoVertex_Z_downstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(z, wgt_minerva_v1);
              h_Distance_to_InnerTank_downstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(Reco_distance_nearestWall, wgt_minerva_v1);
              h_CryoVertex_R_downstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(r, wgt_minerva_v1);
            }
            else if(CryoTankRegion_type==kDownstream_ConcaveCap)
            {
              h_CryoVertex_X_downstreamConcaveCap_Material.GetComponentHist(Material_type_Event)->Fill(x, wgt_minerva_v1);
              h_CryoVertex_Y_downstreamConcaveCap_Material.GetComponentHist(Material_type_Event)->Fill(y, wgt_minerva_v1);
              h_CryoVertex_Z_downstreamConcaveCap_Material.GetComponentHist(Material_type_Event)->Fill(z, wgt_minerva_v1);
              h_Distance_to_InnerTank_downstreamConcaveCap_Material.GetComponentHist(Material_type_Event)->Fill(Reco_distance_nearestWall, wgt_minerva_v1);
              h_CryoVertex_R_downstreamConcaveCap_Material.GetComponentHist(Material_type_Event)->Fill(r, wgt_minerva_v1);
            }
            else{std::cout<<"Event not in a region Category: Something is wrong "<<std::endl;assert(false);}

            //h_MuonE_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetEmu()*.001, wgt_minerva_v1);
            //h_MuonPZ_Material.GetComponentHist(Material_type_Event)->Fill(PZ, wgt_minerva_v1);
            //h_MuonPT_Material.GetComponentHist(Material_type_Event)->Fill(PT, wgt_minerva_v1);
            //h_MuonTheta_Material.GetComponentHist(Material_type_Event)->Fill(Theta*toDegs, wgt_minerva_v1);

            int mapcount_loop =0;

            double Smearing_X = vertexX_Convolution(generatorFit);
            double Smearing_Y = vertexY_Convolution(generatorFit);

            for ( dog = ZShifts.begin(); dog != ZShifts.end();++dog)
            {

              int i = dog->first.i;
              int j = dog->first.j;
              int k = dog->first.k;


              Index3 ijk{i,j,k};

              double shift = Normal_distrubution_map[ijk](generator);

              double Vertex_Z_OffSet = z + shift;
              double Vertex_X_OffSet = x + Smearing_X;
              double Vertex_Y_OffSet = y + Smearing_Y;
              double Vertex_R_OffSet =  sqrt(Vertex_X_OffSet * Vertex_X_OffSet + Vertex_Y_OffSet * Vertex_Y_OffSet );


              double Vertex_Z_OffSet_TRUE = z_TRUE;
              double Vertex_X_OffSet_TRUE = x_TRUE;
              double Vertex_Y_OffSet_TRUE = y_TRUE;
              double Vertex_R_OffSet_TRUE = r_TRUE;

              //if(IsInFiducalVolumeFromtheInnerEdge(Vertex_R_OffSet, Vertex_Z_OffSet, 50.0  )==false) continue;

              //std::cout<<" index = " << mapcount << " key (i,j,k) =  (" << dog->first.i <<" , "<< dog->first.j<< " , "<< dog->first.k  <<")   OffSet (mean, stddev) =  ( " << dog->second.mean << " , " << dog->second.stddev <<" ) "<<std::endl;
              double dist_upstreamCap_shift = DistanceFromUpStreamBulge(Vertex_Z_OffSet , Vertex_R_OffSet);
              double dist_downstreamCap_shift = DistanceFromDownStreamBulge(Vertex_Z_OffSet , Vertex_R_OffSet);

              double dist_upstreamCap_TRUE_shift = DistanceFromUpStreamBulge(Vertex_Z_OffSet_TRUE , Vertex_R_OffSet_TRUE);
              double dist_downstreamCap_TRUE_shift = DistanceFromDownStreamBulge(Vertex_Z_OffSet_TRUE , Vertex_R_OffSet_TRUE);



              double Distance_shift = RECO_Distance_to_innerTank(Vertex_R_OffSet, Vertex_Z_OffSet  );
              double Distance_TRUE_shift = RECO_Distance_to_innerTank(Vertex_R_OffSet_TRUE, Vertex_Z_OffSet_TRUE  );


              Hist_3index_Map_Z.at(ijk)->Fill(Vertex_Z_OffSet, wgt_minerva_v1);
              Hist_3index_Map_Y.at(ijk)->Fill(Vertex_Y_OffSet, wgt_minerva_v1);
              Hist_3index_Map_X.at(ijk)->Fill(Vertex_X_OffSet, wgt_minerva_v1);
              Hist_3index_Map_R.at(ijk)->Fill(Vertex_R_OffSet, wgt_minerva_v1);
              Hist_3index_DistanceEdge.at(ijk)->Fill(Distance_shift, wgt_minerva_v1);

              Hist_3index_Map_Z_TRUE.at(ijk)->Fill(Vertex_Z_OffSet_TRUE, wgt_minerva_v1);
              Hist_3index_Map_Y_TRUE.at(ijk)->Fill(Vertex_Y_OffSet_TRUE, wgt_minerva_v1);
              Hist_3index_Map_X_TRUE.at(ijk)->Fill(Vertex_X_OffSet_TRUE, wgt_minerva_v1);
              Hist_3index_Map_R_TRUE.at(ijk)->Fill(Vertex_R_OffSet_TRUE, wgt_minerva_v1);
              Hist_3index_DistanceEdge_TRUE.at(ijk)->Fill(Distance_TRUE_shift, wgt_minerva_v1);


              Hist_3index_Map_DistanceupstreamCap.at(ijk)->Fill(dist_upstreamCap_shift ,wgt_minerva_v1);
              Hist_3index_Map_DistancedownstreamCap.at(ijk)->Fill(dist_downstreamCap_shift, wgt_minerva_v1);
              Hist_3index_Map_DistanceupstreamCap_TRUE.at(ijk)->Fill(dist_upstreamCap_TRUE_shift, wgt_minerva_v1);
              Hist_3index_Map_DistancedownstreamCap_TRUE.at(ijk)->Fill(dist_downstreamCap_TRUE_shift, wgt_minerva_v1);



              if(Cylindrical_CutAboutZero(Vertex_R_OffSet)== true){

                Hist_3index_Map_DistanceupstreamCap_RCut.at(ijk)->Fill(dist_upstreamCap_shift ,wgt_minerva_v1);
                Hist_3index_Map_DistancedownstreamCap_RCut.at(ijk)->Fill(dist_downstreamCap_shift, wgt_minerva_v1);
                Hist_3index_Map_DistanceupstreamCap_RCut_TRUE.at(ijk)->Fill(dist_upstreamCap_TRUE_shift, wgt_minerva_v1);
                Hist_3index_Map_DistancedownstreamCap_RCut_TRUE.at(ijk)->Fill(dist_downstreamCap_TRUE_shift, wgt_minerva_v1);
                Hist_3index_Map_Z_RCut_TRUE.at(ijk)->Fill(Vertex_Z_OffSet_TRUE, wgt_minerva_v1);
                Hist_3index_Map_Z_RCut.at(ijk)->Fill(Vertex_Z_OffSet, wgt_minerva_v1);

              }

              CryoTank_REGIONS CryoTankRegion_type = FourRegion_of_CryoTank(Vertex_Z_OffSet_TRUE);

              if(CryoTankRegion_type==kUpstream_head)
              {

                Hist_3index_Map_X_upstreamCap.at(ijk)->Fill(Vertex_X_OffSet, wgt_minerva_v1);
                Hist_3index_Map_Y_upstreamCap.at(ijk)->Fill(Vertex_Y_OffSet, wgt_minerva_v1);
                Hist_3index_Map_R_upstreamCap.at(ijk)->Fill(Vertex_R_OffSet, wgt_minerva_v1);
                Hist_3index_Map_Z_upstreamCap.at(ijk)->Fill(Vertex_Z_OffSet, wgt_minerva_v1);
                Hist_3index_DistanceEdge_upstreamCap.at(ijk)->Fill(Distance_shift, wgt_minerva_v1);

                Hist_3index_Map_X_upstreamCap_TRUE.at(ijk)->Fill(Vertex_X_OffSet_TRUE, wgt_minerva_v1);
                Hist_3index_Map_Y_upstreamCap_TRUE.at(ijk)->Fill(Vertex_Y_OffSet_TRUE, wgt_minerva_v1);
                Hist_3index_Map_R_upstreamCap_TRUE.at(ijk)->Fill(Vertex_R_OffSet_TRUE, wgt_minerva_v1);
                Hist_3index_Map_Z_upstreamCap_TRUE.at(ijk)->Fill(Vertex_Z_OffSet_TRUE, wgt_minerva_v1);
                Hist_3index_DistanceEdge_upstreamCap_TRUE.at(ijk)->Fill(Distance_TRUE_shift, wgt_minerva_v1);

                Hist_3index_Map_DistanceupstreamCap_upstream.at(ijk)->Fill(dist_upstreamCap_shift, wgt_minerva_v1);
                Hist_3index_Map_DistancedownstreamCap_upstream.at(ijk)->Fill(dist_downstreamCap_shift, wgt_minerva_v1);
                Hist_3index_Map_DistanceupstreamCap_upstream_TRUE.at(ijk)->Fill(dist_upstreamCap_TRUE_shift, wgt_minerva_v1);
                Hist_3index_Map_DistancedownstreamCap_upstream_TRUE.at(ijk)->Fill(dist_downstreamCap_TRUE_shift, wgt_minerva_v1);

                HistFolio_3index_Map_X_upstreamcap.at(ijk).GetComponentHist(Material_type_Event)->Fill(Vertex_X_OffSet, wgt_minerva_v1);
                HistFolio_3index_Map_Y_upstreamcap.at(ijk).GetComponentHist(Material_type_Event)->Fill(Vertex_Y_OffSet, wgt_minerva_v1);
                HistFolio_3index_Map_Z_upstreamcap.at(ijk).GetComponentHist(Material_type_Event)->Fill(Vertex_Z_OffSet, wgt_minerva_v1);
                HistFolio_3index_Map_R_upstreamcap.at(ijk).GetComponentHist(Material_type_Event)->Fill(Vertex_R_OffSet, wgt_minerva_v1);




                if(Cylindrical_CutAboutZero(Vertex_R_OffSet)== true){
                  Hist_3index_Map_DistanceupstreamCap_upstream_RCut.at(ijk)->Fill(dist_upstreamCap_shift, wgt_minerva_v1);
                  Hist_3index_Map_DistancedownstreamCap_upstream_RCut.at(ijk)->Fill(dist_downstreamCap_shift, wgt_minerva_v1);
                  Hist_3index_Map_DistanceupstreamCap_upstream_RCut_TRUE.at(ijk)->Fill(dist_upstreamCap_TRUE_shift, wgt_minerva_v1);
                  Hist_3index_Map_DistancedownstreamCap_upstream_RCut_TRUE.at(ijk)->Fill(dist_downstreamCap_TRUE_shift, wgt_minerva_v1);
                  Hist_3index_Map_Z_RCut_upstreamCap_TRUE.at(ijk)->Fill(Vertex_Z_OffSet_TRUE, wgt_minerva_v1);
                  Hist_3index_Map_Z_RCut_upstreamCap.at(ijk)->Fill(Vertex_Z_OffSet, wgt_minerva_v1);
                }

              }


              else if(CryoTankRegion_type==kCenter)
              {
                Hist_3index_Map_X_barrel.at(ijk)->Fill(Vertex_X_OffSet, wgt_minerva_v1);
                Hist_3index_Map_Y_barrel.at(ijk)->Fill(Vertex_Y_OffSet, wgt_minerva_v1);
                Hist_3index_Map_R_barrel.at(ijk)->Fill(Vertex_R_OffSet, wgt_minerva_v1);
                Hist_3index_Map_Z_barrel.at(ijk)->Fill(Vertex_Z_OffSet, wgt_minerva_v1);
                Hist_3index_DistanceEdge_barrel.at(ijk)->Fill(Distance_shift, wgt_minerva_v1);

                Hist_3index_Map_X_barrel_TRUE.at(ijk)->Fill(Vertex_X_OffSet_TRUE, wgt_minerva_v1);
                Hist_3index_Map_Y_barrel_TRUE.at(ijk)->Fill(Vertex_Y_OffSet_TRUE, wgt_minerva_v1);
                Hist_3index_Map_R_barrel_TRUE.at(ijk)->Fill(Vertex_R_OffSet_TRUE, wgt_minerva_v1);
                Hist_3index_Map_Z_barrel_TRUE.at(ijk)->Fill(Vertex_Z_OffSet_TRUE, wgt_minerva_v1);
                Hist_3index_DistanceEdge_barrel_TRUE.at(ijk)->Fill(Distance_TRUE_shift, wgt_minerva_v1);

                Hist_3index_Map_DistanceupstreamCap_barrel.at(ijk)->Fill(dist_upstreamCap_shift, wgt_minerva_v1);
                Hist_3index_Map_DistancedownstreamCap_barrel.at(ijk)->Fill(dist_downstreamCap_shift, wgt_minerva_v1);
                Hist_3index_Map_DistanceupstreamCap_barrel_TRUE.at(ijk)->Fill(dist_upstreamCap_TRUE_shift, wgt_minerva_v1);
                Hist_3index_Map_DistancedownstreamCap_barrel_TRUE.at(ijk)->Fill(dist_downstreamCap_TRUE_shift, wgt_minerva_v1);


                HistFolio_3index_Map_X_barrel.at(ijk).GetComponentHist(Material_type_Event)->Fill(Vertex_X_OffSet, wgt_minerva_v1);
                HistFolio_3index_Map_Y_barrel.at(ijk).GetComponentHist(Material_type_Event)->Fill(Vertex_Y_OffSet, wgt_minerva_v1);
                HistFolio_3index_Map_Z_barrel.at(ijk).GetComponentHist(Material_type_Event)->Fill(Vertex_Z_OffSet, wgt_minerva_v1);
                HistFolio_3index_Map_R_barrel.at(ijk).GetComponentHist(Material_type_Event)->Fill(Vertex_R_OffSet, wgt_minerva_v1);



                if(Cylindrical_CutAboutZero(Vertex_R_OffSet)== true){
                  Hist_3index_Map_Z_RCut_barrel_TRUE.at(ijk)->Fill(Vertex_Z_OffSet_TRUE, wgt_minerva_v1);
                  Hist_3index_Map_Z_RCut_barrel.at(ijk)->Fill(Vertex_Z_OffSet, wgt_minerva_v1);

                  Hist_3index_Map_DistanceupstreamCap_barrel_RCut.at(ijk)->Fill(dist_upstreamCap_shift, wgt_minerva_v1);
                  Hist_3index_Map_DistancedownstreamCap_barrel_RCut.at(ijk)->Fill(dist_downstreamCap_shift, wgt_minerva_v1);
                  Hist_3index_Map_DistanceupstreamCap_barrel_RCut_TRUE.at(ijk)->Fill(dist_upstreamCap_TRUE_shift, wgt_minerva_v1);
                  Hist_3index_Map_DistancedownstreamCap_barrel_RCut_TRUE.at(ijk)->Fill(dist_downstreamCap_TRUE_shift, wgt_minerva_v1);
                }



              }
              else if(CryoTankRegion_type==kDownstream_head)
              {

                Hist_3index_Map_X_downstreamCap.at(ijk)->Fill(Vertex_X_OffSet, wgt_minerva_v1);
                Hist_3index_Map_Y_downstreamCap.at(ijk)->Fill(Vertex_Y_OffSet, wgt_minerva_v1);
                Hist_3index_Map_R_downstreamCap.at(ijk)->Fill(Vertex_R_OffSet, wgt_minerva_v1);
                Hist_3index_Map_Z_downstreamCap.at(ijk)->Fill(Vertex_Z_OffSet, wgt_minerva_v1);
                Hist_3index_DistanceEdge_downstreamCap.at(ijk)->Fill(Distance_shift, wgt_minerva_v1);

                Hist_3index_Map_X_downstreamCap_TRUE.at(ijk)->Fill(Vertex_X_OffSet_TRUE, wgt_minerva_v1);
                Hist_3index_Map_Y_downstreamCap_TRUE.at(ijk)->Fill(Vertex_Y_OffSet_TRUE, wgt_minerva_v1);
                Hist_3index_Map_R_downstreamCap_TRUE.at(ijk)->Fill(Vertex_R_OffSet_TRUE, wgt_minerva_v1);
                Hist_3index_Map_Z_downstreamCap_TRUE.at(ijk)->Fill(Vertex_Z_OffSet_TRUE, wgt_minerva_v1);
                Hist_3index_DistanceEdge_downstreamCap_TRUE.at(ijk)->Fill(Distance_TRUE_shift, wgt_minerva_v1);

                Hist_3index_Map_DistanceupstreamCap_downstreamCap.at(ijk)->Fill(dist_upstreamCap_shift ,wgt_minerva_v1);
                Hist_3index_Map_DistancedownstreamCap_downstreamCap.at(ijk)->Fill(dist_downstreamCap_shift, wgt_minerva_v1);
                Hist_3index_Map_DistanceupstreamCap_downstreamCap_TRUE.at(ijk)->Fill(dist_upstreamCap_TRUE_shift, wgt_minerva_v1);
                Hist_3index_Map_DistancedownstreamCap_downstreamCap_TRUE.at(ijk)->Fill(dist_downstreamCap_TRUE_shift, wgt_minerva_v1);

                HistFolio_3index_Map_X_downstreamcap.at(ijk).GetComponentHist(Material_type_Event)->Fill(Vertex_X_OffSet, wgt_minerva_v1);
                HistFolio_3index_Map_Y_downstreamcap.at(ijk).GetComponentHist(Material_type_Event)->Fill(Vertex_Y_OffSet, wgt_minerva_v1);
                HistFolio_3index_Map_Z_downstreamcap.at(ijk).GetComponentHist(Material_type_Event)->Fill(Vertex_Z_OffSet, wgt_minerva_v1);
                HistFolio_3index_Map_R_downstreamcap.at(ijk).GetComponentHist(Material_type_Event)->Fill(Vertex_R_OffSet, wgt_minerva_v1);


                if(Cylindrical_CutAboutZero(Vertex_R_OffSet)== true){
                  Hist_3index_Map_DistanceupstreamCap_downstreamCap_RCut.at(ijk)->Fill(dist_upstreamCap_shift ,wgt_minerva_v1);
                  Hist_3index_Map_DistancedownstreamCap_downstreamCap_RCut.at(ijk)->Fill(dist_downstreamCap_shift, wgt_minerva_v1);
                  Hist_3index_Map_DistanceupstreamCap_downstreamCap_RCut_TRUE.at(ijk)->Fill(dist_upstreamCap_TRUE_shift, wgt_minerva_v1);
                  Hist_3index_Map_DistancedownstreamCap_downstreamCap_RCut_TRUE.at(ijk)->Fill(dist_downstreamCap_TRUE_shift, wgt_minerva_v1);
                  Hist_3index_Map_Z_RCut_downstreamCap_TRUE.at(ijk)->Fill(Vertex_Z_OffSet_TRUE, wgt_minerva_v1);
                  Hist_3index_Map_Z_RCut_downstreamCap.at(ijk)->Fill(Vertex_Z_OffSet, wgt_minerva_v1);

                }



              }
              else if(CryoTankRegion_type==kDownstream_ConcaveCap)
              {
                Hist_3index_Map_X_downstreamconcavecap.at(ijk)->Fill(Vertex_X_OffSet, wgt_minerva_v1);
                Hist_3index_Map_Y_downstreamconcavecap.at(ijk)->Fill(Vertex_Y_OffSet, wgt_minerva_v1);
                Hist_3index_Map_R_downstreamconcavecap.at(ijk)->Fill(Vertex_R_OffSet, wgt_minerva_v1);
                Hist_3index_Map_Z_downstreamconcavecap.at(ijk)->Fill(Vertex_Z_OffSet, wgt_minerva_v1);
                Hist_3index_DistanceEdge_downstreamconcavecap.at(ijk)->Fill(Distance_shift, wgt_minerva_v1);

                Hist_3index_Map_X_downstreamconcavecap_TRUE.at(ijk)->Fill(Vertex_X_OffSet_TRUE, wgt_minerva_v1);
                Hist_3index_Map_Y_downstreamconcavecap_TRUE.at(ijk)->Fill(Vertex_Y_OffSet_TRUE, wgt_minerva_v1);
                Hist_3index_Map_R_downstreamconcavecap_TRUE.at(ijk)->Fill(Vertex_R_OffSet_TRUE, wgt_minerva_v1);
                Hist_3index_Map_Z_downstreamconcavecap_TRUE.at(ijk)->Fill(Vertex_Z_OffSet_TRUE, wgt_minerva_v1);
                Hist_3index_DistanceEdge_downstreamconcavecap_TRUE.at(ijk)->Fill(Distance_TRUE_shift, wgt_minerva_v1);

                Hist_3index_Map_DistanceupstreamCap_downstreamconcavecap.at(ijk)->Fill(dist_upstreamCap_shift, wgt_minerva_v1);
                Hist_3index_Map_DistancedownstreamCap_downstreamconcavecap.at(ijk)->Fill(dist_downstreamCap_shift, wgt_minerva_v1);
                Hist_3index_Map_DistanceupstreamCap_downstreamconcavecap_TRUE.at(ijk)->Fill(dist_upstreamCap_TRUE_shift, wgt_minerva_v1);
                Hist_3index_Map_DistancedownstreamCap_downstreamconcavecap_TRUE.at(ijk)->Fill(dist_downstreamCap_TRUE_shift, wgt_minerva_v1);

                HistFolio_3index_Map_X_downstreamconcavecap.at(ijk).GetComponentHist(Material_type_Event)->Fill(Vertex_X_OffSet, wgt_minerva_v1);
                HistFolio_3index_Map_Y_downstreamconcavecap.at(ijk).GetComponentHist(Material_type_Event)->Fill(Vertex_Y_OffSet, wgt_minerva_v1);
                HistFolio_3index_Map_Z_downstreamconcavecap.at(ijk).GetComponentHist(Material_type_Event)->Fill(Vertex_Z_OffSet, wgt_minerva_v1);
                HistFolio_3index_Map_R_downstreamconcavecap.at(ijk).GetComponentHist(Material_type_Event)->Fill(Vertex_R_OffSet, wgt_minerva_v1);


                if(Cylindrical_CutAboutZero(Vertex_R_OffSet)== true){
                  Hist_3index_Map_DistanceupstreamCap_downstreamconcavecap_RCut.at(ijk)->Fill(dist_upstreamCap_shift, wgt_minerva_v1);
                  Hist_3index_Map_DistancedownstreamCap_downstreamconcavecap_RCut.at(ijk)->Fill(dist_downstreamCap_shift, wgt_minerva_v1);
                  Hist_3index_Map_DistanceupstreamCap_downstreamconcavecap_RCut_TRUE.at(ijk)->Fill(dist_upstreamCap_TRUE_shift, wgt_minerva_v1);
                  Hist_3index_Map_DistancedownstreamCap_downstreamconcavecap_RCut_TRUE.at(ijk)->Fill(dist_downstreamCap_TRUE_shift, wgt_minerva_v1);
                  Hist_3index_Map_Z_RCut_downstreamconcavecap_TRUE.at(ijk)->Fill(Vertex_Z_OffSet_TRUE, wgt_minerva_v1);
                  Hist_3index_Map_Z_RCut_downstreamconcavecap.at(ijk)->Fill(Vertex_Z_OffSet, wgt_minerva_v1);

                }



              }
              else{std::cout<<"ABSURDITY !! Event Failed to be in a  CryoRegion: Something Wrong"<<std::endl; assert(false);}

              //mapcount_loop++;
            }

          } // end of CV

        }// END of Universe Groups
      }// END OF RECO CUTS

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
  //=========================================
  // Plot stuff
  //=========================================

  //h_MuonPZ.SyncCVHistos();
  //h_MuonPT.SyncCVHistos();
  //h_MuonE.SyncCVHistos();
  //h_MuonTheta.SyncCVHistos();
  h_CryoVertex_X.SyncCVHistos();
  h_CryoVertex_Y.SyncCVHistos();
  h_CryoVertex_Z.SyncCVHistos();
  h_CryoVertex_R.SyncCVHistos();

  h_CryoVertex_X_TRUE.SyncCVHistos();
  h_CryoVertex_Y_TRUE.SyncCVHistos();
  h_CryoVertex_Z_TRUE.SyncCVHistos();
  h_CryoVertex_R_TRUE.SyncCVHistos();
  h_Distance_to_InnerTank.SyncCVHistos();
  h_Distance_to_InnerTank_TRUE.SyncCVHistos();
  h_Distance_to_InnerTank.SyncCVHistos();
  h_Distance_to_InnerTank_TRUE.SyncCVHistos();
  h_Distance_to_InnerTank_upstreamCap.SyncCVHistos();
  h_Distance_to_InnerTank_upstreamCap_TRUE.SyncCVHistos();
  h_Distance_to_InnerTank_barrel.SyncCVHistos();
  h_Distance_to_InnerTank_barrel_TRUE.SyncCVHistos();
  h_Distance_to_InnerTank_downstreamCap.SyncCVHistos();
  h_Distance_to_InnerTank_downstreamCap_TRUE.SyncCVHistos();
  h_Distance_to_InnerTank_downstreamConcaveCap.SyncCVHistos();
  h_Distance_to_InnerTank_downstreamConcaveCap_TRUE.SyncCVHistos();
  h_Distance_to_upstreamCap.SyncCVHistos();
  h_Distance_to_upstreamCap_TRUE.SyncCVHistos();
  h_Distance_to_downstreamCap.SyncCVHistos();
  h_Distance_to_downstreamCap_TRUE.SyncCVHistos();
  h_CryoVertex_X_upstreamCap.SyncCVHistos();
  h_CryoVertex_Y_upstreamCap.SyncCVHistos();
  h_CryoVertex_Z_upstreamCap.SyncCVHistos();
  h_CryoVertex_R_upstreamCap.SyncCVHistos();
  h_CryoVertex_X_upstreamCap_TRUE.SyncCVHistos();
  h_CryoVertex_Y_upstreamCap_TRUE.SyncCVHistos();
  h_CryoVertex_Z_upstreamCap_TRUE.SyncCVHistos();
  h_CryoVertex_R_upstreamCap_TRUE.SyncCVHistos();
  h_CryoVertex_X_barrel.SyncCVHistos();
  h_CryoVertex_Y_barrel.SyncCVHistos();
  h_CryoVertex_Z_barrel.SyncCVHistos();
  h_CryoVertex_R_barrel.SyncCVHistos();
  h_CryoVertex_X_barrel_TRUE.SyncCVHistos();
  h_CryoVertex_Y_barrel_TRUE.SyncCVHistos();
  h_CryoVertex_Z_barrel_TRUE.SyncCVHistos();
  h_CryoVertex_R_barrel_TRUE.SyncCVHistos();
  h_CryoVertex_X_downstreamCap.SyncCVHistos();
  h_CryoVertex_Y_downstreamCap.SyncCVHistos();
  h_CryoVertex_Z_downstreamCap.SyncCVHistos();
  h_CryoVertex_R_downstreamCap.SyncCVHistos();
  h_CryoVertex_X_downstreamCap_TRUE.SyncCVHistos();
  h_CryoVertex_Y_downstreamCap_TRUE.SyncCVHistos();
  h_CryoVertex_Z_downstreamCap_TRUE.SyncCVHistos();
  h_CryoVertex_R_downstreamCap_TRUE.SyncCVHistos();
  h_CryoVertex_X_downstreamConcaveCap.SyncCVHistos();
  h_CryoVertex_Y_downstreamConcaveCap.SyncCVHistos();
  h_CryoVertex_Z_downstreamConcaveCap.SyncCVHistos();
  h_CryoVertex_R_downstreamConcaveCap.SyncCVHistos();
  h_CryoVertex_X_downstreamConcaveCap_TRUE.SyncCVHistos();
  h_CryoVertex_Y_downstreamConcaveCap_TRUE.SyncCVHistos();
  h_CryoVertex_Z_downstreamConcaveCap_TRUE.SyncCVHistos();
  h_CryoVertex_R_downstreamConcaveCap_TRUE.SyncCVHistos();

  h_CryoVertex_Z_RCut.SyncCVHistos();
  h_CryoVertex_Z_RCut_TRUE.SyncCVHistos();
  h_CryoVertex_Z_RCut_upstreamCap.SyncCVHistos();
  h_CryoVertex_Z_RCut_upstreamCap_TRUE.SyncCVHistos();
  h_CryoVertex_Z_RCut_barrel.SyncCVHistos();
  h_CryoVertex_Z_RCut_barrel_TRUE.SyncCVHistos();
  h_CryoVertex_Z_RCut_downstreamCap.SyncCVHistos();
  h_CryoVertex_Z_RCut_downstreamCap_TRUE.SyncCVHistos();
  h_CryoVertex_Z_RCut_downstreamConcaveCap.SyncCVHistos();
  h_CryoVertex_Z_RCut_downstreamConcaveCap_TRUE.SyncCVHistos();


  h_Distance_to_upstreamCap.SyncCVHistos();
  h_Distance_to_upstreamCap_TRUE.SyncCVHistos();
  h_Distance_to_downstreamCap.SyncCVHistos();
  h_Distance_to_downstreamCap_TRUE.SyncCVHistos();


  h_Distance_to_upstreamCap_upstreamCap.SyncCVHistos();
  h_Distance_to_upstreamCap_upstreamCap_TRUE.SyncCVHistos();
  h_Distance_to_downstreamCap_upstreamCap.SyncCVHistos();
  h_Distance_to_downstreamCap_upstreamCap_TRUE.SyncCVHistos();
  h_Distance_to_upstreamCap_barrel.SyncCVHistos();
  h_Distance_to_upstreamCap_barrel_TRUE.SyncCVHistos();
  h_Distance_to_downstreamCap_barrel.SyncCVHistos();
  h_Distance_to_downstreamCap_barrel_TRUE.SyncCVHistos();
  h_Distance_to_upstreamCap_downstreamCap.SyncCVHistos();
  h_Distance_to_upstreamCap_downstreamCap_TRUE.SyncCVHistos();
  h_Distance_to_downstreamCap_downstreamCap.SyncCVHistos();
  h_Distance_to_downstreamCap_downstreamCap_TRUE.SyncCVHistos();
  h_Distance_to_upstreamCap_downstreamConcaveCap.SyncCVHistos();
  h_Distance_to_upstreamCap_downstreamConcaveCap_TRUE.SyncCVHistos();
  h_Distance_to_downstreamCap_downstreamConcaveCap.SyncCVHistos();
  h_Distance_to_downstreamCap_downstreamConcaveCap_TRUE.SyncCVHistos();


  h_Distance_to_upstreamCap_RCut.SyncCVHistos();
  h_Distance_to_upstreamCap_RCut_TRUE.SyncCVHistos();
  h_Distance_to_downstreamCap_RCut.SyncCVHistos();
  h_Distance_to_downstreamCap_RCut_TRUE.SyncCVHistos();
  h_Distance_to_upstreamCap_RCut_upstreamCap.SyncCVHistos();
  h_Distance_to_upstreamCap_RCut_upstreamCap_TRUE.SyncCVHistos();
  h_Distance_to_downstreamCap_RCut_upstreamCap.SyncCVHistos();
  h_Distance_to_downstreamCap_RCut_upstreamCap_TRUE.SyncCVHistos();
  h_Distance_to_upstreamCap_RCut_barrel.SyncCVHistos();
  h_Distance_to_upstreamCap_RCut_barrel_TRUE.SyncCVHistos();
  h_Distance_to_downstreamCap_RCut_barrel.SyncCVHistos();
  h_Distance_to_downstreamCap_RCut_barrel_TRUE.SyncCVHistos();
  h_Distance_to_upstreamCap_RCut_downstreamCap.SyncCVHistos();
  h_Distance_to_upstreamCap_RCut_downstreamCap_TRUE.SyncCVHistos();
  h_Distance_to_downstreamCap_RCut_downstreamCap.SyncCVHistos();
  h_Distance_to_downstreamCap_RCut_downstreamCap_TRUE.SyncCVHistos();
  h_Distance_to_upstreamCap_RCut_downstreamConcaveCap.SyncCVHistos();
  h_Distance_to_upstreamCap_RCut_downstreamConcaveCap_TRUE.SyncCVHistos();
  h_Distance_to_downstreamCap_RCut_downstreamConcaveCap.SyncCVHistos();
  h_Distance_to_downstreamCap_RCut_downstreamConcaveCap_TRUE.SyncCVHistos();



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


  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~ RECO Eff cuts ~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;

  if(Run_EventLoopOnGid==true){
    sprintf(outFileName, "%s_%s_%s_%s_ConvolutionZ_noShift_noWgts.root", "Histograms",c,d,ErrorStatus);
    std::cout << "Writing output file on Grid to: " <<outFileName << std::endl;

  }
  else{
    sprintf(outFileName, "%s/%s_%s_%s_%s_ConvolutionZ_noShift_noWgts.root", rootpathway, "Histograms",c,d,ErrorStatus);
    std::cout << "Writing output file to: " <<outFileName << std::endl;

  }


  //TFile *outFile(outFileName, "RECREATE");
  TFile *outFile = new TFile(outFileName,"RECREATE");
  TChain POT_branch("Meta");
  POT_branch.Add(RootName.c_str());
  //TTree *oldtree = (TTree*)file->Get("Meta");
  TTree *clone = POT_branch.CloneTree();
  clone->Write();

  std::cout << "Writing output file for ZShifts " << std::endl;

for ( dog = ZShifts.begin(); dog != ZShifts.end();++dog)
{

  int i = dog->first.i;
  int j = dog->first.j;
  int k = dog->first.k;

//  Index3 ijk{dog->first.i,dog->first.j,dog->first.k};

  Index3 ijk{i,j,k};

  Hist_3index_Map_Z.at(ijk)->Write();
  Hist_3index_Map_Y.at(ijk)->Write();
  Hist_3index_Map_X.at(ijk)->Write();
  Hist_3index_Map_R.at(ijk)->Write();
  Hist_3index_DistanceEdge.at(ijk)->Write();
  Hist_3index_Map_Z_TRUE.at(ijk)->Write();
  Hist_3index_Map_Z_RCut_TRUE.at(ijk)->Write();
  Hist_3index_Map_Z_RCut.at(ijk)->Write();
  Hist_3index_Map_Y_TRUE.at(ijk)->Write();
  Hist_3index_Map_X_TRUE.at(ijk)->Write();
  Hist_3index_Map_R_TRUE.at(ijk)->Write();
  Hist_3index_DistanceEdge_TRUE.at(ijk)->Write();


  Hist_3index_Map_X_upstreamCap.at(ijk)->Write();
  Hist_3index_Map_Y_upstreamCap.at(ijk)->Write();
  Hist_3index_Map_R_upstreamCap.at(ijk)->Write();
  Hist_3index_Map_Z_upstreamCap.at(ijk)->Write();
  Hist_3index_DistanceEdge_upstreamCap.at(ijk)->Write();
  Hist_3index_Map_X_barrel.at(ijk)->Write();
  Hist_3index_Map_Y_barrel.at(ijk)->Write();
  Hist_3index_Map_R_barrel.at(ijk)->Write();
  Hist_3index_Map_Z_barrel.at(ijk)->Write();
  Hist_3index_DistanceEdge_barrel.at(ijk)->Write();
  Hist_3index_Map_X_downstreamCap.at(ijk)->Write();
  Hist_3index_Map_Y_downstreamCap.at(ijk)->Write();
  Hist_3index_Map_R_downstreamCap.at(ijk)->Write();
  Hist_3index_Map_Z_downstreamCap.at(ijk)->Write();
  Hist_3index_DistanceEdge_downstreamCap.at(ijk)->Write();
  Hist_3index_Map_X_downstreamconcavecap.at(ijk)->Write();
  Hist_3index_Map_Y_downstreamconcavecap.at(ijk)->Write();
  Hist_3index_Map_R_downstreamconcavecap.at(ijk)->Write();
  Hist_3index_Map_Z_downstreamconcavecap.at(ijk)->Write();
  Hist_3index_DistanceEdge_downstreamconcavecap.at(ijk)->Write();

  Hist_3index_Map_X_upstreamCap_TRUE.at(ijk)->Write();
  Hist_3index_Map_Y_upstreamCap_TRUE.at(ijk)->Write();
  Hist_3index_Map_R_upstreamCap_TRUE.at(ijk)->Write();
  Hist_3index_Map_Z_upstreamCap_TRUE.at(ijk)->Write();
  Hist_3index_Map_Z_RCut_upstreamCap_TRUE.at(ijk)->Write();
  Hist_3index_Map_Z_RCut_upstreamCap.at(ijk)->Write();

  Hist_3index_DistanceEdge_upstreamCap_TRUE.at(ijk)->Write();
  Hist_3index_Map_X_barrel_TRUE.at(ijk)->Write();
  Hist_3index_Map_Y_barrel_TRUE.at(ijk)->Write();
  Hist_3index_Map_R_barrel_TRUE.at(ijk)->Write();
  Hist_3index_Map_Z_barrel_TRUE.at(ijk)->Write();
  Hist_3index_Map_Z_RCut_barrel_TRUE.at(ijk)->Write();
  Hist_3index_Map_Z_RCut_barrel.at(ijk)->Write();

  Hist_3index_DistanceEdge_barrel_TRUE.at(ijk)->Write();
  Hist_3index_Map_X_downstreamCap_TRUE.at(ijk)->Write();
  Hist_3index_Map_Y_downstreamCap_TRUE.at(ijk)->Write();
  Hist_3index_Map_R_downstreamCap_TRUE.at(ijk)->Write();
  Hist_3index_Map_Z_downstreamCap_TRUE.at(ijk)->Write();
  Hist_3index_Map_Z_RCut_downstreamCap_TRUE.at(ijk)->Write();
  Hist_3index_Map_Z_RCut_downstreamCap.at(ijk)->Write();
  Hist_3index_DistanceEdge_downstreamCap_TRUE.at(ijk)->Write();
  Hist_3index_Map_X_downstreamconcavecap_TRUE.at(ijk)->Write();
  Hist_3index_Map_Y_downstreamconcavecap_TRUE.at(ijk)->Write();
  Hist_3index_Map_R_downstreamconcavecap_TRUE.at(ijk)->Write();
  Hist_3index_Map_Z_downstreamconcavecap_TRUE.at(ijk)->Write();
  Hist_3index_Map_Z_RCut_downstreamconcavecap_TRUE.at(ijk)->Write();
  Hist_3index_Map_Z_RCut_downstreamconcavecap.at(ijk)->Write();
  Hist_3index_DistanceEdge_downstreamconcavecap_TRUE.at(ijk)->Write();


  Hist_3index_Map_DistanceupstreamCap_RCut.at(ijk)->Write();
  Hist_3index_Map_DistancedownstreamCap_RCut.at(ijk)->Write();
  Hist_3index_Map_DistanceupstreamCap_RCut_TRUE.at(ijk)->Write();
  Hist_3index_Map_DistancedownstreamCap_RCut_TRUE.at(ijk)->Write();
  Hist_3index_Map_DistanceupstreamCap_upstream_RCut.at(ijk)->Write();
  Hist_3index_Map_DistancedownstreamCap_upstream_RCut.at(ijk)->Write();
  Hist_3index_Map_DistanceupstreamCap_upstream_RCut_TRUE.at(ijk)->Write();
  Hist_3index_Map_DistancedownstreamCap_upstream_RCut_TRUE.at(ijk)->Write();
  Hist_3index_Map_DistanceupstreamCap_barrel_RCut.at(ijk)->Write();
  Hist_3index_Map_DistancedownstreamCap_barrel_RCut.at(ijk)->Write();
  Hist_3index_Map_DistanceupstreamCap_barrel_RCut_TRUE.at(ijk)->Write();
  Hist_3index_Map_DistancedownstreamCap_barrel_RCut_TRUE.at(ijk)->Write();
  Hist_3index_Map_DistanceupstreamCap_downstreamCap_RCut.at(ijk)->Write();
  Hist_3index_Map_DistancedownstreamCap_downstreamCap_RCut.at(ijk)->Write();
  Hist_3index_Map_DistanceupstreamCap_downstreamCap_RCut_TRUE.at(ijk)->Write();
  Hist_3index_Map_DistancedownstreamCap_downstreamCap_RCut_TRUE.at(ijk)->Write();
  Hist_3index_Map_DistanceupstreamCap_downstreamconcavecap_RCut.at(ijk)->Write();
  Hist_3index_Map_DistancedownstreamCap_downstreamconcavecap_RCut.at(ijk)->Write();
  Hist_3index_Map_DistanceupstreamCap_downstreamconcavecap_RCut_TRUE.at(ijk)->Write();
  Hist_3index_Map_DistancedownstreamCap_downstreamconcavecap_RCut_TRUE.at(ijk)->Write();
/// no RCut

  Hist_3index_Map_DistanceupstreamCap.at(ijk)->Write();
  Hist_3index_Map_DistancedownstreamCap.at(ijk)->Write();
  Hist_3index_Map_DistanceupstreamCap_TRUE.at(ijk)->Write();
  Hist_3index_Map_DistancedownstreamCap_TRUE.at(ijk)->Write();
  Hist_3index_Map_DistanceupstreamCap_upstream.at(ijk)->Write();
  Hist_3index_Map_DistancedownstreamCap_upstream.at(ijk)->Write();
  Hist_3index_Map_DistanceupstreamCap_upstream_TRUE.at(ijk)->Write();
  Hist_3index_Map_DistancedownstreamCap_upstream_TRUE.at(ijk)->Write();
  Hist_3index_Map_DistanceupstreamCap_barrel.at(ijk)->Write();
  Hist_3index_Map_DistancedownstreamCap_barrel.at(ijk)->Write();
  Hist_3index_Map_DistanceupstreamCap_barrel_TRUE.at(ijk)->Write();
  Hist_3index_Map_DistancedownstreamCap_barrel_TRUE.at(ijk)->Write();
  Hist_3index_Map_DistanceupstreamCap_downstreamCap.at(ijk)->Write();
  Hist_3index_Map_DistancedownstreamCap_downstreamCap.at(ijk)->Write();
  Hist_3index_Map_DistanceupstreamCap_downstreamCap_TRUE.at(ijk)->Write();
  Hist_3index_Map_DistancedownstreamCap_downstreamCap_TRUE.at(ijk)->Write();
  Hist_3index_Map_DistanceupstreamCap_downstreamconcavecap.at(ijk)->Write();
  Hist_3index_Map_DistancedownstreamCap_downstreamconcavecap.at(ijk)->Write();
  Hist_3index_Map_DistanceupstreamCap_downstreamconcavecap_TRUE.at(ijk)->Write();
  Hist_3index_Map_DistancedownstreamCap_downstreamconcavecap_TRUE.at(ijk)->Write();

  HistFolio_3index_Map_X_upstreamcap.at(ijk).WriteToFile(*outFile);
  HistFolio_3index_Map_Y_upstreamcap.at(ijk).WriteToFile(*outFile);
  HistFolio_3index_Map_Z_upstreamcap.at(ijk).WriteToFile(*outFile);
  HistFolio_3index_Map_R_upstreamcap.at(ijk).WriteToFile(*outFile);
  HistFolio_3index_Map_X_barrel.at(ijk).WriteToFile(*outFile);
  HistFolio_3index_Map_Y_barrel.at(ijk).WriteToFile(*outFile);
  HistFolio_3index_Map_Z_barrel.at(ijk).WriteToFile(*outFile);
  HistFolio_3index_Map_R_barrel.at(ijk).WriteToFile(*outFile);
  HistFolio_3index_Map_X_downstreamcap.at(ijk).WriteToFile(*outFile);
  HistFolio_3index_Map_Y_downstreamcap.at(ijk).WriteToFile(*outFile);
  HistFolio_3index_Map_Z_downstreamcap.at(ijk).WriteToFile(*outFile);
  HistFolio_3index_Map_R_downstreamcap.at(ijk).WriteToFile(*outFile);
  HistFolio_3index_Map_X_downstreamconcavecap.at(ijk).WriteToFile(*outFile);
  HistFolio_3index_Map_Y_downstreamconcavecap.at(ijk).WriteToFile(*outFile);
  HistFolio_3index_Map_Z_downstreamconcavecap.at(ijk).WriteToFile(*outFile);
  HistFolio_3index_Map_R_downstreamconcavecap.at(ijk).WriteToFile(*outFile);


}
/*
std::cout << "Writing output file for OffSetMapZ_YOffSet_constantX " << std::endl;

for ( dog = OffSetMapZ_YOffSet_constantX.begin(); dog != OffSetMapZ_YOffSet_constantX.end();++dog)
{
  int i = dog->first.i;
  int j = dog->first.j;
  int k = dog->first.k;

  Index3 ijk{i,j,k};

  Hist_3index_Map_Z_Y_Z.at(ijk)->Write();
  Hist_3index_Map_Z_Y_Y.at(ijk)->Write();
  Hist_3index_Map_Z_Y_R.at(ijk)->Write();
  Hist_3index_Map_Z_Y.at(ijk)->Write();
  Hist_3index_Map_Z_Y_DistanceEdge.at(ijk)->Write();

}
std::cout << "Writing output file for OffSetMapZ_XOffSet_constantY " << std::endl;
for ( dog = OffSetMapZ_XOffSet_constantY.begin(); dog != OffSetMapZ_XOffSet_constantY.end();++dog)
{
  int i = dog->first.i;
  int j = dog->first.j;
  int k = dog->first.k;

  Index3 ijk{i,j,k};

  Hist_3index_Map_Z_X_Z.at(ijk)->Write();
  Hist_3index_Map_Z_X_X.at(ijk)->Write();
  Hist_3index_Map_Z_X_R.at(ijk)->Write();
  Hist_3index_Map_Z_X.at(ijk)->Write();
  Hist_3index_Map_Z_X_DistanceEdge.at(ijk)->Write();

}

std::cout << "Writing output file for  OffSetMapZ_OffSet_constantXYY " << std::endl;

for ( dog = OffSetMapZ_OffSet_constantXY.begin(); dog != OffSetMapZ_OffSet_constantXY.end();++dog)
{
  int i = dog->first.i;
  int j = dog->first.j;
  int k = dog->first.k;

  Index3 ijk{i,j,k};

  Hist_3index_Map_constantXY_ZOffSet.at(ijk)->Write();
  Hist_3index_Map_constantXY_DistanceEdge.at(ijk)->Write();

}
*/
std::cout << "Writing output file for  Stacks" << std::endl;

  //h_MuonE_Material.WriteToFile(*outFile);
  //h_MuonPZ_Material.WriteToFile(*outFile);
  //h_MuonPT_Material.WriteToFile(*outFile);
  //h_MuonTheta_Material.WriteToFile(*outFile);
  h_CryoVertex_X_Material.WriteToFile(*outFile);
  h_CryoVertex_Y_Material.WriteToFile(*outFile);
  h_CryoVertex_Z_Material.WriteToFile(*outFile);
  h_CryoVertex_R_Material.WriteToFile(*outFile);
  h_Distance_to_InnerTank_Material.WriteToFile(*outFile);


  h_CryoVertex_X_upstreamCap_Material.WriteToFile(*outFile);
  h_CryoVertex_Y_upstreamCap_Material.WriteToFile(*outFile);
  h_CryoVertex_Z_upstreamCap_Material.WriteToFile(*outFile);
  h_CryoVertex_R_upstreamCap_Material.WriteToFile(*outFile);
  h_Distance_to_InnerTank_upstreamCap_Material.WriteToFile(*outFile);

  h_CryoVertex_X_barrel_Material.WriteToFile(*outFile);
  h_CryoVertex_Y_barrel_Material.WriteToFile(*outFile);
  h_CryoVertex_Z_barrel_Material.WriteToFile(*outFile);
  h_CryoVertex_R_barrel_Material.WriteToFile(*outFile);
  h_Distance_to_InnerTank_barrel_Material.WriteToFile(*outFile);

  h_CryoVertex_X_downstreamCap_Material.WriteToFile(*outFile);
  h_CryoVertex_Y_downstreamCap_Material.WriteToFile(*outFile);
  h_CryoVertex_Z_downstreamCap_Material.WriteToFile(*outFile);
  h_CryoVertex_R_downstreamCap_Material.WriteToFile(*outFile);
  h_Distance_to_InnerTank_downstreamCap_Material.WriteToFile(*outFile);

  h_CryoVertex_X_downstreamConcaveCap_Material.WriteToFile(*outFile);
  h_CryoVertex_Y_downstreamConcaveCap_Material.WriteToFile(*outFile);
  h_CryoVertex_Z_downstreamConcaveCap_Material.WriteToFile(*outFile);
  h_CryoVertex_R_downstreamConcaveCap_Material.WriteToFile(*outFile);
  h_Distance_to_InnerTank_downstreamConcaveCap_Material.WriteToFile(*outFile);

  //h_MuonE.hist->Write();
  //PlotUtils::MnvH1D* h_MuonE_FluxIntegrated = PlotUtils::flux_reweighter(playlist_fluxreweighter, nu_pdg, useNuEconstraint, NFlux_universe).GetIntegratedFluxReweighted(nu_pdg, h_MuonE.hist, Min_NuFluxEnergy, Max_NuFluxEnergy, useMuonCorrelations);//GetRebinnedFluxReweighted (nu_pdg, h_MuonE.hist);
  //h_MuonE_FluxIntegrated->Clone()->Write("h_MuonE_FluxIntegrated");


  //h_MuonPZ.hist->Write();
  //PlotUtils::MnvH1D* h_MuonPZ_FluxIntegrated = PlotUtils::flux_reweighter(playlist_fluxreweighter, nu_pdg, useNuEconstraint, NFlux_universe).GetIntegratedFluxReweighted(nu_pdg, h_MuonPZ.hist, Min_NuFluxEnergy, Max_NuFluxEnergy, useMuonCorrelations); //GetRebinnedFluxReweighted (nu_pdg, h_MuonPZ.hist);
  //h_MuonPZ_FluxIntegrated->Clone()->Write("h_MuonPZ_FluxIntegrated");


  //h_MuonPT.hist->Write();
  //PlotUtils::MnvH1D* h_MuonPT_FluxIntegrated = PlotUtils::flux_reweighter(playlist_fluxreweighter, nu_pdg, useNuEconstraint, NFlux_universe).GetIntegratedFluxReweighted(nu_pdg, h_MuonPT.hist, Min_NuFluxEnergy, Max_NuFluxEnergy, useMuonCorrelations);//GetRebinnedFluxReweighted(nu_pdg, h_MuonPT.hist);
  //h_MuonPT_FluxIntegrated->Clone()->Write("h_MuonPT_FluxIntegrated");

  //h_MuonTheta.hist->Write();
  //PlotUtils::MnvH1D* h_MuonTheta_FluxIntegrated = PlotUtils::flux_reweighter(playlist_fluxreweighter, nu_pdg, useNuEconstraint, NFlux_universe).GetIntegratedFluxReweighted(nu_pdg, h_MuonTheta.hist, Min_NuFluxEnergy, Max_NuFluxEnergy, useMuonCorrelations); //GetRebinnedFluxReweighted(nu_pdg, h_MuonTheta.hist);
  //h_MuonTheta_FluxIntegrated->Clone()->Write("h_MuonTheta_FluxIntegrated");

  h_CryoVertex_X.hist->Write();
  h_CryoVertex_Y.hist->Write();
  h_CryoVertex_Z.hist->Write();
  h_CryoVertex_R.hist->Write();
  h_CryoVertex_X_TRUE.hist->Write();
  h_CryoVertex_Y_TRUE.hist->Write();
  h_CryoVertex_Z_TRUE.hist->Write();
  h_CryoVertex_R_TRUE.hist->Write();
  h_Distance_to_InnerTank.hist->Write();
  h_Distance_to_InnerTank_TRUE.hist->Write();
  h_Distance_to_InnerTank.hist->Write();
  h_Distance_to_InnerTank_TRUE.hist->Write();
  h_Distance_to_InnerTank_upstreamCap.hist->Write();
  h_Distance_to_InnerTank_upstreamCap_TRUE.hist->Write();
  h_Distance_to_InnerTank_barrel.hist->Write();
  h_Distance_to_InnerTank_barrel_TRUE.hist->Write();
  h_Distance_to_InnerTank_downstreamCap.hist->Write();
  h_Distance_to_InnerTank_downstreamCap_TRUE.hist->Write();
  h_Distance_to_InnerTank_downstreamConcaveCap.hist->Write();
  h_Distance_to_InnerTank_downstreamConcaveCap_TRUE.hist->Write();
  h_CryoVertex_Z_RCut.hist->Write();
  h_CryoVertex_Z_RCut_TRUE.hist->Write();
  h_CryoVertex_Z_RCut_upstreamCap.hist->Write();
  h_CryoVertex_Z_RCut_upstreamCap_TRUE.hist->Write();
  h_CryoVertex_Z_RCut_barrel.hist->Write();
  h_CryoVertex_Z_RCut_barrel_TRUE.hist->Write();
  h_CryoVertex_Z_RCut_downstreamCap.hist->Write();
  h_CryoVertex_Z_RCut_downstreamCap_TRUE.hist->Write();
  h_CryoVertex_Z_RCut_downstreamConcaveCap.hist->Write();
  h_CryoVertex_Z_RCut_downstreamConcaveCap_TRUE.hist->Write();

  h_CryoVertex_X_upstreamCap.hist->Write();
  h_CryoVertex_Y_upstreamCap.hist->Write();
  h_CryoVertex_Z_upstreamCap.hist->Write();
  h_CryoVertex_R_upstreamCap.hist->Write();
  h_CryoVertex_X_upstreamCap_TRUE.hist->Write();
  h_CryoVertex_Y_upstreamCap_TRUE.hist->Write();
  h_CryoVertex_Z_upstreamCap_TRUE.hist->Write();
  h_CryoVertex_R_upstreamCap_TRUE.hist->Write();
  h_CryoVertex_X_barrel.hist->Write();
  h_CryoVertex_Y_barrel.hist->Write();
  h_CryoVertex_Z_barrel.hist->Write();
  h_CryoVertex_R_barrel.hist->Write();
  h_CryoVertex_X_barrel_TRUE.hist->Write();
  h_CryoVertex_Y_barrel_TRUE.hist->Write();
  h_CryoVertex_Z_barrel_TRUE.hist->Write();
  h_CryoVertex_R_barrel_TRUE.hist->Write();
  h_CryoVertex_X_downstreamCap.hist->Write();
  h_CryoVertex_Y_downstreamCap.hist->Write();
  h_CryoVertex_Z_downstreamCap.hist->Write();
  h_CryoVertex_R_downstreamCap.hist->Write();
  h_CryoVertex_X_downstreamCap_TRUE.hist->Write();
  h_CryoVertex_Y_downstreamCap_TRUE.hist->Write();
  h_CryoVertex_Z_downstreamCap_TRUE.hist->Write();
  h_CryoVertex_R_downstreamCap_TRUE.hist->Write();
  h_CryoVertex_X_downstreamConcaveCap.hist->Write();
  h_CryoVertex_Y_downstreamConcaveCap.hist->Write();
  h_CryoVertex_Z_downstreamConcaveCap.hist->Write();
  h_CryoVertex_R_downstreamConcaveCap.hist->Write();
  h_CryoVertex_X_downstreamConcaveCap_TRUE.hist->Write();
  h_CryoVertex_Y_downstreamConcaveCap_TRUE.hist->Write();
  h_CryoVertex_Z_downstreamConcaveCap_TRUE.hist->Write();
  h_CryoVertex_R_downstreamConcaveCap_TRUE.hist->Write();

  h_Distance_to_upstreamCap.hist->Write();
  h_Distance_to_upstreamCap_TRUE.hist->Write();
  h_Distance_to_downstreamCap.hist->Write();
  h_Distance_to_downstreamCap_TRUE.hist->Write();
  h_Distance_to_upstreamCap_upstreamCap.hist->Write();
  h_Distance_to_upstreamCap_upstreamCap_TRUE.hist->Write();
  h_Distance_to_downstreamCap_upstreamCap.hist->Write();
  h_Distance_to_downstreamCap_upstreamCap_TRUE.hist->Write();
  h_Distance_to_upstreamCap_barrel.hist->Write();
  h_Distance_to_upstreamCap_barrel_TRUE.hist->Write();
  h_Distance_to_downstreamCap_barrel.hist->Write();
  h_Distance_to_downstreamCap_barrel_TRUE.hist->Write();
  h_Distance_to_upstreamCap_downstreamCap.hist->Write();
  h_Distance_to_upstreamCap_downstreamCap_TRUE.hist->Write();
  h_Distance_to_downstreamCap_downstreamCap.hist->Write();
  h_Distance_to_downstreamCap_downstreamCap_TRUE.hist->Write();
  h_Distance_to_upstreamCap_downstreamConcaveCap.hist->Write();
  h_Distance_to_upstreamCap_downstreamConcaveCap_TRUE.hist->Write();
  h_Distance_to_downstreamCap_downstreamConcaveCap.hist->Write();
  h_Distance_to_downstreamCap_downstreamConcaveCap_TRUE.hist->Write();
  h_Distance_to_upstreamCap_RCut.hist->Write();
  h_Distance_to_upstreamCap_RCut_TRUE.hist->Write();
  h_Distance_to_downstreamCap_RCut.hist->Write();
  h_Distance_to_downstreamCap_RCut_TRUE.hist->Write();
  h_Distance_to_upstreamCap_RCut_upstreamCap.hist->Write();
  h_Distance_to_upstreamCap_RCut_upstreamCap_TRUE.hist->Write();
  h_Distance_to_downstreamCap_RCut_upstreamCap.hist->Write();
  h_Distance_to_downstreamCap_RCut_upstreamCap_TRUE.hist->Write();
  h_Distance_to_upstreamCap_RCut_barrel.hist->Write();
  h_Distance_to_upstreamCap_RCut_barrel_TRUE.hist->Write();
  h_Distance_to_downstreamCap_RCut_barrel.hist->Write();
  h_Distance_to_downstreamCap_RCut_barrel_TRUE.hist->Write();
  h_Distance_to_upstreamCap_RCut_downstreamCap.hist->Write();
  h_Distance_to_upstreamCap_RCut_downstreamCap_TRUE.hist->Write();
  h_Distance_to_downstreamCap_RCut_downstreamCap.hist->Write();
  h_Distance_to_downstreamCap_RCut_downstreamCap_TRUE.hist->Write();
  h_Distance_to_upstreamCap_RCut_downstreamConcaveCap.hist->Write();
  h_Distance_to_upstreamCap_RCut_downstreamConcaveCap_TRUE.hist->Write();
  h_Distance_to_downstreamCap_RCut_downstreamConcaveCap.hist->Write();
  h_Distance_to_downstreamCap_RCut_downstreamConcaveCap_TRUE.hist->Write();




  outFile->Close();


  char playlistname_char[playlist.length()+1];
  strcpy(playlistname_char,playlist.c_str());
  char arachneName[1024];

TCanvas *can = new TCanvas("", "");
MnvPlotter *mnv_plotter = new MnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);



char pdf_name[1024];
char pdf_start[1024];
char pdf_mid[1024];
char pdf_end[1024];

    sprintf(pdf_name, "Fidical_volumne_cuts_check_%s",c);

    sprintf(pdf_start,"%s.pdf(",pdf_name);
    //sprintf(pdf_mid,  "%s.pdf",pdf_name);
    sprintf(pdf_end,  "%s.pdf)",pdf_name);

    can -> Print(pdf_start);




    can -> Print(pdf_end);

    std::cout << "END OF Plotting" << std::endl;

    //std::cout << " THe Greatest  Chi sqrt value for Reco Cuts = "<< greatest_Chisqrt<< std::endl;
   //MakeLatex_Tables_withTrue_Event_info(N_A_secTrkParticle," ",  "N_A_FS_RECO", c, .5, "N_A in FS");
   //std::cout << " this many Other long tracks  = "<< otherlongtrack<< std::endl;


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

std::vector<ECuts> GetVectorRECOCuts_ALL() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ECuts> ret_vec;
  ret_vec.push_back(kNoCuts  );
  ret_vec.push_back(kGoodEnergy );
  ret_vec.push_back(kThetaMu );
  ret_vec.push_back(kMuonAngle );
  ret_vec.push_back(kNTracks);
  ret_vec.push_back(kUsableMuon);
  ret_vec.push_back(kMu_is_Plausible);
  //ret_vec.push_back(kNonMu_is_Plausible);
  ret_vec.push_back(kVeto );
  ret_vec.push_back(kSix );
  ret_vec.push_back(kMatchVetoDeadPaddle);

  ret_vec.push_back(kMinosCoil );
  ret_vec.push_back(kMinosMatch);
  ret_vec.push_back(kMinosCurvature);
  ret_vec.push_back(kMinosCharge );

  ret_vec.push_back(kVertexConverge);
  //ret_vec.push_back(kFiducialVolume_new );
  ret_vec.push_back(kTrackForwardGoing );
  ret_vec.push_back(ksecTrkwrtblessthanMaxAngle);
  ret_vec.push_back(kVertex_ConvergedfromAllTracks);
  ret_vec.push_back(kMaxChiSqrt_byTrackType);
  ret_vec.push_back(kAllCuts );

  return ret_vec;
//#endif
}



std::vector<ECuts> GetVectorRECOCutsFidicual_Eff() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ECuts> ret_vec;
  ret_vec.push_back(kNoCuts );
  ret_vec.push_back(kGoodEnergy );
  ret_vec.push_back(kUsableMuon);
  ret_vec.push_back(kMinosCoil );
  ret_vec.push_back(kMinosMatch);
  ret_vec.push_back(kMinosCurvature);
  ret_vec.push_back(kMinosCharge );

  ret_vec.push_back(kThetaMu );
  ret_vec.push_back(kMuonAngle );
  ret_vec.push_back(kMu_is_Plausible);

  ret_vec.push_back(kNTracks);
  ret_vec.push_back(kVertexConverge);
  ret_vec.push_back(kVertex_ConvergedfromAllTracks);
  ret_vec.push_back(kMaxChiSqrt_byTrackType);


  ret_vec.push_back(kVeto );
  ret_vec.push_back(kSix );
  ret_vec.push_back(kMatchVetoDeadPaddle);

  ret_vec.push_back(kTrackForwardGoing);
  ret_vec.push_back(ksecTrkwrtblessthanMaxAngle);

  ret_vec.push_back(kAllCuts );
  return ret_vec;
//#endif
}



std::vector<ECutsTRUTH> GetTRUTH_FidiucalMuCutsVector() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ECutsTRUTH> True_vec;
  True_vec.push_back(kTRUTHNoCuts   );
  True_vec.push_back(kTRUTHMuonEnergy );
  True_vec.push_back(kTRUTHMuonAngle );
  True_vec.push_back(kTRUTHneutrino);
  True_vec.push_back(kTRUTHCCInteraction );
  True_vec.push_back(kTRUTHtarget);
  True_vec.push_back(kTRUTH_greaterthanoneFS);
  //True_vec.push_back(kTRUTH_NoNeutral_FS_2ndTrk_RECOBRANCH);
  True_vec.push_back(kTRUTH_NoNeutral_FS_2ndTrk_withProtonanPionThresholds_RECOBRANCH);
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);
  True_vec.push_back(kAllTRUTHCuts);
  return True_vec;
//#endif
}

std::vector<ECutsTRUTH> GetTRUTHCutsVector_ALL() {
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
  //True_vec.push_back(kTRUTH_NoNeutral_FS_2ndTrk_RECOBRANCH);
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);
  True_vec.push_back(kTRUTH_NoNeutral_FS_2ndTrk_withProtonanPionThresholds_RECOBRANCH);
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);
  True_vec.push_back(kAllTRUTHCuts);


  //int n = sizeof(kCutsArray) / sizeof(kCutsArray[0]);
  //static std::vector<ECuts> ret_vec(kCutsArray, kCutsArray + n);
  return True_vec;
//#endif
}

//////////////////////////////////////////////////////////////////////////
//GET MUON Varibles
//////////////////////////////////////////////////////////////////////////


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
