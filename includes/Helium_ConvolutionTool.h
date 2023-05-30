#ifndef HELIUM_CONVOLUTIONTOOL_H
#define HELIUM_CONVOLUTIONTOOL_H

#include <iomanip>
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

#include "TMinuit.h"
#include "TFitter.h"
#include "TFractionFitter.h"

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

#include "HeliumPlotUtils.h"
#include "CryoTankUtils.h"
#include "HeliumDefaults.h"
#include "HeliumUtils.h"
#include "Helium2DPlotUtils.h"

namespace VertexShiftValues {
static const double Shift_X = 4.0; //-24.0;  // // 5.0;
static const double Shift_Y = -4.0;// -32.0; //  // 50
static const double Shift_Z = -6.0; //-12.0;  //

}
namespace Al_wgts {
// Newest Wgts
static const double upstream = 2.33;
static const double barrel = 2.17;
static const double downstream = 1.70;
static const double concave = 0.01;

}

namespace Convolution_Vertex_shift_Values {

static const double  Full_vertex_X_mean= -12.0 ;
static const double  Full_vertex_X_sigma= 55.0 ;

static const double Empty_vertex_X_mean=  -12.0;
static const double Empty_vertex_X_sigma= 47.0;

static const double  Full_vertex_Y_mean= 44.0 ;
static const double  Full_vertex_Y_sigma= 58.0 ;

static const double  Empty_vertex_Y_mean=  48.0;
static const double  Empty_vertex_Y_sigma= 58.0;


static const double   Full_vertex_Z_mean=  6.0 ;
static const double   Full_vertex_Z_sigma= 0.0 ;
static const double  Empty_vertex_Z_mean=  4.0;
static const double  Empty_vertex_Z_sigma= 0.0;
///////////////////////////////////////////////////

static const double Empty_vertex_X_beforeShift_mean=  -12.0;
static const double Empty_vertex_X_beforeShift_sigma= 47.0;

static const double  Empty_vertex_Y_beforeShift_mean=  48.0;
static const double  Empty_vertex_Y_beforeShift_sigma= 58.0;

static const double  Empty_vertex_Z_beforeShift_mean=  4.0;
static const double  Empty_vertex_Z_beforeShift_sigma= 4.0;

static const double Full_vertex_X_beforeShift_mean=  -12.0;
static const double Full_vertex_X_beforeShift_sigma= 55.0;

static const double  Full_vertex_Y_beforeShift_mean=  44.0;
static const double  Full_vertex_Y_beforeShift_sigma= 58.0;

static const double  Full_vertex_Z_beforeShift_mean=  4.0;
static const double  Full_vertex_Z_beforeShift_sigma= 4.0;
}

void Fill_Convolution (ME_helium_Playlists playlist_name, double &X_mean,
		       double &X_sigma, double &Y_mean, double &Y_sigma,
		       double &Z_mean, double &Z_sigma);

void Fill_Convolution_BeforeShift (ME_helium_Playlists playlist_name,
				   double &X_mean, double &X_sigma,
				   double &Y_mean, double &Y_sigma,
				   double &Z_mean, double &Z_sigma);




namespace Convolution_shift_Values {

////////////////////////////
// All units are in mm /////
////////////////////////////,
static const double vertex_Z_totalRegion_RECO_mean        =    0.0;
static const double vertex_Z_totalRegion_RECO_stddev      =  105.0;
static const double vertex_Z_totalRegion_DATA_mean        =  125.0;
static const double vertex_Z_totalRegion_DATA_stddev      =  110.0;
static const double vertex_Z_totalRegion_DATA_2_mean      =  125.0;
static const double vertex_Z_totalRegion_DATA_2_stddev    =  105.0;


static const double vertex_Z_RCut_totalRegion_RECO_mean        =    0.0;
static const double vertex_Z_RCut_totalRegion_RECO_stddev      =  105.0;
static const double vertex_Z_RCut_totalRegion_DATA_mean        =  125.0;
static const double vertex_Z_RCut_totalRegion_DATA_stddev      =  110.0;
static const double vertex_Z_RCut_totalRegion_DATA_2_mean      =  125.0;
static const double vertex_Z_RCut_totalRegion_DATA_2_stddev    =  105.0;

static const double vertex_R_totalRegion_RECO_mean        =   0.0;
static const double vertex_R_totalRegion_RECO_stddev      = 105.0;
static const double vertex_R_totalRegion_DATA_mean        = 125.0;
static const double vertex_R_totalRegion_DATA_stddev      = 110.0;
static const double vertex_R_totalRegion_DATA_2_mean      = 125.0;
static const double vertex_R_totalRegion_DATA_2_stddev    = 105.0;

static const double vertex_RR_totalRegion_RECO_mean        =   0.0;
static const double vertex_RR_totalRegion_RECO_stddev      = 400.0;
static const double vertex_RR_totalRegion_DATA_mean        =   0.0;
static const double vertex_RR_totalRegion_DATA_stddev      = 4900.0;
static const double vertex_RR_totalRegion_DATA_2_mean      =   0.0;
static const double vertex_RR_totalRegion_DATA_2_stddev    = 4900.0;

static const double distancetowall_totalRegion_RECO_mean     =  0.0;
static const double distancetowall_totalRegion_RECO_stddev   = 52.5;
static const double distancetowall_totalRegion_DATA_mean     = 40.0;
static const double distancetowall_totalRegion_DATA_stddev   = 45.0;
static const double distancetowall_totalRegion_DATA_2_mean   =  0.0;
static const double distancetowall_totalRegion_DATA_2_stddev = 35.0;

///////////////////////////////
static const double vertex_Z_upstream_RECO_mean        =    0.0;
static const double vertex_Z_upstream_RECO_stddev      =  105.0;
static const double vertex_Z_upstream_DATA_mean        =  125.0;
static const double vertex_Z_upstream_DATA_stddev      =  110.0;
static const double vertex_Z_upstream_DATA_2_mean      =  125.0;
static const double vertex_Z_upstream_DATA_2_stddev    =  105.0;

static const double vertex_Z_RCut_upstream_RECO_mean        =    0.0;
static const double vertex_Z_RCut_upstream_RECO_stddev      =  105.0;
static const double vertex_Z_RCut_upstream_DATA_mean        =  125.0;
static const double vertex_Z_RCut_upstream_DATA_stddev      =  110.0;
static const double vertex_Z_RCut_upstream_DATA_2_mean      =  125.0;
static const double vertex_Z_RCut_upstream_DATA_2_stddev    =  105.0;

static const double Distance_to_upstreamCap_RECO_mean        =    0.0;
static const double Distance_to_upstreamCap_RECO_stddev      =  105.0;
static const double Distance_to_upstreamCap_DATA_mean        =  125.0;
static const double Distance_to_upstreamCap_DATA_stddev      =  110.0;
static const double Distance_to_upstreamCap_DATA_2_mean      =  125.0;
static const double Distance_to_upstreamCap_DATA_2_stddev    =  105.0;

static const double Distance_to_downstreamCap_RECO_mean      =    0.0;
static const double Distance_to_downstreamCap_RECO_stddev    =  105.0;
static const double Distance_to_downstreamCap_DATA_mean      =  125.0;
static const double Distance_to_downstreamCap_DATA_stddev    =  110.0;
static const double Distance_to_downstreamCap_DATA_2_mean    =  125.0;
static const double Distance_to_downstreamCap_DATA_2_stddev  =  105.0;


static const double vertex_R_upstream_RECO_mean        =   0.0;
static const double vertex_R_upstream_RECO_stddev      = 105.0;
static const double vertex_R_upstream_DATA_mean        = 125.0;
static const double vertex_R_upstream_DATA_stddev      = 110.0;
static const double vertex_R_upstream_DATA_2_mean      = 125.0;
static const double vertex_R_upstream_DATA_2_stddev    = 105.0;

static const double vertex_RR_upstream_RECO_mean        =    0.0;
static const double vertex_RR_upstream_RECO_stddev      =  400.0;
static const double vertex_RR_upstream_DATA_mean        =    0.0;
static const double vertex_RR_upstream_DATA_stddev      = 4900.0;
static const double vertex_RR_upstream_DATA_2_mean      =    0.0;
static const double vertex_RR_upstream_DATA_2_stddev    = 4900.0;

static const double distancetowall_upstream_RECO_mean        =  0.0;
static const double distancetowall_upstream_RECO_stddev      = 52.5;
static const double distancetowall_upstream_DATA_mean        = 40.0;
static const double distancetowall_upstream_DATA_stddev      = 45.0;
static const double distancetowall_upstream_DATA_2_mean      =  0.0;
static const double distancetowall_upstream_DATA_2_stddev    = 35.0;
////

static const double vertex_Z_barrel_RECO_mean         =    0.0;
static const double vertex_Z_barrel_RECO_stddev       =  105.0;
static const double vertex_Z_barrel_DATA_mean         =  125.0;
static const double vertex_Z_barrel_DATA_stddev       =  110.0;
static const double vertex_Z_barrel_DATA_2_mean       =  125.0;
static const double vertex_Z_barrel_DATA_2_stddev     =  105.0;

static const double vertex_Z_RCut_barrel_RECO_mean         =    0.0;
static const double vertex_Z_RCut_barrel_RECO_stddev       =  105.0;
static const double vertex_Z_RCut_barrel_DATA_mean         =  125.0;
static const double vertex_Z_RCut_barrel_DATA_stddev       =  110.0;
static const double vertex_Z_RCut_barrel_DATA_2_mean       =  125.0;
static const double vertex_Z_RCut_barrel_DATA_2_stddev     =  105.0;

static const double vertex_R_barrel_RECO_mean           =   0.0;
static const double vertex_R_barrel_RECO_stddev         = 105.0;
static const double vertex_R_barrel_DATA_mean           = 125.0;
static const double vertex_R_barrel_DATA_stddev         = 110.0;
static const double vertex_R_barrel_DATA_2_mean         = 125.0;
static const double vertex_R_barrel_DATA_2_stddev       = 105.0;

static const double vertex_RR_barrel_RECO_mean        =    0.0;
static const double vertex_RR_barrel_RECO_stddev      =  400.0;
static const double vertex_RR_barrel_DATA_mean        =    0.0;
static const double vertex_RR_barrel_DATA_stddev      = 4900.0;
static const double vertex_RR_barrel_DATA_2_mean      =    0.0;
static const double vertex_RR_barrel_DATA_2_stddev    = 4900.0;

static const double distancetowall_barrel_RECO_mean        =  0.0;
static const double distancetowall_barrel_RECO_stddev      = 52.5;
static const double distancetowall_barrel_DATA_mean        = 40.0;
static const double distancetowall_barrel_DATA_stddev      = 45.0;
static const double distancetowall_barrel_DATA_2_mean      =  0.0;
static const double distancetowall_barrel_DATA_2_stddev    = 35.0;
///////////
static const double vertex_Z_downstream_RECO_mean        =    0.0;
static const double vertex_Z_downstream_RECO_stddev      =  105.0;
static const double vertex_Z_downstream_DATA_mean        =  125.0;
static const double vertex_Z_downstream_DATA_stddev      =  110.0;
static const double vertex_Z_downstream_DATA_2_mean      =  125.0;
static const double vertex_Z_downstream_DATA_2_stddev    =  105.0;

static const double vertex_Z_RCut_downstream_RECO_mean        =    0.0;
static const double vertex_Z_RCut_downstream_RECO_stddev      =  105.0;
static const double vertex_Z_RCut_downstream_DATA_mean        =  125.0;
static const double vertex_Z_RCut_downstream_DATA_stddev      =  110.0;
static const double vertex_Z_RCut_downstream_DATA_2_mean      =  125.0;
static const double vertex_Z_RCut_downstream_DATA_2_stddev    =  105.0;


static const double vertex_R_downstream_RECO_mean        =   0.0;
static const double vertex_R_downstream_RECO_stddev      = 105.0;
static const double vertex_R_downstream_DATA_mean        = 125.0;
static const double vertex_R_downstream_DATA_stddev      = 110.0;
static const double vertex_R_downstream_DATA_2_mean      = 125.0;
static const double vertex_R_downstream_DATA_2_stddev    = 105.0;

static const double vertex_RR_downstream_RECO_mean        =    0.0;
static const double vertex_RR_downstream_RECO_stddev      =  400.0;
static const double vertex_RR_downstream_DATA_mean        =    0.0;
static const double vertex_RR_downstream_DATA_stddev      = 4900.0;
static const double vertex_RR_downstream_DATA_2_mean      =    0.0;
static const double vertex_RR_downstream_DATA_2_stddev    = 4900.0;

static const double distancetowall_downstream_RECO_mean        =  0.0;
static const double distancetowall_downstream_RECO_stddev      = 52.5;
static const double distancetowall_downstream_DATA_mean        = 40.0;
static const double distancetowall_downstream_DATA_stddev      = 45.0;
static const double distancetowall_downstream_DATA_2_mean      =  0.0;
static const double distancetowall_downstream_DATA_2_stddev    = 35.0;
//
static const double vertex_Z_downstreamConcave_RECO_mean        =    0.0;
static const double vertex_Z_downstreamConcave_RECO_stddev      =  105.0;
static const double vertex_Z_downstreamConcave_DATA_mean        =  125.0;
static const double vertex_Z_downstreamConcave_DATA_stddev      =  110.0;
static const double vertex_Z_downstreamConcave_DATA_2_mean      =  125.0;
static const double vertex_Z_downstreamConcave_DATA_2_stddev    =  105.0;

static const double vertex_Z_RCut_downstreamConcave_RECO_mean        =    0.0;
static const double vertex_Z_RCut_downstreamConcave_RECO_stddev      =  105.0;
static const double vertex_Z_RCut_downstreamConcave_DATA_mean        =  125.0;
static const double vertex_Z_RCut_downstreamConcave_DATA_stddev      =  110.0;
static const double vertex_Z_RCut_downstreamConcave_DATA_2_mean      =  125.0;
static const double vertex_Z_RCut_downstreamConcave_DATA_2_stddev    =  105.0;


static const double vertex_R_downstreamConcave_RECO_mean        =   0.0;
static const double vertex_R_downstreamConcave_RECO_stddev      = 105.0;
static const double vertex_R_downstreamConcave_DATA_mean        = 125.0;
static const double vertex_R_downstreamConcave_DATA_stddev      = 110.0;
static const double vertex_R_downstreamConcave_DATA_2_mean      = 125.0;
static const double vertex_R_downstreamConcave_DATA_2_stddev    = 105.0;

static const double vertex_RR_downstreamConcave_RECO_mean        =    0.0;
static const double vertex_RR_downstreamConcave_RECO_stddev      =  400.0;
static const double vertex_RR_downstreamConcave_DATA_mean        =    0.0;
static const double vertex_RR_downstreamConcave_DATA_stddev      = 4900.0;
static const double vertex_RR_downstreamConcave_DATA_2_mean      =    0.0;
static const double vertex_RR_downstreamConcave_DATA_2_stddev    = 4900.0;

static const double distancetowall_downstreamConcave_RECO_mean        =  0.0;
static const double distancetowall_downstreamConcave_RECO_stddev      = 52.5;
static const double distancetowall_downstreamConcave_DATA_mean        = 40.0;
static const double distancetowall_downstreamConcave_DATA_stddev      = 45.0;
static const double distancetowall_downstreamConcave_DATA_2_mean      =  0.0;
static const double distancetowall_downstreamConcave_DATA_2_stddev    = 35.0;


}



