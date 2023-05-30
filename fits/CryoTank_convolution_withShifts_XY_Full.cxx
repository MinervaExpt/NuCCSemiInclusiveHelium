#include "CryoTank_convolution_withShifts.h"

///Gobal Varibles
//Global histograms because TMinuit needs them global...
//Blob plots
//const int nHistos =7;
//TH1D h_Full[nHistos];//contains ALL the categorizations, including data
//TH1D h_Empty[nHistos];//contains ALL the categorizations, including data

void Kin(bool &cutsOn, bool &my_norm, bool &my_debug, int &Print_Systematics ) {
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


 std::ofstream outputTxtfile; // out file stream
 outputTxtfile.open("FIT_XY_Full_run3_new.txt");
//time_t now = time(0);
//tm *ltm = localtime(&now);
//char timeset[2024];
//char timeset_nonstacks[2024];
//std::string SysError_printLabel = PrintLabel_Systematics(Print_Systematics);
//auto Playlist_names =  MakePlaylistString(kMEPlayList_Vector);
//sprintf(timeset_nonstacks,"%i_%i_%i_%i_%s_%s", 1 + ltm->tm_mon,ltm->tm_mday, ltm->tm_hour,ltm->tm_min, SysError_printLabel.c_str(), Playlist_names.c_str());
//sprintf(timeset, "%i_%i_%i_%i", 1 + ltm->tm_mon,ltm->tm_mday, ltm->tm_hour,ltm->tm_min);

sprintf(text_title_pdf1, "Plots_Convolution_XY_FULL.pdf(" );
can -> Print(text_title_pdf1);
sprintf(text_title_pdf2, "Plots_Convolution_XY_FULL.pdf" );
sprintf(text_title_pdf3, "Plots_Convolution_XY_FULL.pdf)" );
sprintf(text_title_pdf4, "Plots_Convolution_XY_FULL" );
std::string PDF_label(text_title_pdf4);
std::string PDF_label_input(text_title_pdf2);

sprintf(chisqrt_title_pdf1, "Plots_Convolution_shiftsXY_ChiSqrt_Fullsearch.pdf(" );
can -> Print(chisqrt_title_pdf1);
sprintf(chisqrt_title_pdf2, "Plots_Convolution_shiftsXY_ChiSqrt_Fullsearch.pdf" );
sprintf(chisqrt_title_pdf3, "Plots_Convolution_shiftsXY_ChiSqrt_Fullsearch.pdf)" );
sprintf(chisqrt_title_pdf4, "Plots_Convolution_shiftsXY_ChiSqrt_Fullsearch" );


ME_playlist_RootPathMAP MAP_RootPath_Empty_MC;
ME_playlist_RootPathMAP MAP_RootPath_OtherEmpty_MC;
ME_playlist_RootPathMAP MAP_RootPath_Full_MC;

ME_playlist_RootPathMAP MAP_RootPath_Empty_DATA;
ME_playlist_RootPathMAP MAP_RootPath_Full_DATA;
//
//std::vector<StackType> StackType_vector;
//
//StackType_vector.push_back(kMaterial );
//StackType_vector.push_back(kInteraction);
//StackType_vector.push_back(kParticle);

/////////////////
/// MC
/////////////////
// Empty Playlist
/////////////////

auto PlaylistME_1G_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1G_MC_StatsONLYErrors_ConvolutionXY_noShift_noWgts.root";
auto PlaylistME_1A_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1A_MC_StatsONLYErrors_ConvolutionXY_noShift_noWgts.root";
auto PlaylistME_1L_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1L_MC_StatsONLYErrors_ConvolutionXY_noShift_noWgts.root";
auto PlaylistME_1M_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1M_MC_StatsONLYErrors_ConvolutionXY_noShift_noWgts.root";
auto PlaylistME_1N_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1N_MC_StatsONLYErrors_ConvolutionXY_noShift_noWgts.root";
MAP_RootPath_Empty_MC.insert(std::make_pair(kMEPlayList_Vector.at(0), PlaylistME_1G_MC_path));
MAP_RootPath_Empty_MC.insert(std::make_pair(kMEPlayList_Vector.at(1), PlaylistME_1A_MC_path));
MAP_RootPath_Empty_MC.insert(std::make_pair(kMEPlayList_Vector.at(2), PlaylistME_1L_MC_path));
MAP_RootPath_Empty_MC.insert(std::make_pair(kMEPlayList_Vector.at(3), PlaylistME_1M_MC_path));
MAP_RootPath_Empty_MC.insert(std::make_pair(kMEPlayList_Vector.at(4), PlaylistME_1N_MC_path));

////////////////////////////////////////////////////////////////////////////////
//Full
////////////////////////////////////////////////////////////////////////////////

auto PlaylistME_1P_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1P_MC_StatsONLYErrors_ConvolutionXY_noShift_noWgts.root";
auto PlaylistME_1C_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1C_MC_StatsONLYErrors_ConvolutionXY_noShift_noWgts.root";
auto PlaylistME_1D_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1D_MC_StatsONLYErrors_ConvolutionXY_noShift_noWgts.root";
auto PlaylistME_1F_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1F_MC_StatsONLYErrors_ConvolutionXY_noShift_noWgts.root";
auto PlaylistME_1E_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1E_MC_StatsONLYErrors_ConvolutionXY_noShift_noWgts.root";

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

//.NormalParaFit_Map ZShifts;


  double stddev_Start_X = 35.0; //30.0;
  double stddev_Finish_X = 75.0; //48.0;
  int stddev_NSteps_X = 10;
  double mean_Start_X = -20; //30.0;
  double mean_Finish_X = 0; //48.0;
  int mean_NSteps_X = 5; // reduced my half


  double stddev_Start_Y = 50.0; //30.0;
  double stddev_Finish_Y = 70.0; //48.0;
  int stddev_NSteps_Y = 5;
  double mean_Start_Y = 40; //30.0;
  double mean_Finish_Y = 60.0; //48.0;
  int mean_NSteps_Y = 5; // reduced my half

/// Combined parameter space
  double stddev_Start_Combined = 28.0; //30.0;
  double stddev_Finish_Combined = 80.0; //30.0;
    int stddev_NSteps_Combined = 13;
  double mean_Start_Combined = -32; //30.0;
  double mean_Finish_Combined = 60; //48.0;
  int mean_NSteps_Combined = 23;




  //FillConvolutionShiftMap(ZShifts, stddev_offset_Start_vertexZ, stddev_offset_Finish_vertexZ,
  //  stddev_steps, mean_offset_Start_vertexZ, mean_offset_Finish_vertexZ, mean_steps, true); // 1D

  NormalParaFit_XYMap XYShiftMap; // Filling Convolution parameters 2D
    FillConvolutionShiftMapXY(XYShiftMap,
            stddev_Start_X,  stddev_Finish_X,
            stddev_NSteps_X, mean_Start_X,
            mean_Finish_X,   mean_NSteps_X,
            stddev_Start_Y,  stddev_Finish_Y,
            stddev_NSteps_Y, mean_Start_Y,
            mean_Finish_Y,   mean_NSteps_Y,
           true);


//int NBinZ =NumZSteps;
std::vector<double> stddev_X_Vector = MakeBinVector(stddev_NSteps_X, stddev_Start_X, stddev_Finish_X); // i
std::vector<double> mean_X_Vector = MakeBinVector(mean_NSteps_X, mean_Start_X, mean_Finish_X); // j

std::vector<double> stddev_Y_Vector = MakeBinVector(stddev_NSteps_Y, stddev_Start_Y, stddev_Finish_Y); // k
std::vector<double> mean_Y_Vector = MakeBinVector(mean_NSteps_Y, mean_Start_Y, mean_Finish_Y); // m

Index4 zeroConvolution{mean_X_Vector.size(),stddev_X_Vector.size(),stddev_Y_Vector.size(),mean_Y_Vector.size()};

std::vector<double> stddev_Combined_Vector = MakeBinVector(stddev_NSteps_Combined, stddev_Start_Combined, stddev_Finish_Combined); // k
std::vector<double> mean_Combined_Vector = MakeBinVector(mean_NSteps_Combined, mean_Start_Combined, mean_Finish_Combined); // m

//BinMap XFit_binMap;// =  ConstuctBinMapNormal_Fit_Parameters(mean_X_Vector ,stddev_X_Vector );
//BinMap YFit_binMap; //= ConstuctBinMapNormal_Fit_Parameters(mean_Y_Vector ,stddev_Y_Vector );
//BinMap CombinedFit_binMap;// = ConstuctBinMapNormal_Fit_Parameters(mean_Combined_Vector ,stddev_Combined_Vector );


//ConstuctBinMapNormal_Fit_Parameters(XFit_binMap,mean_X_Vector ,stddev_X_Vector );
//ConstuctBinMapNormal_Fit_Parameters(XFit_binMap,mean_Y_Vector ,stddev_Y_Vector );
//ConstuctBinMapNormal_Fit_Parameters(CombinedFit_binMap,mean_Combined_Vector ,stddev_Combined_Vector );



int mapcount=0;
typename std::map<Index4, Normal_Fit_ParametersXY>::const_iterator dog;
/*
MnvH2D *h_VertexXFit   =  new MnvH2D("h_VertexXFit", "h_VertexXFit", mean_X_Vector.size()-1, mean_X_Vector.data(),stddev_X_Vector.size()-1, stddev_X_Vector.data()  );
MnvH2D *h_VertexYFit   = new MnvH2D("h_VertexYFit", "h_VertexYFit", mean_Y_Vector.size()-1, mean_Y_Vector.data(),stddev_Y_Vector.size()-1, stddev_Y_Vector.data()  );
MnvH2D *h_VertexFit_combinedSpace = new MnvH2D("h_VertexFit_combinedSpace", "h_VertexFit_combinedSpace", mean_Combined_Vector.size()-1, mean_Combined_Vector.data(),stddev_Combined_Vector.size()-1, stddev_Combined_Vector.data()  ); ;

MnvH2D *h_VertexXFit_error   =  new MnvH2D("h_VertexXFit_error", "h_VertexXFit_error", mean_X_Vector.size()-1, mean_X_Vector.data(),stddev_X_Vector.size()-1, stddev_X_Vector.data()  );
MnvH2D *h_VertexYFit_error   = new MnvH2D("h_VertexYFit_error", "h_VertexYFit_error", mean_Y_Vector.size()-1, mean_Y_Vector.data(),stddev_Y_Vector.size()-1, stddev_Y_Vector.data()  );
MnvH2D *h_VertexFit_combinedSpace_error = new MnvH2D("h_VertexFit_combinedSpace_error", "h_VertexFit_combinedSpace_error", mean_Combined_Vector.size()-1, mean_Combined_Vector.data(),stddev_Combined_Vector.size()-1, stddev_Combined_Vector.data()  ); ;





MnvH2D *h_Wgts_Xupstream =  new MnvH2D("h_Wgts_Xupstream", "h_Wgts_Xupstream", mean_X_Vector.size()-1, mean_X_Vector.data(),stddev_X_Vector.size()-1, stddev_X_Vector.data()  );
MnvH2D *h_Wgts_XBarrel=  new MnvH2D("h_Wgts_XBarrel", "h_Wgts_XBarrel", mean_X_Vector.size()-1, mean_X_Vector.data(),stddev_X_Vector.size()-1, stddev_X_Vector.data()  );
MnvH2D *h_Wgts_Xdownstream =  new MnvH2D("h_Wgts_Xdownstream", "h_Wgts_Xdownstream", mean_X_Vector.size()-1, mean_X_Vector.data(),stddev_X_Vector.size()-1, stddev_X_Vector.data()  );
MnvH2D *h_Wgts_Xconcave  =  new MnvH2D("h_Wgts_Xconcave", "h_Wgts_Xconcave", mean_X_Vector.size()-1, mean_X_Vector.data(),stddev_X_Vector.size()-1, stddev_X_Vector.data()  );

MnvH2D *h_Wgts_Yupstream = new MnvH2D("h_Wgts_Yupstream", "h_Wgts_Yupstream", mean_Y_Vector.size()-1, mean_Y_Vector.data(),stddev_Y_Vector.size()-1, stddev_Y_Vector.data()  );
MnvH2D *h_Wgts_YBarrel = new MnvH2D("h_Wgts_YBarrel", "h_Wgts_YBarrel", mean_Y_Vector.size()-1, mean_Y_Vector.data(),stddev_Y_Vector.size()-1, stddev_Y_Vector.data()  );
MnvH2D *h_Wgts_Ydownstream = new MnvH2D("h_Wgts_Ydownstream", "h_Wgts_Ydownstream", mean_Y_Vector.size()-1, mean_Y_Vector.data(),stddev_Y_Vector.size()-1, stddev_Y_Vector.data()  );
MnvH2D *h_Wgts_Yconcave = new MnvH2D("h_Wgts_Yconcave", "h_Wgts_Yconcave", mean_Y_Vector.size()-1, mean_Y_Vector.data(),stddev_Y_Vector.size()-1, stddev_Y_Vector.data()  );

MnvH2D *h_Wgts_combinedSpaceupstream = new MnvH2D("h_Wgts_combinedSpaceupstream", "h_Wgts_combinedSpaceupstream", mean_Combined_Vector.size()-1, mean_Combined_Vector.data(),stddev_Combined_Vector.size()-1, stddev_Combined_Vector.data()  );
MnvH2D *h_Wgts_combinedSpaceBarrel = new MnvH2D("h_Wgts_combinedSpaceBarrel", "h_Wgts_combinedSpaceBarrel", mean_Combined_Vector.size()-1, mean_Combined_Vector.data(),stddev_Combined_Vector.size()-1, stddev_Combined_Vector.data()  );
MnvH2D *h_Wgts_combinedSpacedownstream = new MnvH2D("h_Wgts_combinedSpacedownstream", "h_Wgts_combinedSpacedownstream", mean_Combined_Vector.size()-1, mean_Combined_Vector.data(),stddev_Combined_Vector.size()-1, stddev_Combined_Vector.data()  );
MnvH2D *h_Wgts_combinedSpaceconcave = new MnvH2D("h_Wgts_combinedSpaceconcave", "h_Wgts_combinedSpaceconcave", mean_Combined_Vector.size()-1, mean_Combined_Vector.data(),stddev_Combined_Vector.size()-1, stddev_Combined_Vector.data()  );

MnvH2D *h_Wgts_Xupstream_Error =  new MnvH2D("h_Wgts_Xupstream_Error", "h_Wgts_Xupstream_Error", mean_X_Vector.size()-1, mean_X_Vector.data(),stddev_X_Vector.size()-1, stddev_X_Vector.data()  );
MnvH2D *h_Wgts_XBarrel_Error=  new MnvH2D("h_Wgts_XBarrel_Error", "h_Wgts_XBarrel_Error", mean_X_Vector.size()-1, mean_X_Vector.data(),stddev_X_Vector.size()-1, stddev_X_Vector.data()  );
MnvH2D *h_Wgts_Xdownstream_Error =  new MnvH2D("h_Wgts_Xdownstream", "h_Wgts_Xdownstream_Error", mean_X_Vector.size()-1, mean_X_Vector.data(),stddev_X_Vector.size()-1, stddev_X_Vector.data()  );
MnvH2D *h_Wgts_Xconcave_Error  =  new MnvH2D("h_Wgts_Xconcave_Error", "h_Wgts_Xconcave_Error", mean_X_Vector.size()-1, mean_X_Vector.data(),stddev_X_Vector.size()-1, stddev_X_Vector.data()  );

MnvH2D *h_Wgts_Yupstream_Error = new MnvH2D("h_Wgts_Yupstream_Error", "h_Wgts_Yupstream_Error", mean_Y_Vector.size()-1, mean_Y_Vector.data(),stddev_Y_Vector.size()-1, stddev_Y_Vector.data()  );
MnvH2D *h_Wgts_YBarrel_Error = new MnvH2D("h_Wgts_YBarrel_Error", "h_Wgts_YBarrel_Error", mean_Y_Vector.size()-1, mean_Y_Vector.data(),stddev_Y_Vector.size()-1, stddev_Y_Vector.data()  );
MnvH2D *h_Wgts_Ydownstream_Error = new MnvH2D("h_Wgts_Ydownstream_Error", "h_Wgts_Ydownstream_Error", mean_Y_Vector.size()-1, mean_Y_Vector.data(),stddev_Y_Vector.size()-1, stddev_Y_Vector.data()  );
MnvH2D *h_Wgts_Yconcave_Error = new MnvH2D("h_Wgts_Yconcave_Error", "h_Wgts_Yconcave_Error", mean_Y_Vector.size()-1, mean_Y_Vector.data(),stddev_Y_Vector.size()-1, stddev_Y_Vector.data()  );

MnvH2D *h_Wgts_combinedSpaceupstream_Error = new MnvH2D("h_Wgts_combinedSpaceupstream_Error", "h_Wgts_combinedSpaceupstream_Error", mean_Combined_Vector.size()-1, mean_Combined_Vector.data(),stddev_Combined_Vector.size()-1, stddev_Combined_Vector.data()  );
MnvH2D *h_Wgts_combinedSpaceBarrel_Error = new MnvH2D("h_Wgts_combinedSpaceBarrel_Error", "h_Wgts_combinedSpaceBarrel_Error", mean_Combined_Vector.size()-1, mean_Combined_Vector.data(),stddev_Combined_Vector.size()-1, stddev_Combined_Vector.data()  );
MnvH2D *h_Wgts_combinedSpacedownstream_Error = new MnvH2D("h_Wgts_combinedSpacedownstream_Error", "h_Wgts_combinedSpacedownstream_Error", mean_Combined_Vector.size()-1, mean_Combined_Vector.data(),stddev_Combined_Vector.size()-1, stddev_Combined_Vector.data()  );
MnvH2D *h_Wgts_combinedSpaceconcave_Error = new MnvH2D("h_Wgts_combinedSpaceconcave_Error", "h_Wgts_combinedSpaceconcave_Error", mean_Combined_Vector.size()-1, mean_Combined_Vector.data(),stddev_Combined_Vector.size()-1, stddev_Combined_Vector.data()  );
*/

//std::cout<<"XFit_binMap.size() = "<< XFit_binMap.size()<<std::endl;

/*
for(auto cat : XFit_binMap){

std::cout<< " bin (i,j) = (" <<cat.second.i << " ,"<<cat.second.j << ") "<<std::endl;
std::cout<< " bin (mean,stddev) = (" <<cat.first.mean << " ,"<<cat.first.stddev << ") "<<std::endl;

double binedgeX = h_VertexXFit->GetXaxis()->GetBinLowEdge(cat.second.i);
double binedgeY = h_VertexXFit->GetYaxis()->GetBinLowEdge(cat.second.j);

std::cout<<" binedge  from hist (mean,stddev) = ("<< binedgeX <<", "<< binedgeY<< ")"<<std::endl;
std::cout<<""<<std::endl;


}

*/

//FitHistName_Map HistName_Map;
//Index4 ZeroShift{stddev_X_Vector.size(),mean_X_Vector.size(),stddev_Y_Vector.size(),mean_Y_Vector.size()};

//std::vector<double> Chi_sqrt_zeroshift_before;
//std::vector<double> Chi_sqrt_zeroshift_after;
//
//const int N_Hists = 5;
/*
MnvH2D *h_Chisqrt_X_Truth_todata_Full[N_Hists];  // 0 total 1 upstream cap , 2 barrel , 3 downstream, 4 downstreamconcave
MnvH2D *h_Chisqrt_Y_Truth_todata_Full[N_Hists];
MnvH2D *h_Chisqrt_Z_Truth_todata_Full[N_Hists];
//MnvH2D *h_Chisqrt_Z_Truth_todata_Full_RCut[N_Hists];
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

*/

std::string x_offset_string;
std::string y_offset_string;
std::string z_offset_string;
std::string title_string;



double bins_X = 12;
double bins_Y = 12;
double bins_Z = 13;
double bins_R = 15;

double npars = 4;



//std::vector<std::string> histNames;
//std::vector<Fit_Parms_Names> FitParms;
//h_Data_CryoVertex_X
//h_Data_CryoVertex_Y
//h_Data_CryoVertex_Z
//h_Data_CryoVertex_R
//h_CryoVertex_X
//h_CryoVertex_Y
//h_CryoVertex_Z
//h_CryoVertex_R,
//histNames.push_back("h_Data_CryoVertex_R");FitParms.push_back(kh_Name_Data_fitTo);
//histNames.push_back("h_CryoVertex_R");FitParms.push_back(kh_Name_MC_fitting);
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




//ChiSqrt_results Best_ChiSqrt_Result_Full{9999.0, 9999.0, 9999.0, 9999.0, 9999.0, 9999.0, 9999.0, 9999.0, 9999.0, 9999.0};
//ChiSqrt_results Best_ChiSqrt_Result_Empty{9999.0, 9999.0, 9999.0, 9999.0, 9999.0, 9999.0, 9999.0, 9999.0, 9999.0, 9999.0};
//ChiSqrt_results Best_ChiSqrt_Result_Full_Empty{9999.0, 9999.0, 9999.0, 9999.0, 9999.0, 9999.0, 9999.0, 9999.0, 9999.0, 9999.0};
//
//
//BestIndex Bestindex_ChiSqrt_Full{{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
//BestIndex Bestindex_ChiSqrt_Empty{{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
//BestIndex Bestindex_ChiSqrt_Full_Empty{{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};

Best4IndexFit Best_4indexFitMap_FUll  = init_defaultBest4IndexFit();
Best4IndexFit Best_4indexFitMap_Empty = init_defaultBest4IndexFit();

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~Looping throuh vertex Z~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

 mapcount = 0;
//std::string title_name;
//std::stringstream stream;
std::cout<<"Finished Loop "<<std::endl;
std::vector<double> wgt_vector;
std::vector<double> wgt_error_vector;
std::cout<<"about to apply Fit"<<std::endl;
double Chisqrt_error = 99;
double Chisqrt = 99;
double Chisqrt_X_Y_Z = 99;
double ChisqrtR_Z = 99;

double ChisqrtX = 9999;
double ChisqrtY = 9999;
double ChisqrtZ = 9999;
double ChisqrtR = 9999;

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



Convolution_Tool_TotalPlaylist.input_pdfLabel(PDF_label);
Convolution_Tool_TotalPlaylist.assign_CryoVertex_type();
Convolution_Tool_TotalPlaylist.assign_RegionsHist_RecoandTRUEName();
Convolution_Tool_TotalPlaylist.assign_CryoVertexTotalRegion_ConvolutedTRUEHistName();
Convolution_Tool_TotalPlaylist.assign_RegionsHist_dataName();
Convolution_Tool_TotalPlaylist.assign_Material_XYZR_HistName();
Convolution_Tool_TotalPlaylist.Intialize_dataHistNames();
Convolution_Tool_TotalPlaylist.init_NuMEPlaylist_POT();
Convolution_Tool_TotalPlaylist.PrintPOT();
//Convolution_Tool_TotalPlaylist.init_All_DataHists();
Convolution_Tool_TotalPlaylist.init_All_DataFullHists();

//Convolution_Tool_TotalPlaylist.init_All_RecoHists();
//Convolution_Tool_TotalPlaylist.init_All_TRUEHists();
//Convolution_Tool_TotalPlaylist.assign_xAxis();
//Convolution_Tool_TotalPlaylist.init_ZeroShift_RECO_Convolution_Regions_Hists_PlaylistCombinedMC();
Convolution_Tool_TotalPlaylist.initFULLONLY_RECO_Convolution_Material_Regions_Hists_PlaylistCombinedMC(zeroConvolution.i, zeroConvolution.j, zeroConvolution.k, zeroConvolution.m  );
std::cout<<"Starting to Plot"<<std::endl;
//Convolution_Tool_TotalPlaylist.Plot_Full_ConvolRECO(0.0, 0.0);
//Convolution_Tool_TotalPlaylist.Plot_EventDistrubution_FITRegionsOnly_ConvolRECO_Empty(0.0, 0.0);
Normal_Fit_ParametersXY xyMape{{kX,{0.0,0.0}},{kY,{0.0,0.0}}};
std::cout<<"Starting to Fit"<<std::endl;
Convolution_Tool_TotalPlaylist.Plot_regions_XYFit_Full( xyMape , 0, 0, "test" );
SetConvolutionShiftMapTool(Convolution_Tool_TotalPlaylist);
FitConvolutionTool(Convolution_Tool_TotalPlaylist, 4,
  "fitlog", "log", PDF_label,
wgt_vector, wgt_error_vector );

std::cout<<"Finished fit"<<std::endl;
Convolution_Tool_TotalPlaylist.Fill_Alwgt(wgt_vector, wgt_error_vector);
std::cout<<"Applying Wgts"<<std::endl;
Convolution_Tool_TotalPlaylist.ApplyFitResults_toFull();
Convolution_Tool_TotalPlaylist.CalMaterial_ChiSqrtFullAfter( ChisqrtX, ChisqrtY, ChisqrtZ, ChisqrtR);
std::cout<<"plotting init"<<std::endl;
std::cout<<"plotting fit"<<std::endl;
std::cout<<"print ChiSqrt ChisqrtX = " << ChisqrtX<< " ChisqrtY ="<< ChisqrtY<<  "ChisqrtZ =" <<ChisqrtZ <<  "ChisqrtR =" << ChisqrtR<<  std::endl;
//Convolution_Tool_TotalPlaylist.Plot_regions_XYFit_Empty( xyMape , 1, 1, "fit" );
wgt_error_vector.clear();
wgt_vector.clear();

Convolution_Tool_TotalPlaylist.Clear_Al_wgt();

////////////////////////
///// EMPTY
///////////////////////
double Chisqrt_Top1 = 3117.62;
double Chisqrt_Top2 = 3130.82;
double Chisqrt_Top3 = 3131.62;
double Chisqrt_Top4 = 3131.69;
double Chisqrt_Top5 = 3132.74;
Index4 Top1index{2 ,3, 2, 2 };
Index4 Top2index{2 ,4, 3, 4};
Index4 Top3index{1 ,1, 3, 1 };
Index4 Top4index{1 ,4, 2, 2};
Index4 Top5index{3 ,2, 3, 0 };

double Chisqrt_Top1R = 2969.2 ;
double Chisqrt_Top2R = 2970.04;
double Chisqrt_Top3R = 2978.6;
double Chisqrt_Top4R = 2978.63;
double Chisqrt_Top5R = 2978.87;
Index4 Top1indexR{2 ,0, 4, 0};
Index4 Top2indexR{3 ,0, 4, 0 };
Index4 Top3indexR{3 ,0, 5, 0 };
Index4 Top4indexR{3 ,1, 5, 0 };
Index4 Top5indexR{1 ,1, 3, 0};
////////////
//FUll
////////////

double FullChisqrt_Top1 = 6762.89;
double FullChisqrt_Top2 = 6764.22;
double FullChisqrt_Top3 = 6765.17;
double FullChisqrt_Top4 = 6765.5;
double FullChisqrt_Top5 = 6765.61;
Index4 FullTop1index{2 ,5, 2, 1 };
Index4 FullTop2index{0 ,6, 1, 0};
Index4 FullTop3index{2 ,5, 5, 3 };
Index4 FullTop4index{1 ,6, 4, 2};
Index4 FullTop5index{0 ,6, 2, 0};

double FullChisqrt_Top1R = 6610.91;
double FullChisqrt_Top2R = 6612.72;
double FullChisqrt_Top3R = 6613.45 ;
double FullChisqrt_Top4R = 6615.46;
double FullChisqrt_Top5R = 6616.24;
Index4 FullTop1indexR{0 ,0, 5, 0};
Index4 FullTop2indexR{3 ,1, 5, 0 };
Index4 FullTop3indexR{1 ,0, 5, 0  };
Index4 FullTop4indexR{1 ,1, 5, 0};
Index4 FullTop5indexR{1 ,2, 5, 0};

std::map<double , Index4> FullChisqrtMap{{FullChisqrt_Top1 ,FullTop1index},{FullChisqrt_Top2 ,FullTop2index}, {FullChisqrt_Top3 ,FullTop3index}, {FullChisqrt_Top4 ,FullTop4index}, {FullChisqrt_Top5 ,FullTop5index}};
std::map<double , Index4> FullChisqrtMapR{{FullChisqrt_Top1R ,FullTop1indexR},{FullChisqrt_Top2R ,FullTop2indexR}, {FullChisqrt_Top3R ,FullTop3indexR}, {FullChisqrt_Top4R ,FullTop4indexR}, {FullChisqrt_Top5R ,FullTop5indexR}};


//std::map<double , Index4>::iterator itEnd;


std::cout<<"XYShiftMap.size() = "<< XYShiftMap.size()<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~Starting Loop ~~~~~~~~~~~~~~~"<<std::endl;
//typename std::map<Index4, Normal_Fit_ParametersXY>::const_iterator dog;


Index4 killatIndex4{5,6,1,5};

 auto itbeing =   XYShiftMap.find(killatIndex4); // XYShiftMap.begin()
for ( dog = itbeing; dog != XYShiftMap.end();++dog)
{
  //std::cout<<" index = " << mapcount << " key (i,j,k) =  (" << dog->first.i <<" , "<< dog->first.j<< " , "<< dog->first.k  << " , "<< dog->first.m <<
  //")"<<std::endl;

  if(mapcount%10==0) std::cout << mapcount << " Steps   " << std::endl;


double meanX; double stddevX;double meanY; double stddevY;

for (auto ptr = dog->second.begin(); ptr != dog->second.end(); ptr++) {

  if(ptr->first == kX){
    meanX = ptr->second.mean;
    stddevX = ptr->second.stddev;
  }
  else if(ptr->first == kY){
    meanY = ptr->second.mean;
    stddevY = ptr->second.stddev;
  }
  else {std::cout<<" I have more keys then i should: ERROR check"<< std::endl; assert(false);}
  }

//std::cout<<"X(mean,stddev), Y(mean,stddev)  =   X(" <<meanX << ", " <<stddevY << ") , Y("<< meanY<< ", "<< stddevY<< ") "<< std::endl;
Index4 CurrentIndex{dog->first.i,  dog->first.j,  dog->first.k,  dog->first.m};

Convolution_Tool_TotalPlaylist.initFULLONLY_RECO_Convolution_Material_Regions_Hists_PlaylistCombinedMC( dog->first.i,  dog->first.j,  dog->first.k,  dog->first.m );

// FitFullorEmpty = 0  Empty
// FitFullorEmpty = 1 log Empty
// FitFullorEmpty = 5 log combined
// FitFullorEmpty = 6    combined


FitConvolutionTool(Convolution_Tool_TotalPlaylist, 4,
  "fitlog", "log", PDF_label,
wgt_vector, wgt_error_vector );

Convolution_Tool_TotalPlaylist.Fill_Alwgt(wgt_vector, wgt_error_vector);
Convolution_Tool_TotalPlaylist.ApplyFitResults_toFull();
Convolution_Tool_TotalPlaylist.CalMaterial_ChiSqrtFullAfter( ChisqrtX, ChisqrtY, ChisqrtZ, ChisqrtR);




Chisqrt_X_Y_Z = ChisqrtX + ChisqrtY + ChisqrtZ;
 ChisqrtR_Z = ChisqrtR + ChisqrtZ;
//itEnd = ChisqrtMap.find(4);


outputTxtfile<<dog->first.i <<","<<  dog->first.j<< "," << dog->first.k<< "," << dog->first.m << "," << ChisqrtX << ","<<  ChisqrtY << ","<<  ChisqrtZ << ", " << ChisqrtR<<endl;


//std::cout << " Chisqrt = " << Chisqrt << "ChisqrtMap.end()->first = " << ChisqrtMap.rbegin()->first  << std::endl;
if(Chisqrt_X_Y_Z < FullChisqrtMap.rbegin()->first ){

FullChisqrtMap.insert(std::pair<double , Index4 >(Chisqrt_X_Y_Z, CurrentIndex));


FullChisqrtMap.erase(FullChisqrtMap.rbegin()->first);


}


if( ChisqrtR_Z < FullChisqrtMapR.rbegin()->first ){

FullChisqrtMapR.insert(std::pair<double , Index4 >( ChisqrtR_Z, CurrentIndex));
FullChisqrtMapR.erase(FullChisqrtMapR.rbegin()->first);

}



if(mapcount%100==0){

std ::cout << "index = 100 current key (i,j,k,m) =  ("<<CurrentIndex.i << " ,"<< CurrentIndex.j << ", "<< CurrentIndex.k << ", "<< CurrentIndex.m<< " )"<< std::endl;


for(auto cat = FullChisqrtMap.begin(); cat != FullChisqrtMap.end();++cat){

std::cout<< "FullChisqrtMap:cat->first = " << cat->first<< " (i,j,k,m) =  ("<<cat->second.i << " ,"<< cat->second.j << ", "<< cat->second.k << ", "<< cat->second.m<< " )"<< std::endl;

}
for(auto cat = FullChisqrtMapR.begin(); cat != FullChisqrtMapR.end();++cat){

std::cout<<"FullChisqrtMapR: cat->first = " << cat->first<< " (i,j,k,m) =  ("<<cat->second.i << " ,"<< cat->second.j << ", "<< cat->second.k << ", "<< cat->second.m<< " )"<< std::endl;

}}


mapcount++;

wgt_error_vector.clear();
wgt_vector.clear();

Convolution_Tool_TotalPlaylist.Clear_Al_wgt();
}




std::cout<<"Making Plots "<<std::endl;
/*

char Plot_title[1024];
char xaxislabel[1024];
char yaxislabel[1024];

Index4 indexBest = ChisqrtMap.begin()->second;
double indexChi = ChisqrtMap.begin()->first;
double X_mean, X_stddev, Y_mean, Y_stddev;

X_mean = XYShiftMap[indexBest][kX].mean ;
X_stddev = XYShiftMap[indexBest][kX].stddev;
Y_mean = XYShiftMap[indexBest][kY].mean ;
Y_stddev = XYShiftMap[indexBest][kY].stddev;

sprintf(Plot_title, "Combined Empty Fit Vertex X Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", X_mean,
X_stddev, indexChi );
Draw2DHist(h_VertexXFit,  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

sprintf(Plot_title, "Combined Empty Fit Vertex X Min(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", Y_mean,
Y_stddev, indexChi );
Draw2DHist(h_VertexYFit,  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

sprintf(Plot_title, "Combined Empty Fit Vertex X(#mu,#sigma) = (%.2f, %.2f) and Y(#mu,#sigma) = (%.2f, %.2f) = %.2f [#chi^{2}]", X_mean,
X_stddev,Y_mean,Y_stddev, indexChi );
Draw2DHist(h_VertexFit_combinedSpace,  "mean",  "stddev", "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
*/

for(auto topFit :FullChisqrtMap){

Convolution_Tool_TotalPlaylist.initFULLONLY_RECO_Convolution_Material_Regions_Hists_PlaylistCombinedMC( topFit.second.i,  topFit.second.j,  topFit.second.k,  topFit.second.m );

Index4 bestChi_4index{topFit.second.i,  topFit.second.j,  topFit.second.k,  topFit.second.m };
double Chisqrt, Chisqrt_error;
FitConvolutionTool(Convolution_Tool_TotalPlaylist, 4,
  "fitlog", "log", PDF_label,
wgt_vector, wgt_error_vector);

Convolution_Tool_TotalPlaylist.Fill_Alwgt(wgt_vector, wgt_error_vector);
Convolution_Tool_TotalPlaylist.ApplyFitResults_toFull();
Convolution_Tool_TotalPlaylist.CalMaterial_ChiSqrtFullAfter( ChisqrtX, ChisqrtY, ChisqrtZ, ChisqrtR);
Chisqrt =  ChisqrtX + ChisqrtY + ChisqrtZ;
std::string Chisqrt_string = std::to_string(Chisqrt);
std::string Title =  "Full [Log(X+Y+Z) #chi^{2} = " + Chisqrt_string + "]";
Convolution_Tool_TotalPlaylist.Plot_regions_XYFit(Convolution_Tool_TotalPlaylist.Full , XYShiftMap[bestChi_4index] , 1, 1, Title, false, true );
Convolution_Tool_TotalPlaylist.Clear_Al_wgt();
wgt_vector.clear();
 wgt_error_vector.clear();
}

for(auto topFit :FullChisqrtMapR){


Convolution_Tool_TotalPlaylist.initFULLONLY_RECO_Convolution_Material_Regions_Hists_PlaylistCombinedMC( topFit.second.i,  topFit.second.j,  topFit.second.k,  topFit.second.m );

Index4 bestChi_4index{topFit.second.i,  topFit.second.j,  topFit.second.k,  topFit.second.m };
double Chisqrt, Chisqrt_error;
FitConvolutionTool(Convolution_Tool_TotalPlaylist, 4,
  "fitlog", "log", PDF_label,
wgt_vector, wgt_error_vector);
Convolution_Tool_TotalPlaylist.Fill_Alwgt(wgt_vector, wgt_error_vector);
Convolution_Tool_TotalPlaylist.ApplyFitResults_toFull();
Convolution_Tool_TotalPlaylist.CalMaterial_ChiSqrtFullAfter( ChisqrtX, ChisqrtY, ChisqrtZ, ChisqrtR);
Chisqrt =  ChisqrtR + ChisqrtZ;
std::string Chisqrt_string = std::to_string(Chisqrt);
std::string Title =  "Full [Log(Z+R) #chi^{2}  = " + Chisqrt_string + "]";
Convolution_Tool_TotalPlaylist.Plot_regions_XYFit(Convolution_Tool_TotalPlaylist.Full , XYShiftMap[bestChi_4index] , 1, 1, Title, false, true );
Convolution_Tool_TotalPlaylist.Clear_Al_wgt();
wgt_vector.clear();
 wgt_error_vector.clear();
}




  can -> Print(text_title_pdf3);
  can -> Print(chisqrt_title_pdf3);

delete can;

return;
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



Kin(cutsOn, my_norm, my_debug,  my_Print_Systmatics);

std::cout<<"Finished Kin"<< std::endl;

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


/*
int binX_i = XFit_binMap[{stddevX, meanX}].i;
int binX_j = XFit_binMap[{stddevX, meanX}].j;

int binY_i = YFit_binMap[{stddevY, meanY}].i;
int binY_j = YFit_binMap[{stddevY, meanY}].j;

int binY_combined_i = CombinedFit_binMap[{stddevY, meanY}].i;
int binY_combined_j = CombinedFit_binMap[{stddevY, meanY}].j;

int binX_combined_i = CombinedFit_binMap[{stddevX, meanX}].i;
int binX_combined_j = CombinedFit_binMap[{stddevX, meanX}].j;

h_VertexXFit->SetBinContent (binX_i, binX_j, Chisqrt);
h_VertexYFit->SetBinContent (binY_i, binY_j, Chisqrt);
h_VertexFit_combinedSpace->SetBinContent (binY_combined_i, binY_combined_i, Chisqrt);
h_VertexFit_combinedSpace->SetBinContent (binX_combined_i, binX_combined_i, Chisqrt);

h_VertexXFit_error->SetBinContent (binX_i, binX_j, Chisqrt_error);
h_VertexYFit_error->SetBinContent (binY_i, binY_j, Chisqrt_error);
h_VertexFit_combinedSpace_error->SetBinContent (binY_combined_i, binY_combined_i, Chisqrt_error);
h_VertexFit_combinedSpace_error->SetBinContent (binX_combined_i, binX_combined_i, Chisqrt_error);



h_Wgts_Xupstream->SetBinContent (binX_i, binX_j, wgt_vector.at(0));
h_Wgts_XBarrel->SetBinContent (binX_i, binX_j, wgt_vector.at(1));
h_Wgts_Xdownstream->SetBinContent (binX_i, binX_j, wgt_vector.at(2));
h_Wgts_Xconcave->SetBinContent (binX_i, binX_j, wgt_vector.at(3));

h_Wgts_Yupstream ->SetBinContent (binY_i, binY_j, wgt_vector.at(0));
h_Wgts_YBarrel->SetBinContent (binY_i, binY_j, wgt_vector.at(1));
h_Wgts_Ydownstream->SetBinContent (binY_i, binY_j, wgt_vector.at(2));
h_Wgts_Yconcave->SetBinContent (binY_i, binY_j, wgt_vector.at(3));

h_Wgts_combinedSpaceupstream->SetBinContent (binY_combined_i, binY_combined_i, wgt_vector.at(0));
h_Wgts_combinedSpaceBarrel->SetBinContent (binY_combined_i, binY_combined_i, wgt_vector.at(1));
h_Wgts_combinedSpacedownstream->SetBinContent (binY_combined_i, binY_combined_i, wgt_vector.at(2));
h_Wgts_combinedSpaceconcave->SetBinContent (binY_combined_i, binY_combined_i, wgt_vector.at(3));

h_Wgts_combinedSpaceupstream->SetBinContent (binX_combined_i, binX_combined_i, wgt_vector.at(0));
h_Wgts_combinedSpaceBarrel->SetBinContent (binX_combined_i, binX_combined_i, wgt_vector.at(1));
h_Wgts_combinedSpacedownstream->SetBinContent (binX_combined_i, binX_combined_i, wgt_vector.at(2));
h_Wgts_combinedSpaceconcave->SetBinContent (binX_combined_i, binX_combined_i, wgt_vector.at(3));
/////

h_Wgts_Xupstream->SetBinContent (binX_i, binX_j, wgt_error_vector.at(0));
h_Wgts_XBarrel->SetBinContent (binX_i, binX_j, wgt_error_vector.at(1));
h_Wgts_Xdownstream->SetBinContent (binX_i, binX_j, wgt_error_vector.at(2));
h_Wgts_Xconcave->SetBinContent (binX_i, binX_j, wgt_error_vector.at(3));

h_Wgts_Yupstream ->SetBinContent (binY_i, binY_j, wgt_error_vector.at(0));
h_Wgts_YBarrel->SetBinContent (binY_i, binY_j, wgt_error_vector.at(1));
h_Wgts_Ydownstream->SetBinContent (binY_i, binY_j, wgt_error_vector.at(2));
h_Wgts_Yconcave->SetBinContent (binY_i, binY_j, wgt_error_vector.at(3));

h_Wgts_combinedSpaceupstream_Error->SetBinContent (binY_combined_i, binY_combined_i, wgt_error_vector.at(0));
h_Wgts_combinedSpaceBarrel_Error->SetBinContent (binY_combined_i, binY_combined_i, wgt_error_vector.at(1));
h_Wgts_combinedSpacedownstream_Error->SetBinContent (binY_combined_i, binY_combined_i, wgt_error_vector.at(2));
h_Wgts_combinedSpaceconcave_Error->SetBinContent (binY_combined_i, binY_combined_i, wgt_error_vector.at(3));

h_Wgts_combinedSpaceupstream_Error->SetBinContent (binX_combined_i, binX_combined_i, wgt_error_vector.at(0));
h_Wgts_combinedSpaceBarrel_Error->SetBinContent (binX_combined_i, binX_combined_i, wgt_error_vector.at(1));
h_Wgts_combinedSpacedownstream_Error->SetBinContent (binX_combined_i, binX_combined_i, wgt_error_vector.at(2));
h_Wgts_combinedSpaceconcave_Error->SetBinContent (binX_combined_i, binX_combined_i, wgt_error_vector.at(3));

TFile *outFile = new TFile("outputFitEmpty.root","RECREATE");


std::cout<<"Writing Hists"<< std::endl;

h_VertexXFit ->Write();
h_VertexYFit ->Write();
h_VertexFit_combinedSpace ->Write();
h_VertexFit_combinedSpace ->Write();
h_VertexXFit_error ->Write();
h_VertexYFit_error ->Write();
h_VertexFit_combinedSpace_error ->Write();
h_VertexFit_combinedSpace_error ->Write();
h_Wgts_Xupstream ->Write();
h_Wgts_XBarrel ->Write();
h_Wgts_Xdownstream ->Write();
h_Wgts_Xconcave ->Write();
h_Wgts_Yupstream ->Write();
h_Wgts_YBarrel ->Write();
h_Wgts_Ydownstream ->Write();
h_Wgts_Yconcave ->Write();
h_Wgts_combinedSpaceupstream ->Write();
h_Wgts_combinedSpaceBarrel ->Write();
h_Wgts_combinedSpacedownstream ->Write();
h_Wgts_combinedSpaceconcave ->Write();
h_Wgts_combinedSpaceupstream_Error->Write();
h_Wgts_combinedSpaceBarrel_Error ->Write();
h_Wgts_combinedSpacedownstream_Error ->Write();
h_Wgts_combinedSpaceconcave_Error ->Write();
h_Wgts_Xupstream ->Write();
h_Wgts_XBarrel ->Write();
h_Wgts_Xconcave ->Write();
h_Wgts_Yupstream  ->Write();
h_Wgts_YBarrel ->Write();
h_Wgts_Ydownstream ->Write();
h_Wgts_Yconcave ->Write();
outFile->Close();
*/
//std::string Total_Chi_Before;
//std::string Total_Chi_After;
