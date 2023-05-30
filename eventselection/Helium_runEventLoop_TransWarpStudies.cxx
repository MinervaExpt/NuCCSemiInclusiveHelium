//File: HeliumUtils.h
//Brief: Common functions that deal with the ME 1D Helium Analysis framework
//Author: Christian Nguyen christian2nguyen@ufl.edu

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
std::vector<ECutsTRUTH> GetTRUTHCutsVector_noMuonPhaseSpace();
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
const bool m_RunCodeWithSystematics = false;
const bool RunwithConvolution = false;
const bool RunwithShift = false;
const bool RunwithFid = true;
const bool useweights = false;



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
  PlotUtils::NamedCategory<Interaction_type>({kElastic},          "QE")
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
ParticleGroup_reduced_categories = {
  PlotUtils::NamedCategory<Particle_type>({kParticle_N_A},          "N_A"),
  PlotUtils::NamedCategory<Particle_type>({kParticle_OTHER},        "Other"),
  PlotUtils::NamedCategory<Particle_type>({kParticle_neutral},      "Neutral"),
  PlotUtils::NamedCategory<Particle_type>({kMuon},                   "Muon"),
  PlotUtils::NamedCategory<Particle_type>({kPion_0_Electron_kGamma},"Pion_0_Electron_Gamma"),
  PlotUtils::NamedCategory<Particle_type>({kPion_pos_neg},          "#pi^{}"),
  PlotUtils::NamedCategory<Particle_type>({kProton},                "Proton")


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

//typedef std::map< std::string, std::vector<HeliumCVUniverse*> > UniverseMap;

UniverseMap GetErrorBands(PlotUtils::ChainWrapper* chain , ME_helium_Status CryoTankStatus ) {

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

    UniverseMap VertexSmearing_systematics = GetHELIUMVertex_XYZ_SmearingShiftSystematicsMap<HeliumCVUniverse>(chain,CryoTankStatus);
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
const std::vector<ECutsTRUTH> kTRUTHCutsVector = GetTRUTHCutsVector();//GetTRUTHCutsVector();
const std::vector<ECutsTRUTH> kTRUTHCutsVector_NoPhase =  GetTRUTHCutsVector_noMuonPhaseSpace();


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

 TDatabasePDG *pdg_DATABASEobject = TDatabasePDG::Instance();

 MinervaUniverse::SetTruth(false);
  MinervaUniverse::SetDeuteriumGeniePiTune(false);
  MinervaUniverse::SetNuEConstraint(true);
  MinervaUniverse::SetZExpansionFaReweight(false);
  MinervaUniverse::SetAnalysisNuPDG(14);
  MinervaUniverse::SetNonResPiReweight(false); // not off for MK
  MinervaUniverse::SetNFluxUniverses(n_flux_universes);
  std::string playlist = GetPlaylist(PlayList_iterator);
  ME_helium_Status CryoTankStatus =  GetPlaylist_HeliumStatus(PlayList_iterator);
  MinervaUniverse::SetPlaylist(playlist);

  double ShiftX_major = return_shiftX(); //5.0;//-44.0; // [mm]
  double ShiftY_major = return_shiftY(); //50.0; // 41 [mm]
  double ShiftZ_major = return_shiftZ();

  if(RunwithShift==false){
   ShiftX_major= 0.0;
   ShiftY_major= 0.0;
   ShiftZ_major= 0.0;
  }


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
UniverseMap error_bands = GetErrorBands(chw_MC, CryoTankStatus);


for(auto band :error_bands ){std::cout<<"Checking Universe this is universe with name : " << band.first<<std::endl;}
std::vector<std::vector<HeliumCVUniverse*>> Error_Band_Universe_GROUPS = groupCompatibleUniverses(error_bands);

error_name_Map error_name;
error_name_Univ_MvnHistMap MnvReponse_Hist_N_Map;
//std::map<const std::string,  int> error_Number;
for(auto band :error_bands ){std::cout<<"Checking Universe this is universe with name : " << band.first<<std::endl;}
//std::vector<std::vector<HeliumCVUniverse*>> Error_Band_Universe_GROUPS = groupCompatibleUniverses(error_bands); // Group Vertical and Laterial bands together


std::map<std::string, std::vector<HeliumCVUniverse*> >::iterator itr;
for(itr = error_bands.begin(); itr != error_bands.end(); ++itr) error_name.insert(std::pair<std::string, const int>((itr->second)[0]->ShortName(), (itr->second).size()));
int count = 0;
int unv_count = 0;
Fill_MnvReponse_ErrorUniv_Hist_numbers(MnvReponse_Hist_N_Map, error_name);


std::cout<<"checking Error Names "<< std::endl;
std::cout<<"MnvReponse_Hist_N_Map.size() = "<<MnvReponse_Hist_N_Map.size()<< std::endl;
for(auto cat : error_bands ){
std::cout<<"Universe Name = " <<cat.first << std::endl;
}


double mcPOT = GetPOT_local(mcchainPOT, "MC");
std::cout<<"Number of Universes set is = "<< 	MinervaUniverse::GetNFluxUniverses()<<std::endl;
std::cout << "POT of this Playlist = "<< mcPOT <<std::endl;


static weightMK *weight_MK;
char *mparalocation = std::getenv("MPARAMFILESROOT");
string dir_data = string(mparalocation)+"/data/Reweight/";
weight_MK = new weightMK(dir_data + "output_ratio_genie_neut_for_MKmodel.root");

//MinervaUniverse::SetNFluxUniverses(25);
POTCounter pot_counter;

const std::string RootName = GetPlaylist_ROOT_path(PlayList_iterator, is_mc );

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
std::cout<<"~~~~ Finished 1 set  ~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<std::endl;

PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE("h_MuonE", "Muon_{E} NEW Method", Ebin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE_BG("h_MuonE_BG", "Muon_{E} NEW Method", Ebin_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE_Fake("h_MuonE_Fake", "Muon_{E} NEW Method", Ebin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE_Fake2("h_MuonE_Fake2", "Muon_{E} NEW Method", Ebin_vector , error_bands);
MnvH1D *h_MuonE_MKmodel    =    new MnvH1D("h_MuonE_MKmodel", "h_MuonE_MKmodel", Ebin_vector.size()-1, Ebin_vector.data() );
MnvH1D *h_MuonE_v2tune    =    new MnvH1D("h_MuonE_v2tune", "h_MuonE_v2tune", Ebin_vector.size()-1, Ebin_vector.data() );


PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE_TRUE_RECO("h_MuonE_TRUE_RECO", "Muon_{E} NEW Method", Ebin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPZ("h_MuonPZ", "Muon_{PZ} NEW Method",  Pzbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPZ_BG("h_MuonPZ_BG", "Muon_{PZ} NEW Method",  Pzbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPZ_Fake("h_MuonPZ_Fake", "Muon_{PZ} NEW Method",  Pzbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPZ_Fake2("h_MuonPZ_Fake2", "Muon_{PZ} NEW Method",  Pzbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPZ_TRUE_RECO("h_MuonPZ_TRUE_RECO", "Muon_{PZ} NEW Method",  Pzbin_vector , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonPZ_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonPZ_Material", Pzbin_vector ,"h_MuonPZ_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonPZ_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonPZ_Interaction", Pzbin_vector ,"h_MuonPZ_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_MuonPZ_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_reduced_categories, "h_MuonPZ_Particle", Pzbin_vector ,"h_MuonPZ_Particle; [GeV];Events");
//h_MuonPZ_Particle.ApplyColorPalette(Helium9_colorScheme);


PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPT("h_MuonPT", "Muon_{PT} NEW Method",  PTbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPT_BG("h_MuonPT_BG", "Muon_{PT} NEW Method",  PTbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPT_Fake("h_MuonPT_Fake", "Muon_{PT} NEW Method",  PTbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPT_Fake2("h_MuonPT_Fake2", "Muon_{PT} NEW Method",  PTbin_vector , error_bands);


PlotUtils::HistWrapper<HeliumCVUniverse> h_Muon_pseudorapidity("h_Muon_pseudorapidity", "h_Muon_pseudorapidity", pseudorapidity_muon_vector  , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Muon_pseudorapidity_angle("h_Muon_pseudorapidity_angle", "h_Muon_pseudorapidity_angle", MuonThetabin_vector  , error_bands);


PlotUtils::HistWrapper<HeliumCVUniverse> h_Muon_rapidity("h_Muon_rapidity", "h_Muon_rapidity", rapidity_muon_vector  , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPT_TRUE_RECO("h_MuonPT_TRUE_RECO", "Muon_{PT} NEW Method",  PTbin_vector , error_bands);

//h_MuonCurvatureSig_Particle.ApplyColorPalette(Helium9_colorScheme);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonTheta("h_MuonTheta", "MuonTheta [Deg]",  MuonThetabin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonTheta_BG("h_MuonTheta_BG", "MuonTheta [Deg]",  MuonThetabin_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonTheta_Fake("h_MuonTheta_Fake", "MuonTheta [Deg]",  MuonThetabin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonTheta_Fake2("h_MuonTheta_Fake2", "MuonTheta [Deg]",  MuonThetabin_vector , error_bands);



PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonTheta_TRUE_RECO("h_MuonTheta_TRUE_RECO", "MuonTheta [Deg]",  MuonThetabin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPhi("h_MuonPhi", "Muon Phi [Deg]",  AnglePhi_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPhi_TRUE_RECO("h_MuonPhi_TRUE_RECO", "Muon Phi [Deg]",  AnglePhi_vector , error_bands);


///////////////////////////////////////
// low angle study
///////////////////////////////////////


std::vector<double> bigAngle_bins{0.0, 15.0, 30.0, 45.0, 60.0};
MnvH2D *h_2d_2ndtrkLength_Angle    =    new MnvH2D("h_2d_2ndtrkLength_Angle", "h_2d_2ndtrkLength_Angle", Recoil_track_length_vector.size()-1, Recoil_track_length_vector.data(), bigAngle_bins.size()-1, bigAngle_bins.data());

std::vector<double> bigAngle_bins_finner{0.0, 5.0, 10.0, 15.0, 20.0, 25.0, 30.0, 45.0, 60.0};
MnvH2D *h_2d_2ndtrkLength_finerAngle    =    new MnvH2D("h_2d_2ndtrkLength_finerAngle", "h_2d_2ndtrkLength_finerAngle", Recoil_track_length_vector.size()-1, Recoil_track_length_vector.data(), bigAngle_bins_finner.size()-1, bigAngle_bins_finner.data());



/////////////////////////////////////
//
/////////////////////////////////////
MnvH2D *h_2d_2ndtrkangle_2ndTrkE_TRUE_RECO    =    new MnvH2D("h_2d_2ndtrkangle_2ndTrkE_TRUE_RECO", "h_2d_2ndtrkangle_2ndTrkE_TRUE_RECO", secTrk_Theta_TRUEbin_vector.size()-1, secTrk_Theta_TRUEbin_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );

//MnvH2D *h_2d_2ndtrkangle_2ndTrkE_Proton_TRUE_RECO    =    new MnvH2D("h_2d_2ndtrkangle_2ndTrkE_Proton_TRUE_RECO", "h_2d_2ndtrkangle_2ndTrkE_Proton_TRUE_RECO", secTrk_Theta_TRUEbin_vector.size()-1, secTrk_Theta_TRUEbin_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );

//MnvH2D *h_2d_2ndtrkangle_2ndTrkE_Pion_TRUE_RECO    =    new MnvH2D("h_2d_2ndtrkangle_2ndTrkE_Pion_TRUE_RECO", "h_2d_2ndtrkangle_2ndTrkE_Pion_TRUE_RECO", secTrk_Theta_TRUEbin_vector.size()-1, secTrk_Theta_TRUEbin_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );

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

MnvH2D *h_Mig_Vertex_X_RECO      =   new MnvH2D("h_Mig_Vertex_X_RECO",     "h_Mig_Vertex_X_RECO",  Vertex_Xbin_vector.size()-1, Vertex_Xbin_vector.data(), Vertex_Xbin_vector.size()-1, Vertex_Xbin_vector.data());
MnvH2D *h_Mig_Vertex_Y_RECO      =   new MnvH2D("h_Mig_Vertex_Y_RECO",     "h_Mig_Vertex_Y_RECO",  Vertex_Ybin_vector.size()-1, Vertex_Ybin_vector.data(), Vertex_Ybin_vector.size()-1, Vertex_Ybin_vector.data());
MnvH2D *h_Mig_Vertex_R_RECO      =   new MnvH2D("h_Mig_Vertex_R_RECO",     "h_Mig_Vertex_R_RECO",  Vertex_Rbin_vector.size()-1, Vertex_Rbin_vector.data(), Vertex_Rbin_vector.size()-1, Vertex_Rbin_vector.data());
MnvH2D *h_Mig_Vertex_Z_RECO      =   new MnvH2D("h_Mig_Vertex_Z_RECO",     "h_Mig_Vertex_Z_RECO",  Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data(), Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());



auto fraction = MakeBinVector(20, 0, 1);

////////////////
//Vertex Hist///
////////////////

MinervaUnfold::MnvResponse *MnvR_Muon_PT = new MinervaUnfold::MnvResponse( "MnvR_Muon_PT",  "MnvR_Muon_PT",   PTbin_vector);
MinervaUnfold::MnvResponse *MnvR_Muon_PZ = new MinervaUnfold::MnvResponse( "MnvR_Muon_PZ",  "MnvR_Muon_PZ",   Pzbin_vector);
MinervaUnfold::MnvResponse *MnvR_Muon_theta = new MinervaUnfold::MnvResponse( "MnvR_Muon_theta",  "MnvR_Muon_theta",   MuonThetabin_vector);
MinervaUnfold::MnvResponse *MnvR_Muon_E = new MinervaUnfold::MnvResponse( "MnvR_Muon_E",  "MnvR_Muon_E",   Ebin_vector);

MinervaUnfold::MnvResponse *MnvR_Muon_PT_plus10percent = new MinervaUnfold::MnvResponse( "MnvR_Muon_PT_plus10percent",  "MnvR_Muon_PT_plus10percent",   PTbin_vector);
MinervaUnfold::MnvResponse *MnvR_Muon_PZ_plus10percent = new MinervaUnfold::MnvResponse( "MnvR_Muon_PZ_plus10percent",  "MnvR_Muon_PZ_plus10percent",   Pzbin_vector);
MinervaUnfold::MnvResponse *MnvR_Muon_theta_plus10percent = new MinervaUnfold::MnvResponse( "MnvR_Muon_theta_plus10percent",  "MnvR_Muon_theta_plus10percent",   MuonThetabin_vector);
MinervaUnfold::MnvResponse *MnvR_Muon_E_plus10percent = new MinervaUnfold::MnvResponse( "MnvR_Muon_E_plus10percent",  "MnvR_Muon_E_plus10percent",   Ebin_vector);


MinervaUnfold::MnvResponse *MnvR_Muon_PT_minus10percent = new MinervaUnfold::MnvResponse( "MnvR_Muon_PT_minus10percent",  "MnvR_Muon_PT_minus10percent",   PTbin_vector);
MinervaUnfold::MnvResponse *MnvR_Muon_PZ_minus10percent = new MinervaUnfold::MnvResponse( "MnvR_Muon_PZ_minus10percent",  "MnvR_Muon_PZ_minus10percent",   Pzbin_vector);
MinervaUnfold::MnvResponse *MnvR_Muon_theta_minus10percent = new MinervaUnfold::MnvResponse( "MnvR_Muon_theta_minus10percent",  "MnvR_Muon_theta_minus10percent",   MuonThetabin_vector);
MinervaUnfold::MnvResponse *MnvR_Muon_E_minus10percent = new MinervaUnfold::MnvResponse( "MnvR_Muon_E_minus10percent",  "MnvR_Muon_E_minus10percent",   Ebin_vector);

MinervaUnfold::MnvResponse *MnvR_Muon_PT_WarpFunction = new MinervaUnfold::MnvResponse( "MnvR_Muon_PT_WarpFunction",  "MnvR_Muon_PT_WarpFunction",   PTbin_vector);
MinervaUnfold::MnvResponse *MnvR_Muon_PZ_WarpFunction = new MinervaUnfold::MnvResponse( "MnvR_Muon_PZ_WarpFunction",  "MnvR_Muon_PZ_WarpFunction",   Pzbin_vector);
MinervaUnfold::MnvResponse *MnvR_Muon_theta_WarpFunction = new MinervaUnfold::MnvResponse( "MnvR_Muon_theta_WarpFunction",  "MnvR_Muon_theta_WarpFunction",   MuonThetabin_vector);
MinervaUnfold::MnvResponse *MnvR_Muon_E_WarpFunction = new MinervaUnfold::MnvResponse( "MnvR_Muon_E_WarpFunction",  "MnvR_Muon_E_WarpFunction",   Ebin_vector);


std::vector<MinervaUnfold::MnvResponse*>  MnvR_vector = {MnvR_Muon_PT, MnvR_Muon_PZ, MnvR_Muon_theta, MnvR_Muon_E,
  MnvR_Muon_PT_plus10percent,
  MnvR_Muon_PZ_plus10percent,
  MnvR_Muon_theta_plus10percent,
  MnvR_Muon_E_plus10percent,
  MnvR_Muon_PT_minus10percent,
  MnvR_Muon_PZ_minus10percent,
  MnvR_Muon_theta_minus10percent,
  MnvR_Muon_E_minus10percent,
  MnvR_Muon_PT_WarpFunction,
  MnvR_Muon_PZ_WarpFunction,
  MnvR_Muon_theta_WarpFunction,
  MnvR_Muon_E_WarpFunction

};// , MnvR_cryoVertex_Z_R



//std::map<const std::string,  int> error_Number;
for(auto band :error_bands ){std::cout<<"Checking Universe this is universe with name : " << band.first<<std::endl;}


//PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_Particle_N_A_secTrk_Theta_TRUE_RECO_Interaction =
//PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_Particle_N_A_secTrk_Theta_TRUE_RECO_Interaction", secTrk_Theta_TRUEbin_vector ,"h_Particle_N_A_secTrk_Theta_TRUE_RECO_Interaction; [Degs];Events");
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


FillingRecoCountingMapAdd(CountMap_RECO , kFiducialVolume_new );
FillingRecoCountingMapAdd(CountMap_RECO_Helium ,kFiducialVolume_new );
FillingRecoCountingMapAdd(CountMap_RECO_nonHelium ,kFiducialVolume_new );
FillingRecoCountingMapAdd(CountMap_TRUE_RECO ,kFiducialVolume_new );

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

  std::cout<<"Running Over this Playlist = "<< playlist.c_str()<<std::endl;


  double Pi = 3.14159265358979323846;
  for(int ii=0; ii<chw_MC->GetEntries(); ++ii){

    if(ii%1000==0) std::cout << (ii/100) << " k " << std::flush;

    //=========================================
    // For every systematic, loop over the universes, and fill the
    // appropriate histogram in the MnvH1D
    //=========================================

    for (auto band : error_bands){
      std::vector<HeliumCVUniverse*> error_band_universes = band.second;
      unv_count = 0;

      for (auto universe : error_band_universes){

        universe->SetEntry(ii);

        ///////////////////////////////////////////
        ////
        ////  Varibles that go into all universes
        ////
        ////
        ///////////////////////////////////////////

        /*
        double ShiftX  = ShiftX_major;
        double ShiftY =  ShiftY_major;
        double ShiftZ =  ShiftZ_major;

        if(Material_type_Event!=kAluminium && Material_type_Event!=kHelium ){
        ShiftX=0;
        ShiftY=0;
        ShiftZ=0;}
        */
        double Smearing_X = vertexX_Convolution(generator);
        double Smearing_Y = vertexY_Convolution(generator);
        double Smearing_Z = vertexZ_Convolution(generator);

        if(RunwithConvolution == false){
          Smearing_X = 0.0;
          Smearing_Y = 0.0;
          Smearing_Z = 0.0;
        }

        double x = universe->GetVertex_x()  + Smearing_X;
        double y = universe->GetVertex_y()  + Smearing_Y;
        double z = universe->GetVertex_z()  + Smearing_Z;
        double r =  sqrt(x*x + y*y);

        if(PassesCutsRECO(*universe,  is_mc , kCutsVector,kWeights_v1tune, CountMap_RECO, CountMap_RECO_Helium, CountMap_RECO_nonHelium,r,z) ){

          double wgt_minerva_v1 = universe->GetWeight(kWeights_v1tune);
          Material_type Material_type_Event = universe->Get_MaterialStackType();

          double x_true= universe->GetTRUE_Vertex_x();
          double y_true= universe->GetTRUE_Vertex_y();
          double z_true= universe->GetTRUE_Vertex_z();


          double r_true =  sqrt(x_true*x_true + y_true*y_true);

          //if(RunwithFid==true){
          //if(IsInFiducalVolumeFromtheInnerEdge( r, z, 50.0  )==false) continue;
          //}

          CryoTank_REGIONS CryoTankRegion_type = FourRegion_of_CryoTank(z_true);

          double Al_wgt = 1.0;
          if(useweights==true){Al_wgt *= return_AlWgt(CryoTankRegion_type, Material_type_Event);}
          wgt_minerva_v1*=Al_wgt;


          double Theta = universe->GetThetamu();
          double Pmu = universe ->GetPmu()/1000;
          double phi = universe -> GetPhimu();
          double Emu = universe->GetEmu()*.001;

          double px = Pmu * std::sin(Theta) * std::cos(phi);
          double py = Pmu * std::sin(Theta) * std::sin(phi);

          double PT = sqrt(px*px + py*py);
          double PZ = Pmu*std::cos(Theta);


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
            Interaction_type Interaction_type_Event =  universe->Get_Interaction_withDISbreakdown();//->Get_InteractionStackType();

            TrackType Track_type_Event = universe->GetTrackType();
            int secTrk_PDG = PDG_trklist.at(secondTrk);

            int secTrk_PDG_nonpartent = PDG_trklist_nonparent.at(secondTrk);

            Particle_type Particle_type_Event_nonparent =  GetParticlegroup_typeReduced(secTrk_PDG_nonpartent);
            Particle_type Particle_type_Event =  GetParticlegroup_typeReduced(secTrk_PDG);

            ///////////////////////////////////////////
            ////
            ////  Apply RECO CUTS to CV
            ////
            ///////////////////////////////////////////


              double weight_forMK = universe->GetWeight(kWeights_forMK);
              double MK_Weight = universe->GetMKmodelWeight_local(weight_MK);

              h_MuonE_v2tune->Fill(universe->GetMuonE_ECT(),universe->GetWeight(kWeights_v2tune));
              h_MuonE_MKmodel->Fill(universe->GetMuonE_ECT(),weight_forMK*weight_forMK);

              VertexOptions VertexOption_type = universe->GetVertex_optionType();
              boolNTrack boolNTrack_Type = universe->GetVertex_boolNTrack();


              double Reco_distance = RECO_Distance_to_innerTank(*universe);

              double chisqt = universe->GetVertexChiSqrFit();

              h_Mig_Vertex_X_RECO->Fill(x,x_true,wgt_minerva_v1);
              h_Mig_Vertex_Y_RECO->Fill(y,y_true,wgt_minerva_v1);
              h_Mig_Vertex_R_RECO->Fill(r,r_true,wgt_minerva_v1);
              h_Mig_Vertex_Z_RECO->Fill(z,z_true,wgt_minerva_v1);




              auto trackType = universe->GetTrackType();


            }//END of RECO CUTs for CV

            ///////////////////////////////////////////
            ////
            ////  END OF CV
            ////
            ///////////////////////////////////////////

            double weight_forMK = 1.0; //universe->GetWeight(kWeights_forMK);
            double MK_Weight = universe->GetMKmodelWeight_local(weight_MK);

            h_MuonE.univHist(universe)->Fill(Emu,wgt_minerva_v1);
            h_MuonPZ.univHist(universe)->Fill(PZ,wgt_minerva_v1);
            h_MuonPT.univHist(universe)->Fill(PT,wgt_minerva_v1);
            h_MuonTheta.univHist(universe)->Fill(Theta*TMath::RadToDeg(),wgt_minerva_v1);
            if(Material_type_Event != kHelium){
              h_MuonE_BG.univHist(universe)->Fill(Emu,wgt_minerva_v1);
              h_MuonPZ_BG.univHist(universe)->Fill(PZ,wgt_minerva_v1);
              h_MuonPT_BG.univHist(universe)->Fill(PT,wgt_minerva_v1);
              h_MuonTheta_BG.univHist(universe)->Fill(Theta*TMath::RadToDeg(),wgt_minerva_v1);
            }



            h_MuonE_Fake.univHist(universe)->Fill(universe->GetMuonE_ECT(),universe->GetWeight(kWeights_v2tune));

            h_MuonPZ_Fake.univHist(universe)->Fill(universe->GetMuonPz_ECT(),universe->GetWeight(kWeights_v2tune));

            h_MuonPT_Fake.univHist(universe)->Fill(universe->GetMuonPt_ECT(),universe->GetWeight(kWeights_v2tune));

            h_MuonTheta_Fake.univHist(universe)->Fill(universe->GetmuAngleWRTB_Degs(),MK_Weight * universe->GetWeight(kWeights_v2tune));

            h_MuonE_Fake2.univHist(universe)->Fill(universe->GetMuonE_ECT(),MK_Weight*weight_forMK);

            h_MuonPZ_Fake2.univHist(universe)->Fill(universe->GetMuonPz_ECT(),MK_Weight*weight_forMK);

            h_MuonPT_Fake2.univHist(universe)->Fill(universe->GetMuonPt_ECT(),MK_Weight*weight_forMK);

            h_MuonTheta_Fake2.univHist(universe)->Fill(universe->GetmuAngleWRTB_Degs(),MK_Weight*weight_forMK);

          auto tracktype = universe->GetTrackType();


        } // END of RECO Cuts

        ///////////////////////////////////////////
        ////
        ////  Apply TRUTH + RECO CUTS to each universe
        ////
        ///////////////////////////////////////////

        if(PassesCutsTRUTH(*universe, kTRUTHCutsVector, kWeights_v1tune , Truth_Cut_Map)){


          //std::cout<<"universe->ShortName() = " << universe->ShortName()<<std::endl;
          // Tell the Event which entry in the TChain it's looking at
          /*
          double ShiftX  = ShiftX_major;
          double ShiftY =  ShiftY_major;
          double ShiftZ =  ShiftZ_major;

          if(Material_type_Event!=kAluminium && Material_type_Event!=kHelium ){
          ShiftX=0;
          ShiftY=0;
          ShiftZ=0;}
          */

          double Smearing_X = vertexX_Convolution(generator);
          double Smearing_Y = vertexY_Convolution(generator);
          double Smearing_Z = vertexZ_Convolution(generator);

          if(RunwithConvolution == false){
            Smearing_X = 0.0;
            Smearing_Y = 0.0;
            Smearing_Z = 0.0;
          }

          double x = universe->GetVertex_x() + Smearing_X;
          double y = universe->GetVertex_y() + Smearing_Y;
          double z = universe->GetVertex_z() + Smearing_Z;
          double r =  sqrt(x*x + y*y);

          if(PassesCutsRECO(*universe,  is_mc , kCutsVector_Eff ,kWeights_v1tune ,CountMap_TRUE_RECO,r,z) ){

            auto PDG_trklist = universe->GetVector_nonMuonTk_PDG_Parent();
            auto Energy_trklist = universe-> GetVector_nonMuonTk_Energy_GeV_Parent();
            auto Angle_trklist = universe->GetVector_nonMuonTk_Angle_wrtb_Degs_Parent();
            auto EnergyFraction_vector = universe->Get_TrueFractionE_vector();
            //int secondTrk = universe->Getindex2ndTrackhighestKE();

            int secondTrk = universe->Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_lessthanAngle_muonNotinlist(PDG_trklist, Energy_trklist, Angle_trklist, EnergyFraction_vector);
            if(secondTrk==-999)continue;


            Material_type Material_type_Event = universe->Get_MaterialStackType();


            double x_true= universe->GetTRUE_Vertex_x();
            double y_true= universe->GetTRUE_Vertex_y();
            double z_true= universe->GetTRUE_Vertex_z();
            double r_true =  sqrt(x_true*x_true + y_true*y_true);

          //if(RunwithFid==true){
            //if(IsInFiducalVolumeFromtheInnerEdge( r, z, 50.0  )==false) continue;}
            double secTrkTrueEnergy = Energy_trklist.at(secondTrk);
            double wgt_minerva_v1 = universe->GetWeight(kWeights_v1tune);

            int secTrk_PDG = PDG_trklist.at(secondTrk);
            double secTrkAngle  = Angle_trklist.at(secondTrk);
            double secTrkTrueAngle = universe->GetTRUE_NonmuTrkANGLE_WRTB(secondTrk);

            double Theta = universe->GetThetamu();
            double Pmu = universe -> GetPmu()/1000;
            double Emu =   universe->GetEmu()*.001;
            double phi = universe -> GetPhimu();
            double Theta_Degs = Theta* TMath::RadToDeg();

            double px = Pmu * std::sin(Theta) * std::cos(phi);
            double py = Pmu * std::sin(Theta) * std::sin(phi);

            double PT = sqrt(px*px + py*py);
            double PZ = Pmu*std::cos(Theta);


            double Emu_TRUE = universe->GetTRUE_Emu();
            double Theta_TRUE = universe->GetThetalepTrue();
            double phi_TRUE = universe->GetPhilepTrue();
            double Theta_Degs_TRUE = Theta_TRUE* TMath::RadToDeg();
            //double Pmu_TRUE = universe->GetTRUE_Pmu();
            //double px_TRUE = Pmu_TRUE * std::sin(Theta_TRUE) * std::cos(phi_TRUE);
            //double py_TRUE = Pmu_TRUE * std::sin(Theta_TRUE) * std::sin(phi_TRUE);

            //double MuonPT_TRUE = sqrt(px_TRUE*px_TRUE + py_TRUE*py_TRUE);
            //double MuonPZ_TRUE = Pmu_TRUE*std::cos(Theta_TRUE);

            double MuonPZ_TRUE = universe->GetPmuLongitudinalTrue();
            double MuonPT_TRUE = universe->GetPmuTransverseTrue();

            //Particle_type GroupType = GetParticlegroup_typeReduced(secTrk_PDG);

        if(isCV(*universe)){


          int index_trajector = universe->getindexTrueTrajectors_closestRECO();
          int pdg_trajector = universe->Get_index_Trajector_PDG(index_trajector);
          auto EnergyFraction_vector = universe->Get_TrueFractionE_vector();


          if(secondTrk==-999 || secondTrk== -9999 )continue;
          // Turned off Energy function



          Particle_type Particle_type_Event = GetParticlegroup_typeReduced(secTrk_PDG);
          Interaction_type Interaction_type_Event =  universe->Get_Interaction_withDISbreakdown();//universe->Get_InteractionStackType();
          Material_type Material_type_Event = universe->Get_MaterialStackType();

          int run = universe->GetRunN();
          int subrun = universe->GetSubRunN();
          int gate = universe->GetGateN();
          int slice  = universe->GetSliceN();

          int True_tracksize = PDG_trklist.size();

          h_Mig_MuonE->Fill(Emu,Emu_TRUE,wgt_minerva_v1);
          h_Mig_MuonPZ->Fill(PZ,MuonPZ_TRUE,wgt_minerva_v1);
          h_Mig_MuonPT->Fill(PT,MuonPT_TRUE,wgt_minerva_v1);
          h_Mig_MuonTheta->Fill(Theta_Degs,Theta_Degs_TRUE,wgt_minerva_v1);

          MnvR_Muon_PT->Fill(PT,MuonPT_TRUE,wgt_minerva_v1);
          MnvR_Muon_PZ->Fill(PZ,MuonPZ_TRUE,wgt_minerva_v1);
          MnvR_Muon_theta->Fill(Theta_Degs,Theta_Degs_TRUE,wgt_minerva_v1);
          MnvR_Muon_E->Fill(Emu,Emu_TRUE,wgt_minerva_v1);

          MnvR_Muon_PT_plus10percent->Fill(PT,MuonPT_TRUE,wgt_minerva_v1*1.1);
          MnvR_Muon_PZ_plus10percent->Fill(PZ,MuonPZ_TRUE,wgt_minerva_v1*1.1);
          MnvR_Muon_theta_plus10percent->Fill(Theta_Degs,Theta_Degs_TRUE,wgt_minerva_v1*1.1);
          MnvR_Muon_E_plus10percent->Fill(Emu,Emu_TRUE,wgt_minerva_v1*1.1);
          MnvR_Muon_PT_minus10percent->Fill(PT,MuonPT_TRUE,wgt_minerva_v1*.9);
          MnvR_Muon_PZ_minus10percent->Fill(PZ,MuonPZ_TRUE,wgt_minerva_v1*.9);
          MnvR_Muon_theta_minus10percent->Fill(Theta_Degs,Theta_Degs_TRUE,wgt_minerva_v1*.9);
          MnvR_Muon_E_minus10percent->Fill(Emu,Emu_TRUE,wgt_minerva_v1*.9);





          MnvR_Muon_PT_WarpFunction->Fill(PT,MuonPT_TRUE,wgt_minerva_v1*WarpingFunctionPT_GeV(MuonPT_TRUE));
          MnvR_Muon_PZ_WarpFunction->Fill(PZ,MuonPZ_TRUE,wgt_minerva_v1*WarpingFunctionPZ_GeV(MuonPZ_TRUE));
          MnvR_Muon_E_WarpFunction->Fill(Emu,Emu_TRUE,wgt_minerva_v1*WarpingFunctionE_GeV(Emu_TRUE));
          MnvR_Muon_theta_WarpFunction->Fill(Theta_Degs, Theta_Degs_TRUE,wgt_minerva_v1*WarpingFunctionTheta_Deg(Theta_Degs_TRUE));

          /// Assuming that only need the cv


          h_Mig_Vertex_X->Fill(x,x_true,wgt_minerva_v1);
          h_Mig_Vertex_Y->Fill(y,y_true,wgt_minerva_v1);
          h_Mig_Vertex_R->Fill(r,r_true,wgt_minerva_v1);
          h_Mig_Vertex_Z->Fill(z,z_true,wgt_minerva_v1);


        } // END OF CV
        ///////////////////////////////////////////
        ////
        ////  END OF CV For TRUTH + RECO cuts
        ////
        ///////////////////////////////////////////
        int True_tracksize = PDG_trklist.size();

        h_MuonE_TRUE_RECO.univHist(universe)->Fill(Emu_TRUE,wgt_minerva_v1);

        h_MuonPZ_TRUE_RECO.univHist(universe)->Fill(MuonPZ_TRUE,wgt_minerva_v1);

        h_MuonPT_TRUE_RECO.univHist(universe)->Fill(MuonPT_TRUE,wgt_minerva_v1);

        h_MuonTheta_TRUE_RECO.univHist(universe)->Fill(Theta_Degs_TRUE,wgt_minerva_v1);

      }// END Reco Cuts
    }//END OF TRUTH PASS CUTS
    unv_count++;
  } // end of Error universe loop
} // End of Band names
  ///////////////////////////////////////////
  ////
  ////
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


double countdata= 0.0;
double countmc= 0.0;

    h_MuonPZ.SyncCVHistos();
    h_MuonPT.SyncCVHistos();
    h_MuonE.SyncCVHistos();
    h_MuonTheta.SyncCVHistos();
    h_MuonE_BG.SyncCVHistos();
    h_MuonPZ_BG.SyncCVHistos();
    h_MuonPT_BG.SyncCVHistos();
    h_MuonTheta_BG.SyncCVHistos();
    h_MuonPZ_Fake.SyncCVHistos();
    h_MuonPT_Fake.SyncCVHistos();
    h_MuonE_Fake.SyncCVHistos();
    h_MuonTheta_Fake.SyncCVHistos();
    h_MuonPZ_Fake2.SyncCVHistos();
    h_MuonPT_Fake2.SyncCVHistos();
    h_MuonE_Fake2.SyncCVHistos();
    h_MuonTheta_Fake2.SyncCVHistos();

    h_MuonPZ_TRUE_RECO.SyncCVHistos();
    h_MuonPT_TRUE_RECO.SyncCVHistos();
    h_MuonE_TRUE_RECO.SyncCVHistos();
    h_MuonTheta_TRUE_RECO.SyncCVHistos();

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


  //outFileName = "Histograms_test.root";
  //auto outFile = TFile::Open(outFileName);
  if(Run_EventLoopOnGid==true){
    sprintf(outFileName, "%s_%s_%s_%s_TRANSWARP_MK.root", "Histograms",c,d,ErrorStatus);
    std::cout << "Writing output file on Grid to: " <<outFileName << std::endl;

  }
  else{
    sprintf(outFileName, "%s/%s_%s_%s_%s_TRANSWARP_MK.root", rootpathway, "Histograms",c,d,ErrorStatus);
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

  h_MuonPZ.hist->Write();
  PlotUtils::MnvH1D* h_MuonPZ_FluxIntegrated = PlotUtils::flux_reweighter(playlist_fluxreweighter, nu_pdg, useNuEconstraint, NFlux_universe).GetIntegratedFluxReweighted(nu_pdg, h_MuonPZ.hist, Min_NuFluxEnergy, Max_NuFluxEnergy, useMuonCorrelations); //GetRebinnedFluxReweighted (nu_pdg, h_MuonPZ.hist);
  h_MuonPZ_FluxIntegrated->Clone()->Write("h_MuonPZ_FluxIntegrated");


  h_MuonPZ_TRUE_RECO.hist->Write();


  h_MuonPT.hist->Write();
  PlotUtils::MnvH1D* h_MuonPT_FluxIntegrated = PlotUtils::flux_reweighter(playlist_fluxreweighter, nu_pdg, useNuEconstraint, NFlux_universe).GetIntegratedFluxReweighted(nu_pdg, h_MuonPT.hist, Min_NuFluxEnergy, Max_NuFluxEnergy, useMuonCorrelations);//GetRebinnedFluxReweighted(nu_pdg, h_MuonPT.hist);
  h_MuonPT_FluxIntegrated->Clone()->Write("h_MuonPT_FluxIntegrated");

  h_MuonPT_TRUE_RECO.hist->Write();
  h_MuonTheta.hist->Write();

  PlotUtils::MnvH1D* h_MuonTheta_FluxIntegrated = PlotUtils::flux_reweighter(playlist_fluxreweighter, nu_pdg, useNuEconstraint, NFlux_universe).GetIntegratedFluxReweighted(nu_pdg, h_MuonTheta.hist, Min_NuFluxEnergy, Max_NuFluxEnergy, useMuonCorrelations); //GetRebinnedFluxReweighted(nu_pdg, h_MuonTheta.hist);
  h_MuonTheta_FluxIntegrated->Clone()->Write("h_MuonTheta_FluxIntegrated");

  h_MuonTheta_TRUE_RECO.hist->Write();

  h_MuonE_BG.hist->Write();
  h_MuonPZ_BG.hist->Write();
  h_MuonPT_BG.hist->Write();
  h_MuonTheta_BG.hist->Write();

  h_MuonPZ_Fake.hist->Write();
  h_MuonPT_Fake.hist->Write();
  h_MuonE_Fake.hist->Write();
  h_MuonTheta_Fake.hist->Write();

  h_MuonPZ_Fake2.hist->Write();
  h_MuonPT_Fake2.hist->Write();
  h_MuonE_Fake2.hist->Write();
  h_MuonTheta_Fake2.hist->Write();



  h_Mig_MuonE->Write();
  h_Mig_MuonPZ->Write();
  h_Mig_MuonPT->Write();
  h_Mig_MuonTheta->Write();

  h_Mig_Vertex_X->Write();
  h_Mig_Vertex_Y->Write();
  h_Mig_Vertex_R->Write();
  h_Mig_Vertex_Z->Write();

  h_Mig_Vertex_X_RECO->Write();
  h_Mig_Vertex_Y_RECO->Write();
  h_Mig_Vertex_R_RECO->Write();
  h_Mig_Vertex_Z_RECO->Write();

  h_Mig_MuonE_py->Write();
  h_Mig_MuonPZ_py->Write();
  h_Mig_MuonPT_py->Write();
  h_Mig_MuonTheta_py->Write();
  h_Mig_MuonE_px->Write();
  h_Mig_MuonPZ_px->Write();
  h_Mig_MuonPT_px->Write();
  h_Mig_MuonTheta_px->Write();

  bool clear_bands = true;
  for (auto cat: MnvR_vector){


    MnvH2D *migrationH = NULL;
    MnvH1D *h_reco = NULL;
    MnvH1D *h_truth = NULL;
    bool check = cat->GetMigrationObjects(migrationH, h_reco, h_truth );

        std::cout<< "finihsed  mresp.SyncCVHistos();"<<std::endl;
      migrationH->Write();
      std::cout<< "finihsed mresp_reco.hist->Write();  "<<std::endl;
      //h_reco.SyncCVHistos();
      h_reco->Write();
      h_truth->Write();

  }




  outFile->Close();


  char playlistname_char[playlist.length()+1];
  strcpy(playlistname_char,playlist.c_str());
  char arachneName[1024];

    std::cout << "END OF Plotting" << std::endl;

   std::cout << " this many Other long tracks  = "<< otherlongtrack<< std::endl;


  for(auto band : error_bands){
    std::vector<HeliumCVUniverse*> band_universes = band.second;
    for(unsigned int i_universe = 0; i_universe < band_universes.size(); ++i_universe){ delete band_universes[i_universe];}
  }

  std::cout << "Success" << std::endl;




//can -> Print("Test.pdf");

}//END of Eventloop Function

//=========================================
//=========================================
//////////////////////////////////////////////////////////////


std::vector<ECuts> GetRECOCutsVector() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ECuts> ret_vec;
  ret_vec.push_back(kNoCuts  );
  //ret_vec.push_back(kGoodEnergy );
  //ret_vec.push_back(kThetaMu );
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
  ret_vec.push_back(kVertex_ConvergedfromAllTracks);
  ret_vec.push_back(kMaxChiSqrt_byTrackType);
  //ret_vec.push_back(kFiducialVolume );
  ret_vec.push_back(kFiducialVolume_new );
  ret_vec.push_back(kTrackForwardGoing );
  ret_vec.push_back(ksecTrkwrtblessthanMaxAngle);
  //ret_vec.push_back(kMaxChiSqrt);

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
  //ret_vec.push_back(kGoodEnergy );
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
  //ret_vec.push_back(kFiducialVolume );
  ret_vec.push_back(kFiducialVolume_new );
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
  //True_vec.push_back(kTRUTHMuonEnergy );
  //True_vec.push_back(kTRUTHMuonAngle );
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
  //True_vec.push_back(kTRUTH_NoNeutral_FS_2ndTrk_withProtonanPionThresholds_RECOBRANCH);
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);
  True_vec.push_back(kAllTRUTHCuts);


  //int n = sizeof(kCutsArray) / sizeof(kCutsArray[0]);
  //static std::vector<ECuts> ret_vec(kCutsArray, kCutsArray + n);
  return True_vec;
//#endif
}

std::vector<ECutsTRUTH> GetTRUTHCutsVector_noMuonPhaseSpace() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ECutsTRUTH> True_vec;
  True_vec.push_back(kTRUTHNoCuts   );
  //True_vec.push_back(kTRUTHMuonEnergy );
  //True_vec.push_back(kTRUTHMuonAngle );
  True_vec.push_back(kTRUTHneutrino);
  True_vec.push_back(kTRUTHCCInteraction );
  True_vec.push_back(kTRUTHtarget);
  True_vec.push_back(kTRUTH_greaterthanoneFS);
  //True_vec.push_back(kTRUTHFiduical ); // dont' apply truth fiduical cut in Nomrateor
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);
  //True_vec.push_back(kTRUTH_NoNeutral_FS_2ndTrk_RECOBRANCH);
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
 weight_vec.push_back(kweightMK);



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
