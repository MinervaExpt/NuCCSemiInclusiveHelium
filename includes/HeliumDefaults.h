#ifndef HELIUMDEFAULTS_H
#define HELIUMDEFAULTS_H

#include "PlotUtils/MnvH1D.h"
#include "PlotUtils/MnvH2D.h"
#include "PlotUtils/HistWrapper.h"
#include "PlotUtils/Hist2DWrapper.h"
#include "TObjArray.h"
#include "TArrayD.h"
#include "TMath.h"
#include <algorithm>  // erase, remove_if
#include "HeliumCVUniverse.h"
//#include "MasterAnaCVUniverse.h"
#include "PlotUtils/MnvNormalization.h"
#include <sstream>
#include "PlotUtils/HistFolio.h"
#include <iostream>
#include <map>
#include <iomanip>
#include <tuple>
#include <random>


////////////////////////////////////////////////////////////////////////////////
template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 6) {
  std::ostringstream out;
  out.precision(n);
  out << std::fixed << a_value;
  return out.str();
}
////////////////////////////////////////////////////////////////////////////////
struct SliceID {
  int run;
  int subrun;
  int gate;
  int slice;
};
////////////////////////////////////////////////////////////////////////////////
class Vertex_XYZ {
 public:
  double x;
  double y;
  double z;

  Vertex_XYZ(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}

  bool operator==(const Vertex_XYZ& vector) const {
    return (x == vector.x && y == vector.y && z == vector.z);
  }

  Vertex_XYZ& operator=(const Vertex_XYZ& vector) {
    x = vector.x;
    y = vector.y;
    z = vector.z;
    return *this;
  }

  Vertex_XYZ operator+(const Vertex_XYZ& input) const {
    return Vertex_XYZ(x + input.x, y + input.y, z + input.z);
  }

  Vertex_XYZ operator-(const Vertex_XYZ& input) const {
    return Vertex_XYZ(x - input.x, y - input.y, z - input.z);
  }

  double DotProduct(const Vertex_XYZ& vector1, const Vertex_XYZ& vector2) {
    return vector1.x * vector2.x + vector1.y * vector2.y +
           vector1.z * vector2.z;
  }

  Vertex_XYZ CrossProduct(const Vertex_XYZ& vector1,
                          const Vertex_XYZ& vector2) {
    Vertex_XYZ inputVector;
    inputVector.x = vector1.y * vector2.z - vector1.z * vector2.y;
    inputVector.y = vector1.z * vector2.x - vector1.x * vector2.z;
    inputVector.z = vector1.x * vector2.y - vector1.y * vector2.x;
    return inputVector;
  }
};
////////////////////////////////////////////////////////////////////////////////
struct Normal_Fit_Parameters {
  double stddev;
  double mean;

  bool operator==(const Normal_Fit_Parameters& input) const {
    return (stddev == input.stddev && mean == input.mean);
  }
  bool operator<(const Normal_Fit_Parameters& input) const {
    return (stddev < input.stddev) ||
           (stddev == input.stddev && mean < input.mean);
  }
};
////////////////////////////////////////////////////////////////////////////////
struct Index2 {
  int i;
  int j;

  bool operator==(const Index2& ij) const { return (i == ij.i && j == ij.j); }

  bool operator<(const Index2& ij) const {
    return i < ij.i || (i == ij.i && j < ij.j);
  }
};
////////////////////////////////////////////////////////////////////////////////
struct Index3 {
  int i;
  int j;
  int k;

  bool operator==(const Index3& ijk) const {
    return (i == ijk.i && j == ijk.j && k == ijk.k);
  }

  bool operator<(const Index3& ijk) const {
    return (std::tie(i, j, k) < std::tie(ijk.i, ijk.j, ijk.k));
  }
};
////////////////////////////////////////////////////////////////////////////////
struct Index4 {
  int i;
  int j;
  int k;
  int m;

  bool operator==(const Index4& ijkm) const {
    return (i == ijkm.i && j == ijkm.j && k == ijkm.k && m == ijkm.m);
  }

  bool operator<(const Index4& ijkm) const {
    return (std::tie(i, j, k, m) < std::tie(ijkm.i, ijkm.j, ijkm.k, ijkm.m));
  }
};
////////////////////////////////////////////////////////////////////////////////
struct Convolution_X_Y_FitResult {
  Index4 index;
  double meanX;
  double stddevX;
  double meanY;
  double stddevY;
  double Chi_X;
  double Chi_Y;
  double Chi_Z;
  double Chi_R;
};
////////////////////////////////////////////////////////////////////////////////
struct SliceID_vertex_info {
  SliceID RunInfo;
  Vertex_XYZ vertex;
};
////////////////////////////////////////////////////////////////////////////////
struct Trajector {
  SliceID RunInfo;
  std::vector<int> PDG;
  std::vector<double> KE;
  std::vector<double> Angle;

  std::vector<double> InitalTrkx;
  std::vector<double> InitalTrky;
  std::vector<double> InitalTrkz;

  std::vector<double> FinalTrkx;
  std::vector<double> FinalTrky;
  std::vector<double> FinalTrkz;
};
////////////////////////////////////////////////////////////////////////////////
struct Trajector_DATA {
  SliceID RunInfo;

  double muon_Intial_nodex;
  double muon_Intial_nodey;
  double muon_Intial_nodez;

  double muon_Final_nodex;
  double muon_Final_nodey;
  double muon_Final_nodez;

  std::vector<double> ShortTrk_Intialx;
  std::vector<double> ShortTrk_Intialy;
  std::vector<double> ShortTrk_Intialz;

  std::vector<double> ShortTrk_FinalTrkx;
  std::vector<double> ShortTrk_FinalTrky;
  std::vector<double> ShortTrk_FinalTrkz;

  std::vector<double> ShortTrk_KE;
  std::vector<double> ShortTrk_Angle;
  std::vector<double> ShortTrk_Length;
};
////////////////////////////////////////////////////////////////////////////////
struct Trajector_withTrueEnergyFraction {
  SliceID RunInfo;
  std::vector<int> PDG;
  std::vector<double> KE;
  std::vector<double> Angle;
  std::vector<double> true_energy_fraction;

  std::vector<double> InitalTrkx;
  std::vector<double> InitalTrky;
  std::vector<double> InitalTrkz;

  std::vector<double> FinalTrkx;
  std::vector<double> FinalTrky;
  std::vector<double> FinalTrkz;
};
////////////////////////////////////////////////////////////////////////////////
struct TRUE_RECO_Energies_Trajectors {
  SliceID RunInfo;

  std::vector<int> PDG_mcFS;
  std::vector<double> KE_mcFS;
  std::vector<double> Angle_mcFS;

  std::vector<int> PDG_TRUETrajectors;
  std::vector<double> KE_TRUETrajectors;
  std::vector<double> Angle_TRUETrajectors;

  std::vector<int> PDG_TRUE_RECOtrks;
  std::vector<double> KE_TRUE_RECOtrks;
  std::vector<double> Angle_TRUE_RECOtrks;
  std::vector<double> TRUE_EnergyFraction_RECOtrks;
};
////////////////////////////////////////////////////////////////////////////////
class HeliumCVUniverse;
// class MasterAnaCVUniverse;
struct parameterizationEquation_params_bare {
  double Xo;
  double Yo;
  double Zo;
  double a;
  double b;
  double c;
};
////////////////////////////////////////////////////////////////////////////////
struct parameterizationEquation_params {
  int pdg;
  double KE;
  double Xo;
  double Yo;
  double Zo;
  double a;
  double b;
  double c;
};
////////////////////////////////////////////////////////////////////////////////
struct parameterizationEquation_params_DATA {
  double KE;
  double Angle;
  double length;
  double Xo;
  double Yo;
  double Zo;
  double a;
  double b;
  double c;
};
////////////////////////////////////////////////////////////////////////////////
struct parameterizationEquation_paramsWithTrueFraction {
  int pdg;
  double KE;
  double TRUE_Efraction;
  double Xo;
  double Yo;
  double Zo;
  double a;
  double b;
  double c;
};
////////////////////////////////////////////////////////////////////////////////
struct GaussianFitsParms {
  double CutValue;
  double TotalN;
  double Sigma;
  double Sigma_Error;
  double Mean;
  double Mean_Error;
  double Constant;
  double Constant_Error;
  double ChiSqrt;
  int NDF;
};
////////////////////////////////////////////////////////////////////////////////
struct NEvent_FidiucalCut {
  double FidiucalCut;
  double TotalN_Numra;
  double TotalN_TRUE;
  double TotalN_RECO_Helium;
  double TotalN_RECO_nonHelium;
  double TotalN_RECO_total;
};

