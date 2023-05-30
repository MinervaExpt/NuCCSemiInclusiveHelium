//File: Helium2D_runEventLoop.cxx
//Brief: Given ntuple files from HeAnaTupleTool.cpp , extracts 2D RECO EventSelction for 4Helium-Nu interactions
//Writes a .root file Event Selection histograms.
//
//Usage: RECO 2DEventSelection
//
//Author: Christian Nguyen  christian2nguyen@ufl.edu

#include "MasterAnn_runEventLoop_noGroups.h"
//#include "../includes/HeliumCVUniverse.h"
TDatabasePDG *pdg_DATABASEobject = TDatabasePDG::Instance();
std::string OUTputRoot_pathway = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles_MasterAnaDev";
//=====================================================
// Functions
//=====================================================
typedef std::map<int, int> TRUE_RECOMap;

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
const bool RunwithConvolution = false;
const bool useweights = false;
const bool FidOn = true;
double Angle55Deg_inrad = 0.959931; // 55 degs


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

const std::vector<PlotUtils::NamedCategory<Particle_type>>
ParticleGroup_reduced_categories = {
  PlotUtils::NamedCategory<Particle_type>({kProton},                 "Proton"),
  PlotUtils::NamedCategory<Particle_type>({kPion_pos_neg},           "#pi^{#pm}"),
  PlotUtils::NamedCategory<Particle_type>({kParticle_neutral},       "Neutral"),
  PlotUtils::NamedCategory<Particle_type>({kMuon},                   "Muon"),
  PlotUtils::NamedCategory<Particle_type>({kPion_0_Electron_kGamma}, "Pion_0_Electron_kGamma"),
  PlotUtils::NamedCategory<Particle_type>({kParticle_OTHER},         "Other")
};



const std::vector<PlotUtils::NamedCategory<CH_Signal_type>>
Signal_Selection_categories = {
  PlotUtils::NamedCategory<CH_Signal_type>({kSignal},                 "Signal"),
  PlotUtils::NamedCategory<CH_Signal_type>({kBG_NC},                  "BG NC"),
  PlotUtils::NamedCategory<CH_Signal_type>({kBG_CCwrongsign},         "BG Wrong Sign"),
  PlotUtils::NamedCategory<CH_Signal_type>({kBG_Neutral_secTrk},      "BG neutral recoil Trk"),
};



const int n_flux_universes = 100;

