// File: CrossSection_Normalization.h
// Brief: The header for Helium_Vertex_XYZ_Smearing_LateralSystematics.cxx
//  contains functions for Systematic helium Vertex Error
// Author: Christian Nguyen christian2nguyen@ufl.edu
// ========================================================================

#ifndef HELIUM_VERTEX_XYZ_SMEARING_LATERALSYSTEMATICS_CXX
#define HELIUM_VERTEX_XYZ_SMEARING_LATERALSYSTEMATICS_CXX

// class to vary the Helium Smearing
#include "Helium_Vertex_XYZ_Smearing_LateralSystematics.h"
#include <iostream>

template <class T>
std::vector<T*> GetHELIUMVertex_XYZ_SmearingShiftSystematics(
    typename T::config_t chain, ME_helium_Status CryoTankStatus) {
  double m_Uncertainty_X = CryoTankStatus == kFULL
                               ? Helium_ShiftsXYZ::Uncertainty_X_FULL
                               : Helium_ShiftsXYZ::Uncertainty_X_EMPTY;
  double m_Uncertainty_Y = CryoTankStatus == kFULL
                               ? Helium_ShiftsXYZ::Uncertainty_Y_FULL
                               : Helium_ShiftsXYZ::Uncertainty_Y_EMPTY;
  double m_Uncertainty_Z = CryoTankStatus == kFULL
                               ? Helium_ShiftsXYZ::Uncertainty_Z_FULL
                               : Helium_ShiftsXYZ::Uncertainty_Z_EMPTY;

  std::vector<T*> ret;
  std::string Cryotank_status_string = GetPlaylistStatusString(CryoTankStatus);
  std::cout << " CryoTank Status : " << Cryotank_status_string << std::endl;
  std::cout << "Vertex Helium Smearing for a shifts in 6 universe :: "
               "GetHELIUMVertexSmearingShiftSystematics"
            << std::endl;
  std::cout << "(-/+)(X Uncertainty ) =  (" << m_Uncertainty_X << ") [mm]"
            << std::endl;
  std::cout << "(-/+)(Y Uncertainty ) =  (" << m_Uncertainty_Y << ") [mm]"
            << std::endl;
  std::cout << "(-/+)(Z Uncertainty ) =  (" << m_Uncertainty_Z << ") [mm]"
            << std::endl;

  ret.push_back(
      new HeliumVertexSmearing_X_ShiftUniverse<T>(chain, -1., m_Uncertainty_X));
  ret.push_back(
      new HeliumVertexSmearing_X_ShiftUniverse<T>(chain, 1., m_Uncertainty_X));
  ret.push_back(
      new HeliumVertexSmearing_Y_ShiftUniverse<T>(chain, -1., m_Uncertainty_Y));
  ret.push_back(
      new HeliumVertexSmearing_Y_ShiftUniverse<T>(chain, 1., m_Uncertainty_Y));
  ret.push_back(
      new HeliumVertexSmearing_Z_ShiftUniverse<T>(chain, -1., m_Uncertainty_Z));
  ret.push_back(
      new HeliumVertexSmearing_Z_ShiftUniverse<T>(chain, 1., m_Uncertainty_Z));

  return ret;
}

template <class T>
std::map<std::string, std::vector<T*> >
GetHELIUMVertex_XYZ_SmearingShiftSystematicsMap(
    typename T::config_t chain, ME_helium_Status CryoTankStatus) {
  std::map<std::string, std::vector<T*> > ret;

  double m_Uncertainty_X = CryoTankStatus == kFULL
                               ? Helium_ShiftsXYZ::Uncertainty_X_FULL
                               : Helium_ShiftsXYZ::Uncertainty_X_EMPTY;
  double m_Uncertainty_Y = CryoTankStatus == kFULL
                               ? Helium_ShiftsXYZ::Uncertainty_Y_FULL
                               : Helium_ShiftsXYZ::Uncertainty_Y_EMPTY;
  double m_Uncertainty_Z = CryoTankStatus == kFULL
                               ? Helium_ShiftsXYZ::Uncertainty_Z_FULL
                               : Helium_ShiftsXYZ::Uncertainty_Z_EMPTY;

  std::string Cryotank_status_string = GetPlaylistStatusString(CryoTankStatus);
  std::cout << " CryoTank Status : " << Cryotank_status_string << std::endl;
  std::cout << "Vertex Helium Smearing for a shifts in 6 universe: "
               "GetHELIUMVertexSmearingShiftSystematicsMap"
            << std::endl;
  std::cout << "(-/+)(X Uncertainty ) =  (" << m_Uncertainty_X << ") [mm]"
            << std::endl;
  std::cout << "(-/+)(Y Uncertainty ) =  (" << m_Uncertainty_Y << ") [mm]"
            << std::endl;
  std::cout << "(-/+)(Z Uncertainty ) =  (" << m_Uncertainty_Z << ") [mm]"
            << std::endl;

  ret["VertexSmearingX"].push_back(
      new HeliumVertexSmearing_X_ShiftUniverse<T>(chain, -1., m_Uncertainty_X));
  ret["VertexSmearingX"].push_back(
      new HeliumVertexSmearing_X_ShiftUniverse<T>(chain, 1., m_Uncertainty_X));
  ret["VertexSmearingY"].push_back(
      new HeliumVertexSmearing_Y_ShiftUniverse<T>(chain, -1., m_Uncertainty_Y));
  ret["VertexSmearingY"].push_back(
      new HeliumVertexSmearing_Y_ShiftUniverse<T>(chain, 1., m_Uncertainty_Y));
  ret["VertexSmearingZ"].push_back(
      new HeliumVertexSmearing_Z_ShiftUniverse<T>(chain, -1., m_Uncertainty_Z));
  ret["VertexSmearingZ"].push_back(
      new HeliumVertexSmearing_Z_ShiftUniverse<T>(chain, 1., m_Uncertainty_Z));
  return ret;
}

