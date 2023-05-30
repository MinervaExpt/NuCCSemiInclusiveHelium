//Author: Christian Nguyen
// Helium Cross Section Extractor.cxx
// Started to Build: May 17 2020
//email: christian2nguyen@ufl.edu

#include "ExtractHeliumCrossSectionHists.h"
#include "PlotUtils/TargetUtils.h"


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
auto PlaylistME_1P_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/MasterAnaDev_minervame1P_RECO_MC_All_SysErrorsOn_Fid.root";
auto PlaylistME_1C_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/MasterAnaDev_minervame1C_RECO_MC_All_SysErrorsOn_Fid.root";
auto PlaylistME_1D_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/MasterAnaDev_minervame1D_RECO_MC_All_SysErrorsOn_Fid.root";
auto PlaylistME_1F_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/MasterAnaDev_minervame1F_RECO_MC_All_SysErrorsOn_Fid.root";
auto PlaylistME_1E_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/MasterAnaDev_minervame1E_RECO_MC_All_SysErrorsOn_Fid.root";
auto PlaylistME_1G_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/MasterAnaDev_minervame1G_RECO_MC_All_SysErrorsOn_Fid.root";
auto PlaylistME_1A_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/MasterAnaDev_minervame1A_RECO_MC_All_SysErrorsOn_Fid.root";
auto PlaylistME_1L_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/MasterAnaDev_minervame1L_RECO_MC_All_SysErrorsOn_Fid.root";
auto PlaylistME_1M_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/MasterAnaDev_minervame1M_RECO_MC_All_SysErrorsOn_Fid.root";
auto PlaylistME_1N_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/MasterAnaDev_minervame1N_RECO_MC_All_SysErrorsOn_Fid.root";
auto PlaylistME_1B_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/MasterAnaDev_minervame1B_RECO_MC_All_SysErrorsOn_Fid.root";
auto PlaylistME_1O_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/MasterAnaDev_minervame1O_RECO_MC_All_SysErrorsOn_Fid.root";

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
ME_playlist_RootPathMAP MAP_RootPath_Tracker_MC_TRUTH_Flux;
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

MAP_RootPath_Tracker_MC_TRUTH_Flux.insert(std::make_pair(TrackerME_playlist_vector.at(0),  PlaylistME_1P_MC_FLUX_TRUTH_path));
MAP_RootPath_Tracker_MC_TRUTH_Flux.insert(std::make_pair(TrackerME_playlist_vector.at(1),  PlaylistME_1C_MC_FLUX_TRUTH_path));
MAP_RootPath_Tracker_MC_TRUTH_Flux.insert(std::make_pair(TrackerME_playlist_vector.at(2),  PlaylistME_1D_MC_FLUX_TRUTH_path));
MAP_RootPath_Tracker_MC_TRUTH_Flux.insert(std::make_pair(TrackerME_playlist_vector.at(3),  PlaylistME_1F_MC_FLUX_TRUTH_path));
MAP_RootPath_Tracker_MC_TRUTH_Flux.insert(std::make_pair(TrackerME_playlist_vector.at(4),  PlaylistME_1E_MC_FLUX_TRUTH_path));
MAP_RootPath_Tracker_MC_TRUTH_Flux.insert(std::make_pair(TrackerME_playlist_vector.at(5),  PlaylistME_1G_MC_FLUX_TRUTH_path));
MAP_RootPath_Tracker_MC_TRUTH_Flux.insert(std::make_pair(TrackerME_playlist_vector.at(6),  PlaylistME_1A_MC_FLUX_TRUTH_path));
MAP_RootPath_Tracker_MC_TRUTH_Flux.insert(std::make_pair(TrackerME_playlist_vector.at(7),  PlaylistME_1L_MC_FLUX_TRUTH_path));
MAP_RootPath_Tracker_MC_TRUTH_Flux.insert(std::make_pair(TrackerME_playlist_vector.at(8),  PlaylistME_1M_MC_FLUX_TRUTH_path));
MAP_RootPath_Tracker_MC_TRUTH_Flux.insert(std::make_pair(TrackerME_playlist_vector.at(9),  PlaylistME_1N_MC_FLUX_TRUTH_path));
MAP_RootPath_Tracker_MC_TRUTH_Flux.insert(std::make_pair(TrackerME_playlist_vector.at(10), PlaylistME_1B_MC_FLUX_TRUTH_path));
MAP_RootPath_Tracker_MC_TRUTH_Flux.insert(std::make_pair(TrackerME_playlist_vector.at(11), PlaylistME_1O_MC_FLUX_TRUTH_path));





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
auto outFile = TFile::Open("CrossSection_MasterAnaDev.root", "RECREATE");

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

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<< "TRYING : MuonE " << std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

