// File: CrossSection_Normalization.h
// Brief: The header for CrossSection_Normalization.cxx
//  contains functions for normalizing the Cross Section
// Author: Christian Nguyen christian2nguyen@ufl.edu
// ========================================================================
#ifndef CROSSSECTION_NORMALIZATION_H
#define CROSSSECTION_NORMALIZATION_H

#include "HeliumCVUniverse.h"
#include "HeliumDefaults.h"
#include "HeliumUtils.h"
#include "PlotUtils/ChainWrapper.h"
#include <iostream>
#include "TMath.h"
#include <vector>
#include "Helium2DUtils.h"
#include <PlotUtils/MnvH1D.h>
#include <PlotUtils/MnvH2D.h>
#include <PlotUtils/MnvPlotter.h>
#include <MinervaUnfold/MnvUnfold.h>
#include <PlotUtils/MnvVertErrorBand.h>
#include <PlotUtils/MnvLatErrorBand.h>
#include <PlotUtils/MnvNormalization.h>
#include <PlotUtils/FluxReweighter.h>
#include "TMinuit.h"
#include "TFitter.h"
#include "TF1.h"

void POT_Normalize_2DCrossSection_Hist_InteractionOnly_DISBreakdown(
    CrossSection2D_Hist& inputCross_Hist, double normalize_MC_data);
////////////////////////////////////////////////////////////////////////////////
void POT_Normalize_CrossSection_Hist_InteractionOnly_DISBreakdown(
    CrossSection_Hist& inputCross_Hist, double normalize_MC_data);
////////////////////////////////////////////////////////////////////////////////
void POT_Normalize_CrossSection_Hist_InteractionOnly(
    CrossSection_Hist& inputCross_Hist, double normalize_MC_data);
////////////////////////////////////////////////////////////////////////////////
void POT_Normalize_CrossSection_Hist(CrossSection_Hist& inputCross_Hist,
                                     double normalize_MC_data,
                                     double normalize_fullData_emptyData = 1,
                                     bool dodata = false);
////////////////////////////////////////////////////////////////////////////////
void AddErrorBands_TOEffDom(CrossSection_Hist& inputCross_Hist);
////////////////////////////////////////////////////////////////////////////////
void AddErrorBands_TOEffDom(CrossSection2D_Hist& inputCross_Hist);
////////////////////////////////////////////////////////////////////////////////
void POT_Normalize_2DCrossSection_Hist(CrossSection2D_Hist& inputCross_Hist,
                                       double normalize_MC_data,
                                       double normalize_fullData_emptyData = 1,
                                       bool dodata = false);
////////////////////////////////////////////////////////////////////////////////
void POT_Normalize_CrossSection2D_Hist_Daisy(
    CrossSection2D_Hist_Daisy& inputCross_Hist, double normalize_MC_data);
////////////////////////////////////////////////////////////////////////////////
void Subtract_CrossSection_Hist(CrossSection_Hist& inputCross_Hist_Full,
                                CrossSection_Hist& inputCross_Hist_Empty);
////////////////////////////////////////////////////////////////////////////////
void Subtract_CrossSection_Hist_Interaction(
    CrossSection_Hist& inputCross_Hist_Full,
    CrossSection_Hist& inputCross_Hist_Empty);
////////////////////////////////////////////////////////////////////////////////
void Subtract_CrossSection_Hist(CrossSection2D_Hist& inputCross_Hist_Full,
                                CrossSection2D_Hist& inputCross_Hist_Empty);
////////////////////////////////////////////////////////////////////////////////
void Subtract_CrossSection_Hist_Interaction(
    CrossSection2D_Hist& inputCross_Hist_Full,
    CrossSection2D_Hist& inputCross_Hist_Empty);
////////////////////////////////////////////////////////////////////////////////
void Subtract_CrossSection_Hist_Interaction_DISBreakdown(
    CrossSection2D_Hist& inputCross_Hist_Full,
    CrossSection2D_Hist& inputCross_Hist_Empty);
////////////////////////////////////////////////////////////////////////////////
void POT_Normalize_CrossSection_Hist_noBG(
    CrossSection_Hist& inputCross_Hist, double normalize_MC_data,
    double normalize_fullData_emptyData = 1, bool dodata = false);
