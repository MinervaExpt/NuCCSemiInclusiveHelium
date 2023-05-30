#ifndef CRYOTANK_CONVOLUTION_WITHSHIFTS_H
#define CRYOTANK_CONVOLUTION_WITHSHIFTS_H


#include "TTree.h"
#include "TFile.h"
#include <map>

#include "TChain.h"
#include "TH1.h"
#include <TH2.h>
#include "TF1.h"
#include "TH1D.h"
#include "TH1F.h"
#include "TGraphErrors.h"
#include "THStack.h"

#include "TMinuit.h"
#include "TFitter.h"


#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "TMath.h"
#include <math.h>
#include <vector>
#include "TEllipse.h"
#include <TROOT.h>
#include <TStyle.h>
#include "TAttMarker.h"
#include "TAttFill.h"
#include "TPaletteAxis.h"
#include <TCanvas.h>
#include <TPad.h>
#include <TPaveStats.h>
#include "TLegend.h"
#include <TLatex.h>
#include <TPDF.h>
#include <TPostScript.h>
#include "TImage.h"
#include <TProfile.h>
#include "PlotUtils/MnvApplication.h"
#include <PlotUtils/MnvH1D.h>
#include <PlotUtils/MnvH2D.h>
#include <PlotUtils/MnvPlotter.h>
#include <MinervaUnfold/MnvUnfold.h>
#include <PlotUtils/MnvVertErrorBand.h>
#include <PlotUtils/MnvLatErrorBand.h>
#include <PlotUtils/MnvNormalization.h>
#include <PlotUtils/FluxReweighter.h>
#include <PlotUtils/POTCounter.h>

#include <set>
#include <iterator>
#include <sstream>
#include <string>
#include <time.h>

#include "../includes/loadLibs.h"
#include "../includes/HeliumPlotUtils.h"
#include "../includes/CryoTankUtils.h"
#include "../includes/HeliumDefaults.h"

#include "../includes/HeliumUtils.h"
#include "../includes/Helium2DPlotUtils.h"
#include "../Make_Plots/Common_plots.h"
#include "../includes/Helium_ConvolutionTool.h"
#include "MinervaUnfold/MnvResponse.h"


std::vector<CryoVertex> GetCryoVertexVaribles();

std::vector<ME_helium_Playlists> GetPlayListVector();
void Kin(bool &cutsOn, bool &my_norm, bool &my_debug, const char *userDir);



//////////////////////////////////////////////////////////////////////////////
//
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
   char *xaxislabel, char* yaxislabel, Pot_MapList Pot_MC , Pot_MapList POT_Data, double Ymax);

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


void SetConvolutionShiftMapTool(Convolution_Tool sbtool_input);
void Clone_OffSet1DMap(MnvH1D_Map &inputMap_Clone , MnvH1D_Map inputMap_input);
void Clone_OffSet2DMap(MnvH2D_Map &inputMap_Clone , MnvH2D_Map inputMap_input);
void FitConvolutionTool(Convolution_Tool sbtool, int FitFullorEmpty,
  std::string fitName, std::string file_name, std::string pdf_label,
  std::vector<double> &wgt_vector, std::vector<double> &wgt_error_vector, double &chisqrt, double &chisqrt_error);
