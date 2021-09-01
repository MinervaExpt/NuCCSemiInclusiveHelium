// ========================================================================
// Base class for an un-systematically shifted (i.e. CV) universe.  Implement
// your own base class with the functions you need. I've implemented GetEnu(),
// GetMuonE() and GetHadronE() as examples: you'll have other variables you
// want.
//
// To add a systematic, inherit from this class and override whichever
// functions you need to. For a "vertical" error, this will mean overriding the
// GetWeight() function to modify the event weight. For a "lateral" error, this
// will mean overriding the function that calculates the quantity that is being
// shifted (muon energy, or hadronic energy or whatever).
//
// For examples of each of those two cases, see ./LateralSystematics.h and
// PlotUtils/GenieSystematics.h. For an example of how to put the whole thing
// together and actually *use* the classes, see the runUniverseShift.C macro in
// this directory. `root -l runUniverseShift.C+`
// ========================================================================

#include "PlotUtils/MinervaUniverse.h"
#include "PlotUtils/ChainWrapper.h"
#include <iostream>
#include "TMath.h"



#ifndef HELIUMCVUNIVERSE_H
#define HELIUMCVUNIVERSE_H
#include "HeliumUtils.h"
#include "HeliumDefaults.h"
#include "HeliumCuts.h"
#include "PlotUtils/FluxSystematics.h"
#include "PlotUtils/FluxReweighter.h"
#include "PlotUtils/MinosMuonEfficiencyCorrection.h"
#include "PlotUtils/weightMK.h"
#include <TDatabasePDG.h>
#include <assert.h>

class HeliumPlayListInfo;

namespace Helium_PDG {

const int pdg_Pi0 = 111;
const int pdg_neutron = 2112;
const int pdg_antineutron = -2112;
const int pdg_Genie_bindingE = 2000000101;
const int pdg_Sigma0 =3212;
const int pdg_antiSigma0 = -3212;
const int pdg_Lambda0 =3122;
const int pdg_antiLambda0 = -3122;
const int pdg_Nu_e = 12;
const int pdg_Nu_mu = 14;
const int pdg_Proton = 2212;
const int pdg_Pion_neg = -211;
const int pdg_Pion_pos = 211;
const int pdg_Photon = 22;

}






class HeliumCVUniverse: public PlotUtils::MinervaUniverse {
public:
  #include "PlotUtils/WeightFunctions.h"
  #include "PlotUtils/MuonFunctions.h"
  #include "PlotUtils/TruthFunctions.h"

  HeliumCVUniverse(PlotUtils::ChainWrapper* chw, double nsigma=0)
  : PlotUtils::MinervaUniverse(chw, nsigma)
  {}

    // Destructor
  virtual ~HeliumCVUniverse(){}



// All functions we write here should be 'virtual', so that the universes
// that inherit from CVUniverse can override them.
//virtual bool IsInFiducalVolumeFromtheInnerEdge(double Min_distance_toShell ) const ;
// ========================================================================
// Get Weight
//
// We override the various weight getting functions herein in different
// vertical systematic universe classes.
// ========================================================================
virtual double GetWeight(HeliumPlayListInfo info) const;
virtual double GetWeight(Weights kweight) const;
virtual double GetWeight(std::vector<Weights> kweight) const;

virtual double GetTrueQ3() const;
virtual double GetTrueQ0() const;
virtual double GetTrueQ2() const;
//virtual double GetThetamu()const;
//virtual double GetPmu() const;
virtual double GetPmu_inhouse() const;
//virtual double GetEmu() const;      /* MeV */
virtual double GetTRUE_Phimu()const;
// ========================================================================
// Get Variable Functions
// Write a virtual "Get" function for _any_ variable (coming directly from a
// branch, or composed of several branches) that will be laterally shifted
// or affected by the lateral shift of a systematic universe.
//
// We override some or all of these function in different systematic
// universe classes located in LateralSystematics.h.
// ========================================================================
virtual Interaction_type Get_InteractionStackType() const;

virtual Material_type Get_MaterialStackType() const;

virtual Particle_type Get_NonParticleStackType(int trk) const;

virtual Particle_type Get_ParticleStackType_leadingandnonleading(int trk) const;

virtual  CryoTank_REGIONS Get_RECO_CryoTank_region()const;
virtual  CryoTank_REGIONS Get_TRUE_CryoTank_region()const;

virtual double GetDummyVar() const;
virtual double GetVertexChiSqrFit() const;
virtual bool GetboolIsUsableMuon() const;
virtual int GetIntIsusableMuon() const;
virtual double GetOpenAngle(int TRKNum) const;
//////////////////////////////////////////////////////////////
///Vetowall
/////////////////////////////////////////////////////////////
virtual bool Getextrapnowalls() const;
virtual bool Getextrapwall1() const;
virtual bool Getextrapwall2() const;
virtual bool Getextrapbothwalls() const;
virtual bool GetMuonTrkMatchToVETOwalloff() const;
virtual int  GetNumberMatchToVeto() const;
virtual int  GetMatchToVeto() const;
virtual int  GetSixPush() const;
virtual int GetTracksize() const;

virtual TrackType GetTrackType() const;
virtual int GetLongAnchorTrackStatus() const;
virtual int GetShortAnchorTrackStatus() const;
virtual int GetOtherLongTrackStatus() const;

