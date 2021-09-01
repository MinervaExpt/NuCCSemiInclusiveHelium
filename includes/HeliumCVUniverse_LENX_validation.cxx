#include "HeliumCVUniverse_LENX_validation.h"







 double  HeliumCVUniverse_LENX_validation::GetWeight_LENXVal() const{return GetDouble("wght");}
 int HeliumCVUniverse_LENX_validation::GetCC_LENXVal() const{ return GetInt("cc");}
 int HeliumCVUniverse_LENX_validation::Get_imcomingNUtype_LENXVal() const{ return GetInt("neu");}

double HeliumCVUniverse_LENX_validation::GetP_x_lepton_LENXVal() const{return GetDouble("pxl");} // GeV
double HeliumCVUniverse_LENX_validation::GetP_y_lepton_LENXVal() const{return GetDouble("pyl");} // GeV


double HeliumCVUniverse_LENX_validation::GetP_z_lepton_LENXVal() const{return GetDouble("pzl");} // GeV
double HeliumCVUniverse_LENX_validation::GetP_E_lepton_LENXVal() const{return GetDouble("El");} // GeV



double HeliumCVUniverse_LENX_validation::GetPmuTransverse_LENXVal() const { // input is GeV
    const double px=HeliumCVUniverse_LENX_validation::GetP_x_lepton_LENXVal();
    const double py=HeliumCVUniverse_LENX_validation::GetP_y_lepton_LENXVal();
    const double pz=HeliumCVUniverse_LENX_validation::GetP_z_lepton_LENXVal();
    // Copied (and modified) from MinervaCoordSysTool::thetaWRTBeam
    const double numi_beam_angle_rad = -0.05887; // Taken from MinervaPhysicalConstants.h
    double pyp = -1.0 *sin( numi_beam_angle_rad )*pz + cos( numi_beam_angle_rad )*py;
    double pt   = sqrt( pow(px,2) +pow(pyp,2) );
    return pt; //GeV
  }


  double HeliumCVUniverse_LENX_validation::GetPmuLongitudinal_LENXVal() const { //input is GeV
    const double pylep=HeliumCVUniverse_LENX_validation::GetP_y_lepton_LENXVal();
    const double pzlep=HeliumCVUniverse_LENX_validation::GetP_z_lepton_LENXVal();
    // Copied (and modified) from MinervaCoordSysTool::thetaWRTBeam
    const double numi_beam_angle_rad = -0.05887; // Taken from MinervaPhysicalConstants.h
    double pzp = cos( numi_beam_angle_rad )*pzlep + sin( numi_beam_angle_rad )*pylep;
    return pzp; //GeV
  }





  double HeliumCVUniverse_LENX_validation::ThetaWRTBeam(double x , double y, double z, double bias) const {
    double beamconstant = -0.05887;
    double pyp = -1.0 *TMath::Sin( beamconstant + bias )*z + TMath::Cos( beamconstant + bias )*y;
    double pzp = TMath::Cos(beamconstant + bias )*z + TMath::Sin( beamconstant + bias )*y;
    double denom2 = pow(x,2) + pow(pyp,2) + pow(pzp,2);
    if( 0. == denom2 || denom2 < 0.0){
      return -999;
    }
    else{
      return acos(pzp / sqrt(denom2) );
    }

  }


double HeliumCVUniverse_LENX_validation::GetAnglewrtb_lepton_LENXVal() const{
  const double px=HeliumCVUniverse_LENX_validation::GetP_x_lepton_LENXVal();
  const double py=HeliumCVUniverse_LENX_validation::GetP_y_lepton_LENXVal();
  const double pz=HeliumCVUniverse_LENX_validation::GetP_z_lepton_LENXVal();

  return HeliumCVUniverse_LENX_validation::ThetaWRTBeam(px , py, pz, 0.0);


}


double HeliumCVUniverse_LENX_validation::GetAnglewrtb_Degs_lepton_LENXVal() const{

auto angle = HeliumCVUniverse_LENX_validation::GetAnglewrtb_lepton_LENXVal();
return angle *  TMath::RadToDeg();

}



//virtual int GetFS_pdg_LENXVal() const;

 double HeliumCVUniverse_LENX_validation::GetVertex_X_LENXVal() const{return GetDouble("vtxx")*1000;}; // convert to mm
 double HeliumCVUniverse_LENX_validation::GetVertex_Y_LENXVal() const{return GetDouble("vtxy")*1000;}; // convert to mm
 double HeliumCVUniverse_LENX_validation::GetVertex_R_LENXVal() const{
   auto x = HeliumCVUniverse_LENX_validation::GetVertex_X_LENXVal();
   auto y = HeliumCVUniverse_LENX_validation::GetVertex_Y_LENXVal();
   return sqrt(pow(x,2) + pow(y,2));

 }
 double HeliumCVUniverse_LENX_validation::GetVertex_RR_LENXVal() const{
   auto x = HeliumCVUniverse_LENX_validation::GetVertex_X_LENXVal();
   auto y = HeliumCVUniverse_LENX_validation::GetVertex_Y_LENXVal();
   return pow(x,2) + pow(y,2);

 }
 double  HeliumCVUniverse_LENX_validation::GetVertex_Z_LENXVal() const{return GetDouble("vtxz")*1000;}; // convert to mm

 int HeliumCVUniverse_LENX_validation::Get_atomic_Z_LENXVal() const{ return GetInt("Z");}
 int HeliumCVUniverse_LENX_validation::Get_atomic_A_LENXVal() const{ return GetInt("A");}
