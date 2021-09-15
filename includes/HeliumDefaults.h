#ifndef HELIUMDEFAULTS_H
#define HELIUMDEFAULTS_H

#include "PlotUtils/MnvH1D.h"
#include "PlotUtils/HistWrapper.h"
#include "PlotUtils/Hist2DWrapper.h"
#include "TObjArray.h"
#include "TArrayD.h"
#include "TMath.h"
#include <algorithm> // erase, remove_if
#include "HeliumCVUniverse.h"
#include "PlotUtils/MnvNormalization.h"
#include <sstream>
#include "PlotUtils/HistFolio.h"
#include <iostream>
#include <map>

template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 6)
{
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return out.str();
}

//==============================================================================
// Typedefs and enum
//==============================================================================
struct SliceID{

int run;
int subrun;
int gate;
int slice;

};

struct Vertex_XYZ
{
   double x;
   double y;
   double z;
};


struct SliceID_vertex_info{
SliceID RunInfo;
Vertex_XYZ vertex;
};

struct Trajector{
  SliceID RunInfo;
  std::vector <int> PDG;
  std::vector <double> KE;
  std::vector <double> Angle;

  std::vector <double> InitalTrkx;
  std::vector <double> InitalTrky;
  std::vector <double> InitalTrkz;

  std::vector <double> FinalTrkx;
  std::vector <double> FinalTrky;
  std::vector <double> FinalTrkz;

};

struct Trajector_DATA{
  SliceID RunInfo;

  double muon_Intial_nodex;
  double muon_Intial_nodey;
  double muon_Intial_nodez;

  double muon_Final_nodex;
  double muon_Final_nodey;
  double muon_Final_nodez;

  std::vector <double> ShortTrk_Intialx;
  std::vector <double> ShortTrk_Intialy;
  std::vector <double> ShortTrk_Intialz;

  std::vector <double> ShortTrk_FinalTrkx;
  std::vector <double> ShortTrk_FinalTrky;
  std::vector <double> ShortTrk_FinalTrkz;

  std::vector <double> ShortTrk_KE;
  std::vector <double> ShortTrk_Angle;
  std::vector <double> ShortTrk_Length;


};



struct Trajector_withTrueEnergyFraction{
  SliceID RunInfo;
  std::vector <int> PDG;
  std::vector <double> KE;
  std::vector <double> Angle;
  std::vector <double> true_energy_fraction;

  std::vector <double> InitalTrkx;
  std::vector <double> InitalTrky;
  std::vector <double> InitalTrkz;

  std::vector <double> FinalTrkx;
  std::vector <double> FinalTrky;
  std::vector <double> FinalTrkz;

};


struct TRUE_RECO_Energies_Trajectors{
  SliceID RunInfo;

  std::vector <int> PDG_mcFS;
  std::vector <double> KE_mcFS;
  std::vector <double> Angle_mcFS;

  std::vector <int> PDG_TRUETrajectors;
  std::vector <double> KE_TRUETrajectors;
  std::vector <double> Angle_TRUETrajectors;

  std::vector <int> PDG_TRUE_RECOtrks;
  std::vector <double> KE_TRUE_RECOtrks;
  std::vector <double> Angle_TRUE_RECOtrks;
  std::vector <double> TRUE_EnergyFraction_RECOtrks;
};



class HeliumCVUniverse;

struct  parameterizationEquation_params_bare
{
  double Xo;
  double Yo;
  double Zo;
  double a;
  double b;
  double c;

};


struct  parameterizationEquation_params
{
  int pdg;
  double KE;
  double Xo;
  double Yo;
  double Zo;
  double a;
  double b;
  double c;

};