enum Convolution_shift{
kvertex_Z_totalRegion,
kvertex_R_totalRegion,
kvertex_RR_totalRegion,
kdistancetowall_totalRegion,

kDistancetoCap_upstream,
kvertex_Z_upstream,
kvertex_R_upstream,
kvertex_RR_upstream,
kdistancetowall_upstream,

kvertex_Z_barrel,
kvertex_R_barrel,
kvertex_RR_barrel,
kdistancetowall_barrel,

kDistancetoCap_downstream,
kvertex_Z_downstream,
kvertex_R_downstream,
kvertex_RR_downstream,
kdistancetowall_downstream,

kvertex_Z_downstreamConcave,
kvertex_R_downstreamConcave,
kvertex_RR_downstreamConcave,
kdistancetowall_downstreamConcave,

kvertex_Z_RCut_totalRegion,
kvertex_Z_RCut_upstream,
kvertex_Z_RCut_barrel,
kvertex_Z_RCut_downstream,
kvertex_Z_RCut_downstreamConcave,

};



struct Convolution_Parameters {
CryoVertex Vertex_type;

double stddev_toRECO;
double mean_toRECO;
double stddev_toDATA;
double mean_toDATA;
double stddev_toDATA2;
double mean_toDATA2;


double ChiSqrt_Truth_toRECO = -1.0;
double ChiSqrt_Truth_toData = -1.0;
double ChiSqrt_Reco_toData = -1.0;
};


typedef std::map<Convolution_shift, Convolution_Parameters > Convolution_Parameters_MAP;

Convolution_Parameters_MAP CreateConvolutionParameterMap();


double return_AlWgt(CryoTank_REGIONS input_region , Material_type input_material);
double return_shiftX();
double return_shiftY();
double return_shiftZ();
void PrintWgtsBeingUSED();





struct ChiSqrt_results{
  double Chisqrt_X;
  double Chisqrt_Y;
  double Chisqrt_Z;
  double Chisqrt_Z_RCut;
  double Chisqrt_R;
  double Chisqrt_NearestWall;
  double Chisqrt_DistancetoUpstreamCap;
  double Chisqrt_DistancetoUpstreamCap_RCut;
  double Chisqrt_DistancetoDownstreamCap;
  double Chisqrt_DistancetoDownstreamCap_RCut;
};



struct BestIndex {
Index3 best_Chisqrt_X;
Index3 best_Chisqrt_Y;
Index3 best_Chisqrt_Z;
Index3 best_Chisqrt_Z_RCut;
Index3 best_Chisqrt_R;
Index3 best_Chisqrt_NearestWall;
Index3 best_Chisqrt_DistancetoUpstreamCap;
Index3 best_Chisqrt_DistancetoUpstreamCap_RCut;
Index3 best_Chisqrt_DistancetoDownstreamCap;
Index3 best_Chisqrt_DistancetoDownstreamCap_RCut;
};

struct Best4IndexFit {
Index4 best_Chisqrt_X;
Index4 best_Chisqrt_Y;
Index4 best_Chisqrt_Z;
Index4 best_Chisqrt_R;

Normal_Fit_Parameters FitXpars;
Normal_Fit_Parameters FitYpars;
Normal_Fit_Parameters FitZpars;
Normal_Fit_Parameters FitRpars;

};




struct ChiSqrt_CryoTankRegions{
ChiSqrt_results upstream;
ChiSqrt_results barrel;
ChiSqrt_results downstream;
ChiSqrt_results concave;
};

struct BestIndex_Regions {

  BestIndex upstream;
  BestIndex barrel;
  BestIndex downstream;
  BestIndex concave;

};


struct Best4Index_Regions {

  Best4IndexFit upstream;
  Best4IndexFit barrel;
  Best4IndexFit downstream;
  Best4IndexFit concave;

};


struct Convolution_hist
{
  CryoVertex CryoVertex_type;
  std::string Data_name;
  std::string Reco_name;
  std::string TRUE_name;
  std::string TRUE_Convoluted_name;
  std::string Reco_Material_name;



  MnvH1D* MnvH1D_data;
  MnvH1D* MnvH1D_mc_Reco;
  MnvH1D* MnvH1D_mc_TRUTH;
  MnvH1D* MnvH1D_mc_Convoluted[2]; // 0 Convoluted RECO, 1 Convoluted RECO Reweighted Reco

  MnvH1D* MnvH1D_mc_Convoluted_Helium[2]; // 0 Convoluted RECO, 1 Convoluted RECO Reweighted Reco
  MnvH1D* MnvH1D_mc_Convoluted_Aluminium[2]; // 0 Convoluted RECO, 1 Convoluted RECO Reweighted Reco
  MnvH1D* MnvH1D_mc_Convoluted_Carbon[2]; // 0 Convoluted RECO, 1 Convoluted RECO Reweighted Reco
  MnvH1D* MnvH1D_mc_Convoluted_Iron[2]; // 0 Convoluted RECO, 1 Convoluted RECO Reweighted Reco
  MnvH1D* MnvH1D_mc_Convoluted_Lead[2]; // 0 Convoluted RECO, 1 Convoluted RECO Reweighted Reco
  MnvH1D* MnvH1D_mc_Convoluted_Other[2]; // 0 Convoluted RECO, 1 Convoluted RECO Reweighted Reco



  std::string Xaxis_Title;

};


struct Convolution_CryoRegions
{
Convolution_hist Upstream;
Convolution_hist Barrel;
Convolution_hist Downstream;
Convolution_hist Concave;

};


struct  ConvolutionShiftMap{

  std::string name = "Default";

  Convolution_hist Vertex_X_TotalRegion;
  Convolution_hist Vertex_Y_TotalRegion;
  Convolution_hist Vertex_R_TotalRegion;
  Convolution_hist Vertex_RR_TotalRegion;
  Convolution_hist Vertex_Z_TotalRegion;
  Convolution_hist Vertex_Z_TotalRegion_RCut;
  Convolution_hist NearestWall_TotalRegion;
  Convolution_hist DistanceUpstreamCap_TotalRegion;
  Convolution_hist DistanceDownstreamCap_TotalRegion;
  Convolution_hist DistanceUpstreamCap_TotalRegion_RCut;
  Convolution_hist DistanceDownstreamCap_TotalRegion_RCut;


  Convolution_CryoRegions Vertex_X_Regions;
  Convolution_CryoRegions Vertex_Y_Regions;
  Convolution_CryoRegions Vertex_Z_Regions;
  Convolution_CryoRegions Vertex_R_Regions;
  Convolution_CryoRegions Vertex_TRUE_X_Regions;
  Convolution_CryoRegions Vertex_TRUE_Y_Regions;
  Convolution_CryoRegions Vertex_TRUE_Z_Regions;
  Convolution_CryoRegions Vertex_TRUE_R_Regions;
  Convolution_CryoRegions Vertex_Z_Regions_RCut;
  Convolution_CryoRegions Vertex_RR_Regions;

  Convolution_CryoRegions DistanceUpstreamCap_Regions;
  Convolution_CryoRegions DistanceDownstreamCap_Regions;
  Convolution_CryoRegions DistanceUpstreamCap_Regions_RCut;
  Convolution_CryoRegions DistanceDownstreamCap_Regions_RCut;

  Convolution_CryoRegions muonPT_Regions;
  Convolution_CryoRegions muonPZ_Regions;
  Convolution_CryoRegions muonE_Regions;
  Convolution_CryoRegions muontheta_Regions;
  Convolution_CryoRegions muonDOCA_Regions;
  Convolution_CryoRegions NearestWall_Regions;
  Convolution_CryoRegions recoilDOCA_Regions;
  Convolution_CryoRegions recoilAngle_Regions;
  Convolution_CryoRegions tracklength_Regions;

