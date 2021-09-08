#ifndef NONMUONKINEMATICS2DPLOTS_H
#define NONMUONKINEMATICS2DPLOTS_H


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
#include "PlotUtils/HistWrapper.h"
#include "PlotUtils/HistFolio.h"
#include "PlotUtils/MnvColors.h"
#include "PlotUtils/NamedCategory.h"


#include <set>
#include <iterator>
#include <sstream>
#include <string>
#include <time.h>

#include "../includes/HeliumUtils.h"
#include "../includes/Helium2DUtils.h"
#include "../includes/Helium2DPlotUtils.h"
#include "../includes/HeliumPlotUtils.h"
#include "../includes/CryoTankUtils.h"
#include "../includes/HeliumDefaults.h"
#include "../includes/HeliumUtils.h"

#include "Common_plots.h"


std::vector<CryoVertex> GetCryoVertexVaribles();
std::vector<SecondTrkVar> GetPlayListSecondTrkVector();
std::vector<ME_helium_Playlists> GetPlayListVector();
void Kin(bool &cutsOn, bool &my_norm, bool &my_debug, const char *userDir);
//void DrawStack_Material(bool my_debug, TFile *inputFile,  CryoVertex Vertex_type , ME_helium_Playlists PlayList , int doShape,
///	int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf);
///void DrawStack_Interaction(bool my_debug, TFile *inputFile,  CryoVertex Vertex_type , ME_helium_Playlists PlayList , int doShape,
//  int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf);
///void DrawStack_Particle(bool my_debug, TFile *inputFile,  CryoVertex Vertex_type , ME_helium_Playlists PlayList , int doShape,
  //int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf);
  /*void DrawStack(const int intTarPart,const char *intTarPart_name, bool my_debug, TFile *inputFile,  CryoVertex Vertex_type , ME_helium_Playlists PlayList , int doShape,
    int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf);*/

#endif