////////////////////////////////////////////////////////////////////////////////
//==============================================================================
// Typedefs and enum
//==============================================================================
////////////////////////////////////////////////////////////////////////////////


enum ECuts {
  kNoCuts,
  kGoodEnergy,
  kMuonAngle,
  kNTracks,
  kUsableMuon,
  kMu_is_Plausible,
  kNonMu_is_Plausible,
  kVeto,
  kSix,
  kMatchVetoDeadPaddle,  // Veto wall
  kMinosCoil,
  kMinosMatch,
  kMinosCurvature,
  kMinosCharge,  // Good muon
  kThetaMu,      // good Muon
  kVertexConverge,
  kVertex_ConvergedfromAllTracks,
  kMaxChiSqrt_byTrackType,
  kFiducialVolume,
  kFiducialVolume_new,  // Vertex Check  // good recoil system
  kTrackForwardGoing,
  ksecTrkwrtblessthanMaxAngle,
  kThetaMuLess,
  kFiducialVolume_ExtraShell,
  kMaxChiSqrt,
  kMuonAngle_CenterForwardGoingAngle,
  kAllCuts
  /*
   kAnaDev_MINOSMatch
  ,kAnaDev_PassReco
  ,kAnaDev_Atleast2tracks
  ,kAnaDev_GetDeadTimeCut
  ,kAnaDev_TrackerOnly
  ,kAnaDev_InHexagon
  ,kAnaDev_PassThetaCut_heliumlike
  ,kAnaDev_2ndtrackAngle*/
};
////////////////////////////////////////////////////////////////////////////////
enum ECutsTRUTH {
  kTRUTHNoCuts,
  kTRUTHneutrino,
  kTRUTHCCInteraction,
  kTRUTHtarget,
  kTRUTHMuonEnergy,
  kTRUTHMuonAngle,
  kTRUTHFiduical,
  kTRUTHFiduical_new,
  kTRUTH_greaterthanoneFS,
  kTRUTHFiduical_ExtraShell,
  kTRUTH_NoNeutral_FS_2ndTrk_RECOBRANCH,
  kTRUTH_NoNeutral_FS_2ndTrk_noAngleCut_RECOBRANCH,
  kTRUTH_NoNeutral_FS_2ndTrk_withProtonanPionThresholds_RECOBRANCH,
  kTRUTH_NoNeutral_FS_2ndTrk_withProtonanPionThresholds_RECOBRANCH_NoOverLayFraction,
  kTRUTH_2ndTrkPionEnergythreshold, /* this cut doesn't check if the particle is
                                       neutral*/
  kTRUTH_2ndTrkProtonEnergythreshold, /* this cut doesn't check if the particle
                                         is neutral*/
  kTRUTH_2ndTrkDimuonEnergythreshold, /* this cut doesn't check if the particle
                                         is neutral*/
  kTRUTH_2ndTrkEnergythreshold,  /* this cut doesn't check if the particle is
                                    neutral*/
  kTRUTH_secTrk_Angle_threshold, /* this cut doesn't check if the particle is
                                    neutral*/
  kTRUTH_atleastone_non_Neutral_secTrk,
  kTRUTH_No_Neutral_secTrk_Angle_threshold,
  kTRUTH_No_Neutral_KEthreshold_withProtonanPionThresholds,
  kTRUTH_No_Neutral_secTrk_Angle_threshold_withProtonanPionThresholds,
  kAllTRUTHCuts
};
////////////////////////////////////////////////////////////////////////////////
enum MuonVar {
  kNONE,
  kP_T,
  kE,
  kP_Z,
  kAngleWRTB,
  kMidAngleWRTB,
  kAngleWRTBhelium,
  kAnglePhihelium,
  kAnglePhi,
  kDOCA_muon,
  kCharge,
  kcurvatureSig,
  kTRUTH_P_T,
  kTRUTH_E,
  kTRUTH_P_Z,
  kTRUTH_AngleWRTB,
  kTRUTH_DOCA,
  kTRUTH_Charge,
  kminosMuon_Energy,
  kminos_R,
  kminosStart_X,
  kminosStart_Y,
  kminosStart_Z,
  kminosEnd_X,
  kminosEnd_Y,
  kminosEnd_Z,
  kmuonFirstNodeX,
  kmuonFirstNodeY,
  kmuonFirstNodeZ,
  kmuonLastNodeX,
  kmuonLastNodeY,
  kmuonLastNodeZ,
  kMuonMatchtoMinos,
  kMuonMatchtoVeto,
  ktracksize,
  kmuonVertexTiming,
  kpseudorapidity,
  kP_T_2D,
  kP_Z_2D,
  kDOCA_muon_2D,
  kE_2D,
  kcurvatureSig_2D,
  kAngleWRTB_2D

};
////////////////////////////////////////////////////////////////////////////////
enum CryoVertex {
  kX,
  kY,
  kZ,
  kZ_RCut,
  kX_RCut,
  kY_RCut,
  kR_RCut,
  kR,
  kRR,
  kdistance_edge,
  kdistance_upstreamcap,
  kdistance_downstreamcap,
  kdistance_upstreamcap_RCut,
  kdistance_downstreamcap_RCut,
  kdistance_edge_fiducial,
  kX_eff,
  kY_eff,
  kZ_eff,
  kR_eff,
  kRR_eff,
  kX_resolution,
  kY_resolution,
  kZ_resolution,
  kR_resolution,
  kRR_resolution,
  kX_Precent_resolution,
  kY_Precent_resolution,
  kZ_Precent_resolution,
  kR_Precent_resolution,
  kRR_Precent_resolution,
  kTRUTH_X,
  kTRUTH_Y,
  kTRUTH_Z,
  kTRUTH_R,
  kfitConverge,
  kX_upstreamcap,
  kX_barrel,
  kX_downstreamcap,
  kX_downstreamconcavecap,
  kY_upstreamcap,
  kY_barrel,
  kY_downstreamcap,
  kY_downstreamconcavecap,
  kZ_upstreamcap,
  kZ_barrel,
  kZ_downstreamcap,
  kZ_downstreamconcavecap,
  kR_upstreamcap,
  kR_barrel,
  kR_downstreamcap,
  kR_downstreamconcavecap,
  krecoil_DOCA,
  krecoil_tracklength_minerva,
  kDistanceto_UpstreamCap,
  kDistanceto_DownstreamCap,
  kfitConverge_2D,
  kdistance_edge_2D,
  kX_2D,
  kY_2D,
  kZ_2D,
  kR_2D

};
////////////////////////////////////////////////////////////////////////////////
enum SecondTrkVar {
  ksecE,
  ksecE_Proton,
  ksecE_Pion,
  kThetamid,
  kTheta,
  kOpenAngle,
  kPathway,
  kDOCA,
  kFirstsecTrk_Xnode,
  kFirstsecTrk_Ynode,
  kFirstsecTrk_Znode,
  kLastsecTrk_Xnode,
  kLastsecTrk_Ynode,
  kLastsecTrk_Znode,
  ksec_vertexTiming,
  ksec_Pt,
  ksec_Pz,
  ksecDOCA_TRUTH,
  kFullAngle,
  ksec_tracklength_minerva,
  ksecE_2D,
  ksecTheta_2D,
  kDOCA_2D,
  ksec_tracklength_minerva_2D
};
////////////////////////////////////////////////////////////////////////////////
enum ME_helium_Playlists {
  kME1P,
  kME1C,
  kME1D,
  kME1E,
  kME1F,
  kME1A,
  kME1G,
  kME1L,
  kME1M,
  kME1N,
  kME1B,
  kME1O,
  kME1P_Truth,
  kME1C_Truth,
  kME1D_Truth,
  kME1E_Truth,
  kME1F_Truth,
  kME1A_Truth,
  kME1G_Truth,
  kME1L_Truth,
  kME1M_Truth,
  kME1N_Truth,
  kCombinedFull,
  kCombinedEmpty,
};
////////////////////////////////////////////////////////////////////////////////
enum Muon2DVar {
  kPT_PZ,
  kPT_theta,
  kPZ_theta,
  kE_theta,
  kE_PZ,
  kE_PT,
  kVertex_Z_R
};
////////////////////////////////////////////////////////////////////////////////
enum VetoWall_vars {
  kmatchToVeto,
  knumbermatchToVeto,
  kSixPush,
  kextrapnowalls,
  kextrapwall1,
  kextrapwall2,
  kextrapbothwalls,
  kMuonTrkMatchToVETOwalloff,
  kPMTMap,
  kPMTMap_On,
  kPMTMap_Off
};
////////////////////////////////////////////////////////////////////////////////
enum ME_helium_Status {
  kEMPTY,
  kFULL,
  kFull_Empty,
  kMC_FULL,
  kMC_EMPTY,
  kDATA_FULL,
  kDATA_EMPTY,
  kNULL
};
////////////////////////////////////////////////////////////////////////////////
enum Material_type {
  kIron,
  kHelium,
  kCarbon,
  kLead,
  kAluminium,
  kMaterial_OTHER,
  kMaterial_Total
};
////////////////////////////////////////////////////////////////////////////////
enum Interaction_type {
  kElastic,
  kRes_Coh_Pion,
  kDIS,
  k2p2h,
  kInteraction_OTHER,
  kInteraction_Total,
  kInteraction_NONE,
  kdeltaRES,
  kHeavierRES,
  kDISSoft,
  kDISHard,
  kDISSIS
};
////////////////////////////////////////////////////////////////////////////////
enum Topologies_type { kCC0P0Pi, kCC1P0Pi, kCC2P0Pi, kCCOther };
////////////////////////////////////////////////////////////////////////////////
enum CH_Signal_type { kSignal, kBG_NC, kBG_CCwrongsign, kBG_Neutral_secTrk };
////////////////////////////////////////////////////////////////////////////////
enum FluxSlices {
  kSlice1,
  kSlice2,
  kSlice3,
  kSlice4,
  kheliumdaisy0,
  kheliumdaisy1,
  kheliumdaisy2,
  kheliumdaisy3,
  kheliumdaisy4,
  kheliumdaisy5,
  kheliumdaisy6,
  kheliumdaisy7,
  kheliumdaisy8,
  kheliumdaisy9,
  kheliumdaisy10,
  kheliumdaisy11
};
////////////////////////////////////////////////////////////////////////////////
enum Particle_type {
  kElectron,
  kPion_neg,
  kPion_pos,
  kPion_pos_neg,
  kPion_0,
  kPion_combine,
  kKaon,
  kProton,
  kNeutron,
  kMuon,
  kGamma,
  kNeutrino_muon,
  kNeutrino_electron,
  kAnti_Neutrino,
  kFourHelium,
  kLamdba,
  kSigma_plus,
  kParticle_OTHER,
  kParticle_N_A,
  kParticle_Total,
  kParticle_neutral,
  kPion_0_Electron_kGamma
};
////////////////////////////////////////////////////////////////////////////////
enum Veto_status_type { kPMTON, kPMTOFF };
////////////////////////////////////////////////////////////////////////////////
enum Weights {
  kweightFlux,
  kweightMinos,
  kweight2p2ptune,
  kweightRPA,
  kweightGenie,
  kweightLowQ2Pi,
  kweight_HeliumTargetMass,
  kweightZexp,
  kweightMK,
  kweightNone
};
////////////////////////////////////////////////////////////////////////////////
enum StackType {
  kMaterial,
  kInteraction,
  kParticle,
  kCryoTankRegions,
  kTrackType,
  kVertexOptions,
  kboolNTrack,
  kOpenAnglestack,
  kCH_Signal_type
};
////////////////////////////////////////////////////////////////////////////////
enum Migration { Mig_E, Mig_PT, Mig_PZ, Mig_theta };
////////////////////////////////////////////////////////////////////////////////
enum CryoTank_REGIONS {
  kUpstream_head,
  kCenter,
  kDownstream_head,
  kDownstream_ConcaveCap,
  kXCenter,
  kXLeftShelf,
  kXRightShelf,
  kXoutsideEdges,
  kOUTSIDE,
  Zregion1,
  Zregion2,
  Zregion3,
  Zregion4,
  Zregion5,
  Zregion6,
  Zregion7,
  Zregion8,
  Zregion9,
  Zregion10,
  Zregion11,
  Zregion12,
  Zregion13,
  Zregion14

};
////////////////////////////////////////////////////////////////////////////////
enum SecTrkAngle { kAngle15, kAngle30, kAngle45, kAngle60 };
////////////////////////////////////////////////////////////////////////////////
enum OpenAngle {
  kOAngle5,
  kOAngle10,
  kOAngle15,
  kOAngle20,
  kOAngle25,
  kOAngle30,
  kOAngle45,
  kOAngle60
};
////////////////////////////////////////////////////////////////////////////////
enum TrackType { kShort, kLong, kOtherLong, kNotdefinedTrack };
////////////////////////////////////////////////////////////////////////////////
enum VertexOptions { kOpt_1, kOpt_2, kOpt_3, kOpt_4 };
////////////////////////////////////////////////////////////////////////////////
enum boolNTrack { kone_Trk, ktwo_Trk, kmore_Trk, kallfalseTrk };
////////////////////////////////////////////////////////////////////////////////
enum CrossSectionHist {
  Data_signal,
  RECO_signal,
  Data_BG,
  Data_signal_potNorm,
  Data_BG_potNorm,
  Data_signal_BGsub_potNorm,
  RECO_signal_BGsub_potNorm,
  Data_signal_BG_subtracted,
  Data_signal_unfolded,
  Data_signal_unfolded_effcorrected,
  Data_crosssection,
  True_crosssection,
  nom_Eff,
  dom_Eff,
  Eff,
  h_flux,
  Mig,
  mvnreponse_Mig,
  mvnreponse_RECO,
  mvnreponse_TRUE,
  True_crosssection_interaction_Elastic,
  True_crosssection_interaction_DIS,
  True_crosssection_interaction_DISSIS,
  True_crosssection_interaction_DISSoft,
  True_crosssection_interaction_DISHard,
  True_crosssection_interaction_1pion,
  True_crosssection_interaction_DeltaRes,
  True_crosssection_interaction_HeavierRes,
  True_crosssection_interaction_2p2h,
  True_crosssection_interaction_other,
  True_crosssection_interaction_none,
  MC_reco,
  MC_reco_BG,
  MC_reco_subtracted_BG
};
////////////////////////////////////////////////////////////////////////////////
enum UnFoldingHist {
  UnFoldingHistData,
  UnFoldingHistData_TRUTH,
  UnFoldingHistFakeData,
  UnFoldingHistRECO,
  UnFoldingHistTRUTH,
  UnFoldingHistMig
};
////////////////////////////////////////////////////////////////////////////////
enum Fit_Parms_Names {
  kroot_filePath_DataFull,
  kroot_filePath_DataEmpty,
  kroot_filePath_MCFull,
  kroot_filePath_MCEmpty,
  kh_Name_Data_fitTo,
  kh_Name_MC_fitting,
  kh_Name_Data_fitTo_vertexX,
  kh_Name_MC_fitTo_vertexX,
  kh_Name_MC_fitTo_TRUE_vertexX,
  kh_Name_Data_fitTo_vertexY,
  kh_Name_MC_fitTo_vertexY,
  kh_Name_MC_fitTo_TRUE_vertexY,
  kh_Name_Data_fitTo_vertexZ,
  kh_Name_MC_fitTo_vertexZ,
  kh_Name_MC_fitTo_TRUE_vertexZ,
  kh_Name_Data_fitTo_vertexR,
  kh_Name_MC_fitTo_vertexR,
  kh_Name_MC_fitTo_TRUE_vertexR,
  kh_Name_Pt,
  kh_Name_pZ,
  kh_Name_theta,
  kh_Name_Vertex_X,
  kh_Name_vertex_Y,
  kh_Name_vertex_Z,
  kh_Name_vertex_R,
  kh_Name_vertex_disEdge
};
////////////////////////////////////////////////////////////////////////////////
enum MC_ModelTypes {
  kME_GENIE_MnvTune1,
  kME_GENIE_G18_02a_02_11a,
  kME_GENIE_G18_10a_02_11a,
  kME_GENIE_G18_02b_02_11a,
  kME_GENIE_G18_10b_02_11a

};
////////////////////////////////////////////////////////////////////////////////
struct ArachnesecTrk {
  int run;
  int subrun;
  int gate;
  int slice;
  double secTrk_angle_wrtb;
  double secTrk_KE;
  int secTrk_PDG;
};
////////////////////////////////////////////////////////////////////////////////
struct Arachne_alltracks {
  int run;
  int subrun;
  int gate;
  int slice;

