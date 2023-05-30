#include "Make_CrossSection_Plots.h"



CrossSection_name_Map Generate_CrossSection_histsNames_withInteraction(MuonVar MuonVar_type, std::string playlist, bool isFUll);
CrossSection_name_Map Generate_CrossSection_histsNames_withInteraction_DISbreakdown_helium(MuonVar MuonVar_type, std::string playlist, bool isFUll);
CrossSection_name_Map Generate_CrossSection_histsNames_withInteraction_DISbreakdown(MuonVar MuonVar_type, std::string playlist, bool isFUll);
std::vector<ME_helium_Playlists> GetTrackerPlayListVector();
std::vector<double> generateXAxisBins();
std::vector<double> log_replace(const std::vector<double>& input);
TH2D* rebin_x_axis(TH2D* hist, const std::vector<double>& new_bins);
void MakeCrossSectionPlots_Interaction_Ratio(CrossSection_MnvH1D_Map CrossSection_map,CrossSection_MnvH1D_Map CrossSection_map_helium,
  std::string cross_section_units, std::string pdf,bool MakeXaxisLOG,bool doBinwidth ,
  MuonVar MuonVar, char *Playlist_name, double POT_Data, double POT_MC, Genie_Models Modelinputs);

  //TF1* GetSpline(std::string material);
  //  MnvH1D* MakeCrossSectionSpineHist( MnvH1D *originalHist, std::string material);
  //  MnvH1D* MakeFluxHist(MnvH1D *originalHist, std::string material, double ntargets, double potnorm);
  //  MnvH1D* GetCrossSection_hist(MnvH1D *originalHist, std::string material);


  MnvH1D* MakeHist_combinedTotalError(MnvH1D* input);
  std::vector<double> get_y_bin_edges( TH2D* hist);
  std::vector<double> get_y_bin_edges( MnvH2D* hist);

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

auto PlaylistME_CrossSection_fluxhelium_vertexX = "/minerva/data/users/cnguyen/ME_Flux/flux_helium_helium_2d_vertexX.root";
auto PlaylistME_CrossSection_fluxhelium_vertexY = "/minerva/data/users/cnguyen/ME_Flux/flux_helium_helium_2d_vertexY.root";

//auto PlaylistME_CrossSection_Path = "/minerva/app/users/cnguyen/cmtuser/Minerva_v22r1p1Helium_GIT/NuCCSemiInclusiveHelium/Make_CrossSection/CrossSection.root";



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


std::vector<double> newbins{0, 4, 6, 8, 10, 15, 20};
//0  ,1  ,2  ,3  ,4  ,5  ,6  ,7  ,8  ,9 ,10  ,11  ,12  ,13  ,14  ,15  ,16  ,17  ,18 ,19  ,20
std::vector<double> binsforweights{0, 4, 6, 8, 10, 15, 20};//{0, 4, 6, 8, 10, 15, 20,100};
//0.0  ,1.0  ,2.0  ,3.0  ,4.0  ,5.0  ,6.0  ,7.0  ,8.0  ,9.0 ,10.0  ,11.0  ,12.0  ,13.0  ,14.0  ,15.0  ,16.0  ,17.0  ,18.0 ,19.0  ,20.0
std::vector<double> Vector_bins{0, 4, 6, 8, 10, 15, 20};




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


auto PlaylistME_Flux_tracker_daisy0 = "/minerva/data/users/cnguyen/ME_Flux/flux_tracker_Daisy0.root";
auto PlaylistME_Flux_tracker_daisy1 = "/minerva/data/users/cnguyen/ME_Flux/flux_tracker_Daisy1.root";
auto PlaylistME_Flux_tracker_daisy2 = "/minerva/data/users/cnguyen/ME_Flux/flux_tracker_Daisy2.root";
auto PlaylistME_Flux_tracker_daisy3 = "/minerva/data/users/cnguyen/ME_Flux/flux_tracker_Daisy3.root";
auto PlaylistME_Flux_tracker_daisy4 = "/minerva/data/users/cnguyen/ME_Flux/flux_tracker_Daisy4.root";
auto PlaylistME_Flux_tracker_daisy5 = "/minerva/data/users/cnguyen/ME_Flux/flux_tracker_Daisy5.root";
auto PlaylistME_Flux_tracker_daisy6 = "/minerva/data/users/cnguyen/ME_Flux/flux_tracker_Daisy6.root";
auto PlaylistME_Flux_tracker_daisy7 = "/minerva/data/users/cnguyen/ME_Flux/flux_tracker_Daisy7.root";
auto PlaylistME_Flux_tracker_daisy8 = "/minerva/data/users/cnguyen/ME_Flux/flux_tracker_Daisy8.root";
auto PlaylistME_Flux_tracker_daisy9 = "/minerva/data/users/cnguyen/ME_Flux/flux_tracker_Daisy9.root";
auto PlaylistME_Flux_tracker_daisy10 = "/minerva/data/users/cnguyen/ME_Flux/flux_tracker_Daisy10.root";
auto PlaylistME_Flux_tracker_daisy11 = "/minerva/data/users/cnguyen/ME_Flux/flux_tracker_Daisy11.root";



//simple_flux_tracker_tracker.root
auto PlaylistME_Flux_tracker_git = "../../MATFluxAndReweightFiles/flux_daisy/neutrinos/targets_2345_jointNueIMD/flux_with_errors/flux_tracker.root";// "/minerva/data/users/cnguyen/ME_Flux/flux_tracker_Full_Tracker.root";
//auto PlaylistME_Flux_tracker = "/minerva/data/users/cnguyen/ME_Flux/flux_tracker_Full_Tracker.root";
//auto PlaylistME_Flux_Tracker_homebrew = "/minerva/data/users/cnguyen/ME_Flux/flux_tracker_homebrew.root";// "/minerva/data/users/cnguyen/ME_Flux/flux_tracker_Full_Tracker.root";flux_tracker_tracker_remake.root
//flux_tracker_homebrew.root


auto PlaylistME_Flux_tracker_slice1 = "/minerva/data/users/cnguyen/ME_Flux/flux_tracker_Slice1.root";
auto PlaylistME_Flux_tracker_slice2 = "/minerva/data/users/cnguyen/ME_Flux/flux_tracker_Slice2.root";
auto PlaylistME_Flux_tracker_slice3 = "/minerva/data/users/cnguyen/ME_Flux/flux_tracker_Slice3.root";
auto PlaylistME_Flux_tracker_slice4 = "/minerva/data/users/cnguyen/ME_Flux/flux_tracker_Slice4.root";

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


TFile *TFile_Flux_tracker_daisy0 = new TFile(PlaylistME_Flux_tracker_daisy0);
TFile *TFile_Flux_tracker_daisy1 = new TFile(PlaylistME_Flux_tracker_daisy1);
TFile *TFile_Flux_tracker_daisy2 = new TFile(PlaylistME_Flux_tracker_daisy2);
TFile *TFile_Flux_tracker_daisy3 = new TFile(PlaylistME_Flux_tracker_daisy3);
TFile *TFile_Flux_tracker_daisy4 = new TFile(PlaylistME_Flux_tracker_daisy4);
TFile *TFile_Flux_tracker_daisy5 = new TFile(PlaylistME_Flux_tracker_daisy5);
TFile *TFile_Flux_tracker_daisy6 = new TFile(PlaylistME_Flux_tracker_daisy6);
TFile *TFile_Flux_tracker_daisy7 = new TFile(PlaylistME_Flux_tracker_daisy7);
TFile *TFile_Flux_tracker_daisy8 = new TFile(PlaylistME_Flux_tracker_daisy8);
TFile *TFile_Flux_tracker_daisy9 = new TFile(PlaylistME_Flux_tracker_daisy9);
TFile *TFile_Flux_tracker_daisy10 = new TFile(PlaylistME_Flux_tracker_daisy10);
TFile *TFile_Flux_tracker_daisy11 = new TFile(PlaylistME_Flux_tracker_daisy11);


auto Flux_helium_daisy0_1 = Get1DHist(*TFile_Flux_helium_daisy0,"flux_rebined");
auto Flux_helium_daisy1_1 = Get1DHist(*TFile_Flux_helium_daisy1,"flux_rebined");
auto Flux_helium_daisy2_1 = Get1DHist(*TFile_Flux_helium_daisy2,"flux_rebined");
auto Flux_helium_daisy3_1 = Get1DHist(*TFile_Flux_helium_daisy3,"flux_rebined");
auto Flux_helium_daisy4_1 = Get1DHist(*TFile_Flux_helium_daisy4,"flux_rebined");
auto Flux_helium_daisy5_1 = Get1DHist(*TFile_Flux_helium_daisy5,"flux_rebined");
auto Flux_helium_daisy6_1 = Get1DHist(*TFile_Flux_helium_daisy6,"flux_rebined");
auto Flux_helium_daisy7_1 = Get1DHist(*TFile_Flux_helium_daisy7,"flux_rebined");
auto Flux_helium_daisy8_1 = Get1DHist(*TFile_Flux_helium_daisy8,"flux_rebined");
//auto Flux_helium_daisy8_morebins = Get1DHist(*TFile_Flux_helium_daisy8,"flux");
auto Flux_helium_daisy9_1 = Get1DHist(*TFile_Flux_helium_daisy9,"flux_rebined");
auto Flux_helium_daisy10_1 = Get1DHist(*TFile_Flux_helium_daisy10,"flux_rebined");
auto Flux_helium_daisy11_1 = Get1DHist(*TFile_Flux_helium_daisy11,"flux_rebined");




UnBinWidthNormalizeMnvH1D(*Flux_helium_daisy0_1);
UnBinWidthNormalizeMnvH1D(*Flux_helium_daisy1_1);
UnBinWidthNormalizeMnvH1D(*Flux_helium_daisy2_1);
UnBinWidthNormalizeMnvH1D(*Flux_helium_daisy3_1);
UnBinWidthNormalizeMnvH1D(*Flux_helium_daisy4_1);
UnBinWidthNormalizeMnvH1D(*Flux_helium_daisy5_1);
UnBinWidthNormalizeMnvH1D(*Flux_helium_daisy6_1);
UnBinWidthNormalizeMnvH1D(*Flux_helium_daisy7_1);
UnBinWidthNormalizeMnvH1D(*Flux_helium_daisy8_1);
UnBinWidthNormalizeMnvH1D(*Flux_helium_daisy9_1);
UnBinWidthNormalizeMnvH1D(*Flux_helium_daisy10_1);
UnBinWidthNormalizeMnvH1D(*Flux_helium_daisy11_1);



 PlotUtils::MnvH1D *Flux_helium_daisy0 = RebinMnvH1D(Flux_helium_daisy0_1,newbins);
 PlotUtils::MnvH1D *Flux_helium_daisy1 = RebinMnvH1D(Flux_helium_daisy1_1,newbins);
 PlotUtils::MnvH1D *Flux_helium_daisy2 = RebinMnvH1D(Flux_helium_daisy2_1,newbins);
 PlotUtils::MnvH1D *Flux_helium_daisy3 = RebinMnvH1D(Flux_helium_daisy3_1,newbins);
 PlotUtils::MnvH1D *Flux_helium_daisy4 = RebinMnvH1D(Flux_helium_daisy4_1,newbins);
 PlotUtils::MnvH1D *Flux_helium_daisy5 = RebinMnvH1D(Flux_helium_daisy5_1,newbins);
 PlotUtils::MnvH1D *Flux_helium_daisy6 = RebinMnvH1D(Flux_helium_daisy6_1,newbins);
 PlotUtils::MnvH1D *Flux_helium_daisy7 = RebinMnvH1D(Flux_helium_daisy7_1,newbins);
 PlotUtils::MnvH1D *Flux_helium_daisy8 = RebinMnvH1D(Flux_helium_daisy8_1,newbins);
 PlotUtils::MnvH1D *Flux_helium_daisy9 = RebinMnvH1D(Flux_helium_daisy9_1,newbins);
 PlotUtils::MnvH1D *Flux_helium_daisy10 = RebinMnvH1D(Flux_helium_daisy10_1,newbins);
 PlotUtils::MnvH1D *Flux_helium_daisy11 = RebinMnvH1D(Flux_helium_daisy11_1,newbins);


 Flux_helium_daisy0->Scale(1.0,"width");
 Flux_helium_daisy1->Scale(1.0,"width");
 Flux_helium_daisy2->Scale(1.0,"width");
 Flux_helium_daisy3->Scale(1.0,"width");
 Flux_helium_daisy4->Scale(1.0,"width");
 Flux_helium_daisy5->Scale(1.0,"width");
 Flux_helium_daisy6->Scale(1.0,"width");
 Flux_helium_daisy7->Scale(1.0,"width");
 Flux_helium_daisy8->Scale(1.0,"width");
 Flux_helium_daisy9->Scale(1.0,"width");
 Flux_helium_daisy10->Scale(1.0,"width");
 Flux_helium_daisy11->Scale(1.0,"width");


