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

#include "../includes/HeliumPlotUtils.h"
#include "../includes/CryoTankUtils.h"
#include "../includes/HeliumDefaults.h"
#include "../includes/HeliumUtils.h"

#include "../Make_Plots/Common_plots.h"

std::vector<ME_helium_Playlists> GetPlayListVector();
std::vector<MuonVar> GetMUONVaribles_Total();
void PrintCrossSection_MapName(CrossSection_name_Map Map , char* outputLabel);
CrossSection_MnvH1D_Map Generate_CrossSection_Hist_Map(TFile& file, CrossSection_name_Map Map);
CrossSection_name_Map Generate_CrossSection_histsNames(MuonVar MuonVar_type, std::string playlist, bool isFUll);
Migration_MnvH2D_Map Generate_CrossSection_Mig_Hist_Map(TFile& file, std::vector<MuonVar> muon_vector);
void MakeCrossSectionPlots(CrossSection_MnvH1D_Map CrossSection_map,std::string cross_section_units, std::string pdf,bool MakeXaxisLOG,bool doBinwidth ,MuonVar MuonVar, char *Playlist_name);



#endif