struct  parameterizationEquation_params_DATA
{
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

struct  parameterizationEquation_paramsWithTrueFraction
{
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



enum ECuts {
  kNoCuts,  kGoodEnergy, kUsableMuon, kMinosCoil, kMinosMatch, kMinosCurvature,  kMinosCharge, // Good muon
  kThetaMu,  kMuonAngle, kMu_is_Plausible,  // good Muon
  kNTracks,  kVertexConverge, kVertex_ConvergedfromAllTracks, kMaxChiSqrt_byTrackType, kFiducialVolume, // Vertex Check  // good recoil system
  kVeto, kSix, kMatchVetoDeadPaddle, // Veto wall
  kTrackForwardGoing, ksecTrkwrtblessthanMaxAngle,
  kThetaMuLess,  kNonMu_is_Plausible, kFiducialVolume_ExtraShell,
  kMaxChiSqrt,   kAllCuts};



enum ECutsTRUTH {
  kTRUTHNoCuts, kTRUTHneutrino, kTRUTHCCInteraction, kTRUTHtarget,  kTRUTHMuonEnergy,  kTRUTHMuonAngle, kTRUTHFiduical,
  kTRUTH_greaterthanoneFS, kTRUTHFiduical_ExtraShell ,
  kTRUTH_NoNeutral_FS_2ndTrk_RECOBRANCH, kTRUTH_NoNeutral_FS_2ndTrk_noAngleCut_RECOBRANCH, kTRUTH_NoNeutral_FS_2ndTrk_withProtonanPionThresholds_RECOBRANCH,
  kTRUTH_2ndTrkPionEnergythreshold,kTRUTH_2ndTrkProtonEnergythreshold,kTRUTH_2ndTrkDimuonEnergythreshold,
  kTRUTH_2ndTrkEnergythreshold, kTRUTH_secTrk_Angle_threshold, kTRUTH_No_Neutral_secTrk_Angle_threshold, kTRUTH_atleastone_non_Neutral_secTrk,
  kTRUTH_No_Neutral_secTrk_Angle_threshold_withProtonanPionThresholds, kAllTRUTHCuts
};



enum MuonVar{kNONE, kP_T,  kE,  kP_Z,  kAngleWRTB, kMidAngleWRTB, kAngleWRTBhelium,
    kAnglePhihelium, kAnglePhi,kDOCA_muon, kCharge, kcurvatureSig,
    kTRUTH_P_T,  kTRUTH_E,  kTRUTH_P_Z,  kTRUTH_AngleWRTB, kTRUTH_DOCA ,kTRUTH_Charge,
    kminosMuon_Energy,kminos_R, kminosStart_X, kminosStart_Y,
    kminosStart_Z, kminosEnd_X, kminosEnd_Y, kminosEnd_Z,
    kmuonFirstNodeX,kmuonFirstNodeY,kmuonFirstNodeZ,
    kmuonLastNodeX,kmuonLastNodeY,kmuonLastNodeZ,
    kMuonMatchtoMinos,kMuonMatchtoVeto, ktracksize,
    kmuonVertexTiming, kpseudorapidity

};

enum CryoVertex{kX,  kY,  kZ, kR, kRR, kX_eff,  kY_eff,  kZ_eff, kR_eff, kRR_eff,
   kX_resolution,  kY_resolution,  kZ_resolution, kR_resolution, kRR_resolution,
   kX_Precent_resolution,  kY_Precent_resolution,  kZ_Precent_resolution, kR_Precent_resolution, kRR_Precent_resolution,
    kTRUTH_X,  kTRUTH_Y,  kTRUTH_Z, kTRUTH_R, kfitConverge };



enum SecondTrkVar{ksecE, ksecE_Proton, ksecE_Pion,  kThetamid,  kTheta, kOpenAngle, kPathway, kDOCA,
   kFirstsecTrk_Xnode, kFirstsecTrk_Ynode, kFirstsecTrk_Znode, kLastsecTrk_Xnode, kLastsecTrk_Ynode,
   kLastsecTrk_Znode, ksec_vertexTiming, ksec_Pt, ksec_Pz, ksecDOCA_TRUTH, kFullAngle, ksec_tracklength_minerva};


enum ME_helium_Playlists {kME1P,kME1C,kME1D,kME1E,kME1F,kME1A,kME1G,kME1L,kME1M,kME1N,
                           kME1P_Truth,kME1C_Truth,kME1D_Truth,kME1E_Truth,kME1F_Truth,
                           kME1A_Truth,kME1G_Truth,kME1L_Truth,kME1M_Truth,kME1N_Truth};

enum Muon2DVar{kPT_PZ, kPT_theta ,kPZ_theta ,kE_theta ,kE_PZ ,kE_PT, kVertex_Z_R};

enum VetoWall_vars{kmatchToVeto , knumbermatchToVeto, kSixPush, kextrapnowalls, kextrapwall1,
  kextrapwall2, kextrapbothwalls, kMuonTrkMatchToVETOwalloff, kPMTMap, kPMTMap_On, kPMTMap_Off};

enum ME_helium_Status {kEMPTY, kFULL, kFull_Empty, kMC_FULL, kMC_EMPTY, kDATA_FULL, kDATA_EMPTY, kNULL};

enum Material_type {kIron, kHelium, kCarbon, kLead, kAluminium, kMaterial_OTHER, kMaterial_Total};

enum Interaction_type {kElastic, kRes_Coh_Pion,  kDIS, k2p2h, kInteraction_OTHER, kInteraction_Total, kInteraction_NONE };

enum Particle_type {kElectron, kPion_neg, kPion_pos, kPion_0, kPion_combine, kKaon, kProton, kNeutron,
   kMuon, kGamma, kNeutrino_muon, kNeutrino_electron, kAnti_Neutrino, kFourHelium, kLamdba, kSigma_plus,
    kParticle_OTHER, kParticle_N_A, kParticle_Total};

enum Veto_status_type {kPMTON, kPMTOFF};

enum Weights{ kweightFlux, kweightMinos, kweight2p2ptune, kweightRPA, kweightGenie, kweightLowQ2Pi,
   kweight_HeliumTargetMass, kweightNone};

enum StackType {kMaterial, kInteraction,kParticle, kCryoTankRegions, kTrackType, kVertexOptions, kboolNTrack};

enum Migration{Mig_E, Mig_PT, Mig_PZ, Mig_theta};

enum CryoTank_REGIONS{kUpstream_head, kCenter , kDownstream_head, kOUTSIDE};

enum SecTrkAngle{kAngle15,kAngle30,kAngle45,kAngle60};

enum TrackType{kShort, kLong, kOtherLong, kNotdefinedTrack};

enum VertexOptions{kOpt_1,kOpt_2,kOpt_3,kOpt_4};

enum boolNTrack{kone_Trk, ktwo_Trk, kmore_Trk, kallfalseTrk};

enum CrossSectionHist{Data_signal, Data_BG, Data_signal_potNorm, Data_BG_potNorm, Data_signal_BGsub_potNorm,
                      Data_signal_unfolded, Data_signal_unfolded_effcorrected, Data_crosssection, True_crosssection,
                      nom_Eff, dom_Eff, Eff, h_flux, Mig};






//enum class {
//kIron, kHelium, kCarbon,kLead, kAluminium, kmaterial_typeOTHER, kmaterial_typeTotal,
//};
struct GaussianResolutionFits{
double CutValue;
double TotalN;
double Sigma;
double Mean;
double Constant;
double ChiSqrt;
int NDF;

};




struct ArachnesecTrk
{
  int   run;
  int   subrun;
  int   gate;
  int   slice;
  double secTrk_angle_wrtb;
  double secTrk_KE;
  int    secTrk_PDG;
};

struct Arachne_alltracks
{
  int   run;
  int   subrun;
  int   gate;
  int   slice;