ME_playlist_CrossSection_MAP CrossSection_Hist_Playlist_Map_MuonE = Constuct_crosssection_Hists_PlaylistMap(MuonE_names, TrackerTFile_Map_MC_RECO, TrackerTFile_Map_MC_TRUTH, TrackerTFile_Map_DATA );
//Constuct_crosssection_Hists_PlaylistMap_noBG
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<< "TRYING : MuonpZ " << std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;


ME_playlist_CrossSection_MAP CrossSection_Hist_Playlist_Map_MuonPZ = Constuct_crosssection_Hists_PlaylistMap(MuonPZ_names, TrackerTFile_Map_MC_RECO, TrackerTFile_Map_MC_TRUTH, TrackerTFile_Map_DATA );

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<< "TRYING : Muon pt " << std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;


ME_playlist_CrossSection_MAP CrossSection_Hist_Playlist_Map_MuonPT = Constuct_crosssection_Hists_PlaylistMap(MuonPT_names, TrackerTFile_Map_MC_RECO, TrackerTFile_Map_MC_TRUTH, TrackerTFile_Map_DATA );

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<< "TRYING : Muon theta " << std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;


ME_playlist_CrossSection_MAP CrossSection_Hist_Playlist_Map_MuonTheta = Constuct_crosssection_Hists_PlaylistMap(MuonTheta_names, TrackerTFile_Map_MC_RECO, TrackerTFile_Map_MC_TRUTH, TrackerTFile_Map_DATA );

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<< "TRYING : Muon E " << std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;


ME_playlist_CrossSection_MAP CrossSection_Hist_Playlist_Map_secondTrackAngle =  Constuct_crosssection_Hists_PlaylistMap_noMig_Flux_BG(SecondTrackAngle_names, TrackerTFile_Map_MC_RECO, TrackerTFile_Map_MC_TRUTH, TrackerTFile_Map_DATA);

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<< "TRYING : 2D Pt vs PZ " << std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;




ME_playlist_2DCrossSection_MAP FullCrossSection_Hist_Playlist_Map_MuonPT_PZ = Constuct_2Dcrosssection_Hists_PlaylistMap(MuonPT_PZ_histNames, TrackerTFile_Map_MC_RECO, TrackerTFile_Map_MC_TRUTH, TrackerTFile_Map_DATA );




std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"                          Combined Maps                     "<< std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;


std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"                          AddInteractionHistMap                     "<< std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~  AddInteractionHistMap_DISbreakdown            ~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<< "TRYING : MuonE " << std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;


AddInteractionHistMap_DISbreakdown(CrossSection_Hist_Playlist_Map_MuonE,     TrackerTFile_Map_MC_TRUTH, MuonE_names.hist_Eff_denominator_name, "" );


std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<< "TRYING : Muonpt " << std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;


AddInteractionHistMap_DISbreakdown(CrossSection_Hist_Playlist_Map_MuonPT,    TrackerTFile_Map_MC_TRUTH, MuonPT_names.hist_Eff_denominator_name, "" );

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<< "TRYING : Muon pz " << std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

AddInteractionHistMap_DISbreakdown(CrossSection_Hist_Playlist_Map_MuonPZ,    TrackerTFile_Map_MC_TRUTH, MuonPZ_names.hist_Eff_denominator_name, "");


std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<< "TRYING : 2D " << std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;


AddInteractionHistMap_DISbreakdown(CrossSection_Hist_Playlist_Map_MuonTheta, TrackerTFile_Map_MC_TRUTH, MuonTheta_names.hist_Eff_denominator_name, "" );

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<< "TRYING : Muon theta " << std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;



AddInteraction2DHistMap_DISbreakdown(FullCrossSection_Hist_Playlist_Map_MuonPT_PZ,   TrackerTFile_Map_MC_TRUTH, "h_Muon_PZ_PT", "" );


std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"  Combine_crosssection_Hists_PlaylistMap_includeInteraction   "<< std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<< "TRYING : MuonE " << std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;


CrossSection_Hist CombinedHist_MuonE     =  Combine_crosssection_Hists_PlaylistMap_includeInteraction_DISbreakdown(CrossSection_Hist_Playlist_Map_MuonE,         TrackerME_playlist_vector.at(3));
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<< "TRYING : Muon pz " << std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

CrossSection_Hist CombinedHist_MuonPZ    =  Combine_crosssection_Hists_PlaylistMap_includeInteraction_DISbreakdown(CrossSection_Hist_Playlist_Map_MuonPZ,        TrackerME_playlist_vector.at(3));
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<< "TRYING : Muonpt " << std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;


CrossSection_Hist CombinedHist_MuonPT    =  Combine_crosssection_Hists_PlaylistMap_includeInteraction_DISbreakdown(CrossSection_Hist_Playlist_Map_MuonPT,        TrackerME_playlist_vector.at(3));
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<< "TRYING : Muon theta " << std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;


