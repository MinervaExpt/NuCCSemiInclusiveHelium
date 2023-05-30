#ifndef HELIUMPLOTUTILS_H
#define HELIUMPLOTUTILS_H

#include "TCanvas.h"
#include <TStyle.h>
#include "TObjArray.h"
#include "PlotUtils/MnvVertErrorBand.h"
#include "PlotUtils/MnvPlotter.h"
#include "PlotUtils/HistogramUtils.h"
#include "PlotUtils/MnvH1D.h"
#include "PlotUtils/MnvH2D.h"
#include "PlotUtils/HistFolio.h"
#include "HeliumCuts.h"
#include <iostream>
#include "HeliumDefaults.h"
#include "HeliumUtils.h"
#include "TPie.h"
#include "TGraphErrors.h"
#include <TGraph2D.h>
#include "TF1.h"
#include "GridCanvas.h"
#include "plot.h"
#include "myPlotStyle.h"
#include <TProfile.h>
#include "TEllipse.h"
#include "TVirtualFitter.h"
#include "TPaveStats.h"
#include "TColor.h"
#include "Helium2DPlotUtils.h"
#include "Helium_reweightModels.h"
//#include "TF1Convolution.h" gvm root verson 5 doesn't have these functions

//#include "PlotUtils/MnvApplication.h"

const double xmin = 0.;
const double xmax = 20;
const int nbins = 30;

std::vector<Interaction_Map> Interaction_vector(TObjArray *Hists_vector,
                                                bool doPOTscaling,
                                                double scaler);
//============================================================================
std::vector<Material_Map> Material_vector(TObjArray *Hists_vector,
                                          bool doPOTscaling, double scaler);
//============================================================================
std::vector<Particle_Map> Particle_vector(TObjArray *Hists_vector,
                                          bool doPOTscaling, double scaler);
//============================================================================
const bool do_fractional_uncertainty = true;
const bool do_cov_area_norm = false;
const bool include_stat_error = false;
//============================================================================
const std::string do_fractional_uncertainty_str =
    do_fractional_uncertainty ? std::string("Frac") : std::string("Abs");
const std::string do_cov_area_norm_str =
    do_cov_area_norm ? std::string("CovAreaNorm") : std::string("");
//============================================================================
void PlotErrorSummary(PlotUtils::MnvH1D *hist, std::string pdf,
                      std::string title, std::string xaxis, TCanvas *cE);
//============================================================================
void PlotErrorSummaryNew(PlotUtils::MnvH1D *hist, std::string pdf,
                         std::string title, std::string xaxis, TCanvas *cE,
                         MnvPlotter *mnvPlotter);
//============================================================================
void PlotErrorSummaryNew(PlotUtils::MnvH1D *hist, std::string pdf,
                         std::string title, std::string xaxis, TCanvas *cE,
                         MnvPlotter *mnvPlotter, bool Debug,
                         bool PrintAllGroupErrors);
//============================================================================
void MakeModelErrorGroups(MnvPlotter &mnvPlotter);
//============================================================================
void PlotVertBand(std::string band, std::string method_str,
                  PlotUtils::MnvH1D *hist);
//============================================================================
void PlotVertBand(std::string band, std::string method_str, std::string title,
                  std::string Xaxis, std::string Yaxis,
                  PlotUtils::MnvH1D *hist);
//============================================================================
void PlotLatBand(std::string band, std::string method_str,
                 PlotUtils::MnvH1D *hist);
//============================================================================
void PlotVertUniverse(std::string band, unsigned int universe,
                      std::string method_str, PlotUtils::MnvH1D *hist);
//============================================================================
void PlotLatUniverse(std::string band, unsigned int universe,
                     std::string method_str, PlotUtils::MnvH1D *hist);
//============================================================================
void PlotCVAndError(PlotUtils::MnvH1D *hist, std::string label);
//============================================================================
void Plot_MuonCVAndErrorWITHDATA(PlotUtils::MnvH1D *histFullMC,
                                 PlotUtils::MnvH1D *histEmptyMC,
                                 PlotUtils::MnvH1D *datahist_Full,
                                 PlotUtils::MnvH1D *datahist_Empty,
                                 std::string label, double POT[],
                                 MuonVar Muontype, int order, TCanvas *cE);
void PlotTotalError(PlotUtils::MnvH1D *hist, std::string method_str);
//============================================================================
void DrawStack_Particle(bool my_debug, TFile *inputFile, CryoVertex Vertex_type,
                        ME_helium_Playlists PlayList, int doShape, int logScale,
                        const char *title, MnvPlotter *plot, TCanvas *can,
                        const char *pdf);
//============================================================================
void DrawStack_Particle_MuonVar(bool my_debug, TFile *inputFile,
                                MuonVar MuonVar_type,
                                ME_helium_Playlists PlayList, int doShape,
                                int logScale, const char *title,
                                MnvPlotter *plot, TCanvas *can,
                                const char *pdf);
//============================================================================
void DrawStack_Interaction(bool my_debug, TFile *inputFile,
                           CryoVertex Vertex_type, ME_helium_Playlists PlayList,
                           int doShape, int logScale, const char *title,
                           MnvPlotter *plot, TCanvas *can, const char *pdf);
//============================================================================
void DrawStack_Interaction_MuonVar(bool my_debug, TFile *inputFile,
                                   MuonVar MuonVar_type,
                                   ME_helium_Playlists PlayList, int doShape,
                                   int logScale, const char *title,
                                   MnvPlotter *plot, TCanvas *can,
                                   const char *pdf);
//============================================================================
void DrawStack_Material(bool my_debug, TFile *inputFile, CryoVertex Vertex_type,
                        ME_helium_Playlists PlayList, int doShape, int logScale,
                        const char *title, MnvPlotter *plot, TCanvas *can,
                        const char *pdf);
//============================================================================
void DrawStack_Material_MuonVar(bool my_debug, TFile *inputFile,
                                MuonVar MuonVar_type,
                                ME_helium_Playlists PlayList, int doShape,
                                int logScale, const char *title,
                                MnvPlotter *plot, TCanvas *can,
                                const char *pdf);
//============================================================================
void DrawCVAndError_FromTFile(TFile *inputFile, char *histoName,
                              char *histotitle, std::string xaxislabel,
                              std::string label);
//============================================================================
void DrawCVAndError_FromTFile(bool PrintallErrors, TFile *inputFile,
                              char *histoName, char *histotitle,
                              std::string xaxislabel, std::string label);
//============================================================================
void DrawCVAndError_FromTFile(TFile *inputFile_MCFULL, TFile *inputFile_MCEMPTY,
                              char *histoName_MC, TFile *inputFile_DATAFULL,
                              TFile *inputFile_DATAEMPTY, char *histoName_Data,
                              Pot_MapStatusList POT_MC,
                              Pot_MapStatusList POT_DATA, char *histotitle,
                              std::string xaxislabel, std::string label,
                              bool DoBinwidthNorm, bool doSmallerrorgrounps,
                              std::string units);
//============================================================================
void DrawCVAndError_FromTFile(TFile *inputFile_MCFULL, TFile *inputFile_MCEMPTY,
                              char *histoName_MC, TFile *inputFile_DATAFULL,
                              TFile *inputFile_DATAEMPTY, char *histoName_Data,
                              Pot_MapStatusList POT_MC,
                              Pot_MapStatusList POT_DATA,
                              bool TrueifFullelseEmpty, char *histotitle,
                              std::string xaxislabel, std::string label,
                              bool DoBinwidthNorm, bool doSmallerrorgrounps,
                              std::string units, int Print_Error, bool Debug);
//============================================================================
void DrawCVAndError_FromTFile(TFile *inputFile_MCFULL, TFile *inputFile_MCEMPTY,
                              char *histoName_MC, TFile *inputFile_DATAFULL,
                              TFile *inputFile_DATAEMPTY, char *histoName_Data,
                              Pot_MapStatusList POT_MC,
                              Pot_MapStatusList POT_DATA,
                              bool TrueifFullelseEmpty, char *histotitle,
                              std::string xaxislabel, std::string label,
                              bool DoBinwidthNorm, bool doSmallerrorgrounps,
                              std::string units, int Print_Error, bool Debug,
                              bool Makelogx, bool Makelogy);
//============================================================================
void DrawDATAWITHCV_AndError_FromTFile(TFile *inputFile, TFile *inputFile_data,
                                       char *histoName, char *histoName_data,
                                       char *histotitle, std::string xaxislabel,
                                       std::string label);
//============================================================================
void PlotCVAndError_second_Track(PlotUtils::MnvH1D *hist, std::string label,
                                 SecondTrkVar second_Track, TCanvas *can,
                                 std::string title);
//============================================================================
void DrawDATAWITHCV_AndError_FromTFile_Single_playlist(
    TFile *inputFile, TFile *inputFile_data, Pot_MapList POT_MC,
    Pot_MapList POT_DATA, ME_helium_Playlists playlist_name, char *histoName,
    char *histoName_data, char *histotitle, std::string xaxislabel,
    std::string label, bool MakeBinwidth_Norm);
//============================================================================
void DrawDATAWITHCV_AndError_FromTFile_Single_playlist_Full_EMPTY(
    TFile *inputFileFULL, TFile *inputFileEMPTY, TFile *inputFile_Fulldata,
    TFile *inputFile_Emptydata, Pot_MapList POT_MC, Pot_MapList POT_DATA,
    ME_helium_Playlists playlist_name_FULL,
    ME_helium_Playlists playlist_name_EMPTY, char *histoName,
    char *histoName_data, char *histotitle, std::string xaxislabel,
    std::string label, bool MakeBinwidth_Norm);
//============================================================================
void DrawCVAndError_FromHIST(MnvH1D *hist_INCOMING, char *histotitle,
                             std::string xaxislabel, std::string yaxislabel,
                             std::string pdf_name, bool Setgrid);
//============================================================================
void DrawCVAndError_FromHIST(MnvH1D *hist, char *histotitle,
                             std::string xaxislabel, std::string yaxislabel,
                             std::string pdf_name, bool Setgrid, bool LogX);
//============================================================================
void DrawCVAndError_FromHIST(bool PrintALLerrorGroups, MnvH1D *hist,
                             char *histotitle, std::string xaxislabel,
                             std::string yaxislabel, std::string pdf_name,
                             bool Setgrid, bool doBinwidth = false,
                             bool SetYlimits = false, double Ymin = -99,
                             double Ymax = 99);
//============================================================================
void DrawCVAndError_FromHIST_withVLine(MnvH1D *hist, char *histotitle,
                                       std::string xaxislabel,
                                       std::string yaxislabel,
                                       std::string pdf_name, bool Setgrid,
                                       bool LogX, bool LogY, double xAxis_Vline,
                                       const std::string &arrow_direction,
                                       double arrow_length);