  int totalNTRK;
  std::vector <int>  Trk_PDG;
  std::vector <double> Trk_angle;
  std::vector <double> Trk_Energy;

};


struct True_Event_info{

  int mc_incoming;
  int mc_current;
  int interaction_type;
  int material_Z;
  int SecTk_index;
  std::vector <int>  PDGs;
  std::vector <double> Angles_Degs;
  std::vector <double> Energies_GeV;

};

struct ALL_True_Event_info{

  int mc_incoming;
  int mc_current;
  int interaction_type;
  int material_Z;
  int SecTk_index;
  int mother_index;
  int Fdaughter_index;
  int Ldaughter_index;
  std::vector <int>  PDGs;
  std::vector <double> Angles_Degs;
  std::vector <double> Energies_GeV;
  std::vector <int>  PDG_ALL_event_IDS;
};

struct SliceID_secTrk{

  int run;
  int subrun;
  int gate;
  int slice;
  double angle;
  double Energy_GeV;
  int pdg;

};

typedef std::map<Particle_type, PlotUtils::MnvH1D*  > Particle_MnvH1D_Map;
typedef std::map<Material_type, PlotUtils::MnvH1D*  > Material_type_MnvH1D_Map;
typedef std::map<Interaction_type, PlotUtils::MnvH1D*  > Interaction_type_MnvH1D_Map;

typedef std::map<ECuts, double > RECO_Cut_Map;
typedef std::map<ECutsTRUTH, double > TRUE_Cut_Map;

typedef std::map<ECuts, double> EventCount_RECO;
typedef std::map<ECuts,std::vector<Vertex_XYZ> > EventCount_CryoVertex_Vector;
typedef std::map<ECutsTRUTH, double> EventCount_Truth;
//typedef std::map<Particle_type, double>    Particle_Map;
//typedef std::map<Material_type, double>    Material_type_Map;
//typedef std::map<Interaction_type, double> Interaction_type_Map;

struct Particle_Map {
  Particle_type type;
  double Amount;
};

struct Material_Map {
  Material_type type;
  double Amount;
};

struct Interaction_Map {
  Interaction_type type;
  double Amount;
};


struct Track_Map {
  TrackType type;
  double Amount;
};

struct VertexOptions_Map {
  VertexOptions type;
  double Amount;
};

struct boolNTrack_Map {
  boolNTrack type;
  double Amount;
};


struct Hist_phyiscs_map{
  char *Hist_name;
  ME_helium_Playlists playlist;
  ME_helium_Status Crytank_status;
  bool RecoorTruth;
  std::vector<Particle_Map> Particle_vector;
  std::vector<Material_Map> Material_vector;
  std::vector<Interaction_Map> Interaction_vector;
};

struct Hist_phyiscs_map_withtrack{
  char *Hist_name;
  ME_helium_Playlists playlist;
  ME_helium_Status Crytank_status;
  bool RecoorTruth;
  std::vector<Particle_Map> Particle_vector;
  std::vector<Material_Map> Material_vector;
  std::vector<Interaction_Map> Interaction_vector;
  std::vector<Track_Map> Track_vector;
};


struct EventCut_Rate_STRUCT{
   char *RECOBRANCH_TGraph_RECO_TRUTH_name;
   char *RECOBRANCH_TGraph_RECO_name;
   char *TRUTHBRANCH_TGraph_name;
  ME_helium_Playlists playlist;
  ME_helium_Status Crytank_status;
  TRUE_Cut_Map TRUTHBRANCH_TRUE_EVENTSECTION_MAP;
  TRUE_Cut_Map RECOBRANCH_TRUE_EVENTSECTION_MAP;
  RECO_Cut_Map RECOBRANCH_TRUE_RECO_EVENTSECTION_MAP;


};


/*
struct Hist_map_track{
  char *Hist_name;
  ME_helium_Playlists playlist;
  ME_helium_Status Crytank_status;
  bool RecoorTruth;
  bool isData;
  std::vector<Track_Map> Track_vector;

};
*/

struct Hist_map_track{
  char *Hist_name;
  ME_helium_Playlists playlist;
  ME_helium_Status Crytank_status;
  bool RecoorTruth;
  bool isData;
  std::vector<Track_Map> Track_vector;
  std::vector<VertexOptions_Map> VertexOptions_vector;
  std::vector<boolNTrack_Map> boolNTrack_vector;

};



struct CrossSection_histNames{

MuonVar MuonType;
std::string Reco_hist_name;
std::string Migration_name;
std::string Data_hist_name;
std::string hist_Eff_denominator_name;
std::string hist_Eff_numerator_name;
std::string hist_Flux_name;
};

struct CrossSection_Hist{

MuonVar MuonType;
PlotUtils::MnvH1D* h_flux;
PlotUtils::MnvH1D* h_Data_Signal;
PlotUtils::MnvH1D* h_RECO_Signal;
PlotUtils::MnvH1D* h_effNum;
PlotUtils::MnvH1D* h_effDom;
PlotUtils::MnvH2D* h_Mig;

};

typedef std::map< std::string, std::vector<HeliumCVUniverse*> > UniverseMap;
typedef std::map<const std::string, int> error_name_Map;
typedef std::map<std::string,  std::vector<int>> MnvReponse_ErrorUniv_Hist_numbers;
typedef std::map<int, int> error_name_Univ_MvnHistMap;

typedef std::map<ME_helium_Playlists, EventCount_RECO > EventPlaylist_RecoCount;
typedef std::map< ME_helium_Status ,std::vector<ME_helium_Playlists>> FullAndEmptyPlaylistMap;

typedef std::map<ME_helium_Status, double> Pot_MapStatusList;
typedef std::map<ME_helium_Status, double> CyroStatusPot_MapList;

typedef std::map<ME_helium_Playlists, double> Pot_MapList;


typedef std::pair<ME_helium_Playlists, TFile*> ME_playlist_TFilePAIR;
typedef std::map<ME_helium_Playlists, TFile*> ME_playlist_TFileMAP;

typedef std::pair<ME_helium_Playlists,std::string> ME_playlist_RootPathPAIR;
typedef std::map<ME_helium_Playlists, std::string> ME_playlist_RootPathMAP;

typedef std::pair<ME_helium_Playlists,CrossSection_Hist> ME_playlist_CrossSection_PAIR;
typedef std::map<ME_helium_Playlists, CrossSection_Hist> ME_playlist_CrossSection_MAP;



typedef std::map<ME_helium_Playlists, PlotUtils::MnvH1D*> Playlist_MnvH1D_Map;
typedef std::map<ME_helium_Playlists, PlotUtils::MnvH2D*> Playlist_MnvH2D_Map;

typedef std::map<ME_helium_Playlists, PlotUtils::HistFolio<PlotUtils::MnvH1D>> Playlist_HistFolio_MnvH1D_Map;
typedef std::map<CrossSectionHist, PlotUtils::MnvH1D*> CrossSection_MnvH1D_Map;
typedef std::map<CrossSectionHist, std::string> CrossSection_name_Map;
typedef std::map<Migration, PlotUtils::MnvH2D*> Migration_MnvH2D_Map;


typedef PlotUtils::Hist2DWrapper<HeliumCVUniverse> CVH2DW;
typedef std::map<ME_helium_Playlists, PlotUtils::MnvH2D*> Playlist_MnvH2D_Map;
typedef std::map<ME_helium_Playlists, PlotUtils::HistFolio<PlotUtils::MnvH2D>> Playlist_HistFolio_MnvH2D_Map;


namespace Helium2DPlayListInfo_Pathways{

