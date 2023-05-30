#ifndef CRYOTANK_EMPTYHELIUM_FIT_H
#define CRYOTANK_EMPTYHELIUM_FIT_H


#include "TTree.h"
#include "TFile.h"


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

#include "../includes/Helium_SideBandTool.h"
#include "../includes/Helium_3CryoRegionsSideBandTool.h"



#include "../Make_Plots/Common_plots.h"


std::vector<CryoVertex> GetCryoVertexVaribles();

std::vector<ME_helium_Playlists> GetPlayListVector();
void Kin(bool &cutsOn, bool &my_norm, bool &my_debug, const char *userDir);
//=============================================================================
void SetHeliumSideBandTool(Helium_SideBandTool sbtool_input) ;
//=============================================================================
void SetHelium3SideBandTool(Helium_3CryoRegionsSideBandTool sbtool_input);
//=============================================================================
void FitSideBands(Helium_SideBandTool sbtool,
  std::string fitName, std::string file_name, std::string pdf_label, double &wgt, double &wgt_error);
  //=============================================================================
void FitSideBands(Helium_3CryoRegionsSideBandTool sbtool, int FitFullorEmpty,
  std::string fitName, std::string file_name, std::string pdf_label,  std::vector<double> &wgt_vector, std::vector<double> &wgt_error_vector, double &error_onFit);
  //=============================================================================
void FitMinuit(Helium_SideBandTool sbtool, std::string fitName, std::string pdf_label, double &wgt, double &wgt_error);
//=============================================================================
void FitMinuit_EmptyLogchi2(Helium_SideBandTool sbtool, std::string fitName, std::string pdf_label, double &wgt, double &wgt_error, double &errorofFit);
//=============================================================================
void FitMinuit_Empty_RZ(Helium_SideBandTool sbtool, std::string fitName, std::string pdf_label, double &wgt, double &wgt_error);
//=============================================================================
void FitMinuit_Empty(Helium_3CryoRegionsSideBandTool sbtool, std::string fitName, std::string pdf_label, std::vector<double> &wgt_vector, std::vector<double> &wgt_error);
//=============================================================================
void FitMinuit_Empty_regionX(Helium_3CryoRegionsSideBandTool sbtool, std::string fitName, std::string pdf_label, std::vector<double> &wgt_vector, std::vector<double> &wgt_error);
//=============================================================================
void FitMinuit_Full(Helium_3CryoRegionsSideBandTool sbtool, std::string fitName, std::string pdf_label, std::vector<double> &wgt_vector, std::vector<double> &wgt_error);
//=============================================================================
void FitMinuit_Full_Empty(Helium_3CryoRegionsSideBandTool sbtool, std::string fitName, std::string pdf_label, std::vector<double> &wgt_vector, std::vector<double> &wgt_error);
//=============================================================================
void FitMinuit_Full_Empty_Al_He_Combinedfit(Helium_3CryoRegionsSideBandTool sbtool,
  std::string fitName, std::string pdf_label, std::vector<double> &wgt_vector, std::vector<double> &wgt_error);
  //=============================================================================
void  FitMinuit_Empty_regionXZ(Helium_3CryoRegionsSideBandTool sbtool, std::string fitName, std::string pdf_label, std::vector<double> &wgt_vector, std::vector<double> &wgt_error);
void calc_ChiSq(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag);
//=============================================================================
double calc_ChiSq_SideBand(HeliumSideBand  &sb, Double_t *par, int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1);
//=============================================================================
double calc_ChiSq_SideBand_CV(HeliumSideBand  &sb, Double_t *par, int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1);
double calc_ChiSq_For_SideBand_CV(Helium3SideBand  &sb, double InPut,
   int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1);
//=============================================================================
double calc_ChiSq_For_SideBand_CV(Helium3SideBand  &sb, double InPut_Alwgt, double InPut_Hewgt,
   int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1);
//=============================================================================
double calc_ChiSq_SideBand_region1_CV(Helium3SideBand  &sb, Double_t *par,
   int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1);
//=============================================================================
double calc_ChiSq_SideBand_UpstreamCap_He_Al_fit_CV(Helium3SideBand  &sb, Double_t *par,
   int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1);
//=============================================================================
double calc_ChiSq_SideBand_region2_CV(Helium3SideBand  &sb, Double_t *par,
  int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1);
//=============================================================================
double calc_ChiSq_SideBand_Barrel_He_Al_fit_CV(Helium3SideBand  &sb, Double_t *par,
    int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1);
//=============================================================================
double calc_ChiSq_SideBand_region3_CV(Helium3SideBand  &sb, Double_t *par,
  int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1);
//=============================================================================
double calc_ChiSq_SideBand_downstreamCap_He_Al_fit_CV(Helium3SideBand  &sb, Double_t *par,
    int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1);
//=============================================================================
double calc_ChiSq_SideBand_region4_CV(Helium3SideBand  &sb, Double_t *par,
  int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1);
//=============================================================================
double calc_ChiSq_SideBand_downstreamConcaveCap_He_Al_fit_CV(Helium3SideBand  &sb, Double_t *par,
    int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1);
//=============================================================================
double calc_ChiSq_For_SideBand_CV_Vertex_X_Region14(
  CryoRegion_HeliumNSideBand_Map InputMap, Double_t *InPut_Alwgt,
  int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1);
//=============================================================================
double calc_ChiSq_For_SideBand_CV_Vertex_X_Region14_LOG(
  CryoRegion_HeliumNSideBand_Map InputMap, Double_t *InPut_Alwgt,
  int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1);
