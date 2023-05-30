#include "CryoTank_EmptyHelium_Fit.h"
//////////////////////////////////////////////////////////////////////////////
/*void Point_to_XYZR_MC_Material(Material_type_MnvH1D_Map &Map, std::string BaseName,  int i , int j, int k );
void FillFitHistName_Map_cryoregions(Material_type_MnvH1D_Map &histMap_upstream,
                                    Material_type_MnvH1D_Map &histMap_barrel,
                                    Material_type_MnvH1D_Map &histMap_downstream,
                                    Material_type_MnvH1D_Map &histMap_downstreamconcave,
     std::string ExtraTag, int i , int j, int k);*/
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
MnvPlotter *mnv_plotter = new MnvPlotter();
 char text_title_pdf1[2024];
 char text_title_pdf2[2024];
 char text_title_pdf3[2024];
 char text_title_pdf4[2024];
 char chisqrt_title_pdf1[2024];
 char chisqrt_title_pdf2[2024];
 char chisqrt_title_pdf3[2024];
 char chisqrt_title_pdf4[2024];


time_t now = time(0);
tm *ltm = localtime(&now);
char timeset[2024];
char timeset_nonstacks[2024];
std::string SysError_printLabel = PrintLabel_Systematics(Print_Systematics);
auto Playlist_names =  MakePlaylistString(kMEPlayList_Vector);
sprintf(timeset_nonstacks,"%i_%i_%i_%i_%s_%s", 1 + ltm->tm_mon,ltm->tm_mday, ltm->tm_hour,ltm->tm_min, SysError_printLabel.c_str(), Playlist_names.c_str());
sprintf(timeset, "%i_%i_%i_%i", 1 + ltm->tm_mon,ltm->tm_mday, ltm->tm_hour,ltm->tm_min);

sprintf(text_title_pdf1, "Plots_CryoVertex_Fitting_XYShiftsWithConvolution_Empty_NuMELog_XY.pdf(" );
can -> Print(text_title_pdf1  );
sprintf(text_title_pdf2, "Plots_CryoVertex_Fitting_XYShiftsWithConvolution_Empty_NuMELog_XY.pdf" );
sprintf(text_title_pdf3, "Plots_CryoVertex_Fitting_XYShiftsWithConvolution_Empty_NuMELog_XY.pdf)" );
sprintf(text_title_pdf4, "Plots_CryoVertex_Fitting_XYShiftsWithConvolution_Empty_NuMELog_XY" );
std::string PDF_label(text_title_pdf4);

sprintf(chisqrt_title_pdf1, "Plots_CryoVertex_OffSet_ChiSqrt_Convolution_LogChi_vertexXY_new.pdf(" );
can -> Print(chisqrt_title_pdf1);
sprintf(chisqrt_title_pdf2, "Plots_CryoVertex_OffSet_ChiSqrt_Convolution_LogChi_vertexXY_new.pdf" );
sprintf(chisqrt_title_pdf3, "Plots_CryoVertex_OffSet_ChiSqrt_Convolution_LogChi_vertexXY_new.pdf)" );
sprintf(chisqrt_title_pdf4, "Plots_CryoVertex_OffSet_ChiSqrt_Convolution_LogChi_vertexXY_new" );


ME_playlist_RootPathMAP MAP_RootPath_Empty_MC;
ME_playlist_RootPathMAP MAP_RootPath_OtherEmpty_MC;
ME_playlist_RootPathMAP MAP_RootPath_Full_MC;

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


auto PlaylistME_1G_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1G_MC_StatsONLYErrors_OFFSET_ConvolutionXY_XYShift.root";
auto PlaylistME_1A_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1A_MC_StatsONLYErrors_OFFSET_ConvolutionXY_XYShift.root";
auto PlaylistME_1L_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1L_MC_StatsONLYErrors_OFFSET_ConvolutionXY_XYShift.root";
auto PlaylistME_1M_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1M_MC_StatsONLYErrors_OFFSET_ConvolutionXY_XYShift.root";
auto PlaylistME_1N_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1N_MC_StatsONLYErrors_OFFSET_ConvolutionXY_XYShift.root";
MAP_RootPath_Empty_MC.insert(std::make_pair(kMEPlayList_Vector.at(0), PlaylistME_1G_MC_path));
MAP_RootPath_Empty_MC.insert(std::make_pair(kMEPlayList_Vector.at(1), PlaylistME_1A_MC_path));
MAP_RootPath_Empty_MC.insert(std::make_pair(kMEPlayList_Vector.at(2), PlaylistME_1L_MC_path));
MAP_RootPath_Empty_MC.insert(std::make_pair(kMEPlayList_Vector.at(3), PlaylistME_1M_MC_path));
MAP_RootPath_Empty_MC.insert(std::make_pair(kMEPlayList_Vector.at(4), PlaylistME_1N_MC_path));


/////////////////
/// Data
/////////////////
/////////////////
// Empty
/////////////////
auto PlaylistME_1G_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1G_Data_SideBand.root";
auto PlaylistME_1A_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1A_Data_SideBand.root";
auto PlaylistME_1L_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1L_Data_SideBand.root";
auto PlaylistME_1M_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1M_Data_SideBand.root";
auto PlaylistME_1N_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1N_Data_SideBand.root";
//////////////////
MAP_RootPath_Empty_DATA.insert(std::make_pair(kMEPlayList_Vector.at(0), PlaylistME_1G_Data_path));
MAP_RootPath_Empty_DATA.insert(std::make_pair(kMEPlayList_Vector.at(1), PlaylistME_1A_Data_path));
MAP_RootPath_Empty_DATA.insert(std::make_pair(kMEPlayList_Vector.at(2), PlaylistME_1L_Data_path));
MAP_RootPath_Empty_DATA.insert(std::make_pair(kMEPlayList_Vector.at(3), PlaylistME_1M_Data_path));
MAP_RootPath_Empty_DATA.insert(std::make_pair(kMEPlayList_Vector.at(4), PlaylistME_1N_Data_path));
////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
auto PlaylistME_1P_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1P_Data_SideBand.root";
auto PlaylistME_1C_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1C_Data_SideBand.root";
auto PlaylistME_1D_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1D_Data_SideBand.root";
auto PlaylistME_1F_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1F_Data_SideBand.root";
auto PlaylistME_1E_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1E_Data_SideBand.root";
///minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1A_MC_StatsONLYErrors_OFFSET_Alwgt.root
////////////////////
MAP_RootPath_Full_DATA.insert(std::make_pair(kMEPlayList_Vector.at(5), PlaylistME_1P_Data_path));
MAP_RootPath_Full_DATA.insert(std::make_pair(kMEPlayList_Vector.at(6), PlaylistME_1C_Data_path));
MAP_RootPath_Full_DATA.insert(std::make_pair(kMEPlayList_Vector.at(7), PlaylistME_1D_Data_path));
MAP_RootPath_Full_DATA.insert(std::make_pair(kMEPlayList_Vector.at(8), PlaylistME_1F_Data_path));
MAP_RootPath_Full_DATA.insert(std::make_pair(kMEPlayList_Vector.at(9), PlaylistME_1E_Data_path));



Pot_MapList EmptyPOT_local_MC_MAP = Constuct_POT_playlistMap(MAP_RootPath_Empty_MC, true);
//Pot_MapList FullPOT_local_MC_MAP  = Constuct_POT_playlistMap(MAP_RootPath_Full_MC, true);
Pot_MapList EmptyPOT_local_Data_MAP = Constuct_POT_playlistMap(MAP_RootPath_Empty_DATA, false);
Pot_MapList FullPOT_local_Data_MAP  = Constuct_POT_playlistMap(MAP_RootPath_Full_DATA, false);

//PlotUtils::POTCounter *PotCounter_Object; // unsure why the plotulits pot function isn't work need to revist

//Pot_MapList EmptyPOT_MC_MAP = Constuct_POT_playlistMap(PotCounter_Object, MAP_RootPath_OtherEmpty_MC);
//Pot_MapList FullPOT_MC_MAP = Constuct_POT_playlistMap(PotCounter_Object, MAP_RootPath_Full_MC);
ME_playlist_TFileMAP EmptyTFile_Map_MC;

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


double NegZ_offset = -80.0; //30.0;
double PosZ_offset = 80.0; //48.0;
int NumZSteps = 80; //6; // steps of 4mm

double NegX_offset = -25.0;
double PosX_offset =  25.0;
int NumXSteps = 25;  // // steps of 4mm

double NegY_offset = -25.0;
double PosY_offset = 25.0;
int NumYSteps = 25; //  // steps of 4mm


const int Zsteps = 1;//NumZSteps+1;

//int NBinZ =NumZSteps;
std::vector<double> X_offsetVector = MakeBinVector(NumXSteps, NegX_offset, PosX_offset); // i
std::vector<double> Y_offsetVector = MakeBinVector(NumYSteps, NegY_offset, PosY_offset); // j

int NBinX =NumXSteps;
int NBinY = NumYSteps;

