#include "Make_CrossSection_Plots.h"

CrossSection_name_Map Generate_CrossSection_histsNames_withInteraction(MuonVar MuonVar_type, std::string playlist, bool isFUll);
CrossSection_name_Map Generate_CrossSection_histsNames_withInteraction_DISbreakdown_helium(MuonVar MuonVar_type, std::string playlist, bool isFUll);
CrossSection_name_Map Generate_CrossSection_histsNames_withInteraction_DISbreakdown(MuonVar MuonVar_type, std::string playlist, bool isFUll);
std::vector<ME_helium_Playlists> GetTrackerPlayListVector();
void MakeCrossSectionPlots_Interaction_Ratio(CrossSection_MnvH1D_Map CrossSection_map,CrossSection_MnvH1D_Map CrossSection_map_helium,
  std::string cross_section_units, std::string pdf,bool MakeXaxisLOG,bool doBinwidth ,
  MuonVar MuonVar, char *Playlist_name, double POT_Data, double POT_MC, Genie_Models Modelinputs);
///////////////////////////////////////////////////
///// Do all function
//////////////////////////////////////////////////

double FULL_POT_DATA_helium = 4.96441e+20;
double FULL_POT_MC_helium = 4.75655e+21;


double Tracker_MC_POT = 4.97204e+21;
double Tracker_Data_POT = 9.6612e+20;


double POT_Ratio = FULL_POT_DATA_helium / Tracker_Data_POT;

double POT_Ratio_MC = FULL_POT_DATA_helium / Tracker_MC_POT;


