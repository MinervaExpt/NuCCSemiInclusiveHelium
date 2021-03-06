
#ifndef Helium_VertexSmearing_LateralSystematics_2XY_2Z_H
#define Helium_VertexSmearing_LateralSystematics_2XY_2Z_H

#include "PlotUtils/TreeWrapper.h"
#include "HeliumCVUniverse.h"
#include <iostream>

//#include "Helium_VertexSmearing_LateralSystematics.h"
// THis Error Systematic applies lateral shifts, In the R and Z vertex positions

namespace Helium_Shifts {
  double const Uncertainty_X = 11.69;//mm
  double const Uncertainty_Y = 13.16;//mm
  double const Uncertainty_Z = 106.0; // mm // 65  // old value from true - RECO 114.54;//mm
  double const Uncertainty_R = 13.00 ;//mm
//error shifts from gaussain fit
  double const nsigma_Xshift_pos =   0.13; //mm
  double const nsigma_Xshift_neg =  - 0.13;//mm
  double const nsigma_Yshift_pos =   0.14; //mm
  double const nsigma_Yshift_neg =  - 0.14;//mm
  double const nsigma_Zshift_pos =   1.32;//mm
  double const nsigma_Zshift_neg =  - 1.32;//mm
  double const nsigma_Rshift_pos =   0.13;//mm
  double const nsigma_Rshift_neg =  - 0.13;//mm
}


  template<class T>
  class HeliumVertexSmearingRShiftUniverse: public T
    {
    public:
      HeliumVertexSmearingRShiftUniverse(typename T::config_t chw, double nsigma,
        double m_Uncertainty_R=Helium_Shifts::Uncertainty_R);

      virtual double GetVertex_r() const  /*override*/;

      virtual std::string ShortName() const /*override*/;
      virtual std::string LatexName() const /*override*/;
      virtual bool IsVerticalOnly()  const  { return false; }/*override*/
    private:
      double m_Uncertainty_R;
    };



    template<class T>
    class HeliumVertexSmearingZShiftUniverse: public T
      {
      public:
        HeliumVertexSmearingZShiftUniverse(typename T::config_t chw, double nsigma,
          double m_Uncertainty_Z=Helium_Shifts::Uncertainty_Z
        );

        virtual double GetVertex_z() const  /*override*/;
        //virtual double Get_SigmaZ(double Zinput) const;
        virtual std::string ShortName() const /*override*/;
        virtual std::string LatexName() const /*override*/;
        virtual bool IsVerticalOnly()  const  { return false; }/*override*/
      private:
        double m_Uncertainty_Z;
      };



// For template classes, the header needs to know about the definitions
#include "Helium_VertexSmearing_LateralSystematics_2XY_2Z.cxx"
#endif // RecoProtonKECutSYSTEMATICS_H
