//Author: Christian Nguyen
// Helium Cross Section Extractor.cxx
// Started to Build: May 17 2020
//email: christian2nguyen@ufl.edu

#include "ExtractHeliumCrossSectionHists.h"



const std::vector<PlotUtils::NamedCategory<CH_Signal_type>>
Signal_Selection_categories = {
  PlotUtils::NamedCategory<CH_Signal_type>({kSignal},                 "Signal"),
  PlotUtils::NamedCategory<CH_Signal_type>({kBG_NC},                  "BG NC"),
  PlotUtils::NamedCategory<CH_Signal_type>({kBG_CCwrongsign},         "BG Wrong Sign"),
  PlotUtils::NamedCategory<CH_Signal_type>({kBG_Neutral_secTrk},      "BG neutral recoil Trk"),
};

std::string OUTputRoot_pathway = "/minerva/data/users/cnguyen/CrossSection_Hists_ALLPlaylists";
std::vector<MuonVar> GetCrossSectionVaribles();
std::vector<Muon2DVar> GetCrossSection2DVaribles();
std::vector<ME_helium_Playlists> GetTrackerPlayListVector();
std::vector<ME_helium_Playlists> GetEmptyPlayListVector();
void Make_latexTables_CutMap(CutMap inputMap,char *playlist_name_char, std::string CyroTank_status );
void Playlist_CutTableLatex_Efficiency_Purity(CutMap inputMap , char *playlist_name_char, std::string CyroTank_status   );
void RunCrossSectionExtractor(bool &my_norm, bool &my_debug, int &Print_Systematics){
TH1::AddDirectory(false);
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~       Starting CrossSection Extraction for Helium 1D: ~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
auto TrackerME_playlist_vector = GetTrackerPlayListVector();

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~       Getting Nucleaons in tracker      ~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

TargetUtils TargetTool;

bool ForMC = true;
bool ForData = false;

double nNucleons_MC = TargetTool.GetTrackerNNucleons( 5980, 8422, ForMC );
double nNucleons_Data = TargetTool.GetTrackerNNucleons( 5980, 8422, ForData );

Pot_MapStatusList POT_MC_Status, POT_DATA_Status;
///////////////////////////////////////////
//I want to constuct cross section as a function of muon parameters pT, Pz , E , and theta
// going to try to find E first
///////////////////////////////
// lets start with two playlist F and G
/////////////
// Full Playlist
/////////////
auto PlaylistME_1P_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/MasterAnaDev_minervame1P_RECO_MC_All_SysErrorsOn_Fid_p3.root";
auto PlaylistME_1C_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/MasterAnaDev_minervame1C_RECO_MC_All_SysErrorsOn_Fid_p3.root";
auto PlaylistME_1D_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/MasterAnaDev_minervame1D_RECO_MC_All_SysErrorsOn_Fid_p3.root";
auto PlaylistME_1F_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/MasterAnaDev_minervame1F_RECO_MC_All_SysErrorsOn_Fid_p3.root";
auto PlaylistME_1E_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/MasterAnaDev_minervame1E_RECO_MC_All_SysErrorsOn_Fid_p3.root";
auto PlaylistME_1G_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/MasterAnaDev_minervame1G_RECO_MC_All_SysErrorsOn_Fid_p3.root";
auto PlaylistME_1A_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/MasterAnaDev_minervame1A_RECO_MC_All_SysErrorsOn_Fid_p3.root";
auto PlaylistME_1L_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/MasterAnaDev_minervame1L_RECO_MC_All_SysErrorsOn_Fid_p3.root";
auto PlaylistME_1M_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/MasterAnaDev_minervame1M_RECO_MC_All_SysErrorsOn_Fid_p3.root";
auto PlaylistME_1N_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/MasterAnaDev_minervame1N_RECO_MC_All_SysErrorsOn_Fid_p3.root";
auto PlaylistME_1B_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/MasterAnaDev_minervame1B_RECO_MC_All_SysErrorsOn_Fid_p3.root";
auto PlaylistME_1O_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/MasterAnaDev_minervame1O_RECO_MC_All_SysErrorsOn_Fid_p3.root";

//_RECO_MC_StatsONLYErrors_Fid
//_RECO_MC_All_SysErrorsOn_Fid

/////////////
// Full Playlist Data
/////////////

auto PlaylistME_1P_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles_MasterAnaDev/Histograms_minervame1P_Data.root";
auto PlaylistME_1C_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles_MasterAnaDev/Histograms_minervame1C_Data.root";
auto PlaylistME_1D_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles_MasterAnaDev/Histograms_minervame1D_Data.root";
auto PlaylistME_1F_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles_MasterAnaDev/Histograms_minervame1F_Data.root";
auto PlaylistME_1E_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles_MasterAnaDev/Histograms_minervame1E_Data.root";
auto PlaylistME_1G_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles_MasterAnaDev/Histograms_minervame1G_Data.root";
auto PlaylistME_1A_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles_MasterAnaDev/Histograms_minervame1A_Data.root";
auto PlaylistME_1L_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles_MasterAnaDev/Histograms_minervame1L_Data.root";
auto PlaylistME_1M_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles_MasterAnaDev/Histograms_minervame1M_Data.root";
auto PlaylistME_1N_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles_MasterAnaDev/Histograms_minervame1N_Data.root";
auto PlaylistME_1B_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles_MasterAnaDev/Histograms_minervame1B_Data.root";
auto PlaylistME_1O_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles_MasterAnaDev/Histograms_minervame1O_Data.root";

/////////////
// Full Playlist Truth
/////////////


auto PlaylistME_1P_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/Histograms_TRUTH_MasterAnaDev_minervame1P_TRUTH_All_SysErrorsOn_Fid.root";
auto PlaylistME_1C_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/Histograms_TRUTH_MasterAnaDev_minervame1C_TRUTH_All_SysErrorsOn_Fid.root";
auto PlaylistME_1D_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/Histograms_TRUTH_MasterAnaDev_minervame1D_TRUTH_All_SysErrorsOn_Fid.root";
auto PlaylistME_1F_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/Histograms_TRUTH_MasterAnaDev_minervame1F_TRUTH_All_SysErrorsOn_Fid.root";
auto PlaylistME_1E_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/Histograms_TRUTH_MasterAnaDev_minervame1E_TRUTH_All_SysErrorsOn_Fid.root";
auto PlaylistME_1G_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/Histograms_TRUTH_MasterAnaDev_minervame1G_TRUTH_All_SysErrorsOn_Fid.root";
auto PlaylistME_1A_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/Histograms_TRUTH_MasterAnaDev_minervame1A_TRUTH_All_SysErrorsOn_Fid.root";
auto PlaylistME_1L_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/Histograms_TRUTH_MasterAnaDev_minervame1L_TRUTH_All_SysErrorsOn_Fid.root";
auto PlaylistME_1M_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/Histograms_TRUTH_MasterAnaDev_minervame1M_TRUTH_All_SysErrorsOn_Fid.root";
auto PlaylistME_1N_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/Histograms_TRUTH_MasterAnaDev_minervame1N_TRUTH_All_SysErrorsOn_Fid.root";
auto PlaylistME_1B_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/Histograms_TRUTH_MasterAnaDev_minervame1B_TRUTH_All_SysErrorsOn_Fid.root";
auto PlaylistME_1O_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/Histograms_TRUTH_MasterAnaDev_minervame1O_TRUTH_All_SysErrorsOn_Fid.root";
//All_SysErrorsOn_Fid



auto PlaylistME_1P_MC_FLUX_TRUTH_path = "/minerva/data/users/cnguyen/ME_Flux/Histograms_TRUTH_MasterAnaDev_FLUX_minervame1P_TRUTH_All_SysErrorsOn_Fid.root";
auto PlaylistME_1C_MC_FLUX_TRUTH_path = "/minerva/data/users/cnguyen/ME_Flux/Histograms_TRUTH_MasterAnaDev_FLUX_minervame1C_TRUTH_All_SysErrorsOn_Fid.root";
auto PlaylistME_1D_MC_FLUX_TRUTH_path = "/minerva/data/users/cnguyen/ME_Flux/Histograms_TRUTH_MasterAnaDev_FLUX_minervame1D_TRUTH_All_SysErrorsOn_Fid.root";
auto PlaylistME_1F_MC_FLUX_TRUTH_path = "/minerva/data/users/cnguyen/ME_Flux/Histograms_TRUTH_MasterAnaDev_FLUX_minervame1F_TRUTH_All_SysErrorsOn_Fid.root";
auto PlaylistME_1E_MC_FLUX_TRUTH_path = "/minerva/data/users/cnguyen/ME_Flux/Histograms_TRUTH_MasterAnaDev_FLUX_minervame1E_TRUTH_All_SysErrorsOn_Fid.root";
auto PlaylistME_1G_MC_FLUX_TRUTH_path = "/minerva/data/users/cnguyen/ME_Flux/Histograms_TRUTH_MasterAnaDev_FLUX_minervame1G_TRUTH_All_SysErrorsOn_Fid.root";
auto PlaylistME_1A_MC_FLUX_TRUTH_path = "/minerva/data/users/cnguyen/ME_Flux/Histograms_TRUTH_MasterAnaDev_FLUX_minervame1A_TRUTH_All_SysErrorsOn_Fid.root";
auto PlaylistME_1L_MC_FLUX_TRUTH_path = "/minerva/data/users/cnguyen/ME_Flux/Histograms_TRUTH_MasterAnaDev_FLUX_minervame1L_TRUTH_All_SysErrorsOn_Fid.root";
auto PlaylistME_1M_MC_FLUX_TRUTH_path = "/minerva/data/users/cnguyen/ME_Flux/Histograms_TRUTH_MasterAnaDev_FLUX_minervame1M_TRUTH_All_SysErrorsOn_Fid.root";
auto PlaylistME_1N_MC_FLUX_TRUTH_path = "/minerva/data/users/cnguyen/ME_Flux/Histograms_TRUTH_MasterAnaDev_FLUX_minervame1N_TRUTH_All_SysErrorsOn_Fid.root";
auto PlaylistME_1B_MC_FLUX_TRUTH_path = "/minerva/data/users/cnguyen/ME_Flux/Histograms_TRUTH_MasterAnaDev_FLUX_minervame1B_TRUTH_All_SysErrorsOn_Fid.root";
auto PlaylistME_1O_MC_FLUX_TRUTH_path = "/minerva/data/users/cnguyen/ME_Flux/Histograms_TRUTH_MasterAnaDev_FLUX_minervame1O_TRUTH_All_SysErrorsOn_Fid.root";


auto PlaylistME_CrossSection_Path_tracker_1A = "/pnfs/minerva/persistent/users/anezkak/fluxConstraint/Nu_flux/Hists_EventSelection_minervame1A_FluxConstraint_optimPetal_sys_t99_z99_Nu.root";
auto PlaylistME_CrossSection_Path_tracker_1B = "/pnfs/minerva/persistent/users/anezkak/fluxConstraint/Nu_flux/Hists_EventSelection_minervame1B_FluxConstraint_optimPetal_sys_t99_z99_Nu.root";
auto PlaylistME_CrossSection_Path_tracker_1C = "/pnfs/minerva/persistent/users/anezkak/fluxConstraint/Nu_flux/Hists_EventSelection_minervame1C_FluxConstraint_optimPetal_sys_t99_z99_Nu.root";
auto PlaylistME_CrossSection_Path_tracker_1D = "/pnfs/minerva/persistent/users/anezkak/fluxConstraint/Nu_flux/Hists_EventSelection_minervame1D_FluxConstraint_optimPetal_sys_t99_z99_Nu.root";
auto PlaylistME_CrossSection_Path_tracker_1E = "/pnfs/minerva/persistent/users/anezkak/fluxConstraint/Nu_flux/Hists_EventSelection_minervame1E_FluxConstraint_optimPetal_sys_t99_z99_Nu.root";
auto PlaylistME_CrossSection_Path_tracker_1F = "/pnfs/minerva/persistent/users/anezkak/fluxConstraint/Nu_flux/Hists_EventSelection_minervame1F_FluxConstraint_optimPetal_sys_t99_z99_Nu.root";
auto PlaylistME_CrossSection_Path_tracker_1G = "/pnfs/minerva/persistent/users/anezkak/fluxConstraint/Nu_flux/Hists_EventSelection_minervame1G_FluxConstraint_optimPetal_sys_t99_z99_Nu.root";
auto PlaylistME_CrossSection_Path_tracker_1L = "/pnfs/minerva/persistent/users/anezkak/fluxConstraint/Nu_flux/Hists_EventSelection_minervame1L_FluxConstraint_optimPetal_sys_t99_z99_Nu.root";
auto PlaylistME_CrossSection_Path_tracker_1M = "/pnfs/minerva/persistent/users/anezkak/fluxConstraint/Nu_flux/Hists_EventSelection_minervame1M_FluxConstraint_optimPetal_sys_t99_z99_Nu.root";
auto PlaylistME_CrossSection_Path_tracker_1N = "/pnfs/minerva/persistent/users/anezkak/fluxConstraint/Nu_flux/Hists_EventSelection_minervame1N_FluxConstraint_optimPetal_sys_t99_z99_Nu.root";
auto PlaylistME_CrossSection_Path_tracker_1O = "/pnfs/minerva/persistent/users/anezkak/fluxConstraint/Nu_flux/Hists_EventSelection_minervame1O_FluxConstraint_optimPetal_sys_t99_z99_Nu.root";
auto PlaylistME_CrossSection_Path_tracker_1P = "/pnfs/minerva/persistent/users/anezkak/fluxConstraint/Nu_flux/Hists_EventSelection_minervame1P_FluxConstraint_optimPetal_sys_t99_z99_Nu.root";

TFile *TFile_Tracker_1A= new TFile(PlaylistME_CrossSection_Path_tracker_1A);
TFile *TFile_Tracker_1B= new TFile(PlaylistME_CrossSection_Path_tracker_1B);
TFile *TFile_Tracker_1C= new TFile(PlaylistME_CrossSection_Path_tracker_1C);
TFile *TFile_Tracker_1D= new TFile(PlaylistME_CrossSection_Path_tracker_1D);
TFile *TFile_Tracker_1E= new TFile(PlaylistME_CrossSection_Path_tracker_1E);
TFile *TFile_Tracker_1F= new TFile(PlaylistME_CrossSection_Path_tracker_1F);
TFile *TFile_Tracker_1G= new TFile(PlaylistME_CrossSection_Path_tracker_1G);
TFile *TFile_Tracker_1L= new TFile(PlaylistME_CrossSection_Path_tracker_1L);
TFile *TFile_Tracker_1M= new TFile(PlaylistME_CrossSection_Path_tracker_1M);
TFile *TFile_Tracker_1N= new TFile(PlaylistME_CrossSection_Path_tracker_1N);
TFile *TFile_Tracker_1O= new TFile(PlaylistME_CrossSection_Path_tracker_1O);
TFile *TFile_Tracker_1P= new TFile(PlaylistME_CrossSection_Path_tracker_1P);


ME_playlist_TFileMAP TrackerTFile_Map_MC_TRACKER_Anezkak;
/////////////////////////////////////////////////////
// Empty
/////////////////////////////////////////////////////


TrackerTFile_Map_MC_TRACKER_Anezkak.insert(std::make_pair(TrackerME_playlist_vector.at(0), TFile_Tracker_1P));
TrackerTFile_Map_MC_TRACKER_Anezkak.insert(std::make_pair(TrackerME_playlist_vector.at(1), TFile_Tracker_1C));
TrackerTFile_Map_MC_TRACKER_Anezkak.insert(std::make_pair(TrackerME_playlist_vector.at(2), TFile_Tracker_1D));
TrackerTFile_Map_MC_TRACKER_Anezkak.insert(std::make_pair(TrackerME_playlist_vector.at(3), TFile_Tracker_1F));
TrackerTFile_Map_MC_TRACKER_Anezkak.insert(std::make_pair(TrackerME_playlist_vector.at(4), TFile_Tracker_1E));
TrackerTFile_Map_MC_TRACKER_Anezkak.insert(std::make_pair(TrackerME_playlist_vector.at(5), TFile_Tracker_1G));
TrackerTFile_Map_MC_TRACKER_Anezkak.insert(std::make_pair(TrackerME_playlist_vector.at(6), TFile_Tracker_1A));
TrackerTFile_Map_MC_TRACKER_Anezkak.insert(std::make_pair(TrackerME_playlist_vector.at(7), TFile_Tracker_1L));
TrackerTFile_Map_MC_TRACKER_Anezkak.insert(std::make_pair(TrackerME_playlist_vector.at(8), TFile_Tracker_1M));
TrackerTFile_Map_MC_TRACKER_Anezkak.insert(std::make_pair(TrackerME_playlist_vector.at(9), TFile_Tracker_1N));
TrackerTFile_Map_MC_TRACKER_Anezkak.insert(std::make_pair(TrackerME_playlist_vector.at(10),TFile_Tracker_1B));
TrackerTFile_Map_MC_TRACKER_Anezkak.insert(std::make_pair(TrackerME_playlist_vector.at(11),TFile_Tracker_1O));




ME_playlist_RootPathMAP MAP_RootPath_Tracker_MC_RECO;
ME_playlist_RootPathMAP MAP_RootPath_Tracker_MC_TRUTH;
ME_playlist_RootPathMAP MAP_RootPath_Tracker_DATA;
//ME_playlist_RootPathMAP MAP_RootPath_Tracker_MC_TRUTH_Flux;
/////////////////////////////
////
///////////////////////////
MAP_RootPath_Tracker_MC_RECO.insert(std::make_pair(TrackerME_playlist_vector.at(0), PlaylistME_1P_MC_path));
MAP_RootPath_Tracker_MC_RECO.insert(std::make_pair(TrackerME_playlist_vector.at(1), PlaylistME_1C_MC_path));
MAP_RootPath_Tracker_MC_RECO.insert(std::make_pair(TrackerME_playlist_vector.at(2), PlaylistME_1D_MC_path));
MAP_RootPath_Tracker_MC_RECO.insert(std::make_pair(TrackerME_playlist_vector.at(3), PlaylistME_1F_MC_path));
MAP_RootPath_Tracker_MC_RECO.insert(std::make_pair(TrackerME_playlist_vector.at(4), PlaylistME_1E_MC_path));
MAP_RootPath_Tracker_MC_RECO.insert(std::make_pair(TrackerME_playlist_vector.at(5), PlaylistME_1G_MC_path));
MAP_RootPath_Tracker_MC_RECO.insert(std::make_pair(TrackerME_playlist_vector.at(6), PlaylistME_1A_MC_path));
MAP_RootPath_Tracker_MC_RECO.insert(std::make_pair(TrackerME_playlist_vector.at(7), PlaylistME_1L_MC_path));
MAP_RootPath_Tracker_MC_RECO.insert(std::make_pair(TrackerME_playlist_vector.at(8), PlaylistME_1M_MC_path));
MAP_RootPath_Tracker_MC_RECO.insert(std::make_pair(TrackerME_playlist_vector.at(9), PlaylistME_1N_MC_path));
MAP_RootPath_Tracker_MC_RECO.insert(std::make_pair(TrackerME_playlist_vector.at(10), PlaylistME_1B_MC_path));
MAP_RootPath_Tracker_MC_RECO.insert(std::make_pair(TrackerME_playlist_vector.at(11), PlaylistME_1O_MC_path));

MAP_RootPath_Tracker_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(0), PlaylistME_1P_MC_TRUTH_path));
MAP_RootPath_Tracker_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(1), PlaylistME_1C_MC_TRUTH_path));
MAP_RootPath_Tracker_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(2), PlaylistME_1D_MC_TRUTH_path));
MAP_RootPath_Tracker_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(3), PlaylistME_1F_MC_TRUTH_path));
MAP_RootPath_Tracker_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(4), PlaylistME_1E_MC_TRUTH_path));
MAP_RootPath_Tracker_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(5), PlaylistME_1G_MC_TRUTH_path));
MAP_RootPath_Tracker_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(6), PlaylistME_1A_MC_TRUTH_path));
MAP_RootPath_Tracker_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(7), PlaylistME_1L_MC_TRUTH_path));
MAP_RootPath_Tracker_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(8), PlaylistME_1M_MC_TRUTH_path));
MAP_RootPath_Tracker_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(9), PlaylistME_1N_MC_TRUTH_path));
MAP_RootPath_Tracker_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(10), PlaylistME_1B_MC_TRUTH_path));
MAP_RootPath_Tracker_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(11), PlaylistME_1O_MC_TRUTH_path));

