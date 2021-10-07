#include "HeliumCuts.h"
//#include<map>
//need to change so all function varibles are got from functions decleared in CVU
TDatabasePDG *pdg_DATABASEobject_forCUTs = TDatabasePDG::Instance();

std::vector<Particle_type>  GetParicle_typeTRUTH();
const std::vector<Particle_type> kSecondary_particle_vector = GetParicle_typeTRUTH();

std::vector<Particle_type> GetParicle_typeTRUTH() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<Particle_type> Particle;
  Particle.push_back(kProton);
  Particle.push_back(kPion_0);
  Particle.push_back(kPion_neg);
  Particle.push_back(kPion_pos);
  Particle.push_back(kMuon);

  return Particle;
//#endif
}

bool PassesCutsRECO(const HeliumCVUniverse& univ, bool is_mc ,std::vector<ECuts> cuts)
{
  #ifndef __CINT__
  bool pass = true;

  for (auto c : cuts){
    pass = pass && PassesCut(univ, c, is_mc);
  }

  return pass;
  #endif // __CINT__
}

bool PassesCutsRECO(const HeliumCVUniverse& univ, bool is_mc ,std::vector<ECuts> cuts, std::vector<Weights> kWeights, RECO_Cut_Map &CountMap)
{
  #ifndef __CINT__
  bool pass = true;
  for (const auto c : cuts){
    pass = pass && PassesCut(univ, c, is_mc);

    if(isCV(univ) && pass==true){
      double weight = univ.GetWeight(kWeights);
      CountMap[c]+=weight;

    }
  }


  return pass;
  #endif // __CINT__
}

bool PassesCutsRECOData(const HeliumCVUniverse& univ, bool is_mc ,std::vector<ECuts> cuts, RECO_Cut_Map &CountMap)
{
  #ifndef __CINT__
  bool pass = true;
  for (const auto c : cuts){
    pass = pass && PassesCut(univ, c, is_mc);

    if(pass==true){

      CountMap[c]+=1.0;

    }
  }

  return pass;
  #endif // __CINT__
}

bool PassesCutsRECO(const HeliumCVUniverse& univ, bool is_mc ,std::vector<ECuts> cuts, std::vector<Weights> kWeights, RECO_Cut_Map &CountMap,RECO_Cut_Map &CountMap_TrueHelium, RECO_Cut_Map &CountMap_nonHelium)
{
  #ifndef __CINT__
  bool pass = true;

  for (auto c : cuts){
    pass = pass && PassesCut(univ, c, is_mc);
    if(isCV(univ) && pass==true){
      double weight = univ.GetWeight(kWeights);
      CountMap[c]+=weight;
      if(univ.GetTargetType()==2)
      {
        CountMap_TrueHelium[c]+=weight;
      }
      else{
        CountMap_nonHelium[c]+=weight;
      }

    }
  }

  return pass;
  #endif // __CINT__
}

bool  PassesCutsTRUTH(const HeliumCVUniverse& univ, std::vector<ECutsTRUTH> TRUTHcuts) {
  #ifndef __CINT__

  bool pass = true;
  for (auto c : TRUTHcuts){
    pass = pass && PassesTRUTH(univ, c);
  }

  return pass;
  #endif // __CINT__
}

bool  PassesCutsTRUTH(const HeliumCVUniverse& univ, std::vector<ECutsTRUTH> TRUTHcuts, std::vector<Weights> kWeights , TRUE_Cut_Map &CountMap) {
  #ifndef __CINT__

  bool pass = true;
  for (auto c : TRUTHcuts){
    pass = pass && PassesTRUTH(univ, c);
    if(isCV(univ) && pass==true){
      double weight = univ.GetWeight(kWeights);
      CountMap[c]+=weight;
    }
  }

  return pass;
  #endif // __CINT__
}



bool  PassesCut(const HeliumCVUniverse& univ, ECuts cut, bool is_mc) {
  #ifndef __CINT__

  switch (cut) {

    case kNoCuts:
    return true;

    case kGoodEnergy:
    return IsGoodEnergy(univ);

    case kMuonAngle:
    return IsMuonAngleGood(univ);

    case kFiducialVolume:
    return IsInFiduicalVolume(univ);

    case kFiducialVolume_ExtraShell:
    return IsInExtraFiduicalVolume(univ);

    case kMinosMatch:
    return IsMinsoMatch( univ);

    case kMinosCharge:
    return IsMuonChargeGood(univ);

    case kUsableMuon:
    return IsUsableMuon(univ) ;

    case kMinosCoil:
    return IsMINOSFiduicalVolumnGood( univ);

    case kMinosCurvature:
    return IsGoodCurvatureSignificance(univ);

    case kVertexConverge:
    return IsVertexConvergeGood(univ);

    case kThetaMu:
    return ISMuonAngle_Cutgood(univ);

    case kSix:
    return IsSixPushGood( univ);

    case kVeto:
    return IsVetoGood(univ);

    case kNonMu_is_Plausible:
    return NonMuon_Plausible(univ,is_mc);

    case kMu_is_Plausible:
    return Muon_Plausible(univ,is_mc);

    case kTrackForwardGoing:
    return IsTrackForwardGoing(univ);

    case kNTracks:
    return IsNTracksGood (univ);

    case kMatchVetoDeadPaddle:
    return  GetCutExtrapolatetoDeadVetoGood(univ);

    case ksecTrkwrtblessthanMaxAngle:
    return IssecTrklessthanDeg(univ);

    case kMaxChiSqrt:
    return IsVertexChiSqrtLessthanMax(univ);

    case kMaxChiSqrt_byTrackType:
    return IsVertexChiSqrtLessthanMax_ByTrackType(univ);

    case kVertex_ConvergedfromAllTracks:
    return IsVertexConverge_usingALLTracks(univ);

    case kAllCuts:
    return true;

    default:
    std::cout << "PassesCut Error Unknown Cut!" << cut <<   std::endl;
    return false;
  };
  #endif // __CINT__
}


//==============================================================================
// TRUTH Cut functions
//==============================================================================