XYZ_VertexOffSet_Map OffSetMapXYZ;
//XYZ_VertexOffSet_Map OffSetMapZ;
typename std::map<Index3, Vertex_XYZ>::const_iterator offsetmap_IT;
//FillXYZOffSetMap(OffSetMapXYZ, NegX_offset, PosX_offset, NumXSteps, NegY_offset, PosY_offset,  NumYSteps, NegZ_offset, PosZ_offset, NumZSteps, true );
FillXYZOffSetMapconstantZ(OffSetMapXYZ, NegX_offset, PosX_offset, NumXSteps, NegY_offset, PosY_offset,  NumYSteps, 0.0 ,  true);
//FillXYZOffSetMapconstantXY(OffSetMapXYZ, -24.0, -32.0, NegZ_offset, PosZ_offset, NumZSteps, true);

int mapcount=0;
typename std::map<Index3, Vertex_XYZ>::const_iterator dog;
for ( dog = OffSetMapXYZ.begin(); dog != OffSetMapXYZ.end();++dog)
{
std::cout<<" index = " << mapcount << " key (i,j,k) =  (" << dog->first.i <<" , "<< dog->first.j<< " , "<< dog->first.k  <<")   OffSet (x, y, z) =  (" << dog->second.x << ", " << dog->second.y<< " , "<< dog->second.z <<" ) "<<std::endl;
mapcount++;
}

//NegZ_offset = 150.0;
//PosZ_offset = -150.0;
//NumZSteps = 60; // steps of 5mm
//AddZOffSettoSetMap(OffSetMapZ, 0.0, 0.0, NegZ_offset, PosZ_offset, NumZSteps );
FitHistName_Map HistName_Map;
//Index3 ZeroShift = GetindexZeroShift(OffSetMapXYZ);
Index3 ZeroShift{27 , 27 , 27};
//Index3 ZeroShift{32 , 32 , 32};
std::vector<double> Chi_sqrt_zeroshift_before;
std::vector<double> Chi_sqrt_zeroshift_after;

MnvH2D *h_Chisqrt_X_before[Zsteps+1];
MnvH2D *h_Chisqrt_Y_before[Zsteps+1];
MnvH2D *h_Chisqrt_Z_before[Zsteps+1];
MnvH2D *h_Chisqrt_R_before[Zsteps+1];
MnvH2D *h_Chisqrt_Combined_before[Zsteps+1];
MnvH2D *h_Chisqrt_X_after[Zsteps+1];
MnvH2D *h_Chisqrt_Y_after[Zsteps+1];
MnvH2D *h_Chisqrt_Z_after[Zsteps+1];
MnvH2D *h_Chisqrt_R_after[Zsteps+1];
MnvH2D *h_Chisqrt_Combined_after[Zsteps+1];
MnvH2D *h_Chisqrt_X_Y_after[Zsteps+1];
double chiX_Before[Zsteps+1];
double chiY_Before[Zsteps+1];
double chiZ_Before[Zsteps+1];
double chiR_Before[Zsteps+1];
double chiTotal_Before[Zsteps+1];
double chiX_After[Zsteps+1];
double chiY_After[Zsteps+1];
double chiZ_After[Zsteps+1];
double chiR_After[Zsteps+1];
double chiTotal_After[Zsteps+1];
std::string x_offset_string;
std::string y_offset_string;
std::string z_offset_string;
std::string title_string;
std::string Total_Chi_Before;
std::string Total_Chi_After;
Array2D(h_Chisqrt_X_before, Zsteps+1, "h_Chisqrt_X_before", "h_Chisqrt_X_before", X_offsetVector, Y_offsetVector);
Array2D(h_Chisqrt_Y_before, Zsteps+1, "h_Chisqrt_Y_before", "h_Chisqrt_Y_before", X_offsetVector, Y_offsetVector);
Array2D(h_Chisqrt_Z_before, Zsteps+1, "h_Chisqrt_Z_before", "h_Chisqrt_Z_before", X_offsetVector, Y_offsetVector);
Array2D(h_Chisqrt_R_before, Zsteps+1, "h_Chisqrt_R_before", "h_Chisqrt_R_before", X_offsetVector, Y_offsetVector);
Array2D(h_Chisqrt_Combined_before, Zsteps+1, "h_Chisqrt_Combined_before", "h_Chisqrt_Combined_before", X_offsetVector, Y_offsetVector);
Array2D(h_Chisqrt_X_after, Zsteps+1, "h_Chisqrt_X_after", "h_Chisqrt_X_after", X_offsetVector, Y_offsetVector);
Array2D(h_Chisqrt_Y_after, Zsteps+1, "h_Chisqrt_Y_after", "h_Chisqrt_Y_after", X_offsetVector, Y_offsetVector);
Array2D(h_Chisqrt_Z_after, Zsteps+1, "h_Chisqrt_Z_after", "h_Chisqrt_Z_after", X_offsetVector, Y_offsetVector);
Array2D(h_Chisqrt_R_after, Zsteps+1, "h_Chisqrt_R_after", "h_Chisqrt_R_after", X_offsetVector, Y_offsetVector);

Array2D(h_Chisqrt_Combined_after, Zsteps+1, "h_Chisqrt_Combined_after", "h_Chisqrt_Combined_after", X_offsetVector, Y_offsetVector);

Array2D(h_Chisqrt_X_Y_after, Zsteps+1, "h_Chisqrt_X_Y_after", "h_Chisqrt_X_Y_after", X_offsetVector, Y_offsetVector);

double error_onfit = 999;


//MnvH2D *h_Chisqrt_X_before    =    new MnvH2D("h_Chisqrt_X_before", "h_Chisqrt_X_before",  X_offsetVector.size()-1,  X_offsetVector.data(),Y_offsetVector.size()-1, Y_offsetVector.data()  );
//MnvH2D *h_Chisqrt_Y_before    =    new MnvH2D("h_Chisqrt_Y_before", "h_Chisqrt_Y_before",  X_offsetVector.size()-1,  X_offsetVector.data(),Y_offsetVector.size()-1, Y_offsetVector.data()  );
//MnvH2D *h_Chisqrt_Z_before    =    new MnvH2D("h_Chisqrt_Z_before", "h_Chisqrt_Z_before",  X_offsetVector.size()-1,  X_offsetVector.data(),Y_offsetVector.size()-1, Y_offsetVector.data()  );
//MnvH2D *h_Chisqrt_R_before    =    new MnvH2D("h_Chisqrt_R_before", "h_Chisqrt_R_before",  X_offsetVector.size()-1,  X_offsetVector.data(),Y_offsetVector.size()-1, Y_offsetVector.data()  );
//MnvH2D *h_Chisqrt_Combined_before    =    new MnvH2D("h_Chisqrt_Combined_before", "h_Chisqrt_Combined_before",  X_offsetVector.size()-1,  X_offsetVector.data(),Y_offsetVector.size()-1, Y_offsetVector.data()  );



//MnvH2D *h_Chisqrt_X_before_ndf    =    new MnvH2D("h_Chisqrt_X_before_ndf", "h_Chisqrt_X_before_ndf",  X_offsetVector.size()-1,  X_offsetVector.data(),Y_offsetVector.size()-1, Y_offsetVector.data()  );
//MnvH2D *h_Chisqrt_Y_before_ndf    =    new MnvH2D("h_Chisqrt_Y_before_ndf", "h_Chisqrt_Y_before_ndf",  X_offsetVector.size()-1,  X_offsetVector.data(),Y_offsetVector.size()-1, Y_offsetVector.data()  );
//MnvH2D *h_Chisqrt_Z_before_ndf    =    new MnvH2D("h_Chisqrt_Z_before_ndf", "h_Chisqrt_Z_before_ndf",  X_offsetVector.size()-1,  X_offsetVector.data(),Y_offsetVector.size()-1, Y_offsetVector.data()  );
//MnvH2D *h_Chisqrt_R_before_ndf    =    new MnvH2D("h_Chisqrt_R_before_ndf", "h_Chisqrt_R_before_ndf",  X_offsetVector.size()-1,  X_offsetVector.data(),Y_offsetVector.size()-1, Y_offsetVector.data()  );
//MnvH2D *h_Chisqrt_Combined_before_ndf    =    new MnvH2D("h_Chisqrt_Combined_before_ndf", "h_Chisqrt_Combined_before_ndf",  X_offsetVector.size()-1,  X_offsetVector.data(),Y_offsetVector.size()-1, Y_offsetVector.data()  );


//MnvH2D *h_Chisqrt_X_after    =    new MnvH2D("h_Chisqrt_X_after", "h_Chisqrt_X_after",  X_offsetVector.size()-1,  X_offsetVector.data(),Y_offsetVector.size()-1, Y_offsetVector.data()  );
//MnvH2D *h_Chisqrt_Y_after    =    new MnvH2D("h_Chisqrt_Y_after", "h_Chisqrt_Y_after",  X_offsetVector.size()-1,  X_offsetVector.data(),Y_offsetVector.size()-1, Y_offsetVector.data()  );
//MnvH2D *h_Chisqrt_Z_after    =    new MnvH2D("h_Chisqrt_Z_after", "h_Chisqrt_Z_after",  X_offsetVector.size()-1,  X_offsetVector.data(),Y_offsetVector.size()-1, Y_offsetVector.data()  );
//MnvH2D *h_Chisqrt_R_after    =    new MnvH2D("h_Chisqrt_R_after", "h_Chisqrt_R_after",  X_offsetVector.size()-1,  X_offsetVector.data(),Y_offsetVector.size()-1, Y_offsetVector.data()  );
//MnvH2D *h_Chisqrt_Combined_after    =    new MnvH2D("h_Chisqrt_Combined_after", "h_Chisqrt_Combined_after",  X_offsetVector.size()-1,  X_offsetVector.data(),Y_offsetVector.size()-1, Y_offsetVector.data()  );