MAP_RootPath_Tracker_DATA.insert(std::make_pair(TrackerME_playlist_vector.at(0), PlaylistME_1P_Data_path));
MAP_RootPath_Tracker_DATA.insert(std::make_pair(TrackerME_playlist_vector.at(1), PlaylistME_1C_Data_path));
MAP_RootPath_Tracker_DATA.insert(std::make_pair(TrackerME_playlist_vector.at(2), PlaylistME_1D_Data_path));
MAP_RootPath_Tracker_DATA.insert(std::make_pair(TrackerME_playlist_vector.at(3), PlaylistME_1F_Data_path));
MAP_RootPath_Tracker_DATA.insert(std::make_pair(TrackerME_playlist_vector.at(4), PlaylistME_1E_Data_path));
MAP_RootPath_Tracker_DATA.insert(std::make_pair(TrackerME_playlist_vector.at(5), PlaylistME_1G_Data_path));
MAP_RootPath_Tracker_DATA.insert(std::make_pair(TrackerME_playlist_vector.at(6), PlaylistME_1A_Data_path));
MAP_RootPath_Tracker_DATA.insert(std::make_pair(TrackerME_playlist_vector.at(7), PlaylistME_1L_Data_path));
MAP_RootPath_Tracker_DATA.insert(std::make_pair(TrackerME_playlist_vector.at(8), PlaylistME_1M_Data_path));
MAP_RootPath_Tracker_DATA.insert(std::make_pair(TrackerME_playlist_vector.at(9), PlaylistME_1N_Data_path));
MAP_RootPath_Tracker_DATA.insert(std::make_pair(TrackerME_playlist_vector.at(10), PlaylistME_1B_Data_path));
MAP_RootPath_Tracker_DATA.insert(std::make_pair(TrackerME_playlist_vector.at(11), PlaylistME_1O_Data_path));
/////////////////////////////
////Flux
///////////////////////////

//MAP_RootPath_Tracker_MC_TRUTH_Flux.insert(std::make_pair(TrackerME_playlist_vector.at(0),  PlaylistME_1P_MC_FLUX_TRUTH_path));
//MAP_RootPath_Tracker_MC_TRUTH_Flux.insert(std::make_pair(TrackerME_playlist_vector.at(1),  PlaylistME_1C_MC_FLUX_TRUTH_path));
//MAP_RootPath_Tracker_MC_TRUTH_Flux.insert(std::make_pair(TrackerME_playlist_vector.at(2),  PlaylistME_1D_MC_FLUX_TRUTH_path));
//MAP_RootPath_Tracker_MC_TRUTH_Flux.insert(std::make_pair(TrackerME_playlist_vector.at(3),  PlaylistME_1F_MC_FLUX_TRUTH_path));
//MAP_RootPath_Tracker_MC_TRUTH_Flux.insert(std::make_pair(TrackerME_playlist_vector.at(4),  PlaylistME_1E_MC_FLUX_TRUTH_path));
//MAP_RootPath_Tracker_MC_TRUTH_Flux.insert(std::make_pair(TrackerME_playlist_vector.at(5),  PlaylistME_1G_MC_FLUX_TRUTH_path));
//MAP_RootPath_Tracker_MC_TRUTH_Flux.insert(std::make_pair(TrackerME_playlist_vector.at(6),  PlaylistME_1A_MC_FLUX_TRUTH_path));
//MAP_RootPath_Tracker_MC_TRUTH_Flux.insert(std::make_pair(TrackerME_playlist_vector.at(7),  PlaylistME_1L_MC_FLUX_TRUTH_path));
//MAP_RootPath_Tracker_MC_TRUTH_Flux.insert(std::make_pair(TrackerME_playlist_vector.at(8),  PlaylistME_1M_MC_FLUX_TRUTH_path));
//MAP_RootPath_Tracker_MC_TRUTH_Flux.insert(std::make_pair(TrackerME_playlist_vector.at(9),  PlaylistME_1N_MC_FLUX_TRUTH_path));
//MAP_RootPath_Tracker_MC_TRUTH_Flux.insert(std::make_pair(TrackerME_playlist_vector.at(10), PlaylistME_1B_MC_FLUX_TRUTH_path));
//MAP_RootPath_Tracker_MC_TRUTH_Flux.insert(std::make_pair(TrackerME_playlist_vector.at(11), PlaylistME_1O_MC_FLUX_TRUTH_path));