////////////////////////////////////////////////////////////////////////////////
void POT_Normalize_CrossSection_Hist_Daisy(
    CrossSection_Hist_Daisy& inputCross_Hist, double normalize_MC_data);
////////////////////////////////////////////////////////////////////////////////
void ApplyBGSubtration_Daisy(CrossSection_Hist_Daisy& inputCross_Hist);
////////////////////////////////////////////////////////////////////////////////
void UnfoldHist_Daisy(CrossSection_Hist_Daisy& inputCross_Hists_Daisy,
                      int num_iter);
////////////////////////////////////////////////////////////////////////////////
void UnfoldHist_Daisy2D(CrossSection2D_Hist_Daisy& inputCross_Hists_Daisy,
                        int num_iter);
////////////////////////////////////////////////////////////////////////////////
void MakeNumeratorEff_Daisy(CrossSection_Hist_Daisy& inputCross_Hists_Daisy);
////////////////////////////////////////////////////////////////////////////////
void MakeNumeratorEff_Daisy(CrossSection2D_Hist_Daisy& inputCross_Hists_Daisy);
////////////////////////////////////////////////////////////////////////////////
std::map<int, MnvH1D*> GetDaisyUnfoldedData(
    CrossSection_Hist_Daisy& inputCross_Hists_Daisy);
////////////////////////////////////////////////////////////////////////////////
std::map<int, MnvH2D*> GetDaisyUnfoldedData(
    CrossSection2D_Hist_Daisy& inputCross_Hists_Daisy);
////////////////////////////////////////////////////////////////////////////////
std::map<int, MnvH1D*> GetDaisyEff(
    CrossSection_Hist_Daisy& inputCross_Hists_Daisy);
////////////////////////////////////////////////////////////////////////////////
std::map<int, MnvH2D*> GetDaisyEff(
    CrossSection2D_Hist_Daisy& inputCross_Hists_Daisy);
////////////////////////////////////////////////////////////////////////////////
PlotUtils::MnvH2D* normalize2D(PlotUtils::MnvH2D* efficiencyCorrected,
                               PlotUtils::MnvH2D* fluxIntegral,
                               const double nNucleons, const double POT);
////////////////////////////////////////////////////////////////////////////////
void POT_Normalize_2DCrossSection_Hist_RECO_Data(
    CrossSection2D_Hist& inputCross_Hist, double normalize_MC_data,
    double normalize_fullData_emptyData = 1, bool dodata = false);
////////////////////////////////////////////////////////////////////////////////
void POT_Normalize_2DCrossSection_Hist_InteractionOnly(
    CrossSection2D_Hist& inputCross_Hist, double normalize_MC_data);
////////////////////////////////////////////////////////////////////////////////
PlotUtils::MnvH2D* UnfoldHist2D_new(PlotUtils::MnvH2D* h_folded,
                                    PlotUtils::MnvH2D* h_RECO,
                                    PlotUtils::MnvH2D* h_TRUTH,
                                    PlotUtils::MnvH2D* h_migration,
                                    int num_iter, bool addSystematics,
                                    bool useSysVariatedMigrations);
////////////////////////////////////////////////////////////////////////////////
PlotUtils::MnvH2D* UnfoldHist2D_new(PlotUtils::MnvH2D* h_folded,
                                    PlotUtils::MnvH2D* h_folded_MC,
                                    PlotUtils::MnvH2D* h_RECO,
                                    PlotUtils::MnvH2D* h_TRUTH,
                                    PlotUtils::MnvH2D* h_migration,
                                    int num_iter, bool addSystematics,
                                    bool useSysVariatedMigrations);
////////////////////////////////////////////////////////////////////////////////
MnvH2D* UnfoldHistOld(MnvH2D* h_data_nobck, MnvH2D* h_mc_nobck, MnvH2D* h_reco,
                      MnvH2D* h_generated, MnvH2D* h_migration, int num_iter,
                      MnvPlotter* mnvPlotter, char* pdf);
////////////////////////////////////////////////////////////////////////////////
PlotUtils::MnvH1D* UnfoldHist(PlotUtils::MnvH1D* h_folded,
                              PlotUtils::MnvH2D* h_migration, int num_iter);
////////////////////////////////////////////////////////////////////////////////
PlotUtils::MnvH1D* normalize(PlotUtils::MnvH1D* efficiencyCorrected,
                             PlotUtils::MnvH1D* fluxIntegral,
                             const double nNucleons, const double POT);
