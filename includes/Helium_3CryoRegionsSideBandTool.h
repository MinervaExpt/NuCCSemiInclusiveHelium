#ifndef HELIUM_3CRYOREGIONSSIDEBANDTOOL_H
#define HELIUM_3CRYOREGIONSSIDEBANDTOOL_H

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
#include "TGraph2DErrors.h"
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
#include "TVirtualFitter.h"

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

static const int nModels3band = 7;

struct Resolution_hists {
  std::string name;
  MnvH1D* MnvH1D_Resolution_RECO;
  MnvH1D* MnvH1D_Resolution_TRUE_RECO;
  MnvH1D* MnvH1D_percentageResolution_RECO;
  MnvH1D* MnvH1D_percentageResolution_TRUE_RECO;
};

struct XSec_Var3band {
  std::string name;

  MnvH1D* MnvH1D_data;
  MnvH1D* MnvH1D_mc_total;

  // 2 Hists for MC Models
  //      ind = 0 for Before Fit
  //      ind = 1 for modified according to fit
  MnvH1D* MnvH1D_Helium[2];
  MnvH1D* MnvH1D_Aluminium[2];
  MnvH1D* MnvH1D_Carbon[2];
  MnvH1D* MnvH1D_Lead[2];
  MnvH1D* MnvH1D_Iron[2];
  MnvH1D* MnvH1D_Other[2];
  std::string Xaxis_Title;
};
struct XSec_VarNband {
  std::string name;
  std::string name_data;

  MnvH1D* MnvH1D_data;
  // 2 Hists for MC Models
  //      ind = 0 for Before Fit
  //      ind = 1 for modified according to fit
  MnvH1D* MnvH1D_Helium[2];
  MnvH1D* MnvH1D_Aluminium[2];
  MnvH1D* MnvH1D_Carbon[2];
  MnvH1D* MnvH1D_Lead[2];
  MnvH1D* MnvH1D_Iron[2];
  MnvH1D* MnvH1D_Other[2];
  std::string Xaxis_Title;
};

struct Helium3SideBand {
  std::string name = "Default";
  std::string model_names[nModels3band];

  // Fit Variable
  MnvH1D* MnvH1D_Vertex_X_data;
  MnvH1D* MnvH1D_Vertex_X_mc_total;
  std::string Xaxis_Title_Vertex_X = "Vertex X [mm]";
  MnvH1D* MnvH1D_Vertex_Y_data;
  MnvH1D* MnvH1D_Vertex_Y_mc_total;
  std::string Xaxis_Title_Vertex_Y = "Vertex Y [mm]";
  MnvH1D* MnvH1D_Vertex_Z_data;
  MnvH1D* MnvH1D_Vertex_Z_mc_total;
  std::string Xaxis_Title_Vertex_Z = "Vertex Z [mm]";
  MnvH1D* MnvH1D_Vertex_R_data;
  MnvH1D* MnvH1D_Vertex_R_mc_total;
  std::string Xaxis_Title_Vertex_R = "Vertex R [mm]";

  TH1D* TH1D_vertex_X_fit;  // Hist for fit
  TH1D* TH1D_vertex_Y_fit;  // Hist for fit
  TH1D* TH1D_vertex_Z_fit;  // Hist for fit
  TH1D* TH1D_vertex_R_fit;  // Hist for fit

  FitHistName_Map HistName_Map;
  // 2 Hists for MC Models
  //      ind = 0 Before Fit
  //      ind = 1 for modified according to fit
  MnvH1D* MnvH1D_Vertex_X_Helium[2];
  MnvH1D* MnvH1D_Vertex_X_Aluminium[2];
  MnvH1D* MnvH1D_Vertex_X_Carbon[2];
  MnvH1D* MnvH1D_Vertex_X_Iron[2];
  MnvH1D* MnvH1D_Vertex_X_Lead[2];
  MnvH1D* MnvH1D_Vertex_X_Other[2];

  MnvH1D* MnvH1D_Vertex_Y_Helium[2];
  MnvH1D* MnvH1D_Vertex_Y_Aluminium[2];
  MnvH1D* MnvH1D_Vertex_Y_Carbon[2];
  MnvH1D* MnvH1D_Vertex_Y_Iron[2];
  MnvH1D* MnvH1D_Vertex_Y_Lead[2];
  MnvH1D* MnvH1D_Vertex_Y_Other[2];

  MnvH1D* MnvH1D_Vertex_Z_Helium[2];
  MnvH1D* MnvH1D_Vertex_Z_Aluminium[2];
  MnvH1D* MnvH1D_Vertex_Z_Carbon[2];
  MnvH1D* MnvH1D_Vertex_Z_Iron[2];
  MnvH1D* MnvH1D_Vertex_Z_Lead[2];
  MnvH1D* MnvH1D_Vertex_Z_Other[2];

  MnvH1D* MnvH1D_Vertex_R_Helium[2];
  MnvH1D* MnvH1D_Vertex_R_Aluminium[2];
  MnvH1D* MnvH1D_Vertex_R_Carbon[2];
  MnvH1D* MnvH1D_Vertex_R_Iron[2];
  MnvH1D* MnvH1D_Vertex_R_Lead[2];
  MnvH1D* MnvH1D_Vertex_R_Other[2];

  double POT_MC = 9999;
  double POT_Data = 9999;

  MnvH2D* MnvH2D_Mig_vertex_X;
  MnvH2D* MnvH2D_Mig_vertex_Y;
  MnvH2D* MnvH2D_Mig_vertex_R;
  MnvH2D* MnvH2D_Mig_vertex_Z;

  std::vector<TH1D*> Vertex_X_data_all_universes;
  std::vector<TH1D*> Vertex_X_mc_total_all_universes;
  std::vector<TH1D*> Vertex_X_Helium_all_universes;
  std::vector<TH1D*> Vertex_X_Aluminium_all_universes;
  std::vector<TH1D*> Vertex_X_Carbon_all_universes;
  std::vector<TH1D*> Vertex_X_Iron_all_universes;
  std::vector<TH1D*> Vertex_X_Lead_all_universes;
  std::vector<TH1D*> Vertex_X_Other_all_universes;

  std::vector<TH1D*> Vertex_Y_data_all_universes;
  std::vector<TH1D*> Vertex_Y_mc_total_all_universes;
  std::vector<TH1D*> Vertex_Y_Helium_all_universes;
  std::vector<TH1D*> Vertex_Y_Aluminium_all_universes;
  std::vector<TH1D*> Vertex_Y_Carbon_all_universes;
  std::vector<TH1D*> Vertex_Y_Iron_all_universes;
  std::vector<TH1D*> Vertex_Y_Lead_all_universes;
  std::vector<TH1D*> Vertex_Y_Other_all_universes;

  std::vector<TH1D*> Vertex_Z_data_all_universes;
  std::vector<TH1D*> Vertex_Z_mc_total_all_universes;
  std::vector<TH1D*> Vertex_Z_Helium_all_universes;
  std::vector<TH1D*> Vertex_Z_Aluminium_all_universes;
  std::vector<TH1D*> Vertex_Z_Carbon_all_universes;
  std::vector<TH1D*> Vertex_Z_Iron_all_universes;
  std::vector<TH1D*> Vertex_Z_Lead_all_universes;
  std::vector<TH1D*> Vertex_Z_Other_all_universes;

  std::vector<TH1D*> Vertex_R_data_all_universes;
  std::vector<TH1D*> Vertex_R_mc_total_all_universes;
  std::vector<TH1D*> Vertex_R_Helium_all_universes;
  std::vector<TH1D*> Vertex_R_Aluminium_all_universes;
  std::vector<TH1D*> Vertex_R_Carbon_all_universes;
  std::vector<TH1D*> Vertex_R_Iron_all_universes;
  std::vector<TH1D*> Vertex_R_Lead_all_universes;
  std::vector<TH1D*> Vertex_R_Other_all_universes;

  std::vector<std::string> Vertex_X_err_bands_data_all_universes;
  std::vector<std::string> Vertex_X_err_bands_mc_total_all_universes;
  std::vector<std::string> Vertex_X_err_bands_Helium_all_universes;
  std::vector<std::string> Vertex_X_err_bands_Aluminium_all_universes;
  std::vector<std::string> Vertex_X_err_bands_Carbon_all_universes;
  std::vector<std::string> Vertex_X_err_bands_Iron_all_universes;
  std::vector<std::string> Vertex_X_err_bands_Lead_all_universes;
  std::vector<std::string> Vertex_X_err_bands_Other_all_universes;

  std::vector<std::string> Vertex_Y_err_bands_data_all_universes;
  std::vector<std::string> Vertex_Y_err_bands_mc_total_all_universes;
  std::vector<std::string> Vertex_Y_err_bands_Helium_all_universes;
  std::vector<std::string> Vertex_Y_err_bands_Aluminium_all_universes;
  std::vector<std::string> Vertex_Y_err_bands_Carbon_all_universes;
  std::vector<std::string> Vertex_Y_err_bands_Iron_all_universes;
  std::vector<std::string> Vertex_Y_err_bands_Lead_all_universes;
  std::vector<std::string> Vertex_Y_err_bands_Other_all_universes;

  std::vector<std::string> Vertex_Z_err_bands_data_all_universes;
  std::vector<std::string> Vertex_Z_err_bands_mc_total_all_universes;
  std::vector<std::string> Vertex_Z_err_bands_Helium_all_universes;
  std::vector<std::string> Vertex_Z_err_bands_Aluminium_all_universes;
  std::vector<std::string> Vertex_Z_err_bands_Carbon_all_universes;
  std::vector<std::string> Vertex_Z_err_bands_Iron_all_universes;
  std::vector<std::string> Vertex_Z_err_bands_Lead_all_universes;
  std::vector<std::string> Vertex_Z_err_bands_Other_all_universes;

  std::vector<std::string> Vertex_R_err_bands_data_all_universes;
  std::vector<std::string> Vertex_R_err_bands_mc_total_all_universes;
  std::vector<std::string> Vertex_R_err_bands_Helium_all_universes;
  std::vector<std::string> Vertex_R_err_bands_Aluminium_all_universes;
  std::vector<std::string> Vertex_R_err_bands_Carbon_all_universes;
  std::vector<std::string> Vertex_R_err_bands_Iron_all_universes;
  std::vector<std::string> Vertex_R_err_bands_Lead_all_universes;
  std::vector<std::string> Vertex_R_err_bands_Other_all_universes;

  std::vector<int> Vertex_X_hist_ind_data_all_universes;
  std::vector<int> Vertex_X_hist_ind_mc_total_all_universes;
  std::vector<int> Vertex_X_hist_ind_Helium_all_universes;
  std::vector<int> Vertex_X_hist_ind_Aluminium_all_universes;
  std::vector<int> Vertex_X_hist_ind_Carbon_all_universes;
  std::vector<int> Vertex_X_hist_ind_Iron_all_universes;
  std::vector<int> Vertex_X_hist_ind_Lead_all_universes;
  std::vector<int> Vertex_X_hist_ind_Other_all_universes;

  std::vector<int> Vertex_Y_hist_ind_data_all_universes;
  std::vector<int> Vertex_Y_hist_ind_mc_total_all_universes;
  std::vector<int> Vertex_Y_hist_ind_Helium_all_universes;
  std::vector<int> Vertex_Y_hist_ind_Aluminium_all_universes;
  std::vector<int> Vertex_Y_hist_ind_Carbon_all_universes;
  std::vector<int> Vertex_Y_hist_ind_Iron_all_universes;
  std::vector<int> Vertex_Y_hist_ind_Lead_all_universes;
  std::vector<int> Vertex_Y_hist_ind_Other_all_universes;

