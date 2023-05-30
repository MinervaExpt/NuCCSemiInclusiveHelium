
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

//-4.0; // [mm]    //

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

const std::vector<PlotUtils::NamedCategory<CryoTank_REGIONS>>
VertexRegions_Category = {
  PlotUtils::NamedCategory<CryoTank_REGIONS>({kUpstream_head},   "UpStreamCap"),
  PlotUtils::NamedCategory<CryoTank_REGIONS>({kCenter},          "Barrel"),
  PlotUtils::NamedCategory<CryoTank_REGIONS>({kDownstream_head}, "DownStreamCap"),
  PlotUtils::NamedCategory<CryoTank_REGIONS>({kDownstream_ConcaveCap}, "DownStreamConcaveCap")
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
const std::vector<ECuts> kCutsVector_FiduicalEff = GetVectorRECOCuts_ALL();//
const std::vector<ECutsTRUTH> kCuts_Truth_Vector = GetTRUTHCutsVector_ALL();
const std::vector<Particle_type> kSecondary_particle_vector = GetParicle_type();
const std::vector<Weights> kWeights_v1tune = GetWeightVector();
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

const bool useweights = false;
const bool RunwithShift = false;

const bool RunwithConvolution = true;

const bool RunwithFid = false;

 double ShiftX_major = return_shiftX();//5.0;//-44.0; // [mm]
 double ShiftY_major = return_shiftY();//50.0; // 41 [mm]
 double ShiftZ_major = return_shiftZ();

if(RunwithShift==false){
  ShiftX_major= 0.0;
  ShiftY_major= 0.0;
  ShiftZ_major= 0.0;
}



  MinervaUniverse::SetPlaylist(playlist);

  double vertex_X_sigma = 0.0; double vertex_X_mean = 0.0;
  double vertex_Y_sigma = 0.0; double vertex_Y_mean = 0.0;
  double vertex_Z_sigma = 0.0; double vertex_Z_mean = 0.0;
std::default_random_engine generator;

if(RunwithConvolution == true){
  Fill_Convolution_BeforeShift(PlayList_iterator ,vertex_X_mean,
    vertex_X_sigma, vertex_Y_mean, vertex_Y_sigma, vertex_Z_mean, vertex_Z_sigma);
}

std::normal_distribution<double> vertexZ_Convolution(vertex_Z_mean, vertex_Z_sigma);
std::normal_distribution<double> vertexX_Convolution(vertex_X_mean, vertex_X_sigma);
std::normal_distribution<double> vertexY_Convolution(vertex_Y_mean, vertex_Y_sigma);




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
//std::vector<double> Vertex_Zbin_vector = GetBinvertexVector(kZ);
//std::vector<double> Vertex_Rbin_vector = GetBinvertexVector(kR);
//std::vector<double> Vertex_Ybin_vector = GetBinvertexVector(kY);
//std::vector<double> Vertex_Xbin_vector = GetBinvertexVector(kX

  std::vector<double> Vertex_Zbin_vector{1450, 1750.00, 2050.00, 2250, 2450, 2650, 2850, 3000, 3200,  3400, 3650, 3900, 4200, 4350};
  std::vector<double> Vertex_Rbin_vector{0, 200, 400, 600,  700,   800,  1000,  1200};
  std::vector<double> Vertex_Ybin_vector{-1200, -1000, -800, -600, -400, -200, 0, 200, 400, 600, 800, 1000, 1200};
  std::vector<double> Vertex_Xbin_vector{-1200, -1000, -800, -600, -400, -200, 0, 200, 400, 600, 800, 1000, 1200};




std::vector<double> Distance_to_innerTank = GetBinvertexVector(kdistance_edge);
std::vector<double> Vertex_DOCAbin_vector = GetBinMuonVector(kDOCA_muon);
std::vector<double> secTrk_DOCA_vector = GetSecondTrkVarVector(kDOCA);
std::vector<double> Distance_to_Caps = GetBinvertexVector(kdistance_downstreamcap);
std::vector<double> Ebin_vector = GetBinMuonVector(kE);
std::vector<double> Pzbin_vector = GetBinMuonVector(kP_Z);
std::vector<double> PTbin_vector = GetBinMuonVector(kP_T);
std::vector<double> MuonThetabin_vector = GetBinMuonVector(kAngleWRTB);
std::vector<double> secTrk_Pathway_vector = GetSecondTrkVarVector(kPathway);
std::vector<double> Recoil_track_length_vector = GetSecondTrkVarVector(ksec_tracklength_minerva);

std::vector<double> Vertex_resolution_Xbin_vector = GetBinvertexVector(kX_resolution);
std::vector<double> Vertex_resolution_Ybin_vector = GetBinvertexVector(kY_resolution);
std::vector<double> Vertex_resolution_Zbin_vector = GetBinvertexVector(kZ_resolution);
std::vector<double> Vertex_resolution_Rbin_vector = GetBinvertexVector(kR_resolution);
std::vector<double> Vertex_resolution_RRbin_vector= GetBinvertexVector(kRR_resolution);

std::vector<double> Bins_toAddxyr{ -100, 100};

std::vector<double> Bins_toAddZ{-600,-550,-500, -450, -400 ,-350, 350, 400, 450, 500, 550,600};


for(auto cat : Bins_toAddxyr){
Vertex_resolution_Rbin_vector.push_back(cat);
Vertex_resolution_Xbin_vector.push_back(cat);
Vertex_resolution_Ybin_vector.push_back(cat);
}

for(auto cat : Bins_toAddZ){
Vertex_resolution_Zbin_vector.push_back(cat);
}



std::sort(Vertex_resolution_Rbin_vector.begin(),Vertex_resolution_Rbin_vector.end());
std::sort(Vertex_resolution_Xbin_vector.begin(),Vertex_resolution_Xbin_vector.end());
std::sort(Vertex_resolution_Ybin_vector.begin(),Vertex_resolution_Ybin_vector.end());
std::sort(Vertex_resolution_Zbin_vector.begin(),Vertex_resolution_Zbin_vector.end());


std::vector<double> Vertex_Percent_resolution_Xbin_vector= GetBinvertexVector(kX_Precent_resolution);
std::vector<double> Vertex_Percent_resolution_Ybin_vector= GetBinvertexVector(kY_Precent_resolution);
std::vector<double> Vertex_Percent_resolution_Zbin_vector= GetBinvertexVector(kZ_Precent_resolution);
std::vector<double> Vertex_Percent_resolution_Rbin_vector= GetBinvertexVector(kR_Precent_resolution);
std::vector<double> Vertex_Percent_resolution_RRbin_vector= GetBinvertexVector(kRR_Precent_resolution);



PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE("h_MuonE", "Muon_{E}", Ebin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPZ("h_MuonPZ", "Muon_{PZ}",  Pzbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPT("h_MuonPT", "Muon_{PT}",  PTbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonTheta("h_MuonTheta", "#theta_{#mu} NEW Method",  MuonThetabin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X("h_CryoVertex_X", "Vertex_X",  Vertex_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y("h_CryoVertex_Y", "Vertex_Y",  Vertex_Ybin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z("h_CryoVertex_Z", "Vertex_Z",  Vertex_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_RCut("h_CryoVertex_Z_RCut", "Vertex_Z_RCut",  Vertex_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R("h_CryoVertex_R", "h_CryoVertex_R",  Vertex_Rbin_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_RCut("h_CryoVertex_X_RCut", "Vertex_X",  Vertex_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_RCut("h_CryoVertex_Y_RCut", "Vertex_Y",  Vertex_Ybin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_RCut("h_CryoVertex_R_RCut", "h_CryoVertex_R",  Vertex_Rbin_vector , error_bands);


PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_InnerTank("h_Distance_to_InnerTank", "h_Distance_to_InnerTank",  Distance_to_innerTank, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonDOCA("h_MuonDOCA", "Muon_DOCA",  Vertex_DOCAbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_DOCA("h_secTrk_DOCA", "h_secTrk DOCA",  secTrk_DOCA_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Pathlength("h_secTrk_Pathlength", "h_secTrk Pathlength ",  secTrk_Pathway_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_tracklength("h_secTrk_tracklength", "Recoil track length  [cm] ", Recoil_track_length_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_downstreamCap("h_Distance_to_downstreamCap", "h_Distance_to_downstreamCap",  Distance_to_Caps, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_upstreamCap("h_Distance_to_upstreamCap", "h_Distance_to_upstreamCap",  Distance_to_Caps, error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_downstreamCap_RCut("h_Distance_to_downstreamCap_RCut", "h_Distance_to_downstreamCap_RCut",  Distance_to_Caps, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_upstreamCap_RCut("h_Distance_to_upstreamCap_RCut", "h_Distance_to_upstreamCap_RCut",  Distance_to_Caps, error_bands);


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

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_R_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_R_Material", Vertex_Rbin_vector ,"h_CryoVertex_R_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_X_RCut_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_X_RCut_Material", Vertex_Xbin_vector ,"h_CryoVertex_X_RCut_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Y_RCut_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Y_RCut_Material", Vertex_Ybin_vector ,"h_CryoVertex_Y_RCut_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_R_RCut_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_R_RCut_Material", Vertex_Rbin_vector ,"h_CryoVertex_R_RCut_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Z_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Z_Material", Vertex_Zbin_vector ,"h_CryoVertex_Z_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Z_RCut_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Z_RCut_Material", Vertex_Zbin_vector ,"h_CryoVertex_Z_RCut_Material; [mm];Events");



PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Distance_to_InnerTank_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Distance_to_InnerTank_Material",  Distance_to_innerTank  ,"h_Distance_to_InnerTank_Material");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonDOCA_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonDOCA_Material", Vertex_DOCAbin_vector ,"h_MuonDOCA_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_tracklength_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_tracklength_Material", Recoil_track_length_vector ,"h_secTrk_tracklength_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_DOCA_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_DOCA_Material", secTrk_DOCA_vector ,"h_secTrk_DOCA_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Distance_to_downstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Distance_to_downstreamCap_Material", Distance_to_Caps ,"h_Distance_to_downstreamCap_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Distance_to_downstreamCap_RCut_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Distance_to_downstreamCap_RCut_Material", Distance_to_Caps ,"h_Distance_to_downstreamCap_RCut_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Distance_to_upstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Distance_to_upstreamCap_Material", Distance_to_Caps ,"h_Distance_to_upstreamCap_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Distance_to_upstreamCap_RCut_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Distance_to_upstreamCap_RCut_Material", Distance_to_Caps ,"h_Distance_to_upstreamCap_RCut_Material; [mm];Events");




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
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE_UpstreamCap(                "h_MuonE_UpstreamCap", "Muon_{E}", Ebin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPZ_UpstreamCap(               "h_MuonPZ_UpstreamCap", "Muon_{PZ}",  Pzbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPT_UpstreamCap(               "h_MuonPT_UpstreamCap", "Muon_{PT}",  PTbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonTheta_UpstreamCap(            "h_MuonTheta_UpstreamCap", "#theta_{#mu} NEW Method",  MuonThetabin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_UpstreamCap(         "h_CryoVertex_X_UpstreamCap", "Vertex X",  Vertex_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_UpstreamCap(         "h_CryoVertex_Y_UpstreamCap", "Vertex Y",  Vertex_Ybin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_UpstreamCap(         "h_CryoVertex_R_UpstreamCap", "Vertex R",  Vertex_Rbin_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_RCut_UpstreamCap(         "h_CryoVertex_X_RCut_UpstreamCap", "Vertex X",  Vertex_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_RCut_UpstreamCap(         "h_CryoVertex_Y_RCut_UpstreamCap", "Vertex Y",  Vertex_Ybin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_RCut_UpstreamCap(         "h_CryoVertex_R_RCut_UpstreamCap", "Vertex R",  Vertex_Rbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_UpstreamCap(         "h_CryoVertex_Z_UpstreamCap", "Vertex Z",  Vertex_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_RCut_UpstreamCap(    "h_CryoVertex_Z_RCut_UpstreamCap", "Vertex Z",  Vertex_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_InnerTank_UpstreamCap("h_Distance_to_InnerTank_UpstreamCap", "h_Distance_to_InnerTank_UpstreamCap",  Distance_to_innerTank, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonDOCA_UpstreamCap(             "h_MuonDOCA_UpstreamCap", "Muon_DOCA",  Vertex_DOCAbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_DOCA_UpstreamCap(          "h_secTrk_DOCA_UpstreamCap", "h_secTrk DOCA",  secTrk_DOCA_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Pathlength_UpstreamCap(    "h_secTrk_Pathlength_UpstreamCap", "h_secTrk Pathlength ",  secTrk_Pathway_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_tracklength_UpstreamCap(   "h_secTrk_tracklength_UpstreamCap", "Recoil track length  [cm] ", Recoil_track_length_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_InnerTank_Barrel_UpstreamCap("h_Distance_to_InnerTank_Barrel_UpstreamCap", "h_Distance_to_InnerTank_Barrel_UpstreamCap",      Distance_to_innerTank, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_InnerTank_Caps_UpstreamCap(  "h_Distance_to_InnerTank_Caps_UpstreamCap",   "h_Distance_to_InnerTank_Caps_UpstreamCap",        Distance_to_innerTank, error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_InnerTank_Barrel_Barrel("h_Distance_to_InnerTank_Barrel_Barrel", "h_Distance_to_InnerTank_Barrel_Barrel",      Distance_to_innerTank, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_InnerTank_Caps_Barrel(  "h_Distance_to_InnerTank_Caps_Barrel",   "h_Distance_to_InnerTank_Caps_Barrel",        Distance_to_innerTank, error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_InnerTank_Barrel_DownstreamCap("h_Distance_to_InnerTank_Barrel_DownstreamCap", "h_Distance_to_InnerTank_Barrel_DownstreamCap",      Distance_to_innerTank, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_InnerTank_Caps_DownstreamCap(  "h_Distance_to_InnerTank_Caps_DownstreamCap",   "h_Distance_to_InnerTank_Caps_DownstreamCap",        Distance_to_innerTank, error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_InnerTank_Barrel_Downstream_ConcaveCap("h_Distance_to_InnerTank_Barrel_Downstream_ConcaveCap", "h_Distance_to_InnerTank_Barrel_Downstream_ConcaveCap",      Distance_to_innerTank, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_InnerTank_Caps_Downstream_ConcaveCap(  "h_Distance_to_InnerTank_Caps_Downstream_ConcaveCap",   "h_Distance_to_InnerTank_Caps_Downstream_ConcaveCap",        Distance_to_innerTank, error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_downstreamCap_UpstreamCap("h_Distance_to_downstreamCap_UpstreamCap", "h_Distance_to_downstreamCap_UpstreamCap",  Distance_to_Caps, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_upstreamCap_UpstreamCap(  "h_Distance_to_upstreamCap_UpstreamCap",   "h_Distance_to_upstreamCap_UpstreamCap",    Distance_to_Caps, error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_downstreamCap_RCut_UpstreamCap("h_Distance_to_downstreamCap_RCut_UpstreamCap", "h_Distance_to_downstreamCap_RCut_UpstreamCap",  Distance_to_Caps, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_upstreamCap_RCut_UpstreamCap(  "h_Distance_to_upstreamCap_RCut_UpstreamCap",   "h_Distance_to_upstreamCap_RCut_UpstreamCap",    Distance_to_Caps, error_bands);


///////////////////////////////////////////////////////////////////////////////////////

PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_resolution_RECO(            "h_CryoVertex_Y_resolution_RECO",             "h_CryoVertex_Y_resolution_RECO",                 Vertex_resolution_Ybin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_percentresolution_RECO(     "h_CryoVertex_Y_percentresolution_RECO",      "h_CryoVertex_Y_percentresolution_RECO",          Vertex_Percent_resolution_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_resolution_TRUE_RECO(       "h_CryoVertex_Y_resolution_TRUE_RECO",        "h_CryoVertex_Y_resolution_TRUE_RECO",            Vertex_resolution_Ybin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_percentresolution_TRUE_RECO("h_CryoVertex_Y_percentresolution_TRUE_RECO", "h_CryoVertex_Y_percentresolution_TRUE_RECO",     Vertex_Percent_resolution_Xbin_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_UpstreamCap_resolution_RECO(          "h_CryoVertex_Y_UpstreamCap_resolution_RECO",           "h_CryoVertex_Y_UpstreamCap_resolution_RECO",                                 Vertex_resolution_Ybin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_UpstreamCap_percentresolution_RECO(   "h_CryoVertex_Y_UpstreamCap_percentresolution_RECO",    "h_CryoVertex_Y_UpstreamCap_percentresolution_RECO",                          Vertex_Percent_resolution_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_Barrel_resolution_RECO(               "h_CryoVertex_Y_Barrel_resolution_RECO",                "h_CryoVertex_Y_Barrel_resolution_RECO",                                      Vertex_resolution_Ybin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_Barrel_percentresolution_RECO(        "h_CryoVertex_Y_Barrel_percentresolution_RECO",         "h_CryoVertex_Y_Barrel_percentresolution_RECO",                               Vertex_Percent_resolution_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_DownstreamCap_resolution_RECO(        "h_CryoVertex_Y_DownstreamCap_resolution_RECO",         "h_CryoVertex_Y_DownstreamCap_resolution_RECO",                               Vertex_resolution_Ybin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_DownstreamCap_percentresolution_RECO( "h_CryoVertex_Y_DownstreamCap_percentresolution_RECO",  "h_CryoVertex_Y_DownstreamCap_percentresolution_RECO",                        Vertex_Percent_resolution_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_Downstream_ConcaveCap_resolution_RECO("h_CryoVertex_Y_Downstream_ConcaveCap_resolution_RECO", "h_CryoVertex_Y_Downstream_ConcaveCap_resolution_RECO",                       Vertex_resolution_Ybin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_Downstream_ConcaveCap_percentresolution_RECO("h_CryoVertex_Y_Downstream_ConcaveCap_percentresolution_RECO", "h_CryoVertex_Y_Downstream_ConcaveCap_percentresolution_RECO",  Vertex_Percent_resolution_Xbin_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_UpstreamCap_resolution_TRUE_RECO(          "h_CryoVertex_Y_UpstreamCap_resolution_TRUE_RECO",           "h_CryoVertex_Y_UpstreamCap_resolution_TRUE_RECO",                                 Vertex_resolution_Ybin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_UpstreamCap_percentresolution_TRUE_RECO(   "h_CryoVertex_Y_UpstreamCap_percentresolution_TRUE_RECO",    "h_CryoVertex_Y_UpstreamCap_percentresolution_TRUE_RECO",                          Vertex_Percent_resolution_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_Barrel_resolution_TRUE_RECO(               "h_CryoVertex_Y_Barrel_resolution_TRUE_RECO",                "h_CryoVertex_Y_Barrel_resolution_TRUE_RECO",                                      Vertex_resolution_Ybin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_Barrel_percentresolution_TRUE_RECO(        "h_CryoVertex_Y_Barrel_percentresolution_TRUE_RECO",         "h_CryoVertex_Y_Barrel_percentresolution_TRUE_RECO",                               Vertex_Percent_resolution_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_DownstreamCap_resolution_TRUE_RECO(        "h_CryoVertex_Y_DownstreamCap_resolution_TRUE_RECO",         "h_CryoVertex_Y_DownstreamCap_resolution_TRUE_RECO",                               Vertex_resolution_Ybin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_DownstreamCap_percentresolution_TRUE_RECO( "h_CryoVertex_Y_DownstreamCap_percentresolution_TRUE_RECO",  "h_CryoVertex_Y_DownstreamCap_percentresolution_TRUE_RECO",                        Vertex_Percent_resolution_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_Downstream_ConcaveCap_resolution_TRUE_RECO("h_CryoVertex_Y_Downstream_ConcaveCap_resolution_TRUE_RECO", "h_CryoVertex_Y_Downstream_ConcaveCap_resolution_TRUE_RECO",                       Vertex_resolution_Ybin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_Downstream_ConcaveCap_percentresolution_TRUE_RECO("h_CryoVertex_Y_Downstream_ConcaveCap_percentresolution_TRUE_RECO", "h_CryoVertex_Y_Downstream_ConcaveCap_percentresolution_TRUE_RECO",  Vertex_Percent_resolution_Xbin_vector , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Y_resolution_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Y_resolution_Material", Vertex_resolution_Ybin_vector ,"h_CryoVertex_Y_resolution_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Y_UpstreamCap_resolution_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Y_UpstreamCap_resolution_Material", Vertex_resolution_Ybin_vector ,"h_CryoVertex_Y_UpstreamCap_resolution_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Y_Barrel_resolution_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Y_Barrel_resolution_Material", Vertex_resolution_Ybin_vector ,"h_CryoVertex_Y_Barrel_resolution_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Y_DownstreamCap_resolution_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Y_DownstreamCap_resolution_Material", Vertex_resolution_Ybin_vector ,"h_CryoVertex_Y_UpstreamCap_resolution_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Y_Downstream_ConcaveCap_resolution_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Y_Downstream_ConcaveCap_resolution_Material", Vertex_resolution_Ybin_vector ,"h_CryoVertex_Y_UpstreamCap_resolution_Material; [mm];Events");
/////////////////////////////////////////////////////

PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_resolution_RECO(            "h_CryoVertex_R_resolution_RECO",             "h_CryoVertex_R_resolution_RECO",                 Vertex_resolution_Rbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_percentresolution_RECO(     "h_CryoVertex_R_percentresolution_RECO",      "h_CryoVertex_R_percentresolution_RECO",          Vertex_Percent_resolution_Rbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_resolution_TRUE_RECO(       "h_CryoVertex_R_resolution_TRUE_RECO",        "h_CryoVertex_R_resolution_TRUE_RECO",            Vertex_resolution_Rbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_percentresolution_TRUE_RECO("h_CryoVertex_R_percentresolution_TRUE_RECO", "h_CryoVertex_R_percentresolution_TRUE_RECO",     Vertex_Percent_resolution_Rbin_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_UpstreamCap_resolution_RECO(          "h_CryoVertex_R_UpstreamCap_resolution_RECO",           "h_CryoVertex_R_UpstreamCap_resolution_RECO",                                 Vertex_resolution_Rbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_UpstreamCap_percentresolution_RECO(   "h_CryoVertex_R_UpstreamCap_percentresolution_RECO",    "h_CryoVertex_R_UpstreamCap_percentresolution_RECO",                          Vertex_Percent_resolution_Rbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_Barrel_resolution_RECO(               "h_CryoVertex_R_Barrel_resolution_RECO",                "h_CryoVertex_R_Barrel_resolution_RECO",                                      Vertex_resolution_Rbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_Barrel_percentresolution_RECO(        "h_CryoVertex_R_Barrel_percentresolution_RECO",         "h_CryoVertex_R_Barrel_percentresolution_RECO",                               Vertex_Percent_resolution_Rbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_DownstreamCap_resolution_RECO(        "h_CryoVertex_R_DownstreamCap_resolution_RECO",         "h_CryoVertex_R_DownstreamCap_resolution_RECO",                               Vertex_resolution_Rbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_DownstreamCap_percentresolution_RECO( "h_CryoVertex_R_DownstreamCap_percentresolution_RECO",  "h_CryoVertex_R_DownstreamCap_percentresolution_RECO",                        Vertex_Percent_resolution_Rbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_Downstream_ConcaveCap_resolution_RECO("h_CryoVertex_R_Downstream_ConcaveCap_resolution_RECO", "h_CryoVertex_R_Downstream_ConcaveCap_resolution_RECO",                       Vertex_resolution_Rbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_Downstream_ConcaveCap_percentresolution_RECO("h_CryoVertex_R_Downstream_ConcaveCap_percentresolution_RECO", "h_CryoVertex_R_Downstream_ConcaveCap_percentresolution_RECO",  Vertex_Percent_resolution_Rbin_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_UpstreamCap_resolution_TRUE_RECO(          "h_CryoVertex_R_UpstreamCap_resolution_TRUE_RECO",           "h_CryoVertex_R_UpstreamCap_resolution_TRUE_RECO",                                 Vertex_resolution_Rbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_UpstreamCap_percentresolution_TRUE_RECO(   "h_CryoVertex_R_UpstreamCap_percentresolution_TRUE_RECO",    "h_CryoVertex_R_UpstreamCap_percentresolution_TRUE_RECO",                          Vertex_Percent_resolution_Rbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_Barrel_resolution_TRUE_RECO(               "h_CryoVertex_R_Barrel_resolution_TRUE_RECO",                "h_CryoVertex_R_Barrel_resolution_TRUE_RECO",                                      Vertex_resolution_Rbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_Barrel_percentresolution_TRUE_RECO(        "h_CryoVertex_R_Barrel_percentresolution_TRUE_RECO",         "h_CryoVertex_R_Barrel_percentresolution_TRUE_RECO",                               Vertex_Percent_resolution_Rbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_DownstreamCap_resolution_TRUE_RECO(        "h_CryoVertex_R_DownstreamCap_resolution_TRUE_RECO",         "h_CryoVertex_R_DownstreamCap_resolution_TRUE_RECO",                               Vertex_resolution_Rbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_DownstreamCap_percentresolution_TRUE_RECO( "h_CryoVertex_R_DownstreamCap_percentresolution_TRUE_RECO",  "h_CryoVertex_R_DownstreamCap_percentresolution_TRUE_RECO",                        Vertex_Percent_resolution_Rbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_Downstream_ConcaveCap_resolution_TRUE_RECO("h_CryoVertex_R_Downstream_ConcaveCap_resolution_TRUE_RECO", "h_CryoVertex_R_Downstream_ConcaveCap_resolution_TRUE_RECO",                       Vertex_resolution_Rbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_Downstream_ConcaveCap_percentresolution_TRUE_RECO("h_CryoVertex_R_Downstream_ConcaveCap_percentresolution_TRUE_RECO", "h_CryoVertex_R_Downstream_ConcaveCap_percentresolution_TRUE_RECO",  Vertex_Percent_resolution_Rbin_vector , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_R_resolution_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_R_resolution_Material", Vertex_resolution_Rbin_vector ,"h_CryoVertex_R_resolution_Material; [mm];Events");


PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_R_UpstreamCap_resolution_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_R_UpstreamCap_resolution_Material", Vertex_resolution_Rbin_vector ,"h_CryoVertex_R_UpstreamCap_resolution_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_R_Barrel_resolution_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_R_Barrel_resolution_Material", Vertex_resolution_Rbin_vector ,"h_CryoVertex_R_Barrel_resolution_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_R_DownstreamCap_resolution_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_R_DownstreamCap_resolution_Material", Vertex_resolution_Rbin_vector ,"h_CryoVertex_R_UpstreamCap_resolution_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_R_Downstream_ConcaveCap_resolution_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_R_Downstream_ConcaveCap_resolution_Material", Vertex_resolution_Rbin_vector ,"h_CryoVertex_R_UpstreamCap_resolution_Material; [mm];Events");
////////////////////////////////////////////////////////////////

PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_resolution_RECO(            "h_CryoVertex_Z_resolution_RECO",             "h_CryoVertex_Z_resolution_RECO",                 Vertex_resolution_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_percentresolution_RECO(     "h_CryoVertex_Z_percentresolution_RECO",      "h_CryoVertex_Z_percentresolution_RECO",          Vertex_Percent_resolution_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_resolution_TRUE_RECO(       "h_CryoVertex_Z_resolution_TRUE_RECO",        "h_CryoVertex_Z_resolution_TRUE_RECO",            Vertex_resolution_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_percentresolution_TRUE_RECO("h_CryoVertex_Z_percentresolution_TRUE_RECO", "h_CryoVertex_Z_percentresolution_TRUE_RECO",     Vertex_Percent_resolution_Zbin_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_UpstreamCap_resolution_RECO(          "h_CryoVertex_Z_UpstreamCap_resolution_RECO",           "h_CryoVertex_Z_UpstreamCap_resolution_RECO",                                 Vertex_resolution_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_UpstreamCap_percentresolution_RECO(   "h_CryoVertex_Z_UpstreamCap_percentresolution_RECO",    "h_CryoVertex_Z_UpstreamCap_percentresolution_RECO",                          Vertex_Percent_resolution_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_Barrel_resolution_RECO(               "h_CryoVertex_Z_Barrel_resolution_RECO",                "h_CryoVertex_Z_Barrel_resolution_RECO",                                      Vertex_resolution_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_Barrel_percentresolution_RECO(        "h_CryoVertex_Z_Barrel_percentresolution_RECO",         "h_CryoVertex_Z_Barrel_percentresolution_RECO",                               Vertex_Percent_resolution_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_DownstreamCap_resolution_RECO(        "h_CryoVertex_Z_DownstreamCap_resolution_RECO",         "h_CryoVertex_Z_DownstreamCap_resolution_RECO",                               Vertex_resolution_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_DownstreamCap_percentresolution_RECO( "h_CryoVertex_Z_DownstreamCap_percentresolution_RECO",  "h_CryoVertex_Z_DownstreamCap_percentresolution_RECO",                        Vertex_Percent_resolution_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_Downstream_ConcaveCap_resolution_RECO("h_CryoVertex_Z_Downstream_ConcaveCap_resolution_RECO", "h_CryoVertex_Z_Downstream_ConcaveCap_resolution_RECO",                       Vertex_resolution_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_Downstream_ConcaveCap_percentresolution_RECO("h_CryoVertex_Z_Downstream_ConcaveCap_percentresolution_RECO", "h_CryoVertex_Z_Downstream_ConcaveCap_percentresolution_RECO",  Vertex_Percent_resolution_Zbin_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_UpstreamCap_resolution_TRUE_RECO(          "h_CryoVertex_Z_UpstreamCap_resolution_TRUE_RECO",           "h_CryoVertex_Z_UpstreamCap_resolution_TRUE_RECO",                                 Vertex_resolution_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_UpstreamCap_percentresolution_TRUE_RECO(   "h_CryoVertex_Z_UpstreamCap_percentresolution_TRUE_RECO",    "h_CryoVertex_Z_UpstreamCap_percentresolution_TRUE_RECO",                          Vertex_Percent_resolution_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_Barrel_resolution_TRUE_RECO(               "h_CryoVertex_Z_Barrel_resolution_TRUE_RECO",                "h_CryoVertex_Z_Barrel_resolution_TRUE_RECO",                                      Vertex_resolution_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_Barrel_percentresolution_TRUE_RECO(        "h_CryoVertex_Z_Barrel_percentresolution_TRUE_RECO",         "h_CryoVertex_Z_Barrel_percentresolution_TRUE_RECO",                               Vertex_Percent_resolution_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_DownstreamCap_resolution_TRUE_RECO(        "h_CryoVertex_Z_DownstreamCap_resolution_TRUE_RECO",         "h_CryoVertex_Z_DownstreamCap_resolution_TRUE_RECO",                               Vertex_resolution_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_DownstreamCap_percentresolution_TRUE_RECO( "h_CryoVertex_Z_DownstreamCap_percentresolution_TRUE_RECO",  "h_CryoVertex_Z_DownstreamCap_percentresolution_TRUE_RECO",                        Vertex_Percent_resolution_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_Downstream_ConcaveCap_resolution_TRUE_RECO("h_CryoVertex_Z_Downstream_ConcaveCap_resolution_TRUE_RECO", "h_CryoVertex_Z_Downstream_ConcaveCap_resolution_TRUE_RECO",                       Vertex_resolution_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_Downstream_ConcaveCap_percentresolution_TRUE_RECO("h_CryoVertex_Z_Downstream_ConcaveCap_percentresolution_TRUE_RECO", "h_CryoVertex_Z_Downstream_ConcaveCap_percentresolution_TRUE_RECO",  Vertex_Percent_resolution_Zbin_vector , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Z_resolution_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Z_resolution_Material", Vertex_resolution_Zbin_vector ,"h_CryoVertex_Z_resolution_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Z_UpstreamCap_resolution_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Z_UpstreamCap_resolution_Material", Vertex_resolution_Zbin_vector ,"h_CryoVertex_Z_UpstreamCap_resolution_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Z_Barrel_resolution_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Z_Barrel_resolution_Material",      Vertex_resolution_Zbin_vector ,"h_CryoVertex_Z_Barrel_resolution_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Z_DownstreamCap_resolution_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Z_DownstreamCap_resolution_Material", Vertex_resolution_Zbin_vector ,"h_CryoVertex_Z_DownstreamCap_resolution_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Z_Downstream_ConcaveCap_resolution_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Z_Downstream_ConcaveCap_resolution_Material", Vertex_resolution_Zbin_vector ,"h_CryoVertex_Z_Downstream_ConcaveCap_resolution_Material; [mm];Events");
////////////////////////////////////////////////////////////////////////////////

PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_resolution_RECO(            "h_CryoVertex_X_resolution_RECO",             "h_CryoVertex_X_resolution_RECO",                 Vertex_resolution_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_percentresolution_RECO(     "h_CryoVertex_X_percentresolution_RECO",      "h_CryoVertex_X_percentresolution_RECO",          Vertex_Percent_resolution_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_resolution_TRUE_RECO(       "h_CryoVertex_X_resolution_TRUE_RECO",        "h_CryoVertex_X_resolution_TRUE_RECO",            Vertex_resolution_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_percentresolution_TRUE_RECO("h_CryoVertex_X_percentresolution_TRUE_RECO", "h_CryoVertex_X_percentresolution_TRUE_RECO",     Vertex_Percent_resolution_Xbin_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_UpstreamCap_resolution_RECO(          "h_CryoVertex_X_UpstreamCap_resolution_RECO",           "h_CryoVertex_X_UpstreamCap_resolution_RECO",                                 Vertex_resolution_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_UpstreamCap_percentresolution_RECO(   "h_CryoVertex_X_UpstreamCap_percentresolution_RECO",    "h_CryoVertex_X_UpstreamCap_percentresolution_RECO",                          Vertex_Percent_resolution_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_Barrel_resolution_RECO(               "h_CryoVertex_X_Barrel_resolution_RECO",                "h_CryoVertex_X_Barrel_resolution_RECO",                                      Vertex_resolution_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_Barrel_percentresolution_RECO(        "h_CryoVertex_X_Barrel_percentresolution_RECO",         "h_CryoVertex_X_Barrel_percentresolution_RECO",                               Vertex_Percent_resolution_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_DownstreamCap_resolution_RECO(        "h_CryoVertex_X_DownstreamCap_resolution_RECO",         "h_CryoVertex_X_DownstreamCap_resolution_RECO",                               Vertex_resolution_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_DownstreamCap_percentresolution_RECO( "h_CryoVertex_X_DownstreamCap_percentresolution_RECO",  "h_CryoVertex_X_DownstreamCap_percentresolution_RECO",                        Vertex_Percent_resolution_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_Downstream_ConcaveCap_resolution_RECO("h_CryoVertex_X_Downstream_ConcaveCap_resolution_RECO", "h_CryoVertex_X_Downstream_ConcaveCap_resolution_RECO",                       Vertex_resolution_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_Downstream_ConcaveCap_percentresolution_RECO("h_CryoVertex_X_Downstream_ConcaveCap_percentresolution_RECO", "h_CryoVertex_X_Downstream_ConcaveCap_percentresolution_RECO",  Vertex_Percent_resolution_Xbin_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_UpstreamCap_resolution_TRUE_RECO(          "h_CryoVertex_X_UpstreamCap_resolution_TRUE_RECO",           "h_CryoVertex_X_UpstreamCap_resolution_TRUE_RECO",                                 Vertex_resolution_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_UpstreamCap_percentresolution_TRUE_RECO(   "h_CryoVertex_X_UpstreamCap_percentresolution_TRUE_RECO",    "h_CryoVertex_X_UpstreamCap_percentresolution_TRUE_RECO",                          Vertex_Percent_resolution_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_Barrel_resolution_TRUE_RECO(               "h_CryoVertex_X_Barrel_resolution_TRUE_RECO",                "h_CryoVertex_X_Barrel_resolution_TRUE_RECO",                                      Vertex_resolution_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_Barrel_percentresolution_TRUE_RECO(        "h_CryoVertex_X_Barrel_percentresolution_TRUE_RECO",         "h_CryoVertex_X_Barrel_percentresolution_TRUE_RECO",                               Vertex_Percent_resolution_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_DownstreamCap_resolution_TRUE_RECO(        "h_CryoVertex_X_DownstreamCap_resolution_TRUE_RECO",         "h_CryoVertex_X_DownstreamCap_resolution_TRUE_RECO",                               Vertex_resolution_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_DownstreamCap_percentresolution_TRUE_RECO( "h_CryoVertex_X_DownstreamCap_percentresolution_TRUE_RECO",  "h_CryoVertex_X_DownstreamCap_percentresolution_TRUE_RECO",                        Vertex_Percent_resolution_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_Downstream_ConcaveCap_resolution_TRUE_RECO("h_CryoVertex_X_Downstream_ConcaveCap_resolution_TRUE_RECO", "h_CryoVertex_X_Downstream_ConcaveCap_resolution_TRUE_RECO",                       Vertex_resolution_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_Downstream_ConcaveCap_percentresolution_TRUE_RECO("h_CryoVertex_X_Downstream_ConcaveCap_percentresolution_TRUE_RECO", "h_CryoVertex_X_Downstream_ConcaveCap_percentresolution_TRUE_RECO",  Vertex_Percent_resolution_Xbin_vector , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_X_resolution_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_X_resolution_Material", Vertex_resolution_Xbin_vector ,"h_CryoVertex_X_resolution_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_X_UpstreamCap_resolution_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_X_UpstreamCap_resolution_Material", Vertex_resolution_Xbin_vector ,"h_CryoVertex_X_UpstreamCap_resolution_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_X_Barrel_resolution_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_X_Barrel_resolution_Material", Vertex_resolution_Xbin_vector ,"h_CryoVertex_X_Barrel_resolution_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_X_DownstreamCap_resolution_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_X_DownstreamCap_resolution_Material", Vertex_resolution_Xbin_vector ,"h_CryoVertex_X_UpstreamCap_resolution_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_X_Downstream_ConcaveCap_resolution_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_X_Downstream_ConcaveCap_resolution_Material", Vertex_resolution_Xbin_vector ,"h_CryoVertex_X_UpstreamCap_resolution_Material; [mm];Events");

/////////

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonE_UpstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonE_UpstreamCap_Material", Ebin_vector ,"MuonE_UpstreamCap_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonPZ_UpstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonPZ_UpstreamCap_Material", Pzbin_vector ,"h_MuonPZ_UpstreamCap_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonPT_UpstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonPT_UpstreamCap_Material", PTbin_vector ,"h_MuonPT_UpstreamCap_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonTheta_UpstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonTheta_UpstreamCap_Material", MuonThetabin_vector ,"h_MuonTheta_UpstreamCap_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_X_UpstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_X_UpstreamCap_Material", Vertex_Xbin_vector ,"h_CryoVertex_X_UpstreamCap_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Y_UpstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Y_UpstreamCap_Material", Vertex_Ybin_vector ,"h_CryoVertex_Y_UpstreamCap_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_R_UpstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_R_UpstreamCap_Material", Vertex_Rbin_vector ,"h_CryoVertex_R_UpstreamCap_Material; [mm];Events");
/////
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_X_RCut_UpstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_X_RCut_UpstreamCap_Material", Vertex_Xbin_vector ,"h_CryoVertex_X_RCut_UpstreamCap_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Y_RCut_UpstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Y_RCut_UpstreamCap_Material", Vertex_Ybin_vector ,"h_CryoVertex_Y_RCut_UpstreamCap_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_R_RCut_UpstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_R_RCut_UpstreamCap_Material", Vertex_Rbin_vector ,"h_CryoVertex_R_RCut_UpstreamCap_Material; [mm];Events");

///
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Z_UpstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Z_UpstreamCap_Material", Vertex_Zbin_vector ,"h_CryoVertex_Z_UpstreamCap_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Z_RCut_UpstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Z_RCut_UpstreamCap_Material", Vertex_Zbin_vector ,"h_CryoVertex_Z_RCut_UpstreamCap_Material; [mm];Events");


PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Distance_to_InnerTank_UpstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Distance_to_InnerTank_UpstreamCap_Material",  Distance_to_innerTank  ,"h_Distance_to_InnerTank_UpstreamCap_Material");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_DOCA_UpstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_DOCA_UpstreamCap_Material", secTrk_DOCA_vector ,"h_secTrk_DOCA_UpstreamCap_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonDOCA_UpstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonDOCA_UpstreamCap_Material", Vertex_DOCAbin_vector ,"h_MuonDOCA_UpstreamCap_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_tracklength_UpstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_tracklength_UpstreamCap_Material", Recoil_track_length_vector ,"h_secTrk_tracklength_UpstreamCap_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_Pathlength_UpstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_Pathlength_UpstreamCap_Material", secTrk_Pathway_vector ,"h_secTrk_Pathlength_UpstreamCap_Material; [cm^2/g];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Distance_to_downstreamCap_UpstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Distance_to_downstreamCap_UpstreamCap_Material", Distance_to_Caps ,"h_Distance_to_downstreamCap_UpstreamCap_Material; [cm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Distance_to_upstreamCap_UpstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Distance_to_upstreamCap_UpstreamCap_Material", Distance_to_Caps ,"h_Distance_to_upstreamCap_UpstreamCap_Material; [cm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Distance_to_downstreamCap_RCut_UpstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Distance_to_downstreamCap_RCut_UpstreamCap_Material", Distance_to_Caps ,"h_Distance_to_downstreamCap_RCut_UpstreamCap_Material; [cm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Distance_to_upstreamCap_RCut_UpstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Distance_to_upstreamCap_RCut_UpstreamCap_Material", Distance_to_Caps ,"h_Distance_to_upstreamCap_RCut_UpstreamCap_Material; [cm];Events");


PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Distance_to_InnerTank_Caps_UpstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Distance_to_InnerTank_Caps_UpstreamCap_Material",  Distance_to_innerTank  ,"h_Distance_to_InnerTank_Caps_UpstreamCap_Material");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Distance_to_InnerTank_Barrel_UpstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Distance_to_InnerTank_Barrel_UpstreamCap_Material",  Distance_to_innerTank  ,"h_Distance_to_InnerTank_Barrel_UpstreamCap_Material");

//////////////


PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType> h_CryoVertex_Z_TrackType =
PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType>(TrackType_Category, "h_CryoVertex_Z_TrackType", Vertex_Zbin_vector ,"h_CryoVertex_Z_TrackType; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions> h_CryoVertex_Z_vertex =
PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions>(VertexOptions_Category, "h_CryoVertex_Z_vertex", Vertex_Zbin_vector ,"h_CryoVertex_Z_vertex; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack> h_CryoVertex_Z_Ntracks =
PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack>(boolNTrack_Category, "h_CryoVertex_Z_Ntracks", Vertex_Zbin_vector ,"h_CryoVertex_Z_Ntracks; [mm];Events");


//new

PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType> h_CryoVertex_Z_UpstreamCap_TrackType =
PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType>(TrackType_Category, "h_CryoVertex_Z_UpstreamCap_TrackType", Vertex_Zbin_vector ,"h_CryoVertex_Z_UpstreamCap_TrackType; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType> h_CryoVertex_X_UpstreamCap_TrackType =
PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType>(TrackType_Category, "h_CryoVertex_X_UpstreamCap_TrackType", Vertex_Xbin_vector ,"h_CryoVertex_X_UpstreamCap_TrackType; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType> h_CryoVertex_Y_UpstreamCap_TrackType =
PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType>(TrackType_Category, "h_CryoVertex_Y_UpstreamCap_TrackType", Vertex_Ybin_vector ,"h_CryoVertex_Y_UpstreamCap_TrackType; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType> h_CryoVertex_R_UpstreamCap_TrackType =
PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType>(TrackType_Category, "h_CryoVertex_R_UpstreamCap_TrackType", Vertex_Rbin_vector ,"h_CryoVertex_R_UpstreamCap_TrackType; [mm];Events");


PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions> h_CryoVertex_Z_UpstreamCap_vertex =
PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions>(VertexOptions_Category, "h_CryoVertex_Z_UpstreamCap_vertex", Vertex_Zbin_vector ,"h_CryoVertex_Z_UpstreamCap_vertex; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions> h_CryoVertex_X_UpstreamCap_vertex =
PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions>(VertexOptions_Category, "h_CryoVertex_X_UpstreamCap_vertex", Vertex_Xbin_vector ,"h_CryoVertex_X_UpstreamCap_vertex; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions> h_CryoVertex_Y_UpstreamCap_vertex =
PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions>(VertexOptions_Category, "h_CryoVertex_Y_UpstreamCap_vertex", Vertex_Ybin_vector ,"h_CryoVertex_Y_UpstreamCap_vertex; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions> h_CryoVertex_R_UpstreamCap_vertex =
PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions>(VertexOptions_Category, "h_CryoVertex_R_UpstreamCap_vertex", Vertex_Rbin_vector ,"h_CryoVertex_R_UpstreamCap_vertex; [mm];Events");

////


PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack> h_CryoVertex_Z_UpstreamCap_Ntracks =
PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack>(boolNTrack_Category, "h_CryoVertex_Z_UpstreamCap_Ntracks", Vertex_Zbin_vector ,"h_CryoVertex_Z_UpstreamCap_Ntracks; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack> h_CryoVertex_X_UpstreamCap_Ntracks =
PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack>(boolNTrack_Category, "h_CryoVertex_X_UpstreamCap_Ntracks", Vertex_Xbin_vector ,"h_CryoVertex_X_UpstreamCap_Ntracks; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack> h_CryoVertex_Y_UpstreamCap_Ntracks =
PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack>(boolNTrack_Category, "h_CryoVertex_Y_UpstreamCap_Ntracks", Vertex_Ybin_vector ,"h_CryoVertex_Y_UpstreamCap_Ntracks; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack> h_CryoVertex_R_UpstreamCap_Ntracks =
PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack>(boolNTrack_Category, "h_CryoVertex_R_UpstreamCap_Ntracks", Vertex_Rbin_vector ,"h_CryoVertex_R_UpstreamCap_Ntracks; [mm];Events");



///////////////////////////////////////////////////////////////////////////////
///Barrel Region
///////////////////////////////////////////////////////////////////////////////

PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE_Barrel("h_MuonE_Barrel", "Muon_{E}", Ebin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPZ_Barrel("h_MuonPZ_Barrel", "Muon_{PZ}",  Pzbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPT_Barrel("h_MuonPT_Barrel", "Muon_{PT}",  PTbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonTheta_Barrel("h_MuonTheta_Barrel", "#theta_{#mu} NEW Method",  MuonThetabin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_Barrel("h_CryoVertex_X_Barrel", "Vertex X",  Vertex_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_Barrel("h_CryoVertex_Y_Barrel", "Vertex Y",  Vertex_Ybin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_Barrel("h_CryoVertex_R_Barrel", "Vertex R",  Vertex_Rbin_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_RCut_Barrel("h_CryoVertex_X_RCut_Barrel", "Vertex X",  Vertex_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_RCut_Barrel("h_CryoVertex_Y_RCut_Barrel", "Vertex Y",  Vertex_Ybin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_RCut_Barrel("h_CryoVertex_R_RCut_Barrel", "Vertex R",  Vertex_Rbin_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_Barrel("h_CryoVertex_Z_Barrel", "Vertex Z",  Vertex_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_RCut_Barrel("h_CryoVertex_Z_RCut_Barrel", "Vertex Z",  Vertex_Zbin_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_InnerTank_Barrel("h_Distance_to_InnerTank_Barrel", "h_Distance_to_InnerTank_Barrel",  Distance_to_innerTank, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonDOCA_Barrel("h_MuonDOCA_Barrel", "Muon_DOCA",  Vertex_DOCAbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_DOCA_Barrel("h_secTrk_DOCA_Barrel", "h_secTrk DOCA",  secTrk_DOCA_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Pathlength_Barrel("h_secTrk_Pathlength_Barrel", "h_secTrk Pathlength ",  secTrk_Pathway_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_tracklength_Barrel("h_secTrk_tracklength_Barrel", "Recoil track length  [cm] ", Recoil_track_length_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_downstreamCap_Barrel("h_Distance_to_downstreamCap_Barrel", "h_Distance_to_downstreamCap_Barrel",  Distance_to_Caps, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_upstreamCap_Barrel(  "h_Distance_to_upstreamCap_Barrel",   "h_Distance_to_upstreamCap_Barrel",    Distance_to_Caps, error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_downstreamCap_RCut_Barrel("h_Distance_to_downstreamCap_RCut_Barrel", "h_Distance_to_downstreamCap_RCut_Barrel",  Distance_to_Caps, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_upstreamCap_RCut_Barrel(  "h_Distance_to_upstreamCap_RCut_Barrel",   "h_Distance_to_upstreamCap_RCut_Barrel",    Distance_to_Caps, error_bands);


PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonE_Barrel_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonE_Barrel_Material", Ebin_vector ,"MuonE_Barrel_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonPZ_Barrel_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonPZ_Barrel_Material", Pzbin_vector ,"h_MuonPZ_Barrel_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonPT_Barrel_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonPT_Barrel_Material", PTbin_vector ,"h_MuonPT_Barrel_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonTheta_Barrel_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonTheta_Barrel_Material", MuonThetabin_vector ,"h_MuonTheta_Barrel_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_X_Barrel_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_X_Barrel_Material", Vertex_Xbin_vector ,"h_CryoVertex_X_Barrel_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Y_Barrel_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Y_Barrel_Material", Vertex_Ybin_vector ,"h_CryoVertex_Y_Barrel_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_R_Barrel_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_R_Barrel_Material", Vertex_Rbin_vector ,"h_CryoVertex_R_Barrel_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_X_RCut_Barrel_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_X_RCut_Barrel_Material", Vertex_Xbin_vector ,"h_CryoVertex_X_RCut_Barrel_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Y_RCut_Barrel_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Y_RCut_Barrel_Material", Vertex_Ybin_vector ,"h_CryoVertex_Y_RCut_Barrel_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_R_RCut_Barrel_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_R_RCut_Barrel_Material", Vertex_Rbin_vector ,"h_CryoVertex_R_RCut_Barrel_Material; [mm];Events");


PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Z_Barrel_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Z_Barrel_Material", Vertex_Zbin_vector ,"h_CryoVertex_Z_Barrel_Material; [mm];Events");


PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Z_RCut_Barrel_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Z_RCut_Barrel_Material", Vertex_Zbin_vector ,"h_CryoVertex_Z_RCut_Barrel_Material; [mm];Events");



PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Distance_to_InnerTank_Barrel_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Distance_to_InnerTank_Barrel_Material",  Distance_to_innerTank  ,"h_Distance_to_InnerTank_Barrel_Material");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Distance_to_InnerTank_Caps_Barrel_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Distance_to_InnerTank_Caps_Barrel_Material",  Distance_to_innerTank  ,"h_Distance_to_InnerTank_Caps_Barrel_Material");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Distance_to_InnerTank_Barrel_Barrel_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Distance_to_InnerTank_Barrel_Barrel_Material",  Distance_to_innerTank  ,"h_Distance_to_InnerTank_Barrel_Barrel_Material");



PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_DOCA_Barrel_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_DOCA_Barrel_Material", secTrk_DOCA_vector ,"h_secTrk_DOCA_Barrel_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonDOCA_Barrel_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonDOCA_Barrel_Material", Vertex_DOCAbin_vector ,"h_MuonDOCA_Barrel_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_tracklength_Barrel_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_tracklength_Barrel_Material", Recoil_track_length_vector ,"h_secTrk_tracklength_Barrel_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_Pathlength_Barrel_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_Pathlength_Barrel_Material", secTrk_Pathway_vector ,"h_secTrk_Pathlength_Barrel_Material; [cm^2/g];Events");


PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Distance_to_downstreamCap_Barrel_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Distance_to_downstreamCap_Barrel_Material", Distance_to_Caps ,"h_Distance_to_downstreamCap_Barrel_Material; [cm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Distance_to_upstreamCap_Barrel_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Distance_to_upstreamCap_Barrel_Material", Distance_to_Caps ,"h_Distance_to_upstreamCap_Barrel_Material; [cm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Distance_to_downstreamCap_RCut_Barrel_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Distance_to_downstreamCap_RCut_Barrel_Material", Distance_to_Caps ,"h_Distance_to_downstreamCap_RCut_Barrel_Material; [cm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Distance_to_upstreamCap_RCut_Barrel_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Distance_to_upstreamCap_RCut_Barrel_Material", Distance_to_Caps ,"h_Distance_to_upstreamCap_RCut_Barrel_Material; [cm];Events");


PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType> h_CryoVertex_Z_Barrel_TrackType =
PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType>(TrackType_Category, "h_CryoVertex_Z_Barrel_TrackType", Vertex_Zbin_vector ,"h_CryoVertex_Z_Barrel_TrackType; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType> h_CryoVertex_X_Barrel_TrackType =
PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType>(TrackType_Category, "h_CryoVertex_X_Barrel_TrackType", Vertex_Xbin_vector ,"h_CryoVertex_X_Barrel_TrackType; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType> h_CryoVertex_Y_Barrel_TrackType =
PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType>(TrackType_Category, "h_CryoVertex_Y_Barrel_TrackType", Vertex_Ybin_vector ,"h_CryoVertex_Y_Barrel_TrackType; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType> h_CryoVertex_R_Barrel_TrackType =
PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType>(TrackType_Category, "h_CryoVertex_R_Barrel_TrackType", Vertex_Rbin_vector ,"h_CryoVertex_R_Barrel_TrackType; [mm];Events");


PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions> h_CryoVertex_Z_Barrel_vertex =
PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions>(VertexOptions_Category, "h_CryoVertex_Z_Barrel_vertex", Vertex_Zbin_vector ,"h_CryoVertex_Z_Barrel_vertex; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions> h_CryoVertex_X_Barrel_vertex =
PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions>(VertexOptions_Category, "h_CryoVertex_X_Barrel_vertex", Vertex_Xbin_vector ,"h_CryoVertex_X_Barrel_vertex; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions> h_CryoVertex_Y_Barrel_vertex =
PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions>(VertexOptions_Category, "h_CryoVertex_Y_Barrel_vertex", Vertex_Ybin_vector ,"h_CryoVertex_Y_Barrel_vertex; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions> h_CryoVertex_R_Barrel_vertex =
PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions>(VertexOptions_Category, "h_CryoVertex_R_Barrel_vertex", Vertex_Rbin_vector ,"h_CryoVertex_R_Barrel_vertex; [mm];Events");

////


PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack> h_CryoVertex_Z_Barrel_Ntracks =
PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack>(boolNTrack_Category, "h_CryoVertex_Z_Barrel_Ntracks", Vertex_Zbin_vector ,"h_CryoVertex_Z_Barrel_Ntracks; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack> h_CryoVertex_X_Barrel_Ntracks =
PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack>(boolNTrack_Category, "h_CryoVertex_X_Barrel_Ntracks", Vertex_Xbin_vector ,"h_CryoVertex_X_Barrel_Ntracks; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack> h_CryoVertex_Y_Barrel_Ntracks =
PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack>(boolNTrack_Category, "h_CryoVertex_Y_Barrel_Ntracks", Vertex_Ybin_vector ,"h_CryoVertex_Y_Barrel_Ntracks; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack> h_CryoVertex_R_Barrel_Ntracks =
PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack>(boolNTrack_Category, "h_CryoVertex_R_Barrel_Ntracks", Vertex_Rbin_vector ,"h_CryoVertex_R_Barrel_Ntracks; [mm];Events");



///////////////////////////////////////////////////////////////////////////////
///DownStream Cap Region
///////////////////////////////////////////////////////////////////////////////

PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE_DownstreamCap("h_MuonE_DownstreamCap", "Muon_{E}", Ebin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPZ_DownstreamCap("h_MuonPZ_DownstreamCap", "Muon_{PZ}",  Pzbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPT_DownstreamCap("h_MuonPT_DownstreamCap", "Muon_{PT}",  PTbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonTheta_DownstreamCap("h_MuonTheta_DownstreamCap", "#theta_{#mu} NEW Method",  MuonThetabin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_DownstreamCap("h_CryoVertex_X_DownstreamCap", "Vertex X",  Vertex_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_DownstreamCap("h_CryoVertex_Y_DownstreamCap", "Vertex Y",  Vertex_Ybin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_DownstreamCap("h_CryoVertex_R_DownstreamCap", "Vertex R",  Vertex_Rbin_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_RCut_DownstreamCap("h_CryoVertex_X_RCut_DownstreamCap", "Vertex X",  Vertex_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_RCut_DownstreamCap("h_CryoVertex_Y_RCut_DownstreamCap", "Vertex Y",  Vertex_Ybin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_RCut_DownstreamCap("h_CryoVertex_R_RCut_DownstreamCap", "Vertex R",  Vertex_Rbin_vector , error_bands);


PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_DownstreamCap("h_CryoVertex_Z_DownstreamCap", "Vertex Z",  Vertex_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_RCut_DownstreamCap("h_CryoVertex_Z_RCut_DownstreamCap", "Vertex Z",  Vertex_Zbin_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_InnerTank_DownstreamCap("h_Distance_to_InnerTank_DownstreamCap", "h_Distance_to_InnerTank",  Distance_to_innerTank, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonDOCA_DownstreamCap("h_MuonDOCA_DownstreamCap", "Muon_DOCA",  Vertex_DOCAbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_DOCA_DownstreamCap("h_secTrk_DOCA_DownstreamCap", "h_secTrk DOCA",  secTrk_DOCA_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Pathlength_DownstreamCap("h_secTrk_Pathlength_DownstreamCap", "h_secTrk Pathlength ",  secTrk_Pathway_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_tracklength_DownstreamCap("h_secTrk_tracklength_DownstreamCap", "Recoil track length  [cm] ", Recoil_track_length_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_downstreamCap_DownstreamCap("h_Distance_to_downstreamCap_DownstreamCap", "h_Distance_to_downstreamCap_DownstreamCap",  Distance_to_Caps, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_upstreamCap_DownstreamCap(  "h_Distance_to_upstreamCap_DownstreamCap",   "h_Distance_to_upstreamCap_DownstreamCap",    Distance_to_Caps, error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_downstreamCap_RCut_DownstreamCap("h_Distance_to_downstreamCap_RCut_DownstreamCap", "h_Distance_to_downstreamCap_RCut_DownstreamCap",  Distance_to_Caps, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_upstreamCap_RCut_DownstreamCap(  "h_Distance_to_upstreamCap_RCut_DownstreamCap",   "h_Distance_to_upstreamCap_RCut_DownstreamCap",    Distance_to_Caps, error_bands);



PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonE_DownstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonE_DownstreamCap_Material", Ebin_vector ,"MuonE_DownstreamCap_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonPZ_DownstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonPZ_DownstreamCap_Material", Pzbin_vector ,"h_MuonPZ_DownstreamCap_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonPT_DownstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonPT_DownstreamCap_Material", PTbin_vector ,"h_MuonPT_DownstreamCap_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonTheta_DownstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonTheta_DownstreamCap_Material", MuonThetabin_vector ,"h_MuonTheta_DownstreamCap_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_X_DownstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_X_DownstreamCap_Material", Vertex_Xbin_vector ,"h_CryoVertex_X_DownstreamCap_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Y_DownstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Y_DownstreamCap_Material", Vertex_Ybin_vector ,"h_CryoVertex_Y_DownstreamCap_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_R_DownstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_R_DownstreamCap_Material", Vertex_Rbin_vector ,"h_CryoVertex_R_DownstreamCap_Material; [mm];Events");


PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_X_RCut_DownstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_X_RCut_DownstreamCap_Material", Vertex_Xbin_vector ,"h_CryoVertex_X_RCut_DownstreamCap_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Y_RCut_DownstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Y_RCut_DownstreamCap_Material", Vertex_Ybin_vector ,"h_CryoVertex_Y_RCut_DownstreamCap_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_R_RCut_DownstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_R_RCut_DownstreamCap_Material", Vertex_Rbin_vector ,"h_CryoVertex_R_RCut_DownstreamCap_Material; [mm];Events");


PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Z_DownstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Z_DownstreamCap_Material", Vertex_Zbin_vector ,"h_CryoVertex_Z_DownstreamCap_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Z_RCut_DownstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Z_RCut_DownstreamCap_Material", Vertex_Zbin_vector ,"h_CryoVertex_Z_RCut_DownstreamCap_Material; [mm];Events");



PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Distance_to_InnerTank_DownstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Distance_to_InnerTank_DownstreamCap_Material",  Distance_to_innerTank  ,"h_Distance_to_InnerTank_DownstreamCap_Material");


PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Distance_to_InnerTank_Caps_DownstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Distance_to_InnerTank_Caps_DownstreamCap_Material",  Distance_to_innerTank  ,"h_Distance_to_InnerTank_Caps_DownstreamCap_Material");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Distance_to_InnerTank_Barrel_DownstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Distance_to_InnerTank_Barrel_DownstreamCap_Material",  Distance_to_innerTank  ,"h_Distance_to_InnerTank_Barrel_DownstreamCap_Material");



PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_DOCA_DownstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_DOCA_DownstreamCap_Material", secTrk_DOCA_vector ,"h_secTrk_DOCA_DownstreamCap_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonDOCA_DownstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonDOCA_DownstreamCap_Material", Vertex_DOCAbin_vector ,"h_MuonDOCA_DownstreamCap_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_tracklength_DownstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_tracklength_DownstreamCap_Material", Recoil_track_length_vector ,"h_secTrk_tracklength_DownstreamCap_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_Pathlength_DownstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_Pathlength_DownstreamCap_Material", secTrk_Pathway_vector ,"h_secTrk_Pathlength_DownstreamCap_Material; [cm^2/g];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Distance_to_downstreamCap_DownstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Distance_to_downstreamCap_DownstreamCap_Material", Distance_to_Caps ,"h_Distance_to_downstreamCap_DownstreamCap_Material; [cm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Distance_to_upstreamCap_DownstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Distance_to_upstreamCap_DownstreamCap_Material", Distance_to_Caps ,"h_Distance_to_upstreamCap_DownstreamCap_Material; [cm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Distance_to_downstreamCap_RCut_DownstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Distance_to_downstreamCap_RCut_DownstreamCap_Material", Distance_to_Caps ,"h_Distance_to_downstreamCap__RCutDownstreamCap_Material; [cm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Distance_to_upstreamCap_RCut_DownstreamCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Distance_to_upstreamCap_RCut_DownstreamCap_Material", Distance_to_Caps ,"h_Distance_to_upstreamCap_RCut_DownstreamCap_Material; [cm];Events");


PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType> h_CryoVertex_Z_DownstreamCap_TrackType =
PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType>(TrackType_Category, "h_CryoVertex_Z_DownstreamCap_TrackType", Vertex_Zbin_vector ,"h_CryoVertex_Z_DownstreamCap_TrackType; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType> h_CryoVertex_X_DownstreamCap_TrackType =
PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType>(TrackType_Category, "h_CryoVertex_X_DownstreamCap_TrackType", Vertex_Xbin_vector ,"h_CryoVertex_X_DownstreamCap_TrackType; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType> h_CryoVertex_Y_DownstreamCap_TrackType =
PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType>(TrackType_Category, "h_CryoVertex_Y_DownstreamCap_TrackType", Vertex_Ybin_vector ,"h_CryoVertex_Y_DownstreamCap_TrackType; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType> h_CryoVertex_R_DownstreamCap_TrackType =
PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType>(TrackType_Category, "h_CryoVertex_R_DownstreamCap_TrackType", Vertex_Rbin_vector ,"h_CryoVertex_R_DownstreamCap_TrackType; [mm];Events");


PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions> h_CryoVertex_Z_DownstreamCap_vertex =
PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions>(VertexOptions_Category, "h_CryoVertex_Z_DownstreamCap_vertex", Vertex_Zbin_vector ,"h_CryoVertex_Z_DownstreamCap_vertex; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions> h_CryoVertex_X_DownstreamCap_vertex =
PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions>(VertexOptions_Category, "h_CryoVertex_X_DownstreamCap_vertex", Vertex_Xbin_vector ,"h_CryoVertex_X_DownstreamCap_vertex; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions> h_CryoVertex_Y_DownstreamCap_vertex =
PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions>(VertexOptions_Category, "h_CryoVertex_Y_DownstreamCap_vertex", Vertex_Ybin_vector ,"h_CryoVertex_Y_DownstreamCap_vertex; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions> h_CryoVertex_R_DownstreamCap_vertex =
PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions>(VertexOptions_Category, "h_CryoVertex_R_DownstreamCap_vertex", Vertex_Rbin_vector ,"h_CryoVertex_R_DownstreamCap_vertex; [mm];Events");

////


PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack> h_CryoVertex_Z_DownstreamCap_Ntracks =
PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack>(boolNTrack_Category, "h_CryoVertex_Z_DownstreamCap_Ntracks", Vertex_Zbin_vector ,"h_CryoVertex_Z_DownstreamCap_Ntracks; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack> h_CryoVertex_X_DownstreamCap_Ntracks =
PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack>(boolNTrack_Category, "h_CryoVertex_X_DownstreamCap_Ntracks", Vertex_Xbin_vector ,"h_CryoVertex_X_DownstreamCap_Ntracks; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack> h_CryoVertex_Y_DownstreamCap_Ntracks =
PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack>(boolNTrack_Category, "h_CryoVertex_Y_DownstreamCap_Ntracks", Vertex_Ybin_vector ,"h_CryoVertex_Y_DownstreamCap_Ntracks; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack> h_CryoVertex_R_DownstreamCap_Ntracks =
PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack>(boolNTrack_Category, "h_CryoVertex_R_DownstreamCap_Ntracks", Vertex_Rbin_vector ,"h_CryoVertex_R_DownstreamCap_Ntracks; [mm];Events");





////////////////////////////////////////////////////////////////////////////////
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE_Downstream_ConcaveCap("h_MuonE_Downstream_ConcaveCap", "Muon_{E}", Ebin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPZ_Downstream_ConcaveCap("h_MuonPZ_Downstream_ConcaveCap", "Muon_{PZ}",  Pzbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPT_Downstream_ConcaveCap("h_MuonPT_Downstream_ConcaveCap", "Muon_{PT}",  PTbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonTheta_Downstream_ConcaveCap("h_MuonTheta_Downstream_ConcaveCap", "#theta_{#mu} ",  MuonThetabin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_Downstream_ConcaveCap("h_CryoVertex_X_Downstream_ConcaveCap", "Vertex X",  Vertex_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_Downstream_ConcaveCap("h_CryoVertex_Y_Downstream_ConcaveCap", "Vertex Y",  Vertex_Ybin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_Downstream_ConcaveCap("h_CryoVertex_R_Downstream_ConcaveCap", "Vertex R",  Vertex_Rbin_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_RCut_Downstream_ConcaveCap("h_CryoVertex_X_RCut_Downstream_ConcaveCap", "Vertex X",  Vertex_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_RCut_Downstream_ConcaveCap("h_CryoVertex_Y_RCut_Downstream_ConcaveCap", "Vertex Y",  Vertex_Ybin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_RCut_Downstream_ConcaveCap("h_CryoVertex_R_RCut_Downstream_ConcaveCap", "Vertex R",  Vertex_Rbin_vector , error_bands);


PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_Downstream_ConcaveCap("h_CryoVertex_Z_Downstream_ConcaveCap", "Vertex Z",  Vertex_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_RCut_Downstream_ConcaveCap("h_CryoVertex_Z_RCut_Downstream_ConcaveCap", "Vertex Z",  Vertex_Zbin_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_InnerTank_Downstream_ConcaveCap("h_Distance_to_InnerTank_Downstream_ConcaveCap", "h_Distance_to_InnerTank",  Distance_to_innerTank, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonDOCA_Downstream_ConcaveCap("h_MuonDOCA_Downstream_ConcaveCap", "Muon_DOCA",  Vertex_DOCAbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_DOCA_Downstream_ConcaveCap("h_secTrk_DOCA_Downstream_ConcaveCap", "h_secTrk DOCA",  secTrk_DOCA_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Pathlength_Downstream_ConcaveCap("h_secTrk_Pathlength_Downstream_ConcaveCap", "h_secTrk Pathlength ",  secTrk_Pathway_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_tracklength_Downstream_ConcaveCap("h_secTrk_tracklength_Downstream_ConcaveCap", "Recoil track length  [cm] ", Recoil_track_length_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_downstreamCap_Downstream_ConcaveCap("h_Distance_to_downstreamCap_Downstream_ConcaveCap", "h_Distance_to_downstreamCap_Downstream_ConcaveCap",  Distance_to_Caps, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_upstreamCap_Downstream_ConcaveCap(  "h_Distance_to_upstreamCap_Downstream_ConcaveCap",   "h_Distance_to_upstreamCap_Downstream_ConcaveCap",    Distance_to_Caps, error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_downstreamCap_RCut_Downstream_ConcaveCap("h_Distance_to_downstreamCap_RCut_Downstream_ConcaveCap", "h_Distance_to_downstreamCap_Downstream_ConcaveCap",  Distance_to_Caps, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Distance_to_upstreamCap_RCut_Downstream_ConcaveCap(  "h_Distance_to_upstreamCap_RCut_Downstream_ConcaveCap",   "h_Distance_to_upstreamCap_Downstream_ConcaveCap",    Distance_to_Caps, error_bands);



PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonE_Downstream_ConcaveCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonE_Downstream_ConcaveCap_Material", Ebin_vector ,"MuonE_Downstream_ConcaveCap_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonPZ_Downstream_ConcaveCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonPZ_Downstream_ConcaveCap_Material", Pzbin_vector ,"h_MuonPZ_Downstream_ConcaveCap_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonPT_Downstream_ConcaveCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonPT_Downstream_ConcaveCap_Material", PTbin_vector ,"h_MuonPT_Downstream_ConcaveCap_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonTheta_Downstream_ConcaveCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonTheta_Downstream_ConcaveCap_Material", MuonThetabin_vector ,"h_MuonTheta_Downstream_ConcaveCap_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_X_Downstream_ConcaveCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_X_Downstream_ConcaveCap_Material", Vertex_Xbin_vector ,"h_CryoVertex_X_Downstream_ConcaveCap_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Y_Downstream_ConcaveCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Y_Downstream_ConcaveCap_Material", Vertex_Ybin_vector ,"h_CryoVertex_Y_Downstream_ConcaveCap_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_R_Downstream_ConcaveCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_R_Downstream_ConcaveCap_Material", Vertex_Rbin_vector ,"h_CryoVertex_R_Downstream_ConcaveCap_Material; [mm];Events");


PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_X_RCut_Downstream_ConcaveCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_X_RCut_Downstream_ConcaveCap_Material", Vertex_Xbin_vector ,"h_CryoVertex_X_RCut_Downstream_ConcaveCap_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Y_RCut_Downstream_ConcaveCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Y_RCut_Downstream_ConcaveCap_Material", Vertex_Ybin_vector ,"h_CryoVertex_Y_RCut_Downstream_ConcaveCap_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_R_RCut_Downstream_ConcaveCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_R_RCut_Downstream_ConcaveCap_Material", Vertex_Rbin_vector ,"h_CryoVertex_R_RCut_Downstream_ConcaveCap_Material; [mm];Events");



PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Z_Downstream_ConcaveCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Z_Downstream_ConcaveCap_Material", Vertex_Zbin_vector ,"h_CryoVertex_Z_Downstream_ConcaveCap_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Z_RCut_Downstream_ConcaveCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Z_RCut_Downstream_ConcaveCap_Material", Vertex_Zbin_vector ,"h_CryoVertex_Z_RCut_Downstream_ConcaveCap_Material; [mm];Events");



PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Distance_to_InnerTank_Downstream_ConcaveCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Distance_to_InnerTank_Downstream_ConcaveCap_Material",  Distance_to_innerTank  ,"h_Distance_to_InnerTank_Downstream_ConcaveCap_Material");


PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Distance_to_InnerTank_Caps_Downstream_ConcaveCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Distance_to_InnerTank_Caps_Downstream_ConcaveCap_Material",  Distance_to_innerTank  ,"h_Distance_to_InnerTank_Caps_Downstream_ConcaveCap_Material");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Distance_to_InnerTank_Barrel_Downstream_ConcaveCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Distance_to_InnerTank_Barrel_Downstream_ConcaveCap_Material",  Distance_to_innerTank  ,"h_Distance_to_InnerTank_Barrel_Downstream_ConcaveCap_Material");


PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_DOCA_Downstream_ConcaveCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_DOCA_Downstream_ConcaveCap_Material", secTrk_DOCA_vector ,"h_secTrk_DOCA_Downstream_ConcaveCap_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonDOCA_Downstream_ConcaveCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonDOCA_Downstream_ConcaveCap_Material", Vertex_DOCAbin_vector ,"h_MuonDOCA_Downstream_ConcaveCap_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_tracklength_Downstream_ConcaveCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_tracklength_Downstream_ConcaveCap_Material", Recoil_track_length_vector ,"h_secTrk_tracklength_Downstream_ConcaveCap_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_Pathlength_Downstream_ConcaveCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_Pathlength_Downstream_ConcaveCap_Material", secTrk_Pathway_vector ,"h_secTrk_Pathlength_Downstream_ConcaveCap_Material; [cm^2/g];Events");


PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Distance_to_downstreamCap_Downstream_ConcaveCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Distance_to_downstreamCap_Downstream_ConcaveCap_Material", Distance_to_Caps ,"h_Distance_to_downstreamCap_Downstream_ConcaveCap_Material; [cm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Distance_to_upstreamCap_Downstream_ConcaveCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Distance_to_upstreamCap_Downstream_ConcaveCap_Material", Distance_to_Caps ,"h_Distance_to_upstreamCap_Downstream_ConcaveCap_Material; [cm];Events");


PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Distance_to_downstreamCap_RCut_Downstream_ConcaveCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Distance_to_downstreamCap_RCut_Downstream_ConcaveCap_Material", Distance_to_Caps ,"h_Distance_to_downstreamCap_RCut_Downstream_ConcaveCap_Material; [cm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Distance_to_upstreamCap_RCut_Downstream_ConcaveCap_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Distance_to_upstreamCap_RCut_Downstream_ConcaveCap_Material", Distance_to_Caps ,"h_Distance_to_upstreamCap_RCut_Downstream_ConcaveCap_Material; [cm];Events");


PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType> h_CryoVertex_Z_Downstream_ConcaveCap_TrackType =
PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType>(TrackType_Category, "h_CryoVertex_Z_Downstream_ConcaveCap_TrackType", Vertex_Zbin_vector ,"h_CryoVertex_Z_Downstream_ConcaveCap_TrackType; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType> h_CryoVertex_X_Downstream_ConcaveCap_TrackType =
PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType>(TrackType_Category, "h_CryoVertex_X_Downstream_ConcaveCap_TrackType", Vertex_Xbin_vector ,"h_CryoVertex_X_Downstream_ConcaveCap_TrackType; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType> h_CryoVertex_Y_Downstream_ConcaveCap_TrackType =
PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType>(TrackType_Category, "h_CryoVertex_Y_Downstream_ConcaveCap_TrackType", Vertex_Ybin_vector ,"h_CryoVertex_Y_Downstream_ConcaveCap_TrackType; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType> h_CryoVertex_R_Downstream_ConcaveCap_TrackType =
PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType>(TrackType_Category, "h_CryoVertex_R_Downstream_ConcaveCap_TrackType", Vertex_Rbin_vector ,"h_CryoVertex_R_Downstream_ConcaveCap_TrackType; [mm];Events");


PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions> h_CryoVertex_Z_Downstream_ConcaveCap_vertex =
PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions>(VertexOptions_Category, "h_CryoVertex_Z_Downstream_ConcaveCap_vertex", Vertex_Zbin_vector ,"h_CryoVertex_Z_Downstream_ConcaveCap_vertex; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions> h_CryoVertex_X_Downstream_ConcaveCap_vertex =
PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions>(VertexOptions_Category, "h_CryoVertex_X_Downstream_ConcaveCap_vertex", Vertex_Xbin_vector ,"h_CryoVertex_X_Downstream_ConcaveCap_vertex; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions> h_CryoVertex_Y_Downstream_ConcaveCap_vertex =
PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions>(VertexOptions_Category, "h_CryoVertex_Y_Downstream_ConcaveCap_vertex", Vertex_Ybin_vector ,"h_CryoVertex_Y_Downstream_ConcaveCap_vertex; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions> h_CryoVertex_R_Downstream_ConcaveCap_vertex =
PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions>(VertexOptions_Category, "h_CryoVertex_R_Downstream_ConcaveCap_vertex", Vertex_Rbin_vector ,"h_CryoVertex_R_Downstream_ConcaveCap_vertex; [mm];Events");

////


PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack> h_CryoVertex_Z_Downstream_ConcaveCap_Ntracks =
PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack>(boolNTrack_Category, "h_CryoVertex_Z_Downstream_ConcaveCap_Ntracks", Vertex_Zbin_vector ,"h_CryoVertex_Z_Downstream_ConcaveCap_Ntracks; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack> h_CryoVertex_X_Downstream_ConcaveCap_Ntracks =
PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack>(boolNTrack_Category, "h_CryoVertex_X_Downstream_ConcaveCap_Ntracks", Vertex_Xbin_vector ,"h_CryoVertex_X_Downstream_ConcaveCap_Ntracks; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack> h_CryoVertex_Y_Downstream_ConcaveCap_Ntracks =
PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack>(boolNTrack_Category, "h_CryoVertex_Y_Downstream_ConcaveCap_Ntracks", Vertex_Ybin_vector ,"h_CryoVertex_Y_Downstream_ConcaveCap_Ntracks; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack> h_CryoVertex_R_Downstream_ConcaveCap_Ntracks =
PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack>(boolNTrack_Category, "h_CryoVertex_R_Downstream_ConcaveCap_Ntracks", Vertex_Rbin_vector ,"h_CryoVertex_R_Downstream_ConcaveCap_Ntracks; [mm];Events");




////////////////
//Vertex Hist///
////////////////
MnvH2D *h_Mig_Vertex_X      =   new MnvH2D("h_Mig_Vertex_X",     "h_Mig_Vertex_X",  Vertex_Xbin_vector.size()-1, Vertex_Xbin_vector.data(), Vertex_Xbin_vector.size()-1, Vertex_Xbin_vector.data());
MnvH2D *h_Mig_Vertex_Y      =   new MnvH2D("h_Mig_Vertex_Y",     "h_Mig_Vertex_Y",  Vertex_Ybin_vector.size()-1, Vertex_Ybin_vector.data(), Vertex_Ybin_vector.size()-1, Vertex_Ybin_vector.data());
MnvH2D *h_Mig_Vertex_R      =   new MnvH2D("h_Mig_Vertex_R",     "h_Mig_Vertex_R",  Vertex_Rbin_vector.size()-1, Vertex_Rbin_vector.data(), Vertex_Rbin_vector.size()-1, Vertex_Rbin_vector.data());
MnvH2D *h_Mig_Vertex_Z      =   new MnvH2D("h_Mig_Vertex_Z",     "h_Mig_Vertex_Z",  Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data(), Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());


MnvH2D *h_Mig_Vertex_X_UpstreamCap      =   new MnvH2D("h_Mig_Vertex_X_UpstreamCap",     "h_Mig_Vertex_X_UpstreamCap",  Vertex_Xbin_vector.size()-1, Vertex_Xbin_vector.data(), Vertex_Xbin_vector.size()-1, Vertex_Xbin_vector.data());
MnvH2D *h_Mig_Vertex_Y_UpstreamCap      =   new MnvH2D("h_Mig_Vertex_Y_UpstreamCap",     "h_Mig_Vertex_Y_UpstreamCap",  Vertex_Ybin_vector.size()-1, Vertex_Ybin_vector.data(), Vertex_Ybin_vector.size()-1, Vertex_Ybin_vector.data());
MnvH2D *h_Mig_Vertex_R_UpstreamCap      =   new MnvH2D("h_Mig_Vertex_R_UpstreamCap",     "h_Mig_Vertex_R_UpstreamCap",  Vertex_Rbin_vector.size()-1, Vertex_Rbin_vector.data(), Vertex_Rbin_vector.size()-1, Vertex_Rbin_vector.data());
MnvH2D *h_Mig_Vertex_Z_UpstreamCap      =   new MnvH2D("h_Mig_Vertex_Z_UpstreamCap",     "h_Mig_Vertex_Z_UpstreamCap",  Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data(), Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());

MnvH2D *h_Mig_Vertex_X_Barrel      =   new MnvH2D("h_Mig_Vertex_X_Barrel",     "h_Mig_Vertex_X_Barrel",  Vertex_Xbin_vector.size()-1, Vertex_Xbin_vector.data(), Vertex_Xbin_vector.size()-1, Vertex_Xbin_vector.data());
MnvH2D *h_Mig_Vertex_Y_Barrel      =   new MnvH2D("h_Mig_Vertex_Y_Barrel",     "h_Mig_Vertex_Y_Barrel",  Vertex_Ybin_vector.size()-1, Vertex_Ybin_vector.data(), Vertex_Ybin_vector.size()-1, Vertex_Ybin_vector.data());
MnvH2D *h_Mig_Vertex_R_Barrel      =   new MnvH2D("h_Mig_Vertex_R_Barrel",     "h_Mig_Vertex_R_Barrel",  Vertex_Rbin_vector.size()-1, Vertex_Rbin_vector.data(), Vertex_Rbin_vector.size()-1, Vertex_Rbin_vector.data());
MnvH2D *h_Mig_Vertex_Z_Barrel      =   new MnvH2D("h_Mig_Vertex_Z_Barrel",     "h_Mig_Vertex_Z_Barrel",  Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data(), Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());

MnvH2D *h_Mig_Vertex_X_DownstreamCap      =   new MnvH2D("h_Mig_Vertex_X_DownstreamCap",     "h_Mig_Vertex_X_DownstreamCap",  Vertex_Xbin_vector.size()-1, Vertex_Xbin_vector.data(), Vertex_Xbin_vector.size()-1, Vertex_Xbin_vector.data());
MnvH2D *h_Mig_Vertex_Y_DownstreamCap      =   new MnvH2D("h_Mig_Vertex_Y_DownstreamCap",     "h_Mig_Vertex_Y_DownstreamCap",  Vertex_Ybin_vector.size()-1, Vertex_Ybin_vector.data(), Vertex_Ybin_vector.size()-1, Vertex_Ybin_vector.data());
MnvH2D *h_Mig_Vertex_R_DownstreamCap      =   new MnvH2D("h_Mig_Vertex_R_DownstreamCap",     "h_Mig_Vertex_R_DownstreamCap",  Vertex_Rbin_vector.size()-1, Vertex_Rbin_vector.data(), Vertex_Rbin_vector.size()-1, Vertex_Rbin_vector.data());
MnvH2D *h_Mig_Vertex_Z_DownstreamCap      =   new MnvH2D("h_Mig_Vertex_Z_DownstreamCap",     "h_Mig_Vertex_Z_DownstreamCap",  Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data(), Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());

MnvH2D *h_Mig_Vertex_X_Downstream_ConcaveCap      =   new MnvH2D("h_Mig_Vertex_X_Downstream_ConcaveCap",     "h_Mig_Vertex_X_downstream_ConcaveCap",  Vertex_Xbin_vector.size()-1, Vertex_Xbin_vector.data(), Vertex_Xbin_vector.size()-1, Vertex_Xbin_vector.data());
MnvH2D *h_Mig_Vertex_Y_Downstream_ConcaveCap      =   new MnvH2D("h_Mig_Vertex_Y_Downstream_ConcaveCap",     "h_Mig_Vertex_Y_downstream_ConcaveCap",  Vertex_Ybin_vector.size()-1, Vertex_Ybin_vector.data(), Vertex_Ybin_vector.size()-1, Vertex_Ybin_vector.data());
MnvH2D *h_Mig_Vertex_R_Downstream_ConcaveCap      =   new MnvH2D("h_Mig_Vertex_R_Downstream_ConcaveCap",     "h_Mig_Vertex_R_downstream_ConcaveCap",  Vertex_Rbin_vector.size()-1, Vertex_Rbin_vector.data(), Vertex_Rbin_vector.size()-1, Vertex_Rbin_vector.data());
MnvH2D *h_Mig_Vertex_Z_Downstream_ConcaveCap      =   new MnvH2D("h_Mig_Vertex_Z_Downstream_ConcaveCap",     "h_Mig_Vertex_Z_downstream_ConcaveCap",  Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data(), Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());
////////////////////////////////////////////////////////////////////////////////
// 14 region breakdown
////////////////////////////////////////////////////////////////////////////////

std::vector<CryoTank_REGIONS> RegionVector = CryoZRegionBreakdown14_vector();
HistFolio_material_CryoRegionMap  HistFolio_Region14_Map_Vertex_X;
HistFolio_material_CryoRegionMap  HistFolio_Region14_Map_Vectex_Y;
HistFolio_material_CryoRegionMap  HistFolio_Region14_Map_Vectex_Z;
HistFolio_material_CryoRegionMap  HistFolio_Region14_Map_Vectex_R;

HistFolio_material_CryoRegionMap  HistFolio_Region14_Map_TRUE_Vertex_X;
HistFolio_material_CryoRegionMap  HistFolio_Region14_Map_TRUE_Vectex_Y;
HistFolio_material_CryoRegionMap  HistFolio_Region14_Map_TRUE_Vectex_Z;
HistFolio_material_CryoRegionMap  HistFolio_Region14_Map_TRUE_Vectex_R;

HistFolio_material_CryoRegionMap  HistFolio_Region14_Map_Distance_to_NearestWall;
HistFolio_material_CryoRegionMap  HistFolio_Region14_Map_h_secTrk_Tracklength;
HistFolio_material_CryoRegionMap  HistFolio_Region14_Map_secTrk_DOCA;
HistFolio_material_CryoRegionMap  HistFolio_Region14_Map_Muon_DOCA;
HistFolio_material_CryoRegionMap  HistFolio_Region14_Map_MuonPZ;
HistFolio_material_CryoRegionMap  HistFolio_Region14_Map_MuonPT;
HistFolio_material_CryoRegionMap  HistFolio_Region14_Map_MuonTheta;
HistFolio_material_CryoRegionMap  HistFolio_Region14_Map_MuonE;

char tempName[1024];


for(auto cat: RegionVector){

  sprintf(tempName,"%s_Region_%d","h_Region14_Vertex_X_Material", GetRegionint(cat));
  PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_X_Region14_Material =
  PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, tempName, Vertex_Xbin_vector ,"Vertex_X_Material; [mm];Events:");
  HistFolio_Region14_Map_Vertex_X.insert(std::make_pair(cat, h_CryoVertex_X_Region14_Material ));

  sprintf(tempName,"%s_Region_%d","h_Region14_Vertex_Y_Material", GetRegionint(cat));
  PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Y_Region14_Material =
  PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, tempName, Vertex_Ybin_vector ,"Vertex_Y_Material; [mm];Events:");
  HistFolio_Region14_Map_Vectex_Y.insert(std::make_pair(cat, h_CryoVertex_Y_Region14_Material ));

  sprintf(tempName,"%s_Region_%d","h_Region14_Vertex_Z_Material", GetRegionint(cat));
  PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Z_Region14_Material=
  PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, tempName, Vertex_Zbin_vector ,"Vertex_Z_Material; [mm];Events:");
  HistFolio_Region14_Map_Vectex_Z.insert(std::make_pair(cat, h_CryoVertex_Z_Region14_Material));

  sprintf(tempName,"%s_Region_%d","h_Region14_Vertex_R_Material", GetRegionint(cat));
  PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_R_Region14_Material =
  PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, tempName, Vertex_Rbin_vector ,"Vertex_R_Material; [mm];Events:");
  HistFolio_Region14_Map_Vectex_R.insert(std::make_pair(cat, h_CryoVertex_R_Region14_Material ));

  sprintf(tempName,"%s_Region_%d","h_Region14_TRUE_Vertex_X_Material", GetRegionint(cat));
  PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_TRUE_CryoVertex_X_Region14_Material =
  PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, tempName, Vertex_Xbin_vector ,"Vertex_X_Material; [mm];Events:");
  HistFolio_Region14_Map_TRUE_Vertex_X.insert(std::make_pair(cat, h_TRUE_CryoVertex_X_Region14_Material ));

  sprintf(tempName,"%s_Region_%d","h_Region14_TRUE_Vertex_Y_Material", GetRegionint(cat));
  PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_TRUE_CryoVertex_Y_Region14_Material =
  PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, tempName, Vertex_Ybin_vector ,"Vertex_Y_Material; [mm];Events:");
  HistFolio_Region14_Map_TRUE_Vectex_Y.insert(std::make_pair(cat, h_TRUE_CryoVertex_Y_Region14_Material ));

  sprintf(tempName,"%s_Region_%d","h_Region14_TRUE_Vertex_Z_Material", GetRegionint(cat));
  PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_TRUE_CryoVertex_Z_Region14_Material=
  PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, tempName, Vertex_Zbin_vector ,"Vertex_Z_Material; [mm];Events:");
  HistFolio_Region14_Map_TRUE_Vectex_Z.insert(std::make_pair(cat, h_TRUE_CryoVertex_Z_Region14_Material));

  sprintf(tempName,"%s_Region_%d","h_Region14_TRUE_Vertex_R_Material", GetRegionint(cat));
  PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_TRUE_CryoVertex_R_Region14_Material =
  PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, tempName, Vertex_Rbin_vector ,"Vertex_R_Material; [mm];Events:");
  HistFolio_Region14_Map_TRUE_Vectex_R.insert(std::make_pair(cat, h_TRUE_CryoVertex_R_Region14_Material ));

  sprintf(tempName,"%s_Region_%d","h_Region14_NearestWall_Material", GetRegionint(cat));
  PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_NearestWall_Region14_Material =
  PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, tempName, Distance_to_innerTank  ,"NearestWall; [mm];Events:");
  HistFolio_Region14_Map_Distance_to_NearestWall.insert(std::make_pair(cat, h_NearestWall_Region14_Material ));


  sprintf(tempName,"%s_Region_%d","h_Region14_secTrk_Tracklength_Material", GetRegionint(cat));
  PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_Tracklength_Region14_Material =
  PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, tempName, Recoil_track_length_vector   ,"secTrk_Tracklength; [mm];Events:");
  HistFolio_Region14_Map_h_secTrk_Tracklength.insert(std::make_pair(cat, h_secTrk_Tracklength_Region14_Material ));

  sprintf(tempName,"%s_Region_%d","h_Region14_secTrk_DOCA_Material", GetRegionint(cat));
  PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_DOCA_Region14_Material =
  PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, tempName, secTrk_DOCA_vector   ,"secTrk_DOCA; [mm];Events:");
  HistFolio_Region14_Map_secTrk_DOCA.insert(std::make_pair(cat, h_secTrk_DOCA_Region14_Material ));

  sprintf(tempName,"%s_Region_%d","h_Region14_Muon_DOCA_Material", GetRegionint(cat));
  PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Muon_DOCA_Region14_Material =
  PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, tempName, Vertex_DOCAbin_vector   ,"Muon_DOCA; [mm];Events:");
  HistFolio_Region14_Map_Muon_DOCA.insert(std::make_pair(cat, h_Muon_DOCA_Region14_Material ));


  sprintf(tempName,"%s_Region_%d","h_Region14_Muon_E_Material", GetRegionint(cat));
  PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Muon_E_Region14_Material =
  PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, tempName, Ebin_vector   ,"Muon_E; [mm];Events:");
  HistFolio_Region14_Map_MuonE.insert(std::make_pair(cat, h_Muon_E_Region14_Material ));


  sprintf(tempName,"%s_Region_%d","h_Region14_Muon_PT_Material", GetRegionint(cat));
  PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Muon_PT_Region14_Material =
  PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, tempName, PTbin_vector   ,"Muon_PT; [mm];Events:");
  HistFolio_Region14_Map_MuonPT.insert(std::make_pair(cat, h_Muon_PT_Region14_Material ));

  sprintf(tempName,"%s_Region_%d","h_Region14_Muon_PZ_Material", GetRegionint(cat));
  PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Muon_PZ_Region14_Material =
  PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, tempName, Pzbin_vector   ,"Muon_PZ; [mm];Events:");
  HistFolio_Region14_Map_MuonPZ.insert(std::make_pair(cat, h_Muon_PZ_Region14_Material ));

  sprintf(tempName,"%s_Region_%d","h_Region14_MuonTheta_Material", GetRegionint(cat));
  PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonTheta_Region14_Material =
  PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, tempName, MuonThetabin_vector  ,"MuonTheta; [mm];Events:");
  HistFolio_Region14_Map_MuonTheta.insert(std::make_pair(cat, h_MuonTheta_Region14_Material ));

}









  //=========================================
  // Entry Loop For MC
  //=========================================

  RECO_Cut_Map CountMap_Fiduical;
  RECO_Cut_Map CountMap_TRUE_RECO;
  FillingRecoCountingMap(kCutsVector_FiduicalEff, CountMap_Fiduical);
  RECO_Cut_Map CountMap_ALL;
  FillingRecoCountingMap(kCutsVector_FiduicalEff, CountMap_TRUE_RECO);
  CountMap_Fiduical[kFiducialVolume_new]=0.0;
  CountMap_TRUE_RECO[kFiducialVolume_new]=0.0;
  TRUE_Cut_Map Truth_Cut_Map_Fiduical;
  TRUE_Cut_Map Truth_Cut_Map_ALL;
  FillingTruthCountingMap(kCuts_Truth_Vector,     Truth_Cut_Map_ALL);

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
if(useweights==true) PrintWgtsBeingUSED();

if(RunwithConvolution == true){
std::cout<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;
std::cout<< "Running with Convolution"<< std::endl;
std::cout<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;
std::cout<<"vertex X (mean , sigma) = ( " << vertex_X_mean<< ", "<< vertex_X_sigma<< " ) "<<std::endl;
std::cout<<"vertex Y (mean , sigma) = ( " << vertex_Y_mean<< ", "<< vertex_Y_sigma<< " ) "<<std::endl;
std::cout<<"vertex Z (mean , sigma) = ( " << vertex_Z_mean<< ", "<< vertex_Z_sigma<< " ) "<<std::endl;
std::cout<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;
std::cout<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;

}
else if (RunwithConvolution == false){

  std::cout<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;
  std::cout<< "NO Convolution Applied "<< std::endl;
  std::cout<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;

}


  std::cout<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;
  std::cout<<"Runing with shift values of "<< std::endl;
  std::cout<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;
  std::cout<<"vertex X Shift =  " << ShiftX_major<<std::endl;
  std::cout<<"vertex Y Shift =  " << ShiftY_major<<std::endl;
  std::cout<<"vertex Z Shift =  " << ShiftZ_major<<std::endl;

  std::cout<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;
  std::cout<<" ~~~~~~~~~~~~~~ Fiduical IS:";
  if( RunwithFid==true){std::cout<<"ON "<<std::endl;}
  else if (RunwithFid==false){std::cout<<"OFF "<<std::endl;}
  std::cout<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;



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

        if(PassesCutsTRUTH(*Universe_GROUP.front(), kCuts_Truth_Vector, kWeights_v1tune, Truth_Cut_Map_ALL)){
          // TRUTH ONLY Cuts
          if(PassesCutsRECO(*Universe_GROUP.front(),  is_mc , kCutsVector_FiduicalEff, kWeights_v1tune, CountMap_TRUE_RECO) ){
            for (auto universe : Universe_GROUP){
              universe->SetEntry(ii);

              double wgt_minerva_v1 = universe->GetWeight(kWeights_v1tune);

              Material_type Material_type_Event = universe->Get_MaterialStackType();

              double ShiftX  = ShiftX_major;
              double ShiftY =  ShiftY_major;
              double ShiftZ =  ShiftZ_major;

              if(Material_type_Event!=kAluminium && Material_type_Event!=kHelium ){
                ShiftX=0;
                ShiftY=0;
                ShiftZ=0;}

              double x = universe->GetVertex_x() + ShiftX ;
              double y = universe->GetVertex_y() + ShiftY ;
              double z = universe->GetVertex_z() + ShiftZ ;

              double x_true= universe->GetTRUE_Vertex_x();
              double y_true= universe->GetTRUE_Vertex_y();
              double z_true= universe->GetTRUE_Vertex_z();

              double r =  sqrt(x*x + y*y);
              double r_true =  sqrt(x_true*x_true + y_true*y_true);

            if(RunwithFid==true){
              if(IsInFiducalVolumeFromtheInnerEdge( r, z, 50.0  )==false) continue;}
              CountMap_TRUE_RECO[kFiducialVolume_new]=+wgt_minerva_v1;
              double x_resolution = x_true - x;
              double y_resolution = y_true - y;
              double z_resolution = z_true - z;
              double r_resolution = r_true - r;

              CryoTank_REGIONS CryoTankRegion_type = FourRegion_of_CryoTank(z_true);

              double Al_wgt = 1.0;
              if(useweights==true){Al_wgt *= return_AlWgt(CryoTankRegion_type, Material_type_Event);}
                wgt_minerva_v1*=Al_wgt;


              h_CryoVertex_X_resolution_TRUE_RECO.univHist(universe)->Fill(x_resolution,wgt_minerva_v1);
              h_CryoVertex_X_percentresolution_TRUE_RECO.univHist(universe)->Fill(x_resolution/x_true,wgt_minerva_v1);
              h_CryoVertex_Y_resolution_TRUE_RECO.univHist(universe)->Fill(y_resolution,wgt_minerva_v1);
              h_CryoVertex_Y_percentresolution_TRUE_RECO.univHist(universe)->Fill(y_resolution/y_true,wgt_minerva_v1);
              h_CryoVertex_R_resolution_TRUE_RECO.univHist(universe)->Fill(r_resolution,wgt_minerva_v1);
              h_CryoVertex_R_percentresolution_TRUE_RECO.univHist(universe)->Fill(r_resolution/r_true,wgt_minerva_v1);
              h_CryoVertex_Z_resolution_TRUE_RECO.univHist(universe)->Fill(z_resolution,wgt_minerva_v1);
              h_CryoVertex_Z_percentresolution_TRUE_RECO.univHist(universe)->Fill(z_resolution/z_true,wgt_minerva_v1);


              if(CryoTankRegion_type==kUpstream_head)
              {

                h_CryoVertex_X_UpstreamCap_resolution_TRUE_RECO.univHist(universe)->Fill(x_resolution,wgt_minerva_v1);
                h_CryoVertex_X_UpstreamCap_percentresolution_TRUE_RECO.univHist(universe)->Fill(x_resolution/x_true,wgt_minerva_v1);
                h_CryoVertex_Y_UpstreamCap_resolution_TRUE_RECO.univHist(universe)->Fill(y_resolution,wgt_minerva_v1);
                h_CryoVertex_Y_UpstreamCap_percentresolution_TRUE_RECO.univHist(universe)->Fill(y_resolution/y_true,wgt_minerva_v1);
                h_CryoVertex_R_UpstreamCap_resolution_TRUE_RECO.univHist(universe)->Fill(r_resolution,wgt_minerva_v1);
                h_CryoVertex_R_UpstreamCap_percentresolution_TRUE_RECO.univHist(universe)->Fill(r_resolution/r_true,wgt_minerva_v1);
                h_CryoVertex_Z_UpstreamCap_resolution_TRUE_RECO.univHist(universe)->Fill(z_resolution,wgt_minerva_v1);
                h_CryoVertex_Z_UpstreamCap_percentresolution_TRUE_RECO.univHist(universe)->Fill(z_resolution/z_true,wgt_minerva_v1);

              }
              else if(CryoTankRegion_type==kCenter)
              {
                h_CryoVertex_X_Barrel_resolution_TRUE_RECO.univHist(universe)->Fill(x_resolution,wgt_minerva_v1);
                h_CryoVertex_X_Barrel_percentresolution_TRUE_RECO.univHist(universe)->Fill(x_resolution/x_true,wgt_minerva_v1);
                h_CryoVertex_Y_Barrel_resolution_TRUE_RECO.univHist(universe)->Fill(y_resolution,wgt_minerva_v1);
                h_CryoVertex_Y_Barrel_percentresolution_TRUE_RECO.univHist(universe)->Fill(y_resolution/y_true,wgt_minerva_v1);
                h_CryoVertex_R_Barrel_resolution_TRUE_RECO.univHist(universe)->Fill(r_resolution,wgt_minerva_v1);
                h_CryoVertex_R_Barrel_percentresolution_TRUE_RECO.univHist(universe)->Fill(r_resolution/r_true,wgt_minerva_v1);
                h_CryoVertex_Z_Barrel_resolution_TRUE_RECO.univHist(universe)->Fill(z_resolution,wgt_minerva_v1);
                h_CryoVertex_Z_Barrel_percentresolution_TRUE_RECO.univHist(universe)->Fill(z_resolution/z_true,wgt_minerva_v1);

              }
              else if(CryoTankRegion_type==kDownstream_head)
              {
                h_CryoVertex_X_DownstreamCap_resolution_TRUE_RECO.univHist(universe)->Fill(x_resolution,wgt_minerva_v1);
                h_CryoVertex_X_DownstreamCap_percentresolution_TRUE_RECO.univHist(universe)->Fill(x_resolution/x_true,wgt_minerva_v1);
                h_CryoVertex_Y_DownstreamCap_resolution_TRUE_RECO.univHist(universe)->Fill(y_resolution,wgt_minerva_v1);
                h_CryoVertex_Y_DownstreamCap_percentresolution_TRUE_RECO.univHist(universe)->Fill(y_resolution/y_true,wgt_minerva_v1);
                h_CryoVertex_R_DownstreamCap_resolution_TRUE_RECO.univHist(universe)->Fill(r_resolution,wgt_minerva_v1);
                h_CryoVertex_R_DownstreamCap_percentresolution_TRUE_RECO.univHist(universe)->Fill(r_resolution/r_true,wgt_minerva_v1);
                h_CryoVertex_Z_DownstreamCap_resolution_TRUE_RECO.univHist(universe)->Fill(z_resolution,wgt_minerva_v1);
                h_CryoVertex_Z_DownstreamCap_percentresolution_TRUE_RECO.univHist(universe)->Fill(z_resolution/z_true,wgt_minerva_v1);

              }

              else if(CryoTankRegion_type==kDownstream_ConcaveCap)
              {
                h_CryoVertex_X_Downstream_ConcaveCap_resolution_TRUE_RECO.univHist(universe)->Fill(x_resolution,wgt_minerva_v1);
                h_CryoVertex_X_Downstream_ConcaveCap_percentresolution_TRUE_RECO.univHist(universe)->Fill(x_resolution/x_true,wgt_minerva_v1);
                h_CryoVertex_Y_Downstream_ConcaveCap_resolution_TRUE_RECO.univHist(universe)->Fill(y_resolution,wgt_minerva_v1);
                h_CryoVertex_Y_Downstream_ConcaveCap_percentresolution_TRUE_RECO.univHist(universe)->Fill(y_resolution/y_true,wgt_minerva_v1);
                h_CryoVertex_R_Downstream_ConcaveCap_resolution_TRUE_RECO.univHist(universe)->Fill(r_resolution,wgt_minerva_v1);
                h_CryoVertex_R_Downstream_ConcaveCap_percentresolution_TRUE_RECO.univHist(universe)->Fill(r_resolution/r_true,wgt_minerva_v1);
                h_CryoVertex_Z_Downstream_ConcaveCap_resolution_TRUE_RECO.univHist(universe)->Fill(z_resolution,wgt_minerva_v1);
                h_CryoVertex_Z_Downstream_ConcaveCap_percentresolution_TRUE_RECO.univHist(universe)->Fill(z_resolution/z_true,wgt_minerva_v1);

              }

              else{std::cout<<"ABSURDITY !! Event Failed to be in a  CryoRegion: Something Wrong"<<std::endl; assert(false);}
            }// END of Universe Groups
          }// END OF TRUTH + RECO CUTS
        }//END OF TRUTH PASS CUTS


        ///////////////////////////////////////////
        ////
        ////  Apply RECO CUTS to each universe
        ////
        ///////////////////////////////////////////


      if(PassesCutsRECO(*Universe_GROUP.front(),  is_mc , kCutsVector_FiduicalEff , kWeights_v1tune, CountMap_Fiduical ) ){
        for (auto universe : Universe_GROUP){

          universe->SetEntry(ii);

          Material_type Material_type_Event = universe->Get_MaterialStackType();

          double wgt_minerva_v1 = universe->GetWeight(kWeights_v1tune);

          double ShiftX  = ShiftX_major;
          double ShiftY =  ShiftY_major;
          double ShiftZ =  ShiftZ_major;

          if(Material_type_Event!=kAluminium && Material_type_Event!=kHelium ){
            ShiftX=0;
            ShiftY=0;
            ShiftZ=0;}

          double Smearing_X = vertexX_Convolution(generator);
          double Smearing_Y = vertexY_Convolution(generator);
          double Smearing_Z = vertexZ_Convolution(generator);

          if(RunwithConvolution == false){
            Smearing_X = 0.0;
            Smearing_Y = 0.0;
            Smearing_Z = 0.0;
          }


          double x = universe->GetVertex_x() + ShiftX + Smearing_X;
          double y = universe->GetVertex_y() + ShiftY + Smearing_Y;
          double z = universe->GetVertex_z() + ShiftZ + Smearing_Z;

          double x_true = universe->GetTRUE_Vertex_x();
          double y_true = universe->GetTRUE_Vertex_y();
          double z_true = universe->GetTRUE_Vertex_z();

          //Vertex_XYZ VertexPostion{x,y,z};
          double r =  sqrt(x*x + y*y);
          double r_true =  sqrt(x_true*x_true + y_true*y_true);

          double x_resolution = x_true - x;
          double y_resolution = y_true - y;
          double z_resolution = z_true - z;
          double r_resolution = r_true - r;

          double Theta = universe->GetThetamu();
          double Pmu = universe ->GetPmu()/1000;
          if(RunwithFid==true){
          if(IsInFiducalVolumeFromtheInnerEdge( r, z, 50.0  )==false) continue;}
          CountMap_Fiduical[kFiducialVolume_new]=+wgt_minerva_v1;
          double phi = universe->GetPhimu();

          double px = Pmu * std::sin(Theta) * std::cos(phi);
          double py = Pmu * std::sin(Theta) * std::sin(phi);

          double PT = sqrt(px*px + py*py);
          double PZ = Pmu*std::cos(Theta);
          double Emu = universe->GetEmu()*.001;

          double MuonDoca = universe->GetDOCAmu();//universe->Calculated_DOCA(0 , VertexPostion);
          //std::cout<<"Mu doca out = "<< universe->GetDOCAmu() << " new = " << MuonDoca <<std::endl;



          int secondTrk = universe->Getindex2ndTrackhighestKE();
          double SecTrkDoca = universe->GetNonmuDOCA(secondTrk);//universe->Calculated_DOCA(secondTrk , VertexPostion);


          CryoTank_REGIONS CryoTankRegion_type = FourRegion_of_CryoTank(z_true);
          CryoTank_REGIONS CryoTankRegion14 = CryoZRegionBreakdown14(z_true);


        //  double Reco_distance = RECO_Distance_to_innerTank(*universe);
          double Reco_distance = RECO_Distance_to_innerTank(r, z );
          double dist_upstreamCap = DistanceFromUpStreamBulge(z , r);
          double dist_downstreamCap = DistanceFromDownStreamBulge(z , r);
          double minervaTrkLength = universe->GetNonmuTrkLength_InMinerva_Incm(secondTrk);

          TrackType Track_type_Event = universe->GetTrackType();
          VertexOptions VertexOption_type = universe->GetVertex_optionType();
          boolNTrack boolNTrack_Type = universe->GetVertex_boolNTrack();

         double Al_wgt = 1.0;
         if(useweights==true){Al_wgt *= return_AlWgt(CryoTankRegion_type, Material_type_Event);}
         wgt_minerva_v1*=Al_wgt;



          if(CryoTankRegion_type==kUpstream_head)
          {
            h_MuonE_UpstreamCap.univHist(universe)->Fill(Emu,wgt_minerva_v1);
            h_MuonPZ_UpstreamCap.univHist(universe)->Fill(PZ,wgt_minerva_v1);
            h_MuonPT_UpstreamCap.univHist(universe)->Fill(PT,wgt_minerva_v1);
            h_MuonTheta_UpstreamCap.univHist(universe)->Fill(Theta*TMath::RadToDeg(),wgt_minerva_v1);
            h_CryoVertex_X_UpstreamCap.univHist(universe)->Fill(x ,wgt_minerva_v1);
            h_CryoVertex_Y_UpstreamCap.univHist(universe)->Fill(y ,wgt_minerva_v1);
            h_CryoVertex_Z_UpstreamCap.univHist(universe)->Fill(z ,wgt_minerva_v1);
            h_CryoVertex_R_UpstreamCap.univHist(universe)->Fill(r,wgt_minerva_v1);
            h_Distance_to_InnerTank_UpstreamCap.univHist(universe)->Fill(Reco_distance,wgt_minerva_v1);
            h_Distance_to_InnerTank_Caps_UpstreamCap.univHist(universe)->Fill(Reco_distance,wgt_minerva_v1);
            h_MuonDOCA_UpstreamCap.univHist(universe)->Fill(MuonDoca,wgt_minerva_v1);
            h_secTrk_DOCA_UpstreamCap.univHist(universe)->Fill(SecTrkDoca,wgt_minerva_v1);
            h_secTrk_tracklength_UpstreamCap.univHist(universe)->Fill(minervaTrkLength,wgt_minerva_v1);
            h_Distance_to_downstreamCap_UpstreamCap.univHist(universe)->Fill(dist_downstreamCap,wgt_minerva_v1);
            h_Distance_to_upstreamCap_UpstreamCap.univHist(universe)->Fill(dist_upstreamCap,wgt_minerva_v1);



            h_CryoVertex_X_UpstreamCap_resolution_RECO.univHist(universe)->Fill(x_resolution,wgt_minerva_v1);
            h_CryoVertex_X_UpstreamCap_percentresolution_RECO.univHist(universe)->Fill(x_resolution/x_true,wgt_minerva_v1);
            h_CryoVertex_Y_UpstreamCap_resolution_RECO.univHist(universe)->Fill(y_resolution,wgt_minerva_v1);
            h_CryoVertex_Y_UpstreamCap_percentresolution_RECO.univHist(universe)->Fill(y_resolution/y_true,wgt_minerva_v1);
            h_CryoVertex_R_UpstreamCap_resolution_RECO.univHist(universe)->Fill(r_resolution,wgt_minerva_v1);
            h_CryoVertex_R_UpstreamCap_percentresolution_RECO.univHist(universe)->Fill(r_resolution/r_true,wgt_minerva_v1);
            h_CryoVertex_Z_UpstreamCap_resolution_RECO.univHist(universe)->Fill(z_resolution,wgt_minerva_v1);
            h_CryoVertex_Z_UpstreamCap_percentresolution_RECO.univHist(universe)->Fill(z_resolution/z_true,wgt_minerva_v1);


            if(Cylindrical_CutAboutZero(r)== true){

              h_CryoVertex_Z_RCut_UpstreamCap.univHist(universe)->Fill(z ,wgt_minerva_v1);
              h_CryoVertex_X_RCut_UpstreamCap.univHist(universe)->Fill(x ,wgt_minerva_v1);
              h_CryoVertex_Y_RCut_UpstreamCap.univHist(universe)->Fill(y ,wgt_minerva_v1);
              h_CryoVertex_R_RCut_UpstreamCap.univHist(universe)->Fill(r,wgt_minerva_v1);
              h_Distance_to_downstreamCap_RCut_UpstreamCap.univHist(universe)->Fill(dist_downstreamCap,wgt_minerva_v1);
              h_Distance_to_upstreamCap_RCut_UpstreamCap.univHist(universe)->Fill(dist_upstreamCap,wgt_minerva_v1);
            }


          }
          else if(CryoTankRegion_type==kCenter)
          {
            h_MuonE_Barrel.univHist(universe)->Fill(Emu,wgt_minerva_v1);
            h_MuonPZ_Barrel.univHist(universe)->Fill(PZ,wgt_minerva_v1);
            h_MuonPT_Barrel.univHist(universe)->Fill(PT,wgt_minerva_v1);
            h_MuonTheta_Barrel.univHist(universe)->Fill(Theta*TMath::RadToDeg(),wgt_minerva_v1);
            h_CryoVertex_X_Barrel.univHist(universe)->Fill(x ,wgt_minerva_v1);
            h_CryoVertex_Y_Barrel.univHist(universe)->Fill(y ,wgt_minerva_v1);
            h_CryoVertex_Z_Barrel.univHist(universe)->Fill(z ,wgt_minerva_v1);
            h_CryoVertex_R_Barrel.univHist(universe)->Fill(r,wgt_minerva_v1);
            h_Distance_to_InnerTank_Barrel.univHist(universe)->Fill(Reco_distance,wgt_minerva_v1);
            h_MuonDOCA_Barrel.univHist(universe)->Fill(MuonDoca,wgt_minerva_v1);
            h_secTrk_DOCA_Barrel.univHist(universe)->Fill(SecTrkDoca,wgt_minerva_v1);
            h_secTrk_tracklength_Barrel.univHist(universe)->Fill(minervaTrkLength,wgt_minerva_v1);
            h_Distance_to_downstreamCap_Barrel.univHist(universe)->Fill(dist_downstreamCap,wgt_minerva_v1);
            h_Distance_to_upstreamCap_Barrel.univHist(universe)->Fill(dist_upstreamCap,wgt_minerva_v1);
            h_Distance_to_InnerTank_Barrel_Barrel.univHist(universe)->Fill(Reco_distance,wgt_minerva_v1);


            h_CryoVertex_X_Barrel_resolution_RECO.univHist(universe)->Fill(x_resolution,wgt_minerva_v1);
            h_CryoVertex_X_Barrel_percentresolution_RECO.univHist(universe)->Fill(x_resolution/x_true,wgt_minerva_v1);
            h_CryoVertex_Y_Barrel_resolution_RECO.univHist(universe)->Fill(y_resolution,wgt_minerva_v1);
            h_CryoVertex_Y_Barrel_percentresolution_RECO.univHist(universe)->Fill(y_resolution/y_true,wgt_minerva_v1);
            h_CryoVertex_R_Barrel_resolution_RECO.univHist(universe)->Fill(r_resolution,wgt_minerva_v1);
            h_CryoVertex_R_Barrel_percentresolution_RECO.univHist(universe)->Fill(r_resolution/r_true,wgt_minerva_v1);
            h_CryoVertex_Z_Barrel_resolution_RECO.univHist(universe)->Fill(z_resolution,wgt_minerva_v1);
            h_CryoVertex_Z_Barrel_percentresolution_RECO.univHist(universe)->Fill(z_resolution/z_true,wgt_minerva_v1);

            if(Cylindrical_CutAboutZero(r)== true){
              h_CryoVertex_Z_RCut_Barrel.univHist(universe)->Fill(z ,wgt_minerva_v1);
              h_CryoVertex_X_RCut_Barrel.univHist(universe)->Fill(x ,wgt_minerva_v1);
              h_CryoVertex_Y_RCut_Barrel.univHist(universe)->Fill(y ,wgt_minerva_v1);
              h_CryoVertex_R_RCut_Barrel.univHist(universe)->Fill(r,wgt_minerva_v1);
              h_Distance_to_downstreamCap_RCut_Barrel.univHist(universe)->Fill(dist_downstreamCap,wgt_minerva_v1);
              h_Distance_to_upstreamCap_RCut_Barrel.univHist(universe)->Fill(dist_upstreamCap,wgt_minerva_v1);
            }

          }
          else if(CryoTankRegion_type==kDownstream_head)
          {
            h_MuonE_DownstreamCap.univHist(universe)->Fill(Emu,wgt_minerva_v1);
            h_MuonPZ_DownstreamCap.univHist(universe)->Fill(PZ,wgt_minerva_v1);
            h_MuonPT_DownstreamCap.univHist(universe)->Fill(PT,wgt_minerva_v1);
            h_MuonTheta_DownstreamCap.univHist(universe)->Fill(Theta*TMath::RadToDeg(),wgt_minerva_v1);
            h_CryoVertex_X_DownstreamCap.univHist(universe)->Fill(x ,wgt_minerva_v1);
            h_CryoVertex_Y_DownstreamCap.univHist(universe)->Fill(y ,wgt_minerva_v1);
            h_CryoVertex_Z_DownstreamCap.univHist(universe)->Fill(z ,wgt_minerva_v1);
            h_CryoVertex_R_DownstreamCap.univHist(universe)->Fill(r,wgt_minerva_v1);
            h_Distance_to_InnerTank_DownstreamCap.univHist(universe)->Fill(Reco_distance,wgt_minerva_v1);
            h_Distance_to_InnerTank_Caps_DownstreamCap.univHist(universe)->Fill(Reco_distance,wgt_minerva_v1);
            h_MuonDOCA_DownstreamCap.univHist(universe)->Fill(MuonDoca,wgt_minerva_v1);
            h_secTrk_DOCA_DownstreamCap.univHist(universe)->Fill(SecTrkDoca,wgt_minerva_v1);
            h_secTrk_tracklength_DownstreamCap.univHist(universe)->Fill(minervaTrkLength,wgt_minerva_v1);

            h_Distance_to_downstreamCap_DownstreamCap.univHist(universe)->Fill(dist_downstreamCap,wgt_minerva_v1);
            h_Distance_to_upstreamCap_DownstreamCap.univHist(universe)->Fill(dist_upstreamCap,wgt_minerva_v1);



            h_CryoVertex_X_DownstreamCap_resolution_RECO.univHist(universe)->Fill(x_resolution,wgt_minerva_v1);
            h_CryoVertex_X_DownstreamCap_percentresolution_RECO.univHist(universe)->Fill(x_resolution/x_true,wgt_minerva_v1);
            h_CryoVertex_Y_DownstreamCap_resolution_RECO.univHist(universe)->Fill(y_resolution,wgt_minerva_v1);
            h_CryoVertex_Y_DownstreamCap_percentresolution_RECO.univHist(universe)->Fill(y_resolution/y_true,wgt_minerva_v1);
            h_CryoVertex_R_DownstreamCap_resolution_RECO.univHist(universe)->Fill(r_resolution,wgt_minerva_v1);
            h_CryoVertex_R_DownstreamCap_percentresolution_RECO.univHist(universe)->Fill(r_resolution/r_true,wgt_minerva_v1);
            h_CryoVertex_Z_DownstreamCap_resolution_RECO.univHist(universe)->Fill(z_resolution,wgt_minerva_v1);
            h_CryoVertex_Z_DownstreamCap_percentresolution_RECO.univHist(universe)->Fill(z_resolution/z_true,wgt_minerva_v1);

            if(Cylindrical_CutAboutZero(r)== true){
              h_CryoVertex_Z_RCut_DownstreamCap.univHist(universe)->Fill(z ,wgt_minerva_v1);

              h_CryoVertex_X_RCut_DownstreamCap.univHist(universe)->Fill(x ,wgt_minerva_v1);
              h_CryoVertex_Y_RCut_DownstreamCap.univHist(universe)->Fill(y ,wgt_minerva_v1);
              h_CryoVertex_R_RCut_DownstreamCap.univHist(universe)->Fill(r,wgt_minerva_v1);
              h_Distance_to_downstreamCap_RCut_DownstreamCap.univHist(universe)->Fill(dist_downstreamCap,wgt_minerva_v1);
              h_Distance_to_upstreamCap_RCut_DownstreamCap.univHist(universe)->Fill(dist_upstreamCap,wgt_minerva_v1);
            }



          }
          else if(CryoTankRegion_type==kDownstream_ConcaveCap)
          {
            h_MuonE_Downstream_ConcaveCap.univHist(universe)->Fill(Emu,wgt_minerva_v1);
            h_MuonPZ_Downstream_ConcaveCap.univHist(universe)->Fill(PZ,wgt_minerva_v1);
            h_MuonPT_Downstream_ConcaveCap.univHist(universe)->Fill(PT,wgt_minerva_v1);
            h_MuonTheta_Downstream_ConcaveCap.univHist(universe)->Fill(Theta*TMath::RadToDeg(),wgt_minerva_v1);
            h_CryoVertex_X_Downstream_ConcaveCap.univHist(universe)->Fill(x ,wgt_minerva_v1);
            h_CryoVertex_Y_Downstream_ConcaveCap.univHist(universe)->Fill(y ,wgt_minerva_v1);
            h_CryoVertex_Z_Downstream_ConcaveCap.univHist(universe)->Fill(z ,wgt_minerva_v1);
            h_CryoVertex_R_Downstream_ConcaveCap.univHist(universe)->Fill(r,wgt_minerva_v1);
            h_Distance_to_InnerTank_Downstream_ConcaveCap.univHist(universe)->Fill(Reco_distance,wgt_minerva_v1);
            h_Distance_to_InnerTank_Caps_Downstream_ConcaveCap.univHist(universe)->Fill(Reco_distance,wgt_minerva_v1);


            h_MuonDOCA_Downstream_ConcaveCap.univHist(universe)->Fill(MuonDoca,wgt_minerva_v1);
            h_secTrk_DOCA_Downstream_ConcaveCap.univHist(universe)->Fill(SecTrkDoca,wgt_minerva_v1);
            h_secTrk_tracklength_Downstream_ConcaveCap.univHist(universe)->Fill(minervaTrkLength,wgt_minerva_v1);

            h_Distance_to_downstreamCap_Downstream_ConcaveCap.univHist(universe)->Fill(dist_downstreamCap,wgt_minerva_v1);
            h_Distance_to_upstreamCap_Downstream_ConcaveCap.univHist(universe)->Fill(dist_upstreamCap,wgt_minerva_v1);


            h_CryoVertex_X_Downstream_ConcaveCap_resolution_RECO.univHist(universe)->Fill(x_resolution,wgt_minerva_v1);
            h_CryoVertex_X_Downstream_ConcaveCap_percentresolution_RECO.univHist(universe)->Fill(x_resolution/x_true,wgt_minerva_v1);
            h_CryoVertex_Y_Downstream_ConcaveCap_resolution_RECO.univHist(universe)->Fill(y_resolution,wgt_minerva_v1);
            h_CryoVertex_Y_Downstream_ConcaveCap_percentresolution_RECO.univHist(universe)->Fill(y_resolution/y_true,wgt_minerva_v1);
            h_CryoVertex_R_Downstream_ConcaveCap_resolution_RECO.univHist(universe)->Fill(r_resolution,wgt_minerva_v1);
            h_CryoVertex_R_Downstream_ConcaveCap_percentresolution_RECO.univHist(universe)->Fill(r_resolution/r_true,wgt_minerva_v1);
            h_CryoVertex_Z_Downstream_ConcaveCap_resolution_RECO.univHist(universe)->Fill(z_resolution,wgt_minerva_v1);
            h_CryoVertex_Z_Downstream_ConcaveCap_percentresolution_RECO.univHist(universe)->Fill(z_resolution/z_true,wgt_minerva_v1);


            if(Cylindrical_CutAboutZero(r)== true){
              h_CryoVertex_Z_RCut_Downstream_ConcaveCap.univHist(universe)->Fill(z ,wgt_minerva_v1);
              h_CryoVertex_X_RCut_Downstream_ConcaveCap.univHist(universe)->Fill(x ,wgt_minerva_v1);
              h_CryoVertex_Y_RCut_Downstream_ConcaveCap.univHist(universe)->Fill(y ,wgt_minerva_v1);
              h_CryoVertex_R_RCut_Downstream_ConcaveCap.univHist(universe)->Fill(r,wgt_minerva_v1);
              h_Distance_to_downstreamCap_RCut_Downstream_ConcaveCap.univHist(universe)->Fill(dist_downstreamCap,wgt_minerva_v1);
              h_Distance_to_upstreamCap_RCut_Downstream_ConcaveCap.univHist(universe)->Fill(dist_upstreamCap,wgt_minerva_v1);
            }


          }

          else{std::cout<<"ABSURDITY !! Event Failed to be in a  CryoRegion: Something Wrong"<<std::endl; assert(false);}

          h_MuonE.univHist(universe)->Fill(Emu,wgt_minerva_v1);
          h_MuonPZ.univHist(universe)->Fill(PZ,wgt_minerva_v1);
          h_MuonPT.univHist(universe)->Fill(PT,wgt_minerva_v1);
          h_MuonTheta.univHist(universe)->Fill(Theta*TMath::RadToDeg(),wgt_minerva_v1);
          h_CryoVertex_X.univHist(universe)->Fill(x ,wgt_minerva_v1);
          h_CryoVertex_Y.univHist(universe)->Fill(y ,wgt_minerva_v1);
          h_CryoVertex_Z.univHist(universe)->Fill(z ,wgt_minerva_v1);
          h_CryoVertex_R.univHist(universe)->Fill(r,wgt_minerva_v1);
          h_Distance_to_InnerTank.univHist(universe)->Fill(Reco_distance,wgt_minerva_v1);
          h_Distance_to_downstreamCap.univHist(universe)->Fill(dist_downstreamCap,wgt_minerva_v1);
          h_Distance_to_upstreamCap.univHist(universe)->Fill(dist_upstreamCap,wgt_minerva_v1);

          h_MuonDOCA.univHist(universe)->Fill(MuonDoca,wgt_minerva_v1);
          h_secTrk_DOCA.univHist(universe)->Fill(SecTrkDoca,wgt_minerva_v1);
          h_secTrk_tracklength.univHist(universe)->Fill(minervaTrkLength,wgt_minerva_v1);

          h_CryoVertex_X_resolution_RECO.univHist(universe)->Fill(x_resolution,wgt_minerva_v1);
          h_CryoVertex_X_percentresolution_RECO.univHist(universe)->Fill(x_resolution/x_true,wgt_minerva_v1);
          h_CryoVertex_Y_resolution_RECO.univHist(universe)->Fill(y_resolution,wgt_minerva_v1);
          h_CryoVertex_Y_percentresolution_RECO.univHist(universe)->Fill(y_resolution/y_true,wgt_minerva_v1);
          h_CryoVertex_R_resolution_RECO.univHist(universe)->Fill(r_resolution,wgt_minerva_v1);
          h_CryoVertex_R_percentresolution_RECO.univHist(universe)->Fill(r_resolution/r_true,wgt_minerva_v1);
          h_CryoVertex_Z_resolution_RECO.univHist(universe)->Fill(z_resolution,wgt_minerva_v1);
          h_CryoVertex_Z_percentresolution_RECO.univHist(universe)->Fill(z_resolution/z_true,wgt_minerva_v1);


          if(Cylindrical_CutAboutZero(r)== true){
            h_Distance_to_downstreamCap_RCut.univHist(universe)->Fill(dist_downstreamCap,wgt_minerva_v1);
            h_Distance_to_upstreamCap_RCut.univHist(universe)->Fill(dist_upstreamCap,wgt_minerva_v1);
            h_CryoVertex_Z_RCut.univHist(universe)->Fill(z ,wgt_minerva_v1);
            h_CryoVertex_X_RCut.univHist(universe)->Fill(x ,wgt_minerva_v1);
            h_CryoVertex_Y_RCut.univHist(universe)->Fill(y ,wgt_minerva_v1);
            h_CryoVertex_R_RCut.univHist(universe)->Fill(r,wgt_minerva_v1);


          }


          if(isCV(*universe)){





            if(Cylindrical_CutAboutZero(r)== true){
              h_CryoVertex_Z_RCut_Material.GetComponentHist(Material_type_Event)->Fill(z, wgt_minerva_v1);
              h_Distance_to_upstreamCap_RCut_Material.GetComponentHist(Material_type_Event)->Fill(dist_upstreamCap, wgt_minerva_v1);
              h_Distance_to_downstreamCap_RCut_Material.GetComponentHist(Material_type_Event)->Fill(dist_downstreamCap, wgt_minerva_v1);

              h_CryoVertex_X_RCut_Material.GetComponentHist(Material_type_Event)->Fill(x, wgt_minerva_v1);
              h_CryoVertex_Y_RCut_Material.GetComponentHist(Material_type_Event)->Fill(y, wgt_minerva_v1);
              h_CryoVertex_R_RCut_Material.GetComponentHist(Material_type_Event)->Fill(r, wgt_minerva_v1);

            }

            if(CryoTankRegion_type==kUpstream_head)
            {
              h_MuonE_UpstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(Emu, wgt_minerva_v1);
              h_MuonPZ_UpstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(PZ, wgt_minerva_v1);
              h_MuonPT_UpstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(PT, wgt_minerva_v1);
              h_MuonTheta_UpstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(Theta*toDegs, wgt_minerva_v1);
              h_CryoVertex_X_UpstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(x, wgt_minerva_v1);
              h_CryoVertex_Y_UpstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(y, wgt_minerva_v1);
              h_CryoVertex_R_UpstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(r, wgt_minerva_v1);
              h_CryoVertex_Z_UpstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(z, wgt_minerva_v1);

              h_Distance_to_InnerTank_UpstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(Reco_distance, wgt_minerva_v1);
              h_Distance_to_InnerTank_Caps_UpstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(Reco_distance, wgt_minerva_v1);
              h_MuonDOCA_UpstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(MuonDoca, wgt_minerva_v1);
              h_secTrk_DOCA_UpstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(SecTrkDoca, wgt_minerva_v1);
              h_secTrk_tracklength_UpstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(minervaTrkLength, wgt_minerva_v1);
              h_Distance_to_downstreamCap_UpstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(dist_downstreamCap, wgt_minerva_v1);
              h_Distance_to_upstreamCap_UpstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(dist_upstreamCap, wgt_minerva_v1);


              h_CryoVertex_X_UpstreamCap_resolution_Material.GetComponentHist(Material_type_Event)->Fill(x_resolution, wgt_minerva_v1);
              h_CryoVertex_Y_UpstreamCap_resolution_Material.GetComponentHist(Material_type_Event)->Fill(y_resolution, wgt_minerva_v1);
              h_CryoVertex_R_UpstreamCap_resolution_Material.GetComponentHist(Material_type_Event)->Fill(r_resolution, wgt_minerva_v1);
              h_CryoVertex_Z_UpstreamCap_resolution_Material.GetComponentHist(Material_type_Event)->Fill(z_resolution, wgt_minerva_v1);
              h_Mig_Vertex_X_UpstreamCap->Fill(x,x_true,wgt_minerva_v1);
              h_Mig_Vertex_Y_UpstreamCap->Fill(y,y_true,wgt_minerva_v1);
              h_Mig_Vertex_R_UpstreamCap->Fill(r,r_true,wgt_minerva_v1);
              h_Mig_Vertex_Z_UpstreamCap->Fill(z,z_true,wgt_minerva_v1);


              h_CryoVertex_Z_UpstreamCap_TrackType.GetComponentHist(Track_type_Event)->Fill(z, wgt_minerva_v1);
              h_CryoVertex_X_UpstreamCap_TrackType.GetComponentHist(Track_type_Event)->Fill(x, wgt_minerva_v1);
              h_CryoVertex_Y_UpstreamCap_TrackType.GetComponentHist(Track_type_Event)->Fill(y, wgt_minerva_v1);
              h_CryoVertex_R_UpstreamCap_TrackType.GetComponentHist(Track_type_Event)->Fill(r, wgt_minerva_v1);
              h_CryoVertex_Z_UpstreamCap_vertex.GetComponentHist( VertexOption_type)->Fill(z, wgt_minerva_v1);
              h_CryoVertex_X_UpstreamCap_vertex.GetComponentHist( VertexOption_type)->Fill(x, wgt_minerva_v1);
              h_CryoVertex_Y_UpstreamCap_vertex.GetComponentHist( VertexOption_type)->Fill(y, wgt_minerva_v1);
              h_CryoVertex_R_UpstreamCap_vertex.GetComponentHist( VertexOption_type)->Fill(r, wgt_minerva_v1);
              h_CryoVertex_Z_UpstreamCap_Ntracks.GetComponentHist(boolNTrack_Type)->Fill(z, wgt_minerva_v1);
              h_CryoVertex_X_UpstreamCap_Ntracks.GetComponentHist(boolNTrack_Type)->Fill(x, wgt_minerva_v1);
              h_CryoVertex_Y_UpstreamCap_Ntracks.GetComponentHist(boolNTrack_Type)->Fill(y, wgt_minerva_v1);
              h_CryoVertex_R_UpstreamCap_Ntracks.GetComponentHist(boolNTrack_Type)->Fill(r, wgt_minerva_v1);


              if(Cylindrical_CutAboutZero(r)== true){
                h_CryoVertex_Z_RCut_UpstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(z, wgt_minerva_v1);
                h_Distance_to_downstreamCap_RCut_UpstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(dist_downstreamCap, wgt_minerva_v1);
                h_Distance_to_upstreamCap_RCut_UpstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(dist_upstreamCap, wgt_minerva_v1);
                h_CryoVertex_X_RCut_UpstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(x, wgt_minerva_v1);
                h_CryoVertex_Y_RCut_UpstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(y, wgt_minerva_v1);
                h_CryoVertex_R_RCut_UpstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(r, wgt_minerva_v1);

              }




            }
            else if(CryoTankRegion_type==kCenter)
            {
              h_MuonE_Barrel_Material.GetComponentHist(Material_type_Event)->Fill(Emu, wgt_minerva_v1);
              h_MuonPZ_Barrel_Material.GetComponentHist(Material_type_Event)->Fill(PZ, wgt_minerva_v1);
              h_MuonPT_Barrel_Material.GetComponentHist(Material_type_Event)->Fill(PT, wgt_minerva_v1);
              h_MuonTheta_Barrel_Material.GetComponentHist(Material_type_Event)->Fill(Theta*toDegs, wgt_minerva_v1);
              h_CryoVertex_X_Barrel_Material.GetComponentHist(Material_type_Event)->Fill(x, wgt_minerva_v1);
              h_CryoVertex_Y_Barrel_Material.GetComponentHist(Material_type_Event)->Fill(y, wgt_minerva_v1);
              h_CryoVertex_Z_Barrel_Material.GetComponentHist(Material_type_Event)->Fill(z, wgt_minerva_v1);
              h_CryoVertex_R_Barrel_Material.GetComponentHist(Material_type_Event)->Fill(r, wgt_minerva_v1);
              h_Distance_to_InnerTank_Barrel_Material.GetComponentHist(Material_type_Event)->Fill(Reco_distance, wgt_minerva_v1);
              h_Distance_to_InnerTank_Barrel_Barrel_Material.GetComponentHist(Material_type_Event)->Fill(Reco_distance, wgt_minerva_v1);
              h_MuonDOCA_Barrel_Material.GetComponentHist(Material_type_Event)->Fill(MuonDoca, wgt_minerva_v1);
              h_secTrk_DOCA_Barrel_Material.GetComponentHist(Material_type_Event)->Fill(SecTrkDoca, wgt_minerva_v1);
              h_secTrk_tracklength_Barrel_Material.GetComponentHist(Material_type_Event)->Fill(minervaTrkLength, wgt_minerva_v1);

              h_Distance_to_downstreamCap_Barrel_Material.GetComponentHist(Material_type_Event)->Fill(dist_downstreamCap, wgt_minerva_v1);
              h_Distance_to_upstreamCap_Barrel_Material.GetComponentHist(Material_type_Event)->Fill(dist_upstreamCap, wgt_minerva_v1);
              h_CryoVertex_X_Barrel_resolution_Material.GetComponentHist(Material_type_Event)->Fill(x_resolution, wgt_minerva_v1);
              h_CryoVertex_Y_Barrel_resolution_Material.GetComponentHist(Material_type_Event)->Fill(y_resolution, wgt_minerva_v1);
              h_CryoVertex_R_Barrel_resolution_Material.GetComponentHist(Material_type_Event)->Fill(r_resolution, wgt_minerva_v1);
              h_CryoVertex_Z_Barrel_resolution_Material.GetComponentHist(Material_type_Event)->Fill(z_resolution, wgt_minerva_v1);
              h_Mig_Vertex_X_Barrel->Fill(x,x_true,wgt_minerva_v1);
              h_Mig_Vertex_Y_Barrel->Fill(y,y_true,wgt_minerva_v1);
              h_Mig_Vertex_R_Barrel->Fill(r,r_true,wgt_minerva_v1);
              h_Mig_Vertex_Z_Barrel->Fill(z,z_true,wgt_minerva_v1);


              h_CryoVertex_Z_Barrel_TrackType.GetComponentHist(Track_type_Event)->Fill(z, wgt_minerva_v1);
              h_CryoVertex_X_Barrel_TrackType.GetComponentHist(Track_type_Event)->Fill(x, wgt_minerva_v1);
              h_CryoVertex_Y_Barrel_TrackType.GetComponentHist(Track_type_Event)->Fill(y, wgt_minerva_v1);
              h_CryoVertex_R_Barrel_TrackType.GetComponentHist(Track_type_Event)->Fill(r, wgt_minerva_v1);
              h_CryoVertex_Z_Barrel_vertex.GetComponentHist( VertexOption_type)->Fill(z, wgt_minerva_v1);
              h_CryoVertex_X_Barrel_vertex.GetComponentHist( VertexOption_type)->Fill(x, wgt_minerva_v1);
              h_CryoVertex_Y_Barrel_vertex.GetComponentHist( VertexOption_type)->Fill(y, wgt_minerva_v1);
              h_CryoVertex_R_Barrel_vertex.GetComponentHist( VertexOption_type)->Fill(r, wgt_minerva_v1);
              h_CryoVertex_Z_Barrel_Ntracks.GetComponentHist(boolNTrack_Type)->Fill(z, wgt_minerva_v1);
              h_CryoVertex_X_Barrel_Ntracks.GetComponentHist(boolNTrack_Type)->Fill(x, wgt_minerva_v1);
              h_CryoVertex_Y_Barrel_Ntracks.GetComponentHist(boolNTrack_Type)->Fill(y, wgt_minerva_v1);
              h_CryoVertex_R_Barrel_Ntracks.GetComponentHist(boolNTrack_Type)->Fill(r, wgt_minerva_v1);


              if(Cylindrical_CutAboutZero(r)== true){
                h_CryoVertex_Z_RCut_Barrel_Material.GetComponentHist(Material_type_Event)->Fill(z, wgt_minerva_v1);
                h_Distance_to_downstreamCap_RCut_Barrel_Material.GetComponentHist(Material_type_Event)->Fill(dist_downstreamCap, wgt_minerva_v1);
                h_Distance_to_upstreamCap_RCut_Barrel_Material.GetComponentHist(Material_type_Event)->Fill(dist_upstreamCap, wgt_minerva_v1);

                h_CryoVertex_X_RCut_Barrel_Material.GetComponentHist(Material_type_Event)->Fill(x, wgt_minerva_v1);
                h_CryoVertex_Y_RCut_Barrel_Material.GetComponentHist(Material_type_Event)->Fill(y, wgt_minerva_v1);
                h_CryoVertex_R_RCut_Barrel_Material.GetComponentHist(Material_type_Event)->Fill(r, wgt_minerva_v1);

              }


            }
            else if(CryoTankRegion_type==kDownstream_head)
            {
              h_MuonE_DownstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(Emu, wgt_minerva_v1);
              h_MuonPZ_DownstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(PZ, wgt_minerva_v1);
              h_MuonPT_DownstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(PT, wgt_minerva_v1);
              h_MuonTheta_DownstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(Theta*toDegs, wgt_minerva_v1);
              h_CryoVertex_X_DownstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(x, wgt_minerva_v1);
              h_CryoVertex_Y_DownstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(y, wgt_minerva_v1);
              h_CryoVertex_Z_DownstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(z, wgt_minerva_v1);
              h_CryoVertex_R_DownstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(r, wgt_minerva_v1);
              h_Distance_to_InnerTank_DownstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(Reco_distance, wgt_minerva_v1);
              h_Distance_to_InnerTank_Caps_DownstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(Reco_distance, wgt_minerva_v1);
              h_MuonDOCA_DownstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(MuonDoca, wgt_minerva_v1);
              h_secTrk_DOCA_DownstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(SecTrkDoca, wgt_minerva_v1);
              h_secTrk_tracklength_DownstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(minervaTrkLength, wgt_minerva_v1);

              h_Distance_to_downstreamCap_DownstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(dist_downstreamCap, wgt_minerva_v1);
              h_Distance_to_upstreamCap_DownstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(dist_upstreamCap, wgt_minerva_v1);


              h_CryoVertex_X_DownstreamCap_resolution_Material.GetComponentHist(Material_type_Event)->Fill(x_resolution, wgt_minerva_v1);
              h_CryoVertex_Y_DownstreamCap_resolution_Material.GetComponentHist(Material_type_Event)->Fill(y_resolution, wgt_minerva_v1);
              h_CryoVertex_R_DownstreamCap_resolution_Material.GetComponentHist(Material_type_Event)->Fill(r_resolution, wgt_minerva_v1);
              h_CryoVertex_Z_DownstreamCap_resolution_Material.GetComponentHist(Material_type_Event)->Fill(z_resolution, wgt_minerva_v1);

              h_Mig_Vertex_X_DownstreamCap->Fill(x,x_true,wgt_minerva_v1);
              h_Mig_Vertex_Y_DownstreamCap->Fill(y,y_true,wgt_minerva_v1);
              h_Mig_Vertex_R_DownstreamCap->Fill(r,r_true,wgt_minerva_v1);
              h_Mig_Vertex_Z_DownstreamCap->Fill(z,z_true,wgt_minerva_v1);

              h_CryoVertex_Z_DownstreamCap_TrackType.GetComponentHist(Track_type_Event)->Fill(z, wgt_minerva_v1);
              h_CryoVertex_X_DownstreamCap_TrackType.GetComponentHist(Track_type_Event)->Fill(x, wgt_minerva_v1);
              h_CryoVertex_Y_DownstreamCap_TrackType.GetComponentHist(Track_type_Event)->Fill(y, wgt_minerva_v1);
              h_CryoVertex_R_DownstreamCap_TrackType.GetComponentHist(Track_type_Event)->Fill(r, wgt_minerva_v1);
              h_CryoVertex_Z_DownstreamCap_vertex.GetComponentHist( VertexOption_type)->Fill(z, wgt_minerva_v1);
              h_CryoVertex_X_DownstreamCap_vertex.GetComponentHist( VertexOption_type)->Fill(x, wgt_minerva_v1);
              h_CryoVertex_Y_DownstreamCap_vertex.GetComponentHist( VertexOption_type)->Fill(y, wgt_minerva_v1);
              h_CryoVertex_R_DownstreamCap_vertex.GetComponentHist( VertexOption_type)->Fill(r, wgt_minerva_v1);
              h_CryoVertex_Z_DownstreamCap_Ntracks.GetComponentHist(boolNTrack_Type)->Fill(z, wgt_minerva_v1);
              h_CryoVertex_X_DownstreamCap_Ntracks.GetComponentHist(boolNTrack_Type)->Fill(x, wgt_minerva_v1);
              h_CryoVertex_Y_DownstreamCap_Ntracks.GetComponentHist(boolNTrack_Type)->Fill(y, wgt_minerva_v1);
              h_CryoVertex_R_DownstreamCap_Ntracks.GetComponentHist(boolNTrack_Type)->Fill(r, wgt_minerva_v1);

              if(Cylindrical_CutAboutZero(r)== true){
                h_CryoVertex_Z_RCut_DownstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(z, wgt_minerva_v1);
                h_Distance_to_downstreamCap_RCut_DownstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(dist_downstreamCap, wgt_minerva_v1);
                h_Distance_to_upstreamCap_RCut_DownstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(dist_upstreamCap, wgt_minerva_v1);

                h_CryoVertex_X_RCut_DownstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(x, wgt_minerva_v1);
                h_CryoVertex_Y_RCut_DownstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(y, wgt_minerva_v1);
                h_CryoVertex_R_RCut_DownstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(r, wgt_minerva_v1);
              }

            }
            else if(CryoTankRegion_type==kDownstream_ConcaveCap)
            {
              h_MuonE_Downstream_ConcaveCap_Material.GetComponentHist(Material_type_Event)->Fill(Emu, wgt_minerva_v1);
              h_MuonPZ_Downstream_ConcaveCap_Material.GetComponentHist(Material_type_Event)->Fill(PZ, wgt_minerva_v1);
              h_MuonPT_Downstream_ConcaveCap_Material.GetComponentHist(Material_type_Event)->Fill(PT, wgt_minerva_v1);
              h_MuonTheta_Downstream_ConcaveCap_Material.GetComponentHist(Material_type_Event)->Fill(Theta*toDegs, wgt_minerva_v1);
              h_CryoVertex_X_Downstream_ConcaveCap_Material.GetComponentHist(Material_type_Event)->Fill(x, wgt_minerva_v1);
              h_CryoVertex_Y_Downstream_ConcaveCap_Material.GetComponentHist(Material_type_Event)->Fill(y, wgt_minerva_v1);
              h_CryoVertex_Z_Downstream_ConcaveCap_Material.GetComponentHist(Material_type_Event)->Fill(z, wgt_minerva_v1);
              h_CryoVertex_R_Downstream_ConcaveCap_Material.GetComponentHist(Material_type_Event)->Fill(r, wgt_minerva_v1);
              h_Distance_to_InnerTank_Downstream_ConcaveCap_Material.GetComponentHist(Material_type_Event)->Fill(Reco_distance, wgt_minerva_v1);
              h_Distance_to_InnerTank_Caps_Downstream_ConcaveCap_Material.GetComponentHist(Material_type_Event)->Fill(Reco_distance, wgt_minerva_v1);
              h_MuonDOCA_Downstream_ConcaveCap_Material.GetComponentHist(Material_type_Event)->Fill(MuonDoca, wgt_minerva_v1);
              h_secTrk_DOCA_Downstream_ConcaveCap_Material.GetComponentHist(Material_type_Event)->Fill(SecTrkDoca, wgt_minerva_v1);
              h_secTrk_tracklength_Downstream_ConcaveCap_Material.GetComponentHist(Material_type_Event)->Fill(minervaTrkLength, wgt_minerva_v1);

              h_Distance_to_downstreamCap_Downstream_ConcaveCap_Material.GetComponentHist(Material_type_Event)->Fill(dist_downstreamCap, wgt_minerva_v1);
              h_Distance_to_upstreamCap_Downstream_ConcaveCap_Material.GetComponentHist(Material_type_Event)->Fill(dist_upstreamCap, wgt_minerva_v1);



              h_CryoVertex_X_Downstream_ConcaveCap_resolution_Material.GetComponentHist(Material_type_Event)->Fill(x_resolution, wgt_minerva_v1);
              h_CryoVertex_Y_Downstream_ConcaveCap_resolution_Material.GetComponentHist(Material_type_Event)->Fill(y_resolution, wgt_minerva_v1);
              h_CryoVertex_R_Downstream_ConcaveCap_resolution_Material.GetComponentHist(Material_type_Event)->Fill(r_resolution, wgt_minerva_v1);
              h_CryoVertex_Z_Downstream_ConcaveCap_resolution_Material.GetComponentHist(Material_type_Event)->Fill(z_resolution, wgt_minerva_v1);


              h_Mig_Vertex_X_Downstream_ConcaveCap->Fill(x,x_true,wgt_minerva_v1);
              h_Mig_Vertex_Y_Downstream_ConcaveCap->Fill(y,y_true,wgt_minerva_v1);
              h_Mig_Vertex_R_Downstream_ConcaveCap->Fill(r,r_true,wgt_minerva_v1);
              h_Mig_Vertex_Z_Downstream_ConcaveCap->Fill(z,z_true,wgt_minerva_v1);


              h_CryoVertex_Z_Downstream_ConcaveCap_TrackType.GetComponentHist(Track_type_Event)->Fill(z, wgt_minerva_v1);
              h_CryoVertex_X_Downstream_ConcaveCap_TrackType.GetComponentHist(Track_type_Event)->Fill(x, wgt_minerva_v1);
              h_CryoVertex_Y_Downstream_ConcaveCap_TrackType.GetComponentHist(Track_type_Event)->Fill(y, wgt_minerva_v1);
              h_CryoVertex_R_Downstream_ConcaveCap_TrackType.GetComponentHist(Track_type_Event)->Fill(r, wgt_minerva_v1);
              h_CryoVertex_Z_Downstream_ConcaveCap_vertex.GetComponentHist( VertexOption_type)->Fill(z, wgt_minerva_v1);
              h_CryoVertex_X_Downstream_ConcaveCap_vertex.GetComponentHist( VertexOption_type)->Fill(x, wgt_minerva_v1);
              h_CryoVertex_Y_Downstream_ConcaveCap_vertex.GetComponentHist( VertexOption_type)->Fill(y, wgt_minerva_v1);
              h_CryoVertex_R_Downstream_ConcaveCap_vertex.GetComponentHist( VertexOption_type)->Fill(r, wgt_minerva_v1);
              h_CryoVertex_Z_Downstream_ConcaveCap_Ntracks.GetComponentHist(boolNTrack_Type)->Fill(z, wgt_minerva_v1);
              h_CryoVertex_X_Downstream_ConcaveCap_Ntracks.GetComponentHist(boolNTrack_Type)->Fill(x, wgt_minerva_v1);
              h_CryoVertex_Y_Downstream_ConcaveCap_Ntracks.GetComponentHist(boolNTrack_Type)->Fill(y, wgt_minerva_v1);
              h_CryoVertex_R_Downstream_ConcaveCap_Ntracks.GetComponentHist(boolNTrack_Type)->Fill(r, wgt_minerva_v1);


              if(Cylindrical_CutAboutZero(r)== true){
                h_CryoVertex_Z_RCut_Downstream_ConcaveCap_Material.GetComponentHist(Material_type_Event)->Fill(z, wgt_minerva_v1);
                h_Distance_to_downstreamCap_RCut_Downstream_ConcaveCap_Material.GetComponentHist(Material_type_Event)->Fill(dist_downstreamCap, wgt_minerva_v1);
                h_Distance_to_upstreamCap_RCut_Downstream_ConcaveCap_Material.GetComponentHist(Material_type_Event)->Fill(dist_upstreamCap, wgt_minerva_v1);
                h_CryoVertex_X_RCut_Downstream_ConcaveCap_Material.GetComponentHist(Material_type_Event)->Fill(x, wgt_minerva_v1);
                h_CryoVertex_Y_RCut_Downstream_ConcaveCap_Material.GetComponentHist(Material_type_Event)->Fill(y, wgt_minerva_v1);
                h_CryoVertex_R_RCut_Downstream_ConcaveCap_Material.GetComponentHist(Material_type_Event)->Fill(r, wgt_minerva_v1);

              }


            }


            else{std::cout<<"ABSURDITY !! Event Failed to be in a  CryoRegion: Something Wrong"<<std::endl; assert(false);}

            h_MuonE_Material.GetComponentHist(Material_type_Event)->Fill(Emu, wgt_minerva_v1);
            h_MuonPZ_Material.GetComponentHist(Material_type_Event)->Fill(PZ, wgt_minerva_v1);
            h_MuonPT_Material.GetComponentHist(Material_type_Event)->Fill(PT, wgt_minerva_v1);
            h_MuonTheta_Material.GetComponentHist(Material_type_Event)->Fill(Theta*toDegs, wgt_minerva_v1);
            h_CryoVertex_X_Material.GetComponentHist(Material_type_Event)->Fill(x, wgt_minerva_v1);
            h_CryoVertex_Y_Material.GetComponentHist(Material_type_Event)->Fill(y, wgt_minerva_v1);
            h_CryoVertex_Z_Material.GetComponentHist(Material_type_Event)->Fill(z, wgt_minerva_v1);
            h_CryoVertex_R_Material.GetComponentHist(Material_type_Event)->Fill(r, wgt_minerva_v1);
            h_Distance_to_InnerTank_Material.GetComponentHist(Material_type_Event)->Fill(Reco_distance, wgt_minerva_v1);
            h_MuonDOCA_Material.GetComponentHist(Material_type_Event)->Fill(MuonDoca, wgt_minerva_v1);
            h_secTrk_DOCA_Material.GetComponentHist(Material_type_Event)->Fill(SecTrkDoca, wgt_minerva_v1);
            h_secTrk_tracklength_Material.GetComponentHist(Material_type_Event)->Fill(minervaTrkLength, wgt_minerva_v1);

            h_MuonE_CryoRegions.GetComponentHist(CryoTankRegion_type)->Fill(Emu, wgt_minerva_v1);
            h_MuonPZ_CryoRegions.GetComponentHist(CryoTankRegion_type)->Fill(PZ, wgt_minerva_v1);
            h_MuonPT_CryoRegions.GetComponentHist(CryoTankRegion_type)->Fill(PT, wgt_minerva_v1);
            h_MuonTheta_CryoRegions.GetComponentHist(CryoTankRegion_type)->Fill(Theta*toDegs, wgt_minerva_v1);
            h_CryoVertex_X_CryoRegions.GetComponentHist(CryoTankRegion_type)->Fill(x, wgt_minerva_v1);
            h_CryoVertex_Y_CryoRegions.GetComponentHist(CryoTankRegion_type)->Fill(y, wgt_minerva_v1);
            h_CryoVertex_Z_CryoRegions.GetComponentHist(CryoTankRegion_type)->Fill(z, wgt_minerva_v1);
            h_CryoVertex_R_CryoRegions.GetComponentHist(CryoTankRegion_type)->Fill(r, wgt_minerva_v1);
            h_Distance_to_InnerTank_CryoRegions.GetComponentHist(CryoTankRegion_type)->Fill(Reco_distance, wgt_minerva_v1);

            h_CryoVertex_X_resolution_Material.GetComponentHist(Material_type_Event)->Fill(x_resolution, wgt_minerva_v1);
            h_CryoVertex_Y_resolution_Material.GetComponentHist(Material_type_Event)->Fill(y_resolution, wgt_minerva_v1);
            h_CryoVertex_R_resolution_Material.GetComponentHist(Material_type_Event)->Fill(r_resolution, wgt_minerva_v1);
            h_CryoVertex_Z_resolution_Material.GetComponentHist(Material_type_Event)->Fill(z_resolution, wgt_minerva_v1);

            h_Mig_Vertex_X->Fill(x,x_true,wgt_minerva_v1);
            h_Mig_Vertex_Y->Fill(y,y_true,wgt_minerva_v1);
            h_Mig_Vertex_R->Fill(r,r_true,wgt_minerva_v1);
            h_Mig_Vertex_Z->Fill(z,z_true,wgt_minerva_v1);
            h_Distance_to_downstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(dist_downstreamCap, wgt_minerva_v1);
            h_Distance_to_upstreamCap_Material.GetComponentHist(Material_type_Event)->Fill(dist_upstreamCap, wgt_minerva_v1);

            h_CryoVertex_Z_TrackType.GetComponentHist(Track_type_Event)->Fill(z, wgt_minerva_v1);
            h_CryoVertex_Z_vertex.GetComponentHist( VertexOption_type)->Fill(z, wgt_minerva_v1);
            h_CryoVertex_Z_Ntracks.GetComponentHist(boolNTrack_Type)->Fill(z, wgt_minerva_v1);


            //////////////////////////////////////////////////////////////////////////////////
            // Region 14
            //////////////////////////////////////////////////////////////////////////////////






            HistFolio_Region14_Map_Vertex_X.at(CryoTankRegion14).GetComponentHist(Material_type_Event)->Fill(x,wgt_minerva_v1);
            HistFolio_Region14_Map_Vectex_Y.at(CryoTankRegion14).GetComponentHist(Material_type_Event)->Fill(y,wgt_minerva_v1);
            HistFolio_Region14_Map_Vectex_Z.at(CryoTankRegion14).GetComponentHist(Material_type_Event)->Fill(z,wgt_minerva_v1);
            HistFolio_Region14_Map_Vectex_R.at(CryoTankRegion14).GetComponentHist(Material_type_Event)->Fill(r,wgt_minerva_v1);
            HistFolio_Region14_Map_TRUE_Vertex_X.at(CryoTankRegion14).GetComponentHist(Material_type_Event)->Fill(x_true,wgt_minerva_v1);
            HistFolio_Region14_Map_TRUE_Vectex_Y.at(CryoTankRegion14).GetComponentHist(Material_type_Event)->Fill(y_true,wgt_minerva_v1);
            HistFolio_Region14_Map_TRUE_Vectex_Z.at(CryoTankRegion14).GetComponentHist(Material_type_Event)->Fill(z_true,wgt_minerva_v1);
            HistFolio_Region14_Map_TRUE_Vectex_R.at(CryoTankRegion14).GetComponentHist(Material_type_Event)->Fill(r_true,wgt_minerva_v1);
            HistFolio_Region14_Map_Distance_to_NearestWall.at(CryoTankRegion14).GetComponentHist(Material_type_Event)->Fill(Reco_distance,wgt_minerva_v1);
            HistFolio_Region14_Map_h_secTrk_Tracklength.at(CryoTankRegion14).GetComponentHist(Material_type_Event)->Fill(minervaTrkLength,wgt_minerva_v1);
            HistFolio_Region14_Map_secTrk_DOCA.at(CryoTankRegion14).GetComponentHist(Material_type_Event)->Fill(SecTrkDoca,wgt_minerva_v1);
            HistFolio_Region14_Map_Muon_DOCA.at(CryoTankRegion14).GetComponentHist(Material_type_Event)->Fill(MuonDoca,wgt_minerva_v1);
            HistFolio_Region14_Map_MuonPZ.at(CryoTankRegion14).GetComponentHist(Material_type_Event)->Fill(PZ,wgt_minerva_v1);
            HistFolio_Region14_Map_MuonPT.at(CryoTankRegion14).GetComponentHist(Material_type_Event)->Fill(PT,wgt_minerva_v1);
            HistFolio_Region14_Map_MuonTheta.at(CryoTankRegion14).GetComponentHist(Material_type_Event)->Fill(Theta*toDegs,wgt_minerva_v1);
            HistFolio_Region14_Map_MuonE.at(CryoTankRegion14).GetComponentHist(Material_type_Event)->Fill(Emu,wgt_minerva_v1);







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

  h_MuonE_UpstreamCap.SyncCVHistos();
  h_MuonPZ_UpstreamCap.SyncCVHistos();
  h_MuonPT_UpstreamCap.SyncCVHistos();
  h_MuonTheta_UpstreamCap.SyncCVHistos();
  h_CryoVertex_X_UpstreamCap.SyncCVHistos();
  h_CryoVertex_Y_UpstreamCap.SyncCVHistos();
  h_CryoVertex_Z_UpstreamCap.SyncCVHistos();
  h_CryoVertex_Z_RCut.SyncCVHistos();
  h_CryoVertex_Z_RCut_UpstreamCap.SyncCVHistos();
  h_CryoVertex_Z_RCut_Barrel.SyncCVHistos();
  h_CryoVertex_Z_RCut_DownstreamCap.SyncCVHistos();
  h_CryoVertex_Z_RCut_Downstream_ConcaveCap.SyncCVHistos();
  h_CryoVertex_R_UpstreamCap.SyncCVHistos();
  h_Distance_to_InnerTank_UpstreamCap.SyncCVHistos();
  h_Distance_to_InnerTank_Caps_DownstreamCap.SyncCVHistos();
  h_Distance_to_InnerTank_Caps_UpstreamCap.SyncCVHistos();
  h_Distance_to_InnerTank_Barrel_DownstreamCap.SyncCVHistos();
  h_Distance_to_InnerTank_Barrel_UpstreamCap.SyncCVHistos();



  h_MuonE_Barrel.SyncCVHistos();
  h_MuonPT_Barrel.SyncCVHistos();
  h_MuonPZ_Barrel.SyncCVHistos();
  h_MuonTheta_Barrel.SyncCVHistos();
  h_CryoVertex_X_Barrel.SyncCVHistos();
  h_CryoVertex_Y_Barrel.SyncCVHistos();
  h_CryoVertex_Z_Barrel.SyncCVHistos();
  h_CryoVertex_R_Barrel.SyncCVHistos();
  h_Distance_to_InnerTank_Barrel_Barrel.SyncCVHistos();
  h_Distance_to_InnerTank_Barrel.SyncCVHistos();

  h_MuonE_DownstreamCap.SyncCVHistos();
  h_MuonPZ_DownstreamCap.SyncCVHistos();
  h_MuonPT_DownstreamCap.SyncCVHistos();
  h_MuonTheta_DownstreamCap.SyncCVHistos();
  h_CryoVertex_X_DownstreamCap.SyncCVHistos();
  h_CryoVertex_Y_DownstreamCap.SyncCVHistos();
  h_CryoVertex_Z_DownstreamCap.SyncCVHistos();
  h_CryoVertex_R_DownstreamCap.SyncCVHistos();
  h_Distance_to_InnerTank_DownstreamCap.SyncCVHistos();

  h_MuonE_Downstream_ConcaveCap.SyncCVHistos();
  h_MuonPZ_Downstream_ConcaveCap.SyncCVHistos();
  h_MuonPT_Downstream_ConcaveCap.SyncCVHistos();
  h_MuonTheta_Downstream_ConcaveCap.SyncCVHistos();
  h_CryoVertex_X_Downstream_ConcaveCap.SyncCVHistos();
  h_CryoVertex_Y_Downstream_ConcaveCap.SyncCVHistos();
  h_CryoVertex_Z_Downstream_ConcaveCap.SyncCVHistos();
  h_CryoVertex_R_Downstream_ConcaveCap.SyncCVHistos();
  h_Distance_to_InnerTank_Downstream_ConcaveCap.SyncCVHistos();
  h_Distance_to_InnerTank_Caps_Downstream_ConcaveCap.SyncCVHistos();
  h_Distance_to_InnerTank_Barrel_Downstream_ConcaveCap.SyncCVHistos();
  h_MuonDOCA.SyncCVHistos();
  h_secTrk_DOCA.SyncCVHistos();
  h_MuonDOCA_UpstreamCap.SyncCVHistos();
  h_secTrk_DOCA_UpstreamCap.SyncCVHistos();
  h_MuonDOCA_Barrel.SyncCVHistos();
  h_secTrk_DOCA_Barrel.SyncCVHistos();
  h_MuonDOCA_DownstreamCap.SyncCVHistos();
  h_secTrk_DOCA_DownstreamCap.SyncCVHistos();
  h_MuonDOCA_Downstream_ConcaveCap.SyncCVHistos();
  h_secTrk_DOCA_Downstream_ConcaveCap.SyncCVHistos();
  h_secTrk_tracklength.SyncCVHistos();
  h_secTrk_tracklength_UpstreamCap.SyncCVHistos();
  h_secTrk_tracklength_Barrel.SyncCVHistos();
  h_secTrk_tracklength_DownstreamCap.SyncCVHistos();
  h_secTrk_tracklength_Downstream_ConcaveCap.SyncCVHistos();


  h_CryoVertex_X_resolution_RECO.SyncCVHistos();
  h_CryoVertex_X_percentresolution_RECO.SyncCVHistos();
  h_CryoVertex_Y_resolution_RECO.SyncCVHistos();
  h_CryoVertex_Y_percentresolution_RECO.SyncCVHistos();
  h_CryoVertex_R_resolution_RECO.SyncCVHistos();
  h_CryoVertex_R_percentresolution_RECO.SyncCVHistos();
  h_CryoVertex_Z_resolution_RECO.SyncCVHistos();
  h_CryoVertex_Z_percentresolution_RECO.SyncCVHistos();
  h_CryoVertex_X_UpstreamCap_resolution_RECO.SyncCVHistos();
  h_CryoVertex_X_UpstreamCap_percentresolution_RECO.SyncCVHistos();
  h_CryoVertex_Y_UpstreamCap_resolution_RECO.SyncCVHistos();
  h_CryoVertex_Y_UpstreamCap_percentresolution_RECO.SyncCVHistos();
  h_CryoVertex_R_UpstreamCap_resolution_RECO.SyncCVHistos();
  h_CryoVertex_R_UpstreamCap_percentresolution_RECO.SyncCVHistos();
  h_CryoVertex_Z_UpstreamCap_resolution_RECO.SyncCVHistos();
  h_CryoVertex_Z_UpstreamCap_percentresolution_RECO.SyncCVHistos();
  h_CryoVertex_X_Barrel_resolution_RECO.SyncCVHistos();
  h_CryoVertex_X_Barrel_percentresolution_RECO.SyncCVHistos();
  h_CryoVertex_Y_Barrel_resolution_RECO.SyncCVHistos();
  h_CryoVertex_Y_Barrel_percentresolution_RECO.SyncCVHistos();
  h_CryoVertex_R_Barrel_resolution_RECO.SyncCVHistos();
  h_CryoVertex_R_Barrel_percentresolution_RECO.SyncCVHistos();
  h_CryoVertex_Z_Barrel_resolution_RECO.SyncCVHistos();
  h_CryoVertex_Z_Barrel_percentresolution_RECO.SyncCVHistos();
  h_CryoVertex_X_DownstreamCap_resolution_RECO.SyncCVHistos();
  h_CryoVertex_X_DownstreamCap_percentresolution_RECO.SyncCVHistos();
  h_CryoVertex_Y_DownstreamCap_resolution_RECO.SyncCVHistos();
  h_CryoVertex_Y_DownstreamCap_percentresolution_RECO.SyncCVHistos();
  h_CryoVertex_R_DownstreamCap_resolution_RECO.SyncCVHistos();
  h_CryoVertex_R_DownstreamCap_percentresolution_RECO.SyncCVHistos();
  h_CryoVertex_Z_DownstreamCap_resolution_RECO.SyncCVHistos();
  h_CryoVertex_Z_DownstreamCap_percentresolution_RECO.SyncCVHistos();
  h_CryoVertex_X_Downstream_ConcaveCap_resolution_RECO.SyncCVHistos();
  h_CryoVertex_X_Downstream_ConcaveCap_percentresolution_RECO.SyncCVHistos();
  h_CryoVertex_Y_Downstream_ConcaveCap_resolution_RECO.SyncCVHistos();
  h_CryoVertex_Y_Downstream_ConcaveCap_percentresolution_RECO.SyncCVHistos();
  h_CryoVertex_R_Downstream_ConcaveCap_resolution_RECO.SyncCVHistos();
  h_CryoVertex_R_Downstream_ConcaveCap_percentresolution_RECO.SyncCVHistos();
  h_CryoVertex_Z_Downstream_ConcaveCap_resolution_RECO.SyncCVHistos();
  h_CryoVertex_Z_Downstream_ConcaveCap_percentresolution_RECO.SyncCVHistos();

  h_CryoVertex_X_resolution_TRUE_RECO.SyncCVHistos();
  h_CryoVertex_X_percentresolution_TRUE_RECO.SyncCVHistos();
  h_CryoVertex_Y_resolution_TRUE_RECO.SyncCVHistos();
  h_CryoVertex_Y_percentresolution_TRUE_RECO.SyncCVHistos();
  h_CryoVertex_R_resolution_TRUE_RECO.SyncCVHistos();
  h_CryoVertex_R_percentresolution_TRUE_RECO.SyncCVHistos();
  h_CryoVertex_Z_resolution_TRUE_RECO.SyncCVHistos();
  h_CryoVertex_Z_percentresolution_TRUE_RECO.SyncCVHistos();
  h_CryoVertex_X_UpstreamCap_resolution_TRUE_RECO.SyncCVHistos();
  h_CryoVertex_X_UpstreamCap_percentresolution_TRUE_RECO.SyncCVHistos();
  h_CryoVertex_Y_UpstreamCap_resolution_TRUE_RECO.SyncCVHistos();
  h_CryoVertex_Y_UpstreamCap_percentresolution_TRUE_RECO.SyncCVHistos();
  h_CryoVertex_R_UpstreamCap_resolution_TRUE_RECO.SyncCVHistos();
  h_CryoVertex_R_UpstreamCap_percentresolution_TRUE_RECO.SyncCVHistos();
  h_CryoVertex_Z_UpstreamCap_resolution_TRUE_RECO.SyncCVHistos();
  h_CryoVertex_Z_UpstreamCap_percentresolution_TRUE_RECO.SyncCVHistos();
  h_CryoVertex_X_Barrel_resolution_TRUE_RECO.SyncCVHistos();
  h_CryoVertex_X_Barrel_percentresolution_TRUE_RECO.SyncCVHistos();
  h_CryoVertex_Y_Barrel_resolution_TRUE_RECO.SyncCVHistos();
  h_CryoVertex_Y_Barrel_percentresolution_TRUE_RECO.SyncCVHistos();
  h_CryoVertex_R_Barrel_resolution_TRUE_RECO.SyncCVHistos();
  h_CryoVertex_R_Barrel_percentresolution_TRUE_RECO.SyncCVHistos();
  h_CryoVertex_Z_Barrel_resolution_TRUE_RECO.SyncCVHistos();
  h_CryoVertex_Z_Barrel_percentresolution_TRUE_RECO.SyncCVHistos();
  h_CryoVertex_X_DownstreamCap_resolution_TRUE_RECO.SyncCVHistos();
  h_CryoVertex_X_DownstreamCap_percentresolution_TRUE_RECO.SyncCVHistos();
  h_CryoVertex_Y_DownstreamCap_resolution_TRUE_RECO.SyncCVHistos();
  h_CryoVertex_Y_DownstreamCap_percentresolution_TRUE_RECO.SyncCVHistos();
  h_CryoVertex_R_DownstreamCap_resolution_TRUE_RECO.SyncCVHistos();
  h_CryoVertex_R_DownstreamCap_percentresolution_TRUE_RECO.SyncCVHistos();
  h_CryoVertex_Z_DownstreamCap_resolution_TRUE_RECO.SyncCVHistos();
  h_CryoVertex_Z_DownstreamCap_percentresolution_TRUE_RECO.SyncCVHistos();
  h_CryoVertex_X_Downstream_ConcaveCap_resolution_TRUE_RECO.SyncCVHistos();
  h_CryoVertex_X_Downstream_ConcaveCap_percentresolution_TRUE_RECO.SyncCVHistos();
  h_CryoVertex_Y_Downstream_ConcaveCap_resolution_TRUE_RECO.SyncCVHistos();
  h_CryoVertex_Y_Downstream_ConcaveCap_percentresolution_TRUE_RECO.SyncCVHistos();
  h_CryoVertex_R_Downstream_ConcaveCap_resolution_TRUE_RECO.SyncCVHistos();
  h_CryoVertex_R_Downstream_ConcaveCap_percentresolution_TRUE_RECO.SyncCVHistos();
  h_CryoVertex_Z_Downstream_ConcaveCap_resolution_TRUE_RECO.SyncCVHistos();
  h_CryoVertex_Z_Downstream_ConcaveCap_percentresolution_TRUE_RECO.SyncCVHistos();

  h_Distance_to_downstreamCap.SyncCVHistos();
  h_Distance_to_upstreamCap.SyncCVHistos();
  h_Distance_to_downstreamCap_UpstreamCap.SyncCVHistos();
  h_Distance_to_upstreamCap_UpstreamCap.SyncCVHistos();
  h_Distance_to_downstreamCap_Barrel.SyncCVHistos();
  h_Distance_to_upstreamCap_Barrel.SyncCVHistos();
  h_Distance_to_downstreamCap_DownstreamCap.SyncCVHistos();
  h_Distance_to_upstreamCap_DownstreamCap.SyncCVHistos();
  h_Distance_to_downstreamCap_Downstream_ConcaveCap.SyncCVHistos();
  h_Distance_to_upstreamCap_Downstream_ConcaveCap.SyncCVHistos();

  h_CryoVertex_X_RCut.SyncCVHistos();
  h_CryoVertex_Y_RCut.SyncCVHistos();
  h_CryoVertex_R_RCut.SyncCVHistos();
  h_CryoVertex_X_RCut_UpstreamCap.SyncCVHistos();
  h_CryoVertex_Y_RCut_UpstreamCap.SyncCVHistos();
  h_CryoVertex_R_RCut_UpstreamCap.SyncCVHistos();
  h_CryoVertex_X_RCut_Barrel.SyncCVHistos();
  h_CryoVertex_Y_RCut_Barrel.SyncCVHistos();
  h_CryoVertex_R_RCut_Barrel.SyncCVHistos();
  h_CryoVertex_X_RCut_DownstreamCap.SyncCVHistos();
  h_CryoVertex_Y_RCut_DownstreamCap.SyncCVHistos();
  h_CryoVertex_R_RCut_DownstreamCap.SyncCVHistos();
  h_CryoVertex_X_RCut_Downstream_ConcaveCap.SyncCVHistos();
  h_CryoVertex_Y_RCut_Downstream_ConcaveCap.SyncCVHistos();
  h_CryoVertex_R_RCut_Downstream_ConcaveCap.SyncCVHistos();


  // DrawMCWithErrorBand
//  PlotCVAndError(Muon_PZ_FULLMC.hist, "TEST");
std::string systematics_status;
if(m_RunCodeWithSystematics==true){sysmatics_status= "All_SysErrorsOn";}
else if (m_RunCodeWithSystematics==false){sysmatics_status= "StatsONLYErrors";}



  char outFileName[2024];
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

  std::string Wgts;
  if(useweights==true){Wgts= "Wgts";}
  else if (useweights==false){Wgts= "noWgts";}
  char Wgts_char[Wgts.length()+1];
  strcpy(Wgts_char, Wgts.c_str());

  std::string convolution;
  if(RunwithConvolution==true){convolution= "_Convolution";}
  else if (RunwithConvolution==false){convolution= "";}
  char convolution_char[convolution.length()+1];
  strcpy(convolution_char, convolution.c_str());

  std::string Fiduical_status;
  if( RunwithFid==true){Fiduical_status= "Fid";}
  else if (RunwithFid==false){Fiduical_status= "NoFid";}

  char Fiduical_status_char[Fiduical_status.length()+1];
  strcpy(Fiduical_status_char, Fiduical_status.c_str());

  std::string Shift_status;
  if(RunwithShift==true){Shift_status= "neg24_neg32_neg12"; }
  else if (RunwithShift==false){Shift_status= "Noshift";}
  char Shift_status_char[Shift_status.length()+1];
  strcpy(Shift_status_char, Shift_status.c_str());


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
    sprintf(outFileName, "%s_%s_%s_%s_ThreeRegion_sideBandShift_%s_%s_%s_ShiftAll%s.root", "Histograms",c,d,ErrorStatus,Shift_status_char, Wgts_char, Fiduical_status_char, convolution_char);
    std::cout << "Writing output file on Grid to: " <<outFileName << std::endl;

  }
  else{
    sprintf(outFileName, "%s/%s_%s_%s_%s_ThreeRegion_sideBandShift_%s_%s_%s_ShiftAll%s.root", rootpathway, "Histograms",c,d,ErrorStatus,Shift_status_char, Wgts_char, Fiduical_status_char, convolution_char);
    std::cout << "Writing output file to: " <<outFileName << std::endl;
  }

//ThreeRegion_sideBandShift_5_50_neg4_nowgts_noFid_ShiftAll

  //TFile *outFile(outFileName, "RECREATE");
  TFile *outFile = new TFile(outFileName,"RECREATE");
  TChain POT_branch("Meta");
  POT_branch.Add(RootName.c_str());
  //TTree *oldtree = (TTree*)file->Get("Meta");
  TTree *clone = POT_branch.CloneTree();
  clone->Write();

std::cout << "Writing output file for  Stacks" << std::endl;

h_CryoVertex_Z_TrackType.WriteToFile(*outFile);
h_CryoVertex_Z_vertex.WriteToFile(*outFile);
h_CryoVertex_Z_Ntracks.WriteToFile(*outFile);


  h_MuonE_Material.WriteToFile(*outFile);
  h_MuonPZ_Material.WriteToFile(*outFile);
  h_MuonPT_Material.WriteToFile(*outFile);
  h_MuonTheta_Material.WriteToFile(*outFile);
  h_CryoVertex_X_Material.WriteToFile(*outFile);
  h_CryoVertex_Y_Material.WriteToFile(*outFile);
  h_CryoVertex_Z_Material.WriteToFile(*outFile);
  h_CryoVertex_R_Material.WriteToFile(*outFile);
  h_Distance_to_InnerTank_Material.WriteToFile(*outFile);
  h_MuonDOCA_Material.WriteToFile(*outFile);
  h_secTrk_DOCA_Material.WriteToFile(*outFile);
  h_secTrk_tracklength_Material.WriteToFile(*outFile);

  h_CryoVertex_X_resolution_Material.WriteToFile(*outFile);
  h_CryoVertex_Y_resolution_Material.WriteToFile(*outFile);
  h_CryoVertex_R_resolution_Material.WriteToFile(*outFile);
  h_CryoVertex_Z_resolution_Material.WriteToFile(*outFile);

  h_CryoVertex_Z_UpstreamCap_TrackType.WriteToFile(*outFile);
  h_CryoVertex_X_UpstreamCap_TrackType.WriteToFile(*outFile);
  h_CryoVertex_Y_UpstreamCap_TrackType.WriteToFile(*outFile);
  h_CryoVertex_R_UpstreamCap_TrackType.WriteToFile(*outFile);
  h_CryoVertex_Z_UpstreamCap_vertex.WriteToFile(*outFile);
  h_CryoVertex_X_UpstreamCap_vertex.WriteToFile(*outFile);
  h_CryoVertex_Y_UpstreamCap_vertex.WriteToFile(*outFile);
  h_CryoVertex_R_UpstreamCap_vertex.WriteToFile(*outFile);
  h_CryoVertex_Z_UpstreamCap_Ntracks.WriteToFile(*outFile);
  h_CryoVertex_X_UpstreamCap_Ntracks.WriteToFile(*outFile);
  h_CryoVertex_Y_UpstreamCap_Ntracks.WriteToFile(*outFile);
  h_CryoVertex_R_UpstreamCap_Ntracks.WriteToFile(*outFile);

  h_CryoVertex_Z_Barrel_TrackType.WriteToFile(*outFile);
  h_CryoVertex_X_Barrel_TrackType.WriteToFile(*outFile);
  h_CryoVertex_Y_Barrel_TrackType.WriteToFile(*outFile);
  h_CryoVertex_R_Barrel_TrackType.WriteToFile(*outFile);
  h_CryoVertex_Z_Barrel_vertex.WriteToFile(*outFile);
  h_CryoVertex_X_Barrel_vertex.WriteToFile(*outFile);
  h_CryoVertex_Y_Barrel_vertex.WriteToFile(*outFile);
  h_CryoVertex_R_Barrel_vertex.WriteToFile(*outFile);
  h_CryoVertex_Z_Barrel_Ntracks.WriteToFile(*outFile);
  h_CryoVertex_X_Barrel_Ntracks.WriteToFile(*outFile);
  h_CryoVertex_Y_Barrel_Ntracks.WriteToFile(*outFile);
  h_CryoVertex_R_Barrel_Ntracks.WriteToFile(*outFile);

  h_CryoVertex_Z_DownstreamCap_TrackType.WriteToFile(*outFile);
  h_CryoVertex_X_DownstreamCap_TrackType.WriteToFile(*outFile);
  h_CryoVertex_Y_DownstreamCap_TrackType.WriteToFile(*outFile);
  h_CryoVertex_R_DownstreamCap_TrackType.WriteToFile(*outFile);
  h_CryoVertex_Z_DownstreamCap_vertex.WriteToFile(*outFile);
  h_CryoVertex_X_DownstreamCap_vertex.WriteToFile(*outFile);
  h_CryoVertex_Y_DownstreamCap_vertex.WriteToFile(*outFile);
  h_CryoVertex_R_DownstreamCap_vertex.WriteToFile(*outFile);
  h_CryoVertex_Z_DownstreamCap_Ntracks.WriteToFile(*outFile);
  h_CryoVertex_X_DownstreamCap_Ntracks.WriteToFile(*outFile);
  h_CryoVertex_Y_DownstreamCap_Ntracks.WriteToFile(*outFile);
  h_CryoVertex_R_DownstreamCap_Ntracks.WriteToFile(*outFile);


  h_CryoVertex_Z_Downstream_ConcaveCap_TrackType.WriteToFile(*outFile);
  h_CryoVertex_X_Downstream_ConcaveCap_TrackType.WriteToFile(*outFile);
  h_CryoVertex_Y_Downstream_ConcaveCap_TrackType.WriteToFile(*outFile);
  h_CryoVertex_R_Downstream_ConcaveCap_TrackType.WriteToFile(*outFile);
  h_CryoVertex_Z_Downstream_ConcaveCap_vertex.WriteToFile(*outFile);
  h_CryoVertex_X_Downstream_ConcaveCap_vertex.WriteToFile(*outFile);
  h_CryoVertex_Y_Downstream_ConcaveCap_vertex.WriteToFile(*outFile);
  h_CryoVertex_R_Downstream_ConcaveCap_vertex.WriteToFile(*outFile);
  h_CryoVertex_Z_Downstream_ConcaveCap_Ntracks.WriteToFile(*outFile);
  h_CryoVertex_X_Downstream_ConcaveCap_Ntracks.WriteToFile(*outFile);
  h_CryoVertex_Y_Downstream_ConcaveCap_Ntracks.WriteToFile(*outFile);
  h_CryoVertex_R_Downstream_ConcaveCap_Ntracks.WriteToFile(*outFile);



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

  h_CryoVertex_Z_RCut_Material.WriteToFile(*outFile);
  h_Distance_to_downstreamCap_Material.WriteToFile(*outFile);
  h_Distance_to_upstreamCap_Material.WriteToFile(*outFile);
  h_Distance_to_upstreamCap_RCut_Material.WriteToFile(*outFile);
  h_Distance_to_downstreamCap_RCut_Material.WriteToFile(*outFile);
  h_MuonE_UpstreamCap_Material.WriteToFile(*outFile);
  h_MuonPZ_UpstreamCap_Material.WriteToFile(*outFile);
  h_MuonPT_UpstreamCap_Material.WriteToFile(*outFile);
  h_MuonTheta_UpstreamCap_Material.WriteToFile(*outFile);
  h_CryoVertex_X_UpstreamCap_Material.WriteToFile(*outFile);
  h_CryoVertex_Y_UpstreamCap_Material.WriteToFile(*outFile);
  h_CryoVertex_Z_UpstreamCap_Material.WriteToFile(*outFile);
  h_CryoVertex_Z_RCut_UpstreamCap_Material.WriteToFile(*outFile);

  h_CryoVertex_R_UpstreamCap_Material.WriteToFile(*outFile);
  h_Distance_to_InnerTank_UpstreamCap_Material.WriteToFile(*outFile);
  h_Distance_to_InnerTank_Caps_UpstreamCap_Material.WriteToFile(*outFile);
  h_MuonDOCA_UpstreamCap_Material.WriteToFile(*outFile);
  h_secTrk_DOCA_UpstreamCap_Material.WriteToFile(*outFile);
  h_MuonDOCA_Barrel_Material.WriteToFile(*outFile);
  h_secTrk_DOCA_Barrel_Material.WriteToFile(*outFile);
  h_MuonDOCA_DownstreamCap_Material.WriteToFile(*outFile);
  h_secTrk_DOCA_DownstreamCap_Material.WriteToFile(*outFile);
  h_MuonDOCA_Downstream_ConcaveCap_Material.WriteToFile(*outFile);
  h_secTrk_DOCA_Downstream_ConcaveCap_Material.WriteToFile(*outFile);

  h_secTrk_tracklength_UpstreamCap_Material.WriteToFile(*outFile);
  h_secTrk_tracklength_Barrel_Material.WriteToFile(*outFile);
  h_secTrk_tracklength_DownstreamCap_Material.WriteToFile(*outFile);
  h_secTrk_tracklength_Downstream_ConcaveCap_Material.WriteToFile(*outFile);

  h_Distance_to_downstreamCap_UpstreamCap_Material.WriteToFile(*outFile);
  h_Distance_to_upstreamCap_UpstreamCap_Material.WriteToFile(*outFile);

  h_Distance_to_downstreamCap_RCut_UpstreamCap_Material.WriteToFile(*outFile);
  h_Distance_to_upstreamCap_RCut_UpstreamCap_Material.WriteToFile(*outFile);

  std::cout << "Upstream Material Stacks Done" << std::endl;

  h_MuonE_Barrel_Material.WriteToFile(*outFile);
  h_MuonPZ_Barrel_Material.WriteToFile(*outFile);
  h_MuonPT_Barrel_Material.WriteToFile(*outFile);
  h_MuonTheta_Barrel_Material.WriteToFile(*outFile);
  h_CryoVertex_X_Barrel_Material.WriteToFile(*outFile);
  h_CryoVertex_Y_Barrel_Material.WriteToFile(*outFile);
  h_CryoVertex_Z_Barrel_Material.WriteToFile(*outFile);
  h_CryoVertex_R_Barrel_Material.WriteToFile(*outFile);
  h_Distance_to_InnerTank_Barrel_Material.WriteToFile(*outFile);
  h_Distance_to_InnerTank_Barrel_Barrel_Material.WriteToFile(*outFile);
  h_Distance_to_downstreamCap_Barrel_Material.WriteToFile(*outFile);
  h_Distance_to_upstreamCap_Barrel_Material.WriteToFile(*outFile);

  h_CryoVertex_Z_RCut_Barrel_Material.WriteToFile(*outFile);
  h_Distance_to_downstreamCap_RCut_Barrel_Material.WriteToFile(*outFile);
  h_Distance_to_upstreamCap_RCut_Barrel_Material.WriteToFile(*outFile);

  std::cout << "Barrel Material Stacks Done" << std::endl;

  h_MuonE_DownstreamCap_Material.WriteToFile(*outFile);
  h_MuonPZ_DownstreamCap_Material.WriteToFile(*outFile);
  h_MuonPT_DownstreamCap_Material.WriteToFile(*outFile);
  h_MuonTheta_DownstreamCap_Material.WriteToFile(*outFile);
  h_CryoVertex_X_DownstreamCap_Material.WriteToFile(*outFile);
  h_CryoVertex_Y_DownstreamCap_Material.WriteToFile(*outFile);
  h_CryoVertex_Z_DownstreamCap_Material.WriteToFile(*outFile);
  h_CryoVertex_R_DownstreamCap_Material.WriteToFile(*outFile);
  h_Distance_to_InnerTank_DownstreamCap_Material.WriteToFile(*outFile);
  h_Distance_to_InnerTank_Caps_DownstreamCap_Material.WriteToFile(*outFile);
  h_Distance_to_downstreamCap_DownstreamCap_Material.WriteToFile(*outFile);
  h_Distance_to_upstreamCap_DownstreamCap_Material.WriteToFile(*outFile);
  h_CryoVertex_Z_RCut_DownstreamCap_Material.WriteToFile(*outFile);
  h_Distance_to_downstreamCap_RCut_DownstreamCap_Material.WriteToFile(*outFile);
  h_Distance_to_upstreamCap_RCut_DownstreamCap_Material.WriteToFile(*outFile);

  std::cout << "Downstream Material Stacks Done" << std::endl;

  h_MuonE_Downstream_ConcaveCap_Material.WriteToFile(*outFile);
  h_MuonPZ_Downstream_ConcaveCap_Material.WriteToFile(*outFile);
  h_MuonPT_Downstream_ConcaveCap_Material.WriteToFile(*outFile);
  h_MuonTheta_Downstream_ConcaveCap_Material.WriteToFile(*outFile);
  h_CryoVertex_X_Downstream_ConcaveCap_Material.WriteToFile(*outFile);
  h_CryoVertex_Y_Downstream_ConcaveCap_Material.WriteToFile(*outFile);
  h_CryoVertex_Z_Downstream_ConcaveCap_Material.WriteToFile(*outFile);
  h_CryoVertex_R_Downstream_ConcaveCap_Material.WriteToFile(*outFile);
  h_Distance_to_InnerTank_Downstream_ConcaveCap_Material.WriteToFile(*outFile);
  h_Distance_to_InnerTank_Caps_Downstream_ConcaveCap_Material.WriteToFile(*outFile);
  h_Distance_to_downstreamCap_Downstream_ConcaveCap_Material.WriteToFile(*outFile);
  h_Distance_to_upstreamCap_Downstream_ConcaveCap_Material.WriteToFile(*outFile);

  h_CryoVertex_X_UpstreamCap_resolution_Material.WriteToFile(*outFile);
  h_CryoVertex_Y_UpstreamCap_resolution_Material.WriteToFile(*outFile);
  h_CryoVertex_R_UpstreamCap_resolution_Material.WriteToFile(*outFile);
  h_CryoVertex_Z_UpstreamCap_resolution_Material.WriteToFile(*outFile);
  h_CryoVertex_X_Barrel_resolution_Material.WriteToFile(*outFile);
  h_CryoVertex_Y_Barrel_resolution_Material.WriteToFile(*outFile);
  h_CryoVertex_R_Barrel_resolution_Material.WriteToFile(*outFile);
  h_CryoVertex_Z_Barrel_resolution_Material.WriteToFile(*outFile);
  h_CryoVertex_X_DownstreamCap_resolution_Material.WriteToFile(*outFile);
  h_CryoVertex_Y_DownstreamCap_resolution_Material.WriteToFile(*outFile);
  h_CryoVertex_R_DownstreamCap_resolution_Material.WriteToFile(*outFile);
  h_CryoVertex_Z_DownstreamCap_resolution_Material.WriteToFile(*outFile);
  h_CryoVertex_X_Downstream_ConcaveCap_resolution_Material.WriteToFile(*outFile);
  h_CryoVertex_Y_Downstream_ConcaveCap_resolution_Material.WriteToFile(*outFile);
  h_CryoVertex_R_Downstream_ConcaveCap_resolution_Material.WriteToFile(*outFile);
  h_CryoVertex_Z_Downstream_ConcaveCap_resolution_Material.WriteToFile(*outFile);

  h_CryoVertex_Z_RCut_Downstream_ConcaveCap_Material.WriteToFile(*outFile);
  h_Distance_to_downstreamCap_RCut_Downstream_ConcaveCap_Material.WriteToFile(*outFile);
  h_Distance_to_upstreamCap_RCut_Downstream_ConcaveCap_Material.WriteToFile(*outFile);


  h_Mig_Vertex_X->Write();
  h_Mig_Vertex_Y->Write();
  h_Mig_Vertex_R->Write();
  h_Mig_Vertex_Z->Write();
  h_Mig_Vertex_X_UpstreamCap->Write();
  h_Mig_Vertex_Y_UpstreamCap->Write();
  h_Mig_Vertex_R_UpstreamCap->Write();
  h_Mig_Vertex_Z_UpstreamCap->Write();
  h_Mig_Vertex_X_Barrel->Write();
  h_Mig_Vertex_Y_Barrel->Write();
  h_Mig_Vertex_R_Barrel->Write();
  h_Mig_Vertex_Z_Barrel->Write();
  h_Mig_Vertex_X_DownstreamCap->Write();
  h_Mig_Vertex_Y_DownstreamCap->Write();
  h_Mig_Vertex_R_DownstreamCap->Write();
  h_Mig_Vertex_Z_DownstreamCap->Write();
  h_Mig_Vertex_X_Downstream_ConcaveCap->Write();
  h_Mig_Vertex_Y_Downstream_ConcaveCap->Write();
  h_Mig_Vertex_R_Downstream_ConcaveCap->Write();
  h_Mig_Vertex_Z_Downstream_ConcaveCap->Write();

  h_CryoVertex_X_RCut_Material.WriteToFile(*outFile);
  h_CryoVertex_Y_RCut_Material.WriteToFile(*outFile);
  h_CryoVertex_R_RCut_Material.WriteToFile(*outFile);

  h_CryoVertex_X_RCut_UpstreamCap_Material.WriteToFile(*outFile);
  h_CryoVertex_Y_RCut_UpstreamCap_Material.WriteToFile(*outFile);
  h_CryoVertex_R_RCut_UpstreamCap_Material.WriteToFile(*outFile);
  h_CryoVertex_X_RCut_Barrel_Material.WriteToFile(*outFile);
  h_CryoVertex_Y_RCut_Barrel_Material.WriteToFile(*outFile);
  h_CryoVertex_R_RCut_Barrel_Material.WriteToFile(*outFile);
  h_CryoVertex_X_RCut_DownstreamCap_Material.WriteToFile(*outFile);
  h_CryoVertex_Y_RCut_DownstreamCap_Material.WriteToFile(*outFile);
  h_CryoVertex_R_RCut_DownstreamCap_Material.WriteToFile(*outFile);
  h_CryoVertex_X_RCut_Downstream_ConcaveCap_Material.WriteToFile(*outFile);
  h_CryoVertex_Y_RCut_Downstream_ConcaveCap_Material.WriteToFile(*outFile);
  h_CryoVertex_R_RCut_Downstream_ConcaveCap_Material.WriteToFile(*outFile);



for(auto cat: RegionVector){

  HistFolio_Region14_Map_Vertex_X.at(cat).WriteToFile(*outFile);
  HistFolio_Region14_Map_Vectex_Y.at(cat).WriteToFile(*outFile);
  HistFolio_Region14_Map_Vectex_Z.at(cat).WriteToFile(*outFile);
  HistFolio_Region14_Map_Vectex_R.at(cat).WriteToFile(*outFile);
  HistFolio_Region14_Map_TRUE_Vertex_X.at(cat).WriteToFile(*outFile);
  HistFolio_Region14_Map_TRUE_Vectex_Y.at(cat).WriteToFile(*outFile);
  HistFolio_Region14_Map_TRUE_Vectex_Z.at(cat).WriteToFile(*outFile);
  HistFolio_Region14_Map_TRUE_Vectex_R.at(cat).WriteToFile(*outFile);
  HistFolio_Region14_Map_Distance_to_NearestWall.at(cat).WriteToFile(*outFile);
  HistFolio_Region14_Map_h_secTrk_Tracklength.at(cat).WriteToFile(*outFile);
  HistFolio_Region14_Map_secTrk_DOCA.at(cat).WriteToFile(*outFile);
  HistFolio_Region14_Map_Muon_DOCA.at(cat).WriteToFile(*outFile);
  HistFolio_Region14_Map_MuonPZ.at(cat).WriteToFile(*outFile);
  HistFolio_Region14_Map_MuonPT.at(cat).WriteToFile(*outFile);
  HistFolio_Region14_Map_MuonTheta.at(cat).WriteToFile(*outFile);
  HistFolio_Region14_Map_MuonE.at(cat).WriteToFile(*outFile);



}






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


  h_MuonE_UpstreamCap.hist->Write();
  h_MuonPZ_UpstreamCap.hist->Write();
  h_MuonPT_UpstreamCap.hist->Write();
  h_MuonTheta_UpstreamCap.hist->Write();
  h_CryoVertex_X_UpstreamCap.hist->Write();
  h_CryoVertex_Y_UpstreamCap.hist->Write();
  h_CryoVertex_Z_UpstreamCap.hist->Write();
  h_CryoVertex_Z_RCut.hist->Write();
  h_CryoVertex_Z_RCut_UpstreamCap.hist->Write();
  h_CryoVertex_Z_RCut_Barrel.hist->Write();
  h_CryoVertex_Z_RCut_DownstreamCap.hist->Write();
  h_CryoVertex_Z_RCut_Downstream_ConcaveCap.hist->Write();
  h_CryoVertex_R_UpstreamCap.hist->Write();
  h_Distance_to_InnerTank_UpstreamCap.hist->Write();
  h_Distance_to_InnerTank_Caps_DownstreamCap.hist->Write();
  h_Distance_to_InnerTank_Barrel_Downstream_ConcaveCap.hist->Write();
  h_Distance_to_InnerTank_Barrel_DownstreamCap.hist->Write();
  h_Distance_to_InnerTank_Barrel_UpstreamCap.hist->Write();
  h_CryoVertex_X_RCut.hist->Write();
  h_CryoVertex_Y_RCut.hist->Write();
  h_CryoVertex_R_RCut.hist->Write();
  h_CryoVertex_X_RCut_UpstreamCap.hist->Write();
  h_CryoVertex_Y_RCut_UpstreamCap.hist->Write();
  h_CryoVertex_R_RCut_UpstreamCap.hist->Write();
  h_CryoVertex_X_RCut_Barrel.hist->Write();
  h_CryoVertex_Y_RCut_Barrel.hist->Write();
  h_CryoVertex_R_RCut_Barrel.hist->Write();
  h_CryoVertex_X_RCut_DownstreamCap.hist->Write();
  h_CryoVertex_Y_RCut_DownstreamCap.hist->Write();
  h_CryoVertex_R_RCut_DownstreamCap.hist->Write();
  h_CryoVertex_X_RCut_Downstream_ConcaveCap.hist->Write();
  h_CryoVertex_Y_RCut_Downstream_ConcaveCap.hist->Write();
  h_CryoVertex_R_RCut_Downstream_ConcaveCap.hist->Write();


  std::cout << "Upstream Main Var done" << std::endl;

  h_MuonE_Barrel.hist->Write();
  h_MuonPT_Barrel.hist->Write();
  h_MuonPZ_Barrel.hist->Write();
  h_MuonTheta_Barrel.hist->Write();
  h_CryoVertex_X_Barrel.hist->Write();
  h_CryoVertex_Y_Barrel.hist->Write();
  h_CryoVertex_Z_Barrel.hist->Write();
  h_CryoVertex_R_Barrel.hist->Write();
  h_Distance_to_InnerTank_Barrel_Barrel.hist->Write();
  h_Distance_to_InnerTank_Barrel.hist->Write();


  std::cout << "Barrel Main Var done" << std::endl;

  h_MuonE_DownstreamCap.hist->Write();
  h_MuonPZ_DownstreamCap.hist->Write();
  h_MuonPT_DownstreamCap.hist->Write();
  h_MuonTheta_DownstreamCap.hist->Write();
  h_CryoVertex_X_DownstreamCap.hist->Write();
  h_CryoVertex_Y_DownstreamCap.hist->Write();
  h_CryoVertex_Z_DownstreamCap.hist->Write();
  h_CryoVertex_R_DownstreamCap.hist->Write();
  h_Distance_to_InnerTank_DownstreamCap.hist->Write();
  std::cout << "DownStream Main Var done" << std::endl;

  h_MuonE_Downstream_ConcaveCap.hist->Write();
  h_MuonPZ_Downstream_ConcaveCap.hist->Write();
  h_MuonPT_Downstream_ConcaveCap.hist->Write();
  h_MuonTheta_Downstream_ConcaveCap.hist->Write();
  h_CryoVertex_X_Downstream_ConcaveCap.hist->Write();
  h_CryoVertex_Y_Downstream_ConcaveCap.hist->Write();
  h_CryoVertex_Z_Downstream_ConcaveCap.hist->Write();
  h_CryoVertex_R_Downstream_ConcaveCap.hist->Write();
  h_Distance_to_InnerTank_Downstream_ConcaveCap.hist->Write();
  h_Distance_to_InnerTank_Caps_Downstream_ConcaveCap.hist->Write();
  h_Distance_to_InnerTank_Barrel_Downstream_ConcaveCap.hist->Write();
  h_MuonDOCA.hist->Write();
  h_secTrk_DOCA.hist->Write();
  h_secTrk_tracklength.hist->Write();
  h_MuonDOCA_UpstreamCap.hist->Write();
  h_secTrk_DOCA_UpstreamCap.hist->Write();
  h_MuonDOCA_Barrel.hist->Write();
  h_secTrk_DOCA_Barrel.hist->Write();
  h_MuonDOCA_DownstreamCap.hist->Write();
  h_secTrk_DOCA_DownstreamCap.hist->Write();
  h_MuonDOCA_Downstream_ConcaveCap.hist->Write();
  h_secTrk_DOCA_Downstream_ConcaveCap.hist->Write();

  h_secTrk_tracklength_UpstreamCap.hist->Write();
  h_secTrk_tracklength_Barrel.hist->Write();
  h_secTrk_tracklength_DownstreamCap.hist->Write();
  h_secTrk_tracklength_Downstream_ConcaveCap.hist->Write();


  h_Distance_to_downstreamCap.hist->Write();
  h_Distance_to_upstreamCap.hist->Write();
  h_Distance_to_downstreamCap_UpstreamCap.hist->Write();
  h_Distance_to_upstreamCap_UpstreamCap.hist->Write();
  h_Distance_to_downstreamCap_Barrel.hist->Write();
  h_Distance_to_upstreamCap_Barrel.hist->Write();
  h_Distance_to_downstreamCap_DownstreamCap.hist->Write();
  h_Distance_to_upstreamCap_DownstreamCap.hist->Write();
  h_Distance_to_downstreamCap_Downstream_ConcaveCap.hist->Write();
  h_Distance_to_upstreamCap_Downstream_ConcaveCap.hist->Write();

  h_Distance_to_downstreamCap_RCut.hist->Write();
  h_Distance_to_upstreamCap_RCut.hist->Write();

  h_Distance_to_downstreamCap_RCut_UpstreamCap.hist->Write();
  h_Distance_to_upstreamCap_RCut_UpstreamCap.hist->Write();
  h_Distance_to_downstreamCap_RCut_Barrel.hist->Write();
  h_Distance_to_upstreamCap_RCut_Barrel.hist->Write();
  h_Distance_to_downstreamCap_RCut_DownstreamCap.hist->Write();
  h_Distance_to_upstreamCap_RCut_DownstreamCap.hist->Write();
  h_Distance_to_downstreamCap_RCut_Downstream_ConcaveCap.hist->Write();
  h_Distance_to_upstreamCap_RCut_Downstream_ConcaveCap.hist->Write();



  h_CryoVertex_X_resolution_RECO.hist->Write();
  h_CryoVertex_X_percentresolution_RECO.hist->Write();
  h_CryoVertex_Y_resolution_RECO.hist->Write();
  h_CryoVertex_Y_percentresolution_RECO.hist->Write();
  h_CryoVertex_R_resolution_RECO.hist->Write();
  h_CryoVertex_R_percentresolution_RECO.hist->Write();
  h_CryoVertex_Z_resolution_RECO.hist->Write();
  h_CryoVertex_Z_percentresolution_RECO.hist->Write();
  h_CryoVertex_X_UpstreamCap_resolution_RECO.hist->Write();
  h_CryoVertex_X_UpstreamCap_percentresolution_RECO.hist->Write();
  h_CryoVertex_Y_UpstreamCap_resolution_RECO.hist->Write();
  h_CryoVertex_Y_UpstreamCap_percentresolution_RECO.hist->Write();
  h_CryoVertex_R_UpstreamCap_resolution_RECO.hist->Write();
  h_CryoVertex_R_UpstreamCap_percentresolution_RECO.hist->Write();
  h_CryoVertex_Z_UpstreamCap_resolution_RECO.hist->Write();
  h_CryoVertex_Z_UpstreamCap_percentresolution_RECO.hist->Write();
  h_CryoVertex_X_Barrel_resolution_RECO.hist->Write();
  h_CryoVertex_X_Barrel_percentresolution_RECO.hist->Write();
  h_CryoVertex_Y_Barrel_resolution_RECO.hist->Write();
  h_CryoVertex_Y_Barrel_percentresolution_RECO.hist->Write();
  h_CryoVertex_R_Barrel_resolution_RECO.hist->Write();
  h_CryoVertex_R_Barrel_percentresolution_RECO.hist->Write();
  h_CryoVertex_Z_Barrel_resolution_RECO.hist->Write();
  h_CryoVertex_Z_Barrel_percentresolution_RECO.hist->Write();
  h_CryoVertex_X_DownstreamCap_resolution_RECO.hist->Write();
  h_CryoVertex_X_DownstreamCap_percentresolution_RECO.hist->Write();
  h_CryoVertex_Y_DownstreamCap_resolution_RECO.hist->Write();
  h_CryoVertex_Y_DownstreamCap_percentresolution_RECO.hist->Write();
  h_CryoVertex_R_DownstreamCap_resolution_RECO.hist->Write();
  h_CryoVertex_R_DownstreamCap_percentresolution_RECO.hist->Write();
  h_CryoVertex_Z_DownstreamCap_resolution_RECO.hist->Write();
  h_CryoVertex_Z_DownstreamCap_percentresolution_RECO.hist->Write();
  h_CryoVertex_X_Downstream_ConcaveCap_resolution_RECO.hist->Write();
  h_CryoVertex_X_Downstream_ConcaveCap_percentresolution_RECO.hist->Write();
  h_CryoVertex_Y_Downstream_ConcaveCap_resolution_RECO.hist->Write();
  h_CryoVertex_Y_Downstream_ConcaveCap_percentresolution_RECO.hist->Write();
  h_CryoVertex_R_Downstream_ConcaveCap_resolution_RECO.hist->Write();
  h_CryoVertex_R_Downstream_ConcaveCap_percentresolution_RECO.hist->Write();
  h_CryoVertex_Z_Downstream_ConcaveCap_resolution_RECO.hist->Write();
  h_CryoVertex_Z_Downstream_ConcaveCap_percentresolution_RECO.hist->Write();



  h_CryoVertex_X_resolution_TRUE_RECO.hist->Write();
  h_CryoVertex_X_percentresolution_TRUE_RECO.hist->Write();
  h_CryoVertex_Y_resolution_TRUE_RECO.hist->Write();
  h_CryoVertex_Y_percentresolution_TRUE_RECO.hist->Write();
  h_CryoVertex_R_resolution_TRUE_RECO.hist->Write();
  h_CryoVertex_R_percentresolution_TRUE_RECO.hist->Write();
  h_CryoVertex_Z_resolution_TRUE_RECO.hist->Write();
  h_CryoVertex_Z_percentresolution_TRUE_RECO.hist->Write();
  h_CryoVertex_X_UpstreamCap_resolution_TRUE_RECO.hist->Write();
  h_CryoVertex_X_UpstreamCap_percentresolution_TRUE_RECO.hist->Write();
  h_CryoVertex_Y_UpstreamCap_resolution_TRUE_RECO.hist->Write();
  h_CryoVertex_Y_UpstreamCap_percentresolution_TRUE_RECO.hist->Write();
  h_CryoVertex_R_UpstreamCap_resolution_TRUE_RECO.hist->Write();
  h_CryoVertex_R_UpstreamCap_percentresolution_TRUE_RECO.hist->Write();
  h_CryoVertex_Z_UpstreamCap_resolution_TRUE_RECO.hist->Write();
  h_CryoVertex_Z_UpstreamCap_percentresolution_TRUE_RECO.hist->Write();
  h_CryoVertex_X_Barrel_resolution_TRUE_RECO.hist->Write();
  h_CryoVertex_X_Barrel_percentresolution_TRUE_RECO.hist->Write();
  h_CryoVertex_Y_Barrel_resolution_TRUE_RECO.hist->Write();
  h_CryoVertex_Y_Barrel_percentresolution_TRUE_RECO.hist->Write();
  h_CryoVertex_R_Barrel_resolution_TRUE_RECO.hist->Write();
  h_CryoVertex_R_Barrel_percentresolution_TRUE_RECO.hist->Write();
  h_CryoVertex_Z_Barrel_resolution_TRUE_RECO.hist->Write();
  h_CryoVertex_Z_Barrel_percentresolution_TRUE_RECO.hist->Write();
  h_CryoVertex_X_DownstreamCap_resolution_TRUE_RECO.hist->Write();
  h_CryoVertex_X_DownstreamCap_percentresolution_TRUE_RECO.hist->Write();
  h_CryoVertex_Y_DownstreamCap_resolution_TRUE_RECO.hist->Write();
  h_CryoVertex_Y_DownstreamCap_percentresolution_TRUE_RECO.hist->Write();
  h_CryoVertex_R_DownstreamCap_resolution_TRUE_RECO.hist->Write();
  h_CryoVertex_R_DownstreamCap_percentresolution_TRUE_RECO.hist->Write();
  h_CryoVertex_Z_DownstreamCap_resolution_TRUE_RECO.hist->Write();
  h_CryoVertex_Z_DownstreamCap_percentresolution_TRUE_RECO.hist->Write();
  h_CryoVertex_X_Downstream_ConcaveCap_resolution_TRUE_RECO.hist->Write();
  h_CryoVertex_X_Downstream_ConcaveCap_percentresolution_TRUE_RECO.hist->Write();
  h_CryoVertex_Y_Downstream_ConcaveCap_resolution_TRUE_RECO.hist->Write();
  h_CryoVertex_Y_Downstream_ConcaveCap_percentresolution_TRUE_RECO.hist->Write();
  h_CryoVertex_R_Downstream_ConcaveCap_resolution_TRUE_RECO.hist->Write();
  h_CryoVertex_R_Downstream_ConcaveCap_percentresolution_TRUE_RECO.hist->Write();
  h_CryoVertex_Z_Downstream_ConcaveCap_resolution_TRUE_RECO.hist->Write();
  h_CryoVertex_Z_Downstream_ConcaveCap_percentresolution_TRUE_RECO.hist->Write();


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
  //ret_vec.push_back(kMuonAngle_CenterForwardGoingAngle);
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
  //ret_vec.push_back(ksecTrkwrtblessthanMaxAngle);

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