void Kin( bool &my_norm, bool &my_debug, bool &BinNorm , int &Print_Systematics ) {
TH1::AddDirectory(false);

const std::vector<ME_helium_Playlists> kPlayListVector_MC = GetPlayListVector();
int N_Error_groups;
if(Print_Systematics==2 || Print_Systematics == 1) {N_Error_groups=0;}
else if (Print_Systematics==0){N_Error_groups=7;}


TCanvas *can = new TCanvas("can");
MnvPlotter *mnv_plot = new MnvPlotter();
 char text_title_pdf1[2024];
 char text_title_pdf2[2024];
 char text_title_pdf3[2024];
 char text_title_pdf4[2024];
 char Latex_name[2024];
time_t now = time(0);
tm *ltm = localtime(&now);
 char timeset[2024];
 char timeset_nonstacks[2024];
 std::string SysError_printLabel = PrintLabel_Systematics(Print_Systematics);
 auto Playlist_names =  MakePlaylistString(kPlayListVector_MC);
 sprintf(timeset_nonstacks,"%i_%i_%i_%i_%s_%s", 1 + ltm->tm_mon,ltm->tm_mday, ltm->tm_hour,ltm->tm_min, SysError_printLabel.c_str(),Playlist_names.c_str());
 sprintf(timeset, "%i_%i_%i_%i", 1 + ltm->tm_mon,ltm->tm_mday, ltm->tm_hour,ltm->tm_min);

auto PlaylistME_CrossSection_Path = "/minerva/app/users/cnguyen/cmtuser/Minerva_v22r1p1Helium_GIT/NuCCSemiInclusiveHelium/Make_CrossSection/CrossSection.root";
auto PlaylistME_CrossSection_MasterAnaDevPath = "/minerva/app/users/cnguyen/cmtuser/Minerva_v22r1p1Helium_GIT/NuCCSemiInclusiveHelium/Make_CrossSection/CrossSection_MasterAnaDev.root";



bool is_mc=true;bool isNOT_mc=false;
std::string pdf_CV = string(text_title_pdf4);
bool Stats_only = false;


auto PlaylistME_CrossSection_GENIE_version_Path = "/minerva/app/users/cnguyen/cmtuser/Minerva_v22r1p1Helium_GIT/NuCCSemiInclusiveHelium/Make_CrossSection/CrossSection_MK.root";

auto TrackerME_playlist_vector = GetTrackerPlayListVector();
/////////////
// Full Playlist
/////////////
auto PlaylistME_1P_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/MasterAnaDev_minervame1P_RECO_MC_StatsONLYErrors_Fid.root";
auto PlaylistME_1C_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/MasterAnaDev_minervame1C_RECO_MC_StatsONLYErrors_Fid.root";
auto PlaylistME_1D_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/MasterAnaDev_minervame1D_RECO_MC_StatsONLYErrors_Fid.root";
auto PlaylistME_1F_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/MasterAnaDev_minervame1F_RECO_MC_StatsONLYErrors_Fid.root";
auto PlaylistME_1E_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/MasterAnaDev_minervame1E_RECO_MC_StatsONLYErrors_Fid.root";
auto PlaylistME_1G_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/MasterAnaDev_minervame1G_RECO_MC_StatsONLYErrors_Fid.root";
auto PlaylistME_1A_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/MasterAnaDev_minervame1A_RECO_MC_StatsONLYErrors_Fid.root";
auto PlaylistME_1L_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/MasterAnaDev_minervame1L_RECO_MC_StatsONLYErrors_Fid.root";
auto PlaylistME_1M_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/MasterAnaDev_minervame1M_RECO_MC_StatsONLYErrors_Fid.root";
auto PlaylistME_1N_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/MasterAnaDev_minervame1N_RECO_MC_StatsONLYErrors_Fid.root";
auto PlaylistME_1B_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/MasterAnaDev_minervame1B_RECO_MC_StatsONLYErrors_Fid.root";
auto PlaylistME_1O_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/MasterAnaDev_minervame1O_RECO_MC_StatsONLYErrors_Fid.root";




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
//auto PlaylistME_1C_MC_TRUTH_test = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/Histograms_TRUTH_MasterAnaDev_minervame1O_TRUTH_All_SysErrorsOn_Fid.root";
ME_playlist_RootPathMAP MAP_RootPath_Tracker_MC_RECO;
ME_playlist_RootPathMAP MAP_RootPath_Tracker_MC_TRUTH;
ME_playlist_RootPathMAP MAP_RootPath_Tracker_DATA;

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

//MAP_RootPath_Tracker_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(0), PlaylistME_1P_MC_TRUTH_path));
//MAP_RootPath_Tracker_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(1), PlaylistME_1C_MC_TRUTH_path));
//MAP_RootPath_Tracker_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(2), PlaylistME_1D_MC_TRUTH_path));
//MAP_RootPath_Tracker_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(3), PlaylistME_1F_MC_TRUTH_path));
//MAP_RootPath_Tracker_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(4), PlaylistME_1E_MC_TRUTH_path));
//MAP_RootPath_Tracker_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(5), PlaylistME_1G_MC_TRUTH_path));
//MAP_RootPath_Tracker_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(6), PlaylistME_1A_MC_TRUTH_path));
//MAP_RootPath_Tracker_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(7), PlaylistME_1L_MC_TRUTH_path));
//MAP_RootPath_Tracker_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(8), PlaylistME_1M_MC_TRUTH_path));
//MAP_RootPath_Tracker_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(9), PlaylistME_1N_MC_TRUTH_path));
//MAP_RootPath_Tracker_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(10), PlaylistME_1B_MC_TRUTH_path));
//MAP_RootPath_Tracker_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(11), PlaylistME_1O_MC_TRUTH_path));

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
////
///////////////////////////







/////////////////////////////////////////////////////
// Empty
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

//TFile *TFile_ME1C_MC = new TFile(PlaylistME_1C_MC_TRUTH_test);

//TFile *TFile_ME1P_MC_TRUTH = new TFile(PlaylistME_1P_MC_TRUTH_path);
//TFile *TFile_ME1C_MC_TRUTH = new TFile(PlaylistME_1C_MC_TRUTH_path);
//TFile *TFile_ME1D_MC_TRUTH = new TFile(PlaylistME_1D_MC_TRUTH_path);
//TFile *TFile_ME1E_MC_TRUTH = new TFile(PlaylistME_1E_MC_TRUTH_path);
//TFile *TFile_ME1F_MC_TRUTH = new TFile(PlaylistME_1F_MC_TRUTH_path);
//TFile *TFile_ME1G_MC_TRUTH = new TFile(PlaylistME_1G_MC_TRUTH_path);
//TFile *TFile_ME1A_MC_TRUTH = new TFile(PlaylistME_1A_MC_TRUTH_path);
//TFile *TFile_ME1L_MC_TRUTH = new TFile(PlaylistME_1L_MC_TRUTH_path);
//TFile *TFile_ME1M_MC_TRUTH = new TFile(PlaylistME_1M_MC_TRUTH_path);
//TFile *TFile_ME1N_MC_TRUTH = new TFile(PlaylistME_1N_MC_TRUTH_path);
//TFile *TFile_ME1B_MC_TRUTH = new TFile(PlaylistME_1B_MC_TRUTH_path);
//TFile *TFile_ME1O_MC_TRUTH = new TFile(PlaylistME_1O_MC_TRUTH_path);

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
auto PlaylistME_Flux_helium = "/minerva/data/users/cnguyen/ME_Flux/flux_helium_Full.root";

auto PlaylistME_Flux_helium_slice1 = "/minerva/data/users/cnguyen/ME_Flux/flux_helium_Slice1.root";
auto PlaylistME_Flux_helium_slice2 = "/minerva/data/users/cnguyen/ME_Flux/flux_helium_Slice2.root";
auto PlaylistME_Flux_helium_slice3 = "/minerva/data/users/cnguyen/ME_Flux/flux_helium_Slice3.root";
auto PlaylistME_Flux_helium_slice4 = "/minerva/data/users/cnguyen/ME_Flux/flux_helium_Slice4.root";

auto PlaylistME_Flux_helium_daisy0 = "/minerva/data/users/cnguyen/ME_Flux/flux_helium_Daisy0.root";
auto PlaylistME_Flux_helium_daisy1 = "/minerva/data/users/cnguyen/ME_Flux/flux_helium_Daisy1.root";
auto PlaylistME_Flux_helium_daisy2 = "/minerva/data/users/cnguyen/ME_Flux/flux_helium_Daisy2.root";
auto PlaylistME_Flux_helium_daisy3 = "/minerva/data/users/cnguyen/ME_Flux/flux_helium_Daisy3.root";
auto PlaylistME_Flux_helium_daisy4 = "/minerva/data/users/cnguyen/ME_Flux/flux_helium_Daisy4.root";
auto PlaylistME_Flux_helium_daisy5 = "/minerva/data/users/cnguyen/ME_Flux/flux_helium_Daisy5.root";
auto PlaylistME_Flux_helium_daisy6 = "/minerva/data/users/cnguyen/ME_Flux/flux_helium_Daisy6.root";
auto PlaylistME_Flux_helium_daisy7 = "/minerva/data/users/cnguyen/ME_Flux/flux_helium_Daisy7.root";
auto PlaylistME_Flux_helium_daisy8 = "/minerva/data/users/cnguyen/ME_Flux/flux_helium_Daisy8.root";
auto PlaylistME_Flux_helium_daisy9 = "/minerva/data/users/cnguyen/ME_Flux/flux_helium_Daisy9.root";
auto PlaylistME_Flux_helium_daisy10 = "/minerva/data/users/cnguyen/ME_Flux/flux_helium_Daisy10.root";
auto PlaylistME_Flux_helium_daisy11 = "/minerva/data/users/cnguyen/ME_Flux/flux_helium_Daisy11.root";


//simple_flux_tracker_tracker.root
auto PlaylistME_Flux_tracker = "../../MATFluxAndReweightFiles/flux_daisy/neutrinos/targets_2345_jointNueIMD/flux_with_errors/flux_tracker.root";// "/minerva/data/users/cnguyen/ME_Flux/flux_tracker_Full_Tracker.root";
//auto PlaylistME_Flux_tracker = "/minerva/data/users/cnguyen/ME_Flux/flux_tracker_Full_Tracker.root";
auto PlaylistME_Flux_tracker_slice1 = "/minerva/data/users/cnguyen/ME_Flux/flux_helium_MasterAnaDev_Slice1.root";
auto PlaylistME_Flux_tracker_slice2 = "/minerva/data/users/cnguyen/ME_Flux/flux_helium_MasterAnaDev_Slice2.root";
auto PlaylistME_Flux_tracker_slice3 = "/minerva/data/users/cnguyen/ME_Flux/flux_helium_MasterAnaDev_Slice3.root";
auto PlaylistME_Flux_tracker_slice4 = "/minerva/data/users/cnguyen/ME_Flux/flux_helium_MasterAnaDev_Slice4.root";

TFile *TFile_Flux_helium = new TFile(PlaylistME_Flux_helium);
TFile *TFile_Flux_helium_slice1 = new TFile(PlaylistME_Flux_helium_slice1);
TFile *TFile_Flux_helium_slice2 = new TFile(PlaylistME_Flux_helium_slice2);
TFile *TFile_Flux_helium_slice3 = new TFile(PlaylistME_Flux_helium_slice3);
TFile *TFile_Flux_helium_slice4 = new TFile(PlaylistME_Flux_helium_slice4);


TFile *TFile_Flux_helium_daisy0 = new TFile(PlaylistME_Flux_helium_daisy0);
TFile *TFile_Flux_helium_daisy1 = new TFile(PlaylistME_Flux_helium_daisy1);
TFile *TFile_Flux_helium_daisy2 = new TFile(PlaylistME_Flux_helium_daisy2);
TFile *TFile_Flux_helium_daisy3 = new TFile(PlaylistME_Flux_helium_daisy3);
TFile *TFile_Flux_helium_daisy4 = new TFile(PlaylistME_Flux_helium_daisy4);
TFile *TFile_Flux_helium_daisy5 = new TFile(PlaylistME_Flux_helium_daisy5);
TFile *TFile_Flux_helium_daisy6 = new TFile(PlaylistME_Flux_helium_daisy6);
TFile *TFile_Flux_helium_daisy7 = new TFile(PlaylistME_Flux_helium_daisy7);
TFile *TFile_Flux_helium_daisy8 = new TFile(PlaylistME_Flux_helium_daisy8);
TFile *TFile_Flux_helium_daisy9 = new TFile(PlaylistME_Flux_helium_daisy9);
TFile *TFile_Flux_helium_daisy10 = new TFile(PlaylistME_Flux_helium_daisy10);
TFile *TFile_Flux_helium_daisy11 = new TFile(PlaylistME_Flux_helium_daisy11);

auto Flux_helum_daisy0 = Get1DHist(*TFile_Flux_helium_daisy0,"flux");
auto Flux_helum_daisy1 = Get1DHist(*TFile_Flux_helium_daisy1,"flux");
auto Flux_helum_daisy2 = Get1DHist(*TFile_Flux_helium_daisy2,"flux");
auto Flux_helum_daisy3 = Get1DHist(*TFile_Flux_helium_daisy3,"flux");
auto Flux_helum_daisy4 = Get1DHist(*TFile_Flux_helium_daisy4,"flux");
auto Flux_helum_daisy5 = Get1DHist(*TFile_Flux_helium_daisy5,"flux");
auto Flux_helum_daisy6 = Get1DHist(*TFile_Flux_helium_daisy6,"flux");
auto Flux_helum_daisy7 = Get1DHist(*TFile_Flux_helium_daisy7,"flux");
auto Flux_helum_daisy8 = Get1DHist(*TFile_Flux_helium_daisy8,"flux");
auto Flux_helum_daisy9 = Get1DHist(*TFile_Flux_helium_daisy9,"flux");
auto Flux_helum_daisy10 = Get1DHist(*TFile_Flux_helium_daisy10,"flux");
auto Flux_helum_daisy11 = Get1DHist(*TFile_Flux_helium_daisy11,"flux");

auto Flux_helum = Get1DHist(*TFile_Flux_helium,"flux");
auto Flux_helum_th1d = GetTH1DHist(*TFile_Flux_helium,"flux");
auto Flux_helum_slice1 = Get1DHist(*TFile_Flux_helium_slice1,"flux");
auto Flux_helum_slice2 = Get1DHist(*TFile_Flux_helium_slice2,"flux");
auto Flux_helum_slice3 = Get1DHist(*TFile_Flux_helium_slice3,"flux");
auto Flux_helum_slice4 = Get1DHist(*TFile_Flux_helium_slice4,"flux");


//Flux_helum_slice1->Divide(Flux_helum_slice1,Flux_helum_th1d);
//Flux_helum_slice2->Divide(Flux_helum_slice1,Flux_helum_th1d);
//Flux_helum_slice3->Divide(Flux_helum_slice1,Flux_helum_th1d);
//Flux_helum_slice4->Divide(Flux_helum_slice1,Flux_helum_th1d);
//Flux_helum_th1d->Divide(Flux_helum_th1d,Flux_helum_th1d);

TFile *TFile_Flux_Tracker = new TFile(PlaylistME_Flux_tracker);
TFile *TFile_Flux_Tracker_slice1 = new TFile(PlaylistME_Flux_tracker_slice1);
TFile *TFile_Flux_Tracker_slice2 = new TFile(PlaylistME_Flux_tracker_slice2);
TFile *TFile_Flux_Tracker_slice3 = new TFile(PlaylistME_Flux_tracker_slice3);
TFile *TFile_Flux_Tracker_slice4 = new TFile(PlaylistME_Flux_tracker_slice4);

auto Flux_Tracker = Get1DHist(*TFile_Flux_Tracker,"flux");
auto Flux_Tracker_slice1 = Get1DHist(*TFile_Flux_Tracker_slice1,"flux");
auto Flux_Tracker_slice2 = Get1DHist(*TFile_Flux_Tracker_slice2,"flux");
auto Flux_Tracker_slice3 = Get1DHist(*TFile_Flux_Tracker_slice3,"flux");
auto Flux_Tracker_slice4 = Get1DHist(*TFile_Flux_Tracker_slice4,"flux");



ME_playlist_TFileMAP TrackerTFile_Map_MC_RECO;
ME_playlist_TFileMAP TrackerTFile_Map_MC_TRUTH;
ME_playlist_TFileMAP TrackerTFile_Map_DATA;

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


//TrackerTFile_Map_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(0),TFile_ME1P_MC_TRUTH));
//TrackerTFile_Map_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(1),TFile_ME1C_MC_TRUTH));
//TrackerTFile_Map_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(2),TFile_ME1D_MC_TRUTH));
//TrackerTFile_Map_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(3),TFile_ME1F_MC_TRUTH));
//TrackerTFile_Map_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(4),TFile_ME1E_MC_TRUTH));
//TrackerTFile_Map_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(5),TFile_ME1G_MC_TRUTH));
//TrackerTFile_Map_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(6),TFile_ME1A_MC_TRUTH));
//TrackerTFile_Map_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(7),TFile_ME1L_MC_TRUTH));
//TrackerTFile_Map_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(8),TFile_ME1M_MC_TRUTH));
//TrackerTFile_Map_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(9),TFile_ME1N_MC_TRUTH));
//TrackerTFile_Map_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(10),TFile_ME1B_MC_TRUTH));
//TrackerTFile_Map_MC_TRUTH.insert(std::make_pair(TrackerME_playlist_vector.at(11),TFile_ME1O_MC_TRUTH));

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





//Different Models





sprintf(text_title_pdf1, "PLOTS_%s_FluxFits_tracker_reduced.pdf(","" );
can -> Print(text_title_pdf1);
sprintf(text_title_pdf2, "PLOTS_%s_FluxFits_tracker_reduced.pdf","" );
sprintf(text_title_pdf3, "PLOTS_%s_FluxFits_tracker_reduced.pdf)","" );
sprintf(text_title_pdf4, "PLOTS_%s_FluxFits_tracker_reduced","" );
 pdf_CV = string(text_title_pdf4);

  std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;
  std::cout<< "  Ploting 1D Cross Section "<< std::endl;
  std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;




std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~       Starting Plotter: Kinematic Plots         ~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

TFile *TFile_CrossSection_tracker = new TFile(PlaylistME_CrossSection_MasterAnaDevPath);
TFile *TFile_CrossSection_helium = new TFile(PlaylistME_CrossSection_Path);
auto muon_vector = GetMUONVaribles_Total();
bool isFull = true;
bool isEmpty = false;
bool DoBinWidthNorm = true;
bool DontBinWidthNorm = false;
bool Makelog = false;
//auto Map_MuonE_Full_hist = Generate_CrossSection_Hist_Map(*TFile_CrossSection, muonE_full_names);
//auto Map_MuonE_Full_hist_helium = Generate_CrossSection_Hist_Map(*TFile_CrossSection_helium, muonE_helium_names);
//auto MuonE_Mig = Get2DHist(*TFile_CrossSection, muonE_full_names[mvnreponse_Mig]);
std::cout<<"Making Migration"<< std::endl;
//auto PlaylistME_CrossSection_MasterAnaDevPath = "/minerva/app/users/cnguyen/cmtuser/Minerva_v22r1p1Helium_GIT/NuCCSemiInclusiveHelium/Make_CrossSection/CrossSection_MasterAnaDev.root";

auto PlaylistME_CrossSection_fluxtracker_vertexX = "/minerva/data/users/cnguyen/ME_Flux/flux_tracker_tracker_2d_vertexX.root";
auto PlaylistME_CrossSection_fluxtracker_vertexY = "/minerva/data/users/cnguyen/ME_Flux/flux_tracker_tracker_2d_vertexY.root";
TFile *TFile_Flux_tracker_vertexX = new TFile(PlaylistME_CrossSection_fluxtracker_vertexX);
TFile *TFile_Flux_tracker_vertexY = new TFile(PlaylistME_CrossSection_fluxtracker_vertexY);




//auto EuvsVertexX = Get2DHist(*TFile_CrossSection_tracker,"h2d_Enu_TRUE_vertex_X_reduced");
//auto EuvsVertexY = Get2DHist(*TFile_CrossSection_tracker,"h2d_Enu_TRUE_vertex_Y_reduced");

auto EuvsVertexX = Get2DHist(*TFile_Flux_tracker_vertexX,"flux_2d");
auto EuvsVertexY = Get2DHist(*TFile_Flux_tracker_vertexY,"flux_2d");


auto EuvsVertexX_rate = Get2DHist(*TFile_CrossSection_tracker,"h2d_Enu_TRUE_vertex_X_reduced1");
auto EuvsVertexY_rate = Get2DHist(*TFile_CrossSection_tracker,"h2d_Enu_TRUE_vertex_Y_reduced1");



Draw2DHist(EuvsVertexX, "E_{#nu} [GeV]", "Vertex X [mm]", "#nu / m^2 / POT / GeV" , "" , text_title_pdf2, can,mnv_plot);
Draw2DHist(EuvsVertexY, "E_{#nu} [GeV]", "Vertex Y [mm]", "#nu / m^2 / POT / GeV" , "" , text_title_pdf2, can,mnv_plot);

Draw2DHist(EuvsVertexX_rate, "E_{#nu} [GeV]", "Vertex X [mm]", "NEvent" , "" , text_title_pdf2, can,mnv_plot);
Draw2DHist(EuvsVertexY_rate, "E_{#nu} [GeV]", "Vertex Y [mm]", "NEvent" , "" , text_title_pdf2, can,mnv_plot);




//TH2D EuvsVertexX_th1d = EuvsVertexX->GetCVHistoWithStatError();
//TH2D EuvsVertexY_th1d = EuvsVertexY->GetCVHistoWithStatError();
//
//TH2D *histpointerA = &EuvsVertexX_th1d;
//TH2D *histpointerB = &EuvsVertexY_th1d;

//std::vector<double> para_vector{12274.3,6.22405,1.83853,19.8097,661.243,9237.28,2.95147,10.8605,513.395}; // got from fit
//std::vector<double> wgt_error_vector{2.84761,0.000253499,0.000194692,0.161912,0.209654,2.19916,0.000401035,0.095175,0.0899211}; // got from fit
std::vector<TGraph*> outputTGraphs;
double chi2= 99 ;// = 435226;
std::vector<double> para_vector;
std::vector<double> wgt_error_vector;

//int EuvsVertexX_N_Xbins  = EuvsVertexX_th1d.GetNbinsX();
//int EuvsVertexX_N_Ybins  = EuvsVertexX_th1d.GetNbinsY();
//
//int EuvsVertexY_N_Xbins  = EuvsVertexY_th1d.GetNbinsX();
//int EuvsVertexY_N_Ybins  = EuvsVertexY_th1d.GetNbinsY();
//
//double ndf = EuvsVertexX_N_Xbins * EuvsVertexX_N_Ybins + EuvsVertexY_N_Xbins * EuvsVertexY_N_Ybins;
//double ndf_fit = ndf - 9;
//Fit2Dhist(histpointerA, histpointerB, para_vector, wgt_error_vector, chi2, outputTGraphs );
//int count=0;
//std::ofstream myfile;
//
//myfile.open("GaussianFit_joint_tracker_reduced.txt");
//for(int i=0; i < para_vector.size(); i++  ){
//  myfile <<"index: "<< count<< "pars : " <<  para_vector.at(i) <<"   Error :" <<  wgt_error_vector.at(i)<< std::endl;
//count++;
//}

/*
 Draw2DHist_warpFit2DGaussian(EuvsVertexX, "E_{#nu} [GeV]","Vertex X [mm]", chi2, ndf_fit,
  para_vector.at(0),para_vector.at(1),para_vector.at(2),para_vector.at(3),para_vector.at(4),
   wgt_error_vector.at(0),wgt_error_vector.at(1),wgt_error_vector.at(2),wgt_error_vector.at(3),wgt_error_vector.at(4),
    "Joint Fit Vertex X [Tracker]", text_title_pdf2, can,mnv_plot);

    Draw2DHist_warpFit2DGaussian(EuvsVertexY, "E_{#nu} [GeV]","Vertex Y [mm]", chi2, ndf_fit,
     para_vector.at(5),para_vector.at(1),para_vector.at(6),para_vector.at(7),para_vector.at(8),
      wgt_error_vector.at(5),wgt_error_vector.at(1),wgt_error_vector.at(6),wgt_error_vector.at(7),wgt_error_vector.at(8),
       "Joint Fit Vertex Y [Tracker] ", text_title_pdf2, can,mnv_plot);

       auto outFile = TFile::Open("CrossSection_FluxFits_tracker_reduced.root", "RECREATE");
       ////
       outFile->cd(); // make sure that we will write to this ROOT file g->Write("MyGraph");
       outputTGraphs.at(0)->Write("MyGraph_fitContour_1sigma_par_3_7");
       outputTGraphs.at(1)->Write("MyGraph_fitContour_1sigma_par_1_3");
       outputTGraphs.at(2)->Write("MyGraph_fitContour_1sigma_par_1_7");
       outputTGraphs.at(3)->Write("MyGraph_fitContour_2sigma_par_3_7");
       outputTGraphs.at(4)->Write("MyGraph_fitContour_2sigma_par_1_3");
       outputTGraphs.at(5)->Write("MyGraph_fitContour_2sigma_par_1_7");
       outFile->Close();



       TFile* f0 = new TFile("CrossSection_FluxFits_tracker_reduced.root");
       TGraph* MyGraph_fitContour_1sigma_par_3_7 = (TGraph*)f0->Get("MyGraph_fitContour_1sigma_par_3_7");
       TGraph* MyGraph_fitContour_1sigma_par_1_3 = (TGraph*)f0->Get("MyGraph_fitContour_1sigma_par_1_3");
       TGraph* MyGraph_fitContour_1sigma_par_1_7 = (TGraph*)f0->Get("MyGraph_fitContour_1sigma_par_1_7");
       TGraph* MyGraph_fitContour_2sigma_par_3_7 = (TGraph*)f0->Get("MyGraph_fitContour_2sigma_par_3_7");
       TGraph* MyGraph_fitContour_2sigma_par_1_3 = (TGraph*)f0->Get("MyGraph_fitContour_2sigma_par_1_3");
       TGraph* MyGraph_fitContour_2sigma_par_1_7 = (TGraph*)f0->Get("MyGraph_fitContour_2sigma_par_1_7");

        DrawTGraph(MyGraph_fitContour_1sigma_par_3_7, MyGraph_fitContour_2sigma_par_3_7, "Beam Postion X [mm]", "Beam Postion Y [mm]",
                " [Tracker]Fit Contour of X vs Y position Beam Peak","1#sigma","2#sigma",
                text_title_pdf2, can,mnv_plot,false,false,true );

        DrawTGraph(MyGraph_fitContour_1sigma_par_1_3, MyGraph_fitContour_2sigma_par_1_3, "E_{#nu} [GeV]", "Beam Postion X [mm]",
                        " [Tracker] Fit Contour of X vs E_{#nu} Beam Peak","1#sigma","2#sigma",
                        text_title_pdf2, can,mnv_plot,false,false,true );

        DrawTGraph(MyGraph_fitContour_1sigma_par_1_7, MyGraph_fitContour_2sigma_par_1_7, "E_{#nu} [GeV]", "Beam Postion Y [mm]",
                                        " [Tracker] Fit Contour of Y vs E_{#nu}","1#sigma","2#sigma",
                                        text_title_pdf2, can,mnv_plot,false,false,true );
*/

std::vector<double> Mean_Y_EuvsVertexX = calculateMeanValues(EuvsVertexX);
std::vector<double> Mean_Y_EuvsVertexY = calculateMeanValues(EuvsVertexY);
std::vector<double> Bins_EuvsVertexX = extractXBins(EuvsVertexX);

std::vector<double> Mean_Y_EuvsVertexX_rate = calculateMeanValues(EuvsVertexX_rate);
std::vector<double> Mean_Y_EuvsVertexY_rate = calculateMeanValues(EuvsVertexY_rate);
std::vector<double> Bins_EuvsVertexX_rate = extractXBins(EuvsVertexX_rate);


removeFirstNElements(Mean_Y_EuvsVertexX,15);
removeFirstNElements(Mean_Y_EuvsVertexY,15);
removeFirstNElements(Bins_EuvsVertexX,15);

removeFirstNElements(Mean_Y_EuvsVertexX_rate,15);
removeFirstNElements(Mean_Y_EuvsVertexY_rate,15);
removeFirstNElements(Bins_EuvsVertexX_rate,15);


TGraph *g_TGraph_EuvsVertexY = createTGraph(Bins_EuvsVertexX,Mean_Y_EuvsVertexY);
TGraph *g_TGraph_EuvsVertexX =createTGraph(Bins_EuvsVertexX,Mean_Y_EuvsVertexX);

TGraph *g_TGraph_EuvsVertexY_rate = createTGraph(Bins_EuvsVertexX_rate,Mean_Y_EuvsVertexY_rate);

TGraph *g_TGraph_EuvsVertexX_rate =createTGraph(Bins_EuvsVertexX_rate,Mean_Y_EuvsVertexX_rate);


//DrawTGraph(g_TGraph_EuvsVertexX, "#nu / m^2 / POT / GeV","Mean Vertex X",
//           "Mean Values of Vertex X for Helium for Flux", "", text_title_pdf2, can,mnv_plot, false, false );

//std::vector<double> Mean_Y_EuvsVertexY = calculateMeanValues(EuvsVertexY);

//TGraph *g_TGraph_EuvsVertexY =createTGraph(Bins_EuvsVertexX ,Mean_Y_EuvsVertexY);

//TGraph *g_TGraph_EuvsVertexY = MakeTGraph_NOERRORS_from_Vectors(Mean_Y_EuvsVertexY,Bins_EuvsVertexX);
DrawTGraph(g_TGraph_EuvsVertexY, "E_{#nu}","Mean Vertex Y",
"Mean Values of Vertex Y for Tracker for Flux", "", text_title_pdf2, can,mnv_plot, false, false );

DrawTGraph_GaussianFit(g_TGraph_EuvsVertexY, "E_{#nu}","Mean Vertex Y",
"Mean Values of Vertex Y for Tracker for Flux", "", text_title_pdf2, can,mnv_plot, false, false,4.5,12 );


DrawTGraph(g_TGraph_EuvsVertexX, "E_{#nu}","Mean Vertex X",
"Mean Values of Vertex X for Tracker for Flux", "", text_title_pdf2, can,mnv_plot, false, false );

DrawTGraph_GaussianFit(g_TGraph_EuvsVertexX, "E_{#nu}","Mean Vertex X",
"Mean Values of Vertex Y for Tracker for Flux", "", text_title_pdf2, can,mnv_plot, false, false,4.5,12 );
///////////////////
DrawTGraph(g_TGraph_EuvsVertexY_rate, "E_{#nu}","Mean Vertex Y",
"Mean Values of Vertex Y for Tracker for Flux [Rate]", "", text_title_pdf2, can,mnv_plot, false, false );

DrawTGraph_GaussianFit(g_TGraph_EuvsVertexY_rate, "E_{#nu}","Mean Vertex Y",
"Mean Values of Vertex Y for Tracker for Flux [Rate]", "", text_title_pdf2, can,mnv_plot, false, false,4.5,12 );


DrawTGraph(g_TGraph_EuvsVertexX_rate, "E_{#nu}","Mean Vertex X",
"Mean Values of Vertex X for Tracker for Flux [Rate]", "", text_title_pdf2, can,mnv_plot, false, false );

DrawTGraph_GaussianFit(g_TGraph_EuvsVertexX_rate, "E_{#nu}","Mean Vertex X",
"Mean Values of Vertex Y for Tracker for Flux [Rate]", "", text_title_pdf2, can,mnv_plot, false, false,4.5,12 );







//std::cout<< "chi = "<< chi2<< "ndf = "<< ndf << " ndf_fit = "<< ndf_fit<<std::endl;
//
//std::cout<< "chi/ndf = "<< chi2 / ndf << "  chi/ndf_fit = "<< chi2 / ndf_fit <<std::endl;





//auto EuvsVertexX_reduce = Get2DHist(*TFile_CrossSection_helium,"h2d_Enu_TRUE_vertex_X_reduced");
//auto EuvsVertexY_reduce = Get2DHist(*TFile_CrossSection_helium,"h2d_Enu_TRUE_vertex_Y_reduced");


  //Draw2DHist_histWithTProfile(EuvsVertexX, "", "E_{#nu} ","Vertex X [mm]",text_title_pdf2, can, mnv_plot);
  //Draw2DHist_histWithTProfile(EuvsVertexY, "", "E_{#nu} ","Vertex Y [mm]",text_title_pdf2, can, mnv_plot);

  //Draw2DHist_histWithTProfile(EuvsVertexX_reduce, "", "E_{#nu} ","Vertex X [mm]",text_title_pdf2, can, mnv_plot);
  //Draw2DHist_histWithTProfile(EuvsVertexY_reduce, "", "E_{#nu} ","Vertex Y [mm]",text_title_pdf2, can, mnv_plot);

  //Draw2DHist_histWithTProfile_Y(EuvsVertexX, "", "E_{#nu} ","Vertex X [mm]",text_title_pdf2, can, mnv_plot);
  //Draw2DHist_histWithTProfile_Y(EuvsVertexY, "", "E_{#nu} ","Vertex Y [mm]",text_title_pdf2, can, mnv_plot);

  //Draw2DHist_histWithTProfile_Y(EuvsVertexX_reduce, "", "E_{#nu} ","Vertex X [mm]",text_title_pdf2, can, mnv_plot);
  //Draw2DHist_histWithTProfile_Y(EuvsVertexY_reduce, "", "E_{#nu} ","Vertex Y [mm]",text_title_pdf2, can, mnv_plot);

  //Draw2DHist_warpFit2DGaussian(EuvsVertexX, "E_{#nu}", "Vertex X [mm]",  "Gaussian Fit", text_title_pdf2, can, mnv_plot)//;

  //Draw2DHist_warpFit2DGaussian(EuvsVertexY, "E_{#nu} ", "Vertex Y [mm]","Gaussian Fit", text_title_pdf2, can, mnv_plot);
  //double areaCX = EuvsVertexX->Integral();
  //double areaCY = EuvsVertexY->Integral();
  //EuvsVertexX->Scale(1.0/areaCX);
  //EuvsVertexY->Scale(1.0/areaCY);

  //Draw2DHist_warpFit2DGaussian(EuvsVertexX, "E_{#nu}", "Vertex X [mm]",  "Gaussian Fit [AreaNorm]", text_title_pdf2, can, mnv_plot);

  //Draw2DHist_warpFit2DGaussian(EuvsVertexY, "E_{#nu} ", "Vertex Y [mm]", "Gaussian Fit [AreaNorm]", text_title_pdf2, can, mnv_plot);
  can -> Print(text_title_pdf3);
  can->Close();













std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;

std::cout<< " Done with Muon Plots"<< std::endl;

std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;


//sprintf(Latex_name, "PLOTS_%s_Muon_Latex_CV_and_Stacks", timeset);
 //input_Latex_name = Latex_name;



   std::cout << "lastline" << std::endl;

   return;

}



 int main() {

bool my_norm;
std::cout << "Which Normalization?  (0 = POT, 1 = relative equal areas) " << std::endl;
//std::cin >> my_norm;
 my_norm=true;
std::cout << std::boolalpha << my_norm << std::endl;

bool my_BinNormilzed;
std::cout << "Do you want to Bin Width Normlize?  (0 = yes, 1 = no) " << std::endl;
//std::cin >> my_BinNormilzed;
my_BinNormilzed= true;
std::cout << std::boolalpha << my_norm << std::endl;

int my_Print_Systmatics=1;
std::cout << "Print Error Systmatics?  [ 0 = Total and Groups Systemtics Errors ,  1 = Total Systematic Errors , 2 = none ]" << std::endl;
//std::cin >> my_Print_Systmatics;
std::cout << "Print Error Systmatics: " << my_Print_Systmatics << std::endl;


bool my_debug = true;
std::cout << "Run in Debug Mode? (0 = NO, 1 = YES) " << std::endl;
//std::cin >> my_debug;
std::cout << std::boolalpha << my_debug << std::endl;


Kin(my_norm, my_debug, my_BinNormilzed, my_Print_Systmatics);

std::cout<< "Done with Program"<<std::endl;

return 0;

}


