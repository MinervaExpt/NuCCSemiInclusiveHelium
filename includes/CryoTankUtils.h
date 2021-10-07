//File: Cryotankutils.h
//Brief: The header for Cryotankutils.cxx
//  contains cryotank contants and the Functions dealing with the CryoTank
//Author: Christian Nguyen christian2nguyen@ufl.edu
// ========================================================================
#ifndef CRYOTANKUTILS_H
#define CRYOTANKUTILS_H

#include "HeliumCVUniverse.h"
#include "PlotUtils/ChainWrapper.h"
#include <iostream>
#include "TMath.h"
#include <vector>
#include "HeliumDefaults.h"
#include "HeliumCuts.h"

namespace CryoTankConsts {

////////////////////////////
// All units are in mm /////
////////////////////////////

const double CryoDishedHeadInnerRadius = 1476.0;
const double CryoDishedHeadInnerRadiusMin = 1271.24977876;
const double CryoDishedHeadInnerTheta = 0.533012304503;
const double CryoDishedHeadOuterRadius = 1483.62;
const double CryoDishedHeadTheta = 0.534952705856;
//////////////////////////////////////////
/// Metal Shielding , surrounding the inner vessel
/////////////////////////////////////////////
const double CryoHeatShieldAngle = 1.57079632679;
const double CryoHeatShieldCapThickness = 1.5875;
const double CryoHeatShieldInnerRadius = 838.0;
const double CryoHeatShieldLength = 1711.16;
const double CryoHeatShieldOuterRadius = 839.5875;
const double CryoHeatShieldThickness = 1.5875;
const double CryoInnerVesselDishedHeadThickness = 7.62;
//////////////////////////////////////////
/// Inner Vessel
/////////////////////////////////////////////
const double CryoInnerVesselInnerDiameter = 1500.0;
const double CryoInnerVesselInnerRadius = 750.0;
const double CryoInnerVesselLength = 1187.46;
const double CryoInnerVesselOuterRadius = 756.35;
const double CryoInnerVesselThickness = 6.35;
const double CryoInnerVesselTotalLength = 3727.04417087;
const double CryoInnerVesselZPosInVacuumVessel = -206.0;
//////////////////////////////////////////
/// Vacuum Vessel
/////////////////////////////////////////////
const double CryoVacuumVesselCylinderLength = 2262.7;
const double CryoVacuumVesselDishedHeadInnerRadius = 1933.0;
const double CryoVacuumVesselDishedHeadOuterRadius = 1940.62;
const double CryoVacuumVesselDishedHeadTheta = 0.490639019349;
const double CryoVacuumVesselDishedHeadThickness = 7.62;
const double CryoVacuumVesselEndHemiInnerRadius = 1066.8;
const double CryoVacuumVesselEndHemiOuterRadius = 1071.1942;
const double CryoVacuumVesselEndHemiTheta = 1.02969680084;
const double CryoVacuumVesselEndHemiThickness = 4.3942;
const double CryoVacuumVesselInnerRadius = 906.526;
const double CryoVacuumVesselOuterRadius = 914.4;
const double CryoVacuumVesselThickness = 7.874;

const double DefaultOffset = 3093.91;
const double FBackOfCryoInnerVessel = 3687.44726506;
const double FBackOfCryoVessel = 4225.26;
const double FrontOfCryoInnerVessel = 2088.37273494;
const double FrontOfCryoVessel = 1733.6288223;
const double ZZCryoInnerVesselLength = 1596.96044248;
const double ZZCryoVacuumVesselBackToCryoInnerVessel = 537.812734936;
const double ZZCryoVacuumVesselFrontToCryoInnerVessel = 354.743912632;
const double ZZCryoVacuumVesselLength = 2491.6311777;
/////////////////////////////////////////////////////////////
////Length of Upstream and DownStream Bulges of CyroTank/////
const double Lenghtofbulge =   abs(CryoDishedHeadInnerRadiusMin - CryoDishedHeadInnerRadius);
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
// Z position of the DOWNstream
////////////////////////////////////////////////////////////
const double endbulgepoint = FBackOfCryoInnerVessel - CryoDishedHeadInnerRadius;
/////////////////////////////////////////////////////////////
// Z position of the END of upstream Bulge
////////////////////////////////////////////////////////////
const double Zpostion_EndOfupstreamBulge = FrontOfCryoInnerVessel + Lenghtofbulge;
/////////////////////////////////////////////////////////////
// Z position of the START of Downstream Bulge
////////////////////////////////////////////////////////////
const double Zpostion_StartOfdownstreamendBulge = FBackOfCryoInnerVessel - Lenghtofbulge;
const double inverse_CryoDishedHeadInnerRadius   = 1.0 / CryoDishedHeadInnerRadius;
const double FrontCryotank = CryoDishedHeadInnerRadius + FrontOfCryoInnerVessel;

const double startofradiusUpstreamVector = FrontOfCryoInnerVessel + CryoDishedHeadInnerRadius;
const double startofradiusDownstreamVector = FBackOfCryoInnerVessel - CryoDishedHeadInnerRadius;
///////////////////////////////////////////////////////////////////////////////
const double Lenght_of_CryotankBarrel = Zpostion_StartOfdownstreamendBulge - Zpostion_EndOfupstreamBulge;
const double Zpostion_MidCryoTank = FrontOfCryoInnerVessel + Lenghtofbulge + (Lenght_of_CryotankBarrel / 2.0);


/////////////////////////////////////////////////////////////
// For Smearing Study, Adding/Subtractions distance to different Regions
////////////////////////////////////////////////////////////

const double Sigma_Zextra_Bugles = 250.0; // [mm]
const double Sigma_Zextra_BugleTO_outside = 450.0; // [mm]
const double Sigma_Zextra_BugleTO_Center = 150.0; // [mm]
const double Sigma_Zextra_Barrel = -100.0; // [mm]
const double Radius_ClindericalBulge_regions = 650; //[mm]
}
//////////////////////////////////////////////////////////////
///Fiducial function
/////////////////////////////////////////////////////////////
bool IsInFiducalVolumeFromtheInnerEdge(const HeliumCVUniverse&, double Min_distance_toShell );
bool IsInFiducalVolumeFromtheInnerEdgeTRUTH(const HeliumCVUniverse& univ, double Min_distance_toShell );
bool IsInExtendentedFiducalVolumeFromtheInnerEdge(const HeliumCVUniverse& univ, double Min_distance_toShell, double AddRegionOutside, double Sigma_Zextra = CryoTankConsts::Sigma_Zextra_Bugles);
bool IsInExtendentedFiducalVolumeFromtheInnerEdge(const HeliumCVUniverse& univ, double Min_distance_toShell, double AddRegionOutside, double AddRegionOutside_center ,  double Sigma_Zextra );

