#include "CryoTank_EmptyHelium_Fit.h"
//////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
OffSet1DMap Constuct_OffSet1DMap(TFile *PlaylistME_Tfile_MC,TFile *PlaylistME_Tfile_Data,
   const char *hist_MCname, const char *hist_DataName, char *Title, ME_helium_Playlists playlist, VertexOffSet_Map OffSetMap,
 int NBinZ, int NBinR );

 OffSet2DMap Constuct_OffSet2DMap(TFile *PlaylistME_Tfile_MC,TFile *PlaylistME_Tfile_Data,
    const char *hist_MCname, const char *hist_DataName, char *Title, ME_helium_Playlists playlist, VertexOffSet_Map OffSetMap,
  int NBinZ, int NBinR );


std::vector<OffSet1DMap> Constuct_OffSet1DMap_Vector(ME_playlist_TFileMAP InputTFileMap, ME_playlist_TFileMAP InputTFileData,
                                                  const char *hist_MCname, const char *hist_DataName,char *Title, VertexOffSet_Map OffSetMap,
                                                  int NBinZ, int NBinR );
std::vector<OffSet2DMap> Constuct_OffSet2DMap_Vector(ME_playlist_TFileMAP InputTFileMap, ME_playlist_TFileMAP InputTFileData,
  const char *hist_MCname, const char *hist_DataName,char *Title, VertexOffSet_Map OffSetMap,
  int NBinZ, int NBinR );

void ScaleData_OffSet1DMap(OffSet1DMap &inputMap, double ScaleData);
void ScaleData_OffSet2DMap(OffSet2DMap &inputMap, double ScaleData);
void ScaleMC_OffSet1DMap(OffSet1DMap &inputMap , double ScaleMC);
void ScaleMC_OffSet2DMap(OffSet2DMap &inputMap , double ScaleMC);
OffSet1DMap Combined_OffSet1DMap_Vector(std::vector<OffSet1DMap> input, ME_helium_Playlists ADDtothisHis ,const char* name, int NBinZ, int NBinR , bool isFull );
OffSet2DMap Combined_OffSet2DMap_Vector(std::vector<OffSet2DMap> input, ME_helium_Playlists ADDtothisHis ,const char* name, int NBinZ, int NBinR , bool isFull );


void DrawSinglePlaylist_OffSet1DPlot(TCanvas *can, MnvPlotter *plot, OffSet1DMap InputMap, std::string units, std::string pdf_label, std::string pdf_Chisqrlabel, char* hist_title,
   char *xaxislabel, char* yaxislabel, Pot_MapList Pot_MC , Pot_MapList Pot_Data, double Ymax);

void DrawSinglePlaylist_OffSet1DPlot_Combined(TCanvas *can, MnvPlotter *plot, OffSet1DMap InputMap, std::string units, std::string pdf_label, std::string pdf_Chisqrlabel, char* hist_title,
  char *xaxislabel, char* yaxislabel, double CombinedDataPOT_ScaleEMPTY , double CombinedMCPOT_ScaleEMPTY ,std::string playlist_name, double Ymax);

void Draw_Single_playlist_1D_VertexShifts(ME_playlist_TFileMAP FullMCMap,     Pot_MapList FullMC_scalerMap,
                          ME_playlist_TFileMAP EmptyMCMap,    Pot_MapList EmptyMC_scalerMap,
                          ME_playlist_TFileMAP FullDataMap,   Pot_MapList FullData_scalerMap,
                          ME_playlist_TFileMAP EmptyDataMap,  Pot_MapList EmptyData_scalerMap,
   const char *histoName_MC, const char *histoName_data, std::string units, std::string pdf_label,std::string pdf_Chisqrlabel, char* hist_title,
   char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG, bool MakeYaxisLOG, bool DrawallErrorGroups,
   double NegZ_offset, double PosZ_offset, int NumZSteps, double NegR_offset, double PosR_offset,  int NumRSteps, double Empty_yMax, TCanvas *can, MnvPlotter *plot
 );



void Clone_OffSet1DMap(MnvH1D_Map &inputMap_Clone , MnvH1D_Map inputMap_input);
void Clone_OffSet2DMap(MnvH2D_Map &inputMap_Clone , MnvH2D_Map inputMap_input);



  void AppendtoLatex_FiveFigures(std::string output_name ,  std::string pdf_name_CV, int Figure_1_page_number, int Figure_2_page_number,
        int Figure_3_page_number, int Figure_5_page_number, int Figure_6_page_number, char *slideTitle);

std::vector<CryoVertex> GetCryoVertexVaribles_All();

///Gobal Varibles
//Global histograms because TMinuit needs them global...
//Blob plots
const int nHistos =7;
TH1D h_Full[nHistos];//contains ALL the categorizations, including data
TH1D h_Empty[nHistos];//contains ALL the categorizations, including data

