// Loop entries, make cuts, fill histograms.
// * Uses the New Systematics Framework and "Universe" objects.
// * loop universes, make cuts and fill histograms with the correct lateral
// shifts and weights for each universe.
// * TChain --> PlotUtils::ChainWrapper.
// * MnvHXD --> PlotUtils::HistWrapper.
// * Genie, flux, non-resonant pion, and some detector systematics calculated.
#include "Helium_runEventLoopForDATA_SmearingStudy.h"

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
  PlotUtils::NamedCategory<TrackType>({kNotdefinedTrack}, "NotdefinedTrack")

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
  bool isNOT_mc= false;
bool is_counter = true;
double POT[4];
const std::vector< ECuts > kCutsVector = GetRECOCutsVector();

const std::vector< ME_helium_Playlists> kPlayListVector = GetPlayListVector();
const std::vector< ME_helium_Playlists> kTRUEPlayListVector = GetTRUEPlayListVector();

const std::vector<MuonVar> kMuonVaribles_vector = GetMUONVaribles();
const std::vector<SecondTrkVar> ksecTrkVaribles_vector = GetPlayListSecondTrkVector();

const std::vector<CryoVertex> kCryoVertexVaribles_vector = GetCryoVertexVaribles();
EventPlaylist_RecoCount EventCountMap;

MinervaUniverse::SetNuEConstraint(false);

std::vector <SliceID_vertex_info> Low_R_EventID_vector;
int Center_counter = 0;

std::string playlist = GetPlaylist(PlayList_iterator);
MinervaUniverse::SetPlaylist(playlist);


//======================================================================
////////////////////ADDING TO CHAIN wrapper ///////////////////////////
//======================================================================

//======================================================================
///////////////////Making/adding to error bands  ///////////////////////////
//======================================================================

POTCounter pot_counter;


auto mcscale = 1.0; //Data_POT_full/ MC_POT_full;

double Mev_to_GeV=.001;

std::vector<double> Ebin_vector = GetBinMuonVector(kE);
std::vector<double> Pzbin_vector= GetBinMuonVector(kP_Z);
std::vector<double> PTbin_vector= GetBinMuonVector(kP_T);

std::vector<double> MuonThetabin_vector= GetBinMuonVector(kAngleWRTB);

//std::vector<double> Vertex_Xbin_vector = GetBinvertexVector(kX);
//std::vector<double> Vertex_Ybin_vector = GetBinvertexVector(kY);
//std::vector<double> Vertex_Zbin_vector = GetBinvertexVector(kZ);
//std::vector<double> Vertex_Rbin_vector = GetBinvertexVector(kR);

std::vector<double> Vertex_Zbin_vector{1450, 1750.00, 2050.00, 2250, 2450, 2650, 2850, 3000, 3200,  3400, 3650, 3900, 4200, 4350};
std::vector<double> Vertex_Rbin_vector{0, 200, 400, 600,  700,   800,  1000,  1200};
std::vector<double> Vertex_Ybin_vector{-1200, -1000, -800, -600, -400, -200, 0, 200, 400, 600, 800, 1000, 1200};
std::vector<double> Vertex_Xbin_vector{-1200, -1000, -800, -600, -400, -200, 0, 200, 400, 600, 800, 1000, 1200};



std::vector<double> Vertex_RRbin_vector = GetBinvertexVector(kRR);
std::vector<double> Vertex_DOCAbin_vector= GetBinMuonVector(kDOCA_muon);

//std::vector<double> secTrkEbin_vector = GetSecondTrkVarVector(ksecE_Proton);
std::vector<double> secTrkEbin_vector= GetSecondTrkVarVector(ksecE);
std::vector<double> secTrkThetamid_vector= GetSecondTrkVarVector(kThetamid);
std::vector<double> secTrkTrkDOCA_vector= GetSecondTrkVarVector(kDOCA);
std::vector<double> secTrkPathway_vector = GetSecondTrkVarVector(kPathway);
std::vector<double> secTrkTheta_vector= GetSecondTrkVarVector(kTheta);

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
std::vector<double> Distance_to_innerTank = GetBinvertexVector(kdistance_edge);
std::vector<double> Distance_to_Caps = GetBinvertexVector(kdistance_downstreamcap);

std::vector<double> Recoil_track_length_vector;
double recoil_bin_count = 0.0;
for(int ww = 0; ww < 50; ww++ ){
Recoil_track_length_vector.push_back(recoil_bin_count);
recoil_bin_count = recoil_bin_count + 2.54; // bins in [cm]
}
  // Use the vector of systematic universes to make your MnvH1D

////////////////
//muon Energy///
////////////////

MnvH1D *h_Data_MuonE       =    new MnvH1D("h_Data_MuonE", "h_Data_MuonE", Ebin_vector.size()-1, Ebin_vector.data());
MnvH1D *h_Data_MuonPT      =    new MnvH1D("h_Data_MuonPT", "h_Data_MuonPT", PTbin_vector.size()-1, PTbin_vector.data());
MnvH1D *h_Data_MuonPZ      =    new MnvH1D("h_Data_MuonPZ", "h_Data_MuonPZ", Pzbin_vector.size()-1, Pzbin_vector.data());
MnvH1D *h_Data_MuonTheta   =    new MnvH1D("h_Data_MuonTheta", "h_Data_MuonTheta", MuonThetabin_vector.size()-1, MuonThetabin_vector.data());
MnvH1D *h_Data_MuonDOCA    =    new MnvH1D("h_Data_MuonDOCA", "h_Data_MuonDOCA", Vertex_DOCAbin_vector.size()-1, Vertex_DOCAbin_vector.data());

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

MnvH1D *h_Data_VetoWall_matchToVeto       = new MnvH1D("h_DATA_VetoWall_matchToVeto", "h_DATA_VetoWall_matchToVeto", BinVector_MatchToveto.size()-1, BinVector_MatchToveto.data());
MnvH1D *h_Data_VetoWall_extrapnowalls     = new MnvH1D("h_Data_VetoWall_extrapnowalls","h_Data_VetoWall_extrapnowalls", 2, -0.5, 1.5);
MnvH1D *h_Data_VetoWall_extrapwall1       = new MnvH1D("h_Data_VetoWall_extrapwall1","h_Data_VetoWall_extrapwall1", 2, -0.5, 1.5);
MnvH1D *h_Data_VetoWall_extrapwall2       = new MnvH1D("h_Data_VetoWall_extrapwall2","h_Data_VetoWall_extrapwall2", 2, -0.5, 1.5);
MnvH1D *h_Data_VetoWall_extrapbothwalls   = new MnvH1D("h_Data_VetoWall_extrapbothwalls","h_Data_VetoWall_extrapbothwalls", 2, -0.5, 1.5);
MnvH1D *h_Data_VetoWall_MuonTrkMatchToVETOwalloff = new MnvH1D("h_Data_VetoWall_MuonTrkMatchToVETOwalloff","h_Data_VetoWall_MuonTrkMatchToVETOwalloff", 2, -0.5, 1.5);

MnvH1D *h_Data_secTrk_tracklength                           =    new MnvH1D("h_Data_secTrk_tracklength", "h_Data_secTrk_tracklength", Recoil_track_length_vector.size()-1, Recoil_track_length_vector.data());
MnvH1D *h_Data_secTrk_tracklength_upstreamCap               =    new MnvH1D("h_Data_secTrk_tracklength_upstreamCap", "h_Data_secTrk_tracklength_upstreamCap", Recoil_track_length_vector.size()-1, Recoil_track_length_vector.data());
MnvH1D *h_Data_secTrk_tracklength_barrel             =    new MnvH1D("h_Data_secTrk_tracklength_barrel", "h_Data_secTrk_tracklength_barrel", Recoil_track_length_vector.size()-1, Recoil_track_length_vector.data());
MnvH1D *h_Data_secTrk_tracklength_downstreamCap             =    new MnvH1D("h_Data_secTrk_tracklength_downstreamCap", "h_Data_secTrk_tracklength_downstreamCap", Recoil_track_length_vector.size()-1, Recoil_track_length_vector.data());
MnvH1D *h_Data_secTrk_tracklength_downstreamConcaveCap                    =    new MnvH1D("h_Data_secTrk_tracklength_downstreamConcaveCap", "h_Data_secTrk_tracklength_downstreamConcaveCap", Recoil_track_length_vector.size()-1, Recoil_track_length_vector.data());



MnvH1D *h_Data_secTrkLength_upstreamCap               =    new MnvH1D("h_Data_secTrkLength_upstreamCap",          "h_Data_secTrkLength_upstreamCap",          Recoil_track_length_vector.size()-1, Recoil_track_length_vector.data());
MnvH1D *h_Data_secTrkLength_downstreamCap             =    new MnvH1D("h_Data_secTrkLength_downstreamCap",        "h_Data_secTrkLength_downstreamCap",        Recoil_track_length_vector.size()-1, Recoil_track_length_vector.data());
MnvH1D *h_Data_secTrkLength_barrel                    =    new MnvH1D("h_Data_secTrkLength_barrel",               "h_Data_secTrkLength_barrel",               Recoil_track_length_vector.size()-1, Recoil_track_length_vector.data());
MnvH1D *h_Data_secTrkLength_downstreamConcaveCap      =    new MnvH1D("h_Data_secTrkLength_downstreamConcaveCap", "h_Data_secTrkLength_downstreamConcaveCap", Recoil_track_length_vector.size()-1, Recoil_track_length_vector.data());

MnvH1D *h_Data_secTrkLength_Fiducial_upstreamCap               =    new MnvH1D("h_Data_secTrkLength_Fiducial_upstreamCap",          "h_Data_secTrkLength_Fiducial_upstreamCap",          Recoil_track_length_vector.size()-1, Recoil_track_length_vector.data());
MnvH1D *h_Data_secTrkLength_Fiducial_downstreamCap             =    new MnvH1D("h_Data_secTrkLength_Fiducial_downstreamCap",        "h_Data_secTrkLength_Fiducial_downstreamCap",        Recoil_track_length_vector.size()-1, Recoil_track_length_vector.data());
MnvH1D *h_Data_secTrkLength_Fiducial_barrel                    =    new MnvH1D("h_Data_secTrkLength_Fiducial_barrel",               "h_Data_secTrkLength_Fiducial_barrel",               Recoil_track_length_vector.size()-1, Recoil_track_length_vector.data());
MnvH1D *h_Data_secTrkLength_Fiducial_downstreamConcaveCap      =    new MnvH1D("h_Data_secTrkLength_Fiducial_downstreamConcaveCap", "h_Data_secTrkLength_Fiducial_downstreamConcaveCap", Recoil_track_length_vector.size()-1, Recoil_track_length_vector.data());



MnvH1D *h_Data_secTrk_DOCA_upstreamCap                 =    new MnvH1D("h_Data_secTrk_DOCA_upstreamCap", "h_Data_secTrk_DOCA_upstreamCap", secTrkTrkDOCA_vector.size()-1, secTrkTrkDOCA_vector.data());
MnvH1D *h_Data_secTrk_DOCA_barrel                      =    new MnvH1D("h_Data_secTrk_DOCA_barrel", "h_Data_secTrk_DOCA_barrel", secTrkTrkDOCA_vector.size()-1, secTrkTrkDOCA_vector.data());
MnvH1D *h_Data_secTrk_DOCA_downstreamCap               =    new MnvH1D("h_Data_secTrk_DOCA_downstreamCap", "h_Data_secTrk_DOCA_downstreamCap", secTrkTrkDOCA_vector.size()-1, secTrkTrkDOCA_vector.data());
MnvH1D *h_Data_secTrk_DOCA_downstreamConcaveCap        =    new MnvH1D("h_Data_secTrk_DOCA_downstreamConcaveCap", "h_Data_secTrk_DOCA_downstreamConcaveCap", secTrkTrkDOCA_vector.size()-1, secTrkTrkDOCA_vector.data());

MnvH1D *h_Data_secTrk_DOCA_Fiducial_upstreamCap                 =    new MnvH1D("h_Data_secTrk_DOCA_Fiducial_upstreamCap", "h_Data_secTrk_DOCA_Fiducial_upstreamCap", secTrkTrkDOCA_vector.size()-1, secTrkTrkDOCA_vector.data());
MnvH1D *h_Data_secTrk_DOCA_Fiducial_barrel                      =    new MnvH1D("h_Data_secTrk_DOCA_Fiducial_barrel", "h_Data_secTrk_DOCA_Fiducial_barrel", secTrkTrkDOCA_vector.size()-1, secTrkTrkDOCA_vector.data());
MnvH1D *h_Data_secTrk_DOCA_Fiducial_downstreamCap               =    new MnvH1D("h_Data_secTrk_DOCA_Fiducial_downstreamCap", "h_Data_secTrk_DOCA_Fiducial_downstreamCap", secTrkTrkDOCA_vector.size()-1, secTrkTrkDOCA_vector.data());
MnvH1D *h_Data_secTrk_DOCA_Fiducial_downstreamConcaveCap        =    new MnvH1D("h_Data_secTrk_DOCA_Fiducial_downstreamConcaveCap", "h_Data_secTrk_DOCA_Fiducial_downstreamConcaveCap", secTrkTrkDOCA_vector.size()-1, secTrkTrkDOCA_vector.data());