auto Flux_tracker_daisy0 = Get1DHist(*TFile_Flux_tracker_daisy0,"flux_rebined");
auto Flux_tracker_daisy1 = Get1DHist(*TFile_Flux_tracker_daisy1,"flux_rebined");
auto Flux_tracker_daisy2 = Get1DHist(*TFile_Flux_tracker_daisy2,"flux_rebined");
auto Flux_tracker_daisy3 = Get1DHist(*TFile_Flux_tracker_daisy3,"flux_rebined");
auto Flux_tracker_daisy4 = Get1DHist(*TFile_Flux_tracker_daisy4,"flux_rebined");
auto Flux_tracker_daisy5 = Get1DHist(*TFile_Flux_tracker_daisy5,"flux_rebined");
auto Flux_tracker_daisy6 = Get1DHist(*TFile_Flux_tracker_daisy6,"flux_rebined");
auto Flux_tracker_daisy7 = Get1DHist(*TFile_Flux_tracker_daisy7,"flux_rebined");
auto Flux_tracker_daisy8 = Get1DHist(*TFile_Flux_tracker_daisy8,"flux_rebined");
auto Flux_tracker_daisy9 = Get1DHist(*TFile_Flux_tracker_daisy9,"flux_rebined");
auto Flux_tracker_daisy10 = Get1DHist(*TFile_Flux_tracker_daisy10,"flux_rebined");
auto Flux_tracker_daisy11 = Get1DHist(*TFile_Flux_tracker_daisy11,"flux_rebined");



auto Flux_helium = Get1DHist(*TFile_Flux_helium,"flux_rebined");
auto Flux_helium_manybins = Get1DHist(*TFile_Flux_helium,"flux");
//auto Flux_helium_th1d = GetTH1DHist(*TFile_Flux_helium,"flux");
auto Flux_helium_slice1_1 = Get1DHist(*TFile_Flux_helium_slice1,"flux_rebined");
auto Flux_helium_slice2_1 = Get1DHist(*TFile_Flux_helium_slice2,"flux_rebined");
auto Flux_helium_slice3_1 = Get1DHist(*TFile_Flux_helium_slice3,"flux_rebined");
auto Flux_helium_slice4_1 = Get1DHist(*TFile_Flux_helium_slice4,"flux_rebined");

UnBinWidthNormalizeMnvH1D(*Flux_helium_slice1_1);
UnBinWidthNormalizeMnvH1D(*Flux_helium_slice2_1);
UnBinWidthNormalizeMnvH1D(*Flux_helium_slice3_1);
UnBinWidthNormalizeMnvH1D(*Flux_helium_slice4_1);

PlotUtils::MnvH1D* Flux_helium_slice1 = RebinMnvH1D(Flux_helium_slice1_1,newbins);
PlotUtils::MnvH1D* Flux_helium_slice2 = RebinMnvH1D(Flux_helium_slice2_1,newbins);
PlotUtils::MnvH1D* Flux_helium_slice3 = RebinMnvH1D(Flux_helium_slice3_1,newbins);
PlotUtils::MnvH1D* Flux_helium_slice4 = RebinMnvH1D(Flux_helium_slice4_1,newbins);
Flux_helium_slice1->Scale(1.0,"width");
Flux_helium_slice2->Scale(1.0,"width");
Flux_helium_slice3->Scale(1.0,"width");
Flux_helium_slice4->Scale(1.0,"width");


//Flux_helium_slice1->Divide(Flux_helium_slice1,Flux_helium_th1d);
//Flux_helium_slice2->Divide(Flux_helium_slice1,Flux_helium_th1d);
//Flux_helium_slice3->Divide(Flux_helium_slice1,Flux_helium_th1d);
//Flux_helium_slice4->Divide(Flux_helium_slice1,Flux_helium_th1d);
//Flux_helium_th1d->Divide(Flux_helium_th1d,Flux_helium_th1d);
//TFile *TFile_Flux_Tracker_homebrew = new TFile(PlaylistME_Flux_Tracker_homebrew);
//TFile *TFile_Flux_Tracker = new TFile(PlaylistME_Flux_Tracker_homebrew);
TFile *TFile_Flux_Tracker_git = new TFile(PlaylistME_Flux_tracker_git);

TFile *TFile_Flux_Tracker_slice1 = new TFile(PlaylistME_Flux_tracker_slice1);
TFile *TFile_Flux_Tracker_slice2 = new TFile(PlaylistME_Flux_tracker_slice2);
TFile *TFile_Flux_Tracker_slice3 = new TFile(PlaylistME_Flux_tracker_slice3);
TFile *TFile_Flux_Tracker_slice4 = new TFile(PlaylistME_Flux_tracker_slice4);
auto PlaylistRemake = "/minerva/data/users/cnguyen/ME_Flux/flux_tracker_tracker_remake.root";
TFile *TFile_Flux_Tracker_remake = new TFile(PlaylistRemake);
std::cout<<"pass5"<<std::endl;

//auto Flux_Tracker_remake = Get1DHist(*TFile_Flux_Tracker_remake,"flux");

//auto Flux_Tracker_rebin = Get1DHist(*TFile_Flux_Tracker_homebrew,"flux_rebined");
auto Flux_Tracker = Get1DHist(*TFile_Flux_Tracker_git,"flux");

//auto Flux_Tracker_homebrew = Get1DHist(*TFile_Flux_Tracker_homebrew,"flux_rebined");
//auto Flux_Tracker_homebrew2 = Get1DHist(*TFile_Flux_Tracker_homebrew,"flux");
std::cout<<"pass6"<<std::endl;
auto Flux_Tracker_slice1 = Get1DHist(*TFile_Flux_Tracker_slice1,"flux_rebined");
auto Flux_Tracker_slice2 = Get1DHist(*TFile_Flux_Tracker_slice2,"flux_rebined");
auto Flux_Tracker_slice3 = Get1DHist(*TFile_Flux_Tracker_slice3,"flux_rebined");
auto Flux_Tracker_slice4 = Get1DHist(*TFile_Flux_Tracker_slice4,"flux_rebined");




TFile *TFile_Flux_helium_vertexX = new TFile(PlaylistME_CrossSection_fluxhelium_vertexX);
TFile *TFile_Flux_helium_vertexY = new TFile(PlaylistME_CrossSection_fluxhelium_vertexY);

auto TFile_Flux_tracker_NuEvspatal_name = "/minerva/data2/users/anezkak/2022/fluxFinal/Neutrinos/separated/flux_tracker.root";
TFile *TFile_Flux_tracker_NuEvspatal = new TFile(TFile_Flux_tracker_NuEvspatal_name);


auto TFile_Flux_tracker_NuEvspatal_name_inhouse = "/minerva/data/users/cnguyen/ME_Flux/flux_tracker_inhouse_tracker_patal2DFlux.root";//"/minerva/data/users/cnguyen/ME_Flux/flux_tracker_Daisy2DFlux.root";
TFile *TFile_Flux_tracker_NuEvspatal_inhouse = new TFile(TFile_Flux_tracker_NuEvspatal_name_inhouse);



auto Flux_Tracker_1   = (MnvH1D *)Flux_Tracker->Clone("Flux_Tracker_1");
auto Flux_Tracker_Ratio   = (MnvH1D *)Flux_Tracker->Clone("Flux_Tracker_Ratio");
UnBinWidthNormalizeMnvH1D(*Flux_Tracker_1);
PlotUtils::MnvH1D* Flux_Tracker_rebin = RebinMnvH1D(Flux_Tracker_1, newbins);

PlotUtils::MnvH1D* Flux_Tracker_rebin_petals = RebinMnvH1D(Flux_Tracker_1, binsforweights);


Flux_Tracker_rebin->Scale(1.0,"width");
Flux_Tracker_rebin_petals->Scale(1.0,"width");

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





sprintf(text_title_pdf1, "PLOTS_%s_FluxFits_helium_log_flux.pdf(","" );
can -> Print(text_title_pdf1);
sprintf(text_title_pdf2, "PLOTS_%s_FluxFits_helium_log_flux.pdf","" );
sprintf(text_title_pdf3, "PLOTS_%s_FluxFits_helium_log_flux.pdf)","" );
sprintf(text_title_pdf4, "PLOTS_%s_FluxFits_helium_log_flux","" );
 pdf_CV = string(text_title_pdf4);

  std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;
  std::cout<< "  Ploting 1D Cross Section "<< std::endl;
  std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;




std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~       Starting Plotter: Kinematic Plots         ~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

TFile *TFile_CrossSection_tracker = new TFile(PlaylistME_CrossSection_MasterAnaDevPath);
TFile *TFile_CrossSection_helium = new TFile(PlaylistME_CrossSection_Path);
TFile *TFile_CrossSection_heliumFlux = new TFile(PlaylistME_CrossSection_Path);
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
std::cout<<"Mid point of Cryotank" << GetMidPointCryoTank()<< std::endl;

//auto EuvsVertexX = Get2DHist(*TFile_CrossSection_helium,"h2d_Enu_TRUE_vertex_X_reduced");
//auto EuvsVertexY = Get2DHist(*TFile_CrossSection_helium,"h2d_Enu_TRUE_vertex_Y_reduced");

auto EuvsVertexX = Get2DHist(*TFile_Flux_helium_vertexX,"flux_2d");
auto EuvsVertexY = Get2DHist(*TFile_Flux_helium_vertexY,"flux_2d");


auto EuvsVertexX_Herate = Get2DHist(*TFile_CrossSection_helium,"h2d_Enu_TRUE_vertex_X_reduced");
auto EuvsVertexY_Herate = Get2DHist(*TFile_CrossSection_helium,"h2d_Enu_TRUE_vertex_Y_reduced");

auto EuvsVertexX_CHrate = Get2DHist(*TFile_CrossSection_tracker,"h2d_Enu_TRUE_vertex_X_reduced1");
auto EuvsVertexY_CHrate = Get2DHist(*TFile_CrossSection_tracker,"h2d_Enu_TRUE_vertex_Y_reduced1");





auto Tracker_vs_patal = Get2DHist(*TFile_Flux_tracker_NuEvspatal,"flux_2d");

//auto Tracker_vs_patal = rebinXAxis(Tracker_vs_patal_1, binsforweights);


auto Tracker_vs_patal_inhouse = Get2DHist(*TFile_Flux_tracker_NuEvspatal_inhouse,"flux_2d");
//auto Tracker_vs_patal_inhouse = rebinXAxis(Tracker_vs_patal_inhouse_1, binsforweights);


std::vector<double> newBins =  generateXAxisBins();

//auto EuvsVertexX =rebinXAxis(EuvsVertexX_input, newBins);
//auto EuvsVertexY =rebinXAxis(EuvsVertexY_input, newBins);