void Kin(bool &cutsOn, bool &my_norm, bool &my_debug, const char *userDir, int &Print_Systematics ) {
TH1::AddDirectory(false);
loadLibs();
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~       Starting Helium Fitter: Planning to ReWeight Al Events  ~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::vector<ME_helium_Playlists> GetPlayListVector_MC();
std::vector<ME_helium_Playlists> GetPlayListVector_DATA();
const std::vector< ME_helium_Playlists> kMEPlayList_Vector = GetPlayListVector_MC();
std::vector<ME_helium_Playlists> kPlayListVector_DATA =GetPlayListVector_DATA();
const std::vector<CryoVertex> kCryoVertexVaribles_vector = GetCryoVertexVaribles();
int N_Error_groups;
if(Print_Systematics==2 || Print_Systematics == 1) {N_Error_groups=0;}
else if (Print_Systematics==0){N_Error_groups=7;}
Pot_MapList POT_MC,POT_DATA;
Pot_MapStatusList POT_MC_Status, POT_DATA_Status;
TCanvas *can = new TCanvas("can");
MnvPlotter *mnv_plot = new MnvPlotter();
 char text_title_pdf1[2024];
 char text_title_pdf2[2024];
 char text_title_pdf3[2024];
 char text_title_pdf4[2024];
 char chisqrt_title_pdf1[2024];
 char chisqrt_title_pdf2[2024];
 char chisqrt_title_pdf3[2024];
 char chisqrt_title_pdf4[2024];

 char text_title_noshift_pdf1[2024];
 char text_title_noshift_pdf2[2024];
 char text_title_noshift_pdf3[2024];
 char text_title_noshift_pdf4[2024];



time_t now = time(0);
tm *ltm = localtime(&now);
char timeset[2024];
char timeset_nonstacks[2024];
std::string SysError_printLabel = PrintLabel_Systematics(Print_Systematics);
auto Playlist_names =  MakePlaylistString(kMEPlayList_Vector);
sprintf(timeset_nonstacks,"%i_%i_%i_%i_%s_%s", 1 + ltm->tm_mon,ltm->tm_mday, ltm->tm_hour,ltm->tm_min, SysError_printLabel.c_str(), Playlist_names.c_str());
sprintf(timeset, "%i_%i_%i_%i", 1 + ltm->tm_mon,ltm->tm_mday, ltm->tm_hour,ltm->tm_min);

sprintf(text_title_pdf1, "Plots_CryoVertex_Fitting_AllNuME_shiftedAll_Wgts_noFid_Covolution.pdf(" );
can -> Print(text_title_pdf1);
sprintf(text_title_pdf2, "Plots_CryoVertex_Fitting_AllNuME_shiftedAll_Wgts_noFid_Covolution.pdf" );
sprintf(text_title_pdf2, "Plots_CryoVertex_Fitting_AllNuME_shiftedAll_Wgts_noFid_Covolution.pdf" );
sprintf(text_title_pdf3, "Plots_CryoVertex_Fitting_AllNuME_shiftedAll_Wgts_noFid_Covolution.pdf)" );
sprintf(text_title_pdf4, "Plots_CryoVertex_Fitting_AllNuME_shiftedAll_Wgts_noFid_Covolution" );
std::string PDF_label(text_title_pdf4);

sprintf(text_title_noshift_pdf1, "Plots_CryoVertex_AllNuME_NOshifted_Fid.pdf(" );
can -> Print(text_title_noshift_pdf1);
sprintf(text_title_noshift_pdf3, "Plots_CryoVertex_AllNuME_NOshifted_Fid.pdf)" );


std::string PDF_label_noshift = "Plots_CryoVertex_AllNuME_NOshifted_Fid";
std::string PDF_label_withpdf(text_title_pdf2);

sprintf(chisqrt_title_pdf1, "Plots_CryoVertex_OffSet_ChiSqrt.pdf(" );
can -> Print(chisqrt_title_pdf1);
sprintf(chisqrt_title_pdf2, "Plots_CryoVertex_OffSet_ChiSqrt.pdf" );
sprintf(chisqrt_title_pdf2, "Plots_CryoVertex_OffSet_ChiSqrt.pdf" );
sprintf(chisqrt_title_pdf3, "Plots_CryoVertex_OffSet_ChiSqrt.pdf)" );
sprintf(chisqrt_title_pdf4, "Plots_CryoVertex_OffSet_ChiSqrt" );


ME_playlist_RootPathMAP MAP_RootPath_Empty_MC;
ME_playlist_RootPathMAP MAP_RootPath_Empty_MC_noshift;
ME_playlist_RootPathMAP MAP_RootPath_OtherEmpty_MC;
ME_playlist_RootPathMAP MAP_RootPath_Full_MC;
ME_playlist_RootPathMAP MAP_RootPath_Full_MC_noshift;


ME_playlist_RootPathMAP MAP_RootPath_Empty_DATA;
ME_playlist_RootPathMAP MAP_RootPath_Full_DATA;

std::vector<StackType> StackType_vector;

StackType_vector.push_back(kMaterial );
StackType_vector.push_back(kInteraction);
StackType_vector.push_back(kParticle);

/////////////////
/// MC
/////////////////
// Empty Playlist
/////////////////
/*
auto PlaylistME_1G_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1G_MC_All_SysErrorsOn_ThreeRegion_sideBand.root";
auto PlaylistME_1A_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1A_MC_All_SysErrorsOn_ThreeRegion_sideBand.root";
auto PlaylistME_1L_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1L_MC_All_SysErrorsOn_ThreeRegion_sideBand.root";
auto PlaylistME_1M_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1M_MC_All_SysErrorsOn_ThreeRegion_sideBand.root";
auto PlaylistME_1N_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1N_MC_All_SysErrorsOn_ThreeRegion_sideBand.root";
*/

auto PlaylistME_1G_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1G_MC_StatsONLYErrors_ThreeRegion_sideBandShift_Noshift_noWgts_NoFid_ShiftAll_Convolution.root";
auto PlaylistME_1A_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1A_MC_StatsONLYErrors_ThreeRegion_sideBandShift_Noshift_noWgts_NoFid_ShiftAll_Convolution.root";
auto PlaylistME_1L_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1L_MC_StatsONLYErrors_ThreeRegion_sideBandShift_Noshift_noWgts_NoFid_ShiftAll_Convolution.root";
auto PlaylistME_1M_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1M_MC_StatsONLYErrors_ThreeRegion_sideBandShift_Noshift_noWgts_NoFid_ShiftAll_Convolution.root";
auto PlaylistME_1N_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1N_MC_StatsONLYErrors_ThreeRegion_sideBandShift_Noshift_noWgts_NoFid_ShiftAll_Convolution.root";


auto PlaylistME_noshift_1G_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1G_MC_StatsONLYErrors_ThreeRegion_sideBandShift_Noshift_noWgts_Fid_ShiftAll.root";
auto PlaylistME_noshift_1A_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1A_MC_StatsONLYErrors_ThreeRegion_sideBandShift_Noshift_noWgts_Fid_ShiftAll.root";
auto PlaylistME_noshift_1L_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1L_MC_StatsONLYErrors_ThreeRegion_sideBandShift_Noshift_noWgts_Fid_ShiftAll.root";
auto PlaylistME_noshift_1M_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1M_MC_StatsONLYErrors_ThreeRegion_sideBandShift_Noshift_noWgts_Fid_ShiftAll.root";
auto PlaylistME_noshift_1N_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1N_MC_StatsONLYErrors_ThreeRegion_sideBandShift_Noshift_noWgts_Fid_ShiftAll.root";


//auto PlaylistME_1G_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1G_MC_StatsONLYErrors_ThreeRegion_sideBand_Noshift_nowgts_noFid.root";
//auto PlaylistME_1A_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1A_MC_StatsONLYErrors_ThreeRegion_sideBand_Noshift_nowgts_noFid.root";
//auto PlaylistME_1L_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1L_MC_StatsONLYErrors_ThreeRegion_sideBand_Noshift_nowgts_noFid.root";
//auto PlaylistME_1M_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1M_MC_StatsONLYErrors_ThreeRegion_sideBand_Noshift_nowgts_noFid.root";
//auto PlaylistME_1N_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1N_MC_StatsONLYErrors_ThreeRegion_sideBand_Noshift_nowgts_noFid.root";



///minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1L_MC_All_SysErrorsOn_ThreeRegion_sideBand.root

MAP_RootPath_Empty_MC.insert(std::make_pair(kMEPlayList_Vector.at(0), PlaylistME_1G_MC_path));
MAP_RootPath_Empty_MC.insert(std::make_pair(kMEPlayList_Vector.at(1), PlaylistME_1A_MC_path));
MAP_RootPath_Empty_MC.insert(std::make_pair(kMEPlayList_Vector.at(2), PlaylistME_1L_MC_path));
MAP_RootPath_Empty_MC.insert(std::make_pair(kMEPlayList_Vector.at(3), PlaylistME_1M_MC_path));
MAP_RootPath_Empty_MC.insert(std::make_pair(kMEPlayList_Vector.at(4), PlaylistME_1N_MC_path));

MAP_RootPath_Empty_MC_noshift.insert(std::make_pair(kMEPlayList_Vector.at(0), PlaylistME_noshift_1G_MC_path));
MAP_RootPath_Empty_MC_noshift.insert(std::make_pair(kMEPlayList_Vector.at(1), PlaylistME_noshift_1A_MC_path));
MAP_RootPath_Empty_MC_noshift.insert(std::make_pair(kMEPlayList_Vector.at(2), PlaylistME_noshift_1L_MC_path));
MAP_RootPath_Empty_MC_noshift.insert(std::make_pair(kMEPlayList_Vector.at(3), PlaylistME_noshift_1M_MC_path));
MAP_RootPath_Empty_MC_noshift.insert(std::make_pair(kMEPlayList_Vector.at(4), PlaylistME_noshift_1N_MC_path));

////////
//Full//
////////
auto PlaylistME_1P_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1P_MC_StatsONLYErrors_ThreeRegion_sideBandShift_Noshift_noWgts_NoFid_ShiftAll_Convolution.root";
auto PlaylistME_1C_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1C_MC_StatsONLYErrors_ThreeRegion_sideBandShift_Noshift_noWgts_NoFid_ShiftAll_Convolution.root";
auto PlaylistME_1D_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1D_MC_StatsONLYErrors_ThreeRegion_sideBandShift_Noshift_noWgts_NoFid_ShiftAll_Convolution.root";
auto PlaylistME_1F_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1F_MC_StatsONLYErrors_ThreeRegion_sideBandShift_Noshift_noWgts_NoFid_ShiftAll_Convolution.root";
auto PlaylistME_1E_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1E_MC_StatsONLYErrors_ThreeRegion_sideBandShift_Noshift_noWgts_NoFid_ShiftAll_Convolution.root";

auto PlaylistME_noshift_1P_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1P_MC_StatsONLYErrors_ThreeRegion_sideBandShift_Noshift_noWgts_Fid_ShiftAll.root";
auto PlaylistME_noshift_1C_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1C_MC_StatsONLYErrors_ThreeRegion_sideBandShift_Noshift_noWgts_Fid_ShiftAll.root";
auto PlaylistME_noshift_1D_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1D_MC_StatsONLYErrors_ThreeRegion_sideBandShift_Noshift_noWgts_Fid_ShiftAll.root";
auto PlaylistME_noshift_1F_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1F_MC_StatsONLYErrors_ThreeRegion_sideBandShift_Noshift_noWgts_Fid_ShiftAll.root";
auto PlaylistME_noshift_1E_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1E_MC_StatsONLYErrors_ThreeRegion_sideBandShift_Noshift_noWgts_Fid_ShiftAll.root";



MAP_RootPath_Full_MC.insert(std::make_pair(kMEPlayList_Vector.at(5), PlaylistME_1P_MC_path));
MAP_RootPath_Full_MC.insert(std::make_pair(kMEPlayList_Vector.at(6), PlaylistME_1C_MC_path));
MAP_RootPath_Full_MC.insert(std::make_pair(kMEPlayList_Vector.at(7), PlaylistME_1D_MC_path));
MAP_RootPath_Full_MC.insert(std::make_pair(kMEPlayList_Vector.at(8), PlaylistME_1F_MC_path));
MAP_RootPath_Full_MC.insert(std::make_pair(kMEPlayList_Vector.at(9), PlaylistME_1E_MC_path));

MAP_RootPath_Full_MC_noshift.insert(std::make_pair(kMEPlayList_Vector.at(5), PlaylistME_noshift_1P_MC_path));
MAP_RootPath_Full_MC_noshift.insert(std::make_pair(kMEPlayList_Vector.at(6), PlaylistME_noshift_1C_MC_path));
MAP_RootPath_Full_MC_noshift.insert(std::make_pair(kMEPlayList_Vector.at(7), PlaylistME_noshift_1D_MC_path));
MAP_RootPath_Full_MC_noshift.insert(std::make_pair(kMEPlayList_Vector.at(8), PlaylistME_noshift_1F_MC_path));
MAP_RootPath_Full_MC_noshift.insert(std::make_pair(kMEPlayList_Vector.at(9), PlaylistME_noshift_1E_MC_path));


/////////////////
/// Data
/////////////////
/////////////////
// Empty
/////////////////
auto PlaylistME_1G_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1G_Data_SideBand_NoFid.root";
auto PlaylistME_1A_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1A_Data_SideBand_NoFid.root";
auto PlaylistME_1L_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1L_Data_SideBand_NoFid.root";
auto PlaylistME_1M_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1M_Data_SideBand_NoFid.root";
auto PlaylistME_1N_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1N_Data_SideBand_NoFid.root";
//////////////////
MAP_RootPath_Empty_DATA.insert(std::make_pair(kMEPlayList_Vector.at(0), PlaylistME_1G_Data_path));
MAP_RootPath_Empty_DATA.insert(std::make_pair(kMEPlayList_Vector.at(1), PlaylistME_1A_Data_path));
MAP_RootPath_Empty_DATA.insert(std::make_pair(kMEPlayList_Vector.at(2), PlaylistME_1L_Data_path));
MAP_RootPath_Empty_DATA.insert(std::make_pair(kMEPlayList_Vector.at(3), PlaylistME_1M_Data_path));
MAP_RootPath_Empty_DATA.insert(std::make_pair(kMEPlayList_Vector.at(4), PlaylistME_1N_Data_path));
//////////////
//Full
//////////////
auto PlaylistME_1P_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1P_Data_SideBand_NoFid.root";
auto PlaylistME_1C_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1C_Data_SideBand_NoFid.root";
auto PlaylistME_1D_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1D_Data_SideBand_NoFid.root";
auto PlaylistME_1F_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1F_Data_SideBand_NoFid.root";
auto PlaylistME_1E_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1E_Data_SideBand_NoFid.root";
///minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1A_MC_StatsONLYErrors_OFFSET_Alwgt.root
////////////////////
MAP_RootPath_Full_DATA.insert(std::make_pair(kMEPlayList_Vector.at(5), PlaylistME_1P_Data_path));
MAP_RootPath_Full_DATA.insert(std::make_pair(kMEPlayList_Vector.at(6), PlaylistME_1C_Data_path));
MAP_RootPath_Full_DATA.insert(std::make_pair(kMEPlayList_Vector.at(7), PlaylistME_1D_Data_path));
MAP_RootPath_Full_DATA.insert(std::make_pair(kMEPlayList_Vector.at(8), PlaylistME_1F_Data_path));
MAP_RootPath_Full_DATA.insert(std::make_pair(kMEPlayList_Vector.at(9), PlaylistME_1E_Data_path));
////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////

Pot_MapList EmptyPOT_local_MC_MAP = Constuct_POT_playlistMap(MAP_RootPath_Empty_MC, true);
Pot_MapList FullPOT_local_MC_MAP  = Constuct_POT_playlistMap(MAP_RootPath_Full_MC, true);

Pot_MapList EmptyPOT_noshift_local_MC_MAP = Constuct_POT_playlistMap(MAP_RootPath_Empty_MC_noshift, true);
Pot_MapList FullPOT_noshift_local_MC_MAP  = Constuct_POT_playlistMap(MAP_RootPath_Full_MC_noshift, true);



Pot_MapList EmptyPOT_local_Data_MAP = Constuct_POT_playlistMap(MAP_RootPath_Empty_DATA, false);
Pot_MapList FullPOT_local_Data_MAP  = Constuct_POT_playlistMap(MAP_RootPath_Full_DATA, false);

//PlotUtils::POTCounter *PotCounter_Object; // unsure why the plotulits pot function isn't work need to revist

//Pot_MapList EmptyPOT_MC_MAP = Constuct_POT_playlistMap(PotCounter_Object, MAP_RootPath_OtherEmpty_MC);
//Pot_MapList FullPOT_MC_MAP = Constuct_POT_playlistMap(PotCounter_Object, MAP_RootPath_Full_MC);


PrintPot_MapList(EmptyPOT_local_MC_MAP, "EmptyPOT_local_MC_MAP"  );
PrintPot_MapList(FullPOT_local_MC_MAP, "FullPOT_local_MC_MAP"  );

PrintPot_MapList(EmptyPOT_local_Data_MAP, "EmptyPOT_local_Data_MAP"  );
PrintPot_MapList(FullPOT_local_Data_MAP, "FullPOT_local_Data_MAP"  );


Pot_MapList EmptyPOT_local_MC_ScaledMAP = POT_ScalersMap(EmptyPOT_local_MC_MAP ,FullPOT_local_Data_MAP[kMEPlayList_Vector.at(8)] );
Pot_MapList FullPOT_local_MC_ScaledMAP = POT_ScalersMap(FullPOT_local_MC_MAP ,FullPOT_local_Data_MAP[kMEPlayList_Vector.at(8)] );

Pot_MapList EmptyPOT_local_Data_ScaledMAP = POT_ScalersMap(EmptyPOT_local_Data_MAP ,FullPOT_local_Data_MAP[kMEPlayList_Vector.at(8)] );
Pot_MapList FullPOT_local_Data_ScaledMAP = POT_ScalersMap(FullPOT_local_Data_MAP ,FullPOT_local_Data_MAP[kMEPlayList_Vector.at(8)] );


PrintPot_MapList(EmptyPOT_local_MC_ScaledMAP, "EmptyPOT_local_MC_ScaledMAP"  );
PrintPot_MapList(FullPOT_local_MC_ScaledMAP, "FullPOT_local_MC_ScaledMAP"  );

PrintPot_MapList(EmptyPOT_local_Data_ScaledMAP, "EmptyPOT_local_Data_ScaledMAP"  );
PrintPot_MapList(FullPOT_local_Data_ScaledMAP, "FullPOT_local_Data_ScaledMAP"  );


ME_playlist_TFileMAP EmptyTFile_Map_MC;
ME_playlist_TFileMAP EmptyTFile_Map_MC_noshift;

TFile *PlaylistME_1G_TFile = new TFile(PlaylistME_1G_MC_path);
TFile *PlaylistME_1A_TFile = new TFile(PlaylistME_1A_MC_path);
TFile *PlaylistME_1L_TFile = new TFile(PlaylistME_1L_MC_path);
TFile *PlaylistME_1M_TFile = new TFile(PlaylistME_1M_MC_path);
TFile *PlaylistME_1N_TFile = new TFile(PlaylistME_1N_MC_path);

EmptyTFile_Map_MC.insert(std::make_pair(kMEPlayList_Vector.at(0),PlaylistME_1G_TFile));
EmptyTFile_Map_MC.insert(std::make_pair(kMEPlayList_Vector.at(1),PlaylistME_1A_TFile));
EmptyTFile_Map_MC.insert(std::make_pair(kMEPlayList_Vector.at(2),PlaylistME_1L_TFile));
EmptyTFile_Map_MC.insert(std::make_pair(kMEPlayList_Vector.at(3),PlaylistME_1M_TFile));
EmptyTFile_Map_MC.insert(std::make_pair(kMEPlayList_Vector.at(4),PlaylistME_1N_TFile));


TFile *PlaylistME_1G_TFile_noshift = new TFile(PlaylistME_noshift_1G_MC_path);
TFile *PlaylistME_1A_TFile_noshift = new TFile(PlaylistME_noshift_1A_MC_path);
TFile *PlaylistME_1L_TFile_noshift = new TFile(PlaylistME_noshift_1L_MC_path);
TFile *PlaylistME_1M_TFile_noshift = new TFile(PlaylistME_noshift_1M_MC_path);
TFile *PlaylistME_1N_TFile_noshift = new TFile(PlaylistME_noshift_1N_MC_path);


EmptyTFile_Map_MC_noshift.insert(std::make_pair(kMEPlayList_Vector.at(0),PlaylistME_1G_TFile_noshift));
EmptyTFile_Map_MC_noshift.insert(std::make_pair(kMEPlayList_Vector.at(1),PlaylistME_1A_TFile_noshift));
EmptyTFile_Map_MC_noshift.insert(std::make_pair(kMEPlayList_Vector.at(2),PlaylistME_1L_TFile_noshift));
EmptyTFile_Map_MC_noshift.insert(std::make_pair(kMEPlayList_Vector.at(3),PlaylistME_1M_TFile_noshift));
EmptyTFile_Map_MC_noshift.insert(std::make_pair(kMEPlayList_Vector.at(4),PlaylistME_1N_TFile_noshift));



ME_playlist_TFileMAP FullTFile_Map_MC;
TFile *PlaylistME_1P_TFile = new TFile(PlaylistME_1P_MC_path);
TFile *PlaylistME_1C_TFile = new TFile(PlaylistME_1C_MC_path);
TFile *PlaylistME_1D_TFile = new TFile(PlaylistME_1D_MC_path);
TFile *PlaylistME_1F_TFile = new TFile(PlaylistME_1F_MC_path);
TFile *PlaylistME_1E_TFile = new TFile(PlaylistME_1E_MC_path);
FullTFile_Map_MC.insert(std::make_pair(kMEPlayList_Vector.at(5),PlaylistME_1P_TFile));
FullTFile_Map_MC.insert(std::make_pair(kMEPlayList_Vector.at(6),PlaylistME_1C_TFile));
FullTFile_Map_MC.insert(std::make_pair(kMEPlayList_Vector.at(7),PlaylistME_1D_TFile));
FullTFile_Map_MC.insert(std::make_pair(kMEPlayList_Vector.at(8),PlaylistME_1F_TFile));
FullTFile_Map_MC.insert(std::make_pair(kMEPlayList_Vector.at(9),PlaylistME_1E_TFile));


ME_playlist_TFileMAP FullTFile_Map_MC_noshift;
TFile *PlaylistME_1P_TFile_noshift = new TFile(PlaylistME_noshift_1P_MC_path);
TFile *PlaylistME_1C_TFile_noshift = new TFile(PlaylistME_noshift_1C_MC_path);
TFile *PlaylistME_1D_TFile_noshift = new TFile(PlaylistME_noshift_1D_MC_path);
TFile *PlaylistME_1F_TFile_noshift = new TFile(PlaylistME_noshift_1F_MC_path);
TFile *PlaylistME_1E_TFile_noshift = new TFile(PlaylistME_noshift_1E_MC_path);
FullTFile_Map_MC_noshift.insert(std::make_pair(kMEPlayList_Vector.at(5),PlaylistME_1P_TFile_noshift));
FullTFile_Map_MC_noshift.insert(std::make_pair(kMEPlayList_Vector.at(6),PlaylistME_1C_TFile_noshift));
FullTFile_Map_MC_noshift.insert(std::make_pair(kMEPlayList_Vector.at(7),PlaylistME_1D_TFile_noshift));
FullTFile_Map_MC_noshift.insert(std::make_pair(kMEPlayList_Vector.at(8),PlaylistME_1F_TFile_noshift));
FullTFile_Map_MC_noshift.insert(std::make_pair(kMEPlayList_Vector.at(9),PlaylistME_1E_TFile_noshift));




ME_playlist_TFileMAP FullTFile_Map_Data;

TFile *PlaylistME_1P_DATA_TFile = new TFile(PlaylistME_1P_Data_path);
TFile *PlaylistME_1C_DATA_TFile = new TFile(PlaylistME_1C_Data_path);
TFile *PlaylistME_1D_DATA_TFile = new TFile(PlaylistME_1D_Data_path);
TFile *PlaylistME_1F_DATA_TFile = new TFile(PlaylistME_1F_Data_path);
TFile *PlaylistME_1E_DATA_TFile = new TFile(PlaylistME_1E_Data_path);
FullTFile_Map_Data.insert(std::make_pair(kMEPlayList_Vector.at(5),PlaylistME_1P_DATA_TFile));
FullTFile_Map_Data.insert(std::make_pair(kMEPlayList_Vector.at(6),PlaylistME_1C_DATA_TFile));
FullTFile_Map_Data.insert(std::make_pair(kMEPlayList_Vector.at(7),PlaylistME_1D_DATA_TFile));
FullTFile_Map_Data.insert(std::make_pair(kMEPlayList_Vector.at(8),PlaylistME_1F_DATA_TFile));
FullTFile_Map_Data.insert(std::make_pair(kMEPlayList_Vector.at(9),PlaylistME_1E_DATA_TFile));



ME_playlist_TFileMAP EmptyTFile_Map_Data;

TFile *PlaylistME_1G_DATA_TFile = new TFile(PlaylistME_1G_Data_path);
TFile *PlaylistME_1A_DATA_TFile = new TFile(PlaylistME_1A_Data_path);
TFile *PlaylistME_1L_DATA_TFile = new TFile(PlaylistME_1L_Data_path);
TFile *PlaylistME_1M_DATA_TFile = new TFile(PlaylistME_1M_Data_path);
TFile *PlaylistME_1N_DATA_TFile = new TFile(PlaylistME_1N_Data_path);
EmptyTFile_Map_Data.insert(std::make_pair(kMEPlayList_Vector.at(0),PlaylistME_1G_DATA_TFile));
EmptyTFile_Map_Data.insert(std::make_pair(kMEPlayList_Vector.at(1),PlaylistME_1A_DATA_TFile));
EmptyTFile_Map_Data.insert(std::make_pair(kMEPlayList_Vector.at(2),PlaylistME_1L_DATA_TFile));
EmptyTFile_Map_Data.insert(std::make_pair(kMEPlayList_Vector.at(3),PlaylistME_1M_DATA_TFile));
EmptyTFile_Map_Data.insert(std::make_pair(kMEPlayList_Vector.at(4),PlaylistME_1N_DATA_TFile));



bool is_mc=true;
bool isNOT_mc=false;

std::string  pdf_CV = string(text_title_pdf4);
std::string  pdf_ChiSqr = string(chisqrt_title_pdf4);
bool DoBinwidthNorm=true;
bool MakeXaxisLOG=false;
bool MakeYaxisLOG=false;
bool DrawallErrorGroups=false;

double NegZ_offset = 0.0;
double PosZ_offset = 0.0;
int NumZSteps = 1; // steps of 5mm

double NegX_offset = -40.0;
double PosX_offset = 20.0;
int NumXSteps = 30; // steps of 5mm

double NegY_offset = -20.0;
double PosY_offset = 80.0;
int NumYSteps = 50; // steps of 5mm


int NBinZ =NumZSteps;


int NBinX =NumXSteps;
int NBinY = NumYSteps;

XYZ_VertexOffSet_Map OffSetMapXYZ;

FillXYZOffSetMap(OffSetMapXYZ, NegX_offset, PosX_offset, NumXSteps, NegY_offset, PosY_offset,  NumYSteps, NegZ_offset, PosZ_offset, NumZSteps, true );


//const char* PlaylistME_1G_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1G_MC_All_SysErrorsOn_ThreeRegion_sideBand.root"; //PlaylistME_1G_MC_path;
//const char* PlaylistME_1G_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1G_Data_SideBand.root"; //(PlaylistME_1G_Data_path);
//const char* PlaylistME_1F_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1F_MC_All_SysErrorsOn_ThreeRegion_sideBand.root"; //PlaylistME_1F_MC_path;
//const char* PlaylistME_1F_Data_path =  "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1F_Data_SideBand.root"; //(PlaylistME_1F_Data_path);

//TFile *PlaylistME_1G_TFile = new TFile(PlaylistME_1G_MC_path);
/*

ME_playlist_TFileMAP FullTFile_Map_MC;
TFile *PlaylistME_1F_TFile = new TFile(PlaylistME_1F_MC_path);
FullTFile_Map_MC.insert(std::make_pair(kMEPlayList_Vector.at(8),PlaylistME_1F_TFile));

ME_playlist_TFileMAP EmptyTFile_Map_MC;

EmptyTFile_Map_MC.insert(std::make_pair(kMEPlayList_Vector.at(0),PlaylistME_1G_TFile));
ME_playlist_TFileMAP FullTFile_Map_Data;
TFile *PlaylistME_1F_DATA_TFile = new TFile(PlaylistME_1F_Data_path);
FullTFile_Map_Data.insert(std::make_pair(kMEPlayList_Vector.at(8),PlaylistME_1F_DATA_TFile));
ME_playlist_TFileMAP EmptyTFile_Map_Data;
TFile *PlaylistME_1G_DATA_TFile = new TFile(PlaylistME_1G_Data_path);
EmptyTFile_Map_Data.insert(std::make_pair(kMEPlayList_Vector.at(0),PlaylistME_1G_DATA_TFile));


MAP_RootPath_Empty_DATA.insert(std::make_pair(kMEPlayList_Vector.at(0), PlaylistME_1G_Data_path));
MAP_RootPath_Full_DATA.insert(std::make_pair(kMEPlayList_Vector.at(8), PlaylistME_1F_Data_path));

MAP_RootPath_Full_MC.insert(std::make_pair(kMEPlayList_Vector.at(8), PlaylistME_1F_MC_path));
MAP_RootPath_Empty_MC.insert(std::make_pair(kMEPlayList_Vector.at(0), PlaylistME_1G_MC_path));
*/


//Pot_MapList EmptyPOT_local_Data_MAP = Constuct_POT_playlistMap(MAP_RootPath_Empty_DATA, false);
//Pot_MapList FullPOT_local_Data_MAP  = Constuct_POT_playlistMap(MAP_RootPath_Full_DATA, false);
//Pot_MapList EmptyPOT_local_MC_MAP = Constuct_POT_playlistMap(MAP_RootPath_Empty_MC, true);
//Pot_MapList FullPOT_local_MC_MAP  = Constuct_POT_playlistMap(MAP_RootPath_Full_MC, true);


std::vector<std::string> histNames;
std::vector<Fit_Parms_Names> FitParms;
//h_Data_CryoVertex_X
//h_Data_CryoVertex_Y
//h_Data_CryoVertex_Z
//h_Data_CryoVertex_R
//h_CryoVertex_X
//h_CryoVertex_Y
//h_CryoVertex_Z
//h_CryoVertex_R,
histNames.push_back("h_Data_CryoVertex_R");FitParms.push_back(kh_Name_Data_fitTo);
histNames.push_back("h_CryoVertex_R");FitParms.push_back(kh_Name_MC_fitting);
////////////////////////////////////////////////////////////////////////////////
/*init_Tool(std::string input_PathtoRootMC_empty,
          std::string input_PathtoRootData_empty,
          std::string input_PathtoRootMC_full,
          std::string input_PathtoRootData_full,
          std::vector<std::string> histNames,
          std::vector<Fit_Parms_Names> FitParms,
          double FullPOTMC, double EmptyPOTMC, double FullPOTdata, double EmptyPOTdata );*/
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//kME1P,kME1C,kME1D,kME1E,kME1F,kME1A,kME1G,kME1L,kME1M,kME1N
//////////////////////////////////////////////////////////////
//
//  Inti Sidebandtool
//////////////////////////////////////////////////////////////
// 1D Fit
//////////////////////////////////////////////////////////////
/*
Helium_SideBandTool HeliumSideBand_Tool_Empty_1G_Full_1F;
std::cout<<"init_Tool Helium_SideBandTool"<<std::endl;
HeliumSideBand_Tool_Empty_1G_Full_1F.init_Tool_2playlist(input_PathtoRootMC_empty,
                                             input_PathtoRootData_empty,
                                             input_PathtoRootMC_full,
                                             input_PathtoRootData_full,
                                             histNames,
                                             FitParms,
          FullPOT_local_Data_MAP[kME1F]/FullPOT_local_MC_MAP[kME1F], FullPOT_local_Data_MAP[kME1F]/EmptyPOT_local_MC_MAP[kME1G], 1.0,   FullPOT_local_Data_MAP[kME1F]/EmptyPOT_local_Data_MAP[kME1G] );

HeliumSideBand_Tool_Empty_1G_Full_1F.InputPDFLabel(PDF_label);

HeliumSideBand_Tool_Empty_1G_Full_1F.Plot_initHist("ME1F","ME1G", "Vertex R [mm]");
//FitSideBands("Heliumfit",  "",  PDF_label);
std:cout<<"Finished::Plot_initHist"<<std::endl;
SetHeliumSideBandTool(HeliumSideBand_Tool_Empty_1G_Full_1F);
//FitSideBands("fit_vertexR", "EmptyFillResults.txt", PDF_label);
double fitwgt;
double fitwgt_error;
FitSideBands(HeliumSideBand_Tool_Empty_1G_Full_1F,"fit_vertexR", "EmptyFillResults.txt", PDF_label, fitwgt,fitwgt_error );

std::cout<<"Results of weights =  " <<  fitwgt << " -/+" << fitwgt_error << std::endl;

HeliumSideBand_Tool_Empty_1G_Full_1F.wgt_Aluminium.push_back(fitwgt);
HeliumSideBand_Tool_Empty_1G_Full_1F.err_Aluminium.push_back(fitwgt_error);

HeliumSideBand_Tool_Empty_1G_Full_1F.ApplyFitResults();
HeliumSideBand_Tool_Empty_1G_Full_1F.Plot_AfterFitHist("ME1F","ME1G", "Vertex R [mm]");

//HeliumSideBand_Tool_Empty_1G_Full_1F.Plot_AfterFitHist("ME1F","ME1G", "Vertex R [mm]");

   std::ofstream outfile1 ("X_Y_Fits.txt"); // re-create file from start of script
   outfile1.close();
   int fit_page = 5;
   int fit_page_X = 6;
   int fit_page_Y = 7;
   int fit_page_Z = 9;
   int fit_page_R = 8;
*/
////////////////////////////////////////
// Fitting to Empty to Side band 2 play list
//////////////////////////////////////
/*
Helium_3CryoRegionsSideBandTool Helium3SideBand_Tool_Empty_1G_Full_1F( FullTFile_Map_MC,
FullTFile_Map_Data,
EmptyTFile_Map_MC,
EmptyTFile_Map_Data,
FullPOT_local_Data_MAP,
FullPOT_local_MC_MAP,
EmptyPOT_local_Data_MAP,
EmptyPOT_local_MC_MAP
);




std::vector< ME_helium_Playlists> fullPlayList_Vector;
fullPlayList_Vector.push_back(kMEPlayList_Vector.at(8));
std::vector< ME_helium_Playlists> EmptyPlayList_Vector;
EmptyPlayList_Vector.push_back(kMEPlayList_Vector.at(0));


Helium3SideBand_Tool_Empty_1G_Full_1F.init_Tool_2playlist(fullPlayList_Vector,EmptyPlayList_Vector);
Helium3SideBand_Tool_Empty_1G_Full_1F.InputPDFLabel(PDF_label);
Helium3SideBand_Tool_Empty_1G_Full_1F.Plot_initHist("ME1F","ME1G", "");
SetHelium3SideBandTool(Helium3SideBand_Tool_Empty_1G_Full_1F);
std::vector<double> wgt_vector;
std::vector<double> wgt_error_vector;
FitSideBands(Helium3SideBand_Tool_Empty_1G_Full_1F,
  "fourbandFit","fourbandFit", PDF_label,  wgt_vector, wgt_error_vector);
  Helium3SideBand_Tool_Empty_1G_Full_1F.Fill_Alwgt(wgt_vector, wgt_error_vector );
Helium3SideBand_Tool_Empty_1G_Full_1F.ApplyFitResults();
Helium3SideBand_Tool_Empty_1G_Full_1F.Plot_AfterFitHist("ME1F","ME1G", "");
Helium3SideBand_Tool_Empty_1G_Full_1F.MakeLatexSlides("Fit_latex");
*/
///////////////////////////////////
///
/////////////////////////////////

std::vector< ME_helium_Playlists> fullPlayList_Vector;
fullPlayList_Vector.push_back(kMEPlayList_Vector.at(5));
fullPlayList_Vector.push_back(kMEPlayList_Vector.at(6));
fullPlayList_Vector.push_back(kMEPlayList_Vector.at(7));
fullPlayList_Vector.push_back(kMEPlayList_Vector.at(8));
fullPlayList_Vector.push_back(kMEPlayList_Vector.at(9));

std::vector< ME_helium_Playlists> EmptyPlayList_Vector;
EmptyPlayList_Vector.push_back(kMEPlayList_Vector.at(0));
EmptyPlayList_Vector.push_back(kMEPlayList_Vector.at(1));
EmptyPlayList_Vector.push_back(kMEPlayList_Vector.at(2));
EmptyPlayList_Vector.push_back(kMEPlayList_Vector.at(3));
EmptyPlayList_Vector.push_back(kMEPlayList_Vector.at(4));


Helium_3CryoRegionsSideBandTool Helium3SideBand_Tool_FullPlaylist(
FullTFile_Map_MC,
FullTFile_Map_Data,
EmptyTFile_Map_MC,
EmptyTFile_Map_Data,
FullPOT_local_Data_MAP,
FullPOT_local_MC_MAP,
EmptyPOT_local_Data_MAP,
EmptyPOT_local_MC_MAP
);

Helium_3CryoRegionsSideBandTool Helium3SideBand_Tool_FullPlaylist_noshift(
FullTFile_Map_MC_noshift,
FullTFile_Map_Data,
EmptyTFile_Map_MC_noshift,
EmptyTFile_Map_Data,
FullPOT_local_Data_MAP,
FullPOT_noshift_local_MC_MAP,
EmptyPOT_local_Data_MAP,
EmptyPOT_noshift_local_MC_MAP
);

/*
Helium_3CryoRegionsSideBandTool Helium3SideBand_Tool_EmptyPlaylist(
EmptyTFile_Map_MC,
EmptyTFile_Map_Data,
EmptyPOT_local_Data_MAP,
EmptyPOT_local_MC_MAP
);
*/

int FitEmpty = 0;
int FitFull = 1;
int FitFull_Empty = 2;
int FitFull_Empty_combined = 3;
double errorfit = 999;

Helium3SideBand_Tool_FullPlaylist.InputPDFLabel(PDF_label);
//Helium3SideBand_Tool_FullPlaylist.SetLogChi(true);
//Helium3SideBand_Tool_FullPlaylist.SetAreaNormalized(false);
Helium3SideBand_Tool_FullPlaylist.init_Tool_CompleteNuMEplaylist(fullPlayList_Vector, EmptyPlayList_Vector);
Helium3SideBand_Tool_FullPlaylist.FillResolutionHistnames();
Helium3SideBand_Tool_FullPlaylist.init_MC_PlaylistCombined_SideBand_Resolution_Histograms();
Helium3SideBand_Tool_FullPlaylist.init_MC_PlaylistCombined_Mig_Histograms(fullPlayList_Vector.at(0), EmptyPlayList_Vector.at(0));
Helium3SideBand_Tool_FullPlaylist.Plot_initHist("All","All", "[Convolution applied][noFid]");
Helium3SideBand_Tool_FullPlaylist.Plot_initResolutionHist("[Convolution applied][noFid]", "All","All");
//Helium3SideBand_Tool_FullPlaylist.MakeRatioPlot_forXYZR("Before reweight", 0);
//Helium3SideBand_Tool_FullPlaylist.plotEmpty_Resolutions(false);
//Helium3SideBand_Tool_FullPlaylist.plotFull_Empty_Resolutions(false);
//Helium3SideBand_Tool_FullPlaylist.Plot_All_MigHist("[Convolution][Shifted ^{4}He+^{27}Al](4, -4, -6)[Fid]");
//Helium3SideBand_Tool_EmptyPlaylist.init_Tool_CompleteEmptyplaylist(EmptyPlayList_Vector);
Helium3SideBand_Tool_FullPlaylist_noshift.init_Tool_CompleteNuMEplaylist(fullPlayList_Vector, EmptyPlayList_Vector);
Helium3SideBand_Tool_FullPlaylist_noshift.InputPDFLabel(PDF_label_noshift);
Helium3SideBand_Tool_FullPlaylist_noshift.Plot_initHist("All","All", "[No Wgts and Convolution][noFid]");
Helium3SideBand_Tool_FullPlaylist_noshift.WriteBeforeChi("Chi_BeforeNoShiftedFid");
std::cout<<"Setting Tool for fitting"<<std::endl;

SetHelium3SideBandTool(Helium3SideBand_Tool_FullPlaylist);
std::vector<double> wgt_vector;
std::vector<double> wgt_error_vector;
std::cout<<"Fitting Side band"<<std::endl;

FitSideBands(Helium3SideBand_Tool_FullPlaylist, 7,
  "fourbandFit","fourbandFit", PDF_label,  wgt_vector, wgt_error_vector, errorfit);
//Helium3SideBand_Tool_FullPlaylist.Fill_AlandHewgts(wgt_vector, wgt_error_vector );
//std::cout<<"Filling wgts"<<std::endl;
Helium3SideBand_Tool_FullPlaylist.Fill_Alwgt(wgt_vector, wgt_error_vector );
//std::cout<<"Applying Wgts"<<std::endl;
Helium3SideBand_Tool_FullPlaylist.ApplyFitResults();
//std::cout<<"Applying wgts to Resolution "<<std::endl;
//Helium3SideBand_Tool_FullPlaylist.ApplyFitResults_toResolution();
////Helium3SideBand_Tool_FullPlaylist.ApplyFitResults_Al_He_combined();
int combinedFit = 1;
//std::cout<<"Plotting after fit "<<std::endl;
Helium3SideBand_Tool_FullPlaylist.Plot_AfterFitHist("All","All", "Convolution applied [noFid]", combinedFit);
//std::cout<<"Plotting Resolution after fit "<<std::endl;
//Helium3SideBand_Tool_FullPlaylist.Plot_AfterFit_ResolutionHist("After Log #chi^{2} Fit [Shifted](0,0,0)[Fid]", "All","All");
//Helium3SideBand_Tool_FullPlaylist.MakeRatioPlot_forXYZR("After reweight", 1);

//Helium3SideBand_Tool_FullPlaylist.MakeChiSqrt_table("Fitting_COMBINED_Empty_Fid_42shifted", 1.0);
//Helium3SideBand_Tool_FullPlaylist.MakeLatexSlides("Fit_latex");
std::vector<double> full_chi_old;
std::vector<double> empty_chi_old;
std::vector<double> full_empty_chi_old;
Helium3SideBand_Tool_FullPlaylist.Fill_vectors_file(full_chi_old , empty_chi_old, full_empty_chi_old, "Chi_BeforeNoShiftedFid" );
Helium3SideBand_Tool_FullPlaylist_noshift.init_MC_PlaylistCombined_Mig_Histograms(fullPlayList_Vector.at(0), EmptyPlayList_Vector.at(0));


//Helium3SideBand_Tool_FullPlaylist.MakeChiSqrt_table_beforeShiftincluded("50_5_Neg24_chiTable_Fid", 1.0, full_chi_old , empty_chi_old, full_empty_chi_old);


MnvH2D* Mig_vertex_X  = (PlotUtils::MnvH2D*)Helium3SideBand_Tool_FullPlaylist.Empty.MnvH2D_Mig_vertex_X->Clone("Mig_vertex_X");
MnvH2D* Mig_vertex_Y  = (PlotUtils::MnvH2D*)Helium3SideBand_Tool_FullPlaylist.Empty.MnvH2D_Mig_vertex_Y->Clone("Mig_vertex_Y");
MnvH2D* Mig_vertex_R  = (PlotUtils::MnvH2D*)Helium3SideBand_Tool_FullPlaylist.Empty.MnvH2D_Mig_vertex_R->Clone("Mig_vertex_R");
MnvH2D* Mig_vertex_Z  = (PlotUtils::MnvH2D*)Helium3SideBand_Tool_FullPlaylist.Empty.MnvH2D_Mig_vertex_Z->Clone("Mig_vertex_Z");

MnvH2D* Mig_vertex_X_Noshifted  = (PlotUtils::MnvH2D*)Helium3SideBand_Tool_FullPlaylist_noshift.Empty.MnvH2D_Mig_vertex_X->Clone("Mig_vertex_X");
MnvH2D* Mig_vertex_Y_Noshifted  = (PlotUtils::MnvH2D*)Helium3SideBand_Tool_FullPlaylist_noshift.Empty.MnvH2D_Mig_vertex_Y->Clone("Mig_vertex_Y");
MnvH2D* Mig_vertex_R_Noshifted  = (PlotUtils::MnvH2D*)Helium3SideBand_Tool_FullPlaylist_noshift.Empty.MnvH2D_Mig_vertex_R->Clone("Mig_vertex_R");
MnvH2D* Mig_vertex_Z_Noshifted  = (PlotUtils::MnvH2D*)Helium3SideBand_Tool_FullPlaylist_noshift.Empty.MnvH2D_Mig_vertex_Z->Clone("Mig_vertex_Z");


//rowNormalize(*h_mig_rowNorm);


Mig_vertex_X->Divide(Mig_vertex_X, Mig_vertex_X_Noshifted);
Mig_vertex_Y->Divide(Mig_vertex_Y, Mig_vertex_Y_Noshifted);
Mig_vertex_R->Divide(Mig_vertex_R, Mig_vertex_R_Noshifted);
Mig_vertex_Z->Divide(Mig_vertex_Z, Mig_vertex_Z_Noshifted);


 Draw2DHist_Migration_Histpointer(Mig_vertex_X,  "E[All] [noFid] Ratio #frac{Shifted(4, -4, -6)}{NotShifted} Migration ",
   "RECO vertex X", "TRUE vertex X", "RATIO #frac{Shifted ^{4}He + ^{27}Al }{NotShifted}",
 PDF_label, can, mnv_plot);

 Draw2DHist_Migration_Histpointer(Mig_vertex_Y,  "E[All] [noFid] Ratio #frac{Shifted(4, -4, -6)}{NotShifted} Migration ",
   "RECO vertex Y", "TRUE vertex Y", "RATIO #frac{Shifted ^{4}He + ^{27}Al }{NotShifted}",
 PDF_label, can, mnv_plot);

 Draw2DHist_Migration_Histpointer(Mig_vertex_R,  "E[All] [noFid] Ratio #frac{Shifted(4, -4, -6)}{NotShifted} Migration ",
   "RECO vertex R", "TRUE vertex R", "RATIO #frac{Shifted ^{4}He + ^{27}Al }{NotShifted}",
 PDF_label, can, mnv_plot);

 Draw2DHist_Migration_Histpointer(Mig_vertex_Z,  "E[All] [noFid] Ratio #frac{Shifted(4, -4, -6)}{NotShifted} Migration ",
   "RECO vertex Z", "TRUE vertex Z", "RATIO #frac{Shifted ^{4}He + ^{27}Al }{NotShifted}",
 PDF_label, can, mnv_plot);



 //Draw_FourFitRegion_CryoTank(PDF_label_withpdf, can, mnv_plot);

   can -> Print(text_title_pdf3);
   can -> Print(chisqrt_title_pdf3);
   can -> Print(text_title_noshift_pdf3);


}