bool  PassesTRUTH(const HeliumCVUniverse& univ, ECutsTRUTH cut) {
  #ifndef __CINT__

  switch (cut) {
    case kTRUTHNoCuts:
    return true;

    case  kTRUTHMuonEnergy:
    return TRUTH_IsMuonGoodEnergy(univ);

    case  kTRUTHMuonAngle:
    return TRUTH_IsMuonAngleGood(univ);

    case kTRUTHneutrino:
    return TRUTH_IsNeutrino( univ);

    case kTRUTHCCInteraction:
    return TRUTH_IsCCInteractionType(univ);

    case  kTRUTHtarget:
    return TRUTH_IsTargetTypeHelium( univ);

    case  kTRUTHFiduical:
    return TRUTH_IsINFiduicalVolume( univ);

    case kTRUTHFiduical_ExtraShell:
    return TRUTH_IsINFiduicalVolume_EXTRA( univ);

    case kTRUTH_greaterthanoneFS:
    return TRUTH_GreaterthanONEFS(univ);

    case kTRUTH_2ndTrkPionEnergythreshold:
    return Truth_hardonCut_Threshold_EnergyPIONS(univ);

    case kTRUTH_2ndTrkProtonEnergythreshold:
    return Truth_hardonCut_Threshold_EnergyPROTON( univ);

    case kTRUTH_2ndTrkDimuonEnergythreshold:
    return Truth_hardonCut_Threshold_EnergyDiMuon(univ);

    case  kTRUTH_secTrk_Angle_threshold:
    return TRUTH_Is2ndTrk_maxiumAngle_threshold(univ);

    case kTRUTH_No_Neutral_secTrk_Angle_threshold:
    return TRUTH_Is2ndTrk_maxiumAngle_threshold_No_Neutral(univ);

    case kTRUTH_atleastone_non_Neutral_secTrk:
    return TRUTH_IsAtLeastOne_2ndTrk_non_NeutralParticle(univ);

    case kTRUTH_No_Neutral_secTrk_Angle_threshold_withProtonanPionThresholds:
    return TRUTH_Is2ndTrk_maxiumAngle_threshold_No_Neutral_WITHProtonAndPion_thresholds(univ);

    case kTRUTH_No_Neutral_KEthreshold_withProtonanPionThresholds:
    return TRUTH_Is2ndTrk_No_Neutral_WITHProtonAndPion_thresholds(univ);

    case  kTRUTH_2ndTrkEnergythreshold:
    return Truth_hardonCut_Threshold_Energy( univ);

    case  kTRUTH_NoNeutral_FS_2ndTrk_RECOBRANCH:
    return TRUTH_Is2ndTrk_maxiumAngle_threshold_No_Neutral_leading2ndTrk_RECOBRANCH(univ);

    case kTRUTH_NoNeutral_FS_2ndTrk_noAngleCut_RECOBRANCH:
    return TRUTH_Is2ndTrk_threshold_No_Neutral_leading2ndTrk_RECOBRANCH(univ);

    case  kTRUTH_NoNeutral_FS_2ndTrk_withProtonanPionThresholds_RECOBRANCH:
    return TRUTH_Is2ndTrk_maxiumAngle_threshold_No_Neutral_And_KE_proton_pion_thresholdsleading2ndTrk_RECOBRANCH(univ);

    case kAllTRUTHCuts:
    return true;

    default:
      std::cout << "PassesCut Error Unknown Cut!" << cut <<   std::endl;
      return false;
  };
#endif // __CINT__
}

//////////////////////////////////////////////////////////////
///TRUTH FUNCTIONS for Cuts
/////////////////////////////////////////////////////////////


    bool  TRUTH_IsTargetTypeHelium(const HeliumCVUniverse& univ){
      if (univ.GetInt("mc_targetZ") != HeliumCUTConsts::HeliumZ)
      {return false;}
      else{return true;}
    }

    bool  TRUTH_IsNeutrino(const HeliumCVUniverse& univ){
      if (univ.GetInt("mc_incoming") != HeliumCUTConsts::NeutrinoPDGType)
      {return false;}
      else{return true;}
    }

    bool  TRUTH_IsCCInteractionType(const HeliumCVUniverse& univ){
      if (univ.GetInt("mc_current") != HeliumCUTConsts::MC_currentType)
      {return false;}
      else{return true;}
    }


    bool  TRUTH_IsMuonGoodEnergy(const HeliumCVUniverse& univ){
      double TrueMuonEnergy = univ.GetDouble("truth_true_muon_E");
      if (TrueMuonEnergy <= HeliumCUTConsts:: Muon_Minimum_Energy || TrueMuonEnergy >= HeliumCUTConsts:: Muon_Maximum_Energy )
      {return false;}
      else{return true;}
    }

    bool  TRUTH_IsMuonAngleGood(const HeliumCVUniverse& univ){
      double TrueMuonAngle = univ.GetDouble("truth_true_muon_theta")* TMath::RadToDeg();
      if (TrueMuonAngle > HeliumCUTConsts::Maximum_MuonAngle || TrueMuonAngle < 0.0)
      {return false;}
      else{return true;}
    }

    bool  TRUTH_IsINFiduicalVolume(const HeliumCVUniverse& univ){
      if (false == IsInFiducalVolumeFromtheInnerEdgeTRUTH( univ, HeliumCUTConsts::VextexMiniumDisToCryoTankInnerTank))
      {return false;}
      else{return true;}
    }

    bool  TRUTH_IsINFiduicalVolume(const HeliumCVUniverse& univ, double Cut_MiniumDisToCryoTankInnerTank){
      if (false == IsInFiducalVolumeFromtheInnerEdgeTRUTH( univ, Cut_MiniumDisToCryoTankInnerTank))
      {return false;}
      else{return true;}
    }


    bool TRUTH_IsINFiduicalVolume_EXTRA(const HeliumCVUniverse& univ){
      if (false == IsInExtendentedFiducalVolumeFromtheInnerEdge_TRUTH( univ, 0.0, HeliumCUTConsts::CryoTankExtraAddRegionOutside))
      {return false;}
      else{return true;}
    }


    bool  TRUTH_GreaterthanONEFS(const HeliumCVUniverse& univ){
      auto PDG_vector  = univ.GETvector_PDG_FS_particles();
      if (PDG_vector.size() == 1 || PDG_vector.size() == 0)
      {return false;}
      else{return true;}
    }




// correct method for Getting Energy TDatabasePDG *pdg_DATABASEobject = TDatabasePDG::Instance();

bool  TRUTH_Is2ndTrk_maxiumAngle_threshold(const HeliumCVUniverse& univ, double Max_deg){
  std::vector<int> PDG_trklist = univ.GETvector_PDG_FS_particles();
  std::vector <double> Angle_trklist = univ.GETvector_theta_wrtb_FS_particles();
  if(PDG_trklist.size()==0) return false;
  for(unsigned int i = 1; i < PDG_trklist.size(); i++ ){
    double TrueHardonangle_wrtb = Angle_trklist.at(i);
    if (TrueHardonangle_wrtb < Max_deg )
    {return true;}
  }

  return false;
}

bool  TRUTH_Is2ndTrk_maxiumAngle_threshold_No_Neutral(const HeliumCVUniverse& univ, double Max_deg){

  std::vector<int> PDG_trklist = univ.GETvector_PDG_FS_particles();
  std::vector <double> Angle_trklist = univ.GETvector_theta_wrtb_FS_particles();
  if(PDG_trklist.size()==0) return false;
  for(unsigned int i = 1; i < PDG_trklist.size(); i++ ){
    double TrueHardonangle_wrtb = Angle_trklist.at(i);
    if (TrueHardonangle_wrtb < Max_deg &&
        Helium_PDG::pdg_Pi0 != PDG_trklist.at(i) &&
        Helium_PDG::pdg_neutron != PDG_trklist.at(i) &&
        Helium_PDG::pdg_antineutron!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_Genie_bindingE!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_Sigma0!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_antiSigma0!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_Nu_e!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_Nu_mu!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_Lambda0!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_antiLambda0 != PDG_trklist.at(i) &&
        Helium_PDG::pdg_Photon != PDG_trklist.at(i)
      )
    {return true;}

  }

  return false;
}