Draw2DHist(EuvsVertexX, "E_{#nu} [GeV]", "Vertex X [mm]", "#nu / m^2 / POT / GeV" , "helium" , text_title_pdf2, can,mnv_plot);
Draw2DHist(EuvsVertexY, "E_{#nu} [GeV]", "Vertex Y [mm]", "#nu / m^2 / POT / GeV" , "helium" , text_title_pdf2, can,mnv_plot);

Draw2DHist(EuvsVertexX_Herate, "E_{#nu} [GeV]", "Vertex X [mm]", "NEvents" , "Helium" , text_title_pdf2, can,mnv_plot);
Draw2DHist(EuvsVertexY_Herate, "E_{#nu} [GeV]", "Vertex Y [mm]", "NEvents" , "Helium" , text_title_pdf2, can,mnv_plot);

Draw2DHist(EuvsVertexX_CHrate, "E_{#nu} [GeV]", "Vertex X [mm]", "NEvents" , "Tracker" , text_title_pdf2, can,mnv_plot);
Draw2DHist(EuvsVertexY_CHrate, "E_{#nu} [GeV]", "Vertex Y [mm]", "NEvents" , "Tracker" , text_title_pdf2, can,mnv_plot);




TH2D EuvsVertexX_th1d = EuvsVertexX->GetCVHistoWithStatError();
TH2D EuvsVertexY_th1d = EuvsVertexY->GetCVHistoWithStatError();

TH2D *histpointerA = &EuvsVertexX_th1d;
TH2D *histpointerB = &EuvsVertexY_th1d;

//std::vector<double> para_vector{296.075,6.08259,1.81076,4.39108,386.319,296.436,1.80762,12.6798,384.758}; // got from fit
//std::vector<double> wgt_error_vector{0.311362 ,0.000980123, 0.000870514, 0.30624, 0.294206, 0.317199, 0.00100436, 0.342542, 0.28184}; // got from fit
std::vector<TGraph*> outputTGraphs;
std::vector<double> para_vector;
std::vector<double> wgt_error_vector;
double chi2 = 9999; //435226;

//std::vector<double> para_vector{292.856,6.18073,1.83031, 5.0862,385.824,217.089,2.96047,9.06537,347.303};
//std::vector<double> wgt_error_vector{0.2946640,.00113269,0.000960875,0.349156,0.285165,0.240458,0.00179219,0.272949,0.19685};

int EuvsVertexX_N_Xbins  = EuvsVertexX_th1d.GetNbinsX();
int EuvsVertexX_N_Ybins  = EuvsVertexX_th1d.GetNbinsY();

int EuvsVertexY_N_Xbins  = EuvsVertexY_th1d.GetNbinsX();
int EuvsVertexY_N_Ybins  = EuvsVertexY_th1d.GetNbinsY();

double ndf = EuvsVertexX_N_Xbins * EuvsVertexX_N_Ybins + EuvsVertexY_N_Xbins * EuvsVertexY_N_Ybins;
double ndf_fit = ndf - 9;
//Fit2Dhist(histpointerA, histpointerB, para_vector, wgt_error_vector, chi2, outputTGraphs );
//int count=0;
//std::ofstream myfile;
//myfile.open("GaussianFit_joint_helium_log_flux.txt");
//for(int i=0; i < para_vector.size(); i++  ){
//  myfile <<"index: "<< count<< "pars : " <<  para_vector.at(i) <<"   Error :" <<  wgt_error_vector.at(i)<< std::endl;
//count++;
//}


// Draw2DHist_warpFit2DGaussian(EuvsVertexX, "E_{#nu} [GeV]","Vertex X [mm]", chi2, ndf_fit,
//  para_vector.at(0),para_vector.at(1),para_vector.at(2),para_vector.at(3),para_vector.at(4),
//   wgt_error_vector.at(0),wgt_error_vector.at(1),wgt_error_vector.at(2),wgt_error_vector.at(3),wgt_error_vector.at(4),
//    "Joint Fit Vertex X [from Flux] [Helium][log #chi^{2}]", text_title_pdf2, can,mnv_plot);
//
//Draw2DHist_warpFit2DGaussian(EuvsVertexY, "E_{#nu} [GeV]","Vertex Y [mm]", chi2, ndf_fit,
//     para_vector.at(5),para_vector.at(1),para_vector.at(6),para_vector.at(7),para_vector.at(8),
//      wgt_error_vector.at(5),wgt_error_vector.at(1),wgt_error_vector.at(6),wgt_error_vector.at(7),wgt_error_vector.at(8),
//       "Joint Fit Vertex Y [from Flux][Helium][log #chi^{2}]", text_title_pdf2, can,mnv_plot);
//


std::vector<double> Mean_Y_EuvsVertexX = calculateMeanValues(EuvsVertexX_Herate);
std::vector<double> Mean_Y_EuvsVertexY = calculateMeanValues(EuvsVertexY_Herate);
std::vector<double> Bins_EuvsVertexX = extractXBins(EuvsVertexX_Herate);

std::vector<double> Mean_Y_EuvsVertexX_CH = calculateMeanValues(EuvsVertexX_CHrate);
std::vector<double> Mean_Y_EuvsVertexY_CH = calculateMeanValues(EuvsVertexY_CHrate);
std::vector<double> Bins_EuvsVertexX_CH = extractXBins(EuvsVertexX_CHrate);


removeFirstNElements(Mean_Y_EuvsVertexX,15);
removeFirstNElements(Mean_Y_EuvsVertexY,15);
removeFirstNElements(Bins_EuvsVertexX,15);

removeFirstNElements(Mean_Y_EuvsVertexX_CH,15);
removeFirstNElements(Mean_Y_EuvsVertexY_CH,15);
removeFirstNElements(Bins_EuvsVertexX_CH,15);

for(int i =0 ; i < Bins_EuvsVertexX.size();i++)
{

std::cout<<"Mean = " <<Mean_Y_EuvsVertexX.at(i) << "   bin:  "<<  Bins_EuvsVertexX.at(i)<<std::endl;

}





TGraph *g_TGraph_EuvsVertexY = createTGraph(Bins_EuvsVertexX,Mean_Y_EuvsVertexY);
TGraph *g_TGraph_EuvsVertexX =createTGraph(Bins_EuvsVertexX,Mean_Y_EuvsVertexX);

TGraph *g_TGraph_EuvsVertexY_CH = createTGraph(Bins_EuvsVertexX_CH,Mean_Y_EuvsVertexY_CH);
TGraph *g_TGraph_EuvsVertexX_CH =createTGraph(Bins_EuvsVertexX_CH,Mean_Y_EuvsVertexX_CH);

//DrawTGraph(g_TGraph_EuvsVertexX, "#nu / m^2 / POT / GeV","Mean Vertex X",
//           "Mean Values of Vertex X for Helium for Flux", "", text_title_pdf2, can,mnv_plot, false, false );

//std::vector<double> Mean_Y_EuvsVertexY = calculateMeanValues(EuvsVertexY);

//TGraph *g_TGraph_EuvsVertexY =createTGraph(Bins_EuvsVertexX ,Mean_Y_EuvsVertexY);

//TGraph *g_TGraph_EuvsVertexY = MakeTGraph_NOERRORS_from_Vectors(Mean_Y_EuvsVertexY,Bins_EuvsVertexX);
DrawTGraph(g_TGraph_EuvsVertexY, "E_{#nu}","Mean Vertex Y",
"Mean Values of Vertex Y for Helium for Flux", "", text_title_pdf2, can,mnv_plot, false, false );

DrawTGraph_GaussianFit(g_TGraph_EuvsVertexY, "E_{#nu}","Mean Vertex Y",
"Mean Values of Vertex Y for Helium for Flux", "", text_title_pdf2, can,mnv_plot, false, false,4.5,12 );

DrawTGraph(g_TGraph_EuvsVertexX, "E_{#nu}","Mean Vertex X",
"Mean Values of Vertex X for Helium for Flux", "", text_title_pdf2, can,mnv_plot, false, false );

DrawTGraph_GaussianFit(g_TGraph_EuvsVertexX, "E_{#nu}","Mean Vertex X",
"Mean Values of Vertex X for Helium for Flux", "", text_title_pdf2, can,mnv_plot, false, false,4.5,12 );

/////////

DrawTGraph(g_TGraph_EuvsVertexY_CH, "E_{#nu}","Mean Vertex Y",
"Mean Values of Vertex Y for Tracker for Flux", "", text_title_pdf2, can,mnv_plot, false, false );

DrawTGraph_GaussianFit(g_TGraph_EuvsVertexY_CH, "E_{#nu}","Mean Vertex Y",
"Mean Values of Vertex Y for Tracker for Flux", "", text_title_pdf2, can,mnv_plot, false, false,4.5,12 );

DrawTGraph(g_TGraph_EuvsVertexX_CH, "E_{#nu}","Mean Vertex X",
"Mean Values of Vertex X for Tracker for Flux", "", text_title_pdf2, can,mnv_plot, false, false );

DrawTGraph_GaussianFit(g_TGraph_EuvsVertexX_CH, "E_{#nu}","Mean Vertex X",
"Mean Values of Vertex X for Tracker for Flux", "", text_title_pdf2, can,mnv_plot, false, false,4.5,12 );


//double area_Hex = EuvsVertexX_Herate->Integral();
//double area_Hey = EuvsVertexY_Herate->Integral();
//
//double area_CHx = EuvsVertexX_CHrate->Integral();
//double area_CHy = EuvsVertexY_CHrate->Integral();
//
//EuvsVertexX_CHrate->Scale(1/area_CHx);
//EuvsVertexY_CHrate->Scale(1/area_CHy);
//
//EuvsVertexX_Herate->Scale(1/area_Hex);
//EuvsVertexY_Herate->Scale(1/area_Hey);

EuvsVertexX_Herate->Divide(EuvsVertexX_Herate, EuvsVertexX_CHrate);
EuvsVertexY_Herate->Divide(EuvsVertexY_Herate, EuvsVertexY_CHrate);


Draw2DHist(EuvsVertexX_Herate, "E_{#nu} [GeV]", "Vertex X [mm]", "Ratio He/CH" , "" , text_title_pdf2, can,mnv_plot);
Draw2DHist(EuvsVertexY_Herate, "E_{#nu} [GeV]", "Vertex Y [mm]", "Ratio He/CH" , "" , text_title_pdf2, can,mnv_plot);


std::vector<double> Mean_Y_EuvsVertexX_ratio = calculateMeanValues(EuvsVertexX_Herate);
std::vector<double> Mean_Y_EuvsVertexY_ratio = calculateMeanValues(EuvsVertexY_Herate);
std::vector<double> Bins_EuvsVertexX_ratio = extractXBins(EuvsVertexX_Herate);

removeFirstNElements(Mean_Y_EuvsVertexX_ratio,15);
removeFirstNElements(Mean_Y_EuvsVertexY_ratio,15);
removeFirstNElements(Bins_EuvsVertexX_ratio,15);

TGraph *g_TGraph_EuvsVertexY_ratio = createTGraph(Bins_EuvsVertexX_ratio,Mean_Y_EuvsVertexY_ratio);
TGraph *g_TGraph_EuvsVertexX_ratio =createTGraph(Bins_EuvsVertexX_ratio,Mean_Y_EuvsVertexX_ratio);


DrawTGraph(g_TGraph_EuvsVertexY_ratio, "E_{#nu}","Mean Vertex Y",
"Ratio He/ CH Mean Values of Vertex Y for Tracker for Flux", "", text_title_pdf2, can,mnv_plot, false, false );

DrawTGraph_GaussianFit(g_TGraph_EuvsVertexY_ratio, "E_{#nu}","Mean Vertex Y",
"Ratio He/ CH Mean Values of Vertex Y for Tracker for Flux", "", text_title_pdf2, can,mnv_plot, false, false,4.5,12 );

DrawTGraph(g_TGraph_EuvsVertexX_ratio, "E_{#nu}","Mean Vertex X",
"Ratio He/ CH Mean Values of Vertex X for Tracker for Flux", "", text_title_pdf2, can,mnv_plot, false, false );