/////////////////////////////////////////////////////
// TFile for Full
/////////////////////////////////////////////////////
TFile *TFile_ME1P_MC_RECO = new TFile(PlaylistME_1P_MC_path);
TFile *TFile_ME1C_MC_RECO = new TFile(PlaylistME_1C_MC_path);
TFile *TFile_ME1D_MC_RECO = new TFile(PlaylistME_1D_MC_path);
TFile *TFile_ME1E_MC_RECO = new TFile(PlaylistME_1E_MC_path);
TFile *TFile_ME1F_MC_RECO = new TFile(PlaylistME_1F_MC_path);
TFile *TFile_ME1G_MC_RECO = new TFile(PlaylistME_1G_MC_path);
TFile *TFile_ME1A_MC_RECO = new TFile(PlaylistME_1A_MC_path);
TFile *TFile_ME1L_MC_RECO = new TFile(PlaylistME_1L_MC_path);
TFile *TFile_ME1M_MC_RECO = new TFile(PlaylistME_1M_MC_path);
TFile *TFile_ME1N_MC_RECO = new TFile(PlaylistME_1N_MC_path);
TFile *TFile_ME1B_MC_RECO = new TFile(PlaylistME_1B_MC_path);
TFile *TFile_ME1O_MC_RECO = new TFile(PlaylistME_1O_MC_path);
////////
TFile *TFile_ME1P_MC_TRUTH = new TFile(PlaylistME_1P_MC_TRUTH_path);
TFile *TFile_ME1C_MC_TRUTH = new TFile(PlaylistME_1C_MC_TRUTH_path);
TFile *TFile_ME1D_MC_TRUTH = new TFile(PlaylistME_1D_MC_TRUTH_path);
TFile *TFile_ME1E_MC_TRUTH = new TFile(PlaylistME_1E_MC_TRUTH_path);
TFile *TFile_ME1F_MC_TRUTH = new TFile(PlaylistME_1F_MC_TRUTH_path);
TFile *TFile_ME1G_MC_TRUTH = new TFile(PlaylistME_1G_MC_TRUTH_path);
TFile *TFile_ME1A_MC_TRUTH = new TFile(PlaylistME_1A_MC_TRUTH_path);
TFile *TFile_ME1L_MC_TRUTH = new TFile(PlaylistME_1L_MC_TRUTH_path);
TFile *TFile_ME1M_MC_TRUTH = new TFile(PlaylistME_1M_MC_TRUTH_path);
TFile *TFile_ME1N_MC_TRUTH = new TFile(PlaylistME_1N_MC_TRUTH_path);
TFile *TFile_ME1B_MC_TRUTH = new TFile(PlaylistME_1B_MC_TRUTH_path);
TFile *TFile_ME1O_MC_TRUTH = new TFile(PlaylistME_1O_MC_TRUTH_path);
//////////
TFile *TFile_ME1P_DATA = new TFile(PlaylistME_1P_Data_path);
TFile *TFile_ME1C_DATA = new TFile(PlaylistME_1C_Data_path);
TFile *TFile_ME1D_DATA = new TFile(PlaylistME_1D_Data_path);
TFile *TFile_ME1E_DATA = new TFile(PlaylistME_1E_Data_path);
TFile *TFile_ME1F_DATA = new TFile(PlaylistME_1F_Data_path);
TFile *TFile_ME1G_DATA = new TFile(PlaylistME_1G_Data_path);
TFile *TFile_ME1A_DATA = new TFile(PlaylistME_1A_Data_path);
TFile *TFile_ME1L_DATA = new TFile(PlaylistME_1L_Data_path);
TFile *TFile_ME1M_DATA = new TFile(PlaylistME_1M_Data_path);
TFile *TFile_ME1N_DATA = new TFile(PlaylistME_1N_Data_path);
TFile *TFile_ME1B_DATA = new TFile(PlaylistME_1B_Data_path);
TFile *TFile_ME1O_DATA = new TFile(PlaylistME_1O_Data_path);
/////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////
TFile *TFile_ME1P_MC_TRUTH_FLUX = new TFile(PlaylistME_1P_MC_FLUX_TRUTH_path);
TFile *TFile_ME1C_MC_TRUTH_FLUX = new TFile(PlaylistME_1C_MC_FLUX_TRUTH_path);
TFile *TFile_ME1D_MC_TRUTH_FLUX = new TFile(PlaylistME_1D_MC_FLUX_TRUTH_path);
TFile *TFile_ME1E_MC_TRUTH_FLUX = new TFile(PlaylistME_1E_MC_FLUX_TRUTH_path);
TFile *TFile_ME1F_MC_TRUTH_FLUX = new TFile(PlaylistME_1F_MC_FLUX_TRUTH_path);
TFile *TFile_ME1G_MC_TRUTH_FLUX = new TFile(PlaylistME_1G_MC_FLUX_TRUTH_path);
TFile *TFile_ME1A_MC_TRUTH_FLUX = new TFile(PlaylistME_1A_MC_FLUX_TRUTH_path);
TFile *TFile_ME1L_MC_TRUTH_FLUX = new TFile(PlaylistME_1L_MC_FLUX_TRUTH_path);
TFile *TFile_ME1M_MC_TRUTH_FLUX = new TFile(PlaylistME_1M_MC_FLUX_TRUTH_path);
TFile *TFile_ME1N_MC_TRUTH_FLUX = new TFile(PlaylistME_1N_MC_FLUX_TRUTH_path);
TFile *TFile_ME1B_MC_TRUTH_FLUX = new TFile(PlaylistME_1B_MC_FLUX_TRUTH_path);
TFile *TFile_ME1O_MC_TRUTH_FLUX = new TFile(PlaylistME_1O_MC_FLUX_TRUTH_path);





ME_playlist_TFileMAP TrackerTFile_Map_MC_RECO;
ME_playlist_TFileMAP TrackerTFile_Map_MC_TRUTH;
ME_playlist_TFileMAP TrackerTFile_Map_DATA;
ME_playlist_TFileMAP TrackerTFile_Map_MC_TRUTH_FLUX;
/////////////////////////////////////////////////////
// Empty
/////////////////////////////////////////////////////


TrackerTFile_Map_MC_RECO.insert(std::make_pair(TrackerME_playlist_vector.at(0),TFile_ME1P_MC_RECO));
TrackerTFile_Map_MC_RECO.insert(std::make_pair(TrackerME_playlist_vector.at(1),TFile_ME1C_MC_RECO));
TrackerTFile_Map_MC_RECO.insert(std::make_pair(TrackerME_playlist_vector.at(2),TFile_ME1D_MC_RECO));
TrackerTFile_Map_MC_RECO.insert(std::make_pair(TrackerME_playlist_vector.at(3),TFile_ME1F_MC_RECO));
TrackerTFile_Map_MC_RECO.insert(std::make_pair(TrackerME_playlist_vector.at(4),TFile_ME1E_MC_RECO));
TrackerTFile_Map_MC_RECO.insert(std::make_pair(TrackerME_playlist_vector.at(5),TFile_ME1G_MC_RECO));
TrackerTFile_Map_MC_RECO.insert(std::make_pair(TrackerME_playlist_vector.at(6),TFile_ME1A_MC_RECO));
TrackerTFile_Map_MC_RECO.insert(std::make_pair(TrackerME_playlist_vector.at(7),TFile_ME1L_MC_RECO));
TrackerTFile_Map_MC_RECO.insert(std::make_pair(TrackerME_playlist_vector.at(8),TFile_ME1M_MC_RECO));
TrackerTFile_Map_MC_RECO.insert(std::make_pair(TrackerME_playlist_vector.at(9),TFile_ME1N_MC_RECO));
TrackerTFile_Map_MC_RECO.insert(std::make_pair(TrackerME_playlist_vector.at(10),TFile_ME1B_MC_RECO));
TrackerTFile_Map_MC_RECO.insert(std::make_pair(TrackerME_playlist_vector.at(11),TFile_ME1O_MC_RECO));


TrackerTFile_Map_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(0),TFile_ME1P_MC_TRUTH));
TrackerTFile_Map_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(1),TFile_ME1C_MC_TRUTH));
TrackerTFile_Map_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(2),TFile_ME1D_MC_TRUTH));
TrackerTFile_Map_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(3),TFile_ME1F_MC_TRUTH));
TrackerTFile_Map_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(4),TFile_ME1E_MC_TRUTH));
TrackerTFile_Map_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(5),TFile_ME1G_MC_TRUTH));
TrackerTFile_Map_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(6),TFile_ME1A_MC_TRUTH));
TrackerTFile_Map_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(7),TFile_ME1L_MC_TRUTH));
TrackerTFile_Map_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(8),TFile_ME1M_MC_TRUTH));
TrackerTFile_Map_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(9),TFile_ME1N_MC_TRUTH));
TrackerTFile_Map_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(10),TFile_ME1B_MC_TRUTH));
TrackerTFile_Map_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(11),TFile_ME1O_MC_TRUTH));

TrackerTFile_Map_DATA.insert(std::make_pair(TrackerME_playlist_vector.at(0),TFile_ME1P_DATA));
TrackerTFile_Map_DATA.insert(std::make_pair(TrackerME_playlist_vector.at(1),TFile_ME1C_DATA));
TrackerTFile_Map_DATA.insert(std::make_pair(TrackerME_playlist_vector.at(2),TFile_ME1D_DATA));
TrackerTFile_Map_DATA.insert(std::make_pair(TrackerME_playlist_vector.at(3),TFile_ME1F_DATA));
TrackerTFile_Map_DATA.insert(std::make_pair(TrackerME_playlist_vector.at(4),TFile_ME1E_DATA));
TrackerTFile_Map_DATA.insert(std::make_pair(TrackerME_playlist_vector.at(5),TFile_ME1G_DATA));
TrackerTFile_Map_DATA.insert(std::make_pair(TrackerME_playlist_vector.at(6),TFile_ME1A_DATA));
TrackerTFile_Map_DATA.insert(std::make_pair(TrackerME_playlist_vector.at(7),TFile_ME1L_DATA));
TrackerTFile_Map_DATA.insert(std::make_pair(TrackerME_playlist_vector.at(8),TFile_ME1M_DATA));
TrackerTFile_Map_DATA.insert(std::make_pair(TrackerME_playlist_vector.at(9),TFile_ME1N_DATA));
TrackerTFile_Map_DATA.insert(std::make_pair(TrackerME_playlist_vector.at(10),TFile_ME1B_DATA));
TrackerTFile_Map_DATA.insert(std::make_pair(TrackerME_playlist_vector.at(11),TFile_ME1O_DATA));


/////////////////////////////////////////////////////
// Flux
/////////////////////////////////////////////////////

TrackerTFile_Map_MC_TRUTH_FLUX.insert(std::make_pair(TrackerME_playlist_vector.at(0), TFile_ME1P_MC_TRUTH_FLUX));
TrackerTFile_Map_MC_TRUTH_FLUX.insert(std::make_pair(TrackerME_playlist_vector.at(1), TFile_ME1C_MC_TRUTH_FLUX));
TrackerTFile_Map_MC_TRUTH_FLUX.insert(std::make_pair(TrackerME_playlist_vector.at(2), TFile_ME1D_MC_TRUTH_FLUX));
TrackerTFile_Map_MC_TRUTH_FLUX.insert(std::make_pair(TrackerME_playlist_vector.at(3), TFile_ME1F_MC_TRUTH_FLUX));
TrackerTFile_Map_MC_TRUTH_FLUX.insert(std::make_pair(TrackerME_playlist_vector.at(4), TFile_ME1E_MC_TRUTH_FLUX));
TrackerTFile_Map_MC_TRUTH_FLUX.insert(std::make_pair(TrackerME_playlist_vector.at(5), TFile_ME1G_MC_TRUTH_FLUX));
TrackerTFile_Map_MC_TRUTH_FLUX.insert(std::make_pair(TrackerME_playlist_vector.at(6), TFile_ME1A_MC_TRUTH_FLUX));
TrackerTFile_Map_MC_TRUTH_FLUX.insert(std::make_pair(TrackerME_playlist_vector.at(7), TFile_ME1L_MC_TRUTH_FLUX));
TrackerTFile_Map_MC_TRUTH_FLUX.insert(std::make_pair(TrackerME_playlist_vector.at(8), TFile_ME1M_MC_TRUTH_FLUX));
TrackerTFile_Map_MC_TRUTH_FLUX.insert(std::make_pair(TrackerME_playlist_vector.at(9), TFile_ME1N_MC_TRUTH_FLUX));
TrackerTFile_Map_MC_TRUTH_FLUX.insert(std::make_pair(TrackerME_playlist_vector.at(10),TFile_ME1B_MC_TRUTH_FLUX));
TrackerTFile_Map_MC_TRUTH_FLUX.insert(std::make_pair(TrackerME_playlist_vector.at(11),TFile_ME1O_MC_TRUTH_FLUX));





//////////////
///
/////////////


auto MuonVaribles = GetCrossSectionVaribles();
auto MuonVaribles2D = GetCrossSection2DVaribles();


CrossSection_histNames MuonE_names     = Constuct_crosssection_Histname(MuonVaribles[0]);
CrossSection_histNames MuonPZ_names    = Constuct_crosssection_Histname(MuonVaribles[1]);
CrossSection_histNames MuonPT_names    = Constuct_crosssection_Histname(MuonVaribles[2]);
CrossSection_histNames MuonTheta_names = Constuct_crosssection_Histname(MuonVaribles[3]);
CrossSection_2DhistNames MuonPT_PZ_histNames = Constuct_2Dcrosssection_Histname(MuonVaribles2D[0]);
CrossSection_histNames SecondTrackAngle_names;

SecondTrackAngle_names.Reco_hist_name = "h_secTrk_Theta";
SecondTrackAngle_names.Data_hist_name = "h_Data_secondTrkTheta";
SecondTrackAngle_names.hist_Eff_denominator_name = "h_secTrk_Theta_TRUE";
SecondTrackAngle_names.hist_Eff_numerator_name = "h_secTrk_Theta_TRUE_RECO";

//MuonVar MuonType;
//std::string Reco_hist_name;
//std::string Reco_hist_BG_name;
//std::string Migration_name;
//std::string Data_hist_name;
//std::string hist_Eff_denominator_name;
//std::string hist_Eff_numerator_name;
//std::string hist_Flux_name;

std::cout<<"found names"<< std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<""<<std::endl;
Print_crosssection_Histname(MuonE_names);
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
Print_crosssection_Histname(MuonPZ_names);
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
Print_crosssection_Histname(MuonPT_names);
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
Print_crosssection_Histname(MuonTheta_names);
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"             Constructing Hists Playlist Map"<< std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
int n_flux_universes =  100;
int nu_pdg = 14;
const bool use_nue_constraint = true;
bool useMuonCorrelations = true;
const std::string project_dir = "targets_12345_jointNueIMD";
double min_energy = 0;
double max_energy = 120;

auto& frw = PlotUtils::flux_reweighter("minervame1f", nu_pdg, use_nue_constraint, n_flux_universes);



std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~GET POT    ~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
Pot_MapList POT_MC_RECO_MAP  = Constuct_POT_playlistMap(MAP_RootPath_Tracker_MC_RECO, true);

Pot_MapList POT_DATA_MAP  = Constuct_POT_playlistMap(MAP_RootPath_Tracker_DATA, false);