//MnvH2D *h_Chisqrt_X_after_ndf    =    new MnvH2D("h_Chisqrt_X_after_ndf", "h_Chisqrt_X_after_ndf",  X_offsetVector.size()-1,  X_offsetVector.data(),Y_offsetVector.size()-1, Y_offsetVector.data()  );
//MnvH2D *h_Chisqrt_Y_after_ndf    =    new MnvH2D("h_Chisqrt_Y_after_ndf", "h_Chisqrt_Y_after_ndf",  X_offsetVector.size()-1,  X_offsetVector.data(),Y_offsetVector.size()-1, Y_offsetVector.data()  );
//MnvH2D *h_Chisqrt_Z_after_ndf    =    new MnvH2D("h_Chisqrt_Z_after_ndf", "h_Chisqrt_Z_after_ndf",  X_offsetVector.size()-1,  X_offsetVector.data(),Y_offsetVector.size()-1, Y_offsetVector.data()  );
//MnvH2D *h_Chisqrt_R_after_ndf    =    new MnvH2D("h_Chisqrt_R_after_ndf", "h_Chisqrt_R_after_ndf",  X_offsetVector.size()-1,  X_offsetVector.data(),Y_offsetVector.size()-1, Y_offsetVector.data()  );
//MnvH2D *h_Chisqrt_Combined_after_ndf    =    new MnvH2D("h_Chisqrt_Combined_after_ndf", "h_Chisqrt_Combined_after_ndf",  X_offsetVector.size()-1,  X_offsetVector.data(),Y_offsetVector.size()-1, Y_offsetVector.data()  );


//MnvH2D *h_Chisqrt_X_ndf    =    new MnvH2D("h_Chisqrt_X_ndf", "h_Chisqrt_X_ndf",  X_offsetVector.size()-1,  X_offsetVector.data(),Y_offsetVector.size()-1, Y_offsetVector.data()  );
//MnvH2D *h_Chisqrt_Y_ndf    =    new MnvH2D("h_Chisqrt_Y_ndf", "h_Chisqrt_Y_ndf",  X_offsetVector.size()-1,  X_offsetVector.data(),Y_offsetVector.size()-1, Y_offsetVector.data()  );
//MnvH2D *h_Chisqrt_Z_ndf    =    new MnvH2D("h_Chisqrt_Z_ndf", "h_Chisqrt_Z_ndf",  X_offsetVector.size()-1,  X_offsetVector.data(),Y_offsetVector.size()-1, Y_offsetVector.data()  );
//MnvH2D *h_Chisqrt_R_ndf    =    new MnvH2D("h_Chisqrt_R_ndf", "h_Chisqrt_R_ndf",  X_offsetVector.size()-1,  X_offsetVector.data(),Y_offsetVector.size()-1, Y_offsetVector.data()  );


//MnvH2D *h_Al_wgt_upstream             =    new MnvH2D("h_Al_wgt_upstream",          "h_Al_wgt_upstream",          X_offsetVector.size()-1,  X_offsetVector.data(),Y_offsetVector.size()-1, Y_offsetVector.data()  );
//MnvH2D *h_Al_wgt_barrel               =    new MnvH2D("h_Al_wgt_barrel",            "h_Al_wgt_barrel",            X_offsetVector.size()-1,  X_offsetVector.data(),Y_offsetVector.size()-1, Y_offsetVector.data()  );
//MnvH2D *h_Al_wgt_downstream           =    new MnvH2D("h_Al_wgt_downstream",        "h_Al_wgt_downstream",        X_offsetVector.size()-1,  X_offsetVector.data(),Y_offsetVector.size()-1, Y_offsetVector.data()  );
//MnvH2D *h_Al_wgt_downstreamconcave    =    new MnvH2D("h_Al_wgt_downstreamconcave", "h_Al_wgt_downstreamconcave", X_offsetVector.size()-1,  X_offsetVector.data(),Y_offsetVector.size()-1, Y_offsetVector.data()  );



double bins_X = 12;
double bins_Y = 12;
double bins_Z = 13;
double bins_R = 15;

double npars = 4;

double bins_X_ndf =  bins_X - npars;
double bins_Y_ndf =  bins_Y - npars;
double bins_Z_ndf =  bins_Z - npars;
double bins_R_ndf =  bins_R - npars;

double total_ndf = bins_X_ndf + bins_Y_ndf + bins_Z_ndf + bins_R_ndf;

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
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//kME1P,kME1C,kME1D,kME1E,kME1F,kME1A,kME1G,kME1L,kME1M,kME1N

int FitEmpty= 0;
std::vector< ME_helium_Playlists> EmptyPlayList_Vector;
EmptyPlayList_Vector.push_back(kMEPlayList_Vector.at(0));
EmptyPlayList_Vector.push_back(kMEPlayList_Vector.at(1));
EmptyPlayList_Vector.push_back(kMEPlayList_Vector.at(2));
EmptyPlayList_Vector.push_back(kMEPlayList_Vector.at(3));
EmptyPlayList_Vector.push_back(kMEPlayList_Vector.at(4));


std::vector< ME_helium_Playlists> FullPlayList_Vector;
FullPlayList_Vector.push_back(kMEPlayList_Vector.at(5));
FullPlayList_Vector.push_back(kMEPlayList_Vector.at(6));
FullPlayList_Vector.push_back(kMEPlayList_Vector.at(7));
FullPlayList_Vector.push_back(kMEPlayList_Vector.at(8));
FullPlayList_Vector.push_back(kMEPlayList_Vector.at(9));

std::cout<<"Starting: Helium_3CryoRegionsSideBandTool"<< std::endl;

Helium_3CryoRegionsSideBandTool Helium3SideBand_Tool_EmptyPlaylist(
EmptyTFile_Map_MC,
EmptyTFile_Map_Data,
EmptyPOT_local_Data_MAP,
EmptyPOT_local_MC_MAP,
FullPOT_local_Data_MAP
);

std::cout<<"Finished : Helium_3CryoRegionsSideBandTool"<< std::endl;

Helium3SideBand_Tool_EmptyPlaylist.InputPDFLabel(PDF_label);

Helium3SideBand_Tool_EmptyPlaylist.init_Tool_CompleteEmptyplaylist(EmptyPlayList_Vector, FullPlayList_Vector);
std::cout<<"Starting : init_Tool_CompleteEmptyplaylist"<< std::endl;
//Helium3SideBand_Tool_EmptyPlaylist.POTScale_New_Fit_EmptyDataHist();
//Helium3SideBand_Tool_EmptyPlaylist.initSideBands_EmptyDataplaylist(kMEPlayList_Vector.at(2));
std::cout<<"Starting : init_EMPTY_Combined_MCShifted_SideBand_FitHistograms"<< std::endl;
Helium3SideBand_Tool_EmptyPlaylist.init_EMPTY_Combined_MCShifted_SideBand_FitHistograms(ZeroShift.i , ZeroShift.j, ZeroShift.k); //const ME_helium_Playlists Empty_Playlist
std::cout<<"Finished : init_EMPTY_Combined_MCShifted_SideBand_FitHistograms"<< std::endl;

std::cout<<"Starting  :POTScale_New_Fit_EmptyMCHist"<< std::endl;

Helium3SideBand_Tool_EmptyPlaylist.POTScale_New_Fit_EmptyMCHist();
//std::cout<<"finished scaling"<<std::endl;
double chiX_zeroshift_1; double chiY_zeroshift_1; double chiZ_zeroshift_1; double chiR_zeroshift_1;
Helium3SideBand_Tool_EmptyPlaylist.GetEMPTYChiSqt_FitParmsBefore(chiX_zeroshift_1, chiY_zeroshift_1, chiZ_zeroshift_1, chiR_zeroshift_1);
//std::cout<<"chiZ_Before = "<< chiZ_Before<<std::endl;
title_string = "before : Shift = (0, 0, 0) [Convolution Applied][noFid]";

Chi_sqrt_zeroshift_before.push_back(chiX_zeroshift_1);
Chi_sqrt_zeroshift_before.push_back(chiY_zeroshift_1);
Chi_sqrt_zeroshift_before.push_back(chiZ_zeroshift_1);
Chi_sqrt_zeroshift_before.push_back(chiR_zeroshift_1);

Helium3SideBand_Tool_EmptyPlaylist.PlotCurrent_init_EmptyHist(title_string, "All");
SetHelium3SideBandTool(Helium3SideBand_Tool_EmptyPlaylist);

std::vector<double> wgt_vector;
std::vector<double> wgt_error_vector;
std::cout<<"about to apply Fit"<<std::endl;

FitSideBands(Helium3SideBand_Tool_EmptyPlaylist, 7,
  "fourbandFit","fourbandFit", PDF_label,  wgt_vector, wgt_error_vector, error_onfit);