//============================================================================
void DrawStack_secTrk_Particle_FUll_EMPTY(
    bool my_debug, TFile *inputFile_FULL, TFile *inputFile_EMPTY,
    Pot_MapList POT_MC, SecondTrkVar second_Trk_type,
    ME_helium_Playlists PlayListFULL, ME_helium_Playlists PlayListEmpty,
    int doShape, int logScale, std::string Hist_name_addON, MnvPlotter *plot,
    TCanvas *can, const char *pdf);
//============================================================================
void DrawStack_secTrk_Particle_FUll_EMPTY_WITHDATA(
    bool my_debug, TFile *inputFile_FULL, TFile *inputFile_EMPTY,
    TFile *inputFile__DATA_FULL, TFile *inputFile_DATA_EMPTY,
    Pot_MapList POT_MC, Pot_MapList POT_DATA, SecondTrkVar second_Trk_type,
    ME_helium_Playlists PlayListFULL, ME_helium_Playlists PlayListEmpty,
    int doShape, int logScale, std::string Hist_name_addON, MnvPlotter *plot,
    TCanvas *can, const char *pdf);
//============================================================================
void Draw2DHist(MnvH2D *hist, const char *xaxislabel, const char *yaxislabel,
                const char *Title, const char *pdf, TCanvas *can,
                MnvPlotter *plot);
//============================================================================
void Draw2DHist_MvR(MnvH2D *hist, const char *xaxislabel,
                    const char *yaxislabel, char *zaxislabel, const char *Title,
                    const char *pdf, TCanvas *can, MnvPlotter *plot,
                    std::vector<double> BigAxisX, std::vector<double> BigAxisY,
                    std::vector<double> BigAxisX_small,
                    std::vector<double> BigAxisY_small, bool setcolorMap);
//============================================================================
void Draw2DHist(TH2D *hist, char *xaxislabel, char *yaxislabel,
                char *zaxislabel, char *Title, char *pdf, TCanvas *can,
                MnvPlotter *plot);
//============================================================================
void DrawMnvH2D(MnvH2D *hist, char *xaxislabel, char *yaxislabel,
                char *zaxislabel, char *Title, char *pdf, TCanvas *can,
                MnvPlotter *plot, bool setMiniumTrue = true);
//============================================================================
void Draw2DHist_TFILE(TFile *inputFile, const char *histoName,
                      const char *Title, const char *xaxislabel,
                      const char *yaxislabel, const char *pdf, TCanvas *can,
                      MnvPlotter *plot, bool PrintText = true);
//============================================================================
void Draw2DHist_Migration_TFILE(TFile *inputFile, const char *histoName,
                                const char *Title, const char *xaxislabel,
                                const char *yaxislabel, const char *pdf,
                                TCanvas *can, MnvPlotter *plot, bool PrintText);
//============================================================================
void Draw2DHist_Migration_TFILE_FULL_EMPTY(
    TFile *inputFile_FULL, TFile *inputFile_EMPTY, double MCscale,
    const char *histoName, const char *Title, const char *xaxislabel,
    const char *yaxislabel, const char *pdf_label, TCanvas *can,
    MnvPlotter *plot, bool PrintText);
//============================================================================
void Draw2DHist_Migration_Histpointer(MnvH2D *hist, const char *Title,
                                      const char *xaxislabel,
                                      const char *yaxislabel,
                                      const char *zaxislabel,
                                      const char *pdf_label, TCanvas *can,
                                      MnvPlotter *plot);
//============================================================================
void Draw2DHist_Migration_Histpointer(MnvH2D *hist, std::string Title_string,
                                      std::string xaxislabel_string,
                                      std::string yaxislabel_string,
                                      std::string zaxislabel_string,
                                      std::string pdf_label, TCanvas *can,
                                      MnvPlotter *plot);
//============================================================================
void Draw2DHist_histWithTProfile(MnvH2D *hist_input, const char *Title,
                                 const char *xaxislabel, const char *yaxislabel,
                                 const char *pdf, TCanvas *can,
                                 MnvPlotter *plot);
//============================================================================
void Draw2DHist_histWithTProfile_Y(MnvH2D *hist_input, const char *Title,
                                   const char *xaxislabel,
                                   const char *yaxislabel, const char *pdf,
                                   TCanvas *can, MnvPlotter *plot);
//============================================================================
void Draw2DHist_HistpointernoText(MnvH2D *hist, const char *Title,
                                  const char *xaxislabel,
                                  const char *yaxislabel,
                                  const char *zaxislabel, const char *pdf_label,
                                  TCanvas *can, MnvPlotter *plot);
//============================================================================
void Draw2DHist_withEllipse(MnvH2D *hist, char *xaxislabel, char *yaxislabel,
                            char *zaxislabel, char *Title, char *pdf,
                            TCanvas *can, MnvPlotter *plot, double r1,
                            double r2);
//============================================================================
void Draw2DHist_warp(MnvH2D *hist_input, const char *xaxislabel,
                     const char *yaxislabel, const char *Title, const char *pdf,
                     TCanvas *can, MnvPlotter *plot);
//============================================================================
void Draw2DHist_warpFit(MnvH2D *hist_input, const char *xaxislabel,
                        const char *yaxislabel, const char *Title,
                        const char *pdf, TCanvas *can, MnvPlotter *plot);
//============================================================================
void Draw2DHist_warpFit(MnvH2D *hist_input,
  const char* xaxislabel,const char* yaxislabel,
  const char* Title,
  const char* pdf, TCanvas *can,
  MnvPlotter *plot, char *Text_fitParms);
//============================================================================
void Draw2DHist_warpFit_show(MnvH2D *hist_input, const char *xaxislabel,
                             const char *yaxislabel, const char *Title,
                             const char *pdf, TCanvas *can, MnvPlotter *plot);
//============================================================================
void Draw2DHist_warpFit_show(MnvH2D *hist_input,
  const char* xaxislabel,const char* yaxislabel,
  const char* Title,
  const char* pdf,
  TCanvas *can, MnvPlotter *plot, Double_t *pars);
//============================================================================
void DrawStack_Vertex_Material_FUll_EMPTY_WITHDATA(
    bool my_debug, TFile *inputFile_FULL, TFile *inputFile_EMPTY,
    TFile *inputFile_DATA_FULL, TFile *inputFile_DATA_EMPTY, Pot_MapList POT_MC,
    Pot_MapList POT_DATA, CryoVertex CryroVertex_type,
    ME_helium_Playlists PlayListFULL, ME_helium_Playlists PlayListEmpty,
    int doShape, int logScale, std::string Hist_name_addON, MnvPlotter *plot,
    TCanvas *can, const char *pdf);
//============================================================================
void DrawMagration_heatMap(TH2D *h_migration_input, const char *xaxislabel,
                           const char *yaxislabel, const char *Title,
                           const char *pdf, TCanvas *can, MnvPlotter *plotter,
                           bool includeFlows = false);
//============================================================================
void DrawMagration_heatMap(MnvH2D *h_mig, const char *xaxislabel,
                           const char *yaxislabel, const char *Title,
                           const char *pdf, TCanvas *can, MnvPlotter *plotter,
                           bool includeFlows = false);
//============================================================================
void DrawMagration_heatMap_noText(MnvH2D *h_mig, const char *xaxislabel,
                                  const char *yaxislabel, const char *Title,
                                  const char *pdf, TCanvas *can,
                                  MnvPlotter *plotter,
                                  bool includeFlows = false,
                                  const char *zaxislabel = "");
//============================================================================
void DrawMagration_heatMap_LabelBinNumber(MnvH2D *h_mig, const char *xaxislabel,
                                          const char *yaxislabel,
                                          const char *Title, const char *pdf,
                                          TCanvas *can, MnvPlotter *plotter);
//============================================================================
void DrawMagration_heatMap_LabelBinNumber_new(
    MnvH2D *h_mig, const char *xaxislabel, const char *yaxislabel,
    const char *Title, const char *pdf, TCanvas *can, MnvPlotter *plotter,
    MnvH2D *h_binning, int bini, int binningtype, int rownormtype = 3,
    double text_size = 0.02);
//============================================================================
void DrawMagration_heatMap_Mig(MnvH2D *h_mig, const char *xaxislabel,
                               const char *yaxislabel, const char *Title,
                               const char *pdf, TCanvas *can,
                               MnvPlotter *plotter);
//============================================================================
void DrawMagration_heatMap_MigBinN(MnvH2D *h_mig, const char *xaxislabel,
                                   const char *yaxislabel, const char *Title,
                                   const char *pdf, TCanvas *can,
                                   MnvPlotter *plotter, int rownormtype);
//============================================================================
void DrawMagration_heatMap_MigBinN(MnvH2D *h_mig, const char *xaxislabel,
                                   const char *yaxislabel, TCanvas *can,
                                   MnvPlotter *plotter, MnvH2D *h_binning,
                                   int bini, int binningtype, int rownormtype,
                                   double text_size_label,
                                   double marker_size_label, double setMax);
//============================================================================
void Draw2DHist_NumberFigures_TFILE(TFile *inputFile, const char *histoName,
                                    const char *Title, const char *xaxislabel,
                                    const char *yaxislabel, const char *pdf,
                                    TCanvas *can, MnvPlotter *plot);
//============================================================================
void DrawMagration_heatMap_Label(MnvH2D *h_mig, const char *xaxislabel,
                                 const char *yaxislabel, const char *Title,
                                 const char *pdf, TCanvas *can,
                                 MnvPlotter *plotter, int rownormtype);
//============================================================================
void DrawMagration_heatMap_Label(MnvH2D *h_mig, const char *xaxislabel,
                                const char *yaxislabel, const char *Title,
                                const char *pdf, TCanvas *can,
                                MnvPlotter *plotter, int rownormtype,double Zmax);
//============================================================================
void DrawSTACKfromHistFilio_FromTFile(
    TFile *inputFile_MCFULL, TFile *inputFile_MCEMPTY, char *histoName_MC,
    TFile *inputFile_DATAFULL, TFile *inputFile_DATAEMPTY, char *histoName_Data,
    Pot_MapStatusList POT_MC, Pot_MapStatusList POT_DATA,
    bool TrueifFullelseEmpty, char *histotitle, std::string xaxislabel,
    std::string pdf_label, bool DoBinwidthNorm, bool doSmallerrorgrounps,
    std::string units, StackType STACKTYPE, bool Debug);
