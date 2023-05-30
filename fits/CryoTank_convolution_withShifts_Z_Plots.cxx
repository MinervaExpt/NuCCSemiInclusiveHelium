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
void Append_latex_Presenation_4figures(std::string output_name ,  std::string pdf_name_CV, char *Var_name ,int figure1,int figure2,int figure3,int figure4 );
void Append_latex_Presenation_5figures(std::string output_name ,  std::string pdf_name_CV, char *Var_name ,int figure1,int figure2,int figure3,int figure4,int figure5 );
void Create_Latex_presentation_PlotZ(std::string output_name ,  std::string pdf_name_CV);

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
void Create_Latex_presentation_section(std::string output_name ,  std::string pdf_name_CV, int EmptyStart, int FullStart, int Full_EmptyStart);
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
NormalParaFit_Map ZShifts;

 double stddev_offset_Start_vertexZ = 0.0; //30.0;
 double stddev_offset_Finish_vertexZ = 24.0; //48.0;
 int stddev_steps = 12;
 double mean_offset_Start_vertexZ = -20; //30.0;
 double mean_offset_Finish_vertexZ = 20.0; //48.0;
 int mean_steps = 20; // reduced my half


 FillConvolutionShiftMap(ZShifts, stddev_offset_Start_vertexZ, stddev_offset_Finish_vertexZ,
   stddev_steps, mean_offset_Start_vertexZ, mean_offset_Finish_vertexZ, mean_steps, true);


double boundary1 = 2342.66;
double boundary2 = 2342.66;
double boundary3 = 3698.25;


sprintf(text_title_pdf1, "Plots_Convolution_Subtraction_set7.pdf(" );
can -> Print(text_title_pdf1);
sprintf(text_title_pdf2, "Plots_Convolution_Subtraction_set7.pdf" );
sprintf(text_title_pdf3, "Plots_Convolution_Subtraction_set7.pdf)" );
sprintf(text_title_pdf4, "Plots_Convolution_Subtraction_set7" );
std::string PDF_label(text_title_pdf4);
std::string PDF_label_input(text_title_pdf2);

sprintf(chisqrt_title_pdf1, "Plots_Convolution_Subtraction.pdf(" );

sprintf(chisqrt_title_pdf2, "Plots_Convolution_Subtraction.pdf" );
sprintf(chisqrt_title_pdf3, "Plots_Convolution_Subtraction.pdf)" );
sprintf(chisqrt_title_pdf4, "Plots_Convolution_Subtraction" );



/////////////////////////////////////////////////////////////////////////////////
// Empty
////////////////////////////////////////////////////////////////////////////////

auto Empty_type1 =  "/minerva/data/users/cnguyen/Convolution_vertexRootfiles/Convolution_Empty_bd1_2342.66_bd2_3432.46_bd3_3698.25.root";
//////////////////
// bd1_2360.00_bd2_3407.69_bd3_3670.00
//bd1_2342.66_bd2_3432.46_bd3_3738.25
// 3728.25
////////////////////////////////////////////////////////////////////////////////////////////////
//Full

auto Full_type1 =  "/minerva/data/users/cnguyen/Convolution_vertexRootfiles/Convolution_Full_bd1_2342.66_bd2_3432.46_bd3_3698.25.root";

TFile *PlaylistME_Empty_TFile = new TFile(Empty_type1);
TFile *PlaylistME_Full_TFile = new TFile(Full_type1);


bool is_mc=true;
bool isNOT_mc=false;

std::string  pdf_CV = string(text_title_pdf4);
std::string  pdf_ChiSqr = string(chisqrt_title_pdf4);
bool DoBinwidthNorm=true;
bool MakeXaxisLOG=false;
bool MakeYaxisLOG=false;
bool DrawallErrorGroups=false;

Convolution_Tool Convolution_Tool(PlaylistME_Full_TFile,PlaylistME_Empty_TFile);

Convolution_Tool.input_pdfLabel(PDF_label);
Convolution_Tool.assign_CryoVertex_type();
Convolution_Tool.assign_xAxis();

bool isinit = true;
int rank = 1;

//rank =1 ChiSqt = 2541.97index (i,j,k) = (15, 0 , 0 )
//rank =2 ChiSqt = 2548.83index (i,j,k) = (16, 1 , 0 )
//rank =3 ChiSqt = 2565.5index (i,j,k) = (16, 0 , 0 )
//rank =4 ChiSqt = 2584.38index (i,j,k) = (17, 2 , 0 )
//rank =5 ChiSqt = 2586.12index (i,j,k) = (17, 0 , 0 )
//rank =6 ChiSqt = 2586.56index (i,j,k) = (19, 0 , 0 )

