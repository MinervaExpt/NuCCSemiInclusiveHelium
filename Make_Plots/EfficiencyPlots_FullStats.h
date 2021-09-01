#ifndef EFFICIENCYPLOTS_FULLSTATS_H
#define EFFICIENCYPLOTS_FULLSTATS_H


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

#include <set>
#include <iterator>
#include <sstream>
#include <string>
#include <time.h>

#include "../includes/HeliumPlotUtils.h"
#include "../includes/CryoTankUtils.h"
#include "../includes/HeliumDefaults.h"
#include "../includes/HeliumUtils.h"

#include "Common_plots.h"



std::vector<CryoVertex> GetCryoVertexVaribles();

std::vector<ME_helium_Playlists> GetPlayListVector();
void Kin(bool &cutsOn, bool &my_norm, bool &my_debug, const char *userDir);

void Draw_Efficiency_2ndTrk(std::vector <PlayList_INFO> Playlist, ME_helium_Playlists Playlist_toscaleto , const char *histoName,
  int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf , SecondTrkVar playlist_name );

void Draw_Efficiency_2ndTrk_FULL_EMPTY(PlayList_INFO FULL_playlist,PlayList_INFO EMPTY_playlist , const char *histoName,
  int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf , SecondTrkVar playlist_name );

  void Draw_Efficiency_MUON_FULL_EMPTY(PlayList_INFO FULL_playlist,PlayList_INFO EMPTY_playlist , const char *histoName,
    int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf , MuonVar Muon_Var );

  void Draw_Efficiency_Muon_FULL_EMPTY_Fullstats(ME_playlist_TFileMAP FullMCMap, ME_playlist_TFileMAP Full_TRUTHDEM_MCMap,
                                                   Pot_MapList FullMC_scalerMap, ME_playlist_TFileMAP EmptyMCMap,
                                                   ME_playlist_TFileMAP Empty_TRUTHDEM_MCMap, Pot_MapList EmptyMC_scalerMap,
                                                   const char *histoName, int logScale, const char* title,
                                                   TCanvas *can, const char *pdf , MuonVar playlist_name , bool OnlyEffplot, double yMax );

void Draw_Efficiency_Muon_FULL_EMPTY_Fullstats_Combined(ME_playlist_TFileMAP FullMCMap, ME_playlist_TFileMAP Full_TRUTHDEM_MCMap,
                                               Pot_MapList FullMC_scalerMap, ME_playlist_TFileMAP EmptyMCMap,
                                               ME_playlist_TFileMAP Empty_TRUTHDEM_MCMap, Pot_MapList EmptyMC_scalerMap,
                                               const char *histoName, int logScale, const char* title,
                                               TCanvas *can, const char *pdf , MuonVar playlist_name , bool OnlyEffplot, double yMax );

void Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats(ME_playlist_TFileMAP FullMCMap, ME_playlist_TFileMAP Full_TRUTHDEM_MCMap,
                                                    Pot_MapList FullMC_scalerMap, ME_playlist_TFileMAP EmptyMCMap,
                                                    ME_playlist_TFileMAP Empty_TRUTHDEM_MCMap, Pot_MapList EmptyMC_scalerMap,
                                                    const char *histoName, const char *Xaxis_title, const char *Yaxis_title,
                                                    int logScale, const char* title_type_char, const char* title, MnvPlotter *mnvPlotter, TCanvas *can, const char *pdf, bool OnlyEffplot);

void Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_Combined(ME_playlist_TFileMAP FullMCMap, ME_playlist_TFileMAP Full_TRUTHDEM_MCMap,
                                                    Pot_MapList FullMC_POTMap, ME_playlist_TFileMAP EmptyMCMap,
                                                    ME_playlist_TFileMAP Empty_TRUTHDEM_MCMap, Pot_MapList EmptyMC_POTMap,
                                                    const char *histoName, const char *Xaxis_title, const char *Yaxis_title,
                                                    int logScale, const char* title_type_char, const char* title, MnvPlotter *mnvPlotter, TCanvas *can, const char *pdf, bool OnlyEffplot);


void Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH_FullStats_COMBINED( ME_playlist_TFileMAP FullMCMap, ME_playlist_TFileMAP Full_TRUTHDEM_MCMap,
                                                            Pot_MapList FullMC_scalerMap, ME_playlist_TFileMAP EmptyMCMap,
                                                             ME_playlist_TFileMAP Empty_TRUTHDEM_MCMap, Pot_MapList EmptyMC_scalerMap,
       const char *histoName, bool logScale, const char* title, TCanvas *can, const char *pdf , SecondTrkVar playlist_name, bool OnlyEffplot , double ymax );


 void Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH_FullStats( ME_playlist_TFileMAP FullMCMap, ME_playlist_TFileMAP Full_TRUTHDEM_MCMap,
                                                               Pot_MapList FullMC_scalerMap, ME_playlist_TFileMAP EmptyMCMap,
                                                                ME_playlist_TFileMAP Empty_TRUTHDEM_MCMap, Pot_MapList EmptyMC_scalerMap,
          const char *histoName, bool logScale, const char* title,  TCanvas *can, const char *pdf , SecondTrkVar playlist_name, bool OnlyEffplot , double ymax );

void Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_Combined_PanelPlots(ME_playlist_TFileMAP FullMCMap, ME_playlist_TFileMAP Full_TRUTHDEM_MCMap,
                                                              Pot_MapList FullMC_scalerMap, ME_playlist_TFileMAP EmptyMCMap,
                                                              ME_playlist_TFileMAP Empty_TRUTHDEM_MCMap, Pot_MapList EmptyMC_scalerMap,
                                                              const char *histoName, const char *Xaxis_title, const char *Yaxis_title, const char *Zaxis_title,
                                                              bool logScale, bool doBinwidth, const char* title_type_char, const char* title ,
                                                              MnvPlotter *mnvPlotter, TCanvas *can, char *pdf, bool OnlyEffplot , double max_x, double max_y  );
//
void Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_Combined_PanelPlots(ME_playlist_TFileMAP FullMCMap, ME_playlist_TFileMAP Full_TRUTHDEM_MCMap,
                                                                       Pot_MapList FullMC_POTMap, ME_playlist_TFileMAP EmptyMCMap,
                                                                       ME_playlist_TFileMAP Empty_TRUTHDEM_MCMap, Pot_MapList EmptyMC_POTMap,
                                                                       const char *histoName, const char *Xaxis_title, const char *Yaxis_title,const char * Zaxis_title,
                                                                       bool logScale, bool doBinwidth, const char* title_type_char, const char* title ,MnvPlotter *mnvPlotter,
                                                                       TCanvas *can,  char *pdf, bool OnlyEffplot, double max_x, double max_y , double txt_sizeY , double txt_sizeX );

void Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_PANELPLOTS(ME_playlist_TFileMAP FullMCMap, ME_playlist_TFileMAP Full_TRUTHDEM_MCMap,
                                                              Pot_MapList FullMC_scalerMap, ME_playlist_TFileMAP EmptyMCMap,
                                                              ME_playlist_TFileMAP Empty_TRUTHDEM_MCMap, Pot_MapList EmptyMC_scalerMap,
                                                              const char *histoName, const char *Xaxis_title, const char *Yaxis_title, const char *Zaxis_title,
                                                              bool logScale, bool doBinwidth, const char* title_type_char, const char* title ,
                                                              MnvPlotter *mnvPlotter, TCanvas *can, char *pdf, bool OnlyEffplot , double max_x, double max_y  );
//

void Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_PANELPLOTS(ME_playlist_TFileMAP FullMCMap, ME_playlist_TFileMAP Full_TRUTHDEM_MCMap,
                                                              Pot_MapList FullMC_scalerMap, ME_playlist_TFileMAP EmptyMCMap,
                                                              ME_playlist_TFileMAP Empty_TRUTHDEM_MCMap, Pot_MapList EmptyMC_scalerMap,
                                                              const char *histoName, const char *Xaxis_title, const char *Yaxis_title, const char *Zaxis_title,
                                                              bool logScale, bool doBinwidth, const char* title_type_char, const char* title ,
                                                              MnvPlotter *mnvPlotter, TCanvas *can, char *pdf, bool OnlyEffplot , double max_x, double max_y, double txt_sizeY , double txt_sizeX  );



//void DrawStack_Material(bool my_debug, TFile *inputFile,  CryoVertex Vertex_type , ME_helium_Playlists PlayList , int doShape,
///	int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf);
///void DrawStack_Interaction(bool my_debug, TFile *inputFile,  CryoVertex Vertex_type , ME_helium_Playlists PlayList , int doShape,
//  int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf);
///void DrawStack_Particle(bool my_debug, TFile *inputFile,  CryoVertex Vertex_type , ME_helium_Playlists PlayList , int doShape,
  //int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf);
  /*void DrawStack(const int intTarPart,const char *intTarPart_name, bool my_debug, TFile *inputFile,  CryoVertex Vertex_type , ME_helium_Playlists PlayList , int doShape,
    int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf);*/

#endif
