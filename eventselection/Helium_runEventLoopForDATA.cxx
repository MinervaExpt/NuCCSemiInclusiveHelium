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

const std::vector< ME_helium_Playlists> kPlayListVector = GetPlayListVector();
const std::vector< ME_helium_Playlists> kTRUEPlayListVector = GetTRUEPlayListVector();

const std::vector<MuonVar> kMuonVaribles_vector = GetMUONVaribles();
const std::vector<SecondTrkVar> ksecTrkVaribles_vector = GetPlayListSecondTrkVector();

const std::vector<CryoVertex> kCryoVertexVaribles_vector = GetCryoVertexVaribles();
EventPlaylist_RecoCount EventCountMap;
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

std::vector<double> Vertex_Xbin_vector= GetBinvertexVector(kX);
std::vector<double> Vertex_Ybin_vector= GetBinvertexVector(kY);
std::vector<double> Vertex_Zbin_vector= GetBinvertexVector(kZ);
std::vector<double> Vertex_Rbin_vector= GetBinvertexVector(kR);
std::vector<double> Vertex_DOCAbin_vector= GetBinMuonVector(kDOCA_muon);

//std::vector<double> secTrkEbin_vector = GetSecondTrkVarVector(ksecE_Proton);
std::vector<double> secTrkEbin_vector= GetSecondTrkVarVector(ksecE);
std::vector<double> secTrkThetamid_vector= GetSecondTrkVarVector(kThetamid);
std::vector<double> secTrkTrkDOCA_vector= GetSecondTrkVarVector(kDOCA);
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



std::vector<double> Recoil_track_length_vector;
double recoil_bin_count=0.0;
for(int ww = 0; ww < 50; ww++ ){
Recoil_track_length_vector.push_back(recoil_bin_count);
recoil_bin_count = recoil_bin_count + 2.54; // bins in [cm]
}
std::vector<double> pseudorapidity_muon_vector{1.0, 1.5,2.0,2.25,2.5,2.75,3.0,3.25,3.5,3.75,4.0,4.5,5.0,8.0};
std::vector<double> rapidity_muon_vector{2.25,  2.45,  2.65,   2.85,  3.05,  3.25, 3.45, 3.65};


  // Use the vector of systematic universes to make your MnvH1D

////////////////
//muon Energy///
////////////////

MnvH1D *h_Data_MuonE       =    new MnvH1D("h_Data_MuonE", "h_Data_MuonE", Ebin_vector.size()-1, Ebin_vector.data());
MnvH1D *h_Data_MuonPT      =    new MnvH1D("h_Data_MuonPT", "h_Data_MuonPT", PTbin_vector.size()-1, PTbin_vector.data());
MnvH1D *h_Data_MuonPZ      =    new MnvH1D("h_Data_MuonPZ", "h_Data_MuonPZ", Pzbin_vector.size()-1, Pzbin_vector.data());
MnvH1D *h_Data_MuonTheta   =    new MnvH1D("h_Data_MuonTheta", "h_Data_MuonTheta", MuonThetabin_vector.size()-1, MuonThetabin_vector.data());
MnvH1D *h_Data_MuonDOCA    =    new MnvH1D("h_Data_MuonDOCA", "h_Data_MuonDOCA", Vertex_DOCAbin_vector.size()-1, Vertex_DOCAbin_vector.data());

MnvH1D *h_Data_Muon_pseudorapidity   =    new MnvH1D("h_Data_Muon_pseudorapidity", "h_Data_Muon_pseudorapidity", pseudorapidity_muon_vector.size()-1, pseudorapidity_muon_vector.data());
MnvH1D *h_Data_Muon_pseudorapidity_angle   =    new MnvH1D("h_Data_Muon_pseudorapidity_angle", "h_Data_Muon_pseudorapidity_angle", MuonThetabin_vector.size()-1, MuonThetabin_vector.data());

MnvH1D *h_Data_Muon_rapidity    =    new MnvH1D("h_Data_Muon_rapidity", "h_Data_Muon_rapidity", rapidity_muon_vector.size()-1, rapidity_muon_vector.data());


MnvH1D *h_Data_Tracksize =              new MnvH1D("h_Data_Tracksize", "h_Data_Tracksize", TrackSize_vector.size()-1, TrackSize_vector.data());
MnvH1D *h_Data_MuoncurvatureSig    =    new MnvH1D("h_Data_MuoncurvatureSig", "h_Data_MuoncurvatureSig", Muon_curvatureSig_vector.size()-1, Muon_curvatureSig_vector.data());