void ZeroDiagonal(TMatrixD& m);
////////////////////////////////////////////////////////////////////////////////
TMatrixD divideCovByHists(TMatrixD m, TH2D* num, TH2D* dem);
////////////////////////////////////////////////////////////////////////////////
CrossSection_MnvH2D_Map Generate_2DCrossSection_Hist_Map(
    TFile& file, CrossSection_name_Map Map);
TF1* GetSpline(std::string material);
////////////////////////////////////////////////////////////////////////////////
MnvH1D* MakeCrossSectionSpineHist(MnvH1D* originalHist, std::string material);
////////////////////////////////////////////////////////////////////////////////
MnvH1D* GetCrossSection_hist(MnvH1D* originalHist, std::string material);
////////////////////////////////////////////////////////////////////////////////
MnvH1D* MakeFluxHist(MnvH1D* originalHist, std::string material,
                     double ntargets, double potnorm);
////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_Daisy(CrossSection_Hist& Constuct_crosssection_Hists,
                        TFile& file, char* Name);
////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_2DDaisy(CrossSection2D_Hist& Constuct_crosssection_Hists,
                          TFile& file, char* Name);
////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_2DDaisy(CrossSection2D_Hist_Daisy& Daisy_crosssection_Hists,
                          TFile& file, char* Name);
////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_Daisy_Efficiency(
    CrossSection_Hist& Constuct_crosssection_Hists, TFile& file, char* Name);
////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_2DDaisy_Efficiency(
    CrossSection2D_Hist& Constuct_crosssection_Hists, TFile& file, char* Name);
////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_2DDaisy_Data(CrossSection2D_Hist& Constuct_crosssection_Hists,
                               TFile& file, char* Name, char* ProcessedName);
////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_2DDaisy_Data(
    CrossSection2D_Hist_Daisy& Daisy_crosssection_Hists, TFile& file,
    char* Name, char* ProcessedName);
////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_Daisy_Signal(CrossSection_Hist& Constuct_crosssection_Hists,
                               TFile& file, char* Name, char* ProcessedName);
////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_Daisy_RECO(CrossSection_Hist &Constuct_crosssection_Hists,
	                              TFile& file, char* Name, char *ProcessedName);
////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_2DDaisy_Data_RECO(
  CrossSection2D_Hist_Daisy &Daisy_crosssection_Hists,
   TFile& file, char* Name, char *ProcessedName);
////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_2DDaisy_Signal(
    CrossSection2D_Hist& Constuct_crosssection_Hists, TFile& file, char* Name,
    char* ProcessedName);
////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_Daisy(CrossSection_Hist_Daisy& Daisy_crosssection_Hists,
                        TFile& file, char* Name);
////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_Daisy_Efficiency(
    CrossSection_Hist_Daisy& Daisy_crosssection_Hists, TFile& file, char* Name);
////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_2D_Daisy_Efficiency(
    CrossSection2D_Hist_Daisy& Daisy_crosssection_Hists, TFile& file,
    char* Name);
////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_Daisy_Data_RECO(
    CrossSection_Hist_Daisy& Daisy_crosssection_Hists, TFile& file, char* Name,
    char* ProcessedName);
////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_Daisy_RECO(CrossSection_Hist_Daisy &Daisy_crosssection_Hists,
	TFile& file, char* Name, char *ProcessedName);
////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_Daisy_Data(CrossSection_Hist_Daisy& Daisy_crosssection_Hists,
                             TFile& file, char* Name, char* ProcessedName);
////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_Daisy_UnfoldedData(
    CrossSection_Hist& Constuct_crosssection_Hists, TFile& file, char* Name,
    char* ProcessedName);
////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_Daisy_UnfoldedData(
    CrossSection_Hist_Daisy& Daisy_crosssection_Hists, TFile& file, char* Name,
    char* ProcessedName);
////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_2DDaisy_UnfoldedData(
    CrossSection2D_Hist& Constuct_crosssection_Hists, TFile& file, char* Name,
    char* ProcessedName);
////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_2DDaisy_UnfoldedData(
    CrossSection2D_Hist_Daisy& Daisy_crosssection_Hists, TFile& file,
    char* Name, char* ProcessedName);
#endif
