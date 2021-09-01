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
  PlotUtils::NamedCategory<TrackType>({kOtherLong}, "OtherLongTracks")
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

MnvH1D *h_Data_secTrk_tracklength      =    new MnvH1D("h_Data_secTrk_tracklength", "h_Data_secTrk_tracklength", Recoil_track_length_vector.size()-1, Recoil_track_length_vector.data());
MnvH1D *h_Data_secTrk_tracklength_upstreamCap      =    new MnvH1D("h_Data_secTrk_tracklength_upstreamCap", "h_Data_secTrk_tracklength_upstreamCap", Recoil_track_length_vector.size()-1, Recoil_track_length_vector.data());
MnvH1D *h_Data_secTrk_tracklength_downstreamCap      =    new MnvH1D("h_Data_secTrk_tracklength_downstreamCap", "h_Data_secTrk_tracklength_downstreamCap", Recoil_track_length_vector.size()-1, Recoil_track_length_vector.data());
MnvH1D *h_Data_secTrk_tracklength_Barrel      =    new MnvH1D("h_Data_secTrk_tracklength_Barrel", "h_Data_secTrk_tracklength_Barrel", Recoil_track_length_vector.size()-1, Recoil_track_length_vector.data());


////////////////
//Vertex Hist///
////////////////
MnvH1D *h_Data_CryoVertex_X      =    new MnvH1D("h_Data_CryoVertex_X", "h_Data_CryoVertex_X", Vertex_Xbin_vector.size()-1, Vertex_Xbin_vector.data());
MnvH1D *h_Data_CryoVertex_Y      =    new MnvH1D("h_Data_CryoVertex_Y", "h_Data_CryoVertex_Y", Vertex_Ybin_vector.size()-1, Vertex_Ybin_vector.data());
MnvH1D *h_Data_CryoVertex_Z      =    new MnvH1D("h_Data_CryoVertex_Z", "h_Data_CryoVertex_Z", Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());
MnvH1D *h_Data_CryoVertex_R      =    new MnvH1D("h_Data_CryoVertex_R", "h_Data_CryoVertex_R", Vertex_Rbin_vector.size()-1, Vertex_Rbin_vector.data());
MnvH1D *h_Data_CryoVertexChiSqFit      =    new MnvH1D("h_Data_CryoVertexChiSqFit", "h_Data_CryoVertexChiSqFit", Vertex_ChiSqFit_vector.size()-1, Vertex_ChiSqFit_vector.data());

PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType> h_Data_CryoVertexChiSqFit_TrackType =
PlotUtils::HistFolio<PlotUtils::MnvH1D, TrackType>(TrackType_Category, "h_Data_CryoVertexChiSqFit_TrackType", Vertex_ChiSqFit_vector ,"h_Data_CryoVertexChiSqFit_TrackType; [mm];Events");



std::vector<double> Vertex_Rbins_vectorMOREbins_vec = {0,50,100,150,200,250,300,350,400,450,500,550,600,650,700,750,800,850,900,950,1000,1050,1100,1150,1200,1250 };
std::vector<double> Vertex_RRbins_vectorMOREbins_vec;
for(auto cat : Vertex_Rbins_vectorMOREbins_vec ) {Vertex_RRbins_vectorMOREbins_vec.push_back(cat * cat);}


MnvH1D *h_Data_SmearingCryoVertex_R      =    new MnvH1D("h_Data_SmearingCryoVertex_R", "h_Data_SmearingCryoVertex_R", Vertex_Rbins_vectorMOREbins_vec.size()-1, Vertex_Rbins_vectorMOREbins_vec.data());


std::vector<double> Bins_distance_to_Bulges ={-400,-375,-350,-325,-300,-275,-250,-225,-200,-175,-150,-
125,-100,-75,-50,-25, 0,25,50,75,100,125,150,175,200,225,250,275,300,325,350,375,400};


MnvH1D *h_Data_Vertex_distance_upstream      =    new MnvH1D("h_Data_Vertex_distance_upstream", "h_Data_Vertex_distance_upstream", Bins_distance_to_Bulges.size()-1, Bins_distance_to_Bulges.data());
MnvH1D *h_Data_CryoVertex_Z_upstream      =    new MnvH1D("h_Data_CryoVertex_Z_upstream", "h_Data_CryoVertex_Z_upstream", Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());

MnvH1D *h_Data_Vertex_distance_downstream      =    new MnvH1D("h_Data_Vertex_distance_downstream", "h_Data_Vertex_distance_downstream", Bins_distance_to_Bulges.size()-1, Bins_distance_to_Bulges.data());
//MnvH1D *h_Data_Vertex_distance_other      =    new MnvH1D("h_Data_Vertex_distance_other", "h_Data_Vertex_distance_other", Bins_distance_to_Bulges.size()-1, Bins_distance_to_Bulges.data());
MnvH1D *h_Data_CryoVertex_Z_downstream      =    new MnvH1D("h_Data_CryoVertex_Z_downstream", "h_Data_CryoVertex_Z_downstream", Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());