  std::vector<int> Vertex_Z_hist_ind_data_all_universes;
  std::vector<int> Vertex_Z_hist_ind_mc_total_all_universes;
  std::vector<int> Vertex_Z_hist_ind_Helium_all_universes;
  std::vector<int> Vertex_Z_hist_ind_Aluminium_all_universes;
  std::vector<int> Vertex_Z_hist_ind_Carbon_all_universes;
  std::vector<int> Vertex_Z_hist_ind_Iron_all_universes;
  std::vector<int> Vertex_Z_hist_ind_Lead_all_universes;
  std::vector<int> Vertex_Z_hist_ind_Other_all_universes;

  std::vector<int> Vertex_R_hist_ind_data_all_universes;
  std::vector<int> Vertex_R_hist_ind_mc_total_all_universes;
  std::vector<int> Vertex_R_hist_ind_Helium_all_universes;
  std::vector<int> Vertex_R_hist_ind_Aluminium_all_universes;
  std::vector<int> Vertex_R_hist_ind_Carbon_all_universes;
  std::vector<int> Vertex_R_hist_ind_Iron_all_universes;
  std::vector<int> Vertex_R_hist_ind_Lead_all_universes;
  std::vector<int> Vertex_R_hist_ind_Other_all_universes;

  // File for Fit Variable                       g
  //     TFile* f_mc_fit=NULL;
  //   TFile* f_data_fit=NULL;

  // File for XSec Variable
  // TFile* f_mc_var=NULL;
  // TFile* f_data_var=NULL;

  XSec_Var3band muon_PT;
  XSec_Var3band muon_PZ;
  XSec_Var3band muon_theta;
  XSec_Var3band muon_E;
  XSec_Var3band muon_doca;
  XSec_Var3band DistancetoEdge;
  XSec_Var3band SecTrk_doca;
  XSec_Var3band TrackLength;
  XSec_Var3band DistancetoUpstreamCap;
  XSec_Var3band DistancetoDownstreamCap;

  XSec_Var3band DistancetoUpstreamCap_RCut;
  XSec_Var3band DistancetoDownstreamCap_RCut;

  XSec_Var3band Vertex_Z_RCut;
  XSec_Var3band Vertex_X_RCut;
  XSec_Var3band Vertex_Y_RCut;
  XSec_Var3band Vertex_R_RCut;

  XSec_Var3band DistancetoEdge_Caps;
  XSec_Var3band DistancetoEdge_Barrel;

  XSec_Var3band Vertex_X_Resolution;
  XSec_Var3band Vertex_Y_Resolution;
  XSec_Var3band Vertex_Z_Resolution;
  XSec_Var3band Vertex_R_Resolution;

  Resolution_hists Resolution_hists_Vertex_X;
  Resolution_hists Resolution_hists_Vertex_Y;
  Resolution_hists Resolution_hists_Vertex_Z;
  Resolution_hists Resolution_hists_Vertex_R;

  std::vector<double> Vertex_X_nData;
  std::vector<double> Vertex_X_nMC;
  std::vector<double> Vertex_X_nHelium;
  std::vector<double> Vertex_X_nAluminium;
  std::vector<double> Vertex_X_nCarbon;
  std::vector<double> Vertex_X_nIron;
  std::vector<double> Vertex_X_nLead;
  std::vector<double> Vertex_X_nOther;

  std::vector<double> Vertex_Y_nData;
  std::vector<double> Vertex_Y_nMC;
  std::vector<double> Vertex_Y_nHelium;
  std::vector<double> Vertex_Y_nAluminium;
  std::vector<double> Vertex_Y_nCarbon;
  std::vector<double> Vertex_Y_nIron;
  std::vector<double> Vertex_Y_nLead;
  std::vector<double> Vertex_Y_nOther;

  std::vector<double> Vertex_Z_nData;
  std::vector<double> Vertex_Z_nMC;
  std::vector<double> Vertex_Z_nHelium;
  std::vector<double> Vertex_Z_nAluminium;
  std::vector<double> Vertex_Z_nCarbon;
  std::vector<double> Vertex_Z_nIron;
  std::vector<double> Vertex_Z_nLead;
  std::vector<double> Vertex_Z_nOther;

  std::vector<double> Vertex_R_nData;
  std::vector<double> Vertex_R_nMC;
  std::vector<double> Vertex_R_nHelium;
  std::vector<double> Vertex_R_nAluminium;
  std::vector<double> Vertex_R_nCarbon;
  std::vector<double> Vertex_R_nIron;
  std::vector<double> Vertex_R_nLead;
  std::vector<double> Vertex_R_nOther;
};
struct HeliumNSideBand {
  std::string name = "Default";
  std::string model_names[nModels3band];
  FitHistName_Map HistName_Map;
  // 2 Hists for MC Models
  //      ind = 0 Before Fit
  //      ind = 1 for modified according to fit
  MnvH1D* MnvH1D_Vertex_X_data;
  MnvH1D* MnvH1D_Vertex_Y_data;
  MnvH1D* MnvH1D_Vertex_Z_data;
  MnvH1D* MnvH1D_Vertex_R_data;

  MnvH1D* MnvH1D_Vertex_X_Helium[4];  // reco Measure  0 , true measure  1 ,
                                      // reco Fit 2,  true Fit 3
  MnvH1D* MnvH1D_Vertex_X_Aluminium[4];
  MnvH1D* MnvH1D_Vertex_X_Carbon[4];
  MnvH1D* MnvH1D_Vertex_X_Iron[4];
  MnvH1D* MnvH1D_Vertex_X_Lead[4];
  MnvH1D* MnvH1D_Vertex_X_Other[4];

  MnvH1D* MnvH1D_Vertex_Y_Helium[4];
  MnvH1D* MnvH1D_Vertex_Y_Aluminium[4];
  MnvH1D* MnvH1D_Vertex_Y_Carbon[4];
  MnvH1D* MnvH1D_Vertex_Y_Iron[4];
  MnvH1D* MnvH1D_Vertex_Y_Lead[4];
  MnvH1D* MnvH1D_Vertex_Y_Other[4];

  MnvH1D* MnvH1D_Vertex_Z_Helium[4];
  MnvH1D* MnvH1D_Vertex_Z_Aluminium[4];
  MnvH1D* MnvH1D_Vertex_Z_Carbon[4];
  MnvH1D* MnvH1D_Vertex_Z_Iron[4];
  MnvH1D* MnvH1D_Vertex_Z_Lead[4];
  MnvH1D* MnvH1D_Vertex_Z_Other[4];

  MnvH1D* MnvH1D_Vertex_R_Helium[4];
  MnvH1D* MnvH1D_Vertex_R_Aluminium[4];
  MnvH1D* MnvH1D_Vertex_R_Carbon[4];
  MnvH1D* MnvH1D_Vertex_R_Iron[4];
  MnvH1D* MnvH1D_Vertex_R_Lead[4];
  MnvH1D* MnvH1D_Vertex_R_Other[4];

  double POT_MC = 9999;
  double POT_Data = 9999;

  XSec_VarNband muon_PT;
  XSec_VarNband muon_PZ;
  XSec_VarNband muon_theta;
  XSec_VarNband muon_E;
  XSec_VarNband muon_doca;
  XSec_VarNband DistancetoEdge;
  XSec_VarNband SecTrk_doca;
  XSec_VarNband TrackLength;

  XSec_VarNband Vertex_X_Resolution;
  XSec_VarNband Vertex_Y_Resolution;
  XSec_VarNband Vertex_Z_Resolution;
  XSec_VarNband Vertex_R_Resolution;
};
typedef std::map<CryoTank_REGIONS, HeliumNSideBand>
    CryoRegion_HeliumNSideBand_Map;
class Helium_3CryoRegionsSideBandTool {
 public:
  Helium_3CryoRegionsSideBandTool();
  Helium_3CryoRegionsSideBandTool(
      ME_playlist_TFileMAP TFile_Map_Full_MC_input,
      ME_playlist_TFileMAP TFile_Map_Full_Data_input,
      ME_playlist_TFileMAP TFile_Map_Empty_MC_input,
      ME_playlist_TFileMAP TFile_Map_Empty_Data_input,
      Pot_MapList POTMap_Full_Data_input, Pot_MapList POTMap_Full_MC_input,
      Pot_MapList POTMap_Empty_Data_input, Pot_MapList POTMap_Empty_MC_input)
      : TFile_Map_Full_MC(TFile_Map_Full_MC_input),
        TFile_Map_Full_Data(TFile_Map_Full_Data_input),
        TFile_Map_Empty_MC(TFile_Map_Empty_MC_input),
        TFile_Map_Empty_Data(TFile_Map_Empty_Data_input),
        POTMap_Full_Data(POTMap_Full_Data_input),
        POTMap_Full_MC(POTMap_Full_MC_input),
        POTMap_Empty_Data(POTMap_Empty_Data_input),
        POTMap_Empty_MC(POTMap_Empty_MC_input) {}
  Helium_3CryoRegionsSideBandTool(
      ME_playlist_TFileMAP TFile_Map_Empty_MC_input,
      ME_playlist_TFileMAP TFile_Map_Empty_Data_input,
      Pot_MapList POTMap_Empty_Data_input, Pot_MapList POTMap_Empty_MC_input,
      Pot_MapList POTMap_Full_Data_input)
      : TFile_Map_Empty_MC(TFile_Map_Empty_MC_input),
        TFile_Map_Empty_Data(TFile_Map_Empty_Data_input),
        POTMap_Empty_Data(POTMap_Empty_Data_input),
        POTMap_Empty_MC(POTMap_Empty_MC_input),
        POTMap_Full_Data(POTMap_Full_Data_input) {}
  ~Helium_3CryoRegionsSideBandTool();

  void AddPlaylistTypetoSideBands(
      std::vector<ME_helium_Playlists> FullPlaylist_vector,
      std::vector<ME_helium_Playlists> EmptyPlaylist_vector);
  void Fill_Alwgt(std::vector<double> inputWgt,
                  std::vector<double> inputwgt_errors);
  void Fill_AlandHewgts(std::vector<double> inputWgt,
                        std::vector<double> inputWgt_errors);
  void SaveFitResults(double chisq, double par_values[4], double par_errors[4]);
  void SaveFitResults_Al_and_He(double chisq, double par_values[8],
                                double par_errors[8]);
  void ApplyFitResults();
  void ApplyFitResults_To_Full_EmptyFits();
  void ApplyFitResults_Al_He_combined();
  // void ApplyFitResults_Empty();
  void ApplyFitResults_toFitParmsOnly_Empty();
  void ApplyFitResults_toFitParmsOnly_Empty_regionX();
  void ApplyFitResults_toFitParmsOnly_Empty_regionXZ();
  void ApplyFitResults_toResolution();
  void ApplyFitResultsNSideBand(HeliumNSideBand& sb, double Alwgt);
  void ApplyFitResultsNSideBand(CryoRegion_HeliumNSideBand_Map& RegionMap,
                                std::vector<double> Alwgt_vector);
  void ApplyFitResultsNSideBand_Empty();
  void Plot(std::string fitName, std::string pdf_label, std::string xaxislabel);
  void WriteFitResults(std::string file_name);
  void MakeLatexSlides(std::string output_name);
  void MakeChiSqrt_table(std::string input_name, double scale);
  void WriteStatistics();
  void init_POTScale_AllHist();
  void init_Tool_2playlist(
      std::vector<ME_helium_Playlists> Full_PlaylistInput,
      std::vector<ME_helium_Playlists> Empty_PlaylistInput);
  void init_Tool_CompleteNuMEplaylist(
      std::vector<ME_helium_Playlists> Full_PlaylistInput,
      std::vector<ME_helium_Playlists> Empty_PlaylistInput);

