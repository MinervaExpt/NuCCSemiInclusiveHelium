// Loop entries, make cuts, fill histograms.
// * Uses the New Systematics Framework and "Universe" objects.
// * loop universes, make cuts and fill histograms with the correct lateral
// shifts and weights for each universe.
// * TChain --> PlotUtils::ChainWrapper.
// * MnvHXD --> PlotUtils::HistWrapper.
// * Genie, flux, non-resonant pion, and some detector systematics calculated.
#include "Helium_runEventLoopForDATA.h"

std::string OUTputRoot_pathway = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles";
//=====================================================
// Functions
//=====================================================
std::vector<ECuts> GetRECOCutsVector();
std::vector<ECuts> GetVectorRECOCutsFidicual_Eff();
std::vector<MuonVar> GetMUONVaribles();
std::vector<SecondTrkVar> GetPlayListSecondTrkVector();
std::vector<CryoVertex> GetCryoVertexVaribles();
std::vector<ME_helium_Playlists> GetPlayListVector();
std::vector<ME_helium_Playlists> GetTRUEPlayListVector();
// Get container of systematics

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
CryoRegion14_Category = {
  PlotUtils::NamedCategory<CryoTank_REGIONS>({Zregion1}, "Region_1" ),
  PlotUtils::NamedCategory<CryoTank_REGIONS>({Zregion2}, "Region_2" ),
  PlotUtils::NamedCategory<CryoTank_REGIONS>({Zregion3}, "Region_3" ),
  PlotUtils::NamedCategory<CryoTank_REGIONS>({Zregion4}, "Region_4" ),
  PlotUtils::NamedCategory<CryoTank_REGIONS>({Zregion5}, "Region_5" ),
  PlotUtils::NamedCategory<CryoTank_REGIONS>({Zregion6}, "Region_6" ),
  PlotUtils::NamedCategory<CryoTank_REGIONS>({Zregion7}, "Region_7" ),
  PlotUtils::NamedCategory<CryoTank_REGIONS>({Zregion8}, "Region_8" ),
  PlotUtils::NamedCategory<CryoTank_REGIONS>({Zregion9}, "Region_9" ),
  PlotUtils::NamedCategory<CryoTank_REGIONS>({Zregion10}, "Region_10" ),
  PlotUtils::NamedCategory<CryoTank_REGIONS>({Zregion11}, "Region_11" ),
  PlotUtils::NamedCategory<CryoTank_REGIONS>({Zregion12}, "Region_12" ),
  PlotUtils::NamedCategory<CryoTank_REGIONS>({Zregion13}, "Region_13" ),
  PlotUtils::NamedCategory<CryoTank_REGIONS>({Zregion14}, "Region_14" )
};









