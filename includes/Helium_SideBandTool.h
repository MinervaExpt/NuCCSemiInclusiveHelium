#ifndef HELIUM_SIDEBANDTOOL_H
#define HELIUM_SIDEBANDTOOL_H

#include <iomanip>
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

#include "TMinuit.h"
#include "TFitter.h"
#include "TFractionFitter.h"

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

#include "HeliumPlotUtils.h"
#include "CryoTankUtils.h"
#include "HeliumDefaults.h"
#include "HeliumUtils.h"
#include "Helium2DPlotUtils.h"

using namespace PlotUtils;

static const int nModels = 7;

struct XSec_Var {
  std::string name;

  MnvH1D* MnvH1D_data;
  MnvH1D* MnvH1D_mc_total;

  // 2 Hists for MC Models
  //      ind = 0 for Helium_Full
  //      ind = 1 for modified according to fit
  MnvH1D* MnvH1D_Helium[2];
  MnvH1D* MnvH1D_Aluminium[2];
  MnvH1D* MnvH1D_Carbon[2];
  MnvH1D* MnvH1D_Lead[2];
  MnvH1D* MnvH1D_Iron[2];
  MnvH1D* MnvH1D_Other[2];

  std::string Xaxis_Title;
};

struct HeliumSideBand {
  std::string name = "Default";
  std::string model_names[nModels];

  // Fit Variable
  MnvH1D* MnvH1D_data;
  MnvH1D* MnvH1D_mc_total;
  TH1D* TH1D_fit;  // Hist for fit
  std::string Xaxis_Title;
  FitHistName_Map HistName_Map;
  double POT_MC = 9999;
  double POT_Data = 9999;
  // 2 Hists for MC Models
  //      ind = 0 for Helium_Full
  //      ind = 1 for modified according to fit
  MnvH1D* MnvH1D_Helium[2];
  MnvH1D* MnvH1D_Aluminium[2];
  MnvH1D* MnvH1D_Carbon[2];
  MnvH1D* MnvH1D_Iron[2];
  MnvH1D* MnvH1D_Lead[2];
  MnvH1D* MnvH1D_Other[2];

  std::vector<TH1D*> data_all_universes;
  std::vector<TH1D*> mc_total_all_universes;
  std::vector<TH1D*> Helium_all_universes;
  std::vector<TH1D*> Aluminium_all_universes;
  std::vector<TH1D*> Carbon_all_universes;
  std::vector<TH1D*> Iron_all_universes;
  std::vector<TH1D*> Lead_all_universes;
  std::vector<TH1D*> Other_all_universes;

  std::vector<std::string> err_bands_data_all_universes;
  std::vector<std::string> err_bands_mc_total_all_universes;
  std::vector<std::string> err_bands_Helium_all_universes;
  std::vector<std::string> err_bands_Aluminium_all_universes;
  std::vector<std::string> err_bands_Carbon_all_universes;
  std::vector<std::string> err_bands_Iron_all_universes;
  std::vector<std::string> err_bands_Lead_all_universes;
  std::vector<std::string> err_bands_Other_all_universes;

  std::vector<int> hist_ind_data_all_universes;
  std::vector<int> hist_ind_mc_total_all_universes;
  std::vector<int> hist_ind_Helium_all_universes;
  std::vector<int> hist_ind_Aluminium_all_universes;
  std::vector<int> hist_ind_Carbon_all_universes;
  std::vector<int> hist_ind_Iron_all_universes;
  std::vector<int> hist_ind_Lead_all_universes;
  std::vector<int> hist_ind_Other_all_universes;

  // File for Fit Variable
  TFile* f_mc_fit = NULL;
  TFile* f_data_fit = NULL;

  // File for XSec Variable
  TFile* f_mc_var = NULL;
  TFile* f_data_var = NULL;

  XSec_Var muon_PT;
  XSec_Var muon_PZ;
  XSec_Var muon_theta;
  XSec_Var muon_E;

  XSec_Var Vertex_X;
  XSec_Var Vertex_Y;
  XSec_Var Vertex_Z;
  XSec_Var DistancetoEdge;

  std::vector<double> nData;
  std::vector<double> nMC;
  std::vector<double> nHelium;
  std::vector<double> nAluminium;
  std::vector<double> nCarbon;
  std::vector<double> nIron;
  std::vector<double> nLead;
  std::vector<double> nOther;
};

class Helium_SideBandTool {
 public:
  Helium_SideBandTool();
  Helium_SideBandTool(std::string input_PathtoRootMC_empty,
                      std::string input_PathtoRootData_empty,
                      std::string input_PathtoRootMC_full,
                      std::string input_PathtoRootData_full,
                      std::vector<std::string> histNames,
                      std::vector<Fit_Parms_Names> FitParms, double FullPOTMC,
                      double EmptyPOTMC, double FullPOTdata,
                      double EmptyPOTdata);

  ~Helium_SideBandTool();