CrossSection_Hist CombinedHist_MuonTheta =  Combine_crosssection_Hists_PlaylistMap_includeInteraction_DISbreakdown(CrossSection_Hist_Playlist_Map_MuonTheta,     TrackerME_playlist_vector.at(3));

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<< "TRYING : SecondTrackAngle " << std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

CrossSection_Hist CombinedHist_SecondTrackAngle =  Combine_crosssection_Hists_PlaylistMap_noFlux_mig_BG(CrossSection_Hist_Playlist_Map_secondTrackAngle,     TrackerME_playlist_vector.at(3));


std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<< "TRYING : 2D " << std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;



CrossSection2D_Hist CombinedHist_MuonPT_PZ     =  Combine_2Dcrosssection_Hists_PlaylistMap_includeInteraction_DISbreakdown(FullCrossSection_Hist_Playlist_Map_MuonPT_PZ,         TrackerME_playlist_vector.at(3));

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~Normalize Hist ~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;


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


POT_Normalize_CrossSection_Hist(CombinedHist_MuonE , MC_to_Data);
POT_Normalize_CrossSection_Hist(CombinedHist_MuonPZ , MC_to_Data);
POT_Normalize_CrossSection_Hist(CombinedHist_MuonPT , MC_to_Data);
POT_Normalize_CrossSection_Hist(CombinedHist_MuonTheta , MC_to_Data);
POT_Normalize_2DCrossSection_Hist(CombinedHist_MuonPT_PZ ,   MC_to_Data);

CombinedHist_SecondTrackAngle.h_RECO_Signal->Scale(MC_to_Data);
CombinedHist_SecondTrackAngle.h_effNum->Scale(MC_to_Data);
CombinedHist_SecondTrackAngle.h_effDom->Scale(MC_to_Data);




POT_Normalize_CrossSection_Hist_InteractionOnly_DISBreakdown(CombinedHist_MuonE,     MC_to_Data);
POT_Normalize_CrossSection_Hist_InteractionOnly_DISBreakdown(CombinedHist_MuonPZ,    MC_to_Data);
POT_Normalize_CrossSection_Hist_InteractionOnly_DISBreakdown(CombinedHist_MuonPT,    MC_to_Data);
POT_Normalize_CrossSection_Hist_InteractionOnly_DISBreakdown(CombinedHist_MuonTheta, MC_to_Data);
POT_Normalize_2DCrossSection_Hist_InteractionOnly_DISBreakdown(CombinedHist_MuonPT_PZ,     MC_to_Data);
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~ Checking Binning   ~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