// Class Definitions
// Constructor
template <typename T>
HeliumVertexSmearing_X_ShiftUniverse<T>::HeliumVertexSmearing_X_ShiftUniverse(
    typename T::config_t chw, double nsigma, double Uncertainty_X)
    : T(chw, nsigma), m_Uncertainty_X(Uncertainty_X) {}

template <typename T>
HeliumVertexSmearing_Y_ShiftUniverse<T>::HeliumVertexSmearing_Y_ShiftUniverse(
    typename T::config_t chw, double nsigma, double Uncertainty_Y)
    : T(chw, nsigma), m_Uncertainty_Y(Uncertainty_Y) {}

template <typename T>
HeliumVertexSmearing_Z_ShiftUniverse<T>::HeliumVertexSmearing_Z_ShiftUniverse(
    typename T::config_t chw, double nsigma, double Uncertainty_Z)
    : T(chw, nsigma), m_Uncertainty_Z(Uncertainty_Z) {}

template <typename T>
double HeliumVertexSmearing_X_ShiftUniverse<T>::GetVertex_x() const {
  // double Plus_error_shift = (T::m_nsigma > 0 ) ?
  // Helium_Shifts::nsigma_Rshift_pos : Helium_Shifts::nsigma_Rshift_neg;
  // double Plus_error_shift =
  // double shift_val = T::m_nsigma * ( m_Uncertainty_R + Plus_error_shift);
  double shift_val = T::m_nsigma * m_Uncertainty_X;
  // std::cout <<"Vertex X[Before] = "<< T::GetVertex_x() << "Vertex X [After
  // Shift] " << shift_val + T::GetVertex_x()<<
  //" shift_val = "<< shift_val <<" Plus_error_shift = " << Plus_error_shift
  //<<std::endl;
  return shift_val + T::GetVertex_x();
}

template <typename T>
double HeliumVertexSmearing_Y_ShiftUniverse<T>::GetVertex_y() const {
  // double Plus_error_shift = (T::m_nsigma > 0 ) ?
  // Helium_Shifts::nsigma_Rshift_pos : Helium_Shifts::nsigma_Rshift_neg;
  // double Plus_error_shift =
  // double shift_val = T::m_nsigma * ( m_Uncertainty_R + Plus_error_shift);
  double shift_val = T::m_nsigma * m_Uncertainty_Y;
  // std::cout <<"Vertex X[Before] = "<< T::GetVertex_x() << "Vertex X [After
  // Shift] " << shift_val + T::GetVertex_x()<<
  //" shift_val = "<< shift_val <<" Plus_error_shift = " << Plus_error_shift
  //<<std::endl;
  return shift_val + T::GetVertex_y();
}

template <typename T>
double HeliumVertexSmearing_Z_ShiftUniverse<T>::GetVertex_z() const {
  double shift_val =
      T::m_nsigma * m_Uncertainty_Z;  //(m_Uncertainty_Z + Plus_error_shift);
  // std::cout <<"vertex Z[Before] = "<< T::GetVertex_z() << " Vertex Z [After
  // Shift] " << shift_val+T::GetVertex_z() <<std::endl;
  //" shift_val = "<< shift_val <<" Plus_error_shift = " << Plus_error_shift
  //<<std::endl;
  return shift_val + T::GetVertex_z();
}

template <typename T>
std::string HeliumVertexSmearing_X_ShiftUniverse<T>::ShortName() const {
  std::string universe_name = "VertexSmearingX";
  return universe_name;
}

template <typename T>
std::string HeliumVertexSmearing_X_ShiftUniverse<T>::LatexName() const {
  return "Vertex X Smearing";
}

template <typename T>
std::string HeliumVertexSmearing_Y_ShiftUniverse<T>::ShortName() const {
  std::string universe_name = "VertexSmearingY";
  return universe_name;
}

template <typename T>
std::string HeliumVertexSmearing_Y_ShiftUniverse<T>::LatexName() const {
  return "Vertex Y Smearing";
}

template <typename T>
std::string HeliumVertexSmearing_Z_ShiftUniverse<T>::ShortName() const {
  std::string universe_name = "VertexSmearingZ";
  return universe_name;
}

template <typename T>
std::string HeliumVertexSmearing_Z_ShiftUniverse<T>::LatexName() const {
  return "Vertex Z Smearing";
}

////////////////////////////////////////////
//
////////////////////////////////////////////

#endif  // HELIUM_VERTEXSMEARING_LATERALSYSTEMATICS_CXX
