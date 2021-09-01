#ifndef SMEARING_STUDY_FULLSTATS_H
#define SMEARING_STUDY_FULLSTATS_H


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

#include "../includes/Helium2DPlotUtils.h"
#include "../includes/HeliumPlotUtils.h"
#include "../includes/CryoTankUtils.h"
#include "../includes/HeliumDefaults.h"
#include "../includes/HeliumUtils.h"

#include "Common_plots.h"

void Draw_Data_RECO_TRUTH_Hist_Full_Stats(char *histoName_TRUTH_RECO,
                                          char *histoName_MC_RECO,
                                          char *histoName_data,
                                          ME_playlist_TFileMAP FullMCMap,    Pot_MapList FullMC_scalerMap,
                                          ME_playlist_TFileMAP EmptyMCMap,   Pot_MapList EmptyMC_scalerMap,
                                          ME_playlist_TFileMAP FullDataMap,  Pot_MapList FullData_scalerMap,
                                          ME_playlist_TFileMAP EmptyDataMap, Pot_MapList EmptyData_scalerMap,
                                          std::string units, std::string pdf_label, char* hist_title,
                                          char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG, double Ymax
                                        );

void Draw_Data_RECO_TRUTH_Hist_Full_Stats_Combined(char *histoName_TRUTH_RECO,
                                          char *histoName_MC_RECO,
                                          char *histoName_data,
                                          ME_playlist_TFileMAP FullMCMap,    Pot_MapList FullMC_POTMap,
                                          ME_playlist_TFileMAP EmptyMCMap,   Pot_MapList EmptyMC_POTMap,
                                          ME_playlist_TFileMAP FullDataMap,  Pot_MapList FullData_POTMap,
                                          ME_playlist_TFileMAP EmptyDataMap, Pot_MapList EmptyData_POTMap,
                                          std::string units, std::string pdf_label, char* hist_title,
                                          char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG, double Ymax
                                        );
//

void Draw_Data_RECO_TRUTH_withConvolution_Hist_Full_Stats_Combined(char *histoName_TRUTH_RECO,
                                          char *histoName_TRUTH_RECO_Convol,
                                          char *histoName_MC_RECO,
                                          char *histoName_data,
                                          ME_playlist_TFileMAP FullMCMap,    Pot_MapList FullMC_POTMap,
                                          ME_playlist_TFileMAP EmptyMCMap,   Pot_MapList EmptyMC_POTMap,
                                          ME_playlist_TFileMAP FullDataMap,  Pot_MapList FullData_POTMap,
                                          ME_playlist_TFileMAP EmptyDataMap, Pot_MapList EmptyData_POTMap,
                                          std::string units, std::string pdf_label, char* hist_title,
                                          char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG, double Ymax, double ConvolutedBymm
                                        );
//

void Draw_Data_RECO_TRUTH_withConvolution_Hist_Full_Stats(char *histoName_TRUTH_RECO,
                                                          char *histoName_TRUTH_RECO_Convol,
                                                          char *histoName_MC_RECO,
                                                          char *histoName_data,
                                                          ME_playlist_TFileMAP FullMCMap,    Pot_MapList FullMC_scalerMap,
                                                          ME_playlist_TFileMAP EmptyMCMap,   Pot_MapList EmptyMC_scalerMap,
                                                          ME_playlist_TFileMAP FullDataMap,  Pot_MapList FullData_scalerMap,
                                                          ME_playlist_TFileMAP EmptyDataMap, Pot_MapList EmptyData_scalerMap,
                                                          std::string units, std::string pdf_label, char* hist_title,
                                                          char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG, double Ymax, double ConvolutedBymm
                                                        );
//


#endif
