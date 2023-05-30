//File: Helium2D_runEventLoop.cxx
//Brief: Given ntuple files from HeAnaTupleTool.cpp , extracts 2D RECO EventSelction for 4Helium-Nu interactions
//Writes a .root file Event Selection histograms.
//
//Usage: RECO 2DEventSelection
//
//Author: Christian Nguyen  christian2nguyen@ufl.edu

#include "Helium2D_runEventLoop.h"

std::string OUTputRoot_pathway = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles";
//=====================================================
// Functions
//=====================================================
std::vector<ECuts> GetRECOCutsVector();
std::vector<ECuts> GetRECOCutsForEffVector();
std::vector<ECutsTRUTH> GetTRUTHCutsVector();
std::vector<MuonVar> GetMUONVaribles();
std::vector<SecondTrkVar> GetPlayListSecondTrkVector();
std::vector<CryoVertex> GetCryoVertexVaribles();

std::vector<Particle_type>  GetParicle_type();
std::vector<Weights> GetWeightVector();
std::vector<Weights> GetWeightVector_v2();
std::vector<Weights> GetWeightVector_mk();
//double Mev_to_GeV=.001;

// Get container of systematic
const bool m_RunCodeWithSystematics = true;
const bool RunwithConvolution = true;
const bool useweights = true;
const bool FidOn = true;
//vector <EventRunMAP> secTrkLowEnergy, secTrkHighAngle, secTrkLowEnergyAndHighAngle;

const std::vector<PlotUtils::NamedCategory<Material_type>>
MaterialGroup_categories = {
PlotUtils::NamedCategory<Material_type>({kMaterial_OTHER}, "Other"),
PlotUtils::NamedCategory<Material_type>({kIron},           "Iron"),
PlotUtils::NamedCategory<Material_type>({kCarbon},         "Carbon"),
PlotUtils::NamedCategory<Material_type>({kLead},           "Lead"),
PlotUtils::NamedCategory<Material_type>({kAluminium},      "Aluminium"),
PlotUtils::NamedCategory<Material_type>({kHelium},         "Helium")

};
const std::vector<PlotUtils::NamedCategory<Interaction_type>>
InteractionGroup_categories = {
  PlotUtils::NamedCategory<Interaction_type>({kInteraction_OTHER},"Other"),
  PlotUtils::NamedCategory<Interaction_type>({kInteraction_NONE}, "None"),
  PlotUtils::NamedCategory<Interaction_type>({kDIS},              "DIS"),
  PlotUtils::NamedCategory<Interaction_type>({k2p2h},             "2p2h"),
  PlotUtils::NamedCategory<Interaction_type>({kRes_Coh_Pion},     "Res_Coh"),
  PlotUtils::NamedCategory<Interaction_type>({kElastic},          "Elastic")
};

const std::vector<PlotUtils::NamedCategory<Interaction_type>>
InteractionGroupDISBreakdown_categories = {
  PlotUtils::NamedCategory<Interaction_type>({kInteraction_OTHER},"Other"),
  PlotUtils::NamedCategory<Interaction_type>({kDISSoft},          "SoftDIS"),
  PlotUtils::NamedCategory<Interaction_type>({kDISHard},          "HardDIS"),
  PlotUtils::NamedCategory<Interaction_type>({kDISSIS},           "SIS"),
  PlotUtils::NamedCategory<Interaction_type>({k2p2h},             "2p2h"),
  PlotUtils::NamedCategory<Interaction_type>({kdeltaRES},         "#DeltaRes"),
  PlotUtils::NamedCategory<Interaction_type>({kHeavierRES},       "HeavierRes"),
  PlotUtils::NamedCategory<Interaction_type>({kElastic},          "QE")
};
/*
const std::vector<PlotUtils::NamedCategory<Particle_type>>
ParticleGroup_categories = {
  PlotUtils::NamedCategory<Particle_type>({kParticle_N_A}, "N_A"),
  PlotUtils::NamedCategory<Particle_type>({kParticle_OTHER}, "Other"),
  PlotUtils::NamedCategory<Particle_type>({kElectron}, "Electron"),
  PlotUtils::NamedCategory<Particle_type>({kMuon},     "Muon"),
  PlotUtils::NamedCategory<Particle_type>({kGamma},    "Gamma"),
  PlotUtils::NamedCategory<Particle_type>({kNeutrino_muon}, "Neutrino_muon"),
  PlotUtils::NamedCategory<Particle_type>({kNeutrino_electron}, "Neutrino_electron"),
  PlotUtils::NamedCategory<Particle_type>({kAnti_Neutrino}, "Anti_Neutrino"),
  PlotUtils::NamedCategory<Particle_type>({kKaon},     "Kaon"),
  PlotUtils::NamedCategory<Particle_type>({kPion_0},     "Pi0"),
  PlotUtils::NamedCategory<Particle_type>({kPion_neg},     "Pi^{-}"),
  PlotUtils::NamedCategory<Particle_type>({kPion_pos},     "Pi^{+}"),
  PlotUtils::NamedCategory<Particle_type>({kProton},   "Proton"),
  PlotUtils::NamedCategory<Particle_type>({kNeutron},   "Neutron"),
  PlotUtils::NamedCategory<Particle_type>({kFourHelium},   "{}^{4}He"),
  PlotUtils::NamedCategory<Particle_type>({kLamdba},   "Lamdba"),
  PlotUtils::NamedCategory<Particle_type>({kSigma_plus},   "Sigma^{+}")

};


const std::vector<PlotUtils::NamedCategory<Particle_type>>
ParticleGroup_categories_new = {
  PlotUtils::NamedCategory<Particle_type>({kParticle_N_A}, "N_A"),
  PlotUtils::NamedCategory<Particle_type>({kParticle_OTHER}, "Other"),
  PlotUtils::NamedCategory<Particle_type>({kElectron}, "Electron"),
  PlotUtils::NamedCategory<Particle_type>({kMuon},     "Muon"),
  PlotUtils::NamedCategory<Particle_type>({kGamma},    "Gamma"),
  PlotUtils::NamedCategory<Particle_type>({kNeutrino_muon}, "Neutrino_muon"),
  PlotUtils::NamedCategory<Particle_type>({kNeutrino_electron}, "Neutrino_electron"),
  PlotUtils::NamedCategory<Particle_type>({kAnti_Neutrino}, "Anti_Neutrino"),
  PlotUtils::NamedCategory<Particle_type>({kKaon},     "Kaon"),
  PlotUtils::NamedCategory<Particle_type>({kPion_0},     "Pi0"),
  PlotUtils::NamedCategory<Particle_type>({kPion_neg},     "Pi^{-}"),
  PlotUtils::NamedCategory<Particle_type>({kPion_pos},     "Pi^{+}"),
  PlotUtils::NamedCategory<Particle_type>({kProton},   "Proton"),
  PlotUtils::NamedCategory<Particle_type>({kNeutron},   "Neutron"),
  PlotUtils::NamedCategory<Particle_type>({kFourHelium},   "{}^{4}He"),
  PlotUtils::NamedCategory<Particle_type>({kLamdba},   "Lamdba"),
  PlotUtils::NamedCategory<Particle_type>({kSigma_plus},   "Sigma^{+}")

};
*/

const std::vector<PlotUtils::NamedCategory<Particle_type>>
ParticleGroup_reduced_categories = {
  PlotUtils::NamedCategory<Particle_type>({kProton},                 "Proton"),
  PlotUtils::NamedCategory<Particle_type>({kPion_pos_neg},           "Pion_pos_neg"),
  PlotUtils::NamedCategory<Particle_type>({kParticle_neutral},       "Neutral"),
  PlotUtils::NamedCategory<Particle_type>({kMuon},                   "Muon"),
  PlotUtils::NamedCategory<Particle_type>({kPion_0_Electron_kGamma}, "Pion_0_Electron_kGamma"),
  PlotUtils::NamedCategory<Particle_type>({kParticle_OTHER},         "Other")
};

/*
const std::vector<PlotUtils::NamedCategory<Particle_type>>
ParticleGroup_reduced_categories = {
  PlotUtils::NamedCategory<Particle_type>({kParticle_N_A},          "N_A"),
  PlotUtils::NamedCategory<Particle_type>({kParticle_OTHER},        "Other"),
  PlotUtils::NamedCategory<Particle_type>({kParticle_neutral},      "Neutral"),
  PlotUtils::NamedCategory<Particle_type>({kMuon},                   "Muon"),
  PlotUtils::NamedCategory<Particle_type>({kPion_0_Electron_kGamma},"Pion_0_Electron_Gamma"),
  PlotUtils::NamedCategory<Particle_type>({kPion_pos_neg},          "#pi^{#pm}"),
  PlotUtils::NamedCategory<Particle_type>({kProton},                "Proton")


};
*/


const std::vector<PlotUtils::NamedCategory<OpenAngle>>
OpenAngle_Category = {
  PlotUtils::NamedCategory<OpenAngle>({kOAngle5},    "angle5"),
  PlotUtils::NamedCategory<OpenAngle>({kOAngle10},   "angle10"),
  PlotUtils::NamedCategory<OpenAngle>({kOAngle15},   "angle15"),
  PlotUtils::NamedCategory<OpenAngle>({kOAngle20},   "angle20"),
  PlotUtils::NamedCategory<OpenAngle>({kOAngle25},   "angle25"),
  PlotUtils::NamedCategory<OpenAngle>({kOAngle30},   "angle30"),
  PlotUtils::NamedCategory<OpenAngle>({kOAngle45},   "angle45"),
  PlotUtils::NamedCategory<OpenAngle>({kOAngle60},   "angle60")
};

/*const auto TracksGreaterThan2 = {  NamedCategory<int>({3},   "ThirdTrack"),
                                   NamedCategory<int>({4},   "FourthTrack"),
                                   NamedCategory<int>({5},   "FifthTrack"),
                                   NamedCategory<int>({6},   "SixthTrack"),
                                   NamedCategory<int>({7},   "SevethTrack"),
                                   NamedCategory<int>({8},   "EighthTrack")

                                 };*/
const int n_flux_universes = 100;