  const std::string ME_LOCAL_PLAYLIST_txtFILE_mc = "/minerva/app/users/cnguyen/cmtuser/Minerva_v22r1p1Helium/Ana/VetoWallStudies/scripts/ChainWrapper_ME2D/playlists/MC_Playlist/";
  const std::string ME_LOCAL_PLAYLIST_txtFILE_data = "/minerva/app/users/cnguyen/cmtuser/Minerva_v22r1p1Helium/Ana/VetoWallStudies/scripts/ChainWrapper_ME2D/playlists/Data_Playlist/";
  const std::string ME_PNFS_ROOT_Pathway = "/pnfs/minerva/persistent/users/cnguyen/";


}


template <typename T, typename U>
bool CompareMap_ME_helium_PlaylistsKeys(std::map<ME_helium_Playlists,T>& l,  std::map<ME_helium_Playlists,U>& r)
{
  if(l.size() != r.size())
  {
    std::cout<<"Maps are different Sizes"<<std::endl;
    return false;
  }

  typename std::map<ME_helium_Playlists,T>::const_iterator i;
  typename std::map<ME_helium_Playlists,U>::const_iterator j;

  for(i = l.begin(), j = r.begin(); i != l.end(); ++i, ++j)
  {
    if(i->first != j->first) { return false;}
  }
  return true;

} //



// Don't mix up true/reco hadron containers
//typedef int TruePionIdx;
//typedef int RecoPionIdx;

typedef PlotUtils::MnvH1D MH1D;
typedef PlotUtils::HistWrapper<HeliumCVUniverse> CVHW;

typedef std::map<std::string, std::vector<HeliumCVUniverse*>> UniverseMap;


class HeliumPlayListInfo{
  std::string m_playlist_type;
  double m_normweightLowP;
  double m_normweightHighP;
  double m_normweightLowPErr;
  double m_normweightHighPErr;

public:
  HeliumPlayListInfo(std::string playlist ){
  //SetplaylistName( playlist);
  //std::string playlist =  GetPlaylist(playlist_type);

  m_playlist_type = playlist;

  std::cout<<"initializer Playlist info for PlayList = "<< m_playlist_type<<std::endl;

  MnvNormalizer *MnvNorm = new MnvNormalizer("Inextinguishable", playlist);

   SetLowP(MnvNorm->GetCorrection(1000)); //Get the mnv norm weight for low P muons
   SethighP(MnvNorm->GetCorrection(10000)); //Get the mnv norm weight for high P muons
   SetLowPErr( MnvNorm->GetCorrectionErr(1000)); //Get the mnv norm weight error for low P muons
   SethighPErr(MnvNorm->GetCorrectionErr(10000)); //Get the mvn norm weight error for high P muons
  }


void SetplaylistName(std::string playlist){m_playlist_type = playlist;}
void SetLowP(double lowP){m_normweightLowP =lowP;}
void SethighP(double highP){m_normweightHighP =highP;}
void SetLowPErr(double lowP){m_normweightLowPErr = lowP;}
void SethighPErr(double highP){m_normweightHighPErr = highP;}
double GetLowP_Rang(){return m_normweightLowP;}
double GetHighP_Rang(){return m_normweightHighP;}
std::string GetPlaylistname(){return m_playlist_type; }

};

/*
HeliumPlayListInfo::HeliumPlayListInfo(std::string playlist) {
//SetplaylistName( playlist);

MnvNormalizer *MnvNorm = new MnvNormalizer("Eroica", playlist);

 SetLowP(MnvNorm->GetCorrection(1000)); //Get the mnv norm weight for low P muons
 SethighP(MnvNorm->GetCorrection(10000)); //Get the mnv norm weight for high P muons
 SetLowPErr( MnvNorm->GetCorrectionErr(1000)); //Get the mnv norm weight error for low P muons
 SethighPErr(MnvNorm->GetCorrectionErr(10000)); //Get the mvn norm weight error for high P muons


}

*/

//==============================================================================


//==============================================================================
// Systematic shift constants
//==============================================================================


//==============================================================================
// Color schemes
//==============================================================================
namespace CCNuPionIncPlotting {
  //const int N_COLORS=10;
  //const int colors[N_COLORS] = {kRed+1, kOrange+8, kGray+1, kOrange-7, kGreen+2, kYellow+2, kCyan-3, kBlue-7, kMagenta-6, kMagenta+2};