DrawTGraph_GaussianFit(g_TGraph_EuvsVertexX_ratio, "E_{#nu}","Mean Vertex X",
"Ratio He/ CH Mean Values of Vertex Y and Flux", "", text_title_pdf2, can,mnv_plot, false, false,4.5,12 );





DrawCVAndError_From6HIST(Flux_Tracker_rebin, "Tracker",
Flux_helium, "Helium Flux",
Flux_helium_slice1,"Helium Flux slice 1",
Flux_helium_slice2,"Helium Flux slice 2",
Flux_helium_slice3,"Helium Flux slice 3",
Flux_helium_slice4,"Helium Flux slice 4",
"Flux" ,"E_{#nu} [GeV]", "#nu / m^2 / POT / GeV",
pdf_CV, true, false , false , DontBinWidthNorm, .0001,  false,   false);





//DrawCVAndError_FromHIST(true ,Flux_Tracker, "Tracker Flux check " ,"Flux","Event/[GeV]", pdf_CV,true,true, false, -99,-99);
/*
auto names  = Flux_helium_daisy8_morebins->GetErrorBandNames();

for(auto name:names){
std::cout<<"Band Names : "<< name<<std::endl;

}
*/

//DrawCVAndError_FromHIST(true ,Flux_helium_daisy8_morebins, "Daisy8" ,"Flux","Event/[GeV]", pdf_CV,true,true, false, -99,-99);

DrawCVAndError_FromDaisyHIST(Flux_Tracker_rebin, "Tracker" ,
                                    Flux_helium_daisy0, "Helium daisy 0" ,
                                  Flux_helium_daisy1, "Helium daisy 1" ,
                                  Flux_helium_daisy2,"Helium daisy 2",
                                  Flux_helium_daisy3,"Helium daisy 3",
                                  Flux_helium_daisy4,"Helium daisy 4",
                                  Flux_helium_daisy5,"Helium daisy 5",
                                  Flux_helium_daisy6,"Helium daisy 6",
                                  Flux_helium_daisy7,"Helium daisy 7",
                                  Flux_helium_daisy8,"Helium daisy 8",
                                  Flux_helium_daisy9,"Helium daisy 9",
                                   Flux_helium_daisy10,"Helium daisy 10",
                                  Flux_helium_daisy11,"Helium daisy 11",
    "Flux Helium Daisy " ,"E_{#nu} [GeV]", "#nu / m^2 / POT / GeV",
      pdf_CV, true,DontBinWidthNorm, .0001 , false,  false );



Flux_helium_slice1->Divide(Flux_helium_slice1,Flux_Tracker_rebin);
Flux_helium_slice2->Divide(Flux_helium_slice2,Flux_Tracker_rebin);
Flux_helium_slice3->Divide(Flux_helium_slice3,Flux_Tracker_rebin);
Flux_helium_slice4->Divide(Flux_helium_slice4,Flux_Tracker_rebin);
//
Flux_helium_daisy0->Divide(Flux_helium_daisy0,Flux_Tracker_rebin);
Flux_helium_daisy1->Divide(Flux_helium_daisy1,Flux_Tracker_rebin);
Flux_helium_daisy2->Divide(Flux_helium_daisy2,Flux_Tracker_rebin);
Flux_helium_daisy3->Divide(Flux_helium_daisy3,Flux_Tracker_rebin);
Flux_helium_daisy4->Divide(Flux_helium_daisy4,Flux_Tracker_rebin);
Flux_helium_daisy5->Divide(Flux_helium_daisy5,Flux_Tracker_rebin);
Flux_helium_daisy6->Divide(Flux_helium_daisy6,Flux_Tracker_rebin);
Flux_helium_daisy7->Divide(Flux_helium_daisy7,Flux_Tracker_rebin);
Flux_helium_daisy8->Divide(Flux_helium_daisy8,Flux_Tracker_rebin);
Flux_helium_daisy9->Divide(Flux_helium_daisy9,Flux_Tracker_rebin);
Flux_helium_daisy10->Divide(Flux_helium_daisy10,Flux_Tracker_rebin);
Flux_helium_daisy11->Divide(Flux_helium_daisy11,Flux_Tracker_rebin);


std::cout<<" N bins Helium" << Flux_helium->GetNbinsX()<<std::endl;
//std::cout<<" N bins tracker" << Flux_Tracker_homebrew->GetNbinsX()<<std::endl;

auto Flux_Tracker_clone   = (MnvH1D *)Flux_Tracker->Clone("Flux_Tracker_clone");

auto Flux_Tracker_clone2   = (MnvH1D *)Flux_Tracker->Clone("Flux_Tracker_clone2");
auto Flux_helium_manybins_clone   = (MnvH1D *)Flux_helium_manybins->Clone("Flux_helium_manybins_clone");




UnBinWidthNormalizeMnvH1D(*Flux_Tracker_clone2);
UnBinWidthNormalizeMnvH1D(*Flux_helium_manybins_clone);
PlotUtils::MnvH1D* Flux_Tracker_clone2_rebin = RebinMnvH1D(Flux_Tracker_clone2, newbins);
PlotUtils::MnvH1D* Flux_Tracker_clone2_rebin_new = RebinMnvH1D(Flux_Tracker_clone2, binsforweights);
PlotUtils::MnvH1D* Flux_Tracker_course = RebinMnvH1D(Flux_Tracker_clone2, Vector_bins);
Flux_Tracker_clone2_rebin->Scale(1.0,"width");
auto Flux_Tracker_clone2_rebin1   = (MnvH1D *)Flux_Tracker_clone2_rebin->Clone("Flux_Tracker_clone2_rebin1");

//Flux_Tracker_clone2_rebin_new->Scale(1.0,"width");

PlotUtils::MnvH1D* Flux_helium_manybins_clone_rebin = RebinMnvH1D(Flux_helium_manybins_clone, binsforweights);
//Flux_helium_manybins_clone_rebin->Scale(1.0,"width");


Draw2DHist(Tracker_vs_patal, "E_{#nu} [GeV]", "Daisy Number", "Flux" , " " , text_title_pdf2, can,mnv_plot);
Draw2DHist(Tracker_vs_patal_inhouse, "E_{#nu} [GeV]", "Daisy Number", "Flux" , " inhouse" , text_title_pdf2, can,mnv_plot);

auto Tracker_vs_patal_inhouse_clone = (PlotUtils::MnvH2D*)Tracker_vs_patal_inhouse->Clone("Tracker_vs_patal_inhouse_clone");


Tracker_vs_patal_inhouse_clone->Divide(Tracker_vs_patal_inhouse_clone,Tracker_vs_patal);

Draw2DHist(Tracker_vs_patal_inhouse_clone, "E_{#nu} [GeV]", "Daisy Number", "Flux" , " Ratio" , text_title_pdf2, can,mnv_plot);

TH2D *inputTracker_vs_patal   = (TH2D *)Tracker_vs_patal->Clone("inputTracker_vs_patal");
TH2D *inputTracker_vs_patal_inhouse   = (TH2D *)Tracker_vs_patal_inhouse->Clone("inputTracker_vs_patal_inhouse");


auto ybins_inhouse = get_y_bin_edges(inputTracker_vs_patal_inhouse);
auto ybins = get_y_bin_edges(Tracker_vs_patal);


std::cout<<"inhouse bins"<< std::endl;
for(auto yb:ybins_inhouse){std::cout<<"bin"<<yb<<std::endl;}

std::cout<<" bins"<< std::endl;

for(auto yb:ybins){std::cout<<"bin"<<yb<<std::endl;}
//Tracker_vs_patal_inhouse->Divide(Tracker_vs_patal_inhouse, Tracker_vs_patal);

//Draw2DHist(Tracker_vs_patal_inhouse, "E_{#nu} [GeV]", "Daisy Number", "Flux" , " inhouse /  Anezkak ratio" , text_title_pdf2, can,mnv_plot);

auto PlaylistME_CrossSection_reweighted = " CrossSection_MasterAnaDev_DAISY.root";
TFile *TFile_ME_reweighted = new TFile(PlaylistME_CrossSection_reweighted);
auto TrackerFlux_reweighted = Get1DHist(*TFile_ME_reweighted,"Tracker_Flux_reweighted");
TrackerFlux_reweighted->GetXaxis()->SetRangeUser(0.0,20.0);
auto Flux_helium_manybins_clone3   = (MnvH1D *)Flux_helium_manybins->Clone("Flux_helium_manybins_clone3");
Flux_helium_manybins_clone3->GetXaxis()->SetRangeUser(0.0,20.0);
auto Flux_helium_manybins_clone4 = (MnvH1D *)Flux_helium_manybins->Clone("Flux_helium_manybins_clone4");
auto Flux_helium_manybins_clone5 = (MnvH1D *)Flux_helium_manybins->Clone("Flux_helium_manybins_clone5");

MnvH1D *TrackerFlux_reweighted_clone   = (MnvH1D *)TrackerFlux_reweighted->Clone("TrackerFlux_reweighted_clone");


DrawCVAndError_From2HIST_test(Flux_helium_manybins, "Helium" ,Flux_Tracker_clone, "Tracker",  "Flux Ratio " ,"E_{#nu} [GeV]", "^{4}He flux / CH flux",
pdf_CV, true,  DontBinWidthNorm, -99, -99 , false );

Flux_helium_manybins->Divide(Flux_helium_manybins,Flux_Tracker_clone);
Flux_Tracker_clone->Divide(Flux_Tracker_clone,Flux_Tracker_clone);

DrawCVAndError_From2HIST_test(Flux_helium_manybins, "Helium" ,Flux_Tracker_clone, "Tracker",  "Flux Ratio " ,"E_{#nu} [GeV]", "^{4}He flux / CH flux",
pdf_CV, true,  DontBinWidthNorm, 1.25, .85 , false );
///////////////////////////////////////////////////////

DrawCVAndError_From2HIST_test(Flux_helium_manybins_clone4, "Helium" ,TrackerFlux_reweighted, "Tracker reweighted",  "Flux Ratio " ,"E_{#nu} [GeV]", "^{4}He flux / CH flux",
pdf_CV, true,  DontBinWidthNorm, -99, -99 , false );

Flux_helium_manybins_clone4->Divide(Flux_helium_manybins_clone4,TrackerFlux_reweighted);
TrackerFlux_reweighted->Divide(TrackerFlux_reweighted,TrackerFlux_reweighted);

DrawCVAndError_From2HIST_test(Flux_helium_manybins_clone4, "Helium" ,TrackerFlux_reweighted, "Tracker reweighted",  "Flux Ratio " ,"E_{#nu} [GeV]", "^{4}He flux / CH flux",
pdf_CV, true,  DontBinWidthNorm, 1.25, .85 , false );

/////////////////////////////////////////////////////
//Wide bins
/////////////////////////////////////////////////
UnBinWidthNormalizeMnvH1D(*TrackerFlux_reweighted_clone);
PlotUtils::MnvH1D* TrackerFlux_reweighted_rebin = RebinMnvH1D(TrackerFlux_reweighted_clone, binsforweights);
TrackerFlux_reweighted_rebin->Scale(1.0,"width");

UnBinWidthNormalizeMnvH1D(*Flux_helium_manybins_clone5);
PlotUtils::MnvH1D* Flux_helium_manybins_clone5_rebin = RebinMnvH1D(Flux_helium_manybins_clone5, binsforweights);
Flux_helium_manybins_clone5_rebin->Scale(1.0,"width");

UnBinWidthNormalizeMnvH1D(*Flux_helium_manybins_clone3);
PlotUtils::MnvH1D* Flux_helium_manybins_clone3_rebin = RebinMnvH1D(Flux_helium_manybins_clone3, binsforweights);
Flux_helium_manybins_clone3_rebin->Scale(1.0,"width");