///////////////////
//Pot_MapList MC_ScalingMap =  POT_ScalersMap(POT_MC_RECO_MAP , POT_DATA_MAP[kME1F] );
//Pot_MapList DATA_ScalingMap =  POT_ScalersMap(POT_DATA_MAP , POT_DATA_MAP[kME1F] );



std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~Combined  POT    ~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
const double Tracker_MC_POT = Combine_POTFromMap(POT_MC_RECO_MAP );

const double Tracker_Data_POT = Combine_POTFromMap(POT_DATA_MAP );

const double MC_to_Data = Tracker_Data_POT / Tracker_MC_POT;


std::cout<<" Tracker_MC_POT = "<< Tracker_MC_POT << std::endl;
std::cout<<" Tracker_Data_POT = "<< Tracker_Data_POT << std::endl;
std::cout<< "MC_to_Data = " <<  MC_to_Data << std::endl;

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<< "TRYING : MuonE " << std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
bool Make2DCrosssection = true;
//ME_playlist_CrossSection_MAP CrossSection_Hist_Playlist_Map_MuonE = Constuct_crosssection_Hists_PlaylistMap(MuonE_names, TrackerTFile_Map_MC_RECO, TrackerTFile_Map_MC_TRUTH, TrackerTFile_Map_DATA );

auto playlist69 = "/minerva/app/users/cnguyen/cmtuser/Minerva_v22r1p1Helium_GIT/opt/lib/data/flux_daisy/neutrinos/targets_12345_jointNueIMD/out_helium_000100.root";
TFile *TFile_test = new TFile(playlist69);
std::cout<< "error abands" << std::endl;
auto hist_test = Get1DHist(*TFile_test,"param_hist");

auto errornames = hist_test->GetErrorBandNames();
std::cout<<"errornames.size() = " << errornames.size()<< std::endl;
for(auto errorname:errornames){std::cout<<" Error name"<<errorname<<std::endl;}

char outFileName[1024];

if(Make2DCrosssection==false){
  sprintf(outFileName, "CrossSection_MasterAnaDev_DAISY.root");
}
else {sprintf(outFileName, "CrossSection_MasterAnaDev_2D_DAISY.root");}



auto outFile = TFile::Open(outFileName, "RECREATE");



if(Make2DCrosssection==false){

  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<< "TRYING : MuonpZ " << std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  ME_playlist_CrossSection_MAP_DAISY CrossSection_Map_Daisy_MuonPZ = Constuct_crosssection_Hists_PlaylistMap_DAISY(MuonPZ_names, TrackerTFile_Map_MC_RECO, TrackerTFile_Map_MC_TRUTH, TrackerTFile_Map_DATA);
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<< "TRYING : Muon pt " << std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  ME_playlist_CrossSection_MAP_DAISY CrossSection_Map_Daisy_MuonPT = Constuct_crosssection_Hists_PlaylistMap_DAISY(MuonPT_names, TrackerTFile_Map_MC_RECO, TrackerTFile_Map_MC_TRUTH, TrackerTFile_Map_DATA);
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<< "TRYING : Muon theta " << std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  ME_playlist_CrossSection_MAP_DAISY CrossSection_Map_Daisy_MuonTheta = Constuct_crosssection_Hists_PlaylistMap_DAISY(MuonTheta_names, TrackerTFile_Map_MC_RECO, TrackerTFile_Map_MC_TRUTH, TrackerTFile_Map_DATA);
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<< "TRYING : Muon E " << std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  ME_playlist_CrossSection_MAP_DAISY CrossSection_Map_Daisy_MuonE = Constuct_crosssection_Hists_PlaylistMap_DAISY(MuonE_names, TrackerTFile_Map_MC_RECO, TrackerTFile_Map_MC_TRUTH, TrackerTFile_Map_DATA);
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<< "TRYING : Combined " << std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

  CrossSection_Hist_Daisy CombinedHist_MuonE_Daisy = Combine_crosssection_Hists_PlaylistMap_Daisy(CrossSection_Map_Daisy_MuonE,TrackerME_playlist_vector.at(3) );
  CrossSection_Hist_Daisy CombinedHist_MuonPZ_Daisy = Combine_crosssection_Hists_PlaylistMap_Daisy(CrossSection_Map_Daisy_MuonPZ,TrackerME_playlist_vector.at(3) );
  CrossSection_Hist_Daisy CombinedHist_MuonPT_Daisy = Combine_crosssection_Hists_PlaylistMap_Daisy(CrossSection_Map_Daisy_MuonPT,TrackerME_playlist_vector.at(3) );
  CrossSection_Hist_Daisy CombinedHist_MuonTheta_Daisy = Combine_crosssection_Hists_PlaylistMap_Daisy(CrossSection_Map_Daisy_MuonTheta,TrackerME_playlist_vector.at(3) );


  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~Normalize  1D Hist ~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

  POT_Normalize_CrossSection_Hist_Daisy(CombinedHist_MuonPT_Daisy, MC_to_Data);
  WritetoTFile_Daisy(CombinedHist_MuonPT_Daisy, *outFile, "h_MuonPT");


  POT_Normalize_CrossSection_Hist_Daisy(CombinedHist_MuonPZ_Daisy, MC_to_Data);
  WritetoTFile_Daisy(CombinedHist_MuonPZ_Daisy, *outFile, "h_MuonPZ");


  POT_Normalize_CrossSection_Hist_Daisy(CombinedHist_MuonE_Daisy, MC_to_Data);
  WritetoTFile_Daisy(CombinedHist_MuonE_Daisy, *outFile, "h_MuonE");


  POT_Normalize_CrossSection_Hist_Daisy(CombinedHist_MuonTheta_Daisy, MC_to_Data);
  WritetoTFile_Daisy(CombinedHist_MuonTheta_Daisy, *outFile, "h_MuonTheta");

  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~ BG Subtraction ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  ////////////////////////////////////////////////////////////////////////////////
  // 1D
  ////////////////////////////////////////////////////////////////////////////////

  /// Add Error band to Data
  AddMissingErrorBandsAndFillWithCV_toData_ForDaisy(CombinedHist_MuonPT_Daisy);
  AddMissingErrorBandsAndFillWithCV_toData_ForDaisy(CombinedHist_MuonPZ_Daisy);

  AddMissingErrorBandsAndFillWithCV_toData_ForDaisy(CombinedHist_MuonE_Daisy);
  AddMissingErrorBandsAndFillWithCV_toData_ForDaisy(CombinedHist_MuonTheta_Daisy);

  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

  // Apply Subtract to Data
  ApplyBGSubtraction_todata_CrossSection_Daisy(CombinedHist_MuonPT_Daisy);
  //WritetoTFile_Daisy_Data(CombinedHist_MuonPT_Daisy, *outFile, "h_MuonPT", "BGSubtracted");
  ApplyBGSubtraction_toRECO_CrossSection_Daisy(CombinedHist_MuonPT_Daisy);
  WritetoTFile_Daisy_Data_RECO(CombinedHist_MuonPT_Daisy, *outFile, "h_MuonPT", "BGSubtracted");

  ApplyBGSubtraction_todata_CrossSection_Daisy(CombinedHist_MuonPZ_Daisy);
  //WritetoTFile_Daisy_Data(CombinedHist_MuonPZ_Daisy, *outFile, "h_MuonPZ", "BGSubtracted");
  ApplyBGSubtraction_toRECO_CrossSection_Daisy(CombinedHist_MuonPZ_Daisy);
  WritetoTFile_Daisy_Data_RECO(CombinedHist_MuonPZ_Daisy, *outFile, "h_MuonPZ", "BGSubtracted");

  ApplyBGSubtraction_todata_CrossSection_Daisy(CombinedHist_MuonE_Daisy);
  //WritetoTFile_Daisy_Data(CombinedHist_MuonE_Daisy, *outFile, "h_MuonE", "BGSubtracted");
  ApplyBGSubtraction_toRECO_CrossSection_Daisy(CombinedHist_MuonE_Daisy);
  WritetoTFile_Daisy_Data_RECO(CombinedHist_MuonE_Daisy, *outFile, "h_MuonE", "BGSubtracted");

  ApplyBGSubtraction_todata_CrossSection_Daisy(CombinedHist_MuonTheta_Daisy);
  //WritetoTFile_Daisy_Data(CombinedHist_MuonTheta_Daisy, *outFile, "h_MuonTheta", "BGSubtracted");
  ApplyBGSubtraction_toRECO_CrossSection_Daisy(CombinedHist_MuonTheta_Daisy);
  WritetoTFile_Daisy_Data_RECO(CombinedHist_MuonTheta_Daisy, *outFile, "h_MuonTheta", "BGSubtracted");




  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~ UnFolding ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

  UnfoldHist_Daisy( CombinedHist_MuonPT_Daisy, 3);
  WritetoTFile_Daisy_UnfoldedData(CombinedHist_MuonPT_Daisy, *outFile, "h_MuonPT", "BGSubtracted_Unfolded");

  UnfoldHist_Daisy( CombinedHist_MuonPZ_Daisy, 3);
  WritetoTFile_Daisy_UnfoldedData(CombinedHist_MuonPZ_Daisy, *outFile, "h_MuonPZ", "BGSubtracted_Unfolded");

  UnfoldHist_Daisy( CombinedHist_MuonE_Daisy, 3);
  WritetoTFile_Daisy_UnfoldedData(CombinedHist_MuonE_Daisy, *outFile, "h_MuonE", "BGSubtracted_Unfolded");

  UnfoldHist_Daisy( CombinedHist_MuonTheta_Daisy, 3);
  WritetoTFile_Daisy_UnfoldedData(CombinedHist_MuonTheta_Daisy, *outFile, "h_MuonTheta", "BGSubtracted_Unfolded");

  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~ efficiency Correct ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

  MakeNumeratorEff_Daisy(CombinedHist_MuonPT_Daisy);
  MakeNumeratorEff_Daisy(CombinedHist_MuonPZ_Daisy);
  WritetoTFile_Daisy_Efficiency(CombinedHist_MuonPT_Daisy, *outFile, "h_MuonPT");
  WritetoTFile_Daisy_Efficiency(CombinedHist_MuonPZ_Daisy, *outFile, "h_MuonPZ");

  MakeNumeratorEff_Daisy(CombinedHist_MuonE_Daisy);
  MakeNumeratorEff_Daisy(CombinedHist_MuonTheta_Daisy);
  WritetoTFile_Daisy_Efficiency(CombinedHist_MuonE_Daisy, *outFile, "h_MuonE");
  WritetoTFile_Daisy_Efficiency(CombinedHist_MuonTheta_Daisy, *outFile, "h_MuonTheta");

  std::map<int, MnvH1D*> UnfoldedData_map_PT =  GetDaisyUnfoldedData(CombinedHist_MuonPT_Daisy);
  std::map<int, MnvH1D*> Eff_map_PT =  GetDaisyEff(CombinedHist_MuonPT_Daisy);

  std::map<int, MnvH1D*> UnfoldedData_map_PZ =  GetDaisyUnfoldedData(CombinedHist_MuonPZ_Daisy);
  std::map<int, MnvH1D*> Eff_map_PZ =  GetDaisyEff(CombinedHist_MuonPZ_Daisy);

  std::map<int, MnvH1D*> UnfoldedData_map_E =  GetDaisyUnfoldedData(CombinedHist_MuonE_Daisy);
  std::map<int, MnvH1D*> Eff_map_E =  GetDaisyEff(CombinedHist_MuonE_Daisy);

  std::map<int, MnvH1D*> UnfoldedData_map_Theta =  GetDaisyUnfoldedData(CombinedHist_MuonTheta_Daisy);
  std::map<int, MnvH1D*> Eff_map_Theta =  GetDaisyEff(CombinedHist_MuonTheta_Daisy);
  outFile->cd();

  char Print_Name[1024];
  for(int petal = 0; petal < 12; petal++ ){
    UnfoldedData_map_PT[petal]->Divide(UnfoldedData_map_PT[petal],Eff_map_PT[petal]);
    sprintf(Print_Name, "h_MuonPT_Data_EffiencyCorrect_Daisy_%i", petal);
    UnfoldedData_map_PT[petal] ->Clone()->Write(Print_Name);

    UnfoldedData_map_PZ[petal]->Divide(UnfoldedData_map_PZ[petal],Eff_map_PZ[petal]);
    sprintf(Print_Name, "h_MuonPZ_Data_EffiencyCorrect_Daisy_%i", petal);
    UnfoldedData_map_PZ[petal] ->Clone()->Write(Print_Name);

    UnfoldedData_map_E[petal]->Divide(UnfoldedData_map_E[petal],Eff_map_E[petal]);
    sprintf(Print_Name, "h_MuonE_Data_EffiencyCorrect_Daisy_%i", petal);
    UnfoldedData_map_E[petal] ->Clone()->Write(Print_Name);

    UnfoldedData_map_Theta[petal]->Divide(UnfoldedData_map_Theta[petal],Eff_map_Theta[petal]);
    sprintf(Print_Name, "h_MuonTheta_Data_EffiencyCorrect_Daisy_%i", petal);
    UnfoldedData_map_Theta[petal] ->Clone()->Write(Print_Name);

  }



  auto h_MuonPT_eff_corr_tracker_to_helium = frw.GetReweightedDaisySum(nu_pdg, "helium", UnfoldedData_map_PT, project_dir );
  auto h_MuonPZ_eff_corr_tracker_to_helium = frw.GetReweightedDaisySum(nu_pdg, "helium", UnfoldedData_map_PZ, project_dir );
  auto h_MuonE_eff_corr_tracker_to_helium = frw.GetReweightedDaisySum(nu_pdg, "helium", UnfoldedData_map_E, project_dir );
  auto h_MuonTheta_eff_corr_tracker_to_helium = frw.GetReweightedDaisySum(nu_pdg, "helium", UnfoldedData_map_Theta, project_dir );

  outFile->cd();
  h_MuonPT_eff_corr_tracker_to_helium ->Clone()->Write("h_MuonPT_eff_corr_tracker_to_helium_combined");
  h_MuonPZ_eff_corr_tracker_to_helium ->Clone()->Write("h_MuonPZ_eff_corr_tracker_to_helium_combined");
  h_MuonE_eff_corr_tracker_to_helium ->Clone()->Write("h_MuonE_eff_corr_tracker_to_helium_combined");
  h_MuonTheta_eff_corr_tracker_to_helium ->Clone()->Write("h_MuonTheta_eff_corr_tracker_to_helium_combined");



  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~ finished  GetReweightedDaisySum ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

  auto fluxIntegral_muonPT = frw.GetIntegratedTargetFlux(nu_pdg, "helium", h_MuonPT_eff_corr_tracker_to_helium, min_energy, max_energy, project_dir);
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  auto fluxIntegral_muonPZ = frw.GetIntegratedTargetFlux(nu_pdg, "helium", h_MuonPZ_eff_corr_tracker_to_helium, min_energy, max_energy, project_dir);
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  auto fluxIntegral_muonE = frw.GetIntegratedTargetFlux(nu_pdg, "helium", h_MuonE_eff_corr_tracker_to_helium, min_energy, max_energy, project_dir);
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  auto fluxIntegral_muonTheta = frw.GetIntegratedTargetFlux(nu_pdg, "helium", h_MuonTheta_eff_corr_tracker_to_helium, min_energy, max_energy, project_dir);



  auto h_crossSection_MuonPT = normalize(h_MuonPT_eff_corr_tracker_to_helium, /*CombinedHist_MuonE.h_flux*/fluxIntegral_muonPT, nNucleons_Data, Tracker_Data_POT);
  auto h_crossSection_MuonPZ = normalize(h_MuonPZ_eff_corr_tracker_to_helium, /*CombinedHist_MuonE.h_flux*/fluxIntegral_muonPZ, nNucleons_Data, Tracker_Data_POT);
  auto h_crossSection_MuonTheta = normalize(h_MuonTheta_eff_corr_tracker_to_helium, /*CombinedHist_MuonE.h_flux*/fluxIntegral_muonTheta, nNucleons_Data, Tracker_Data_POT);
  auto h_crossSection_MuonE = normalize(h_MuonE_eff_corr_tracker_to_helium, /*CombinedHist_MuonE.h_flux*/fluxIntegral_muonE, nNucleons_Data, Tracker_Data_POT);

  outFile->cd();
  h_crossSection_MuonPZ->Clone()->Write("h_MuonPZ_Tracker_CrossSection_Petal_correction");
  h_crossSection_MuonE->Clone()->Write("h_MuonE_Tracker_CrossSection_Petal_correction");
  h_crossSection_MuonTheta->Clone()->Write("h_MuonTheta_Tracker_CrossSection_Petal_correction");
  h_crossSection_MuonPT->Clone()->Write("h_MuonPT_Tracker_CrossSection_Petal_correction");





}// End of if
////////////////////////////////////////////////////////////////////////////////
//End of If
////////////////////////////////////////////////////////////////////////////////
else{

  ////////////////////////////////////////////////////////////////////////////////
  // 2D
  ////////////////////////////////////////////////////////////////////////////////
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<< "TRYING : 2D Pt vs PZ " << std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  ME_playlist_2D_CrossSection_MAP_DAISY FullCrossSection_Hist_Playlist_Map_MuonPT_PZ = Constuct_crosssection_2DHists_PlaylistMap_DAISY(MuonPT_PZ_histNames, TrackerTFile_Map_MC_RECO, TrackerTFile_Map_MC_TRUTH, TrackerTFile_Map_DATA );
  CrossSection2D_Hist_Daisy CombinedHist_MuonPT_PZ_Daisy = Combine_crosssection_Hists_PlaylistMap_Daisy(FullCrossSection_Hist_Playlist_Map_MuonPT_PZ, TrackerME_playlist_vector.at(3) );
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~Normalize 2D Hist ~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  POT_Normalize_CrossSection2D_Hist_Daisy(CombinedHist_MuonPT_PZ_Daisy, MC_to_Data);
  WritetoTFile_2DDaisy(CombinedHist_MuonPT_PZ_Daisy, *outFile, "h_MuonPT_PZ");
  AddMissingErrorBandsAndFillWithCV_toData_ForDaisy(CombinedHist_MuonPT_PZ_Daisy);

  ApplyBGSubtraction_todata_CrossSection_Daisy(CombinedHist_MuonPT_PZ_Daisy);
  //WritetoTFile_2DDaisy_Data(CombinedHist_MuonPT_PZ_Daisy, *outFile, "h_MuonPT_PZ", "BGSubtracted");

  ApplyBGSubtraction_toRECO_CrossSection_Daisy(CombinedHist_MuonPT_PZ_Daisy);
  WritetoTFile_2DDaisy_Data_RECO(CombinedHist_MuonPT_PZ_Daisy, *outFile, "h_MuonPT_PZ", "BGSubtracted");

  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~ UnFolding ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

  UnfoldHist_Daisy2D(CombinedHist_MuonPT_PZ_Daisy, 3);
  WritetoTFile_2DDaisy_UnfoldedData(CombinedHist_MuonPT_PZ_Daisy, *outFile, "h_MuonPT_PZ", "BGSubtracted_Unfolded");


  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~ efficiency Correct ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  MakeNumeratorEff_Daisy( CombinedHist_MuonPT_PZ_Daisy );
  WritetoTFile_2D_Daisy_Efficiency(CombinedHist_MuonPT_PZ_Daisy, *outFile, "h_MuonPT_PZ");


  std::map<int, MnvH2D*> UnfoldedData_map_MuonPT_PZ =  GetDaisyUnfoldedData(CombinedHist_MuonPT_PZ_Daisy);
  std::map<int, MnvH2D*> Eff_map_MuonPT_PZ = GetDaisyEff(CombinedHist_MuonPT_PZ_Daisy);

  outFile->cd();

  char Print_Name[1024];
  for(int petal = 0; petal < 12; petal++ ){

    UnfoldedData_map_MuonPT_PZ[petal]->Divide(UnfoldedData_map_MuonPT_PZ[petal],Eff_map_MuonPT_PZ[petal]);
    sprintf(Print_Name, "h_MuonPT_PZ_Data_EffiencyCorrect_Daisy_%i", petal);
    UnfoldedData_map_MuonPT_PZ[petal] ->Clone()->Write(Print_Name);

  }


  auto h_MuonPT_PZ_eff_corr_tracker_to_helium = frw.GetReweightedDaisySum(nu_pdg, "helium", UnfoldedData_map_MuonPT_PZ, project_dir );
  outFile->cd();
  h_MuonPT_PZ_eff_corr_tracker_to_helium ->Clone()->Write("h_MuonPT_PZ_eff_corr_tracker_to_helium_combined");

  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~ finished  GetReweightedDaisySum ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  auto fluxIntegral_muonPTPZ = frw.GetIntegratedTargetFlux(nu_pdg, "helium", h_MuonPT_PZ_eff_corr_tracker_to_helium, min_energy, max_energy, project_dir);

  auto h_crossSection_MuonPT_PZ = normalize2D(h_MuonPT_PZ_eff_corr_tracker_to_helium, /*CombinedHist_MuonE.h_flux*/fluxIntegral_muonPTPZ, nNucleons_Data, Tracker_Data_POT);
  outFile->cd();
  h_crossSection_MuonPT_PZ->Clone()->Write("h_MuonPT_PZ_Tracker_CrossSection_Petal_correction");

}// End of Else
////////////////////////////////////////////////////////////////////////////////
// ENd of else
////////////////////////////////////////////////////////////////////////////////

