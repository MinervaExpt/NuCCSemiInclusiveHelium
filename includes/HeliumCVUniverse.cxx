//File: HeliumCVUniverse.cxx
//Brief: ME HeliumCVUniverse for the Helium Analysis
//Author: Christian Nguyen christian2nguyen@ufl.edu

#include "HeliumCVUniverse.h"

const double Mev_to_GeV=.001;
const double True_Start_Znode = 4292.96; // mm


//CTOR
double HeliumCVUniverse::GetTrueQ0() const{
  double q0 = -1;
  q0 = GetVecElem("mc_incomingPartVec",3) - GetVecElem("mc_primFSLepton",3);
  return q0/1000.0;
}
///////////////////////////////////////////////////

double HeliumCVUniverse::GetTrueQ3( ) const {
  double px = GetVecElem("mc_primFSLepton",0)-GetVecElem("mc_incomingPartVec",0);
  double py = GetVecElem("mc_primFSLepton",1)-GetVecElem("mc_incomingPartVec",1);
  double pz = GetVecElem("mc_primFSLepton",2)-GetVecElem("mc_incomingPartVec",2);
  double q3 = sqrt(px*px+py*py+pz*pz);
  return q3/1000.0;
}
///////////////////////////////////////////////////
double HeliumCVUniverse::GetTrueQ2() const{
  double q3 = HeliumCVUniverse::GetTrueQ3();
  double q0 = HeliumCVUniverse::GetTrueQ0();
  return q3*q3 - q0*q0;  // check this vs tuple value
}
///////////////////////////////////////////////////
double HeliumCVUniverse::GetQ2True_GeV() const {
  double qq = GetQ2True() * 0.001 * 0.001; // MeV^2 to GeV^2
  return qq;
}
///////////////////////////////////////////////////
bool HeliumCVUniverse::GetboolIsUsableMuon()         const { return GetBool("cut_isUsableMuon");}
///////////////////////////////////////////////////
int HeliumCVUniverse::GetIntIsusableMuon()           const
{
  bool mybool = GetboolIsUsableMuon();
  int boolInt = mybool ? 1 : 0;
  return boolInt;
}
///////////////////////////////////////////////////
double HeliumCVUniverse::GetOpenAngle(int TRKNum) const{return GetVecElem("trackangle",TRKNum);}
// Get Branches and Calculate Quantities for the universe/event
// Get RECO Branches (always MeV, radians)
double HeliumCVUniverse::GetDummyVar()  const { return -999.; }
double HeliumCVUniverse::GetVertexChiSqrFit() const{return GetDouble("cryo_vtx_fit_chi2");}
///////////////////////////////////////////////////
Material_type HeliumCVUniverse::Get_MaterialStackType()const {
  int target_Z = GetTargetType();
  Material_type Type =  GetMaterial_TargetZenum(target_Z);
  return  Type;
}
///////////////////////////////////////////////////
Interaction_type HeliumCVUniverse::Get_InteractionStackType()const {
  int interaction_type = GetIntactionType();
  Interaction_type Type =GetInteractionenum(interaction_type);
  return Type;
}
///////////////////////////////////////////////////
Particle_type HeliumCVUniverse::Get_NonParticleStackType(int trk) const{
  int PDG =   GetNon_muon_PDG(trk );
  Particle_type type = GetParticlegroup_type(PDG );
  return type;

}
///////////////////////////////////////////////////
Particle_type HeliumCVUniverse::Get_ParticleStackType_leadingandnonleading(int trk) const{
  int PDG =   GetNon_muon_PDG(trk );
  return GetParticlegroup_typeProtonandpion_other(PDG);
}
///////////////////////////////////////////////////
double HeliumCVUniverse::GetMuonE()       const { return GetDouble("muonE")*.001; }
double HeliumCVUniverse::GetPmu_inhouse() const { return sqrt(pow(GetMuonE(),2.0) - pow(HeliumConsts::MUON_MASS_GEV,2.0)); }
double HeliumCVUniverse::GetMuonPz()      const { return GetVecElem("muonP",2)* .001;}
double HeliumCVUniverse::GetMuonPx()      const { return GetVecElem("muonP",0)* .001;}
double HeliumCVUniverse::GetMuonPy()      const { return GetVecElem("muonP",1)* .001;}
double HeliumCVUniverse::GetChargemu()    const { return GetDouble("muonCharge");}
double HeliumCVUniverse::GetDOCAmu()      const { return GetVecElem("trackDOCA",0);}
///////////////////////////////////////////////////
double HeliumCVUniverse::GetMuonE_ECT()       const { return GetDouble("muonE_EnergyCorrectionTool")*.001; }
double HeliumCVUniverse::GetPmu_ECT()         const { return sqrt(pow(GetMuonE_ECT(),2.0) - pow(HeliumConsts::MUON_MASS_GEV,2.0)); }
double HeliumCVUniverse::GetMuonPx_ECT()      const { return GetVecElem("muonP_EnergyCorrectionTool",0)* .001;}
double HeliumCVUniverse::GetMuonPy_ECT()      const { return GetVecElem("muonP_EnergyCorrectionTool",1)* .001;}
double HeliumCVUniverse::GetMuonPz_ECT()      const { return GetVecElem("muonP_EnergyCorrectionTool",2)* .001;}
///////////////////////////////////////////////////
double HeliumCVUniverse::GetMuonP_three_momentum_absolute() const {
  double px = GetMuonPx_ECT();
  double py = GetMuonPy_ECT();
  double pz = GetMuonPz_ECT();
  return sqrt(px*px + py*py + pz*pz);
}
///////////////////////////////////////////////////
double HeliumCVUniverse::GetMuonPt()                    const {
  double px = GetVecElem("muonP",0)* .001;
	double py = GetVecElem("muonP",1)* .001;
	double pT =sqrt(pow(px,2)+pow(py,2));
	return pT;}
///////////////////////////////////////////////////
double HeliumCVUniverse::GetMuonPt_ECT()                 const {
  double px = GetVecElem("muonP_EnergyCorrectionTool",0)* .001;
  double py = GetVecElem("muonP_EnergyCorrectionTool",1)* .001;
  double pT =sqrt(pow(px,2)+pow(py,2));
  return pT;}
///////////////////////////////////////////////////
double HeliumCVUniverse::GetVertex_x()                 const{return GetVecElem("cryo_vtx",0);};
double HeliumCVUniverse::GetVertex_y()                 const{return GetVecElem("cryo_vtx",1);};
double HeliumCVUniverse::GetVertex_z()                 const{return GetVecElem("cryo_vtx",2);};
double HeliumCVUniverse::GetVertex_r()                 const{
  double x = HeliumCVUniverse::GetVertex_x() ;
  double y = HeliumCVUniverse::GetVertex_y() ;
  double r = sqrt(pow(x,2)+ pow(y,2));
  return r ;};
//////////////////////////////////////////////////////
// Get Vertex Opt Type
//////////////////////////////////
bool HeliumCVUniverse::GetVertex_option1() const{return GetBool("Vtx_Op_1");};//vtx was reconstructed using Vtx Option 1
bool HeliumCVUniverse::GetVertex_option2() const{return GetBool("Vtx_Op_2");};//vtx was reconstructed using Vtx Option 2
bool HeliumCVUniverse::GetVertex_option3() const{return GetBool("Vtx_Op_3");};//vtx was reconstructed using Vtx Option 3

bool HeliumCVUniverse::GetisOneTrk() const{return GetBool("one_Trk");};//vtx was reconstructed using  1 track(s)
bool HeliumCVUniverse::GetisTwoTrk() const{return GetBool("two_Trk");};//vtx was reconstructed using  2 track(s)
bool HeliumCVUniverse::GetisGreaterTwoTrk() const{return GetBool("more_Trk");};///vtx was reconstructed using >2 track(s)

VertexOptions HeliumCVUniverse::GetVertex_optionType() const {
  bool option1 = GetVertex_option1();
  bool option2 = GetVertex_option2();
  bool option3 = GetVertex_option3();
  if(option1==true && option2== false && option3 ==false ){return kOpt_1;}
  else if(option1==false && option2== true && option3 ==false ){return kOpt_2;}
  else if(option1==false && option2== false && option3 ==true ){return kOpt_3;}
  else if(option1==false && option2== false && option3 ==false ){return kOpt_4;}

};

boolNTrack HeliumCVUniverse::GetVertex_boolNTrack() const {
  bool trk1 = GetisOneTrk();
  bool trk2 = GetisTwoTrk();
  bool trkgreater2 = GetisGreaterTwoTrk();

  if(trk1==true && trk2 ==false && trkgreater2 == false ){return kone_Trk;}
  else if(trk1==false && trk2== true && trkgreater2 == false ){return ktwo_Trk;}
  else if(trk1==false && trk2== false && trkgreater2 ==true ){return kmore_Trk;}
  else{return kallfalseTrk;}
};

///////////////////////////////////////////////////
CryoTank_REGIONS HeliumCVUniverse::Get_RECO_CryoTank_region()const{
  double Z = HeliumCVUniverse::GetVertex_z();
  CryoTank_REGIONS region = Region_of_CryoTank(Z);
  return region;
}
///////////////////////////////////////////////////
double HeliumCVUniverse::GetVertex_rr()                 const{
	double x = HeliumCVUniverse::GetVertex_x() ;
	double y = HeliumCVUniverse::GetVertex_y() ;
	double rr = pow(x,2)+ pow(y,2);
	return rr ;};
///////////////////////////////////////////////////
double HeliumCVUniverse::GetDistance_vertex_toUpStreamBulge()const{
  double r = GetVertex_r();
  double z = GetVertex_z();
  return DistanceFromUpStreamBulge(z , r);
};
///////////////////////////////////////////////////
double HeliumCVUniverse::GetDistance_vertex_toDownStreamBulge()const{
  double r = GetVertex_r();
  double z = GetVertex_z();
  return DistanceFromDownStreamBulge(z , r);
};
///////////////////////////////////////////////////
double HeliumCVUniverse::pseudorapidity_muon() const{
  double P_l = GetMuonPz_ECT(); //GeV
  double p3 = GetMuonP_three_momentum_absolute(); //GeV
  return atanh(P_l / p3);
}
///////////////////////////////////////////////////
double HeliumCVUniverse::rapidity_muon() const{
  double pseudorapidity = pseudorapidity_muon();
  double acosh_pseudo = acosh(pseudorapidity);
  double pt = GetMuonPt_ECT(); // GeV
  double muon_mass_sqrted = 0.1056583755 * 0.1056583755; //GeV
  double bottom = sqrt(pt*pt * muon_mass_sqrted);
  double top_1 = sqrt(muon_mass_sqrted* pt*pt *  acosh_pseudo*acosh_pseudo);
  double top_2 = pt * asinh(pseudorapidity);
  return log((top_1 + top_2) /  bottom);
}
///////////////////////////////////////////////////
double HeliumCVUniverse::GetCurvatureSignificance() const{return GetDouble("muon_curvatureSignificance");};
double HeliumCVUniverse::GetmuAngleWRTB()           const{return GetDouble("muon_theta"); };
double HeliumCVUniverse::GetmuAngleWRTB_Degs()      const{return  ConvertRadToDeg(GetmuAngleWRTB()); };
//////////////////////////////////////////////////////////////////////////
/////////////Veto                                             ////////////
//////////////////////////////////////////////////////////////////////////
int  HeliumCVUniverse::GetMatchToVeto()               const{ return GetInt("event_IsVeto");};
int  HeliumCVUniverse::GetSixPush()                   const{ return GetInt("sixPush");};
int  HeliumCVUniverse::GetNumberMatchToVeto()         const{ return GetInt("NumberMatchToVeto");};
bool HeliumCVUniverse::Getextrapnowalls()             const{ return GetBool("extrapnowalls");};
bool HeliumCVUniverse::Getextrapwall1()               const{ return GetBool("extrapwall1");};
bool HeliumCVUniverse::Getextrapwall2()               const{ return GetBool("extrapwall2");};
bool HeliumCVUniverse::Getextrapbothwalls()           const{ return GetBool("extrapbothwalls");};
bool HeliumCVUniverse::GetMuonTrkMatchToVETOwalloff() const{ return GetBool("MuonTrkMatchToVETOwalloff");};
std::vector <int> HeliumCVUniverse::GetVector_PMTVeto_Map() const {return GetVecInt("VetoWallPMTStatusMAP");};
///////////////////////////////////////////////////
//int  HeliumCVUniverse::Get_rockMuonTruth()         const{ return GetInt("rockMuonTruth");};
//////////////////////////////////////////////////////////////////////////////////////////////////////
double HeliumCVUniverse::GetTotalMomentum(double px,double py,double pz)const{
	return sqrt(pow(px,2) + pow(py,2) + pow(pz,2));
}
///////////////////////////////////////////
double HeliumCVUniverse::GetMINOS_Energy() const{return GetDouble("MINOS_E")/ 1000.0;};
double HeliumCVUniverse::GetMINOSStart_X()const{return GetVecElem("muon_minosStart",0);};
double HeliumCVUniverse::GetMINOSStart_Y()const{return GetVecElem("muon_minosStart",1);};
double HeliumCVUniverse::GetMINOSStart_Z()const{return GetVecElem("muon_minosStart",2);};
///////////////////////////////////////////////////
double HeliumCVUniverse::GetMINOSEnd_X()const{return GetVecElem("muon_minosEnd",0);};
double HeliumCVUniverse::GetMINOSEnd_Y()const{return GetVecElem("muon_minosEnd",1);};
double HeliumCVUniverse::GetMINOSEnd_Z()const{return GetVecElem("muon_minosEnd",2);};
///////////////////////////////////////////////////
double HeliumCVUniverse::GetMuon_firstNode_X()const{ return GetVecElem("cryotrackxnodes",0);};
double HeliumCVUniverse::GetMuon_firstNode_Y()const{ return GetVecElem("cryotrackynodes",0);};
double HeliumCVUniverse::GetMuon_firstNode_Z()const{ return GetVecElem("cryotrackznodes",0);};
///////////////////////////////////////////////////
double HeliumCVUniverse::GetMuon_lastNode_X()const {return GetVecElem("cryotrack_lastxnodes",0);};
double HeliumCVUniverse::GetMuon_lastNode_Y()const {return GetVecElem("cryotrack_lastynodes",0);};
double HeliumCVUniverse::GetMuon_lastNode_Z()const {return GetVecElem("cryotrack_lastznodes",0);};
///////////////////////////////////////////////////
std::vector <double> HeliumCVUniverse::GetVector_firstNode_X() const {return GetVecDouble("cryotrackxnodes");}
std::vector <double> HeliumCVUniverse::GetVector_firstNode_Y() const {return GetVecDouble("cryotrackynodes");}
std::vector <double> HeliumCVUniverse::GetVector_firstNode_Z() const {return GetVecDouble("cryotrackznodes");}
///////////////////////////////////////////////////
std::vector <double> HeliumCVUniverse::GetVector_lastNode_X() const {return GetVecDouble("cryotrack_lastxnodes");}
std::vector <double> HeliumCVUniverse::GetVector_lastNode_Y() const {return GetVecDouble("cryotrack_lastynodes");}
std::vector <double> HeliumCVUniverse::GetVector_lastNode_Z() const {return GetVecDouble("cryotrack_lastznodes");}
///////////////////////////////////////////////////
std::vector <double> HeliumCVUniverse::Get_RecoilVector_firstNode_X() const {
  auto first_node_x = GetVector_firstNode_X();
  std::vector<double> recoil_first_node_x(first_node_x.begin() + 1, first_node_x.end());
  return recoil_first_node_x;
}
///////////////////////////////////////////////////
std::vector <double> HeliumCVUniverse::Get_RecoilVector_firstNode_Y() const {
  auto first_node_y = GetVector_firstNode_Y();
  std::vector<double> recoil_first_node_y(first_node_y.begin() + 1, first_node_y.end());
  return recoil_first_node_y;}
