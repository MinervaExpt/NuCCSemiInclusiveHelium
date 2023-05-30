#include "CryoTank_convolution_withShifts.h"

///Gobal Varibles
//Global histograms because TMinuit needs them global...
//Blob plots
//const int nHistos =7;
//TH1D h_Full[nHistos];//contains ALL the categorizations, including data
//TH1D h_Empty[nHistos];//contains ALL the categorizations, including data
void readCSV(std::istream &input, std::vector< std::vector<double> > &output);
std::vector<Convolution_X_Y_FitResult> constuctFitVector(std::vector< std::vector<double> > input_vector_vector,   NormalParaFit_XYMap XYShiftMap);
double EllipticparaboloidFunction(Double_t *x, Double_t *par);
double FunctionAverage_Ellipticparaboloid(double Xellipse, double Yellipse,
    double maxX, double maxY, double minX, double minY, double a, double b);
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



sprintf(text_title_pdf1, "Plots_Convolution_XY_new_1.pdf(" );
can -> Print(text_title_pdf1);
sprintf(text_title_pdf2, "Plots_Convolution_XY_new_1.pdf" );
sprintf(text_title_pdf3, "Plots_Convolution_XY_new_1.pdf)" );
sprintf(text_title_pdf4, "Plots_Convolution_XY_new_1" );
std::string PDF_label(text_title_pdf4);
std::string PDF_label_input(text_title_pdf2);

sprintf(chisqrt_title_pdf1, "Plots_ConvolutionFitting.pdf(" );
can -> Print(chisqrt_title_pdf1);
sprintf(chisqrt_title_pdf2, "Plots_ConvolutionFitting.pdf" );
sprintf(chisqrt_title_pdf3, "Plots_ConvolutionFitting.pdf)" );
sprintf(chisqrt_title_pdf4, "Plots_ConvolutionFitting" );


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


for(auto cat : mean_X_Vector){std::cout<< "mean_X_Vector = " << cat<<std::endl; }
for(auto cat :stddev_X_Vector){std::cout<< "stddev_X_Vector = " << cat<<std::endl; }
for(auto cat :mean_Y_Vector){std::cout<< "mean_Y_Vector = " << cat<<std::endl; }
for(auto cat :stddev_Y_Vector){std::cout<< "stddev_Y_Vector = " << cat<<std::endl; }






//ConstuctBinMapNormal_Fit_Parameters(XFit_binMap,mean_X_Vector ,stddev_X_Vector );
//ConstuctBinMapNormal_Fit_Parameters(XFit_binMap,mean_Y_Vector ,stddev_Y_Vector );
//ConstuctBinMapNormal_Fit_Parameters(CombinedFit_binMap,mean_Combined_Vector ,stddev_Combined_Vector );



int mapcount=0;
typename std::map<Index4, Normal_Fit_ParametersXY>::const_iterator dog;




std::string x_offset_string;
std::string y_offset_string;
std::string z_offset_string;
std::string title_string;



double bins_X = 48;
double bins_Y = 48;
double bins_Z = 104;
double bins_R = 15;

double NumberDoF_X_Y_Z = bins_X*bins_Y*bins_Z - 4;

double npars = 4;


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


Best4IndexFit Best_4indexFitMap_FUll  = init_defaultBest4IndexFit();
Best4IndexFit Best_4indexFitMap_Empty = init_defaultBest4IndexFit();

std::string filename = "Fit_XY_Empty_Combined_new1.txt"; //"FIT_XY_Empty_combined.txt";
std::string filenameFull = "Fit_XY_Full_Combined_new1.txt"; // "Fit_XY_Full_combined.txt";

std::ifstream myFile(filename);
std::ifstream myFile_full(filenameFull);

std::vector< std::vector<double> > linebylineVector;
std::vector< std::vector<double> > linebylineVectorFull;
readCSV(myFile, linebylineVector);
readCSV(myFile_full, linebylineVectorFull);
int linecout = 1;
for(auto Dogoh : linebylineVector){
std::cout<< "line "<< linecout << std::endl;
for(auto pup : Dogoh){
std::cout<< pup << ", ";

}
std::cout<<""<<std::endl;
linecout++;
}

std::vector<Convolution_X_Y_FitResult> ConvolutionFit_vector = constuctFitVector(linebylineVector,   XYShiftMap);
std::vector<Convolution_X_Y_FitResult> ConvolutionFitFull_vector = constuctFitVector(linebylineVectorFull,   XYShiftMap);

std::cout<<"looking at values "<<std::endl;

for(auto cat:ConvolutionFit_vector ){
  std::cout<< "meanX = " <<cat.meanX<<std::endl;
  std::cout<< "stddevX = " <<cat.stddevX<<std::endl;
  std::cout<< "meanY = " <<cat.meanY<<std::endl;
  std::cout<< "stddevY = " <<cat.stddevY<<std::endl;
  std::cout<< "Chi_X = " <<cat.Chi_X<<std::endl;
  std::cout<< "Chi_Y = " <<cat.Chi_Y<<std::endl;
  std::cout<< "Chi_Z = " <<cat.Chi_Z<<std::endl;
  std::cout<< "Chi_R = " <<cat.Chi_R<<std::endl;



}