  void init_POTScale_Full();
  void init_POTScale_Empty();
  void init_POTScale_Empty_RegionX();
  void init_POTScale_Empty_RegionXZ();
  void init_POTScale_Full_Empty();
  void init_Hist_Full_minus_Empty();
  void init_MC_PlaylistCombined_SideBand_Resolution_Histograms(
      ME_helium_Playlists Full_Playlist, ME_helium_Playlists Empty_Playlist);
  void init_MC_PlaylistCombined_Mig_Histograms(
      ME_helium_Playlists Full_Playlist, ME_helium_Playlists Empty_Playlist);
  void Plot_initHist(std::string Full_info, std::string Empty_info,
                     std::string axisName_fit);
  void Plot_AfterFitHist(std::string Full_info, std::string Empty_info,
                         std::string axisName_fit, int isCombinedFit = 0);
  void Plot_AfterFit_EMPTY_Hist(std::string title_info, std::string Empty_info,
                                int isCombinedFit = 0);
  void Plot_AfterFit_EMPTY_Hist_RegionX(std::string title_info,
                                        std::string Empty_info,
                                        int isCombinedFit = 3);
  void Plot_AfterFit_EMPTY_Hist_regionX_shift(std::string title_info,
                                              std::string Empty_info,
                                              int isCombinedFit = 3);
  void Plot_AfterFit_EMPTY_Hist_regionXZ_shift(std::string title_info,
                                               std::string Empty_info,
                                               int isCombinedFit = 3);

  void InputPDFLabel(std::string input);
  std::string GetName();
  void Vector_string_names(std::vector<std::string>& SideBand_name);
  void Vector_string_Fittingnames(std::vector<std::string>& SideBand_name);
  void initSideBands_EmptyDataplaylist(
      const ME_helium_Playlists Empty_Playlist);
  void GetShiftedMCHist_forEmpty(int index_i, int index_j, int index_k);
  void ConstructVertex_FitMC_shifted_HistName_Map(Helium3SideBand& sb,
                                                  std::string ExtraTag);
  void init_EMPTY_MCShifted_SideBand_FitHistograms(
      int i, int j, int k, const ME_helium_Playlists Empty_Playlist);
  void init_Tool_SingleEmptyplaylist(
      std::vector<ME_helium_Playlists> Empty_PlaylistInput);
  void ConstuctandFill_EmptyPlaylist_POT_forSideBands(
      ME_helium_Playlists EmptyPlaylist);
  void PlotCurrent_init_EmptyHist(std::string title_info,
                                  std::string Empty_info);
  void PlotCurrent_init_EmptyHist_regionX(std::string title_info,
                                          std::string Empty_info);
  void PlotCurrent_init_EmptyHist_regionXZ(std::string title_info,
                                           std::string Empty_info);
  void init_POTScale_FitVarsEmpty();
  void init_POTScale_FitVarsEmpty_RegionX();
  void init_POTScale_FitVarsEmpty_RegionXZ();
  void POTScale_New_Fit_EmptyMCHist();
  void POTScale_New_Fit_EmptyDataHist();
  void POTScale_New_Fit_EmptyMCHist_regionX();
  void POTScale_New_Fit_EmptyMCHist_regionXZ();
  void init_EMPTY_Combined_MCShifted_SideBand_FitHistograms(int i, int j,
                                                            int k);
  void init_EMPTY_Combined_MCShifted_SideBand_FitHistograms_RegionX(int i,
                                                                    int j,
                                                                    int k);
  void init_EMPTY_Combined_MCShifted_SideBand_FitHistograms_RegionXZ(int i,
                                                                     int j,
                                                                     int k);
  void GetEMPTYChiSqt_FitParmsBefore(double& chisqrt_X, double& chisqrt_Y,
                                     double& chisqrt_Z, double& chisqrt_R);
  void GetEMPTY_LOGChiSqt_FitParmsBefore(double& chisqrt_X, double& chisqrt_Y,
                                         double& chisqrt_Z, double& chisqrt_R);
  void GetEMPTYChiSqt_FitParmsBefore_regionX(double& chisqrt_X,
                                             double& chisqrt_Y,
                                             double& chisqrt_Z,
                                             double& chisqrt_R);
  void GetEMPTYChiSqt_FitParmsBefore_regionXZ(double& chisqrt_X,
                                              double& chisqrt_Y,
                                              double& chisqrt_Z,
                                              double& chisqrt_R);
  void GetEMPTYChiSqt_FitParmsAfter(double& chisqrt_X, double& chisqrt_Y,
                                    double& chisqrt_Z, double& chisqrt_R);
  void GetEMPTY_LOG_ChiSqt_FitParmsAfter(double& chisqrt_X, double& chisqrt_Y,
                                         double& chisqrt_Z, double& chisqrt_R);
  void GetEMPTYChiSqt_FitParmsAfter_regionX(double& chisqrt_X,
                                            double& chisqrt_Y,
                                            double& chisqrt_Z,
                                            double& chisqrt_R);
  void GetEMPTYChiSqt_FitParmsAfter_regionXZ(double& chisqrt_X,
                                             double& chisqrt_Y,
                                             double& chisqrt_Z,
                                             double& chisqrt_R);

  void init_Tool_CompleteEmptyplaylist(
      std::vector<ME_helium_Playlists> Empty_PlaylistInput,
      std::vector<ME_helium_Playlists> Full_PlaylistInput);
  void init_Tool_CompleteEmptyplaylist_Xregions(
      std::vector<ME_helium_Playlists> Empty_PlaylistInput);
  void init_Tool_CompleteEmptyplaylist_XZregions(
      std::vector<ME_helium_Playlists> Empty_PlaylistInput);
  void Clear_Al_wgt();
  void FillResolutionHistnames();
  void init_MC_PlaylistCombined_SideBand_Resolution_Histograms();
  void Plot_initResolutionHist(std::string title_info, std::string Full_info,
                               std::string Empty_info);
  void Plot_AfterFit_ResolutionHist(std::string title_info,
                                    std::string Full_info,
                                    std::string Empty_info);
  void plotFull_Empty_Resolutions(bool withfitorRMS);
  void plotFull_Resolutions(bool withfitorRMS);
  void plotEmpty_Resolutions(bool withfitorRMS);
  void Plot_All_MigHist(std::string Title_input);
  void Plot_Full_MigHist(std::string Title_input);
  void Plot_Empty_MigHist(std::string Title_input);
  void MakeRatioPlot_forXYZR(std::string Title, int ind);
  void WriteBeforeChi(std::string FileName);
  void Fill_vectors_file(std::vector<double>& Full_vector,
                         std::vector<double>& Empty_vector,
                         std::vector<double>& Full_Empty_vector,
                         std::string FileName);
  void MakeChiSqrt_table_beforeShiftincluded(
      std::string input_name, double scale,
      std::vector<double> Full_input_before,
      std::vector<double> Empty_input_before,
      std::vector<double> Full_Empty_input_before);
  void SetLogChi(bool input) { UseLogChi_Tool = input; };
  void SetAreaNormalized(bool input) { doAreaNormalized_Tool = input; };
  void initNRegionsNames_Empty();
  void PrintNRegionsNames_Empty();
  void initSideBands_CombinedEmptyDataplaylist();
  void initSideBands_CombinedEmptyDataplaylist_Combinedonly();
  void init_Region_Map_MaterialHists_Empty();
  void init_playlists(std::vector<ME_helium_Playlists> Full_PlaylistInput,
                      std::vector<ME_helium_Playlists> Empty_PlaylistInput);
  void Get_TotalPOT_scalers(std::vector<ME_helium_Playlists> FullPlaylist,
                            std::vector<ME_helium_Playlists> EmptyPlaylist,
                            double& FullMC_toFullData,
                            double& EmptyMC_toFullData,
                            double& EmptyData_toFullData);
  void FillPOT_NSideBandMap(CryoRegion_HeliumNSideBand_Map& inputMap,
                            double POT_MC_Data, double POT_Empty_data_toFUll);
  void FillPOT_HeliumNSideBand_Map();

  void Scale_intit_Empty_NSideBand_Map();
  void Scale_intit_Full_NSideBand_Map();
  void Scale_intit_Full_Empty_NSideBand_Map();
  void Plot_init_FitVar_Region14_Empty();
  void Plot_after_FitVar_Region14_Empty();
  ///////////////////////////////////
  /// Helium Side Band structs
  ///////////////////////////////////
  ///////////////////////////////////
  // SideBands to Fit
  ///////////////////////////////////
  Helium3SideBand Empty;
  /// Different Z regions
  Helium3SideBand Empty_UpstreamCap;
  Helium3SideBand Empty_Barrel;
  Helium3SideBand Empty_DownstreamCap;
  Helium3SideBand Empty_DownstreamConcaveCap;
  ////////////////////////////
  // Different X regions
  ///////////
  Helium3SideBand Empty_XCenter;
  Helium3SideBand Empty_XLeftShelf;
  Helium3SideBand Empty_XRightShelf;
  Helium3SideBand Empty_XoutsideEdges;

  /////////////////////////////////////
  /// I want the option if i want to fit to Full, Empty, or F-E
  //////////////////////////////////////
  Helium3SideBand Full;
  Helium3SideBand Full_UpstreamCap;
  Helium3SideBand Full_Barrel;
  Helium3SideBand Full_DownstreamCap;
  Helium3SideBand Full_DownstreamConcaveCap;

  Helium3SideBand Full_Empty;
  Helium3SideBand Full_Empty_UpstreamCap;
  Helium3SideBand Full_Empty_Barrel;
  Helium3SideBand Full_Empty_DownstreamCap;
  Helium3SideBand Full_Empty_DownstreamConcaveCap;

  CryoRegion_HeliumNSideBand_Map CryoRegionMap_Full;
  CryoRegion_HeliumNSideBand_Map CryoRegionMap_Empty;
  CryoRegion_HeliumNSideBand_Map CryoRegionMap_Full_Empty;

  std::vector<CryoTank_REGIONS> CryoRegion14_vector{
      Zregion1,  Zregion2,  Zregion3,  Zregion4, Zregion5,
      Zregion6,  Zregion7,  Zregion8,  Zregion9, Zregion10,
      Zregion11, Zregion12, Zregion13, Zregion14};

  int N_Universes = 1;  // assuming the CV is only being fitted
  int current_unv = 0;
  bool MakeBinWidth = true;
  bool IsHeandAlFit = false;
  bool UseLogChi_Tool = false;
  bool doAreaNormalized_Tool = false;
  bool set_ymax_forFitVars = true;

  double YaxisMax_X = 12.0;
  double YaxisMax_Y = 18.0;
  double YaxisMax_Z = 16.0;
  double YaxisMax_R = 45.0;