//============================================================================
void DrawSTACKfromHistFilio_FromTFileNoData(
    TFile *inputFile_MCFULL, TFile *inputFile_MCEMPTY, char *histoName_MC,
    Pot_MapStatusList POT_MC, Pot_MapStatusList POT_DATA, char *histotitle,
    std::string xaxislabel, std::string pdf_label, bool DoBinwidthNorm,
    std::string units, StackType STACKTYPE, bool Debug, bool SetMaximum = false,
    double Maximum_group = 1);
//============================================================================
void DrawSINGLESTACKMCHistFilio_FromTFile(TFile *inputFile_MCinput,
                                          char *histoName_MC, char *histotitle,
                                          std::string xaxislabel,
                                          std::string pdf_label,
                                          bool DoBinwidthNorm, bool Debug);
//============================================================================
void DrawRatio_FromTFile(TFile *inputFile_numerator, TFile *inputFile_demonator,
                         char *histoName_num, char *histoName_dem,
                         char *histotitle, std::string xaxislabel,
                         std::string pdf_label, std::string units);
//============================================================================
void Draw2DHist_Full_Empty_TFILE(TFile *inputFile_Full, TFile *inputFile_Empty,
                                 const char *histoName, Pot_MapList POT_MC,
                                 ME_helium_Playlists PlayListFULL,
                                 ME_helium_Playlists PlayListEmpty,
                                 const char *Title, const char *xaxislabel,
                                 const char *yaxislabel, const char *pdf,
                                 TCanvas *can, MnvPlotter *plot);
//============================================================================
void Draw1DFit_withBand(std::vector<double> Axis_X, std::vector<double> Axis_Y,
                        char *xaxislabel, char *yaxislabel, char *Title,
                        char *pdf, TCanvas *can, MnvPlotter *plot);
//============================================================================
void MakeTrue_interactionPlots(std::vector<Trajector> input_vector,
                               const char *Playlist, double Spaceingcm,
                               const char *pdf, TCanvas *can, MnvPlotter *plot);
//============================================================================
void MakeTrue_interactionPlots_WithRECOtrajector(
    std::vector<Trajector> input_vector,
    std::vector<Trajector_withTrueEnergyFraction> input_vector_RECO,
    const char *Playlist, double Spaceingcm, const char *pdf, TCanvas *can,
    MnvPlotter *plot);
//============================================================================
void SetHist(PlotUtils::MnvH1D *hist, char *xaxislabel, char *yaxislabel);
//============================================================================
void SetHist(TH1F *hist, char *xaxislabel, char *yaxislabel);
//============================================================================
void SetHist_Data(PlotUtils::MnvH1D &hist, char *xaxislabel, char *yaxislabel);
//============================================================================
void SetMaxforDraw(PlotUtils::MnvH1D *hist_to_Draw, PlotUtils::MnvH1D *hist);
//============================================================================
void SetMaxforDraw(PlotUtils::MnvH1D *hist_to_Draw, PlotUtils::MnvH1D *hist,
                   PlotUtils::MnvH1D *hist3);
//============================================================================
Hist_phyiscs_map Make_Physics_distribution_map_FromTFile(
    TFile *inputTFile, char *histoName_MC, bool UsePotScaling, double POTScale,
    ME_helium_Playlists playlist, bool IsRecoOrTruth);
//============================================================================
void DrawCVAndError_FromHistPointer(MnvH1D *hist, char *histotitle,
                                    std::string xaxislabel,
                                    std::string yaxislabel, std::string label,
                                    bool doBinwidth, bool MakeXaxisLOG);
//============================================================================
void DrawCVAndError_FromHistPointer(MnvH1D *hist, char *histotitle,
                                    std::string xaxislabel,
                                    std::string yaxislabel, std::string label,
                                    bool doBinwidth, bool MakeXaxisLOG,
                                    double maxY);
//============================================================================
void DrawCVAndError_FromHistPointer(MnvH1D *hist, char *histotitle,
                                    std::string xaxislabel,
                                    std::string yaxislabel, std::string label,
                                    bool doBinwidth, bool MakeXaxisLOG,
                                    bool printErrors, double Ymax);
//============================================================================
void DrawCVAndError_FromHistPointer(
    MnvH1D *hist_input, MnvH1D *datahist_input, MnvH1D *hist_inputBackground,
    MnvH1D *datahist_inputBackground, char *histotitle, std::string xaxislabel,
    std::string yaxislabel, std::string label, bool doBinwidth,
    bool MakeXaxisLOG, bool printErrors, double Ymax, bool PrintALLerrorGroups);
//============================================================================
void DrawCVAndError_FromHistPointer(MnvH1D *hist, MnvH1D *datahist,
                                    char *histotitle, std::string xaxislabel,
                                    std::string yaxislabel, std::string label,
                                    bool doBinwidth, bool MakeXaxisLOG,
                                    bool printErrors, double Ymax,
                                    bool PrintALLerrorGroups = false);
//============================================================================
void DrawCVAndError_FromHistPointer(MnvH1D *hist, char *histotitle,
                                    std::string xaxislabel,
                                    std::string yaxislabel, std::string label,
                                    bool doBinwidth, bool MakeXaxisLOG,
                                    bool MakeYaxisLOG);
//============================================================================
void Draw_2D_Panel_MC_Only_frompointer(
    MnvH2D *hist, char *histotitle, char *legend_title, std::string xaxislabel,
    std::string Xunits, std::string yaxislabel, std::string Yunits,
    std::string Zaxislabel, double headroom, char *pdf_label, bool doBinwidth,
    bool MakeXaxisLOG, double x_projectionTxtsize = .025,
    double y_projectionTxtsize = .03, bool doMultipliers = true);
//============================================================================
void Draw_2D_Panel_MC_Only_frompointer_WithErrorBand(
    MnvH2D *hist, char *histotitle, char *legend_title, std::string xaxislabel,
    std::string Xunits, std::string yaxislabel, std::string Yunits,
    std::string Zaxislabel, double headroom, char *pdf_label, bool doBinwidth,
    bool MakeXaxisLOG, double x_projectionTxtsize = .025,
    double y_projectionTxtsize = .03, bool doMultipliers = false);
//============================================================================
void Draw_2D_Panel_MC_andData_frompointer_DISbreakdown(
    MnvH2D *hist_Data, MnvH2D *hist_MC, MnvH2D *hist_MC_QE,
    MnvH2D *hist_MC_HeavierRES, MnvH2D *hist_MC_deltaRES, MnvH2D *hist_MC_2p2h,
    MnvH2D *hist_MC_DISSIS, MnvH2D *hist_MC_DISHard, MnvH2D *hist_MC_DISSoft,
    MnvH2D *hist_MC_Other, MnvH2D *hist_MC_NONE, bool DataStat_SysError,
    bool MC_Stat_SysError, char *histotitle, std::string xaxislabel,
    std::string yaxislabel, const char *Zaxislabel, double max_x, double max_y,
    bool setMaxY, char *pdf_label, bool doBinwidth, bool MakeXaxisLOG,
    double x_projectionTxtsize = .025, double y_projectionTxtsize = .03,
    bool doMultipliers = false, bool MakeRatio = false);
//============================================================================
void Draw_2D_Panel_MC_andData_frompointer_DISbreakdown_E_theta(
    MnvH2D *hist_Data, MnvH2D *hist_MC, MnvH2D *hist_MC_QE,
    MnvH2D *hist_MC_HeavierRES, MnvH2D *hist_MC_deltaRES, MnvH2D *hist_MC_2p2h,
    MnvH2D *hist_MC_DISSIS, MnvH2D *hist_MC_DISHard, MnvH2D *hist_MC_DISSoft,
    MnvH2D *hist_MC_Other, MnvH2D *hist_MC_NONE, bool DataStat_SysError,
    bool MC_Stat_SysError, char *histotitle, std::string xaxislabel,
    std::string yaxislabel, const char *Zaxislabel, double max_x, double max_y,
    bool setMaxY, char *pdf_label, bool doBinwidth, bool MakeXaxisLOG,
    double x_projectionTxtsize = .025, double y_projectionTxtsize = .03,
    bool doMultipliers = false, bool MakeRatio = false);
//============================================================================
void Draw_2D_Panel_MC_andData_frompointer_DISbreakdown(
    MnvH2D *hist_Data, MnvH2D *hist_MC, MnvH2D *hist_MC_QE,
    MnvH2D *hist_MC_HeavierRES, MnvH2D *hist_MC_deltaRES, MnvH2D *hist_MC_2p2h,
    MnvH2D *hist_MC_DISSIS, MnvH2D *hist_MC_DISHard, MnvH2D *hist_MC_DISSoft,
    MnvH2D *hist_MC_Other, MnvH2D *hist_MC_NONE, bool DataStat_SysError,
    bool MC_Stat_SysError, char *histotitle, std::string xaxislabel,
    std::string yaxislabel, const char *Zaxislabel, double max_x, double max_y,
    bool setMaxY, char *pdf_label, bool doBinwidth, bool MakeXaxisLOG,
    double x_projectionTxtsize, double y_projectionTxtsize, bool doMultipliers,
    std::vector<double> YMultipliers, std::vector<double> XMultipliers);
//============================================================================
void Draw_2D_Panel_MC_andData_frompointer_DISbreakdown_STACK(
    MnvH2D *hist_Data, MnvH2D *hist_MC, MnvH2D *hist_MC_QE,
    MnvH2D *hist_MC_HeavierRES, MnvH2D *hist_MC_deltaRES, MnvH2D *hist_MC_2p2h,
    MnvH2D *hist_MC_DISSIS, MnvH2D *hist_MC_DISHard, MnvH2D *hist_MC_DISSoft,
    MnvH2D *hist_MC_Other, MnvH2D *hist_MC_NONE, bool DataStat_SysError,
    bool MC_Stat_SysError, char *histotitle, std::string xaxislabel,
    std::string yaxislabel, const char *Zaxislabel, double max_x, double max_y,
    bool setMaxY, char *pdf_label, bool doBinwidth, bool MakeXaxisLOG,
    double x_projectionTxtsize, double y_projectionTxtsize, bool doMultipliers,
    std::vector<double> YMultipliers, std::vector<double> XMultipliers);
//============================================================================
void Draw_2D_Panel_MC_andData_frompointer_DISbreakdown_E_theta(
    MnvH2D *hist_Data, MnvH2D *hist_MC, MnvH2D *hist_MC_QE,
    MnvH2D *hist_MC_HeavierRES, MnvH2D *hist_MC_deltaRES, MnvH2D *hist_MC_2p2h,
    MnvH2D *hist_MC_DISSIS, MnvH2D *hist_MC_DISHard, MnvH2D *hist_MC_DISSoft,
    MnvH2D *hist_MC_Other, MnvH2D *hist_MC_NONE, bool DataStat_SysError,
    bool MC_Stat_SysError, char *histotitle, std::string xaxislabel,
    std::string yaxislabel, const char *Zaxislabel, double max_x, double max_y,
    bool setMaxY, char *pdf_label, bool doBinwidth, bool MakeXaxisLOG,
    double x_projectionTxtsize, double y_projectionTxtsize, bool doMultipliers,
    std::vector<double> YMultipliers, std::vector<double> XMultipliers);
