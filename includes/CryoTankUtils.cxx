// File: CryoTankGeometry.cxx
// Brief: The Functions that deal with the CryoTank Geometry
// Author: Christian Nguyen christian2nguyen@ufl.edu
//#ifndef CryoTankGeometry_cxx
//#define CryoTankGeometry_cxx

#include "CryoTankUtils.h"

////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////
double GetMidPointCryoTank() { return CryoTankConsts::Zpostion_MidCryoTank; }
////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////
double Distance_to_innerTank(double Zinput, double Rinput) {
  double delta_to_shell_Sphereical_Cap_upstream = 99999;
  double delta_to_shell_Sphereical_Cap_downstream = 99999;
  double delta_to_shell_Barrel = 99999;
  double Rsmall_upstream = 99999;
  double Rsmall_downstream = 99999;
  double Rsmall_Center = 99999;

  //////////////
  // upstream Cap
  //////////////
  if ((Zinput < CryoTankConsts::Zpostion_EndOfupstreamBulge)) {
    double lenghtupstream_sphereical =
        abs(CryoTankConsts::startofradiusUpstreamVector - Zinput);
    Rsmall_upstream = sqrt(pow(lenghtupstream_sphereical, 2) + pow(Rinput, 2));
    delta_to_shell_Sphereical_Cap_upstream =
        CryoTankConsts::CryoDishedHeadInnerRadius - Rsmall_upstream;
    delta_to_shell_Barrel = CryoTankConsts::CryoInnerVesselInnerRadius - Rinput;

    if (delta_to_shell_Sphereical_Cap_upstream < delta_to_shell_Barrel) {
      return delta_to_shell_Sphereical_Cap_upstream;
    } else {
      return delta_to_shell_Barrel;
    }

  }

  //////////////
  //  Barrel
  //////////////

  else if (
      (CryoTankConsts::Zpostion_EndOfupstreamBulge <= Zinput) &&
      (Zinput <=
       CryoTankConsts::
           Zpostion_StartOfdownstreamendBulge)) {  // delta_to_shell  =
                                                   // (AddRegionOutside +
                                                   // CryoTankConsts::CryoInnerVesselInnerRadius)
                                                   // - Rinput;
    ///////
    // if the vertex is outside of the barrel then the closest postion would be
    // to the Cylindrical outter wall and the caps are not considered
    /////
    ///////////
    /// IF the vertex point is "inside" the Cyrotank's Inner walls then the
    /// distances
    // to the  Barrel's wall and upstream and downstream Caps' are checked and
    // the smallest distance is considered
    //////////
    // else{
    //////////////////////////////////////
    //// Find Distance to barrel wall
    /////////////////////////////////////
    delta_to_shell_Barrel = CryoTankConsts::CryoInnerVesselInnerRadius - Rinput;
    //////////////////////////////////////
    //// Find Distance to upstream Cap
    /////////////////////////////////////
    if (CryoTankConsts::Zpostion_MidCryoTank > Zinput) {
      // MoreUpstream towards the beam
      double lenghtupstream_sphereical =
          abs(CryoTankConsts::startofradiusUpstreamVector - Zinput);
      Rsmall_upstream =
          sqrt(pow(lenghtupstream_sphereical, 2) + pow(Rinput, 2));
      delta_to_shell_Sphereical_Cap_upstream =
          CryoTankConsts::CryoDishedHeadInnerRadius - Rsmall_upstream;
    }
    //////////////////////////////////////
    //// Find Distance to Downstream Cap
    /////////////////////////////////////
    else if (CryoTankConsts::Zpostion_MidCryoTank < Zinput) {
      // more downstream towawds Minerva
      double lenghtdownstream_sphereical =
          abs(Zinput - CryoTankConsts::startofradiusDownstreamVector);
      Rsmall_downstream =
          sqrt(pow(lenghtdownstream_sphereical, 2) + pow(Rinput, 2));
      delta_to_shell_Sphereical_Cap_downstream =
          CryoTankConsts::CryoDishedHeadInnerRadius - Rsmall_downstream;
    }
    //////////////////////////////////////
    ////Pick the shortest distance tank's inner wall to be the return distance
    /////////////////////////////////////
    if (delta_to_shell_Barrel <= delta_to_shell_Sphereical_Cap_upstream &&
        delta_to_shell_Barrel <= delta_to_shell_Sphereical_Cap_downstream) {
      return delta_to_shell_Barrel;
    } else if (delta_to_shell_Sphereical_Cap_upstream <=
                   delta_to_shell_Barrel &&
               delta_to_shell_Sphereical_Cap_upstream <=
                   delta_to_shell_Sphereical_Cap_downstream) {
      return delta_to_shell_Sphereical_Cap_upstream;
    } else {
      return delta_to_shell_Sphereical_Cap_downstream;
    }

  }

  //////////////
  // End Barrel
  //////////////
  else if (Zinput > CryoTankConsts::Zpostion_StartOfdownstreamendBulge) {
    double lenghtdownstream_sphereical =
        abs(Zinput - CryoTankConsts::startofradiusDownstreamVector);
    Rsmall_downstream =
        sqrt(pow(lenghtdownstream_sphereical, 2) + pow(Rinput, 2));
    delta_to_shell_Sphereical_Cap_downstream =
        CryoTankConsts::CryoDishedHeadInnerRadius - Rsmall_downstream;
    delta_to_shell_Barrel = CryoTankConsts::CryoInnerVesselInnerRadius - Rinput;

    if (delta_to_shell_Sphereical_Cap_downstream < delta_to_shell_Barrel) {
      return delta_to_shell_Sphereical_Cap_downstream;
    } else {
      return delta_to_shell_Barrel;
    }

    // return delta_to_shell_Sphereical_Cap_downstream;
  }

  else {
    std::cout << "INside:Return_RECODistance_to_innerTank: a Case failed to "
                 "correctly calculate the distance to the innerVessels edge "
              << std::endl;
    assert(false);
    return -9999;
  }

}  // end of function
//==============================================================================
// Constants from CryoTank
//==============================================================================
bool IsInFiducalVolumeFromtheInnerEdge(const HeliumCVUniverse &univ,
                                       double Min_distance_toShell) {
  double Zinput = univ.GetVertex_z();
  double Rinput = univ.GetVertex_r();  // sqrt( pow(Xinput,2) + pow(Yinput,2));

  double Rsmall, delta_to_shell;

  if ((CryoTankConsts::FrontOfCryoInnerVessel <= Zinput) &&
      (Zinput < CryoTankConsts::Zpostion_EndOfupstreamBulge)) {
    double lenghtupstream =
        abs(CryoTankConsts::startofradiusUpstreamVector - Zinput);
    Rsmall = sqrt(pow(lenghtupstream, 2) + pow(Rinput, 2));
    delta_to_shell = CryoTankConsts::CryoDishedHeadInnerRadius - Rsmall;
  }

  else if ((CryoTankConsts::Zpostion_EndOfupstreamBulge <= Zinput) &&
           (Zinput <= CryoTankConsts::Zpostion_StartOfdownstreamendBulge)) {
    delta_to_shell = CryoTankConsts::CryoInnerVesselInnerRadius - Rinput;
  }

  else if ((Zinput > CryoTankConsts::Zpostion_StartOfdownstreamendBulge) &&
           (CryoTankConsts::FBackOfCryoInnerVessel >= Zinput)) {
    double lenghtdownstream =
        abs(Zinput - CryoTankConsts::startofradiusDownstreamVector);
    Rsmall = sqrt(pow(lenghtdownstream, 2) + pow(Rinput, 2));
    delta_to_shell = CryoTankConsts::CryoDishedHeadInnerRadius - Rsmall;
  }

  else {
    Rsmall = -9999.00;
    return false;
  }

  delta_to_shell =
      std::floor(delta_to_shell * 100) / 100;  // round to 100s place
  if (Min_distance_toShell <= delta_to_shell && delta_to_shell > 0.0) {
    return true;

  }

  else {
    return false;
  }
}
////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////
bool IsInFiducalVolumeFromtheInnerEdge_new(const HeliumCVUniverse &univ,
                                           double Min_distance_toShell) {
  double Zinput = univ.GetVertex_z();
  double Rinput = univ.GetVertex_r();
  double Distance_toEdge = Distance_to_innerTank(Zinput, Rinput);
  if (Distance_toEdge > Min_distance_toShell) {
    return true;
  } else {
    return false;
  }
}  // End of function
////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////
bool IsInFiducalVolumeFromtheInnerEdgeTRUTH_new(const HeliumCVUniverse &univ,
                                                double Min_distance_toShell) {
  double Zinput = univ.GetTRUE_Vertex_z();
  double Rinput = univ.GetTRUE_Vertex_r();
  double Distance_toEdge = Distance_to_innerTank(Zinput, Rinput);
  if (Distance_toEdge > Min_distance_toShell) {
    return true;
  } else {
    return false;
  }
}  // End of function
////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////
bool IsInFiducalVolumeFromtheInnerEdge(double Rinput, double Zinput,
                                       double Min_distance_toShell) {
  double Distance_toEdge = Distance_to_innerTank(Zinput, Rinput);
  if (Distance_toEdge > Min_distance_toShell) {
    return true;
  } else {
    return false;
  }
}  // End of function
////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////
bool IsInFiducalVolumeFromtheInnerEdgeTRUTH(const HeliumCVUniverse &univ,
                                            double Min_distance_toShell) {
  double Xinput = univ.GetTRUE_Vertex_x();
  double Yinput = univ.GetTRUE_Vertex_y();
  double Zinput = univ.GetTRUE_Vertex_z();
  double Rinput = sqrt(pow(Xinput, 2) + pow(Yinput, 2));
  double Rsmall, delta_to_shell;

  if ((CryoTankConsts::FrontOfCryoInnerVessel <= Zinput) &&
      (Zinput < CryoTankConsts::Zpostion_EndOfupstreamBulge)) {
    double lenghtupstream =
        abs(CryoTankConsts::startofradiusUpstreamVector - Zinput);
    Rsmall = sqrt(pow(lenghtupstream, 2) + pow(Rinput, 2));
    delta_to_shell = CryoTankConsts::CryoDishedHeadInnerRadius - Rsmall;
  }

  else if ((CryoTankConsts::Zpostion_EndOfupstreamBulge <= Zinput) &&
           (Zinput <= CryoTankConsts::Zpostion_StartOfdownstreamendBulge)) {
    delta_to_shell = CryoTankConsts::CryoInnerVesselInnerRadius - Rinput;
  }

  else if ((Zinput > CryoTankConsts::Zpostion_StartOfdownstreamendBulge) &&
           (CryoTankConsts::FBackOfCryoInnerVessel >= Zinput)) {
    double lenghtdownstream =
        abs(Zinput - CryoTankConsts::startofradiusDownstreamVector);
    Rsmall = sqrt(pow(lenghtdownstream, 2) + pow(Rinput, 2));
    delta_to_shell = CryoTankConsts::CryoDishedHeadInnerRadius - Rsmall;
  }

  else {
    Rsmall = -9999.00;
    return false;
  }

  delta_to_shell =
      std::floor(delta_to_shell * 100) / 100;  // round to 100s place
  if (Min_distance_toShell <= delta_to_shell && delta_to_shell > 0.0) {
    return true;
  }

  else {
    return false;
  }
}
////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////
bool IsInExtendentedFiducalVolumeFromtheInnerEdge(const HeliumCVUniverse &univ,
                                                  double Min_distance_toShell,
                                                  double AddRegionOutside,
                                                  double Sigma_Zextra) {
  // THis Function Extrents the Fidiucal Volumne  regions are controlled
  // together

  double Zinput = univ.GetVertex_z();
  double Rinput = univ.GetVertex_r();  // sqrt( pow(Xinput,2) + pow(Yinput,2));

  double Rsmall, delta_to_shell;

  if (((CryoTankConsts::FrontOfCryoInnerVessel - Sigma_Zextra) <= Zinput) &&
      (Zinput < CryoTankConsts::Zpostion_EndOfupstreamBulge)) {
    double lenghtupstream =
        abs(CryoTankConsts::startofradiusUpstreamVector - Zinput);
    Rsmall = sqrt(pow(lenghtupstream, 2) + pow(Rinput, 2));
    // delta_to_shell = (AddRegionOutside +
    // CryoTankConsts::CryoDishedHeadInnerRadius ) - Rsmall;
    delta_to_shell = CryoTankConsts::CryoDishedHeadInnerRadius - Rsmall;
  }

  else if ((CryoTankConsts::Zpostion_EndOfupstreamBulge <= Zinput) &&
           (Zinput <= CryoTankConsts::Zpostion_StartOfdownstreamendBulge)) {
    // delta_to_shell  = (AddRegionOutside +
    // CryoTankConsts::CryoInnerVesselInnerRadius) - Rinput;
    delta_to_shell = CryoTankConsts::CryoInnerVesselInnerRadius - Rinput;
  }

  else if ((Zinput > CryoTankConsts::Zpostion_StartOfdownstreamendBulge) &&
           ((CryoTankConsts::FBackOfCryoInnerVessel + Sigma_Zextra) >=
            Zinput)) {
    double lenghtdownstream =
        abs(Zinput - CryoTankConsts::startofradiusDownstreamVector);
    Rsmall = sqrt(pow(lenghtdownstream, 2) + pow(Rinput, 2));
    // delta_to_shell = (AddRegionOutside +
    // CryoTankConsts::CryoDishedHeadInnerRadius) - Rsmall;
    delta_to_shell = CryoTankConsts::CryoDishedHeadInnerRadius - Rsmall;
  }

  else {
    return false;
  }

  delta_to_shell =
      std::floor(delta_to_shell * 100) / 100;  // rounding to  hundredths place

  if (delta_to_shell >= 0.0) {
    return true;
  }  // if positive is inside cryoTank inner shell

  else if (delta_to_shell < 0)  // if negative is outside of cryoTank inner
                                // shell but is it too far away ?
  {
    double outside_distance_to_shell = abs(delta_to_shell);

    if (outside_distance_to_shell < Min_distance_toShell) {
      return true;
    }  // checking if distance to shell is at the min
    else {
      return false;
    }  // if to far fail
  }    // end of outside of cryotank inner surface

}  // end of function
////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////
bool IsInExtendentedFiducalVolumeFromtheInnerEdge(
    const HeliumCVUniverse &univ, double Min_distance_toShell,
    double AddRegionOutside, double AddRegionOutside_center,
    double Sigma_Zextra) {
  // THis Function Extrents the Fidiucal Volumne and can control the  center the
  // region and the Caps seperately

  double Zinput = univ.GetVertex_z();
  double Rinput = univ.GetVertex_r();  // sqrt( pow(Xinput,2) + pow(Yinput,2));

  double Rsmall, delta_to_shell;

  if (((CryoTankConsts::FrontOfCryoInnerVessel - Sigma_Zextra) <= Zinput) &&
      (Zinput < CryoTankConsts::Zpostion_EndOfupstreamBulge)) {
    double lenghtupstream =
        abs(CryoTankConsts::startofradiusUpstreamVector - Zinput);
    Rsmall = sqrt(pow(lenghtupstream, 2) + pow(Rinput, 2));
    // delta_to_shell = (AddRegionOutside +
    // CryoTankConsts::CryoDishedHeadInnerRadius ) - Rsmall;
    delta_to_shell = CryoTankConsts::CryoDishedHeadInnerRadius - Rsmall;
  }

  else if ((CryoTankConsts::Zpostion_EndOfupstreamBulge <= Zinput) &&
           (Zinput <= CryoTankConsts::Zpostion_StartOfdownstreamendBulge)) {
    //  delta_to_shell  = (AddRegionOutside_center +
    //  CryoTankConsts::CryoInnerVesselInnerRadius) - Rinput;
    delta_to_shell = CryoTankConsts::CryoInnerVesselInnerRadius - Rinput;
  }

  else if ((Zinput > CryoTankConsts::Zpostion_StartOfdownstreamendBulge) &&
           ((CryoTankConsts::FBackOfCryoInnerVessel + Sigma_Zextra) >=
            Zinput)) {
    double lenghtdownstream =
        abs(Zinput - CryoTankConsts::startofradiusDownstreamVector);
    Rsmall = sqrt(pow(lenghtdownstream, 2) + pow(Rinput, 2));
    // delta_to_shell = (AddRegionOutside +
    // CryoTankConsts::CryoDishedHeadInnerRadius) - Rsmall;
    delta_to_shell = CryoTankConsts::CryoDishedHeadInnerRadius - Rsmall;
  }

  else {
    return false;
  }

  //  if (Min_distance_toShell <= delta_to_shell && delta_to_shell  > 0.0 )
  //{
  // return true;
  //}
  delta_to_shell =
      std::floor(delta_to_shell * 100) / 100;  // rounding to  hundredths place

  if (delta_to_shell >= 0.0) {
    return true;
  }  // if positive is inside cryoTank inner shell

  else if (delta_to_shell < 0)  // if negative is outside of cryoTank inner
                                // shell but is it to far away ?
  {
    double outside_distance_to_shell = abs(delta_to_shell);

    if (outside_distance_to_shell < Min_distance_toShell) {
      return true;
    } else {
      return false;
    }

  }  // outside of shell
}  // end of function
////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////
bool IsInExtendentedFiducalVolumeFromtheInnerEdge_TRUTH(
    const HeliumCVUniverse &univ, double Min_distance_toShell,
    double AddRegionOutside, double Sigma_Zextra) {
  double Zinput = univ.GetTRUE_Vertex_z();
  double Rinput =
      univ.GetTRUE_Vertex_r();  // sqrt( pow(Xinput,2) + pow(Yinput,2));

  double Rsmall, delta_to_shell;

  if (((CryoTankConsts::FrontOfCryoInnerVessel - Sigma_Zextra) <= Zinput) &&
      (Zinput < CryoTankConsts::Zpostion_EndOfupstreamBulge)) {
    double lenghtupstream =
        abs(CryoTankConsts::startofradiusUpstreamVector - Zinput);
    Rsmall = sqrt(pow(lenghtupstream, 2) + pow(Rinput, 2));
    // delta_to_shell = (AddRegionOutside +
    // CryoTankConsts::CryoDishedHeadInnerRadius ) - Rsmall;
    delta_to_shell = CryoTankConsts::CryoDishedHeadInnerRadius - Rsmall;
  }

  else if ((CryoTankConsts::Zpostion_EndOfupstreamBulge <= Zinput) &&
           (Zinput <= CryoTankConsts::Zpostion_StartOfdownstreamendBulge)) {
    // delta_to_shell  = (AddRegionOutside +
    // CryoTankConsts::CryoInnerVesselInnerRadius) - Rinput;
    delta_to_shell = CryoTankConsts::CryoInnerVesselInnerRadius - Rinput;
  }

  else if ((Zinput > CryoTankConsts::Zpostion_StartOfdownstreamendBulge) &&
           ((CryoTankConsts::FBackOfCryoInnerVessel + Sigma_Zextra) >=
            Zinput)) {
    double lenghtdownstream =
        abs(Zinput - CryoTankConsts::startofradiusDownstreamVector);
    Rsmall = sqrt(pow(lenghtdownstream, 2) + pow(Rinput, 2));
    // delta_to_shell = (AddRegionOutside +
    // CryoTankConsts::CryoDishedHeadInnerRadius) - Rsmall;
    delta_to_shell = CryoTankConsts::CryoDishedHeadInnerRadius - Rsmall;
  }

  else {
    return false;
  }

  delta_to_shell =
      std::floor(delta_to_shell * 100) / 100;  // rounding to  hundredths place

  if (delta_to_shell >= 0.0) {
    return true;
  }  // if positive is inside cryoTank inner shell

  else if (delta_to_shell < 0)  // if negative is outside of cryoTank inner
                                // shell but is it too far away ?
  {
    double outside_distance_to_shell = abs(delta_to_shell);

    if (outside_distance_to_shell < Min_distance_toShell) {
      return true;
    }  // checking if distance to shell is at the min
    else {
      return false;
    }  // if to far fail
  }    // end of outside of cryotank inner surface
}  // End
//////////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////////
bool Cylindrical_CutAboutZero(const HeliumCVUniverse &univ,
                              double fiducial_radius) {
  double Rinput = univ.GetVertex_r();
  double delta_to_shell = fiducial_radius - Rinput;

  if (delta_to_shell < 0.0) {
    return false;
  } else {
    return true;
  }

}  // end of function
////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////
bool Cylindrical_CutAboutZero(double Rinput, double fiducial_radius) {
  double delta_to_shell = fiducial_radius - Rinput;
  if (delta_to_shell < 0.0) {
    return false;
  } else {
    return true;
  }

}  // end of function
////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////
CryoTank_REGIONS Region_of_CryoTank(double Zinput) {
  if (Zinput < CryoTankConsts::Zpostion_EndOfupstreamBulge) {
    return kUpstream_head;
  }

  else if ((CryoTankConsts::Zpostion_EndOfupstreamBulge <= Zinput) &&
           (Zinput <= CryoTankConsts::Zpostion_StartOfdownstreamendBulge)) {
    return kCenter;
  } else if (Zinput > CryoTankConsts::Zpostion_StartOfdownstreamendBulge) {
    return kDownstream_head;
  }

  else {
    std::cout << " Region_of_CryoTank Failed to founded in a region"
              << std::endl;
    assert(false);
  }

}  // end of function
////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////
CryoTank_REGIONS FourRegion_of_CryoTank(double Zinput) {
  if (Zinput <
      2342.66 /*CryoTankConsts::Zpostion_EndOfupstreamBulge*/) { /*old bin
                                                                    changed when
                                                                    may binner
                                                                    */
    return kUpstream_head;
  }

  else if (
      (/*CryoTankConsts::Zpostion_EndOfupstreamBulge*/ 2342.66 <= Zinput) &&
      (Zinput <=
       /*CryoTankConsts::Zpostion_StartOfdownstreamendBulge*/ 3432.46)) {  // 3407.69**old
                                                                           // 3432.46
    return kCenter;
  } else if ((Zinput >
              /*CryoTankConsts::Zpostion_StartOfdownstreamendBulge*/ 3432.46) &&
             (Zinput <= 3688.25)) { /*     * Org3738.25 3728.25 3718.25,
                                       3708.25, 3698.25, 3688.25 changed sep 1
                                       new old ||3712.62 trying one bin over
                                       older bound , changed it when binner
                                       became finer*/
    return kDownstream_head;
  } else if (Zinput > 3688.25) {
    return kDownstream_ConcaveCap;
  } else {
    std::cout << " Region_of_CryoTank Failed to founded in a region"
              << std::endl;
    assert(false);
  }

}  // end of function
////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////
CryoTank_REGIONS FourVertexXRegion_of_CryoTank(double Xinput) {
  //-1200.0,  -1000.0, -800.0, -600.0, |-400.0,  -200.0,  0, 200.0,|  400.0,
  //600.0, 800.0, 1000.0, 1200.0

  if ((-400.0 <= Xinput) && (Xinput <= 200.0)) {
    return kXCenter;
  }

  else if ((-800.0 <= Xinput) && (Xinput < -400.0)) {
    return kXLeftShelf;
  }

  else if ((Xinput > 200.0) && (Xinput <= 600.0)) {
    return kXRightShelf;
  }

  else if (Xinput > 600.0 || Xinput < -800.0) {
    return kXoutsideEdges;
  } else {
    std::cout << " Region_of_CryoTank Failed to founded in a region"
              << std::endl;
    assert(false);
  }
}
////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////
CryoTank_REGIONS FourVertexXZRegion_of_CryoTank(double Xinput, double Zinput) {
  //-1200.0,  -1000.0, -800.0, -600.0, |-400.0,  -200.0,  0, 200.0,|  400.0,
  //600.0, 800.0, 1000.0, 1200.0

  if (Zinput > 3687.0) {
    return kDownstream_ConcaveCap;
  }

  else {
    if ((-400.0 <= Xinput) && (Xinput <= 400.0)) {
      return kXCenter;
    }

    else if (Xinput < -400.0) {
      return kXLeftShelf;
    }

    else if (Xinput > 400.0) {
      return kXRightShelf;
    }

    else {
      std::cout << " Region_of_CryoTank Failed to founded in a region"
                << std::endl;
      assert(false);
    }
  }
}
////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////
CryoTank_REGIONS Bulge_Regions_of_CryoTank(double Zinput,
                                           double Sigma_Zextra_fromBulge,
                                           double Sigma_Zextra_intoCenter) {
  if (((CryoTankConsts::FrontOfCryoInnerVessel - Sigma_Zextra_fromBulge) <
       Zinput) &&
      (Zinput < (CryoTankConsts::Zpostion_EndOfupstreamBulge +
                 Sigma_Zextra_intoCenter))) {
    return kUpstream_head;
  }

  else if ((Zinput > (CryoTankConsts::Zpostion_StartOfdownstreamendBulge -
                      Sigma_Zextra_intoCenter)) &&
           ((CryoTankConsts::FBackOfCryoInnerVessel + Sigma_Zextra_fromBulge) >
            Zinput)) {
    return kDownstream_head;
  }

  else {
    return kOUTSIDE;
  }

}  // end of function
////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////
CryoTank_REGIONS Barrel_Region_of_CryoTank(double Zinput, double Sigma_Zextra) {
  if ((CryoTankConsts::Zpostion_EndOfupstreamBulge - Sigma_Zextra <= Zinput) &&
      (Zinput <=
       CryoTankConsts::Zpostion_StartOfdownstreamendBulge + Sigma_Zextra)) {
    return kCenter;
  }

  else {
    return kOUTSIDE;
  }
}  // end of function
////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////
void SetHist_SizeMarker(TGraph &Tg_result) {
  Tg_result.SetLineWidth(4);
  Tg_result.SetMarkerSize(2);
  Tg_result.SetMarkerStyle(6);
}
////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////
double RECO_Distance_to_innerTank(const HeliumCVUniverse &univ) {
  double Zinput = univ.GetVertex_z();
  double Rinput = univ.GetVertex_r();
  double Distance = Distance_to_innerTank(Zinput, Rinput);
  return Distance;
}
////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////
double RECO_Distance_to_innerTank(double Rinput, double Zinput) {
  double Distance = Distance_to_innerTank(Zinput, Rinput);
  return Distance;
}
////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////
double TRUE_Distance_to_innerTank(const HeliumCVUniverse &univ) {
  double Zinput = univ.GetTRUE_Vertex_z();
  double Rinput = univ.GetTRUE_Vertex_r();
  double Distance = Distance_to_innerTank(Zinput, Rinput);
  return Distance;
}
////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////
void SetHist_CRYOTank(TGraph &Tg_result, std::string xaxislabel,
                      std::string yaxislabel) {
  Tg_result.GetXaxis()->CenterTitle();
  Tg_result.GetYaxis()->CenterTitle();
  Tg_result.GetXaxis()->SetTitle(xaxislabel.c_str());
  Tg_result.GetYaxis()->SetTitle(yaxislabel.c_str());
  Tg_result.GetXaxis()->SetTitleSize(0.038);
  Tg_result.GetYaxis()->SetTitleSize(0.038);
  Tg_result.SetLineColor(2);
  Tg_result.SetLineWidth(4);
  Tg_result.SetMarkerColor(1);
  Tg_result.SetMarkerSize(1);
  Tg_result.SetMarkerStyle(6);
  Tg_result.SetMaximum(1200.0);
  Tg_result.SetMinimum(-1100.0);
  return;
}
////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////
void SetHist_CRYOTankXY(TGraph *Tg_result, char *xaxislabel, char *yaxislabel) {
  Tg_result->GetXaxis()->CenterTitle();
  Tg_result->GetYaxis()->CenterTitle();
  Tg_result->GetXaxis()->SetTitle(xaxislabel);
  Tg_result->GetYaxis()->SetTitle(yaxislabel);
  Tg_result->GetXaxis()->SetTitleSize(0.038);
  Tg_result->GetYaxis()->SetTitleSize(0.038);
  Tg_result->SetLineColor(2);
  Tg_result->SetLineWidth(4);
  Tg_result->SetMarkerColor(1);
  Tg_result->SetMarkerSize(1);
  Tg_result->SetMarkerStyle(6);
  Tg_result->SetMaximum(1200.0);
  Tg_result->SetMinimum(-1100.0);
  return;
}
////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////
void SetHist_CRYOTankR(TGraph &Tg_result, char *xaxislabel, char *yaxislabel) {
  Tg_result.GetXaxis()->CenterTitle();
  Tg_result.GetYaxis()->CenterTitle();
  Tg_result.GetXaxis()->SetTitle(xaxislabel);
  Tg_result.GetYaxis()->SetTitle(yaxislabel);
  Tg_result.GetXaxis()->SetTitleSize(0.038);
  Tg_result.GetYaxis()->SetTitleSize(0.038);
  Tg_result.SetLineColor(2);
  Tg_result.SetLineWidth(4);
  Tg_result.SetMarkerColor(1);
  Tg_result.SetMarkerSize(1);
  Tg_result.SetMarkerStyle(6);
  Tg_result.SetMaximum(1200.0);
  Tg_result.SetMinimum(0);
  return;
}
////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////
void SetHist_CRYOTankRR(TGraph &Tg_result, char *xaxislabel, char *yaxislabel) {
  Tg_result.GetXaxis()->CenterTitle();
  Tg_result.GetYaxis()->CenterTitle();
  Tg_result.GetXaxis()->SetTitle(xaxislabel);
  Tg_result.GetYaxis()->SetTitle(yaxislabel);
  Tg_result.GetXaxis()->SetTitleSize(0.038);
  Tg_result.GetYaxis()->SetTitleSize(0.038);
  Tg_result.SetLineColor(2);
  Tg_result.SetLineWidth(4);
  Tg_result.SetMarkerColor(1);
  Tg_result.SetMarkerSize(1);
  Tg_result.SetMarkerStyle(6);
  Tg_result.SetMaximum(1250000.0);
  Tg_result.SetMinimum(0);
  return;
}
////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////
double DistanceFromUpStreamBulge(double Zinput, double Rinput) {
  double Rsmall, delta_to_shell;

  double lenghtupstream =
      abs(CryoTankConsts::startofradiusUpstreamVector - Zinput);
  Rsmall = sqrt(pow(lenghtupstream, 2) + pow(Rinput, 2));
  delta_to_shell = CryoTankConsts::CryoDishedHeadInnerRadius - Rsmall;
  return delta_to_shell;
}
////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////
double DistanceFromDownStreamBulge(double Zinput, double Rinput) {
  double Rsmall, delta_to_shell;

  double lenghtdownstream =
      abs(Zinput - CryoTankConsts::startofradiusDownstreamVector);
  Rsmall = sqrt(pow(lenghtdownstream, 2) + pow(Rinput, 2));
  delta_to_shell = CryoTankConsts::CryoDishedHeadInnerRadius - Rsmall;
  return delta_to_shell;
}
////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////
double CryoTank_MC_gemfunction_output_R_input_Z(double Z_input) {
  double R_output;

  // double FBackOfCryoInnerVessel=  CryoTankConsts::FBackOfCryoInnerVessel;

  if ((CryoTankConsts::FrontOfCryoInnerVessel <= Z_input) &&
      (CryoTankConsts::Zpostion_EndOfupstreamBulge > Z_input)) {
    R_output = CryoTankConsts::CryoDishedHeadInnerRadius *
               sin(acos(CryoTankConsts::inverse_CryoDishedHeadInnerRadius *
                        (CryoTankConsts::FrontCryotank - Z_input)));
    return R_output;
  } else if ((CryoTankConsts::Zpostion_EndOfupstreamBulge <= Z_input) &&
             (Z_input <= CryoTankConsts::Zpostion_StartOfdownstreamendBulge)) {
    R_output = CryoTankConsts::CryoInnerVesselInnerRadius;
    return R_output;
  }

  else if ((Z_input > CryoTankConsts::Zpostion_StartOfdownstreamendBulge) &&
           (Z_input <= CryoTankConsts::FBackOfCryoInnerVessel)) {
    R_output = CryoTankConsts::CryoDishedHeadInnerRadius *
               sin(acos(CryoTankConsts::inverse_CryoDishedHeadInnerRadius *
                        (Z_input - CryoTankConsts::endbulgepoint)));
    return R_output;
  } else {
    R_output = 0.0;
    return R_output;
  }

}  // end of function
////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////
double CryoTank_MC_gemfunction_output_X_input_Z(double Z_input, double Theta,
                                                double phi) {
  // phi 0<phi<pi
  double R_output;

  if ((CryoTankConsts::FrontOfCryoInnerVessel <= Z_input) &&
      (CryoTankConsts::Zpostion_EndOfupstreamBulge > Z_input)) {
    R_output = CryoTankConsts::CryoDishedHeadInnerRadius *
               sin(acos(CryoTankConsts::inverse_CryoDishedHeadInnerRadius *
                        (CryoTankConsts::FrontCryotank - Z_input)));
    return R_output * sin(phi) * cos(Theta);
  } else if ((CryoTankConsts::Zpostion_EndOfupstreamBulge <= Z_input) &&
             (Z_input <= CryoTankConsts::Zpostion_StartOfdownstreamendBulge)) {
    R_output = CryoTankConsts::CryoInnerVesselInnerRadius;
    return R_output * cos(Theta);
  }

  else if ((Z_input > CryoTankConsts::Zpostion_StartOfdownstreamendBulge) &&
           (Z_input <= CryoTankConsts::FBackOfCryoInnerVessel)) {
    R_output = CryoTankConsts::CryoDishedHeadInnerRadius *
               sin(acos(CryoTankConsts::inverse_CryoDishedHeadInnerRadius *
                        (Z_input - CryoTankConsts::endbulgepoint)));
    return R_output * sin(phi) * cos(Theta);
  }

  else {
    R_output = 0.0;
    return R_output;
  }

}  // end of function
////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////
double CryoTank_MC_gemfunction_output_Y_input_Z(double Z_input, double Theta,
                                                double phi) {
  double R_output;

  if ((CryoTankConsts::FrontOfCryoInnerVessel <= Z_input) &&
      (CryoTankConsts::Zpostion_EndOfupstreamBulge > Z_input)) {
    R_output = CryoTankConsts::CryoDishedHeadInnerRadius *
               sin(acos(CryoTankConsts::inverse_CryoDishedHeadInnerRadius *
                        (CryoTankConsts::FrontCryotank - Z_input)));
    return R_output * sin(phi) * sin(Theta);
  } else if ((CryoTankConsts::Zpostion_EndOfupstreamBulge <= Z_input) &&
             (Z_input <= CryoTankConsts::Zpostion_StartOfdownstreamendBulge)) {
    R_output = CryoTankConsts::CryoInnerVesselInnerRadius;
    return R_output * sin(Theta);
  }

  else if ((Z_input > CryoTankConsts::Zpostion_StartOfdownstreamendBulge) &&
           (Z_input <= CryoTankConsts::FBackOfCryoInnerVessel)) {
    R_output = CryoTankConsts::CryoDishedHeadInnerRadius *
               sin(acos(CryoTankConsts::inverse_CryoDishedHeadInnerRadius *
                        (Z_input - CryoTankConsts::endbulgepoint)));
    return R_output * sin(phi) * sin(Theta);
  }

  else {
    R_output = 0.0;
    return R_output;
  }
}  // end of function
////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////
void CryoTank_FillVector_Y_Z(int Fineness, int Fineness_theta, int Fineness_phi,
                             double ZZ[], double YY[]) {
  double Start = CryoTankConsts::FBackOfCryoInnerVessel;
  double End = CryoTankConsts::FBackOfCryoInnerVessel;
  std::vector<double> R_vector, Z_vector;
  const int Nbin = Fineness;
  const int Nbin_theta = Fineness_theta;
  const int Nbin_phi = Fineness_phi;

  // char tempName[1024];
  double Zstep = (End - Start) / Nbin;
  double Z = Start;
  double THETA = 0.0;
  double PHI = 0.0;
  double R = 0;
  double Pi = TMath::Pi();
  double Theta_step = (2 * Pi) / Nbin_theta;
  double phi_step = (Pi) / Nbin_phi;

  for (int i = 0; i < Nbin; i++) {
    PHI = 0.0;
    for (int j = 0; j < Nbin_phi; j++) {
      THETA = 0.0;
      for (int k = 0; k < Nbin_theta; k++) {
        // std::cout<<"(z,theta,phi) = ("<<Z<<" , "<<THETA<<" ,
        // "<<PHI<<")"<<std::endl;
        R = CryoTank_MC_gemfunction_output_Y_input_Z(Z, THETA, PHI);
        R_vector.push_back(R);
        Z_vector.push_back(Z);
        //  std::cout<<"testing of function bulge (Z,X) = (" << Z<< " , "<< R <<
        //  " )" <<std::endl;
        THETA = THETA + Theta_step;
      }
      PHI = PHI + phi_step;
    }

    Z = Z + Zstep;
  }

  const int size = R_vector.size();

  for (int j = 0; j < size; j++) {
    YY[j] = R_vector[j];
    ZZ[j] = Z_vector[j];
  }
  return;
}  // end of function
////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////
void CryoTank_FillVector_X_Z(int Fineness, int Fineness_theta, int Fineness_phi,
                             double ZZ[], double XX[]) {
  double Start = CryoTankConsts::FBackOfCryoInnerVessel;
  double End = CryoTankConsts::FBackOfCryoInnerVessel;
  std::vector<double> R_vector, Z_vector;
  const int Nbin = Fineness;
  const int Nbin_theta = Fineness_theta;
  const int Nbin_phi = Fineness_phi;

  // char tempName[1024];
  double Zstep = (End - Start) / Nbin;
  double Z = Start;
  double THETA = 0.0;
  double PHI = 0.0;
  double R = 0;
  double Pi = TMath::Pi();
  double Theta_step = (2 * Pi) / Nbin_theta;
  double phi_step = (Pi) / Nbin_phi;

  for (int i = 0; i < Nbin; i++) {
    PHI = 0.0;
    for (int j = 0; j < Nbin_phi; j++) {
      THETA = 0.0;
      for (int k = 0; k < Nbin_theta; k++) {
        // std::cout<<"(z,theta,phi) = ("<<Z<<" , "<<THETA<<" ,
        // "<<PHI<<")"<<std::endl;
        R = CryoTank_MC_gemfunction_output_X_input_Z(Z, THETA, PHI);
        R_vector.push_back(R);
        Z_vector.push_back(Z);
        //  std::cout<<"testing of function bulge (Z,X) = (" << Z<< " , "<< R <<
        //  " )" <<std::endl;
        THETA = THETA + Theta_step;
      }
      PHI = PHI + phi_step;
    }

    Z = Z + Zstep;
  }

  const int size = R_vector.size();

  for (int j = 0; j < size; j++) {
    XX[j] = R_vector[j];
    ZZ[j] = Z_vector[j];
  }
return;
}  // end of function
////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////
void CryoTank_FillVector_R_Z(int Fineness, int plottype, double ZZ[],
                             double RR[]) {
  double Start = CryoTankConsts::FBackOfCryoInnerVessel;
  double End = CryoTankConsts::FBackOfCryoInnerVessel;
  std::vector<double> R_vector, Z_vector;
  const int Nbin = Fineness;

  double Zstep = (End - Start) / Nbin;
  double Z = Start;
  double R = 0;

  for (int i = 0; i < Nbin; i++) {
    if (plottype == 0) R = CryoTank_MC_gemfunction_output_R_input_Z(Z);
    if (plottype == 1) R = pow(CryoTank_MC_gemfunction_output_R_input_Z(Z), 2);

    RR[i] = R;
    ZZ[i] = Z;
    // std::cout<<"testing of function bulge (Z,R) = (" << Z<< " , "<< R << " )"
    // <<std::endl;
    Z = Z + Zstep;
  }
  return;
}  // end of function
////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////
void Fill_Ecuts_vertexVector(const HeliumCVUniverse &universe,
                             std::vector<ECuts> cuts,
                             EventCount_CryoVertex_Vector &Vector, bool is_mc) {
  double Xinput = universe.GetVertex_x();
  double Yinput = universe.GetVertex_y();
  double Zinput = universe.GetVertex_z();

  bool pass = true;

  for (auto c : cuts) {
    pass = pass && PassesCut(universe, c, is_mc);
    if (pass == true) {
      Vector[c].push_back({Xinput, Yinput, Zinput});
    } else {
      continue;
    }

  }  // endl;
}
////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////
TGraph *Tank_Z_R_or_RR(int plottype) {
  // double R_final = 750;
  double Start = 2089.37273494;
  double End = 3687.44726506;
  const int Nbin = 400;
  std::vector<double> R_vector;
  std::vector<double> Z_vector;
  // char tempName[1024];
  double Zstep = (End - Start) / Nbin;
  double Z = Start;
  double R = 0;

  for (int i = 0; i < Nbin; i++) {
    if (plottype == 0) R = CryoTank_MC_gemfunction_output_R_input_Z(Z);
    if (plottype == 1) R = pow(CryoTank_MC_gemfunction_output_R_input_Z(Z), 2);
    R_vector.push_back(R);
    Z_vector.push_back(Z);
    Z = Z + Zstep;
  }
  const int size = R_vector.size();
  // std::cout<<"Size = "<< size<<std::endl;
  double ZZ[size];
  double XX[size];

  for (int j = 0; j < size; j++) {
    XX[j] = R_vector[j];
    ZZ[j] = Z_vector[j];
  }
  TGraph *Tg_result = new TGraph(size, ZZ, XX);

  Tg_result->GetXaxis()->CenterTitle();
  Tg_result->GetYaxis()->CenterTitle();
  Tg_result->GetXaxis()->SetTitle("Z [mm]");
  if (plottype == 0) {
    Tg_result->GetYaxis()->SetTitle("R [mm]");
  } else {
    Tg_result->GetYaxis()->SetTitle("R^{2} [mm]");
  }
  Tg_result->GetXaxis()->SetTitleSize(0.038);
  Tg_result->GetYaxis()->SetTitleSize(0.038);
  Tg_result->SetLineColor(2);
  Tg_result->SetLineWidth(4);
  Tg_result->SetMarkerColor(1);
  Tg_result->SetMarkerSize(1);
  Tg_result->SetMarkerStyle(20);
  Tg_result->SetMaximum(1100.0);
  Tg_result->SetMinimum(-1100.0);

  return Tg_result;
}  // end of function
///////////////////////////////////////
//
////////////////////////////////////////
TGraph *Tank_X_Y() {
  double R_final = 750;
  const int Nbin = 400;

  // char tempName[1024];
  double x[Nbin], y[Nbin];
  double step = 2 * acos(-1.0) / Nbin;
  double theta = 0;

  for (int i = 0; i < Nbin; i++) {
    x[i] = R_final * cos(theta);
    y[i] = R_final * sin(theta);
    // std::cout<<"testing of function bulge (Z,R) = (" << Z<< " , "<< R << " )"
    // <<std::endl;
    theta = theta + step;
  }

  TGraph *Tg_result = new TGraph(Nbin, x, y);

  return Tg_result;
}  // end function
///////////////////////////////////////
//
////////////////////////////////////////
TGraph *Tank_Z_X_or_Y(bool IfTrueXelseY) {
  double Start = 2089.37273494;
  // double End = 3687.44726506;
  double End = 3688.;
  const int Nbin = 75;
  const int Nbin_theta = 20;
  const int Nbin_phi = 20;
  std::vector<double> R_vector;
  std::vector<double> Z_vector;
  double Zstep = (End - Start) / Nbin;
  double Z = Start;
  double THETA = 0.0;
  double PHI = 0.0;
  double R = 0;
  double Pi = TMath::Pi();
  double Theta_step = (2 * Pi) / Nbin_theta;
  double phi_step = (Pi) / Nbin_phi;

  for (int i = 0; i <= Nbin; i++) {
    PHI = 0.0;
    for (int j = 0; j <= Nbin_phi; j++) {
      THETA = 0.0;
      for (int k = 0; k < Nbin_theta; k++) {
        // std::cout<<"(z,theta,phi) = ("<<Z<<" , "<<THETA<<" ,
        // "<<PHI<<")"<<std::endl;
        if (IfTrueXelseY == true) {
          R = CryoTank_MC_gemfunction_output_X_input_Z(Z, THETA, PHI);
        } else if (IfTrueXelseY == false) {
          R = CryoTank_MC_gemfunction_output_Y_input_Z(Z, THETA, PHI);
        }
        R_vector.push_back(R);
        Z_vector.push_back(Z);
        //  std::cout<<"testing of function bulge (Z,X) = (" << Z<< " , "<< R <<
        //  " )" <<std::endl;
        THETA = THETA + Theta_step;
      }

      PHI = PHI + phi_step;
    }

    Z = Z + Zstep;
  }

  const int size = R_vector.size();
  // std::cout<<"Size = "<< size<<std::endl;
  double ZZ[size];
  double XX[size];

  for (int j = 0; j < size; j++) {
    XX[j] = R_vector[j];
    ZZ[j] = Z_vector[j];
  }
  TGraph *Tg_result = new TGraph(size, ZZ, XX);

  Tg_result->GetXaxis()->CenterTitle();
  Tg_result->GetYaxis()->CenterTitle();
  Tg_result->GetXaxis()->SetTitle("Z [mm]");
  if (IfTrueXelseY == true) {
    Tg_result->GetYaxis()->SetTitle("X [mm]");
  } else {
    Tg_result->GetYaxis()->SetTitle("Y [mm]");
  }
  Tg_result->GetXaxis()->SetTitleSize(0.038);
  Tg_result->GetYaxis()->SetTitleSize(0.038);
  Tg_result->SetLineColor(2);
  Tg_result->SetLineWidth(4);
  Tg_result->SetMarkerColor(1);
  Tg_result->SetMarkerSize(1);
  Tg_result->SetMarkerStyle(20);
  Tg_result->SetMaximum(1100.0);
  Tg_result->SetMinimum(-1100.0);

  return Tg_result;
}  // end of function
////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////
TGraph *Tank_Z_X_or_Y(int IfTrueXelseY) {
  bool bool_input;
  if (IfTrueXelseY == 0) {
    bool_input = true;
  } else if (IfTrueXelseY == 1) {
    bool_input = false;
  }
  TGraph *Tg_result = Tank_Z_X_or_Y(bool_input);
  return Tg_result;
}
////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////
double CenterVolume(double DistancefromEdge) {
  double radius =
      (CryoTankConsts::CryoInnerVesselInnerRadius - DistancefromEdge);
  double Volume =
      TMath::Pi() * radius * radius * CryoTankConsts::Lenght_of_CryotankBarrel;
  return Volume;
}
////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////
double CapVolume(double DistancefromEdge) {
  double h = CryoTankConsts::Lenghtofbulge - DistancefromEdge;
  double a = CryoTankConsts::CryoInnerVesselInnerRadius - DistancefromEdge;

  double volume = (TMath::Pi() / 6.0) * h * (3 * a * a + h * h);
  return volume;
}
////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////
double CryoTankInnerVolume(double DistancefromEdge) {
  double volume =
      CenterVolume(DistancefromEdge) + 2 * CapVolume(DistancefromEdge);
  return volume;
}
////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////
double CryoTankInnerVolume_metercube(double DistancefromEdge) {
  double volume = CryoTankInnerVolume(DistancefromEdge) * pow(10, -9);
  return volume;
}
////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////
bool isInHexagon_Helium(const double x, const double y, const double apothem,
                        const double rotation) {
  // derotate x,y to x-prime and y-prime so we can compare to hexagon with
  // rotation = 0
  double xp = x * cos(-rotation) + y * sin(-rotation);
  double yp = -x * sin(-rotation) + y * cos(-rotation);

  // Hexagon is symmetric about its x and y now, so use positive xp and yp
  xp = fabs(xp);
  yp = fabs(yp);

  double lenOfSide = apothem * (2 / sqrt(3));
  double slope = (lenOfSide / 2.0) / apothem;

  if ((xp * xp + yp * yp) < apothem * apothem)
    return true;
  else if (xp <= apothem && yp * yp < lenOfSide / 2.0)
    return true;
  else if (xp <= apothem && yp < lenOfSide - xp * slope)
    return true;

  return false;
}
////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////