bool IsInExtendentedFiducalVolumeFromtheInnerEdge_TRUTH(const HeliumCVUniverse& univ, double Min_distance_toShell, double AddRegionOutside, double Sigma_Zextra = CryoTankConsts::Sigma_Zextra_Bugles);
CryoTank_REGIONS Region_of_CryoTank(double Zinput);
CryoTank_REGIONS Bulge_Regions_of_CryoTank(double Zinput,double Sigma_Zextra_fromBulge = CryoTankConsts::Sigma_Zextra_BugleTO_outside , double Sigma_Zextra_intoCenter = CryoTankConsts::Sigma_Zextra_BugleTO_Center);
CryoTank_REGIONS Barrel_Region_of_CryoTank(double Zinput, double Sigma_Zextra = CryoTankConsts::Sigma_Zextra_Barrel);
void SetHist_CRYOTankRR(TGraph *Tg_result, char *xaxislabel , char *yaxislabel);
void SetHist_CRYOTankR(TGraph *Tg_result, char *xaxislabel , char *yaxislabel);
void SetHist_CRYOTankXY(TGraph *Tg_result, char *xaxislabel , char *yaxislabel);
void SetHist_SizeMarker(TGraph *Tg_result);
double CryoTank_MC_gemfunction_output_Y_input_Z(double Z_input ,double Theta, double phi);
double CryoTank_MC_gemfunction_output_X_input_Z(double Z_input ,double Theta, double phi);
double CryoTank_MC_gemfunction_output_R_input_Z(double Z_input);
void CryoTank_FillVector_Y_Z(int Fineness, int Fineness_theta ,int Fineness_phi, double ZZ[] ,double YY[] );
void CryoTank_FillVector_X_Z(int Fineness, int Fineness_theta ,int Fineness_phi, double ZZ[] ,double XX[] );
void CryoTank_FillVector_R_Z(int Fineness, int plottype ,  double ZZ[] ,double RR[] );
void Fill_Ecuts_vertexVector(const HeliumCVUniverse& universe ,std::vector<ECuts> cuts, EventCount_CryoVertex_Vector &Vector , bool is_mc);
TGraph  *Tank_Z_R_or_RR(int plottype);
TGraph  *Tank_X_Y();
TGraph  *Tank_Z_X_or_Y(bool IfTrueXelseY);
TGraph  *Tank_Z_X_or_Y(int IfTrueXelseY);
bool isInHexagon_Helium(	const double 	x, const double 	y, const double apothem = 850.00/*mm*/, const double 	rotation = 0.0	 );
double DistanceFromUpStreamBulge(double Zinput , double Rinput);
double DistanceFromDownStreamBulge(double Zinput , double Rinput);
bool Cylindrical_CutAboutZero(const HeliumCVUniverse& univ,double fiducial_radius = CryoTankConsts::Radius_ClindericalBulge_regions);

double CenterVolume(double DistancefromEdge); //mm
double CapVolume(double DistancefromEdge ); //mm
double CryoTankInnerVolume(double DistancefromEdge); //mm
double CryoTankInnerVolume_metercube(double DistancefromEdge = 20.0);
double Distance_to_innerTank(double Zinput, double Rinput );
double RECO_Distance_to_innerTank(const HeliumCVUniverse& univ);
double TRUE_Distance_to_innerTank(const HeliumCVUniverse& univ);
//////////////////////////////////////////////////////////////
///End of Fucntion
/////////////////////////////////////////////////////////////






#endif