std::vector<ME_helium_Playlists> GetPlayListVector() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ME_helium_Playlists> Playlist;


Playlist.push_back(kME1F);
//Playlist.push_back(kME1P);
  Playlist.push_back(kME1G);
  //Playlist.push_back(kME1A);
  //Playlist.push_back(kME1C);
  //Playlist.push_back(kME1D);

  return Playlist;
//#endif
}



/////////////////////////////////////////////
std::vector<MuonVar> GetMUONVaribles_Total() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<MuonVar> MuonVars;
  MuonVars.push_back(kE);
  MuonVars.push_back(kP_Z);
  MuonVars.push_back(kP_T);

  MuonVars.push_back(kAngleWRTB);


  return MuonVars;
//#endif
}

CrossSection_name_Map Generate_CrossSection_histsNames(MuonVar MuonVar_type, std::string playlist, bool isFUll){

  CrossSection_name_Map Name_Map;

  if(isFUll==true)
  {
    auto hist_name = GetMuonVarHistName(MuonVar_type);
    std::string hist1_name = hist_name + "_" + playlist + "_Data_Signal";
    Name_Map.insert(std::make_pair(Data_signal, hist1_name));

    std::string hist1_name_pot = hist_name + "_" + playlist + "_potnorm_Data_Signal";
    Name_Map.insert(std::make_pair(Data_signal_potNorm, hist1_name_pot));

    std::string hist1_name_pot_full_empty = hist_name + "_Full_sub_Empty_potnorm_Data_Signal";
    Name_Map.insert(std::make_pair(Data_signal_BGsub_potNorm, hist1_name_pot_full_empty));

    std::string unfolded_name = hist_name + "_unfolded_data";
    Name_Map.insert(std::make_pair(Data_signal_unfolded, unfolded_name));

    std::string eff_Corrected_name = hist_name +"_unfolded_data_effcorrected";
    Name_Map.insert(std::make_pair(Data_signal_unfolded_effcorrected, eff_Corrected_name));

    std::string unfolded_crosssection_name = hist_name + "_CrossSection_data_unfolded";
    Name_Map.insert(std::make_pair(Data_crosssection, unfolded_crosssection_name));

    std::string truecross_name = hist_name + "_TrueCrossSection";
    Name_Map.insert(std::make_pair(True_crosssection, truecross_name));

    std::string nom_Eff_name = hist_name+ "_" + playlist + "_effNum";
    Name_Map.insert(std::make_pair(nom_Eff, nom_Eff_name));

    std::string dom_Eff_name = hist_name + "_" + playlist + "_effDom";
    Name_Map.insert(std::make_pair(dom_Eff, dom_Eff_name));

    std::string eff_name = hist_name + "_efficiency";
    Name_Map.insert(std::make_pair(Eff, eff_name));


   std::string TRUEcrosssection_elastic = hist_name + "_efficiency";

  }

  else if(isFUll==false){
    auto hist_name = GetMuonVarHistName(MuonVar_type);
    std::string hist1_name = hist_name + "_" + playlist;
    Name_Map.insert(std::make_pair(Data_BG, hist1_name));

    std::string hist1_name_pot = hist1_name + "_potnorm";
    Name_Map.insert(std::make_pair(Data_BG_potNorm, hist1_name_pot));
  }

  return Name_Map;

}