///////////////////////////////////////////////////
std::vector <double> HeliumCVUniverse::Get_RecoilVector_firstNode_Z() const {
  auto first_node_z = GetVector_firstNode_Z();
  std::vector<double> recoil_first_node_z(first_node_z.begin() + 1, first_node_z.end());
  return recoil_first_node_z;}
///////////////////////////////////////////////////
std::vector <double> HeliumCVUniverse::Get_RecoilVector_lastNode_X() const {
  auto last_node_x = GetVector_lastNode_X();
  std::vector<double> recoil_last_node_x(last_node_x.begin() + 1, last_node_x.end());
  return recoil_last_node_x;}
///////////////////////////////////////////////////
std::vector <double> HeliumCVUniverse::Get_RecoilVector_lastNode_Y() const {
  auto last_node_y = GetVector_lastNode_Y();
  std::vector<double> recoil_last_node_y(last_node_y.begin() + 1, last_node_y.end());
  return recoil_last_node_y;}
///////////////////////////////////////////////////
std::vector <double> HeliumCVUniverse::Get_RecoilVector_lastNode_Z() const {
  auto last_node_z = GetVector_lastNode_Z();
  std::vector<double> recoil_last_node_z(last_node_z.begin() + 1, last_node_z.end());
  return recoil_last_node_z;}
///////////////////////////////////////////////////
Trajector_DATA HeliumCVUniverse::Return_Trajector_DATA_struct() const{
  auto Event_slice = GetEventSliceForData();
  auto muon_firstX = GetMuon_firstNode_X();
  auto muon_firstY = GetMuon_firstNode_Y();
  auto muon_firstZ = GetMuon_firstNode_Z();
  auto muon_LastX = GetMuon_lastNode_X();
  auto muon_LastY = GetMuon_lastNode_Y();
  auto muon_LastZ = GetMuon_lastNode_Z();
  auto shorttrack_Intialnodex = Get_RecoilVector_firstNode_X();
  auto shorttrack_Intialnodey = Get_RecoilVector_firstNode_Y();
  auto shorttrack_Intialnodez = Get_RecoilVector_firstNode_Z();
  auto shorttrack_Finalnodex = Get_RecoilVector_lastNode_X();
  auto shorttrack_Finalnodey = Get_RecoilVector_lastNode_Y();
  auto shorttrack_Finalnodez = Get_RecoilVector_lastNode_Z();
  auto Energy = GetVector_GetNonmuTrkE();
  auto angle = GetVector_NonmuTrkAngleWRTbeamMID();
  auto length = GetVector_GetNonmuTrkLength_InMinerva_Incm();
  Trajector_DATA data_vector{Event_slice, muon_firstX, muon_firstY, muon_firstZ,
                            muon_LastX, muon_LastY, muon_LastZ,
                            shorttrack_Intialnodex, shorttrack_Intialnodey, shorttrack_Intialnodez,
                            shorttrack_Finalnodex, shorttrack_Finalnodey, shorttrack_Finalnodez,
                            Energy, angle, length};
return data_vector;};
///////////////////////////////////////////////////
int HeliumCVUniverse::GetLongAnchorTrackStatus() const{return GetInt("LongAnchorTracksVtxFitStatus");};
int HeliumCVUniverse::GetShortAnchorTrackStatus() const{return GetInt("ShortAnchorTracksVtxFitStatus");};
int HeliumCVUniverse::GetOtherLongTrackStatus() const{return GetInt("OtherLongTracksVtxFitStatus");};
///////////////////////////////////////////////////
int HeliumCVUniverse::GetTracksize() const{return GetInt("tracksize");};
///////////////////////////////////////////////////
TrackType HeliumCVUniverse::GetTrackType() const{
  auto longstatus = GetLongAnchorTrackStatus();
  auto shortstatus = GetShortAnchorTrackStatus();
  auto Otherlongerstatus = GetOtherLongTrackStatus();
  TrackType return_type;
  if(longstatus != -1 && shortstatus ==-1 && Otherlongerstatus==-1 ){return_type = kLong;}
  else if(longstatus == -1 && shortstatus !=-1 && Otherlongerstatus==-1 ){ return_type = kShort;}
  else if(longstatus == -1 && shortstatus == -1 && Otherlongerstatus != -1 ){return_type = kOtherLong;}
  else {return_type = kNotdefinedTrack;}
  return return_type;
  }// end of Function
///////////////////////////////////////////////////
int HeliumCVUniverse::GetTRUE_Tracksize() const{return GetInt("truth_true_tracksize");};
int HeliumCVUniverse::Getindex2ndTrackhighestKE()const{
  int N_trkSize = GetInt("tracksize");
  double highest = 0.0;
  int secondTk_index = -999;
  for (int i = 0; i < N_trkSize; i++) {
    if (GetNonmuTrkE(i) > highest){
      highest = GetNonmuTrkE(i);
      secondTk_index = i;
    } // if found highest E
  }// end of loop
  if(secondTk_index==-999){return -999;}
  return secondTk_index;
}// end of function
///////////////////////////////////////////////////
int HeliumCVUniverse::Getindex2ndTrack_TRUE_highestKE()const{
  int N_trkSize = GetInt("tracksize");
  double highest = 0.0;
  int secondTk_index = -999;
  for (int i = 0; i < N_trkSize; i++) {
    if (GetTRUENonmuTrkE(i) > highest){
      highest = GetTRUENonmuTrkE(i);
      secondTk_index = i;
    } // if found highest E
  }
  if(secondTk_index==-999){return -999;}
  return secondTk_index;
}//END of function
//////////////////////////////////////////////////////////////////////////
//Get TRUTH Info
//////////////////////////////////////////////////////////////////////////
double HeliumCVUniverse::GetTRUE_Emu()                    const { return GetDouble("truth_true_muon_E")*.001; }
double HeliumCVUniverse::GetTRUE_Pmu()                    const { return sqrt(pow(GetTRUE_Emu(),2.0) - pow(HeliumConsts::MUON_MASS_GEV,2.0)); }
double HeliumCVUniverse::GetTRUE_PZmu()                   const { return GetVecElem("mc_primFSLepton",2)* .001;}
///////////////////////////////////////////////////
double HeliumCVUniverse::GetTRUE_muANGLE_WRTB_DEG() const{return GetDouble("truth_true_muon_theta") * TMath::RadToDeg(); }
double HeliumCVUniverse::GetTRUE_muANGLE_WRTB_rad() const{return GetDouble("truth_true_muon_theta") ;}
///////////////////////////////////////////////////
double HeliumCVUniverse::GetTRUE_PTmu() const
{
  double px = GetVecElem("mc_primFSLepton",0)* .001;
  double py = GetVecElem("mc_primFSLepton",1)* .001;
  double pT =sqrt(pow(px,2)+pow(py,2));
  return pT;
};
///////////////////////////////////////////////////
double HeliumCVUniverse::GetTRUE_Vertex_x() const{return GetVecElem("mc_vtx",0);};
double HeliumCVUniverse::GetTRUE_Vertex_y() const{return GetVecElem("mc_vtx",1);};
double HeliumCVUniverse::GetTRUE_Vertex_z() const{return GetVecElem("mc_vtx",2);};
///////////////////////////////////////////////////
Vertex_XYZ HeliumCVUniverse::GetTRUE_Vertex3Dpoint() const{
  auto x = GetTRUE_Vertex_x();
  auto y = GetTRUE_Vertex_y();
  auto z = GetTRUE_Vertex_z();
  Vertex_XYZ Point{x,y,z};
  return Point;
};

///////////////////////////////////////////////////
double HeliumCVUniverse::GetTRUE_Vertex_r()                 const{
  double x = HeliumCVUniverse::GetTRUE_Vertex_x() ;
  double y = HeliumCVUniverse::GetTRUE_Vertex_y() ;
  double r = sqrt(pow(x,2)+ pow(y,2));
  return r ;
};
///////////////////////////////////////////////////
double HeliumCVUniverse::GetTRUE_Vertex_rr()                  const{
  double x = HeliumCVUniverse::GetTRUE_Vertex_x() ;
  double y = HeliumCVUniverse::GetTRUE_Vertex_y() ;
  double rr = pow(x,2)+ pow(y,2);
  return rr;
};
///////////////////////////////////////////////////
CryoTank_REGIONS HeliumCVUniverse::Get_TRUE_CryoTank_region() const{
  double Z = HeliumCVUniverse::GetTRUE_Vertex_z();
  CryoTank_REGIONS region = Region_of_CryoTank(Z);
  return region;
}
///////////////////////////////////////////////////
double HeliumCVUniverse::GetTRUE_Phimu() const{return GetDouble("truth_FSlepton_Phi");};
int  HeliumCVUniverse::GetIntactionType()const{ return GetInt("mc_intType");};
int  HeliumCVUniverse::GetTargetType()   const{ return GetInt("mc_targetZ");};

int  HeliumCVUniverse::GetNon_muon_PDG(int TRKNum)const{ return GetVecElem("truth_nonmu_PDG",TRKNum);};
///////////////////////////////////////////////////
int  HeliumCVUniverse::GetPDG_2ndTrk_highestEnergy() const{
  int TRKNum = HeliumCVUniverse::Getindex2ndTrackhighestKE();
  return HeliumCVUniverse::GetNon_muon_PDG(TRKNum);};
  ///////////////////////////////////////////////////
int  HeliumCVUniverse::GetPDG_2ndTrk_highestTRUEEnergy() const{
  int TRKNum = HeliumCVUniverse::Getindex2ndTrack_TRUE_highestKE();
  return HeliumCVUniverse::GetNon_muon_PDG(TRKNum);};
  ///////////////////////////////////////////////////