void FitConvolutionTool(Convolution_Tool sbtool, int FitFullorEmpty,
		std::string fitName, std::string file_name, std::string pdf_label,
		std::vector<double> &wgt_vector, std::vector<double> &wgt_error_vector );
  double calc_LOG_ChiSq_For_ConvolutionTool_CV_Vertex(
Convolution_CryoRegions &CryoRegions,
  double InPut_Alwgt_region1,
  double InPut_Alwgt_region2,
  double InPut_Alwgt_region3,
  double InPut_Alwgt_region4,
   int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1, bool removeFirstandLastBin= true, bool isVertexZ=false);


   ///////////////////////////////////////////////////////////////////
   double calc_ChiSq_For_ConvolutionTool_CV_Vertex_Combined_Full_Empty_1set(
   Convolution_CryoRegions &CryoRegions_Empty,
   Convolution_CryoRegions &CryoRegions_Full,
     double InPut_Alwgt_region1,
     double InPut_Alwgt_region2,
     double InPut_Alwgt_region3,
     double InPut_Alwgt_region4,

      int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1, bool removeFirstandLastBin= true, bool isVertexZ=false);

      double calc_ChiSq_For_ConvolutionTool_CV_Vertex_Combined_Full_Empty_1set_log(
Convolution_CryoRegions &CryoRegions_Empty,
Convolution_CryoRegions &CryoRegions_Full,
  double InPut_Alwgt_region1,
  double InPut_Alwgt_region2,
  double InPut_Alwgt_region3,
  double InPut_Alwgt_region4,

   int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1, bool removeFirstandLastBin= true, bool isVertexZ=false);

   double calc_ChiSq_For_ConvolutionTool_CV_Vertex_Combined_Full_Empty_Difference(
   Convolution_CryoRegions &CryoRegions_Empty,
   Convolution_CryoRegions &CryoRegions_Full,
     double InPut_Alwgt_region1,
     double InPut_Alwgt_region2,
     double InPut_Alwgt_region3,
     double InPut_Alwgt_region4,

      int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1, bool removeFirstandLastBin= true, bool isVertexZ=false);

      double calc_ChiSq_For_ConvolutionTool_CV_Vertex_Combined_Full_Empty_Difference_Log(
    Convolution_CryoRegions &CryoRegions_Empty,
    Convolution_CryoRegions &CryoRegions_Full,
      double InPut_Alwgt_region1,
      double InPut_Alwgt_region2,
      double InPut_Alwgt_region3,
      double InPut_Alwgt_region4,

       int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1, bool removeFirstandLastBin= true, bool isVertexZ=false);



void calc_ChiSq_ConvolutionTool_Empty(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag);
void calc_ChiSq_ConvolutionTool_Full(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag);
void calc_ChiSq_ConvolutionTool_Empty_RZ(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag);
void calc_ChiSq_ConvolutionTool_EmptyLog(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag);
void calc_ChiSq_ConvolutionTool_FullLog(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag);

void calc_ChiSq_ConvolutionTool_Combined(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag);
void calc_ChiSq_ConvolutionTool_Combined_Log(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag);
void calc_ChiSq_ConvolutionTool_Combined_1set(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag);
void calc_ChiSq_ConvolutionTool_Combined_1set_Log(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag);
void calc_ChiSq_ConvolutionTool_Combined_Differece(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag);
void calc_ChiSq_ConvolutionTool_Combined_Differece_Log(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag);


void FitMinuit_Convolution_Empty(Convolution_Tool sbtool, std::string fitName, std::string pdf_label, std::vector<double> &wgt_vector, std::vector<double> &wgt_error , double &chisqrt, double &chisqrt_error);
void FitMinuit_Convolution_Full(Convolution_Tool sbtool, std::string fitName, std::string pdf_label, std::vector<double> &wgt_vector, std::vector<double> &wgt_error);

void FitMinuit_Convolution_Empty_RZ(Convolution_Tool sbtool, std::string fitName, std::string pdf_label, std::vector<double> &wgt_vector, std::vector<double> &wgt_error);
void FitMinuit_Convolution_EmptyLogchi2(Convolution_Tool sbtool, std::string fitName, std::string pdf_label, std::vector<double> &wgt_vector, std::vector<double> &wgt_error, double &chisqrt, double &chisqrt_error);
void FitMinuit_Convolution_FullLogchi2(Convolution_Tool sbtool, std::string fitName, std::string pdf_label, std::vector<double> &wgt_vector, std::vector<double> &wgt_error);

void FitMinuit_Convolution_Combined_chi2(Convolution_Tool sbtool, std::string fitName, std::string pdf_label, std::vector<double> &wgt_vector, std::vector<double> &wgt_error, double &chisqrt, double &chisqrt_error);
void FitMinuit_Convolution_CombinedLogchi2(Convolution_Tool sbtool, std::string fitName, std::string pdf_label, std::vector<double> &wgt_vector, std::vector<double> &wgt_error,  double &chisqrt, double &chisqrt_error);