/*UniverseMap GetErrorBands(PlotUtils::ChainWrapper* chain, , ME_helium_Status CryoTankStatus )) {
    //typedef std::map< std::string, std::vector<HeliumCVUniverse*> > SystMap;
    UniverseMap error_bands;
    //SystMap error_bands;

    //========================================================================
    // CV
    //========================================================================

    error_bands[std::string("cv")].push_back( new HeliumCVUniverse(chain) );

    if(m_RunCodeWithSystematics){

      //========================================================================
      ///// Minerva Muon Energy
      //========================================================================

      SystMap MinervaMuon_systematics = PlotUtils::GetMinervaMuonSystematicsMap<HeliumCVUniverse>(chain);
      error_bands.insert(MinervaMuon_systematics.begin(), MinervaMuon_systematics.end());


      //========================================================================
      // MINOS efficiency
      //========================================================================

      SystMap MinosMuon_systematics = PlotUtils::GetMinosMuonSystematicsMap<HeliumCVUniverse>(chain);
      error_bands.insert(MinosMuon_systematics.begin(), MinosMuon_systematics.end());

      //========================================================================
      // Muon match efficiency
      //========================================================================

      SystMap MinosEff_systematics = PlotUtils::GetMinosEfficiencySystematicsMap<HeliumCVUniverse>(chain);
      error_bands.insert(MinosEff_systematics.begin(), MinosEff_systematics.end());

      //========================================================================
      //Flux
      //========================================================================

      SystMap flux_systematics = PlotUtils::GetFluxSystematicsMap<HeliumCVUniverse>(chain,n_flux_universes);
      error_bands.insert(flux_systematics.begin(), flux_systematics.end());

      //========================================================================
      // Beam Angle
      //========================================================================

      SystMap angle_systematics = PlotUtils::GetAngleSystematicsMap<HeliumCVUniverse>(chain,NSFDefaults::beamThetaX_Err,NSFDefaults::beamThetaY_Err);
      error_bands.insert(angle_systematics.begin(), angle_systematics.end());

      //========================================================================
      // GENIE FSI + CrossSection
      //========================================================================

      SystMap genie_systematics = PlotUtils::GetGenieSystematicsMap<HeliumCVUniverse>(chain);
      error_bands.insert(genie_systematics.begin(), genie_systematics.end());

      //========================================================================
       // MnvTunes
       //========================================================================
       // 2p2h

      SystMap a2p2h_systematics = PlotUtils::Get2p2hSystematicsMap<HeliumCVUniverse>(chain);
      error_bands.insert(a2p2h_systematics.begin(), a2p2h_systematics.end());

      //========================================================================
      // (RPA)random phase appox , long range Nuclear correlations modeling
      //========================================================================

      SystMap RPA_systematics = PlotUtils::GetRPASystematicsMap<HeliumCVUniverse>(chain);
      error_bands.insert(RPA_systematics.begin(), RPA_systematics.end());

      //SystMap LowQ2Pi_systematics = PlotUtils::GetLowQ2PiSystematicsMap<HeliumCVUniverse>(chain);
      //error_bands.insert(LowQ2Pi_systematics.begin(), LowQ2Pi_systematics.end());

      //========================================================================
      // Helium
      //========================================================================


      SystMap VertexSmearing_systematics = GetHELIUMVertexSmearingShiftSystematicsMap<HeliumCVUniverse>(chain);
      error_bands.insert(VertexSmearing_systematics.begin(), VertexSmearing_systematics.end());

      SystMap HeliumTargetMass_systematics = GetHeliumTargetMassSystematicsMap<HeliumCVUniverse>(chain);
      error_bands.insert(HeliumTargetMass_systematics.begin(), HeliumTargetMass_systematics.end());

    }


  return error_bands;
}*/
UniverseMap GetErrorBands(PlotUtils::ChainWrapper* chain , ME_helium_Status CryoTankStatus ) {

    //return Map
    UniverseMap error_bands;

    // CV
    error_bands[std::string("cv")].push_back( new HeliumCVUniverse(chain) );

    //Detector systematics, lateral sh

if(m_RunCodeWithSystematics){

    //========================================================================
    // FLUX
    //========================================================================

    UniverseMap flux_systematics = PlotUtils::GetFluxSystematicsMap<HeliumCVUniverse>(chain,n_flux_universes);
    error_bands.insert(flux_systematics.begin(), flux_systematics.end());

    //========================================================================
    // Muons
    //========================================================================

    ///// MINOS ERROR systems
    // Muon reco in MINERvA -- Catchall systematic for pmu reco in minerva.
    // Lateral-only. Shifts pmu.

    UniverseMap MinervaMuon_systematics = PlotUtils::GetMinervaMuonSystematicsMap<HeliumCVUniverse>(chain);
    error_bands.insert(MinervaMuon_systematics.begin(), MinervaMuon_systematics.end());
    // Minerva Error System

    // Vertical only
    // MINOS efficiency

    UniverseMap MinosMuon_systematics = PlotUtils::GetMinosMuonSystematicsMap<HeliumCVUniverse>(chain);
    error_bands.insert(MinosMuon_systematics.begin(), MinosMuon_systematics.end());

    // Muon match efficiency
    UniverseMap MinosEff_systematics = PlotUtils::GetMinosEfficiencySystematicsMap<HeliumCVUniverse>(chain);
    error_bands.insert(MinosEff_systematics.begin(), MinosEff_systematics.end());


    // Muon Energy resolution
    UniverseMap MuonEnergyResolution_systematics =PlotUtils::GetMuonResolutionSystematicsMap<HeliumCVUniverse>(chain);
      error_bands.insert(MuonEnergyResolution_systematics.begin(), MuonEnergyResolution_systematics.end());


   // Beam Angle
    UniverseMap angle_systematics = PlotUtils::GetAngleSystematicsMap<HeliumCVUniverse>(chain);/*,NSFDefaults::beamThetaX_Err,NSFDefaults::beamThetaY_Err*/
    error_bands.insert(angle_systematics.begin(), angle_systematics.end());

    UniverseMap MuonangleResolution_systematics = PlotUtils::GetMuonAngleResolutionSystematicsMap<HeliumCVUniverse>(chain);
    error_bands.insert(MuonangleResolution_systematics.begin(), MuonangleResolution_systematics.end());


    //========================================================================
    // GENIE
    //========================================================================
    // Standard

    UniverseMap genie_systematics = PlotUtils::GetGenieSystematicsMap<HeliumCVUniverse>(chain);
    error_bands.insert(genie_systematics.begin(), genie_systematics.end());

    //========================================================================
     // MnvTunes
     //========================================================================
     // 2p2h

    UniverseMap a2p2h_systematics = PlotUtils::Get2p2hSystematicsMap<HeliumCVUniverse>(chain);
    error_bands.insert(a2p2h_systematics.begin(), a2p2h_systematics .end());

    // RPA
    UniverseMap RPA_systematics = PlotUtils::GetRPASystematicsMap<HeliumCVUniverse>(chain);
    error_bands.insert(RPA_systematics.begin(), RPA_systematics.end());

    //========================================================================
    // Helium
    //========================================================================

    UniverseMap VertexSmearing_systematics = GetHELIUMVertex_XYZ_SmearingShiftSystematicsMap<HeliumCVUniverse>(chain,CryoTankStatus);
    error_bands.insert(VertexSmearing_systematics.begin(), VertexSmearing_systematics.end());



    UniverseMap HeliumTargetMass_systematics = GetHeliumTargetMassSystematicsMap<HeliumCVUniverse>(chain);
    error_bands.insert(HeliumTargetMass_systematics.begin(), HeliumTargetMass_systematics.end());

    // response efficiency
    //UniverseMap recoil_systematics = PlotUtils::GetRecoilSystematicsMap<HeliumCVUniverse>(chain,true);
    //error_bands.insert(recoil_systematics.begin(), recoil_systematics.end());
    //Flux


    //UniverseMap LowQ2Pi_systematics = PlotUtils::GetLowQ2PiSystematicsMap<HeliumCVUniverse>(chain);
    //error_bands.insert(LowQ2Pi_systematics.begin(), LowQ2Pi_systematics.end());

}

  // Non-res pi
  //UniverseMap nonrespi_systematics =
  //  PlotUtils::GetNonResPiSystematicsMap<HeliumCVUniverse>(chain);
  //error_bands.insert(nonrespi_systematics.begin(), nonrespi_systematics.end());

  return error_bands;
}

//======================================================================
// End of Error Universe
//======================================================================


//======================================================================
// Event Loop
//======================================================================

