#ifndef MAKE_CROSSSECTION_PLOTS_H
#define MAKE_CROSSSECTION_PLOTS_H

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

#include "TMinuit.h"
#include "TFitter.h"
#include <assert.h>

#include "../includes/HeliumPlotUtils.h"
#include "../includes/Helium2DPlotUtils.h"
#include "../includes/plot.h"
#include "../includes/CryoTankUtils.h"
#include "../includes/HeliumDefaults.h"
#include "../includes/HeliumUtils.h"
#include "../includes/Helium2DUtils.h"
#include "../Make_Plots/Common_plots.h"
#include "ExtractHeliumCrossSectionHists.h"
#include "../includes/Helium_reweightModels.h"
#include "../includes/CrossSection_Normalization.h"
#include "PlotUtils/TargetUtils.h"

std::vector<ME_helium_Playlists> GetPlayListVector();
std::vector<MuonVar> GetMUONVaribles_Total();
void PrintCrossSection_MapName(CrossSection_name_Map Map, char *outputLabel);
CrossSection_MnvH1D_Map Generate_CrossSection_Hist_Map(
    TFile &file, CrossSection_name_Map Map);

CrossSection_name_Map Generate_CrossSection_histsNames(MuonVar MuonVar_type,
                                                       std::string playlist,
                                                       bool isFUll);
Migration_MnvH2D_Map Generate_CrossSection_Mig_Hist_Map(
    TFile &file, std::vector<MuonVar> muon_vector);
void MakeCrossSectionPlots(CrossSection_MnvH1D_Map CrossSection_map,
                           std::string cross_section_units, std::string pdf,
                           bool MakeXaxisLOG, bool doBinwidth, MuonVar MuonVar,
                           char *Playlist_name);
void MakeCrossSectionPlots_Interaction(
    CrossSection_MnvH1D_Map CrossSection_map,
    CrossSection_MnvH1D_Map CrossSection_mapEmpty,
    std::string cross_section_units, std::string pdf, bool MakeXaxisLOG,
    bool doBinwidth, MuonVar MuonVar, char *Playlist_name, double POT_Data,
    double POT_MC, Genie_Models Modelinputs);

///////////// for flux fitting

double Gaussian2D_miniut(double x, double y, double A, double Xo, double sigmaX,
                         double Yo, double sigmaY);
void Set_h1_Gobal_flux(TH2D *input);
void Set_h2_Gobal_flux(TH2D *input);
void calc_two2D_Gobal_ChiSq_2DGaussian2D(Int_t &npar, Double_t *gin,
                                         Double_t &f, Double_t *par,
                                         Int_t iflag);
void calc_two2D_Gobal_ChiSq_2DGaussian2D_LOG(Int_t &npar, Double_t *gin,
                                             Double_t &f, Double_t *par,
                                             Int_t iflag);
void FitMinuit_h1_Gobal__2DGaussian2D(std::vector<double> &FitParas,
                                      std::vector<double> &FitParas_error,
                                      double &chi_2,
                                      std::vector<TGraph *> &outputTGraphs);
void Fit2Dhist(TH2D *HistA, TH2D *HistB, std::vector<double> &para_vector,
               std::vector<double> &wgt_error_vector, double &chi2,
               std::vector<TGraph *> &outputTGraphs);
///////////////////////////
void Set_Lambda_Penity(double input);
void Set_Tracker_Gobal_flux(TH1D *input);
void Set_Helium_Gobal_flux(TH1D *input);
void Set_Target_Gobal_flux(TH1D *input);
void Set_Tracker_Daisy_Gobal_flux(TH2D *input);
void Set_Gobal_Ratio(TH1D *input);
void Set_Daisy_fit(TH1D *input_helium_flux, TH1D *input_tracker_flux,
                   TH2D *Daisy_slices_flux);
void setYbins(TH2D *h_input);
void setXbins(TH2D *h_input);
void SetBins_usingflux_Tracker_Daisy();
void SetStatvector_usingflux_Tracker_Daisy();
void SetStatvector(TH2D *hist);
void clearStatvector();
void Fit2DPatals_fluxratioAttachhist(TH2D *HistPatalFlux, TH1D *HistTrackerFlux,
                                     TH1D *HistHeliumFlux);
void Fit2DPatals_fluxratio(std::vector<double> &FitParas,
                           std::vector<double> &FitParas_error, double &chi_2,
                           double Lambda);
void FitMinuit_h1_Gobal__FluxPatals(std::vector<double> &FitParas,
                                    std::vector<double> &FitParas_error,
                                    double &chi_2);
PlotUtils::MnvH1D *make_param_hist(std::string name,
                                   std::vector<double> parameters,
                                   std::vector<double> parameter_errors);
void Daisyfit_function(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par,
                       Int_t iflag);

#endif
