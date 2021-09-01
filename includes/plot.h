#ifndef PLOT_H
#define PLOT_H

#include "TClass.h"
#include "TList.h"
#include "TH1.h"
#include "TH2.h"
#include "TPad.h"
#include "TGraphErrors.h"

#include <iostream>
#include <vector>
#include <math.h>
#include <iostream>
#include "GridCanvas.h"


class GridCanvas;
//======================================================================

// Return a unique string on every call, so we can name root hists
// without it clobbering them
TString uniq();
//======================================================================

// Convert a histogram to a graph so we can draw it without ROOT
// drawing extra lines at the end and other such nonsense

TGraphErrors* histToGraph(TH1* h, double multiplier=1, bool includeZeros=true);
std::vector<double> GetScales(std::vector<std::pair<TH2*, const char*> >histopts, bool pxProj, double plotMax, double fracMax, bool limitRange= false, double rmin=0, double rmax=100);
//======================================================================
TH1* getPadAxisHist(TPad* pad);
//======================================================================
std::vector<TH1*> getPadHists(TPad* pad);
//======================================================================
double getPadMax(TPad* pad);
//======================================================================
void reMax(TPad* pad, double ymin=0, double headroom=1.1);
//======================================================================
void drawBinRange(TH2* h, int axis, int bin, const char* varName, const char* numFormatStr=".2f", bool left=false);
//======================================================================
void drawBinRange(TH2* h, int axis, int bin, const char* varName, double text_size, const char* numFormatStr=".2f", bool left=false );
//=====================================================================================================================
void drawBinRangeSpecial(TH2* h, int axis, int bin, const char* varName, const char* numFormatStr=".2f", bool left=false, bool smallrange=false);
//======================================================================
void drawVarBinRange(TH2* h, int axis, int minbin, int maxbin, const char* varName, const char* numFormatStr=".2f", bool left=false);
//======================================================================
GridCanvas* plotpT1D(std::vector<std::pair<TH2*, const char*> > histAndOpts,
                     double* multipliers=NULL);
//======================================================================
//GridCanvas* plotYAxis1D(std::vector<std::pair<TH2*, const char*> > histAndOpts, std::string  xaxistitle, std::string celltitle,
	//		double* multipliers=NULL);

GridCanvas* plotYAxis1D(std::vector<std::pair<TH2*, const char*> > histAndOpts, std::string xaxistitle, std::string celltitle,
                           double* multipliers=NULL , double label_size =.03);

///////////////For ratios/////////////////////////////////////
//======================================================================
GridCanvas* plotYfrac1D(std::vector<std::pair<TH2*, const char*> > histAndOpts, std::string  xaxistitle, std::string  celltitle,
			double* multipliers=NULL);
//======================================================================
//======================================================================
GridCanvas* plotYAxis1D(std::vector<std::pair<TH2*, const char*> > histAndOpts, std::string  xaxistitle, std::string  celltitle, int ncolumns, int nrows, int xwidth, int ywidth,
			double* multipliers=NULL);
//======================================================================
GridCanvas* plotpT1DAntiNu(std::vector<std::pair<TH2*, const char*> > histAndOpts,
                     double* multipliers=NULL);
//======================================================================
TH1* rebinpz(TH1* h);
//======================================================================
GridCanvas* plotpz1D(std::vector<std::pair<TH2*, const char*> > histAndOpts,
                     double* multipliers=NULL, bool is3D=false);

//======================================================================

GridCanvas* plotfracpz(std::vector<std::pair<TH2*, const char*> > histAndOpts,
		       double* multipliers=NULL, bool doGENIEs=false, bool doPrelimLabel=false, bool smallrange=false);
//======================================================================
GridCanvas* plotfracpt(std::vector<std::pair<TH2*, const char*> > histAndOpts,
		       double* multipliers=NULL, bool doGENIEs=false, bool doPrelimLabel=false, bool smallrange=false);
////////////////////////////For Ratio Plots//////////////////////////////////

//======================================================================
GridCanvas* plotXfrac1D(std::vector<std::pair<TH2*, const char*> > histAndOpts, std::string  xaxistitle, std::string  celltitle,
                     double* multipliers=NULL);
//======================================================================
//GridCanvas* plotXAxis1D(std::vector<std::pair<TH2*, const char*> > histAndOpts, std::string  xaxistitle, std::string  celltitle,
  //                   double* multipliers=NULL);

 GridCanvas* plotXAxis1D(std::vector<std::pair<TH2*, const char*> > histAndOpts, std::string xaxistitle, std::string celltitle,
                               double* multipliers=NULL, double label_size = .026);

//======================================================================
GridCanvas* plotXAxis1D_ReducedXRange(std::vector<std::pair<TH2*, const char*> > histAndOpts, std::string  xaxistitle, std::string  celltitle, double xminval, double xmaxval,
                     double* multipliers=NULL);
//======================================================================
GridCanvas* plotXAxis1D_ReducedXRange(std::vector<std::pair<TH2*, const char*> > histAndOpts, std::string  xaxistitle, std::string  celltitle, int grid_x, int grid_y, double xminval, double xmaxval, double xpix, double ypix,
                     double* multipliers=NULL);
//======================================================================
GridCanvas* plotXAxis1D(std::vector<std::pair<TH2*, const char*> > histAndOpts, std::string  xaxistitle, std::string  celltitle, int ncolumns, int nrows, int xwidth, int ywidth,
                     double* multipliers=NULL);

//======================================================================
GridCanvas* plotXAxis1DRebinPz(std::vector<std::pair<TH2*, const char*> > histAndOpts, std::string  xaxistitle, std::string  celltitle, int ncolumns, int nrows, int xwidth, int ywidth,
                     double* multipliers=NULL);
//======================================================================
GridCanvas* plotXAxis1D_Nue(std::vector<std::pair<TH2*, const char*> > histAndOpts, std::string  xaxistitle, std::string  celltitle,
                     double* multipliers=NULL);

//======================================================================
GridCanvas* plotpz1DAntiNu(std::vector<std::pair<TH2*, const char*> > histAndOpts,
                     double* multipliers=NULL);

//======================================================================
GridCanvas* plotvtx1D(std::vector<std::pair<TH2*, const char*> > histAndOpts,
		      double* multipliers=NULL, TH2* denominator=NULL, bool track2=false);
//======================================================================
GridCanvas* plotvtxrate1D(std::vector<std::pair<TH2*, const char*> > histAndOpts,
			  double* multipliers=NULL,bool track2=false, bool binbybin =false);




#endif