MnvH1D *h_Data_minosR    =          new MnvH1D("h_Data_minosR", "h_Data_minosR", Minos_R_vector.size()-1, Minos_R_vector.data());
MnvH1D *h_Data_minosStart_X    =    new MnvH1D("h_Data_minosStart_X", "h_Data_minosStart_X", Minos_Start_X_vector.size()-1, Minos_Start_X_vector.data());
MnvH1D *h_Data_minosStart_Y    =    new MnvH1D("h_Data_minosStart_Y", "h_Data_minosStart_Y", Minos_Start_Y_vector.size()-1, Minos_Start_Y_vector.data());
MnvH1D *h_Data_minosStart_Z    =    new MnvH1D("h_Data_minosStart_Z", "h_Data_minosStart_Z", Minos_Start_Z_vector.size()-1, Minos_Start_Z_vector.data());

MnvH1D *h_Data_minosEnd_X    =    new MnvH1D("h_Data_minosEnd_X", "h_Data_minosEnd_X", Minos_End_X_vector.size()-1, Minos_End_X_vector.data());
MnvH1D *h_Data_minosEnd_Y    =    new MnvH1D("h_Data_minosEnd_Y", "h_Data_minosEnd_Y", Minos_End_Y_vector.size()-1, Minos_End_Y_vector.data());
MnvH1D *h_Data_minosEnd_Z    =    new MnvH1D("h_Data_minosEnd_Z", "h_Data_minosEnd_Z", Minos_End_Z_vector.size()-1, Minos_End_Z_vector.data());

MnvH1D *h_Data_muonFirstNodeX    =    new MnvH1D("h_Data_muonFirstNodeX", "h_Data_muonFirstNodeX", Muon_StartNode_X_vector.size()-1, Muon_StartNode_X_vector.data());
MnvH1D *h_Data_muonFirstNodeY    =    new MnvH1D("h_Data_muonFirstNodeY", "h_Data_muonFirstNodeY", Muon_StartNode_Y_vector.size()-1, Muon_StartNode_Y_vector.data());
MnvH1D *h_Data_muonFirstNodeZ    =    new MnvH1D("h_Data_muonFirstNodeZ", "h_Data_muonFirstNodeZ", Muon_StartNode_Z_vector.size()-1, Muon_StartNode_Z_vector.data());

MnvH1D *h_Data_muonLastNodeX    =    new MnvH1D("h_Data_muonLastNodeX", "h_Data_muonLastNodeX", Muon_LastNode_X_vector.size()-1, Muon_LastNode_X_vector.data());
MnvH1D *h_Data_muonLastNodeY    =    new MnvH1D("h_Data_muonLastNodeY", "h_Data_muonLastNodeY", Muon_LastNode_Y_vector.size()-1, Muon_LastNode_Y_vector.data());
MnvH1D *h_Data_muonLastNodeZ    =    new MnvH1D("h_Data_muonLastNodeZ", "h_Data_muonLastNodeZ", Muon_LastNode_Z_vector.size()-1, Muon_LastNode_Z_vector.data());

MnvH1D *h_Data_MuonCharge =          new MnvH1D("h_Data_MuonCharge", "h_Data_MuonCharge", MuonCharge_vector.size()-1, MuonCharge_vector.data());
MnvH1D *h_Data_MuonMatchtoMinos =    new MnvH1D("h_Data_MuonMatchtoMinos", "h_Data_MuonMatchtoMinos", MuonMatchtoMinos_vector.size()-1, MuonMatchtoMinos_vector.data());
MnvH1D *h_Data_MuonMatchtoVeto =     new MnvH1D("h_Data_MuonMatchtoVeto", "h_Data_MuonMatchtoVeto", MuonMatchtoVeto_vector.size()-1, MuonMatchtoVeto_vector.data());


MnvH1D *h_Data_VetoWall_NumbermatchToVeto       = new MnvH1D("h_Data_VetoWall_NumbermatchToVeto", "h_Data_VetoWall_NumbermatchToVeto", 7, -1.5, 5.5);
MnvH1D *h_Data_VetoWall_matchToVeto       = new MnvH1D("h_Data_VetoWall_matchToVeto", "h_Data_VetoWall_matchToVeto", MuonMatchtoVeto_vector.size()-1,MuonMatchtoVeto_vector.data());

