#include "Make_CrossSection_Plots.h"

CrossSection_name_Map Generate_CrossSection_histsNames_withInteraction(
  MuonVar MuonVar_type, std::string playlist, bool isFUll);
///============================================================================
CrossSection_name_Map Generate_CrossSection_histsNames_withInteraction_DISbreakdown_helium(
  MuonVar MuonVar_type, std::string playlist, bool isFUll);
  ///============================================================================
CrossSection_name_Map Generate_CrossSection_histsNames_withInteraction_DISbreakdown(
  MuonVar MuonVar_type, std::string playlist, bool isFUll);
  ///============================================================================
CrossSection_name_Map Generate_2DCrossSection_histsNames_withInteraction_DISbreakdown_forMasterAna(
  std::string hist_name,  std::string playlist,  bool PrintNames);
  ///============================================================================
CrossSection_name_Map Generate_2DCrossSection_histsNames_withInteraction_DISbreakdown_helium(
  std::string hist_name, Muon2DVar MuonVar_type,  std::string playlist,
   bool isFUll , bool PrintNames);
///============================================================================
std::vector<ME_helium_Playlists> GetTrackerPlayListVector();
///============================================================================
std::string GetMigDaisy(MuonVar MuonVar_type, std::string Petal);
///============================================================================
void MakeCrossSectionPlots_Interaction_Ratio(CrossSection_MnvH1D_Map CrossSection_map,
  CrossSection_MnvH1D_Map CrossSection_map_helium,
  std::string cross_section_units, std::string pdf,bool MakeXaxisLOG,bool doBinwidth ,
  MuonVar MuonVar, char *Playlist_name, double POT_Data, double POT_MC,
   Genie_Models Modelinputs, TCanvas *can, MnvPlotter *plot, bool makepieInteraction= false);
   ///============================================================================
  void MakeCrossSectionPlots_Interaction_Ratio(CrossSection_MnvH1D_Map CrossSection_map,
    CrossSection_MnvH1D_Map CrossSection_map_helium,
    std::string cross_section_units, std::string pdf,bool MakeXaxisLOG,bool doBinwidth ,
    MuonVar MuonVar, char *Playlist_name, double POT_Data, double POT_MC, Genie_Models Modelinputs,
     TCanvas *can, MnvPlotter *plot, bool makepieInteraction, MnvH1D* Daisy_combined_Data,
      MnvH1D* Daisy_combined_CrosSection_Data );
      ///============================================================================
  void Make2DCrossSectionPlots_Interaction_Ratio(CrossSection_MnvH2D_Map CrossSection_map_tracker,
     CrossSection_MnvH2D_Map CrossSection_map_Helium,
    std::string cross_section_units, std::string pdf,bool MakeXaxisLOG,bool doBinwidth,
    Muon2DVar MuonVar, char *Playlist_name, TCanvas *can, MnvPlotter *plot, double POT_Data,
    double POT_MC, MnvH2D *hist_Data_Daisy_Corrected);
CrossSection_name_Map Generate_CrossSection_histsNames_Daisy(MuonVar MuonVar_type, std::string Petal);
///============================================================================
CrossSection_name_Map Generate_CrossSection_histsNames_Daisy(std::string inputName,
   std::string Petal);
   ///============================================================================
  std::map<int, CrossSection_name_Map> Generate_CrossSection_histsNames_DaisyMap(MuonVar MuonVar_type);
  std::map<int, CrossSection_name_Map> Generate_2DCrossSection_histsNames_DaisyMap(std::string inputname );
///========================================================================
void Make_DaisyPlots_CrossSection_Plots(
  std::map<int, CrossSection_name_Map> inputDaisyNameMap,
  TFile& inputTFile, MuonVar MuonVar, std::string pdf, double POT_Data,
  double POT_MC,TCanvas *can, MnvPlotter *mnv_plot);
///========================================================================
void Make_DaisyPlots_2DCrossSection_Plots(
  std::map<int, CrossSection_name_Map> inputDaisyNameMap,
  TFile& inputTFile, Muon2DVar MuonVar,
  std::string pdf, double POT_Data,
  double POT_MC,TCanvas *can,
  MnvPlotter *mnv_plot);
///========================================================================
  std::string generateLatexFrame(const std::vector<int> pageNumbers, std::string presentationTitle,
    std::string plotsFileName, int daisyNumber);
///============================================================================
  std::vector<int> generateNumberPattern(int startingValue, std::vector<int>inputPattern);
///============================================================================
  void GenerateLatex_textfile(char *FileName, std::vector<int> StartingPages,
    std::string MuonName, std::string pdfname);
///============================================================================
  std::string generateLatexFrame_2DEffLayout( std::string pdfName,
      std::vector<int>& pageNumbers, int titleNumber);
///============================================================================
std::string generateLatexFrame_2D_Daisy(
  std::string& pdfName, std::vector<int>& pageNumbers, int titleNumber);
///============================================================================
void GenerateLatex_textfile_2DEff(char *FileName, std::vector<int> StartingPages,
       std::string MuonName, std::string pdfname);
///============================================================================
void GenerateLatex_textfile_2D_Daisy(char *FileName,
  std::vector<int> StartingPages,
  std::string MuonName, std::string pdfname);
///============================================================================

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
 char text_titleDaisy[2024];
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
auto PlaylistME_CrossSection_Path_2Dhelium = "/minerva/app/users/cnguyen/cmtuser/Minerva_v22r1p1Helium_GIT/NuCCSemiInclusiveHelium/Make_CrossSection/CrossSection2D.root";
auto PlaylistME_CrossSection_MasterAnaDevPath_Daisy = "/minerva/app/users/cnguyen/cmtuser/Minerva_v22r1p1Helium_GIT/NuCCSemiInclusiveHelium/Make_CrossSection/CrossSection_MasterAnaDev_DAISY.root";
auto PlaylistME_CrossSection_MasterAnaDevPath_Daisy2D = "/minerva/app/users/cnguyen/cmtuser/Minerva_v22r1p1Helium_GIT/NuCCSemiInclusiveHelium/Make_CrossSection/CrossSection_MasterAnaDev_2D_DAISY.root";



bool is_mc=true;bool isNOT_mc=false;
std::string pdf_CV = string(text_title_pdf4);
bool Stats_only = false;


auto PlaylistME_CrossSection_GENIE_version_Path = "/minerva/app/users/cnguyen/cmtuser/Minerva_v22r1p1Helium_GIT/NuCCSemiInclusiveHelium/Make_CrossSection/CrossSection_MK.root";

auto TrackerME_playlist_vector = GetTrackerPlayListVector();
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
//auto PlaylistME_Flux_helium = "/minerva/data/users/cnguyen/ME_Flux/flux_helium_Full.root";
//
//auto PlaylistME_Flux_helium_slice1 = "/minerva/data/users/cnguyen/ME_Flux/flux_helium_Slice1.root";
//auto PlaylistME_Flux_helium_slice2 = "/minerva/data/users/cnguyen/ME_Flux/flux_helium_Slice2.root";
//auto PlaylistME_Flux_helium_slice3 = "/minerva/data/users/cnguyen/ME_Flux/flux_helium_Slice3.root";
//auto PlaylistME_Flux_helium_slice4 = "/minerva/data/users/cnguyen/ME_Flux/flux_helium_Slice4.root";

//auto PlaylistME_Flux_helium_daisy0 = "/minerva/data/users/cnguyen/ME_Flux/flux_helium_Daisy0.root";
//auto PlaylistME_Flux_helium_daisy1 = "/minerva/data/users/cnguyen/ME_Flux/flux_helium_Daisy1.root";
//auto PlaylistME_Flux_helium_daisy2 = "/minerva/data/users/cnguyen/ME_Flux/flux_helium_Daisy2.root";
//auto PlaylistME_Flux_helium_daisy3 = "/minerva/data/users/cnguyen/ME_Flux/flux_helium_Daisy3.root";
//auto PlaylistME_Flux_helium_daisy4 = "/minerva/data/users/cnguyen/ME_Flux/flux_helium_Daisy4.root";
//auto PlaylistME_Flux_helium_daisy5 = "/minerva/data/users/cnguyen/ME_Flux/flux_helium_Daisy5.root";
//auto PlaylistME_Flux_helium_daisy6 = "/minerva/data/users/cnguyen/ME_Flux/flux_helium_Daisy6.root";
//auto PlaylistME_Flux_helium_daisy7 = "/minerva/data/users/cnguyen/ME_Flux/flux_helium_Daisy7.root";
//auto PlaylistME_Flux_helium_daisy8 = "/minerva/data/users/cnguyen/ME_Flux/flux_helium_Daisy8.root";
//auto PlaylistME_Flux_helium_daisy9 = "/minerva/data/users/cnguyen/ME_Flux/flux_helium_Daisy9.root";
//auto PlaylistME_Flux_helium_daisy10 = "/minerva/data/users/cnguyen/ME_Flux/flux_helium_Daisy10.root";
//auto PlaylistME_Flux_helium_daisy11 = "/minerva/data/users/cnguyen/ME_Flux/flux_helium_Daisy11.root";


////simple_flux_tracker_tracker.root
//auto PlaylistME_Flux_tracker = "../../MATFluxAndReweightFiles/flux_daisy/neutrinos/targets_2345_jointNueIMD/flux_with_errors/flux_tracker.root";// "/minerva/data/users/cnguyen/ME_Flux/flux_tracker_Full_Tracker.root";
////auto PlaylistME_Flux_tracker = "/minerva/data/users/cnguyen/ME_Flux/flux_tracker_tracker.root";
//auto PlaylistME_Flux_Tracker_rebin = "/minerva/data/users/cnguyen/ME_Flux/flux_tracker_tracker.root";
//auto PlaylistME_Flux_tracker_slice1 = "/minerva/data/users/cnguyen/ME_Flux/flux_helium_MasterAnaDev_Slice1.root";
//auto PlaylistME_Flux_tracker_slice2 = "/minerva/data/users/cnguyen/ME_Flux/flux_helium_MasterAnaDev_Slice2.root";
//auto PlaylistME_Flux_tracker_slice3 = "/minerva/data/users/cnguyen/ME_Flux/flux_helium_MasterAnaDev_Slice3.root";
//auto PlaylistME_Flux_tracker_slice4 = "/minerva/data/users/cnguyen/ME_Flux/flux_helium_MasterAnaDev_Slice4.root";
//
//TFile *TFile_Flux_helium = new TFile(PlaylistME_Flux_helium);
//TFile *TFile_Flux_helium_slice1 = new TFile(PlaylistME_Flux_helium_slice1);
//TFile *TFile_Flux_helium_slice2 = new TFile(PlaylistME_Flux_helium_slice2);
//TFile *TFile_Flux_helium_slice3 = new TFile(PlaylistME_Flux_helium_slice3);
//TFile *TFile_Flux_helium_slice4 = new TFile(PlaylistME_Flux_helium_slice4);
//
//
//TFile *TFile_Flux_helium_daisy0 = new TFile(PlaylistME_Flux_helium_daisy0);
//TFile *TFile_Flux_helium_daisy1 = new TFile(PlaylistME_Flux_helium_daisy1);
//TFile *TFile_Flux_helium_daisy2 = new TFile(PlaylistME_Flux_helium_daisy2);
//TFile *TFile_Flux_helium_daisy3 = new TFile(PlaylistME_Flux_helium_daisy3);
//TFile *TFile_Flux_helium_daisy4 = new TFile(PlaylistME_Flux_helium_daisy4);
//TFile *TFile_Flux_helium_daisy5 = new TFile(PlaylistME_Flux_helium_daisy5);
//TFile *TFile_Flux_helium_daisy6 = new TFile(PlaylistME_Flux_helium_daisy6);
//TFile *TFile_Flux_helium_daisy7 = new TFile(PlaylistME_Flux_helium_daisy7);
//TFile *TFile_Flux_helium_daisy8 = new TFile(PlaylistME_Flux_helium_daisy8);
//TFile *TFile_Flux_helium_daisy9 = new TFile(PlaylistME_Flux_helium_daisy9);
//TFile *TFile_Flux_helium_daisy10 = new TFile(PlaylistME_Flux_helium_daisy10);
//TFile *TFile_Flux_helium_daisy11 = new TFile(PlaylistME_Flux_helium_daisy11);
//
//auto Flux_helum_daisy0 = Get1DHist(*TFile_Flux_helium_daisy0,"flux");
//auto Flux_helum_daisy1 = Get1DHist(*TFile_Flux_helium_daisy1,"flux");
//auto Flux_helum_daisy2 = Get1DHist(*TFile_Flux_helium_daisy2,"flux");
//auto Flux_helum_daisy3 = Get1DHist(*TFile_Flux_helium_daisy3,"flux");
//auto Flux_helum_daisy4 = Get1DHist(*TFile_Flux_helium_daisy4,"flux");
//auto Flux_helum_daisy5 = Get1DHist(*TFile_Flux_helium_daisy5,"flux");
//auto Flux_helum_daisy6 = Get1DHist(*TFile_Flux_helium_daisy6,"flux");
//auto Flux_helum_daisy7 = Get1DHist(*TFile_Flux_helium_daisy7,"flux");
//auto Flux_helum_daisy8 = Get1DHist(*TFile_Flux_helium_daisy8,"flux");
//auto Flux_helum_daisy9 = Get1DHist(*TFile_Flux_helium_daisy9,"flux");
//auto Flux_helum_daisy10 = Get1DHist(*TFile_Flux_helium_daisy10,"flux");
//auto Flux_helum_daisy11 = Get1DHist(*TFile_Flux_helium_daisy11,"flux");
//
//auto Flux_helum_daisy0_rebin = Get1DHist(*TFile_Flux_helium_daisy0,"flux_rebined");
//auto Flux_helum_daisy1_rebin = Get1DHist(*TFile_Flux_helium_daisy1,"flux_rebined");
//auto Flux_helum_daisy2_rebin = Get1DHist(*TFile_Flux_helium_daisy2,"flux_rebined");
//auto Flux_helum_daisy3_rebin = Get1DHist(*TFile_Flux_helium_daisy3,"flux_rebined");
//auto Flux_helum_daisy4_rebin = Get1DHist(*TFile_Flux_helium_daisy4,"flux_rebined");
//auto Flux_helum_daisy5_rebin = Get1DHist(*TFile_Flux_helium_daisy5,"flux_rebined");
//auto Flux_helum_daisy6_rebin = Get1DHist(*TFile_Flux_helium_daisy6,"flux_rebined");
//auto Flux_helum_daisy7_rebin = Get1DHist(*TFile_Flux_helium_daisy7,"flux_rebined");
//auto Flux_helum_daisy8_rebin = Get1DHist(*TFile_Flux_helium_daisy8,"flux_rebined");
//auto Flux_helum_daisy9_rebin = Get1DHist(*TFile_Flux_helium_daisy9,"flux_rebined");
//auto Flux_helum_daisy10_rebin = Get1DHist(*TFile_Flux_helium_daisy10,"flux_rebined");
//auto Flux_helum_daisy11_rebin = Get1DHist(*TFile_Flux_helium_daisy11,"flux_rebined");
//



//auto Flux_helum = Get1DHist(*TFile_Flux_helium,"flux");
//auto Flux_helum_rebin = Get1DHist(*TFile_Flux_helium,"flux_rebined");
//auto Flux_helum_th1d = GetTH1DHist(*TFile_Flux_helium,"flux");
//auto Flux_helum_slice1 = Get1DHist(*TFile_Flux_helium_slice1,"flux");
//auto Flux_helum_slice2 = Get1DHist(*TFile_Flux_helium_slice2,"flux");
//auto Flux_helum_slice3 = Get1DHist(*TFile_Flux_helium_slice3,"flux");
//auto Flux_helum_slice4 = Get1DHist(*TFile_Flux_helium_slice4,"flux");
//
//auto Flux_helum_slice1_rebin = Get1DHist(*TFile_Flux_helium_slice1,"flux_rebined");
//auto Flux_helum_slice2_rebin = Get1DHist(*TFile_Flux_helium_slice2,"flux_rebined");
//auto Flux_helum_slice3_rebin = Get1DHist(*TFile_Flux_helium_slice3,"flux_rebined");
//auto Flux_helum_slice4_rebin = Get1DHist(*TFile_Flux_helium_slice4,"flux_rebined");


//Flux_helum_slice1->Divide(Flux_helum_slice1,Flux_helum_th1d);
//Flux_helum_slice2->Divide(Flux_helum_slice1,Flux_helum_th1d);
//Flux_helum_slice3->Divide(Flux_helum_slice1,Flux_helum_th1d);
//Flux_helum_slice4->Divide(Flux_helum_slice1,Flux_helum_th1d);
//Flux_helum_th1d->Divide(Flux_helum_th1d,Flux_helum_th1d);

//TFile *TFile_Flux_Tracker = new TFile(PlaylistME_Flux_tracker);

//TFile *TFile_Flux_Tracker_rebin = new TFile(PlaylistME_Flux_Tracker_rebin);
//TFile *TFile_Flux_Tracker_slice1 = new TFile(PlaylistME_Flux_tracker_slice1);
//TFile *TFile_Flux_Tracker_slice2 = new TFile(PlaylistME_Flux_tracker_slice2);
//TFile *TFile_Flux_Tracker_slice3 = new TFile(PlaylistME_Flux_tracker_slice3);
//TFile *TFile_Flux_Tracker_slice4 = new TFile(PlaylistME_Flux_tracker_slice4);
//
//auto Flux_Tracker = Get1DHist(*TFile_Flux_Tracker,"flux");
//auto Flux_Tracker_clone = Get1DHist(*TFile_Flux_Tracker,"flux");
//
//
//auto Flux_Tracker_rebin = Get1DHist(*TFile_Flux_Tracker_rebin,"flux_rebined");
//auto Flux_Tracker_rebin_flux = Get1DHist(*TFile_Flux_Tracker_rebin,"flux");
//
//auto Flux_Tracker_rebin_flux_clone = Get1DHist(*TFile_Flux_Tracker_rebin,"flux");
//Flux_Tracker_rebin->Scale( 1.0195);
//Flux_Tracker_rebin_flux_clone->Scale( 1.0195);

//auto Flux_Tracker_slice1 = Get1DHist(*TFile_Flux_Tracker_slice1,"flux");
//auto Flux_Tracker_slice2 = Get1DHist(*TFile_Flux_Tracker_slice2,"flux");
//auto Flux_Tracker_slice3 = Get1DHist(*TFile_Flux_Tracker_slice3,"flux");
//auto Flux_Tracker_slice4 = Get1DHist(*TFile_Flux_Tracker_slice4,"flux");

//Flux_Tracker->AddMissingErrorBandsAndFillWithCV(*Flux_helum);


  //DrawCVAndError_FromHIST(false ,Flux_Tracker, "" ,"E_{#nu}","#nu / m^2 / POT / GeV",  pdf_CV, false);



    //  void DrawCVAndError_From5HIST(MnvH1D *hist_Data_input, char *legend_Data_title,
    //                                TH1D *hist_1_input, char *legend_1_title,
    //                                TH1D *hist_2_input, char *legend_2_title,
    //                                TH1D *hist_3_input, char *legend_3_title,
    //                                TH1D *hist_4_input, char *legend_4_title,
    //                                TH1D *hist_5_input, char *legend_5_title,
    //                                Double_t normBinWidth,
    //                                std::vector<int> fillColors,
    //                                 char *histotitle ,std::string xaxislabel, std::string yaxislabel,
    //     std::string pdf_name, bool Setgrid, bool BinWidthNorm, double Ymax , bool setLogY );

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

auto GENIE_G18_02a_02_11a_playlistPath ="/minerva/app/users/cnguyen/cmtuser/Minerva_v22r1p1Helium_GIT/NuCCSemiInclusiveHelium/eventselection2D/CrossSection_G18_02a_02_11a_new3.root";
auto GENIE_G18_10a_02_11a_playlistPath ="/minerva/app/users/cnguyen/cmtuser/Minerva_v22r1p1Helium_GIT/NuCCSemiInclusiveHelium/eventselection2D/CrossSection_G18_10b_02_11a_new3.root";
auto GENIE_G18_02b_02_11a_playlistPath ="/minerva/app/users/cnguyen/cmtuser/Minerva_v22r1p1Helium_GIT/NuCCSemiInclusiveHelium/eventselection2D/CrossSection_G18_10a_02_11a_new3.root";
auto GENIE_G18_10b_02_11a_playlistPath ="/minerva/app/users/cnguyen/cmtuser/Minerva_v22r1p1Helium_GIT/NuCCSemiInclusiveHelium/eventselection2D/CrossSection_G18_02b_02_11a_new3.root";

Model_RootPathMAP Model_Paths;
Model_Paths.insert(std::make_pair(kME_GENIE_G18_02a_02_11a,GENIE_G18_02a_02_11a_playlistPath));
Model_Paths.insert(std::make_pair(kME_GENIE_G18_10a_02_11a,GENIE_G18_10a_02_11a_playlistPath));
Model_Paths.insert(std::make_pair(kME_GENIE_G18_02b_02_11a,GENIE_G18_02b_02_11a_playlistPath));
Model_Paths.insert(std::make_pair(kME_GENIE_G18_10b_02_11a,GENIE_G18_10b_02_11a_playlistPath));


Genie_Models PT_GenieModel("pt",Model_Paths);
Genie_Models PZ_GenieModel("pz",Model_Paths);
Genie_Models EGenieModel("E",Model_Paths);
Genie_Models AngleGenieModel("Angle",Model_Paths);


sprintf(text_title_pdf1, "PLOTS_%s_CrossSection_RATO_new.pdf(","" );
can -> Print(text_title_pdf1);
sprintf(text_title_pdf2, "PLOTS_%s_CrossSection_RATO_new.pdf","" );
sprintf(text_title_pdf3, "PLOTS_%s_CrossSection_RATO_new.pdf)","" );
sprintf(text_title_pdf4, "PLOTS_%s_CrossSection_RATO_new","" );
 pdf_CV = string(text_title_pdf4);

  std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;
  std::cout<< "  Ploting 1D Cross Section "<< std::endl;
  std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;




std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~       Starting Plotter: Kinematic Plots         ~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

TFile *TFile_CrossSection_tracker = new TFile(PlaylistME_CrossSection_MasterAnaDevPath);
TFile *TFile_CrossSection_tracker_Daisy = new TFile(PlaylistME_CrossSection_MasterAnaDevPath_Daisy);
TFile *TFile_CrossSection_helium = new TFile(PlaylistME_CrossSection_Path);
TFile *TFile_CrossSection_2Dhelium = new TFile(PlaylistME_CrossSection_Path_2Dhelium);
TFile *TFile_CrossSection_tracker_Daisy_2D = new TFile(PlaylistME_CrossSection_MasterAnaDevPath_Daisy2D);
auto muon_vector = GetMUONVaribles_Total();
bool isFull = true;
bool isEmpty = false;
bool DoBinWidthNorm = true;
bool DontBinWidthNorm = false;
bool Makelog = false;


auto muonE_full_names = Generate_CrossSection_histsNames_withInteraction_DISbreakdown(muon_vector[0], "Tracker", isFull);
auto muonE_helium_names = Generate_CrossSection_histsNames_withInteraction_DISbreakdown_helium(muon_vector[0], "Full", isFull);
auto Map_MuonE_Full_hist = Generate_CrossSection_Hist_Map(*TFile_CrossSection_tracker, muonE_full_names);
auto Map_MuonE_Full_hist_helium = Generate_CrossSection_Hist_Map(*TFile_CrossSection_helium, muonE_helium_names);