//double Chisqrt_Top1 =3292.99;
//double Chisqrt_Top2 =3303.85;
//double Chisqrt_Top3 =3307.62;
//double Chisqrt_Top4 =3311.59;
//double Chisqrt_Top5 =3318.06;
//double Chisqrt_Top6 =3322.55;

//Index3 Top1index{16, 0 , 0 };
//Index3 Top2index{17, 0 , 0 };
//Index3 Top3index{18, 0 , 0 };
//Index3 Top4index{19, 0 , 0 };
//Index3 Top5index{18, 1 , 0 };
//Index3 Top6index{16, 1 , 0 };

//Index3 Fullindex{12, 0 , 0}; //org
//Index3 Emptyindex{11, 0 , 0 };// org

//Index3 Fullindex{12, 0 , 0 }; //org
//Index3 Emptyindex{13, 0 , 0 }; //org

Index3 Fullindex{12, 0 , 0}; //org
Index3 Emptyindex{13, 0 , 0};// org

std::vector<double> Empty_Chisqrt_Before;
std::vector<double> Full_Chisqrt_Before;
std::vector<double> Full_Empty_Chisqrt_Before;
//
std::vector<double> Empty_Chisqrt_After;
std::vector<double> Full_Chisqrt_After;
std::vector<double> Full_Empty_Chisqrt_After;
//
std::vector<double> Empty_Var_Chisqrt_Before;
std::vector<double> Full_Var_Chisqrt_Before;
std::vector<double> Full_Empty_Var_Chisqrt_Before;
//
std::vector<double> Empty_Var_Chisqrt_After;
std::vector<double> Full_Var_Chisqrt_After;
std::vector<double> Full_Empty_Var_Chisqrt_After;
//
std::vector<double> Empty_Fiduical_Chisqrt_Before;
std::vector<double> Full_Fiduical_Chisqrt_Before;
std::vector<double> Full_Empty_Fiduical_Chisqrt_Before;
//
std::vector<double> Empty_Fiduical_Chisqrt_After;
std::vector<double> Full_Fiduical_Chisqrt_After;
std::vector<double> Full_Empty_Fiduical_Chisqrt_After;
//
std::vector<double> Empty_Var_Fiduical_Chisqrt_Before;
std::vector<double> Full_Var_Fiduical_Chisqrt_Before;
std::vector<double> Full_Empty_Var_Fiduical_Chisqrt_Before;
//
std::vector<double> Empty_Var_Fiduical_Chisqrt_After;
std::vector<double> Full_Var_Fiduical_Chisqrt_After;
std::vector<double> Full_Empty_Var_Fiduical_Chisqrt_After;





//rank =1 ChiSqt = 2657.39index (i,j,k) = (12, 0 , 0 )
//rank =2 ChiSqt = 2658.15index (i,j,k) = (12, 1 , 0 )
//rank =3 ChiSqt = 2671.19index (i,j,k) = (13, 0 , 0 )
//rank =4 ChiSqt = 2677.42index (i,j,k) = (11, 2 , 0 )
//rank =5 ChiSqt = 2678.45index (i,j,k) = (13, 1 , 0 )
//rank =6 ChiSqt = 2684.73index (i,j,k) = (14, 1 , 0 )
std::vector<double> wgt_vector;
std::vector<double> wgt_error_vector;
double Fullmean = ZShifts[Fullindex].mean;
double Fullsigma = ZShifts[Fullindex].stddev;

double Emptymean = ZShifts[Emptyindex].mean;
double Emptysigma = ZShifts[Emptyindex].stddev;

Convolution_Tool.init_Full_Plotting_PlaylistCombined(isinit, rank , Fullindex.i, Fullindex.j, Fullindex.k);
Convolution_Tool.init_Empty_Plotting_PlaylistCombined(isinit, rank,  Emptyindex.i, Emptyindex.j, Emptyindex.k);
Convolution_Tool.FillEmpty_Normal_Fit_ParametersXY(Convolution_Vertex_shift_Values::Empty_vertex_X_mean , Convolution_Vertex_shift_Values::Empty_vertex_X_sigma, Convolution_Vertex_shift_Values::Empty_vertex_Y_mean , Convolution_Vertex_shift_Values::Empty_vertex_Y_sigma);
Convolution_Tool.FillFull_Normal_Fit_ParametersXY(Convolution_Vertex_shift_Values::Full_vertex_X_mean , Convolution_Vertex_shift_Values::Full_vertex_X_sigma, Convolution_Vertex_shift_Values::Full_vertex_Y_mean , Convolution_Vertex_shift_Values::Full_vertex_Y_sigma);
Convolution_Tool.includeBouodaries(true);
//Convolution_Tool.SetBoundaries( 2342.66,2342.66, 3738.25 );
//bd1_2360.00_bd2_3407.69_bd3_3670.00
Convolution_Tool.SetBoundaries( boundary1, boundary2, boundary3 );



