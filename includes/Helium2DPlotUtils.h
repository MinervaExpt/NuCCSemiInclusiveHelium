#ifndef HELIUM2DPLOTUTILS_H
#define HELIUM2DPLOTUTILS_H

#include "GridCanvas.h"

//#include "TCanvas.h"
#include "PlotUtils/MnvVertErrorBand.h"
#include "PlotUtils/MnvPlotter.h"
#include "PlotUtils/HistogramUtils.h"
#include "PlotUtils/MnvH1D.h"
//#include "PlotUtils/GridCanvas.h"
#include "HeliumCuts.h"
#include <iostream>
#include "HeliumUtils.h"
#include "Helium2DUtils.h"
#include "HeliumDefaults.h"
#include <TStyle.h>

#include "PlotUtils/MnvH2D.h"
// #include "../util/plot/plot.h"

#include "TLatex.h"
#include "TLegend.h"
#include "TStopwatch.h"
#include "TEnv.h"
#include "TChain.h"
#include "TF2.h"
#include "Math/DistFunc.h"
#include "TGraphErrors.h"
#include "TFile.h"
#include "TColor.h"
//#include "panel_plotting/myPlotStyle.h"
//#include "panel_plotting/localColor.h"
//#include "panel_plotting/LinkDef.h"
//#include "panel_plotting/GridCanvas.h"
//#include "panel_plotting/plot.h"
//#include "panel_plotting/plot.h"
#include "plot.h"
#include "myPlotStyle.h"
#include "localColor.h"
#include "HeliumPlotUtils.h"
//#include "panel_plotting/LinkDef.h"

//#include "panel_plotting/plot.h"

// const Particle_color_map Particle_COLORMAP;

// const Material_color_map Material_COLORMAP;
// const Interaction_color_map Interaction_COLORMAP;
/////===============================================================================================
std::vector<double> GetScales_2d(
    std::vector<std::pair<TH2 *, const char *> > histopts, bool pzProj);
/////===============================================================================================
std::vector<double> Normlized_to_lowest_Mulitplers_2d(
    std::vector<double> multiply_vector);
/////===============================================================================================
std::vector<double> GetScales_2d(
    std::vector<std::pair<TH2 *, const char *> > histopts, bool pzProj,
    bool donormalized);
/////===============================================================================================
std::vector<double> Normlized_to_lowest_Mulitplers(
    std::vector<double> multiply_vector);
/////===============================================================================================
std::vector<std::pair<TH2 *, const char *> > Make_pannelhis_vector(
    MnvH2D *data, const TObjArray *mcHists, StackType STACKTYPE, TLegend *leg,
    int Plottype = 0);
/////===============================================================================================
/////===============================================================================================
void Draw2DCVAndError_FromTFile(
    TFile *inputFile_MCFULL, TFile *inputFile_MCEMPTY, char *histoName_MC,
    TFile *inputFile_DATAFULL, TFile *inputFile_DATAEMPTY, char *histoName_Data,
    Pot_MapStatusList POT_MC, Pot_MapStatusList POT_DATA,
    bool TrueifFullelseEmpty, char *histotitle, std::string xaxislabel,
    std::string yaxislabel, std::string yaxislabel_units, std::string pdf_label,
    bool DoBinwidthNorm, bool doSmallerrorgrounps, int Print_Error, bool Debug);
/////===============================================================================================
void DrawSTACKfromHistFilio_FromTFile2D(
    TFile *inputFile_MCFULL, TFile *inputFile_MCEMPTY, char *histoName_MC,
    TFile *inputFile_DATAFULL, TFile *inputFile_DATAEMPTY, char *histoName_Data,
    Pot_MapStatusList POT_MC, Pot_MapStatusList POT_DATA,
    bool TrueifFullelseEmpty, char *histotitle, std::string xaxislabel,
    std::string yaxislabel, const char *yaxisUNITS, std::string pdf_label,
    bool DoBinwidthNorm, bool doSmallerrorgrounps, StackType STACKTYPE,
    bool Debug);