std::cout<<"Finished Fit"<<std::endl;

Helium3SideBand_Tool_EmptyPlaylist.Fill_Alwgt(wgt_vector, wgt_error_vector );
Helium3SideBand_Tool_EmptyPlaylist.ApplyFitResults_toFitParmsOnly_Empty();

Helium3SideBand_Tool_EmptyPlaylist.GetEMPTYChiSqt_FitParmsAfter(chiX_zeroshift_1, chiY_zeroshift_1, chiZ_zeroshift_1, chiR_zeroshift_1);
Chi_sqrt_zeroshift_after.push_back(chiX_zeroshift_1);
Chi_sqrt_zeroshift_after.push_back(chiY_zeroshift_1);
Chi_sqrt_zeroshift_after.push_back(chiZ_zeroshift_1);
Chi_sqrt_zeroshift_after.push_back(chiR_zeroshift_1);
title_string = "After : Shift = (0, 0, 0) [Convolution Applied][noFid]";
Helium3SideBand_Tool_EmptyPlaylist.Plot_AfterFit_EMPTY_Hist(title_string, "All");

wgt_vector.clear();
wgt_error_vector.clear();
Helium3SideBand_Tool_EmptyPlaylist.Clear_Al_wgt();
/*
double LeastChisqt_X_before = 99999; Index3 least_Xbefore;
double LeastChisqt_Y_before = 99999; Index3 least_Ybefore;
double LeastChisqt_Z_before = 99999; Index3 least_Zbefore;
double LeastChisqt_R_before = 99999; Index3 least_Rbefore;

double LeastChisqt_Combined_before = 999999; Index3 least_combinedbefore;
double LeastChisqt_X_after = 99999; Index3 least_Xafter;
double LeastChisqt_Y_after = 99999; Index3 least_Yafter;
double LeastChisqt_Z_after = 99999; Index3 least_Zafter;
double LeastChisqt_R_after = 99999; Index3 least_Rafter;

double LeastChisqt_Combined_after = 999999; Index3 least_combinedafter;
*/
double LeastChisqt_X_before[Zsteps+1];
double LeastChisqt_Y_before[Zsteps+1];
double LeastChisqt_Z_before[Zsteps+1];
double LeastChisqt_R_before[Zsteps+1];
double LeastChisqt_Combined_before[Zsteps+1];
Index3 least_Xbefore[Zsteps+1];
Index3 least_Ybefore[Zsteps+1];
Index3 least_Zbefore[Zsteps+1];
Index3 least_Rbefore[Zsteps+1];
double LeastChisqt_X_after[Zsteps+1];
double LeastChisqt_Y_after[Zsteps+1];
double LeastChisqt_Z_after[Zsteps+1];
double LeastChisqt_R_after[Zsteps+1];
double LeastChisqt_Combined_after[Zsteps+1];
Index3 least_Xafter[Zsteps+1];
Index3 least_Yafter[Zsteps+1];
Index3 least_Zafter[Zsteps+1];
Index3 least_Rafter[Zsteps+1];
Index3 least_combinedbefore[Zsteps+1];
Index3 least_combinedafter[Zsteps+1];


for(int i =0; i < Zsteps+1 ; ++i)
{
  LeastChisqt_X_before[i]=999999;
  LeastChisqt_Y_before[i]=999999;
  LeastChisqt_Z_before[i]=999999;
  LeastChisqt_R_before[i]=999999;
  LeastChisqt_Combined_before[i]=999999;
  LeastChisqt_X_after[i] = 999999;
  LeastChisqt_Y_after[i] = 999999;
  LeastChisqt_Z_after[i] = 999999;
  LeastChisqt_R_after[i] = 999999;
  LeastChisqt_Combined_after[i] = 999999;
  chiX_Before[i] = 999999;
  chiY_Before[i] = 999999;
  chiZ_Before[i] = 999999;
  chiR_Before[i] = 999999;
  chiTotal_Before[i] = 999999;

  chiX_After[i] = 999999;
  chiY_After[i] = 999999;
  chiZ_After[i] = 999999;
  chiR_After[i] = 999999;
  chiTotal_After[i] = 999999;
  least_combinedafter[i]= {12,12,12};
  least_combinedbefore[i]={12,12,12};

}


std::cout<<"Cycle throught Off Set Map"<<std::endl;
int count= 0;

std::vector<double> ChiSqrt_Z_vector_before;
std::vector<double> ChiSqrt_Z_vector_after;

std::vector<double> ChiSqrt_Combined_vector_before;
std::vector<double> ChiSqrt_Combined_vector_after;
std::vector<double> ChiSqrt_Z_R_vector_after;

std::vector<double> ChiSqrt_R_vector_before;
std::vector<double> ChiSqrt_R_vector_after;
std::vector<double> ChiSqrt_X_vector_before;
std::vector<double> ChiSqrt_X_vector_after;
std::vector<double> ChiSqrt_Y_vector_before;
std::vector<double> ChiSqrt_Y_vector_after;
std::vector<double> OffSet_Z_vector;


double LowestChi_X_Y = 535.367;

 mapcount = 0;
std::string title_name;
std::stringstream stream;



std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~Looping throuh vertex X and Y~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;