bool  TRUTH_IsAtLeastOne_2ndTrk_non_NeutralParticle(const HeliumCVUniverse& univ){

  std::vector<int> PDG_trklist = univ.GETvector_PDG_FS_particles();
  if(PDG_trklist.size()==0) return false;
  for(unsigned int i = 1; i < PDG_trklist.size(); i++ ){
    if (Helium_PDG::pdg_Pi0 != PDG_trklist.at(i) &&
        Helium_PDG::pdg_neutron != PDG_trklist.at(i) &&
        Helium_PDG::pdg_antineutron!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_Genie_bindingE!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_Sigma0!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_antiSigma0!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_Nu_e!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_Nu_mu!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_Lambda0!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_antiLambda0 != PDG_trklist.at(i) &&
        Helium_PDG::pdg_Photon != PDG_trklist.at(i)
      )
    {return true;}

  }

  return false;
}


bool  TRUTH_Is2ndTrk_maxiumAngle_threshold_No_Neutral_WITHProtonAndPion_thresholds(const HeliumCVUniverse& univ, double Max_deg, double Pion_Energy , double Proton_Energy){

  std::vector<int> PDG_trklist = univ.GETvector_PDG_FS_particles();
  std::vector <double> Angle_trklist = univ.GETvector_theta_wrtb_FS_particles();
  std::vector<double> Energy_trklist   = univ.GETvector_KE_mc_FS_particles_GeV(pdg_DATABASEobject_forCUTs);

  if(PDG_trklist.size()==0) return false;
  for(unsigned int i = 1; i < PDG_trklist.size(); ++i ){
    double TrueHardonangle_wrtb = Angle_trklist.at(i);

    if (TrueHardonangle_wrtb < Max_deg &&
        Helium_PDG::pdg_Pi0 != PDG_trklist.at(i) &&
        Helium_PDG::pdg_neutron != PDG_trklist.at(i) &&
        Helium_PDG::pdg_antineutron!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_Genie_bindingE!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_Sigma0!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_antiSigma0!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_Nu_e!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_Nu_mu!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_Lambda0!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_antiLambda0 != PDG_trklist.at(i)  &&
        Helium_PDG::pdg_Photon != PDG_trklist.at(i) )
        {

          if(PDG_trklist.at(i)== Helium_PDG::pdg_Proton && Energy_trklist.at(i) > Proton_Energy ){return true;}
          else if((PDG_trklist.at(i) == Helium_PDG::pdg_Pion_pos || PDG_trklist.at(i) == Helium_PDG::pdg_Pion_neg) && Energy_trklist.at(i) > Pion_Energy){return true;}
          else if(PDG_trklist.at(i) != Helium_PDG::pdg_Pion_pos &&  PDG_trklist.at(i) != Helium_PDG::pdg_Pion_neg && PDG_trklist.at(i) != Helium_PDG::pdg_Proton){return true;}

        }

  }

  return false;
}
///////////////////

bool  TRUTH_Is2ndTrk_No_Neutral_WITHProtonAndPion_thresholds(const HeliumCVUniverse& univ, double Pion_Energy , double Proton_Energy){

  std::vector<int> PDG_trklist = univ.GETvector_PDG_FS_particles();
  std::vector<double> Energy_trklist   = univ.GETvector_KE_mc_FS_particles_GeV(pdg_DATABASEobject_forCUTs);

  if(PDG_trklist.size()==0) return false;

  for(unsigned int i = 1; i < PDG_trklist.size(); ++i ){
    if (Helium_PDG::pdg_Pi0 != PDG_trklist.at(i) &&
        Helium_PDG::pdg_neutron != PDG_trklist.at(i) &&
        Helium_PDG::pdg_antineutron!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_Genie_bindingE!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_Sigma0!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_antiSigma0!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_Nu_e!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_Nu_mu!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_Lambda0!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_antiLambda0 != PDG_trklist.at(i)  &&
        Helium_PDG::pdg_Photon != PDG_trklist.at(i) )
        {

          if(PDG_trklist.at(i)== Helium_PDG::pdg_Proton && Energy_trklist.at(i) > Proton_Energy ){return true;}
          else if((PDG_trklist.at(i) == Helium_PDG::pdg_Pion_pos || PDG_trklist.at(i) == Helium_PDG::pdg_Pion_neg) && Energy_trklist.at(i) > Pion_Energy){return true;}
          else if(PDG_trklist.at(i) != Helium_PDG::pdg_Pion_pos &&  PDG_trklist.at(i) != Helium_PDG::pdg_Pion_neg && PDG_trklist.at(i) != Helium_PDG::pdg_Proton){return true;}

        }

  }

  return false;
}