DrawCVAndError_From2HIST_test(Flux_helium_manybins_clone5_rebin, "Helium" ,  Flux_Tracker_clone2_rebin1, "Tracker",  "Flux Ratio " ,"E_{#nu} [GeV]", "^{4}He flux / CH flux",
pdf_CV, true,  DontBinWidthNorm, -99, -99 , false );


Flux_helium_manybins_clone5_rebin->Divide(Flux_helium_manybins_clone5_rebin,Flux_Tracker_clone2_rebin1);
Flux_Tracker_clone2_rebin1->Divide(Flux_Tracker_clone2_rebin1,Flux_Tracker_clone2_rebin1);

DrawCVAndError_From2HIST_test(Flux_helium_manybins_clone5_rebin, "Helium" ,Flux_Tracker_clone2_rebin1, "Tracker",  "Flux Ratio " ,"E_{#nu} [GeV]", "^{4}He flux / CH flux",
pdf_CV, true,  DontBinWidthNorm, 1.25, .85 , false );

///////////////////////////////////////////////////////

DrawCVAndError_From2HIST_test(Flux_helium_manybins_clone3_rebin, "Helium" ,TrackerFlux_reweighted_rebin, "Tracker reweighted",  "Flux Ratio " ,"E_{#nu} [GeV]", "^{4}He flux / CH flux",
pdf_CV, true,  DontBinWidthNorm, -99, -99 , false );

Flux_helium_manybins_clone3_rebin->Divide(Flux_helium_manybins_clone3_rebin,TrackerFlux_reweighted_rebin);
TrackerFlux_reweighted_rebin->Divide(TrackerFlux_reweighted_rebin,TrackerFlux_reweighted_rebin);

DrawCVAndError_From2HIST_test(Flux_helium_manybins_clone3_rebin, "Helium" ,TrackerFlux_reweighted_rebin, "Tracker reweighted",  "Flux Ratio " ,"E_{#nu} [GeV]", "^{4}He flux / CH flux",
pdf_CV, true,  DontBinWidthNorm, 1.25, .85 , false );


///////////////////////////////////////////////////////

  DrawCVAndError_From2HIST_test(Flux_Tracker_clone2_rebin, "Flux_Tracker_clone2_rebin" ,Flux_helium_manybins_clone_rebin, "Flux_helium_manybins_clone_rebin",  "Flux Ratio " ,"E_{#nu} [GeV]", "^{4}He flux / CH flux",
  pdf_CV, true,  DontBinWidthNorm, -99, -99 , false );
auto Flux_helium_manybins_clone2 = (MnvH1D *)Flux_helium_manybins_clone_rebin->Clone("Flux_helium_manybins_clone2");
  Flux_helium_manybins_clone_rebin->Divide(Flux_helium_manybins_clone_rebin,Flux_Tracker_clone2_rebin);
  Flux_Tracker_clone2_rebin->Divide(Flux_Tracker_clone2_rebin,Flux_Tracker_clone2_rebin);

  DrawCVAndError_From2HIST_test(Flux_Tracker_clone2_rebin, "Flux_Tracker_clone2_rebin" ,Flux_helium_manybins_clone_rebin, "Flux_helium_manybins_clone_rebin",  "Flux Ratio " ,"E_{#nu} [GeV]", "^{4}He flux / CH flux",
  pdf_CV, true,  DontBinWidthNorm, 1.25, .85 , false );







auto NuMu_Rate = Get1DHist(*TFile_CrossSection_helium,"h_Enu_helium_TRUE");
auto inhouseFlux = MakeFluxHist(NuMu_Rate, "helium", 1.42245e+29 / 4.0, 4.75655e+21);

MnvH1D*inputFluxForrFit_helium_mvnh1d   = (MnvH1D*)inhouseFlux->Clone("inputFluxForrFit_helium_mvnh1d");
inputFluxForrFit_helium_mvnh1d->GetXaxis()->SetRangeUser(0.0,20.0);
PlotUtils::MnvH1D* inhouseFlux_rebined = RebinMnvH1D(inhouseFlux, binsforweights);
inhouseFlux->GetXaxis()->SetRangeUser(0.0,20.0);
TH1D *inputFluxForrFit_helium   = (TH1D *)inhouseFlux->Clone("inputFluxForrFit_helium");


auto Fluxbinning_parth_course = "/minerva/app/users/cnguyen/cmtuser/Minerva_v22r1p1Helium_GIT/MATFluxAndReweightFiles/flux_daisy/neutrinos/targets_12345_jointNueIMD/out_iron_000100.root";
auto Fluxbinning_parth = "/minerva/app/users/cnguyen/cmtuser/Minerva_v22r1p1Helium_GIT/MATFluxAndReweightFiles/flux_daisy/neutrinos/targets_12345_jointNueIMD/flux_with_errors/flux_tracker.root";

TFile *TFile_binning = new TFile(Fluxbinning_parth);
auto h_fluxBinnng = Get1DHist(*TFile_binning,"rate");

TFile *TFile_binning_course = new TFile(Fluxbinning_parth_course);
auto h_fluxBinnng_course = Get1DHist(*TFile_binning_course,"flux");

std::cout<<"h_fluxBinnng Number of bins" << h_fluxBinnng->GetNbinsX()<<std::endl;
FluxReweighter FluxTool(14,true,"minervame1f",PlotUtils::FluxReweighter::gen2thin,PlotUtils::FluxReweighter::g4numiv6);

//FluxReweighter(int nuPDG,
//      bool applyNuEConstraint,
//      std::string playlist_str,
//      enum EFluxVersion fluxVersion,
//      enum EG4NumiVersion g4NumiVersion,
//      int nUniverses/*= 200*/)

MnvH1D* Helium_NuMu_Rate_towrite = FluxTool.GetRebinnedFluxReweighted_FromInputFlux(NuMu_Rate, h_fluxBinnng);
MnvH1D* Helium_Flux_towrite = FluxTool.GetRebinnedFluxReweighted_FromInputFlux(inhouseFlux, h_fluxBinnng);
MnvH1D* Helium_CrossSection =  GetCrossSection_hist(NuMu_Rate, "helium");
Helium_NuMu_Rate_towrite->GetXaxis()->SetRangeUser(0.0,20.0);
Helium_Flux_towrite->GetXaxis()->SetRangeUser(0.0,20.0);
Helium_CrossSection->GetXaxis()->SetRangeUser(0.0,20.0);
std::cout<<"Helium_NuMu_Rate_to write  Number of bins" << Helium_NuMu_Rate_towrite->GetNbinsX()<<std::endl;
auto outFile_flux = TFile::Open("flux_helium.root", "RECREATE");
outFile_flux->cd();
Helium_NuMu_Rate_towrite->Write("rate");
Helium_Flux_towrite->Write("flux");
Helium_CrossSection->Write("xsec");
outFile_flux->Close();

auto NuMu_Rate_anezkak = Get1DHist(*TFile_CrossSection_tracker,"h_Enu_tracker_Anezkak_TRUE");
//UnBinWidthNormalizeMnvH1D(*NuMu_Rate_anezkak);
auto NuMu_Rate_christian = Get1DHist(*TFile_CrossSection_tracker,"h_Enu_tracker_TRUE");




//NuMu_Rate_christian->Scale(1.0,"width");
TargetUtils TargetTool;
double NumberTracker_atoms = TargetTool.GetTrackerNCarbonAtoms(5890.0, 8467.0, true);

auto inhouseFlux_tracker_anezkak = MakeFluxHist(NuMu_Rate_anezkak, "tracker", NumberTracker_atoms, 4.88E+21);
auto inhouseFlux_tracker_christian = MakeFluxHist(NuMu_Rate_christian, "tracker", NumberTracker_atoms, 4.97204e+21);

inhouseFlux_tracker_christian->GetXaxis()->SetRangeUser(0.0,20.0);



MnvH1D* Tracker_NuMu_Rate_towrite = FluxTool.GetRebinnedFluxReweighted_FromInputFlux(NuMu_Rate_christian, h_fluxBinnng);
MnvH1D* Tracker_Flux_towrite = FluxTool.GetRebinnedFluxReweighted_FromInputFlux(inhouseFlux_tracker_christian, h_fluxBinnng);
MnvH1D* Tracker_CrossSection =  GetCrossSection_hist(NuMu_Rate_christian, "tracker");
Tracker_NuMu_Rate_towrite->GetXaxis()->SetRangeUser(0.0,20.0);
Tracker_Flux_towrite->GetXaxis()->SetRangeUser(0.0,20.0);
Tracker_CrossSection->GetXaxis()->SetRangeUser(0.0,20.0);

auto outFile_flux_tracker = TFile::Open("flux_tracker.root", "RECREATE");
outFile_flux_tracker->cd();
Tracker_NuMu_Rate_towrite->Write("rate");
Tracker_Flux_towrite->Write("flux");
Tracker_CrossSection->Write("xsec");
outFile_flux_tracker->Close();




MnvH1D* inputFluxForrFit_Tracker_mvnh1d   = (MnvH1D*)inhouseFlux_tracker_christian->Clone("inputFluxForrFit_Tracker_mvnh1d");

//PlotUtils::MnvH1D* inhouseFlux_tracker_christian_rebined = RebinMnvH1D(inhouseFlux_tracker_christian, binsforweights);
inhouseFlux_tracker_anezkak->GetXaxis()->SetRangeUser(0.0,20.0);
TH1D * inputFluxForrFit_Tracker   = (TH1D *)inhouseFlux_tracker_christian->Clone("inputFluxForrFit_Tracker");



inhouseFlux->GetXaxis()->SetRangeUser(0.0,20.0);
Flux_Tracker_Ratio->GetXaxis()->SetRangeUser(0.0,20.0);

//POT
// Number nucleons
////NuMu_Rate->Scale(1/NuMu_Rate->Integral());
NuMu_Rate->Scale(1.0,"width");
NuMu_Rate->GetXaxis()->SetRangeUser(0.0,20.0);
//DrawCVAndError_FromHIST(true , NuMu_Rate, "Total fiducial" ,"E_{#nu} [GeV]","Event/[GeV]", pdf_CV,true,true, false, -99,-99);
//
//auto NuMu_Rate_Daisy0 = Get1DHist(*TFile_CrossSection_helium,"h_Enu_TRUE_helium_Daisy0");
////NuMu_Rate->Scale(1/NuMu_Rate->Integral());
//NuMu_Rate_Daisy0->Scale(1.0,"width");
//NuMu_Rate_Daisy0->GetXaxis()->SetRangeUser(0.0,20.0);
//DrawCVAndError_FromHIST(true , inhouseFlux, "inhouseflux" ,"E_{#nu} [GeV]","CC-#nu_{#mu} / m^{2} / POT / GeV", pdf_CV,true,true, false, -99,-99);
//auto Flux_test = Get1DHist(*TFile_Flux_helium,"flux");
//DrawCVAndError_FromHIST(true , inhouseFlux_tracker, "Tracker inhouse flux" ,"E_{#nu} [GeV]","CC-#nu_{#mu} / m^{2} / POT / GeV", pdf_CV,true,true, false, -99,-99);

//inhouseFlux->Divide(inhouseFlux, inhouseFlux_tracker_christian);
//inhouseFlux_tracker_christian->Divide(inhouseFlux_tracker_christian, inhouseFlux_tracker_christian);
DrawCVAndError_FromHIST(true , inhouseFlux_tracker_christian, "Inhouse" ,"E_{#nu} [GeV]","CC-#nu_{#mu} / m^{2} / POT / GeV", pdf_CV,true,true, false, -99,-99);

auto inhouseFlux_tracker_christian_CombinedErrors = MakeHist_combinedTotalError(inhouseFlux_tracker_christian);
inhouseFlux_tracker_christian_CombinedErrors->GetXaxis()->SetRangeUser(0.0,20.0);
DrawCVAndError_FromHIST(true , inhouseFlux_tracker_christian_CombinedErrors, "Inhouse" ,"E_{#nu} [GeV]","CC-#nu_{#mu} / m^{2} / POT / GeV", pdf_CV,true,true, false, -99,-99);