  int totalNTRK;
  std::vector<int> Trk_PDG;
  std::vector<double> Trk_angle;
  std::vector<double> Trk_Energy;
};
////////////////////////////////////////////////////////////////////////////////
struct True_Event_info {
  int mc_incoming;
  int mc_current;
  int interaction_type;
  int material_Z;
  int SecTk_index;
  std::vector<int> PDGs;
  std::vector<double> Angles_Degs;
  std::vector<double> Energies_GeV;
};
////////////////////////////////////////////////////////////////////////////////
struct ALL_True_Event_info {
  int mc_incoming;
  int mc_current;
  int interaction_type;
  int material_Z;
  int SecTk_index;
  int mother_index;
  int Fdaughter_index;
  int Ldaughter_index;
  std::vector<int> PDGs;
  std::vector<double> Angles_Degs;
  std::vector<double> Energies_GeV;
  std::vector<int> PDG_ALL_event_IDS;
};
////////////////////////////////////////////////////////////////////////////////
struct SliceID_secTrk {
  int run;
  int subrun;
  int gate;
  int slice;
  double angle;
  double Energy_GeV;
  int pdg;
};
////////////////////////////////////////////////////////////////////////////////
typedef std::map<Particle_type, PlotUtils::MnvH1D*> Particle_MnvH1D_Map;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<Material_type, PlotUtils::MnvH1D*> Material_type_MnvH1D_Map;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<Interaction_type, PlotUtils::MnvH1D*> Interaction_type_MnvH1D_Map;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<Particle_type, PlotUtils::MnvH2D*> Particle_MnvH2D_Map;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<Material_type, PlotUtils::MnvH2D*> Material_type_MnvH2D_Map;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<Interaction_type, PlotUtils::MnvH2D*>
    Interaction_type_MnvH2D_Map;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<ECuts, double> RECO_Cut_Map;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<ECutsTRUTH, double> TRUE_Cut_Map;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<ECuts, double> EventCount_RECO;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<ECuts, std::vector<Vertex_XYZ>> EventCount_CryoVertex_Vector;