Convolution_Tool.Plot_regions_XYZFit_Empty( Emptymean ,  Emptysigma, 0, 0, "[Empty]" );


Convolution_Tool.Plot_regions_TRUEXYZFit_Empty(0 , 0, 0, 0, "[Empty]" );
Convolution_Tool.Plot_regions_NonFitVars_Empty( Emptymean ,  Emptysigma, 0, 0, "[Empty]"  );

Convolution_Tool.GetVectorChiSq_before_fit(Empty_Chisqrt_Before);
Convolution_Tool.GetVectorChiSqVars_before_fit(Empty_Var_Chisqrt_Before);
Convolution_Tool.ClearChisqrtvector();
//
//std::cout<<"checking output  Empty_Chisqrt_Before"<<std::endl;
//for(auto cat :Empty_Chisqrt_Before ){
//std::cout<< cat<< std::endl;
//}
//std::cout<<"finished"<< std::endl;
//
//std::cout<<"checking output  Empty_Var_Chisqrt_Before"<<std::endl;
//for(auto cat :Empty_Var_Chisqrt_Before ){
//std::cout<< cat<< std::endl;
//}
//std::cout<<"finished"<< std::endl;



Convolution_Tool.Plot_regions_XYZFit_Full( Fullmean , Fullsigma, 0, 0, "[Full]" );
Convolution_Tool.Plot_regions_TRUEXYZFit_Full(0 , 0, 0, 0, "[Full]" );
Convolution_Tool.Plot_regions_NonFitVars_Full( Fullmean , Fullsigma, 0, 0, "[Full]"  );

Convolution_Tool.GetVectorChiSq_before_fit(Full_Chisqrt_Before);
Convolution_Tool.GetVectorChiSqVars_before_fit(Full_Var_Chisqrt_Before);
Convolution_Tool.ClearChisqrtvector();


//std::cout<<"checking output  Full_Chisqrt_Before"<<std::endl;
//for(auto cat :Full_Chisqrt_Before ){
//std::cout<< cat<< std::endl;
//}
//std::cout<<"finished"<< std::endl;
//std::cout<<"checking output  Full_Var_Chisqrt_Before"<<std::endl;
//for(auto cat :Full_Var_Chisqrt_Before ){
//std::cout<< cat<< std::endl;
//}

Convolution_Tool.CloneFulltoFull_Empty();
Convolution_Tool.Subtract_Full_Empty(0);

Convolution_Tool.Plot_regions_XYZFit_Full_Empty(Fullmean , Fullsigma, Emptymean,Emptysigma, 0, 0, "[F-E]" );
Convolution_Tool.Plot_regions_TRUEXYZFit_Full_Empty(0 , 0, 0, 0, "[F-E]" );
Convolution_Tool.Plot_regions_NonFitVars_Full_Empty(Fullmean , Fullsigma,Emptymean,Emptysigma, 0, 0, "[F-E]" );

Convolution_Tool.GetVectorChiSq_before_fit(Full_Empty_Chisqrt_Before);
Convolution_Tool.GetVectorChiSqVars_before_fit(Full_Empty_Var_Chisqrt_Before);
Convolution_Tool.ClearChisqrtvector();

//
//std::cout<<"checking output  Full_Empty_Chisqrt_Before"<<std::endl;
//for(auto cat :Full_Empty_Chisqrt_Before ){
//std::cout<< cat<< std::endl;
//}
//std::cout<<"finished"<< std::endl;
//std::cout<<"checking output  Full_Empty_Var_Chisqrt_Before"<<std::endl;
//for(auto cat :Full_Empty_Var_Chisqrt_Before ){
//std::cout<< cat<< std::endl;
//}


Convolution_Tool.init_Empty_Plotting_PlaylistCombined_Fiducial(isinit, rank,  Emptyindex.i, Emptyindex.j, Emptyindex.k);
Convolution_Tool.init_Full_Plotting_PlaylistCombined_Fiducial( isinit, rank , Fullindex.i, Fullindex.j, Fullindex.k);

Convolution_Tool.CloneFulltoFull_Empty_Fiducial();
Convolution_Tool.Subtract_Full_Empty_Fiducial(0);

Convolution_Tool.Plot_regions_XYZFit_Empty_Fiducial( Emptymean ,  Emptysigma, 0, 0, "[Fiducial][Empty]" );
Convolution_Tool.Plot_regions_TRUEXYZFit_Empty_Fiducial(Emptymean ,  Emptysigma, 0, 0, "[Fiducial][Empty]" );
Convolution_Tool.Plot_regions_NonFitVars_Empty_Fiducial( Emptymean ,  Emptysigma, 0, 0, "[Fiducial][Empty]"  );

