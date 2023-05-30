//Author: Christian Nguyen
// Helium TransWarp  Extractor.cxx
// Started to Build: Sep 1 2022
//email: christian2nguyen@ufl.edu

#include "ExtractHeliumHist_TransWarp.h"

std::string OUTputRoot_pathway = "/minerva/data/users/cnguyen/CrossSection_Hists_ALLPlaylists";
std::vector<MuonVar> GetTransWarpVaribles();
std::vector<ME_helium_Playlists> GetFullPlayListVector();
std::vector<ME_helium_Playlists> GetEmptyPlayListVector();

void POT_Normalize_TranWarp_Hist(TransWarp_Hist &inputCross_Hist, double normalize_MC_data);
void POT_Normalize_TranWarp_2DHist(TransWarp_2DHist &inputCross_Hist, double normalize_MC_data);
void Subtract_TransWarp_Hist(TransWarp_Hist &inputCross_Hist_Full, TransWarp_Hist &inputCross_Hist_Empty);
void Subtract_TransWarp_2DHist(TransWarp_2DHist &inputCross_Hist_Full, TransWarp_2DHist &inputCross_Hist_Empty);
//void AddErrorBands_TOEffDom(CrossSection_Hist &inputCross_Hist);
void RunTransWarpExtractor(bool &my_norm, bool &my_debug, int &Print_Systematics){
TH1::AddDirectory(false);
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~       Starting CrossSection Extraction for Helium 1D: ~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
auto FullME_playlist_vector = GetFullPlayListVector();
auto EmptyME_playlist_vector = GetEmptyPlayListVector();
auto full_playlist_initial = GetPlaylist_InitialName(FullME_playlist_vector[0]);
auto empty_playlist_initial = GetPlaylist_InitialName(EmptyME_playlist_vector[0]);

char fullplaylist_char[full_playlist_initial.length()+1];
strcpy( fullplaylist_char,full_playlist_initial.c_str());

char emptyplaylist_char[empty_playlist_initial.length()+1];
strcpy( emptyplaylist_char,empty_playlist_initial.c_str());

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

Pot_MapStatusList POT_MC_Status, POT_DATA_Status;
///////////////////////////////////////////
//I want to constuct cross section as a function of muon parameters pT, Pz , E , and theta
// going to try to find E first
///////////////////////////////
// lets start with two playlist F and G
/////////////
// Full Playlist
/////////////
auto PlaylistME_1P_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1P_MC_StatsONLYErrors_TRANSWARP_MK.root";
auto PlaylistME_1C_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1C_MC_StatsONLYErrors_TRANSWARP_MK.root";
auto PlaylistME_1D_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1D_MC_StatsONLYErrors_TRANSWARP_MK.root";
auto PlaylistME_1F_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1F_MC_StatsONLYErrors_TRANSWARP_MK.root";
auto PlaylistME_1E_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1E_MC_StatsONLYErrors_TRANSWARP_MK.root";
/////////////
// Empty Playlist
/////////////
auto PlaylistME_1G_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1G_MC_StatsONLYErrors_TRANSWARP_MK.root";
auto PlaylistME_1A_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1A_MC_StatsONLYErrors_TRANSWARP_MK.root";
auto PlaylistME_1L_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1L_MC_StatsONLYErrors_TRANSWARP_MK.root";
auto PlaylistME_1M_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1M_MC_StatsONLYErrors_TRANSWARP_MK.root";
auto PlaylistME_1N_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1N_MC_StatsONLYErrors_TRANSWARP_MK.root";

////////////
// Full Playlist
/////////////
auto PlaylistME_1P_MC2D_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2Dminervame1P_RECO_MC_StatsONLYErrorsTRANSWARP_MK.root";
auto PlaylistME_1C_MC2D_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2Dminervame1C_RECO_MC_StatsONLYErrorsTRANSWARP_MK.root";
auto PlaylistME_1D_MC2D_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2Dminervame1D_RECO_MC_StatsONLYErrorsTRANSWARP_MK.root";
auto PlaylistME_1F_MC2D_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2Dminervame1F_RECO_MC_StatsONLYErrorsTRANSWARP_MK.root";
auto PlaylistME_1E_MC2D_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2Dminervame1E_RECO_MC_StatsONLYErrorsTRANSWARP_MK.root";
/////////////
// Empty Playlist
/////////////
auto PlaylistME_1G_MC2D_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2Dminervame1G_RECO_MC_StatsONLYErrorsTRANSWARP_MK.root";
auto PlaylistME_1A_MC2D_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2Dminervame1A_RECO_MC_StatsONLYErrorsTRANSWARP_MK.root";
auto PlaylistME_1L_MC2D_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2Dminervame1L_RECO_MC_StatsONLYErrorsTRANSWARP_MK.root";
auto PlaylistME_1M_MC2D_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2Dminervame1M_RECO_MC_StatsONLYErrorsTRANSWARP_MK.root";
auto PlaylistME_1N_MC2D_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2Dminervame1N_RECO_MC_StatsONLYErrorsTRANSWARP_MK.root";


/////////////
// Full Playlist Data
/////////////


auto PlaylistME_1P_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1P_Data.root";
auto PlaylistME_1C_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1C_Data.root";
auto PlaylistME_1D_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1D_Data.root";
auto PlaylistME_1F_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1F_Data.root";
auto PlaylistME_1E_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1E_Data.root";

/////////////
// Empty Playlist  Data
/////////////

auto PlaylistME_1G_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1G_Data.root";
auto PlaylistME_1A_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1A_Data.root";
auto PlaylistME_1L_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1L_Data.root";
auto PlaylistME_1M_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1M_Data.root";
auto PlaylistME_1N_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1N_Data.root";

/// Shouldn't look at Truth Branch Only RECO

/////////////
// Full Playlist Truth
/////////////


/////////////
// Empty Playlist  Truth
/////////////


ME_playlist_RootPathMAP MAP_RootPath_Empty_MC_RECO;
ME_playlist_RootPathMAP MAP_RootPath_Empty_MC_RECO_2D;
ME_playlist_RootPathMAP MAP_RootPath_Empty_DATA;

ME_playlist_RootPathMAP MAP_RootPath_Full_MC_RECO;
ME_playlist_RootPathMAP MAP_RootPath_Full_MC_RECO_2D;
ME_playlist_RootPathMAP MAP_RootPath_Full_DATA;

/////////////////////////////
////Empty
///////////////////////////

MAP_RootPath_Empty_MC_RECO.insert(std::make_pair(EmptyME_playlist_vector.at(0), PlaylistME_1G_MC_path));
MAP_RootPath_Empty_MC_RECO.insert(std::make_pair(EmptyME_playlist_vector.at(1), PlaylistME_1A_MC_path));
MAP_RootPath_Empty_MC_RECO.insert(std::make_pair(EmptyME_playlist_vector.at(2), PlaylistME_1L_MC_path));
MAP_RootPath_Empty_MC_RECO.insert(std::make_pair(EmptyME_playlist_vector.at(3), PlaylistME_1M_MC_path));
MAP_RootPath_Empty_MC_RECO.insert(std::make_pair(EmptyME_playlist_vector.at(4), PlaylistME_1N_MC_path));

MAP_RootPath_Empty_MC_RECO_2D.insert(std::make_pair(EmptyME_playlist_vector.at(0), PlaylistME_1G_MC2D_path));
MAP_RootPath_Empty_MC_RECO_2D.insert(std::make_pair(EmptyME_playlist_vector.at(1), PlaylistME_1A_MC2D_path));
MAP_RootPath_Empty_MC_RECO_2D.insert(std::make_pair(EmptyME_playlist_vector.at(2), PlaylistME_1L_MC2D_path));
MAP_RootPath_Empty_MC_RECO_2D.insert(std::make_pair(EmptyME_playlist_vector.at(3), PlaylistME_1M_MC2D_path));
MAP_RootPath_Empty_MC_RECO_2D.insert(std::make_pair(EmptyME_playlist_vector.at(4), PlaylistME_1N_MC2D_path));




MAP_RootPath_Empty_DATA.insert(std::make_pair(EmptyME_playlist_vector.at(0), PlaylistME_1G_Data_path));
MAP_RootPath_Empty_DATA.insert(std::make_pair(EmptyME_playlist_vector.at(1), PlaylistME_1A_Data_path));
MAP_RootPath_Empty_DATA.insert(std::make_pair(EmptyME_playlist_vector.at(2), PlaylistME_1L_Data_path));
MAP_RootPath_Empty_DATA.insert(std::make_pair(EmptyME_playlist_vector.at(3), PlaylistME_1M_Data_path));
MAP_RootPath_Empty_DATA.insert(std::make_pair(EmptyME_playlist_vector.at(4), PlaylistME_1N_Data_path));

/////////////////////////////
////Full
///////////////////////////

MAP_RootPath_Full_MC_RECO.insert(std::make_pair(FullME_playlist_vector.at(0), PlaylistME_1P_MC_path));
MAP_RootPath_Full_MC_RECO.insert(std::make_pair(FullME_playlist_vector.at(1), PlaylistME_1C_MC_path));
MAP_RootPath_Full_MC_RECO.insert(std::make_pair(FullME_playlist_vector.at(2), PlaylistME_1D_MC_path));
MAP_RootPath_Full_MC_RECO.insert(std::make_pair(FullME_playlist_vector.at(3), PlaylistME_1F_MC_path));
MAP_RootPath_Full_MC_RECO.insert(std::make_pair(FullME_playlist_vector.at(4), PlaylistME_1E_MC_path));


MAP_RootPath_Full_MC_RECO_2D.insert(std::make_pair(FullME_playlist_vector.at(0), PlaylistME_1P_MC2D_path));
MAP_RootPath_Full_MC_RECO_2D.insert(std::make_pair(FullME_playlist_vector.at(1), PlaylistME_1C_MC2D_path));
MAP_RootPath_Full_MC_RECO_2D.insert(std::make_pair(FullME_playlist_vector.at(2), PlaylistME_1D_MC2D_path));
MAP_RootPath_Full_MC_RECO_2D.insert(std::make_pair(FullME_playlist_vector.at(3), PlaylistME_1F_MC2D_path));
MAP_RootPath_Full_MC_RECO_2D.insert(std::make_pair(FullME_playlist_vector.at(4), PlaylistME_1E_MC2D_path));


MAP_RootPath_Full_DATA.insert(std::make_pair(FullME_playlist_vector.at(0), PlaylistME_1P_Data_path));
MAP_RootPath_Full_DATA.insert(std::make_pair(FullME_playlist_vector.at(1), PlaylistME_1C_Data_path));
MAP_RootPath_Full_DATA.insert(std::make_pair(FullME_playlist_vector.at(2), PlaylistME_1D_Data_path));
MAP_RootPath_Full_DATA.insert(std::make_pair(FullME_playlist_vector.at(3), PlaylistME_1F_Data_path));
MAP_RootPath_Full_DATA.insert(std::make_pair(FullME_playlist_vector.at(4), PlaylistME_1E_Data_path));


/////////////////////////////////////////////////////
// Empty
/////////////////////////////////////////////////////

TFile *TFile_ME1G_MC_RECO = new TFile(PlaylistME_1G_MC_path);
TFile *TFile_ME1A_MC_RECO = new TFile(PlaylistME_1A_MC_path);
TFile *TFile_ME1L_MC_RECO = new TFile(PlaylistME_1L_MC_path);
TFile *TFile_ME1M_MC_RECO = new TFile(PlaylistME_1M_MC_path);
TFile *TFile_ME1N_MC_RECO = new TFile(PlaylistME_1N_MC_path);

TFile *TFile_ME1G_MC_RECO2D = new TFile(PlaylistME_1G_MC2D_path);
TFile *TFile_ME1A_MC_RECO2D = new TFile(PlaylistME_1A_MC2D_path);
TFile *TFile_ME1L_MC_RECO2D = new TFile(PlaylistME_1L_MC2D_path);
TFile *TFile_ME1M_MC_RECO2D = new TFile(PlaylistME_1M_MC2D_path);
TFile *TFile_ME1N_MC_RECO2D = new TFile(PlaylistME_1N_MC2D_path);



TFile *TFile_ME1G_DATA = new TFile(PlaylistME_1G_Data_path);
TFile *TFile_ME1A_DATA = new TFile(PlaylistME_1A_Data_path);
TFile *TFile_ME1L_DATA = new TFile(PlaylistME_1L_Data_path);
TFile *TFile_ME1M_DATA = new TFile(PlaylistME_1M_Data_path);
TFile *TFile_ME1N_DATA = new TFile(PlaylistME_1N_Data_path);

/////////////////////////////////////////////////////
// Full
/////////////////////////////////////////////////////
TFile *TFile_ME1P_MC_RECO = new TFile(PlaylistME_1P_MC_path);
TFile *TFile_ME1C_MC_RECO = new TFile(PlaylistME_1C_MC_path);
TFile *TFile_ME1D_MC_RECO = new TFile(PlaylistME_1D_MC_path);
TFile *TFile_ME1E_MC_RECO = new TFile(PlaylistME_1E_MC_path);
TFile *TFile_ME1F_MC_RECO = new TFile(PlaylistME_1F_MC_path);

TFile *TFile_ME1P_MC_RECO2D = new TFile(PlaylistME_1P_MC2D_path);
TFile *TFile_ME1C_MC_RECO2D = new TFile(PlaylistME_1C_MC2D_path);
TFile *TFile_ME1D_MC_RECO2D = new TFile(PlaylistME_1D_MC2D_path);
TFile *TFile_ME1E_MC_RECO2D = new TFile(PlaylistME_1E_MC2D_path);
TFile *TFile_ME1F_MC_RECO2D = new TFile(PlaylistME_1F_MC2D_path);


TFile *TFile_ME1P_DATA = new TFile(PlaylistME_1P_Data_path);
TFile *TFile_ME1C_DATA = new TFile(PlaylistME_1C_Data_path);
TFile *TFile_ME1D_DATA = new TFile(PlaylistME_1D_Data_path);
TFile *TFile_ME1E_DATA = new TFile(PlaylistME_1E_Data_path);
TFile *TFile_ME1F_DATA = new TFile(PlaylistME_1F_Data_path);

ME_playlist_TFileMAP EmptyTFile_Map_MC_RECO;
ME_playlist_TFileMAP EmptyTFile_Map_MC_RECO2D;
ME_playlist_TFileMAP EmptyTFile_Map_DATA;

ME_playlist_TFileMAP FullTFile_Map_MC_RECO;
ME_playlist_TFileMAP FullTFile_Map_MC_RECO2D;
ME_playlist_TFileMAP FullTFile_Map_DATA;

/////////////////////////////////////////////////////
// Empty
/////////////////////////////////////////////////////


EmptyTFile_Map_MC_RECO.insert(std::make_pair(EmptyME_playlist_vector.at(0),TFile_ME1G_MC_RECO));
EmptyTFile_Map_MC_RECO.insert(std::make_pair(EmptyME_playlist_vector.at(1),TFile_ME1A_MC_RECO));
EmptyTFile_Map_MC_RECO.insert(std::make_pair(EmptyME_playlist_vector.at(2),TFile_ME1L_MC_RECO));
EmptyTFile_Map_MC_RECO.insert(std::make_pair(EmptyME_playlist_vector.at(3),TFile_ME1M_MC_RECO));
EmptyTFile_Map_MC_RECO.insert(std::make_pair(EmptyME_playlist_vector.at(4),TFile_ME1N_MC_RECO));

EmptyTFile_Map_MC_RECO2D.insert(std::make_pair(EmptyME_playlist_vector.at(0),TFile_ME1G_MC_RECO2D));
EmptyTFile_Map_MC_RECO2D.insert(std::make_pair(EmptyME_playlist_vector.at(1),TFile_ME1A_MC_RECO2D));
EmptyTFile_Map_MC_RECO2D.insert(std::make_pair(EmptyME_playlist_vector.at(2),TFile_ME1L_MC_RECO2D));
EmptyTFile_Map_MC_RECO2D.insert(std::make_pair(EmptyME_playlist_vector.at(3),TFile_ME1M_MC_RECO2D));
EmptyTFile_Map_MC_RECO2D.insert(std::make_pair(EmptyME_playlist_vector.at(4),TFile_ME1N_MC_RECO2D));


EmptyTFile_Map_DATA.insert(std::make_pair(EmptyME_playlist_vector.at(0),TFile_ME1G_DATA));
EmptyTFile_Map_DATA.insert(std::make_pair(EmptyME_playlist_vector.at(1),TFile_ME1A_DATA));
EmptyTFile_Map_DATA.insert(std::make_pair(EmptyME_playlist_vector.at(2),TFile_ME1L_DATA));
EmptyTFile_Map_DATA.insert(std::make_pair(EmptyME_playlist_vector.at(3),TFile_ME1M_DATA));
EmptyTFile_Map_DATA.insert(std::make_pair(EmptyME_playlist_vector.at(4),TFile_ME1N_DATA));

/////////////////////////////////////////////////////
// Full
/////////////////////////////////////////////////////
FullTFile_Map_MC_RECO.insert(std::make_pair(FullME_playlist_vector.at(0),TFile_ME1P_MC_RECO));
FullTFile_Map_MC_RECO.insert(std::make_pair(FullME_playlist_vector.at(1),TFile_ME1C_MC_RECO));
FullTFile_Map_MC_RECO.insert(std::make_pair(FullME_playlist_vector.at(2),TFile_ME1D_MC_RECO));
FullTFile_Map_MC_RECO.insert(std::make_pair(FullME_playlist_vector.at(3),TFile_ME1F_MC_RECO));
FullTFile_Map_MC_RECO.insert(std::make_pair(FullME_playlist_vector.at(4),TFile_ME1E_MC_RECO));

FullTFile_Map_MC_RECO2D.insert(std::make_pair(FullME_playlist_vector.at(0),TFile_ME1P_MC_RECO2D));
FullTFile_Map_MC_RECO2D.insert(std::make_pair(FullME_playlist_vector.at(1),TFile_ME1C_MC_RECO2D));
FullTFile_Map_MC_RECO2D.insert(std::make_pair(FullME_playlist_vector.at(2),TFile_ME1D_MC_RECO2D));
FullTFile_Map_MC_RECO2D.insert(std::make_pair(FullME_playlist_vector.at(3),TFile_ME1F_MC_RECO2D));
FullTFile_Map_MC_RECO2D.insert(std::make_pair(FullME_playlist_vector.at(4),TFile_ME1E_MC_RECO2D));

FullTFile_Map_DATA.insert(std::make_pair(FullME_playlist_vector.at(0),TFile_ME1P_DATA));
FullTFile_Map_DATA.insert(std::make_pair(FullME_playlist_vector.at(1),TFile_ME1C_DATA));
FullTFile_Map_DATA.insert(std::make_pair(FullME_playlist_vector.at(2),TFile_ME1D_DATA));
FullTFile_Map_DATA.insert(std::make_pair(FullME_playlist_vector.at(3),TFile_ME1F_DATA));
FullTFile_Map_DATA.insert(std::make_pair(FullME_playlist_vector.at(4),TFile_ME1E_DATA));
//////////////
///
/////////////
auto MuonVaribles = GetTransWarpVaribles();

auto outFile = TFile::Open("TransWarp_Hists_MK.root", "RECREATE");


TransWarp_histNames Closure_test_Hist_Pt_names = Constuct_Unfolding_Histname(kP_T,
  "MnvR_Muon_PT_reco",
  "MnvR_Muon_PT_truth",
  "MnvR_Muon_PT_migration",
  "MnvR_Muon_PT_reco",
  "MnvR_Muon_PT_truth"
);

TransWarp_histNames Closure_test_Hist_Pt_Warp_names = Constuct_Unfolding_Histname(kP_T,
  "MnvR_Muon_PT_WarpFunction_reco",
  "MnvR_Muon_PT_WarpFunction_truth",
  "MnvR_Muon_PT_WarpFunction_migration",
  "MnvR_Muon_PT_WarpFunction_reco",
  "MnvR_Muon_PT_WarpFunction_truth"
);

TransWarp_histNames Closure_test_Hist_Pt_Warp_names_plus10 = Constuct_Unfolding_Histname(kP_T,
  "MnvR_Muon_PT_plus10percent_reco",
  "MnvR_Muon_PT_plus10percent_truth",
  "MnvR_Muon_PT_plus10percent_migration",
  "MnvR_Muon_PT_plus10percent_reco",
  "MnvR_Muon_PT_plus10percent_truth"
);

TransWarp_histNames Closure_test_Hist_Pt_Warp_names_minus10 = Constuct_Unfolding_Histname(kP_T,
  "MnvR_Muon_PT_minus10percent_reco",
  "MnvR_Muon_PT_minus10percent_truth",
  "MnvR_Muon_PT_minus10percent_migration",
  "MnvR_Muon_PT_minus10percent_reco",
  "MnvR_Muon_PT_minus10percent_truth"
);


TransWarp_histNames Closure_test_Hist_Pz_names = Constuct_Unfolding_Histname(kP_Z,
  "MnvR_Muon_PZ_reco",
  "MnvR_Muon_PZ_truth",
  "MnvR_Muon_PZ_migration",
  "MnvR_Muon_PZ_reco",
  "MnvR_Muon_PZ_truth"
);

TransWarp_histNames Closure_test_Hist_Pz_Warp_names = Constuct_Unfolding_Histname(kP_Z,
  "MnvR_Muon_PZ_WarpFunction_reco",
  "MnvR_Muon_PZ_WarpFunction_truth",
  "MnvR_Muon_PZ_WarpFunction_migration",
  "MnvR_Muon_PZ_WarpFunction_reco",
  "MnvR_Muon_PZ_WarpFunction_truth"
);

TransWarp_histNames Closure_test_Hist_Pz_Warp_names_plus10 = Constuct_Unfolding_Histname(kP_Z,
  "MnvR_Muon_PZ_plus10percent_reco",
  "MnvR_Muon_PZ_plus10percent_truth",
  "MnvR_Muon_PZ_plus10percent_migration",
  "MnvR_Muon_PZ_plus10percent_reco",
  "MnvR_Muon_PZ_plus10percent_truth"
);

TransWarp_histNames Closure_test_Hist_Pz_Warp_names_minus10 = Constuct_Unfolding_Histname(kP_Z,
  "MnvR_Muon_PZ_minus10percent_reco",
  "MnvR_Muon_PZ_minus10percent_truth",
  "MnvR_Muon_PZ_minus10percent_migration",
  "MnvR_Muon_PZ_minus10percent_reco",
  "MnvR_Muon_PZ_minus10percent_truth"
);



TransWarp_histNames Closure_test_Hist_Theta_names = Constuct_Unfolding_Histname(kAngleWRTB,
  "MnvR_Muon_theta_reco",
  "MnvR_Muon_theta_truth",
  "MnvR_Muon_theta_migration",
  "MnvR_Muon_theta_reco",
  "MnvR_Muon_theta_truth"
);


TransWarp_histNames Closure_test_Hist_Theta_Warp_names = Constuct_Unfolding_Histname(kAngleWRTB,
  "MnvR_Muon_theta_WarpFunction_reco",
  "MnvR_Muon_theta_WarpFunction_truth",
  "MnvR_Muon_theta_WarpFunction_migration",
  "MnvR_Muon_theta_WarpFunction_reco",
  "MnvR_Muon_theta_WarpFunction_truth"
);

TransWarp_histNames Closure_test_Hist_Theta_Warp_names_plus10 = Constuct_Unfolding_Histname(kAngleWRTB,
  "MnvR_Muon_theta_plus10percent_reco",
  "MnvR_Muon_theta_plus10percent_truth",
  "MnvR_Muon_theta_plus10percent_migration",
  "MnvR_Muon_theta_plus10percent_reco",
  "MnvR_Muon_theta_plus10percent_truth"
);


TransWarp_histNames Closure_test_Hist_Theta_Warp_names_minus10 = Constuct_Unfolding_Histname(kAngleWRTB,
  "MnvR_Muon_theta_minus10percent_reco",
  "MnvR_Muon_theta_minus10percent_truth",
  "MnvR_Muon_theta_minus10percent_migration",
  "MnvR_Muon_theta_minus10percent_reco",
  "MnvR_Muon_theta_minus10percent_truth"
);


TransWarp_histNames Closure_test_Hist_E_names = Constuct_Unfolding_Histname(kE,
  "MnvR_Muon_E_reco",
  "MnvR_Muon_E_truth",
  "MnvR_Muon_E_migration",
  "MnvR_Muon_E_reco",
  "MnvR_Muon_E_truth"
);

TransWarp_histNames Closure_test_Hist_E_Warp_names = Constuct_Unfolding_Histname(kE,
  "MnvR_Muon_E_WarpFunction_reco",
  "MnvR_Muon_E_WarpFunction_truth",
  "MnvR_Muon_E_WarpFunction_migration",
  "MnvR_Muon_E_WarpFunction_reco",
  "MnvR_Muon_E_WarpFunction_truth"
);

TransWarp_histNames Closure_test_Hist_E_Warp_names_plus10 = Constuct_Unfolding_Histname(kE,
  "MnvR_Muon_E_plus10percent_reco",
  "MnvR_Muon_E_plus10percent_truth",
  "MnvR_Muon_E_plus10percent_migration",
  "MnvR_Muon_E_plus10percent_reco",
  "MnvR_Muon_E_plus10percent_truth"
);

TransWarp_histNames Closure_test_Hist_E_Warp_names_minus10 = Constuct_Unfolding_Histname(kE,
  "MnvR_Muon_E_minus10percent_reco",
  "MnvR_Muon_E_minus10percent_truth",
  "MnvR_Muon_E_minus10percent_migration",
  "MnvR_Muon_E_minus10percent_reco",
  "MnvR_Muon_E_minus10percent_truth"
);


TransWarp_histNames Closure_test_2DHist_names = Constuct_Unfolding_Histname(kP_T,
  "MnvR_Muon_PZ_PT_reco",
  "MnvR_Muon_PZ_PT_truth",
  "MnvR_Muon_PZ_PT_migration",
  "MnvR_Muon_PZ_PT_reco",
  "MnvR_Muon_PZ_PT_truth"
);

TransWarp_histNames Closure_test_2DHist_names_new = Constuct_Unfolding_Histname(kP_T,
  "MnvR_Muon_PZ_PT_new_reco",
  "MnvR_Muon_PZ_PT_new_truth",
  "MnvR_Muon_PZ_PT_new_migration",
  "MnvR_Muon_PZ_PT_new_reco",
  "MnvR_Muon_PZ_PT_new_truth"
);

TransWarp_histNames Closure_test_2DHist_names_new_Warp = Constuct_Unfolding_Histname(kP_T,
  "MnvR_Muon_PZ_PT_WarpingFunction_reco",
  "MnvR_Muon_PZ_PT_WarpingFunction_truth",
  "MnvR_Muon_PZ_PT_WarpingFunction_migration",
  "MnvR_Muon_PZ_PT_WarpingFunction_reco",
  "MnvR_Muon_PZ_PT_WarpingFunction_truth"
);


TransWarp_histNames Closure_test_2DHist_names_plus10 = Constuct_Unfolding_Histname(kP_T,
  "MnvR_Muon_PZ_PT_plus10percent_reco",
  "MnvR_Muon_PZ_PT_plus10percent_truth",
  "MnvR_Muon_PZ_PT_plus10percent_migration",
  "MnvR_Muon_PZ_PT_plus10percent_reco",
  "MnvR_Muon_PZ_PT_plus10percent_truth"
);

TransWarp_histNames Closure_test_2DHist_names_minus10 = Constuct_Unfolding_Histname(kP_T,
  "MnvR_Muon_PZ_PT_minus10percent_reco",
  "MnvR_Muon_PZ_PT_minus10percent_truth",
  "MnvR_Muon_PZ_PT_minus10percent_migration",
  "MnvR_Muon_PZ_PT_minus10percent_reco",
  "MnvR_Muon_PZ_PT_minus10percent_truth"
);


std::cout<<"found names"<< std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<""<<std::endl;
Print_Transwarp_Histname(Closure_test_Hist_Pt_names);
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"             Constructing Hists Playlist Map"<< std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~FULL~~~~~~~~~~~~~"<<std::endl;

ME_playlist_TransWarp_Hist_Map Closure_PT_Map_Full =  Constuct_TransWarp_Hists_PlaylistMap(Closure_test_Hist_Pt_names,       FullTFile_Map_MC_RECO);
ME_playlist_TransWarp_Hist_Map Closure_PZ_Map_Full =  Constuct_TransWarp_Hists_PlaylistMap(Closure_test_Hist_Pz_names,       FullTFile_Map_MC_RECO);
ME_playlist_TransWarp_Hist_Map Closure_Theta_Map_Full =  Constuct_TransWarp_Hists_PlaylistMap(Closure_test_Hist_Theta_names, FullTFile_Map_MC_RECO);
ME_playlist_TransWarp_Hist_Map Closure_E_Map_Full =  Constuct_TransWarp_Hists_PlaylistMap(Closure_test_Hist_E_names,         FullTFile_Map_MC_RECO);
ME_playlist_TransWarp_2DHist_Map Closure_PZ_PT_Map_Full =  Constuct_TransWarp_2DHists_PlaylistMap(Closure_test_2DHist_names,         FullTFile_Map_MC_RECO2D);
ME_playlist_TransWarp_2DHist_Map Closure_PZ_PT_Map_Full_new =  Constuct_TransWarp_2DHists_PlaylistMap(Closure_test_2DHist_names_new,         FullTFile_Map_MC_RECO2D);
/////////
/// Warp
////////
ME_playlist_TransWarp_Hist_Map   Closure_PT_Map_Full_Warp =  Constuct_TransWarp_Hists_PlaylistMap(Closure_test_Hist_Pt_Warp_names,       FullTFile_Map_MC_RECO);
ME_playlist_TransWarp_Hist_Map   Closure_PZ_Map_Full_Warp =  Constuct_TransWarp_Hists_PlaylistMap(Closure_test_Hist_Pz_Warp_names,       FullTFile_Map_MC_RECO);
ME_playlist_TransWarp_Hist_Map   Closure_Theta_Map_Full_Warp =  Constuct_TransWarp_Hists_PlaylistMap(Closure_test_Hist_Theta_Warp_names, FullTFile_Map_MC_RECO);
ME_playlist_TransWarp_Hist_Map   Closure_E_Map_Full_Warp =  Constuct_TransWarp_Hists_PlaylistMap(Closure_test_Hist_E_Warp_names,         FullTFile_Map_MC_RECO);
ME_playlist_TransWarp_2DHist_Map Closure_PZ_PT_Map_Full_Warp =  Constuct_TransWarp_2DHists_PlaylistMap(Closure_test_2DHist_names_new_Warp,         FullTFile_Map_MC_RECO2D);
// plus 10
ME_playlist_TransWarp_Hist_Map   Closure_PT_Map_Full_plus10 =  Constuct_TransWarp_Hists_PlaylistMap(Closure_test_Hist_Pt_Warp_names_plus10,       FullTFile_Map_MC_RECO);
ME_playlist_TransWarp_Hist_Map   Closure_PZ_Map_Full_plus10 =  Constuct_TransWarp_Hists_PlaylistMap(Closure_test_Hist_Pz_Warp_names_plus10,       FullTFile_Map_MC_RECO);
ME_playlist_TransWarp_Hist_Map   Closure_Theta_Map_Full_plus10 =  Constuct_TransWarp_Hists_PlaylistMap(Closure_test_Hist_Theta_Warp_names_plus10, FullTFile_Map_MC_RECO);
ME_playlist_TransWarp_Hist_Map   Closure_E_Map_Full_plus10 =  Constuct_TransWarp_Hists_PlaylistMap(Closure_test_Hist_E_Warp_names_plus10,         FullTFile_Map_MC_RECO);
ME_playlist_TransWarp_2DHist_Map Closure_PZ_PT_Map_Full_plus10 =  Constuct_TransWarp_2DHists_PlaylistMap(Closure_test_2DHist_names_plus10,         FullTFile_Map_MC_RECO2D);

// Minus 10
ME_playlist_TransWarp_Hist_Map   Closure_PT_Map_Full_minus10 =  Constuct_TransWarp_Hists_PlaylistMap(Closure_test_Hist_Pt_Warp_names_minus10,       FullTFile_Map_MC_RECO);
ME_playlist_TransWarp_Hist_Map   Closure_PZ_Map_Full_minus10 =  Constuct_TransWarp_Hists_PlaylistMap(Closure_test_Hist_Pz_Warp_names_minus10,       FullTFile_Map_MC_RECO);
ME_playlist_TransWarp_Hist_Map   Closure_Theta_Map_Full_minus10 =  Constuct_TransWarp_Hists_PlaylistMap(Closure_test_Hist_Theta_Warp_names_minus10, FullTFile_Map_MC_RECO);
ME_playlist_TransWarp_Hist_Map   Closure_E_Map_Full_minus10 =  Constuct_TransWarp_Hists_PlaylistMap(Closure_test_Hist_E_Warp_names_minus10,         FullTFile_Map_MC_RECO);
ME_playlist_TransWarp_2DHist_Map Closure_PZ_PT_Map_Full_minus10 =  Constuct_TransWarp_2DHists_PlaylistMap(Closure_test_2DHist_names_minus10,         FullTFile_Map_MC_RECO2D);

std::cout<<"~~~~~~~Empty~~~~~~~~~~~~~"<<std::endl;
ME_playlist_TransWarp_Hist_Map   Closure_PT_Map_Empty =  Constuct_TransWarp_Hists_PlaylistMap(Closure_test_Hist_Pt_names,        EmptyTFile_Map_MC_RECO);
ME_playlist_TransWarp_Hist_Map   Closure_PZ_Map_Empty =  Constuct_TransWarp_Hists_PlaylistMap(Closure_test_Hist_Pz_names,        EmptyTFile_Map_MC_RECO);
ME_playlist_TransWarp_Hist_Map   Closure_Theta_Map_Empty =  Constuct_TransWarp_Hists_PlaylistMap(Closure_test_Hist_Theta_names,  EmptyTFile_Map_MC_RECO);
ME_playlist_TransWarp_Hist_Map   Closure_E_Map_Empty =  Constuct_TransWarp_Hists_PlaylistMap(Closure_test_Hist_E_names,          EmptyTFile_Map_MC_RECO);
ME_playlist_TransWarp_2DHist_Map Closure_PZ_PT_Map_Empty =  Constuct_TransWarp_2DHists_PlaylistMap(Closure_test_2DHist_names,   EmptyTFile_Map_MC_RECO2D);
ME_playlist_TransWarp_2DHist_Map Closure_PZ_PT_Map_Empty_new =  Constuct_TransWarp_2DHists_PlaylistMap(Closure_test_2DHist_names_new,   EmptyTFile_Map_MC_RECO2D);

ME_playlist_TransWarp_Hist_Map Closure_PT_Map_Empty_Warp =  Constuct_TransWarp_Hists_PlaylistMap(Closure_test_Hist_Pt_Warp_names,       EmptyTFile_Map_MC_RECO);
ME_playlist_TransWarp_Hist_Map Closure_PZ_Map_Empty_Warp =  Constuct_TransWarp_Hists_PlaylistMap(Closure_test_Hist_Pz_Warp_names,       EmptyTFile_Map_MC_RECO);
ME_playlist_TransWarp_Hist_Map Closure_Theta_Map_Empty_Warp =  Constuct_TransWarp_Hists_PlaylistMap(Closure_test_Hist_Theta_Warp_names, EmptyTFile_Map_MC_RECO);
ME_playlist_TransWarp_Hist_Map Closure_E_Map_Empty_Warp =  Constuct_TransWarp_Hists_PlaylistMap(Closure_test_Hist_E_Warp_names,         EmptyTFile_Map_MC_RECO);
ME_playlist_TransWarp_2DHist_Map Closure_PZ_PT_Map_Empty_Warp =  Constuct_TransWarp_2DHists_PlaylistMap(Closure_test_2DHist_names_new_Warp,         EmptyTFile_Map_MC_RECO2D);

ME_playlist_TransWarp_Hist_Map Closure_PT_Map_Empty_Warp_plus10 =  Constuct_TransWarp_Hists_PlaylistMap(Closure_test_Hist_Pt_Warp_names_plus10,       EmptyTFile_Map_MC_RECO);
ME_playlist_TransWarp_Hist_Map Closure_PZ_Map_Empty_Warp_plus10 =  Constuct_TransWarp_Hists_PlaylistMap(Closure_test_Hist_Pz_Warp_names_plus10,       EmptyTFile_Map_MC_RECO);
ME_playlist_TransWarp_Hist_Map Closure_Theta_Map_Empty_Warp_plus10 =  Constuct_TransWarp_Hists_PlaylistMap(Closure_test_Hist_Theta_Warp_names_plus10, EmptyTFile_Map_MC_RECO);
ME_playlist_TransWarp_Hist_Map Closure_E_Map_Empty_Warp_plus10 =  Constuct_TransWarp_Hists_PlaylistMap(Closure_test_Hist_E_Warp_names_plus10,         EmptyTFile_Map_MC_RECO);
ME_playlist_TransWarp_2DHist_Map Closure_PZ_PT_Map_Empty_Warp_plus10 =  Constuct_TransWarp_2DHists_PlaylistMap(Closure_test_2DHist_names_plus10,         EmptyTFile_Map_MC_RECO2D);

ME_playlist_TransWarp_Hist_Map Closure_PT_Map_Empty_Warp_minus10 =  Constuct_TransWarp_Hists_PlaylistMap(Closure_test_Hist_Pt_Warp_names_minus10,       EmptyTFile_Map_MC_RECO);
ME_playlist_TransWarp_Hist_Map Closure_PZ_Map_Empty_Warp_minus10 =  Constuct_TransWarp_Hists_PlaylistMap(Closure_test_Hist_Pz_Warp_names_minus10,       EmptyTFile_Map_MC_RECO);
ME_playlist_TransWarp_Hist_Map Closure_Theta_Map_Empty_Warp_minus10 =  Constuct_TransWarp_Hists_PlaylistMap(Closure_test_Hist_Theta_Warp_names_minus10, EmptyTFile_Map_MC_RECO);
ME_playlist_TransWarp_Hist_Map Closure_E_Map_Empty_Warp_minus10 =  Constuct_TransWarp_Hists_PlaylistMap(Closure_test_Hist_E_Warp_names_minus10,         EmptyTFile_Map_MC_RECO);
ME_playlist_TransWarp_2DHist_Map Closure_PZ_PT_Map_Empty_Warp_minus10 =  Constuct_TransWarp_2DHists_PlaylistMap(Closure_test_2DHist_names_minus10,         EmptyTFile_Map_MC_RECO2D);


std::cout<<"Size Closure_PT_Map_Full  of Map = "<< Closure_PT_Map_Full.size()<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"                          Combined Maps                     "<< std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~Empty~~~~~~~~~~~~~"<<std::endl;

TransWarp_Hist Closure_PT_Map_EMPTYCombined = Combine_TranWarp_Hists_PlaylistMap(Closure_PT_Map_Empty, EmptyME_playlist_vector.at(0) );
TransWarp_Hist Closure_PZ_Map_EMPTYCombined = Combine_TranWarp_Hists_PlaylistMap(Closure_PZ_Map_Empty, EmptyME_playlist_vector.at(0) );
TransWarp_Hist Closure_Theta_Map_EMPTYCombined = Combine_TranWarp_Hists_PlaylistMap(Closure_Theta_Map_Empty, EmptyME_playlist_vector.at(0) );
TransWarp_Hist Closure_E_Map_EMPTYCombined = Combine_TranWarp_Hists_PlaylistMap(Closure_E_Map_Empty, EmptyME_playlist_vector.at(0) );

TransWarp_Hist Closure_PT_Map_EMPTYCombined_Warp = Combine_TranWarp_Hists_PlaylistMap(Closure_PT_Map_Empty_Warp, EmptyME_playlist_vector.at(0) );
TransWarp_Hist Closure_PZ_Map_EMPTYCombined_Warp = Combine_TranWarp_Hists_PlaylistMap(Closure_PZ_Map_Empty_Warp, EmptyME_playlist_vector.at(0) );
TransWarp_Hist Closure_Theta_Map_EMPTYCombined_Warp = Combine_TranWarp_Hists_PlaylistMap(Closure_Theta_Map_Empty_Warp, EmptyME_playlist_vector.at(0) );
TransWarp_Hist Closure_E_Map_EMPTYCombined_Warp = Combine_TranWarp_Hists_PlaylistMap(Closure_E_Map_Empty_Warp, EmptyME_playlist_vector.at(0) );



TransWarp_2DHist Closure_2D_Map_EMPTYCombined = Combine_TranWarp_2DHists_PlaylistMap(Closure_PZ_PT_Map_Empty, EmptyME_playlist_vector.at(0) );
TransWarp_2DHist Closure_2D_Map_EMPTYCombinednew = Combine_TranWarp_2DHists_PlaylistMap(Closure_PZ_PT_Map_Empty_new, EmptyME_playlist_vector.at(0) );
TransWarp_2DHist Closure_2D_Map_EMPTYCombinednew_Warp = Combine_TranWarp_2DHists_PlaylistMap(Closure_PZ_PT_Map_Empty_Warp, EmptyME_playlist_vector.at(0) );

/// Plus 10

TransWarp_Hist Closure_PT_Map_EMPTYCombined_plus10 = Combine_TranWarp_Hists_PlaylistMap(Closure_PT_Map_Empty_Warp_plus10, EmptyME_playlist_vector.at(0) );
TransWarp_Hist Closure_PZ_Map_EMPTYCombined_plus10 = Combine_TranWarp_Hists_PlaylistMap(Closure_PZ_Map_Empty_Warp_plus10, EmptyME_playlist_vector.at(0) );
TransWarp_Hist Closure_Theta_Map_EMPTYCombined_plus10 = Combine_TranWarp_Hists_PlaylistMap(Closure_Theta_Map_Empty_Warp_plus10, EmptyME_playlist_vector.at(0) );
TransWarp_Hist Closure_E_Map_EMPTYCombined_plus10 = Combine_TranWarp_Hists_PlaylistMap(Closure_E_Map_Empty_Warp_plus10, EmptyME_playlist_vector.at(0) );
TransWarp_2DHist Closure_2D_Map_EMPTYCombined_plus10 = Combine_TranWarp_2DHists_PlaylistMap(Closure_PZ_PT_Map_Empty_Warp_plus10, EmptyME_playlist_vector.at(0) );

//minus 10

TransWarp_Hist Closure_PT_Map_EMPTYCombined_minus10 = Combine_TranWarp_Hists_PlaylistMap(Closure_PT_Map_Empty_Warp_minus10, EmptyME_playlist_vector.at(0) );
TransWarp_Hist Closure_PZ_Map_EMPTYCombined_minus10 = Combine_TranWarp_Hists_PlaylistMap(Closure_PZ_Map_Empty_Warp_minus10, EmptyME_playlist_vector.at(0) );
TransWarp_Hist Closure_Theta_Map_EMPTYCombined_minus10 = Combine_TranWarp_Hists_PlaylistMap(Closure_Theta_Map_Empty_Warp_minus10, EmptyME_playlist_vector.at(0) );
TransWarp_Hist Closure_E_Map_EMPTYCombined_minus10 = Combine_TranWarp_Hists_PlaylistMap(Closure_E_Map_Empty_Warp_minus10, EmptyME_playlist_vector.at(0) );
TransWarp_2DHist Closure_2D_Map_EMPTYCombined_minus10 = Combine_TranWarp_2DHists_PlaylistMap(Closure_PZ_PT_Map_Empty_Warp_minus10, EmptyME_playlist_vector.at(0) );




std::cout<<"~~~~~~~FULL~~~~~~~~~~~~~"<<std::endl;

TransWarp_Hist Closure_PT_Map_FULLCombined = Combine_TranWarp_Hists_PlaylistMap(Closure_PT_Map_Full, FullME_playlist_vector.at(3) );
TransWarp_Hist Closure_PZ_Map_FULLCombined = Combine_TranWarp_Hists_PlaylistMap(Closure_PZ_Map_Full, FullME_playlist_vector.at(3) );
TransWarp_Hist Closure_Theta_Map_FULLCombined = Combine_TranWarp_Hists_PlaylistMap(Closure_Theta_Map_Full, FullME_playlist_vector.at(3) );
TransWarp_Hist Closure_E_Map_FULLCombined = Combine_TranWarp_Hists_PlaylistMap(Closure_E_Map_Full, FullME_playlist_vector.at(3) );
////Warp

TransWarp_Hist Closure_PT_Map_FULLCombined_Warp = Combine_TranWarp_Hists_PlaylistMap(Closure_PT_Map_Full_Warp, FullME_playlist_vector.at(3) );
TransWarp_Hist Closure_PZ_Map_FULLCombined_Warp = Combine_TranWarp_Hists_PlaylistMap(Closure_PZ_Map_Full_Warp, FullME_playlist_vector.at(3) );
TransWarp_Hist Closure_Theta_Map_FULLCombined_Warp = Combine_TranWarp_Hists_PlaylistMap(Closure_Theta_Map_Full_Warp, FullME_playlist_vector.at(3) );
TransWarp_Hist Closure_E_Map_FULLCombined_Warp = Combine_TranWarp_Hists_PlaylistMap(Closure_E_Map_Full_Warp, FullME_playlist_vector.at(3) );
/// plus 10

TransWarp_Hist Closure_PT_Map_FULLCombined_plus10 = Combine_TranWarp_Hists_PlaylistMap(Closure_PT_Map_Full_plus10, FullME_playlist_vector.at(3) );
TransWarp_Hist Closure_PZ_Map_FULLCombined_plus10 = Combine_TranWarp_Hists_PlaylistMap(Closure_PZ_Map_Full_plus10, FullME_playlist_vector.at(3) );
TransWarp_Hist Closure_Theta_Map_FULLCombined_plus10 = Combine_TranWarp_Hists_PlaylistMap(Closure_Theta_Map_Full_plus10, FullME_playlist_vector.at(3) );
TransWarp_Hist Closure_E_Map_FULLCombined_plus10 = Combine_TranWarp_Hists_PlaylistMap(Closure_E_Map_Full_plus10, FullME_playlist_vector.at(3) );

TransWarp_Hist Closure_PT_Map_FULLCombined_minus10 = Combine_TranWarp_Hists_PlaylistMap(Closure_PT_Map_Full_minus10, FullME_playlist_vector.at(3) );
TransWarp_Hist Closure_PZ_Map_FULLCombined_minus10 = Combine_TranWarp_Hists_PlaylistMap(Closure_PZ_Map_Full_minus10, FullME_playlist_vector.at(3) );
TransWarp_Hist Closure_Theta_Map_FULLCombined_minus10 = Combine_TranWarp_Hists_PlaylistMap(Closure_Theta_Map_Full_minus10, FullME_playlist_vector.at(3) );
TransWarp_Hist Closure_E_Map_FULLCombined_minus10 = Combine_TranWarp_Hists_PlaylistMap(Closure_E_Map_Full_minus10, FullME_playlist_vector.at(3) );

TransWarp_2DHist Closure_2D_Map_FullCombined = Combine_TranWarp_2DHists_PlaylistMap(Closure_PZ_PT_Map_Full, FullME_playlist_vector.at(3) );
TransWarp_2DHist Closure_2D_Map_FullCombinednew = Combine_TranWarp_2DHists_PlaylistMap(Closure_PZ_PT_Map_Full_new, FullME_playlist_vector.at(3) );
TransWarp_2DHist Closure_2D_Map_FullCombinednew_Warp = Combine_TranWarp_2DHists_PlaylistMap(Closure_PZ_PT_Map_Full_Warp, FullME_playlist_vector.at(3) );

TransWarp_2DHist Closure_2D_Map_FullCombined_plus10 = Combine_TranWarp_2DHists_PlaylistMap(Closure_PZ_PT_Map_Full_plus10,FullME_playlist_vector.at(3));
TransWarp_2DHist Closure_2D_Map_FullCombined_minus10 = Combine_TranWarp_2DHists_PlaylistMap(Closure_PZ_PT_Map_Full_minus10,FullME_playlist_vector.at(3));


std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~Normalize Hist ~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;


std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~GET POT    ~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
Pot_MapList EmptyPOT_MC_RECO_MAP = Constuct_POT_playlistMap(MAP_RootPath_Empty_MC_RECO, true);
Pot_MapList EmptyPOT_MC_RECO_MAP2D = Constuct_POT_playlistMap(MAP_RootPath_Empty_MC_RECO_2D, true);

Pot_MapList FullPOT_MC_RECO_MAP  = Constuct_POT_playlistMap(MAP_RootPath_Full_MC_RECO, true);
Pot_MapList FullPOT_MC_RECO_MAP2D  = Constuct_POT_playlistMap(MAP_RootPath_Full_MC_RECO_2D, true);


Pot_MapList EmptyPOT_DATA_MAP = Constuct_POT_playlistMap(MAP_RootPath_Empty_DATA, false);
Pot_MapList FullPOT_DATA_MAP  = Constuct_POT_playlistMap(MAP_RootPath_Full_DATA, false);
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~Combined  POT    ~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

const double Empty_MC_POT = Combine_POTFromMap(EmptyPOT_MC_RECO_MAP );
const double Full_MC_POT = Combine_POTFromMap(FullPOT_MC_RECO_MAP );

const double Empty_MC_POT2D = Combine_POTFromMap(EmptyPOT_MC_RECO_MAP2D );
const double Full_MC_POT2D = Combine_POTFromMap(FullPOT_MC_RECO_MAP2D );



const double Empty_DATA_POT = Combine_POTFromMap(EmptyPOT_DATA_MAP );
const double Full_DATA_POT = Combine_POTFromMap(FullPOT_DATA_MAP );

const double Full_MC_Full_Data = Full_DATA_POT / Full_MC_POT;
const double Full_MC_Full_Data2D = Full_DATA_POT / Full_MC_POT2D;

const double Empty_MC_Full_Data = Full_DATA_POT / Empty_MC_POT;
const double Empty_Data_Full_Data = Full_DATA_POT / Empty_DATA_POT;
const double Empty_MC_Full_Data2D = Full_DATA_POT / Empty_MC_POT2D;



std::cout<< "Full_DATA_POT = " <<  Full_DATA_POT << std::endl;
std::cout<< "Full_MC_POT = " <<  Full_MC_POT << std::endl;

POT_Normalize_TranWarp_Hist(Closure_PT_Map_FULLCombined, Full_MC_Full_Data);
POT_Normalize_TranWarp_Hist(Closure_PT_Map_EMPTYCombined, Empty_MC_Full_Data);

POT_Normalize_TranWarp_Hist(Closure_PZ_Map_FULLCombined, Full_MC_Full_Data);
POT_Normalize_TranWarp_Hist(Closure_PZ_Map_EMPTYCombined, Empty_MC_Full_Data);

POT_Normalize_TranWarp_Hist(Closure_Theta_Map_FULLCombined, Full_MC_Full_Data);
POT_Normalize_TranWarp_Hist(Closure_Theta_Map_EMPTYCombined, Empty_MC_Full_Data);

POT_Normalize_TranWarp_Hist(Closure_E_Map_FULLCombined, Full_MC_Full_Data);
POT_Normalize_TranWarp_Hist(Closure_E_Map_EMPTYCombined, Empty_MC_Full_Data);
/////////////////////////////
/////Warp
///////////////////////////

POT_Normalize_TranWarp_Hist(Closure_PT_Map_FULLCombined_Warp, Full_MC_Full_Data);
POT_Normalize_TranWarp_Hist(Closure_PT_Map_EMPTYCombined_Warp, Empty_MC_Full_Data);

POT_Normalize_TranWarp_Hist(Closure_PZ_Map_FULLCombined_Warp, Full_MC_Full_Data);
POT_Normalize_TranWarp_Hist(Closure_PZ_Map_EMPTYCombined_Warp, Empty_MC_Full_Data);

POT_Normalize_TranWarp_Hist(Closure_Theta_Map_FULLCombined_Warp, Full_MC_Full_Data);
POT_Normalize_TranWarp_Hist(Closure_Theta_Map_EMPTYCombined_Warp, Empty_MC_Full_Data);

POT_Normalize_TranWarp_Hist(Closure_E_Map_FULLCombined_Warp, Full_MC_Full_Data);
POT_Normalize_TranWarp_Hist(Closure_E_Map_EMPTYCombined_Warp, Empty_MC_Full_Data);
/////////
POT_Normalize_TranWarp_2DHist(Closure_2D_Map_FullCombined, Full_MC_Full_Data2D);
POT_Normalize_TranWarp_2DHist(Closure_2D_Map_EMPTYCombined, Empty_MC_Full_Data2D);

POT_Normalize_TranWarp_2DHist(Closure_2D_Map_FullCombinednew, Full_MC_Full_Data2D);
POT_Normalize_TranWarp_2DHist(Closure_2D_Map_EMPTYCombinednew, Empty_MC_Full_Data2D);

POT_Normalize_TranWarp_2DHist(Closure_2D_Map_FullCombinednew_Warp, Full_MC_Full_Data2D);
POT_Normalize_TranWarp_2DHist(Closure_2D_Map_EMPTYCombinednew_Warp, Empty_MC_Full_Data2D);

POT_Normalize_TranWarp_2DHist(Closure_2D_Map_FullCombined_plus10, Full_MC_Full_Data2D);
POT_Normalize_TranWarp_2DHist(Closure_2D_Map_EMPTYCombined_plus10, Empty_MC_Full_Data2D);

POT_Normalize_TranWarp_2DHist(Closure_2D_Map_FullCombined_minus10, Full_MC_Full_Data2D);
POT_Normalize_TranWarp_2DHist(Closure_2D_Map_EMPTYCombined_minus10, Empty_MC_Full_Data2D);

//////
//Plus
///////

POT_Normalize_TranWarp_Hist(Closure_PT_Map_FULLCombined_plus10, Full_MC_Full_Data);
POT_Normalize_TranWarp_Hist(Closure_PT_Map_EMPTYCombined_plus10, Empty_MC_Full_Data);

POT_Normalize_TranWarp_Hist(Closure_PZ_Map_FULLCombined_plus10, Full_MC_Full_Data);
POT_Normalize_TranWarp_Hist(Closure_PZ_Map_EMPTYCombined_plus10, Empty_MC_Full_Data);

POT_Normalize_TranWarp_Hist(Closure_Theta_Map_FULLCombined_plus10, Full_MC_Full_Data);
POT_Normalize_TranWarp_Hist(Closure_Theta_Map_EMPTYCombined_plus10, Empty_MC_Full_Data);

POT_Normalize_TranWarp_Hist(Closure_E_Map_FULLCombined_plus10, Full_MC_Full_Data);
POT_Normalize_TranWarp_Hist(Closure_E_Map_EMPTYCombined_plus10, Empty_MC_Full_Data);

/////
///minus
/////
POT_Normalize_TranWarp_Hist(Closure_PT_Map_FULLCombined_minus10, Full_MC_Full_Data);
POT_Normalize_TranWarp_Hist(Closure_PT_Map_EMPTYCombined_minus10, Empty_MC_Full_Data);

POT_Normalize_TranWarp_Hist(Closure_PZ_Map_FULLCombined_minus10, Full_MC_Full_Data);
POT_Normalize_TranWarp_Hist(Closure_PZ_Map_EMPTYCombined_minus10, Empty_MC_Full_Data);

POT_Normalize_TranWarp_Hist(Closure_Theta_Map_FULLCombined_minus10, Full_MC_Full_Data);
POT_Normalize_TranWarp_Hist(Closure_Theta_Map_EMPTYCombined_minus10, Empty_MC_Full_Data);

POT_Normalize_TranWarp_Hist(Closure_E_Map_FULLCombined_minus10, Full_MC_Full_Data);
POT_Normalize_TranWarp_Hist(Closure_E_Map_EMPTYCombined_minus10, Empty_MC_Full_Data);


std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~ Checking Binning   ~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~Subtraction Applied ~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

Subtract_TransWarp_Hist(Closure_PT_Map_FULLCombined,    Closure_PT_Map_EMPTYCombined);
Subtract_TransWarp_Hist(Closure_PZ_Map_FULLCombined,    Closure_PZ_Map_EMPTYCombined);
Subtract_TransWarp_Hist(Closure_Theta_Map_FULLCombined, Closure_Theta_Map_EMPTYCombined);
Subtract_TransWarp_Hist(Closure_E_Map_FULLCombined,     Closure_E_Map_EMPTYCombined);
////////////
// Warp
/////////////
Subtract_TransWarp_Hist(Closure_PT_Map_FULLCombined_Warp,    Closure_PT_Map_EMPTYCombined_Warp);
Subtract_TransWarp_Hist(Closure_PZ_Map_FULLCombined_Warp,    Closure_PZ_Map_EMPTYCombined_Warp);
Subtract_TransWarp_Hist(Closure_Theta_Map_FULLCombined_Warp, Closure_Theta_Map_EMPTYCombined_Warp);
Subtract_TransWarp_Hist(Closure_E_Map_FULLCombined_Warp,     Closure_E_Map_EMPTYCombined_Warp);
///////////////////
Subtract_TransWarp_2DHist(Closure_2D_Map_FullCombined,         Closure_2D_Map_EMPTYCombined);
Subtract_TransWarp_2DHist(Closure_2D_Map_FullCombinednew,      Closure_2D_Map_EMPTYCombinednew);
Subtract_TransWarp_2DHist(Closure_2D_Map_FullCombinednew_Warp, Closure_2D_Map_EMPTYCombinednew_Warp);
////Plus

Subtract_TransWarp_Hist(Closure_PT_Map_FULLCombined_plus10,    Closure_PT_Map_EMPTYCombined_plus10);
Subtract_TransWarp_Hist(Closure_PZ_Map_FULLCombined_plus10,    Closure_PZ_Map_EMPTYCombined_plus10);
Subtract_TransWarp_Hist(Closure_Theta_Map_FULLCombined_plus10, Closure_Theta_Map_EMPTYCombined_plus10);
Subtract_TransWarp_Hist(Closure_E_Map_FULLCombined_plus10,     Closure_E_Map_EMPTYCombined_plus10);
Subtract_TransWarp_2DHist(Closure_2D_Map_FullCombined_plus10, Closure_2D_Map_EMPTYCombined_plus10);

////minus

Subtract_TransWarp_Hist(Closure_PT_Map_FULLCombined_minus10,    Closure_PT_Map_EMPTYCombined_minus10);
Subtract_TransWarp_Hist(Closure_PZ_Map_FULLCombined_minus10,    Closure_PZ_Map_EMPTYCombined_minus10);
Subtract_TransWarp_Hist(Closure_Theta_Map_FULLCombined_minus10, Closure_Theta_Map_EMPTYCombined_minus10);
Subtract_TransWarp_Hist(Closure_E_Map_FULLCombined_minus10,     Closure_E_Map_EMPTYCombined_minus10);
Subtract_TransWarp_2DHist(Closure_2D_Map_FullCombined_minus10, Closure_2D_Map_EMPTYCombined_minus10);


std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~Writing TransWarp Hist ~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

WritetoTFile_TranWarpHist(Closure_PT_Map_FULLCombined, *outFile,    "MuonPT_Closure");
WritetoTFile_TranWarpHist(Closure_PZ_Map_FULLCombined, *outFile,    "MuonPZ_Closure");
WritetoTFile_TranWarpHist(Closure_Theta_Map_FULLCombined, *outFile, "MuonTheta_Closure");
WritetoTFile_TranWarpHist(Closure_E_Map_FULLCombined, *outFile,     "MuonE_Closure");

WritetoTFile_TranWarpHist(Closure_PT_Map_FULLCombined_Warp, *outFile,    "MuonPT_Warp");
WritetoTFile_TranWarpHist(Closure_PZ_Map_FULLCombined_Warp, *outFile,    "MuonPZ_Warp");
WritetoTFile_TranWarpHist(Closure_Theta_Map_FULLCombined_Warp, *outFile, "MuonTheta_Warp");
WritetoTFile_TranWarpHist(Closure_E_Map_FULLCombined_Warp, *outFile,     "MuonE_Warp");

WritetoTFile_TranWarpHist(Closure_PT_Map_FULLCombined_plus10, *outFile,    "MuonPT_plus10");
WritetoTFile_TranWarpHist(Closure_PZ_Map_FULLCombined_plus10, *outFile,    "MuonPZ_plus10");
WritetoTFile_TranWarpHist(Closure_Theta_Map_FULLCombined_plus10, *outFile, "MuonTheta_plus10");
WritetoTFile_TranWarpHist(Closure_E_Map_FULLCombined_plus10, *outFile,     "MuonE_plus10");

WritetoTFile_TranWarpHist(Closure_PT_Map_FULLCombined_minus10, *outFile,    "MuonPT_minus10");
WritetoTFile_TranWarpHist(Closure_PZ_Map_FULLCombined_minus10, *outFile,    "MuonPZ_minus10");
WritetoTFile_TranWarpHist(Closure_Theta_Map_FULLCombined_minus10, *outFile, "MuonTheta_minus10");
WritetoTFile_TranWarpHist(Closure_E_Map_FULLCombined_minus10, *outFile,     "MuonE_minus10");



WritetoTFile_TranWarp2DHist(Closure_2D_Map_FullCombined, *outFile,     "Muon_2DClosure");
WritetoTFile_TranWarp2DHist(Closure_2D_Map_FullCombinednew, *outFile,     "Muon_2DClosureNew");

WritetoTFile_TranWarp2DHist(Closure_2D_Map_FullCombinednew_Warp, *outFile,     "Muon_2D_Warp");

WritetoTFile_TranWarp2DHist(Closure_2D_Map_FullCombined_plus10, *outFile,     "Muon_2D_plus10");
WritetoTFile_TranWarp2DHist(Closure_2D_Map_FullCombined_minus10, *outFile,     "Muon_2D_minus10");

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;





outFile->Close();






} // end of RunTransWarpExtractor