  double YaxisMax_PT = 9.0 * 1000;
  double YaxisMax_PZ = 1.2 * 1000;
  double YaxisMax_E = 1.0 * 1000;
  double YaxisMax_theta = 1.0 * 1000;

  CryoVertexDoubleMap ChiSqrt_beforeCryoVertex_EmptyMap;
  MuonVarDoubleMap ChiSqrt_beforeMuonVar_EmptyMap;
  CryoVertexDoubleMap ChiSqrt_beforeCryoVertex_FullMap;
  MuonVarDoubleMap ChiSqrt_beforeMuonVar_FullMap;
  CryoVertexDoubleMap ChiSqrt_beforeCryoVertex_Full_EmptyMap;
  MuonVarDoubleMap ChiSqrt_beforeMuonVar_Full_EmptyMap;

  CryoVertexDoubleMap ChiSqrt_afterCryoVertex_EmptyMap;
  MuonVarDoubleMap ChiSqrt_afterMuonVar_EmptyMap;
  CryoVertexDoubleMap ChiSqrt_afterCryoVertex_FullMap;
  MuonVarDoubleMap ChiSqrt_afterMuonVar_FullMap;
  CryoVertexDoubleMap ChiSqrt_afterCryoVertex_Full_EmptyMap;
  MuonVarDoubleMap ChiSqrt_afterMuonVar_Full_EmptyMap;

  std::vector<double> ChiSq_before_fit;
  std::vector<double> ChiSq_after_fit;
  std::vector<double> ChiSq_before_fit_var;

  std::vector<double> wgt_Aluminium;
  std::vector<double> err_Aluminium;

  std::vector<double> wgt_Helium;
  std::vector<double> err_Helium;

  std::vector<ME_helium_Playlists> Full_Playlist;
  std::vector<ME_helium_Playlists> Empty_Playlist;

  ME_playlist_TFileMAP TFile_Map_Full_MC;
  ME_playlist_TFileMAP TFile_Map_Full_Data;

  ME_playlist_TFileMAP TFile_Map_Empty_MC;
  ME_playlist_TFileMAP TFile_Map_Empty_Data;

  Pot_MapList POTMap_Empty_Data;
  Pot_MapList POTMap_Empty_MC;
  Pot_MapList POTMap_Full_Data;
  Pot_MapList POTMap_Full_MC;

 private:
  MnvH1D* GetMnvH1D(TFile* f, std::string var_name);
  MnvH2D* GetMnvH2D(TFile* f, std::string var_name);
  void initSideBand_FitHistograms(Helium3SideBand& sb, std::string Extra_Label,
                                  TFile* TFile_MC, TFile* TFile_Data);
  void initSideBand_FitHistograms(Helium3SideBand& sb, TFile* TFile_MC,
                                  TFile* TFile_Data);
  void initSideBands_2playlist(const ME_helium_Playlists Full_Playlist,
                               const ME_helium_Playlists Empty_Playlist);
  void init_fitHist_Full_Empty(Helium3SideBand& sb_full_empty,
                               Helium3SideBand& sb_full);
  void init_fit_dataHist(Helium3SideBand& sb, TFile* f, std::string dataHist);
  void GetAllUniverses(MnvH1D* mnvh1d_hist, std::vector<TH1D*>& all_universes,
                       std::vector<std::string>& err_bands,
                       std::vector<int>& hist_ind);
  void initSideBand_AllUniverses(Helium3SideBand& sb);
  void initSideBand_XSecHistograms(Helium3SideBand& sb, std::string ExtraLabel,
                                   TFile* TFile_MC, TFile* TFile_Data);
  void initSideBand_XSecHistograms(TFile* TFile_MC, TFile* TFile_Data,
                                   Helium3SideBand& sb, XSec_Var3band& xsec_var,
                                   std::string Data_hist,
                                   std::string MChist_name,
                                   std::string Xaxis_name,
                                   std::string Var_name);
  void initFull_EmptySideBand_XSecHistograms();
  void GetStatistics(Helium3SideBand& sb);
  void GetStatistics_Vertex_X(Helium3SideBand& sb);
  void GetStatistics_Vertex_Y(Helium3SideBand& sb);
  void GetStatistics_Vertex_Z(Helium3SideBand& sb);
  void GetStatistics_Vertex_R(Helium3SideBand& sb);
  void POTScale_SideBand(Helium3SideBand& sb);
  void SetNames(Helium3SideBand& sb, std::string name);
  void ApplyFitResults(Helium3SideBand& sb, double Alwgt);
  void ApplyFitResults(Helium3SideBand& sb, double Alwgt, double Hewgt);
  void ApplyFitResults(XSec_Var3band& xsec_var, double Alwgt);
  void ApplyFitResults(XSec_Var3band& xsec_var, double Alwgt, double Hewgt);
  void ApplyFitResults(XSec_VarNband& xsec_var, double Alwgt);
  void ApplyFitResults_Xsecvar(Helium3SideBand& sb, double Alwgt);
  void ApplyFitResults_Resolution(Helium3SideBand& sb, double Alwgt);
  void ApplyFitToBands(Helium3SideBand& sb_region1, Helium3SideBand& sb_region2,
                       Helium3SideBand& sb_region3, Helium3SideBand& sb_region4,
                       std::vector<double> Alwgt_vector);
  void ApplyFitToBands(Helium3SideBand& sb_upstreamCap,
                       Helium3SideBand& sb_barrel,
                       Helium3SideBand& sb_downstreamCap,
                       Helium3SideBand& sb_downstreamconcaveCap,
                       std::vector<double> Alwgt_vector,
                       std::vector<double> Hewgt_vector);
  void ApplyFitResults(Helium3SideBand& sb_Full_Empty, Helium3SideBand& sb_Full,
                       Helium3SideBand& sb_Empty);

  void ApplyFitToResolution_Bands(Helium3SideBand& sb_region1,
                                  Helium3SideBand& sb_region2,
                                  Helium3SideBand& sb_region3,
                                  Helium3SideBand& sb_region4,
                                  std::vector<double> Alwgt_vector);

  void WriteStatistics(Helium3SideBand& sb);
  void FillHistName_Map(Helium3SideBand& sb, std::vector<std::string> histNames,
                        std::vector<Fit_Parms_Names> FitParms);
  void ConstructVertex_FitHistName_Map(Helium3SideBand& sb,
                                       std::string ExtraTag);
  void FillPotScaler(Helium3SideBand& sb, double POTscalerdata,
                     double POTscalerMC);
  // double calc_Global_ChiSq(int unv, double POT_ratio, CryoVertexDoubleMap
  // ChiSqrt_fits);
  // double calc_ChiSq_SideBand(Helium3SideBand &sb, double POT_ratio, int unv =
  // 0, bool isPartial = false, int min_bin = 1, int max_bin = 1);
  double calc_ChiSq_SideBand_Vertex_X(Helium3SideBand& sb, double POT_ratio,
                                      int unv = 0, bool isPartial = false,
                                      int min_bin = 1, int max_bin = 1);
  double calc_ChiSq_SideBand_Vertex_Y(Helium3SideBand& sb, double POT_ratio,
                                      int unv = 0, bool isPartial = false,
                                      int min_bin = 1, int max_bin = 1);
  double calc_ChiSq_SideBand_Vertex_Z(Helium3SideBand& sb, double POT_ratio,
                                      int unv = 0, bool isPartial = false,
                                      int min_bin = 1, int max_bin = 1);
  double calc_ChiSq_SideBand_Vertex_R(Helium3SideBand& sb, double POT_ratio,
                                      int unv = 0, bool isPartial = false,
                                      int min_bin = 1, int max_bin = 1);
  // double cal_Chisq_Var(XSec_Var3band &xsec_var,  double POT_ratio, int ind );
  void initSideBand_FitDataHistograms(Helium3SideBand& sb, TFile* TFile_Data);
  void init_MCShifted_SideBand_FitHistograms(Helium3SideBand& sb,
                                             TFile* TFile_MC, int i, int j,
                                             int k);
  void init_MC_Mig_Histograms(Helium3SideBand& sb, std::string regionstring,
                              ME_playlist_TFileMAP TFile_Map_MC,
                              ME_helium_Playlists StartingPlaylist);
  void ConstuctandFill_Complete_EMPTYNuMEPlaylist_POT_forSideBands(
      std::vector<ME_helium_Playlists> EmptyPlaylist,
      std::vector<ME_helium_Playlists> FullPlaylist);
  void ConstuctandFill_Complete_EMPTYNuMEPlaylist_POT_forSideBands_Xregions(
      std::vector<ME_helium_Playlists> EmptyPlaylist);
  void ConstuctandFill_Complete_EMPTYNuMEPlaylist_POT_forSideBands_XZregions(
      std::vector<ME_helium_Playlists> EmptyPlaylist);

  void FillPOTScalar_sideBand(Helium3SideBand& sb);
  void FillPOTScalar(Helium3SideBand& sb, double POTMC_input,
                     double POTData_input);
  void init_POTScale_FittingVar_onlySideBand(Helium3SideBand& sb);
  // Plot Functions
  void DrawDataMCWithErrorBand(Helium3SideBand& sb, int toprint,
                               double POT_ratio, std::string pdf_label,
                               MnvPlotter* plotter, TCanvas* c,
                               std::string Hist_title);
  void Plot(Helium3SideBand& sb, int ind, double POT_ratio, std::string fitName,
            std::string pdf_label, std::string Hist_title,
            std::string xaxislabel, int index = 0);
  void Plot(Helium3SideBand& sb, double POT_ratio, std::string fitName,
            std::string pdf_label, std::string Hist_title,
            std::string xaxislabel);
  // void Plot(Helium3SideBand &sb, double POT_ratio, std::string fitName,
  // std::string pdf_label);
  //  void Plot(Helium3SideBand &sb, int ind, double POT_ratio, std::string
  //  fitName, std::string pdf_label);
  void Plot(std::string pdf_label, double POT_ratio, int ind,
            Helium3SideBand& sb, XSec_Var3band& xsec_var, std::string var_name,
            std::string Hist_title, std::string xaxislabel, int index = 0,
            bool applyMaxY = false, double MaxY = 999);
  void Plot(std::string pdf_label, int ind, double POT_ratio,
            std::string sb_name, std::string var_name, MnvH1D* data,
            MnvH1D* mc_total, MnvH1D* Helium, MnvH1D* Aluminium, MnvH1D* Carbon,
            MnvH1D* Iron, MnvH1D* Lead, MnvH1D* Other, std::string Hist_title,
            std::string xaxislabel, int index, bool UseLogChi,
            bool applyMaxY = false, double MaxY = 999);

  void Plot_NoStack(std::string pdf_label, int ind, double POT_ratio,
                    std::string sb_name, std::string var_name, MnvH1D* data,
                    MnvH1D* mc_total, MnvH1D* Helium, MnvH1D* Aluminium,
                    MnvH1D* Carbon, MnvH1D* Iron, MnvH1D* Lead, MnvH1D* Other,
                    std::string Hist_title, std::string xaxislabel, int index,
                    bool UseLogChi);