//======================================================================
//void EventCounter(const HeliumCVUniverse& , std::vector<ECuts> cuts, EventCount_RECO &Event_map ,bool isNOT_mc,HeliumPlayListInfo Info );
// Main
void runEventLoop(ME_helium_Playlists &PlayList_iterator) {
  // Make a chain of events
  loadLibs();
//std::vector<ECuts> kCutsVector;
bool isNOT_mc= false;
bool is_counter = true;
double POT[4];
int num_NotDefinedTracks=0;
const std::vector< ECuts > kCutsVector = GetRECOCutsVector();
const std::vector< ECuts > kCutsVector_Fiduical =GetVectorRECOCutsFidicual_Eff();
//const std::vector< ECuts > kCutsVector_Fiduical = GetRECOCutsVector();
const std::vector< ME_helium_Playlists> kPlayListVector = GetPlayListVector();
const std::vector< ME_helium_Playlists> kTRUEPlayListVector = GetTRUEPlayListVector();

const std::vector<MuonVar> kMuonVaribles_vector = GetMUONVaribles();
const std::vector<SecondTrkVar> ksecTrkVaribles_vector = GetPlayListSecondTrkVector();

const std::vector<CryoVertex> kCryoVertexVaribles_vector = GetCryoVertexVaribles();
EventPlaylist_RecoCount EventCountMap;
MinervaUniverse::SetTruth(false);
MinervaUniverse::SetNuEConstraint(false);
MinervaUniverse::SetDeuteriumGeniePiTune(false);

std::string playlist = GetPlaylist(PlayList_iterator);
MinervaUniverse::SetPlaylist(playlist);
int trackcount=0;
int trackcount_track=0;

std::vector<SliceID_vertex_info> SliceID_vertex_info_vector;
std::vector<Trajector_DATA> Trajector_DATA_vector;
std::vector<SliceID_vertex_info> SliceID_vertex_info_length_vector;
std::vector<Trajector_DATA> Trajector_DATA_length_vector;
//======================================================================
////////////////////ADDING TO CHAIN wrapper ///////////////////////////
//======================================================================

//======================================================================
///////////////////Making/adding to error bands  ///////////////////////////
//======================================================================

POTCounter pot_counter;


  auto mcscale = 1.0; //Data_POT_full/ MC_POT_full;

double Mev_to_GeV=.001;


//std::cout << "MC_POT_full = "<< MC_POT_full<< " MC_POT_empty = "<< MC_POT_empty << "  Data_POT_full = " << Data_POT_full << "  Data_POT_empty = " << Data_POT_empty<< std::endl;

  // Make a map of systematic universes
//  std::map< std::string, std::vector<HeliumCVUniverse*> > DATAerror_bands = GetErrorBands(chw_Data);
std::vector<double> Ebin_vector = GetBinMuonVector(kE);
std::vector<double> Pzbin_vector= GetBinMuonVector(kP_Z);
std::vector<double> PTbin_vector= GetBinMuonVector(kP_T);

std::vector<double> MuonThetabin_vector= GetBinMuonVector(kAngleWRTB);

//std::vector<double> Vertex_Xbin_vector= GetBinvertexVector(kX);
//std::vector<double> Vertex_Ybin_vector= GetBinvertexVector(kY);
//std::vector<double> Vertex_Zbin_vector= GetBinvertexVector(kZ);
//std::vector<double> Vertex_Rbin_vector= GetBinvertexVector(kR);

std::vector<double> Vertex_Zbin_vector{1450, 1750.00, 2050.00, 2250, 2450, 2650, 2850, 3000, 3200,  3400, 3650, 3900, 4200, 4350};
std::vector<double> Vertex_Rbin_vector{0, 200, 400, 600,  700,   800,  1000,  1200};
std::vector<double> Vertex_Ybin_vector{-1200, -1000, -800, -600, -400, -200, 0, 200, 400, 600, 800, 1000, 1200};
std::vector<double> Vertex_Xbin_vector{-1200, -1000, -800, -600, -400, -200, 0, 200, 400, 600, 800, 1000, 1200};



std::vector<double> Vertex_DOCAbin_vector = GetBinMuonVector(kDOCA_muon);
std::vector<double> secTrk_DOCA_vector = GetSecondTrkVarVector(kDOCA);

//std::vector<double> secTrkEbin_vector = GetSecondTrkVarVector(ksecE_Proton);
std::vector<double> secTrkEbin_vector= GetSecondTrkVarVector(ksecE);
std::vector<double> secTrkThetamid_vector= GetSecondTrkVarVector(kThetamid);

std::vector<double> secTrkPathway_vector = GetSecondTrkVarVector(kPathway);

std::vector<double> BinVector_MatchToveto= GetBinMuonVector(kMuonMatchtoVeto);
std::vector<double> Minos_R_vector = GetBinMuonVector(kminos_R);
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

std::vector<double> secTrk_StartNode_X_vector= GetSecondTrkVarVector(kFirstsecTrk_Xnode);
std::vector<double> secTrk_StartNode_Y_vector= GetSecondTrkVarVector(kFirstsecTrk_Ynode);
std::vector<double> secTrk_StartNode_Z_vector= GetSecondTrkVarVector(kFirstsecTrk_Znode);

std::vector<double> secTrk_LastNode_X_vector= GetSecondTrkVarVector(kLastsecTrk_Xnode);
std::vector<double> secTrk_LastNode_Y_vector= GetSecondTrkVarVector(kLastsecTrk_Ynode);
std::vector<double> secTrk_LastNode_Z_vector= GetSecondTrkVarVector(kLastsecTrk_Znode);
std::vector<double> TrackSize_vector = GetBinMuonVector(ktracksize);

std::vector<double> Vertex_ChiSqFit_vector= GetBinvertexVector(kfitConverge);
std::vector<double> Muon_curvatureSig_vector= GetBinMuonVector(kcurvatureSig);

std::vector<double> MuonCharge_vector= GetBinMuonVector(kCharge);
std::vector<double> MuonMatchtoMinos_vector= GetBinMuonVector(kMuonMatchtoMinos);
std::vector<double> MuonMatchtoVeto_vector= GetBinMuonVector(kMuonMatchtoVeto);

std::vector<double> Veto_PMTmap_vector = GetVetowall_BinVetor(kPMTMap);
std::vector<double> Recoil_track_length_vector = GetSecondTrkVarVector(ksec_tracklength_minerva);;
std::vector<double> secTrk_Pathway_vector = GetSecondTrkVarVector(kPathway);
std::vector<double> Distance_to_innerTank = GetBinvertexVector(kdistance_edge);
std::vector<double> Distance_to_Caps = GetBinvertexVector(kdistance_downstreamcap);
std::vector<double> pseudorapidity_muon_vector{1.0, 1.5,2.0,2.25,2.5,2.75,3.0,3.25,3.5,3.75,4.0,4.5,5.0,8.0};
std::vector<double> rapidity_muon_vector{2.25,  2.45,  2.65,   2.85,  3.05,  3.25, 3.45, 3.65};
//std::vector<double> CutToSurface_bins{-400, -380, -360, -340, -320, -300, -280, -260, -240, -220, -200, -180, -160, -140, -120, -100, -80, -60, -40, -20, 0, 20, 40, 60, 80, 100, 120};


MnvH1D *h_Data_Distance_to_InnerTank          =              new MnvH1D("h_Data_Distance_to_InnerTank",                       "h_Data_Distance_to_InnerTank", Distance_to_innerTank.size()-1, Distance_to_innerTank.data());
MnvH1D *h_Data_Distance_to_InnerTank_Fidiucal =              new MnvH1D("h_Data_Distance_to_InnerTank_Fidiucal",              "h_Data_Distance_to_InnerTank_Fidiucal", Distance_to_innerTank.size()-1, Distance_to_innerTank.data());
MnvH1D *h_Data_Distance_to_InnerTank_UpstreamCap =           new MnvH1D("h_Data_Distance_to_InnerTank_UpstreamCap",           "h_Data_Distance_to_InnerTank_UpstreamCap", Distance_to_innerTank.size()-1, Distance_to_innerTank.data());
MnvH1D *h_Data_Distance_to_InnerTank_Barrel      =           new MnvH1D("h_Data_Distance_to_InnerTank_Barrel",                "h_Data_Distance_to_InnerTank_Barrel", Distance_to_innerTank.size()-1, Distance_to_innerTank.data());
MnvH1D *h_Data_Distance_to_InnerTank_DownstreamCap =         new MnvH1D("h_Data_Distance_to_InnerTank_DownstreamCap",         "h_Data_Distance_to_InnerTank_DownstreamCap", Distance_to_innerTank.size()-1, Distance_to_innerTank.data());
MnvH1D *h_Data_Distance_to_InnerTank_Downstream_ConcaveCap = new MnvH1D("h_Data_Distance_to_InnerTank_Downstream_ConcaveCap", "h_Data_Distance_to_InnerTank_Downstream_ConcaveCap", Distance_to_innerTank.size()-1, Distance_to_innerTank.data());

MnvH1D *h_Data_Distance_to_InnerTank_Caps_UpstreamCap =           new MnvH1D("h_Data_Distance_to_InnerTank_Caps_UpstreamCap",           "h_Data_Distance_to_InnerTank_Caps_UpstreamCap", Distance_to_innerTank.size()-1, Distance_to_innerTank.data());
MnvH1D *h_Data_Distance_to_InnerTank_Caps_Barrel      =           new MnvH1D("h_Data_Distance_to_InnerTank_Caps_Barrel",                "h_Data_Distance_to_InnerTank_Caps_Barrel", Distance_to_innerTank.size()-1, Distance_to_innerTank.data());
MnvH1D *h_Data_Distance_to_InnerTank_Caps_DownstreamCap =         new MnvH1D("h_Data_Distance_to_InnerTank_Caps_DownstreamCap",         "h_Data_Distance_to_InnerTank_Caps_DownstreamCap", Distance_to_innerTank.size()-1, Distance_to_innerTank.data());
MnvH1D *h_Data_Distance_to_InnerTank_Caps_Downstream_ConcaveCap = new MnvH1D("h_Data_Distance_to_InnerTank_Caps_Downstream_ConcaveCap", "h_Data_Distance_to_InnerTank_Caps_Downstream_ConcaveCap", Distance_to_innerTank.size()-1, Distance_to_innerTank.data());

MnvH1D *h_Data_Distance_to_InnerTank_Barrel_UpstreamCap =           new MnvH1D("h_Data_Distance_to_InnerTank_Barrel_UpstreamCap",           "h_Data_Distance_to_InnerTank_Barrel_UpstreamCap", Distance_to_innerTank.size()-1, Distance_to_innerTank.data());
MnvH1D *h_Data_Distance_to_InnerTank_Barrel_Barrel      =           new MnvH1D("h_Data_Distance_to_InnerTank_Barrel_Barrel",                "h_Data_Distance_to_InnerTank_Barrel_Barrel", Distance_to_innerTank.size()-1, Distance_to_innerTank.data());
MnvH1D *h_Data_Distance_to_InnerTank_Barrel_DownstreamCap =         new MnvH1D("h_Data_Distance_to_InnerTank_Barrel_DownstreamCap",         "h_Data_Distance_to_InnerTank_Barrel_DownstreamCap", Distance_to_innerTank.size()-1, Distance_to_innerTank.data());
MnvH1D *h_Data_Distance_to_InnerTank_Barrel_Downstream_ConcaveCap = new MnvH1D("h_Data_Distance_to_InnerTank_Barrel_Downstream_ConcaveCap", "h_Data_Distance_to_InnerTank_Barrel_Downstream_ConcaveCap", Distance_to_innerTank.size()-1, Distance_to_innerTank.data());

MnvH1D *h_Data_Distance_to_UpstreamCap                       = new MnvH1D("h_Data_Distance_to_UpstreamCap",                     "h_Data_Distance_to_UpstreamCap",                      Distance_to_Caps.size()-1, Distance_to_Caps.data());
MnvH1D *h_Data_Distance_to_UpstreamCap_UpstreamCap           = new MnvH1D("h_Data_Distance_to_UpstreamCap_UpstreamCap",          "h_Data_Distance_to_UpstreamCap_UpstreamCap",             Distance_to_Caps.size()-1, Distance_to_Caps.data());
MnvH1D *h_Data_Distance_to_UpstreamCap_Barrel                = new MnvH1D("h_Data_Distance_to_UpstreamCap_Barrel",              "h_Data_Distance_to_UpstreamCap_Barrel",               Distance_to_Caps.size()-1, Distance_to_Caps.data());
MnvH1D *h_Data_Distance_to_UpstreamCap_DownstreamCap         = new MnvH1D("h_Data_Distance_to_UpstreamCap_DownstreamCap",       "h_Data_Distance_to_UpstreamCap_DownstreamCap",        Distance_to_Caps.size()-1, Distance_to_Caps.data());
MnvH1D *h_Data_Distance_to_UpstreamCap_Downstream_ConcaveCap = new MnvH1D("h_Data_Distance_to_UpstreamCap_Downstream_ConcaveCap","h_Data_Distance_to_UpstreamCap_Downstream_ConcaveCap", Distance_to_Caps.size()-1, Distance_to_Caps.data());

MnvH1D *h_Data_Distance_to_UpstreamCap_RCut                       = new MnvH1D("h_Data_Distance_to_UpstreamCap_RCut",                     "h_Data_Distance_to_UpstreamCap_RCut",                      Distance_to_Caps.size()-1, Distance_to_Caps.data());
MnvH1D *h_Data_Distance_to_UpstreamCap_RCut_UpstreamCap           = new MnvH1D("h_Data_Distance_to_UpstreamCap_RCut_UpstreamCap",            "h_Data_Distance_to_UpstreamCap_RCut_UpstreamCap",    Distance_to_Caps.size()-1, Distance_to_Caps.data());
MnvH1D *h_Data_Distance_to_UpstreamCap_RCut_Barrel                = new MnvH1D("h_Data_Distance_to_UpstreamCap_RCut_Barrel",              "h_Data_Distance_to_UpstreamCap_RCut_Barrel",               Distance_to_Caps.size()-1, Distance_to_Caps.data());
MnvH1D *h_Data_Distance_to_UpstreamCap_RCut_DownstreamCap         = new MnvH1D("h_Data_Distance_to_UpstreamCap_RCut_DownstreamCap",       "h_Data_Distance_to_UpstreamCap_RCut_DownstreamCap",        Distance_to_Caps.size()-1, Distance_to_Caps.data());
MnvH1D *h_Data_Distance_to_UpstreamCap_RCut_Downstream_ConcaveCap = new MnvH1D("h_Data_Distance_to_UpstreamCap_RCut_Downstream_ConcaveCap","h_Data_Distance_to_UpstreamCap_RCut_Downstream_ConcaveCap", Distance_to_Caps.size()-1, Distance_to_Caps.data());


MnvH1D *h_Data_Distance_to_DownstreamCap                       =  new MnvH1D("h_Data_Distance_to_DownstreamCap",                      "h_Data_Distance_to_DownstreamCap",                      Distance_to_Caps.size()-1, Distance_to_Caps.data());
MnvH1D *h_Data_Distance_to_DownstreamCap_UpstreamCap           =  new MnvH1D("h_Data_Distance_to_DownstreamCap_UpstreamCap",             "h_Data_Distance_to_DownstreamCap_UpstreamCap",    Distance_to_Caps.size()-1, Distance_to_Caps.data());
MnvH1D *h_Data_Distance_to_DownstreamCap_Barrel                =  new MnvH1D("h_Data_Distance_to_DownstreamCap_Barrel",               "h_Data_Distance_to_DownstreamCap_Barrel",               Distance_to_Caps.size()-1, Distance_to_Caps.data());
MnvH1D *h_Data_Distance_to_DownstreamCap_DownstreamCap         =  new MnvH1D("h_Data_Distance_to_DownstreamCap_DownstreamCap",        "h_Data_Distance_to_DownstreamCap_DownstreamCap",        Distance_to_Caps.size()-1, Distance_to_Caps.data());
MnvH1D *h_Data_Distance_to_DownstreamCap_Downstream_ConcaveCap =  new MnvH1D("h_Data_Distance_to_DownstreamCap_Downstream_ConcaveCap", "h_Data_Distance_to_DownstreamCap_Downstream_ConcaveCap", Distance_to_Caps.size()-1, Distance_to_Caps.data());

MnvH1D *h_Data_Distance_to_DownstreamCap_RCut                       =  new MnvH1D("h_Data_Distance_to_DownstreamCap_RCut",                      "h_Data_Distance_to_DownstreamCap_RCut",                      Distance_to_Caps.size()-1, Distance_to_Caps.data());
MnvH1D *h_Data_Distance_to_DownstreamCap_RCut_UpstreamCap           =  new MnvH1D("h_Data_Distance_to_DownstreamCap_RCut_UpstreamCap",          "h_Data_Distance_to_DownstreamCap_RCut_UpstreamCap",       Distance_to_Caps.size()-1, Distance_to_Caps.data());
MnvH1D *h_Data_Distance_to_DownstreamCap_RCut_Barrel                =  new MnvH1D("h_Data_Distance_to_DownstreamCap_RCut_Barrel",               "h_Data_Distance_to_DownstreamCap_RCut_Barrel",               Distance_to_Caps.size()-1, Distance_to_Caps.data());
MnvH1D *h_Data_Distance_to_DownstreamCap_RCut_DownstreamCap         =  new MnvH1D("h_Data_Distance_to_DownstreamCap_RCut_DownstreamCap",        "h_Data_Distance_to_DownstreamCap_RCut_DownstreamCap",        Distance_to_Caps.size()-1, Distance_to_Caps.data());
MnvH1D *h_Data_Distance_to_DownstreamCap_RCut_Downstream_ConcaveCap =  new MnvH1D("h_Data_Distance_to_DownstreamCap_RCut_Downstream_ConcaveCap", "h_Data_Distance_to_DownstreamCap_RCut_Downstream_ConcaveCap", Distance_to_Caps.size()-1, Distance_to_Caps.data());

////////////////
//muon Energy///
////////////////

MnvH1D *h_Data_MuonE       =    new MnvH1D("h_Data_MuonE", "h_Data_MuonE", Ebin_vector.size()-1, Ebin_vector.data());
MnvH1D *h_Data_MuonPT      =    new MnvH1D("h_Data_MuonPT", "h_Data_MuonPT", PTbin_vector.size()-1, PTbin_vector.data());
MnvH1D *h_Data_MuonPZ      =    new MnvH1D("h_Data_MuonPZ", "h_Data_MuonPZ", Pzbin_vector.size()-1, Pzbin_vector.data());
MnvH1D *h_Data_MuonTheta   =    new MnvH1D("h_Data_MuonTheta", "h_Data_MuonTheta", MuonThetabin_vector.size()-1, MuonThetabin_vector.data());
MnvH1D *h_Data_MuonDOCA    =    new MnvH1D("h_Data_MuonDOCA", "h_Data_MuonDOCA", Vertex_DOCAbin_vector.size()-1, Vertex_DOCAbin_vector.data());


PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS> h_Data_MuonE_CryoRegion14 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS>(CryoRegion14_Category, "h_Data_MuonE_CryoRegion14", Ebin_vector ,"h_Data_MuonE_CryoRegion14; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS> h_Data_MuonPT_CryoRegion14 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS>(CryoRegion14_Category, "h_Data_MuonPT_CryoRegion14", PTbin_vector ,"h_Data_MuonPT_CryoRegion14; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS> h_Data_MuonPZ_CryoRegion14 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS>(CryoRegion14_Category, "h_Data_MuonPZ_CryoRegion14", Pzbin_vector ,"h_Data_MuonPZ_CryoRegion14; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS> h_Data_MuonTheta_CryoRegion14 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS>(CryoRegion14_Category, "h_Data_MuonTheta_CryoRegion14", MuonThetabin_vector,"h_Data_MuonTheta_CryoRegion14; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS> h_Data_MuonDOCA_CryoRegion14 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS>(CryoRegion14_Category, "h_Data_MuonDOCA_CryoRegion14", Vertex_DOCAbin_vector,"h_Data_MuonDOCA_CryoRegion14; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS> h_Data_Distance_to_InnerTank_CryoRegion14 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS>(CryoRegion14_Category, "h_Data_Distance_to_InnerTank_CryoRegion14", Distance_to_innerTank,"h_Data_Distance_to_InnerTank_CryoRegion14; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS> h_Data_CryoVertex_Y_CryoRegion14 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS>(CryoRegion14_Category, "h_Data_CryoVertex_Y_CryoRegion14", Vertex_Ybin_vector ,"h_Data_CryoVertex_Y_CryoRegion14; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS> h_Data_CryoVertex_X_CryoRegion14 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS>(CryoRegion14_Category, "h_Data_CryoVertex_X_CryoRegion14", Vertex_Xbin_vector ,"h_Data_CryoVertex_X_CryoRegion14; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS> h_Data_CryoVertex_Z_CryoRegion14 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS>(CryoRegion14_Category, "h_Data_CryoVertex_Z_CryoRegion14", Vertex_Zbin_vector ,"h_Data_CryoVertex_Z_CryoRegion14; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS> h_Data_CryoVertex_R_CryoRegion14 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS>(CryoRegion14_Category, "h_Data_CryoVertex_R_CryoRegion14", Vertex_Rbin_vector ,"h_Data_CryoVertex_R_CryoRegion14; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS> h_Data_secTrk_DOCA_CryoRegion14 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS>(CryoRegion14_Category, "h_Data_secTrk_DOCA_CryoRegion14", secTrk_DOCA_vector,"h_Data_secTrk_DOCA_CryoRegion14; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS> h_Data_secTrk_Length_CryoRegion14 =
PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS>(CryoRegion14_Category, "h_Data_secTrk_Length_CryoRegion14", Recoil_track_length_vector,"h_Data_secTrk_Length_CryoRegion14; [mm];Events");




MnvH1D *h_Data_MuonE_UpstreamCap       =    new MnvH1D("h_Data_MuonE_UpstreamCap",     "h_Data_MuonE_UpstreamCap", Ebin_vector.size()-1, Ebin_vector.data());
MnvH1D *h_Data_MuonPT_UpstreamCap      =    new MnvH1D("h_Data_MuonPT_UpstreamCap",    "h_Data_MuonPT_UpstreamCap", PTbin_vector.size()-1, PTbin_vector.data());
MnvH1D *h_Data_MuonPZ_UpstreamCap      =    new MnvH1D("h_Data_MuonPZ_UpstreamCap",    "h_Data_MuonPZ_UpstreamCap", Pzbin_vector.size()-1, Pzbin_vector.data());
MnvH1D *h_Data_MuonTheta_UpstreamCap   =    new MnvH1D("h_Data_MuonTheta_UpstreamCap", "h_Data_MuonTheta_UpstreamCap", MuonThetabin_vector.size()-1, MuonThetabin_vector.data());
MnvH1D *h_Data_MuonDOCA_UpstreamCap    =    new MnvH1D("h_Data_MuonDOCA_UpstreamCap",  "h_Data_MuonDOCA_UpstreamCap", Vertex_DOCAbin_vector.size()-1, Vertex_DOCAbin_vector.data());


MnvH1D *h_Data_MuonE_Barrel       =    new MnvH1D("h_Data_MuonE_Barrel", "h_Data_MuonE_Barrel",         Ebin_vector.size()-1, Ebin_vector.data());
MnvH1D *h_Data_MuonPT_Barrel      =    new MnvH1D("h_Data_MuonPT_Barrel", "h_Data_MuonPT_Barrel",       PTbin_vector.size()-1, PTbin_vector.data());
MnvH1D *h_Data_MuonPZ_Barrel      =    new MnvH1D("h_Data_MuonPZ_Barrel", "h_Data_MuonPZ_Barrel",       Pzbin_vector.size()-1, Pzbin_vector.data());
MnvH1D *h_Data_MuonTheta_Barrel   =    new MnvH1D("h_Data_MuonTheta_Barrel", "h_Data_MuonTheta_Barrel", MuonThetabin_vector.size()-1, MuonThetabin_vector.data());
MnvH1D *h_Data_MuonDOCA_Barrel    =    new MnvH1D("h_Data_MuonDOCA_Barrel", "h_Data_MuonDOCA_Barrel",   Vertex_DOCAbin_vector.size()-1, Vertex_DOCAbin_vector.data());


MnvH1D *h_Data_MuonE_DownstreamCap       =    new MnvH1D("h_Data_MuonE_DownstreamCap", "h_Data_MuonE_DownstreamCap", Ebin_vector.size()-1, Ebin_vector.data());
MnvH1D *h_Data_MuonPT_DownstreamCap      =    new MnvH1D("h_Data_MuonPT_DownstreamCap", "h_Data_MuonPT_DownstreamCap", PTbin_vector.size()-1, PTbin_vector.data());
MnvH1D *h_Data_MuonPZ_DownstreamCap      =    new MnvH1D("h_Data_MuonPZ_DownstreamCap", "h_Data_MuonPZ_DownstreamCap", Pzbin_vector.size()-1, Pzbin_vector.data());
MnvH1D *h_Data_MuonTheta_DownstreamCap   =    new MnvH1D("h_Data_MuonTheta_DownstreamCap", "h_Data_MuonTheta_DownstreamCap", MuonThetabin_vector.size()-1, MuonThetabin_vector.data());
MnvH1D *h_Data_MuonDOCA_DownstreamCap    =    new MnvH1D("h_Data_MuonDOCA_DownstreamCap", "h_Data_MuonDOCA_DownstreamCap", Vertex_DOCAbin_vector.size()-1, Vertex_DOCAbin_vector.data());


MnvH1D *h_Data_MuonE_Downstream_ConcaveCap       =    new MnvH1D("h_Data_MuonE_Downstream_ConcaveCap", "h_Data_MuonE_Downstream_ConcaveCap", Ebin_vector.size()-1, Ebin_vector.data());
MnvH1D *h_Data_MuonPT_Downstream_ConcaveCap      =    new MnvH1D("h_Data_MuonPT_Downstream_ConcaveCap", "h_Data_MuonPT_Downstream_ConcaveCap", PTbin_vector.size()-1, PTbin_vector.data());
MnvH1D *h_Data_MuonPZ_Downstream_ConcaveCap      =    new MnvH1D("h_Data_MuonPZ_Downstream_ConcaveCap", "h_Data_MuonPZ_Downstream_ConcaveCap", Pzbin_vector.size()-1, Pzbin_vector.data());
MnvH1D *h_Data_MuonTheta_Downstream_ConcaveCap   =    new MnvH1D("h_Data_MuonTheta_Downstream_ConcaveCap", "h_Data_MuonTheta_Downstream_ConcaveCap", MuonThetabin_vector.size()-1, MuonThetabin_vector.data());
MnvH1D *h_Data_MuonDOCA_Downstream_ConcaveCap    =    new MnvH1D("h_Data_MuonDOCA_Downstream_ConcaveCap", "h_Data_MuonDOCA_Downstream_ConcaveCap", Vertex_DOCAbin_vector.size()-1, Vertex_DOCAbin_vector.data());
MnvH1D *h_Data_Muon_pseudorapidity   =    new MnvH1D("h_Data_Muon_pseudorapidity", "h_Data_Muon_pseudorapidity", pseudorapidity_muon_vector.size()-1, pseudorapidity_muon_vector.data());
MnvH1D *h_Data_Muon_pseudorapidity_angle   =    new MnvH1D("h_Data_Muon_pseudorapidity_angle", "h_Data_Muon_pseudorapidity_angle", MuonThetabin_vector.size()-1, MuonThetabin_vector.data());

MnvH1D *h_Data_Muon_rapidity    =    new MnvH1D("h_Data_Muon_rapidity", "h_Data_Muon_rapidity", rapidity_muon_vector.size()-1, rapidity_muon_vector.data());

MnvH1D *h_Data_Tracksize =              new MnvH1D("h_Data_Tracksize", "h_Data_Tracksize", TrackSize_vector.size()-1, TrackSize_vector.data());
MnvH1D *h_Data_MuoncurvatureSig    =    new MnvH1D("h_Data_MuoncurvatureSig", "h_Data_MuoncurvatureSig", Muon_curvatureSig_vector.size()-1, Muon_curvatureSig_vector.data());

MnvH1D *h_Data_minosR    =          new MnvH1D("h_Data_minosR", "h_Data_minosR", Minos_R_vector.size()-1, Minos_R_vector.data());



////////////////
//Vertex Hist///
////////////////
MnvH1D *h_Data_CryoVertex_X                       = new MnvH1D("h_Data_CryoVertex_X",                      "h_Data_CryoVertex_X",                       Vertex_Xbin_vector.size()-1, Vertex_Xbin_vector.data());
MnvH1D *h_Data_CryoVertex_X_UpstreamCap           = new MnvH1D("h_Data_CryoVertex_X_UpstreamCap",          "h_Data_CryoVertex_X_UpstreamCap",           Vertex_Xbin_vector.size()-1, Vertex_Xbin_vector.data());
MnvH1D *h_Data_CryoVertex_X_Barrel                = new MnvH1D("h_Data_CryoVertex_X_Barrel",               "h_Data_CryoVertex_X_Barrel",                Vertex_Xbin_vector.size()-1, Vertex_Xbin_vector.data());
MnvH1D *h_Data_CryoVertex_X_DownstreamCap         = new MnvH1D("h_Data_CryoVertex_X_DownstreamCap",        "h_Data_CryoVertex_X_DownstreamCap",         Vertex_Xbin_vector.size()-1, Vertex_Xbin_vector.data());
MnvH1D *h_Data_CryoVertex_X_Downstream_ConcaveCap = new MnvH1D("h_Data_CryoVertex_X_Downstream_ConcaveCap","h_Data_CryoVertex_X_Downstream_ConcaveCap", Vertex_Xbin_vector.size()-1, Vertex_Xbin_vector.data());


////////////////
MnvH1D *h_Data_CryoVertex_X_RCut                       = new MnvH1D("h_Data_CryoVertex_X_RCut",                      "h_Data_CryoVertex_X_RCut",                       Vertex_Xbin_vector.size()-1, Vertex_Xbin_vector.data());
MnvH1D *h_Data_CryoVertex_X_RCut_UpstreamCap           = new MnvH1D("h_Data_CryoVertex_X_RCut_UpstreamCap",          "h_Data_CryoVertex_X_RCut_UpstreamCap",           Vertex_Xbin_vector.size()-1, Vertex_Xbin_vector.data());
MnvH1D *h_Data_CryoVertex_X_RCut_Barrel                = new MnvH1D("h_Data_CryoVertex_X_RCut_Barrel",               "h_Data_CryoVertex_X_RCut_Barrel",                Vertex_Xbin_vector.size()-1, Vertex_Xbin_vector.data());
MnvH1D *h_Data_CryoVertex_X_RCut_DownstreamCap         = new MnvH1D("h_Data_CryoVertex_X_RCut_DownstreamCap",        "h_Data_CryoVertex_X_RCut_DownstreamCap",         Vertex_Xbin_vector.size()-1, Vertex_Xbin_vector.data());
MnvH1D *h_Data_CryoVertex_X_RCut_Downstream_ConcaveCap = new MnvH1D("h_Data_CryoVertex_X_RCut_Downstream_ConcaveCap","h_Data_CryoVertex_X_RCut_Downstream_ConcaveCap", Vertex_Xbin_vector.size()-1, Vertex_Xbin_vector.data());



PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType> h_Data_CryoVertex_X_Track =
PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType>(TrackType_Category, "h_Data_CryoVertex_X_Track", Vertex_Xbin_vector ,"h_Data_CryoVertex_X_Track; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack> h_Data_CryoVertex_X_boolNTrack =
PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack>(boolNTrack_Category, "h_Data_CryoVertex_X_boolNTrack", Vertex_Xbin_vector ,"h_Data_CryoVertex_X_boolNTrack; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions> h_Data_CryoVertex_X_VertexOptions =
PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions>(VertexOptions_Category, "h_Data_CryoVertex_X_VertexOptions", Vertex_Xbin_vector ,"h_Data_CryoVertex_X_VertexOptions; [mm];Events");


MnvH1D *h_Data_CryoVertex_Y                       = new MnvH1D("h_Data_CryoVertex_Y",                      "h_Data_CryoVertex_Y",                       Vertex_Ybin_vector.size()-1, Vertex_Ybin_vector.data());
MnvH1D *h_Data_CryoVertex_Y_UpstreamCap           = new MnvH1D("h_Data_CryoVertex_Y_UpstreamCap",          "h_Data_CryoVertex_Y_UpstreamCap",           Vertex_Ybin_vector.size()-1, Vertex_Ybin_vector.data());
MnvH1D *h_Data_CryoVertex_Y_Barrel                = new MnvH1D("h_Data_CryoVertex_Y_Barrel",               "h_Data_CryoVertex_Y_Barrel",                Vertex_Ybin_vector.size()-1, Vertex_Ybin_vector.data());
MnvH1D *h_Data_CryoVertex_Y_DownstreamCap         = new MnvH1D("h_Data_CryoVertex_Y_DownstreamCap",        "h_Data_CryoVertex_Y_DownstreamCap",         Vertex_Ybin_vector.size()-1, Vertex_Ybin_vector.data());
MnvH1D *h_Data_CryoVertex_Y_Downstream_ConcaveCap = new MnvH1D("h_Data_CryoVertex_Y_Downstream_ConcaveCap","h_Data_CryoVertex_Y_Downstream_ConcaveCap", Vertex_Ybin_vector.size()-1, Vertex_Ybin_vector.data());

MnvH1D *h_Data_CryoVertex_Y_RCut                       = new MnvH1D("h_Data_CryoVertex_Y_RCut",                      "h_Data_CryoVertex_Y_RCut",                       Vertex_Ybin_vector.size()-1, Vertex_Ybin_vector.data());
MnvH1D *h_Data_CryoVertex_Y_RCut_UpstreamCap           = new MnvH1D("h_Data_CryoVertex_Y_RCut_UpstreamCap",          "h_Data_CryoVertex_Y_RCut_UpstreamCap",           Vertex_Ybin_vector.size()-1, Vertex_Ybin_vector.data());
MnvH1D *h_Data_CryoVertex_Y_RCut_Barrel                = new MnvH1D("h_Data_CryoVertex_Y_RCut_Barrel",               "h_Data_CryoVertex_Y_RCut_Barrel",                Vertex_Ybin_vector.size()-1, Vertex_Ybin_vector.data());
MnvH1D *h_Data_CryoVertex_Y_RCut_DownstreamCap         = new MnvH1D("h_Data_CryoVertex_Y_RCut_DownstreamCap",        "h_Data_CryoVertex_Y_RCut_DownstreamCap",         Vertex_Ybin_vector.size()-1, Vertex_Ybin_vector.data());
MnvH1D *h_Data_CryoVertex_Y_RCut_Downstream_ConcaveCap = new MnvH1D("h_Data_CryoVertex_Y_RCut_Downstream_ConcaveCap","h_Data_CryoVertex_Y_RCut_Downstream_ConcaveCap", Vertex_Ybin_vector.size()-1, Vertex_Ybin_vector.data());



PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType> h_Data_CryoVertex_Y_Track =
PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType>(TrackType_Category, "h_Data_CryoVertex_Y_Track", Vertex_Ybin_vector ,"h_Data_CryoVertex_Y_Track; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack> h_Data_CryoVertex_Y_boolNTrack =
PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack>(boolNTrack_Category, "h_Data_CryoVertex_Y_boolNTrack", Vertex_Ybin_vector ,"h_Data_CryoVertex_Y_boolNTrack; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions> h_Data_CryoVertex_Y_VertexOptions =
PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions>(VertexOptions_Category, "h_Data_CryoVertex_Y_VertexOptions", Vertex_Ybin_vector ,"h_Data_CryoVertex_Y_VertexOptions; [mm];Events");

MnvH1D *h_Data_CryoVertex_Z               =            new MnvH1D("h_Data_CryoVertex_Z",                      "h_Data_CryoVertex_Z",                       Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());
MnvH1D *h_Data_CryoVertex_Z_UpstreamCap   =            new MnvH1D("h_Data_CryoVertex_Z_UpstreamCap",          "h_Data_CryoVertex_Z_UpstreamCap",           Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());
MnvH1D *h_Data_CryoVertex_Z_Barrel        =            new MnvH1D("h_Data_CryoVertex_Z_Barrel",               "h_Data_CryoVertex_Z_Barrel",                Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());
MnvH1D *h_Data_CryoVertex_Z_DownstreamCap =            new MnvH1D("h_Data_CryoVertex_Z_DownstreamCap",        "h_Data_CryoVertex_Z_DownstreamCap",         Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());
MnvH1D *h_Data_CryoVertex_Z_Downstream_ConcaveCap =    new MnvH1D("h_Data_CryoVertex_Z_Downstream_ConcaveCap","h_Data_CryoVertex_Z_Downstream_ConcaveCap", Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());


MnvH1D *h_Data_CryoVertex_Z_RCut               =            new MnvH1D("h_Data_CryoVertex_Z_RCut",                      "h_Data_CryoVertex_Z_RCut",                       Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());
MnvH1D *h_Data_CryoVertex_Z_RCut_UpstreamCap   =            new MnvH1D("h_Data_CryoVertex_Z_RCut_UpstreamCap",          "h_Data_CryoVertex_Z_RCut_UpstreamCap",           Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());
MnvH1D *h_Data_CryoVertex_Z_RCut_Barrel        =            new MnvH1D("h_Data_CryoVertex_Z_RCut_Barrel",               "h_Data_CryoVertex_Z_RCut_Barrel",                Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());
MnvH1D *h_Data_CryoVertex_Z_RCut_DownstreamCap =            new MnvH1D("h_Data_CryoVertex_Z_RCut_DownstreamCap",        "h_Data_CryoVertex_Z_RCut_DownstreamCap",         Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());
MnvH1D *h_Data_CryoVertex_Z_RCut_Downstream_ConcaveCap =    new MnvH1D("h_Data_CryoVertex_Z_RCut_Downstream_ConcaveCap","h_Data_CryoVertex_Z_RCut_Downstream_ConcaveCap", Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());


PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType> h_Data_CryoVertex_Z_Track =
PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType>(TrackType_Category, "h_Data_CryoVertex_Z_Track", Vertex_Zbin_vector ,"h_Data_CryoVertex_Z_Track; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack> h_Data_CryoVertex_Z_boolNTrack =
PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack>(boolNTrack_Category, "h_Data_CryoVertex_Z_boolNTrack", Vertex_Zbin_vector ,"h_Data_CryoVertex_Z_boolNTrack; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions> h_Data_CryoVertex_Z_VertexOptions =
PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions>(VertexOptions_Category, "h_Data_CryoVertex_Z_VertexOptions", Vertex_Zbin_vector ,"h_Data_CryoVertex_Z_VertexOptions; [mm];Events");


MnvH1D *h_Data_CryoVertex_R                       =    new MnvH1D("h_Data_CryoVertex_R",                       "h_Data_CryoVertex_R",                       Vertex_Rbin_vector.size()-1, Vertex_Rbin_vector.data());
MnvH1D *h_Data_CryoVertex_R_UpstreamCap           =    new MnvH1D("h_Data_CryoVertex_R_UpstreamCap",           "h_Data_CryoVertex_R_UpstreamCap",           Vertex_Rbin_vector.size()-1, Vertex_Rbin_vector.data());
MnvH1D *h_Data_CryoVertex_R_Barrel                =    new MnvH1D("h_Data_CryoVertex_R_Barrel",                "h_Data_CryoVertex_R_Barrel",                Vertex_Rbin_vector.size()-1, Vertex_Rbin_vector.data());
MnvH1D *h_Data_CryoVertex_R_DownstreamCap         =    new MnvH1D("h_Data_CryoVertex_R_DownstreamCap",         "h_Data_CryoVertex_R_DownstreamCap",         Vertex_Rbin_vector.size()-1, Vertex_Rbin_vector.data());
MnvH1D *h_Data_CryoVertex_R_Downstream_ConcaveCap =    new MnvH1D("h_Data_CryoVertex_R_Downstream_ConcaveCap", "h_Data_CryoVertex_R_Downstream_ConcaveCap", Vertex_Rbin_vector.size()-1, Vertex_Rbin_vector.data());

MnvH1D *h_Data_CryoVertex_R_RCut                       =    new MnvH1D("h_Data_CryoVertex_R_RCut",                       "h_Data_CryoVertex_R_RCut",                       Vertex_Rbin_vector.size()-1, Vertex_Rbin_vector.data());
MnvH1D *h_Data_CryoVertex_R_RCut_UpstreamCap           =    new MnvH1D("h_Data_CryoVertex_R_RCut_UpstreamCap",           "h_Data_CryoVertex_R_RCut_UpstreamCap",           Vertex_Rbin_vector.size()-1, Vertex_Rbin_vector.data());
MnvH1D *h_Data_CryoVertex_R_RCut_Barrel                =    new MnvH1D("h_Data_CryoVertex_R_RCut_Barrel",                "h_Data_CryoVertex_R_RCut_Barrel",                Vertex_Rbin_vector.size()-1, Vertex_Rbin_vector.data());
MnvH1D *h_Data_CryoVertex_R_RCut_DownstreamCap         =    new MnvH1D("h_Data_CryoVertex_R_RCut_DownstreamCap",         "h_Data_CryoVertex_R_RCut_DownstreamCap",         Vertex_Rbin_vector.size()-1, Vertex_Rbin_vector.data());
MnvH1D *h_Data_CryoVertex_R_RCut_Downstream_ConcaveCap =    new MnvH1D("h_Data_CryoVertex_R_RCut_Downstream_ConcaveCap", "h_Data_CryoVertex_R_RCut_Downstream_ConcaveCap", Vertex_Rbin_vector.size()-1, Vertex_Rbin_vector.data());


PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType> h_Data_CryoVertex_R_Track =
PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType>(TrackType_Category, "h_Data_CryoVertex_R_Track", Vertex_Rbin_vector ,"h_Data_CryoVertex_R_Track; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack> h_Data_CryoVertex_R_boolNTrack =
PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack>(boolNTrack_Category, "h_Data_CryoVertex_R_boolNTrack", Vertex_Rbin_vector ,"h_Data_CryoVertex_R_boolNTrack; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions> h_Data_CryoVertex_R_VertexOptions =
PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions>(VertexOptions_Category, "h_Data_CryoVertex_R_VertexOptions", Vertex_Rbin_vector ,"h_Data_CryoVertex_R_VertexOptions; [mm];Events");

MnvH1D *h_Data_CryoVertexChiSqFit      =    new MnvH1D("h_Data_CryoVertexChiSqFit", "h_Data_CryoVertexChiSqFit", Vertex_ChiSqFit_vector.size()-1, Vertex_ChiSqFit_vector.data());
MnvH1D *h_Data_CryoVertexChiSqFit_long      =    new MnvH1D("h_Data_CryoVertexChiSqFit_long", "h_Data_CryoVertexChiSqFit_long", Vertex_ChiSqFit_vector.size()-1, Vertex_ChiSqFit_vector.data());
MnvH1D *h_Data_CryoVertexChiSqFit_otherlong      =    new MnvH1D("h_Data_CryoVertexChiSqFit_otherlong", "h_Data_CryoVertexChiSqFit_otherlong", Vertex_ChiSqFit_vector.size()-1, Vertex_ChiSqFit_vector.data());
MnvH1D *h_Data_CryoVertexChiSqFit_short      =    new MnvH1D("h_Data_CryoVertexChiSqFit_short", "h_Data_CryoVertexChiSqFit_short", Vertex_ChiSqFit_vector.size()-1, Vertex_ChiSqFit_vector.data());

PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType> h_Data_CryoVertexChiSqFit_Track =
PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType>(TrackType_Category, "h_Data_CryoVertexChiSqFit_Track", Vertex_ChiSqFit_vector ,"h_Data_CryoVertexChiSqFit_Track; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions> h_Data_CryoVertexChiSqFit_VertexOptions =
PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions>(VertexOptions_Category, "h_Data_CryoVertexChiSqFit_VertexOptions", Vertex_ChiSqFit_vector ,"h_Data_CryoVertexChiSqFit_VertexOptions; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack> h_Data_CryoVertexChiSqFit_boolNTrack =
PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack>(boolNTrack_Category, "h_Data_CryoVertexChiSqFit_boolNTrack", Vertex_ChiSqFit_vector ,"h_Data_CryoVertexChiSqFit_boolNTrack; [mm];Events");



PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType> h_Data_CryoVertexChiSqFitgreater10_Track =
PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType>(TrackType_Category, "h_Data_CryoVertexChiSqFitgreater10_Track", Vertex_ChiSqFit_vector ,"h_Data_CryoVertexChiSqFitgreater10_Track; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions> h_Data_CryoVertexChiSqFit_unDefinedTrk_VertexOptions =
PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions>(VertexOptions_Category, "h_Data_CryoVertexChiSqFit_unDefinedTrk_VertexOptions", Vertex_ChiSqFit_vector ,"h_Data_unDefinedTrk_CryoVertexChiSqFit_VertexOptions; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack> h_Data_CryoVertexChiSqFit_unDefinedTrk_boolNTrack =
PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack>(boolNTrack_Category, "h_Data_CryoVertexChiSqFit_unDefinedTrk_boolNTrack", Vertex_ChiSqFit_vector ,"h_Data_CryoVertexChiSqFit_unDefinedTrk_boolNTrack; [mm];Events");



int otherlongtrack=0;
/////////////
//2nd Trk Plots
/////////////
MnvH1D *h_Data_secTrk_DOCA                 =    new MnvH1D("h_Data_secTrk_DOCA", "h_Data_secTrk_DOCA", secTrk_DOCA_vector.size()-1, secTrk_DOCA_vector.data());
MnvH1D *h_Data_secTrk_DOCA_UpstreamCap            =    new MnvH1D("h_Data_secTrk_DOCA_UpstreamCap",           "h_Data_secTrk_DOCA_UpstreamCap", secTrk_DOCA_vector.size()-1, secTrk_DOCA_vector.data());
MnvH1D *h_Data_secTrk_DOCA_Barrel                 =    new MnvH1D("h_Data_secTrk_DOCA_Barrel",                "h_Data_secTrk_DOCA_Barrel", secTrk_DOCA_vector.size()-1, secTrk_DOCA_vector.data());
MnvH1D *h_Data_secTrk_DOCA_DownstreamCap          =    new MnvH1D("h_Data_secTrk_DOCA_DownstreamCap",         "h_Data_secTrk_DOCA_DownstreamCap", secTrk_DOCA_vector.size()-1, secTrk_DOCA_vector.data());
MnvH1D *h_Data_secTrk_DOCA_Downstream_ConcaveCap  =   new MnvH1D("h_Data_secTrk_DOCA_Downstream_ConcaveCap", "h_Data_secTrk_DOCA_Downstream_ConcaveCap", secTrk_DOCA_vector.size()-1, secTrk_DOCA_vector.data());


MnvH1D *h_Data_secTrk_Pathlength                        =    new MnvH1D("h_Data_secTrk_Pathlength",                       "h_Data_secTrk_Pathlength", secTrkPathway_vector.size()-1, secTrkPathway_vector.data());
MnvH1D *h_Data_secTrk_Pathlength_UpstreamCap            =    new MnvH1D("h_Data_secTrk_Pathlength_UpstreamCap",           "h_Data_secTrk_Pathlength_UpstreamCap", secTrkPathway_vector.size()-1, secTrkPathway_vector.data());
MnvH1D *h_Data_secTrk_Pathlength_Barrel                 =    new MnvH1D("h_Data_secTrk_Pathlength_Barrel",                "h_Data_secTrk_Pathlength_Barrel", secTrkPathway_vector.size()-1, secTrkPathway_vector.data());
MnvH1D *h_Data_secTrk_Pathlength_DownstreamCap          =    new MnvH1D("h_Data_secTrk_Pathlength_DownstreamCap",         "h_Data_secTrk_Pathlength_DownstreamCap", secTrkPathway_vector.size()-1, secTrkPathway_vector.data());
MnvH1D *h_Data_secTrk_Pathlength_Downstream_ConcaveCap  =    new MnvH1D("h_Data_secTrk_Pathlength_Downstream_ConcaveCap", "h_Data_secTrk_Pathlength_Downstream_ConcaveCap", secTrkPathway_vector.size()-1, secTrkPathway_vector.data());

MnvH1D *h_Data_secTrk_Length                         =    new MnvH1D("h_Data_secTrk_Length",                       "h_Data_secTrk_Length", Recoil_track_length_vector.size()-1, Recoil_track_length_vector.data());
MnvH1D *h_Data_secTrk_Length_UpstreamCap             =    new MnvH1D("h_Data_secTrk_Length_UpstreamCap",           "h_Data_secTrk_Length_UpstreamCap", Recoil_track_length_vector.size()-1, Recoil_track_length_vector.data());
MnvH1D *h_Data_secTrk_Length_Barrel                  =    new MnvH1D("h_Data_secTrk_Length_Barrel",                "h_Data_secTrk_Length_Barrel", Recoil_track_length_vector.size()-1, Recoil_track_length_vector.data());
MnvH1D *h_Data_secTrk_Length_DownstreamCap           =    new MnvH1D("h_Data_secTrk_Length_DownstreamCap",         "h_Data_secTrk_Length_DownstreamCap", Recoil_track_length_vector.size()-1, Recoil_track_length_vector.data());
MnvH1D *h_Data_secTrk_Length_Downstream_ConcaveCap   =    new MnvH1D("h_Data_secTrk_Length_Downstream_ConcaveCap", "h_Data_secTrk_Length_Downstream_ConcaveCap", Recoil_track_length_vector.size()-1, Recoil_track_length_vector.data());





MnvH1D *h_Data_secTrk_Energy               =    new MnvH1D("h_Data_secTrk_Energy", "h_Data_secTrk_Energy", secTrkEbin_vector.size()-1, secTrkEbin_vector.data());
MnvH1D *h_Data_secTrk_MidAngle             =    new MnvH1D("h_Data_secTrk_MidAngle", "h_Data_secTrk_MidAngle", secTrkThetamid_vector.size()-1, secTrkThetamid_vector.data());
MnvH1D *h_Data_secTrk_Openangle            =    new MnvH1D("h_Data_secTrk_Openangle", "h_Data_secTrk_Openangle", secTrkThetamid_vector.size()-1, secTrkThetamid_vector.data());


MnvH1D *h_Data_secTrk_Length_longtracker          =    new MnvH1D("h_Data_secTrk_Length_longtracker", "h_Data_secTrk_Length_longtracker", Recoil_track_length_vector.size()-1, Recoil_track_length_vector.data());
MnvH1D *h_Data_secTrk_Length_shorttracker          =    new MnvH1D("h_Data_secTrk_Length_shorttracker", "h_Data_secTrk_Length_shorttracker", Recoil_track_length_vector.size()-1, Recoil_track_length_vector.data());
MnvH1D *h_Data_secTrk_Length_otherlongtracker          =    new MnvH1D("h_Data_secTrk_Length_otherlongtracker", "h_Data_secTrk_Length_otherlongtracker", Recoil_track_length_vector.size()-1, Recoil_track_length_vector.data());



///////////
///Vetowall
///////////

MnvH1D *h_Data_secTrk_FirstNodeX = new MnvH1D("h_Data_secTrk_FirstNodeX","h_Data_secTrk_FirstNodeX",secTrk_StartNode_X_vector.size()-1,secTrk_StartNode_X_vector.data());
MnvH1D *h_Data_secTrk_FirstNodeY = new MnvH1D("h_Data_secTrk_FirstNodeY","h_Data_secTrk_FirstNodeY",secTrk_StartNode_Y_vector.size()-1,secTrk_StartNode_Y_vector.data());
MnvH1D *h_Data_secTrk_FirstNodeZ = new MnvH1D("h_Data_secTrk_FirstNodeZ","h_Data_secTrk_FirstNodeZ",secTrk_StartNode_Z_vector.size()-1,secTrk_StartNode_Z_vector.data());
MnvH1D *h_Data_secTrk_LastNodeX = new MnvH1D("h_Data_secTrk_LastNodeX","h_Data_secTrk_LastNodeX",secTrk_LastNode_X_vector.size()-1,secTrk_LastNode_X_vector.data());
MnvH1D *h_Data_secTrk_LastNodeY = new MnvH1D("h_Data_secTrk_LastNodeY","h_Data_secTrk_LastNodeY",secTrk_LastNode_Y_vector.size()-1,secTrk_LastNode_Y_vector.data());
MnvH1D *h_Data_secTrk_LastNodeZ = new MnvH1D("h_Data_secTrk_LastNodeZ","h_Data_secTrk_LastNodeZ",secTrk_LastNode_Z_vector.size()-1,secTrk_LastNode_Z_vector.data());
///////////
///Vetowall
///////////

MnvH2D *h2_Data_R_Z= new MnvH2D("h2_Data_R_Z","h2_Data_R_Z",Vertex_Rbin_vector.size()-1, Vertex_Rbin_vector.data(), Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());
MnvH2D *h2_Data_X_Z= new MnvH2D("h2_Data_X_Z","h2_Data_X_Z",Vertex_Xbin_vector.size()-1, Vertex_Xbin_vector.data(), Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());
MnvH2D *h2_Data_Y_Z= new MnvH2D("h2_Data_Y_Z","h2_Data_Y_Z",Vertex_Ybin_vector.size()-1, Vertex_Ybin_vector.data(), Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());


MnvH2D *h2_Data_secTrkpathLength_R= new MnvH2D("h2_Data_secTrkpathLength_R","h2_Data_secTrkpathLength_R",secTrkPathway_vector.size()-1, secTrkPathway_vector.data(), Vertex_Rbin_vector.size()-1, Vertex_Rbin_vector.data());
MnvH2D *h2_Data_secTrkpathLength_Z= new MnvH2D("h2_Data_secTrkpathLength_Z","h2_Data_secTrkpathLength_Z",secTrkPathway_vector.size()-1, secTrkPathway_vector.data(), Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());

MnvH2D *h2_Data_secTrkLength_R= new MnvH2D("h2_Data_secTrkLength_R","h2_Data_secTrkLength_R",Recoil_track_length_vector.size()-1, Recoil_track_length_vector.data(), Vertex_Rbin_vector.size()-1, Vertex_Rbin_vector.data());
MnvH2D *h2_Data_secTrkLength_Z= new MnvH2D("h2_Data_secTrkLength_Z","h2_Data_secTrkLength_Z",Recoil_track_length_vector.size()-1, Recoil_track_length_vector.data(), Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());

MnvH2D *h2_Data_FirstZnode_2ndTrklength    =    new MnvH2D("h2_Data_FirstZnode_2ndTrklength", "h2_Data_FirstZnode_2ndTrklength",  secTrk_StartNode_Z_vector.size()-1, secTrk_StartNode_Z_vector.data(),Recoil_track_length_vector.size()-1,  Recoil_track_length_vector.data()  );
MnvH2D *h2_Data_LastZnode_2ndTrklength    =    new MnvH2D("h2_Data_LastZnode_2ndTrklength", "h2_Data_LastZnode_2ndTrklength",   secTrk_LastNode_Z_vector.size()-1, secTrk_LastNode_Z_vector.data(),Recoil_track_length_vector.size()-1,  Recoil_track_length_vector.data()  );

std::vector<double> bigAngle_bins{0.0,15.0,30.0,45.0,60.0};
MnvH2D *h2_Data_2ndtrkLength_Angle    =    new MnvH2D("h2_Data_2ndtrkLength_Angle", "h2_Data_2ndtrkLength_Angle", Recoil_track_length_vector.size()-1, Recoil_track_length_vector.data(), bigAngle_bins.size()-1, bigAngle_bins.data());

std::vector<double> bigAngle_bins_finner{0.0, 5.0, 10.0, 15.0, 20.0, 25.0, 30.0, 45.0, 60.0};
MnvH2D *h2_Data_2ndtrkLength_finerAngle    =    new MnvH2D("h2_Data_2ndtrkLength_finerAngle", "h2_Data_2ndtrkLength_finerAngle", Recoil_track_length_vector.size()-1, Recoil_track_length_vector.data(), bigAngle_bins_finner.size()-1, bigAngle_bins_finner.data());



  EventCount_RECO EventCounter_data;


  std::cout << "size of vector " << kCutsVector.size()<<std::endl;
  for (auto cut : kCutsVector){
  std::cout<<" count= "<<cut<<std::endl;
  EventCounter_data[cut]=0.0;

  //std::cout << GetCutName( cut) << "  " << EventCounter_dataFull[cut] <<" " <<EventCounter_MCFull[cut]<<std::endl;

  }


  ProcInfo_t procInfo;
  gSystem->GetProcInfo(&procInfo);
  std::cout << "Mem0: " << procInfo.fMemResident << "\n";


  HeliumPlayListInfo Playlist_Info(playlist);
  std::cout<<"Working with Playlist =  "<<  Playlist_Info.GetPlaylistname()<<std::endl;


  gSystem->GetProcInfo(&procInfo);
  std::cout << "Mem1: " << procInfo.fMemResident << "\n";

  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"Data LOOP  "<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

RECO_Cut_Map CountMap_RECO_Data;//
RECO_Cut_Map CountMap_RECO_Data_fiduical;//
FillingRecoCountingMap(kCutsVector, CountMap_RECO_Data);

FillingRecoCountingMap(kCutsVector_Fiduical, CountMap_RECO_Data_fiduical);
//////////////////////////////////////////////////////////////////////////
// Data Loop ME_playlist_1A_BranchesADDED
//////////////////////////////////////////////////////////////////////////
gSystem->GetProcInfo(&procInfo);
std::cout<<"On Playlist: "<<Playlist_Info.GetPlaylistname() << "Mem2: " << procInfo.fMemResident << "\n";
//auto Playlist_txtFILEPath = GetPlaylist_txtFILE_path("1A_BranchesADDED",  isNOT_mc );
auto Playlist_txtFILEPath = GetPlaylist_txtFILE_path(PlayList_iterator, isNOT_mc );

std::cout<<"Pathway of Root files = "<< Playlist_txtFILEPath<<std::endl;
//PlotUtils::ChainWrapper* chw_Data  = makeChainWrapperPtr("../playlists/Data_Playlist/ME_1A_DATA.txt", "Muon");
//PlotUtils::ChainWrapper* chw_Data  = makeChainWrapperPtr("../playlists/Data_Playlist/ME_1P_DATA.txt", "Muon");
PlotUtils::ChainWrapper* chw_Data  = makeChainWrapperPtr(Playlist_txtFILEPath.c_str(), "HeAnaTupleTool");
PlotUtils::ChainWrapper* datachainPOT = makeChainWrapperPtr(Playlist_txtFILEPath.c_str(), "Meta");
//std::map< std::string, std::vector<HeliumCVUniverse*> > data_error_bands = GetErrorBands(chw_Data);
auto dataPOT = 1.0;//GetPOT(datachainPOT);
//std::cout << "POT of MC = "<< dataPOT<<std::endl;
HeliumCVUniverse* dataEvt = new HeliumCVUniverse(chw_Data);
//const std::string RootName = GetPlaylist_ROOT_path("1G_vertexweightto10mm", isNOT_mc );
auto intial_playlist = GetPlaylist_InitialName(PlayList_iterator);
const std::string RootName = GetPlaylist_ROOT_path(intial_playlist, isNOT_mc );

std::cout << "rootName =" << RootName<<std::endl;
//MinervaUniverse::SetPlaylist_AGAIN(playlist);
//MinervaUniverse::SetPlaylist(playlist);
//double POTFULLDATA = dataEvt->GetBatchPOT();

//std::cout << "POT = " << dataPOT<<std::endl;
//HeliumCVUniverse* universe = data_error_bands["CV"][0];
std::cout << "*** Starting Data Loop ***" << std::endl;

for(Long64_t ievent=0; ievent < chw_Data->GetEntries(); ++ievent){

  if(ievent%10000==0) std::cout << (ievent/1000) << " k Events " << std::endl;
  dataEvt->SetEntry(ievent);

  EventCounter(*dataEvt, kCutsVector, EventCounter_data, isNOT_mc, Playlist_Info );


  if(PassesCutsRECOData(*dataEvt,  isNOT_mc , kCutsVector, CountMap_RECO_Data) ){
    //std::cout << "passed Cuts" << std::endl;
    double zvertex = dataEvt->GetVertex_z();
    double xvertex = dataEvt->GetVertex_x();
    double rvertex = dataEvt->GetVertex_r();
    //if(IsInFiducalVolumeFromtheInnerEdge( rvertex, zvertex, 50.0  )==false) continue;
    double Theta = dataEvt->GetThetamu();
    double Pmu =   dataEvt->GetPmu()/1000;
    double Emu =   dataEvt->GetEmu()*.001;
    double pseduo_r = dataEvt->pseudorapidity_muon();
    double pseduo_theta = 2 * atan(exp(-pseduo_r)) * TMath::RadToDeg();
    double phi = dataEvt->GetPhimu();

    double px = Pmu * std::sin(Theta) * std::cos(phi);
    double py = Pmu * std::sin(Theta) * std::sin(phi);

    double PT = sqrt(px*px + py*py);
    double PZ = Pmu*std::cos(Theta);

    auto trackType = dataEvt->GetTrackType();
    CryoTank_REGIONS CryoTankRegion_type =   FourRegion_of_CryoTank(zvertex);


    VertexOptions VertexOption_type = dataEvt->GetVertex_optionType();
    boolNTrack boolNTrack_Type = dataEvt->GetVertex_boolNTrack();
    int secondTrk = dataEvt->Getindex2ndTrackhighestKE();
    double TrackLength = dataEvt->GetNonmuTrkLength(secondTrk);

    double distance_upstreamCap = DistanceFromUpStreamBulge(zvertex , rvertex);
    double distance_DownstreamCap = DistanceFromDownStreamBulge(zvertex , rvertex);
    double Theta_Deg = Theta*TMath::RadToDeg();
    double Distance_nearestWall = RECO_Distance_to_innerTank(*dataEvt);
    double secTrk_DOCA = dataEvt->GetNonmuDOCA(secondTrk);

    h_Data_MuonE->Fill(Emu, 1.0);
    h_Data_MuonPZ->Fill(PZ, 1.0);
    h_Data_MuonPT->Fill(PT, 1.0);
    h_Data_MuonTheta->Fill(Theta_Deg,1.0);
    h_Data_Muon_pseudorapidity->Fill(pseduo_r,1.0);
    h_Data_Muon_pseudorapidity_angle->Fill(pseduo_theta,1.0);
    h_Data_Muon_rapidity->Fill(dataEvt->rapidity_muon(),1.0);
    h_Data_Distance_to_InnerTank->Fill(Distance_nearestWall,1.0);

    h_Data_MuonDOCA->Fill(dataEvt->GetDOCAmu(),1.0);
    h_Data_secTrk_DOCA->Fill(secTrk_DOCA,1.0);
    h_Data_secTrk_Pathlength->Fill(TrackLength,1.0);
    h_Data_secTrk_Length->Fill(dataEvt->GetNonmuTrkLength_InMinerva_Incm(secondTrk),1.0);

    h_Data_Distance_to_UpstreamCap->Fill(distance_upstreamCap,1.0);
    h_Data_Distance_to_DownstreamCap->Fill(distance_DownstreamCap,1.0);




      if(Cylindrical_CutAboutZero(*dataEvt)==true){
        h_Data_CryoVertex_Z_RCut->Fill(dataEvt->GetVertex_z(),1.0);
        h_Data_CryoVertex_X_RCut->Fill(dataEvt->GetVertex_x(),1.0);
        h_Data_CryoVertex_Y_RCut->Fill(dataEvt->GetVertex_y(),1.0);
        h_Data_CryoVertex_R_RCut->Fill(dataEvt->GetVertex_r(),1.0);
        h_Data_Distance_to_UpstreamCap_RCut->Fill(distance_upstreamCap,1.0);
        h_Data_Distance_to_DownstreamCap_RCut->Fill(distance_DownstreamCap,1.0);
      }

    //std::cout << "CyroTank Z" << std::endl;
    if(CryoTankRegion_type==kUpstream_head)
    {
      h_Data_CryoVertex_X_UpstreamCap->Fill(dataEvt->GetVertex_x(),1.0);
      h_Data_CryoVertex_Y_UpstreamCap->Fill(dataEvt->GetVertex_y(),1.0);
      h_Data_CryoVertex_Z_UpstreamCap->Fill(dataEvt->GetVertex_z(),1.0);
      h_Data_CryoVertex_R_UpstreamCap->Fill(dataEvt->GetVertex_r(),1.0);
      h_Data_Distance_to_InnerTank_UpstreamCap->Fill(distance_upstreamCap,1.0);
      h_Data_Distance_to_InnerTank_Caps_UpstreamCap->Fill(distance_DownstreamCap,1.0);
      h_Data_MuonE_UpstreamCap->Fill(Emu, 1.0);
      h_Data_MuonPZ_UpstreamCap->Fill(PZ, 1.0);
      h_Data_MuonPT_UpstreamCap->Fill(PT, 1.0);
      h_Data_MuonTheta_UpstreamCap->Fill(Theta_Deg,1.0);

      h_Data_MuonDOCA_UpstreamCap->Fill(dataEvt->GetDOCAmu(),1.0);
      h_Data_secTrk_DOCA_UpstreamCap->Fill(secTrk_DOCA,1.0);
      h_Data_secTrk_Pathlength_UpstreamCap->Fill(TrackLength,1.0);
      h_Data_secTrk_Length_UpstreamCap->Fill(dataEvt->GetNonmuTrkLength_InMinerva_Incm(secondTrk),1.0);

      h_Data_Distance_to_UpstreamCap_UpstreamCap->Fill(distance_upstreamCap,1.0);
      h_Data_Distance_to_DownstreamCap_UpstreamCap->Fill(distance_DownstreamCap,1.0);

      if(Cylindrical_CutAboutZero(*dataEvt)==true){
        h_Data_CryoVertex_Z_RCut_UpstreamCap->Fill(dataEvt->GetVertex_z(), 1.0);
        h_Data_Distance_to_UpstreamCap_RCut_UpstreamCap->Fill(distance_upstreamCap,1.0);
        h_Data_Distance_to_DownstreamCap_RCut_UpstreamCap->Fill(distance_DownstreamCap,1.0);
        h_Data_CryoVertex_X_RCut_UpstreamCap->Fill(dataEvt->GetVertex_x(),1.0);
        h_Data_CryoVertex_Y_RCut_UpstreamCap->Fill(dataEvt->GetVertex_y(),1.0);
        h_Data_CryoVertex_R_RCut_UpstreamCap->Fill(dataEvt->GetVertex_r(),1.0);

      }


    }
    else if(CryoTankRegion_type==kCenter)
    {
      h_Data_CryoVertex_X_Barrel->Fill(dataEvt->GetVertex_x(),1.0);
      h_Data_CryoVertex_Y_Barrel->Fill(dataEvt->GetVertex_y(),1.0);
      h_Data_CryoVertex_Z_Barrel->Fill(dataEvt->GetVertex_z(),1.0);
      h_Data_CryoVertex_R_Barrel->Fill(dataEvt->GetVertex_r(),1.0);
      h_Data_Distance_to_InnerTank_Barrel->Fill(Distance_nearestWall,1.0);
      h_Data_Distance_to_InnerTank_Barrel_Barrel->Fill(Distance_nearestWall,1.0);
      h_Data_MuonE_Barrel->Fill(Emu, 1.0);
      h_Data_MuonPZ_Barrel->Fill(PZ, 1.0);
      h_Data_MuonPT_Barrel->Fill(PT, 1.0);
      h_Data_MuonTheta_Barrel->Fill(Theta_Deg,1.0);

      h_Data_MuonDOCA_Barrel->Fill(dataEvt->GetDOCAmu(),1.0);
      h_Data_secTrk_DOCA_Barrel->Fill(secTrk_DOCA,1.0);
      h_Data_secTrk_Pathlength_Barrel->Fill(TrackLength,1.0);
      h_Data_secTrk_Length_Barrel->Fill(dataEvt->GetNonmuTrkLength_InMinerva_Incm(secondTrk),1.0);

      h_Data_Distance_to_UpstreamCap_Barrel->Fill(distance_upstreamCap,1.0);
      h_Data_Distance_to_DownstreamCap_Barrel->Fill(distance_DownstreamCap,1.0);

      if(Cylindrical_CutAboutZero(*dataEvt)==true){
        h_Data_CryoVertex_Z_RCut_Barrel->Fill(dataEvt->GetVertex_z(), 1.0);
        h_Data_Distance_to_UpstreamCap_RCut_Barrel->Fill(distance_upstreamCap,1.0);
        h_Data_Distance_to_DownstreamCap_RCut_Barrel->Fill(distance_DownstreamCap,1.0);
        h_Data_CryoVertex_X_RCut_Barrel->Fill(dataEvt->GetVertex_x(),1.0);
        h_Data_CryoVertex_Y_RCut_Barrel->Fill(dataEvt->GetVertex_y(),1.0);
        h_Data_CryoVertex_R_RCut_Barrel->Fill(dataEvt->GetVertex_r(),1.0);

      }




    }
    else if(CryoTankRegion_type==kDownstream_head)
    {
      h_Data_CryoVertex_X_DownstreamCap->Fill(dataEvt->GetVertex_x(),1.0);
      h_Data_CryoVertex_Y_DownstreamCap->Fill(dataEvt->GetVertex_y(),1.0);
      h_Data_CryoVertex_Z_DownstreamCap->Fill(dataEvt->GetVertex_z(),1.0);
      h_Data_CryoVertex_R_DownstreamCap->Fill(dataEvt->GetVertex_r(),1.0);
      h_Data_Distance_to_InnerTank_DownstreamCap->Fill(Distance_nearestWall,1.0);
      h_Data_Distance_to_InnerTank_Caps_DownstreamCap->Fill(Distance_nearestWall,1.0);
      h_Data_MuonE_DownstreamCap->Fill(Emu, 1.0);
      h_Data_MuonPZ_DownstreamCap->Fill(PZ, 1.0);
      h_Data_MuonPT_DownstreamCap->Fill(PT, 1.0);
      h_Data_MuonTheta_DownstreamCap->Fill(Theta_Deg,1.0);

      h_Data_MuonDOCA_DownstreamCap->Fill(dataEvt->GetDOCAmu(),1.0);
      h_Data_secTrk_DOCA_DownstreamCap->Fill(secTrk_DOCA,1.0);
      h_Data_secTrk_Pathlength_DownstreamCap->Fill(TrackLength,1.0);
      h_Data_secTrk_Length_DownstreamCap->Fill(dataEvt->GetNonmuTrkLength_InMinerva_Incm(secondTrk),1.0);

      h_Data_Distance_to_UpstreamCap_DownstreamCap->Fill(distance_upstreamCap,1.0);
      h_Data_Distance_to_DownstreamCap_DownstreamCap->Fill(distance_DownstreamCap,1.0);

      if(Cylindrical_CutAboutZero(*dataEvt)==true){
        h_Data_CryoVertex_Z_RCut_DownstreamCap->Fill(dataEvt->GetVertex_z(), 1.0);
        h_Data_Distance_to_UpstreamCap_RCut_DownstreamCap->Fill(distance_upstreamCap,1.0);
        h_Data_Distance_to_DownstreamCap_RCut_DownstreamCap->Fill(distance_DownstreamCap,1.0);
        h_Data_CryoVertex_X_RCut_DownstreamCap->Fill(dataEvt->GetVertex_x(),1.0);
        h_Data_CryoVertex_Y_RCut_DownstreamCap->Fill(dataEvt->GetVertex_y(),1.0);
        h_Data_CryoVertex_R_RCut_DownstreamCap->Fill(dataEvt->GetVertex_r(),1.0);
      }



    }
    else if(CryoTankRegion_type==kDownstream_ConcaveCap)
    {
      h_Data_CryoVertex_X_Downstream_ConcaveCap->Fill(dataEvt->GetVertex_x(),1.0);
      h_Data_CryoVertex_Y_Downstream_ConcaveCap->Fill(dataEvt->GetVertex_y(),1.0);
      h_Data_CryoVertex_Z_Downstream_ConcaveCap->Fill(dataEvt->GetVertex_z(),1.0);
      h_Data_CryoVertex_R_Downstream_ConcaveCap->Fill(dataEvt->GetVertex_r(),1.0);
      h_Data_Distance_to_InnerTank_Downstream_ConcaveCap->Fill(Distance_nearestWall,1.0);
      h_Data_Distance_to_InnerTank_Caps_Downstream_ConcaveCap->Fill(Distance_nearestWall,1.0);
      h_Data_MuonE_Downstream_ConcaveCap->Fill(Emu, 1.0);
      h_Data_MuonPZ_Downstream_ConcaveCap->Fill(PZ, 1.0);
      h_Data_MuonPT_Downstream_ConcaveCap->Fill(PT, 1.0);
      h_Data_MuonTheta_Downstream_ConcaveCap->Fill(Theta_Deg,1.0);

      h_Data_MuonDOCA_Downstream_ConcaveCap->Fill(dataEvt->GetDOCAmu(),1.0);
      h_Data_secTrk_DOCA_Downstream_ConcaveCap->Fill(secTrk_DOCA,1.0);
      h_Data_secTrk_Pathlength_Downstream_ConcaveCap->Fill(TrackLength,1.0);
      h_Data_secTrk_Length_Downstream_ConcaveCap->Fill(dataEvt->GetNonmuTrkLength_InMinerva_Incm(secondTrk),1.0);

      h_Data_Distance_to_UpstreamCap_Downstream_ConcaveCap->Fill(distance_upstreamCap,1.0);
      h_Data_Distance_to_DownstreamCap_Downstream_ConcaveCap->Fill(distance_DownstreamCap,1.0);

      if(Cylindrical_CutAboutZero(*dataEvt)==true){
        h_Data_CryoVertex_Z_RCut_Downstream_ConcaveCap->Fill(dataEvt->GetVertex_z(), 1.0);
        h_Data_Distance_to_UpstreamCap_RCut_Downstream_ConcaveCap->Fill(distance_upstreamCap,1.0);
        h_Data_Distance_to_DownstreamCap_RCut_Downstream_ConcaveCap->Fill(distance_DownstreamCap,1.0);
        h_Data_CryoVertex_X_RCut_Downstream_ConcaveCap->Fill(dataEvt->GetVertex_x(),1.0);
        h_Data_CryoVertex_Y_RCut_Downstream_ConcaveCap->Fill(dataEvt->GetVertex_y(),1.0);
        h_Data_CryoVertex_R_RCut_Downstream_ConcaveCap->Fill(dataEvt->GetVertex_r(),1.0);
      }

    }
    else{std::cout<<"ABSURDITY !! Event Failed to be in a  CryoRegion: Something Wrong"<<std::endl; assert(false);}


////////////////////////////////////////////

    h_Data_CryoVertex_X->Fill(dataEvt->GetVertex_x(),1.0);
    h_Data_CryoVertex_X_Track.GetComponentHist(trackType)->Fill(dataEvt->GetVertex_x(), 1.0);
    h_Data_CryoVertex_X_boolNTrack.GetComponentHist(boolNTrack_Type)->Fill(dataEvt->GetVertex_x(), 1.0);
    h_Data_CryoVertex_X_VertexOptions.GetComponentHist(VertexOption_type)->Fill(dataEvt->GetVertex_x(), 1.0);


    h_Data_CryoVertex_Y->Fill(dataEvt->GetVertex_y(),1.0);
    h_Data_CryoVertex_Y_Track.GetComponentHist(trackType)->Fill(dataEvt->GetVertex_y(), 1.0);
    h_Data_CryoVertex_Y_boolNTrack.GetComponentHist(boolNTrack_Type)->Fill(dataEvt->GetVertex_y(), 1.0);
    h_Data_CryoVertex_Y_VertexOptions.GetComponentHist(VertexOption_type)->Fill(dataEvt->GetVertex_y(), 1.0);


    h_Data_CryoVertex_Z->Fill(dataEvt->GetVertex_z(),1.0);
    h_Data_CryoVertex_Z_Track.GetComponentHist(trackType)->Fill(dataEvt->GetVertex_z(), 1.0);
    h_Data_CryoVertex_Z_boolNTrack.GetComponentHist(boolNTrack_Type)->Fill(dataEvt->GetVertex_z(), 1.0);
    h_Data_CryoVertex_Z_VertexOptions.GetComponentHist(VertexOption_type)->Fill(dataEvt->GetVertex_z(), 1.0);


    h_Data_CryoVertex_R->Fill(dataEvt->GetVertex_r(),1.0);
    h_Data_CryoVertex_R_Track.GetComponentHist(trackType)->Fill(dataEvt->GetVertex_r(), 1.0);
    h_Data_CryoVertex_R_boolNTrack.GetComponentHist(boolNTrack_Type)->Fill(dataEvt->GetVertex_r(), 1.0);
    h_Data_CryoVertex_R_VertexOptions.GetComponentHist(VertexOption_type)->Fill(dataEvt->GetVertex_r(), 1.0);
    h_Data_CryoVertexChiSqFit->Fill(dataEvt->GetVertexChiSqrFit(),1.0);


    double chisqt = dataEvt->GetVertexChiSqrFit();


      h_Data_CryoVertexChiSqFit_Track.GetComponentHist(trackType)->Fill(chisqt, 1.0);

      h_Data_CryoVertexChiSqFit_VertexOptions.GetComponentHist(VertexOption_type)->Fill(chisqt, 1.0);
      h_Data_CryoVertexChiSqFit_boolNTrack.GetComponentHist(boolNTrack_Type)->Fill(chisqt, 1.0);
      if(chisqt > 10){ h_Data_CryoVertexChiSqFitgreater10_Track.GetComponentHist(trackType)->Fill(chisqt, 1.0);}


          if(kLong==trackType)
          {  h_Data_secTrk_Length_longtracker->Fill(dataEvt->GetNonmuTrkLength_InMinerva_Incm(secondTrk),1.0);
            h_Data_CryoVertexChiSqFit_long->Fill(dataEvt->GetVertexChiSqrFit(),1.0);
          }
          else if (kShort==trackType){
            h_Data_CryoVertexChiSqFit_short->Fill(dataEvt->GetVertexChiSqrFit(),1.0);
            h_Data_secTrk_Length_shorttracker->Fill(dataEvt->GetNonmuTrkLength_InMinerva_Incm(secondTrk),1.0);

          }
          else if (kOtherLong==trackType){
            h_Data_CryoVertexChiSqFit_otherlong->Fill(dataEvt->GetVertexChiSqrFit(),1.0);
            h_Data_secTrk_Length_otherlongtracker->Fill(dataEvt->GetNonmuTrkLength_InMinerva_Incm(secondTrk),1.0);

          }
          else if (kNotdefinedTrack==trackType){num_NotDefinedTracks++;

            h_Data_CryoVertexChiSqFit_unDefinedTrk_VertexOptions.GetComponentHist(VertexOption_type)->Fill(chisqt, 1.0);
            h_Data_CryoVertexChiSqFit_unDefinedTrk_boolNTrack.GetComponentHist(boolNTrack_Type)->Fill(chisqt, 1.0);

            Trajector_DATA stuct_data = dataEvt->Return_Trajector_DATA_struct();
            Trajector_DATA_length_vector.push_back(stuct_data);

          }

    double recoiltheta = dataEvt->GetNonmuTrkAngleWRTbeamMID(secondTrk);
    h_Data_secTrk_Energy->Fill(dataEvt->GetNonmuTrkE(secondTrk)*Mev_to_GeV,1.0);
    h_Data_secTrk_MidAngle ->Fill(dataEvt->GetNonmuTrkAngleWRTbeamMID(secondTrk),1.0);
    h_Data_secTrk_Openangle->Fill(dataEvt->GetNonmuTrkAngleWRTmu(secondTrk),1.0);


    //auto tracktype = dataEvt->GetTrackType();


    h2_Data_R_Z->Fill(dataEvt->GetVertex_r(),dataEvt->GetVertex_z(),1.0);
    h2_Data_X_Z->Fill(dataEvt->GetVertex_x(),dataEvt->GetVertex_z(),1.0);
    h2_Data_Y_Z->Fill(dataEvt->GetVertex_y(),dataEvt->GetVertex_z(),1.0);

    h2_Data_secTrkpathLength_R->Fill(TrackLength,dataEvt->GetVertex_r(),1.0);
    h2_Data_secTrkpathLength_Z->Fill(TrackLength,dataEvt->GetVertex_z(),1.0);

    h2_Data_secTrkLength_R->Fill(TrackLength,dataEvt->GetVertex_r(),1.0);
    h2_Data_secTrkLength_Z->Fill(TrackLength,dataEvt->GetVertex_z(),1.0);
    h2_Data_2ndtrkLength_Angle->Fill(TrackLength,dataEvt->GetNonmuTrkAngleWRTbeamMID(secondTrk),1.0);
    h2_Data_2ndtrkLength_finerAngle->Fill(TrackLength,dataEvt->GetNonmuTrkAngleWRTbeamMID(secondTrk),1.0);

    h2_Data_FirstZnode_2ndTrklength->Fill(dataEvt->GetFirstNodeZ(secondTrk), TrackLength, 1.0);
    h2_Data_LastZnode_2ndTrklength->Fill(dataEvt->GetLastNodeZ(secondTrk), TrackLength, 1.0);
    h_Data_Tracksize->Fill(dataEvt->GetTracksize(),1.0);
    h_Data_Distance_to_InnerTank_Fidiucal->Fill(Distance_nearestWall,1.0);


    CryoTank_REGIONS CryoTankRegion14 = CryoZRegionBreakdown14(dataEvt->GetVertex_z());

    h_Data_MuonE_CryoRegion14.GetComponentHist(CryoTankRegion14)->Fill( Emu, 1.0);
    h_Data_MuonPT_CryoRegion14.GetComponentHist(CryoTankRegion14)->Fill(PT, 1.0);
    h_Data_MuonPZ_CryoRegion14.GetComponentHist(CryoTankRegion14)->Fill(PZ, 1.0);
    h_Data_MuonTheta_CryoRegion14.GetComponentHist(CryoTankRegion14)->Fill(Theta_Deg, 1.0);
    h_Data_MuonDOCA_CryoRegion14.GetComponentHist(CryoTankRegion14)->Fill(dataEvt->GetDOCAmu(), 1.0);
    h_Data_Distance_to_InnerTank_CryoRegion14.GetComponentHist(CryoTankRegion14)->Fill(Distance_nearestWall, 1.0);
    h_Data_CryoVertex_Y_CryoRegion14.GetComponentHist(CryoTankRegion14)->Fill(dataEvt->GetVertex_y(), 1.0);
    h_Data_CryoVertex_X_CryoRegion14.GetComponentHist(CryoTankRegion14)->Fill(dataEvt->GetVertex_x(), 1.0);
    h_Data_CryoVertex_Z_CryoRegion14.GetComponentHist(CryoTankRegion14)->Fill(dataEvt->GetVertex_z(), 1.0);
    h_Data_CryoVertex_R_CryoRegion14.GetComponentHist(CryoTankRegion14)->Fill(dataEvt->GetVertex_r(), 1.0);
    h_Data_secTrk_DOCA_CryoRegion14.GetComponentHist(CryoTankRegion14)->Fill(secTrk_DOCA, 1.0);
    h_Data_secTrk_Length_CryoRegion14.GetComponentHist(CryoTankRegion14)->Fill(TrackLength, 1.0);




  }// End of cuts





}// End of enties
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
//EventCountMap[kPlayListVector[0]] = EventCounter_MCFull;
//EventCountMap[kPlayListVector[0]] = EventCounter_MCEmpty;
EventCountMap[PlayList_iterator] = EventCounter_data;
//EventCountMap[kPlayListVector[3]] = EventCounter_dataEmpty;
//////////////////////////////////////////////////////////////////////////
//End of Empty data
//////////////////////////////////////////////////////////////////////////



PrintCutstoScreen( kCutsVector , EventCounter_data, "Full Data",1.0 );



double countdata= 0.0;
double countmc= 0.0;
//double countmcscaled= 0.0;


 //PrintCutstoScreenF_E(  kCutsVector,  kPlayListVector , EventCountMap, POT );
  //=========================================
  // Plot stuff
  //=========================================


//sprintf(pdf_start, "Optimization_figures.pdf(");
//sprintf(pdf_end, "Optimization_figures.pdf)");

TCanvas *can = new TCanvas("", "");
//TCanvas *can = new TCanvas("can", "can",1800,1600);
MnvPlotter *mnv_plotter = new MnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);

   std::cout << " this many Other long tracks  = "<< otherlongtrack<< std::endl;
  std::cout << "END OF Plotting" << std::endl;

  char outFileName[1024];
  auto playlist_name = Playlist_Info.GetPlaylistname();
  auto datatype = String_ISMC(isNOT_mc);
  char c[playlist_name.size() + 1];
  char d[datatype.size() + 1];
  strcpy(c, playlist_name.c_str());
  strcpy(d, datatype.c_str());
  char rootpathway[OUTputRoot_pathway.length()+1];
  strcpy(rootpathway, OUTputRoot_pathway.c_str());
  Make_cvsOfCutsRate( kCutsVector , EventCounter_data, c, isNOT_mc, mcscale, dataPOT );
  TGraph  *RECO_Data_Cuts = Make_RECOCut_Tgraph_fromCutMap("RECO_Data_Cuts", CountMap_RECO_Data);
  TGraph  *RECO_Data_Cuts_Fiducial = Make_RECOCut_Tgraph_fromCutMap("RECO_Data_Cuts_Fiducial", CountMap_RECO_Data_fiduical);


  //outFileName = "Histograms_test.root";
  //auto outFile = TFile::Open(outFileName);
  char pdf_name[1024];
  char pdf_start[1024];
  char pdf_mid[1024];
  char pdf_end[1024];
  sprintf(pdf_name, "DATA_PLOTS_%s_%s",c,d);

  sprintf(pdf_start,"%s.pdf(",pdf_name);
  sprintf(pdf_mid,  "%s.pdf",pdf_name);
  sprintf(pdf_end,  "%s.pdf)",pdf_name);

  can -> Print(pdf_start);

  //DrawVertex_Cryotank_X_Y_R_Vs_Z(UpstreamBugle_vector , c, " [DATA]Upstream Bugle" ,pdf_name , can, mnv_plotter);
  //DrawVertex_Cryotank_X_Y_R_Vs_Z(DownstreamBugle_vector , c, " [DATA]Downstream Bugle" ,pdf_name , can, mnv_plotter);
  //DrawVertex_Cryotank_X_Y_R_Vs_Z(CenterBugle_vector, c, "[DATA]Center Bugle" ,pdf_name , can, mnv_plotter);


  can -> Print(pdf_end);


  sprintf(outFileName, "%s/%s_%s_%s_SideBand_NoFid.root",rootpathway, "Histograms",c,d);

  std::cout << "Writing output file to: " <<outFileName << std::endl;

  //TFile outFile(outFileName, "RECREATE");

  TFile outFile(outFileName, "RECREATE");

  TChain POT_branch("Meta");
  POT_branch.Add(RootName.c_str());
  TTree *clone =POT_branch.CloneTree();
  clone->Write();


  RECO_Data_Cuts->Write();
  RECO_Data_Cuts_Fiducial->Write();
  h_Data_MuonE->Write();
  h_Data_MuonPZ->Write();
  h_Data_MuonPT->Write();
  h_Data_MuonTheta->Write();

  h_Data_MuonE_UpstreamCap->Write();
  h_Data_MuonPT_UpstreamCap->Write();
  h_Data_MuonPZ_UpstreamCap->Write();
  h_Data_MuonTheta_UpstreamCap->Write();

  h_Data_MuonE_Barrel->Write();
  h_Data_MuonPT_Barrel->Write();
  h_Data_MuonPZ_Barrel->Write();
  h_Data_MuonTheta_Barrel->Write();

  h_Data_MuonE_DownstreamCap->Write();
  h_Data_MuonPT_DownstreamCap->Write();
  h_Data_MuonPZ_DownstreamCap->Write();
  h_Data_MuonTheta_DownstreamCap->Write();

  h_Data_MuonE_Downstream_ConcaveCap->Write();
  h_Data_MuonPT_Downstream_ConcaveCap->Write();
  h_Data_MuonPZ_Downstream_ConcaveCap->Write();
  h_Data_MuonTheta_Downstream_ConcaveCap->Write();


  h_Data_MuonDOCA->Write();
  h_Data_MuonDOCA_UpstreamCap->Write();
  h_Data_MuonDOCA_Barrel->Write();
  h_Data_MuonDOCA_DownstreamCap->Write();
  h_Data_MuonDOCA_Downstream_ConcaveCap->Write();

  h_Data_Muon_pseudorapidity->Write();
  h_Data_Muon_pseudorapidity_angle->Write();
  h_Data_Muon_rapidity->Write();


  h_Data_CryoVertex_X->Write();
  h_Data_CryoVertex_Y->Write();
  h_Data_CryoVertex_Z->Write();
  h_Data_CryoVertex_R->Write();



  h_Data_CryoVertex_Z_RCut->Write();
  h_Data_CryoVertex_Z_RCut_UpstreamCap->Write();
  h_Data_CryoVertex_Z_RCut_Barrel->Write();
  h_Data_CryoVertex_Z_RCut_DownstreamCap->Write();
  h_Data_CryoVertex_Z_RCut_Downstream_ConcaveCap->Write();

  h_Data_Distance_to_DownstreamCap->Write();
  h_Data_Distance_to_DownstreamCap_UpstreamCap->Write();
  h_Data_Distance_to_DownstreamCap_Barrel->Write();
  h_Data_Distance_to_DownstreamCap_DownstreamCap->Write();
  h_Data_Distance_to_DownstreamCap_Downstream_ConcaveCap->Write();

  h_Data_Distance_to_DownstreamCap_RCut->Write();
  h_Data_Distance_to_DownstreamCap_RCut_UpstreamCap->Write();
  h_Data_Distance_to_DownstreamCap_RCut_Barrel->Write();
  h_Data_Distance_to_DownstreamCap_RCut_DownstreamCap->Write();
  h_Data_Distance_to_DownstreamCap_RCut_Downstream_ConcaveCap->Write();


  h_Data_Distance_to_UpstreamCap->Write();
  h_Data_Distance_to_UpstreamCap_UpstreamCap->Write();
  h_Data_Distance_to_UpstreamCap_Barrel->Write();
  h_Data_Distance_to_UpstreamCap_DownstreamCap->Write();
  h_Data_Distance_to_UpstreamCap_Downstream_ConcaveCap->Write();

  h_Data_Distance_to_UpstreamCap_RCut->Write();
  h_Data_Distance_to_UpstreamCap_RCut_UpstreamCap->Write();
  h_Data_Distance_to_UpstreamCap_RCut_Barrel->Write();
  h_Data_Distance_to_UpstreamCap_RCut_DownstreamCap->Write();
  h_Data_Distance_to_UpstreamCap_RCut_Downstream_ConcaveCap->Write();

  h_Data_CryoVertex_X_UpstreamCap->Write();
  h_Data_CryoVertex_Y_UpstreamCap->Write();
  h_Data_CryoVertex_Z_UpstreamCap->Write();
  h_Data_CryoVertex_R_UpstreamCap->Write();

  h_Data_CryoVertex_X_Barrel->Write();
  h_Data_CryoVertex_Y_Barrel->Write();
  h_Data_CryoVertex_Z_Barrel->Write();
  h_Data_CryoVertex_R_Barrel->Write();

  h_Data_CryoVertex_X_DownstreamCap->Write();
  h_Data_CryoVertex_Y_DownstreamCap->Write();
  h_Data_CryoVertex_Z_DownstreamCap->Write();
  h_Data_CryoVertex_R_DownstreamCap->Write();

  h_Data_CryoVertex_X_Downstream_ConcaveCap->Write();
  h_Data_CryoVertex_Y_Downstream_ConcaveCap->Write();
  h_Data_CryoVertex_Z_Downstream_ConcaveCap->Write();
  h_Data_CryoVertex_R_Downstream_ConcaveCap->Write();


  h_Data_CryoVertexChiSqFit->Write();
  h_Data_CryoVertexChiSqFit_short->Write();
  h_Data_CryoVertexChiSqFit_long->Write();
  h_Data_CryoVertexChiSqFit_otherlong->Write();
  h_Data_CryoVertexChiSqFit_Track.WriteToFile(outFile);
  h_Data_CryoVertexChiSqFitgreater10_Track.WriteToFile(outFile);
  h_Data_CryoVertexChiSqFit_VertexOptions.WriteToFile(outFile);
  h_Data_CryoVertexChiSqFit_boolNTrack.WriteToFile(outFile);
  h_Data_CryoVertexChiSqFit_unDefinedTrk_VertexOptions.WriteToFile(outFile);
  h_Data_CryoVertexChiSqFit_unDefinedTrk_boolNTrack.WriteToFile(outFile);

  h_Data_CryoVertex_X_Track.WriteToFile(outFile);
  h_Data_CryoVertex_X_boolNTrack.WriteToFile(outFile);
  h_Data_CryoVertex_X_VertexOptions.WriteToFile(outFile);

  h_Data_CryoVertex_Y_Track.WriteToFile(outFile);
  h_Data_CryoVertex_Y_boolNTrack.WriteToFile(outFile);
  h_Data_CryoVertex_Y_VertexOptions.WriteToFile(outFile);

  h_Data_CryoVertex_Z_Track.WriteToFile(outFile);
  h_Data_CryoVertex_Z_boolNTrack.WriteToFile(outFile);
  h_Data_CryoVertex_Z_VertexOptions.WriteToFile(outFile);

  h_Data_CryoVertex_R_Track.WriteToFile(outFile);
  h_Data_CryoVertex_R_boolNTrack.WriteToFile(outFile);
  h_Data_CryoVertex_R_VertexOptions.WriteToFile(outFile);

  h_Data_secTrk_Energy->Write();
  h_Data_secTrk_MidAngle ->Write();
  h_Data_secTrk_DOCA->Write();
  h_Data_secTrk_DOCA_UpstreamCap->Write();
  h_Data_secTrk_DOCA_Barrel->Write();
  h_Data_secTrk_DOCA_DownstreamCap->Write();
  h_Data_secTrk_DOCA_Downstream_ConcaveCap->Write();
  h_Data_secTrk_Pathlength->Write();
  h_Data_secTrk_Pathlength_UpstreamCap->Write();
  h_Data_secTrk_Pathlength_Barrel->Write();
  h_Data_secTrk_Pathlength_DownstreamCap->Write();
  h_Data_secTrk_Pathlength_Downstream_ConcaveCap->Write();
  h_Data_secTrk_Length->Write();
  h_Data_secTrk_Length_UpstreamCap->Write();
  h_Data_secTrk_Length_Barrel->Write();
  h_Data_secTrk_Length_DownstreamCap->Write();
  h_Data_secTrk_Length_Downstream_ConcaveCap->Write();


  h_Data_secTrk_Length_shorttracker->Write();
  h_Data_secTrk_Length_longtracker->Write();
  h_Data_secTrk_Length_otherlongtracker->Write();



  h_Data_secTrk_Openangle->Write();
  h_Data_Tracksize->Write();
  h_Data_secTrk_FirstNodeX->Write();
  h_Data_secTrk_FirstNodeY->Write();
  h_Data_secTrk_FirstNodeZ->Write();
  h_Data_secTrk_LastNodeX->Write();
  h_Data_secTrk_LastNodeY->Write();
  h_Data_secTrk_LastNodeZ->Write();

  h2_Data_secTrkpathLength_R->Write();
  h2_Data_secTrkpathLength_Z->Write();

  h2_Data_R_Z->Write();
  h2_Data_X_Z->Write();
  h2_Data_Y_Z->Write();

  h2_Data_secTrkLength_R->Write();
  h2_Data_secTrkLength_Z->Write();
  h2_Data_2ndtrkLength_Angle->Write();
  h2_Data_2ndtrkLength_finerAngle->Write();
  h2_Data_FirstZnode_2ndTrklength->Write();
  h2_Data_LastZnode_2ndTrklength->Write();


  h_Data_Distance_to_InnerTank->Write();
  h_Data_Distance_to_InnerTank_Fidiucal->Write();
  h_Data_Distance_to_InnerTank_UpstreamCap->Write();
  h_Data_Distance_to_InnerTank_Caps_UpstreamCap->Write();
  h_Data_Distance_to_InnerTank_Caps_Barrel->Write();
  h_Data_Distance_to_InnerTank_Barrel->Write();
  h_Data_Distance_to_InnerTank_Barrel_Barrel->Write();
  h_Data_Distance_to_InnerTank_DownstreamCap->Write();
  h_Data_Distance_to_InnerTank_Caps_DownstreamCap->Write();
  h_Data_Distance_to_InnerTank_Downstream_ConcaveCap->Write();
  h_Data_Distance_to_InnerTank_Caps_UpstreamCap->Write();
  h_Data_Distance_to_InnerTank_Caps_DownstreamCap->Write();
  h_Data_Distance_to_InnerTank_Caps_Downstream_ConcaveCap->Write();
  h_Data_Distance_to_InnerTank_Caps_Downstream_ConcaveCap->Write();
  h_Data_CryoVertex_X_RCut->Write();
  h_Data_CryoVertex_X_RCut_UpstreamCap->Write();
  h_Data_CryoVertex_X_RCut_Barrel->Write();
  h_Data_CryoVertex_X_RCut_DownstreamCap->Write();
  h_Data_CryoVertex_X_RCut_Downstream_ConcaveCap->Write();
  h_Data_CryoVertex_Y_RCut->Write();
  h_Data_CryoVertex_Y_RCut_UpstreamCap->Write();
  h_Data_CryoVertex_Y_RCut_Barrel->Write();
  h_Data_CryoVertex_Y_RCut_DownstreamCap->Write();
  h_Data_CryoVertex_Y_RCut_Downstream_ConcaveCap->Write();
  h_Data_CryoVertex_R_RCut->Write();
  h_Data_CryoVertex_R_RCut_UpstreamCap->Write();
  h_Data_CryoVertex_R_RCut_Barrel->Write();
  h_Data_CryoVertex_R_RCut_DownstreamCap->Write();
  h_Data_CryoVertex_R_RCut_Downstream_ConcaveCap->Write();

  h_Data_MuonE_CryoRegion14.WriteToFile(outFile);
  h_Data_MuonPT_CryoRegion14.WriteToFile(outFile);
  h_Data_MuonPZ_CryoRegion14.WriteToFile(outFile);
  h_Data_MuonTheta_CryoRegion14.WriteToFile(outFile);
  h_Data_MuonDOCA_CryoRegion14.WriteToFile(outFile);
  h_Data_Distance_to_InnerTank_CryoRegion14.WriteToFile(outFile);
  h_Data_CryoVertex_Y_CryoRegion14.WriteToFile(outFile);
  h_Data_CryoVertex_X_CryoRegion14.WriteToFile(outFile);
  h_Data_CryoVertex_Z_CryoRegion14.WriteToFile(outFile);
  h_Data_CryoVertex_R_CryoRegion14.WriteToFile(outFile);
  h_Data_secTrk_DOCA_CryoRegion14.WriteToFile(outFile);
  h_Data_secTrk_Length_CryoRegion14.WriteToFile(outFile);




  outFile.Close();


  //=========================================



//Make_cvs_Data_scanning(SliceID_vertex_info_vector, "EventScan_fourtracks");


//MakeData_trajector(Trajector_DATA_vector, c ,10 ,"Trajector_data", can, mnv_plotter);
//MakeLatex_particleTraj_DATAplots3Tracks(Trajector_DATA_vector,"Trajector_data", "Trajector_data_latex", playlist_name.c_str());

MakeData_trajector(Trajector_DATA_length_vector, c ,10 ,"Trajector_data_Length", can, mnv_plotter);
MakeLatex_particleTraj_DATAplots3Tracks(Trajector_DATA_length_vector,"Trajector_data_Length", "Trajector_data_Length_latex", playlist_name.c_str());


/*
std::cout<<"makeing Table"<<std::endl;
for(auto cat:Trajector_DATA_vector){
  std::cout<<Data_FourtrackTableLatexString(cat)<<std::endl;
}
*/
  std::cout << "Success looping throught Playlist of " <<Playlist_Info.GetPlaylistname() <<std::endl;
std::cout<< "number of tracks not defined " << num_NotDefinedTracks<< std::endl;

}//END of Event Loop

//=========================================
//=========================================
//////////////////////////////////////////////////////////////
std::vector<ECuts> GetRECOCutsVector() {
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
  //ret_vec.push_back(kMuonAngle_CenterForwardGoingAngle);
  ret_vec.push_back(kMu_is_Plausible);

  ret_vec.push_back(kNTracks);
  ret_vec.push_back(kVertexConverge);
  ret_vec.push_back(kVertex_ConvergedfromAllTracks);
  ret_vec.push_back(kMaxChiSqrt_byTrackType);
  //ret_vec.push_back(kFiducialVolume);

  //ret_vec.push_back(kFiducialVolume_new);

  ret_vec.push_back(kVeto );
  ret_vec.push_back(kSix );
  ret_vec.push_back(kMatchVetoDeadPaddle);

  ret_vec.push_back(kTrackForwardGoing);
  ret_vec.push_back(ksecTrkwrtblessthanMaxAngle);

  ret_vec.push_back(kAllCuts );

  /*ret_vec.push_back(kNoCuts  );//
  ret_vec.push_back(kGoodEnergy );//
  ret_vec.push_back(kThetaMu );//
  ret_vec.push_back(kMuonAngle );//
  ret_vec.push_back(kNTracks);//
  ret_vec.push_back(kUsableMuon);//
  //ret_vec.push_back(kNonMu_is_Plausible);
  ret_vec.push_back(kMu_is_Plausible);//
  ret_vec.push_back(kVeto );//
  ret_vec.push_back(kSix );//
  ret_vec.push_back(kMatchVetoDeadPaddle);//

  ret_vec.push_back(kMinosCoil );//
  ret_vec.push_back(kMinosMatch);//
  ret_vec.push_back(kMinosCurvature);//
  ret_vec.push_back(kMinosCharge );//

  ret_vec.push_back(kVertexConverge);//
  ret_vec.push_back(kFiducialVolume );//
  //ret_vec.push_back(kFiducialVolume_ExtraShell);
  ret_vec.push_back(kTrackForwardGoing );//
  ret_vec.push_back(ksecTrkwrtblessthanMaxAngle);//
  //ret_vec.push_back(kMaxChiSqrt);
  ret_vec.push_back(kVertex_ConvergedfromAllTracks);//
  ret_vec.push_back(kMaxChiSqrt_byTrackType);//

  ret_vec.push_back(kAllCuts );//

*/

  //int n = sizeof(kCutsArray) / sizeof(kCutsArray[0]);
  //static std::vector<ECuts> ret_vec(kCutsArray, kCutsArray + n);
  return ret_vec;
//#endif
}

//////////////////
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



////////////////////////////////////////////////////////
//GET MUON Varibles
//////////////////////////////////////////////////////////////////////////
std::vector<MuonVar> GetMUONVaribles() {
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
}

//////////////////////////////////////////////////////////////////////////
//GET Vertex Varibles
//////////////////////////////////////////////////////////////////////////
std::vector<CryoVertex> GetCryoVertexVaribles() {
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
}


std::vector<ME_helium_Playlists> GetPlayListVector() {
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
}

std::vector<ME_helium_Playlists> GetTRUEPlayListVector() {
  std::vector<ME_helium_Playlists> Playlist;

  Playlist.push_back(kME1G_Truth);

  return Playlist;
}


std::vector<SecondTrkVar> GetPlayListSecondTrkVector() {
  std::vector<SecondTrkVar> Playlist;

  Playlist.push_back(ksecE);
  Playlist.push_back(kThetamid);

  return Playlist;
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

  runEventLoop(Playlist_to_run);
  return 0;
}