//============================================================================
void Draw_2D_Panel_MC_Only_frompointer_YProjection(
    MnvH2D *hist, char *histotitle, char *legend_title, std::string xaxislabel,
    std::string yaxislabel, const char *Zaxislabel, double max_y,
    char *pdf_label, bool doBinwidth, bool MakeXaxisLOG);
//============================================================================
void Draw_2D_Panel_MC_Only_frompointer_XProjection(
    MnvH2D *hist, char *histotitle, char *legend_title, std::string xaxislabel,
    std::string yaxislabel, const char *Zaxislabel, double max_x,
    char *pdf_label, bool doBinwidth, bool MakeXaxisLOG);
//============================================================================
void Draw_Data_RECO_TRUTH_Hist_fromTFile_withConvolution(
    char *histoName_TRUTH, char *histoName_TRUTHConvolution,
    TFile *inputFile_MCinputFULL, TFile *inputFile_MCinputEmpty,
    char *histoName_MC, TFile *inputFile_DatainputFULL,
    TFile *inputFile_DatainputEmpty, char *histoName_data,
    char *Playlist_name_FULL, char *Playlist_name_EMPTY, std::string pdf_label,
    char *histotitle, char *xaxislabel, char *yaxislabel, bool DoBinwidthNorm,
    bool MakeXaxisLOG, Pot_MapStatusList POT_DATA, Pot_MapStatusList POT_MC);
//============================================================================
void Draw_Data_RECO_TRUTH_Hist_withConvolution_fromPointers(
    MnvH1D *hist_Data, MnvH1D *hist_RECOMC, MnvH1D *hist_TRUTH_Convolution,
    MnvH1D *hist_TRUTH, char *Playlist_name, std::string pdf_label,
    char *histotitle, char *playlist_status, char *xaxislabel, char *yaxislabel,
    bool DoBinwidthNorm, bool MakeXaxisLOG, double Ymax, double Convoluted_Mean,
    double Convoluted_stddev, double &ChiSqrt_Truth_toRECO,
    double &ChiSqrt_Truth_toData, double &ChiSqrt_Reco_toData);
//============================================================================
void Draw_Data_RECO_TRUTH_Hist_withConvolutionRECO_fromPointers(
    MnvH1D *hist_Data, MnvH1D *hist_RECOMC, MnvH1D *hist_RECO_Convolution,
    MnvH1D *hist_TRUTH, bool AreaNorm_todata, char *Playlist_name,
    std::string pdf_label, char *histotitle, char *playlist_status,
    char *xaxislabel, char *yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG,
    double Ymax, double Convoluted_MeanF, double Convoluted_stddevF,
    double Convoluted_MeanE, double Convoluted_stddevE,
    double &ChiSqrt_ConvolRECOtoRECO, double &ChiSqrt_ConvolRECOtoData,
    double &ChiSqrt_RECO_toData);
//============================================================================
void Draw_Data_RECO_TRUTH_Hist_withConvolutionRECO_fromPointers(
    MnvH1D *hist_Data, MnvH1D *hist_RECOMC, MnvH1D *hist_RECO_Convolution,
    MnvH1D *hist_TRUTH, bool AreaNorm_todata, char *Playlist_name,
    std::string pdf_label, char *histotitle, char *playlist_status,
    char *xaxislabel, char *yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG,
    double Ymax, double Convoluted_Mean, double Convoluted_stddev,
    double &ChiSqrt_ConvolRECOtoRECO, double &ChiSqrt_ConvolRECOtoData,
    double &ChiSqrt_RECO_toData);
//============================================================================
void DrawCVAndError_FromHIST_withFit(MnvH1D *hist, char *histotitle,
                                     std::string xaxislabel,
                                     std::string yaxislabel,
                                     std::string pdf_name, bool Setgrid,
                                     bool PrintErrors = false,
                                     bool PrintallErrorGroups = false);
//============================================================================
void DrawCVAndError_FromHIST_withFit(
    MnvH1D *hist, char *histotitle, std::string xaxislabel,
    std::string yaxislabel, std::string pdf_name, bool Setgrid,
    double &sigma_return, double &TotalN_return, double &chi_sq_return,
    int &NDF_return, double &Mean_return, double &Constant_return,
    bool PrintErrors = false, bool PrintallErrorGroups = false);
//============================================================================
void DrawCVAndError_FromHIST_withRMS(
    MnvH1D *hist_input, char *histotitle, std::string xaxislabel,
    std::string yaxislabel, char *Units, std::string pdf_name, bool Setgrid,
    bool doBinwidth, bool PrintErrors, bool PrintallErrorGroups,
    bool PrintRMS_percentage, bool AreaNormalized = false);
//============================================================================
void MakeCVS_from_hist(TFile *input_TFile, char *histoName,
                       char *histoName_Label);
//============================================================================
void MakeCVS_from_HISTS(char *histoName_TRUTH, TFile *inputFile_MCinputFULL,
                        TFile *inputFile_MCinputEmpty, char *histoName_MC,
                        TFile *inputFile_DatainputFULL,
                        TFile *inputFile_DatainputEmpty, char *histoName_data,
                        char *Playlist_name_FULL, char *Playlist_name_EMPTY,
                        char *File_Title, char *varibleName,
                        Pot_MapStatusList POT_DATA, Pot_MapStatusList POT_MC);
//============================================================================
void Draw_DataHist_fromTFile(TFile *inputFile_DatainputFULL,
                             TFile *inputFile_DatainputEmpty,
                             char *histoName_data, char *Playlist_name_FULL,
                             char *Playlist_name_Empty, std::string pdf_label,
                             char *histotitle, char *xaxislabel,
                             char *yaxislabel, bool DoBinwidthNorm,
                             bool MakeXaxisLOG, Pot_MapStatusList POT_DATA);
//============================================================================
void Draw_DataWITHMC_Hist_fromTFile(
    TFile *inputFile_MCinputFULL, TFile *inputFile_MCinputEmpty,
    char *histoName_MC, TFile *inputFile_DatainputFULL,
    TFile *inputFile_DatainputEmpty, char *histoName_data,
    char *Playlist_name_FULL, char *Playlist_name_EMPTY, std::string pdf_label,
    char *histotitle, char *xaxislabel, char *yaxislabel, bool DoBinwidthNorm,
    bool MakeXaxisLOG, Pot_MapStatusList POT_DATA, Pot_MapStatusList POT_MC);
//============================================================================
void Draw_DataWITHMC_SingleHistinput(MnvH1D *hist_MC, MnvH1D *hist_Data,
                                     char *Playlist_name, std::string pdf_label,
                                     char *histotitle, std::string units,
                                     char *xaxislabel, char *yaxislabel,
                                     bool DoBinwidthNorm, bool MakeXaxisLOG);
//============================================================================
void Draw_DataWITHMC_SingleHistinput_withRatio(
    MnvH1D *hist_MC_input, MnvH1D *hist_Data_input, char *Playlist_name,
    std::string pdf_label, char *histotitle, std::string units,
    char *xaxislabel, char *yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG,
    bool MakeYaxisLOG = false, bool drawAllErrorGroups = true);
//============================================================================
void Draw_DataWITHMC_SingleHistinput_withRatio(
    MnvH1D *hist_MC, MnvH1D *hist_Data, char *Playlist_name,
    std::string pdf_label, char *histotitle, std::string units,
    char *xaxislabel, char *yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG,
    bool MakeYaxisLOG, bool drawErrors, bool drawAllErrorGroups, double Ymax,
    double &ChiSqr_return, int &ndf_return);
//============================================================================
void Draw_DataWITHMC_SingleHistinput_withRatioCrossSection(
    MnvH1D *hist_MC_input, MnvH1D *hist_Data_input, char *Playlist_name,
    std::string pdf_label, char *histotitle, std::string units,
    char *xaxislabel, char *yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG,
    bool drawAllErrorGroups = true);
//============================================================================
void Draw_DataWITHMC_SingleHistinput_withRatioCrossSection(
    MnvH1D *hist_MC_input, MnvH1D *hist_Data_input, char *Playlist_name,
    std::string pdf_label, char *histotitle, std::string units,
    char *xaxislabel, char *yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG,
    bool drawAllErrorGroups, double MaxYvalue);
//============================================================================
void Draw_DataWITHMC_SingleHistinput_withRatioCrossSection(
    MnvH1D *hist_MC_input, MnvH1D *hist_Data_input, TObjArray *modelHist_input,
    char *Playlist_name, std::string pdf_label, char *histotitle,
    std::string units, char *xaxislabel, char *yaxislabel, bool MakeXaxisLOG);
//============================================================================
void Draw_DataWITHMC_SingleHistinput_withRatioCrossSection_Interactions(
    MnvH1D *hist_MC, MnvH1D *hist_Data, MnvH1D *h_elastic, MnvH1D *h_2p2h,
    MnvH1D *h_1pion, MnvH1D *h_DIS, MnvH1D *h_None, MnvH1D *h_Other,
    char *Playlist_name, std::string pdf_label, char *histotitle,
    std::string units, char *xaxislabel, char *yaxislabel, bool DoBinwidthNorm,
    bool MakeXaxisLOG, bool drawAllErrorGroups, double POT_MC, double POT_DATA);
//============================================================================
void Draw_DataWITHMC_SingleHistinput_withRatioCrossSection_Interactions_DISbreakdown(
    MnvH1D *hhist_MC, MnvH1D *hhist_Data, MnvH1D *hh_elastic, MnvH1D *hh_2p2h,
    MnvH1D *hh_deltaRes, MnvH1D *hh_heavierRes, MnvH1D *hh_DISSIS,
    MnvH1D *hh_DISSoft, MnvH1D *hh_DIShard, MnvH1D *hh_None, MnvH1D *hh_Other,
    char *Playlist_name, std::string pdf_label, char *histotitle,
    std::string units, char *xaxislabel, char *yaxislabel, bool DoBinwidthNorm,
    bool MakeXaxisLOG, bool drawAllErrorGroups, double POT_MC, double POT_DATA);