  void Plot_regions(
      std::string pdf_label, int ind, double POT_ratio, MnvH1D* data_region1,
      MnvH1D* mc_total_region1, MnvH1D* Helium_region1,
      MnvH1D* Aluminium_region1, MnvH1D* Carbon_region1, MnvH1D* Iron_region1,
      MnvH1D* Lead_region1, MnvH1D* Other_region1, MnvH1D* data_region2,
      MnvH1D* mc_total_region2, MnvH1D* Helium_region2,
      MnvH1D* Aluminium_region2, MnvH1D* Carbon_region2, MnvH1D* Iron_region2,
      MnvH1D* Lead_region2, MnvH1D* Other_region2, MnvH1D* data_region3,
      MnvH1D* mc_total_region3, MnvH1D* Helium_region3,
      MnvH1D* Aluminium_region3, MnvH1D* Carbon_region3, MnvH1D* Iron_region3,
      MnvH1D* Lead_region3, MnvH1D* Other_region3, MnvH1D* data_region4,
      MnvH1D* mc_total_region4, MnvH1D* Helium_region4,
      MnvH1D* Aluminium_region4, MnvH1D* Carbon_region4, MnvH1D* Iron_region4,
      MnvH1D* Lead_rcegion4, MnvH1D* Other_region4, std::string Hist_title,
      std::string xaxislabel, double& ChiSqrt, double& ChiSqrtAfter,
      int FitType, bool UseLogChi, bool doAreaNormalized, bool applyMaxY,
      double MaxY);

  void Plot_regions_addlinerFittoRatio(
      std::string pdf_label, int ind, double POT_ratio, MnvH1D* data_region1,
      MnvH1D* mc_total_region1, MnvH1D* Helium_region1,
      MnvH1D* Aluminium_region1, MnvH1D* Carbon_region1, MnvH1D* Iron_region1,
      MnvH1D* Lead_region1, MnvH1D* Other_region1,

      MnvH1D* data_region2, MnvH1D* mc_total_region2, MnvH1D* Helium_region2,
      MnvH1D* Aluminium_region2, MnvH1D* Carbon_region2, MnvH1D* Iron_region2,
      MnvH1D* Lead_region2, MnvH1D* Other_region2,

      MnvH1D* data_region3, MnvH1D* mc_total_region3, MnvH1D* Helium_region3,
      MnvH1D* Aluminium_region3, MnvH1D* Carbon_region3, MnvH1D* Iron_region3,
      MnvH1D* Lead_region3, MnvH1D* Other_region3,

      MnvH1D* data_region4, MnvH1D* mc_total_region4, MnvH1D* Helium_region4,
      MnvH1D* Aluminium_region4, MnvH1D* Carbon_region4, MnvH1D* Iron_region4,
      MnvH1D* Lead_region4, MnvH1D* Other_region4,

      std::string Hist_title, std::string xaxislabel, double& ChiSqrt,
      double& ChiSqrtAfter, int FitType, bool UseLogChi, bool doAreaNormalized,
      bool applyMaxY, double MaxY);

  void Plot_regions_noStack(
      std::string pdf_label, int ind, double POT_ratio, MnvH1D* data_region1,
      MnvH1D* mc_total_region1, MnvH1D* Helium_region1,
      MnvH1D* Aluminium_region1, MnvH1D* Carbon_region1, MnvH1D* Iron_region1,
      MnvH1D* Lead_region1, MnvH1D* Other_region1, MnvH1D* data_region2,
      MnvH1D* mc_total_region2, MnvH1D* Helium_region2,
      MnvH1D* Aluminium_region2, MnvH1D* Carbon_region2, MnvH1D* Iron_region2,
      MnvH1D* Lead_region2, MnvH1D* Other_region2, MnvH1D* data_region3,
      MnvH1D* mc_total_region3, MnvH1D* Helium_region3,
      MnvH1D* Aluminium_region3, MnvH1D* Carbon_region3, MnvH1D* Iron_region3,
      MnvH1D* Lead_region3, MnvH1D* Other_region3, MnvH1D* data_region4,
      MnvH1D* mc_total_region4, MnvH1D* Helium_region4,
      MnvH1D* Aluminium_region4, MnvH1D* Carbon_region4, MnvH1D* Iron_region4,
      MnvH1D* Lead_region4, MnvH1D* Other_region4, std::string Hist_title,
      std::string xaxislabel, double& ChiSqrt, double& ChiSqrtAfter,
      int FitType, bool UseLogChi, bool doAreaNormalized);

  void Plot_regions_addArrow(
      std::string pdf_label, int ind, double POT_ratio, MnvH1D* data_region1,
      MnvH1D* mc_total_region1, MnvH1D* Helium_region1,
      MnvH1D* Aluminium_region1, MnvH1D* Carbon_region1, MnvH1D* Iron_region1,
      MnvH1D* Lead_region1, MnvH1D* Other_region1, MnvH1D* data_region2,
      MnvH1D* mc_total_region2, MnvH1D* Helium_region2,
      MnvH1D* Aluminium_region2, MnvH1D* Carbon_region2, MnvH1D* Iron_region2,
      MnvH1D* Lead_region2, MnvH1D* Other_region2, MnvH1D* data_region3,
      MnvH1D* mc_total_region3, MnvH1D* Helium_region3,
      MnvH1D* Aluminium_region3, MnvH1D* Carbon_region3, MnvH1D* Iron_region3,
      MnvH1D* Lead_region3, MnvH1D* Other_region3, MnvH1D* data_region4,
      MnvH1D* mc_total_region4, MnvH1D* Helium_region4,
      MnvH1D* Aluminium_region4, MnvH1D* Carbon_region4, MnvH1D* Iron_region4,
      MnvH1D* Lead_region4, MnvH1D* Other_region4,

      std::string Hist_title, std::string xaxislabel, double& ChiSqrt,
      double& ChiSqrtAfter, int FitType, double cut_location, double y1_arrow,
      double y2_arrow, double arrow_length, bool UseLogChi,
      bool doAreaNormalized);

  void Plot_regionsNoStack_addArrow(
      std::string pdf_label, int ind, double POT_ratio, MnvH1D* data_region1,
      MnvH1D* mc_total_region1, MnvH1D* Helium_region1,
      MnvH1D* Aluminium_region1, MnvH1D* Carbon_region1, MnvH1D* Iron_region1,
      MnvH1D* Lead_region1, MnvH1D* Other_region1, MnvH1D* data_region2,
      MnvH1D* mc_total_region2, MnvH1D* Helium_region2,
      MnvH1D* Aluminium_region2, MnvH1D* Carbon_region2, MnvH1D* Iron_region2,
      MnvH1D* Lead_region2, MnvH1D* Other_region2, MnvH1D* data_region3,
      MnvH1D* mc_total_region3, MnvH1D* Helium_region3,
      MnvH1D* Aluminium_region3, MnvH1D* Carbon_region3, MnvH1D* Iron_region3,
      MnvH1D* Lead_region3, MnvH1D* Other_region3, MnvH1D* data_region4,
      MnvH1D* mc_total_region4, MnvH1D* Helium_region4,
      MnvH1D* Aluminium_region4, MnvH1D* Carbon_region4, MnvH1D* Iron_region4,
      MnvH1D* Lead_region4, MnvH1D* Other_region4,

      std::string Hist_title, std::string xaxislabel, double& ChiSqrt,
      double& ChiSqrtAfter, int FitType, double cut_location, double y1_arrow,
      double y2_arrow, double arrow_length, bool UseLogChi,
      bool doAreaNormalized);

  void Plot(std::string pdf_label, int ind, double POT_ratio,
            MnvH1D* data_UpstreamCap, MnvH1D* mc_total_UpstreamCap,
            MnvH1D* Helium_UpstreamCap, MnvH1D* Aluminium_UpstreamCap,
            MnvH1D* Carbon_UpstreamCap, MnvH1D* Iron_UpstreamCap,
            MnvH1D* Lead_UpstreamCap, MnvH1D* Other_UpstreamCap,
            MnvH1D* data_Barrel, MnvH1D* mc_total_Barrel, MnvH1D* Helium_Barrel,
            MnvH1D* Aluminium_Barrel, MnvH1D* Carbon_Barrel,
            MnvH1D* Iron_Barrel, MnvH1D* Lead_Barrel, MnvH1D* Other_Barrel,
            MnvH1D* data_DownstreamCap, MnvH1D* mc_total_DownstreamCap,
            MnvH1D* Helium_DownstreamCap, MnvH1D* Aluminium_DownstreamCap,
            MnvH1D* Carbon_DownstreamCap, MnvH1D* Iron_DownstreamCap,
            MnvH1D* Lead_DownstreamCap, MnvH1D* Other_DownstreamCap,
            MnvH1D* data_DownstreamConcaveCap,
            MnvH1D* mc_total_DownstreamConcaveCap,
            MnvH1D* Helium_DownstreamConcaveCap,
            MnvH1D* Aluminium_DownstreamConcaveCap,
            MnvH1D* Carbon_DownstreamConcaveCap,
            MnvH1D* Iron_DownstreamConcaveCap,
            MnvH1D* Lead_DownstreamConcaveCap,
            MnvH1D* Other_DownstreamConcaveCap, std::string Hist_title,
            std::string xaxislabel, double& ChiSqrt, double& ChiSqrtAfter,
            bool He_and_AlFit, bool UseLogChi, bool doAreaNormalized);

  void Plot_regions_noData(
      std::string pdf_label, int ind, double POT_ratio,
      MnvH1D* mc_total_region1, MnvH1D* Helium_region1,
      MnvH1D* Aluminium_region1, MnvH1D* Carbon_region1, MnvH1D* Iron_region1,
      MnvH1D* Lead_region1, MnvH1D* Other_region1,

      MnvH1D* mc_total_region2, MnvH1D* Helium_region2,
      MnvH1D* Aluminium_region2, MnvH1D* Carbon_region2, MnvH1D* Iron_region2,
      MnvH1D* Lead_region2, MnvH1D* Other_region2,

      MnvH1D* mc_total_region3, MnvH1D* Helium_region3,
      MnvH1D* Aluminium_region3, MnvH1D* Carbon_region3, MnvH1D* Iron_region3,
      MnvH1D* Lead_region3, MnvH1D* Other_region3,

      MnvH1D* mc_total_region4, MnvH1D* Helium_region4,
      MnvH1D* Aluminium_region4, MnvH1D* Carbon_region4, MnvH1D* Iron_region4,
      MnvH1D* Lead_region4, MnvH1D* Other_region4,

      std::string Hist_title, std::string xaxislabel);

  void Plot_regions_Region14(std::string pdf_label, CryoRegion_HistMap Data_Map,
                             CryoRegion_HistMap Helium_Map,
                             CryoRegion_HistMap Al_Map,
                             CryoRegion_HistMap Other_Map,
                             std::string Hist_title, std::string xaxislabel,
                             double& ChiSqrt, double& ChiSqrtAfter, int FitType,
                             bool UseLogChi, bool doAreaNormalized,
                             bool applyMaxY, double MaxY, int index);

  void Plot_Resolution_vertex_Material(std::string pdf_label, double POT_ratio,
                                       int ind, Helium3SideBand& sb_region1,
                                       Helium3SideBand& sb_region2,
                                       Helium3SideBand& sb_region3,
                                       Helium3SideBand& sb_region4,
                                       std::string histTitle);

  void PlotCombinedRegions_Fitting_Vars(
      Helium3SideBand& sb_region1, Helium3SideBand& sb_region2,
      Helium3SideBand& sb_region3, Helium3SideBand& sb_region4, int ind,
      double POT_ratio, std::string histTitle, std::string pdf_label,
      CryoVertexDoubleMap& chisqrt_map_before,
      CryoVertexDoubleMap& chisqrt_map_after, int FitType = 0);