void FitMinuit_Convolution_Combined_1set(Convolution_Tool sbtool, std::string fitName, std::string pdf_label, std::vector<double> &wgt_vector, std::vector<double> &wgt_error);
void FitMinuit_Convolution_Combined_1set_Log(Convolution_Tool sbtool, std::string fitName, std::string pdf_label, std::vector<double> &wgt_vector, std::vector<double> &wgt_error);
void FitMinuit_Convolution_Combined_difference(Convolution_Tool sbtool, std::string fitName, std::string pdf_label, std::vector<double> &wgt_vector, std::vector<double> &wgt_error);
void FitMinuit_Convolution_Combined_difference_Log(Convolution_Tool sbtool, std::string fitName, std::string pdf_label, std::vector<double> &wgt_vector, std::vector<double> &wgt_error);




double calc_ChiSq_For_ConvolutionTool_CV_Vertex(
Convolution_CryoRegions &CryoRegions,
  double InPut_Alwgt_region1,
  double InPut_Alwgt_region2,
  double InPut_Alwgt_region3,
  double InPut_Alwgt_region4,
   int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1, bool removeFirstandLastBin= true, bool isVertexZ=false);


void AppendtoLatex_FiveFigures(std::string output_name ,  std::string pdf_name_CV, int Figure_1_page_number, int Figure_2_page_number,
        int Figure_3_page_number, int Figure_5_page_number, int Figure_6_page_number, char *slideTitle);

std::vector<CryoVertex> GetCryoVertexVaribles_All();


double calc_ChiSq_For_ConvolutionTool_CV_Vertex_Combined_Full_Empty(
Convolution_CryoRegions &CryoRegions_Empty,
Convolution_CryoRegions &CryoRegions_Full,
  double InPut_Alwgt_region1_Empty,
  double InPut_Alwgt_region2_Empty,
  double InPut_Alwgt_region3_Empty,
  double InPut_Alwgt_region4_Empty,
  double InPut_Alwgt_region1_Full,
  double InPut_Alwgt_region2_Full,
  double InPut_Alwgt_region3_Full,
  double InPut_Alwgt_region4_Full,

   int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1, bool removeFirstandLastBin= true, bool isVertexZ=false);

	 double calc_LOG_ChiSq_For_ConvolutionTool_CV_Vertex_Combined_Full_Empty(
	 Convolution_CryoRegions &CryoRegions_Empty,
	 Convolution_CryoRegions &CryoRegions_Full,
	   double InPut_Alwgt_region1_Empty,
	   double InPut_Alwgt_region2_Empty,
	   double InPut_Alwgt_region3_Empty,
	   double InPut_Alwgt_region4_Empty,
	   double InPut_Alwgt_region1_Full,
	   double InPut_Alwgt_region2_Full,
	   double InPut_Alwgt_region3_Full,
	   double InPut_Alwgt_region4_Full,

	    int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1, bool removeFirstandLastBin= true, bool isVertexZ=false);




double EllipticparaboloidFunction_miniut(Double_t *x, Double_t *par);
double EllipticparaboloidFunction_miniut(double x, double y, double paraA, double paraB);
void Set_h1_Gobal(TH2D * input);
void Set_h2_Gobal(TH2D * input);

void calc_h1_Gobal_ChiSq_2D_Ellipticparaboloid(Int_t &npar, Double_t *gin, Double_t &fvar, Double_t *par, Int_t iflag);
void FitMinuit_h1_Gobal_Ellipticparaboloid(std::vector<double> &FitParas, std::vector<double> &FitParas_error );
void FillHist_Ellipticparaboloid(MnvH2D &h_Fill,double ParaA, double ParaB );
void calc_h1_Gobal_ChiSqLOG_2D_Ellipticparaboloid(Int_t &npar, Double_t *gin, Double_t &fvar, Double_t *par, Int_t iflag);

#endif