//////////////////////
    bool  TRUTH_Is2ndTrk_maxiumAngle_threshold_No_Neutral_leading2ndTrk(const HeliumCVUniverse& univ, double Max_deg){
      std::vector<int> PDG_trklist = univ.GETvector_PDG_FS_particles();
      std::vector <double> Angle_trklist = univ.GETvector_theta_wrtb_FS_particles();
      std::vector<double> Energy_trklist   = univ.GETvector_KE_mc_FS_particles_GeV(pdg_DATABASEobject_forCUTs);
      int secondTrk =-999;

      if(PDG_trklist.size()==0) return false;
      else if(PDG_trklist.size()==1) return false; // only muon no 2nd trk
      else if( PDG_trklist.size()==2 &&
               Helium_PDG::pdg_Pi0 != PDG_trklist.at(1) &&
               Helium_PDG::pdg_neutron != PDG_trklist.at(1) &&
               Helium_PDG::pdg_antineutron!= PDG_trklist.at(1) &&
               Helium_PDG::pdg_Genie_bindingE!= PDG_trklist.at(1) &&
               Helium_PDG::pdg_Sigma0!= PDG_trklist.at(1) &&
               Helium_PDG::pdg_antiSigma0!= PDG_trklist.at(1) &&
               Helium_PDG::pdg_Nu_e!= PDG_trklist.at(1) &&
               Helium_PDG::pdg_Nu_mu!= PDG_trklist.at(1) &&
               Helium_PDG::pdg_Lambda0!= PDG_trklist.at(1) &&
               Helium_PDG::pdg_antiLambda0 != PDG_trklist.at(1) &&
               Helium_PDG::pdg_Photon != PDG_trklist.at(1)
             ){secondTrk =1;}

             else if(PDG_trklist.size() > 2){
               secondTrk = univ.Get_Index_highestKE_mc_FSPart_WithDeglessthan_NO_NeutralParticles(Max_deg, Energy_trklist, Angle_trklist, PDG_trklist );
               if(secondTrk == -999){return false;}
             }


             double TrueHardonangle_wrtb = Angle_trklist.at(secondTrk);

             if (TrueHardonangle_wrtb > Max_deg )
             {return false;}
             else{return true;}
           }






    bool  TRUTH__minimum_Energy_threshold_Pion_GeV(double energy ){
      if (energy<HeliumCUTConsts::Truth_pion_Minimum_Energy){return false;}
      else{return true;}
    }

    bool  TRUTH__minimum_Energy_threshold_Proton_GeV(double energy ){
      if (energy<HeliumCUTConsts::Truth_proton_Minimum_Energy){return false;}
      else{return true;}
    }

    bool  TRUTH__minimum_Energy_threshold_dimuon_GeV(double energy ){
      if (energy<HeliumCUTConsts::Truth_dimuon_Maximum_Energy){return false;}
      else{return true;}
    }

    bool Truth_hardonCut_Threshold_EnergyPIONS(const HeliumCVUniverse& univ){
      auto secondTrk = univ.Getindex2ndTrack_TRUE_highestKE();
      auto input_type =  univ.GetNon_muon_PDG(secondTrk);
      Particle_type GroupType = GetParticlegroup_type(input_type);

//      bool Energy_2ndtrkPass= false;
      double Sec_trk_Energy = univ.GetTRUE_NonmuTrkE(secondTrk);
      if(GroupType==kSecondary_particle_vector[1]){
        return TRUTH__minimum_Energy_threshold_Pion_GeV(Sec_trk_Energy);
      }
      else{ return true;}

    }

    bool Truth_hardonCut_Threshold_EnergyPROTON(const HeliumCVUniverse& univ){
      auto secondTrk = univ.Getindex2ndTrack_TRUE_highestKE();
      auto input_type =  univ.GetNon_muon_PDG(secondTrk);
      Particle_type GroupType = GetParticlegroup_type(input_type);

      double Sec_trk_Energy = univ.GetTRUE_NonmuTrkE(secondTrk);
      if(GroupType==kSecondary_particle_vector[0]){
        return TRUTH__minimum_Energy_threshold_Pion_GeV(Sec_trk_Energy);
      }
      else{ return true;}

    }

    bool Truth_hardonCut_Threshold_EnergyDiMuon(const HeliumCVUniverse& univ){
      auto secondTrk = univ.Getindex2ndTrack_TRUE_highestKE();
      auto input_type =  univ.GetNon_muon_PDG(secondTrk);
      Particle_type GroupType = GetParticlegroup_type(input_type);

      double Sec_trk_Energy = univ.GetTRUE_NonmuTrkE(secondTrk);
      if(GroupType==kSecondary_particle_vector[2]){
        return TRUTH__minimum_Energy_threshold_Pion_GeV(Sec_trk_Energy);
      }
      else{ return true;}

    }


    bool Truth_hardonCut_Threshold_Energy(const HeliumCVUniverse& univ){
      auto secondTrk = univ.Getindex2ndTrack_TRUE_highestKE();
      auto input_type =  univ.GetNon_muon_PDG(secondTrk);
      Particle_type GroupType = GetParticlegroup_type(input_type);

      bool Energy_2ndtrkPass= false;

      double Sec_trk_Energy = univ.GetTRUE_NonmuTrkE(secondTrk);

      if(GroupType==kSecondary_particle_vector[0]){
        Energy_2ndtrkPass=TRUTH__minimum_Energy_threshold_Proton_GeV(Sec_trk_Energy );
      }
      else if(GroupType==kSecondary_particle_vector[1]){
        Energy_2ndtrkPass=TRUTH__minimum_Energy_threshold_Pion_GeV(Sec_trk_Energy );
      }
      else if(GroupType==kSecondary_particle_vector[2]){
        Energy_2ndtrkPass=TRUTH__minimum_Energy_threshold_dimuon_GeV(Sec_trk_Energy );
      }
      else{Energy_2ndtrkPass=true;}

      return Energy_2ndtrkPass;

    }//endl function



bool TRUTH_Is2ndTrk_maxiumAngle_threshold_No_Neutral_leading2ndTrk_RECOBRANCH(const HeliumCVUniverse& univ, double Max_deg)
{
  auto PDG_trklist = univ.GetVector_nonMuonTk_PDG_Parent();
  auto Angle_trklist = univ.GetVector_nonMuonTk_Angle_wrtb_Degs_Parent();
  auto Energy_Frac = univ.Get_TrueFractionE_vector();


  for(unsigned int i = 0; i < PDG_trklist.size(); i++ ){

    double TrueHardonangle_wrtb = Angle_trklist.at(i);
    if (TrueHardonangle_wrtb < Max_deg &&
        Helium_PDG::pdg_Pi0 != PDG_trklist.at(i) &&
        Helium_PDG::pdg_neutron != PDG_trklist.at(i) &&
        Helium_PDG::pdg_antineutron!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_Genie_bindingE!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_Sigma0!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_antiSigma0!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_Nu_e!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_Nu_mu!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_Lambda0!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_antiLambda0 != PDG_trklist.at(i) &&
        Helium_PDG::pdg_Photon != PDG_trklist.at(i) &&
        -9999 != PDG_trklist.at(i) &&
        TRUTH_EnergyFraction_AreTrueDigits(Energy_Frac,i ) == true )
        {return true;}
      }// end of loop

  return false;

}//End of function



bool TRUTH_Is2ndTrk_threshold_No_Neutral_leading2ndTrk_RECOBRANCH(const HeliumCVUniverse& univ)
{
  auto PDG_trklist = univ.GetVector_nonMuonTk_PDG_Parent(); // the First entry is -9999
  auto Energy_Frac = univ.Get_TrueFractionE_vector();


  for(unsigned int i = 0; i < PDG_trklist.size(); i++ ){

    if (Helium_PDG::pdg_Pi0 != PDG_trklist.at(i) &&
        Helium_PDG::pdg_neutron != PDG_trklist.at(i) &&
        Helium_PDG::pdg_antineutron!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_Genie_bindingE!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_Sigma0!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_antiSigma0!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_Nu_e!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_Nu_mu!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_Lambda0!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_antiLambda0 != PDG_trklist.at(i) &&
        Helium_PDG::pdg_Photon != PDG_trklist.at(i) &&
        -9999 != PDG_trklist.at(i) &&
        TRUTH_EnergyFraction_AreTrueDigits(Energy_Frac,i )== true)
        {return true;}
      }// end of loop

  return false;

}//End of function