//End of MainFuntion
///////////////////////////////////

/////////////////////////////////////////////
//Main Function
/////////////////////////////////////////////

 int main() {

bool cutsOn=true;
std::cout << "Run over cutsOn?  (0 = false, 1 = true) " << std::endl;
//std::cin >> cutsOn;
std::cout << std::boolalpha << cutsOn << std::endl;

bool my_norm=true;
std::cout << "Which Normalization?  (0 = POT, 1 = relative equal areas) " << std::endl;
//std::cin >> my_norm;
std::cout << std::boolalpha << my_norm << std::endl;

bool my_debug=true;
std::cout << "Run in Debug Mode? (0 = NO, 1 = YES) " << std::endl;
//std::cin >> my_debug;
std::cout << std::boolalpha << my_debug << std::endl;

int my_Print_Systmatics = 0;
std::cout << "Print Error Systmatics?  [ 0 = Total and Groups Systemtics Errors ,  1 = Total Systematic Errors , 2 = none ]" << std::endl;
//std::cin >> my_Print_Systmatics;
std::cout << "Pitched: " << my_Print_Systmatics << std::endl;


std::string input="cnguyen";
std::cout << "What is the name of the user? " << std::endl;
//std::cin >> input;
std::cout << input << std::endl;

const char *inputFileLoc = input.c_str();

Kin(cutsOn, my_norm, my_debug, inputFileLoc, my_Print_Systmatics);

return 0;

}