Convolution_Tool.GetVectorChiSq_before_fit(Empty_Fiduical_Chisqrt_Before);
Convolution_Tool.GetVectorChiSqVars_before_fit(Empty_Var_Fiduical_Chisqrt_Before);
Convolution_Tool.ClearChisqrtvector();

std::cout<<"checking output  Empty_Fiduical_Chisqrt_Before"<<std::endl;
for(auto cat :Empty_Fiduical_Chisqrt_Before ){
std::cout<< cat<< std::endl;
}
//std::cout<<"finished"<< std::endl;
//
//std::cout<<"checking output  Empty_Fiduical_Var_Chisqrt_Before"<<std::endl;
//for(auto cat :Empty_Var_Fiduical_Chisqrt_Before ){
//std::cout<< cat<< std::endl;
//}
//std::cout<<"finished"<< std::endl;

Convolution_Tool.Plot_regions_XYZFit_Full_Fiducial( Fullmean , Fullsigma, 0, 0, "[Fiducial][Full]" );
Convolution_Tool.Plot_regions_TRUEXYZFit_Full_Fiducial(Fullmean , Fullsigma, 0, 0, "[Fiducial][Full]" );
Convolution_Tool.Plot_regions_NonFitVars_Full_Fiducial( Fullmean , Fullsigma, 0, 0, "[Fiducial][Full]"  );

Convolution_Tool.GetVectorChiSq_before_fit(Full_Fiduical_Chisqrt_Before);
Convolution_Tool.GetVectorChiSqVars_before_fit(Full_Var_Fiduical_Chisqrt_Before);
Convolution_Tool.ClearChisqrtvector();


Convolution_Tool.Plot_regions_XYZFit_Full_Empty_Fiducial(  Fullmean , Fullsigma, Emptymean ,  Emptysigma, 0, 0, "[Fiducial][F-E]" );
Convolution_Tool.Plot_regions_TRUEXYZFit_Full_Empty_Fiducial(0 , 0, 0, 0, "[Fiducial][F-E]" );
Convolution_Tool.Plot_regions_NonFitVars_Full_Empty_Fiducial( Fullmean , Fullsigma, Emptymean ,  Emptysigma, 0, 0, "[Fiducial][F-E]" );
std::cout<< " Setting Tool "<<std::endl;

Convolution_Tool.GetVectorChiSq_before_fit(Full_Empty_Fiduical_Chisqrt_Before);
Convolution_Tool.GetVectorChiSqVars_before_fit(Full_Empty_Var_Fiduical_Chisqrt_Before);
Convolution_Tool.ClearChisqrtvector();

SetConvolutionShiftMapTool(Convolution_Tool);
std::cout<< " Fitting "<<std::endl;
FitConvolutionTool(Convolution_Tool, 1,
  "fitlog", "log", PDF_label,
wgt_vector, wgt_error_vector );


Convolution_Tool.Fill_Alwgt(wgt_vector, wgt_error_vector);
std::cout<< " applying weights "<<std::endl;
Convolution_Tool.ApplyFitResults_toEmpty();
Convolution_Tool.ApplyFitResults_toTRUEEmpty();
Convolution_Tool.ApplyFitResults_tononFitVarEmpty();


Convolution_Tool.ApplyFitResults_toEmpty_Fiducial();
Convolution_Tool.ApplyFitResults_toTRUEEmpty_Fiducial();
Convolution_Tool.ApplyFitResults_tononFitVarEmpty_Fiducial();

Convolution_Tool.ApplyFitResults_toFull();
Convolution_Tool.ApplyFitResults_toTRUEFull();
Convolution_Tool.ApplyFitResults_tononFitVarFull();


Convolution_Tool.ApplyFitResults_toFull_Fiducial();
Convolution_Tool.ApplyFitResults_toTRUEFull_Fiducial();
Convolution_Tool.ApplyFitResults_tononFitVarFull_Fiducial();
std::cout<< " Cloning "<<std::endl;


std::cout<< " Plotting fits !! "<<std::endl;

Convolution_Tool.Plot_regions_XYZFit_Empty( Emptymean ,  Emptysigma, 1, 1, "[Empty]" );
Convolution_Tool.Plot_regions_TRUEXYZFit_Empty(Emptymean ,  Emptysigma, 1, 1, "[Empty]" );
Convolution_Tool.Plot_regions_NonFitVars_Empty( Emptymean ,  Emptysigma, 1, 1, "[Empty]"  );

Convolution_Tool.GetVectorChiSq_after_fit(Empty_Chisqrt_After);
Convolution_Tool.GetVectorChiSqVars_after_fit(Empty_Var_Chisqrt_After);
Convolution_Tool.ClearChisqrtvector();

Convolution_Tool.Plot_regions_XYZFit_Full( Fullmean , Fullsigma, 1, 1, "[Full]" );
Convolution_Tool.Plot_regions_TRUEXYZFit_Full(Fullmean , Fullsigma, 1, 1, "[Full]" );
Convolution_Tool.Plot_regions_NonFitVars_Full( Fullmean , Fullsigma, 1, 1, "[Full]"  );