bool TRUTH_Is2ndTrk_maxiumAngle_threshold_No_Neutral_And_KE_proton_pion_thresholdsleading2ndTrk_RECOBRANCH(const HeliumCVUniverse& univ, double Max_deg, double Pion_Energy  , double Proton_Energy)
{
  auto PDG_trklist = univ.GetVector_nonMuonTk_PDG_Parent();
  auto Angle_trklist = univ.GetVector_nonMuonTk_Angle_wrtb_Degs_Parent();
  auto Energy_trklist = univ.GetVector_nonMuonTk_Energy_GeV_Parent();
  auto Energy_Frac = univ.Get_TrueFractionE_vector();

  for(unsigned int i = 0; i < PDG_trklist.size(); i++ ){

    double TrueHardonangle_wrtb = Angle_trklist.at(i);
    if (TrueHardonangle_wrtb < Max_deg &&
        Helium_PDG::pdg_Pi0 != PDG_trklist.at(i) &&
        Helium_PDG::pdg_neutron != PDG_trklist.at(i) &&
        Helium_PDG::pdg_antineutron!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_Genie_bindingE!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_Sigma0!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_antiSigma0!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_Nu_e!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_Nu_mu!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_Lambda0!= PDG_trklist.at(i) &&
        Helium_PDG::pdg_antiLambda0 != PDG_trklist.at(i) &&
        Helium_PDG::pdg_Photon != PDG_trklist.at(i) &&
        -9999 != PDG_trklist.at(i) &&
        TRUTH_EnergyFraction_AreTrueDigits(Energy_Frac,i ) == true )
        {

          if(PDG_trklist.at(i)== Helium_PDG::pdg_Proton && Energy_trklist.at(i) > Proton_Energy ){return true;}
          else if((PDG_trklist.at(i) == Helium_PDG::pdg_Pion_pos || PDG_trklist.at(i) == Helium_PDG::pdg_Pion_neg) && Energy_trklist.at(i) > Pion_Energy){return true;}
          else if(PDG_trklist.at(i) != Helium_PDG::pdg_Pion_pos &&  PDG_trklist.at(i) != Helium_PDG::pdg_Pion_neg && PDG_trklist.at(i) != Helium_PDG::pdg_Proton){return true;}
        }
      }// end of loop

  return false;

}//End of function


bool  TRUTH_EnergyFraction_AreTrueDigits(std::vector<double> E_Fraction_vector, int index, double Cut_fraction  ){


double E_Fraction = E_Fraction_vector.at(index);
if(E_Fraction < 0.0){return false;}
else if(E_Fraction < Cut_fraction ){return false;}
else{return true;}



}// End of function





/////////////////////////////

    bool GetCutExtrapolatetoDeadVetoGood(const HeliumCVUniverse& univ){
      bool did_ExtrapolatetoDeadVeto= univ.GetBool("MuonTrkMatchToVETOwalloff");
      if(did_ExtrapolatetoDeadVeto==true){return false;}
      else{return true;}

    }


//////////////////////////////////////////////////////////////
///RECO FUNCTIONS for Cuts
/////////////////////////////////////////////////////////////
// cut on max number of iso prongs
//making list of varible to cut on
bool    IsGoodEnergy  ( const HeliumCVUniverse& univ) { return univ.GetBool("cut_goodEnergy"); }
int     SixPush       ( const HeliumCVUniverse& univ) { return univ.GetInt("sixPush"); }
int     IsVeto        ( const HeliumCVUniverse& univ) { return univ.GetInt("event_IsVeto") ; }
double  MuonAngle     ( const HeliumCVUniverse& univ) { return univ.GetmuAngleWRTB_Degs(); }
bool    ISMuonAngle_Cutgood( const HeliumCVUniverse& univ) { return univ.GetBool("cut_thetacut"); }

bool    CoilCut       ( const HeliumCVUniverse& univ) { return univ.GetBool("cut_coilcut"); }
bool    IsMinsoMatch  ( const HeliumCVUniverse& univ) { return univ.GetBool("cut_minosMatchTrack"); }
bool    IsUsableMuon  ( const HeliumCVUniverse& univ) { return univ.GetBool("cut_isUsableMuon"); }
int     MuonChange    ( const HeliumCVUniverse& univ) { return univ.GetInt("muonCharge"); }

int     DidVertexConverge ( const HeliumCVUniverse& univ) { return  univ.GetInt("cryo_vtx_fit_converged");}

//////////////////////////////////////////////////////////////
///IS Plausible
/////////////////////////////////////////////////////////////

bool nonmu_is_plausible( const HeliumCVUniverse& univ) { return univ.GetBool("nonmu_is_plausible");}
bool mu_is_plausible ( const HeliumCVUniverse& univ) {return  univ.GetBool("mu_is_plausible");}

bool  NonMuon_Plausible (const HeliumCVUniverse& univ, bool IsMC){
  if(IsMC==true){
  if(nonmu_is_plausible(univ) == false){
    return false;}

    else{return true;}
  }

  else if(IsMC==false){return true;}
  else{std::cout<<"WRONG in Plasible function"<<std::endl; return true;}
}

bool  Muon_Plausible (const HeliumCVUniverse& univ, bool IsMC){
  if(IsMC==true){
  if(mu_is_plausible(univ) == false){
    return false;}

    else{return true;}
  }

  else if(IsMC==false){return true;}
  else{std::cout<<"WRONG in Plasible function"<<std::endl; return true;}
}


  //////////////////////////////////////////////////////////////
  ///IS Curvature good
  /////////////////////////////////////////////////////////////


  bool  IsMuon_CurvatureGreater( const HeliumCVUniverse& univ, double CurvatureInput )
{
  if( abs( univ.GetCurvatureSignificance()) <= abs( CurvatureInput)) {return false;}
  else{return true;}
}

bool  IsGoodCurvatureSignificance (const HeliumCVUniverse& univ){
  if( IsMuon_CurvatureGreater( univ, HeliumCUTConsts::Maximum_SigCurvature ) == true){
    return true;}
    else{return false;}
  }

//////////////////////////////////////////////////////////////
///IS IN fiduical
/////////////////////////////////////////////////////////////

  bool  IsInFiduicalVolume(const HeliumCVUniverse& univ){
    if (false == IsInFiducalVolumeFromtheInnerEdge( univ, HeliumCUTConsts::VextexMiniumDisToCryoTankInnerTank))
    {return false;}
    else{return true;}
  }


  bool  IsInFiduicalVolume(const HeliumCVUniverse& univ, double Cut_MiniumDisToCryoTankInnerTank){
    if (false == IsInFiducalVolumeFromtheInnerEdge( univ, Cut_MiniumDisToCryoTankInnerTank))
    {return false;}
    else{return true;}
  }


bool IsInExtraFiduicalVolume(const HeliumCVUniverse& univ){
  if (false == IsInExtendentedFiducalVolumeFromtheInnerEdge(univ, 0.0, HeliumCUTConsts::CryoTankExtraAddRegionOutside ))
  {return false;}
  else{return true;}
}


bool IsInExtraFiduicalVolume_Non_seperated_Cryo_regions(const HeliumCVUniverse& univ, double Cut_MiniumDisToCryoTankInnerTank){

if(Cut_MiniumDisToCryoTankInnerTank < 0.0){

double Cutinput = abs(Cut_MiniumDisToCryoTankInnerTank);
double ZExtra = Cutinput;  // added a little  length to Zextra but doesnt count for Cut

if (false == IsInExtendentedFiducalVolumeFromtheInnerEdge(univ, Cutinput, Cutinput, ZExtra ))
{return false;}
else{return true;}
}

else if(Cut_MiniumDisToCryoTankInnerTank>= 0.0){

  if (false == IsInFiducalVolumeFromtheInnerEdge( univ, Cut_MiniumDisToCryoTankInnerTank))
  {return false;}
  else{return true;}


}



}

