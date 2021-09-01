
#ifndef HELIUM_VERTEXSMEARING_LATERALSYSTEMATICS_2XY_2Z_CXX
#define HELIUM_VERTEXSMEARING_LATERALSYSTEMATICS_2XY_2Z_CXX

// class to vary the Helium Smearing
#include "Helium_VertexSmearing_LateralSystematics_2XY_2Z.h"
#include <iostream>


 template <class T>
  std::vector<T*> GetHELIUMVertexSmearingShiftSystematics(typename T::config_t chain,
  double m_Uncertainty_R = Helium_Shifts::Uncertainty_R,
  double m_Uncertainty_Z = Helium_Shifts::Uncertainty_Z)
    {
      std::vector<T*> ret;
      std::cout << "Vertex Helium Smearing for a shifts in 4 universe (-/+)(deltaR) =  (" <<  m_Uncertainty_R <<
                   "[mm]) and (-/+)(deltaZ) = ()"<<m_Uncertainty_Z<< "[mm])" << std::endl;
      ret.push_back(new HeliumVertexSmearingRShiftUniverse<T>(chain, -1., m_Uncertainty_R));
      ret.push_back(new HeliumVertexSmearingRShiftUniverse<T>(chain,  1., m_Uncertainty_R));
      ret.push_back(new HeliumVertexSmearingZShiftUniverse<T>(chain, -1., m_Uncertainty_Z));
      ret.push_back(new HeliumVertexSmearingZShiftUniverse<T>(chain,  1., m_Uncertainty_Z));


      return ret;
    }


  template <class T>
  std::map<std::string, std::vector<T*> > GetHELIUMVertexSmearingShiftSystematicsMap(
      typename T::config_t chain,
      double m_Uncertainty_R=Helium_Shifts::Uncertainty_R,
      double m_Uncertainty_Z=Helium_Shifts::Uncertainty_Z)
      {
        std::map< std::string, std::vector<T*> > ret;
        std::cout << "Vertex Helium Smearing for a shifts in 4 universe (-/+)(deltaR) = (" <<  m_Uncertainty_R<<
        "[mm]) and (-/+)(deltaZ) = ()"<<m_Uncertainty_Z<< "[mm])" << std::endl;

              ret["VertexSmearingR"].push_back(new HeliumVertexSmearingRShiftUniverse<T>(chain, -1.,   m_Uncertainty_R));
              ret["VertexSmearingR"].push_back(new HeliumVertexSmearingRShiftUniverse<T>(chain,  1.,   m_Uncertainty_R));
              ret["VertexSmearingZ"].push_back(new HeliumVertexSmearingZShiftUniverse<T>(chain, -1.,   m_Uncertainty_Z));
              ret["VertexSmearingZ"].push_back(new HeliumVertexSmearingZShiftUniverse<T>(chain,  1.,   m_Uncertainty_Z));
    return ret;
  }

  // Class Definitions
  // Constructor
  template<typename T>
  HeliumVertexSmearingRShiftUniverse<T>::HeliumVertexSmearingRShiftUniverse(
      typename T::config_t chw, double nsigma, double Uncertainty_R):
       T(chw, nsigma), m_Uncertainty_R(Uncertainty_R) {}

  template<typename T>
  HeliumVertexSmearingZShiftUniverse<T>::HeliumVertexSmearingZShiftUniverse(
    typename T::config_t chw, double nsigma, double Uncertainty_Z):
    T(chw, nsigma),  m_Uncertainty_Z(Uncertainty_Z) {}


  template<typename T>
  double HeliumVertexSmearingRShiftUniverse<T>::GetVertex_r() const {
    //double Plus_error_shift = (T::m_nsigma > 0 ) ? Helium_Shifts::nsigma_Rshift_pos : Helium_Shifts::nsigma_Rshift_neg;
    //double Plus_error_shift =
    //double shift_val = T::m_nsigma * ( m_Uncertainty_R + Plus_error_shift);
    double shift_val = T::m_nsigma * m_Uncertainty_R;
    //std::cout <<"Vertex X[Before] = "<< T::GetVertex_x() << "Vertex X [After Shift] " << shift_val + T::GetVertex_x()<<
    //" shift_val = "<< shift_val <<" Plus_error_shift = " << Plus_error_shift <<std::endl;
    return shift_val+T::GetVertex_r();

  }


  template<typename T>
  double HeliumVertexSmearingZShiftUniverse<T>::GetVertex_z() const {
    //double Z = T::GetVertex_z();
    //double sigmaZ  =61.1199 - 0.0125073*Z;

    //double Plus_error_shift = (T::m_nsigma > 0 ) ? sigmaZ : -1*sigmaZ;
    double shift_val = T::m_nsigma * m_Uncertainty_Z; //(m_Uncertainty_Z + Plus_error_shift);
  //std::cout <<"vertex Z[Before] = "<< T::GetVertex_z() << " Vertex Z [After Shift] " << shift_val+T::GetVertex_z() <<std::endl;
    //" shift_val = "<< shift_val <<" Plus_error_shift = " << Plus_error_shift <<std::endl;
    return shift_val+T::GetVertex_z();

  }

  template<typename T>
  std::string HeliumVertexSmearingRShiftUniverse<T>::ShortName() const {
    //std::string universe_name = (T::m_nsigma > 0 ) ? "VertexSmearingR_Pos" : "VertexSmearingR_Neg";
    std::string universe_name = "VertexSmearingR";
    return universe_name; }

  template<typename T>
  std::string HeliumVertexSmearingRShiftUniverse<T>::LatexName() const { return "Vertex R Smearing"; }


  template<typename T>
  std::string HeliumVertexSmearingZShiftUniverse<T>::ShortName() const {
    //std::string universe_name = (T::m_nsigma > 0 ) ? "VertexSmearingZ_Pos" : "VertexSmearingZ_Neg";
    std::string universe_name = "VertexSmearingZ";
    return universe_name; }

  template<typename T>
  std::string HeliumVertexSmearingZShiftUniverse<T>::LatexName() const { return "Vertex Z Smearing"; }



//double Get_SigmaZ(double Zinput) const {
//return 108.005 - 0.026578 *Zinput;
//};
////////////////////////////////////////////
//
////////////////////////////////////////////






/*

  virtual double  const override {
    double shift_val  = 11.69 * nsigma;
    return shift_val + CVUniverse::GetVertex_x();
  }

  virtual double GetVertex_y() const override {
    double shift_val    = 13.16 * nsigma;
    return shift_val + CVUniverse::GetVertex_y();
  }

  virtual double GetVertex_z() const override {
    double shift_val    = 114.54* nsigma;
    return shift_val + CVUniverse::GetVertex_z();
  }
*/
#endif // HELIUM_VERTEXSMEARING_LATERALSYSTEMATICS_CXX