/////===============================================================================================
void DrawSTACKfromHistFilio_FromTFile2D(
    TFile *inputFile_MC, char *histoName_MC, TFile *inputFile_DATA,
    char *histoName_Data, double POT_MC_to_Data, char *histotitle,
    std::string xaxislabel, std::string yaxislabel, char *zaxislabel_units,
    std::string pdf_label, bool DoBinwidthNorm, StackType STACKTYPE, bool Debug,
    bool doMultipliers, std::vector<double> YMultipliers,
    std::vector<double> XMultipliers);
/////===============================================================================================
void Draw2D_Migration_FromTFile(
    TFile *inputFile_MCFULL, TFile *inputFile_MCEMPTY, char *histoName_MC_Mig,
    char *histoName_MC_RECO, char *histoName_MC_TRUTH, Pot_MapStatusList POT_MC,
    char *histotitle, char *Fullplaylist_name, char *Emptyplaylist_name,
    std::string xaxislabel, std::string yaxislabel,
    std::string yaxislabel_units, std::string pdf_label, bool DoBinwidthNorm,
    bool Debug);
/////===============================================================================================
void Draw2DFULLStat_CV_SystematicErr(
    ME_playlist_TFileMAP FullMCMap, Pot_MapList FullMC_scalerMap,
    ME_playlist_TFileMAP EmptyMCMap, Pot_MapList EmptyMC_scalerMap,
    ME_playlist_TFileMAP FullDataMap, Pot_MapList FullData_scalerMap,
    ME_playlist_TFileMAP EmptyDataMap, Pot_MapList EmptyData_scalerMap,
    char *histoName_MC, char *histoName_data, char *pdf_label, char *hist_title,
    char *xaxislabel, char *yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG,
    double max_x, double max_y, double x_projectionTxtsize,
    double y_projectionTxtsize);
/////===============================================================================================
void Draw2DFULLStat_CV_SystematicErrFromPointer(
    MnvH2D *hist_Data, MnvH2D *hist_MC, ME_helium_Playlists playlist,
    MnvPlotter *plot, char *pdf_label, char *hist_title, char *xaxislabel,
    char *yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG, double max_x,
    double max_y, double x_projectionTxtsize, double y_projectionTxtsize,
    double &chisqrt, int &ndf, bool TurnoffPrinting);
/////===============================================================================================
void Draw2D_Panel_CV_SystematicErrFromPointer(
    MnvH2D *hist_Data, MnvH2D *hist_MC, char *playlistInfo_char,
    char *HeliumStatus_name_char, MnvPlotter *mnvPlotter, char *pdf_label,
    char *hist_title, char *xaxislabel, char *yaxislabel, char *zaxislabel,
    bool DoBinwidthNorm, bool MakeXaxisLOG, double max_x, double max_y,
    double x_projectionTxtsize, double y_projectionTxtsize, double &chisqrt,
    int &ndf, bool doMultipliers = false);
/////===============================================================================================
void Draw2DFULLStatCOMBINED_CV_SystematicErr(
    ME_playlist_TFileMAP FullMCMap, Pot_MapList FullMC_POTMap,
    ME_playlist_TFileMAP EmptyMCMap, Pot_MapList EmptyMC_POTMap,
    ME_playlist_TFileMAP FullDataMap, Pot_MapList FullData_POTMap,
    ME_playlist_TFileMAP EmptyDataMap, Pot_MapList EmptyData_POTMap,
    char *histoName_MC, char *histoName_data, char *pdf_label, char *hist_title,
    char *xaxislabel, char *yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG,
    double max_x, double max_y, double x_projectionTxtsize,
    double y_projectionTxtsize);
/////===============================================================================================

void Draw2DFULLStat_2dplotSingle(
    ME_playlist_TFileMAP FullMCMap, Pot_MapList FullMC_scalerMap,
    ME_playlist_TFileMAP EmptyMCMap, Pot_MapList EmptyMC_scalerMap,
    ME_playlist_TFileMAP FullDataMap, Pot_MapList FullData_scalerMap,
    ME_playlist_TFileMAP EmptyDataMap, Pot_MapList EmptyData_scalerMap,
    char *histoName_MC, char *histoName_data, char *pdf_label, char *hist_title,
    char *xaxislabel, char *yaxislabel);