CrossSection_name_Map Generate_CrossSection_histsNames_withInteraction(MuonVar MuonVar_type, std::string playlist, bool isFUll){

  CrossSection_name_Map Name_Map;

  if(isFUll==true)
  {
    auto hist_name = GetMuonVarHistName(MuonVar_type);
    std::string hist1_name = hist_name + "_" + playlist + "_Data_Signal";
    Name_Map.insert(std::make_pair(Data_signal, hist1_name));

    std::string hist1_name_pot = hist_name + "_" + playlist + "_potnorm_Data_Signal";
    Name_Map.insert(std::make_pair(Data_signal_potNorm, hist1_name_pot));

    std::string hist1_name_pot_full_empty = hist_name + "_Full_sub_Empty_potnorm_Data_Signal";
    Name_Map.insert(std::make_pair(Data_signal_BGsub_potNorm, hist1_name_pot_full_empty));

    std::string unfolded_name = hist_name + "_unfolded_data";
    Name_Map.insert(std::make_pair(Data_signal_unfolded, unfolded_name));

    std::string eff_Corrected_name = hist_name +"_unfolded_data_effcorrected";
    Name_Map.insert(std::make_pair(Data_signal_unfolded_effcorrected, eff_Corrected_name));

    std::string unfolded_crosssection_name = hist_name + "_CrossSection_data_unfolded";
    Name_Map.insert(std::make_pair(Data_crosssection, unfolded_crosssection_name));

    std::string truecross_name = hist_name + "_TrueCrossSection";
    Name_Map.insert(std::make_pair(True_crosssection, truecross_name));

    std::string nom_Eff_name = hist_name+ "_" + playlist + "_effNum";
    Name_Map.insert(std::make_pair(nom_Eff, nom_Eff_name));

    std::string dom_Eff_name = hist_name + "_" + playlist + "_effDom";
    Name_Map.insert(std::make_pair(dom_Eff, dom_Eff_name));

    std::string eff_name = hist_name + "_efficiency";
    Name_Map.insert(std::make_pair(Eff, eff_name));

   std::string TRUEcrosssection_Elastic = hist_name + "_CrossSection_Interaction_Elastic";
   Name_Map.insert(std::make_pair(True_crosssection_interaction_Elastic,TRUEcrosssection_Elastic));

   std::string TRUEcrosssection_DIS = hist_name + "_CrossSection_Interaction_DIS";
   Name_Map.insert(std::make_pair(True_crosssection_interaction_DIS,TRUEcrosssection_DIS));

   std::string TRUEcrosssection_1pion = hist_name + "_CrossSection_Interaction_1Pion";
   Name_Map.insert(std::make_pair(True_crosssection_interaction_1pion,TRUEcrosssection_1pion));

   std::string TRUEcrosssection_2p2h = hist_name + "_CrossSection_Interaction_2p2h";
   Name_Map.insert(std::make_pair(True_crosssection_interaction_2p2h, TRUEcrosssection_2p2h));

   std::string TRUEcrosssection_Other = hist_name + "_CrossSection_Interaction_Other";
   Name_Map.insert(std::make_pair(True_crosssection_interaction_other,TRUEcrosssection_Other));

   std::string TRUEcrosssection_none = hist_name + "_CrossSection_Interaction_None";
    Name_Map.insert(std::make_pair(True_crosssection_interaction_none,TRUEcrosssection_none));

  }

  else if(isFUll==false){
    auto hist_name = GetMuonVarHistName(MuonVar_type);
    std::string hist1_name = hist_name + "_" + playlist;
    Name_Map.insert(std::make_pair(Data_BG, hist1_name));

    std::string hist1_name_pot = hist1_name + "_potnorm";
    Name_Map.insert(std::make_pair(Data_BG_potNorm, hist1_name_pot));
  }

  return Name_Map;

}