  void Plot_Al_RatioMCANDData_Full_OverEmpty(
      std::string pdf_label, int ind, MnvH1D* data_region1_Full,
      MnvH1D* mc_total_region1_Full, MnvH1D* Aluminium_region1_Full,
      MnvH1D* data_region2_Full, MnvH1D* mc_total_region2_Full,
      MnvH1D* Aluminium_region2_Full, MnvH1D* data_region3_Full,
      MnvH1D* mc_total_region3_Full, MnvH1D* Aluminium_region3_Full,
      MnvH1D* data_region4_Full, MnvH1D* mc_total_region4_Full,
      MnvH1D* Aluminium_region4_Full,

      MnvH1D* data_region1_Empty, MnvH1D* mc_total_region1_Empty,
      MnvH1D* Aluminium_region1_Empty, MnvH1D* data_region2_Empty,
      MnvH1D* mc_total_region2_Empty, MnvH1D* Aluminium_region2_Empty,
      MnvH1D* data_region3_Empty, MnvH1D* mc_total_region3_Empty,
      MnvH1D* Aluminium_region3_Empty, MnvH1D* data_region4_Empty,
      MnvH1D* mc_total_region4_Empty, MnvH1D* Aluminium_region4_Empty,
      std::string Hist_title, std::string xaxislabel);

  void Plot_Al_RatioMCANDData_Full_OverEmpty_Combined(
      std::string pdf_label, int ind, MnvH1D* data_region1_Full,
      MnvH1D* mc_total_region1_Full, MnvH1D* Aluminium_region1_Full,
      MnvH1D* data_region2_Full, MnvH1D* mc_total_region2_Full,
      MnvH1D* Aluminium_region2_Full, MnvH1D* data_region3_Full,
      MnvH1D* mc_total_region3_Full, MnvH1D* Aluminium_region3_Full,
      MnvH1D* data_region4_Full, MnvH1D* mc_total_region4_Full,
      MnvH1D* Aluminium_region4_Full,

      MnvH1D* data_region1_Empty, MnvH1D* mc_total_region1_Empty,
      MnvH1D* Aluminium_region1_Empty, MnvH1D* data_region2_Empty,
      MnvH1D* mc_total_region2_Empty, MnvH1D* Aluminium_region2_Empty,
      MnvH1D* data_region3_Empty, MnvH1D* mc_total_region3_Empty,
      MnvH1D* Aluminium_region3_Empty, MnvH1D* data_region4_Empty,
      MnvH1D* mc_total_region4_Empty, MnvH1D* Aluminium_region4_Empty,
      std::string Hist_title, std::string xaxislabel);

  void PlotCombinedRegions_Fitting_Vars_NoStack(
      Helium3SideBand& sb_region1, Helium3SideBand& sb_region2,
      Helium3SideBand& sb_region3, Helium3SideBand& sb_region4, int ind,
      double POT_ratio, std::string histTitle, std::string pdf_label,
      CryoVertexDoubleMap& chisqrt_map_before,
      CryoVertexDoubleMap& chisqrt_map_after, int fitType = 0);

  void Plot_4RegionsVar(std::string pdf_label, double POT_ratio, int ind,
                        Helium3SideBand& sb_region1,
                        Helium3SideBand& sb_region2,
                        Helium3SideBand& sb_region3,
                        Helium3SideBand& sb_region4, std::string histTitle,
                        CryoVertexDoubleMap& chisqrt_mapvertex_before,
                        MuonVarDoubleMap& chisqrt_MuonVar_before,
                        CryoVertexDoubleMap& chisqrt_mapvertex_after,
                        MuonVarDoubleMap& chisqrt_MuonVar_after,
                        int FitType = 0);

  void Plot_4RegionsVar_noStack(
      std::string pdf_label, double POT_ratio, int ind,
      Helium3SideBand& sb_region1, Helium3SideBand& sb_region2,
      Helium3SideBand& sb_region3, Helium3SideBand& sb_region4,
      std::string histTitle, CryoVertexDoubleMap& chisqrt_mapvertex_before,
      MuonVarDoubleMap& chisqrt_MuonVar_before,
      CryoVertexDoubleMap& chisqrt_mapvertex_after,
      MuonVarDoubleMap& chisqrt_MuonVar_after, int FitType = 0);

  void plot_Resolutions(Helium3SideBand& sb, std::string pdf_label,
                        bool withfitorRMS, std::string Hist_title_sideband);

  void Plot_Resolutions(Resolution_hists hists, std::string pdf_label,
                        std::string Hist_title, std::string xaxislabel,
                        bool withfitorRMS);

  void Plot_Resolution_HistwithError(MnvH1D* input_hist, std::string pdf_label,
                                     std::string Hist_title,
                                     std::string xaxislabel, bool withfitorRMS,
                                     bool PrintRMS_percentage);

  void Plot_MigHist(MnvH2D* hist, std::string Title_string,
                    std::string xaxislabel_string,
                    std::string yaxislabel_string,
                    std::string zaxislabel_string, std::string pdf_label);

  void Plot_MigHist_RowNormalize(MnvH2D* hist, std::string Title_string,
                                 std::string xaxislabel_string,
                                 std::string yaxislabel_string,
                                 std::string zaxislabel_string,
                                 std::string pdf_label);

  void Plot_MigHist_ColNormalize(MnvH2D* hist, std::string Title_string,
                                 std::string xaxislabel_string,
                                 std::string yaxislabel_string,
                                 std::string zaxislabel_string,
                                 std::string pdf_label);

  void Plot_MigHist(Helium3SideBand& sb, std::string pdf_label,
                    std::string Title_input);

  void AppendtoLatex(std::string output_name, std::string pdf_name_CV,
                     int Figure_1_page_number, int Figure_2_page_number,
                     int Figure_3_page_number, std::string slideTitle);

  void MakeLatexChiSqrt_table(std::string output_name,
                              std::string CryoTank_status,
                              std::vector<std::string> VectorName,
                              std::vector<double> Chisqt_Before,
                              std::vector<double> Chisqt_After,
                              std::vector<double> NDF, double scale);

  void MakeLatexChiSqrt_table_new(std::string output_name,
                                  std::string CryoTank_status,
                                  std::vector<std::string> VectorName,
                                  std::vector<double> Chisqt_Before,
                                  std::vector<double> Chisqt_shifted,
                                  std::vector<double> Chisqt_shifted_weighted,
                                  std::vector<double> NDF, double scale);

  void Fill_ndf_vars(Helium3SideBand& sb, std::vector<double>& ndf_vector);
  void Fill_ndf_Fitting(Helium3SideBand& sb, std::vector<double>& ndf_vector);
  void Fill_ChiSqt(std::vector<double>& Full_Chisqt_before,
                   std::vector<double>& Full_Chisqt_after,
                   std::vector<double>& Empty_Chisqt_before,
                   std::vector<double>& Empty_Chisqt_after,
                   std::vector<double>& Full_Empty_Chisqt_before,
                   std::vector<double>& Full_Empty_Chisqt_after);

  void Fill_ChiSqt_Empty(std::vector<double>& Empty_Chisqt_before,
                         std::vector<double>& Empty_Chisqt_after);

  void MakeChiSqrt_table_vertex_Empty(std::string input_name,
                                      std::vector<double> beforeChi_zeroshift,
                                      std::vector<double> afterChi_zeroshift,
                                      double scale = 1.0);

  void ColorHists(TH1D* data, TH1D* Helium, TH1D* Aluminium, TH1D* Carbon,
                  TH1D* Iron, TH1D* Lead, TH1D* Other);
  void ColorHistsForLines(TH1D* data, TH1D* Helium, TH1D* Aluminium,
                          TH1D* Carbon, TH1D* Iron, TH1D* Lead, TH1D* Other);
  void ColorHists(TH1D* Carbon, TH1D* Iron, TH1D* Lead, TH1D* Other);
  void ColorHistsForLines(TH1D* Carbon, TH1D* Iron, TH1D* Lead, TH1D* Other);
  void ColorData(TH1D* data);
  void Color_HeliumHists(TH1D* Helium_UpsteamCap, TH1D* Helium_Barrel,
                         TH1D* Helium_DownstreamCap,
                         TH1D* Helium_DownstreamConcaveCap);
  void Color_HeliumHistsForLines(TH1D* Helium_UpsteamCap, TH1D* Helium_Barrel,
                                 TH1D* Helium_DownstreamCap,
                                 TH1D* Helium_DownstreamConcaveCap);
  void Color_AluminiumHists(TH1D* Aluminium_UpsteamCap, TH1D* Aluminium_Barrel,
                            TH1D* Aluminium_DownstreamCap,
                            TH1D* Aluminium_DownstreamConcaveCap);
  void Color_AluminiumHistsForLines(TH1D* Aluminium_UpsteamCap,
                                    TH1D* Aluminium_Barrel,
                                    TH1D* Aluminium_DownstreamCap,
                                    TH1D* Aluminium_DownstreamConcaveCap);
  double calc_ChiSq(TH1D* data, TH1D* Helium, TH1D* Aluminium, TH1D* Carbon,
                    TH1D* Iron, TH1D* Lead, TH1D* Other);
  double calc_LogChiSq(TH1D* data, TH1D* Helium, TH1D* Aluminium, TH1D* Carbon,
                       TH1D* Lead, TH1D* Iron, TH1D* Other);
  double calc_ChiSq(TH1D* data, TH1D* Helium_upstream, TH1D* Helium_barrel,
                    TH1D* Helium_downstream, TH1D* Helium_downstreamconcave,
                    TH1D* Aluminium_upstream, TH1D* Aluminium_barrel,
                    TH1D* Aluminium_downstream,
                    TH1D* Aluminium_downstreamconcave, TH1D* Carbon, TH1D* Lead,
                    TH1D* Iron, TH1D* Other);

  double calc_ChiSq(CryoRegion_HistMap Data_Map, CryoRegion_HistMap Helium_Map,
                    CryoRegion_HistMap Al_Map, CryoRegion_HistMap Other_Map);

  double calc_ChiSq_Log(CryoRegion_HistMap Data_Map,
                        CryoRegion_HistMap Helium_Map,
                        CryoRegion_HistMap Al_Map,
                        CryoRegion_HistMap Other_Map);

  double calc_LogChiSq(TH1D* data, TH1D* Helium_upstream, TH1D* Helium_barrel,
                       TH1D* Helium_downstream, TH1D* Helium_downstreamconcave,
                       TH1D* Aluminium_upstream, TH1D* Aluminium_barrel,
                       TH1D* Aluminium_downstream,
                       TH1D* Aluminium_downstreamconcave, TH1D* Carbon,
                       TH1D* Lead, TH1D* Iron, TH1D* Other);