Check_NSignalBins(CombinedHist_MuonE,      "CombinedHist_MuonE");
Check_NSignalBins(CombinedHist_MuonPZ,     "CombinedHist_MuonPZ");
Check_NSignalBins(CombinedHist_MuonPT,     "CombinedHist_MuonPT");
Check_NSignalBins(CombinedHist_MuonTheta,  "CombinedHist_MuonTheta");
//Check2D_NSignalBins(CombinedHist_MuonPT_PZ,      "CombinedHist_MuonPT_PZ");
/////////
//MAKING CUT TABLE
/////////
/*
Playlist_CutMap Total_CutTable;
CutMap Combined_CutMap_Full;
CutMap Combined_CutMap_Empty;
CutMap Combined_CutMap_Full_Empty;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~ Starting to Make Cut Tables   ~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~ Filling Names ~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

FillCutMapPlaylists(Total_CutTable, Playlist_Combined);
FillCutMapPlaylists(Total_CutTable, "RECO_Data_Cuts",  "RECO_Cuts", "RECO_Helium_Cuts", "TRUE_RECO_Cuts", "Truth_Cuts", "Truth_Cuts");

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~ Finished Filling Names   ~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~ Filling Full ~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;


for(auto playlist : FullME_playlist_vector){
FillCutMap_fromTFiles(Total_CutTable[playlist], FullTFile_Map_MC_TRUTH[playlist],   FullTFile_Map_MC_RECO[playlist], FullTFile_Map_DATA[playlist]);
}

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~ Finished Filling Full   ~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~ Filling Empty ~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;


for(auto playlist : EmptyME_playlist_vector){
FillCutMap_fromTFiles(Total_CutTable[playlist], EmptyTFile_Map_MC_TRUTH[playlist],   EmptyTFile_Map_MC_RECO[playlist], EmptyTFile_Map_DATA[playlist]);
}

for(auto playlist : EmptyME_playlist_vector){
FillCutMap_fromTFiles(Total_CutTable[playlist], EmptyTFile_Map_MC_TRUTH[playlist],   EmptyTFile_Map_MC_RECO[playlist], EmptyTFile_Map_DATA[playlist]);
}

for(auto playlist : Playlist_Combined){
ADDCUT_same_Cut_Map_RECO(Total_CutTable[playlist], kNonMu_is_Plausible , kMu_is_Plausible);
ADDCUT_same_Cut_Map_Data(Total_CutTable[playlist], kNonMu_is_Plausible , kMu_is_Plausible);
}




std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~ Starting to Make Combined Cut Map   ~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

std::cout<< "Before: Combined_CutMap_Full.size() = "<< Combined_CutMap_Full.MC_RECO_CutsMap.size() <<std::endl;

CombinedCutMap(Combined_CutMap_Full, Total_CutTable, FullME_playlist_vector, FullME_playlist_vector.at(0) );
CombinedCutMap(Combined_CutMap_Empty, Total_CutTable, EmptyME_playlist_vector, EmptyME_playlist_vector.at(0) );
CombinedCutMap(Combined_CutMap_Full_Empty, Total_CutTable, FullME_playlist_vector, FullME_playlist_vector.at(0) );


std::cout<< "After: Combined_CutMap_Full.size() = "<< Combined_CutMap_Full.MC_RECO_CutsMap.size() <<std::endl;

std::cout<<" "<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<std::endl;
std::cout<<"Printing Events before POT scaling "<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<std::endl;
std::cout<<" "<<std::endl;
PrintCutMapMaptoScreen(Combined_CutMap_Full.MC_RECO_CutsMap);

Scale_CutMap(Combined_CutMap_Full, Full_MC_Full_Data);
Scale_CutMap(Combined_CutMap_Full_Empty, Full_MC_Full_Data);
Scale_CutMap(Combined_CutMap_Empty, Empty_MC_Full_Data, Empty_Data_Full_Data);
/////////////////////////
////// Print Total here
///////////////////////
Make_latexTables_CutMap(Combined_CutMap_Full,"Combined_Full", "Full" );
Make_latexTables_CutMap(Combined_CutMap_Empty,"Combined_Empty", "Empty" );
SubTract_Cut_Map(Combined_CutMap_Full_Empty, Combined_CutMap_Empty);
Make_latexTables_CutMap(Combined_CutMap_Full_Empty,"Combined_Full_Empty", "F-E" );


/////////////////


for(auto playlist : FullME_playlist_vector){
Scale_CutMap(Total_CutTable[playlist], FullMC_ScalingMap[playlist], FullDATA_ScalingMap[playlist] );
}

for(auto playlist : EmptyME_playlist_vector){
Scale_CutMap(Total_CutTable[playlist], EMPTYMC_ScalingMap[playlist], EmptyDATA_ScalingMap[playlist] );
}

for(auto playlist :Playlist_Combined){
std::string playlistname = GetPlaylist_InitialName(playlist);
char playistname_char[playlistname.length()+1];
strcpy(playistname_char,playlistname.c_str());
std::string cryotank_status = GetPlaylistStatusString(GetPlaylist_HeliumStatus(playlist));
Make_latexTables_CutMap(Total_CutTable[playlist], playistname_char, cryotank_status );

}


std::cout<<" "<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<std::endl;
std::cout<<"Printing Events After POT scaling "<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<std::endl;
PrintCutMapMaptoScreen(Combined_CutMap_Full.MC_RECO_CutsMap);
*/




std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~ Writing to File Current Hists   ~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;


std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~ WritetoTFile_All   ~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<< "TRYING : Muon E " << std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

WritetoTFile_All(CombinedHist_MuonE,     *outFile,  "h_MuonE_Tracker");
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<< "TRYING : Muon PZ " << std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

WritetoTFile_All(CombinedHist_MuonPZ,    *outFile,  "h_MuonPZ_Tracker");
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<< "TRYING : Muon PT " << std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

WritetoTFile_All(CombinedHist_MuonPT,    *outFile,  "h_MuonPT_Tracker");

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<< "TRYING : Muon theta " << std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

WritetoTFile_All(CombinedHist_MuonTheta, *outFile,  "h_MuonTheta_Tracker");

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<< "TRYING : 2D " << std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

WritetoTFile_2DAll(CombinedHist_MuonPT_PZ,    *outFile,  "h_MuonPT_PZ_Tracker");

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~ WritetoTFile_Interaction_DISbreakdown   ~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<< "TRYING : Muon E " << std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;



WritetoTFile_Interaction_DISbreakdown(CombinedHist_MuonE,      *outFile, "h_MuonE_Tracker");

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<< "TRYING : Muon PZ " << std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;


WritetoTFile_Interaction_DISbreakdown(CombinedHist_MuonPZ,     *outFile, "h_MuonPZ_Tracker");

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<< "TRYING : Muon PT " << std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;