Convolution_Tool.GetVectorChiSq_after_fit(Full_Chisqrt_After);
Convolution_Tool.GetVectorChiSqVars_after_fit(Full_Var_Chisqrt_After);
Convolution_Tool.ClearChisqrtvector();

Convolution_Tool.Plot_regions_XYZFit_Empty_Fiducial( Emptymean ,  Emptysigma, 1, 1, "[Fiducial][Empty]" );
Convolution_Tool.Plot_regions_TRUEXYZFit_Empty_Fiducial(Emptymean ,  Emptysigma, 1, 1, "[Fiducial][Empty]" );
Convolution_Tool.Plot_regions_NonFitVars_Empty_Fiducial( Emptymean ,  Emptysigma, 1, 1, "[Fiducial][Empty]"  );

Convolution_Tool.GetVectorChiSq_after_fit(Empty_Fiduical_Chisqrt_After);
Convolution_Tool.GetVectorChiSqVars_after_fit(Empty_Var_Fiduical_Chisqrt_After);
Convolution_Tool.ClearChisqrtvector();



Convolution_Tool.Plot_regions_XYZFit_Full_Fiducial( Fullmean , Fullsigma, 1, 1, "[Fiducial][Full]" );
Convolution_Tool.Plot_regions_TRUEXYZFit_Full_Fiducial(Fullmean , Fullsigma, 1, 1, "[Fiducial][Full]" );
Convolution_Tool.Plot_regions_NonFitVars_Full_Fiducial( Fullmean , Fullsigma, 1, 1, "[Fiducial][Full]"  );

Convolution_Tool.GetVectorChiSq_after_fit(Full_Fiduical_Chisqrt_After);
Convolution_Tool.GetVectorChiSqVars_after_fit(Full_Var_Fiduical_Chisqrt_After);
Convolution_Tool.ClearChisqrtvector();

Convolution_Tool.ClonetoFull_EMPTY(1 , 1);
Convolution_Tool.Subtract_Full_Empty(1);
std::cout<< " Cloning Fiduical "<<std::endl;
Convolution_Tool.ClonetoFull_EMPTY_Fiducial(1 , 1);
Convolution_Tool.Subtract_Full_Empty_Fiducial(1);

std::cout<< " Subtraction "<<std::endl;

Convolution_Tool.Plot_regions_XYZFit_Full_Empty(   Fullmean , Fullsigma, Emptymean ,  Emptysigma, 1, 1, "[F-E]" );
Convolution_Tool.Plot_regions_TRUEXYZFit_Full_Empty(  0 , 0, 1, 1, "[F-E]" );
Convolution_Tool.Plot_regions_NonFitVars_Full_Empty( Fullmean , Fullsigma, Emptymean ,  Emptysigma, 1, 1, "[F-E]" );


Convolution_Tool.GetVectorChiSq_after_fit(Full_Empty_Chisqrt_After);
Convolution_Tool.GetVectorChiSqVars_after_fit(Full_Empty_Var_Chisqrt_After);
Convolution_Tool.ClearChisqrtvector();


Convolution_Tool.Plot_regions_XYZFit_Full_Empty_Fiducial(Fullmean , Fullsigma,Emptymean ,  Emptysigma, 1, 1, "[Fiducial][F-E]" );
Convolution_Tool.Plot_regions_TRUEXYZFit_Full_Empty_Fiducial(  0 , 0, 1, 1, "[Fiducial][F-E]" );
Convolution_Tool.Plot_regions_NonFitVars_Full_Empty_Fiducial( Fullmean , Fullsigma,Emptymean ,  Emptysigma, 1, 1, "[Fiducial][F-E]" );


Convolution_Tool.GetVectorChiSq_after_fit(Full_Empty_Fiduical_Chisqrt_After);
Convolution_Tool.GetVectorChiSqVars_after_fit(Full_Empty_Var_Fiduical_Chisqrt_After);
Convolution_Tool.ClearChisqrtvector();


std::string y_offset_string;
std::string z_offset_string;
std::string title_string;

Create_Latex_presentation_PlotZ("Orginal_set1" ,  "Plots_Convolution_Subtraction");

double bins_X = 48;
double bins_Y = 48;
double bins_Z = 104;
double bins_R = 15;

double NumberDoF_X_Y_Z = bins_X*bins_Y*bins_Z - 4;

double npars = 4;

char Name[1024];

sprintf(Name,"Fit_XYZR_chisqt_Before_bd1_%.2f_bd2_%.2f_bd3_%.2f.txt",boundary1, boundary2, boundary3 );
std::ofstream outfile (Name);
std::vector<double>::iterator Full_iter;
std::vector<double>::iterator Empty_iter;
std::vector<double>::iterator Full_Empty_iter;