  void SaveFitResults(double chisq, double par_values[1], double par_errors[1]);
  void ApplyFitResults();
  // void Plot();
  void Plot(std::string fitName, std::string pdf_label, std::string xaxislabel);
  void WriteFitResults(std::string file_name);
  void WriteStatistics();
  void init_POTScale_AllHist();
  void init_Tool_2playlist(std::string input_PathtoRootMC_empty,
                           std::string input_PathtoRootData_empty,
                           std::string input_PathtoRootMC_full,
                           std::string input_PathtoRootData_full,
                           std::vector<std::string> histNames,
                           std::vector<Fit_Parms_Names> FitParms,
                           double FullPOTMC, double EmptyPOTMC,
                           double FullPOTdata, double EmptyPOTdata);
  void init_POTScale_Full();
  void init_POTScale_Empty();
  void init_POTScale_Full_Empty();
  void init_Hist_Full_minus_Empty();
  void Plot_initHist(std::string Full_info, std::string Empty_info,
                     std::string axisName_fit);
  void Plot_AfterFitHist(std::string Full_info, std::string Empty_info,
                         std::string axisName_fit);
  void InputPDFLabel(std::string input);
  std::string GetName();

  ///////////////////////////////////
  /// Helium Side Band structs
  ///////////////////////////////////

  HeliumSideBand Helium_Full;
  HeliumSideBand Helium_Empty;
  HeliumSideBand Helium_Full_Empty;

  int N_Universes;
  int current_unv;
  bool MakeBinWidth = true;
  std::vector<double> ChiSq_before_fit;
  std::vector<double> ChiSq_before_fit_var;
  std::vector<double> ChiSq_after_fit;
  std::vector<double> wgt_Aluminium;
  std::vector<double> err_Aluminium;

 private:
  void OpenRootFiles_Empty(std::string input_PathtoRootMC,
                           std::string input_PathtoRootData);
  void OpenRootFiles_Full(std::string input_PathtoRootMC,
                          std::string input_PathtoRootData);
  void OpenRootFiles_Full_Empty(std::string input_PathtoRootMC,
                                std::string input_PathtoRootData);
  MnvH1D* GetMnvH1D(TFile* f, std::string var_name);
  MnvH2D* GetMnvH2D(TFile* f, std::string var_name);
  void initSideBands_2playlist();
  void initSideBand_FitHistograms(HeliumSideBand& sb);
  void init_fitHist_Full_Empty(HeliumSideBand& sb_full_empty,
                               HeliumSideBand& sb_full);
  void init_fit_dataHist(HeliumSideBand& sb, TFile* f, std::string dataHist);
  void GetAllUniverses(MnvH1D* mnvh1d_hist, std::vector<TH1D*>& all_universes,
                       std::vector<std::string>& err_bands,
                       std::vector<int>& hist_ind);
  void initSideBand_AllUniverses(HeliumSideBand& sb);
  void initSideBand_XSecHistograms(HeliumSideBand& sb);
  void initSideBand_XSecHistograms(HeliumSideBand& sb, XSec_Var& xsec_var,
                                   std::string Data_hist,
                                   std::string MChist_name);

  void initFull_EmptySideBand_XSecHistograms();
  void GetStatistics(HeliumSideBand& sb);
  void POTScale_SideBand(HeliumSideBand& sb);
  void SetNames(HeliumSideBand& sb, std::string name);
  void ApplyFitResults(HeliumSideBand& sb);
  void ApplyFitResults(XSec_Var& xsec_var);
  void ApplyFitResults(HeliumSideBand& sb_Full_Empty, HeliumSideBand& sb_Full,
                       HeliumSideBand& sb_Empty);
  void WriteStatistics(HeliumSideBand& sb);
  void FillHistName_Map(HeliumSideBand& sb, std::vector<std::string> histNames,
                        std::vector<Fit_Parms_Names> FitParms);
  void FillPotScaler(HeliumSideBand& sb, double POTscalerdata,
                     double POTscalerMC);
  double calc_Global_ChiSq(int unv, double POT_ratio);
  double calc_ChiSq_SideBand(HeliumSideBand& sb, double POT_ratio, int unv = 0,
                             bool isPartial = false, int min_bin = 1,
                             int max_bin = 1);

