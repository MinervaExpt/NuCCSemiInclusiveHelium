// File: Cryotankutils.h
// Brief: The header for Cryotankutils.cxx
//  contains cryotank contants and the Functions dealing with the CryoTank
// Author: Christian Nguyen christian2nguyen@ufl.edu
// ========================================================================
#ifndef CRYOTANKUTILS_H
#define CRYOTANKUTILS_H

#include "HeliumCVUniverse.h"
#include "HeliumDefaults.h"
#include "PlotUtils/ChainWrapper.h"
#include <iostream>
#include "TMath.h"
#include <vector>
#include "HeliumCuts.h"

namespace CryoTankConsts {

////////////////////////////
// All units are in mm /////
////////////////////////////

static const double CryoDishedHeadInnerRadius = 1476.0;
static const double CryoDishedHeadInnerRadiusMin = 1271.24977876;
static const double CryoDishedHeadInnerTheta = 0.533012304503;
static const double CryoDishedHeadOuterRadius = 1483.62;
static const double CryoDishedHeadTheta = 0.534952705856;
//////////////////////////////////////////
/// Metal Shielding , surrounding the inner vessel
/////////////////////////////////////////////
static const double CryoHeatShieldAngle = 1.57079632679;
static const double CryoHeatShieldCapThickness = 1.5875;
static const double CryoHeatShieldInnerRadius = 838.0;
static const double CryoHeatShieldLength = 1711.16;
static const double CryoHeatShieldOuterRadius = 839.5875;
static const double CryoHeatShieldThickness = 1.5875;
static const double CryoInnerVesselDishedHeadThickness = 7.62;
//////////////////////////////////////////
/// Inner Vessel
/////////////////////////////////////////////
static const double CryoInnerVesselInnerDiameter = 1500.0;
static const double CryoInnerVesselInnerRadius = 750.0;
static const double CryoInnerVesselLength = 1187.46;
static const double CryoInnerVesselOuterRadius = 756.35;
static const double CryoInnerVesselThickness = 6.35;
static const double CryoInnerVesselTotalLength = 3727.04417087;
static const double CryoInnerVesselZPosInVacuumVessel = -206.0;
//////////////////////////////////////////
/// Vacuum Vessel
/////////////////////////////////////////////
static const double CryoVacuumVesselCylinderLength = 2262.7;
static const double CryoVacuumVesselDishedHeadInnerRadius = 1933.0;
static const double CryoVacuumVesselDishedHeadOuterRadius = 1940.62;
static const double CryoVacuumVesselDishedHeadTheta = 0.490639019349;
static const double CryoVacuumVesselDishedHeadThickness = 7.62;
static const double CryoVacuumVesselEndHemiInnerRadius = 1066.8;
static const double CryoVacuumVesselEndHemiOuterRadius = 1071.1942;
static const double CryoVacuumVesselEndHemiTheta = 1.02969680084;
static const double CryoVacuumVesselEndHemiThickness = 4.3942;
static const double CryoVacuumVesselInnerRadius = 906.526;
static const double CryoVacuumVesselOuterRadius = 914.4;
static const double CryoVacuumVesselThickness = 7.874;

static const double DefaultOffset = 3093.91;
static const double FBackOfCryoInnerVessel = 3687.44726506;
static const double FBackOfCryoVessel = 4225.26;
static const double FrontOfCryoInnerVessel = 2088.37273494;
static const double FrontOfCryoVessel = 1733.6288223;
static const double ZZCryoInnerVesselLength = 1596.96044248;
static const double ZZCryoVacuumVesselBackToCryoInnerVessel = 537.812734936;
static const double ZZCryoVacuumVesselFrontToCryoInnerVessel = 354.743912632;
static const double ZZCryoVacuumVesselLength = 2491.6311777;
/////////////////////////////////////////////////////////////
////Length of Upstream and DownStream Bulges of CyroTank/////
static const double Lenghtofbulge =
    abs(CryoDishedHeadInnerRadiusMin - CryoDishedHeadInnerRadius);
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
// Z position of the DOWNstream
////////////////////////////////////////////////////////////
static const double endbulgepoint =
    FBackOfCryoInnerVessel - CryoDishedHeadInnerRadius;
/////////////////////////////////////////////////////////////
// Z position of the END of upstream Bulge
////////////////////////////////////////////////////////////
static const double Zpostion_EndOfupstreamBulge =
    FrontOfCryoInnerVessel + Lenghtofbulge;
/////////////////////////////////////////////////////////////
// Z position of the START of Downstream Bulge
////////////////////////////////////////////////////////////
static const double Zpostion_StartOfdownstreamendBulge =
    FBackOfCryoInnerVessel - Lenghtofbulge;

static const double inverse_CryoDishedHeadInnerRadius =
    1.0 / CryoDishedHeadInnerRadius;

static const double FrontCryotank =
    CryoDishedHeadInnerRadius + FrontOfCryoInnerVessel;

static const double startofradiusUpstreamVector =
    FrontOfCryoInnerVessel + CryoDishedHeadInnerRadius;

static const double startofradiusDownstreamVector =
    FBackOfCryoInnerVessel - CryoDishedHeadInnerRadius;
///////////////////////////////////////////////////////////////////////////////
static const double Lenght_of_CryotankBarrel =
    Zpostion_StartOfdownstreamendBulge - Zpostion_EndOfupstreamBulge;

static const double Zpostion_MidCryoTank =
    FrontOfCryoInnerVessel + Lenghtofbulge + (Lenght_of_CryotankBarrel / 2.0);
/////////////////////////////////////////////////////////////
// For Smearing Study, Adding/Subtractions distance to different Regions
////////////////////////////////////////////////////////////
const double Sigma_Zextra_Bugles = 250.0;            // [mm]
const double Sigma_Zextra_BugleTO_outside = 450.0;   // [mm]
const double Sigma_Zextra_BugleTO_Center = 150.0;    // [mm]
const double Sigma_Zextra_Barrel = -100.0;           // [mm]
const double Radius_ClindericalBulge_regions = 650;  //[mm]
}
//////////////////////////////////////////////////////////////
/// Fiducial function
/////////////////////////////////////////////////////////////
bool IsInFiducalVolumeFromtheInnerEdge(const HeliumCVUniverse&,
                                       double Min_distance_toShell);