  double POT_MC  = 1.0;
  double POT_Data = 1.0;



};

Best4IndexFit init_defaultBest4IndexFit();


class Convolution_Tool
{
  public:
    Convolution_Tool();
    Convolution_Tool(ME_playlist_TFileMAP TFile_Map_Full_MC_input,
                      ME_playlist_TFileMAP TFile_Map_Full_Data_input,
                      ME_playlist_TFileMAP TFile_Map_Empty_MC_input,
                      ME_playlist_TFileMAP TFile_Map_Empty_Data_input,
                      Pot_MapList POTMap_Full_Data_input,
                      Pot_MapList POTMap_Full_MC_input,
                      Pot_MapList POTMap_Empty_Data_input,
                      Pot_MapList POTMap_Empty_MC_input) :
                      TFile_Map_Full_MC(TFile_Map_Full_MC_input),
                      TFile_Map_Full_Data(TFile_Map_Full_Data_input),
                      TFile_Map_Empty_MC(TFile_Map_Empty_MC_input),
                      TFile_Map_Empty_Data(TFile_Map_Empty_Data_input),
                      POTMap_Full_Data(POTMap_Full_Data_input),
                      POTMap_Full_MC(POTMap_Full_MC_input),
                      POTMap_Empty_Data(POTMap_Empty_Data_input),
                      POTMap_Empty_MC(POTMap_Empty_MC_input)
                      {}
Convolution_Tool( ME_playlist_TFileMAP TFile_Map_Empty_MC_input,
                  ME_playlist_TFileMAP TFile_Map_Empty_Data_input,
                  Pot_MapList POTMap_Empty_Data_input,
                  Pot_MapList POTMap_Empty_MC_input) :
                  TFile_Map_Empty_MC(TFile_Map_Empty_MC_input),
                  TFile_Map_Empty_Data(TFile_Map_Empty_Data_input),
                  POTMap_Empty_Data(POTMap_Empty_Data_input),
                  POTMap_Empty_MC(POTMap_Empty_MC_input)
                  {}
Convolution_Tool(TFile *inputFull, TFile *InputEmpty) : InputFull_Plotting(inputFull), InputEmpty_Plotting(InputEmpty){}
~Convolution_Tool();
void assign_CryoVertex_type();
void Intialize_dataHistNames();
void assign_RegionsHist_RecoandTRUEName();
void assign_TotalRegionHist_dataName();
void assign_RegionsHist_dataName();
void assign_CryoVertexTotalRegion_ConvolutedTRUEHistName();
void assign_Material_XYZR_HistName();

void ConstuctandFill_Complete_NuMEPlaylist_POT(
  std::vector<ME_helium_Playlists> FullPlaylist,
  std::vector<ME_helium_Playlists> EmptyPlaylist);

void init_NuMEPlaylist_POT();
void init_All_DataHists();
void init_All_DataEmptyHists();
void init_All_DataFullHists();
void init_All_RecoHists();
void init_Total_RecoHists();
void init_Regions_RecoHists();
void init_All_TRUEHists();
void init_Regions_TRUEHists();
void init_Total_TRUEHists();
void CloneFulltoFull_Empty();
void CloneFulltoFull_Empty_Fiducial();
void CloneFulltoFull_Empty_TRUE();
void CloneFulltoFull_Empty_TRUE_Fiducial();
void ClearChisqrtvector();

void init_TRUTHConvolution_MCZEROShifted_PlaylistCombined_Histograms(
  ConvolutionShiftMap &input, ME_playlist_TFileMAP TFile_Map_MC,
   ME_helium_Playlists StartingPlaylist );

void SetPotTitle(std::string input){PlotTitle = input;}
void SetBoundaries(double upsteam_barrel,double barrle_downstream, double downstream_cave )
{
  boundary_upstream_barrel = upsteam_barrel;
  boundary_barrel_downstream = barrle_downstream;
  boundary_downstream_concave = downstream_cave;}

void includeBouodaries(bool input){ includeboundary = input; }

void SetBinWidthNorm(bool input);
void SetXaxis_toLog(bool input);
void SetZeroshift4index(Index4 input );
void PlotFull(double Convoluted_Mean, double Convoluted_stddev, int ind );
void PlotFull_ConvolRECO(double Convoluted_Mean, double Convoluted_stddev, int ind );
void PlotEmpty(double Convoluted_Mean, double Convoluted_stddev, int ind );
void PlotFull_Empty(double Convoluted_Mean, double Convoluted_stddev, int ind );
void Plot_EventDistrubution_TotalRegion(ConvolutionShiftMap &inputMap, std::string Playlist_name,
   std::string playlist_status, double Convoluted_Mean, double Convoluted_stddev, int ind);
void Plot_EventDistrubution_ConvolRECO_TotalRegion(ConvolutionShiftMap &inputMap, std::string Playlist_name,
      std::string playlist_status, double Convoluted_Mean, double Convoluted_stddev, int ind);

void Plot_EventDistrubution_ConvolRECO_TotalRegion(ConvolutionShiftMap &inputMap, std::string Playlist_name,
         std::string playlist_status,  BestIndex Index_input, NormalParaFit_Map ZShifts );

void Plot_EventDistrubution_BestRegionsXYRZ(ConvolutionShiftMap &inputMap,Normal_Fit_ParametersXY &inputMapParametersXY, std::string Playlist_name,
            std::string playlist_status, int ind);

void Plot_EventDistrubution_ConvolRECO_TotalRegion_F_E(ConvolutionShiftMap &inputMap, std::string Playlist_name,
   std::string playlist_status,  BestIndex Index_input_Full, BestIndex Index_input_Empty, NormalParaFit_Map ZShifts );

void Plot_Full_ConvolRECO(NormalParaFit_Map ZShifts, BestIndex Index_input_Full, BestIndex Index_input_Empty);

void Plot_EventDistrubution_Regions(ConvolutionShiftMap &inputMap, std::string Playlist_name,
   std::string playlist_status, double Convoluted_Mean, double Convoluted_stddev, int ind);

void Plot_EventDistrubution_FITRegionsOnly_ConvolRECO_Empty(double Convoluted_Mean, double Convoluted_stddev);

void Plot_EventDistrubution_FITRegionsOnly_ConvolRECO(ConvolutionShiftMap &inputMap, std::string Playlist_name,
   std::string playlist_status, double Convoluted_Mean, double Convoluted_stddev);

void Plot_regions_XYFit(ConvolutionShiftMap inputMap, Normal_Fit_ParametersXY inputMapParametersXY , int ind, int FitType, std::string Hist_title, bool doAreaNormalized, bool applyMaxY , bool isFiduical =false );


void Plot_ConvolRECO_Eventdistrubution_Regions(Convolution_CryoRegions &histsInput,
  std::string Playlist_name,  std::string histotitle, std::string playlist_status,
  double Ymax, double Convoluted_Mean, double Convoluted_stddev);

void Plot_ConvolRECO_Eventdistrubution_Regions(
  Convolution_CryoRegions &histsInput,
  std::string Playlist_name,
  std::string histotitle,
  std::string playlist_status,
  double Ymax,
  double Convoluted_Mean_USCap,   double Convoluted_stddev_USCap,
  double Convoluted_Mean_barrel,  double Convoluted_stddev_barrel,
  double Convoluted_Mean_DSCap,   double Convoluted_stddev_DSCap,
  double Convoluted_Mean_concave, double Convoluted_stddev_concave);


void Plot_Eventdistrubution_Regions(Convolution_CryoRegions &histsInput,   std::string Playlist_name,  std::string histotitle, std::string playlist_status,
  double Ymax, double Convoluted_Mean, double Convoluted_stddev, int ind);

void Plot_EventDistrubution_Regions_ConvolRECO(ConvolutionShiftMap &inputMap, std::string Playlist_name,
     std::string playlist_status, double Convoluted_Mean, double Convoluted_stddev);

void Plot_EventDistrubution_Regions_F_E(Convolution_CryoRegions &inputMap, std::string Playlist_name, std::string xaxislabel, std::string PlotTitle,
        std::string playlist_status,
        Index3 bestupstreamF,   Index3 bestupstreamE,
        Index3 bestbarrelF,     Index3 bestbarrelE,
        Index3 bestdownstreamF, Index3 bestdownstreamE,
        Index3 bestconcaveF,    Index3 bestconcaveE,
         NormalParaFit_Map ShiftsMap  );


void Plot_Regions(double Convoluted_Mean, double Convoluted_stddev);
void Plot_Regions_ConvolRECO(double Convoluted_Mean, double Convoluted_stddev);

void PlotFull_Regions(double Convoluted_Mean, double Convoluted_stddev, int ind );
void PlotFull_Regions_ConvolRECO(double Convoluted_Mean, double Convoluted_stddev );

void PlotEmpty_Regions(double Convoluted_Mean, double Convoluted_stddev, int ind );
void PlotEmpty_Regions_ConvolRECO(double Convoluted_Mean, double Convoluted_stddev );
void Plot_EmptyOnly_ConvolRECO(double Convoluted_Mean, double Convoluted_stddev);
void Plot_FullOnly_ConvolRECO(double Convoluted_Mean, double Convoluted_stddev);
void PlotFull_Empty_Regions(double Convoluted_Mean, double Convoluted_stddev, int ind );
void PlotFull_Empty_Regions_ConvolRECO(double Convoluted_Mean, double Convoluted_stddev);
void Plot_init_material_Full(std::string title);
void Plot_AfterFit_material_Full(std::string title);
void Plot_init_material_Empty(std::string title);
void Plot_AfterFit_material_Empty(std::string title);
void init_ALL_Convolution_Regions_Hists_PlaylistCombinedMC(int i, int j, int k);
void init_ALL_RECOConvolution_Regions_Hists_PlaylistCombinedMC(int i, int j, int k);

void init_TRUE_Total_and_Regions_Hists_PlaylistCombinedMC(ConvolutionShiftMap &input,
   ME_playlist_TFileMAP TFile_Map_MC,
    ME_helium_Playlists StartingPlaylist,
     int i, int j, int k );

void init_RECO_Total_and_Regions_Hists_PlaylistCombinedMC(ConvolutionShiftMap &input,
   ME_playlist_TFileMAP TFile_Map_MC,
    ME_helium_Playlists StartingPlaylist,
    int i, int j, int k );

void init_ZeroShift_TRUE_Convolution_Regions_Hists_PlaylistCombinedMC();
void init_ZeroShift_RECO_Convolution_Regions_Hists_PlaylistCombinedMC();
void init_TRUE_Convolution_TotalHists_PlaylistCombinedMC(int i , int j, int k);
void init_TRUE_Convolution_Regions_Hists_PlaylistCombinedMC(int i , int j, int k);

void init_RECO_Convolution_TotalHists_PlaylistCombinedMC(int i , int j, int k);
void init_RECO_Convolution_TotalHists_PlaylistCombinedMC(BestIndex bestindex_Full, BestIndex bestindex_Empty);
void init_RECO_Convolution_Regions_Hists_PlaylistCombinedMC(int i , int j, int k);

void init_RECO_Convolution_RegonsHists_PlaylistCombinedMC(BestIndex_Regions bestindex_Full, BestIndex_Regions bestindex_Empty);

void initEMPTYONLY_RECO_Convolution_Material_Regions_TRUEHists_PlaylistCombinedMC(int i, int j, int k);
void initEMPTYONLY_RECO_Convolution_Material_Regions_TRUEHists_PlaylistCombinedMC_Fiducial(int i, int j, int k);
void initEMPTYONLY_RECO_Convolution_Material_Regions_NON_vertex_varsHists_PlaylistCombinedMC(int i, int j, int k);
void initEMPTYONLY_RECO_Convolution_Material_Regions_NON_vertex_varsHists_PlaylistCombinedMC_Fiducial(int i, int j, int k);

void initFULLONLY_RECO_Convolution_Material_Regions_TRUEHists_PlaylistCombinedMC(int i, int j, int k);

void initFULLONLY_RECO_Convolution_Material_Regions_TRUEHists_PlaylistCombinedMC_Fiducial(int i, int j, int k);
void initFULLONLY_RECO_Convolution_Material_Regions_NON_vertex_varsHists_PlaylistCombinedMC(int i, int j, int k);
void initFULLONLY_RECO_Convolution_Material_Regions_NON_vertex_varsHists_PlaylistCombinedMC_Fiducial(int i, int j, int k);

void input_pdfLabel(std::string input_name);
void printDATAhistname(Convolution_hist input_hist);
void print_Total_DATAhistname(ConvolutionShiftMap input_Map);
void printRECOhistname(Convolution_hist input_hist);
void print_Total_RECOhistname(ConvolutionShiftMap input_Map);
void printTRUEhistname(Convolution_hist input_hist);
void print_Total_TRUEhistname(ConvolutionShiftMap input_Map);
void printConvolutedTRUEhistname(Convolution_hist input_hist);
void print_Total_ConvolutedTRUEhistname(ConvolutionShiftMap input_Map);
void Print_initNames(ConvolutionShiftMap input_histmap);
void Print_initNames_Empty();
void Plot_Full(double Convoluted_Mean, double Convoluted_stddev);
void Plot_Full_ConvolRECO(double Convoluted_Mean, double Convoluted_stddev);
void PrintPOT();
void assign_xAxis();
void SaveBestChisqt_Total(ChiSqrt_results &Best, BestIndex &bestindex, ChiSqrt_results &Compare , Index3 input );

void SaveBestChiSqrt_Regions(ChiSqrt_CryoTankRegions &input_Full_best,
                        ChiSqrt_CryoTankRegions &input_Empty_best,
                        ChiSqrt_CryoTankRegions &input_Full_Empty_best,
                        ChiSqrt_CryoTankRegions &input_Full,
                        ChiSqrt_CryoTankRegions &input_Empty,
                        ChiSqrt_CryoTankRegions &input_Full_Empty,
                        BestIndex_Regions &bestindex_Full,
                        BestIndex_Regions &bestindex_Empty,
                        BestIndex_Regions &bestindex_Full_Empty, Index3 input);

void Cal_Chisqrt_ConvolutionTruth_ToData_Regions(MnvPlotter *MnvPlotter,
  ConvolutionShiftMap &Hist_Map, ChiSqrt_CryoTankRegions &Chi_Sqt_Map, int ind);

void Cal_Chisqt_Total(ConvolutionShiftMap &Hist_Map, ChiSqrt_results &input, MnvPlotter *MnvPlotter , int ind);
void Cal_Chisqt_Total(ChiSqrt_results &inputFull, ChiSqrt_results &inputEmpty,
  ChiSqrt_results &input_Full_Empty, MnvPlotter *MnvPlotter, int ind );
void Cal_Chisqrt_ConvolutionTruth_ToData(MnvPlotter *MnvPlotter,
  Convolution_hist input,double &Chi2DataMC_DatatoTRUTH,
   int &ndf_Chi2DataMC_DatatoTRUTH, int ind );

void Cal_Chisqrt_ConvolutionTruth_ToData_Regions(MnvPlotter *MnvPlotter, ChiSqrt_CryoTankRegions &inputFull,
  ChiSqrt_CryoTankRegions &inputEmpty, ChiSqrt_CryoTankRegions &input_Full_Empty, int ind );

void Fill_TotalChiSqrts(ChiSqrt_results &ChiSqrt_input, double mean,
  double stddev,
  MnvH2D *h2_Vertex_X_TotalRegion[],
  MnvH2D *h2_Vertex_Y_TotalRegion[],
  MnvH2D *h2_Vertex_R_TotalRegion[],
  /*MnvH2D &h2_Vertex_RR_TotalRegion,*/
  MnvH2D *h2_Vertex_Z_TotalRegion[],
  MnvH2D *h2_Vertex_Z_TotalRegion_RCut[],
  MnvH2D *h2_NearestWall_TotalRegion[],
  MnvH2D *h2_DistanceUpstreamCap_TotalRegion[],
  MnvH2D *h2_DistanceDownstreamCap_TotalRegion[],
  MnvH2D *h2_DistanceUpstreamCap_TotalRegion_RCut[],
  MnvH2D *h2_DistanceDownstreamCap_TotalRegion_RCut[]);


void Fill_TotalChiSqrts_Regions(ChiSqrt_CryoTankRegions &ChiSqrt_input, double mean,
  double stddev,
  MnvH2D *h2_Vertex_X_Regions[],
  MnvH2D *h2_Vertex_Y_Regions[],
  MnvH2D *h2_Vertex_R_Regions[],
  /*MnvH2D &h2_Vertex_RR_Regions[5],*/
  MnvH2D *h2_Vertex_Z_Regions[],
  MnvH2D *h2_Vertex_Z_Regions_RCut[],
  MnvH2D *h2_NearestWall_Regions[],
  MnvH2D *h2_DistanceUpstreamCap_Regions[],
  MnvH2D *h2_DistanceDownstreamCap_Regions[],
  MnvH2D *h2_DistanceUpstreamCap_Regions_RCut[],
  MnvH2D *h2_DistanceDownstreamCap_Regions_RCut[]);

void SaveBestChiSqrt_Total(ChiSqrt_results &inputFull_best,
                          ChiSqrt_results &inputEmpty_best,
                          ChiSqrt_results &input_Full_Empty_best,
                          ChiSqrt_results &inputFull_input,
                          ChiSqrt_results &inputEmpty_input,
                          ChiSqrt_results &input_Full_Empty_input,
  BestIndex &bestindex_Full, BestIndex &bestindex_Empty, BestIndex &bestindex_Full_Empty,
  Index3 input);


void Fill_bestIndex3_default(BestIndex &input);
void Fill_Regions_bestindex3_default(BestIndex_Regions inputMap);
void Fill_ChiSqrt_results_default(ChiSqrt_results &inputMap);
void Fill_Regions_ChiSqrt_results_default(ChiSqrt_CryoTankRegions &inputMap);
void SaveBestChisqt_Regions(ChiSqrt_CryoTankRegions &Best_Map,
  BestIndex_Regions &bestindex,
  ChiSqrt_CryoTankRegions &Compare_Map , Index3 input );

void init_RECO_Convolution_Material_Regions_Hists_PlaylistCombinedMC(int i, int j, int k);
void init_RECO_Convolution_Material_Regions_Hists_PlaylistCombinedMC(int i, int j, int k, int m);
void initEMPTYONLY_RECO_Convolution_Material_Regions_Hists_PlaylistCombinedMC(int i, int j, int k);
void initEMPTYONLY_RECO_Convolution_Material_Regions_Hists_PlaylistCombinedMC_Fiducial(int i, int j, int k);
void initFULLONLY_RECO_Convolution_Material_Regions_Hists_PlaylistCombinedMC_Fiducial(int i, int j, int k);
void initEMPTYONLY_RECO_Convolution_Material_Regions_Hists_PlaylistCombinedMC(int i, int j, int k , int m);
void initFULLONLY_RECO_Convolution_Material_Regions_Hists_PlaylistCombinedMC(int i, int j, int k);
void initFULLONLY_RECO_Convolution_Material_Regions_Hists_PlaylistCombinedMC(int i, int j, int k, int m);
void init_TRUE_ConvolutionTotalHists_PlaylistCombinedMC(int i , int j, int k);
void init_RECO_ConvolutionTotalHists_PlaylistCombinedMC(int i , int j, int k);
void init_DataConvolutionHists(TFile *inputfile, Convolution_hist& input, std::string Histname);
void init_MaterialType(TFile *inputfile, Convolution_hist& input,int ind, std::string Histname);
void init_MaterialType_Regions(TFile *inputfile, Convolution_CryoRegions &input,int ind, std::string histname);
void init_DataType_Regions(TFile *inputfile, Convolution_CryoRegions &input, std::string histname);
void Fill_Alwgt(std::vector<double>inputWgt,std::vector<double>inputwgt_errors );
void Clear_Al_wgt();
void ApplyFitResults_toEmpty();
void ApplyFitResults_toTRUEEmpty();
void ApplyFitResults_tononFitVarEmpty();
void ApplyFitResults_toFull();
void ApplyFitResults_toTRUEFull();
void ApplyFitResults_tononFitVarFull();

void ApplyFitResults_toEmpty_Fiducial();
void ApplyFitResults_toTRUEEmpty_Fiducial();
void ApplyFitResults_tononFitVarEmpty_Fiducial();
void ApplyFitResults_toFull_Fiducial();
void ApplyFitResults_toTRUEFull_Fiducial();
void ApplyFitResults_tononFitVarFull_Fiducial();

void ApplyFitResults_toFullEmptyJointFit();

void CalMaterial_ChiSqrtFullAfter( double &chisqrt_x,
  double &chisqrt_y, double &chisqrt_z, double &chisqrt_r);

void CalMaterial_ChiSqrtEmptyAfter( double &chisqrt_x,
   double &chisqrt_y, double &chisqrt_z, double &chisqrt_r);

void init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined_FittingVar(
  ConvolutionShiftMap &input, std::string ExtraString,
   ME_playlist_TFileMAP TFile_Map_MC,ME_helium_Playlists StartingPlaylist,
   int i, int j, int k, int m );

void POTscale_MC_Convoluted_Regions_fitRegionsOnly(ConvolutionShiftMap &input,
                                                  double POTscaler, int ind);
void Subtract_TRUEConvolutionHists_Regions_FitVars(
   ConvolutionShiftMap &Subtract_from, ConvolutionShiftMap &input, int ind);
void init_RECO_Convolution_Regions_Hists_PlaylistCombinedMC_ForFit(int i, int j,
                                                                  int k,
                                                                  int m);
void init_RECO_Convolution_Regions_Hists_PlaylistCombinedMC_ForFit_Full(int i,
                                                                       int j,
                                                                       int k,
                                                                       int m);
void init_RECO_Convolution_Regions_Hists_PlaylistCombinedMC_ForFit_Empty(int i,
                                                                        int j,
                                                                        int k,
                                                                        int m);
void init_Full_Plotting_PlaylistCombined(bool isinit, int rank, int i, int j,
                                        int k);
void init_Full_Plotting_PlaylistCombined_Fiducial(bool isinit, int rank, int i,
                                                 int j, int k);
void init_Empty_Plotting_PlaylistCombined(bool isinit, int rank, int i, int j,
                                         int k);
void init_Empty_Plotting_PlaylistCombined_Fiducial(bool isinit, int rank, int i,
                                                  int j, int k);
void Fill_Alwgt_full_empty(std::vector<double> inputWgt,
                          std::vector<double> inputwgt_errors);
void Plot_regions_XYFit_Empty(Normal_Fit_ParametersXY inputMapParametersXY,
                             int ind, int FitType, std::string Hist_title);
void Plot_regions_XYFit_Full(Normal_Fit_ParametersXY inputMapParametersXY,
                            int ind, int FitType, std::string Hist_title);
void Plot_regions_XYZFit(ConvolutionShiftMap inputMap,
                        Normal_Fit_ParametersXY inputMapParametersXY,
                        double Zmean, double Zsigma, int ind, int FitType,
                        std::string Hist_title, bool doAreaNormalized,
                        bool applyMaxY, bool isFiduical = false,
                        bool isFull_Empty = false, double ZmeanE = 99,
                        double ZsigmaE = 99);

void Plot_regions_XYZFit_TRUE(ConvolutionShiftMap inputMap,
    Normal_Fit_ParametersXY inputMapParametersXY, double Zmean , double Zsigma, int ind, int FitType,
    std::string Hist_title, bool doAreaNormalized, bool applyMaxY,  bool isFiduical = false  );

void Plot_regions_nonFitVarsFit(ConvolutionShiftMap inputMap,
  Normal_Fit_ParametersXY inputMapParametersXY, double Zmean , double Zsigma, int ind, int FitType,
  std::string Hist_title, bool doAreaNormalized, bool applyMaxY ,  bool isFull_Empty = false ,  double ZmeanE= 99 , double ZsigmaE =99  );

void Plot_regions_XYZFit_Full(double Zmean, double Zsigma, int ind, int FitType,
                              std::string Hist_title);
void Plot_regions_XYZFit_Empty(double Zmean, double Zsigma, int ind,
                               int FitType, std::string Hist_title);
void Plot_regions_XYZFit_Full_Fiducial(double Zmean, double Zsigma, int ind,
                                       int FitType, std::string Hist_title);
void Plot_regions_XYZFit_Empty_Fiducial(double Zmean, double Zsigma, int ind,
                                        int FitType, std::string Hist_title);

void Plot_regions_XYZFit_Full_Empty(double ZmeanF, double ZsigmaF,
                                    double ZmeanE, double ZsigmaE, int ind,
                                    int FitType, std::string Hist_title);
void Plot_regions_XYZFit_Full_Empty_Fiducial(double ZmeanF, double ZsigmaF,
                                             double ZmeanE, double ZsigmaE,
                                             int ind, int FitType,
                                             std::string Hist_title);

void Plot_regions_TRUEXYZFit_Empty(double Zmean, double Zsigma, int ind,
                                   int FitType, std::string Hist_title);
void Plot_regions_TRUEXYZFit_Empty_Fiducial(double Zmean, double Zsigma,
                                            int ind, int FitType,
                                            std::string Hist_title);

void Plot_regions_TRUEXYZFit_Full(double Zmean, double Zsigma, int ind,
                                  int FitType, std::string Hist_title);
void Plot_regions_TRUEXYZFit_Full_Fiducial(double Zmean, double Zsigma, int ind,
                                           int FitType, std::string Hist_title);
void Plot_regions_TRUEXYZFit_Full_Empty(double Zmean, double Zsigma, int ind,
                                        int FitType, std::string Hist_title);
void Plot_regions_TRUEXYZFit_Full_Empty_Fiducial(double Zmean, double Zsigma,
                                                 int ind, int FitType,
                                                 std::string Hist_title);

void Plot_regions_NonFitVars_Empty(double Zmean, double Zsigma, int ind,
                                   int FitType, std::string Hist_title);
void Plot_regions_NonFitVars_Empty_Fiducial(double Zmean, double Zsigma,
                                            int ind, int FitType,
                                            std::string Hist_title);
void Plot_regions_NonFitVars_Full(double Zmean, double Zsigma, int ind,
                                  int FitType, std::string Hist_title);
void Plot_regions_NonFitVars_Full_Fiducial(double Zmean, double Zsigma, int ind,
                                           int FitType, std::string Hist_title);
void Plot_regions_NonFitVars_Full_Empty(double ZmeanF, double ZsigmaF,
                                        double ZmeanE, double ZsigmaE, int ind,
                                        int FitType, std::string Hist_title);
void Plot_regions_NonFitVars_Full_Empty_Fiducial(double ZmeanF, double ZsigmaF,
                                                 double ZmeanE, double ZsigmaE,
                                                 int ind, int FitType,
                                                 std::string Hist_title);

void FillEmpty_Normal_Fit_ParametersXY(double meanX , double sigmaX, double meanY , double sigmaY);
void FillFull_Normal_Fit_ParametersXY(double meanX , double sigmaX, double meanY , double sigmaY);
void Write_Empty_init_and_wgted(TFile& f,  char *nameinput);
void Write_Full_init_and_wgted(TFile& f,  char *nameinput);

void Write_Empty_init_and_wgted_Fiducial(TFile& f,  char *nameinput);
void Write_Full_init_and_wgted_Fiducial(TFile& f,  char *nameinput);

void assign_Convolution_CryoRegions_dataHistName_nonVertexVars(ConvolutionShiftMap &input_histmap);
void assign_Convolution_CryoRegions_dataHistName_nonVertexVars_Fiducial(ConvolutionShiftMap &input_histmap);
void Subtract_DataHists_Regions_Vars(ConvolutionShiftMap &Subtract_from , ConvolutionShiftMap &input);
void Subtract_Full_Empty(int ind);

void Subtract_Full_Empty_Fiducial(int ind);
void ClonetoFull_EMPTY(int indnew , int indtoclone);
void ClonetoFull_EMPTY_Fiducial(int indnew , int indtoclone);
void CloneTRUEVertex(ConvolutionShiftMap &input, ConvolutionShiftMap &inputClone);

void GetVectorChiSq_before_fit(std::vector<double> &inputVector);
void GetVectorChiSqVars_before_fit(std::vector<double> &inputVector);
void GetVectorChiSq_after_fit(std::vector<double> &inputVector);
void GetVectorChiSqVars_after_fit(std::vector<double> &inputVector);


ConvolutionShiftMap Full;
ConvolutionShiftMap Empty;
ConvolutionShiftMap Full_Empty;

ConvolutionShiftMap Full_Fid;
ConvolutionShiftMap Empty_Fid;
ConvolutionShiftMap Full_Empty_Fid;



ME_playlist_TFileMAP TFile_Map_Full_MC;
ME_playlist_TFileMAP TFile_Map_Full_Data;

ME_playlist_TFileMAP TFile_Map_Empty_MC;
ME_playlist_TFileMAP TFile_Map_Empty_Data;

TFile *InputFull_Plotting;
TFile *InputEmpty_Plotting;

ME_helium_Playlists StartingPlaylist_Full = kME1F;
ME_helium_Playlists StartingPlaylist_Empty = kME1M;

std::vector<ME_helium_Playlists> FullPlaylist_vector{kME1P,kME1C,kME1D,kME1F,kME1E};
std::vector<ME_helium_Playlists> EmptyPlaylist_vector{kME1G,kME1A,kME1L,kME1M,kME1N};

Pot_MapList POTMap_Empty_Data;
Pot_MapList POTMap_Empty_MC;
Pot_MapList POTMap_Full_Data;
Pot_MapList POTMap_Full_MC;

NormalParaFit_Map ZShifts;
std::vector<CryoVertex> CryoVertexVars_vectorList{kX, kY, kZ, kR, kRR, kdistance_edge, kdistance_upstreamcap,kdistance_downstreamcap};
std::string PlotTitle;
Index3 ZeroShift3index{0,0,1};
Index4 ZeroShift4index;
std::string globalpdf_label;
std::string globalpdf_labelwithpdf;
bool global_DoBinwidthNorm = true;
bool global_MakeXaxisLOG = false;
bool global_MakeAreaNorm_todata = true;
bool global_doAreaNormalized_Tool = false;
bool MakeBinWidth = true;
bool IsHeandAlFit = false;
bool UseLogChi_Tool = false;

bool set_ymax_forFitVars = true;
std::vector<double> wgt_Aluminium;
std::vector<double> err_Aluminium;

std::vector<double> wgt_Aluminium_Full;
std::vector<double> err_Aluminium_Full;

std::vector<double> wgt_Aluminium_Empty;
std::vector<double> err_Aluminium_Empty;


std::vector<double> wgt_Helium;
std::vector<double> err_Helium;
std::vector<double> ChiSq_before_fit;
std::vector<double> ChiSq_after_fit;
std::vector<double> ChiSq_before_fit_var;
std::vector<double> ChiSq_after_fit_var;

double YaxisMax_X = 12.0;
double YaxisMax_Y = 18.0;
double YaxisMax_Z = 16.0;
double YaxisMax_R = 45.0;


double YaxisMax_X_Fid = 8.0;
double YaxisMax_Y_Fid = 8.0;
double YaxisMax_Z_Fid = 12.0;
double YaxisMax_R_Fid = 20.0;

double boundary_upstream_barrel;
double boundary_barrel_downstream;
double boundary_downstream_concave;
bool includeboundary = false;

Normal_Fit_ParametersXY global_MapParametersXY_Full;
Normal_Fit_ParametersXY global_MapParametersXY_Empty;