std::map<int, CrossSection_name_Map> muonE_Daisy_names  = Generate_CrossSection_histsNames_DaisyMap(muon_vector[0]);


sprintf(text_titleDaisy, "Daisy_Plots_%s.pdf(", "MuonE");
can -> Print(text_titleDaisy);
sprintf(text_titleDaisy, "Daisy_Plots_%s", "MuonE");
std::string Daisy_plot_MuonEname(text_titleDaisy);
Make_DaisyPlots_CrossSection_Plots(muonE_Daisy_names,*TFile_CrossSection_tracker_Daisy,muon_vector[0], Daisy_plot_MuonEname, Tracker_Data_POT, Tracker_MC_POT,can, mnv_plot);
sprintf(text_titleDaisy, "Daisy_Plots_%s.pdf)", "MuonE");
can -> Print(text_titleDaisy);

auto MuonE_Combined_Daisy = Get1DHist(*TFile_CrossSection_tracker_Daisy, "h_MuonE_eff_corr_tracker_to_helium_combined");
auto MuonE_Combined_Daisy_CrossSection = Get1DHist(*TFile_CrossSection_tracker_Daisy, "h_MuonE_Tracker_CrossSection_Petal_correction");



auto MuonE_Mig = Get2DHist(*TFile_CrossSection_tracker, muonE_full_names[mvnreponse_Mig]);
DrawMagration_heatMap_Label(MuonE_Mig, "RECO E_{#mu}","TRUTH E_{#mu}",  "Migration E_{#mu}", text_title_pdf2, can, mnv_plot, 9);
DrawMagration_heatMap_Label(MuonE_Mig, "RECO E_{#mu}","TRUTH E_{#mu}",  "Migration E_{#mu} (ROWNorm)", text_title_pdf2, can, mnv_plot, 3);
MakeCrossSectionPlots_Interaction_Ratio(Map_MuonE_Full_hist, Map_MuonE_Full_hist_helium, "GeV", pdf_CV,Makelog,DoBinWidthNorm ,muon_vector[0], "Combined Playlist" ,Tracker_Data_POT, Tracker_MC_POT, EGenieModel,can, mnv_plot, true, MuonE_Combined_Daisy,MuonE_Combined_Daisy_CrossSection);

//PrintCrossSection_MapName(muonE_full_names,"muonE_full_names");
////////////////////////////////////////////////////////////////////////////////
//// PZ
////////////////////////////////////////////////////////////////////////////////

auto muonPZ_full_names = Generate_CrossSection_histsNames_withInteraction_DISbreakdown(muon_vector[1], "Tracker", isFull);
auto muonPZ_helium_names = Generate_CrossSection_histsNames_withInteraction_DISbreakdown_helium(muon_vector[1], "Full", isFull);
auto Map_MuonPZ_Full_hist = Generate_CrossSection_Hist_Map(*TFile_CrossSection_tracker, muonPZ_full_names);
std::map<int, CrossSection_name_Map> muonPZ_Daisy_names  = Generate_CrossSection_histsNames_DaisyMap(muon_vector[1]);

sprintf(text_titleDaisy, "Daisy_Plots_%s.pdf(", "MuonPZ");
can -> Print(text_titleDaisy);
sprintf(text_titleDaisy, "Daisy_Plots_%s", "MuonPZ");
std::string Daisy_plot_MuonPZname(text_titleDaisy);
Make_DaisyPlots_CrossSection_Plots(muonPZ_Daisy_names,*TFile_CrossSection_tracker_Daisy,muon_vector[1], Daisy_plot_MuonPZname, Tracker_Data_POT, Tracker_MC_POT,can, mnv_plot);
sprintf(text_titleDaisy, "Daisy_Plots_%s.pdf)", "MuonPZ");
can -> Print(text_titleDaisy);



auto Map_MuonPZ_Full_hist_helium = Generate_CrossSection_Hist_Map(*TFile_CrossSection_helium, muonPZ_helium_names);
auto MuonPZ_Mig = Get2DHist(*TFile_CrossSection_tracker, muonPZ_full_names[mvnreponse_Mig]);

auto MuonPZ_Combined_Daisy = Get1DHist(*TFile_CrossSection_tracker_Daisy, "h_MuonPZ_eff_corr_tracker_to_helium_combined");
auto MuonPZ_Combined_Daisy_CrossSection = Get1DHist(*TFile_CrossSection_tracker_Daisy, "h_MuonPZ_Tracker_CrossSection_Petal_correction");



DrawMagration_heatMap_Label(MuonPZ_Mig, "RECO P_{Z}","TRUTH P_{Z}",  "Migration P_{Z}", text_title_pdf2, can, mnv_plot, 9);
DrawMagration_heatMap_Label(MuonPZ_Mig, "RECO P_{Z}","TRUTH P_{Z}",  "Migration P_{Z} (ROWNorm)", text_title_pdf2, can, mnv_plot, 3);

MakeCrossSectionPlots_Interaction_Ratio(Map_MuonPZ_Full_hist, Map_MuonPZ_Full_hist_helium, "GeV", pdf_CV,Makelog,DoBinWidthNorm ,muon_vector[1], "Combined Playlist", Tracker_Data_POT, Tracker_MC_POT, PZ_GenieModel, can, mnv_plot, false, MuonPZ_Combined_Daisy, MuonPZ_Combined_Daisy_CrossSection );

////////////////////////////////////////////////////////////////////////////////
//// PT
////////////////////////////////////////////////////////////////////////////////

auto muonPT_full_names = Generate_CrossSection_histsNames_withInteraction_DISbreakdown(muon_vector[2], "Tracker", isFull);
auto Map_MuonPT_Full_hist = Generate_CrossSection_Hist_Map(*TFile_CrossSection_tracker, muonPT_full_names);
std::map<int, CrossSection_name_Map> muonPT_Daisy_names  = Generate_CrossSection_histsNames_DaisyMap(muon_vector[2]);

sprintf(text_titleDaisy, "Daisy_Plots_%s.pdf(", "MuonPT");
can -> Print(text_titleDaisy);
sprintf(text_titleDaisy, "Daisy_Plots_%s", "MuonPT");
std::string Daisy_plot_MuonPTname(text_titleDaisy);
Make_DaisyPlots_CrossSection_Plots(muonPT_Daisy_names,*TFile_CrossSection_tracker_Daisy,muon_vector[2], Daisy_plot_MuonPTname, Tracker_Data_POT, Tracker_MC_POT,can, mnv_plot);
sprintf(text_titleDaisy, "Daisy_Plots_%s.pdf)", "MuonPT");
can -> Print(text_titleDaisy);

std::vector<int> SlidePages{2, 20, 38, 56, 74, 92, 110, 128, 146, 164, 182, 200};

GenerateLatex_textfile("MuonPT_Latex_daisy_slides.txt", SlidePages, "Muon PT ",Daisy_plot_MuonPTname + ".pdf");






auto muonPT_helium_names = Generate_CrossSection_histsNames_withInteraction_DISbreakdown_helium(muon_vector[2], "Full", isFull);
auto Map_MuonPT_Full_hist_helium = Generate_CrossSection_Hist_Map(*TFile_CrossSection_helium, muonPT_helium_names);


auto MuonPT_Mig = Get2DHist(*TFile_CrossSection_tracker, muonPT_full_names[mvnreponse_Mig]);

auto MuonPT_Combined_Daisy = Get1DHist(*TFile_CrossSection_tracker_Daisy, "h_MuonPT_eff_corr_tracker_to_helium_combined");
auto MuonPT_Combined_Daisy_CrossSection = Get1DHist(*TFile_CrossSection_tracker_Daisy, "h_MuonPT_Tracker_CrossSection_Petal_correction");




DrawMagration_heatMap_Label(MuonPT_Mig, "RECO P_{T}","TRUTH P_{T}",  "Migration P_{T}", text_title_pdf2, can, mnv_plot, 9);
DrawMagration_heatMap_Label(MuonPT_Mig, "RECO P_{T}","TRUTH P_{T}",  "Migration P_{T} (ROWNorm)", text_title_pdf2, can, mnv_plot, 3);


MakeCrossSectionPlots_Interaction_Ratio(Map_MuonPT_Full_hist, Map_MuonPT_Full_hist_helium,  "GeV", pdf_CV,Makelog,DoBinWidthNorm ,muon_vector[2],
"Combined Playlist", Tracker_Data_POT, Tracker_MC_POT, PT_GenieModel,can, mnv_plot, false ,MuonPT_Combined_Daisy, MuonPT_Combined_Daisy_CrossSection );


////////////////////////////////////////////////////////////////////////////////
//// Theta
////////////////////////////////////////////////////////////////////////////////



auto muonTheta_full_names = Generate_CrossSection_histsNames_withInteraction_DISbreakdown(muon_vector[3], "Tracker", isFull);
auto Map_MuonTheta_Full_hist = Generate_CrossSection_Hist_Map(*TFile_CrossSection_tracker, muonTheta_full_names);
auto muonTheta_helium_names = Generate_CrossSection_histsNames_withInteraction_DISbreakdown_helium(muon_vector[3], "Full", isFull);
auto Map_MuonTheta_Full_hist_helium = Generate_CrossSection_Hist_Map(*TFile_CrossSection_helium, muonTheta_helium_names);

std::map<int, CrossSection_name_Map> muonTheta_Daisy_names  = Generate_CrossSection_histsNames_DaisyMap(muon_vector[3]);

auto MuonTheta_Mig = Get2DHist(*TFile_CrossSection_tracker, muonTheta_full_names[mvnreponse_Mig]);


sprintf(text_titleDaisy, "Daisy_Plots_%s.pdf(", "MuonTheta");
can -> Print(text_titleDaisy);
sprintf(text_titleDaisy, "Daisy_Plots_%s", "MuonTheta");
std::string Daisy_plot_MuonThetaname(text_titleDaisy);
Make_DaisyPlots_CrossSection_Plots(muonTheta_Daisy_names, *TFile_CrossSection_tracker_Daisy,muon_vector[3], Daisy_plot_MuonThetaname, Tracker_Data_POT, Tracker_MC_POT,can, mnv_plot);
sprintf(text_titleDaisy, "Daisy_Plots_%s.pdf)", "MuonTheta");
can -> Print(text_titleDaisy);


auto MuonTheta_Combined_Daisy = Get1DHist(*TFile_CrossSection_tracker_Daisy, "h_MuonTheta_eff_corr_tracker_to_helium_combined");
auto MuonTheta_Combined_Daisy_CrossSection = Get1DHist(*TFile_CrossSection_tracker_Daisy, "h_MuonTheta_Tracker_CrossSection_Petal_correction");




DrawMagration_heatMap_Label(MuonTheta_Mig, "RECO #theta_{#theta}","TRUTH #theta_{#theta}",  "Migration #theta_{#theta}", text_title_pdf2, can, mnv_plot, 9);
DrawMagration_heatMap_Label(MuonTheta_Mig, "RECO #theta_{#theta}","TRUTH #theta_{#theta}",  "Migration #theta_{#theta} (ROWNorm)", text_title_pdf2, can, mnv_plot, 3);
MakeCrossSectionPlots_Interaction_Ratio(Map_MuonTheta_Full_hist, Map_MuonTheta_Full_hist_helium, "Deg", pdf_CV,Makelog,DoBinWidthNorm,
                                         muon_vector[3], "Combined Playlist", Tracker_Data_POT, Tracker_MC_POT,
                                         AngleGenieModel,can, mnv_plot, false, MuonTheta_Combined_Daisy, MuonTheta_Combined_Daisy_CrossSection );


//auto secondtrack_RECO = Get1DHist(*TFile_CrossSection, );
//auto secondtrack_Data = Get1DHist(*TFile_CrossSection, );
auto secondtrack_Eff = Get1DHist(*TFile_CrossSection_tracker,"h_SecondTrackAngle_efficiency" );
DrawCVAndError_FromHistPointer(secondtrack_Eff, "Recoil Track Angle (wrtb) Efficiency" ,"#theta_{recoil} [deg]", "Efficiency", pdf_CV,  false, false);


//DrawSTACKfromHistFilio_COMBINED(TrackerTFile_Map_MC_RECO, POT_Ratio_MC,
//  TrackerTFile_Map_DATA, POT_Ratio,
//  "h_MuonPZ" , "h_Data_MuonPZ", "CH Muon P_{Z}",
//  "P_{Z} ", pdf_CV, true, "[GeV]", kCH_Signal_type, false, false );
//
//DrawSTACKfromHistFilio_COMBINED(TrackerTFile_Map_MC_RECO, POT_Ratio_MC,
//  TrackerTFile_Map_DATA, POT_Ratio,
//  "h_MuonPT" , "h_Data_MuonPT", "CH Muon P_{T}",
//  "P_{T}", pdf_CV, true, "[GeV]", kCH_Signal_type, false, false );
//
//DrawSTACKfromHistFilio_COMBINED(TrackerTFile_Map_MC_RECO, POT_Ratio_MC,
//  TrackerTFile_Map_DATA, POT_Ratio,
//  "h_MuonTheta" , "h_Data_MuonTheta", " Muon Angle (wrtb)",
//  "#theta_{#mu} (wrtb) ", pdf_CV, true, "[Deg]", kCH_Signal_type, false, false );
//
//DrawSTACKfromHistFilio_COMBINED(TrackerTFile_Map_MC_RECO, POT_Ratio_MC,
//  TrackerTFile_Map_DATA, POT_Ratio,
//  "h_MuonE" , "h_Data_MuonE", "Muon KE",
//  "E_{#mu}", pdf_CV, true, "[GeV]", kCH_Signal_type, false, false );

////////////////////////////////////////////////////////////////////////////////
//// PT Vs PZ
////////////////////////////////////////////////////////////////////////////////


auto muon_tracker_ptpz_names = Generate_2DCrossSection_histsNames_withInteraction_DISbreakdown_forMasterAna("h_MuonPT_PZ", "Tracker", true);
auto Map_PT_PZ_tracker_hists = Generate_2DCrossSection_Hist_Map(*TFile_CrossSection_tracker, muon_tracker_ptpz_names);

auto MuonPT_PZ_helium_names = Generate_2DCrossSection_histsNames_withInteraction_DISbreakdown_helium("h_MuonPT_PZ",kPT_PZ, "Full", isFull ,true);
auto Map_PT_PZ_helium_hists = Generate_2DCrossSection_Hist_Map(*TFile_CrossSection_2Dhelium, MuonPT_PZ_helium_names);

//Migration_MnvH2D_Map MigHist = Generate_CrossSection_Mig_Hist_Map(*TFile_CrossSection,muon_vector);


std::map<int, CrossSection_name_Map> CrossSection2D_DaisyNames =  Generate_2DCrossSection_histsNames_DaisyMap("h_MuonPT_PZ");

sprintf(text_titleDaisy, "Daisy_Plots_%s.pdf(", "MuonPT_PZ");
can -> Print(text_titleDaisy);
sprintf(text_titleDaisy, "Daisy_Plots_%s", "MuonPT_PZ");
std::string Daisy_plot_MuonpTpZname(text_titleDaisy);

Make_DaisyPlots_2DCrossSection_Plots(
  CrossSection2D_DaisyNames,
  *TFile_CrossSection_tracker_Daisy_2D, kPT_PZ,
  Daisy_plot_MuonpTpZname,  Tracker_Data_POT, Tracker_MC_POT,can, mnv_plot);

  sprintf(text_titleDaisy, "Daisy_Plots_%s.pdf)", "MuonPT_PZ");
  can -> Print(text_titleDaisy);


  GenerateLatex_textfile_2DEff("MuonPT_PZ_Latex_daisy_Effslides.txt",
   SlidePages,"$P_{T}$ vs $P_{Z}$", Daisy_plot_MuonpTpZname);

std::vector<int> SlidePagesRate{10, 30, 46, 64, 82, 100, 118, 136, 154, 172, 190, 208};

   GenerateLatex_textfile_2D_Daisy("MuonPT_PZ_Latex_daisy_Rateslides.txt",
    SlidePagesRate,"$P_{T}$ vs $P_{Z}$", Daisy_plot_MuonpTpZname);

//auto MuonPT_Combined_Daisy = Get1DHist(*TFile_CrossSection_tracker_Daisy, "h_MuonPT_eff_corr_tracker_to_helium_combined");
auto MuonPT_PZ_Combined_Daisy_CrossSection = Get2DHist(*TFile_CrossSection_tracker_Daisy_2D, "h_MuonPT_PZ_Tracker_CrossSection_Petal_correction");


  Make2DCrossSectionPlots_Interaction_Ratio(Map_PT_PZ_tracker_hists, Map_PT_PZ_helium_hists,
    "[GeV^{2}]", pdf_CV, Makelog,  true,
    kPT_PZ, "Combined", can, mnv_plot,Tracker_Data_POT, Tracker_MC_POT, MuonPT_PZ_Combined_Daisy_CrossSection);

    std::vector<int> Helium9_colorScheme = {
      TColor::GetColor("#EEFF00"), // neonyellow,
        TColor::GetColor("#ffc922"), //'sunset yellow'
        TColor::GetColor("#DF00FF"), //'psychedelic Purple
        TColor::GetColor("#87CEEB"),//'skyblue'
      TColor::GetColor("#0859C6"), //blue
      TColor::GetColor("#654522"), // yellowishbrown,
      TColor::GetColor(43, 206,  72 ), //green
      TColor::GetColor("#FF0800"),//2 candy Apple
      TColor::GetColor("#90AD1C"),
      TColor::GetColor("#BABABA"), //Gray
      TColor::GetColor("#00FFFF"),//'aqua'
      TColor::GetColor("#F1B6DA"),//pink
      TColor::GetColor("#00A86B"),//'Jade'
      TColor::GetColor("#FAFAD2"),  // LightGoldenRodYellow
      TColor::GetColor("#800000"),  // Maroon
      TColor::GetColor("#555555"),  // dark grey
      TColor::GetColor(0, 153, 143 ), //turquoise
      TColor::GetColor("#654522"), // yellowishbrown,
      TColor::GetColor("#8db600"), // yellowgreen,
      TColor::GetColor("#D3D3D3"),  //'lightgrey'
       TColor::GetColor("#90AD1C"),
       TColor::GetColor("#CCDDAA")
    };

 //char trackerstackname_char[muon_tracker_ptpz_names[Data_signal].length()+1];
 //strcpy(trackerstackname_char, muon_tracker_ptpz_names[Data_signal].c_str());
/*
    DrawSTACKfromHistFilio_FromTFile2D(TFile_CrossSection_tracker,  "h_Muon_PZ_PT" ,  TFile_CrossSection_tracker,
      trackerstackname_char, 1.0, "Signal and BG",
      "P_{Z}", "P_{T}","Nevents",
       pdf_CV, DoBinWidthNorm, kCH_Signal_type, true, false,
        YMultipliers, XMultipliers );
*/
        auto Signal = Get2DHist(*TFile_CrossSection_tracker,"h_Muon_PZ_PT_SignalSelection_Signal" );
        Signal->SetTitle("Signal");
        auto BG_NC = Get2DHist(*TFile_CrossSection_tracker,"h_Muon_PZ_PT_SignalSelection_BG_NC" );
        BG_NC->SetTitle("BG NC");
        auto BG_wrongsign = Get2DHist(*TFile_CrossSection_tracker,"h_Muon_PZ_PT_SignalSelection_BG_WrongSign" );
        BG_wrongsign->SetTitle("BG Wrong Sign");
        auto BG_Neutral_2ndtrack = Get2DHist(*TFile_CrossSection_tracker,"h_Muon_PZ_PT_SignalSelection_BG_Neutral_2ndtrack" );
        BG_wrongsign->SetTitle("BG Neutral 2ndtrack");
        TObjArray stack;

        stack.Add(Signal);
        stack.Add(BG_NC);
        stack.Add(BG_wrongsign);
        stack.Add(BG_Neutral_2ndtrack);
        bool doMultipliers= false;
        std::vector<double> XMultipliers{1,1,1,1,1,1,1,1};
        std::vector<double> YMultipliers{1,1,1,1,1,4,4,1};

std::cout<<"trying to print PlotDataStackedMC2D_ProjY"<<std::endl;

PlotDataStackedMC2D_ProjY(Map_PT_PZ_tracker_hists[Data_signal],
                                          stack,
                                        Helium9_colorScheme,
                                        text_title_pdf2, "Signal and BG",
                                        "P_{Z}", "P_{T}",
                                        "Nevents",
                                        99, false,  doMultipliers,
                                         YMultipliers,
                                        DoBinWidthNorm, .03
                                      );

PlotDataStackedMC2D_ProjX(Map_PT_PZ_tracker_hists[Data_signal],
                          stack,
                          Helium9_colorScheme,
                          text_title_pdf2, "Signal and BG",
                          "P_{T}", "P_{Z}",
                          "Nevents",
                          99, false,  doMultipliers,
                          XMultipliers,
                          DoBinWidthNorm, .03
                        );



//DrawSTACKfromHistFilio_COMBINED(TrackerTFile_Map_MC_RECO, POT_Ratio_MC,
//  TrackerTFile_Map_DATA, POT_Ratio,
//  "h_secTrk_tracklength" , "h_Data_secTrk_tracklength", "Leading Recoil Tracklength",
//  "Track Length", pdf_CV, true, "cm", kParticle, false, false );
//
//DrawSTACKfromHistFilio_COMBINED(TrackerTFile_Map_MC_RECO, POT_Ratio_MC,
//  TrackerTFile_Map_DATA, POT_Ratio,
//  "h_secTrk_Theta" , "h_Data_secondTrkTheta", "Leading Recoil Track Angle (wrtb)",
//  "Recoil Angle (wrtb)", pdf_CV, true, "cm", kParticle, false, false );


//auto EuvsVertexX = Get2DHist(*TFile_CrossSection_helium,"h2d_Enu_TRUE_vertex_X");
//auto EuvsVertexY = Get2DHist(*TFile_CrossSection_helium,"h2d_Enu_TRUE_vertex_Y");

//TH2D EuvsVertexX_th1d = EuvsVertexX->GetCVHistoWithStatError();
//TH2D EuvsVertexY_th1d = EuvsVertexY->GetCVHistoWithStatError();

//TH2D *histpointerA = &EuvsVertexX_th1d;
//TH2D *histpointerB = &EuvsVertexY_th1d;

std::vector<double> para_vector;
std::vector<double> wgt_error_vector;
double chi2;







 can -> Print(text_title_pdf3);
 can->Close();

 sprintf(Latex_name, "PLOTS_%s_Latex_Muon_CV_ERRORS", timeset_nonstacks);








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