/////===============================================================================================

void Draw2DFULLStatCOMBINED_2dplotSingle(
    ME_playlist_TFileMAP FullMCMap, Pot_MapList FullMC_POTMap,
    ME_playlist_TFileMAP EmptyMCMap, Pot_MapList EmptyMC_POTMap,
    ME_playlist_TFileMAP FullDataMap, Pot_MapList FullData_POTMap,
    ME_playlist_TFileMAP EmptyDataMap, Pot_MapList EmptyData_POTMap,
    char *histoName_MC, char *histoName_data, char *pdf_label, char *hist_title,
    char *xaxislabel, char *yaxislabel);
/////===============================================================================================
double EllipticparaboloidFunction(Double_t *x, Double_t *par);
/////===============================================================================================
void DrawEllipticparaboloidFit(MnvH2D *hist, const char *xaxislabel,
                               const char *yaxislabel, const char *zaxislabel,
                               const char *Title, const char *pdf, TCanvas *can,
                               MnvPlotter *plot, double MinX, double MaxX,
                               double MinY, double MaxY);
/////===============================================================================================
void Draw2D_Panel_CV_SystematicErrFromPointer_new(
    MnvH2D *hist_Data, MnvH2D *hist_MC, char *playlistInfo_char,
    char *HeliumStatus_name_char, MnvPlotter *mnvPlotter, char *pdf1,
    char *hist_title, char *xaxislabel, char *yaxislabel, char *zaxislabel,
    bool DoBinwidthNorm, bool MakeXaxisLOG, double max_x, double max_y,
    double x_projectionTxtsize, double y_projectionTxtsize, double &chisqrt,
    int &ndf);
/////===============================================================================================
std::vector<std::pair<TH2 *, const char *> > getSystHistsAndOpts(
    MnvH2D *data, bool XprojectionTrue, TLegend *&leg, char *pdf = "",
    bool print1Dpanels = false);
////============================================================================================
std::vector<std::pair<TH2 *, const char *> > getSystHistsAndOpts_Model(
    MnvH2D *data, bool XprojectionTrue, TLegend *&leg, char *pdf,
    bool print1Dpanels);
/////===============================================================================================
std::vector<std::pair<TH2 *, const char *> > getSystHistsAndOpts_errorBand(
    MnvH2D *data, MnvH2D *h_mc, bool XprojectionTrue, TLegend *&leg,
    char *pdf = "", bool print1Dpanels = false);
/////===============================================================================================
std::vector<std::pair<TH2 *, const char *> > getSystHistsAndOpts_ErrorGroup(
    std::string ErrorGroup, MnvH2D *data, bool XprojectionTrue, TLegend *&leg,
    char *pdf, bool print1Dpanels = false);
/////===============================================================================================
TH2 *concatenateHists(std::vector<TH1 *> &hists1D, int axis, TH2D *temp);

/////===============================================================================================
void DrawPanel_SystematicErrorPlots_ProjectionY(
    MnvH2D *data_input, std::string variablex, std::string variabley,
    char *title_charint, char *pdf_label, double SetYmax = .4,
    bool setMaxY = true, bool print1dPlots = false);
/////===============================================================================================
void DrawPanel_SystematicErrorPlots_ProjectionY_model(
    MnvH2D *data_input, std::string variablex, std::string variabley,
    char *title_char, char *pdf_label, double SetYmax = .4, bool setMaxY = true,
    bool print1dPlots = false);
/////===============================================================================================
void DrawPanel_SystematicErrorPlots_ProjectionY_E_theta(
    MnvH2D *data_input, std::string variablex, std::string variabley,
    char *title_char, char *pdf_label, double SetYmax = .4, bool setMaxY = true,
    bool print1dPlots = false);
/////===============================================================================================
void DrawPanel_SystematicErrorPlots_ProjectionX(
    MnvH2D *data, std::string variablex, std::string variabley,
    char *title_char, char *pdf_label, double SetYmax = .4, bool setMaxY = true,
    bool print1dPlots = false);