// ---------------------------------------------------------------------
// Flux reweighter information, get reweighted daisy sum according to a material
// ---------------------------------------------------------------------



auto  Vector_daisy_wgts = frw.GetReweightedDaisyWgts(nu_pdg, "helium", project_dir );
int number=0;

std::cout<<"looking at weights"<<std::endl;
for(auto wgt:Vector_daisy_wgts){
std::cout<< number<< " wgt "<< wgt<<std::endl;
  number ++;
}

//Vector_daisy_wgts.push_back(1.0);
//Vector_daisy_wgts.push_back(1.0);



std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~ Cross Section ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
//fluxIntegral->AddMissingErrorBandsAndFillWithCV( *CombinedHist_MuonPT_PZ.h_effNum );
//inputCross_Hist.h_effDom->AddMissingErrorBandsAndFillWithCV(*inputCross_Hist.h_effNum);




////////////////
/////Flux
/////////////////

if(Make2DCrosssection==false){
Playlist_MnvH1D_Map NuE_true_Map =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TrackerTFile_Map_MC_TRUTH_FLUX, "h_Enu_TRUE" );
Playlist_MnvH1D_Map NuE_true_Map_tracker_Anezkak =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TrackerTFile_Map_MC_TRACKER_Anezkak, "selected_mc_truth_trackerC_Enu" );
Playlist_MnvH2D_Map NuE_true_Enu_slice_Map =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(TrackerTFile_Map_MC_TRUTH_FLUX, "h_Enu_Slice_TRUE" );
Playlist_MnvH2D_Map NuE_true_Enu_daisy_Map =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(TrackerTFile_Map_MC_TRUTH_FLUX, "h2_Enu_DAISY_TRUE" );

Playlist_MnvH1D_Map NuE_true_Map_Slice1 =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TrackerTFile_Map_MC_TRUTH_FLUX, "h_Enu_TRUE_Slice1" );
Playlist_MnvH1D_Map NuE_true_Map_Slice2 =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TrackerTFile_Map_MC_TRUTH_FLUX, "h_Enu_TRUE_Slice2" );
Playlist_MnvH1D_Map NuE_true_Map_Slice3 =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TrackerTFile_Map_MC_TRUTH_FLUX, "h_Enu_TRUE_Slice3" );
Playlist_MnvH1D_Map NuE_true_Map_Slice4 =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TrackerTFile_Map_MC_TRUTH_FLUX, "h_Enu_TRUE_Slice4" );


Playlist_MnvH1D_Map h_Enu_TRUE_Daisy0_map = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TrackerTFile_Map_MC_TRUTH_FLUX, "h_Enu_TRUE_Daisy0" );
Playlist_MnvH1D_Map h_Enu_TRUE_Daisy1_map = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TrackerTFile_Map_MC_TRUTH_FLUX, "h_Enu_TRUE_Daisy1" );
Playlist_MnvH1D_Map h_Enu_TRUE_Daisy2_map = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TrackerTFile_Map_MC_TRUTH_FLUX, "h_Enu_TRUE_Daisy2" );
Playlist_MnvH1D_Map h_Enu_TRUE_Daisy3_map = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TrackerTFile_Map_MC_TRUTH_FLUX, "h_Enu_TRUE_Daisy3" );
Playlist_MnvH1D_Map h_Enu_TRUE_Daisy4_map = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TrackerTFile_Map_MC_TRUTH_FLUX, "h_Enu_TRUE_Daisy4" );
Playlist_MnvH1D_Map h_Enu_TRUE_Daisy5_map = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TrackerTFile_Map_MC_TRUTH_FLUX, "h_Enu_TRUE_Daisy5" );
Playlist_MnvH1D_Map h_Enu_TRUE_Daisy6_map = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TrackerTFile_Map_MC_TRUTH_FLUX, "h_Enu_TRUE_Daisy6" );
Playlist_MnvH1D_Map h_Enu_TRUE_Daisy7_map = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TrackerTFile_Map_MC_TRUTH_FLUX, "h_Enu_TRUE_Daisy7" );
Playlist_MnvH1D_Map h_Enu_TRUE_Daisy8_map = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TrackerTFile_Map_MC_TRUTH_FLUX, "h_Enu_TRUE_Daisy8" );
Playlist_MnvH1D_Map h_Enu_TRUE_Daisy9_map = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TrackerTFile_Map_MC_TRUTH_FLUX, "h_Enu_TRUE_Daisy9" );
Playlist_MnvH1D_Map h_Enu_TRUE_Daisy10_map = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TrackerTFile_Map_MC_TRUTH_FLUX, "h_Enu_TRUE_Daisy10" );
Playlist_MnvH1D_Map h_Enu_TRUE_Daisy11_map = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TrackerTFile_Map_MC_TRUTH_FLUX, "h_Enu_TRUE_Daisy11" );