/////////////////////////////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<ME_helium_Playlists> GetPlayListVector()
{
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
/////////////////////////////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<MuonVar> GetMUONVaribles_Total()
{
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<MuonVar> MuonVars;
  MuonVars.push_back(kE);
  MuonVars.push_back(kP_Z);
  MuonVars.push_back(kP_T);

  MuonVars.push_back(kAngleWRTB);


  return MuonVars;
//#endif
}
/////////////////////////////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////////////////////////////
CrossSection_name_Map Generate_CrossSection_histsNames(
  MuonVar MuonVar_type, std::string playlist, bool isFUll)
{

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
/////////////////////////////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////////////////////////////
CrossSection_name_Map Generate_CrossSection_histsNames_withInteraction(
  MuonVar MuonVar_type, std::string playlist, bool isFUll)
  {

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
/////////////////////////////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////////////////////////////
CrossSection_name_Map Generate_CrossSection_histsNames_withInteraction_DISbreakdown(
  MuonVar MuonVar_type, std::string playlist, bool isFUll)
  {

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

    std::string hist1_name_Data_signal_BG_subtracted = hist_name +"_" + playlist +  "_Data_BG_Subtracted";
    Name_Map.insert(std::make_pair(Data_signal_BG_subtracted, hist1_name_Data_signal_BG_subtracted));

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
  else if(isFUll==false)
  {

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
/////////////////////////////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////////////////////////////
CrossSection_name_Map Generate_CrossSection_histsNames_Daisy(MuonVar MuonVar_type, std::string Petal){

  CrossSection_name_Map Name_Map;
  std::string Daisy = "_Daisy" + Petal;

  auto hist_name = GetMuonVarHistName(MuonVar_type);
  std::string hist1_name = hist_name + Daisy + "_Data_Signal";
  Name_Map.insert(std::make_pair(Data_signal, hist1_name));

  std::string hist1_name_RECO_BG = hist_name + Daisy + "_RECO_BG";
  Name_Map.insert(std::make_pair(MC_reco_BG, hist1_name_RECO_BG));

  std::string hist1_name_RECO = hist_name + Daisy + "_RECO_Signal";
  Name_Map.insert(std::make_pair(MC_reco, hist1_name_RECO));

  std::string hist1_name_Data_BG_subtracted = hist_name + Daisy + "_Data_BGSubtracted";
  Name_Map.insert(std::make_pair(Data_signal_BGsub_potNorm, hist1_name_Data_BG_subtracted));

  std::string unfolded_name =  hist_name + Daisy + "_Data_BGSubtracted_Unfolded";
  Name_Map.insert(std::make_pair(Data_signal_unfolded, unfolded_name));

  std::string eff_name = hist_name + Daisy + "_Efficiency";
  Name_Map.insert(std::make_pair(Eff, eff_name));

  std::string eff_Corrected_name = hist_name +"_Data_EffiencyCorrect_Daisy_" + Petal;
  Name_Map.insert(std::make_pair(Data_signal_unfolded_effcorrected, eff_Corrected_name));

  std::string TrueSignal_name =  hist_name + Daisy + "_effDom";
  Name_Map.insert(std::make_pair(dom_Eff, TrueSignal_name));

  return Name_Map;

}

/////////////////////////////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////////////////////////////
CrossSection_name_Map Generate_CrossSection_histsNames_Daisy(std::string inputName,
   std::string Petal)
   {

  CrossSection_name_Map Name_Map;
  std::string Daisy = inputName + "_Daisy" + Petal;

  std::string hist1_name =   Daisy + "_Data_Signal";
  Name_Map.insert(std::make_pair(Data_signal, hist1_name));

  std::string hist1_name_RECO_BG =  Daisy + "_RECO_BG";
  Name_Map.insert(std::make_pair(MC_reco_BG, hist1_name_RECO_BG));

  std::string hist1_name_RECO =   Daisy + "_RECO";
  Name_Map.insert(std::make_pair(MC_reco, hist1_name_RECO));

  std::string hist1_name_Data_BG_subtracted =   Daisy + "_Data_BGSubtracted";
  Name_Map.insert(std::make_pair(Data_signal_BGsub_potNorm, hist1_name_Data_BG_subtracted));

  std::string unfolded_name =    Daisy + "_Data_BGSubtracted_Unfolded";
  Name_Map.insert(std::make_pair(Data_signal_unfolded, unfolded_name));

  std::string eff_name =   Daisy + "_Efficiency";
  Name_Map.insert(std::make_pair(Eff, eff_name));

  std::string eff_Corrected_name = inputName + "_Data_EffiencyCorrect_Daisy_" + Petal;
  Name_Map.insert(std::make_pair(Data_signal_unfolded_effcorrected, eff_Corrected_name));

  std::string TrueSignal_name =    Daisy + "_effDom";
  Name_Map.insert(std::make_pair(dom_Eff, TrueSignal_name));

  std::string mvnreponse_RECO_name = Daisy + "_mvnreponse_RECO";
  Name_Map.insert(std::make_pair(mvnreponse_RECO, mvnreponse_RECO_name));

  std::string mvnreponse_true_name = Daisy + "_mvnreponse_TRUE";
  Name_Map.insert(std::make_pair(mvnreponse_TRUE, mvnreponse_true_name));

  std::string mvnreponse_mig_name = Daisy + "_Mig";
  Name_Map.insert(std::make_pair(mvnreponse_Mig, mvnreponse_mig_name));

  return Name_Map;

}
/////////////////////////////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////////////////////////////

std::string GetMigDaisy(MuonVar MuonVar_type, std::string Petal){

  auto hist_name = GetMuonVarHistName(MuonVar_type);
  std::string Daisy = "_Daisy" + Petal;
  std::string hist1_name_MIG = hist_name + Daisy + "_Mig";
  return hist1_name_MIG;

};
/////////////////////////////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////////////////////////////

std::map<int, CrossSection_name_Map> Generate_CrossSection_histsNames_DaisyMap(MuonVar MuonVar_type){

  std::vector<std::string> Petal_list{"0","1","2","3","4","5","6","7","8","9","10","11"};
  std::map<int, CrossSection_name_Map> outputMap;
  int mapnumber = 0;
  for(auto petal : Petal_list){
    CrossSection_name_Map Daisyname = Generate_CrossSection_histsNames_Daisy(MuonVar_type, petal);
    outputMap.insert(std::make_pair(mapnumber, Daisyname));
    mapnumber++;
  }
  return outputMap;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////////////////////////////

std::map<int, CrossSection_name_Map> Generate_2DCrossSection_histsNames_DaisyMap(std::string inputname ){

  std::vector<std::string> Petal_list{"0","1","2","3","4","5","6","7","8","9","10","11"};
  std::map<int, CrossSection_name_Map> outputMap;
  int mapnumber = 0;
  for(auto petal : Petal_list){
    CrossSection_name_Map Daisyname = Generate_CrossSection_histsNames_Daisy(inputname, petal);
    outputMap.insert(std::make_pair(mapnumber, Daisyname));
    mapnumber++;
  }
  return outputMap;
}


/////////////////////////////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////////////////////////////
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
/////////////////////////////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////////////////////////////
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
/////////////////////////////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////////////////////////////
Migration_MnvH2D_Map Generate_CrossSection_Mig_Hist_Map(
  TFile& file, std::vector<MuonVar> muon_vector)
{
  Migration_MnvH2D_Map Hist_Map;
  for(auto Muon:muon_vector){
    auto mig_type = Migration_muonType(Muon);
    std::string Name = GetMuonVarHistName(Muon) + "_Mig";
    auto hist_2D = Get2DHist(file, Name );
    Hist_Map.insert(std::make_pair(mig_type, hist_2D));

  }

    return Hist_Map;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////////////////////////////
void MakeCrossSectionPlots_Interaction_Ratio(
  CrossSection_MnvH1D_Map CrossSection_map,
  CrossSection_MnvH1D_Map CrossSection_map_helium,
  std::string cross_section_units, std::string pdf,
  bool MakeXaxisLOG,bool doBinwidth , MuonVar MuonVar,
  char *Playlist_name, double POT_Data, double POT_MC,
  Genie_Models Modelinputs, TCanvas *can,
  MnvPlotter *plot, bool makepieInteraction){


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

std::string X_axis_true = "TRUE " + GetMuonVarAXISName(MuonVar);
char X_axis_true_char[X_axis_true.length()+1];
strcpy(X_axis_true_char,X_axis_true.c_str());

char pdf_char1[pdf.length()+1];
strcpy(pdf_char1, pdf.c_str());


bool dontBinwidthNorm = false;

auto true_clone = CrossSection_map[dom_Eff]->Clone("true_clone");

char title_Signal_TRUTH_char[title_Signal_TRUTH.length()+1];
strcpy(title_Signal_TRUTH_char,title_Signal_TRUTH.c_str());
DrawCVAndError_FromHistPointer(CrossSection_map[dom_Eff], title_Signal_TRUTH_char ,X_axis, EventBin, pdf,  doBinwidth, MakeXaxisLOG);
std::cout<<"Made CrossSection_map[dom_Eff]" << std::endl;

std::string title_Signal_nomEff = MuonTitle + " Selection Nom Eff";
char title_Signal_nomEff_char[title_Signal_nomEff.length()+1];
strcpy(title_Signal_nomEff_char,title_Signal_nomEff.c_str());
DrawCVAndError_FromHistPointer(CrossSection_map[nom_Eff], title_Signal_nomEff_char ,X_axis, EventBin, pdf,  doBinwidth, MakeXaxisLOG);
std::cout<<"Made CrossSection_map[nom_Eff]" << std::endl;


std::string title_Signal = MuonTitle + " Event Selection";
char title_Signal_char[title_Signal.length()+1];
strcpy(title_Signal_char,title_Signal.c_str());
DrawCVAndError_FromHistPointer(CrossSection_map[Data_signal], title_Signal_char ,X_axis, EventBin, pdf,  doBinwidth, MakeXaxisLOG);
std::cout<<"Made CrossSection_map[Data_signal]" << std::endl;


Draw_DataWITHMC_SingleHistinput_withRatioCrossSection(CrossSection_map[RECO_signal], CrossSection_map[Data_signal],
                                           Playlist_name, pdf, title_Signal_char, unit, X_axis_char, EventBin_noUnits_char,
                                          doBinwidth, MakeXaxisLOG,  false);

std::string title_BG = MuonTitle + "BG Subtracted Data";
char title_BG_char[title_BG.length()+1];
strcpy(title_BG_char,title_BG.c_str());



Draw_DataWITHMC_SingleHistinput_withRatioCrossSection(CrossSection_map[RECO_signal], CrossSection_map[Data_signal_BG_subtracted],
                                           Playlist_name, pdf, title_BG_char, unit, X_axis_char, EventBin_noUnits_char,
                                          doBinwidth, MakeXaxisLOG,  false);






Draw_DataWITHMC_SingleHistinput_withRatioCrossSection(true_clone, CrossSection_map[Data_signal_BG_subtracted],
                                           Playlist_name, pdf, title_BG_char, unit, X_axis_true_char, EventBin_noUnits_char,
                                          doBinwidth, MakeXaxisLOG,  false);



std::string title_unfolded = MuonTitle + " [Unfolded]";
char title_unfolded_char[title_unfolded.length()+1];
strcpy(title_unfolded_char,title_unfolded.c_str());
DrawCVAndError_FromHistPointer(CrossSection_map[Data_signal_unfolded], title_unfolded_char ,X_axis, EventBin, pdf,  doBinwidth, MakeXaxisLOG);

Draw_DataWITHMC_SingleHistinput_withRatioCrossSection(true_clone, CrossSection_map[Data_signal_unfolded],
                                           Playlist_name, pdf, title_unfolded_char, unit, X_axis_true_char,EventBin_noUnits_char,
                                          doBinwidth, MakeXaxisLOG,  false);


std::cout<<"CrossSection_map[Data_signal_unfolded]" << std::endl;

std::string title_EffCorr_Pot = MuonTitle + " [BGsub][Unfolded][Eff Corr]";
char title_EffCorr_Pot_char[title_EffCorr_Pot.length()+1];
strcpy(title_EffCorr_Pot_char,title_EffCorr_Pot.c_str());

DrawCVAndError_FromHistPointer(CrossSection_map[Data_signal_unfolded_effcorrected], title_EffCorr_Pot_char ,X_axis, EventBin, pdf,  doBinwidth, MakeXaxisLOG);
std::cout<<"CrossSection_map[Data_signal_unfolded_effcorrected]" << std::endl;


Draw_DataWITHMC_SingleHistinput_withRatioCrossSection(true_clone, CrossSection_map[Data_signal_unfolded_effcorrected],
                                           Playlist_name, pdf, title_EffCorr_Pot_char, unit, X_axis_true_char, EventBin_noUnits_char,
                                          doBinwidth, MakeXaxisLOG,  false);



std::string title_eff = MuonTitle + " Efficiency";
char title_eff_char[title_eff.length()+1];
strcpy(title_eff_char,title_eff.c_str());
DrawCVAndError_FromHistPointer(CrossSection_map[Eff], title_eff_char ,X_axis, Efficiency_name, pdf,  false, MakeXaxisLOG);
std::cout<<"CrossSection_map[Eff]" << std::endl;

std::string Eventselection_title = MuonTitle + " Event Selection";
char Eventselection_title_char[Eventselection_title.length()+1];
strcpy(Eventselection_title_char,Eventselection_title.c_str());



std::string title_Cross_Section = MuonTitle + " Cross-Section:  #nu_{#mu} + CH #rightarrow #mu^{-} + X";
char title_Cross_Section_char[title_Cross_Section.length()+1];
strcpy(title_Cross_Section_char,title_Cross_Section.c_str());

std::string crossSection_y_axis = "#frac{d#sigma}{d" + GetMuonVar_crosssection(MuonVar) + "}#[]{10^{-38} #frac{cm^{2}}{"+ cross_section_units + " N} }";


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

//Draw_DataWITHMC_SingleHistinput_withRatio(CrossSection_map[True_crosssection], CrossSection_map[Data_crosssection],
//                                            Playlist_name, pdf, title_Cross_Section_char, "",
//                                            X_axis_char, crossSection_y_axis_char, dontBinwidthNorm, MakeXaxisLOG,
//                                            false, false);

Draw_DataWITHMC_SingleHistinput_withRatioCrossSection(CrossSection_map[True_crosssection], CrossSection_map[Data_crosssection],
                                                    Playlist_name, pdf, title_Cross_Section_char, "", X_axis_true_char, crossSection_y_axis_char,
                                                    dontBinwidthNorm, MakeXaxisLOG,  false);




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
      pdf, "CH Cross-Section Interaction Breakdown",
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

    Draw_DataWITHMC_SingleHistinput_withRatioCrossSection(CrossSection_map[True_crosssection], CrossSection_map[Data_crosssection],
                                                          Playlist_name, pdf,  title_Ratio_Cross_Section_char, "", X_axis_true_char, crossSection_Ratio_y_axis_char,
                                                          dontBinwidthNorm, MakeXaxisLOG,  false);





if(makepieInteraction==true){

  TObjArray stack_input;

  stack_input.Add (CrossSection_map[True_crosssection_interaction_Elastic]) ;
  stack_input.Add (CrossSection_map[True_crosssection_interaction_HeavierRes]);
  stack_input.Add (CrossSection_map[True_crosssection_interaction_DeltaRes]);
  stack_input.Add (CrossSection_map[True_crosssection_interaction_2p2h]);
  stack_input.Add (CrossSection_map[True_crosssection_interaction_DISSIS]);
  stack_input.Add (CrossSection_map[True_crosssection_interaction_DISHard]);
  stack_input.Add (CrossSection_map[True_crosssection_interaction_DISSoft]);
  stack_input.Add (CrossSection_map[True_crosssection_interaction_other]);
  stack_input.Add (CrossSection_map[True_crosssection_interaction_none]);
  const TObjArray  *mcHists_Breakdown_input =  &stack_input ;
   TObjArray  *mcHists_Breakdown_input1 =  &stack_input ;


std::vector<Interaction_Map> Interaction_Map_vector =  Interaction_vector( mcHists_Breakdown_input1, false, 1.0);
DrawPieFigures_Interaction(Interaction_Map_vector,  pdf_char1, can, plot, false, false, "none", title_Cross_Section_char );
}





return;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////////////////////////////
void MakeCrossSectionPlots_Interaction_Ratio(
  CrossSection_MnvH1D_Map CrossSection_map,
  CrossSection_MnvH1D_Map CrossSection_map_helium,
  std::string cross_section_units, std::string pdf,
  bool MakeXaxisLOG,bool doBinwidth ,
  MuonVar MuonVar, char *Playlist_name, double POT_Data,
  double POT_MC, Genie_Models Modelinputs,
   TCanvas *can, MnvPlotter *plot, bool makepieInteraction,
   MnvH1D* Daisy_combined_Data, MnvH1D* Daisy_combined_CrosSection_Data )
{


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

std::string X_axis_true = "TRUE " + GetMuonVarAXISName(MuonVar);
char X_axis_true_char[X_axis_true.length()+1];
strcpy(X_axis_true_char,X_axis_true.c_str());

char pdf_char1[pdf.length()+1];
strcpy(pdf_char1, pdf.c_str());


bool dontBinwidthNorm = false;

auto true_clone = CrossSection_map[dom_Eff]->Clone("true_clone");

char title_Signal_TRUTH_char[title_Signal_TRUTH.length()+1];
strcpy(title_Signal_TRUTH_char,title_Signal_TRUTH.c_str());
DrawCVAndError_FromHistPointer(CrossSection_map[dom_Eff],
  title_Signal_TRUTH_char ,X_axis, EventBin, pdf,  doBinwidth, MakeXaxisLOG);
std::cout<<"Made CrossSection_map[dom_Eff]" << std::endl;

std::string title_Signal_nomEff = MuonTitle + " Selection Nom Eff";
char title_Signal_nomEff_char[title_Signal_nomEff.length()+1];
strcpy(title_Signal_nomEff_char,title_Signal_nomEff.c_str());
DrawCVAndError_FromHistPointer(CrossSection_map[nom_Eff],
   title_Signal_nomEff_char ,X_axis, EventBin, pdf,  doBinwidth, MakeXaxisLOG);
std::cout<<"Made CrossSection_map[nom_Eff]" << std::endl;


std::string title_Signal = MuonTitle + " Event Selection";
char title_Signal_char[title_Signal.length()+1];
strcpy(title_Signal_char,title_Signal.c_str());
DrawCVAndError_FromHistPointer(CrossSection_map[Data_signal],
  title_Signal_char ,X_axis, EventBin, pdf,  doBinwidth, MakeXaxisLOG);
std::cout<<"Made CrossSection_map[Data_signal]" << std::endl;


Draw_DataWITHMC_SingleHistinput_withRatioCrossSection(
  CrossSection_map[RECO_signal], CrossSection_map[Data_signal],
  Playlist_name, pdf, title_Signal_char, unit, X_axis_char, EventBin_noUnits_char,
  doBinwidth, MakeXaxisLOG,  false);

std::string title_BG = MuonTitle + "BG Subtracted Data";
char title_BG_char[title_BG.length()+1];
strcpy(title_BG_char,title_BG.c_str());



Draw_DataWITHMC_SingleHistinput_withRatioCrossSection(
  CrossSection_map[RECO_signal], CrossSection_map[Data_signal_BG_subtracted],
  Playlist_name, pdf, title_BG_char, unit, X_axis_char, EventBin_noUnits_char,
  doBinwidth, MakeXaxisLOG,  false);






Draw_DataWITHMC_SingleHistinput_withRatioCrossSection(
  true_clone, CrossSection_map[Data_signal_BG_subtracted],
  Playlist_name, pdf, title_BG_char, unit, X_axis_true_char, EventBin_noUnits_char,
  doBinwidth, MakeXaxisLOG,  false);



std::string title_unfolded = MuonTitle + " [Unfolded]";
char title_unfolded_char[title_unfolded.length()+1];
strcpy(title_unfolded_char,title_unfolded.c_str());
DrawCVAndError_FromHistPointer(
  CrossSection_map[Data_signal_unfolded],
  title_unfolded_char ,X_axis, EventBin, pdf,
    doBinwidth, MakeXaxisLOG);

Draw_DataWITHMC_SingleHistinput_withRatioCrossSection(
  true_clone, CrossSection_map[Data_signal_unfolded],
  Playlist_name, pdf, title_unfolded_char, unit,
   X_axis_true_char,EventBin_noUnits_char,
  doBinwidth, MakeXaxisLOG,  false);


std::cout<<"CrossSection_map[Data_signal_unfolded]" << std::endl;

std::string title_EffCorr_Pot = MuonTitle + " [BGsub][Unfolded][Eff Corr]";
char title_EffCorr_Pot_char[title_EffCorr_Pot.length()+1];
strcpy(title_EffCorr_Pot_char,title_EffCorr_Pot.c_str());

DrawCVAndError_FromHistPointer(
  CrossSection_map[Data_signal_unfolded_effcorrected],
  title_EffCorr_Pot_char ,X_axis, EventBin, pdf,
  doBinwidth, MakeXaxisLOG);
std::cout<<"CrossSection_map[Data_signal_unfolded_effcorrected]" << std::endl;


Draw_DataWITHMC_SingleHistinput_withRatioCrossSection(
  true_clone, CrossSection_map[Data_signal_unfolded_effcorrected],
  Playlist_name, pdf, title_EffCorr_Pot_char,
  unit, X_axis_true_char, EventBin_noUnits_char,
  doBinwidth, MakeXaxisLOG,  false);



std::string title_eff = MuonTitle + " Efficiency";
char title_eff_char[title_eff.length()+1];
strcpy(title_eff_char,title_eff.c_str());
DrawCVAndError_FromHistPointer(CrossSection_map[Eff], title_eff_char ,X_axis, Efficiency_name, pdf,  false, MakeXaxisLOG);
std::cout<<"CrossSection_map[Eff]" << std::endl;

std::string Eventselection_title = MuonTitle + " Event Selection";
char Eventselection_title_char[Eventselection_title.length()+1];
strcpy(Eventselection_title_char,Eventselection_title.c_str());



std::string title_Cross_Section = MuonTitle + " Cross-Section:  #nu_{#mu} + CH #rightarrow #mu^{-} + X";
char title_Cross_Section_char[title_Cross_Section.length()+1];
strcpy(title_Cross_Section_char,title_Cross_Section.c_str());

std::string crossSection_y_axis = "#frac{d#sigma}{d" + GetMuonVar_crosssection(MuonVar) + "}#[]{10^{-38} #frac{cm^{2}}{"+ cross_section_units + " N} }";


char crossSection_y_axis_char[crossSection_y_axis.length()+1];
strcpy(crossSection_y_axis_char,crossSection_y_axis.c_str());
std::cout<<"Scaling Hists" << std::endl;

 auto names = CrossSection_map[True_crosssection]->GetErrorBandNames();
for(auto name : names){

std::cout<< " Name os TRUE crossection band 1 "<< name << std::endl;

}
//fauto ccma_band = CrossSection_map[True_crosssection]->GetLatErrorBand( "GENIE_MaCCQE" );

 //PlotVertBand("Flux", "flux",CrossSection_map[True_crosssection]);

MnvH1D* Daisy_combined = (MnvH1D*)Daisy_combined_Data->Clone("Daisy_combined");
MnvH1D* Daisy_TrackerCrosSection_Data = (MnvH1D*)Daisy_combined_CrosSection_Data->Clone("Daisy_CrosSection_Data");





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
Daisy_TrackerCrosSection_Data->Scale(1/Scale);
std::string inputname1 = pdfname + "Old_ZexpTRUE";
std::string inputname2 = pdfname + "Old_ZexpData";
//PlotVertBand("GENIE_MaZExpCCQE", inputname1 ,"MaCCQE Systematic universes MC TRUE", X_axis, crossSection_y_axis, CrossSection_map[True_crosssection]);
//PlotVertBand("GENIE_MaZExpCCQE", inputname2 ,"MaCCQE Systematic universes DATA", X_axis, crossSection_y_axis, CrossSection_map[Data_crosssection]);


//

TH1D*  hMC_Model_nominal =  (TH1D*)CrossSection_map[True_crosssection]->Clone(uniq());

std::cout<<"Writing First XSec method" << std::endl;


Draw_DataWITHMC_SingleHistinput_withRatioCrossSection(CrossSection_map[True_crosssection], CrossSection_map[Data_crosssection],
                                                    Playlist_name, pdf, title_Cross_Section_char, "", X_axis_true_char, crossSection_y_axis_char,
                                                    dontBinwidthNorm, MakeXaxisLOG,  false);

Draw_DataWITHMC_SingleHistinput_withRatioCrossSection(CrossSection_map[True_crosssection], Daisy_TrackerCrosSection_Data,
  "Daisy Corrrected Tracker ", pdf, title_Cross_Section_char, "", X_axis_true_char, crossSection_y_axis_char,
  dontBinwidthNorm, MakeXaxisLOG,  false);



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


//std::cout<<"TITLE outside class " << Modelinputs.ModelHistMap_1D[0]->GetTitle()<<std::endl;
std::cout<<"apout Draw_DataWITHMC_SingleHistinput_withRatioCrossSection " << std::endl;
//Draw_DataWITHMC_SingleHistinput_withRatioCrossSection(CrossSection_map[True_crosssection], CrossSection_map[Data_crosssection], TobjMC_Model,
//Playlist_name, pdf, title_Cross_Section_char, "", X_axis_char, crossSection_y_axis_char, MakeXaxisLOG );




std::cout<<"CrossSection_map[True_crosssection]" << std::endl;

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


        Draw_DataWITHMC_SingleHistinput_withRatioCrossSection_Interactions_DISbreakdown(
          CrossSection_map[True_crosssection], Daisy_TrackerCrosSection_Data,
          CrossSection_map[True_crosssection_interaction_Elastic],
          CrossSection_map[True_crosssection_interaction_2p2h],
          CrossSection_map[True_crosssection_interaction_DeltaRes],
          CrossSection_map[True_crosssection_interaction_HeavierRes],
          CrossSection_map[True_crosssection_interaction_DISSIS],
          CrossSection_map[True_crosssection_interaction_DISSoft],
          CrossSection_map[True_crosssection_interaction_DISHard],
          CrossSection_map[True_crosssection_interaction_none],
          CrossSection_map[True_crosssection_interaction_other],
          "Daisy Corrected", pdf, title_Cross_Section_char, "",
          X_axis_char, crossSection_y_axis_char, dontBinwidthNorm, MakeXaxisLOG,  false, POT_MC, POT_Data);


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
      pdf, "CH Cross-Section Interaction Breakdown",
         X_axis_char, "Fraction of Events");

         CrossSection_map_helium[True_crosssection]->Scale(1/Scale);
         CrossSection_map_helium[Data_crosssection]->Scale(1/Scale);
         //
         //CrossSection_map[True_crosssection]->Scale(POT_Ratio);
         //CrossSection_map[Data_crosssection]->Scale(POT_Ratio);
         //Daisy_TrackerCrosSection_Data->Scale(POT_Ratio);
         MnvH1D* helium_crosssection = (MnvH1D*)CrossSection_map_helium[Data_crosssection]->Clone("helium_crosssection");

         std::cout<< " Trying to Divide" << MuonTitle << std::endl;
         std::cout<< "CrossSection_map[True_crosssection] Bins " <<      CrossSection_map[True_crosssection]->GetNbinsX()<< std::endl;
         std::cout<< "CrossSection_map_helium[True_crosssection] Bins " <<      CrossSection_map_helium[True_crosssection]->GetNbinsX()<< std::endl;

         std::cout<< "CrossSection_map[Data_crosssection] Bins " <<      CrossSection_map[Data_crosssection]->GetNbinsX()<< std::endl;
         std::cout<< "CrossSection_map_helium[Data_crosssection] Bins " <<      CrossSection_map_helium[Data_crosssection]->GetNbinsX()<< std::endl;


         //CrossSection_map[True_crosssection]->Divide(CrossSection_map[True_crosssection],CrossSection_map_helium[True_crosssection] ) ;

         //CrossSection_map[Data_crosssection]->Divide(CrossSection_map[Data_crosssection],CrossSection_map_helium[Data_crosssection] ) ;

         CrossSection_map_helium[True_crosssection]->Divide(CrossSection_map_helium[True_crosssection],CrossSection_map[True_crosssection] ) ;
         CrossSection_map_helium[Data_crosssection]->Divide(CrossSection_map_helium[Data_crosssection],CrossSection_map[Data_crosssection] ) ;

         helium_crosssection->Divide(helium_crosssection, Daisy_TrackerCrosSection_Data) ;



          crossSection_y_axis = "#frac{d#sigma^{He}}{d" + GetMuonVar_crosssection(MuonVar) + "} / " "#frac{d#sigma^{CH}}{d" + GetMuonVar_crosssection(MuonVar) + "}";


          char crossSection_Ratio_y_axis_char[crossSection_y_axis.length()+1];
          strcpy(crossSection_Ratio_y_axis_char,crossSection_y_axis.c_str());
          title_Cross_Section = MuonTitle + " Cross Section Ratio";

          char title_Ratio_Cross_Section_char[title_Cross_Section.length()+1];
          strcpy(title_Ratio_Cross_Section_char,title_Cross_Section.c_str());



    Draw_DataWITHMC_SingleHistinput_withRatio(CrossSection_map_helium[True_crosssection], CrossSection_map_helium[Data_crosssection],
                                                     Playlist_name, pdf, title_Ratio_Cross_Section_char, "",
                                                     X_axis_char, crossSection_Ratio_y_axis_char, false, MakeXaxisLOG,
                                                     false, false);

    Draw_DataWITHMC_SingleHistinput_withRatioCrossSection(CrossSection_map_helium[True_crosssection], CrossSection_map_helium[Data_crosssection],
                                                          Playlist_name, pdf,  title_Ratio_Cross_Section_char, "", X_axis_true_char, crossSection_Ratio_y_axis_char,
                                                          dontBinwidthNorm, MakeXaxisLOG,  true, 1.8);

      Draw_DataWITHMC_SingleHistinput_withRatioCrossSection(CrossSection_map_helium[True_crosssection], helium_crosssection,
       "Daisy Corrected", pdf,  title_Ratio_Cross_Section_char, "", X_axis_true_char, crossSection_Ratio_y_axis_char,
     dontBinwidthNorm, MakeXaxisLOG,  true, 1.8 );




if(makepieInteraction==true){

  TObjArray stack_input;

  stack_input.Add (CrossSection_map[True_crosssection_interaction_Elastic]) ;
  stack_input.Add (CrossSection_map[True_crosssection_interaction_HeavierRes]);
  stack_input.Add (CrossSection_map[True_crosssection_interaction_DeltaRes]);
  stack_input.Add (CrossSection_map[True_crosssection_interaction_2p2h]);
  stack_input.Add (CrossSection_map[True_crosssection_interaction_DISSIS]);
  stack_input.Add (CrossSection_map[True_crosssection_interaction_DISHard]);
  stack_input.Add (CrossSection_map[True_crosssection_interaction_DISSoft]);
  stack_input.Add (CrossSection_map[True_crosssection_interaction_other]);
  stack_input.Add (CrossSection_map[True_crosssection_interaction_none]);
  const TObjArray  *mcHists_Breakdown_input =  &stack_input ;
   TObjArray  *mcHists_Breakdown_input1 =  &stack_input ;


std::vector<Interaction_Map> Interaction_Map_vector =  Interaction_vector( mcHists_Breakdown_input1, false, 1.0);
DrawPieFigures_Interaction(Interaction_Map_vector,  pdf_char1, can, plot, false, false, "none", title_Cross_Section_char );
}
return;
}
////////////////////////////////////////////////////////////////////////////////
///
/////////////////////////////////////////////////////////////////////////////////
void Make_DaisyPlots_CrossSection_Plots(std::map<int, CrossSection_name_Map> inputDaisyNameMap,
  TFile& inputTFile, MuonVar MuonVar, std::string pdf, double POT_Data,
  double POT_MC,TCanvas *can, MnvPlotter *mnv_plot)
  {
std::cout<<" Ploting Daisy Plots "<< std::endl;

std::string X_axis = GetMuonVarAXISName(MuonVar);
char X_axis_char[X_axis.length()+1];
strcpy(X_axis_char,X_axis.c_str());
std::string MuonTitle = GetMuonVarTitleName(MuonVar);
std::string pdfname= GetMuonVarpdfName(MuonVar);
std::string unit = GetMuonUnitType(MuonVar);
std::string title_Effiency = MuonTitle + " Efficiency Daisy Patel: ";
std::string title_main = MuonTitle + " Daisy Patel: ";
std::string EventBin = "Event Rate / [" + unit +"]";
std::string Efficiency_name  = "Efficiency" ;
std::string EventBin_noUnits = "Event Rate";
auto hist_name = GetMuonVarHistName(MuonVar);
char EventBin_char[EventBin.length()+1];
strcpy(EventBin_char,EventBin.c_str());
char EventBin_noUnits_char[EventBin_noUnits.length()+1];
strcpy(EventBin_noUnits_char,EventBin_noUnits.c_str());

std::string X_axis_true = "TRUE " + GetMuonVarAXISName(MuonVar);
char X_axis_true_char[X_axis_true.length()+1];
strcpy(X_axis_true_char,X_axis_true.c_str());
std::string pdf2 = pdf + ".pdf";
char pdf_char[pdf2.length()+1];
strcpy(pdf_char, pdf2.c_str());


bool dontBinwidthNorm = false;
bool doBinwidth = true;
bool MakeXaxisLOG = false;
bool printErrors = true;
double SetMaxEff;
double SetMaxMC_reco;
double SetMaxMC_True;

for(auto Map = inputDaisyNameMap.begin();Map != inputDaisyNameMap.end(); Map++){

  std::string petal_Numb =  std::to_string(Map->first);

  CrossSection_MnvH1D_Map Daisy_Petal_Hist = Generate_CrossSection_Hist_Map(inputTFile, Map->second);
  std::string MigName = hist_name + "_Daisy" + petal_Numb + "_Mig";
  auto h_Mig = Get2DHist(inputTFile, MigName );
  std::string title_main_petal = title_main + " " + petal_Numb;


  if(Map == inputDaisyNameMap.begin()){
    double MaxEff_temp = 0;
    double SetMaxMC_reco_temp = 0;
    double SetMaxMC_true_temp = 0;

    for(auto Mapinside = inputDaisyNameMap.begin();Mapinside != inputDaisyNameMap.end(); Mapinside++){


      CrossSection_MnvH1D_Map Daisy_Petal_Hist_inside = Generate_CrossSection_Hist_Map(inputTFile, Mapinside->second);

      double Maxeff_input = Daisy_Petal_Hist_inside[Eff]->GetMaximum();

      auto clone1 = (MnvH1D*)Daisy_Petal_Hist_inside[MC_reco]->Clone("");
      clone1->Scale(1.0,"width");
      double maxReco_input = clone1->GetMaximum();

      auto clone2 = (MnvH1D*)Daisy_Petal_Hist_inside[dom_Eff]->Clone("");
      clone2->Scale(1.0,"width");
      double MaxTrue_input = clone2->GetMaximum();


      if(Maxeff_input > MaxEff_temp  ){
        MaxEff_temp = Maxeff_input;
        SetMaxEff = 1.1*MaxEff_temp;
      }

      if(maxReco_input > SetMaxMC_reco_temp  ){
        SetMaxMC_reco_temp = maxReco_input;
        SetMaxMC_reco = 1.2*maxReco_input;
      }

      if(MaxTrue_input > SetMaxMC_true_temp  ){
        SetMaxMC_true_temp = MaxTrue_input;
        SetMaxMC_True = 1.2*MaxTrue_input;
      }
    }
  }

  //Daisy_Petal_Hist[Data_signal]
  //Daisy_Petal_Hist[MC_reco_BG]
  //Daisy_Petal_Hist[MC_reco]
  //Daisy_Petal_Hist[Data_signal_BGsub_potNorm]
  //Daisy_Petal_Hist[Data_signal_unfolded]
  //Daisy_Petal_Hist[Eff]
  //Daisy_Petal_Hist[dom_Eff]
  //Daisy_Petal_Hist[Data_signal_unfolded_effcorrected]

  std::string title_Effiency_petal = title_Effiency  +  petal_Numb;
  char title_Effiency_char[title_Effiency_petal.length()+1];
  strcpy(title_Effiency_char,title_Effiency_petal.c_str());
  DrawCVAndError_FromHistPointer(Daisy_Petal_Hist[Eff], title_Effiency_char ,X_axis_true, "Efficiency" , pdf,  dontBinwidthNorm, MakeXaxisLOG,SetMaxEff );

  //void DrawCVAndError_FromHistPointer(MnvH1D *hist_input, char *histotitle ,std::string xaxislabel, std::string yaxislabel,
  //std::string label, bool doBinwidth, bool MakeXaxisLOG, bool printErrors, double Ymax)

  char title_main_petal_char[title_main_petal.length()+1];
  strcpy(title_main_petal_char,title_main_petal.c_str());
  DrawMagration_heatMap_Label(h_Mig, X_axis_char ,X_axis_true_char,  title_main_petal_char, pdf_char, can, mnv_plot, 3, 1.0);

  std::string RECO_title = "Daisy : " +  petal_Numb;
  char RECO_title_char[RECO_title.length()+1];
  strcpy(RECO_title_char,RECO_title.c_str());

  Draw_DataWITHMC_SingleHistinput_withRatioCrossSection(Daisy_Petal_Hist[MC_reco], Daisy_Petal_Hist[Data_signal],
                                             "Event Selection", pdf, RECO_title_char, unit, X_axis_char, EventBin_noUnits_char,
                                            doBinwidth, MakeXaxisLOG,  false, SetMaxMC_reco);

  Draw_DataWITHMC_SingleHistinput_withRatioCrossSection(Daisy_Petal_Hist[MC_reco], Daisy_Petal_Hist[Data_signal_BGsub_potNorm],
    "Event Selection BG Subtracted", pdf, RECO_title_char, unit, X_axis_char, EventBin_noUnits_char,
    doBinwidth, MakeXaxisLOG,  false, SetMaxMC_reco);

  Draw_DataWITHMC_SingleHistinput_withRatioCrossSection(Daisy_Petal_Hist[dom_Eff], Daisy_Petal_Hist[Data_signal_BGsub_potNorm],
    "Event Selection BG Subtracted", pdf, RECO_title_char, unit, X_axis_true_char, EventBin_noUnits_char,
    doBinwidth, MakeXaxisLOG,  false,SetMaxMC_True);

  Draw_DataWITHMC_SingleHistinput_withRatioCrossSection(Daisy_Petal_Hist[dom_Eff], Daisy_Petal_Hist[Data_signal_unfolded],
    "Event Selection BG - Subtracted - Unfolded", pdf, RECO_title_char, unit, X_axis_true_char, EventBin_noUnits_char,
    doBinwidth, MakeXaxisLOG,  false,SetMaxMC_True);

  Draw_DataWITHMC_SingleHistinput_withRatioCrossSection(Daisy_Petal_Hist[dom_Eff], Daisy_Petal_Hist[Data_signal_unfolded_effcorrected],
    "Event Selection - BG Subtracted - Unfolded - EffCorrect", pdf, RECO_title_char, unit, X_axis_true_char, EventBin_noUnits_char,
    doBinwidth, MakeXaxisLOG,  false,SetMaxMC_True);


}






}
////////////////////////////////////////////////////////////////////////////////
///
/////////////////////////////////////////////////////////////////////////////////

void Make_DaisyPlots_2DCrossSection_Plots(
  std::map<int, CrossSection_name_Map> inputDaisyNameMap,
  TFile& inputTFile, Muon2DVar MuonVar,
  std::string pdf, double POT_Data,
  double POT_MC,TCanvas *can,
  MnvPlotter *mnv_plot)
  {
std::cout<<" Ploting Daisy Plots "<< std::endl;
std::string X_axis = GetMuon2DVar_XaxisTitle(MuonVar);
char X_axis_char[X_axis.length()+1];
strcpy(X_axis_char,X_axis.c_str());
std::string Y_axis = GetMuon2DVar_YaxisTitle(MuonVar);
char Y_axis_char[Y_axis.length()+1];
strcpy(Y_axis_char,Y_axis.c_str());
std::string Y_axisUnits = GetMuon2DVar_yaxisUnits(MuonVar);
std::string X_axisUnits = GetMuon2DVar_xaxisUnits(MuonVar);
std::vector<double> Pzbin_vector{1.5, 3.0, 4.0, 5.0, 6.0, 8.0, 10.0, 20.0};
std::vector<double> PTbin_vector{0.0, 0.25, 0.4, 0.55, 0.7, 0.85, 2.5};

std::string MuonTitle = GetMuon2DVar_Title(MuonVar);
std::string title_Effiency = MuonTitle + " Efficiency Daisy Patel: ";
std::string title_main = MuonTitle + " Daisy Patel: ";
std::string EventBin = "Event Rate / [" + Y_axisUnits +"]";
std::string Efficiency_name  = "Efficiency" ;
std::string EventBin_noUnits = "Event Rate";

char EventBin_char[EventBin.length()+1];
strcpy(EventBin_char,EventBin.c_str());
char EventBin_noUnits_char[EventBin_noUnits.length()+1];
strcpy(EventBin_noUnits_char,EventBin_noUnits.c_str());

std::string X_axis_true = "TRUE " + X_axis;
char X_axis_true_char[X_axis_true.length()+1];
strcpy(X_axis_true_char,X_axis_true.c_str());

std::string Y_axis_true = "TRUE " + Y_axis;
char Y_axis_true_char[Y_axis_true.length()+1];
strcpy(Y_axis_true_char,Y_axis_true.c_str());


std::string pdf2 = pdf + ".pdf";
char pdf_char[pdf2.length()+1];
strcpy(pdf_char, pdf2.c_str());




bool dontBinwidthNorm = false;
bool doBinwidth = true;
bool MakeXaxisLOG = false;
bool printErrors = true;
double SetMaxEff;
double SetMaxMC_reco;
double SetMaxMC_True;
bool DoBinN= true;
double Markersize = .3;
char Title[1024];


for(auto Map = inputDaisyNameMap.begin();Map != inputDaisyNameMap.end(); Map++){

  std::string petal_Numb =  std::to_string(Map->first);

  auto Map_PT_PZ_tracker_hists = Generate_2DCrossSection_Hist_Map(inputTFile, Map->second);
  auto true_clone = Map_PT_PZ_tracker_hists[dom_Eff]->Clone("true_clone");



/*
  if(Map == inputDaisyNameMap.begin()){
    double MaxEff_temp = 0;
    double SetMaxMC_reco_temp = 0;
    double SetMaxMC_true_temp = 0;

    //for(auto Mapinside = inputDaisyNameMap.begin();Mapinside != inputDaisyNameMap.end(); Mapinside++){


      double Maxeff_input = Daisy_Petal_Hist_inside[Eff]->GetMaximum();


      auto clone1 = (MnvH1D*)Daisy_Petal_Hist_inside[MC_reco]->Clone("");
      clone1->Scale(1.0,"width");
      double maxReco_input = clone1->GetMaximum();

      auto clone2 = (MnvH1D*)Daisy_Petal_Hist_inside[dom_Eff]->Clone("");
      clone2->Scale(1.0,"width");
      double MaxTrue_input = clone2->GetMaximum();


      if(Maxeff_input > MaxEff_temp  ){
        MaxEff_temp = Maxeff_input;
        SetMaxEff = 1.1*MaxEff_temp;
      }

      if(maxReco_input > SetMaxMC_reco_temp  ){
        SetMaxMC_reco_temp = maxReco_input;
        SetMaxMC_reco = 1.2*maxReco_input;
      }

      if(MaxTrue_input > SetMaxMC_true_temp  ){
        SetMaxMC_true_temp = MaxTrue_input;
        SetMaxMC_True = 1.2*MaxTrue_input;
      }
    }
  }*/

  //Daisy_Petal_Hist[Data_signal]
  //Daisy_Petal_Hist[MC_reco_BG]
  //Daisy_Petal_Hist[MC_reco]
  //Daisy_Petal_Hist[Data_signal_BGsub_potNorm]
  //Daisy_Petal_Hist[Data_signal_unfolded]
  //Daisy_Petal_Hist[Eff]
  //Daisy_Petal_Hist[dom_Eff]
  //Daisy_Petal_Hist[Data_signal_unfolded_effcorrected]
  //Daisy_Petal_Hist[mvnreponse_RECO]
  //Daisy_Petal_Hist[mvnreponse_TRUE]
std::string title_main_petal = MuonTitle + "Daisy: " + petal_Numb;
  char title_main_petal_char[title_main_petal.length()+1];
  strcpy(title_main_petal_char,title_main_petal.c_str());

//  DrawMagration_heatMap_Label(Map_PT_PZ_tracker_hists[mvnreponse_Mig], X_axis_char ,,
  //  title_main_petal_char, pdf_char, can, mnv_plot, 3, 1.0);
    //sprintf(Title,"Migration Daisy : %i",  Map->first);

  sprintf(Title,"2D Migration Daisy : %i",  Map->first);
  DrawMagration_heatMap_noText(
    Map_PT_PZ_tracker_hists[mvnreponse_Mig] ,
    X_axis_true_char,
    Y_axis_true_char, Title,
    pdf_char, can, mnv_plot, false,"");


sprintf(Title,"Migration X Projection Daisy : %i",  Map->first);
PlotDataMC_Migration_ProjX(Map_PT_PZ_tracker_hists[mvnreponse_Mig],
    Map_PT_PZ_tracker_hists[mvnreponse_RECO],
    Map_PT_PZ_tracker_hists[mvnreponse_TRUE],
    Pzbin_vector,
    pdf_char, Title,  "Reco P_{Z} [GeV/c]",
    "P_{T}",   "True P_{Z} [GeV/c] ",
    2500, mnv_plot, can,4,.01,Markersize,DoBinN);

  std::cout<<"Drawing:PlotDataMC_Migration_Proj=Y "<< std::endl;
    sprintf(Title,"Migration Y Projection Daisy : %i",  Map->first);
  PlotDataMC_Migration_ProjY( Map_PT_PZ_tracker_hists[mvnreponse_Mig],
    Map_PT_PZ_tracker_hists[mvnreponse_RECO],
    Map_PT_PZ_tracker_hists[mvnreponse_TRUE],PTbin_vector,
    pdf_char, Title,  "Reco P_{T} [GeV/c]",
    "P_{Z}",   "True P_{T} [GeV/c] ",
    2500, mnv_plot, can,4,.01,Markersize,DoBinN) ;


    sprintf(Title,"Migration X Projection (Row Norm) Daisy : %i",  Map->first);
  PlotDataMC_Migration_ProjX( Map_PT_PZ_tracker_hists[mvnreponse_Mig],
    Map_PT_PZ_tracker_hists[mvnreponse_RECO],
    Map_PT_PZ_tracker_hists[mvnreponse_TRUE],Pzbin_vector,
    pdf_char,Title,  "Reco P_{Z} [GeV/c]",
    "P_{T}",   "True P_{Z} [GeV/c] ",
    1.0, mnv_plot, can,3,.01,Markersize,DoBinN) ;

    sprintf(Title,"Migration Y Projection (Row Norm) Daisy : %i",  Map->first);
  PlotDataMC_Migration_ProjY( Map_PT_PZ_tracker_hists[mvnreponse_Mig],
    Map_PT_PZ_tracker_hists[mvnreponse_RECO],
    Map_PT_PZ_tracker_hists[mvnreponse_TRUE],PTbin_vector,
    pdf_char, Title,  "Reco P_{T} [GeV/c]",
    "P_{Z}",   "True P_{T} [GeV/c] ",
    1.0, mnv_plot, can, 3,.01,Markersize,DoBinN) ;



    //  MnvH2D *ProjectMig = GetMigration_Projection_Y_forBinN(CrossSection_map[mvnreponse_Mig], CrossSection_map[mvnreponse_RECO],CrossSection_map[mvnreponse_TRUE], Pzbin_vector , 1 );

    //MnvH2D *h_return =    new MnvH2D("h_return", "h_return",Pzbin_vector.size()-1, Pzbin_vector.data() ,Pzbin_vector.size()-1, Pzbin_vector.data()  );


  //GetMigration_Projection_Y_forBinN_input(h_return, CrossSection_map[mvnreponse_Mig], CrossSection_map[mvnreponse_RECO],CrossSection_map[mvnreponse_TRUE], 1);


//  for(int  XTruthbinN = 1; XTruthbinN <=  Map_PT_PZ_tracker_hists[mvnreponse_TRUE]->GetNbinsX();  XTruthbinN++  ){
//    for(int  XRecobinN = 1; XRecobinN <=  Map_PT_PZ_tracker_hists[mvnreponse_RECO]->GetNbinsX();  XRecobinN++  ){
//
//      int globalBin =  GetGlobalBinNFrom2DMig_BinN( Map_PT_PZ_tracker_hists[mvnreponse_Mig], Map_PT_PZ_tracker_hists[mvnreponse_RECO],  Map_PT_PZ_tracker_hists[mvnreponse_TRUE], XRecobinN, 1 , XTruthbinN, 1);
//      double content =  Map_PT_PZ_tracker_hists[mvnreponse_Mig]->GetBinContent(globalBin);
//
//      int Global_hreturn_binN  = XTruthbinN*(h_return->GetNbinsX()+2) + XRecobinN; // Assuming Truth is Y axis
//      std::cout<< "Global_hreturn_binN = " << Global_hreturn_binN << " content = " << content << std::endl;
//      h_return->AddBinContent(Global_hreturn_binN,content);
//    }
//  }


  //Draw2DHist(h_return, X_axis_char, X_axis_char, "NEvent" , title_main_petal_char , pdf_char, can,mnv_plot);

  //DrawMagration_heatMap_LabelBinNumber(h_return, "x bins", "y bins",  "bin1", pdf_char, can,mnv_plot);





  std::string title_Effiency_petal = title_Effiency  +  petal_Numb;
  char title_Effiency_char[title_Effiency_petal.length()+1];
  strcpy(title_Effiency_char,title_Effiency_petal.c_str());

  DrawMagration_heatMap_Label(Map_PT_PZ_tracker_hists[Eff],
     X_axis_true_char , Y_axis_true_char,
  title_Effiency_char, pdf_char, can, mnv_plot, 3, .3);


  std::vector<double> XMultipliers{1,1,1,1,1,1,1,1};
  bool do_bin_width_norm_eff = false;
  bool statPlusSysDATA = true;
   bool statPlusSysMC  = true;


  PlotMC_ErrorBand2D_ProjX(
    Map_PT_PZ_tracker_hists[Eff],
      pdf_char, title_main_petal_char,  X_axis_char,
    Y_axis_char,   "Efficiency", .8 , true,  false, XMultipliers,
    statPlusSysDATA , statPlusSysMC , do_bin_width_norm_eff, true , .03);

  PlotMC_ErrorBand2D_ProjY(
    Map_PT_PZ_tracker_hists[Eff],
     pdf_char,title_main_petal_char,  Y_axis_char,
      X_axis_char, "Efficiency", .8 , true,  false, XMultipliers,
      statPlusSysDATA , statPlusSysMC , do_bin_width_norm_eff, true , .03);


  std::string RECO_title = "Daisy : " +  petal_Numb;
  char RECO_title_char[RECO_title.length()+1];
  strcpy(RECO_title_char,RECO_title.c_str());

///////
// Normalize 10^3
///////
Map_PT_PZ_tracker_hists[Data_signal]->Scale(.001);
Map_PT_PZ_tracker_hists[MC_reco]->Scale(.001);
Map_PT_PZ_tracker_hists[Data_signal_BGsub_potNorm]->Scale(.001);
Map_PT_PZ_tracker_hists[dom_Eff]->Scale(.001);
Map_PT_PZ_tracker_hists[Data_signal_unfolded]->Scale(.001);
Map_PT_PZ_tracker_hists[Data_signal_unfolded_effcorrected]->Scale(.001);
bool SetMax = true;
  sprintf(Title,"RECO Event Selection Daisy : %i",  Map->first);
  PlotDataMC_ErrorBand2D_ProjY(Map_PT_PZ_tracker_hists[Data_signal],
     Map_PT_PZ_tracker_hists[MC_reco],
    pdf_char, RECO_title_char ,  Y_axis_char, X_axis_char,   "NEvents(10^{-3}) / [GeV/c]^{2}",
    45.5, SetMax,  true, XMultipliers,
    true , true , doBinwidth,  false, .03);

  PlotDataMC_ErrorBand2D_ProjX(
    Map_PT_PZ_tracker_hists[Data_signal],
     Map_PT_PZ_tracker_hists[MC_reco],
    pdf_char, RECO_title_char ,  X_axis_char, Y_axis_char,   "NEvents(10^{-3}) / [GeV/c]^{2}",
    7.5, SetMax,  true, XMultipliers,
    true , true , doBinwidth,  false, .03);

  sprintf(Title,"RECO Event Selection BG Subtracted Daisy : %i",  Map->first);
  PlotDataMC_ErrorBand2D_ProjY(
    Map_PT_PZ_tracker_hists[Data_signal_BGsub_potNorm],
     Map_PT_PZ_tracker_hists[MC_reco],
    pdf_char, Title ,  Y_axis_char, X_axis_char,   "NEvents(10^{-3}) / [GeV/c]^{2}",
    45.5, SetMax,  true, XMultipliers,
    true , true , doBinwidth,  false, .03);

  PlotDataMC_ErrorBand2D_ProjX(
    Map_PT_PZ_tracker_hists[Data_signal_BGsub_potNorm],
     Map_PT_PZ_tracker_hists[MC_reco],
    pdf_char, Title ,  X_axis_char, Y_axis_char,   "NEvents(10^{-3}) / [GeV/c]^{2}",
    7.5, SetMax,  true, XMultipliers,
    true , true , doBinwidth,  false, .03);

  sprintf(Title,"TRUE MC BG Subtracted Daisy : %i",  Map->first);
  PlotDataMC_ErrorBand2D_ProjY(
    Map_PT_PZ_tracker_hists[Data_signal_BGsub_potNorm],
     Map_PT_PZ_tracker_hists[dom_Eff],
    pdf_char, Title ,  Y_axis_char, X_axis_char,   "NEvents(10^{-3}) / [GeV/c]^{2}",
    95, SetMax,  true, XMultipliers,
    true , true , doBinwidth,  false, .03);

  PlotDataMC_ErrorBand2D_ProjX(
    Map_PT_PZ_tracker_hists[Data_signal_BGsub_potNorm],
     Map_PT_PZ_tracker_hists[dom_Eff],
    pdf_char, Title ,  X_axis_char, Y_axis_char,   "NEvents(10^{-3}) / [GeV/c]^{2}",
    15, SetMax,  true, XMultipliers,
    true , true , doBinwidth,  false, .03);

  sprintf(Title,"Data Unfolded Daisy : %i",  Map->first);
  PlotDataMC_ErrorBand2D_ProjY(
    Map_PT_PZ_tracker_hists[Data_signal_unfolded],
     Map_PT_PZ_tracker_hists[dom_Eff],
    pdf_char, Title ,  Y_axis_char, X_axis_char,   "NEvents(10^{-3}) / [GeV/c]^{2}",
    95, SetMax,  true, XMultipliers,
    true , true , doBinwidth,  false, .03);

  PlotDataMC_ErrorBand2D_ProjX(
    Map_PT_PZ_tracker_hists[Data_signal_unfolded],
     Map_PT_PZ_tracker_hists[dom_Eff],
    pdf_char, Title ,  X_axis_char, Y_axis_char,   "NEvents(10^{-3}) / [GeV/c]^{2}",
    15, SetMax,  true, XMultipliers,
    true , true , doBinwidth,  false, .03);

  sprintf(Title,"Efficiency Corrected Data : %i",  Map->first);
  PlotDataMC_ErrorBand2D_ProjY(
    Map_PT_PZ_tracker_hists[Data_signal_unfolded_effcorrected],
    Map_PT_PZ_tracker_hists[dom_Eff],
    pdf_char, Title ,  Y_axis_char, X_axis_char,   "NEvents(10^{-3}) / [GeV/c]^{2}",
    95, SetMax,  true, XMultipliers,
    true , true , doBinwidth,  false, .03);

  PlotDataMC_ErrorBand2D_ProjX(
    Map_PT_PZ_tracker_hists[Data_signal_unfolded_effcorrected],
     Map_PT_PZ_tracker_hists[dom_Eff],
    pdf_char, Title ,  X_axis_char, Y_axis_char,   "NEvents(10^{-3}) / [GeV/c]^{2}",
    15, SetMax,  true, XMultipliers,
    true , true , doBinwidth,  false, .03);


    ////////////////////////////////////////////////////////////////////////////////
    ///
    ////////////////////////////////////////////////////////////////////////////////
  }// ENd of Petal Loop
  ////////////////////////////////////////////////////////////////////////////////
  ///
  ////////////////////////////////////////////////////////////////////////////////

}
////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////
CrossSection_name_Map Generate_CrossSection_histsNames_withInteraction_DISbreakdown_helium(
  MuonVar MuonVar_type, std::string playlist, bool isFUll)
  {

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
////////////////////////////////////////////////////////////////////////////////
/// 2D
////////////////////////////////////////////////////////////////////////////////
CrossSection_name_Map Generate_2DCrossSection_histsNames_withInteraction_DISbreakdown_helium(
  std::string hist_name, Muon2DVar MuonVar_type,  std::string playlist,
   bool isFUll , bool PrintNames)
   {

  CrossSection_name_Map Name_Map;

  if(isFUll==true)
  {

    std::string hist1_name = hist_name + "_" + playlist + "_Data_Signal";
    Name_Map.insert(std::make_pair(Data_signal, hist1_name));



    std::string hist_RECO_name = hist_name + "_" + playlist + "_MC_RECO";
    Name_Map.insert(std::make_pair(MC_reco, hist_RECO_name));

    //std::string hist1_name_pot = hist_name + "_" + playlist + "_potnorm_Data_Signal";
    //Name_Map.insert(std::make_pair(Data_signal_potNorm, hist1_name_pot));

    std::string hist1_name_pot_full_empty = hist_name + "_Full_sub_Empty_potnorm_Data_Signal";
    Name_Map.insert(std::make_pair(Data_signal_BGsub_potNorm, hist1_name_pot_full_empty));

    std::string hist2_name_pot_full_empty = hist_name + "_Full_sub_Empty_potnorm_RECO";
    Name_Map.insert(std::make_pair(RECO_signal_BGsub_potNorm, hist2_name_pot_full_empty));

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

    std::string mvnreponse_Mig_name = hist_name + "_mvnreponse_Mig";
    Name_Map.insert(std::make_pair(mvnreponse_Mig, mvnreponse_Mig_name));

    std::string mvnreponse_RECO_name = hist_name + "_mvnreponse_RECO";
    Name_Map.insert(std::make_pair(mvnreponse_RECO, mvnreponse_RECO_name));

    std::string mvnreponse_true_name = hist_name + "_mvnreponse_TRUE";
    Name_Map.insert(std::make_pair(mvnreponse_TRUE, mvnreponse_true_name));

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

    if(PrintNames==true){

   std::cout<<"Printer Names of Got His"<<std::endl;
   std::cout<<"hist1_name = " << hist1_name<< std::endl;
   std::cout<<"hist_RECO_name = " << hist_RECO_name<< std::endl;
   //std::cout<<"hist1_name_pot = " << hist1_name_pot<< std::endl;
   std::cout<<"hist1_name_pot_full_empty = " << hist1_name_pot_full_empty<< std::endl;
   std::cout<<"hist2_name_pot_full_empty = " << hist2_name_pot_full_empty<< std::endl;
   std::cout<<"unfolded_name = " << unfolded_name<< std::endl;
   std::cout<<"eff_Corrected_name = " << eff_Corrected_name<< std::endl;
   std::cout<<"unfolded_crosssection_name = " << unfolded_crosssection_name<< std::endl;
   std::cout<<"truecross_name = " << truecross_name<< std::endl;
   std::cout<<"nom_Eff_name = " << nom_Eff_name<< std::endl;
   std::cout<<"dom_Eff_name = " << dom_Eff_name<< std::endl;
   std::cout<<"eff_name = " << eff_name<< std::endl;
   std::cout<<"mvnreponse_Mig_name = " << mvnreponse_Mig_name<< std::endl;
   std::cout<<"mvnreponse_RECO_name = " << mvnreponse_RECO_name<< std::endl;
   std::cout<<"mvnreponse_true_name = " << mvnreponse_true_name<< std::endl;
   std::cout<<"TRUEcrosssection_Elastic = " << TRUEcrosssection_Elastic<< std::endl;
   std::cout<<"TRUEcrosssection_DISSIS = " << TRUEcrosssection_DISSIS<< std::endl;
   std::cout<<"TRUEcrosssection_DISSoft = " << TRUEcrosssection_DISSoft<< std::endl;
   std::cout<<"TRUEcrosssection_DISHard = " << TRUEcrosssection_DISHard<< std::endl;
   std::cout<<"TRUEcrosssection_deltaRes = " << TRUEcrosssection_deltaRes<< std::endl;
   std::cout<<"TRUEcrosssection_HeavierRes = " << TRUEcrosssection_HeavierRes<< std::endl;
   std::cout<<"TRUEcrosssection_2p2h = " << TRUEcrosssection_2p2h<< std::endl;
   std::cout<<"TRUEcrosssection_Other = " << TRUEcrosssection_Other<< std::endl;
   std::cout<<"TRUEcrosssection_none = " << TRUEcrosssection_none<< std::endl;


 }


  }

  else if(isFUll==false){

    //std::string hist1_name = hist_name + "_" + playlist;
    //Name_Map.insert(std::make_pair(Data_BG, hist1_name));

    //std::string hist1_name_pot = hist1_name + "_potnorm";
    //Name_Map.insert(std::make_pair(Data_BG_potNorm, hist1_name_pot));

    std::string hist1_name = hist_name + "_" + playlist + "_Data_Signal";
    Name_Map.insert(std::make_pair(Data_signal, hist1_name));

    std::string hist_RECO_name = hist_name + "_" + playlist + "_MC_RECO";
    Name_Map.insert(std::make_pair(MC_reco, hist_RECO_name));


  }


  return Name_Map;

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
CrossSection_name_Map Generate_2DCrossSection_histsNames_withInteraction_DISbreakdown_forMasterAna(
  std::string hist_name,  std::string playlist,  bool PrintNames)
  {

  CrossSection_name_Map Name_Map;

    std::string hist1_name = hist_name + "_" + playlist + "_Data_Signal";
    Name_Map.insert(std::make_pair(Data_signal, hist1_name));

    std::string hist_RECO_name = hist_name + "_" + playlist + "_MC_RECO";
    Name_Map.insert(std::make_pair(MC_reco, hist_RECO_name));

    //std::string hist1_name_pot = hist_name + "_" + playlist + "_potnorm_Data_Signal";
    //Name_Map.insert(std::make_pair(Data_signal_potNorm, hist1_name_pot));

    std::string hist1_name_BG = hist_name + "_" + playlist + "_MC_RECO_BG";
    Name_Map.insert(std::make_pair(MC_reco_BG, hist1_name_BG));

    std::string hist1_name_Data_signal_BG_subtracted = hist_name + "_" + playlist  + "_Data_BG_Subtracted";
    Name_Map.insert(std::make_pair(Data_signal_BG_subtracted, hist1_name_Data_signal_BG_subtracted));

    std::string unfolded_name = hist_name + "_unfolded_data";
    Name_Map.insert(std::make_pair(Data_signal_unfolded, unfolded_name));

    std::string eff_Corrected_name = hist_name +"_unfolded_data_effcorrected";
    Name_Map.insert(std::make_pair(Data_signal_unfolded_effcorrected, eff_Corrected_name));

    std::string unfolded_crosssection_name = hist_name + "_CrossSection_data_unfolded_effCorrect";
    Name_Map.insert(std::make_pair(Data_crosssection, unfolded_crosssection_name));

    std::string truecross_name = hist_name + "_TrueCrossSection";
    Name_Map.insert(std::make_pair(True_crosssection, truecross_name));

    std::string nom_Eff_name = hist_name+ "_" + playlist + "_effNum";
    Name_Map.insert(std::make_pair(nom_Eff, nom_Eff_name));

    std::string dom_Eff_name = hist_name + "_" + playlist + "_effDom";
    Name_Map.insert(std::make_pair(dom_Eff, dom_Eff_name));

    std::string eff_name = hist_name + "_efficiency";
    Name_Map.insert(std::make_pair(Eff, eff_name));

    std::string mvnreponse_Mig_name = hist_name + "_mvnreponse_Mig";
    Name_Map.insert(std::make_pair(mvnreponse_Mig, mvnreponse_Mig_name));

    std::string mvnreponse_RECO_name = hist_name + "_mvnreponse_RECO";
    Name_Map.insert(std::make_pair(mvnreponse_RECO, mvnreponse_RECO_name));

    std::string mvnreponse_true_name = hist_name + "_mvnreponse_TRUE";
    Name_Map.insert(std::make_pair(mvnreponse_TRUE, mvnreponse_true_name));

   std::string TRUEcrosssection_Elastic = hist_name + "_TrueCrossSection_CrossSection_Interaction_QE";
   Name_Map.insert(std::make_pair(True_crosssection_interaction_Elastic,TRUEcrosssection_Elastic));

   std::string TRUEcrosssection_DISSIS = hist_name + "_TrueCrossSection_CrossSection_Interaction_DISSIS";
   Name_Map.insert(std::make_pair(True_crosssection_interaction_DISSIS,TRUEcrosssection_DISSIS));

   std::string TRUEcrosssection_DISSoft = hist_name + "_TrueCrossSection_CrossSection_Interaction_DISSoft";
   Name_Map.insert(std::make_pair(True_crosssection_interaction_DISSoft,TRUEcrosssection_DISSoft));

   std::string TRUEcrosssection_DISHard = hist_name + "_TrueCrossSection_CrossSection_Interaction_DISHard";
   Name_Map.insert(std::make_pair(True_crosssection_interaction_DISHard,TRUEcrosssection_DISHard));

   std::string TRUEcrosssection_deltaRes = hist_name + "_TrueCrossSection_CrossSection_Interaction_#DeltaRes";
   Name_Map.insert(std::make_pair(True_crosssection_interaction_DeltaRes,TRUEcrosssection_deltaRes));

   std::string TRUEcrosssection_HeavierRes = hist_name + "_TrueCrossSection_CrossSection_Interaction_HeavierRes";
   Name_Map.insert(std::make_pair(True_crosssection_interaction_HeavierRes,TRUEcrosssection_HeavierRes));

   std::string TRUEcrosssection_2p2h = hist_name + "_TrueCrossSection_CrossSection_Interaction_2p2h";
   Name_Map.insert(std::make_pair(True_crosssection_interaction_2p2h, TRUEcrosssection_2p2h));

   std::string TRUEcrosssection_Other = hist_name + "_TrueCrossSection_CrossSection_Interaction_Other";
   Name_Map.insert(std::make_pair(True_crosssection_interaction_other,TRUEcrosssection_Other));

   std::string TRUEcrosssection_none = hist_name + "_TrueCrossSection_CrossSection_Interaction_None";
    Name_Map.insert(std::make_pair(True_crosssection_interaction_none,TRUEcrosssection_none));

    if(PrintNames==true){

   std::cout<<"Printer Names of Got His"<<std::endl;
   std::cout<<"hist1_name = " << hist1_name<< std::endl;
   std::cout<<"hist_RECO_name = " << hist_RECO_name<< std::endl;
   //std::cout<<"hist1_name_pot = " << hist1_name_pot<< std::endl;
   //std::cout<<"hist1_name_pot_full_empty = " << hist1_name_pot_full_empty<< std::endl;
   //std::cout<<"hist2_name_pot_full_empty = " << hist2_name_pot_full_empty<< std::endl;
   std::cout<<"unfolded_name = " << unfolded_name<< std::endl;
   std::cout<<"eff_Corrected_name = " << eff_Corrected_name<< std::endl;
   std::cout<<"unfolded_crosssection_name = " << unfolded_crosssection_name<< std::endl;
   std::cout<<"truecross_name = " << truecross_name<< std::endl;
   std::cout<<"nom_Eff_name = " << nom_Eff_name<< std::endl;
   std::cout<<"dom_Eff_name = " << dom_Eff_name<< std::endl;
   std::cout<<"eff_name = " << eff_name<< std::endl;
   std::cout<<"mvnreponse_Mig_name = " << mvnreponse_Mig_name<< std::endl;
   std::cout<<"mvnreponse_RECO_name = " << mvnreponse_RECO_name<< std::endl;
   std::cout<<"mvnreponse_true_name = " << mvnreponse_true_name<< std::endl;
   //std::cout<<"TRUEcrosssection_Elastic = " << TRUEcrosssection_Elastic<< std::endl;
   //std::cout<<"TRUEcrosssection_DISSIS = " << TRUEcrosssection_DISSIS<< std::endl;
   //std::cout<<"TRUEcrosssection_DISSoft = " << TRUEcrosssection_DISSoft<< std::endl;
   //std::cout<<"TRUEcrosssection_DISHard = " << TRUEcrosssection_DISHard<< std::endl;
   //std::cout<<"TRUEcrosssection_deltaRes = " << TRUEcrosssection_deltaRes<< std::endl;
   //std::cout<<"TRUEcrosssection_HeavierRes = " << TRUEcrosssection_HeavierRes<< std::endl;
   //std::cout<<"TRUEcrosssection_2p2h = " << TRUEcrosssection_2p2h<< std::endl;
   //std::cout<<"TRUEcrosssection_Other = " << TRUEcrosssection_Other<< std::endl;
   //std::cout<<"TRUEcrosssection_none = " << TRUEcrosssection_none<< std::endl;


 }


  return Name_Map;

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void Make2DCrossSectionPlots_Interaction_Ratio(
  CrossSection_MnvH2D_Map CrossSection_map_tracker,
  CrossSection_MnvH2D_Map CrossSection_map_helium,
  std::string cross_section_units, std::string pdf,
  bool MakeXaxisLOG,bool doBinwidth,
  Muon2DVar MuonVar, char *Playlist_name, TCanvas *can,
  MnvPlotter *plot, double POT_Data, double POT_MC,
   MnvH2D *hist_Data_Daisy_Corrected )
  {

char title_char[1024];
bool Print1Dplots = false;
double chisqrt = 999;int ndf=0;
std::cout<<"Inside MakeCrossSectionPlots " << std::endl;
/// first Plot Signal Data
std::string X_axis = GetMuon2DVar_XaxisTitle(MuonVar);
std::string Y_axis = GetMuon2DVar_YaxisTitle(MuonVar);
std::string Y_axisUnits = GetMuon2DVar_yaxisUnits(MuonVar);
std::string X_axisUnits = GetMuon2DVar_xaxisUnits(MuonVar);
std::vector<double> Pzbin_vector{1.5, 3.0, 4.0, 5.0, 6.0, 8.0, 10.0, 20.0};
std::vector<double> PTbin_vector{0.0, 0.25, 0.4, 0.55, 0.7, 0.85, 2.5};
bool DontdoBinwidth = false;
char X_axis_char[X_axis.length()+1];
char Y_axis_char[Y_axis.length()+1];
strcpy(X_axis_char, X_axis.c_str());
strcpy(Y_axis_char, Y_axis.c_str());
std::string pdfLabel = pdf + ".pdf";
char pdf_char[pdfLabel.length()+1];
strcpy(pdf_char, pdfLabel.c_str());

std::string title_base = GetMuon2DVar_Title(MuonVar);
char title_base_char[title_base.length()+1];
strcpy(title_base_char ,title_base.c_str());
MnvH2D* Daisy_correct_CrossSection = (MnvH2D*)hist_Data_Daisy_Corrected->Clone("Daisy_correct_CrossSection");



double Scale = pow(10,-39);
CrossSection_map_tracker[Data_crosssection]->Scale(1/Scale);
CrossSection_map_tracker[True_crosssection]->Scale(1/Scale);
CrossSection_map_helium[Data_crosssection]->Scale(1/Scale);
CrossSection_map_helium[True_crosssection]->Scale(1/Scale);
CrossSection_map_tracker[True_crosssection_interaction_Elastic]->Scale(1/Scale);
CrossSection_map_tracker[True_crosssection_interaction_DISSIS]->Scale(1/Scale);
CrossSection_map_tracker[True_crosssection_interaction_DISSoft]->Scale(1/Scale);
CrossSection_map_tracker[True_crosssection_interaction_DISHard]->Scale(1/Scale);
CrossSection_map_tracker[True_crosssection_interaction_DeltaRes]->Scale(1/Scale);
CrossSection_map_tracker[True_crosssection_interaction_HeavierRes]->Scale(1/Scale);
CrossSection_map_tracker[True_crosssection_interaction_2p2h]->Scale(1/Scale);
CrossSection_map_tracker[True_crosssection_interaction_other]->Scale(1/Scale);
CrossSection_map_tracker[True_crosssection_interaction_none]->Scale(1/Scale);
Daisy_correct_CrossSection->Scale(1/Scale);
//std::cout<<" 1Title HeavierRes : "<< CrossSection_map_tracker[True_crosssection_interaction_HeavierRes]->GetTitle() << std::endl;
//std::cout<<" 1Title Res : "<< CrossSection_map_tracker[True_crosssection_interaction_DeltaRes]->GetTitle() << std::endl;
//

// PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type> hist_Stack();

 //hist_Stack.AddComponentHist("QE", CrossSection_map_tracker[True_crosssection_interaction_Elastic]);
 //hist_Stack.AddComponentHist("SIS",CrossSection_map_tracker[True_crosssection_interaction_DISSIS]);
 //hist_Stack.AddComponentHist("SoftDIS",CrossSection_map_tracker[True_crosssection_interaction_DISSoft]);
 //hist_Stack.AddComponentHist("HardDIS",CrossSection_map_tracker[True_crosssection_interaction_DISHard]);
 //hist_Stack.AddComponentHist("#DeltaRes",CrossSection_map_tracker[True_crosssection_interaction_DeltaRes]);
 //hist_Stack.AddComponentHist("HeavierRes",CrossSection_map_tracker[True_crosssection_interaction_HeavierRes]);
 //hist_Stack.AddComponentHist("2p2h",CrossSection_map_tracker[True_crosssection_interaction_2p2h]);
 //hist_Stack.AddComponentHist("Other",CrossSection_map_tracker[True_crosssection_interaction_other]);
 //hist_Stack.AddComponentHist("None",CrossSection_map_tracker[True_crosssection_interaction_none]);
sprintf(title_char, "%s  Data_signal ", title_base_char);
Draw2DHist(CrossSection_map_tracker[Data_signal], X_axis_char, Y_axis_char, "NEvents",title_char, pdf_char, can, plot);
sprintf(title_char, "%s  MC_reco ", title_base_char);
Draw2DHist(CrossSection_map_tracker[MC_reco], X_axis_char, Y_axis_char, "NEvent" , title_char , pdf_char, can,plot);
sprintf(title_char, "%s Data_signal_unfolded ", title_base_char);
Draw2DHist(CrossSection_map_tracker[Data_signal_unfolded], X_axis_char, Y_axis_char, "NEvent" , title_char  , pdf_char, can,plot);
sprintf(title_char, "%s Data_signal_unfolded_effcorrected ", title_base_char);
Draw2DHist(CrossSection_map_tracker[Data_signal_unfolded_effcorrected], X_axis_char, Y_axis_char, "NEvent" , title_char , pdf_char, can,plot);
sprintf(title_char, "%s nom_Eff", title_base_char);
Draw2DHist(CrossSection_map_tracker[nom_Eff], X_axis_char, Y_axis_char, "NEvent" , title_char , pdf_char, can,plot);
sprintf(title_char, "%s dom_Eff", title_base_char);
Draw2DHist(CrossSection_map_tracker[dom_Eff], X_axis_char, Y_axis_char, "NEvent" , title_char , pdf_char, can,plot);

sprintf(title_char, "%s mvnreponse_Mig", title_base_char);
Draw2DHist(CrossSection_map_tracker[mvnreponse_Mig], X_axis_char, Y_axis_char, "NEvent" , title_char , pdf_char, can,plot);
sprintf(title_char, "%s mvnreponse_RECO", title_base_char);
Draw2DHist(CrossSection_map_tracker[mvnreponse_RECO], X_axis_char, Y_axis_char, "NEvent" , title_char, pdf_char, can,plot);
sprintf(title_char, "%s mvnreponse_TRUE", title_base_char);
Draw2DHist(CrossSection_map_tracker[mvnreponse_TRUE], X_axis_char, Y_axis_char, "NEvent" , title_char , pdf_char, can,plot);

bool DoBinN= true;
double Markersize = .3;

std::cout<<"Drawing:PlotDataMC_Migration_ProjX "<< std::endl;

PlotDataMC_Migration_ProjX(CrossSection_map_tracker[mvnreponse_Mig], CrossSection_map_tracker[mvnreponse_RECO],CrossSection_map_tracker[mvnreponse_TRUE],Pzbin_vector,
  pdf_char, "Migration X Projection",  "Reco P_{Z} [GeV]",
  "P_{T}",   "True P_{Z} [GeV] ",
  100, plot, can,4,.01,Markersize,DoBinN);

std::cout<<"Drawing:PlotDataMC_Migration_Proj=Y "<< std::endl;
PlotDataMC_Migration_ProjY(CrossSection_map_tracker[mvnreponse_Mig], CrossSection_map_tracker[mvnreponse_RECO],CrossSection_map_tracker[mvnreponse_TRUE],PTbin_vector,
  pdf_char, "Migration Y Projection",  "Reco P_{T} [GeV]",
  "P_{Z}",   "True P_{T} [GeV] ",
  100, plot, can,4,.01,Markersize,DoBinN) ;


PlotDataMC_Migration_ProjX(CrossSection_map_tracker[mvnreponse_Mig], CrossSection_map_tracker[mvnreponse_RECO],CrossSection_map_tracker[mvnreponse_TRUE],Pzbin_vector,
  pdf_char, "Migration X Projection (Row Norm)",  "Reco P_{Z} [GeV]",
  "P_{T}",   "True P_{Z} [GeV] ",
  1.0, plot, can,3,.01,Markersize,DoBinN) ;


PlotDataMC_Migration_ProjY(CrossSection_map_tracker[mvnreponse_Mig], CrossSection_map_tracker[mvnreponse_RECO],CrossSection_map_tracker[mvnreponse_TRUE],PTbin_vector,
  pdf_char, "Migration Y Projection (Row Norm)",  "Reco P_{T} [GeV]",
  "P_{Z}",   "True P_{T} [GeV] ",
  1.0, plot, can, 3,.01,Markersize,DoBinN) ;



//  MnvH2D *ProjectMig = GetMigration_Projection_Y_forBinN(CrossSection_map_tracker[mvnreponse_Mig], CrossSection_map_tracker[mvnreponse_RECO],CrossSection_map_tracker[mvnreponse_TRUE], Pzbin_vector , 1 );

MnvH2D *h_return =    new MnvH2D("h_return", "h_return",Pzbin_vector.size()-1, Pzbin_vector.data() ,Pzbin_vector.size()-1, Pzbin_vector.data()  );


//GetMigration_Projection_Y_forBinN_input(h_return, CrossSection_map_tracker[mvnreponse_Mig], CrossSection_map_tracker[mvnreponse_RECO],CrossSection_map_tracker[mvnreponse_TRUE], 1);


for(int  XTruthbinN = 1; XTruthbinN <= CrossSection_map_tracker[mvnreponse_TRUE]->GetNbinsX();  XTruthbinN++  ){
  for(int  XRecobinN = 1; XRecobinN <= CrossSection_map_tracker[mvnreponse_RECO]->GetNbinsX();  XRecobinN++  ){

    int globalBin =  GetGlobalBinNFrom2DMig_BinN(CrossSection_map_tracker[mvnreponse_Mig],CrossSection_map_tracker[mvnreponse_RECO], CrossSection_map_tracker[mvnreponse_TRUE], XRecobinN, 1 , XTruthbinN, 1);
    double content = CrossSection_map_tracker[mvnreponse_Mig]->GetBinContent(globalBin);

    int Global_hreturn_binN  = XTruthbinN*(h_return->GetNbinsX()+2) + XRecobinN; // Assuming Truth is Y axis
    std::cout<< "Global_hreturn_binN = " << Global_hreturn_binN << " content = " << content << std::endl;
    h_return->AddBinContent(Global_hreturn_binN,content);
  }
}


Draw2DHist(h_return, X_axis_char, X_axis_char, "NEvent" , title_char , pdf_char, can,plot);

DrawMagration_heatMap_LabelBinNumber(h_return, "x bins", "y bins",  "bin1", pdf_char, can,plot);


std::string crossSection_z_axis = "#frac{#partial^{2} #sigma}{#partial" + GetMuon2DVar_XaxisTitle_noUntils(MuonVar)+"#partial"+ GetMuon2DVar_YaxisTitle_noUntils(MuonVar) + "} #[]{10^{-39} #frac{ cm^{2}}{" +  GetMuon2DVar_yaxisUnits(MuonVar) + " N} }";
char crossSection_z_axis_char[crossSection_z_axis.length()+1];
strcpy(crossSection_z_axis_char,crossSection_z_axis.c_str());
sprintf(title_char, "%s  Data_crosssection ", title_base_char);
Draw2DHist(CrossSection_map_tracker[Data_crosssection],  "data Pt", "data Pz", crossSection_z_axis_char, title_char  ,  pdf_char, can, plot);
sprintf(title_char, "%s  True_crosssection ", title_base_char);
Draw2DHist(CrossSection_map_tracker[True_crosssection],  "true Pt", "true Pz", crossSection_z_axis_char, title_char  ,  pdf_char, can, plot);


//Draw2DHist(CrossSection_map_tracker[True_crosssection_interaction_Elastic], X_axis_char, Y_axis_char, "NEvent" , "True_crosssection_interaction_Elastic" , pdf_char, can,plot);
//Draw2DHist(CrossSection_map_tracker[True_crosssection_interaction_DISSIS], X_axis_char, Y_axis_char, "NEvent" , "True_crosssection_interaction_DISSIS" , pdf_char, can,plot);
//Draw2DHist(CrossSection_map_tracker[True_crosssection_interaction_DISSoft], X_axis_char, Y_axis_char, "NEvent" , "True_crosssection_interaction_DISSoft" , pdf_char, can,plot);
//Draw2DHist(CrossSection_map_tracker[True_crosssection_interaction_DISHard], X_axis_char, Y_axis_char, "NEvent" , "True_crosssection_interaction_DISHard" , pdf_char, can,plot);
//Draw2DHist(CrossSection_map_tracker[True_crosssection_interaction_DeltaRes], X_axis_char, Y_axis_char, "NEvent" , "True_crosssection_interaction_DeltaRes" , pdf_char, can,plot);
//Draw2DHist(CrossSection_map_tracker[True_crosssection_interaction_HeavierRes], X_axis_char, Y_axis_char, "NEvent" , "True_crosssection_interaction_HeavierRes" , pdf_char, can,plot);
//Draw2DHist(CrossSection_map_tracker[True_crosssection_interaction_2p2h], X_axis_char, Y_axis_char, "NEvent" , "True_crosssection_interaction_2p2h" , pdf_char, can,plot);
//Draw2DHist(CrossSection_map_tracker[True_crosssection_interaction_other], X_axis_char, Y_axis_char, "NEvent" , "True_crosssection_interaction_other" , pdf_char, can,plot);
//Draw2DHist(CrossSection_map_tracker[True_crosssection_interaction_none], X_axis_char, Y_axis_char, "NEvent" , "True_crosssection_interaction_none" , pdf_char, can,plot);

//std::cout<<" Title HeavierRes : "<< CrossSection_map_tracker[True_crosssection_interaction_HeavierRes]->GetTitle() << std::endl;
//std::cout<<" Title Res : "<< CrossSection_map_tracker[True_crosssection_interaction_DeltaRes]->GetTitle() << std::endl;

sprintf(title_char, "%s  Efficiency ", title_base_char);
Draw2DHist(CrossSection_map_tracker[Eff], X_axis_char, Y_axis_char, "Eff" , title_char , pdf_char, can,plot);

sprintf(title_char, "%s True denominator Fractional Uncertainty ", title_base_char);
DrawPanel_SystematicErrorPlots_ProjectionY(CrossSection_map_tracker[dom_Eff],X_axis, Y_axis, title_char, pdf_char ,.25, true, Print1Dplots );
DrawPanel_SystematicErrorPlots_ProjectionY_model(CrossSection_map_tracker[dom_Eff],X_axis, Y_axis, title_char, pdf_char ,.25, true, Print1Dplots );
DrawPanel_SystematicErrorPlots_ProjectionX(CrossSection_map_tracker[dom_Eff],X_axis, Y_axis, title_char, pdf_char ,.25, true, Print1Dplots );
DrawPanel_SystematicErrorPlots_ProjectionX_model(CrossSection_map_tracker[dom_Eff],X_axis, Y_axis, title_char, pdf_char ,.25, true, Print1Dplots );


sprintf(title_char, "%s  True Denominator", title_base_char);
CrossSection_map_tracker[dom_Eff]->Scale(1.0/1000);
CrossSection_map_tracker[Data_signal_unfolded]->Scale(1.0/1000);
CrossSection_map_tracker[Data_signal_unfolded_effcorrected]->Scale(1.0/1000);
Draw_2D_Panel_MC_Only_frompointer(CrossSection_map_tracker[dom_Eff] , title_char, "True Denominator",
Y_axis,Y_axisUnits, X_axis, X_axisUnits,"NEvents(10^{-3})" , 1.1, pdf_char, doBinwidth, MakeXaxisLOG,
.03, .03, false);

sprintf(title_char, "%s Numerator Fractional Uncertainty ", title_base_char);
DrawPanel_SystematicErrorPlots_ProjectionY(CrossSection_map_tracker[nom_Eff],X_axis, Y_axis, title_char, pdf_char,.35, true, Print1Dplots );
DrawPanel_SystematicErrorPlots_ProjectionX(CrossSection_map_tracker[nom_Eff],X_axis, Y_axis, title_char, pdf_char,.35, true, Print1Dplots );
CrossSection_map_tracker[nom_Eff]->Scale(1.0/1000);

sprintf(title_char, "%s  Numerator", title_base_char);
Draw_2D_Panel_MC_Only_frompointer(CrossSection_map_tracker[nom_Eff] , title_char, "True Numerator",
Y_axis,Y_axisUnits, X_axis, X_axisUnits,"NEvents(10^{-3})" , 1.1, pdf_char, doBinwidth, MakeXaxisLOG,
.03, .03, false);


sprintf(title_char, "%s  Efficiency Fractional Uncertainty ", title_base_char);
DrawPanel_SystematicErrorPlots_ProjectionY(CrossSection_map_tracker[Eff], X_axis, Y_axis, title_char, pdf_char, .1, true, Print1Dplots );
DrawPanel_SystematicErrorPlots_ProjectionX(CrossSection_map_tracker[Eff], X_axis, Y_axis, title_char, pdf_char, .1, true, Print1Dplots );

sprintf(title_char, "Efficiency Fractional Uncertainty [ProjX] %s " , title_base_char);
Plot2D_FractionError_ProjX(CrossSection_map_tracker[Eff], pdf_char, title_char,  X_axis_char, Y_axis_char, .1,.02);

sprintf(title_char, "Efficiency Fractional Uncertainty [ProjY] %s " , title_base_char);
Plot2D_FractionError_ProjY(CrossSection_map_tracker[Eff], pdf_char, title_char,  X_axis_char, Y_axis_char, .1,.02);

//Plot2D_FractionError_ProjY_Group(PlotUtils::MnvH2D* HistInput,
//        char *pdf_label, char *histotitle,  char *xaxislabel, char *GroupName,
//        char *yaxislabel,
//        double Ymax,
//        double text_size);

std::cout<< "Drawing indivdual Systematic errors "<<std::endl;

//DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE FSI",           CrossSection_map_tracker[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false  );
//DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE Cross Section", CrossSection_map_tracker[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false  );
//DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE CrossSection QE", CrossSection_map_tracker[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false, true  );
//DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE CrossSection 1#pi", CrossSection_map_tracker[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false, true  );
//DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE CrossSection DIS", CrossSection_map_tracker[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false, true  );
//DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE CrossSection NC" ,CrossSection_map_tracker[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false, true  );
//DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE Nucleon FSI", CrossSection_map_tracker[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false, true  );
//DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE Pion FSI", CrossSection_map_tracker[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false, true  );
//DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "Vertex Smearing",     CrossSection_map_tracker[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false  );
//DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "2p2h RPA Mvn1Tune",   CrossSection_map_tracker[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false  );
//DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "Beam Angle",          CrossSection_map_tracker[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false  );
//DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "Muon Reconstruction", CrossSection_map_tracker[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false  );
//
//DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "GENIE FSI",           CrossSection_map_tracker[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false  );
//DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "GENIE Cross Section", CrossSection_map_tracker[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false  );
//DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "GENIE CrossSection QE", CrossSection_map_tracker[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false, true  );
//DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "GENIE CrossSection 1#pi", CrossSection_map_tracker[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false, true  );
//DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "GENIE CrossSection DIS", CrossSection_map_tracker[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false, true  );
//DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "GENIE CrossSection NC", CrossSection_map_tracker[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false, true  );
//DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "GENIE Nucleon FSI", CrossSection_map_tracker[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false, true  );
//DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "GENIE Pion FSI", CrossSection_map_tracker[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false, true  );
//DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "Vertex Smearing",     CrossSection_map_tracker[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false  );
//DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "2p2h RPA Mvn1Tune",   CrossSection_map_tracker[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false  );
//DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "Beam Angle",          CrossSection_map_tracker[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false  );
//DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "Muon Reconstruction", CrossSection_map_tracker[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false  );


DrawPanel_SystematicErrorPlots_ProjectionX(CrossSection_map_tracker[Eff], X_axis, Y_axis, title_char, pdf_char, .15, true, Print1Dplots );



sprintf(title_char, "%s  Efficiency ", title_base_char);
Draw_2D_Panel_MC_Only_frompointer(CrossSection_map_tracker[Eff], title_char, "Efficiency",
  Y_axis, Y_axisUnits, X_axis, X_axisUnits, "Efficiency" , 1.1, pdf_char, DontdoBinwidth, MakeXaxisLOG,
  .03, .03, false);

Draw_2D_Panel_MC_Only_frompointer_WithErrorBand(CrossSection_map_tracker[Eff], title_char, "Efficiency",
Y_axis, Y_axisUnits, X_axis, X_axisUnits, "Efficiency" , 1.1, pdf_char, DontdoBinwidth, MakeXaxisLOG,
.03, .03, false);

std::vector<double> XMultipliers{1,1,1,1,1,1,1,1};
std::vector<double> YMultipliers{1,1,1,1,1,1,1,1};
bool do_bin_width_norm_eff = false;
bool statPlusSysDATA = true;
 bool statPlusSysMC  = true;


PlotMC_ErrorBand2D_ProjX(CrossSection_map_tracker[Eff],  pdf_char, title_char,  X_axis_char,
  Y_axis_char,   "Efficiency", .1 , false,  false, XMultipliers,
  statPlusSysDATA , statPlusSysMC , do_bin_width_norm_eff, true , .03);

PlotMC_ErrorBand2D_ProjY(CrossSection_map_tracker[Eff],  pdf_char, title_char,  Y_axis_char,
    X_axis_char,   "Efficiency", .1 , false,  false, XMultipliers,
    statPlusSysDATA , statPlusSysMC , do_bin_width_norm_eff, true , .03);


    PlotMC_ErrorBand2D_ProjX(CrossSection_map_tracker[Eff],  pdf_char, title_char,  X_axis_char,
      Y_axis_char,   "Efficiency", 1 , true,  false, XMultipliers,
      statPlusSysDATA , statPlusSysMC , do_bin_width_norm_eff, true , .03);

    PlotMC_ErrorBand2D_ProjY(CrossSection_map_tracker[Eff],  pdf_char, title_char,  Y_axis_char,
        X_axis_char,   "Efficiency", 1 , true,  false, XMultipliers,
        statPlusSysDATA , statPlusSysMC , do_bin_width_norm_eff, true , .03);




sprintf(title_char, "%s Unfolded Data Fractional Uncertainty", title_base_char);
DrawPanel_SystematicErrorPlots_ProjectionY(CrossSection_map_tracker[Data_signal_unfolded],X_axis, Y_axis, title_char, pdf_char ,.1, true, Print1Dplots );
DrawPanel_SystematicErrorPlots_ProjectionX(CrossSection_map_tracker[Data_signal_unfolded], Y_axis, X_axis, title_char, pdf_char ,.1, true, Print1Dplots );


//CrossSection_map_tracker[dom_Eff]->Scale(1.0/1000);
sprintf(title_char, "%s  BG subtracted Unfolded Data ", title_base_char);
//Draw_2D_Panel_MC_Only_frompointer(CrossSection_map_tracker[Data_signal_unfolded] , title_char, "Unfolded Data",
//Y_axis,Y_axisUnits, X_axis, X_axisUnits,"NEvents(10^{-3})" , 1.1, pdf_char, doBinwidth, MakeXaxisLOG,
//.03, .03, false);

Draw2D_Panel_CV_SystematicErrFromPointer(CrossSection_map_tracker[Data_signal_unfolded], CrossSection_map_tracker[dom_Eff], Playlist_name,
   "Combined", plot,
  pdf_char, title_char, Y_axis_char, X_axis_char,
  "NEvents(10^{-3}) / [GeV^{2}]", doBinwidth, MakeXaxisLOG,
  15, 5, .03, .03, chisqrt, ndf, false );

  PlotDataMC_ErrorBand2D_ProjY(CrossSection_map_tracker[Data_signal_unfolded], CrossSection_map_tracker[dom_Eff],
    pdf_char, title_char ,  Y_axis_char, X_axis_char,   "Events(10^{-3}) / [GeV^{2}]",
    99, false,  true, XMultipliers,
    true , true , doBinwidth,  false, .03);

    PlotDataMC_ErrorBand2D_ProjX(CrossSection_map_tracker[Data_signal_unfolded], CrossSection_map_tracker[dom_Eff],
      pdf_char, title_char ,  X_axis_char, Y_axis_char,   "Events(10^{-3}) / [GeV^{2}]",
      99, false,  true, XMultipliers,
      true , true , doBinwidth,  false, .03);
      //bool statPlusSysDATA , bool statPlusSysMC ,
        //                 bool do_bin_width_norm,  bool useHistTitles, double text_size


sprintf(title_char, "%s Unfolded Eff corrected Data Fractional Uncertainty", title_base_char);
DrawPanel_SystematicErrorPlots_ProjectionY(CrossSection_map_tracker[Data_signal_unfolded_effcorrected],X_axis, Y_axis, title_char, pdf_char ,.1, true, Print1Dplots );
DrawPanel_SystematicErrorPlots_ProjectionX(CrossSection_map_tracker[Data_signal_unfolded_effcorrected], Y_axis, X_axis, title_char, pdf_char ,.1, true, Print1Dplots );



sprintf(title_char, "%s  BG subtracted Unfolded Eff corrected Data", title_base_char);
//Draw_2D_Panel_MC_Only_frompointer(CrossSection_map_tracker[Data_signal_unfolded_effcorrected] , title_char, "Unfolded Eff corrected Data",
//Y_axis,Y_axisUnits, X_axis, X_axisUnits,"NEvents" , 1.1, pdf_char, doBinwidth, MakeXaxisLOG,
//.03, .03, false);

//Draw2D_Panel_CV_SystematicErrFromPointer(CrossSection_map_tracker[Data_signal_unfolded_effcorrected], CrossSection_map_tracker[dom_Eff], Playlist_name,
//   "Combined", plot,
//  pdf_char, title_char, Y_axis_char, X_axis_char,
//  "NEvents", doBinwidth, MakeXaxisLOG,
//  15, 5, .03, .03, chisqrt, ndf, false );

//  Draw2D_Panel_CV_SystematicErrFromPointer(CrossSection_map_tracker[Data_signal_unfolded_effcorrected],
//    CrossSection_map_tracker[dom_Eff],Playlist_name,
//    "Combined", plot,
//    pdf_char, title_char, Y_axis_char, X_axis_char,
//    "Events(10^{-3}) / [GeV^2]", doBinwidth, MakeXaxisLOG,
//    15, 15, .03, .03, chisqrt, ndf, false );


    PlotDataMC_ErrorBand2D_ProjY(CrossSection_map_tracker[Data_signal_unfolded_effcorrected], CrossSection_map_tracker[dom_Eff],
      pdf_char, title_char ,  Y_axis_char, X_axis_char,   "Events(10^{-3})/[GeV^{2}]",
      99, false,  true, XMultipliers,
      true , true , doBinwidth,  false, .03);

      PlotDataMC_ErrorBand2D_ProjX(CrossSection_map_tracker[Data_signal_unfolded_effcorrected], CrossSection_map_tracker[dom_Eff],
        pdf_char, title_char ,  X_axis_char, Y_axis_char,   "Events(10^{-3})/[GeV^{2}]",
        99, false,  true, XMultipliers,
        true , true , doBinwidth,  false, .03);


//sprintf(title_char, "%s  Efficiency denominator Fractional uncertainty ", title_base_char);
//DrawPanel_SystematicErrorPlots(CrossSection_map_tracker[dom_Eff], Y_axis, X_axis,title_char, pdf_char );
//sprintf(title_char, "%s  Efficiency numeratorFractional uncertainty ", title_base_char);
//DrawPanel_SystematicErrorPlots(CrossSection_map_tracker[nom_Eff], Y_axis, X_axis,title_char, pdf_char );
//sprintf(title_char, "%s NEvent ", title_base_char);
// DrawPanel_MC_dataErrorPlots(CrossSection_map_tracker[Data_signal],CrossSection_map_tracker[MC_reco], Y_axis, X_axis,title_char, pdf_char);

sprintf(title_char, "%s Event Selection", title_base_char);

Draw2D_Panel_CV_SystematicErrFromPointer(CrossSection_map_tracker[Data_signal],
  CrossSection_map_tracker[MC_reco],Playlist_name  ,
  "Full", plot,
  pdf_char, title_char, Y_axis_char, X_axis_char,
"Nevent", doBinwidth, MakeXaxisLOG,
  100, 100, .03, .03, chisqrt, ndf, false );

PlotDataMC_ErrorBand2D_ProjY(CrossSection_map_tracker[Data_signal],
  CrossSection_map_tracker[MC_reco],
  pdf_char, title_char ,  Y_axis_char, X_axis_char,   "Events / [GeV^{2}]",
  99, false,  true, XMultipliers,
  true , true , true,  false, .03);


PlotDataMC_ErrorBand2D_ProjX(CrossSection_map_tracker[Data_signal],
  CrossSection_map_tracker[MC_reco],
  pdf_char, title_char ,  X_axis_char, Y_axis_char,   "Events / [GeV^{2}]",
  99, false,  true, XMultipliers,
  true , true , true,  false, .03);


//
sprintf(title_char, "%s RECO Event Selection Rate with Data BG Subtracted", title_base_char);


PlotDataMC_ErrorBand2D_ProjY(CrossSection_map_tracker[Data_signal_BG_subtracted],
  CrossSection_map_tracker[MC_reco],
  pdf_char, title_char ,  Y_axis_char, Y_axis_char,   "Events / [GeV^{2}]",
  99, false,  true, XMultipliers,
  true , true , true,  false, .03);

PlotDataMC_ErrorBand2D_ProjX(CrossSection_map_tracker[Data_signal_BG_subtracted],
   CrossSection_map_tracker[MC_reco],
  pdf_char, title_char ,  Y_axis_char, Y_axis_char,   "Events / [GeV^{2}]",
  99, false,  true, XMultipliers,
  true , true , true,  false, .03);


sprintf(title_char, "%s Efficiency [%s]",title_base_char, Playlist_name );
Draw2DHist(CrossSection_map_tracker[Eff],  X_axis_char, Y_axis_char, "[Efficiency]",
           title_char  ,  pdf_char, can, plot);
std::string titlestring(title_char);

Draw2DHist_Migration_Histpointer(CrossSection_map_tracker[Eff], titlestring,
                  X_axis, Y_axis,  "Efficiency",pdf, can, plot);
sprintf(title_char, "%s Migration [%s]",title_base_char, Playlist_name );
Draw2DHist(CrossSection_map_tracker[mvnreponse_Mig],  "BinN", "BinN", "[NEvents]", title_char  ,  pdf_char, can, plot);

std::string title_Cross_Section = title_base + " 2D Cross-Section:  #nu_{#mu} + CH #rightarrow #mu^{-} + X";
std::string title_Cross_Section_Daisy = title_base + "Daisy Corrected 2D Cross-Section:  #nu_{#mu} + CH #rightarrow #mu^{-} + X";
char title_Cross_Section_char[title_Cross_Section.length()+1];
strcpy(title_Cross_Section_char,title_Cross_Section.c_str());


char title_Cross_Section_daisy_char[title_Cross_Section_Daisy.length()+1];
strcpy(title_Cross_Section_daisy_char,title_Cross_Section_Daisy.c_str());


//sprintf(title_char, "%s  [%s]",title_base_char, Playlist_name );
//std::string crossSection_z_axis = "#frac{#partial #sigma}{#partial" + GetMuon2DVar_XaxisTitle_noUntils(MuonVar)+"#partial"+ GetMuon2DVar_YaxisTitle_noUntils(MuonVar) + "} (10^{-38} cm^{2} / " +  GetMuon2DVar_yaxisUnits(MuonVar) + " / ^{4}He)";
//char crossSection_z_axis_char[crossSection_z_axis.length()+1];
//strcpy(crossSection_z_axis_char,crossSection_z_axis.c_str());
//
Draw2D_Panel_CV_SystematicErrFromPointer(CrossSection_map_tracker[Data_crosssection],
   CrossSection_map_tracker[True_crosssection], Playlist_name,
   "Combined", plot,
  pdf_char, title_Cross_Section_char, Y_axis_char, X_axis_char,
  crossSection_z_axis_char, DontdoBinwidth, MakeXaxisLOG,
  15, 5, .03, .03, chisqrt, ndf, false );

std::vector<double> XMultipliers_cross{5,1,1,1,1,1,1,1};
std::vector<double> YMultipliers_cross{1,1,1,1,1,4,4,1};

      PlotDataMC_ErrorBand2D_ProjY(CrossSection_map_tracker[Data_crosssection], CrossSection_map_tracker[True_crosssection],
        pdf_char, title_Cross_Section_char ,  Y_axis_char, X_axis_char,   crossSection_z_axis_char,
        99, false,  true, YMultipliers_cross,
        true , true , !DontdoBinwidth,  false, .03);

        PlotDataMC_ErrorBand2D_ProjX(CrossSection_map_tracker[Data_crosssection], CrossSection_map_tracker[True_crosssection],
          pdf_char, title_Cross_Section_char ,  X_axis_char, Y_axis_char,   crossSection_z_axis_char,
          99, false,  true, XMultipliers_cross,
          true , true , !DontdoBinwidth,  false, .03);


          sprintf(title_char, "%s Cross Section Data Fractional Uncertainty", title_base_char);
          DrawPanel_SystematicErrorPlots_ProjectionY(CrossSection_map_tracker[Data_crosssection],X_axis, Y_axis, title_char, pdf_char ,.1, true, Print1Dplots );
          DrawPanel_SystematicErrorPlots_ProjectionX(CrossSection_map_tracker[Data_crosssection], Y_axis, X_axis, title_char, pdf_char ,.1, true, Print1Dplots );



  //Data_signal_unfolded
  //Data_signal_unfolded_effcorrected
  //dom_Eff


bool DataStat_SysError = true;
bool MC_Stat_SysError =true;

  Draw_2D_Panel_MC_andData_frompointer_DISbreakdown(CrossSection_map_tracker[Data_crosssection], CrossSection_map_tracker[True_crosssection],
    CrossSection_map_tracker[True_crosssection_interaction_Elastic],
    CrossSection_map_tracker[True_crosssection_interaction_HeavierRes] ,
    CrossSection_map_tracker[True_crosssection_interaction_DeltaRes]  ,
    CrossSection_map_tracker[True_crosssection_interaction_2p2h] ,
    CrossSection_map_tracker[True_crosssection_interaction_DISSIS] ,
     CrossSection_map_tracker[True_crosssection_interaction_DISHard] ,
     CrossSection_map_tracker[True_crosssection_interaction_DISSoft] ,
     CrossSection_map_tracker[True_crosssection_interaction_other],
     CrossSection_map_tracker[True_crosssection_interaction_none],
     DataStat_SysError,
     MC_Stat_SysError,
    title_Cross_Section_char, Y_axis,
    X_axis_char,  crossSection_z_axis_char , 1.4, 1.4, false,
    pdf_char,  doBinwidth,  MakeXaxisLOG,
    .03, .03, false);

std::vector<double> Mupl_X{5,1,1,1,1,1,1,1};
std::vector<double> Mupl_Y{1,1,1,1,1,4,4,1};

    Draw_2D_Panel_MC_andData_frompointer_DISbreakdown(CrossSection_map_tracker[Data_crosssection], CrossSection_map_tracker[True_crosssection],
      CrossSection_map_tracker[True_crosssection_interaction_Elastic],
      CrossSection_map_tracker[True_crosssection_interaction_HeavierRes] ,
      CrossSection_map_tracker[True_crosssection_interaction_DeltaRes]  ,
      CrossSection_map_tracker[True_crosssection_interaction_2p2h] ,
      CrossSection_map_tracker[True_crosssection_interaction_DISSIS] ,
       CrossSection_map_tracker[True_crosssection_interaction_DISHard] ,
       CrossSection_map_tracker[True_crosssection_interaction_DISSoft] ,
       CrossSection_map_tracker[True_crosssection_interaction_other],
       CrossSection_map_tracker[True_crosssection_interaction_none],
       DataStat_SysError,
       MC_Stat_SysError,
      title_Cross_Section_char, Y_axis,
      X_axis_char,  crossSection_z_axis_char , 25, 3.5, false,
      pdf_char,  doBinwidth,  MakeXaxisLOG,
      .03, .03, true, Mupl_Y, Mupl_X);



      Draw_2D_Panel_MC_andData_frompointer_DISbreakdown_STACK(CrossSection_map_tracker[Data_crosssection], CrossSection_map_tracker[True_crosssection],
        CrossSection_map_tracker[True_crosssection_interaction_Elastic],
        CrossSection_map_tracker[True_crosssection_interaction_HeavierRes] ,
        CrossSection_map_tracker[True_crosssection_interaction_DeltaRes]  ,
        CrossSection_map_tracker[True_crosssection_interaction_2p2h] ,
        CrossSection_map_tracker[True_crosssection_interaction_DISSIS] ,
         CrossSection_map_tracker[True_crosssection_interaction_DISHard] ,
         CrossSection_map_tracker[True_crosssection_interaction_DISSoft] ,
         CrossSection_map_tracker[True_crosssection_interaction_other],
         CrossSection_map_tracker[True_crosssection_interaction_none],
         DataStat_SysError,
         MC_Stat_SysError,
        title_Cross_Section_char, Y_axis,
        X_axis_char,  crossSection_z_axis_char , 3.5, 25, true,
        pdf_char,  doBinwidth,  MakeXaxisLOG,
        .03, .03, false, Mupl_Y, Mupl_X);


TObjArray stack_input;

stack_input.Add (CrossSection_map_tracker[True_crosssection_interaction_Elastic]) ;
stack_input.Add (CrossSection_map_tracker[True_crosssection_interaction_HeavierRes]);
stack_input.Add (CrossSection_map_tracker[True_crosssection_interaction_DeltaRes]);
stack_input.Add (CrossSection_map_tracker[True_crosssection_interaction_2p2h]);
stack_input.Add (CrossSection_map_tracker[True_crosssection_interaction_DISSIS]);
stack_input.Add (CrossSection_map_tracker[True_crosssection_interaction_DISHard]);
stack_input.Add (CrossSection_map_tracker[True_crosssection_interaction_DISSoft]);
stack_input.Add (CrossSection_map_tracker[True_crosssection_interaction_other]);
stack_input.Add (CrossSection_map_tracker[True_crosssection_interaction_none]);
const TObjArray  *mcHists_Breakdown_input =  &stack_input ;
std::vector<int> Helium9_colorScheme = {
  TColor::GetColor("#F1B6DA"),//pink 11

  TColor::GetColor("#DF00FF"), //'psychedelic Purple1
  TColor::GetColor(43,206,72 ), //green 2
  TColor::GetColor("#87CEEB"),//'skyblue' 3
  TColor::GetColor("#0859C6"), //blue 4
  TColor::GetColor("#654522"), // yellowishbrown,5
  TColor::GetColor("#ffc922"), //'sunset yellow'6
  TColor::GetColor("#f47835"),//2 candy Apple7
  TColor::GetColor("#800000"),  // Maroon
  TColor::GetColor("#90AD1C"),//8
  TColor::GetColor("#BABABA"), //Gray 9
  TColor::GetColor("#00FFFF"),//'aqua' 10
  TColor::GetColor("#AAF0D1"), // mint green
  TColor::GetColor(kRed),//'Jade' 12
  TColor::GetColor("#FAFAD2"),  // LightGoldenRodYellow 13

  TColor::GetColor("#555555"),  // dark grey 15
  TColor::GetColor(0, 153, 143 ), //turquoise 16
  TColor::GetColor("#654522"), // yellowishbrown, 17
  TColor::GetColor("#8db600"), // yellowgreen, 18
  TColor::GetColor("#D3D3D3"),  //'lightgrey' 19
  TColor::GetColor("#90AD1C"), // 20
  TColor::GetColor("#CCDDAA"), //21
  TColor::GetColor(kMagenta), //22
  TColor::GetColor("#EEFF00") // neonyellow,0
};

PlotDataStackedMC2D_ProjY(CrossSection_map_tracker[Data_crosssection], CrossSection_map_tracker[True_crosssection], mcHists_Breakdown_input,
                                       Helium9_colorScheme, doBinwidth,
                                      pdf_char, title_Cross_Section_char,  X_axis_char,
                                      Y_axis_char,   crossSection_z_axis_char,
                                      6, true,  true,
                                       Mupl_Y );

PlotDataStackedMC2D_ProjX(CrossSection_map_tracker[Data_crosssection], CrossSection_map_tracker[True_crosssection], mcHists_Breakdown_input,
 Helium9_colorScheme, doBinwidth,
  pdf_char, title_Cross_Section_char,  Y_axis_char,
  X_axis_char,   crossSection_z_axis_char,
  1, true,  true,
  Mupl_X );

  PlotDataStackedMC2D_ProjY(Daisy_correct_CrossSection, CrossSection_map_tracker[True_crosssection], mcHists_Breakdown_input,
                                         Helium9_colorScheme, doBinwidth,
                                        pdf_char, title_Cross_Section_daisy_char,  X_axis_char,
                                        Y_axis_char,   crossSection_z_axis_char,
                                        6, true,  true,
                                         Mupl_Y );

  PlotDataStackedMC2D_ProjX(Daisy_correct_CrossSection, CrossSection_map_tracker[True_crosssection], mcHists_Breakdown_input,
   Helium9_colorScheme, doBinwidth,
    pdf_char, title_Cross_Section_daisy_char,  Y_axis_char,
    X_axis_char,   crossSection_z_axis_char,
    1, true,  true,
    Mupl_X );



PlotFractionofEvents2D_ProjY(CrossSection_map_tracker[True_crosssection], mcHists_Breakdown_input,
                           Helium9_colorScheme,"Fraction per Bin" ,
                           "Fraction Total",
                           pdf_char, "MC Fraction of Cross Sections",    X_axis_char,
                           Y_axis_char,  "MC Fraction of Cross Sections");

PlotFractionofEvents2D_ProjX(CrossSection_map_tracker[True_crosssection], mcHists_Breakdown_input,
                              Helium9_colorScheme,"Fraction per Bin" ,
                              "Fraction Total",
                              pdf_char, "MC Fraction of Cross Sections",    Y_axis_char,
                              X_axis_char,  "MC Fraction of Cross Sections");







bool DoRatio= true;
      Draw_2D_Panel_MC_andData_frompointer_DISbreakdown(CrossSection_map_tracker[Data_crosssection], CrossSection_map_tracker[True_crosssection],
        CrossSection_map_tracker[True_crosssection_interaction_Elastic],
        CrossSection_map_tracker[True_crosssection_interaction_HeavierRes] ,
        CrossSection_map_tracker[True_crosssection_interaction_DeltaRes]  ,
        CrossSection_map_tracker[True_crosssection_interaction_2p2h] ,
        CrossSection_map_tracker[True_crosssection_interaction_DISSIS] ,
         CrossSection_map_tracker[True_crosssection_interaction_DISHard] ,
         CrossSection_map_tracker[True_crosssection_interaction_DISSoft] ,
         CrossSection_map_tracker[True_crosssection_interaction_other],
         CrossSection_map_tracker[True_crosssection_interaction_none],
         DataStat_SysError,
         false,
        title_Cross_Section_char, Y_axis,
        X_axis_char,  "Ratio to Nominal GENIE [MvnTune-v1]" , 2.4, 2.4, true,
        pdf_char,  false,  MakeXaxisLOG,
        .03, .03, false, DoRatio);



sprintf(title_char, "%s CrossSection Data Fractional Uncertainty ", title_base_char);
  DrawPanel_SystematicErrorPlots_ProjectionY(CrossSection_map_tracker[Data_crosssection], X_axis, Y_axis, title_char, pdf_char, .5, true, Print1Dplots );
  DrawPanel_SystematicErrorPlots_ProjectionX(CrossSection_map_tracker[Data_crosssection], X_axis, Y_axis, title_char, pdf_char, .5, true, Print1Dplots );

  DrawPanel_SystematicErrorPlots_ProjectionY_model(CrossSection_map_tracker[Data_crosssection], X_axis, Y_axis, title_char, pdf_char, .15, true, Print1Dplots );
  DrawPanel_SystematicErrorPlots_ProjectionX_model(CrossSection_map_tracker[Data_crosssection], X_axis, Y_axis, title_char, pdf_char, .15, true, Print1Dplots );

  //DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE FSI",           CrossSection_map_tracker[Data_crosssection], X_axis, Y_axis_char,  title_char, pdf_char, .13, true, false  );
  //DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "GENIE FSI",           CrossSection_map_tracker[Data_crosssection], Y_axis_char,X_axis,  title_char, pdf_char, .13, true, false  );
  //DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE Cross Section", CrossSection_map_tracker[Data_crosssection], X_axis, Y_axis_char,  title_char, pdf_char, .13, true, false  );
  //DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "GENIE Cross Section", CrossSection_map_tracker[Data_crosssection], Y_axis_char,X_axis,  title_char, pdf_char, .13, true, false  );
  //DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "Vertex Smearing",     CrossSection_map_tracker[Data_crosssection], X_axis, Y_axis_char,  title_char, pdf_char, .13, true, false  );
  //DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "Vertex Smearing",     CrossSection_map_tracker[Data_crosssection], Y_axis_char,X_axis,  title_char, pdf_char, .13, true, false  );
  //DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "2p2h RPA Mvn1Tune",   CrossSection_map_tracker[Data_crosssection], X_axis, Y_axis_char,  title_char, pdf_char, .13, true, false  );
  //DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "2p2h RPA Mvn1Tune",   CrossSection_map_tracker[Data_crosssection], Y_axis_char,X_axis,  title_char, pdf_char, .13, true, false  );
  //DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "Beam Angle",          CrossSection_map_tracker[Data_crosssection], X_axis, Y_axis_char,  title_char, pdf_char, .13, true, false  );
  //DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "Beam Angle",          CrossSection_map_tracker[Data_crosssection], Y_axis_char,X_axis,  title_char, pdf_char, .13, true, false  );
  //DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "Muon Reconstruction", CrossSection_map_tracker[Data_crosssection], X_axis, Y_axis_char,  title_char, pdf_char, .13, true, false  );
  //DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "Muon Reconstruction", CrossSection_map_tracker[Data_crosssection], Y_axis_char,X_axis,  title_char, pdf_char, .13, true, false  );

  Plot2D_FractionError_ProjY_Group(CrossSection_map_tracker[Data_crosssection],   pdf_char, "GENIE CrossSection QE",  Y_axis_char, "GENIE CrossSection QE",   X_axis_char,  .05, .03);
  Plot2D_FractionError_ProjY_Group(CrossSection_map_tracker[Data_crosssection],   pdf_char, "GENIE CrossSection 1#pi", Y_axis_char, "GENIE CrossSection 1#pi", X_axis_char,  .05, .03);
  Plot2D_FractionError_ProjY_Group(CrossSection_map_tracker[Data_crosssection],   pdf_char, "GENIE CrossSection DIS", Y_axis_char, "GENIE CrossSection DIS",  X_axis_char,  .05, .03);
  //Plot2D_FractionError_ProjY_Group(CrossSection_map_tracker[Data_crosssection],   pdf_char, "GENIE CrossSection NC",  Y_axis_char, "GENIE CrossSection NC",   X_axis_char,  .05, .03);
  Plot2D_FractionError_ProjY_Group(CrossSection_map_tracker[Data_crosssection],   pdf_char, "GENIE Nucleon FSI",      Y_axis_char, "GENIE Nucleon FSI",       X_axis_char,  .05, .03);
  Plot2D_FractionError_ProjY_Group(CrossSection_map_tracker[Data_crosssection],   pdf_char, "GENIE Pion FSI",         Y_axis_char, "GENIE Pion FSI",          X_axis_char,  .05, .03);
  //Plot2D_FractionError_ProjY_Group(CrossSection_map_tracker[Data_crosssection],   pdf_char, "Vertex Smearing",        Y_axis_char, "Vertex Smearing",         X_axis_char,  .05, .03, false);
  Plot2D_FractionError_ProjY_Group(CrossSection_map_tracker[Data_crosssection],   pdf_char, "Muon Reconstruction",    Y_axis_char, "Muon Reconstruction",     X_axis_char,  .05, .03, false);
  Plot2D_FractionError_ProjY_Group(CrossSection_map_tracker[Data_crosssection],   pdf_char, "Beam Angle",             Y_axis_char, "Beam Angle",              X_axis_char,  .05, .03, false);
  Plot2D_FractionError_ProjY_Group(CrossSection_map_tracker[Data_crosssection],   pdf_char, "2p2h RPA Mvn1Tune",             Y_axis_char, "2p2h RPA Mvn1Tune",              X_axis_char,  .05, .03, false);



  DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE FSI",           CrossSection_map_tracker[Data_crosssection], X_axis, Y_axis,  title_char, pdf_char, .05, true, false  );
  DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE Cross Section", CrossSection_map_tracker[Data_crosssection], X_axis, Y_axis,  title_char, pdf_char, .05, true, false  );
  DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE CrossSection QE", CrossSection_map_tracker[Data_crosssection], X_axis, Y_axis,  title_char, pdf_char, .05, true, false, true  );
  DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE CrossSection 1#pi", CrossSection_map_tracker[Data_crosssection], X_axis, Y_axis,  title_char, pdf_char,.05, true, false, true  );
  DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE CrossSection DIS", CrossSection_map_tracker[Data_crosssection], X_axis, Y_axis,  title_char, pdf_char,.05, true, false, true  );
  //DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE CrossSection NC", CrossSection_map_tracker[Data_crosssection], X_axis, Y_axis,  title_char, pdf_char, .05, true, false, true  );
  DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE Nucleon FSI", CrossSection_map_tracker[Data_crosssection], X_axis, Y_axis,  title_char, pdf_char,     .05, true, false, true  );
  DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE Pion FSI",      CrossSection_map_tracker[Data_crosssection], X_axis, Y_axis,  title_char, pdf_char,        .05, true, false, true  );
  //DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "Vertex Smearing",     CrossSection_map_tracker[Data_crosssection], X_axis, Y_axis,  title_char, pdf_char, .05, true, false  );
  DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "2p2h RPA Mvn1Tune",   CrossSection_map_tracker[Data_crosssection], X_axis, Y_axis,  title_char, pdf_char, .05, true, false  );
  DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "Beam Angle",          CrossSection_map_tracker[Data_crosssection], X_axis, Y_axis,  title_char, pdf_char, .05, true, false  );
  DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "Muon Reconstruction", CrossSection_map_tracker[Data_crosssection], X_axis, Y_axis,  title_char, pdf_char, .05, true, false  );
  DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "Flux", CrossSection_map_tracker[Data_crosssection], X_axis, Y_axis,  title_char, pdf_char, .05, true, false  );


  Plot2D_FractionError_ProjX_Group(CrossSection_map_tracker[Data_crosssection],   pdf_char, "GENIE CrossSection QE", X_axis_char, "GENIE CrossSection QE", Y_axis_char,  .05, .03);
  Plot2D_FractionError_ProjX_Group(CrossSection_map_tracker[Data_crosssection],   pdf_char, "GENIE CrossSection 1#pi", X_axis_char, "GENIE CrossSection 1#pi", Y_axis_char,  .05, .03);
  Plot2D_FractionError_ProjX_Group(CrossSection_map_tracker[Data_crosssection],   pdf_char, "GENIE CrossSection DIS", X_axis_char, "GENIE CrossSection DIS", Y_axis_char,  .05, .03);
  //Plot2D_FractionError_ProjX_Group(CrossSection_map_tracker[Data_crosssection],   pdf_char, "GENIE CrossSection NC", X_axis_char, "GENIE CrossSection NC", Y_axis_char,  .05, .03);
  Plot2D_FractionError_ProjX_Group(CrossSection_map_tracker[Data_crosssection],   pdf_char, "GENIE Nucleon FSI", X_axis_char, "GENIE Nucleon FSI", Y_axis_char,  .05, .03);
  Plot2D_FractionError_ProjX_Group(CrossSection_map_tracker[Data_crosssection],   pdf_char, "GENIE Pion FSI", X_axis_char, "GENIE Pion FSI", Y_axis_char,  .05, .03);

  //Plot2D_FractionError_ProjX_Group(CrossSection_map_tracker[Data_crosssection],   pdf_char, "Vertex Smearing", X_axis_char, "Vertex Smearing", Y_axis_char,  .05, .03, false);
  Plot2D_FractionError_ProjX_Group(CrossSection_map_tracker[Data_crosssection],   pdf_char, "Muon Reconstruction", X_axis_char, "Muon Reconstruction", Y_axis_char,  .05, .03, false);
  Plot2D_FractionError_ProjX_Group(CrossSection_map_tracker[Data_crosssection],   pdf_char, "Beam Angle", X_axis_char, "Beam Angle", Y_axis_char,  .05, .03, false);
  Plot2D_FractionError_ProjX_Group(CrossSection_map_tracker[Data_crosssection],   pdf_char, "2p2h RPA Mvn1Tune", X_axis_char, "2p2h RPA Mvn1Tune", Y_axis_char,  .05, .03, false);



  DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "GENIE FSI",           CrossSection_map_tracker[Data_crosssection], Y_axis, X_axis,  title_char, pdf_char, .05, true, false  );
  DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "GENIE Cross Section", CrossSection_map_tracker[Data_crosssection], Y_axis, X_axis,  title_char, pdf_char, .05, true, false  );
  DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "GENIE CrossSection QE", CrossSection_map_tracker[Data_crosssection], Y_axis, X_axis,  title_char, pdf_char, .05, true, false, true  );
  DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "GENIE CrossSection 1#pi", CrossSection_map_tracker[Data_crosssection], Y_axis, X_axis,  title_char, pdf_char, .05, true, false, true  );
  DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "GENIE CrossSection DIS", CrossSection_map_tracker[Data_crosssection], Y_axis, X_axis,  title_char, pdf_char, .05, true, false, true  );
  //DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "GENIE CrossSection NC", CrossSection_map_tracker[Data_crosssection], Y_axis, X_axis,  title_char, pdf_char, .05, true, false, true  );
  DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "GENIE Nucleon FSI", CrossSection_map_tracker[Data_crosssection], Y_axis, X_axis,  title_char, pdf_char, .05, true, false, true  );
  DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "GENIE Pion FSI", CrossSection_map_tracker[Data_crosssection], Y_axis, X_axis,  title_char, pdf_char, .05, true, false, true  );
  //DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "Vertex Smearing",     CrossSection_map_tracker[Data_crosssection], Y_axis, X_axis,  title_char, pdf_char, .05, true, false  );
  DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "2p2h RPA Mvn1Tune",   CrossSection_map_tracker[Data_crosssection], Y_axis, X_axis,  title_char, pdf_char, .05, true, false  );
  DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "Beam Angle",          CrossSection_map_tracker[Data_crosssection], Y_axis, X_axis,  title_char, pdf_char, .05, true, false  );
  DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "Muon Reconstruction", CrossSection_map_tracker[Data_crosssection], Y_axis, X_axis,  title_char, pdf_char, .05, true, false  );
  DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "Flux", CrossSection_map_tracker[Data_crosssection], Y_axis, X_axis,  title_char, pdf_char, .05, true, false  );