MnvH1D *h_Data_Smearing_Center_region_CryoVertex_R      =    new MnvH1D("h_Data_Smearing_Center_region_CryoVertex_R", "h_Data_Smearing_Center_region_CryoVertex_R", Vertex_Rbins_vectorMOREbins_vec.size()-1, Vertex_Rbins_vectorMOREbins_vec.data());
MnvH1D *h_Data_Smearing_Center_region_CryoVertex_RR      =    new MnvH1D("h_Data_Smearing_Center_region_CryoVertex_RR", "h_Data_Smearing_Center_region_CryoVertex_RR", Vertex_RRbins_vectorMOREbins_vec.size()-1, Vertex_RRbins_vectorMOREbins_vec.data());



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

for(Long64_t ievent=0; ievent < chw_Data->GetEntries(); ++ievent){

  if(ievent%10000==0) std::cout << (ievent/1000) << "k " << std::endl;
  dataEvt->SetEntry(ievent);

  EventCounter(*dataEvt, kCutsVector, EventCounter_data, isNOT_mc, Playlist_Info );


  if(  PassesCutsRECO(*dataEvt,  isNOT_mc , kCutsVector) ){

    double Theta = dataEvt->GetThetamu();
    //double Pmu =   dataEvt-> GetPmu_inhouse()/1000;
    double Pmu =   dataEvt->GetPmu()/1000;
    double Emu =   dataEvt->GetEmu()*.001;
    //std::cout << "Theta = "<< Theta<<std::endl;
    //std::cout << "Pmu = "<< Pmu<<std::endl;
    //std::cout << "Pmu = "<< dataEvt->GetMuonPt_ECT()<<std::endl;

    //std::cout << "Muon E = "<< dataEvt->GetMuonE_ECT()<<std::endl;
    h_Data_MuonE->Fill(Emu, 1.0);
    h_Data_MuonPZ->Fill(Pmu*std::cos(Theta), 1.0);//GetMuonPz()
    h_Data_MuonPT->Fill(Pmu*std::sin(Theta), 1.0);
    h_Data_MuonTheta->Fill(Theta*TMath::RadToDeg(),1.0);
    int secondTrk = dataEvt->Getindex2ndTrackhighestKE();
  //  h_Data_MuonE->Fill(dataEvt->GetMuonE_ECT(), 1.0);//GetMuonE()
  //  h_Data_MuonPZ->Fill(dataEvt->GetMuonPz_ECT(), 1.0);//GetMuonPz()
  //  h_Data_MuonPT->Fill(dataEvt->GetMuonPt_ECT(), 1.0);//GetMuonPt()
    h_Data_CryoVertex_X->Fill(dataEvt->GetVertex_x(),1.0);
    h_Data_CryoVertex_Y->Fill(dataEvt->GetVertex_y(),1.0);
    h_Data_CryoVertex_Z->Fill(dataEvt->GetVertex_z(),1.0);
    h_Data_CryoVertex_R->Fill(dataEvt->GetVertex_r(),1.0);
    h_Data_secTrk_tracklength->Fill(dataEvt->GetNonmuTrkLength_InMinerva_Incm(secondTrk),1.0);
    h_Data_CryoVertexChiSqFit->Fill(dataEvt->GetVertexChiSqrFit(),1.0);
    TrackType Track_type_Event = dataEvt->GetTrackType();
    h_Data_CryoVertexChiSqFit_TrackType.GetComponentHist(Track_type_Event)->Fill(dataEvt->GetVertexChiSqrFit(), 1.0);



    h_Data_SmearingCryoVertex_R->Fill(dataEvt->GetVertex_r(), 1.0);

    auto CryoTank_Bulge_REGIONS_data =  Bulge_Regions_of_CryoTank(dataEvt->GetVertex_z());
    auto CryoTank_Barrel_REGIONS_data = Barrel_Region_of_CryoTank(dataEvt->GetVertex_z());
// IsInExtendentedFiducalVolumeFromtheInnerEdge(*dataEvt,  0.0, 100.0, 50.0 ,175.0)
    if(CryoTank_Bulge_REGIONS_data==kUpstream_head && Cylindrical_CutAboutZero(*dataEvt)  == true){
      auto distance = DistanceFromUpStreamBulge(dataEvt->GetVertex_z() , dataEvt->GetVertex_r());
      h_Data_Vertex_distance_upstream->Fill(distance, 1.0);
      h_Data_CryoVertex_Z_upstream->Fill(dataEvt->GetVertex_z(), 1.0);
      Vertex_XYZ XYZinput{dataEvt->GetVertex_x(),dataEvt->GetVertex_y(),dataEvt->GetVertex_z()};
      UpstreamBugle_vector.push_back(XYZinput);
      h_Data_secTrk_tracklength_upstreamCap->Fill(dataEvt->GetNonmuTrkLength_InMinerva_Incm(secondTrk),1.0);


    }
    else if(CryoTank_Bulge_REGIONS_data==kDownstream_head && Cylindrical_CutAboutZero(*dataEvt) == true){
      auto distance = DistanceFromDownStreamBulge(dataEvt->GetVertex_z() , dataEvt->GetVertex_r());
       h_Data_Vertex_distance_downstream->Fill(distance, 1.0);
       h_Data_CryoVertex_Z_downstream->Fill(dataEvt->GetVertex_z(), 1.0);
       Vertex_XYZ XYZinput{dataEvt->GetVertex_x(),dataEvt->GetVertex_y(),dataEvt->GetVertex_z()};
       DownstreamBugle_vector.push_back(XYZinput);
       h_Data_secTrk_tracklength_downstreamCap->Fill(dataEvt->GetNonmuTrkLength_InMinerva_Incm(secondTrk),1.0);

     }
    if(CryoTank_Barrel_REGIONS_data==kCenter){
      double Current_R = dataEvt->GetVertex_r();
      h_Data_CryoVertex_Z_Center->Fill(dataEvt->GetVertex_z(), 1.0);
      h_Data_Smearing_Center_region_CryoVertex_R->Fill(Current_R, 1.0);
      h_Data_Smearing_Center_region_CryoVertex_RR->Fill(dataEvt->GetVertex_rr(), 1.0);
      Vertex_XYZ XYZinput{dataEvt->GetVertex_x(),dataEvt->GetVertex_y(),dataEvt->GetVertex_z()};
      h_Data_secTrk_tracklength_Barrel->Fill(dataEvt->GetNonmuTrkLength_InMinerva_Incm(secondTrk),1.0);

      CenterBugle_vector.push_back(XYZinput);

      if(200 < Current_R && Current_R < 600 && Center_counter < 75){
      SliceID Event_slice = dataEvt->GetEventSliceForData();
      SliceID_vertex_info Low_R_EventID{Event_slice, XYZinput};
      Low_R_EventID_vector.push_back(Low_R_EventID);
      Center_counter++;
    }
  } // end of if center


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


 //PrintCutstoScreenF_E(  kCutsVector,  kPlayListVector , EventCountMap, POT );
  //=========================================
  // Plot stuff
  //=========================================


//sprintf(pdf_start, "Optimization_figures.pdf(");
//sprintf(pdf_end, "Optimization_figures.pdf)");

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


  can -> Print(pdf_end);


  sprintf(outFileName, "%s/%s_%s_%s_SmearingStudy.root",rootpathway, "Histograms",c,d);

  std::cout << "Writing output file to: " <<outFileName << std::endl;

  //TFile outFile(outFileName, "RECREATE");

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
  h_Data_CryoVertex_Y->Write();
  h_Data_CryoVertex_Z->Write();
  h_Data_CryoVertex_R->Write();
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
  h_Data_Vertex_distance_upstream->Write();
  h_Data_Vertex_distance_downstream->Write();
  h_Data_CryoVertex_Z_downstream->Write();
  h_Data_CryoVertex_Z_upstream->Write();
  h_Data_CryoVertex_Z_Center->Write();
  h_Data_Smearing_Center_region_CryoVertex_R->Write();
  h_Data_Smearing_Center_region_CryoVertex_RR->Write();
  h_Data_secTrk_tracklength->Write();
  h_Data_secTrk_tracklength_upstreamCap->Write();
  h_Data_secTrk_tracklength_downstreamCap->Write();
  h_Data_secTrk_tracklength_Barrel->Write();
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
  ret_vec.push_back(kNoCuts  );
  ret_vec.push_back(kGoodEnergy );
  ret_vec.push_back(kThetaMu );
  ret_vec.push_back(kMuonAngle );
  ret_vec.push_back(kNTracks);
  ret_vec.push_back(kUsableMuon);
  //ret_vec.push_back(kNonMu_is_Plausible);
  ret_vec.push_back(kVeto );
  ret_vec.push_back(kSix );
  ret_vec.push_back(kMinosCoil );
  ret_vec.push_back(kMinosMatch);
  ret_vec.push_back(kMinosCurvature);
  ret_vec.push_back(kMinosCharge );
  ret_vec.push_back(kVertexConverge);
  //ret_vec.push_back(kFiducialVolume );
  ret_vec.push_back(kFiducialVolume_ExtraShell);
  ret_vec.push_back(kTrackForwardGoing );
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