/////////////////////////////////////////////
std::vector<MuonVar> GetTransWarpVaribles() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<MuonVar> MuonVars;

  MuonVars.push_back(kE);
  MuonVars.push_back(kP_Z);
  MuonVars.push_back(kP_T);
  MuonVars.push_back(kAngleWRTB);

  return MuonVars;
//#endif
}

void POT_Normalize_TranWarp_Hist(TransWarp_Hist &inputCross_Hist, double normalize_MC_data){

  inputCross_Hist.mc_reco->Scale(normalize_MC_data);
  inputCross_Hist.mc_truth->Scale(normalize_MC_data);
  inputCross_Hist.data_reco->Scale(normalize_MC_data);
  inputCross_Hist.data_truth->Scale(normalize_MC_data);
  inputCross_Hist.h_Mig->Scale(normalize_MC_data);


}

void POT_Normalize_TranWarp_2DHist(TransWarp_2DHist &inputCross_Hist, double normalize_MC_data){

  inputCross_Hist.mc_reco->Scale(normalize_MC_data);
  inputCross_Hist.mc_truth->Scale(normalize_MC_data);
  inputCross_Hist.data_reco->Scale(normalize_MC_data);
  inputCross_Hist.data_truth->Scale(normalize_MC_data);
  inputCross_Hist.h_Mig->Scale(normalize_MC_data);


}