Plot2D_FractionError_ProjY(CrossSection_map_tracker[Data_crosssection], pdf_char, title_char,  Y_axis_char, X_axis_char, .15,.03);
Plot2D_FractionError_ProjX(CrossSection_map_tracker[Data_crosssection], pdf_char, title_char,  X_axis_char, Y_axis_char, .15,.025);

sprintf(title_char, "%s CrossSection True Model Fractional Uncertainty ", title_base_char);
Plot2D_FractionError_ProjY(CrossSection_map_tracker[True_crosssection], pdf_char, title_char,  Y_axis_char, X_axis_char, .15,.03);
Plot2D_FractionError_ProjX(CrossSection_map_tracker[True_crosssection], pdf_char, title_char,  X_axis_char, Y_axis_char, .15,.025);



  //Draw_2D_Panel_MC_andData_frompointer(CrossSection_map_tracker[Data_crosssection], CrossSection_map_tracker[True_crosssection],
  //  hist_Stack, title_Cross_Section_char, X_axis, Y_axis, crossSection_z_axis_char , 1, 1, pdf_char, doBinwidth,  MakeXaxisLOG,
  //    .03, .03 );

//
//(MnvH2D *hist_Data, MnvH2D *hist_MC,
//  PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type> hist_Stack,
//  char *histotitle, std::string xaxislabel,
//   std::string yaxislabel,const char *Zaxislabel , double max_x, double max_y,
//    char *pdf_label, bool doBinwidth, bool MakeXaxisLOG,
//    double x_projectionTxtsize, double y_projectionTxtsize )