std::vector<ME_helium_Playlists> GetPlayListVector_MC() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ME_helium_Playlists> Playlist;
  //EMPTY
    Playlist.push_back(kME1G);
    Playlist.push_back(kME1A);
    Playlist.push_back(kME1L);
    Playlist.push_back(kME1M);
    Playlist.push_back(kME1N);
  //Full
    Playlist.push_back(kME1P);
    Playlist.push_back(kME1C);
    Playlist.push_back(kME1D);
    Playlist.push_back(kME1F);
    Playlist.push_back(kME1E);
  return Playlist;
//#endif
}


std::vector<ME_helium_Playlists> GetPlayListVector_DATA() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ME_helium_Playlists> Playlist;

  //EMPTY
    Playlist.push_back(kME1G);
    Playlist.push_back(kME1A);
    Playlist.push_back(kME1L);
    Playlist.push_back(kME1M);
    Playlist.push_back(kME1N);
  //Full
    Playlist.push_back(kME1P);
    Playlist.push_back(kME1C);
    Playlist.push_back(kME1D);
    Playlist.push_back(kME1F);
    Playlist.push_back(kME1E);
  return Playlist;
//#endif
}
//////////////////////////////////////////////////////////////////////////
//GET Vertex Varibles
//////////////////////////////////////////////////////////////////////////
std::vector<CryoVertex> GetCryoVertexVaribles() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<CryoVertex> CryoVertexVars;

  CryoVertexVars.push_back(kX);
  CryoVertexVars.push_back(kY);
  //CryoVertexVars.push_back(kZ);
  //CryoVertexVars.push_back(kR);


  return CryoVertexVars;
