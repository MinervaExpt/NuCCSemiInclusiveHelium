// * Uses the New Systematics Framework and "Universe" objects.
// * loop universes, make cuts and fill histograms with the correct lateral
// shifts and weights for each universe.
// * TChain --> PlotUtils::ChainWrapper.
// * MnvHXD --> PlotUtils::HistWrapper.
// * Genie, flux, non-resonant pion, and some detector systematics calculated.
#include "Helium_runEventLoop_SmearingStudy.h"
#include <random>

std::string OUTputRoot_pathway = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles";
//=====================================================
// Functions
//=====================================================
std::vector<ECuts> GetRECOCutsVector();
std::vector<ECuts> GetRECOCutsForEffVector();
std::vector<ECutsTRUTH> GetTRUTHCutsVector();
std::vector<ECutsTRUTH> GetTRUTHCutsVector_Energy();
std::vector<MuonVar> GetMUONVaribles();
std::vector<SecondTrkVar> GetPlayListSecondTrkVector();
std::vector<CryoVertex> GetCryoVertexVaribles();
std::vector<ME_helium_Playlists> GetPlayListVector();

std::vector<Particle_type>  GetParicle_type();
std::vector<Weights> GetWeightVector();
std::vector<Weights> GetWeightVector_v2();
std::vector<Weights> GetWeightVector_mk();
//double Mev_to_GeV=.001;



// Get container of systematic
const bool m_RunCodeWithSystematics = true;
const int n_flux_universes = 10;
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
  PlotUtils::NamedCategory<Interaction_type>({kRes_Coh_Pion},     "1Pion"),
  PlotUtils::NamedCategory<Interaction_type>({kElastic},          "Elastic")
};


const std::vector<PlotUtils::NamedCategory<CryoTank_REGIONS>>
CryoRegionsGroup_categories = {
  PlotUtils::NamedCategory<CryoTank_REGIONS>({kUpstream_head},"Upstream_Bulge"),
  PlotUtils::NamedCategory<CryoTank_REGIONS>({kCenter}, "Center"),
  PlotUtils::NamedCategory<CryoTank_REGIONS>({kDownstream_head},  "Downstream_Bulge"),
  PlotUtils::NamedCategory<CryoTank_REGIONS>({kOUTSIDE},             "Outside"),
};

/*
const std::vector<PlotUtils::NamedCategory<Particle_type>>
ParticleGroup_categories = {
  PlotUtils::NamedCategory<Particle_type>({kParticle_N_A},   "N_A"),
  PlotUtils::NamedCategory<Particle_type>({kParticle_OTHER}, "Other"),
  PlotUtils::NamedCategory<Particle_type>({kElectron},       "Electron"),
  PlotUtils::NamedCategory<Particle_type>({kMuon},           "Muon"),
  PlotUtils::NamedCategory<Particle_type>({kGamma},          "Gamma"),
  PlotUtils::NamedCategory<Particle_type>({kNeutrino_muon}, "Neutrino_muon"),
  PlotUtils::NamedCategory<Particle_type>({kNeutrino_electron}, "Neutrino_electron"),
  PlotUtils::NamedCategory<Particle_type>({kAnti_Neutrino}, "Anti_Neutrino"),
  PlotUtils::NamedCategory<Particle_type>({kKaon},           "Kaon"),
  PlotUtils::NamedCategory<Particle_type>({kPion_0},         "Pi0"),
  PlotUtils::NamedCategory<Particle_type>({kPion_neg},       "Pi^{-}"),
  PlotUtils::NamedCategory<Particle_type>({kPion_pos},       "Pi^{+}"),
  PlotUtils::NamedCategory<Particle_type>({kProton},         "Proton"),
  PlotUtils::NamedCategory<Particle_type>({kNeutron},        "Neutron")
};
*/
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
ParticleGroup_leadingvsnonleading_categories = {
  PlotUtils::NamedCategory<Particle_type>({kParticle_OTHER}, "Other"),
  PlotUtils::NamedCategory<Particle_type>({kPion_0},         "Pi0"),
  PlotUtils::NamedCategory<Particle_type>({kPion_neg},       "Pi^{-}"),
  PlotUtils::NamedCategory<Particle_type>({kPion_pos},       "Pi^{+}"),
  PlotUtils::NamedCategory<Particle_type>({kProton},         "Proton"),
  PlotUtils::NamedCategory<Particle_type>({kNeutron},   "Neutron")
};


std::vector<int> Helium9_colorScheme = {
    TColor::GetColor("#BBCCEE"),  // paleBlue
    TColor::GetColor("#CCEEFF"),  // pale cyan
    TColor::GetColor("#CCDDAA"),  // pale greeen
    TColor::GetColor("#EEEEBB"),  // pale yellow
    TColor::GetColor("#FFCCCC"), // pale red
    TColor::GetColor("#DDDDDD"),  // pale grey
    TColor::GetColor("#222255"),  // dark Blue
    TColor::GetColor("#225555"),  // dark cyan
    TColor::GetColor("#225522"),  // dark green
    TColor::GetColor("#666633"),  // dark yellow
    TColor::GetColor("#66333"),  // dark red
    TColor::GetColor("#555555")  // dark grey
};
std::map< std::string, std::vector<HeliumCVUniverse*> >
  GetErrorBands(PlotUtils::ChainWrapper* chain) {
    typedef std::map< std::string, std::vector<HeliumCVUniverse*> > SystMap;

    SystMap error_bands;

    // CV
    error_bands[std::string("CV")].push_back( new HeliumCVUniverse(chain) );

    //Detector systematics, lateral sh

if(!m_RunCodeWithSystematics){

//    SystMap muonP_systematics = PlotUtils::GetMuonSystematicsMap<HeliumCVUniverse>(chain,NSFDefaults::KludgedMinosMuonMomentum_Err);
  //  error_bands.insert(muonP_systematics.begin(), muonP_systematics.end());
    //std::cout << "C++ make muon resolution systematics" << std::endl;

    ///// MINOS ERROR systems
    SystMap MinervaMuon_systematics = PlotUtils::GetMinervaMuonSystematicsMap<HeliumCVUniverse>(chain);
    error_bands.insert(MinervaMuon_systematics.begin(), MinervaMuon_systematics.end());
    // Minerva Error System

    // MINOS efficiency
    SystMap MinosMuon_systematics = PlotUtils::GetMinosMuonSystematicsMap<HeliumCVUniverse>(chain);
    error_bands.insert(MinosMuon_systematics.begin(), MinosMuon_systematics.end());

    // Muon match efficiency
    SystMap MinosEff_systematics = PlotUtils::GetMinosEfficiencySystematicsMap<HeliumCVUniverse>(chain);
    error_bands.insert(MinosEff_systematics.begin(), MinosEff_systematics.end());

    SystMap flux_systematics = PlotUtils::GetFluxSystematicsMap<HeliumCVUniverse>(chain,n_flux_universes);
    error_bands.insert(flux_systematics.begin(), flux_systematics.end());

    SystMap angle_systematics = PlotUtils::GetAngleSystematicsMap<HeliumCVUniverse>(chain,NSFDefaults::beamThetaX_Err,NSFDefaults::beamThetaY_Err);
    error_bands.insert(angle_systematics.begin(), angle_systematics.end());

    //GENIE
    SystMap genie_systematics = PlotUtils::GetGenieSystematicsMap<HeliumCVUniverse>(chain);
    error_bands.insert(genie_systematics.begin(), genie_systematics.end());


    //std::cout<<"C++ make tune systematics" << std::endl;

    SystMap a2p2h_systematics = PlotUtils::Get2p2hSystematicsMap<HeliumCVUniverse>(chain);
    error_bands.insert(a2p2h_systematics.begin(), a2p2h_systematics.end());

    SystMap RPA_systematics = PlotUtils::GetRPASystematicsMap<HeliumCVUniverse>(chain);
    error_bands.insert(RPA_systematics.begin(), RPA_systematics.end());

    //SystMap LowQ2Pi_systematics = PlotUtils::GetLowQ2PiSystematicsMap<HeliumCVUniverse>(chain);
    //error_bands.insert(LowQ2Pi_systematics.begin(), LowQ2Pi_systematics.end()); // for v2 tune

    //SystMap VertexSmearing_systematics = GetHELIUMVertexSmearingShiftSystematicsMap<HeliumCVUniverse>(chain);
    //error_bands.insert(VertexSmearing_systematics.begin(), VertexSmearing_systematics.end());
    //error_bands[std::string("Vertex_Smearing")].push_back(new VertexSmearingShiftUniverse(chain, -1));
    //error_bands[std::string("Vertex_Smearing")].push_back(new VertexSmearingShiftUniverse(chain, +1));
    SystMap VertexSmearing_systematics = GetHELIUMVertexSmearingShiftSystematicsMap<HeliumCVUniverse>(chain);
    error_bands.insert(VertexSmearing_systematics.begin(), VertexSmearing_systematics.end());

    SystMap HeliumTargetMass_systematics = GetHeliumTargetMassSystematicsMap<HeliumCVUniverse>(chain);
    error_bands.insert(HeliumTargetMass_systematics.begin(), HeliumTargetMass_systematics.end());


}

  // Non-res pi
  //SystMap nonrespi_systematics =
  //  PlotUtils::GetNonResPiSystematicsMap<HeliumCVUniverse>(chain);
  //error_bands.insert(nonrespi_systematics.begin(), nonrespi_systematics.end());

  return error_bands;
}
//======================================================================
//void EventCounter(const HeliumCVUniverse& , std::vector<ECuts> cuts, EventCount_RECO &Event_map ,bool is_mc,HeliumPlayListInfo Info );