 private:
   MnvH1D* GetMnvH1D(TFile* f, std::string var_name);
   MnvH2D* GetMnvH2D(TFile* f, std::string var_name);
   void assign_CryoVertex_dataHistName(std::string name,
      Convolution_hist &input_hist);
   void assign_CryoVertex_dataHistName(CryoVertex type, std::string AddString,
       Convolution_hist &input_hist);
   void assign_CryoVertex_dataHistName(CryoVertex type, std::string AddString,
       Convolution_CryoRegions &input_histmap);

   void assignTotalRegion_dataHistName(ConvolutionShiftMap &input_histmap);
   void assign_CryoVertex_RecoHistName(std::string name,
                                       Convolution_hist &input_hist);
   void assign_CryoVertex_Material_RecoHistName(std::string name,
                                                Convolution_hist &input_hist);
   void assign_CryoVertex_TRUEHistName(std::string name,
                                       Convolution_hist &input_hist);
   void assign_CryoVertex_ConvolutedTRUEHistName(std::string name,
                                                 Convolution_hist &input_hist);
   void assign_CryoVertex_type(CryoVertex type, Convolution_hist &input_hist);
   void assign_CryoVertex_type(ConvolutionShiftMap &Shift_Map);
   void assign_CryoVertex_type_Regions(CryoVertex type,
                                       Convolution_CryoRegions &input_region_hist);
   void assign_Xaxis_CryoVertex_type_Regions(
       Convolution_CryoRegions &input_region_hist);
   void assign_Convolution_CryoRegions_dataHistName(
       Convolution_CryoRegions &input_histmap, std::string inputname);
   void assignRegions_dataHistName(ConvolutionShiftMap &input_histmap);
   void assignRegions_dataHistName_Fiducial(ConvolutionShiftMap &input_histmap);
   void assign_CryoVertexTotalRegion_ConvolutedTRUEHistName(
       ConvolutionShiftMap &input_Map);
   void assign_CryoVertex_RecoandTRUEHistName(std::string name,
                                              std::string AddString,
                                              Convolution_hist &input_hist);
   void assign_CryoVertex_RecoandTRUEHistName(CryoVertex type,
                                              std::string AddString,
                                              Convolution_hist &input_hist);
   void assign_CryoVertex_TotalRegion_RecoandTRUEHistName(
       ConvolutionShiftMap &input_histmap);
   void assign_Convolution_CryoRegions_HistName(
       Convolution_CryoRegions &input_histmap, std::string inputname);
   void assign_Convolution_CryoRegions_Hist_MaterialName(
       Convolution_CryoRegions &input_histmap, std::string inputname);
   void assign_Convolution_CryoRegions_HistName(ConvolutionShiftMap &inputMap);
   void assign_Convolution_CryoRegions_Material_XYZR_HistName(
       ConvolutionShiftMap &inputMap);
   void assign_Convolution_CryoRegions_Material_XYZR_HistName_Fiducial(
       ConvolutionShiftMap &inputMap);
   void assign_Convolution_CryoRegions_ConvolutedTRUEName(
       Convolution_CryoRegions &input_histmap, std::string inputname);
   void assign_Convolution_CryoRegions_Material_nonVertexVars_HistName(
       ConvolutionShiftMap &inputMap);
   void assign_Convolution_CryoRegions_Material_nonVertexVars_HistName_Fiducial(
       ConvolutionShiftMap &inputMap);
   void assign_Xaxis_title(Convolution_hist &input);
   void assign_Xaxis_title(ConvolutionShiftMap &input_histmap);