typedef std::map<ECutsTRUTH, double> EventCount_Truth;
////////////////////////////////////////////////////////////////////////////////
// typedef std::map<Particle_type, double>    Particle_Map;
// typedef std::map<Material_type, double>    Material_type_Map;
// typedef std::map<Interaction_type, double> Interaction_type_Map;
////////////////////////////////////////////////////////////////////////////////
struct EventCut_Rate_STRUCT {
  char* RECOBRANCH_TGraph_RECO_TRUTH_name;
  char* RECOBRANCH_TGraph_RECO_name;
  char* TRUTHBRANCH_TGraph_name;

  ME_helium_Playlists playlist;
  ME_helium_Status Crytank_status;
  TRUE_Cut_Map TRUTHBRANCH_TRUE_EVENTSECTION_MAP;
  TRUE_Cut_Map RECOBRANCH_TRUE_EVENTSECTION_MAP;
  RECO_Cut_Map RECOBRANCH_TRUE_RECO_EVENTSECTION_MAP;
};
////////////////////////////////////////////////////////////////////////////////
struct CutMap {
  ME_helium_Playlists Playlist;
  ME_helium_Status Crytank_status;

  std::string Data_Tgraph_name;
  std::string RECO_Tgraph_name;
  std::string RECO_Helium_Tgraph_name;
  std::string MCRecoBr_TRUE_RECO_Tgraph_name;
  std::string MCRecoBr_TRUE_Tgraph_name;
  std::string TRUTH_Tgraph_name;

  RECO_Cut_Map DATA_CutsMap;
  RECO_Cut_Map MC_RECO_CutsMap;
  RECO_Cut_Map MC_RECO_Helium_CutsMap;
  RECO_Cut_Map MCRecoBr_TRUTH_RECO_CutsMap;
  TRUE_Cut_Map MCRecoBr_TRUTH_CutsMap;
  TRUE_Cut_Map MC_TRUTH_CutsMap;
};
////////////////////////////////////////////////////////////////////////////////
typedef std::map<ME_helium_Playlists, CutMap> Playlist_CutMap;
////////////////////////////////////////////////////////////////////////////////
struct Particle_Map {
  Particle_type type;
  double Amount;
};
////////////////////////////////////////////////////////////////////////////////
struct Material_Map {
  Material_type type;
  double Amount;
};
////////////////////////////////////////////////////////////////////////////////
struct Interaction_Map {
  Interaction_type type;
  double Amount;
};
////////////////////////////////////////////////////////////////////////////////
struct Track_Map {
  TrackType type;
  double Amount;
};
////////////////////////////////////////////////////////////////////////////////
struct VertexOptions_Map {
  VertexOptions type;
  double Amount;
};
////////////////////////////////////////////////////////////////////////////////
struct boolNTrack_Map {
  boolNTrack type;
  double Amount;
};
////////////////////////////////////////////////////////////////////////////////
struct Hist_phyiscs_map {
  char* Hist_name;
  ME_helium_Playlists playlist;
  ME_helium_Status Crytank_status;
  bool RecoorTruth;
  std::vector<Particle_Map> Particle_vector;
  std::vector<Material_Map> Material_vector;
  std::vector<Interaction_Map> Interaction_vector;
};
////////////////////////////////////////////////////////////////////////////////
struct Hist_phyiscs_map_withtrack {
  char* Hist_name;
  ME_helium_Playlists playlist;
  ME_helium_Status Crytank_status;
  bool RecoorTruth;
  std::vector<Particle_Map> Particle_vector;
  std::vector<Material_Map> Material_vector;
  std::vector<Interaction_Map> Interaction_vector;
  std::vector<Track_Map> Track_vector;
};

////////////////////////////////////////////////////////////////////////////////

struct Hist_map_track {
  char* Hist_name;
  ME_helium_Playlists playlist;
  ME_helium_Status Crytank_status;
  bool RecoorTruth;
  bool isData;
  std::vector<Track_Map> Track_vector;
  std::vector<VertexOptions_Map> VertexOptions_vector;
  std::vector<boolNTrack_Map> boolNTrack_vector;
};
////////////////////////////////////////////////////////////////////////////////
struct CrossSection_histNames {
  MuonVar MuonType;
  std::string Reco_hist_name;
  std::string Reco_hist_BG_name;
  std::string Migration_name;
  std::string Data_hist_name;
  std::string hist_Eff_denominator_name;
  std::string hist_Eff_numerator_name;
  std::string hist_Flux_name;
};
////////////////////////////////////////////////////////////////////////////////
struct CrossSection_2DhistNames {
  Muon2DVar Muon2DType;
  std::string Data_hist_name;
  std::string hist_Flux_name;
  std::string hist_Eff_denominator_name;
  std::string hist_Eff_numerator_name;
  std::string MnvReponse_Name_Mig;
  std::string MnvReponse_Name_reco;
  std::string MnvReponse_Name_true;
  std::string RECO_MC_name;
  std::string RECO_MC_BG_name;
};
////////////////////////////////////////////////////////////////////////////////
struct CrossSection_Hist {
  MuonVar MuonType;
  PlotUtils::MnvH1D* h_flux;
  PlotUtils::MnvH1D* h_Data_Signal;
  PlotUtils::MnvH1D* h_Data_Signal_Unfolded;
  PlotUtils::MnvH1D* h_RECO_Signal;
  PlotUtils::MnvH1D* h_RECO_BG;
  PlotUtils::MnvH1D* h_effNum;
  PlotUtils::MnvH1D* h_effDom;
  PlotUtils::MnvH2D* h_Mig;