for (offsetmap_IT = OffSetMapXYZ.begin(); offsetmap_IT != OffSetMapXYZ.end(); ++offsetmap_IT){

  int i = offsetmap_IT->first.i;
  int j = offsetmap_IT->first.j;
  int k = offsetmap_IT->first.k;
  //std::cout << "k = "<< k<<std::endl;

   if(i==27 && j ==27 && k ==27)continue; // skip zeroshift

    if(count%10==0) std::cout << "in Loop count = "<< count << " k = "<< k<< std::endl;

  Helium3SideBand_Tool_EmptyPlaylist.init_EMPTY_Combined_MCShifted_SideBand_FitHistograms(i, j, k);
  Helium3SideBand_Tool_EmptyPlaylist.POTScale_New_Fit_EmptyMCHist();

  //Helium3SideBand_Tool_EmptyPlaylist.GetEMPTYChiSqt_FitParmsBefore(chiX_Before[0], chiY_Before[0], chiZ_Before[0], chiR_Before[0]);
  /*Helium3SideBand_Tool_EmptyPlaylist.GetEMPTY_LOGChiSqt_FitParmsBefore(chiX_Before[1], chiY_Before[1], chiZ_Before[1], chiR_Before[1]);


  //chiTotal_Before[0] = chiX_Before[0] +  chiY_Before[0] +  chiZ_Before[0];
  chiTotal_Before[1] = chiX_Before[1] +  chiY_Before[1] +  chiZ_Before[1];
  //double total_chi_ndf = total_chi / total_ndf;
  //ChiSqrt_Combined_vector_before.push_back(chiTotal_Before[0]);
  //h_Chisqrt_X_before[k]->SetBinContent(i, j, chiX_Before[k]);
  //h_Chisqrt_Y_before[k]->SetBinContent(i, j, chiY_Before[k]);
  //h_Chisqrt_Z_before[k]->SetBinContent(i, j, chiZ_Befores[k]);
  //h_Chisqrt_R_before[k]->SetBinContent(i, j, chiR_Before[k]);
  //h_Chisqrt_Combined_before[k]->SetBinContent(i, j, chiTotal_Before[k]);



  if (LeastChisqt_X_before[0] > chiX_Before[0]) {
    LeastChisqt_X_before[0] = chiX_Before[0];
    least_Xbefore[0] = offsetmap_IT->first;
  }

  if (LeastChisqt_Y_before[0] > chiY_Before[0]) {
    LeastChisqt_Y_before[0] = chiY_Before[0];
    least_Ybefore[0] = offsetmap_IT->first;
  }

  if (LeastChisqt_Z_before[0] > chiZ_Before[0]) {
    LeastChisqt_Z_before[0] = chiZ_Before[0];
    least_Zbefore[0] = offsetmap_IT->first;
  }

  if (LeastChisqt_R_before[0] > chiR_Before[0]) {
    LeastChisqt_R_before[0] = chiR_Before[0];
    least_Rbefore[0] = offsetmap_IT->first;
  }

  if (LeastChisqt_Combined_before[0] > chiTotal_Before[0]) {
    LeastChisqt_Combined_before[0] = chiTotal_Before[0];
    least_combinedbefore[0] = offsetmap_IT->first;
  }

  if (LeastChisqt_Combined_before[1] > chiTotal_Before[1]) {
    LeastChisqt_Combined_before[1] = chiTotal_Before[1];
    least_combinedbefore[1] = offsetmap_IT->first;
  }
*/
/*
  FitSideBands(Helium3SideBand_Tool_EmptyPlaylist, FitEmpty,
    "fourbandFit","fourbandFit", PDF_label,  wgt_vector, wgt_error_vector);

    Helium3SideBand_Tool_EmptyPlaylist.Fill_Alwgt(wgt_vector, wgt_error_vector );
    //h_Al_wgt_upstream->SetBinContent(i, j, wgt_vector.at(0));
    //h_Al_wgt_barrel->SetBinContent(i, j, wgt_vector.at(1));
    //h_Al_wgt_downstream->SetBinContent(i, j, wgt_vector.at(2));
    //h_Al_wgt_downstreamconcave->SetBinContent(i, j, wgt_vector.at(3));

    Helium3SideBand_Tool_EmptyPlaylist.ApplyFitResults_toFitParmsOnly_Empty();
    Helium3SideBand_Tool_EmptyPlaylist.GetEMPTYChiSqt_FitParmsAfter(chiX_After[0], chiY_After[0], chiZ_After[0], chiR_After[0]);
    chiTotal_After[0] = chiX_After[0] + chiY_After[0] + chiZ_After[0];
    double Total_Z_R =  chiZ_After[0] + chiR_After[0];
    double total_after_ndf =  chiTotal_After[0] / total_ndf;

  //  h_Chisqrt_X_after[0]->SetBinContent(i, j, chiTotal_After[0]);
    //h_Chisqrt_Y_after[0]->SetBinContent(i, j, chiY_After[0]);
    //h_Chisqrt_Z_after[k]->SetBinContent(i, j, chiZ_After[k]);
    h_Chisqrt_R_after[0]->SetBinContent(i, j, Total_Z_R);
    h_Chisqrt_Combined_after[0]->SetBinContent(i, j, chiTotal_After[0]);

    //h_Chisqrt_X_after_ndf->SetBinContent(i, j, chiX_After / bins_X_ndf);
    //h_Chisqrt_Y_after_ndf->SetBinContent(i, j, chiY_After / bins_Y_ndf);
    //h_Chisqrt_Z_after_ndf->SetBinContent(i, j, chiZ_After / bins_Z_ndf);
    //h_Chisqrt_R_after_ndf->SetBinContent(i, j, chiR_After / bins_R_ndf);
    //h_Chisqrt_Combined_after_ndf->SetBinContent(i, j, total_after_ndf);

    //ChiSqrt_Combined_vector_after.push_back(chiTotal_After[0]);
    //ChiSqrt_Z_R_vector_after.push_back(Total_Z_R);

    if (LeastChisqt_X_after[0] > chiX_After[0]) {
      LeastChisqt_X_after[0] = chiX_After[0];
      least_Xafter[0] = offsetmap_IT->first;
    }

    if (LeastChisqt_Y_after[0] > chiY_After[0]) {
      LeastChisqt_Y_after[0] = chiY_After[0];
      least_Yafter[0] = offsetmap_IT->first;
    }

    if (LeastChisqt_Z_after[0] > chiZ_After[0]) {
      LeastChisqt_Z_after[0] = chiZ_After[0];
      least_Zafter[0] = offsetmap_IT->first;
    }

    if (LeastChisqt_R_after[0] > Total_Z_R ) {
      LeastChisqt_R_after[0] = Total_Z_R;
      least_Rafter[0] = offsetmap_IT->first;
    }

    if (LeastChisqt_Combined_after[0] > chiTotal_After[0]) {
      LeastChisqt_Combined_after[0] = chiTotal_After[0];
      least_combinedafter[0] = offsetmap_IT->first;
    }


    wgt_vector.clear();
    wgt_error_vector.clear();
    Helium3SideBand_Tool_EmptyPlaylist.Clear_Al_wgt();
*/

    FitSideBands(Helium3SideBand_Tool_EmptyPlaylist, 7,
      "fourbandFit","fourbandFit", PDF_label,  wgt_vector, wgt_error_vector, error_onfit);

      Helium3SideBand_Tool_EmptyPlaylist.Fill_Alwgt(wgt_vector, wgt_error_vector );
      Helium3SideBand_Tool_EmptyPlaylist.ApplyFitResults_toFitParmsOnly_Empty();
      Helium3SideBand_Tool_EmptyPlaylist.GetEMPTYChiSqt_FitParmsAfter(chiX_After[1], chiY_After[1], chiZ_After[1], chiR_After[1]);
      chiTotal_After[1] = chiX_After[1] + chiY_After[1] + chiZ_After[1];
      double chi_x_y = chiX_After[1] + chiY_After[1];
       double Total_Z_R =  chiZ_After[1] + chiR_After[1];
       double norm_X_Y = (chi_x_y - LowestChi_X_Y);


    if(chi_x_y == LowestChi_X_Y){std::cout<<"wowwww"<<std::endl;}

      /*if(offsetmap_IT->second.z > -12 && offsetmap_IT->second.z < 5){

         stream << std::fixed << std::setprecision(1) << offsetmap_IT->second.x;
         x_offset_string = stream.str();
         stream.str(std::string());
         stream << std::fixed << std::setprecision(1) << offsetmap_IT->second.y;
         y_offset_string = stream.str();
         stream.str(std::string());
         stream << std::fixed << std::setprecision(1) << offsetmap_IT->second.z;
         z_offset_string = stream.str();
         stream.str(std::string());

         stream << std::fixed << std::setprecision(1) << chiTotal_After[1];
         Total_Chi_After = stream.str();
         stream.str(std::string());

         title_string = "[noFid]After:[X+Y+Z] Log #chi^{2}_{total} = " + Total_Chi_After   + " | offset[mm] = (" + x_offset_string  +  "," + y_offset_string + "," + z_offset_string + ")";
         Helium3SideBand_Tool_EmptyPlaylist.Plot_AfterFit_EMPTY_Hist(title_string, "All");

       }
*/

       //OffSet_Z_vector.push_back(offsetmap_IT->second.z);
       //ChiSqrt_Z_vector_after.push_back(chiZ_After[1]);
       //ChiSqrt_Combined_vector_after.push_back(chiTotal_After[1]);
       //ChiSqrt_Z_R_vector_after.push_back(Total_Z_R);
       //ChiSqrt_R_vector_after.push_back(chiR_After[1]);
       //ChiSqrt_X_vector_after.push_back(chiX_After[1]);
       //ChiSqrt_Y_vector_after.push_back(chiY_After[1]);

      h_Chisqrt_X_after[1]->SetBinContent(i, j, chiTotal_After[1]);
      h_Chisqrt_Y_after[1]->SetBinContent(i, j, chiY_After[1]);
      h_Chisqrt_Z_after[1]->SetBinContent(i, j, chiZ_After[1]);
      h_Chisqrt_R_after[1]->SetBinContent(i, j, Total_Z_R);
      h_Chisqrt_Combined_after[1]->SetBinContent(i, j, chiTotal_After[1]);
      //h_Chisqrt_X_Y_after[0]->SetBinContent(i, j, chi_x_y);
      h_Chisqrt_X_Y_after[1]->SetBinContent(i, j, chi_x_y);
      h_Chisqrt_X_Y_after[0]->SetBinContent(i, j, norm_X_Y);





      if (LeastChisqt_X_after[1] > chiX_After[1]) {
        LeastChisqt_X_after[1] = chiX_After[1];
        least_Xafter[1] = offsetmap_IT->first;
      }

      if (LeastChisqt_Y_after[1] > chiY_After[1]) {
        LeastChisqt_Y_after[1] = chiY_After[1];
        least_Yafter[1] = offsetmap_IT->first;
      }

      if (LeastChisqt_R_after[1] > Total_Z_R ) {
        LeastChisqt_R_after[1] = Total_Z_R;
        least_Rafter[1] = offsetmap_IT->first;
      }

      if (LeastChisqt_Combined_after[1] > chiTotal_After[1]) {
        LeastChisqt_Combined_after[1] = chiTotal_After[1];
        least_combinedafter[1] = offsetmap_IT->first;
      }


      if (LeastChisqt_Combined_after[2] > chi_x_y) {
        LeastChisqt_Combined_after[2] = chi_x_y;
        least_combinedafter[2] = offsetmap_IT->first;
      }


count++;

wgt_vector.clear();
wgt_error_vector.clear();
Helium3SideBand_Tool_EmptyPlaylist.Clear_Al_wgt();

}



std::cout<<"Finished Loop "<<std::endl;
/// End of Loop


std::cout<<"Writing Hists"<< std::endl;
TFile *outFile = new TFile("Chisqrt_fit_results_XY.root","RECREATE");
/*
for(int k =0; k<Zsteps; k++){

  std::cout<<"writing k = "<< k<<std::endl;
h_Chisqrt_X_before[k]->Write();
h_Chisqrt_Y_before[k]->Write();
h_Chisqrt_Z_before[k]->Write();
h_Chisqrt_R_before[k]->Write();
h_Chisqrt_Combined_before[k]->Write();
h_Chisqrt_X_after[k]->Write();
h_Chisqrt_Y_after[k]->Write();
h_Chisqrt_Z_after[k]->Write();
h_Chisqrt_R_after[k]->Write();
h_Chisqrt_Combined_after[k]->Write();
}
*/

h_Chisqrt_X_after[1]->Write();
h_Chisqrt_Y_after[1]->Write();
h_Chisqrt_Z_after[1]->Write();
h_Chisqrt_R_after[1]->Write();
h_Chisqrt_Combined_after[1]->Write();
h_Chisqrt_X_Y_after[1]->Write();
h_Chisqrt_X_Y_after[0]->Write();

outFile->Close();


char Plot_title[1024];
char xaxislabel[1024];
char yaxislabel[1024];


sprintf(xaxislabel, "Off Set X [mm]");
sprintf(yaxislabel, "Off Set Y [mm]");