std::vector<double>::iterator Full_Fid_iter;
std::vector<double>::iterator Empty_Fid_iter;
std::vector<double>::iterator Full_Empty_Fid_iter;



for(Empty_iter = Empty_Chisqrt_Before.begin() ,Full_iter = Full_Chisqrt_Before.begin(), Full_Empty_iter = Full_Empty_Chisqrt_Before.begin();Empty_iter != Empty_Chisqrt_Before.end(); Empty_iter++ , Full_iter++,Full_Empty_iter++  ){
outfile<< *Full_iter<< ", " <<  *Empty_iter<< ", "<< *Full_Empty_iter << " , ";
}
outfile<<""<<std::endl;

for(Empty_Fid_iter = Empty_Fiduical_Chisqrt_Before.begin() ,Full_Fid_iter = Full_Fiduical_Chisqrt_Before.begin(), Full_Empty_Fid_iter = Full_Empty_Fiduical_Chisqrt_Before.begin();Empty_Fid_iter !=  Empty_Fiduical_Chisqrt_Before.end(); Empty_Fid_iter++ , Full_Fid_iter++,Full_Empty_Fid_iter++  ){
outfile<< *Full_Fid_iter<< ", " <<  *Empty_Fid_iter<< ", "<< *Full_Empty_Fid_iter << " , ";
}


outfile.close();

sprintf(Name,"Fit_var_chisqt_Before_bd1_%.2f_bd2_%.2f_bd3_%.2f.txt",boundary1, boundary2, boundary3 );
std::ofstream outfile2 (Name);


for(Empty_iter = Empty_Var_Chisqrt_Before.begin() ,Full_iter = Full_Var_Chisqrt_Before.begin(), Full_Empty_iter = Full_Empty_Var_Chisqrt_Before.begin();Empty_iter != Empty_Var_Chisqrt_Before.end(); Empty_iter++ , Full_iter++,Full_Empty_iter++  ){
outfile2<< *Full_iter<< ", " <<  *Empty_iter<< ", " << *Full_Empty_iter << " , ";
}

outfile2<<""<<std::endl;

for(Empty_Fid_iter = Empty_Var_Fiduical_Chisqrt_Before.begin() ,Full_Fid_iter = Full_Var_Fiduical_Chisqrt_Before.begin(), Full_Empty_Fid_iter = Full_Empty_Var_Fiduical_Chisqrt_Before.begin();Empty_Fid_iter !=  Empty_Var_Fiduical_Chisqrt_Before.end(); Empty_Fid_iter++ , Full_Fid_iter++,Full_Empty_Fid_iter++  ){
outfile2<< *Full_Fid_iter<< ", " <<  *Empty_Fid_iter<< ", "<< *Full_Empty_Fid_iter << " , ";
}




outfile2.close();

sprintf(Name,"Fit_XYZR_chisqt_After_bd1_%.2f_bd2_%.2f_bd3_%.2f.txt",boundary1, boundary2, boundary3 );
std::ofstream outfile3 (Name);



for(Empty_iter = Empty_Chisqrt_After.begin() ,Full_iter = Full_Chisqrt_After.begin(), Full_Empty_iter = Full_Empty_Chisqrt_After.begin();Empty_iter != Empty_Chisqrt_After.end(); Empty_iter++ , Full_iter++,Full_Empty_iter++  ){
outfile3<< *Full_iter<< ", " <<  *Empty_iter<< ", "<< *Full_Empty_iter << " , ";
}
outfile3<<""<<std::endl;

for(Empty_Fid_iter = Empty_Fiduical_Chisqrt_After.begin() ,Full_Fid_iter = Full_Fiduical_Chisqrt_After.begin(), Full_Empty_Fid_iter = Full_Empty_Fiduical_Chisqrt_After.begin();Empty_Fid_iter !=  Empty_Fiduical_Chisqrt_After.end(); Empty_Fid_iter++ , Full_Fid_iter++,Full_Empty_Fid_iter++  ){
outfile3<< *Full_Fid_iter<< ", " <<  *Empty_Fid_iter<< ", "<< *Full_Empty_Fid_iter << " , ";
}


outfile3.close();

sprintf(Name,"Fit_var_chisqt_After_bd1_%.2f_bd2_%.2f_bd3_%.2f.txt",boundary1, boundary2, boundary3 );

std::ofstream outfile4 (Name);



for(Empty_iter = Empty_Var_Chisqrt_After.begin() ,Full_iter = Full_Var_Chisqrt_After.begin(), Full_Empty_iter = Full_Empty_Var_Chisqrt_After.begin();Empty_iter != Empty_Var_Chisqrt_After.end(); Empty_iter++ , Full_iter++,Full_Empty_iter++  ){
outfile4<< *Full_iter<< ", " <<  *Empty_iter<< ", "<< *Full_Empty_iter << " , ";
}
outfile4<<""<<std::endl;