void runEventLoop(bool &m_debugOn, ME_helium_Playlists &PlayList_iterator) {
  loadLibs();
TH1::AddDirectory(kFALSE);

const std::vector<ECuts> kCutsVector = GetRECOCutsVector();
const std::vector<ECuts> kCutsVector_Eff = GetRECOCutsForEffVector();
const std::vector<ECutsTRUTH> kTRUTHCutsVector = GetTRUTHCutsVector();

const std::vector<Weights> kWeights_v1tune= GetWeightVector();
const std::vector<Weights> kWeights_v2tune= GetWeightVector_v2();
const std::vector<Weights> kWeights_forMK = GetWeightVector_mk();
const std::vector<MuonVar> kMuonVaribles_vector = GetMUONVaribles();
const std::vector<SecondTrkVar> kSecTrkVaribles_vector = GetPlayListSecondTrkVector();

const std::vector<CryoVertex> kCryoVertexVaribles_vector = GetCryoVertexVaribles();

RECO_Cut_Map CountMap_RECO;// = ConstuctRecoCountingMap(kCutsVector);
RECO_Cut_Map CountMap_RECO_Helium ;//= ConstuctRecoCountingMap(kCutsVector);
RECO_Cut_Map CountMap_RECO_nonHelium;// = ConstuctRecoCountingMap(kCutsVector);
RECO_Cut_Map CountMap_TRUE_RECO;
TRUE_Cut_Map Truth_Cut_Map;

FillingRecoCountingMap(kCutsVector, CountMap_RECO);
FillingRecoCountingMap(kCutsVector, CountMap_RECO_Helium);
FillingRecoCountingMap(kCutsVector, CountMap_RECO_nonHelium);
FillingRecoCountingMap(kCutsVector_Eff, CountMap_TRUE_RECO);
FillingTruthCountingMap(kTRUTHCutsVector, Truth_Cut_Map);


const std::vector<Particle_type> kSecondary_particle_vector = GetParicle_type();

double vertex_X_sigma = 0.0; double vertex_X_mean = 0.0;
double vertex_Y_sigma = 0.0; double vertex_Y_mean = 0.0;
double vertex_Z_sigma = 0.0; double vertex_Z_mean = 0.0;
std::default_random_engine generator;

if(RunwithConvolution == true){
Fill_Convolution_BeforeShift(PlayList_iterator ,vertex_X_mean,
  vertex_X_sigma, vertex_Y_mean, vertex_Y_sigma, vertex_Z_mean, vertex_Z_sigma);
}

std::normal_distribution<double> vertexZ_Convolution(vertex_Z_mean, vertex_Z_sigma);
std::normal_distribution<double> vertexX_Convolution(vertex_X_mean, vertex_X_sigma);
std::normal_distribution<double> vertexY_Convolution(vertex_Y_mean, vertex_Y_sigma);


//======================================================================
////////////////////ADDING TO CHAIN wrapper ///////////////////////////
//======================================================================
bool is_mc= true;

//PlotUtils::ChainWrapper* chw_FullMC = makeChainWrapperPtr("../playlists/playlist_MC_Mvn13C_ecoicaPlus_8_23_19.txt", "Muon");//
//PlotUtils::ChainWrapper* chw_MC = makeChainWrapperPtr("../playlists/MC_Playlist/ME_1G_MC.txt", "Muon");//

//======================================================================
// SET MINERVA Analysis Type and Universes
//======================================================================
  MinervaUniverse::SetDeuteriumGeniePiTune(false);
  MinervaUniverse::SetNuEConstraint(true);
  MinervaUniverse::SetZExpansionFaReweight(true);
  MinervaUniverse::SetAnalysisNuPDG(14);
  MinervaUniverse::SetNonResPiReweight(true);
  MinervaUniverse::SetNFluxUniverses(n_flux_universes);
  std::string playlist = GetPlaylist(PlayList_iterator);
  MinervaUniverse::SetPlaylist(playlist);
  MinervaUniverse::SetTruth(false);
  ME_helium_Status CryoTankStatus =  GetPlaylist_HeliumStatus(PlayList_iterator);

  //======================================================================
  // SET Flux Parameters for Intergrated Flux hist
  //======================================================================
  int nu_pdg = MinervaUniverse::GetAnalysisNuPDG();
  std::string playlist_fluxreweighter = MinervaUniverse::GetPlaylist();
  bool useNuEconstraint = MinervaUniverse::UseNuEConstraint();
  int NFlux_universe = MinervaUniverse::GetNFluxUniverses();
  bool useMuonCorrelations = true;
  double Min_NuFluxEnergy = 0.0;
  double Max_NuFluxEnergy = 120.0;

  //======================================================================
  //
  //======================================================================


  auto Playlist_txtFILEPath = GetPlaylist_txtFILE_path(PlayList_iterator, is_mc );
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"Adding to Chain Wrapper For Loop   "<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  PlotUtils::ChainWrapper* chw_MC = makeChainWrapperPtr(Playlist_txtFILEPath.c_str(), "HeAnaTupleTool");
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"Adding to Chain Wrapper For POT counter   "<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  PlotUtils::ChainWrapper* mcchainPOT = makeChainWrapperPtr(Playlist_txtFILEPath.c_str(), "Meta");

  //======================================================================
  ///////////////////Making/adding to error bands  ///////////////////////////
  //======================================================================
//std::map< std::string, std::vector<HeliumCVUniverse*> > error_bands = GetErrorBands(chw_FullMC);
//std::map<std::string, std::vector<HeliumCVUniverse*> > error_bands= GetErrorBands(chw_MC);

UniverseMap error_bands = GetErrorBands(chw_MC, CryoTankStatus);
error_name_Map error_name;
error_name_Univ_MvnHistMap MnvReponse_Hist_N_Map;
//std::map<const std::string,  int> error_Number;
for(auto band :error_bands ){std::cout<<"Checking Universe this is universe with name : " << band.first<<std::endl;}
//std::vector<std::vector<HeliumCVUniverse*>> Error_Band_Universe_GROUPS = groupCompatibleUniverses(error_bands); // Group Vertical and Laterial bands together



std::map<std::string, std::vector<HeliumCVUniverse*> >::iterator itr;
for(itr = error_bands.begin(); itr != error_bands.end(); ++itr) error_name.insert(std::pair<std::string, const int>((itr->second)[0]->ShortName(), (itr->second).size()));
int count = 0;

//for(itr = error_bands.begin(); itr != error_bands.end(); ++itr){
//  const int input = count;
//   error_name.insert(std::pair<std::string, const int>((itr->second)[0]->ShortName(), input));
//   count++;
// }

HeliumPlayListInfo Playlist_Info(playlist);
Fill_MnvReponse_ErrorUniv_Hist_numbers(MnvReponse_Hist_N_Map, error_name);

std::cout<<"checking Error Names "<< std::endl;
std::cout<<"MnvReponse_Hist_N_Map.size() = "<<MnvReponse_Hist_N_Map.size()<< std::endl;
for(auto cat : error_bands ){
std::cout<<"Universe Name = " <<cat.first << std::endl;
}
int unv_count = 0;

std::map<std::string, const int>::iterator itr_m;


//double mcPOT = GetPOT_local(mcchainPOT, "MC");
//std::cout<<"Number of Universes set is = "<<    MinervaUniverse::GetNFluxUniverses()<<std::endl;
//std::cout << "POT of this Playlist = "<< mcPOT <<std::endl;

//static weightMK *weight_MK;
//char *mparalocation = std::getenv("MPARAMFILESROOT");
//string dir_data = string(mparalocation)+"/data/Reweight/";
//weight_MK = new weightMK(dir_data + "output_ratio_genie_neut_for_MKmodel.root");

POTCounter pot_counter;


const std::string RootName = GetPlaylist_ROOT_path(PlayList_iterator, is_mc );
//const std::string RootName = GetPlaylist_ROOT_path("1F_pdgcorrection_2",  is_mc );
std::cout<<"The Playlist that is set is = "<< playlist.c_str()<<std::endl;
std::cout<<"The Playlist Root = "<< RootName<<std::endl;
 ///pnfs/minerva/persistent/users/cnguyen/ME_G1_Merg/*.root

std::cout<<"Working with Playlist =  "<<  Playlist_Info.GetPlaylistname()<<std::endl;

  //======================================================================
  // SET Binning for Hist
  //======================================================================
std::vector<double> Ebin_vector = GetBinMuonVector(kE_2D);
//std::vector<double> Pzbin_vector= GetBinMuonVector(kP_Z);
std::vector<double> PTbin_vector= GetBinMuonVector(kP_T_2D);
std::vector<double> Pzbin_vector = GetBinMuonVector(kP_Z_2D);


std::vector<double> Pzbin_finebinnning_vector= GetBinMuonVector(kP_Z);
std::vector<double> PTbin_finebinnning_vector= GetBinMuonVector(kP_T);

std::vector<double> MuonThetabin_vector= GetBinMuonVector(kAngleWRTB_2D);
std::vector<double> Muon_curvatureSig_vector= GetBinMuonVector(kcurvatureSig_2D);
std::vector<double> MuonCharge_vector= GetBinMuonVector(kCharge);
std::vector<double> AnglePhi_vector = GetBinMuonVector(kAnglePhi);

std::vector<double> Minos_Start_X_vector= GetBinMuonVector(kminosStart_X);
std::vector<double> Minos_Start_Y_vector= GetBinMuonVector(kminosStart_Y);
std::vector<double> Minos_Start_Z_vector= GetBinMuonVector(kminosStart_Z);

std::vector<double> Minos_End_X_vector= GetBinMuonVector(kminosEnd_X);
std::vector<double> Minos_End_Y_vector= GetBinMuonVector(kminosEnd_Y);
std::vector<double> Minos_End_Z_vector= GetBinMuonVector(kminosEnd_Z);

std::vector<double> Muon_StartNode_X_vector= GetBinMuonVector(kmuonFirstNodeX);
std::vector<double> Muon_StartNode_Y_vector= GetBinMuonVector(kmuonFirstNodeY);
std::vector<double> Muon_StartNode_Z_vector= GetBinMuonVector(kmuonFirstNodeZ);

std::vector<double> Muon_LastNode_X_vector= GetBinMuonVector(kmuonLastNodeX);
std::vector<double> Muon_LastNode_Y_vector= GetBinMuonVector(kmuonLastNodeY);
std::vector<double> Muon_LastNode_Z_vector= GetBinMuonVector(kmuonLastNodeZ);

std::vector<double> VectexTiming_vector = GetBinMuonVector(kmuonVertexTiming);
std::vector<double> Vertex_ChiSqFit_vector= GetBinvertexVector(kfitConverge_2D);
////////////////////////
std::vector<double> Vertex_Xbin_vector = GetBinvertexVector(kX_2D);
std::vector<double> Vertex_Ybin_vector = GetBinvertexVector(kY_2D);
std::vector<double> Vertex_Zbin_vector = GetBinvertexVector(kZ_2D);
std::vector<double> Vertex_Rbin_vector = GetBinvertexVector(kR_2D);

std::vector<double> VertexXYbins_coarse = GetBinvertexVector(kY_2D);
std::vector<double> bigAngle_bins{0.0, 15.0, 30.0, 45.0, 60.0};


std::vector<double> SecTrk_Thetamidbin_vector= GetSecondTrkVarVector(kThetamid);

std::vector<double> Vertex_DOCAbin_vector= GetBinMuonVector(kDOCA_muon_2D);
std::vector<double> Vertex_secondTrkEbin_vector= GetSecondTrkVarVector(ksecE_2D);
std::vector<double> Vertex_secondTrkTheta_vector= GetSecondTrkVarVector(ksecTheta_2D);
std::vector<double> SecTrk_DOCA_vector= GetSecondTrkVarVector(kDOCA_2D);
std::vector<double> SecTrk_Pathway_vector= GetSecondTrkVarVector(kPathway);

std::vector<double> SecTrk_Tracklength_vector= GetSecondTrkVarVector(ksec_tracklength_minerva_2D);


std::vector<double> MuonMatchtoMinos_vector= GetBinMuonVector(kMuonMatchtoMinos);
std::vector<double> TrackSize_vector= GetBinMuonVector(ktracksize);
std::vector<double> MuonMatchtoVeto_vector= GetBinMuonVector(kMuonMatchtoVeto);

std::vector<double> SecTRK_StartNode_X_vector= GetSecondTrkVarVector(kFirstsecTrk_Xnode);
std::vector<double> SecTRK_StartNode_Y_vector= GetSecondTrkVarVector(kFirstsecTrk_Ynode);
std::vector<double> SecTRK_StartNode_Z_vector= GetSecondTrkVarVector(kFirstsecTrk_Znode);

std::vector<double> SecTRK_LastNodeX_vector= GetSecondTrkVarVector(kLastsecTrk_Xnode);
std::vector<double> SecTRK_LastNodeY_vector= GetSecondTrkVarVector(kLastsecTrk_Ynode);
std::vector<double> SecTRK_LastNodeZ_vector= GetSecondTrkVarVector(kLastsecTrk_Znode);


std::vector<double> distance_edge_vector = GetBinvertexVector(kdistance_edge_2D);





/////////////////////////////////
// 2d reponse using bin space
////////////////////////////////
//vector<vector<double> > vector_2D_PZ_PT;
//vector_2D_PZ_PT.push_back(PTbin_vector);
//vector_2D_PZ_PT.push_back(Pzbin_vector);
//HyperDimLinearizer::HyperDimLinearizer *HyperDim2d_PZ_PT = new HyperDimLinearizer::HyperDimLinearizer(vector_2D_PZ_PT,0)
////////////////
//muon Varibles///
////////////////
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_PZ_PT("h_Muon_PZ_PT", "h_Muon_PZ_PT", Pzbin_vector, PTbin_vector , error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_PZ_PT_finebinning("h_Muon_PZ_PT_finebinning", "h_Muon_PZ_PT_finebinning", Pzbin_finebinnning_vector, PTbin_finebinnning_vector , error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_PZ_PT_BG("h_Muon_PZ_PT_BG", "h_Muon_PZ_PT_BG", Pzbin_vector, PTbin_vector , error_bands);



PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_PT_theta("h_Muon_PT_theta", "h_Muon_PT_theta", PTbin_vector , MuonThetabin_vector, error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_PZ_theta("h_Muon_PZ_theta", "h_Muon_PZ_theta", Pzbin_vector , MuonThetabin_vector, error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_E_theta("h_Muon_E_theta", "h_Muon_E_theta",  Ebin_vector , MuonThetabin_vector, error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_E_theta_BG("h_Muon_E_theta_BG", "h_Muon_E_theta_BG",  Ebin_vector , MuonThetabin_vector, error_bands);

PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_E_PZ("h_Muon_E_PZ", "h_Muon_E_PZ",  Ebin_vector ,  Pzbin_vector, error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_E_PT("h_Muon_E_PT", "h_Muon_E_PT",  Ebin_vector , PTbin_vector, error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_cryoVertex_Z_R("h_cryoVertex_Z_R", "h_cryoVertex_Z_R", Vertex_Zbin_vector, Vertex_Rbin_vector , error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_PT_cryoVertex_R("h_Muon_PT_cryoVertex_R", "h_Muon_PT_cryoVertex_R", PTbin_vector, Vertex_Rbin_vector , error_bands);

PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_PZ_PT_TRUE_RECO("h_Muon_PZ_PT_TRUE_RECO", "h_Muon_PZ_PT_TRUE_RECO", Pzbin_vector, PTbin_vector , error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_PT_theta_TRUE_RECO("h_Muon_PT_theta_TRUE_RECO", "h_Muon_PT_theta_TRUE_RECO", PTbin_vector , MuonThetabin_vector, error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_PZ_theta_TRUE_RECO("h_Muon_PZ_theta_TRUE_RECO", "h_Muon_PZ_theta_TRUE_RECO", Pzbin_vector , MuonThetabin_vector, error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_E_theta_TRUE_RECO("h_Muon_E_theta_TRUE_RECO", "h_Muon_E_theta_TRUE_RECO",  Ebin_vector , MuonThetabin_vector, error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_E_PZ_TRUE_RECO("h_Muon_E_PZ_TRUE_RECO", "h_Muon_E_PZ_TRUE_RECO",  Ebin_vector ,  Pzbin_vector, error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_E_PT_TRUE_RECO("h_Muon_E_PT_TRUE_RECO", "h_Muon_E_PT_TRUE_RECO",  Ebin_vector , PTbin_vector, error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_cryoVertex_Z_R_TRUE_RECO("h_cryoVertex_Z_R_TRUE_RECO", "h_cryoVertex_Z_R_TRUE_RECO", Vertex_Zbin_vector, Vertex_Rbin_vector , error_bands);

PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_cryoVertex_Z_X_TRUE_RECO("h_cryoVertex_Z_X_TRUE_RECO", "h_cryoVertex_Z_X_TRUE_RECO", Vertex_Zbin_vector, Vertex_Xbin_vector , error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_cryoVertex_Z_Y_TRUE_RECO("h_cryoVertex_Z_Y_TRUE_RECO", "h_cryoVertex_Z_Y_TRUE_RECO", Vertex_Zbin_vector, Vertex_Ybin_vector , error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_cryoVertex_X_Y_TRUE_RECO("h_cryoVertex_X_Y_TRUE_RECO", "h_cryoVertex_X_Y_TRUE_RECO", Vertex_Xbin_vector, Vertex_Ybin_vector , error_bands);

PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_theta_openAngle_TRUE_RECO("h_theta_openAngle_TRUE_RECO", "h_theta_openAngle_TRUE_RECO", MuonThetabin_vector, bigAngle_bins , error_bands);


PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_cryoVertex_Z_theta_TRUE_RECO("h_cryoVertex_Z_theta_TRUE_RECO", "h_cryoVertex_Z_theta_TRUE_RECO", Vertex_Zbin_vector, MuonThetabin_vector , error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_cryoVertex_R_theta_TRUE_RECO("h_cryoVertex_R_theta_TRUE_RECO", "h_cryoVertex_R_theta_TRUE_RECO", Vertex_Rbin_vector, MuonThetabin_vector , error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_cryoVertex_Z_OpenAngle_TRUE_RECO("h_cryoVertex_Z_OpenAngle_TRUE_RECO", "h_cryoVertex_Z_OpenAngle_TRUE_RECO", Vertex_Zbin_vector, bigAngle_bins , error_bands);

PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_2ndtrkangle_2ndTrkE_TRUE_RECO("h_2ndtrkangle_2ndTrkE_TRUE_RECO", "h_2ndtrkangle_2ndTrkE_TRUE_RECO",  bigAngle_bins, Vertex_secondTrkEbin_vector , error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_PT_NTracks("h_Muon_PT_NTracks", "h_Muon_PT_NTracks", PTbin_vector, TrackSize_vector, error_bands);


PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Vertex_Z_R("h_Vertex_Z_R", "h_Vertex_Z_R", Vertex_Zbin_vector, Vertex_Rbin_vector , error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Vertex_Z_X("h_Vertex_Z_X", "h_Vertex_Z_X", Vertex_Zbin_vector, VertexXYbins_coarse , error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Vertex_Z_Y("h_Vertex_Z_Y", "h_Vertex_Z_Y", Vertex_Zbin_vector, VertexXYbins_coarse , error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Vertex_X_Y("h_Vertex_X_Y", "h_Vertex_X_Y", VertexXYbins_coarse, VertexXYbins_coarse , error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Vertex_Z_ChiSq("h_Vertex_Z_ChiSq", "h_Vertex_Z_ChiSq", Vertex_Zbin_vector, Vertex_ChiSqFit_vector , error_bands);



std::vector<double> EnergyNu; //{0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0};

double edge = 0;
for(int i = 0; i < 1001; i ++ ){
  EnergyNu.push_back(edge);
  edge = edge + .1;
}


PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_RECO("h_Enu_TRUE_RECO", "h_Enu_TRUE_RECO",                EnergyNu , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_RECO_signalDiff("h_Enu_TRUE_RECO_signalDiff", "h_Enu_TRUE_RECO_signalDiff",                EnergyNu , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu("h_Enu", "h_Enu",                EnergyNu , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_RECO_Slice1("h_Enu_TRUE_RECO_Slice1", "h_Enu_TRUE_RECO_Slice1",                EnergyNu , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_RECO_Slice2("h_Enu_TRUE_RECO_Slice2", "h_Enu_TRUE_RECO_Slice2",                EnergyNu , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_RECO_Slice3("h_Enu_TRUE_RECO_Slice3", "h_Enu_TRUE_RECO_Slice3",                EnergyNu , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Enu_TRUE_RECO_Slice4("h_Enu_TRUE_RECO_Slice4", "h_Enu_TRUE_RECO_Slice4",                EnergyNu , error_bands);




PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Vertex_Z_openAngle("h_Vertex_Z_openAngle", "h_Vertex_Z_openAngle", Vertex_Zbin_vector, bigAngle_bins , error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Vertex_R_openAngle("h_Vertex_R_openAngle", "h_Vertex_R_openAngle", Vertex_Rbin_vector, bigAngle_bins , error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Vertex_X_openAngle("h_Vertex_X_openAngle", "h_Vertex_X_openAngle", VertexXYbins_coarse, bigAngle_bins , error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Vertex_Y_openAngle("h_Vertex_Y_openAngle", "h_Vertex_Y_openAngle", VertexXYbins_coarse, bigAngle_bins , error_bands);

PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Vertex_Z_DistanceNearEdge("h_Vertex_Z_DistanceNearEdge", "h_Vertex_Z_DistanceNearEdge", Vertex_Zbin_vector, distance_edge_vector , error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Vertex_R_DistanceNearEdge("h_Vertex_R_DistanceNearEdge", "h_Vertex_R_DistanceNearEdge", Vertex_Rbin_vector, distance_edge_vector , error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Vertex_X_DistanceNearEdge("h_Vertex_X_DistanceNearEdge", "h_Vertex_X_DistanceNearEdge", VertexXYbins_coarse, distance_edge_vector , error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Vertex_Y_DistanceNearEdge("h_Vertex_Y_DistanceNearEdge", "h_Vertex_Y_DistanceNearEdge", VertexXYbins_coarse, distance_edge_vector , error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Vertex_Z_MuonTheta("h_Vertex_Z_MuonTheta", "h_Vertex_Z_MuonTheta", Vertex_Zbin_vector, MuonThetabin_vector , error_bands);


PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_PT_CuratureSig("h_Muon_PT_CuratureSig", "h_Muon_PT_CuratureSig", PTbin_vector, Muon_curvatureSig_vector, error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_PZ_CuratureSig("h_Muon_PZ_CuratureSig", "h_Muon_PZ_CuratureSig", Pzbin_vector, Muon_curvatureSig_vector, error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_E_CuratureSig("h_Muon_E_CuratureSig", "h_Muon_E_CuratureSig",  Ebin_vector,    Muon_curvatureSig_vector, error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_theta_CuratureSig("h_Muon_theta_CuratureSig", "h_Muon_theta_CuratureSig",      MuonThetabin_vector , Muon_curvatureSig_vector, error_bands);

PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_secTrkE_secTrkTheta("h_secTrkE_secTrkTheta", "h_secTrkE_secTrkTheta",  Vertex_secondTrkEbin_vector , Vertex_secondTrkTheta_vector, error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Vertex_Z_secTrkTheta("h_Vertex_Z_secTrkTheta", "h_Vertex_Z_secTrkTheta", Vertex_Zbin_vector, Vertex_secondTrkTheta_vector , error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Vertex_Z_secTrkE("h_Vertex_Z_secTrkE", "h_Vertex_Z_secTrkE", Vertex_Zbin_vector, Vertex_secondTrkEbin_vector , error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Vertex_Z_trkLength("h_Vertex_Z_trkLength", "h_Vertex_Z_trkLength", Vertex_Zbin_vector, SecTrk_Tracklength_vector , error_bands);


PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_secTrkTheta_TrkLength("h_secTrkTheta_TrkLength", "h_secTrkTheta_TrkLength", Vertex_secondTrkTheta_vector, SecTrk_Tracklength_vector , error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_secTrkE_TrkLength("h_secTrkE_TrkLength", "h_secTrkE_TrkLength", Vertex_secondTrkEbin_vector , SecTrk_Tracklength_vector , error_bands);

PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_secTrkTheta_secTrkDoca("h_secTrkTheta_secTrkDoca", "h_secTrkTheta_secTrkDoca", Vertex_secondTrkTheta_vector, SecTrk_DOCA_vector , error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_secTrkE_secTrkDoca("h_secTrkE_secTrkDoca", "h_secTrkE_secTrkDoca", Vertex_secondTrkEbin_vector , SecTrk_DOCA_vector , error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_MuonDoca_secTrkDoca("h_MuonDoca_secTrkDoca", "h_MuonDoca_secTrkDoca", Vertex_DOCAbin_vector , SecTrk_DOCA_vector , error_bands);



MinervaUnfold::MnvResponse *MnvR_Vertex_Z_R = new MinervaUnfold::MnvResponse( "MnvR_Vertex_Z_R",  "MnvR_Vertex_Z_R",  Vertex_Zbin_vector,       Vertex_Rbin_vector,  error_name);
MinervaUnfold::MnvResponse *MnvR_Vertex_Z_X = new MinervaUnfold::MnvResponse( "MnvR_Vertex_Z_X",  "MnvR_Vertex_Z_X",  Vertex_Zbin_vector,       VertexXYbins_coarse,  error_name);
MinervaUnfold::MnvResponse *MnvR_Vertex_Z_Y = new MinervaUnfold::MnvResponse( "MnvR_Vertex_Z_Y",  "MnvR_Vertex_Z_Y",  Vertex_Zbin_vector,       VertexXYbins_coarse,  error_name);
MinervaUnfold::MnvResponse *MnvR_Vertex_X_Y = new MinervaUnfold::MnvResponse( "MnvR_Vertex_X_Y",  "MnvR_Vertex_X_Y",  VertexXYbins_coarse,       VertexXYbins_coarse,  error_name);



/// Mnv Response Migration constuctor
//std::map<std::string,MinervaUnfold::MnvResponse*> Response

 MinervaUnfold::MnvResponse *MnvR_Muon_PZ_PT    = new MinervaUnfold::MnvResponse( "MnvR_Muon_PZ_PT",     "MnvR_Muon_PZ_PT",     Pzbin_vector,       PTbin_vector,         error_name);
 //MinervaUnfold::MnvResponse *MnvR_Muon_PZ_PT_finebinning    = new MinervaUnfold::MnvResponse( "MnvR_Muon_PZ_PT_finebinning",     "MnvR_Muon_PZ_PT_finebinning",     Pzbin_finebinnning_vector,       PTbin_finebinnning_vector,         error_name);

 MinervaUnfold::MnvResponse *MnvR_Muon_PT_theta = new MinervaUnfold::MnvResponse( "MnvR_Muon_PT_theta",  "MnvR_Muon_PT_theta",  PTbin_vector,       MuonThetabin_vector,  error_name);
 MinervaUnfold::MnvResponse *MnvR_Muon_PZ_theta = new MinervaUnfold::MnvResponse( "MnvR_Muon_PZ_theta",  "MnvR_Muon_PZ_theta",  Pzbin_vector,       MuonThetabin_vector,  error_name);
 MinervaUnfold::MnvResponse *MnvR_Muon_E_theta  = new MinervaUnfold::MnvResponse( "MnvR_Muon_E_theta",   "MnvR_Muon_E_theta",   Ebin_vector,        MuonThetabin_vector,  error_name);
 MinervaUnfold::MnvResponse *MnvR_Muon_E_PZ     = new MinervaUnfold::MnvResponse( "MnvR_Muon_E_PZ",      "MnvR_Muon_E_PZ",      Ebin_vector,        Pzbin_vector,         error_name);
 MinervaUnfold::MnvResponse *MnvR_Muon_E_PT     = new MinervaUnfold::MnvResponse( "MnvR_Muon_E_PT",      "MnvR_Muon_E_PT",      Ebin_vector,        PTbin_vector,         error_name);
 //MinervaUnfold::MnvResponse *MnvR_cryoVertex_Z_R = new MinervaUnfold::MnvResponse("MnvR_cryoVertex_Z_R", "MnvR_cryoVertex_Z_R", Vecrtex_Zbin_vector, Vertex_Rbin_vector , error_name);

 PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_theta_openAngle("h_theta_openAngle", "h_theta_openAngle", MuonThetabin_vector, bigAngle_bins , error_bands);


std::vector<MinervaUnfold::MnvResponse*>  MnvR_vector = {
  MnvR_Muon_PZ_PT,
  MnvR_Muon_PT_theta,
  MnvR_Muon_PZ_theta,
  MnvR_Muon_E_theta,
  MnvR_Muon_E_PZ,
  MnvR_Muon_E_PT,
  MnvR_Vertex_Z_R,
  MnvR_Vertex_Z_X,
  MnvR_Vertex_Z_Y,
  MnvR_Vertex_X_Y};// , MnvR_cryoVertex_Z_R


PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type> h_Muon_PZ_PT_Material =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type>(MaterialGroup_categories, "h_Muon_PZ_PT_Material",  Pzbin_vector, PTbin_vector  ,"h_Muon_PZ_PT_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type> h_Muon_PZ_PT_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_Muon_PZ_PT_Interaction",  Pzbin_vector, PTbin_vector  ,"h_Muon_PZ_PT_Interaction; [GeV];Events");


PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type> h_Muon_PZ_PT_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type>(ParticleGroup_reduced_categories, "h_Muon_PZ_PT_Particle",  Pzbin_vector, PTbin_vector  ,"h_Muon_PZ_PT_Particle; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, OpenAngle> h_Muon_PZ_PT_OpenAngle =
PlotUtils::HistFolio<PlotUtils::MnvH2D, OpenAngle>(OpenAngle_Category, "h_Muon_PZ_PT_OpenAngle",  Pzbin_vector, PTbin_vector  ,"h_Muon_PZ_PT_OpenAngle; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type> h_Muon_PT_theta_Material =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type>(MaterialGroup_categories, "h_Muon_PT_theta_Material",  PTbin_vector , MuonThetabin_vector ,"h_Muon_PT_theta_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type> h_Muon_PT_theta_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_Muon_PT_theta_Interaction",  PTbin_vector , MuonThetabin_vector ,"h_Muon_PT_theta_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type> h_Muon_PT_theta_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type>(ParticleGroup_reduced_categories, "h_Muon_PT_theta_Particle",  PTbin_vector , MuonThetabin_vector ,"h_Muon_PT_theta_Particle; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type> h_Muon_PZ_theta_Material =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type>(MaterialGroup_categories, "h_Muon_PZ_theta_Material",  Pzbin_vector , MuonThetabin_vector ,"h_Muon_PZ_theta_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type> h_Muon_PZ_theta_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_Muon_PZ_theta_Interaction",  Pzbin_vector , MuonThetabin_vector ,"h_Muon_PZ_theta_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type> h_Muon_PZ_theta_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type>(ParticleGroup_reduced_categories, "h_Muon_PZ_theta_Particle",  Pzbin_vector , MuonThetabin_vector ,"h_Muon_PZ_theta_Particle; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type> h_Muon_E_theta_Material =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type>(MaterialGroup_categories, "h_Muon_E_theta_Material",  Ebin_vector , MuonThetabin_vector ,"E_theta_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type> h_Muon_E_theta_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_Muon_E_theta_Interaction",  Ebin_vector , MuonThetabin_vector ,"E_theta_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type> h_Muon_E_theta_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type>(ParticleGroup_reduced_categories, "h_Muon_E_theta_Particle",  Ebin_vector , MuonThetabin_vector ,"E_theta_Particle; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type> h_Muon_E_PZ_Material =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type>(MaterialGroup_categories, "h_Muon_E_PZ_Material",  Ebin_vector , Pzbin_vector ,"E_PZ_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type> h_Muon_E_PZ_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_Muon_E_PZ_Interaction",  Ebin_vector , Pzbin_vector ,"E_PZ_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type> h_Muon_E_PZ_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type>(ParticleGroup_reduced_categories, "h_Muon_E_PZ_Particle",  Ebin_vector , Pzbin_vector ,"h_Muon_E_PZ_Particle; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type> h_Muon_E_PT_Material =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type>(MaterialGroup_categories, "h_Muon_E_PT_Material",  Ebin_vector , PTbin_vector ,"E_PT_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type> h_Muon_E_PT_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_Muon_E_PT_Interaction",  Ebin_vector , PTbin_vector ,"E_PT_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type> h_Muon_E_PT_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type>(ParticleGroup_reduced_categories, "h_Muon_E_PT_Particle",  Ebin_vector , PTbin_vector ,"E_PT_Particle; [GeV];Events");


PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type> h_cryoVertex_Z_R_Material =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type>(MaterialGroup_categories, "h_cryoVertex_Z_R_Material",Vertex_Zbin_vector,  Vertex_Rbin_vector  ,"vertex_z_r_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type> h_cryoVertex_Z_R_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_cryoVertex_Z_R_Interaction",Vertex_Zbin_vector,  Vertex_Rbin_vector  ,"vertex_z_r_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type> h_cryoVertex_Z_R_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type>(ParticleGroup_reduced_categories, "h_cryoVertex_Z_R_Particle", Vertex_Zbin_vector,  Vertex_Rbin_vector  ,"h_cryoVertex_Z_R_Particle; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, OpenAngle> h_cryoVertex_Z_R_OpenAngle =
PlotUtils::HistFolio<PlotUtils::MnvH2D, OpenAngle>(OpenAngle_Category, "h_cryoVertex_Z_R_OpenAngle",Vertex_Zbin_vector,  Vertex_Rbin_vector  ,"h_cryoVertex_Z_R_OpenAngle; [GeV];Events");


PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type> h_cryoVertex_Z_X_Material =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type>(MaterialGroup_categories, "h_cryoVertex_Z_X_Material",Vertex_Zbin_vector,  VertexXYbins_coarse  ,"vertex_z_x_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type> h_cryoVertex_Z_Y_Material =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type>(MaterialGroup_categories, "h_cryoVertex_Z_Y_Material",Vertex_Zbin_vector,  VertexXYbins_coarse  ,"vertex_z_y_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type> h_cryoVertex_X_Y_Material =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type>(MaterialGroup_categories, "h_cryoVertex_X_Y_Material", VertexXYbins_coarse,  VertexXYbins_coarse  ,"vertex_x_y_Material; [mm];Events");




/////////////////////////////////////
//
/////////////////////////////////////


/////////////////////////////////////////

  //=========================================
  // Entry Loop For MC
  //=========================================
std::cout<<"Here"<<std::endl;
  ProcInfo_t procInfo;
  gSystem->GetProcInfo(&procInfo);

std::string sysmatics_status;
if(m_RunCodeWithSystematics==true){sysmatics_status= "Systematics On";}
else if (m_RunCodeWithSystematics==false){sysmatics_status= "Systematics Off";}

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;
std::cout<<"~~~~~~~~~ Systematic are =   "<< sysmatics_status <<" ~~~~~~~~~ "<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;
std::cout<<"~~~~~~~~~  THIS IS RECO 2D ~~~~~~~~~ "<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;

  std::cout << "Memory/time used so Far: " << procInfo.fMemResident/1000<< " MB" <<" time = "<<  procInfo.fCpuSys <<  " Sec"<<"\n";

  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<" Starting RECO MC LOOP  "<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;


  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<< "Playlist : "<< playlist.c_str()<< std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;


  ///////////////////////////////////////////
  ////
  //// Main Event Selection Loop
  ////
  ////
  ///////////////////////////////////////////

  for(int ii=0; ii<chw_MC->GetEntries(); ++ii){

    if(ii%1000==0) std::cout << (ii/100) << " k " << std::flush;

    //=========================================
    // For every Laterial and grouped  Vertical systematic, apply cuts ,
    // then loop over individiual  universes, and fill the
    // appropriate histogram in the MnvH1D
    //=========================================

    for (auto band : error_bands){

      std::vector<HeliumCVUniverse*> error_band_universes = band.second;
      unv_count = 0;
      for (auto universe : error_band_universes){


        universe->SetEntry(ii);
        ///////////////////////////////////////////
        ////
        ////  RECO CUTs all other Universes
        ////
        ////
        ///////////////////////////////////////////

        ///////////////////////////////////////////
        //// I apply convolution the vertex before I try to apply Fiduical cut , therefore i cut on the convoluted values
        ////
        ///////////////////////////////////////////

        double Smearing_X = vertexX_Convolution(generator);
        double Smearing_Y = vertexY_Convolution(generator);
        double Smearing_Z = vertexZ_Convolution(generator);

        if(RunwithConvolution == false){
          Smearing_X = 0.0;
          Smearing_Y = 0.0;
          Smearing_Z = 0.0;
        }


        double x = universe->GetVertex_x()  + Smearing_X;
        double y = universe->GetVertex_y()  + Smearing_Y;
        double z = universe->GetVertex_z()  + Smearing_Z;
        double r =  sqrt(x*x + y*y);



        if(PassesCutsRECO(*universe,  is_mc , kCutsVector,kWeights_v1tune, CountMap_RECO, CountMap_RECO_Helium, CountMap_RECO_nonHelium,r,z)){


             double Theta = universe->GetThetamu();
             //double Pmu =   dataEvt-> GetPmu_inhouse()/1000;
             double Theta_Degs = Theta* TMath::RadToDeg();

             double Pmu =   universe->GetPmu()*.001;
             double Emu =   universe->GetEmu()*.001;
             double phi = universe->GetPhimu();

             double px = Pmu * std::sin(Theta) * std::cos(phi);
             double py = Pmu * std::sin(Theta) * std::sin(phi);

             double PT = sqrt(px*px + py*py);
             double PZ = Pmu*std::cos(Theta);

             double mvn1wgt = universe->GetWeight(kWeights_v1tune);
             int secondTrk = universe->Getindex2ndTrackhighestKE();

             double x_true= universe->GetTRUE_Vertex_x();
             double y_true= universe->GetTRUE_Vertex_y();
             double z_true= universe->GetTRUE_Vertex_z();
             double r_true =  sqrt(x_true*x_true + y_true*y_true);


             //double z = universe->GetVertex_z();
             //double x = universe->GetVertex_x();
             //double y = universe->GetVertex_y();
             //double r = universe->GetVertex_r();


             double OpenAngle = universe->GetOpenAngle(secondTrk);
             double CurvatureSign = universe->GetCurvatureSignificance();
             double Angle2ndTrk =universe->GetNonmuTrkAngleWRTbeamMID(secondTrk);
             double Energy2ndTrk = universe->GetNonmuTrkE_GeV(secondTrk);
             double Lenght2ndTrk = universe->GetNonmuTrkLength_InMinerva_Incm(secondTrk);
             double DOCA_2ndtrk = universe->GetNonmuDOCA(secondTrk);

             //if(RunwithFid==true){
             //if(IsInFiducalVolumeFromtheInnerEdge( r, z, 50.0  )==false) continue;
             //}
             Material_type Material_type_Event = universe->Get_MaterialStackType();
             CryoTank_REGIONS CryoTankRegion_type = FourRegion_of_CryoTank(z_true);

             double Al_wgt = 1.0;
             if(useweights==true){Al_wgt *= return_AlWgt(CryoTankRegion_type, Material_type_Event);}
             mvn1wgt*=Al_wgt;

             const int  unvHist_count1 = MnvReponse_Hist_N_Map[unv_count];

             h_Muon_PZ_PT.univHist(universe)->Fill(PZ, PT, mvn1wgt);
             h_Muon_PZ_PT_finebinning.univHist(universe)->Fill(PZ, PT, mvn1wgt);
             h_Muon_PT_theta.univHist(universe)->Fill(PT, Theta_Degs,mvn1wgt);
             h_Muon_PZ_theta.univHist(universe)->Fill(PZ, Theta_Degs,mvn1wgt);
             h_Muon_E_theta.univHist(universe)->Fill(Emu,Theta_Degs , mvn1wgt);
             h_Muon_E_PZ.univHist(universe)->Fill(Emu, PZ, mvn1wgt);
             h_Muon_E_PT.univHist(universe)->Fill(Emu, PT, mvn1wgt);
             h_cryoVertex_Z_R.univHist(universe)->Fill(z,r , mvn1wgt);
             h_Muon_PT_cryoVertex_R.univHist(universe)->Fill(PT,r , mvn1wgt);
             h_Vertex_Z_R.univHist(universe)->Fill(z,r , mvn1wgt);
             h_Vertex_Z_X.univHist(universe)->Fill(z,x , mvn1wgt);
             h_Vertex_Z_Y.univHist(universe)->Fill(z,y , mvn1wgt);
             h_Vertex_X_Y.univHist(universe)->Fill(x,y , mvn1wgt);

             h_Vertex_Z_openAngle.univHist(universe)->Fill(z,OpenAngle , mvn1wgt);
             h_Vertex_R_openAngle.univHist(universe)->Fill(r,OpenAngle , mvn1wgt);
             h_Vertex_X_openAngle.univHist(universe)->Fill(x,OpenAngle , mvn1wgt);
             h_Vertex_Y_openAngle.univHist(universe)->Fill(y,OpenAngle , mvn1wgt);
             h_theta_openAngle.univHist(universe)->Fill(Theta_Degs,OpenAngle , mvn1wgt);

             h_Muon_PT_NTracks.univHist(universe)->Fill(PT, universe->GetTracksize(),mvn1wgt);

             h_Vertex_Z_ChiSq.univHist(universe)->Fill(z, universe->GetVertexChiSqrFit(),mvn1wgt);

             MnvR_Vertex_Z_R->Fill(z,r, z_true,r_true,universe->ShortName(),unvHist_count1,mvn1wgt);
             MnvR_Vertex_Z_X->Fill(z,x, z_true,x_true,universe->ShortName(),unvHist_count1,mvn1wgt);
             MnvR_Vertex_Z_Y->Fill(z,y, z_true,y_true,universe->ShortName(),unvHist_count1,mvn1wgt);
             MnvR_Vertex_X_Y->Fill(x,y, x_true,y_true,universe->ShortName(),unvHist_count1,mvn1wgt);


             h_Vertex_Z_MuonTheta.univHist(universe)->Fill(z, Theta_Degs,mvn1wgt);
             h_Muon_PT_CuratureSig.univHist(universe)->Fill(PT, CurvatureSign,mvn1wgt);
             h_Muon_PZ_CuratureSig.univHist(universe)->Fill(PZ, CurvatureSign,mvn1wgt);
             h_Muon_E_CuratureSig.univHist(universe)->Fill(Emu, CurvatureSign,mvn1wgt);
             h_Muon_theta_CuratureSig.univHist(universe)->Fill(Theta_Degs, CurvatureSign,mvn1wgt);
             h_secTrkE_secTrkTheta.univHist(universe)->Fill(Energy2ndTrk, Angle2ndTrk,mvn1wgt);
             h_Vertex_Z_secTrkTheta.univHist(universe)->Fill(z, Angle2ndTrk,mvn1wgt);
             h_Vertex_Z_secTrkE.univHist(universe)->Fill(z, Energy2ndTrk,mvn1wgt);
             h_Vertex_Z_trkLength.univHist(universe)->Fill(z, Lenght2ndTrk,mvn1wgt);
             h_secTrkTheta_TrkLength.univHist(universe)->Fill(Angle2ndTrk, Lenght2ndTrk,mvn1wgt);
             h_secTrkE_TrkLength.univHist(universe)->Fill(Energy2ndTrk, Lenght2ndTrk,mvn1wgt);
             h_secTrkTheta_secTrkDoca.univHist(universe)->Fill( Angle2ndTrk,DOCA_2ndtrk ,mvn1wgt);
             h_secTrkE_secTrkDoca.univHist(universe)->Fill(Energy2ndTrk,DOCA_2ndtrk ,mvn1wgt);
             h_MuonDoca_secTrkDoca.univHist(universe)->Fill(universe->GetDOCAmu(), DOCA_2ndtrk ,mvn1wgt);
             h_Enu.univHist(universe)->Fill(universe->GetEnuTrue()*.001 ,mvn1wgt);
             //double Reco_distance = RECO_Distance_to_innerTank(*universe);

              double Reco_distance = RECO_Distance_to_innerTank(r,z  );

             h_Vertex_Z_DistanceNearEdge.univHist(universe)->Fill(z, Reco_distance,mvn1wgt);
             h_Vertex_R_DistanceNearEdge.univHist(universe)->Fill(r, Reco_distance,mvn1wgt);
             h_Vertex_X_DistanceNearEdge.univHist(universe)->Fill(x, Reco_distance,mvn1wgt);
             h_Vertex_Y_DistanceNearEdge.univHist(universe)->Fill(y, Reco_distance,mvn1wgt);

             if(Material_type_Event != kHelium){
               h_Muon_PZ_PT_BG.univHist(universe)->Fill(PZ, PT, mvn1wgt);
               h_Muon_E_theta_BG.univHist(universe)->Fill(Emu,Theta_Degs , mvn1wgt);

             }

             ///////////////////////////////////////////
             ////
             ////  FILL CV
             ////
             ////
             ///////////////////////////////////////////

             if( isCV(*universe)){


               Interaction_type Interaction_type_Event =  universe->Get_Interaction_withDISbreakdown();
               Material_type Material_type_Event = universe->Get_MaterialStackType();
              // Particle_type Particle_type_Event =  universe->Get_NonParticleStackType(secondTrk);
                auto PDG_trklist = universe->GetVector_nonMuonTk_PDG_Parent();
              Particle_type Particle_type_Event = GetParticlegroup_typeReduced(PDG_trklist.at(secondTrk));
              auto angletype = OpenAngleType(OpenAngle);

               h_Muon_PZ_PT_Material.GetComponentHist(Material_type_Event)->Fill(PZ, PT, mvn1wgt);
               h_Muon_PZ_PT_Interaction.GetComponentHist(Interaction_type_Event)->Fill(PZ, PT, mvn1wgt);
               h_Muon_PZ_PT_Particle.GetComponentHist(Particle_type_Event)->Fill(PZ, PT, mvn1wgt);
               h_Muon_PZ_PT_OpenAngle.GetComponentHist(angletype)->Fill(PZ, PT, mvn1wgt);
               h_Muon_PT_theta_Material.GetComponentHist(Material_type_Event)->Fill(PT, Theta_Degs,mvn1wgt);
               h_Muon_PT_theta_Interaction.GetComponentHist(Interaction_type_Event)->Fill(PT, Theta_Degs,mvn1wgt);
               h_Muon_PT_theta_Particle.GetComponentHist(Particle_type_Event)->Fill(PT, Theta_Degs,mvn1wgt);

               h_Muon_PZ_theta_Material.GetComponentHist(Material_type_Event)->Fill(PZ, Theta_Degs,mvn1wgt);
               h_Muon_PZ_theta_Interaction.GetComponentHist(Interaction_type_Event)->Fill(PZ, Theta_Degs,mvn1wgt);
               h_Muon_PZ_theta_Particle.GetComponentHist(Particle_type_Event)->Fill(PZ, Theta_Degs,mvn1wgt);

               h_Muon_E_theta_Material.GetComponentHist(Material_type_Event)->Fill(Emu,Theta_Degs,mvn1wgt);
               h_Muon_E_theta_Interaction.GetComponentHist(Interaction_type_Event)->Fill(Emu,Theta_Degs,mvn1wgt);
               h_Muon_E_theta_Particle.GetComponentHist(Particle_type_Event)->Fill(Emu,Theta_Degs,mvn1wgt);

               h_Muon_E_PZ_Material.GetComponentHist(Material_type_Event)->Fill(Emu, PZ,mvn1wgt);
               h_Muon_E_PZ_Interaction.GetComponentHist(Interaction_type_Event)->Fill(Emu, PZ,mvn1wgt);
               h_Muon_E_PZ_Particle.GetComponentHist(Particle_type_Event)->Fill(Emu, PZ,mvn1wgt);

               h_Muon_E_PT_Material.GetComponentHist(Material_type_Event)->Fill(Emu, PT,mvn1wgt);
               h_Muon_E_PT_Interaction.GetComponentHist(Interaction_type_Event)->Fill(Emu, PT,mvn1wgt);
               h_Muon_E_PT_Particle.GetComponentHist(Particle_type_Event)->Fill(Emu, PT,mvn1wgt);

               h_cryoVertex_Z_R_Material.GetComponentHist(Material_type_Event)->Fill(z,r, mvn1wgt);
               h_cryoVertex_Z_R_Interaction.GetComponentHist(Interaction_type_Event)->Fill(z,r, mvn1wgt);
               h_cryoVertex_Z_R_Particle.GetComponentHist(Particle_type_Event)->Fill(z,r, mvn1wgt);
               h_cryoVertex_Z_R_OpenAngle.GetComponentHist(angletype)->Fill(z,r, mvn1wgt);

               h_cryoVertex_Z_X_Material.GetComponentHist(Material_type_Event)->Fill(z,x, mvn1wgt);
               h_cryoVertex_Z_Y_Material.GetComponentHist(Material_type_Event)->Fill(z,y, mvn1wgt);
               h_cryoVertex_X_Y_Material.GetComponentHist(Material_type_Event)->Fill(x,y, mvn1wgt);

             }//
             ///////////////////////////////////////////
             ////
             ////  END CV
             ////
             ////
             ///////////////////////////////////////////



           }// End RECO Cuts
           ///////////////////////////////////////////
           ////
           ////  Apply TRUTH + RECO CUTS to each universe
           ////
           ///////////////////////////////////////////
           if(PassesCutsTRUTH(*universe, kTRUTHCutsVector, kWeights_v1tune , Truth_Cut_Map)){

//           double Smearing_X = vertexX_Convolution(generator);
//           double Smearing_Y = vertexY_Convolution(generator);
//           double Smearing_Z = vertexZ_Convolution(generator);
//
//           if(RunwithConvolution == false){
//             Smearing_X = 0.0;
//             Smearing_Y = 0.0;
//             Smearing_Z = 0.0;
//           }
//
//           double x = universe->GetVertex_x() + Smearing_X;
//           double y = universe->GetVertex_y() + Smearing_Y;
//           double z = universe->GetVertex_z() + Smearing_Z;
//           double r =  sqrt(x*x + y*y);

          if(PassesCutsRECO(*universe,  is_mc , kCutsVector_Eff ,kWeights_v1tune ,CountMap_TRUE_RECO,r,z ) ){

          //std::cout<<"universe->ShortName() = " << universe->ShortName()<<std::endl;
          // Tell the Event which entry in the TChain it's looking at
          double Emu_TRUE = universe->GetTRUE_Emu(); // GeV
          double Theta_TRUE = universe->GetThetalepTrue(); // Rad
          double phi_TRUE = universe->GetPhilepTrue(); // Rad
          double Theta_Degs_TRUE = Theta_TRUE* TMath::RadToDeg();
          double Pmu_TRUE = universe->GetTRUE_Pmu(); // GeV
          double px_TRUE = Pmu_TRUE * std::sin(Theta_TRUE) * std::cos(phi_TRUE);
          double py_TRUE = Pmu_TRUE * std::sin(Theta_TRUE) * std::sin(phi_TRUE);

          //double MuonPT_TRUE = sqrt(px_TRUE*px_TRUE + py_TRUE*py_TRUE);
          //double MuonPZ_TRUE = Pmu_TRUE*std::cos(Theta_TRUE);

          double MuonPZ_TRUE = universe->GetPmuLongitudinalTrue(); //GeV
          double MuonPT_TRUE = universe->GetPmuTransverseTrue(); // GeV

          double PhiMuonAngle_TRUE = phi_TRUE * TMath::RadToDeg();

          double Theta = universe->GetThetamu();
          //double Pmu =   dataEvt-> GetPmu_inhouse()/1000;
          double Theta_Degs = Theta* TMath::RadToDeg();

          double Pmu =   universe->GetPmu()*.001;
          double Emu =   universe->GetEmu()*.001;
          double phi = universe->GetPhimu();

          double px = Pmu * std::sin(Theta) * std::cos(phi);
          double py = Pmu * std::sin(Theta) * std::sin(phi);

          double PT = sqrt(px*px + py*py);
          double PZ = Pmu*std::cos(Theta);

          double ztrue = universe->GetTRUE_Vertex_z();
          double xtrue = universe->GetTRUE_Vertex_x();
          double ytrue = universe->GetTRUE_Vertex_y();
          double rtrue = universe->GetTRUE_Vertex_r();


          double mvn1wgt = universe->GetWeight(kWeights_v1tune);

          Material_type Material_type_Event = universe->Get_MaterialStackType();
          CryoTank_REGIONS CryoTankRegion_type = FourRegion_of_CryoTank(ztrue);


          double Al_wgt = 1.0;
          if(useweights==true){Al_wgt *= return_AlWgt(CryoTankRegion_type, Material_type_Event);}
          mvn1wgt*=Al_wgt;


          auto PDG_trklist = universe->GetVector_nonMuonTk_PDG_Parent();
          auto Energy_trklist = universe-> GetVector_nonMuonTk_Energy_GeV_Parent();
          auto Angle_trklist = universe->GetVector_nonMuonTk_Angle_wrtb_Degs_Parent();
          auto EnergyFraction_vector = universe->Get_TrueFractionE_vector();
          int secondTrk = universe->Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_lessthanAngle_muonNotinlist(PDG_trklist, Energy_trklist, Angle_trklist, EnergyFraction_vector);
          double TrueOpenAngle = universe->GetTRUE_NonmuTrkopenangle(secondTrk);
          if(secondTrk==-999|| secondTrk==-9999 )continue;


          int secTrk_PDG = PDG_trklist.at(secondTrk);
          double secTrkAngle  = Angle_trklist.at(secondTrk);
          double secTrkKE = Energy_trklist.at(secondTrk);



          h_Muon_PZ_PT_TRUE_RECO.univHist(universe)->Fill(MuonPZ_TRUE, MuonPT_TRUE, mvn1wgt);
          h_Muon_PT_theta_TRUE_RECO.univHist(universe)->Fill(MuonPT_TRUE, Theta_Degs_TRUE,mvn1wgt);
          h_Muon_PZ_theta_TRUE_RECO.univHist(universe)->Fill( MuonPZ_TRUE, Theta_Degs_TRUE,mvn1wgt);
          h_Muon_E_theta_TRUE_RECO.univHist(universe)->Fill(Emu_TRUE,Theta_Degs_TRUE , mvn1wgt);
          h_Muon_E_PZ_TRUE_RECO.univHist(universe)->Fill(Emu_TRUE, MuonPZ_TRUE, mvn1wgt);
          h_Muon_E_PT_TRUE_RECO.univHist(universe)->Fill(Emu_TRUE, MuonPT_TRUE, mvn1wgt);
          h_cryoVertex_Z_theta_TRUE_RECO.univHist(universe)->Fill(ztrue, Theta_Degs_TRUE, mvn1wgt);
          h_cryoVertex_R_theta_TRUE_RECO.univHist(universe)->Fill(rtrue, Theta_Degs_TRUE, mvn1wgt);
          h_cryoVertex_Z_R_TRUE_RECO.univHist(universe)->Fill(ztrue,rtrue , mvn1wgt);
          h_theta_openAngle_TRUE_RECO.univHist(universe)->Fill(Theta_Degs_TRUE,TrueOpenAngle , mvn1wgt);
          h_cryoVertex_Z_X_TRUE_RECO.univHist(universe)->Fill(ztrue,xtrue , mvn1wgt);
          h_cryoVertex_Z_Y_TRUE_RECO.univHist(universe)->Fill(ztrue,ytrue , mvn1wgt);
          h_cryoVertex_X_Y_TRUE_RECO.univHist(universe)->Fill(xtrue,ytrue , mvn1wgt);
          h_cryoVertex_Z_OpenAngle_TRUE_RECO.univHist(universe)->Fill(ztrue,TrueOpenAngle , mvn1wgt);
          h_Enu_TRUE_RECO_signalDiff.univHist(universe)->Fill(universe->GetEnuTrue()*.001, mvn1wgt);
          h_2ndtrkangle_2ndTrkE_TRUE_RECO.univHist(universe)->Fill(secTrkAngle, secTrkKE, mvn1wgt);
          //h_2ndtrkangle_openAngle_TRUE_RECO.univHist(universe)->Fill(MuonPZ_TRUE, Theta_Degs_TRUE, mvn1wgt);
          const int  unvHist_count = MnvReponse_Hist_N_Map[unv_count];
        //  std::cout<<"universe->ShortName() = "<< universe->ShortName()<< "unvHist_count = "<< unvHist_count<<"unv_count = "<< unv_count<<std::endl;
        //  std::cout<< <<std::endl;
        //  std::cout<<"unv_count = "<< unv_count<<std::endl;
          MnvR_Muon_PZ_PT->Fill(PZ, PT, MuonPZ_TRUE, MuonPT_TRUE, universe->ShortName(),unvHist_count,mvn1wgt);
          MnvR_Muon_PT_theta->Fill(PT,Theta_Degs, MuonPT_TRUE,Theta_Degs_TRUE,universe->ShortName(),unvHist_count,mvn1wgt);
          MnvR_Muon_PZ_theta->Fill(PZ,Theta_Degs,MuonPZ_TRUE,Theta_Degs_TRUE,universe->ShortName(),unvHist_count,mvn1wgt);
          MnvR_Muon_E_theta->Fill(Emu, Theta_Degs, Emu_TRUE, Theta_Degs_TRUE,universe->ShortName(),unvHist_count,mvn1wgt);
          MnvR_Muon_E_PZ->Fill(Emu,PZ,Emu_TRUE ,MuonPZ_TRUE,universe->ShortName(),unvHist_count,mvn1wgt);
          MnvR_Muon_E_PT->Fill(Emu,PT,Emu_TRUE ,MuonPT_TRUE,universe->ShortName(),unvHist_count,mvn1wgt);
          //MnvR_cryoVertex_Z_R->Fill(universe->GetVertex_z(), universe->GetVertex_r(),universe->GetTRUE_Vertex_z(),universe->GetTRUE_Vertex_r() ,universe->ShortName(), unvHist_count, mvn1wgt);


        } // End of RECO CUTs
      }// End of TRUTH CUTS





if(universe->Get_mc_incoming()==14){
  if(universe->Get_mc_current()==1){
    if (universe->isHeliumInteraction()){
      double mvn1wgt = universe->GetWeight(kWeights_v1tune);
      h_Enu_TRUE_RECO.univHist(universe)->Fill(universe->GetEnuTrue()*.001,mvn1wgt);

      auto Slicetype = universe->GetTRUERegionSliceHelium();
      if (Slicetype==kSlice1){h_Enu_TRUE_RECO_Slice1.univHist(universe)->Fill(universe->GetEnuTrue()*.001,mvn1wgt);}
      else if (Slicetype==kSlice2) {h_Enu_TRUE_RECO_Slice2.univHist(universe)->Fill(universe->GetEnuTrue()*.001,mvn1wgt);}
      else if (Slicetype==kSlice3) {h_Enu_TRUE_RECO_Slice3.univHist(universe)->Fill(universe->GetEnuTrue()*.001,mvn1wgt);}
      else if (Slicetype==kSlice4) {h_Enu_TRUE_RECO_Slice4.univHist(universe)->Fill(universe->GetEnuTrue()*.001,mvn1wgt);}







    }
  }
}


      unv_count++;
    }// End of Universe

  }// End of Band
  ///////////////////////////////////////////
////
////  GROUPED Vertical and Laterialuniverse loop
////
///////////////////////////////////////////
} //End entries loop
///////////////////////////////////////////
////
////  End entries loop
////
///////////////////////////////////////////




  gSystem->GetProcInfo(&procInfo);
  std::cout << " Done with loop Mem1: " << procInfo.fMemResident/1000 << " MB" << " time = "<<  procInfo.fCpuSys  <<  " sec""\n";
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//End of Empty data
//////////////////////////////////////////////////////////////////////////


double countdata= 0.0;
double countmc= 0.0;

h_Muon_PZ_PT.SyncCVHistos();
h_Muon_PZ_PT_BG.SyncCVHistos();
h_Muon_PZ_PT_finebinning.SyncCVHistos();
h_Muon_PT_theta.SyncCVHistos();
h_Muon_PZ_theta.SyncCVHistos();
h_Muon_E_theta.SyncCVHistos();
h_Muon_E_theta_BG.SyncCVHistos();
h_Muon_E_PZ.SyncCVHistos();
h_Muon_E_PT.SyncCVHistos();
h_cryoVertex_Z_R.SyncCVHistos();
h_Muon_PT_cryoVertex_R.SyncCVHistos();
h_Vertex_Z_R.SyncCVHistos();
h_Vertex_Z_X.SyncCVHistos();
h_Vertex_Z_Y.SyncCVHistos();
h_Vertex_X_Y.SyncCVHistos();
h_Vertex_Z_openAngle.SyncCVHistos();
h_Vertex_R_openAngle.SyncCVHistos();
h_Vertex_X_openAngle.SyncCVHistos();
h_Vertex_Y_openAngle.SyncCVHistos();
h_theta_openAngle.SyncCVHistos();
h_Muon_PZ_PT_TRUE_RECO.SyncCVHistos();
h_Muon_PT_theta_TRUE_RECO.SyncCVHistos();
h_Muon_PZ_theta_TRUE_RECO.SyncCVHistos();
h_Muon_E_theta_TRUE_RECO.SyncCVHistos();
h_Muon_E_PZ_TRUE_RECO.SyncCVHistos();
h_Muon_E_PT_TRUE_RECO.SyncCVHistos();
h_cryoVertex_Z_R_TRUE_RECO.SyncCVHistos();
h_theta_openAngle_TRUE_RECO.SyncCVHistos();
h_cryoVertex_Z_theta_TRUE_RECO.SyncCVHistos();
h_cryoVertex_R_theta_TRUE_RECO.SyncCVHistos();
h_cryoVertex_Z_X_TRUE_RECO.SyncCVHistos();
h_cryoVertex_Z_Y_TRUE_RECO.SyncCVHistos();
h_cryoVertex_X_Y_TRUE_RECO.SyncCVHistos();
h_cryoVertex_Z_OpenAngle_TRUE_RECO.SyncCVHistos();
h_2ndtrkangle_2ndTrkE_TRUE_RECO.SyncCVHistos();
h_Muon_PT_NTracks.SyncCVHistos();
h_Vertex_Z_ChiSq.SyncCVHistos();
h_Vertex_Z_MuonTheta.SyncCVHistos();
h_Muon_PT_CuratureSig.SyncCVHistos();
h_Muon_PZ_CuratureSig.SyncCVHistos();
h_Muon_E_CuratureSig.SyncCVHistos();
h_Muon_theta_CuratureSig.SyncCVHistos();
h_secTrkE_secTrkTheta.SyncCVHistos();
h_Vertex_Z_secTrkTheta.SyncCVHistos();
h_Vertex_Z_secTrkE.SyncCVHistos();
h_Vertex_Z_trkLength.SyncCVHistos();
h_secTrkTheta_TrkLength.SyncCVHistos();
h_secTrkE_TrkLength.SyncCVHistos();
h_secTrkTheta_secTrkDoca.SyncCVHistos();
h_secTrkE_secTrkDoca.SyncCVHistos();
h_MuonDoca_secTrkDoca.SyncCVHistos();
h_Vertex_Z_DistanceNearEdge.SyncCVHistos();
h_Vertex_R_DistanceNearEdge.SyncCVHistos();
h_Vertex_X_DistanceNearEdge.SyncCVHistos();
h_Vertex_Y_DistanceNearEdge.SyncCVHistos();
h_Enu_TRUE_RECO.SyncCVHistos();
h_Enu_TRUE_RECO_signalDiff.SyncCVHistos();
h_Enu.SyncCVHistos();
h_Enu_TRUE_RECO_Slice1.SyncCVHistos();
h_Enu_TRUE_RECO_Slice2.SyncCVHistos();
h_Enu_TRUE_RECO_Slice3.SyncCVHistos();
h_Enu_TRUE_RECO_Slice4.SyncCVHistos();
//////////////////////////////////

  //=========================================
  // Plot stuff
  //=========================================

  // DrawMCWithErrorBand
//  PlotCVAndError(Muon_PZ_FULLMC.hist, "TEST");
std::string systematics_status;

if(m_RunCodeWithSystematics==true){sysmatics_status= "All_SysErrorsOn";}
else if (m_RunCodeWithSystematics==false){sysmatics_status= "StatsONLYErrors";}
std::string convolution_status;

if(RunwithConvolution==true){convolution_status= "ConvolutionApp";}
else if (RunwithConvolution==false){convolution_status= "";}

std::string weight_status;

if(useweights==true){weight_status= "wgtApp";}
else if (useweights==false){weight_status= "";}

std::string Fid_status;
if(FidOn==true){Fid_status= "";}
else if (FidOn==false){Fid_status= "no";}



  char outFileName[1024];
  char outFileName_pdf[1024];
  auto playlist_name = Playlist_Info.GetPlaylistname();
  char c[playlist_name.length() + 1];
  char rootpathway[OUTputRoot_pathway.length()+1];
  char ErrorStatus[sysmatics_status.length()+1];
  char Fid_status_char[Fid_status.length()+1];
  char weight_status_char[weight_status.length()+1];
  char Convolution_status_char[convolution_status.length()+1];


  strcpy(rootpathway, OUTputRoot_pathway.c_str());
  strcpy(c, playlist_name.c_str());
  strcpy(ErrorStatus, sysmatics_status.c_str());
  strcpy(Fid_status_char, Fid_status.c_str());
  strcpy(weight_status_char, weight_status.c_str());
  strcpy(Convolution_status_char, convolution_status.c_str());




  TGraph  *RECO_2DCuts           = Make_RECOCut_Tgraph_fromCutMap("RECO_2DCuts"          , CountMap_RECO);
  TGraph  *RECO_Helium_2DCuts    = Make_RECOCut_Tgraph_fromCutMap("RECO_Helium_2DCuts"   , CountMap_RECO_Helium);
  TGraph  *RECO_nonHelium_2DCuts = Make_RECOCut_Tgraph_fromCutMap("RECO_nonHelium_2DCuts", CountMap_RECO);
  TGraph  *TRUE_RECO_2DCuts      = Make_RECOCut_Tgraph_fromCutMap("TRUE_RECO_2DCuts"     , CountMap_TRUE_RECO);
  TGraph  *Truth_2DCuts          = Make_TruthCut_Tgraph_fromCutMap("Truth_2DCuts"        , Truth_Cut_Map);


if(RunwithConvolution==true && useweights==true){
  sprintf(outFileName, "%s/%s_2D%s_%s_%s_%s_%s_%sFid.root", rootpathway, "Histograms", c, "RECO_MC", ErrorStatus,Convolution_status_char, weight_status_char, Fid_status_char);
  sprintf(outFileName_pdf, "%s_2D%s_%s_%s_%s_%s_%sFid.pdf", "Histograms", c, "RECO_MC", ErrorStatus,Convolution_status_char, weight_status_char, Fid_status_char);
}

else if(RunwithConvolution==true && useweights==false){
  sprintf(outFileName, "%s/%s_2D%s_%s_%s_%s_%sFid.root", rootpathway, "Histograms", c, "RECO_MC", ErrorStatus,Convolution_status_char, Fid_status_char);
  sprintf(outFileName_pdf, "%s_2D%s_%s_%s_%s_%sFid.pdf", "Histograms", c, "RECO_MC", ErrorStatus,Convolution_status_char, Fid_status_char);

}
else {  sprintf(outFileName, "%s/%s_2D%s_%s_%s_%sFid.root", rootpathway, "Histograms", c, "RECO_MC", ErrorStatus, Fid_status_char);
sprintf(outFileName_pdf, "%s_2D%s_%s_%s_%s_%sFid.pdf",  "Histograms", c, "RECO_MC", ErrorStatus,Convolution_status_char, Fid_status_char);

}

  std::cout << "Writing output file to: " <<outFileName << std::endl;

  TFile *outFile = new TFile(outFileName,"RECREATE");

  TChain POT_branch("Meta");
  POT_branch.Add(RootName.c_str());
  //TTree *oldtree = (TTree*)file->Get("Meta");
  TTree *clone = POT_branch.CloneTree();
  clone->Write();
  //////////////
  /// Cut rates
  ///////////////

  RECO_2DCuts->Write();
  TRUE_RECO_2DCuts->Write();
  RECO_Helium_2DCuts->Write();
  RECO_nonHelium_2DCuts->Write();
  Truth_2DCuts->Write();

  h_Muon_PZ_PT.hist->Write();
  h_Muon_PZ_PT_BG.hist->Write();
  h_Muon_PZ_PT_finebinning.hist->Write();
  PlotUtils::MnvH2D* h_Muon_PZ_PT_FluxIntegrated = PlotUtils::flux_reweighter(playlist_fluxreweighter, nu_pdg, useNuEconstraint, NFlux_universe).GetIntegratedFluxReweighted(nu_pdg, h_Muon_PZ_PT.hist, Min_NuFluxEnergy, Max_NuFluxEnergy, useMuonCorrelations);
  h_Muon_PZ_PT_FluxIntegrated->Clone()->Write("h_Muon_PZ_PT_FluxIntegrated");
  h_Muon_PT_theta.hist->Write();

  PlotUtils::MnvH2D* h_Muon_PT_theta_FluxIntegrated = PlotUtils::flux_reweighter(playlist_fluxreweighter, nu_pdg, useNuEconstraint, NFlux_universe).GetIntegratedFluxReweighted(nu_pdg, h_Muon_PT_theta.hist, Min_NuFluxEnergy, Max_NuFluxEnergy, useMuonCorrelations);
  h_Muon_PT_theta_FluxIntegrated->Clone()->Write("h_Muon_PT_theta_FluxIntegrated");
  h_Muon_PZ_theta.hist->Write();

  PlotUtils::MnvH2D* h_Muon_PZ_theta_FluxIntegrated = PlotUtils::flux_reweighter(playlist_fluxreweighter, nu_pdg, useNuEconstraint, NFlux_universe).GetIntegratedFluxReweighted(nu_pdg, h_Muon_PZ_theta.hist, Min_NuFluxEnergy, Max_NuFluxEnergy, useMuonCorrelations);
  h_Muon_PZ_theta_FluxIntegrated->Clone()->Write("h_Muon_PZ_theta_FluxIntegrated");

  h_Muon_E_theta.hist->Write();
  h_Muon_E_theta_BG.hist->Write();
  PlotUtils::MnvH2D* h_Muon_E_theta_FluxIntegrated = PlotUtils::flux_reweighter(playlist_fluxreweighter, nu_pdg, useNuEconstraint, NFlux_universe).GetIntegratedFluxReweighted(nu_pdg, h_Muon_E_theta.hist, Min_NuFluxEnergy, Max_NuFluxEnergy, useMuonCorrelations);
  h_Muon_E_theta_FluxIntegrated->Clone()->Write("h_Muon_E_theta_FluxIntegrated");

  h_Muon_E_PZ.hist->Write();
  PlotUtils::MnvH2D* h_Muon_E_PZ_FluxIntegrated = PlotUtils::flux_reweighter(playlist_fluxreweighter, nu_pdg, useNuEconstraint, NFlux_universe).GetIntegratedFluxReweighted(nu_pdg, h_Muon_E_PZ.hist, Min_NuFluxEnergy, Max_NuFluxEnergy, useMuonCorrelations);
  h_Muon_E_PZ_FluxIntegrated->Clone()->Write("h_Muon_E_PZ_FluxIntegrated");

  h_Muon_E_PT.hist->Write();
  PlotUtils::MnvH2D* h_Muon_E_PT_FluxIntegrated = PlotUtils::flux_reweighter(playlist_fluxreweighter, nu_pdg, useNuEconstraint, NFlux_universe).GetIntegratedFluxReweighted(nu_pdg, h_Muon_E_PT.hist, Min_NuFluxEnergy, Max_NuFluxEnergy, useMuonCorrelations);
  h_Muon_E_PT_FluxIntegrated->Clone()->Write("h_Muon_E_PT_FluxIntegrated");

  h_cryoVertex_Z_R.hist->Write();
  PlotUtils::MnvH2D* h_cryoVertex_Z_R_FluxIntegrated = PlotUtils::flux_reweighter(playlist_fluxreweighter, nu_pdg, useNuEconstraint, NFlux_universe).GetIntegratedFluxReweighted(nu_pdg, h_cryoVertex_Z_R.hist, Min_NuFluxEnergy, Max_NuFluxEnergy, useMuonCorrelations);
  h_cryoVertex_Z_R_FluxIntegrated->Clone()->Write("h_cryoVertex_Z_R_FluxIntegrated");

  h_Muon_PT_cryoVertex_R.hist->Write();
  h_Vertex_Z_R.hist->Write();
  h_Vertex_Z_X.hist->Write();
  h_Vertex_Z_Y.hist->Write();
  h_Vertex_X_Y.hist->Write();

  h_Vertex_Z_openAngle.hist->Write();
  h_Vertex_R_openAngle.hist->Write();
  h_Vertex_X_openAngle.hist->Write();
  h_Vertex_Y_openAngle.hist->Write();
  h_theta_openAngle.hist->Write();
  h_Muon_PT_NTracks.hist->Write();
  h_Vertex_Z_ChiSq.hist->Write();
  h_Muon_PZ_PT_TRUE_RECO.hist->Write();
  h_Muon_PT_theta_TRUE_RECO.hist->Write();
  h_Muon_PZ_theta_TRUE_RECO.hist->Write();
  h_Muon_E_theta_TRUE_RECO.hist->Write();
  h_Muon_E_PZ_TRUE_RECO.hist->Write();
  h_Muon_E_PT_TRUE_RECO.hist->Write();
  h_cryoVertex_Z_R_TRUE_RECO.hist->Write();
  h_theta_openAngle_TRUE_RECO.hist->Write();
  h_cryoVertex_Z_theta_TRUE_RECO.hist->Write();

  h_cryoVertex_R_theta_TRUE_RECO.hist->Write();
  h_cryoVertex_Z_X_TRUE_RECO.hist->Write();
  h_cryoVertex_Z_Y_TRUE_RECO.hist->Write();
  h_cryoVertex_X_Y_TRUE_RECO.hist->Write();
  h_Enu_TRUE_RECO.hist->Write();
  h_Enu_TRUE_RECO_signalDiff.hist->Write();
  h_Enu_TRUE_RECO_Slice1.hist->Write();
  h_Enu_TRUE_RECO_Slice2.hist->Write();
  h_Enu_TRUE_RECO_Slice3.hist->Write();
  h_Enu_TRUE_RECO_Slice4.hist->Write();

  h_Enu.hist->Write();
  h_cryoVertex_Z_OpenAngle_TRUE_RECO.hist->Write();
  h_2ndtrkangle_2ndTrkE_TRUE_RECO.hist->Write();
  h_Vertex_Z_MuonTheta.hist->Write();
  h_Muon_PT_CuratureSig.hist->Write();
  h_Muon_PZ_CuratureSig.hist->Write();
  h_Muon_E_CuratureSig.hist->Write();
  h_Muon_theta_CuratureSig.hist->Write();
  h_secTrkE_secTrkTheta.hist->Write();
  h_Vertex_Z_secTrkTheta.hist->Write();
  h_Vertex_Z_secTrkE.hist->Write();
  h_Vertex_Z_trkLength.hist->Write();
  h_secTrkTheta_TrkLength.hist->Write();
  h_secTrkE_TrkLength.hist->Write();
  h_secTrkTheta_secTrkDoca.hist->Write();
  h_secTrkE_secTrkDoca.hist->Write();
  h_MuonDoca_secTrkDoca.hist->Write();
  h_Vertex_Z_DistanceNearEdge.hist->Write();
  h_Vertex_R_DistanceNearEdge.hist->Write();
  h_Vertex_X_DistanceNearEdge.hist->Write();
  h_Vertex_Y_DistanceNearEdge.hist->Write();
  h_Muon_PZ_PT_OpenAngle.WriteToFile(*outFile);
  h_Muon_PZ_PT_Material.WriteToFile(*outFile);
  h_Muon_PZ_PT_Interaction.WriteToFile(*outFile);
  h_Muon_PZ_PT_Particle.WriteToFile(*outFile);
  h_cryoVertex_Z_R_Particle.WriteToFile(*outFile);
  h_Muon_PT_theta_Material.WriteToFile(*outFile);
  h_Muon_PT_theta_Interaction.WriteToFile(*outFile);
  h_Muon_PT_theta_Particle.WriteToFile(*outFile);
  h_Muon_PZ_theta_Material.WriteToFile(*outFile);
  h_Muon_PZ_theta_Interaction.WriteToFile(*outFile);
  h_Muon_PZ_theta_Particle.WriteToFile(*outFile);
  h_Muon_E_theta_Material.WriteToFile(*outFile);
  h_Muon_E_theta_Interaction.WriteToFile(*outFile);
  h_Muon_E_theta_Particle.WriteToFile(*outFile);
  h_Muon_E_PZ_Material.WriteToFile(*outFile);
  h_Muon_E_PZ_Interaction.WriteToFile(*outFile);
  h_Muon_E_PZ_Particle.WriteToFile(*outFile);
  h_Muon_E_PT_Material.WriteToFile(*outFile);
  h_Muon_E_PT_Interaction.WriteToFile(*outFile);
  h_Muon_E_PT_Particle.WriteToFile(*outFile);
  h_cryoVertex_Z_R_Material.WriteToFile(*outFile);
  h_cryoVertex_Z_R_Interaction.WriteToFile(*outFile);
  h_cryoVertex_Z_X_Material.WriteToFile(*outFile);
  h_cryoVertex_Z_Y_Material.WriteToFile(*outFile);
  h_cryoVertex_X_Y_Material.WriteToFile(*outFile);
  h_cryoVertex_Z_R_OpenAngle.WriteToFile(*outFile);


//////////////////////
//Write 2D migrationss
//////////////////////
std::cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;
std::cout << " Starting to write the mresp "<< std::endl;
std::cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;
const bool clear_bands = true;

for (auto cat: MnvR_vector){

    MnvH2D *migrationH = NULL;
    MnvH2D *h_reco = NULL;
    MnvH2D *h_truth = NULL;

    bool check = cat->GetMigrationObjects(migrationH, h_reco, h_truth );

    //std::vector<std::string> errorhreco = h_reco->GetVertErrorBandNames();
    //for(auto dog : errorhreco){std::cout<<"errorhreco error band "<< dog<< std::endl;}

    //std::cout<< "finished bool check = cat->GetMigrationObjects(migrationH, h_reco, h_truth );"<<std::endl;
    PlotUtils::Hist2DWrapper<HeliumCVUniverse> mresp = PlotUtils::Hist2DWrapper<HeliumCVUniverse>(migrationH, error_bands, clear_bands);
    PlotUtils::Hist2DWrapper<HeliumCVUniverse> mresp_reco = PlotUtils::Hist2DWrapper<HeliumCVUniverse>(h_reco, error_bands, !clear_bands);
    PlotUtils::Hist2DWrapper<HeliumCVUniverse> mresp_true = PlotUtils::Hist2DWrapper<HeliumCVUniverse>(h_truth, error_bands, !clear_bands);

    std::cout<< "finihsed  mresp"<<std::endl;
    //mresp.SyncCVHistos();
    mresp_reco.SyncCVHistos();
    mresp_true.SyncCVHistos();
    std::cout<< "finihsed  mresp.SyncCVHistos();"<<std::endl;
    mresp.hist->Write();
    std::cout<< "finihsed mresp_reco.hist->Write();  "<<std::endl;
    //h_reco.SyncCVHistos();
    mresp_reco.hist->Write();
    //std::vector<std::string> error_names1 = mresp_reco.hist->GetVertErrorBandNames();
    //std::vector<std::string> error_names2 = mresp_true.hist->GetVertErrorBandNames();
    //std::vector<std::string> error_names3 = mresp.hist->GetVertErrorBandNames();
    //DrawPanel_SystematicErrorPlots_ProjectionY(h_reco,"P_{Z}", "P_{T}", title_char, text_title_pdf2 , .8, true, Print1Dplots );
    //for(auto dog : error_names1){std::cout<<"h_reco error band "<< dog<< std::endl;}
    //fstd::cout<< "finihsed h_reco->Write();  "<<std::endl;
    //h_truth.SyncCVHistos();
    //for(auto dog : error_names1){std::cout<<"mresp error band "<< dog<< std::endl;}

    //for(auto dog : error_names2){std::cout<<"h_truth error band "<< dog<< std::endl;}
    mresp_true.hist->Write();

    //std::cout<< "finihsed mresp_true->Write();  "<<std::endl;


  }
///////////////////////////////////////////////
// Finshied Writing Closing
//////////////////////////////////////////////
outFile->Close();


std::cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;
std::cout << " Finshied "<< std::endl;
std::cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;




//MnvPlotter *mnv_plotter = new MnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);




//sprintf(outFileName, "%s_2D%s_%s_%s_noFid.pdf",  "Histograms", c, "RECO_MC", ErrorStatus);
TCanvas *can = new TCanvas("can", "can",1800,1600);
std::cout << "Success" << std::endl;
can -> Print(outFileName_pdf);
can->Close();


for(auto band : error_bands){
  std::vector<HeliumCVUniverse*> band_universes = band.second;
  for(unsigned int i_universe = 0; i_universe < band_universes.size(); ++i_universe){ delete band_universes[i_universe];}
}




}

///////////////////
//END of Event Loop
///////////////////


//=========================================
// Functions
//=========================================
std::vector<ECuts> GetRECOCutsVector() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ECuts> ret_vec;
  ret_vec.push_back(kNoCuts  );
  ret_vec.push_back(kGoodEnergy );
  //ret_vec.push_back(kThetaMu );
  ret_vec.push_back(kMuonAngle );
  ret_vec.push_back(kNTracks);
  ret_vec.push_back(kUsableMuon);
  ret_vec.push_back(kMu_is_Plausible);
  //ret_vec.push_back(kNonMu_is_Plausible);
  ret_vec.push_back(kVeto );
  ret_vec.push_back(kSix );
  ret_vec.push_back(kMatchVetoDeadPaddle);

  ret_vec.push_back(kMinosCoil );
  ret_vec.push_back(kMinosMatch);
  ret_vec.push_back(kMinosCurvature);
  ret_vec.push_back(kMinosCharge );

  ret_vec.push_back(kVertexConverge);
  ret_vec.push_back(kVertex_ConvergedfromAllTracks);
  ret_vec.push_back(kMaxChiSqrt_byTrackType);
  //ret_vec.push_back(kFiducialVolume );
  ret_vec.push_back(kFiducialVolume_new );
  ret_vec.push_back(kTrackForwardGoing );
  ret_vec.push_back(ksecTrkwrtblessthanMaxAngle);
  //ret_vec.push_back(kMaxChiSqrt);

  ret_vec.push_back(kAllCuts );



  //int n = sizeof(kCutsArray) / sizeof(kCutsArray[0]);
  //static std::vector<ECuts> ret_vec(kCutsArray, kCutsArray + n);
  return ret_vec;
//#endif
}

std::vector<ECuts> GetRECOCutsForEffVector() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ECuts> ret_vec;
  ret_vec.push_back(kNoCuts  );
  ret_vec.push_back(kGoodEnergy );
  //ret_vec.push_back(kThetaMu );
  ret_vec.push_back(kMuonAngle );
  ret_vec.push_back(kNTracks);
  ret_vec.push_back(kUsableMuon);
  ret_vec.push_back(kMu_is_Plausible);
  ret_vec.push_back(kNonMu_is_Plausible);
  ret_vec.push_back(kVeto );
  ret_vec.push_back(kSix );
  ret_vec.push_back(kMatchVetoDeadPaddle);

  ret_vec.push_back(kMinosCoil );
  ret_vec.push_back(kMinosMatch);
  ret_vec.push_back(kMinosCurvature);
  ret_vec.push_back(kMinosCharge );

  ret_vec.push_back(kVertexConverge);
  //ret_vec.push_back(kFiducialVolume );
  ret_vec.push_back(kFiducialVolume_new );
  ret_vec.push_back(kTrackForwardGoing );
  ret_vec.push_back(ksecTrkwrtblessthanMaxAngle);
  //ret_vec.push_back(kMaxChiSqrt);
  ret_vec.push_back(kVertex_ConvergedfromAllTracks);
  ret_vec.push_back(kMaxChiSqrt_byTrackType);
  ret_vec.push_back(kAllCuts );

  //int n = sizeof(kCutsArray) / sizeof(kCutsArray[0]);
  //static std::vector<ECuts> ret_vec(kCutsArray, kCutsArray + n);
  return ret_vec;
//#endif
}

std::vector<ECutsTRUTH> GetTRUTHCutsVector() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ECutsTRUTH> True_vec;
  True_vec.push_back(kTRUTHNoCuts   );
  //True_vec.push_back(kTRUTHMuonEnergy );
  //True_vec.push_back(kTRUTHMuonAngle );
  True_vec.push_back(kTRUTHneutrino);
  True_vec.push_back(kTRUTHCCInteraction );
  True_vec.push_back(kTRUTHtarget);
  True_vec.push_back(kTRUTH_greaterthanoneFS);
  //True_vec.push_back(kTRUTHFiduical );// no True Fiduical Cut on top
  //True_vec.push_back(kTRUTH_2ndTrkEnergythreshold );
  //True_vec.push_back(kTRUTH_2ndTrkAnlgethreshold );
  //True_vec.push_back(kTRUTH_secTrk_Angle_threshold);
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);
  //True_vec.push_back(kTRUTH_NoNeutral_FS_2ndTrk_RECOBRANCH);
  //True_vec.push_back(kTRUTH_NoNeutral_FS_2ndTrk_withProtonanPionThresholds_RECOBRANCH);
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);
  True_vec.push_back(kAllTRUTHCuts);


  //int n = sizeof(kCutsArray) / sizeof(kCutsArray[0]);
  //static std::vector<ECuts> ret_vec(kCutsArray, kCutsArray + n);
  return True_vec;
//#endif
}

//////////////////////////////////////////////////////////////////////////
//GET MUON Varibles
//////////////////////////////////////////////////////////////////////////
std::vector<MuonVar> GetMUONVaribles() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<MuonVar> MuonVars;

  MuonVars.push_back(kE );
  MuonVars.push_back(kP_Z);
  MuonVars.push_back(kP_T);
  MuonVars.push_back(kAngleWRTB);
  MuonVars.push_back(kDOCA_muon);

  MuonVars.push_back(kTRUTH_E );
  MuonVars.push_back(kTRUTH_P_Z);
  MuonVars.push_back(kTRUTH_P_T);
  MuonVars.push_back(kTRUTH_AngleWRTB);

  return MuonVars;
//#endif
}

std::vector<Particle_type> GetParicle_type() {
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

//////////////////////////////////////////////////////////////////////////
//GET Vertex Varibles
//////////////////////////////////////////////////////////////////////////
std::vector<CryoVertex> GetCryoVertexVaribles() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<CryoVertex> CryoVertexVars;

  CryoVertexVars.push_back(kX);
  CryoVertexVars.push_back(kY);
  CryoVertexVars.push_back(kZ);
  CryoVertexVars.push_back(kR);


  CryoVertexVars.push_back(kTRUTH_X);
  CryoVertexVars.push_back(kTRUTH_Y);
  CryoVertexVars.push_back(kTRUTH_Z);
  CryoVertexVars.push_back(kTRUTH_R);

  return CryoVertexVars;
//#endif
}

std::vector<SecondTrkVar> GetPlayListSecondTrkVector() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<SecondTrkVar> Playlist;

  Playlist.push_back(ksecE);
  Playlist.push_back(kThetamid);

  return Playlist;
//#endif
}

//////////////////////////
///Weight Functions
/////////////////////////

std::vector<Weights> GetWeightVector() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<Weights> weight_vec;

  weight_vec.push_back(kweightFlux );
  weight_vec.push_back(kweightMinos );
  weight_vec.push_back(kweightGenie);
  weight_vec.push_back(kweight2p2ptune );
  weight_vec.push_back(kweightRPA);
  //weight_vec.push_back(kweightZexp); // applied throught the MAT system
  weight_vec.push_back(kweight_HeliumTargetMass);
  //weight_vec.push_back(kweightLowQ2Pi);

  return weight_vec;
//#endif
}

std::vector<Weights> GetWeightVector_v2() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<Weights> weight_vec;
  weight_vec.push_back(kweightFlux );
  weight_vec.push_back(kweightMinos );
  weight_vec.push_back(kweightGenie);
  weight_vec.push_back(kweight2p2ptune );
  weight_vec.push_back(kweightRPA);
  //weight_vec.push_back(kweightZexp);
  weight_vec.push_back(kweightLowQ2Pi);
  weight_vec.push_back(kweight_HeliumTargetMass);
  return weight_vec;
//#endif
}

std::vector<Weights> GetWeightVector_mk() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<Weights> weight_vec;
  weight_vec.push_back(kweightFlux );
  weight_vec.push_back(kweightMinos );
  weight_vec.push_back(kweightGenie);
  weight_vec.push_back(kweight2p2ptune );
  weight_vec.push_back(kweightRPA);
  //weight_vec.push_back(kweightZexp);
  weight_vec.push_back(kweight_HeliumTargetMass);
  //weight_vec.push_back(kweightLowQ2Pi);
  return weight_vec;
//#endif
}

//////////////////////////
///Main
/////////////////////////
int main(int argc, char* argv[]){
  TH1::AddDirectory(false);
  bool m_cutson = true;

  std::cout << "This is the playlist "<< argv[1] << std::endl;
  std::string playlist_string(argv[1]);
  ME_helium_Playlists Playlist_to_run = GetPlaylist_FromString(playlist_string);

  std::cout << "Run over cutsOn?  (0 = false, 1 = true) " << std::endl;
  //std::cin >> cutsOn;
  std::cout << std::boolalpha << m_cutson << std::endl;

  bool m_debugOn=true;
  std::cout << "Run in Debug Mode? (0 = NO, 1 = YES) " << std::endl;
  //std::cin >> my_debug;
  std::cout << std::boolalpha << m_debugOn << std::endl;


  std::string input_user= "cnguyen";
  std::cout << "What is the name of the user? " << std::endl;
  //std::cin >> input_user;
  std::cout << input_user << std::endl;


  runEventLoop(m_debugOn, Playlist_to_run);
  return 0;
}
//#endif