/*
void AddErrorBands_TOEffDom(CrossSection_Hist &inputCross_Hist){
inputCross_Hist.h_effDom->AddMissingErrorBandsAndFillWithCV(*inputCross_Hist.h_effNum);
return;
}// end of function
*/




void Subtract_TransWarp_Hist(TransWarp_Hist &inputCross_Hist_Full, TransWarp_Hist &inputCross_Hist_Empty){

  inputCross_Hist_Full.mc_reco->Add(inputCross_Hist_Empty.mc_reco,-1);
  inputCross_Hist_Full.mc_truth->Add(inputCross_Hist_Empty.mc_truth,-1);
  inputCross_Hist_Full.data_reco->Add(inputCross_Hist_Empty.data_reco,-1);
  inputCross_Hist_Full.data_truth->Add(inputCross_Hist_Empty.data_truth,-1);
  inputCross_Hist_Full.h_Mig->Add(inputCross_Hist_Empty.h_Mig,-1);
}


void Subtract_TransWarp_2DHist(TransWarp_2DHist &inputCross_Hist_Full, TransWarp_2DHist &inputCross_Hist_Empty){

  inputCross_Hist_Full.mc_reco->Add(inputCross_Hist_Empty.mc_reco,-1);
  inputCross_Hist_Full.mc_truth->Add(inputCross_Hist_Empty.mc_truth,-1);
  inputCross_Hist_Full.data_reco->Add(inputCross_Hist_Empty.data_reco,-1);
  inputCross_Hist_Full.data_truth->Add(inputCross_Hist_Empty.data_truth,-1);
  inputCross_Hist_Full.h_Mig->Add(inputCross_Hist_Empty.h_Mig,-1);



}