//============================================================================
void Draw_DataWITHMC_SingleHistinput(MnvH1D *hist_MC, MnvH1D *hist_Data,
                                     char *Playlist_name, std::string pdf_label,
                                     char *histotitle, std::string units,
                                     char *xaxislabel, char *yaxislabel,
                                     bool DoBinwidthNorm, bool MakeXaxisLOG,
                                     double POT_data, double POT_MC,
                                     bool drawAllErrorGroups = true);
//============================================================================
void Draw_DataWITHMC_SingleHistinput_withRatio(
    MnvH1D *hist_MC_input, MnvH1D *hist_Data_input, char *Playlist_name,
    std::string pdf_label, char *histotitle, std::string units,
    char *xaxislabel, char *yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG,
    double POT_data, double POT_MC, bool drawAllErrorGroups = true);
//============================================================================
void Draw_Data_RECO_TRUTH_Hist_fromTFile(
    char *histoName_TRUTH, TFile *inputFile_MCinputFULL,
    TFile *inputFile_MCinputEmpty, char *histoName_MC,
    TFile *inputFile_DatainputFULL, TFile *inputFile_DatainputEmpty,
    char *histoName_data, char *Playlist_name_FULL, char *Playlist_name_EMPTY,
    std::string pdf_label, char *histotitle, char *xaxislabel, char *yaxislabel,
    bool DoBinwidthNorm, bool MakeXaxisLOG, Pot_MapStatusList POT_DATA,
    Pot_MapStatusList POT_MC);
//============================================================================
void Draw_Data_RECO_TRUTH_Hist_fromPointer(
    MnvH1D *histMC_TRUTH, MnvH1D *histMC_RECO, MnvH1D *hist_Data,
    char *Playlist_name, char *playlist_status, std::string pdf_label,
    char *histotitle, char *xaxislabel, char *yaxislabel, bool DoBinwidthNorm,
    bool MakeXaxisLOG, double Ymax);
//============================================================================
void DrawPie_Figures_EventCutRate(
    TFile *inputFile_TRUTHBranch, char *TGraphName_TRUTHBranch,
    TFile *inputFile_RECOBranch, char *TGraphName_RECOBranch_TRUE,
    char *TGraphName_RECOBranch_TRUE_RECO, ME_helium_Playlists playlist,
    ME_helium_Status Crytank_status, const char *pdf, TCanvas *can,
    MnvPlotter *plotter, char *Title);
//============================================================================
void DrawPieFigures(Hist_phyiscs_map Input_map, const char *pdf, TCanvas *can,
                    MnvPlotter *plotter, bool IsReco, bool MakCVS = false,
                    const char *CVS_title = "");
//============================================================================
void DrawPieFigures_withTrackType(Hist_phyiscs_map_withtrack Input_map,
                                  const char *pdf, TCanvas *can,
                                  MnvPlotter *plotter, bool IsReco, bool MakCVS,
                                  const char *CVS_title, char *Title);
//============================================================================
void Draw_TrackTypePieFigures(Hist_map_track Input_map, const char *pdf,
                              TCanvas *can, MnvPlotter *plotter,
                              bool IsRecoOrData, bool MakCVS,
                              const char *CVS_title, char *Title);
//============================================================================
void DrawPieFigures_Interaction(
    std::vector<Interaction_Map> Interaction_Map_vector, const char *pdf,
    TCanvas *can, MnvPlotter *plotter, bool IsReco, bool MakCVS,
    const char *CVS_title, std::string Title_i);
//============================================================================
void Draw_MCHist_fromTFile(TFile *inputFile_MCinput, char *histoName_MC,
                           std::string pdf_label, char *histotitle,
                           char *xaxislabel, char *yaxislabel,
                           bool DoBinwidthNorm);
//============================================================================
TGraphErrors *MakeTGraph_from_Mvn1HD(TFile *inputFile_MCinput,
                                     char *histoName_MC);
//============================================================================
TGraphErrors *MakeTGraph_from_Vectors(std::vector<double> Y_para,
                                      std::vector<double> X_para);
//============================================================================
TGraphErrors *MakeTGraph_from_VectorsErrors(std::vector<double> Y_para,
                                            std::vector<double> y_para_errors,
                                            std::vector<double> X_para);
//============================================================================
TGraphErrors *MakeTGraph_from_VectorsNoErrors(std::vector<double> Y_para,
                                              std::vector<double> X_para);
//============================================================================
TGraph *MakeTGraph_NOERRORS_from_Vectors(std::vector<double> Y_para,
                                         std::vector<double> X_para);
//============================================================================
TGraph *createTGraph(const std::vector<double> xValues,
                     const std::vector<double> yValues);
void Draw_TGraph_fit(TFile *inputFile_MCinput, char *histoName_MC,
                     std::string pdf_label, char *histotitle, char *xaxislabel,
                     char *yaxislabel);
//============================================================================
void Draw_MCHist_fromTFile_andFIT(TFile *inputFile_MCinput, char *histoName_MC,
                                  std::string pdf_label, char *histotitle,
                                  char *xaxislabel, char *yaxislabel);
//============================================================================
void Draw_MCHist_WithErrorBands_fromTFile_andFIT(
    TFile *inputFile_MCinput, char *histoName_MC, std::string pdf_label,
    char *histotitle, char *xaxislabel, char *yaxislabel);
//============================================================================
void Draw_MCHist_fromTFile_SMEARING(TFile *inputFile_MCinput,
                                    char *histoName_MC_CV,
                                    char *histoName_MC_shifts,
                                    std::string pdf_label, char *histotitle,
                                    char *xaxislabel, char *yaxislabel);
//============================================================================
void Draw_MCHist_withErrorSys_fromTFile(TFile *inputFile_MCinput,
                                        char *histoName_MC,
                                        std::string pdf_label, char *histotitle,
                                        char *xaxislabel, char *yaxislabel,
                                        bool DoBinwidthNorm);
//============================================================================
void Draw_RATIO_fromTFiles(TFile *inputFile_Top, char *histoName_Top,
                           char *histoName_TopLabel, TFile *inputFile_Bottom,
                           char *histoName_Bottom, char *histoName_BottomLabel,
                           char *histoName_Ratio, std::string pdf_label,
                           char *histotitle, char *xaxislabel, char *yaxislabel,
                           bool DoBinwidthNorm);
//============================================================================
void Draw_RATIO_fromTFiles(TFile *inputFile_Top, char *histoName_Top,
                           char *histoName_TopLabel, TFile *inputFile_Bottom,
                           char *histoName_Bottom, char *histoName_BottomLabel,
                           char *histoName_Ratio, std::string pdf_label,
                           char *histotitle, char *xaxislabel, char *yaxislabel,
                           bool DoBinwidthNorm, double MinY, double MaxY);
//============================================================================
void Draw_MCHist_withErrorSys_fromTFile(
    TFile *inputFile_MCFull, TFile *inputFile_MCEmpty, char *histoName_MC,
    Pot_MapStatusList POT_MC, Pot_MapStatusList POT_DATA, std::string pdf_label,
    char *histotitle, char *xaxislabel, char *yaxislabel, bool DoBinwidthNorm);
//============================================================================
void DrawVertex_Cryotank_X_Y_R_Vs_Z(std::vector<Vertex_XYZ> input_XYZ_vector,
                                    const char *Playlist, const char *title,
                                    const char *pdf, TCanvas *can,
                                    MnvPlotter *plot);
//============================================================================
void DrawVertex_Cryotank_X_Y_R_Vs_Z(std::vector<Vertex_XYZ> input_XYZ_vector_He,
                                    std::vector<Vertex_XYZ> input_XYZ_vector_Al,
                                    const char *Playlist, const char *title,
                                    const char *pdf, TCanvas *can,
                                    MnvPlotter *plot);
//============================================================================
void DrawFULLStat_CV_SystematicErr(
    ME_playlist_TFileMAP FullMCMap, Pot_MapList FullMC_scalerMap,
    ME_playlist_TFileMAP EmptyMCMap, Pot_MapList EmptyMC_scalerMap,
    ME_playlist_TFileMAP FullDataMap, Pot_MapList FullData_scalerMap,
    ME_playlist_TFileMAP EmptyDataMap, Pot_MapList EmptyData_scalerMap,
    char *histoName_MC, char *histoName_data, std::string units,
    std::string pdf_label, char *hist_title, char *xaxislabel, char *yaxislabel,
    bool DoBinwidthNorm, bool MakeXaxisLOG, bool MakeYaxisLOG,
    bool DrawallErrorGroups = true);
//============================================================================
void DrawFULLStat_CV_SystematicErr(
    ME_playlist_TFileMAP FullMCMap, Pot_MapList FullMC_scalerMap,
    ME_playlist_TFileMAP EmptyMCMap, Pot_MapList EmptyMC_scalerMap,
    char *histoName_MC, std::string pdf_label, char *hist_title,
    char *xaxislabel, char *yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG);
//============================================================================
void DrawFULLStatCOMBINED_CV_SystematicErr(
    ME_playlist_TFileMAP FullMCMap, Pot_MapList FullMC_scalerMap,
    ME_playlist_TFileMAP EmptyMCMap, Pot_MapList EmptyMC_scalerMap,
    ME_playlist_TFileMAP FullDataMap, Pot_MapList FullData_scalerMap,
    ME_playlist_TFileMAP EmptyDataMap, Pot_MapList EmptyData_scalerMap,
    char *histoName_MC, char *histoName_data, std::string units,
    std::string pdf_label, char *hist_title, char *xaxislabel, char *yaxislabel,
    bool DoBinwidthNorm, bool MakeXaxisLOG, bool DrawallErrorGroups = true);
//============================================================================
void DrawFULLStatCOMBINED_CV_SystematicErr(
    ME_playlist_TFileMAP FullMCMap, Pot_MapList FullMC_POTMap,
    Pot_MapList FullData_POTMap, ME_playlist_TFileMAP EmptyMCMap,
    Pot_MapList EmptyMC_POTMap, Pot_MapList EmptyData_POTMap,
    char *histoName_MC, std::string pdf_label, char *hist_title,
    char *xaxislabel, char *yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG);
//============================================================================
void DrawSTACKfromHistFilio_FULLStats(
    ME_playlist_TFileMAP FullMCMap, Pot_MapList FullMC_scalerMap,
    ME_playlist_TFileMAP EmptyMCMap, Pot_MapList EmptyMC_scalerMap,
    ME_playlist_TFileMAP FullDataMap, Pot_MapList FullData_scalerMap,
    ME_playlist_TFileMAP EmptyDataMap, Pot_MapList EmptyData_scalerMap,
    char *histoName_MC, char *histoName_Data, char *histotitle,
    std::string xaxislabel, std::string pdf_label, bool DoBinwidthNorm,
    std::string units, StackType STACKTYPE, bool Debug);