bool IsInExtraFiduicalVolume_Non_seperated_Cryo_regions_TRUTH(const HeliumCVUniverse& univ, double Cut_MiniumDisToCryoTankInnerTank){

if(Cut_MiniumDisToCryoTankInnerTank < 0.0){

double Cutinput = abs(Cut_MiniumDisToCryoTankInnerTank);
double ZExtra = Cutinput;  // added a little  length to Zextra but doesnt count for Cut

if (false == IsInExtendentedFiducalVolumeFromtheInnerEdge_TRUTH(univ, Cutinput, Cutinput, ZExtra ))
{return false;}
else{return true;}
}

else if(Cut_MiniumDisToCryoTankInnerTank >= 0.0){

  if (false == IsInFiducalVolumeFromtheInnerEdgeTRUTH( univ, Cut_MiniumDisToCryoTankInnerTank))
  {return false;}
  else{return true;}


}



}
  //////////////////////////////////////////////////////////////
  ///IS forward Going
  /////////////////////////////////////////////////////////////

  bool  IsTrackForwardGoing(const HeliumCVUniverse& univ)  {

    bool timecut = true;
    int Tracksize = univ.GetInt("tracksize");
    double startingTrackTime = univ.GetVecElem("tracktimes",0);

    for ( int j = 1; j < Tracksize; j++){
      if (fabs(startingTrackTime - univ.GetVecElem("tracktimes",j)) > 10) timecut = false;
    }

    return timecut;


  }

  //////////////////////////////////////////////////////////////
  ///IS Muon angle Good
  /////////////////////////////////////////////////////////////

  bool  IsMuonAngleGood(const HeliumCVUniverse& univ){
    double MuonAngle = univ.GetThetamu()*TMath::RadToDeg();             // Wrong method need to use the virtual function that can be overridden univ.GetmuAngleWRTB_Degs();
    if (MuonAngle > HeliumCUTConsts::Maximum_MuonAngle)
    {return false;}
    else{return true;}
  }

  //////////////////////////////////////////////////////////////
  ///IS Muon charge Good
  /////////////////////////////////////////////////////////////


  bool  IsMuonChargeGood(const HeliumCVUniverse& univ){
    double MuonCharge = MuonChange( univ);
    if (MuonCharge != HeliumCUTConsts:: Neutrino_Muon_Chargetype)
    {return false;}
    else{return true;}
  }

  //////////////////////////////////////////////////////////////
  ///IS Vertexing good
  /////////////////////////////////////////////////////////////


  bool  IsVertexConvergeGood(const HeliumCVUniverse& univ){
    int VertexConverge = DidVertexConverge(univ);
    if (VertexConverge != 1)
    {return false;}
    else{return true;}
  }

  //////////////////////////////////////////////////////////////
  ///IS Six push good
  /////////////////////////////////////////////////////////////

  bool  IsSixPushGood(const HeliumCVUniverse& univ){
    int sixPush = SixPush( univ);
    if (sixPush == 1)
    {return false;}
    else{return true;}
  }

  bool  IsMINOSFiduicalVolumnGood(const HeliumCVUniverse& univ){
    bool coilCut = CoilCut( univ);
    if (coilCut == false)
    {return false;}
    else{return true;}
  }

  //////////////////////////////////////////////////////////////
  ///IS Number of Tracks good
  /////////////////////////////////////////////////////////////
  bool    Only1Track( const HeliumCVUniverse& univ) { return univ.GetBool("one_Trk"); }
  int     NumberTracks  ( const HeliumCVUniverse& univ) { return univ.GetInt("tracksize"); }

  bool  IsNTracksGood (const HeliumCVUniverse& univ){
    if( (Only1Track (univ) == true) || (NumberTracks(univ) == HeliumCUTConsts::GreaterthanNTracks)){
      return false;}
      else{return true;}
    }



    bool  IsVetoGood(const HeliumCVUniverse& univ){
      int veto = IsVeto(univ);
      if (veto != 0)
      {return false;}
      else{return true;}
    }

    bool IssecTrklessthanDeg(const HeliumCVUniverse& univ , double Max_deg)
    {

      int secondTrk = univ.Getindex2ndTrackhighestKE();
      double Angle = univ.GetNonmuTrkAngleWRTbeamMID(secondTrk);

      if (Angle < Max_deg) {
        return true;
      }
      else{return false;}

    }//end of function


  bool IsVertexChiSqrtLessthanMax(const HeliumCVUniverse& univ , double Max_chisqrt)
  {

    double Chisqrt = univ.GetVertexChiSqrFit();

    if (Chisqrt < Max_chisqrt) {
      return true;
    }
    else{return false;}


  }


  bool IsVertexChiSqrtLessthanMax_ByTrackType(const HeliumCVUniverse& univ , double Max_chisqrt_long, double Max_chisqrt_otherlong, double Max_chisqrt_short)
  {

    double Chisqrt = univ.GetVertexChiSqrFit();
    TrackType Track_type = univ.GetTrackType();

    if(kShort==Track_type){
      if (Chisqrt < Max_chisqrt_short) {
        return true;
      }
      else{return false;}
    }

    else if(kLong==Track_type){
      if (Chisqrt < Max_chisqrt_long) {
        return true;
      }
      else{return false;}
    }

    else if(kOtherLong==Track_type){
      if (Chisqrt < Max_chisqrt_otherlong) {
        return true;
      }
      else{return false;}
    }

    else{return false;}

  }// end of function
//////////////////////
bool IsVertexConverge_usingALLTracks(const HeliumCVUniverse& univ ){

  auto trackType = univ.GetTrackType();
  if (kNotdefinedTrack == trackType){return false;}
  else{return true;}

}//end of function
//==============================================================================
// Cut Names
//==============================================================================
std::string  GetCutName(ECuts cut) {
  switch (cut) {
    case kNoCuts:
    return "No Cuts";

    case kGoodEnergy:
    return "Good Muon Energy";

    case kMuonAngle:
    return "Muon Angle < 12 Degs";

    case kMinosMatch:
    return "muon matched MINOS to Minerva";

    case kMinosCharge:
    return "Minos charge Type";

    case kUsableMuon:
    return "Is a usable Muon";

    case kMinosCoil:
    return "MINOS Fiducal Coil cut";

    case kMinosCurvature:
    return "MINOS SigCurature";

    case kVertexConverge:
    return "Vertex converged";

    case kThetaMu:
    return "Muon Angle < 17 Degs";

    case kThetaMuLess:
    return "Muon Angle tighter cut";

    case kNTracks:
    return "Tracks > 1 ";

    case kSix:
    return "SixPush";

    case kVeto:
    return "Veto wall";

    case kNonMu_is_Plausible:
    return "Non-muon is plausible ";

    case kMu_is_Plausible:
    return "Muon is plausible ";

    case kTrackForwardGoing:
    return "Track is going foward in time";

    case kFiducialVolume:
    return "Fiducial Volume";

    case kFiducialVolume_ExtraShell:
    return "EXTENDENTED!!! Fiduical Volmne is begin Appled";

    case kMatchVetoDeadPaddle:
    return"Muon Track Match to dead paddle";

    case ksecTrkwrtblessthanMaxAngle:
    return "Second trk less than Max Angle";

    case kMaxChiSqrt:
    return "Maxium Vertex Chi sqrt";

    case kMaxChiSqrt_byTrackType:
    return "Maxium Vertex Chi sqrt BY Track type";

    case kVertex_ConvergedfromAllTracks:
    return "Vertex Converged using All (Muon and nonMuon) tracks";


    case kAllCuts:
    return "All cuts applied ";


    default:
    std::cout << "ERROR: GetCutName unknown cut!" << std::endl;
    return "";
  };
}