  Particle_MnvH1D_Map Particle_HistMap;
  Interaction_type_MnvH1D_Map Interaction_HistMap;
  Material_type_MnvH1D_Map Material_HistMap_RECO;
};
////////////////////////////////////////////////////////////////////////////////
struct CrossSection_Hist_Daisy {
  CrossSection_Hist Daisy0;
  CrossSection_Hist Daisy1;
  CrossSection_Hist Daisy2;
  CrossSection_Hist Daisy3;
  CrossSection_Hist Daisy4;
  CrossSection_Hist Daisy5;
  CrossSection_Hist Daisy6;
  CrossSection_Hist Daisy7;
  CrossSection_Hist Daisy8;
  CrossSection_Hist Daisy9;
  CrossSection_Hist Daisy10;
  CrossSection_Hist Daisy11;
};
////////////////////////////////////////////////////////////////////////////////
struct CrossSection2D_Hist {
  Muon2DVar Muon2DType;
  PlotUtils::MnvH2D* h_flux;
  PlotUtils::MnvH2D* h_Data_Signal;
  PlotUtils::MnvH2D* h_Data_Signal_Unfolded;
  PlotUtils::MnvH2D* h_effNum;
  PlotUtils::MnvH2D* h_effDom;
  PlotUtils::MnvH2D* h_mvnreponse_Mig;
  PlotUtils::MnvH2D* h_mvnreponse_RECO;
  PlotUtils::MnvH2D* h_mvnreponse_TRUE;
  PlotUtils::MnvH2D* h_RECO;
  PlotUtils::MnvH2D* h_RECO_BG;

  Particle_MnvH2D_Map Particle_HistMap;
  Interaction_type_MnvH2D_Map Interaction_HistMap;
};
////////////////////////////////////////////////////////////////////////////////
struct CrossSection2D_Hist_Daisy {
  CrossSection2D_Hist Daisy0;
  CrossSection2D_Hist Daisy1;
  CrossSection2D_Hist Daisy2;
  CrossSection2D_Hist Daisy3;
  CrossSection2D_Hist Daisy4;
  CrossSection2D_Hist Daisy5;
  CrossSection2D_Hist Daisy6;
  CrossSection2D_Hist Daisy7;
  CrossSection2D_Hist Daisy8;
  CrossSection2D_Hist Daisy9;
  CrossSection2D_Hist Daisy10;
  CrossSection2D_Hist Daisy11;
};
////////////////////////////////////////////////////////////////////////////////
struct TransWarp_histNames {
  MuonVar MuonType;
  std::string mc_reco_name;
  std::string mc_truth_name;
  std::string data_reco_name;
  std::string data_truth_name;
  std::string Migration_name;
};
////////////////////////////////////////////////////////////////////////////////
struct TransWarp_Hist {
  MuonVar MuonType;
  PlotUtils::MnvH1D* mc_reco;
  PlotUtils::MnvH1D* mc_truth;
  PlotUtils::MnvH1D* data_reco;
  PlotUtils::MnvH1D* data_truth;
  PlotUtils::MnvH2D* h_Mig;
};
////////////////////////////////////////////////////////////////////////////////
struct TransWarp_2DHist {
  MuonVar MuonType;
  PlotUtils::MnvH2D* mc_reco;
  PlotUtils::MnvH2D* mc_truth;
  PlotUtils::MnvH2D* data_reco;
  PlotUtils::MnvH2D* data_truth;
  PlotUtils::MnvH2D* h_Mig;
};
////////////////////////////////////////////////////////////////////////////////
typedef std::map<std::string, std::vector<HeliumCVUniverse*>> UniverseMap;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<const std::string, int> error_name_Map;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<std::string, std::vector<int>>
    MnvReponse_ErrorUniv_Hist_numbers;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<int, int> error_name_Univ_MvnHistMap;
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
typedef std::map<int, PlotUtils::MnvH2D*> MnvH2D_Map;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<int, PlotUtils::MnvH1D*> MnvH1D_Map;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<int, std::pair<double, double>> VertexOffSet_Map;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<Index3, Vertex_XYZ> XYZ_VertexOffSet_Map;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<Index3, double> IndexMaptoDouble;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<Index3, Normal_Fit_Parameters> NormalParaFit_Map;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<Index3, std::normal_distribution<double>>
    normal_distribution_Map;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<Index4, std::normal_distribution<double>>
    normal_distribution_index4_Map;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<CryoVertex, Normal_Fit_Parameters> Normal_Fit_ParametersXY;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<Index4, Normal_Fit_ParametersXY> NormalParaFit_XYMap;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<Index3, PlotUtils::MnvH1D*> MnvH1D_3indexMap;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<Index4, PlotUtils::MnvH1D*> MnvH1D_4indexMap;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<Index3, PlotUtils::MnvH2D*> MnvH2D_3indexMap;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<Index3, PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>>
    HistFolio_material_type_3indexMap;
    ////////////////////////////////////////////////////////////////////////////////
typedef std::map<CryoTank_REGIONS,
                 PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>>
    HistFolio_material_CryoRegionMap;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<CryoTank_REGIONS, PlotUtils::MnvH1D*> CryoRegion_HistMap;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<Index4, PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>>
    HistFolio_material_type_4indexMap;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<ME_helium_Playlists, EventCount_RECO> EventPlaylist_RecoCount;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<ME_helium_Status, std::vector<ME_helium_Playlists>>
    FullAndEmptyPlaylistMap;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<ME_helium_Status, double> Pot_MapStatusList;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<ME_helium_Status, double> CyroStatusPot_MapList;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<ME_helium_Playlists, double> Pot_MapList;
////////////////////////////////////////////////////////////////////////////////
typedef std::pair<ME_helium_Playlists, TFile*> ME_playlist_TFilePAIR;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<ME_helium_Playlists, TFile*> ME_playlist_TFileMAP;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<double, TFile*> TFileMAP;
////////////////////////////////////////////////////////////////////////////////
typedef std::pair<ME_helium_Playlists, std::string> ME_playlist_RootPathPAIR;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<ME_helium_Playlists, std::string> ME_playlist_RootPathMAP;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<double, std::string> RootPathMAP;
////////////////////////////////////////////////////////////////////////////////
typedef std::pair<ME_helium_Playlists, CrossSection_Hist>
    ME_playlist_CrossSection_PAIR;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<ME_helium_Playlists, CrossSection_Hist>
    ME_playlist_CrossSection_MAP;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<ME_helium_Playlists, CrossSection_Hist_Daisy>
    ME_playlist_CrossSection_MAP_DAISY;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<ME_helium_Playlists, CrossSection2D_Hist_Daisy>
    ME_playlist_2D_CrossSection_MAP_DAISY;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<ME_helium_Playlists, CrossSection2D_Hist>
    ME_playlist_2DCrossSection_MAP;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<ME_helium_Playlists, PlotUtils::MnvH1D*> Playlist_MnvH1D_Map;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<ME_helium_Playlists, PlotUtils::MnvH2D*> Playlist_MnvH2D_Map;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<MC_ModelTypes, TFile*> Model_TFileMAP;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<MC_ModelTypes, PlotUtils::MnvH1D*> Model_MnvH1D_Map;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<MC_ModelTypes, PlotUtils::MnvH2D*> Model_MnvH2D_Map;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<MC_ModelTypes, TH1D*> Model_TH1D_Map;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<MC_ModelTypes, TH1D*> Model_TH1D_Map;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<MC_ModelTypes, std::string> Model_RootPathMAP;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<ME_helium_Playlists, PlotUtils::HistFolio<PlotUtils::MnvH1D>>
    Playlist_HistFolio_MnvH1D_Map;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<CrossSectionHist, PlotUtils::MnvH1D*> CrossSection_MnvH1D_Map;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<CrossSectionHist, PlotUtils::MnvH2D*> CrossSection_MnvH2D_Map;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<CrossSectionHist, std::string> CrossSection_name_Map;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<Migration, PlotUtils::MnvH2D*> Migration_MnvH2D_Map;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<ME_helium_Playlists, TransWarp_Hist>
    ME_playlist_TransWarp_Hist_Map;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<ME_helium_Playlists, TransWarp_2DHist>
    ME_playlist_TransWarp_2DHist_Map;