//Draw2D_Panel_CV_SystematicErrFromPointer(CrossSection_map_tracker[Data_signal], CrossSection_map_tracker[Data_signal],Playlist_name  ,
//  "F-E", plot,
//  pdf_char, title_Cross_Section_char, X_axis_char, Y_axis_char,
//  crossSection_z_axis_char, doBinwidth, MakeXaxisLOG,
//  15, 15, .03, .03, chisqrt, ndf );
std::string crossSectionRatio_Z_axis =  "#frac{#partial^{2} #sigma^{He}}{#partial " + GetMuon2DVar_XaxisTitle_noUntils(MuonVar) + " #partial"+ GetMuon2DVar_YaxisTitle_noUntils(MuonVar) +  " } / " "#frac{#partial^{2} #sigma^{CH}}{#partial " + GetMuon2DVar_XaxisTitle_noUntils(MuonVar) + " #partial " + GetMuon2DVar_YaxisTitle_noUntils(MuonVar) + "}";
char crossSectionRatio_Z_axis_char[crossSectionRatio_Z_axis.length()+1];
strcpy(crossSectionRatio_Z_axis_char, crossSectionRatio_Z_axis.c_str());
title_Cross_Section = title_base + " Cross Section Ratio";

char title_Ratio_Cross_Section_char[title_Cross_Section.length()+1];
strcpy(title_Ratio_Cross_Section_char,title_Cross_Section.c_str());