//#endif
}
std::vector<CryoVertex> GetCryoVertexVaribles_All() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<CryoVertex> CryoVertexVars;

  CryoVertexVars.push_back(kX);
  CryoVertexVars.push_back(kY);
  CryoVertexVars.push_back(kR);
  CryoVertexVars.push_back(kZ);



  return CryoVertexVars;
//#endif
}





void AppendtoLatex_FiveFigures(std::string output_name ,  std::string pdf_name_CV, int Figure_1_page_number, int Figure_2_page_number,
  int Figure_3_page_number, int Figure_5_page_number, int Figure_6_page_number, char *slideTitle){
  double scale= .24;
  std::ofstream myfile;
  std::string fileName = output_name + ".txt";
  myfile.open(fileName, std::ios_base::app);
  std::cout<<"Adding to Latex File "<< fileName<<std::endl;
  LatexFormat Latex_output(scale);
  myfile<<"\n";
  myfile<<"\n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<"%%%  Start   "<< slideTitle<<" \n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<Latex_output.GetBeginFrame(slideTitle)<< "\n";
  myfile<<Latex_output.GetBeginTabular()<< "\n";
  myfile<<Latex_output.GetInclude_figure(Figure_1_page_number, pdf_name_CV)<< "\n";
  myfile<<"& \n";
  myfile<<Latex_output.GetInclude_figure(Figure_2_page_number, pdf_name_CV )<< "\n";
  myfile<<"& \n";
  myfile<<Latex_output.GetInclude_figure(Figure_3_page_number, pdf_name_CV)<< "\n";
  myfile<<Latex_output.Get_vSpace("-.28cm")<< "\n";
  myfile<<"\\\\ \n";

  myfile<<"& \n";
  myfile<<Latex_output.GetInclude_figure(Figure_5_page_number, pdf_name_CV )<< "\n";
  myfile<<"& \n";
  myfile<<Latex_output.GetInclude_figure(Figure_6_page_number, pdf_name_CV)<< "\n";
  myfile<<Latex_output.GetEndTabular()<< "\n";
  myfile<<Latex_output.GetEndFrame();

  myfile<<"\n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<"%%% END FRAME  \n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";

  myfile.close();


}// end of function