CrossSection_name_Map Generate_CrossSection_histsNames_withInteraction_DISbreakdown(MuonVar MuonVar_type, std::string playlist, bool isFUll){

  CrossSection_name_Map Name_Map;
    auto hist_name = GetMuonVarHistName(MuonVar_type);

  if(isFUll==true)
  {

    std::string hist1_name = hist_name + "_" + playlist + "_Data_Signal";
    Name_Map.insert(std::make_pair(Data_signal, hist1_name));

    std::string hist1_reco = hist_name + "_" + playlist + "_RECO_Signal";
    Name_Map.insert(std::make_pair(RECO_signal, hist1_reco));

    //std::string hist1_name_pot = hist_name + "_" + playlist + "_potnorm_Data_Signal";
    //Name_Map.insert(std::make_pair(Data_signal_potNorm, hist1_name_pot));

    //std::string hist_RECO_BG = hist_name + "_" + playlist + "_potnorm_RECO_BG";
    //Name_Map.insert(std::make_pair(MC_reco_BG, hist_RECO_BG));

    //std::string hist1_name_pot_full_empty = hist_name + "_Full_sub_Empty_potnorm_Data_Signal";
    //Name_Map.insert(std::make_pair(Data_signal_BGsub_potNorm, hist1_name_pot_full_empty));

    //std::string hist2_name_pot_full_empty = hist_name + "_Full_sub_Empty_potnorm_RECO_Signal";
    //Name_Map.insert(std::make_pair(RECO_signal_BGsub_potNorm, hist2_name_pot_full_empty));

    //std::string hist1_name_pot_full_empty_BG = hist_name + "_Full_sub_Empty_potnorm_RECO_BG";
    //Name_Map.insert(std::make_pair(MC_reco_subtracted_BG, hist1_name_pot_full_empty_BG));

    //std::string hist1_name_Data_signal_BG_subtracted = hist_name + "_Data_BG_Subtracted";
    //Name_Map.insert(std::make_pair(Data_signal_BG_subtracted, hist1_name_Data_signal_BG_subtracted));

    std::string unfolded_name = hist_name+ "_" + playlist  + "_unfolded_data";
    Name_Map.insert(std::make_pair(Data_signal_unfolded, unfolded_name));

    std::string eff_Corrected_name = hist_name + "_" + playlist +"_unfolded_data_effcorrected";
    Name_Map.insert(std::make_pair(Data_signal_unfolded_effcorrected, eff_Corrected_name));

    std::string unfolded_crosssection_name = hist_name + "_" + playlist + "_CrossSection_data_unfolded";
    Name_Map.insert(std::make_pair(Data_crosssection, unfolded_crosssection_name));

    std::string truecross_name = hist_name + "_" + playlist + "_TrueCrossSection";
    Name_Map.insert(std::make_pair(True_crosssection, truecross_name));

    std::string nom_Eff_name = hist_name+ "_" + playlist + "_effNum";
    Name_Map.insert(std::make_pair(nom_Eff, nom_Eff_name));

    std::string dom_Eff_name = hist_name + "_" + playlist + "_effDom";
    Name_Map.insert(std::make_pair(dom_Eff, dom_Eff_name));

    std::string eff_name = hist_name + "_" + playlist + "_efficiency";
    Name_Map.insert(std::make_pair(Eff, eff_name));

   std::string TRUEcrosssection_Elastic = hist_name + "_" + playlist + "_CrossSection_Interaction_QE";
   Name_Map.insert(std::make_pair(True_crosssection_interaction_Elastic,TRUEcrosssection_Elastic));

   std::string TRUEcrosssection_DISSIS = hist_name + "_" + playlist + "_CrossSection_Interaction_DISSIS";
   Name_Map.insert(std::make_pair(True_crosssection_interaction_DISSIS,TRUEcrosssection_DISSIS));

   std::string TRUEcrosssection_DISSoft = hist_name + "_" + playlist + "_CrossSection_Interaction_DISSoft";
   Name_Map.insert(std::make_pair(True_crosssection_interaction_DISSoft,TRUEcrosssection_DISSoft));

   std::string TRUEcrosssection_DISHard = hist_name + "_" + playlist + "_CrossSection_Interaction_DISHard";
   Name_Map.insert(std::make_pair(True_crosssection_interaction_DISHard,TRUEcrosssection_DISHard));

   std::string TRUEcrosssection_deltaRes = hist_name + "_" + playlist + "_CrossSection_Interaction_#DeltaRes";
   Name_Map.insert(std::make_pair(True_crosssection_interaction_DeltaRes,TRUEcrosssection_deltaRes));

   std::string TRUEcrosssection_HeavierRes = hist_name + "_" + playlist + "_CrossSection_Interaction_HeavierRes";
   Name_Map.insert(std::make_pair(True_crosssection_interaction_HeavierRes,TRUEcrosssection_HeavierRes));

   std::string TRUEcrosssection_2p2h = hist_name + "_" + playlist + "_CrossSection_Interaction_2p2h";
   Name_Map.insert(std::make_pair(True_crosssection_interaction_2p2h, TRUEcrosssection_2p2h));

   std::string TRUEcrosssection_Other = hist_name + "_" + playlist + "_CrossSection_Interaction_Other";
   Name_Map.insert(std::make_pair(True_crosssection_interaction_other,TRUEcrosssection_Other));

   std::string TRUEcrosssection_none = hist_name + "_" + playlist + "_CrossSection_Interaction_None";
    Name_Map.insert(std::make_pair(True_crosssection_interaction_none,TRUEcrosssection_none));

    std::string Mig = hist_name + "_Mig";
     Name_Map.insert(std::make_pair(mvnreponse_Mig,Mig));



  }

  else if(isFUll==false){

    //auto hist_name = GetMuonVarHistName(MuonVar_type);
  //  std::string hist1_name = hist_name + "_" + playlist + "_Data_Signal";
    //Name_Map.insert(std::make_pair(Data_signal, hist1_name));

    //std::string hist1_RECO = hist_name + "_" + playlist + "_RECO_Signal";
    //Name_Map.insert(std::make_pair(RECO_signal, hist1_RECO));

    std::string hist1_reco = hist_name + "_" + playlist + "_potnorm_RECO_Signal";
    Name_Map.insert(std::make_pair(RECO_signal, hist1_reco));

    std::string hist1_name_pot = hist_name + "_" + playlist + "_potnorm_Data_Signal";
    Name_Map.insert(std::make_pair(Data_signal, hist1_name_pot));


    //std::string hist1_name = hist_name + "_" + playlist;
    //Name_Map.insert(std::make_pair(Data_BG, hist1_name));

    std::string hist_RECO_BG = hist_name + "_" + playlist + "_potnorm_RECO_BG";
    Name_Map.insert(std::make_pair(MC_reco_BG, hist_RECO_BG));

    std::string hist2_name_pot = hist_name + "_potnorm";
    Name_Map.insert(std::make_pair(Data_BG_potNorm, hist2_name_pot));
  }

  return Name_Map;

}