////////////////////////////////////////////////////////////////////////////////
typedef PlotUtils::Hist2DWrapper<HeliumCVUniverse> CVH2DW;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<ME_helium_Playlists, PlotUtils::MnvH2D*> Playlist_MnvH2D_Map;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<ME_helium_Playlists, PlotUtils::HistFolio<PlotUtils::MnvH2D>>
    Playlist_HistFolio_MnvH2D_Map;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<Fit_Parms_Names, std::string> FitHistName_Map;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<CryoVertex, double> CryoVertexDoubleMap;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<MuonVar, double> MuonVarDoubleMap;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<Normal_Fit_Parameters, Index2> BinMap;
////////////////////////////////////////////////////////////////////////////////
struct OffSet1DMap {
  char* Hist_title;
  ME_helium_Playlists playlist;
  ME_helium_Status Crytank_status;
  int NBinZ;
  int NBinR;
  VertexOffSet_Map OffSetMap;
  MnvH1D_Map Hist_MC_Map;
  PlotUtils::MnvH1D* DataHist;
};
////////////////////////////////////////////////////////////////////////////////
struct OffSet2DMap {
  char* Hist_title;
  ME_helium_Playlists playlist;
  ME_helium_Status Crytank_status;
  int NBinZ;
  int NBinR;
  VertexOffSet_Map OffSetMap;
  MnvH2D_Map Hist_MC_Map;
  PlotUtils::MnvH2D* DataHist;
};
////////////////////////////////////////////////////////////////////////////////
namespace Helium2DPlayListInfo_Pathways {

const std::string ME_LOCAL_PLAYLIST_txtFILE_mc =
    "/minerva/app/users/cnguyen/cmtuser/Minerva_v22r1p1Helium/Ana/"
    "VetoWallStudies/scripts/ChainWrapper_ME2D/playlists/MC_Playlist/";
const std::string ME_LOCAL_PLAYLIST_txtFILE_data =
    "/minerva/app/users/cnguyen/cmtuser/Minerva_v22r1p1Helium/Ana/"
    "VetoWallStudies/scripts/ChainWrapper_ME2D/playlists/Data_Playlist/";
const std::string ME_PNFS_ROOT_Pathway =
    "/pnfs/minerva/persistent/users/cnguyen/";
}
////////////////////////////////////////////////////////////////////////////////
template <typename T, typename U>
bool CompareMap_ME_helium_PlaylistsKeys(std::map<ME_helium_Playlists, T>& l,
                                        std::map<ME_helium_Playlists, U>& r) {
  if (l.size() != r.size()) {
    std::cout << "Maps are different Sizes" << std::endl;
    return false;
  }

  typename std::map<ME_helium_Playlists, T>::const_iterator i;
  typename std::map<ME_helium_Playlists, U>::const_iterator j;

  for (i = l.begin(), j = r.begin(); i != l.end(); ++i, ++j) {
    if (i->first != j->first) {
      return false;
    }
  }
  return true;

}
////////////////////////////////////////////////////////////////////////////////
// Don't mix up true/reco hadron containers
// typedef int TruePionIdx;
// typedef int RecoPionIdx;
typedef PlotUtils::MnvH1D MH1D;
////////////////////////////////////////////////////////////////////////////////
typedef PlotUtils::HistWrapper<HeliumCVUniverse> CVHW;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<std::string, std::vector<HeliumCVUniverse*>> UniverseMap;
////////////////////////////////////////////////////////////////////////////////
class HeliumPlayListInfo {
  std::string m_playlist_type;
  double m_normweightLowP;
  double m_normweightHighP;
  double m_normweightLowPErr;
  double m_normweightHighPErr;

 public:
  HeliumPlayListInfo(std::string playlist) {
    // SetplaylistName( playlist);
    // std::string playlist =  GetPlaylist(playlist_type);

    m_playlist_type = playlist;

    std::cout << "initializer Playlist info for PlayList = " << m_playlist_type
              << std::endl;

    MnvNormalizer* MnvNorm = new MnvNormalizer("Inextinguishable", playlist);

    SetLowP(MnvNorm->GetCorrection(
        1000));  // Get the mnv norm weight for low P muons
    SethighP(MnvNorm->GetCorrection(
        10000));  // Get the mnv norm weight for high P muons
    SetLowPErr(MnvNorm->GetCorrectionErr(
        1000));  // Get the mnv norm weight error for low P muons
    SethighPErr(MnvNorm->GetCorrectionErr(
        10000));  // Get the mvn norm weight error for high P muons
  }