  //const int colors[N_COLORS] = {kRed+3, kOrange+9, kGray+2, kOrange+3, kGreen+3, kYellow+3, kCyan-2, kBlue-7, kMagenta-6, kMagenta+2};
  //const int fill_colors[N_COLORS] = {kRed+1, kOrange+6, kGray+1, kOrange-5, kGreen-2, kYellow+2, kCyan-8, kBlue-9, kMagenta-9, kMagenta-2};

  const int N_COLORS = 8;
  const int colors[N_COLORS] = {kRed+3, kOrange+9, kGray+2,kBlue , kCyan-2,kGreen+3 , kMagenta-6, kMagenta+2 };
  const int fill_colors[N_COLORS] = {kRed+1, kOrange+6, kGray+1,kBlue-6 , kCyan-8, kGreen-2, kMagenta-9, kMagenta-2};

   const int nColors2 = 12;
   const int colors2[nColors2]={
                       kMagenta+1,
                       kOrange+2,
                       kTeal-7,
                       kRed-6,
                       kSpring-1,
                       kBlue,
                       kAzure+7,
                       kCyan+2,
                       kViolet-4,
                       kGreen+3,
                       kYellow+2,
                       kGray+2,
   };
   const int fill_colors2[nColors2]={
                       kMagenta-1,
                       kOrange,
                       kTeal-9,
                       kRed-8,
                       kSpring-3,
                       kBlue-2,
                       kAzure+5,
                       kCyan,
                       kViolet-6,
                       kGreen+1,
                       kYellow,
                       kGray,
   };

