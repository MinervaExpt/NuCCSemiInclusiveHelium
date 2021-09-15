
//==============================================================================
//File: HeliumCuts.h
////Brief: The header for HeliumCuts.cxx
////  Contains functionality  for applying Cuts to the Helium ntuple
////Author: Christian Nguyen christian2nguyen@ufl.edu
//// ========================================================================



#ifndef HELIUMCUTS_H
#define HELIUMCUTS_H

#include <vector>
#include "HeliumCVUniverse.h"
#include "HeliumDefaults.h" // enum ECuts, CCNuPionIncConsts, ContainerEraser
#include "CryoTankUtils.h"

//==============================================================================
// USE THESE CUTS by applying a  vector of different cuts to  PassesCutsRECO or  PassesCutsTRUTH
//
//==============================================================================




namespace HeliumCUTConsts {


  const int NeutrinoPDGType = 14;
  const int HeliumZ= 2;

  const double Maximum_MuonAngle = 12.0;


  const double Maximum_SigCurvature = -5.0;

  const int MC_currentType = 1; //1 CC 2 NC

  const int Neutrino_Muon_Chargetype = -1;

  const int GreaterthanNTracks= 1;

  const double Muon_Minimum_Energy = 2000; // MeV
  const double Muon_Maximum_Energy = 50000; // MeV

  const double VextexMiniumDisToCryoTankInnerTank = 20.0; // mm For Cut Value

  const double CryoTankExtraAddRegionOutside = 450.0; // mm Cut Cut Value for Smearing
// was 200mm

  const double Truth_pion_Minimum_Energy = .060; // GeV
  const double Truth_proton_Minimum_Energy = .110; // GeV
  const double Truth_dimuon_Maximum_Energy = .060; // GeV
  const double Truth_HardonAngle_wrtb_Maximum = 60; //deg
  const double Truth_EFractionAreTrueDigits = 0.50; //

  const double Maximum_secTrkwrtb_CUT = 54;
  const double Maximum_secTrkwrtb_GreatestKE = 54; // For Truth Section of index of second track with Greatest KE

  const double Maximum_VertexChiSqrt = 200.0;

  const double Maximum_Longtrack_VertexChiSqrt = 40.0; //25 // 40
  const double Maximum_OtherLongtrack_VertexChiSqrt = 40; //20 // 40
  const double Maximum_Short_VertexChiSqrt = 25.0; //10 // 25





/*



std::vector<Particle_type> Particle;
Particle.push_back(kProton);
Particle.push_back(kPion);
Particle.push_back(kMuon);
  const std::vector<Particle_type> kSecondary_particle_vector;
  kSecondary_particle_vector.push_back(kProton);
  kSecondary_particle_vector.push_back(kPion);
  kSecondary_particle_vector.push_back(kMuon);
  */

}


//==============================================================================
// These cuts were made in the ana tool
// So for reco data and MC these are always true.
//==============================================================================


//==============================================================================
// Function Declarations
//==============================================================================

bool PassesCutsRECO(const HeliumCVUniverse& , bool is_mc ,std::vector<ECuts> cuts);
bool PassesCutsRECO(const HeliumCVUniverse& univ, bool is_mc ,std::vector<ECuts> cuts, std::vector<Weights> kWeights, RECO_Cut_Map &CountMap);
bool PassesCutsRECO(const HeliumCVUniverse& univ, bool is_mc ,std::vector<ECuts> cuts, std::vector<Weights> kWeights, RECO_Cut_Map &CountMap,RECO_Cut_Map &CountMap_TrueHelium, RECO_Cut_Map &CountMap_nothelium);
bool PassesCutsRECOData(const HeliumCVUniverse& univ, bool is_mc ,std::vector<ECuts> cuts, RECO_Cut_Map &CountMap);
bool PassesCut(const HeliumCVUniverse&, ECuts cut, bool is_mc) ;
bool PassesCutsTRUTH(const HeliumCVUniverse&, std::vector<ECutsTRUTH> TRUTHcuts) ;
bool PassesCutsTRUTH(const HeliumCVUniverse& univ, std::vector<ECutsTRUTH> TRUTHcuts, std::vector<Weights> kWeights, TRUE_Cut_Map &CountMap);
bool PassesTRUTH(const HeliumCVUniverse&, ECutsTRUTH cut) ;



