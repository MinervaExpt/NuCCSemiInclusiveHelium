#ifndef HELIUM_TARGETMASSSYSTEMATICS_CXX
#define HELIUM_TARGETMASSSYSTEMATICS_CXX

// class to vary the Helium Smearings
#include "Helium_TargetMassSystematics.h"
#include <iostream>
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
template <class T>
std::vector<T*> GetHeliumTargetMassSystematics(typename T::config_t chain) {
  std::vector<T*> ret;
  std::cout << "Helium Target Mass shifts in 2 universe percentage with "
               "Postive shift =  ("
            << Helium_MassShifts::MassShift_Pos_percentage * 100
            << " [%] ) and negative shift = "
            << Helium_MassShifts::MassShift_Neg_percentage * 100 << "[%] )"
            << std::endl;
  // ret.push_back(new HeliumVertexSmearing_RShiftUniverse<T>(chain, -1.,
  // m_Uncertainty_R));
  // ret.push_back(new HeliumVertexSmearing_RShiftUniverse<T>(chain,  1.,
  // m_Uncertainty_R));
  ret.push_back(new HeliumTargetMassUniverse<T>(chain, -1.));
  ret.push_back(new HeliumTargetMassUniverse<T>(chain, 1.));

  return ret;
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
template <class T>
std::map<std::string, std::vector<T*> > GetHeliumTargetMassSystematicsMap(
    typename T::config_t chain) {
  std::map<std::string, std::vector<T*> > ret;

  std::cout << "Helium Target Mass shifts in 2 universe percentage with "
               "Postive shift =  ("
            << Helium_MassShifts::MassShift_Pos_percentage * 100
            << " [%] ) and negative shift = "
            << Helium_MassShifts::MassShift_Neg_percentage * 100 << "[%] )"
            << std::endl;

  ret["HeliumTargetMass"].push_back(
      new HeliumTargetMassUniverse<T>(chain, -1.));
  ret["HeliumTargetMass"].push_back(new HeliumTargetMassUniverse<T>(chain, 1.));

  return ret;
}

/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
HeliumTargetMassUniverse<T>::HeliumTargetMassUniverse(typename T::config_t chw,
                                                      double nsigma)
    : T(chw, nsigma) {}

template <typename T>
double HeliumTargetMassUniverse<T>::GetTargetMassWeight() const {
  int targetZ = T::GetTargetZTrue();  // GetTargetType(); // atomic number of
                                      // struck nucleus
  double cv_wgt = T::GetTargetMassWeight();
  double wgt_shift;
  // if interaction is a Helium Nuclear Target else assume no shift
  if (targetZ == 2) {
    wgt_shift = Helium_MassShifts::
    HeliumMassShift;  //(T::m_nsigma > 0 ) ?
    //Helium_MassShifts::MassShift_Pos_percentage :
    //Helium_MassShifts::MassShift_Neg_percentage;
  }

  else {
    // assume 0 if not helium
    wgt_shift = 0.0;  // only apply to helium for now
  }

  return cv_wgt + T::m_nsigma * wgt_shift;
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
std::string HeliumTargetMassUniverse<T>::ShortName() const {
  std::string universe_name = "HeliumTargetMass";  //(T::m_nsigma > 0 ) ?
  //"HeTargetMass_Pos" :
  //"HeTargetMass_Neg";
  return universe_name;
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
std::string HeliumTargetMassUniverse<T>::LatexName() const {
  return "He Target Mass";
}

////////////////////////////////////////////
//
////////////////////////////////////////////

#endif  // HELIUM_VERTEXSMEARING_LATERALSYSTEMATICS_CXX