OffSet1DMap Constuct_OffSet1DMap(TFile *PlaylistME_Tfile_MC, TFile *PlaylistME_Tfile_Data,
                                 const char *hist_MCname, const char *hist_DataName,
                                 char *Title,  ME_helium_Playlists playlist, VertexOffSet_Map OffSetMap,
                                 int NBinZ, int NBinR ){
std::cout<<"Inside:Constuct_OffSet1DMap"<<std::endl;
   OffSet1DMap ReturnMap;
   MnvH1D_Map Hist_MC_Map_input;

   ReturnMap.Hist_title= Title;
   ReturnMap.playlist = playlist;
   ReturnMap.Crytank_status =  GetPlaylist_HeliumStatus(playlist);
   ReturnMap.OffSetMap=OffSetMap;
   ReturnMap.NBinZ = NBinZ;
   ReturnMap.NBinR = NBinR;


   bool CryoTankstatus = IFstatusFullreturntrue(ReturnMap.Crytank_status);
   ReturnMap.DataHist = Get1DHist(*PlaylistME_Tfile_Data, hist_DataName, CryoTankstatus);
   char tempName[1024];

   for(int i = 0; i < NBinZ; ++i ){
     for(int j = 0; j < NBinR; ++j ){

       int input_int = CantorPair(i, j);
       sprintf(tempName,"%s_%d", hist_MCname, input_int);
       std::cout<<"Trying to get Hist named = "<< tempName<<std::endl;
       PlotUtils::MnvH1D* hist  = Get1DHist(*PlaylistME_Tfile_MC, tempName, CryoTankstatus);
       Hist_MC_Map_input.insert(std::make_pair(input_int, hist));
     }
   }

   ReturnMap.Hist_MC_Map = Hist_MC_Map_input;


   return ReturnMap;

 }

 OffSet2DMap Constuct_OffSet2DMap(TFile *PlaylistME_Tfile_MC, TFile *PlaylistME_Tfile_Data,
                                  const char *hist_MCname, const char *hist_DataName,
                                  char *Title,  ME_helium_Playlists playlist, VertexOffSet_Map OffSetMap,
                                  int NBinZ, int NBinR ){
 std::cout<<"Inside:Constuct_OffSet1DMap"<<std::endl;
    OffSet2DMap ReturnMap;
    MnvH2D_Map Hist_MC_Map_input;

    ReturnMap.Hist_title= Title;
    ReturnMap.playlist = playlist;
    ReturnMap.Crytank_status =  GetPlaylist_HeliumStatus(playlist);
    ReturnMap.OffSetMap=OffSetMap;
    ReturnMap.NBinZ = NBinZ;
    ReturnMap.NBinR = NBinR;


    bool CryoTankstatus = IFstatusFullreturntrue(ReturnMap.Crytank_status);
    ReturnMap.DataHist = Get2DHist(*PlaylistME_Tfile_Data, hist_DataName, CryoTankstatus);
    char tempName[1024];

    for(int i = 0; i < NBinZ; ++i ){
      for(int j = 0; j < NBinR; ++j ){

        int input_int = CantorPair(i, j);
        sprintf(tempName,"%s_%d", hist_MCname, input_int);
        std::cout<<"Trying to get Hist named = "<< tempName<<std::endl;
        PlotUtils::MnvH2D* hist  = Get2DHist(*PlaylistME_Tfile_MC, tempName, CryoTankstatus);
        Hist_MC_Map_input.insert(std::make_pair(input_int, hist));
      }
    }

    ReturnMap.Hist_MC_Map = Hist_MC_Map_input;


    return ReturnMap;

  }




std::vector<OffSet1DMap> Constuct_OffSet1DMap_Vector(ME_playlist_TFileMAP InputTFileMap, ME_playlist_TFileMAP InputTFileData,
                                                  const char *hist_MCname, const char *hist_DataName,char *Title,  VertexOffSet_Map OffSetMap,
                                                  int NBinZ, int NBinR ){

std::vector<OffSet1DMap>  OffSet_Vector;
std::cout<<"Inside:Constuct_OffSet1DMap_Vector"<<std::endl;
  //typename std::map<ME_helium_Playlists, TFile*>::const_iterator cat;
    //typename std::map<ME_helium_Playlists, TFile*>::const_iterator cat;

  typename std::map<ME_helium_Playlists, TFile*>::const_iterator cat;
  typename std::map<ME_helium_Playlists, TFile*>::const_iterator dog;

for( cat =  InputTFileMap.begin(), dog = InputTFileData.begin(); cat != InputTFileMap.end(); ++cat, ++dog ){
std::cout<<"Making map for playlist = "<< GetPlaylist_Name(cat->first)<<std::endl;

  OffSet1DMap offset1dMap_index = Constuct_OffSet1DMap(cat->second, dog->second , hist_MCname, hist_DataName,Title, cat->first,  OffSetMap, NBinZ,  NBinR );
  OffSet_Vector.push_back(offset1dMap_index);


}

return OffSet_Vector;


}//end of function