/////===============================================================================================
void DrawPanel_SystematicErrorPlots_ProjectionX_model(
    MnvH2D *data, std::string variablex, std::string variabley,
    char *title_char, char *pdf_label, double SetYmax = .4, bool setMaxY = true,
    bool print1dPlots = false);
/////===============================================================================================
void DrawPanel_SystematicErrorPlots_ProjectionX_E_theta(
    MnvH2D *data, std::string variablex, std::string variabley,
    char *title_char, char *pdf_label, double SetYmax = .4, bool setMaxY = true,
    bool print1dPlots = false);
/////===============================================================================================
void DrawPanel_SystematicErrorPlots_ProjectionY_Groups(
    TCanvas *cE, MnvH2D *data_input, std::string variablex,
    std::string variabley, char *title_char, char *pdf_label,
    double SetYmax = .4, bool setMaxY = true, bool print1dPlots = false,
    bool applyingModel = false);

void DrawPanel_SystematicErrorPlots_ProjectionY_Groups(
    std::string groupName, MnvH2D *data_input, std::string variablex,
    std::string variabley, char *title_char, char *pdf_label,
    double SetYmax = .4, bool setMaxY = true, bool print1dPlots = false,
    bool applyingModel = false);

void DrawPanel_SystematicErrorPlots_ProjectionX_Groups(
    std::string groupName, MnvH2D *data_input, std::string variablex,
    std::string variabley, char *title_char, char *pdf_label,
    double SetYmax = .4, bool setMaxY = true, bool print1dPlots = false,
    bool applyingModel = false);
/////===============================================================================================

void DrawPanel_MC_dataErrorPlots_ProjectionY(MnvH2D *data, MnvH2D *h_MC,
                                             std::string variablex,
                                             std::string variabley,
                                             char *title_char, char *pdf_label,
                                             double Ymaxlimit = .3);
/////===============================================================================================
std::vector<std::pair<TH2 *, const char *> > Make_pannelhis_vector(
    MnvH2D *data, MnvH2D *MC_total, const TObjArray *mcHists,
    std::vector<int> color_vector, TLegend *&leg);

void Draw_inputTranswarp2DHist_fromPointers(
    MnvH2D *h_data, MnvH2D *h_data_true, MnvH2D *h_mc_reco, MnvH2D *h_mc_true,
    bool AreaNorm_todata, char *pdf_label, char *histotitle, char *xaxislabel,
    char *yaxislabel, char *zaxislabel_units, bool DoBinwidthNorm,
    bool MakeXaxisLOG, double Ymax, bool setMaxY, bool doMultipliers,
    std::vector<double> YMultipliers, std::vector<double> XMultipliers);

void PlotDataStackedMC2D_ProjY(
    PlotUtils::MnvH2D *data, PlotUtils::MnvH2D *mc, const TObjArray *stack,
    std::vector<int> fillColors, bool DoBinwidthNorm, char *pdf_label,
    char *histotitle, char *xaxislabel, char *yaxislabel,
    char *zaxislabel_units, double Ymax, bool setMaxY, bool doMultipliers,
    std::vector<double> YMultipliers, bool statPlusSysDATA = true,
    bool statPlusSysMC = true, bool do_bin_width_norm = false,
    bool useHistTitles = false);

void PlotDataStackedMC2D_ProjY(PlotUtils::MnvH2D *data, TObjArray stack,
                               std::vector<int> fillColors, char *pdf_label,
                               char *histotitle, char *xaxislabel,
                               char *yaxislabel, char *zaxislabel_units,
                               double Ymax, bool setMaxY, bool doMultipliers,
                               std::vector<double> YMultipliers,
                               bool do_bin_width_norm, double text_size);

void PlotDataMC_ErrorBand2D_ProjY(
    PlotUtils::MnvH2D *data, PlotUtils::MnvH2D *mc, char *pdf_label,
    char *histotitle, char *xaxislabel, char *yaxislabel,
    char *zaxislabel_units, double Ymax, bool setMaxY, bool doMultipliers,
    std::vector<double> XMultipliers, bool statPlusSysDATA, bool statPlusSysMC,
    bool do_bin_width_norm, bool useHistTitles, double text_size = .03);