//=============================================================================
double calc_ChiSq_For_SideBand_CV_Vertex_Y_Region14(
  CryoRegion_HeliumNSideBand_Map InputMap, Double_t *InPut_Alwgt,
  int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1);
//=============================================================================
double calc_ChiSq_For_SideBand_CV_Vertex_Y_Region14_LOG(
  CryoRegion_HeliumNSideBand_Map InputMap, Double_t *InPut_Alwgt,
  int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1);
  //=============================================================================
double calc_ChiSq_For_SideBand_CV_Vertex_Z_Region14(
    CryoRegion_HeliumNSideBand_Map InputMap, Double_t *InPut_Alwgt,
       int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1);
 //=============================================================================
double calc_ChiSq_For_SideBand_CV_Vertex_Z_Region14_LOG(
       CryoRegion_HeliumNSideBand_Map InputMap, Double_t *InPut_Alwgt,
          int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1);
//=============================================================================
void calc_ChiSq_Empty(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag);
//=============================================================================
void calc_ChiSq_Empty_Region14_LOG(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag);
//=============================================================================
void calc_ChiSq_Empty_Region14(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag);
//=============================================================================
void calc_ChiSq_Full(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag);
//=============================================================================
void calc_ChiSq_Full_Empty(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag);
//=============================================================================
void calc_ChiSq_FullandEmptyCombinedFit(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag);
//=============================================================================
void calc_ChiSq_Empty_regionX_Zonly(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag);
//=============================================================================
void calc_ChiSq_Empty_regionXZ(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag);
//=============================================================================
double calc_ChiSq_For_SideBand_CV_Vertex_X(
  Helium3SideBand  &sb_region1,
  Helium3SideBand  &sb_region2,
  Helium3SideBand  &sb_region3,
  Helium3SideBand  &sb_region4,
  double InPut_Alwgt_region1,
  double InPut_Alwgt_region2,
  double InPut_Alwgt_region3,
  double InPut_Alwgt_region4,
   int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1, bool removeFirstandLastBin=true);
//=============================================================================
double calc_ChiSqLog_For_SideBand_CV_Vertex_X(
  Helium3SideBand  &sb_region1,
  Helium3SideBand  &sb_region2,
  Helium3SideBand  &sb_region3,
  Helium3SideBand  &sb_region4,
  double InPut_Alwgt_region1,
  double InPut_Alwgt_region2,
  double InPut_Alwgt_region3,
  double InPut_Alwgt_region4,
  int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1, bool removeFirstandLastBin=true);
//=============================================================================
double calc_ChiSq_For_SideBand_CV_Vertex_Y(
  Helium3SideBand  &sb_region1,
  Helium3SideBand  &sb_region2,
  Helium3SideBand  &sb_region3,
  Helium3SideBand  &sb_region4,
  double InPut_Alwgt_region1,
  double InPut_Alwgt_region2,
  double InPut_Alwgt_region3,
  double InPut_Alwgt_region4,
  int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1, bool removeFirstandLastBin=true);

double calc_ChiSqLog_For_SideBand_CV_Vertex_Y(
    Helium3SideBand  &sb_region1,
    Helium3SideBand  &sb_region2,
    Helium3SideBand  &sb_region3,
    Helium3SideBand  &sb_region4,
    double InPut_Alwgt_region1,
    double InPut_Alwgt_region2,
    double InPut_Alwgt_region3,
    double InPut_Alwgt_region4,
    int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1, bool removeFirstandLastBin=true);

double calc_ChiSq_For_SideBand_CV_Vertex_Z(
  Helium3SideBand  &sb_region1,
  Helium3SideBand  &sb_region2,
  Helium3SideBand  &sb_region3,
  Helium3SideBand  &sb_region4,
  double InPut_Alwgt_region1,
  double InPut_Alwgt_region2,
  double InPut_Alwgt_region3,
  double InPut_Alwgt_region4,
  int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1, bool removeFirstandLastBin=true);

  double calc_ChiSqLog_For_SideBand_CV_Vertex_Z(
    Helium3SideBand  &sb_region1,
    Helium3SideBand  &sb_region2,
    Helium3SideBand  &sb_region3,
    Helium3SideBand  &sb_region4,
    double InPut_Alwgt_region1,
    double InPut_Alwgt_region2,
    double InPut_Alwgt_region3,
    double InPut_Alwgt_region4,
    int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1, bool removeFirstandLastBin=true);


double calc_ChiSq_For_SideBand_CV_Vertex_R(
  Helium3SideBand  &sb_region1,
  Helium3SideBand  &sb_region2,
  Helium3SideBand  &sb_region3,
  Helium3SideBand  &sb_region4,
  double InPut_Alwgt_region1,
  double InPut_Alwgt_region2,
  double InPut_Alwgt_region3,
  double InPut_Alwgt_region4,
  int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1, bool removeFirstandLastBin=true);

double calc_ChiSqLog_For_SideBand_CV_Vertex_R(
    Helium3SideBand  &sb_region1,
    Helium3SideBand  &sb_region2,
    Helium3SideBand  &sb_region3,
    Helium3SideBand  &sb_region4,
    double InPut_Alwgt_region1,
    double InPut_Alwgt_region2,
    double InPut_Alwgt_region3,
    double InPut_Alwgt_region4,
    int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1, bool removeFirstandLastBin=true);













#endif
