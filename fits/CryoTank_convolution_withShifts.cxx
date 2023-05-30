#include "CryoTank_convolution_withShifts.h"

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
Pot_MapList POT_MC,POT_Data;
Pot_MapStatusList POT_MC_Status, POT_Data_Status;
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

sprintf(text_title_pdf1, "Plots_Convolution_shifts_Z_Full.pdf(" );
can -> Print(text_title_pdf1);
sprintf(text_title_pdf2, "Plots_Convolution_shifts_Z_Full.pdf" );
sprintf(text_title_pdf3, "Plots_Convolution_shifts_Z_Full.pdf)" );
sprintf(text_title_pdf4, "Plots_Convolution_shifts_Z_Full" );
std::string PDF_label(text_title_pdf4);
std::string PDF_label_input(text_title_pdf2);

sprintf(chisqrt_title_pdf1, "Plots_Convolution_shifts_ChiSqrt_Fullsearch_ZFULL.pdf(" );
can -> Print(chisqrt_title_pdf1);
sprintf(chisqrt_title_pdf2, "Plots_Convolution_shifts_ChiSqrt_Fullsearch_ZFULL.pdf" );
sprintf(chisqrt_title_pdf3, "Plots_Convolution_shifts_ChiSqrt_Fullsearch_ZFULL.pdf)" );
sprintf(chisqrt_title_pdf4, "Plots_Convolution_shifts_ChiSqrt_Fullsearch_ZFULL" );


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

auto PlaylistME_1G_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1G_MC_StatsONLYErrors_ConvolutionZ_noShift_noWgts.root";
auto PlaylistME_1A_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1A_MC_StatsONLYErrors_ConvolutionZ_noShift_noWgts.root";
auto PlaylistME_1L_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1L_MC_StatsONLYErrors_ConvolutionZ_noShift_noWgts.root";
auto PlaylistME_1M_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1M_MC_StatsONLYErrors_ConvolutionZ_noShift_noWgts.root";
auto PlaylistME_1N_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1N_MC_StatsONLYErrors_ConvolutionZ_noShift_noWgts.root";
MAP_RootPath_Empty_MC.insert(std::make_pair(kMEPlayList_Vector.at(0), PlaylistME_1G_MC_path));
MAP_RootPath_Empty_MC.insert(std::make_pair(kMEPlayList_Vector.at(1), PlaylistME_1A_MC_path));
MAP_RootPath_Empty_MC.insert(std::make_pair(kMEPlayList_Vector.at(2), PlaylistME_1L_MC_path));
MAP_RootPath_Empty_MC.insert(std::make_pair(kMEPlayList_Vector.at(3), PlaylistME_1M_MC_path));
MAP_RootPath_Empty_MC.insert(std::make_pair(kMEPlayList_Vector.at(4), PlaylistME_1N_MC_path));

////////////////////////////////////////////////////////////////////////////////
//Full
////////////////////////////////////////////////////////////////////////////////

auto PlaylistME_1P_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1P_MC_StatsONLYErrors_ConvolutionZ_noShift_noWgts.root";
auto PlaylistME_1C_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1C_MC_StatsONLYErrors_ConvolutionZ_noShift_noWgts.root";
auto PlaylistME_1D_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1D_MC_StatsONLYErrors_ConvolutionZ_noShift_noWgts.root";
auto PlaylistME_1F_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1F_MC_StatsONLYErrors_ConvolutionZ_noShift_noWgts.root";
auto PlaylistME_1E_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1E_MC_StatsONLYErrors_ConvolutionZ_noShift_noWgts.root";

MAP_RootPath_Full_MC.insert(std::make_pair(kMEPlayList_Vector.at(5), PlaylistME_1P_MC_path));
MAP_RootPath_Full_MC.insert(std::make_pair(kMEPlayList_Vector.at(6), PlaylistME_1C_MC_path));
MAP_RootPath_Full_MC.insert(std::make_pair(kMEPlayList_Vector.at(7), PlaylistME_1D_MC_path));
MAP_RootPath_Full_MC.insert(std::make_pair(kMEPlayList_Vector.at(8), PlaylistME_1F_MC_path));
MAP_RootPath_Full_MC.insert(std::make_pair(kMEPlayList_Vector.at(9), PlaylistME_1E_MC_path));


/////////////////
/// Data
/////////////////
////////////////////////////////////////////////////////////////////////////////
// Empty
////////////////////////////////////////////////////////////////////////////////

auto PlaylistME_1G_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1G_Data_SmearingStudy.root";
auto PlaylistME_1A_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1A_Data_SmearingStudy.root";
auto PlaylistME_1L_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1L_Data_SmearingStudy.root";
auto PlaylistME_1M_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1M_Data_SmearingStudy.root";
auto PlaylistME_1N_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1N_Data_SmearingStudy.root";
//////////////////
MAP_RootPath_Empty_DATA.insert(std::make_pair(kMEPlayList_Vector.at(0), PlaylistME_1G_Data_path));
MAP_RootPath_Empty_DATA.insert(std::make_pair(kMEPlayList_Vector.at(1), PlaylistME_1A_Data_path));
MAP_RootPath_Empty_DATA.insert(std::make_pair(kMEPlayList_Vector.at(2), PlaylistME_1L_Data_path));
MAP_RootPath_Empty_DATA.insert(std::make_pair(kMEPlayList_Vector.at(3), PlaylistME_1M_Data_path));
MAP_RootPath_Empty_DATA.insert(std::make_pair(kMEPlayList_Vector.at(4), PlaylistME_1N_Data_path));
////////////////////////////////////////////////////////////////////////////////////////////////
//Full
////////////////////////////////////////////////////////////////////////////////////////////////
auto PlaylistME_1P_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1P_Data_SmearingStudy.root";
auto PlaylistME_1C_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1C_Data_SmearingStudy.root";
auto PlaylistME_1D_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1D_Data_SmearingStudy.root";
auto PlaylistME_1F_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1F_Data_SmearingStudy.root";
auto PlaylistME_1E_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1E_Data_SmearingStudy.root";


MAP_RootPath_Full_DATA.insert(std::make_pair(kMEPlayList_Vector.at(5), PlaylistME_1P_Data_path));
MAP_RootPath_Full_DATA.insert(std::make_pair(kMEPlayList_Vector.at(6), PlaylistME_1C_Data_path));
MAP_RootPath_Full_DATA.insert(std::make_pair(kMEPlayList_Vector.at(7), PlaylistME_1D_Data_path));
MAP_RootPath_Full_DATA.insert(std::make_pair(kMEPlayList_Vector.at(8), PlaylistME_1F_Data_path));
MAP_RootPath_Full_DATA.insert(std::make_pair(kMEPlayList_Vector.at(9), PlaylistME_1E_Data_path));


Pot_MapList EmptyPOT_local_MC_MAP   = Constuct_POT_playlistMap(MAP_RootPath_Empty_MC, true);
Pot_MapList FullPOT_local_MC_MAP    = Constuct_POT_playlistMap(MAP_RootPath_Full_MC, true);
Pot_MapList EmptyPOT_local_Data_MAP = Constuct_POT_playlistMap(MAP_RootPath_Empty_DATA, false);
Pot_MapList FullPOT_local_Data_MAP  = Constuct_POT_playlistMap(MAP_RootPath_Full_DATA, false);

/////////////////////////////////////////
///Empty
/////////////////////////////////////////

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

/////////////////////////////////////////
///Full
/////////////////////////////////////////

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



bool is_mc=true;
bool isNOT_mc=false;

std::string  pdf_CV = string(text_title_pdf4);
std::string  pdf_ChiSqr = string(chisqrt_title_pdf4);
bool DoBinwidthNorm=true;
bool MakeXaxisLOG=false;
bool MakeYaxisLOG=false;
bool DrawallErrorGroups=false;

NormalParaFit_Map ZShifts;
//NormalParaFit_Map RShifts;



double stddev_offset_Start_vertexZ = 0.0; //30.0;
double stddev_offset_Finish_vertexZ = 24.0; //48.0;
int stddev_steps = 12;
double mean_offset_Start_vertexZ = -50; //30.0;
double mean_offset_Finish_vertexZ = 50.0; //48.0;
int mean_steps = 50; // reduced my half


FillConvolutionShiftMap(ZShifts, stddev_offset_Start_vertexZ, stddev_offset_Finish_vertexZ,
  stddev_steps, mean_offset_Start_vertexZ, mean_offset_Finish_vertexZ, mean_steps, true);

const int Zsteps = 1;//NumZSteps+1;

//int NBinZ =NumZSteps;
std::vector<double> stddev_offsetVector = MakeBinVector(stddev_steps, stddev_offset_Start_vertexZ, stddev_offset_Finish_vertexZ); // i
std::vector<double> mean_offsetVector = MakeBinVector(mean_steps, mean_offset_Start_vertexZ, mean_offset_Finish_vertexZ); // j

int mapcount=0;
typename std::map<Index3, Normal_Fit_Parameters>::const_iterator  dog;
typename std::map<Index3, Normal_Fit_Parameters>::const_iterator  ConvolutedShift_it;
for ( dog = ZShifts.begin(); dog != ZShifts.end();++dog)
{
  //std::cout<<" index = " << mapcount << " key (i,j,k) =  (" << dog->first.i <<" , "<< dog->first.j<< " , "<< dog->first.k  <<")   OffSet (mean, stddev) =  ( " << dog->second.mean << " , " << dog->second.stddev <<" ) "<<std::endl;
//mapcount++;
}

FitHistName_Map HistName_Map;
Index3 ZeroShift{5 , 0 , 0};

std::vector<double> Chi_sqrt_zeroshift_before;
std::vector<double> Chi_sqrt_zeroshift_after;

const int N_Hists = 5;

MnvH2D *h_Chisqrt_X_Truth_todata_Full[N_Hists];  // 0 total 1 upstream cap , 2 barrel , 3 downstream, 4 downstreamconcave
MnvH2D *h_Chisqrt_Y_Truth_todata_Full[N_Hists];
MnvH2D *h_Chisqrt_Z_Truth_todata_Full[N_Hists];
MnvH2D *h_Chisqrt_Z_Truth_todata_Full_RCut[N_Hists];
MnvH2D *h_Chisqrt_R_Truth_todata_Full[N_Hists];

Array2D(h_Chisqrt_X_Truth_todata_Full,      N_Hists, "h_Chisqrt_X_Truth_todata_Full",      "h_Chisqrt_X_todata",mean_offsetVector, stddev_offsetVector);
Array2D(h_Chisqrt_Y_Truth_todata_Full,      N_Hists, "h_Chisqrt_Y_Truth_todata_Full",      "h_Chisqrt_Y_todata",mean_offsetVector, stddev_offsetVector);
Array2D(h_Chisqrt_Z_Truth_todata_Full,      N_Hists, "h_Chisqrt_Z_Truth_todata_Full",      "h_Chisqrt_Z_todata",mean_offsetVector, stddev_offsetVector);
Array2D(h_Chisqrt_Z_Truth_todata_Full_RCut, N_Hists, "h_Chisqrt_Z_Truth_todata_Full_RCut", "h_Chisqrt_Z_todata",mean_offsetVector, stddev_offsetVector);
Array2D(h_Chisqrt_R_Truth_todata_Full,      N_Hists, "h_Chisqrt_R_Truth_todata_Full",      "h_Chisqrt_R_todata",mean_offsetVector, stddev_offsetVector);


MnvH2D *h_Chisqrt_Distancetowall_Truth_todata_Full[N_Hists];
MnvH2D *h_Chisqrt_Distancetowall_Truth_todata_Full_RCut[N_Hists];
MnvH2D *h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Full[N_Hists];
MnvH2D *h_Chisqrt_Distanceto_downstreamcap_Truth_todata_Full[N_Hists];
MnvH2D *h_Chisqrt_Distanceto_upstreamcap_Truth_todata_RCut_Full[N_Hists];
MnvH2D *h_Chisqrt_Distanceto_downstreamcap_Truth_todata_RCut_Full[N_Hists];

Array2D(h_Chisqrt_Distancetowall_Truth_todata_Full,                N_Hists, "h_Chisqrt_Distancetowall_Truth_todata_Full",           "h_Chisqrt_Distancetowall_todata",          mean_offsetVector, stddev_offsetVector);
Array2D(h_Chisqrt_Distancetowall_Truth_todata_Full_RCut,           N_Hists, "h_Chisqrt_Distancetowall_Truth_todata_Full_RCut",           "h_Chisqrt_Distancetowall_todata",          mean_offsetVector, stddev_offsetVector);
Array2D(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Full,        N_Hists, "h_Chisqrt_Distanceto_upstreamcap_todata_Full",   "h_Chisqrt_Distanceto_upstreamcap_todata",  mean_offsetVector, stddev_offsetVector);
Array2D(h_Chisqrt_Distanceto_downstreamcap_Truth_todata_Full,      N_Hists, "h_Chisqrt_Distanceto_downstreamcap_todata_Full", "h_Chisqrt_Distanceto_downstreamcap_todata",mean_offsetVector, stddev_offsetVector);
Array2D(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_RCut_Full,   N_Hists, "h_Chisqrt_Distanceto_upstreamcap_todata_RCut_Full",   "h_Chisqrt_Distanceto_upstreamcap_todata",  mean_offsetVector, stddev_offsetVector);
Array2D(h_Chisqrt_Distanceto_downstreamcap_Truth_todata_RCut_Full, N_Hists, "h_Chisqrt_Distanceto_downstreamcap_todata_RCut_Full", "h_Chisqrt_Distanceto_downstreamcap_todata",mean_offsetVector, stddev_offsetVector);



MnvH2D *h_Chisqrt_X_Truth_todata_Empty[N_Hists];  // 0 total 1 upstream cap , 2 barrel , 3 downstream, 4 downstreamconcave
MnvH2D *h_Chisqrt_Y_Truth_todata_Empty[N_Hists];
MnvH2D *h_Chisqrt_Z_Truth_todata_Empty[N_Hists];
MnvH2D *h_Chisqrt_Z_Truth_todata_Empty_RCut[N_Hists];
MnvH2D *h_Chisqrt_R_Truth_todata_Empty[N_Hists];

MnvH2D *h_Chisqrt_Distancetowall_Truth_todata_Empty[N_Hists];

MnvH2D *h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Empty[N_Hists];
MnvH2D *h_Chisqrt_Distanceto_downstreamcap_Truth_todata_Empty[N_Hists];
MnvH2D *h_Chisqrt_Distanceto_upstreamcap_Truth_todata_RCut_Empty[N_Hists];
MnvH2D *h_Chisqrt_Distanceto_downstreamcap_Truth_todata_RCut_Empty[N_Hists];

Array2D(h_Chisqrt_X_Truth_todata_Empty,      N_Hists, "h_Chisqrt_X_Truth_todata_Empty",      "h_Chisqrt_X_todata",mean_offsetVector, stddev_offsetVector);
Array2D(h_Chisqrt_Y_Truth_todata_Empty,      N_Hists, "h_Chisqrt_Y_Truth_todata_Empty",      "h_Chisqrt_Y_todata",mean_offsetVector, stddev_offsetVector);
Array2D(h_Chisqrt_Z_Truth_todata_Empty,      N_Hists, "h_Chisqrt_Z_Truth_todata_Empty",      "h_Chisqrt_Z_todata",mean_offsetVector, stddev_offsetVector);
Array2D(h_Chisqrt_Z_Truth_todata_Empty_RCut, N_Hists, "h_Chisqrt_Z_Truth_todata_Empty_RCut", "h_Chisqrt_Z_todata",mean_offsetVector, stddev_offsetVector);
Array2D(h_Chisqrt_R_Truth_todata_Empty,      N_Hists, "h_Chisqrt_R_Truth_todata_Empty",      "h_Chisqrt_R_todata",mean_offsetVector, stddev_offsetVector);

Array2D(h_Chisqrt_Distancetowall_Truth_todata_Empty,                N_Hists, "h_Chisqrt_Distancetowall_Truth_todata_Empty",           "h_Chisqrt_Distancetowall_todata",          mean_offsetVector, stddev_offsetVector);
Array2D(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Empty,        N_Hists, "h_Chisqrt_Distanceto_upstreamcap_todata_Empty",   "h_Chisqrt_Distanceto_upstreamcap_todata",  mean_offsetVector, stddev_offsetVector);
Array2D(h_Chisqrt_Distanceto_downstreamcap_Truth_todata_Empty,      N_Hists, "h_Chisqrt_Distanceto_downstreamcap_todata_Empty", "h_Chisqrt_Distanceto_downstreamcap_todata",mean_offsetVector, stddev_offsetVector);
Array2D(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_RCut_Empty,   N_Hists, "h_Chisqrt_Distanceto_upstreamcap_todata_RCut_Empty",   "h_Chisqrt_Distanceto_upstreamcap_todata",  mean_offsetVector, stddev_offsetVector);
Array2D(h_Chisqrt_Distanceto_downstreamcap_Truth_todata_RCut_Empty, N_Hists, "h_Chisqrt_Distanceto_downstreamcap_todata_RCut_Empty", "h_Chisqrt_Distanceto_downstreamcap_todata",mean_offsetVector, stddev_offsetVector);


MnvH2D *h_Chisqrt_X_Truth_todata_Full_Empty[N_Hists];  // 0 total 1 upstream cap , 2 barrel , 3 downstream, 4 downstreamconcave
MnvH2D *h_Chisqrt_Y_Truth_todata_Full_Empty[N_Hists];
MnvH2D *h_Chisqrt_Z_Truth_todata_Full_Empty[N_Hists];
MnvH2D *h_Chisqrt_Z_Truth_todata_Full_Empty_RCut[N_Hists];
MnvH2D *h_Chisqrt_R_Truth_todata_Full_Empty[N_Hists];

MnvH2D *h_Chisqrt_Distancetowall_Truth_todata_Full_Empty[N_Hists];
MnvH2D *h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Full_Empty[N_Hists];
MnvH2D *h_Chisqrt_Distanceto_downstreamcap_Truth_todata_Full_Empty[N_Hists];
MnvH2D *h_Chisqrt_Distanceto_upstreamcap_Truth_todata_RCut_Full_Empty[N_Hists];
MnvH2D *h_Chisqrt_Distanceto_downstreamcap_Truth_todata_RCut_Full_Empty[N_Hists];


Array2D(h_Chisqrt_X_Truth_todata_Full_Empty,      N_Hists, "h_Chisqrt_X_Truth_todata_Full_Empty",      "h_Chisqrt_X_todata",mean_offsetVector, stddev_offsetVector);
Array2D(h_Chisqrt_Y_Truth_todata_Full_Empty,      N_Hists, "h_Chisqrt_Y_Truth_todata_Full_Empty",      "h_Chisqrt_Y_todata",mean_offsetVector, stddev_offsetVector);
Array2D(h_Chisqrt_Z_Truth_todata_Full_Empty,      N_Hists, "h_Chisqrt_Z_Truth_todata_Full_Empty",      "h_Chisqrt_Z_todata",mean_offsetVector, stddev_offsetVector);
Array2D(h_Chisqrt_Z_Truth_todata_Full_Empty_RCut, N_Hists, "h_Chisqrt_Z_Truth_todata_Full_Empty_RCut", "h_Chisqrt_Z_todata",mean_offsetVector, stddev_offsetVector);
Array2D(h_Chisqrt_R_Truth_todata_Full_Empty,      N_Hists, "h_Chisqrt_R_Truth_todata_Full_Empty",      "h_Chisqrt_R_todata",mean_offsetVector, stddev_offsetVector);

Array2D(h_Chisqrt_Distancetowall_Truth_todata_Full_Empty,                N_Hists, "h_Chisqrt_Distancetowall_Truth_todata_Full_Empty",           "h_Chisqrt_Distancetowall_todata",          mean_offsetVector, stddev_offsetVector);
Array2D(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Full_Empty,        N_Hists, "h_Chisqrt_Distanceto_upstreamcap_todata_Full_Empty",   "h_Chisqrt_Distanceto_upstreamcap_todata",  mean_offsetVector, stddev_offsetVector);
Array2D(h_Chisqrt_Distanceto_downstreamcap_Truth_todata_Full_Empty,      N_Hists, "h_Chisqrt_Distanceto_downstreamcap_todata_Full_Empty", "h_Chisqrt_Distanceto_downstreamcap_todata",mean_offsetVector, stddev_offsetVector);
Array2D(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_RCut_Full_Empty,   N_Hists, "h_Chisqrt_Distanceto_upstreamcap_todata_RCut_Full_Empty",   "h_Chisqrt_Distanceto_upstreamcap_todata",  mean_offsetVector, stddev_offsetVector);
Array2D(h_Chisqrt_Distanceto_downstreamcap_Truth_todata_RCut_Full_Empty, N_Hists, "h_Chisqrt_Distanceto_downstreamcap_todata_RCut_Full_Empty", "h_Chisqrt_Distanceto_downstreamcap_todata",mean_offsetVector, stddev_offsetVector);


MnvH2D *h_Chisqrt_X_Truth_toRECO[N_Hists];  // 0 total 1 upstream cap , 2 barrel , 3 downstream, 4 downstreamconcave
MnvH2D *h_Chisqrt_Y_Truth_toRECO[N_Hists];
MnvH2D *h_Chisqrt_Z_Truth_toRECO[N_Hists];
MnvH2D *h_Chisqrt_R_Truth_toRECO[N_Hists];

MnvH2D *h_Chisqrt_Distancetowall_Truth_todata[N_Hists];
MnvH2D *h_Chisqrt_Distanceto_upstreamcap_Truth_todata[N_Hists];
MnvH2D *h_Chisqrt_Distanceto_downstreamcap_Truth_todata[N_Hists];

MnvH2D *h_Chisqrt_Distancetowall_Truth_toRECO[N_Hists];
MnvH2D *h_Chisqrt_Distanceto_upstreamcap_Truth_toRECO[N_Hists];
MnvH2D *h_Chisqrt_Distanceto_downstreamcap_Truth_toRECO[N_Hists];



std::string x_offset_string;
std::string y_offset_string;
std::string z_offset_string;
std::string title_string;



double bins_X = 12;
double bins_Y = 12;
double bins_Z = 13;
double bins_R = 15;

double npars = 4;



std::vector<std::string> histNames;
std::vector<Fit_Parms_Names> FitParms;
MnvH2D *h_Al_wgt_upstream             =    new MnvH2D("h_Al_wgt_upstream",          "h_Al_wgt_upstream",          mean_offsetVector.size()-1,  mean_offsetVector.data(), stddev_offsetVector.size()-1, stddev_offsetVector.data()  );
MnvH2D *h_Al_wgt_barrel               =    new MnvH2D("h_Al_wgt_barrel",            "h_Al_wgt_barrel",            mean_offsetVector.size()-1,  mean_offsetVector.data(), stddev_offsetVector.size()-1, stddev_offsetVector.data()  );
MnvH2D *h_Al_wgt_downstream           =    new MnvH2D("h_Al_wgt_downstream",        "h_Al_wgt_downstream",        mean_offsetVector.size()-1,  mean_offsetVector.data(), stddev_offsetVector.size()-1, stddev_offsetVector.data()  );
MnvH2D *h_Al_wgt_downstreamconcave    =    new MnvH2D("h_Al_wgt_downstreamconcave", "h_Al_wgt_downstreamconcave", mean_offsetVector.size()-1,  mean_offsetVector.data(), stddev_offsetVector.size()-1, stddev_offsetVector.data()  );


MnvH2D *h_Chisqrt_X_Y_Z    =    new MnvH2D("h_Chisqrt_X_Y_Z", "h_Chisqrt_X_Y_Z", mean_offsetVector.size()-1,  mean_offsetVector.data(),stddev_offsetVector.size()-1, stddev_offsetVector.data()  );
MnvH2D *h_Chisqrt_R_Z    =    new MnvH2D("h_Chisqrt_R_Z", "h_Chisqrt_R_Z", mean_offsetVector.size()-1,  mean_offsetVector.data(),      stddev_offsetVector.size()-1, stddev_offsetVector.data()  );



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




std::cout<<"Cycle throught Off Set Map"<<std::endl;
int count= 0;

std::vector<double> ChiSqrt_Z_vector_before;
std::vector<double> ChiSqrt_Z_vector;

std::vector<double> ChiSqrt_Combined_vector_before;
std::vector<double> ChiSqrt_Combined_vector;
std::vector<double> ChiSqrt_Z_R_vector;

std::vector<double> ChiSqrt_R_vector_before;
std::vector<double> ChiSqrt_R_vector;
std::vector<double> ChiSqrt_X_vector_before;
std::vector<double> ChiSqrt_X_vector;
std::vector<double> ChiSqrt_Y_vector_before;
std::vector<double> ChiSqrt_Y_vector;
std::vector<double> OffSet_Z_vector;


ChiSqrt_results Best_ChiSqrt_Result_Full{9999.0, 9999.0, 9999.0, 9999.0, 9999.0, 9999.0, 9999.0, 9999.0, 9999.0, 9999.0};
ChiSqrt_results Best_ChiSqrt_Result_Empty{9999.0, 9999.0, 9999.0, 9999.0, 9999.0, 9999.0, 9999.0, 9999.0, 9999.0, 9999.0};
ChiSqrt_results Best_ChiSqrt_Result_Full_Empty{9999.0, 9999.0, 9999.0, 9999.0, 9999.0, 9999.0, 9999.0, 9999.0, 9999.0, 9999.0};


BestIndex Bestindex_ChiSqrt_Full{{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
BestIndex Bestindex_ChiSqrt_Empty{{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
BestIndex Bestindex_ChiSqrt_Full_Empty{{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~Looping throuh vertex Z~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

 mapcount = 0;
std::string title_name;
std::stringstream stream;
char Plot_title[1024];
std::cout<<"Finished Loop "<<std::endl;


double Chisqrt_Top1 = 99999.9;
double Chisqrt_Top2 = 999999.9;
double Chisqrt_Top3 = 9999990.9;
double Chisqrt_Top4 = 99999900.9;
double Chisqrt_Top5 = 999999009.9;
Index3 Top1index{0 ,0, 0 };
Index3 Top2index{0 ,0, 0};
Index3 Top3index{0 ,0, 0 };
Index3 Top4index{0 ,0, 0};
Index3 Top5index{0 ,0, 0};
std::vector<double> wgt_vector;
std::vector<double> wgt_error_vector;
std::map<double , Index3> Chisqrt_Top5Map{{Chisqrt_Top1 ,Top1index},{Chisqrt_Top2 ,Top2index}, {Chisqrt_Top3 ,Top3index}, {Chisqrt_Top4 ,Top4index}, {Chisqrt_Top5 ,Top5index}};


Convolution_Tool Convolution_Tool_TotalPlaylist(
  FullTFile_Map_MC,
  FullTFile_Map_Data,
  EmptyTFile_Map_MC,
  EmptyTFile_Map_Data,

  FullPOT_local_Data_MAP,
  FullPOT_local_MC_MAP,
  EmptyPOT_local_Data_MAP,
  EmptyPOT_local_MC_MAP
);

ChiSqrt_results inputFull;
ChiSqrt_results inputEmpty;
ChiSqrt_results input_Full_Empty;

BestIndex_Regions BestIndex_Regions_Full;
BestIndex_Regions BestIndex_Regions_Empty;
BestIndex_Regions BestIndex_Regions_Full_Empty;

ChiSqrt_CryoTankRegions ChiSqrt_CryoTankRegions_Full;
ChiSqrt_CryoTankRegions ChiSqrt_CryoTankRegions_Empty;
ChiSqrt_CryoTankRegions ChiSqrt_CryoTankRegions_Full_Empty;

ChiSqrt_CryoTankRegions BEST_ChiSqrt_CryoTankRegions_Full;
ChiSqrt_CryoTankRegions BEST_ChiSqrt_CryoTankRegions_Empty;
ChiSqrt_CryoTankRegions BEST_ChiSqrt_CryoTankRegions_Full_Empty;


Convolution_Tool_TotalPlaylist.input_pdfLabel(PDF_label);
Convolution_Tool_TotalPlaylist.assign_CryoVertex_type();
Convolution_Tool_TotalPlaylist.assign_RegionsHist_RecoandTRUEName();
Convolution_Tool_TotalPlaylist.assign_CryoVertexTotalRegion_ConvolutedTRUEHistName();
//Convolution_Tool_TotalPlaylist.assign_RegionsHist_dataName();
Convolution_Tool_TotalPlaylist.Intialize_dataHistNames();
Convolution_Tool_TotalPlaylist.init_NuMEPlaylist_POT();
Convolution_Tool_TotalPlaylist.PrintPOT();
Convolution_Tool_TotalPlaylist.init_All_DataHists();
//Convolution_Tool_TotalPlaylist.init_All_RecoHists();
//Convolution_Tool_TotalPlaylist.init_All_TRUEHists();
Convolution_Tool_TotalPlaylist.assign_xAxis();
Convolution_Tool_TotalPlaylist.assign_Material_XYZR_HistName();

double vertex_X_mean;
double vertex_X_sigma;
double vertex_Y_mean;
double vertex_Y_sigma;
double vertex_Z_mean;
double vertex_Z_sigma;

double ChisqrtX  = 999;
double ChisqrtY = 999;
double ChisqrtZ  = 999;
double ChisqrtR = 999;

Fill_Convolution_BeforeShift(kME1C ,vertex_X_mean,
    vertex_X_sigma, vertex_Y_mean, vertex_Y_sigma, vertex_Z_mean, vertex_Z_sigma);
    Convolution_Tool_TotalPlaylist.FillFull_Normal_Fit_ParametersXY(vertex_X_mean,vertex_X_sigma, vertex_Y_mean, vertex_Y_sigma);

//Convolution_Tool_TotalPlaylist.init_ZeroShift_RECO_Convolution_Regions_Hists_PlaylistCombinedMC();
//std::cout<<"Starting to Plot"<<std::endl;
//Convolution_Tool_TotalPlaylist.Plot_Full_ConvolRECO(0.0, 0.0);
//Convolution_Tool_TotalPlaylist.Plot_Regions_ConvolRECO(0.0, 0.0);

Convolution_Tool_TotalPlaylist.initFULLONLY_RECO_Convolution_Material_Regions_Hists_PlaylistCombinedMC( ZeroShift.i,  ZeroShift.j,  ZeroShift.k );
Convolution_Tool_TotalPlaylist.Plot_regions_XYZFit_Full( 0 , 0, 0, 0, "Before Fit" );
SetConvolutionShiftMapTool(Convolution_Tool_TotalPlaylist);
FitConvolutionTool(Convolution_Tool_TotalPlaylist, 4,
  "fitlog", "log", PDF_label,
wgt_vector, wgt_error_vector);
//std::cout<<"Filling Wgts"<< std::endl;
Convolution_Tool_TotalPlaylist.Fill_Alwgt(wgt_vector, wgt_error_vector);
//std::cout<<"ApplyFitResults"<< std::endl;
Convolution_Tool_TotalPlaylist.ApplyFitResults_toFull();
Convolution_Tool_TotalPlaylist.CalMaterial_ChiSqrtFullAfter( ChisqrtX, ChisqrtY, ChisqrtZ, ChisqrtR);
Convolution_Tool_TotalPlaylist.Plot_regions_XYZFit_Full( 0 , 0, 1, 1, "After Fit" );

std::cout<<"ChisqrtX = " << ChisqrtX << std::endl;
std::cout<<"ChisqrtY = " << ChisqrtY << std::endl;
std::cout<<"ChisqrtZ = " << ChisqrtZ << std::endl;
std::cout<<"ChisqrtR = " << ChisqrtR << std::endl;


Convolution_Tool_TotalPlaylist.Clear_Al_wgt();
wgt_vector.clear();
wgt_error_vector.clear();

double BestChitFit = 99999;
double BestFit_meanZ = 99999;
double BestFit_stddevZ = 99999;
Index3 input_index_best{99,99,99};

double BestRChitFit = 99999;
double BestRFit_meanZ = 99999;
double BestRFit_stddevZ = 99999;
Index3 input_index_bestR{99,99,99};






std::cout<<"~~~~~~~~~~~~~~~~~Starting Loop ~~~~~~~~~~~~~~~"<<std::endl;

/*
for ( dog = ZShifts.begin(); dog != ZShifts.end();++dog)
{
  //std::cout<<" index = " << mapcount << " key (i,j,k) =  (" << dog->first.i <<" , "<< dog->first.j<< " , "<< dog->first.k  <<")   OffSet (mean, stddev) =  ( " << dog->second.mean << " , " << dog->second.stddev <<" ) "<<std::endl;
mapcount++;
double mean = dog->second.mean;
double stddev = dog->second.stddev;

  if(mapcount%10==0) std::cout << mapcount << " Steps  " << std::endl;
  //std::cout<<"init_ALL_RECOConvolution_Regions_Hists_PlaylistCombinedMC"<<std::endl;
Convolution_Tool_TotalPlaylist.init_ALL_RECOConvolution_Regions_Hists_PlaylistCombinedMC(dog->first.i, dog->first.j, dog->first.k);
//std::cout<<"Cal_Chisqt_Total"<<std::endl;

Convolution_Tool_TotalPlaylist.Cal_Chisqt_Total(inputFull, inputEmpty, input_Full_Empty, mnv_plotter, 1 );
//std::cout<< "Finished Cal_Chisqt_Total" << std::endl;
//std::cout<<"Cal_Chisqrt_ConvolutionTruth_ToData_Regions"<<std::endl;
Convolution_Tool_TotalPlaylist.Cal_Chisqrt_ConvolutionTruth_ToData_Regions(mnv_plotter, ChiSqrt_CryoTankRegions_Full, ChiSqrt_CryoTankRegions_Empty, ChiSqrt_CryoTankRegions_Full_Empty, 1 );

Index3 input_index{dog->first.i, dog->first.j, dog->first.k};
//std::cout<<"SaveBestChiSqrt_Total"<<std::endl;

Convolution_Tool_TotalPlaylist.SaveBestChiSqrt_Total(Best_ChiSqrt_Result_Full, Best_ChiSqrt_Result_Empty, Best_ChiSqrt_Result_Full_Empty,
                                                     inputFull, inputEmpty, input_Full_Empty, Bestindex_ChiSqrt_Full, Bestindex_ChiSqrt_Empty,
                                                     Bestindex_ChiSqrt_Full_Empty, input_index);

//Convolution_Tool_TotalPlaylist.SaveBestChiSqrt_Regions(BEST_ChiSqrt_CryoTankRegions_Full,
//                                                       BEST_ChiSqrt_CryoTankRegions_Empty,
//                            c                           BEST_ChiSqrt_CryoTankRegions_Full_Empty,
//                                                       ChiSqrt_CryoTankRegions_Full,
//                                                       ChiSqrt_CryoTankRegions_Empty,
//                                                       ChiSqrt_CryoTankRegions_Full_Empty,
//                                                       BestIndex_Regions_Full,
//                                                       BestIndex_Regions_Empty,
//                                                       BestIndex_Regions_Full_Empty, input_index);


//Convolution_Tool_TotalPlaylist.Cal_Chisqrt_ConvolutionTruth_ToData_Regions(mnv_plotter, ChiSqrt_CryoTankRegions_Full, ChiSqrt_CryoTankRegions_Empty, ChiSqrt_CryoTankRegions_Full_Empty);
//std::cout<< "Finished Cal_Chisqrt_ConvolutionTruth_ToData_Regions" << std::endl;
//std::cout<<"Fill_TotalChiSqrts FULL"<<std::endl;
Convolution_Tool_TotalPlaylist.Fill_TotalChiSqrts(inputFull, mean, stddev,
  h_Chisqrt_X_Truth_todata_Full,
  h_Chisqrt_Y_Truth_todata_Full,
  h_Chisqrt_R_Truth_todata_Full,
  h_Chisqrt_Z_Truth_todata_Full,
  h_Chisqrt_Z_Truth_todata_Full_RCut,
  h_Chisqrt_Distancetowall_Truth_todata_Full,
  h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Full,
  h_Chisqrt_Distanceto_downstreamcap_Truth_todata_Full,
  h_Chisqrt_Distanceto_upstreamcap_Truth_todata_RCut_Full,
  h_Chisqrt_Distanceto_downstreamcap_Truth_todata_RCut_Full);

//std::cout<<"Fill_TotalChiSqrts Empty"<<std::endl;

  Convolution_Tool_TotalPlaylist.Fill_TotalChiSqrts(inputEmpty, mean, stddev,
    h_Chisqrt_X_Truth_todata_Empty,
    h_Chisqrt_Y_Truth_todata_Empty,
    h_Chisqrt_R_Truth_todata_Empty,
    h_Chisqrt_Z_Truth_todata_Empty,
    h_Chisqrt_Z_Truth_todata_Empty_RCut,
    h_Chisqrt_Distancetowall_Truth_todata_Empty,
    h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Empty,
    h_Chisqrt_Distanceto_downstreamcap_Truth_todata_Empty,
    h_Chisqrt_Distanceto_upstreamcap_Truth_todata_RCut_Empty,
    h_Chisqrt_Distanceto_downstreamcap_Truth_todata_RCut_Empty);

//Convolution_Tool_TotalPlaylist.Fill_TotalChiSqrts(input_Full_Empty, mean, stddev,
//  h_Chisqrt_X_Truth_todata_Full_Empty,
//  h_Chisqrt_Y_Truth_todata_Full_Empty,
//  h_Chisqrt_R_Truth_todata_Full_Empty,
//  h_Chisqrt_Z_Truth_todata_Full_Empty,
//  h_Chisqrt_Z_Truth_todata_Full_Empty_RCut,
//  h_Chisqrt_Distancetowall_Truth_todata_Full_Empty,
//  h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Full_Empty,
//  h_Chisqrt_Distanceto_downstreamcap_Truth_todata_Full_Empty,
//  h_Chisqrt_Distanceto_upstreamcap_Truth_todata_RCut_Full_Empty,
//  h_Chisqrt_Distanceto_downstreamcap_Truth_todata_RCut_Full_Empty);

//h_Chisqrt_X_Truth_todata_Full[0]->Fill(mean,stddev,inputFull.Chisqrt_X);
//h_Chisqrt_Y_Truth_todata_Full[0]->Fill(mean,stddev,inputFull.Chisqrt_Y);
//h_Chisqrt_R_Truth_todata_Full[0]->Fill(mean,stddev,inputFull.Chisqrt_R);
////h2_Vertex_RR_TotalRegion.Fill(mean,stddev,);
//h_Chisqrt_Z_Truth_todata_Full[0]->Fill(mean,stddev,inputFull.Chisqrt_Z);
//h_Chisqrt_Z_Truth_todata_Full_RCut[0]->Fill(mean,stddev,inputFull.Chisqrt_Z_RCut);
//h_Chisqrt_Distancetowall_Truth_todata_Full[0]->Fill(mean,stddev,inputFull.Chisqrt_NearestWall);
//h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Full[0]->Fill(mean,stddev,inputFull.Chisqrt_DistancetoUpstreamCap);
//h_Chisqrt_Distanceto_downstreamcap_Truth_todata_Full[0]->Fill(mean,stddev,inputFull.Chisqrt_DistancetoDownstreamCap);
//h_Chisqrt_Distanceto_upstreamcap_Truth_todata_RCut_Full[0]->Fill(mean,stddev,inputFull.Chisqrt_DistancetoUpstreamCap_RCut);
//h_Chisqrt_Distanceto_downstreamcap_Truth_todata_RCut_Full[0]->Fill(mean,stddev,inputFull.Chisqrt_DistancetoDownstreamCap_RCut);

//std::cout<< "Fininshed:Fill_TotalChiSqrts" << std::endl;

Convolution_Tool_TotalPlaylist.Fill_TotalChiSqrts_Regions(ChiSqrt_CryoTankRegions_Full, mean, stddev,
  h_Chisqrt_X_Truth_todata_Full,
  h_Chisqrt_Y_Truth_todata_Full,
  h_Chisqrt_R_Truth_todata_Full,
  h_Chisqrt_Z_Truth_todata_Full,
  h_Chisqrt_Z_Truth_todata_Full_RCut,
  h_Chisqrt_Distancetowall_Truth_todata_Full,
  h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Full,
  h_Chisqrt_Distanceto_downstreamcap_Truth_todata_Full,
  h_Chisqrt_Distanceto_upstreamcap_Truth_todata_RCut_Full,
  h_Chisqrt_Distanceto_downstreamcap_Truth_todata_RCut_Full);

Convolution_Tool_TotalPlaylist.Fill_TotalChiSqrts_Regions(ChiSqrt_CryoTankRegions_Empty, mean, stddev,
  h_Chisqrt_X_Truth_todata_Empty,
  h_Chisqrt_Y_Truth_todata_Empty,
  h_Chisqrt_R_Truth_todata_Empty,
  h_Chisqrt_Z_Truth_todata_Empty,
  h_Chisqrt_Z_Truth_todata_Empty_RCut,
  h_Chisqrt_Distancetowall_Truth_todata_Empty,
  h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Empty,
  h_Chisqrt_Distanceto_downstreamcap_Truth_todata_Empty,
  h_Chisqrt_Distanceto_upstreamcap_Truth_todata_RCut_Empty,
  h_Chisqrt_Distanceto_downstreamcap_Truth_todata_RCut_Empty);


  Convolution_Tool_TotalPlaylist.Fill_TotalChiSqrts_Regions(ChiSqrt_CryoTankRegions_Full_Empty, mean, stddev,
    h_Chisqrt_X_Truth_todata_Full_Empty,
    h_Chisqrt_Y_Truth_todata_Full_Empty,
    h_Chisqrt_R_Truth_todata_Full_Empty,
    h_Chisqrt_Z_Truth_todata_Full_Empty,
    h_Chisqrt_Z_Truth_todata_Full_Empty_RCut,
    h_Chisqrt_Distancetowall_Truth_todata_Full_Empty,
    h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Full_Empty,
    h_Chisqrt_Distanceto_downstreamcap_Truth_todata_Full_Empty,
    h_Chisqrt_Distanceto_upstreamcap_Truth_todata_RCut_Full_Empty,
    h_Chisqrt_Distanceto_downstreamcap_Truth_todata_RCut_Full_Empty);

//std::cout<< "Fininshed:Fill_TotalChiSqrts_Regions" << std::endl;

}*/
/////////////////////////////////////////////////////////
/////////////////////Loop throught Empty ///////////////
/////////////////////////////////////////////////////////

for ( dog = ZShifts.begin(); dog != ZShifts.end();++dog)
{
  //std::cout<<" index = " << mapcount << " key (i,j,k) =  (" << dog->first.i <<" , "<< dog->first.j<< " , "<< dog->first.k  <<")   OffSet (mean, stddev) =  ( " << dog->second.mean << " , " << dog->second.stddev <<" ) "<<std::endl;

double mean = dog->second.mean;
double stddev = dog->second.stddev;

  if(mapcount%10==0) std::cout << mapcount << " Steps  " << std::endl;

Convolution_Tool_TotalPlaylist.initFULLONLY_RECO_Convolution_Material_Regions_Hists_PlaylistCombinedMC( dog->first.i,  dog->first.j,  dog->first.k );

Index3 input_index{dog->first.i, dog->first.j, dog->first.k};
double Chisqrt, Chisqrt_error;
int i = dog->first.i;
int j = dog->first.j;
//std::cout<<"finished  Trying to Fit"<< std::endl;
SetConvolutionShiftMapTool(Convolution_Tool_TotalPlaylist);
FitConvolutionTool(Convolution_Tool_TotalPlaylist, 4,
  "fitlog", "log", PDF_label,
wgt_vector, wgt_error_vector);
//std::cout<<"Filling Wgts"<< std::endl;
Convolution_Tool_TotalPlaylist.Fill_Alwgt(wgt_vector, wgt_error_vector);
//std::cout<<"ApplyFitResults"<< std::endl;
Convolution_Tool_TotalPlaylist.ApplyFitResults_toFull();

Convolution_Tool_TotalPlaylist.CalMaterial_ChiSqrtFullAfter( ChisqrtX, ChisqrtY, ChisqrtZ, ChisqrtR);
double Chisqrt_X_Y_Z =  ChisqrtX + ChisqrtY + ChisqrtZ;
double Chi_R_Z = ChisqrtR + ChisqrtZ;

if(BestChitFit > Chisqrt_X_Y_Z ){
BestChitFit = Chisqrt_X_Y_Z;
BestFit_meanZ = mean;
BestFit_stddevZ = stddev;
input_index_best = input_index;
}

if(BestRChitFit > Chi_R_Z ){
BestRChitFit = Chi_R_Z;
BestRFit_meanZ = mean;
BestRFit_stddevZ = stddev;
input_index_bestR = input_index;
}

/*
if(mean > -2 && 6  > mean ) {

if (stddev < 5 ){

  sprintf(Plot_title,  "Fit #chi^{2} =  %.1f", Chisqrt_X_Y_Z  );
  std::string PLOT_string(Plot_title);
  Convolution_Tool_TotalPlaylist.Plot_regions_XYZFit_Full(mean  , stddev, 1, 1, PLOT_string);


}


}*/

if(Chisqrt_X_Y_Z < Chisqrt_Top5Map.rbegin()->first ){

Chisqrt_Top5Map.insert(std::pair<double , Index3 >(Chisqrt_X_Y_Z, input_index));


Chisqrt_Top5Map.erase(Chisqrt_Top5Map.rbegin()->first);


}




h_Al_wgt_upstream->SetBinContent(i, j, wgt_vector.at(0));
h_Al_wgt_barrel->SetBinContent(i, j, wgt_vector.at(1));
h_Al_wgt_downstream->SetBinContent(i, j, wgt_vector.at(2));
h_Al_wgt_downstreamconcave->SetBinContent(i, j, wgt_vector.at(3));
h_Chisqrt_X_Y_Z->SetBinContent(i, j,  Chisqrt_X_Y_Z);
h_Chisqrt_R_Z->SetBinContent(i, j, Chi_R_Z);


Convolution_Tool_TotalPlaylist.Clear_Al_wgt();
wgt_vector.clear();
wgt_error_vector.clear();





mapcount++;

}


wgt_error_vector.clear();
wgt_vector.clear();
Convolution_Tool_TotalPlaylist.Clear_Al_wgt();
/////////////////////////////////////////////////////////
/////////////////////Loop throught Full ///////////////
/////////////////////////////////////////////////////////


std::cout<<"Writing Hists"<< std::endl;




char xaxislabel[1024];
char yaxislabel[1024];
std::string Total_Chi_Before;
std::string Total_Chi_After;

sprintf(xaxislabel, "Off Set X [mm]");
sprintf(yaxislabel, "Off Set Y [mm]");

std::cout<<"Making Plots "<<std::endl;

//std::ofstream myfile;
  //myfile.open ("Chisqrt_Combined_output_neg45_40_Z.txt");

//Convolution_Tool_TotalPlaylist.init_RECO_Convolution_TotalHists_PlaylistCombinedMC(Bestindex_ChiSqrt_Full, Bestindex_ChiSqrt_Empty);
//Convolution_Tool_TotalPlaylist.init_RECO_Convolution_RegonsHists_PlaylistCombinedMC( BestIndex_Regions_Full,  BestIndex_Regions_Empty);
//Convolution_Tool_TotalPlaylist.Plot_Full_ConvolRECO(ZShifts, Bestindex_ChiSqrt_Full, Bestindex_ChiSqrt_Empty);


///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
///  Full Total
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~




sprintf(Plot_title, " Vertex X + Y + Z Convoluted total [Combined Full] Min X(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", BestFit_meanZ,
 BestFit_stddevZ, BestChitFit );
Draw2DHist(h_Chisqrt_X_Y_Z,  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

sprintf(Plot_title, " Vertex R+Z Convoluted total [Combined Full] Min X(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", BestRFit_meanZ,
 BestRFit_stddevZ, BestRChitFit );
Draw2DHist(h_Chisqrt_R_Z,  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

sprintf(Plot_title, "Fitted Wgts upstream [Combined Full]" );
Draw2DHist(h_Al_wgt_upstream,  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

sprintf(Plot_title, "Fitted Wgts Barrel [Combined Full]" );
Draw2DHist(h_Al_wgt_barrel,  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

sprintf(Plot_title, "Fitted Wgts Downstream [Combined Full]" );
Draw2DHist(h_Al_wgt_downstream,  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

sprintf(Plot_title, "Fitted Concave [Combined Full]" );
Draw2DHist(h_Al_wgt_downstreamconcave,  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

wgt_error_vector.clear();
wgt_vector.clear();
Convolution_Tool_TotalPlaylist.Clear_Al_wgt();

for(auto MapIndex : Chisqrt_Top5Map){

  Convolution_Tool_TotalPlaylist.initFULLONLY_RECO_Convolution_Material_Regions_Hists_PlaylistCombinedMC(MapIndex.second.i, MapIndex.second.j, MapIndex.second.k );
Index3 indexinput{MapIndex.second.i, MapIndex.second.j, MapIndex.second.k} ;
double mean = ZShifts[indexinput].mean;
double stddev = ZShifts[indexinput].stddev;
Convolution_Tool_TotalPlaylist.Plot_regions_XYZFit_Full( mean  , stddev, 0, 0, "before");

FitConvolutionTool(Convolution_Tool_TotalPlaylist, 4,
  "fitlog", "log", PDF_label,
wgt_vector, wgt_error_vector );

Convolution_Tool_TotalPlaylist.Fill_Alwgt(wgt_vector, wgt_error_vector);
Convolution_Tool_TotalPlaylist.ApplyFitResults_toFull();
Convolution_Tool_TotalPlaylist.CalMaterial_ChiSqrtFullAfter( ChisqrtX, ChisqrtY, ChisqrtZ, ChisqrtR);
double Chisqrt =  ChisqrtX + ChisqrtY + ChisqrtZ;

sprintf(Plot_title,  "Fit #chi^{2} =  %.1f", Chisqrt  );
std::string PLOT_string(Plot_title);
Convolution_Tool_TotalPlaylist.Plot_regions_XYZFit_Full( mean  , stddev, 1, 1, PLOT_string);

wgt_error_vector.clear();
wgt_vector.clear();
Convolution_Tool_TotalPlaylist.Clear_Al_wgt();

}








//FillFull_Normal_Fit_ParametersXY(double meanX , double sigmaX, double meanY , double sigmaY);
/*
FitConvolutionTool(Convolution_Tool_TotalPlaylist, 1,
  "fitlog", "log", PDF_label,
wgt_vector, wgt_error_vector );

std::cout<<"Finished fit"<<std::endl;
Convolution_Tool_TotalPlaylist.Fill_Alwgt(wgt_vector, wgt_error_vector);
std::cout<<"Applying Wgts"<<std::endl;
Convolution_Tool_TotalPlaylist.ApplyFitResults_toEmpty();
Convolution_Tool_TotalPlaylist.Plot_regions_XYZFit_Empty( BestFit_meanZ  , BestFit_stddevZ, 1, 1, " Best Fit After" );
wgt_error_vector.clear();
wgt_vector.clear();
Convolution_Tool_TotalPlaylist.Clear_Al_wgt();
*/

/*
  sprintf(Plot_title, " Vertex X Convoluted total [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[Bestindex_ChiSqrt_Full.best_Chisqrt_X].mean,
   ZShifts[Bestindex_ChiSqrt_Full.best_Chisqrt_X].stddev, Best_ChiSqrt_Result_Full.Chisqrt_X );
  Draw2DHist(h_Chisqrt_X_Truth_todata_Full[0],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
*/
/*
  //~~~~~~~
  sprintf(Plot_title, "[USCap] Vertex X [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full.upstream.best_Chisqrt_X].mean,
   ZShifts[BestIndex_Regions_Full.upstream.best_Chisqrt_X].stddev, BEST_ChiSqrt_CryoTankRegions_Full.upstream.Chisqrt_X );
  Draw2DHist(h_Chisqrt_X_Truth_todata_Full[1],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

  sprintf(Plot_title, "[barrel] Vertex X [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full.barrel.best_Chisqrt_X].mean,
   ZShifts[BestIndex_Regions_Full.barrel.best_Chisqrt_X].stddev, BEST_ChiSqrt_CryoTankRegions_Full.barrel.Chisqrt_X );
  Draw2DHist(h_Chisqrt_X_Truth_todata_Full[2],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

  sprintf(Plot_title, "[DSCap] Vertex X [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full.downstream.best_Chisqrt_X].mean,
   ZShifts[BestIndex_Regions_Full.downstream.best_Chisqrt_X].stddev, BEST_ChiSqrt_CryoTankRegions_Full.downstream.Chisqrt_X );
  Draw2DHist(h_Chisqrt_X_Truth_todata_Full[3],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

  sprintf(Plot_title, "[Concave] Vertex X [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full.concave.best_Chisqrt_X].mean,
   ZShifts[BestIndex_Regions_Full.concave.best_Chisqrt_X].stddev, BEST_ChiSqrt_CryoTankRegions_Full.concave.Chisqrt_X );
  Draw2DHist(h_Chisqrt_X_Truth_todata_Full[4],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
  //~~~~~~~~~~~~
*/


/*
  sprintf(Plot_title, " Vertex Y [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[Bestindex_ChiSqrt_Full.best_Chisqrt_Y].mean,
   ZShifts[Bestindex_ChiSqrt_Full.best_Chisqrt_Y].stddev,Best_ChiSqrt_Result_Full.Chisqrt_Y );
  Draw2DHist(h_Chisqrt_Y_Truth_todata_Full[0],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
*/
/*
  //~~~~~~~
  sprintf(Plot_title, "[USCap] Vertex Y [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full.upstream.best_Chisqrt_Y].mean,
   ZShifts[BestIndex_Regions_Full.upstream.best_Chisqrt_Y].stddev, BEST_ChiSqrt_CryoTankRegions_Full.upstream.Chisqrt_Y );
  Draw2DHist(h_Chisqrt_Y_Truth_todata_Full[1],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

  sprintf(Plot_title, "[barrel] Vertex Y [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full.barrel.best_Chisqrt_Y].mean,
   ZShifts[BestIndex_Regions_Full.barrel.best_Chisqrt_Y].stddev, BEST_ChiSqrt_CryoTankRegions_Full.barrel.Chisqrt_Y );
  Draw2DHist(h_Chisqrt_Y_Truth_todata_Full[2],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

  sprintf(Plot_title, "[DSCap] Vertex Y [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full.downstream.best_Chisqrt_Y].mean,
   ZShifts[BestIndex_Regions_Full.downstream.best_Chisqrt_Y].stddev, BEST_ChiSqrt_CryoTankRegions_Full.downstream.Chisqrt_Y );
  Draw2DHist(h_Chisqrt_Y_Truth_todata_Full[3],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

  sprintf(Plot_title, "[Concave] Vertex Y [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full.concave.best_Chisqrt_Y].mean,
   ZShifts[BestIndex_Regions_Full.concave.best_Chisqrt_Y].stddev, BEST_ChiSqrt_CryoTankRegions_Full.concave.Chisqrt_Y );
  Draw2DHist(h_Chisqrt_Y_Truth_todata_Full[4],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
  //~~~~~~~~~~~~
*/


//  sprintf(Plot_title, " Vertex R [Combined Full]  Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[Bestindex_ChiSqrt_Full.best_Chisqrt_R].mean,
//   ZShifts[Bestindex_ChiSqrt_Full.best_Chisqrt_R].stddev,Best_ChiSqrt_Result_Full.Chisqrt_R );
//  Draw2DHist(h_Chisqrt_R_Truth_todata_Full[0],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

/*
  //~~~~~~~
  sprintf(Plot_title, "[USCap] Vertex R [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full.upstream.best_Chisqrt_R].mean,
   ZShifts[BestIndex_Regions_Full.upstream.best_Chisqrt_R].stddev, BEST_ChiSqrt_CryoTankRegions_Full.upstream.Chisqrt_R );
  Draw2DHist(h_Chisqrt_R_Truth_todata_Full[1],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

  sprintf(Plot_title, "[barrel] Vertex R [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full.barrel.best_Chisqrt_R].mean,
   ZShifts[BestIndex_Regions_Full.barrel.best_Chisqrt_R].stddev, BEST_ChiSqrt_CryoTankRegions_Full.barrel.Chisqrt_R );
  Draw2DHist(h_Chisqrt_R_Truth_todata_Full[2],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

  sprintf(Plot_title, "[DSCap] Vertex R [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full.downstream.best_Chisqrt_R].mean,
   ZShifts[BestIndex_Regions_Full.downstream.best_Chisqrt_R].stddev, BEST_ChiSqrt_CryoTankRegions_Full.downstream.Chisqrt_R );
  Draw2DHist(h_Chisqrt_R_Truth_todata_Full[3],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

  sprintf(Plot_title, "[Concave] Vertex R [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full.concave.best_Chisqrt_R].mean,
   ZShifts[BestIndex_Regions_Full.concave.best_Chisqrt_R].stddev, BEST_ChiSqrt_CryoTankRegions_Full.concave.Chisqrt_R );
  Draw2DHist(h_Chisqrt_R_Truth_todata_Full[4],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
  //~~~~~~~~~~~~
*/
  //sprintf(Plot_title, " Vertex Z [Combined Full]  Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[Bestindex_ChiSqrt_Full.best_Chisqrt_Z].mean,
  // ZShifts[Bestindex_ChiSqrt_Full.best_Chisqrt_Z].stddev,Best_ChiSqrt_Result_Full.Chisqrt_Z );
  //Draw2DHist(h_Chisqrt_Z_Truth_todata_Full[0],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

/*
  //~~~~~~~
  sprintf(Plot_title, "[USCap] Vertex Z [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full.upstream.best_Chisqrt_Z].mean,
   ZShifts[BestIndex_Regions_Full.upstream.best_Chisqrt_Z].stddev, BEST_ChiSqrt_CryoTankRegions_Full.upstream.Chisqrt_Z );
  Draw2DHist(h_Chisqrt_Z_Truth_todata_Full[1],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

  sprintf(Plot_title, "[barrel] Vertex Z [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full.barrel.best_Chisqrt_Z].mean,
   ZShifts[BestIndex_Regions_Full.barrel.best_Chisqrt_Z].stddev, BEST_ChiSqrt_CryoTankRegions_Full.barrel.Chisqrt_Z );
  Draw2DHist(h_Chisqrt_Z_Truth_todata_Full[2],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

  sprintf(Plot_title, "[DSCap] Vertex Z [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full.downstream.best_Chisqrt_Z].mean,
   ZShifts[BestIndex_Regions_Full.downstream.best_Chisqrt_Z].stddev, BEST_ChiSqrt_CryoTankRegions_Full.downstream.Chisqrt_Z );
  Draw2DHist(h_Chisqrt_Z_Truth_todata_Full[3],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

  sprintf(Plot_title, "[Concave] Vertex Z [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full.concave.best_Chisqrt_Z].mean,
   ZShifts[BestIndex_Regions_Full.concave.best_Chisqrt_Z].stddev, BEST_ChiSqrt_CryoTankRegions_Full.concave.Chisqrt_Z );
  Draw2DHist(h_Chisqrt_Z_Truth_todata_Full[4],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
  //~~~~~~~~~~~~
*/



//  sprintf(Plot_title, " Vertex Z [RCut] [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[Bestindex_ChiSqrt_Full.best_Chisqrt_Z_RCut].mean,
//   ZShifts[Bestindex_ChiSqrt_Full.best_Chisqrt_Z_RCut].stddev, Best_ChiSqrt_Result_Full.Chisqrt_Z_RCut );
//  Draw2DHist(h_Chisqrt_Z_Truth_todata_Full_RCut[0],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

/*
  //~~~~~~~
  sprintf(Plot_title, "[USCap] [RCut] Vertex Z [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full.upstream.best_Chisqrt_Z_RCut].mean,
   ZShifts[BestIndex_Regions_Full.upstream.best_Chisqrt_Z_RCut].stddev, BEST_ChiSqrt_CryoTankRegions_Full.upstream.Chisqrt_Z_RCut );
  Draw2DHist(h_Chisqrt_Z_Truth_todata_Full_RCut[1],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

  sprintf(Plot_title, "[barrel] [RCut] Vertex Z [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full.barrel.best_Chisqrt_Z_RCut].mean,
   ZShifts[BestIndex_Regions_Full.barrel.best_Chisqrt_Z_RCut].stddev, BEST_ChiSqrt_CryoTankRegions_Full.barrel.Chisqrt_Z_RCut );
  Draw2DHist(h_Chisqrt_Z_Truth_todata_Full_RCut[2],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

  sprintf(Plot_title, "[DSCap]  [RCut] Vertex Z [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full.downstream.best_Chisqrt_Z_RCut].mean,
   ZShifts[BestIndex_Regions_Full.downstream.best_Chisqrt_Z_RCut].stddev, BEST_ChiSqrt_CryoTankRegions_Full.downstream.Chisqrt_Z_RCut );
  Draw2DHist(h_Chisqrt_Z_Truth_todata_Full_RCut[3],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

  sprintf(Plot_title, "[Concave] [RCut] Vertex Z [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full.concave.best_Chisqrt_Z_RCut].mean,
   ZShifts[BestIndex_Regions_Full.concave.best_Chisqrt_Z_RCut].stddev, BEST_ChiSqrt_CryoTankRegions_Full.concave.Chisqrt_Z_RCut );
  Draw2DHist(h_Chisqrt_Z_Truth_todata_Full_RCut[4],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
  //~~~~~~~~~~~~
*/

//  sprintf(Plot_title, "Distance to NearestWall [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[Bestindex_ChiSqrt_Full.best_Chisqrt_NearestWall].mean,
//   ZShifts[Bestindex_ChiSqrt_Full.best_Chisqrt_NearestWall].stddev, Best_ChiSqrt_Result_Full.Chisqrt_NearestWall );
//  Draw2DHist(h_Chisqrt_Distancetowall_Truth_todata_Full[0],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
/*
  //~~~~~~~
  sprintf(Plot_title, "[USCap]  [RCut] Distance to Nearest Wall [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full.upstream.best_Chisqrt_NearestWall].mean,
   ZShifts[BestIndex_Regions_Full.upstream.best_Chisqrt_NearestWall].stddev, BEST_ChiSqrt_CryoTankRegions_Full.upstream.Chisqrt_NearestWall );
  Draw2DHist(h_Chisqrt_Distancetowall_Truth_todata_Full[1],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

  sprintf(Plot_title, "[barrel] [RCut] Distance to Nearest Wall [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full.barrel.best_Chisqrt_NearestWall].mean,
   ZShifts[BestIndex_Regions_Full.barrel.best_Chisqrt_NearestWall].stddev, BEST_ChiSqrt_CryoTankRegions_Full.barrel.Chisqrt_NearestWall );
  Draw2DHist(h_Chisqrt_Distancetowall_Truth_todata_Full[2],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

  sprintf(Plot_title, "[DSCap]  [RCut] Distance to Nearest Wall [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full.downstream.best_Chisqrt_NearestWall].mean,
   ZShifts[BestIndex_Regions_Full.downstream.best_Chisqrt_NearestWall].stddev, BEST_ChiSqrt_CryoTankRegions_Full.downstream.Chisqrt_NearestWall );
  Draw2DHist(h_Chisqrt_Distancetowall_Truth_todata_Full[3],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

  sprintf(Plot_title, "[Concave] [RCut] Distance to Nearest Wall [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full.concave.best_Chisqrt_NearestWall].mean,
   ZShifts[BestIndex_Regions_Full.concave.best_Chisqrt_NearestWall].stddev, BEST_ChiSqrt_CryoTankRegions_Full.concave.Chisqrt_NearestWall );
  Draw2DHist(h_Chisqrt_Distancetowall_Truth_todata_Full[4],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
  //~~~~~~~~~~~~
*/

  //sprintf(Plot_title, "Distance to USCap  [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[Bestindex_ChiSqrt_Full.best_Chisqrt_DistancetoUpstreamCap].mean,
  //ZShifts[Bestindex_ChiSqrt_Full.best_Chisqrt_DistancetoUpstreamCap].stddev, Best_ChiSqrt_Result_Full.Chisqrt_DistancetoUpstreamCap );
  //Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Full[0],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

/*
  //~~~~~~~
  sprintf(Plot_title, "[USCap]  Distance to USCap [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full.upstream.best_Chisqrt_DistancetoUpstreamCap].mean,
   ZShifts[BestIndex_Regions_Full.upstream.best_Chisqrt_DistancetoUpstreamCap].stddev, BEST_ChiSqrt_CryoTankRegions_Full.upstream.Chisqrt_DistancetoUpstreamCap );
  Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Full[1],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

  sprintf(Plot_title, "[barrel] Distance to USCap [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full.barrel.best_Chisqrt_DistancetoUpstreamCap].mean,
   ZShifts[BestIndex_Regions_Full.barrel.best_Chisqrt_DistancetoUpstreamCap].stddev, BEST_ChiSqrt_CryoTankRegions_Full.barrel.Chisqrt_DistancetoUpstreamCap );
  Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Full[2],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

  sprintf(Plot_title, "[DSCap]  Distance to USCap [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full.downstream.best_Chisqrt_DistancetoUpstreamCap].mean,
   ZShifts[BestIndex_Regions_Full.downstream.best_Chisqrt_DistancetoUpstreamCap].stddev, BEST_ChiSqrt_CryoTankRegions_Full.downstream.Chisqrt_DistancetoUpstreamCap );
  Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Full[3],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

  sprintf(Plot_title, "[Concave] Distance to USCap [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full.concave.best_Chisqrt_DistancetoUpstreamCap].mean,
   ZShifts[BestIndex_Regions_Full.concave.best_Chisqrt_DistancetoUpstreamCap].stddev, BEST_ChiSqrt_CryoTankRegions_Full.concave.Chisqrt_DistancetoUpstreamCap );
  Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Full[4],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
  //~~~~~~~~~~~~
*/
//  sprintf(Plot_title, "Distance to Downstream Cap Convoluted total [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[Bestindex_ChiSqrt_Full.best_Chisqrt_DistancetoDownstreamCap].mean,
//   ZShifts[Bestindex_ChiSqrt_Full.best_Chisqrt_DistancetoDownstreamCap].stddev, Best_ChiSqrt_Result_Full.Chisqrt_DistancetoDownstreamCap );
//   Draw2DHist(h_Chisqrt_Distanceto_downstreamcap_Truth_todata_Full[0],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

/*
   //~~~~~~~
   sprintf(Plot_title, "[USCap]  Distance to DSCap [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full.upstream.best_Chisqrt_DistancetoDownstreamCap].mean,
    ZShifts[BestIndex_Regions_Full.upstream.best_Chisqrt_DistancetoDownstreamCap].stddev, BEST_ChiSqrt_CryoTankRegions_Full.upstream.Chisqrt_DistancetoDownstreamCap );
   Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Full[1],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

   sprintf(Plot_title, "[barrel] Distance to DSCap [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full.barrel.best_Chisqrt_DistancetoDownstreamCap].mean,
    ZShifts[BestIndex_Regions_Full.barrel.best_Chisqrt_DistancetoDownstreamCap].stddev, BEST_ChiSqrt_CryoTankRegions_Full.barrel.Chisqrt_DistancetoDownstreamCap );
   Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Full[2],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

   sprintf(Plot_title, "[DSCap]  Distance to DSCap [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full.downstream.best_Chisqrt_DistancetoDownstreamCap].mean,
    ZShifts[BestIndex_Regions_Full.downstream.best_Chisqrt_DistancetoDownstreamCap].stddev, BEST_ChiSqrt_CryoTankRegions_Full.downstream.Chisqrt_DistancetoDownstreamCap );
   Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Full[3],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

   sprintf(Plot_title, "[Concave] Distance to DSCap [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full.concave.best_Chisqrt_DistancetoDownstreamCap].mean,
    ZShifts[BestIndex_Regions_Full.concave.best_Chisqrt_DistancetoDownstreamCap].stddev, BEST_ChiSqrt_CryoTankRegions_Full.concave.Chisqrt_DistancetoDownstreamCap );
   Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Full[4],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
   //~~~~~~~~~~~~
*/

   //sprintf(Plot_title, "Distance to USCap [RCut] [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[Bestindex_ChiSqrt_Full.best_Chisqrt_DistancetoUpstreamCap_RCut].mean,
   //ZShifts[Bestindex_ChiSqrt_Full.best_Chisqrt_DistancetoUpstreamCap_RCut].stddev, Best_ChiSqrt_Result_Full.Chisqrt_DistancetoUpstreamCap_RCut );
   //Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_RCut_Full[0],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

/*
  //~~~~~~~
  sprintf(Plot_title, "[USCap]  [RCut] Distance to USCap [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full.upstream.best_Chisqrt_DistancetoUpstreamCap_RCut].mean,
   ZShifts[BestIndex_Regions_Full.upstream.best_Chisqrt_DistancetoUpstreamCap_RCut].stddev, BEST_ChiSqrt_CryoTankRegions_Full.upstream.Chisqrt_DistancetoUpstreamCap_RCut );
  Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Full[1],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

  sprintf(Plot_title, "[barrel] [RCut] Distance to USCap [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full.barrel.best_Chisqrt_DistancetoUpstreamCap_RCut].mean,
   ZShifts[BestIndex_Regions_Full.barrel.best_Chisqrt_DistancetoUpstreamCap_RCut].stddev, BEST_ChiSqrt_CryoTankRegions_Full.barrel.Chisqrt_DistancetoUpstreamCap_RCut );
  Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Full[2],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

  sprintf(Plot_title, "[DSCap]  [RCut] Distance to USCap [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full.downstream.best_Chisqrt_DistancetoUpstreamCap_RCut].mean,
   ZShifts[BestIndex_Regions_Full.downstream.best_Chisqrt_DistancetoUpstreamCap_RCut].stddev, BEST_ChiSqrt_CryoTankRegions_Full.downstream.Chisqrt_DistancetoUpstreamCap_RCut );
  Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Full[3],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

  sprintf(Plot_title, "[Concave] [RCut] Distance to USCap [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full.concave.best_Chisqrt_DistancetoUpstreamCap_RCut].mean,
   ZShifts[BestIndex_Regions_Full.concave.best_Chisqrt_DistancetoUpstreamCap_RCut].stddev, BEST_ChiSqrt_CryoTankRegions_Full.concave.Chisqrt_DistancetoUpstreamCap_RCut );
  Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Full[4],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
  //~~~~~~~~~~~~
*/

//  sprintf(Plot_title, "Distance to DSCap [RCut] [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[Bestindex_ChiSqrt_Full.best_Chisqrt_DistancetoDownstreamCap_RCut].mean,
//   ZShifts[Bestindex_ChiSqrt_Full.best_Chisqrt_DistancetoDownstreamCap_RCut].stddev, Best_ChiSqrt_Result_Full.Chisqrt_DistancetoDownstreamCap_RCut );
//  Draw2DHist(h_Chisqrt_Distanceto_downstreamcap_Truth_todata_RCut_Full[0],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

/*
  //~~~~~~~
  sprintf(Plot_title, "[USCap]  [RCut] Distance to DSCap [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full.upstream.best_Chisqrt_DistancetoDownstreamCap_RCut].mean,
   ZShifts[BestIndex_Regions_Full.upstream.best_Chisqrt_DistancetoDownstreamCap_RCut].stddev, BEST_ChiSqrt_CryoTankRegions_Full.upstream.Chisqrt_DistancetoDownstreamCap_RCut );
  Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Full[1],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

  sprintf(Plot_title, "[barrel] [RCut] Distance to DSCap [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full.barrel.best_Chisqrt_DistancetoDownstreamCap_RCut].mean,
   ZShifts[BestIndex_Regions_Full.barrel.best_Chisqrt_DistancetoDownstreamCap_RCut].stddev, BEST_ChiSqrt_CryoTankRegions_Full.barrel.Chisqrt_DistancetoDownstreamCap_RCut );
  Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Full[2],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

  sprintf(Plot_title, "[DSCap] [RCut] Distance to DSCap [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full.downstream.best_Chisqrt_DistancetoDownstreamCap_RCut].mean,
   ZShifts[BestIndex_Regions_Full.downstream.best_Chisqrt_DistancetoDownstreamCap_RCut].stddev, BEST_ChiSqrt_CryoTankRegions_Full.downstream.Chisqrt_DistancetoDownstreamCap_RCut );
  Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Full[3],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

  sprintf(Plot_title, "[Concave] [RCut] Distance to DSCap [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full.concave.best_Chisqrt_DistancetoDownstreamCap_RCut].mean,
   ZShifts[BestIndex_Regions_Full.concave.best_Chisqrt_DistancetoDownstreamCap_RCut].stddev, BEST_ChiSqrt_CryoTankRegions_Full.concave.Chisqrt_DistancetoDownstreamCap_RCut );
  Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Full[4],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
  //~~~~~~~~~~~~
*/


///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
///  EMPTY
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  //sprintf(Plot_title, " Vertex X [Combined Empty] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[Bestindex_ChiSqrt_Empty.best_Chisqrt_X].mean,
  // ZShifts[Bestindex_ChiSqrt_Empty.best_Chisqrt_X].stddev, Best_ChiSqrt_Result_Empty.Chisqrt_X );
  //Draw2DHist(h_Chisqrt_X_Truth_todata_Empty[0],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

/*
  //~~~~~~~
  sprintf(Plot_title, "[USCap] Vertex X [Combined Empty] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Empty.upstream.best_Chisqrt_X].mean,
   ZShifts[BestIndex_Regions_Empty.upstream.best_Chisqrt_X].stddev, BEST_ChiSqrt_CryoTankRegions_Empty.upstream.Chisqrt_X );
  Draw2DHist(h_Chisqrt_X_Truth_todata_Empty[1],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

  sprintf(Plot_title, "[barrel] Vertex X [Combined Empty] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Empty.barrel.best_Chisqrt_X].mean,
   ZShifts[BestIndex_Regions_Empty.barrel.best_Chisqrt_X].stddev, BEST_ChiSqrt_CryoTankRegions_Empty.barrel.Chisqrt_X );
  Draw2DHist(h_Chisqrt_X_Truth_todata_Empty[2],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

  sprintf(Plot_title, "[DSCap] Vertex X [Combined Empty] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Empty.downstream.best_Chisqrt_X].mean,
   ZShifts[BestIndex_Regions_Empty.downstream.best_Chisqrt_X].stddev, BEST_ChiSqrt_CryoTankRegions_Empty.downstream.Chisqrt_X );
  Draw2DHist(h_Chisqrt_X_Truth_todata_Empty[3],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

  sprintf(Plot_title, "[Concave] Vertex X [Combined Empty] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Empty.concave.best_Chisqrt_X].mean,
   ZShifts[BestIndex_Regions_Empty.concave.best_Chisqrt_X].stddev, BEST_ChiSqrt_CryoTankRegions_Empty.concave.Chisqrt_X );
  Draw2DHist(h_Chisqrt_X_Truth_todata_Empty[4],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
  //~~~~~~~~~~~~
*/



  //sprintf(Plot_title, " Vertex Y [Combined Empty] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[Bestindex_ChiSqrt_Empty.best_Chisqrt_Y].mean,
  //ZShifts[Bestindex_ChiSqrt_Empty.best_Chisqrt_Y].stddev,Best_ChiSqrt_Result_Empty.Chisqrt_Y );
  //Draw2DHist(h_Chisqrt_Y_Truth_todata_Empty[0],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

/*
//~~~~~~~
sprintf(Plot_title, "[USCap] Vertex Y [Combined Empty] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Empty.upstream.best_Chisqrt_Y].mean,
ZShifts[BestIndex_Regions_Empty.upstream.best_Chisqrt_Y].stddev, BEST_ChiSqrt_CryoTankRegions_Empty.upstream.Chisqrt_Y );
Draw2DHist(h_Chisqrt_Y_Truth_todata_Empty[1],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

sprintf(Plot_title, "[barrel] Vertex Y [Combined Empty] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Empty.barrel.best_Chisqrt_Y].mean,
ZShifts[BestIndex_Regions_Empty.barrel.best_Chisqrt_Y].stddev, BEST_ChiSqrt_CryoTankRegions_Empty.barrel.Chisqrt_Y );
Draw2DHist(h_Chisqrt_Y_Truth_todata_Empty[2],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

sprintf(Plot_title, "[DSCap] Vertex Y [Combined Empty] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Empty.downstream.best_Chisqrt_Y].mean,
ZShifts[BestIndex_Regions_Empty.downstream.best_Chisqrt_Y].stddev, BEST_ChiSqrt_CryoTankRegions_Empty.downstream.Chisqrt_Y );
Draw2DHist(h_Chisqrt_Y_Truth_todata_Empty[3],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

sprintf(Plot_title, "[Concave] Vertex Y [Combined Empty] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Empty.concave.best_Chisqrt_Y].mean,
ZShifts[BestIndex_Regions_Empty.concave.best_Chisqrt_Y].stddev, BEST_ChiSqrt_CryoTankRegions_Empty.concave.Chisqrt_Y );
Draw2DHist(h_Chisqrt_Y_Truth_todata_Empty[4],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
//~~~~~~~~~~~~
*/

//sprintf(Plot_title, " Vertex R [Combined Empty]  Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[Bestindex_ChiSqrt_Empty.best_Chisqrt_R].mean,
//ZShifts[Bestindex_ChiSqrt_Empty.best_Chisqrt_R].stddev,Best_ChiSqrt_Result_Empty.Chisqrt_R );
//Draw2DHist(h_Chisqrt_R_Truth_todata_Empty[0],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

/*
//~~~~~~~
sprintf(Plot_title, "[USCap] Vertex R [Combined Empty] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Empty.upstream.best_Chisqrt_R].mean,
ZShifts[BestIndex_Regions_Empty.upstream.best_Chisqrt_R].stddev, BEST_ChiSqrt_CryoTankRegions_Empty.upstream.Chisqrt_R );
Draw2DHist(h_Chisqrt_R_Truth_todata_Empty[1],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

sprintf(Plot_title, "[barrel] Vertex R [Combined Empty] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Empty.barrel.best_Chisqrt_R].mean,
ZShifts[BestIndex_Regions_Empty.barrel.best_Chisqrt_R].stddev, BEST_ChiSqrt_CryoTankRegions_Empty.barrel.Chisqrt_R );
Draw2DHist(h_Chisqrt_R_Truth_todata_Empty[2],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

sprintf(Plot_title, "[DSCap] Vertex R [Combined Empty] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Empty.downstream.best_Chisqrt_R].mean,
ZShifts[BestIndex_Regions_Empty.downstream.best_Chisqrt_R].stddev, BEST_ChiSqrt_CryoTankRegions_Empty.downstream.Chisqrt_R );
Draw2DHist(h_Chisqrt_R_Truth_todata_Empty[3],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

sprintf(Plot_title, "[Concave] Vertex R [Combined Empty] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Empty.concave.best_Chisqrt_R].mean,
ZShifts[BestIndex_Regions_Empty.concave.best_Chisqrt_R].stddev, BEST_ChiSqrt_CryoTankRegions_Empty.concave.Chisqrt_R );
Draw2DHist(h_Chisqrt_R_Truth_todata_Empty[4],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
//~~~~~~~~~~~~

*/

sprintf(Plot_title, " Vertex Z [Combined Full]  Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[Bestindex_ChiSqrt_Empty.best_Chisqrt_Z].mean,
ZShifts[Bestindex_ChiSqrt_Empty.best_Chisqrt_Z].stddev,Best_ChiSqrt_Result_Empty.Chisqrt_Z );
Draw2DHist(h_Chisqrt_Z_Truth_todata_Empty[0],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

/*
//~~~~~~~
sprintf(Plot_title, "[USCap] Vertex Z [Combined Empty] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Empty.upstream.best_Chisqrt_Z].mean,
ZShifts[BestIndex_Regions_Empty.upstream.best_Chisqrt_Z].stddev, BEST_ChiSqrt_CryoTankRegions_Empty.upstream.Chisqrt_Z );
Draw2DHist(h_Chisqrt_Z_Truth_todata_Empty[1],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

sprintf(Plot_title, "[barrel] Vertex Z [Combined Empty] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Empty.barrel.best_Chisqrt_Z].mean,
ZShifts[BestIndex_Regions_Empty.barrel.best_Chisqrt_Z].stddev, BEST_ChiSqrt_CryoTankRegions_Empty.barrel.Chisqrt_Z );
Draw2DHist(h_Chisqrt_Z_Truth_todata_Empty[2],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

sprintf(Plot_title, "[DSCap] Vertex Z [Combined Empty] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Empty.downstream.best_Chisqrt_Z].mean,
ZShifts[BestIndex_Regions_Empty.downstream.best_Chisqrt_Z].stddev, BEST_ChiSqrt_CryoTankRegions_Empty.downstream.Chisqrt_Z );
Draw2DHist(h_Chisqrt_Z_Truth_todata_Empty[3],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

sprintf(Plot_title, "[Concave] Vertex Z [Combined Empty] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Empty.concave.best_Chisqrt_Z].mean,
ZShifts[BestIndex_Regions_Empty.concave.best_Chisqrt_Z].stddev, BEST_ChiSqrt_CryoTankRegions_Empty.concave.Chisqrt_Z );
Draw2DHist(h_Chisqrt_Z_Truth_todata_Empty[4],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
//~~~~~~~~~~~~
*/

sprintf(Plot_title, " Vertex Z [RCut] [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[Bestindex_ChiSqrt_Empty.best_Chisqrt_Z_RCut].mean,
ZShifts[Bestindex_ChiSqrt_Empty.best_Chisqrt_Z_RCut].stddev, Best_ChiSqrt_Result_Empty.Chisqrt_Z_RCut );
Draw2DHist(h_Chisqrt_Z_Truth_todata_Empty_RCut[0],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

/*
//~~~~~~~
sprintf(Plot_title, "[USCap] [RCut] Vertex Z [Combined Empty] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Empty.upstream.best_Chisqrt_Z_RCut].mean,
ZShifts[BestIndex_Regions_Empty.upstream.best_Chisqrt_Z_RCut].stddev, BEST_ChiSqrt_CryoTankRegions_Empty.upstream.Chisqrt_Z_RCut );
Draw2DHist(h_Chisqrt_Z_Truth_todata_Empty_RCut[1],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

sprintf(Plot_title, "[barrel] [RCut] Vertex Z [Combined Empty] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Empty.barrel.best_Chisqrt_Z_RCut].mean,
ZShifts[BestIndex_Regions_Empty.barrel.best_Chisqrt_Z_RCut].stddev, BEST_ChiSqrt_CryoTankRegions_Empty.barrel.Chisqrt_Z_RCut );
Draw2DHist(h_Chisqrt_Z_Truth_todata_Empty_RCut[2],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

sprintf(Plot_title, "[DSCap]  [RCut] Vertex Z [Combined Empty] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Empty.downstream.best_Chisqrt_Z_RCut].mean,
ZShifts[BestIndex_Regions_Empty.downstream.best_Chisqrt_Z_RCut].stddev, BEST_ChiSqrt_CryoTankRegions_Empty.downstream.Chisqrt_Z_RCut );
Draw2DHist(h_Chisqrt_Z_Truth_todata_Empty_RCut[3],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

sprintf(Plot_title, "[Concave] [RCut] Vertex Z [Combined Empty] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Empty.concave.best_Chisqrt_Z_RCut].mean,
ZShifts[BestIndex_Regions_Empty.concave.best_Chisqrt_Z_RCut].stddev, BEST_ChiSqrt_CryoTankRegions_Empty.concave.Chisqrt_Z_RCut );
Draw2DHist(h_Chisqrt_Z_Truth_todata_Empty_RCut[4],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
//~~~~~~~~~~~~
*/
sprintf(Plot_title, "Distance to NearestWall [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[Bestindex_ChiSqrt_Empty.best_Chisqrt_NearestWall].mean,
ZShifts[Bestindex_ChiSqrt_Empty.best_Chisqrt_NearestWall].stddev, Best_ChiSqrt_Result_Empty.Chisqrt_NearestWall );
Draw2DHist(h_Chisqrt_Distancetowall_Truth_todata_Empty[0],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
/*

//~~~~~~~
sprintf(Plot_title, "[USCap]  [RCut] Distance to Nearest Wall [Combined Empty] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Empty.upstream.best_Chisqrt_NearestWall].mean,
ZShifts[BestIndex_Regions_Empty.upstream.best_Chisqrt_NearestWall].stddev, BEST_ChiSqrt_CryoTankRegions_Empty.upstream.Chisqrt_NearestWall );
Draw2DHist(h_Chisqrt_Distancetowall_Truth_todata_Empty[1],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

sprintf(Plot_title, "[barrel] [RCut] Distance to Nearest Wall [Combined Empty] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Empty.barrel.best_Chisqrt_NearestWall].mean,
ZShifts[BestIndex_Regions_Empty.barrel.best_Chisqrt_NearestWall].stddev, BEST_ChiSqrt_CryoTankRegions_Empty.barrel.Chisqrt_NearestWall );
Draw2DHist(h_Chisqrt_Distancetowall_Truth_todata_Empty[2],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

sprintf(Plot_title, "[DSCap]  [RCut] Distance to Nearest Wall [Combined Empty] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Empty.downstream.best_Chisqrt_NearestWall].mean,
ZShifts[BestIndex_Regions_Empty.downstream.best_Chisqrt_NearestWall].stddev, BEST_ChiSqrt_CryoTankRegions_Empty.downstream.Chisqrt_NearestWall );
Draw2DHist(h_Chisqrt_Distancetowall_Truth_todata_Empty[3],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

sprintf(Plot_title, "[Concave] [RCut] Distance to Nearest Wall [Combined Empty] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Empty.concave.best_Chisqrt_NearestWall].mean,
ZShifts[BestIndex_Regions_Empty.concave.best_Chisqrt_NearestWall].stddev, BEST_ChiSqrt_CryoTankRegions_Empty.concave.Chisqrt_NearestWall );
Draw2DHist(h_Chisqrt_Distancetowall_Truth_todata_Empty[4],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
//~~~~~~~~~~~~
*/

sprintf(Plot_title, "Distance to USCap [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[Bestindex_ChiSqrt_Empty.best_Chisqrt_DistancetoUpstreamCap].mean,
ZShifts[Bestindex_ChiSqrt_Empty.best_Chisqrt_DistancetoUpstreamCap].stddev, Best_ChiSqrt_Result_Empty.Chisqrt_DistancetoUpstreamCap );
Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Empty[0],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

/*
//~~~~~~~
sprintf(Plot_title, "[USCap]  Distance to USCap [Combined Empty] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Empty.upstream.best_Chisqrt_DistancetoUpstreamCap].mean,
ZShifts[BestIndex_Regions_Empty.upstream.best_Chisqrt_DistancetoUpstreamCap].stddev, BEST_ChiSqrt_CryoTankRegions_Empty.upstream.Chisqrt_DistancetoUpstreamCap );
Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Empty[1],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

sprintf(Plot_title, "[barrel] Distance to USCap [Combined Empty] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Empty.barrel.best_Chisqrt_DistancetoUpstreamCap].mean,
ZShifts[BestIndex_Regions_Empty.barrel.best_Chisqrt_DistancetoUpstreamCap].stddev, BEST_ChiSqrt_CryoTankRegions_Empty.barrel.Chisqrt_DistancetoUpstreamCap );
Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Empty[2],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

sprintf(Plot_title, "[DSCap]  Distance to USCap [Combined Empty] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Empty.downstream.best_Chisqrt_DistancetoUpstreamCap].mean,
ZShifts[BestIndex_Regions_Empty.downstream.best_Chisqrt_DistancetoUpstreamCap].stddev, BEST_ChiSqrt_CryoTankRegions_Empty.downstream.Chisqrt_DistancetoUpstreamCap );
Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Empty[3],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

sprintf(Plot_title, "[Concave] Distance to USCap [Combined Empty] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Empty.concave.best_Chisqrt_DistancetoUpstreamCap].mean,
ZShifts[BestIndex_Regions_Empty.concave.best_Chisqrt_DistancetoUpstreamCap].stddev, BEST_ChiSqrt_CryoTankRegions_Empty.concave.Chisqrt_DistancetoUpstreamCap );
Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Empty[4],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
//~~~~~~~~~~~~
*/
sprintf(Plot_title, "Distance to DS Cap [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[Bestindex_ChiSqrt_Empty.best_Chisqrt_DistancetoDownstreamCap].mean,
ZShifts[Bestindex_ChiSqrt_Empty.best_Chisqrt_DistancetoDownstreamCap].stddev, Best_ChiSqrt_Result_Empty.Chisqrt_DistancetoDownstreamCap );
Draw2DHist(h_Chisqrt_Distanceto_downstreamcap_Truth_todata_Empty[0],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

/*
//~~~~~~~
sprintf(Plot_title, "[USCap]  Distance to DSCap [Combined Empty] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Empty.upstream.best_Chisqrt_DistancetoDownstreamCap].mean,
ZShifts[BestIndex_Regions_Empty.upstream.best_Chisqrt_DistancetoDownstreamCap].stddev, BEST_ChiSqrt_CryoTankRegions_Empty.upstream.Chisqrt_DistancetoDownstreamCap );
Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Empty[1],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

sprintf(Plot_title, "[barrel] Distance to DSCap [Combined Empty] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Empty.barrel.best_Chisqrt_DistancetoDownstreamCap].mean,
ZShifts[BestIndex_Regions_Empty.barrel.best_Chisqrt_DistancetoDownstreamCap].stddev, BEST_ChiSqrt_CryoTankRegions_Empty.barrel.Chisqrt_DistancetoDownstreamCap );
Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Empty[2],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

sprintf(Plot_title, "[DSCap]  Distance to DSCap [Combined Empty] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Empty.downstream.best_Chisqrt_DistancetoDownstreamCap].mean,
ZShifts[BestIndex_Regions_Empty.downstream.best_Chisqrt_DistancetoDownstreamCap].stddev, BEST_ChiSqrt_CryoTankRegions_Empty.downstream.Chisqrt_DistancetoDownstreamCap );
Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Empty[3],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

sprintf(Plot_title, "[Concave] Distance to DSCap [Combined Empty] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Empty.concave.best_Chisqrt_DistancetoDownstreamCap].mean,
ZShifts[BestIndex_Regions_Empty.concave.best_Chisqrt_DistancetoDownstreamCap].stddev, BEST_ChiSqrt_CryoTankRegions_Empty.concave.Chisqrt_DistancetoDownstreamCap );
Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Empty[4],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
//~~~~~~~~~~~~
*/

sprintf(Plot_title, "Distance to USCap [RCut] [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[Bestindex_ChiSqrt_Empty.best_Chisqrt_DistancetoUpstreamCap_RCut].mean,
ZShifts[Bestindex_ChiSqrt_Empty.best_Chisqrt_DistancetoUpstreamCap_RCut].stddev, Best_ChiSqrt_Result_Empty.Chisqrt_DistancetoUpstreamCap_RCut );
Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_RCut_Empty[0],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

/*
//~~~~~~~
sprintf(Plot_title, "[USCap]  [RCut] Distance to USCap [Combined Empty] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Empty.upstream.best_Chisqrt_DistancetoUpstreamCap_RCut].mean,
ZShifts[BestIndex_Regions_Empty.upstream.best_Chisqrt_DistancetoUpstreamCap_RCut].stddev, BEST_ChiSqrt_CryoTankRegions_Empty.upstream.Chisqrt_DistancetoUpstreamCap_RCut );
Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Empty[1],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

sprintf(Plot_title, "[barrel] [RCut] Distance to USCap [Combined Empty] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Empty.barrel.best_Chisqrt_DistancetoUpstreamCap_RCut].mean,
ZShifts[BestIndex_Regions_Empty.barrel.best_Chisqrt_DistancetoUpstreamCap_RCut].stddev, BEST_ChiSqrt_CryoTankRegions_Empty.barrel.Chisqrt_DistancetoUpstreamCap_RCut );
Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Empty[2],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

sprintf(Plot_title, "[DSCap]  [RCut] Distance to USCap [Combined Empty] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Empty.downstream.best_Chisqrt_DistancetoUpstreamCap_RCut].mean,
ZShifts[BestIndex_Regions_Empty.downstream.best_Chisqrt_DistancetoUpstreamCap_RCut].stddev, BEST_ChiSqrt_CryoTankRegions_Empty.downstream.Chisqrt_DistancetoUpstreamCap_RCut );
Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Empty[3],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

sprintf(Plot_title, "[Concave] [RCut] Distance to USCap [Combined Empty] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Empty.concave.best_Chisqrt_DistancetoUpstreamCap_RCut].mean,
ZShifts[BestIndex_Regions_Empty.concave.best_Chisqrt_DistancetoUpstreamCap_RCut].stddev, BEST_ChiSqrt_CryoTankRegions_Empty.concave.Chisqrt_DistancetoUpstreamCap_RCut );
Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Empty[4],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
//~~~~~~~~~~~~
*/
sprintf(Plot_title, "Distance to  DSCap [RCut] Convoluted total [Combined Full] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[Bestindex_ChiSqrt_Empty.best_Chisqrt_DistancetoDownstreamCap_RCut].mean,
ZShifts[Bestindex_ChiSqrt_Empty.best_Chisqrt_DistancetoDownstreamCap_RCut].stddev, Best_ChiSqrt_Result_Empty.Chisqrt_DistancetoDownstreamCap_RCut );
Draw2DHist(h_Chisqrt_Distanceto_downstreamcap_Truth_todata_RCut_Empty[0],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

/*
//~~~~~~~
sprintf(Plot_title, "[USCap]  [RCut] Distance to DSCap [Combined Empty] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Empty.upstream.best_Chisqrt_DistancetoDownstreamCap_RCut].mean,
ZShifts[BestIndex_Regions_Empty.upstream.best_Chisqrt_DistancetoDownstreamCap_RCut].stddev, BEST_ChiSqrt_CryoTankRegions_Empty.upstream.Chisqrt_DistancetoDownstreamCap_RCut );
Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Empty[1],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

sprintf(Plot_title, "[barrel] [RCut] Distance to DSCap [Combined Empty] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Empty.barrel.best_Chisqrt_DistancetoDownstreamCap_RCut].mean,
ZShifts[BestIndex_Regions_Empty.barrel.best_Chisqrt_DistancetoDownstreamCap_RCut].stddev, BEST_ChiSqrt_CryoTankRegions_Empty.barrel.Chisqrt_DistancetoDownstreamCap_RCut );
Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Empty[2],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

sprintf(Plot_title, "[DSCap] [RCut] Distance to DSCap [Combined Empty] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Empty.downstream.best_Chisqrt_DistancetoDownstreamCap_RCut].mean,
ZShifts[BestIndex_Regions_Empty.downstream.best_Chisqrt_DistancetoDownstreamCap_RCut].stddev, BEST_ChiSqrt_CryoTankRegions_Empty.downstream.Chisqrt_DistancetoDownstreamCap_RCut );
Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Empty[3],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

sprintf(Plot_title, "[Concave] [RCut] Distance to DSCap [Combined Empty] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Empty.concave.best_Chisqrt_DistancetoDownstreamCap_RCut].mean,
ZShifts[BestIndex_Regions_Empty.concave.best_Chisqrt_DistancetoDownstreamCap_RCut].stddev, BEST_ChiSqrt_CryoTankRegions_Empty.concave.Chisqrt_DistancetoDownstreamCap_RCut );
Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Empty[4],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
//~~~~~~~~~~~~
  ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  ///  Full - EMPTY
  ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

    sprintf(Plot_title, " Vertex X [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[Bestindex_ChiSqrt_Full_Empty.best_Chisqrt_X].mean,
     ZShifts[Bestindex_ChiSqrt_Full_Empty.best_Chisqrt_X].stddev, Best_ChiSqrt_Result_Full_Empty.Chisqrt_X );
    Draw2DHist(h_Chisqrt_X_Truth_todata_Full_Empty[0],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
/*
    //~~~~~~~
    sprintf(Plot_title, "[USCap] Vertex X [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full_Empty.upstream.best_Chisqrt_X].mean,
     ZShifts[BestIndex_Regions_Full_Empty.upstream.best_Chisqrt_X].stddev, BEST_ChiSqrt_CryoTankRegions_Full_Empty.upstream.Chisqrt_X );
    Draw2DHist(h_Chisqrt_X_Truth_todata_Full_Empty[1],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

    sprintf(Plot_title, "[barrel] Vertex X [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full_Empty.barrel.best_Chisqrt_X].mean,
     ZShifts[BestIndex_Regions_Full_Empty.barrel.best_Chisqrt_X].stddev, BEST_ChiSqrt_CryoTankRegions_Full_Empty.barrel.Chisqrt_X );
    Draw2DHist(h_Chisqrt_X_Truth_todata_Full_Empty[2],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

    sprintf(Plot_title, "[DSCap] Vertex X [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full_Empty.downstream.best_Chisqrt_X].mean,
     ZShifts[BestIndex_Regions_Full_Empty.downstream.best_Chisqrt_X].stddev, BEST_ChiSqrt_CryoTankRegions_Full_Empty.downstream.Chisqrt_X );
    Draw2DHist(h_Chisqrt_X_Truth_todata_Full_Empty[3],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

    sprintf(Plot_title, "[Concave] Vertex X [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full_Empty.concave.best_Chisqrt_X].mean,
     ZShifts[BestIndex_Regions_Full_Empty.concave.best_Chisqrt_X].stddev, BEST_ChiSqrt_CryoTankRegions_Full_Empty.concave.Chisqrt_X );
    Draw2DHist(h_Chisqrt_X_Truth_todata_Full_Empty[4],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
    //~~~~~~~~~~~~
*/

    sprintf(Plot_title, " Vertex Y Convoluted total [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[Bestindex_ChiSqrt_Full_Empty.best_Chisqrt_Y].mean,
     ZShifts[Bestindex_ChiSqrt_Full_Empty.best_Chisqrt_Y].stddev,Best_ChiSqrt_Result_Full_Empty.Chisqrt_Y );
    Draw2DHist(h_Chisqrt_Y_Truth_todata_Full_Empty[0],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
/*
    //~~~~~~~
    sprintf(Plot_title, "[USCap] Vertex Y [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full_Empty.upstream.best_Chisqrt_Y].mean,
     ZShifts[BestIndex_Regions_Full_Empty.upstream.best_Chisqrt_Y].stddev, BEST_ChiSqrt_CryoTankRegions_Full_Empty.upstream.Chisqrt_Y );
    Draw2DHist(h_Chisqrt_Y_Truth_todata_Full_Empty[1],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

    sprintf(Plot_title, "[barrel] Vertex Y [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full_Empty.barrel.best_Chisqrt_Y].mean,
     ZShifts[BestIndex_Regions_Full_Empty.barrel.best_Chisqrt_Y].stddev, BEST_ChiSqrt_CryoTankRegions_Full_Empty.barrel.Chisqrt_Y );
    Draw2DHist(h_Chisqrt_Y_Truth_todata_Full_Empty[2],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

    sprintf(Plot_title, "[DSCap] Vertex Y [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full_Empty.downstream.best_Chisqrt_Y].mean,
     ZShifts[BestIndex_Regions_Full_Empty.downstream.best_Chisqrt_Y].stddev, BEST_ChiSqrt_CryoTankRegions_Full_Empty.downstream.Chisqrt_Y );
    Draw2DHist(h_Chisqrt_Y_Truth_todata_Full_Empty[3],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

    sprintf(Plot_title, "[Concave] Vertex Y [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full_Empty.concave.best_Chisqrt_Y].mean,
     ZShifts[BestIndex_Regions_Full_Empty.concave.best_Chisqrt_Y].stddev, BEST_ChiSqrt_CryoTankRegions_Full_Empty.concave.Chisqrt_Y );
    Draw2DHist(h_Chisqrt_Y_Truth_todata_Full_Empty[4],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
    //~~~~~~~~~~~~
*/
    sprintf(Plot_title, " Vertex R Convoluted total [Combined F-E]  Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[Bestindex_ChiSqrt_Full_Empty.best_Chisqrt_R].mean,
     ZShifts[Bestindex_ChiSqrt_Full_Empty.best_Chisqrt_R].stddev,Best_ChiSqrt_Result_Full_Empty.Chisqrt_R );
    Draw2DHist(h_Chisqrt_R_Truth_todata_Full_Empty[0],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
/*
    //~~~~~~~
    sprintf(Plot_title, "[USCap] Vertex R [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full_Empty.upstream.best_Chisqrt_R].mean,
     ZShifts[BestIndex_Regions_Full_Empty.upstream.best_Chisqrt_R].stddev, BEST_ChiSqrt_CryoTankRegions_Full_Empty.upstream.Chisqrt_R );
    Draw2DHist(h_Chisqrt_R_Truth_todata_Full_Empty[1],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

    sprintf(Plot_title, "[barrel] Vertex R [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full_Empty.barrel.best_Chisqrt_R].mean,
     ZShifts[BestIndex_Regions_Full_Empty.barrel.best_Chisqrt_R].stddev, BEST_ChiSqrt_CryoTankRegions_Full_Empty.barrel.Chisqrt_R );
    Draw2DHist(h_Chisqrt_R_Truth_todata_Full_Empty[2],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

    sprintf(Plot_title, "[DSCap] Vertex R [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full_Empty.downstream.best_Chisqrt_R].mean,
     ZShifts[BestIndex_Regions_Full_Empty.downstream.best_Chisqrt_R].stddev, BEST_ChiSqrt_CryoTankRegions_Full_Empty.downstream.Chisqrt_R );
    Draw2DHist(h_Chisqrt_R_Truth_todata_Full_Empty[3],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

    sprintf(Plot_title, "[Concave] Vertex R [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full_Empty.concave.best_Chisqrt_R].mean,
     ZShifts[BestIndex_Regions_Full_Empty.concave.best_Chisqrt_R].stddev, BEST_ChiSqrt_CryoTankRegions_Full_Empty.concave.Chisqrt_R );
    Draw2DHist(h_Chisqrt_R_Truth_todata_Full_Empty[4],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
    //~~~~~~~~~~~~
*/

    sprintf(Plot_title, " Vertex Z Convoluted total [Combined F-E]  Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[Bestindex_ChiSqrt_Full_Empty.best_Chisqrt_Z].mean,
     ZShifts[Bestindex_ChiSqrt_Full_Empty.best_Chisqrt_Z].stddev,Best_ChiSqrt_Result_Full_Empty.Chisqrt_Z );
    Draw2DHist(h_Chisqrt_Z_Truth_todata_Full_Empty[0],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
/*
    //~~~~~~~
    sprintf(Plot_title, "[USCap] Vertex Z [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full_Empty.upstream.best_Chisqrt_Z].mean,
     ZShifts[BestIndex_Regions_Full_Empty.upstream.best_Chisqrt_Z].stddev, BEST_ChiSqrt_CryoTankRegions_Full_Empty.upstream.Chisqrt_Z );
    Draw2DHist(h_Chisqrt_Z_Truth_todata_Full_Empty[1],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

    sprintf(Plot_title, "[barrel] Vertex Z [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full_Empty.barrel.best_Chisqrt_Z].mean,
     ZShifts[BestIndex_Regions_Full_Empty.barrel.best_Chisqrt_Z].stddev, BEST_ChiSqrt_CryoTankRegions_Full_Empty.barrel.Chisqrt_Z );
    Draw2DHist(h_Chisqrt_Z_Truth_todata_Full_Empty[2],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

    sprintf(Plot_title, "[DSCap] Vertex Z [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full_Empty.downstream.best_Chisqrt_Z].mean,
     ZShifts[BestIndex_Regions_Full_Empty.downstream.best_Chisqrt_Z].stddev, BEST_ChiSqrt_CryoTankRegions_Full_Empty.downstream.Chisqrt_Z );
    Draw2DHist(h_Chisqrt_Z_Truth_todata_Full_Empty[3],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

    sprintf(Plot_title, "[Concave] Vertex Z [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full_Empty.concave.best_Chisqrt_Z].mean,
     ZShifts[BestIndex_Regions_Full_Empty.concave.best_Chisqrt_Z].stddev, BEST_ChiSqrt_CryoTankRegions_Full_Empty.concave.Chisqrt_Z );
    Draw2DHist(h_Chisqrt_Z_Truth_todata_Full_Empty[4],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
    //~~~~~~~~~~~~
*/

    sprintf(Plot_title, " Vertex Z [RCut] Convoluted total [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[Bestindex_ChiSqrt_Full_Empty.best_Chisqrt_Z_RCut].mean,
     ZShifts[Bestindex_ChiSqrt_Full_Empty.best_Chisqrt_Z_RCut].stddev, Best_ChiSqrt_Result_Full_Empty.Chisqrt_Z_RCut );
    Draw2DHist(h_Chisqrt_Z_Truth_todata_Full_Empty_RCut[0],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);


/*
      //~~~~~~~
      sprintf(Plot_title, "[USCap] [RCut] Vertex Z [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full_Empty.upstream.best_Chisqrt_Z_RCut].mean,
       ZShifts[BestIndex_Regions_Full_Empty.upstream.best_Chisqrt_Z_RCut].stddev, BEST_ChiSqrt_CryoTankRegions_Full_Empty.upstream.Chisqrt_Z_RCut );
      Draw2DHist(h_Chisqrt_Z_Truth_todata_Full_Empty_RCut[1],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

      sprintf(Plot_title, "[barrel] [RCut] Vertex Z [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full_Empty.barrel.best_Chisqrt_Z_RCut].mean,
       ZShifts[BestIndex_Regions_Full_Empty.barrel.best_Chisqrt_Z_RCut].stddev, BEST_ChiSqrt_CryoTankRegions_Full_Empty.barrel.Chisqrt_Z_RCut );
      Draw2DHist(h_Chisqrt_Z_Truth_todata_Full_Empty_RCut[2],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

      sprintf(Plot_title, "[DSCap]  [RCut] Vertex Z [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full_Empty.downstream.best_Chisqrt_Z_RCut].mean,
       ZShifts[BestIndex_Regions_Full_Empty.downstream.best_Chisqrt_Z_RCut].stddev, BEST_ChiSqrt_CryoTankRegions_Full_Empty.downstream.Chisqrt_Z_RCut );
      Draw2DHist(h_Chisqrt_Z_Truth_todata_Full_Empty_RCut[3],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

      sprintf(Plot_title, "[Concave] [RCut] Vertex Z [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full_Empty.concave.best_Chisqrt_Z_RCut].mean,
       ZShifts[BestIndex_Regions_Full_Empty.concave.best_Chisqrt_Z_RCut].stddev, BEST_ChiSqrt_CryoTankRegions_Full_Empty.concave.Chisqrt_Z_RCut );
      Draw2DHist(h_Chisqrt_Z_Truth_todata_Full_Empty_RCut[4],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
      //~~~~~~~~~~~~
*/
    sprintf(Plot_title, "Distance to NearestWall [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[Bestindex_ChiSqrt_Full_Empty.best_Chisqrt_NearestWall].mean,
     ZShifts[Bestindex_ChiSqrt_Full_Empty.best_Chisqrt_NearestWall].stddev, Best_ChiSqrt_Result_Full_Empty.Chisqrt_NearestWall );
    Draw2DHist(h_Chisqrt_Distancetowall_Truth_todata_Full_Empty[0],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
/*
    //~~~~~~~
    sprintf(Plot_title, "[USCap]  [RCut] Distance to Nearest Wall [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full_Empty.upstream.best_Chisqrt_NearestWall].mean,
     ZShifts[BestIndex_Regions_Full_Empty.upstream.best_Chisqrt_NearestWall].stddev, BEST_ChiSqrt_CryoTankRegions_Full_Empty.upstream.Chisqrt_NearestWall );
    Draw2DHist(h_Chisqrt_Distancetowall_Truth_todata_Full_Empty[1],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

    sprintf(Plot_title, "[barrel] [RCut] Distance to Nearest Wall [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full_Empty.barrel.best_Chisqrt_NearestWall].mean,
     ZShifts[BestIndex_Regions_Full_Empty.barrel.best_Chisqrt_NearestWall].stddev, BEST_ChiSqrt_CryoTankRegions_Full_Empty.barrel.Chisqrt_NearestWall );
    Draw2DHist(h_Chisqrt_Distancetowall_Truth_todata_Full_Empty[2],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

    sprintf(Plot_title, "[DSCap]  [RCut] Distance to Nearest Wall [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full_Empty.downstream.best_Chisqrt_NearestWall].mean,
     ZShifts[BestIndex_Regions_Full_Empty.downstream.best_Chisqrt_NearestWall].stddev, BEST_ChiSqrt_CryoTankRegions_Full_Empty.downstream.Chisqrt_NearestWall );
    Draw2DHist(h_Chisqrt_Distancetowall_Truth_todata_Full_Empty[3],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

    sprintf(Plot_title, "[Concave] [RCut] Distance to Nearest Wall [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full_Empty.concave.best_Chisqrt_NearestWall].mean,
     ZShifts[BestIndex_Regions_Full_Empty.concave.best_Chisqrt_NearestWall].stddev, BEST_ChiSqrt_CryoTankRegions_Full_Empty.concave.Chisqrt_NearestWall );
    Draw2DHist(h_Chisqrt_Distancetowall_Truth_todata_Full_Empty[4],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
    //~~~~~~~~~~~~
*/

    sprintf(Plot_title, "Distance to USCap  Convoluted total [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[Bestindex_ChiSqrt_Full_Empty.best_Chisqrt_DistancetoUpstreamCap].mean,
     ZShifts[Bestindex_ChiSqrt_Full_Empty.best_Chisqrt_DistancetoUpstreamCap].stddev, Best_ChiSqrt_Result_Full_Empty.Chisqrt_DistancetoUpstreamCap );
    Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Full_Empty[0],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
/*
    //~~~~~~~
    sprintf(Plot_title, "[USCap]  Distance to USCap [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full_Empty.upstream.best_Chisqrt_DistancetoUpstreamCap].mean,
     ZShifts[BestIndex_Regions_Full_Empty.upstream.best_Chisqrt_DistancetoUpstreamCap].stddev, BEST_ChiSqrt_CryoTankRegions_Full_Empty.upstream.Chisqrt_DistancetoUpstreamCap );
    Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Full_Empty[1],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

    sprintf(Plot_title, "[barrel] Distance to USCap [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full_Empty.barrel.best_Chisqrt_DistancetoUpstreamCap].mean,
     ZShifts[BestIndex_Regions_Full_Empty.barrel.best_Chisqrt_DistancetoUpstreamCap].stddev, BEST_ChiSqrt_CryoTankRegions_Full_Empty.barrel.Chisqrt_DistancetoUpstreamCap );
    Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Full_Empty[2],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

    sprintf(Plot_title, "[DSCap]  Distance to USCap [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full_Empty.downstream.best_Chisqrt_DistancetoUpstreamCap].mean,
     ZShifts[BestIndex_Regions_Full_Empty.downstream.best_Chisqrt_DistancetoUpstreamCap].stddev, BEST_ChiSqrt_CryoTankRegions_Full_Empty.downstream.Chisqrt_DistancetoUpstreamCap );
    Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Full_Empty[3],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

    sprintf(Plot_title, "[Concave] Distance to USCap [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full_Empty.concave.best_Chisqrt_DistancetoUpstreamCap].mean,
     ZShifts[BestIndex_Regions_Full_Empty.concave.best_Chisqrt_DistancetoUpstreamCap].stddev, BEST_ChiSqrt_CryoTankRegions_Full_Empty.concave.Chisqrt_DistancetoUpstreamCap );
    Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Full_Empty[4],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
    //~~~~~~~~~~~~

*/
    sprintf(Plot_title, "Distance to downstream Cap Convoluted total [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[Bestindex_ChiSqrt_Full_Empty.best_Chisqrt_DistancetoDownstreamCap].mean,
     ZShifts[Bestindex_ChiSqrt_Full_Empty.best_Chisqrt_DistancetoDownstreamCap].stddev, Best_ChiSqrt_Result_Full_Empty.Chisqrt_DistancetoDownstreamCap );
     Draw2DHist(h_Chisqrt_Distanceto_downstreamcap_Truth_todata_Full_Empty[0],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
/*
     //~~~~~~~
     sprintf(Plot_title, "[USCap]  Distance to DSCap [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full_Empty.upstream.best_Chisqrt_DistancetoDownstreamCap].mean,
      ZShifts[BestIndex_Regions_Full_Empty.upstream.best_Chisqrt_DistancetoDownstreamCap].stddev, BEST_ChiSqrt_CryoTankRegions_Full_Empty.upstream.Chisqrt_DistancetoDownstreamCap );
     Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Full_Empty[1],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

     sprintf(Plot_title, "[barrel] Distance to DSCap [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full_Empty.barrel.best_Chisqrt_DistancetoDownstreamCap].mean,
      ZShifts[BestIndex_Regions_Full_Empty.barrel.best_Chisqrt_DistancetoDownstreamCap].stddev, BEST_ChiSqrt_CryoTankRegions_Full_Empty.barrel.Chisqrt_DistancetoDownstreamCap );
     Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Full_Empty[2],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

     sprintf(Plot_title, "[DSCap]  Distance to DSCap [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full_Empty.downstream.best_Chisqrt_DistancetoDownstreamCap].mean,
      ZShifts[BestIndex_Regions_Full_Empty.downstream.best_Chisqrt_DistancetoDownstreamCap].stddev, BEST_ChiSqrt_CryoTankRegions_Full_Empty.downstream.Chisqrt_DistancetoDownstreamCap );
     Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Full_Empty[3],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

     sprintf(Plot_title, "[Concave] Distance to DSCap [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full_Empty.concave.best_Chisqrt_DistancetoDownstreamCap].mean,
      ZShifts[BestIndex_Regions_Full_Empty.concave.best_Chisqrt_DistancetoDownstreamCap].stddev, BEST_ChiSqrt_CryoTankRegions_Full_Empty.concave.Chisqrt_DistancetoDownstreamCap );
     Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Full_Empty[4],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
     //~~~~~~~~~~~~
*/

    sprintf(Plot_title, "Distance to UpstreamCap [RCut] Convoluted total [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[Bestindex_ChiSqrt_Full_Empty.best_Chisqrt_DistancetoUpstreamCap_RCut].mean,
     ZShifts[Bestindex_ChiSqrt_Full_Empty.best_Chisqrt_DistancetoUpstreamCap_RCut].stddev, Best_ChiSqrt_Result_Full_Empty.Chisqrt_DistancetoUpstreamCap_RCut );
    Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_RCut_Full_Empty[0],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
/*
    //~~~~~~~
    sprintf(Plot_title, "[USCap]  [RCut] Distance to USCap [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full_Empty.upstream.best_Chisqrt_DistancetoUpstreamCap_RCut].mean,
     ZShifts[BestIndex_Regions_Full_Empty.upstream.best_Chisqrt_DistancetoUpstreamCap_RCut].stddev, BEST_ChiSqrt_CryoTankRegions_Full_Empty.upstream.Chisqrt_DistancetoUpstreamCap_RCut );
    Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Full_Empty[1],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

    sprintf(Plot_title, "[barrel] [RCut] Distance to USCap [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full_Empty.barrel.best_Chisqrt_DistancetoUpstreamCap_RCut].mean,
     ZShifts[BestIndex_Regions_Full_Empty.barrel.best_Chisqrt_DistancetoUpstreamCap_RCut].stddev, BEST_ChiSqrt_CryoTankRegions_Full_Empty.barrel.Chisqrt_DistancetoUpstreamCap_RCut );
    Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Full_Empty[2],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

    sprintf(Plot_title, "[DSCap]  [RCut] Distance to USCap [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full_Empty.downstream.best_Chisqrt_DistancetoUpstreamCap_RCut].mean,
     ZShifts[BestIndex_Regions_Full_Empty.downstream.best_Chisqrt_DistancetoUpstreamCap_RCut].stddev, BEST_ChiSqrt_CryoTankRegions_Full_Empty.downstream.Chisqrt_DistancetoUpstreamCap_RCut );
    Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Full_Empty[3],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

    sprintf(Plot_title, "[Concave] [RCut] Distance to USCap [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full_Empty.concave.best_Chisqrt_DistancetoUpstreamCap_RCut].mean,
     ZShifts[BestIndex_Regions_Full_Empty.concave.best_Chisqrt_DistancetoUpstreamCap_RCut].stddev, BEST_ChiSqrt_CryoTankRegions_Full_Empty.concave.Chisqrt_DistancetoUpstreamCap_RCut );
    Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Full_Empty[4],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
    //~~~~~~~~~~~~
*/


    sprintf(Plot_title, "Distance to downstream Cap [RCut] Convoluted total [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[Bestindex_ChiSqrt_Full_Empty.best_Chisqrt_DistancetoDownstreamCap_RCut].mean,
     ZShifts[Bestindex_ChiSqrt_Full_Empty.best_Chisqrt_DistancetoDownstreamCap_RCut].stddev, Best_ChiSqrt_Result_Full_Empty.Chisqrt_DistancetoDownstreamCap_RCut );
    Draw2DHist(h_Chisqrt_Distanceto_downstreamcap_Truth_todata_RCut_Full_Empty[0],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
/*

    //~~~~~~~
    sprintf(Plot_title, "[USCap]  [RCut] Distance to DSCap [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full_Empty.upstream.best_Chisqrt_DistancetoDownstreamCap_RCut].mean,
     ZShifts[BestIndex_Regions_Full_Empty.upstream.best_Chisqrt_DistancetoDownstreamCap_RCut].stddev, BEST_ChiSqrt_CryoTankRegions_Full_Empty.upstream.Chisqrt_DistancetoDownstreamCap_RCut );
    Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Full_Empty[1],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

    sprintf(Plot_title, "[barrel] [RCut] Distance to DSCap [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full_Empty.barrel.best_Chisqrt_DistancetoDownstreamCap_RCut].mean,
     ZShifts[BestIndex_Regions_Full_Empty.barrel.best_Chisqrt_DistancetoDownstreamCap_RCut].stddev, BEST_ChiSqrt_CryoTankRegions_Full_Empty.barrel.Chisqrt_DistancetoDownstreamCap_RCut );
    Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Full_Empty[2],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

    sprintf(Plot_title, "[DSCap] [RCut] Distance to DSCap [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full_Empty.downstream.best_Chisqrt_DistancetoDownstreamCap_RCut].mean,
     ZShifts[BestIndex_Regions_Full_Empty.downstream.best_Chisqrt_DistancetoDownstreamCap_RCut].stddev, BEST_ChiSqrt_CryoTankRegions_Full_Empty.downstream.Chisqrt_DistancetoDownstreamCap_RCut );
    Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Full_Empty[3],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

    sprintf(Plot_title, "[Concave] [RCut] Distance to DSCap [Combined F-E] Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", ZShifts[BestIndex_Regions_Full_Empty.concave.best_Chisqrt_DistancetoDownstreamCap_RCut].mean,
     ZShifts[BestIndex_Regions_Full_Empty.concave.best_Chisqrt_DistancetoDownstreamCap_RCut].stddev, BEST_ChiSqrt_CryoTankRegions_Full_Empty.concave.Chisqrt_DistancetoDownstreamCap_RCut );
    Draw2DHist(h_Chisqrt_Distanceto_upstreamcap_Truth_todata_Full_Empty[4],  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
    //~~~~~~~~~~~~
*/


  //myfile.close();





  can -> Print(text_title_pdf3);
  can -> Print(chisqrt_title_pdf3);




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
   char *xaxislabel, char* yaxislabel,  Pot_MapList Pot_MC , Pot_MapList POT_Data , double Ymax){

     bool DoBinwidthNorm=false;
     bool DrawErrors= false;
     bool MakeXaxisLOG=false;
     bool MakeYaxisLOG= false;
     bool drawAllErrorGroups = false;
     char Plot_title[1024];
     std::string playlist_name = GetPlaylist_InitialName(InputMap.playlist);
     double MCtoData_scaler = POT_Data[InputMap.playlist] / Pot_MC[InputMap.playlist];

     std::string HeliumStatus_name = GetPlaylistStatusString(GetPlaylist_HeliumStatus(InputMap.playlist));
     char HeliumStatus_name_char[HeliumStatus_name.length()+1];
     strcpy(HeliumStatus_name_char,HeliumStatus_name.c_str());

     char playlist_name_char[playlist_name.length()+1];
     strcpy( playlist_name_char,playlist_name.c_str());

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

/*

   //////////////////////////////////////////////////////
   // Convolution_Tool
   /////////////////////////////////////////////////////
Convolution_Tool::Convolution_Tool(){
  std::cout<<"initialized Convolution_Tool but did nothing !!! "<<std::endl;
}

Convolution_Tool::~Convolution_Tool()
{
}

void Convolution_Tool::Intialize_dataHistNames(){
  assign_CryoVertex_type();
  assign_TotalRegionHist_dataName();
  assign_RegionsHist_dataName();
}

void Convolution_Tool::assign_CryoVertex_dataHistName(std::string name , Convolution_hist &input_hist){
  input_hist.Data_name = name;
}

void Convolution_Tool::printDATAhistname(Convolution_hist input_hist){
  std::cout<< input_hist.Data_name <<std::endl;
}

void Convolution_Tool::print_Total_DATAhistname(ConvolutionShiftMap input_Map){
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~Total Data Names " << std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
  std::cout << "Vertex_X_TotalRegion                    = ";  printDATAhistname(input_Map.Vertex_X_TotalRegion);
  std::cout << "Vertex_Y_TotalRegion                    = ";  printDATAhistname(input_Map.Vertex_Y_TotalRegion);
  std::cout << "Vertex_R_TotalRegion                    = ";  printDATAhistname(input_Map.Vertex_R_TotalRegion);
  //std::cout << "Vertex_RR_TotalRegion                   = ";  printDATAhistname(input_Map.Vertex_RR_TotalRegion);
  std::cout << "Vertex_Z_TotalRegion                    = ";  printDATAhistname(input_Map.Vertex_Z_TotalRegion);
  std::cout << "Vertex_Z_TotalRegion_RCut               = ";  printDATAhistname(input_Map.Vertex_Z_TotalRegion_RCut);
  std::cout << "NearestWall_TotalRegion                 = ";  printDATAhistname(input_Map.NearestWall_TotalRegion);
  std::cout << "DistanceUpstreamCap_TotalRegion         = ";  printDATAhistname(input_Map.DistanceUpstreamCap_TotalRegion);
  std::cout << "DistanceDownstreamCap_TotalRegion       = ";  printDATAhistname(input_Map.DistanceDownstreamCap_TotalRegion);
  std::cout << "DistanceUpstreamCap_TotalRegion_RCut    = ";  printDATAhistname(input_Map.DistanceUpstreamCap_TotalRegion_RCut);
  std::cout << "DistanceDownstreamCap_TotalRegion_RCut  = ";  printDATAhistname(input_Map.DistanceDownstreamCap_TotalRegion_RCut);
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
}

void Convolution_Tool::print_Total_RECOhistname(ConvolutionShiftMap input_Map){
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~Total RECO Names " << std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
  std::cout << "Vertex_X_TotalRegion                    =   ";  printRECOhistname(input_Map.Vertex_X_TotalRegion);
  std::cout << "Vertex_Y_TotalRegion                    =   ";  printRECOhistname(input_Map.Vertex_Y_TotalRegion);
  std::cout << "Vertex_R_TotalRegion                    =   ";  printRECOhistname(input_Map.Vertex_R_TotalRegion);
  //std::cout << "Vertex_RR_TotalRegion                   =   ";  printRECOhistname(input_Map.Vertex_RR_TotalRegion);
  std::cout << "Vertex_Z_TotalRegion                    =   ";  printRECOhistname(input_Map.Vertex_Z_TotalRegion);
  std::cout << "Vertex_Z_TotalRegion_RCut               =   ";  printRECOhistname(input_Map.Vertex_Z_TotalRegion_RCut);
  std::cout << "NearestWall_TotalRegion                 =   ";  printRECOhistname(input_Map.NearestWall_TotalRegion);
  std::cout << "DistanceUpstreamCap_TotalRegion         =   ";  printRECOhistname(input_Map.DistanceUpstreamCap_TotalRegion);
  std::cout << "DistanceDownstreamCap_TotalRegion       =   ";  printRECOhistname(input_Map.DistanceDownstreamCap_TotalRegion);
  std::cout << "DistanceUpstreamCap_TotalRegion_RCut    =   ";  printRECOhistname(input_Map.DistanceUpstreamCap_TotalRegion_RCut);
  std::cout << "DistanceDownstreamCap_TotalRegion_RCut  =   ";  printRECOhistname(input_Map.DistanceDownstreamCap_TotalRegion_RCut);
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
}

void Convolution_Tool::assign_CryoVertex_RecoHistName(std::string name , Convolution_hist &input_hist){
  input_hist.Reco_name = name;
}

void Convolution_Tool::printRECOhistname(Convolution_hist input_hist){
  std::cout<< input_hist.Reco_name<<std::endl;
}

void Convolution_Tool::assign_CryoVertex_TRUEHistName(std::string name , Convolution_hist &input_hist){
  input_hist.TRUE_name = name;
}

void Convolution_Tool::printTRUEhistname(Convolution_hist input_hist){
  std::cout<< input_hist.TRUE_name<<std::endl;
}


void Convolution_Tool::print_Total_TRUEhistname(ConvolutionShiftMap input_Map){

  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~Total TRUE Names~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
  std::cout << "Vertex_X_TotalRegion                    = ";  printTRUEhistname(input_Map.Vertex_X_TotalRegion);
  std::cout << "Vertex_Y_TotalRegion                    = ";  printTRUEhistname(input_Map.Vertex_Y_TotalRegion);
  std::cout << "Vertex_R_TotalRegion                    = ";  printTRUEhistname(input_Map.Vertex_R_TotalRegion);
  //std::cout << "Vertex_RR_TotalRegion                   = ";  printTRUEhistname(input_Map.Vertex_RR_TotalRegion);
  std::cout << "Vertex_Z_TotalRegion                    = ";  printTRUEhistname(input_Map.Vertex_Z_TotalRegion);
  std::cout << "Vertex_Z_TotalRegion_RCut               = ";  printTRUEhistname(input_Map.Vertex_Z_TotalRegion_RCut);
  std::cout << "NearestWall_TotalRegion                 = ";  printTRUEhistname(input_Map.NearestWall_TotalRegion);
  std::cout << "DistanceUpstreamCap_TotalRegion         = ";  printTRUEhistname(input_Map.DistanceUpstreamCap_TotalRegion);
  std::cout << "DistanceDownstreamCap_TotalRegion       = ";  printTRUEhistname(input_Map.DistanceDownstreamCap_TotalRegion);
  std::cout << "DistanceUpstreamCap_TotalRegion_RCut    = ";  printTRUEhistname(input_Map.DistanceUpstreamCap_TotalRegion_RCut);
  std::cout << "DistanceDownstreamCap_TotalRegion_RCut  = ";  printTRUEhistname(input_Map.DistanceDownstreamCap_TotalRegion_RCut);
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
}

void Convolution_Tool::Print_initNames(ConvolutionShiftMap input_histmap){

  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~Printing Names " << std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
  print_Total_DATAhistname(input_histmap);
  print_Total_RECOhistname(input_histmap);
  print_Total_TRUEhistname(input_histmap);
  print_Total_ConvolutedTRUEhistname(input_histmap);
}


void Convolution_Tool::Print_initNames_Empty(){
  Print_initNames(Empty);
}

void Convolution_Tool::assign_CryoVertex_ConvolutedTRUEHistName(std::string name , Convolution_hist &input_hist){
  input_hist.TRUE_Convoluted_name = name;
}

void Convolution_Tool::printConvolutedTRUEhistname(Convolution_hist input_hist){
  std::cout<< input_hist.TRUE_Convoluted_name<<std::endl;
}

void Convolution_Tool::print_Total_ConvolutedTRUEhistname(ConvolutionShiftMap input_Map){

  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~Total TRUE Convoluted Names~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
  std::cout << "Vertex_X_TotalRegion                    = ";  printConvolutedTRUEhistname(input_Map.Vertex_X_TotalRegion);
  std::cout << "Vertex_Y_TotalRegion                    = ";  printConvolutedTRUEhistname(input_Map.Vertex_Y_TotalRegion);
  std::cout << "Vertex_R_TotalRegion                    = ";  printConvolutedTRUEhistname(input_Map.Vertex_R_TotalRegion);
  //std::cout << "Vertex_RR_TotalRegion                   = ";  printConvolutedTRUEhistname(input_Map.Vertex_RR_TotalRegion);
  std::cout << "Vertex_Z_TotalRegion                    = ";  printConvolutedTRUEhistname(input_Map.Vertex_Z_TotalRegion);
  std::cout << "Vertex_Z_TotalRegion_RCut               = ";  printConvolutedTRUEhistname(input_Map.Vertex_Z_TotalRegion_RCut);
  std::cout << "NearestWall_TotalRegion                 = ";  printConvolutedTRUEhistname(input_Map.NearestWall_TotalRegion);
  std::cout << "DistanceUpstreamCap_TotalRegion         = ";  printConvolutedTRUEhistname(input_Map.DistanceUpstreamCap_TotalRegion);
  std::cout << "DistanceDownstreamCap_TotalRegion       = ";  printConvolutedTRUEhistname(input_Map.DistanceDownstreamCap_TotalRegion);
  std::cout << "DistanceUpstreamCap_TotalRegion_RCut    = ";  printConvolutedTRUEhistname(input_Map.DistanceUpstreamCap_TotalRegion_RCut);
  std::cout << "DistanceDownstreamCap_TotalRegion_RCut  = ";  printConvolutedTRUEhistname(input_Map.DistanceDownstreamCap_TotalRegion_RCut);
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
}



void Convolution_Tool::assign_CryoVertexTotalRegion_ConvolutedTRUEHistName(ConvolutionShiftMap &input_Map){

  assign_CryoVertex_ConvolutedTRUEHistName("h_offset_Vertex_X",      input_Map.Vertex_X_TotalRegion);
  assign_CryoVertex_ConvolutedTRUEHistName("h_offset_Vertex_Y",      input_Map.Vertex_Y_TotalRegion);
  assign_CryoVertex_ConvolutedTRUEHistName("h_offset_Vertex_Z",      input_Map.Vertex_Z_TotalRegion);
  assign_CryoVertex_ConvolutedTRUEHistName("h_offset_Vertex_Z_RCut", input_Map.Vertex_Z_TotalRegion_RCut);
  assign_CryoVertex_ConvolutedTRUEHistName("h_offset_Vertex_R",      input_Map.Vertex_R_TotalRegion);
  assign_CryoVertex_ConvolutedTRUEHistName("h_offset_DistanceEdge",  input_Map.NearestWall_TotalRegion);

  assign_CryoVertex_ConvolutedTRUEHistName("h_Map_DistanceupstreamCap_RCut",   input_Map.DistanceUpstreamCap_TotalRegion_RCut);
  assign_CryoVertex_ConvolutedTRUEHistName("h_Map_DistanceupstreamCap",        input_Map.DistanceUpstreamCap_TotalRegion);
  assign_CryoVertex_ConvolutedTRUEHistName("h_Map_DistancedownstreamCap_RCut", input_Map.DistanceDownstreamCap_TotalRegion_RCut);
  assign_CryoVertex_ConvolutedTRUEHistName("h_Map_DistancedownstreamCap",      input_Map.DistanceDownstreamCap_TotalRegion);

  assign_Convolution_CryoRegions_ConvolutedTRUEName(input_Map.Vertex_X_Regions,                  "h_offset_Vertex_X");
  assign_Convolution_CryoRegions_ConvolutedTRUEName(input_Map.Vertex_Y_Regions,                  "h_offset_Vertex_Y");
  assign_Convolution_CryoRegions_ConvolutedTRUEName(input_Map.Vertex_Z_Regions,                  "h_offset_Vertex_Z");
  assign_Convolution_CryoRegions_ConvolutedTRUEName(input_Map.Vertex_Z_Regions_RCut,             "h_offset_Vertex_Z_RCut");
  assign_Convolution_CryoRegions_ConvolutedTRUEName(input_Map.Vertex_R_Regions,                  "h_offset_Vertex_R");
  assign_Convolution_CryoRegions_ConvolutedTRUEName(input_Map.NearestWall_Regions,               "h_Map_DistanceEdge");
  assign_Convolution_CryoRegions_ConvolutedTRUEName(input_Map.DistanceUpstreamCap_Regions,       "h_Map_DistanceupstreamCap");
  assign_Convolution_CryoRegions_ConvolutedTRUEName(input_Map.DistanceDownstreamCap_Regions,     "h_Map_DistancedownstreamCap");
  assign_Convolution_CryoRegions_ConvolutedTRUEName(input_Map.DistanceUpstreamCap_Regions_RCut,  "h_Map_DistanceupstreamCap_RCut");
  assign_Convolution_CryoRegions_ConvolutedTRUEName(input_Map.DistanceDownstreamCap_Regions_RCut,"h_Map_DistancedownstreamCap_RCut");
}


void Convolution_Tool::assign_CryoVertex_RecoandTRUEHistName(std::string name, std::string AddString, Convolution_hist &input_hist){
  std::string inputname;
  inputname = name + AddString;
  assign_CryoVertex_RecoHistName(inputname , input_hist);
  inputname = name + AddString + "_TRUE";
  assign_CryoVertex_TRUEHistName(inputname , input_hist);
}


void Convolution_Tool::assign_CryoVertex_RecoandTRUEHistName(CryoVertex type, std::string AddString, Convolution_hist &input_hist){
   std::string histname = GetVertexCryoVarHistName(type);
   assign_CryoVertex_RecoandTRUEHistName(histname, AddString, input_hist);
 }


 void Convolution_Tool::assign_CryoVertex_TotalRegion_RecoandTRUEHistName(ConvolutionShiftMap &input_histmap){

   assign_CryoVertex_RecoandTRUEHistName(input_histmap.Vertex_X_TotalRegion.CryoVertex_type,             "",input_histmap.Vertex_X_TotalRegion);
   assign_CryoVertex_RecoandTRUEHistName(input_histmap.Vertex_Y_TotalRegion.CryoVertex_type,             "",input_histmap.Vertex_Y_TotalRegion);
   assign_CryoVertex_RecoandTRUEHistName(input_histmap.Vertex_R_TotalRegion.CryoVertex_type,             "",input_histmap.Vertex_R_TotalRegion);
   //assign_CryoVertex_RecoandTRUEHistName(input_histmap.Vertex_RR_TotalRegion.CryoVertex_type,            "",input_histmap.Vertex_RR_TotalRegion);
   assign_CryoVertex_RecoandTRUEHistName(input_histmap.Vertex_Z_TotalRegion.CryoVertex_type,             "",input_histmap.Vertex_Z_TotalRegion);
   assign_CryoVertex_RecoandTRUEHistName(input_histmap.Vertex_Z_TotalRegion_RCut.CryoVertex_type,        "_RCut",input_histmap.Vertex_Z_TotalRegion_RCut);
   assign_CryoVertex_RecoandTRUEHistName(input_histmap.NearestWall_TotalRegion.CryoVertex_type,          "",input_histmap.NearestWall_TotalRegion);
   assign_CryoVertex_RecoandTRUEHistName(input_histmap.DistanceUpstreamCap_TotalRegion.CryoVertex_type,  "",input_histmap.DistanceUpstreamCap_TotalRegion);
   assign_CryoVertex_RecoandTRUEHistName(input_histmap.DistanceDownstreamCap_TotalRegion.CryoVertex_type,"",input_histmap.DistanceDownstreamCap_TotalRegion);
   assign_CryoVertex_RecoandTRUEHistName(input_histmap.DistanceUpstreamCap_TotalRegion.CryoVertex_type,  "_RCut",input_histmap.DistanceUpstreamCap_TotalRegion_RCut);
   assign_CryoVertex_RecoandTRUEHistName(input_histmap.DistanceDownstreamCap_TotalRegion.CryoVertex_type,"_RCut",input_histmap.DistanceDownstreamCap_TotalRegion_RCut);
 }



void Convolution_Tool::assign_Convolution_CryoRegions_HistName(Convolution_CryoRegions &input_histmap, std::string inputname){
   std::string histname;
   histname = inputname + "_upstreamCap";
   assign_CryoVertex_RecoandTRUEHistName(histname, "", input_histmap.Upstream);
   histname = inputname + "_barrel";
   assign_CryoVertex_RecoandTRUEHistName(histname, "", input_histmap.Barrel);
   histname = inputname + "_downstreamCap";
   assign_CryoVertex_RecoandTRUEHistName(histname, "", input_histmap.Downstream);
   histname = inputname + "_downstreamConcaveCap";
   assign_CryoVertex_RecoandTRUEHistName(histname, "", input_histmap.Concave);
 }


void Convolution_Tool::assign_Convolution_CryoRegions_HistName(ConvolutionShiftMap &inputMap){

  std::string histname;
  histname = GetVertexCryoVarHistName(kX);

  assign_Convolution_CryoRegions_HistName(inputMap.Vertex_X_Regions, histname);
  histname = GetVertexCryoVarHistName(kY);

  assign_Convolution_CryoRegions_HistName(inputMap.Vertex_Y_Regions, histname);
  histname = GetVertexCryoVarHistName(kZ);
  assign_Convolution_CryoRegions_HistName(inputMap.Vertex_Z_Regions, histname);

  histname = GetVertexCryoVarHistName(kZ)+ "_RCut";
  assign_Convolution_CryoRegions_HistName(inputMap.Vertex_Z_Regions_RCut, histname);

  histname = GetVertexCryoVarHistName(kR);
  assign_Convolution_CryoRegions_HistName(inputMap.Vertex_R_Regions, histname);
  //histname = GetVertexCryoVarHistName(kRR);
  //assign_Convolution_CryoRegions_HistName(inputMap.Vertex_RR_Regions,histname);
  histname = GetVertexCryoVarHistName(kdistance_edge);
  assign_Convolution_CryoRegions_HistName(inputMap.NearestWall_Regions,histname);
  histname = GetVertexCryoVarHistName(kdistance_upstreamcap);
  assign_Convolution_CryoRegions_HistName(inputMap.DistanceUpstreamCap_Regions,histname);
  histname = GetVertexCryoVarHistName(kdistance_downstreamcap);
  assign_Convolution_CryoRegions_HistName(inputMap.DistanceDownstreamCap_Regions,histname);
  histname = GetVertexCryoVarHistName(kdistance_upstreamcap) + "_RCut";
  assign_Convolution_CryoRegions_HistName(inputMap.DistanceUpstreamCap_Regions_RCut,histname);
  histname = GetVertexCryoVarHistName(kdistance_downstreamcap)+ "_RCut";
  assign_Convolution_CryoRegions_HistName(inputMap.DistanceDownstreamCap_Regions_RCut,histname);
}


void Convolution_Tool::assign_CryoVertex_dataHistName(CryoVertex type, std::string AddString,  Convolution_hist &input_hist){
  std::string histname = GetVertexCryoVarHist_DATA_Name(type) + AddString;
  //std::cout<<"assign_CryoVertex_dataHistName = "  << histname << std::endl;
  assign_CryoVertex_dataHistName(histname ,  input_hist);
}


void Convolution_Tool::assign_Convolution_CryoRegions_dataHistName(Convolution_CryoRegions &input_histmap, std::string inputname){
  std::string HistName;
  HistName = inputname + "_upstreamCap";
  assign_CryoVertex_dataHistName(HistName , input_histmap.Upstream);
  HistName = inputname + "_barrel";
  assign_CryoVertex_dataHistName(HistName , input_histmap.Barrel);
  HistName = inputname + "_downstreamCap";
  assign_CryoVertex_dataHistName(HistName , input_histmap.Downstream);
  HistName = inputname + "_downstreamConcaveCap";
  assign_CryoVertex_dataHistName(HistName , input_histmap.Concave);
}



void Convolution_Tool::assign_Convolution_CryoRegions_ConvolutedTRUEName(Convolution_CryoRegions &input_histmap, std::string inputname){
  std::string HistName;
  HistName = inputname + "_upstreamCap";
  assign_CryoVertex_ConvolutedTRUEHistName(HistName , input_histmap.Upstream);
  HistName = inputname + "_barrel";
  assign_CryoVertex_ConvolutedTRUEHistName(HistName , input_histmap.Barrel);
  HistName = inputname + "_downstreamCap";
  assign_CryoVertex_ConvolutedTRUEHistName(HistName , input_histmap.Downstream);
  HistName = inputname + "_downstreamConcaveCap";
  assign_CryoVertex_ConvolutedTRUEHistName(HistName , input_histmap.Concave);
}


void Convolution_Tool::assign_CryoVertex_dataHistName(CryoVertex type, std::string AddString, Convolution_CryoRegions &input_histmap){
  std::string histname = GetVertexCryoVarHist_DATA_Name(type) + AddString;
  assign_Convolution_CryoRegions_dataHistName(input_histmap, histname);
}


void Convolution_Tool::assign_Xaxis_title(Convolution_hist &input){
 input.Xaxis_Title = GetVertexCryoVarAxisTitle(input.CryoVertex_type);
}

void Convolution_Tool::assign_Xaxis_CryoVertex_type_Regions(Convolution_CryoRegions &input_region_hist)
{
  assign_Xaxis_title(input_region_hist.Upstream);
  assign_Xaxis_title(input_region_hist.Barrel);
  assign_Xaxis_title(input_region_hist.Downstream);
  assign_Xaxis_title(input_region_hist.Concave);
}

void Convolution_Tool::assign_Xaxis_title(ConvolutionShiftMap &input_histmap){

  assign_Xaxis_title(input_histmap.Vertex_X_TotalRegion);
  assign_Xaxis_title(input_histmap.Vertex_Y_TotalRegion);
  assign_Xaxis_title(input_histmap.Vertex_R_TotalRegion);
  //assign_Xaxis_title(input_histmap.Vertex_RR_TotalRegion);
  assign_Xaxis_title(input_histmap.Vertex_Z_TotalRegion);
  assign_Xaxis_title(input_histmap.Vertex_Z_TotalRegion_RCut);
  assign_Xaxis_title(input_histmap.NearestWall_TotalRegion);
  assign_Xaxis_title(input_histmap.DistanceUpstreamCap_TotalRegion);
  assign_Xaxis_title(input_histmap.DistanceDownstreamCap_TotalRegion);
  assign_Xaxis_title(input_histmap.DistanceUpstreamCap_TotalRegion_RCut);
  assign_Xaxis_title(input_histmap.DistanceDownstreamCap_TotalRegion_RCut);


  assign_Xaxis_CryoVertex_type_Regions(input_histmap.Vertex_X_Regions);
  assign_Xaxis_CryoVertex_type_Regions(input_histmap.Vertex_Y_Regions);
  assign_Xaxis_CryoVertex_type_Regions(input_histmap.Vertex_Z_Regions);
  assign_Xaxis_CryoVertex_type_Regions(input_histmap.Vertex_Z_Regions_RCut);
  assign_Xaxis_CryoVertex_type_Regions(input_histmap.Vertex_R_Regions);
  //assign_Xaxis_CryoVertex_type_Regions(input_histmap.Vertex_RR_Regions);
  assign_Xaxis_CryoVertex_type_Regions(input_histmap.NearestWall_Regions);
  assign_Xaxis_CryoVertex_type_Regions(input_histmap.DistanceUpstreamCap_Regions);
  assign_Xaxis_CryoVertex_type_Regions(input_histmap.DistanceDownstreamCap_Regions);
  assign_Xaxis_CryoVertex_type_Regions(input_histmap.DistanceUpstreamCap_Regions_RCut);
  assign_Xaxis_CryoVertex_type_Regions(input_histmap.DistanceDownstreamCap_Regions_RCut);

}

void Convolution_Tool::assignTotalRegion_dataHistName(ConvolutionShiftMap &input_histmap){

  assign_CryoVertex_dataHistName( input_histmap.Vertex_X_TotalRegion.CryoVertex_type,             "",     input_histmap.Vertex_X_TotalRegion);
  assign_CryoVertex_dataHistName( input_histmap.Vertex_Y_TotalRegion.CryoVertex_type,             "",     input_histmap.Vertex_Y_TotalRegion);
  assign_CryoVertex_dataHistName( input_histmap.Vertex_R_TotalRegion.CryoVertex_type,             "",     input_histmap.Vertex_R_TotalRegion);
//assign_CryoVertex_dataHistName( input_histmap.Vertex_RR_TotalRegion.CryoVertex_type,            "",input_histmap.Vertex_RR_TotalRegion);
  assign_CryoVertex_dataHistName( input_histmap.Vertex_Z_TotalRegion.CryoVertex_type,             "",      input_histmap.Vertex_Z_TotalRegion);
  assign_CryoVertex_dataHistName( input_histmap.Vertex_Z_TotalRegion_RCut.CryoVertex_type,        "_RCut", input_histmap.Vertex_Z_TotalRegion_RCut);
  assign_CryoVertex_dataHistName( input_histmap.NearestWall_TotalRegion.CryoVertex_type,          "",      input_histmap.NearestWall_TotalRegion);
  assign_CryoVertex_dataHistName( input_histmap.DistanceUpstreamCap_TotalRegion.CryoVertex_type,  "",      input_histmap.DistanceUpstreamCap_TotalRegion);
  assign_CryoVertex_dataHistName( input_histmap.DistanceDownstreamCap_TotalRegion.CryoVertex_type, "",     input_histmap.DistanceDownstreamCap_TotalRegion);
  assign_CryoVertex_dataHistName( input_histmap.DistanceUpstreamCap_TotalRegion_RCut.CryoVertex_type,   "_RCut",input_histmap.DistanceUpstreamCap_TotalRegion_RCut);
  assign_CryoVertex_dataHistName( input_histmap.DistanceDownstreamCap_TotalRegion_RCut.CryoVertex_type, "_RCut",input_histmap.DistanceDownstreamCap_TotalRegion_RCut);
}


void Convolution_Tool::assignRegions_dataHistName(ConvolutionShiftMap &input_histmap){

  assign_CryoVertex_dataHistName(kX,                     "",input_histmap.Vertex_X_Regions);
  assign_CryoVertex_dataHistName(kY,                     "",input_histmap.Vertex_Y_Regions);
  assign_CryoVertex_dataHistName(kZ,                     "",input_histmap.Vertex_Z_Regions);
  assign_CryoVertex_dataHistName(kZ,                 "_RCut",input_histmap.Vertex_Z_Regions_RCut);
  assign_CryoVertex_dataHistName(kR,                      "",input_histmap.Vertex_R_Regions);
  //assign_CryoVertex_dataHistName(kRR,                     "",input_histmap.Vertex_RR_Regions);
  assign_CryoVertex_dataHistName(kdistance_edge,          "",input_histmap.NearestWall_Regions);
  assign_CryoVertex_dataHistName(kdistance_upstreamcap,   "",input_histmap.DistanceUpstreamCap_Regions);
  assign_CryoVertex_dataHistName(kdistance_downstreamcap, "",input_histmap.DistanceDownstreamCap_Regions);
  assign_CryoVertex_dataHistName(kdistance_upstreamcap,   "_RCut",input_histmap.DistanceUpstreamCap_Regions_RCut);
  assign_CryoVertex_dataHistName(kdistance_downstreamcap, "_RCut",input_histmap.DistanceDownstreamCap_Regions_RCut);
}

void Convolution_Tool::assign_CryoVertex_type(CryoVertex type , Convolution_hist &input_hist){
  input_hist.CryoVertex_type = type;
}

void Convolution_Tool::assign_CryoVertex_type_Regions(CryoVertex type, Convolution_CryoRegions &input_region_hist){
  assign_CryoVertex_type(type, input_region_hist.Upstream);
  assign_CryoVertex_type(type, input_region_hist.Barrel);
  assign_CryoVertex_type(type, input_region_hist.Downstream);
  assign_CryoVertex_type(type, input_region_hist.Concave);
}

void Convolution_Tool::assign_xAxis(){
std::cout<<"assign_xAxis():full"<<std::endl;
assign_Xaxis_title(Full);
std::cout<<"assign_xAxis():full:Finished"<<std::endl;
std::cout<<"assign_xAxis():Empty"<<std::endl;
assign_Xaxis_title(Empty);
std::cout<<"assign_xAxis():Empty:Finished"<<std::endl;
std::cout<<"assign_xAxis():Full - Empty"<<std::endl;
assign_Xaxis_title(Full_Empty);
std::cout<<"assign_xAxis():Full - Empty:Finished"<<std::endl;


}

void Convolution_Tool::assign_CryoVertex_type(ConvolutionShiftMap &Shift_Map){

  assign_CryoVertex_type(kX, Shift_Map.Vertex_X_TotalRegion);
  assign_CryoVertex_type(kY, Shift_Map.Vertex_Y_TotalRegion);
  assign_CryoVertex_type(kZ, Shift_Map.Vertex_Z_TotalRegion);
  assign_CryoVertex_type(kZ, Shift_Map.Vertex_Z_TotalRegion_RCut);
  assign_CryoVertex_type(kR, Shift_Map.Vertex_R_TotalRegion);
  //assign_CryoVertex_type( kRR, Shift_Map.Vertex_RR_TotalRegion);
  assign_CryoVertex_type(kdistance_edge,          Shift_Map.NearestWall_TotalRegion);
  assign_CryoVertex_type(kdistance_upstreamcap,   Shift_Map.DistanceUpstreamCap_TotalRegion);
  assign_CryoVertex_type(kdistance_downstreamcap, Shift_Map.DistanceDownstreamCap_TotalRegion);

  assign_CryoVertex_type(kdistance_upstreamcap,   Shift_Map.DistanceUpstreamCap_TotalRegion_RCut);
  assign_CryoVertex_type(kdistance_downstreamcap, Shift_Map.DistanceDownstreamCap_TotalRegion_RCut);

  assign_CryoVertex_type_Regions(kX, Shift_Map.Vertex_X_Regions);
  assign_CryoVertex_type_Regions(kY, Shift_Map.Vertex_Y_Regions);
  assign_CryoVertex_type_Regions(kZ, Shift_Map.Vertex_Z_Regions);
  assign_CryoVertex_type_Regions(kZ, Shift_Map.Vertex_Z_Regions_RCut);
  assign_CryoVertex_type_Regions(kR, Shift_Map.Vertex_R_Regions);
  //assign_CryoVertex_type_Regions(kRR ,Shift_Map.Vertex_RR_Regions);
  assign_CryoVertex_type_Regions(kdistance_edge,          Shift_Map.NearestWall_Regions);
  assign_CryoVertex_type_Regions(kdistance_upstreamcap,   Shift_Map.DistanceUpstreamCap_Regions);
  assign_CryoVertex_type_Regions(kdistance_downstreamcap, Shift_Map.DistanceDownstreamCap_Regions);

  assign_CryoVertex_type_Regions(kdistance_upstreamcap,   Shift_Map.DistanceUpstreamCap_Regions_RCut);
  assign_CryoVertex_type_Regions(kdistance_downstreamcap, Shift_Map.DistanceDownstreamCap_Regions_RCut);


}

void Convolution_Tool::assign_CryoVertex_type(){
  assign_CryoVertex_type(Full);
  assign_CryoVertex_type(Empty);
  assign_CryoVertex_type(Full_Empty);
}

void Convolution_Tool::assign_TotalRegionHist_dataName(){
  assignTotalRegion_dataHistName(Full);
  assignTotalRegion_dataHistName(Empty);
  assignTotalRegion_dataHistName(Full_Empty);
}

void Convolution_Tool::assign_RegionsHist_dataName(){
  assignRegions_dataHistName(Full);
  assignRegions_dataHistName(Empty);
  assignRegions_dataHistName(Full_Empty);
}

void Convolution_Tool::assign_RegionsHist_RecoandTRUEName(){

  assign_CryoVertex_TotalRegion_RecoandTRUEHistName(Full);
  assign_CryoVertex_TotalRegion_RecoandTRUEHistName(Empty);
  assign_CryoVertex_TotalRegion_RecoandTRUEHistName(Full_Empty);
  assign_Convolution_CryoRegions_HistName(Full);
  assign_Convolution_CryoRegions_HistName(Empty);
  assign_Convolution_CryoRegions_HistName(Full_Empty);
}

void Convolution_Tool::assign_CryoVertexTotalRegion_ConvolutedTRUEHistName(){

  assign_CryoVertexTotalRegion_ConvolutedTRUEHistName(Full);
  assign_CryoVertexTotalRegion_ConvolutedTRUEHistName(Empty);
  assign_CryoVertexTotalRegion_ConvolutedTRUEHistName(Full_Empty);

}

void Convolution_Tool::init_DataHists_Total_PlaylistCombined(Convolution_hist& input, ME_playlist_TFileMAP TFile_Map_Data, ME_helium_Playlists StartingPlaylist )
{
  std::string var;
  var = input.Data_name;
  Playlist_MnvH1D_Map  Map_data = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_Data, var );
  input.MnvH1D_data =  Combine_Hists_fromMAP(Map_data , StartingPlaylist ,"h_data");

}

void Convolution_Tool::init_DataHists_Regions_PlaylistCombined(Convolution_CryoRegions& input, ME_playlist_TFileMAP TFile_Map_Data, ME_helium_Playlists StartingPlaylist )
{
  init_DataHists_Total_PlaylistCombined(input.Upstream,    TFile_Map_Data,  StartingPlaylist );
  init_DataHists_Total_PlaylistCombined(input.Barrel,      TFile_Map_Data,  StartingPlaylist );
  init_DataHists_Total_PlaylistCombined(input.Downstream,  TFile_Map_Data,  StartingPlaylist );
  init_DataHists_Total_PlaylistCombined(input.Concave,     TFile_Map_Data,  StartingPlaylist );
}


void Convolution_Tool::init_DataHists_Total_PlaylistCombined(ConvolutionShiftMap &input, ME_playlist_TFileMAP TFile_Map_Data, ME_helium_Playlists StartingPlaylist ){
  init_DataHists_Total_PlaylistCombined(input.Vertex_X_TotalRegion,                   TFile_Map_Data, StartingPlaylist);
  init_DataHists_Total_PlaylistCombined(input.Vertex_Y_TotalRegion,                   TFile_Map_Data, StartingPlaylist);
  init_DataHists_Total_PlaylistCombined(input.Vertex_R_TotalRegion,                   TFile_Map_Data, StartingPlaylist);
  //init_DataHists_Total_PlaylistCombined(input.Vertex_RR_TotalRegion,                TFile_Map_Data, StartingPlaylist);
  init_DataHists_Total_PlaylistCombined(input.Vertex_Z_TotalRegion,                   TFile_Map_Data, StartingPlaylist);
  init_DataHists_Total_PlaylistCombined(input.Vertex_Z_TotalRegion_RCut,              TFile_Map_Data, StartingPlaylist);
  init_DataHists_Total_PlaylistCombined(input.NearestWall_TotalRegion,                TFile_Map_Data, StartingPlaylist);
  init_DataHists_Total_PlaylistCombined(input.DistanceUpstreamCap_TotalRegion,        TFile_Map_Data, StartingPlaylist);
  init_DataHists_Total_PlaylistCombined(input.DistanceDownstreamCap_TotalRegion,      TFile_Map_Data, StartingPlaylist);
  init_DataHists_Total_PlaylistCombined(input.DistanceUpstreamCap_TotalRegion_RCut,   TFile_Map_Data, StartingPlaylist);
  init_DataHists_Total_PlaylistCombined(input.DistanceDownstreamCap_TotalRegion_RCut, TFile_Map_Data, StartingPlaylist);
}

void Convolution_Tool::init_DataHists_Regions_PlaylistCombined(ConvolutionShiftMap &input, ME_playlist_TFileMAP TFile_Map_Data, ME_helium_Playlists StartingPlaylist ){

  init_DataHists_Regions_PlaylistCombined(input.Vertex_X_Regions,                    TFile_Map_Data, StartingPlaylist);
  init_DataHists_Regions_PlaylistCombined(input.Vertex_Y_Regions,                    TFile_Map_Data, StartingPlaylist);
  init_DataHists_Regions_PlaylistCombined(input.Vertex_Z_Regions,                    TFile_Map_Data, StartingPlaylist);
  init_DataHists_Regions_PlaylistCombined(input.Vertex_Z_Regions_RCut,               TFile_Map_Data, StartingPlaylist);
  init_DataHists_Regions_PlaylistCombined(input.Vertex_R_Regions,                    TFile_Map_Data, StartingPlaylist);
  //init_DataHists_Regions_PlaylistCombined(input.Vertex_RR_Regions,                 TFile_Map_Data, StartingPlaylist);
  init_DataHists_Regions_PlaylistCombined(input.NearestWall_Regions,                 TFile_Map_Data, StartingPlaylist);
  init_DataHists_Regions_PlaylistCombined(input.DistanceUpstreamCap_Regions,         TFile_Map_Data, StartingPlaylist);
  init_DataHists_Regions_PlaylistCombined(input.DistanceDownstreamCap_Regions,       TFile_Map_Data, StartingPlaylist);
  init_DataHists_Regions_PlaylistCombined(input.DistanceUpstreamCap_Regions_RCut,    TFile_Map_Data, StartingPlaylist);
  init_DataHists_Regions_PlaylistCombined(input.DistanceDownstreamCap_Regions_RCut,  TFile_Map_Data, StartingPlaylist);
}

void Convolution_Tool::init_All_DataHists(){
std::cout<<"~~~~~~~~~~~Initizing Data Hist~~~~~~~~~~``"<< std::endl;
init_DataHists_Total_PlaylistCombined(Full,   TFile_Map_Full_Data,  StartingPlaylist_Full);
init_DataHists_Regions_PlaylistCombined(Full, TFile_Map_Full_Data,  StartingPlaylist_Full);

init_DataHists_Total_PlaylistCombined( Full_Empty,   TFile_Map_Full_Data,  StartingPlaylist_Full);
init_DataHists_Regions_PlaylistCombined(Full_Empty, TFile_Map_Full_Data,  StartingPlaylist_Full);

init_DataHists_Total_PlaylistCombined(  Empty,   TFile_Map_Empty_Data, StartingPlaylist_Empty);
init_DataHists_Regions_PlaylistCombined(Empty, TFile_Map_Empty_Data, StartingPlaylist_Empty);

POTscaleData_Total(Empty,   Empty.POT_Data);
POTscaleData_Regions(Empty, Empty.POT_Data);

Subtract_DataHists_Regions(Full_Empty,  Empty);
Subtract_DataHists_Total(  Full_Empty,    Empty);
std::cout<<"~~~~~~~~Finished Data Hist~~~~~~~~~~~~``"<< std::endl;

}


void Convolution_Tool::init_RecoHists_PlaylistCombinedMC(Convolution_hist &input, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist )
{
  std::string var;
  var = input.Reco_name;
  Playlist_MnvH1D_Map  Map_Reco = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  input.MnvH1D_mc_Reco =  Combine_Hists_fromMAP(Map_Reco , StartingPlaylist ,"Map_Reco");

}


void Convolution_Tool::init_RecoHists_PlaylistCombinedMC(Convolution_CryoRegions& input, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist )
{
  init_RecoHists_PlaylistCombinedMC(input.Upstream   ,TFile_Map_MC, StartingPlaylist);
  init_RecoHists_PlaylistCombinedMC(input.Barrel     ,TFile_Map_MC, StartingPlaylist);
  init_RecoHists_PlaylistCombinedMC(input.Downstream ,TFile_Map_MC, StartingPlaylist);
  init_RecoHists_PlaylistCombinedMC(input.Concave    ,TFile_Map_MC, StartingPlaylist);
}


void Convolution_Tool::init_RecoHists_Total_PlaylistCombinedMC(ConvolutionShiftMap &input, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist )
{
  init_RecoHists_PlaylistCombinedMC(input.Vertex_X_TotalRegion,                   TFile_Map_MC, StartingPlaylist);
  init_RecoHists_PlaylistCombinedMC(input.Vertex_Y_TotalRegion,                   TFile_Map_MC, StartingPlaylist);
  init_RecoHists_PlaylistCombinedMC(input.Vertex_R_TotalRegion,                   TFile_Map_MC, StartingPlaylist);
  //init_RecoHists_PlaylistCombinedMC(input.Vertex_RR_TotalRegion,                  TFile_Map_MC, StartingPlaylist);
  init_RecoHists_PlaylistCombinedMC(input.Vertex_Z_TotalRegion,                   TFile_Map_MC, StartingPlaylist);
  init_RecoHists_PlaylistCombinedMC(input.Vertex_Z_TotalRegion_RCut,              TFile_Map_MC, StartingPlaylist);
  init_RecoHists_PlaylistCombinedMC(input.NearestWall_TotalRegion,                TFile_Map_MC, StartingPlaylist);
  init_RecoHists_PlaylistCombinedMC(input.DistanceUpstreamCap_TotalRegion,        TFile_Map_MC, StartingPlaylist);
  init_RecoHists_PlaylistCombinedMC(input.DistanceDownstreamCap_TotalRegion,      TFile_Map_MC, StartingPlaylist);
  init_RecoHists_PlaylistCombinedMC(input.DistanceUpstreamCap_TotalRegion_RCut,   TFile_Map_MC, StartingPlaylist);
  init_RecoHists_PlaylistCombinedMC(input.DistanceDownstreamCap_TotalRegion_RCut, TFile_Map_MC, StartingPlaylist);
}

void Convolution_Tool::init_RecoHists_Regions_PlaylistCombinedMC(ConvolutionShiftMap &input, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist )
{
  init_RecoHists_PlaylistCombinedMC(input.Vertex_X_Regions,                   TFile_Map_MC, StartingPlaylist);
  init_RecoHists_PlaylistCombinedMC(input.Vertex_Y_Regions,                   TFile_Map_MC, StartingPlaylist);
  init_RecoHists_PlaylistCombinedMC(input.Vertex_Z_Regions,                   TFile_Map_MC, StartingPlaylist);
  init_RecoHists_PlaylistCombinedMC(input.Vertex_Z_Regions_RCut,              TFile_Map_MC, StartingPlaylist);
  init_RecoHists_PlaylistCombinedMC(input.Vertex_R_Regions,                   TFile_Map_MC, StartingPlaylist);
  //init_RecoHists_PlaylistCombinedMC(input.Vertex_RR_Regions,                TFile_Map_MC, StartingPlaylist);
  init_RecoHists_PlaylistCombinedMC(input.NearestWall_Regions,                TFile_Map_MC, StartingPlaylist);
  init_RecoHists_PlaylistCombinedMC(input.DistanceUpstreamCap_Regions,        TFile_Map_MC, StartingPlaylist);
  init_RecoHists_PlaylistCombinedMC(input.DistanceDownstreamCap_Regions,      TFile_Map_MC, StartingPlaylist);
  init_RecoHists_PlaylistCombinedMC(input.DistanceUpstreamCap_Regions_RCut,   TFile_Map_MC, StartingPlaylist);
  init_RecoHists_PlaylistCombinedMC(input.DistanceDownstreamCap_Regions_RCut, TFile_Map_MC, StartingPlaylist);
}


void Convolution_Tool::init_All_RecoHists(){
std::cout<<"~~~~~~~~~~Intializing RECO Hist ~~~~~~~~~~~~"<<std::endl;
  init_RecoHists_Total_PlaylistCombinedMC(Full,   TFile_Map_Full_MC,  StartingPlaylist_Full);
  init_RecoHists_Regions_PlaylistCombinedMC(Full, TFile_Map_Full_MC,  StartingPlaylist_Full);

  POTscale_MCReco_Total(Full,   Full.POT_MC);
  POTscale_MCReco_Regions(Full, Full.POT_MC);

  init_RecoHists_Total_PlaylistCombinedMC(Full_Empty,   TFile_Map_Full_MC,  StartingPlaylist_Full);
  init_RecoHists_Regions_PlaylistCombinedMC(Full_Empty, TFile_Map_Full_MC,  StartingPlaylist_Full);

  POTscale_MCReco_Total(Full_Empty,   Full.POT_MC);
  POTscale_MCReco_Regions(Full_Empty, Full.POT_MC);

  init_RecoHists_Total_PlaylistCombinedMC(Empty,   TFile_Map_Empty_MC, StartingPlaylist_Empty);
  init_RecoHists_Regions_PlaylistCombinedMC(Empty, TFile_Map_Empty_MC, StartingPlaylist_Empty);

  POTscale_MCReco_Total(Empty,   Empty.POT_MC);
  POTscale_MCReco_Regions(Empty, Empty.POT_MC);

  Subtract_RecoHists_Total(Full_Empty, Empty);
  Subtract_RecoHists_Regions(Full_Empty, Empty);

  std::cout<<"~~~~~~~~~~Finished RECO Hist ~~~~~~~~~~~~"<<std::endl;

}


void Convolution_Tool::init_Total_RecoHists(){
  std::cout << "nit_Total_RecoHists()"<<std::endl;
  init_RecoHists_Total_PlaylistCombinedMC(Full,   TFile_Map_Full_MC,  StartingPlaylist_Full);
  std::cout<<"init_RecoHists_Total_PlaylistCombinedMC::Finshied initalize  total"<< std::endl;
  POTscale_MCReco_Total(Full , Full.POT_MC);
  std::cout<<"Finished POT RECO total"<< std::endl;
  init_RecoHists_Total_PlaylistCombinedMC(Full_Empty,   TFile_Map_Full_MC,  StartingPlaylist_Full);
  std::cout<<"int F - E "<< std::endl;
  POTscale_MCReco_Total(Full_Empty , Full.POT_MC);
  std::cout<<"Finished POT RECO total F - E"<< std::endl;
  init_RecoHists_Total_PlaylistCombinedMC(Empty,   TFile_Map_Empty_MC, StartingPlaylist_Empty);
  std::cout<<"Finished init E"<< std::endl;

  POTscale_MCReco_Total(Empty , Empty.POT_MC);
  std::cout<<"Finished POT E"<< std::endl;
  Subtract_RecoHists_Total(Full_Empty, Empty);
  std::cout<<"Finished Subtraction "<< std::endl;
}
void Convolution_Tool::init_Regions_RecoHists(){
  init_RecoHists_Regions_PlaylistCombinedMC(Full, TFile_Map_Full_MC,  StartingPlaylist_Full);
  POTscale_MCReco_Regions(Full , Full.POT_MC);
  init_RecoHists_Regions_PlaylistCombinedMC(Full_Empty, TFile_Map_Full_MC,  StartingPlaylist_Full);
  POTscale_MCReco_Regions(Full_Empty , Full.POT_MC);
  init_RecoHists_Regions_PlaylistCombinedMC(Empty, TFile_Map_Empty_MC, StartingPlaylist_Empty);
  POTscale_MCReco_Regions(Empty , Empty.POT_MC);
  Subtract_RecoHists_Regions(Full_Empty, Empty);
}


void Convolution_Tool::init_TRUEHists_PlaylistCombinedMC(Convolution_hist& input, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist )
{
  std::string var;
  var = input.TRUE_name;
  Playlist_MnvH1D_Map  Map_TRUE = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  input.MnvH1D_mc_TRUTH =  Combine_Hists_fromMAP(Map_TRUE , StartingPlaylist ,"h_TRUE");

}

void Convolution_Tool::init_TRUEHists_PlaylistCombinedMC(Convolution_CryoRegions& input, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist )
{
  init_TRUEHists_PlaylistCombinedMC(input.Upstream ,  TFile_Map_MC, StartingPlaylist);
  init_TRUEHists_PlaylistCombinedMC(input.Barrel ,    TFile_Map_MC, StartingPlaylist);
  init_TRUEHists_PlaylistCombinedMC(input.Downstream ,TFile_Map_MC, StartingPlaylist);
  init_TRUEHists_PlaylistCombinedMC(input.Concave ,   TFile_Map_MC, StartingPlaylist);
}


void Convolution_Tool::init_TRUEHists_Total_PlaylistCombinedMC(ConvolutionShiftMap &input, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist )
{std::cout<<"inside::init_TRUEHists_Total_PlaylistCombinedMC"<<std::endl;
  init_TRUEHists_PlaylistCombinedMC(input.Vertex_X_TotalRegion,                    TFile_Map_MC , StartingPlaylist);
  init_TRUEHists_PlaylistCombinedMC(input.Vertex_Y_TotalRegion,                    TFile_Map_MC , StartingPlaylist);
  init_TRUEHists_PlaylistCombinedMC(input.Vertex_R_TotalRegion,                    TFile_Map_MC , StartingPlaylist);
  //init_TRUEHists_PlaylistCombinedMC(input.Vertex_RR_TotalRegion,                   TFile_Map_MC , StartingPlaylist);
  init_TRUEHists_PlaylistCombinedMC(input.Vertex_Z_TotalRegion,                    TFile_Map_MC , StartingPlaylist);
  init_TRUEHists_PlaylistCombinedMC(input.Vertex_Z_TotalRegion_RCut ,              TFile_Map_MC , StartingPlaylist);
  init_TRUEHists_PlaylistCombinedMC(input.NearestWall_TotalRegion,                 TFile_Map_MC , StartingPlaylist);
  init_TRUEHists_PlaylistCombinedMC(input.DistanceUpstreamCap_TotalRegion ,        TFile_Map_MC , StartingPlaylist);
  init_TRUEHists_PlaylistCombinedMC(input.DistanceDownstreamCap_TotalRegion ,      TFile_Map_MC , StartingPlaylist);
  init_TRUEHists_PlaylistCombinedMC(input.DistanceUpstreamCap_TotalRegion_RCut ,   TFile_Map_MC , StartingPlaylist);
  init_TRUEHists_PlaylistCombinedMC(input.DistanceDownstreamCap_TotalRegion_RCut , TFile_Map_MC , StartingPlaylist);

}

void Convolution_Tool::init_TRUEHists_Regions_PlaylistCombinedMC(ConvolutionShiftMap &input, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist )
{
  init_TRUEHists_PlaylistCombinedMC(input.Vertex_X_Regions,                   TFile_Map_MC, StartingPlaylist);
  init_TRUEHists_PlaylistCombinedMC(input.Vertex_Y_Regions,                   TFile_Map_MC, StartingPlaylist);
  init_TRUEHists_PlaylistCombinedMC(input.Vertex_Z_Regions,                   TFile_Map_MC, StartingPlaylist);
  init_TRUEHists_PlaylistCombinedMC(input.Vertex_Z_Regions_RCut,              TFile_Map_MC, StartingPlaylist);
  init_TRUEHists_PlaylistCombinedMC(input.Vertex_R_Regions,                   TFile_Map_MC, StartingPlaylist);
  //init_TRUEHists_PlaylistCombinedMC(input.Vertex_RR_Regions,                TFile_Map_MC, StartingPlaylist);
  init_TRUEHists_PlaylistCombinedMC(input.NearestWall_Regions,                TFile_Map_MC, StartingPlaylist);
  init_TRUEHists_PlaylistCombinedMC(input.DistanceUpstreamCap_Regions,        TFile_Map_MC, StartingPlaylist);
  init_TRUEHists_PlaylistCombinedMC(input.DistanceDownstreamCap_Regions,      TFile_Map_MC, StartingPlaylist);
  init_TRUEHists_PlaylistCombinedMC(input.DistanceUpstreamCap_Regions_RCut,   TFile_Map_MC, StartingPlaylist);
  init_TRUEHists_PlaylistCombinedMC(input.DistanceDownstreamCap_Regions_RCut, TFile_Map_MC, StartingPlaylist);
}

void Convolution_Tool::init_All_TRUEHists(){
  std::cout<< "init_All_TRUEHists::init FUll  "<< std::endl;
  init_TRUEHists_Total_PlaylistCombinedMC(Full,   TFile_Map_Full_MC,  StartingPlaylist_Full);
  init_TRUEHists_Regions_PlaylistCombinedMC(Full, TFile_Map_Full_MC,  StartingPlaylist_Full);

  std::cout<< "Finished init "<< std::endl;
  std::cout << "Starting to POT Scale: FUll"<<std::endl;
  POTscale_MCTRUTH_Total(Full , Full.POT_MC);
  POTscale_MCTRUTH_Regions(Full , Full.POT_MC);


    std::cout<< "init F - E  "<< std::endl;
  init_TRUEHists_Total_PlaylistCombinedMC(Full_Empty,   TFile_Map_Full_MC,  StartingPlaylist_Full);
  init_TRUEHists_Regions_PlaylistCombinedMC(Full_Empty, TFile_Map_Full_MC,  StartingPlaylist_Full);

    std::cout<< "Scaling F - E  "<< std::endl;
  POTscale_MCTRUTH_Total(Full_Empty , Full.POT_MC);
  POTscale_MCTRUTH_Regions(Full_Empty , Full.POT_MC);

  std::cout<< "init E  "<< std::endl;
  init_TRUEHists_Total_PlaylistCombinedMC(Empty,   TFile_Map_Empty_MC,  StartingPlaylist_Empty);
  init_TRUEHists_Regions_PlaylistCombinedMC(Empty, TFile_Map_Empty_MC,  StartingPlaylist_Empty);

  std::cout << "Starting to POT Scale: Empty"<<std::endl;
  POTscale_MCTRUTH_Total(Empty , Empty.POT_MC);
  POTscale_MCTRUTH_Regions(Empty , Empty.POT_MC);

  std::cout << "Subtraction Total "<<std::endl;
  Subtract_TRUEHists_Total(Full_Empty, Empty);
    std::cout << "Subtraction Regions "<<std::endl;
  Subtract_TRUEHists_Regions(Full_Empty, Empty);
  std::cout<< "~~~~~~~~~~~ Finished  TRUEHists ~~~~~~~~~~~~"<< std::endl;
}

void Convolution_Tool::init_Total_TRUEHists(){

  init_TRUEHists_Total_PlaylistCombinedMC(Full,   TFile_Map_Full_MC,  StartingPlaylist_Full);
  POTscale_MCTRUTH_Total(Full , Full.POT_MC);
  init_TRUEHists_Total_PlaylistCombinedMC(Full_Empty,   TFile_Map_Full_MC,  StartingPlaylist_Full);
  POTscale_MCTRUTH_Total(Full_Empty , Full.POT_MC);
  init_TRUEHists_Total_PlaylistCombinedMC(Empty,   TFile_Map_Empty_MC,  StartingPlaylist_Empty);
  POTscale_MCTRUTH_Total(Empty , Empty.POT_MC);
  Subtract_TRUEHists_Total(Full_Empty, Empty);

}

void Convolution_Tool::init_Regions_TRUEHists(){

  init_TRUEHists_Regions_PlaylistCombinedMC(Full, TFile_Map_Full_MC,  StartingPlaylist_Full);
  POTscale_MCTRUTH_Regions(Full , Full.POT_MC);
  init_TRUEHists_Regions_PlaylistCombinedMC(Full_Empty, TFile_Map_Full_MC,  StartingPlaylist_Full);
  POTscale_MCTRUTH_Regions(Full_Empty , Full.POT_MC);
  init_TRUEHists_Regions_PlaylistCombinedMC(Empty, TFile_Map_Empty_MC,  StartingPlaylist_Empty);
  POTscale_MCTRUTH_Regions(Empty , Empty.POT_MC);
  Subtract_TRUEHists_Regions(Full_Empty, Empty);

}



void Convolution_Tool::init_TRUTHConvolutionHist_MCShifted_PlaylistCombined(Convolution_hist& input, std::string ExtraString, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist, int i, int j, int k )
{
  std::string string_i = std::to_string(i);
  std::string string_j = std::to_string(j);
  std::string string_k = std::to_string(k);
  std::string var;

  var = input.TRUE_Convoluted_name + ExtraString+ "_TRUE" + "_i_j_k_" + string_i + "_" +  string_j + "_" + string_k;
  Playlist_MnvH1D_Map  Convolution_toData_Map_0 =    Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  input.MnvH1D_mc_Convoluted[0] =  Combine_Hists_fromMAP(Convolution_toData_Map_0 , StartingPlaylist ,"Convolution_toData_0");

}

void Convolution_Tool::init_TRUTHConvolution_RegionsHists_MCShifted_PlaylistCombined(Convolution_CryoRegions& input, std::string ExtraString, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist , int i, int j, int k)
{
  init_TRUTHConvolutionHist_MCShifted_PlaylistCombined(input.Upstream,   "", TFile_Map_MC, StartingPlaylist, i,  j,  k);
  init_TRUTHConvolutionHist_MCShifted_PlaylistCombined(input.Barrel,     "", TFile_Map_MC, StartingPlaylist, i,  j,  k);
  init_TRUTHConvolutionHist_MCShifted_PlaylistCombined(input.Downstream, "", TFile_Map_MC, StartingPlaylist, i,  j,  k);
  init_TRUTHConvolutionHist_MCShifted_PlaylistCombined(input.Concave,    "", TFile_Map_MC, StartingPlaylist, i,  j,  k);
}

void Convolution_Tool::init_TRUTHConvolution_RegionsHists_MCShifted_PlaylistCombined(ConvolutionShiftMap &input, std::string ExtraString, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist, int i, int j, int k )
{
init_TRUTHConvolution_RegionsHists_MCShifted_PlaylistCombined(input.Vertex_X_Regions,                  "", TFile_Map_MC, StartingPlaylist, i, j, k);
init_TRUTHConvolution_RegionsHists_MCShifted_PlaylistCombined(input.Vertex_Y_Regions,                  "", TFile_Map_MC, StartingPlaylist, i, j, k);
init_TRUTHConvolution_RegionsHists_MCShifted_PlaylistCombined(input.Vertex_Z_Regions,                  "", TFile_Map_MC, StartingPlaylist, i, j, k);
init_TRUTHConvolution_RegionsHists_MCShifted_PlaylistCombined(input.Vertex_Z_Regions_RCut,             "", TFile_Map_MC, StartingPlaylist, i, j, k);
init_TRUTHConvolution_RegionsHists_MCShifted_PlaylistCombined(input.Vertex_R_Regions,                  "", TFile_Map_MC, StartingPlaylist, i, j, k);
//init_TRUTHConvolution_RegionsHists_MCShifted_PlaylistCombined(input.Vertex_RR_Regions,                 "", TFile_Map_MC, i,j,k, StartingPlaylist);
init_TRUTHConvolution_RegionsHists_MCShifted_PlaylistCombined(input.NearestWall_Regions,               "", TFile_Map_MC, StartingPlaylist, i, j, k);
init_TRUTHConvolution_RegionsHists_MCShifted_PlaylistCombined(input.DistanceUpstreamCap_Regions,       "", TFile_Map_MC, StartingPlaylist, i, j, k);
init_TRUTHConvolution_RegionsHists_MCShifted_PlaylistCombined(input.DistanceDownstreamCap_Regions,     "", TFile_Map_MC, StartingPlaylist, i, j, k);
init_TRUTHConvolution_RegionsHists_MCShifted_PlaylistCombined(input.DistanceUpstreamCap_Regions_RCut,  "", TFile_Map_MC, StartingPlaylist, i, j, k);
init_TRUTHConvolution_RegionsHists_MCShifted_PlaylistCombined(input.DistanceDownstreamCap_Regions_RCut,"", TFile_Map_MC, StartingPlaylist, i, j, k);
}


void Convolution_Tool::init_TRUE_ConvolutionTotalHists_PlaylistCombinedMC(ConvolutionShiftMap &input, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist, int i, int j, int k )
{
init_TRUTHConvolutionHist_MCShifted_PlaylistCombined(input.Vertex_X_TotalRegion,                    "",  TFile_Map_MC, StartingPlaylist, i , j, k );
init_TRUTHConvolutionHist_MCShifted_PlaylistCombined(input.Vertex_Y_TotalRegion,                    "",  TFile_Map_MC, StartingPlaylist, i , j, k );
init_TRUTHConvolutionHist_MCShifted_PlaylistCombined(input.Vertex_R_TotalRegion,                    "",  TFile_Map_MC, StartingPlaylist, i , j, k );
//init_TRUTHConvolutionHist_MCShifted_PlaylistCombined(input.Vertex_RR_TotalRegion,                   "",  TFile_Map_MC, i , j, k, StartingPlaylist );
init_TRUTHConvolutionHist_MCShifted_PlaylistCombined(input.Vertex_Z_TotalRegion,                    "",  TFile_Map_MC, StartingPlaylist, i, j, k);
init_TRUTHConvolutionHist_MCShifted_PlaylistCombined(input.Vertex_Z_TotalRegion_RCut,               "",  TFile_Map_MC, StartingPlaylist, i, j, k);
init_TRUTHConvolutionHist_MCShifted_PlaylistCombined(input.NearestWall_TotalRegion,                 "",  TFile_Map_MC, StartingPlaylist, i, j, k);
init_TRUTHConvolutionHist_MCShifted_PlaylistCombined(input.DistanceUpstreamCap_TotalRegion,         "",  TFile_Map_MC, StartingPlaylist, i, j, k);
init_TRUTHConvolutionHist_MCShifted_PlaylistCombined(input.DistanceDownstreamCap_TotalRegion,       "",  TFile_Map_MC, StartingPlaylist, i, j, k);
init_TRUTHConvolutionHist_MCShifted_PlaylistCombined(input.DistanceUpstreamCap_TotalRegion_RCut,    "",  TFile_Map_MC, StartingPlaylist, i, j, k);
init_TRUTHConvolutionHist_MCShifted_PlaylistCombined(input.DistanceDownstreamCap_TotalRegion_RCut,  "",  TFile_Map_MC, StartingPlaylist, i, j, k);
//std::cout<<"Finished:init_TRUE_ConvolutionTotalHists_PlaylistCombinedMC"<<std::endl;
}

void Convolution_Tool::init_TRUE_Total_and_Regions_Hists_PlaylistCombinedMC(ConvolutionShiftMap &input, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist, int i, int j, int k ){

init_TRUE_ConvolutionTotalHists_PlaylistCombinedMC(input, TFile_Map_MC,  StartingPlaylist,  i ,  j,  k );
init_TRUTHConvolution_RegionsHists_MCShifted_PlaylistCombined(input, "",  TFile_Map_MC , StartingPlaylist,  i ,  j,  k );

}

void  Convolution_Tool::init_TRUE_Convolution_TotalHists_PlaylistCombinedMC(int i, int j, int k){
// Ful
init_TRUE_ConvolutionTotalHists_PlaylistCombinedMC(Full,         TFile_Map_Full_MC,   StartingPlaylist_Full,  i,  j,  k);
//std::cout<<"Finished Full"<<std::endl;
init_TRUE_ConvolutionTotalHists_PlaylistCombinedMC(Full_Empty,   TFile_Map_Full_MC,   StartingPlaylist_Full,  i,  j,  k);
//std::cout<<"Finished Full - Empty"<<std::endl;
init_TRUE_ConvolutionTotalHists_PlaylistCombinedMC(Empty,        TFile_Map_Empty_MC,  StartingPlaylist_Empty, i,  j,  k);
//std::cout<<"Empty"<<std::endl;
//std::cout<<"Finished Intializes now to POT scale"<<std::endl;

POTscale_MC_Convoluted_Total(Full,        Full.POT_MC, 0);
POTscale_MC_Convoluted_Total(Full_Empty , Full.POT_MC, 0);
POTscale_MC_Convoluted_Total(Empty,      Empty.POT_MC, 0);
//std::cout<<"Now to Scale"<<std::endl;

Subtract_TRUEConvolutionHists_Total(Full_Empty , Empty, 0);

}

void  Convolution_Tool::init_TRUE_Convolution_Regions_Hists_PlaylistCombinedMC(int i, int j, int k){
// Full
init_TRUTHConvolution_RegionsHists_MCShifted_PlaylistCombined(Full,  "",       TFile_Map_Full_MC,   StartingPlaylist_Full,  i ,  j,  k );
init_TRUTHConvolution_RegionsHists_MCShifted_PlaylistCombined(Full_Empty,"",   TFile_Map_Full_MC,   StartingPlaylist_Full,  i ,  j,  k );
init_TRUTHConvolution_RegionsHists_MCShifted_PlaylistCombined(Empty, "",       TFile_Map_Empty_MC,  StartingPlaylist_Empty,  i ,  j,  k );

POTscale_MC_Convoluted_Regions(Full,        Full.POT_MC, 0);
POTscale_MC_Convoluted_Regions(Full_Empty , Full.POT_MC, 0);
POTscale_MC_Convoluted_Regions(Empty,      Empty.POT_MC, 0);

Subtract_TRUEConvolutionHists_Regions(Full_Empty , Empty, 0);

}


void Convolution_Tool::init_RECOConvolutionHist_MCShifted_PlaylistCombined(Convolution_hist& input, std::string ExtraString, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist, int i, int j, int k )
{
  std::string string_i = std::to_string(i);
  std::string string_j = std::to_string(j);
  std::string string_k = std::to_string(k);
  std::string var;

  var = input.TRUE_Convoluted_name + ExtraString  + "_i_j_k_" + string_i + "_" +  string_j + "_" + string_k;
  Playlist_MnvH1D_Map  Convolution_toData_Map_1 =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  input.MnvH1D_mc_Convoluted[1] =  Combine_Hists_fromMAP(Convolution_toData_Map_1 , StartingPlaylist ,"Convolution_toData_1");


}


void Convolution_Tool::init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(Convolution_CryoRegions& input, std::string ExtraString, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist , int i, int j, int k)
{
  init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.Upstream,   "", TFile_Map_MC, StartingPlaylist, i,  j,  k);
  init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.Barrel,     "", TFile_Map_MC, StartingPlaylist, i,  j,  k);
  init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.Downstream, "", TFile_Map_MC, StartingPlaylist, i,  j,  k);
  init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.Concave,    "", TFile_Map_MC, StartingPlaylist, i,  j,  k);
}


void Convolution_Tool::init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(Convolution_CryoRegions& input, std::string ExtraString, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist, Index3 upstream, Index3 barrel,Index3 downstream,Index3 concave )
{
  init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.Upstream,   "", TFile_Map_MC, StartingPlaylist, upstream.i,   upstream.j,    upstream.k);
  init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.Barrel,     "", TFile_Map_MC, StartingPlaylist, barrel.i,     barrel.j,      barrel.k);
  init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.Downstream, "", TFile_Map_MC, StartingPlaylist, downstream.i, downstream.j,  downstream.k);
  init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.Concave,    "", TFile_Map_MC, StartingPlaylist, concave.i,    concave.j,     concave.k);
}



void Convolution_Tool::init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(ConvolutionShiftMap &input, std::string ExtraString, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist, int i, int j, int k )
{
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.Vertex_X_Regions,                  "", TFile_Map_MC, StartingPlaylist, i, j, k);
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.Vertex_Y_Regions,                  "", TFile_Map_MC, StartingPlaylist, i, j, k);
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.Vertex_Z_Regions,                  "", TFile_Map_MC, StartingPlaylist, i, j, k);
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.Vertex_Z_Regions_RCut,             "", TFile_Map_MC, StartingPlaylist, i, j, k);
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.Vertex_R_Regions,                  "", TFile_Map_MC, StartingPlaylist, i, j, k);
//init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.Vertex_RR_Regions,                 "", TFile_Map_MC, i,j,k, StartingPlaylist);
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.NearestWall_Regions,               "", TFile_Map_MC, StartingPlaylist, i, j, k);
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.DistanceUpstreamCap_Regions,       "", TFile_Map_MC, StartingPlaylist, i, j, k);
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.DistanceDownstreamCap_Regions,     "", TFile_Map_MC, StartingPlaylist, i, j, k);
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.DistanceUpstreamCap_Regions_RCut,  "", TFile_Map_MC, StartingPlaylist, i, j, k);
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.DistanceDownstreamCap_Regions_RCut,"", TFile_Map_MC, StartingPlaylist, i, j, k);
}


void Convolution_Tool::init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(ConvolutionShiftMap &input, std::string ExtraString, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist, BestIndex_Regions indexMap   )
{
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.Vertex_X_Regions,                  "", TFile_Map_MC, StartingPlaylist, indexMap.upstream.best_Chisqrt_X,     indexMap.barrel.best_Chisqrt_X,     indexMap.downstream.best_Chisqrt_X,     indexMap.concave.best_Chisqrt_X      );
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.Vertex_Y_Regions,                  "", TFile_Map_MC, StartingPlaylist, indexMap.upstream.best_Chisqrt_Y,     indexMap.barrel.best_Chisqrt_Y,     indexMap.downstream.best_Chisqrt_Y,     indexMap.concave.best_Chisqrt_Y      );
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.Vertex_Z_Regions,                  "", TFile_Map_MC, StartingPlaylist, indexMap.upstream.best_Chisqrt_Z,     indexMap.barrel.best_Chisqrt_Z,     indexMap.downstream.best_Chisqrt_Z,     indexMap.concave.best_Chisqrt_Z      );
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.Vertex_Z_Regions_RCut,             "", TFile_Map_MC, StartingPlaylist, indexMap.upstream.best_Chisqrt_Z_RCut,indexMap.barrel.best_Chisqrt_Z_RCut,indexMap.downstream.best_Chisqrt_Z_RCut,indexMap.concave.best_Chisqrt_Z_RCut );
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.Vertex_R_Regions,                  "", TFile_Map_MC, StartingPlaylist, indexMap.upstream.best_Chisqrt_R,     indexMap.barrel.best_Chisqrt_R,     indexMap.downstream.best_Chisqrt_R,     indexMap.concave.best_Chisqrt_R      );
//init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.Vertex_RR_Regions,                 "", TFile_Map_MC, i,j,k, StartingPlaylist);
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.NearestWall_Regions,               "", TFile_Map_MC, StartingPlaylist, indexMap.upstream.best_Chisqrt_NearestWall,                  indexMap.barrel.best_Chisqrt_NearestWall,                 indexMap.downstream.best_Chisqrt_NearestWall,                 indexMap.concave.best_Chisqrt_NearestWall                  );
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.DistanceUpstreamCap_Regions,       "", TFile_Map_MC, StartingPlaylist, indexMap.upstream.best_Chisqrt_DistancetoUpstreamCap,        indexMap.barrel.best_Chisqrt_DistancetoUpstreamCap,       indexMap.downstream.best_Chisqrt_DistancetoUpstreamCap,       indexMap.concave.best_Chisqrt_DistancetoUpstreamCap        );
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.DistanceDownstreamCap_Regions,     "", TFile_Map_MC, StartingPlaylist, indexMap.upstream.best_Chisqrt_DistancetoDownstreamCap,      indexMap.barrel.best_Chisqrt_DistancetoDownstreamCap,     indexMap.downstream.best_Chisqrt_DistancetoDownstreamCap,     indexMap.concave.best_Chisqrt_DistancetoDownstreamCap      );
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.DistanceUpstreamCap_Regions_RCut,  "", TFile_Map_MC, StartingPlaylist, indexMap.upstream.best_Chisqrt_DistancetoUpstreamCap_RCut,   indexMap.barrel.best_Chisqrt_DistancetoUpstreamCap_RCut,  indexMap.downstream.best_Chisqrt_DistancetoUpstreamCap_RCut,  indexMap.concave.best_Chisqrt_DistancetoUpstreamCap_RCut   );
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.DistanceDownstreamCap_Regions_RCut,"", TFile_Map_MC, StartingPlaylist, indexMap.upstream.best_Chisqrt_DistancetoDownstreamCap_RCut, indexMap.barrel.best_Chisqrt_DistancetoDownstreamCap_RCut,indexMap.downstream.best_Chisqrt_DistancetoDownstreamCap_RCut,indexMap.concave.best_Chisqrt_DistancetoDownstreamCap_RCut );
}






void Convolution_Tool::init_RECO_ConvolutionTotalHists_PlaylistCombinedMC(ConvolutionShiftMap &input, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist, int i, int j, int k )
{
init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.Vertex_X_TotalRegion,                    "",  TFile_Map_MC, StartingPlaylist, i , j, k );
init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.Vertex_Y_TotalRegion,                    "",  TFile_Map_MC, StartingPlaylist, i , j, k );
init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.Vertex_R_TotalRegion,                    "",  TFile_Map_MC, StartingPlaylist, i , j, k );
//init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.Vertex_RR_TotalRegion,                   "",  TFile_Map_MC, i , j, k, StartingPlaylist );
init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.Vertex_Z_TotalRegion,                    "",  TFile_Map_MC, StartingPlaylist, i, j, k);
init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.Vertex_Z_TotalRegion_RCut,               "",  TFile_Map_MC, StartingPlaylist, i, j, k);
init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.NearestWall_TotalRegion,                 "",  TFile_Map_MC, StartingPlaylist, i, j, k);
init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.DistanceUpstreamCap_TotalRegion,         "",  TFile_Map_MC, StartingPlaylist, i, j, k);
init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.DistanceDownstreamCap_TotalRegion,       "",  TFile_Map_MC, StartingPlaylist, i, j, k);
init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.DistanceUpstreamCap_TotalRegion_RCut,    "",  TFile_Map_MC, StartingPlaylist, i, j, k);
init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.DistanceDownstreamCap_TotalRegion_RCut,  "",  TFile_Map_MC, StartingPlaylist, i, j, k);
//std::cout<<"Finished:init_TRUE_ConvolutionTotalHists_PlaylistCombinedMC"<<std::endl;
}

void Convolution_Tool::init_BestFitHist_RECO_ConvolutionTotalHists_PlaylistCombinedMC(ConvolutionShiftMap &input, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist, BestIndex bestindex_input  )
{
init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.Vertex_X_TotalRegion,                    "",  TFile_Map_MC, StartingPlaylist, bestindex_input.best_Chisqrt_X.i , bestindex_input.best_Chisqrt_X.j, bestindex_input.best_Chisqrt_X.k);
init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.Vertex_Y_TotalRegion,                    "",  TFile_Map_MC, StartingPlaylist, bestindex_input.best_Chisqrt_Y.i , bestindex_input.best_Chisqrt_Y.j, bestindex_input.best_Chisqrt_Y.k );
init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.Vertex_R_TotalRegion,                    "",  TFile_Map_MC, StartingPlaylist, bestindex_input.best_Chisqrt_R.i , bestindex_input.best_Chisqrt_R.j, bestindex_input.best_Chisqrt_R.k );
//init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.Vertex_RR_TotalRegion,                   "",  TFile_Map_MC, i , j, k, StartingPlaylist );
init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.Vertex_Z_TotalRegion,                    "",  TFile_Map_MC, StartingPlaylist, bestindex_input.best_Chisqrt_Z.i,                            bestindex_input.best_Chisqrt_Z.j,                            bestindex_input.best_Chisqrt_Z.k);
init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.Vertex_Z_TotalRegion_RCut,               "",  TFile_Map_MC, StartingPlaylist, bestindex_input.best_Chisqrt_Z_RCut.i,                       bestindex_input.best_Chisqrt_Z_RCut.j,                       bestindex_input.best_Chisqrt_Z_RCut.k);
init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.NearestWall_TotalRegion,                 "",  TFile_Map_MC, StartingPlaylist, bestindex_input.best_Chisqrt_NearestWall.i,                  bestindex_input.best_Chisqrt_NearestWall.j,                  bestindex_input.best_Chisqrt_NearestWall.k);
init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.DistanceUpstreamCap_TotalRegion,         "",  TFile_Map_MC, StartingPlaylist, bestindex_input.best_Chisqrt_DistancetoUpstreamCap.i,        bestindex_input.best_Chisqrt_DistancetoUpstreamCap.j,        bestindex_input.best_Chisqrt_DistancetoUpstreamCap.k);
init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.DistanceDownstreamCap_TotalRegion,       "",  TFile_Map_MC, StartingPlaylist, bestindex_input.best_Chisqrt_DistancetoDownstreamCap.i,      bestindex_input.best_Chisqrt_DistancetoDownstreamCap.j,      bestindex_input.best_Chisqrt_DistancetoDownstreamCap.k);
init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.DistanceUpstreamCap_TotalRegion_RCut,    "",  TFile_Map_MC, StartingPlaylist, bestindex_input.best_Chisqrt_DistancetoUpstreamCap_RCut.i,   bestindex_input.best_Chisqrt_DistancetoUpstreamCap_RCut.j,   bestindex_input.best_Chisqrt_DistancetoUpstreamCap_RCut.k);
init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.DistanceDownstreamCap_TotalRegion_RCut,  "",  TFile_Map_MC, StartingPlaylist, bestindex_input.best_Chisqrt_DistancetoDownstreamCap_RCut.i, bestindex_input.best_Chisqrt_DistancetoDownstreamCap_RCut.j, bestindex_input.best_Chisqrt_DistancetoDownstreamCap_RCut.k);
//std::cout<<"Finished:init_TRUE_ConvolutionTotalHists_PlaylistCombinedMC"<<std::endl;
}







void Convolution_Tool::init_RECO_Total_and_Regions_Hists_PlaylistCombinedMC(ConvolutionShiftMap &input, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist, int i, int j, int k ){

init_RECO_ConvolutionTotalHists_PlaylistCombinedMC(input, TFile_Map_MC,  StartingPlaylist,  i ,  j,  k );
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input, "",  TFile_Map_MC , StartingPlaylist,  i ,  j,  k );


}

void  Convolution_Tool::init_RECO_Convolution_TotalHists_PlaylistCombinedMC(int i, int j, int k){
// Ful
init_RECO_ConvolutionTotalHists_PlaylistCombinedMC(Full,         TFile_Map_Full_MC,   StartingPlaylist_Full,  i,  j,  k);
//std::cout<<"Finished Full"<<std::endl;
init_RECO_ConvolutionTotalHists_PlaylistCombinedMC(Full_Empty,   TFile_Map_Full_MC,   StartingPlaylist_Full,  i,  j,  k);
//std::cout<<"Finished Full - Empty"<<std::endl;
init_RECO_ConvolutionTotalHists_PlaylistCombinedMC(Empty,        TFile_Map_Empty_MC,  StartingPlaylist_Empty, i,  j,  k);
//std::cout<<"Empty"<<std::endl;
//std::cout<<"Finished Intializes now to POT scale"<<std::endl;

POTscale_MC_Convoluted_Total(Full,        Full.POT_MC, 1);
POTscale_MC_Convoluted_Total(Full_Empty , Full.POT_MC, 1);
POTscale_MC_Convoluted_Total(Empty,      Empty.POT_MC, 1);
//std::cout<<"Now to Scale"<<std::endl;

Subtract_TRUEConvolutionHists_Total(Full_Empty , Empty, 1);

}


void  Convolution_Tool::init_RECO_Convolution_Regions_Hists_PlaylistCombinedMC(int i, int j, int k){
// Full
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(Full,  "",       TFile_Map_Full_MC,   StartingPlaylist_Full,  i ,  j,  k );
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(Full_Empty,"",   TFile_Map_Full_MC,   StartingPlaylist_Full,  i ,  j,  k );
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(Empty, "",       TFile_Map_Empty_MC,  StartingPlaylist_Empty, i ,  j,  k );

POTscale_MC_Convoluted_Regions(Full,        Full.POT_MC,  1);
POTscale_MC_Convoluted_Regions(Full_Empty , Full.POT_MC,  1);
POTscale_MC_Convoluted_Regions(Empty,       Empty.POT_MC, 1);

Subtract_TRUEConvolutionHists_Regions(Full_Empty , Empty, 1);

}


void  Convolution_Tool::init_RECO_Convolution_TotalHists_PlaylistCombinedMC(BestIndex bestindex_Full, BestIndex bestindex_Empty){
// Full

init_BestFitHist_RECO_ConvolutionTotalHists_PlaylistCombinedMC(Full,       TFile_Map_Full_MC,   StartingPlaylist_Full, bestindex_Full  );
init_BestFitHist_RECO_ConvolutionTotalHists_PlaylistCombinedMC(Full_Empty, TFile_Map_Full_MC,   StartingPlaylist_Full, bestindex_Full  );
init_BestFitHist_RECO_ConvolutionTotalHists_PlaylistCombinedMC(Empty,      TFile_Map_Empty_MC,  StartingPlaylist_Empty, bestindex_Empty  );


POTscale_MC_Convoluted_Total(Full,        Full.POT_MC, 1);
POTscale_MC_Convoluted_Total(Full_Empty , Full.POT_MC, 1);
POTscale_MC_Convoluted_Total(Empty,      Empty.POT_MC, 1);

Subtract_TRUEConvolutionHists_Total(Full_Empty , Empty, 1);
}

void  Convolution_Tool::init_RECO_Convolution_RegonsHists_PlaylistCombinedMC(BestIndex_Regions bestindex_Full, BestIndex_Regions bestindex_Empty){
// Full

init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(Full,      "", TFile_Map_Full_MC,   StartingPlaylist_Full, bestindex_Full  );
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(Full_Empty,"", TFile_Map_Full_MC,   StartingPlaylist_Full, bestindex_Full  );
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(Empty,     "", TFile_Map_Empty_MC,  StartingPlaylist_Empty, bestindex_Empty  );

POTscale_MC_Convoluted_Regions(Full,        Full.POT_MC, 1);
POTscale_MC_Convoluted_Regions(Full_Empty , Full.POT_MC, 1);
POTscale_MC_Convoluted_Regions(Empty,      Empty.POT_MC, 1);

Subtract_TRUEConvolutionHists_Regions(Full_Empty , Empty, 1);


}

void  Convolution_Tool::init_ALL_RECOConvolution_Regions_Hists_PlaylistCombinedMC(int i, int j, int k){
//.std::cout<<"Inside:init_ALL_Convolution_Regions_Hists_PlaylistCombinedMC"<<std::endl;
init_RECO_Convolution_TotalHists_PlaylistCombinedMC( i, j, k);
//.std::cout<<"Finished: init_TRUE_Convolution_TotalHists_PlaylistCombinedMC"<<std::endl;
init_RECO_Convolution_Regions_Hists_PlaylistCombinedMC( i, j, k);
}







void  Convolution_Tool::init_ALL_Convolution_Regions_Hists_PlaylistCombinedMC(int i, int j, int k){
//std::cout<<"Inside:init_ALL_Convolution_Regions_Hists_PlaylistCombinedMC"<<std::endl;
init_TRUE_Convolution_TotalHists_PlaylistCombinedMC( i, j, k);
//std::cout<<"Finished: init_TRUE_Convolution_TotalHists_PlaylistCombinedMC"<<std::endl;
init_TRUE_Convolution_Regions_Hists_PlaylistCombinedMC( i, j, k);
}


void  Convolution_Tool::init_ZeroShift_TRUE_Convolution_Regions_Hists_PlaylistCombinedMC(){

init_TRUE_Convolution_Regions_Hists_PlaylistCombinedMC(ZeroShiftindex.i , ZeroShiftindex.j, ZeroShiftindex.k);
init_TRUE_Convolution_TotalHists_PlaylistCombinedMC(ZeroShiftindex.i , ZeroShiftindex.j, ZeroShiftindex.k);

}

void  Convolution_Tool::init_ZeroShift_RECO_Convolution_Regions_Hists_PlaylistCombinedMC(){

init_RECO_Convolution_Regions_Hists_PlaylistCombinedMC(ZeroShiftindex.i , ZeroShiftindex.j, ZeroShiftindex.k);
init_RECO_Convolution_TotalHists_PlaylistCombinedMC(ZeroShiftindex.i , ZeroShiftindex.j, ZeroShiftindex.k);

}



void Convolution_Tool::init_TRUTHConvolution_MCZEROShifted_PlaylistCombined_Histograms(ConvolutionShiftMap &input, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist ){

  init_TRUE_ConvolutionTotalHists_PlaylistCombinedMC(input, TFile_Map_MC,  StartingPlaylist, ZeroShiftindex.i , ZeroShiftindex.j, ZeroShiftindex.k );

}




void Convolution_Tool::FillDataPOT(double inputPOT, ConvolutionShiftMap &inputMap){
  inputMap.POT_Data = inputPOT;
}
void Convolution_Tool::FillMCPOT(double inputPOT, ConvolutionShiftMap &inputMap){
  inputMap.POT_MC = inputPOT;
}


void Convolution_Tool::ConstuctandFill_Complete_NuMEPlaylist_POT(std::vector<ME_helium_Playlists> FullPlaylist , std::vector<ME_helium_Playlists> EmptyPlaylist){

  double Total_MCFull_POT  = 0.0;
  double Total_MCEmpty_POT = 0.0;
  double Total_DataFull_POT  = 0.0;
  double Total_DataEmpty_POT  = 0.0;

  for(auto cat:FullPlaylist){
    Total_MCFull_POT+=POTMap_Full_MC[cat];
    Total_DataFull_POT+=POTMap_Full_Data[cat];
  }

  for(auto cat:EmptyPlaylist){
    Total_MCEmpty_POT+=POTMap_Empty_MC[cat];
    Total_DataEmpty_POT+=POTMap_Empty_Data[cat];
  }

  double FullMC_toFullData = Total_DataFull_POT / Total_MCFull_POT;
  double EmptyMC_toFullData = Total_DataFull_POT / Total_MCEmpty_POT;
  double EmptyData_toFullData = Total_DataFull_POT / Total_DataEmpty_POT;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<" FullMC_toFullData = "<< FullMC_toFullData<<std::endl;
std::cout<<" EmptyMC_toFullData = "<< EmptyMC_toFullData<<std::endl;
std::cout<<" EmptyData_toFullData = "<< EmptyData_toFullData<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;


  FillDataPOT(EmptyData_toFullData, Empty);
  FillMCPOT(EmptyMC_toFullData, Empty);
  FillMCPOT(FullMC_toFullData, Full);
}

void Convolution_Tool::init_NuMEPlaylist_POT(){
  ConstuctandFill_Complete_NuMEPlaylist_POT(FullPlaylist_vector , EmptyPlaylist_vector);
}


void Convolution_Tool::POTscaleData(Convolution_hist &input , double POTscaler){
input.MnvH1D_data->Scale(POTscaler);
}
void Convolution_Tool::POTscaleMC_Reco(Convolution_hist &input , double POTscaler){
input.MnvH1D_mc_Reco->Scale(POTscaler);
}
void Convolution_Tool::POTscaleMC_TRUTH(Convolution_hist &input , double POTscaler){
input.MnvH1D_mc_TRUTH->Scale(POTscaler);
}
void Convolution_Tool::POTscaleMC_ConvoluteTRUTH(Convolution_hist &input , double POTscaler, int ind){
input.MnvH1D_mc_Convoluted[ind]->Scale(POTscaler);
}

void Convolution_Tool::POTscaleData_Regions(Convolution_CryoRegions &input , double POTscaler){
POTscaleData(input.Upstream,   POTscaler);
POTscaleData(input.Barrel,     POTscaler);
POTscaleData(input.Downstream, POTscaler);
POTscaleData(input.Concave,    POTscaler);
}

void Convolution_Tool::POTscale_MCReco_Regions(Convolution_CryoRegions &input , double POTscaler){
POTscaleMC_Reco(input.Upstream,  POTscaler);
POTscaleMC_Reco(input.Barrel,    POTscaler);
POTscaleMC_Reco(input.Downstream,POTscaler);
POTscaleMC_Reco(input.Concave,   POTscaler);
}

void Convolution_Tool::POTscale_MCTRUTH_Regions(Convolution_CryoRegions &input , double POTscaler){
POTscaleMC_TRUTH(input.Upstream,   POTscaler);
POTscaleMC_TRUTH(input.Barrel,     POTscaler);
POTscaleMC_TRUTH(input.Downstream, POTscaler);
POTscaleMC_TRUTH(input.Concave,    POTscaler);
}
void Convolution_Tool::POTscaleMC_ConvoluteTRUTH_Regions(Convolution_CryoRegions &input , double POTscaler, int ind){
POTscaleMC_ConvoluteTRUTH(input.Upstream,   POTscaler, ind);
POTscaleMC_ConvoluteTRUTH(input.Barrel,     POTscaler, ind);
POTscaleMC_ConvoluteTRUTH(input.Downstream, POTscaler, ind);
POTscaleMC_ConvoluteTRUTH(input.Concave,    POTscaler, ind);
}
void Convolution_Tool::POTscaleData_Total(ConvolutionShiftMap &input , double POTscaler){

  POTscaleData(input.Vertex_X_TotalRegion,                  POTscaler);
  POTscaleData(input.Vertex_Y_TotalRegion,                  POTscaler);
  POTscaleData(input.Vertex_R_TotalRegion,                  POTscaler);
  //POTscaleData(input.Vertex_RR_TotalRegion,                 POTscaler);
  POTscaleData(input.Vertex_Z_TotalRegion,                  POTscaler);
  POTscaleData(input.Vertex_Z_TotalRegion_RCut,             POTscaler);
  POTscaleData(input.NearestWall_TotalRegion,               POTscaler);
  POTscaleData(input.DistanceUpstreamCap_TotalRegion,       POTscaler);
  POTscaleData(input.DistanceDownstreamCap_TotalRegion,     POTscaler);
  POTscaleData(input.DistanceUpstreamCap_TotalRegion_RCut,  POTscaler);
  POTscaleData(input.DistanceDownstreamCap_TotalRegion_RCut,POTscaler);
}

void Convolution_Tool::POTscaleData_Regions(ConvolutionShiftMap &input , double POTscaler){

  POTscaleData_Regions(input.Vertex_X_Regions,                  POTscaler);
  POTscaleData_Regions(input.Vertex_Y_Regions,                  POTscaler);
  POTscaleData_Regions(input.Vertex_R_Regions,                  POTscaler);
  //POTscaleData_Regions(input.Vertex_RR_TotalRegion,                 POTscaler);
  POTscaleData_Regions(input.Vertex_Z_Regions,                  POTscaler);
  POTscaleData_Regions(input.Vertex_Z_Regions_RCut,             POTscaler);
  POTscaleData_Regions(input.NearestWall_Regions,               POTscaler);
  POTscaleData_Regions(input.DistanceUpstreamCap_Regions,       POTscaler);
  POTscaleData_Regions(input.DistanceDownstreamCap_Regions,     POTscaler);
  POTscaleData_Regions(input.DistanceUpstreamCap_Regions_RCut,  POTscaler);
  POTscaleData_Regions(input.DistanceDownstreamCap_Regions_RCut,POTscaler);
}


void Convolution_Tool::POTscale_MCReco_Total(ConvolutionShiftMap &input , double POTscaler){

  POTscaleMC_Reco(input.Vertex_X_TotalRegion,                  POTscaler);
  POTscaleMC_Reco(input.Vertex_Y_TotalRegion,                  POTscaler);
  POTscaleMC_Reco(input.Vertex_R_TotalRegion,                  POTscaler);
  //POTscaleMC_Reco(input.Vertex_RR_TotalRegion,                 POTscaler);
  POTscaleMC_Reco(input.Vertex_Z_TotalRegion,                  POTscaler);
  POTscaleMC_Reco(input.Vertex_Z_TotalRegion_RCut,             POTscaler);
  POTscaleMC_Reco(input.NearestWall_TotalRegion,               POTscaler);
  POTscaleMC_Reco(input.DistanceUpstreamCap_TotalRegion,       POTscaler);
  POTscaleMC_Reco(input.DistanceDownstreamCap_TotalRegion,     POTscaler);
  POTscaleMC_Reco(input.DistanceUpstreamCap_TotalRegion_RCut,  POTscaler);
  POTscaleMC_Reco(input.DistanceDownstreamCap_TotalRegion_RCut,POTscaler);
}

void Convolution_Tool::POTscale_MCReco_Regions(ConvolutionShiftMap &input , double POTscaler){

  POTscale_MCReco_Regions(input.Vertex_X_Regions,                  POTscaler);
  POTscale_MCReco_Regions(input.Vertex_Y_Regions,                  POTscaler);
  POTscale_MCReco_Regions(input.Vertex_R_Regions,                  POTscaler);
  //POTscale_MCReco_Regions(input.Vertex_RR_Regions,                 POTscaler);
  POTscale_MCReco_Regions(input.Vertex_Z_Regions,                  POTscaler);
  POTscale_MCReco_Regions(input.Vertex_Z_Regions_RCut,             POTscaler);
  POTscale_MCReco_Regions(input.NearestWall_Regions,               POTscaler);
  POTscale_MCReco_Regions(input.DistanceUpstreamCap_Regions,       POTscaler);
  POTscale_MCReco_Regions(input.DistanceDownstreamCap_Regions,     POTscaler);
  POTscale_MCReco_Regions(input.DistanceUpstreamCap_Regions_RCut,  POTscaler);
  POTscale_MCReco_Regions(input.DistanceDownstreamCap_Regions_RCut,POTscaler);
}

void Convolution_Tool::POTscale_MCTRUTH_Total(ConvolutionShiftMap &input , double POTscaler){

  POTscaleMC_TRUTH(input.Vertex_X_TotalRegion,                  POTscaler);
  POTscaleMC_TRUTH(input.Vertex_Y_TotalRegion,                  POTscaler);
  POTscaleMC_TRUTH(input.Vertex_R_TotalRegion,                  POTscaler);
  //POTscaleMC_TRUTH(input.Vertex_RR_TotalRegion,                 POTscaler);
  POTscaleMC_TRUTH(input.Vertex_Z_TotalRegion,                  POTscaler);
  POTscaleMC_TRUTH(input.Vertex_Z_TotalRegion_RCut,             POTscaler);
  POTscaleMC_TRUTH(input.NearestWall_TotalRegion,               POTscaler);
  POTscaleMC_TRUTH(input.DistanceUpstreamCap_TotalRegion,       POTscaler);
  POTscaleMC_TRUTH(input.DistanceDownstreamCap_TotalRegion,     POTscaler);
  POTscaleMC_TRUTH(input.DistanceUpstreamCap_TotalRegion_RCut,  POTscaler);
  POTscaleMC_TRUTH(input.DistanceDownstreamCap_TotalRegion_RCut,POTscaler);
}
void Convolution_Tool::POTscale_MCTRUTH_Regions(ConvolutionShiftMap &input , double POTscaler){

  POTscale_MCTRUTH_Regions(input.Vertex_X_Regions,                  POTscaler);
  POTscale_MCTRUTH_Regions(input.Vertex_Y_Regions,                  POTscaler);
  POTscale_MCTRUTH_Regions(input.Vertex_R_Regions,                  POTscaler);
  //POTscale_MCTRUTH_Regions(input.Vertex_RR_Region,                 POTscaler);
  POTscale_MCTRUTH_Regions(input.Vertex_Z_Regions,                  POTscaler);
  POTscale_MCTRUTH_Regions(input.Vertex_Z_Regions_RCut,             POTscaler);
  POTscale_MCTRUTH_Regions(input.NearestWall_Regions,               POTscaler);
  POTscale_MCTRUTH_Regions(input.DistanceUpstreamCap_Regions,       POTscaler);
  POTscale_MCTRUTH_Regions(input.DistanceDownstreamCap_Regions,     POTscaler);
  POTscale_MCTRUTH_Regions(input.DistanceUpstreamCap_Regions_RCut,  POTscaler);
  POTscale_MCTRUTH_Regions(input.DistanceDownstreamCap_Regions_RCut,POTscaler);
}

void Convolution_Tool::POTscale_MC_Convoluted_Total(ConvolutionShiftMap &input , double POTscaler, int ind){

  POTscaleMC_ConvoluteTRUTH(input.Vertex_X_TotalRegion,                  POTscaler, ind);
  POTscaleMC_ConvoluteTRUTH(input.Vertex_Y_TotalRegion,                  POTscaler, ind);
  POTscaleMC_ConvoluteTRUTH(input.Vertex_R_TotalRegion,                  POTscaler, ind);
  //POTscaleMC_ConvoluteTRUTH(input.Vertex_RR_TotalRegion,                 POTscaler, ind);
  POTscaleMC_ConvoluteTRUTH(input.Vertex_Z_TotalRegion,                  POTscaler, ind);
  POTscaleMC_ConvoluteTRUTH(input.Vertex_Z_TotalRegion_RCut,             POTscaler, ind);
  POTscaleMC_ConvoluteTRUTH(input.NearestWall_TotalRegion,               POTscaler, ind);
  POTscaleMC_ConvoluteTRUTH(input.DistanceUpstreamCap_TotalRegion,       POTscaler, ind);
  POTscaleMC_ConvoluteTRUTH(input.DistanceDownstreamCap_TotalRegion,     POTscaler, ind);
  POTscaleMC_ConvoluteTRUTH(input.DistanceUpstreamCap_TotalRegion_RCut,  POTscaler, ind);
  POTscaleMC_ConvoluteTRUTH(input.DistanceDownstreamCap_TotalRegion_RCut,POTscaler, ind);
}

void Convolution_Tool::POTscale_MC_Convoluted_Regions(ConvolutionShiftMap &input , double POTscaler, int ind){

  POTscaleMC_ConvoluteTRUTH_Regions(input.Vertex_X_Regions,                  POTscaler, ind);
  POTscaleMC_ConvoluteTRUTH_Regions(input.Vertex_Y_Regions,                  POTscaler, ind);
  POTscaleMC_ConvoluteTRUTH_Regions(input.Vertex_R_Regions,                  POTscaler, ind);
  //POTscaleMC_ConvoluteTRUTH_Regions(input.Vertex_RR_Regions,                 POTscaler, ind);
  POTscaleMC_ConvoluteTRUTH_Regions(input.Vertex_Z_Regions,                  POTscaler, ind);
  POTscaleMC_ConvoluteTRUTH_Regions(input.Vertex_Z_Regions_RCut,             POTscaler, ind);
  POTscaleMC_ConvoluteTRUTH_Regions(input.NearestWall_Regions,               POTscaler, ind);
  POTscaleMC_ConvoluteTRUTH_Regions(input.DistanceUpstreamCap_Regions,       POTscaler, ind);
  POTscaleMC_ConvoluteTRUTH_Regions(input.DistanceDownstreamCap_Regions,     POTscaler, ind);
  POTscaleMC_ConvoluteTRUTH_Regions(input.DistanceUpstreamCap_Regions_RCut,  POTscaler, ind);
  POTscaleMC_ConvoluteTRUTH_Regions(input.DistanceDownstreamCap_Regions_RCut,POTscaler, ind);
}



void Convolution_Tool::Subtract_DataHists(Convolution_hist &Subtract_from , Convolution_hist &input ){
  Subtract_from.MnvH1D_data->Add(input.MnvH1D_data, -1.0);
}

void Convolution_Tool::Subtract_CryoRegions_DataHists(Convolution_CryoRegions &Subtract_from , Convolution_CryoRegions &input ){
Subtract_DataHists(Subtract_from.Upstream,    input.Upstream );
Subtract_DataHists(Subtract_from.Barrel,      input.Barrel );
Subtract_DataHists(Subtract_from.Downstream,  input.Downstream );
Subtract_DataHists(Subtract_from.Concave,     input.Concave );
}

void Convolution_Tool::PrintPOT(){
  std::cout<<"~~~~~~~~~~~~~~~~PRINTING POT~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<" POT MC FUll = " << Full.POT_MC<<std::endl;
  std::cout<<" POT Data FUll = " << Full.POT_Data<<std::endl;

  std::cout<<" POT MC Empty = " << Empty.POT_MC<<std::endl;
  std::cout<<" POT Data Empty = " << Empty.POT_Data<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~ Finished ~~~~~~~~~~~~~~~~~~~"<<std::endl;

}



void Convolution_Tool::Subtract_DataHists_Total(ConvolutionShiftMap &Subtract_from , ConvolutionShiftMap &input)
{

Subtract_DataHists( Subtract_from.Vertex_X_TotalRegion,                   input.Vertex_X_TotalRegion);
Subtract_DataHists( Subtract_from.Vertex_Y_TotalRegion,                   input.Vertex_Y_TotalRegion);
Subtract_DataHists( Subtract_from.Vertex_R_TotalRegion,                   input.Vertex_R_TotalRegion);
//Subtract_DataHists( Subtract_from.Vertex_RR_TotalRegion,                  input.Vertex_RR_TotalRegion);
Subtract_DataHists( Subtract_from.Vertex_Z_TotalRegion,                   input.Vertex_Z_TotalRegion);
Subtract_DataHists( Subtract_from.Vertex_Z_TotalRegion_RCut,              input.Vertex_Z_TotalRegion_RCut);
Subtract_DataHists( Subtract_from.NearestWall_TotalRegion,                input.NearestWall_TotalRegion);
Subtract_DataHists( Subtract_from.DistanceUpstreamCap_TotalRegion,        input.DistanceUpstreamCap_TotalRegion);
Subtract_DataHists( Subtract_from.DistanceDownstreamCap_TotalRegion,      input.DistanceDownstreamCap_TotalRegion);
Subtract_DataHists( Subtract_from.DistanceUpstreamCap_TotalRegion_RCut,   input.DistanceUpstreamCap_TotalRegion_RCut);
Subtract_DataHists( Subtract_from.DistanceDownstreamCap_TotalRegion_RCut, input.DistanceDownstreamCap_TotalRegion_RCut);
}

void Convolution_Tool::Subtract_DataHists_Regions(ConvolutionShiftMap &Subtract_from , ConvolutionShiftMap &input)
{
  Subtract_CryoRegions_DataHists(Subtract_from.Vertex_X_Regions,                   input.Vertex_X_Regions);
  Subtract_CryoRegions_DataHists(Subtract_from.Vertex_Y_Regions,                   input.Vertex_Y_Regions);
  Subtract_CryoRegions_DataHists(Subtract_from.Vertex_Z_Regions,                   input.Vertex_Z_Regions);
  Subtract_CryoRegions_DataHists(Subtract_from.Vertex_Z_Regions_RCut,              input.Vertex_Z_Regions_RCut);
  Subtract_CryoRegions_DataHists(Subtract_from.Vertex_R_Regions,                   input.Vertex_R_Regions);
  //Subtract_CryoRegions_DataHists(Subtract_from.Vertex_RR_Regions,                  input.Vertex_RR_Regions);
  Subtract_CryoRegions_DataHists(Subtract_from.NearestWall_Regions,                input.NearestWall_Regions);
  Subtract_CryoRegions_DataHists(Subtract_from.DistanceUpstreamCap_Regions,        input.DistanceUpstreamCap_Regions);
  Subtract_CryoRegions_DataHists(Subtract_from.DistanceDownstreamCap_Regions,      input.DistanceDownstreamCap_Regions);
  Subtract_CryoRegions_DataHists(Subtract_from.DistanceUpstreamCap_Regions_RCut,   input.DistanceUpstreamCap_Regions_RCut);
  Subtract_CryoRegions_DataHists(Subtract_from.DistanceDownstreamCap_Regions_RCut, input.DistanceDownstreamCap_Regions_RCut);
}

void Convolution_Tool::Subtract_RecoHists(Convolution_hist &Subtract_from , Convolution_hist &input ){
  Subtract_from.MnvH1D_mc_Reco->Add(input.MnvH1D_mc_Reco, -1.0);
}

void Convolution_Tool::Subtract_CryoRegions_RecoHists(Convolution_CryoRegions &Subtract_from , Convolution_CryoRegions &input ){
  Subtract_RecoHists(Subtract_from.Upstream,    input.Upstream );
  Subtract_RecoHists(Subtract_from.Barrel,      input.Barrel );
  Subtract_RecoHists(Subtract_from.Downstream,  input.Downstream );
  Subtract_RecoHists(Subtract_from.Concave,     input.Concave );
}

void Convolution_Tool::Subtract_RecoHists_Total(ConvolutionShiftMap &Subtract_from , ConvolutionShiftMap &input)
{
  Subtract_RecoHists(Subtract_from.Vertex_X_TotalRegion,                   input.Vertex_X_TotalRegion);
  Subtract_RecoHists(Subtract_from.Vertex_Y_TotalRegion,                   input.Vertex_Y_TotalRegion);
  Subtract_RecoHists(Subtract_from.Vertex_R_TotalRegion,                   input.Vertex_R_TotalRegion);
  //Subtract_RecoHists(Subtract_from.Vertex_RR_TotalRegion,                   input.Vertex_RR_TotalRegion);
  Subtract_RecoHists(Subtract_from.Vertex_Z_TotalRegion,                   input.Vertex_Z_TotalRegion);
  Subtract_RecoHists(Subtract_from.Vertex_Z_TotalRegion_RCut,              input.Vertex_Z_TotalRegion_RCut);
  Subtract_RecoHists(Subtract_from.NearestWall_TotalRegion,                input.NearestWall_TotalRegion);
  Subtract_RecoHists(Subtract_from.DistanceUpstreamCap_TotalRegion,        input.DistanceUpstreamCap_TotalRegion);
  Subtract_RecoHists(Subtract_from.DistanceDownstreamCap_TotalRegion,      input.DistanceDownstreamCap_TotalRegion);
  Subtract_RecoHists(Subtract_from.DistanceUpstreamCap_TotalRegion_RCut,   input.DistanceUpstreamCap_TotalRegion_RCut);
  Subtract_RecoHists(Subtract_from.DistanceDownstreamCap_TotalRegion_RCut, input.DistanceDownstreamCap_TotalRegion_RCut);
}

void Convolution_Tool::Subtract_RecoHists_Regions(ConvolutionShiftMap &Subtract_from , ConvolutionShiftMap &input)
{
  Subtract_CryoRegions_RecoHists(Subtract_from.Vertex_X_Regions,                   input.Vertex_X_Regions);
  Subtract_CryoRegions_RecoHists(Subtract_from.Vertex_Y_Regions,                   input.Vertex_Y_Regions);
  Subtract_CryoRegions_RecoHists(Subtract_from.Vertex_Z_Regions,                   input.Vertex_Z_Regions);
  Subtract_CryoRegions_RecoHists(Subtract_from.Vertex_Z_Regions_RCut,              input.Vertex_Z_Regions_RCut);
  Subtract_CryoRegions_RecoHists(Subtract_from.Vertex_R_Regions,                   input.Vertex_R_Regions);
  //Subtract_CryoRegions_RecoHists(Subtract_from.Vertex_RR_Regions,                  input.Vertex_RR_Regions);
  Subtract_CryoRegions_RecoHists(Subtract_from.NearestWall_Regions,                input.NearestWall_Regions);
  Subtract_CryoRegions_RecoHists(Subtract_from.DistanceUpstreamCap_Regions,        input.DistanceUpstreamCap_Regions);
  Subtract_CryoRegions_RecoHists(Subtract_from.DistanceDownstreamCap_Regions,      input.DistanceDownstreamCap_Regions);
  Subtract_CryoRegions_RecoHists(Subtract_from.DistanceUpstreamCap_Regions_RCut,   input.DistanceUpstreamCap_Regions_RCut);
  Subtract_CryoRegions_RecoHists(Subtract_from.DistanceDownstreamCap_Regions_RCut, input.DistanceDownstreamCap_Regions_RCut);
}



void Convolution_Tool::Subtract_TrueHists(Convolution_hist &Subtract_from , Convolution_hist &input ){
  Subtract_from.MnvH1D_mc_TRUTH->Add(input.MnvH1D_mc_TRUTH, -1.0);
}
void Convolution_Tool::Subtract_TrueConvoluedHists(Convolution_hist &Subtract_from , Convolution_hist &input, int ind ){
  Subtract_from.MnvH1D_mc_Convoluted[ind]->Add(input.MnvH1D_mc_Convoluted[ind], -1.0);
}

void Convolution_Tool::Subtract_CryoRegions_TRUEHists(Convolution_CryoRegions &Subtract_from , Convolution_CryoRegions &input ){
  Subtract_TrueHists(Subtract_from.Upstream,    input.Upstream );
  Subtract_TrueHists(Subtract_from.Barrel,      input.Barrel );
  Subtract_TrueHists(Subtract_from.Downstream,  input.Downstream );
  Subtract_TrueHists(Subtract_from.Concave,     input.Concave );
}

void Convolution_Tool::Subtract_CryoRegions_TRUEConvolutionHists(Convolution_CryoRegions &Subtract_from , Convolution_CryoRegions &input, int ind ){
  Subtract_TrueConvoluedHists(Subtract_from.Upstream,    input.Upstream,   ind);
  Subtract_TrueConvoluedHists(Subtract_from.Barrel,      input.Barrel,     ind);
  Subtract_TrueConvoluedHists(Subtract_from.Downstream,  input.Downstream, ind);
  Subtract_TrueConvoluedHists(Subtract_from.Concave,     input.Concave,    ind);
}

void Convolution_Tool::Subtract_TRUEConvolutionHists_Total(ConvolutionShiftMap &Subtract_from , ConvolutionShiftMap &input, int ind)
{
  Subtract_TrueConvoluedHists(Subtract_from.Vertex_X_TotalRegion,                   input.Vertex_X_TotalRegion,                   ind);
  Subtract_TrueConvoluedHists(Subtract_from.Vertex_Y_TotalRegion,                   input.Vertex_Y_TotalRegion,                   ind);
  Subtract_TrueConvoluedHists(Subtract_from.Vertex_R_TotalRegion,                   input.Vertex_R_TotalRegion,                   ind);
  //Subtract_TrueConvoluedHists(Subtract_from.Vertex_RR_TotalRegion,                  input.Vertex_RR_TotalRegion,                  ind);
  Subtract_TrueConvoluedHists(Subtract_from.Vertex_Z_TotalRegion,                   input.Vertex_Z_TotalRegion,                   ind);
  Subtract_TrueConvoluedHists(Subtract_from.Vertex_Z_TotalRegion_RCut,              input.Vertex_Z_TotalRegion_RCut,              ind);
  Subtract_TrueConvoluedHists(Subtract_from.NearestWall_TotalRegion,                input.NearestWall_TotalRegion,                ind);
  Subtract_TrueConvoluedHists(Subtract_from.DistanceUpstreamCap_TotalRegion,        input.DistanceUpstreamCap_TotalRegion,        ind);
  Subtract_TrueConvoluedHists(Subtract_from.DistanceDownstreamCap_TotalRegion,      input.DistanceDownstreamCap_TotalRegion,      ind);
  Subtract_TrueConvoluedHists(Subtract_from.DistanceUpstreamCap_TotalRegion_RCut,   input.DistanceUpstreamCap_TotalRegion_RCut,   ind);
  Subtract_TrueConvoluedHists(Subtract_from.DistanceDownstreamCap_TotalRegion_RCut, input.DistanceDownstreamCap_TotalRegion_RCut, ind);
}

void Convolution_Tool::Subtract_TRUEConvolutionHists_Regions(ConvolutionShiftMap &Subtract_from , ConvolutionShiftMap &input, int ind)
{
  Subtract_CryoRegions_TRUEConvolutionHists(Subtract_from.Vertex_X_Regions,                   input.Vertex_X_Regions, ind);
  Subtract_CryoRegions_TRUEConvolutionHists(Subtract_from.Vertex_Y_Regions,                   input.Vertex_Y_Regions, ind);
  Subtract_CryoRegions_TRUEConvolutionHists(Subtract_from.Vertex_Z_Regions,                   input.Vertex_Z_Regions, ind);
  Subtract_CryoRegions_TRUEConvolutionHists(Subtract_from.Vertex_Z_Regions_RCut,              input.Vertex_Z_Regions_RCut, ind);
  Subtract_CryoRegions_TRUEConvolutionHists(Subtract_from.Vertex_R_Regions,                   input.Vertex_R_Regions, ind);
  //Subtract_CryoRegions_TRUEConvolutionHists(Subtract_from.Vertex_RR_Regions,                  input.Vertex_RR_Regions, ind);
  Subtract_CryoRegions_TRUEConvolutionHists(Subtract_from.NearestWall_Regions,                input.NearestWall_Regions, ind);
  Subtract_CryoRegions_TRUEConvolutionHists(Subtract_from.DistanceUpstreamCap_Regions,        input.DistanceUpstreamCap_Regions, ind);
  Subtract_CryoRegions_TRUEConvolutionHists(Subtract_from.DistanceDownstreamCap_Regions,      input.DistanceDownstreamCap_Regions, ind);
  Subtract_CryoRegions_TRUEConvolutionHists(Subtract_from.DistanceUpstreamCap_Regions_RCut,   input.DistanceUpstreamCap_Regions_RCut, ind);
  Subtract_CryoRegions_TRUEConvolutionHists(Subtract_from.DistanceDownstreamCap_Regions_RCut, input.DistanceDownstreamCap_Regions_RCut, ind);
}
void Convolution_Tool::Subtract_TRUEHists_Total(ConvolutionShiftMap &Subtract_from , ConvolutionShiftMap &input)
{
  Subtract_TrueHists(Subtract_from.Vertex_X_TotalRegion,                   input.Vertex_X_TotalRegion);
  Subtract_TrueHists(Subtract_from.Vertex_Y_TotalRegion,                   input.Vertex_Y_TotalRegion);
  Subtract_TrueHists(Subtract_from.Vertex_R_TotalRegion,                   input.Vertex_R_TotalRegion);
  //Subtract_TrueHists(Subtract_from.Vertex_RR_TotalRegion,                  input.Vertex_RR_TotalRegion);
  Subtract_TrueHists(Subtract_from.Vertex_Z_TotalRegion,                   input.Vertex_Z_TotalRegion);
  Subtract_TrueHists(Subtract_from.Vertex_Z_TotalRegion_RCut,              input.Vertex_Z_TotalRegion_RCut);
  Subtract_TrueHists(Subtract_from.NearestWall_TotalRegion,                input.NearestWall_TotalRegion);
  Subtract_TrueHists(Subtract_from.DistanceUpstreamCap_TotalRegion,        input.DistanceUpstreamCap_TotalRegion);
  Subtract_TrueHists(Subtract_from.DistanceDownstreamCap_TotalRegion,      input.DistanceDownstreamCap_TotalRegion);
  Subtract_TrueHists(Subtract_from.DistanceUpstreamCap_TotalRegion_RCut,   input.DistanceUpstreamCap_TotalRegion_RCut);
  Subtract_TrueHists(Subtract_from.DistanceDownstreamCap_TotalRegion_RCut, input.DistanceDownstreamCap_TotalRegion_RCut);
}
void Convolution_Tool::Subtract_TRUEHists_Regions(ConvolutionShiftMap &Subtract_from , ConvolutionShiftMap &input)
{
  Subtract_CryoRegions_TRUEHists(Subtract_from.Vertex_X_Regions,                   input.Vertex_X_Regions);
  Subtract_CryoRegions_TRUEHists(Subtract_from.Vertex_Y_Regions,                   input.Vertex_Y_Regions);
  Subtract_CryoRegions_TRUEHists(Subtract_from.Vertex_Z_Regions,                   input.Vertex_Z_Regions);
  Subtract_CryoRegions_TRUEHists(Subtract_from.Vertex_Z_Regions_RCut,              input.Vertex_Z_Regions_RCut);
  Subtract_CryoRegions_TRUEHists(Subtract_from.Vertex_R_Regions,                   input.Vertex_R_Regions);
  //Subtract_CryoRegions_TRUEHists(Subtract_from.Vertex_RR_Regions,                  input.Vertex_RR_Regions);
  Subtract_CryoRegions_TRUEHists(Subtract_from.NearestWall_Regions,                input.NearestWall_Regions);
  Subtract_CryoRegions_TRUEHists(Subtract_from.DistanceUpstreamCap_Regions,        input.DistanceUpstreamCap_Regions);
  Subtract_CryoRegions_TRUEHists(Subtract_from.DistanceDownstreamCap_Regions,      input.DistanceDownstreamCap_Regions);
  Subtract_CryoRegions_TRUEHists(Subtract_from.DistanceUpstreamCap_Regions_RCut,   input.DistanceUpstreamCap_Regions_RCut);
  Subtract_CryoRegions_TRUEHists(Subtract_from.DistanceDownstreamCap_Regions_RCut, input.DistanceDownstreamCap_Regions_RCut);
}







void Convolution_Tool::input_pdfLabel(std::string input_name){
globalpdf_label = input_name;
}

void Convolution_Tool::Plot_Eventdistrubution
(MnvH1D *hist_Data,
  MnvH1D *hist_RecoMC,
  MnvH1D *hist_TRUTH_Convolution, MnvH1D *hist_TRUTH,
  std::string Playlist_name,
  std::string histotitle,
  std::string playlist_status,
  std::string xaxislabel,
  std::string yaxislabel,
  double Ymax, double Convoluted_Mean,
  double Convoluted_stddev,
  double &ChiSqrt_Truth_toReco,
  double &ChiSqrt_Truth_toData,
  double &ChiSqrt_Reco_toData)
  {

     char playlist_status_char[playlist_status.length()+1];
     strcpy(playlist_status_char,playlist_status.c_str());

     char Playlist_name_char[Playlist_name.length()+1];
     strcpy(Playlist_name_char,Playlist_name.c_str());

     char histotitle_char[histotitle.length()+1];
     strcpy(histotitle_char,histotitle.c_str());

     char xaxislabel_char[xaxislabel.length()+1];
     strcpy(xaxislabel_char,xaxislabel.c_str());

     char yaxislabel_char[yaxislabel.length()+1];
     strcpy(yaxislabel_char,yaxislabel.c_str());

     Draw_Data_RECO_TRUTH_Hist_withConvolution_fromPointers(
      hist_Data,
      hist_RecoMC,
      hist_TRUTH_Convolution,
      hist_TRUTH,
      Playlist_name_char,
      globalpdf_label,
      histotitle_char,
      playlist_status_char,
      xaxislabel_char,
      yaxislabel_char,
      global_DoBinwidthNorm,
      global_MakeXaxisLOG,
      Ymax,
      Convoluted_Mean,
      Convoluted_stddev,
      ChiSqrt_Truth_toReco,
      ChiSqrt_Truth_toData,
      ChiSqrt_Reco_toData );

}


void Convolution_Tool::Plot_Eventdistrubution_RECOCol(
  MnvH1D *hist_Data,
  MnvH1D *hist_RECOMC,
  MnvH1D *hist_RECO_Convolution,
  MnvH1D *hist_TRUTH,
  std::string Playlist_name,
  std::string histotitle,
  std::string playlist_status,
  std::string xaxislabel,
  std::string yaxislabel,
  double Ymax,
  double Convoluted_Mean,
  double Convoluted_stddev,
  double &ChiSqrt_ConvolRECOtoRECO,
  double &ChiSqrt_ConvolRECOtoData,
  double &ChiSqrt_RECO_toData)
  {

     char playlist_status_char[playlist_status.length()+1];
     strcpy(playlist_status_char,playlist_status.c_str());

     char Playlist_name_char[Playlist_name.length()+1];
     strcpy(Playlist_name_char,Playlist_name.c_str());

     char histotitle_char[histotitle.length()+1];
     strcpy(histotitle_char,histotitle.c_str());

     char xaxislabel_char[xaxislabel.length()+1];
     strcpy(xaxislabel_char,xaxislabel.c_str());

     char yaxislabel_char[yaxislabel.length()+1];
     strcpy(yaxislabel_char,yaxislabel.c_str());


     Draw_Data_RECO_TRUTH_Hist_withConvolutionRECO_fromPointers(
       hist_Data,
       hist_RECOMC,
       hist_RECO_Convolution,
       hist_TRUTH,
       global_MakeAreaNorm_todata,
       Playlist_name_char,
       globalpdf_label,
       histotitle_char,
       playlist_status_char,
       xaxislabel_char,
       yaxislabel_char,
       global_DoBinwidthNorm,
       global_MakeXaxisLOG,
       Ymax,
       Convoluted_Mean,
       Convoluted_stddev,
       ChiSqrt_ConvolRECOtoRECO,
       ChiSqrt_ConvolRECOtoData,
        ChiSqrt_RECO_toData);


}

void Convolution_Tool::Plot_Eventdistrubution_RECOCol(
  MnvH1D *hist_Data,
  MnvH1D *hist_RECOMC,
  MnvH1D *hist_RECO_Convolution,
  MnvH1D *hist_TRUTH,
  std::string Playlist_name,
  std::string histotitle,
  std::string playlist_status,
  std::string xaxislabel,
  std::string yaxislabel,
  double Ymax,
  double Convoluted_MeanF,
  double Convoluted_stddevF,
  double Convoluted_MeanE,
  double Convoluted_stddevE,
  double &ChiSqrt_ConvolRECOtoRECO,
  double &ChiSqrt_ConvolRECOtoData,
  double &ChiSqrt_RECO_toData)
  {

     char playlist_status_char[playlist_status.length()+1];
     strcpy(playlist_status_char,playlist_status.c_str());

     char Playlist_name_char[Playlist_name.length()+1];
     strcpy(Playlist_name_char,Playlist_name.c_str());

     char histotitle_char[histotitle.length()+1];
     strcpy(histotitle_char,histotitle.c_str());

     char xaxislabel_char[xaxislabel.length()+1];
     strcpy(xaxislabel_char,xaxislabel.c_str());

     char yaxislabel_char[yaxislabel.length()+1];
     strcpy(yaxislabel_char,yaxislabel.c_str());


     Draw_Data_RECO_TRUTH_Hist_withConvolutionRECO_fromPointers(
       hist_Data,
       hist_RECOMC,
       hist_RECO_Convolution,
       hist_TRUTH,
       global_MakeAreaNorm_todata,
       Playlist_name_char,
       globalpdf_label,
       histotitle_char,
       playlist_status_char,
       xaxislabel_char,
       yaxislabel_char,
       global_DoBinwidthNorm,
       global_MakeXaxisLOG,
       Ymax,
       Convoluted_MeanF,
       Convoluted_stddevF,
       Convoluted_MeanE,
       Convoluted_stddevE,
       ChiSqrt_ConvolRECOtoRECO,
       ChiSqrt_ConvolRECOtoData,
        ChiSqrt_RECO_toData);


}


void Convolution_Tool::Plot_Eventdistrubution_RECOCol(
  Convolution_hist &histsInput,
  std::string Playlist_name,
  std::string histotitle,
  std::string playlist_status,
  double Ymax, double Convoluted_Mean,
  double Convoluted_stddev,
  double &ChiSqrt_ConvolRECOtoRECO,
  double &ChiSqrt_ConvolRECOtoData,
  double &ChiSqrt_RECO_toData  ){


    Plot_Eventdistrubution_RECOCol(histsInput.MnvH1D_data,
      histsInput.MnvH1D_mc_Reco,
      histsInput.MnvH1D_mc_Convoluted[1],
      histsInput.MnvH1D_mc_TRUTH,
      Playlist_name,
      histotitle,
      playlist_status,
      histsInput.Xaxis_Title,
      "mm",  Ymax,  Convoluted_Mean,  Convoluted_stddev,
      ChiSqrt_ConvolRECOtoRECO,
      ChiSqrt_ConvolRECOtoData,
      ChiSqrt_RECO_toData);

    }

    void Convolution_Tool::Plot_Eventdistrubution_RECOCol(
      Convolution_hist &histsInput,
      std::string Playlist_name,
      std::string histotitle,
      std::string playlist_status,
      double Ymax,
      double Convoluted_MeanF,
      double Convoluted_stddevF,
      double Convoluted_MeanE,
      double Convoluted_stddevE,
      double &ChiSqrt_ConvolRECOtoRECO,
      double &ChiSqrt_ConvolRECOtoData,
      double &ChiSqrt_RECO_toData  ){


        Plot_Eventdistrubution_RECOCol(histsInput.MnvH1D_data,
          histsInput.MnvH1D_mc_Reco,
          histsInput.MnvH1D_mc_Convoluted[1],
          histsInput.MnvH1D_mc_TRUTH,
          Playlist_name,
          histotitle,
          playlist_status,
          histsInput.Xaxis_Title,
          "mm",  Ymax,  Convoluted_MeanF,  Convoluted_stddevF,
          Convoluted_MeanE,  Convoluted_stddevE,
          ChiSqrt_ConvolRECOtoRECO,
          ChiSqrt_ConvolRECOtoData,
          ChiSqrt_RECO_toData);

        }


void Convolution_Tool::Plot_Eventdistrubution(
  Convolution_hist &histsInput,
  std::string Playlist_name,
  std::string histotitle,
  std::string playlist_status,
  double Ymax, double Convoluted_Mean,
  double Convoluted_stddev, int ind,
   double &ChiSqrt_Truth_toReco,
   double &ChiSqrt_Truth_toData,
   double &ChiSqrt_Reco_toData)
  {

    Plot_Eventdistrubution(histsInput.MnvH1D_data,
      histsInput.MnvH1D_mc_Reco,
      histsInput.MnvH1D_mc_Convoluted[ind],
      histsInput.MnvH1D_mc_TRUTH,
      Playlist_name,
      histotitle,
      playlist_status,
      histsInput.Xaxis_Title,
      "mm",  Ymax,  Convoluted_Mean,  Convoluted_stddev,
      ChiSqrt_Truth_toReco,
      ChiSqrt_Truth_toData,
      ChiSqrt_Reco_toData);

}

void Convolution_Tool::Plot_Eventdistrubution_Regions(Convolution_CryoRegions &histsInput,
   std::string Playlist_name,  std::string histotitle, std::string playlist_status,
  double Ymax, double Convoluted_Mean, double Convoluted_stddev, int ind)
  {
    double chisqrt1 = 10;
    double chisqrt2 = 10;
    double chisqrt3 = 10;


std::string Title = "[USCap]" + histotitle;

Plot_Eventdistrubution(histsInput.Upstream.MnvH1D_data,
      histsInput.Upstream.MnvH1D_mc_Reco,
      histsInput.Upstream.MnvH1D_mc_Convoluted[ind],
      histsInput.Upstream.MnvH1D_mc_TRUTH,
      Playlist_name,
      Title,
      playlist_status,
      histsInput.Upstream.Xaxis_Title,
      "mm",  Ymax,  Convoluted_Mean,  Convoluted_stddev,
      chisqrt1,
      chisqrt2,
      chisqrt3);

 Title = "[barrel]" + histotitle;

Plot_Eventdistrubution(histsInput.Barrel.MnvH1D_data,
  histsInput.Barrel.MnvH1D_mc_Reco,
  histsInput.Barrel.MnvH1D_mc_Convoluted[ind],
  histsInput.Barrel.MnvH1D_mc_TRUTH,
  Playlist_name,
  Title,
  playlist_status,
  histsInput.Barrel.Xaxis_Title,
  "mm",  Ymax,  Convoluted_Mean,  Convoluted_stddev,
  chisqrt1,
  chisqrt2,
  chisqrt3);

 Title = "[DSCap]" + histotitle;

Plot_Eventdistrubution(histsInput.Downstream.MnvH1D_data,
  histsInput.Downstream.MnvH1D_mc_Reco,
  histsInput.Downstream.MnvH1D_mc_Convoluted[ind],
  histsInput.Downstream.MnvH1D_mc_TRUTH,
  Playlist_name,
  Title,
  playlist_status,
  histsInput.Downstream.Xaxis_Title,
  "mm",  Ymax,  Convoluted_Mean,  Convoluted_stddev,
  chisqrt1,
  chisqrt2,
  chisqrt3);

 Title = "[DSConcave]" + histotitle;

Plot_Eventdistrubution(histsInput.Concave.MnvH1D_data,
  histsInput.Concave.MnvH1D_mc_Reco,
  histsInput.Concave.MnvH1D_mc_Convoluted[ind],
  histsInput.Concave.MnvH1D_mc_TRUTH,
  Playlist_name,
  Title,
  playlist_status,
  histsInput.Concave.Xaxis_Title,
  "mm",  Ymax,  Convoluted_Mean,  Convoluted_stddev,
  chisqrt1,
  chisqrt2,
  chisqrt3);



}

void Convolution_Tool::Plot_ConvolRECO_Eventdistrubution_Regions(
  Convolution_CryoRegions &histsInput,
   std::string Playlist_name,
    std::string histotitle,
    std::string playlist_status,
  double Ymax, double Convoluted_Mean, double Convoluted_stddev)
  {
    double chisqrt1 = 10;
    double chisqrt2 = 10;
    double chisqrt3 = 10;

std::string Title = "[USCap]" + histotitle;

Plot_Eventdistrubution_RECOCol(histsInput.Upstream.MnvH1D_data,
      histsInput.Upstream.MnvH1D_mc_Reco,
      histsInput.Upstream.MnvH1D_mc_Convoluted[1],
      histsInput.Upstream.MnvH1D_mc_TRUTH,
      Playlist_name,
      Title,
      playlist_status,
      histsInput.Upstream.Xaxis_Title,
      "mm",  Ymax,  Convoluted_Mean,  Convoluted_stddev,
      chisqrt1,
      chisqrt2,
      chisqrt3);

 Title = "[barrel]" + histotitle;

Plot_Eventdistrubution_RECOCol(histsInput.Barrel.MnvH1D_data,
  histsInput.Barrel.MnvH1D_mc_Reco,
  histsInput.Barrel.MnvH1D_mc_Convoluted[1],
  histsInput.Barrel.MnvH1D_mc_TRUTH,
  Playlist_name,
  Title,
  playlist_status,
  histsInput.Barrel.Xaxis_Title,
  "mm",  Ymax,  Convoluted_Mean,  Convoluted_stddev,
  chisqrt1,
  chisqrt2,
  chisqrt3);

 Title = "[DSCap]" + histotitle;

Plot_Eventdistrubution_RECOCol(histsInput.Downstream.MnvH1D_data,
  histsInput.Downstream.MnvH1D_mc_Reco,
  histsInput.Downstream.MnvH1D_mc_Convoluted[1],
  histsInput.Downstream.MnvH1D_mc_TRUTH,
  Playlist_name,
  Title,
  playlist_status,
  histsInput.Downstream.Xaxis_Title,
  "mm",  Ymax,  Convoluted_Mean,  Convoluted_stddev,
  chisqrt1,
  chisqrt2,
  chisqrt3);

 Title = "[DSConcave]" + histotitle;

Plot_Eventdistrubution_RECOCol(histsInput.Concave.MnvH1D_data,
  histsInput.Concave.MnvH1D_mc_Reco,
  histsInput.Concave.MnvH1D_mc_Convoluted[1],
  histsInput.Concave.MnvH1D_mc_TRUTH,
  Playlist_name,
  Title,
  playlist_status,
  histsInput.Concave.Xaxis_Title,
  "mm",  Ymax,  Convoluted_Mean,  Convoluted_stddev,
  chisqrt1,
  chisqrt2,
  chisqrt3);



}

void Convolution_Tool::Plot_ConvolRECO_Eventdistrubution_Regions(
  Convolution_CryoRegions &histsInput,
  std::string Playlist_name,
  std::string histotitle,
  std::string playlist_status,
  double Ymax, double Convoluted_Mean_USCap, double Convoluted_stddev_USCap,
  double Convoluted_Mean_barrel, double Convoluted_stddev_barrel,
  double Convoluted_Mean_DSCap, double Convoluted_stddev_DSCap,
  double Convoluted_Mean_concave, double Convoluted_stddev_concave)
  {
    double chisqrt1 = 10;
    double chisqrt2 = 10;
    double chisqrt3 = 10;

std::string Title = "[USCap]" + histotitle;

Plot_Eventdistrubution_RECOCol(histsInput.Upstream.MnvH1D_data,
      histsInput.Upstream.MnvH1D_mc_Reco,
      histsInput.Upstream.MnvH1D_mc_Convoluted[1],
      histsInput.Upstream.MnvH1D_mc_TRUTH,
      Playlist_name,
      Title,
      playlist_status,
      histsInput.Upstream.Xaxis_Title,
      "mm",  Ymax,  Convoluted_Mean_USCap,  Convoluted_stddev_USCap,
      chisqrt1,
      chisqrt2,
      chisqrt3);

 Title = "[barrel]" + histotitle;

Plot_Eventdistrubution_RECOCol(histsInput.Barrel.MnvH1D_data,
  histsInput.Barrel.MnvH1D_mc_Reco,
  histsInput.Barrel.MnvH1D_mc_Convoluted[1],
  histsInput.Barrel.MnvH1D_mc_TRUTH,
  Playlist_name,
  Title,
  playlist_status,
  histsInput.Barrel.Xaxis_Title,
  "mm",  Ymax,  Convoluted_Mean_barrel,  Convoluted_stddev_barrel,
  chisqrt1,
  chisqrt2,
  chisqrt3);

 Title = "[DSCap]" + histotitle;

Plot_Eventdistrubution_RECOCol(histsInput.Downstream.MnvH1D_data,
  histsInput.Downstream.MnvH1D_mc_Reco,
  histsInput.Downstream.MnvH1D_mc_Convoluted[1],
  histsInput.Downstream.MnvH1D_mc_TRUTH,
  Playlist_name,
  Title,
  playlist_status,
  histsInput.Downstream.Xaxis_Title,
  "mm",  Ymax,  Convoluted_Mean_DSCap,  Convoluted_stddev_DSCap,
  chisqrt1,
  chisqrt2,
  chisqrt3);

 Title = "[DSConcave]" + histotitle;

Plot_Eventdistrubution_RECOCol(histsInput.Concave.MnvH1D_data,
  histsInput.Concave.MnvH1D_mc_Reco,
  histsInput.Concave.MnvH1D_mc_Convoluted[1],
  histsInput.Concave.MnvH1D_mc_TRUTH,
  Playlist_name,
  Title,
  playlist_status,
  histsInput.Concave.Xaxis_Title,
  "mm",  Ymax,  Convoluted_Mean_concave,  Convoluted_stddev_concave,
  chisqrt1,
  chisqrt2,
  chisqrt3);



}

void Convolution_Tool::Plot_Full(double Convoluted_Mean, double Convoluted_stddev){

  Plot_EventDistrubution_TotalRegion(Full,"Combined", "Full",  Convoluted_Mean,  Convoluted_stddev, 0);
  Plot_EventDistrubution_TotalRegion(Empty,"Combined", "Empty",  Convoluted_Mean,  Convoluted_stddev, 0);
  Plot_EventDistrubution_TotalRegion(Full_Empty,"Combined", "F-E",  Convoluted_Mean,  Convoluted_stddev, 0);

}

void Convolution_Tool::Plot_Full_ConvolRECO(double Convoluted_Mean, double Convoluted_stddev){
std::cout<<"Ploting FUll "<<std::endl;
  Plot_EventDistrubution_ConvolRECO_TotalRegion(Full,      "Combined", "Full",  Convoluted_Mean,  Convoluted_stddev, 1);
  std::cout<<"Ploting Empty "<<std::endl;
  Plot_EventDistrubution_ConvolRECO_TotalRegion(Empty,     "Combined", "Empty",  Convoluted_Mean,  Convoluted_stddev, 1);
  std::cout<<"Ploting FUll - Empty "<<std::endl;
  Plot_EventDistrubution_ConvolRECO_TotalRegion(Full_Empty,"Combined", "F-E",  Convoluted_Mean,  Convoluted_stddev, 1);

}


void Convolution_Tool::Plot_EventDistrubution_TotalRegion(ConvolutionShiftMap &inputMap, std::string Playlist_name,
   std::string playlist_status, double Convoluted_Mean, double Convoluted_stddev, int ind){

  double chisqrt1 = 10;
  double chisqrt2 = 10;
  double chisqrt3 = 10;

  std::string Title_WithExtra;

Plot_Eventdistrubution(inputMap.Vertex_X_TotalRegion,   Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev, ind, chisqrt1, chisqrt2, chisqrt3);

Plot_Eventdistrubution(inputMap.Vertex_Y_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev, ind, chisqrt1, chisqrt2, chisqrt3);

Plot_Eventdistrubution(inputMap.Vertex_R_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev, ind, chisqrt1, chisqrt2, chisqrt3);

//Plot_Eventdistrubution(inputMap.Vertex_RR_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
//  1.0,  Convoluted_Mean,  Convoluted_stddev, ind, chisqrt1, chisqrt2, chisqrt3);

Plot_Eventdistrubution(inputMap.Vertex_Z_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev, ind, chisqrt1, chisqrt2, chisqrt3);

Title_WithExtra = "[RCut]  " + PlotTitle;
Plot_Eventdistrubution(inputMap.Vertex_Z_TotalRegion_RCut, Playlist_name,  Title_WithExtra , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev, ind, chisqrt1, chisqrt2, chisqrt3);

Plot_Eventdistrubution(inputMap.NearestWall_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev, ind, chisqrt1, chisqrt2, chisqrt3);

Plot_Eventdistrubution(inputMap.DistanceUpstreamCap_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev, ind, chisqrt1, chisqrt2, chisqrt3);

Plot_Eventdistrubution(inputMap.DistanceDownstreamCap_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev, ind, chisqrt1, chisqrt2, chisqrt3);

Plot_Eventdistrubution(inputMap.DistanceUpstreamCap_TotalRegion_RCut, Playlist_name,  Title_WithExtra , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev, ind, chisqrt1, chisqrt2, chisqrt3);

Plot_Eventdistrubution(inputMap.DistanceDownstreamCap_TotalRegion_RCut, Playlist_name,  Title_WithExtra , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev, ind, chisqrt1, chisqrt2, chisqrt3);

}

void Convolution_Tool::Plot_EventDistrubution_ConvolRECO_TotalRegion(ConvolutionShiftMap &inputMap, std::string Playlist_name,
   std::string playlist_status, double Convoluted_Mean, double Convoluted_stddev, int ind){

  double chisqrt1 = 10;
  double chisqrt2 = 10;
  double chisqrt3 = 10;

  std::string Title_WithExtra;

Plot_Eventdistrubution_RECOCol(inputMap.Vertex_X_TotalRegion,   Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev,  chisqrt1, chisqrt2, chisqrt3);

Plot_Eventdistrubution_RECOCol(inputMap.Vertex_Y_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev,  chisqrt1, chisqrt2, chisqrt3);

Plot_Eventdistrubution_RECOCol(inputMap.Vertex_R_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev,  chisqrt1, chisqrt2, chisqrt3);

//Plot_Eventdistrubution(inputMap.Vertex_RR_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
//  1.0,  Convoluted_Mean,  Convoluted_stddev, ind, chisqrt1, chisqrt2, chisqrt3);

Plot_Eventdistrubution_RECOCol(inputMap.Vertex_Z_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev,  chisqrt1, chisqrt2, chisqrt3);

Title_WithExtra = "[RCut]  " + PlotTitle;
Plot_Eventdistrubution_RECOCol(inputMap.Vertex_Z_TotalRegion_RCut, Playlist_name,  Title_WithExtra , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev,  chisqrt1, chisqrt2, chisqrt3);

Plot_Eventdistrubution_RECOCol(inputMap.NearestWall_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev,  chisqrt1, chisqrt2, chisqrt3);

Plot_Eventdistrubution_RECOCol(inputMap.DistanceUpstreamCap_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev, chisqrt1, chisqrt2, chisqrt3);

Plot_Eventdistrubution_RECOCol(inputMap.DistanceDownstreamCap_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev, chisqrt1, chisqrt2, chisqrt3);

Plot_Eventdistrubution_RECOCol(inputMap.DistanceUpstreamCap_TotalRegion_RCut, Playlist_name,  Title_WithExtra , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev, chisqrt1, chisqrt2, chisqrt3);

Plot_Eventdistrubution_RECOCol(inputMap.DistanceDownstreamCap_TotalRegion_RCut, Playlist_name,  Title_WithExtra , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev, chisqrt1, chisqrt2, chisqrt3);

}

void Convolution_Tool::Plot_EventDistrubution_ConvolRECO_TotalRegion(ConvolutionShiftMap &inputMap, std::string Playlist_name,
   std::string playlist_status,  BestIndex Index_input, NormalParaFit_Map ZShifts ){

  double chisqrt1 = 10;
  double chisqrt2 = 10;
  double chisqrt3 = 10;

double Convoluted_Mean;
double Convoluted_stddev;

  Index3 inputbest_Chisqrt_X{Index_input.best_Chisqrt_X.i,Index_input.best_Chisqrt_X.j,Index_input.best_Chisqrt_X.k};
  Convoluted_Mean = ZShifts[inputbest_Chisqrt_X].mean;
  Convoluted_stddev = ZShifts[inputbest_Chisqrt_X].stddev;
  std::string Title_WithExtra;

Plot_Eventdistrubution_RECOCol(inputMap.Vertex_X_TotalRegion,   Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev,  chisqrt1, chisqrt2, chisqrt3);

  Index3 inputbest_Chisqrt_Y{Index_input.best_Chisqrt_Y.i,Index_input.best_Chisqrt_Y.j,Index_input.best_Chisqrt_Y.k};
  Convoluted_Mean = ZShifts[inputbest_Chisqrt_Y].mean;
  Convoluted_stddev = ZShifts[inputbest_Chisqrt_Y].stddev;

Plot_Eventdistrubution_RECOCol(inputMap.Vertex_Y_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev,  chisqrt1, chisqrt2, chisqrt3);

  Index3 inputbest_Chisqrt_R{Index_input.best_Chisqrt_R.i,Index_input.best_Chisqrt_R.j,Index_input.best_Chisqrt_R.k};
  Convoluted_Mean = ZShifts[inputbest_Chisqrt_R].mean;
  Convoluted_stddev = ZShifts[inputbest_Chisqrt_R].stddev;

Plot_Eventdistrubution_RECOCol(inputMap.Vertex_R_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev,  chisqrt1, chisqrt2, chisqrt3);

//Plot_Eventdistrubution(inputMap.Vertex_RR_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
//  1.0,  Convoluted_Mean,  Convoluted_stddev, ind, chisqrt1, chisqrt2, chisqrt3);

Index3 inputbest_Chisqrt_Z{Index_input.best_Chisqrt_Z.i,Index_input.best_Chisqrt_Z.j,Index_input.best_Chisqrt_Z.k};
Convoluted_Mean = ZShifts[inputbest_Chisqrt_Z].mean;
Convoluted_stddev = ZShifts[inputbest_Chisqrt_Z].stddev;

Plot_Eventdistrubution_RECOCol(inputMap.Vertex_Z_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev,  chisqrt1, chisqrt2, chisqrt3);

  Index3 inputbest_Chisqrt_Z_RCut{Index_input.best_Chisqrt_Z_RCut.i,Index_input.best_Chisqrt_Z_RCut.j,Index_input.best_Chisqrt_Z_RCut.k};
  Convoluted_Mean = ZShifts[inputbest_Chisqrt_Z_RCut].mean;
  Convoluted_stddev = ZShifts[inputbest_Chisqrt_Z_RCut].stddev;

Title_WithExtra = "[RCut]  " + PlotTitle;
Plot_Eventdistrubution_RECOCol(inputMap.Vertex_Z_TotalRegion_RCut, Playlist_name,  Title_WithExtra , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev,  chisqrt1, chisqrt2, chisqrt3);

  Index3 inputbest_NearestWall{Index_input.best_Chisqrt_NearestWall.i,Index_input.best_Chisqrt_NearestWall.j,Index_input.best_Chisqrt_NearestWall.k};
  Convoluted_Mean = ZShifts[inputbest_NearestWall].mean;
  Convoluted_stddev = ZShifts[inputbest_NearestWall].stddev;

Plot_Eventdistrubution_RECOCol(inputMap.NearestWall_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev,  chisqrt1, chisqrt2, chisqrt3);

  Index3 inputbest_DistancetoUpstreamCap{Index_input.best_Chisqrt_DistancetoUpstreamCap.i,Index_input.best_Chisqrt_DistancetoUpstreamCap.j,Index_input.best_Chisqrt_DistancetoUpstreamCap.k};
  Convoluted_Mean = ZShifts[inputbest_DistancetoUpstreamCap].mean;
  Convoluted_stddev = ZShifts[inputbest_DistancetoUpstreamCap].stddev;

Plot_Eventdistrubution_RECOCol(inputMap.DistanceUpstreamCap_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev, chisqrt1, chisqrt2, chisqrt3);

  Index3 inputbest_DistancetoDownstreamCap{Index_input.best_Chisqrt_DistancetoDownstreamCap.i,Index_input.best_Chisqrt_DistancetoDownstreamCap.j,Index_input.best_Chisqrt_DistancetoDownstreamCap.k};
  Convoluted_Mean = ZShifts[inputbest_DistancetoDownstreamCap].mean;
  Convoluted_stddev = ZShifts[inputbest_DistancetoDownstreamCap].stddev;

Plot_Eventdistrubution_RECOCol(inputMap.DistanceDownstreamCap_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev, chisqrt1, chisqrt2, chisqrt3);

  Index3 inputbest_DistancetoUpstreamCap_RCut{Index_input.best_Chisqrt_DistancetoUpstreamCap_RCut.i,Index_input.best_Chisqrt_DistancetoUpstreamCap_RCut.j,Index_input.best_Chisqrt_DistancetoUpstreamCap_RCut.k};
  Convoluted_Mean = ZShifts[inputbest_DistancetoUpstreamCap_RCut].mean;
  Convoluted_stddev = ZShifts[inputbest_DistancetoUpstreamCap_RCut].stddev;

Plot_Eventdistrubution_RECOCol(inputMap.DistanceUpstreamCap_TotalRegion_RCut, Playlist_name,  Title_WithExtra , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev, chisqrt1, chisqrt2, chisqrt3);

  Index3 inputbest_DistancetoDownstreamCap_RCut{Index_input.best_Chisqrt_DistancetoDownstreamCap_RCut.i,Index_input.best_Chisqrt_DistancetoDownstreamCap_RCut.j,Index_input.best_Chisqrt_DistancetoDownstreamCap_RCut.k};
  Convoluted_Mean = ZShifts[inputbest_DistancetoDownstreamCap_RCut].mean;
  Convoluted_stddev = ZShifts[inputbest_DistancetoDownstreamCap_RCut].stddev;

Plot_Eventdistrubution_RECOCol(inputMap.DistanceDownstreamCap_TotalRegion_RCut, Playlist_name,  Title_WithExtra , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev, chisqrt1, chisqrt2, chisqrt3);

}
//~~~~~~~~~~~~~~~~~~~~~
void Convolution_Tool::Plot_EventDistrubution_ConvolRECO_TotalRegion_F_E(ConvolutionShiftMap &inputMap, std::string Playlist_name,
   std::string playlist_status,  BestIndex Index_input_Full, BestIndex Index_input_Empty, NormalParaFit_Map ZShifts ){

  double chisqrt1 = 10;
  double chisqrt2 = 10;
  double chisqrt3 = 10;

double Convoluted_MeanF;
double Convoluted_stddevF;

double Convoluted_MeanE;
double Convoluted_stddevE;

  Index3 inputbest_Chisqrt_XFULL{Index_input_Full.best_Chisqrt_X.i,Index_input_Full.best_Chisqrt_X.j,Index_input_Full.best_Chisqrt_X.k};
  Convoluted_MeanF = ZShifts[inputbest_Chisqrt_XFULL].mean;
  Convoluted_stddevF = ZShifts[inputbest_Chisqrt_XFULL].stddev;

  Index3 inputbest_Chisqrt_XEmpty{Index_input_Empty.best_Chisqrt_X.i,Index_input_Empty.best_Chisqrt_X.j,Index_input_Empty.best_Chisqrt_X.k};
  Convoluted_MeanE = ZShifts[inputbest_Chisqrt_XEmpty].mean;
  Convoluted_stddevE = ZShifts[inputbest_Chisqrt_XEmpty].stddev;

  std::string Title_WithExtra;

Plot_Eventdistrubution_RECOCol(inputMap.Vertex_X_TotalRegion,   Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_MeanF,  Convoluted_stddevF, Convoluted_MeanE,  Convoluted_stddevE,  chisqrt1, chisqrt2, chisqrt3);

  Index3 inputbest_Chisqrt_Y_Full{Index_input_Full.best_Chisqrt_Y.i,Index_input_Full.best_Chisqrt_Y.j,Index_input_Full.best_Chisqrt_Y.k};
  Convoluted_MeanF = ZShifts[inputbest_Chisqrt_Y_Full].mean;
  Convoluted_stddevF = ZShifts[inputbest_Chisqrt_Y_Full].stddev;

  Index3 inputbest_Chisqrt_Y_Empty{Index_input_Empty.best_Chisqrt_Y.i,Index_input_Empty.best_Chisqrt_Y.j,Index_input_Empty.best_Chisqrt_Y.k};
  Convoluted_MeanE = ZShifts[inputbest_Chisqrt_Y_Empty].mean;
  Convoluted_stddevE = ZShifts[inputbest_Chisqrt_Y_Empty].stddev;


Plot_Eventdistrubution_RECOCol(inputMap.Vertex_Y_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_MeanF,  Convoluted_stddevF, Convoluted_MeanE,  Convoluted_stddevE,  chisqrt1, chisqrt2, chisqrt3);

  Index3 inputbest_Chisqrt_R_Full{Index_input_Full.best_Chisqrt_R.i,Index_input_Full.best_Chisqrt_R.j,Index_input_Full.best_Chisqrt_R.k};
  Convoluted_MeanF = ZShifts[inputbest_Chisqrt_R_Full].mean;
  Convoluted_stddevF = ZShifts[inputbest_Chisqrt_R_Full].stddev;

  Index3 inputbest_Chisqrt_R_Empty{Index_input_Empty.best_Chisqrt_R.i,Index_input_Empty.best_Chisqrt_R.j,Index_input_Empty.best_Chisqrt_R.k};
  Convoluted_MeanE = ZShifts[inputbest_Chisqrt_R_Empty].mean;
  Convoluted_stddevE = ZShifts[inputbest_Chisqrt_R_Empty].stddev;

Plot_Eventdistrubution_RECOCol(inputMap.Vertex_R_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_MeanF,  Convoluted_stddevF, Convoluted_MeanE,  Convoluted_stddevE,  chisqrt1, chisqrt2, chisqrt3);

//Plot_Eventdistrubution(inputMap.Vertex_RR_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
//  1.0,  Convoluted_Mean,  Convoluted_stddev, ind, chisqrt1, chisqrt2, chisqrt3);

Index3 inputbest_Chisqrt_Z_Full{Index_input_Full.best_Chisqrt_Z.i,Index_input_Full.best_Chisqrt_Z.j,Index_input_Full.best_Chisqrt_Z.k};
Convoluted_MeanF = ZShifts[inputbest_Chisqrt_Z_Full].mean;
Convoluted_stddevF = ZShifts[inputbest_Chisqrt_Z_Full].stddev;

Index3 inputbest_Chisqrt_Z_Empty{Index_input_Empty.best_Chisqrt_Z.i,Index_input_Empty.best_Chisqrt_Z.j,Index_input_Empty.best_Chisqrt_Z.k};
Convoluted_MeanE = ZShifts[inputbest_Chisqrt_Z_Empty].mean;
Convoluted_stddevE = ZShifts[inputbest_Chisqrt_Z_Empty].stddev;

Plot_Eventdistrubution_RECOCol(inputMap.Vertex_Z_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_MeanF,  Convoluted_stddevF, Convoluted_MeanE,  Convoluted_stddevE,  chisqrt1, chisqrt2, chisqrt3);

  Index3 inputbest_Chisqrt_Z_RCut_Full{Index_input_Full.best_Chisqrt_Z_RCut.i,Index_input_Full.best_Chisqrt_Z_RCut.j,Index_input_Full.best_Chisqrt_Z_RCut.k};
  Convoluted_MeanF = ZShifts[inputbest_Chisqrt_Z_RCut_Full].mean;
  Convoluted_stddevF = ZShifts[inputbest_Chisqrt_Z_RCut_Full].stddev;

  Index3 inputbest_Chisqrt_Z_RCut_Empty{Index_input_Empty.best_Chisqrt_Z_RCut.i,Index_input_Empty.best_Chisqrt_Z_RCut.j,Index_input_Empty.best_Chisqrt_Z_RCut.k};
  Convoluted_MeanE = ZShifts[inputbest_Chisqrt_Z_RCut_Empty].mean;
  Convoluted_stddevE = ZShifts[inputbest_Chisqrt_Z_RCut_Empty].stddev;

Title_WithExtra = "[RCut]  " + PlotTitle;
Plot_Eventdistrubution_RECOCol(inputMap.Vertex_Z_TotalRegion_RCut, Playlist_name,  Title_WithExtra , playlist_status,
  1.0,  Convoluted_MeanF,  Convoluted_stddevF, Convoluted_MeanE,  Convoluted_stddevE,  chisqrt1, chisqrt2, chisqrt3);

  Index3 inputbest_NearestWall_Full{Index_input_Full.best_Chisqrt_NearestWall.i,Index_input_Full.best_Chisqrt_NearestWall.j,Index_input_Full.best_Chisqrt_NearestWall.k};
  Convoluted_MeanF = ZShifts[inputbest_NearestWall_Full].mean;
  Convoluted_stddevF = ZShifts[inputbest_NearestWall_Full].stddev;

  Index3 inputbest_NearestWall_Empty{Index_input_Empty.best_Chisqrt_NearestWall.i,Index_input_Empty.best_Chisqrt_NearestWall.j,Index_input_Empty.best_Chisqrt_NearestWall.k};
  Convoluted_MeanE = ZShifts[inputbest_NearestWall_Empty].mean;
  Convoluted_stddevE = ZShifts[inputbest_NearestWall_Empty].stddev;

Plot_Eventdistrubution_RECOCol(inputMap.NearestWall_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_MeanF,  Convoluted_stddevF, Convoluted_MeanE,  Convoluted_stddevE,  chisqrt1, chisqrt2, chisqrt3);

  Index3 inputbest_DistancetoUpstreamCap_Full{Index_input_Full.best_Chisqrt_DistancetoUpstreamCap.i,Index_input_Full.best_Chisqrt_DistancetoUpstreamCap.j,Index_input_Full.best_Chisqrt_DistancetoUpstreamCap.k};
  Convoluted_MeanF = ZShifts[inputbest_DistancetoUpstreamCap_Full].mean;
  Convoluted_stddevF = ZShifts[inputbest_DistancetoUpstreamCap_Full].stddev;

  Index3 inputbest_DistancetoUpstreamCap_Empty{Index_input_Empty.best_Chisqrt_DistancetoUpstreamCap.i,Index_input_Empty.best_Chisqrt_DistancetoUpstreamCap.j,Index_input_Empty.best_Chisqrt_DistancetoUpstreamCap.k};
  Convoluted_MeanE = ZShifts[inputbest_DistancetoUpstreamCap_Empty].mean;
  Convoluted_stddevE = ZShifts[inputbest_DistancetoUpstreamCap_Empty].stddev;

Plot_Eventdistrubution_RECOCol(inputMap.DistanceUpstreamCap_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_MeanF,  Convoluted_stddevF, Convoluted_MeanE,  Convoluted_stddevE, chisqrt1, chisqrt2, chisqrt3);

  Index3 inputbest_DistancetoDownstreamCap_Full{Index_input_Full.best_Chisqrt_DistancetoDownstreamCap.i,Index_input_Full.best_Chisqrt_DistancetoDownstreamCap.j,Index_input_Full.best_Chisqrt_DistancetoDownstreamCap.k};
  Convoluted_MeanF = ZShifts[inputbest_DistancetoDownstreamCap_Full].mean;
  Convoluted_stddevF = ZShifts[inputbest_DistancetoDownstreamCap_Full].stddev;

  Index3 inputbest_DistancetoDownstreamCap_Empty{Index_input_Empty.best_Chisqrt_DistancetoDownstreamCap.i,Index_input_Empty.best_Chisqrt_DistancetoDownstreamCap.j,Index_input_Empty.best_Chisqrt_DistancetoDownstreamCap.k};
  Convoluted_MeanE = ZShifts[inputbest_DistancetoDownstreamCap_Empty].mean;
  Convoluted_stddevE = ZShifts[inputbest_DistancetoDownstreamCap_Empty].stddev;

Plot_Eventdistrubution_RECOCol(inputMap.DistanceDownstreamCap_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_MeanF,  Convoluted_stddevF, Convoluted_MeanE,  Convoluted_stddevE, chisqrt1, chisqrt2, chisqrt3);

  Index3 inputbest_DistancetoUpstreamCap_RCut_Full{Index_input_Full.best_Chisqrt_DistancetoUpstreamCap_RCut.i,Index_input_Full.best_Chisqrt_DistancetoUpstreamCap_RCut.j,Index_input_Full.best_Chisqrt_DistancetoUpstreamCap_RCut.k};
  Convoluted_MeanF = ZShifts[inputbest_DistancetoUpstreamCap_RCut_Full].mean;
  Convoluted_stddevF = ZShifts[inputbest_DistancetoUpstreamCap_RCut_Full].stddev;

  Index3 inputbest_DistancetoUpstreamCap_RCut_Empty{Index_input_Empty.best_Chisqrt_DistancetoUpstreamCap_RCut.i,Index_input_Empty.best_Chisqrt_DistancetoUpstreamCap_RCut.j,Index_input_Empty.best_Chisqrt_DistancetoUpstreamCap_RCut.k};
  Convoluted_MeanE = ZShifts[inputbest_DistancetoUpstreamCap_RCut_Empty].mean;
  Convoluted_stddevE = ZShifts[inputbest_DistancetoUpstreamCap_RCut_Empty].stddev;

Plot_Eventdistrubution_RECOCol(inputMap.DistanceUpstreamCap_TotalRegion_RCut, Playlist_name,  Title_WithExtra , playlist_status,
  1.0,  Convoluted_MeanF,  Convoluted_stddevF, Convoluted_MeanE,  Convoluted_stddevE, chisqrt1, chisqrt2, chisqrt3);

  Index3 inputbest_DistancetoDownstreamCap_RCut_Full{Index_input_Full.best_Chisqrt_DistancetoDownstreamCap_RCut.i,Index_input_Full.best_Chisqrt_DistancetoDownstreamCap_RCut.j,Index_input_Full.best_Chisqrt_DistancetoDownstreamCap_RCut.k};
  Convoluted_MeanF = ZShifts[inputbest_DistancetoDownstreamCap_RCut_Full].mean;
  Convoluted_stddevF = ZShifts[inputbest_DistancetoDownstreamCap_RCut_Full].stddev;

  Index3 inputbest_DistancetoDownstreamCap_RCut_Empty{Index_input_Empty.best_Chisqrt_DistancetoDownstreamCap_RCut.i,Index_input_Empty.best_Chisqrt_DistancetoDownstreamCap_RCut.j,Index_input_Empty.best_Chisqrt_DistancetoDownstreamCap_RCut.k};
  Convoluted_MeanE = ZShifts[inputbest_DistancetoDownstreamCap_RCut_Empty].mean;
  Convoluted_stddevE = ZShifts[inputbest_DistancetoDownstreamCap_RCut_Empty].stddev;

Plot_Eventdistrubution_RECOCol(inputMap.DistanceDownstreamCap_TotalRegion_RCut, Playlist_name,  Title_WithExtra , playlist_status,
  1.0,  Convoluted_MeanF,  Convoluted_stddevF, Convoluted_MeanE,  Convoluted_stddevE, chisqrt1, chisqrt2, chisqrt3);

}

void Convolution_Tool::Plot_Full_ConvolRECO(NormalParaFit_Map ZShifts, BestIndex Index_input_Full, BestIndex Index_input_Empty){
std::cout<<"Ploting FUll "<<std::endl;
Plot_EventDistrubution_ConvolRECO_TotalRegion(Full,    "Combined", "Full",  Index_input_Full,  ZShifts );
  std::cout<<"Ploting Empty "<<std::endl;
Plot_EventDistrubution_ConvolRECO_TotalRegion(Empty,     "Combined", "Empty",  Index_input_Empty,  ZShifts);
  std::cout<<"Ploting FUll - Empty "<<std::endl;
Plot_EventDistrubution_ConvolRECO_TotalRegion_F_E(Full_Empty,     "Combined", "F-E", Index_input_Full,  Index_input_Empty,  ZShifts);
}



void Convolution_Tool::Plot_EventDistrubution_Regions(ConvolutionShiftMap &inputMap, std::string Playlist_name,
   std::string playlist_status, double Convoluted_Mean, double Convoluted_stddev, int ind){

std::string TitleExtra = "[RCut] " + PlotTitle;
Plot_Eventdistrubution_Regions(inputMap.Vertex_X_Regions,                   Playlist_name, PlotTitle,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev, ind);
Plot_Eventdistrubution_Regions(inputMap.Vertex_Y_Regions,                   Playlist_name, PlotTitle,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev, ind);
Plot_Eventdistrubution_Regions(inputMap.Vertex_Z_Regions,                   Playlist_name, PlotTitle,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev, ind);
Plot_Eventdistrubution_Regions(inputMap.Vertex_Z_Regions_RCut,              Playlist_name, TitleExtra,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev, ind);
Plot_Eventdistrubution_Regions(inputMap.Vertex_R_Regions,                   Playlist_name, PlotTitle,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev, ind);
//Plot_Eventdistrubution_Regions(inputMap.Vertex_RR_Regions,                  Playlist_name, PlotTitle,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev, ind);
Plot_Eventdistrubution_Regions(inputMap.NearestWall_Regions,                Playlist_name, PlotTitle,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev, ind);
Plot_Eventdistrubution_Regions(inputMap.DistanceUpstreamCap_Regions,        Playlist_name, PlotTitle,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev, ind);
Plot_Eventdistrubution_Regions(inputMap.DistanceDownstreamCap_Regions,      Playlist_name, PlotTitle,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev, ind);
Plot_Eventdistrubution_Regions(inputMap.DistanceUpstreamCap_Regions_RCut,   Playlist_name, TitleExtra,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev, ind);
Plot_Eventdistrubution_Regions(inputMap.DistanceDownstreamCap_Regions_RCut, Playlist_name, TitleExtra,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev, ind);

}





void Convolution_Tool::Plot_EventDistrubution_Regions_F_E(Convolution_CryoRegions &inputMap, std::string Playlist_name, std::string xaxislabel, std::string PlotTitle,
   std::string playlist_status,
   Index3 bestupstreamF,   Index3 bestupstreamE,
   Index3 bestbarrelF,     Index3 bestbarrelE,
   Index3 bestdownstreamF, Index3 bestdownstreamE,
   Index3 bestconcaveF,    Index3 bestconcaveE,
    NormalParaFit_Map ShiftsMap  ){

std::string TitleExtra = "[USCap] " +  PlotTitle;

double chi1=0;
double chi2=0;
double chi3=0;


Plot_Eventdistrubution_RECOCol(
  inputMap.Upstream.MnvH1D_data,
  inputMap.Upstream.MnvH1D_mc_Reco,
  inputMap.Upstream.MnvH1D_mc_Convoluted[1],
  inputMap.Upstream.MnvH1D_mc_TRUTH,
  Playlist_name,
  TitleExtra,
  playlist_status,
  xaxislabel,
  "NEvent",
  1.0,
  ShiftsMap[bestupstreamF].mean,
  ShiftsMap[bestupstreamF].stddev,
  ShiftsMap[bestupstreamE].mean,
  ShiftsMap[bestupstreamE].stddev,
  chi1,
  chi2,
  chi3);

  Plot_Eventdistrubution_RECOCol(
    inputMap.Barrel.MnvH1D_data,
    inputMap.Barrel.MnvH1D_mc_Reco,
    inputMap.Barrel.MnvH1D_mc_Convoluted[1],
    inputMap.Barrel.MnvH1D_mc_TRUTH,
    Playlist_name,
    TitleExtra,
    playlist_status,
    xaxislabel,
    "NEvent",
    1.0,
    ShiftsMap[bestbarrelF].mean,
    ShiftsMap[bestbarrelF].stddev,
    ShiftsMap[bestbarrelE].mean,
    ShiftsMap[bestbarrelE].stddev,
    chi1,
    chi2,
    chi3);


    Plot_Eventdistrubution_RECOCol(
      inputMap.Downstream.MnvH1D_data,
      inputMap.Downstream.MnvH1D_mc_Reco,
      inputMap.Downstream.MnvH1D_mc_Convoluted[1],
      inputMap.Downstream.MnvH1D_mc_TRUTH,
      Playlist_name,
      TitleExtra,
      playlist_status,
      xaxislabel,
      "NEvent",
      1.0,
      ShiftsMap[bestdownstreamF].mean,
      ShiftsMap[bestdownstreamF].stddev,
      ShiftsMap[bestdownstreamE].mean,
      ShiftsMap[bestdownstreamE].stddev,
      chi1,
      chi2,
      chi3);

      Plot_Eventdistrubution_RECOCol(
        inputMap.Concave.MnvH1D_data,
        inputMap.Concave.MnvH1D_mc_Reco,
        inputMap.Concave.MnvH1D_mc_Convoluted[1],
        inputMap.Concave.MnvH1D_mc_TRUTH,
        Playlist_name,
        TitleExtra,
        playlist_status,
        xaxislabel,
        "NEvent",
        1.0,
        ShiftsMap[bestconcaveF].mean,
        ShiftsMap[bestconcaveF].stddev,
        ShiftsMap[bestconcaveE].mean,
        ShiftsMap[bestconcaveE].stddev,
        chi1,
        chi2,
        chi3);



}








void Convolution_Tool::Plot_EventDistrubution_Regions_ConvolRECO(ConvolutionShiftMap &inputMap, std::string Playlist_name,
   std::string playlist_status, double Convoluted_Mean, double Convoluted_stddev){

std::string TitleExtra = "[RCut] " + PlotTitle;
Plot_ConvolRECO_Eventdistrubution_Regions(inputMap.Vertex_X_Regions,                   Playlist_name, PlotTitle,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev);
Plot_ConvolRECO_Eventdistrubution_Regions(inputMap.Vertex_Y_Regions,                   Playlist_name, PlotTitle,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev);
Plot_ConvolRECO_Eventdistrubution_Regions(inputMap.Vertex_Z_Regions,                   Playlist_name, PlotTitle,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev);
Plot_ConvolRECO_Eventdistrubution_Regions(inputMap.Vertex_Z_Regions_RCut,              Playlist_name, TitleExtra,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev);
Plot_ConvolRECO_Eventdistrubution_Regions(inputMap.Vertex_R_Regions,                   Playlist_name, PlotTitle,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev);
//Plot_EventDistrubution_Regions_ConvolRECO(inputMap.Vertex_RR_Regions,                  Playlist_name, PlotTitle,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev, ind);
Plot_ConvolRECO_Eventdistrubution_Regions(inputMap.NearestWall_Regions,                Playlist_name, PlotTitle,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev);
Plot_ConvolRECO_Eventdistrubution_Regions(inputMap.DistanceUpstreamCap_Regions,        Playlist_name, PlotTitle,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev);
Plot_ConvolRECO_Eventdistrubution_Regions(inputMap.DistanceDownstreamCap_Regions,      Playlist_name, PlotTitle,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev);
Plot_ConvolRECO_Eventdistrubution_Regions(inputMap.DistanceUpstreamCap_Regions_RCut,   Playlist_name, TitleExtra,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev);
Plot_ConvolRECO_Eventdistrubution_Regions(inputMap.DistanceDownstreamCap_Regions_RCut, Playlist_name, TitleExtra,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev);

}



 void Convolution_Tool::PlotFull(double Convoluted_Mean, double Convoluted_stddev, int ind ){
  Plot_EventDistrubution_TotalRegion(Full, "Combined",
  "F",  Convoluted_Mean,  Convoluted_stddev,  ind);
}

void Convolution_Tool::PlotFull_ConvolRECO(double Convoluted_Mean, double Convoluted_stddev, int ind ){
 Plot_EventDistrubution_ConvolRECO_TotalRegion(Full, "Combined",
 "F",  Convoluted_Mean,  Convoluted_stddev,  ind);
}



void Convolution_Tool::PlotFull_Regions(double Convoluted_Mean, double Convoluted_stddev, int ind ){
 Plot_EventDistrubution_Regions(Full, "Combined",
 "F",  Convoluted_Mean,  Convoluted_stddev,  ind);
}

void Convolution_Tool::PlotFull_Regions_ConvolRECO(double Convoluted_Mean, double Convoluted_stddev){
 Plot_EventDistrubution_Regions_ConvolRECO(Full, "Combined",
 "F",  Convoluted_Mean,  Convoluted_stddev);
}

 void Convolution_Tool::PlotEmpty(double Convoluted_Mean, double Convoluted_stddev, int ind ){
  Plot_EventDistrubution_TotalRegion(Empty, "Combined",
  "E",  Convoluted_Mean,  Convoluted_stddev,  ind);
}

void Convolution_Tool::PlotEmpty_Regions(double Convoluted_Mean, double Convoluted_stddev, int ind ){
 Plot_EventDistrubution_Regions(Empty, "Combined",
 "E",  Convoluted_Mean,  Convoluted_stddev,  ind);
}

void Convolution_Tool::PlotEmpty_Regions_ConvolRECO(double Convoluted_Mean, double Convoluted_stddev ){
  Plot_EventDistrubution_Regions_ConvolRECO(Empty, "Combined",
 "E",  Convoluted_Mean,  Convoluted_stddev);
}


void Convolution_Tool::PlotFull_Empty(double Convoluted_Mean, double Convoluted_stddev, int ind ){
  Plot_EventDistrubution_TotalRegion(Full_Empty, "Combined",
  "F-E",  Convoluted_Mean,  Convoluted_stddev,  ind);
}

void Convolution_Tool::PlotFull_Empty_Regions(double Convoluted_Mean, double Convoluted_stddev, int ind ){
 Plot_EventDistrubution_Regions(Full_Empty, "Combined",
 "F-E",  Convoluted_Mean,  Convoluted_stddev,  ind);
}

void Convolution_Tool::PlotFull_Empty_Regions_ConvolRECO(double Convoluted_Mean, double Convoluted_stddev ){
 Plot_EventDistrubution_Regions_ConvolRECO(Full_Empty, "Combined",
 "F-E",  Convoluted_Mean,  Convoluted_stddev);
}




void Convolution_Tool::Plot_Regions(double Convoluted_Mean, double Convoluted_stddev){
PlotFull_Regions( Convoluted_Mean, Convoluted_stddev,  0 );
PlotEmpty_Regions( Convoluted_Mean, Convoluted_stddev,  0 );
PlotFull_Empty_Regions( Convoluted_Mean, Convoluted_stddev,  0 );
}

void Convolution_Tool::Plot_Regions_ConvolRECO(double Convoluted_Mean, double Convoluted_stddev){
PlotFull_Regions_ConvolRECO( Convoluted_Mean, Convoluted_stddev );
PlotEmpty_Regions_ConvolRECO( Convoluted_Mean, Convoluted_stddev );
PlotFull_Empty_Regions_ConvolRECO( Convoluted_Mean, Convoluted_stddev );
}



void Convolution_Tool::SetBinWidthNorm(bool input){global_DoBinwidthNorm = input;}
void Convolution_Tool::SetXaxis_toLog(bool input){global_MakeXaxisLOG = input;}


void Convolution_Tool::Cal_Chisqrt_ConvolutionTruth_ToData(MnvPlotter *MnvPlotter,
  Convolution_hist input,
  double &Chi2DataMC_DatatoTRUTH, int &ndf_Chi2DataMC_DatatoTRUTH, int ind )
  {
     Chi2DataMC_DatatoTRUTH       =  MnvPlotter->Chi2DataMC(input.MnvH1D_data,    input.MnvH1D_mc_Convoluted[ind], ndf_Chi2DataMC_DatatoTRUTH);
     //Chi2DataMC_DatatoTRUTH       = CalChiSqrt(input, ind );
  }



  void Convolution_Tool::Cal_Chisqrt_ConvolutionTruth_ToData_Regions(MnvPlotter *MnvPlotter,
    Convolution_CryoRegions &Hist_input, int ind,
    double &Chi2DataMC_DatatoTRUTH_upstream,   int &ndf_Chi2DataMC_DatatoTRUTH_upstream,
    double &Chi2DataMC_DatatoTRUTH_barrel,     int &ndf_Chi2DataMC_DatatoTRUTH_barrel,
    double &Chi2DataMC_DatatoTRUTH_downstream, int &ndf_Chi2DataMC_DatatoTRUTH_downstream,
    double &Chi2DataMC_DatatoTRUTH_concave,    int &ndf_Chi2DataMC_DatatoTRUTH_concave){

      Cal_Chisqrt_ConvolutionTruth_ToData(MnvPlotter, Hist_input.Upstream,
      Chi2DataMC_DatatoTRUTH_upstream, ndf_Chi2DataMC_DatatoTRUTH_upstream,  ind );

      Cal_Chisqrt_ConvolutionTruth_ToData(MnvPlotter,  Hist_input.Barrel,
        Chi2DataMC_DatatoTRUTH_barrel, ndf_Chi2DataMC_DatatoTRUTH_barrel,  ind );

      Cal_Chisqrt_ConvolutionTruth_ToData(MnvPlotter, Hist_input.Downstream,
        Chi2DataMC_DatatoTRUTH_downstream, ndf_Chi2DataMC_DatatoTRUTH_downstream,  ind );

      Cal_Chisqrt_ConvolutionTruth_ToData(MnvPlotter, Hist_input.Concave,
        Chi2DataMC_DatatoTRUTH_concave, ndf_Chi2DataMC_DatatoTRUTH_concave,  ind );

  }

  void Convolution_Tool::Cal_Chisqrt_ConvolutionTruth_ToData_Regions(MnvPlotter *MnvPlotter,
    Convolution_CryoRegions &Hist_input, int ind,
    double &Chi2DataMC_DatatoTRUTH_upstream,
    double &Chi2DataMC_DatatoTRUTH_barrel,
    double &Chi2DataMC_DatatoTRUTH_downstream,
    double &Chi2DataMC_DatatoTRUTH_concave ){

      int ndf1= 0; int ndf2= 0; int ndf3= 0; int  ndf4= 0;

      Cal_Chisqrt_ConvolutionTruth_ToData_Regions(MnvPlotter, Hist_input, ind,
        Chi2DataMC_DatatoTRUTH_upstream,   ndf1,
        Chi2DataMC_DatatoTRUTH_barrel,     ndf2,
        Chi2DataMC_DatatoTRUTH_downstream, ndf3,
        Chi2DataMC_DatatoTRUTH_concave,    ndf4);

  }




void Convolution_Tool::Cal_Chisqrt_ConvolutionTruth_ToData_Regions(MnvPlotter *MnvPlotter,
    ConvolutionShiftMap &Hist_Map, ChiSqrt_CryoTankRegions &Chi_Sqt_Map, int ind)
  {

Cal_Chisqrt_ConvolutionTruth_ToData_Regions(MnvPlotter,
  Hist_Map.Vertex_X_Regions, ind,
  Chi_Sqt_Map.upstream.Chisqrt_X,
  Chi_Sqt_Map.barrel.Chisqrt_X,
  Chi_Sqt_Map.downstream.Chisqrt_X,
  Chi_Sqt_Map.concave.Chisqrt_X);

Cal_Chisqrt_ConvolutionTruth_ToData_Regions(MnvPlotter,
  Hist_Map.Vertex_Y_Regions, ind,
  Chi_Sqt_Map.upstream.Chisqrt_Y,
  Chi_Sqt_Map.barrel.Chisqrt_Y,
  Chi_Sqt_Map.downstream.Chisqrt_Y,
  Chi_Sqt_Map.concave.Chisqrt_Y);

Cal_Chisqrt_ConvolutionTruth_ToData_Regions(MnvPlotter,
  Hist_Map.Vertex_Z_Regions, ind,
  Chi_Sqt_Map.upstream.Chisqrt_Z,
  Chi_Sqt_Map.barrel.Chisqrt_Z,
  Chi_Sqt_Map.downstream.Chisqrt_Z,
  Chi_Sqt_Map.concave.Chisqrt_Z);

Cal_Chisqrt_ConvolutionTruth_ToData_Regions(MnvPlotter,
  Hist_Map.Vertex_Z_Regions_RCut, ind,
  Chi_Sqt_Map.upstream.Chisqrt_Z_RCut,
  Chi_Sqt_Map.barrel.Chisqrt_Z_RCut,
  Chi_Sqt_Map.downstream.Chisqrt_Z_RCut,
  Chi_Sqt_Map.concave.Chisqrt_Z_RCut);

Cal_Chisqrt_ConvolutionTruth_ToData_Regions(MnvPlotter,
  Hist_Map.Vertex_R_Regions, ind,
  Chi_Sqt_Map.upstream.Chisqrt_R,
  Chi_Sqt_Map.barrel.Chisqrt_R,
  Chi_Sqt_Map.downstream.Chisqrt_R,
  Chi_Sqt_Map.concave.Chisqrt_R);

Cal_Chisqrt_ConvolutionTruth_ToData_Regions(MnvPlotter,
Hist_Map.Vertex_RR_Regions, 0
Chi_Sqt_Map.upstream.Chisqrt_RR,
Chi_Sqt_Map.barrel.Chisqrt_RR,
Chi_Sqt_Map.downstream.Chisqrt_RR,
Chi_Sqt_Map.concave.Chisqrt_RR);

Cal_Chisqrt_ConvolutionTruth_ToData_Regions(MnvPlotter,
  Hist_Map.NearestWall_Regions, ind,
  Chi_Sqt_Map.upstream.Chisqrt_NearestWall,
  Chi_Sqt_Map.barrel.Chisqrt_NearestWall,
  Chi_Sqt_Map.downstream.Chisqrt_NearestWall,
  Chi_Sqt_Map.concave.Chisqrt_NearestWall);

Cal_Chisqrt_ConvolutionTruth_ToData_Regions(MnvPlotter,
  Hist_Map.DistanceUpstreamCap_Regions, ind,
  Chi_Sqt_Map.upstream.Chisqrt_DistancetoUpstreamCap,
  Chi_Sqt_Map.barrel.Chisqrt_DistancetoUpstreamCap,
  Chi_Sqt_Map.downstream.Chisqrt_DistancetoUpstreamCap,
  Chi_Sqt_Map.concave.Chisqrt_DistancetoUpstreamCap);

Cal_Chisqrt_ConvolutionTruth_ToData_Regions(MnvPlotter,
  Hist_Map.DistanceDownstreamCap_Regions, ind,
  Chi_Sqt_Map.upstream.Chisqrt_DistancetoDownstreamCap,
  Chi_Sqt_Map.barrel.Chisqrt_DistancetoDownstreamCap,
  Chi_Sqt_Map.downstream.Chisqrt_DistancetoDownstreamCap,
  Chi_Sqt_Map.concave.Chisqrt_DistancetoDownstreamCap);

Cal_Chisqrt_ConvolutionTruth_ToData_Regions(MnvPlotter,
  Hist_Map.DistanceUpstreamCap_Regions_RCut, ind,
  Chi_Sqt_Map.upstream.Chisqrt_DistancetoUpstreamCap_RCut,
  Chi_Sqt_Map.barrel.Chisqrt_DistancetoUpstreamCap_RCut,
  Chi_Sqt_Map.downstream.Chisqrt_DistancetoUpstreamCap_RCut,
  Chi_Sqt_Map.concave.Chisqrt_DistancetoUpstreamCap_RCut);

Cal_Chisqrt_ConvolutionTruth_ToData_Regions(MnvPlotter,
  Hist_Map.DistanceDownstreamCap_Regions_RCut, ind,
  Chi_Sqt_Map.upstream.Chisqrt_DistancetoDownstreamCap_RCut,
  Chi_Sqt_Map.barrel.Chisqrt_DistancetoDownstreamCap_RCut,
  Chi_Sqt_Map.downstream.Chisqrt_DistancetoDownstreamCap_RCut,
  Chi_Sqt_Map.concave.Chisqrt_DistancetoDownstreamCap_RCut);
}


void   Convolution_Tool::Cal_Chisqrt_ConvolutionTruth_ToData_Regions(MnvPlotter *MnvPlotter,
  ChiSqrt_CryoTankRegions &inputFull,
  ChiSqrt_CryoTankRegions &inputEmpty,
  ChiSqrt_CryoTankRegions &input_Full_Empty, int ind ){

    Cal_Chisqrt_ConvolutionTruth_ToData_Regions(MnvPlotter, Full, inputFull, ind);
    Cal_Chisqrt_ConvolutionTruth_ToData_Regions(MnvPlotter, Empty, inputEmpty, ind);
    Cal_Chisqrt_ConvolutionTruth_ToData_Regions(MnvPlotter, Full_Empty, input_Full_Empty, ind);

  }




void Convolution_Tool::Cal_Chisqt_Total(ConvolutionShiftMap &Hist_Map, ChiSqrt_results &input, MnvPlotter *MnvPlotter , int ind){
int ndf;

//std::cout<<"inside:Cal_Chisqt_Total"<<std::endl;

Cal_Chisqrt_ConvolutionTruth_ToData(MnvPlotter,Hist_Map.Vertex_X_TotalRegion, input.Chisqrt_X, ndf, ind);
Cal_Chisqrt_ConvolutionTruth_ToData(MnvPlotter,Hist_Map.Vertex_Y_TotalRegion, input.Chisqrt_Y, ndf, ind);
Cal_Chisqrt_ConvolutionTruth_ToData(MnvPlotter,Hist_Map.Vertex_R_TotalRegion, input.Chisqrt_R, ndf, ind);
//Cal_Chisqrt_ConvolutionTruth_ToData(MnvPlotter,Hist_Map.Vertex_RR_TotalRegion, input., 0);
Cal_Chisqrt_ConvolutionTruth_ToData(MnvPlotter,Hist_Map.Vertex_Z_TotalRegion,                   input.Chisqrt_Z,                            ndf, ind);
Cal_Chisqrt_ConvolutionTruth_ToData(MnvPlotter,Hist_Map.Vertex_Z_TotalRegion_RCut,              input.Chisqrt_Z_RCut,                       ndf, ind);
Cal_Chisqrt_ConvolutionTruth_ToData(MnvPlotter,Hist_Map.NearestWall_TotalRegion,                input.Chisqrt_NearestWall,                  ndf, ind);
Cal_Chisqrt_ConvolutionTruth_ToData(MnvPlotter,Hist_Map.DistanceUpstreamCap_TotalRegion,        input.Chisqrt_DistancetoUpstreamCap,        ndf, ind);
Cal_Chisqrt_ConvolutionTruth_ToData(MnvPlotter,Hist_Map.DistanceDownstreamCap_TotalRegion,      input.Chisqrt_DistancetoDownstreamCap,      ndf, ind);
Cal_Chisqrt_ConvolutionTruth_ToData(MnvPlotter,Hist_Map.DistanceUpstreamCap_TotalRegion_RCut,   input.Chisqrt_DistancetoUpstreamCap_RCut,   ndf, ind);
Cal_Chisqrt_ConvolutionTruth_ToData(MnvPlotter,Hist_Map.DistanceDownstreamCap_TotalRegion_RCut, input.Chisqrt_DistancetoDownstreamCap_RCut, ndf, ind);

}








void Convolution_Tool::Cal_Chisqt_Total(ChiSqrt_results &inputFull, ChiSqrt_results &inputEmpty, ChiSqrt_results &input_Full_Empty, MnvPlotter *MnvPlotter, int ind ){


Cal_Chisqt_Total(Full, inputFull, MnvPlotter , ind);
Cal_Chisqt_Total(Empty, inputEmpty, MnvPlotter , ind);
Cal_Chisqt_Total(Full_Empty, input_Full_Empty, MnvPlotter , ind);

}



void Convolution_Tool::SaveBestChiSqrt_Total(ChiSqrt_results &inputFull_best,
                                             ChiSqrt_results &inputEmpty_best,
                                             ChiSqrt_results &input_Full_Empty_best,

                                             ChiSqrt_results &inputFull_input,
                                             ChiSqrt_results &inputEmpty_input,
                                             ChiSqrt_results &input_Full_Empty_input,
BestIndex &bestindex_Full, BestIndex &bestindex_Empty, BestIndex &bestindex_Full_Empty,
 Index3 input){

SaveBestChisqt_Total(inputFull_best, bestindex_Full, inputFull_input, input);
SaveBestChisqt_Total(inputEmpty_best, bestindex_Empty, inputEmpty_input, input);
SaveBestChisqt_Total(input_Full_Empty_best, bestindex_Full_Empty, input_Full_Empty_input, input);
}



void Convolution_Tool::Fill_bestIndex3_default(BestIndex &input){

  Index3 Zero_index{0,0,0};

  input.best_Chisqrt_X = Zero_index;
  input.best_Chisqrt_Y = Zero_index;
  input.best_Chisqrt_Z = Zero_index;
  input.best_Chisqrt_Z_RCut = Zero_index;
  input.best_Chisqrt_R = Zero_index;
  input.best_Chisqrt_NearestWall = Zero_index;
  input.best_Chisqrt_DistancetoUpstreamCap = Zero_index;
  input.best_Chisqrt_DistancetoUpstreamCap_RCut = Zero_index;
  input.best_Chisqrt_DistancetoDownstreamCap = Zero_index;
  input.best_Chisqrt_DistancetoDownstreamCap_RCut = Zero_index;

}



void Convolution_Tool::Fill_ChiSqrt_results_default(ChiSqrt_results &inputMap){

  double inputValue = 999999;

  inputMap.Chisqrt_X = inputValue;
  inputMap.Chisqrt_Y = inputValue;
  inputMap.Chisqrt_Z = inputValue;
  inputMap.Chisqrt_Z_RCut = inputValue;
  inputMap.Chisqrt_R = inputValue;
  inputMap.Chisqrt_NearestWall = inputValue;
  inputMap.Chisqrt_DistancetoUpstreamCap = inputValue;
  inputMap.Chisqrt_DistancetoUpstreamCap_RCut = inputValue;
  inputMap.Chisqrt_DistancetoDownstreamCap = inputValue;
  inputMap.Chisqrt_DistancetoDownstreamCap_RCut = inputValue;

}



void Convolution_Tool::Fill_Regions_bestindex3_default(BestIndex_Regions inputMap){

Fill_bestIndex3_default(inputMap.upstream);
Fill_bestIndex3_default(inputMap.barrel);
Fill_bestIndex3_default(inputMap.downstream);
Fill_bestIndex3_default(inputMap.concave);

}


void Convolution_Tool::Fill_Regions_ChiSqrt_results_default(ChiSqrt_CryoTankRegions &inputMap){

Fill_ChiSqrt_results_default(inputMap.upstream);
Fill_ChiSqrt_results_default(inputMap.barrel);
Fill_ChiSqrt_results_default(inputMap.downstream);
Fill_ChiSqrt_results_default(inputMap.concave);

}



 void Convolution_Tool::SaveBestChisqt_Total(ChiSqrt_results &Best, BestIndex &bestindex, ChiSqrt_results &Compare , Index3 input ){

 if(Best.Chisqrt_X  > Compare.Chisqrt_X){
 Best.Chisqrt_X = Compare.Chisqrt_X;
 bestindex.best_Chisqrt_X = input;
 }

 if(Best.Chisqrt_Y  > Compare.Chisqrt_Y){
 Best.Chisqrt_Y = Compare.Chisqrt_Y;
 bestindex.best_Chisqrt_Y = input;
 }

 if(Best.Chisqrt_Z  > Compare.Chisqrt_Z){
 Best.Chisqrt_Z = Compare.Chisqrt_Z;
 bestindex.best_Chisqrt_Z = input;
 }

 if(Best.Chisqrt_Z_RCut  > Compare.Chisqrt_Z_RCut){
 Best.Chisqrt_Z_RCut = Compare.Chisqrt_Z_RCut;
 bestindex.best_Chisqrt_Z_RCut = input;
 }

 if(Best.Chisqrt_R  > Compare.Chisqrt_R){
 Best.Chisqrt_R = Compare.Chisqrt_R;
 bestindex.best_Chisqrt_R = input;
 }


 if(Best.Chisqrt_NearestWall  > Compare.Chisqrt_NearestWall){
 Best.Chisqrt_NearestWall = Compare.Chisqrt_NearestWall;
 bestindex.best_Chisqrt_NearestWall = input;
 }


 if(Best.Chisqrt_DistancetoUpstreamCap  > Compare.Chisqrt_DistancetoUpstreamCap){
 Best.Chisqrt_DistancetoUpstreamCap = Compare.Chisqrt_DistancetoUpstreamCap;
 bestindex.best_Chisqrt_DistancetoUpstreamCap = input;
 }

 if(Best.Chisqrt_DistancetoUpstreamCap_RCut  > Compare.Chisqrt_DistancetoUpstreamCap_RCut){
 Best.Chisqrt_DistancetoUpstreamCap_RCut = Compare.Chisqrt_DistancetoUpstreamCap_RCut;
 bestindex.best_Chisqrt_DistancetoUpstreamCap_RCut = input;
 }

 if(Best.Chisqrt_DistancetoDownstreamCap  > Compare.Chisqrt_DistancetoDownstreamCap){
 Best.Chisqrt_DistancetoDownstreamCap = Compare.Chisqrt_DistancetoDownstreamCap;
 bestindex.best_Chisqrt_DistancetoDownstreamCap = input;
 }

 if(Best.Chisqrt_DistancetoDownstreamCap_RCut  > Compare.Chisqrt_DistancetoDownstreamCap_RCut){
 Best.Chisqrt_DistancetoDownstreamCap_RCut = Compare.Chisqrt_DistancetoDownstreamCap_RCut;
 bestindex.best_Chisqrt_DistancetoDownstreamCap_RCut = input;
 }

 }



 void Convolution_Tool::SaveBestChisqt_Regions(ChiSqrt_CryoTankRegions &Best_Map, BestIndex_Regions &bestindex, ChiSqrt_CryoTankRegions &Compare_Map , Index3 input ){

   SaveBestChisqt_Total(Best_Map.upstream,   bestindex.upstream,   Compare_Map.upstream,   input);
   SaveBestChisqt_Total(Best_Map.barrel,     bestindex.barrel,     Compare_Map.barrel,     input);
   SaveBestChisqt_Total(Best_Map.downstream, bestindex.downstream, Compare_Map.downstream, input);
   SaveBestChisqt_Total(Best_Map.concave,    bestindex.concave,    Compare_Map.concave,    input);

 }

  void Convolution_Tool::SaveBestChiSqrt_Regions(
                         ChiSqrt_CryoTankRegions &input_Full_best,
                         ChiSqrt_CryoTankRegions &input_Empty_best,
                         ChiSqrt_CryoTankRegions &input_Full_Empty_best,
                         ChiSqrt_CryoTankRegions &input_Full,
                         ChiSqrt_CryoTankRegions &input_Empty,
                         ChiSqrt_CryoTankRegions &input_Full_Empty,
                         BestIndex_Regions &bestindex_Full,
                         BestIndex_Regions &bestindex_Empty,
                         BestIndex_Regions &bestindex_Full_Empty, Index3 input)
                         {

  SaveBestChisqt_Regions(input_Full_best,       bestindex_Full,       input_Full,       input);
  SaveBestChisqt_Regions(input_Empty_best,      bestindex_Empty,      input_Empty ,     input);
  SaveBestChisqt_Regions(input_Full_Empty_best, bestindex_Full_Empty, input_Full_Empty, input);


                         }





void Convolution_Tool::Fill_TotalChiSqrts(ChiSqrt_results &ChiSqrt_input, double mean,
  double stddev,
  MnvH2D *h2_Vertex_X_TotalRegion[],
  MnvH2D *h2_Vertex_Y_TotalRegion[],
  MnvH2D *h2_Vertex_R_TotalRegion[],
  MnvH2D &h2_Vertex_RR_TotalRegion,
  MnvH2D *h2_Vertex_Z_TotalRegion[],
  MnvH2D *h2_Vertex_Z_TotalRegion_RCut[],
  MnvH2D *h2_NearestWall_TotalRegion[],
  MnvH2D *h2_DistanceUpstreamCap_TotalRegion[],
  MnvH2D *h2_DistanceDownstreamCap_TotalRegion[],
  MnvH2D *h2_DistanceUpstreamCap_TotalRegion_RCut[],
  MnvH2D *h2_DistanceDownstreamCap_TotalRegion_RCut[])
  {
    h2_Vertex_X_TotalRegion[0]->Fill(                  mean,stddev,ChiSqrt_input.Chisqrt_X);
    h2_Vertex_Y_TotalRegion[0]->Fill(                  mean,stddev,ChiSqrt_input.Chisqrt_Y);
    h2_Vertex_R_TotalRegion[0]->Fill(                  mean,stddev,ChiSqrt_input.Chisqrt_R);
    //h2_Vertex_RR_TotalRegion.Fill(mean,stddev,);
    h2_Vertex_Z_TotalRegion[0]->Fill(                  mean,stddev,ChiSqrt_input.Chisqrt_Z);
    h2_Vertex_Z_TotalRegion_RCut[0]->Fill(             mean,stddev,ChiSqrt_input.Chisqrt_Z_RCut);
    h2_NearestWall_TotalRegion[0]->Fill(               mean,stddev,ChiSqrt_input.Chisqrt_NearestWall);
    h2_DistanceUpstreamCap_TotalRegion[0]->Fill(       mean,stddev,ChiSqrt_input.Chisqrt_DistancetoUpstreamCap);
    h2_DistanceDownstreamCap_TotalRegion[0]->Fill(     mean,stddev,ChiSqrt_input.Chisqrt_DistancetoDownstreamCap);
    h2_DistanceUpstreamCap_TotalRegion_RCut[0]->Fill(  mean,stddev,ChiSqrt_input.Chisqrt_DistancetoUpstreamCap_RCut);
    h2_DistanceDownstreamCap_TotalRegion_RCut[0]->Fill(mean,stddev,ChiSqrt_input.Chisqrt_DistancetoDownstreamCap_RCut);
  };



  void Convolution_Tool::Fill_TotalChiSqrts_Regions(ChiSqrt_CryoTankRegions &ChiSqrt_input, double mean,
    double stddev,
    MnvH2D *h2_Vertex_X_Regions[],
    MnvH2D *h2_Vertex_Y_Regions[],
    MnvH2D *h2_Vertex_R_Regions[],
    MnvH2D &h2_Vertex_RR_Regions[5],
    MnvH2D *h2_Vertex_Z_Regions[],
    MnvH2D *h2_Vertex_Z_Regions_RCut[],
    MnvH2D *h2_NearestWall_Regions[],
    MnvH2D *h2_DistanceUpstreamCap_Regions[],
    MnvH2D *h2_DistanceDownstreamCap_Regions[],
    MnvH2D *h2_DistanceUpstreamCap_Regions_RCut[],
    MnvH2D *h2_DistanceDownstreamCap_Regions_RCut[])
    {

      //std::cout<<"Inside:: Fill_TotalChiSqrts_Regions : 1"<<std::endl;

    //  std::cout<<"Filling values mean = "<< mean << " stddev = " << stddev<< " ChiSqrt_input.upstream.Chisqrt_X = " << ChiSqrt_input.upstream.Chisqrt_X  << std::endl;
    //  std::cout<< "h2_Vertex_X_Regions->size() = " <<  sizeof(h2_Vertex_X_Regions)<<std::endl;
      h2_Vertex_X_Regions[1]->Fill(mean,                   stddev,ChiSqrt_input.upstream.Chisqrt_X);
      h2_Vertex_Y_Regions[1]->Fill(mean,                   stddev,ChiSqrt_input.upstream.Chisqrt_Y);
      h2_Vertex_R_Regions[1]->Fill(mean,                   stddev,ChiSqrt_input.upstream.Chisqrt_R);
      //h2_Vertex_RR_TotalRegion.Fill(mean,stddev,);
      h2_Vertex_Z_Regions[1]->Fill(mean,                  stddev,ChiSqrt_input.upstream.Chisqrt_Z);
      h2_Vertex_Z_Regions_RCut[1]->Fill(mean,             stddev,ChiSqrt_input.upstream.Chisqrt_Z_RCut);
      h2_NearestWall_Regions[1]->Fill(mean,               stddev,ChiSqrt_input.upstream.Chisqrt_NearestWall);
      h2_DistanceUpstreamCap_Regions[1]->Fill(mean,       stddev,ChiSqrt_input.upstream.Chisqrt_DistancetoUpstreamCap);
      h2_DistanceDownstreamCap_Regions[1]->Fill(mean,     stddev,ChiSqrt_input.upstream.Chisqrt_DistancetoDownstreamCap);
      h2_DistanceUpstreamCap_Regions_RCut[1]->Fill(mean,  stddev,ChiSqrt_input.upstream.Chisqrt_DistancetoUpstreamCap_RCut);
      h2_DistanceDownstreamCap_Regions_RCut[1]->Fill(mean,stddev,ChiSqrt_input.upstream.Chisqrt_DistancetoDownstreamCap_RCut);


  //  std::cout<<"Inside:: Fill_TotalChiSqrts_Regions : 2"<<std::endl;

      h2_Vertex_X_Regions[2]->Fill(           mean,        stddev,ChiSqrt_input.barrel.Chisqrt_X);
      h2_Vertex_Y_Regions[2]->Fill(            mean,        stddev,ChiSqrt_input.barrel.Chisqrt_Y);
      h2_Vertex_R_Regions[2]->Fill(           mean,        stddev,ChiSqrt_input.barrel.Chisqrt_R);
      //h2_Vertex_RR_TotalRegion.Fill(mean,stddev,);
      h2_Vertex_Z_Regions[2]->Fill(           mean,       stddev,ChiSqrt_input.barrel.Chisqrt_Z);
      h2_Vertex_Z_Regions_RCut[2]->Fill(      mean,       stddev,ChiSqrt_input.barrel.Chisqrt_Z_RCut);
      h2_NearestWall_Regions[2]->Fill(        mean,       stddev,ChiSqrt_input.barrel.Chisqrt_NearestWall);
      h2_DistanceUpstreamCap_Regions[2]->Fill(mean,       stddev,ChiSqrt_input.barrel.Chisqrt_DistancetoUpstreamCap);
      h2_DistanceDownstreamCap_Regions[2]->Fill(mean,     stddev,ChiSqrt_input.barrel.Chisqrt_DistancetoDownstreamCap);
      h2_DistanceUpstreamCap_Regions_RCut[2]->Fill(mean,  stddev,ChiSqrt_input.barrel.Chisqrt_DistancetoUpstreamCap_RCut);
      h2_DistanceDownstreamCap_Regions_RCut[2]->Fill(mean,stddev,ChiSqrt_input.barrel.Chisqrt_DistancetoDownstreamCap_RCut);


//    std::cout<<"Inside:: Fill_TotalChiSqrts_Regions : 3"<<std::endl;

      h2_Vertex_X_Regions[3]->Fill(mean,                   stddev,ChiSqrt_input.downstream.Chisqrt_X);
      h2_Vertex_Y_Regions[3]->Fill(mean,                   stddev,ChiSqrt_input.downstream.Chisqrt_Y);
      h2_Vertex_R_Regions[3]->Fill(mean,                   stddev,ChiSqrt_input.downstream.Chisqrt_R);
      //h2_Vertex_RR_TotalRegion.Fill(mean,stddev,);
      h2_Vertex_Z_Regions[3]->Fill(mean,                  stddev,ChiSqrt_input.downstream.Chisqrt_Z);
      h2_Vertex_Z_Regions_RCut[3]->Fill(mean,             stddev,ChiSqrt_input.downstream.Chisqrt_Z_RCut);
      h2_NearestWall_Regions[3]->Fill(mean,               stddev,ChiSqrt_input.downstream.Chisqrt_NearestWall);
      h2_DistanceUpstreamCap_Regions[3]->Fill(mean,       stddev,ChiSqrt_input.downstream.Chisqrt_DistancetoUpstreamCap);
      h2_DistanceDownstreamCap_Regions[3]->Fill(mean,     stddev,ChiSqrt_input.downstream.Chisqrt_DistancetoDownstreamCap);
      h2_DistanceUpstreamCap_Regions_RCut[3]->Fill(mean,  stddev,ChiSqrt_input.downstream.Chisqrt_DistancetoUpstreamCap_RCut);
      h2_DistanceDownstreamCap_Regions_RCut[3]->Fill(mean,stddev,ChiSqrt_input.downstream.Chisqrt_DistancetoDownstreamCap_RCut);


    //std::cout<<"Inside:: Fill_TotalChiSqrts_Regions : 4"<<std::endl;

      h2_Vertex_X_Regions[4]->Fill(mean,                   stddev,ChiSqrt_input.concave.Chisqrt_X);
      h2_Vertex_Y_Regions[4]->Fill(mean,                   stddev,ChiSqrt_input.concave.Chisqrt_Y);
      h2_Vertex_R_Regions[4]->Fill(mean,                   stddev,ChiSqrt_input.concave.Chisqrt_R);
      //h2_Vertex_RR_TotalRegion.Fill(mean,stddev,);
      h2_Vertex_Z_Regions[4]->Fill(mean,                  stddev,ChiSqrt_input.concave.Chisqrt_Z);
      h2_Vertex_Z_Regions_RCut[4]->Fill(mean,             stddev,ChiSqrt_input.concave.Chisqrt_Z_RCut);
      h2_NearestWall_Regions[4]->Fill(mean,               stddev,ChiSqrt_input.concave.Chisqrt_NearestWall);
      h2_DistanceUpstreamCap_Regions[4]->Fill(mean,       stddev,ChiSqrt_input.concave.Chisqrt_DistancetoUpstreamCap);
      h2_DistanceDownstreamCap_Regions[4]->Fill(mean,     stddev,ChiSqrt_input.concave.Chisqrt_DistancetoDownstreamCap);
      h2_DistanceUpstreamCap_Regions_RCut[4]->Fill(mean,  stddev,ChiSqrt_input.concave.Chisqrt_DistancetoUpstreamCap_RCut);
      h2_DistanceDownstreamCap_Regions_RCut[4]->Fill(mean,stddev,ChiSqrt_input.concave.Chisqrt_DistancetoDownstreamCap_RCut);
    };


double Convolution_Tool::CalChiSqrt(Convolution_hist InputHistMap, int ind, bool isPartial, int min_bin, int max_bin ){

  //std::cout<<"inside:calc_ChiSq_SideBand"<<std::endl;
      if (!isPartial){
          min_bin = 1;
          max_bin = InputHistMap.MnvH1D_data->GetNbinsX();
      }

      if (min_bin == max_bin){
          cout<<"Wrong Range for Fit"<<endl;
          exit(EXIT_FAILURE);
      }


      double ChiSq = 0.0;

      for (int i = 1; i <= InputHistMap.MnvH1D_data->GetNbinsX(); ++i){
          // Get N(Events) in Single Bin
          double err = InputHistMap.MnvH1D_data->GetBinError(i);
          double nData = InputHistMap.MnvH1D_data->GetBinContent(i);
          if (nData == 0) continue;
          double nMC_total = InputHistMap.MnvH1D_mc_Convoluted[ind]->GetBinContent(i);

          double delta = pow((nMC_total - nData),2) / pow(err,2);
          ChiSq += delta;
        }
      return ChiSq;
  }



double Convolution_Tool::CalLogChiSqrt(Convolution_hist InputHistMap, int ind, bool isPartial , int min_bin, int max_bin){

  //std::cout<<"inside:calc_ChiSq_SideBand"<<std::endl;
      if (!isPartial){
          min_bin = 1;
          max_bin = InputHistMap.MnvH1D_data->GetNbinsX();
      }

      if (min_bin == max_bin){
          cout<<"Wrong Range for Fit"<<endl;
          exit(EXIT_FAILURE);
      }


      double ChiSq = 0.0;

      for (int i = 1; i <= InputHistMap.MnvH1D_data->GetNbinsX(); ++i){
          // Get N(Events) in Single Bin
          double err = InputHistMap.MnvH1D_data->GetBinError(i);
          double nData = InputHistMap.MnvH1D_data->GetBinContent(i);
          if (nData == 0) continue;
          double nMC_total = InputHistMap.MnvH1D_mc_Convoluted[1]->GetBinContent(i);

          double c = nData * log(nMC_total);
          double delta = 2 * (nMC_total - c);
          ChiSq += delta;
        }
      return ChiSq;
  }
*/