////////////////////////////////////////////////////////////////////////////////
bool IsInFiducalVolumeFromtheInnerEdge_new(const HeliumCVUniverse& univ,
                                           double Min_distance_toShell);
////////////////////////////////////////////////////////////////////////////////
bool IsInFiducalVolumeFromtheInnerEdge(double Rinput, double Zinput,
                                       double Min_distance_toShell);
////////////////////////////////////////////////////////////////////////////////
bool IsInFiducalVolumeFromtheInnerEdgeTRUTH(const HeliumCVUniverse& univ,
                                            double Min_distance_toShell);
////////////////////////////////////////////////////////////////////////////////
bool IsInFiducalVolumeFromtheInnerEdgeTRUTH_new(const HeliumCVUniverse& univ,
                                                double Min_distance_toShell);
////////////////////////////////////////////////////////////////////////////////
bool IsInExtendentedFiducalVolumeFromtheInnerEdge(
    const HeliumCVUniverse& univ, double Min_distance_toShell,
    double AddRegionOutside,
    double Sigma_Zextra = CryoTankConsts::Sigma_Zextra_Bugles);
////////////////////////////////////////////////////////////////////////////////
bool IsInExtendentedFiducalVolumeFromtheInnerEdge(
    const HeliumCVUniverse& univ, double Min_distance_toShell,
    double AddRegionOutside, double AddRegionOutside_center,
    double Sigma_Zextra);
////////////////////////////////////////////////////////////////////////////////
double GetMidPointCryoTank();
////////////////////////////////////////////////////////////////////////////////
bool IsInExtendentedFiducalVolumeFromtheInnerEdge_TRUTH(
    const HeliumCVUniverse& univ, double Min_distance_toShell,
    double AddRegionOutside,
    double Sigma_Zextra = CryoTankConsts::Sigma_Zextra_Bugles);
////////////////////////////////////////////////////////////////////////////////
CryoTank_REGIONS Region_of_CryoTank(double Zinput);
////////////////////////////////////////////////////////////////////////////////
CryoTank_REGIONS FourRegion_of_CryoTank(double Zinput);
////////////////////////////////////////////////////////////////////////////////
CryoTank_REGIONS FourVertexXRegion_of_CryoTank(double Xinput);
////////////////////////////////////////////////////////////////////////////////
CryoTank_REGIONS FourVertexXZRegion_of_CryoTank(double Xinput, double Zinput);
////////////////////////////////////////////////////////////////////////////////
CryoTank_REGIONS Bulge_Regions_of_CryoTank(
    double Zinput, double Sigma_Zextra_fromBulge =
                       CryoTankConsts::Sigma_Zextra_BugleTO_outside,
    double Sigma_Zextra_intoCenter =
        CryoTankConsts::Sigma_Zextra_BugleTO_Center);