//============================================================================
void DrawSTACKfromHistFilio_FULLStatsCOMBINED(
    ME_playlist_TFileMAP FullMCMap, Pot_MapList FullMC_scalerMap,
    ME_playlist_TFileMAP EmptyMCMap, Pot_MapList EmptyMC_scalerMap,
    ME_playlist_TFileMAP FullDataMap, Pot_MapList FullData_scalerMap,
    ME_playlist_TFileMAP EmptyDataMap, Pot_MapList EmptyData_scalerMap,
    char *histoName_MC, char *histoName_Data, char *histotitle,
    std::string xaxislabel, std::string pdf_label, bool DoBinwidthNorm,
    std::string units, StackType STACKTYPE, bool Debug,
    bool MakeYaxisLOG = false);
//============================================================================
void DrawSTACKfromHistFilio_COMBINED(
    ME_playlist_TFileMAP MCMap, double POTScale_MC_To_DATA,
    ME_playlist_TFileMAP DataMap, double POTScale_Data_To_DATA,
    char *histoName_MC, char *histoName_Data, char *histotitle,
    std::string xaxislabel, std::string pdf_label, bool DoBinwidthNorm,
    std::string units, StackType STACKTYPE, bool Debug, bool MakeYaxisLOG);
//============================================================================
void DrawNonSTACKfromHistFilio_FULLStatsCOMBINED(
    ME_playlist_TFileMAP FullMCMap, Pot_MapList FullMC_POTMap,
    ME_playlist_TFileMAP EmptyMCMap, Pot_MapList EmptyMC_POTMap,
    ME_playlist_TFileMAP FullDataMap, Pot_MapList FullData_POTMap,
    ME_playlist_TFileMAP EmptyDataMap, Pot_MapList EmptyData_POTMap,
    char *histoName_MC, char *histoName_Data, char *histotitle,
    std::string xaxislabel, std::string pdf_label, bool DoBinwidthNorm,
    std::string units, StackType STACKTYPE, bool Debug);
//============================================================================
void Draw_2D_Panel_MC_andData_frompointer(
    MnvH2D *hist_Data, MnvH2D *hist_MC, char *histotitle,
    std::string xaxislabel, std::string yaxislabel, const char *Zaxislabel,
    double max_x, double max_y, char *pdf_label, bool doBinwidth,
    bool MakeXaxisLOG, double x_projectionTxtsize, double y_projectionTxtsize,
    bool doMultiplier = false);
//============================================================================
void Draw_2D_Panel_MC_andData_frompointer(
    MnvH2D *hist_Data, MnvH2D *hist_MC,
    PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type> hist_Stack,
    char *histotitle, std::string xaxislabel, std::string yaxislabel,
    const char *Zaxislabel, double max_x, double max_y, char *pdf_label,
    bool doBinwidth, bool MakeXaxisLOG, double x_projectionTxtsize,
    double y_projectionTxtsize);
//============================================================================
void MakeData_trajector(std::vector<Trajector_DATA> input_vector,
                        const char *Playlist, double Spaceingcm,
                        const char *pdf, TCanvas *can, MnvPlotter *plot);
//============================================================================
void Draw2DHist_hist(MnvH2D *hist_input, const char *Title,
                     const char *xaxislabel, const char *yaxislabel,
                     const char *pdf, TCanvas *can, MnvPlotter *plot);
//============================================================================
void Draw2DHist(  MnvH2D *hist, const char* xaxislabel,
  const char* yaxislabel, const char* Title,
  const char* pdf, TCanvas *can,
  MnvPlotter *plot, double setMax);
//============================================================================
void Draw2DHist_hist_notext(MnvH2D *hist_input, const char *Title,
                            const char *xaxislabel, const char *yaxislabel,
                            const char *pdf, TCanvas *can, MnvPlotter *plot,
                            bool includeFlows = false);
//============================================================================
void Draw2DRatio_FromTFile(TFile *inputFile_numerator,
                           TFile *inputFile_demonator, char *histoName_num,
                           char *histoName_dem, char *num_labelname_y,
                           char *dem_labelname_y, char *num_labelname_x,
                           char *dem_labelname_x, char *histotitle,
                           const char *pdf, TCanvas *can, MnvPlotter *plot);
//============================================================================
void DrawTGraph(TGraphErrors *g_TGraph1, TGraphErrors *g_TGraph2,
                TGraphErrors *g_TGraph3, const char *xaxislabel,
                const char *yaxislabel, const char *Title,
                const char *legend_Title1, const char *legend_Title2,
                const char *legend_Title3, const char *pdf, TCanvas *can,
                MnvPlotter *plot, bool MakeXaxisLOG, bool MakeYaxisLOG,
                bool setGrid = false, bool doMax = false);
//============================================================================
void DrawTGraph(TGraphErrors *g_TGraph1, TGraphErrors *g_TGraph2,
                const char *xaxislabel, const char *yaxislabel,
                const char *Title, const char *legend_Title1,
                const char *legend_Title2, const char *pdf, TCanvas *can,
                MnvPlotter *plot, bool MakeXaxisLOG, bool MakeYaxisLOG,
                bool doMax = true);
//============================================================================
void DrawTGraph(TGraph *g_TGraph1, TGraph *g_TGraph2, const char *xaxislabel,
                const char *yaxislabel, const char *Title,
                const char *legend_Title1, const char *legend_Title2,
                const char *pdf, TCanvas *can, MnvPlotter *plot,
                bool MakeXaxisLOG = false, bool MakeYaxisLOG = false,
                bool doMax = true);
//============================================================================
void DrawTGraph(TGraphErrors *g_TGraph, const char *xaxislabel,
                const char *yaxislabel, const char *Title,
                const char *legend_Title, const char *pdf, TCanvas *can,
                MnvPlotter *plot, bool MakeXaxisLOG, bool MakeYaxisLOG);
//============================================================================
void DrawTGraph_GaussianFit(TGraph *g_TGraph, const char *xaxislabel,
                            const char *yaxislabel, const char *Title,
                            const char *legend_Title, const char *pdf,
                            TCanvas *can, MnvPlotter *plot, bool MakeXaxisLOG,
                            bool MakeYaxisLOG, double MinXfit, double MaxXfit);
//============================================================================
void DrawTGraph(TGraph *g_TGraph, const char *xaxislabel,
                const char *yaxislabel, const char *Title,
                const char *legend_Title, const char *pdf, TCanvas *can,
                MnvPlotter *plot, bool MakeXaxisLOG, bool MakeYaxisLOG);
//============================================================================
void DrawTGraph_withArrow(TGraphErrors *g_TGraph, const char *xaxislabel,
                          const char *yaxislabel, const char *Title,
                          const char *legend_Title, const char *pdf,
                          TCanvas *can, MnvPlotter *plot, bool MakeXaxisLOG,
                          bool MakeYaxisLOG, const double cut_location,
                          const double y1_arrow, const double y2_arrow,
                          const double arrow_length,
                          const std::string arrow_direction);
//============================================================================
void DrawTGraph_PolyFit(TGraph *g_TGraph, const char *xaxislabel,
                        const char *yaxislabel, const char *Title,
                        const char *legend_Title, const char *legend_Title_fit,
                        const char *pdf, TCanvas *can, MnvPlotter *plot,
                        bool MakeXaxisLOG, bool MakeYaxisLOG, double MinXfit,
                        double MaxXfit, char *functionName);
//============================================================================
double FindMaxSecondDerivative(TF1 *fitFunc, double range_min,
                               double range_max);
//============================================================================
TF1 *createPolynomialFunction(int N, double xmin, double xmax,
                              double *parameters);
//============================================================================
std::vector<Track_Map> Track_vector(TObjArray *Hists_vector, bool doPOTscaling,
                                    double scaler);
//============================================================================
std::vector<boolNTrack_Map> boolNTrack_vector(TObjArray *Hists_vector,
                                              bool doPOTscaling, double scaler);
//============================================================================
std::vector<VertexOptions_Map> vertexOption_vector(TObjArray *Hists_vector,
                                                   bool doPOTscaling,
                                                   double scaler);
//============================================================================
Hist_phyiscs_map_withtrack Make_Physics_withTrack_distribution_map_FromTFile(
    TFile *inputTFile, char *histoName_MC, bool UsePotScaling, double POTScale,
    ME_helium_Playlists playlist, bool IsRecoOrTruth);
//============================================================================
Hist_map_track Make_Track_distribution_map_FromTFile(
    TFile *inputTFile, char *histoName, bool UsePotScaling, double POTScale,
    ME_helium_Playlists playlist, bool IsRecoOrTruth, bool isData);
//============================================================================
void DrawSTACK_FORDATAONLY_fromHistFilio_FromTFile(
    TFile *inputFile_DATAFULL, TFile *inputFile_DATAEMPTY, char *histoName_Data,
    Pot_MapStatusList POT_DATA, bool TrueifFullelseEmpty, char *histotitle,
    std::string xaxislabel, std::string pdf_label, bool DoBinwidthNorm,
    std::string units, StackType STACKTYPE, bool Debug);
//============================================================================
void FillFitParms(TF1 *gfit, GaussianFitsParms &FitParms);
//============================================================================
void Draw_TGraphs_fitParams(
    std::vector<GaussianFitsParms> GaussianFits_values_Resolution_vector,
    const char *pdf_label, char *histotitle, TCanvas *cE,
    MnvPlotter *mnvPlotter, bool Xlog = false, bool Ylog = false);
//============================================================================
void Draw_TGraphs_fitParams(
    std::vector<GaussianFitsParms> GaussianFits_helium,
    std::vector<GaussianFitsParms> GaussianFits_nonhelium,
    std::vector<GaussianFitsParms> GaussianFits_total, const char *pdf_label,
    char *histotitle, TCanvas *cE, MnvPlotter *mnvPlotter, bool Xlog = false,
    bool Ylog = false, bool setGrid = false, char *Playlist = "");
//============================================================================
void Draw_XDistribution_PerBinWithGaussFit_2DHist(
    MnvH2D *hist_input, const char *Title, const char *xaxislabel,
    const char *yaxislabel, const char *pdf, TCanvas *can, MnvPlotter *plot,
    bool Setgrid, Double_t maxY);
//============================================================================
void Draw_XDistribution_PerBinWithGaussFit_2DHist(
    MnvH2D *hist_total, MnvH2D *hist_input_Helium, MnvH2D *hist_input_NonHelium,
    const char *Title, const char *xaxislabel, const char *yaxislabel,
    const char *pdf, char *Playlist, TCanvas *can, MnvPlotter *plot,
    bool Setgrid, Double_t maxY, bool LogX, bool LogY);