PlotUtils::MnvH1D *h_Enu_TRUE = Combine_Hists_fromMAP(NuE_true_Map , TrackerME_playlist_vector.at(3) ,"h_Enu_TRUE");
PlotUtils::MnvH1D *h_Enu_TRUE_Anezkak = Combine_Hists_fromMAP(NuE_true_Map_tracker_Anezkak , TrackerME_playlist_vector.at(3) ,"h_Enu_TRUE_Anezkak");
PlotUtils::MnvH1D *h_Enu_TRUE_Slice1 = Combine_Hists_fromMAP(NuE_true_Map_Slice1 , TrackerME_playlist_vector.at(3) ,"h_Enu_TRUE_Slice1");
PlotUtils::MnvH1D *h_Enu_TRUE_Slice2 = Combine_Hists_fromMAP(NuE_true_Map_Slice2 , TrackerME_playlist_vector.at(3) ,"h_Enu_TRUE_Slice2");
PlotUtils::MnvH1D *h_Enu_TRUE_Slice3 = Combine_Hists_fromMAP(NuE_true_Map_Slice3 , TrackerME_playlist_vector.at(3) ,"h_Enu_TRUE_Slice3");
PlotUtils::MnvH1D *h_Enu_TRUE_Slice4 = Combine_Hists_fromMAP(NuE_true_Map_Slice4 , TrackerME_playlist_vector.at(3) ,"h_Enu_TRUE_Slice4");



PlotUtils::MnvH1D *h_Enu_TRUE_Daisy0 = Combine_Hists_fromMAP(h_Enu_TRUE_Daisy0_map , TrackerME_playlist_vector.at(3) ,"h_Enu_TRUE_Daisy0");
PlotUtils::MnvH1D *h_Enu_TRUE_Daisy1 = Combine_Hists_fromMAP(h_Enu_TRUE_Daisy1_map , TrackerME_playlist_vector.at(3) ,"h_Enu_TRUE_Daisy1");
PlotUtils::MnvH1D *h_Enu_TRUE_Daisy2 = Combine_Hists_fromMAP(h_Enu_TRUE_Daisy2_map , TrackerME_playlist_vector.at(3) ,"h_Enu_TRUE_Daisy2");
PlotUtils::MnvH1D *h_Enu_TRUE_Daisy3 = Combine_Hists_fromMAP(h_Enu_TRUE_Daisy3_map , TrackerME_playlist_vector.at(3) ,"h_Enu_TRUE_Daisy3");
PlotUtils::MnvH1D *h_Enu_TRUE_Daisy4 = Combine_Hists_fromMAP(h_Enu_TRUE_Daisy4_map , TrackerME_playlist_vector.at(3) ,"h_Enu_TRUE_Daisy4");
PlotUtils::MnvH1D *h_Enu_TRUE_Daisy5 = Combine_Hists_fromMAP(h_Enu_TRUE_Daisy5_map , TrackerME_playlist_vector.at(3) ,"h_Enu_TRUE_Daisy5");
PlotUtils::MnvH1D *h_Enu_TRUE_Daisy6 = Combine_Hists_fromMAP(h_Enu_TRUE_Daisy6_map , TrackerME_playlist_vector.at(3) ,"h_Enu_TRUE_Daisy6");
PlotUtils::MnvH1D *h_Enu_TRUE_Daisy7 = Combine_Hists_fromMAP(h_Enu_TRUE_Daisy7_map , TrackerME_playlist_vector.at(3) ,"h_Enu_TRUE_Daisy7");
PlotUtils::MnvH1D *h_Enu_TRUE_Daisy8 = Combine_Hists_fromMAP(h_Enu_TRUE_Daisy8_map , TrackerME_playlist_vector.at(3) ,"h_Enu_TRUE_Daisy8");
PlotUtils::MnvH1D *h_Enu_TRUE_Daisy9 = Combine_Hists_fromMAP(h_Enu_TRUE_Daisy9_map , TrackerME_playlist_vector.at(3) ,"h_Enu_TRUE_Daisy9");
PlotUtils::MnvH1D *h_Enu_TRUE_Daisy10 =Combine_Hists_fromMAP(h_Enu_TRUE_Daisy10_map , TrackerME_playlist_vector.at(3) ,"h_Enu_TRUE_Daisy10");
PlotUtils::MnvH1D *h_Enu_TRUE_Daisy11 =Combine_Hists_fromMAP(h_Enu_TRUE_Daisy11_map , TrackerME_playlist_vector.at(3) ,"h_Enu_TRUE_Daisy11");


PlotUtils::MnvH1D *h_Enu_TRUE_Daisy0_clone_rewgt =    (MnvH1D*)h_Enu_TRUE_Daisy0->Clone("h_Enu_TRUE_Daisy0_clone");
PlotUtils::MnvH1D *h_Enu_TRUE_Daisy1_clone_rewgt =    (MnvH1D*)h_Enu_TRUE_Daisy1->Clone("h_Enu_TRUE_Daisy1_clone");
PlotUtils::MnvH1D *h_Enu_TRUE_Daisy2_clone_rewgt =    (MnvH1D*)h_Enu_TRUE_Daisy2->Clone("h_Enu_TRUE_Daisy2_clone");
PlotUtils::MnvH1D *h_Enu_TRUE_Daisy3_clone_rewgt =    (MnvH1D*)h_Enu_TRUE_Daisy3->Clone("h_Enu_TRUE_Daisy3_clone");
PlotUtils::MnvH1D *h_Enu_TRUE_Daisy4_clone_rewgt =    (MnvH1D*)h_Enu_TRUE_Daisy4->Clone("h_Enu_TRUE_Daisy4_clone");
PlotUtils::MnvH1D *h_Enu_TRUE_Daisy5_clone_rewgt =    (MnvH1D*)h_Enu_TRUE_Daisy5->Clone("h_Enu_TRUE_Daisy5_clone");
PlotUtils::MnvH1D *h_Enu_TRUE_Daisy6_clone_rewgt =    (MnvH1D*)h_Enu_TRUE_Daisy6->Clone("h_Enu_TRUE_Daisy6_clone");
PlotUtils::MnvH1D *h_Enu_TRUE_Daisy7_clone_rewgt =    (MnvH1D*)h_Enu_TRUE_Daisy7->Clone("h_Enu_TRUE_Daisy7_clone");
PlotUtils::MnvH1D *h_Enu_TRUE_Daisy8_clone_rewgt =    (MnvH1D*)h_Enu_TRUE_Daisy8->Clone("h_Enu_TRUE_Daisy8_clone");
PlotUtils::MnvH1D *h_Enu_TRUE_Daisy9_clone_rewgt =    (MnvH1D*)h_Enu_TRUE_Daisy9->Clone("h_Enu_TRUE_Daisy9_clone");
PlotUtils::MnvH1D *h_Enu_TRUE_Daisy10_clone_rewgt =     (MnvH1D*)h_Enu_TRUE_Daisy10->Clone("h_Enu_TRUE_Daisy10_clone");
PlotUtils::MnvH1D *h_Enu_TRUE_Daisy11_clone_rewgt =     (MnvH1D*)h_Enu_TRUE_Daisy11->Clone("h_Enu_TRUE_Daisy11_clone");


h_Enu_TRUE_Daisy0_clone_rewgt->Scale(Vector_daisy_wgts.at(0));
h_Enu_TRUE_Daisy1_clone_rewgt->Scale(Vector_daisy_wgts.at(1));
h_Enu_TRUE_Daisy2_clone_rewgt->Scale(Vector_daisy_wgts.at(2));
h_Enu_TRUE_Daisy3_clone_rewgt->Scale(Vector_daisy_wgts.at(3));
h_Enu_TRUE_Daisy4_clone_rewgt->Scale(Vector_daisy_wgts.at(4));
h_Enu_TRUE_Daisy5_clone_rewgt->Scale(Vector_daisy_wgts.at(5));
h_Enu_TRUE_Daisy6_clone_rewgt->Scale(Vector_daisy_wgts.at(6));
h_Enu_TRUE_Daisy7_clone_rewgt->Scale(Vector_daisy_wgts.at(7));
h_Enu_TRUE_Daisy8_clone_rewgt->Scale(Vector_daisy_wgts.at(8));
h_Enu_TRUE_Daisy9_clone_rewgt->Scale(Vector_daisy_wgts.at(9));
h_Enu_TRUE_Daisy10_clone_rewgt->Scale(Vector_daisy_wgts.at(10));
h_Enu_TRUE_Daisy11_clone_rewgt->Scale(Vector_daisy_wgts.at(11));



std::map<int, MnvH1D*> TrackerFluxReweight;

TrackerFluxReweight.insert({0,h_Enu_TRUE_Daisy0});
TrackerFluxReweight.insert({1,h_Enu_TRUE_Daisy1});
TrackerFluxReweight.insert({2,h_Enu_TRUE_Daisy2});
TrackerFluxReweight.insert({3,h_Enu_TRUE_Daisy3});
TrackerFluxReweight.insert({4,h_Enu_TRUE_Daisy4});
TrackerFluxReweight.insert({5,h_Enu_TRUE_Daisy5});
TrackerFluxReweight.insert({6,h_Enu_TRUE_Daisy6});
TrackerFluxReweight.insert({7,h_Enu_TRUE_Daisy7});
TrackerFluxReweight.insert({8,h_Enu_TRUE_Daisy8});
TrackerFluxReweight.insert({9,h_Enu_TRUE_Daisy9});
TrackerFluxReweight.insert({10,h_Enu_TRUE_Daisy10});
TrackerFluxReweight.insert({11,h_Enu_TRUE_Daisy11});



double NumberTracker_atoms = TargetTool.GetTrackerNCarbonAtoms(5890.0, 8467.0, true);
double NumberTracker_atoms_Daisy = NumberTracker_atoms / 12;
auto Enu_reweighted = frw.GetReweightedDaisySum(nu_pdg, "helium", TrackerFluxReweight, project_dir );

auto Enu_reweighted_Flux = MakeFluxHist(Enu_reweighted, "tracker", NumberTracker_atoms, 4.97204e+21);
auto h_Enu_TRUE_Flux = MakeFluxHist(h_Enu_TRUE, "tracker", NumberTracker_atoms, 4.97204e+21);

auto h_Enu_TRUE_Daisy0_clone_rewgt_flux = MakeFluxHist(h_Enu_TRUE_Daisy0_clone_rewgt,"tracker", NumberTracker_atoms_Daisy, 4.97204e+21);
auto h_Enu_TRUE_Daisy1_clone_rewgt_flux = MakeFluxHist(h_Enu_TRUE_Daisy1_clone_rewgt,"tracker", NumberTracker_atoms_Daisy, 4.97204e+21);
auto h_Enu_TRUE_Daisy2_clone_rewgt_flux = MakeFluxHist(h_Enu_TRUE_Daisy2_clone_rewgt,"tracker", NumberTracker_atoms_Daisy, 4.97204e+21);
auto h_Enu_TRUE_Daisy3_clone_rewgt_flux = MakeFluxHist(h_Enu_TRUE_Daisy3_clone_rewgt,"tracker", NumberTracker_atoms_Daisy, 4.97204e+21);
auto h_Enu_TRUE_Daisy4_clone_rewgt_flux = MakeFluxHist(h_Enu_TRUE_Daisy4_clone_rewgt,"tracker", NumberTracker_atoms_Daisy, 4.97204e+21);
auto h_Enu_TRUE_Daisy5_clone_rewgt_flux = MakeFluxHist(h_Enu_TRUE_Daisy5_clone_rewgt,"tracker", NumberTracker_atoms_Daisy, 4.97204e+21);
auto h_Enu_TRUE_Daisy6_clone_rewgt_flux = MakeFluxHist(h_Enu_TRUE_Daisy6_clone_rewgt,"tracker", NumberTracker_atoms_Daisy, 4.97204e+21);
auto h_Enu_TRUE_Daisy7_clone_rewgt_flux = MakeFluxHist(h_Enu_TRUE_Daisy7_clone_rewgt,"tracker", NumberTracker_atoms_Daisy, 4.97204e+21);
auto h_Enu_TRUE_Daisy8_clone_rewgt_flux = MakeFluxHist(h_Enu_TRUE_Daisy8_clone_rewgt,"tracker", NumberTracker_atoms_Daisy, 4.97204e+21);
auto h_Enu_TRUE_Daisy9_clone_rewgt_flux = MakeFluxHist(h_Enu_TRUE_Daisy9_clone_rewgt,"tracker", NumberTracker_atoms_Daisy, 4.97204e+21);
auto h_Enu_TRUE_Daisy10_clone_rewgt_flux = MakeFluxHist(h_Enu_TRUE_Daisy10_clone_rewgt,"tracker", NumberTracker_atoms_Daisy, 4.97204e+21);
auto h_Enu_TRUE_Daisy11_clone_rewgt_flux = MakeFluxHist(h_Enu_TRUE_Daisy11_clone_rewgt,"tracker", NumberTracker_atoms_Daisy, 4.97204e+21);

outFile->cd();
Enu_reweighted_Flux->Clone()->Write("Tracker_Flux_reweighted");
h_Enu_TRUE_Flux->Clone()->Write("Tracker_Flux");
h_Enu_TRUE_Flux->Divide(h_Enu_TRUE_Flux,Enu_reweighted_Flux);
h_Enu_TRUE_Flux->Clone()->Write("Tracker_Flux_Ratio");