UniverseMap GetErrorBands(PlotUtils::ChainWrapper* chain ) {

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

        // Target Mass Systematics
        UniverseMap targetMass_systematics = PlotUtils::GetTargetMassSystematicsMap_forScintillator<HeliumCVUniverse>(chain);
        error_bands.insert(targetMass_systematics.begin(), targetMass_systematics.end());

        //========================================================================
        // Particle Response Systematics (Detector)
        //========================================================================

      //  const bool NEUTRON = false;
      //  const bool use_new_part_resp = true;
      //  const bool PROTON = true;
      //  UniverseMap Response_systematics = PlotUtils::GetResponseSystematicsMap<HeliumCVUniverse>(chain, NEUTRON, use_new_part_resp, PROTON);
      //  error_bands.insert(Response_systematics.begin(), Response_systematics.end());

        //========================================================================
        // GEANT hadrons with MnvHadronReweight
        //========================================================================
        //UniverseMap GeantHadron_systematics = PlotUtils::GetGeantHadronSystematicsMap<HeliumCVUniverse>(chain);
        //error_bands.insert(GeantHadron_systematics.begin(), GeantHadron_systematics.end());
       //Don't need Hadron sysmatics because im not measuring any hadronic dependend parameteres
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

std::vector<FluxSlices> DaisyN{
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
  //ME_helium_Status CryoTankStatus =  GetPlaylist_HeliumStatus(PlayList_iterator);

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

  auto Playlist_txtFILEPath = GetPlaylist_txtFILE_path_MasterAnaDev(PlayList_iterator, is_mc );
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"Adding to Chain Wrapper For Loop   "<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  PlotUtils::ChainWrapper* chw_MC = makeChainWrapperPtr(Playlist_txtFILEPath.c_str(), "MasterAnaDev");
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"Adding to Chain Wrapper For POT counter   "<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  PlotUtils::ChainWrapper* mcchainPOT = makeChainWrapperPtr(Playlist_txtFILEPath.c_str(), "Meta");

  //======================================================================
  ///////////////////Making/adding to error bands  ///////////////////////////
  //======================================================================
//std::map< std::string, std::vector<HeliumCVUniverse*> > error_bands = GetErrorBands(chw_FullMC);
//std::map<std::string, std::vector<HeliumCVUniverse*> > error_bands= GetErrorBands(chw_MC);

UniverseMap error_bands = GetErrorBands(chw_MC);
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



POTCounter pot_counter;


//const std::string RootName = GetPlaylist_ROOT_path(PlayList_iterator, is_mc );
const std::string RootName = GetPlaylist_ROOT_path_MasterAnaDev(PlayList_iterator, is_mc );
//const std::string RootName = GetPlaylist_ROOT_path("1F_pdgcorrection_2",  is_mc );
std::cout<<"The Playlist that is set is = "<< playlist.c_str()<<std::endl;
std::cout<<"The Playlist Root = "<< RootName<<std::endl;
 ///pnfs/minerva/persistent/users/cnguyen/ME_G1_Merg/*.root

std::cout<<"Working with Playlist =  "<<  Playlist_Info.GetPlaylistname()<<std::endl;

  //======================================================================
  // SET Binning for Hist
  //======================================================================
  std::vector<double> Ebin_vector = GetBinMuonVector(kE_2D);
  std::vector<double> PTbin_vector= GetBinMuonVector(kP_T_2D);
  std::vector<double> Pzbin_vector = GetBinMuonVector(kP_Z_2D);

  std::vector<double> MuonThetabin_vector= GetBinMuonVector(kAngleWRTB_2D);
  std::vector<double> Ebin_1Dvector = GetBinMuonVector(kE);
  std::vector<double> Pzbin_1Dvector= GetBinMuonVector(kP_Z);
  std::vector<double> PTbin_1Dvector= GetBinMuonVector(kP_T);
  std::vector<double> MuonThetabin_1Dvector= GetBinMuonVector(kAngleWRTB);

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


std::vector<double> Vertex_secondTrkTheta_bins= GetSecondTrkVarVector(kThetamid);


std::vector<double> Recoil_track_length_vector;
double recoil_bin_count=0.0;
for(int ww = 0; ww < 100; ww++ ){
Recoil_track_length_vector.push_back(recoil_bin_count);
recoil_bin_count = recoil_bin_count + 2.54; // bins in [cm]
}




/////////////////////////////////
// 2d reponse using bin space
////////////////////////////////
//vector<vector<double> > vector_2D_PZ_PT;
//vector_2D_PZ_PT.push_back(PTbin_vector);
//vector_2D_PZ_PT.push_back(Pzbin_vector);
//HyperDimLinearizer::HyperDimLinearizer *HyperDim2d_PZ_PT = new HyperDimLinearizer::HyperDimLinearizer(vector_2D_PZ_PT,0)
////////////////
//Patal maps
////////////////
// 2D
////////////////
std::map< FluxSlices, PlotUtils::Hist2DWrapper<HeliumCVUniverse>> h_Muon_PZ_PT_Daisy_Map;
std::map< FluxSlices, PlotUtils::Hist2DWrapper<HeliumCVUniverse>> h_Muon_PZ_PT_BG_Daisy_Map;
std::map< FluxSlices, PlotUtils::Hist2DWrapper<HeliumCVUniverse>> h_Muon_PZ_PT_TRUE_RECO_Daisy_Map;
////////////////
// 1D
////////////////
std::map< FluxSlices, PlotUtils::HistWrapper<HeliumCVUniverse>> h_MuonE_Daisy_Map;
std::map< FluxSlices, PlotUtils::HistWrapper<HeliumCVUniverse>> h_MuonE_BG_Daisy_Map;
std::map< FluxSlices, PlotUtils::HistWrapper<HeliumCVUniverse>> h_MuonE_TRUE_RECO_Daisy_Map;
std::map< FluxSlices, PlotUtils::HistWrapper<HeliumCVUniverse>> h_MuonPZ_Daisy_Map;
std::map< FluxSlices, PlotUtils::HistWrapper<HeliumCVUniverse>> h_MuonPZ_BG_Daisy_Map;
std::map< FluxSlices, PlotUtils::HistWrapper<HeliumCVUniverse>> h_MuonPZ_TRUE_RECO_Daisy_Map;
std::map< FluxSlices, PlotUtils::HistWrapper<HeliumCVUniverse>> h_MuonPT_Daisy_Map;
std::map< FluxSlices, PlotUtils::HistWrapper<HeliumCVUniverse>> h_MuonPT_BG_Daisy_Map;
std::map< FluxSlices, PlotUtils::HistWrapper<HeliumCVUniverse>> h_MuonPT_TRUE_RECO_Daisy_Map;
std::map< FluxSlices, PlotUtils::HistWrapper<HeliumCVUniverse>> h_MuonTheta_Daisy_Map;
std::map< FluxSlices, PlotUtils::HistWrapper<HeliumCVUniverse>> h_MuonTheta_BG_Daisy_Map;
std::map< FluxSlices, PlotUtils::HistWrapper<HeliumCVUniverse>> h_MuonTheta_TRUE_RECO_Daisy_Map;

std::map< FluxSlices, MinervaUnfold::MnvResponse*> h_Muon_PZ_PT_Response_Map;


std::map< FluxSlices, MnvH2D*> h_Mig_MuonE_Daisy_Map;
std::map< FluxSlices, MnvH2D*> h_Mig_MuonPZ_Daisy_Map;
std::map< FluxSlices, MnvH2D*> h_Mig_MuonPT_Daisy_Map;
std::map< FluxSlices, MnvH2D*> h_Mig_MuonTheta_Daisy_Map;

PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_PZ_PT(          "h_Muon_PZ_PT",           "h_Muon_PZ_PT",           Pzbin_vector, PTbin_vector , error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_PZ_PT_BG(       "h_Muon_PZ_PT_BG",        "h_Muon_PZ_PT_BG",        Pzbin_vector, PTbin_vector , error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_PZ_PT_TRUE_RECO("h_Muon_PZ_PT_TRUE_RECO", "h_Muon_PZ_PT_TRUE_RECO", Pzbin_vector, PTbin_vector , error_bands);
char Title[1024];
int daisy_N=0;


///2D Petal

for(auto petal:DaisyN){

  sprintf(Title, "h_Muon_PZ_PT_Daisy_%i",daisy_N);
  PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_PZ_PT(Title, Title, Pzbin_vector, PTbin_vector , error_bands);
  h_Muon_PZ_PT_Daisy_Map.insert({petal,  h_Muon_PZ_PT});

  sprintf(Title, "h_Muon_PZ_PT_BG_Daisy_%i",daisy_N);
  PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_PZ_PT_BG(Title, Title, Pzbin_vector, PTbin_vector , error_bands);
  h_Muon_PZ_PT_BG_Daisy_Map.insert({petal,  h_Muon_PZ_PT_BG});

  sprintf(Title, "h_Muon_PZ_PT_TRUE_RECO_Daisy_%i",daisy_N);
  PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_PZ_PT_TRUE_RECO(Title, Title, Pzbin_vector, PTbin_vector , error_bands);
  h_Muon_PZ_PT_TRUE_RECO_Daisy_Map.insert({petal,  h_Muon_PZ_PT_TRUE_RECO});

  sprintf(Title, "MnvR_Muon_PZ_PT_Daisy_%i",daisy_N);
  MinervaUnfold::MnvResponse *MnvR_Muon_PZ_PT    = new MinervaUnfold::MnvResponse( Title, Title, Pzbin_vector,   PTbin_vector,   error_name);
  h_Muon_PZ_PT_Response_Map.insert({petal,  MnvR_Muon_PZ_PT });

  sprintf(Title, "h_MuonE_Daisy_%i",daisy_N);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE(Title, Title, Ebin_1Dvector , error_bands);
  h_MuonE_Daisy_Map.insert({petal,h_MuonE});
  sprintf(Title, "h_MuonE_BG_Daisy_%i",daisy_N);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE_BG(Title, Title, Ebin_1Dvector , error_bands);
  h_MuonE_BG_Daisy_Map.insert({petal,h_MuonE_BG});
  sprintf(Title, "h_MuonE_TRUE_RECO_Daisy_%i",daisy_N);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE_TRUE_RECO(Title, Title, Ebin_1Dvector , error_bands);
  h_MuonE_TRUE_RECO_Daisy_Map.insert({petal,h_MuonE_TRUE_RECO});
  sprintf(Title, "h_MuonPZ_Daisy_%i",daisy_N);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPZ(Title, Title,  Pzbin_1Dvector , error_bands);
  h_MuonPZ_Daisy_Map.insert({petal,h_MuonPZ});
  sprintf(Title, "h_MuonPZ_BG_Daisy_%i",daisy_N);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPZ_BG(Title, Title,  Pzbin_1Dvector , error_bands);
  h_MuonPZ_BG_Daisy_Map.insert({petal,h_MuonPZ_BG});
  sprintf(Title, "h_MuonPZ_TRUE_RECO_Daisy_%i",daisy_N);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPZ_TRUE_RECO(Title, Title,  Pzbin_1Dvector , error_bands);
  h_MuonPZ_TRUE_RECO_Daisy_Map.insert({petal,h_MuonPZ_TRUE_RECO});
  sprintf(Title, "h_MuonPT_Daisy_%i",daisy_N);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPT(Title, Title,  PTbin_1Dvector , error_bands);
  h_MuonPT_Daisy_Map.insert({petal,h_MuonPT});
  sprintf(Title, "h_MuonPT_BG_Daisy_%i",daisy_N);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPT_BG(Title, Title,  PTbin_1Dvector , error_bands);
  h_MuonPT_BG_Daisy_Map.insert({petal,h_MuonPT_BG});
  sprintf(Title, "h_MuonPT_TRUE_RECO_Daisy_%i",daisy_N);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPT_TRUE_RECO(Title, Title,  PTbin_1Dvector , error_bands);
  h_MuonPT_TRUE_RECO_Daisy_Map.insert({petal,h_MuonPT_TRUE_RECO});
  sprintf(Title, "h_MuonTheta_Daisy_%i",daisy_N);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonTheta(Title, Title,  MuonThetabin_1Dvector , error_bands);
  h_MuonTheta_Daisy_Map.insert({petal,h_MuonTheta});
  sprintf(Title, "h_MuonTheta_BG_Daisy_%i",daisy_N);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonTheta_BG(Title, Title,  MuonThetabin_1Dvector , error_bands);
  h_MuonTheta_BG_Daisy_Map.insert({petal,h_MuonTheta_BG});
  sprintf(Title, "h_MuonTheta_TRUE_RECO_Daisy_%i",daisy_N);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonTheta_TRUE_RECO(Title, Title,  MuonThetabin_1Dvector , error_bands);
  h_MuonTheta_TRUE_RECO_Daisy_Map.insert({petal,h_MuonTheta_TRUE_RECO});


  sprintf(Title, "h_Mig_MuonE_Daisy_%i",daisy_N);
  MnvH2D *h_Mig_MuonE_peta      =   new MnvH2D( Title , Title ,  Ebin_1Dvector.size()-1,         Ebin_1Dvector.data(),         Ebin_1Dvector.size()-1,         Ebin_1Dvector.data());
  h_Mig_MuonE_Daisy_Map.insert({petal,h_Mig_MuonE_peta});
  sprintf(Title, "h_Mig_MuonPZ_Daisy_%i",daisy_N);
  MnvH2D *h_Mig_MuonPZ_petal     =   new MnvH2D( Title ,Title ,    Pzbin_1Dvector.size()-1,        Pzbin_1Dvector.data(),        Pzbin_1Dvector.size()-1,        Pzbin_1Dvector.data());
  h_Mig_MuonPZ_Daisy_Map.insert({petal,h_Mig_MuonPZ_petal});
  sprintf(Title, "h_Mig_MuonPT_Daisy_%i",daisy_N);
  MnvH2D *h_Mig_MuonPT_petal     =   new MnvH2D( Title ,Title ,    PTbin_1Dvector.size()-1,        PTbin_1Dvector.data(),        PTbin_1Dvector.size()-1,        PTbin_1Dvector.data());
  h_Mig_MuonPT_Daisy_Map.insert({petal,h_Mig_MuonPT_petal});
  sprintf(Title, "h_Mig_MuonTheta_Daisy_%i",daisy_N);
  MnvH2D *h_Mig_MuonTheta_petal  =   new MnvH2D(Title, Title, MuonThetabin_1Dvector.size()-1, MuonThetabin_1Dvector.data(), MuonThetabin_1Dvector.size()-1, MuonThetabin_1Dvector.data());
   h_Mig_MuonTheta_Daisy_Map.insert({petal,h_Mig_MuonTheta_petal});
   daisy_N++;
}


/// Mnv Response Migration constuctor
//std::map<std::string,MinervaUnfold::MnvResponse*> Response

MinervaUnfold::MnvResponse *MnvR_Muon_PZ_PT    = new MinervaUnfold::MnvResponse( "MnvR_Muon_PZ_PT",     "MnvR_Muon_PZ_PT",     Pzbin_vector,       PTbin_vector,         error_name);
MinervaUnfold::MnvResponse *MnvR_Muon_E_theta  = new MinervaUnfold::MnvResponse( "MnvR_Muon_E_theta",   "MnvR_Muon_E_theta",   Ebin_vector,        MuonThetabin_vector,  error_name);



std::vector<MinervaUnfold::MnvResponse*>  MnvR_vector = {
  MnvR_Muon_PZ_PT,
  MnvR_Muon_E_theta};// , MnvR_cryoVertex_Z_R


PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type> h_Muon_PZ_PT_Material =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type>(MaterialGroup_categories, "h_Muon_PZ_PT_Material",  Pzbin_vector, PTbin_vector  ,"h_Muon_PZ_PT_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type> h_Muon_PZ_PT_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_Muon_PZ_PT_Interaction",  Pzbin_vector, PTbin_vector  ,"h_Muon_PZ_PT_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type> h_Muon_PZ_PT_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type>(ParticleGroup_reduced_categories, "h_Muon_PZ_PT_Particle",  Pzbin_vector, PTbin_vector  ,"h_Muon_PZ_PT_Particle; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, CH_Signal_type> h_Muon_PZ_PT_SignalSelection =
PlotUtils::HistFolio<PlotUtils::MnvH2D, CH_Signal_type>(Signal_Selection_categories, "h_Muon_PZ_PT_SignalSelection",  Pzbin_vector, PTbin_vector  ,"h_Muon_PZ_PT_SignalSelection; [GeV];Events");





PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_E_theta("h_Muon_E_theta", "h_Muon_E_theta",  Ebin_vector , MuonThetabin_vector, error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_E_theta_BG("h_Muon_E_theta_BG", "h_Muon_E_theta_BG",  Ebin_vector , MuonThetabin_vector, error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type> h_Muon_E_theta_Material =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type>(MaterialGroup_categories, "h_Muon_E_theta_Material",  Ebin_vector , MuonThetabin_vector ,"E_theta_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type> h_Muon_E_theta_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_Muon_E_theta_Interaction",  Ebin_vector , MuonThetabin_vector ,"E_theta_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type> h_Muon_E_theta_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type>(ParticleGroup_reduced_categories, "h_Muon_E_theta_Particle",  Ebin_vector , MuonThetabin_vector ,"E_theta_Particle; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, CH_Signal_type> h_Muon_E_theta_SignalSelection =
PlotUtils::HistFolio<PlotUtils::MnvH2D, CH_Signal_type>(Signal_Selection_categories, "h_Muon_E_theta_SignalSelection",  Ebin_vector , MuonThetabin_vector ,"E_theta_SignalSelection; [GeV];Events");



/////////////////////////////////////
//
/////////////////////////////////////

PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE("h_MuonE", "Muon_{E} NEW Method", Ebin_1Dvector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE_BG("h_MuonE_BG", "Muon_{E} NEW Method", Ebin_1Dvector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE_TRUE_RECO("h_MuonE_TRUE_RECO", "Muon_{E} NEW Method", Ebin_1Dvector , error_bands);
/////////////////////////////////////////
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonE_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonE_Material", Ebin_1Dvector ,"MuonE_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonE_Interaction", Ebin_1Dvector ,"MuonE_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_MuonE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_reduced_categories, "h_MuonE_Particle", Ebin_1Dvector ,"MuonE_Particle; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, CH_Signal_type> h_MuonE_SignalSelection =
PlotUtils::HistFolio<PlotUtils::MnvH1D, CH_Signal_type>(Signal_Selection_categories, "h_MuonE_SignalSelection", Ebin_1Dvector ,"h_MuonE_SignalSelection; [GeV];Events");


PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPZ("h_MuonPZ", "Muon_{PZ} NEW Method",  Pzbin_1Dvector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPZ_BG("h_MuonPZ_BG", "Muon_{PZ} NEW Method",  Pzbin_1Dvector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPZ_TRUE_RECO("h_MuonPZ_TRUE_RECO", "Muon_{PZ} NEW Method",  Pzbin_1Dvector , error_bands);


PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonPZ_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonPZ_Material", Pzbin_1Dvector ,"h_MuonPZ_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonPZ_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonPZ_Interaction", Pzbin_1Dvector ,"h_MuonPZ_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_MuonPZ_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_reduced_categories, "h_MuonPZ_Particle", Pzbin_1Dvector ,"h_MuonPZ_Particle; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, CH_Signal_type> h_MuonPZ_SignalSelection =
PlotUtils::HistFolio<PlotUtils::MnvH1D, CH_Signal_type>(Signal_Selection_categories, "h_MuonPZ_SignalSelection", Pzbin_1Dvector ,"h_MuonPZ_SignalSelection; [GeV];Events");

PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPT("h_MuonPT", "Muon_{PT} NEW Method",  PTbin_1Dvector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPT_BG("h_MuonPT_BG", "Muon_{PT} NEW Method",  PTbin_1Dvector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPT_TRUE_RECO("h_MuonPT_TRUE_RECO", "Muon_{PT} NEW Method",  PTbin_1Dvector , error_bands);
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonPT_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonPT_Material", PTbin_1Dvector ,"h_MuonPT_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonPT_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonPT_Interaction", PTbin_1Dvector ,"h_MuonPT_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_MuonPT_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_reduced_categories, "h_MuonPT_Particle", PTbin_1Dvector ,"h_MuonPT_Particle; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, CH_Signal_type> h_MuonPT_SignalSelection =
PlotUtils::HistFolio<PlotUtils::MnvH1D, CH_Signal_type>(Signal_Selection_categories, "h_MuonPT_SignalSelection", PTbin_1Dvector ,"h_MuonPT_SignalSelection; [GeV];Events");



PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonTheta("h_MuonTheta", "MuonTheta [Deg]",  MuonThetabin_1Dvector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonTheta_BG("h_MuonTheta_BG", "MuonTheta [Deg]",  MuonThetabin_1Dvector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonTheta_TRUE_RECO("h_MuonTheta_TRUE_RECO", "MuonTheta [Deg]",  MuonThetabin_1Dvector , error_bands);



PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonTheta_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonTheta_Material", MuonThetabin_1Dvector ,"h_MuonTheta_Material; [Deg];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonTheta_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_MuonTheta_Interaction", MuonThetabin_1Dvector ,"h_MuonTheta_Interaction; [Deg];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_MuonTheta_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_reduced_categories, "h_MuonTheta_Particle", MuonThetabin_1Dvector ,"h_MuonTheta_Particle; [Deg];Events");


PlotUtils::HistFolio<PlotUtils::MnvH1D, CH_Signal_type> h_MuonTheta_SignalSelection =
PlotUtils::HistFolio<PlotUtils::MnvH1D, CH_Signal_type>(Signal_Selection_categories, "h_MuonTheta_SignalSelection", MuonThetabin_1Dvector ,"h_MuonTheta_SignalSelection; [Deg];Events");



PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Theta_TRUE_RECO("h_secTrk_Theta_TRUE_RECO", "h_secTrk_Theta NEW Method",  Vertex_secondTrkTheta_bins , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Theta("h_secTrk_Theta", "h_secTrk_Theta NEW Method",  Vertex_secondTrkTheta_bins , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_Theta_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_Theta_Material", Vertex_secondTrkTheta_bins ,"h_secTrk_Theta_TRUE_Material; [Deg];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_secTrk_Theta_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_secTrk_Theta_Interaction", Vertex_secondTrkTheta_bins ,"h_secTrk_Theta_TRUE_Interaction; [Deg];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_Theta_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_reduced_categories, "h_secTrk_Theta_Particle", Vertex_secondTrkTheta_bins ,"h_secTrk_Theta_TRUE_Particle; [Deg];Events");

PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_tracklength("h_secTrk_tracklength", "Recoil track length  [cm] ", Recoil_track_length_vector , error_bands);
//PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_tracklength_TRUE_RECO("h_secTrk_tracklength_TRUE_RECO", "Recoil track length  [cm] ", Recoil_track_length_vector , error_bands);
//PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_tracklength_TRUE_TRUE_RECO("h_secTrk_tracklength_TRUE_TRUE_RECO", "Recoil track length  [cm] ", Recoil_track_length_vector , error_bands);


//PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_tracklength_Material =
//PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_tracklength_Material", Recoil_track_length_vector ,"h_secTrk_tracklength_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_secTrk_tracklength_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroupDISBreakdown_categories, "h_secTrk_tracklength_Interaction", Recoil_track_length_vector , "h_secTrk_tracklength_Interaction; [cm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_tracklength_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_reduced_categories, "h_secTrk_tracklength_Particle",Recoil_track_length_vector  ,"h_secTrk_tracklength_Particle; [cm];Events");





MnvH2D *h_Mig_MuonE      =   new MnvH2D("h_Mig_MuonE",     "h_Mig_MuonE",     Ebin_1Dvector.size()-1,         Ebin_1Dvector.data(),         Ebin_1Dvector.size()-1,         Ebin_1Dvector.data());
MnvH2D *h_Mig_MuonPZ     =   new MnvH2D("h_Mig_MuonPZ",    "h_Mig_MuonPZ",    Pzbin_1Dvector.size()-1,        Pzbin_1Dvector.data(),        Pzbin_1Dvector.size()-1,        Pzbin_1Dvector.data());
MnvH2D *h_Mig_MuonPT     =   new MnvH2D("h_Mig_MuonPT",    "h_Mig_MuonPT",    PTbin_1Dvector.size()-1,        PTbin_1Dvector.data(),        PTbin_1Dvector.size()-1,        PTbin_1Dvector.data());
MnvH2D *h_Mig_MuonTheta  =   new MnvH2D("h_Mig_MuonTheta", "h_Mig_MuonTheta", MuonThetabin_1Dvector.size()-1, MuonThetabin_1Dvector.data(), MuonThetabin_1Dvector.size()-1, MuonThetabin_1Dvector.data());






std::vector<double> EnergyNu;//{0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0};

double edge = 0;
for(int i = 0; i < 1001; i ++ ){
  EnergyNu.push_back(edge);
  edge = edge + .1;
}
std::vector<double> EnergySlices{0.0,1.0,2.0,3.0,4.0};


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
  int count_cut[10];
  for(int i = 0 ; i < 10 ; i ++ ){count_cut[i]=0;}
  ///////////////////////////////////////////
  ////
  //// Main Event Selection Loop
  ////
  ////
  ///////////////////////////////////////////

  for(int ii=0; ii<chw_MC->GetEntries(); ++ii){

    if(ii%100000==0) std::cout << (ii/100000) << "K " << std::flush;

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
        //if( universe->GetInt("muon_corrected_p") == -999 ) continue;

        bool RECOCut1 = universe->isMINOSMatch_bool();
        //if(RECOCut1==false){std::cout<<" didnt Passed RECOCut1   "<<std::endl; continue;}

        bool RECOCut2 = universe->PassReco();
      //  if(RECOCut2==false){std::cout<<" didnt Passed RECOCut2   "<<std::endl; continue;}

        bool RECOCut3 = universe->Atleast2tracks();
        //if(RECOCut3==false){std::cout<<" didnt Passed RECOCut3   "<<std::endl; continue;}

        bool RECOCut4 = universe->GetDeadTimeCut();
      //  if(RECOCut4==false){std::cout<<" didnt Passed RECOCut4   deadtime =  "<<universe->GetDeadTime() <<std::endl; }

        bool RECOCut5 = universe->TrackerOnly();
        //if(RECOCut5==false){std::cout<<" didnt Passed RECOCut5   "<<std::endl; continue;}

        bool RECOCut6 = universe->InHexagon(850);
      //  if(RECOCut6==false){std::cout<<" didnt Passed RECOCut6   "<<std::endl; continue;}

        bool RECOCut7 = universe->PassThetaCut_heliumlike(universe->GetThetamuDegrees());
        //if(RECOCut7==false){std::cout<<" didnt Passed RECOCut7   "<<std::endl; continue;}

        bool RECOCut8 = universe->IsEmUGoodEnergy_AnaDev();

        bool RECOCut9 = universe->PionRECOtrack_good();

        bool RECOCut10 = universe->IsthereRecoilwithAngleLess(Angle55Deg_inrad);


        //if(RECOCut9==false){continue;}

        bool isneutrino = false;
        bool isCC = false;

      //  if( isCV(*universe)){

      //    if(RECOCut1 = true) {count_cut[0]++;}
      //    if(RECOCut2 = true) {count_cut[1]++;}
      //    if(RECOCut3 = true) {count_cut[2]++;}
      //    if(RECOCut4 = true) {count_cut[3]++;}
      //    if(RECOCut5 = true) {count_cut[4]++;}
      //    if(RECOCut6 = true) {count_cut[5]++;}
      //    if(RECOCut7 = true) {count_cut[6]++;}
      //    if(RECOCut8 = true) {count_cut[7]++;}}


  //  if(ii%1000000==0){
  //     std::cout<< "RECOCut1 = " << RECOCut1 <<" count = " << count_cut[0] <<std::endl;
  //     std::cout<< "RECOCut2 = " << RECOCut2 <<" count = " << count_cut[1] <<std::endl;
  //     std::cout<< "RECOCut3 = " << RECOCut3 <<" count = " << count_cut[2] <<std::endl;
  //     std::cout<< "RECOCut4 = " << RECOCut4 <<" count = " << count_cut[3] <<std::endl;
  //     std::cout<< "RECOCut5 = " << RECOCut5 <<" count = " << count_cut[4] <<std::endl;
  //     std::cout<< "RECOCut6 = " << RECOCut6 <<" count = " << count_cut[5] <<std::endl;
  //     std::cout<< "RECOCut7 = " << RECOCut7 <<" count = " << count_cut[6] <<std::endl;
  //     std::cout<< "RECOCut8 = " << RECOCut8 <<" count = " << count_cut[7] <<std::endl;
  //   }

      if(14== universe->GetTruthNuPDG()){
        isneutrino=true;
      }
      if(1== universe->GetCurrent()){
        isCC=true;
      }




        if(RECOCut1 &&
          RECOCut2 &&
          RECOCut3 &&
          RECOCut4 &&
          RECOCut5 &&
          RECOCut6 &&
          RECOCut7 &&
          RECOCut8 &&
          RECOCut9 &&
          RECOCut10 ){
//std::cout<< " Somthing Passed !!"<< std::endl;

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
             int sectrkindex = universe->FindPionIndex(Angle55Deg_inrad);
             double secondtrkAngle = universe->Get_NonmuTrkANGLE_WRTB_AnaDev(sectrkindex);
             //int secondTrk = universe->Getindex2ndTrackhighestKE();
             const int  unvHist_count1 = MnvReponse_Hist_N_Map[unv_count];
             //std::cout<<"wgt = "<< mvn1wgt<< std::endl;
             h_Muon_PZ_PT.univHist(universe)->Fill(PZ, PT, mvn1wgt);
             h_Muon_E_theta.univHist(universe)->Fill(Emu,Theta_Degs , mvn1wgt);
             h_MuonE.univHist(universe)->Fill(Emu,mvn1wgt);
             h_MuonPZ.univHist(universe)->Fill(PZ,mvn1wgt);
             h_MuonPT.univHist(universe)->Fill(PT,mvn1wgt);
             h_MuonTheta.univHist(universe)->Fill(Theta_Degs,mvn1wgt);
             h_secTrk_Theta.univHist(universe)->Fill(secondtrkAngle,mvn1wgt);
             h_secTrk_tracklength.univHist(universe)->Fill(universe->GetPrimaryProtonTrackLength_cm(),mvn1wgt);

             auto petal = universe->GetRECORegion12DAISY_MasterAna();// multiply from cm to mm

             h_Muon_PZ_PT_Daisy_Map[petal].univHist(universe)->Fill(PZ, PT, mvn1wgt);
             h_MuonE_Daisy_Map[petal].univHist(universe)->Fill(Emu,mvn1wgt);
             h_MuonPZ_Daisy_Map[petal].univHist(universe)->Fill(PZ,mvn1wgt);
             h_MuonPT_Daisy_Map[petal].univHist(universe)->Fill(PT,mvn1wgt);
             h_MuonTheta_Daisy_Map[petal].univHist(universe)->Fill(Theta_Degs,mvn1wgt);


             ///////////////////////////////////////////
             ////
             ////  FILL CV
             ////
             ////
             ///////////////////////////////////////////
             int pdg = universe->getPDG_PionRECOTrack(sectrkindex);
             //std::cout<<"out 5 pdg  = "<< pdg <<std::endl;

           Particle_type Particle_type_Event = GetParticlegroup_typeReduced(pdg);
           //std::cout<<"out 6 Particle_type_Event = "<< Particle_type_Event<<std::endl;
           CH_Signal_type SelectionType = universe->return_CH_Sigal_type(Particle_type_Event);

           if (SelectionType!=kSignal){
             h_Muon_PZ_PT_BG.univHist(universe)->Fill(PZ, PT, mvn1wgt);
             h_Muon_E_theta_BG.univHist(universe)->Fill(Emu,Theta_Degs , mvn1wgt);
             h_MuonE_BG.univHist(universe)->Fill(Emu,mvn1wgt);
             h_MuonPZ_BG.univHist(universe)->Fill(PZ,mvn1wgt);
             h_MuonPT_BG.univHist(universe)->Fill(PT,mvn1wgt);
             h_MuonTheta_BG.univHist(universe)->Fill(Theta_Degs,mvn1wgt);

             h_Muon_PZ_PT_BG_Daisy_Map[petal].univHist(universe)->Fill(PZ, PT, mvn1wgt);
             h_MuonE_BG_Daisy_Map[petal].univHist(universe)->Fill(Emu,mvn1wgt);
             h_MuonPZ_BG_Daisy_Map[petal].univHist(universe)->Fill(PZ,mvn1wgt);
             h_MuonPT_BG_Daisy_Map[petal].univHist(universe)->Fill(PT,mvn1wgt);
             h_MuonTheta_BG_Daisy_Map[petal].univHist(universe)->Fill(Theta_Degs,mvn1wgt);
           }





             if( isCV(*universe)){

              // if(RECOCut1 = true) {count_cut[0]++;}
              // if(RECOCut2 = true) {count_cut[1]++;}
              // if(RECOCut3 = true) {count_cut[2]++;}
              // if(RECOCut4 = true) {count_cut[3]++;}
              // if(RECOCut5 = true) {count_cut[4]++;}
              // if(RECOCut6 = true) {count_cut[5]++;}
              // if(RECOCut7 = true) {count_cut[6]++;}
              // if(RECOCut8 = true) {count_cut[7]++;}

              // std::cout<<"out 1"<<std::endl;
              Interaction_type Interaction_type_Event =  universe->Get_Interaction_withDISbreakdown_AnaDev();
              //double secondtrkAngle = universe->Get_NonmuTrkANGLE_WRTB_AnaDev(sectrkindex);

               //h_Muon_PZ_PT_Material.GetComponentHist(Material_type_Event)->Fill(PZ, PT, mvn1wgt);
               h_Muon_PZ_PT_Interaction.GetComponentHist(Interaction_type_Event)->Fill(PZ, PT, mvn1wgt);
              // std::cout<<"out 8"<<std::endl;

               h_Muon_PZ_PT_Particle.GetComponentHist(Particle_type_Event)->Fill(PZ, PT, mvn1wgt);

               h_Muon_E_theta_Interaction.GetComponentHist(Interaction_type_Event)->Fill(Emu,Theta_Degs,mvn1wgt);
               h_Muon_E_theta_Particle.GetComponentHist(Particle_type_Event)->Fill(Emu,Theta_Degs,mvn1wgt);
               h_MuonE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(Emu, mvn1wgt);
               h_MuonE_Particle.GetComponentHist(Particle_type_Event)->Fill(Emu, mvn1wgt);

               h_MuonPZ_Interaction.GetComponentHist(Interaction_type_Event)->Fill(PZ, mvn1wgt);
               h_MuonPZ_Particle.GetComponentHist(Particle_type_Event)->Fill(PZ, mvn1wgt);

               h_MuonPT_Interaction.GetComponentHist(Interaction_type_Event)->Fill(PT, mvn1wgt);
               h_MuonPT_Particle.GetComponentHist(Particle_type_Event)->Fill(PT, mvn1wgt);

               h_MuonTheta_Interaction.GetComponentHist(Interaction_type_Event)->Fill(Theta_Degs, mvn1wgt);
               h_MuonTheta_Particle.GetComponentHist(Particle_type_Event)->Fill(Theta_Degs, mvn1wgt);

               h_secTrk_Theta_Interaction.GetComponentHist(Interaction_type_Event)->Fill(secondtrkAngle, mvn1wgt);
               h_secTrk_Theta_Particle.GetComponentHist(Particle_type_Event)->Fill(secondtrkAngle, mvn1wgt);

               h_secTrk_tracklength_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetPrimaryProtonTrackLength_cm(), mvn1wgt);
               h_secTrk_tracklength_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetPrimaryProtonTrackLength_cm(), mvn1wgt);


               h_Muon_PZ_PT_SignalSelection.GetComponentHist(SelectionType)->Fill(PZ, PT, mvn1wgt);
               h_Muon_E_theta_SignalSelection.GetComponentHist(SelectionType)->Fill(Emu,Theta_Degs,mvn1wgt);
               h_MuonE_SignalSelection.GetComponentHist(SelectionType)->Fill(Emu, mvn1wgt);
               h_MuonPZ_SignalSelection.GetComponentHist(SelectionType)->Fill(PZ, mvn1wgt);
               h_MuonPT_SignalSelection.GetComponentHist(SelectionType)->Fill(PT, mvn1wgt);
               h_MuonTheta_SignalSelection.GetComponentHist(SelectionType)->Fill(Theta_Degs, mvn1wgt);

             }

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
           if(isneutrino && isCC){
            // std::cout<<" inside TRUTH + RECO"<<std::endl;
          if(RECOCut1 &&
            RECOCut2 &&
            RECOCut3 &&
            RECOCut4 &&
            RECOCut5 &&
            RECOCut6 &&
            RECOCut7 &&
            RECOCut8 &&
            RECOCut9 &&
            RECOCut10
          ){
          //std::cout<<"universe->ShortName() = " << universe->ShortName()<<std::endl;
          // Tell the Event which entry in the TChain it's looking at
          double Emu_TRUE = universe->GetEnuTrue()*.001; // GeV
          double Theta_Degs_TRUE = universe->GetTrueThetamuDegrees(); // Rad

          double MuonPZ_TRUE = universe->GetPmuLongitudinalTrue(); //GeV
          double MuonPT_TRUE = universe->GetPmuTransverseTrue(); // GeV

          //double PhiMuonAngle_TRUE = phi_TRUE * TMath::RadToDeg();

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

          auto petal = universe->GetRECORegion12DAISY_MasterAna();// multiply from cm to mm


          double mvn1wgt = universe->GetWeight(kWeights_v1tune);
          int sectrkindex = universe->FindPionIndex(Angle55Deg_inrad);

          auto reco_index = universe->GET_RECO_index_hadron_GreatestKE();
          auto angle_true =  universe->GETvector_theta_wrtb_FS_particles();
          int newindex1 = universe->GET_index_Pion_InRecoBranch_getTrueTrackID(reco_index);


          h_MuonE_TRUE_RECO.univHist(universe)->Fill(Emu_TRUE,mvn1wgt);

          h_MuonPZ_TRUE_RECO.univHist(universe)->Fill(MuonPZ_TRUE,mvn1wgt);

          h_MuonPT_TRUE_RECO.univHist(universe)->Fill(MuonPT_TRUE,mvn1wgt);

          h_MuonTheta_TRUE_RECO.univHist(universe)->Fill(Theta_Degs_TRUE,mvn1wgt);

          h_Muon_PZ_PT_TRUE_RECO.univHist(universe)->Fill(MuonPZ_TRUE, MuonPT_TRUE, mvn1wgt);

          h_secTrk_Theta_TRUE_RECO.univHist(universe)->Fill(angle_true.at(newindex1-1), mvn1wgt);


          h_Muon_PZ_PT_TRUE_RECO_Daisy_Map[petal].univHist(universe)->Fill(MuonPZ_TRUE, MuonPT_TRUE, mvn1wgt);
          h_MuonE_TRUE_RECO_Daisy_Map[petal].univHist(universe)->Fill(Emu_TRUE,mvn1wgt);
          h_MuonPZ_TRUE_RECO_Daisy_Map[petal].univHist(universe)->Fill(MuonPZ_TRUE,mvn1wgt);
          h_MuonPT_TRUE_RECO_Daisy_Map[petal].univHist(universe)->Fill(MuonPT_TRUE,mvn1wgt);
          h_MuonTheta_TRUE_RECO_Daisy_Map[petal].univHist(universe)->Fill(Theta_Degs_TRUE,mvn1wgt);

          const int  unvHist_count = MnvReponse_Hist_N_Map[unv_count];
          MnvR_Muon_PZ_PT->Fill(PZ, PT, MuonPZ_TRUE, MuonPT_TRUE, universe->ShortName(),unvHist_count,mvn1wgt);
          MnvR_Muon_E_theta->Fill(Emu, Theta_Degs, Emu_TRUE, Theta_Degs_TRUE,universe->ShortName(),unvHist_count,mvn1wgt);

          h_Muon_PZ_PT_Response_Map[petal]->Fill(PZ, PT, MuonPZ_TRUE, MuonPT_TRUE, universe->ShortName(),unvHist_count,mvn1wgt);

         if( isCV(*universe)){
          h_Mig_MuonE->Fill(Emu,Emu_TRUE,mvn1wgt);
          h_Mig_MuonPZ->Fill(PZ,MuonPZ_TRUE,mvn1wgt);
          h_Mig_MuonPT->Fill(PT,MuonPT_TRUE,mvn1wgt);
          h_Mig_MuonTheta->Fill(Theta_Degs,Theta_Degs_TRUE,mvn1wgt);

          h_Mig_MuonE_Daisy_Map[petal]->Fill(Emu,Emu_TRUE,mvn1wgt);
          h_Mig_MuonPZ_Daisy_Map[petal]->Fill(PZ,MuonPZ_TRUE,mvn1wgt);
          h_Mig_MuonPT_Daisy_Map[petal]->Fill(PT,MuonPT_TRUE,mvn1wgt);
          h_Mig_MuonTheta_Daisy_Map[petal]->Fill(Theta_Degs,Theta_Degs_TRUE,mvn1wgt);


        }
      } // End of RECO CUTs
    }// End of TRUTH CUTS



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
h_Muon_E_theta.SyncCVHistos();
h_Muon_PZ_PT_TRUE_RECO.SyncCVHistos();
h_secTrk_tracklength.SyncCVHistos();

h_MuonPZ.SyncCVHistos();
h_MuonPT.SyncCVHistos();
h_MuonE.SyncCVHistos();
h_MuonTheta.SyncCVHistos();

h_MuonPZ_TRUE_RECO.SyncCVHistos();
h_MuonPT_TRUE_RECO.SyncCVHistos();
h_MuonE_TRUE_RECO.SyncCVHistos();
h_secTrk_Theta_TRUE_RECO.SyncCVHistos();
h_MuonTheta_TRUE_RECO.SyncCVHistos();
h_secTrk_Theta.SyncCVHistos();


h_Muon_PZ_PT_BG.SyncCVHistos();
h_Muon_E_theta_BG.SyncCVHistos();
h_MuonE_BG.SyncCVHistos();
h_MuonPZ_BG.SyncCVHistos();
h_MuonPT_BG.SyncCVHistos();
h_MuonTheta_BG.SyncCVHistos();

for(auto petal:DaisyN){
h_Muon_PZ_PT_Daisy_Map[petal].SyncCVHistos();
h_MuonE_Daisy_Map[petal].SyncCVHistos();
h_MuonPZ_Daisy_Map[petal].SyncCVHistos();
h_MuonPT_Daisy_Map[petal].SyncCVHistos();
h_MuonTheta_Daisy_Map[petal].SyncCVHistos();
h_Muon_PZ_PT_BG_Daisy_Map[petal].SyncCVHistos();
h_MuonE_BG_Daisy_Map[petal].SyncCVHistos();
h_MuonPZ_BG_Daisy_Map[petal].SyncCVHistos();
h_MuonPT_BG_Daisy_Map[petal].SyncCVHistos();
h_MuonTheta_BG_Daisy_Map[petal].SyncCVHistos();
h_Muon_PZ_PT_TRUE_RECO_Daisy_Map[petal].SyncCVHistos();
h_MuonE_TRUE_RECO_Daisy_Map[petal].SyncCVHistos();
h_MuonPZ_TRUE_RECO_Daisy_Map[petal].SyncCVHistos();
h_MuonPT_TRUE_RECO_Daisy_Map[petal].SyncCVHistos();
h_MuonTheta_TRUE_RECO_Daisy_Map[petal].SyncCVHistos();
}
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



if(RunwithConvolution==true && useweights==true){
  sprintf(outFileName, "%s/%s_%s_%s_%s_%s_%s_%sFid.root", rootpathway, "MasterAnaDev", c, "RECO_MC", ErrorStatus,Convolution_status_char, weight_status_char, Fid_status_char);
  sprintf(outFileName_pdf, "%s_%s_%s_%s_%s_%s_%sFid.pdf", "Histograms", c, "RECO_MC", ErrorStatus,Convolution_status_char, weight_status_char, Fid_status_char);
}

else if(RunwithConvolution==true && useweights==false){
  sprintf(outFileName, "%s/%s_%s_%s_%s_%s_%sFid_p3.root", rootpathway, "MasterAnaDev", c, "RECO_MC", ErrorStatus,Convolution_status_char, Fid_status_char);
  sprintf(outFileName_pdf, "%s_%s_%s_%s_%s_%sFid_p3.pdf", "Histograms", c, "RECO_MC", ErrorStatus,Convolution_status_char, Fid_status_char);

}
else {  sprintf(outFileName, "%s/%s_%s_%s_%s_%sFid_p3.root", rootpathway, "MasterAnaDev", c, "RECO_MC", ErrorStatus, Fid_status_char);
sprintf(outFileName_pdf, "%s_%s_%s_%s_%s_%sFid_p3.pdf",  "Histograms", c, "RECO_MC", ErrorStatus,Convolution_status_char, Fid_status_char);

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

  //RECO_2DCuts->Write();
  //TRUE_RECO_2DCuts->Write();
  //RECO_Helium_2DCuts->Write();
  //RECO_nonHelium_2DCuts->Write();
  //Truth_2DCuts->Write();


  //////////////////////
  /// 2D
  /////////////////////
  h_Muon_PZ_PT.hist->Write();
  PlotUtils::MnvH2D* h_Muon_PZ_PT_FluxIntegrated = PlotUtils::flux_reweighter(playlist_fluxreweighter, nu_pdg, useNuEconstraint, NFlux_universe).GetIntegratedFluxReweighted(nu_pdg, h_Muon_PZ_PT.hist, Min_NuFluxEnergy, Max_NuFluxEnergy, useMuonCorrelations);
  h_Muon_PZ_PT_FluxIntegrated->Clone()->Write("h_Muon_PZ_PT_FluxIntegrated");

  h_Muon_E_theta.hist->Write();
  PlotUtils::MnvH2D* h_Muon_E_theta_FluxIntegrated = PlotUtils::flux_reweighter(playlist_fluxreweighter, nu_pdg, useNuEconstraint, NFlux_universe).GetIntegratedFluxReweighted(nu_pdg, h_Muon_E_theta.hist, Min_NuFluxEnergy, Max_NuFluxEnergy, useMuonCorrelations);
  h_Muon_E_theta_FluxIntegrated->Clone()->Write("h_Muon_E_theta_FluxIntegrated");
  h_Muon_PZ_PT_TRUE_RECO.hist->Write();

  h_Muon_PZ_PT_BG.hist->Write();
  h_Muon_E_theta_BG.hist->Write();
  h_MuonE_BG.hist->Write();
  h_MuonPZ_BG.hist->Write();
  h_MuonPT_BG.hist->Write();
  h_MuonTheta_BG.hist->Write();

  PlotUtils::MnvH1D* h_MuonE_FluxIntegrated = PlotUtils::flux_reweighter(playlist_fluxreweighter, nu_pdg, useNuEconstraint, NFlux_universe).GetIntegratedFluxReweighted(nu_pdg, h_MuonE.hist, Min_NuFluxEnergy, Max_NuFluxEnergy, useMuonCorrelations);//GetRebinnedFluxReweighted (nu_pdg, h_MuonE.hist);
    h_MuonE_FluxIntegrated->Clone()->Write("h_MuonE_FluxIntegrated");

  PlotUtils::MnvH1D* h_MuonPZ_FluxIntegrated = PlotUtils::flux_reweighter(playlist_fluxreweighter, nu_pdg, useNuEconstraint, NFlux_universe).GetIntegratedFluxReweighted(nu_pdg, h_MuonPZ.hist, Min_NuFluxEnergy, Max_NuFluxEnergy, useMuonCorrelations); //GetRebinnedFluxReweighted (nu_pdg, h_MuonPZ.hist);
    h_MuonPZ_FluxIntegrated->Clone()->Write("h_MuonPZ_FluxIntegrated");

  PlotUtils::MnvH1D* h_MuonPT_FluxIntegrated = PlotUtils::flux_reweighter(playlist_fluxreweighter, nu_pdg, useNuEconstraint, NFlux_universe).GetIntegratedFluxReweighted(nu_pdg, h_MuonPT.hist, Min_NuFluxEnergy, Max_NuFluxEnergy, useMuonCorrelations);//GetRebinnedFluxReweighted(nu_pdg, h_MuonPT.hist);
  h_MuonPT_FluxIntegrated->Clone()->Write("h_MuonPT_FluxIntegrated");

  PlotUtils::MnvH1D* h_MuonTheta_FluxIntegrated = PlotUtils::flux_reweighter(playlist_fluxreweighter, nu_pdg, useNuEconstraint, NFlux_universe).GetIntegratedFluxReweighted(nu_pdg, h_MuonTheta.hist, Min_NuFluxEnergy, Max_NuFluxEnergy, useMuonCorrelations); //GetRebinnedFluxReweighted(nu_pdg, h_MuonTheta.hist);
    h_MuonTheta_FluxIntegrated->Clone()->Write("h_MuonTheta_FluxIntegrated");




    h_MuonE.hist->Write();
    h_MuonPZ.hist->Write();
    h_MuonPT.hist->Write();
    h_MuonTheta.hist->Write();
    h_secTrk_tracklength.hist->Write();
    h_secTrk_Theta.hist->Write();
   //h_Muon_E_theta_TRUE_RECO.hist->Write();
  //h_Muon_E_theta_Interaction.WriteToFile(*outFile);
  h_Muon_E_theta_Particle.WriteToFile(*outFile);


  h_Muon_PZ_PT_Particle.WriteToFile(*outFile);
  h_MuonE_Particle.WriteToFile(*outFile);
  h_MuonPZ_Particle.WriteToFile(*outFile);
  h_MuonPT_Particle.WriteToFile(*outFile);
  h_MuonTheta_Particle.WriteToFile(*outFile);

  h_Muon_PZ_PT_SignalSelection.WriteToFile(*outFile);
  h_Muon_E_theta_SignalSelection.WriteToFile(*outFile);
  h_MuonE_SignalSelection.WriteToFile(*outFile);
  h_MuonPZ_SignalSelection.WriteToFile(*outFile);
  h_MuonPT_SignalSelection.WriteToFile(*outFile);
  h_MuonTheta_SignalSelection.WriteToFile(*outFile);


  h_secTrk_Theta_Interaction.WriteToFile(*outFile);
  h_secTrk_Theta_Particle.WriteToFile(*outFile);

  h_secTrk_tracklength_Interaction.WriteToFile(*outFile);
  h_secTrk_tracklength_Particle.WriteToFile(*outFile);


  h_MuonE_TRUE_RECO.hist->Write();
  h_MuonPZ_TRUE_RECO.hist->Write();
  h_MuonPT_TRUE_RECO.hist->Write();
  h_MuonTheta_TRUE_RECO.hist->Write();
  h_secTrk_Theta_TRUE_RECO.hist->Write();

  for(auto petal:DaisyN){
  h_Muon_PZ_PT_Daisy_Map[petal].hist->Write();
  h_MuonE_Daisy_Map[petal].hist->Write();
  h_MuonPZ_Daisy_Map[petal].hist->Write();
  h_MuonPT_Daisy_Map[petal].hist->Write();
  h_MuonTheta_Daisy_Map[petal].hist->Write();
  h_Muon_PZ_PT_BG_Daisy_Map[petal].hist->Write();
  h_MuonE_BG_Daisy_Map[petal].hist->Write();
  h_MuonPZ_BG_Daisy_Map[petal].hist->Write();
  h_MuonPT_BG_Daisy_Map[petal].hist->Write();
  h_MuonTheta_BG_Daisy_Map[petal].hist->Write();
  h_Muon_PZ_PT_TRUE_RECO_Daisy_Map[petal].hist->Write();
  h_MuonE_TRUE_RECO_Daisy_Map[petal].hist->Write();
  h_MuonPZ_TRUE_RECO_Daisy_Map[petal].hist->Write();
  h_MuonPT_TRUE_RECO_Daisy_Map[petal].hist->Write();
  h_MuonTheta_TRUE_RECO_Daisy_Map[petal].hist->Write();

  h_Mig_MuonE_Daisy_Map[petal]->Write();
  h_Mig_MuonPZ_Daisy_Map[petal]->Write();
  h_Mig_MuonPT_Daisy_Map[petal]->Write();
  h_Mig_MuonTheta_Daisy_Map[petal]->Write();


  }


  h_Muon_PZ_PT_Interaction.WriteToFile(*outFile);
  h_Muon_E_theta_Interaction.WriteToFile(*outFile);
  h_MuonE_Interaction.WriteToFile(*outFile);
  h_MuonPZ_Interaction.WriteToFile(*outFile);
  h_MuonPT_Interaction.WriteToFile(*outFile);
  h_MuonTheta_Interaction.WriteToFile(*outFile);


  h_Muon_PZ_PT_Material.WriteToFile(*outFile);
  h_Muon_E_theta_Material.WriteToFile(*outFile);
  h_MuonE_Material.WriteToFile(*outFile);
  h_MuonPZ_Material.WriteToFile(*outFile);
  h_MuonPT_Material.WriteToFile(*outFile);
  h_MuonTheta_Material.WriteToFile(*outFile);

  h_Mig_MuonE->Write();
  h_Mig_MuonPZ->Write();
  h_Mig_MuonPT->Write();
  h_Mig_MuonTheta->Write();

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


for(auto petal : DaisyN){

MnvH2D *migrationH = NULL;
MnvH2D *h_reco = NULL;
MnvH2D *h_truth = NULL;

bool check = h_Muon_PZ_PT_Response_Map[petal]->GetMigrationObjects(migrationH, h_reco, h_truth );

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
mresp_reco.hist->Write();
mresp_true.hist->Write();

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


for(auto band : error_bands){
  std::vector<HeliumCVUniverse*> band_universes = band.second;
  for(unsigned int i_universe = 0; i_universe < band_universes.size(); ++i_universe){ delete band_universes[i_universe];}
}







TCanvas *can = new TCanvas("can", "can",1800,1600);
sprintf(outFileName_pdf, "%s_%s_%s_%s_%sFid.pdf",  "MasterAnaDev", c, "RECO_MC", ErrorStatus,Convolution_status_char,  Fid_status_char);
can->Print(outFileName_pdf);
can->Close();



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
  //ret_vec.push_back(kFiducialVolume_new );
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
  //weight_vec.push_back(kweight_HeliumTargetMass);
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
  //weight_vec.push_back(kweight_HeliumTargetMass);
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