//MinervaUnfold::MnvResponse *Mvn_ChiFit_X   = new MinervaUnfold::MnvResponse("Mvn_ChiFit_X", "Mvn_ChiFit_X", mean_X_Vector.size()-1, mean_X_Vector.data(), stddev_X_Vector.size()-1, stddev_X_Vector.data(), mean_Y_Vector.size()-1, mean_Y_Vector.data(), stddev_Y_Vector.size()-1, stddev_Y_Vector.data());
//MinervaUnfold::MnvResponse *Mvn_ChiFit_Y   = new MinervaUnfold::MnvResponse("Mvn_ChiFit_Y", "Mvn_ChiFit_Y", mean_X_Vector.size()-1, mean_X_Vector.data(), stddev_X_Vector.size()-1, stddev_X_Vector.data(), mean_Y_Vector.size()-1, mean_Y_Vector.data(), stddev_Y_Vector.size()-1, stddev_Y_Vector.data());
//MinervaUnfold::MnvResponse *Mvn_ChiFit_R   = new MinervaUnfold::MnvResponse("Mvn_ChiFit_R", "Mvn_ChiFit_R", mean_X_Vector.size()-1, mean_X_Vector.data(), stddev_X_Vector.size()-1, stddev_X_Vector.data(), mean_Y_Vector.size()-1, mean_Y_Vector.data(), stddev_Y_Vector.size()-1, stddev_Y_Vector.data());
//
//MinervaUnfold::MnvResponse *Mvn_ChiFit_X_Y   = new MinervaUnfold::MnvResponse("Mvn_ChiFit_X_Y", "Mvn_ChiFit_X_Y",       mean_X_Vector.size()-1, mean_X_Vector.data(), stddev_X_Vector.size()-1, stddev_X_Vector.data(), mean_Y_Vector.size()-1, mean_Y_Vector.data(), stddev_Y_Vector.size()-1, stddev_Y_Vector.data());
//MinervaUnfold::MnvResponse *Mvn_ChiFit_X_Y_Z   = new MinervaUnfold::MnvResponse("Mvn_ChiFit_X_Y_Z", "Mvn_ChiFit_X_Y_Z", mean_X_Vector.size()-1, mean_X_Vector.data(), stddev_X_Vector.size()-1, stddev_X_Vector.data(), mean_Y_Vector.size()-1, mean_Y_Vector.data(), stddev_Y_Vector.size()-1, stddev_Y_Vector.data());
//MinervaUnfold::MnvResponse *Mvn_ChiFit_R_Z   = new MinervaUnfold::MnvResponse("Mvn_ChiFit_R_Z", "Mvn_ChiFit_R_Z",       mean_X_Vector.size()-1, mean_X_Vector.data(), stddev_X_Vector.size()-1, stddev_X_Vector.data(), mean_Y_Vector.size()-1, mean_Y_Vector.data(), stddev_Y_Vector.size()-1, stddev_Y_Vector.data());


MinervaUnfold::MnvResponse *Mvn_ChiFit_X     = new MinervaUnfold::MnvResponse("Mvn_ChiFit_X",     "Mvn_ChiFit_X",     mean_Y_Vector.size()-1, mean_Y_Vector.data(),stddev_Y_Vector.size()-1, stddev_Y_Vector.data(),mean_X_Vector.size()-1, mean_X_Vector.data(), stddev_X_Vector.size()-1, stddev_X_Vector.data());
MinervaUnfold::MnvResponse *Mvn_ChiFit_Y     = new MinervaUnfold::MnvResponse("Mvn_ChiFit_Y",     "Mvn_ChiFit_Y",     mean_Y_Vector.size()-1, mean_Y_Vector.data(),stddev_Y_Vector.size()-1, stddev_Y_Vector.data(),mean_X_Vector.size()-1, mean_X_Vector.data(), stddev_X_Vector.size()-1, stddev_X_Vector.data());
MinervaUnfold::MnvResponse *Mvn_ChiFit_R     = new MinervaUnfold::MnvResponse("Mvn_ChiFit_R",     "Mvn_ChiFit_R",     mean_Y_Vector.size()-1, mean_Y_Vector.data(),stddev_Y_Vector.size()-1, stddev_Y_Vector.data(),mean_X_Vector.size()-1, mean_X_Vector.data(), stddev_X_Vector.size()-1, stddev_X_Vector.data());
MinervaUnfold::MnvResponse *Mvn_ChiFit_X_Y   = new MinervaUnfold::MnvResponse("Mvn_ChiFit_X_Y",   "Mvn_ChiFit_X_Y",   mean_Y_Vector.size()-1, mean_Y_Vector.data(),stddev_Y_Vector.size()-1, stddev_Y_Vector.data(),mean_X_Vector.size()-1, mean_X_Vector.data(), stddev_X_Vector.size()-1, stddev_X_Vector.data());
MinervaUnfold::MnvResponse *Mvn_ChiFit_X_Y_Z = new MinervaUnfold::MnvResponse("Mvn_ChiFit_X_Y_Z", "Mvn_ChiFit_X_Y_Z", mean_Y_Vector.size()-1, mean_Y_Vector.data(),stddev_Y_Vector.size()-1, stddev_Y_Vector.data(),mean_X_Vector.size()-1, mean_X_Vector.data(), stddev_X_Vector.size()-1, stddev_X_Vector.data());
MinervaUnfold::MnvResponse *Mvn_ChiFit_R_Z   = new MinervaUnfold::MnvResponse("Mvn_ChiFit_R_Z",   "Mvn_ChiFit_R_Z",   mean_Y_Vector.size()-1, mean_Y_Vector.data(),stddev_Y_Vector.size()-1, stddev_Y_Vector.data(),mean_X_Vector.size()-1, mean_X_Vector.data(), stddev_X_Vector.size()-1, stddev_X_Vector.data());
MinervaUnfold::MnvResponse *Mvn_ChiFit_X_Y_Norm   = new MinervaUnfold::MnvResponse("Mvn_ChiFit_X_Y_Norm",   "Mvn_ChiFit_X_Y_Norm",   mean_Y_Vector.size()-1, mean_Y_Vector.data(),stddev_Y_Vector.size()-1, stddev_Y_Vector.data(),mean_X_Vector.size()-1, mean_X_Vector.data(), stddev_X_Vector.size()-1, stddev_X_Vector.data());