std::string  GetCutNameforLatex(ECuts cut) {
  switch (cut) {
    case kNoCuts:
    return "No Cuts";

    case kGoodEnergy:
    return "2 [GeV] $<$ $E_{\\mu}$ $<$ 50 [GeV]";

    case kMuonAngle:
    return "$\\theta_{\\mu}$ $<$ 12 [Degs]";

    case kMinosMatch:
    return "Muon matched MINOS to Minerva";

    case kMinosCharge:
    return "Muon Charge (-)";

    case kUsableMuon:
    return "Usable Muon Track with $E_{\\mu}$ $>$ 0 ";

    case kMinosCoil:
    return "Minos Fiducal Coil cut 210 [mm] $<$ R $<$ 2500 [mm]";

    case kMinosCurvature:
    return "Curvature Significance $\\frac{(q/p)}{\\sigma(q/p)}$ $<$ -5 ";

    case kVertexConverge:
    return "Vertex Converged";

    case kThetaMu:
    return "$\\theta_{\\mu}$ $<$ 17 [Degs]";

    case kThetaMuLess:
    return "Muon Angle tighter cut";

    case kNTracks:
    return "NTracks $>$ 1 ";

    case kSix:
    return "SixPush(VetoWall Dead time)";

    case kVeto:
    return "No Veto Wall Matches";

    case kNonMu_is_Plausible:
    return "Non-muon is Plausible (Overlay Check) ";

    case kMu_is_Plausible:
    return "Muon is Plausible (Overlay Check) ";

    case kTrackForwardGoing:
    return "Tracks are Going Foward in Time";

    case kFiducialVolume:
    return "Fiducial Volume";

    case kFiducialVolume_ExtraShell:
    return "EXTENDENTED!!! Fiduical Volmne is begin Appled";

    case kMatchVetoDeadPaddle:
    return"Muon Track not Match to off Voltage Veto paddle";

    case ksecTrkwrtblessthanMaxAngle:
    return "$\\theta_{Recoil}$ $<$ 60 [Deg] ";

    case kMaxChiSqrt:
    return "Maxium Vertex Chi sqrt";

    case kMaxChiSqrt_byTrackType:
    return "Maximum Vertex $\\chi^{2}$ by Track type";

    case kVertex_ConvergedfromAllTracks:
    return "Vertex Converged using All tracks";


    case kAllCuts:
    return "All cuts applied ";


    default:
    std::cout << "ERROR: GetCutName unknown cut!" << std::endl;
    return "";
  };
}


std::string  GetCutNameforRootLatex(ECuts cut) {
  switch (cut) {
    case kNoCuts:
    return "No Cuts";

    case kGoodEnergy:
    return "2 [GeV] < E_{#mu} < 50 [GeV]";

    case kMuonAngle:
    return "#theta_{#mu} < 12 [Degs]";

    case kMinosMatch:
    return "Muon matched MINOS to Minerva";

    case kMinosCharge:
    return "Muon Charge (-)";

    case kUsableMuon:
    return "Usable Muon Track with E_{#mu} > 0 ";

    case kMinosCoil:
    return "Minos Fiducal Coil cut 210 [mm] < R < 2500 [mm]";

    case kMinosCurvature:
    return "Curvature Significance #frac{(q/p)}{#sigma(q/p)} < -5 ";

    case kVertexConverge:
    return "Vertex Converged";

    case kThetaMu:
    return "#theta_{#mu} < 17 [Degs]";

    case kThetaMuLess:
    return "Muon Angle tighter cut";

    case kNTracks:
    return "NTracks > 1 ";

    case kSix:
    return "SixPush(VetoWall Dead time)";

    case kVeto:
    return "No Veto Wall Matches";

    case kNonMu_is_Plausible:
    return "Non-muon is Plausible (Overlay Check) ";

    case kMu_is_Plausible:
    return "Muon is Plausible (Overlay Check) ";

    case kTrackForwardGoing:
    return "Tracks are Going Foward in Time";

    case kFiducialVolume:
    return "Fiducial Volume";

    case kFiducialVolume_ExtraShell:
    return "EXTENDENTED!!! Fiduical Volmne is begin Appled";

    case kMatchVetoDeadPaddle:
    return"Muon Track not Match to off Voltage Veto paddle";

    case ksecTrkwrtblessthanMaxAngle:
    return "#theta_{Recoil} < 60 [Deg] ";

    case kMaxChiSqrt:
    return "Maxium Vertex Chi sqrt";

    case kMaxChiSqrt_byTrackType:
    return "Maximum Vertex #chi^{2} by Track type";

    case kVertex_ConvergedfromAllTracks:
    return "Vertex Converged using All tracks";


    case kAllCuts:
    return "All cuts applied ";


    default:
    std::cout << "ERROR: GetCutName unknown cut!" << std::endl;
    return "";
  };
}