double HeliumCVUniverse::ThetaWRTBeam(double x , double y, double z, double bias) const {
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
////////////////////////////////////////////////////////////////////////////////////////////////////
///Truth Information
////////////////////////////////////////////////////////////////////////////////////////////////////
int  HeliumCVUniverse::Get_mc_incoming() const{ return GetInt("mc_incoming");}
int  HeliumCVUniverse::Get_mc_current()  const{ return GetInt("mc_current");}
double HeliumCVUniverse::GetTRUE_NonmuTrkE(int TRKNum)           const{return GetVecElem("truth_nonmuKE",TRKNum) * .001;} //GeV
double HeliumCVUniverse::GetTRUE_NonmuTrkopenangle(int TRKNum)   const{return GetVecElem("truth_opening_angle",TRKNum)* TMath::RadToDeg();}
double HeliumCVUniverse::GetTRUE_NonmuTrkANGLE_WRTB(int TRKNum)  const{return GetVecElem("truth_nonmu_angleWRTB",TRKNum)* TMath::RadToDeg();}
double HeliumCVUniverse::GetTRUE_nonMuonDOCA(int TRKNum)         const{return GetVecElem("truth_nonmu_DOCA",TRKNum);}
double HeliumCVUniverse::GetTRUE_nonMuoncolumnarDensity(int TRKNum) const{return GetVecElem("truth_nonmu_columnarDensity",TRKNum);}
int    HeliumCVUniverse::GetTRUE_NonmuTrk_PDG_Parent(int TRKNum)    const{return GetVecElem("truth_nonmu_PDG_Parent",TRKNum);};
std::vector <int> HeliumCVUniverse::GETvector_PDG_FS_particles()    const{ return GetVecInt("mc_FSPartPDG");}
std::vector <double> HeliumCVUniverse::GETvector_Energy_mc_FS_particles() const{ return GetVecDouble("mc_FSPartE");}
std::vector <int> HeliumCVUniverse::Get_TRUE_vector_ALL_Event_PDG()       const {return GetVecInt("mc_er_ID");}
///////////////////////////////////////////////////
int  HeliumCVUniverse::Get_TRUE_Mother_index()        const{ return GetInt("mc_er_mother");};
int  HeliumCVUniverse::Get_TRUE_firstdaughter_index() const{ return GetInt("mc_er_FD");};
int  HeliumCVUniverse::Get_TRUE_lastdaughter_index()  const{ return GetInt("mc_er_LD");};
///////////////////////////////////////////////////
std::vector <int> HeliumCVUniverse::Get_TRUE_indexs() const {
  std::vector <int> vector;
  auto mother = Get_TRUE_Mother_index();
  auto first_daughter = Get_TRUE_firstdaughter_index();
  auto last_daughter =Get_TRUE_lastdaughter_index();
  vector.push_back(mother);
  vector.push_back(first_daughter);
  vector.push_back(last_daughter);
  return vector;}
  ////////////////////////////////////////////////
  std::vector <double> HeliumCVUniverse::MakeTRUE_VectorTrackLengthinMinerva_mm() const {

    std::vector<Vertex_XYZ> NpointVector_FS_particles = Construct_EndPointvector_ForTRUE_FS_particle();
    Vertex_XYZ VertexP = GetTRUE_Vertex3Dpoint();
    std::vector<parameterizationEquation_params_bare> PARS_equation_lines = MakeParameterize_bare_lineParasFromPoints(VertexP,  NpointVector_FS_particles);
    std::vector<double> t_vector = FindVector_TforParameterizeLinesAtZ(PARS_equation_lines, True_Start_Znode );
    std::vector<Vertex_XYZ> True_Start_nodes = GetTrueMinervaStartPostion(PARS_equation_lines, t_vector, True_Start_Znode);
    std::vector<double>  Distance = FindDistance_vector(True_Start_nodes, NpointVector_FS_particles );
    return Distance;
  }

  std::vector <double> HeliumCVUniverse::MakeTRUE_VectorTrackLengthinMinerva_cm() const{
    auto vector = MakeTRUE_VectorTrackLengthinMinerva_mm();
    std::vector <double> output_vector;
    for(auto cat :vector ){
      output_vector.push_back(cat*.1); // to cm
    }
    return output_vector;

  }



///////////////////////////////////////////////////
std::vector <double> HeliumCVUniverse::GETvector_KE_mc_FS_particles_MeV( TDatabasePDG *pdg_DATABASEobject )const{
  auto Total_E_particles = GETvector_Energy_mc_FS_particles();
  auto pdg = GETvector_PDG_FS_particles();
  std::vector<double> KE_particle;
  if(Total_E_particles.size() != pdg.size() ){
    assert(false && "Error Size of Vectors for PDG_energy and PDG list are different sizes: NOT GOOD" );
  }
  int i=0;
  for(auto cat : pdg ){
    //std::cout<<" pdg = "<< cat <<std::endl;
    double KE = -999;
    double mass = -9999;
    if (cat == 1000130270)       {mass = 26.90*931.49;} //27Al //MeV
    else if (cat == 1000020040)   {mass = 3.72*931.49;} //4He //MeV
    else if (cat == 1000020030)   {mass = 3.02*931.49;} //3He //MeV
    else if (cat == 1000010020)   {mass = 2.01*931.49;} //2 deuterium //MeV
    else if (cat == 1000010060)   {mass = 15.99*931.49;} //16Oxygen) //MeV
    else if (cat == 1000030060)   {mass = 6.02*931.49;} //Li6 //MeV
    else if (cat == 2000000101)   {mass=0;}
    else{
      auto Particle_type =  pdg_DATABASEobject->GetParticle(cat);
      mass = Particle_type->Mass()*1000;
      //std::cout<<"PDG = "<< cat <<" totalE = "<< Total_E_particles.at(i) <<" Mass [MeV]= "<< mass<<std::endl;
      //KE = Total_E_particles.at(i) - Particle_type->Mass()*1000; // Must convert the Mass GeV to MeV
    }
    double totalE = Total_E_particles.at(i);
    totalE = round( totalE * 100.0 ) / 100.0;
    mass = round( mass * 100.0 ) / 100.0;
    KE = totalE - mass;
    if(mass == -9999 || KE==-999){assert(false && "FAILED TO FIND mass and calculate KE" );}
    if(KE < 0){std::cout<<"This has a Neg KE ,Thats Weird!! the pdg = "<< cat<<std::endl; }
      //std::cout<<"[FAILURE] KE is Neg KE = "<< KE << std::endl;assert(false && "KE NEG"); }
    KE_particle.push_back(KE);
    i++;
  }
  return KE_particle;
}// end of function
///////////////////////////////////////////////////
std::vector <double> HeliumCVUniverse::GETvector_KE_mc_FS_particles_GeV(TDatabasePDG *pdg_DATABASEobject)const{
  auto KE_pdgvector = GETvector_KE_mc_FS_particles_MeV(pdg_DATABASEobject );
  std::vector<double> KE_GeV_vector;
  for(auto cat : KE_pdgvector){
    KE_GeV_vector.push_back(cat*.001);
  }
  return KE_GeV_vector;
}//end of function
///////////////////////////////////////////////////
int HeliumCVUniverse::Get_Index_highestKE_mc_FSPart() const {
  auto KE_vector = GETvector_Energy_mc_FS_particles_MeVtoGeV();
  auto pdg_vector = GETvector_PDG_FS_particles();
  int secondTk_index =0;
  if(pdg_vector.size()==1) return 0;
  else if(pdg_vector.size()==2) return 1;
  else {
    int start = 0;
    if(pdg_vector[0] == 13){start = 1;}
    int N_size= KE_vector.size();
    double highest = -999;
    for (int i = start; i < N_size; i++) {
      if (KE_vector.at(i) > highest){
        highest = KE_vector.at(i);
        secondTk_index = i;
      } // if found highest E
    }
  }

  if(secondTk_index==-999){return -999;}
  return secondTk_index;
}
///////////////////////////////////////////////////
int HeliumCVUniverse::Get_Index_highestKE_mc_FSPart_WithDeglessthan(double Angle,
  std::vector<double> KE_vector, std::vector<double> angle_vector, std::vector<int> pdg_vector) const {
    int secondTk_index =0;
    if(pdg_vector.size()==1) return 0;
    else if(pdg_vector.size()==2) return 1;
    else {
      int start = 0;
      if(pdg_vector[0] == 13){start = 1;}
      int N_size= KE_vector.size();
      double highest = -999;
      for (int i = start; i < N_size; i++) {
        if (KE_vector.at(i) > highest && angle_vector.at(i) < Angle  ){
          highest = KE_vector.at(i);
          secondTk_index = i;
        } // if found highest E
      }
    }
    if(secondTk_index==-999){return -999;}
    return secondTk_index;
  }// end of function
///////////////////////////////////////////////////
int HeliumCVUniverse::Get_Index_highestKE_mc_FSPart_WithDeglessthan_NO_NeutralParticles(double Angle,
  std::vector<double> KE_vector, std::vector<double> angle_vector, std::vector<int> pdg_vector  ) const {
    int secondTk_index = -999;
    if(pdg_vector.size()==1){ return 0;}
  else if(pdg_vector.size()==2 &&
    angle_vector.at(1) < Angle &&
    Helium_PDG::pdg_Pi0 != pdg_vector.at(1) &&
    Helium_PDG::pdg_neutron != pdg_vector.at(1) &&
    Helium_PDG::pdg_antineutron!= pdg_vector.at(1) &&
    Helium_PDG::pdg_Genie_bindingE!= pdg_vector.at(1) &&
    Helium_PDG::pdg_Sigma0!= pdg_vector.at(1)&&
    Helium_PDG::pdg_antiSigma0!= pdg_vector.at(1) &&
    Helium_PDG::pdg_Nu_e!= pdg_vector.at(1) &&
    Helium_PDG::pdg_Nu_mu!= pdg_vector.at(1) &&
    Helium_PDG::pdg_Lambda0!= pdg_vector.at(1) &&
    Helium_PDG::pdg_antiLambda0 != pdg_vector.at(1) &&
    Helium_PDG::pdg_Photon != pdg_vector.at(1))
    {return 1;}

  else if(pdg_vector.size()>2)
  {
    int start = 0;
    if(pdg_vector[0] == 13){start = 1;}

    int N_size= KE_vector.size();
    double highest = -999;
    for (int i = start; i < N_size; i++) {
      if (KE_vector.at(i) > highest &&
      angle_vector.at(i) < Angle &&
      Helium_PDG::pdg_Pi0 != pdg_vector.at(i) &&
      Helium_PDG::pdg_neutron != pdg_vector.at(i)&&
      Helium_PDG::pdg_antineutron!= pdg_vector.at(i)&&
      Helium_PDG::pdg_Genie_bindingE!= pdg_vector.at(i) &&
      Helium_PDG::pdg_Sigma0!= pdg_vector.at(i) &&
      Helium_PDG::pdg_antiSigma0!= pdg_vector.at(i) &&
      Helium_PDG::pdg_Nu_e!= pdg_vector.at(i) &&
      Helium_PDG::pdg_Nu_mu!= pdg_vector.at(i) &&
      Helium_PDG::pdg_Lambda0!= pdg_vector.at(i) &&
      Helium_PDG::pdg_Photon != pdg_vector.at(i) &&
      Helium_PDG::pdg_antiLambda0 != pdg_vector.at(i))
      {
        highest = KE_vector.at(i);
        secondTk_index = i;
      } // if found highest E
    }
  }
  if(secondTk_index==-999){return -999;}
  return secondTk_index;
}// end of function
///////////////////////////////////////////////////

int HeliumCVUniverse::Get_Index_highestKE_mc_FSPart_NO_NeutralParticles(
                                    std::vector<double> KE_vector, std::vector<int> pdg_vector,
                                    std::vector<double> truedigitEfraction_vector)
                                     const {
    int secondTk_index = -999;

    if(pdg_vector.size()==1 && -9999 != pdg_vector.at(0)){ return 0;}

    else if(pdg_vector.size()==2 &&
     Helium_PDG::pdg_Pi0 != pdg_vector.at(1) &&
     Helium_PDG::pdg_neutron != pdg_vector.at(1) &&
     Helium_PDG::pdg_antineutron!= pdg_vector.at(1) &&
     Helium_PDG::pdg_Genie_bindingE!= pdg_vector.at(1) &&
     Helium_PDG::pdg_Sigma0!= pdg_vector.at(1)&&
     Helium_PDG::pdg_antiSigma0!= pdg_vector.at(1) &&
     Helium_PDG::pdg_Nu_e!= pdg_vector.at(1) &&
     Helium_PDG::pdg_Nu_mu!= pdg_vector.at(1) &&
     Helium_PDG::pdg_Lambda0!= pdg_vector.at(1) &&
     Helium_PDG::pdg_antiLambda0 != pdg_vector.at(1) &&
     Helium_PDG::pdg_Photon != pdg_vector.at(1) &&
     -9999 != pdg_vector.at(1) &&
     TRUTH_EnergyFraction_AreTrueDigits(truedigitEfraction_vector,1 ) == true
   )

   {return 1;}

   else if(pdg_vector.size()>2)
   {
     int start = 0;
     if(pdg_vector[0] == 13 || pdg_vector[0] == -9999 ){start = 1;}

     int N_size= KE_vector.size();
     double highest = -999;

     for (int i = start; i < N_size; i++) {
       if (KE_vector.at(i) > highest &&
       Helium_PDG::pdg_Pi0 != pdg_vector.at(i) &&
       Helium_PDG::pdg_neutron != pdg_vector.at(i)&&
       Helium_PDG::pdg_antineutron!= pdg_vector.at(i)&&
       Helium_PDG::pdg_Genie_bindingE!= pdg_vector.at(i) &&
       Helium_PDG::pdg_Sigma0!= pdg_vector.at(i) &&
       Helium_PDG::pdg_antiSigma0!= pdg_vector.at(i) &&
       Helium_PDG::pdg_Nu_e!= pdg_vector.at(i) &&
       Helium_PDG::pdg_Nu_mu!= pdg_vector.at(i) &&
       Helium_PDG::pdg_Lambda0!= pdg_vector.at(i) &&
       Helium_PDG::pdg_Photon != pdg_vector.at(i) &&
       Helium_PDG::pdg_antiLambda0 != pdg_vector.at(i) &&
       -9999 != pdg_vector.at(i) &&
       TRUTH_EnergyFraction_AreTrueDigits(truedigitEfraction_vector,i ) == true
     )
     {
       highest = KE_vector.at(i);
       secondTk_index = i;
     } // if found highest E
   }
 }

 if(secondTk_index==-999){return -999;}
 return secondTk_index;
}// end of function


//////////////////////////////////////////////////
int HeliumCVUniverse::Get_Index_highestKE_mc_FSPart_NO_NeutralParticlesForTruthBranch( std::vector<double> KE_vector,
  std::vector<int> pdg_vector) const {
    int secondTk_index = -999;
    if(pdg_vector.size()==1){ return 0;}
    else if(pdg_vector.size()==2 &&
    Helium_PDG::pdg_Pi0 != pdg_vector.at(1) &&
    Helium_PDG::pdg_neutron != pdg_vector.at(1) &&
    Helium_PDG::pdg_antineutron!= pdg_vector.at(1) &&
    Helium_PDG::pdg_Genie_bindingE!= pdg_vector.at(1) &&
    Helium_PDG::pdg_Sigma0!= pdg_vector.at(1)&&
    Helium_PDG::pdg_antiSigma0!= pdg_vector.at(1) &&
    Helium_PDG::pdg_Nu_e!= pdg_vector.at(1) &&
    Helium_PDG::pdg_Nu_mu!= pdg_vector.at(1) &&
    Helium_PDG::pdg_Lambda0!= pdg_vector.at(1) &&
    Helium_PDG::pdg_antiLambda0 != pdg_vector.at(1) &&
    Helium_PDG::pdg_Photon != pdg_vector.at(1)
  )
    {return 1;} // the muon should be element 0

  else if(pdg_vector.size()>2)
  {
    int start = 0;
    if(pdg_vector.at(0) == 13){start = 1;}

    int N_size= KE_vector.size();
    double highest = -999;
    for (int i = start; i < N_size; i++) {
      if (KE_vector.at(i) > highest &&
      Helium_PDG::pdg_Pi0 != pdg_vector.at(i) &&
      Helium_PDG::pdg_neutron != pdg_vector.at(i)&&
      Helium_PDG::pdg_antineutron!= pdg_vector.at(i)&&
      Helium_PDG::pdg_Genie_bindingE!= pdg_vector.at(i) &&
      Helium_PDG::pdg_Sigma0!= pdg_vector.at(i) &&
      Helium_PDG::pdg_antiSigma0!= pdg_vector.at(i) &&
      Helium_PDG::pdg_Nu_e!= pdg_vector.at(i) &&
      Helium_PDG::pdg_Nu_mu!= pdg_vector.at(i) &&
      Helium_PDG::pdg_Lambda0!= pdg_vector.at(i) &&
      Helium_PDG::pdg_Photon != pdg_vector.at(i) &&
      Helium_PDG::pdg_antiLambda0 != pdg_vector.at(i)
    )
      {
        highest = KE_vector.at(i);
        secondTk_index = i;
      } // if found highest E
    }


  }

  if(secondTk_index==-999){return -999;}
  return secondTk_index;
}// end of function

///////////////////////////////////////////////////
int HeliumCVUniverse::Get_Index_highestKE_mc_FSPart_WithDeglessthan_NO_NeutralParticles_withKEpion_proton(double Angle,
  std::vector<double> KE_vector,
  std::vector<double> angle_vector,
  std::vector<int> pdg_vector,
  std::vector<double> truedigitEfraction_vector ,
  double KE_pion,
  double KE_proton)
  const {
    int secondTk_index = -999;

    if(pdg_vector.size()==1 && TRUTH_EnergyFraction_AreTrueDigits(truedigitEfraction_vector,0 ) == true && -9999 != pdg_vector.at(0) ){ return 0;}
    else if(pdg_vector.size()==2 &&
    angle_vector.at(1) < Angle &&
    Helium_PDG::pdg_Pi0 != pdg_vector.at(1) &&
    Helium_PDG::pdg_neutron != pdg_vector.at(1)&&
    Helium_PDG::pdg_antineutron!= pdg_vector.at(1)&&
    Helium_PDG::pdg_Genie_bindingE!= pdg_vector.at(1) &&
    Helium_PDG::pdg_Sigma0!= pdg_vector.at(1)&&
    Helium_PDG::pdg_antiSigma0!= pdg_vector.at(1) &&
    Helium_PDG::pdg_Nu_e!= pdg_vector.at(1) &&
    Helium_PDG::pdg_Nu_mu!= pdg_vector.at(1) &&
    Helium_PDG::pdg_Lambda0!= pdg_vector.at(1) &&
    Helium_PDG::pdg_antiLambda0 != pdg_vector.at(1) &&
    Helium_PDG::pdg_Photon != pdg_vector.at(1) &&
    -9999 != pdg_vector.at(1) &&
    TRUTH_EnergyFraction_AreTrueDigits(truedigitEfraction_vector,1 ) == true
  )
  {
    if(pdg_vector.at(1)== Helium_PDG::pdg_Proton && KE_vector.at(1) > KE_proton ){return 1;}
    else if((pdg_vector.at(1) == Helium_PDG::pdg_Pion_pos || pdg_vector.at(1) == Helium_PDG::pdg_Pion_neg) && KE_vector.at(1) > KE_pion){return 1;}
    else if(pdg_vector.at(1) != Helium_PDG::pdg_Pion_pos &&  pdg_vector.at(1) != Helium_PDG::pdg_Pion_neg && pdg_vector.at(1) != Helium_PDG::pdg_Proton){return 1;}
  }
  else if(pdg_vector.size()>2) {
    int start = 0;
    if(pdg_vector[0] == 13){start = 1;}

    int N_size= KE_vector.size();
    double highest = -999;
    for (int i = start; i < N_size; i++) {
      if (KE_vector.at(i) > highest &&
      angle_vector.at(i) < Angle &&
      Helium_PDG::pdg_Pi0 != pdg_vector.at(i) &&
      Helium_PDG::pdg_neutron != pdg_vector.at(i)&&
      Helium_PDG::pdg_antineutron!= pdg_vector.at(i)&&
      Helium_PDG::pdg_Genie_bindingE!= pdg_vector.at(i) &&
      Helium_PDG::pdg_Sigma0!= pdg_vector.at(i) &&
      Helium_PDG::pdg_antiSigma0!= pdg_vector.at(i) &&
      Helium_PDG::pdg_Nu_e!= pdg_vector.at(i) &&
      Helium_PDG::pdg_Nu_mu!= pdg_vector.at(i) &&
      Helium_PDG::pdg_Lambda0!= pdg_vector.at(i) &&
      Helium_PDG::pdg_antiLambda0 != pdg_vector.at(i) &&
      Helium_PDG::pdg_Photon != pdg_vector.at(i) &&
      -9999 != pdg_vector.at(i) &&
      TRUTH_EnergyFraction_AreTrueDigits(truedigitEfraction_vector,i ) == true)
      {
        if(pdg_vector.at(i)== Helium_PDG::pdg_Proton && KE_vector.at(i) > KE_proton ){
          highest = KE_vector.at(i);
          secondTk_index = i;
        }
        else if((pdg_vector.at(i) == Helium_PDG::pdg_Pion_pos || pdg_vector.at(i) == Helium_PDG::pdg_Pion_neg) && KE_vector.at(i) > KE_pion){
          highest = KE_vector.at(i);
          secondTk_index = i;
        }
        else if(pdg_vector.at(i) != Helium_PDG::pdg_Pion_pos &&  pdg_vector.at(i) != Helium_PDG::pdg_Pion_neg && pdg_vector.at(i) != Helium_PDG::pdg_Proton){
          highest = KE_vector.at(i);
          secondTk_index = i;
        }
      } // if found highest E
    }//for loop
  }// more than 2 pdg if
  if(secondTk_index==-999){return -999;}
  return secondTk_index;
} // end of function
///////////////////////////////////////////////////
int HeliumCVUniverse::Get_Index_highestKE_mc_FSPart_WithDeglessthan_NO_NeutralParticles_withKEpion_proton(double Angle,
  std::vector<double> KE_vector,
  std::vector<double> angle_vector,
  std::vector<int> pdg_vector,
  double KE_pion,
  double KE_proton)
  const {
    int secondTk_index = -999;

    if(pdg_vector.size()==1 ){ return 0;}
    else if(pdg_vector.size()==2 &&
    angle_vector.at(1) < Angle &&
    Helium_PDG::pdg_Pi0 != pdg_vector.at(1) &&
    Helium_PDG::pdg_neutron != pdg_vector.at(1)&&
    Helium_PDG::pdg_antineutron!= pdg_vector.at(1)&&
    Helium_PDG::pdg_Genie_bindingE!= pdg_vector.at(1) &&
    Helium_PDG::pdg_Sigma0!= pdg_vector.at(1)&&
    Helium_PDG::pdg_antiSigma0!= pdg_vector.at(1) &&
    Helium_PDG::pdg_Nu_e!= pdg_vector.at(1) &&
    Helium_PDG::pdg_Nu_mu!= pdg_vector.at(1) &&
    Helium_PDG::pdg_Lambda0!= pdg_vector.at(1) &&
    Helium_PDG::pdg_antiLambda0 != pdg_vector.at(1) &&
    Helium_PDG::pdg_Photon != pdg_vector.at(1) &&
    -9999 != pdg_vector.at(1)
  )
  {
    if(pdg_vector.at(1)== Helium_PDG::pdg_Proton && KE_vector.at(1) > KE_proton ){return 1;}
    else if((pdg_vector.at(1) == Helium_PDG::pdg_Pion_pos || pdg_vector.at(1) == Helium_PDG::pdg_Pion_neg) && KE_vector.at(1) > KE_pion){return 1;}
    else if(pdg_vector.at(1) != Helium_PDG::pdg_Pion_pos &&  pdg_vector.at(1) != Helium_PDG::pdg_Pion_neg && pdg_vector.at(1) != Helium_PDG::pdg_Proton){return 1;}
  }

  else if(pdg_vector.size()>2) {
    int start = 0;
    if(pdg_vector[0] == 13){start = 1;}

    int N_size= KE_vector.size();
    double highest = -999;
    for (int i = start; i < N_size; i++) {
      if (KE_vector.at(i) > highest &&
      angle_vector.at(i) < Angle &&
      Helium_PDG::pdg_Pi0 != pdg_vector.at(i) &&
      Helium_PDG::pdg_neutron != pdg_vector.at(i)&&
      Helium_PDG::pdg_antineutron!= pdg_vector.at(i)&&
      Helium_PDG::pdg_Genie_bindingE!= pdg_vector.at(i) &&
      Helium_PDG::pdg_Sigma0!= pdg_vector.at(i) &&
      Helium_PDG::pdg_antiSigma0!= pdg_vector.at(i) &&
      Helium_PDG::pdg_Nu_e!= pdg_vector.at(i) &&
      Helium_PDG::pdg_Nu_mu!= pdg_vector.at(i) &&
      Helium_PDG::pdg_Lambda0!= pdg_vector.at(i) &&
      Helium_PDG::pdg_antiLambda0 != pdg_vector.at(i) &&
      Helium_PDG::pdg_Photon != pdg_vector.at(i) &&
      -9999 != pdg_vector.at(i)

    )
    {
      if(pdg_vector.at(i)== Helium_PDG::pdg_Proton && KE_vector.at(i) > KE_proton ){
        highest = KE_vector.at(i);
        secondTk_index = i;
      }
      else if((pdg_vector.at(i) == Helium_PDG::pdg_Pion_pos || pdg_vector.at(i) == Helium_PDG::pdg_Pion_neg) && KE_vector.at(i) > KE_pion){
        highest = KE_vector.at(i);
        secondTk_index = i;
      }
      else if(pdg_vector.at(i) != Helium_PDG::pdg_Pion_pos &&  pdg_vector.at(i) != Helium_PDG::pdg_Pion_neg && pdg_vector.at(i) != Helium_PDG::pdg_Proton){
        highest = KE_vector.at(i);
        secondTk_index = i;
      }


    } // if found highest E
  }//for loop
}// more than 2 pdg if
if(secondTk_index==-999){return -999;}
return secondTk_index;
}
///////////////////////////////////////////////////
int HeliumCVUniverse::Get_Index_highestKE_NOleadingMuoninlist_WithDeglessthan_NO_NeutralParticles(double Angle,
   std::vector<double> KE_vector, std::vector<double> angle_vector, std::vector<int> pdg_vector , std::vector<double> truedigitEfraction_vector  ) const {
  int secondTk_index = -999;

   if( pdg_vector.size()== 2 &&
       angle_vector.at(1) < Angle &&
       Helium_PDG::pdg_Pi0 != pdg_vector.at(1) &&
       Helium_PDG::pdg_neutron != pdg_vector.at(1)&&
       Helium_PDG::pdg_antineutron!= pdg_vector.at(1)&&
       Helium_PDG::pdg_Genie_bindingE!= pdg_vector.at(1) &&
       Helium_PDG::pdg_Sigma0!= pdg_vector.at(1)&&
       Helium_PDG::pdg_antiSigma0!= pdg_vector.at(1) &&
       Helium_PDG::pdg_Nu_e!= pdg_vector.at(1) &&
       Helium_PDG::pdg_Nu_mu!= pdg_vector.at(1) &&
       Helium_PDG::pdg_Lambda0!= pdg_vector.at(1) &&
       Helium_PDG::pdg_antiLambda0 != pdg_vector.at(1) &&
       Helium_PDG::pdg_Photon != pdg_vector.at(1) &&
       -9999 != pdg_vector.at(1) &&
       TRUTH_EnergyFraction_AreTrueDigits(truedigitEfraction_vector,1 ) == true)
     { return 1;}
     else if(pdg_vector.size() > 2) {
       int N_size= KE_vector.size();
       double highest = -999;

       for (unsigned int i = 1; i < N_size; i++) {
         if (KE_vector.at(i) > highest &&
         angle_vector.at(i) < Angle &&
         Helium_PDG::pdg_Pi0 != pdg_vector.at(i) &&
         Helium_PDG::pdg_neutron != pdg_vector.at(i)&&
         Helium_PDG::pdg_antineutron!= pdg_vector.at(i)&&
         Helium_PDG::pdg_Genie_bindingE!= pdg_vector.at(i) &&
         Helium_PDG::pdg_Sigma0!= pdg_vector.at(i) &&
         Helium_PDG::pdg_antiSigma0!= pdg_vector.at(i) &&
         Helium_PDG::pdg_Nu_e!= pdg_vector.at(i) &&
         Helium_PDG::pdg_Nu_mu!= pdg_vector.at(i) &&
         Helium_PDG::pdg_Lambda0!= pdg_vector.at(i) &&
         Helium_PDG::pdg_antiLambda0 != pdg_vector.at(i) &&
         Helium_PDG::pdg_Photon != pdg_vector.at(i) &&
         -9999 != pdg_vector.at(i) &&
         TRUTH_EnergyFraction_AreTrueDigits(truedigitEfraction_vector,i) == true)
         {
           highest = KE_vector.at(i);
           secondTk_index = i;
           
         } // if found highest E
       }
     }
     if(secondTk_index==-999){return -999;}
     return secondTk_index;
   }
///////////////////////////////////////////////////
int HeliumCVUniverse::Get_Index_highestKE_NOleadingMuoninlist_WithDeglessthan_NO_NeutralParticles_WithProton_pionKEthreshold(double Angle,
    std::vector<double> KE_vector, std::vector<double> angle_vector, std::vector<int> pdg_vector, std::vector<double> truedigitEfraction_vector ,double KE_pion, double KE_proton ) const {
   int secondTk_index = -999;

    if( pdg_vector.size()== 2 &&
        angle_vector.at(1) < Angle &&
        Helium_PDG::pdg_Pi0 != pdg_vector.at(1) &&
        Helium_PDG::pdg_neutron != pdg_vector.at(1)&&
        Helium_PDG::pdg_antineutron!= pdg_vector.at(1)&&
        Helium_PDG::pdg_Genie_bindingE!= pdg_vector.at(1) &&
        Helium_PDG::pdg_Sigma0!= pdg_vector.at(1)&&
        Helium_PDG::pdg_antiSigma0!= pdg_vector.at(1) &&
        Helium_PDG::pdg_Nu_e!= pdg_vector.at(1) &&
        Helium_PDG::pdg_Nu_mu!= pdg_vector.at(1) &&
        Helium_PDG::pdg_Lambda0!= pdg_vector.at(1) &&
        Helium_PDG::pdg_antiLambda0 != pdg_vector.at(1) &&
        Helium_PDG::pdg_Photon != pdg_vector.at(1) &&
        -9999 != pdg_vector.at(1) &&
        TRUTH_EnergyFraction_AreTrueDigits(truedigitEfraction_vector,1 ) == true
      )
      {   if(pdg_vector.at(1)== Helium_PDG::pdg_Proton && KE_vector.at(1) > KE_proton ){return 1;}
        else if((pdg_vector.at(1) == Helium_PDG::pdg_Pion_pos || pdg_vector.at(1) == Helium_PDG::pdg_Pion_neg) && KE_vector.at(1) > KE_pion){return 1;}
        else if(pdg_vector.at(1) != Helium_PDG::pdg_Pion_pos &&  pdg_vector.at(1) != Helium_PDG::pdg_Pion_neg && pdg_vector.at(1) != Helium_PDG::pdg_Proton){return 1;}
      }// END of IF
      else if(pdg_vector.size() > 2) {
        int N_size= KE_vector.size();
        double highest = -999;
        for (unsigned int i = 1; i < N_size; i++) {
          if (KE_vector.at(i) > highest &&
          angle_vector.at(i) < Angle &&
          Helium_PDG::pdg_Pi0 != pdg_vector.at(i) &&
          Helium_PDG::pdg_neutron != pdg_vector.at(i)&&
          Helium_PDG::pdg_antineutron!= pdg_vector.at(i)&&
          Helium_PDG::pdg_Genie_bindingE!= pdg_vector.at(i) &&
          Helium_PDG::pdg_Sigma0!= pdg_vector.at(i) &&
          Helium_PDG::pdg_antiSigma0!= pdg_vector.at(i) &&
          Helium_PDG::pdg_Nu_e!= pdg_vector.at(i) &&
          Helium_PDG::pdg_Nu_mu!= pdg_vector.at(i) &&
          Helium_PDG::pdg_Lambda0!= pdg_vector.at(i) &&
          Helium_PDG::pdg_antiLambda0 != pdg_vector.at(i) &&
          Helium_PDG::pdg_Photon != pdg_vector.at(i) &&
          -9999 != pdg_vector.at(i) &&
          TRUTH_EnergyFraction_AreTrueDigits(truedigitEfraction_vector,i ) == true
        )
        {
          if(pdg_vector.at(i)== Helium_PDG::pdg_Proton && KE_vector.at(i) > KE_proton ){
            highest = KE_vector.at(i);
            secondTk_index = i;
          }
          else if((pdg_vector.at(i) == Helium_PDG::pdg_Pion_pos || pdg_vector.at(i) == Helium_PDG::pdg_Pion_neg) && KE_vector.at(i) > KE_pion){
            highest = KE_vector.at(i);
            secondTk_index = i;
          }
          else if(pdg_vector.at(i) != Helium_PDG::pdg_Pion_pos &&  pdg_vector.at(i) != Helium_PDG::pdg_Pion_neg && pdg_vector.at(i) != Helium_PDG::pdg_Proton){
            highest = KE_vector.at(i);
            secondTk_index = i;
          }
        } // if found highest E
      }
    }
    if(secondTk_index==-999){return -999;}
    return secondTk_index;
  }
///////////////////////////////////////////////////
int HeliumCVUniverse::Returnindex_True_2ndTk_GreatestKE_lessthanAngle(std::vector<int> PDG_trklist, std::vector<double> Energy_trklist, std::vector <double> Angle_trklist ) const{

  int secondTrk = 999;
  if(PDG_trklist.size()==0){std::cout<<"Error Only Muon Trk no Secondary Trk "<<std::endl; return -999;};
  if(PDG_trklist.size()==1) secondTrk=0;
  else if(PDG_trklist.size() == 2) secondTrk=1;
  else if(PDG_trklist.size() > 2){

    secondTrk = Get_Index_highestKE_mc_FSPart_WithDeglessthan(HeliumCUTConsts::Maximum_secTrkwrtb_GreatestKE, Energy_trklist, Angle_trklist, PDG_trklist );
  }

  return secondTrk;

}
///////////////////////////////////////////////////
int HeliumCVUniverse::Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_lessthanAngle(std::vector<int> PDG_trklist, std::vector<double> Energy_trklist, std::vector <double> Angle_trklist ) const{

  int secondTrk = 999;
  if(PDG_trklist.size()==0){std::cout<<"Error Only Muon Trk no Secondary Trk "<<std::endl; return -999;};
  if(PDG_trklist.size()==1 ) return 0;
  secondTrk = Get_Index_highestKE_mc_FSPart_WithDeglessthan_NO_NeutralParticles(HeliumCUTConsts::Maximum_secTrkwrtb_GreatestKE, Energy_trklist, Angle_trklist, PDG_trklist);
  return secondTrk;
}



///////////////////////////////////////////////////

///////////////////////////////////////////////////
int HeliumCVUniverse::Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE(std::vector<int> PDG_trklist, std::vector<double> Energy_trklist) const{

  int secondTrk = 999;
  if(PDG_trklist.size()==0){std::cout<<"Error Only Muon Trk no Secondary Trk "<<std::endl; return -999;};
  if(PDG_trklist.size()==1 ) return 0;
  secondTrk = Get_Index_highestKE_mc_FSPart_NO_NeutralParticlesForTruthBranch( Energy_trklist, PDG_trklist);
  return secondTrk;
}



///////////////////////////////////////////////////
int HeliumCVUniverse::Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_lessthanAngle_withKE_thresholdonProtonandPion(std::vector<int> PDG_trklist,
  std::vector<double> Energy_trklist, std::vector <double> Angle_trklist, std::vector <double> truedigitEfraction_vector ) const{

  int secondTrk = 999;
  if(PDG_trklist.size()==0 ){std::cout<<"Error Only Muon Trk no Secondary Trk "<<std::endl; return -999;};
  if(truedigitEfraction_vector.size()==0 ){std::cout<<"Error, Size of truedigitEfraction_vector is zero "<<std::endl; return -999;};
  if(PDG_trklist.size()==1 && TRUTH_EnergyFraction_AreTrueDigits(truedigitEfraction_vector,0 ) == true) return 0;

    secondTrk = Get_Index_highestKE_mc_FSPart_WithDeglessthan_NO_NeutralParticles_withKEpion_proton(HeliumCUTConsts::Maximum_secTrkwrtb_GreatestKE,
      Energy_trklist, Angle_trklist, PDG_trklist, truedigitEfraction_vector,
     HeliumCUTConsts::Truth_pion_Minimum_Energy, HeliumCUTConsts::Truth_proton_Minimum_Energy );

  return secondTrk;
}
///////////////////////////////////////////////////
int HeliumCVUniverse::Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_lessthanAngle_withKE_thresholdonProtonandPion(std::vector<int> PDG_trklist,
  std::vector<double> Energy_trklist, std::vector <double> Angle_trklist) const{

  int secondTrk = 999;
  if(PDG_trklist.size()==0 ){std::cout<<"Error Only Muon Trk no Secondary Trk "<<std::endl; return -999;};
  if(PDG_trklist.size()==1) return 0;

    secondTrk = Get_Index_highestKE_mc_FSPart_WithDeglessthan_NO_NeutralParticles_withKEpion_proton(
      HeliumCUTConsts::Maximum_secTrkwrtb_GreatestKE,
      Energy_trklist, Angle_trklist, PDG_trklist,
       HeliumCUTConsts::Truth_pion_Minimum_Energy, HeliumCUTConsts::Truth_proton_Minimum_Energy );

  return secondTrk;
}
///////////////////////////////////////////////////
int HeliumCVUniverse::Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_muonNotinlist(std::vector<int> PDG_trklist, std::vector<double> Energy_trklist, std::vector <double> truedigitEfraction_vector  ) const{

  int secondTrk = -999;

    secondTrk = Get_Index_highestKE_mc_FSPart_NO_NeutralParticles(Energy_trklist, PDG_trklist, truedigitEfraction_vector );

  return secondTrk;
}
///////////////////////////////////////////////////


///////////////////////////////////////////////////
int HeliumCVUniverse::Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_lessthanAngle_muonNotinlist(std::vector<int> PDG_trklist, std::vector<double> Energy_trklist, std::vector <double> Angle_trklist,std::vector <double> truedigitEfraction_vector  ) const{

  int secondTrk = -999;

    secondTrk = Get_Index_highestKE_NOleadingMuoninlist_WithDeglessthan_NO_NeutralParticles(HeliumCUTConsts::Maximum_secTrkwrtb_GreatestKE, Energy_trklist, Angle_trklist, PDG_trklist, truedigitEfraction_vector );

  return secondTrk;
}
///////////////////////////////////////////////////
int HeliumCVUniverse::Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_lessthanAngle_muonNotinlist_KE_proton_pion_thrusthold(std::vector<int> PDG_trklist, std::vector<double> Energy_trklist, std::vector <double> Angle_trklist , std::vector <double> truedigitEfraction_vector) const{

  int secondTrk = -999;

    secondTrk = Get_Index_highestKE_NOleadingMuoninlist_WithDeglessthan_NO_NeutralParticles_WithProton_pionKEthreshold(HeliumCUTConsts::Maximum_secTrkwrtb_GreatestKE,Energy_trklist, Angle_trklist, PDG_trklist, truedigitEfraction_vector, HeliumCUTConsts::Truth_pion_Minimum_Energy ,HeliumCUTConsts::Truth_proton_Minimum_Energy );

  return secondTrk;

}
///////////////////////////////////////////////////
std::vector <double> HeliumCVUniverse::FromTRUTH_branch_GetVector_lastNode_X() const {return GetVecDouble("truth_truthbranch_ALLTrajectors_FinalPositionX");}
std::vector <double> HeliumCVUniverse::FromTRUTH_branch_GetVector_lastNode_Y() const {return GetVecDouble("truth_truthbranch_ALLTrajectors_FinalPositionY");}
std::vector <double> HeliumCVUniverse::FromTRUTH_branch_GetVector_lastNode_Z() const {return GetVecDouble("truth_truthbranch_ALLTrajectors_FinalPositionZ");}
///////////////////////////////////////////////////
std::vector<Vertex_XYZ> HeliumCVUniverse::Construct_EndPointvector_ForTRUE_FS_particle ()const{
  std::vector <Vertex_XYZ> Final_vector;

  auto X_vector = FromTRUTH_branch_GetVector_lastNode_X();
  auto Y_vector = FromTRUTH_branch_GetVector_lastNode_Y();
  auto Z_vector = FromTRUTH_branch_GetVector_lastNode_Z();

//std::cout<< "X_vector.size() = " << X_vector.size()<<std::endl;
//std::cout<< "Y_vector.size() = " << Y_vector.size()<<std::endl;
//std::cout<< "Z_vector.size() = " << Z_vector.size()<<std::endl;

if(X_vector.size() != Y_vector.size() || Y_vector.size() != Z_vector.size() ){assert(0 && "Truth Endpoint trajectories Position Vectors are not the same size in Tuple: ERROR");}


  for(int i=0; i < X_vector.size(); i++){

    //std::cout<< "X_vector.at("<<i<<") = " << X_vector.at(i)<<std::endl;
    //std::cout<< "Y_vector.at("<<i<<") = " << Y_vector.at(i)<<std::endl;
    //std::cout<< "Z_vector.at("<<i<<") = " << Z_vector.at(i)<<std::endl;

    Vertex_XYZ Single_point{X_vector.at(i),Y_vector.at(i),Z_vector.at(i)};
    Final_vector.push_back(Single_point);
  }
  return Final_vector;
}
///////////////////////////////////////////////////
int HeliumCVUniverse::Get_Index_LowestKE_mc_FSPart() const {
  auto KE_vector = GETvector_Energy_mc_FS_particles_MeVtoGeV();
  auto pdg_vector = GETvector_PDG_FS_particles();

  if(pdg_vector[0] == 13){
  KE_vector.erase(KE_vector.begin());}

  int N_size= KE_vector.size();
  double Lowest = 999;
  int secondTk_index =0;
  for (int i = 0; i < N_size; i++) {
    if (KE_vector.at(i) < Lowest){
      Lowest = KE_vector.at(i);
      secondTk_index = i;
    } // if found highest E
  }
  if(secondTk_index==-999){return -999;}
  return secondTk_index;

}



///////////////////////////////////////////////////
std::vector <double> HeliumCVUniverse::GETvector_Px_mc_FS_particles()const{ return GetVecDouble("mc_FSPartPx");}
std::vector <double> HeliumCVUniverse::GETvector_Py_mc_FS_particles()const{ return GetVecDouble("mc_FSPartPy");}
std::vector <double> HeliumCVUniverse::GETvector_Pz_mc_FS_particles()const{ return GetVecDouble("mc_FSPartPz");}
std::vector <double> HeliumCVUniverse::GETvector_theta_wrtb_FS_particles() const{
std::vector <double> Theta_vector;
auto PX = GETvector_Px_mc_FS_particles();
auto PY = GETvector_Py_mc_FS_particles();
auto PZ = GETvector_Pz_mc_FS_particles();
int i = 0;
for(auto cat : PX){
  double rad_angle = ThetaWRTBeam(cat, PY.at(i), PZ.at(i),0.0);
  Theta_vector.push_back(rad_angle*TMath::RadToDeg());
  i++;
}
return Theta_vector;
}
///////////////////////////////////////////////////

std::vector <double> HeliumCVUniverse::GETvector_Energy_mc_FS_particles_MeVtoGeV()const{
  std::vector <double> E_GeV_vector;
  auto E_vector = GETvector_Energy_mc_FS_particles();
  for(auto cat : E_vector)
  {
    E_GeV_vector.push_back(cat*.001);
  }
  return E_GeV_vector;
}
///////////////////////////////////////////////////
int  HeliumCVUniverse::GET_N_PDG_FS_particles()const{
  auto vector = GETvector_PDG_FS_particles();
  return vector.size();
}
//////////////////////////////////////////////////////////////////////////
//Get Non MuonTrk Info
//////////////////////////////////////////////////////////////////////////
double HeliumCVUniverse::GetNonmuTrkE(int TRKNum)              const{return GetVecElem("nonmuKE",TRKNum);}
double HeliumCVUniverse::GetNonmuTrkE_GeV(int TRKNum)          const{return GetVecElem("nonmuKE",TRKNum) * .001;}
double HeliumCVUniverse::GetNonmuTrkAngleWRTbeam(int TRKNum)   const{return GetVecElem("nonmu_thetaWRTB",TRKNum);}
double HeliumCVUniverse::GetNonmuTrkAngleWRTbeamMID(int TRKNum) const{return GetVecElem("nonmu_thetaWRTBmid",TRKNum);}
///////////////////////////////////////////////////
std::vector <double> HeliumCVUniverse::GetVector_GetNonmuTrkE() const {
  auto energy = GetVecDouble("nonmuKE");
  std::vector <double> energy_vector;

  for(unsigned int i=1; i<energy.size();i++ ){
    energy_vector.push_back(energy.at(i));
  }
  return energy_vector;
}

std::vector <double> HeliumCVUniverse::GetVector_NonmuTrkAngleWRTbeamMID() const {
  auto Angle = GetVecDouble("nonmu_thetaWRTBmid");
  std::vector <double> Angle_vector;

  for(unsigned int i=1; i<Angle.size();i++ ){
    Angle_vector.push_back(Angle.at(i));
  }
  return Angle_vector;
}
///////////////////////////////////////////////////
double HeliumCVUniverse::GetNonmuTrkAngleWRTmu(int TRKNum)const{return GetVecElem("trackangle",TRKNum);}
double HeliumCVUniverse::GetNonmuTrkLength(int TRKNum)    const{return GetVecElem("nonmu_tracklength",TRKNum);}
double HeliumCVUniverse::GetNonmuDOCA(int TRKNum)         const{return GetVecElem("trackDOCA",TRKNum);}
double HeliumCVUniverse::GetNonmuTrkTimes(int TRKNum)     const{return GetVecElem("tracktimes",TRKNum);}


double HeliumCVUniverse::GetFirstNodeX(int TRKNum) const{return GetVecElem("cryotrackxnodes",TRKNum);}
double HeliumCVUniverse::GetLastNodeX(int TRKNum)  const{return GetVecElem("cryotrack_lastxnodes",TRKNum);}
double HeliumCVUniverse::GetFirstNodeY(int TRKNum) const{return GetVecElem("cryotrackynodes",TRKNum);}
double HeliumCVUniverse::GetLastNodeY(int TRKNum)  const{return GetVecElem("cryotrack_lastynodes",TRKNum);}
double HeliumCVUniverse::GetFirstNodeZ(int TRKNum) const{return GetVecElem("cryotrackznodes",TRKNum);}
double HeliumCVUniverse::GetLastNodeZ(int TRKNum)  const{return GetVecElem("cryotrack_lastznodes",TRKNum);}

double HeliumCVUniverse::GetNonmuTrkLength_InMinerva(int TRKNum)const{
  double x = GetLastNodeX(TRKNum) - GetFirstNodeX(TRKNum);
  double y = GetLastNodeY(TRKNum) - GetFirstNodeY(TRKNum);
  double z = GetLastNodeZ(TRKNum) - GetFirstNodeZ(TRKNum);

  return sqrt(pow(x,2) + pow(y,2) + pow(z,2));
}

double HeliumCVUniverse::GetNonmuTrkLength_InMinerva_Incm(int TRKNum)const{
      double mm = GetNonmuTrkLength_InMinerva(TRKNum);
     return  mm * 0.1;
}
///////////////////////////////////////////////////
std::vector <double> HeliumCVUniverse::GetVector_GetNonmuTrkLength_InMinerva_Incm() const{

  int N_tracks = GetTracksize();
  std::vector<double> trackLength_vector;

  for(int i=1;i<N_tracks;i++){
    auto trackLength = GetNonmuTrkLength_InMinerva_Incm(i);
    trackLength_vector.push_back(trackLength);
  }
  return trackLength_vector;
}//end of functin
///////////////////////////////////////////////////
// Event INformation
///////////////////////////////////////////////////

int HeliumCVUniverse::GetRunN() const{return GetInt("ev_run");}
int HeliumCVUniverse::GetSubRunN() const{return GetInt("ev_subrun");}
int HeliumCVUniverse::GetGateN() const{return GetInt("ev_gate");}
int HeliumCVUniverse::GetSliceN() const{return GetVecElem("slice_numbers",0);}


int HeliumCVUniverse::GetMCRunN() const{return GetInt("mc_run");}
int HeliumCVUniverse::GetMCSubRunN() const{return GetInt("mc_subrun");}
int HeliumCVUniverse::GetMCGateN() const{return GetInt("mc_nthEvtInFile");}
int HeliumCVUniverse::GetMCSliceN() const{return GetVecElem("slice_numbers",0);}

std::vector <int> HeliumCVUniverse::GetEventRun() const {
  std::vector <int> return_vector;

  return_vector.push_back(HeliumCVUniverse::GetRunN());
  return_vector.push_back(HeliumCVUniverse::GetSubRunN());
  return_vector.push_back(HeliumCVUniverse::GetGateN());
  return_vector.push_back(HeliumCVUniverse::GetSliceN());

  return return_vector;
}

SliceID HeliumCVUniverse::GetEventSliceForData() const{
  auto run_vector = GetEventRun();
  SliceID return_Slice{run_vector.at(0),run_vector.at(1),run_vector.at(2),run_vector.at(3)};
  return return_Slice;
}


std::vector <int> HeliumCVUniverse::GetVector_nonMuonTk_PDG() const {return GetVecInt("truth_nonmu_PDG");}
std::vector <double> HeliumCVUniverse::GetVector_nonMuonTk_Angle_wrtb_rad() const {return GetVecDouble("truth_nonmu_angleWRTB");}
std::vector <double> HeliumCVUniverse::GetVector_nonMuonTk_Energy_MeV() const {return GetVecDouble("truth_nonmuKE");}

std::vector <double> HeliumCVUniverse::GetVector_nonMuonTk_Angle_wrtb_Degs() const {
  std::vector<double> output_vector;
  auto input = GetVector_nonMuonTk_Angle_wrtb_rad();
  for(auto cat : input){
    output_vector.push_back(cat*TMath::RadToDeg());
  }

  return output_vector;
}



std::vector <double> HeliumCVUniverse::GetVector_nonMuonTk_Energy_GeV() const {
  auto input_vector = GetVector_nonMuonTk_Energy_MeV();
  std::vector<double> output_vector;

  for(auto cat : input_vector){
    output_vector.push_back(cat*.001);
  }

  return output_vector;

}
/////////////////////

std::vector <int> HeliumCVUniverse::GetVector_nonMuonTk_PDG_Parent() const {return GetVecInt("truth_nonmu_PDG_Parent");}
std::vector <double> HeliumCVUniverse::GetVector_nonMuonTk_Angle_wrtb_rad_Parent() const {return GetVecDouble("truth_nonmu_angleWRTB_Parent");}
std::vector <double> HeliumCVUniverse::GetVector_nonMuonTk_Energy_MeV_Parent() const {return GetVecDouble("truth_nonmuKE_Parent");}
std::vector<double> HeliumCVUniverse::Get_TrueFractionE_vector() const{ return GetVecDouble("truth_fraction_aretruedigits");}





std::vector <double> HeliumCVUniverse::GetVector_nonMuonTk_Energy_GeV_Parent() const {
  auto input_vector = GetVector_nonMuonTk_Energy_MeV_Parent();
  std::vector<double> output_vector;

  for(auto cat : input_vector){
    output_vector.push_back(cat*.001);
  }

  return output_vector;

}

std::vector <double> HeliumCVUniverse::GetVector_nonMuonTk_Angle_wrtb_Degs_Parent() const {
  std::vector<double> output_vector;
  auto input = GetVector_nonMuonTk_Angle_wrtb_rad_Parent();
  for(auto cat : input){
    output_vector.push_back(cat*TMath::RadToDeg());
  }

  return output_vector;
}



double HeliumCVUniverse::GetTRUE_NonmuTrkE_Parent(int TRKNum) const{return GetVecElem("truth_nonmuKE_Parent",TRKNum) * .001;} //GeV
double HeliumCVUniverse::GetTRUE_NonmuTrkopenangle_Parent(int TRKNum) const{return GetVecElem("truth_opening_angle_Parent",TRKNum)* TMath::RadToDeg();}
double HeliumCVUniverse::GetTRUE_NonmuTrkANGLE_WRTB_Parent(int TRKNum) const{return GetVecElem("truth_nonmu_angleWRTB_Parent",TRKNum)* TMath::RadToDeg();}

double HeliumCVUniverse::distance_betweenPoints(double x1, double y1, double z1, double x2, double y2, double z2){
  return sqrt(pow((x2-x1),2) + pow((y2-y1),2) + pow((z2-z1),2));
}
///////////////////////////////////////////////////
int HeliumCVUniverse::Trajectorindex_leastdistance(double x1, double y1, double z1, std::vector<double>FinalX,std::vector<double>FinalY,std::vector<double>FinalZ ){

  int i=0;
  int index =0;
  double shortest_dis = 999999.0;

  for(auto cat:FinalX ){
    double distance = distance_betweenPoints( x1,  y1,  z1, cat, FinalY[i], FinalZ[i]);

    if(shortest_dis > distance){
      shortest_dis = distance;
      index=i;
    }

  }

  return index;

}
///////////////////////////////////////////////////
int  HeliumCVUniverse::getindexTrueTrajectors_closestRECO(){
  auto index_reco = Getindex2ndTrackhighestKE();

  double reco_x = GetLastNodeX(index_reco);
  double reco_y = GetLastNodeY(index_reco);
  double reco_z = GetLastNodeZ(index_reco);

  auto FinalX = GetVector_ALLTrajector_FinalPosition("x");
  auto FinalY = GetVector_ALLTrajector_FinalPosition("y");
  auto FinalZ = GetVector_ALLTrajector_FinalPosition("z");


  return Trajectorindex_leastdistance(reco_x, reco_y, reco_z, FinalX, FinalY, FinalZ );

}//end of function
//////////////////////////////////////////////////////////////////////////
//Get TRUTH Non MuonTrk Info
//////////////////////////////////////////////////////////////////////////

double HeliumCVUniverse::GetTRUENonmuTrkE(int TRKNum) const           {return GetVecElem("truth_nonmuKE",TRKNum)* .001;}
double HeliumCVUniverse::GetTRUENonmuTrkAngleWRTbeam(int TRKNum) const{return( GetVecElem("truth_nonmu_angleWRTB",TRKNum) * TMath::RadToDeg());}
double HeliumCVUniverse::GetTRUENonmuTrkAngleWRTmu(int TRKNum) const  {return (GetVecElem("truth_opening_angle",TRKNum)* TMath::RadToDeg());}

double HeliumCVUniverse::GetVetoTotEff() const{return GetDouble("vetoTotalEff");}
double HeliumCVUniverse::GetVetoTotAcc() const{return GetDouble("vetoTotalAcc");}

double HeliumCVUniverse::GetVetoAccpetedWeigh() const{
	double AccTot= 1.0 + HeliumCVUniverse::GetVetoTotAcc();
	double EffTot= 1.0 - HeliumCVUniverse::GetVetoTotEff();
	double weight = AccTot;
	weight *=EffTot;
	return weight;}


	//////////////////////////////////////////////////////////////////////////
	//Get Weights
	//////////////////////////////////////////////////////////////////////////
	double HeliumCVUniverse::GetWeight(HeliumPlayListInfo info) const {
		double wgt_flux_and_cv=1.0, wgt_nrp=1.0, wgt_genie=1.0, wgt_lowQ2=1.0;
		double  wgt_normWeightLowandHighP=1.0, wgt_RPA=1.0, wgt_2p2h=1.0;
		double wgt_minos_eff =1.0;
		double wgt_VetoEff = 1.0;
    double mgt_targetMass = 1.0;
		// flux + cv

		std::string playlist(info.GetPlaylistname());

		double Enu  = GetDouble("mc_incomingE")*1e-3;
		int nu_type = GetInt("mc_incoming");
		wgt_flux_and_cv = GetFluxAndCVWeight( Enu, nu_type);

		wgt_2p2h = GetLowRecoil2p2hWeight();

		wgt_genie = GetGenieWeight();

		wgt_RPA = GetRPAWeight();

		wgt_minos_eff = GetMinosEfficiencyWeight();

    mgt_targetMass = GetTargetMassWeight();
    //wgt_minos_eff = MinosMuonEfficiencyCorrection(true);

		//wgt_lowQ2 = GetLowQ2PiWeight("MINOS"); // add for v1 tune

		wgt_VetoEff =1.00000; // HeliumCVUniverse::GetVetoAccpetedWeigh();

		return wgt_flux_and_cv * wgt_normWeightLowandHighP * wgt_2p2h *  wgt_genie * wgt_nrp * wgt_RPA * wgt_VetoEff * wgt_lowQ2 * wgt_minos_eff*mgt_targetMass;

	}




  double HeliumCVUniverse::GetWeight(Weights kweight) const {

    switch (kweight) {

      case kweightFlux:
      return GetFluxAndCVWeight();

      case kweightMinos:
      return GetMinosEfficiencyWeight();

      case kweight2p2ptune:
      return GetLowRecoil2p2hWeight();

      case kweightRPA:
      return  GetRPAWeight();

      case kweightGenie:
      return GetGenieWeight();

      case kweightLowQ2Pi:
      return GetLowQ2PiWeight("MINOS");

      case kweight_HeliumTargetMass:
      return GetTargetMassWeight();

      case kweightNone:
      return 1.0;

      default:
      std::cout << "ERROR: Unknown weight " << std::endl;
      return -9999;

    };//end of switch

  }


  double HeliumCVUniverse::GetWeight(std::vector<Weights> kweight_vector) const {
    double return_weight=1.0;
    for(auto weight:kweight_vector){
      return_weight *= GetWeight(weight);
    }

    return return_weight;
  }

//////Robs Method


double HeliumCVUniverse::GetPmuTransverseTrue() const {
    const double px=GetVecElem("mc_primFSLepton", 0);
    const double py=GetVecElem("mc_primFSLepton", 1);
    const double pz=GetVecElem("mc_primFSLepton", 2);
    // Copied (and modified) from MinervaCoordSysTool::thetaWRTBeam
    const double numi_beam_angle_rad = -0.05887; // Taken from MinervaPhysicalConstants.h
    double pyp = -1.0 *sin( numi_beam_angle_rad )*pz + cos( numi_beam_angle_rad )*py;
    double pt   = sqrt( pow(px,2) +pow(pyp,2) );
    return 1.0e-3*pt; //GeV
  }
  double HeliumCVUniverse::GetPmuLongitudinalTrue() const {
    const double pylep=GetVecElem("mc_primFSLepton", 1);
    const double pzlep=GetVecElem("mc_primFSLepton", 2);
    // Copied (and modified) from MinervaCoordSysTool::thetaWRTBeam
    const double numi_beam_angle_rad = -0.05887; // Taken from MinervaPhysicalConstants.h
    double pzp = cos( numi_beam_angle_rad )*pzlep + sin( numi_beam_angle_rad )*pylep;
    return 1.0e-3*pzp; //GeV
  }

double HeliumCVUniverse::GetQ2forMKmodel() const {
  return GetDouble("mc_Q2") * 1e-6;
}

double HeliumCVUniverse::GetWforMKmodel() const {
  return GetDouble("mc_w") * 1e-3;
}

int HeliumCVUniverse::GetCCforMKmodel() const {
return GetDouble("mc_current");
}

int HeliumCVUniverse::GetnPartforMKmodel() const {
return GetDouble("mc_er_nPart");
}

int HeliumCVUniverse::GetnIDforMKmodel(int index)const {
  return GetVecElem("mc_er_ID",index);
}

int HeliumCVUniverse::GetnIDstatusforMKmodel(int index)const {
  return GetVecElem("mc_er_status",index);
}

double HeliumCVUniverse::GetMKmodelWeight_local(weightMK *weight_MK)const {

const double Q2 = GetQ2forMKmodel();
const double W = GetWforMKmodel();

 const int intType = GetIntactionType();
 const int current = GetCCforMKmodel();
 const int targetA = GetTargetType();
 const int nPart = GetnPartforMKmodel();
 int ID[nPart];
 int status[nPart];

 for(int i=0; i<nPart; i++){
   ID[i]= GetnIDforMKmodel(i);
   status[i]=GetnIDstatusforMKmodel(i);
 }
 //I used ChainWrapper in the original version to get the values of the
 return weight_MK->getWeight(W, Q2 ,current, intType, nPart, targetA, ID, status);
}



std::vector <double> HeliumCVUniverse::GetVector_ALLTrajector_Angle() const {return GetVecDouble("HeAnaTupleTool_ALLTrajectors_Angle");}
std::vector <double> HeliumCVUniverse::GetVector_ALLTrajector_DOCA() const {return GetVecDouble("HeAnaTupleTool_ALLTrajectors_DOCA");}
std::vector <double> HeliumCVUniverse::GetVector_ALLTrajector_E() const {return GetVecDouble("HeAnaTupleTool_ALLTrajectors_E");}
std::vector <double> HeliumCVUniverse::GetVector_ALLTrajector_TrkLength() const {return GetVecDouble("HeAnaTupleTool_ALLTrajectors_TrkLength");}
std::vector <double> HeliumCVUniverse::GetVector_ALLTrajector_columnarDensity() const {return GetVecDouble("HeAnaTupleTool_ALLTrajectors_columnarDensity");}
int HeliumCVUniverse::Get_ALLTrajector_tracksize() const{return GetInt("HeAnaTupleTool_ALLTrajectors_true_tracksize_sz");}







std::vector <double> HeliumCVUniverse::GetVector_ALLTrajector_FinalPosition(std::string input) const {
 if(input=="x"){return GetVecDouble("HeAnaTupleTool_ALLTrajectors_FinalPositionX");}
 else if(input=="y"){return GetVecDouble("HeAnaTupleTool_ALLTrajectors_FinalPositionY");}
 else if(input=="z"){return GetVecDouble("HeAnaTupleTool_ALLTrajectors_FinalPositionZ");}
 else{
   std::cout<<"ERROR"<<std::endl;
   std::vector<double> A={-999,-999,-999};
   return A;
 }
}

std::vector <double> HeliumCVUniverse::GetVector_ALLTrajector_InitalPosition(std::string input) const {
 if(input=="x"){return GetVecDouble("HeAnaTupleTool_ALLTrajectors_InitalPositionX");}
 else if(input=="y"){return GetVecDouble("HeAnaTupleTool_ALLTrajectors_InitalPositionY");}
 else if(input=="z"){return GetVecDouble("HeAnaTupleTool_ALLTrajectors_InitalPositionZ");}
 else{
   std::cout<<"ERROR"<<std::endl;
   std::vector<double> A={-999,-999,-999};
   return A;
 }
}

std::vector <int> HeliumCVUniverse::GetVector_ALLTrajector_PDG() const {return GetVecInt("HeAnaTupleTool_ALLTrajectors_PDG");}

int HeliumCVUniverse::Get_index_Trajector_PDG(int index) const {return GetVecElem("HeAnaTupleTool_ALLTrajectors_PDG",index);}


std::vector <double> HeliumCVUniverse::GetVector_ALLTrajector_P(std::string input) const {
 if(input=="x"){return GetVecDouble("HeAnaTupleTool_ALLTrajectors_PX");}
 else if(input=="y"){return GetVecDouble("HeAnaTupleTool_ALLTrajectors_PY");}
 else if(input=="z"){return GetVecDouble("HeAnaTupleTool_ALLTrajectors_PZ");}
 else
 {
   std::cout<<"ERROR"<<std::endl;
   std::vector<double> A={-999,-999,-999};
   return A;
 }
}



Trajector HeliumCVUniverse::GetVector_ALLTrajector() const {

  auto run = GetMCRunN();
  auto subrun = GetMCSubRunN();
  auto gate = GetMCGateN();
  auto slice  = GetMCSliceN();

  SliceID RunInfo={run,subrun,gate,slice};

  auto PDG = GetVector_ALLTrajector_PDG();
  auto E = GetVector_ALLTrajector_E();
  auto Angle = GetVector_ALLTrajector_Angle();
  auto IntialX = GetVector_ALLTrajector_InitalPosition("x");
  auto IntialY = GetVector_ALLTrajector_InitalPosition("y");
  auto IntialZ = GetVector_ALLTrajector_InitalPosition("z");

  auto FinalX = GetVector_ALLTrajector_FinalPosition("x");
  auto FinalY = GetVector_ALLTrajector_FinalPosition("y");
  auto FinalZ = GetVector_ALLTrajector_FinalPosition("z");


  Trajector Event_trajectors = {RunInfo,PDG,E,Angle,IntialX,IntialY,IntialZ,FinalX,FinalY,FinalZ};
  return Event_trajectors;

}



Trajector HeliumCVUniverse::GetVector_ALLTrajector_ForWithRecoTracks() const {

  auto run = GetMCRunN();
  auto subrun = GetMCSubRunN();
  auto gate = GetMCGateN();
  auto slice  = GetMCSliceN();

  SliceID RunInfo={run,subrun,gate,slice};
  //make muon first entry and the other Tracks nonmuon
  std::vector<int> PDG;
  std::vector<double> E;
  std::vector<double> Angle;
  auto IntialX =  GetVector_firstNode_X();
  auto IntialY =  GetVector_firstNode_Y();
  auto IntialZ =  GetVector_firstNode_Z();
  auto FinalX =  GetVector_lastNode_X();
  auto FinalY =  GetVector_lastNode_Y();
  auto FinalZ =  GetVector_lastNode_Z();

  PDG.push_back(13);
  E.push_back(GetTRUE_Emu()*1000); // Convert back to GeV
  Angle.push_back(GetTRUE_muANGLE_WRTB_DEG());

  auto pdg_nonmuon = GetVector_nonMuonTk_PDG();
  auto nonmuon_KE = GetVector_nonMuonTk_Energy_MeV();
  auto Angle_nonmuon = GetVector_nonMuonTk_Angle_wrtb_rad();

  for(auto pdg_index : pdg_nonmuon)
  {
    if(pdg_index != -9999)
    {
      PDG.push_back(pdg_index);
    }
  }

  for(auto KE_index : nonmuon_KE)
  {
    if(KE_index != -9999)
    {
      E.push_back(KE_index); // into GeV
    }

  }

  for(auto Angle_nonmuon_index : Angle_nonmuon)
  {
    if(Angle_nonmuon_index != -9999)
    {
      Angle.push_back(Angle_nonmuon_index*TMath::RadToDeg());
    }
  }
  int  a = PDG.size();
  int  b = E.size();
  int  c = Angle.size();
  int  d = IntialX.size();
  int  e = IntialY.size();
  int  f = IntialZ.size();
  int  g = FinalX.size();
  int  h = FinalY.size();
  int  i = FinalZ.size();

  std::vector<int> numbers = {a,b,c,d,e,f,g,h,i};

  if(std::count(std::begin(numbers), std::end(numbers), numbers.front()) != numbers.size()){
    int kk=0;
    for(auto cat : numbers ){
      std::cout<<"index = "<< kk <<" size of numbers "<< cat <<std::endl;
      kk++;
    }

    for(auto cat :PDG){std::cout<<"PDG = "<< cat<<std::endl;}
    for(auto cat :pdg_nonmuon){std::cout<<"pdg_nonmuon = "<< cat<<std::endl;}

    for(auto cat :E){std::cout<<"E = "<< cat<<std::endl;}
    for(auto cat :Angle){std::cout<<"Angle = "<< cat<<std::endl;}
    for(auto cat :IntialX){std::cout<<"IntialX = "<< cat<<std::endl;}
    for(auto cat :IntialY){std::cout<<"IntialY = "<< cat<<std::endl;}
    for(auto cat :IntialZ){std::cout<<"IntialZ = "<< cat<<std::endl;}
    for(auto cat :FinalX){std::cout<<"FinalX = "<< cat<<std::endl;}
    for(auto cat :FinalY){std::cout<<"FinalY = "<< cat<<std::endl;}
    for(auto cat :FinalZ){std::cout<<"FinalZ = "<< cat<<std::endl;}
    std::cout<<"Error  The  Compoents are not the same size in the GetVector_ALLTrajector_ForWithRecoTracks "<< std::endl;
    assert(1);
  }

  Trajector Event_trajectors = {RunInfo,PDG,E,Angle,IntialX,IntialY,IntialZ,FinalX,FinalY,FinalZ};
  return Event_trajectors;
}
////////////////////////////////////////////////////////////////////////////////

Trajector HeliumCVUniverse::GetVector_ALLTrajector_ForWithRecoTracks_Parent() const {

  auto run = GetMCRunN();
  auto subrun = GetMCSubRunN();
  auto gate = GetMCGateN();
  auto slice  = GetMCSliceN();

  SliceID RunInfo={run,subrun,gate,slice};
  //make muon first entry and the other Tracks nonmuon
  std::vector<int> PDG;
  std::vector<double> E;
  std::vector<double> Angle;
  auto IntialX =  GetVector_firstNode_X();
  auto IntialY =  GetVector_firstNode_Y();
  auto IntialZ =  GetVector_firstNode_Z();
  auto FinalX =  GetVector_lastNode_X();
  auto FinalY =  GetVector_lastNode_Y();
  auto FinalZ =  GetVector_lastNode_Z();

  PDG.push_back(13);
  E.push_back(GetTRUE_Emu()*1000); // Convert back to GeV
  Angle.push_back(GetTRUE_muANGLE_WRTB_DEG());

  auto pdg_nonmuon = GetVector_nonMuonTk_PDG_Parent();
  auto nonmuon_KE = GetVector_nonMuonTk_Energy_MeV_Parent();
  auto Angle_nonmuon = GetVector_nonMuonTk_Angle_wrtb_rad_Parent();

  for(auto pdg_index : pdg_nonmuon)
  {
    if(pdg_index != -9999)
    {
      PDG.push_back(pdg_index);
    }
  }

  for(auto KE_index : nonmuon_KE)
  {
    if(KE_index != -9999)
    {
      E.push_back(KE_index); // into GeV
    }

  }

  for(auto Angle_nonmuon_index : Angle_nonmuon)
  {
    if(Angle_nonmuon_index != -9999)
    {
      Angle.push_back(Angle_nonmuon_index*TMath::RadToDeg());
    }
  }
  int  a = PDG.size();
  int  b = E.size();
  int  c = Angle.size();
  int  d = IntialX.size();
  int  e = IntialY.size();
  int  f = IntialZ.size();
  int  g = FinalX.size();
  int  h = FinalY.size();
  int  i = FinalZ.size();

  std::vector<int> numbers = {a,b,c,d,e,f,g,h,i};

  if(std::count(std::begin(numbers), std::end(numbers), numbers.front()) != numbers.size()){
    int kk=0;
    for(auto cat : numbers ){
      std::cout<<"index = "<< kk <<" size of numbers "<< cat <<std::endl;
      kk++;
    }

    for(auto cat :PDG){std::cout<<"PDG = "<< cat<<std::endl;}
    for(auto cat :pdg_nonmuon){std::cout<<"pdg_nonmuon = "<< cat<<std::endl;}

    for(auto cat :E){std::cout<<"E = "<< cat<<std::endl;}
    for(auto cat :Angle){std::cout<<"Angle = "<< cat<<std::endl;}
    for(auto cat :IntialX){std::cout<<"IntialX = "<< cat<<std::endl;}
    for(auto cat :IntialY){std::cout<<"IntialY = "<< cat<<std::endl;}
    for(auto cat :IntialZ){std::cout<<"IntialZ = "<< cat<<std::endl;}
    for(auto cat :FinalX){std::cout<<"FinalX = "<< cat<<std::endl;}
    for(auto cat :FinalY){std::cout<<"FinalY = "<< cat<<std::endl;}
    for(auto cat :FinalZ){std::cout<<"FinalZ = "<< cat<<std::endl;}
    std::cout<<"Error  The  Compoents are not the same size in the GetVector_ALLTrajector_ForWithRecoTracks "<< std::endl;
    assert(1);
  }

  Trajector Event_trajectors = {RunInfo,PDG,E,Angle,IntialX,IntialY,IntialZ,FinalX,FinalY,FinalZ};
  return Event_trajectors;
}




////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
Trajector_withTrueEnergyFraction HeliumCVUniverse::GetVector_ALLTrajector_ForWithRecoTracks_withTrueEFraction() const
{
  auto run = GetMCRunN();
  auto subrun = GetMCSubRunN();
  auto gate = GetMCGateN();
  auto slice  = GetMCSliceN();

  SliceID RunInfo={run,subrun,gate,slice};

  //make muon first entry and the other Tracks nonmuon
  std::vector<int> PDG;
  std::vector<double> E;
  std::vector<double> Angle;
  std::vector<double> True_energyFraction;
  auto IntialX =  GetVector_firstNode_X();
  auto IntialY =  GetVector_firstNode_Y();
  auto IntialZ =  GetVector_firstNode_Z();
  auto FinalX =  GetVector_lastNode_X();
  auto FinalY =  GetVector_lastNode_Y();
  auto FinalZ =  GetVector_lastNode_Z();

  PDG.push_back(13);
  E.push_back(GetTRUE_Emu()*1000); // Convert back to GeV
  Angle.push_back(GetTRUE_muANGLE_WRTB_DEG());
  True_energyFraction.push_back(-9999);
  // don't have true information for muon

  auto pdg_nonmuon = GetVector_nonMuonTk_PDG();
  auto nonmuon_KE = GetVector_nonMuonTk_Energy_MeV();
  auto Angle_nonmuon = GetVector_nonMuonTk_Angle_wrtb_rad();
  auto TrueEnergyFr = Get_TrueFractionE_vector();


  for(auto pdg_index : pdg_nonmuon)
  {
    if(pdg_index != -9999)
    {
      PDG.push_back(pdg_index);
    }


  }

  for(auto KE_index : nonmuon_KE)
  {
    if(KE_index != -9999)
    {
      E.push_back(KE_index); // into GeV
    }

  }

  for(auto Angle_nonmuon_index : Angle_nonmuon)
  {
    if(Angle_nonmuon_index != -9999)
    {
      Angle.push_back(Angle_nonmuon_index*TMath::RadToDeg());
    }
  }

  for(auto true_energy_fr_index : TrueEnergyFr)
  {
    if(true_energy_fr_index != -9999)
    {
      True_energyFraction.push_back(true_energy_fr_index); // into GeV
    }

  }
  int  a = PDG.size();
  int  b = E.size();
  int  c = Angle.size();
  int  d = IntialX.size();
  int  e = IntialY.size();
  int  f = IntialZ.size();
  int  g = FinalX.size();
  int  h = FinalY.size();
  int  i = FinalZ.size();
  int  j = True_energyFraction.size();

  std::vector<int> numbers = {a,b,c,d,e,f,g,h,i,j};

  if(std::count(std::begin(numbers), std::end(numbers), numbers.front()) != numbers.size()){
    int kk=0;
    for(auto cat : numbers ){
      std::cout<<"index = "<< kk <<" size of numbers "<< cat <<std::endl;
    kk++;
  }
  for(auto cat :PDG){std::cout<<"PDG = "<< cat<<std::endl;}
  for(auto cat :pdg_nonmuon){std::cout<<"pdg_nonmuon = "<< cat<<std::endl;}
  for(auto cat :E){std::cout<<"E = "<< cat<<std::endl;}
  for(auto cat :Angle){std::cout<<"Angle = "<< cat<<std::endl;}
  for(auto cat :IntialX){std::cout<<"IntialX = "<< cat<<std::endl;}
  for(auto cat :IntialY){std::cout<<"IntialY = "<< cat<<std::endl;}
  for(auto cat :IntialZ){std::cout<<"IntialZ = "<< cat<<std::endl;}
  for(auto cat :FinalX){std::cout<<"FinalX = "<< cat<<std::endl;}
  for(auto cat :FinalY){std::cout<<"FinalY = "<< cat<<std::endl;}
  for(auto cat :FinalZ){std::cout<<"FinalZ = "<< cat<<std::endl;}
  for(auto cat :True_energyFraction){std::cout<<"True_energyFraction = "<< cat<<std::endl;}
  std::cout<<"Error  The  Compoents are not the same size in the GetVector_ALLTrajector_ForWithRecoTracks "<< std::endl;
  assert(1);
}

 Trajector_withTrueEnergyFraction Event_trajectors = {RunInfo,PDG,E,Angle,True_energyFraction,IntialX,IntialY,IntialZ,FinalX,FinalY,FinalZ};
 return Event_trajectors;


}
////////////////////////////////////////////////////////////////////////////////
Trajector_withTrueEnergyFraction HeliumCVUniverse::GetVector_ALLTrajector_ForWithRecoTracks_withTrueEFraction_Parent() const
{
  auto run = GetMCRunN();
  auto subrun = GetMCSubRunN();
  auto gate = GetMCGateN();
  auto slice  = GetMCSliceN();

  SliceID RunInfo={run,subrun,gate,slice};

  //make muon first entry and the other Tracks nonmuon
  std::vector<int> PDG;
  std::vector<double> E;
  std::vector<double> Angle;
  std::vector<double> True_energyFraction;
  auto IntialX =  GetVector_firstNode_X();
  auto IntialY =  GetVector_firstNode_Y();
  auto IntialZ =  GetVector_firstNode_Z();
  auto FinalX =  GetVector_lastNode_X();
  auto FinalY =  GetVector_lastNode_Y();
  auto FinalZ =  GetVector_lastNode_Z();

  PDG.push_back(13);
  E.push_back(GetTRUE_Emu()*1000); // Convert back to GeV
  Angle.push_back(GetTRUE_muANGLE_WRTB_DEG());
  True_energyFraction.push_back(-9999);
  // don't have true information for muon

  auto pdg_nonmuon = GetVector_nonMuonTk_PDG_Parent();
  auto nonmuon_KE = GetVector_nonMuonTk_Energy_MeV_Parent();
  auto Angle_nonmuon = GetVector_nonMuonTk_Angle_wrtb_rad_Parent();
  auto TrueEnergyFr = Get_TrueFractionE_vector();


  for(auto pdg_index : pdg_nonmuon)
  {
    if(pdg_index != -9999)
    {
      PDG.push_back(pdg_index);
    }


  }

  for(auto KE_index : nonmuon_KE)
  {
    if(KE_index != -9999)
    {
      E.push_back(KE_index); // into GeV
    }

  }

  for(auto Angle_nonmuon_index : Angle_nonmuon)
  {
    if(Angle_nonmuon_index != -9999)
    {
      Angle.push_back(Angle_nonmuon_index*TMath::RadToDeg());
    }
  }

  for(auto true_energy_fr_index : TrueEnergyFr)
  {
    if(true_energy_fr_index != -9999)
    {
      True_energyFraction.push_back(true_energy_fr_index); // into GeV
    }

  }
  int  a = PDG.size();
  int  b = E.size();
  int  c = Angle.size();
  int  d = IntialX.size();
  int  e = IntialY.size();
  int  f = IntialZ.size();
  int  g = FinalX.size();
  int  h = FinalY.size();
  int  i = FinalZ.size();
  int  j = True_energyFraction.size();

  std::vector<int> numbers = {a,b,c,d,e,f,g,h,i,j};

  if(std::count(std::begin(numbers), std::end(numbers), numbers.front()) != numbers.size()){
    int kk=0;
    for(auto cat : numbers ){
      std::cout<<"index = "<< kk <<" size of numbers "<< cat <<std::endl;
    kk++;
  }
  for(auto cat :PDG){std::cout<<"PDG = "<< cat<<std::endl;}
  for(auto cat :pdg_nonmuon){std::cout<<"pdg_nonmuon = "<< cat<<std::endl;}
  for(auto cat :E){std::cout<<"E = "<< cat<<std::endl;}
  for(auto cat :Angle){std::cout<<"Angle = "<< cat<<std::endl;}
  for(auto cat :IntialX){std::cout<<"IntialX = "<< cat<<std::endl;}
  for(auto cat :IntialY){std::cout<<"IntialY = "<< cat<<std::endl;}
  for(auto cat :IntialZ){std::cout<<"IntialZ = "<< cat<<std::endl;}
  for(auto cat :FinalX){std::cout<<"FinalX = "<< cat<<std::endl;}
  for(auto cat :FinalY){std::cout<<"FinalY = "<< cat<<std::endl;}
  for(auto cat :FinalZ){std::cout<<"FinalZ = "<< cat<<std::endl;}
  for(auto cat :True_energyFraction){std::cout<<"True_energyFraction = "<< cat<<std::endl;}
  std::cout<<"Error  The  Compoents are not the same size in the GetVector_ALLTrajector_ForWithRecoTracks "<< std::endl;
  assert(1);
}

 Trajector_withTrueEnergyFraction Event_trajectors = {RunInfo,PDG,E,Angle,True_energyFraction,IntialX,IntialY,IntialZ,FinalX,FinalY,FinalZ};
 return Event_trajectors;


}
///////////////////////////////////////////////////////////////////////////////
// Get RECO Calculated Quantities (always MeV, radians)
//////////////////////////////////////////////////////////////////////////
TRUE_RECO_Energies_Trajectors  HeliumCVUniverse::TRUE_RECO_Energies_TrajectorsStuct() const{

  auto run = GetMCRunN();
  auto subrun = GetMCSubRunN();
  auto gate = GetMCGateN();
  auto slice  = GetMCSliceN();

  SliceID RunInfo={run,subrun,gate,slice};

  std::vector<int> RECO_pdg;
  std::vector<double> RECO_KE;
  std::vector<double> RECO_angle;
  std::vector<double> RECO_TRUE_EnergyFraction;

  auto KE_muon = GetTRUE_Emu() * 1000.0; // to MeV
  auto angle = GetTRUE_muANGLE_WRTB_rad();
  RECO_pdg.push_back(13);
  RECO_KE.push_back(KE_muon);
  RECO_angle.push_back(angle);
  RECO_TRUE_EnergyFraction.push_back(-9999);

  auto RECOpdg = GetVector_nonMuonTk_PDG();
   for(auto pdg:RECOpdg){RECO_pdg.push_back(pdg);}
  auto RECOnonmuon_KE = GetVector_nonMuonTk_Energy_MeV();
   for(auto KE:RECOnonmuon_KE){RECO_KE.push_back(KE);}
  auto RECOAngle_nonmuon = GetVector_nonMuonTk_Angle_wrtb_rad();
   for(auto angle:RECOAngle_nonmuon){RECO_angle.push_back(angle);}
  auto RECOTrueEnergyFraction = Get_TrueFractionE_vector();
   for(auto true_energy_fraction:RECOTrueEnergyFraction){RECO_TRUE_EnergyFraction.push_back(true_energy_fraction);}


   auto PDG_trajector = GetVector_ALLTrajector_PDG();
   auto KE_trajector = GetVector_ALLTrajector_E();
   auto Angle_trajector = GetVector_ALLTrajector_Angle();

   auto PDG_FSParticles = GETvector_PDG_FS_particles();
   auto KE_mcFSParticles = GETvector_Energy_mc_FS_particles();
   auto theta_FSParicles = GETvector_theta_wrtb_FS_particles();


   TRUE_RECO_Energies_Trajectors output = {RunInfo,
                                       PDG_FSParticles, KE_mcFSParticles, theta_FSParicles,
                                       PDG_trajector, KE_trajector, Angle_trajector,
                                       RECO_pdg, RECO_KE, RECO_angle, RECOTrueEnergyFraction};
    //
    return output;
}
////
TRUE_RECO_Energies_Trajectors  HeliumCVUniverse::TRUE_RECO_Energies_TrajectorsStuct_Parent() const{

  auto run = GetMCRunN();
  auto subrun = GetMCSubRunN();
  auto gate = GetMCGateN();
  auto slice  = GetMCSliceN();

  SliceID RunInfo={run,subrun,gate,slice};

  std::vector<int> RECO_pdg;
  std::vector<double> RECO_KE;
  std::vector<double> RECO_angle;
  std::vector<double> RECO_TRUE_EnergyFraction;

  auto KE_muon = GetTRUE_Emu() * 1000.0; // to MeV
  auto angle = GetTRUE_muANGLE_WRTB_rad();
  RECO_pdg.push_back(13);
  RECO_KE.push_back(KE_muon);
  RECO_angle.push_back(angle);
  RECO_TRUE_EnergyFraction.push_back(-9999);

  auto RECOpdg = GetVector_nonMuonTk_PDG_Parent();
   for(auto pdg:RECOpdg){RECO_pdg.push_back(pdg);}
  auto RECOnonmuon_KE = GetVector_nonMuonTk_Energy_MeV_Parent();
   for(auto KE:RECOnonmuon_KE){RECO_KE.push_back(KE);}
  auto RECOAngle_nonmuon = GetVector_nonMuonTk_Angle_wrtb_rad_Parent();
   for(auto angle:RECOAngle_nonmuon){RECO_angle.push_back(angle);}
  auto RECOTrueEnergyFraction = Get_TrueFractionE_vector();
   for(auto true_energy_fraction:RECOTrueEnergyFraction){RECO_TRUE_EnergyFraction.push_back(true_energy_fraction);}


   auto PDG_trajector = GetVector_ALLTrajector_PDG();
   auto KE_trajector = GetVector_ALLTrajector_E();
   auto Angle_trajector = GetVector_ALLTrajector_Angle();

   auto PDG_FSParticles = GETvector_PDG_FS_particles();
   auto KE_mcFSParticles = GETvector_Energy_mc_FS_particles();
   auto theta_FSParicles = GETvector_theta_wrtb_FS_particles();


   TRUE_RECO_Energies_Trajectors output = {RunInfo,
                                       PDG_FSParticles, KE_mcFSParticles, theta_FSParicles,
                                       PDG_trajector, KE_trajector, Angle_trajector,
                                       RECO_pdg, RECO_KE, RECO_angle, RECOTrueEnergyFraction};
    //
    return output;
}






// HeliumCVUniverse_cxx