WritetoTFile_Interaction_DISbreakdown(CombinedHist_MuonPT,     *outFile, "h_MuonPT_Tracker");

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<< "TRYING : Muon theta" << std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;


WritetoTFile_Interaction_DISbreakdown(CombinedHist_MuonTheta,  *outFile, "h_MuonTheta_Tracker");

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~ ~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~Writing Hist ~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;



WritetoTFile_NormTRUECrossSection(CombinedHist_MuonE,      *outFile,  "h_MuonE_Tracker_TrueCrossSection",       nNucleons_MC, Tracker_Data_POT);
WritetoTFile_NormTRUECrossSection(CombinedHist_MuonPT,     *outFile,  "h_MuonPT_Tracker_TrueCrossSection",      nNucleons_MC, Tracker_Data_POT);
WritetoTFile_NormTRUECrossSection(CombinedHist_MuonPZ,     *outFile,  "h_MuonPZ_Tracker_TrueCrossSection",      nNucleons_MC, Tracker_Data_POT);
WritetoTFile_NormTRUECrossSection(CombinedHist_MuonTheta,  *outFile,   "h_MuonTheta_Tracker_TrueCrossSection",  nNucleons_MC, Tracker_Data_POT);

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

WritetoTFile_NormTRUECrossSection_Interaction_DISbreakdown(CombinedHist_MuonE,      *outFile,  "h_MuonE_Tracker",       nNucleons_MC, Tracker_Data_POT);
WritetoTFile_NormTRUECrossSection_Interaction_DISbreakdown(CombinedHist_MuonPT,     *outFile,  "h_MuonPT_Tracker",      nNucleons_MC, Tracker_Data_POT);
WritetoTFile_NormTRUECrossSection_Interaction_DISbreakdown(CombinedHist_MuonPZ,     *outFile,  "h_MuonPZ_Tracker",      nNucleons_MC, Tracker_Data_POT);
WritetoTFile_NormTRUECrossSection_Interaction_DISbreakdown(CombinedHist_MuonTheta,  *outFile,  "h_MuonTheta_Tracker",   nNucleons_MC, Tracker_Data_POT);

WritetoTFile_NormTRUECrossSection_Interaction_DISbreakdown(CombinedHist_MuonPT_PZ, *outFile,  "h_MuonPT_PZ_TrueCrossSection",       nNucleons_MC, Tracker_Data_POT);
WritetoTFile_NormTRUE2DCrossSection(CombinedHist_MuonPT_PZ,      *outFile,  "h_MuonPT_PZ_TrueCrossSection",       nNucleons_MC, Tracker_Data_POT);
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~ BG Subtraction ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

CombinedHist_MuonE.h_Data_Signal->Clone()->Write("h_MuonE_Tracker_data");
CombinedHist_MuonPZ.h_Data_Signal->Clone()->Write("h_MuonPZ_Tracker_data");
CombinedHist_MuonPT.h_Data_Signal->Clone()->Write("h_MuonPT_Tracker_data");
CombinedHist_MuonTheta.h_Data_Signal->Clone()->Write("h_MuonTheta_Tracker_data");
CombinedHist_MuonPT_PZ.h_Data_Signal->Clone()->Write("h_MuonPT_PZ_Tracker_data");

////////////////////////////////////////////////////////////////////////////////
// 1D
////////////////////////////////////////////////////////////////////////////////

CombinedHist_MuonE.h_Data_Signal->AddMissingErrorBandsAndFillWithCV(*CombinedHist_MuonE.h_RECO_BG);
CombinedHist_MuonPZ.h_Data_Signal->AddMissingErrorBandsAndFillWithCV(*CombinedHist_MuonPZ.h_RECO_BG);
CombinedHist_MuonPT.h_Data_Signal->AddMissingErrorBandsAndFillWithCV(*CombinedHist_MuonPT.h_RECO_BG);
CombinedHist_MuonTheta.h_Data_Signal->AddMissingErrorBandsAndFillWithCV(*CombinedHist_MuonTheta.h_RECO_BG);

CombinedHist_MuonE.h_Data_Signal->Add(CombinedHist_MuonE.h_RECO_BG,-1);
CombinedHist_MuonPZ.h_Data_Signal->Add(CombinedHist_MuonPZ.h_RECO_BG,-1);
CombinedHist_MuonPT.h_Data_Signal->Add(CombinedHist_MuonPT.h_RECO_BG,-1);
CombinedHist_MuonTheta.h_Data_Signal->Add(CombinedHist_MuonTheta.h_RECO_BG,-1);