DrawCVAndError_From2HIST_test(inhouseFlux, "Helium" ,inhouseFlux_tracker_christian, "Tracker christian",  "CC-#nu_{#mu} / m^{2} / POT / GeV" ,"E_{#nu} [GeV]", "^{4}He flux / CH flux",
pdf_CV, true,  DontBinWidthNorm, -99,-99 , false );

DrawCVAndError_From2HIST_test(inhouseFlux_tracker_anezkak, "tracker anezkak" ,inhouseFlux_tracker_christian, "Tracker christian",  "CC-#nu_{#mu} / m^{2} / POT / GeV" ,"E_{#nu} [GeV]", "^{4}He flux / CH flux",
pdf_CV, true,  DontBinWidthNorm, -99,-99 , false );


inhouseFlux_tracker_anezkak->Divide(inhouseFlux_tracker_anezkak,inhouseFlux_tracker_christian);

inhouseFlux->Divide(inhouseFlux,inhouseFlux_tracker_christian);
inhouseFlux_tracker_christian->Divide(inhouseFlux_tracker_christian,inhouseFlux_tracker_christian);

DrawCVAndError_From2HIST_test(inhouseFlux, "Helium" ,inhouseFlux_tracker_christian, "Tracker christian",  "Flux Ratio " ,"E_{#nu} [GeV]", "^{4}He flux / CH flux",
pdf_CV, true,  DontBinWidthNorm, 1.25, .85 , false );



DrawCVAndError_From2HIST_test(inhouseFlux_tracker_anezkak, "tracker anezkak" ,inhouseFlux_tracker_christian, "Tracker christian",  "Flux Ratio " ,"E_{#nu} [GeV]", "#frac{anezkak}{Christian} Tracker Flux",
pdf_CV, true,  DontBinWidthNorm, 1.025, .99 , false );
//auto NuMu_Rate_Daisy8 = Get1DHist(*TFile_CrossSection_helium,"h_Enu_TRUE_helium_Daisy8");
//NuMu_Rate_Daisy8->Scale(1.0,"width");
//NuMu_Rate_Daisy8->GetXaxis()->SetRangeUser(0.0,20.0);
//DrawCVAndError_FromHIST(true ,inhouseFlux, "inhouseFlux ration of differnet helium" ,"E_{#nu} [GeV]","Event/[GeV]", pdf_CV,true,true, false, -99,-99);




  DrawCVAndError_From_L_2HIST_RHist_test(Flux_Tracker_clone2_rebin, "Tracker" ,Flux_helium_manybins_clone_rebin, "Helium",
   NuMu_Rate, "True #nu_{#mu} Helium rate",
   "Flux Ratio " ,"E_{#nu} [GeV]", "^{4}He flux / CH flux", "NEvents / [GeV]",
   pdf_CV, true,  DontBinWidthNorm, 1.25, .85 , false);

  DrawCVAndError_From_L_2HIST_RHist_test2(Flux_Tracker_clone2_rebin, "Tracker" ,Flux_helium_manybins_clone_rebin, "Helium",
   NuMu_Rate, "True #nu_{#mu} Helium rate",
   "Helium Flux" ,"E_{#nu} [GeV]", "CC-#nu_{#mu} / m^{2} / POT / GeV", "NEvents / [GeV]",
   pdf_CV, true,  DontBinWidthNorm, 1.25, .85 , false);


double integral_tope = NuMu_Rate->Integral(NuMu_Rate->FindBin(6.5), NuMu_Rate->FindBin(14));
double integral_tope_1 = NuMu_Rate->Integral(NuMu_Rate->FindBin(14), NuMu_Rate->FindBin(20));
double integral_tope_rate_2 = NuMu_Rate->Integral(NuMu_Rate->FindBin(5.5), NuMu_Rate->FindBin(6.5));
double integral_tope_rate_3 = NuMu_Rate->Integral(NuMu_Rate->FindBin(2), NuMu_Rate->FindBin(5.5));


std::cout<<"percentage of events 2 to 5.5     " << (integral_tope_rate_3 / NuMu_Rate->Integral()) * 100 << std::endl;
std::cout<<"percentage of events 5.5 to 6.6     " << (integral_tope_rate_2 / NuMu_Rate->Integral()) * 100 << std::endl;
std::cout<<"percentage of events 8 to 14     " << (integral_tope / NuMu_Rate->Integral()) * 100 << std::endl;
std::cout<<"percentage of events 14 to 20     " << (integral_tope_1 / NuMu_Rate->Integral()) * 100 << std::endl;
Flux_helium_manybins_clone2->GetXaxis()->SetRangeUser(0.0,20.0);

  // DrawCVAndError_From_L_2HIST_RHist_test(Flux_Tracker_clone2_rebin, "Tracker" ,Flux_helium_manybins_clone_rebin, "Helium",
  //  Flux_helium_manybins_clone3, "True #nu_{#mu} Helium rate",
  //  "Flux Ratio " ,"E_{#nu} [GeV]", "^{4}He flux / CH flux", "CC-#nu_{#mu} / m^{2} / POT / GeV",
  //  pdf_CV, true,  DontBinWidthNorm, 1.25, .85 , false);





Flux_Tracker_rebin->Divide(Flux_Tracker_rebin,Flux_Tracker_rebin);

bool dontprinterrors= false;

 DrawCVAndError_From5HIST(Flux_Tracker_rebin, "Tracker" ,
                                Flux_helium_slice1,"slice1",
                                Flux_helium_slice2,"slice2",
                                Flux_helium_slice3,"slice3",
                                Flux_helium_slice4,"slice4",
  "Slices" ,"E_{#nu} [GeV]", "Ratio ^{4}He / CH",
     pdf_CV, true, dontprinterrors, dontprinterrors, DontBinWidthNorm, 1.2 ,.8 ,false,  false );



              DrawCVAndError_FromDaisyHIST(Flux_Tracker_rebin, "Tracker" ,
                                                  Flux_helium_daisy0, "Helium daisy 0" ,
                                                Flux_helium_daisy1, "Helium daisy 1" ,
                                                Flux_helium_daisy2,"Helium daisy 2",
                                                Flux_helium_daisy3,"Helium daisy 3",
                                                Flux_helium_daisy4,"Helium daisy 4",
                                                Flux_helium_daisy5,"Helium daisy 5",
                                                Flux_helium_daisy6,"Helium daisy 6",
                                                Flux_helium_daisy7,"Helium daisy 7",
                                                Flux_helium_daisy8,"Helium daisy 8",
                                                Flux_helium_daisy9,"Helium daisy 9",
                                                Flux_helium_daisy10,"Helium daisy 10",
                                                Flux_helium_daisy11,"Helium daisy 11",
                  "Flux Helium Daisy " ,"E_{#nu} [GeV]", "Helium/CH Flux",
                    pdf_CV, true,DontBinWidthNorm, 1.3 , false,  false );


DrawCVAndError_From2HIST(inputFluxForrFit_Tracker, "tracker input" ,inputFluxForrFit_helium,
                             "helium input",  "hist input fit" ,"E_{#nu} [GeV]", "#nu / m^2 / POT / GeV",
                            pdf_CV, true, DontBinWidthNorm, -99 ,false);

Draw2DHist(inputTracker_vs_patal_inhouse,  "E_{#nu} [GeV]", " daisy Number","#nu / m^2 / POT / GeV",
                                             "Input inhouse",  text_title_pdf2, can, mnv_plot);

Draw2DHist(inputTracker_vs_patal,  "E_{#nu} [GeV]", " daisy Number","#nu / m^2 / POT / GeV",
"anezkak ",  text_title_pdf2, can, mnv_plot);

std::vector<double> bins_thicc{0,4,6,8,10,15,20};//0, 4, 6, 8, 10, 15, 20

auto inputTracker_vs_patal_inhouse_newbins = rebin_x_axis(inputTracker_vs_patal,bins_thicc); //inputTracker_vs_patal_inhouse
UnBinWidthNormalizeTH1D(*inputFluxForrFit_Tracker);
UnBinWidthNormalizeTH1D(*inputFluxForrFit_helium);
auto inputFluxForrFit_Tracker_newbins = Rebin(inputFluxForrFit_Tracker, bins_thicc);
 auto inputFluxForrFit_helium_newbins = Rebin(inputFluxForrFit_helium, bins_thicc);

 inputFluxForrFit_Tracker_newbins->Scale(1.0,"width");
 inputFluxForrFit_helium_newbins->Scale(1.0,"width");

 //PlotUtils::MnvH1D* Flux_Tracker_clone2_rebin = RebinMnvH1D(Flux_Tracker_clone2, newbins);



  DrawCVAndError_From2HIST(inputFluxForrFit_Tracker_newbins, "Tracker " ,inputFluxForrFit_helium_newbins,
          "helium",  "input rebined hist for fit " ,"E_{#mu} [GeV]","#nu / m^2 / POT / GeV",
          pdf_CV, true, false, -99 , false);

 Draw2DHist(inputTracker_vs_patal_inhouse_newbins, "E_{#mu} [GeV]", "Daisy N", "#nu / m^2 / POT / GeV",
                           "input 2D for fit",  text_title_pdf2, can, mnv_plot);

//WidthBinNormalize(*inputTracker_vs_patal_inhouse_newbins);

Draw2DHist(inputTracker_vs_patal_inhouse_newbins, "E_{#mu} [GeV]", "Daisy N", "#nu / m^2 / POT / GeV",
                          "input 2D for fit ",  text_title_pdf2, can, mnv_plot);

Fit2DPatals_fluxratioAttachhist(inputTracker_vs_patal_inhouse_newbins, inputFluxForrFit_Tracker_newbins, inputFluxForrFit_helium_newbins);




std::vector<double> reg_lambda{20, 30, 40, 50,55, 60,65, 70, 75, 80, 85, 90,100,  110, 120, 130, 140, 160, 180, 200, 300, 500, 1000, 1200, 1500};

double chi_2=99;

std::vector<double> chi_vector;
std::vector<double> chi_vector_other;
std::vector<double> Param_vector;
std::vector<double> Param_Error_vector;

std::vector<double> FitParas; std::vector<double> FitParas_error;

for(auto lambda:reg_lambda){

Fit2DPatals_fluxratio(FitParas, FitParas_error, chi_2, lambda );
chi_vector.push_back(chi_2);


if(lambda == 100){
Param_vector = FitParas;
Param_Error_vector = FitParas_error;

}

FitParas.clear();
FitParas_error.clear();
}

//auto h_weights = make_param_hist(Param_vector, Param_Error_vector);
std::vector<double> bins{1,2,3,4,5,6,7,8,9,10,11,12};
std::vector<double> unitbins{1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0};
//auto weights = MakeTGraph_from_VectorsErrors(Param_vector, Param_Error_vector, bins);
auto weights = MakeTGraph_from_VectorsErrors(Param_vector, Param_Error_vector, bins);
//std::vector<double>MakeChilog;

for(auto &Num: chi_vector){
Num = log(Num);
}

TGraph* Fiting = createTGraph(reg_lambda, chi_vector);
//TGraph* FitingLog = createTGraph(newreg_lambda, chi_vector_other);
 DrawTGraph(Fiting,  "lambda", "#chi^{2} + Reg ","L-Curve fit","Helium", text_title_pdf2, can, mnv_plot, false, false );
 DrawTGraph(Fiting, "lambda","#chi^{2} + Reg ", "L-Curve fit","Helium", text_title_pdf2, can, mnv_plot, false, true );


 DrawTGraph_PolyFit(Fiting, "Regularization #lambda","Log #[]{ #chi^{2} + Reg}",
    "L-Curve fit", "Helium", "Poly6",
    text_title_pdf2, can, mnv_plot, false, false, 50, 200, "pol 6" );