void PrintCrossSection_MapName(CrossSection_name_Map Map , char * outputLabel){

 std::map<CrossSectionHist, std::string>::iterator it;
 std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;
 std::cout<< " Printing Hist Map for : "<< outputLabel << std::endl;
 std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;

 for (it = Map.begin(); it != Map.end(); it++)
 {

     std::cout <<"Map key = "
               << it->first    // string (key)
               << ": Hist String = "
               << it->second   // string's value
               << std::endl;
 }
 std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;
 std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;



return;

}





CrossSection_MnvH1D_Map Generate_CrossSection_Hist_Map(TFile& file, CrossSection_name_Map Map){
  CrossSection_MnvH1D_Map Hist_Map;

  std::map<CrossSectionHist, std::string>::iterator it;
  for (it = Map.begin(); it != Map.end(); it++)
  {
    std::cout<<"HistName = "<< it->second << std::endl;
    auto hist = Get1DHist(file, it->second );
    //MnvH1D *hist = (MnvH1D*)(cat->second)->Get(name);
    Hist_Map.insert(std::make_pair(it->first, hist));

  }

  return Hist_Map;

}


Migration_MnvH2D_Map Generate_CrossSection_Mig_Hist_Map(TFile& file, std::vector<MuonVar> muon_vector){
  Migration_MnvH2D_Map Hist_Map;
  for(auto Muon:muon_vector){
    auto mig_type = Migration_muonType(Muon);
    std::string Name = GetMuonVarHistName(Muon) + "_Mig";
    auto hist_2D = Get2DHist(file, Name );
    Hist_Map.insert(std::make_pair(mig_type, hist_2D));

  }

    return Hist_Map;
}