MinervaUnfold::MnvResponse *Mvn_ChiFit_Full_X     = new MinervaUnfold::MnvResponse("Mvn_ChiFit_Full_X",     "Mvn_ChiFit_Full_X",     mean_Y_Vector.size()-1, mean_Y_Vector.data(),stddev_Y_Vector.size()-1, stddev_Y_Vector.data(),mean_X_Vector.size()-1, mean_X_Vector.data(), stddev_X_Vector.size()-1, stddev_X_Vector.data());
MinervaUnfold::MnvResponse *Mvn_ChiFit_Full_Y     = new MinervaUnfold::MnvResponse("Mvn_ChiFit_Full_Y",     "Mvn_ChiFit_Full_Y",     mean_Y_Vector.size()-1, mean_Y_Vector.data(),stddev_Y_Vector.size()-1, stddev_Y_Vector.data(),mean_X_Vector.size()-1, mean_X_Vector.data(), stddev_X_Vector.size()-1, stddev_X_Vector.data());
MinervaUnfold::MnvResponse *Mvn_ChiFit_Full_R     = new MinervaUnfold::MnvResponse("Mvn_ChiFit_Full_R",     "Mvn_ChiFit_Full_R",     mean_Y_Vector.size()-1, mean_Y_Vector.data(),stddev_Y_Vector.size()-1, stddev_Y_Vector.data(),mean_X_Vector.size()-1, mean_X_Vector.data(), stddev_X_Vector.size()-1, stddev_X_Vector.data());
MinervaUnfold::MnvResponse *Mvn_ChiFit_Full_X_Y   = new MinervaUnfold::MnvResponse("Mvn_ChiFit_Full_X_Y",   "Mvn_ChiFit_Full_X_Y",   mean_Y_Vector.size()-1, mean_Y_Vector.data(),stddev_Y_Vector.size()-1, stddev_Y_Vector.data(),mean_X_Vector.size()-1, mean_X_Vector.data(), stddev_X_Vector.size()-1, stddev_X_Vector.data());
MinervaUnfold::MnvResponse *Mvn_ChiFit_Full_X_Y_Z = new MinervaUnfold::MnvResponse("Mvn_ChiFit_Full_X_Y_Z", "Mvn_ChiFit_Full_X_Y_Z", mean_Y_Vector.size()-1, mean_Y_Vector.data(),stddev_Y_Vector.size()-1, stddev_Y_Vector.data(),mean_X_Vector.size()-1, mean_X_Vector.data(), stddev_X_Vector.size()-1, stddev_X_Vector.data());
MinervaUnfold::MnvResponse *Mvn_ChiFit_Full_R_Z   = new MinervaUnfold::MnvResponse("Mvn_ChiFit_Full_R_Z",   "Mvn_ChiFit_Full_R_Z",   mean_Y_Vector.size()-1, mean_Y_Vector.data(),stddev_Y_Vector.size()-1, stddev_Y_Vector.data(),mean_X_Vector.size()-1, mean_X_Vector.data(), stddev_X_Vector.size()-1, stddev_X_Vector.data());
MinervaUnfold::MnvResponse *Mvn_ChiFit_Full_X_Y_Norm   = new MinervaUnfold::MnvResponse("Mvn_ChiFit_Full_X_Y_Norm",   "Mvn_ChiFit_Full_X_Y_Norm",   mean_Y_Vector.size()-1, mean_Y_Vector.data(),stddev_Y_Vector.size()-1, stddev_Y_Vector.data(),mean_X_Vector.size()-1, mean_X_Vector.data(), stddev_X_Vector.size()-1, stddev_X_Vector.data());



double BestChitFit[6];
double BestFit_meanX[6];
double BestFit_stddevX[6];
double BestFit_meanY[6];
double BestFit_stddevY[6];

double BestFULLChitFit[6];
double BestFitFULL_meanX[6];
double BestFitFULL_stddevX[6];
double BestFitFULL_meanY[6];
double BestFitFULL_stddevY[6];
const double Lowest_X_Y_chi_Empty = 513.373;
const double Lowest_X_Y_chi_Full = 457.79;

for(int w = 0 ; w < 6; w++){

  BestChitFit[w]=999999;
  BestFit_meanX[w]=999999;
  BestFit_stddevX[w]=999999;
  BestFit_meanY[w]=999999;
  BestFit_stddevY[w]=999999;

  BestFULLChitFit[w]=999999;
  BestFitFULL_meanX[w]=999999;
  BestFitFULL_stddevX[w]=999999;
  BestFitFULL_meanY[w]=999999;
  BestFitFULL_stddevY[w]=999999;


}

std::ofstream outfile ("Full_Chisrt_x_y.txt");



for(auto Convolution_result : ConvolutionFit_vector){

  double  meanX_value =  Convolution_result.meanX;
  double  stddevX_value =  Convolution_result.stddevX;
  double  meanY_value =  Convolution_result.meanY;
  double  stddevY_value =  Convolution_result.stddevY;
  double  Chi_X_value =  Convolution_result.Chi_X;
  double  Chi_Y_value =  Convolution_result.Chi_Y;
  double  Chi_Z_value =  Convolution_result.Chi_Z;
  double  Chi_R_value =  Convolution_result.Chi_R;
  double Combined_X_Y_chi = Chi_X_value + Chi_Y_value;
  double Combined_X_Y_Z_chi = Chi_X_value + Chi_Y_value + Chi_Z_value;
  double Combined_R_Z_chi = Chi_R_value  +  Chi_Z_value;
  double Norm_input =  (Combined_X_Y_chi - Lowest_X_Y_chi_Empty) ;




if(meanX_value==0 && stddevX_value == 0 && meanY_value ==0 && stddevY_value ==0 ) continue;

if(BestChitFit[0] > Chi_X_value ){
BestChitFit[0] = Chi_X_value;
BestFit_meanX[0] = meanX_value;
BestFit_stddevX[0] = stddevX_value;
BestFit_meanY[0] = meanY_value;
BestFit_stddevY[0] = stddevY_value;
}

if(BestChitFit[1]> Chi_Y_value ){
  BestChitFit[1] = Chi_Y_value;
  BestFit_meanX[1] = meanX_value;
  BestFit_stddevX[1] = stddevX_value;
  BestFit_meanY[1] = meanY_value;
  BestFit_stddevY[1] = stddevY_value;

}
if(BestChitFit[2]> Chi_R_value ){
  BestChitFit[2] = Chi_R_value;
  BestFit_meanX[2] = meanX_value;
  BestFit_stddevX[2] = stddevX_value;
  BestFit_meanY[2] = meanY_value;
  BestFit_stddevY[2] = stddevY_value;
}

if(BestChitFit[3]> Combined_X_Y_chi ){
  BestChitFit[3] = Combined_X_Y_chi;
  BestFit_meanX[3] = meanX_value;
  BestFit_stddevX[3] = stddevX_value;
  BestFit_meanY[3] = meanY_value;
  BestFit_stddevY[3] = stddevY_value;


}
if(BestChitFit[4]> Combined_X_Y_Z_chi ){
  BestChitFit[4] = Combined_X_Y_Z_chi;
  BestFit_meanX[4] = meanX_value;
  BestFit_stddevX[4] = stddevX_value;
  BestFit_meanY[4] = meanY_value;
  BestFit_stddevY[4] = stddevY_value;
}

if(BestChitFit[5]> Combined_R_Z_chi ){

  BestChitFit[5] = Combined_R_Z_chi;
  BestFit_meanX[5] = meanX_value;
  BestFit_stddevX[5] = stddevX_value;
  BestFit_meanY[5] = meanY_value;
  BestFit_stddevY[5] = stddevY_value;

}



Mvn_ChiFit_X->Fill( meanY_value, stddevY_value, meanX_value, stddevX_value,  Chi_X_value / NumberDoF_X_Y_Z );
Mvn_ChiFit_Y->Fill( meanY_value, stddevY_value, meanX_value, stddevX_value,  Chi_Y_value / NumberDoF_X_Y_Z);
Mvn_ChiFit_R->Fill( meanY_value, stddevY_value, meanX_value, stddevX_value,  Chi_R_value / NumberDoF_X_Y_Z );
Mvn_ChiFit_X_Y->Fill( meanY_value, stddevY_value, meanX_value, stddevX_value,  Combined_X_Y_chi / NumberDoF_X_Y_Z );
Mvn_ChiFit_X_Y_Norm->Fill( meanY_value, stddevY_value, meanX_value, stddevX_value,  Norm_input );
Mvn_ChiFit_X_Y_Z->Fill(meanY_value, stddevY_value, meanX_value, stddevX_value,  Combined_X_Y_Z_chi / NumberDoF_X_Y_Z );
Mvn_ChiFit_R_Z->Fill( meanY_value, stddevY_value, meanX_value, stddevX_value,  Combined_R_Z_chi / NumberDoF_X_Y_Z);


}