h_Enu_TRUE_Daisy0_clone_rewgt_flux->Clone()->Write("Tracker_Flux_reweighted_Daisy_0");
h_Enu_TRUE_Daisy1_clone_rewgt_flux->Clone()->Write("Tracker_Flux_reweighted_Daisy_1");
h_Enu_TRUE_Daisy2_clone_rewgt_flux->Clone()->Write("Tracker_Flux_reweighted_Daisy_2");
h_Enu_TRUE_Daisy3_clone_rewgt_flux->Clone()->Write("Tracker_Flux_reweighted_Daisy_3");
h_Enu_TRUE_Daisy4_clone_rewgt_flux->Clone()->Write("Tracker_Flux_reweighted_Daisy_4");
h_Enu_TRUE_Daisy5_clone_rewgt_flux->Clone()->Write("Tracker_Flux_reweighted_Daisy_5");
h_Enu_TRUE_Daisy6_clone_rewgt_flux->Clone()->Write("Tracker_Flux_reweighted_Daisy_6");
h_Enu_TRUE_Daisy7_clone_rewgt_flux->Clone()->Write("Tracker_Flux_reweighted_Daisy_7");
h_Enu_TRUE_Daisy8_clone_rewgt_flux->Clone()->Write("Tracker_Flux_reweighted_Daisy_8");
h_Enu_TRUE_Daisy9_clone_rewgt_flux->Clone()->Write("Tracker_Flux_reweighted_Daisy_9");
h_Enu_TRUE_Daisy10_clone_rewgt_flux->Clone()->Write("Tracker_Flux_reweighted_Daisy_10");
h_Enu_TRUE_Daisy11_clone_rewgt_flux->Clone()->Write("Tracker_Flux_reweighted_Daisy_11");


//h_Enu_TRUE->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonE.h_effDom);
//h_Enu_TRUE->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonE.h_effDom);
//h_Enu_TRUE_Slice1->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonE.h_effDom);
//h_Enu_TRUE_Slice2->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonE.h_effDom);
//h_Enu_TRUE_Slice3->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonE.h_effDom);
//h_Enu_TRUE_Slice4->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonE.h_effDom);
//h_Enu_TRUE_Daisy0->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonE.h_effDom);
//h_Enu_TRUE_Daisy1->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonE.h_effDom);
//h_Enu_TRUE_Daisy2->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonE.h_effDom);
//h_Enu_TRUE_Daisy3->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonE.h_effDom);
//h_Enu_TRUE_Daisy4->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonE.h_effDom);
//h_Enu_TRUE_Daisy5->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonE.h_effDom);
//h_Enu_TRUE_Daisy6->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonE.h_effDom);
//h_Enu_TRUE_Daisy7->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonE.h_effDom);
//h_Enu_TRUE_Daisy8->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonE.h_effDom);
//h_Enu_TRUE_Daisy9->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonE.h_effDom);
//h_Enu_TRUE_Daisy10->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonE.h_effDom);
//h_Enu_TRUE_Daisy11->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonE.h_effDom);
//Playlist_MnvH2D_Map h_Enu_TRUE_vertex_X_Map =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(TrackerTFile_Map_MC_TRUTH_FLUX, "h_Enu_TRUE_vertex_X" );
//Playlist_MnvH2D_Map h_Enu_TRUE_vertex_Y_Map =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(TrackerTFile_Map_MC_TRUTH_FLUX, "h_Enu_TRUE_vertex_Y" );



auto h2d_Enu_TRUE_Slice = Combine_2DHists_fromMAP(NuE_true_Enu_slice_Map , TrackerME_playlist_vector.at(3) ,"h2d_Enu_TRUE_Slice");
auto h2d_Enu_TRUE_daisy = Combine_2DHists_fromMAP(NuE_true_Enu_daisy_Map , TrackerME_playlist_vector.at(3) ,"h2d_Enu_TRUE_daisy");


//auto h2d_Enu_TRUE_RECO_Slice = Combine_2DHists_fromMAP(NuE_true_RECO_Enu_slice_Map ,TrackerME_playlist_vector.at(3) ,"h_Enu_TRUE_RECO_Slice");
//auto h2d_Enu_TRUE_vertex_Y = Combine_2DHists_fromMAP(NuE_true_Enu_slice_Map , TrackerME_playlist_vector.at(3) ,"h_Enu_TRUE_vertex_X");
//auto h2d_Enu_TRUE_vertex_X = Combine_2DHists_fromMAP(NuE_true_Enu_slice_Map , TrackerME_playlist_vector.at(3) ,"h2d_Enu_TRUE_vertex_Y");

//auto h2d_Enu_TRUE_Slice = Combine_2DHists_fromMAP(NuE_true_Enu_slice_Map , TrackerME_playlist_vector.at(3) ,"h2d_Enu_TRUE_Slice");


Playlist_MnvH2D_Map h2d_Enu_TRUE_vertex_X_Map =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(TrackerTFile_Map_MC_TRUTH_FLUX, "h_Enu_TRUE_vertex_X" );
Playlist_MnvH2D_Map h2d_Enu_TRUE_vertex_Y_Map =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(TrackerTFile_Map_MC_TRUTH_FLUX, "h_Enu_TRUE_vertex_Y" );


Playlist_MnvH2D_Map h2d_Enu_TRUE_vertex_X_Map1 =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(TrackerTFile_Map_MC_TRUTH_FLUX, "h_Enu_TRUE_vertex_X_reduced" );
Playlist_MnvH2D_Map h2d_Enu_TRUE_vertex_Y_Map1 =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(TrackerTFile_Map_MC_TRUTH_FLUX, "h_Enu_TRUE_vertex_Y_reduced" );

Playlist_MnvH2D_Map h2d_Enu_TRUE_vertex_X_Map2 =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(TrackerTFile_Map_MC_TRUTH_FLUX, "h_Enu_TRUE_vertex_X_reduced1" );
Playlist_MnvH2D_Map h2d_Enu_TRUE_vertex_Y_Map2 =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(TrackerTFile_Map_MC_TRUTH_FLUX, "h_Enu_TRUE_vertex_Y_reduced1" );

auto h2d_Enu_TRUE_vertex_Y = Combine_2DHists_fromMAP(h2d_Enu_TRUE_vertex_Y_Map , TrackerME_playlist_vector.at(3) ,"h2d_Enu_TRUE_vertex_Y");
auto h2d_Enu_TRUE_vertex_X = Combine_2DHists_fromMAP(h2d_Enu_TRUE_vertex_X_Map , TrackerME_playlist_vector.at(3) ,"h2d_Enu_TRUE_vertex_X");

auto h2d_Enu_TRUE_vertex_Y1 = Combine_2DHists_fromMAP(h2d_Enu_TRUE_vertex_Y_Map1 , TrackerME_playlist_vector.at(3) ,"h2d_Enu_TRUE_vertex_Y1");
auto h2d_Enu_TRUE_vertex_X1 = Combine_2DHists_fromMAP(h2d_Enu_TRUE_vertex_X_Map1 , TrackerME_playlist_vector.at(3) ,"h2d_Enu_TRUE_vertex_X1");

auto h2d_Enu_TRUE_vertex_Y2 = Combine_2DHists_fromMAP(h2d_Enu_TRUE_vertex_Y_Map2 , TrackerME_playlist_vector.at(3) ,"h2d_Enu_TRUE_vertex_Y2");
auto h2d_Enu_TRUE_vertex_X2 = Combine_2DHists_fromMAP(h2d_Enu_TRUE_vertex_X_Map2 , TrackerME_playlist_vector.at(3) ,"h2d_Enu_TRUE_vertex_X2");


h2d_Enu_TRUE_vertex_Y->Clone()->Write("h2d_Enu_TRUE_vertex_Y");
h2d_Enu_TRUE_vertex_X->Clone()->Write("h2d_Enu_TRUE_vertex_X");

h2d_Enu_TRUE_vertex_Y1->Clone()->Write("h2d_Enu_TRUE_vertex_Y_reduced");
h2d_Enu_TRUE_vertex_X1->Clone()->Write("h2d_Enu_TRUE_vertex_X_reduced");

h2d_Enu_TRUE_vertex_Y2->Clone()->Write("h2d_Enu_TRUE_vertex_Y_reduced1");
h2d_Enu_TRUE_vertex_X2->Clone()->Write("h2d_Enu_TRUE_vertex_X_reduced1");

h_Enu_TRUE->Clone()->Write("h_Enu_tracker_TRUE");
Enu_reweighted->Clone()->Write("Enu_tracker_TRUE_reweighted");

auto h_Enu_TRUE_clone = (MnvH1D*)h_Enu_TRUE->Clone("h_Enu_TRUE_clone");

h_Enu_TRUE->Divide(h_Enu_TRUE,Enu_reweighted);
h_Enu_TRUE->Clone()->Write("h_Enu_tracker_TRUE_Ratio");

h_Enu_TRUE_Daisy0->Clone()->Write("h_Enu_TRUE_tracker_Daisy0");
h_Enu_TRUE_Daisy1->Clone()->Write("h_Enu_TRUE_tracker_Daisy1");
h_Enu_TRUE_Daisy2->Clone()->Write("h_Enu_TRUE_tracker_Daisy2");
h_Enu_TRUE_Daisy3->Clone()->Write("h_Enu_TRUE_tracker_Daisy3");
h_Enu_TRUE_Daisy4->Clone()->Write("h_Enu_TRUE_tracker_Daisy4");
h_Enu_TRUE_Daisy5->Clone()->Write("h_Enu_TRUE_tracker_Daisy5");
h_Enu_TRUE_Daisy6->Clone()->Write("h_Enu_TRUE_tracker_Daisy6");
h_Enu_TRUE_Daisy7->Clone()->Write("h_Enu_TRUE_tracker_Daisy7");
h_Enu_TRUE_Daisy8->Clone()->Write("h_Enu_TRUE_tracker_Daisy8");
h_Enu_TRUE_Daisy9->Clone()->Write("h_Enu_TRUE_tracker_Daisy9");
h_Enu_TRUE_Daisy10->Clone()->Write("h_Enu_TRUE_tracker_Daisy10");
h_Enu_TRUE_Daisy11->Clone()->Write("h_Enu_TRUE_tracker_Daisy11");





for(auto wgt:Vector_daisy_wgts){
std::cout<< number<< " wgt "<< wgt<<std::endl;
  number ++;
}




h_Enu_TRUE_Daisy0->Add(h_Enu_TRUE_Daisy1,1.0);
h_Enu_TRUE_Daisy0->Add(h_Enu_TRUE_Daisy2,1.0);
h_Enu_TRUE_Daisy0->Add(h_Enu_TRUE_Daisy3,1.0);
h_Enu_TRUE_Daisy0->Add(h_Enu_TRUE_Daisy4,1.0);
h_Enu_TRUE_Daisy0->Add(h_Enu_TRUE_Daisy5,1.0);
h_Enu_TRUE_Daisy0->Add(h_Enu_TRUE_Daisy6,1.0);
h_Enu_TRUE_Daisy0->Add(h_Enu_TRUE_Daisy7,1.0);
h_Enu_TRUE_Daisy0->Add(h_Enu_TRUE_Daisy8,1.0);
h_Enu_TRUE_Daisy0->Add(h_Enu_TRUE_Daisy9,1.0);
h_Enu_TRUE_Daisy0->Add(h_Enu_TRUE_Daisy10,1.0);
h_Enu_TRUE_Daisy0->Add(h_Enu_TRUE_Daisy11,1.0);
h_Enu_TRUE_Daisy0->Clone()->Write("h_Enu_tracker_TRUE_inhouseSum");

h_Enu_TRUE_clone->Divide(h_Enu_TRUE_clone,h_Enu_TRUE_Daisy0);
h_Enu_TRUE_clone->Clone()->Write("h_Enu_tracker_TRUE_inhouseSum_ratio");

h_Enu_TRUE_Anezkak->Clone()->Write("h_Enu_tracker_Anezkak_TRUE");

h_Enu_TRUE_Slice1->Clone()->Write("h_Enu_tracker_TRUE_Slice1");
h_Enu_TRUE_Slice2->Clone()->Write("h_Enu_tracker_TRUE_Slice2");
h_Enu_TRUE_Slice3->Clone()->Write("h_Enu_tracker_TRUE_Slice3");
h_Enu_TRUE_Slice4->Clone()->Write("h_Enu_tracker_TRUE_Slice4");

h2d_Enu_TRUE_Slice->Clone()->Write("h2d_Enu_TRUE_Slice");

h2d_Enu_TRUE_daisy->Clone()->Write("h2d_Enu_TRUE_Daisy");
//h2d_Enu_TRUE_RECO_Slice->Clone()->Write("h2d_Enu_TRUE_RECO_Slice");

}




//Playlist_HistFolio_MnvH2D_Map Signal_BG_hists_Map = Constuct_HistFolio_MnvH2DMap_FromME_playlist_TFileMAP(TrackerTFile_Map_MC_REC, "h_Muon_PZ_PT_SignalSelection" );

outFile->Close();

//Playlist_MnvH1D_Map reco_Tracklength_Map =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TrackerTFile_Map_MC_RECO, "h_secTrk_tracklength" );



} // end of RunCrossSectionExtractor



/////////////////////////////////////////////
std::vector<MuonVar> GetCrossSectionVaribles() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<MuonVar> MuonVars;

  MuonVars.push_back(kE);
  MuonVars.push_back(kP_Z);
  MuonVars.push_back(kP_T);
  MuonVars.push_back(kAngleWRTB);

  return MuonVars;
//#endif
}


std::vector<ME_helium_Playlists> GetTrackerPlayListVector() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ME_helium_Playlists> Playlist;

  Playlist.push_back(kME1P);
  Playlist.push_back(kME1C);
  Playlist.push_back(kME1D);
  Playlist.push_back(kME1F);
  Playlist.push_back(kME1E);
  Playlist.push_back(kME1G);
  Playlist.push_back(kME1A);
  Playlist.push_back(kME1L);
  Playlist.push_back(kME1M);
  Playlist.push_back(kME1N);
  Playlist.push_back(kME1B);
  Playlist.push_back(kME1O);

  return Playlist;