void MakeCrossSectionPlots_Interaction_Ratio(CrossSection_MnvH1D_Map CrossSection_map,CrossSection_MnvH1D_Map CrossSection_map_helium,
  std::string cross_section_units, std::string pdf,bool MakeXaxisLOG,bool doBinwidth ,
  MuonVar MuonVar, char *Playlist_name, double POT_Data, double POT_MC, Genie_Models Modelinputs){


std::cout<<"Inside MakeCrossSectionPlots " << std::endl;
/// first Plot Signal Data
std::string X_axis = GetMuonVarAXISName(MuonVar);
char X_axis_char[X_axis.length()+1];
strcpy(X_axis_char,X_axis.c_str());
std::string MuonTitle = GetMuonVarTitleName(MuonVar);
std::string pdfname= GetMuonVarpdfName(MuonVar);
std::string unit = GetMuonUnitType(MuonVar);
std::string title_Signal_TRUTH = MuonTitle + " TRUTH Signal Selection Dom Eff";
std::string EventBin = "Event Rate / [" + unit +"]";
std::string Efficiency_name  = "Efficiency" ;
std::string EventBin_noUnits = "Event Rate";
char EventBin_char[EventBin.length()+1];
strcpy(EventBin_char,EventBin.c_str());
char EventBin_noUnits_char[EventBin_noUnits.length()+1];
strcpy(EventBin_noUnits_char,EventBin_noUnits.c_str());

bool dontBinwidthNorm = false;



char title_Signal_TRUTH_char[title_Signal_TRUTH.length()+1];
strcpy(title_Signal_TRUTH_char,title_Signal_TRUTH.c_str());
DrawCVAndError_FromHistPointer(CrossSection_map[dom_Eff], title_Signal_TRUTH_char ,X_axis, EventBin, pdf,  doBinwidth, MakeXaxisLOG);
std::cout<<"Made CrossSection_map[dom_Eff]" << std::endl;

std::string title_Signal_nomEff = MuonTitle + " Selection Nom Eff";
char title_Signal_nomEff_char[title_Signal_nomEff.length()+1];
strcpy(title_Signal_nomEff_char,title_Signal_nomEff.c_str());
DrawCVAndError_FromHistPointer(CrossSection_map[nom_Eff], title_Signal_nomEff_char ,X_axis, EventBin, pdf,  doBinwidth, MakeXaxisLOG);
std::cout<<"Made CrossSection_map[nom_Eff]" << std::endl;


std::string title_Signal = MuonTitle + " Data Signal Selection";
char title_Signal_char[title_Signal.length()+1];
strcpy(title_Signal_char,title_Signal.c_str());
DrawCVAndError_FromHistPointer(CrossSection_map[Data_signal], title_Signal_char ,X_axis, EventBin, pdf,  doBinwidth, MakeXaxisLOG);
std::cout<<"Made CrossSection_map[Data_signal]" << std::endl;

//std::string title_Signal_Pot = MuonTitle + " Data Signal [POT normalize]";
//char title_Signal_Pot_char[title_Signal_Pot.length()+1];
//strcpy(title_Signal_Pot_char,title_Signal_Pot.c_str());
//DrawCVAndError_FromHistPointer(CrossSection_map[Data_signal_potNorm], title_Signal_Pot_char ,X_axis, EventBin, pdf,  doBinwidth, MakeXaxisLOG);
//std::cout<<"CrossSection_map[Data_signal_potNorm]" << std::endl;

//std::string title_Signal_Pot2 = MuonTitle + " Data Signal with BG";
//char title_Signal_Pot2_char[title_Signal_Pot2.length()+1];
//strcpy(title_Signal_Pot2_char,title_Signal_Pot2.c_str());

 //DrawCVAndError_FromHistPointer(CrossSection_map[Data_signal], CrossSection_map[RECO_signal],CrossSection_mapEmpty[Data_signal], CrossSection_mapEmpty[RECO_signal], title_Signal_Pot2_char, X_axis,EventBin ,
//pdf, true, false, false, -99, false);

//std::string title_Signal_BG_Sub_Pot = MuonTitle + " Data Signal [POT normalize][BGsub]";
//char title_Signal_BG_Sub_Pot_char[title_Signal_BG_Sub_Pot.length()+1];
//strcpy(title_Signal_BG_Sub_Pot_char,title_Signal_BG_Sub_Pot.c_str());
//DrawCVAndError_FromHistPointer(CrossSection_map[Data_signal_BGsub_potNorm], title_Signal_BG_Sub_Pot_char ,X_axis, EventBin, pdf,  doBinwidth, MakeXaxisLOG);
//std::cout<<"CossSection_map[Data_signal_BGsub_potNorm]" << std::endl;

//std::string title_Signal_BG_Sub_Pot_BG = MuonTitle + " Data Signal [RECO BGsub]";
//char title_Signal_BG_Sub_Pot_BG_char[title_Signal_BG_Sub_Pot_BG.length()+1];
//strcpy(title_Signal_BG_Sub_Pot_BG_char,title_Signal_BG_Sub_Pot_BG.c_str());
//DrawCVAndError_FromHistPointer(CrossSection_map[Data_signal_BG_subtracted], title_Signal_BG_Sub_Pot_BG_char ,X_axis, EventBin, pdf,  doBinwidth, MakeXaxisLOG);
//std::cout<<"CossSection_map[Data_signal_BGsub_potNorm]" << std::endl;


std::string title_BG = MuonTitle + "BG Subtracted";
char title_BG_char[title_BG.length()+1];
strcpy(title_BG_char,title_BG.c_str());


//DrawCVAndError_FromHistPointer(CrossSection_map[MC_reco_subtracted_BG], title_BG_char ,X_axis, EventBin, pdf,  doBinwidth, MakeXaxisLOG);
//std::cout<<"CossSection_map[Data_signal_BGsub_potNorm]" << std::endl;


//Draw_DataWITHMC_SingleHistinput_withRatioCrossSection(CrossSection_map[RECO_signal_BGsub_potNorm], CrossSection_map[Data_signal_BGsub_potNorm],
//                                           Playlist_name, pdf, title_BG_char, "", X_axis_char, EventBin_char,
//                                          doBinwidth, MakeXaxisLOG,  false);

  //Draw_DataWITHMC_SingleHistinput_withRatio(CrossSection_map[RECO_signal_BGsub_potNorm],
  //  CrossSection_map[Data_signal_BGsub_potNorm],
  //  Playlist_name, pdf, title_BG_char, unit,
  //  X_axis_char, EventBin_noUnits_char, doBinwidth, MakeXaxisLOG,
  //  false, false);



std::string title_unfolded = MuonTitle + " Data Signal [POT norm][Unfolded]";
char title_unfolded_char[title_unfolded.length()+1];
strcpy(title_unfolded_char,title_unfolded.c_str());
DrawCVAndError_FromHistPointer(CrossSection_map[Data_signal_unfolded], title_unfolded_char ,X_axis, EventBin, pdf,  doBinwidth, MakeXaxisLOG);

std::cout<<"CrossSection_map[Data_signal_unfolded]" << std::endl;

std::string title_EffCorr_Pot = MuonTitle + " Data Signal [POT norm][BGsub][Unfolded][Eff Corr]";
char title_EffCorr_Pot_char[title_EffCorr_Pot.length()+1];
strcpy(title_EffCorr_Pot_char,title_EffCorr_Pot.c_str());

DrawCVAndError_FromHistPointer(CrossSection_map[Data_signal_unfolded_effcorrected], title_EffCorr_Pot_char ,X_axis, EventBin, pdf,  doBinwidth, MakeXaxisLOG);
std::cout<<"CrossSection_map[Data_signal_unfolded_effcorrected]" << std::endl;

std::string title_eff = MuonTitle + " Efficiency";
char title_eff_char[title_eff.length()+1];
strcpy(title_eff_char,title_eff.c_str());
DrawCVAndError_FromHistPointer(CrossSection_map[Eff], title_eff_char ,X_axis, Efficiency_name, pdf,  false, MakeXaxisLOG);
std::cout<<"CrossSection_map[Eff]" << std::endl;

std::string Eventselection_title = MuonTitle + " Event Selection";
char Eventselection_title_char[Eventselection_title.length()+1];
strcpy(Eventselection_title_char,Eventselection_title.c_str());

Draw_DataWITHMC_SingleHistinput_withRatio(CrossSection_map[RECO_signal], CrossSection_map[Data_signal],
                                            Playlist_name, pdf, Eventselection_title_char, "",
                                            X_axis_char, "Event Rate", doBinwidth, MakeXaxisLOG,
                                            false, false);





std::string title_Cross_Section = MuonTitle + " Cross-Section:  #nu_{#mu} + CH #rightarrow #mu^{-} + X";
char title_Cross_Section_char[title_Cross_Section.length()+1];
strcpy(title_Cross_Section_char,title_Cross_Section.c_str());

std::string crossSection_y_axis = "#frac{d#sigma}{d" + GetMuonVar_crosssection(MuonVar) + "} (10^{-38} cm^{2} / " +  cross_section_units + " / nucleon)";


char crossSection_y_axis_char[crossSection_y_axis.length()+1];
strcpy(crossSection_y_axis_char,crossSection_y_axis.c_str());
std::cout<<"Scaling Hists" << std::endl;

 auto names = CrossSection_map[True_crosssection]->GetErrorBandNames();
for(auto name : names){

std::cout<< " Name os TRUE crossection band 1 "<< name << std::endl;

}
//fauto ccma_band = CrossSection_map[True_crosssection]->GetLatErrorBand( "GENIE_MaCCQE" );

 //PlotVertBand("Flux", "flux",CrossSection_map[True_crosssection]);


double Scale = pow(10,-38);
CrossSection_map[True_crosssection]->Scale(1/Scale);
CrossSection_map[Data_crosssection]->Scale(1/Scale);
CrossSection_map[True_crosssection_interaction_Elastic]->Scale(1/Scale);
//CrossSection_map[True_crosssection_interaction_DIS]->Scale(1/Scale);
CrossSection_map[True_crosssection_interaction_DISSIS]->Scale(1/Scale);
CrossSection_map[True_crosssection_interaction_DISSoft]->Scale(1/Scale);
CrossSection_map[True_crosssection_interaction_DISHard]->Scale(1/Scale);
CrossSection_map[True_crosssection_interaction_DeltaRes]->Scale(1/Scale);
CrossSection_map[True_crosssection_interaction_HeavierRes]->Scale(1/Scale);
//CrossSection_map[True_crosssection_interaction_DIS]->Scale(1/Scale);
//CrossSection_map[True_crosssection_interaction_1pion]->Scale(1/Scale);
CrossSection_map[True_crosssection_interaction_2p2h]->Scale(1/Scale);
CrossSection_map[True_crosssection_interaction_other]->Scale(1/Scale);
CrossSection_map[True_crosssection_interaction_none]->Scale(1/Scale);

std::string inputname1 = pdfname + "Old_ZexpTRUE";
std::string inputname2 = pdfname + "Old_ZexpData";
//PlotVertBand("GENIE_MaZExpCCQE", inputname1 ,"MaCCQE Systematic universes MC TRUE", X_axis, crossSection_y_axis, CrossSection_map[True_crosssection]);
//PlotVertBand("GENIE_MaZExpCCQE", inputname2 ,"MaCCQE Systematic universes DATA", X_axis, crossSection_y_axis, CrossSection_map[Data_crosssection]);


//

TH1D*  hMC_Model_nominal =  (TH1D*)CrossSection_map[True_crosssection]->Clone(uniq());

std::cout<<"Writing First XSec method" << std::endl;
//Draw_DataWITHMC_SingleHistinput_withRatioCrossSection(CrossSection_map[True_crosssection], CrossSection_map[Data_crosssection],
//                                           Playlist_name, pdf, title_Cross_Section_char, "", X_axis_char, crossSection_y_axis_char,
//                                          doBinwidth, MakeXaxisLOG,  true);

Draw_DataWITHMC_SingleHistinput_withRatio(CrossSection_map[True_crosssection], CrossSection_map[Data_crosssection],
                                            Playlist_name, pdf, title_Cross_Section_char, "",
                                            X_axis_char, crossSection_y_axis_char, dontBinwidthNorm, MakeXaxisLOG,
                                            false, false);



                                        //  auto names2 = CrossSection_map[True_crosssection]->GetErrorBandNames();
                                        // for(auto name : names2){

                                        // std::cout<< " Name os TRUE crossection band 2 "<< name << std::endl;

                                        // }


Modelinputs.intializeTFileMap();
Modelinputs.intializeTH1DMap();
Modelinputs.ScaleTH1DHists(1/Scale);
double Area = CrossSection_map[True_crosssection]->Integral();
std::cout<<"Modelinputs.ModelHistMap_1D.size() = "<< Modelinputs.ModelHistMap_th1D.size()<<std::endl;

//TH1D*  hMC_Model_G18_02a_02_11a =  (TH1D*)Modelinputs.ModelHistMap_th1D[kME_GENIE_G18_02a_02_11a]->Clone("G18_02a_02_11a");
//TH1D*  hMC_Model_G18_10a_02_11a =  (TH1D*)Modelinputs.ModelHistMap_th1D[kME_GENIE_G18_10a_02_11a]->Clone("G18_10a_02_11a");
//TH1D*  hMC_Model_G18_02b_02_11a =  (TH1D*)Modelinputs.ModelHistMap_th1D[kME_GENIE_G18_02b_02_11a]->Clone("G18_02b_02_11a");
//TH1D*  hMC_Model_G18_10b_02_11a =  (TH1D*)Modelinputs.ModelHistMap_th1D[kME_GENIE_G18_10b_02_11a]->Clone("G18_10b_02_11a");
//
//Double_t NormBinWidth = CrossSection_map[True_crosssection]->GetNormBinWidth();


//hMC_Model_G18_02a_02_11a->Scale(Area/ hMC_Model_G18_02a_02_11a->Integral());
//hMC_Model_G18_10a_02_11a->Scale(Area/ hMC_Model_G18_10a_02_11a->Integral());
//hMC_Model_G18_02b_02_11a->Scale(Area/ hMC_Model_G18_02b_02_11a->Integral());
//hMC_Model_G18_10b_02_11a->Scale(Area/ hMC_Model_G18_10b_02_11a->Integral());



//DrawCVAndError_From2HIST(hMC_Model_nominal, "nominal" ,hMC_Model_G18_10a_02_11a,
//         "G18_10a_02_11a",  "model test" ,X_axis, crossSection_y_axis ,
//pdf, false, true, -99 , false);

std::vector<int> Helium9_colorScheme = {
  TColor::GetColor("#DA70D6"), //'orchid'
  TColor::GetColor("#FFA500"), //'orange'
  TColor::GetColor("#87CEEB"),//'skyblue'
  TColor::GetColor("#6495ED"), //'cornflowerblue'
  TColor::GetColor("#00FFFF"),//'aqua'
  TColor::GetColor("#0000CD"),//'blue'
  TColor::GetColor("#FF0000"),//'red'
  TColor::GetColor("#32CD32"),//'limegreen'
  TColor::GetColor("#FFD700"),  // Gold
  TColor::GetColor("#800000"),  // Maroon
  TColor::GetColor("#555555")  // dark grey
};


//DrawCVAndError_From5HIST(CrossSection_map[Data_crosssection], "Data",
//                              hMC_Model_nominal, "Minerva v1",
//                              hMC_Model_G18_02a_02_11a, "GENIE: G18_02a_02_11a",
//                              hMC_Model_G18_10a_02_11a, "GENIE: G18_10a_02_11a",
//                              hMC_Model_G18_02b_02_11a, "GENIE: G18_02b_02_11a",
//                              hMC_Model_G18_10b_02_11a, "GENIE: G18_10b_02_11a",
//                              NormBinWidth,
//                              Helium9_colorScheme,
//                              "Model comparson" ,X_axis, crossSection_y_axis,
//   pdf, false, true, -99 , false);




//TObjArray *TobjMC_Model;
//TobjMC_Model->SetOwner(kTRUE);
//
//TobjMC_Model->Add(hMC_Model_G18_02a_02_11a);
//TobjMC_Model->Add(hMC_Model_G18_10a_02_11a);
//TobjMC_Model->Add(hMC_Model_G18_02b_02_11a);
//TobjMC_Model->Add(hMC_Model_G18_10b_02_11a);

//hMC_Model_clone->Scale(1.0,"width");
//hMC_Model_clone->Scale(Scale);

//MC_ModelTypes{kME_GENIE_MnvTune1,
//  kME_GENIE_G18_02a_02_11a,
//  kME_GENIE_G18_10a_02_11a,
//  kME_GENIE_G18_02b_02_11a,
//  kME_GENIE_G18_10b_02_11a
//

//std::cout<<"TITLE outside class " << Modelinputs.ModelHistMap_1D[0]->GetTitle()<<std::endl;
std::cout<<"apout Draw_DataWITHMC_SingleHistinput_withRatioCrossSection " << std::endl;
//Draw_DataWITHMC_SingleHistinput_withRatioCrossSection(CrossSection_map[True_crosssection], CrossSection_map[Data_crosssection], TobjMC_Model,
//Playlist_name, pdf, title_Cross_Section_char, "", X_axis_char, crossSection_y_axis_char, MakeXaxisLOG );




std::cout<<"CrossSection_map[True_crosssection]" << std::endl;
 //void Draw_DataWITHMC_SingleHistinput_withRatio(MnvH1D *hist_MC, MnvH1D *hist_Data,
     //char *Playlist_name, std::string pdf_label, char *histotitle, std::string units,
      //char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG , bool drawAllErrorGroups= true);
      std::cout<<"Writing First XSec method with Interactions" << std::endl;

      Draw_DataWITHMC_SingleHistinput_withRatioCrossSection_Interactions_DISbreakdown(
        CrossSection_map[True_crosssection], CrossSection_map[Data_crosssection],
        CrossSection_map[True_crosssection_interaction_Elastic],
        CrossSection_map[True_crosssection_interaction_2p2h],
        CrossSection_map[True_crosssection_interaction_DeltaRes],
        CrossSection_map[True_crosssection_interaction_HeavierRes],
        CrossSection_map[True_crosssection_interaction_DISSIS],
        CrossSection_map[True_crosssection_interaction_DISSoft],
        CrossSection_map[True_crosssection_interaction_DISHard],
        CrossSection_map[True_crosssection_interaction_none],
        CrossSection_map[True_crosssection_interaction_other],
        Playlist_name, pdf, title_Cross_Section_char, "",
        X_axis_char, crossSection_y_axis_char, dontBinwidthNorm, MakeXaxisLOG,  false, POT_MC, POT_Data);
        std::string pdf_pdf = pdf + ".pdf";

        char matrixtitle[1024];
        sprintf(matrixtitle, "[DATA] %s ",X_axis_char );
      DrawCovarientMatrix_FromHistPointer(CrossSection_map[Data_crosssection], matrixtitle, "Bin Number","Bin Number ", pdf_pdf);


        Draw_MCInteractions_FractionEvents(
      CrossSection_map[True_crosssection],
    CrossSection_map[True_crosssection_interaction_Elastic],
    CrossSection_map[True_crosssection_interaction_2p2h],
    CrossSection_map[True_crosssection_interaction_DeltaRes],
    CrossSection_map[True_crosssection_interaction_HeavierRes],
    CrossSection_map[True_crosssection_interaction_DISSIS],
    CrossSection_map[True_crosssection_interaction_DISSoft],
    CrossSection_map[True_crosssection_interaction_DISHard],
    CrossSection_map[True_crosssection_interaction_none],
    CrossSection_map[True_crosssection_interaction_other],
      pdf, "Cross-Section Interaction Breakdown",
         X_axis_char, "Fraction of Events");

         CrossSection_map_helium[True_crosssection]->Scale(1/Scale);
         CrossSection_map_helium[Data_crosssection]->Scale(1/Scale);

         CrossSection_map[True_crosssection]->Scale(POT_Ratio);
         CrossSection_map[Data_crosssection]->Scale(POT_Ratio);

         std::cout<< " Trying to Divide" << MuonTitle << std::endl;
         std::cout<< "CrossSection_map[True_crosssection] Bins " <<      CrossSection_map[True_crosssection]->GetNbinsX()<< std::endl;
         std::cout<< "CrossSection_map_helium[True_crosssection] Bins " <<      CrossSection_map_helium[True_crosssection]->GetNbinsX()<< std::endl;

         std::cout<< "CrossSection_map[Data_crosssection] Bins " <<      CrossSection_map[Data_crosssection]->GetNbinsX()<< std::endl;
         std::cout<< "CrossSection_map_helium[Data_crosssection] Bins " <<      CrossSection_map_helium[Data_crosssection]->GetNbinsX()<< std::endl;


         CrossSection_map[True_crosssection]->Divide(CrossSection_map[True_crosssection],CrossSection_map_helium[True_crosssection] ) ;
         CrossSection_map[Data_crosssection]->Divide(CrossSection_map[Data_crosssection],CrossSection_map_helium[Data_crosssection] ) ;


          crossSection_y_axis = "#frac{d#sigma^{CH}}{d" + GetMuonVar_crosssection(MuonVar) + "} / #frac{d#sigma^{He}}{d" + GetMuonVar_crosssection(MuonVar) + "}";
          char crossSection_Ratio_y_axis_char[crossSection_y_axis.length()+1];
          strcpy(crossSection_Ratio_y_axis_char,crossSection_y_axis.c_str());
          title_Cross_Section = MuonTitle + " Cross Section Ratio";

          char title_Ratio_Cross_Section_char[title_Cross_Section.length()+1];
          strcpy(title_Ratio_Cross_Section_char,title_Cross_Section.c_str());



         Draw_DataWITHMC_SingleHistinput_withRatio(CrossSection_map[True_crosssection], CrossSection_map[Data_crosssection],
                                                     Playlist_name, pdf, title_Ratio_Cross_Section_char, "",
                                                     X_axis_char, crossSection_Ratio_y_axis_char, false, MakeXaxisLOG,
                                                     false, false);




return;
}