for(Empty_Fid_iter = Empty_Var_Fiduical_Chisqrt_After.begin() ,Full_Fid_iter = Full_Var_Fiduical_Chisqrt_After.begin(), Full_Empty_Fid_iter = Full_Empty_Var_Fiduical_Chisqrt_After.begin();Empty_Fid_iter !=  Empty_Var_Fiduical_Chisqrt_After.end(); Empty_Fid_iter++ , Full_Fid_iter++,Full_Empty_Fid_iter++  ){
outfile4<< *Full_Fid_iter<< ", " <<  *Empty_Fid_iter<< ", "<< *Full_Empty_Fid_iter << " , ";
}


outfile4.close();

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////








can -> Print(text_title_pdf3);




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






void Append_latex_Presenation_4figures(std::string output_name ,  std::string pdf_name_CV, char *Var_name ,int figure1,int figure2,int figure3,int figure4 )
  {
  double scale= .21;
  std::ofstream myfile;

 std::string fileName = output_name + ".txt";
  myfile.open(fileName, std::ios_base::app);
  std::cout<<"Adding to Latex File "<< fileName<<std::endl;
  LatexFormat Presenation(scale);

  myfile<<Presenation.GetSubSection(Var_name);


  myfile<<"\n";
  myfile<<"\n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<"%%% Slide "<<Var_name <<" \n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<Presenation.GetBeginFrame("")<< "\n";
  myfile<<"\\centering \n";
  myfile<<Presenation.GetBeginTabular("cc")<< "\n";
  myfile<<Presenation.GetInclude_figure(figure1, pdf_name_CV)<< "\n";
  myfile<<"& \n";
  myfile<<Presenation.GetInclude_figure(figure2, pdf_name_CV )<< "\n";
  myfile<<"\\vspace{-.25cm} \n";
  myfile<<"\\\\ \n";
  myfile<<Presenation.GetInclude_figure(figure3, pdf_name_CV)<< "\n";
  myfile<<"& \n";
  myfile<<Presenation.GetInclude_figure(figure4, pdf_name_CV )<< "\n";
  myfile<<Presenation.GetEndTabular()<< "\n";
  myfile<<Presenation.GetEndFrame();


    myfile.close();




}//end of


void Append_latex_Presenation_5figures(std::string output_name ,  std::string pdf_name_CV, char *Var_name ,int figure1,int figure2,int figure3,int figure4,int figure5 )
  {
  double scale= .21;
  std::ofstream myfile;

 std::string fileName = output_name + ".txt";
  myfile.open(fileName, std::ios_base::app);
  std::cout<<"Adding to Latex File "<< fileName<<std::endl;
  LatexFormat Presenation(scale);

  myfile<<Presenation.GetSubSection(Var_name);

  myfile<<"\n";
  myfile<<"\n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<"%%% 2DEff FULL "<< Var_name <<" \n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<Presenation.GetBeginFrame(Var_name)<< "\n";
  myfile<<Presenation.GetBeginTabular("ccc")<< "\n";
  myfile<<Presenation.GetInclude_figure(figure1, pdf_name_CV)<< "\n";
  myfile<<"\\vspace{-.25cm} \n";
  myfile<<"& \n";
  myfile<<Presenation.GetInclude_figure(figure2, pdf_name_CV )<< "\n";
  myfile<<"& \n";
  myfile<<Presenation.GetInclude_figure(figure3, pdf_name_CV)<< "\n";
  myfile<<"\\\\ \n";
  myfile<<Presenation.GetInclude_figure(figure4, pdf_name_CV )<< "\n";
  myfile<<"& \n";
  myfile<<Presenation.GetInclude_figure(figure5, pdf_name_CV)<< "\n";
  myfile<<Presenation.GetEndTabular()<< "\n";
  myfile<<Presenation.GetEndFrame();


    myfile.close();




}//end of