//============================================================================
void DrawCVAndError_From2HIST_withFit(
    MnvH1D *hist_total, MnvH1D *histHelium, MnvH1D *histnonHelium,
    char *histotitle, std::string xaxislabel, std::string yaxislabel,
    std::string pdf_name, bool Setgrid, GaussianFitsParms &total_FitParms,
    GaussianFitsParms &helium_FitParms, GaussianFitsParms &nonhelium_FitParms,
    bool PrintErrors, bool PrintallErrorGroups, bool BinWidthNorm = false);
//============================================================================
void DrawCVAndError_From2HIST(MnvH1D *hist_total, MnvH1D *histHelium,
                              MnvH1D *histnonHelium, char *histotitle,
                              std::string xaxislabel, std::string yaxislabel,
                              std::string pdf_name, bool Setgrid,
                              bool PrintErrors, bool PrintallErrorGroups,
                              bool BinWidthNorm, double Ymax,
                              bool setLogY = false);
//============================================================================//============================================================================
void DrawCVAndError_From2HIST(MnvH1D *hist_1_input, char *legend_1_title,
                              MnvH1D *hist_2_input, char *legend_2_title,
                              char *histotitle, std::string xaxislabel,
                              std::string yaxislabel, std::string pdf_name,
                              bool Setgrid, bool PrintErrors,
                              bool PrintallErrorGroups, bool BinWidthNorm,
                              double Ymax, bool setLogY = false,
                              bool setLogX = false);
//============================================================================//============================================================================
void DrawCVAndError_From2HIST(TH1D *hist_1, char *legend_1_title, TH1D *hist_2,
                              char *legend_2_title, char *histotitle,
                              std::string xaxislabel, std::string yaxislabel,
                              std::string pdf_name, bool Setgrid,
                              bool BinWidthNorm, double Ymax, bool setLogY);
//============================================================================//============================================================================
void DrawCVAndError_From2HIST_test(MnvH1D *hist_1_input, char *legend_1_title,
                                   MnvH1D *hist_2_input, char *legend_2_title,
                                   char *histotitle, std::string xaxislabel,
                                   std::string yaxislabel, std::string pdf_name,
                                   bool Setgrid, bool BinWidthNorm, double Ymax,
                                   double Ymin, bool setLogY);
//============================================================================
void DrawCVAndError_From_L_2HIST_RHist_test(
    MnvH1D *hist_1_input, char *legend_1_title, MnvH1D *hist_2_input,
    char *legend_2_title, MnvH1D *hist_3_input, char *legend_3_title,
    char *histotitle, std::string xaxislabel, std::string yaxislabel,
    std::string yaxislabel_right, std::string pdf_name, bool Setgrid,
    bool BinWidthNorm, double Ymax, double Ymin, bool setLogY,
    bool setLogY_right = false);
//============================================================================
void DrawCVAndError_From_R_2HIST_LHist_test(
    MnvH1D *hist_1_input, char *legend_1_title, MnvH1D *hist_2_input,
    char *legend_2_title, MnvH1D *hist_3_input, char *legend_3_title,
    char *histotitle, std::string xaxislabel, std::string yaxislabel,
    std::string yaxislabel_right, std::string pdf_name, bool Setgrid,
    bool BinWidthNorm, double Ymax, double Ymin, bool setLogY,
    bool setLogY_right = false);
//============================================================================
void DrawCVAndError_From_L_2HIST_RHist_test2(
    MnvH1D *hist_1_input, char *legend_1_title, MnvH1D *hist_2_input,
    char *legend_2_title, MnvH1D *hist_3_input, char *legend_3_title,
    char *histotitle, std::string xaxislabel, std::string yaxislabel,
    std::string yaxislabel_right, std::string pdf_name, bool Setgrid,
    bool BinWidthNorm, double Ymax, double Ymin, bool setLogY,
    bool setLogY_right = false);
//============================================================================
void DrawCVAndError_From6HIST(MnvH1D *hist_1_input, char *legend_1_title,
                              MnvH1D *hist_2_input, char *legend_2_title,
                              MnvH1D *hist_3_input, char *legend_3_title,
                              MnvH1D *hist_4_input, char *legend_4_title,
                              MnvH1D *hist_5_input, char *legend_5_title,
                              MnvH1D *hist_6_input, char *legend_6_title,
                              char *histotitle, std::string xaxislabel,
                              std::string yaxislabel, std::string pdf_name,
                              bool Setgrid, bool PrintErrors,
                              bool PrintallErrorGroups, bool BinWidthNorm,
                              double Ymax, bool setLogY, bool setLogX);
//============================================================================
void DrawCVAndError_From6HIST_RECO_vs_TRUE(
    MnvH1D *hist_total_TRUE, MnvH1D *histHelium_TRUE,
    MnvH1D *histnonHelium_TRUE, MnvH1D *hist_total_RECO,
    MnvH1D *histHelium_RECO, MnvH1D *histnonHelium_RECO, char *histotitle,
    std::string xaxislabel, std::string yaxislabel, std::string pdf_name,
    bool Setgrid, bool PrintErrors, bool PrintallErrorGroups, bool BinWidthNorm,
    double Ymax, bool setLogY = false);
//============================================================================
void DrawCVAndError_FromHIST(bool PrintALLerrorGroups, MnvH1D *hist,
                             char *histotitle, std::string xaxislabel,
                             std::string yaxislabel, std::string pdf_name,
                             bool Setgrid, bool doBinwidth, bool SetYlimits,
                             double Ymin, double Ymax,
                             const double cut_location, const double y1_arrow,
                             const double y2_arrow, const double arrow_length,
                             const std::string arrow_direction);
//============================================================================
void Draw_TGraphs_NEvent_FidiucalCut(
    std::vector<NEvent_FidiucalCut> NEvent_FidiucalCut_vector,
    const char *pdf_label, char *histotitle, const char *playlist, TCanvas *cE,
    MnvPlotter *mnvPlotter, bool Xlog, bool Ylog);
//============================================================================//============================================================================
void Draw_TGraphs_NEventONLY_FidiucalCut(
    std::vector<NEvent_FidiucalCut> NEvent_FidiucalCut_vector,
    const char *pdf_label, char *histotitle, const char *playlist, TCanvas *cE,
    MnvPlotter *mnvPlotter, bool Xlog, bool Ylog);
//============================================================================//============================================================================
void Draw_YDistribution_PerBin_2DHist_Purity_Efficiency(
    MnvH2D *hist_input_Numerator, MnvH2D *hist_input_Denominator,
    MnvH2D *hist_input_Total, MnvH2D *hist_input_Helium_RECO,
    MnvH2D *hist_input_NonHelium_RECO, const char *Title,
    const char *xaxislabel, const char *yaxislabel, const char *playlist,
    const char *pdf, TCanvas *can, MnvPlotter *plot, bool Setgrid,
    double maxY_recoCuts, double maxY_TruthCuts, bool LogX, bool LogY);
//============================================================================
void Draw_YDistribution_PerBin_2DHist_Purity_Efficiency(
    MnvH2D *hist_input_Numerator, MnvH2D *hist_input_Denominator,
    MnvH2D *hist_input_Total, MnvH2D *hist_input_Helium_RECO,
    MnvH2D *hist_input_NonHelium_RECO, MnvH2D *hist_input_Efficiency,
    const char *Title, const char *xaxislabel, const char *yaxislabel,
    const char *playlist, const char *pdf, TCanvas *can, MnvPlotter *plot,
    bool Setgrid, double maxY_recoCuts, double maxY_TruthCuts, bool LogX,
    bool LogY);
//============================================================================
void Draw_YDistribution_PerBin_2DHist(
    MnvH2D *hist_input_Total, MnvH2D *hist_input_Helium_RECO,
    MnvH2D *hist_input_NonHelium_RECO, const char *Title,
    const char *xaxislabel, const char *yaxislabel, const char *playlist,
    const char *pdf, TCanvas *can, MnvPlotter *plot, bool Setgrid,
    double maxY_recoCuts, bool LogX, bool LogY);
//============================================================================
void DrawCVAndError_eff_purity_EOM_ERROR(MnvH1D *hist_eff, MnvH1D *hist_pur,
                                         char *histotitle,
                                         std::string xaxislabel,
                                         const char *pdf, bool doBinwidth,
                                         double Ymax,
                                         std::vector<double> BinsEdges_vector);
//============================================================================
void SetUpMigration_BybinN(TH2D &hist, bool includeFlows, double markersize,
                           const char *Ztitle);
//============================================================================
void SetUpMigration_BybinN(MnvH2D &hist, bool includeFlows, double markersize,
                           const char *Ztitle);
//============================================================================
void SetUpMigration(TH2D &hist, bool includeFlows, double markersize,
                    const char *Xaxis, const char *Yaxis, const char *Ztitle);
//============================================================================
void SetUpMigration(MnvH2D &hist, bool includeFlows, double markersize,
                    const char *Xaxis, const char *Yaxis, const char *Ztitle);
//============================================================================
void DrawCVAndError_3tankRegionsHIST_withRMS(
    MnvH1D *hist_upstreamCap, MnvH1D *hist_barrel, MnvH1D *hist_downstreamCap,
    char *histotitle, std::string xaxislabel, std::string yaxislabel,
    char *Units, std::string pdf_name, bool Setgrid, bool doBinwidth,
    bool PrintRMS_percentage, bool AreaNormalized, double YMax);
//============================================================================
void Draw_2DPlotFromVectors(std::vector<double> Xaxis,
                            std::vector<double> Yaxis,
                            std::vector<double> Zaxis, char *histotitle,
                            char *xaxislabel, char *yaxislabel,
                            char *zaxislabel, MnvPlotter *plot, TCanvas *can,
                            char *pdf);
//============================================================================
void SetLineForCryoPlots(TGraph &Tg_result, int color);
//============================================================================
void Draw_FourFitRegion_CryoTank(std::string pdf, TCanvas *can,
                                 MnvPlotter *plot);
//============================================================================
void DrawVertex_Cryotank_X_Y_R_Vs_Z_4regions(
    std::vector<Vertex_XYZ> input_XYZ_vectorupstream,
    std::vector<Vertex_XYZ> input_XYZ_vectorbarrel,
    std::vector<Vertex_XYZ> input_XYZ_vectordownstream,
    std::vector<Vertex_XYZ> input_XYZ_vectordownstreamconcave,
    const char *Playlist, const char *title, const char *pdf, TCanvas *can,
    MnvPlotter *plot);