////////////////////////////////////////////////////////////////////////////////
// 2D
////////////////////////////////////////////////////////////////////////////////
CombinedHist_MuonPT_PZ.h_Data_Signal->AddMissingErrorBandsAndFillWithCV(*CombinedHist_MuonPT_PZ.h_RECO_BG);
CombinedHist_MuonPT_PZ.h_Data_Signal->Add(CombinedHist_MuonPT_PZ.h_RECO_BG,-1);






CombinedHist_MuonE.h_Data_Signal->Clone()->Write("h_MuonE_Tracker_Data_BG_Subtracted");
CombinedHist_MuonPZ.h_Data_Signal->Clone()->Write("h_MuonPZ_Tracker_Data_BG_Subtracted");
CombinedHist_MuonPT.h_Data_Signal->Clone()->Write("h_MuonPT_Tracker_Data_BG_Subtracted");
CombinedHist_MuonTheta.h_Data_Signal->Clone()->Write("h_MuonTheta_Tracker_Data_BG_Subtracted");
CombinedHist_MuonPT_PZ.h_Data_Signal->Clone()->Write("h_MuonPT_PZ_Tracker_Data_BG_Subtracted");

CombinedHist_SecondTrackAngle.h_Data_Signal->Clone()->Write("h_Data_SecondTrackAngle");
CombinedHist_SecondTrackAngle.h_RECO_Signal->Clone()->Write("h_RECO_SecondTrackAngle");


std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~ UnFolding ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;


std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
CombinedHist_MuonE.h_Mig->Clone()->Write("h_MuonE_Mig");
auto unfoldedMuonE_data = UnfoldHist(CombinedHist_MuonE.h_Data_Signal, CombinedHist_MuonE.h_Mig, 3 );
unfoldedMuonE_data->Clone()->Write("h_MuonE_Tracker_unfolded_data");
CombinedHist_MuonPZ.h_Mig->Clone()->Write("h_MuonPZ_Mig");
auto unfoldedMuonPZ_data = UnfoldHist( CombinedHist_MuonPZ.h_Data_Signal, CombinedHist_MuonPZ.h_Mig, 3 );
unfoldedMuonPZ_data->Clone()->Write("h_MuonPZ_Tracker_unfolded_data");
CombinedHist_MuonPT.h_Mig->Clone()->Write("h_MuonPT_Mig");
auto unfoldedMuonPT_data = UnfoldHist( CombinedHist_MuonPT.h_Data_Signal, CombinedHist_MuonPT.h_Mig, 3 );
unfoldedMuonPT_data->Clone()->Write("h_MuonPT_Tracker_unfolded_data");
CombinedHist_MuonTheta.h_Mig->Clone()->Write("h_MuonTheta_Mig");
auto unfoldedMuonTheta_data = UnfoldHist( CombinedHist_MuonTheta.h_Data_Signal, CombinedHist_MuonTheta.h_Mig, 3 );
unfoldedMuonTheta_data->Clone()->Write("h_MuonTheta_Tracker_unfolded_data");

CombinedHist_MuonPT_PZ.h_mvnreponse_Mig->Clone()->Write("h_MuonPT_PZ_mvnreponse_Mig");
CombinedHist_MuonPT_PZ.h_mvnreponse_RECO->Clone()->Write("h_MuonPT_PZ_mvnreponse_RECO" );
CombinedHist_MuonPT_PZ.h_mvnreponse_TRUE->Clone()->Write("h_MuonPT_PZ_mvnreponse_TRUE");


bool addSystematics = true;
bool useSysVariatedMigrations = false;
int num_iter=2;
MnvH2D* h_unfoldedData_MuonPT_PZ = nullptr;
h_unfoldedData_MuonPT_PZ = UnfoldHist2D_new(CombinedHist_MuonPT_PZ.h_Data_Signal, CombinedHist_MuonPT_PZ.h_mvnreponse_RECO, CombinedHist_MuonPT_PZ.h_mvnreponse_TRUE, CombinedHist_MuonPT_PZ.h_mvnreponse_Mig, num_iter, addSystematics, useSysVariatedMigrations );
h_unfoldedData_MuonPT_PZ->Clone()->Write("h_MuonPT_PZ_unfolded_data");
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~ efficiency Correct ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
AddErrorBands_TOEffDom(CombinedHist_MuonE);
CombinedHist_MuonE.h_effNum->Divide(CombinedHist_MuonE.h_effNum, CombinedHist_MuonE.h_effDom);
CombinedHist_MuonE.h_effNum->Clone()->Write("h_MuonE_Tracker_efficiency");

unfoldedMuonE_data->Divide(unfoldedMuonE_data, CombinedHist_MuonE.h_effNum);
unfoldedMuonE_data->Clone()->Write("h_MuonE_Tracker_unfolded_data_effcorrected");
///////////////////////////////
CombinedHist_MuonPZ.h_effNum->Divide(CombinedHist_MuonPZ.h_effNum, CombinedHist_MuonPZ.h_effDom);
CombinedHist_MuonPZ.h_effNum->Clone()->Write("h_MuonPZ_Tracker_efficiency");

