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
double mean_offset_Start_vertexZ = -20; //30.0;
double mean_offset_Finish_vertexZ = 20.0; //48.0;
int mean_steps = 20; // reduced my half


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
Index3 ZeroShift{0 , 0 , 1};

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


//double Chisqrt_Top1 =  2559.93; // 99999; //2541.97;
//double Chisqrt_Top2 =  2565.15; // 99999.9; //2548.83;
//double Chisqrt_Top3 =  2568.8; // 999999.9; //2565.5;
//double Chisqrt_Top4 =  2571.83; // 9999990.9; //2584.38;
//double Chisqrt_Top5 =  2573.87; // 99999900.9; //2586.12;
//double Chisqrt_Top6 =  2578.44; // 999999009.9; //2586.56;

double Chisqrt_Top1 = 99999;
double Chisqrt_Top2 = 99999.9;
double Chisqrt_Top3 = 999999.9;
double Chisqrt_Top4 = 9999990.9;
double Chisqrt_Top5 = 99999900.9;
double Chisqrt_Top6 = 999999009.9;


Index3 Top1index{0 ,0, 0 };
Index3 Top2index{0 ,0, 0};
Index3 Top3index{0 ,0, 0 };
Index3 Top4index{0 ,0, 0};
Index3 Top5index{0 , 0 , 0};
Index3 Top6index{0 , 0 , 0};

//Index3 Top1index{14, 1 , 0};
//Index3 Top2index{15, 1 , 0};
//Index3 Top3index{14, 2 , 0};
//Index3 Top4index{13, 0 , 0};
//Index3 Top5index{14, 0 , 0};
//Index3 Top6index{16, 0 , 0};

//rank =1 ChiSqt = 2559.93index (i,j,k) = (14, 1 , 0 )
//rank =2 ChiSqt = 2565.15index (i,j,k) = (15, 1 , 0 )
//rank =3 ChiSqt = 2568.8index (i,j,k) = (14, 2 , 0 )
//rank =4 ChiSqt = 2571.83index (i,j,k) = (13, 0 , 0 )
//rank =5 ChiSqt = 2573.87index (i,j,k) = (14, 0 , 0 )
//rank =6 ChiSqt = 2578.44index (i,j,k) = (16, 0 , 0 )
//rank =1 ChiSqt = 2541.97index (i,j,k) = (15, 0 , 0 )
//rank =2 ChiSqt = 2548.83index (i,j,k) = (16, 1 , 0 )
//rank =3 ChiSqt = 2565.5index (i,j,k) = (16, 0 , 0 )
//rank =4 ChiSqt = 2584.38index (i,j,k) = (17, 2 , 0 )
//rank =5 ChiSqt = 2586.12index (i,j,k) = (17, 0 , 0 )
//rank =6 ChiSqt = 2586.56index (i,j,k) = (19, 0 , 0 )

//rank =1 ChiSqt = 2597.64index (i,j,k) = (12, 0 , 0 )
//rank =2 ChiSqt = 2599.78index (i,j,k) = (12, 1 , 0 )
//rank =3 ChiSqt = 2607.85index (i,j,k) = (13, 0 , 0 )
//rank =4 ChiSqt = 2615.16index (i,j,k) = (13, 1 , 0 )
//rank =5 ChiSqt = 2620.27index (i,j,k) = (11, 2 , 0 )
//rank =6 ChiSqt = 2620.75index (i,j,k) = (14, 1 , 0 )