std::vector<OffSet2DMap> Constuct_OffSet2DMap_Vector(ME_playlist_TFileMAP InputTFileMap, ME_playlist_TFileMAP InputTFileData,
                                                  const char *hist_MCname, const char *hist_DataName,char *Title,  VertexOffSet_Map OffSetMap,
                                                  int NBinZ, int NBinR ){

std::vector<OffSet2DMap>  OffSet_Vector;
std::cout<<"Inside:Constuct_OffSet1DMap_Vector"<<std::endl;
  //typename std::map<ME_helium_Playlists, TFile*>::const_iterator cat;
    //typename std::map<ME_helium_Playlists, TFile*>::const_iterator cat;

  typename std::map<ME_helium_Playlists, TFile*>::const_iterator cat;
  typename std::map<ME_helium_Playlists, TFile*>::const_iterator dog;

for( cat =  InputTFileMap.begin(), dog = InputTFileData.begin(); cat != InputTFileMap.end(); ++cat, ++dog ){
std::cout<<"Making map for playlist = "<< GetPlaylist_Name(cat->first)<<std::endl;

  OffSet2DMap offset2dMap_index = Constuct_OffSet2DMap(cat->second, dog->second , hist_MCname, hist_DataName,Title, cat->first,  OffSetMap, NBinZ,  NBinR );
  OffSet_Vector.push_back(offset2dMap_index);


}

return OffSet_Vector;


}//end of function


OffSet1DMap Combined_OffSet1DMap_Vector(std::vector<OffSet1DMap> input, ME_helium_Playlists ADDtothisHis,
  const char* name, int NBinZ, int NBinR , bool isFull )
{
  OffSet1DMap CombinedMap;

  PlotUtils::MnvH1D* histTOAdd;
  MnvH1D_Map Hist_MC_Map_toADD;
std::cout<<"inside:Combined_OffSet1DMap_Vector "<<std::endl;

  for(auto cat:input ){

    if(cat.playlist==ADDtothisHis){
      //histTOAdd =  cat.DataHist;
      histTOAdd = (PlotUtils::MnvH1D*)cat.DataHist->Clone("histTOAdd");
      Clone_OffSet1DMap(Hist_MC_Map_toADD , cat.Hist_MC_Map);
      //Hist_MC_Map_toADD = cat.Hist_MC_Map;
      CombinedMap.Hist_title = cat.Hist_title;
      CombinedMap.OffSetMap=cat.OffSetMap;
    }
  }

    CombinedMap.NBinZ = NBinZ;
    CombinedMap.NBinR = NBinR;

    for(auto cat:input ){
      if(cat.playlist != ADDtothisHis){
        histTOAdd->Add(cat.DataHist);
        AddMnvH1D_Maps(Hist_MC_Map_toADD, cat.Hist_MC_Map,  NBinZ,  NBinR);
      }
    }


    if(isFull==true){
      CombinedMap.playlist= kCombinedFull;
      CombinedMap.Crytank_status=  kFULL;
    }
    else{
      CombinedMap.playlist= kCombinedEmpty;
      CombinedMap.Crytank_status=kEMPTY;
    }


    CombinedMap.DataHist = histTOAdd;
    CombinedMap.Hist_MC_Map = Hist_MC_Map_toADD;


    return CombinedMap;

  //end loop
}// END OF FUNCTION

OffSet2DMap Combined_OffSet2DMap_Vector(std::vector<OffSet2DMap> input, ME_helium_Playlists ADDtothisHis,
  const char* name, int NBinZ, int NBinR , bool isFull )
{
  OffSet2DMap CombinedMap;

  PlotUtils::MnvH2D* histTOAdd;
  MnvH2D_Map Hist_MC_Map_toADD;
std::cout<<"inside:Combined_OffSet1DMap_Vector "<<std::endl;

  for(auto cat:input ){

    if(cat.playlist==ADDtothisHis){
      //histTOAdd =  cat.DataHist;
      histTOAdd = (PlotUtils::MnvH2D*)cat.DataHist->Clone("histTOAdd");
      Clone_OffSet2DMap(Hist_MC_Map_toADD , cat.Hist_MC_Map);
      //Hist_MC_Map_toADD = cat.Hist_MC_Map;
      CombinedMap.Hist_title = cat.Hist_title;
      CombinedMap.OffSetMap=cat.OffSetMap;
    }
  }

    CombinedMap.NBinZ = NBinZ;
    CombinedMap.NBinR = NBinR;

    for(auto cat:input ){
      if(cat.playlist != ADDtothisHis){
        histTOAdd->Add(cat.DataHist);
        AddMnvH2D_Maps(Hist_MC_Map_toADD, cat.Hist_MC_Map,  NBinZ,  NBinR);
      }
    }


    if(isFull==true){
      CombinedMap.playlist= kCombinedFull;
      CombinedMap.Crytank_status=  kFULL;
    }
    else{
      CombinedMap.playlist= kCombinedEmpty;
      CombinedMap.Crytank_status=kEMPTY;
    }


    CombinedMap.DataHist = histTOAdd;
    CombinedMap.Hist_MC_Map = Hist_MC_Map_toADD;


    return CombinedMap;

  //end loop
}// END OF FUNCTION

void ScaleMC_OffSet1DMap(OffSet1DMap &inputMap , double ScaleMC){

  for(auto cat = inputMap.Hist_MC_Map.begin(); cat != inputMap.Hist_MC_Map.begin(); ++cat ){
    cat->second->Scale(ScaleMC);
  }
}//end of function

void ScaleMC_OffSet2DMap(OffSet2DMap &inputMap , double ScaleMC){

  for(auto cat = inputMap.Hist_MC_Map.begin(); cat != inputMap.Hist_MC_Map.begin(); ++cat ){
    cat->second->Scale(ScaleMC);
  }
}//end of function

void ScaleData_OffSet1DMap(OffSet1DMap &inputMap , double ScaleData){
  inputMap.DataHist->Scale(ScaleData);
}

void ScaleData_OffSet2DMap(OffSet2DMap &inputMap , double ScaleData){
  inputMap.DataHist->Scale(ScaleData);
}

void Clone_OffSet1DMap(MnvH1D_Map &inputMap_Clone , MnvH1D_Map inputMap_input){
  std::cout<<"inside: Clone_OffSet1DMap"<<std::endl;
for(auto cat =inputMap_input.begin();cat !=inputMap_input.end(); ++cat  ){
auto hist = (PlotUtils::MnvH1D*)cat->second->Clone("hist_COPY");
inputMap_Clone.insert(std::make_pair(cat->first,hist ));

}


}

void Clone_OffSet2DMap(MnvH2D_Map &inputMap_Clone , MnvH2D_Map inputMap_input){
  std::cout<<"inside: Clone_OffSet2DMap"<<std::endl;
for(auto cat =inputMap_input.begin();cat !=inputMap_input.end(); ++cat  ){
auto hist = (PlotUtils::MnvH2D*)cat->second->Clone("hist_COPY");
inputMap_Clone.insert(std::make_pair(cat->first,hist ));

}


}


void DrawSinglePlaylist_OffSet1DPlot(TCanvas *can, MnvPlotter *plot, OffSet1DMap InputMap,
  std::string units, std::string pdf_label, std::string pdf_Chisqrlabel, char* hist_title,
   char *xaxislabel, char* yaxislabel,  Pot_MapList Pot_MC , Pot_MapList Pot_Data , double Ymax){

     bool DoBinwidthNorm=false;
     bool DrawErrors= false;
     bool MakeXaxisLOG=false;
     bool MakeYaxisLOG= false;
     bool drawAllErrorGroups = false;
     char Plot_title[1024];
     std::string playlist_name = GetPlaylist_InitialName(InputMap.playlist);
     double MCtoData_scaler = Pot_Data[InputMap.playlist] / Pot_MC[InputMap.playlist];

     std::string HeliumStatus_name = GetPlaylistStatusString(GetPlaylist_HeliumStatus(InputMap.playlist));
     char HeliumStatus_name_char[HeliumStatus_name.length()+1];
     strcpy(HeliumStatus_name_char,HeliumStatus_name.c_str());

     char playlist_name_char[playlist_name.length()+1];
     strcpy( playlist_name_char,playlist_name.c_str());
     /*  char *Hist_title;
       ME_helium_Playlists playlist;
       ME_helium_Status Crytank_status;
       VertexOffSet_Map OffSetMap;
       int NBinZ;
       int NBinR;
       MnvH1D_Map Hist_MC_Map;
       PlotUtils::MnvH1D* DataHist;*/
       std::vector<double> R_offset_vector;
       std::vector<double> Z_offset_vector;
       std::vector<double> chi_offset_vector;
        std::vector<double> chi_offset_ndf_vector;
       int NBinZ = InputMap.NBinZ;
       int NBinR = InputMap.NBinR;
       //ScaleMC_OffSet1DMap(InputMap , MCtoData_scaler);

       for(int i = 0; i < NBinZ; ++i ){
         for(int j = 0; j < NBinR; ++j ){

           int input_int = CantorPair(i, j);

           double RoffSet = InputMap.OffSetMap[input_int].first;
           double ZoffSet = InputMap.OffSetMap[input_int].second;
           R_offset_vector.push_back(RoffSet);
           Z_offset_vector.push_back(ZoffSet);
           double chi = 0;
           int ndf = 0;

              sprintf(Plot_title, "%s OffSetPlot(Z,R) = (%.2f, %.2f) [mm]", hist_title, ZoffSet, RoffSet);
              std::cout<<"title of Hist = "<< Plot_title << "Scaling MC by = "<< MCtoData_scaler << std::endl;
              //InputMap.Hist_MC_Map.at(input_int)->Scale(MCtoData_scaler);
              auto hist_COPY = (PlotUtils::MnvH1D*)InputMap.Hist_MC_Map.at(input_int)->Clone("hist_COPY");
              hist_COPY->Scale(MCtoData_scaler);
              //DrawCVAndError_FromHistPointer(InputMap.DataHist, "data", xaxislabel,  yaxislabel,
              //  pdf_label, DoBinwidthNorm, MakeXaxisLOG);

              Draw_DataWITHMC_SingleHistinput_withRatio(hist_COPY, InputMap.DataHist,
              playlist_name_char, pdf_label, Plot_title, "mm",
              xaxislabel,  yaxislabel,  DoBinwidthNorm, MakeXaxisLOG,
              MakeYaxisLOG ,DrawErrors, drawAllErrorGroups, Ymax ,chi, ndf );

              chi_offset_vector.push_back(chi);
              chi_offset_ndf_vector.push_back((chi / (double)ndf));

         }
       }

      auto TGraphR =  MakeTGraph_from_Vectors(chi_offset_vector,  R_offset_vector);
      auto TGraphZ =  MakeTGraph_from_Vectors(chi_offset_vector,  Z_offset_vector);
      auto TGraphR_ndf=  MakeTGraph_from_Vectors(chi_offset_ndf_vector,  R_offset_vector);
      auto TGraphZ_ndf =  MakeTGraph_from_Vectors(chi_offset_ndf_vector,  Z_offset_vector);
      //std::string pdf_string = pdf_label + ".pdf";
      char pdf_charinput[pdf_Chisqrlabel.length()+1];
      strcpy(pdf_charinput,pdf_Chisqrlabel.c_str());
      char pdf_char[1024];
      sprintf(pdf_char , "%s.pdf",pdf_charinput);

      char TGraphTitle[1024];
      sprintf(TGraphTitle , "#chi^{2} vs. Offset R  [%s(%s)]", playlist_name_char, HeliumStatus_name_char);
      DrawTGraph(TGraphR,     "offSet R",  "#chi^{2}", TGraphTitle , "#chi^{2}",
      pdf_char, can, plot, false, false );
        sprintf(TGraphTitle , "#chi^{2} / ndf vs. Offset R  [%s(%s)]", playlist_name_char, HeliumStatus_name_char);
      DrawTGraph(TGraphR_ndf, "offSet R",  "#chi^{2} / ndf", TGraphTitle , "#chi^{2}",
      pdf_char, can, plot, false, false );

      sprintf(TGraphTitle , "#chi^{2} vs. Offset Z  [%s(%s)]", playlist_name_char, HeliumStatus_name_char);
      DrawTGraph(TGraphZ,   "offSet Z",  "#chi^{2}", TGraphTitle, "#chi^{2}",
      pdf_char, can, plot, false, false );

      sprintf(TGraphTitle , "#chi^{2} /ndf vs. Offset Z [%s(%s)]", playlist_name_char, HeliumStatus_name_char);
      DrawTGraph(TGraphZ_ndf, "offSet Z",  "#chi^{2} / ndf", TGraphTitle, "#chi^{2}",
      pdf_char, can, plot, false, false );

    }//end of function