/*
for(int k =0; k<Zsteps; k++){

  std::cout<< "Making plots k = "<< k <<std::endl;
  std::cout << "least_combinedbefore[k] index(i,j,k) =  ( " <<  least_combinedbefore[k].i << ", "<< least_combinedbefore[k].j<< ", "<< least_combinedbefore[k].k<< " )" << std::endl;
   std::cout << "least_combinedafter[k] = index(i,j,k) =  ( " <<  least_combinedafter[k].i << ", "<< least_combinedafter[k].j<< ", "<< least_combinedafter[k].k<< " )" << std::endl;
sprintf(Plot_title, " [noFid] #chi^{2} before Combined OffSet X Vs Y [E(All)] Min(X,Y,Z) = (%.2f, %.2f, %.2f) = %.2f [#chi^{2}]",
  OffSetMapXYZ[least_combinedbefore[k]].x, OffSetMapXYZ[least_combinedbefore[k]].y,OffSetMapXYZ[least_combinedbefore[k]].z, LeastChisqt_Combined_before[k]);
Draw2DHist(h_Chisqrt_Combined_before[k],  xaxislabel,  yaxislabel, "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

sprintf(Plot_title, "[noFid] #chi^{2} After Combined OffSet X Vs Y [E(All)] Min(X,Y,Z) = (%.2f, %.2f, %.2f) = %.2f [#chi^{2}]",
  OffSetMapXYZ[least_combinedafter[k]].x, OffSetMapXYZ[least_combinedafter[k]].y, OffSetMapXYZ[least_combinedafter[k]].z, LeastChisqt_Combined_after[k]);
Draw2DHist(h_Chisqrt_Combined_before[k],  xaxislabel,  yaxislabel, "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
*/

int k =0;


//least_combinedafter[0].i = 5;
//least_combinedafter[0].j = 14;
//least_combinedafter[0].k = 0;
/*
stream << std::fixed << std::setprecision(1) << OffSetMapXYZ[least_combinedafter[k]].x;
x_offset_string = stream.str();
stream.str(std::string());
stream << std::fixed << std::setprecision(1) << OffSetMapXYZ[least_combinedafter[k]].y;
y_offset_string = stream.str();
stream.str(std::string());
stream << std::fixed << std::setprecision(1) << OffSetMapXYZ[least_combinedafter[k]].z;
z_offset_string = stream.str();
stream.str(std::string());
stream << std::fixed << std::setprecision(1) << LeastChisqt_Combined_before[k];
Total_Chi_Before = stream.str();
stream.str(std::string());
stream << std::fixed << std::setprecision(1) << LeastChisqt_Combined_after[k];
Total_Chi_After = stream.str();
stream.str(std::string());



Helium3SideBand_Tool_EmptyPlaylist.init_EMPTY_Combined_MCShifted_SideBand_FitHistograms(least_combinedafter[k].i , least_combinedafter[k].j, least_combinedafter[k].k);
Helium3SideBand_Tool_EmptyPlaylist.POTScale_New_Fit_EmptyMCHist();

title_string = "[noFid] Before:#chi^{2}_{X+Y+Z} = " + Total_Chi_Before + " | offset[mm] = (" + x_offset_string  +  "," + y_offset_string + "," + z_offset_string + ")";
Helium3SideBand_Tool_EmptyPlaylist.PlotCurrent_init_EmptyHist(title_string, "All");

FitSideBands(Helium3SideBand_Tool_EmptyPlaylist, FitEmpty,
  "fourbandFit","fourbandFit", PDF_label,  wgt_vector, wgt_error_vector);

Helium3SideBand_Tool_EmptyPlaylist.Fill_Alwgt(wgt_vector, wgt_error_vector );
Helium3SideBand_Tool_EmptyPlaylist.ApplyFitResults_toFitParmsOnly_Empty();
title_string = "[noFid] After:#chi^{2}_{X+Y+Z}" + Total_Chi_After   + " | offset[mm] = (" + x_offset_string  +  "," + y_offset_string + "," + z_offset_string + ")";
Helium3SideBand_Tool_EmptyPlaylist.Plot_AfterFit_EMPTY_Hist(title_string, "All");

wgt_vector.clear();
wgt_error_vector.clear();
Helium3SideBand_Tool_EmptyPlaylist.Clear_Al_wgt();
/////////////
/// Combined R and Z
//////////////



stream << std::fixed << std::setprecision(1) << OffSetMapXYZ[least_Rafter[k]].x;
x_offset_string = stream.str();
stream.str(std::string());
stream << std::fixed << std::setprecision(1) << OffSetMapXYZ[least_Rafter[k]].y;
y_offset_string = stream.str();
stream.str(std::string());
stream << std::fixed << std::setprecision(1) << OffSetMapXYZ[least_Rafter[k]].z;
z_offset_string = stream.str();
stream.str(std::string());
stream << std::fixed << std::setprecision(1) << LeastChisqt_R_before[k];
Total_Chi_Before = stream.str();
stream.str(std::string());
stream << std::fixed << std::setprecision(1) << LeastChisqt_R_after[k];
Total_Chi_After = stream.str();
stream.str(std::string());



  Helium3SideBand_Tool_EmptyPlaylist.init_EMPTY_Combined_MCShifted_SideBand_FitHistograms(least_Rafter[0].i , least_Rafter[0].j, least_Rafter[0].k);
  Helium3SideBand_Tool_EmptyPlaylist.POTScale_New_Fit_EmptyMCHist();

title_string = "[noFid]Before:[R+Z] #chi^{2}_{total} = " + Total_Chi_Before + " | offset[mm] = (" + x_offset_string  +  "," + y_offset_string + "," + z_offset_string + ")";
Helium3SideBand_Tool_EmptyPlaylist.PlotCurrent_init_EmptyHist(title_string, "All");
FitSideBands(Helium3SideBand_Tool_EmptyPlaylist, FitEmpty,
  "fourbandFit","fourbandFit", PDF_label,  wgt_vector, wgt_error_vector);


Helium3SideBand_Tool_EmptyPlaylist.Fill_Alwgt(wgt_vector, wgt_error_vector );
Helium3SideBand_Tool_EmptyPlaylist.ApplyFitResults_toFitParmsOnly_Empty();
title_string = "[noFid]After:[R+Z]  #chi^{2}_{total} = " + Total_Chi_After   + " | offset[mm] = (" + x_offset_string  +  "," + y_offset_string + "," + z_offset_string + ")";
Helium3SideBand_Tool_EmptyPlaylist.Plot_AfterFit_EMPTY_Hist(title_string, "All");


wgt_vector.clear();
wgt_error_vector.clear();
Helium3SideBand_Tool_EmptyPlaylist.Clear_Al_wgt();
/////////////////////////////////////////////////
// Log
/////////////////////////////////////////////////
*/
 k =1;
 //least_combinedafter[1].i = 0;
 //least_combinedafter[1].j = 0;
 //least_combinedafter[1].k = 40;
 //least_Rafter[1].i = 0;
 //least_Rafter[1].j = 0;
 //least_Rafter[1].k = 39;

stream << std::fixed << std::setprecision(1) << OffSetMapXYZ[least_combinedafter[k]].x;
x_offset_string = stream.str();
stream.str(std::string());
stream << std::fixed << std::setprecision(1) << OffSetMapXYZ[least_combinedafter[k]].y;
y_offset_string = stream.str();
stream.str(std::string());
stream << std::fixed << std::setprecision(1) << OffSetMapXYZ[least_combinedafter[k]].z;
z_offset_string = stream.str();
stream.str(std::string());
stream << std::fixed << std::setprecision(1) << LeastChisqt_Combined_before[k];
Total_Chi_Before = stream.str();
stream.str(std::string());
stream << std::fixed << std::setprecision(1) << LeastChisqt_Combined_after[k];
Total_Chi_After = stream.str();
stream.str(std::string());



Helium3SideBand_Tool_EmptyPlaylist.init_EMPTY_Combined_MCShifted_SideBand_FitHistograms(least_combinedafter[k].i , least_combinedafter[k].j, least_combinedafter[k].k);
Helium3SideBand_Tool_EmptyPlaylist.POTScale_New_Fit_EmptyMCHist();

title_string = "[noFid] Before: Log #chi^{2}_{X+Y+Z} = " + Total_Chi_Before + " |offset[mm] = (" + x_offset_string  +  "," + y_offset_string + "," + z_offset_string + ")";
Helium3SideBand_Tool_EmptyPlaylist.PlotCurrent_init_EmptyHist(title_string, "All");

FitSideBands(Helium3SideBand_Tool_EmptyPlaylist, 7,
  "fourbandFit","fourbandFit", PDF_label,  wgt_vector, wgt_error_vector, error_onfit);

Helium3SideBand_Tool_EmptyPlaylist.Fill_Alwgt(wgt_vector, wgt_error_vector );
Helium3SideBand_Tool_EmptyPlaylist.ApplyFitResults_toFitParmsOnly_Empty();
title_string = "[noFid] After:[X+Y+Z] log #chi^{2}_{total}" + Total_Chi_After   + " |offset[mm] = (" + x_offset_string  +  "," + y_offset_string + "," + z_offset_string + ")";
Helium3SideBand_Tool_EmptyPlaylist.Plot_AfterFit_EMPTY_Hist(title_string, "All");