 virtual bool GetVertex_option1()const;
 virtual bool GetVertex_option2()const;
 virtual bool GetVertex_option3()const;
 virtual bool GetisOneTrk() const;
 virtual bool GetisTwoTrk() const;
 virtual bool GetisGreaterTwoTrk() const;
virtual boolNTrack GetVertex_boolNTrack() const;
virtual VertexOptions GetVertex_optionType() const;


//virtual int  Get_rockMuonTruth() const;
virtual double GetDistance_vertex_toUpStreamBulge() const;
virtual double GetDistance_vertex_toDownStreamBulge()const;

//////////////////////////////////////////////////////////////
///GET Muon INFO
/////////////////////////////////////////////////////////////

virtual double GetVetoTotEff() const;
virtual double GetVetoTotAcc() const;
virtual double GetVetoAccpetedWeigh() const;
virtual double GetMuonE() const;
virtual double GetMuonE_ECT()const;

virtual std::vector <int> GetVector_PMTVeto_Map() const;


virtual double GetPmu_ECT()const;

virtual double GetMuonPz() const;
virtual double GetMuonPz_ECT()const;

virtual double GetMuonPx() const;
virtual double GetMuonPx_ECT() const;
virtual double GetMuonPy() const;
virtual double GetMuonPy_ECT() const;

virtual double GetMuonPt() const;
virtual double GetMuonPt_ECT() const;

virtual double GetMuonP_three_momentum_absolute() const;


virtual double GetVertex_x() const;
virtual double GetVertex_y() const;
virtual double GetVertex_z() const;
virtual double GetVertex_r() const;
virtual double GetVertex_rr() const;

virtual double GetCurvatureSignificance() const;
virtual double GetmuAngleWRTB() const;
virtual double GetmuAngleWRTB_Degs() const;

virtual double GetChargemu()  const;
virtual double GetDOCAmu() const;

virtual double GetMINOS_Energy() const;

virtual double GetMINOSStart_X() const;
virtual double GetMINOSStart_Y() const;
virtual double GetMINOSStart_Z() const;

virtual double GetMINOSEnd_X() const;
virtual double GetMINOSEnd_Y() const;
virtual double GetMINOSEnd_Z() const;

virtual double GetMuon_firstNode_X() const;
virtual double GetMuon_firstNode_Y() const;
virtual double GetMuon_firstNode_Z() const;

virtual double GetMuon_lastNode_X() const;
virtual double GetMuon_lastNode_Y() const;
virtual double GetMuon_lastNode_Z() const;

virtual std::vector <double> GetVector_firstNode_X() const;
virtual std::vector <double> GetVector_firstNode_Y() const;
virtual std::vector <double> GetVector_firstNode_Z() const;
virtual std::vector <double> GetVector_lastNode_X() const;
virtual std::vector <double> GetVector_lastNode_Y() const;
virtual std::vector <double> GetVector_lastNode_Z() const;

virtual std::vector <double> Get_RecoilVector_firstNode_X() const;
virtual std::vector <double> Get_RecoilVector_firstNode_Y() const;
virtual std::vector <double> Get_RecoilVector_firstNode_Z() const;
virtual std::vector <double> Get_RecoilVector_lastNode_X() const;
virtual std::vector <double> Get_RecoilVector_lastNode_Y() const;
virtual std::vector <double> Get_RecoilVector_lastNode_Z() const;

virtual std::vector <double> GetVector_GetNonmuTrkLength_InMinerva_Incm() const;

virtual std::vector <double> GetVector_GetNonmuTrkE() const;
virtual std::vector <double> GetVector_NonmuTrkAngleWRTbeamMID() const;

virtual int GetRunN() const;
virtual int GetSubRunN() const;
virtual int GetGateN() const;
virtual int GetSliceN() const;

virtual SliceID GetEventSliceForData() const;


virtual int GetMCRunN() const;
virtual int GetMCSubRunN() const;
virtual int GetMCGateN() const;
virtual int GetMCSliceN() const;


virtual std::vector <int> GetEventRun() const ;

virtual double GetTotalMomentum(double px,double py,double pz) const;

//////////////////////////////////////////////////////////////
///MUON TRUTH INFO
/////////////////////////////////////////////////////////////
virtual int Get_mc_incoming() const;
virtual int Get_mc_current() const;

virtual double GetTRUE_Emu()  const;
virtual double GetTRUE_Pmu()  const;
virtual double GetTRUE_PZmu() const;
virtual double GetTRUE_muANGLE_WRTB_DEG() const;
virtual double GetTRUE_PTmu() const;

virtual double GetQ2True_GeV() const;

virtual int GetTRUE_Tracksize() const;

virtual double distance_betweenPoints(double x1, double y1, double z1, double x2, double y2, double z2);
virtual int Trajectorindex_leastdistance(double x1, double y1, double z1, std::vector <double>FinalX,std::vector <double>FinalY,std::vector <double>FinalZ );
virtual int  getindexTrueTrajectors_closestRECO();

virtual double GetTRUE_Vertex_x() const;
virtual double GetTRUE_Vertex_y() const;
virtual double GetTRUE_Vertex_z() const;
virtual double GetTRUE_Vertex_r() const;
virtual double GetTRUE_Vertex_rr() const;
virtual Vertex_XYZ GetTRUE_Vertex3Dpoint()const;
virtual std::vector <double> MakeTRUE_VectorTrackLengthinMinerva_mm() const;
virtual std::vector <double> MakeTRUE_VectorTrackLengthinMinerva_cm() const;

virtual double GetTRUE_NonmuTrkE(int TRKNum) const;
virtual double GetTRUE_NonmuTrkopenangle(int TRKNum) const;
virtual double GetTRUE_NonmuTrkANGLE_WRTB(int TRKNum) const;

virtual double GetTRUE_NonmuTrkE_Parent(int TRKNum) const;
virtual double GetTRUE_NonmuTrkopenangle_Parent(int TRKNum) const;
virtual double GetTRUE_NonmuTrkANGLE_WRTB_Parent(int TRKNum) const;
virtual int GetTRUE_NonmuTrk_PDG_Parent(int TRKNum) const;


virtual std::vector <int> GetVector_nonMuonTk_PDG() const;
virtual std::vector <double> GetVector_nonMuonTk_Angle_wrtb_rad() const;
virtual std::vector <double> GetVector_nonMuonTk_Angle_wrtb_Degs() const;
virtual std::vector <double> GetVector_nonMuonTk_Energy_MeV() const;
virtual std::vector <double> GetVector_nonMuonTk_Energy_GeV() const;


virtual std::vector <int> GetVector_nonMuonTk_PDG_Parent() const;
virtual std::vector <double> GetVector_nonMuonTk_Angle_wrtb_rad_Parent() const;
virtual std::vector <double> GetVector_nonMuonTk_Angle_wrtb_Degs_Parent() const;
virtual std::vector <double> GetVector_nonMuonTk_Energy_MeV_Parent() const;
virtual std::vector <double> GetVector_nonMuonTk_Energy_GeV_Parent() const;

virtual std::vector <int> GETvector_PDG_FS_particles()const;
virtual std::vector <double> GETvector_Energy_mc_FS_particles()const;
virtual std::vector <double> GETvector_KE_mc_FS_particles_MeV(TDatabasePDG *pdg_DATABASEobject)const;
virtual std::vector <double> GETvector_KE_mc_FS_particles_GeV(TDatabasePDG *pdg_DATABASEobject)const;

virtual std::vector <double> GETvector_Px_mc_FS_particles()const;
virtual std::vector <double> GETvector_Py_mc_FS_particles()const;
virtual std::vector <double> GETvector_Pz_mc_FS_particles()const;
virtual std::vector <double> GETvector_theta_wrtb_FS_particles() const;
virtual std::vector <double> GETvector_Energy_mc_FS_particles_MeVtoGeV()const;

virtual std::vector <double> FromTRUTH_branch_GetVector_lastNode_X() const;
virtual std::vector <double> FromTRUTH_branch_GetVector_lastNode_Y() const;
virtual std::vector <double> FromTRUTH_branch_GetVector_lastNode_Z() const;

virtual std::vector <Vertex_XYZ> Construct_EndPointvector_ForTRUE_FS_particle ()const;

virtual int Get_Index_highestKE_mc_FSPart()const;
virtual int GET_N_PDG_FS_particles()const;
virtual int Get_Index_LowestKE_mc_FSPart() const;
virtual double ThetaWRTBeam(double x , double y, double z, double bias) const;


virtual int Getindex2ndTrack_TRUE_highestKE()const;
virtual int Getindex2ndTrackhighestKE() const;

virtual int GetIntactionType() const;
virtual int GetTargetType() const;
virtual int GetNon_muon_PDG(int TRKNum )const;



//////////////////////////////////////////////////////////////////////////
//Get Non MuonTrk Info
//////////////////////////////////////////////////////////////////////////



virtual double GetNonmuTrkE(int TRKNum) const;
virtual double GetNonmuTrkE_GeV(int TRKNum) const;
virtual double GetNonmuTrkAngleWRTbeam(int TRKNum) const;
virtual double GetNonmuTrkAngleWRTbeamMID(int TRKNum) const;


virtual double GetNonmuTrkAngleWRTmu(int TRKNum) const;
virtual double GetNonmuTrkLength(int TRKNum) const;
virtual double GetNonmuDOCA(int TRKNum) const;
virtual double GetNonmuTrkTimes(int TRKNum) const;


virtual double GetFirstNodeX(int TRKNum) const;
virtual double GetLastNodeX(int TRKNum) const;
virtual double GetFirstNodeY(int TRKNum) const;
virtual double GetLastNodeY(int TRKNum) const;
virtual double GetFirstNodeZ(int TRKNum) const;
virtual double GetLastNodeZ(int TRKNum) const;

virtual double GetNonmuTrkLength_InMinerva(int TRKNum)const;
virtual double GetNonmuTrkLength_InMinerva_Incm(int TRKNum)const;

virtual Trajector_DATA Return_Trajector_DATA_struct() const;

virtual double rapidity_muon() const;
virtual double pseudorapidity_muon() const;


virtual double GetQ2forMKmodel() const;
virtual double GetWforMKmodel() const;
virtual int GetCCforMKmodel() const;
virtual int GetnPartforMKmodel() const;

virtual int GetnIDstatusforMKmodel(int index)const;
virtual int GetnIDforMKmodel(int index)const;
virtual double GetMKmodelWeight_local(weightMK *weight_MK)const;
virtual int Returnindex_True_2ndTk_GreatestKE_lessthanAngle(std::vector <int> PDG_trklist, std::vector <double> Energy_trklist, std::vector <double> Angle_trklist )const;

virtual int Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_lessthanAngle(std::vector <int> PDG_trklist, std::vector <double> Energy_trklist, std::vector <double> Angle_trklist ) const;
virtual int Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_lessthanAngle_withKE_thresholdonProtonandPion(std::vector <int> PDG_trklist, std::vector <double> Energy_trklist, std::vector <double> Angle_trklist, std::vector <double> truedigitEfraction_vector ) const;
virtual int Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_lessthanAngle_withKE_thresholdonProtonandPion(std::vector <int> PDG_trklist, std::vector <double> Energy_trklist, std::vector <double> Angle_trklist ) const;

virtual int Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE(std::vector<int> PDG_trklist, std::vector<double> Energy_trklist) const;
virtual int Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_muonNotinlist(std::vector<int> PDG_trklist, std::vector<double> Energy_trklist, std::vector <double> truedigitEfraction_vector  ) const;
virtual int Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_lessthanAngle_muonNotinlist(std::vector <int> PDG_trklist, std::vector <double> Energy_trklist, std::vector <double> Angle_trklist, std::vector <double> truedigitEfraction_vector ) const;
virtual int Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_lessthanAngle_muonNotinlist_KE_proton_pion_thrusthold(std::vector <int> PDG_trklist, std::vector <double> Energy_trklist, std::vector <double> Angle_trklist, std::vector <double> truedigitEfraction_vector ) const;
//////////////////////////////////////////////////////////////
///Get TRUTH Non MuonTrk Info
/////////////////////////////////////////////////////////////

virtual double GetTRUENonmuTrkE(int TRKNum) const;
virtual double GetTRUENonmuTrkAngleWRTbeam(int TRKNum) const;
virtual double GetTRUENonmuTrkAngleWRTmu(int TRKNum) const;
virtual int    GetPDG_2ndTrk_highestEnergy() const;
virtual int    GetPDG_2ndTrk_highestTRUEEnergy() const;
virtual double GetTRUE_nonMuonDOCA(int TRKNum) const;
virtual double GetTRUE_nonMuoncolumnarDensity(int TRKNum) const;
//robs method
virtual double GetPmuTransverseTrue() const;
virtual double GetPmuLongitudinalTrue() const;
virtual double GetTRUE_muANGLE_WRTB_rad() const;

virtual int Get_index_Trajector_PDG(int index) const;

virtual Trajector GetVector_ALLTrajector() const;
virtual Trajector GetVector_ALLTrajector_ForWithRecoTracks() const ;
virtual Trajector GetVector_ALLTrajector_ForWithRecoTracks_Parent() const;
virtual Trajector_withTrueEnergyFraction GetVector_ALLTrajector_ForWithRecoTracks_withTrueEFraction() const;
virtual Trajector_withTrueEnergyFraction GetVector_ALLTrajector_ForWithRecoTracks_withTrueEFraction_Parent() const;

virtual int Get_Index_highestKE_mc_FSPart_NO_NeutralParticles(std::vector<double> KE_vector, std::vector<int> pdg_vector,std::vector<double> truedigitEfraction_vector   ) const;
virtual int Get_Index_highestKE_mc_FSPart_WithDeglessthan(double Angle, std::vector<double> KE_vector, std::vector<double> angle_vector, std::vector<int> pdg_vector  ) const;
virtual int Get_Index_highestKE_mc_FSPart_WithDeglessthan_NO_NeutralParticles(double Angle, std::vector<double> KE_vector, std::vector<double> angle_vector, std::vector<int> pdg_vector  ) const;
virtual int Get_Index_highestKE_mc_FSPart_WithDeglessthan_NO_NeutralParticles_withKEpion_proton(double Angle, std::vector<double> KE_vector, std::vector<double> angle_vector, std::vector<int> pdg_vector, std::vector<double> truedigitEfraction_vector, double KE_pion, double KE_proton  ) const;
virtual int Get_Index_highestKE_mc_FSPart_WithDeglessthan_NO_NeutralParticles_withKEpion_proton(double Angle, std::vector<double> KE_vector, std::vector<double> angle_vector, std::vector<int> pdg_vector, double KE_pion, double KE_proton  ) const;

virtual int Get_Index_highestKE_mc_FSPart_NO_NeutralParticlesForTruthBranch( std::vector<double> KE_vector, std::vector<int> pdg_vector) const;

virtual int Get_Index_highestKE_NOleadingMuoninlist_WithDeglessthan_NO_NeutralParticles(double Angle,std::vector<double> KE_vector, std::vector<double> angle_vector, std::vector<int> pdg_vector, std::vector<double> truedigitEfraction_vector ) const;
virtual int Get_Index_highestKE_NOleadingMuoninlist_WithDeglessthan_NO_NeutralParticles_WithProton_pionKEthreshold(double Angle, std::vector<double> KE_vector, std::vector<double> angle_vector, std::vector<int> pdg_vector, std::vector<double> truedigitEfraction_vector,double KE_pion, double KE_proton ) const;
virtual std::vector<double> GetVector_ALLTrajector_P(std::string input) const;
virtual std::vector<double> GetVector_ALLTrajector_InitalPosition(std::string input) const ;
virtual std::vector <int> GetVector_ALLTrajector_PDG() const;
virtual std::vector<double> GetVector_ALLTrajector_FinalPosition(std::string input) const ;
virtual std::vector <double> GetVector_ALLTrajector_Angle() const;
virtual std::vector <double> GetVector_ALLTrajector_DOCA() const;
virtual std::vector <double> GetVector_ALLTrajector_E() const;
virtual std::vector <double> GetVector_ALLTrajector_TrkLength() const;
virtual std::vector <double> GetVector_ALLTrajector_columnarDensity()const;
virtual int Get_ALLTrajector_tracksize() const;
virtual TRUE_RECO_Energies_Trajectors TRUE_RECO_Energies_TrajectorsStuct() const;
virtual TRUE_RECO_Energies_Trajectors TRUE_RECO_Energies_TrajectorsStuct_Parent() const;

virtual std::vector <int> Get_TRUE_vector_ALL_Event_PDG() const;
virtual int Get_TRUE_Mother_index() const;
virtual int Get_TRUE_firstdaughter_index() const;
virtual int Get_TRUE_lastdaughter_index() const;
virtual std::vector<double> Get_TrueFractionE_vector() const;
virtual std::vector <int> Get_TRUE_indexs() const;


//virtual PlotUtils::MnvH1D* CreateFluxHist();






//////////////////////////////////////////////////////////////
///End of Fucntion
/////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////
///End of Fucntion
/////////////////////////////////////////////////////////////








}; // End of Header

#endif