void Create_Latex_presentation_section(std::string output_name ,  std::string pdf_name_CV, int EmptyStart, int FullStart, int Full_EmptyStart){
//int EmptyStart = 2;
//int FullStart = 19;
//int Full_EmptyStart = 37;
//
//int EmptyStart_Fid = 54;
//int FullStart_Fid = 71;
//int Full_EmptyStart_Fid = 88;
//
//
//int EmptyStart_Fit = 105;
//int FullStart_Fit = 122;
//int Full_EmptyStart_Fit = 173;
//
//int EmptyStart_Fid_Fit = 139;
//int FullStart_Fid_Fit = 156;
//int Full_EmptyStart_Fid_Fit = 190;

/////////////////////////////////////////////////////
Append_latex_Presenation_4figures( output_name ,  pdf_name_CV, "RECO vertex" , EmptyStart, EmptyStart+1,EmptyStart+2, EmptyStart+3 );
Append_latex_Presenation_4figures( output_name ,  pdf_name_CV, "RECO vertex" , FullStart, FullStart+1,FullStart+2, FullStart+3 );
Append_latex_Presenation_4figures( output_name ,  pdf_name_CV, "RECO vertex" , Full_EmptyStart, Full_EmptyStart+1,Full_EmptyStart+2, Full_EmptyStart+3 );

EmptyStart+=4;
FullStart+=4;
Full_EmptyStart+=4;

Append_latex_Presenation_4figures( output_name ,  pdf_name_CV, "TRUE vertex" , EmptyStart,      EmptyStart+1,EmptyStart+2, EmptyStart+3 );
Append_latex_Presenation_4figures( output_name ,  pdf_name_CV, "TRUE vertex" , FullStart,       FullStart+1,FullStart+2, FullStart+3 );
Append_latex_Presenation_4figures( output_name ,  pdf_name_CV, "TRUE vertex" , Full_EmptyStart, Full_EmptyStart+1,Full_EmptyStart+2, Full_EmptyStart+3 );

EmptyStart+=4;
FullStart+=4;
Full_EmptyStart+=4;

Append_latex_Presenation_4figures( output_name ,  pdf_name_CV, "Muon Vars" , EmptyStart, EmptyStart+1,EmptyStart+2, EmptyStart+3 );
Append_latex_Presenation_4figures( output_name ,  pdf_name_CV, "Muon Vars" , FullStart, FullStart+1,FullStart+2, FullStart+3 );
Append_latex_Presenation_4figures( output_name ,  pdf_name_CV, "Muon Vars" , Full_EmptyStart, Full_EmptyStart+1,Full_EmptyStart+2, Full_EmptyStart+3 );


//EmptyStart+=4;
//FullStart+=4;
//Full_EmptyStart+=4;
//
//Append_latex_Presenation_4figures( output_name ,  pdf_name_CV, "Muon Vars" , EmptyStart, EmptyStart+1,EmptyStart+2, EmptyStart+3 );
//Append_latex_Presenation_4figures( output_name ,  pdf_name_CV, "Muon Vars" , FullStart, FullStart+1,FullStart+2, FullStart+3 );
//Append_latex_Presenation_4figures( output_name ,  pdf_name_CV, "Muon Vars" , Full_EmptyStart, Full_EmptyStart+1,Full_EmptyStart+2, Full_EmptyStart+3 );

EmptyStart+=4;
FullStart+=4;
Full_EmptyStart+=4;

Append_latex_Presenation_5figures( output_name ,  pdf_name_CV, "Muon Vars" , EmptyStart, EmptyStart+1,EmptyStart+2, EmptyStart+3,EmptyStart+4 );
Append_latex_Presenation_5figures( output_name ,  pdf_name_CV, "Muon Vars" , FullStart, FullStart+1,FullStart+2, FullStart+3,FullStart+4 );
Append_latex_Presenation_5figures( output_name ,  pdf_name_CV, "Muon Vars" , Full_EmptyStart, Full_EmptyStart+1,Full_EmptyStart+2, Full_EmptyStart+3,Full_EmptyStart+4 );
//////////////////////////////////////////////////////////////


}

void Create_Latex_presentation_PlotZ(std::string output_name ,  std::string pdf_name_CV){

  int EmptyStart = 2;
  int FullStart = 19;
  int Full_EmptyStart = 36;
  //
  int EmptyStart_Fid = 53;
  int FullStart_Fid = 70;
  int Full_EmptyStart_Fid = 87;
  //
  //
  int EmptyStart_Fit = 104;
  int FullStart_Fit = 121;
  int Full_EmptyStart_Fit = 172;
  //
  int EmptyStart_Fid_Fit = 138;
  int FullStart_Fid_Fit = 155;
  int Full_EmptyStart_Fid_Fit = 189;
 std::string fileName = output_name + ".txt";
  std::ofstream outfile (fileName);
  outfile.close();



Create_Latex_presentation_section( output_name ,   pdf_name_CV, EmptyStart, FullStart,  Full_EmptyStart);
Create_Latex_presentation_section( output_name ,   pdf_name_CV, EmptyStart_Fid, FullStart_Fid,  Full_EmptyStart_Fid);

Create_Latex_presentation_section( output_name ,   pdf_name_CV, EmptyStart_Fit, FullStart_Fit,  Full_EmptyStart_Fit);
Create_Latex_presentation_section( output_name ,   pdf_name_CV, EmptyStart_Fid_Fit, FullStart_Fid_Fit,  Full_EmptyStart_Fid_Fit);



}