wgt_vector.clear();
wgt_error_vector.clear();
Helium3SideBand_Tool_EmptyPlaylist.Clear_Al_wgt();
/////////////
/// Combined R and Z
//////////////


stream << std::fixed << std::setprecision(1) << OffSetMapXYZ[least_Rafter[k]].x;
x_offset_string = stream.str();
stream.str(std::string());
stream << std::fixed << std::setprecision(1) << OffSetMapXYZ[least_Rafter[k]].y;
y_offset_string = stream.str();
stream.str(std::string());
stream << std::fixed << std::setprecision(1) << OffSetMapXYZ[least_Rafter[k]].z;
z_offset_string = stream.str();
stream.str(std::string());
stream << std::fixed << std::setprecision(1) << LeastChisqt_R_before[k];
Total_Chi_Before = stream.str();
stream.str(std::string());
stream << std::fixed << std::setprecision(1) << LeastChisqt_R_after[k];
Total_Chi_After = stream.str();
stream.str(std::string());



  Helium3SideBand_Tool_EmptyPlaylist.init_EMPTY_Combined_MCShifted_SideBand_FitHistograms(least_Rafter[k].i , least_Rafter[k].j, least_Rafter[k].k);
  Helium3SideBand_Tool_EmptyPlaylist.POTScale_New_Fit_EmptyMCHist();

title_string = "[noFid]Before:[R+Z]log #chi^{2}_{total} = " + Total_Chi_Before + " | offset[mm] = (" + x_offset_string  +  "," + y_offset_string + "," + z_offset_string + ")";
Helium3SideBand_Tool_EmptyPlaylist.PlotCurrent_init_EmptyHist(title_string, "All");
FitSideBands(Helium3SideBand_Tool_EmptyPlaylist, 7,
  "fourbandFit","fourbandFit", PDF_label,  wgt_vector, wgt_error_vector, error_onfit);


Helium3SideBand_Tool_EmptyPlaylist.Fill_Alwgt(wgt_vector, wgt_error_vector );
Helium3SideBand_Tool_EmptyPlaylist.ApplyFitResults_toFitParmsOnly_Empty();
title_string = "[noFid]After:[R+Z] log #chi^{2}_{total} = " + Total_Chi_After   + " | offset[mm] = (" + x_offset_string  +  "," + y_offset_string + "," + z_offset_string + ")";
Helium3SideBand_Tool_EmptyPlaylist.Plot_AfterFit_EMPTY_Hist(title_string, "All");


wgt_vector.clear();
wgt_error_vector.clear();
Helium3SideBand_Tool_EmptyPlaylist.Clear_Al_wgt();


  //can -> Print(text_title_pdf3);
  //can -> Print(chisqrt_title_pdf3);


//std::cout<<"~~~~~~~~~~~~~~~~~~looping throught ~~~~~~~~~~~~~~~ "<<std::endl;
//for(auto cat : ChiSqrt_Z_vector_after){std::cout<<"ChiSqrt_Z_vector_after"<< cat<<endl;}


//sprintf(Plot_title, " Log #chi^{2} after Vertex X OffSet X Vs Y [E(All)] Min(X,Y) = (%.2f, %.2f) = %.2f [#chi^{2}]",
//  OffSetMapXYZ[least_Xafter[1]].x, OffSetMapXYZ[least_Xafter[1]].y, LeastChisqt_X_after[1] );
//Draw2DHist(h_Chisqrt_X_after[1],  xaxislabel,  yaxislabel, "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

//sprintf(Plot_title, " #chi^{2} after Vertex X OffSet X Vs Y [E(All)] Min(X,Y) = (%.2f, %.2f) = %.2f [#chi^{2} / ndf]",
//  OffSetMapXYZ[least_Xafter].x, OffSetMapXYZ[least_Xafter].y, LeastChisqt_X_after / bins_X_ndf );
//Draw2DHist(h_Chisqrt_X_after_ndf,  xaxislabel,  yaxislabel, "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);


//sprintf(Plot_title, " Log #chi^{2} after Vertex Y OffSet X Vs Y [E(All)] Min(X,Y) = (%.2f, %.2f) = %.2f [#chi^{2}]",
// OffSetMapXYZ[least_Yafter[1]].x, OffSetMapXYZ[least_Yafter[1]].y, LeastChisqt_Y_after[1] );
//Draw2DHist(h_Chisqrt_Y_after[1],  xaxislabel,  yaxislabel, "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

//sprintf(Plot_title, " #chi^{2} after Vertex Y OffSet X Vs Y [E(All)] Min(X,Y) = (%.2f, %.2f) = %.2f [#chi^{2} / ndf]",
 //OffSetMapXYZ[least_Yafter].x, OffSetMapXYZ[least_Yafter].y, LeastChisqt_Y_after / bins_Y_ndf );
//Draw2DHist(h_Chisqrt_Y_after_ndf,  xaxislabel,  yaxislabel, "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);


//sprintf(Plot_title, " #chi^{2} after Vertex Z OffSet X Vs Y [E(All)] Min(X,Y) = (%.2f, %.2f) = %.2f [#chi^{2}]",
//  OffSetMapXYZ[least_Zafter].x, OffSetMapXYZ[least_Zafter].y, LeastChisqt_Z_after );
//Draw2DHist(h_Chisqrt_Z_after,  xaxislabel,  yaxislabel, "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
//
//sprintf(Plot_title, " #chi^{2} after Vertex Z OffSet X Vs Y [E(All)] Min(X,Y) = (%.2f, %.2f) = %.2f [#chi^{2} / ndf]",
//  OffSetMapXYZ[least_Zafter].x, OffSetMapXYZ[least_Zafter].y, LeastChisqt_Z_after / bins_Z_ndf );
//Draw2DHist(h_Chisqrt_Z_after_ndf,  xaxislabel,  yaxislabel, "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);


//sprintf(Plot_title, " #chi^{2} OffSet X Vs Y [E(All)] Min(R,Z) = (%.2f, %.2f) = %.2f [#chi^{2}]",
//OffSetMapXYZ[least_Rafter[0]].x, OffSetMapXYZ[least_Rafter[0]].y, LeastChisqt_R_after[0] );
//Draw2DHist(h_Chisqrt_R_after[0],  xaxislabel,  yaxislabel, "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

//sprintf(Plot_title, "Log #chi^{2} OffSet X Vs Y [E(All)] Min(R,Z) = (%.2f, %.2f) = %.2f [#chi^{2}]",
//  OffSetMapXYZ[least_Rafter[1]].x, OffSetMapXYZ[least_Rafter[1]].y, LeastChisqt_R_after[1] );
//Draw2DHist(h_Chisqrt_R_after[1],  xaxislabel,  yaxislabel, "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);



//sprintf(Plot_title, " #chi^{2} after Vertex R OffSet X Vs Y [E(All)] Min(X,Y) = (%.2f, %.2f) = %.2f [#chi^{2} / ndf]",
//  OffSetMapXYZ[least_Rafter].x, OffSetMapXYZ[least_Rafter].y, LeastChisqt_R_after / bins_R_ndf );
//  Draw2DHist(h_Chisqrt_R_after_ndf,  xaxislabel,  yaxislabel, "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);


//sprintf(Plot_title, " #chi^{2} after Combined OffSet X Vs Y [E(All)] Min(X,Y,Z) = (%.2f, %.2f) = %.2f [#chi^{2}]",
//  OffSetMapXYZ[least_combinedafter[0]].x, OffSetMapXYZ[least_combinedafter[0]].y, LeastChisqt_Combined_after[0]);
//Draw2DHist(h_Chisqrt_Combined_after[0],  xaxislabel,  yaxislabel, "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);



sprintf(Plot_title, " Log #chi^{2} after Combined OffSet X Vs Y [E(All)] Min(X,Y,Z) = (%.2f, %.2f) = %.2f [#chi^{2}]",
  OffSetMapXYZ[least_combinedafter[1]].x, OffSetMapXYZ[least_combinedafter[1]].y, LeastChisqt_Combined_after[1]);