   const int nColors3 = 7;
   const int colors3[nColors3]={
                       kGreen+3,
                       kYellow+2,
                       kOrange+6,
                       kBlue,
                       kCyan+2,
                       kRed+3,
                       kAzure+7
   };
   const int fill_colors3[nColors3]={
                       kGreen+1,
                       kYellow,
                       kOrange+5,
                       kAzure-2,
                       kCyan,
                       kRed+1,
                       kAzure+5
   };

   const int nColors4 = 6;
   const int colors4[nColors4]={
                       kRed+3,
                       kBlue-6,
                       kMagenta-6,
                       kOrange+6,
                       kGreen-2,
                       kAzure+8
   };
   const int fill_colors4[nColors4]={
                       kRed+1,
                       kBlue-2,
                       kMagenta-3,
                       kOrange+5,
                       kGreen-6,
                       kAzure+7
   };

   const int nColors5 = 7;
   const int colors5[nColors5]={
                       kGreen+3,
                       kGray+2,
                       kBlue,
                       kYellow+2,
                       kCyan+2,
                       kRed+3,
                       kAzure+7
   };
   const int fill_colors5[nColors5]={
                       kGreen+1,
                       kGray,
                       kBlue-2,
                       kYellow,
                       kCyan,
                       kRed+1,
                       kAzure+5
   };