for(auto Convolution_result : ConvolutionFitFull_vector){

  double  meanX_value =  Convolution_result.meanX;
  double  stddevX_value =  Convolution_result.stddevX;
  double  meanY_value =  Convolution_result.meanY;
  double  stddevY_value =  Convolution_result.stddevY;
  double  Chi_X_value =  Convolution_result.Chi_X;
  double  Chi_Y_value =  Convolution_result.Chi_Y;
  double  Chi_Z_value =  Convolution_result.Chi_Z;
  double  Chi_R_value =  Convolution_result.Chi_R;
  double Combined_X_Y_chi = Chi_X_value + Chi_Y_value;
  double Combined_X_Y_Z_chi = Chi_X_value + Chi_Y_value + Chi_Z_value;
  double Combined_R_Z_chi = Chi_R_value  +  Chi_Z_value;
  double Norm_input =  (Combined_X_Y_chi - Lowest_X_Y_chi_Full);

  outfile << Combined_X_Y_chi << std::endl;
if(meanX_value==0 && stddevX_value == 0 && meanY_value ==0 && stddevY_value ==0 ) continue;

if(BestFULLChitFit[0] > Chi_X_value ){
BestFULLChitFit[0] = Chi_X_value;
BestFitFULL_meanX[0] = meanX_value;
BestFitFULL_stddevX[0] = stddevX_value;
BestFitFULL_meanY[0] = meanY_value;
BestFitFULL_stddevY[0] = stddevY_value;
}

if(BestFULLChitFit[1]> Chi_Y_value ){
  BestFULLChitFit[1] = Chi_Y_value;
  BestFitFULL_meanX[1] = meanX_value;
  BestFitFULL_stddevX[1] = stddevX_value;
  BestFitFULL_meanY[1] = meanY_value;
  BestFitFULL_stddevY[1] = stddevY_value;

}
if(BestFULLChitFit[2]> Chi_R_value ){
  BestFULLChitFit[2] = Chi_R_value;
  BestFitFULL_meanX[2] = meanX_value;
  BestFitFULL_stddevX[2] = stddevX_value;
  BestFitFULL_meanY[2] = meanY_value;
  BestFitFULL_stddevY[2] = stddevY_value;
}

if(BestFULLChitFit[3]> Combined_X_Y_chi ){
  BestFULLChitFit[3] = Combined_X_Y_chi;
  BestFitFULL_meanX[3] = meanX_value;
  BestFitFULL_stddevX[3] = stddevX_value;
  BestFitFULL_meanY[3] = meanY_value;
  BestFitFULL_stddevY[3] = stddevY_value;

  std::cout<< "Combined_X_Y_chi =  "<< Combined_X_Y_chi<<std::endl;
std::cout<< "Chi_X_value "<< Chi_X_value<<std::endl;
std::cout<< "Chi_Y_value "<< Chi_Y_value<<std::endl;
}
if(BestFULLChitFit[4]> Combined_X_Y_Z_chi ){
  BestFULLChitFit[4] = Combined_X_Y_Z_chi;
  BestFitFULL_meanX[4] = meanX_value;
  BestFitFULL_stddevX[4] = stddevX_value;
  BestFitFULL_meanY[4] = meanY_value;
  BestFitFULL_stddevY[4] = stddevY_value;
}

if(BestFULLChitFit[5]> Combined_R_Z_chi ){
  BestFULLChitFit[5] = Combined_R_Z_chi;
  BestFitFULL_meanX[5] = meanX_value;
  BestFitFULL_stddevX[5] = stddevX_value;
  BestFitFULL_meanY[5] = meanY_value;
  BestFitFULL_stddevY[5] = stddevY_value;

}


Mvn_ChiFit_Full_X->Fill( meanY_value, stddevY_value, meanX_value, stddevX_value,  Chi_X_value / NumberDoF_X_Y_Z );
Mvn_ChiFit_Full_Y->Fill( meanY_value, stddevY_value, meanX_value, stddevX_value,  Chi_Y_value / NumberDoF_X_Y_Z);
Mvn_ChiFit_Full_R->Fill( meanY_value, stddevY_value, meanX_value, stddevX_value,  Chi_R_value / NumberDoF_X_Y_Z );
Mvn_ChiFit_Full_X_Y->Fill( meanY_value, stddevY_value, meanX_value, stddevX_value,  Combined_X_Y_chi / NumberDoF_X_Y_Z );
Mvn_ChiFit_Full_X_Y_Z->Fill(meanY_value, stddevY_value, meanX_value, stddevX_value,  Combined_X_Y_Z_chi / NumberDoF_X_Y_Z );
Mvn_ChiFit_Full_R_Z->Fill( meanY_value, stddevY_value, meanX_value, stddevX_value,  Combined_R_Z_chi / NumberDoF_X_Y_Z);
Mvn_ChiFit_Full_X_Y_Norm->Fill( meanY_value, stddevY_value, meanX_value, stddevX_value,  Norm_input);

}



outfile.close();

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
Convolution_Tool_TotalPlaylist.init_All_DataHists();
//Convolution_Tool_TotalPlaylist.init_All_DataFullHists();

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
Convolution_Tool_TotalPlaylist.Plot_regions_XYFit_Full( xyMape , 0, 0, "Combined Full" );
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
Convolution_Tool_TotalPlaylist.Plot_regions_XYFit_Full( xyMape , 1, 1, "fit to Full Data Only " );
wgt_error_vector.clear();
wgt_vector.clear();
Convolution_Tool_TotalPlaylist.Clear_Al_wgt();
//////////////////////////////////////////////////////
Convolution_Tool_TotalPlaylist.initEMPTYONLY_RECO_Convolution_Material_Regions_Hists_PlaylistCombinedMC(zeroConvolution.i, zeroConvolution.j, zeroConvolution.k, zeroConvolution.m  );
Convolution_Tool_TotalPlaylist.initFULLONLY_RECO_Convolution_Material_Regions_Hists_PlaylistCombinedMC(zeroConvolution.i, zeroConvolution.j, zeroConvolution.k, zeroConvolution.m  );

