//Author: Christian Nguyen
// Helium Cross Section Extractor header
// Started to Build: May 17 2020
//email: christian2nguyen@ufl.edu

#ifndef EXTRACTHELIUMCROSSSECTIONHISTS_H
#define EXTRACTHELIUMCROSSSECTIONHISTS_H


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
#include "PlotUtils/TargetUtils.h"

#include <set>
#include <iterator>
#include <sstream>
#include <string>
#include <time.h>

#include "../includes/HeliumPlotUtils.h"
#include "../includes/Helium2DPlotUtils.h"
#include "../includes/CryoTankUtils.h"
#include "../includes/HeliumDefaults.h"
#include "../includes/HeliumUtils.h"
#include "../includes/Helium2DUtils.h"
#include "../eventselection/EventCounting.h"
#include "../includes/CrossSection_Normalization.h"









// END OF HEADER
#endif