MnvH1D *h_Data_VetoWall_extrapnowalls     = new MnvH1D("h_Data_VetoWall_extrapnowalls","h_Data_VetoWall_extrapnowalls", MuonMatchtoVeto_vector.size()-1,MuonMatchtoVeto_vector.data());
MnvH1D *h_Data_VetoWall_extrapwall1       = new MnvH1D("h_Data_VetoWall_extrapwall1","h_Data_VetoWall_extrapwall1", MuonMatchtoVeto_vector.size()-1,MuonMatchtoVeto_vector.data());
MnvH1D *h_Data_VetoWall_extrapwall2       = new MnvH1D("h_Data_VetoWall_extrapwall2","h_Data_VetoWall_extrapwall2", MuonMatchtoVeto_vector.size()-1,MuonMatchtoVeto_vector.data());
MnvH1D *h_Data_VetoWall_extrapbothwalls   = new MnvH1D("h_Data_VetoWall_extrapbothwalls","h_Data_VetoWall_extrapbothwalls", MuonMatchtoVeto_vector.size()-1,MuonMatchtoVeto_vector.data());
MnvH1D *h_Data_VetoWall_MuonTrkMatchToVETOwalloff = new MnvH1D("h_Data_VetoWall_MuonTrkMatchToVETOwalloff","h_Data_VetoWall_MuonTrkMatchToVETOwalloff", MuonMatchtoVeto_vector.size()-1,MuonMatchtoVeto_vector.data());
MnvH1D *h_Data_VetoWall_vetoSixPush               = new MnvH1D("h_Data_VetoWall_vetoSixPush","h_Data_VetoWall_vetoSixPush", MuonMatchtoVeto_vector.size()-1,MuonMatchtoVeto_vector.data());

MnvH1D *h_Data_VetoWall_PMTMAP_ON               = new MnvH1D("h_Data_VetoWall_PMTMAP_ON","h_Data_VetoWall_PMTMAP_ON", Veto_PMTmap_vector.size()-1, Veto_PMTmap_vector.data());
MnvH1D *h_Data_VetoWall_PMTMAP_OFF               = new MnvH1D("h_Data_VetoWall_PMTMAP_OFF","h_Data_VetoWall_PMTMAP_OFF", Veto_PMTmap_vector.size()-1, Veto_PMTmap_vector.data());


////////////////
//Vertex Hist///
////////////////
MnvH1D *h_Data_CryoVertex_X      =    new MnvH1D("h_Data_CryoVertex_X", "h_Data_CryoVertex_X", Vertex_Xbin_vector.size()-1, Vertex_Xbin_vector.data());

PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType> h_Data_CryoVertex_X_Track =
PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType>(TrackType_Category, "h_Data_CryoVertex_X_Track", Vertex_Xbin_vector ,"h_Data_CryoVertex_X_Track; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack> h_Data_CryoVertex_X_boolNTrack =
PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack>(boolNTrack_Category, "h_Data_CryoVertex_X_boolNTrack", Vertex_Xbin_vector ,"h_Data_CryoVertex_X_boolNTrack; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions> h_Data_CryoVertex_X_VertexOptions =
PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions>(VertexOptions_Category, "h_Data_CryoVertex_X_VertexOptions", Vertex_Xbin_vector ,"h_Data_CryoVertex_X_VertexOptions; [mm];Events");


MnvH1D *h_Data_CryoVertex_Y      =    new MnvH1D("h_Data_CryoVertex_Y", "h_Data_CryoVertex_Y", Vertex_Ybin_vector.size()-1, Vertex_Ybin_vector.data());

PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType> h_Data_CryoVertex_Y_Track =
PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType>(TrackType_Category, "h_Data_CryoVertex_Y_Track", Vertex_Ybin_vector ,"h_Data_CryoVertex_Y_Track; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack> h_Data_CryoVertex_Y_boolNTrack =
PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack>(boolNTrack_Category, "h_Data_CryoVertex_Y_boolNTrack", Vertex_Ybin_vector ,"h_Data_CryoVertex_Y_boolNTrack; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions> h_Data_CryoVertex_Y_VertexOptions =
PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions>(VertexOptions_Category, "h_Data_CryoVertex_Y_VertexOptions", Vertex_Ybin_vector ,"h_Data_CryoVertex_Y_VertexOptions; [mm];Events");




MnvH1D *h_Data_CryoVertex_Z      =    new MnvH1D("h_Data_CryoVertex_Z", "h_Data_CryoVertex_Z", Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());

PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType> h_Data_CryoVertex_Z_Track =
PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType>(TrackType_Category, "h_Data_CryoVertex_Z_Track", Vertex_Zbin_vector ,"h_Data_CryoVertex_Z_Track; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack> h_Data_CryoVertex_Z_boolNTrack =
PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack>(boolNTrack_Category, "h_Data_CryoVertex_Z_boolNTrack", Vertex_Zbin_vector ,"h_Data_CryoVertex_Z_boolNTrack; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions> h_Data_CryoVertex_Z_VertexOptions =
PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions>(VertexOptions_Category, "h_Data_CryoVertex_Z_VertexOptions", Vertex_Zbin_vector ,"h_Data_CryoVertex_Z_VertexOptions; [mm];Events");


MnvH1D *h_Data_CryoVertex_R      =    new MnvH1D("h_Data_CryoVertex_R", "h_Data_CryoVertex_R", Vertex_Rbin_vector.size()-1, Vertex_Rbin_vector.data());

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
MnvH1D *h_Data_secTrk_DOCA                 =    new MnvH1D("h_Data_secTrk_DOCA", "h_Data_secTrk_DOCA", secTrkTrkDOCA_vector.size()-1, secTrkTrkDOCA_vector.data());
MnvH1D *h_Data_secTrk_Pathlength          =    new MnvH1D("h_Data_secTrk_Pathlength", "h_Data_secTrk_Pathlength", secTrkPathway_vector.size()-1, secTrkPathway_vector.data());
MnvH1D *h_Data_secTrk_Energy               =    new MnvH1D("h_Data_secTrk_Energy", "h_Data_secTrk_Energy", secTrkEbin_vector.size()-1, secTrkEbin_vector.data());
MnvH1D *h_Data_secTrk_MidAngle             =    new MnvH1D("h_Data_secTrk_MidAngle", "h_Data_secTrk_MidAngle", secTrkThetamid_vector.size()-1, secTrkThetamid_vector.data());
MnvH1D *h_Data_secTrk_Openangle            =    new MnvH1D("h_Data_secTrk_Openangle", "h_Data_secTrk_Openangle", secTrkThetamid_vector.size()-1, secTrkThetamid_vector.data());



MnvH1D *h_Data_secTrk_Length          =    new MnvH1D("h_Data_secTrk_Length", "h_Data_secTrk_Length", Recoil_track_length_vector.size()-1, Recoil_track_length_vector.data());

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
FillingRecoCountingMap(kCutsVector, CountMap_RECO_Data);
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

  if(ievent%10000==0) std::cout << (ievent/1000) << "k " << std::endl;
  dataEvt->SetEntry(ievent);

  EventCounter(*dataEvt, kCutsVector, EventCounter_data, isNOT_mc, Playlist_Info );

  if(PassesCutsRECOData(*dataEvt,  isNOT_mc , kCutsVector, CountMap_RECO_Data) ){
    double zvertex = dataEvt->GetVertex_z();
    //if(CryoTankConsts::FBackOfCryoInnerVessel < zvertex )continue;
    //if(CryoTankConsts::FrontOfCryoInnerVessel > zvertex )continue;
    //if(650.0 < dataEvt->GetVertex_r() )continue;

    double Theta = dataEvt->GetThetamu();
    //double Pmu =   dataEvt-> GetPmu_inhouse()/1000;
    double Pmu =   dataEvt->GetPmu()/1000;
    double Emu =   dataEvt->GetEmu()*.001;
    double pseduo_r = dataEvt->pseudorapidity_muon();
    double pseduo_theta = 2 * atan(exp(-pseduo_r)) *TMath::RadToDeg();
    double PT = Pmu*std::sin(Theta);
    double PZ = Pmu*std::cos(Theta);

    auto trackType = dataEvt->GetTrackType();
    VertexOptions VertexOption_type = dataEvt->GetVertex_optionType();
    boolNTrack boolNTrack_Type = dataEvt->GetVertex_boolNTrack();


    //std::cout << "Theta = "<< Theta<<std::endl;
    //std::cout << "Pmu = "<< Pmu<<std::endl;
    //std::cout << "Pmu = "<< dataEvt->GetMuonPt_ECT()<<std::endl;

    //std::cout << "Muon E = "<< dataEvt->GetMuonE_ECT()<<std::endl;
    h_Data_MuonE->Fill(Emu, 1.0);
    h_Data_MuonPZ->Fill(Pmu*std::cos(Theta), 1.0);//GetMuonPz()
    h_Data_MuonPT->Fill(Pmu*std::sin(Theta), 1.0);
    h_Data_MuonTheta->Fill(Theta*TMath::RadToDeg(),1.0);
    h_Data_Muon_pseudorapidity->Fill(pseduo_r,1.0);
    h_Data_Muon_pseudorapidity_angle->Fill(pseduo_theta,1.0);
    h_Data_Muon_rapidity->Fill(dataEvt->rapidity_muon(),1.0);

    int secondTrk = dataEvt->Getindex2ndTrackhighestKE();
    double TrackLength = dataEvt->GetNonmuTrkLength(secondTrk);
  //  h_Data_MuonE->Fill(dataEvt->GetMuonE_ECT(), 1.0);//GetMuonE()
  //  h_Data_MuonPZ->Fill(dataEvt->GetMuonPz_ECT(), 1.0);//GetMuonPz()
  //  h_Data_MuonPT->Fill(dataEvt->GetMuonPt_ECT(), 1.0);//GetMuonPt()
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
        /*
      std::cout<< "track name = "<< GetNameTrack(trackType)<<std::endl;
      auto longstatus = dataEvt->GetLongAnchorTrackStatus();
      auto shortstatus = dataEvt->GetShortAnchorTrackStatus();
      auto Otherlongerstatus = dataEvt->GetOtherLongTrackStatus();
      std::cout<< "longstatus = "<< longstatus<<std::endl;
      std::cout<< "shortstatus = "<< shortstatus<<std::endl;
      std::cout<< "Otherlongerstatus = "<< Otherlongerstatus<<std::endl;
*/

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



    h_Data_MuonDOCA->Fill(dataEvt->GetDOCAmu(),1.0);

    h_Data_MuonCharge->Fill(dataEvt->GetChargemu(), 1.0);
    h_Data_MuonMatchtoMinos->Fill(dataEvt->GetIntIsusableMuon(), 1.0);
    h_Data_MuonMatchtoVeto->Fill(dataEvt->GetMatchToVeto(), 1.0);
    h_Data_MuoncurvatureSig->Fill(dataEvt->GetCurvatureSignificance(), 1.0);

    double recoiltheta = dataEvt->GetNonmuTrkAngleWRTbeamMID(secondTrk);
    h_Data_secTrk_Energy->Fill(dataEvt->GetNonmuTrkE(secondTrk)*Mev_to_GeV,1.0);
    h_Data_secTrk_MidAngle ->Fill(dataEvt->GetNonmuTrkAngleWRTbeamMID(secondTrk),1.0);
    h_Data_secTrk_Openangle->Fill(dataEvt->GetNonmuTrkAngleWRTmu(secondTrk),1.0);
    h_Data_secTrk_DOCA->Fill(dataEvt->GetNonmuDOCA(secondTrk),1.0);

    h_Data_secTrk_Pathlength->Fill(TrackLength,1.0);
    h_Data_secTrk_Length->Fill(dataEvt->GetNonmuTrkLength_InMinerva_Incm(secondTrk),1.0);
    //auto tracktype = dataEvt->GetTrackType();


    h2_Data_R_Z->Fill(dataEvt->GetVertex_r(),dataEvt->GetVertex_z(),1.0);
    h2_Data_X_Z->Fill(dataEvt->GetVertex_x(),dataEvt->GetVertex_z(),1.0);
    h2_Data_Y_Z->Fill(dataEvt->GetVertex_y(),dataEvt->GetVertex_z(),1.0);

    h2_Data_secTrkpathLength_R->Fill(TrackLength,dataEvt->GetVertex_r(),1.0);
    h2_Data_secTrkpathLength_Z->Fill(TrackLength,dataEvt->GetVertex_z(),1.0);

    h2_Data_secTrkLength_R->Fill(dataEvt->GetNonmuTrkLength_InMinerva_Incm(secondTrk),dataEvt->GetVertex_r(),1.0);
    h2_Data_secTrkLength_Z->Fill(dataEvt->GetNonmuTrkLength_InMinerva_Incm(secondTrk),dataEvt->GetVertex_z(),1.0);
    h2_Data_2ndtrkLength_Angle->Fill(dataEvt->GetNonmuTrkLength_InMinerva_Incm(secondTrk),dataEvt->GetNonmuTrkAngleWRTbeamMID(secondTrk),1.0);
    h2_Data_2ndtrkLength_finerAngle->Fill(dataEvt->GetNonmuTrkLength_InMinerva_Incm(secondTrk),dataEvt->GetNonmuTrkAngleWRTbeamMID(secondTrk),1.0);

    h2_Data_FirstZnode_2ndTrklength->Fill(dataEvt->GetFirstNodeZ(secondTrk), TrackLength, 1.0);
    h2_Data_LastZnode_2ndTrklength->Fill(dataEvt->GetLastNodeZ(secondTrk), TrackLength, 1.0);



    h_Data_VetoWall_NumbermatchToVeto->Fill( dataEvt->GetNumberMatchToVeto() ,1.0);
    h_Data_VetoWall_matchToVeto ->Fill( dataEvt->GetMatchToVeto(), 1.0);
    h_Data_VetoWall_extrapnowalls->Fill( dataEvt->Getextrapnowalls() ,1.0);
    h_Data_VetoWall_extrapwall1  ->Fill( dataEvt->Getextrapwall1() ,1.0);
    h_Data_VetoWall_extrapwall2  ->Fill( dataEvt->Getextrapwall2() ,1.0);
    h_Data_VetoWall_extrapbothwalls ->Fill( dataEvt->Getextrapbothwalls() ,1.0);
    h_Data_VetoWall_MuonTrkMatchToVETOwalloff->Fill( dataEvt->GetMuonTrkMatchToVETOwalloff() ,1.0);
    h_Data_VetoWall_vetoSixPush->Fill(dataEvt->GetSixPush() ,1.0);
    auto PMTMap_vector=dataEvt->GetVector_PMTVeto_Map();
    double pmt_count = 1;

    for(auto cat : PMTMap_vector){
      if(cat ==1)h_Data_VetoWall_PMTMAP_ON ->Fill(pmt_count ,1.0);
      if(cat == -1)h_Data_VetoWall_PMTMAP_OFF ->Fill(pmt_count ,1.0);
      pmt_count++;}


    h_Data_secTrk_FirstNodeX->Fill(dataEvt->GetFirstNodeX(secondTrk),1.0);
    h_Data_secTrk_FirstNodeY->Fill(dataEvt->GetFirstNodeY(secondTrk),1.0);
    h_Data_secTrk_FirstNodeZ->Fill(dataEvt->GetFirstNodeZ(secondTrk),1.0);
    h_Data_secTrk_LastNodeX->Fill(dataEvt->GetLastNodeX(secondTrk),1.0);
    h_Data_secTrk_LastNodeY->Fill(dataEvt->GetLastNodeY(secondTrk),1.0);
    h_Data_secTrk_LastNodeZ->Fill(dataEvt->GetLastNodeZ(secondTrk),1.0);
    h_Data_Tracksize->Fill(dataEvt->GetTracksize(),1.0);

/*
  if(trackcount<45){
    if(recoiltheta > 16.0 && recoiltheta < 20.0 ){
      if(PT > .4 && PT < 0.475 ){
        if(PZ > 4.0 && PZ < 4.5 ){
          if(TrackLength < 25. && TrackLength > 17. ){
            std::cout<<"inside pass"<<std::endl;
            Trajector_DATA stuct_data = dataEvt->Return_Trajector_DATA_struct();
            Trajector_DATA_length_vector.push_back(stuct_data);

            trackcount++;
          }
        }
      }
    }
  }
*/


    //if(dataEvt->GetTracksize()==3 ){
      //if(trackcount<30){
      //Vertex_XYZ XYZinput{dataEvt->GetVertex_x(),dataEvt->GetVertex_y(),dataEvt->GetVertex_z()};
      //auto Event_slice = dataEvt->GetEventSliceForData();
      //SliceID_vertex_info Fourtracks{Event_slice, XYZinput};
      //SliceID_vertex_info_vector.push_back(Fourtracks);

      //Trajector_DATA stuct_data = dataEvt->Return_Trajector_DATA_struct();

      //Trajector_DATA_vector.push_back(stuct_data);

    //  }
    //}



    h_Data_minosStart_X->Fill( dataEvt->GetMINOSStart_X(),1.0);
    h_Data_minosStart_Y->Fill( dataEvt->GetMINOSStart_Y(),1.0);
    h_Data_minosStart_Z->Fill( dataEvt->GetMINOSStart_Z(),1.0);
    h_Data_minosEnd_X->Fill( dataEvt->GetMINOSEnd_X(),1.0);
    h_Data_minosEnd_Y->Fill( dataEvt->GetMINOSEnd_Y(),1.0);
    h_Data_minosEnd_Z->Fill( dataEvt->GetMINOSEnd_Z(),1.0);

    h_Data_muonFirstNodeX->Fill( dataEvt->GetMuon_firstNode_X(),1.0);
    h_Data_muonFirstNodeY->Fill( dataEvt->GetMuon_firstNode_Y(),1.0);
    h_Data_muonFirstNodeZ->Fill( dataEvt->GetMuon_firstNode_Z(),1.0);

    h_Data_muonLastNodeX->Fill( dataEvt->GetMuon_lastNode_X(),1.0);
    h_Data_muonLastNodeY->Fill( dataEvt->GetMuon_lastNode_Y(),1.0);
    h_Data_muonLastNodeZ->Fill( dataEvt->GetMuon_lastNode_Z(),1.0);


  }

}
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


  sprintf(outFileName, "%s/%s_%s_%s.root",rootpathway, "Histograms",c,d);

  std::cout << "Writing output file to: " <<outFileName << std::endl;

  //TFile outFile(outFileName, "RECREATE");

  TFile outFile(outFileName, "RECREATE");

  TChain POT_branch("Meta");
  POT_branch.Add(RootName.c_str());
  TTree *clone =POT_branch.CloneTree();
  clone->Write();


  RECO_Data_Cuts->Write();

  h_Data_MuonE->Write();
  h_Data_MuonPZ->Write();
  h_Data_MuonPT->Write();
  h_Data_MuonTheta->Write();
  h_Data_MuonDOCA->Write();
  h_Data_Muon_pseudorapidity->Write();
  h_Data_Muon_pseudorapidity_angle->Write();
  h_Data_Muon_rapidity->Write();


  h_Data_CryoVertex_X->Write();
  h_Data_CryoVertex_Y->Write();
  h_Data_CryoVertex_Z->Write();
  h_Data_CryoVertex_R->Write();
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


  h_Data_VetoWall_NumbermatchToVeto->Write();
  h_Data_VetoWall_matchToVeto->Write();
  h_Data_VetoWall_extrapnowalls->Write();
  h_Data_VetoWall_extrapwall1->Write();
  h_Data_VetoWall_extrapwall2->Write();
  h_Data_VetoWall_extrapbothwalls->Write();
  h_Data_VetoWall_MuonTrkMatchToVETOwalloff->Write();
  h_Data_VetoWall_vetoSixPush->Write();
  h_Data_secTrk_Energy->Write();
  h_Data_secTrk_MidAngle ->Write();
  h_Data_secTrk_DOCA->Write();
  h_Data_secTrk_Pathlength->Write();
  h_Data_secTrk_Length->Write();

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
  h_Data_VetoWall_PMTMAP_ON->Write();
  h_Data_VetoWall_PMTMAP_OFF->Write();
  h_Data_minosStart_X->Write();
  h_Data_minosStart_Y->Write();
  h_Data_minosStart_Z->Write();
  h_Data_minosEnd_X->Write();
  h_Data_minosEnd_Y->Write();
  h_Data_minosEnd_Z->Write();
  h_Data_muonFirstNodeX->Write();
  h_Data_muonFirstNodeY->Write();
  h_Data_muonFirstNodeZ->Write();
  h_Data_muonLastNodeX->Write();
  h_Data_muonLastNodeY->Write();
  h_Data_muonLastNodeZ->Write();
  h_Data_MuonCharge->Write();
  h_Data_MuonMatchtoMinos->Write();
  h_Data_MuonMatchtoVeto->Write();
  h_Data_MuoncurvatureSig->Write();
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



//////////////////////////////////////////////////////////////////////////
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