MnvH1D *h_Data_Distance_to_InnerTank             =           new MnvH1D("h_Data_Distance_to_InnerTank",                       "h_Data_Distance_to_InnerTank",                       Distance_to_innerTank.size()-1, Distance_to_innerTank.data());
MnvH1D *h_Data_Distance_to_InnerTank_upstreamCap =           new MnvH1D("h_Data_Distance_to_InnerTank_upstreamCap",           "h_Data_Distance_to_InnerTank_upstreamCap",           Distance_to_innerTank.size()-1, Distance_to_innerTank.data());
MnvH1D *h_Data_Distance_to_InnerTank_barrel      =           new MnvH1D("h_Data_Distance_to_InnerTank_barrel",                "h_Data_Distance_to_InnerTank_barrel",                Distance_to_innerTank.size()-1, Distance_to_innerTank.data());
MnvH1D *h_Data_Distance_to_InnerTank_downstreamCap =         new MnvH1D("h_Data_Distance_to_InnerTank_downstreamCap",         "h_Data_Distance_to_InnerTank_downstreamCap",         Distance_to_innerTank.size()-1, Distance_to_innerTank.data());
MnvH1D *h_Data_Distance_to_InnerTank_downstreamConcaveCap =  new MnvH1D("h_Data_Distance_to_InnerTank_downstreamConcaveCap",  "h_Data_Distance_to_InnerTank_downstreamConcaveCap",   Distance_to_innerTank.size()-1, Distance_to_innerTank.data());

MnvH1D *h_Data_Distance_to_InnerTank_Fiducial_upstreamCap =           new MnvH1D("h_Data_Distance_to_InnerTank_Fiducial_upstreamCap",           "h_Data_Distance_to_InnerTank_Fiducial_upstreamCap",           Distance_to_innerTank.size()-1, Distance_to_innerTank.data());
MnvH1D *h_Data_Distance_to_InnerTank_Fiducial_barrel      =           new MnvH1D("h_Data_Distance_to_InnerTank_Fiducial_barrel",                "h_Data_Distance_to_InnerTank_Fiducial_barrel",                Distance_to_innerTank.size()-1, Distance_to_innerTank.data());
MnvH1D *h_Data_Distance_to_InnerTank_Fiducial_downstreamCap =         new MnvH1D("h_Data_Distance_to_InnerTank_Fiducial_downstreamCap",         "h_Data_Distance_to_InnerTank_Fiducial_downstreamCap",         Distance_to_innerTank.size()-1, Distance_to_innerTank.data());
MnvH1D *h_Data_Distance_to_InnerTank_Fiducial_downstreamConcaveCap =  new MnvH1D("h_Data_Distance_to_InnerTank_Fiducial_downstreamConcaveCap",  "h_Data_Distance_to_InnerTank_Fiducial_downstreamConcaveCap",   Distance_to_innerTank.size()-1, Distance_to_innerTank.data());




MnvH1D *h_Data_Distance_to_UpstreamCap                       = new MnvH1D("h_Data_Distance_to_UpstreamCap",                     "h_Data_Distance_to_UpstreamCap",                      Distance_to_Caps.size()-1, Distance_to_Caps.data());
MnvH1D *h_Data_Distance_to_UpstreamCap_upstreamCap              = new MnvH1D("h_Data_Distance_to_UpstreamCap_upstreamCap",            "h_Data_Distance_to_UpstreamCap_upstreamCap",             Distance_to_Caps.size()-1, Distance_to_Caps.data());
MnvH1D *h_Data_Distance_to_UpstreamCap_barrel                = new MnvH1D("h_Data_Distance_to_UpstreamCap_barrel",              "h_Data_Distance_to_UpstreamCap_barrel",               Distance_to_Caps.size()-1, Distance_to_Caps.data());
MnvH1D *h_Data_Distance_to_UpstreamCap_downstreamCap         = new MnvH1D("h_Data_Distance_to_UpstreamCap_downstreamCap",       "h_Data_Distance_to_UpstreamCap_downstreamCap",        Distance_to_Caps.size()-1, Distance_to_Caps.data());
MnvH1D *h_Data_Distance_to_UpstreamCap_downstreamConcaveCap  = new MnvH1D("h_Data_Distance_to_UpstreamCap_downstreamConcaveCap","h_Data_Distance_to_UpstreamCap_downstreamConcaveCap", Distance_to_Caps.size()-1, Distance_to_Caps.data());

MnvH1D *h_Data_Distance_to_UpstreamCap_RCut                       = new MnvH1D("h_Data_Distance_to_UpstreamCap_RCut",                     "h_Data_Distance_to_UpstreamCap_RCut",                      Distance_to_Caps.size()-1, Distance_to_Caps.data());
MnvH1D *h_Data_Distance_to_UpstreamCap_RCut_upstreamCap              = new MnvH1D("h_Data_Distance_to_UpstreamCap_RCut_upstreamCap",            "h_Data_Distance_to_UpstreamCap_RCut_upstreamCap",    Distance_to_Caps.size()-1, Distance_to_Caps.data());
MnvH1D *h_Data_Distance_to_UpstreamCap_RCut_barrel                = new MnvH1D("h_Data_Distance_to_UpstreamCap_RCut_barrel",              "h_Data_Distance_to_UpstreamCap_RCut_barrel",               Distance_to_Caps.size()-1, Distance_to_Caps.data());
MnvH1D *h_Data_Distance_to_UpstreamCap_RCut_downstreamCap         = new MnvH1D("h_Data_Distance_to_UpstreamCap_RCut_downstreamCap",       "h_Data_Distance_to_UpstreamCap_RCut_downstreamCap",        Distance_to_Caps.size()-1, Distance_to_Caps.data());
MnvH1D *h_Data_Distance_to_UpstreamCap_RCut_downstreamConcaveCap  = new MnvH1D("h_Data_Distance_to_UpstreamCap_RCut_downstreamConcaveCap","h_Data_Distance_to_UpstreamCap_RCut_downstreamConcaveCap", Distance_to_Caps.size()-1, Distance_to_Caps.data());

MnvH1D *h_Data_Distance_to_DownstreamCap                      =  new MnvH1D("h_Data_Distance_to_DownstreamCap",                      "h_Data_Distance_to_DownstreamCap",                      Distance_to_Caps.size()-1, Distance_to_Caps.data());
MnvH1D *h_Data_Distance_to_DownstreamCap_upstreamCap             =  new MnvH1D("h_Data_Distance_to_DownstreamCap_upstreamCap",             "h_Data_Distance_to_DownstreamCap_upstreamCap",    Distance_to_Caps.size()-1, Distance_to_Caps.data());
MnvH1D *h_Data_Distance_to_DownstreamCap_barrel               =  new MnvH1D("h_Data_Distance_to_DownstreamCap_barrel",               "h_Data_Distance_to_DownstreamCap_barrel",               Distance_to_Caps.size()-1, Distance_to_Caps.data());
MnvH1D *h_Data_Distance_to_DownstreamCap_downstreamCap        =  new MnvH1D("h_Data_Distance_to_DownstreamCap_downstreamCap",        "h_Data_Distance_to_DownstreamCap_downstreamCap",        Distance_to_Caps.size()-1, Distance_to_Caps.data());
MnvH1D *h_Data_Distance_to_DownstreamCap_downstreamConcaveCap =  new MnvH1D("h_Data_Distance_to_DownstreamCap_downstreamConcaveCap", "h_Data_Distance_to_DownstreamCap_downstreamConcaveCap", Distance_to_Caps.size()-1, Distance_to_Caps.data());

MnvH1D *h_Data_Distance_to_DownstreamCap_RCut                      =  new MnvH1D("h_Data_Distance_to_DownstreamCap_RCut",                      "h_Data_Distance_to_DownstreamCap_RCut",                      Distance_to_Caps.size()-1, Distance_to_Caps.data());
MnvH1D *h_Data_Distance_to_DownstreamCap_RCut_upstreamCap          =  new MnvH1D("h_Data_Distance_to_DownstreamCap_RCut_upstreamCap",             "h_Data_Distance_to_DownstreamCap_RCut_upstreamCap",       Distance_to_Caps.size()-1, Distance_to_Caps.data());
MnvH1D *h_Data_Distance_to_DownstreamCap_RCut_barrel               =  new MnvH1D("h_Data_Distance_to_DownstreamCap_RCut_barrel",               "h_Data_Distance_to_DownstreamCap_RCut_barrel",               Distance_to_Caps.size()-1, Distance_to_Caps.data());
MnvH1D *h_Data_Distance_to_DownstreamCap_RCut_downstreamCap        =  new MnvH1D("h_Data_Distance_to_DownstreamCap_RCut_downstreamCap",        "h_Data_Distance_to_DownstreamCap_RCut_downstreamCap",        Distance_to_Caps.size()-1, Distance_to_Caps.data());
MnvH1D *h_Data_Distance_to_DownstreamCap_RCut_downstreamConcaveCap =  new MnvH1D("h_Data_Distance_to_DownstreamCap_RCut_downstreamConcaveCap", "h_Data_Distance_to_DownstreamCap_RCut_downstreamConcaveCap", Distance_to_Caps.size()-1, Distance_to_Caps.data());


MnvH1D *h_Data_MuonE_upstreamCap       =    new MnvH1D("h_Data_MuonE_upstreamCap", "h_Data_MuonE_upstreamCap",       Ebin_vector.size()-1, Ebin_vector.data());
MnvH1D *h_Data_MuonPT_upstreamCap      =    new MnvH1D("h_Data_MuonPT_upstreamCap", "h_Data_MuonPT_upstreamCap",     PTbin_vector.size()-1, PTbin_vector.data());
MnvH1D *h_Data_MuonPZ_upstreamCap      =    new MnvH1D("h_Data_MuonPZ_upstreamCap", "h_Data_MuonPZ_upstreamCap",     Pzbin_vector.size()-1, Pzbin_vector.data());
MnvH1D *h_Data_MuonTheta_upstreamCap   =    new MnvH1D("h_Data_MuonTheta_upstreamCap", "h_Data_MuonTheta_upstreamCap",        MuonThetabin_vector.size()-1, MuonThetabin_vector.data());
MnvH1D *h_Data_MuonDOCA_upstreamCap    =    new MnvH1D("h_Data_MuonDOCA_upstreamCap", "h_Data_MuonDOCA_upstreamCap", Vertex_DOCAbin_vector.size()-1, Vertex_DOCAbin_vector.data());

MnvH1D *h_Data_MuonE_barrel       =    new MnvH1D("h_Data_MuonE_barrel", "h_Data_MuonE_barrel",       Ebin_vector.size()-1, Ebin_vector.data());
MnvH1D *h_Data_MuonPT_barrel      =    new MnvH1D("h_Data_MuonPT_barrel", "h_Data_MuonPT_barrel",     PTbin_vector.size()-1, PTbin_vector.data());
MnvH1D *h_Data_MuonPZ_barrel      =    new MnvH1D("h_Data_MuonPZ_barrel", "h_Data_MuonPZ_barrel",     Pzbin_vector.size()-1, Pzbin_vector.data());
MnvH1D *h_Data_MuonTheta_barrel   =    new MnvH1D("h_Data_MuonTheta_barrel", "h_Data_MuonTheta_barrel",        MuonThetabin_vector.size()-1, MuonThetabin_vector.data());
MnvH1D *h_Data_MuonDOCA_barrel    =    new MnvH1D("h_Data_MuonDOCA_barrel", "h_Data_MuonDOCA_barrel", Vertex_DOCAbin_vector.size()-1, Vertex_DOCAbin_vector.data());

MnvH1D *h_Data_MuonE_downstreamCap       =    new MnvH1D("h_Data_MuonE_downstreamCap", "h_Data_MuonE_downstreamCap",       Ebin_vector.size()-1, Ebin_vector.data());
MnvH1D *h_Data_MuonPT_downstreamCap      =    new MnvH1D("h_Data_MuonPT_downstreamCap", "h_Data_MuonPT_downstreamCap",     PTbin_vector.size()-1, PTbin_vector.data());
MnvH1D *h_Data_MuonPZ_downstreamCap      =    new MnvH1D("h_Data_MuonPZ_downstreamCap", "h_Data_MuonPZ_downstreamCap",     Pzbin_vector.size()-1, Pzbin_vector.data());
MnvH1D *h_Data_MuonTheta_downstreamCap   =    new MnvH1D("h_Data_MuonTheta_downstreamCap", "h_Data_MuonTheta_downstreamCap",        MuonThetabin_vector.size()-1, MuonThetabin_vector.data());
MnvH1D *h_Data_MuonDOCA_downstreamCap    =    new MnvH1D("h_Data_MuonDOCA_downstreamCap", "h_Data_MuonDOCA_downstreamCap", Vertex_DOCAbin_vector.size()-1, Vertex_DOCAbin_vector.data());