// Get a vector of integers which are unique hadron prong identifiers.
// The length of this vector is the number of pion candidate tracks found.
//std::vector<int> GetPionCandidates(HeliumCVUniverse&);

// Helper
 std::string GetCutName(ECuts cut);
 std::string GetCutNameforLatex(ECuts cut);
 std::string GetCutNameforRootLatex(ECuts cut);
 std::string GetCutNameTRUTH(ECutsTRUTH cut);
 std::string GetCutNameLatexTRUTH(ECutsTRUTH cut);
 std::string GetCutNameLatexforRootTRUTH(ECutsTRUTH cut);
//Cuts functions -- eventwide -- TRUTH ONLY


 bool TRUTH_IsTargetTypeHelium(const HeliumCVUniverse&);
 bool TRUTH_IsNeutrino(const HeliumCVUniverse&);
 bool TRUTH_IsCCInteractionType(const HeliumCVUniverse&);
 bool TRUTH_IsMuonGoodEnergy(const HeliumCVUniverse&);
 bool TRUTH_IsMuonAngleGood(const HeliumCVUniverse&);
 bool TRUTH_IsINFiduicalVolume(const HeliumCVUniverse&);
 bool TRUTH_IsINFiduicalVolume(const HeliumCVUniverse& univ, double Cut_MiniumDisToCryoTankInnerTank);
 bool TRUTH_IsINFiduicalVolume_EXTRA(const HeliumCVUniverse& univ);
 bool Truth_hardonCut_Threshold_EnergyPROTON(const HeliumCVUniverse& univ);
 bool Truth_hardonCut_Threshold_EnergyPIONS(const HeliumCVUniverse& univ);
 bool Truth_hardonCut_Threshold_EnergyDiMuon(const HeliumCVUniverse& univ);

 bool  TRUTH_GreaterthanONEFS(const HeliumCVUniverse& univ);

 bool  TRUTH_EnergyFraction_AreTrueDigits(std::vector<double> E_Fraction, int index, double Cut_fraction = HeliumCUTConsts::Truth_EFractionAreTrueDigits );