int petalN =0 ;
std::cout<<"Param_vector.size() = " << Param_vector.size()<< std::endl;
for(auto wgt: Param_vector){
std::cout<<" petal number:  "<< petalN <<  " wgt : " << wgt << std::endl;
petalN++;
}



PlotUtils::MnvH1D* h_weights =  make_param_hist("HeliumWeights" , Param_vector, Param_Error_vector);

//h_weights->AddMissingErrorBandsAndFillWithCV(*Flux_Tracker_clone);

std::cout<<"NBins = " << h_weights->GetNbinsX()<<std::endl;
std::cout<<"intergral =" << h_weights->Integral()<<std::endl;

//DrawCVAndError_FromHIST(h_weights, "Helium Daisy weights" ,"Daisy slice","weight", pdf_CV, false, false);

inputFluxForrFit_helium->Divide(inputFluxForrFit_helium,inputFluxForrFit_Tracker);
inputFluxForrFit_Tracker->Divide(inputFluxForrFit_Tracker,inputFluxForrFit_Tracker);

DrawCVAndError_From2HIST(inputFluxForrFit_Tracker, "tracker input" ,inputFluxForrFit_helium,
                             "helium input",  "hist input fit" ,"E_{#nu} [GeV]", "Ratio",
                            pdf_CV, true, DontBinWidthNorm, -99 ,false);


DrawCVAndError_FromHIST(false , h_weights, "Helium Daisy weights" ,"Daisy Petal Number","Weight",
  pdf_CV,true,false, true, .8,1.2);

//DrawCVAndError_FromHIST(bool PrintALLerrorGroups , MnvH1D *hist, char *histotitle ,std::string xaxislabel,std::string yaxislabel,
//  std::string pdf_name, bool Setgrid,  bool doBinwidth=false ,  bool SetYlimits =false,  double Ymin=-99, double Ymax = 99 );


DrawTGraph(weights, "Daisy Petal Number","weight", "fitted weights","",text_title_pdf2, can, mnv_plot, false, false  );
  //  void DrawTGraph(TGraph *g_TGraph, const char* xaxislabel,const char* yaxislabel,const char* Title, const char* legend_Title,
    //  const char* pdf, TCanvas *can, MnvPlotter *plot, bool MakeXaxisLOG, bool MakeYaxisLOG );

//MnvH1D *hist_1_input, char *legend_1_title ,MnvH1D *hist_2_input,
//            char *legend_2_title,  char *histotitle ,std::string xaxislabel, std::string yaxislabel,
//            std::string pdf_name, bool Setgrid, bool BinWidthNorm, double Ymax , bool setLogY
//
//DrawCVAndError_From2HIST(Flux_Tracker, "Git" ,Flux_Tracker_homebrew2, "Homebrew",  "Flux Ratio " ,"E_{#nu} [GeV]", "^{4}He flux / CH flux",
//pdf_CV, true, false , false , DontBinWidthNorm, -99,  false,   false );


//Flux_Tracker_remake->AddMissingErrorBandsAndFillWithCV(*Flux_Tracker_homebrew);

//DrawCVAndError_From2HIST(Flux_Tracker, "Git" ,Flux_Tracker_remake, "remake",  "Flux Ratio " ,"E_{#nu} [GeV]", "^{4}He flux / CH flux",
//pdf_CV, true, false , false , DontBinWidthNorm, -99,  false,   false );



       //auto outFile = TFile::Open("CrossSection_FluxFits_helium_Flux.root", "RECREATE");

       //outFile->cd(); // make sure that we will write to this ROOT file g->Write("MyGraph");
       //outputTGraphs.at(0)->Write("MyGraph_fitContour_1sigma_par_3_7");
       //outputTGraphs.at(1)->Write("MyGraph_fitContour_1sigma_par_1_3");
       //outputTGraphs.at(2)->Write("MyGraph_fitContour_1sigma_par_1_7");
       //outputTGraphs.at(3)->Write("MyGraph_fitContour_2sigma_par_3_7");
       //outputTGraphs.at(4)->Write("MyGraph_fitContour_2sigma_par_1_3");
       //outputTGraphs.at(5)->Write("MyGraph_fitContour_2sigma_par_1_7");
       //outFile->Close();



    //   TFile* f0 = new TFile("CrossSection_FluxFits_helium.root");
    //   TGraph* MyGraph_fitContour_1sigma_par_3_7 = (TGraph*)f0->Get("MyGraph_fitContour_1sigma_par_3_7");
    //   TGraph* MyGraph_fitContour_1sigma_par_1_3 = (TGraph*)f0->Get("MyGraph_fitContour_1sigma_par_1_3");
    //   TGraph* MyGraph_fitContour_1sigma_par_1_7 = (TGraph*)f0->Get("MyGraph_fitContour_1sigma_par_1_7");
    //   TGraph* MyGraph_fitContour_2sigma_par_3_7 = (TGraph*)f0->Get("MyGraph_fitContour_2sigma_par_3_7");
    //   TGraph* MyGraph_fitContour_2sigma_par_1_3 = (TGraph*)f0->Get("MyGraph_fitContour_2sigma_par_1_3");
    //   TGraph* MyGraph_fitContour_2sigma_par_1_7 = (TGraph*)f0->Get("MyGraph_fitContour_2sigma_par_1_7");

    //    DrawTGraph(MyGraph_fitContour_1sigma_par_3_7, MyGraph_fitContour_2sigma_par_3_7, "Beam Postion X [mm]", "Beam Postion Y [mm]",
    //            "Fit Contour of X vs Y position Beam Peak","1#sigma","2#sigma",
    //            text_title_pdf2, can,mnv_plot,false,false,true );

    //    DrawTGraph(MyGraph_fitContour_1sigma_par_1_3, MyGraph_fitContour_2sigma_par_1_3, "E_{#nu} [GeV]", "Beam Postion X [mm]",
    //                    "Fit Contour of X vs E_{#nu} Beam Peak","1#sigma","2#sigma",
    //                    text_title_pdf2, can,mnv_plot,false,false,true );

    //    DrawTGraph(MyGraph_fitContour_1sigma_par_1_7, MyGraph_fitContour_2sigma_par_1_7, "E_{#nu} [GeV]", "Beam Postion Y [mm]",
    //                                    "Fit Contour of Y vs E_{#nu}","1#sigma","2#sigma",
    //                                    text_title_pdf2, can,mnv_plot,false,false,true );

auto outFile = TFile::Open("out_helium_000100.root", "RECREATE");

outFile->cd();

std::cout<< "chi = "<< chi2<< "ndf = "<< ndf << " ndf_fit = "<< ndf_fit<<std::endl;

std::cout<< "chi/ndf = "<< chi2 / ndf << "  chi/ndf_fit = "<< chi2 / ndf_fit <<std::endl;

h_weights->Write("param_hist");
MnvH1D* inputFluxForrFit_helium_mvnh1d_binned = FluxTool.GetRebinnedFluxReweighted_FromInputFlux(inputFluxForrFit_helium_mvnh1d, h_fluxBinnng_course);
inputFluxForrFit_helium_mvnh1d_binned->SetTitle("helium_rebinned");
inputFluxForrFit_helium_mvnh1d_binned->Write("flux");
MnvH1D* inputFluxForrFit_Tracker_mvnh1d_binned = FluxTool.GetRebinnedFluxReweighted_FromInputFlux(inputFluxForrFit_Tracker_mvnh1d, h_fluxBinnng_course);

inputFluxForrFit_Tracker_mvnh1d_binned->SetTitle("Carbon_rebinned");
inputFluxForrFit_Tracker_mvnh1d_binned->Write("unweighted_flux");

DrawCVAndError_From2HIST_test(inputFluxForrFit_Tracker_mvnh1d_binned, "tracker" ,inputFluxForrFit_helium_mvnh1d_binned, "helium",  "CC-#nu_{#mu} / m^{2} / POT / GeV" ,"E_{#nu} [GeV]", "^{4}He flux / CH flux",
pdf_CV, true,  DontBinWidthNorm, -99,-99 , false );


auto inputFluxForrFit_helium_mvnh1d_binned_CombinedErrors = MakeHist_combinedTotalError(inputFluxForrFit_helium_mvnh1d_binned);
auto inputFluxForrFit_Tracker_mvnh1d_binned_CombinedErrors = MakeHist_combinedTotalError(inputFluxForrFit_Tracker_mvnh1d_binned);

inputFluxForrFit_helium_mvnh1d_binned_CombinedErrors->GetXaxis()->SetRangeUser(0.0,20.0);
inputFluxForrFit_Tracker_mvnh1d_binned_CombinedErrors->GetXaxis()->SetRangeUser(0.0,20.0);

inputFluxForrFit_helium_mvnh1d_binned_CombinedErrors->Divide(inputFluxForrFit_helium_mvnh1d_binned_CombinedErrors, inputFluxForrFit_Tracker_mvnh1d_binned_CombinedErrors);
inputFluxForrFit_helium_mvnh1d_binned_CombinedErrors->Write("flux_ratio");
outFile->Close();
inputFluxForrFit_Tracker_mvnh1d_binned_CombinedErrors->Divide(inputFluxForrFit_Tracker_mvnh1d_binned_CombinedErrors, inputFluxForrFit_Tracker_mvnh1d_binned_CombinedErrors);