  const int coherent_fill_color = kRed-7;
  const int coherent_color = kRed-3;
}

//==============================================================================
// Constants from CCPion const
//==============================================================================
namespace HeliumConsts {

  const double CHARGED_PION_MASS = 139.569;
  const double CHARGED_KAON_MASS = 493.677;
  const double MUON_MASS = 105.659;
  const double PROTON_MASS = 938.3;

  const double CHARGED_PION_MASS_GEV = .139569; // GeV
  const double CHARGED_KAON_MASS_GEV = .493677; // GeV
  const double MUON_MASS_GEV = .105659; // GeV
  const double PROTON_MASS_GEV = .9383; // GeV
  const int HeliumZ = 2;

}




namespace HeliumPlayListInfo_Pathways{

  const std::string ME_LOCAL_PLAYLIST_txtFILE_mc = "/minerva/app/users/cnguyen/cmtuser/Minerva_v22r1p1Helium/Ana/VetoWallStudies/scripts/ChainWrapper_ME/playlists/MC_Playlist/";
  const std::string ME_LOCAL_PLAYLIST_txtFILE_data = "/minerva/app/users/cnguyen/cmtuser/Minerva_v22r1p1Helium/Ana/VetoWallStudies/scripts/ChainWrapper_ME/playlists/Data_Playlist/";
  const std::string ME_PNFS_ROOT_Pathway = "/pnfs/minerva/persistent/users/cnguyen/";


}

//==============================================================================
class LatexFormat{
std::string  beginFrame_string = "\\begin{frame}";
std::string  endFrame_string = "\\end{frame}";
std::string  beginTabular = "\\begin{tabular}{";
std::string  EndTabular = "\\end{tabular}";
std::string  Centering = "\\centering";
double m_scale;
std::string m_pdf_Name;
std::string m_PlotsPerPage= "ccc";

public:
  LatexFormat( double scale){

    m_scale = scale;

  }