unfoldedMuonPZ_data->Divide(unfoldedMuonPZ_data, CombinedHist_MuonPZ.h_effNum);
unfoldedMuonPZ_data->Clone()->Write("h_MuonPZ_Tracker_unfolded_data_effcorrected");
////////////////////////////////
AddErrorBands_TOEffDom(CombinedHist_MuonPT);
CombinedHist_MuonPT.h_effNum->Divide(CombinedHist_MuonPT.h_effNum, CombinedHist_MuonPT.h_effDom);
CombinedHist_MuonPT.h_effNum->Clone()->Write("h_MuonPT_Tracker_efficiency");

unfoldedMuonPT_data->Divide(unfoldedMuonPT_data, CombinedHist_MuonPT.h_effNum);
unfoldedMuonPT_data->Clone()->Write("h_MuonPT_Tracker_unfolded_data_effcorrected");

AddErrorBands_TOEffDom(CombinedHist_MuonTheta);
CombinedHist_MuonTheta.h_effNum->Divide(CombinedHist_MuonTheta.h_effNum, CombinedHist_MuonTheta.h_effDom);
CombinedHist_MuonTheta.h_effNum->Clone()->Write("h_MuonTheta_Tracker_efficiency");

unfoldedMuonTheta_data->Divide(unfoldedMuonTheta_data, CombinedHist_MuonTheta.h_effNum);
unfoldedMuonTheta_data->Clone()->Write("h_MuonTheta_Tracker_unfolded_data_effcorrected");


AddErrorBands_TOEffDom(CombinedHist_MuonPT_PZ);
CombinedHist_MuonPT_PZ.h_effNum->Divide(CombinedHist_MuonPT_PZ.h_effNum, CombinedHist_MuonPT_PZ.h_effDom, 1.0,1.0,"B");
CombinedHist_MuonPT_PZ.h_effNum->Clone()->Write("h_MuonPT_PZ_efficiency");

h_unfoldedData_MuonPT_PZ->Divide(h_unfoldedData_MuonPT_PZ, CombinedHist_MuonPT_PZ.h_effNum);
h_unfoldedData_MuonPT_PZ->Clone()->Write("h_MuonPT_PZ_unfolded_data_effcorrected");


CombinedHist_SecondTrackAngle.h_effNum->Clone()->Write("h_SecondTrackAngle_Num");
CombinedHist_SecondTrackAngle.h_effDom->Clone()->Write("h_SecondTrackAngle_Dom");
CombinedHist_SecondTrackAngle.h_effNum->Divide(CombinedHist_SecondTrackAngle.h_effNum, CombinedHist_SecondTrackAngle.h_effDom);
CombinedHist_SecondTrackAngle.h_effNum->Clone()->Write("h_SecondTrackAngle_efficiency");



std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~ Cross Section ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
CombinedHist_MuonPT_PZ.h_flux->AddMissingErrorBandsAndFillWithCV( *CombinedHist_MuonPT_PZ.h_effNum );


auto h_crossSection_MuonE = normalize(unfoldedMuonE_data, CombinedHist_MuonE.h_flux, nNucleons_Data, Tracker_Data_POT);
h_crossSection_MuonE->Clone()->Write("h_MuonE_Tracker_CrossSection_data_unfolded");

auto h_crossSection_MuonPZ = normalize(unfoldedMuonPZ_data, CombinedHist_MuonPZ.h_flux, nNucleons_Data, Tracker_Data_POT);
h_crossSection_MuonPZ->Clone()->Write("h_MuonPZ_Tracker_CrossSection_data_unfolded");

auto h_crossSection_MuonPT = normalize(unfoldedMuonPT_data, CombinedHist_MuonPT.h_flux, nNucleons_Data, Tracker_Data_POT);
h_crossSection_MuonPT->Clone()->Write("h_MuonPT_Tracker_CrossSection_data_unfolded");

auto h_crossSection_MuonTheta = normalize(unfoldedMuonTheta_data, CombinedHist_MuonTheta.h_flux, nNucleons_Data, Tracker_Data_POT);
h_crossSection_MuonTheta->Clone()->Write("h_MuonTheta_Tracker_CrossSection_data_unfolded");

auto h_crossSection_MuonPT_PZ = normalize2D(h_unfoldedData_MuonPT_PZ, CombinedHist_MuonPT_PZ.h_flux, nNucleons_Data, Tracker_Data_POT);
h_crossSection_MuonPT_PZ->Clone()->Write("h_MuonPT_PZ_CrossSection_data_unfolded_effCorrect");


////////////////
/////Flux
/////////////////


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