//RECO cuts eventwide
 int    SixPush       (const HeliumCVUniverse&);
 int    IsVeto        (const HeliumCVUniverse&);
 double MuonAngle     (const HeliumCVUniverse&);
 bool   CoilCut       (const HeliumCVUniverse&);
 bool   IsMinsoMatch  (const HeliumCVUniverse&);
 bool   IsUsableMuon  (const HeliumCVUniverse&);
 int    MuonChange    (const HeliumCVUniverse&);
 bool   Only1Track (const HeliumCVUniverse&);
 int    NumberTracks  (const HeliumCVUniverse&);
 int    DidVertexConverge ( const HeliumCVUniverse& );

 bool IsGoodEnergy  ( const HeliumCVUniverse&);
 bool IsNTracksGood (const HeliumCVUniverse&) ;
 bool IsSixPushGood(const HeliumCVUniverse&) ;
 bool IsVertexConvergeGood(const HeliumCVUniverse&) ;
 bool IsMuonChargeGood(const HeliumCVUniverse&) ;
 bool IsMuonAngleGood(const HeliumCVUniverse& ) ;
 bool IsTrackForwardGoing(const HeliumCVUniverse& ) ;
 bool IsInFiduicalVolume(const HeliumCVUniverse& );
 bool IsInFiduicalVolume(const HeliumCVUniverse& univ, double Cut_MiniumDisToCryoTankInnerTank);
 bool IsInExtraFiduicalVolume(const HeliumCVUniverse& univ);
 bool IsInExtraFiduicalVolume(const HeliumCVUniverse& univ, double Cut_MiniumDisToCryoTankInnerTank);
 bool IsInExtraFiduicalVolume_Non_seperated_Cryo_regions(const HeliumCVUniverse& univ, double Cut_MiniumDisToCryoTankInnerTank);
 bool IsMuon_CurvatureGreater( const HeliumCVUniverse& , double CurvatureInput ) ;
 bool IsGoodCurvatureSignificance (const HeliumCVUniverse& ) ;
 bool  NonMuon_Plausible(const HeliumCVUniverse& univ, bool IsMC);
 bool  Muon_Plausible (const HeliumCVUniverse& univ, bool IsMC);
 bool  nonmu_is_plausible  ( const HeliumCVUniverse& ) ;
 bool  mu_is_plausible  ( const HeliumCVUniverse& ) ;
 bool  ISMuonAngle_Cutgood( const HeliumCVUniverse& ) ;
 bool  IsVetoGood(const HeliumCVUniverse& );
 bool  IsMINOSFiduicalVolumnGood(const HeliumCVUniverse& );
 bool IssecTrklessthanDeg(const HeliumCVUniverse& univ , double Max_deg = HeliumCUTConsts::Maximum_secTrkwrtb_CUT);
 bool IsVertexChiSqrtLessthanMax(const HeliumCVUniverse& univ , double Max_chisqrt = HeliumCUTConsts::Maximum_VertexChiSqrt);
 bool IsVertexChiSqrtLessthanMax_ByTrackType(const HeliumCVUniverse& univ , double Max_chisqrt_long= HeliumCUTConsts::Maximum_Longtrack_VertexChiSqrt, double Max_chisqrt_otherlong=HeliumCUTConsts::Maximum_OtherLongtrack_VertexChiSqrt, double Max_chisqrt_short=HeliumCUTConsts::Maximum_Short_VertexChiSqrt);
 bool IsVertexConverge_usingALLTracks(const HeliumCVUniverse& univ );

 bool  TRUTH_IsAtLeastOne_2ndTrk_non_NeutralParticle(const HeliumCVUniverse& univ);
 bool  TRUTH_Is2ndTrk_maxiumAngle_threshold(const HeliumCVUniverse& univ, double Max_deg = HeliumCUTConsts::Maximum_secTrkwrtb_GreatestKE);
 bool  TRUTH_Is2ndTrk_maxiumAngle_threshold_No_Neutral(const HeliumCVUniverse& univ, double Max_deg = HeliumCUTConsts::Maximum_secTrkwrtb_GreatestKE);
 bool  TRUTH_Is2ndTrk_maxiumAngle_threshold_No_Neutral_leading2ndTrk(const HeliumCVUniverse& univ, double Max_deg = HeliumCUTConsts::Maximum_secTrkwrtb_GreatestKE);
 bool  TRUTH_Is2ndTrk_maxiumAngle_threshold_No_Neutral_WITHProtonAndPion_thresholds(const HeliumCVUniverse& univ, double Max_degMax_deg = HeliumCUTConsts::Maximum_secTrkwrtb_GreatestKE,double Pion_Energy =HeliumCUTConsts::Truth_pion_Minimum_Energy , double Proton_Energy = HeliumCUTConsts::Truth_proton_Minimum_Energy );
 bool  TRUTH_Is2ndTrk_maxiumAngle_threshold_No_Neutral_leading2ndTrk_RECOBRANCH(const HeliumCVUniverse& univ,double Max_deg = HeliumCUTConsts::Maximum_secTrkwrtb_GreatestKE);
 bool  TRUTH_Is2ndTrk_maxiumAngle_threshold_No_Neutral_And_KE_proton_pion_thresholdsleading2ndTrk_RECOBRANCH(const HeliumCVUniverse& univ, double Max_deg=HeliumCUTConsts::Maximum_secTrkwrtb_GreatestKE, double Pion_Energy = HeliumCUTConsts::Truth_pion_Minimum_Energy, double Proton_Energy = HeliumCUTConsts::Truth_proton_Minimum_Energy);
 bool  TRUTH_Is2ndTrk_threshold_No_Neutral_leading2ndTrk_RECOBRANCH(const HeliumCVUniverse& univ);

 bool  TRUTH__minimum_Energy_threshold_Pion_GeV(double energy );
 bool  TRUTH__minimum_Energy_threshold_Proton_GeV(double energy );
 bool  TRUTH__minimum_Energy_threshold_dimuon_GeV(double energy );
 bool Truth_hardonCut_Threshold_Energy(const HeliumCVUniverse& univ);
 bool GetCutExtrapolatetoDeadVetoGood(const HeliumCVUniverse& univ);

//////////////////////////////////////////////////////////////////////////////
//Counters
/////////////////////////////////////////////////////////////////////////////
#endif