   void init_DataHists_Total_PlaylistCombined(
    Convolution_hist &input, ME_playlist_TFileMAP TFile_Map_Data,
    ME_helium_Playlists StartingPlaylist);
void init_DataHists_Total_PlaylistCombined(
    ConvolutionShiftMap &input, ME_playlist_TFileMAP TFile_Map_Data,
    ME_helium_Playlists StartingPlaylist);

void init_DataHists_Regions_PlaylistCombined(
    Convolution_CryoRegions &input, ME_playlist_TFileMAP TFile_Map_Data,
    ME_helium_Playlists StartingPlaylist);
void init_DataHists_Regions_PlaylistCombined(
    ConvolutionShiftMap &input, ME_playlist_TFileMAP TFile_Map_Data,
    ME_helium_Playlists StartingPlaylist);
void init_DataHists_Regions_PlaylistCombined_Fitonly(
    ConvolutionShiftMap &input, ME_playlist_TFileMAP TFile_Map_Data,
    ME_helium_Playlists StartingPlaylist);
void init_DataHists_Regions_nonVertexVars_PlaylistCombined(
    ConvolutionShiftMap &input, ME_playlist_TFileMAP TFile_Map_Data,
    ME_helium_Playlists StartingPlaylist);
void init_RecoHists_PlaylistCombinedMC(Convolution_hist &input,
                                       ME_playlist_TFileMAP TFile_Map_MC,
                                       ME_helium_Playlists StartingPlaylist);
void init_RecoHists_PlaylistCombinedMC(Convolution_CryoRegions &input,
                                       ME_playlist_TFileMAP TFile_Map_MC,
                                       ME_helium_Playlists StartingPlaylist);
void init_RecoHists_Total_PlaylistCombinedMC(
    ConvolutionShiftMap &input, ME_playlist_TFileMAP TFile_Map_MC,
    ME_helium_Playlists StartingPlaylist);
void init_RecoHists_Regions_PlaylistCombinedMC(
    ConvolutionShiftMap &input, ME_playlist_TFileMAP TFile_Map_MC,
    ME_helium_Playlists StartingPlaylist);

void init_TRUEHists_PlaylistCombinedMC(Convolution_hist &input,
                                       ME_playlist_TFileMAP TFile_Map_MC,
                                       ME_helium_Playlists StartingPlaylist);
void init_TRUEHists_PlaylistCombinedMC(Convolution_CryoRegions &input,
                                       ME_playlist_TFileMAP TFile_Map_MC,
                                       ME_helium_Playlists StartingPlaylist);
void init_TRUEHists_PlaylistCombinedMC(ConvolutionShiftMap &input,
                                       ME_playlist_TFileMAP TFile_Map_MC,
                                       ME_helium_Playlists StartingPlaylist);
void init_TRUEHists_Regions_PlaylistCombinedMC(
    ConvolutionShiftMap &input, ME_playlist_TFileMAP TFile_Map_MC,
    ME_helium_Playlists StartingPlaylist);

void init_TRUEHists_Total_PlaylistCombinedMC(
    ConvolutionShiftMap &input, ME_playlist_TFileMAP TFile_Map_MC,
    ME_helium_Playlists StartingPlaylist);
void init_TRUE_ConvolutionTotalHists_PlaylistCombinedMC(
    ConvolutionShiftMap &input, ME_playlist_TFileMAP TFile_Map_MC,
    ME_helium_Playlists StartingPlaylist, int i, int j, int k);
void init_RECO_ConvolutionTotalHists_PlaylistCombinedMC(
    ConvolutionShiftMap &input, ME_playlist_TFileMAP TFile_Map_MC,
    ME_helium_Playlists StartingPlaylist, int i, int j, int k);
void init_BestFitHist_RECO_ConvolutionTotalHists_PlaylistCombinedMC(
    ConvolutionShiftMap &input, ME_playlist_TFileMAP TFile_Map_MC,
    ME_helium_Playlists StartingPlaylist, BestIndex bestindex_input);

void init_TRUTHConvolutionHist_MCShifted_PlaylistCombined(
    Convolution_hist &input, std::string ExtraString,
    ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist,
    int i, int j, int k);
void init_RECOConvolutionHist_MCShifted_PlaylistCombined(
    Convolution_hist &input, std::string ExtraString,
    ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist,
    int i, int j, int k);
void init_RECOConvolutionHist_MCShifted_PlaylistCombined(
    Convolution_hist &input, std::string ExtraString,
    ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist,
    int i, int j, int k, int m);

void init_TRUTHConvolution_RegionsHists_MCShifted_PlaylistCombined(
    Convolution_CryoRegions &input, std::string ExtraString,
    ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist,
    int i, int j, int k);
void init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(
    ConvolutionShiftMap &input, std::string ExtraString,
    ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist,
    int i, int j, int k);
void init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(
    ConvolutionShiftMap &input, std::string ExtraString,
    ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist,
    int i, int j, int k, int m);
void init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(
    Convolution_CryoRegions &input, std::string ExtraString,
    ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist,
    int i, int j, int k);
void init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(
    Convolution_CryoRegions &input, std::string ExtraString,
    ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist,
    int i, int j, int k, int m);
void init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(
    Convolution_CryoRegions &input, std::string ExtraString,
    ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist,
    Index3 upstream, Index3 barrel, Index3 downstream, Index3 concave);
void init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(
    ConvolutionShiftMap &input, std::string ExtraString,
    ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist,
    BestIndex_Regions indexMap);

void init_RECOConvolution_MaterialHist_MCShifted_PlaylistCombined(
    Convolution_hist &input, std::string ExtraString,
    ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist,
    int i, int j, int k);
void init_RECOConvolution_MaterialHist_MCShifted_PlaylistCombined_Fiducial(
    Convolution_hist &input, std::string ExtraString,
    ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist,
    int i, int j, int k);

void init_RECOConvolution_MaterialHist_MCShifted_PlaylistCombined(
    Convolution_hist &input, std::string ExtraString,
    ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist,
    int i, int j, int k, int m);

void init_TRUTHConvolution_RegionsHists_MCShifted_PlaylistCombined(
    ConvolutionShiftMap &input, std::string ExtraString,
    ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist,
    int i, int j, int k);