std::cout<<"Starting to Plot"<<std::endl;
//Convolution_Tool_TotalPlaylist.Plot_Full_ConvolRECO(0.0, 0.0);
//Convolution_Tool_TotalPlaylist.Plot_EventDistrubution_FITRegionsOnly_ConvolRECO_Empty(0.0, 0.0);
std::cout<<"Starting to Fit"<<std::endl;
Convolution_Tool_TotalPlaylist.Plot_regions_XYFit_Empty( xyMape , 0, 0, "Combined Empty" );
Convolution_Tool_TotalPlaylist.Plot_regions_XYFit_Full( xyMape , 0, 0, "Combined Full" );

SetConvolutionShiftMapTool(Convolution_Tool_TotalPlaylist);
FitConvolutionTool(Convolution_Tool_TotalPlaylist, 1,
  "fitlog", "log", PDF_label,
wgt_vector, wgt_error_vector );

std::cout<<"Finished fit"<<std::endl;
Convolution_Tool_TotalPlaylist.Fill_Alwgt(wgt_vector, wgt_error_vector);
std::cout<<"Applying Wgts"<<std::endl;
Convolution_Tool_TotalPlaylist.ApplyFitResults_toEmpty();
Convolution_Tool_TotalPlaylist.CalMaterial_ChiSqrtEmptyAfter( ChisqrtX, ChisqrtY, ChisqrtZ, ChisqrtR);
std::cout<<"plotting init"<<std::endl;
std::cout<<"plotting fit"<<std::endl;
std::cout<<"print ChiSqrt ChisqrtX = " << ChisqrtX<< " ChisqrtY ="<< ChisqrtY<<  "ChisqrtZ =" <<ChisqrtZ <<  "ChisqrtR =" << ChisqrtR<<  std::endl;
Convolution_Tool_TotalPlaylist.Plot_regions_XYFit_Empty( xyMape , 1, 1, "Fit to Empty data Only" );
wgt_error_vector.clear();
wgt_vector.clear();
Convolution_Tool_TotalPlaylist.Clear_Al_wgt();

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
Convolution_Tool_TotalPlaylist.Plot_regions_XYFit_Full( xyMape , 1, 1, "Fit to Full data Only" );
wgt_error_vector.clear();
wgt_vector.clear();
Convolution_Tool_TotalPlaylist.Clear_Al_wgt();
////////////////////////
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

std::map<double , Index4> EmptyChisqrtMap{{Chisqrt_Top1 ,Top1index},{Chisqrt_Top2 ,Top2index}, {Chisqrt_Top3 ,Top3index}, {Chisqrt_Top4 ,Top4index}, {Chisqrt_Top5 ,Top5index}};
std::map<double , Index4> EmptyChisqrtMapR{{Chisqrt_Top1R ,Top1indexR},{Chisqrt_Top2R ,Top2indexR}, {Chisqrt_Top3R ,Top3indexR}, {Chisqrt_Top4R ,Top4indexR}, {Chisqrt_Top5R ,Top5indexR}};

//std::map<double , Index4>::iterator itEnd;


std::cout<<"XYShiftMap.size() = "<< XYShiftMap.size()<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~Starting Loop ~~~~~~~~~~~~~~~"<<std::endl;
//typename std::map<Index4, Normal_Fit_ParametersXY>::const_iterator dog;


//Index4 killatIndex4{3,5,2,0};

 //auto itbeing =  XYShiftMap.find(killatIndex4); // XYShiftMap.begin()
/*
for ( dog = XYShiftMap.begin(); dog != XYShiftMap.end();++dog)
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

}
*/



std::cout<<"Making Plots "<<std::endl;
for(auto topFit :EmptyChisqrtMap){


Convolution_Tool_TotalPlaylist.initEMPTYONLY_RECO_Convolution_Material_Regions_Hists_PlaylistCombinedMC( topFit.second.i,  topFit.second.j,  topFit.second.k,  topFit.second.m );

Index4 bestChi_4index{topFit.second.i,  topFit.second.j,  topFit.second.k,  topFit.second.m };
double Chisqrt, Chisqrt_error;
FitConvolutionTool(Convolution_Tool_TotalPlaylist, 1,
  "fitlog", "log", PDF_label,
wgt_vector, wgt_error_vector);

Convolution_Tool_TotalPlaylist.Fill_Alwgt(wgt_vector, wgt_error_vector);
Convolution_Tool_TotalPlaylist.ApplyFitResults_toEmpty();
Convolution_Tool_TotalPlaylist.CalMaterial_ChiSqrtEmptyAfter( ChisqrtX, ChisqrtY, ChisqrtZ, ChisqrtR);
Chisqrt =  ChisqrtX + ChisqrtY + ChisqrtZ;
std::string Chisqrt_string = std::to_string(Chisqrt);

std::string Title = "Empty [Log(X+Y+Z) #chi^{2} = " + Chisqrt_string + "]";
Convolution_Tool_TotalPlaylist.Plot_regions_XYFit(Convolution_Tool_TotalPlaylist.Empty , XYShiftMap[bestChi_4index] , 1, 1, Title, false, true );
Convolution_Tool_TotalPlaylist.Clear_Al_wgt();
wgt_vector.clear();
 wgt_error_vector.clear();
}