//uto h2d_Enu_TRUE_vertex_X = Get2DHist(*TFile_ME1C_MC_TRUTH_Flux, "h_Enu_TRUE_vertex_X" );


//h_Enu_TRUE->AddMissingErrorBandsAndFillWithCV(*h_Enu_TRUE_RECO);
//h2d_Enu_TRUE_Slice->AddMissingErrorBandsAndFillWithCV(*h2d_Enu_TRUE_RECO_Slice);
//h_Enu_TRUE_Slice1->AddMissingErrorBandsAndFillWithCV(*h_Enu_TRUE_RECO);
//h_Enu_TRUE_Slice2->AddMissingErrorBandsAndFillWithCV(*h_Enu_TRUE_RECO);
//h_Enu_TRUE_Slice3->AddMissingErrorBandsAndFillWithCV(*h_Enu_TRUE_RECO);
//h_Enu_TRUE_Slice4->AddMissingErrorBandsAndFillWithCV(*h_Enu_TRUE_RECO);



//h_Enu_TRUE->Scale(Full_MC_Full_Data);
//h_Enu_TRUE_RECO->Scale(Full_MC_Full_Data);
//h2d_Enu_TRUE_Slice->Scale(Full_MC_Full_Data);
//h2d_Enu_TRUE_RECO_Slice->Scale(Full_MC_Full_Data);

//h_Enu_TRUE_Slice1->Scale(Full_MC_Full_Data);
//h_Enu_TRUE_RECO_Slice1->Scale(Full_MC_Full_Data);
//h_Enu_TRUE_Slice2->Scale(Full_MC_Full_Data);
//h_Enu_TRUE_RECO_Slice2->Scale(Full_MC_Full_Data);
//h_Enu_TRUE_Slice3->Scale(Full_MC_Full_Data);
//h_Enu_TRUE_RECO_Slice3->Scale(Full_MC_Full_Data);
//h_Enu_TRUE_Slice4->Scale(Full_MC_Full_Data);
//h_Enu_TRUE_RECO_Slice4->Scale(Full_MC_Full_Data);

h_Enu_TRUE->Clone()->Write("h_Enu_tracker_TRUE");
h_Enu_TRUE_Anezkak->Clone()->Write("h_Enu_tracker_Anezkak_TRUE");

h_Enu_TRUE_Slice1->Clone()->Write("h_Enu_tracker_TRUE_Slice1");
h_Enu_TRUE_Slice2->Clone()->Write("h_Enu_tracker_TRUE_Slice2");
h_Enu_TRUE_Slice3->Clone()->Write("h_Enu_tracker_TRUE_Slice3");
h_Enu_TRUE_Slice4->Clone()->Write("h_Enu_tracker_TRUE_Slice4");

h2d_Enu_TRUE_Slice->Clone()->Write("h2d_Enu_TRUE_Slice");

h2d_Enu_TRUE_daisy->Clone()->Write("h2d_Enu_TRUE_Daisy");
//h2d_Enu_TRUE_RECO_Slice->Clone()->Write("h2d_Enu_TRUE_RECO_Slice");



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


//Playlist_HistFolio_MnvH2D_Map Signal_BG_hists_Map = Constuct_HistFolio_MnvH2DMap_FromME_playlist_TFileMAP(TrackerTFile_Map_MC_REC, "h_Muon_PZ_PT_SignalSelection" );

TObjArray Signal_BG_histsTObjArray = ConstuctTObjArray_HistFolio_MnvH2DMap_FromME_playlist_TFileMAP(TrackerTFile_Map_MC_RECO, "h_Muon_PZ_PT_SignalSelection" );
Scale_MnvH2D_Array(Signal_BG_histsTObjArray, MC_to_Data);




unsigned int i = 0;
  for(auto cat : Signal_BG_histsTObjArray) {

    std::string words = Signal_BG_histsTObjArray.At(i)->GetTitle();
    std::cout<<"iHist  = "<< i <<" words = "<< words<<std::endl;

    if(i==0){((PlotUtils::MnvH2D*)Signal_BG_histsTObjArray.At(i))->Write("h_Muon_PZ_PT_SignalSelection_Signal");}
    else if(i==1){((PlotUtils::MnvH2D*)Signal_BG_histsTObjArray.At(i))->Write("h_Muon_PZ_PT_SignalSelection_BG_NC");}
    else if(i==2){((PlotUtils::MnvH2D*)Signal_BG_histsTObjArray.At(i))->Write("h_Muon_PZ_PT_SignalSelection_BG_WrongSign");}
    else if(i==3){((PlotUtils::MnvH2D*)Signal_BG_histsTObjArray.At(i))->Write("h_Muon_PZ_PT_SignalSelection_BG_Neutral_2ndtrack");}



    i++;
  }

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