DrawCVAndError_From2HIST_test(inputFluxForrFit_Tracker_mvnh1d_binned_CombinedErrors, "tracker" ,inputFluxForrFit_helium_mvnh1d_binned_CombinedErrors, "helium",  "CC-#nu_{#mu} / m^{2} / POT / GeV" ,"E_{#nu} [GeV]", "^{4}He flux / CH flux",
pdf_CV, true,  DontBinWidthNorm, 1.25,.85 , false );

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




  //Fit2Dhist(histpointerA, histpointerB, para_vector, wgt_error_vector, chi2 );

  //for(auto cat:para_vector ){
  //  std::cout<<"pars : " <<  cat << std::endl;
  //}


  //auto EuvsVertexX_reduce = Get2DHist(*TFile_CrossSection_helium,"h2d_Enu_TRUE_vertex_X_reduced");
  //auto EuvsVertexY_reduce = Get2DHist(*TFile_CrossSection_helium,"h2d_Enu_TRUE_vertex_Y_reduced");

  //auto EuvsVertexX_reduce1 = Get2DHist(*TFile_CrossSection_helium,"h2d_Enu_TRUE_vertex_X_reduced1");
  //auto EuvsVertexY_reduce1 = Get2DHist(*TFile_CrossSection_helium,"h2d_Enu_TRUE_vertex_Y_reduced1");

    //Draw2DHist_histWithTProfile(EuvsVertexX, "", "E_{#nu} ","Vertex X [mm]",text_title_pdf2, can, mnv_plot);
    //Draw2DHist_histWithTProfile(EuvsVertexY, "", "E_{#nu} ","Vertex Y [mm]",text_title_pdf2, can, mnv_plot);

    //Draw2DHist_histWithTProfile(EuvsVertexX_reduce, "", "E_{#nu} ","Vertex X [mm]",text_title_pdf2, can, mnv_plot);
    //Draw2DHist_histWithTProfile(EuvsVertexY_reduce, "", "E_{#nu} ","Vertex Y [mm]",text_title_pdf2, can, mnv_plot);

  //  Draw2DHist_histWithTProfile_Y(EuvsVertexX, "", "E_{#nu} ","Vertex X [mm]",text_title_pdf2, can, mnv_plot);
  //  Draw2DHist_histWithTProfile_Y(EuvsVertexY, "", "E_{#nu} ","Vertex Y [mm]",text_title_pdf2, can, mnv_plot);

    //Draw2DHist_histWithTProfile_Y(EuvsVertexX_reduce, "", "E_{#nu} ","Vertex X [mm]",text_title_pdf2, can, mnv_plot);
    //Draw2DHist_histWithTProfile_Y(EuvsVertexY_reduce, "", "E_{#nu} ","Vertex Y [mm]",text_title_pdf2, can, mnv_plot);

    //Draw2DHist_warpFit2DGaussian(EuvsVertexX, "E_{#nu}", "Vertex X [mm]",  "Gaussian Fit", text_title_pdf2, can, mnv_plot);

    //Draw2DHist_warpFit2DGaussian(EuvsVertexY, "E_{#nu} ", "Vertex Y [mm]","Gaussian Fit", text_title_pdf2, can, mnv_plot);
    //Draw2DHist_warpFit2DGaussian(EuvsVertexX_reduce, "E_{#nu}", "Vertex X [mm]",  "Gaussian Fit [reduce binning]", text_title_pdf2, can, mnv_plot);
    //Draw2DHist_warpFit2DGaussian(EuvsVertexY_reduce, "E_{#nu} ", "Vertex Y [mm]","Gaussian Fit [reduce binning]", text_title_pdf2, can, mnv_plot);


    //Draw2DHist_warpFit2DGaussian(EuvsVertexX_reduce1, "E_{#nu}", "Vertex X [mm]",  "Gaussian Fit [0 to 10 ]", text_title_pdf2, can, mnv_plot,0.0,10.0);
    //Draw2DHist_warpFit2DGaussian(EuvsVertexY_reduce1, "E_{#nu} ", "Vertex Y [mm]","Gaussian Fit [0 to 10 ]", text_title_pdf2, can, mnv_plot,0.0,10.0);

    //Draw2DHist_warpFit2DGaussian(EuvsVertexX_reduce1, "E_{#nu}", "Vertex X [mm]",  "Gaussian Fit [0 to 12 ]", text_title_pdf2, can, mnv_plot,0.0,12.0);
    //Draw2DHist_warpFit2DGaussian(EuvsVertexY_reduce1, "E_{#nu} ", "Vertex Y [mm]","Gaussian Fit [0 to 12 ]", text_title_pdf2, can, mnv_plot,0.0,12.0);

    //Draw2DHist_warpFit2DGaussian(EuvsVertexX_reduce1, "E_{#nu}", "Vertex X [mm]",  "Gaussian Fit [0 to 15 ]", text_title_pdf2, can, mnv_plot,0.0,15.0);
    //Draw2DHist_warpFit2DGaussian(EuvsVertexY_reduce1, "E_{#nu} ", "Vertex Y [mm]","Gaussian Fit [0 to 15 ]", text_title_pdf2, can, mnv_plot,0.0,15.0);

    //Draw2DHist_warpFit2DGaussian(EuvsVertexX_reduce1, "E_{#nu}", "Vertex X [mm]",  "Gaussian Fit [0 to 20 ]", text_title_pdf2, can, mnv_plot,0.0,20);
    //Draw2DHist_warpFit2DGaussian(EuvsVertexY_reduce1, "E_{#nu} ", "Vertex Y [mm]","Gaussian Fit [0 to 20 ]", text_title_pdf2, can, mnv_plot,0.0,20);




    ////Draw2DHist_warpFit2DGaussian(EuvsVertexX_reduce1, "E_{#nu}", "Vertex X [mm]",  "Gaussian Fit [reduce binning]", text_title_pdf2, can, mnv_plot);
    //Draw2DHist_warpFit2DGaussian(EuvsVertexY_reduce1, "E_{#nu} ", "Vertex Y [mm]","Gaussian Fit [reduce binning]", text_title_pdf2, can, mnv_plot);


  //  double areaCX = EuvsVertexX->Integral();
  //  double areaCY = EuvsVertexY->Integral();
  //  EuvsVertexX->Scale(1.0/areaCX);
  // EuvsVertexY->Scale(1.0/areaCY);
  //
  //  Draw2DHist_warpFit2DGaussian(EuvsVertexX, "E_{#nu}", "Vertex X [mm]",  "Gaussian Fit [AreaNorm]", text_title_pdf2, can, mnv_plot);
  //
  //  Draw2DHist_warpFit2DGaussian(EuvsVertexY, "E_{#nu} ", "Vertex Y [mm]", "Gaussian Fit [AreaNorm]", text_title_pdf2, can, mnv_plot);




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

std::vector<double> generateXAxisBins() {
    std::vector<double> xBins;
    double x = 0.0;
    while (x <= 20.0) {
        xBins.push_back(x);
        x += 0.25;
    }
    return xBins;
}


TH2D* rebin_x_axis(TH2D* hist, const std::vector<double>& new_bins)
{
    // Create a new TH2D with the rebinned x-axis
    TH2D* rebinned_hist = new TH2D(hist->GetName(), hist->GetTitle(), new_bins.size() - 1, &new_bins[0], hist->GetNbinsY(), hist->GetYaxis()->GetXmin(), hist->GetYaxis()->GetXmax());

    // Loop over the y-axis bins
    for (int y_bin = 1; y_bin <= hist->GetNbinsY(); ++y_bin) {
        // Loop over the new x-axis bins
        for (int new_x_bin = 1; new_x_bin <= new_bins.size() - 1; ++new_x_bin) {
            // Calculate the range of old x-axis bins that contribute to this new x-axis bin
            int old_x_bin_start = hist->GetXaxis()->FindBin(new_bins[new_x_bin - 1]);
            int old_x_bin_stop = hist->GetXaxis()->FindBin(new_bins[new_x_bin]) - 1;
            if (old_x_bin_stop < old_x_bin_start) old_x_bin_stop = old_x_bin_start;

            // Sum the contents and errors of the old x-axis bins that contribute to this new x-axis bin
            double content = 0;
            double error = 0;
            for (int old_x_bin = old_x_bin_start; old_x_bin <= old_x_bin_stop; ++old_x_bin) {
                content += hist->GetBinContent(old_x_bin, y_bin);
                error += pow(hist->GetBinError(old_x_bin, y_bin), 2);
            }
            error = sqrt(error);

            // Set the content and error of the new bin
            rebinned_hist->SetBinContent(new_x_bin, y_bin, content);
            rebinned_hist->SetBinError(new_x_bin, y_bin, error);
        }
    }

    return rebinned_hist;
}
std::vector<double> log_replace(const std::vector<double>& input) {
    std::vector<double> output(input.size());
    std::transform(input.begin(), input.end(), output.begin(), [](double x) { return std::log(x); });
    return output;
}













std::vector<double> get_y_bin_edges( TH2D* hist) {
    std::vector<double> y_values;
    for (int i = 1; i <= hist->GetNbinsY(); i++) {
        y_values.push_back(hist->GetYaxis()->GetBinLowEdge(i));
    }
    y_values.push_back(hist->GetYaxis()->GetBinUpEdge(hist->GetNbinsY()));
    std::sort(y_values.begin(), y_values.end());
    auto last = std::unique(y_values.begin(), y_values.end());
    y_values.erase(last, y_values.end());
    return y_values;
}


std::vector<double> get_y_bin_edges( MnvH2D* hist) {
    std::vector<double> y_values;
    for (int i = 1; i <= hist->GetNbinsY(); i++) {
        y_values.push_back(hist->GetYaxis()->GetBinLowEdge(i));
    }
    y_values.push_back(hist->GetYaxis()->GetBinUpEdge(hist->GetNbinsY()));
    std::sort(y_values.begin(), y_values.end());
    auto last = std::unique(y_values.begin(), y_values.end());
    y_values.erase(last, y_values.end());
    return y_values;
}

MnvH1D* MakeHist_combinedTotalError(MnvH1D* input){

  MnvH1D *h2 =(PlotUtils::MnvH1D*)input->Clone("h2");
  MnvH1D *h1 = new MnvH1D(h2->GetName(), h2->GetTitle(), h2->GetNbinsX(), h2->GetXaxis()->GetXbins()->GetArray());
  auto h3 = h2->GetTotalError() ; // Get a TH1D of total error not including stats

  for (int i=1; i<=h1->GetNbinsX(); ++i) {
      double content = h2->GetBinContent(i);
      double error = h3.GetBinContent(i);
      h1->SetBinContent(i, content);
      h1->SetBinError(i, error);
  }


  return h1;


}


/*

TF1* GetSpline(std::string material) {
    //std::assert(std::find(supported_materials.begin(), supported_materials.end(), material) != supported_materials.end(),
      //     ("Can't find material " + material + " in supported_materials").c_str());

    TFile* tf = new TFile("$MPARAMFILESROOT/data/GENIE/spline_files/gxspl-nuclear-MINERVA_Full_v2126.root");
    std::string splinename;
    if (material == "tracker" || material == "carbon") {
        splinename = "nu_mu_C12/tot_cc";
    }
    else if (material == "lead") {
        splinename = "nu_mu_Pb207/tot_cc";
    }
    else if (material == "iron") {
        splinename = "nu_mu_Fe56/tot_cc";
    }
    else if (material == "oxygen") {
        splinename = "nu_mu_O16/tot_cc";
    }
    else if (material == "helium") {
        splinename = "nu_mu_He4/tot_cc";
    }

std::cout<<"splinename = " << splinename << std::endl;
if(splinename == ""){std::cout<<"Wasn't able to get a spline name from material name"<<std::endl;}
  //assert(splinename != "", ("Wasn't able to get a spline name from material name " + material).c_str());

    //TH1D out = (TH1D)tf->Get(splinename.c_str());
//GetTGraph(TFile& fin, const char* name)
      TGraph* out = GetTGraph(*tf, splinename );
      if(out == nullptr){std::cout<<"Wasn't able to th1d "<<std::endl;}

    //assert(out != nullptr, ("Spline is none " + splinename + " for spline name " + material).c_str());


    // Convert to actual function so that integrals are smoother
    TF1* func = new TF1("func", "pol 6", 0, 100);
    std::cout<<"made Function"<< std::endl;
    //out->Fit(funcname.c_str());
    out->Fit(func,"RQ");
    return func;
}

MnvH1D* MakeCrossSectionSpineHist( MnvH1D *originalHist, std::string material){

MnvH1D *emptyHist = new MnvH1D(originalHist->GetName(), originalHist->GetTitle(), originalHist->GetNbinsX(), originalHist->GetXaxis()->GetXbins()->GetArray());

TF1* SpineFunction = GetSpline(material);
double units = 1e-38; //# converts to 1e-38cm
units *= 1.0 / (100.0 * 100.0);

for (int i = 1; i <= emptyHist->GetNbinsX(); ++i) {
  double binlowedge = emptyHist->GetBinLowEdge(i);
  double binwidth = emptyHist->GetBinWidth(i);

  double xsecInt = SpineFunction->Integral(binlowedge, binlowedge + binwidth);
  emptyHist->SetBinContent(i, (xsecInt / binwidth ) *units);
}


    //emptyHist->Scale(1,"width");
    //emptyHist->Scale(units);

return emptyHist;

}

MnvH1D* MakeFluxHist(MnvH1D *originalHist, std::string material, double ntargets, double potnorm){
  MnvH1D *clonedHist =(PlotUtils::MnvH1D*)originalHist->Clone("clonedHist");
MnvH1D * Avg_crosssection = MakeCrossSectionSpineHist( clonedHist,  material);
Avg_crosssection->AddMissingErrorBandsAndFillWithCV(*clonedHist);
clonedHist->Divide(clonedHist, Avg_crosssection);
clonedHist->Scale(1.0 / (ntargets * potnorm ));
clonedHist->Scale(1.0,"width");
return clonedHist;

}

MnvH1D* GetCrossSection_hist(MnvH1D *originalHist, std::string material){
  MnvH1D *clonedHist =(PlotUtils::MnvH1D*)originalHist->Clone("clonedHist");
MnvH1D * Avg_crosssection = MakeCrossSectionSpineHist(clonedHist,  material);
Avg_crosssection->AddMissingErrorBandsAndFillWithCV(*clonedHist);
return Avg_crosssection;

}
*/
