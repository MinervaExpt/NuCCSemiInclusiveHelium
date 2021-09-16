// * Uses the New Systematics Framework and "Universe" objects.
// * loop universes, make cuts and fill histograms with the correct lateral
// shifts and weights for each universe.
// * TChain --> PlotUtils::ChainWrapper.
// * MnvHXD --> PlotUtils::HistWrapper.
// * Genie, flux, non-resonant pion, and some detector systematics calculated.
#include "Helium_runEventLoop_EfficiencyStudy.h"

std::string OUTputRoot_pathway = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles";
//=====================================================
// Cuts applying Functions and Weights
//=====================================================
std::vector<ECuts> GetRECOCutsFor_2ndTrkEnergyVector();
std::vector<ECuts> GetVectorRECOCuts_MuonEnergy_Eff();
std::vector<ECuts> GetRECOCutsFor2ndTrkAngleVector();
std::vector<ECuts> GetRECOCutsFor2ndTrkAngle_noFidiucalVector();
std::vector<ECuts> GetVectorRECOCuts_MuonTheta_Eff();
std::vector<ECuts> GetVectorRECOCutsFidicual_Eff();
std::vector<ECutsTRUTH> GetTRUTHCutsVector();
std::vector<ECutsTRUTH> GetTRUTHCutsVector_Energy();
std::vector<ECutsTRUTH> GetTRUTHCutsVector_2ndtrkAngle();
std::vector<ECutsTRUTH> GetTRUTHCutsVector_2ndtrkEnergy();
std::vector<ECutsTRUTH> GetTRUTH_ThetaMuCutsVector();
std::vector<ECutsTRUTH> GetTRUTH_FidiucalMuCutsVector();
std::vector<MuonVar> GetMUONVaribles();
std::vector<SecondTrkVar> GetPlayListSecondTrkVector();
std::vector<CryoVertex> GetCryoVertexVaribles();

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
const std::vector<ECuts> kCutsVector_MuonEnergy = GetVectorRECOCuts_MuonEnergy_Eff();
const std::vector<ECuts> kCutsVector_2ndtrkAngle = GetRECOCutsFor2ndTrkAngleVector();
const std::vector<ECuts> kCutsVector_2ndtrkAngle_noFidiucal = GetRECOCutsFor2ndTrkAngle_noFidiucalVector();
const std::vector<ECuts> kCutsVector_2ndtrkEnergy = GetRECOCutsFor_2ndTrkEnergyVector();
const std::vector<ECuts> kCutsVector_MuonThetaEff = GetVectorRECOCuts_MuonTheta_Eff();
const std::vector<ECuts> kCutsVector_FiduicalEff = GetVectorRECOCutsFidicual_Eff();



const std::vector<ECutsTRUTH> kTRUTHCutsVector_MuonEnergy =  GetTRUTHCutsVector_Energy();
const std::vector<ECutsTRUTH> kTRUTHCutsVector_MuonTheta = GetTRUTH_ThetaMuCutsVector();
const std::vector<ECutsTRUTH> kTRUTHCutsVector_Fiduical = GetTRUTH_FidiucalMuCutsVector();
const std::vector<ECutsTRUTH> kTRUTHCutsVector_2ndTrkAngle =  GetTRUTHCutsVector_2ndtrkAngle();
const std::vector<ECutsTRUTH> kTRUTHCutsVector_2ndTrkEnergy = GetTRUTHCutsVector_2ndtrkEnergy();


int count_fid_0 = 0;
int count_fid_neg_200 = 0;
int count_fid_50 = 0;

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


//for(auto PlayList_iterator:kPlayListVector ){
  MinervaUniverse::SetDeuteriumGeniePiTune(false);
  MinervaUniverse::SetNuEConstraint(true);
  MinervaUniverse::SetZExpansionFaReweight(false);
  MinervaUniverse::SetAnalysisNuPDG(14);
  MinervaUniverse::SetNonResPiReweight(true);
  MinervaUniverse::SetNFluxUniverses(n_flux_universes);
  std::string playlist = GetPlaylist(PlayList_iterator);

  MinervaUniverse::SetPlaylist(playlist);
  //MinervaUniverse::Set_Multiple_resetPlaylist(true);
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


//static weightMK *weight_MK;
//char *mparalocation = std::getenv("MPARAMFILESROOT");
//string dir_data = string(mparalocation)+"/data/Reweight/";
//weight_MK = new weightMK(dir_data + "output_ratio_genie_neut_for_MKmodel.root");

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
//std::vector<double> MuonThetabin_vector= GetBinMuonVector(kAngleWRTB);

std::vector<double> MuonThetabin_vector{0.0,1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0,14.0,15.0,16.0,17.0,18.0,19.0,20.0}; //= //GetBinMuonVector(kAngleWRTB);

std::cout<< "size MuonThetabin_vector =  "<< MuonThetabin_vector.size()<<std::endl;

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
std::vector<double> Vertex_Xbin_vector= GetBinvertexVector(kX_eff);
std::vector<double> Vertex_Ybin_vector= GetBinvertexVector(kY_eff);
std::vector<double> Vertex_Zbin_vector= GetBinvertexVector(kZ_eff);
std::vector<double> Vertex_Rbin_vector= GetBinvertexVector(kR_eff);
std::vector<double> Vertex_RRbin_vector= GetBinvertexVector(kRR_eff);

std::vector<double> Vertex_resolution_Xbin_vector = GetBinvertexVector(kX_resolution);
std::vector<double> Vertex_resolution_Ybin_vector = GetBinvertexVector(kY_resolution);
std::vector<double> Vertex_resolution_Zbin_vector = GetBinvertexVector(kZ_resolution);
std::vector<double> Vertex_resolution_Rbin_vector = GetBinvertexVector(kR_resolution);
std::vector<double> Vertex_resolution_RRbin_vector= GetBinvertexVector(kRR_resolution);

std::vector<double> Bins_toAddxyr{ -225, -100, 100, 225};
std::vector<double> Bins_toAddz{-1000, -750, -500, -400, 400, 500, 750, 1000};

for(auto cat : Bins_toAddxyr){
Vertex_resolution_Rbin_vector.push_back(cat);
Vertex_resolution_Xbin_vector.push_back(cat);
Vertex_resolution_Ybin_vector.push_back(cat);
}