MnvH1D *h_Data_MuonE_downstreamConcaveCap       =    new MnvH1D("h_Data_MuonE_downstreamConcaveCap", "h_Data_MuonE_downstreamConcaveCap",       Ebin_vector.size()-1, Ebin_vector.data());
MnvH1D *h_Data_MuonPT_downstreamConcaveCap      =    new MnvH1D("h_Data_MuonPT_downstreamConcaveCap", "h_Data_MuonPT_downstreamConcaveCap",     PTbin_vector.size()-1, PTbin_vector.data());
MnvH1D *h_Data_MuonPZ_downstreamConcaveCap      =    new MnvH1D("h_Data_MuonPZ_downstreamConcaveCap", "h_Data_MuonPZ_downstreamConcaveCap",     Pzbin_vector.size()-1, Pzbin_vector.data());
MnvH1D *h_Data_MuonTheta_downstreamConcaveCap   =    new MnvH1D("h_Data_MuonTheta_downstreamConcaveCap", "h_Data_MuonTheta_downstreamConcaveCap",        MuonThetabin_vector.size()-1, MuonThetabin_vector.data());
MnvH1D *h_Data_MuonDOCA_downstreamConcaveCap    =    new MnvH1D("h_Data_MuonDOCA_downstreamConcaveCap", "h_Data_MuonDOCA_downstreamConcaveCap", Vertex_DOCAbin_vector.size()-1, Vertex_DOCAbin_vector.data());
////////////////////////////////
//
/////////////////////////////////
MnvH1D *h_Data_MuonE_Fiducial_upstreamCap       =    new MnvH1D("h_Data_MuonE_Fiducial_upstreamCap", "h_Data_MuonE_Fiducial_upstreamCap",       Ebin_vector.size()-1, Ebin_vector.data());
MnvH1D *h_Data_MuonPT_Fiducial_upstreamCap      =    new MnvH1D("h_Data_MuonPT_Fiducial_upstreamCap", "h_Data_MuonPT_Fiducial_upstreamCap",     PTbin_vector.size()-1, PTbin_vector.data());
MnvH1D *h_Data_MuonPZ_Fiducial_upstreamCap      =    new MnvH1D("h_Data_MuonPZ_Fiducial_upstreamCap", "h_Data_MuonPZ_Fiducial_upstreamCap",     Pzbin_vector.size()-1, Pzbin_vector.data());
MnvH1D *h_Data_MuonTheta_Fiducial_upstreamCap   =    new MnvH1D("h_Data_MuonTheta_Fiducial_upstreamCap", "h_Data_MuonTheta_Fiducial_upstreamCap",        MuonThetabin_vector.size()-1, MuonThetabin_vector.data());
MnvH1D *h_Data_MuonDOCA_Fiducial_upstreamCap    =    new MnvH1D("h_Data_MuonDOCA_Fiducial_upstreamCap", "h_Data_MuonDOCA_Fiducial_upstreamCap", Vertex_DOCAbin_vector.size()-1, Vertex_DOCAbin_vector.data());

MnvH1D *h_Data_MuonE_Fiducial_barrel       =    new MnvH1D("h_Data_MuonE_Fiducial_barrel", "h_Data_MuonE_Fiducial_barrel",       Ebin_vector.size()-1, Ebin_vector.data());
MnvH1D *h_Data_MuonPT_Fiducial_barrel      =    new MnvH1D("h_Data_MuonPT_Fiducial_barrel", "h_Data_MuonPT_Fiducial_barrel",     PTbin_vector.size()-1, PTbin_vector.data());
MnvH1D *h_Data_MuonPZ_Fiducial_barrel      =    new MnvH1D("h_Data_MuonPZ_Fiducial_barrel", "h_Data_MuonPZ_Fiducial_barrel",     Pzbin_vector.size()-1, Pzbin_vector.data());
MnvH1D *h_Data_MuonTheta_Fiducial_barrel   =    new MnvH1D("h_Data_MuonTheta_Fiducial_barrel", "h_Data_MuonTheta_Fiducial_barrel",        MuonThetabin_vector.size()-1, MuonThetabin_vector.data());
MnvH1D *h_Data_MuonDOCA_Fiducial_barrel    =    new MnvH1D("h_Data_MuonDOCA_Fiducial_barrel", "h_Data_MuonDOCA_Fiducial_barrel", Vertex_DOCAbin_vector.size()-1, Vertex_DOCAbin_vector.data());

MnvH1D *h_Data_MuonE_Fiducial_downstreamCap       =    new MnvH1D("h_Data_MuonE_Fiducial_downstreamCap", "h_Data_MuonE_Fiducial_downstreamCap",       Ebin_vector.size()-1, Ebin_vector.data());
MnvH1D *h_Data_MuonPT_Fiducial_downstreamCap      =    new MnvH1D("h_Data_MuonPT_Fiducial_downstreamCap", "h_Data_MuonPT_Fiducial_downstreamCap",     PTbin_vector.size()-1, PTbin_vector.data());
MnvH1D *h_Data_MuonPZ_Fiducial_downstreamCap      =    new MnvH1D("h_Data_MuonPZ_Fiducial_downstreamCap", "h_Data_MuonPZ_Fiducial_downstreamCap",     Pzbin_vector.size()-1, Pzbin_vector.data());
MnvH1D *h_Data_MuonTheta_Fiducial_downstreamCap   =    new MnvH1D("h_Data_MuonTheta_Fiducial_downstreamCap", "h_Data_MuonTheta_Fiducial_downstreamCap",        MuonThetabin_vector.size()-1, MuonThetabin_vector.data());
MnvH1D *h_Data_MuonDOCA_Fiducial_downstreamCap    =    new MnvH1D("h_Data_MuonDOCA_Fiducial_downstreamCap", "h_Data_MuonDOCA_Fiducial_downstreamCap", Vertex_DOCAbin_vector.size()-1, Vertex_DOCAbin_vector.data());

MnvH1D *h_Data_MuonE_Fiducial_downstreamConcaveCap       =    new MnvH1D("h_Data_MuonE_Fiducial_downstreamConcaveCap", "h_Data_MuonE_Fiducial_downstreamConcaveCap",       Ebin_vector.size()-1, Ebin_vector.data());
MnvH1D *h_Data_MuonPT_Fiducial_downstreamConcaveCap      =    new MnvH1D("h_Data_MuonPT_Fiducial_downstreamConcaveCap", "h_Data_MuonPT_Fiducial_downstreamConcaveCap",     PTbin_vector.size()-1, PTbin_vector.data());
MnvH1D *h_Data_MuonPZ_Fiducial_downstreamConcaveCap      =    new MnvH1D("h_Data_MuonPZ_Fiducial_downstreamConcaveCap", "h_Data_MuonPZ_Fiducial_downstreamConcaveCap",     Pzbin_vector.size()-1, Pzbin_vector.data());
MnvH1D *h_Data_MuonTheta_Fiducial_downstreamConcaveCap   =    new MnvH1D("h_Data_MuonTheta_Fiducial_downstreamConcaveCap", "h_Data_MuonTheta_Fiducial_downstreamConcaveCap",        MuonThetabin_vector.size()-1, MuonThetabin_vector.data());
MnvH1D *h_Data_MuonDOCA_Fiducial_downstreamConcaveCap    =    new MnvH1D("h_Data_MuonDOCA_Fiducial_downstreamConcaveCap", "h_Data_MuonDOCA_Fiducial_downstreamConcaveCap", Vertex_DOCAbin_vector.size()-1, Vertex_DOCAbin_vector.data());



MnvH1D *h_Data_secTrk_angle_upstreamCap             =    new MnvH1D("h_Data_secTrk_angle_upstreamCap", "h_Data_secTrk_angle_upstreamCap", secTrkTheta_vector.size()-1, secTrkTheta_vector.data());
MnvH1D *h_Data_secTrk_angle_barrel                  =    new MnvH1D("h_Data_secTrk_angle_barrel", "h_Data_secTrk_angle_barrel", secTrkTheta_vector.size()-1, secTrkTheta_vector.data());
MnvH1D *h_Data_secTrk_angle_downstreamCap           =    new MnvH1D("h_Data_secTrk_angle_downstreamCap", "h_Data_secTrk_angle_downstreamCap", secTrkTheta_vector.size()-1, secTrkTheta_vector.data());
MnvH1D *h_Data_secTrk_angle_downstreamConcaveCap    =    new MnvH1D("h_Data_secTrk_angle_downstreamConcaveCap", "h_Data_secTrk_angle_downstreamConcaveCap", secTrkTheta_vector.size()-1, secTrkTheta_vector.data());

MnvH1D *h_Data_secTrk_angle_Fiducial_upstreamCap             =    new MnvH1D("h_Data_secTrk_angle_Fiducial_upstreamCap",          "h_Data_secTrk_angle_Fiducial_upstreamCap", secTrkTheta_vector.size()-1, secTrkTheta_vector.data());
MnvH1D *h_Data_secTrk_angle_Fiducial_barrel                  =    new MnvH1D("h_Data_secTrk_angle_Fiducial_barrel",               "h_Data_secTrk_angle_Fiducial_barrel", secTrkTheta_vector.size()-1, secTrkTheta_vector.data());
MnvH1D *h_Data_secTrk_angle_Fiducial_downstreamCap           =    new MnvH1D("h_Data_secTrk_angle_Fiducial_downstreamCap",        "h_Data_secTrk_angle_Fiducial_downstreamCap", secTrkTheta_vector.size()-1, secTrkTheta_vector.data());
MnvH1D *h_Data_secTrk_angle_Fiducial_downstreamConcaveCap    =    new MnvH1D("h_Data_secTrk_angle_Fiducial_downstreamConcaveCap", "h_Data_secTrk_angle_Fiducial_downstreamConcaveCap", secTrkTheta_vector.size()-1, secTrkTheta_vector.data());


////////////////
//Vertex Hist///
////////////////
MnvH1D *h_Data_CryoVertex_X                       =    new MnvH1D("h_Data_CryoVertex_X",                      "h_Data_CryoVertex_X",                      Vertex_Xbin_vector.size()-1, Vertex_Xbin_vector.data());
MnvH1D  *h_Data_CryoVertex_X_upstreamCap          =    new MnvH1D("h_Data_CryoVertex_X_upstreamCap",          "h_Data_CryoVertex_X_upstreamCap",          Vertex_Xbin_vector.size()-1, Vertex_Xbin_vector.data());
MnvH1D  *h_Data_CryoVertex_X_barrel               =    new MnvH1D("h_Data_CryoVertex_X_barrel",               "h_Data_CryoVertex_X_barrel",               Vertex_Xbin_vector.size()-1, Vertex_Xbin_vector.data());
MnvH1D  *h_Data_CryoVertex_X_downstreamCap        =    new MnvH1D("h_Data_CryoVertex_X_downstreamCap",        "h_Data_CryoVertex_X_downstreamCap",        Vertex_Xbin_vector.size()-1, Vertex_Xbin_vector.data());
MnvH1D  *h_Data_CryoVertex_X_downstreamConcaveCap =    new MnvH1D("h_Data_CryoVertex_X_downstreamConcaveCap", "h_Data_CryoVertex_X_downstreamConcaveCap", Vertex_Xbin_vector.size()-1, Vertex_Xbin_vector.data());

MnvH1D  *h_Data_CryoVertex_X_Fiducial_upstreamCap          =    new MnvH1D("h_Data_CryoVertex_X_Fiducial_upstreamCap",          "h_Data_CryoVertex_X_Fiducial_upstreamCap",          Vertex_Xbin_vector.size()-1, Vertex_Xbin_vector.data());
MnvH1D  *h_Data_CryoVertex_X_Fiducial_barrel               =    new MnvH1D("h_Data_CryoVertex_X_Fiducial_barrel",               "h_Data_CryoVertex_X_Fiducial_barrel",               Vertex_Xbin_vector.size()-1, Vertex_Xbin_vector.data());
MnvH1D  *h_Data_CryoVertex_X_Fiducial_downstreamCap        =    new MnvH1D("h_Data_CryoVertex_X_Fiducial_downstreamCap",        "h_Data_CryoVertex_X_Fiducial_downstreamCap",        Vertex_Xbin_vector.size()-1, Vertex_Xbin_vector.data());
MnvH1D  *h_Data_CryoVertex_X_Fiducial_downstreamConcaveCap =    new MnvH1D("h_Data_CryoVertex_X_Fiducial_downstreamConcaveCap", "h_Data_CryoVertex_X_Fiducial_downstreamConcaveCap", Vertex_Xbin_vector.size()-1, Vertex_Xbin_vector.data());