  // Plot Functions
  void DrawDataMCWithErrorBand(HeliumSideBand& sb, int toprint,
                               double POT_ratio, std::string pdf_label,
                               MnvPlotter* plotter, TCanvas* c,
                               std::string Hist_title);
  void Plot(HeliumSideBand& sb, int ind, double POT_ratio, std::string fitName,
            std::string pdf_label, std::string Hist_title,
            std::string xaxislabel, int index = 0);
  void Plot(HeliumSideBand& sb, double POT_ratio, std::string fitName,
            std::string pdf_label, std::string Hist_title,
            std::string xaxislabel);
  // void Plot(HeliumSideBand &sb, double POT_ratio, std::string fitName,
  // std::string pdf_label);
  //  void Plot(HeliumSideBand &sb, int ind, double POT_ratio, std::string
  //  fitName, std::string pdf_label);
  void Plot(std::string pdf_label, double POT_ratio, int ind,
            HeliumSideBand& sb, XSec_Var& xsec_var, std::string var_name,
            std::string Hist_title, std::string xaxislabel, int index = 0);
  void Plot(std::string pdf_label, int ind, double POT_ratio,
            std::string sb_name, std::string var_name, MnvH1D* data,
            MnvH1D* mc_total, MnvH1D* Helium, MnvH1D* Aluminium, MnvH1D* Carbon,
            MnvH1D* Iron, MnvH1D* Lead, MnvH1D* Other, std::string Hist_title,
            std::string xaxislabel, int index = 0);
  void ColorHists(TH1D* data, TH1D* Helium, TH1D* Aluminium, TH1D* Carbon,
                  TH1D* Iron, TH1D* Lead, TH1D* Other);
  double calc_ChiSq(TH1D* data, TH1D* Helium, TH1D* Aluminium, TH1D* Carbon,
                    TH1D* Iron, TH1D* Lead, TH1D* Other);
  void POTScale_SideBand_MC_total(HeliumSideBand& sb);
  void POTScale_SideBand_MC_Material(HeliumSideBand& sb, int ind);
  void POTScale_SideBand_Data(HeliumSideBand& sb);
  void POTScale_Var_MC_total(XSec_Var& xsec_var, double POTscaler);
  void POTScale_Var_Data(XSec_Var& xsec_var, double POTscaler);
  void POTScale_Var_MC_Material(XSec_Var& xsec_var, double POTscaler, int ind);
  void init_Full_Empty(HeliumSideBand& sb_full_empty, HeliumSideBand& sb_full);
  void init_POTScale_Var(XSec_Var& xsec_var, double POTscaler_MC,
                         double Potscaler_data);
  void init_POTScale_SideBand(HeliumSideBand& sb);

  void subtract_MC_total(HeliumSideBand& sb_toSubtract, HeliumSideBand& Empty);
  void subtract_MC_Material(HeliumSideBand& sb_toSubtract,
                            HeliumSideBand& Empty, int ind);
  void subtract_Data_total(HeliumSideBand& sb_toSubtract,
                           HeliumSideBand& Empty);

  void subtract_XSecHistograms_MCtotal(XSec_Var& xsec_var_Full,
                                       XSec_Var& xsec_var_Empty);
  void subtract_XSecHistograms_datatotal(XSec_Var& xsec_var_Full,
                                         XSec_Var& xsec_var_Empty);
  void subtract_XSecHistograms_MC_Material(XSec_Var& xsec_var_Full,
                                           XSec_Var& xsec_var_Empty, int ind);
  void init_subtract_XSecHistograms(XSec_Var& xsec_var_Full,
                                    XSec_Var& xsec_var_Empty);
  void Inti_Fit_Xaxis_label(HeliumSideBand& sb, std::string xaxislabel);
  void Inti_XSec_Xaxis_label(XSec_Var& xsec_var, std::string xaxislabel);
  void Inti_Xaxis_labels(HeliumSideBand& sb, std::string xaxislabel);
  void ApplyFitResults_Int_Full_Empty(XSec_Var& xsec_var_Full_Empty,
                                      XSec_Var& xsec_var_Full,
                                      XSec_Var& xsec_var_Empty);
  std::string var_name;

  std::string PDF_printingLabel_input;

  std::vector<int> Helium9_colorScheme = {
      TColor::GetColor("#EEFF00"),  // neonyellow,
      TColor::GetColor("#DF00FF"),  //'psychedelic Purple
      TColor::GetColor(43, 206, 72),  // green
      TColor::GetColor("#87CEEB"),  //'skyblue'
      TColor::GetColor("#0859C6"),  // blue
      TColor::GetColor("#654522"),  // yellowishbrown,
      TColor::GetColor("#ffc922"),  //'sunset yellow'
      TColor::GetColor("#FF0800"),  // 2 candy Apple
      TColor::GetColor("#90AD1C"),
      TColor::GetColor("#BABABA"),  // Gray
      TColor::GetColor("#00FFFF"),  //'aqua'
      TColor::GetColor("#F1B6DA"),  // pink
      TColor::GetColor("#00A86B"),  //'Jade'
      TColor::GetColor("#FAFAD2"),  // LightGoldenRodYellow
      TColor::GetColor("#800000"),  // Maroon
      TColor::GetColor("#555555"),  // dark grey
      TColor::GetColor(0, 153, 143),  // turquoise
      TColor::GetColor("#654522"),  // yellowishbrown,
      TColor::GetColor("#8db600"),  // yellowgreen,
      TColor::GetColor("#D3D3D3"),  //'lightgrey'
      TColor::GetColor("#90AD1C"),   TColor::GetColor("#CCDDAA")};
};
#endif