//#endif
}

std::vector<ME_helium_Playlists> GetEmptyPlayListVector() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ME_helium_Playlists> Playlist;



  return Playlist;
//#endif
}


void Playlist_CutTableLatex_TRUTH(CutMap inputMap , char *playlist_name_char, std::string CyroTank_status  )
{
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"Printing CutRate for:" <<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

  char Title[1024];

  sprintf(Title, "LatexCut_Table_TRUTH_%s.txt", playlist_name_char );


std::map<ECutsTRUTH, double>::iterator Cut_iter;

  std::ostringstream output_string;
  output_string.precision(6);

  auto table = makeTableString(5,"l");

  output_string <<"\\begin{frame}{"<<  playlist_name_char << " TRUE Cut Table}"<< "\n";
  output_string << "\\resizebox{\\textwidth}{!}{" << "\n";
  output_string << "\\begin{table}[]" << "\n";
  output_string << "\\begin{tabular}{||" << table << "|} \n";
  output_string << "\\hline \n";
  output_string << "Cut name (Playlist " <<  playlist_name_char << " [CryoTank "<< CyroTank_status <<  "] ) & NEvents & loss &  $\\%$ loss & Total $\\%$ loss \\\\" << "\n";
  output_string << "\\hline \n";
  output_string << "\\hline \n";
double CutValue_previous = inputMap.MC_TRUTH_CutsMap.begin()->second;
double total_events = CutValue_previous;

for(Cut_iter = inputMap.MC_TRUTH_CutsMap.begin(); Cut_iter!= inputMap.MC_TRUTH_CutsMap.end(); ++Cut_iter  ){

double CutValue = Cut_iter->second;
double loss = CutValue_previous -  CutValue;
double loss_percent = (loss / CutValue_previous) * 100;
double total_precent_loss = ((total_events - CutValue) / total_events)* 100;

CutValue = roundtoTenth(CutValue);
loss = roundtoTenth(loss);
loss_percent = roundToHundreths(loss_percent);
total_precent_loss = roundToHundreths(total_precent_loss);

output_string << GetCutNameLatexTRUTH(Cut_iter->first) << " & "<< Cut_iter->second << " & " << loss << " & " << loss_percent << "&" << total_precent_loss << " \\\\" << "\n";
CutValue_previous = Cut_iter->second;
output_string << "\\hline \n";
}

  output_string << "\\hline \n";
  output_string << "\\end{tabular} \n";
  output_string << "\\end{table}} \n";
  output_string << "\\end{frame} \n";
  std::ofstream myfile;
  myfile.open(Title);
  myfile<<output_string.str();

  myfile.close();


}//end function

void Playlist_CutTableLatex_RECO(CutMap inputMap , char *playlist_name_char, std::string CyroTank_status  )
{
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"Printing CutRate for:" <<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

  char Title[1024];

  sprintf(Title, "LatexCut_Table_RECO_%s.txt", playlist_name_char );


std::map<ECutsTRUTH, double>::iterator Cut_iter;

  std::ostringstream output_string;
  output_string.precision(6);
  output_string <<"\\begin{frame}{"<<  playlist_name_char << " Cut Table}"<< "\n";

  auto table = makeTableString(5,"l");
  output_string << "\\resizebox{\\textwidth}{!}{" << "\n";
  output_string << "\\begin{table}[]" << "\n";
  output_string << "\\begin{tabular}{||" << table << "|} \n";
  output_string << "Cut name (Playlist " <<  playlist_name_char << " [CryoTank "<< CyroTank_status <<  "]  ) & NEvents & loss &  $\\%$ loss & Total $\\%$ loss \\\\" << "\n";
  output_string << "\\hline \n";
  output_string << "\\hline \n";
double CutValue_previous = inputMap.MC_TRUTH_CutsMap.begin()->second;
double total_events = CutValue_previous;
double combined = 0;
for(Cut_iter = inputMap.MC_TRUTH_CutsMap.begin(); Cut_iter!= inputMap.MC_TRUTH_CutsMap.end(); ++Cut_iter  ){

double CutValue = Cut_iter->second;
double loss = CutValue_previous -  CutValue;
combined = combined + loss;
double loss_percent = (loss / CutValue_previous) * 100;
double total_precent_loss = ((total_events - combined ) / total_events)* 100;

CutValue = roundtoTenth(CutValue);
loss = roundtoTenth(loss);
loss_percent = roundToHundreths(loss_percent);
total_precent_loss = roundToHundreths(total_precent_loss);

output_string << GetCutNameLatexTRUTH(Cut_iter->first) << " & "<< CutValue << " & " << loss << " & " << loss_percent << "&" << total_precent_loss << " \\\\" << "\n";
CutValue_previous = Cut_iter->second;
  output_string << "\\hline \n";

}

  output_string << "\\hline \n";
  output_string << "\\end{tabular} \n";
  output_string << "\\end{table}} \n";
  output_string << "\\end{frame} \n";
  std::ofstream myfile;
  myfile.open(Title);
  myfile<<output_string.str();

  myfile.close();


}//end function


void Playlist_CutTableLatex_Efficiency_Purity(CutMap inputMap , char *playlist_name_char, std::string CyroTank_status   )
{
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"Printing CutRate for:" <<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

  char Title[1024];

  sprintf(Title, "LatexCut_Table_RECO_%s.txt", playlist_name_char );

  double TotalNTruth_forEff = inputMap.MC_TRUTH_CutsMap[kAllTRUTHCuts];



  std::map<ECuts, double>::iterator CutData_iter;
  std::map<ECuts, double>::iterator CutRECO_iter;
  std::map<ECuts, double>::iterator CutRECOHelium_iter;
  std::map<ECuts, double>::iterator TRUTH_RECO_iter;


  std::ostringstream output_string;
  output_string.precision(6);

  output_string <<"\\begin{frame}{"<<  playlist_name_char << " RECO Cut Table}"<< "\n";

  auto table = makeTableString(12,"l");
  output_string << "\\resizebox{\\textwidth}{!}{" << "\n";
  output_string << "\\begin{table}[]" << "\n";
  output_string << "\\begin{tabular}{||" << table << "|} \n";
  output_string << "\\hline \n";
  output_string << "Cut name (Playlist " <<  playlist_name_char <<" [CryoTank "<< CyroTank_status <<  "]  ) & NEvents DATA & loss &  $\\%$ loss & Total $\\%$ loss  & NEvents MC & loss &  $\\%$ loss & Total $\\%$ loss  & $\\%$ Eff &  $\\%$ Purity \\\\" << "\n";
  output_string << "\\hline \n";
  output_string << "\\hline \n";
double CutValue_previous_data = inputMap.DATA_CutsMap.begin()->second;
double total_eventsData = CutValue_previous_data;
double CutValue_previous_Reco = inputMap.MC_RECO_CutsMap.begin()->second;
double total_eventsReco = CutValue_previous_Reco;

double combined_data = 0;
double combined_mc = 0;

for(CutData_iter = inputMap.DATA_CutsMap.begin(),
    CutRECO_iter = inputMap.MC_RECO_CutsMap.begin(),
    CutRECOHelium_iter = inputMap.MC_RECO_Helium_CutsMap.begin(),
    TRUTH_RECO_iter = inputMap.MCRecoBr_TRUTH_RECO_CutsMap.begin();
    CutRECO_iter!= inputMap.MC_RECO_CutsMap.end();
    ++CutRECO_iter, ++CutData_iter, ++CutRECOHelium_iter, ++TRUTH_RECO_iter)
    {

      auto name1 = GetCutNameforLatex(CutData_iter->first);
      auto name2 = GetCutNameforLatex(CutRECO_iter->first);
      auto name3 = GetCutNameforLatex(CutRECOHelium_iter->first);
      auto name4 = GetCutNameforLatex(TRUTH_RECO_iter->first);

      std::cout<< "CutData_iter = " << name1<<std::endl;
      std::cout<< "CutRECO_iter = " << name2<<std::endl;
      std::cout<< "CutRECOHelium_iter = " << name3<<std::endl;
      std::cout<< "TRUTH_RECO_iter = " << name4<<std::endl;
      std::cout<< " "<<std::endl;
      std::cout<< " "<<std::endl;

      if(CutData_iter->first != CutRECO_iter->first ||
        CutData_iter->first != CutRECOHelium_iter->first /*||
        CutData_iter->first != TRUTH_RECO_iter->first*/ ) {

          std::cout<<"Cuts are not the same in loop something needs to be Checked" <<std::endl;
          std::cout<< "CutData_iter->first " << GetCutNameforLatex(CutData_iter->first)<< std::endl;
          std::cout<< "CutRECO_iter->first" << GetCutNameforLatex(CutRECO_iter->first)<< std::endl;
          std::cout<< "CutRECOHelium_iter->first " << GetCutNameforLatex(CutRECOHelium_iter->first)  <<std::endl;
          std::cout<< "TRUTH_RECO_iter->first " << GetCutNameforLatex(TRUTH_RECO_iter->first) <<std::endl;

          assert(false);
        }

        double CutValue_data = CutData_iter->second;
        double loss_data = CutValue_previous_data -  CutValue_data;
        combined_data = combined_data + loss_data;
        double loss_percent_data = (loss_data / CutValue_previous_data) * 100;
        double total_precent_loss_data = ((total_eventsData - CutValue_previous_data) / total_eventsData)* 100;

        double CutValue_MCRECO = CutRECO_iter->second;
        double loss_MCRECO = CutValue_previous_Reco -  CutValue_MCRECO;
        combined_mc = combined_mc + loss_MCRECO;
        double loss_percent_MCRECO = (loss_MCRECO / CutValue_previous_Reco) * 100;
        double total_precent_loss_MCRECO = ((total_eventsReco - combined_mc) / total_eventsReco)* 100;

        double Efficiency =  (TRUTH_RECO_iter->second / TotalNTruth_forEff) * 100 ;
        double Purity =   (CutRECOHelium_iter->second / CutValue_MCRECO) * 100 ;

        std::cout<< "Purity = "<< Purity << "  top = " << CutRECOHelium_iter->second << " bottom =  " << CutValue_MCRECO << std::endl;

        CutValue_data = roundtoTenth(CutValue_data);
        loss_data = roundtoTenth(loss_data);
        loss_percent_data = roundToHundreths(loss_percent_data);
        total_precent_loss_data = roundToHundreths(total_precent_loss_data);
        CutValue_MCRECO = roundtoTenth(CutValue_MCRECO);
        loss_MCRECO = roundToHundreths(loss_MCRECO);
        loss_percent_MCRECO = roundToHundreths(loss_percent_MCRECO);
        total_precent_loss_MCRECO = roundToHundreths(total_precent_loss_MCRECO);
        Efficiency = roundToHundreths(Efficiency);
        Purity = roundToHundreths(Purity);




        output_string << GetCutNameforLatex(CutRECO_iter->first) << " & "<< CutValue_data << " & " << loss_data << " & " << loss_percent_data << "&" <<
        total_precent_loss_data << " & "  <<  CutValue_MCRECO << " & " << loss_MCRECO << " & " << loss_percent_MCRECO << "&" <<
        total_precent_loss_MCRECO <<  " & " <<    Efficiency << " & " << Purity     << " \\\\" << "\n";
        CutValue_previous_data = CutData_iter->second;
        CutValue_previous_Reco = CutRECO_iter->second;
output_string << "\\hline \n";
      }//end function

      output_string << "\\hline \n";
      output_string << "\\end{tabular} \n";
      output_string << "\\end{table}} \n";
      output_string << "\\end{frame} \n";

      std::ofstream myfile;
      myfile.open(Title);
      myfile<<output_string.str();

      myfile.close();



    }


void Make_latexTables_CutMap(CutMap inputMap,char *playlist_name_char, std::string CyroTank_status ){
  std::cout<<"Making Latex Table"<< std::endl;
  Playlist_CutTableLatex_RECO(inputMap , playlist_name_char , CyroTank_status );
  Playlist_CutTableLatex_Efficiency_Purity(inputMap , playlist_name_char, CyroTank_status );
  Playlist_CutTableLatex_TRUTH(inputMap , playlist_name_char, CyroTank_status  );

}


std::vector<Muon2DVar> GetCrossSection2DVaribles() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<Muon2DVar> MuonVars;

  MuonVars.push_back(kPT_PZ);
  MuonVars.push_back(kE_theta);


  return MuonVars;
//#endif
}
/*
void POT_Normalize_2DCrossSection_Hist(CrossSection2D_Hist &inputCross_Hist, double normalize_MC_data, double normalize_fullData_emptyData, bool dodata){
  if(dodata==true){
    inputCross_Hist.h_Data_Signal->Scale(normalize_fullData_emptyData);
  }

  inputCross_Hist.h_effNum->Scale(normalize_MC_data);
  inputCross_Hist.h_effDom->Scale(normalize_MC_data);
  inputCross_Hist.h_mvnreponse_Mig->Scale(normalize_MC_data); // in CCQENuPion2D then seem to also scale the Mig
  inputCross_Hist.h_mvnreponse_RECO->Scale(normalize_MC_data);
  inputCross_Hist.h_mvnreponse_TRUE->Scale(normalize_MC_data);
  inputCross_Hist.h_RECO->Scale(normalize_MC_data);

}
*/


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




RunCrossSectionExtractor( my_norm, my_debug,  my_Print_Systmatics);

return 0;

}