// Main
void runEventLoop(bool &m_debugOn, ME_helium_Playlists &PlayList_iterator) {
  // Make a chain of events
  loadLibs();

int Study_cap=50;
int Study_count=0;
double POT[4];
const std::vector<ECuts> kCutsVector = GetRECOCutsVector();
const std::vector<ECuts> kCutsVector_Eff = GetRECOCutsForEffVector();
const std::vector<ECutsTRUTH> kTRUTHCutsVector = GetTRUTHCutsVector_Energy();//GetTRUTHCutsVector();
const std::vector<ECutsTRUTH> kTRUTHCutsVector_Energy =  GetTRUTHCutsVector_Energy();


const std::vector<ME_helium_Playlists> kPlayListVector = GetPlayListVector();


const std::vector<Weights> kWeights_v1tune= GetWeightVector();
const std::vector<Weights> kWeights_v2tune= GetWeightVector_v2();
const std::vector<Weights> kWeights_forMK = GetWeightVector_mk();
const std::vector<MuonVar> kMuonVaribles_vector = GetMUONVaribles();
const std::vector<SecondTrkVar> ksecTrkVaribles_vector = GetPlayListSecondTrkVector();

const std::vector<CryoVertex> kCryoVertexVaribles_vector = GetCryoVertexVaribles();
EventPlaylist_RecoCount EventCountMap;

const std::vector<Particle_type> kSecondary_particle_vector = GetParicle_type();
TH1::AddDirectory(kFALSE);

const double toDegs = 180.0/TMath::Pi();
//======================================================================
////////////////////ADDING TO CHAIN wrapper ///////////////////////////
//======================================================================
bool is_mc= true;
TDatabasePDG *pdg_DATABASEobject = TDatabasePDG::Instance();

MinervaUniverse::SetTruth(false);
MinervaUniverse::SetDeuteriumGeniePiTune(false);
MinervaUniverse::SetNuEConstraint(true);
MinervaUniverse::SetZExpansionFaReweight(false);
MinervaUniverse::SetAnalysisNuPDG(14);
MinervaUniverse::SetNFluxUniverses(n_flux_universes);
std::string playlist = GetPlaylist(PlayList_iterator);
MinervaUniverse::SetPlaylist(playlist);
//MinervaUniverse::Set_Multiple_resetPlaylist(true);

MinervaUniverse::SetNonResPiReweight(true);

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
std::map< std::string, std::vector<HeliumCVUniverse*> > error_bands= GetErrorBands(chw_MC);
//double mcPOT = GetPOT_local(mcchainPOT, "MC");
std::cout<<"Number of Universes set is = "<< 	MinervaUniverse::GetNFluxUniverses()<<std::endl;
//std::cout << "POT of this Playlist = "<< mcPOT <<std::endl;


static weightMK *weight_MK;
char *mparalocation = std::getenv("MPARAMFILESROOT");
string dir_data = string(mparalocation)+"/data/Reweight/";
weight_MK = new weightMK(dir_data + "output_ratio_genie_neut_for_MKmodel.root");

//MinervaUniverse::SetNFluxUniverses(25);
POTCounter pot_counter;

const std::string RootName = GetPlaylist_ROOT_path(PlayList_iterator, is_mc );
//const std::string RootName = GetPlaylist_ROOT_path("1G_pdgcorrection_2",  is_mc );
//const std::string RootName = GetPlaylist_ROOT_path("1G_Bugfix",  is_mc );
//1F_Bugfix
std::cout<<"The Playlist that is set is = "<< playlist.c_str()<<std::endl;
std::cout<<"The Playlist Root = "<< RootName<<std::endl;
 ///pnfs/minerva/persistent/users/cnguyen/ME_G1_Merg/*.root


  auto mcscale = 1.0; //Data_POT_full/ MC_POT_full;


    HeliumPlayListInfo Playlist_Info(playlist);
    std::cout<<"Working with Playlist =  "<<  Playlist_Info.GetPlaylistname()<<std::endl;



//Bins for varibles //
//Muons ///////////////////
std::vector<double> Ebin_vector = GetBinMuonVector(kE);
std::vector<double> Pzbin_vector= GetBinMuonVector(kP_Z);
std::vector<double> PTbin_vector= GetBinMuonVector(kP_T);
std::vector<double> MuonThetabin_vector= GetBinMuonVector(kAngleWRTB);
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
std::vector<double> secTrk_Thetamidbin_vector= GetSecondTrkVarVector(kThetamid);
std::vector<double> secTrk_Theta_TRUEbin_vector= GetSecondTrkVarVector(kFullAngle);


std::vector<double> Vertex_DOCAbin_vector= GetBinMuonVector(kDOCA_muon);
std::vector<double> Vertex_secondTrkEbin_vector = GetSecondTrkVarVector(ksecE_Proton);  //GetSecondTrkVarVector(ksecE);
std::vector<double> Vertex_secondTrkEbin_Proton_vector = GetSecondTrkVarVector(ksecE_Proton);
//std::sort(Vertex_secondTrkEbin_Proton_vector.begin(),Vertex_secondTrkEbin_Proton_vector.end());
std::vector<double> Vertex_secondTrkThetamidbin_vector= GetSecondTrkVarVector(kThetamid);
std::vector<double> secTrk_DOCA_vector= GetSecondTrkVarVector(kDOCA);
std::vector<double> secTrk_Pathway_vector= GetSecondTrkVarVector(kPathway);

std::vector<double> MuonMatchtoMinos_vector= GetBinMuonVector(kMuonMatchtoMinos);
std::vector<double> TrackSize_vector= GetBinMuonVector(ktracksize);
std::vector<double> MuonMatchtoVeto_vector= GetBinMuonVector(kMuonMatchtoVeto);

std::vector<double> secTrk_StartNode_X_vector= GetSecondTrkVarVector(kFirstsecTrk_Xnode);
std::vector<double> secTrk_StartNode_Y_vector= GetSecondTrkVarVector(kFirstsecTrk_Ynode);
std::vector<double> secTrk_StartNode_Z_vector= GetSecondTrkVarVector(kFirstsecTrk_Znode);

std::vector<double> secTrk_LastNodeX_vector= GetSecondTrkVarVector(kLastsecTrk_Xnode);
std::vector<double> secTrk_LastNodeY_vector= GetSecondTrkVarVector(kLastsecTrk_Ynode);
std::vector<double> secTrk_LastNodeZ_vector= GetSecondTrkVarVector(kLastsecTrk_Znode);

std::cout<<"bins"<<std::endl;

std::vector<double> Recoil_track_length_vector;
double recoil_bin_count = 0.0;
for(int ww = 0; ww < 50; ww++ ){
Recoil_track_length_vector.push_back(recoil_bin_count);
recoil_bin_count = recoil_bin_count + 2.54; // bins in [cm]
}

std::vector <True_Event_info> N_A_secTrkParticle;

////////////////
//muon Varibles///
////////////////

PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonMatchtoMinos("h_MuonMatchtoMinos", "Is It Matched (bool)", MuonMatchtoMinos_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE("h_MuonE", "Muon_{E} NEW Method", Ebin_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE_Fake("h_MuonE_Fake", "Muon_{E} NEW Method", Ebin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE_Fake2("h_MuonE_Fake2", "Muon_{E} NEW Method", Ebin_vector , error_bands);
MnvH1D *h_MuonE_MKmodel    =    new MnvH1D("h_MuonE_MKmodel", "h_MuonE_MKmodel", Ebin_vector.size()-1, Ebin_vector.data() );
MnvH1D *h_MuonE_v2tune    =    new MnvH1D("h_MuonE_v2tune", "h_MuonE_v2tune", Ebin_vector.size()-1, Ebin_vector.data() );


PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE_TRUE_RECO("h_MuonE_TRUE_RECO", "Muon_{E} NEW Method", Ebin_vector , error_bands);


PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPZ("h_MuonPZ", "Muon_{PZ} NEW Method",  Pzbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPZ_Fake("h_MuonPZ_Fake", "Muon_{PZ} NEW Method",  Pzbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPZ_Fake2("h_MuonPZ_Fake2", "Muon_{PZ} NEW Method",  Pzbin_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPZ_TRUE_RECO("h_MuonPZ_TRUE_RECO", "Muon_{PZ} NEW Method",  Pzbin_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPT("h_MuonPT", "Muon_{PT} NEW Method",  PTbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPT_Fake("h_MuonPT_Fake", "Muon_{PT} NEW Method",  PTbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPT_Fake2("h_MuonPT_Fake2", "Muon_{PT} NEW Method",  PTbin_vector , error_bands);


PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPT_TRUE_RECO("h_MuonPT_TRUE_RECO", "Muon_{PT} NEW Method",  PTbin_vector , error_bands);


PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonCurvatureSig("h_MuonCurvatureSig", "(q/p) / #sigma(q/p)",  Muon_curvatureSig_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonTheta("h_MuonTheta", "MuonTheta [Deg]",  MuonThetabin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonTheta_Fake("h_MuonTheta_Fake", "MuonTheta [Deg]",  MuonThetabin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonTheta_Fake2("h_MuonTheta_Fake2", "MuonTheta [Deg]",  MuonThetabin_vector , error_bands);


PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonTheta_TRUE_RECO("h_MuonTheta_TRUE_RECO", "MuonTheta [Deg]",  MuonThetabin_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPhi("h_MuonPhi", "Muon Phi [Deg]",  AnglePhi_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPhi_TRUE_RECO("h_MuonPhi_TRUE_RECO", "Muon Phi [Deg]",  AnglePhi_vector , error_bands);



PlotUtils::HistWrapper<HeliumCVUniverse> h_Tracksize("h_Tracksize", "Track size [N]",  TrackSize_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_Tracksize_TRUE_RECO("h_Tracksize_TRUE_RECO", "Tracksize_TRUE_RECO", TrackSize_vector , error_bands);




PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonDOCA("h_MuonDOCA", "Muon_DOCA",  Vertex_DOCAbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonDOCA_TRUE_RECO("h_MuonDOCA_TRUE_RECO", "Muon_DOCA",  Vertex_DOCAbin_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_Nonmuon_VertexTiming("h_Nonmuon_VertexTiming", "h_Nonmuon_VertexTiming",  VectexTiming_vector , error_bands);

//////////////////////////////////////
/////////////Minos/////////////////
//////////////////////////////////
PlotUtils::HistWrapper<HeliumCVUniverse> h_muon_MINOS_E("h_muon_MINOS_E", "Minos Muon_{E} [GeV] ", Ebin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_fitConverge("h_fitConverge", "h_fitConverge",  Vertex_ChiSqFit_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_muon_minosStart_X("h_muon_minosStart_X", "Minos Start X [mm] ", Minos_Start_X_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_muon_minosStart_Y("h_muon_minosStart_Y", "Minos Start Y ", Minos_Start_Y_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_muon_minosStart_Z("h_muon_minosStart_Z", "Minos Start Z ", Minos_Start_Z_vector , error_bands);


PlotUtils::HistWrapper<HeliumCVUniverse> h_muon_minosEnd_X("h_muon_minosEnd_X", "Minos End X ", Minos_End_X_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_muon_minosEnd_Y("h_muon_minosEnd_Y", "Minos End Y ", Minos_End_Y_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_muon_minosEnd_Z("h_muon_minosEnd_Z", "Minos End Z ", Minos_End_Z_vector , error_bands);

/////////////////////////////////////////////////////


PlotUtils::HistWrapper<HeliumCVUniverse> h_muon_StartNode_X("h_muon_StartNode_X", "Muon Starting node X [mm] ",Muon_StartNode_X_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_muon_StartNode_Y("h_muon_StartNode_Y", "Muon Starting node Y [mm] ", Muon_StartNode_X_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_muon_StartNode_Z("h_muon_StartNode_Z", "Muon Starting node Z [mm] ", Muon_StartNode_Z_vector , error_bands);


PlotUtils::HistWrapper<HeliumCVUniverse> h_muon_LastNode_X("h_muon_LastNode_X", "Muon Last node X [mm] ", Muon_LastNode_X_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_muon_LastNode_Y("h_muon_LastNode_Y", "Muon Last node Y [mm] ", Muon_LastNode_Y_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_muon_LastNode_Z("h_muon_LastNode_Z", "Muon Last node Z [mm] ", Muon_LastNode_Z_vector , error_bands);


PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_tracklength("h_secTrk_tracklength", "Recoil track length  [cm] ", Recoil_track_length_vector , error_bands);

//PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_tracklength_upstreamCAP("h_secTrk_tracklength_upstreamCAP", "Recoil track length  [cm] ", Recoil_track_length_vector , error_bands);
//PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_tracklength_Barrel("h_secTrk_tracklength_Barrel", "Recoil track length  [cm] ", Recoil_track_length_vector , error_bands);
//PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_tracklength_downstreamCAP("h_secTrk_tracklength_downstreamCAP", "Recoil track length  [cm] ", Recoil_track_length_vector , error_bands);


PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_tracklength_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_tracklength_Material", Recoil_track_length_vector ,"h_secTrk_tracklength_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_secTrk_tracklength_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_secTrk_tracklength_Interaction", Recoil_track_length_vector , "h_secTrk_tracklength_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_tracklength_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_tracklength_Particle",Recoil_track_length_vector  ,"h_secTrk_tracklength_Particle; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_tracklength_upstreamCAP_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_tracklength_upstreamCAP_Material", Recoil_track_length_vector ,"h_secTrk_tracklength_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_secTrk_tracklength_upstreamCAP_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_secTrk_tracklength_upstreamCAP_Interaction", Recoil_track_length_vector , "h_secTrk_tracklength_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_tracklength_upstreamCAP_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_tracklength_upstreamCAP_Particle",Recoil_track_length_vector  ,"h_secTrk_tracklength_Particle; [mm];Events");


PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_tracklength_downstreamCAP_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_tracklength_downstreamCAP_Material", Recoil_track_length_vector ,"h_secTrk_tracklength_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_secTrk_tracklength_downstreamCAP_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_secTrk_tracklength_downstreamCAP_Interaction", Recoil_track_length_vector , "h_secTrk_tracklength_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_tracklength_downstreamCAP_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_tracklength_downstreamCAP_Particle",Recoil_track_length_vector  ,"h_secTrk_tracklength_Particle; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_tracklength_Barrel_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_tracklength_Barrel_Material", Recoil_track_length_vector ,"h_secTrk_tracklength_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_secTrk_tracklength_Barrel_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_secTrk_tracklength_Barrel_Interaction", Recoil_track_length_vector , "h_secTrk_tracklength_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_tracklength_Barrel_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_tracklength_Barrel_Particle",Recoil_track_length_vector  ,"h_secTrk_tracklength_Particle; [mm];Events");



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


MnvH2D *h2_2ndTrk_length_lastZnode    =    new MnvH2D("h2_2ndTrk_length_lastZnode", "h2_2ndTrk_length_lastZnode",  Pzbin_vector.size()-1,  Pzbin_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );
MnvH2D *h2_2ndTrk_length_firstZnode    =    new MnvH2D("h2_2ndTrk_length_firstZnode", "h2_2ndTrk_length_firstZnode",  Pzbin_vector.size()-1,  Pzbin_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );


///////////////////////////////////////
//
///////////////////////////////////////
////////////////////////////////////////
////Migration Studies
///////////////////////////////////////
MnvH2D *h_Mig_MuonE      =   new MnvH2D("h_Mig_MuonE",     "h_Mig_MuonE",     Ebin_vector.size()-1,         Ebin_vector.data(),         Ebin_vector.size()-1,         Ebin_vector.data());
MnvH2D *h_Mig_MuonPZ     =   new MnvH2D("h_Mig_MuonPZ",    "h_Mig_MuonPZ",    Pzbin_vector.size()-1,        Pzbin_vector.data(),        Pzbin_vector.size()-1,        Pzbin_vector.data());
MnvH2D *h_Mig_MuonPT     =   new MnvH2D("h_Mig_MuonPT",    "h_Mig_MuonPT",    PTbin_vector.size()-1,        PTbin_vector.data(),        PTbin_vector.size()-1,        PTbin_vector.data());
MnvH2D *h_Mig_MuonTheta  =   new MnvH2D("h_Mig_MuonTheta", "h_Mig_MuonTheta", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(), MuonThetabin_vector.size()-1, MuonThetabin_vector.data());


std::vector<double> smearing_x;
std::vector<double> smearing_z;
std::vector<double> smearing_r;

smearing_z.push_back(-1500);
smearing_z.push_back(-1250);
smearing_z.push_back(-1000);
smearing_z.push_back(-750);
smearing_z.push_back(-500);
smearing_z.push_back(-300);
smearing_z.push_back(-200);
smearing_z.push_back(-100);
smearing_z.push_back(0);
smearing_z.push_back(100);
smearing_z.push_back(200);
smearing_z.push_back(300);
smearing_z.push_back(500);
smearing_z.push_back(750);
smearing_z.push_back(1000);
smearing_z.push_back(1250);
smearing_z.push_back(1500);


  smearing_x.push_back(-200);
  smearing_x.push_back(-150);


  double start_vector= -100;

  for(unsigned int i = 0 ; i< 41; i++){
    smearing_x.push_back(start_vector);
    start_vector=start_vector + 5;
  }

  std::vector<double> Vertex_Rbins_vectorMOREbins_vec = {0,50,100,150,200,250,300,350,400,450,500,550,600,650,700,750,800,850,900,950,1000 ,1050,1100,1150,1200,1250};
  std::vector<double> Vertex_RRbins_vectorMOREbins_vec;
  for(auto cat : Vertex_Rbins_vectorMOREbins_vec ) {Vertex_RRbins_vectorMOREbins_vec.push_back(cat * cat);}



  smearing_r.push_back(0);
  smearing_r.push_back(100);
  smearing_r.push_back(200);
  smearing_r.push_back(300);
  smearing_r.push_back(500);
  smearing_r.push_back(750);
  smearing_r.push_back(1000);
  smearing_r.push_back(1250);
  smearing_r.push_back(1500);






  PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_RECO_smearing("h_CryoVertex_X_RECO_smearing", "h_CryoVertex_X_RECO_smearing",  smearing_x , error_bands);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_RECO_smearing("h_CryoVertex_Y_RECO_smearing", "h_CryoVertex_Y_RECO_smearing",  smearing_x , error_bands);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_RECO_smearing("h_CryoVertex_Z_RECO_smearing", "h_CryoVertex_Z_RECO_smearing",  smearing_z , error_bands);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_RECO_smearing("h_CryoVertex_R_RECO_smearing", "h_CryoVertex_R_RECO_smearing",  Vertex_Rbins_vectorMOREbins_vec , error_bands);


  PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS> h_X_RECO_smearing_REGION =
  PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS>(CryoRegionsGroup_categories, "h_X_RECO_smearing_REGION", smearing_x ,"h_X_RECO_smearing_REGION; [mm];Events");

  PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS> h_Y_RECO_smearing_REGION =
  PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS>(CryoRegionsGroup_categories, "h_Y_RECO_smearing_REGION", smearing_x ,"h_Y_RECO_smearing_REGION; [mm];Events");

  PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS> h_Z_RECO_smearing_REGION =
  PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS>(CryoRegionsGroup_categories, "h_Z_RECO_smearing_REGION", smearing_z ,"h_Z_RECO_smearing_REGION; [mm];Events");



    PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS> h_X_TRUE_smearing_REGION =
    PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS>(CryoRegionsGroup_categories, "h_X_TRUE_smearing_REGION", smearing_x ,"h_X_TRUE_smearing_REGION; [mm];Events");

    PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS> h_Y_TRUE_smearing_REGION =
    PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS>(CryoRegionsGroup_categories, "h_Y_TRUE_smearing_REGION", smearing_x ,"h_Y_TRUE_smearing_REGION; [mm];Events");

    PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS> h_Z_TRUE_smearing_REGION =
    PlotUtils::HistFolio<PlotUtils::MnvH1D, CryoTank_REGIONS>(CryoRegionsGroup_categories, "h_Z_TRUE_smearing_REGION", smearing_z ,"h_Z_TRUE_smearing_REGION; [mm];Events");



  PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_RECO_TRUE_smearing("h_CryoVertex_X_RECO_TRUE_smearing", "h_CryoVertex_X_RECO_TRUE_smearing",  smearing_x , error_bands);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_RECO_TRUE_smearing("h_CryoVertex_Y_RECO_TRUE_smearing", "h_CryoVertex_Y_RECO_TRUE_smearing",  smearing_x , error_bands);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_RECO_TRUE_smearing("h_CryoVertex_Z_RECO_TRUE_smearing", "h_CryoVertex_Z_RECO_TRUE_smearing",  smearing_z , error_bands);
  PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_RECO_TRUE_smearing("h_CryoVertex_R_RECO_TRUE_smearing", "h_CryoVertex_R_RECO_TRUE_smearing",  Vertex_Rbins_vectorMOREbins_vec , error_bands);

  MnvH2D *h_Z_Smearing  =   new MnvH2D("h_Z_Smearing", "h_Z_Smearing", Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data(), smearing_z.size()-1, smearing_z.data());

  MnvH2D *h_Z_Mig  =   new MnvH2D("h_Z_Mig", "h_Z_Mig", Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data(), Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());

  std::vector<double> Bins_distance_to_Bulges ={-400,-375,-350,-325,-300,-275,-250,-225,-200,-175,-150,-
  125,-100,-75,-50,-25, 0,25,50,75,100,125,150,175,200,225,250,275,300,325,350,375,400};


  MnvH1D *h_MC_Vertex_distance_upstream      =    new MnvH1D("h_MC_Vertex_distance_upstream", "h_MC_Vertex_distance_upstream", Bins_distance_to_Bulges.size()-1, Bins_distance_to_Bulges.data());
  MnvH1D *h_MC_TRUTH_Vertex_distance_upstream      =    new MnvH1D("h_MC_TRUTH_Vertex_distance_upstream", "h_MC_TRUTH_Vertex_distance_upstream", Bins_distance_to_Bulges.size()-1, Bins_distance_to_Bulges.data());
  MnvH1D *h_MC_TRUTH_Vertex_distance_upstream_Convolution      =    new MnvH1D("h_MC_TRUTH_Vertex_distance_upstream_Convolution", "h_MC_TRUTH_Vertex_distance_upstream_Convolution", Bins_distance_to_Bulges.size()-1, Bins_distance_to_Bulges.data());
  MnvH1D *h_MC_TRUTH_Vertex_distance_upstream_Convolution_toDATA      =    new MnvH1D("h_MC_TRUTH_Vertex_distance_upstream_Convolution_toDATA", "h_MC_TRUTH_Vertex_distance_upstream_Convolution_toDATA", Bins_distance_to_Bulges.size()-1, Bins_distance_to_Bulges.data());
  MnvH1D *h_MC_TRUTH_Vertex_distance_upstream_Convolution_toDATA_2      =    new MnvH1D("h_MC_TRUTH_Vertex_distance_upstream_Convolution_toDATA_2", "h_MC_TRUTH_Vertex_distance_upstream_Convolution_toDATA_2", Bins_distance_to_Bulges.size()-1, Bins_distance_to_Bulges.data());
  MnvH1D *h_secTrk_tracklength_upstreamCAP =    new MnvH1D("h_secTrk_tracklength_upstreamCAP", "h_secTrk_tracklength_upstreamCAP", Recoil_track_length_vector.size()-1, Recoil_track_length_vector.data());


  PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Vertex_distance_upstream_Material =
  PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Vertex_distance_upstream_Material", Bins_distance_to_Bulges ,"h_Vertex_distance_upstream_Material; [mm];Events");

  MnvH1D *h_MC_Vertex_distance_downstream      =    new MnvH1D("h_MC_Vertex_distance_downstream", "h_MC_Vertex_distance_downstream", Bins_distance_to_Bulges.size()-1, Bins_distance_to_Bulges.data());
  MnvH1D *h_MC_TRUTH_Vertex_distance_downstream      =    new MnvH1D("h_MC_TRUTH_Vertex_distance_downstream", "h_MC_TRUTH_Vertex_distance_downstream", Bins_distance_to_Bulges.size()-1, Bins_distance_to_Bulges.data());
  MnvH1D *h_MC_TRUTH_Vertex_distance_downstream_Convolution      =    new MnvH1D("h_MC_TRUTH_Vertex_distance_downstream_Convolution", "h_MC_TRUTH_Vertex_distance_downstream_Convolution", Bins_distance_to_Bulges.size()-1, Bins_distance_to_Bulges.data());
  MnvH1D *h_MC_TRUTH_Vertex_distance_downstream_Convolution_toDATA      =    new MnvH1D("h_MC_TRUTH_Vertex_distance_downstream_Convolution_toDATA", "h_MC_TRUTH_Vertex_distance_downstream_Convolution_toDATA", Bins_distance_to_Bulges.size()-1, Bins_distance_to_Bulges.data());
  MnvH1D *h_secTrk_tracklength_downstreamCAP =    new MnvH1D("h_secTrk_tracklength_downstreamCAP", "h_secTrk_tracklength_downstreamCAP", Recoil_track_length_vector.size()-1, Recoil_track_length_vector.data());



  PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Vertex_distance_downstream_Material =
  PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Vertex_distance_downstream_Material", Bins_distance_to_Bulges ,"h_Vertex_distance_downstream_Material; [mm];Events");




  MnvH1D *h_CryoVertex_R_streaming_Center  =  new MnvH1D("h_CryoVertex_R_streaming_Center",  "h_CryoVertex_R_streaming_Center", Vertex_Rbins_vectorMOREbins_vec.size()-1, Vertex_Rbins_vectorMOREbins_vec.data());
  MnvH1D *h_CryoVertex_R_streaming_TRUTH_Center  =  new MnvH1D("h_CryoVertex_R_streaming_TRUTH_Center",  "h_CryoVertex_R_streaming_TRUTH_Center", Vertex_Rbins_vectorMOREbins_vec.size()-1, Vertex_Rbins_vectorMOREbins_vec.data());
  MnvH1D *h_CryoVertex_R_streaming_TRUTH_Center_Convolution  =  new MnvH1D("h_CryoVertex_R_streaming_TRUTH_Center_Convolution",  "h_CryoVertex_R_streaming_TRUTH_Center_Convolution", Vertex_Rbins_vectorMOREbins_vec.size()-1, Vertex_Rbins_vectorMOREbins_vec.data());
  MnvH1D *h_CryoVertex_R_streaming_TRUTH_Center_Convolution_toData  =  new MnvH1D("h_CryoVertex_R_streaming_TRUTH_Center_Convolution_toData",  "h_CryoVertex_R_streaming_TRUTH_Center_Convolution_toData", Vertex_Rbins_vectorMOREbins_vec.size()-1, Vertex_Rbins_vectorMOREbins_vec.data());
  MnvH1D *h_secTrk_tracklength_Barrel =    new MnvH1D("h_secTrk_tracklength_Barrel", "h_secTrk_tracklength_Barrel", Recoil_track_length_vector.size()-1, Recoil_track_length_vector.data());




  MnvH1D *h_CryoVertex_RR_streaming_Center  =  new MnvH1D("h_CryoVertex_RR_streaming_Center",  "h_CryoVertex_RR_streaming_Center", Vertex_RRbins_vectorMOREbins_vec.size()-1, Vertex_RRbins_vectorMOREbins_vec.data());
  MnvH1D *h_CryoVertex_RR_streaming_TRUTH_Center  =  new MnvH1D("h_CryoVertex_RR_streaming_TRUTH_Center",  "h_CryoVertex_RR_streaming_TRUTH_Center", Vertex_RRbins_vectorMOREbins_vec.size()-1, Vertex_RRbins_vectorMOREbins_vec.data());
  MnvH1D *h_CryoVertex_RR_streaming_TRUTH_Center_Convolution  =  new MnvH1D("h_CryoVertex_RR_streaming_TRUTH_Center_Convolution",  "h_CryoVertex_RR_streaming_TRUTH_Center_Convolution", Vertex_RRbins_vectorMOREbins_vec.size()-1, Vertex_RRbins_vectorMOREbins_vec.data());
  MnvH1D *h_CryoVertex_RR_streaming_TRUTH_Center_Convolution_toData  =  new MnvH1D("h_CryoVertex_RR_streaming_TRUTH_Center_Convolution_toData",  "h_CryoVertex_RR_streaming_TRUTH_Center_Convolution_toData", Vertex_RRbins_vectorMOREbins_vec.size()-1, Vertex_RRbins_vectorMOREbins_vec.data());



  MnvH1D *h_CryoVertex_Z_Center  =  new MnvH1D("h_CryoVertex_Z_Center",  "h_CryoVertex_Z_Center",  Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());
  MnvH1D *h_CryoVertex_Z_Center_TRUTH  =  new MnvH1D("h_CryoVertex_Z_Center_TRUTH",  "h_CryoVertex_Z_Center_TRUTH",  Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());


  PlotUtils::HistFolio<PlotUtils::MnvH1D,Material_type> h_CryoVertex_Z_Center_Material =
  PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Z_Center_Material", Vertex_Zbin_vector ,"h_CryoVertex_Z_Center_Material; [mm];Events");

  MnvH1D *h_CryoVertex_Z_upstream  =  new MnvH1D("h_CryoVertex_Z_upstream",  "h_CryoVertex_Z_upstream",  Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());
  MnvH1D *h_CryoVertex_Z_TRUTH_upstream  =  new MnvH1D("h_CryoVertex_Z_TRUTH_upstream",  "h_CryoVertex_Z_TRUTH_upstream",  Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());



  PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Z_upstream_Material =
  PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Z_upstream_Material", Vertex_Zbin_vector ,"h_CryoVertex_Z_upstream_Material; [mm];Events");

  MnvH1D *h_CryoVertex_Z_downstream  =  new MnvH1D("h_CryoVertex_Z_downstream",  "h_CryoVertex_Z_downstream",  Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());
  MnvH1D *h_CryoVertex_Z_TRUTH_downstream  =  new MnvH1D("h_CryoVertex_Z_TRUTH_downstream",  "h_CryoVertex_Z_TRUTH_downstream",  Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());


  PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Z_downstream_Material =
  PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Z_downstream_Material", Vertex_Zbin_vector ,"h_CryoVertex_Z_downstream_Material; [mm];Events");



////////////////
//Vertex Hist///
////////////////
MnvH1D *h_CryoVertex_X_CV  =  new MnvH1D("h_CryoVertex_X_CV",  "h_CryoVertex_X_CV", Vertex_Xbin_vector.size()-1, Vertex_Xbin_vector.data());
MnvH1D *h_CryoVertex_Y_CV  =  new MnvH1D("h_CryoVertex_Y_CV",  "h_CryoVertex_Y_CV",  Vertex_Ybin_vector.size()-1, Vertex_Ybin_vector.data());
MnvH1D *h_CryoVertex_Z_CV  =  new MnvH1D("h_CryoVertex_Z_CV",  "h_CryoVertex_Z_CV",  Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());

/*
MnvH1D *h_CryoVertex_X_Pos  =  new MnvH1D("h_CryoVertex_X_Pos", "h_CryoVertex_X_Pos", Vertex_Xbin_vector.size()-1, Vertex_Xbin_vector.data());
MnvH1D *h_CryoVertex_X_Neg  =  new MnvH1D("h_CryoVertex_X_Neg", "h_CryoVertex_X_Neg", Vertex_Xbin_vector.size()-1, Vertex_Xbin_vector.data());
MnvH1D *h_CryoVertex_Y_Pos  =  new MnvH1D("h_CryoVertex_Y_Pos", "h_CryoVertex_Y_Pos", Vertex_Ybin_vector.size()-1, Vertex_Ybin_vector.data());
MnvH1D *h_CryoVertex_Y_Neg  =  new MnvH1D("h_CryoVertex_Y_Neg", "h_CryoVertex_Y_Neg", Vertex_Ybin_vector.size()-1, Vertex_Ybin_vector.data());
MnvH1D *h_CryoVertex_Z_Pos  =  new MnvH1D("h_CryoVertex_Z_Pos", "h_CryoVertex_Z_Pos", Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());
MnvH1D *h_CryoVertex_Z_Neg  =  new MnvH1D("h_CryoVertex_Z_Neg", "h_CryoVertex_Z_Neg", Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());
*/



MnvH1D *h_CryoVertex_X_XYshifts  =  new MnvH1D("h_CryoVertex_X_XYshifts", "h_CryoVertex_X_XYshifts", Vertex_Xbin_vector.size()-1, Vertex_Xbin_vector.data());

MnvH1D *h_CryoVertex_X_Zshifts  =  new MnvH1D("h_CryoVertex_X_Zshifts", "h_CryoVertex_X_Zshifts", Vertex_Xbin_vector.size()-1, Vertex_Xbin_vector.data());

MnvH1D *h_CryoVertex_Y_XYshifts  =  new MnvH1D("h_CryoVertex_Y_XYshifts", "h_CryoVertex_Y_XYshifts", Vertex_Ybin_vector.size()-1, Vertex_Ybin_vector.data());

MnvH1D *h_CryoVertex_Y_Zshifts  =  new MnvH1D("h_CryoVertex_Y_Zshifts", "h_CryoVertex_Y_Zshifts", Vertex_Ybin_vector.size()-1, Vertex_Ybin_vector.data());

MnvH1D *h_CryoVertex_Z_XYshifts  =  new MnvH1D("h_CryoVertex_Z_XYshifts", "h_CryoVertex_Z_XYshifts", Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());

MnvH1D *h_CryoVertex_Z_Zshifts  =  new MnvH1D("h_CryoVertex_Z_Zshifts", "h_CryoVertex_Z_Zshifts", Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());




PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X("h_CryoVertex_X", "h_CryoVertex_X",  Vertex_Xbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_TRUE_RECO("h_CryoVertex_X_TRUE_RECO", "h_CryoVertex_X",  Vertex_Xbin_vector , error_bands);


PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_X_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_X_Material", Vertex_Xbin_vector ,"h_CryoVertex_X_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_CryoVertex_X_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_CryoVertex_X_Interaction", Vertex_Xbin_vector ,"h_CryoVertex_X_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_CryoVertex_X_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_CryoVertex_X_Particle", Vertex_Xbin_vector ,"h_CryoVertex_X_Particle; [mm];Events");

//h_CryoVertex_X_Particle.ApplyColorPalette(Helium9_colorScheme);


PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y("h_CryoVertex_Y", "Vertex_Y",  Vertex_Ybin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_TRUE_RECO("h_CryoVertex_Y_TRUE_RECO", "Vertex_Y",  Vertex_Ybin_vector , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Y_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Y_Material", Vertex_Ybin_vector ,"h_CryoVertex_Y_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_CryoVertex_Y_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_CryoVertex_Y_Interaction", Vertex_Ybin_vector ,"h_CryoVertex_Y_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_CryoVertex_Y_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_CryoVertex_Y_Particle", Vertex_Ybin_vector ,"h_CryoVertex_Y_Particle; [mm];Events");

//h_CryoVertex_Y_Particle.ApplyColorPalette(Helium9_colorScheme);


PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z("h_CryoVertex_Z", "Vertex_Z",  Vertex_Zbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_TRUE_RECO("h_CryoVertex_Z_TRUE_RECO", "Vertex_Z",  Vertex_Zbin_vector , error_bands);


PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Z_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Z_Material", Vertex_Zbin_vector ,"h_CryoVertex_Z_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_CryoVertex_Z_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_CryoVertex_Z_Interaction", Vertex_Zbin_vector ,"h_CryoVertex_Z_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_CryoVertex_Z_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_CryoVertex_Z_Particle", Vertex_Zbin_vector ,"h_CryoVertex_Z_Particle; [mm];Events");

//h_CryoVertex_Z_Particle.ApplyColorPalette(Helium9_colorScheme);


PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R("h_CryoVertex_R", "h_CryoVertex_R",  Vertex_Rbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_TRUE_RECO("h_CryoVertex_R_TRUE_RECO", "h_CryoVertex_R",  Vertex_Rbin_vector , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_R_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_R_Material", Vertex_Rbin_vector ,"h_CryoVertex_R_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_CryoVertex_R_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_CryoVertex_R_Interaction", Vertex_Rbin_vector ,"h_CryoVertex_R_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_CryoVertex_R_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_CryoVertex_R_Particle", Vertex_Rbin_vector ,"h_CryoVertex_R_Particle; [mm];Events");

//h_CryoVertex_R_Particle.ApplyColorPalette(Helium9_colorScheme);

PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertexChiSqFit("h_CryoVertexChiSqFit", "h_CryoVertexChiSqFit",  Vertex_ChiSqFit_vector , error_bands);
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertexChiSqFit_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertexChiSqFit_Material", Vertex_ChiSqFit_vector ,"h_CryoVertexChiSqFit_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_CryoVertexChiSqFit_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_CryoVertexChiSqFit_Interaction", Vertex_ChiSqFit_vector ,"h_CryoVertexChiSqFit_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_CryoVertexChiSqFit_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_CryoVertexChiSqFit_Particle", Vertex_ChiSqFit_vector ,"h_CryoVertexChiSqFit_Particle; [mm];Events");
//h_CryoVertexChiSqFit_Particle.ApplyColorPalette(Helium9_colorScheme);

/////////////
//2nd Trk Plots
/////////////


PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Openangle("h_secTrk_Openangle", "h_secTrk openangle NEW Method",  secTrk_Thetamidbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Openangle_TRUE_RECO("h_secTrk_Openangle_TRUE_RECO", "h_secTrk_Openangle ",  secTrk_Theta_TRUEbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Pathlength("h_secTrk_Pathlength", "h_secTrk Pathlength ",  secTrk_Pathway_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Pathlength_TRUE_RECO("h_secTrk_Pathlength_TRUE_RECO", "h_secTrk Pathlength ",  secTrk_Pathway_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_MidTheta("h_secTrk_MidTheta", "h_secTrk_MidTheta NEW Method",  Vertex_secondTrkThetamidbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Theta_TRUE_RECO("h_secTrk_Theta_TRUE_RECO", "h_secTrk_MidTheta NEW Method",  secTrk_Theta_TRUEbin_vector , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Energy("h_secTrk_Energy", "h_secTrk_Energy NEW Method",  Vertex_secondTrkEbin_vector, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Energy_TRUE_RECO("h_secTrk_Energy_TRUE_RECO", "h_secTrk_Energy NEW Method",  Vertex_secondTrkEbin_vector, error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_DOCA("h_secTrk_DOCA", "h_secTrk DOCA NEW Method",  secTrk_DOCA_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_DOCA_TRUE_RECO("h_secTrk_DOCA_TRUE_RECO", "h_secTrk_DOCA_TRUE_RECO",  Vertex_DOCAbin_vector , error_bands);

/////////////////////////////////////////
//TGraph *g_CryoSmearing_vertex_X[4]
//TGraph *g_CryoSmearing_vertex_Y[4]
//TGraph *g_CryoSmearing_vertex_Z[4]
  //=========================================
  // Entry Loop For MC
  //=========================================

  //std::vector<ECuts> kCutsVector;
 std::vector  <ArachnesecTrk> arachneHigh_angle;
 std::vector  <ArachnesecTrk> arachneLow_KE;
 std::vector  <ArachnesecTrk> arachneBoth;
 std::vector <Arachne_alltracks> Arachne_alltrks;
 std::vector <Trajector> All_True_trajectors;
 std::vector <Trajector> All_RECO_trajectors;
 std::vector <TRUE_RECO_Energies_Trajectors> True_Reco_Energies;

  std::vector<Vertex_XYZ> UpstreamBugle_vector;
  std::vector<Vertex_XYZ> UpstreamBugle_vector_He;
  std::vector<Vertex_XYZ> UpstreamBugle_vector_Al;

  std::vector<Vertex_XYZ> DownstreamBugle_vector;
  std::vector<Vertex_XYZ> DownstreamBugle_vector_He;
  std::vector<Vertex_XYZ> DownstreamBugle_vector_Al;

  std::vector<Vertex_XYZ> CenterBugle_vector;
  std::vector<Vertex_XYZ> CenterBugle_vector_He;
  std::vector<Vertex_XYZ> CenterBugle_vector_Al;


  EventCount_RECO EventCounter_EFF;
  EventCount_RECO EventCounter_EFF_TRUTH;
  EventCount_RECO EventCounter_RECO;
  EventCount_Truth EventCounter_TRUTH_total;

// Random Number gen
std::default_random_engine generator;
std::normal_distribution<double> distribution_upstream_RECO(0.0, 105.0); // 0 , 100 best , worst 110
std::normal_distribution<double> distribution_upstream_DATA(125.0, 110.0); // best
std::normal_distribution<double> distribution_upstream_DATA_2(125.0, 105.0);


std::normal_distribution<double> distribution_downstream_RECO(0.0, 52.5); // best
std::normal_distribution<double> distribution_downstream_DATA(35.0, 45.0); // best 40,45 // worst 35,65

std::normal_distribution<double> distribution_BarrelR_RECO(0.0, 20); // 25
std::normal_distribution<double> distribution_BarrelR_DATA(0.0, 75); // BEST 85

std::normal_distribution<double> distribution_BarrelRR_RECO(0.0, 400); //
std::normal_distribution<double> distribution_BarrelRR_DATA(0.0, 4900); // old 120




  std::cout << "size of vector " << kCutsVector.size()<<std::endl;
  for (auto cut : kCutsVector){
  std::cout<<" count= "<<cut<<std::endl;
  EventCounter_RECO[cut]=0.0;
  }


  std::cout << "size of vector for EFF " << kCutsVector_Eff.size()<<std::endl;
  for (auto cut : kCutsVector_Eff){
  std::cout<<" count= "<<cut<<std::endl;
   EventCounter_EFF[cut]=0.0;
   EventCounter_EFF_TRUTH[cut]=0.0;
  }

  std::cout << "size of  TRUTH CUT vector " << kTRUTHCutsVector.size()<<std::endl;
  for (auto cut : kTRUTHCutsVector){
  std::cout<<" count= "<<cut<<std::endl;
   EventCounter_TRUTH_total[cut]=0.0;
  }




  ProcInfo_t procInfo;
  gSystem->GetProcInfo(&procInfo);

std::string sysmatics_status;
if(m_RunCodeWithSystematics==true){sysmatics_status= "Systematics On";}
else if (m_RunCodeWithSystematics==false){sysmatics_status= "Systematics Off";}
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;
std::cout<<"~~~~~~~~~  "<< sysmatics_status <<" ~~~~~~~~~ "<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;


int PDG_notmatch=0;
int PDG_match=0;

  std::cout << "Memory/time used so Far: " << procInfo.fMemResident/1000<< " MB" <<" time = "<<  procInfo.fCpuSys <<  " Sec"<<"\n";

  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"MC LOOP  "<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  double Pi = 3.14159265358979323846;
  for(int ii=0; ii<chw_MC->GetEntries(); ++ii){

    if(ii%1000==0) std::cout << (ii/100) << " k " << std::endl;

    //=========================================
    // For every systematic, loop over the universes, and fill the
    // appropriate histogram in the MnvH1D
    //=========================================

    for (auto band : error_bands){
        //std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
      std::vector<HeliumCVUniverse*> error_band_universes = band.second;
      for (auto universe : error_band_universes){

        // Tell the Event which entry in the TChain it's looking at
        universe->SetEntry(ii);

///////////////////////////////////////////
////
////  FILL CV
////
////
///////////////////////////////////////////


        if( universe->ShortName() == "cv"){
          EventCounter_TRUTH(*universe, kTRUTHCutsVector, EventCounter_TRUTH_total, universe->GetWeight(kWeights_v1tune) );
          EventCounter(*universe, kCutsVector, EventCounter_RECO, is_mc, Playlist_Info );
          EventCounter_RECO_TRUTHApplied(*universe, kTRUTHCutsVector,
            kCutsVector_Eff, EventCounter_EFF_TRUTH,
            EventCounter_EFF ,is_mc, kWeights_v1tune);

            auto PDG_trklist = universe->GetVector_nonMuonTk_PDG();
            auto Energy_trklist = universe-> GetVector_nonMuonTk_Energy_GeV();
            auto Angle_trklist = universe->GetVector_nonMuonTk_Angle_wrtb_Degs();
            auto EnergyFraction_vector = universe->Get_TrueFractionE_vector();
            //int secondTrk = universe->Getindex2ndTrackhighestKE();

            //int secondTrk = universe->Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_lessthanAngle_muonNotinlist(PDG_trklist, Energy_trklist, Angle_trklist, EnergyFraction_vector);
            int secondTrk = universe-> Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_lessthanAngle_muonNotinlist_KE_proton_pion_thrusthold(PDG_trklist, Energy_trklist, Angle_trklist,EnergyFraction_vector);
            if(secondTrk==-999)continue;

            Interaction_type Interaction_type_Event =  universe->Get_InteractionStackType();
            Material_type Material_type_Event = universe->Get_MaterialStackType();
            int secTrk_PDG = PDG_trklist.at(secondTrk);
            Particle_type Particle_type_Event =  GetParticlegroup_type(secTrk_PDG);

            double Theta = universe->GetThetamu();
            double Pmu = universe -> GetPmu()/1000;

            if(  PassesCutsRECO(*universe,  is_mc , kCutsVector) ){

              double weight_forMK = universe->GetWeight(kWeights_forMK);
              double MK_Weight = universe->GetMKmodelWeight_local(weight_MK);

              h_MuonE_v2tune->Fill(universe->GetMuonE_ECT(),universe->GetWeight(kWeights_v2tune));
              h_MuonE_MKmodel->Fill(universe->GetMuonE_ECT(),weight_forMK*weight_forMK);
              h_CryoVertex_Z_CV->Fill(universe->GetVertex_z(),universe->GetWeight(kWeights_v1tune));
              h_CryoVertex_X_CV->Fill(universe->GetVertex_x(),universe->GetWeight(kWeights_v1tune));
              h_CryoVertex_Y_CV->Fill(universe->GetVertex_y(),universe->GetWeight(kWeights_v1tune));

              auto CryoTank_REGIONS_MC =  Bulge_Regions_of_CryoTank(universe->GetVertex_z());
              auto CryoTank_Barrel_REGIONS_MC = Barrel_Region_of_CryoTank(universe->GetVertex_z());



              if(CryoTank_REGIONS_MC==kUpstream_head && Cylindrical_CutAboutZero(*universe) == true){
                auto distance = DistanceFromUpStreamBulge(universe->GetVertex_z() , universe->GetVertex_r());
                auto distance_TRUE = DistanceFromUpStreamBulge(universe->GetTRUE_Vertex_z() , universe->GetTRUE_Vertex_r());
                double Random_Norm_number = distribution_upstream_RECO(generator);
                double Random_Norm_number_data = distribution_upstream_DATA(generator);
                double Random_Norm_number_data_2 = distribution_upstream_DATA_2(generator);

                h_MC_Vertex_distance_upstream->Fill(distance, universe->GetWeight(kWeights_v1tune));
                h_MC_TRUTH_Vertex_distance_upstream->Fill(distance_TRUE, universe->GetWeight(kWeights_v1tune));
                h_MC_TRUTH_Vertex_distance_upstream_Convolution->Fill(distance_TRUE+Random_Norm_number, universe->GetWeight(kWeights_v1tune));
                //h_MC_TRUTH_Vertex_distance_upstream_Convolution->Fill(distance_TRUE-Random_Norm_number, universe->GetWeight(kWeights_v1tune));
                h_MC_TRUTH_Vertex_distance_upstream_Convolution_toDATA->Fill(distance_TRUE+Random_Norm_number_data, universe->GetWeight(kWeights_v1tune));
                h_MC_TRUTH_Vertex_distance_upstream_Convolution_toDATA_2->Fill(distance_TRUE+Random_Norm_number_data_2, universe->GetWeight(kWeights_v1tune));


                h_Vertex_distance_upstream_Material.GetComponentHist(Material_type_Event)->Fill(distance, universe->GetWeight(kWeights_v1tune));
                h_CryoVertex_Z_upstream->Fill(universe->GetVertex_z(), universe->GetWeight(kWeights_v1tune));
                h_CryoVertex_Z_TRUTH_upstream->Fill(universe->GetTRUE_Vertex_z(), universe->GetWeight(kWeights_v1tune));
                h_CryoVertex_Z_upstream_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetVertex_z(), universe->GetWeight(kWeights_v1tune));

                h_secTrk_tracklength_upstreamCAP_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetNonmuTrkLength_InMinerva_Incm(secondTrk), universe->GetWeight(kWeights_v1tune));
                h_secTrk_tracklength_upstreamCAP_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetNonmuTrkLength_InMinerva_Incm(secondTrk), universe->GetWeight(kWeights_v1tune));
                h_secTrk_tracklength_upstreamCAP_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetNonmuTrkLength_InMinerva_Incm(secondTrk), universe->GetWeight(kWeights_v1tune));
                h_secTrk_tracklength_upstreamCAP->Fill(universe->GetNonmuTrkLength_InMinerva_Incm(secondTrk), universe->GetWeight(kWeights_v1tune));


                Vertex_XYZ XYZinput{universe->GetVertex_x(),universe->GetVertex_y(),universe->GetVertex_z()};
                UpstreamBugle_vector.push_back(XYZinput);
                if(Material_type_Event==kHelium){UpstreamBugle_vector_He.push_back(XYZinput);}
                else if(Material_type_Event==kAluminium){UpstreamBugle_vector_Al.push_back(XYZinput);}

              }
              else if(CryoTank_REGIONS_MC==kDownstream_head && Cylindrical_CutAboutZero(*universe)== true){
                double Random_Norm_number = distribution_downstream_RECO(generator);
                double Random_Norm_number_todata = distribution_downstream_DATA(generator);

                auto distance = DistanceFromDownStreamBulge(universe->GetVertex_z() , universe->GetVertex_r());
                auto distance_TRUE = DistanceFromDownStreamBulge(universe->GetTRUE_Vertex_z() , universe->GetTRUE_Vertex_r());
                 h_MC_Vertex_distance_downstream->Fill(distance, universe->GetWeight(kWeights_v1tune));
                 h_MC_TRUTH_Vertex_distance_downstream->Fill(distance_TRUE, universe->GetWeight(kWeights_v1tune));
                 h_MC_TRUTH_Vertex_distance_downstream_Convolution->Fill(distance_TRUE + Random_Norm_number, universe->GetWeight(kWeights_v1tune));
                 h_MC_TRUTH_Vertex_distance_downstream_Convolution_toDATA->Fill(distance_TRUE + Random_Norm_number_todata, universe->GetWeight(kWeights_v1tune));

                 h_Vertex_distance_downstream_Material.GetComponentHist(Material_type_Event)->Fill(distance, universe->GetWeight(kWeights_v1tune));

                 h_CryoVertex_Z_downstream->Fill(universe->GetVertex_z(), universe->GetWeight(kWeights_v1tune));
                 h_CryoVertex_Z_TRUTH_downstream->Fill(universe->GetTRUE_Vertex_z(), universe->GetWeight(kWeights_v1tune));
                 h_CryoVertex_Z_downstream_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetVertex_z(), universe->GetWeight(kWeights_v1tune));

                 h_secTrk_tracklength_downstreamCAP_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetNonmuTrkLength_InMinerva_Incm(secondTrk), universe->GetWeight(kWeights_v1tune));
                 h_secTrk_tracklength_downstreamCAP_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetNonmuTrkLength_InMinerva_Incm(secondTrk), universe->GetWeight(kWeights_v1tune));
                 h_secTrk_tracklength_downstreamCAP_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetNonmuTrkLength_InMinerva_Incm(secondTrk), universe->GetWeight(kWeights_v1tune));
                 h_secTrk_tracklength_downstreamCAP->Fill(universe->GetNonmuTrkLength_InMinerva_Incm(secondTrk), universe->GetWeight(kWeights_v1tune));


                 Vertex_XYZ XYZinput{universe->GetVertex_x(),universe->GetVertex_y(),universe->GetVertex_z()};
                 DownstreamBugle_vector.push_back(XYZinput);
                 if(Material_type_Event==kHelium){DownstreamBugle_vector_He.push_back(XYZinput);}
                 else if(Material_type_Event==kAluminium){DownstreamBugle_vector_Al.push_back(XYZinput);}

               }
                 if(CryoTank_Barrel_REGIONS_MC==kCenter){
                   double Random_Norm_numberR = distribution_BarrelR_RECO(generator);
                   double Random_Norm_numberR_todata = distribution_BarrelR_DATA(generator);

                   double Random_Norm_numberRR = distribution_BarrelRR_RECO(generator);
                   double Random_Norm_numberRR_todata = distribution_BarrelRR_DATA(generator);

                   double TRUE_r =  universe->GetTRUE_Vertex_r();
                   double TRUE_rr = universe->GetTRUE_Vertex_rr();

                   h_CryoVertex_R_streaming_TRUTH_Center_Convolution->Fill(TRUE_r + Random_Norm_numberR, universe->GetWeight(kWeights_v1tune));
                   h_CryoVertex_R_streaming_TRUTH_Center_Convolution_toData->Fill(TRUE_r + Random_Norm_numberR_todata, universe->GetWeight(kWeights_v1tune));

                   h_CryoVertex_RR_streaming_TRUTH_Center_Convolution->Fill(TRUE_rr + Random_Norm_numberRR, universe->GetWeight(kWeights_v1tune));
                   h_CryoVertex_RR_streaming_TRUTH_Center_Convolution_toData->Fill(TRUE_rr + Random_Norm_numberRR_todata, universe->GetWeight(kWeights_v1tune));

                   h_CryoVertex_R_streaming_Center->Fill(universe->GetVertex_r(), universe->GetWeight(kWeights_v1tune));
                   h_CryoVertex_RR_streaming_Center->Fill(universe->GetVertex_rr(), universe->GetWeight(kWeights_v1tune));
                   h_CryoVertex_R_streaming_TRUTH_Center->Fill(TRUE_r, universe->GetWeight(kWeights_v1tune));
                   h_CryoVertex_RR_streaming_TRUTH_Center->Fill(TRUE_rr, universe->GetWeight(kWeights_v1tune));
                   h_CryoVertex_Z_Center->Fill(universe->GetVertex_z(), universe->GetWeight(kWeights_v1tune));
                   h_CryoVertex_Z_Center_TRUTH->Fill(universe->GetTRUE_Vertex_z(), universe->GetWeight(kWeights_v1tune));
                   h_CryoVertex_Z_Center_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetVertex_z(), universe->GetWeight(kWeights_v1tune));
                   h_secTrk_tracklength_Barrel->Fill(universe->GetNonmuTrkLength_InMinerva_Incm(secondTrk), universe->GetWeight(kWeights_v1tune));

                   h_secTrk_tracklength_Barrel_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetNonmuTrkLength_InMinerva_Incm(secondTrk), universe->GetWeight(kWeights_v1tune));
                   h_secTrk_tracklength_Barrel_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetNonmuTrkLength_InMinerva_Incm(secondTrk), universe->GetWeight(kWeights_v1tune));
                   h_secTrk_tracklength_Barrel_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetNonmuTrkLength_InMinerva_Incm(secondTrk), universe->GetWeight(kWeights_v1tune));

                   Vertex_XYZ XYZinput{universe->GetVertex_x(),universe->GetVertex_y(),universe->GetVertex_z()};
                   CenterBugle_vector.push_back(XYZinput);

                   if(Material_type_Event==kHelium){CenterBugle_vector_He.push_back(XYZinput);}
                   else if(Material_type_Event==kAluminium){CenterBugle_vector_Al.push_back(XYZinput);}

                 }

            }//END of RECO CUTs
            ////////////////////////////////////Truth Cuts

            if(PassesCutsTRUTH(*universe, kTRUTHCutsVector)){
              if( PassesCutsRECO(*universe,  is_mc , kCutsVector_Eff) ){

                //int secondTrk = universe->Getindex2ndTrack_TRUE_highestKE();
                auto PDG_trklist = universe->GetVector_nonMuonTk_PDG();
                auto Energy_trklist = universe-> GetVector_nonMuonTk_Energy_GeV();

                auto input_type =  universe->GetNon_muon_PDG(secondTrk);
                int index_trajector = universe->getindexTrueTrajectors_closestRECO();
                int pdg_trajector = universe->Get_index_Trajector_PDG(index_trajector);
                auto EnergyFraction_vector = universe->Get_TrueFractionE_vector();

            //unsigned int secondTrk = universe->Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_lessthanAngle_muonNotinlist(PDG_trklist, Energy_trklist, Angle_trklist,, EnergyFraction_vector);
              unsigned int secondTrk = universe-> Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_lessthanAngle_muonNotinlist_KE_proton_pion_thrusthold(PDG_trklist, Energy_trklist, Angle_trklist, EnergyFraction_vector);
              if(secondTrk==-999)continue;
              int secTrk_PDG = PDG_trklist.at(secondTrk);
              double secTrkAngle  = Angle_trklist.at(secondTrk);
              double secTrkKE = Energy_trklist.at(secondTrk);

                Particle_type Particle_type_Event = GetParticlegroup_type(secTrk_PDG);
                Particle_type GroupType = Particle_type_Event;

                Interaction_type Interaction_type_Event =  universe->Get_InteractionStackType();
                Material_type Material_type_Event = universe->Get_MaterialStackType();

                int run = universe->GetRunN();
                int subrun = universe->GetSubRunN();
                int gate = universe->GetGateN();
                int slice  = universe->GetSliceN();

                double smear_x = universe->GetTRUE_Vertex_x() - universe->GetVertex_x();
                double smear_y = universe->GetTRUE_Vertex_y() - universe->GetVertex_y();
                double smear_z = universe->GetTRUE_Vertex_z() - universe->GetVertex_z();
                double smear_r = universe->GetTRUE_Vertex_r() - universe->GetVertex_r();

                h_Mig_MuonE->Fill(universe->GetEmu()*.001,universe->GetTRUE_Emu(),universe->GetWeight(kWeights_v1tune));
                h_Mig_MuonPZ->Fill(Pmu*std::cos(Theta),universe->GetPmuLongitudinalTrue(),universe->GetWeight(kWeights_v1tune));
                h_Mig_MuonPT->Fill(Pmu*std::sin(Theta),universe->GetPmuTransverseTrue(),universe->GetWeight(kWeights_v1tune));
                h_Mig_MuonTheta->Fill(Theta*toDegs,universe->GetTRUE_muANGLE_WRTB_DEG(),universe->GetWeight(kWeights_v1tune));
                h_Z_Mig->Fill(universe->GetVertex_z(),universe->GetTRUE_Vertex_z(),universe->GetWeight(kWeights_v1tune));

                auto RECO_TANK_REGION = universe->Get_RECO_CryoTank_region();
                auto TRUE_TANK_REGION = universe->Get_TRUE_CryoTank_region();

                h_X_RECO_smearing_REGION.GetComponentHist(RECO_TANK_REGION)->Fill(smear_x, universe->GetWeight(kWeights_v1tune));
                h_Y_RECO_smearing_REGION.GetComponentHist(RECO_TANK_REGION)->Fill(smear_y, universe->GetWeight(kWeights_v1tune));
                h_Z_RECO_smearing_REGION.GetComponentHist(RECO_TANK_REGION)->Fill(smear_z, universe->GetWeight(kWeights_v1tune));

                h_X_TRUE_smearing_REGION.GetComponentHist(TRUE_TANK_REGION)->Fill(smear_x, universe->GetWeight(kWeights_v1tune));
                h_Y_TRUE_smearing_REGION.GetComponentHist(TRUE_TANK_REGION)->Fill(smear_y, universe->GetWeight(kWeights_v1tune));
                h_Z_TRUE_smearing_REGION.GetComponentHist(TRUE_TANK_REGION)->Fill(smear_z, universe->GetWeight(kWeights_v1tune));
                h_Z_Smearing->Fill(universe->GetTRUE_Vertex_z(), smear_z,universe->GetWeight(kWeights_v1tune));

              }//End of Reco CUTs

            }//end of Truth Cuts
          }


        ///////////////////////////////////////////
        ////
        ////  END OF CV
        ////
        ////
        ///////////////////////////////////////////


if( universe->ShortName() == "VertexSmearingR"){
  if(  PassesCutsRECO(*universe,  is_mc , kCutsVector) ){
    h_CryoVertex_Z_XYshifts->Fill(universe->GetVertex_z(),universe->GetWeight(kWeights_v1tune));
    h_CryoVertex_X_XYshifts->Fill(universe->GetVertex_x(),universe->GetWeight(kWeights_v1tune));
    h_CryoVertex_Y_XYshifts->Fill(universe->GetVertex_y(),universe->GetWeight(kWeights_v1tune));
  }
}


if( universe->ShortName() == "VertexSmearingZ"){
  if(  PassesCutsRECO(*universe,  is_mc , kCutsVector) ){
    h_CryoVertex_Z_Zshifts->Fill(universe->GetVertex_z(),universe->GetWeight(kWeights_v1tune));
    h_CryoVertex_X_Zshifts->Fill(universe->GetVertex_x(),universe->GetWeight(kWeights_v1tune));
    h_CryoVertex_Y_Zshifts->Fill(universe->GetVertex_y(),universe->GetWeight(kWeights_v1tune));
  }
}



        //std::cout<< "GetMuonAngleWRTB() > 12.0" << universe->GetMuonAngleWRTB() <<std::endl;
        //=========================================
        // CUTS in each universe
        //=========================================

      if(  PassesCutsRECO(*universe,  is_mc , kCutsVector) ){

       //std::cout<<"(inside universe looping)Universe Name:" << universe->ShortName()<<std::endl;
        //  if(PassesCuts_MC(*universe)){

        double Theta = universe->GetThetamu();
        double Pmu = universe -> GetPmu()/1000;
        int secondTrk = universe->Getindex2ndTrackhighestKE();
        double weight_forMK = 1.0; //universe->GetWeight(kWeights_forMK);

        double MK_Weight = universe->GetMKmodelWeight_local(weight_MK);


        h_MuonE.univHist(universe)->Fill(universe->GetEmu()*.001,universe->GetWeight(kWeights_v1tune));
        h_MuonPZ.univHist(universe)->Fill(Pmu*std::cos(Theta),universe->GetWeight(kWeights_v1tune));
        h_MuonPT.univHist(universe)->Fill(Pmu*std::sin(Theta),universe->GetWeight(kWeights_v1tune));
        h_MuonTheta.univHist(universe)->Fill(Theta*toDegs,universe->GetWeight(kWeights_v1tune));


        h_MuonE_Fake.univHist(universe)->Fill(universe->GetMuonE_ECT(),universe->GetWeight(kWeights_v2tune));

        h_MuonPZ_Fake.univHist(universe)->Fill(universe->GetMuonPz_ECT(),universe->GetWeight(kWeights_v2tune));

        h_MuonPT_Fake.univHist(universe)->Fill(universe->GetMuonPt_ECT(),universe->GetWeight(kWeights_v2tune));

        h_MuonTheta_Fake.univHist(universe)->Fill(universe->GetmuAngleWRTB_Degs(),MK_Weight * universe->GetWeight(kWeights_v2tune));

        h_MuonE_Fake2.univHist(universe)->Fill(universe->GetMuonE_ECT(),MK_Weight*weight_forMK);

        h_MuonPZ_Fake2.univHist(universe)->Fill(universe->GetMuonPz_ECT(),MK_Weight*weight_forMK);

        h_MuonPT_Fake2.univHist(universe)->Fill(universe->GetMuonPt_ECT(),MK_Weight*weight_forMK);

        h_MuonTheta_Fake2.univHist(universe)->Fill(universe->GetmuAngleWRTB_Degs(),MK_Weight*weight_forMK);

        h_CryoVertex_X.univHist(universe)->Fill(universe->GetVertex_x(),universe->GetWeight(kWeights_v1tune));

        h_CryoVertex_Y.univHist(universe)->Fill(universe->GetVertex_y(),universe->GetWeight(kWeights_v1tune));

        h_CryoVertex_Z.univHist(universe)->Fill(universe->GetVertex_z(),universe->GetWeight(kWeights_v1tune));

        h_CryoVertex_R.univHist(universe)->Fill(universe->GetVertex_r(),universe->GetWeight(kWeights_v1tune));


        double smear_x = universe->GetTRUE_Vertex_x() - universe->GetVertex_x();
        double smear_y = universe->GetTRUE_Vertex_y() - universe->GetVertex_y();
        double smear_z = universe->GetTRUE_Vertex_z() - universe->GetVertex_z();
        double smear_r = universe->GetTRUE_Vertex_r() - universe->GetVertex_r();

        h_CryoVertex_X_RECO_smearing.univHist(universe)->Fill(smear_x,universe->GetWeight(kWeights_v1tune));

        h_CryoVertex_Y_RECO_smearing.univHist(universe)->Fill(smear_y,universe->GetWeight(kWeights_v1tune));

        h_CryoVertex_Z_RECO_smearing.univHist(universe)->Fill(smear_z,universe->GetWeight(kWeights_v1tune));

        h_CryoVertex_R_RECO_smearing.univHist(universe)->Fill(smear_r,universe->GetWeight(kWeights_v1tune));

        h_CryoVertexChiSqFit.univHist(universe)->Fill(universe->GetVertexChiSqrFit(),universe->GetWeight(kWeights_v1tune));





        } // End if passed cuts

        ////////////
        ///TRUTH
        ///////////
        //if(m_debugOn==true){std::cout<<"before True Cut for Universe"<<std::endl;}
        if(PassesCutsTRUTH(*universe, kTRUTHCutsVector)){


          if(PassesCutsRECO(*universe,  is_mc , kCutsVector_Eff) ){
            auto PDG_trklist = universe->GetVector_nonMuonTk_PDG();
            auto Energy_trklist = universe-> GetVector_nonMuonTk_Energy_GeV();
            auto Angle_trklist = universe->GetVector_nonMuonTk_Angle_wrtb_Degs();
            auto EnergyFraction_vector = universe->Get_TrueFractionE_vector();
           //int secondTrk = universe->Getindex2ndTrackhighestKE();
            //int secondTrk = universe->Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_lessthanAngle_muonNotinlist(PDG_trklist, Energy_trklist, Angle_trklist, EnergyFraction_vector);
            unsigned int secondTrk = universe-> Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_lessthanAngle_muonNotinlist_KE_proton_pion_thrusthold(PDG_trklist, Energy_trklist, Angle_trklist, EnergyFraction_vector);

            if(secondTrk==-999)continue;
            int secTrk_PDG = PDG_trklist.at(secondTrk);
            double secTrkTrueAngle = Angle_trklist.at(secondTrk);
            double secTrkTrueEnergy = Energy_trklist.at(secondTrk);
            Particle_type GroupType = GetParticlegroup_type(secTrk_PDG);

            int True_tracksize = PDG_trklist.size();

            //std::cout<<"inside Loop True 2nd Trk E = "<<secTrkTrueEnergy<< std::endl;


            h_MuonPhi_TRUE_RECO.univHist(universe)->Fill(universe->GetTRUE_Phimu(),universe->GetWeight(kWeights_v1tune));

            h_CryoVertex_X_TRUE_RECO.univHist(universe)->Fill(universe->GetTRUE_Vertex_x(),universe->GetWeight(kWeights_v1tune));

            h_CryoVertex_Y_TRUE_RECO.univHist(universe)->Fill(universe->GetTRUE_Vertex_y(),universe->GetWeight(kWeights_v1tune));

            h_CryoVertex_Z_TRUE_RECO.univHist(universe)->Fill(universe->GetTRUE_Vertex_z(),universe->GetWeight(kWeights_v1tune));

            h_CryoVertex_R_TRUE_RECO.univHist(universe)->Fill(universe->GetTRUE_Vertex_r(),universe->GetWeight(kWeights_v1tune));

            double smear_x = universe->GetTRUE_Vertex_x() - universe->GetVertex_x();
            double smear_y = universe->GetTRUE_Vertex_y() - universe->GetVertex_y();
            double smear_z = universe->GetTRUE_Vertex_z() - universe->GetVertex_z();
            double smear_r = universe->GetTRUE_Vertex_r() - universe->GetVertex_r();

            h_CryoVertex_X_RECO_TRUE_smearing.univHist(universe)->Fill(smear_x,universe->GetWeight(kWeights_v1tune));
            h_CryoVertex_Y_RECO_TRUE_smearing.univHist(universe)->Fill(smear_y,universe->GetWeight(kWeights_v1tune));
            h_CryoVertex_Z_RECO_TRUE_smearing.univHist(universe)->Fill(smear_z,universe->GetWeight(kWeights_v1tune));
            h_CryoVertex_R_RECO_TRUE_smearing.univHist(universe)->Fill(smear_r,universe->GetWeight(kWeights_v1tune));



          }// END OF TRUTH + RECO CUTS

        }//END OF TRUTH PASS CUTS




      } // End band's universe loop
    } // End Band loop
  } //End entries loop

  gSystem->GetProcInfo(&procInfo);
  std::cout << " Done with loop Mem1: " << procInfo.fMemResident/1000 << " MB" << " time = "<<  procInfo.fCpuSys  <<  " sec""\n";
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
//EventCountMap[kPlayListVector[0]] = EventCounter_MCFull;
EventCountMap[kPlayListVector[0]] = EventCounter_RECO;
//EventCountMap[kPlayListVector[2]] = EventCounter_dataFull;
//EventCountMap[kPlayListVector[3]] = EventCounter_dataEmpty;
//////////////////////////////////////////////////////////////////////////
//End of Empty data
//////////////////////////////////////////////////////////////////////////


double countdata= 0.0;
double countmc= 0.0;

    h_MuonPZ.SyncCVHistos();
    h_MuonPT.SyncCVHistos();
    h_MuonE.SyncCVHistos();
    h_MuonTheta.SyncCVHistos();
    h_MuonPZ_Fake.SyncCVHistos();
    h_MuonPT_Fake.SyncCVHistos();
    h_MuonE_Fake.SyncCVHistos();
    h_MuonTheta_Fake.SyncCVHistos();
    h_MuonPZ_Fake2.SyncCVHistos();
    h_MuonPT_Fake2.SyncCVHistos();
    h_MuonE_Fake2.SyncCVHistos();
    h_MuonTheta_Fake2.SyncCVHistos();
    h_MuonDOCA.SyncCVHistos();
    h_MuonCurvatureSig.SyncCVHistos();
    h_muon_MINOS_E.SyncCVHistos();
    h_CryoVertexChiSqFit.SyncCVHistos();

    h_MuonPZ_TRUE_RECO.SyncCVHistos();
    h_MuonPT_TRUE_RECO.SyncCVHistos();
    h_MuonE_TRUE_RECO.SyncCVHistos();
    h_MuonTheta_TRUE_RECO.SyncCVHistos();
    h_MuonDOCA_TRUE_RECO.SyncCVHistos();
    h_MuonPhi_TRUE_RECO.SyncCVHistos();
//////////////////////////////////


    h_CryoVertex_X.SyncCVHistos();
    h_CryoVertex_Y.SyncCVHistos();
    h_CryoVertex_R.SyncCVHistos();
    h_CryoVertex_Z.SyncCVHistos();


    h_CryoVertex_X_TRUE_RECO.SyncCVHistos();
    h_CryoVertex_Y_TRUE_RECO.SyncCVHistos();
    h_CryoVertex_R_TRUE_RECO.SyncCVHistos();
    h_CryoVertex_Z_TRUE_RECO.SyncCVHistos();
    h_Tracksize_TRUE_RECO.SyncCVHistos();
    h_Tracksize.SyncCVHistos();
    //////////////////////////////////
    h_secTrk_Energy.SyncCVHistos();
    h_secTrk_MidTheta.SyncCVHistos();
    h_secTrk_Openangle.SyncCVHistos();
    h_secTrk_DOCA.SyncCVHistos();


    h_secTrk_DOCA_TRUE_RECO.SyncCVHistos();


    h_secTrk_Energy_TRUE_RECO.SyncCVHistos();
    h_secTrk_Theta_TRUE_RECO.SyncCVHistos();
    h_secTrk_Openangle_TRUE_RECO.SyncCVHistos();
    h_secTrk_DOCA_TRUE_RECO.SyncCVHistos();

    h_secTrk_Pathlength.SyncCVHistos();
    h_secTrk_Pathlength_TRUE_RECO.SyncCVHistos();


    h_CryoVertex_X_RECO_TRUE_smearing.SyncCVHistos();
    h_CryoVertex_Y_RECO_TRUE_smearing.SyncCVHistos();
    h_CryoVertex_Z_RECO_TRUE_smearing.SyncCVHistos();
    h_CryoVertex_R_RECO_TRUE_smearing.SyncCVHistos();

    h_CryoVertex_X_RECO_smearing.SyncCVHistos();
    h_CryoVertex_Y_RECO_smearing.SyncCVHistos();
    h_CryoVertex_Z_RECO_smearing.SyncCVHistos();
    h_CryoVertex_R_RECO_smearing.SyncCVHistos();

//////////////////////////////////
//////////////////////////////////



    //MuonEnergymaterial.Write();
    //outFile.cd();
    //outFile.Write();

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
  auto datatype = String_ISMC(is_mc);
  char c[playlist_name.length() + 1];
  char d[datatype.length() + 1];
  char rootpathway[OUTputRoot_pathway.length()+1];
  char ErrorStatus[sysmatics_status.length()+1];
  strcpy(rootpathway, OUTputRoot_pathway.c_str());
  strcpy(c, playlist_name.c_str());
  strcpy(d, datatype.c_str());
  strcpy(ErrorStatus, sysmatics_status.c_str());
  std::string reco_true = "TRUTHcuts_RECOcuts_" + playlist_name;
  std::string true_Cuts = "TRUTHcuts" + playlist_name;
  char reco_true_char[reco_true.length()+1];
  char true_Cuts_char[true_Cuts.length()+1];
  strcpy(reco_true_char, reco_true.c_str());
  strcpy(true_Cuts_char, true_Cuts.c_str());

  PrintCutstoScreen( kCutsVector , EventCounter_RECO, c, mcscale );
  //MakeEfficiencyCutCVS(EventCounter_EFF_TRUTH, EventCounter_EFF , kCutsVector_Eff,c,mcPOT);
  //Make_cvsOfCutsRate( kCutsVector , EventCounter_RECO, c, true, mcscale, mcPOT);
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~ RECO Eff cuts ~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;
//  Make_cvsOfCutsRateTRUE(kTRUTHCutsVector , EventCounter_TRUTH_total, true_Cuts_char, mcscale, mcPOT);
  //Make_cvsOfCutsRate( kCutsVector_Eff, EventCounter_EFF, reco_true_char, true, mcscale, mcPOT);
  PrintCutstoScreen( kCutsVector_Eff , EventCounter_EFF, c, mcscale );
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~ Making Figures ~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;

  //outFileName = "Histograms_test.root";
  //auto outFile = TFile::Open(outFileName);
  TCanvas *can = new TCanvas("", "");
  MnvPlotter *mnv_plotter = new MnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);

  char pdf_name[1024];
  char pdf_start[1024];
  char pdf_mid[1024];
  char pdf_end[1024];

  sprintf(pdf_name, "RECO_PLOTS_%s_%s_SmearingStudy",c,d);

  sprintf(pdf_start,"%s.pdf(",pdf_name);
  sprintf(pdf_mid,  "%s.pdf",pdf_name);
  sprintf(pdf_end,  "%s.pdf)",pdf_name);

  can -> Print(pdf_start);

  DrawVertex_Cryotank_X_Y_R_Vs_Z(UpstreamBugle_vector , c, " [RECO] Upstream Bugle", pdf_name , can, mnv_plotter);
  DrawVertex_Cryotank_X_Y_R_Vs_Z(DownstreamBugle_vector , c, "[RECO] Downstream Bugle" ,pdf_name, can, mnv_plotter);
  DrawVertex_Cryotank_X_Y_R_Vs_Z(CenterBugle_vector, c, "[RECO] Center Bugle" ,pdf_name, can, mnv_plotter);

  DrawVertex_Cryotank_X_Y_R_Vs_Z(UpstreamBugle_vector_He ,UpstreamBugle_vector_Al, c, " [RECO] Upstream Bugle", pdf_name , can, mnv_plotter);
  DrawVertex_Cryotank_X_Y_R_Vs_Z(DownstreamBugle_vector_He,DownstreamBugle_vector_Al, c, "[RECO] Downstream Bugle" ,pdf_name, can, mnv_plotter);
  DrawVertex_Cryotank_X_Y_R_Vs_Z(CenterBugle_vector_He, CenterBugle_vector_Al,c, "[RECO] Center Bugle" ,pdf_name, can, mnv_plotter);



  can -> Print(pdf_end);

  sprintf(outFileName, "%s/%s_%s_%s_%s4U.root",rootpathway, "SMEARING_STUDY",c,d,ErrorStatus);

  std::cout << "Writing output file to: " <<outFileName << std::endl;

  //TFile outFile(outFileName, "RECREATE");
  MnvH1D *h_Mig_MuonE_px;
  MnvH1D *h_Mig_MuonPZ_px;
  MnvH1D *h_Mig_MuonPT_px;
  MnvH1D *h_Mig_MuonTheta_px;
  MnvH1D *h_Mig_MuonE_py;
  MnvH1D *h_Mig_MuonPZ_py;
  MnvH1D *h_Mig_MuonPT_py;
  MnvH1D *h_Mig_MuonTheta_py;




 h_Mig_MuonE_px = h_Mig_MuonE->ProjectionX("h_Mig_MuonE_px");
 h_Mig_MuonPZ_px = h_Mig_MuonPZ->ProjectionX("h_Mig_MuonPZ_px");
 h_Mig_MuonPT_px = h_Mig_MuonPT->ProjectionX("h_Mig_MuonPT_px");
 h_Mig_MuonTheta_px = h_Mig_MuonTheta->ProjectionX("h_Mig_MuonTheta_px");

   h_Mig_MuonE_py = h_Mig_MuonE->ProjectionY("h_Mig_MuonE_py");
   h_Mig_MuonPZ_py = h_Mig_MuonPZ->ProjectionY("h_Mig_MuonPZ_py");
   h_Mig_MuonPT_py = h_Mig_MuonPT->ProjectionY("h_Mig_MuonPT_py");
   h_Mig_MuonTheta_py = h_Mig_MuonTheta->ProjectionY("h_Mig_MuonTheta_py");


std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~ Making Root file ~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;
  //TFile *outFile(outFileName, "RECREATE");
  TFile *outFile = new TFile(outFileName,"RECREATE");
  TChain POT_branch("Meta");
  POT_branch.Add(RootName.c_str());
  //TTree *oldtree = (TTree*)file->Get("Meta");
  TTree *clone = POT_branch.CloneTree();
  clone->Write();


  h_MuonE.hist->Write();
  h_MuonE_TRUE_RECO.hist->Write();

  h_MuonPZ.hist->Write();
  h_MuonPZ_TRUE_RECO.hist->Write();

  h_MuonPT.hist->Write();
  h_MuonPT_TRUE_RECO.hist->Write();
  h_MuonTheta.hist->Write();
  h_MuonTheta_TRUE_RECO.hist->Write();

  h_MuonPZ_Fake.hist->Write();
  h_MuonPT_Fake.hist->Write();
  h_MuonE_Fake.hist->Write();
  h_MuonTheta_Fake.hist->Write();

  h_MuonPZ_Fake2.hist->Write();
  h_MuonPT_Fake2.hist->Write();
  h_MuonE_Fake2.hist->Write();
  h_MuonTheta_Fake2.hist->Write();


  h_MuonPhi_TRUE_RECO.hist->Write();
  h_MuonDOCA.hist->Write();
  h_MuonDOCA_TRUE_RECO.hist->Write();


  h_CryoVertex_X.hist->Write();
  h_CryoVertex_X_TRUE_RECO.hist->Write();
  h_CryoVertex_X_Material.WriteToFile(*outFile);
  h_CryoVertex_X_Interaction.WriteToFile(*outFile);
  h_CryoVertex_X_Particle.WriteToFile(*outFile);

  h_CryoVertex_Y.hist->Write();
  h_CryoVertex_Y_TRUE_RECO.hist->Write();
  h_CryoVertex_Y_Material.WriteToFile(*outFile);
  h_CryoVertex_Y_Interaction.WriteToFile(*outFile);
  h_CryoVertex_Y_Particle.WriteToFile(*outFile);

  h_CryoVertex_Z.hist->Write();
  h_CryoVertex_Z_TRUE_RECO.hist->Write();
  h_CryoVertex_Z_Material.WriteToFile(*outFile);
  h_CryoVertex_Z_Interaction.WriteToFile(*outFile);
  h_CryoVertex_Z_Particle.WriteToFile(*outFile);

  h_CryoVertex_R.hist->Write();
  h_CryoVertex_R_TRUE_RECO.hist->Write();
  h_CryoVertex_R_Material.WriteToFile(*outFile);
  h_CryoVertex_R_Interaction.WriteToFile(*outFile);
  h_CryoVertex_R_Particle.WriteToFile(*outFile);

  h_CryoVertexChiSqFit.hist->Write();
  h_CryoVertexChiSqFit_Material.WriteToFile(*outFile);
  h_CryoVertexChiSqFit_Interaction.WriteToFile(*outFile);
  h_CryoVertexChiSqFit_Particle.WriteToFile(*outFile);


  h_secTrk_Energy.hist->Write();
  h_secTrk_Energy_TRUE_RECO.hist->Write();
  h_secTrk_Theta_TRUE_RECO.hist->Write();

  h_secTrk_MidTheta.hist->Write();

  h_secTrk_Openangle.hist->Write();

  h_secTrk_DOCA.hist->Write();

  h_secTrk_Pathlength.hist->Write();


  ////////////////////////////////////////////////
  // Veto Wall + Others
  ////////////////////////////////////////////////



  h_Tracksize.hist->Write();
  h_Tracksize_TRUE_RECO.hist->Write();





////////////////////////////////////////////////


/////////////////
/////2D hists////
/////////////////


  h_Mig_MuonE->Write();
  h_Mig_MuonPZ->Write();
  h_Mig_MuonPT->Write();
  h_Mig_MuonTheta->Write();
  h_Mig_MuonE_py->Write();
  h_Mig_MuonPZ_py->Write();
  h_Mig_MuonPT_py->Write();
  h_Mig_MuonTheta_py->Write();
  h_Mig_MuonE_px->Write();
  h_Mig_MuonPZ_px->Write();
  h_Mig_MuonPT_px->Write();
  h_Mig_MuonTheta_px->Write();

  h_MuonE_v2tune->Write();
  h_MuonE_MKmodel->Write();
  h_X_RECO_smearing_REGION.WriteToFile(*outFile);
  h_Y_RECO_smearing_REGION.WriteToFile(*outFile);
  h_Z_RECO_smearing_REGION.WriteToFile(*outFile);
  h_X_TRUE_smearing_REGION.WriteToFile(*outFile);
  h_Y_TRUE_smearing_REGION.WriteToFile(*outFile);
  h_Z_TRUE_smearing_REGION.WriteToFile(*outFile);

  h_CryoVertex_X_RECO_smearing.hist->Write();
  h_CryoVertex_Y_RECO_smearing.hist->Write();
  h_CryoVertex_Z_RECO_smearing.hist->Write();
  h_CryoVertex_R_RECO_smearing.hist->Write();
  h_CryoVertex_X_RECO_TRUE_smearing.hist->Write();
  h_CryoVertex_Y_RECO_TRUE_smearing.hist->Write();
  h_CryoVertex_Z_RECO_TRUE_smearing.hist->Write();
  h_CryoVertex_R_RECO_TRUE_smearing.hist->Write();
/*
  h_CryoVertex_X_Pos->Write();
  h_CryoVertex_X_Neg->Write();

  h_CryoVertex_Y_Pos->Write();
  h_CryoVertex_Y_Neg->Write();

  h_CryoVertex_Z_Pos->Write();
  h_CryoVertex_Z_Neg->Write();


*/

  h_CryoVertex_X_CV->Write();
  h_CryoVertex_Y_CV->Write();
  h_CryoVertex_Z_CV->Write();
  h_MC_Vertex_distance_upstream->Write();
  h_MC_TRUTH_Vertex_distance_upstream->Write();
  h_MC_TRUTH_Vertex_distance_upstream_Convolution->Write();
  h_MC_TRUTH_Vertex_distance_upstream_Convolution_toDATA->Write();
  h_MC_TRUTH_Vertex_distance_upstream_Convolution_toDATA_2->Write();
  h_Vertex_distance_upstream_Material.WriteToFile(*outFile);

  h_MC_Vertex_distance_downstream->Write();
  h_MC_TRUTH_Vertex_distance_downstream->Write();
  h_MC_TRUTH_Vertex_distance_downstream_Convolution->Write();
  h_MC_TRUTH_Vertex_distance_downstream_Convolution_toDATA->Write();
  h_Vertex_distance_downstream_Material.WriteToFile(*outFile);


  h_CryoVertex_R_streaming_Center->Write();
  h_CryoVertex_R_streaming_TRUTH_Center->Write();
  h_CryoVertex_R_streaming_TRUTH_Center_Convolution->Write();
  h_CryoVertex_R_streaming_TRUTH_Center_Convolution_toData->Write();

  h_CryoVertex_RR_streaming_TRUTH_Center_Convolution->Write();
  h_CryoVertex_RR_streaming_TRUTH_Center_Convolution_toData->Write();

  h_CryoVertex_RR_streaming_Center->Write();
  h_CryoVertex_RR_streaming_TRUTH_Center->Write();
  h_CryoVertex_Z_Center->Write();
  h_CryoVertex_Z_Center_TRUTH->Write();
  h_CryoVertex_Z_Center_Material.WriteToFile(*outFile);
  h_CryoVertex_Z_downstream->Write();
  h_CryoVertex_Z_TRUTH_downstream->Write();
  h_CryoVertex_Z_downstream_Material.WriteToFile(*outFile);
  h_CryoVertex_Z_upstream->Write();
  h_CryoVertex_Z_TRUTH_upstream->Write();
  h_CryoVertex_Z_upstream_Material.WriteToFile(*outFile);
  h_CryoVertex_Z_XYshifts->Write();
  h_CryoVertex_X_XYshifts->Write();
  h_CryoVertex_Y_XYshifts->Write();



  h_CryoVertex_Z_Zshifts->Write();
  h_CryoVertex_X_Zshifts->Write();
  h_CryoVertex_Y_Zshifts->Write();


  h_secTrk_tracklength_upstreamCAP->Write();
  h_secTrk_tracklength_upstreamCAP_Material.WriteToFile(*outFile);
  h_secTrk_tracklength_upstreamCAP_Interaction.WriteToFile(*outFile);
  h_secTrk_tracklength_upstreamCAP_Particle.WriteToFile(*outFile);

  h_secTrk_tracklength_downstreamCAP->Write();
  h_secTrk_tracklength_downstreamCAP_Material.WriteToFile(*outFile);
  h_secTrk_tracklength_downstreamCAP_Interaction.WriteToFile(*outFile);
  h_secTrk_tracklength_downstreamCAP_Particle.WriteToFile(*outFile);

  h_secTrk_tracklength_Barrel->Write();
  h_secTrk_tracklength_Barrel_Material.WriteToFile(*outFile);
  h_secTrk_tracklength_Barrel_Interaction.WriteToFile(*outFile);
  h_secTrk_tracklength_Barrel_Particle.WriteToFile(*outFile);




  h_Z_Mig->Write();
  h_Z_Smearing->Write();

  outFile->Close();

  //sprintf(pdf_start, "Optimization_figures.pdf(");
  //sprintf(pdf_end, "Optimization_figures.pdf)");

  //TCanvas *can = new TCanvas("", "");
  //dPlotUtils::MnvPlotter mvnPlotter(PlotUtils::kCCInclusiveHeliumStyle);

    //mnvPlotter.legend_n_columns = 2;
    auto names= h_MuonTheta.hist->GetErrorBandNames();
    auto names_lat= h_MuonTheta.hist->  GetLatErrorBandNames();
    auto names_ver= h_MuonTheta.hist->  GetVertErrorBandNames();
    std::cout<<"all error bands "<<std::endl;
    for(auto cat:names){std::cout<<"names = "<< cat<<std::endl;}
    std::cout<<"names_lat "<<std::endl;
    for(auto cat:names_lat){std::cout<<"names = "<< cat<<std::endl;}
    std::cout<<"names_ver "<<std::endl;
    for(auto cat:names_ver){std::cout<<"names = "<< cat<<std::endl;}


    std::cout << "END OF Plotting" << std::endl;
   MakeLatex_Tables_withTrue_Event_info(N_A_secTrkParticle," ",  "N_A_FS_RECO", c, .5, "N_A in FS");



  for(auto band : error_bands){
    std::vector<HeliumCVUniverse*> band_universes = band.second;
    for(unsigned int i_universe = 0; i_universe < band_universes.size(); ++i_universe){ delete band_universes[i_universe];}
  }

  std::cout << "Success" << std::endl;


  can -> Print(pdf_end);

}//END of Event Loop

//=========================================
//=========================================
//////////////////////////////////////////////////////////////


std::vector<ECuts> GetRECOCutsVector() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ECuts> ret_vec;
  ret_vec.push_back(kNoCuts  );
  ret_vec.push_back(kGoodEnergy );
  ret_vec.push_back(kThetaMu );
  ret_vec.push_back(kMuonAngle );
  ret_vec.push_back(kNTracks);
  ret_vec.push_back(kUsableMuon);
  ret_vec.push_back(kMu_is_Plausible);
  ret_vec.push_back(kVeto );
  ret_vec.push_back(kSix );
  ret_vec.push_back(kMatchVetoDeadPaddle);

  ret_vec.push_back(kMinosCoil );
  ret_vec.push_back(kMinosMatch);
  ret_vec.push_back(kMinosCurvature);
  ret_vec.push_back(kMinosCharge );

  ret_vec.push_back(kVertexConverge);
  //ret_vec.push_back(kFiducialVolume );
 ret_vec.push_back(kFiducialVolume_ExtraShell);

  ret_vec.push_back(kTrackForwardGoing );
  ret_vec.push_back(ksecTrkwrtblessthanMaxAngle);
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
  ret_vec.push_back(kThetaMu );
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
  ret_vec.push_back(kFiducialVolume_ExtraShell);
  ret_vec.push_back(kTrackForwardGoing );
  ret_vec.push_back(ksecTrkwrtblessthanMaxAngle);
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
  True_vec.push_back(kTRUTHMuonEnergy );
  True_vec.push_back(kTRUTHMuonAngle );
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
  True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);
  //True_vec.push_back(kTRUTH_NoNeutral_FS_2ndTrk_withProtonanPionThresholds_RECOBRANCH);
  True_vec.push_back(kAllTRUTHCuts);


  //int n = sizeof(kCutsArray) / sizeof(kCutsArray[0]);
  //static std::vector<ECuts> ret_vec(kCutsArray, kCutsArray + n);
  return True_vec;
//#endif
}

std::vector<ECutsTRUTH> GetTRUTHCutsVector_Energy() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ECutsTRUTH> True_vec;
  True_vec.push_back(kTRUTHNoCuts   );
  True_vec.push_back(kTRUTHMuonEnergy );
  True_vec.push_back(kTRUTHMuonAngle );
  True_vec.push_back(kTRUTHneutrino);
  True_vec.push_back(kTRUTHCCInteraction );
  True_vec.push_back(kTRUTHtarget);
  //True_vec.push_back(kTRUTHFiduical ); // dont' apply truth fiduical cut in Nomrateor
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);

  //True_vec.push_back(kTRUTH_NoNeutral_FS_2ndTrk_RECOBRANCH);
  True_vec.push_back(kTRUTH_NoNeutral_FS_2ndTrk_withProtonanPionThresholds_RECOBRANCH);
  //True_vec.push_back(kTRUTH_2ndTrkProtonEnergythreshold);
  //True_vec.push_back(kTRUTH_2ndTrkPionEnergythreshold);
  //True_vec.push_back(kTRUTH_secTrk_Angle_threshold);
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
  Particle.push_back(kMuon);
  Particle.push_back(kPion_0);
  Particle.push_back(kPion_neg);
  Particle.push_back(kPion_pos);


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



std::vector<ME_helium_Playlists> GetPlayListVector() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ME_helium_Playlists> Playlist;
//EMPTY
//Playlist.push_back(kME1A);//
Playlist.push_back(kME1G);
//Playlist.push_back(kME1L);
//Playlist.push_back(kME1M);
//Playlist.push_back(kME1N);


//Playlist.push_back(kME1P);
//Playlist.push_back(kME1C);
//Playlist.push_back(kME1D);
//Playlist.push_back(kME1F);
//Playlist.push_back(kME1E);
  return Playlist;
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


std::vector<Weights> GetWeightVector() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<Weights> weight_vec;

  weight_vec.push_back(kweightFlux );
  weight_vec.push_back(kweightMinos );
  weight_vec.push_back(kweightGenie);
  weight_vec.push_back(kweight2p2ptune );
  weight_vec.push_back(kweightRPA);
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
  weight_vec.push_back(kweightLowQ2Pi);
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
  //weight_vec.push_back(kweightLowQ2Pi);
  return weight_vec;
//#endif
}
//////////////////////////////////////////////////////////////////////////
//GET CryoTank Varibles
//////////////////////////////////////////////////////////////////////////


//////////////////////////
///Main
/////////////////////////
int main(int argc, char* argv[]){
  TH1::AddDirectory(false);
  bool m_cutson = true;
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

  std::cout << "This is the playlist: "<< argv[1] << std::endl;
  std::string playlist_string(argv[1]);
  ME_helium_Playlists Playlist_to_run = GetPlaylist_FromString(playlist_string);




  runEventLoop(m_debugOn, Playlist_to_run);
  return 0;
}
//#endif