//virtual int Get_nfsp_LENXVal() const;

 int HeliumCVUniverse_LENX_validation::Get_qel_LENXVal() const{ return GetInt("qel");}
 int HeliumCVUniverse_LENX_validation::Get_mec_LENXVal() const{ return GetInt("mec");}
 int HeliumCVUniverse_LENX_validation::Get_res_LENXVal() const{ return GetInt("res");}
 int HeliumCVUniverse_LENX_validation::Get_dis_LENXVal() const{ return GetInt("dis");}
 int HeliumCVUniverse_LENX_validation::Get_coh_LENXVal() const{ return GetInt("coh");}
 int HeliumCVUniverse_LENX_validation::Get_imd_LENXVal() const{ return GetInt("imd");}
// for other root file

  double HeliumCVUniverse_LENX_validation::GetVertex_X_MC() const{return GetVecElem("mc_vtx",0);}
  double HeliumCVUniverse_LENX_validation::GetVertex_Y_MC() const{return GetVecElem("mc_vtx",1);}
  double HeliumCVUniverse_LENX_validation::GetVertex_Z_MC() const{return GetVecElem("mc_vtx",2);}
  double HeliumCVUniverse_LENX_validation::GetVertex_R_MC() const{
    auto x = HeliumCVUniverse_LENX_validation::GetVertex_X_MC();
    auto y = HeliumCVUniverse_LENX_validation::GetVertex_Y_MC();
    return sqrt(pow(x,2) + pow(y,2));

  };

  double HeliumCVUniverse_LENX_validation::GetVertex_RR_MC() const{
    auto x = HeliumCVUniverse_LENX_validation::GetVertex_X_MC();
    auto y = HeliumCVUniverse_LENX_validation::GetVertex_Y_MC();
    return pow(x,2) + pow(y,2);

  };


  int HeliumCVUniverse_LENX_validation::GetCC_MC() const{return GetInt("mc_current");}
  int HeliumCVUniverse_LENX_validation::Get_imcomingNUtype_MC() const{return GetInt("mc_incoming");}
  double HeliumCVUniverse_LENX_validation::GetP_E_lepton_MC() const{return GetVecElem("mc_primFSLepton",3)*.001;} // GeV
  int HeliumCVUniverse_LENX_validation::Get_atomic_Z_MC() const{ return GetInt("mc_targetZ");}

  double HeliumCVUniverse_LENX_validation::GetWeight_MC() const{return GetDouble("wgt");};

  double HeliumCVUniverse_LENX_validation::GetP_x_lepton_MC() const{return GetVecElem("mc_primFSLepton",0)*.001;} // GeV
  double HeliumCVUniverse_LENX_validation::GetP_y_lepton_MC() const{return GetVecElem("mc_primFSLepton",1)*.001;} // GeV
  double HeliumCVUniverse_LENX_validation::GetP_z_lepton_MC() const{return GetVecElem("mc_primFSLepton",2)*.001;} // GeV

  double HeliumCVUniverse_LENX_validation::GetPmuTransverse_MC() const { // input is GeV
      const double px=HeliumCVUniverse_LENX_validation::GetP_x_lepton_MC();
      const double py=HeliumCVUniverse_LENX_validation::GetP_y_lepton_MC();
      const double pz=HeliumCVUniverse_LENX_validation::GetP_z_lepton_MC();
      // Copied (and modified) from MinervaCoordSysTool::thetaWRTBeam
      const double numi_beam_angle_rad = -0.05887; // Taken from MinervaPhysicalConstants.h
      double pyp = -1.0 *sin( numi_beam_angle_rad )*pz + cos( numi_beam_angle_rad )*py;
      double pt   = sqrt( pow(px,2) +pow(pyp,2) );
      return pt; //GeV
    }


    double HeliumCVUniverse_LENX_validation::GetPmuLongitudinal_MC() const { //input is GeV
      const double pylep=HeliumCVUniverse_LENX_validation::GetP_y_lepton_MC();
      const double pzlep=HeliumCVUniverse_LENX_validation::GetP_z_lepton_MC();
      // Copied (and modified) from MinervaCoordSysTool::thetaWRTBeam
      const double numi_beam_angle_rad = -0.05887; // Taken from MinervaPhysicalConstants.h
      double pzp = cos( numi_beam_angle_rad )*pzlep + sin( numi_beam_angle_rad )*pylep;
      return pzp; //GeV
    }


  double HeliumCVUniverse_LENX_validation::GetAnglewrtb_lepton_MC() const{

    const double px=HeliumCVUniverse_LENX_validation::GetP_x_lepton_MC();
    const double py=HeliumCVUniverse_LENX_validation::GetP_y_lepton_MC();
    const double pz=HeliumCVUniverse_LENX_validation::GetP_z_lepton_MC();

    return HeliumCVUniverse_LENX_validation::ThetaWRTBeam(px , py, pz, 0.0);

  }

  double HeliumCVUniverse_LENX_validation::GetAnglewrtb_Degs_lepton_MC() const{
    auto angle = HeliumCVUniverse_LENX_validation::GetAnglewrtb_lepton_MC();
    return angle *  TMath::RadToDeg();
  }



// CVUniverse_cxx