//////////////////
/////////
////////////////
//////////////////////////
void DrawSinglePlaylist_OffSet1DPlot_Combined(TCanvas *can, MnvPlotter *plot, OffSet1DMap InputMap, std::string units, std::string pdf_label, std::string pdf_Chisqrlabel, char* hist_title,
   char *xaxislabel, char* yaxislabel ,char *playlist_name, double Ymax){

     bool DoBinwidthNorm=false;
     bool DrawErrors= false;
     bool MakeXaxisLOG=false;
     bool MakeYaxisLOG= false;
     bool drawAllErrorGroups = false;
     char Plot_title[1024];
     //char playlist_name_char[playlist_name.length()+1];
     //strcpy( playlist_name_char,playlist_name.c_str());
     /*  char *Hist_title;
       ME_helium_Playlists playlist;
       ME_helium_Status Crytank_status;
       VertexOffSet_Map OffSetMap;
       int NBinZ;
       int NBinR;
       MnvH1D_Map Hist_MC_Map;
       PlotUtils::MnvH1D* DataHist;*/
       std::vector<double> R_offset_vector;
       std::vector<double> Z_offset_vector;
       std::vector<double> chi_offset_vector;
        std::vector<double> chi_offset_ndf_vector;
       int NBinZ = InputMap.NBinZ;
       int NBinR = InputMap.NBinR;
       //ScaleMC_OffSet1DMap(InputMap , MCtoData_scaler);

       for(int i = 0; i < NBinZ; ++i ){
         for(int j = 0; j < NBinR; ++j ){

           int input_int = CantorPair(i, j);

           double RoffSet = InputMap.OffSetMap[input_int].first;
           double ZoffSet = InputMap.OffSetMap[input_int].second;
           R_offset_vector.push_back(RoffSet);
           Z_offset_vector.push_back(ZoffSet);
           double chi = 0;
           int ndf = 0;

              sprintf(Plot_title, "%s OffSetPlot(Z,R) = (%.2f, %.2f) [mm]", hist_title, ZoffSet, RoffSet);
              //std::cout<<"title of Hist = "<< Plot_title << "Scaling MC by = "<< MCtoData_scaler << std::endl;
              //InputMap.Hist_MC_Map.at(input_int)->Scale(MCtoData_scaler);
              auto hist_COPY = (PlotUtils::MnvH1D*)InputMap.Hist_MC_Map.at(input_int)->Clone("hist_COPY");

              //hist_COPY->Scale(CombinedMCPOT_ScaleEMPTY);
              //DrawCVAndError_FromHistPointer(InputMap.DataHist, "data", xaxislabel,  yaxislabel,
              //  pdf_label, DoBinwidthNorm, MakeXaxisLOG);

              Draw_DataWITHMC_SingleHistinput_withRatio(hist_COPY, InputMap.DataHist,
              playlist_name, pdf_label, Plot_title, "mm",
              xaxislabel,  yaxislabel,  DoBinwidthNorm, MakeXaxisLOG,
              MakeYaxisLOG ,DrawErrors, drawAllErrorGroups, Ymax ,chi, ndf );

              chi_offset_vector.push_back(chi);
              chi_offset_ndf_vector.push_back((chi / (double)ndf));

         }
       }

      auto TGraphR =  MakeTGraph_from_Vectors(chi_offset_vector,  R_offset_vector);
      auto TGraphZ =  MakeTGraph_from_Vectors(chi_offset_vector,  Z_offset_vector);
      auto TGraphR_ndf=  MakeTGraph_from_Vectors(chi_offset_ndf_vector,  R_offset_vector);
      auto TGraphZ_ndf =  MakeTGraph_from_Vectors(chi_offset_ndf_vector,  Z_offset_vector);
      //std::string pdf_string = pdf_label + ".pdf";
      char pdf_charinput[pdf_Chisqrlabel.length()+1];
      strcpy(pdf_charinput,pdf_Chisqrlabel.c_str());
      char pdf_char[1024];
      sprintf(pdf_char , "%s.pdf",pdf_charinput);

      char TGraphTitle[1024];
      sprintf(TGraphTitle , "#chi^{2} vs. Offset R  [%s]", playlist_name);
      DrawTGraph(TGraphR,  "offSet R",  "#chi^{2}", TGraphTitle, "#chi^{2}",
      pdf_char, can, plot, false, false );
      sprintf(TGraphTitle , "#chi^{2}/ndf vs. Offset R  [%s]", playlist_name);
      DrawTGraph(TGraphR_ndf, "offSet R",  "#chi^{2} / ndf", TGraphTitle, "#chi^{2}",
      pdf_char, can, plot, false, false );
      sprintf(TGraphTitle , "#chi^{2} vs. Offset Z [%s]", playlist_name);
      DrawTGraph(TGraphZ,   "offSet Z",  "#chi^{2}", TGraphTitle, "#chi^{2}",
      pdf_char, can, plot, false, false );
      sprintf(TGraphTitle , "#chi^{2}/ndf vs. Offset Z [%s]", playlist_name);
      DrawTGraph(TGraphZ_ndf, "offSet Z",  "#chi^{2} / ndf", TGraphTitle, "#chi^{2}",
      pdf_char, can, plot, false, false );

    }//end of function

///////////////////
void Draw_Single_playlist_1D_VertexShifts(ME_playlist_TFileMAP FullMCMap, Pot_MapList FullMC_scalerMap,
                          ME_playlist_TFileMAP EmptyMCMap,                Pot_MapList EmptyMC_scalerMap,
                          ME_playlist_TFileMAP FullDataMap,               Pot_MapList FullData_scalerMap,
                          ME_playlist_TFileMAP EmptyDataMap,              Pot_MapList EmptyData_scalerMap,
   const char *histoName_MC, const char *histoName_data, std::string units, std::string pdf_label, std::string pdf_Chisqrlabel, char* hist_title,
   char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG, bool MakeYaxisLOG, bool DrawallErrorGroups,
   double NegZ_offset, double PosZ_offset, int NumZSteps, double NegR_offset, double PosR_offset,  int NumRSteps, double Empty_yMax, TCanvas *can, MnvPlotter *plot
 ){


   Pot_MapStatusList POTMAP_TOTAL =  Constuct_TOTALPOT_cryostatusMap(FullMC_scalerMap, EmptyMC_scalerMap, FullData_scalerMap, EmptyData_scalerMap);
   Pot_MapStatusList POTMAP_TOTAL_scaler = MakeScaler_TOTALPOT_cryostatusMapTOFULLDATA(POTMAP_TOTAL);

   VertexOffSet_Map OffSetMAP;
   FillOffSetMap(OffSetMAP,  NegZ_offset,  PosZ_offset, NumZSteps, NegR_offset,  PosR_offset,  NumRSteps );

   std::cout<<"Printing OffSet map"<< std::endl;
   typename std::map<int, std::pair<double, double>>::const_iterator dog;
   for ( dog = OffSetMAP.begin(); dog != OffSetMAP.end();++dog)
   {
   std::cout<<" index = "  << " key = " << dog->first << "  OffSet (R, Z) =  (" << dog->second.first << ", " << dog->second.second<< " ) "<<std::endl;

   }

   std::vector<OffSet1DMap> OffSet_vector_EMPTY = Constuct_OffSet1DMap_Vector(EmptyMCMap, EmptyDataMap,
                                                     histoName_MC, histoName_data, hist_title,  OffSetMAP,
                                                     NumZSteps, NumRSteps );

OffSet1DMap  OffSetCombinedMap = Combined_OffSet1DMap_Vector(OffSet_vector_EMPTY, kME1G, "OffSetCombinedMap", NumZSteps, NumRSteps , false );
                                                //     double ScaleMC
  ScaleMC_OffSet1DMap(OffSetCombinedMap , POTMAP_TOTAL_scaler[kMC_EMPTY]); // Scale the combined Empty
  ScaleData_OffSet1DMap(OffSetCombinedMap, POTMAP_TOTAL_scaler[kDATA_EMPTY]); // Scale Empty to full

  for(auto cat : OffSet_vector_EMPTY){

    DrawSinglePlaylist_OffSet1DPlot(can, plot, cat, units,  pdf_label,pdf_Chisqrlabel, hist_title,
       xaxislabel, yaxislabel, EmptyMC_scalerMap, EmptyData_scalerMap, Empty_yMax);

  }


  DrawSinglePlaylist_OffSet1DPlot_Combined(can, plot, OffSetCombinedMap, units,  pdf_label,pdf_Chisqrlabel, hist_title,
     xaxislabel, yaxislabel,"Combined Empty", Empty_yMax * 4);




   }//end of function


   //////////////////////////////////////////////////////
   //
   /////////////////////////////////////////////////////