   void init_RECOConvolution_Material_Regions_PlaylistCombined(
     Convolution_CryoRegions& input, std::string ExtraString,
     ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist , int i, int j, int k);


   void init_RECOConvolution_Material_Regions_PlaylistCombined(
       Convolution_CryoRegions& input, std::string ExtraString,
        ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist , int i, int j, int k, int m);

    void init_RECOConvolution_Material_Regions_PlaylistCombined(
      ConvolutionShiftMap &input, std::string ExtraString,
      ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist, int i, int j, int k );

    void init_RECOConvolution_Material_Regions_PlaylistCombined(
      ConvolutionShiftMap &input, std::string ExtraString,
       ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist, int i, int j, int k , int m );

  void init_RECOConvolution_Material_Regions_PlaylistCombined_TRUE_vertex(
    ConvolutionShiftMap &input, std::string ExtraString,
     ME_playlist_TFileMAP TFile_Map_MC,
     ME_helium_Playlists StartingPlaylist, int i, int j, int k );

  void init_RECOConvolution_Material_Regions_PlaylistCombined_nonVertexVars(
    ConvolutionShiftMap &input, std::string ExtraString,
     ME_playlist_TFileMAP TFile_Map_MC,
      ME_helium_Playlists StartingPlaylist, int i, int j, int k );

  void init_MaterialConvolutionForPlotting(TFile *inputTFile,
                                           Convolution_hist &input,
                                           std::string inputname,
                                           std::string Region, bool fullorempty,
                                           bool isinit, int rank, int i, int j,
                                           int k, bool isFiducial = false);
  void init_ConvolutionREGIONSForPlotting(TFile *inputTFile,
                                          Convolution_CryoRegions &Regioninput,
                                          std::string inputname, bool fullorempty,
                                          bool isinit, int rank, int i, int j,
                                          int k, bool isFiducial = false);
  void init_ConvolutionREGIONSForVertexPostionsPlotting(
      TFile *inputTFile, ConvolutionShiftMap &input, bool fullorempty,
      bool isinit, int rank, int i, int j, int k, bool isFiducial = false);
  void init_ConvolutionREGIONSForVertexPostionsPlotting_Fiducial(
      TFile *inputTFile, ConvolutionShiftMap &input, bool fullorempty,
      bool isinit, int rank, int i, int j, int k);
  void init_DataConvolutionForPlotting(TFile *inputTFile, Convolution_hist &input,
                                       std::string inputname, std::string Region,
                                       bool fullorempty, bool isinit, int rank,
                                       int i, int j, int k,
                                       bool isFiducial = false);
  void init_Data_Regions_Plotting(TFile *inputTFile,
                                  Convolution_CryoRegions &input,
                                  std::string inputname, bool fullorempty,
                                  bool isinit, int rank, int i, int j, int k,
                                  bool isFiducial = false);
  void init_Data_Regions_Plotting_Fiducial(TFile *inputTFile,
                                           Convolution_CryoRegions &input,
                                           std::string inputname,
                                           bool fullorempty, bool isinit,
                                           int rank, int i, int j, int k);
  void init_Data_Vertex_Plotting(TFile *inputTFile, ConvolutionShiftMap &input,
                                 bool fullorempty, bool isinit, int rank, int i,
                                 int j, int k);
  void init_Data_Vertex_Plotting_Fiducial(TFile *inputTFile,
                                          ConvolutionShiftMap &input,
                                          bool fullorempty, bool isinit, int rank,
                                          int i, int j, int k);
  void init_ConvolutionREGIONSForTRUEVertexPostionsPlotting(
      TFile *inputTFile, ConvolutionShiftMap &input, bool fullorempty,
      bool isinit, int rank, int i, int j, int k);
  void init_ConvolutionREGIONSForTRUEVertexPostionsPlotting_Fiducial(
      TFile *inputTFile, ConvolutionShiftMap &input, bool fullorempty,
      bool isinit, int rank, int i, int j, int k);
  void init_Data_var_Plotting(TFile *inputTFile, ConvolutionShiftMap &input,
                              bool fullorempty, bool isinit, int rank, int i,
                              int j, int k);
  void init_Data_var_Plotting_Fiducial(TFile *inputTFile,
                                       ConvolutionShiftMap &input,
                                       bool fullorempty, bool isinit, int rank,
                                       int i, int j, int k);
  void init_ConvolutionREGIONSForVarsPlotting(TFile *inputTFile,
                                              ConvolutionShiftMap &input,
                                              bool fullorempty, bool isinit,
                                              int rank, int i, int j, int k);
  void init_ConvolutionREGIONSForVarsPlotting_Fiducial(TFile *inputTFile,
                                                       ConvolutionShiftMap &input,
                                                       bool fullorempty,
                                                       bool isinit, int rank,
                                                       int i, int j, int k);
  void init_Clone_data(Convolution_hist &input, Convolution_hist &inputClone);
  void init_Clone_Material(Convolution_hist &input, Convolution_hist &inputClone);
  void init_Clone_Plotting(Convolution_hist &input, Convolution_hist &inputClone);
  void CloneRegions_Material(Convolution_CryoRegions &input,
                             Convolution_CryoRegions &inputClone, int indnew,
                             int indtoclone);
  void CloneRegions(Convolution_CryoRegions &input,
                    Convolution_CryoRegions &inputClone);
  void CloneVertex(ConvolutionShiftMap &input, ConvolutionShiftMap &inputClone);
  void CloneVertex(ConvolutionShiftMap &input, ConvolutionShiftMap &inputClone,
                   int indnew, int indtoclone);
  void CloneTRUEVertex(ConvolutionShiftMap &input,
                       ConvolutionShiftMap &inputClone, int indnew,
                       int indtoclone);
  void CloneVars(ConvolutionShiftMap &input, ConvolutionShiftMap &inputClone);
  void CloneVars(ConvolutionShiftMap &input, ConvolutionShiftMap &inputClone,
                 int indnew, int indtoclone);
  void init_Clone_Material(Convolution_hist &input, Convolution_hist &inputClone,
                           int indnew, int indtoclone);
  void POTscaleMC_ConvoluteTRUTH(Convolution_hist &input, double POTscaler,
                                 int ind);
  void POTscaleMC_ConvoluteTRUTH_Regions(Convolution_CryoRegions &input,
                                         double POTscaler, int ind);
  void POTscaleData_Total(ConvolutionShiftMap &input, double POTscaler);
  void POTscaleData(Convolution_hist &input, double POTscaler);
  void POTscaleMC_Reco(Convolution_hist &input, double POTscaler);
  void POTscaleMC_TRUTH(Convolution_hist &input, double POTscaler);
  void POTscaleData_Regions(Convolution_CryoRegions &input, double POTscaler);
  void POTscaleData_Regions(ConvolutionShiftMap &input, double POTscaler);
  void POTscaleData_Regions_Fitonly(ConvolutionShiftMap &input, double POTscaler);
  void POTscaleData_Regions_nonVertexVars(ConvolutionShiftMap &input,
                                          double POTscaler);
  void POTscale_MCReco_Total(ConvolutionShiftMap &input, double POTscaler);
  void POTscale_MCReco_Regions(ConvolutionShiftMap &input, double POTscaler);
  void POTscale_MCTRUTH_Total(ConvolutionShiftMap &input, double POTscaler);
  void POTscale_MCTRUTH_Regions(Convolution_CryoRegions &input, double POTscaler);
  void POTscale_MCTRUTH_Regions(ConvolutionShiftMap &input, double POTscaler);
  void POTscale_MCReco_Regions(Convolution_CryoRegions &input, double POTscaler);
  void POTscaleMC_TRUTH_Regions(Convolution_CryoRegions &input, double POTscaler);
  void POTscale_MC_Convoluted_Total(ConvolutionShiftMap &input, double POTscaler,
                                    int ind);
  void POTscale_MC_Convoluted_Regions(ConvolutionShiftMap &input,
                                      double POTscaler, int ind);
  void FillDataPOT(double inputPOT, ConvolutionShiftMap &inputMap);
  void FillMCPOT(double inputPOT, ConvolutionShiftMap &inputMap);