  void ConstuctandFill2Playlist_POT_forSideBands(
      ME_helium_Playlists FullPlaylist, ME_helium_Playlists EmptyPlaylist);
  void ConstuctandFill_Complete_NuMEPlaylist_POT_forSideBands(
      std::vector<ME_helium_Playlists> FullPlaylist,
      std::vector<ME_helium_Playlists> EmptyPlaylist);
  void POTScale_SideBand_MC_total(Helium3SideBand& sb);
  void POTScale_SideBand_MC_Material(Helium3SideBand& sb, int ind);
  void POTScale_SideBand_MC_Material(HeliumNSideBand& sb, int ind);
  void POTScale_SideBand_MC_Material_FitVars(HeliumNSideBand& sb, int ind);
  void POTScale_SideBand_Data(Helium3SideBand& sb);
  void POTScale_SideBand_Data(HeliumNSideBand& sb);
  void POTScale_Var_MC_total(XSec_Var3band& xsec_var, double POTscaler);
  void POTScale_Var_Data(XSec_Var3band& xsec_var, double POTscaler);
  void POTScale_Var_Data(XSec_VarNband& xsec_var, double POTscaler);
  void POTScale_Var_MC_Material(XSec_Var3band& xsec_var, double POTscaler,
                                int ind);
  void POTScale_Var_MC_Material(XSec_VarNband& xsec_var, double POTscaler,
                                int ind);
  void init_Full_Empty(Helium3SideBand& sb_full_empty,
                       Helium3SideBand& sb_full);

  void init_POTScale_Var(XSec_Var3band& xsec_var, double POTscaler_MC,
                         double Potscaler_data);
  void init_POTScale_Var(XSec_VarNband& xsec_var, double POTscaler_MC,
                         double Potscaler_data);
  void init_POTScale_SideBand_Vars(Helium3SideBand& sb);
  void init_POTScale_SideBand(Helium3SideBand& sb);

  void subtract_MC_total(Helium3SideBand& sb_toSubtract,
                         Helium3SideBand& Empty);
  void subtract_MC_Material(Helium3SideBand& sb_toSubtract,
                            Helium3SideBand& Empty, int ind);
  void subtract_Data_total(Helium3SideBand& sb_toSubtract,
                           Helium3SideBand& Empty);

  void subtract_XSecHistograms_MCtotal(XSec_Var3band& xsec_var_Full,
                                       XSec_Var3band& xsec_var_Empty);
  void subtract_XSecHistograms_datatotal(XSec_Var3band& xsec_var_Full,
                                         XSec_Var3band& xsec_var_Empty);
  void subtract_XSecHistograms_MC_Material(XSec_Var3band& xsec_var_Full,
                                           XSec_Var3band& xsec_var_Empty,
                                           int ind);
  void init_subtract_XSecHistograms(XSec_Var3band& xsec_var_Full,
                                    XSec_Var3band& xsec_var_Empty);
  void Inti_XSec_Xaxis_label(XSec_Var3band& xsec_var, std::string xaxislabel);
  void Inti_Xaxis_labels(Helium3SideBand& sb, std::string xaxislabel);
  void ApplyFitResults_Int_Full_Empty(XSec_Var3band& xsec_var_Full_Empty,
                                      XSec_Var3band& xsec_var_Full,
                                      XSec_Var3band& xsec_var_Empty);
  std::string var_name;
  void initSideBand_FitHistogramsFromTFileMap(
      Helium3SideBand& sb, ME_playlist_TFileMAP TFile_Map_MC,
      ME_playlist_TFileMAP TFile_Map_Data,
      ME_helium_Playlists StartingPlaylist);
  void initSideBands_Multipleplaylists(ME_helium_Playlists Rull_Playlist,
                                       ME_helium_Playlists Empty_Playlist);
  void initSideBands_Multipleplaylists_Xregions(
      ME_helium_Playlists Empty_Playlist);
  void initSideBandFromTFileMap_XSecHistograms(
      ME_playlist_TFileMAP TFile_Map_MC, ME_playlist_TFileMAP TFile_Map_Data,
      Helium3SideBand& sb, XSec_Var3band& xsec_var, std::string Data_hist,
      std::string MChist_name, std::string Xaxis_name, std::string Var_name,
      ME_helium_Playlists StartingPlaylist);
  void initNSideBandFromTFileMap_XSecHistograms_data(
      ME_playlist_TFileMAP TFile_Map_Data, HeliumNSideBand& sb,
      XSec_VarNband& xsec_var, ME_helium_Playlists StartingPlaylist);

  void initNSideBandFromTFileMap_XSecHistograms_MC(
      ME_playlist_TFileMAP TFile_Map_MC, HeliumNSideBand& sb,
      XSec_VarNband& xsec_var, ME_helium_Playlists StartingPlaylist);

  void initSideBand_XSecHistograms(Helium3SideBand& sb, std::string ExtraLabel,
                                   ME_playlist_TFileMAP TFile_Map_MC,
                                   ME_playlist_TFileMAP TFile_Map_Data,
                                   ME_helium_Playlists StartingPlaylist);
  void ConstructVertex_FitHistName_MapData(Helium3SideBand& sb,
                                           std::string ExtraTag);
  void ApplyFitResults_toFitParsOnly(Helium3SideBand& sb, double Alwgt);
  void initSideBand_PlaylistCombinedFitDataHistograms(
      Helium3SideBand& sb, ME_playlist_TFileMAP TFile_Map_Data,
      ME_helium_Playlists StartingPlaylist = kME1G);
  void init_MCShifted_PlaylistCombined_SideBand_FitHistograms(
      Helium3SideBand& sb, ME_playlist_TFileMAP TFile_Map_MC, int i, int j,
      int k, ME_helium_Playlists StartingPlaylist = kME1G);
  std::string PDF_printingLabel_input;
  std::string LatexPdfLabel;

  double ChiSqrt(
      MnvH1D* data_Region1, MnvH1D* Helium_Region1, MnvH1D* Aluminium_Region1,
      MnvH1D* Carbon_Region1, MnvH1D* Iron_Region1, MnvH1D* Lead_Region1,
      MnvH1D* Other_Region1,

      MnvH1D* data_Region2, MnvH1D* Helium_Region2, MnvH1D* Aluminium_Region2,
      MnvH1D* Carbon_Region2, MnvH1D* Iron_Region2, MnvH1D* Lead_Region2,
      MnvH1D* Other_Region2,

      MnvH1D* data_Region3, MnvH1D* Helium_Region3, MnvH1D* Aluminium_Region3,
      MnvH1D* Carbon_Region3, MnvH1D* Iron_Region3, MnvH1D* Lead_Region3,
      MnvH1D* Other_Region3,

      MnvH1D* data_Region4, MnvH1D* Helium_Region4, MnvH1D* Aluminium_Region4,
      MnvH1D* Carbon_Region4, MnvH1D* Iron_Region4, MnvH1D* Lead_Region4,
      MnvH1D* Other_Region4);

  double LogChiSqrt(
      MnvH1D* data_Region1, MnvH1D* Helium_Region1, MnvH1D* Aluminium_Region1,
      MnvH1D* Carbon_Region1, MnvH1D* Iron_Region1, MnvH1D* Lead_Region1,
      MnvH1D* Other_Region1,

      MnvH1D* data_Region2, MnvH1D* Helium_Region2, MnvH1D* Aluminium_Region2,
      MnvH1D* Carbon_Region2, MnvH1D* Iron_Region2, MnvH1D* Lead_Region2,
      MnvH1D* Other_Region2,

      MnvH1D* data_Region3, MnvH1D* Helium_Region3, MnvH1D* Aluminium_Region3,
      MnvH1D* Carbon_Region3, MnvH1D* Iron_Region3, MnvH1D* Lead_Region3,
      MnvH1D* Other_Region3,

      MnvH1D* data_Region4, MnvH1D* Helium_Region4, MnvH1D* Aluminium_Region4,
      MnvH1D* Carbon_Region4, MnvH1D* Iron_Region4, MnvH1D* Lead_Region4,
      MnvH1D* Other_Region4);

  double GetChiSqt_X(Helium3SideBand& sb_upstreamCap,
                     Helium3SideBand& sb_Barrel,
                     Helium3SideBand& sb_downstreamCap,
                     Helium3SideBand& sb_downstreamConcaveCap, int ind);

  double GetLogChiSqt_X(Helium3SideBand& sb_upstreamCap,
                        Helium3SideBand& sb_Barrel,
                        Helium3SideBand& sb_downstreamCap,
                        Helium3SideBand& sb_downstreamConcaveCap, int ind);

  double GetChiSqt_Y(Helium3SideBand& sb_upstreamCap,
                     Helium3SideBand& sb_Barrel,
                     Helium3SideBand& sb_downstreamCap,
                     Helium3SideBand& sb_downstreamConcaveCap, int ind);

  double GetLogChiSqt_Y(Helium3SideBand& sb_upstreamCap,
                        Helium3SideBand& sb_Barrel,
                        Helium3SideBand& sb_downstreamCap,
                        Helium3SideBand& sb_downstreamConcaveCap, int ind);

  double GetChiSqt_Z(Helium3SideBand& sb_upstreamCap,
                     Helium3SideBand& sb_Barrel,
                     Helium3SideBand& sb_downstreamCap,
                     Helium3SideBand& sb_downstreamConcaveCap, int ind);

  double GetLogChiSqt_Z(Helium3SideBand& sb_upstreamCap,
                        Helium3SideBand& sb_Barrel,
                        Helium3SideBand& sb_downstreamCap,
                        Helium3SideBand& sb_downstreamConcaveCap, int ind);

  double GetChiSqt_R(Helium3SideBand& sb_upstreamCap,
                     Helium3SideBand& sb_Barrel,
                     Helium3SideBand& sb_downstreamCap,
                     Helium3SideBand& sb_downstreamConcaveCap, int ind);

  double GetLogChiSqt_R(Helium3SideBand& sb_upstreamCap,
                        Helium3SideBand& sb_Barrel,
                        Helium3SideBand& sb_downstreamCap,
                        Helium3SideBand& sb_downstreamConcaveCap, int ind);

  void GetChiSqt_FitParms(Helium3SideBand& sb_upstreamCap,
                          Helium3SideBand& sb_Barrel,
                          Helium3SideBand& sb_downstreamCap,
                          Helium3SideBand& sb_downstreamConcaveCap, int ind,
                          double& chisqrt_X, double& chisqrt_Y,
                          double& chisqrt_Z, double& chisqrt_R);

  void GetLogChiSqt_FitParms(Helium3SideBand& sb_upstreamCap,
                             Helium3SideBand& sb_Barrel,
                             Helium3SideBand& sb_downstreamCap,
                             Helium3SideBand& sb_downstreamConcaveCap, int ind,
                             double& chisqrt_X, double& chisqrt_Y,
                             double& chisqrt_Z, double& chisqrt_R);

  void init_MC_ResolutionVars_PlaylistCombined_Histograms(
      Resolution_hists& Resolution_var, std::string regionstring,
      ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist);
  void init_MC_Resolution_PlaylistCombined_Histograms(
      XSec_Var3band& xsec_var, std::string regionstring,
      ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist);

  void init_MC_PlaylistCombined_SideBand_Resolution_Histograms(
      Helium3SideBand& sb, std::string regionstring,
      ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist);
  void init_MC_PlaylistCombined_SideBand_Resolution_RECOandTRUE_Histograms(
      Helium3SideBand& sb, std::string regionstring,
      ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist);

  // void init_MC_Material_PlaylistCombined_Histograms(XSec_Var3band& xsec_var,
  // std::string regionstring,  ME_playlist_TFileMAP TFile_Map_MC,
  // ME_helium_Playlists StartingPlaylist );
  void FillResolutionHistnames(Helium3SideBand& sb);
  void FillResolutionHistnames(Resolution_hists& resolution_var,
                               std::string hist_name);
  void SaveVector_toFile(std::vector<double> input, std::string name);
  std::vector<double> ReadFile_vector(std::string filename);