MnvH1D  *h_Data_CryoVertex_Y                      =    new MnvH1D("h_Data_CryoVertex_Y",                      "h_Data_CryoVertex_Y",                      Vertex_Ybin_vector.size()-1, Vertex_Ybin_vector.data());
MnvH1D  *h_Data_CryoVertex_Y_upstreamCap          =    new MnvH1D("h_Data_CryoVertex_Y_upstreamCap",          "h_Data_CryoVertex_Y_upstreamCap",          Vertex_Ybin_vector.size()-1, Vertex_Ybin_vector.data());
MnvH1D  *h_Data_CryoVertex_Y_barrel               =    new MnvH1D("h_Data_CryoVertex_Y_barrel",               "h_Data_CryoVertex_Y_barrel",               Vertex_Ybin_vector.size()-1, Vertex_Ybin_vector.data());
MnvH1D  *h_Data_CryoVertex_Y_downstreamCap        =    new MnvH1D("h_Data_CryoVertex_Y_downstreamCap",        "h_Data_CryoVertex_Y_downstreamCap",        Vertex_Ybin_vector.size()-1, Vertex_Ybin_vector.data());
MnvH1D  *h_Data_CryoVertex_Y_downstreamConcaveCap =    new MnvH1D("h_Data_CryoVertex_Y_downstreamConcaveCap", "h_Data_CryoVertex_Y_downstreamConcaveCap", Vertex_Ybin_vector.size()-1, Vertex_Ybin_vector.data());

MnvH1D  *h_Data_CryoVertex_Y_Fiducial_upstreamCap          =    new MnvH1D("h_Data_CryoVertex_Y_Fiducial_upstreamCap",          "h_Data_CryoVertex_Y_Fiducial_upstreamCap",          Vertex_Ybin_vector.size()-1, Vertex_Ybin_vector.data());
MnvH1D  *h_Data_CryoVertex_Y_Fiducial_barrel               =    new MnvH1D("h_Data_CryoVertex_Y_Fiducial_barrel",               "h_Data_CryoVertex_Y_Fiducial_barrel",               Vertex_Ybin_vector.size()-1, Vertex_Ybin_vector.data());
MnvH1D  *h_Data_CryoVertex_Y_Fiducial_downstreamCap        =    new MnvH1D("h_Data_CryoVertex_Y_Fiducial_downstreamCap",        "h_Data_CryoVertex_Y_Fiducial_downstreamCap",        Vertex_Ybin_vector.size()-1, Vertex_Ybin_vector.data());
MnvH1D  *h_Data_CryoVertex_Y_Fiducial_downstreamConcaveCap =    new MnvH1D("h_Data_CryoVertex_Y_Fiducial_downstreamConcaveCap", "h_Data_CryoVertex_Y_Fiducial_downstreamConcaveCap", Vertex_Ybin_vector.size()-1, Vertex_Ybin_vector.data());


MnvH1D *h_Data_CryoVertex_Z                      =    new MnvH1D("h_Data_CryoVertex_Z",                      "h_Data_CryoVertex_Z",                      Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());
MnvH1D *h_Data_CryoVertex_Z_upstreamCap          =    new MnvH1D("h_Data_CryoVertex_Z_upstreamCap",          "h_Data_CryoVertex_Z_upstreamCap",          Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());
MnvH1D *h_Data_CryoVertex_Z_barrel               =    new MnvH1D("h_Data_CryoVertex_Z_barrel",               "h_Data_CryoVertex_Z_barrel",               Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());
MnvH1D *h_Data_CryoVertex_Z_downstreamCap        =    new MnvH1D("h_Data_CryoVertex_Z_downstreamCap",        "h_Data_CryoVertex_Z_downstreamCap",        Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());
MnvH1D *h_Data_CryoVertex_Z_downstreamConcaveCap =    new MnvH1D("h_Data_CryoVertex_Z_downstreamConcaveCap", "h_Data_CryoVertex_Z_downstreamConcaveCap", Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());

MnvH1D *h_Data_CryoVertex_Z_Fiducial_upstreamCap          =    new MnvH1D("h_Data_CryoVertex_Z_Fiducial_upstreamCap",          "h_Data_CryoVertex_Z_Fiducial_upstreamCap",          Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());
MnvH1D *h_Data_CryoVertex_Z_Fiducial_barrel               =    new MnvH1D("h_Data_CryoVertex_Z_Fiducial_barrel",               "h_Data_CryoVertex_Z_Fiducial_barrel",               Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());
MnvH1D *h_Data_CryoVertex_Z_Fiducial_downstreamCap        =    new MnvH1D("h_Data_CryoVertex_Z_Fiducial_downstreamCap",        "h_Data_CryoVertex_Z_Fiducial_downstreamCap",        Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());
MnvH1D *h_Data_CryoVertex_Z_Fiducial_downstreamConcaveCap =    new MnvH1D("h_Data_CryoVertex_Z_Fiducial_downstreamConcaveCap", "h_Data_CryoVertex_Z_Fiducial_downstreamConcaveCap", Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());




MnvH1D *h_Data_CryoVertex_Z_RCut                       =    new MnvH1D("h_Data_CryoVertex_Z_RCut",                       "h_Data_CryoVertex_Z_RCut", Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());
MnvH1D *h_Data_CryoVertex_Z_RCut_upstreamCap           =    new MnvH1D("h_Data_CryoVertex_Z_RCut_upstreamCap",           "h_Data_CryoVertex_Z_RCut_upstreamCap", Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());
MnvH1D *h_Data_CryoVertex_Z_RCut_barrel                =    new MnvH1D("h_Data_CryoVertex_Z_RCut_barrel",                "h_Data_CryoVertex_Z_RCut_barrel", Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());
MnvH1D *h_Data_CryoVertex_Z_RCut_downstreamCap         =    new MnvH1D("h_Data_CryoVertex_Z_RCut_downstreamCap",         "h_Data_CryoVertex_Z_RCut_downstreamCap", Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());
MnvH1D *h_Data_CryoVertex_Z_RCut_downstreamConcaveCap  =    new MnvH1D("h_Data_CryoVertex_Z_RCut_downstreamConcaveCap", "h_Data_CryoVertex_Z_RCut_downstreamConcaveCap", Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());


MnvH1D *h_Data_CryoVertex_R                       =    new MnvH1D("h_Data_CryoVertex_R",                        "h_Data_CryoVertex_R", Vertex_Rbin_vector.size()-1, Vertex_Rbin_vector.data());
MnvH1D *h_Data_CryoVertex_R_upstreamCap           =    new MnvH1D("h_Data_CryoVertex_R_upstreamCap",            "h_Data_CryoVertex_R_upstreamCap",           Vertex_Rbin_vector.size()-1, Vertex_Rbin_vector.data());
MnvH1D *h_Data_CryoVertex_R_barrel                =    new MnvH1D("h_Data_CryoVertex_R_barrel",                 "h_Data_CryoVertex_R_barrel",                Vertex_Rbin_vector.size()-1, Vertex_Rbin_vector.data());
MnvH1D *h_Data_CryoVertex_R_downstreamCap         =    new MnvH1D("h_Data_CryoVertex_R_downstreamCap",          "h_Data_CryoVertex_R_downstreamCap",         Vertex_Rbin_vector.size()-1, Vertex_Rbin_vector.data());
MnvH1D *h_Data_CryoVertex_R_downstreamConcaveCap  =     new MnvH1D("h_Data_CryoVertex_R_downstreamConcaveCap",  "h_Data_CryoVertex_R_downstreamConcaveCap", Vertex_Rbin_vector.size()-1, Vertex_Rbin_vector.data());

MnvH1D *h_Data_CryoVertex_R_Fiducial_upstreamCap           =    new MnvH1D("h_Data_CryoVertex_R_Fiducial_upstreamCap",            "h_Data_CryoVertex_R_Fiducial_upstreamCap",           Vertex_Rbin_vector.size()-1, Vertex_Rbin_vector.data());
MnvH1D *h_Data_CryoVertex_R_Fiducial_barrel                =    new MnvH1D("h_Data_CryoVertex_R_Fiducial_barrel",                 "h_Data_CryoVertex_R_Fiducial_barrel",                Vertex_Rbin_vector.size()-1, Vertex_Rbin_vector.data());
MnvH1D *h_Data_CryoVertex_R_Fiducial_downstreamCap         =    new MnvH1D("h_Data_CryoVertex_R_Fiducial_downstreamCap",          "h_Data_CryoVertex_R_Fiducial_downstreamCap",         Vertex_Rbin_vector.size()-1, Vertex_Rbin_vector.data());
MnvH1D *h_Data_CryoVertex_R_Fiducial_downstreamConcaveCap  =     new MnvH1D("h_Data_CryoVertex_R_Fiducial_downstreamConcaveCap",  "h_Data_CryoVertex_R_Fiducial_downstreamConcaveCap", Vertex_Rbin_vector.size()-1, Vertex_Rbin_vector.data());




MnvH1D *h_Data_CryoVertex_RR                        =    new MnvH1D("h_Data_CryoVertex_RR",                        "h_Data_CryoVertex_RR", Vertex_RRbin_vector.size()-1, Vertex_RRbin_vector.data());
MnvH1D *h_Data_CryoVertex_RR_upstreamCap            =    new MnvH1D("h_Data_CryoVertex_RR_upstreamCap",            "h_Data_CryoVertex_RR_upstreamCap",           Vertex_RRbin_vector.size()-1, Vertex_RRbin_vector.data());
MnvH1D *h_Data_CryoVertex_RR_barrel                 =    new MnvH1D("h_Data_CryoVertex_RR_barrel",                 "h_Data_CryoVertex_RR_barrel",                Vertex_RRbin_vector.size()-1, Vertex_RRbin_vector.data());
MnvH1D *h_Data_CryoVertex_RR_downstreamCap          =    new MnvH1D("h_Data_CryoVertex_RR_downstreamCap",          "h_Data_CryoVertex_RR_downstreamCap",         Vertex_RRbin_vector.size()-1, Vertex_RRbin_vector.data());
MnvH1D *h_Data_CryoVertex_RR_downstreamConcaveCap   =     new MnvH1D("h_Data_CryoVertex_RR_downstreamConcaveCap",  "h_Data_CryoVertex_RR_downstreamConcaveCap", Vertex_RRbin_vector.size()-1, Vertex_RRbin_vector.data());

MnvH1D *h_Data_CryoVertexChiSqFit      =    new MnvH1D("h_Data_CryoVertexChiSqFit", "h_Data_CryoVertexChiSqFit", Vertex_ChiSqFit_vector.size()-1, Vertex_ChiSqFit_vector.data());

PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType> h_Data_CryoVertexChiSqFit_TrackType =
PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType>(TrackType_Category, "h_Data_CryoVertexChiSqFit_TrackType", Vertex_ChiSqFit_vector ,"h_Data_CryoVertexChiSqFit_TrackType; [mm];Events");


PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType> h_Data_CryoVertex_Z_TrackType =
PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType>(TrackType_Category, "h_Data_CryoVertex_Z_TrackType", Vertex_Zbin_vector ,"h_Data_CryoVertex_Z_TrackType; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions> h_Data_CryoVertex_Z_vertex =
PlotUtils::HistFolio<PlotUtils::MnvH1D, VertexOptions>(VertexOptions_Category, "h_Data_CryoVertex_Z_vertex", Vertex_Zbin_vector ,"h_Data_CryoVertex_Z_vertex; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack> h_Data_CryoVertex_Z_Ntracks =
PlotUtils::HistFolio<PlotUtils::MnvH1D, boolNTrack>(boolNTrack_Category, "h_Data_CryoVertex_Z_Ntracks", Vertex_Zbin_vector ,"h_Data_CryoVertex_Z_Ntracks; [mm];Events");





std::vector<double> Vertex_Rbins_vectorMOREbins_vec = {0,50,100,150,200,250,300,350,400,450,500,550,600,650,700,750,800,850,900,950,1000,1050,1100,1150,1200,1250 };
std::vector<double> Vertex_RRbins_vectorMOREbins_vec;
for(auto cat : Vertex_Rbins_vectorMOREbins_vec ) {Vertex_RRbins_vectorMOREbins_vec.push_back(cat * cat);}


MnvH1D *h_Data_SmearingCryoVertex_R      =    new MnvH1D("h_Data_SmearingCryoVertex_R", "h_Data_SmearingCryoVertex_R", Vertex_Rbins_vectorMOREbins_vec.size()-1, Vertex_Rbins_vectorMOREbins_vec.data());

MnvH1D *h_Data_Smearing_Center_region_CryoVertex_R      =    new MnvH1D("h_Data_Smearing_Center_region_CryoVertex_R", "h_Data_Smearing_Center_region_CryoVertex_R",    Vertex_Rbin_vector.size()-1,  Vertex_Rbin_vector.data());
MnvH1D *h_Data_Smearing_Center_region_CryoVertex_RR      =    new MnvH1D("h_Data_Smearing_Center_region_CryoVertex_RR", "h_Data_Smearing_Center_region_CryoVertex_RR", Vertex_RRbin_vector.size()-1, Vertex_RRbin_vector.data());
MnvH1D *h_Data_CryoVertex_Z_Center      =    new MnvH1D("h_Data_CryoVertex_Z_Center", "h_Data_CryoVertex_Z_Center", Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());

/////////////
//2nd Trk Plots
/////////////
MnvH1D *h_Data_secTrk_DOCA                 =    new MnvH1D("h_Data_secTrk_DOCA", "h_Data_secTrk_DOCA", secTrkTrkDOCA_vector.size()-1, secTrkTrkDOCA_vector.data());
MnvH1D *h_Data_secTrk_Pathlength          =    new MnvH1D("h_Data_secTrk_Pathlength", "h_Data_secTrk_Pathlength", secTrkPathway_vector.size()-1, secTrkPathway_vector.data());
MnvH1D *h_Data_secTrk_Energy               =    new MnvH1D("h_Data_secTrk_Energy", "h_Data_secTrk_Energy", secTrkEbin_vector.size()-1, secTrkEbin_vector.data());
MnvH1D *h_Data_secTrk_MidAngle             =    new MnvH1D("h_Data_secTrk_MidAngle", "h_Data_secTrk_MidAngle", secTrkThetamid_vector.size()-1, secTrkThetamid_vector.data());
MnvH1D *h_Data_secTrk_Openangle            =    new MnvH1D("h_Data_secTrk_Openangle", "h_Data_secTrk_Openangle", secTrkThetamid_vector.size()-1, secTrkThetamid_vector.data());


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

std::vector<Vertex_XYZ> UpstreamBugle_vector;
std::vector<Vertex_XYZ> DownstreamBugle_vector;
std::vector<Vertex_XYZ> CenterBugle_vector;


std::vector<Vertex_XYZ> UpstreamCap_vector;
std::vector<Vertex_XYZ> barrel_vector;
std::vector<Vertex_XYZ> DownstreamCap_vector;
std::vector<Vertex_XYZ> downstreamConcaveCap_vector;

std::vector<Vertex_XYZ> UpstreamCap_RCut_vector;
std::vector<Vertex_XYZ> barrel_RCut_vector;
std::vector<Vertex_XYZ> DownstreamCap_RCut_vector;
std::vector<Vertex_XYZ> downstreamConcaveCap_RCut_vector;


std::vector<double> VertexZbins_coarse{1450, 1750.00, 2050.00, 2250, 2450, 2650, 2850, 3000, 3200,  3400, 3650, 3900, 4200, 4350};
std::vector<double> VertexRbins_coarse{0, 200, 400, 600,  700,   800,  1000,  1200};
std::vector<double> VertexXYbins_coarse{-1200, -1000, -800, -600, -400, -200, 0, 200, 400, 600, 800, 1000, 1200};
std::vector<double> bigAngle_bins{0.0, 15.0, 30.0, 45.0, 60.0};

MnvH2D *h_2d_Data_vertexZ_openAngle            =    new MnvH2D("h_2d_Data_vertexZ_openAngle", "h_2d_Data_vertexZ_openAngle",VertexZbins_coarse.size()-1, VertexZbins_coarse.data() ,bigAngle_bins.size()-1, bigAngle_bins.data()  );
MnvH2D *h_2d_Data_vertexR_openAngle            =    new MnvH2D("h_2d_Data_vertexR_openAngle", "h_2d_Data_vertexR_openAngle",VertexRbins_coarse.size()-1, VertexRbins_coarse.data() ,bigAngle_bins.size()-1, bigAngle_bins.data()  );
MnvH2D *h_2d_Data_vertexX_openAngle            =    new MnvH2D("h_2d_Data_vertexX_openAngle", "h_2d_Data_vertexX_openAngle",VertexXYbins_coarse.size()-1, VertexXYbins_coarse.data() ,bigAngle_bins.size()-1, bigAngle_bins.data()  );
MnvH2D *h_2d_Data_vertexY_openAngle            =    new MnvH2D("h_2d_Data_vertexY_openAngle", "h_2d_Data_vertexY_openAngle",VertexXYbins_coarse.size()-1, VertexXYbins_coarse.data() ,bigAngle_bins.size()-1, bigAngle_bins.data()  );

MnvH2D *h_2d_Data_Vertex_Z_R            =    new MnvH2D("h_2d_Data_Vertex_Z_R", "h_2d_Data_Vertex_Z_R", VertexZbins_coarse.size()-1, VertexZbins_coarse.data() ,VertexRbins_coarse.size()-1, VertexRbins_coarse.data()  );
MnvH2D *h_2d_Data_Vertex_Z_X            =    new MnvH2D("h_2d_Data_Vertex_Z_X", "h_2d_Data_Vertex_Z_X",VertexZbins_coarse.size()-1,VertexZbins_coarse.data() ,VertexXYbins_coarse.size()-1, VertexXYbins_coarse.data()  );
MnvH2D *h_2d_Data_Vertex_Z_Y            =    new MnvH2D("h_2d_Data_Vertex_Z_Y", "h_2d_Data_Vertex_Z_Y",VertexZbins_coarse.size()-1,VertexZbins_coarse.data() ,VertexXYbins_coarse.size()-1, VertexXYbins_coarse.data()  );
MnvH2D *h_2d_Data_Vertex_X_Y            =    new MnvH2D("h_2d_Data_Vertex_X_Y", "h_2d_Data_Vertex_X_Y",VertexXYbins_coarse.size()-1,VertexXYbins_coarse.data() ,VertexXYbins_coarse.size()-1, VertexXYbins_coarse.data()  );




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


//////////////////////////////////////////////////////////////////////////
// Data Loop ME_playlist_1A_BranchesADDED
//////////////////////////////////////////////////////////////////////////
gSystem->GetProcInfo(&procInfo);
std::cout<<"On Playlist: "<<Playlist_Info.GetPlaylistname() << "Mem2: " << procInfo.fMemResident << "\n";
//auto Playlist_txtFILEPath = GetPlaylist_txtFILE_path("1F_flagflip",  isNOT_mc );
auto Playlist_txtFILEPath = GetPlaylist_txtFILE_path(PlayList_iterator, isNOT_mc );

std::cout<<"Pathway of Root files = "<< Playlist_txtFILEPath<<std::endl;
//PlotUtils::ChainWrapper* chw_Data  = makeChainWrapperPtr("../playlists/Data_Playlist/ME_1A_DATA.txt", "Muon");
//PlotUtils::ChainWrapper* chw_Data  = makeChainWrapperPtr("../playlists/Data_Playlist/ME_1P_DATA.txt", "Muon");
PlotUtils::ChainWrapper* chw_Data  = makeChainWrapperPtr(Playlist_txtFILEPath.c_str(), "HeAnaTupleTool");
//PlotUtils::ChainWrapper* datachainPOT = makeChainWrapperPtr(Playlist_txtFILEPath.c_str(), "Meta");
//std::map< std::string, std::vector<HeliumCVUniverse*> > data_error_bands = GetErrorBands(chw_Data);
auto dataPOT = 1.0;//GetPOT(datachainPOT);
//std::cout << "POT of MC = "<< dataPOT<<std::endl;
HeliumCVUniverse* dataEvt = new HeliumCVUniverse(chw_Data);
auto intial_playlist = GetPlaylist_InitialName(PlayList_iterator);
const std::string RootName = GetPlaylist_ROOT_path(intial_playlist, isNOT_mc );
//auto intial_playlist = GetPlaylist_InitialName(PlayList_iterator);
//const std::string RootName = GetPlaylist_ROOT_path(intial_playlist, isNOT_mc );

std::cout << "rootName =" << RootName<<std::endl;
//MinervaUniverse::SetPlaylist(playlist);
//double POTFULLDATA = dataEvt->GetBatchPOT();

//std::cout << "POT = " << dataPOT<<std::endl;
//HeliumCVUniverse* universe = data_error_bands["CV"][0];
std::cout << "*** Starting Data Loop ***" << std::endl;
  std::cout<<" Looping throught Playlist: "<< playlist<<std::endl;
for(Long64_t ievent=0; ievent < chw_Data->GetEntries(); ++ievent){

  if(ievent%10000==0) std::cout << (ievent/1000) << "k " << std::endl;
  dataEvt->SetEntry(ievent);

  EventCounter(*dataEvt, kCutsVector, EventCounter_data, isNOT_mc, Playlist_Info );


  if(  PassesCutsRECO(*dataEvt,  isNOT_mc , kCutsVector) ){

    double Theta = dataEvt->GetThetamu();
    //double Pmu =   dataEvt-> GetPmu_inhouse()/1000;
    double Pmu =   dataEvt->GetPmu()/1000;
    double Emu =   dataEvt->GetEmu()*.001;
    double phi =   dataEvt->GetPhimu();

    double px = Pmu * std::sin(Theta) * std::cos(phi);
    double py = Pmu * std::sin(Theta) * std::sin(phi);

    double PT = sqrt(px*px + py*py);
    double PZ = Pmu*std::cos(Theta);

    double distance_upstreamCap = DistanceFromUpStreamBulge(dataEvt->GetVertex_z() , dataEvt->GetVertex_r());
    double distance_downstreamCap = DistanceFromDownStreamBulge(dataEvt->GetVertex_z() , dataEvt->GetVertex_r());
    double r = dataEvt->GetVertex_r();
    double z = dataEvt->GetVertex_z();
    h_Data_MuonE->Fill(Emu, 1.0);
    h_Data_MuonPZ->Fill(PZ, 1.0);
    h_Data_MuonPT->Fill(PT, 1.0);
    h_Data_MuonTheta->Fill(Theta*TMath::RadToDeg(),1.0);
    int secondTrk = dataEvt->Getindex2ndTrackhighestKE();

    TrackType Track_type_Event = dataEvt->GetTrackType();
    VertexOptions VertexOption_type = dataEvt->GetVertex_optionType();
    boolNTrack boolNTrack_Type = dataEvt->GetVertex_boolNTrack();
    double OpenAngle = dataEvt->GetOpenAngle(secondTrk);

    h_Data_CryoVertex_X->Fill(dataEvt->GetVertex_x(),1.0);
    h_Data_CryoVertex_Y->Fill(dataEvt->GetVertex_y(),1.0);
    h_Data_CryoVertex_Z->Fill(z,1.0);
    h_Data_CryoVertex_R->Fill(dataEvt->GetVertex_r(),1.0);
    h_Data_CryoVertex_RR->Fill(dataEvt->GetVertex_rr(),1.0);
    h_Data_secTrk_tracklength->Fill(dataEvt->GetNonmuTrkLength_InMinerva_Incm(secondTrk),1.0);
    h_Data_CryoVertexChiSqFit->Fill(dataEvt->GetVertexChiSqrFit(),1.0);
    h_Data_Distance_to_InnerTank->Fill(RECO_Distance_to_innerTank(*dataEvt),1.0);
    h_Data_CryoVertexChiSqFit_TrackType.GetComponentHist(Track_type_Event)->Fill(dataEvt->GetVertexChiSqrFit(), 1.0);
    h_Data_Distance_to_UpstreamCap->Fill(distance_upstreamCap,1.0);
    h_Data_Distance_to_DownstreamCap->Fill(distance_downstreamCap,1.0);
    h_Data_SmearingCryoVertex_R->Fill(dataEvt->GetVertex_r(), 1.0);

     h_Data_CryoVertex_Z_TrackType.GetComponentHist(Track_type_Event)->Fill(z, 1.0);
     h_Data_CryoVertex_Z_vertex.GetComponentHist( VertexOption_type)->Fill(z, 1.0);
     h_Data_CryoVertex_Z_Ntracks.GetComponentHist(boolNTrack_Type)->Fill(z, 1.0);


     h_2d_Data_vertexZ_openAngle->Fill(dataEvt->GetVertex_z(),OpenAngle,1.0);
     h_2d_Data_vertexR_openAngle->Fill(dataEvt->GetVertex_r(),OpenAngle,1.0);
     h_2d_Data_vertexX_openAngle->Fill(dataEvt->GetVertex_x(),OpenAngle,1.0);
     h_2d_Data_vertexY_openAngle->Fill(dataEvt->GetVertex_y(),OpenAngle,1.0);
     h_2d_Data_Vertex_Z_R->Fill(dataEvt->GetVertex_z(),dataEvt->GetVertex_r(),1.0);

     h_2d_Data_Vertex_Z_X->Fill(dataEvt->GetVertex_z(),dataEvt->GetVertex_x(),1.0);
     h_2d_Data_Vertex_Z_Y->Fill(dataEvt->GetVertex_z(),dataEvt->GetVertex_y(),1.0);
     h_2d_Data_Vertex_X_Y->Fill(dataEvt->GetVertex_x(),dataEvt->GetVertex_y(),1.0);

    if(Track_type_Event==kNotdefinedTrack){std::cout<<"got an not defined track"<<std::endl;}

    if(Cylindrical_CutAboutZero(*dataEvt)  == true){
      h_Data_Distance_to_UpstreamCap_RCut->Fill(distance_upstreamCap,1.0);
      h_Data_Distance_to_DownstreamCap_RCut->Fill(distance_downstreamCap,1.0);
      h_Data_CryoVertex_Z_RCut->Fill(z,1.0);
    }

    //auto CryoTank_Bulge_REGIONS_data =  Bulge_Regions_of_CryoTank(dataEvt->GetVertex_z());
    //auto CryoTank_Barrel_REGIONS_data = Barrel_Region_of_CryoTank(dataEvt->GetVertex_z());
    CryoTank_REGIONS CryoTankRegion_4type = FourRegion_of_CryoTank(z);

    ////////////////////////////////////////
    /// 4 CryoRegions
    //////////////////////////////////////
    ////////////////////////////////////////
    /// Upstream Cap
    //////////////////////////////////////


    if(CryoTankRegion_4type==kUpstream_head){
      h_Data_CryoVertex_X_upstreamCap->Fill(dataEvt->GetVertex_x(),1.0);
      h_Data_CryoVertex_Y_upstreamCap->Fill(dataEvt->GetVertex_y(),1.0);
      h_Data_CryoVertex_Z_upstreamCap->Fill(dataEvt->GetVertex_z(), 1.0);
      h_Data_secTrkLength_upstreamCap->Fill(dataEvt->GetNonmuTrkLength_InMinerva_Incm(secondTrk),1.0);
      h_Data_CryoVertex_R_upstreamCap->Fill(dataEvt->GetVertex_r(),1.0);
      h_Data_CryoVertex_RR_upstreamCap->Fill(dataEvt->GetVertex_rr(),1.0);
      h_Data_secTrk_DOCA_upstreamCap->Fill(dataEvt->GetNonmuDOCA(secondTrk),1.0);
      h_Data_Distance_to_InnerTank_upstreamCap->Fill(RECO_Distance_to_innerTank(*dataEvt),1.0);

      h_Data_MuonE_upstreamCap->Fill(Emu, 1.0);
      h_Data_MuonPT_upstreamCap->Fill(PT, 1.0);
      h_Data_MuonPZ_upstreamCap->Fill(PZ, 1.0);
      h_Data_MuonTheta_upstreamCap->Fill(Theta*TMath::RadToDeg(),1.0);
      h_Data_MuonDOCA_upstreamCap->Fill(dataEvt->GetDOCAmu(),1.0);
      h_Data_secTrk_angle_upstreamCap->Fill(dataEvt->GetNonmuTrkAngleWRTbeamMID(secondTrk),1.0);

      Vertex_XYZ XYZinput{dataEvt->GetVertex_x(),dataEvt->GetVertex_y(),dataEvt->GetVertex_z()};
      UpstreamCap_vector.push_back(XYZinput);

      h_Data_Distance_to_UpstreamCap_upstreamCap->Fill(distance_upstreamCap,1.0);
      h_Data_Distance_to_DownstreamCap_upstreamCap->Fill(distance_downstreamCap,1.0);
      h_Data_secTrk_tracklength_upstreamCap->Fill(dataEvt->GetNonmuTrkLength_InMinerva_Incm(secondTrk),1.0);

      if(Cylindrical_CutAboutZero(*dataEvt)==true){

        UpstreamCap_RCut_vector.push_back(XYZinput);
        h_Data_CryoVertex_Z_RCut_upstreamCap->Fill(z, 1.0);}
        UpstreamBugle_vector.push_back(XYZinput);
        h_Data_Distance_to_UpstreamCap_RCut_upstreamCap->Fill(distance_upstreamCap,1.0);
        h_Data_Distance_to_DownstreamCap_RCut_upstreamCap->Fill(distance_downstreamCap,1.0);

        if(IsInFiducalVolumeFromtheInnerEdge( r, z, 50.0  )==false) continue;

        h_Data_CryoVertex_X_Fiducial_upstreamCap->Fill(dataEvt->GetVertex_x(),1.0);
        h_Data_CryoVertex_Y_Fiducial_upstreamCap->Fill(dataEvt->GetVertex_y(),1.0);
        h_Data_CryoVertex_Z_Fiducial_upstreamCap->Fill(z, 1.0);
        h_Data_CryoVertex_R_Fiducial_upstreamCap->Fill(dataEvt->GetVertex_r(),1.0);
        h_Data_MuonE_Fiducial_upstreamCap->Fill(Emu, 1.0);
        h_Data_MuonPT_Fiducial_upstreamCap->Fill(PT, 1.0);
        h_Data_MuonPZ_Fiducial_upstreamCap->Fill(PZ, 1.0);
        h_Data_MuonTheta_Fiducial_upstreamCap->Fill(Theta*TMath::RadToDeg(),1.0);
        h_Data_MuonDOCA_Fiducial_upstreamCap->Fill(dataEvt->GetDOCAmu(),1.0);
        h_Data_secTrk_angle_Fiducial_upstreamCap->Fill(dataEvt->GetNonmuTrkAngleWRTbeamMID(secondTrk),1.0);
        h_Data_secTrk_DOCA_Fiducial_upstreamCap->Fill(dataEvt->GetNonmuDOCA(secondTrk),1.0);
        h_Data_Distance_to_InnerTank_Fiducial_upstreamCap->Fill(RECO_Distance_to_innerTank(*dataEvt),1.0);
        h_Data_secTrkLength_Fiducial_upstreamCap->Fill(dataEvt->GetNonmuTrkLength_InMinerva_Incm(secondTrk),1.0);








      }





      ////////////////////////////////////////
      /// Barrel
      //////////////////////////////////////

      else if(CryoTankRegion_4type==kCenter){
        Vertex_XYZ XYZinput{dataEvt->GetVertex_x(),dataEvt->GetVertex_y(),dataEvt->GetVertex_z()};
        barrel_vector.push_back(XYZinput);
        h_Data_CryoVertex_X_barrel->Fill(dataEvt->GetVertex_x(),1.0);
        h_Data_CryoVertex_Y_barrel->Fill(dataEvt->GetVertex_y(),1.0);
        h_Data_CryoVertex_Z_barrel->Fill(z, 1.0);
        h_Data_secTrkLength_barrel->Fill(dataEvt->GetNonmuTrkLength_InMinerva_Incm(secondTrk),1.0);
        h_Data_CryoVertex_R_barrel->Fill(dataEvt->GetVertex_r(),1.0);
        h_Data_CryoVertex_RR_barrel->Fill(dataEvt->GetVertex_rr(),1.0);
        h_Data_secTrk_DOCA_barrel->Fill(dataEvt->GetNonmuDOCA(secondTrk),1.0);
        h_Data_Distance_to_InnerTank_barrel->Fill(RECO_Distance_to_innerTank(*dataEvt),1.0);

        h_Data_Distance_to_UpstreamCap_barrel->Fill(distance_upstreamCap,1.0);
        h_Data_Distance_to_DownstreamCap_barrel->Fill(distance_downstreamCap,1.0);

        h_Data_MuonE_barrel->Fill(Emu, 1.0);
        h_Data_MuonPT_barrel->Fill(PT, 1.0);
        h_Data_MuonPZ_barrel->Fill(PZ, 1.0);
        h_Data_MuonTheta_barrel->Fill(Theta*TMath::RadToDeg(),1.0);
        h_Data_MuonDOCA_barrel->Fill(dataEvt->GetDOCAmu(),1.0);
        h_Data_secTrk_angle_barrel->Fill(dataEvt->GetNonmuTrkAngleWRTbeamMID(secondTrk),1.0);
        h_Data_secTrk_tracklength_barrel->Fill(dataEvt->GetNonmuTrkLength_InMinerva_Incm(secondTrk),1.0);

        if(Cylindrical_CutAboutZero(*dataEvt)==true){
          h_Data_CryoVertex_Z_RCut_barrel->Fill(z, 1.0);
          barrel_RCut_vector.push_back(XYZinput);

          DownstreamBugle_vector.push_back(XYZinput);

          h_Data_Distance_to_UpstreamCap_RCut_barrel->Fill(distance_upstreamCap,1.0);
          h_Data_Distance_to_DownstreamCap_RCut_barrel->Fill(distance_downstreamCap,1.0);

        }

        if(IsInFiducalVolumeFromtheInnerEdge( r, z, 50.0  )==false) continue;

        h_Data_CryoVertex_X_Fiducial_barrel->Fill(dataEvt->GetVertex_x(),1.0);
        h_Data_CryoVertex_Y_Fiducial_barrel->Fill(dataEvt->GetVertex_y(),1.0);
        h_Data_CryoVertex_Z_Fiducial_barrel->Fill(z, 1.0);
        h_Data_CryoVertex_R_Fiducial_barrel->Fill(dataEvt->GetVertex_r(),1.0);
        h_Data_MuonE_Fiducial_barrel->Fill(Emu, 1.0);
        h_Data_MuonPT_Fiducial_barrel->Fill(PT, 1.0);
        h_Data_MuonPZ_Fiducial_barrel->Fill(PZ, 1.0);
        h_Data_MuonTheta_Fiducial_barrel->Fill(Theta*TMath::RadToDeg(),1.0);
        h_Data_MuonDOCA_Fiducial_barrel->Fill(dataEvt->GetDOCAmu(),1.0);
        h_Data_secTrk_angle_Fiducial_barrel->Fill(dataEvt->GetNonmuTrkAngleWRTbeamMID(secondTrk),1.0);
        h_Data_secTrk_DOCA_Fiducial_barrel->Fill(dataEvt->GetNonmuDOCA(secondTrk),1.0);
        h_Data_Distance_to_InnerTank_Fiducial_barrel->Fill(RECO_Distance_to_innerTank(*dataEvt),1.0);
        h_Data_secTrkLength_Fiducial_barrel->Fill(dataEvt->GetNonmuTrkLength_InMinerva_Incm(secondTrk),1.0);






      }

      ////////////////////////////////////////
      /// Downstream Cap
      //////////////////////////////////////

      else if(CryoTankRegion_4type==kDownstream_head){
        Vertex_XYZ XYZinput{dataEvt->GetVertex_x(),dataEvt->GetVertex_y(),dataEvt->GetVertex_z()};
        DownstreamCap_vector.push_back(XYZinput);
        h_Data_CryoVertex_X_downstreamCap->Fill(dataEvt->GetVertex_x(),1.0);
        h_Data_CryoVertex_Y_downstreamCap->Fill(dataEvt->GetVertex_y(),1.0);
        h_Data_CryoVertex_Z_downstreamCap->Fill(z, 1.0);
        h_Data_secTrkLength_downstreamCap->Fill(dataEvt->GetNonmuTrkLength_InMinerva_Incm(secondTrk),1.0);
        h_Data_CryoVertex_R_downstreamCap->Fill(dataEvt->GetVertex_r(),1.0);
        h_Data_CryoVertex_RR_downstreamCap->Fill(dataEvt->GetVertex_rr(),1.0);
        h_Data_secTrk_DOCA_downstreamCap->Fill(dataEvt->GetNonmuDOCA(secondTrk),1.0);
        h_Data_Distance_to_InnerTank_downstreamCap->Fill(RECO_Distance_to_innerTank(*dataEvt),1.0);

        h_Data_Distance_to_UpstreamCap_downstreamCap->Fill(distance_upstreamCap,1.0);
        h_Data_Distance_to_DownstreamCap_downstreamCap->Fill(distance_downstreamCap,1.0);

        h_Data_MuonE_downstreamCap->Fill(Emu, 1.0);
        h_Data_MuonPT_downstreamCap->Fill(PT, 1.0);
        h_Data_MuonPZ_downstreamCap->Fill(PZ, 1.0);
        h_Data_MuonTheta_downstreamCap->Fill(Theta*TMath::RadToDeg(),1.0);
        h_Data_MuonDOCA_downstreamCap->Fill(dataEvt->GetDOCAmu(),1.0);
        h_Data_secTrk_angle_downstreamCap->Fill(dataEvt->GetNonmuTrkAngleWRTbeamMID(secondTrk),1.0);
        h_Data_secTrk_tracklength_downstreamCap->Fill(dataEvt->GetNonmuTrkLength_InMinerva_Incm(secondTrk),1.0);

        if(Cylindrical_CutAboutZero(*dataEvt)==true){
          h_Data_CryoVertex_Z_RCut_downstreamCap->Fill(z, 1.0);
          DownstreamCap_RCut_vector.push_back(XYZinput);
          Vertex_XYZ XYZinput{dataEvt->GetVertex_x(),dataEvt->GetVertex_y(),z};
          DownstreamBugle_vector.push_back(XYZinput);
          h_Data_Distance_to_UpstreamCap_RCut_downstreamCap->Fill(distance_upstreamCap,1.0);
          h_Data_Distance_to_DownstreamCap_RCut_downstreamCap->Fill(distance_downstreamCap,1.0);


        }

        if(IsInFiducalVolumeFromtheInnerEdge( r, z, 50.0  )==false) continue;

        h_Data_CryoVertex_X_Fiducial_downstreamCap->Fill(dataEvt->GetVertex_x(),1.0);
        h_Data_CryoVertex_Y_Fiducial_downstreamCap->Fill(dataEvt->GetVertex_y(),1.0);
        h_Data_CryoVertex_Z_Fiducial_downstreamCap->Fill(z, 1.0);
        h_Data_CryoVertex_R_Fiducial_downstreamCap->Fill(dataEvt->GetVertex_r(),1.0);
        h_Data_MuonE_Fiducial_downstreamCap->Fill(Emu, 1.0);
        h_Data_MuonPT_Fiducial_downstreamCap->Fill(PT, 1.0);
        h_Data_MuonPZ_Fiducial_downstreamCap->Fill(PZ, 1.0);
        h_Data_MuonTheta_Fiducial_downstreamCap->Fill(Theta*TMath::RadToDeg(),1.0);
        h_Data_MuonDOCA_Fiducial_downstreamCap->Fill(dataEvt->GetDOCAmu(),1.0);
        h_Data_secTrk_angle_Fiducial_downstreamCap->Fill(dataEvt->GetNonmuTrkAngleWRTbeamMID(secondTrk),1.0);
        h_Data_secTrk_DOCA_Fiducial_downstreamCap->Fill(dataEvt->GetNonmuDOCA(secondTrk),1.0);
        h_Data_Distance_to_InnerTank_Fiducial_downstreamCap->Fill(RECO_Distance_to_innerTank(*dataEvt),1.0);
        h_Data_secTrkLength_Fiducial_downstreamCap->Fill(dataEvt->GetNonmuTrkLength_InMinerva_Incm(secondTrk),1.0);





      }

      ////////////////////////////////////////
      /// DownstreamConcave Cap
      //////////////////////////////////////

      else if(CryoTankRegion_4type==kDownstream_ConcaveCap){
        Vertex_XYZ XYZinput{dataEvt->GetVertex_x(),dataEvt->GetVertex_y(),z};
        downstreamConcaveCap_vector.push_back(XYZinput);
        h_Data_CryoVertex_X_downstreamConcaveCap->Fill(dataEvt->GetVertex_x(),1.0);
        h_Data_CryoVertex_Y_downstreamConcaveCap->Fill(dataEvt->GetVertex_y(),1.0);
        h_Data_CryoVertex_Z_downstreamConcaveCap->Fill(z, 1.0);
        h_Data_secTrkLength_downstreamConcaveCap->Fill(dataEvt->GetNonmuTrkLength_InMinerva_Incm(secondTrk),1.0);
        h_Data_CryoVertex_R_downstreamConcaveCap->Fill(dataEvt->GetVertex_r(),1.0);
        h_Data_CryoVertex_RR_downstreamConcaveCap->Fill(dataEvt->GetVertex_rr(),1.0);
        h_Data_secTrk_DOCA_downstreamConcaveCap->Fill(dataEvt->GetNonmuDOCA(secondTrk),1.0);
        h_Data_Distance_to_InnerTank_downstreamConcaveCap->Fill(RECO_Distance_to_innerTank(*dataEvt),1.0);
        h_Data_Distance_to_UpstreamCap_downstreamConcaveCap->Fill(distance_upstreamCap,1.0);
        h_Data_Distance_to_DownstreamCap_downstreamConcaveCap->Fill(distance_downstreamCap,1.0);
        h_Data_secTrk_tracklength_downstreamConcaveCap->Fill(dataEvt->GetNonmuTrkLength_InMinerva_Incm(secondTrk),1.0);
        h_Data_MuonE_downstreamConcaveCap->Fill(Emu, 1.0);
        h_Data_MuonPT_downstreamConcaveCap->Fill(PT, 1.0);
        h_Data_MuonPZ_downstreamConcaveCap->Fill(PZ, 1.0);
        h_Data_MuonTheta_downstreamConcaveCap->Fill(Theta*TMath::RadToDeg(),1.0);
        h_Data_MuonDOCA_downstreamConcaveCap->Fill(dataEvt->GetDOCAmu(),1.0);
        h_Data_secTrk_angle_downstreamConcaveCap->Fill(dataEvt->GetNonmuTrkAngleWRTbeamMID(secondTrk),1.0);
        if(Cylindrical_CutAboutZero(*dataEvt)==true){
          h_Data_CryoVertex_Z_RCut_downstreamConcaveCap->Fill(dataEvt->GetVertex_z(), 1.0);
          downstreamConcaveCap_RCut_vector.push_back(XYZinput);
          h_Data_Distance_to_UpstreamCap_RCut_downstreamConcaveCap->Fill(distance_upstreamCap,1.0);
          h_Data_Distance_to_DownstreamCap_RCut_downstreamConcaveCap->Fill(distance_downstreamCap,1.0);

        }

    if(IsInFiducalVolumeFromtheInnerEdge( r, z, 50.0  )==false) continue;

    h_Data_CryoVertex_X_Fiducial_downstreamConcaveCap->Fill(dataEvt->GetVertex_x(),1.0);
    h_Data_CryoVertex_Y_Fiducial_downstreamConcaveCap->Fill(dataEvt->GetVertex_y(),1.0);
    h_Data_CryoVertex_Z_Fiducial_downstreamConcaveCap->Fill(dataEvt->GetVertex_z(), 1.0);
    h_Data_CryoVertex_R_Fiducial_downstreamConcaveCap->Fill(dataEvt->GetVertex_r(),1.0);
    h_Data_MuonE_Fiducial_downstreamConcaveCap->Fill(Emu, 1.0);
    h_Data_MuonPT_Fiducial_downstreamConcaveCap->Fill(PT, 1.0);
    h_Data_MuonPZ_Fiducial_downstreamConcaveCap->Fill(PZ, 1.0);
    h_Data_MuonTheta_Fiducial_downstreamConcaveCap->Fill(Theta*TMath::RadToDeg(),1.0);
    h_Data_MuonDOCA_Fiducial_downstreamConcaveCap->Fill(dataEvt->GetDOCAmu(),1.0);
    h_Data_secTrk_angle_Fiducial_downstreamConcaveCap->Fill(dataEvt->GetNonmuTrkAngleWRTbeamMID(secondTrk),1.0);
    h_Data_secTrk_DOCA_Fiducial_downstreamConcaveCap->Fill(dataEvt->GetNonmuDOCA(secondTrk),1.0);
    h_Data_Distance_to_InnerTank_Fiducial_downstreamConcaveCap->Fill(RECO_Distance_to_innerTank(*dataEvt),1.0);
    h_Data_secTrkLength_Fiducial_downstreamConcaveCap->Fill(dataEvt->GetNonmuTrkLength_InMinerva_Incm(secondTrk),1.0);



      }

      ////////////////////////////////////////
      /// End of CryoRegions
      //////////////////////////////////////



      h_Data_MuonDOCA->Fill(dataEvt->GetDOCAmu(),1.0);
      h_Data_MuonCharge->Fill(dataEvt->GetChargemu(), 1.0);
      h_Data_MuonMatchtoMinos->Fill(dataEvt->GetIntIsusableMuon(), 1.0);
      h_Data_MuonMatchtoVeto->Fill(dataEvt->GetMatchToVeto(), 1.0);
      h_Data_MuoncurvatureSig->Fill(dataEvt->GetCurvatureSignificance(), 1.0);

      h_Data_secTrk_Energy->Fill(dataEvt->GetNonmuTrkE(secondTrk)*Mev_to_GeV,1.0);
      h_Data_secTrk_MidAngle ->Fill(dataEvt->GetNonmuTrkAngleWRTbeamMID(secondTrk),1.0);
      h_Data_secTrk_Openangle->Fill(dataEvt->GetNonmuTrkAngleWRTmu(secondTrk),1.0);
      h_Data_secTrk_DOCA->Fill(dataEvt->GetNonmuDOCA(secondTrk),1.0);

      h_Data_secTrk_Pathlength->Fill(dataEvt->GetNonmuTrkLength(secondTrk),1.0);

      h_Data_VetoWall_matchToVeto  ->Fill( dataEvt->GetNumberMatchToVeto() ,1.0);
      h_Data_VetoWall_extrapnowalls->Fill( dataEvt->Getextrapnowalls() ,1.0);
      h_Data_VetoWall_extrapwall1  ->Fill( dataEvt->Getextrapwall1() ,1.0);
      h_Data_VetoWall_extrapwall2  ->Fill( dataEvt->Getextrapwall2() ,1.0);
      h_Data_VetoWall_extrapbothwalls ->Fill( dataEvt->Getextrapbothwalls() ,1.0);
      h_Data_VetoWall_MuonTrkMatchToVETOwalloff->Fill( dataEvt->GetMuonTrkMatchToVETOwalloff() ,1.0);

      h_Data_secTrk_FirstNodeX->Fill(dataEvt->GetFirstNodeX(secondTrk),1.0);
      h_Data_secTrk_FirstNodeY->Fill(dataEvt->GetFirstNodeY(secondTrk),1.0);
      h_Data_secTrk_FirstNodeZ->Fill(dataEvt->GetFirstNodeZ(secondTrk),1.0);
      h_Data_secTrk_LastNodeX->Fill(dataEvt->GetLastNodeX(secondTrk),1.0);
      h_Data_secTrk_LastNodeY->Fill(dataEvt->GetLastNodeY(secondTrk),1.0);
      h_Data_secTrk_LastNodeZ->Fill(dataEvt->GetLastNodeZ(secondTrk),1.0);
      h_Data_Tracksize->Fill(dataEvt->GetTracksize(),1.0);

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

//=========================================
// Plot stuff
//=========================================



TCanvas *can = new TCanvas("", "");
//TCanvas *can = new TCanvas("can", "can",1800,1600);
MnvPlotter *mnv_plotter = new MnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);


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
//outFileName = "Histograms_test.root";
//auto outFile = TFile::Open(outFileName);
char pdf_name[1024];
char pdf_start[1024];
char pdf_mid[1024];
char pdf_end[1024];
sprintf(pdf_name, "DATA_PLOTS_%s_%s_SmearingStudy",c,d);

sprintf(pdf_start,"%s.pdf(",pdf_name);
sprintf(pdf_mid,  "%s.pdf",pdf_name);
sprintf(pdf_end,  "%s.pdf)",pdf_name);

can -> Print(pdf_start);


DrawVertex_Cryotank_X_Y_R_Vs_Z(UpstreamBugle_vector , c, " [DATA]Upstream Bugle" ,pdf_name , can, mnv_plotter);
DrawVertex_Cryotank_X_Y_R_Vs_Z(DownstreamBugle_vector , c, " [DATA]Downstream Bugle" ,pdf_name , can, mnv_plotter);
DrawVertex_Cryotank_X_Y_R_Vs_Z(CenterBugle_vector, c, "[DATA]Center Bugle" ,pdf_name , can, mnv_plotter);

DrawVertex_Cryotank_X_Y_R_Vs_Z_4regions(
  UpstreamCap_vector,
  barrel_vector,
  DownstreamCap_vector,
  downstreamConcaveCap_vector,
  c, "Regions" ,pdf_name , can, mnv_plotter);


DrawVertex_Cryotank_X_Y_R_Vs_Z_4regions(
  UpstreamCap_RCut_vector,
  barrel_RCut_vector,
  DownstreamCap_RCut_vector,
  downstreamConcaveCap_RCut_vector,
  c, "Regions R cut applied" ,pdf_name , can, mnv_plotter);


  can -> Print(pdf_end);


  sprintf(outFileName, "%s/%s_%s_%s_SmearingStudy.root",rootpathway, "Histograms",c,d);

  std::cout << "Writing output file to: " <<outFileName << std::endl;
  TFile outFile(outFileName, "RECREATE");

  TChain POT_branch("Meta");
  POT_branch.Add(RootName.c_str());
  TTree *clone =POT_branch.CloneTree();
  clone->Write();


  h_Data_MuonE->Write();
  h_Data_MuonPZ->Write();
  h_Data_MuonPT->Write();
  h_Data_MuonTheta->Write();
  h_Data_MuonDOCA->Write();
  h_Data_CryoVertex_X->Write();
  h_Data_CryoVertex_X_upstreamCap->Write();
  h_Data_CryoVertex_X_barrel->Write();
  h_Data_CryoVertex_X_downstreamCap->Write();
  h_Data_CryoVertex_X_downstreamConcaveCap->Write();

  h_Data_CryoVertex_Y->Write();
  h_Data_CryoVertex_Y_upstreamCap->Write();
  h_Data_CryoVertex_Y_barrel->Write();
  h_Data_CryoVertex_Y_downstreamCap->Write();
  h_Data_CryoVertex_Y_downstreamConcaveCap->Write();
  h_Data_CryoVertex_Z->Write();

  h_Data_CryoVertex_R->Write();
  h_Data_CryoVertex_R_upstreamCap->Write();
  h_Data_CryoVertex_R_barrel->Write();
  h_Data_CryoVertex_R_downstreamCap->Write();
  h_Data_CryoVertex_R_downstreamConcaveCap->Write();

  h_Data_CryoVertex_RR->Write();
  h_Data_VetoWall_matchToVeto->Write();
  h_Data_VetoWall_extrapnowalls->Write();
  h_Data_VetoWall_extrapwall1->Write();
  h_Data_VetoWall_extrapwall2->Write();
  h_Data_VetoWall_extrapbothwalls->Write();
  h_Data_VetoWall_MuonTrkMatchToVETOwalloff->Write();
  h_Data_secTrk_Energy->Write();
  h_Data_secTrk_MidAngle ->Write();
  h_Data_secTrk_DOCA->Write();
  h_Data_secTrk_Pathlength->Write();
  h_Data_secTrk_Openangle->Write();
  h_Data_Tracksize->Write();
  h_Data_secTrk_FirstNodeX->Write();
  h_Data_secTrk_FirstNodeY->Write();
  h_Data_secTrk_FirstNodeZ->Write();
  h_Data_secTrk_LastNodeX->Write();
  h_Data_secTrk_LastNodeY->Write();
  h_Data_secTrk_LastNodeZ->Write();

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
  h_Data_SmearingCryoVertex_R->Write();
  h_Data_CryoVertexChiSqFit->Write();
  h_Data_CryoVertexChiSqFit_TrackType.WriteToFile(outFile);
  h_Data_CryoVertex_Z_Center->Write();
  h_Data_Smearing_Center_region_CryoVertex_R->Write();
  h_Data_Smearing_Center_region_CryoVertex_RR->Write();
  h_Data_secTrk_tracklength->Write();
  h_Data_secTrk_tracklength_upstreamCap->Write();
  h_Data_secTrk_tracklength_downstreamCap->Write();
  h_Data_secTrk_tracklength_barrel->Write();

  h_Data_secTrkLength_upstreamCap->Write();
  h_Data_secTrkLength_downstreamCap->Write();
  h_Data_secTrkLength_barrel->Write();
  h_Data_secTrkLength_downstreamConcaveCap->Write();

  h_Data_secTrk_DOCA_upstreamCap->Write();
  h_Data_secTrk_DOCA_barrel->Write();
  h_Data_secTrk_DOCA_downstreamCap->Write();
  h_Data_secTrk_DOCA_downstreamConcaveCap->Write();

  h_Data_CryoVertex_Z_upstreamCap->Write();
  h_Data_CryoVertex_Z_barrel->Write();
  h_Data_CryoVertex_Z_downstreamCap->Write();
  h_Data_CryoVertex_Z_downstreamConcaveCap->Write();

  h_Data_CryoVertex_Z_RCut->Write();
  h_Data_CryoVertex_Z_RCut_upstreamCap->Write();
  h_Data_CryoVertex_Z_RCut_barrel->Write();
  h_Data_CryoVertex_Z_RCut_downstreamCap->Write();
  h_Data_CryoVertex_Z_RCut_downstreamConcaveCap->Write();



  h_Data_CryoVertex_RR_upstreamCap->Write();
  h_Data_CryoVertex_RR_barrel->Write();
  h_Data_CryoVertex_RR_downstreamCap->Write();
  h_Data_CryoVertex_RR_downstreamConcaveCap->Write();

  h_Data_Distance_to_InnerTank->Write();
  h_Data_Distance_to_InnerTank_upstreamCap->Write();
  h_Data_Distance_to_InnerTank_barrel->Write();
  h_Data_Distance_to_InnerTank_downstreamCap->Write();
  h_Data_Distance_to_InnerTank_downstreamConcaveCap->Write();


  h_Data_Distance_to_UpstreamCap->Write();
  h_Data_Distance_to_UpstreamCap_upstreamCap->Write();
  h_Data_Distance_to_UpstreamCap_barrel->Write();
  h_Data_Distance_to_UpstreamCap_downstreamCap->Write();
  h_Data_Distance_to_UpstreamCap_downstreamConcaveCap->Write();
  h_Data_Distance_to_UpstreamCap_RCut->Write();
  h_Data_Distance_to_UpstreamCap_RCut_upstreamCap->Write();
  h_Data_Distance_to_UpstreamCap_RCut_barrel->Write();
  h_Data_Distance_to_UpstreamCap_RCut_downstreamCap->Write();
  h_Data_Distance_to_UpstreamCap_RCut_downstreamConcaveCap->Write();
  h_Data_Distance_to_DownstreamCap->Write();
  h_Data_Distance_to_DownstreamCap_upstreamCap->Write();
  h_Data_Distance_to_DownstreamCap_barrel->Write();
  h_Data_Distance_to_DownstreamCap_downstreamCap->Write();
  h_Data_Distance_to_DownstreamCap_downstreamConcaveCap->Write();
  h_Data_Distance_to_DownstreamCap_RCut->Write();
  h_Data_Distance_to_DownstreamCap_RCut_upstreamCap->Write();
  h_Data_Distance_to_DownstreamCap_RCut_barrel->Write();
  h_Data_Distance_to_DownstreamCap_RCut_downstreamCap->Write();
  h_Data_Distance_to_DownstreamCap_RCut_downstreamConcaveCap->Write();


  h_Data_MuonE_upstreamCap->Write();
  h_Data_MuonPT_upstreamCap->Write();
  h_Data_MuonPZ_upstreamCap->Write();
  h_Data_MuonTheta_upstreamCap->Write();
  h_Data_MuonDOCA_upstreamCap->Write();
  h_Data_MuonE_barrel->Write();
  h_Data_MuonPT_barrel->Write();
  h_Data_MuonPZ_barrel->Write();
  h_Data_MuonTheta_barrel->Write();
  h_Data_MuonDOCA_barrel->Write();
  h_Data_MuonE_downstreamCap->Write();
  h_Data_MuonPT_downstreamCap->Write();
  h_Data_MuonPZ_downstreamCap->Write();
  h_Data_MuonTheta_downstreamCap->Write();
  h_Data_MuonDOCA_downstreamCap->Write();
  h_Data_MuonE_downstreamConcaveCap->Write();
  h_Data_MuonPT_downstreamConcaveCap->Write();
  h_Data_MuonPZ_downstreamConcaveCap->Write();
  h_Data_MuonTheta_downstreamConcaveCap->Write();
  h_Data_MuonDOCA_downstreamConcaveCap->Write();



  h_Data_CryoVertex_X_Fiducial_upstreamCap->Write();
  h_Data_CryoVertex_Y_Fiducial_upstreamCap->Write();
  h_Data_CryoVertex_Z_Fiducial_upstreamCap->Write();
  h_Data_CryoVertex_R_Fiducial_upstreamCap->Write();
  h_Data_MuonE_Fiducial_upstreamCap->Write();
  h_Data_MuonPT_Fiducial_upstreamCap->Write();
  h_Data_MuonPZ_Fiducial_upstreamCap->Write();
  h_Data_MuonTheta_Fiducial_upstreamCap->Write();
  h_Data_MuonDOCA_Fiducial_upstreamCap->Write();
  h_Data_secTrk_angle_Fiducial_upstreamCap->Write();
  h_Data_secTrk_DOCA_Fiducial_upstreamCap->Write();
  h_Data_Distance_to_InnerTank_Fiducial_upstreamCap->Write();
  h_Data_secTrkLength_Fiducial_upstreamCap->Write();
  h_Data_CryoVertex_X_Fiducial_barrel->Write();
  h_Data_CryoVertex_Y_Fiducial_barrel->Write();
  h_Data_CryoVertex_Z_Fiducial_barrel->Write();
  h_Data_CryoVertex_R_Fiducial_barrel->Write();
  h_Data_MuonE_Fiducial_barrel->Write();
  h_Data_MuonPT_Fiducial_barrel->Write();
  h_Data_MuonPZ_Fiducial_barrel->Write();
  h_Data_MuonTheta_Fiducial_barrel->Write();
  h_Data_MuonDOCA_Fiducial_barrel->Write();
  h_Data_secTrk_angle_Fiducial_barrel->Write();
  h_Data_secTrk_DOCA_Fiducial_barrel->Write();
  h_Data_Distance_to_InnerTank_Fiducial_barrel->Write();
  h_Data_secTrkLength_Fiducial_barrel->Write();
  h_Data_CryoVertex_X_Fiducial_downstreamCap->Write();
  h_Data_CryoVertex_Y_Fiducial_downstreamCap->Write();
  h_Data_CryoVertex_Z_Fiducial_downstreamCap->Write();
  h_Data_CryoVertex_R_Fiducial_downstreamCap->Write();
  h_Data_MuonE_Fiducial_downstreamCap->Write();
  h_Data_MuonPT_Fiducial_downstreamCap->Write();
  h_Data_MuonPZ_Fiducial_downstreamCap->Write();
  h_Data_MuonTheta_Fiducial_downstreamCap->Write();
  h_Data_MuonDOCA_Fiducial_downstreamCap->Write();
  h_Data_secTrk_angle_Fiducial_downstreamCap->Write();
  h_Data_secTrk_DOCA_Fiducial_downstreamCap->Write();
  h_Data_Distance_to_InnerTank_Fiducial_downstreamCap->Write();
  h_Data_secTrkLength_Fiducial_downstreamCap->Write();
  h_Data_CryoVertex_X_Fiducial_downstreamConcaveCap->Write();
  h_Data_CryoVertex_Y_Fiducial_downstreamConcaveCap->Write();
  h_Data_CryoVertex_Z_Fiducial_downstreamConcaveCap->Write();
  h_Data_CryoVertex_R_Fiducial_downstreamConcaveCap->Write();
  h_Data_MuonE_Fiducial_downstreamConcaveCap->Write();
  h_Data_MuonPT_Fiducial_downstreamConcaveCap->Write();
  h_Data_MuonPZ_Fiducial_downstreamConcaveCap->Write();
  h_Data_MuonTheta_Fiducial_downstreamConcaveCap->Write();
  h_Data_MuonDOCA_Fiducial_downstreamConcaveCap->Write();
  h_Data_secTrk_angle_Fiducial_downstreamConcaveCap->Write();
  h_Data_secTrk_DOCA_Fiducial_downstreamConcaveCap->Write();
  h_Data_Distance_to_InnerTank_Fiducial_downstreamConcaveCap->Write();
  h_Data_secTrkLength_Fiducial_downstreamConcaveCap->Write();

  h_Data_secTrk_angle_upstreamCap->Write();
  h_Data_secTrk_angle_barrel->Write();
  h_Data_secTrk_angle_downstreamCap->Write();
  h_Data_secTrk_angle_downstreamConcaveCap->Write();

  h_Data_CryoVertex_Z_TrackType.WriteToFile(outFile);
  h_Data_CryoVertex_Z_vertex.WriteToFile(outFile);
  h_Data_CryoVertex_Z_Ntracks.WriteToFile(outFile);

  h_2d_Data_vertexZ_openAngle->Write();
  h_2d_Data_vertexR_openAngle->Write();
  h_2d_Data_vertexX_openAngle->Write();
  h_2d_Data_vertexY_openAngle->Write();
  h_2d_Data_Vertex_Z_R->Write();
  h_2d_Data_Vertex_Z_X->Write();
  h_2d_Data_Vertex_Z_Y->Write();
  h_2d_Data_Vertex_X_Y->Write();

  outFile.Close();


  //=========================================


  Make_cvs_Data_scanning(Low_R_EventID_vector, "Data_Low_R_event_study");



  std::cout << "Success looping throught Playlist of " <<Playlist_Info.GetPlaylistname() <<std::endl;
 // END OF PLAYLIST Loop


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

  ret_vec.push_back(kThetaMu );
  ret_vec.push_back(kMuonAngle );
  ret_vec.push_back(kMu_is_Plausible);

  ret_vec.push_back(kNTracks);
  ret_vec.push_back(kVertexConverge);
  ret_vec.push_back(kVertex_ConvergedfromAllTracks);
  ret_vec.push_back(kMaxChiSqrt_byTrackType);
  //ret_vec.push_back(kFiducialVolume);
  //ret_vec.push_back(kFiducialVolume_ExtraShell);
  ret_vec.push_back(kVeto );
  ret_vec.push_back(kSix );
  ret_vec.push_back(kMatchVetoDeadPaddle);

  ret_vec.push_back(kTrackForwardGoing);
  ret_vec.push_back(ksecTrkwrtblessthanMaxAngle);

  ret_vec.push_back(kAllCuts );
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