  void POTscaleMC_Convolute_Material(Convolution_hist &input, double POTscaler,
                                     int ind);
  void POTscale_MCReco_Material_Regions(Convolution_CryoRegions &input,
                                        double POTscaler, int ind);
  void POTscale_MCReco_Material_Regions(ConvolutionShiftMap &input,
                                        double POTscaler, int ind);
  void POTscale_MCReco_Material_Regions_TRUEvertex(ConvolutionShiftMap &input,
                                                   double POTscaler, int ind);
  void POTscale_MCReco_Material_Regions_nonVertexVar(ConvolutionShiftMap &input,
                                                     double POTscaler, int ind);

  void Subtract_DataHists(Convolution_hist &Subtract_from,
                          Convolution_hist &input);
  void Subtract_DataHists_Regions(ConvolutionShiftMap &Subtract_from,
                                  ConvolutionShiftMap &input);
  void Subtract_DataHists_Regions_TRUEVertex(ConvolutionShiftMap &Subtract_from,
                                             ConvolutionShiftMap &input);
  void Subtract_DataHists_Total(ConvolutionShiftMap &Subtract_from,
                                ConvolutionShiftMap &input);
  void Subtract_DataHists_Regions_Vertex(ConvolutionShiftMap &Subtract_from,
                                         ConvolutionShiftMap &input);
  void Subtract_CryoRegions_DataHists(Convolution_CryoRegions &Subtract_from,
                                      Convolution_CryoRegions &input);

  void Subtract_Convolution_Material_Hists_Regions_Vars(
      ConvolutionShiftMap &Subtract_from, ConvolutionShiftMap &input, int ind);
  void Subtract_TrueHists(Convolution_hist &Subtract_from,
                          Convolution_hist &input);
  void Subtract_CryoRegions_TRUEHists(Convolution_CryoRegions &Subtract_from,
                                      Convolution_CryoRegions &input);
  void Subtract_TRUEHists_Total(ConvolutionShiftMap &Subtract_from,
                                ConvolutionShiftMap &input);
  void Subtract_TRUEHists_Regions(ConvolutionShiftMap &Subtract_from,
                                  ConvolutionShiftMap &input);

  void Subtract_TrueConvoluedHists(Convolution_hist &Subtract_from,
                                   Convolution_hist &input, int ind);
  void Subtract_CryoRegions_TRUEConvolutionHists(
      Convolution_CryoRegions &Subtract_from, Convolution_CryoRegions &input,
      int ind);
  void Subtract_TRUEConvolutionHists_Total(ConvolutionShiftMap &Subtract_from,
                                           ConvolutionShiftMap &input, int ind);
  void Subtract_TRUEConvolutionHists_Regions(ConvolutionShiftMap &Subtract_from,
                                             ConvolutionShiftMap &input, int ind);

  void Subtract_RecoHists(Convolution_hist &Subtract_from,
                          Convolution_hist &input);
  void Subtract_RecoHists_Total(ConvolutionShiftMap &Subtract_from,
                                ConvolutionShiftMap &input);
  void Subtract_RecoHists_Regions(ConvolutionShiftMap &Subtract_from,
                                  ConvolutionShiftMap &input);
  void Subtract_CryoRegions_RecoHists(Convolution_CryoRegions &Subtract_from,
                                      Convolution_CryoRegions &input);
  void Subtract_Material_ConvoluedHists(Convolution_hist &Subtract_from,
                                        Convolution_hist &input, int ind);
  void Subtract_CryoRegions_Material_Hists(Convolution_CryoRegions &Subtract_from,
                                           Convolution_CryoRegions &input,
                                           int ind);
  void Subtract_Convolution_Material_Hists_Regions(
      ConvolutionShiftMap &Subtract_from, ConvolutionShiftMap &input, int ind);
  void Subtract_Convolution_Material_Hists_TrueRegions(
      ConvolutionShiftMap &Subtract_from, ConvolutionShiftMap &input, int ind);

   double CalLogChiSqrt(Convolution_hist InputHistMap,int ind,
     bool isPartial = false, int min_bin = 1, int max_bin = 1);
   double CalChiSqrt(Convolution_hist InputHistMap,int ind,
     bool isPartial = false, int min_bin = 1, int max_bin = 1);
   void Plot_Eventdistrubution(Convolution_hist &histsInput,
      std::string Playlist_name,  std::string histotitle, std::string playlist_status,
     double Ymax, double Convoluted_Mean, double Convoluted_stddev, int ind,
      double &ChiSqrt_Truth_toReco,
      double &ChiSqrt_Truth_toData,
      double &ChiSqrt_Reco_toData);

  void Plot_Eventdistrubution_RECOCol(
    Convolution_hist &histsInput,
    std::string Playlist_name,
    std::string histotitle,
    std::string playlist_status,
    double Ymax, double Convoluted_Mean,
    double Convoluted_stddev,
    double &ChiSqrt_ConvolRECOtoRECO,
    double &ChiSqrt_ConvolRECOtoData,
    double &ChiSqrt_RECO_toData  );


  void Plot_Eventdistrubution_RECOCol(
          Convolution_hist &histsInput,
          std::string Playlist_name,
          std::string histotitle,
          std::string playlist_status,
          double Ymax,
          double Convoluted_MeanF,
          double Convoluted_stddevF,
          double Convoluted_MeanE,
          double Convoluted_stddevE,
          double &ChiSqrt_ConvolRECOtoRECO,
          double &ChiSqrt_ConvolRECOtoData,
          double &ChiSqrt_RECO_toData  );

  void Plot_Eventdistrubution(MnvH1D *hist_Data,
     MnvH1D *hist_RecoMC, MnvH1D *hist_TRUTH_Convolution, MnvH1D *hist_TRUTH,
     std::string Playlist_name,  std::string histotitle, std::string playlist_status,
     std::string xaxislabel, std::string yaxislabel,
     double Ymax, double Convoluted_Mean, double Convoluted_stddev,
     double &ChiSqrt_Truth_toReco,
     double &ChiSqrt_Truth_toData,
     double &ChiSqrt_Reco_toData);

  void Plot_Eventdistrubution_RECOCol(
    MnvH1D *hist_Data,
    MnvH1D *hist_RECOMC,
    MnvH1D *hist_RECO_Convolution,
    MnvH1D *hist_TRUTH,
    std::string Playlist_name,
    std::string histotitle,
    std::string playlist_status,
    std::string xaxislabel,
    std::string yaxislabel,
    double Ymax, double Convoluted_Mean,
    double Convoluted_stddev,
    double &ChiSqrt_ConvolRECOtoRECO,
    double &ChiSqrt_ConvolRECOtoData,
    double &ChiSqrt_RECO_toData);

    void Plot_Eventdistrubution_RECOCol(
      MnvH1D *hist_Data,
      MnvH1D *hist_RECOMC,
      MnvH1D *hist_RECO_Convolution,
      MnvH1D *hist_TRUTH,
      std::string Playlist_name,
      std::string histotitle,
      std::string playlist_status,
      std::string xaxislabel,
      std::string yaxislabel,
      double Ymax,
      double Convoluted_MeanF,
      double Convoluted_stddevF,
      double Convoluted_MeanE,
      double Convoluted_stddevE,
      double &ChiSqrt_ConvolRECOtoRECO,
      double &ChiSqrt_ConvolRECOtoData,
      double &ChiSqrt_RECO_toData);


void Cal_Chisqrt_ConvolutionTruth_ToData_Regions(MnvPlotter *MnvPlotter,
  Convolution_CryoRegions &Hist_input, int ind,
  double &Chi2DataMC_DatatoTRUTH_upstream,
  double &Chi2DataMC_DatatoTRUTH_barrel,
  double &Chi2DataMC_DatatoTRUTH_downstream,
  double &Chi2DataMC_DatatoTRUTH_concave );

void Cal_Chisqrt_ConvolutionTruth_ToData_Regions(MnvPlotter *MnvPlotter,
  Convolution_CryoRegions &Hist_input, int ind,
  double &Chi2DataMC_DatatoTRUTH_upstream,   int &ndf_Chi2DataMC_DatatoTRUTH_upstream,
  double &Chi2DataMC_DatatoTRUTH_barrel,     int &ndf_Chi2DataMC_DatatoTRUTH_barrel,
  double &Chi2DataMC_DatatoTRUTH_downstream, int &ndf_Chi2DataMC_DatatoTRUTH_downstream,
  double &Chi2DataMC_DatatoTRUTH_concave,    int &ndf_Chi2DataMC_DatatoTRUTH_concave);