CrossSection_name_Map Generate_CrossSection_histsNames_withInteraction_DISbreakdown_helium(MuonVar MuonVar_type, std::string playlist, bool isFUll){

  CrossSection_name_Map Name_Map;
    auto hist_name = GetMuonVarHistName(MuonVar_type);

  if(isFUll==true)
  {

    std::string hist1_name = hist_name + "_" + playlist + "_Data_Signal";
    Name_Map.insert(std::make_pair(Data_signal, hist1_name));

    std::string hist1_reco = hist_name + "_" + playlist + "_potnorm_RECO_Signal";
    Name_Map.insert(std::make_pair(RECO_signal, hist1_reco));

    std::string hist1_name_pot = hist_name + "_" + playlist + "_potnorm_Data_Signal";
    Name_Map.insert(std::make_pair(Data_signal_potNorm, hist1_name_pot));

    std::string hist_RECO_BG = hist_name + "_" + playlist + "_potnorm_RECO_BG";
    Name_Map.insert(std::make_pair(MC_reco_BG, hist_RECO_BG));

    std::string hist1_name_pot_full_empty = hist_name + "_Full_sub_Empty_potnorm_Data_Signal";
    Name_Map.insert(std::make_pair(Data_signal_BGsub_potNorm, hist1_name_pot_full_empty));

    std::string hist2_name_pot_full_empty = hist_name + "_Full_sub_Empty_potnorm_RECO_Signal";
    Name_Map.insert(std::make_pair(RECO_signal_BGsub_potNorm, hist2_name_pot_full_empty));

    std::string hist1_name_pot_full_empty_BG = hist_name + "_Full_sub_Empty_potnorm_RECO_BG";
    Name_Map.insert(std::make_pair(MC_reco_subtracted_BG, hist1_name_pot_full_empty_BG));

    std::string hist1_name_Data_signal_BG_subtracted = hist_name + "_Data_BG_Subtracted";
    Name_Map.insert(std::make_pair(Data_signal_BG_subtracted, hist1_name_Data_signal_BG_subtracted));

    std::string unfolded_name = hist_name + "_unfolded_data";
    Name_Map.insert(std::make_pair(Data_signal_unfolded, unfolded_name));

    std::string eff_Corrected_name = hist_name +"_unfolded_data_effcorrected";
    Name_Map.insert(std::make_pair(Data_signal_unfolded_effcorrected, eff_Corrected_name));

    std::string unfolded_crosssection_name = hist_name + "_CrossSection_data_unfolded";
    Name_Map.insert(std::make_pair(Data_crosssection, unfolded_crosssection_name));

    std::string truecross_name = hist_name + "_TrueCrossSection";
    Name_Map.insert(std::make_pair(True_crosssection, truecross_name));

    std::string nom_Eff_name = hist_name+ "_" + playlist + "_effNum";
    Name_Map.insert(std::make_pair(nom_Eff, nom_Eff_name));

    std::string dom_Eff_name = hist_name + "_" + playlist + "_effDom";
    Name_Map.insert(std::make_pair(dom_Eff, dom_Eff_name));

    std::string eff_name = hist_name + "_efficiency";
    Name_Map.insert(std::make_pair(Eff, eff_name));

   std::string TRUEcrosssection_Elastic = hist_name + "_CrossSection_Interaction_QE";
   Name_Map.insert(std::make_pair(True_crosssection_interaction_Elastic,TRUEcrosssection_Elastic));

   std::string TRUEcrosssection_DISSIS = hist_name + "_CrossSection_Interaction_DISSIS";
   Name_Map.insert(std::make_pair(True_crosssection_interaction_DISSIS,TRUEcrosssection_DISSIS));

   std::string TRUEcrosssection_DISSoft = hist_name + "_CrossSection_Interaction_DISSoft";
   Name_Map.insert(std::make_pair(True_crosssection_interaction_DISSoft,TRUEcrosssection_DISSoft));

   std::string TRUEcrosssection_DISHard = hist_name + "_CrossSection_Interaction_DISHard";
   Name_Map.insert(std::make_pair(True_crosssection_interaction_DISHard,TRUEcrosssection_DISHard));

   std::string TRUEcrosssection_deltaRes = hist_name + "_CrossSection_Interaction_#DeltaRes";
   Name_Map.insert(std::make_pair(True_crosssection_interaction_DeltaRes,TRUEcrosssection_deltaRes));

   std::string TRUEcrosssection_HeavierRes = hist_name + "_CrossSection_Interaction_HeavierRes";
   Name_Map.insert(std::make_pair(True_crosssection_interaction_HeavierRes,TRUEcrosssection_HeavierRes));

   std::string TRUEcrosssection_2p2h = hist_name + "_CrossSection_Interaction_2p2h";
   Name_Map.insert(std::make_pair(True_crosssection_interaction_2p2h, TRUEcrosssection_2p2h));

   std::string TRUEcrosssection_Other = hist_name + "_CrossSection_Interaction_Other";
   Name_Map.insert(std::make_pair(True_crosssection_interaction_other,TRUEcrosssection_Other));

   std::string TRUEcrosssection_none = hist_name + "_CrossSection_Interaction_None";
    Name_Map.insert(std::make_pair(True_crosssection_interaction_none,TRUEcrosssection_none));

    std::string Mig = hist_name + "_Mig";
     Name_Map.insert(std::make_pair(mvnreponse_Mig,Mig));



  }

  else if(isFUll==false){

    //auto hist_name = GetMuonVarHistName(MuonVar_type);
  //  std::string hist1_name = hist_name + "_" + playlist + "_Data_Signal";
    //Name_Map.insert(std::make_pair(Data_signal, hist1_name));

    //std::string hist1_RECO = hist_name + "_" + playlist + "_RECO_Signal";
    //Name_Map.insert(std::make_pair(RECO_signal, hist1_RECO));

    std::string hist1_reco = hist_name + "_" + playlist + "_potnorm_RECO_Signal";
    Name_Map.insert(std::make_pair(RECO_signal, hist1_reco));

    std::string hist1_name_pot = hist_name + "_" + playlist + "_potnorm_Data_Signal";
    Name_Map.insert(std::make_pair(Data_signal, hist1_name_pot));


    //std::string hist1_name = hist_name + "_" + playlist;
    //Name_Map.insert(std::make_pair(Data_BG, hist1_name));

    std::string hist_RECO_BG = hist_name + "_" + playlist + "_potnorm_RECO_BG";
    Name_Map.insert(std::make_pair(MC_reco_BG, hist_RECO_BG));

    std::string hist2_name_pot = hist_name + "_potnorm";
    Name_Map.insert(std::make_pair(Data_BG_potNorm, hist2_name_pot));
  }

  return Name_Map;

}
/////////////////////////////////////////////////////
//
////////////////////////////////////////////////////
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