title_Cross_Section = title_base + " Cross Section Ratio Daisy Corrected ";
char title_Ratio_Cross_Section_Daisy_char[title_Cross_Section.length()+1];
strcpy(title_Ratio_Cross_Section_Daisy_char,title_Cross_Section.c_str());

//CrossSection_map_tracker[Data_crosssection]->Scale(POT_Ratio);
//CrossSection_map_tracker[True_crosssection]->Scale(POT_Ratio);
MnvH2D* CrossSection_map_helium_clone = (MnvH2D*)CrossSection_map_helium[Data_crosssection]->Clone("CrossSection_map_helium_clone");
MnvH2D* CrossSection_map_helium_clone2 = (MnvH2D*)CrossSection_map_helium[Data_crosssection]->Clone("CrossSection_map_helium_clone2");

//Daisy_correct_CrossSection->Scale(POT_Ratio);


CrossSection_map_helium_clone->Divide(CrossSection_map_helium_clone, CrossSection_map_tracker[Data_crosssection]);
CrossSection_map_helium[Data_crosssection]->Divide(CrossSection_map_helium[Data_crosssection],CrossSection_map_tracker[Data_crosssection]);



CrossSection_map_helium[True_crosssection]->Divide(CrossSection_map_helium[True_crosssection],CrossSection_map_tracker[True_crosssection]);
CrossSection_map_helium_clone2->Divide(CrossSection_map_helium_clone2, Daisy_correct_CrossSection);

