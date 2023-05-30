
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

const std::vector<PlotUtils::NamedCategory<CryoTank_REGIONS>>
VertexRegions_Category = {
  PlotUtils::NamedCategory<CryoTank_REGIONS>({kXCenter},     "Center"),
  PlotUtils::NamedCategory<CryoTank_REGIONS>({kXLeftShelf},  "LeftShelf"),
  PlotUtils::NamedCategory<CryoTank_REGIONS>({kXRightShelf}, "RightShelf"),
  PlotUtils::NamedCategory<CryoTank_REGIONS>({kXoutsideEdges}, "OutsideEdges")
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
const std::vector<ECuts> kCutsVector_FiduicalEff = GetVectorRECOCuts_ALL();//GetVectorRECOCutsFidicual_Eff();
//const std::vector<ECutsTRUTH> kTRUTHCutsVector_Fiduical = GetTRUTH_FidiucalMuCutsVector();

const std::vector<Weights> kWeights_v1tune= GetWeightVector();
const std::vector<Weights> kWeights_v2tune= GetWeightVector_v2();
const std::vector<Weights> kWeights_forMK = GetWeightVector_mk();



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

PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE("h_MuonE", "Muon_{E}", Ebin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPZ("h_MuonPZ", "Muon_{PZ}",  Pzbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPT("h_MuonPT", "Muon_{PT}",  PTbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonTheta("h_MuonTheta", "#theta_{#mu} NEW Method",  MuonThetabin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X("h_CryoVertex_X", "Vertex_X",  Vertex_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y("h_CryoVertex_Y", "Vertex_Y",  Vertex_Ybin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z("h_CryoVertex_Z", "Vertex_Z",  Vertex_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R("h_CryoVertex_R", "h_CryoVertex_R",  Vertex_Rbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_InnerTank("h_Distance_to_InnerTank", "h_Distance_to_InnerTank",  Distance_to_innerTank, error_bands);





///////////////////////////////////////////////////////////////////////////////
///Full Cap Region Material
///////////////////////////////////////////////////////////////////////////////

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonE_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonE_Material", Ebin_vector ,"MuonE_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonPZ_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonPZ_Material", Pzbin_vector ,"h_MuonPZ_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonPT_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonPT_Material", PTbin_vector ,"h_MuonPT_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonTheta_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonTheta_Material", MuonThetabin_vector ,"h_MuonTheta_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_X_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_X_Material", Vertex_Xbin_vector ,"h_CryoVertex_X_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Y_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Y_Material", Vertex_Ybin_vector ,"h_CryoVertex_Y_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Z_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Z_Material", Vertex_Zbin_vector ,"h_CryoVertex_Z_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_R_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_R_Material", Vertex_Rbin_vector ,"h_CryoVertex_R_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Distance_to_InnerTank_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Distance_to_InnerTank_Material",  Distance_to_innerTank  ,"h_Distance_to_InnerTank_Material");
////////////////////////////////////////////////////////////////////////////////
/// Regions
////////////////////////////////////////////////////////////////////////////////

PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS> h_MuonE_CryoRegions =
PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS>(VertexRegions_Category, "h_MuonE_CryoRegions", Ebin_vector ,"MuonE_CryoRegions; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS> h_MuonPZ_CryoRegions =
PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS>(VertexRegions_Category, "h_MuonPZ_CryoRegions", Pzbin_vector ,"h_MuonPZ_CryoRegions; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS> h_MuonPT_CryoRegions =
PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS>(VertexRegions_Category, "h_MuonPT_CryoRegions", PTbin_vector ,"h_MuonPT_CryoRegions; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS> h_MuonTheta_CryoRegions =
PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS>(VertexRegions_Category, "h_MuonTheta_CryoRegions", MuonThetabin_vector ,"h_MuonTheta_CryoRegions; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS> h_CryoVertex_X_CryoRegions =
PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS>(VertexRegions_Category, "h_CryoVertex_X_CryoRegions", Vertex_Xbin_vector ,"h_CryoVertex_X_CryoRegions; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS> h_CryoVertex_Y_CryoRegions =
PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS>(VertexRegions_Category, "h_CryoVertex_Y_CryoRegions", Vertex_Ybin_vector ,"h_CryoVertex_Y_CryoRegions; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS> h_CryoVertex_Z_CryoRegions =
PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS>(VertexRegions_Category, "h_CryoVertex_Z_CryoRegions", Vertex_Zbin_vector ,"h_CryoVertex_Z_CryoRegions; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS> h_CryoVertex_R_CryoRegions =
PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS>(VertexRegions_Category, "h_CryoVertex_R_CryoRegions", Vertex_Rbin_vector ,"h_CryoVertex_R_CryoRegions; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS> h_Distance_to_InnerTank_CryoRegions =
PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS>(VertexRegions_Category, "h_Distance_to_InnerTank_CryoRegions",  Distance_to_innerTank  ,"h_Distance_to_InnerTank_CryoRegions");
///////////////////////////////////////////////////////////////////////////////
///UpStream Cap Region
///////////////////////////////////////////////////////////////////////////////
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE_XCenter("h_MuonE_XCenter", "Muon_{E}", Ebin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPZ_XCenter("h_MuonPZ_XCenter", "Muon_{PZ}",  Pzbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPT_XCenter("h_MuonPT_XCenter", "Muon_{PT}",  PTbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonTheta_XCenter("h_MuonTheta_XCenter", "#theta_{#mu} NEW Method",  MuonThetabin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_XCenter("h_CryoVertex_X_XCenter", "Vertex X",  Vertex_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_XCenter("h_CryoVertex_Y_XCenter", "Vertex Y",  Vertex_Ybin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_XCenter("h_CryoVertex_Z_XCenter", "Vertex Z",  Vertex_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_XCenter("h_CryoVertex_R_XCenter", "Vertex R",  Vertex_Rbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_InnerTank_XCenter("h_Distance_to_InnerTank_XCenter", "h_Distance_to_InnerTank",  Distance_to_innerTank, error_bands);


PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonE_XCenter_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonE_XCenter_Material", Ebin_vector ,"MuonE_XCenter_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonPZ_XCenter_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonPZ_XCenter_Material", Pzbin_vector ,"h_MuonPZ_XCenter_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonPT_XCenter_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonPT_XCenter_Material", PTbin_vector ,"h_MuonPT_XCenter_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonTheta_XCenter_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonTheta_XCenter_Material", MuonThetabin_vector ,"h_MuonTheta_XCenter_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_X_XCenter_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_X_XCenter_Material", Vertex_Xbin_vector ,"h_CryoVertex_X_XCenter_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Y_XCenter_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Y_XCenter_Material", Vertex_Ybin_vector ,"h_CryoVertex_Y_XCenter_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Z_XCenter_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Z_XCenter_Material", Vertex_Zbin_vector ,"h_CryoVertex_Z_XCenter_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_R_XCenter_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_R_XCenter_Material", Vertex_Rbin_vector ,"h_CryoVertex_R_XCenter_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Distance_to_InnerTank_XCenter_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Distance_to_InnerTank_XCenter_Material",  Distance_to_innerTank  ,"h_Distance_to_InnerTank_XCenter_Material");


///////////////////////////////////////////////////////////////////////////////
///XRightShelf Region
///////////////////////////////////////////////////////////////////////////////

PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE_XRightShelf("h_MuonE_XRightShelf", "Muon_{E}", Ebin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPZ_XRightShelf("h_MuonPZ_XRightShelf", "Muon_{PZ}",  Pzbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPT_XRightShelf("h_MuonPT_XRightShelf", "Muon_{PT}",  PTbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonTheta_XRightShelf("h_MuonTheta_XRightShelf", "#theta_{#mu} NEW Method",  MuonThetabin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_XRightShelf("h_CryoVertex_X_XRightShelf", "Vertex X",  Vertex_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_XRightShelf("h_CryoVertex_Y_XRightShelf", "Vertex Y",  Vertex_Ybin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_XRightShelf("h_CryoVertex_Z_XRightShelf", "Vertex Z",  Vertex_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_XRightShelf("h_CryoVertex_R_XRightShelf", "Vertex R",  Vertex_Rbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_InnerTank_XRightShelf("h_Distance_to_InnerTank_XRightShelf", "h_Distance_to_InnerTank",  Distance_to_innerTank, error_bands);


PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonE_XRightShelf_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonE_XRightShelf_Material", Ebin_vector ,"MuonE_XRightShelf_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonPZ_XRightShelf_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonPZ_XRightShelf_Material", Pzbin_vector ,"h_MuonPZ_XRightShelf_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonPT_XRightShelf_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonPT_XRightShelf_Material", PTbin_vector ,"h_MuonPT_XRightShelf_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonTheta_XRightShelf_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonTheta_XRightShelf_Material", MuonThetabin_vector ,"h_MuonTheta_XRightShelf_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_X_XRightShelf_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_X_XRightShelf_Material", Vertex_Xbin_vector ,"h_CryoVertex_X_XRightShelf_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Y_XRightShelf_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Y_XRightShelf_Material", Vertex_Ybin_vector ,"h_CryoVertex_Y_XRightShelf_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Z_XRightShelf_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Z_XRightShelf_Material", Vertex_Zbin_vector ,"h_CryoVertex_Z_XRightShelf_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_R_XRightShelf_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_R_XRightShelf_Material", Vertex_Rbin_vector ,"h_CryoVertex_R_XRightShelf_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Distance_to_InnerTank_XRightShelf_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Distance_to_InnerTank_XRightShelf_Material",  Distance_to_innerTank  ,"h_Distance_to_InnerTank_XRightShelf_Material");

///////////////////////////////////////////////////////////////////////////////
///DownStream Cap Region
///////////////////////////////////////////////////////////////////////////////

PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE_XLeftShelf("h_MuonE_XLeftShelf", "Muon_{E}", Ebin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPZ_XLeftShelf("h_MuonPZ_XLeftShelf", "Muon_{PZ}",  Pzbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPT_XLeftShelf("h_MuonPT_XLeftShelf", "Muon_{PT}",  PTbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonTheta_XLeftShelf("h_MuonTheta_XLeftShelf", "#theta_{#mu} NEW Method",  MuonThetabin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_XLeftShelf("h_CryoVertex_X_XLeftShelf", "Vertex X",  Vertex_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_XLeftShelf("h_CryoVertex_Y_XLeftShelf", "Vertex Y",  Vertex_Ybin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_XLeftShelf("h_CryoVertex_Z_XLeftShelf", "Vertex Z",  Vertex_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_XLeftShelf("h_CryoVertex_R_XLeftShelf", "Vertex R",  Vertex_Rbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_InnerTank_XLeftShelf("h_Distance_to_InnerTank_XLeftShelf", "h_Distance_to_InnerTank",  Distance_to_innerTank, error_bands);


PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonE_XLeftShelf_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonE_XLeftShelf_Material", Ebin_vector ,"MuonE_XLeftShelf_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonPZ_XLeftShelf_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonPZ_XLeftShelf_Material", Pzbin_vector ,"h_MuonPZ_XLeftShelf_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonPT_XLeftShelf_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonPT_XLeftShelf_Material", PTbin_vector ,"h_MuonPT_XLeftShelf_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonTheta_XLeftShelf_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonTheta_XLeftShelf_Material", MuonThetabin_vector ,"h_MuonTheta_XLeftShelf_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_X_XLeftShelf_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_X_XLeftShelf_Material", Vertex_Xbin_vector ,"h_CryoVertex_X_XLeftShelf_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Y_XLeftShelf_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Y_XLeftShelf_Material", Vertex_Ybin_vector ,"h_CryoVertex_Y_XLeftShelf_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Z_XLeftShelf_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Z_XLeftShelf_Material", Vertex_Zbin_vector ,"h_CryoVertex_Z_XLeftShelf_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_R_XLeftShelf_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_R_XLeftShelf_Material", Vertex_Rbin_vector ,"h_CryoVertex_R_XLeftShelf_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Distance_to_InnerTank_XLeftShelf_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Distance_to_InnerTank_XLeftShelf_Material",  Distance_to_innerTank  ,"h_Distance_to_InnerTank_XLeftShelf_Material");

////////////////////////////////////////////////////////////////////////////////
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE_XoutsideEdges("h_MuonE_XoutsideEdges", "Muon_{E}", Ebin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPZ_XoutsideEdges("h_MuonPZ_XoutsideEdges", "Muon_{PZ}",  Pzbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPT_XoutsideEdges("h_MuonPT_XoutsideEdges", "Muon_{PT}",  PTbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonTheta_XoutsideEdges("h_MuonTheta_XoutsideEdges", "#theta_{#mu} ",  MuonThetabin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_XoutsideEdges("h_CryoVertex_X_XoutsideEdges", "Vertex X",  Vertex_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_XoutsideEdges("h_CryoVertex_Y_XoutsideEdges", "Vertex Y",  Vertex_Ybin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_XoutsideEdges("h_CryoVertex_Z_XoutsideEdges", "Vertex Z",  Vertex_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_XoutsideEdges("h_CryoVertex_R_XoutsideEdges", "Vertex R",  Vertex_Rbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_InnerTank_XoutsideEdges("h_Distance_to_InnerTank_XoutsideEdges", "h_Distance_to_InnerTank",  Distance_to_innerTank, error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonE_XoutsideEdges_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonE_XoutsideEdges_Material", Ebin_vector ,"MuonE_XoutsideEdges_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonPZ_XoutsideEdges_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonPZ_XoutsideEdges_Material", Pzbin_vector ,"h_MuonPZ_XoutsideEdges_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonPT_XoutsideEdges_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonPT_XoutsideEdges_Material", PTbin_vector ,"h_MuonPT_XoutsideEdges_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonTheta_XoutsideEdges_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonTheta_XoutsideEdges_Material", MuonThetabin_vector ,"h_MuonTheta_XoutsideEdges_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_X_XoutsideEdges_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_X_XoutsideEdges_Material", Vertex_Xbin_vector ,"h_CryoVertex_X_XoutsideEdges_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Y_XoutsideEdges_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Y_XoutsideEdges_Material", Vertex_Ybin_vector ,"h_CryoVertex_Y_XoutsideEdges_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Z_XoutsideEdges_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Z_XoutsideEdges_Material", Vertex_Zbin_vector ,"h_CryoVertex_Z_XoutsideEdges_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_R_XoutsideEdges_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_R_XoutsideEdges_Material", Vertex_Rbin_vector ,"h_CryoVertex_R_XoutsideEdges_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Distance_to_InnerTank_XoutsideEdges_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Distance_to_InnerTank_XoutsideEdges_Material",  Distance_to_innerTank  ,"h_Distance_to_InnerTank_XoutsideEdges_Material");



  char tempName[1024];





////////////////
//Vertex Hist///
////////////////

  //=========================================
  // Entry Loop For MC
  //=========================================

  RECO_Cut_Map CountMap_Fiduical;
  FillingRecoCountingMap(kCutsVector_FiduicalEff, CountMap_Fiduical);
  RECO_Cut_Map CountMap_ALL;
  FillingRecoCountingMap(kCutsVector_ALL, CountMap_ALL);

  TRUE_Cut_Map Truth_Cut_Map_Fiduical;
  TRUE_Cut_Map Truth_Cut_Map_ALL;

  //FillingTruthCountingMap(kTRUTHCutsVector_Fiduical,     Truth_Cut_Map_Fiduical);

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


  std::cout << "Memory/time used so Far: " << procInfo.fMemResident/1000<< " MB" <<" time = "<<  procInfo.fCpuSys <<  " Sec"<<"\n";

  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"MC LOOP  "<<std::endl;
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
          double x= universe->GetVertex_x();
          double y= universe->GetVertex_y();
          double z= universe->GetVertex_z();
          double r = universe->GetVertex_r();
          double Theta = universe->GetThetamu();
          double Pmu = universe ->GetPmu()/1000;

          double phi = universe->GetPhimu();

          double px = Pmu * std::sin(Theta) * std::cos(phi);
          double py = Pmu * std::sin(Theta) * std::sin(phi);

          double PT = sqrt(px*px + py*py);
          double PZ = Pmu*std::cos(Theta);


          CryoTank_REGIONS CryoTankRegion_type = FourVertexXRegion_of_CryoTank(x);
          double Reco_distance = RECO_Distance_to_innerTank(*universe);

          h_MuonE.univHist(universe)->Fill(universe->GetEmu()*.001,wgt_minerva_v1);
          h_MuonPZ.univHist(universe)->Fill(PZ,wgt_minerva_v1);
          h_MuonPT.univHist(universe)->Fill(PT,wgt_minerva_v1);
          h_MuonTheta.univHist(universe)->Fill(Theta*TMath::RadToDeg(),wgt_minerva_v1);
          h_CryoVertex_X.univHist(universe)->Fill(x ,wgt_minerva_v1);
          h_CryoVertex_Y.univHist(universe)->Fill(y ,wgt_minerva_v1);
          h_CryoVertex_Z.univHist(universe)->Fill(z ,wgt_minerva_v1);
          h_CryoVertex_R.univHist(universe)->Fill(r,wgt_minerva_v1);
          h_Distance_to_InnerTank.univHist(universe)->Fill(Reco_distance,wgt_minerva_v1);

          if(CryoTankRegion_type==kXCenter)
          {
            h_MuonE_XCenter.univHist(universe)->Fill(universe->GetEmu()*.001,wgt_minerva_v1);
            h_MuonPZ_XCenter.univHist(universe)->Fill(PZ,wgt_minerva_v1);
            h_MuonPT_XCenter.univHist(universe)->Fill(PT,wgt_minerva_v1);
            h_MuonTheta_XCenter.univHist(universe)->Fill(Theta*TMath::RadToDeg(),wgt_minerva_v1);
            h_CryoVertex_X_XCenter.univHist(universe)->Fill(x ,wgt_minerva_v1);
            h_CryoVertex_Y_XCenter.univHist(universe)->Fill(y ,wgt_minerva_v1);
            h_CryoVertex_Z_XCenter.univHist(universe)->Fill(z ,wgt_minerva_v1);
            h_CryoVertex_R_XCenter.univHist(universe)->Fill(r,wgt_minerva_v1);
            h_Distance_to_InnerTank_XCenter.univHist(universe)->Fill(Reco_distance,wgt_minerva_v1);
          }
          else if(CryoTankRegion_type==kXRightShelf)
          {
            h_MuonE_XRightShelf.univHist(universe)->Fill(universe->GetEmu()*.001,wgt_minerva_v1);
            h_MuonPZ_XRightShelf.univHist(universe)->Fill(PZ,wgt_minerva_v1);
            h_MuonPT_XRightShelf.univHist(universe)->Fill(PT,wgt_minerva_v1);
            h_MuonTheta_XRightShelf.univHist(universe)->Fill(Theta*TMath::RadToDeg(),wgt_minerva_v1);
            h_CryoVertex_X_XRightShelf.univHist(universe)->Fill(x ,wgt_minerva_v1);
            h_CryoVertex_Y_XRightShelf.univHist(universe)->Fill(y ,wgt_minerva_v1);
            h_CryoVertex_Z_XRightShelf.univHist(universe)->Fill(z ,wgt_minerva_v1);
            h_CryoVertex_R_XRightShelf.univHist(universe)->Fill(r,wgt_minerva_v1);
            h_Distance_to_InnerTank_XRightShelf.univHist(universe)->Fill(Reco_distance,wgt_minerva_v1);

          }
          else if(CryoTankRegion_type==kXLeftShelf)
          {
            h_MuonE_XLeftShelf.univHist(universe)->Fill(universe->GetEmu()*.001,wgt_minerva_v1);
            h_MuonPZ_XLeftShelf.univHist(universe)->Fill(PZ,wgt_minerva_v1);
            h_MuonPT_XLeftShelf.univHist(universe)->Fill(PT,wgt_minerva_v1);
            h_MuonTheta_XLeftShelf.univHist(universe)->Fill(Theta*TMath::RadToDeg(),wgt_minerva_v1);
            h_CryoVertex_X_XLeftShelf.univHist(universe)->Fill(x ,wgt_minerva_v1);
            h_CryoVertex_Y_XLeftShelf.univHist(universe)->Fill(y ,wgt_minerva_v1);
            h_CryoVertex_Z_XLeftShelf.univHist(universe)->Fill(z ,wgt_minerva_v1);
            h_CryoVertex_R_XLeftShelf.univHist(universe)->Fill(r,wgt_minerva_v1);
            h_Distance_to_InnerTank_XLeftShelf.univHist(universe)->Fill(Reco_distance,wgt_minerva_v1);
          }

          else if(CryoTankRegion_type==kXoutsideEdges)
          {
            h_MuonE_XoutsideEdges.univHist(universe)->Fill(universe->GetEmu()*.001,wgt_minerva_v1);
            h_MuonPZ_XoutsideEdges.univHist(universe)->Fill(PZ,wgt_minerva_v1);
            h_MuonPT_XoutsideEdges.univHist(universe)->Fill(PT,wgt_minerva_v1);
            h_MuonTheta_XoutsideEdges.univHist(universe)->Fill(Theta*TMath::RadToDeg(),wgt_minerva_v1);
            h_CryoVertex_X_XoutsideEdges.univHist(universe)->Fill(x ,wgt_minerva_v1);
            h_CryoVertex_Y_XoutsideEdges.univHist(universe)->Fill(y ,wgt_minerva_v1);
            h_CryoVertex_Z_XoutsideEdges.univHist(universe)->Fill(z ,wgt_minerva_v1);
            h_CryoVertex_R_XoutsideEdges.univHist(universe)->Fill(r,wgt_minerva_v1);
            h_Distance_to_InnerTank_XoutsideEdges.univHist(universe)->Fill(Reco_distance,wgt_minerva_v1);
          }



          else{std::cout<<"ABSURDITY !! Event Failed to be in a  CryoRegion: Something Wrong"<<std::endl; assert(false);}



          if(isCV(*universe)){

            h_MuonE_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetEmu()*.001, wgt_minerva_v1);
            h_MuonPZ_Material.GetComponentHist(Material_type_Event)->Fill(PZ, wgt_minerva_v1);
            h_MuonPT_Material.GetComponentHist(Material_type_Event)->Fill(PT, wgt_minerva_v1);
            h_MuonTheta_Material.GetComponentHist(Material_type_Event)->Fill(Theta*toDegs, wgt_minerva_v1);
            h_CryoVertex_X_Material.GetComponentHist(Material_type_Event)->Fill(x, wgt_minerva_v1);
            h_CryoVertex_Y_Material.GetComponentHist(Material_type_Event)->Fill(y, wgt_minerva_v1);
            h_CryoVertex_Z_Material.GetComponentHist(Material_type_Event)->Fill(z, wgt_minerva_v1);
            h_CryoVertex_R_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetVertex_r(), wgt_minerva_v1);
            h_Distance_to_InnerTank_Material.GetComponentHist(Material_type_Event)->Fill(Reco_distance, wgt_minerva_v1);

            h_MuonE_CryoRegions.GetComponentHist(CryoTankRegion_type)->Fill(universe->GetEmu()*.001, wgt_minerva_v1);
            h_MuonPZ_CryoRegions.GetComponentHist(CryoTankRegion_type)->Fill(PZ, wgt_minerva_v1);
            h_MuonPT_CryoRegions.GetComponentHist(CryoTankRegion_type)->Fill(PT, wgt_minerva_v1);
            h_MuonTheta_CryoRegions.GetComponentHist(CryoTankRegion_type)->Fill(Theta*toDegs, wgt_minerva_v1);
            h_CryoVertex_X_CryoRegions.GetComponentHist(CryoTankRegion_type)->Fill(x, wgt_minerva_v1);
            h_CryoVertex_Y_CryoRegions.GetComponentHist(CryoTankRegion_type)->Fill(y, wgt_minerva_v1);
            h_CryoVertex_Z_CryoRegions.GetComponentHist(CryoTankRegion_type)->Fill(z, wgt_minerva_v1);
            h_CryoVertex_R_CryoRegions.GetComponentHist(CryoTankRegion_type)->Fill(universe->GetVertex_r(), wgt_minerva_v1);
            h_Distance_to_InnerTank_CryoRegions.GetComponentHist(CryoTankRegion_type)->Fill(Reco_distance, wgt_minerva_v1);




            if(CryoTankRegion_type==kXCenter)
            {
              h_MuonE_XCenter_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetEmu()*.001, wgt_minerva_v1);
              h_MuonPZ_XCenter_Material.GetComponentHist(Material_type_Event)->Fill(PZ, wgt_minerva_v1);
              h_MuonPT_XCenter_Material.GetComponentHist(Material_type_Event)->Fill(PT, wgt_minerva_v1);
              h_MuonTheta_XCenter_Material.GetComponentHist(Material_type_Event)->Fill(Theta*toDegs, wgt_minerva_v1);
              h_CryoVertex_X_XCenter_Material.GetComponentHist(Material_type_Event)->Fill(x, wgt_minerva_v1);
              h_CryoVertex_Y_XCenter_Material.GetComponentHist(Material_type_Event)->Fill(y, wgt_minerva_v1);
              h_CryoVertex_Z_XCenter_Material.GetComponentHist(Material_type_Event)->Fill(z, wgt_minerva_v1);
              h_CryoVertex_R_XCenter_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetVertex_r(), wgt_minerva_v1);
              h_Distance_to_InnerTank_XCenter_Material.GetComponentHist(Material_type_Event)->Fill(Reco_distance, wgt_minerva_v1);
            }
            else if(CryoTankRegion_type==kXRightShelf)
            {
              h_MuonE_XRightShelf_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetEmu()*.001, wgt_minerva_v1);
              h_MuonPZ_XRightShelf_Material.GetComponentHist(Material_type_Event)->Fill(PZ, wgt_minerva_v1);
              h_MuonPT_XRightShelf_Material.GetComponentHist(Material_type_Event)->Fill(PT, wgt_minerva_v1);
              h_MuonTheta_XRightShelf_Material.GetComponentHist(Material_type_Event)->Fill(Theta*toDegs, wgt_minerva_v1);
              h_CryoVertex_X_XRightShelf_Material.GetComponentHist(Material_type_Event)->Fill(x, wgt_minerva_v1);
              h_CryoVertex_Y_XRightShelf_Material.GetComponentHist(Material_type_Event)->Fill(y, wgt_minerva_v1);
              h_CryoVertex_Z_XRightShelf_Material.GetComponentHist(Material_type_Event)->Fill(z, wgt_minerva_v1);
              h_CryoVertex_R_XRightShelf_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetVertex_r(), wgt_minerva_v1);
              h_Distance_to_InnerTank_XRightShelf_Material.GetComponentHist(Material_type_Event)->Fill(Reco_distance, wgt_minerva_v1);

            }
            else if(CryoTankRegion_type==kXLeftShelf)
            {
              h_MuonE_XLeftShelf_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetEmu()*.001, wgt_minerva_v1);
              h_MuonPZ_XLeftShelf_Material.GetComponentHist(Material_type_Event)->Fill(PZ, wgt_minerva_v1);
              h_MuonPT_XLeftShelf_Material.GetComponentHist(Material_type_Event)->Fill(PT, wgt_minerva_v1);
              h_MuonTheta_XLeftShelf_Material.GetComponentHist(Material_type_Event)->Fill(Theta*toDegs, wgt_minerva_v1);
              h_CryoVertex_X_XLeftShelf_Material.GetComponentHist(Material_type_Event)->Fill(x, wgt_minerva_v1);
              h_CryoVertex_Y_XLeftShelf_Material.GetComponentHist(Material_type_Event)->Fill(y, wgt_minerva_v1);
              h_CryoVertex_Z_XLeftShelf_Material.GetComponentHist(Material_type_Event)->Fill(z, wgt_minerva_v1);
              h_CryoVertex_R_XLeftShelf_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetVertex_r(), wgt_minerva_v1);
              h_Distance_to_InnerTank_XLeftShelf_Material.GetComponentHist(Material_type_Event)->Fill(Reco_distance, wgt_minerva_v1);
            }
            else if(CryoTankRegion_type==kXoutsideEdges)
            {
              h_MuonE_XoutsideEdges_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetEmu()*.001, wgt_minerva_v1);
              h_MuonPZ_XoutsideEdges_Material.GetComponentHist(Material_type_Event)->Fill(PZ, wgt_minerva_v1);
              h_MuonPT_XoutsideEdges_Material.GetComponentHist(Material_type_Event)->Fill(PT, wgt_minerva_v1);
              h_MuonTheta_XoutsideEdges_Material.GetComponentHist(Material_type_Event)->Fill(Theta*toDegs, wgt_minerva_v1);
              h_CryoVertex_X_XoutsideEdges_Material.GetComponentHist(Material_type_Event)->Fill(x, wgt_minerva_v1);

              h_CryoVertex_Y_XoutsideEdges_Material.GetComponentHist(Material_type_Event)->Fill(y, wgt_minerva_v1);
              h_CryoVertex_Z_XoutsideEdges_Material.GetComponentHist(Material_type_Event)->Fill(z, wgt_minerva_v1);
              h_CryoVertex_R_XoutsideEdges_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetVertex_r(), wgt_minerva_v1);
              h_Distance_to_InnerTank_XoutsideEdges_Material.GetComponentHist(Material_type_Event)->Fill(Reco_distance, wgt_minerva_v1);

            }


            else{std::cout<<"ABSURDITY !! Event Failed to be in a  CryoRegion: Something Wrong"<<std::endl; assert(false);}




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

  h_MuonPZ.SyncCVHistos();
  h_MuonPT.SyncCVHistos();
  h_MuonE.SyncCVHistos();
  h_MuonTheta.SyncCVHistos();
  h_CryoVertex_X.SyncCVHistos();
  h_CryoVertex_Y.SyncCVHistos();
  h_CryoVertex_Z.SyncCVHistos();
  h_CryoVertex_R.SyncCVHistos();
  h_Distance_to_InnerTank.SyncCVHistos();

  h_MuonE_XCenter.SyncCVHistos();
  h_MuonPZ_XCenter.SyncCVHistos();
  h_MuonPT_XCenter.SyncCVHistos();
  h_MuonTheta_XCenter.SyncCVHistos();
  h_CryoVertex_X_XCenter.SyncCVHistos();
  h_CryoVertex_Y_XCenter.SyncCVHistos();
  h_CryoVertex_Z_XCenter.SyncCVHistos();
  h_CryoVertex_R_XCenter.SyncCVHistos();
  h_Distance_to_InnerTank_XCenter.SyncCVHistos();

  h_MuonE_XRightShelf.SyncCVHistos();
  h_MuonPT_XRightShelf.SyncCVHistos();
  h_MuonPZ_XRightShelf.SyncCVHistos();
  h_MuonTheta_XRightShelf.SyncCVHistos();
  h_CryoVertex_X_XRightShelf.SyncCVHistos();
  h_CryoVertex_Y_XRightShelf.SyncCVHistos();
  h_CryoVertex_Z_XRightShelf.SyncCVHistos();
  h_CryoVertex_R_XRightShelf.SyncCVHistos();
  h_Distance_to_InnerTank_XRightShelf.SyncCVHistos();

  h_MuonE_XLeftShelf.SyncCVHistos();
  h_MuonPZ_XLeftShelf.SyncCVHistos();
  h_MuonPT_XLeftShelf.SyncCVHistos();
  h_MuonTheta_XLeftShelf.SyncCVHistos();
  h_CryoVertex_X_XLeftShelf.SyncCVHistos();
  h_CryoVertex_Y_XLeftShelf.SyncCVHistos();
  h_CryoVertex_Z_XLeftShelf.SyncCVHistos();
  h_CryoVertex_R_XLeftShelf.SyncCVHistos();
  h_Distance_to_InnerTank_XLeftShelf.SyncCVHistos();

  h_MuonE_XoutsideEdges.SyncCVHistos();
  h_MuonPZ_XoutsideEdges.SyncCVHistos();
  h_MuonPT_XoutsideEdges.SyncCVHistos();
  h_MuonTheta_XoutsideEdges.SyncCVHistos();
  h_CryoVertex_X_XoutsideEdges.SyncCVHistos();
  h_CryoVertex_Y_XoutsideEdges.SyncCVHistos();
  h_CryoVertex_Z_XoutsideEdges.SyncCVHistos();
  h_CryoVertex_R_XoutsideEdges.SyncCVHistos();
  h_Distance_to_InnerTank_XoutsideEdges.SyncCVHistos();
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
  /*
  std::string reco_true = "TRUTHcuts_RECOcuts_" + playlist_name;
  std::string true_Cuts = "TRUTHcuts" + playlist_name;
  char reco_true_char[reco_true.length()+1];
  char true_Cuts_char[true_Cuts.length()+1];
  strcpy(reco_true_char, reco_true.c_str());
  strcpy(true_Cuts_char, true_Cuts.c_str());
*/

  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~ RECO Eff cuts ~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;

  if(Run_EventLoopOnGid==true){
    sprintf(outFileName, "%s_%s_%s_%s_fourXRegions_sideBand.root", "Histograms",c,d,ErrorStatus);
    std::cout << "Writing output file on Grid to: " <<outFileName << std::endl;

  }
  else{
    sprintf(outFileName, "%s/%s_%s_%s_%s_fourXRegions_sideBand.root", rootpathway, "Histograms",c,d,ErrorStatus);
    std::cout << "Writing output file to: " <<outFileName << std::endl;
  }


  //TFile *outFile(outFileName, "RECREATE");
  TFile *outFile = new TFile(outFileName,"RECREATE");
  TChain POT_branch("Meta");
  POT_branch.Add(RootName.c_str());
  //TTree *oldtree = (TTree*)file->Get("Meta");
  TTree *clone = POT_branch.CloneTree();
  clone->Write();

std::cout << "Writing output file for  Stacks" << std::endl;

  h_MuonE_Material.WriteToFile(*outFile);
  h_MuonPZ_Material.WriteToFile(*outFile);
  h_MuonPT_Material.WriteToFile(*outFile);
  h_MuonTheta_Material.WriteToFile(*outFile);
  h_CryoVertex_X_Material.WriteToFile(*outFile);
  h_CryoVertex_Y_Material.WriteToFile(*outFile);
  h_CryoVertex_Z_Material.WriteToFile(*outFile);
  h_CryoVertex_R_Material.WriteToFile(*outFile);
  h_Distance_to_InnerTank_Material.WriteToFile(*outFile);

  std::cout << "Combined Regions Material Done" << std::endl;

  h_MuonE_CryoRegions.WriteToFile(*outFile);
  h_MuonPZ_CryoRegions.WriteToFile(*outFile);
  h_MuonPT_CryoRegions.WriteToFile(*outFile);
  h_MuonTheta_CryoRegions.WriteToFile(*outFile);
  h_CryoVertex_X_CryoRegions.WriteToFile(*outFile);
  h_CryoVertex_Y_CryoRegions.WriteToFile(*outFile);
  h_CryoVertex_Z_CryoRegions.WriteToFile(*outFile);
  h_CryoVertex_R_CryoRegions.WriteToFile(*outFile);
  h_Distance_to_InnerTank_CryoRegions.WriteToFile(*outFile);

  std::cout << "Combined Regions Regions Done" << std::endl;

  h_MuonE_XCenter_Material.WriteToFile(*outFile);
  h_MuonPZ_XCenter_Material.WriteToFile(*outFile);
  h_MuonPT_XCenter_Material.WriteToFile(*outFile);
  h_MuonTheta_XCenter_Material.WriteToFile(*outFile);
  h_CryoVertex_X_XCenter_Material.WriteToFile(*outFile);
  h_CryoVertex_Y_XCenter_Material.WriteToFile(*outFile);
  h_CryoVertex_Z_XCenter_Material.WriteToFile(*outFile);
  h_CryoVertex_R_XCenter_Material.WriteToFile(*outFile);
  h_Distance_to_InnerTank_XCenter_Material.WriteToFile(*outFile);

  std::cout << "Upstream Material Stacks Done" << std::endl;

  h_MuonE_XRightShelf_Material.WriteToFile(*outFile);
  h_MuonPZ_XRightShelf_Material.WriteToFile(*outFile);
  h_MuonPT_XRightShelf_Material.WriteToFile(*outFile);
  h_MuonTheta_XRightShelf_Material.WriteToFile(*outFile);
  h_CryoVertex_X_XRightShelf_Material.WriteToFile(*outFile);
  h_CryoVertex_Y_XRightShelf_Material.WriteToFile(*outFile);
  h_CryoVertex_Z_XRightShelf_Material.WriteToFile(*outFile);
  h_CryoVertex_R_XRightShelf_Material.WriteToFile(*outFile);
  h_Distance_to_InnerTank_XRightShelf_Material.WriteToFile(*outFile);

  std::cout << "XRightShelf Material Stacks Done" << std::endl;

  h_MuonE_XLeftShelf_Material.WriteToFile(*outFile);
  h_MuonPZ_XLeftShelf_Material.WriteToFile(*outFile);
  h_MuonPT_XLeftShelf_Material.WriteToFile(*outFile);
  h_MuonTheta_XLeftShelf_Material.WriteToFile(*outFile);
  h_CryoVertex_X_XLeftShelf_Material.WriteToFile(*outFile);
  h_CryoVertex_Y_XLeftShelf_Material.WriteToFile(*outFile);
  h_CryoVertex_Z_XLeftShelf_Material.WriteToFile(*outFile);
  h_CryoVertex_R_XLeftShelf_Material.WriteToFile(*outFile);
  h_Distance_to_InnerTank_XLeftShelf_Material.WriteToFile(*outFile);
  std::cout << "Downstream Material Stacks Done" << std::endl;

  h_MuonE_XoutsideEdges_Material.WriteToFile(*outFile);
  h_MuonPZ_XoutsideEdges_Material.WriteToFile(*outFile);
  h_MuonPT_XoutsideEdges_Material.WriteToFile(*outFile);
  h_MuonTheta_XoutsideEdges_Material.WriteToFile(*outFile);
  h_CryoVertex_X_XoutsideEdges_Material.WriteToFile(*outFile);
  h_CryoVertex_Y_XoutsideEdges_Material.WriteToFile(*outFile);
  h_CryoVertex_Z_XoutsideEdges_Material.WriteToFile(*outFile);
  h_CryoVertex_R_XoutsideEdges_Material.WriteToFile(*outFile);
  h_Distance_to_InnerTank_XoutsideEdges_Material.WriteToFile(*outFile);

  std::cout << "Writing non Stacks" << std::endl;

  h_MuonE.hist->Write();
  std::cout << "Finished  h_MuonE" << std::endl;

  PlotUtils::MnvH1D* h_MuonE_FluxIntegrated = PlotUtils::flux_reweighter(playlist_fluxreweighter, nu_pdg, useNuEconstraint, NFlux_universe).GetIntegratedFluxReweighted(nu_pdg, h_MuonE.hist, Min_NuFluxEnergy, Max_NuFluxEnergy, useMuonCorrelations);//GetRebinnedFluxReweighted (nu_pdg, h_MuonE.hist);
  h_MuonE_FluxIntegrated->Clone()->Write("h_MuonE_FluxIntegrated");




  h_MuonPZ.hist->Write();
  PlotUtils::MnvH1D* h_MuonPZ_FluxIntegrated = PlotUtils::flux_reweighter(playlist_fluxreweighter, nu_pdg, useNuEconstraint, NFlux_universe).GetIntegratedFluxReweighted(nu_pdg, h_MuonPZ.hist, Min_NuFluxEnergy, Max_NuFluxEnergy, useMuonCorrelations); //GetRebinnedFluxReweighted (nu_pdg, h_MuonPZ.hist);
  h_MuonPZ_FluxIntegrated->Clone()->Write("h_MuonPZ_FluxIntegrated");


  h_MuonPT.hist->Write();
  PlotUtils::MnvH1D* h_MuonPT_FluxIntegrated = PlotUtils::flux_reweighter(playlist_fluxreweighter, nu_pdg, useNuEconstraint, NFlux_universe).GetIntegratedFluxReweighted(nu_pdg, h_MuonPT.hist, Min_NuFluxEnergy, Max_NuFluxEnergy, useMuonCorrelations);//GetRebinnedFluxReweighted(nu_pdg, h_MuonPT.hist);
  h_MuonPT_FluxIntegrated->Clone()->Write("h_MuonPT_FluxIntegrated");


  h_MuonTheta.hist->Write();
  PlotUtils::MnvH1D* h_MuonTheta_FluxIntegrated = PlotUtils::flux_reweighter(playlist_fluxreweighter, nu_pdg, useNuEconstraint, NFlux_universe).GetIntegratedFluxReweighted(nu_pdg, h_MuonTheta.hist, Min_NuFluxEnergy, Max_NuFluxEnergy, useMuonCorrelations); //GetRebinnedFluxReweighted(nu_pdg, h_MuonTheta.hist);
  h_MuonTheta_FluxIntegrated->Clone()->Write("h_MuonTheta_FluxIntegrated");


  h_CryoVertex_X.hist->Write();
  h_CryoVertex_Y.hist->Write();
  h_CryoVertex_Z.hist->Write();
  h_CryoVertex_R.hist->Write();
  h_Distance_to_InnerTank.hist->Write();

  std::cout << "Main Var done" << std::endl;


  h_MuonE_XCenter.hist->Write();
  h_MuonPZ_XCenter.hist->Write();
  h_MuonPT_XCenter.hist->Write();
  h_MuonTheta_XCenter.hist->Write();
  h_CryoVertex_X_XCenter.hist->Write();
  h_CryoVertex_Y_XCenter.hist->Write();
  h_CryoVertex_Z_XCenter.hist->Write();
  h_CryoVertex_R_XCenter.hist->Write();
  h_Distance_to_InnerTank_XCenter.hist->Write();
  std::cout << "Upstream Main Var done" << std::endl;

  h_MuonE_XRightShelf.hist->Write();
  h_MuonPT_XRightShelf.hist->Write();
  h_MuonPZ_XRightShelf.hist->Write();
  h_MuonTheta_XRightShelf.hist->Write();
  h_CryoVertex_X_XRightShelf.hist->Write();
  h_CryoVertex_Y_XRightShelf.hist->Write();
  h_CryoVertex_Z_XRightShelf.hist->Write();
  h_CryoVertex_R_XRightShelf.hist->Write();
  h_Distance_to_InnerTank_XRightShelf.hist->Write();

  std::cout << "XRightShelf Main Var done" << std::endl;

  h_MuonE_XLeftShelf.hist->Write();
  h_MuonPZ_XLeftShelf.hist->Write();
  h_MuonPT_XLeftShelf.hist->Write();
  h_MuonTheta_XLeftShelf.hist->Write();
  h_CryoVertex_X_XLeftShelf.hist->Write();
  h_CryoVertex_Y_XLeftShelf.hist->Write();
  h_CryoVertex_Z_XLeftShelf.hist->Write();
  h_CryoVertex_R_XLeftShelf.hist->Write();
  h_Distance_to_InnerTank_XLeftShelf.hist->Write();
  std::cout << "DownStream Main Var done" << std::endl;

  h_MuonE_XoutsideEdges.hist->Write();
  h_MuonPZ_XoutsideEdges.hist->Write();
  h_MuonPT_XoutsideEdges.hist->Write();
  h_MuonTheta_XoutsideEdges.hist->Write();
  h_CryoVertex_X_XoutsideEdges.hist->Write();
  h_CryoVertex_Y_XoutsideEdges.hist->Write();
  h_CryoVertex_Z_XoutsideEdges.hist->Write();
  h_CryoVertex_R_XoutsideEdges.hist->Write();
  h_Distance_to_InnerTank_XoutsideEdges.hist->Write();
  outFile->Close();

  std::cout << "Finished Making Root file " << std::endl;



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