/*for(auto topFit :EmptyChisqrtMapR){


Convolution_Tool_TotalPlaylist.initEMPTYONLY_RECO_Convolution_Material_Regions_Hists_PlaylistCombinedMC( topFit.second.i,  topFit.second.j,  topFit.second.k,  topFit.second.m );

Index4 bestChi_4index{topFit.second.i,  topFit.second.j,  topFit.second.k,  topFit.second.m };
double Chisqrt, Chisqrt_error;
FitConvolutionTool(Convolution_Tool_TotalPlaylist, 1,
  "fitlog", "log", PDF_label,
wgt_vector, wgt_error_vector);
Convolution_Tool_TotalPlaylist.Fill_Alwgt(wgt_vector, wgt_error_vector);
Convolution_Tool_TotalPlaylist.ApplyFitResults_toEmpty();
Convolution_Tool_TotalPlaylist.CalMaterial_ChiSqrtFullAfter( ChisqrtX, ChisqrtY, ChisqrtZ, ChisqrtR);
Chisqrt =  ChisqrtR + ChisqrtZ;
std::string Chisqrt_string = std::to_string(Chisqrt);
std::string Title =  "Empty [Log(Z+R) #chi^{2}  = " + Chisqrt_string + "]";
Convolution_Tool_TotalPlaylist.Plot_regions_XYFit(Convolution_Tool_TotalPlaylist.Empty , XYShiftMap[bestChi_4index] , 1, 1, Title, false, true );
Convolution_Tool_TotalPlaylist.Clear_Al_wgt();
wgt_vector.clear();
 wgt_error_vector.clear();
}*/

std::cout<<"Making Plots "<<std::endl;
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

std::string Title = "Full [Log(X+Y+Z) #chi^{2} = " + Chisqrt_string + "]";
Convolution_Tool_TotalPlaylist.Plot_regions_XYFit(Convolution_Tool_TotalPlaylist.Full , XYShiftMap[bestChi_4index] , 1, 1, Title, false, true );
Convolution_Tool_TotalPlaylist.Clear_Al_wgt();
wgt_vector.clear();
 wgt_error_vector.clear();
}






char Plot_title[1024];
MnvH2D *migrationH = NULL;
MnvH2D *h_reco = NULL;
MnvH2D *h_truth = NULL;

bool check = Mvn_ChiFit_X->GetMigrationObjects(migrationH, h_reco, h_truth );
sprintf(Plot_title, "[4 par X vertex] Empty Fit Min X(#mu,#sigma), Y(#mu,#sigma) = (%.2f, %.2f) , (%.2f, %.2f) = %.2f [#chi^{2} /ndf]",BestFit_meanX[0] , BestFit_stddevX[0],BestFit_meanY[0] ,BestFit_stddevY[0],BestChitFit[0]  );
//Draw2DHist(migrationH,  "Mean X binning Number",  "stddev X Binning Number", "vertex X #chi^{2} ", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
Draw2DHist_MvR(migrationH,  "Mean X binning Number",  "stddev X Binning Number", "vertex X #chi^{2} ", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter, mean_X_Vector, stddev_X_Vector, mean_Y_Vector, stddev_Y_Vector, true);

 check = Mvn_ChiFit_Y->GetMigrationObjects(migrationH, h_reco, h_truth );
