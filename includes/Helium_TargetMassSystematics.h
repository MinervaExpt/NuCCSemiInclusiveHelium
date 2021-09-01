
#ifndef Helium_TARGETMASSSYSTEMATICS_H
#define Helium_TARGETMASSSYSTEMATICS_H

#include "PlotUtils/TreeWrapper.h"
#include "HeliumCVUniverse.h"
#include <iostream>
// THis Helium Error Systematic applies  a vertial shift, to Truth Helium Nuclear events 





namespace Helium_MassShifts {
  double const HeliumMassShift = 0.02;//
  double const MassShift_Pos_percentage = 0.02;// % two percent mass different
  double const MassShift_Neg_percentage = 0.02;//
}

  template<class T>
  class HeliumTargetMassUniverse: public T
    {
    public:
      HeliumTargetMassUniverse(typename T::config_t chw, double nsigma );

      virtual double GetTargetMassWeight() const  /*override*/;
      virtual std::string ShortName() const /*override*/;
      virtual std::string LatexName() const /*override*/;
      virtual bool IsVerticalOnly()  const  { return true; }/*override*/
    private:
      double m_PercentMassShift;
    };




// For template classes, the header needs to know about the definitions
#include "Helium_TargetMassSystematics.cxx"
#endif // Helium_TARGETMASSSYSTEMATICS_H