for(auto cat : Bins_toAddz){
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

std::vector<double> secTrk_Theta_TRUEbin_vector = GetSecondTrkVarVector(kThetamid);//GetSecondTrkVarVector(kFullAngle);
std::vector<double> Vertex_secondTrkThetamidbin_vector = GetSecondTrkVarVector(kThetamid);
std::vector<double> Vertex_secondTrkTheta_Coarse_bins{0 ,2 ,4 ,6 ,8 ,10 ,12 ,14 ,16 ,18 ,20 ,22 ,24 ,26 ,28 ,30 ,32 ,34 ,36 ,38 ,40 ,42 ,44 ,46 ,48 ,50 ,52 ,54 ,56 ,58 ,60 ,62};


std::vector<double> Vertex_DOCAbin_vector= GetBinMuonVector(kDOCA_muon);
std::vector<double> Vertex_secondTrkEbins = GetSecondTrkVarVector(ksecE);  //GetSecondTrkVarVector(ksecE);,ksecE_Proton
std::vector<double> Vertex_secondTrkEbin_Proton_vector= GetSecondTrkVarVector(ksecE_Proton);
//std::sort(Vertex_secondTrkEbin_Proton_vector.begin(),Vertex_secondTrkEbin_Proton_vector.end());


std::vector<double> Vertex_secondTrkDOCA_bins= GetSecondTrkVarVector(kDOCA);
std::vector<double> Vertex_secondTrkPathway_bins= GetSecondTrkVarVector(kPathway);

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

std::cout<<"bins"<<std::endl;
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






PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE_TRUE_RECO("h_MuonE_TRUE_RECO", "Muon_{E} NEW Method", Ebin_vector , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonE_TRUE_RECO_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonE_Material", Ebin_vector ,"MuonE_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonE_TRUE_RECO_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_MuonE_Interaction", Ebin_vector ,"MuonE_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_MuonE_TRUE_RECO_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_MuonE_Particle", Ebin_vector ,"MuonE_Particle; [GeV];Events");


PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPZ_TRUE_RECO("h_MuonPZ_TRUE_RECO", "Muon_{PZ} NEW Method",  Pzbin_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPT_TRUE_RECO("h_MuonPT_TRUE_RECO", "Muon_{PT} NEW Method",  PTbin_vector , error_bands);


PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonTheta_TRUE_RECO("h_MuonTheta_TRUE_RECO", "MuonTheta [Deg]",  MuonThetabin_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPhi_TRUE_RECO("h_MuonPhi_TRUE_RECO", "Muon Phi [Deg]",  AnglePhi_vector , error_bands);


//////////////////////////////////////
/////////////Minos/////////////////
//////////////////////////////////
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_tracklength_TRUE_RECO("h_secTrk_tracklength_TRUE_RECO", "Recoil track length  [cm] ", Recoil_track_length_vector , error_bands);



std::vector<double> bigAngle_bins{0.0, 15.0, 30.0, 45.0, 60.0};
//MnvH2D *h_2d_2ndtrkLength_Angle    =    new MnvH2D("h_2d_2ndtrkLength_Angle", "h_2d_2ndtrkLength_Angle", Recoil_track_length_vector.size()-1, Recoil_track_length_vector.data(), bigAngle_bins.size()-1, bigAngle_bins.data());

std::vector<double> bigAngle_bins_finner{0.0, 5.0, 10.0, 15.0, 20.0, 25.0, 30.0, 45.0, 60.0};
//MnvH2D *h_2d_2ndtrkLength_finerAngle    =    new MnvH2D("h_2d_2ndtrkLength_finerAngle", "h_2d_2ndtrkLength_finerAngle", Recoil_track_length_vector.size()-1, Recoil_track_length_vector.data(), bigAngle_bins_finner.size()-1, bigAngle_bins_finner.data());



/////////////////////////////////////
//


////////////////
//Vertex Hist///
////////////////
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_TRUE_RECO("h_CryoVertex_X_TRUE_RECO", "h_CryoVertex_X",  Vertex_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_recoX_TRUE_RECO("h_CryoVertex_recoX_TRUE_RECO", "h_CryoVertex_X",  Vertex_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_resolutionX_TRUE_RECO("h_CryoVertex_resolutionX_TRUE_RECO", "h_CryoVertex_resolutionX_TRUE_RECO",  Vertex_resolution_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Percent_resolutionX_TRUE_RECO("h_CryoVertex_Percent_resolutionX_TRUE_RECO", "h_CryoVertex_Percent_resolutionX_TRUE_RECO",  Vertex_Percent_resolution_Xbin_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_recoX_RECO("h_CryoVertex_recoX_RECO", "h_CryoVertex_X",  Vertex_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_resolutionX_RECO("h_CryoVertex_resolutionX_RECO", "h_CryoVertex_resolutionX_RECO",  Vertex_resolution_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Percent_resolutionX_RECO("h_CryoVertex_Percent_resolutionX_RECO", "h_CryoVertex_Percent_resolutionX_RECO",  Vertex_Percent_resolution_Xbin_vector , error_bands);


PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_resolutionX_RECO_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_resolutionX_RECO_Material", Vertex_resolution_Xbin_vector ,"h_CryoVertex_resolutionX_RECO_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_CryoVertex_resolutionX_RECO_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_CryoVertex_resolutionX_RECO_Interaction", Vertex_resolution_Xbin_vector ,"h_CryoVertex_resolutionX_RECO_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_CryoVertex_resolutionX_RECO_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_CryoVertex_resolutionX_RECO_Particle", Vertex_resolution_Xbin_vector ,"h_CryoVertex_resolutionX_RECO_Particle; [mm];Events");






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
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_TRUE_RECO("h_CryoVertex_Y_TRUE_RECO", "Vertex_Y",  Vertex_Ybin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_recoY_TRUE_RECO("h_CryoVertex_recoY_TRUE_RECO", "Vertex_Y",  Vertex_Ybin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_resolutionY_TRUE_RECO("h_CryoVertex_resolutionY_TRUE_RECO", "h_CryoVertex_resolutionY_TRUE_RECO",  Vertex_resolution_Ybin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Percent_resolutionY_TRUE_RECO("h_CryoVertex_Percent_resolutionY_TRUE_RECO", "h_CryoVertex_Percent_resolutionY_TRUE_RECO",  Vertex_Percent_resolution_Ybin_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_recoY_RECO("h_CryoVertex_recoY_RECO", "Vertex_Y",  Vertex_Ybin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_resolutionY_RECO("h_CryoVertex_resolutionY_RECO", "h_CryoVertex_resolutionY_RECO",  Vertex_resolution_Ybin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Percent_resolutionY_RECO("h_CryoVertex_Percent_resolutionY_RECO", "h_CryoVertex_Percent_resolutionY_RECO",  Vertex_Percent_resolution_Ybin_vector , error_bands);


PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_resolutionY_RECO_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_resolutionY_RECO_Material", Vertex_resolution_Ybin_vector ,"h_CryoVertex_resolutionX_RECO_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_CryoVertex_resolutionY_RECO_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_CryoVertex_resolutionY_RECO_Interaction", Vertex_resolution_Ybin_vector ,"h_CryoVertex_resolutionX_RECO_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_CryoVertex_resolutionY_RECO_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_CryoVertex_resolutionY_RECO_Particle", Vertex_resolution_Ybin_vector ,"h_CryoVertex_resolutionX_RECO_Particle; [mm];Events");






PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Y_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Y_Material", Vertex_Ybin_vector ,"h_CryoVertex_Y_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_CryoVertex_Y_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_CryoVertex_Y_Interaction", Vertex_Ybin_vector ,"h_CryoVertex_Y_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_CryoVertex_Y_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_CryoVertex_Y_Particle", Vertex_Ybin_vector ,"h_CryoVertex_Y_Particle; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType> h_CryoVertex_Y_Track =
PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType>(TrackType_Category, "h_CryoVertex_Y_Track", Vertex_Ybin_vector ,"h_CryoVertex_Y_Track; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack> h_CryoVertex_Y_boolNTrack =
PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack>(boolNTrack_Category, "h_CryoVertex_Y_boolNTrack", Vertex_Ybin_vector ,"h_CryoVertex_Y_boolNTrack; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions> h_CryoVertex_Y_VertexOptions =
PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions>(VertexOptions_Category, "h_CryoVertex_Y_VertexOptions", Vertex_Ybin_vector ,"h_CryoVertex_Y_VertexOptions; [mm];Events");

PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_TRUE_RECO("h_CryoVertex_Z_TRUE_RECO", "Vertex_Z",  Vertex_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_recoZ_TRUE_RECO("h_CryoVertex_recoZ_TRUE_RECO", "Vertex_Z",  Vertex_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_resolutionZ_TRUE_RECO("h_CryoVertex_resolutionZ_TRUE_RECO", "h_CryoVertex_resolutionZ_TRUE_RECO",  Vertex_resolution_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Percent_resolutionZ_TRUE_RECO("h_CryoVertex_Percent_resolutionZ_TRUE_RECO", "h_CryoVertex_Percent_resolutionZ_TRUE_RECO",  Vertex_Percent_resolution_Zbin_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_recoZ_RECO("h_CryoVertex_recoZ_RECO", "Vertex_Z",  Vertex_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_resolutionZ_RECO("h_CryoVertex_resolutionZ_RECO", "h_CryoVertex_resolutionZ_RECO",  Vertex_resolution_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Percent_resolutionZ_RECO("h_CryoVertex_Percent_resolutionZ_RECO", "h_CryoVertex_Percent_resolutionZ_RECO",  Vertex_Percent_resolution_Zbin_vector , error_bands);


PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_resolutionZ_RECO_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_resolutionZ_RECO_Material", Vertex_resolution_Zbin_vector ,"h_CryoVertex_resolutionX_RECO_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_CryoVertex_resolutionZ_RECO_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_CryoVertex_resolutionZ_RECO_Interaction", Vertex_resolution_Zbin_vector ,"h_CryoVertex_resolutionX_RECO_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_CryoVertex_resolutionZ_RECO_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_CryoVertex_resolutionZ_RECO_Particle", Vertex_resolution_Zbin_vector ,"h_CryoVertex_resolutionX_RECO_Particle; [mm];Events");


PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_resolutionZ_fidiucal_RECO_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_resolutionZ_fidiucal_RECO_Material", Vertex_resolution_Zbin_vector ,"h_CryoVertex_resolutionX_RECO_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_CryoVertex_resolutionZ_fidiucal_RECO_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_CryoVertex_resolutionZ_fidiucal_RECO_Interaction", Vertex_resolution_Zbin_vector ,"h_CryoVertex_resolutionX_RECO_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_CryoVertex_resolutionZ_fidiucal_RECO_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_CryoVertex_resolutionZ_fidiucal_RECO_Particle", Vertex_resolution_Zbin_vector ,"h_CryoVertex_resolutionX_RECO_Particle; [mm];Events");



PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_resolutionZ_fidiucal_Neg100_RECO_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_resolutionZ_fidiucal_Neg100_RECO_Material", Vertex_resolution_Zbin_vector ,"h_CryoVertex_resolutionX_RECO_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_CryoVertex_resolutionZ_fidiucal_Neg100_RECO_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_CryoVertex_resolutionZ_fidiucal_Neg100_RECO_Interaction", Vertex_resolution_Zbin_vector ,"h_CryoVertex_resolutionX_RECO_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_CryoVertex_resolutionZ_fidiucal_Neg100_RECO_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_CryoVertex_resolutionZ_fidiucal_Neg100_RECO_Particle", Vertex_resolution_Zbin_vector ,"h_CryoVertex_resolutionX_RECO_Particle; [mm];Events");

//
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_resolutionZ_fidiucal_Neg50_RECO_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_resolutionZ_fidiucal_Neg50_RECO_Material", Vertex_resolution_Zbin_vector ,"h_CryoVertex_resolutionX_RECO_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_CryoVertex_resolutionZ_fidiucal_Neg50_RECO_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_CryoVertex_resolutionZ_fidiucal_Neg50_RECO_Interaction", Vertex_resolution_Zbin_vector ,"h_CryoVertex_resolutionX_RECO_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_CryoVertex_resolutionZ_fidiucal_Neg50_RECO_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_CryoVertex_resolutionZ_fidiucal_Neg50_RECO_Particle", Vertex_resolution_Zbin_vector ,"h_CryoVertex_resolutionX_RECO_Particle; [mm];Events");
//
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_resolutionZ_fidiucal_50_RECO_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_resolutionZ_fidiucal_50_RECO_Material", Vertex_resolution_Zbin_vector ,"h_CryoVertex_resolutionX_RECO_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_CryoVertex_resolutionZ_fidiucal_50_RECO_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_CryoVertex_resolutionZ_fidiucal_50_RECO_Interaction", Vertex_resolution_Zbin_vector ,"h_CryoVertex_resolutionX_RECO_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_CryoVertex_resolutionZ_fidiucal_50_RECO_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_CryoVertex_resolutionZ_fidiucal_50_RECO_Particle", Vertex_resolution_Zbin_vector ,"h_CryoVertex_resolutionX_RECO_Particle; [mm];Events");
//

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_resolutionZ_fidiucal_100_RECO_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_resolutionZ_fidiucal_100_RECO_Material", Vertex_resolution_Zbin_vector ,"h_CryoVertex_resolutionX_RECO_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_CryoVertex_resolutionZ_fidiucal_100_RECO_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_CryoVertex_resolutionZ_fidiucal_100_RECO_Interaction", Vertex_resolution_Zbin_vector ,"h_CryoVertex_resolutionX_RECO_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_CryoVertex_resolutionZ_fidiucal_100_RECO_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_CryoVertex_resolutionZ_fidiucal_100_RECO_Particle", Vertex_resolution_Zbin_vector ,"h_CryoVertex_resolutionX_RECO_Particle; [mm];Events");


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


PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_TRUE_RECO("h_CryoVertex_R_TRUE_RECO", "h_CryoVertex_R_TRUE_RECO",  Vertex_Rbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_recoR_TRUE_RECO("h_CryoVertex_recoR_TRUE_RECO", "h_CryoVertex_recoR_TRUE_RECO",  Vertex_Rbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_resolutionR_TRUE_RECO("h_CryoVertex_resolutionR_TRUE_RECO", "h_CryoVertex_resolutionR_TRUE_RECO",  Vertex_resolution_Rbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Percent_resolutionR_TRUE_RECO("h_CryoVertex_Percent_resolutionR_TRUE_RECO", "h_CryoVertex_Percent_resolutionR_TRUE_RECO",  Vertex_Percent_resolution_Rbin_vector , error_bands);


PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_recoR_RECO("h_CryoVertex_recoR_RECO", "h_CryoVertex_recoR_RECO",  Vertex_Rbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_resolutionR_RECO("h_CryoVertex_resolutionR_RECO", "h_CryoVertex_resolutionR_RECO",  Vertex_resolution_Rbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Percent_resolutionR_RECO("h_CryoVertex_Percent_resolutionR_RECO", "h_CryoVertex_Percent_resolutionR_RECO",  Vertex_Percent_resolution_Rbin_vector , error_bands);


PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_resolutionR_RECO_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_resolutionR_RECO_Material", Vertex_resolution_Rbin_vector ,"h_CryoVertex_resolutionR_RECO_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_CryoVertex_resolutionR_RECO_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_CryoVertex_resolutionR_RECO_Interaction", Vertex_resolution_Rbin_vector ,"h_CryoVertex_resolutionR_RECO_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_CryoVertex_resolutionR_RECO_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_CryoVertex_resolutionR_RECO_Particle", Vertex_resolution_Rbin_vector ,"h_CryoVertex_resolutionR_RECO_Particle; [mm];Events");


PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_resolutionR_fidiucal_RECO_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_resolutionR_fidiucal_RECO_Material", Vertex_resolution_Rbin_vector ,"h_CryoVertex_resolutionR_RECO_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_CryoVertex_resolutionR_fidiucal_RECO_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_CryoVertex_resolutionR_fidiucal_RECO_Interaction", Vertex_resolution_Rbin_vector ,"h_CryoVertex_resolutionR_RECO_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_CryoVertex_resolutionR_fidiucal_RECO_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_CryoVertex_resolutionR_fidiucal_RECO_Particle", Vertex_resolution_Rbin_vector ,"h_CryoVertex_resolutionR_RECO_Particle; [mm];Events");


PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_resolutionR_fidiucal_Neg100_RECO_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_resolutionR_fidiucal_Neg100_RECO_Material", Vertex_resolution_Rbin_vector ,"h_CryoVertex_resolutionR_RECO_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_CryoVertex_resolutionR_fidiucal_Neg100_RECO_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_CryoVertex_resolutionR_fidiucal_Neg100_RECO_Interaction", Vertex_resolution_Rbin_vector ,"h_CryoVertex_resolutionR_RECO_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_CryoVertex_resolutionR_fidiucal_Neg100_RECO_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_CryoVertex_resolutionR_fidiucal_Neg100_RECO_Particle", Vertex_resolution_Rbin_vector ,"h_CryoVertex_resolutionR_RECO_Particle; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_resolutionR_fidiucal_Neg50_RECO_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_resolutionR_fidiucal_Neg50_RECO_Material", Vertex_resolution_Rbin_vector ,"h_CryoVertex_resolutionR_RECO_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_CryoVertex_resolutionR_fidiucal_Neg50_RECO_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_CryoVertex_resolutionR_fidiucal_Neg50_RECO_Interaction", Vertex_resolution_Rbin_vector ,"h_CryoVertex_resolutionR_RECO_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_CryoVertex_resolutionR_fidiucal_Neg50_RECO_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_CryoVertex_resolutionR_fidiucal_Neg50_RECO_Particle", Vertex_resolution_Rbin_vector ,"h_CryoVertex_resolutionR_RECO_Particle; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_resolutionR_fidiucal_50_RECO_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_resolutionR_fidiucal_50_RECO_Material", Vertex_resolution_Rbin_vector ,"h_CryoVertex_resolutionR_RECO_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_CryoVertex_resolutionR_fidiucal_50_RECO_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_CryoVertex_resolutionR_fidiucal_50_RECO_Interaction", Vertex_resolution_Rbin_vector ,"h_CryoVertex_resolutionR_RECO_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_CryoVertex_resolutionR_fidiucal_50_RECO_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_CryoVertex_resolutionR_fidiucal_50_RECO_Particle", Vertex_resolution_Rbin_vector ,"h_CryoVertex_resolutionR_RECO_Particle; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_resolutionR_fidiucal_100_RECO_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_resolutionR_fidiucal_100_RECO_Material", Vertex_resolution_Rbin_vector ,"h_CryoVertex_resolutionR_RECO_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_CryoVertex_resolutionR_fidiucal_100_RECO_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_CryoVertex_resolutionR_fidiucal_100_RECO_Interaction", Vertex_resolution_Rbin_vector ,"h_CryoVertex_resolutionR_RECO_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_CryoVertex_resolutionR_fidiucal_100_RECO_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_CryoVertex_resolutionR_fidiucal_100_RECO_Particle", Vertex_resolution_Rbin_vector ,"h_CryoVertex_resolutionR_RECO_Particle; [mm];Events");

//std::vector<double> CutTOSurface{200,190,180,170,160,150,140,130,120,110,100,90,80,70,60,50,40,30,20,10,0};
std::vector<double> CutToSurface_bins{-200,-190,-180,-170,-160,-150,-140,-130,-120,-110,-100,-90,-80,-70,-60,-50,-40,-30,-20,-10,0.0,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200};

//PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_resolutionR_FidiucalCut("h_resolutionR_FidiucalCut", "h_resolutionR_FidiucalCut",  CutToSurface_bins ,  Vertex_resolution_Rbin_vector, error_bands);
//PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_resolutionZ_FidiucalCut("h_resolutionZ_FidiucalCut", "h_resolutionZ_FidiucalCut",  CutToSurface_bins , Vertex_resolution_Zbin_vector, error_bands);
MnvH2D *h_resolutionX_FidiucalCut          =    new MnvH2D("h_resolutionX_FidiucalCut", "h_resolutionX_FidiucalCut",  CutToSurface_bins.size()-1,  CutToSurface_bins.data(), Vertex_resolution_Xbin_vector.size()-1, Vertex_resolution_Xbin_vector.data()  );
MnvH2D *h_resolutionY_FidiucalCut          =    new MnvH2D("h_resolutionY_FidiucalCut", "h_resolutionY_FidiucalCut",  CutToSurface_bins.size()-1,  CutToSurface_bins.data(), Vertex_resolution_Ybin_vector.size()-1, Vertex_resolution_Ybin_vector.data()  );

MnvH2D *h_resolutionR_FidiucalCut          =    new MnvH2D("h_resolutionR_FidiucalCut", "h_resolutionR_FidiucalCut",  CutToSurface_bins.size()-1,  CutToSurface_bins.data(), Vertex_resolution_Rbin_vector.size()-1, Vertex_resolution_Rbin_vector.data()  );
MnvH2D *h_resolutionZ_FidiucalCut         =     new MnvH2D("h_resolutionZ_FidiucalCut", "h_resolutionZ_FidiucalCut",  CutToSurface_bins.size()-1,  CutToSurface_bins.data(), Vertex_resolution_Zbin_vector.size()-1, Vertex_resolution_Zbin_vector.data()  );
//MnvH2D *h_resolutionR_FidiucalCut_RECO          =    new MnvH2D("h_resolutionR_FidiucalCut_RECO", "h_resolutionR_FidiucalCut_RECO",  CutToSurface_bins.size()-1,  CutToSurface_bins.data(), Vertex_resolution_Rbin_vector.size()-1, Vertex_resolution_Rbin_vector.data()  );
//MnvH2D *h_resolutionZ_FidiucalCut_RECO         =    new MnvH2D("h_resolutionZ_FidiucalCut_RECO", "h_resolutionZ_FidiucalCut_RECO",  CutToSurface_bins.size()-1,  CutToSurface_bins.data(), Vertex_resolution_Zbin_vector.size()-1, Vertex_resolution_Zbin_vector.data()  );

MnvH2D *h_resolutionR_FidiucalCut_helium          =    new MnvH2D("h_resolutionR_FidiucalCut_helium", "h_resolutionR_FidiucalCut_helium",  CutToSurface_bins.size()-1,  CutToSurface_bins.data(), Vertex_resolution_Rbin_vector.size()-1, Vertex_resolution_Rbin_vector.data()  );
MnvH2D *h_resolutionZ_FidiucalCut_helium         =     new MnvH2D("h_resolutionZ_FidiucalCut_helium", "h_resolutionZ_FidiucalCut_helium",  CutToSurface_bins.size()-1,  CutToSurface_bins.data(), Vertex_resolution_Zbin_vector.size()-1, Vertex_resolution_Zbin_vector.data()  );

MnvH2D *h_resolutionR_FidiucalCut_nonhelium          =    new MnvH2D("h_resolutionR_FidiucalCut_nonhelium", "h_resolutionR_FidiucalCut_nonhelium",  CutToSurface_bins.size()-1,  CutToSurface_bins.data(), Vertex_resolution_Rbin_vector.size()-1, Vertex_resolution_Rbin_vector.data()  );
MnvH2D *h_resolutionZ_FidiucalCut_nonhelium         =     new MnvH2D("h_resolutionZ_FidiucalCut_nonhelium", "h_resolutionZ_FidiucalCut_nonhelium",  CutToSurface_bins.size()-1,  CutToSurface_bins.data(), Vertex_resolution_Zbin_vector.size()-1, Vertex_resolution_Zbin_vector.data()  );


  std::vector<Vertex_XYZ> FiducalCut_Neg200;
  std::vector<Vertex_XYZ> FiducalCut_Neg150;
  std::vector<Vertex_XYZ> FiducalCut_Neg100;
  std::vector<Vertex_XYZ> FiducalCut_Neg50;
  std::vector<Vertex_XYZ> FiducalCut;
  std::vector<Vertex_XYZ> FiducalCut_50;
  std::vector<Vertex_XYZ> FiducalCut_100;



PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_RR_TRUE_RECO("h_CryoVertex_RR_TRUE_RECO", "h_CryoVertex_RR_TRUE_RECO",  Vertex_RRbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_recoRR_TRUE_RECO("h_CryoVertex_recoRR_TRUE_RECO", "h_CryoVertex_recoRR_TRUE_RECO",  Vertex_RRbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_resolutionRR_TRUE_RECO("h_CryoVertex_resolutionRR_TRUE_RECO", "h_CryoVertex_resolutionRR_TRUE_RECO",  Vertex_resolution_RRbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Percent_resolutionRR_TRUE_RECO("h_CryoVertex_Percent_resolutionRR_TRUE_RECO", "h_CryoVertex_Percent_resolutionRR_TRUE_RECO",  Vertex_Percent_resolution_RRbin_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_recoRR_RECO("h_CryoVertex_recoRR_RECO", "h_CryoVertex_recoRR_RECO",  Vertex_RRbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_resolutionRR_RECO("h_CryoVertex_resolutionRR_RECO", "h_CryoVertex_resolutionRR_RECO",  Vertex_resolution_RRbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Percent_resolutionRR_RECO("h_CryoVertex_Percent_resolutionRR_RECO", "h_CryoVertex_Percent_resolutionRR_RECO",  Vertex_Percent_resolution_RRbin_vector , error_bands);



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




PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertexChiSqFit_TRUE_RECO("h_CryoVertexChiSqFit_TRUE_RECO", "h_CryoVertexChiSqFit_TRUE_RECO",  Vertex_ChiSqFit_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Openangle_TRUE_RECO("h_secTrk_Openangle_TRUE_RECO", "h_secTrk_Openangle ",  secTrk_Theta_TRUEbin_vector , error_bands);


PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_Openangle_TRUE_RECO_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_Openangle_TRUE_RECO_Material", secTrk_Theta_TRUEbin_vector ,"h_secTrk_Openangle_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_secTrk_Openangle_TRUE_RECO_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_secTrk_Openangle_TRUE_RECO_Interaction", secTrk_Theta_TRUEbin_vector ,"h_secTrk_Openangle_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_Openangle_TRUE_RECO_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_Openangle_TRUE_RECO_Particle", secTrk_Theta_TRUEbin_vector ,"h_secTrk_Openangle_Particle; [mm];Events");
//h_secTrk_Openangle_TRUE_RECO_Particle.ApplyColorPalette(Helium9_colorScheme);

PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Pathlength_TRUE_RECO("h_secTrk_Pathlength_TRUE_RECO", "h_secTrk Pathlength ",  Vertex_secondTrkPathway_bins , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Pathlength_PROTON_TRUE_RECO("h_secTrk_Pathlength_PROTON_TRUE_RECO", "h_secTrk Pathlength Proton",  Vertex_secondTrkPathway_bins , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Pathlength_PION_TRUE_RECO("h_secTrk_Pathlength_PION_TRUE_RECO", "h_secTrk Pathlength pion ",  Vertex_secondTrkPathway_bins , error_bands);


PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_Pathlength_TRUE_RECO_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_Pathlength_TRUE_RECO_Material", Vertex_secondTrkPathway_bins ,"h_secTrk_Pathlength_TRUE_RECO_Material; [cm^2/g];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_secTrk_Pathlength_TRUE_RECO_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_secTrk_Pathlength_TRUE_RECO_Interaction", Vertex_secondTrkPathway_bins ,"h_secTrk_Pathlength_TRUE_RECO_Interaction; [cm^2/g];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_Pathlength_TRUE_RECO_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_Pathlength_TRUE_RECO_Particle", Vertex_secondTrkPathway_bins ,"h_secTrk_Pathlength_TRUE_RECO_Particle; [cm^2/g];Events");
//h_secTrk_Pathlength_TRUE_RECO_Particle.ApplyColorPalette(Helium9_colorScheme);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Theta_TRUE_RECO("h_secTrk_Theta_TRUE_RECO", "h_secTrk_MidTheta NEW Method",  secTrk_Theta_TRUEbin_vector , error_bands);


//PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_ThetaLeading_TRUE_RECO("h_secTrk_ThetaLeading_TRUE_RECO", "h_secTrk_ThetaLeading_TRUE_RECO",  secTrk_Theta_TRUEbin_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Energy_TRUE_RECO("h_secTrk_Energy_TRUE_RECO", "h_secTrk_Energy NEW Method",  Vertex_secondTrkEbins, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_EnergyFINEBinning_TRUE_RECO("h_secTrk_EnergyFINEBinning_TRUE_RECO", "h_secTrk_Energy NEW Method",  Vertex_secondTrkEbin_Proton_vector, error_bands);


PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_Energy_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_Energy_Material", Vertex_secondTrkEbins ,"h_secTrk_Energy_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_secTrk_Energy_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_secTrk_Energy_Interaction", Vertex_secondTrkEbins ,"h_secTrk_Energy_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_Energy_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_Energy_Particle", Vertex_secondTrkEbins ,"h_secTrk_Energy_Particle; [GeV];Events");
//h_secTrk_Energy_Particle.ApplyColorPalette(Helium9_colorScheme);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_nonparentEnergy_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_nonparentEnergy_Particle", Vertex_secondTrkEbins ,"h_secTrk_nonparentEnergy_Particle; [GeV];Events");


PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_Energy_TRUE_RECO_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_Energy_TRUE_RECO_Material", Vertex_secondTrkEbin_Proton_vector ,"h_secTrk_Energy_TRUE_RECO_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_secTrk_Energy_TRUE_RECO_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_secTrk_Energy_TRUE_RECO_Interaction", Vertex_secondTrkEbin_Proton_vector ,"h_secTrk_Energy_TRUE_RECO_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_Energy_TRUE_RECO_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_Energy_TRUE_RECO_Particle", Vertex_secondTrkEbin_Proton_vector ,"h_secTrk_Energy_TRUE_RECO_Particle; [GeV];Events");
//h_secTrk_Energy_TRUE_RECO_Particle.ApplyColorPalette(Helium9_colorScheme);


PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Energy_PION_TRUE_RECO("h_secTrk_Energy_PION_TRUE_RECO", "h_secTrk_Energy PION(TRUE +RECO)",  Vertex_secondTrkEbin_Proton_vector, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Theta_PION_TRUE_RECO("h_secTrk_Theta_PION_TRUE_RECO", "h_secTrk_Theta PION (TRUE+RECO)",  secTrk_Theta_TRUEbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Openangle_PION_TRUE_RECO("h_secTrk_Openangle_PION_TRUE_RECO", "h_secTrk_Openangle  PION (TRUE+RECO)",  secTrk_Theta_TRUEbin_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Energy_PROTON_TRUE_RECO("h_secTrk_Energy_PROTON_TRUE_RECO", "h_secTrk_Energy Proton(TRUE+RECO)",  Vertex_secondTrkEbin_Proton_vector, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Theta_PROTON_TRUE_RECO("h_secTrk_Theta_PROTON_TRUE_RECO", "h_secTrk_Theta Proton(TRUE+RECO)",  secTrk_Theta_TRUEbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Openangle_PROTON_TRUE_RECO("h_secTrk_Openangle_PROTON_TRUE_RECO", "h_secTrk_Openangle Proton(TRUE+RECO) ",  secTrk_Theta_TRUEbin_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Energy_Dimuon_TRUE_RECO("h_secTrk_Energy_Dimuon_TRUE_RECO", "h_secTrk_Energy Dimuon(TRUE+RECO)",  Vertex_secondTrkEbin_Proton_vector, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Theta_Dimuon_TRUE_RECO("h_secTrk_Theta_Dimuon_TRUE_RECO", "h_secTrk_Theta Dimuon(TRUE+RECO)",  secTrk_Theta_TRUEbin_vector , error_bands);
/////////////////////////////////////////
//2D
/////////////////////////////////////////
//PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_secTrkTheta_cryoVertex_Z_TRUE_RECO("h_secTrkTheta_cryoVertex_Z_TRUE_RECO", "h_secTrkTheta_cryoVertex_Z_TRUE_RECO",  Vertex_Zbin_vector ,secTrk_Theta_TRUEbin_vector, error_bands);
//PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_secTrkTheta_cryoVertex_R_TRUE_RECO("h_secTrkTheta_cryoVertex_R_TRUE_RECO", "h_secTrkTheta_cryoVertex_R_TRUE_RECO",  Vertex_Rbin_vector ,secTrk_Theta_TRUEbin_vector,  error_bands);

MnvH2D *h_cryoVertex_Z_secTrkTheta_TRUE_RECO =    new MnvH2D("h_cryoVertex_Z_secTrkTheta_TRUE_RECO", "h_cryoVertex_Z_secTrkTheta_TRUE_RECO",  Vertex_Zbin_vector.size()-1,  Vertex_Zbin_vector.data(), Vertex_secondTrkTheta_Coarse_bins.size()-1, Vertex_secondTrkTheta_Coarse_bins.data()  );
MnvH2D *h_cryoVertex_R_secTrkTheta_TRUE_RECO =    new MnvH2D("h_cryoVertex_R_secTrkTheta_TRUE_RECO", "h_cryoVertex_R_secTrkTheta_TRUE_RECO",  Vertex_Rbin_vector.size()-1,  Vertex_Rbin_vector.data(), Vertex_secondTrkTheta_Coarse_bins.size()-1, Vertex_secondTrkTheta_Coarse_bins.data()  );
MnvH2D *h_cryoVertex_Z_R_TRUE_RECO           =    new MnvH2D("h_cryoVertex_Z_R_TRUE_RECO", "h_cryoVertex_Z_R_TRUE_RECO", Vertex_Zbin_vector.size()-1,  Vertex_Zbin_vector.data(),  Vertex_Rbin_vector.size()-1,  Vertex_Rbin_vector.data()  );


MnvH2D *h_muonPT_2ndTrkangle_TRUE_RECO     =    new MnvH2D("h_muonPT_2ndTrkangle_TRUE_RECO",    "h_muonPT_2ndTrkangle_TRUE_RECO",     PTbin_vector.size()-1,  PTbin_vector.data(),               Vertex_secondTrkTheta_Coarse_bins.size()-1, Vertex_secondTrkTheta_Coarse_bins.data()  );
MnvH2D *h_muonPZ_2ndTrkangle_TRUE_RECO     =    new MnvH2D("h_muonPZ_2ndTrkangle_TRUE_RECO",    "h_muonPZ_2ndTrkangle_TRUE_RECO",     Pzbin_vector.size()-1,  Pzbin_vector.data(),               Vertex_secondTrkTheta_Coarse_bins.size()-1, Vertex_secondTrkTheta_Coarse_bins.data()  );
MnvH2D *h_muontheta_2ndTrkangle_TRUE_RECO  =    new MnvH2D("h_muontheta_2ndTrkangle_TRUE_RECO", "h_muontheta_2ndTrkangle_TRUE_RECO",  MuonThetabin_vector.size()-1,  MuonThetabin_vector.data(), Vertex_secondTrkTheta_Coarse_bins.size()-1, Vertex_secondTrkTheta_Coarse_bins.data()  );
//MnvH2D *h_2ndtrkPathlength_2ndTrkE_TRUE    =    new MnvH2D("h_2ndtrkPathlength_2ndTrkE_TRUE", "h_2ndtrkPathlength_2ndTrkE_TRUE", Vertex_secondTrkPathway_bins.size()-1, Vertex_secondTrkPathway_bins.data(), Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );

MnvH2D *h_2ndTrkE_2ndtrkangle_TRUE_RECO         =    new MnvH2D("h_2ndTrkE_2ndtrkangle_TRUE_RECO",        "h_2ndTrkE_2ndtrkangle_TRUE_RECO",        Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data(), Vertex_secondTrkTheta_Coarse_bins.size()-1, Vertex_secondTrkTheta_Coarse_bins.data()  );
MnvH2D *h_2ndTrkE_2ndtrkangle_Proton_TRUE_RECO  =    new MnvH2D("h_2ndTrkE_2ndtrkangle_Proton_TRUE_RECO", "h_2ndTrkE_2ndtrkangle_Proton_TRUE_RECO", Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data(), Vertex_secondTrkTheta_Coarse_bins.size()-1, Vertex_secondTrkTheta_Coarse_bins.data()  );
MnvH2D *h_2ndTrkE_2ndtrkangle_Pion_TRUE_RECO    =    new MnvH2D("h_2ndTrkE_2ndtrkangle_Pion_TRUE_RECO",   "h_2ndTrkE_2ndtrkangle_Pion_TRUE_RECO",   Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data(), Vertex_secondTrkTheta_Coarse_bins.size()-1, Vertex_secondTrkTheta_Coarse_bins.data()  );


MnvH2D *h_cryoVertex_Z_Pathlength_TRUE_RECO        =    new MnvH2D("h_cryoVertex_Z_Pathlength_TRUE_RECO", "h_cryoVertex_Z_Pathlength_TRUE_RECO",  Vertex_Zbin_vector.size()-1,  Vertex_Zbin_vector.data(), Vertex_secondTrkPathway_bins.size()-1, Vertex_secondTrkPathway_bins.data()  );
MnvH2D *h_cryoVertex_R_Pathlength_TRUE_RECO        =    new MnvH2D("h_cryoVertex_R_Pathlength_TRUE_RECO", "h_cryoVertex_R_Pathlength_TRUE_RECO",  Vertex_Rbin_vector.size()-1,  Vertex_Rbin_vector.data(), Vertex_secondTrkPathway_bins.size()-1, Vertex_secondTrkPathway_bins.data()  );

MnvH2D *h_cryoVertex_Z_DOCA_TRUE_RECO        =    new MnvH2D("h_cryoVertex_Z_DOCA_TRUE_RECO", "h_cryoVertex_Z_DOCA_TRUE_RECO",  Vertex_Zbin_vector.size()-1,  Vertex_Zbin_vector.data(), Vertex_secondTrkDOCA_bins.size()-1, Vertex_secondTrkDOCA_bins.data()  );
MnvH2D *h_cryoVertex_R_DOCA_TRUE_RECO        =    new MnvH2D("h_cryoVertex_R_DOCA_TRUE_RECO", "h_cryoVertex_R_DOCA_TRUE_RECO",  Vertex_Rbin_vector.size()-1,  Vertex_Rbin_vector.data(), Vertex_secondTrkDOCA_bins.size()-1, Vertex_secondTrkDOCA_bins.data()  );

MnvH2D *h_cryoVertex_Z_2ndTrkE_TRUE_RECO        =    new MnvH2D("h_cryoVertex_Z_2ndTrkE_TRUE_RECO", "h_cryoVertex_Z_2ndTrkE_TRUE_RECO",  Vertex_Zbin_vector.size()-1,  Vertex_Zbin_vector.data(), Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );
MnvH2D *h_cryoVertex_R_2ndTrkE_TRUE_RECO        =    new MnvH2D("h_cryoVertex_R_2ndTrkE_TRUE_RECO", "h_cryoVertex_R_2ndTrkE_TRUE_RECO",  Vertex_Rbin_vector.size()-1,  Vertex_Rbin_vector.data(), Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );

  //=========================================
  // Entry Loop For MC
  //=========================================

  //std::vector<ECuts> kCutsVector;

  RECO_Cut_Map CountMap_MuonEnergy;
  FillingRecoCountingMap(kCutsVector_MuonEnergy, CountMap_MuonEnergy);
  RECO_Cut_Map CountMap_MuonTheta;
  FillingRecoCountingMap(kCutsVector_MuonThetaEff, CountMap_MuonTheta);
  RECO_Cut_Map CountMap_2ndTrkEnergy;
  FillingRecoCountingMap(kCutsVector_2ndtrkEnergy, CountMap_2ndTrkEnergy);
  RECO_Cut_Map CountMap_2ndTrkAngle;
  FillingRecoCountingMap(kCutsVector_2ndtrkAngle, CountMap_2ndTrkAngle);
  RECO_Cut_Map CountMap_Fiduical;
  FillingRecoCountingMap(kCutsVector_FiduicalEff, CountMap_Fiduical);
  RECO_Cut_Map CountMap_2ndTrkAngle_noFidiucal;
  FillingRecoCountingMap(kCutsVector_2ndtrkAngle_noFidiucal, CountMap_2ndTrkAngle_noFidiucal);

  TRUE_Cut_Map Truth_Cut_Map_MuonEnergy;
  TRUE_Cut_Map Truth_Cut_Map_MuonTheta;
  TRUE_Cut_Map Truth_Cut_Map_Fiduical;
  TRUE_Cut_Map Truth_Cut_Map_2ndTrkEnergy;
  TRUE_Cut_Map Truth_Cut_Map_2ndTrkAngle;


  FillingTruthCountingMap(kTRUTHCutsVector_MuonEnergy,   Truth_Cut_Map_MuonEnergy);
  FillingTruthCountingMap(kTRUTHCutsVector_MuonTheta,    Truth_Cut_Map_MuonTheta);
  FillingTruthCountingMap(kTRUTHCutsVector_Fiduical,     Truth_Cut_Map_Fiduical);
  FillingTruthCountingMap(kTRUTHCutsVector_2ndTrkEnergy, Truth_Cut_Map_2ndTrkEnergy);
  FillingTruthCountingMap(kTRUTHCutsVector_2ndTrkAngle,  Truth_Cut_Map_2ndTrkAngle);




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
//RECO_Cut_Map CountMap_RECO;// = ConstuctRecoCountingMap(kCutsVector);
//RECO_Cut_Map CountMap_RECO_Helium ;//= ConstuctRecoCountingMap(kCutsVector);
//RECO_Cut_Map CountMap_RECO_nonHelium;// = ConstuctRecoCountingMap(kCutsVector);

//FillingRecoCountingMap(kCutsVector, CountMap_RECO);
//FillingRecoCountingMap(kCutsVector, CountMap_RECO_Helium);
//FillingRecoCountingMap(kCutsVector, CountMap_RECO_nonHelium);

//std::cout << "CountMap_RECO.size() = " << CountMap_RECO.size()<< std::endl;
//for(const auto & index :CountMap_RECO ){
//std::cout<<" Cut Name = " <<GetCutName(index.first).c_str() << " Amount = " << index.second << std::endl;


//}



std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;
std::cout<<"~~~~~~~~~  THIS IS RECO 1D ~~~~~~~~~ "<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;


int PDG_notmatch=0;
int PDG_match=0;

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



    if(PassesCutsTRUTH(*Universe_GROUP.front(), kTRUTHCutsVector_MuonTheta, kWeights_v1tune, Truth_Cut_Map_MuonTheta)){
      // TRUTH ONLY Cuts
      if(PassesCutsRECO(*Universe_GROUP.front(),  is_mc , kCutsVector_MuonThetaEff, kWeights_v1tune, CountMap_MuonEnergy) ){
        for (auto universe : Universe_GROUP){
          universe->SetEntry(ii);

          h_MuonTheta_TRUE_RECO.univHist(universe)->Fill(universe->GetTRUE_muANGLE_WRTB_DEG(),universe->GetWeight(kWeights_v1tune));

          if(isCV(*universe)){
            auto PDG_trklist = universe->GetVector_nonMuonTk_PDG_Parent();
            auto Energy_trklist = universe-> GetVector_nonMuonTk_Energy_GeV_Parent();
            auto Angle_trklist = universe->GetVector_nonMuonTk_Angle_wrtb_Degs_Parent();
            auto EnergyFraction_vector = universe->Get_TrueFractionE_vector();

            int secondTrk = universe->Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_muonNotinlist(PDG_trklist, Energy_trklist, EnergyFraction_vector);
/*
            std::cout << "PDG_trklist.size() = " << PDG_trklist.size() << "  Energy_trklist.size() = " << Energy_trklist.size() << "Angle_trklist.size() = " <<  Angle_trklist.size() << "  EnergyFraction_vector.size() = " << EnergyFraction_vector.size()<< std::endl;
            std::cout<<"where is this bug in secondTrk =  "<< secondTrk<< std::endl;
            for(int y = 0; y < PDG_trklist.size(); y++){
              std::cout<< "PDG_trklist = " << PDG_trklist.at(y) <<  "Energy_trklist = "<< Energy_trklist.at(y) << "Energy_trklist = "<< Energy_trklist.at(y) << " EnergyFraction_vector = "<< EnergyFraction_vector.at(y)<< std::endl;
            }
*/

            h_muontheta_2ndTrkangle_TRUE_RECO->Fill(universe->GetTRUE_muANGLE_WRTB_DEG(), Angle_trklist.at(secondTrk),universe->GetWeight(kWeights_v1tune));
            //std::cout<<"where is this bug out "<< std::endl;

          }//end of CV


        }// END of Universe Groups
      }// END OF TRUTH + RECO CUTS
    }//END OF TRUTH PASS CUTS


    if(PassesCutsTRUTH(*Universe_GROUP.front(), kTRUTHCutsVector_MuonEnergy,  kWeights_v1tune, Truth_Cut_Map_MuonEnergy)){
      // TRUTH ONLY Cuts
      if(PassesCutsRECO(*Universe_GROUP.front(),  is_mc, kCutsVector_MuonEnergy, kWeights_v1tune, CountMap_MuonEnergy) ){
        for (auto universe : Universe_GROUP){
          universe->SetEntry(ii);

          double wgt_minerva_v1 =   universe->GetWeight(kWeights_v1tune);


          h_MuonE_TRUE_RECO.univHist(universe)->Fill(universe->GetTRUE_Emu(), wgt_minerva_v1);

          h_MuonPZ_TRUE_RECO.univHist(universe)->Fill(universe->GetPmuLongitudinalTrue(),wgt_minerva_v1);

          h_MuonPT_TRUE_RECO.univHist(universe)->Fill(universe->GetPmuTransverseTrue(),wgt_minerva_v1);

        }// END of Universe Groups
      }// END OF TRUTH + RECO CUTS
    }//END OF TRUTH PASS CUTS



    if(PassesCutsTRUTH(*Universe_GROUP.front(), kTRUTHCutsVector_Fiduical , kWeights_v1tune, Truth_Cut_Map_Fiduical )){
      // TRUTH ONLY Cuts
      if(PassesCutsRECO(*Universe_GROUP.front(),  is_mc , kCutsVector_FiduicalEff , kWeights_v1tune, CountMap_Fiduical ) ){
        for (auto universe : Universe_GROUP){
          universe->SetEntry(ii);

          double wgt_minerva_v1 = universe->GetWeight(kWeights_v1tune);

          double x= universe->GetVertex_x();
          double y= universe->GetVertex_y();
          double z= universe->GetVertex_z();
          double r= universe->GetVertex_r();
          double rr= universe->GetVertex_rr();


          double x_true= universe->GetTRUE_Vertex_x();
          double y_true= universe->GetTRUE_Vertex_y();
          double z_true= universe->GetTRUE_Vertex_z();
          double r_true= universe->GetTRUE_Vertex_r();
          double rr_true= universe->GetTRUE_Vertex_rr();

          h_CryoVertex_X_TRUE_RECO.univHist(universe)->Fill(x_true,wgt_minerva_v1);

          h_CryoVertex_Y_TRUE_RECO.univHist(universe)->Fill(y_true,wgt_minerva_v1);

          h_CryoVertex_Z_TRUE_RECO.univHist(universe)->Fill(z_true,wgt_minerva_v1);

          h_CryoVertex_R_TRUE_RECO.univHist(universe)->Fill(r_true,wgt_minerva_v1);

          h_CryoVertex_RR_TRUE_RECO.univHist(universe)->Fill(rr_true,wgt_minerva_v1);



          h_CryoVertex_recoX_TRUE_RECO.univHist(universe)->Fill(x,wgt_minerva_v1);

          h_CryoVertex_recoY_TRUE_RECO.univHist(universe)->Fill(y,wgt_minerva_v1);

          h_CryoVertex_recoZ_TRUE_RECO.univHist(universe)->Fill(z,wgt_minerva_v1);

          h_CryoVertex_recoR_TRUE_RECO.univHist(universe)->Fill(r,wgt_minerva_v1);

          h_CryoVertex_recoRR_TRUE_RECO.univHist(universe)->Fill(rr,wgt_minerva_v1);


          h_CryoVertex_resolutionX_TRUE_RECO.univHist(universe)->Fill(x_true - x,wgt_minerva_v1);
          h_CryoVertex_resolutionY_TRUE_RECO.univHist(universe)->Fill(y_true - y,wgt_minerva_v1);
          h_CryoVertex_resolutionZ_TRUE_RECO.univHist(universe)->Fill(z_true - z,wgt_minerva_v1);
          h_CryoVertex_resolutionR_TRUE_RECO.univHist(universe)->Fill(r_true - r,wgt_minerva_v1);
          h_CryoVertex_resolutionRR_TRUE_RECO.univHist(universe)->Fill(rr_true - rr,wgt_minerva_v1);

          h_CryoVertex_Percent_resolutionX_TRUE_RECO.univHist(universe)->Fill((x_true - x)/ x_true,wgt_minerva_v1);
          h_CryoVertex_Percent_resolutionY_TRUE_RECO.univHist(universe)->Fill((y_true - y)/ y_true,wgt_minerva_v1);
          h_CryoVertex_Percent_resolutionZ_TRUE_RECO.univHist(universe)->Fill((z_true - z)/ z_true,wgt_minerva_v1);
          h_CryoVertex_Percent_resolutionR_TRUE_RECO.univHist(universe)->Fill((r_true - r)/ r_true,wgt_minerva_v1);
          h_CryoVertex_Percent_resolutionRR_TRUE_RECO.univHist(universe)->Fill((rr_true - rr)/ rr_true,wgt_minerva_v1);






          if(isCV(*universe)){

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
            Particle_type Particle_type_Event = GetParticlegroup_type(secTrk_PDG);
            Interaction_type Interaction_type_Event =  universe->Get_InteractionStackType();
            Material_type Material_type_Event = universe->Get_MaterialStackType();

            h_CryoVertex_X_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetVertex_x(), wgt_minerva_v1);
            h_CryoVertex_X_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetVertex_x(), wgt_minerva_v1);
            h_CryoVertex_X_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetVertex_x(), wgt_minerva_v1);

            h_CryoVertex_Y_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetVertex_y(), wgt_minerva_v1);
            h_CryoVertex_Y_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetVertex_y(), wgt_minerva_v1);
            h_CryoVertex_Y_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetVertex_y(), wgt_minerva_v1);

            h_CryoVertex_Z_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetVertex_z(), wgt_minerva_v1);
            h_CryoVertex_Z_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetVertex_z(), wgt_minerva_v1);
            h_CryoVertex_Z_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetVertex_z(), wgt_minerva_v1);

            h_CryoVertex_R_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetVertex_r(), wgt_minerva_v1);
            h_CryoVertex_R_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetVertex_r(), wgt_minerva_v1);
            h_CryoVertex_R_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetVertex_r(), wgt_minerva_v1);


          }



        }// END of Universe Groups
      }// END OF TRUTH + RECO CUTS
    }//END OF TRUTH PASS CUTS


      if(PassesCutsRECO(*Universe_GROUP.front(),  is_mc , kCutsVector_FiduicalEff , kWeights_v1tune, CountMap_Fiduical ) ){
        for (auto universe : Universe_GROUP){
          universe->SetEntry(ii);

          double wgt_minerva_v1 = universe->GetWeight(kWeights_v1tune);

          double x= universe->GetVertex_x();
          double y= universe->GetVertex_y();
          double z= universe->GetVertex_z();
          double r= universe->GetVertex_r();
          double rr= universe->GetVertex_rr();

          double x_true= universe->GetTRUE_Vertex_x();
          double y_true= universe->GetTRUE_Vertex_y();
          double z_true= universe->GetTRUE_Vertex_z();
          double r_true= universe->GetTRUE_Vertex_r();
          double rr_true= universe->GetTRUE_Vertex_rr();

          double resolutionX = x_true - x;
          double resolutionY = y_true - y;
          double resolutionZ = z_true - z;
          double resolutionR = r_true - r;
          double resolutionRR = rr_true - r;

          h_CryoVertex_resolutionX_RECO.univHist(universe)->Fill(resolutionX,wgt_minerva_v1);
          h_CryoVertex_resolutionY_RECO.univHist(universe)->Fill(resolutionY,wgt_minerva_v1);
          h_CryoVertex_resolutionZ_RECO.univHist(universe)->Fill(resolutionZ,wgt_minerva_v1);
          h_CryoVertex_resolutionR_RECO.univHist(universe)->Fill(resolutionR,wgt_minerva_v1);
          h_CryoVertex_resolutionRR_RECO.univHist(universe)->Fill(resolutionRR,wgt_minerva_v1);

          h_CryoVertex_Percent_resolutionX_RECO.univHist(universe)->Fill(resolutionX / x_true,wgt_minerva_v1);
          h_CryoVertex_Percent_resolutionY_RECO.univHist(universe)->Fill(resolutionY / y_true,wgt_minerva_v1);
          h_CryoVertex_Percent_resolutionZ_RECO.univHist(universe)->Fill(resolutionZ / z_true,wgt_minerva_v1);
          h_CryoVertex_Percent_resolutionR_RECO.univHist(universe)->Fill(resolutionR / r_true,wgt_minerva_v1);
          h_CryoVertex_Percent_resolutionRR_RECO.univHist(universe)->Fill(resolutionRR / rr_true,wgt_minerva_v1);



          if(isCV(*universe)){
            auto PDG_trklist = universe->GetVector_nonMuonTk_PDG_Parent();
            auto Energy_trklist = universe-> GetVector_nonMuonTk_Energy_GeV_Parent();
            auto Angle_trklist = universe->GetVector_nonMuonTk_Angle_wrtb_Degs_Parent();
            auto EnergyFraction_vector = universe->Get_TrueFractionE_vector();
            //int secondTrk = universe->Getindex2ndTrackhighestKE();

            int secondTrk = universe->Get_Index_highestKE_mc_FSPart_WithDeglessthan(54.0, Energy_trklist, Angle_trklist, PDG_trklist);
            //int secondTrk = universe->Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_lessthanAngle_muonNotinlist(PDG_trklist, Energy_trklist, Angle_trklist, EnergyFraction_vector);
            if(secondTrk==-999){std::cout<<"ERROR got -999 for secondtrk "<<std::endl; assert(false);};

            int secTrk_PDG = PDG_trklist.at(secondTrk);
            Particle_type Particle_type_Event = GetParticlegroup_type(secTrk_PDG);
            Interaction_type Interaction_type_Event =  universe->Get_InteractionStackType();
            Material_type Material_type_Event = universe->Get_MaterialStackType();

            h_CryoVertex_resolutionX_RECO_Material.GetComponentHist(Material_type_Event)->Fill(resolutionX, wgt_minerva_v1);
            h_CryoVertex_resolutionX_RECO_Interaction.GetComponentHist(Interaction_type_Event)->Fill(resolutionX, wgt_minerva_v1);
            h_CryoVertex_resolutionX_RECO_Particle.GetComponentHist(Particle_type_Event)->Fill(resolutionX, wgt_minerva_v1);

            h_CryoVertex_resolutionY_RECO_Material.GetComponentHist(Material_type_Event)->Fill(resolutionY, wgt_minerva_v1);
            h_CryoVertex_resolutionY_RECO_Interaction.GetComponentHist(Interaction_type_Event)->Fill(resolutionY, wgt_minerva_v1);
            h_CryoVertex_resolutionY_RECO_Particle.GetComponentHist(Particle_type_Event)->Fill(resolutionY, wgt_minerva_v1);

            h_CryoVertex_resolutionR_RECO_Material.GetComponentHist(Material_type_Event)->Fill(resolutionR, wgt_minerva_v1);
            h_CryoVertex_resolutionR_RECO_Interaction.GetComponentHist(Interaction_type_Event)->Fill(resolutionR, wgt_minerva_v1);
            h_CryoVertex_resolutionR_RECO_Particle.GetComponentHist(Particle_type_Event)->Fill(resolutionR, wgt_minerva_v1);

            h_CryoVertex_resolutionZ_RECO_Material.GetComponentHist(Material_type_Event)->Fill(resolutionZ, wgt_minerva_v1);
            h_CryoVertex_resolutionZ_RECO_Interaction.GetComponentHist(Interaction_type_Event)->Fill(resolutionZ, wgt_minerva_v1);
            h_CryoVertex_resolutionZ_RECO_Particle.GetComponentHist(Particle_type_Event)->Fill(resolutionZ, wgt_minerva_v1);


            if(IsInExtraFiduicalVolume_Non_seperated_Cryo_regions(*universe, 20)){

              h_CryoVertex_resolutionR_fidiucal_RECO_Material.GetComponentHist(Material_type_Event)->Fill(resolutionR, wgt_minerva_v1);
              h_CryoVertex_resolutionR_fidiucal_RECO_Interaction.GetComponentHist(Interaction_type_Event)->Fill(resolutionR, wgt_minerva_v1);
              h_CryoVertex_resolutionR_fidiucal_RECO_Particle.GetComponentHist(Particle_type_Event)->Fill(resolutionR, wgt_minerva_v1);

              h_CryoVertex_resolutionZ_fidiucal_RECO_Material.GetComponentHist(Material_type_Event)->Fill(resolutionZ, wgt_minerva_v1);
              h_CryoVertex_resolutionZ_fidiucal_RECO_Interaction.GetComponentHist(Interaction_type_Event)->Fill(resolutionZ, wgt_minerva_v1);
              h_CryoVertex_resolutionZ_fidiucal_RECO_Particle.GetComponentHist(Particle_type_Event)->Fill(resolutionZ, wgt_minerva_v1);
            }


            for(auto Fid_Cut:CutToSurface_bins ){

              if(IsInExtraFiduicalVolume_Non_seperated_Cryo_regions(*universe, Fid_Cut)){

                h_resolutionX_FidiucalCut->Fill(Fid_Cut, resolutionX,  wgt_minerva_v1);

                h_resolutionY_FidiucalCut->Fill(Fid_Cut, resolutionY,  wgt_minerva_v1);

                h_resolutionR_FidiucalCut->Fill(Fid_Cut, resolutionR,  wgt_minerva_v1);

                h_resolutionZ_FidiucalCut->Fill(Fid_Cut, resolutionZ,  wgt_minerva_v1);


                if( universe->isHeliumInteraction() ){
                  h_resolutionR_FidiucalCut_helium->Fill(Fid_Cut, resolutionR,  wgt_minerva_v1);
                  h_resolutionZ_FidiucalCut_helium->Fill(Fid_Cut, resolutionZ,  wgt_minerva_v1);
                }
                else{
                  h_resolutionR_FidiucalCut_nonhelium->Fill(Fid_Cut, resolutionR,  wgt_minerva_v1);
                  h_resolutionZ_FidiucalCut_nonhelium->Fill(Fid_Cut, resolutionZ,  wgt_minerva_v1);
              }

                if(Fid_Cut==-200){
                  Vertex_XYZ XYZinput{universe->GetVertex_x(),universe->GetVertex_y(),universe->GetVertex_z()};
                  FiducalCut_Neg200.push_back(XYZinput);
                  //count_fid_neg_200= count_fid_neg_200 + wgt_minerva_v1;
                  count_fid_neg_200++;
                }
                else if(Fid_Cut==-150){
                  Vertex_XYZ XYZinput{universe->GetVertex_x(),universe->GetVertex_y(),universe->GetVertex_z()};
                  FiducalCut_Neg150.push_back(XYZinput);
                }
                else if(Fid_Cut==-100){
                  Vertex_XYZ XYZinput{universe->GetVertex_x(),universe->GetVertex_y(),universe->GetVertex_z()};
                  FiducalCut_Neg100.push_back(XYZinput);
                  h_CryoVertex_resolutionR_fidiucal_Neg100_RECO_Material.GetComponentHist(Material_type_Event)->Fill(resolutionR, wgt_minerva_v1);
                  h_CryoVertex_resolutionR_fidiucal_Neg100_RECO_Interaction.GetComponentHist(Interaction_type_Event)->Fill(resolutionR, wgt_minerva_v1);
                  h_CryoVertex_resolutionR_fidiucal_Neg100_RECO_Particle.GetComponentHist(Particle_type_Event)->Fill(resolutionR, wgt_minerva_v1);

                  h_CryoVertex_resolutionZ_fidiucal_Neg100_RECO_Material.GetComponentHist(Material_type_Event)->Fill(resolutionZ, wgt_minerva_v1);
                  h_CryoVertex_resolutionZ_fidiucal_Neg100_RECO_Interaction.GetComponentHist(Interaction_type_Event)->Fill(resolutionZ, wgt_minerva_v1);
                  h_CryoVertex_resolutionZ_fidiucal_Neg100_RECO_Particle.GetComponentHist(Particle_type_Event)->Fill(resolutionZ, wgt_minerva_v1);

                }
                else if(Fid_Cut==-50){
                  Vertex_XYZ XYZinput{universe->GetVertex_x(),universe->GetVertex_y(),universe->GetVertex_z()};
                  FiducalCut_Neg50.push_back(XYZinput);
                  h_CryoVertex_resolutionR_fidiucal_Neg50_RECO_Material.GetComponentHist(Material_type_Event)->Fill(resolutionR, wgt_minerva_v1);
                  h_CryoVertex_resolutionR_fidiucal_Neg50_RECO_Interaction.GetComponentHist(Interaction_type_Event)->Fill(resolutionR, wgt_minerva_v1);
                  h_CryoVertex_resolutionR_fidiucal_Neg50_RECO_Particle.GetComponentHist(Particle_type_Event)->Fill(resolutionR, wgt_minerva_v1);

                  h_CryoVertex_resolutionZ_fidiucal_Neg50_RECO_Material.GetComponentHist(Material_type_Event)->Fill(resolutionZ, wgt_minerva_v1);
                  h_CryoVertex_resolutionZ_fidiucal_Neg50_RECO_Interaction.GetComponentHist(Interaction_type_Event)->Fill(resolutionZ, wgt_minerva_v1);
                  h_CryoVertex_resolutionZ_fidiucal_Neg50_RECO_Particle.GetComponentHist(Particle_type_Event)->Fill(resolutionZ, wgt_minerva_v1);


                }
                else if(Fid_Cut==0){
                  Vertex_XYZ XYZinput{universe->GetVertex_x(),universe->GetVertex_y(),universe->GetVertex_z()};
                  FiducalCut.push_back(XYZinput);
                  //count_fid_0 = count_fid_0 + wgt_minerva_v1;
                  count_fid_0++;
                }
                else if(Fid_Cut==50){
                  Vertex_XYZ XYZinput{universe->GetVertex_x(),universe->GetVertex_y(),universe->GetVertex_z()};
                  FiducalCut_50.push_back(XYZinput);
                  count_fid_50++;
                  h_CryoVertex_resolutionR_fidiucal_50_RECO_Material.GetComponentHist(Material_type_Event)->Fill(resolutionR, wgt_minerva_v1);
                  h_CryoVertex_resolutionR_fidiucal_50_RECO_Interaction.GetComponentHist(Interaction_type_Event)->Fill(resolutionR, wgt_minerva_v1);
                  h_CryoVertex_resolutionR_fidiucal_50_RECO_Particle.GetComponentHist(Particle_type_Event)->Fill(resolutionR, wgt_minerva_v1);

                  h_CryoVertex_resolutionZ_fidiucal_50_RECO_Material.GetComponentHist(Material_type_Event)->Fill(resolutionZ, wgt_minerva_v1);
                  h_CryoVertex_resolutionZ_fidiucal_50_RECO_Interaction.GetComponentHist(Interaction_type_Event)->Fill(resolutionZ, wgt_minerva_v1);
                  h_CryoVertex_resolutionZ_fidiucal_50_RECO_Particle.GetComponentHist(Particle_type_Event)->Fill(resolutionZ, wgt_minerva_v1);

                }
                else if(Fid_Cut==100){
                  Vertex_XYZ XYZinput{universe->GetVertex_x(),universe->GetVertex_y(),universe->GetVertex_z()};
                  FiducalCut_100.push_back(XYZinput);
                  h_CryoVertex_resolutionR_fidiucal_100_RECO_Material.GetComponentHist(Material_type_Event)->Fill(resolutionR, wgt_minerva_v1);
                  h_CryoVertex_resolutionR_fidiucal_100_RECO_Interaction.GetComponentHist(Interaction_type_Event)->Fill(resolutionR, wgt_minerva_v1);
                  h_CryoVertex_resolutionR_fidiucal_100_RECO_Particle.GetComponentHist(Particle_type_Event)->Fill(resolutionR, wgt_minerva_v1);

                  h_CryoVertex_resolutionZ_fidiucal_100_RECO_Material.GetComponentHist(Material_type_Event)->Fill(resolutionZ, wgt_minerva_v1);
                  h_CryoVertex_resolutionZ_fidiucal_100_RECO_Interaction.GetComponentHist(Interaction_type_Event)->Fill(resolutionZ, wgt_minerva_v1);
                  h_CryoVertex_resolutionZ_fidiucal_100_RECO_Particle.GetComponentHist(Particle_type_Event)->Fill(resolutionZ, wgt_minerva_v1);

                }


              } // end of fiduical cut
            }// end of loop



          } // end of CV



        }// END of Universe Groups
      }// END OF RECO CUTS







    if(PassesCutsTRUTH(*Universe_GROUP.front(), kTRUTHCutsVector_2ndTrkEnergy , kWeights_v1tune, Truth_Cut_Map_2ndTrkEnergy)){
      // TRUTH ONLY Cuts
      if(PassesCutsRECO(*Universe_GROUP.front(),  is_mc, kCutsVector_2ndtrkEnergy, kWeights_v1tune, CountMap_2ndTrkEnergy) ){
        for (auto universe : Universe_GROUP){
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
          Particle_type Particle_type_Event = GetParticlegroup_type(secTrk_PDG);

          h_secTrk_Energy_TRUE_RECO.univHist(universe)->Fill(secTrkTrueEnergy,wgt_minerva_v1);
          h_secTrk_EnergyFINEBinning_TRUE_RECO.univHist(universe)->Fill(secTrkTrueEnergy,wgt_minerva_v1);
          h_secTrk_Pathlength_TRUE_RECO.univHist(universe)->Fill(universe->GetTRUE_nonMuoncolumnarDensity(secondTrk),wgt_minerva_v1);

          if(Particle_type_Event==kSecondary_particle_vector[0]){
            h_secTrk_Energy_PROTON_TRUE_RECO.univHist(universe)->Fill(secTrkTrueEnergy,wgt_minerva_v1);
            h_secTrk_Pathlength_PROTON_TRUE_RECO.univHist(universe)->Fill(universe->GetTRUE_nonMuoncolumnarDensity(secondTrk),wgt_minerva_v1);

          }
          if(Particle_type_Event==kSecondary_particle_vector[3]||Particle_type_Event==kSecondary_particle_vector[4])
          {
            h_secTrk_Energy_PION_TRUE_RECO.univHist(universe)->Fill(secTrkTrueEnergy,wgt_minerva_v1);
            h_secTrk_Pathlength_PION_TRUE_RECO.univHist(universe)->Fill(universe->GetTRUE_nonMuoncolumnarDensity(secondTrk),wgt_minerva_v1);

          }
          if(Particle_type_Event==kSecondary_particle_vector[1]){
            h_secTrk_Energy_Dimuon_TRUE_RECO.univHist(universe)->Fill(secTrkTrueEnergy,wgt_minerva_v1);
          }

          if(isCV(*universe)){
            Interaction_type Interaction_type_Event =  universe->Get_InteractionStackType();
            Material_type Material_type_Event = universe->Get_MaterialStackType();
            h_secTrk_Energy_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetNonmuTrkE_GeV(secondTrk), wgt_minerva_v1);
            h_secTrk_Energy_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetNonmuTrkE_GeV(secondTrk), wgt_minerva_v1);
            h_secTrk_Energy_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetNonmuTrkE_GeV(secondTrk), wgt_minerva_v1);


          }


        }// END of Universe Groups
      }// END OF TRUTH + RECO CUTS
    }//END OF TRUTH PASS CUTS


    if(PassesCutsTRUTH(*Universe_GROUP.front(), kTRUTHCutsVector_2ndTrkAngle, kWeights_v1tune, Truth_Cut_Map_2ndTrkAngle )){
      // TRUTH ONLY Cuts
      if(PassesCutsRECO(*Universe_GROUP.front(),  is_mc , kCutsVector_2ndtrkAngle, kWeights_v1tune, CountMap_2ndTrkAngle ) ){
        for (auto universe : Universe_GROUP){
          universe->SetEntry(ii);

          auto PDG_trklist = universe->GetVector_nonMuonTk_PDG_Parent();
          auto Energy_trklist = universe-> GetVector_nonMuonTk_Energy_GeV_Parent();
          auto Angle_trklist = universe->GetVector_nonMuonTk_Angle_wrtb_Degs_Parent();
          auto EnergyFraction_vector = universe->Get_TrueFractionE_vector();
          //int secondTrk = universe->Getindex2ndTrackhighestKE();


          int secondTrk = universe->Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_muonNotinlist(PDG_trklist, Energy_trklist, EnergyFraction_vector);
          if(secondTrk==-999)continue;

          double secTrkTrueAngle  = Angle_trklist.at(secondTrk);
          double secTrkEnergy = Energy_trklist.at(secondTrk);
          double wgt_minerva_v1 = universe->GetWeight(kWeights_v1tune);
          int secTrk_PDG = PDG_trklist.at(secondTrk);
          Particle_type Particle_type_Event = GetParticlegroup_type(secTrk_PDG);


          h_secTrk_Openangle_TRUE_RECO.univHist(universe)->Fill(universe->GetTRUE_NonmuTrkopenangle(secondTrk),wgt_minerva_v1);
          h_secTrk_Theta_TRUE_RECO.univHist(universe)->Fill(secTrkTrueAngle,wgt_minerva_v1);

          if(Particle_type_Event==kSecondary_particle_vector[0]){
            h_secTrk_Theta_PROTON_TRUE_RECO.univHist(universe)->Fill(secTrkTrueAngle,wgt_minerva_v1);
            h_secTrk_Openangle_PROTON_TRUE_RECO.univHist(universe)->Fill(universe->GetTRUE_NonmuTrkopenangle(secondTrk),wgt_minerva_v1);
          }
          if(Particle_type_Event==kSecondary_particle_vector[3]||Particle_type_Event==kSecondary_particle_vector[4])
          {
            h_secTrk_Theta_PION_TRUE_RECO.univHist(universe)->Fill(secTrkTrueAngle,wgt_minerva_v1);
            h_secTrk_Openangle_PION_TRUE_RECO.univHist(universe)->Fill(universe->GetTRUE_NonmuTrkopenangle(secondTrk),wgt_minerva_v1);
          }

          if(Particle_type_Event==kSecondary_particle_vector[1]){
            h_secTrk_Theta_Dimuon_TRUE_RECO.univHist(universe)->Fill(secTrkTrueAngle,wgt_minerva_v1);
          }

          ///===================
          // CV
          ///===================

          if(isCV(*universe)){
            h_muonPT_2ndTrkangle_TRUE_RECO->Fill(universe->GetTRUE_PTmu(),secTrkTrueAngle,wgt_minerva_v1);
            h_muonPZ_2ndTrkangle_TRUE_RECO->Fill(universe->GetTRUE_PZmu(),secTrkTrueAngle,wgt_minerva_v1);
            h_2ndTrkE_2ndtrkangle_TRUE_RECO->Fill(secTrkEnergy,secTrkTrueAngle,wgt_minerva_v1);

            if(Particle_type_Event==kSecondary_particle_vector[0]){
              h_2ndTrkE_2ndtrkangle_Proton_TRUE_RECO->Fill(secTrkEnergy,secTrkTrueAngle,wgt_minerva_v1);
            }

            else if(Particle_type_Event==kSecondary_particle_vector[3]||Particle_type_Event==kSecondary_particle_vector[4])
            {
              h_2ndTrkE_2ndtrkangle_Pion_TRUE_RECO->Fill(secTrkEnergy,secTrkTrueAngle,wgt_minerva_v1);
            }

          }//END OF CV

        }// END of Universe Groups
      }// END OF TRUTH + RECO CUTS
    }//END OF TRUTH PASS CUTS

    if(PassesCutsTRUTH(*Universe_GROUP.front(), kTRUTHCutsVector_2ndTrkAngle )){
      // TRUTH ONLY Cuts
      if(PassesCutsRECO(*Universe_GROUP.front(),  is_mc , kCutsVector_2ndtrkAngle_noFidiucal, kWeights_v1tune, CountMap_2ndTrkAngle_noFidiucal ) ){
        for (auto universe : Universe_GROUP){
          universe->SetEntry(ii);

          auto PDG_trklist = universe->GetVector_nonMuonTk_PDG_Parent();
          auto Energy_trklist = universe-> GetVector_nonMuonTk_Energy_GeV_Parent();
          auto Angle_trklist = universe->GetVector_nonMuonTk_Angle_wrtb_Degs_Parent();
          auto EnergyFraction_vector = universe->Get_TrueFractionE_vector();
          //int secondTrk = universe->Getindex2ndTrackhighestKE();


          int secondTrk = universe->Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_muonNotinlist(PDG_trklist, Energy_trklist, EnergyFraction_vector);
          if(secondTrk==-999)continue;

          double secTrkTrueAngle  = Angle_trklist.at(secondTrk);
          double secTrkTrueEnergy = Energy_trklist.at(secondTrk);
          double wgt_minerva_v1 = universe->GetWeight(kWeights_v1tune);
          int secTrk_PDG = PDG_trklist.at(secondTrk);
          Particle_type Particle_type_Event = GetParticlegroup_type(secTrk_PDG);

          if(isCV(*universe)){
            h_cryoVertex_Z_R_TRUE_RECO->Fill(universe->GetTRUE_Vertex_z(),universe->GetTRUE_Vertex_r(),wgt_minerva_v1);
            h_cryoVertex_Z_secTrkTheta_TRUE_RECO->Fill(universe->GetTRUE_Vertex_z(), secTrkTrueAngle,wgt_minerva_v1);
            h_cryoVertex_R_secTrkTheta_TRUE_RECO->Fill(universe->GetTRUE_Vertex_r(), secTrkTrueAngle,wgt_minerva_v1);
            h_cryoVertex_Z_Pathlength_TRUE_RECO->Fill(universe->GetTRUE_Vertex_z(), universe->GetTRUE_nonMuoncolumnarDensity(secondTrk), wgt_minerva_v1);
            h_cryoVertex_R_Pathlength_TRUE_RECO->Fill(universe->GetTRUE_Vertex_r(), universe->GetTRUE_nonMuoncolumnarDensity(secondTrk), wgt_minerva_v1);
            h_cryoVertex_Z_DOCA_TRUE_RECO->Fill(universe->GetTRUE_Vertex_z(), universe->GetTRUE_nonMuonDOCA(secondTrk), wgt_minerva_v1);
            h_cryoVertex_R_DOCA_TRUE_RECO->Fill(universe->GetTRUE_Vertex_r(), universe->GetTRUE_nonMuonDOCA(secondTrk), wgt_minerva_v1);
            h_cryoVertex_Z_2ndTrkE_TRUE_RECO->Fill(universe->GetTRUE_Vertex_z(), secTrkTrueEnergy, wgt_minerva_v1);
            h_cryoVertex_R_2ndTrkE_TRUE_RECO->Fill(universe->GetTRUE_Vertex_r(), secTrkTrueEnergy, wgt_minerva_v1);


          }//End CV
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


    h_MuonPZ_TRUE_RECO.SyncCVHistos();
    h_MuonPT_TRUE_RECO.SyncCVHistos();
    h_MuonE_TRUE_RECO.SyncCVHistos();
    h_MuonTheta_TRUE_RECO.SyncCVHistos();


    //h_secTrk_tracklength_TRUE_TRUE_RECO.SyncCVHistos();
//////////////////////////////////

    h_CryoVertex_X_TRUE_RECO.SyncCVHistos();
    h_CryoVertex_Y_TRUE_RECO.SyncCVHistos();
    h_CryoVertex_R_TRUE_RECO.SyncCVHistos();

    h_CryoVertex_RR_TRUE_RECO.SyncCVHistos();
    h_CryoVertex_Z_TRUE_RECO.SyncCVHistos();

    h_CryoVertex_recoX_TRUE_RECO.SyncCVHistos();
    h_CryoVertex_recoY_TRUE_RECO.SyncCVHistos();
    h_CryoVertex_recoR_TRUE_RECO.SyncCVHistos();
    h_CryoVertex_recoRR_TRUE_RECO.SyncCVHistos();

    h_CryoVertex_resolutionX_TRUE_RECO.SyncCVHistos();
    h_CryoVertex_resolutionY_TRUE_RECO.SyncCVHistos();
    h_CryoVertex_resolutionZ_TRUE_RECO.SyncCVHistos();
    h_CryoVertex_resolutionR_TRUE_RECO.SyncCVHistos();
    h_CryoVertex_resolutionRR_TRUE_RECO.SyncCVHistos();
    h_CryoVertex_Percent_resolutionX_TRUE_RECO.SyncCVHistos();
    h_CryoVertex_Percent_resolutionY_TRUE_RECO.SyncCVHistos();
    h_CryoVertex_Percent_resolutionZ_TRUE_RECO.SyncCVHistos();
    h_CryoVertex_Percent_resolutionR_TRUE_RECO.SyncCVHistos();
    h_CryoVertex_Percent_resolutionRR_TRUE_RECO.SyncCVHistos();

    h_CryoVertex_resolutionX_RECO.SyncCVHistos();
    h_CryoVertex_resolutionY_RECO.SyncCVHistos();
    h_CryoVertex_resolutionZ_RECO.SyncCVHistos();
    h_CryoVertex_resolutionR_RECO.SyncCVHistos();
    h_CryoVertex_resolutionRR_RECO.SyncCVHistos();
    h_CryoVertex_Percent_resolutionX_RECO.SyncCVHistos();
    h_CryoVertex_Percent_resolutionY_RECO.SyncCVHistos();
    h_CryoVertex_Percent_resolutionZ_RECO.SyncCVHistos();
    h_CryoVertex_Percent_resolutionR_RECO.SyncCVHistos();
    h_CryoVertex_Percent_resolutionRR_RECO.SyncCVHistos();




    h_CryoVertex_recoZ_TRUE_RECO.SyncCVHistos();

    h_secTrk_Theta_Dimuon_TRUE_RECO.SyncCVHistos();

    h_secTrk_Energy_TRUE_RECO.SyncCVHistos();
    h_secTrk_EnergyFINEBinning_TRUE_RECO.SyncCVHistos();
    h_secTrk_Theta_TRUE_RECO.SyncCVHistos();
    h_secTrk_Openangle_TRUE_RECO.SyncCVHistos();

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


    //h_secTrkTheta_cryoVertex_Z_TRUE_RECO.SyncCVHistos();
    //h_secTrkTheta_cryoVertex_R_TRUE_RECO.SyncCVHistos();

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

  //PrintCutstoScreen( kCutsVector , CountMap_RECO, c, mcscale );
  //PrintCutstoScreen( kCutsVector , CountMap_RECO_Helium, "Helium", mcscale );
  //PrintCutstoScreen( kCutsVector , CountMap_RECO_nonHelium, "nonHelium", mcscale );
  //RECOCutTableLatex(c,kCutsVector, CountMap_RECO, CountMap_RECO_Helium, CountMap_RECO_nonHelium );

  //TGraph  *RECO_Cuts = Make_RECOCut_Tgraph_fromCutMap("RECO_Cuts", CountMap_RECO);
  //TGraph  *RECO_Helium_Cuts = Make_RECOCut_Tgraph_fromCutMap("RECO_Helium_Cuts", CountMap_RECO_Helium);
  //TGraph  *RECO_nonHelium_Cuts = Make_RECOCut_Tgraph_fromCutMap("RECO_nonHelium_Cuts", CountMap_RECO);

  //MakeEfficiencyCutCVS(CountMap_RECO, CountMap_RECO_Eff , kCutsVector_Eff,c,mcPOT);
  //Make_cvsOfCutsRate( kCutsVector , CountMap_RECO, c, true, mcscale, mcPOT);
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~ RECO Eff cuts ~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;
  //Make_cvsOfCutsRateTRUE(kTRUTHCutsVector , CountMap_TRUTH, true_Cuts_char, mcscale, mcPOT);
  //Make_cvsOfCutsRate( kCutsVector_Eff, CountMap_RECO_Eff, reco_true_char, true, mcscale, mcPOT);
  //PrintCutstoScreen( kCutsVector_Eff , CountMap_RECO_Eff, c, mcscale );

  //outFileName = "Histograms_test.root";
  //auto outFile = TFile::Open(outFileName);
  if(Run_EventLoopOnGid==true){
    sprintf(outFileName, "%s_%s_%s_%s_Efficiency.root", "Histograms",c,d,ErrorStatus);
    std::cout << "Writing output file on Grid to: " <<outFileName << std::endl;

  }
  else{
    sprintf(outFileName, "%s/%s_%s_%s_%s_Efficiency.root", rootpathway, "Histograms",c,d,ErrorStatus);
    std::cout << "Writing output file to: " <<outFileName << std::endl;

  }


  TGraph *TGraph_Truth_Cut_Map_MuonEnergy   =  Make_TruthCut_Tgraph_fromCutMap("TGraph_Truth_Cut_Map_MuonEnergy",     Truth_Cut_Map_MuonEnergy);
  TGraph *TGraph_Truth_Cut_Map_MuonTheta    =  Make_TruthCut_Tgraph_fromCutMap("TGraph_Truth_Cut_Map_MuonTheta",    Truth_Cut_Map_MuonTheta);
  TGraph *TGraph_Truth_Cut_Map_Fiduical     =  Make_TruthCut_Tgraph_fromCutMap("TGraph_Truth_Cut_Map_Fiduical",         Truth_Cut_Map_Fiduical);
  TGraph *TGraph_Truth_Cut_Map_2ndTrkEnergy =  Make_TruthCut_Tgraph_fromCutMap("TGraph_Truth_Cut_Map_2ndTrkEnergy", Truth_Cut_Map_2ndTrkEnergy);
  TGraph *TGraph_Truth_Cut_Map_2ndTrkAngle  =  Make_TruthCut_Tgraph_fromCutMap("TGraph_Truth_Cut_Map_2ndTrkAngle",  Truth_Cut_Map_2ndTrkAngle);

  TGraph *TGraph_Reco_Cut_Map_MuonEnergy   =  Make_RECOCut_Tgraph_fromCutMap("TGraph_Reco_Cut_Map_MuonEnergy",       CountMap_MuonEnergy);
  TGraph *TGraph_Reco_Cut_Map_MuonTheta    =  Make_RECOCut_Tgraph_fromCutMap("TGraph_Reco_Cut_Map_MuonTheta",        CountMap_MuonTheta);
  TGraph *TGraph_Reco_Cut_Map_Fiduical     =  Make_RECOCut_Tgraph_fromCutMap("TGraph_Reco_Cut_Map_Fiduical",         CountMap_Fiduical);
  TGraph *TGraph_Reco_Cut_Map_2ndTrkEnergy =  Make_RECOCut_Tgraph_fromCutMap("TGraph_Reco_Cut_Map_2ndTrkEnergy",     CountMap_2ndTrkEnergy);
  TGraph *TGraph_Reco_Cut_Map_2ndTrkAngle  =  Make_RECOCut_Tgraph_fromCutMap("TGraph_Reco_Cut_Map_2ndTrkAngle",      CountMap_2ndTrkAngle);



  //TFile *outFile(outFileName, "RECREATE");
  TFile *outFile = new TFile(outFileName,"RECREATE");
  TChain POT_branch("Meta");
  POT_branch.Add(RootName.c_str());
  //TTree *oldtree = (TTree*)file->Get("Meta");
  TTree *clone = POT_branch.CloneTree();
  clone->Write();

  TGraph_Truth_Cut_Map_MuonEnergy->Write();
  TGraph_Truth_Cut_Map_MuonTheta->Write();
  TGraph_Truth_Cut_Map_Fiduical->Write();
  TGraph_Truth_Cut_Map_2ndTrkEnergy->Write();
  TGraph_Truth_Cut_Map_2ndTrkAngle->Write();

  TGraph_Reco_Cut_Map_MuonEnergy->Write();
  TGraph_Reco_Cut_Map_MuonTheta->Write();
  TGraph_Reco_Cut_Map_Fiduical->Write();
  TGraph_Reco_Cut_Map_2ndTrkEnergy->Write();
  TGraph_Reco_Cut_Map_2ndTrkAngle->Write();

  PlotUtils::MnvH1D* h_MuonE_FluxIntegrated = PlotUtils::flux_reweighter(playlist_fluxreweighter, nu_pdg, useNuEconstraint, NFlux_universe).GetIntegratedFluxReweighted(nu_pdg, h_MuonE_TRUE_RECO.hist, Min_NuFluxEnergy, Max_NuFluxEnergy, useMuonCorrelations);//GetRebinnedFluxReweighted (nu_pdg, h_MuonE.hist);
  h_MuonE_FluxIntegrated->Clone()->Write("h_MuonE_FluxIntegrated");
  h_MuonE_TRUE_RECO.hist->Write();


  PlotUtils::MnvH1D* h_MuonPZ_FluxIntegrated = PlotUtils::flux_reweighter(playlist_fluxreweighter, nu_pdg, useNuEconstraint, NFlux_universe).GetIntegratedFluxReweighted(nu_pdg, h_MuonPZ_TRUE_RECO.hist, Min_NuFluxEnergy, Max_NuFluxEnergy, useMuonCorrelations); //GetRebinnedFluxReweighted (nu_pdg, h_MuonPZ.hist);
  h_MuonPZ_FluxIntegrated->Clone()->Write("h_MuonPZ_FluxIntegrated");


  h_MuonPZ_TRUE_RECO.hist->Write();

  PlotUtils::MnvH1D* h_MuonPT_FluxIntegrated = PlotUtils::flux_reweighter(playlist_fluxreweighter, nu_pdg, useNuEconstraint, NFlux_universe).GetIntegratedFluxReweighted(nu_pdg,   h_MuonPZ_TRUE_RECO.hist, Min_NuFluxEnergy, Max_NuFluxEnergy, useMuonCorrelations);//GetRebinnedFluxReweighted(nu_pdg, h_MuonPT.hist);
  h_MuonPT_FluxIntegrated->Clone()->Write("h_MuonPT_FluxIntegrated");

  h_MuonPT_TRUE_RECO.hist->Write();

  PlotUtils::MnvH1D* h_MuonTheta_FluxIntegrated = PlotUtils::flux_reweighter(playlist_fluxreweighter, nu_pdg, useNuEconstraint, NFlux_universe).GetIntegratedFluxReweighted(nu_pdg, h_MuonTheta_TRUE_RECO.hist, Min_NuFluxEnergy, Max_NuFluxEnergy, useMuonCorrelations); //GetRebinnedFluxReweighted(nu_pdg, h_MuonTheta.hist);
  h_MuonTheta_FluxIntegrated->Clone()->Write("h_MuonTheta_FluxIntegrated");

  h_MuonTheta_TRUE_RECO.hist->Write();

  h_CryoVertex_X_TRUE_RECO.hist->Write();
  h_CryoVertex_Y_TRUE_RECO.hist->Write();
  h_CryoVertex_Z_TRUE_RECO.hist->Write();
  h_CryoVertex_R_TRUE_RECO.hist->Write();
  h_CryoVertex_RR_TRUE_RECO.hist->Write();

  h_CryoVertex_recoX_TRUE_RECO.hist->Write();
  h_CryoVertex_recoY_TRUE_RECO.hist->Write();
  h_CryoVertex_recoZ_TRUE_RECO.hist->Write();
  h_CryoVertex_recoR_TRUE_RECO.hist->Write();
  h_CryoVertex_recoRR_TRUE_RECO.hist->Write();

  h_CryoVertex_resolutionX_TRUE_RECO.hist->Write();
  h_CryoVertex_resolutionY_TRUE_RECO.hist->Write();
  h_CryoVertex_resolutionZ_TRUE_RECO.hist->Write();
  h_CryoVertex_resolutionR_TRUE_RECO.hist->Write();
  h_CryoVertex_resolutionRR_TRUE_RECO.hist->Write();
  h_CryoVertex_Percent_resolutionX_TRUE_RECO.hist->Write();
  h_CryoVertex_Percent_resolutionY_TRUE_RECO.hist->Write();
  h_CryoVertex_Percent_resolutionZ_TRUE_RECO.hist->Write();
  h_CryoVertex_Percent_resolutionR_TRUE_RECO.hist->Write();
  h_CryoVertex_Percent_resolutionRR_TRUE_RECO.hist->Write();

  h_CryoVertex_resolutionX_RECO.hist->Write();
  h_CryoVertex_resolutionY_RECO.hist->Write();
  h_CryoVertex_resolutionZ_RECO.hist->Write();
  h_CryoVertex_resolutionR_RECO.hist->Write();
  h_CryoVertex_resolutionRR_RECO.hist->Write();
  h_CryoVertex_Percent_resolutionX_RECO.hist->Write();
  h_CryoVertex_Percent_resolutionY_RECO.hist->Write();
  h_CryoVertex_Percent_resolutionZ_RECO.hist->Write();
  h_CryoVertex_Percent_resolutionR_RECO.hist->Write();
  h_CryoVertex_Percent_resolutionRR_RECO.hist->Write();


  h_secTrk_Energy_TRUE_RECO.hist->Write();
  h_secTrk_Pathlength_TRUE_RECO.hist->Write();
  h_secTrk_Pathlength_PROTON_TRUE_RECO.hist->Write();
  h_secTrk_Pathlength_PION_TRUE_RECO.hist->Write();

  h_CryoVertex_X_Material.WriteToFile(*outFile);
  h_CryoVertex_X_Interaction.WriteToFile(*outFile);
  h_CryoVertex_X_Particle.WriteToFile(*outFile);

  h_CryoVertex_Y_Material.WriteToFile(*outFile);
  h_CryoVertex_Y_Interaction.WriteToFile(*outFile);
  h_CryoVertex_Y_Particle.WriteToFile(*outFile);

  h_CryoVertex_Z_Material.WriteToFile(*outFile);
  h_CryoVertex_Z_Interaction.WriteToFile(*outFile);
  h_CryoVertex_Z_Particle.WriteToFile(*outFile);

  h_CryoVertex_R_Material.WriteToFile(*outFile);
  h_CryoVertex_R_Interaction.WriteToFile(*outFile);
  h_CryoVertex_R_Particle.WriteToFile(*outFile);

  h_secTrk_Energy_Material.WriteToFile(*outFile);
  h_secTrk_Energy_Interaction.WriteToFile(*outFile);
  h_secTrk_Energy_Particle.WriteToFile(*outFile);

  h_CryoVertex_resolutionX_RECO_Material.WriteToFile(*outFile);
  h_CryoVertex_resolutionX_RECO_Interaction.WriteToFile(*outFile);
  h_CryoVertex_resolutionX_RECO_Particle.WriteToFile(*outFile);
  h_CryoVertex_resolutionY_RECO_Material.WriteToFile(*outFile);
  h_CryoVertex_resolutionY_RECO_Interaction.WriteToFile(*outFile);
  h_CryoVertex_resolutionY_RECO_Particle.WriteToFile(*outFile);
  h_CryoVertex_resolutionR_RECO_Material.WriteToFile(*outFile);
  h_CryoVertex_resolutionR_RECO_Interaction.WriteToFile(*outFile);
  h_CryoVertex_resolutionR_RECO_Particle.WriteToFile(*outFile);
  h_CryoVertex_resolutionZ_RECO_Material.WriteToFile(*outFile);
  h_CryoVertex_resolutionZ_RECO_Interaction.WriteToFile(*outFile);
  h_CryoVertex_resolutionZ_RECO_Particle.WriteToFile(*outFile);


  h_CryoVertex_resolutionR_fidiucal_RECO_Material.WriteToFile(*outFile);
  h_CryoVertex_resolutionR_fidiucal_RECO_Interaction.WriteToFile(*outFile);
  h_CryoVertex_resolutionR_fidiucal_RECO_Particle.WriteToFile(*outFile);
  h_CryoVertex_resolutionZ_fidiucal_RECO_Material.WriteToFile(*outFile);
  h_CryoVertex_resolutionZ_fidiucal_RECO_Interaction.WriteToFile(*outFile);
  h_CryoVertex_resolutionZ_fidiucal_RECO_Particle.WriteToFile(*outFile);

  h_CryoVertex_resolutionR_fidiucal_Neg100_RECO_Material.WriteToFile(*outFile);
  h_CryoVertex_resolutionR_fidiucal_Neg100_RECO_Interaction.WriteToFile(*outFile);
  h_CryoVertex_resolutionR_fidiucal_Neg100_RECO_Particle.WriteToFile(*outFile);
  h_CryoVertex_resolutionZ_fidiucal_Neg100_RECO_Material.WriteToFile(*outFile);
  h_CryoVertex_resolutionZ_fidiucal_Neg100_RECO_Interaction.WriteToFile(*outFile);
  h_CryoVertex_resolutionZ_fidiucal_Neg100_RECO_Particle.WriteToFile(*outFile);

  h_CryoVertex_resolutionR_fidiucal_Neg50_RECO_Material.WriteToFile(*outFile);
  h_CryoVertex_resolutionR_fidiucal_Neg50_RECO_Interaction.WriteToFile(*outFile);
  h_CryoVertex_resolutionR_fidiucal_Neg50_RECO_Particle.WriteToFile(*outFile);
  h_CryoVertex_resolutionZ_fidiucal_Neg50_RECO_Material.WriteToFile(*outFile);
  h_CryoVertex_resolutionZ_fidiucal_Neg50_RECO_Interaction.WriteToFile(*outFile);
  h_CryoVertex_resolutionZ_fidiucal_Neg50_RECO_Particle.WriteToFile(*outFile);

  h_CryoVertex_resolutionR_fidiucal_50_RECO_Material.WriteToFile(*outFile);
  h_CryoVertex_resolutionR_fidiucal_50_RECO_Interaction.WriteToFile(*outFile);
  h_CryoVertex_resolutionR_fidiucal_50_RECO_Particle.WriteToFile(*outFile);
  h_CryoVertex_resolutionZ_fidiucal_50_RECO_Material.WriteToFile(*outFile);
  h_CryoVertex_resolutionZ_fidiucal_50_RECO_Interaction.WriteToFile(*outFile);
  h_CryoVertex_resolutionZ_fidiucal_50_RECO_Particle.WriteToFile(*outFile);

  h_CryoVertex_resolutionR_fidiucal_100_RECO_Material.WriteToFile(*outFile);
  h_CryoVertex_resolutionR_fidiucal_100_RECO_Interaction.WriteToFile(*outFile);
  h_CryoVertex_resolutionR_fidiucal_100_RECO_Particle.WriteToFile(*outFile);
  h_CryoVertex_resolutionZ_fidiucal_100_RECO_Material.WriteToFile(*outFile);
  h_CryoVertex_resolutionZ_fidiucal_100_RECO_Interaction.WriteToFile(*outFile);
  h_CryoVertex_resolutionZ_fidiucal_100_RECO_Particle.WriteToFile(*outFile);

  h_secTrk_EnergyFINEBinning_TRUE_RECO.hist->Write();

  h_secTrk_Theta_TRUE_RECO.hist->Write();

  h_secTrk_Openangle_TRUE_RECO.hist->Write();

  ////////////////////////////////////////////////
  // Veto Wall + Others
  ////////////////////////////////////////////////

////////////////////////////////////////////////

  h_secTrk_Energy_Dimuon_TRUE_RECO.hist->Write();
  h_secTrk_Theta_Dimuon_TRUE_RECO.hist->Write();
  h_secTrk_Energy_PROTON_TRUE_RECO.hist->Write();
  h_secTrk_Theta_PROTON_TRUE_RECO.hist->Write();
  h_secTrk_Openangle_PROTON_TRUE_RECO.hist->Write();
  h_secTrk_Energy_PION_TRUE_RECO.hist->Write();
  h_secTrk_Theta_PION_TRUE_RECO.hist->Write();
  h_secTrk_Openangle_PION_TRUE_RECO.hist->Write();


/////////////////
/////2D hists////
/////////////////
//h_secTrkTheta_cryoVertex_Z_TRUE_RECO.hist->Write();
//h_secTrkTheta_cryoVertex_R_TRUE_RECO.hist->Write();
h_resolutionR_FidiucalCut->Write();
h_resolutionZ_FidiucalCut->Write();

h_resolutionX_FidiucalCut->Write();
h_resolutionY_FidiucalCut->Write();

h_resolutionR_FidiucalCut_helium->Write();
h_resolutionZ_FidiucalCut_helium->Write();
h_resolutionR_FidiucalCut_nonhelium->Write();
h_resolutionZ_FidiucalCut_nonhelium->Write();


h_cryoVertex_Z_secTrkTheta_TRUE_RECO->Write();
h_cryoVertex_R_secTrkTheta_TRUE_RECO->Write();

h_cryoVertex_Z_Pathlength_TRUE_RECO->Write();
h_cryoVertex_R_Pathlength_TRUE_RECO->Write();
h_cryoVertex_Z_DOCA_TRUE_RECO->Write();
h_cryoVertex_R_DOCA_TRUE_RECO->Write();
h_cryoVertex_Z_2ndTrkE_TRUE_RECO->Write();
h_cryoVertex_R_2ndTrkE_TRUE_RECO->Write();

h_cryoVertex_Z_R_TRUE_RECO->Write();
h_muonPT_2ndTrkangle_TRUE_RECO->Write();
h_muonPZ_2ndTrkangle_TRUE_RECO->Write();
h_muontheta_2ndTrkangle_TRUE_RECO->Write();
h_2ndTrkE_2ndtrkangle_TRUE_RECO->Write();
h_2ndTrkE_2ndtrkangle_Proton_TRUE_RECO->Write();
h_2ndTrkE_2ndtrkangle_Pion_TRUE_RECO->Write();


  outFile->Close();


  char playlistname_char[playlist.length()+1];
  strcpy(playlistname_char,playlist.c_str());
  char arachneName[1024];

TCanvas *can = new TCanvas("", "");
MnvPlotter *mnv_plotter = new MnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
//MakeTrue_interactionPlots_WithRECOtrajector(All_True_trajectors,All_RECO_trajectors_Parent,playlistname_char , 5.0 ,"RecoStudy_recoilTracks", can,mnv_plotter);
/*
MakeLatex_particleTraj_True_RECO_plots(All_True_trajectors,
                                       All_RECO_trajectors_Parent,
                                       True_Reco_Energies_Parent,
                                       "RecoStudy_recoilTracks"  , "Latex_RecoStudy_recoilTracks", playlistname_char);
*/


char pdf_name[1024];
char pdf_start[1024];
char pdf_mid[1024];
char pdf_end[1024];

    sprintf(pdf_name, "Fidical_volumne_cuts_check_%s",c);

    sprintf(pdf_start,"%s.pdf(",pdf_name);
    //sprintf(pdf_mid,  "%s.pdf",pdf_name);
    sprintf(pdf_end,  "%s.pdf)",pdf_name);

    can -> Print(pdf_start);

  DrawVertex_Cryotank_X_Y_R_Vs_Z(FiducalCut_Neg200 , c, " Fiduical -200 ", pdf_name , can, mnv_plotter);
  DrawVertex_Cryotank_X_Y_R_Vs_Z(FiducalCut_Neg150 , c, " Fiduical -150 ", pdf_name , can, mnv_plotter);
  DrawVertex_Cryotank_X_Y_R_Vs_Z(FiducalCut_Neg100 , c, " Fiduical -100 ", pdf_name , can, mnv_plotter);
  DrawVertex_Cryotank_X_Y_R_Vs_Z(FiducalCut_Neg50 , c, " Fiduical -50 ", pdf_name , can, mnv_plotter);
  DrawVertex_Cryotank_X_Y_R_Vs_Z(FiducalCut , c, " Fiduical 0 ", pdf_name , can, mnv_plotter);
  DrawVertex_Cryotank_X_Y_R_Vs_Z(FiducalCut_50 , c, " Fiduical 50 ", pdf_name , can, mnv_plotter);
  DrawVertex_Cryotank_X_Y_R_Vs_Z(FiducalCut_100 , c, " Fiduical 100 ", pdf_name , can, mnv_plotter);





  can -> Print(pdf_end);

    std::cout << "END OF Plotting" << std::endl;

    std::cout << " THe Greatest  Chi sqrt value for Reco Cuts = "<< greatest_Chisqrt<< std::endl;
   //MakeLatex_Tables_withTrue_Event_info(N_A_secTrkParticle," ",  "N_A_FS_RECO", c, .5, "N_A in FS");
   std::cout << " this many Other long tracks  = "<< otherlongtrack<< std::endl;


std::cout<< "count_fid_neg_200 = " << count_fid_neg_200 << " count_fid_0 =   "<< count_fid_0 <<"count_fid_50  = " << count_fid_50 <<std::endl;


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


std::vector<ECuts> GetRECOCutsFor_2ndTrkEnergyVector() {
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
  ret_vec.push_back(kFiducialVolume);

  ret_vec.push_back(kVeto );
  ret_vec.push_back(kSix );
  ret_vec.push_back(kMatchVetoDeadPaddle);

  ret_vec.push_back(kTrackForwardGoing);
  //ret_vec.push_back(ksecTrkwrtblessthanMaxAngle);

  ret_vec.push_back(kAllCuts );
  return ret_vec;
//#endif
}

std::vector<ECuts> GetVectorRECOCutsEmu_Eff() {
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
  return ret_vec;
//#endif
}


std::vector<ECuts> GetVectorRECOCuts_MuonTheta_Eff() {
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
  //ret_vec.push_back(kMuonAngle );
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
  return ret_vec;
//#endif
}

std::vector<ECuts> GetVectorRECOCuts_MuonEnergy_Eff() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ECuts> ret_vec;
  ret_vec.push_back(kNoCuts  );
  //ret_vec.push_back(kGoodEnergy );
  ret_vec.push_back(kThetaMu );
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

std::vector<ECuts> GetRECOCutsFor2ndTrkAngleVector() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ECuts> ret_vec;
  ret_vec.push_back(kNoCuts  );
  ret_vec.push_back(kGoodEnergy );
  ret_vec.push_back(kThetaMu );
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
  //ret_vec.push_back(kMaxChiSqrt);
  ret_vec.push_back(kVertex_ConvergedfromAllTracks);
  ret_vec.push_back(kMaxChiSqrt_byTrackType);
  ret_vec.push_back(kAllCuts );

  //int n = sizeof(kCutsArray) / sizeof(kCutsArray[0]);
  //static std::vector<ECuts> ret_vec(kCutsArray, kCutsArray + n);
  return ret_vec;
//#endif
}

std::vector<ECuts> GetRECOCutsFor2ndTrkAngle_noFidiucalVector() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ECuts> ret_vec;
  ret_vec.push_back(kNoCuts  );
  ret_vec.push_back(kGoodEnergy );
  ret_vec.push_back(kThetaMu );
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
  //ret_vec.push_back(ksecTrkwrtblessthanMaxAngle);
  ret_vec.push_back(kVertexConverge);
  //ret_vec.push_back(kFiducialVolume );
  ret_vec.push_back(kTrackForwardGoing );
  //ret_vec.push_back(kMaxChiSqrt);
  ret_vec.push_back(kVertex_ConvergedfromAllTracks);
  ret_vec.push_back(kMaxChiSqrt_byTrackType);
  ret_vec.push_back(kAllCuts );

  //int n = sizeof(kCutsArray) / sizeof(kCutsArray[0]);
  //static std::vector<ECuts> ret_vec(kCutsArray, kCutsArray + n);
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
  //ret_vec.push_back(kFiducialVolume);

  ret_vec.push_back(kVeto );
  ret_vec.push_back(kSix );
  ret_vec.push_back(kMatchVetoDeadPaddle);

  ret_vec.push_back(kTrackForwardGoing);
  ret_vec.push_back(ksecTrkwrtblessthanMaxAngle);

  ret_vec.push_back(kAllCuts );
  return ret_vec;
//#endif
}



std::vector<ECutsTRUTH> GetTRUTH_ThetaMuCutsVector() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ECutsTRUTH> True_vec;
  True_vec.push_back(kTRUTHNoCuts   );
  True_vec.push_back(kTRUTHMuonEnergy );
  //True_vec.push_back(kTRUTHMuonAngle );
  True_vec.push_back(kTRUTHneutrino);
  True_vec.push_back(kTRUTHCCInteraction );
  True_vec.push_back(kTRUTHtarget);
  True_vec.push_back(kTRUTH_greaterthanoneFS);
  //True_vec.push_back(kTRUTHFiduical );
  True_vec.push_back(kTRUTH_NoNeutral_FS_2ndTrk_RECOBRANCH);
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);
  True_vec.push_back(kAllTRUTHCuts);

  return True_vec;
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
  True_vec.push_back(kTRUTH_NoNeutral_FS_2ndTrk_RECOBRANCH);
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);
  True_vec.push_back(kAllTRUTHCuts);

  return True_vec;
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
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);
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
  //True_vec.push_back(kTRUTHMuonEnergy );
  True_vec.push_back(kTRUTHMuonAngle );
  True_vec.push_back(kTRUTHneutrino);
  True_vec.push_back(kTRUTHCCInteraction );
  True_vec.push_back(kTRUTHtarget);
  True_vec.push_back(kTRUTH_greaterthanoneFS);
  //True_vec.push_back(kTRUTHFiduical);
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


std::vector<ECutsTRUTH> GetTRUTHCutsVector_2ndtrkAngle() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ECutsTRUTH> True_vec;
  True_vec.push_back(kTRUTHNoCuts   );
  True_vec.push_back(kTRUTHMuonEnergy );
  True_vec.push_back(kTRUTHMuonAngle );
  True_vec.push_back(kTRUTHneutrino);
  True_vec.push_back(kTRUTHCCInteraction );
  True_vec.push_back(kTRUTHtarget);
  True_vec.push_back(kTRUTH_greaterthanoneFS);
  //True_vec.push_back(kTRUTHFiduical);
  True_vec.push_back(kTRUTH_NoNeutral_FS_2ndTrk_noAngleCut_RECOBRANCH);
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

std::vector<ECutsTRUTH> GetTRUTHCutsVector_2ndtrkEnergy() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ECutsTRUTH> True_vec;
  True_vec.push_back(kTRUTHNoCuts   );
  True_vec.push_back(kTRUTHMuonEnergy );
  True_vec.push_back(kTRUTHMuonAngle );
  True_vec.push_back(kTRUTHneutrino);
  True_vec.push_back(kTRUTHCCInteraction );
  True_vec.push_back(kTRUTHtarget);
  True_vec.push_back(kTRUTH_greaterthanoneFS);
  //True_vec.push_back(kTRUTHFiduical);
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