  void SetPlotsPerPage(std::string PlotsPerPage){m_PlotsPerPage = PlotsPerPage;}
  std::string GetNPlotsPreSide(){return m_PlotsPerPage;}
  double GetScale(){return m_scale;}
  std::string GetBeginFrame(){return beginFrame_string; }
  std::string GetEndFrame(){return endFrame_string; }
  std::string GetSubSection(std::string name )
  {
    std::string sub = "\\subsection{ " + name + " }";
    return sub;
  }

  std::string GetBeginFrame(std::string Title)
  {
    std::string BEGIN_start = this->GetBeginFrame();
    std::string BEGIN = BEGIN_start + "{ " + Title + " }";
    return BEGIN;
  }

  std::string GetBeginTabular(){
    std::string BEGIN_start = beginTabular + this->GetNPlotsPreSide() + "}";
    return BEGIN_start;
  }

  std::string GetBeginTabular(std::string input){
    std::string BEGIN_start = beginTabular + input + "}";
    return BEGIN_start;
  }

  std::string GetEndTabular(){return EndTabular;}

  std::string GetCentering(){return Centering;}

  std::string GetInclude_figure(int page, std::string pdf){
    double scale = GetScale();
    std::string Figure_string = "\\includegraphics[scale = " +  to_string_with_precision(scale,  2) + " , page = " + to_string_with_precision(page,2) + "]{" +  pdf + ".pdf}";
    return Figure_string;
  }

  std::string GetInclude_figure(int page, std::string pdf, double inputscale){
    double scale = inputscale;
    std::string Figure_string = "\\includegraphics[scale = " +  to_string_with_precision(scale,  2) + " , page = " + to_string_with_precision(page,2) + "]{" +  pdf + ".pdf}";
    return Figure_string;
  }

  std::string GetInclude_figure( std::string pdf){
    double scale = GetScale();
    std::string Figure_string = "\\includegraphics[scale = " +  to_string_with_precision(scale,  2) + " ]{" +  pdf + ".pdf}";
    return Figure_string;
  }

  std::string Get_URLlink( std::string url , std::string link_name){
    std::string string_to_return = "\\href{" + url + "}{" + link_name + "}";
    return string_to_return;
  }
  std::string BeingItemize(){
    std::string string_to_return = "\\begin{itemize}";
    return string_to_return;
  }
  std::string GetItem(){
    std::string string_to_return = "\\item ";
    return string_to_return;
  }

std::string EndItemize(){
std::string string_to_return = "\\end{itemize}";
return string_to_return;

}

std::string BinningLatexString(std::vector<double> Bins , std::string HistName , std::string Units ){
  /* Example of what i Want
  \resizebox{\textwidth}{!}{
  \begin{tabular}{||c|ccccccccccc|| }
  \hline
   Muon Energy Bins: & underflow && bin1 &  &bin2 &  & bin3&  & bin4 & & overflow \\
    \hline
  Binning limits [Units] &  &0.0 & & .2 & & 3.& & 4.& & 5.  & \\
  \hline
  \end{tabular}}
  */


int BinSize = Bins.size();

std::string  l_length(BinSize*2 + 2, 'c');

std::ostringstream output_string;
output_string.precision(2);
output_string << "\\resizebox{\\textwidth}{!}{" << "\n";
output_string << "\\begin{tabular}{||c|" << l_length << "c||} \n";
output_string << "\\hline \n";
output_string <<  HistName << "Bins: & underflow  ";
for(int cat=0; cat < BinSize-1; cat++ ) {output_string <<"& & bin  " << cat+1 <<" ";  }
output_string << "& & overflow \\\\ \n";
output_string << "\\hline \n";
output_string << "Binning limits [" << Units <<"]";
for(auto cat : Bins ) {output_string <<"& &  " << cat <<" ";  }
output_string << "& & & \\\\ \n";
output_string << "\\hline \n";
output_string << "\\end{tabular}} \n";


return output_string.str();


}




};//end of class


#endif

// common_stuff_h
