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
#include <algorithm>
#include "GridCanvas.h"


class GridCanvas;
//class TLatex;
//======================================================================

// Return a unique string on every call, so we can name root hists
// without it clobbering them
TString uniq();
//======================================================================

// Convert a histogram to a graph so we can draw it without ROOT
// drawing extra lines at the end and other such nonsense
TLegend* getPadLegend(TPad* pad);
//======================================================================
TGraphErrors* histToGraph(TH1* h, double multiplier=1, bool includeZeros=true, TString opts="");
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
void drawBinRange(TH2* h, int axis, int bin, const char* varName,const char* numFormatStr=".2f", int mode=1, int gridx = 0, int gridy = 0);
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
                           double* multipliers=NULL , double label_size =.03, bool DoBinwidthNorm = false);

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
TH1* rebinpt(TH1* h);
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
//======================================================================
GridCanvas* plotXAxis1D(std::vector<std::pair<TH2*, const char*> > histAndOpts, std::string xaxistitle, std::string celltitle,
                     double* multipliers=NULL, bool DoBinwidthNorm= false); // 4
//======================================================================

GridCanvas* plotXAxis1D(std::vector<std::pair<TH2*, const char*> > histAndOpts, std::string xaxistitle, std::string celltitle,double label_size /* = .026*/,
  double* multipliers=NULL, bool DoBinwidthNorm=false); // 5
//======================================================================

GridCanvas* plotXAxis1D(std::vector<std::pair<TH2*, const char*> > histAndOpts, std::string  xaxistitle, std::string  celltitle, int ncolumns, int nrows, int xwidth, int ywidth,
                       double* multipliers=NULL); // 8
//======================================================================
GridCanvas* plotXAxis1D(std::vector<std::pair<TH2*, const char*> > histAndOpts, std::string xaxistitle, std::string celltitle, int grid_x, int grid_y, std::vector<int> panels,
			double* multipliers=NULL); // 7
//======================================================================
//======================================================================


GridCanvas* plotXAxis1D_MoveLabels(std::vector<std::pair<TH2*, const char*> > histAndOpts, std::string xaxistitle, std::string celltitle,
			double* multipliers=NULL, bool moveLabels=false);
//======================================================================
GridCanvas* plotXAxis1D_ReducedXRange(std::vector<std::pair<TH2*, const char*> > histAndOpts, std::string  xaxistitle, std::string  celltitle, double xminval, double xmaxval,
                     double* multipliers=NULL);
//======================================================================
GridCanvas* plotXAxis1D_ReducedXRange(std::vector<std::pair<TH2*, const char*> > histAndOpts, std::string  xaxistitle, std::string  celltitle, int grid_x, int grid_y, double xminval, double xmaxval, double xpix, double ypix,
                     double* multipliers=NULL);
//======================================================================
GridCanvas* plotXAxis1D_IgnoreYBins(std::vector<std::pair<TH2*, const char*> > histAndOpts, std::string xaxistitle, std::string celltitle, int lowYbin, int upYbin,
				    double* multipliers=NULL);
//======================================================================
GridCanvas* plotXAxis1D_IgnoreYBins_ReduceXRange(std::vector<std::pair<TH2*, const char*> > histAndOpts, std::string xaxistitle, std::string celltitle, int lowYbin, int upYbin, double lowX, double highX,
				    double* multipliers=NULL);
//======================================================================
GridCanvas* plotXAxis1DRebinPz(std::vector<std::pair<TH2*, const char*> > histAndOpts, std::string  xaxistitle, std::string  celltitle, int ncolumns, int nrows, int xwidth, int ywidth,
                     double* multipliers=NULL);
//======================================================================
GridCanvas* plotXAxis1D_Nue(std::vector<std::pair<TH2*, const char*> > histAndOpts, std::string  xaxistitle, std::string  celltitle,
                     double* multipliers=NULL);
//======================================================================
GridCanvas* plotYAxis1D_ReducedXRange(std::vector<std::pair<TH2*, const char*> > histAndOpts, std::string xaxistitle, std::string celltitle, int grid_x, int grid_y, double xminval, double xmaxval, double xpix, double ypix,
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
//======================================================================
std::vector<double> GetScales(std::vector<std::pair<TH2*, const char*> >histopts, bool pxProj, double plotMax, double fracMax, bool limitRange = false, double rmin=0, double rmax=100);
//======================================================================
std::vector<double> GetScales(std::vector <std::pair<std::vector<TH1*> ,const char*> > histopts,double yaxismax,double fraction);
//======================================================================
std::vector<double> GetScalesRatio(std::vector<std::pair<TH2*, const char*> >histopts, bool pxProj, double plotMax);
//======================================================================
std::vector<std::vector<double>> GetKinValue(int binsx,int binsy,TH1 *rebinnedhisto,TH2 *templatehist);
//======================================================================
std::vector <TH1*> PrepareHist(TH2* hisy_temp, TH1* dataMnv, const char *prefix,double scale=1.0,bool doRatio=false);
//======================================================================
GridCanvas* plotNonGrid1D(std::vector<std::pair<std::vector<TH1*>, const char*> > histAndOpts, std::string xaxistitle, std::string celltitle, TH2* mytemplate,
			  double* multipliers=NULL);
//======================================================================
std::vector <TH1*> MakeTH1Ds(std::vector<std::vector<double>> kinVs, TH1 *rebinnedhisto,TH2 *templatehist, const char *prefix,double scale=1.0,bool doRatio=false);
//======================================================================
TH1* makeTH1D(int pt_bin,double pt_width, std::vector<double> boundaries,TH1* rebinnedhisto,
  int startindex,const char *prefix,double scale=1.0,bool doRatio=false);
  std::vector<std::string> GetStringBinRanges(TH2* h, bool ProjectionX , std::string VarName);


#endif