////////////////////////////////////////////////////////////////////////////////
CryoTank_REGIONS Barrel_Region_of_CryoTank(
    double Zinput, double Sigma_Zextra = CryoTankConsts::Sigma_Zextra_Barrel);
////////////////////////////////////////////////////////////////////////////////
void SetHist_CRYOTankRR(TGraph& Tg_result, char* xaxislabel, char* yaxislabel);
////////////////////////////////////////////////////////////////////////////////
void SetHist_CRYOTankR(TGraph& Tg_result, char* xaxislabel, char* yaxislabel);
////////////////////////////////////////////////////////////////////////////////
void SetHist_CRYOTankXY(TGraph* Tg_result, char* xaxislabel, char* yaxislabel);
////////////////////////////////////////////////////////////////////////////////
void SetHist_CRYOTank(TGraph& Tg_result, std::string xaxislabel,
                      std::string yaxislabel);
////////////////////////////////////////////////////////////////////////////////
void SetHist_SizeMarker(TGraph& Tg_result);
////////////////////////////////////////////////////////////////////////////////
double CryoTank_MC_gemfunction_output_Y_input_Z(double Z_input, double Theta,
                                                double phi);
////////////////////////////////////////////////////////////////////////////////
double CryoTank_MC_gemfunction_output_X_input_Z(double Z_input, double Theta,
                                                double phi);
////////////////////////////////////////////////////////////////////////////////
double CryoTank_MC_gemfunction_output_R_input_Z(double Z_input);
////////////////////////////////////////////////////////////////////////////////
void CryoTank_FillVector_Y_Z(int Fineness, int Fineness_theta, int Fineness_phi,
                             double ZZ[], double YY[]);
////////////////////////////////////////////////////////////////////////////////
void CryoTank_FillVector_X_Z(int Fineness, int Fineness_theta, int Fineness_phi,
                             double ZZ[], double XX[]);
////////////////////////////////////////////////////////////////////////////////
void CryoTank_FillVector_R_Z(int Fineness, int plottype, double ZZ[],
                             double RR[]);
////////////////////////////////////////////////////////////////////////////////
void Fill_Ecuts_vertexVector(const HeliumCVUniverse& universe,
                             std::vector<ECuts> cuts,
                             EventCount_CryoVertex_Vector& Vector, bool is_mc);
////////////////////////////////////////////////////////////////////////////////
TGraph* Tank_Z_R_or_RR(int plottype);
////////////////////////////////////////////////////////////////////////////////
TGraph* Tank_X_Y();
////////////////////////////////////////////////////////////////////////////////
TGraph* Tank_Z_X_or_Y(bool IfTrueXelseY);
////////////////////////////////////////////////////////////////////////////////
TGraph* Tank_Z_X_or_Y(int IfTrueXelseY);
////////////////////////////////////////////////////////////////////////////////
bool isInHexagon_Helium(const double x, const double y,
                        const double apothem = 850.00 /*mm*/,
                        const double rotation = 0.0);
double DistanceFromUpStreamBulge(double Zinput, double Rinput);
////////////////////////////////////////////////////////////////////////////////
double DistanceFromDownStreamBulge(double Zinput, double Rinput);
////////////////////////////////////////////////////////////////////////////////
bool Cylindrical_CutAboutZero(
    const HeliumCVUniverse& univ,
    double fiducial_radius = CryoTankConsts::Radius_ClindericalBulge_regions);
////////////////////////////////////////////////////////////////////////////////
bool Cylindrical_CutAboutZero(
    double Rinput,
    double fiducial_radius = CryoTankConsts::Radius_ClindericalBulge_regions);
////////////////////////////////////////////////////////////////////////////////
double CenterVolume(double DistancefromEdge);         // mm
////////////////////////////////////////////////////////////////////////////////
double CapVolume(double DistancefromEdge);            // mm
////////////////////////////////////////////////////////////////////////////////
double CryoTankInnerVolume(double DistancefromEdge);  // mm
////////////////////////////////////////////////////////////////////////////////
double CryoTankInnerVolume_metercube(double DistancefromEdge = 50.0);
////////////////////////////////////////////////////////////////////////////////
double Distance_to_innerTank(double Zinput, double Rinput);
////////////////////////////////////////////////////////////////////////////////
double RECO_Distance_to_innerTank(const HeliumCVUniverse& univ);
////////////////////////////////////////////////////////////////////////////////
double RECO_Distance_to_innerTank(double Rinput, double Zinput);
////////////////////////////////////////////////////////////////////////////////
double TRUE_Distance_to_innerTank(const HeliumCVUniverse& univ);
////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
/// End of Fucntion
/////////////////////////////////////////////////////////////

#endif