std::vector<double> wgt_vector;
std::vector<double> wgt_error_vector;
std::map<double , Index3> Chisqrt_Top5Map{{Chisqrt_Top1 ,Top1index},{Chisqrt_Top2 ,Top2index}, {Chisqrt_Top3 ,Top3index}, {Chisqrt_Top4 ,Top4index}, {Chisqrt_Top5 ,Top5index}, {Chisqrt_Top6 ,Top6index}};


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
Convolution_Tool_TotalPlaylist.assign_Material_XYZR_HistName();
Convolution_Tool_TotalPlaylist.assign_xAxis();
Convolution_Tool_TotalPlaylist.init_All_DataHists();
//Convolution_Tool_TotalPlaylist.init_All_RecoHists();
//Convolution_Tool_TotalPcllaylist.init_All_TRUEHists();



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
std::cout<<"~~~~~~~~~~~~~Staring to Intialize Material Plots~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
Convolution_Tool_TotalPlaylist.initFULLONLY_RECO_Convolution_Material_Regions_Hists_PlaylistCombinedMC( ZeroShift.i,  ZeroShift.j,  ZeroShift.k );
std::cout<<"~~~~~~~~~~~~~Staring to Intialize TRUE Material Plots~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
Convolution_Tool_TotalPlaylist.initFULLONLY_RECO_Convolution_Material_Regions_TRUEHists_PlaylistCombinedMC(ZeroShift.i,  ZeroShift.j,  ZeroShift.k);
std::cout<<"~~~~~~~~~~~~~Staring to Intialize non fit  Material Plots~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
Convolution_Tool_TotalPlaylist.initFULLONLY_RECO_Convolution_Material_Regions_NON_vertex_varsHists_PlaylistCombinedMC(ZeroShift.i,  ZeroShift.j,  ZeroShift.k);
std::cout<<"~~~~~~~~~~~~~ to Intialize TRUE Material Plots~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

Convolution_Tool_TotalPlaylist.Plot_regions_XYZFit_Full( 0 , 0, 0, 0, "Before Fit" );
Convolution_Tool_TotalPlaylist.Plot_regions_TRUEXYZFit_Full(0 , 0, 0, 0, "Before Fit" );
Convolution_Tool_TotalPlaylist.Plot_regions_NonFitVars_Full( 0 , 0, 0, 0, "Before Fit"  );
SetConvolutionShiftMapTool(Convolution_Tool_TotalPlaylist);
FitConvolutionTool(Convolution_Tool_TotalPlaylist, 4,
  "fitlog", "log", PDF_label,
wgt_vector, wgt_error_vector);
//std::cout<<"Filling Wgts"<< std::endl;
Convolution_Tool_TotalPlaylist.Fill_Alwgt(wgt_vector, wgt_error_vector);
//std::cout<<"ApplyFitResults"<< std::endl;
Convolution_Tool_TotalPlaylist.ApplyFitResults_toFull();
Convolution_Tool_TotalPlaylist.ApplyFitResults_toTRUEFull();
Convolution_Tool_TotalPlaylist.ApplyFitResults_tononFitVarFull();
Convolution_Tool_TotalPlaylist.CalMaterial_ChiSqrtFullAfter( ChisqrtX, ChisqrtY, ChisqrtZ, ChisqrtR);
Convolution_Tool_TotalPlaylist.Plot_regions_XYZFit_Full( 0 , 0, 1, 1, "After Fit" );
Convolution_Tool_TotalPlaylist.Plot_regions_TRUEXYZFit_Full(0 , 0, 1, 1, "After Fit" );
Convolution_Tool_TotalPlaylist.Plot_regions_NonFitVars_Full( 0 , 0, 1, 1, "After Fit"  );
std::cout<<"ChisqrtX = " << ChisqrtX << std::endl;
std::cout<<"ChisqrtY = " << ChisqrtY << std::endl;
std::cout<<"ChisqrtZ = " << ChisqrtZ << std::endl;
std::cout<<"ChisqrtR = " << ChisqrtR << std::endl;
double ZeroshiftChisqrt = ChisqrtX + ChisqrtY + ChisqrtZ;

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



