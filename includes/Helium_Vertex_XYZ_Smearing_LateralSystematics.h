// File: CrossSection_Normalization.h
// Brief: The header for Helium_Vertex_XYZ_Smearing_LateralSystematics.h
//  contains functions for Systematic helium Vertex Error
// Author: Christian Nguyen christian2nguyen@ufl.edu
// ========================================================================

#ifndef Helium_Vertex_XYZ_Smearing_LateralSystematics_H
#define Helium_Vertex_XYZ_Smearing_LateralSystematics_H

#include "PlotUtils/TreeWrapper.h"
#include "HeliumCVUniverse.h"
#include <iostream>

//#include "Helium_VertexSmearing_LateralSystematics.h"
// THis Error Systematic applies lateral shifts, In the R and Z vertex positions

namespace Helium_ShiftsXYZ {
/////////////
////These Values came from Convolution Study of the Vertex
/////////////
double const Uncertainty_X_FULL = 12.0;  // mm
double const Uncertainty_Y_FULL = 48.0;  // mm
double const Uncertainty_Z_FULL = 4.0;  // mm

double const Uncertainty_X_EMPTY = 12.0;  // mm
double const Uncertainty_Y_EMPTY = 48.0;  // mm
double const Uncertainty_Z_EMPTY = 6.0;  // mm
}

template <class T>
class HeliumVertexSmearing_X_ShiftUniverse : public T {
 public:
  HeliumVertexSmearing_X_ShiftUniverse(typename T::config_t chw, double nsigma,
                                       double m_Uncertainty_X);

  virtual double GetVertex_x() const /*override*/;

  virtual std::string ShortName() const /*override*/;
  virtual std::string LatexName() const /*override*/;
  virtual bool IsVerticalOnly() const { return false; } /*override*/

 private:
  double m_Uncertainty_X;
};

template <class T>
class HeliumVertexSmearing_Y_ShiftUniverse : public T {
 public:
  HeliumVertexSmearing_Y_ShiftUniverse(typename T::config_t chw, double nsigma,
                                       double m_Uncertainty_Y);

  virtual double GetVertex_y() const /*override*/;
  virtual std::string ShortName() const /*override*/;
  virtual std::string LatexName() const /*override*/;
  virtual bool IsVerticalOnly() const { return false; } /*override*/

 private:
  double m_Uncertainty_Y;
};

template <class T>
class HeliumVertexSmearing_Z_ShiftUniverse : public T {
 public:
  HeliumVertexSmearing_Z_ShiftUniverse(typename T::config_t chw, double nsigma,
                                       double m_Uncertainty_Z);

  virtual double GetVertex_z() const /*override*/;
  // virtual double Get_SigmaZ(double Zinput) const;
  virtual std::string ShortName() const /*override*/;
  virtual std::string LatexName() const /*override*/;
  virtual bool IsVerticalOnly() const { return false; } /*override*/

 private:
  double m_Uncertainty_Z;
};

// For template classes, the header needs to know about the definitions
#include "Helium_Vertex_XYZ_Smearing_LateralSystematics.cxx"
#endif  // RecoProtonKECutSYSTEMATICS_H
