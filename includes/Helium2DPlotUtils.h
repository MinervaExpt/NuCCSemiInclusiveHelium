#ifndef HELIUM2DPLOTUTILS_H
#define HELIUM2DPLOTUTILS_H

#include "GridCanvas.h"

//#include "TCanvas.h"
#include "PlotUtils/MnvVertErrorBand.h"
#include "PlotUtils/MnvPlotter.h"
#include "PlotUtils/HistogramUtils.h"
#include "PlotUtils/MnvH1D.h"
#include "HeliumCuts.h"
#include <iostream>
#include "HeliumUtils.h"
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

//const Particle_color_map Particle_COLORMAP;


//const Material_color_map Material_COLORMAP;
//const Interaction_color_map Interaction_COLORMAP;

std::vector<double> GetScales_2d(std::vector<std::pair<TH2*, const char*> >histopts, bool pzProj);
std::vector<double> Normlized_to_lowest_Mulitplers_2d(std::vector <double> multiply_vector);
std::vector<double> GetScales_2d(std::vector<std::pair<TH2*, const char*> >histopts, bool pzProj, bool donormalized);

std::vector<double> Normlized_to_lowest_Mulitplers(std::vector <double> multiply_vector);
std::vector<std::pair<TH2*, const char*> > Make_pannelhis_vector(MnvH2D* data,
   const TObjArray *mcHists, StackType STACKTYPE, TLegend* leg, int Plottype=0);


void Draw2DCVAndError_FromTFile(TFile *inputFile_MCFULL, TFile *inputFile_MCEMPTY,  char *histoName_MC ,TFile *inputFile_DATAFULL,TFile *inputFile_DATAEMPTY,
  char *histoName_Data, Pot_MapStatusList POT_MC, Pot_MapStatusList POT_DATA,bool TrueifFullelseEmpty, char *histotitle, std::string xaxislabel,
   std::string yaxislabel,std::string yaxislabel_units, std::string pdf_label, bool DoBinwidthNorm, bool doSmallerrorgrounps, int Print_Error ,bool Debug);

void DrawSTACKfromHistFilio_FromTFile2D(TFile *inputFile_MCFULL, TFile *inputFile_MCEMPTY,  char *histoName_MC ,  TFile *inputFile_DATAFULL,
  TFile *inputFile_DATAEMPTY, char *histoName_Data, Pot_MapStatusList POT_MC, Pot_MapStatusList POT_DATA, bool TrueifFullelseEmpty, char *histotitle,
  std::string xaxislabel, std::string yaxislabel, const char* yaxisUNITS,std::string pdf_label, bool DoBinwidthNorm, bool doSmallerrorgrounps,  StackType STACKTYPE, bool Debug );

void Draw2D_Migration_FromTFile(TFile *inputFile_MCFULL, TFile *inputFile_MCEMPTY,  char *histoName_MC_Mig,char *histoName_MC_RECO, char *histoName_MC_TRUTH,
  Pot_MapStatusList POT_MC, char *histotitle,char *Fullplaylist_name, char *Emptyplaylist_name, std::string xaxislabel, std::string yaxislabel,
  std::string yaxislabel_units, std::string pdf_label, bool DoBinwidthNorm ,bool Debug);

   void Draw2DFULLStat_CV_SystematicErr(ME_playlist_TFileMAP FullMCMap,     Pot_MapList FullMC_scalerMap,
                                       ME_playlist_TFileMAP EmptyMCMap,   Pot_MapList EmptyMC_scalerMap,
                                       ME_playlist_TFileMAP FullDataMap,  Pot_MapList FullData_scalerMap,
                                       ME_playlist_TFileMAP EmptyDataMap, Pot_MapList EmptyData_scalerMap,
      char *histoName_MC ,char *histoName_data, char* pdf_label, char* hist_title,
      char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG,
       double max_x, double max_y, double x_projectionTxtsize, double y_projectionTxtsize );


   void Draw2DFULLStatCOMBINED_CV_SystematicErr(ME_playlist_TFileMAP FullMCMap, Pot_MapList FullMC_POTMap,
                                       ME_playlist_TFileMAP EmptyMCMap,       Pot_MapList EmptyMC_POTMap,
                                       ME_playlist_TFileMAP FullDataMap,     Pot_MapList FullData_POTMap,
                                       ME_playlist_TFileMAP EmptyDataMap,    Pot_MapList EmptyData_POTMap,
      char *histoName_MC ,char *histoName_data, char *pdf_label, char* hist_title,
      char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG,
      double max_x, double max_y, double x_projectionTxtsize, double y_projectionTxtsize
    );


    void Draw2DFULLStat_2dplotSingle(ME_playlist_TFileMAP FullMCMap,     Pot_MapList FullMC_scalerMap,
                                        ME_playlist_TFileMAP EmptyMCMap,   Pot_MapList EmptyMC_scalerMap,
                                        ME_playlist_TFileMAP FullDataMap,  Pot_MapList FullData_scalerMap,
                                        ME_playlist_TFileMAP EmptyDataMap, Pot_MapList EmptyData_scalerMap,
       char *histoName_MC ,char *histoName_data, char* pdf_label, char* hist_title, char *xaxislabel, char* yaxislabel);


       void Draw2DFULLStatCOMBINED_2dplotSingle(ME_playlist_TFileMAP FullMCMap, Pot_MapList FullMC_POTMap,
                                           ME_playlist_TFileMAP EmptyMCMap,       Pot_MapList EmptyMC_POTMap,
                                           ME_playlist_TFileMAP FullDataMap,     Pot_MapList FullData_POTMap,
                                           ME_playlist_TFileMAP EmptyDataMap,    Pot_MapList EmptyData_POTMap,
          char *histoName_MC ,char *histoName_data, char* pdf_label, char* hist_title, char *xaxislabel, char* yaxislabel);


#endif