void PlotDataMC_ErrorBand2D_ProjY(
    PlotUtils::MnvH2D *data, PlotUtils::MnvH2D *mc,
    PlotUtils::MnvH2D *data_BG_input, PlotUtils::MnvH2D *mc_BG_input,
    char *pdf_label, char *histotitle, char *xaxislabel, char *yaxislabel,
    char *zaxislabel_units, double Ymax, bool setMaxY, bool doMultipliers,
    std::vector<double> XMultipliers, bool statPlusSysDATA, bool statPlusSysMC,
    bool do_bin_width_norm, bool useHistTitles, double text_size);
void Plot2MC_ErrorBand2D_ProjY(
    PlotUtils::MnvH2D *mc1, char *mc1_legendName, PlotUtils::MnvH2D *mc2,
    char *mc2_legendName, char *pdf_label, char *histotitle, char *xaxislabel,
    char *yaxislabel, char *zaxislabel_units, double Ymax, bool setMaxY,
    bool doMultipliers, std::vector<double> XMultipliers, bool statPlusSysDATA,
    bool statPlusSysMC, bool do_bin_width_norm, bool useHistTitles,
    double text_size);

void PlotMC_ErrorBand2D_ProjX(PlotUtils::MnvH2D *mc, char *pdf_label,
                              char *histotitle, char *xaxislabel,
                              char *yaxislabel, char *zaxislabel_units,
                              double Ymax, bool setMaxY, bool doMultipliers,
                              std::vector<double> XMultipliers,
                              bool statPlusSysDATA, bool statPlusSysMC,
                              bool do_bin_width_norm, bool useHistTitles,
                              double text_size);

void PlotDataStackedMC2D_ProjX(
    PlotUtils::MnvH2D *data, PlotUtils::MnvH2D *mc, const TObjArray *stack,
    std::vector<int> fillColors, bool DoBinwidthNorm, char *pdf_label,
    char *histotitle, char *xaxislabel, char *yaxislabel,
    char *zaxislabel_units, double Ymax, bool setMaxY, bool doMultipliers,
    std::vector<double> XMultipliers, bool statPlusSysDATA = true,
    bool statPlusSysMC = true, bool do_bin_width_norm = false,
    bool useHistTitles = false);

void PlotDataStackedMC2D_ProjX(PlotUtils::MnvH2D *data, TObjArray stack,
                               std::vector<int> fillColors, char *pdf_label,
                               char *histotitle, char *xaxislabel,
                               char *yaxislabel, char *zaxislabel_units,
                               double Ymax, bool setMaxY, bool doMultipliers,
                               std::vector<double> XMultipliers,
                               bool do_bin_width_norm, double text_size);

void PlotFractionofEvents2D_ProjY(PlotUtils::MnvH2D *mc, const TObjArray *stack,
                                  std::vector<int> fillColors, char *dataname,
                                  char *dataname_total, char *pdf_label,
                                  char *histotitle, char *xaxislabel,
                                  char *yaxislabel, char *zaxislabel_units);

void PlotDataMC_ErrorBand2D_ProjX(
    PlotUtils::MnvH2D *data, PlotUtils::MnvH2D *mc, char *pdf_label,
    char *histotitle, char *xaxislabel, char *yaxislabel,
    char *zaxislabel_units, double Ymax, bool setMaxY, bool doMultipliers,
    std::vector<double> XMultipliers, bool statPlusSysDATA, bool statPlusSysMC,
    bool do_bin_width_norm, bool useHistTitles, double text_size = .03);

void PlotDataMC_ErrorBand2D_ProjX(
    PlotUtils::MnvH2D *data, PlotUtils::MnvH2D *mc,
    PlotUtils::MnvH2D *data_BG_input, PlotUtils::MnvH2D *mc_BG_input,
    char *pdf_label, char *histotitle, char *xaxislabel, char *yaxislabel,
    char *zaxislabel_units, double Ymax, bool setMaxY, bool doMultipliers,
    std::vector<double> XMultipliers, bool statPlusSysDATA, bool statPlusSysMC,
    bool do_bin_width_norm, bool useHistTitles, double text_size);