  void FillHistName_Map_NRegions(HeliumNSideBand& sb,
                                 std::vector<std::string> histNames,
                                 std::vector<Fit_Parms_Names> FitParms);
  void ConstructVertex_FitMC_shifted_HistName_Map(
      CryoRegion_HeliumNSideBand_Map& sb,
      std::vector<CryoTank_REGIONS> CryoRegion14_vector);
  void FillXsec_VarNbandName(XSec_VarNband& xsec, std::string InputName,
                             std::string XAxis);
  void FillXsec_VarNbandName_Data(XSec_VarNband& xsec, std::string InputName);
  void ConstructVertex_FitMC_shifted_HistName_Map(HeliumNSideBand& sb,
                                                  std::string CyroRegion);
  void ConstructVertex_FitDATA_shifted_HistName_Map(HeliumNSideBand& sb,
                                                    std::string CyroRegion);

  void init_Region_N_MaterialHists(HeliumNSideBand& input_HeliumNSideBand,
                                   ME_playlist_TFileMAP TFile_Map_MC,
                                   ME_helium_Playlists StartingPlaylist);
  void init_Region_N_MaterialHists_Data(HeliumNSideBand& input_HeliumNSideBand,
                                        ME_playlist_TFileMAP TFile_Map_Data,
                                        ME_helium_Playlists StartingPlaylist);
  void init_Region_N_MaterialHists_TRUEMeasure(
      HeliumNSideBand& input_HeliumNSideBand, ME_playlist_TFileMAP TFile_Map_MC,
      ME_helium_Playlists StartingPlaylist);
  void init_Region_Map_MaterialHists(CryoRegion_HeliumNSideBand_Map& input_Map,
                                     ME_playlist_TFileMAP TFile_Map_MC,
                                     ME_helium_Playlists StartingPlaylist);
  void FillPOTScalar(HeliumNSideBand& sb, double POTMC_input,
                     double POTData_input);

  void fill_CryoRegion14_HistMap_vertex_X_data(
      CryoRegion_HeliumNSideBand_Map CryoRegionMap,
      CryoRegion_HistMap& Data_Map);
  void fill_CryoRegion14_HistMap_vertex_Y_data(
      CryoRegion_HeliumNSideBand_Map CryoRegionMap,
      CryoRegion_HistMap& Data_Map);
  void fill_CryoRegion14_HistMap_vertex_Z_data(
      CryoRegion_HeliumNSideBand_Map CryoRegionMap,
      CryoRegion_HistMap& Data_Map);
  void fill_CryoRegion14_HistMap_vertex_R_data(
      CryoRegion_HeliumNSideBand_Map CryoRegionMap,
      CryoRegion_HistMap& Data_Map);

  void fill_CryoRegion14_HistMap_muon_PT_data(
      CryoRegion_HeliumNSideBand_Map CryoRegionMap,
      CryoRegion_HistMap& Data_Map);
  void fill_CryoRegion14_HistMap_muon_PZ_data(
      CryoRegion_HeliumNSideBand_Map CryoRegionMap,
      CryoRegion_HistMap& Data_Map);
  void fill_CryoRegion14_HistMap_muon_theta_data(
      CryoRegion_HeliumNSideBand_Map CryoRegionMap,
      CryoRegion_HistMap& Data_Map);
  void fill_CryoRegion14_HistMap_muon_E_data(
      CryoRegion_HeliumNSideBand_Map CryoRegionMap,
      CryoRegion_HistMap& Data_Map);
  void fill_CryoRegion14_HistMap_muon_doca_data(
      CryoRegion_HeliumNSideBand_Map CryoRegionMap,
      CryoRegion_HistMap& Data_Map);
  void fill_CryoRegion14_HistMap_DistancetoEdge_data(
      CryoRegion_HeliumNSideBand_Map CryoRegionMap,
      CryoRegion_HistMap& Data_Map);
  void fill_CryoRegion14_HistMap_SecTrk_doca_data(
      CryoRegion_HeliumNSideBand_Map CryoRegionMap,
      CryoRegion_HistMap& Data_Map);
  void fill_CryoRegion14_HistMap_TrackLength_doca_data(
      CryoRegion_HeliumNSideBand_Map CryoRegionMap,
      CryoRegion_HistMap& Data_Map);

  void fill_CryoRegion14_HistMap_vertex_X_Material(
      CryoRegion_HeliumNSideBand_Map CryoRegionMap,
      CryoRegion_HistMap& Helium_Map, CryoRegion_HistMap& Al_Map,
      CryoRegion_HistMap& Other_Map, int ind);
  //===========================================================================================
  void fill_CryoRegion14_HistMap_vertex_Y_Material(
      CryoRegion_HeliumNSideBand_Map CryoRegionMap,
      CryoRegion_HistMap& Helium_Map, CryoRegion_HistMap& Al_Map,
      CryoRegion_HistMap& Other_Map, int ind);
  //===========================================================================================
  void fill_CryoRegion14_HistMap_vertex_Z_Material(
      CryoRegion_HeliumNSideBand_Map CryoRegionMap,
      CryoRegion_HistMap& Helium_Map, CryoRegion_HistMap& Al_Map,
      CryoRegion_HistMap& Other_Map, int ind);
  //===========================================================================================
  void fill_CryoRegion14_HistMap_vertex_R_Material(
      CryoRegion_HeliumNSideBand_Map CryoRegionMap,
      CryoRegion_HistMap& Helium_Map, CryoRegion_HistMap& Al_Map,
      CryoRegion_HistMap& Other_Map, int ind);
  //===========================================================================================
  void fill_CryoRegion14_HistMap_muon_PT_Material(
      CryoRegion_HeliumNSideBand_Map CryoRegionMap,
      CryoRegion_HistMap& Helium_Map, CryoRegion_HistMap& Al_Map,
      CryoRegion_HistMap& Other_Map, int ind);
  //===========================================================================================
  void fill_CryoRegion14_HistMap_muon_PZ_Material(
      CryoRegion_HeliumNSideBand_Map CryoRegionMap,
      CryoRegion_HistMap& Helium_Map, CryoRegion_HistMap& Al_Map,
      CryoRegion_HistMap& Other_Map, int ind);
  //===========================================================================================
  void fill_CryoRegion14_HistMap_muon_theta_Material(
      CryoRegion_HeliumNSideBand_Map CryoRegionMap,
      CryoRegion_HistMap& Helium_Map, CryoRegion_HistMap& Al_Map,
      CryoRegion_HistMap& Other_Map, int ind);
  //===========================================================================================
  void fill_CryoRegion14_HistMap_muon_E_Material(
      CryoRegion_HeliumNSideBand_Map CryoRegionMap,
      CryoRegion_HistMap& Helium_Map, CryoRegion_HistMap& Al_Map,
      CryoRegion_HistMap& Other_Map, int ind);
  //===========================================================================================
  void fill_CryoRegion14_HistMap_muon_doca_Material(
      CryoRegion_HeliumNSideBand_Map CryoRegionMap,
      CryoRegion_HistMap& Helium_Map, CryoRegion_HistMap& Al_Map,
      CryoRegion_HistMap& Other_Map, int ind);
  //===========================================================================================
  void fill_CryoRegion14_HistMap_DistancetoEdge_Material(
      CryoRegion_HeliumNSideBand_Map CryoRegionMap,
      CryoRegion_HistMap& Helium_Map, CryoRegion_HistMap& Al_Map,
      CryoRegion_HistMap& Other_Map, int ind);
  //===========================================================================================
  void fill_CryoRegion14_HistMap_SecTrk_doca_Material(
      CryoRegion_HeliumNSideBand_Map CryoRegionMap,
      CryoRegion_HistMap& Helium_Map, CryoRegion_HistMap& Al_Map,
      CryoRegion_HistMap& Other_Map, int ind);
  //===========================================================================================
  void fill_CryoRegion14_HistMap_TrackLength_Material(
      CryoRegion_HeliumNSideBand_Map CryoRegionMap,
      CryoRegion_HistMap& Helium_Map, CryoRegion_HistMap& Al_Map,
      CryoRegion_HistMap& Other_Map, int ind);
  //===========================================================================================

  void Plot_Fit_vars_Region14(std::string Hist_title, bool doAreaNormalized,
                              bool UseLogChi,
                              CryoRegion_HeliumNSideBand_Map CryoRegionMap,
                              bool doBinWidthNorm, std::string pdf_label,
                              int ind, int fittype);

  void Plot_Fit_vars_Region14_Vars(std::string Hist_title,
                                   bool doAreaNormalized, bool UseLogChi,
                                   CryoRegion_HeliumNSideBand_Map CryoRegionMap,
                                   bool doBinWidthNorm, std::string pdf_label,
                                   int ind, int fittype);

  std::vector<int> Helium9_colorScheme = {
      TColor::GetColor("#EEFF00"),
      TColor::GetColor("#DF00FF"),  //'psychedelic Purple1
      TColor::GetColor(43, 206, 72),  // green 2
      TColor::GetColor("#87CEEB"),  //'skyblue' 3
      TColor::GetColor("#0859C6"),  // blue 4
      TColor::GetColor("#654522"),  // yellowishbrown,5
      TColor::GetColor("#ffc922"),  //'sunset yellow'6
      TColor::GetColor("#FF0800"),  // 2 candy Apple7
      TColor::GetColor("#90AD1C"),  // 8
      TColor::GetColor("#BABABA"),  // Gray 9
      TColor::GetColor("#00FFFF"),  //'aqua' 10
      TColor::GetColor("#F1B6DA"),  // pink 11
      TColor::GetColor(kRed),       //'Jade' 12
      TColor::GetColor("#FAFAD2"),  // LightGoldenRodYellow 13
      TColor::GetColor("#800000"),  // Maroon 14
      TColor::GetColor("#555555"),  // dark grey 15
      TColor::GetColor(0, 153, 143),  // turquoise 16
      TColor::GetColor("#654522"),  // yellowishbrown, 17
      TColor::GetColor("#8db600"),  // yellowgreen, 18
      TColor::GetColor("#D3D3D3"),  //'lightgrey' 19
      TColor::GetColor("#90AD1C"),  // 20
      TColor::GetColor("#CCDDAA"),  // 21
      TColor::GetColor(kMagenta)  // 22
  };

  std::vector<int> Helium16_distinct = {
      TColor::GetColor("#2f4f4f"),  // neonyellow,0
      TColor::GetColor("#8b4513"),  //'psychedelic Purple1
      TColor::GetColor("#6b8e23"),  // green 2
      TColor::GetColor("#4b0082"),  //'skyblue' 3
      TColor::GetColor("#48d1cc"),  // blue 4
      TColor::GetColor("#ffa500"),  //'sunset yellow'6
      TColor::GetColor("#ffff00"),  // 2 candy Apple7
      TColor::GetColor("#00ff00"),  // 8
      TColor::GetColor("#ff00ff"),  // pink 11
      TColor::GetColor("#1e90ff"),  //'Jade' 12
      TColor::GetColor("#dda0dd"),  // LightGoldenRodYellow 13
      TColor::GetColor("#ff1493"),  // Maroon 14
      TColor::GetColor("#00fa9a"),  // Gray 9
      TColor::GetColor("#ffdead"),  // dark grey 15
      TColor::GetColor(kMagenta)  // 22
  };
};

#endif
