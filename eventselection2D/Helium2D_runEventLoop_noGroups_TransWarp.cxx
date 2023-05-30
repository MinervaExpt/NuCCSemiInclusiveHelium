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
const bool m_RunCodeWithSystematics = false;
const bool RunwithConvolution = false;
const bool useweights = false;
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
  PlotUtils::NamedCategory<Interaction_type>({kInteraction_NONE}, "None"),
  PlotUtils::NamedCategory<Interaction_type>({kDISSoft},          "SoftDIS"),
  PlotUtils::NamedCategory<Interaction_type>({kDISHard},          "HardDIS"),
  PlotUtils::NamedCategory<Interaction_type>({kDISSIS},           "SIS"),
  PlotUtils::NamedCategory<Interaction_type>({k2p2h},             "2p2h"),
  PlotUtils::NamedCategory<Interaction_type>({kdeltaRES},         "#DeltaRes"),
  PlotUtils::NamedCategory<Interaction_type>({kHeavierRES},       "HeavierRes"),
  PlotUtils::NamedCategory<Interaction_type>({kElastic},          "QE")
};

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

const std::vector<PlotUtils::NamedCategory<Particle_type>>
ParticleGroup_reduced_categories = {
  PlotUtils::NamedCategory<Particle_type>({kParticle_N_A},          "N_A"),
  PlotUtils::NamedCategory<Particle_type>({kParticle_OTHER},        "Other"),
  PlotUtils::NamedCategory<Particle_type>({kParticle_neutral},      "Neutral"),
  PlotUtils::NamedCategory<Particle_type>({kMuon},                   "Muon"),
  PlotUtils::NamedCategory<Particle_type>({kPion_0_Electron_kGamma},"e^{-/+},#gamma,#pi^{0}"),
  PlotUtils::NamedCategory<Particle_type>({kPion_pos_neg},          "Pi^{-/+}"),
  PlotUtils::NamedCategory<Particle_type>({kProton},                "Proton")


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


   // Beam Angle
    UniverseMap angle_systematics = PlotUtils::GetAngleSystematicsMap<HeliumCVUniverse>(chain);/*,NSFDefaults::beamThetaX_Err,NSFDefaults::beamThetaY_Err*/
    error_bands.insert(angle_systematics.begin(), angle_systematics.end());

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
  MinervaUniverse::SetZExpansionFaReweight(false);
  MinervaUniverse::SetAnalysisNuPDG(14);
  MinervaUniverse::SetNonResPiReweight(false);
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
std::vector<double> Ebin_vector = GetBinMuonVector(kE);
std::vector<double> Pzbin_vector{1.5, 3.0, 4.0, 5.0, 6.0, 8.0, 10.0, 20.0};
std::vector<double> PTbin_vector{0.0, 0.25, 0.4, 0.55, 0.7, 0.85, 2.5};  //0.0, 0.25, 0.325, 0.4, 0.475, 0.55, 0.7, 0.85, 2.5
std::vector<double> MuonThetabin_vector= GetBinMuonVector(kAngleWRTB);

std::vector<double> Pzbin_vector_finebinning = GetBinMuonVector(kP_Z);
std::vector<double> PTbin_vector_finebinning = GetBinMuonVector(kP_T);


std::vector<double> Muon_curvatureSig_vector= GetBinMuonVector(kcurvatureSig);
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
std::vector<double> Vertex_ChiSqFit_vector= GetBinvertexVector(kfitConverge);
////////////////////////
std::vector<double> Vertex_Xbin_vector= GetBinvertexVector(kX);
std::vector<double> Vertex_Ybin_vector= GetBinvertexVector(kY);
std::vector<double> Vertex_Zbin_vector= GetBinvertexVector(kZ);
std::vector<double> Vertex_Rbin_vector= GetBinvertexVector(kR);
std::vector<double> SecTrk_Thetamidbin_vector= GetSecondTrkVarVector(kThetamid);
std::vector<double> SecTrk_Theta_TRUEbin_vector= GetSecondTrkVarVector(kFullAngle);


std::vector<double> Vertex_DOCAbin_vector= GetBinMuonVector(kDOCA_muon);
std::vector<double> Vertex_secondTrkEbin_vector= GetSecondTrkVarVector(ksecE);
std::vector<double> Vertex_secondTrkEbin_Proton_vector= GetSecondTrkVarVector(ksecE_Proton);
std::sort(Vertex_secondTrkEbin_Proton_vector.begin(),Vertex_secondTrkEbin_Proton_vector.end());
std::vector<double> Vertex_secondTrkThetamidbin_vector= GetSecondTrkVarVector(kThetamid);
std::vector<double> SecTrk_DOCA_vector= GetSecondTrkVarVector(kDOCA);
std::vector<double> SecTrk_Pathway_vector= GetSecondTrkVarVector(kPathway);

std::vector<double> MuonMatchtoMinos_vector= GetBinMuonVector(kMuonMatchtoMinos);
std::vector<double> TrackSize_vector= GetBinMuonVector(ktracksize);
std::vector<double> MuonMatchtoVeto_vector= GetBinMuonVector(kMuonMatchtoVeto);

std::vector<double> SecTRK_StartNode_X_vector= GetSecondTrkVarVector(kFirstsecTrk_Xnode);
std::vector<double> SecTRK_StartNode_Y_vector= GetSecondTrkVarVector(kFirstsecTrk_Ynode);
std::vector<double> SecTRK_StartNode_Z_vector= GetSecondTrkVarVector(kFirstsecTrk_Znode);

std::vector<double> SecTRK_LastNodeX_vector= GetSecondTrkVarVector(kLastsecTrk_Xnode);
std::vector<double> SecTRK_LastNodeY_vector= GetSecondTrkVarVector(kLastsecTrk_Ynode);
std::vector<double> SecTRK_LastNodeZ_vector= GetSecondTrkVarVector(kLastsecTrk_Znode);

std::cout<<"bins"<<std::endl;
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
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_PZ_PT("h_Muon_PZ_PT", "h_Muon_PZ_PT",  Pzbin_vector, PTbin_vector, error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_PT_theta("h_Muon_PT_theta", "h_Muon_PT_theta", PTbin_vector , MuonThetabin_vector, error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_PZ_theta("h_Muon_PZ_theta", "h_Muon_PZ_theta", Pzbin_vector , MuonThetabin_vector, error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_E_theta("h_Muon_E_theta", "h_Muon_E_theta",  Ebin_vector , MuonThetabin_vector, error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_E_PZ("h_Muon_E_PZ", "h_Muon_E_PZ",  Ebin_vector ,  Pzbin_vector, error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_E_PT("h_Muon_E_PT", "h_Muon_E_PT",  Ebin_vector , PTbin_vector, error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_cryoVertex_Z_R("h_cryoVertex_Z_R", "h_cryoVertex_Z_R", Vertex_Zbin_vector, Vertex_Rbin_vector , error_bands);

PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_PZ_PT_TRUE_RECO("h_Muon_PZ_PT_TRUE_RECO", "h_Muon_PZ_PT_TRUE_RECO", Pzbin_vector, PTbin_vector,  error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_PT_theta_TRUE_RECO("h_Muon_PT_theta_TRUE_RECO", "h_Muon_PT_theta_TRUE_RECO", PTbin_vector , MuonThetabin_vector, error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_PZ_theta_TRUE_RECO("h_Muon_PZ_theta_TRUE_RECO", "h_Muon_PZ_theta_TRUE_RECO", Pzbin_vector , MuonThetabin_vector, error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_E_theta_TRUE_RECO("h_Muon_E_theta_TRUE_RECO", "h_Muon_E_theta_TRUE_RECO",  Ebin_vector , MuonThetabin_vector, error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_E_PZ_TRUE_RECO("h_Muon_E_PZ_TRUE_RECO", "h_Muon_E_PZ_TRUE_RECO",  Ebin_vector ,  Pzbin_vector, error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_E_PT_TRUE_RECO("h_Muon_E_PT_TRUE_RECO", "h_Muon_E_PT_TRUE_RECO",  Ebin_vector , PTbin_vector, error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_cryoVertex_Z_R_TRUE_RECO("h_cryoVertex_Z_R_TRUE_RECO", "h_cryoVertex_Z_R_TRUE_RECO", Vertex_Zbin_vector, Vertex_Rbin_vector , error_bands);

PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_2ndtrkangle_2ndTrkE_TRUE_RECO("h_2ndtrkangle_2ndTrkE_TRUE_RECO", "h_2ndtrkangle_2ndTrkE_TRUE_RECO", Vertex_secondTrkEbin_vector, SecTrk_Theta_TRUEbin_vector , error_bands);




MnvH2D *h_2d_2ndtrkangle_2ndTrkE_TRUE_RECO    =    new MnvH2D("h_2d_2ndtrkangle_2ndTrkE_TRUE_RECO", "h_2d_2ndtrkangle_2ndTrkE_TRUE_RECO", SecTrk_Theta_TRUEbin_vector.size()-1, SecTrk_Theta_TRUEbin_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );




/// Mnv Response Migration constuctor
//std::map<std::string,MinervaUnfold::MnvResponse*> Response

std::cout<< "PTbin_vector.size()" <<  PTbin_vector.size() << std::endl;
for(auto cat :  PTbin_vector){
std::cout<< cat << std::endl;


}

std::cout<< "PZbin_vector.size()" <<  Pzbin_vector.size() << std::endl;
for(auto cat :  Pzbin_vector){
std::cout<< cat << std::endl;


}




 MinervaUnfold::MnvResponse *MnvR_Muon_PZ_PT    = new MinervaUnfold::MnvResponse( "MnvR_Muon_PZ_PT",     "MnvR_Muon_PZ_PT",            Pzbin_vector,         PTbin_vector,         error_name);
 MinervaUnfold::MnvResponse *MnvR_Muon_PZ_PT_new    = new MinervaUnfold::MnvResponse( "MnvR_Muon_PZ_PT_new",     "MnvR_Muon_PZ_PT_new",Pzbin_vector,          PTbin_vector,         error_name);

 MinervaUnfold::MnvResponse *MnvR_Muon_PZ_PT_plus10percent    = new MinervaUnfold::MnvResponse( "MnvR_Muon_PZ_PT_plus10percent",     "MnvR_Muon_PZ_PT_plus10percent",            Pzbin_vector,         PTbin_vector,         error_name);
 MinervaUnfold::MnvResponse *MnvR_Muon_PZ_PT_minus10percent    = new MinervaUnfold::MnvResponse( "MnvR_Muon_PZ_PT_minus10percent",     "MnvR_Muon_PZ_PT_minus10percent",            Pzbin_vector,         PTbin_vector,         error_name);

 MinervaUnfold::MnvResponse *MnvR_Muon_PZ_PT_WarpingFunction    = new MinervaUnfold::MnvResponse( "MnvR_Muon_PZ_PT_WarpingFunction",     "MnvR_Muon_PZ_PT_WarpingFunction",            Pzbin_vector,         PTbin_vector,         error_name);


 MinervaUnfold::MnvResponse *MnvR_Muon_PT_theta = new MinervaUnfold::MnvResponse( "MnvR_Muon_PT_theta",  "MnvR_Muon_PT_theta",  PTbin_vector,       MuonThetabin_vector,  error_name);
 MinervaUnfold::MnvResponse *MnvR_Muon_PZ_theta = new MinervaUnfold::MnvResponse( "MnvR_Muon_PZ_theta",  "MnvR_Muon_PZ_theta",  Pzbin_vector,       MuonThetabin_vector,  error_name);
 MinervaUnfold::MnvResponse *MnvR_Muon_E_theta  = new MinervaUnfold::MnvResponse( "MnvR_Muon_E_theta",   "MnvR_Muon_E_theta",   Ebin_vector,        MuonThetabin_vector,  error_name);
 MinervaUnfold::MnvResponse *MnvR_Muon_E_PZ     = new MinervaUnfold::MnvResponse( "MnvR_Muon_E_PZ",      "MnvR_Muon_E_PZ",      Ebin_vector,        Pzbin_vector,         error_name);
 MinervaUnfold::MnvResponse *MnvR_Muon_E_PT     = new MinervaUnfold::MnvResponse( "MnvR_Muon_E_PT",      "MnvR_Muon_E_PT",      Ebin_vector,        PTbin_vector,         error_name);
 //MinervaUnfold::MnvResponse *MnvR_cryoVertex_Z_R = new MinervaUnfold::MnvResponse("MnvR_cryoVertex_Z_R", "MnvR_cryoVertex_Z_R", Vecrtex_Zbin_vector, Vertex_Rbin_vector , error_name);

std::vector<MinervaUnfold::MnvResponse*>  MnvR_vector = {MnvR_Muon_PZ_PT,  MnvR_Muon_PT_theta, MnvR_Muon_PZ_theta, MnvR_Muon_E_theta,  MnvR_Muon_E_PZ, MnvR_Muon_E_PT, MnvR_Muon_PZ_PT_plus10percent,
MnvR_Muon_PZ_PT_minus10percent, MnvR_Muon_PZ_PT_WarpingFunction};// , MnvR_cryoVertex_Z_R
std::vector<MinervaUnfold::MnvResponse*>  MnvR_vector_new = {MnvR_Muon_PZ_PT_new};

PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type> h_Muon_PZ_PT_Material =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type>(MaterialGroup_categories, "h_Muon_PZ_PT_Material", Pzbin_vector,  PTbin_vector  ,"h_Muon_PZ_PT_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type> h_Muon_PZ_PT_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_Muon_PZ_PT_Interaction",  Pzbin_vector, PTbin_vector ,"h_Muon_PZ_PT_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type> h_Muon_PZ_PT_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type>(ParticleGroup_categories, "h_Muon_PZ_PT_Particle",  Pzbin_vector, PTbin_vector ,"h_Muon_PZ_PT_Particle; [GeV];Events");


PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type> h_Muon_PT_theta_Material =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type>(MaterialGroup_categories, "h_Muon_PT_theta_Material",  PTbin_vector , MuonThetabin_vector ,"h_Muon_PT_theta_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type> h_Muon_PT_theta_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_Muon_PT_theta_Interaction",  PTbin_vector , MuonThetabin_vector ,"h_Muon_PT_theta_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type> h_Muon_PT_theta_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type>(ParticleGroup_categories, "h_Muon_PT_theta_Particle",  PTbin_vector , MuonThetabin_vector ,"h_Muon_PT_theta_Particle; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type> h_Muon_PZ_theta_Material =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type>(MaterialGroup_categories, "h_Muon_PZ_theta_Material",  Pzbin_vector , MuonThetabin_vector ,"h_Muon_PZ_theta_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type> h_Muon_PZ_theta_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_Muon_PZ_theta_Interaction",  Pzbin_vector , MuonThetabin_vector ,"h_Muon_PZ_theta_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type> h_Muon_PZ_theta_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type>(ParticleGroup_categories, "h_Muon_PZ_theta_Particle",  Pzbin_vector , MuonThetabin_vector ,"h_Muon_PZ_theta_Particle; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type> h_Muon_E_theta_Material =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type>(MaterialGroup_categories, "h_Muon_E_theta_Material",  Ebin_vector , MuonThetabin_vector ,"E_theta_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type> h_Muon_E_theta_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_Muon_E_theta_Interaction",  Ebin_vector , MuonThetabin_vector ,"E_theta_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type> h_Muon_E_theta_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type>(ParticleGroup_categories, "h_Muon_E_theta_Particle",  Ebin_vector , MuonThetabin_vector ,"E_theta_Particle; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type> h_Muon_E_PZ_Material =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type>(MaterialGroup_categories, "h_Muon_E_PZ_Material",  Ebin_vector , Pzbin_vector ,"E_PZ_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type> h_Muon_E_PZ_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_Muon_E_PZ_Interaction",  Ebin_vector , Pzbin_vector ,"E_PZ_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type> h_Muon_E_PZ_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type>(ParticleGroup_categories, "h_Muon_E_PZ_Particle",  Ebin_vector , Pzbin_vector ,"h_Muon_E_PZ_Particle; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type> h_Muon_E_PT_Material =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type>(MaterialGroup_categories, "h_Muon_E_PT_Material",  Ebin_vector , PTbin_vector ,"E_PT_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type> h_Muon_E_PT_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_Muon_E_PT_Interaction",  Ebin_vector , PTbin_vector ,"E_PT_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type> h_Muon_E_PT_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type>(ParticleGroup_categories, "h_Muon_E_PT_Particle",  Ebin_vector , PTbin_vector ,"E_PT_Particle; [GeV];Events");


PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type> h_cryoVertex_Z_R_Material =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type>(MaterialGroup_categories, "h_cryoVertex_Z_R_Material",Vertex_Zbin_vector,  Vertex_Rbin_vector  ,"vertex_z_r_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type> h_cryoVertex_Z_R_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_cryoVertex_Z_R_Interaction",Vertex_Zbin_vector,  Vertex_Rbin_vector  ,"vertex_z_r_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type> h_cryoVertex_Z_R_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type>(ParticleGroup_categories, "h_cryoVertex_Z_R_Particle",Vertex_Zbin_vector,  Vertex_Rbin_vector  ,"vertex_z_r_Particle; [GeV];Events");


///////////////////////////////////////
//
///////////////////////////////////////
MnvH2D *h_2d_PZ_PT_TRUE_RECO       =    new MnvH2D("h_2d_PZ_PT_TRUE_RECO", "h_2d_PZ_PT_TRUE_RECO" ,Pzbin_vector.size()-1, Pzbin_vector.data(),PTbin_vector.size()-1, PTbin_vector.data()  );

MnvH2D *h_2d_E_PZ_TRUE_RECO        =    new MnvH2D("h_2d_E_PZ_TRUE_RECO", "h_2d_E_PZ_TRUE_RECO", Ebin_vector.size()-1, Ebin_vector.data(),Pzbin_vector.size()-1, Pzbin_vector.data()  );

MnvH2D *h_2d_Theta_PZ_TRUE_RECO    =    new MnvH2D("h_2d_Theta_PZ_TRUE_RECO", "h_2d_Theta_PZ_TRUE_RECO", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),Pzbin_vector.size()-1, Pzbin_vector.data()  );

MnvH2D *h_2d_E_PT_TRUE_RECO        =    new MnvH2D("h_2d_E_PT_TRUE_RECO", "h_2d_E_PT_TRUE_RECO", Ebin_vector.size()-1, Ebin_vector.data(),PTbin_vector.size()-1, PTbin_vector.data()  );

//MnvH2D *h_2d_Theta_PZ_TRUE         =    new MnvH2D("h_2d_Theta_PZ_TRUE", "h_2d_Theta_PZ_TRUE", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),Pzbin_vector.size()-1, Pzbin_vector.data()  );
//MnvH2D *h_2d_Theta_PZ_TRUE_RECO    =    new MnvH2D("h_2d_Theta_PZ_TRUE_RECO", "h_2d_Theta_PZ_TRUE_RECO", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),Pzbin_vector.size()-1, Pzbin_vector.data()  );

MnvH2D *h_2d_Theta_PT_TRUE_RECO    =    new MnvH2D("h_2d_Theta_PT_TRUE_RECO", "h_2d_Theta_PT_TRUE_RECO", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),PTbin_vector.size()-1, PTbin_vector.data()  );

///////////////////////////////////////
//
///////////////////////////////////////
MnvH2D *h_2d_Theta_2ndTrkE_TRUE_RECO    =    new MnvH2D("h_2d_Theta_2ndTrkE_TRUE_RECO", "h_2d_Theta_2ndTrkE_TRUE_RECO", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );

MnvH2D *h_2d_muonE_2ndTrkE_TRUE_RECO    =    new MnvH2D("h_2d_muonE_2ndTrkE_TRUE_RECO", "h_2d_muonE_2ndTrkE_TRUE_RECO", Ebin_vector.size()-1, Ebin_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );

MnvH2D *h_2d_muonPT_2ndTrkE_TRUE_RECO    =    new MnvH2D("h_2d_muonPT_2ndTrkE_TRUE_RECO", "h_2d_muonPT_2ndTrkE_TRUE_RECO",  PTbin_vector.size()-1,  PTbin_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );

MnvH2D *h_2d_muonPZ_2ndTrkE_TRUE_RECO    =    new MnvH2D("h_2d_muonPZ_2ndTrkE_TRUE_RECO", "h_2d_muonPZ_2ndTrkE_TRUE_RECO",  Pzbin_vector.size()-1,  Pzbin_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );

///////////////////////////////////////
//
///////////////////////////////////////
MnvH2D *h_2d_Theta_2ndTrKangle_TRUE_RECO    =    new MnvH2D("h_2d_Theta_2ndTrKangle_TRUE_RECO", "h_2d_Theta_2ndTrKangle_TRUE_RECO", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),SecTrk_Theta_TRUEbin_vector.size()-1, SecTrk_Theta_TRUEbin_vector.data()  );

MnvH2D *h_2d_muonE_2ndTrkangle_TRUE_RECO    =    new MnvH2D("h_2d_muonE_2ndTrkangle_TRUE_RECO", "h_2d_muonE_2ndTrkangle_TRUE_RECO", Ebin_vector.size()-1, Ebin_vector.data(),SecTrk_Theta_TRUEbin_vector.size()-1, SecTrk_Theta_TRUEbin_vector.data()  );

MnvH2D *h_2d_muonPT_2ndTrkangle_TRUE_RECO    =    new MnvH2D("h_2d_muonPT_2ndTrkangle_TRUE_RECO", "h_2d_muonPT_2ndTrkangle_TRUE_RECO",  PTbin_vector.size()-1,  PTbin_vector.data(),SecTrk_Theta_TRUEbin_vector.size()-1, SecTrk_Theta_TRUEbin_vector.data()  );

MnvH2D *h_2d_muonPZ_2ndTrkangle_TRUE_RECO    =    new MnvH2D("h_2d_muonPZ_2ndTrkangle_TRUE_RECO", "h_2d_muonPZ_2ndTrkangle_TRUE_RECO",  Pzbin_vector.size()-1,  Pzbin_vector.data(),SecTrk_Theta_TRUEbin_vector.size()-1, SecTrk_Theta_TRUEbin_vector.data()  );

///////////////////////////////////////
// low angle study
///////////////////////////////////////
MnvH2D *h_2d_PZ_PT_LOWANGLE_TRUE_RECO       =    new MnvH2D("h_2d_PZ_PT_LOWANGLE_TRUE_RECO", "h_2d_PZ_PT_LOWANGLE_TRUE_RECO" ,Pzbin_vector.size()-1, Pzbin_vector.data(),PTbin_vector.size()-1, PTbin_vector.data()  );

MnvH2D *h_2d_E_PZ_LOWANGLE_TRUE_RECO        =    new MnvH2D("h_2d_E_PZ_LOWANGLE_TRUE_RECO", "h_2d_E_PZ_LOWANGLE_TRUE_RECO", Ebin_vector.size()-1, Ebin_vector.data(),Pzbin_vector.size()-1, Pzbin_vector.data()  );

MnvH2D *h_2d_Theta_PZ_LOWANGLE_TRUE_RECO    =    new MnvH2D("h_2d_Theta_PZ_LOWANGLE_TRUE_RECO", "h_2d_Theta_PZ_LOWANGLE_TRUE_RECO", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),Pzbin_vector.size()-1, Pzbin_vector.data()  );

MnvH2D *h_2d_E_PT_LOWANGLE_TRUE_RECO        =    new MnvH2D("h_2d_E_PT_LOWANGLE_TRUE_RECO", "h_2d_E_PT_LOWANGLE_TRUE_RECO", Ebin_vector.size()-1, Ebin_vector.data(),PTbin_vector.size()-1, PTbin_vector.data()  );

//MnvH2D *h_2d_Theta_PZ_TRUE         =    new MnvH2D("h_2d_Theta_PZ_TRUE", "h_2d_Theta_PZ_TRUE", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),Pzbin_vector.size()-1, Pzbin_vector.data()  );
//MnvH2D *h_2d_Theta_PZ_LOWANGLE_TRUE_RECO    =    new MnvH2D("h_2d_Theta_PZ_LOWANGLE_TRUE_RECO", "h_2d_Theta_PZ_LOWANGLE_TRUE_RECO", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),Pzbin_vector.size()-1, Pzbin_vector.data()  );

MnvH2D *h_2d_Theta_PT_LOWANGLE_TRUE_RECO    =    new MnvH2D("h_2d_Theta_PT_LOWANGLE_TRUE_RECO", "h_2d_Theta_PT_LOWANGLE_TRUE_RECO", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),PTbin_vector.size()-1, PTbin_vector.data()  );

///////////////////////////////////////
//
///////////////////////////////////////
MnvH2D *h_2d_Theta_2ndTrkE_LOWANGLE_TRUE_RECO    =    new MnvH2D("h_2d_Theta_2ndTrkE_LOWANGLE_TRUE_RECO", "h_2d_Theta_2ndTrkE_LOWANGLE_TRUE_RECO", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );

MnvH2D *h_2d_muonE_2ndTrkE_LOWANGLE_TRUE_RECO    =    new MnvH2D("h_2d_muonE_2ndTrkE_LOWANGLE_TRUE_RECO", "h_2d_muonE_2ndTrkE_LOWANGLE_TRUE_RECO", Ebin_vector.size()-1, Ebin_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );

MnvH2D *h_2d_muonPT_2ndTrkE_LOWANGLE_TRUE_RECO    =    new MnvH2D("h_2d_muonPT_2ndTrkE_LOWANGLE_TRUE_RECO", "h_2d_muonPT_2ndTrkE_LOWANGLE_TRUE_RECO",  PTbin_vector.size()-1,  PTbin_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );

MnvH2D *h_2d_muonPZ_2ndTrkE_LOWANGLE_TRUE_RECO    =    new MnvH2D("h_2d_muonPZ_2ndTrkE_LOWANGLE_TRUE_RECO", "h_2d_muonPZ_2ndTrkE_LOWANGLE_TRUE_RECO",  Pzbin_vector.size()-1,  Pzbin_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );

///////////////////////////////////////
//
///////////////////////////////////////
MnvH2D *h_2d_Theta_2ndTrKangle_LOWANGLE_TRUE_RECO    =    new MnvH2D("h_2d_Theta_2ndTrKangle_LOWANGLE_TRUE_RECO", "h_2d_Theta_2ndTrKangle_LOWANGLE_TRUE_RECO", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),SecTrk_Theta_TRUEbin_vector.size()-1, SecTrk_Theta_TRUEbin_vector.data()  );

MnvH2D *h_2d_muonE_2ndTrkangle_LOWANGLE_TRUE_RECO    =    new MnvH2D("h_2d_muonE_2ndTrkangle_LOWANGLE_TRUE_RECO", "h_2d_muonE_2ndTrkangle_LOWANGLE_TRUE_RECO", Ebin_vector.size()-1, Ebin_vector.data(),SecTrk_Theta_TRUEbin_vector.size()-1, SecTrk_Theta_TRUEbin_vector.data()  );

MnvH2D *h_2d_muonPT_2ndTrkangle_LOWANGLE_TRUE_RECO    =    new MnvH2D("h_2d_muonPT_2ndTrkangle_LOWANGLE_TRUE_RECO", "h_2d_muonPT_2ndTrkangle_LOWANGLE_TRUE_RECO",  PTbin_vector.size()-1,  PTbin_vector.data(),SecTrk_Theta_TRUEbin_vector.size()-1, SecTrk_Theta_TRUEbin_vector.data()  );

MnvH2D *h_2d_muonPZ_2ndTrkangle_LOWANGLE_TRUE_RECO    =    new MnvH2D("h_2d_muonPZ_2ndTrkangle_LOWANGLE_TRUE_RECO", "h_2d_muonPZ_2ndTrkangle_LOWANGLE_TRUE_RECO",  Pzbin_vector.size()-1,  Pzbin_vector.data(),SecTrk_Theta_TRUEbin_vector.size()-1, SecTrk_Theta_TRUEbin_vector.data()  );

////////////////////////////////////
//MnvH2D *h_2d_Theta_PT_TRUE         =    new MnvH2D("h_2d_Theta_PT_TRUE", "h_2d_Theta_PT_TRUE", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),PTbin_vector.size()-1, PTbin_vector.data()  );
//MnvH2D *h_2d_Theta_PT_LOWANGLE_TRUE_RECO    =    new MnvH2D("h_2d_Theta_PT_LOWANGLE_TRUE_RECO", "h_2d_Theta_PT_LOWANGLE_TRUE_RECO", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),PTbin_vector.size()-1, PTbin_vector.data()  );
///////////////////////////////////////
//
///////////////////////////////////////

MnvH2D *h_2d_2ndtrkangle_2ndTrkE_LOWANGLE_TRUE_RECO    =    new MnvH2D("h_2d_2ndtrkangle_2ndTrkE_LOWANGLE_TRUE_RECO", "h_2d_2ndtrkangle_2ndTrkE_LOWANGLE_TRUE_RECO", SecTrk_Theta_TRUEbin_vector.size()-1, SecTrk_Theta_TRUEbin_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );

MnvH2D *h_2d_2ndtrkangle_2ndTrkE_Proton_LOWANGLE_TRUE_RECO    =    new MnvH2D("h_2d_2ndtrkangle_2ndTrkE_Proton_LOWANGLE_TRUE_RECO", "h_2d_2ndtrkangle_2ndTrkE_Proton_LOWANGLE_TRUE_RECO", SecTrk_Theta_TRUEbin_vector.size()-1, SecTrk_Theta_TRUEbin_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );

MnvH2D *h_2d_2ndtrkangle_2ndTrkE_Pion_LOWANGLE_TRUE_RECO    =    new MnvH2D("h_2d_2ndtrkangle_2ndTrkE_Pion_LOWANGLE_TRUE_RECO", "h_2d_2ndtrkangle_2ndTrkE_Pion_LOWANGLE_TRUE_RECO", SecTrk_Theta_TRUEbin_vector.size()-1, SecTrk_Theta_TRUEbin_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );

MnvH2D *h_2d_2ndtrkangle_2ndTrkE_dimuon_LOWANGLE_TRUE_RECO    =    new MnvH2D("h_2d_2ndtrkangle_2ndTrkE_dimuon_LOWANGLE_TRUE_RECO", "h_2d_2ndtrkangle_2ndTrkE_dimuon_LOWANGLE_TRUE_RECO", SecTrk_Theta_TRUEbin_vector.size()-1, SecTrk_Theta_TRUEbin_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );

/////////////////////////////////////
//
/////////////////////////////////////




MnvH2D *h_2d_2ndtrkangle_2ndTrkE_Proton_TRUE_RECO    =    new MnvH2D("h_2d_2ndtrkangle_2ndTrkE_Proton_TRUE_RECO", "h_2d_2ndtrkangle_2ndTrkE_Proton_TRUE_RECO", SecTrk_Theta_TRUEbin_vector.size()-1, SecTrk_Theta_TRUEbin_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );

MnvH2D *h_2d_2ndtrkangle_2ndTrkE_Pion_TRUE_RECO    =    new MnvH2D("h_2d_2ndtrkangle_2ndTrkE_Pion_TRUE_RECO", "h_2d_2ndtrkangle_2ndTrkE_Pion_TRUE_RECO", SecTrk_Theta_TRUEbin_vector.size()-1, SecTrk_Theta_TRUEbin_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );

MnvH2D *h_2d_2ndtrkangle_2ndTrkE_dimuon_TRUE_RECO    =    new MnvH2D("h_2d_2ndtrkangle_2ndTrkE_dimuon_TRUE_RECO", "h_2d_2ndtrkangle_2ndTrkE_dimuon_TRUE_RECO", SecTrk_Theta_TRUEbin_vector.size()-1, SecTrk_Theta_TRUEbin_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );
////////////////////////////////////////
////Migration Studies
///////////////////////////////////////

/////////////////////////////////////////

  //=========================================
  // Entry Loop For MC
  //=========================================

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

             double Pmu =   universe->GetPmu()/1000;
             double Emu =   universe->GetEmu()*.001;
             double phi = universe->GetPhimu();

             double px = Pmu * std::sin(Theta) * std::cos(phi);
             double py = Pmu * std::sin(Theta) * std::sin(phi);

             double PT = sqrt(px*px + py*py);
             double PZ = Pmu*std::cos(Theta);




             double mvn1wgt = universe->GetWeight(kWeights_v1tune);


                     double x_true= universe->GetTRUE_Vertex_x();
                     double y_true= universe->GetTRUE_Vertex_y();
                     double z_true= universe->GetTRUE_Vertex_z();


                     double r_true =  sqrt(x_true*x_true + y_true*y_true);

                   //if(RunwithFid==true){
                     //if(IsInFiducalVolumeFromtheInnerEdge( r, z, 50.0  )==false) continue;
                   //}
                   Material_type Material_type_Event = universe->Get_MaterialStackType();
                     CryoTank_REGIONS CryoTankRegion_type = FourRegion_of_CryoTank(z_true);

                     double Al_wgt = 1.0;
                     if(useweights==true){Al_wgt *= return_AlWgt(CryoTankRegion_type, Material_type_Event);}
                       mvn1wgt*=Al_wgt;




                       h_Muon_PZ_PT.univHist(universe)->Fill(PZ, PT, mvn1wgt);
                       h_Muon_PT_theta.univHist(universe)->Fill(PT, Theta_Degs,mvn1wgt);
                       h_Muon_PZ_theta.univHist(universe)->Fill( PZ, Theta_Degs,mvn1wgt);
                       h_Muon_E_theta.univHist(universe)->Fill(Emu,Theta_Degs , mvn1wgt);
                       h_Muon_E_PZ.univHist(universe)->Fill(Emu, PZ, mvn1wgt);
                       h_Muon_E_PT.univHist(universe)->Fill(Emu, PT, mvn1wgt);
                       h_cryoVertex_Z_R.univHist(universe)->Fill(universe->GetVertex_z(),universe->GetVertex_r() , mvn1wgt);




             ///////////////////////////////////////////
             ////
             ////  FILL CV
             ////
             ////
             ///////////////////////////////////////////

             if( isCV(*universe)){

               int secondTrk = universe->Getindex2ndTrackhighestKE();
               Interaction_type Interaction_type_Event =  universe->Get_Interaction_withDISbreakdown();
               Material_type Material_type_Event = universe->Get_MaterialStackType();
              // Particle_type Particle_type_Event =  universe->Get_NonParticleStackType(secondTrk);
              Particle_type Particle_type_Event = GetParticlegroup_typeReduced(secondTrk);


               h_Muon_PZ_PT_Material.GetComponentHist(Material_type_Event)->Fill(PZ, PT, mvn1wgt);
               h_Muon_PZ_PT_Interaction.GetComponentHist(Interaction_type_Event)->Fill(PZ, PT, mvn1wgt);
               h_Muon_PZ_PT_Particle.GetComponentHist(Particle_type_Event)->Fill(PZ, PT, mvn1wgt);

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

               h_cryoVertex_Z_R_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetVertex_z(),universe->GetVertex_r(), mvn1wgt);
               h_cryoVertex_Z_R_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetVertex_z(),universe->GetVertex_r(), mvn1wgt);
               h_cryoVertex_Z_R_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetVertex_z(),universe->GetVertex_r(), mvn1wgt);

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

           double Smearing_X = vertexX_Convolution(generator);
           double Smearing_Y = vertexY_Convolution(generator);
           double Smearing_Z = vertexZ_Convolution(generator);

           if(RunwithConvolution == false){
             Smearing_X = 0.0;
             Smearing_Y = 0.0;
             Smearing_Z = 0.0;
           }

           double x = universe->GetVertex_x() + Smearing_X;
           double y = universe->GetVertex_y() + Smearing_Y;
           double z = universe->GetVertex_z() + Smearing_Z;
           double r =  sqrt(x*x + y*y);

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

          double Pmu =   universe->GetPmu()/1000;
          double Emu =   universe->GetEmu()*.001;
          double phi = universe->GetPhimu();

          double px = Pmu * std::sin(Theta) * std::cos(phi);
          double py = Pmu * std::sin(Theta) * std::sin(phi);

          double PT = sqrt(px*px + py*py);
          double PZ = Pmu*std::cos(Theta);

          double mvn1wgt = universe->GetWeight(kWeights_v1tune);

          auto PDG_trklist = universe->GetVector_nonMuonTk_PDG_Parent();
          auto Energy_trklist = universe-> GetVector_nonMuonTk_Energy_GeV_Parent();
          auto Angle_trklist = universe->GetVector_nonMuonTk_Angle_wrtb_Degs_Parent();
          auto EnergyFraction_vector = universe->Get_TrueFractionE_vector();
          int secondTrk = universe->Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_lessthanAngle_muonNotinlist(PDG_trklist, Energy_trklist, Angle_trklist, EnergyFraction_vector);

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
          h_cryoVertex_Z_R_TRUE_RECO.univHist(universe)->Fill(universe->GetTRUE_Vertex_z(),universe->GetTRUE_Vertex_r() , mvn1wgt);
          h_2ndtrkangle_2ndTrkE_TRUE_RECO.univHist(universe)->Fill(secTrkAngle, secTrkKE, mvn1wgt);

          const int  unvHist_count = MnvReponse_Hist_N_Map[unv_count];
        //  std::cout<<"universe->ShortName() = "<< universe->ShortName()<< "unvHist_count = "<< unvHist_count<<"unv_count = "<< unv_count<<std::endl;
        //  std::cout<< <<std::endl;
        //  std::cout<<"unv_count = "<< unv_count<<std::endl;
        double PTreco = universe->GetMuonPT_new();
        double Pzreco = universe->GetMuonPz_new();

        double PTtrue = universe->GetMuonPTTrue_new();
        double Pztrue = universe->GetMuonPzTrue_new();

        //std::cout<< "universe->ShortName() = "<< universe->ShortName()<< "   unvHist_count = "<< unvHist_count<< "unv_count = "<<unv_count<< std::endl;

          MnvR_Muon_PZ_PT_new->Fill(Pzreco, PTreco, Pztrue, PTtrue, universe->ShortName(),unvHist_count,mvn1wgt);
          MnvR_Muon_PZ_PT->Fill(PZ, PT, MuonPZ_TRUE, MuonPT_TRUE, universe->ShortName(),unvHist_count,mvn1wgt);
          MnvR_Muon_PZ_PT_plus10percent->Fill(Pzreco, PTreco, Pztrue, PTtrue, universe->ShortName(),unvHist_count,mvn1wgt*1.1);
          MnvR_Muon_PZ_PT_minus10percent->Fill(Pzreco, PTreco, Pztrue, PTtrue, universe->ShortName(),unvHist_count,mvn1wgt*.9);

          double warpwgt = WarpingFunctionPZ_PT_GeV(Pztrue, PTtrue);
          MnvR_Muon_PZ_PT_WarpingFunction->Fill(Pzreco, PTreco, Pztrue, PTtrue, universe->ShortName(),unvHist_count,mvn1wgt*warpwgt);


          MnvR_Muon_PT_theta->Fill(PT,Theta_Degs, MuonPT_TRUE,Theta_Degs_TRUE,universe->ShortName(),unvHist_count,mvn1wgt);
          MnvR_Muon_PZ_theta->Fill(PZ,Theta_Degs,MuonPZ_TRUE,Theta_Degs_TRUE,universe->ShortName(),unvHist_count,mvn1wgt);
          MnvR_Muon_E_theta->Fill(Emu, Theta_Degs, Emu_TRUE, Theta_Degs_TRUE,universe->ShortName(),unvHist_count,mvn1wgt);
          MnvR_Muon_E_PZ->Fill(Emu,PZ,Emu_TRUE ,MuonPZ_TRUE,universe->ShortName(),unvHist_count,mvn1wgt);
          MnvR_Muon_E_PT->Fill(Emu,PT,Emu_TRUE ,MuonPT_TRUE,universe->ShortName(),unvHist_count,mvn1wgt);
          //MnvR_cryoVertex_Z_R->Fill(universe->GetVertex_z(), universe->GetVertex_r(),universe->GetTRUE_Vertex_z(),universe->GetTRUE_Vertex_r() ,universe->ShortName(), unvHist_count, mvn1wgt);

          unv_count++;
        } // End of RECO CUTs
      }// End of TRUTH CUTS
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
h_Muon_PT_theta.SyncCVHistos();
h_Muon_PZ_theta.SyncCVHistos();
h_Muon_E_theta.SyncCVHistos();
h_Muon_E_PZ.SyncCVHistos();
h_Muon_E_PT.SyncCVHistos();
h_cryoVertex_Z_R.SyncCVHistos();

h_Muon_PZ_PT_TRUE_RECO.SyncCVHistos();
h_Muon_PT_theta_TRUE_RECO.SyncCVHistos();
h_Muon_PZ_theta_TRUE_RECO.SyncCVHistos();
h_Muon_E_theta_TRUE_RECO.SyncCVHistos();
h_Muon_E_PZ_TRUE_RECO.SyncCVHistos();
h_Muon_E_PT_TRUE_RECO.SyncCVHistos();
h_cryoVertex_Z_R_TRUE_RECO.SyncCVHistos();
//MnvR_Muon_PZ_PT->SyncCVHistos();
//////////////////////////////////

  //=========================================
  // Plot stuff
  //=========================================

  // DrawMCWithErrorBand
//  PlotCVAndError(Muon_PZ_FULLMC.hist, "TEST");
std::string systematics_status;
if(m_RunCodeWithSystematics==true){sysmatics_status= "All_SysErrorsOn";}
else if (m_RunCodeWithSystematics==false){sysmatics_status= "StatsONLYErrors";}


  char outFileName[1024];
  auto playlist_name = Playlist_Info.GetPlaylistname();
  char c[playlist_name.length() + 1];
  char rootpathway[OUTputRoot_pathway.length()+1];
  char ErrorStatus[sysmatics_status.length()+1];

  strcpy(rootpathway, OUTputRoot_pathway.c_str());
  strcpy(c, playlist_name.c_str());
  strcpy(ErrorStatus, sysmatics_status.c_str());



  TGraph  *RECO_2DCuts           = Make_RECOCut_Tgraph_fromCutMap("RECO_2DCuts"          , CountMap_RECO);
  TGraph  *RECO_Helium_2DCuts    = Make_RECOCut_Tgraph_fromCutMap("RECO_Helium_2DCuts"   , CountMap_RECO_Helium);
  TGraph  *RECO_nonHelium_2DCuts = Make_RECOCut_Tgraph_fromCutMap("RECO_nonHelium_2DCuts", CountMap_RECO);
  TGraph  *TRUE_RECO_2DCuts      = Make_RECOCut_Tgraph_fromCutMap("TRUE_RECO_2DCuts"     , CountMap_TRUE_RECO);
  TGraph  *Truth_2DCuts          = Make_TruthCut_Tgraph_fromCutMap("Truth_2DCuts"        , Truth_Cut_Map);

  sprintf(outFileName, "%s/%s_2D%s_%s_%sTRANSWARP_MK.root", rootpathway, "Histograms", c, "RECO_MC", ErrorStatus);
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
  PlotUtils::MnvH2D* h_Muon_PZ_PT_FluxIntegrated = PlotUtils::flux_reweighter(playlist_fluxreweighter, nu_pdg, useNuEconstraint, NFlux_universe).GetIntegratedFluxReweighted(nu_pdg, h_Muon_PZ_PT.hist, Min_NuFluxEnergy, Max_NuFluxEnergy, useMuonCorrelations);
  h_Muon_PZ_PT_FluxIntegrated->Clone()->Write("h_Muon_PZ_PT_FluxIntegrated");
  h_Muon_PT_theta.hist->Write();

  PlotUtils::MnvH2D* h_Muon_PT_theta_FluxIntegrated = PlotUtils::flux_reweighter(playlist_fluxreweighter, nu_pdg, useNuEconstraint, NFlux_universe).GetIntegratedFluxReweighted(nu_pdg, h_Muon_PT_theta.hist, Min_NuFluxEnergy, Max_NuFluxEnergy, useMuonCorrelations);
  h_Muon_PT_theta_FluxIntegrated->Clone()->Write("h_Muon_PT_theta_FluxIntegrated");
  h_Muon_PZ_theta.hist->Write();

  PlotUtils::MnvH2D* h_Muon_PZ_theta_FluxIntegrated = PlotUtils::flux_reweighter(playlist_fluxreweighter, nu_pdg, useNuEconstraint, NFlux_universe).GetIntegratedFluxReweighted(nu_pdg, h_Muon_PZ_theta.hist, Min_NuFluxEnergy, Max_NuFluxEnergy, useMuonCorrelations);
  h_Muon_PZ_theta_FluxIntegrated->Clone()->Write("h_Muon_PZ_theta_FluxIntegrated");

  h_Muon_E_theta.hist->Write();
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


  h_Muon_PZ_PT_TRUE_RECO.hist->Write();
  h_Muon_PT_theta_TRUE_RECO.hist->Write();
  h_Muon_PZ_theta_TRUE_RECO.hist->Write();
  h_Muon_E_theta_TRUE_RECO.hist->Write();
  h_Muon_E_PZ_TRUE_RECO.hist->Write();
  h_Muon_E_PT_TRUE_RECO.hist->Write();
  h_cryoVertex_Z_R_TRUE_RECO.hist->Write();

  h_Muon_PZ_PT_Material.WriteToFile(*outFile);
  h_Muon_PZ_PT_Interaction.WriteToFile(*outFile);
  h_Muon_PZ_PT_Particle.WriteToFile(*outFile);
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
  h_cryoVertex_Z_R_Particle.WriteToFile(*outFile);


//////////////////////
//Write 2D migrationss
//////////////////////
std::cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;
std::cout << " Starting to write the mresp "<< std::endl;
std::cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;
int check=1;
  const bool clear_bands = true;



  for (auto cat: MnvR_vector){

    cout <<"Counter = "<< check << std::endl;

    MnvH2D *migrationH = NULL;
    MnvH2D *h_reco = NULL;
    MnvH2D *h_truth = NULL;
    bool check = cat->GetMigrationObjects(migrationH, h_reco, h_truth );

    std::vector<std::string> errorhreco = h_reco->GetVertErrorBandNames();
    for(auto dog : errorhreco){std::cout<<"errorhreco error band "<< dog<< std::endl;}



    std::cout<< "finished bool check = cat->GetMigrationObjects(migrationH, h_reco, h_truth );"<<std::endl;
    PlotUtils::Hist2DWrapper<HeliumCVUniverse> mresp = PlotUtils::Hist2DWrapper<HeliumCVUniverse>(migrationH, error_bands, clear_bands);
    PlotUtils::Hist2DWrapper<HeliumCVUniverse> mresp_reco = PlotUtils::Hist2DWrapper<HeliumCVUniverse>(h_reco, error_bands, !clear_bands);
    PlotUtils::Hist2DWrapper<HeliumCVUniverse> mresp_true = PlotUtils::Hist2DWrapper<HeliumCVUniverse>(h_truth, error_bands, !clear_bands);

    std::cout<< "finihsed  mresp"<<std::endl;
    mresp.SyncCVHistos();
    mresp_reco.SyncCVHistos();
    mresp_true.SyncCVHistos();
    std::cout<< "finihsed  mresp.SyncCVHistos();"<<std::endl;
    mresp.hist->Write();
    std::cout<< "finihsed mresp_reco.hist->Write();  "<<std::endl;
    //h_reco.SyncCVHistos();
    mresp_reco.hist->Write();
    std::vector<std::string> error_names1 = mresp_reco.hist->GetVertErrorBandNames();
    std::vector<std::string> error_names2 = mresp_true.hist->GetVertErrorBandNames();
    std::vector<std::string> error_names3 = mresp.hist->GetVertErrorBandNames();
    //DrawPanel_SystematicErrorPlots_ProjectionY(h_reco,"P_{Z}", "P_{T}", title_char, text_title_pdf2 , .8, true, Print1Dplots );
    for(auto dog : error_names1){std::cout<<"h_reco error band "<< dog<< std::endl;}
    //fstd::cout<< "finihsed h_reco->Write();  "<<std::endl;
    //h_truth.SyncCVHistos();
    for(auto dog : error_names1){std::cout<<"mresp error band "<< dog<< std::endl;}

    for(auto dog : error_names2){std::cout<<"h_truth error band "<< dog<< std::endl;}
    mresp_true.hist->Write();

    std::cout<< "finihsed mresp_true->Write();  "<<std::endl;
    check++;

  }
  for (auto cat: MnvR_vector_new){

    cout <<"Counter = "<< check << std::endl;

    MnvH2D *migrationH = NULL;
    MnvH2D *h_reco = NULL;
    MnvH2D *h_truth = NULL;
    bool check = cat->GetMigrationObjects(migrationH, h_reco, h_truth );


    migrationH->Write();
    h_reco->Write();
    h_truth->Write();




  }





///////////////////////////////////////////////
// Finshied Writing Closing
//////////////////////////////////////////////
outFile->Close();


std::cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;
std::cout << " Finshied "<< std::endl;
std::cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;



TCanvas *can = new TCanvas("can", "can",1800,1600);
//MnvPlotter *mnv_plotter = new MnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);

char  pdfName[1024];
char pdf_start[1024];
char pdf_end[1024];
sprintf(pdfName, "MuonVars");

for(auto band : error_bands){
  std::vector<HeliumCVUniverse*> band_universes = band.second;
  for(unsigned int i_universe = 0; i_universe < band_universes.size(); ++i_universe){ delete band_universes[i_universe];}
}

std::cout << "Success" << std::endl;
can -> Print("Test.pdf");

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
  weight_vec.push_back(kweight_HeliumTargetMass);
  //weight_vec.push_back(kweightLowQ2Pi);
   weight_vec.push_back(kweightMK);
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
  //weight_vec.push_back(kweightGenie);
  weight_vec.push_back(kweight2p2ptune );
  weight_vec.push_back(kweightRPA);
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