//============================================================================
void Draw_MCInteractions_FractionEvents(MnvH1D *h_elastic, MnvH1D *h_2p2h,
                                        MnvH1D *h_deltaRes,
                                        MnvH1D *h_heavierRes, MnvH1D *h_DISSIS,
                                        MnvH1D *h_DISSoft, MnvH1D *h_DIShard,
                                        MnvH1D *h_None, MnvH1D *h_Other,
                                        std::string pdf_label, char *histotitle,
                                        char *xaxislabel, char *yaxislabel);
//============================================================================
void Draw_MCInteractions_FractionEvents(MnvH1D *h_Total, MnvH1D *h_elastic,
                                        MnvH1D *h_2p2h, MnvH1D *h_deltaRes,
                                        MnvH1D *h_heavierRes, MnvH1D *h_DISSIS,
                                        MnvH1D *h_DISSoft, MnvH1D *h_DIShard,
                                        MnvH1D *h_None, MnvH1D *h_Other,
                                        std::string pdf_label, char *histotitle,
                                        char *xaxislabel, char *yaxislabel);
//============================================================================
void Draw_inputTranswarpHist_fromPointers(
    MnvH1D *h_data, MnvH1D *h_data_true, MnvH1D *h_mc_reco, MnvH1D *h_mc_true,
    bool AreaNorm_todata, std::string pdf_label, char *histotitle,
    char *xaxislabel, char *yaxislabel_units, bool DoBinwidthNorm,
    bool MakeXaxisLOG, double Ymax, bool makeYmax);
//============================================================================
void Draw_TransWarp_converage(MnvH2D *hist2D, MnvH1D *hist1D_mean,
                              MnvH1D *hist1D_median, int var_ndf,
                              char *xaxislabel, char *yaxislabel,
                              char *zaxislabel, char *Title, char *pdf,
                              TCanvas *can, MnvPlotter *plot, double SetZMax,
                              bool MakeLogY = false);
//============================================================================
void test2(char *pdf, MnvH2D *hist2D);
//============================================================================
void DrawCVAndError_From2HIST_ndflines(TH1D *hist_1, char *legend_1_title,
                                       TH1D *hist_2, char *legend_2_title,
                                       char *histotitle, std::string xaxislabel,
                                       std::string yaxislabel,
                                       std::string pdf_name, bool Setgrid,
                                       bool BinWidthNorm, double Ymax,
                                       bool setLogY, double ndf);
//============================================================================
void DrawCVAndError_FromHIST_withGaussianPeak(
    MnvH1D *hist_input, char *histotitle, std::string xaxislabel,
    std::string yaxislabel, std::string pdf_name, bool Setgrid,
    double reduceSpread, double par1, double par2, double Scaleup,
    double range1, double range2);
//============================================================================
void Draw2DHist_warpFit2DGaussian(MnvH2D *hist_input, const char *xaxislabel,
                                  const char *yaxislabel, const char *Title,
                                  const char *pdf, TCanvas *can,
                                  MnvPlotter *plot);
//============================================================================
void Draw2DHist_warpFit2DGaussian(MnvH2D *hist_input, const char *xaxislabel,
                                  const char *yaxislabel, const char *Title,
                                  const char *pdf, TCanvas *can,
                                  MnvPlotter *plot, double MinX, double MaxX);
//============================================================================
void Draw2DHist_warpFit2DGaussian(
    MnvH2D *hist_input, const char *xaxislabel, const char *yaxislabel,
    double chi2fit, double ndfinput, double par0, double par1, double par2,
    double par3, double par4, double par_Error0, double par_Error1,
    double par_Error2, double par_Error3, double par_Error4, const char *Title,
    const char *pdf, TCanvas *can, MnvPlotter *plot);
//============================================================================
void DrawCVAndError_FromHIST_withFit_Npoly(
    MnvH1D *hist_input, char *histotitle, std::string xaxislabel,
    std::string yaxislabel, std::string pdf_name, bool Setgrid,
    char *functionName, const int N_funtion, char *Print_pars);
//============================================================================
void DrawCVAndError_FromHIST_withFit_Npoly_PZ(
    MnvH1D *hist_input, char *histotitle, std::string xaxislabel,
    std::string yaxislabel, std::string pdf_name, bool Setgrid);
//============================================================================
void DrawCVAndError_FromHIST_withFit_3poly_PZ_Daisy(
  MnvH1D *hist_input, char *histotitle ,std::string xaxislabel,
  std::string yaxislabel, std::string pdf_name, bool Setgrid, Double_t *par );
  //============================================================================
void DrawCVAndError_FromHIST_withFit_Npoly_PT(
    MnvH1D *hist_input, char *histotitle, std::string xaxislabel,
    std::string yaxislabel, std::string pdf_name, bool Setgrid);
//============================================================================
void DrawCVAndError_FromHIST_withFit_3poly_PT_Daisy(
  MnvH1D *hist_input, char *histotitle,
  std::string xaxislabel,std::string yaxislabel,
  std::string pdf_name, bool Setgrid, Double_t *par );
//============================================================================
void DrawCVAndError_FromHIST_withFit_Npoly_E(
  MnvH1D *hist_input, char *histotitle, std::string xaxislabel,
  std::string yaxislabel, std::string pdf_name, bool Setgrid);
//============================================================================
void DrawCVAndError_FromHIST_withFit_3poly_E_Daisy(
  MnvH1D *hist_input, char *histotitle, std::string xaxislabel,
  std::string yaxislabel,std::string pdf_name, bool Setgrid, Double_t *par );
//============================================================================
void DrawCVAndError_FromHIST_withFit_Npoly_theta(
  MnvH1D *hist_input, char *histotitle, std::string xaxislabel,
  std::string yaxislabel, std::string pdf_name, bool Setgrid);
//============================================================================
void DrawCVAndError_FromHIST_withFit_3poly_theta_Daisy(
  MnvH1D *hist_input, char *histotitle, std::string xaxislabel,
  std::string yaxislabel, std::string pdf_name, bool Setgrid, Double_t *par );
  //============================================================================
void DrawCovarientMatrix_FromHistPointer(MnvH1D *hist, char *histotitle,
                                         std::string xaxislabel,
                                         std::string yaxislabel,
                                         std::string pdf_label);
//============================================================================
Double_t Gaussian2D(Double_t *x, Double_t *par);
//============================================================================
Double_t Gaussianfun3(Double_t *x, Double_t *par);
//============================================================================
Double_t Poly6_1D(Double_t *x, Double_t *par);
//============================================================================
Double_t Poly5_1D(Double_t *x, Double_t *par);
//============================================================================
Double_t Poly4_1D(Double_t *x, Double_t *par);
//============================================================================
Double_t Poly3_1D(Double_t *x, Double_t *par);
//============================================================================
Double_t WarpingFunctionPZ_PT_GeV(Double_t *x, Double_t *par);
//============================================================================
double WarpingFunctionPZ_PT_GeV(double True_PZ, double True_PT);
//============================================================================
Double_t WarpingFunctionPZ_GeV(Double_t *x, Double_t *par);
//============================================================================
double WarpingFunction_Daisy_PZ_GeV(double TruePZ, Double_t *par );
//============================================================================
Double_t WarpingFunction_DAISY_poly3_PZ_GeV(Double_t *x, Double_t *par);
//============================================================================
double WarpingFunctionPZ_GeV(double TruePZ);
//============================================================================
Double_t WarpingFunctionPT_GeV(Double_t *x, Double_t *par);
//============================================================================
double WarpingFunctionPT_GeV(double TruePT);
//============================================================================
Double_t WarpingFunction_DAISY_poly3_PT_GeV(Double_t *x, Double_t *par);
//============================================================================
double WarpingFunction_DAISY_PT_GeV(double TruePT, Double_t *par);
//============================================================================
Double_t WarpingFunctionE_GeV(Double_t *x, Double_t *par);
//============================================================================
Double_t WarpingFunction_DAISY_poly3_E_GeV(Double_t *x, Double_t *par);
//============================================================================
double WarpingFunctionE_GeV(double TrueE);
//============================================================================
double WarpingFunction_Daisy_E_GeV(double TrueE, Double_t *par);
//============================================================================
Double_t WarpingFunctionTheta_Deg(Double_t *x, Double_t *par);
//============================================================================
double WarpingFunctionTheta_Deg(double TrueTheta);
//============================================================================
Double_t WarpingFunction_DAISY_poly3_Theta_Deg(Double_t *x, Double_t *par);
//============================================================================
double WarpingFunctionTheta_Deg(double TrueTheta,Double_t *par);
//============================================================================
void DrawCVAndError_From5HIST(MnvH1D *hist_Data_input, char *legend_Data_title,
                              TH1D *hist_1_input, char *legend_1_title,
                              TH1D *hist_2_input, char *legend_2_title,
                              TH1D *hist_3_input, char *legend_3_title,
                              TH1D *hist_4_input, char *legend_4_title,
                              TH1D *hist_5_input, char *legend_5_title,
                              std::vector<int> fillColors, char *histotitle,
                              std::string xaxislabel, std::string yaxislabel,
                              std::string pdf_name, bool Setgrid,
                              bool BinWidthNorm, double Ymax, bool setLogY);
//============================================================================
void DrawCVAndError_From5HIST(
    MnvH1D *hist_1_input, char *legend_1_title, MnvH1D *hist_2_input,
    char *legend_2_title, MnvH1D *hist_3_input, char *legend_3_title,
    MnvH1D *hist_4_input, char *legend_4_title, MnvH1D *hist_5_input,
    char *legend_5_title, char *histotitle, std::string xaxislabel,
    std::string yaxislabel, std::string pdf_name, bool Setgrid,
    bool PrintErrors, bool PrintallErrorGroups, bool BinWidthNorm, double Ymax,
    double Ymin, bool setLogY, bool setLogX);
//============================================================================
void DrawCVAndError_FromDaisyHIST(
    MnvH1D *hist_tracker_input, char *legend_tracker_title,
    MnvH1D *hist_0_input, char *legend_0_title, MnvH1D *hist_1_input,
    char *legend_1_title, MnvH1D *hist_2_input, char *legend_2_title,
    MnvH1D *hist_3_input, char *legend_3_title, MnvH1D *hist_4_input,
    char *legend_4_title, MnvH1D *hist_5_input, char *legend_5_title,
    MnvH1D *hist_6_input, char *legend_6_title, MnvH1D *hist_7_input,
    char *legend_7_title, MnvH1D *hist_8_input, char *legend_8_title,
    MnvH1D *hist_9_input, char *legend_9_title, MnvH1D *hist_10_input,
    char *legend_10_title, MnvH1D *hist_11_input, char *legend_11_title,
    char *histotitle, std::string xaxislabel, std::string yaxislabel,
    std::string pdf_name, bool Setgrid, bool BinWidthNorm, double Ymax,
    bool setLogY, bool setLogX);
//============================================================================
#endif