std::vector<ME_helium_Playlists> GetFullPlayListVector() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ME_helium_Playlists> Playlist;

  Playlist.push_back(kME1P);
  Playlist.push_back(kME1C);
  Playlist.push_back(kME1D);
  Playlist.push_back(kME1F);
  Playlist.push_back(kME1E);


  return Playlist;
//#endif
}

std::vector<ME_helium_Playlists> GetEmptyPlayListVector() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ME_helium_Playlists> Playlist;
  Playlist.push_back(kME1G);
  Playlist.push_back(kME1A);
  Playlist.push_back(kME1L);
  Playlist.push_back(kME1M);
  Playlist.push_back(kME1N);


  return Playlist;
//#endif
}

////////////////////////////////////////////
//Main Function
/////////////////////////////////////////////

 int main() {

//TH1::AddDirectory(kFALSE);

bool my_norm=0;
std::cout << "Which Normalization?  (0 = POT, 1 = relative equal areas) " << std::endl;
//std::cin >> my_norm;
std::cout << std::boolalpha << my_norm << std::endl;

bool my_debug=true;
std::cout << "Run in Debug Mode? (0 = NO, 1 = YES) " << std::endl;
//std::cin >> my_debug;
std::cout << std::boolalpha << my_debug << std::endl;

int my_Print_Systmatics=0;
std::cout << "Print Error Systmatics?  [ 0 = Total and Groups Systemtics Errors ,  1 = Total Systematic Errors , 2 = none ]" << std::endl;
//std::cin >> my_Print_Systmatics;

std::cout << "Pitched: " << my_Print_Systmatics << std::endl;




RunTransWarpExtractor( my_norm, my_debug,  my_Print_Systmatics);

return 0;

}