//CrossSection_map_tracker[Data_crosssection]->Divide(CrossSection_map_tracker[Data_crosssection],CrossSection_map_helium[Data_crosssection]);
//CrossSection_map_tracker[True_crosssection]->Divide(CrossSection_map_tracker[True_crosssection],CrossSection_map_helium[True_crosssection]);


//PlotDataMC_ErrorBand2D_ProjY(CrossSection_map_helium_clone, CrossSection_map_helium[True_crosssection],
//  pdf_char, title_Ratio_Cross_Section_char ,  Y_axis_char, X_axis_char,   crossSectionRatio_Z_axis_char,
//  4, true,  true, XMultipliers,
//  true , true , DontdoBinwidth,  false, .03);
//
//  PlotDataMC_ErrorBand2D_ProjX(CrossSection_map_helium_clone, CrossSection_map_helium[True_crosssection],
//    pdf_char, title_Ratio_Cross_Section_char ,  X_axis_char, Y_axis_char,   crossSectionRatio_Z_axis_char,
//    4, true,  true, XMultipliers,
//    true , true , DontdoBinwidth,  false, .03);


    PlotDataMC_ErrorBand2D_ProjY(CrossSection_map_helium[Data_crosssection], CrossSection_map_helium[True_crosssection],
      pdf_char, title_Ratio_Cross_Section_char ,  Y_axis_char, X_axis_char,   crossSectionRatio_Z_axis_char,
      2., true,  true, XMultipliers,
      true , true , DontdoBinwidth,  false, .03);

      PlotDataMC_ErrorBand2D_ProjX(CrossSection_map_helium[Data_crosssection], CrossSection_map_helium[True_crosssection],
        pdf_char, title_Ratio_Cross_Section_char ,  X_axis_char, Y_axis_char,   crossSectionRatio_Z_axis_char,
        2.5, true,  true, XMultipliers,
        true , true , DontdoBinwidth,  false, .03);



            PlotDataMC_ErrorBand2D_ProjY(CrossSection_map_helium_clone2, CrossSection_map_helium[True_crosssection],
              pdf_char, title_Ratio_Cross_Section_Daisy_char ,  Y_axis_char, X_axis_char,   crossSectionRatio_Z_axis_char,
              2., true,  true, XMultipliers,
              true , true , DontdoBinwidth,  false, .03);

              PlotDataMC_ErrorBand2D_ProjX(CrossSection_map_helium_clone2, CrossSection_map_helium[True_crosssection],
                pdf_char, title_Ratio_Cross_Section_Daisy_char ,  X_axis_char, Y_axis_char,   crossSectionRatio_Z_axis_char,
                2.5, true,  true, XMultipliers,
                true , true , DontdoBinwidth,  false, .03);

