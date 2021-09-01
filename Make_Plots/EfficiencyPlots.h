#ifndef EFFICIENCYPLOTS_H
#define EFFICIENCYPLOTS_H


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
#include <iomanip>


#include "../includes/HeliumPlotUtils.h"
#include "../includes/CryoTankUtils.h"
#include "../includes/HeliumDefaults.h"
#include "../includes/HeliumUtils.h"


#include "Common_plots.h"
#include <cassert>


std::vector<CryoVertex> GetCryoVertexVaribles();

std::vector<ME_helium_Playlists> GetPlayListVector();
void Kin(bool &cutsOn, bool &my_norm, bool &my_debug, const char *userDir);

void Draw_Efficiency_2ndTrk(std::vector <PlayList_INFO> Playlist, ME_helium_Playlists Playlist_toscaleto , const char *histoName,
  int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf , SecondTrkVar playlist_name );

void Draw_Efficiency_2ndTrk_FULL_EMPTY(PlayList_INFO FULL_playlist,PlayList_INFO EMPTY_playlist , const char *histoName,
  int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf , SecondTrkVar playlist_name );

  void Draw_Efficiency_MUON_FULL_EMPTY(PlayList_INFO FULL_playlist,PlayList_INFO EMPTY_playlist , const char *histoName,
    int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf , MuonVar Muon_Var );




#endif