Draw2DHist(h_Chisqrt_Combined_after[1],  xaxislabel,  yaxislabel, "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);


sprintf(Plot_title, " X + Y #chi^{2} after Combined OffSet X Vs Y [E(All)] Min(X,Y,Z) = (%.2f, %.2f) = %.2f [#chi^{2}]",
  OffSetMapXYZ[least_combinedafter[1]].x, OffSetMapXYZ[least_combinedafter[1]].y, LeastChisqt_Combined_after[1]);
Draw2DHist(h_Chisqrt_X_Y_after[1],  xaxislabel,  yaxislabel, "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);


sprintf(Plot_title, " Log #chi^{2} after Combined OffSet X Vs Y [E(All)] Min(X,Y,Z) = (#chi^{2} -  #chi_{Min}^{2}) /#chi_{Min}^{2})",
  OffSetMapXYZ[least_combinedafter[2]].x, OffSetMapXYZ[least_combinedafter[2]].y, LeastChisqt_Combined_after[2]);
Draw2DHist(h_Chisqrt_X_Y_after[0],  xaxislabel,  yaxislabel, "(#chi^{2} -  #chi_{Min}^{2}) /#chi_{Min}^{2}) ", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);


sprintf(Plot_title, "Fitted X and Y Shift");

DrawEllipticparaboloidFit(h_Chisqrt_X_Y_after[0], xaxislabel,  yaxislabel, " #chi^{2}",Plot_title, chisqrt_title_pdf2, can, mnv_plotter, -25, 25, -25, 25 );

DrawEllipticparaboloidFit(h_Chisqrt_X_Y_after[1], xaxislabel,  yaxislabel, " #chi^{2}",Plot_title, chisqrt_title_pdf2, can, mnv_plotter, -25, 25, -25, 25 );



//sprintf(Plot_title, " #chi^{2} after Combined OffSet X Vs Y [E(All)] Min(X,Y) = (%.2f, %.2f) = %.2f [#chi^{2} / ndf]",
//  OffSetMapXYZ[least_combinedafter].x, OffSetMapXYZ[least_combinedafter].y, LeastChisqt_Combined_after / total_ndf );
//Draw2DHist(h_Chisqrt_Combined_after_ndf,  xaxislabel,  yaxislabel, "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
/*
sprintf(Plot_title, " [E(All)] Upstream Al wgt from Fit");
Draw2DHist(h_Al_wgt_upstream,  xaxislabel,  yaxislabel, "Al Wgt", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

sprintf(Plot_title, " [E(All)] Barrel Al wgt from Fit");
Draw2DHist(h_Al_wgt_barrel,  xaxislabel,  yaxislabel, "Al Wgt", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

sprintf(Plot_title, " [E(All)] Downstream Al wgt from Fit");
Draw2DHist(h_Al_wgt_downstream,  xaxislabel,  yaxislabel, "Al Wgt", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

sprintf(Plot_title, " [E(All)] Downstream Concave Al wgt from Fit");
Draw2DHist(h_Al_wgt_downstreamconcave,  xaxislabel,  yaxislabel, "Al Wgt", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
*/


//TGraphErrors *TGraph_ChiSqrt_Z_Before =  MakeTGraph_from_VectorsNoErrors(ChiSqrt_Z_vector_before,  OffSet_Z_vector);
//TGraphErrors *TGraph_ChiSqrt_Z_After =  MakeTGraph_from_VectorsNoErrors(ChiSqrt_Z_vector_after,  OffSet_Z_vector);

//TGraphErrors *TGraph_ChiR_Before =  MakeTGraph_from_VectorsNoErrors(ChiSqrt_R_vector_before,  OffSet_Z_vector);
//TGraphErrors *TGraph_ChiR_After =  MakeTGraph_from_VectorsNoErrors(ChiSqrt_R_vector_after,  OffSet_Z_vector);

//TGraphErrors *TGraph_ChiX_Before =  MakeTGraph_from_VectorsNoErrors(ChiSqrt_X_vector_before,  OffSet_Z_vector);
//TGraphErrors *TGraph_ChiX_After =  MakeTGraph_from_VectorsNoErrors(ChiSqrt_X_vector_after,  OffSet_Z_vector);

//TGraphErrors *TGraph_ChiY_Before =  MakeTGraph_from_VectorsNoErrors(ChiSqrt_Y_vector_before,  OffSet_Z_vector);
//TGraphErrors *TGraph_ChiY_After =  MakeTGraph_from_VectorsNoErrors(ChiSqrt_Y_vector_after,  OffSet_Z_vector);

//TGraphErrors *TGraph_Chi_total_Before =  MakeTGraph_from_VectorsNoErrors(ChiSqrt_Combined_vector_before,  OffSet_Z_vector);
//TGraphErrors *TGraph_Chi_total_After =  MakeTGraph_from_VectorsNoErrors(ChiSqrt_Combined_vector_after,  OffSet_Z_vector);

//TGraphErrors *TGraph_Chi_RZ_After =  MakeTGraph_from_VectorsNoErrors(ChiSqrt_Z_R_vector_after,  OffSet_Z_vector);



//DrawTGraph(TGraph_ChiSqrt_Z_After, "OffSet vertex Z [mm]","#chi^{2} Vertex Z ", "After: log #chi^{2} Vertex Z vs OffSet Vector Z [mm]",
//"#chi^{2}", chisqrt_title_pdf2, can, mnv_plotter, false, false );
//
//DrawTGraph(TGraph_ChiR_After, "OffSet vertex Z [mm]","#chi^{2} Vertex R ", "After: log #chi^{2} Vertex R vs OffSet Vector Z [mm]",
//"#chi^{2}", chisqrt_title_pdf2, can, mnv_plotter, false, false );
//
//DrawTGraph(TGraph_ChiX_After, "OffSet vertex Z [mm]","#chi^{2} Vertex X ", "After: log #chi^{2} Vertex X vs OffSet Vector Z [mm]",
//"#chi^{2}", chisqrt_title_pdf2, can, mnv_plotter, false, false );
//
//DrawTGraph(TGraph_ChiY_After, "OffSet vertex Z [mm]","#chi^{2} Vertex Y ", "After: log #chi^{2} Vertex Y vs OffSet Vector Z [mm]",
//"#chi^{2}", chisqrt_title_pdf2, can, mnv_plotter, false, false );
//
//DrawTGraph(TGraph_Chi_total_After, "OffSet vertex Z [mm]","#chi^{2} Combined [X+Y+Z]", "After: log #chi^{2} Combined vs OffSet Vector Z [mm]",
//"#chi^{2}", chisqrt_title_pdf2, can, mnv_plotter, false, false );
//
//DrawTGraph(TGraph_Chi_RZ_After, "OffSet vertex Z [mm]","#chi^{2} Combined [R+Z] ", "After: log #chi^{2} Combined vs OffSet Vector Z [mm]",
//"#chi^{2}", chisqrt_title_pdf2, can, mnv_plotter, false, false );

/*
std::ofstream myfile;
myfile.open("ChisqrtCombined_output_ZLOG.txt");
for(int i= 0; i < OffSet_Z_vector.size() ; ++i){
  myfile << OffSet_Z_vector.at(i)<<" , "<< ChiSqrt_Combined_vector_after.at(i) << "\n";
}

myfile.close();

myfile.open("Chisqrt_R_Z_output_ZLOG.txt");
for(int i= 0; i < OffSet_Z_vector.size() ; ++i){
  myfile << OffSet_Z_vector.at(i)<<" , "<< ChiSqrt_Z_R_vector_after.at(i) << "\n";
}
myfile.close();


myfile.open("Chisqrt_X_output_ZLOG.txt");
for(int i= 0; i < OffSet_Z_vector.size() ; ++i){
  myfile << OffSet_Z_vector.at(i)<<" , "<< ChiSqrt_X_vector_after.at(i) << "\n";
}
myfile.close();

myfile.open("Chisqrt_Y_output_ZLOG.txt");
for(int i= 0; i < OffSet_Z_vector.size() ; ++i){
  myfile << OffSet_Z_vector.at(i)<<" , "<< ChiSqrt_Y_vector_after.at(i) << "\n";
}
myfile.close();

myfile.open("Chisqrt_Z_output_ZLOG.txt");
for(int i= 0; i < OffSet_Z_vector.size() ; ++i){
  myfile << OffSet_Z_vector.at(i)<<" , "<< ChiSqrt_Z_vector_after.at(i) << "\n";
}
myfile.close();
*/



   can -> Print(text_title_pdf3);
   can -> Print(chisqrt_title_pdf3);

/*
   TFile *outFile = new TFile("Chisqrt_fit_results","RECREATE");

   h_Chisqrt_X_before->Write();
   h_Chisqrt_X_before_ndf->Write();
   h_Chisqrt_Y_before->Write();
   h_Chisqrt_Y_before_ndf->Write();
   h_Chisqrt_Z_before->Write();
   h_Chisqrt_Z_before_ndf->Write();
   h_Chisqrt_R_before->Write();
   h_Chisqrt_R_before_ndf->Write();
   h_Chisqrt_Combined_before->Write();
   h_Chisqrt_Combined_before_ndf->Write();
   h_Chisqrt_X_after->Write();
   h_Chisqrt_X_after_ndf->Write();
   h_Chisqrt_Y_after->Write();
   h_Chisqrt_Y_after_ndf->Write();
   h_Chisqrt_Z_after->Write();
   h_Chisqrt_Z_after_ndf->Write();
   h_Chisqrt_R_after->Write();
   h_Chisqrt_R_after_ndf->Write();
   h_Chisqrt_Combined_after->Write();
   h_Chisqrt_Combined_after_ndf->Write();
   h_Al_wgt_upstream->Write();
   h_Al_wgt_barrel->Write();
   h_Al_wgt_downstream->Write();
   h_Al_wgt_downstreamconcave->Write();

  outFile->Close();
*/






std::cout<< "LeastChisqt_Combined_after[1] =  "<< LeastChisqt_Combined_after[1]<<std::endl;
std::cout<< "LeastChisqt_Combined_after[2] =  "<< LeastChisqt_Combined_after[2]<<std::endl;





} /// End of Main function


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
   // reweight cryo regions using chi2 fit for x,y,z scanning  shifts in x,and y only
   /////////////////////////////////////////////////////