  void SetplaylistName(std::string playlist) { m_playlist_type = playlist; }
  void SetLowP(double lowP) { m_normweightLowP = lowP; }
  void SethighP(double highP) { m_normweightHighP = highP; }
  void SetLowPErr(double lowP) { m_normweightLowPErr = lowP; }
  void SethighPErr(double highP) { m_normweightHighPErr = highP; }
  double GetLowP_Rang() { return m_normweightLowP; }
  double GetHighP_Rang() { return m_normweightHighP; }
  std::string GetPlaylistname() { return m_playlist_type; }
};
////////////////////////////////////////////////////////////////////////////////
//==============================================================================
// Color schemes
//==============================================================================
namespace CCNuPionIncPlotting {
// const int N_COLORS=10;
// const int colors[N_COLORS] = {kRed+1, kOrange+8, kGray+1, kOrange-7,
// kGreen+2, kYellow+2, kCyan-3, kBlue-7, kMagenta-6, kMagenta+2};

// const int colors[N_COLORS] = {kRed+3, kOrange+9, kGray+2, kOrange+3,
// kGreen+3, kYellow+3, kCyan-2, kBlue-7, kMagenta-6, kMagenta+2};
// const int fill_colors[N_COLORS] = {kRed+1, kOrange+6, kGray+1, kOrange-5,
// kGreen-2, kYellow+2, kCyan-8, kBlue-9, kMagenta-9, kMagenta-2};

const int N_COLORS = 8;
const int colors[N_COLORS] = {kRed + 3,     kOrange + 9, kGray + 2,
                              kBlue,        kCyan - 2,   kGreen + 3,
                              kMagenta - 6, kMagenta + 2};
const int fill_colors[N_COLORS] = {kRed + 1,     kOrange + 6, kGray + 1,
                                   kBlue - 6,    kCyan - 8,   kGreen - 2,
                                   kMagenta - 9, kMagenta - 2};

const int nColors2 = 12;
const int colors2[nColors2] = {
    kMagenta + 1, kOrange + 2, kTeal - 7,   kRed - 6,   kSpring - 1, kBlue,
    kAzure + 7,   kCyan + 2,   kViolet - 4, kGreen + 3, kYellow + 2, kGray + 2,
};
const int fill_colors2[nColors2] = {
    kMagenta - 1, kOrange, kTeal - 9,   kRed - 8,   kSpring - 3, kBlue - 2,
    kAzure + 5,   kCyan,   kViolet - 6, kGreen + 1, kYellow,     kGray,
};

const int nColors3 = 7;
const int colors3[nColors3] = {kGreen + 3, kYellow + 2, kOrange + 6, kBlue,
                               kCyan + 2,  kRed + 3,    kAzure + 7};
const int fill_colors3[nColors3] = {
    kGreen + 1, kYellow, kOrange + 5, kAzure - 2, kCyan, kRed + 1, kAzure + 5};

const int nColors4 = 6;
const int colors4[nColors4] = {kRed + 3,    kBlue - 6,  kMagenta - 6,
                               kOrange + 6, kGreen - 2, kAzure + 8};
const int fill_colors4[nColors4] = {kRed + 1,    kBlue - 2,  kMagenta - 3,
                                    kOrange + 5, kGreen - 6, kAzure + 7};

const int nColors5 = 7;
const int colors5[nColors5] = {kGreen + 3, kGray + 2, kBlue,     kYellow + 2,
                               kCyan + 2,  kRed + 3,  kAzure + 7};
const int fill_colors5[nColors5] = {kGreen + 1, kGray,    kBlue - 2, kYellow,
                                    kCyan,      kRed + 1, kAzure + 5};

const int coherent_fill_color = kRed - 7;
const int coherent_color = kRed - 3;
}
//==============================================================================
// Constants from CCPion const
//==============================================================================
namespace HeliumConsts {

const double CHARGED_PION_MASS = 139.569;
const double CHARGED_KAON_MASS = 493.677;
const double MUON_MASS = 105.659;
const double PROTON_MASS = 938.3;

const double CHARGED_PION_MASS_GEV = .139569;  // GeV
const double CHARGED_KAON_MASS_GEV = .493677;  // GeV
const double MUON_MASS_GEV = .105659;          // GeV
const double PROTON_MASS_GEV = .9383;          // GeV
const int HeliumZ = 2;
const int AluminumZ = 13;
const double FirstPlaneZPostion = 4337.25;  // mm
}
////////////////////////////////////////////////////////////////////////////////
namespace HeliumPlayListInfo_Pathways {

const std::string ME_LOCAL_PLAYLIST_txtFILE_mc =
    "/minerva/app/users/cnguyen/cmtuser/Minerva_v22r1p1Helium_GIT/"
    "NuCCSemiInclusiveHelium/playlists/MC_Playlist/";
const std::string ME_LOCAL_PLAYLIST_txtFILE_data =
    "/minerva/app/users/cnguyen/cmtuser/Minerva_v22r1p1Helium_GIT/"
    "NuCCSemiInclusiveHelium/playlists/Data_Playlist/";

const std::string MasterAnaDev_ME_LOCAL_PLAYLIST_txtFILE_mc =
    "/minerva/app/users/cnguyen/cmtuser/Minerva_v22r1p1Helium_GIT/"
    "NuCCSemiInclusiveHelium/playlists/MC_Playlist_MasterAnaDev/";
const std::string MasterAnaDev_ME_LOCAL_PLAYLIST_txtFILE_data =
    "/minerva/app/users/cnguyen/cmtuser/Minerva_v22r1p1Helium_GIT/"
    "NuCCSemiInclusiveHelium/playlists/Data_Playlist_MasterAnaDev/";

const std::string ME_PNFS_ROOT_Pathway =
    "/pnfs/minerva/persistent/users/cnguyen/";
const std::string ME_PNFS_ROOT_Pathway_MasterAnaDevP2 =
    "/pnfs/minerva/persistent/DataPreservation/p2/";

const std::string ME_eventSelection_hists_Data =
    "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/";
const std::string ME_eventSelection_hists_MC =
    "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/";

const std::string MasterAnaDev_ME_eventSelection_hists_Data =
    "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles_MasterAnaDev/";
const std::string MasterAnaDev_ME_eventSelection_hists_MC =
    "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev/";

static const std::string EventSelected_me1A_Data =
    ME_eventSelection_hists_Data + "Histograms_minervame1A_Data.root";
static const std::string EventSelected_me1C_Data =
    ME_eventSelection_hists_Data + "Histograms_minervame1C_Data.root";
static const std::string EventSelected_me1D_Data =
    ME_eventSelection_hists_Data + "Histograms_minervame1D_Data.root";
static const std::string EventSelected_me1E_Data =
    ME_eventSelection_hists_Data + "Histograms_minervame1E_Data.root";
static const std::string EventSelected_me1F_Data =
    ME_eventSelection_hists_Data + "Histograms_minervame1F_Data.root";
static const std::string EventSelected_me1G_Data =
    ME_eventSelection_hists_Data + "Histograms_minervame1G_Data.root";
static const std::string EventSelected_me1L_Data =
    ME_eventSelection_hists_Data + "Histograms_minervame1L_Data.root";
static const std::string EventSelected_me1M_Data =
    ME_eventSelection_hists_Data + "Histograms_minervame1M_Data.root";
static const std::string EventSelected_me1N_Data =
    ME_eventSelection_hists_Data + "Histograms_minervame1N_Data.root";
static const std::string EventSelected_me1P_Data =
    ME_eventSelection_hists_Data + "Histograms_minervame1P_Data.root";

static const std::string EventSelected_me1A_MC_All_SysErrorOn =
    ME_eventSelection_hists_MC +
    "Histograms_minervame1A_MC_All_SysErrorsOn.root";
static const std::string EventSelected_me1C_MC_All_SysErrorOn =
    ME_eventSelection_hists_MC +
    "Histograms_minervame1C_MC_All_SysErrorsOn.root";
static const std::string EventSelected_me1D_MC_All_SysErrorOn =
    ME_eventSelection_hists_MC +
    "Histograms_minervame1D_MC_All_SysErrorsOn.root";
static const std::string EventSelected_me1E_MC_All_SysErrorOn =
    ME_eventSelection_hists_MC +
    "Histograms_minervame1E_MC_All_SysErrorsOn.root";
static const std::string EventSelected_me1F_MC_All_SysErrorOn =
    ME_eventSelection_hists_MC +
    "Histograms_minervame1F_MC_All_SysErrorsOn.root";
static const std::string EventSelected_me1G_MC_All_SysErrorOn =
    ME_eventSelection_hists_MC +
    "Histograms_minervame1G_MC_All_SysErrorsOn.root";
static const std::string EventSelected_me1L_MC_All_SysErrorOn =
    ME_eventSelection_hists_MC +
    "Histograms_minervame1L_MC_All_SysErrorsOn.root";
static const std::string EventSelected_me1M_MC_All_SysErrorOn =
    ME_eventSelection_hists_MC +
    "Histograms_minervame1M_MC_All_SysErrorsOn.root";
static const std::string EventSelected_me1N_MC_All_SysErrorOn =
    ME_eventSelection_hists_MC +
    "Histograms_minervame1N_MC_All_SysErrorsOn.root";
static const std::string EventSelected_me1P_MC_All_SysErrorOn =
    ME_eventSelection_hists_MC +
    "Histograms_minervame1P_MC_All_SysErrorsOn.root";

static const std::string EventSelected_me1A_MC_OffSet =
    ME_eventSelection_hists_MC +
    "Histograms_minervame1A_MC_StatsONLYErrors_OFFSET.root";
static const std::string EventSelected_me1C_MC_OffSet =
    ME_eventSelection_hists_MC +
    "Histograms_minervame1C_MC_StatsONLYErrors_OFFSET.root";
static const std::string EventSelected_me1D_MC_OffSet =
    ME_eventSelection_hists_MC +
    "Histograms_minervame1D_MC_StatsONLYErrors_OFFSET.root";
static const std::string EventSelected_me1E_MC_OffSet =
    ME_eventSelection_hists_MC +
    "Histograms_minervame1E_MC_StatsONLYErrors_OFFSET.root";
static const std::string EventSelected_me1F_MC_OffSet =
    ME_eventSelection_hists_MC +
    "Histograms_minervame1F_MC_StatsONLYErrors_OFFSET.root";
static const std::string EventSelected_me1G_MC_OffSet =
    ME_eventSelection_hists_MC +
    "Histograms_minervame1G_MC_StatsONLYErrors_OFFSET.root";
static const std::string EventSelected_me1L_MC_OffSet =
    ME_eventSelection_hists_MC +
    "Histograms_minervame1L_MC_StatsONLYErrors_OFFSET.root";
static const std::string EventSelected_me1M_MC_OffSet =
    ME_eventSelection_hists_MC +
    "Histograms_minervame1M_MC_StatsONLYErrors_OFFSET.root";
static const std::string EventSelected_me1N_MC_OffSet =
    ME_eventSelection_hists_MC +
    "Histograms_minervame1N_MC_StatsONLYErrors_OFFSET.root";
static const std::string EventSelected_me1P_MC_OffSet =
    ME_eventSelection_hists_MC +
    "Histograms_minervame1P_MC_StatsONLYErrors_OFFSET.root";
};
////////////////////////////////////////////////////////////////////////////////
class LatexFormat {
  std::string beginFrame_string = "\\begin{frame}";
  std::string endFrame_string = "\\end{frame}";
  std::string beginTabular = "\\begin{tabular}{";
  std::string EndTabular = "\\end{tabular}";
  std::string Centering = "\\centering";
  std::string horizontalSpace_start = "\\hspace{";
  std::string VerticalSpace_start = "\\vspace{";
  double m_scale;
  std::string m_pdf_Name;
  std::string m_PlotsPerPage = "ccc";