std::cout<<"Made CrossSection_map[dom_Eff]" << std::endl;


return;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string generateLatexFrame(std::vector<int> pageNumbers,
   std::string presentationTitle, std::string plotsFileName, int daisyNumber)
   {
    std::stringstream latexStream;
    std::string daisyName = "Daisy" + std::to_string(daisyNumber);
    latexStream << "\\begin{frame}\n";
    latexStream << "  \\frametitle{" << presentationTitle << "  Daisy : " << daisyNumber << "}\n\n";
    latexStream << "  \\begin{tikzpicture}[remember picture,overlay]\n";
    latexStream << "    \\node[anchor=north east,inner sep=0, yshift=-1cm] at (current page.north east) {\\includegraphics[width=2.5cm]{" << daisyName << ".png}};\n";
    latexStream << "  \\end{tikzpicture}\n";
    latexStream << "  \\vspace{2.5cm}\n";
    latexStream << "  \\begin{tabular}{cccc}\n";
    latexStream << "    \\includegraphics[scale=0.18, page=" << pageNumbers[0] << "]{" << plotsFileName << "} &\n";
    latexStream << "    \\includegraphics[scale=0.22, page=" << pageNumbers[1] << "]{" << plotsFileName << "} &\n";
    latexStream << "    \\includegraphics[scale=0.18, page=" << pageNumbers[2] << "]{" << plotsFileName << "}  \\\\\n";
    latexStream << "    \\hspace{-1cm}\n";
    latexStream << "    \\includegraphics[scale=0.18, page=" << pageNumbers[3] << "]{" << plotsFileName << "} &\n";
    latexStream << "    \\hspace{-2cm}\n";
    latexStream << "    \\includegraphics[scale=0.18, page=" << pageNumbers[4] << "]{" << plotsFileName << "}  &\n";
    latexStream << "    \\hspace{-2cm}\n";
    latexStream << "    \\includegraphics[scale=0.18, page=" << pageNumbers[5] << "]{" << plotsFileName << "} &\n";
    latexStream << "    \\hspace{-1.5cm}\n";
    latexStream << "    \\includegraphics[scale=0.18, page=" << pageNumbers[6] << "]{" << plotsFileName << "}\n";
    latexStream << "  \\end{tabular}\n";
    latexStream << "\\end{frame}";

    return latexStream.str();
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::vector<int> generateNumberPattern(int startingValue, std::vector<int>inputPattern)
{
    std::vector<int> pattern;
    int currentNumber = startingValue;
    pattern.push_back(currentNumber);

    for(auto number : inputPattern){
      int input = currentNumber + number;
      pattern.push_back(input);
    }

    return pattern;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void GenerateLatex_textfile(char *FileName, std::vector<int> StartingPages,
   std::string MuonName, std::string pdfname)
   {

  std::ofstream outfile (FileName);
std::vector<int> PagePattern{2,3,6,9,12,15};

  outfile << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    outfile << "%%%%%%%%%%%%% Daisy Sides for " <<MuonName  << "%%%%" << std::endl;
  outfile << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
int count = 0;
  for(auto StartPage : StartingPages){

    outfile << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    outfile << "%%%%%% Slide Number: "<<  count+1   <<"%%%%%%%%" << std::endl;
    outfile << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
  outfile << " " << std::endl;
  outfile << " " << std::endl;
    auto pages = generateNumberPattern(StartPage, PagePattern);
    std::string sidetitle = MuonName + " Daisy : " + std::to_string(count);
    auto Slide_string = generateLatexFrame(pages,sidetitle  ,  pdfname, count);
    outfile << Slide_string<< std::endl;
  outfile << " " << std::endl;
  outfile << " " << std::endl;
outfile << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
outfile << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    count++;
  }


  outfile.close();



return;

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string generateLatexFrame_2DEffLayout(
   std::string pdfName_input,  std::vector<int>& pageNumbers, int titleNumber)
  {std::string pdfName = pdfName_input + ".pdf";
    std::string daisyName = "Daisy" + std::to_string(titleNumber);
    std::string title = "Daisy:" + std::to_string(titleNumber);
    std::string latexCode = "\\begin{frame}\n";
    latexCode += "  \\frametitle{$P_{T}$ vs $P_{Z}$  " + title + "}\n";
    latexCode += "  \\vspace{-1.5cm}\n";
    latexCode += "  \\begin{tikzpicture}[remember picture,overlay]\n";
    latexCode += "    \\node[anchor=north east,inner sep=0, yshift=-1cm] at (current page.north east) {\\includegraphics[width=2.0cm]{" + daisyName + ".png}};\n";
    latexCode += "  \\end{tikzpicture}\n";
    latexCode += "  \\begin{tabular}{ccc}\n";
    latexCode += "  \\hspace{-1cm}\n";
    latexCode += "    \\includegraphics[scale=0.2, page=" + std::to_string(pageNumbers[0]) + "]{" + pdfName + "} &\n";
    latexCode += "    \\hspace{-2.5cm}  \n";
    latexCode += "    \\includegraphics[scale=0.22, page=" + std::to_string(pageNumbers[1]) + "]{" + pdfName + "} &\n";
    latexCode += "    \\hspace{-5cm}  \n";
    latexCode += "    \\includegraphics[scale=0.22, page=" + std::to_string(pageNumbers[2]) + "]{" + pdfName + "} \n";
    latexCode += "    \\\\\n";
    latexCode += "    \\includegraphics[scale=0.22, page=" + std::to_string(pageNumbers[3]) + "]{" + pdfName + "} &\n";
    latexCode += "    \\includegraphics[scale=0.25, page=" + std::to_string(pageNumbers[4]) + "]{" + pdfName + "} &\n";
    latexCode += "    \\includegraphics[scale=0.25, page=" + std::to_string(pageNumbers[5]) + "]{" + pdfName + "} &\n";
    latexCode += "  \\end{tabular}\n";
    latexCode += "\\end{frame}\n";

    return latexCode;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

void GenerateLatex_textfile_2DEff(char *FileName,
   std::vector<int> StartingPages,
   std::string MuonName, std::string pdfname)
   {

     std::ofstream outfile (FileName);
     std::vector<int> PagePattern{3,4,5,6,7};

     outfile << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
     outfile << "%%%%%%%%%%%%% Daisy Sides for " <<MuonName  << "%%%%" << std::endl;
     outfile << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
     int count = 0;
     for(auto StartPage : StartingPages){

       outfile << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
       outfile << "%%%%%% Slide Number: "<<  count+1   <<"%%%%%%%%" << std::endl;
       outfile << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
       outfile << " " << std::endl;
       outfile << " " << std::endl;
       auto pages = generateNumberPattern(StartPage, PagePattern);
       std::string sidetitle = MuonName + " Daisy : " + std::to_string(count);
       auto Slide_string = generateLatexFrame_2DEffLayout(pdfname, pages, count);
       outfile << Slide_string<< std::endl;
       outfile << " " << std::endl;
       outfile << " " << std::endl;
       outfile << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
       outfile << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
       count++;
     }


     outfile.close();



     return;

   }
   ////////////////////////////////////////////////////////////////////////////////
   //
   ////////////////////////////////////////////////////////////////////////////////
std::string generateLatexFrame_2D_Daisy(
  std::string& pdfName, std::vector<int>& pageNumbers, int titleNumber)
  {
    std::string title = "Daisy:" + std::to_string(titleNumber);
    std::string daisyName = "Daisy" + std::to_string(titleNumber);
    std::string latexCode = "\\begin{frame}\n";
    latexCode += "  \\frametitle{$P_{T}$ vs $P_{Z}$  " + title + "}\n";
    latexCode += "  \\vspace{-1.5cm}\n";
    latexCode += "  \\begin{tikzpicture}[remember picture,overlay]\n";
    latexCode += "    \\node[anchor=north east,inner sep=0, yshift=-.2cm] at (current page.north east) {\\includegraphics[width=1.25cm]{" + daisyName + ".png}};\n";
    latexCode += "  \\end{tikzpicture}\n";
    latexCode += "  \\begin{tabular}{ccccc}\n";
    latexCode += "     \\hspace{-.5cm}\n";
    for (int i = 0; i < pageNumbers.size(); ++i) {
      latexCode += "    \\includegraphics[scale=0.16, page=" + std::to_string(pageNumbers[i]) + "]{" + pdfName + "} &\n";
      if ((i + 1) % 5 == 0)
      latexCode += "    \\\\\n";
      latexCode += "      \\hspace{-.5cm}\n";
    }
    latexCode += "  \\end{tabular}\n";
    latexCode += "\\end{frame}\n";

    return latexCode;
  }
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void GenerateLatex_textfile_2D_Daisy(char *FileName,
  std::vector<int> StartingPages,
  std::string MuonName, std::string pdfname)
  {

    std::ofstream outfile (FileName);
    std::vector<int> PagePattern{2,4,6,8,1,3,5,7,9};

    outfile << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    outfile << "%%%%%%%%%%%%% Daisy Sides for " <<MuonName  << "%%%%" << std::endl;
    outfile << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    int count = 0;
    for(auto StartPage : StartingPages){

      outfile << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
      outfile << "%%%%%% Slide Number: "<<  count+1   <<"%%%%%%%%" << std::endl;
      outfile << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
      outfile << " " << std::endl;
      outfile << " " << std::endl;
      auto pages = generateNumberPattern(StartPage, PagePattern);
      std::string sidetitle = MuonName + " Daisy : " + std::to_string(count);
      auto Slide_string = generateLatexFrame_2D_Daisy(pdfname, pages, count);
      outfile << Slide_string<< std::endl;
      outfile << " " << std::endl;
      outfile << " " << std::endl;
      outfile << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
      outfile << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
      count++;
    }


    outfile.close();



    return;

  }