if(Chisqrt_X_Y_Z < Chisqrt_Top5Map.rbegin()->first ){

Chisqrt_Top5Map.insert(std::pair<double , Index3 >(Chisqrt_X_Y_Z, input_index));

if(Chisqrt_Top5Map.size() > 6) Chisqrt_Top5Map.erase(Chisqrt_Top5Map.rbegin()->first);



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


int rank = 1;
for(auto MapIndex : Chisqrt_Top5Map){

std::cout<< "rank ="<< rank <<" ChiSqt = "<<MapIndex.first << "index (i,j,k) = (" << MapIndex.second.i << ", "<< MapIndex.second.j<< " , "<<  MapIndex.second.k <<  " ) "<< std::endl;
  rank++;
}
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
int topones = 1;
char outputFileName[1024];
double boundary1= 2342.66;
double boundary2 = 3432.46;
double boundary3 = 3688.25;
char name[1024];
char name_Fid[1024];
Chisqrt_Top5Map.insert(std::pair<double , Index3 >(ZeroshiftChisqrt, ZeroShift));

sprintf(outputFileName,"/minerva/data/users/cnguyen/Convolution_vertexRootfiles/Convolution_Full_bd1_%.2f_bd2_%.2f_bd3_%.2f.root",boundary1, boundary2, boundary3 );
std::cout<<"Making file:" << outputFileName << std::endl;
TFile *outFile = new TFile(outputFileName,"RECREATE");



for(auto MapIndex : Chisqrt_Top5Map){

  Convolution_Tool_TotalPlaylist.initFULLONLY_RECO_Convolution_Material_Regions_Hists_PlaylistCombinedMC(MapIndex.second.i, MapIndex.second.j, MapIndex.second.k );
Index3 indexinput{MapIndex.second.i, MapIndex.second.j, MapIndex.second.k} ;
double mean = ZShifts[indexinput].mean;
double stddev = ZShifts[indexinput].stddev;
Convolution_Tool_TotalPlaylist.Plot_regions_XYZFit_Full( mean  , stddev, 0, 0, "before");

std::cout<<"~~~~~~~~~~~~~Staring to Intialize TRUE Material Plots~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
Convolution_Tool_TotalPlaylist.initFULLONLY_RECO_Convolution_Material_Regions_TRUEHists_PlaylistCombinedMC(MapIndex.second.i,  MapIndex.second.j,  MapIndex.second.k);
std::cout<<"~~~~~~~~~~~~~Staring to Intialize non fit  Material Plots~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
Convolution_Tool_TotalPlaylist.initFULLONLY_RECO_Convolution_Material_Regions_NON_vertex_varsHists_PlaylistCombinedMC(MapIndex.second.i,  MapIndex.second.j,  MapIndex.second.k);
std::cout<<"~~~~~~~~~~~~~ to Intialize TRUE Material Plots~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

Convolution_Tool_TotalPlaylist.Plot_regions_TRUEXYZFit_Full(0 , 0, 0, 0, "Before Fit" );
Convolution_Tool_TotalPlaylist.Plot_regions_NonFitVars_Full( 0 , 0, 0, 0, "Before Fit"  );

std::cout<<"intializing the Fidiucal Plots"<< std::endl;
Convolution_Tool_TotalPlaylist.initFULLONLY_RECO_Convolution_Material_Regions_Hists_PlaylistCombinedMC_Fiducial(MapIndex.second.i, MapIndex.second.j, MapIndex.second.k );
std::cout<<"~~~~~~~~~~~~~Staring to Intialize TRUE Material Fiducial Hists~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
Convolution_Tool_TotalPlaylist.initFULLONLY_RECO_Convolution_Material_Regions_TRUEHists_PlaylistCombinedMC_Fiducial(MapIndex.second.i,  MapIndex.second.j,  MapIndex.second.k);
std::cout<<"~~~~~~~~~~~~~Staring to Intialize non fit  Material Fiducial Plots~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
Convolution_Tool_TotalPlaylist.initFULLONLY_RECO_Convolution_Material_Regions_NON_vertex_varsHists_PlaylistCombinedMC_Fiducial(MapIndex.second.i,  MapIndex.second.j,  MapIndex.second.k);
std::cout<<"~~~~~~~~~~~~~ to Intialize TRUE Material Fiducial Plots~~~~~~~~~~~~~~~~~~~~~"<<std::endl;


Convolution_Tool_TotalPlaylist.Plot_regions_TRUEXYZFit_Full_Fiducial(0 , 0, 0, 0, "Before Fit [Fiducial]" );
Convolution_Tool_TotalPlaylist.Plot_regions_NonFitVars_Full_Fiducial( 0 , 0, 0, 0, "Before Fit [Fiducial]"  );
Convolution_Tool_TotalPlaylist.Plot_regions_XYZFit_Full_Fiducial( mean  , stddev, 0, 0, "before [Fiducial]");






FitConvolutionTool(Convolution_Tool_TotalPlaylist, 4,
  "fitlog", "log", PDF_label,
wgt_vector, wgt_error_vector );

Convolution_Tool_TotalPlaylist.Fill_Alwgt(wgt_vector, wgt_error_vector);
Convolution_Tool_TotalPlaylist.ApplyFitResults_toFull();
Convolution_Tool_TotalPlaylist.ApplyFitResults_toTRUEFull();
Convolution_Tool_TotalPlaylist.ApplyFitResults_tononFitVarFull();

Convolution_Tool_TotalPlaylist.ApplyFitResults_toFull_Fiducial();
Convolution_Tool_TotalPlaylist.ApplyFitResults_toTRUEFull_Fiducial();
Convolution_Tool_TotalPlaylist.ApplyFitResults_tononFitVarFull_Fiducial();

Convolution_Tool_TotalPlaylist.CalMaterial_ChiSqrtFullAfter( ChisqrtX, ChisqrtY, ChisqrtZ, ChisqrtR);
double Chisqrt =  ChisqrtX + ChisqrtY + ChisqrtZ;

sprintf(name,"Full_rank_%d_i_j_k_%d_%d_%d",topones, MapIndex.second.i, MapIndex.second.j, MapIndex.second.k);
sprintf(name_Fid , "Full_rank_%d_i_j_k_%d_%d_%d_Fiducial", topones, MapIndex.second.i, MapIndex.second.j, MapIndex.second.k);

sprintf(Plot_title,  "Fit #chi^{2} =  %.1f", Chisqrt  );
std::string PLOT_string(Plot_title);
Convolution_Tool_TotalPlaylist.Plot_regions_XYZFit_Full( mean  , stddev, 1, 1, PLOT_string);
Convolution_Tool_TotalPlaylist.Plot_regions_TRUEXYZFit_Full(0 , 0, 1, 1, PLOT_string );
Convolution_Tool_TotalPlaylist.Plot_regions_NonFitVars_Full( 0 , 0, 1, 1, PLOT_string  );
std::cout<<"Trying to write files with starting name = "<< name <<std::endl;

Convolution_Tool_TotalPlaylist.Plot_regions_XYZFit_Full_Fiducial( mean  , stddev, 1, 1, PLOT_string);
Convolution_Tool_TotalPlaylist.Plot_regions_TRUEXYZFit_Full_Fiducial(0 , 0, 1, 1, PLOT_string );
Convolution_Tool_TotalPlaylist.Plot_regions_NonFitVars_Full_Fiducial( 0 , 0, 1, 1, PLOT_string  );

Convolution_Tool_TotalPlaylist.Write_Full_init_and_wgted(*outFile,  name);
Convolution_Tool_TotalPlaylist.Write_Full_init_and_wgted_Fiducial(*outFile,  name_Fid);

wgt_error_vector.clear();
wgt_vector.clear();
Convolution_Tool_TotalPlaylist.Clear_Al_wgt();
topones++;
}




outFile->Close();



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