void PlotMC_ErrorBand2D_ProjY(PlotUtils::MnvH2D *mc, char *pdf_label,
                              char *histotitle, char *xaxislabel,
                              char *yaxislabel, char *zaxislabel_units,
                              double Ymax, bool setMaxY, bool doMultipliers,
                              std::vector<double> XMultipliers,
                              bool statPlusSysDATA, bool statPlusSysMC,
                              bool do_bin_width_norm, bool useHistTitles,
                              double text_size);

void Plot2MC_ErrorBand2D_ProjX(
    PlotUtils::MnvH2D *mc1, char *mc1_legendName, PlotUtils::MnvH2D *mc2,
    char *mc2_legendName, char *pdf_label, char *histotitle, char *xaxislabel,
    char *yaxislabel, char *zaxislabel_units, double Ymax, bool setMaxY,
    bool doMultipliers, std::vector<double> XMultipliers, bool statPlusSysDATA,
    bool statPlusSysMC, bool do_bin_width_norm, bool useHistTitles,
    double text_size);

void Plot2D_FractionError_ProjX(PlotUtils::MnvH2D *HistInput, char *pdf_label,
                                char *histotitle, char *xaxislabel,
                                char *yaxislabel, double Ymax,
                                double text_size);

void Plot2D_FractionError_ProjX_Group(PlotUtils::MnvH2D *HistInput,
                                      char *pdf_label, char *histotitle,
                                      char *xaxislabel, char *GroupName,
                                      char *yaxislabel, double Ymax,
                                      double text_size,
                                      bool doErrorModelGroups = true);

void Plot2D_FractionError_ProjY(PlotUtils::MnvH2D *HistInput, char *pdf_label,
                                char *histotitle, char *xaxislabel,
                                char *yaxislabel, double Ymax,
                                double text_size);

void Plot2D_FractionError_ProjY_Group(PlotUtils::MnvH2D *HistInput,
                                      char *pdf_label, char *histotitle,
                                      char *xaxislabel, char *GroupName,
                                      char *yaxislabel, double Ymax,
                                      double text_size,
                                      bool doErrorModelGroups = true);

void PlotDataMC_Migration_ProjX(
    PlotUtils::MnvH2D *migration, PlotUtils::MnvH2D *reco,
    PlotUtils::MnvH2D *truth, std::vector<double> ProjectBinning,
    char *pdf_label, char *histotitle, char *xaxislabel, char *yaxislabel,
    char *zaxislabel_units, double Zmax, MnvPlotter *plot, TCanvas *cE,
    int normtype, double txtsize, double markertxtsize, bool doBinN);

void PlotDataMC_Migration_ProjY(
    PlotUtils::MnvH2D *migration, PlotUtils::MnvH2D *reco,
    PlotUtils::MnvH2D *truth, std::vector<double> ProjectBinning,
    char *pdf_label, char *histotitle, char *xaxislabel, char *yaxislabel,
    char *zaxislabel_units, double Zmax, MnvPlotter *mnvPlotter, TCanvas *cE,
    int normtype, double txtsize, double markertxtsize, bool doBinN);

void PlotFractionofEvents2D_ProjX(PlotUtils::MnvH2D *mc, const TObjArray *stack,
                                  std::vector<int> fillColors, char *dataname,
                                  char *dataname_total, char *pdf_label,
                                  char *histotitle, char *xaxislabel,
                                  char *yaxislabel, char *zaxislabel_units);

void Draw2DPlots_Panel(
    ME_playlist_TFileMAP Full_Map, ME_playlist_TFileMAP Full_Data_Map,
    ME_playlist_TFileMAP Empty_Map, ME_playlist_TFileMAP Empty_Data_Map,
    double Full_MC_Full_Data, double Empty_MC_Full_Data,
    double Empty_Data_Full_Data, char *hist_MCName, char *hist_DataName,
    char *xaxis, char *yaxis, char *unitsX, char *unitsY, char *Plot_title,
    std::vector<double> YMultipliers, std::vector<double> XMultipliers,
    bool do_bin_width_norm, bool statPlusSysDATA, bool statPlusSysMC,
    MnvPlotter *mnvPlotter, TCanvas *can, char *pdf, double XprotextSize,
    double YprotextSize);

#endif