  std::vector<int> Helium9_colorScheme = {
    TColor::GetColor("#EEFF00"), // neonyellow,0
    TColor::GetColor("#DF00FF"), //'psychedelic Purple1
    TColor::GetColor(43,206,72 ), //green 2
    TColor::GetColor("#87CEEB"),//'skyblue' 3
    TColor::GetColor("#0859C6"), //blue 4
    TColor::GetColor("#654522"), // yellowishbrown,5
    TColor::GetColor("#ffc922"), //'sunset yellow'6
    TColor::GetColor("#FF0800"),//2 candy Apple7
    TColor::GetColor("#90AD1C"),//8
    TColor::GetColor("#BABABA"), //Gray 9
    TColor::GetColor("#00FFFF"),//'aqua' 10
    TColor::GetColor("#F1B6DA"),//pink 11
    TColor::GetColor(kRed),//'Jade' 12
    TColor::GetColor("#FAFAD2"),  // LightGoldenRodYellow 13
    TColor::GetColor("#800000"),  // Maroon 14
    TColor::GetColor("#555555"),  // dark grey 15
    TColor::GetColor(0, 153, 143 ), //turquoise 16
    TColor::GetColor("#654522"), // yellowishbrown, 17
    TColor::GetColor("#8db600"), // yellowgreen, 18
    TColor::GetColor("#D3D3D3"),  //'lightgrey' 19
    TColor::GetColor("#90AD1C"), // 20
    TColor::GetColor("#CCDDAA"), //21
    TColor::GetColor(kMagenta) //22
  };

  std::vector<int> Helium9_NEWcolorScheme = {
    TColor::GetColor("#006400"), //
    TColor::GetColor("#bc8f8f"), //


    TColor::GetColor("#ff0000"), //
    TColor::GetColor("#ffd700"), //

    TColor::GetColor("#00ff00"), //
    TColor::GetColor("#00ffff"), //


    TColor::GetColor("#a020f0"), //
    TColor::GetColor("#1e90ff"), //
    TColor::GetColor("#ff1493") //

  };

  void Plot_regions_noStack(std::string pdf_label, int ind,
       MnvH1D* data_region1, MnvH1D* Helium_region1,
       MnvH1D* Aluminium_region1, MnvH1D* Carbon_region1,
       MnvH1D* Iron_region1, MnvH1D* Lead_region1, MnvH1D* Other_region1,
       MnvH1D* data_region2, MnvH1D* Helium_region2,
        MnvH1D* Aluminium_region2, MnvH1D* Carbon_region2,
       MnvH1D* Iron_region2, MnvH1D* Lead_region2, MnvH1D* Other_region2,
       MnvH1D* data_region3, MnvH1D* Helium_region3,
        MnvH1D* Aluminium_region3, MnvH1D* Carbon_region3,
       MnvH1D* Iron_region3, MnvH1D* Lead_region3, MnvH1D* Other_region3,
       MnvH1D* data_region4, MnvH1D* Helium_region4,
        MnvH1D* Aluminium_region4, MnvH1D* Carbon_region4,
       MnvH1D* Iron_region4, MnvH1D* Lead_region4, MnvH1D* Other_region4,
       std::string Hist_title, std::string xaxislabel, double &ChiSqrt,
       double &ChiSqrtAfter, int FitType, bool UseLogChi, bool doAreaNormalized);

  void  Plot_regions_Material(std::string pdf_label, int ind,
         MnvH1D* data_region1, MnvH1D* Helium_region1,
         MnvH1D* Aluminium_region1,MnvH1D* Carbon_region1,
         MnvH1D* Iron_region1, MnvH1D* Lead_region1, MnvH1D* Other_region1,
         MnvH1D* data_region2, MnvH1D* Helium_region2,
         MnvH1D* Aluminium_region2, MnvH1D* Carbon_region2,
         MnvH1D* Iron_region2, MnvH1D* Lead_region2, MnvH1D* Other_region2,
         MnvH1D* data_region3, MnvH1D* Helium_region3,
         MnvH1D* Aluminium_region3, MnvH1D* Carbon_region3,
         MnvH1D* Iron_region3, MnvH1D* Lead_region3, MnvH1D* Other_region3,
         MnvH1D* data_region4,  MnvH1D* Helium_region4,
          MnvH1D* Aluminium_region4, MnvH1D* Carbon_region4,
         MnvH1D* Iron_region4, MnvH1D* Lead_region4, MnvH1D* Other_region4,
         std::string Hist_title, std::string xaxislabel, double &ChiSqrt,
         double &ChiSqrtAfter, int FitType, bool UseLogChi,
          bool doAreaNormalized, bool applyMaxY , double MaxY);

  void ColorHists(TH1D* data, TH1D* Helium, TH1D* Aluminium, TH1D* Carbon,
                       TH1D* Iron, TH1D* Lead, TH1D* Other);
  void ColorHistsForLines(TH1D* data, TH1D* Helium, TH1D* Aluminium, TH1D* Carbon,
                         TH1D* Iron, TH1D* Lead, TH1D* Other);
  void ColorHists(TH1D* Carbon, TH1D* Iron, TH1D* Lead, TH1D* Other);
  void ColorHistsForLines(TH1D* Carbon, TH1D* Iron, TH1D* Lead, TH1D* Other);
  void ColorData(TH1D* data);
  void Color_HeliumHists(TH1D* Helium_UpsteamCap, TH1D* Helium_Barrel,
                        TH1D* Helium_DownstreamCap,
                        TH1D* Helium_DownstreamConcaveCap);
  void Color_HeliumHistsForLines(TH1D* Helium_UpsteamCap, TH1D* Helium_Barrel,
                                TH1D* Helium_DownstreamCap,
                                TH1D* Helium_DownstreamConcaveCap);
  void Color_AluminiumHists(TH1D* Aluminium_UpsteamCap, TH1D* Aluminium_Barrel,
                           TH1D* Aluminium_DownstreamCap,
                           TH1D* Aluminium_DownstreamConcaveCap);
  void Color_AluminiumHistsForLines(TH1D* Aluminium_UpsteamCap,
                                   TH1D* Aluminium_Barrel,
                                   TH1D* Aluminium_DownstreamCap,
                                   TH1D* Aluminium_DownstreamConcaveCap);
  double calc_ChiSq(TH1D* data, TH1D* Helium, TH1D* Aluminium, TH1D* Carbon,
                   TH1D* Lead, TH1D* Iron, TH1D* Other);
  double calc_LogChiSq(TH1D* data, TH1D* Helium, TH1D* Aluminium, TH1D* Carbon,
                      TH1D* Lead, TH1D* Iron, TH1D* Other);

  double calc_LogChiSq(TH1D* data, TH1D* Helium_upstream,
    TH1D* Helium_barrel, TH1D* Helium_downstream,TH1D* Helium_downstreamconcave, TH1D* Aluminium_upstream,
    TH1D* Aluminium_barrel, TH1D* Aluminium_downstream,TH1D* Aluminium_downstreamconcave,
    TH1D* Carbon, TH1D* Lead, TH1D* Iron, TH1D* Other);
  double calc_ChiSq(TH1D* data, TH1D* Helium_upstream,
    TH1D* Helium_barrel, TH1D* Helium_downstream,TH1D* Helium_downstreamconcave, TH1D* Aluminium_upstream,
    TH1D* Aluminium_barrel, TH1D* Aluminium_downstream,TH1D* Aluminium_downstreamconcave,
    TH1D* Carbon, TH1D* Lead, TH1D* Iron, TH1D* Other);
    void ApplyFitResults(Convolution_hist &hist, double Alwgt);

  void ApplyFitResults_toRegions(Convolution_CryoRegions &hist,
                                 double Alwgt_Upstream, double Alwgt_Barrel,
                                 double Alwgt_Downstream, double Alwgt_Concave);

  void ApplyFitResults_toMaterialVertex(ConvolutionShiftMap &RegionMap,
                                        double Alwgt_Upstream,
                                        double Alwgt_Barrel,
                                        double Alwgt_Downstream,
                                        double Alwgt_Concave);

  void ApplyFitResults_toMaterialTRUEVertex(ConvolutionShiftMap &RegionMap,
                                            double Alwgt_Upstream,
                                            double Alwgt_Barrel,
                                            double Alwgt_Downstream,
                                            double Alwgt_Concave);

  void ApplyFitResults_toMaterialNonVertexVars(ConvolutionShiftMap &RegionMap,
                                               double Alwgt_Upstream,
                                               double Alwgt_Barrel,
                                               double Alwgt_Downstream,
                                               double Alwgt_Concave);

  void Plot_regions(ConvolutionShiftMap inputMap, int ind, int FitType,
                    std::string Hist_title, bool doAreaNormalized,
                    bool applyMaxY);
  double ChiSqrt(
    MnvH1D* data_Region1, MnvH1D* Helium_Region1,
    MnvH1D* Aluminium_Region1, MnvH1D* Carbon_Region1,
    MnvH1D* Iron_Region1, MnvH1D* Lead_Region1, MnvH1D* Other_Region1,

    MnvH1D* data_Region2, MnvH1D* Helium_Region2, MnvH1D* Aluminium_Region2, MnvH1D* Carbon_Region2,
    MnvH1D* Iron_Region2, MnvH1D* Lead_Region2, MnvH1D* Other_Region2,

    MnvH1D* data_Region3, MnvH1D* Helium_Region3, MnvH1D* Aluminium_Region3, MnvH1D* Carbon_Region3,
    MnvH1D* Iron_Region3, MnvH1D* Lead_Region3, MnvH1D* Other_Region3,

    MnvH1D* data_Region4, MnvH1D* Helium_Region4, MnvH1D* Aluminium_Region4,
    MnvH1D* Carbon_Region4,
    MnvH1D* Iron_Region4, MnvH1D* Lead_Region4, MnvH1D* Other_Region4);

   void CalMaterial_ChiSqrt(ConvolutionShiftMap inputMap, int ind,
      double &chisqrt_x, double &chisqrt_y,
      double &chisqrt_z, double &chisqrt_r);

  void WriteHist_toFile(TFile& f, MnvH1D*inputhist, char *name );

  void Write_dataHist_toFile(TFile& f, Convolution_hist inputMap,
                           char* nameinput);

void Write_RecoTrueHists_toFile(TFile& f, Convolution_hist inputMap,
                                char* nameinput);

void Write_Convolution_hist_toFile_index(TFile& f, Convolution_hist inputMap,
                                         char* name_input, int index);

void Write_Convolution_Region_Data_toFile(TFile& f,
                                          Convolution_CryoRegions inputMap,
                                          char* nameinput);

void Write_Convolution_Region_Total_toFile(TFile& f,
                                           Convolution_CryoRegions inputMap,
                                           char* nameinput);

void Write_Convolution_Region_Convolution_hist_toFile_index(
    TFile& f, Convolution_CryoRegions inputMap, char* nameinput, int index);

void Write_init_VertexRegions(TFile& f, ConvolutionShiftMap ConvolutionShiftMap,
                              char* nameinput);

void Write_Fitted_VertexRegions(TFile& f,
                                ConvolutionShiftMap ConvolutionShiftMap,
                                char* nameinput, int index);

void Write_init_TRUEVertexRegions(TFile& f,
                                  ConvolutionShiftMap ConvolutionShiftMap,
                                  char* nameinput);
void Write_init_NonVertexRegions(TFile& f,
                                 ConvolutionShiftMap ConvolutionShiftMap,
                                 char* nameinput);
void Write_fitted_NonVertexRegions(TFile& f,
                                   ConvolutionShiftMap ConvolutionShiftMap,
                                   char* nameinput);

std::string constuctString_forHist(std::string inputname, bool isinit,
                                   bool fullorempty, int rank, int i, int j,
                                   int k, bool isFiducial = false);

  };



#endif