std::string  GetCutNameTRUTH(ECutsTRUTH cut) {
  switch (cut) {
    case kTRUTHNoCuts:
    return "No Cuts";

    case kTRUTHMuonEnergy:
    return " 2Gev <  true Muon Energy < 50Gev";

    case kTRUTHMuonAngle:
    return "True Muon Angle < 12 ";

    case kTRUTHneutrino:
    return "Neutrino interaction";

    case kTRUTHCCInteraction:
    return "Charge Current Type";

    case kTRUTHtarget:
    return "True Helium Target";

    case kTRUTHFiduical:
    return "True Vertex in Fiduical";

    case kTRUTHFiduical_ExtraShell:
    return "True Vertex in EXTENDENTED Fiduical Shell";

    case kTRUTH_greaterthanoneFS:
    return "More than one TRUE FS particle";

    case  kTRUTH_secTrk_Angle_threshold:
    return "Maxium 2ndtrk Angle Threshold ";

    case kTRUTH_2ndTrkEnergythreshold:
    return "All 2ndTrk Energy minium thresholds";

    case kTRUTH_2ndTrkPionEnergythreshold:
    return "Pion TRUE Energy Minium threshold";

    case kTRUTH_2ndTrkProtonEnergythreshold:
    return "Proton TRUE Energy Minium threshold";

    case kTRUTH_2ndTrkDimuonEnergythreshold:
    return"Dimuon TRUE Energy Minium threshold";

    case kTRUTH_NoNeutral_FS_2ndTrk_RECOBRANCH:
    return "No Netural FS 2nd Trk and angle Threshold for Reco Branch";

    case kTRUTH_NoNeutral_FS_2ndTrk_noAngleCut_RECOBRANCH:
    return "No Netural FS 2nd Trk for TRUTH Reco Branch";

    case kTRUTH_NoNeutral_FS_2ndTrk_withProtonanPionThresholds_RECOBRANCH:
    return "No Netural FS 2nd Trk,angle Threshold , threshold KE on Proton and Pions, for Reco Branch";

    case kTRUTH_atleastone_non_Neutral_secTrk:
    return "At least one 2nd track Non-Neutral Particle ";

    case kTRUTH_No_Neutral_secTrk_Angle_threshold:
    return "No Neutral Particle and angle Threshold";

    case kTRUTH_No_Neutral_secTrk_Angle_threshold_withProtonanPionThresholds:
    return "No Neutral Particle, angle Threshold, threshold KE on Proton, charged Pions, and diMuon";

    case kTRUTH_No_Neutral_KEthreshold_withProtonanPionThresholds:
    return "No Neutral Particle and threshold KE on Proton, Charged Pions and dimuon";

    case kAllTRUTHCuts:
    return "All True Cuts applied";

    default:
    std::cout << "ERROR: GetCutNameTruth unknown cut!" << std::endl;
    return "";
  };
}
std::string  GetCutNameLatexTRUTH(ECutsTRUTH cut) {
  switch (cut) {
    case kTRUTHNoCuts:
    return "No Cuts";

    case kTRUTHMuonEnergy:
    return " 2 [GeV] $<$ True $E_{\\mu}$ $<$ 50 [Gev]";

    case kTRUTHMuonAngle:
    return "True $\\theta_{\\mu}$ $<$ 12 ";

    case kTRUTHneutrino:
    return "Neutrino interaction";

    case kTRUTHCCInteraction:
    return "Charge Current (CC) Interaction";

    case kTRUTHtarget:
    return "True Helium Target";

    case kTRUTHFiduical:
    return "True Vertex in Fiduical";

    case kTRUTHFiduical_ExtraShell:
    return "True Vertex in EXTENDENTED Fiduical Shell";

    case kTRUTH_greaterthanoneFS:
    return "More than one TRUE FS particle";

    case  kTRUTH_secTrk_Angle_threshold:
    return "Maxium 2ndtrk Angle Threshold ";

    case kTRUTH_2ndTrkEnergythreshold:
    return "All 2ndTrk Energy minium thresholds";

    case kTRUTH_2ndTrkPionEnergythreshold:
    return "Pion TRUE Energy Minium threshold";

    case kTRUTH_2ndTrkProtonEnergythreshold:
    return "Proton TRUE Energy Minium threshold";

    case kTRUTH_2ndTrkDimuonEnergythreshold:
    return"Dimuon TRUE Energy Minium threshold";

    case kTRUTH_NoNeutral_FS_2ndTrk_RECOBRANCH:
    return "No Netural FS 2nd Trk and angle Threshold for Reco Branch";

    case kTRUTH_NoNeutral_FS_2ndTrk_withProtonanPionThresholds_RECOBRANCH:
    return "No Netural FS 2nd Trk,angle Threshold , threshold KE on Proton and Pions, for Reco Branch";

    case kTRUTH_atleastone_non_Neutral_secTrk:
    return "At least one Non Neutral Recoil Particle";

    case kTRUTH_No_Neutral_secTrk_Angle_threshold:
    return "At least one Non Neutral Recoil Particle with $\\theta_{wrtb}$ $<$ 60 [Deg] ";

    case kTRUTH_No_Neutral_secTrk_Angle_threshold_withProtonanPionThresholds:
    return "No Neutral Particle, angle Threshold [60 Deg] , threshold KE on Proton 105[MeV]and Pions 60[MeV]";

    case kTRUTH_No_Neutral_KEthreshold_withProtonanPionThresholds:
    return "No Neutral Particle and threshold KE on Proton 105[MeV], Charged Pions 60[MeV] and dimuon 60[MeV]";

    case kAllTRUTHCuts:
    return "All True Cuts applied";

    default:
    std::cout << "ERROR: GetCutNameTruth unknown cut!" << std::endl;
    return "";
  };
}
//////////////////////////////////////////////
//
/////////////////////////////////////////////
std::string  GetCutNameLatexforRootTRUTH(ECutsTRUTH cut) {
  switch (cut) {
    case kTRUTHNoCuts:
    return "No Cuts";

    case kTRUTHMuonEnergy:
    return " 2 [GeV] < True E_{#mu} < 50 [Gev]";

    case kTRUTHMuonAngle:
    return "True #theta_{#mu} < 12 ";

    case kTRUTHneutrino:
    return "Neutrino interaction";

    case kTRUTHCCInteraction:
    return "Charge Current (CC) Interaction";

    case kTRUTHtarget:
    return "True Helium Target";

    case kTRUTHFiduical:
    return "True Vertex in Fiduical";

    case kTRUTHFiduical_ExtraShell:
    return "True Vertex in EXTENDENTED Fiduical Shell";

    case kTRUTH_greaterthanoneFS:
    return "More than one TRUE FS particle";

    case  kTRUTH_secTrk_Angle_threshold:
    return "Maxium 2ndtrk Angle Threshold ";

    case kTRUTH_2ndTrkEnergythreshold:
    return "All 2ndTrk Energy minium thresholds";

    case kTRUTH_2ndTrkPionEnergythreshold:
    return "Pion TRUE Energy Minium threshold";

    case kTRUTH_2ndTrkProtonEnergythreshold:
    return "Proton TRUE Energy Minium threshold";

    case kTRUTH_2ndTrkDimuonEnergythreshold:
    return"Dimuon TRUE Energy Minium threshold";

    case kTRUTH_NoNeutral_FS_2ndTrk_RECOBRANCH:
    return "No Netural FS 2nd Trk and angle Threshold for Reco Branch";

    case kTRUTH_NoNeutral_FS_2ndTrk_withProtonanPionThresholds_RECOBRANCH:
    return "No Netural FS 2nd Trk,angle Threshold , threshold KE on Proton and Pions, for Reco Branch";

    case kTRUTH_atleastone_non_Neutral_secTrk:
    return "At least one Non Neutral Recoil Particle";

    case kTRUTH_No_Neutral_secTrk_Angle_threshold:
    return "At least one Non Neutral Recoil Particle with #theta_{wrtb} < 60 [Deg] ";

    case kTRUTH_No_Neutral_secTrk_Angle_threshold_withProtonanPionThresholds:
    return "No Neutral Particle, angle Threshold , threshold KE on Proton and Pions";

    case kTRUTH_No_Neutral_KEthreshold_withProtonanPionThresholds:
    return "No Neutral Particle and threshold KE on Proton 105[MeV], Charged Pions 60[MeV] and dimuon 60[MeV]";

    case kAllTRUTHCuts:
    return "All True Cuts applied";

    default:
    std::cout << "ERROR: GetCutNameTruth unknown cut!" << std::endl;
    return "";
  };
}