sprintf(Plot_title, "[4 par Y vertex] Empty Fit Min X(#mu,#sigma), Y(#mu,#sigma) = (%.2f, %.2f) , (%.2f, %.2f) = %.2f [#chi^{2} /ndf]",BestFit_meanX[1] , BestFit_stddevX[1],BestFit_meanY[1] ,BestFit_stddevY[1],BestChitFit[1]  );
Draw2DHist(migrationH,  "Mean X binning Number",  "stddev X Binning Number", "vertex Y #chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);


 check = Mvn_ChiFit_X_Y->GetMigrationObjects(migrationH, h_reco, h_truth );
sprintf(Plot_title, "[4 par X+Y vertex] Empty Fit Min X(#mu,#sigma), Y(#mu,#sigma) = (%.2f, %.2f) , (%.2f, %.2f) = %.2f [#chi^{2} /ndf]",BestFit_meanX[3] , BestFit_stddevX[3],BestFit_meanY[3] ,BestFit_stddevY[3],BestChitFit[3]  );
Draw2DHist_MvR(migrationH,  "Mean X binning Number",  "stddev X Binning Number", "vertex Y+X #chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter, mean_X_Vector, stddev_X_Vector, mean_Y_Vector, stddev_Y_Vector, false);


check = Mvn_ChiFit_X_Y_Norm->GetMigrationObjects(migrationH, h_reco, h_truth );
sprintf(Plot_title, "[X+Y vertex] Empty Fit Min X(#mu,#sigma), Y(#mu,#sigma) = (%.2f, %.2f), (%.2f, %.2f) = %.2f [#chi^{2} /ndf]",BestFit_meanX[3] , BestFit_stddevX[3],BestFit_meanY[3] ,BestFit_stddevY[3],BestChitFit[3]  );
Draw2DHist_MvR(migrationH,  "Mean X binning Number",  "stddev X Binning Number", "#chi^{2} - #chi_{BestFit}^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter, mean_X_Vector, stddev_X_Vector, mean_Y_Vector, stddev_Y_Vector, false);

 check = Mvn_ChiFit_R_Z->GetMigrationObjects(migrationH, h_reco, h_truth );
sprintf(Plot_title, "[4 par R+Z vertex] Empty Fit Min X(#mu,#sigma), Y(#mu,#sigma) = (%.2f, %.2f) , (%.2f, %.2f) = %.2f [#chi^{2} /ndf]",BestFit_meanX[5] , BestFit_stddevX[5],BestFit_meanY[5] ,BestFit_stddevY[5],BestChitFit[5]  );
Draw2DHist(migrationH,  "Mean X binning Number",  "stddev X Binning Number", "vertex R+Z #chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

 check = Mvn_ChiFit_Full_X->GetMigrationObjects(migrationH, h_reco, h_truth );
sprintf(Plot_title, "[4 par X vertex] Full Fit Min X(#mu,#sigma), Y(#mu,#sigma) = (%.2f, %.2f) , (%.2f, %.2f) = %.2f [#chi^{2} /ndf]",BestFitFULL_meanX[0] , BestFitFULL_stddevX[0],BestFitFULL_meanY[0] ,BestFitFULL_stddevY[0],BestFULLChitFit[0]  );
Draw2DHist_MvR(migrationH,  "Mean X binning Number",  "stddev X Binning Number", "vertex X #chi^{2} ", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter, mean_X_Vector, stddev_X_Vector, mean_Y_Vector, stddev_Y_Vector, false);
Draw2DHist(migrationH,  "Mean X binning Number",  "stddev X Binning Number", "vertex X #chi^{2} ", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);


 check = Mvn_ChiFit_Full_Y->GetMigrationObjects(migrationH, h_reco, h_truth );
sprintf(Plot_title, "[4 par Y vertex] Full Fit Min X(#mu,#sigma), Y(#mu,#sigma) = (%.2f, %.2f) , (%.2f, %.2f) = %.2f [#chi^{2} /ndf]",BestFitFULL_meanX[1] , BestFitFULL_stddevX[1],BestFitFULL_meanY[1] ,BestFitFULL_stddevY[1],BestFULLChitFit[1]  );
Draw2DHist(migrationH,  "Mean X binning Number",  "stddev X Binning Number", "vertex Y #chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

 check = Mvn_ChiFit_Full_X_Y->GetMigrationObjects(migrationH, h_reco, h_truth );
sprintf(Plot_title, "[4 par X+Y vertex]  Full Fit Min X(#mu,#sigma), Y(#mu,#sigma) = (%.2f, %.2f) , (%.2f, %.2f) = %.2f [#chi^{2} /ndf]",BestFitFULL_meanX[3] , BestFitFULL_stddevX[3],BestFitFULL_meanY[3] ,BestFitFULL_stddevY[3],BestFULLChitFit[3]  );
Draw2DHist_MvR(migrationH,  "Mean X binning Number",  "stddev X Binning Number", "vertex Y+X #chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter, mean_X_Vector, stddev_X_Vector, mean_Y_Vector, stddev_Y_Vector, false);

check = Mvn_ChiFit_Full_X_Y_Norm->GetMigrationObjects(migrationH, h_reco, h_truth );
sprintf(Plot_title, "[4 par X+Y vertex]  Full Fit Min X(#mu,#sigma), Y(#mu,#sigma) = (%.2f, %.2f) , (%.2f, %.2f) = %.2f [#chi^{2} /ndf]",BestFitFULL_meanX[3] , BestFitFULL_stddevX[3],BestFitFULL_meanY[3] ,BestFitFULL_stddevY[3],BestFULLChitFit[3]  );
Draw2DHist_MvR(migrationH,  "Mean X binning Number",  "stddev X Binning Number", "#chi^{2} - #chi_{BestFit}^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter, mean_X_Vector, stddev_X_Vector, mean_Y_Vector, stddev_Y_Vector, false);


check = Mvn_ChiFit_Full_X_Y_Z->GetMigrationObjects(migrationH, h_reco, h_truth );
sprintf(Plot_title, "[4 par X+Y+Z vertex] Full Fit Min X(#mu,#sigma), Y(#mu,#sigma) = (%.2f, %.2f), (%.2f, %.2f) = %.2f [#chi^{2} /ndf]",BestFitFULL_meanX[4] , BestFitFULL_stddevX[4],BestFitFULL_meanY[4] ,BestFitFULL_stddevY[4],BestFULLChitFit[4]  );
Draw2DHist_MvR(migrationH,  "Mean X binning Number",  "stddev X Binning Number", "vertex Y+X+Z #chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter, mean_X_Vector, stddev_X_Vector, mean_Y_Vector, stddev_Y_Vector,false);

 check = Mvn_ChiFit_Full_R_Z->GetMigrationObjects(migrationH, h_reco, h_truth );
sprintf(Plot_title, "[4 par R+Z vertex] Full Fit Min X(#mu,#sigma), Y(#mu,#sigma) = (%.2f, %.2f) , (%.2f, %.2f) = %.2f [#chi^{2} /ndf]",BestFitFULL_meanX[5] , BestFitFULL_stddevX[5],BestFitFULL_meanY[5] ,BestFitFULL_stddevY[5],BestFULLChitFit[5]  );
Draw2DHist(migrationH,  "Mean X binning Number",  "stddev X Binning Number", "vertex R+Z #chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);


   TFile *ShiftXYFit = new TFile("Chisqrt_fit_results_XY.root");

   PlotUtils::MnvH2D* h_Chisqrt_X_Y =  Get2DHist(*ShiftXYFit, "h_Chisqrt_X_Y_after_0" );
    TH2D *h_Chisqrt_X_Y_clone = (TH2D*)h_Chisqrt_X_Y->Clone("h_Chisqrt_X_Y_clone");


    PlotUtils::MnvH2D* h_Chisqrt_X_Y_1 =  Get2DHist(*ShiftXYFit, "h_Chisqrt_X_Y_after_1" );
     TH2D *h_Chisqrt_X_Y_clone_1 = (TH2D*)h_Chisqrt_X_Y_1->Clone("h_Chisqrt_X_Y_clone_1");


    std::vector<double> FitParas;
    std::vector<double> FitParas_error;
    Set_h1_Gobal(h_Chisqrt_X_Y_clone);
    FitMinuit_h1_Gobal_Ellipticparaboloid(FitParas, FitParas_error) ;

   double NegX_offset = -25.0;
   double PosX_offset =  25.0;
   int NumXSteps = 25;  // // steps of 4mm

   double NegY_offset = -25.0;
   double PosY_offset = 25.0;
   int NumYSteps = 25; //  // steps of 4mm



   const int Zsteps = 1;//NumZSteps+1;

   //int NBinZ =NumZSteps;
   std::vector<double> X_offsetVector = MakeBinVector(NumXSteps, NegX_offset, PosX_offset); // i
   std::vector<double> Y_offsetVector = MakeBinVector(NumYSteps, NegY_offset, PosY_offset); // j'
   MnvH2D *h_Fit   =    new MnvH2D("h_Fit", "h_Fit",  X_offsetVector.size()-1,  X_offsetVector.data(),Y_offsetVector.size()-1, Y_offsetVector.data()  );
   MnvH2D *h_Fit_reg   =    new MnvH2D("h_Fit_reg", "h_Fit_reg",  X_offsetVector.size()-1,  X_offsetVector.data(),Y_offsetVector.size()-1, Y_offsetVector.data()  );

  FillHist_Ellipticparaboloid(*h_Fit, FitParas.at(0), FitParas.at(1) );

  std::cout<< "FitParas.at(0) = " << FitParas.at(0)<<std::endl;
  std::cout<< "FitParas.at(1) = " << FitParas.at(1)<<std::endl;


  double AvergaeFit = FunctionAverage_Ellipticparaboloid(5, 5, 5, 5, -5, -5,FitParas.at(0), FitParas.at(1) );


std::cout<< "AvergaeFit ="<< AvergaeFit << std::endl;

  char xaxislabel[1024];
  char yaxislabel[1024];


  sprintf(xaxislabel, "Off Set X [mm]");
  sprintf(yaxislabel, "Off Set Y [mm]");

sprintf(Plot_title, "Fitted X and Y Shift");
DrawEllipticparaboloidFit(h_Chisqrt_X_Y, xaxislabel,  yaxislabel, " #chi^{2}",Plot_title, chisqrt_title_pdf2, can, mnv_plotter, -25, 25, -25, 25 );

sprintf(Plot_title, "#chi^{2} after Combined OffSet X Vs Y [E(All)] Min(X,Y) = (5.0 ,-3.0) = (#chi^{2} -  #chi_{Min}^{2})");
Draw2DHist(h_Chisqrt_X_Y,  xaxislabel,  yaxislabel, "(#chi^{2} -  #chi_{Min}^{2})", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);


//sprintf(Plot_title, "Fit with an Average");
//Draw2DHist(h_Chisqrt_X_Y,  xaxislabel,  yaxislabel, "(#chi^{2} -  #chi_{Min}^{2}) /#chi_{Min}^{2}) ", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);
int ndf;
double chiResult = mnv_plotter->Chi2DataMC(h_Chisqrt_X_Y, h_Fit, ndf);

double chiResult_ndf = chiResult / (double)ndf;

sprintf(Plot_title, " #chi^{2} = %.2f / %i = %.2f  Fit with an Average = %.2f" ,chiResult, ndf, chiResult_ndf, AvergaeFit);
Draw2DHist_withEllipse(h_Fit, xaxislabel,  yaxislabel, "#chi^{2}", Plot_title, chisqrt_title_pdf2, can, mnv_plotter , 10 , 10);

FitParas.clear();
FitParas_error.clear();

/////////////////////////////////


Set_h1_Gobal(h_Chisqrt_X_Y_clone_1);
FitMinuit_h1_Gobal_Ellipticparaboloid(FitParas, FitParas_error) ;
FillHist_Ellipticparaboloid(*h_Fit_reg, FitParas.at(0), FitParas.at(1) );

double chiResult_1 = mnv_plotter->Chi2DataMC(h_Chisqrt_X_Y_1, h_Fit_reg, ndf);
double chiResult_ndf_1 = chiResult_1 / (double)ndf;

double AvergaeFit_1 = FunctionAverage_Ellipticparaboloid(5, 5, 5, 5, -5, -5,FitParas.at(0), FitParas.at(1) );

sprintf(Plot_title, "Fitted X and Y Shift");
DrawEllipticparaboloidFit(h_Chisqrt_X_Y_1, xaxislabel,  yaxislabel, "#chi^{2}",Plot_title, chisqrt_title_pdf2, can, mnv_plotter, -25, 25, -25, 25 );

sprintf(Plot_title, "#chi^{2} after Combined OffSet X Vs Y [E(All)] Min(X,Y) = (5.0 ,-3.0)");
Draw2DHist(h_Chisqrt_X_Y_1,  xaxislabel,  yaxislabel, "#chi^{2}", Plot_title,  chisqrt_title_pdf2, can, mnv_plotter);

sprintf(Plot_title, " #chi^{2} = %.2f / %i = %.2f  Fit with an Average = %.2f" ,chiResult_1, ndf, chiResult_ndf_1, AvergaeFit_1);
Draw2DHist_withEllipse(h_Fit_reg, xaxislabel,  yaxislabel, "#chi^{2}" , Plot_title, chisqrt_title_pdf2, can, mnv_plotter , 5 , 5);

std::cout << "BestFULLChitFit[3] = " << BestFULLChitFit[3] << std::endl;
can -> Print(text_title_pdf3);
can -> Print(chisqrt_title_pdf3);

/////////////////
//
/////////////////










delete can;

delete Mvn_ChiFit_X;
delete Mvn_ChiFit_Y;
delete Mvn_ChiFit_X_Y;
delete Mvn_ChiFit_X_Y_Z;
delete Mvn_ChiFit_R_Z;

delete Mvn_ChiFit_Full_X;
delete Mvn_ChiFit_Full_Y;
delete Mvn_ChiFit_Full_X_Y;
delete Mvn_ChiFit_Full_X_Y_Z;
delete Mvn_ChiFit_Full_R_Z;



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



//std::string Total_Chi_Before;
//std::string Total_Chi_After;


void readCSV(std::istream &input, std::vector< std::vector<double> > &output)
{
   std::string csvLine;
    // read every line from the stream
    while( getline(input, csvLine) )
    {
      std::istringstream csvStream(csvLine);
      std::vector<double> csvDoubles;
      string csvElement;
      // read every element from the line that is seperated by commas
      // and put it into the vector or strings
      while( getline(csvStream, csvElement, ',') )
      {       double input = std::stod(csvElement);
              csvDoubles.push_back(input);
      }
      output.push_back(csvDoubles);
    }
}



std::vector<Convolution_X_Y_FitResult> constuctFitVector(std::vector< std::vector<double> > input_vector_vector,   NormalParaFit_XYMap XYShiftMap){

std::vector<Convolution_X_Y_FitResult> outputVector;

for(auto cat:input_vector_vector ){

Convolution_X_Y_FitResult localresult;
int i = (int)std::round(cat.at(0));
int j = (int)std::round(cat.at(1));
int k = (int)std::round(cat.at(2));
int m = (int)std::round(cat.at(3));
Index4 Indexinput{i,j,k,m};

double x_mean = XYShiftMap[Indexinput][kX].mean;
double x_stddev = XYShiftMap[Indexinput][kX].stddev;
double y_mean = XYShiftMap[Indexinput][kY].mean;
double y_stddev = XYShiftMap[Indexinput][kY].stddev;

localresult.index = Indexinput;
localresult.meanX = x_mean;
localresult.stddevX = x_stddev;
localresult.meanY = y_mean;
localresult.stddevY = y_stddev;
localresult.Chi_X = cat.at(4);
localresult.Chi_Y = cat.at(5);
localresult.Chi_Z = cat.at(6);
localresult.Chi_R = cat.at(7);

outputVector.push_back(localresult);
}

return outputVector;


}




double FunctionAverage_Ellipticparaboloid(double Xellipse, double Yellipse,
    double maxX, double maxY, double minX, double minY, double a, double b){

//double topR =  (( pow(maxX,3)/3 - pow(minX,3)/3)  * (maxY - minY)) / pow(a,2);
//double topL = ((maxX - minX) * (pow(maxY,3)/3 - pow(minY,3)/3)) / pow(b,2);

double Top = (maxX - minX)*(maxY - minY)*(((pow(maxX,2) + pow(minX,2) + maxX * minX) * pow(a,2)) + ((pow(maxY,2) + pow(minY,2) + maxY * minY) * pow(b,2)));
double Bottom = 3 * TMath::Pi() *  Xellipse *  Yellipse * pow(b,2) * pow(a,2);
double value = (Top / Bottom);
  return value;
}