 public:
  LatexFormat(double scale) { m_scale = scale; }

  void SetPlotsPerPage(std::string PlotsPerPage) {
    m_PlotsPerPage = PlotsPerPage;
  }
  std::string GetNPlotsPreSide() { return m_PlotsPerPage; }
  double GetScale() { return m_scale; }
  std::string GetBeginFrame() { return beginFrame_string; }
  std::string GetEndFrame() { return endFrame_string; }
  std::string GetSubSection(std::string name) {
    std::string sub = "\\subsection{ " + name + " }";
    return sub;
  }

  std::string GetBeginFrame(std::string Title) {
    std::string BEGIN_start = this->GetBeginFrame();
    std::string BEGIN = BEGIN_start + "{ " + Title + " }";
    return BEGIN;
  }

  std::string GetBeginTabular() {
    std::string BEGIN_start = beginTabular + this->GetNPlotsPreSide() + "}";
    return BEGIN_start;
  }

  std::string GetBeginTabular(std::string input) {
    std::string BEGIN_start = beginTabular + input + "}";
    return BEGIN_start;
  }

  std::string Get_hSpace(std::string input) {
    std::string hspace = horizontalSpace_start + input + "}";
    return hspace;
  }

  std::string Get_vSpace(std::string input) {
    std::string hspace = VerticalSpace_start + input + "}";
    return hspace;
  }

  std::string GetEndTabular() { return EndTabular; }

  std::string GetCentering() { return Centering; }

  std::string GetInclude_figure(int page, std::string pdf) {
    double scale = GetScale();
    std::string Figure_string =
        "\\includegraphics[scale = " + to_string_with_precision(scale, 2) +
        " , page = " + to_string_with_precision(page, 2) + "]{" + pdf + ".pdf}";
    return Figure_string;
  }

  std::string GetInclude_figure(int page, std::string pdf, double inputscale) {
    double scale = inputscale;
    std::string Figure_string =
        "\\includegraphics[scale = " + to_string_with_precision(scale, 2) +
        " , page = " + to_string_with_precision(page, 2) + "]{" + pdf + ".pdf}";
    return Figure_string;
  }

  std::string GetInclude_figure(std::string pdf) {
    double scale = GetScale();
    std::string Figure_string = "\\includegraphics[scale = " +
                                to_string_with_precision(scale, 2) + " ]{" +
                                pdf + ".pdf}";
    return Figure_string;
  }

  std::string Get_URLlink(std::string url, std::string link_name) {
    std::string string_to_return = "\\href{" + url + "}{" + link_name + "}";
    return string_to_return;
  }
  std::string BeingItemize() {
    std::string string_to_return = "\\begin{itemize}";
    return string_to_return;
  }
  std::string GetItem() {
    std::string string_to_return = "\\item ";
    return string_to_return;
  }

  std::string EndItemize() {
    std::string string_to_return = "\\end{itemize}";
    return string_to_return;
  }

  std::string BinningLatexString(std::vector<double> Bins, std::string HistName,
                                 std::string Units) {
    /* Example of what i Want
    \resizebox{\textwidth}{!}{
    \begin{tabular}{||c|ccccccccccc|| }
    \hline
     Muon Energy Bins: & underflow && bin1 &  &bin2 &  & bin3&  & bin4 & &
    overflow \\
      \hline
    Binning limits [Units] &  &0.0 & & .2 & & 3.& & 4.& & 5.  & \\
    \hline
    \end{tabular}}
    */

    int BinSize = Bins.size();

    std::string l_length(BinSize * 2 + 2, 'c');

    std::ostringstream output_string;
    output_string << std::fixed;
    output_string.precision(2);
    output_string << "\\resizebox{\\textwidth}{!}{"
                  << "\n";
    output_string << "\\begin{tabular}{||c|" << l_length << "c||} \n";
    output_string << "\\hline \n";
    output_string << HistName << "Bins: & underflow  ";
    for (int cat = 0; cat < BinSize - 1; cat++) {
      output_string << "& & bin  " << cat + 1 << " ";
    }
    output_string << "& & overflow \\\\ \n";
    output_string << "\\hline \n";
    output_string << "Binning limits [" << Units << "]";
    for (auto cat : Bins) {
      output_string << "& &  " << cat << " ";
    }
    output_string << "& & & \\\\ \n";
    output_string << "\\hline \n";
    output_string << "\\end{tabular}} \n";

    return output_string.str();
  }

  std::string ChiSqrt_table_LatexString(std::vector<std::string> VectorName,
                                        std::vector<double> Chisqt_Before,
                                        std::vector<double> Chisqt_After,
                                        std::vector<double> NDF,
                                        std::string TitleInForm) {
    std::cout << "inside::ChiSqrt_table_LatexString" << std::endl;

    std::ostringstream output_string;
    output_string << std::fixed;
    output_string.precision(2);
    output_string << "\\resizebox{\\textwidth}{!}{"
                  << "\n";
    output_string << "\\begin{tabular}{||c|c|c|c|c|c|c|c||} \n";
    output_string << "\\hline \n";
    output_string << "Name  & ndf & \\chi^{2} Before  &  \\chi^{2} / ndf "
                     "Before & \\chi^{2} After & \\chi^{2} / ndf After  & "
                     "ratio (a/b) & \\% change \\\\ \\hline \n";
    output_string << "\\hline \n";
    for (int i = 0; i < VectorName.size(); i++) {
      double beforechi = Chisqt_Before.at(i);
      double afterchi = Chisqt_After.at(i);
      double ndf = NDF.at(i);
      double diff = ((beforechi - afterchi) / beforechi) * 100;

      output_string << VectorName.at(i) << " & " << ndf << " & " << beforechi
                    << " & " << beforechi / ndf << " & " << afterchi << " & "
                    << afterchi / ndf << " & " << afterchi / beforechi << "&"
                    << diff << "  \\\\ \\hline \n";
    }
    output_string << "\\hline \n";
    output_string << "\\end{tabular}} \n";

    return output_string.str();
  }

  std::string ChiSqrt_table_LatexString_shifted_weighted(
      std::vector<std::string> VectorName, std::vector<double> Chisqt_Before,
      std::vector<double> Chisqt_shifted,
      std::vector<double> Chisqt_shifted_weighted, std::vector<double> NDF) {
    std::cout << "inside::ChiSqrt_table_LatexString" << std::endl;

    std::ostringstream output_string;
    output_string << std::fixed;
    output_string.precision(2);
    output_string << "\\resizebox{\\textwidth}{!}{"
                  << "\n";
    output_string << "\\begin{tabular}{||c|c|c|c|c|c|c||} \n";
    output_string << "\\hline \n";
    output_string << "Name  & ndf & \\chi^{2} / ndf Before   &  Shifted &  "
                     "weighted & \\Delta shifted & \\Delta weighted & \\\\ "
                     "\\hline \n";
    output_string << "\\hline \n";
    for (int i = 0; i < VectorName.size(); i++) {
      double beforechi = Chisqt_Before.at(i);
      double afterchi_shifted = Chisqt_shifted.at(i);
      double afterchi_shifted_weighted = Chisqt_shifted_weighted.at(i);
      double ndf = NDF.at(i);
      double diff1 = (beforechi - afterchi_shifted);
      double diff2 = (beforechi - afterchi_shifted_weighted);

      output_string << VectorName.at(i) << " & " << ndf << " & "
                    << beforechi / ndf << " & " << afterchi_shifted / ndf
                    << " & " << afterchi_shifted_weighted / ndf << " & "
                    << diff1 / ndf << " & " << diff2 / ndf
                    << "  \\\\ \\hline \n";
    }
    output_string << "\\hline \n";
    output_string << "\\end{tabular}} \n";

    return output_string.str();
  }

};  // end of class
////////////////////////////////////////////////////////////////////////////////
#endif

// common_stuff_h
