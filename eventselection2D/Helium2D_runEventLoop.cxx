// * Uses the New Systematics Framework and "Universe" objects.
// * loop universes, make cuts and fill histograms with the correct lateral
// shifts and weights for each universe.
// * TChain --> PlotUtils::ChainWrapper.
// * MnvHXD --> PlotUtils::HistWrapper.
// * Genie, flux, non-resonant pion, and some detector systematics calculated.
#include "Helium2D_runEventLoop.h"

std::string OUTputRoot_pathway = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles";
//=====================================================
// Functions
//=====================================================
std::vector<ECuts> GetRECOCutsVector();
std::vector<ECutsTRUTH> GetTRUTHCutsVector();
std::vector<MuonVar> GetMUONVaribles();
std::vector<SecondTrkVar> GetPlayListSecondTrkVector();
std::vector<CryoVertex> GetCryoVertexVaribles();
std::vector<ME_helium_Playlists> GetPlayListVector();
std::vector<ME_helium_Playlists> GetTRUEPlayListVector();
std::vector<Particle_type>  GetParicle_type();
std::vector<Weights> GetWeightVector();
std::vector<Weights> GetWeightVector_v2();
std::vector<Weights> GetWeightVector_mk();
//double Mev_to_GeV=.001;

// Get container of systematic
const bool m_RunCodeWithSystematics = true;
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



/*const auto TracksGreaterThan2 = {  NamedCategory<int>({3},   "ThirdTrack"),
                                   NamedCategory<int>({4},   "FourthTrack"),
                                   NamedCategory<int>({5},   "FifthTrack"),
                                   NamedCategory<int>({6},   "SixthTrack"),
                                   NamedCategory<int>({7},   "SevethTrack"),
                                   NamedCategory<int>({8},   "EighthTrack")

                                 };*/
const int n_flux_universes = 10;
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



std::map< std::string, std::vector<CVUniverse*> >
  GetErrorBands(PlotUtils::ChainWrapper* chain) {
    typedef std::map< std::string, std::vector<CVUniverse*> > SystMap;

    SystMap error_bands;

    // CV
    error_bands[std::string("cv")].push_back( new CVUniverse(chain) );

    //Detector systematics, lateral sh

if(m_RunCodeWithSystematics){

//    SystMap muonP_systematics = PlotUtils::GetMuonSystematicsMap<CVUniverse>(chain,NSFDefaults::KludgedMinosMuonMomentum_Err);
  //  error_bands.insert(muonP_systematics.begin(), muonP_systematics.end());
    //std::cout << "C++ make muon resolution systematics" << std::endl;

    ///// MINOS ERROR systems
    SystMap MinervaMuon_systematics = PlotUtils::GetMinervaMuonSystematicsMap<CVUniverse>(chain);
    error_bands.insert(MinervaMuon_systematics.begin(), MinervaMuon_systematics.end());
    // Minerva Error System

    // MINOS efficiency
    SystMap MinosMuon_systematics = PlotUtils::GetMinosMuonSystematicsMap<CVUniverse>(chain);
    error_bands.insert(MinosMuon_systematics.begin(), MinosMuon_systematics.end());

    // Muon match efficiency
    SystMap MinosEff_systematics = PlotUtils::GetMinosEfficiencySystematicsMap<CVUniverse>(chain);
    error_bands.insert(MinosEff_systematics.begin(), MinosEff_systematics.end());

    SystMap flux_systematics = PlotUtils::GetFluxSystematicsMap<CVUniverse>(chain,n_flux_universes);
    error_bands.insert(flux_systematics.begin(), flux_systematics.end());

    SystMap angle_systematics = PlotUtils::GetAngleSystematicsMap<CVUniverse>(chain,NSFDefaults::beamThetaX_Err,NSFDefaults::beamThetaY_Err);
    error_bands.insert(angle_systematics.begin(), angle_systematics.end());
    //GENIE
    SystMap genie_systematics = PlotUtils::GetGenieSystematicsMap<CVUniverse>(chain);
    error_bands.insert(genie_systematics.begin(), genie_systematics.end());

    SystMap a2p2h_systematics = PlotUtils::Get2p2hSystematicsMap<CVUniverse>(chain);
    error_bands.insert(a2p2h_systematics.begin(), a2p2h_systematics.end());

    SystMap RPA_systematics = PlotUtils::GetRPASystematicsMap<CVUniverse>(chain);
    error_bands.insert(RPA_systematics.begin(), RPA_systematics.end());

    //SystMap LowQ2Pi_systematics = PlotUtils::GetLowQ2PiSystematicsMap<CVUniverse>(chain);
    //error_bands.insert(LowQ2Pi_systematics.begin(), LowQ2Pi_systematics.end());
    SystMap VertexSmearing_systematics = GetHELIUMVertexSmearingShiftSystematicsMap<CVUniverse>(chain);
    error_bands.insert(VertexSmearing_systematics.begin(), VertexSmearing_systematics.end());

    SystMap HeliumTargetMass_systematics = GetHeliumTargetMassSystematicsMap<CVUniverse>(chain);
    error_bands.insert(HeliumTargetMass_systematics.begin(), HeliumTargetMass_systematics.end());

    // Muon resolution
    //SystMap muonR_systematics = PlotUtils::GetMuonResolutionSystematicsMap<CVUniverse>(chain,NSFDefaults::muonResolution_Err);
    //error_bands.insert(muonR_systematics.begin(), muonR_systematics.end());
    //std::cout << "C++ make minos efficiency systematics" << std::endl;

    // Non-res pi
    //SystMap nonrespi_systematics =
    //  PlotUtils::GetNonResPiSystematicsMap<CVUniverse>(chain);
    //error_bands.insert(nonrespi_systematics.begin(), nonrespi_systematics.end());



}



  return error_bands;
}
//======================================================================
//void EventCounter(const CVUniverse& , std::vector<ECuts> cuts, EventCount_RECO &Event_map ,bool is_mc,HeliumPlayListInfo Info );
  // Make a chain of events
  loadLibs();
//std::vector<ECuts> kCutsVector;
int Study_cap=50;
int Study_count=0;
double POT[4];
const std::vector<ECuts> kCutsVector = GetRECOCutsVector();
const std::vector<ECutsTRUTH> kTRUTHCutsVector = GetTRUTHCutsVector();
const std::vector<ME_helium_Playlists> kPlayListVector = GetPlayListVector();
const std::vector<ME_helium_Playlists> kTRUEPlayListVector = GetTRUEPlayListVector();

const std::vector<Weights> kWeights_v1tune= GetWeightVector();
const std::vector<Weights> kWeights_v2tune= GetWeightVector_v2();
const std::vector<Weights> kWeights_forMK = GetWeightVector_mk();
const std::vector<MuonVar> kMuonVaribles_vector = GetMUONVaribles();
const std::vector<SecondTrkVar> kSecTrkVaribles_vector = GetPlayListSecondTrkVector();

const std::vector<CryoVertex> kCryoVertexVaribles_vector = GetCryoVertexVaribles();
EventPlaylist_RecoCount EventCountMap;

const std::vector<Particle_type> kSecondary_particle_vector = GetParicle_type();


TH1::AddDirectory(kFALSE);

const double toDegs = 180.0/TMath::Pi();
//======================================================================
////////////////////ADDING TO CHAIN wrapper ///////////////////////////
//======================================================================
bool is_mc= true;
//PlotUtils::ChainWrapper* chw_FullMC = makeChainWrapperPtr("../playlists/playlist_MC_Mvn13C_ecoicaPlus_8_23_19.txt", "Muon");//
//PlotUtils::ChainWrapper* chw_MC = makeChainWrapperPtr("../playlists/MC_Playlist/ME_1G_MC.txt", "Muon");//
//PlotUtils::ChainWrapper* chw_MC = makeChainWrapperPtr("../playlists/MC_Playlist/ME_1A_MC.txt", "Muon");//
//PlotUtils::ChainWrapper* chw_MC = makeChainWrapperPtr("../playlists/MC_Playlist/ME_1A_MC.txt", "Muon");//

  MinervaUniverse::SetDeuteriumGeniePiTune(false);
  MinervaUniverse::SetNuEConstraint(true);
  MinervaUniverse::SetZExpansionFaReweight(false);
  MinervaUniverse::SetAnalysisNuPDG(14);
  MinervaUniverse::SetNonResPiReweight(true);
  MinervaUniverse::SetNFluxUniverses(n_flux_universes);
  std::string playlist = GetPlaylist(PlayList_iterator);
  MinervaUniverse::SetPlaylist(playlist);

  int nu_pdg = MinervaUniverse::GetAnalysisNuPDG();
  std::string playlist_fluxreweighter = MinervaUniverse::GetPlaylist();
  bool useNuEconstraint = MinervaUniverse::UseNuEConstraint();
  int NFlux_universe = MinervaUniverse::GetNFluxUniverses();
  bool useMuonCorrelations = true;
  double Min_NuFluxEnergy = 0.0;
  double Max_NuFluxEnergy = 120.0;
  //MinervaUniverse::Set_Multiple_resetPlaylist(true);



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
//std::map< std::string, std::vector<CVUniverse*> > error_bands = GetErrorBands(chw_FullMC);
std::map<std::string, std::vector<CVUniverse*> > error_bands= GetErrorBands(chw_MC);
std::map<const std::string, const int> error_name;
std::map<std::string, std::vector<CVUniverse*> >::iterator itr;
for(itr = error_bands.begin(); itr != error_bands.end(); ++itr) error_name.insert(std::pair<std::string, const int>((itr->second)[0]->ShortName(), (itr->second).size()));
HeliumPlayListInfo Playlist_Info(playlist);

std::map<std::string, const int>::iterator itr_m;


double mcPOT = GetPOT_local(mcchainPOT, "MC");
std::cout<<"Number of Universes set is = "<<    MinervaUniverse::GetNFluxUniverses()<<std::endl;
std::cout << "POT of this Playlist = "<< mcPOT <<std::endl;


static weightMK *weight_MK;
char *mparalocation = std::getenv("MPARAMFILESROOT");
string dir_data = string(mparalocation)+"/data/Reweight/";
weight_MK = new weightMK(dir_data + "output_ratio_genie_neut_for_MKmodel.root");

//MinervaUniverse::SetNFluxUniverses(25);
POTCounter pot_counter;

//MinervaUniverse::SetPlaylist_AGAIN(playlist);


const std::string RootName = GetPlaylist_ROOT_path(PlayList_iterator, is_mc );
//const std::string RootName = GetPlaylist_ROOT_path("1F_pdgcorrection_2",  is_mc );
std::cout<<"The Playlist that is set is = "<< playlist.c_str()<<std::endl;
std::cout<<"The Playlist Root = "<< RootName<<std::endl;
 ///pnfs/minerva/persistent/users/cnguyen/ME_G1_Merg/*.root


  auto mcscale = 1.0; //Data_POT_full/ MC_POT_full;



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
//vector<vector<double> > vector_2D_PT_PZ;
//vector_2D_PT_PZ.push_back(PTbin_vector);
//vector_2D_PT_PZ.push_back(Pzbin_vector);
//HyperDimLinearizer::HyperDimLinearizer *HyperDim2d_PT_PZ = new HyperDimLinearizer::HyperDimLinearizer(vector_2D_PT_PZ,0)
////////////////
//muon Varibles///
////////////////
PlotUtils::Hist2DWrapper<CVUniverse> h_Muon_PT_PZ("h_Muon_PT_PZ", "h_Muon_PT_PZ", PTbin_vector , Pzbin_vector, error_bands);
PlotUtils::Hist2DWrapper<CVUniverse> h_Muon_PT_theta("h_Muon_PT_theta", "h_Muon_PT_theta", PTbin_vector , MuonThetabin_vector, error_bands);
PlotUtils::Hist2DWrapper<CVUniverse> h_Muon_PZ_theta("h_Muon_PZ_theta", "h_Muon_PZ_theta", Pzbin_vector , MuonThetabin_vector, error_bands);
PlotUtils::Hist2DWrapper<CVUniverse> h_Muon_E_theta("h_Muon_E_theta", "h_Muon_E_theta",  Ebin_vector , MuonThetabin_vector, error_bands);
PlotUtils::Hist2DWrapper<CVUniverse> h_Muon_E_PZ("h_Muon_E_PZ", "h_Muon_E_PZ",  Ebin_vector ,  Pzbin_vector, error_bands);
PlotUtils::Hist2DWrapper<CVUniverse> h_Muon_E_PT("h_Muon_E_PT", "h_Muon_E_PT",  Ebin_vector , PTbin_vector, error_bands);
PlotUtils::Hist2DWrapper<CVUniverse> h_cryoVertex_Z_R("h_cryoVertex_Z_R", "h_cryoVertex_Z_R", Vertex_Zbin_vector, Vertex_Rbin_vector , error_bands);

PlotUtils::Hist2DWrapper<CVUniverse> h_Muon_PT_PZ_TRUE_RECO("h_Muon_PT_PZ_TRUE_RECO", "h_Muon_PT_PZ_TRUE_RECO", PTbin_vector , Pzbin_vector, error_bands);
PlotUtils::Hist2DWrapper<CVUniverse> h_Muon_PT_theta_TRUE_RECO("h_Muon_PT_theta_TRUE_RECO", "h_Muon_PT_theta_TRUE_RECO", PTbin_vector , MuonThetabin_vector, error_bands);
PlotUtils::Hist2DWrapper<CVUniverse> h_Muon_PZ_theta_TRUE_RECO("h_Muon_PZ_theta_TRUE_RECO", "h_Muon_PZ_theta_TRUE_RECO", Pzbin_vector , MuonThetabin_vector, error_bands);
PlotUtils::Hist2DWrapper<CVUniverse> h_Muon_E_theta_TRUE_RECO("h_Muon_E_theta", "h_Muon_E_theta",  Ebin_vector , MuonThetabin_vector, error_bands);
PlotUtils::Hist2DWrapper<CVUniverse> h_Muon_E_PZ_TRUE_RECO("h_Muon_E_PZ_TRUE_RECO", "h_Muon_E_PZ_TRUE_RECO",  Ebin_vector ,  Pzbin_vector, error_bands);
PlotUtils::Hist2DWrapper<CVUniverse> h_Muon_E_PT_TRUE_RECO("h_Muon_E_PT_TRUE_RECO", "h_Muon_E_PT_TRUE_RECO",  Ebin_vector , PTbin_vector, error_bands);
PlotUtils::Hist2DWrapper<CVUniverse> h_cryoVertex_Z_R_TRUE_RECO("h_cryoVertex_Z_R_TRUE_RECO", "h_cryoVertex_Z_R_TRUE_RECO", Vertex_Zbin_vector, Vertex_Rbin_vector , error_bands);

PlotUtils::Hist2DWrapper<CVUniverse> h_2ndtrkangle_2ndTrkE_TRUE_RECO("h_2ndtrkangle_2ndTrkE_TRUE_RECO", "h_2ndtrkangle_2ndTrkE_TRUE_RECO", Vertex_secondTrkEbin_vector, SecTrk_Theta_TRUEbin_vector , error_bands);




MnvH2D *h_2d_2ndtrkangle_2ndTrkE_TRUE_RECO    =    new MnvH2D("h_2d_2ndtrkangle_2ndTrkE_TRUE_RECO", "h_2d_2ndtrkangle_2ndTrkE_TRUE_RECO", SecTrk_Theta_TRUEbin_vector.size()-1, SecTrk_Theta_TRUEbin_vector.data(),Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data()  );




/// Mnv Response Migration constuctor
//std::map<std::string,MinervaUnfold::MnvResponse*> Response

 MinervaUnfold::MnvResponse *MnvR_Muon_PT_PZ    = new MinervaUnfold::MnvResponse( "MnvR_Muon_PT_PZ", "MnvR_Muon_PT_PZ",    PTbin_vector, Pzbin_vector, error_name);
 MinervaUnfold::MnvResponse *MnvR_Muon_PT_theta = new MinervaUnfold::MnvResponse( "MnvR_Muon_PT_theta", "MnvR_Muon_PT_theta", PTbin_vector, MuonThetabin_vector, error_name);
 MinervaUnfold::MnvResponse *MnvR_Muon_PZ_theta = new MinervaUnfold::MnvResponse( "MnvR_Muon_PZ_theta", "MnvR_Muon_PZ_theta", Pzbin_vector, MuonThetabin_vector, error_name);
 MinervaUnfold::MnvResponse *MnvR_Muon_E_theta  = new MinervaUnfold::MnvResponse( "MnvR_Muon_E_theta", "MnvR_Muon_E_theta",  Ebin_vector,  MuonThetabin_vector, error_name);
 MinervaUnfold::MnvResponse *MnvR_Muon_E_PZ     = new MinervaUnfold::MnvResponse( "MnvR_Muon_E_PZ", "MnvR_Muon_E_PZ",     Ebin_vector,  Pzbin_vector,  error_name);
 MinervaUnfold::MnvResponse *MnvR_Muon_E_PT     = new MinervaUnfold::MnvResponse( "MnvR_Muon_E_PT", "MnvR_Muon_E_PT",     Ebin_vector,  PTbin_vector,  error_name);
 MinervaUnfold::MnvResponse *MnvR_cryoVertex_Z_R     = new MinervaUnfold::MnvResponse( "MnvR_cryoVertex_Z_R", "MnvR_cryoVertex_Z_R", Vertex_Zbin_vector, Vertex_Rbin_vector , error_name);

std::vector<MinervaUnfold::MnvResponse*>  MnvR_vector = {MnvR_Muon_PT_PZ, MnvR_Muon_PT_theta, MnvR_Muon_PZ_theta, MnvR_Muon_E_theta,  MnvR_Muon_E_PZ, MnvR_Muon_E_PT, MnvR_cryoVertex_Z_R};




PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type> h_Muon_PT_PZ_Material =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type>(MaterialGroup_categories, "h_Muon_PT_PZ_Material",  PTbin_vector , Pzbin_vector ,"h_Muon_PT_PZ_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type> h_Muon_PT_PZ_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type>(InteractionGroup_categories, "h_Muon_PT_PZ_Interaction",  PTbin_vector , Pzbin_vector ,"h_Muon_PT_PZ_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type> h_Muon_PT_PZ_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type>(ParticleGroup_categories, "h_Muon_PT_PZ_Particle",  PTbin_vector , Pzbin_vector ,"h_Muon_PT_PZ_Particle; [GeV];Events");


PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type> h_Muon_PT_theta_Material =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type>(MaterialGroup_categories, "h_Muon_PT_theta_Material",  PTbin_vector , MuonThetabin_vector ,"h_Muon_PT_theta_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type> h_Muon_PT_theta_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type>(InteractionGroup_categories, "h_Muon_PT_theta_Interaction",  PTbin_vector , MuonThetabin_vector ,"h_Muon_PT_theta_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type> h_Muon_PT_theta_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type>(ParticleGroup_categories, "h_Muon_PT_theta_Particle",  PTbin_vector , MuonThetabin_vector ,"h_Muon_PT_theta_Particle; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type> h_Muon_PZ_theta_Material =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type>(MaterialGroup_categories, "h_Muon_PZ_theta_Material",  Pzbin_vector , MuonThetabin_vector ,"h_Muon_PZ_theta_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type> h_Muon_PZ_theta_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type>(InteractionGroup_categories, "h_Muon_PZ_theta_Interaction",  Pzbin_vector , MuonThetabin_vector ,"h_Muon_PZ_theta_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type> h_Muon_PZ_theta_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type>(ParticleGroup_categories, "h_Muon_PZ_theta_Particle",  Pzbin_vector , MuonThetabin_vector ,"h_Muon_PZ_theta_Particle; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type> h_Muon_E_theta_Material =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type>(MaterialGroup_categories, "h_Muon_E_theta_Material",  Ebin_vector , MuonThetabin_vector ,"E_theta_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type> h_Muon_E_theta_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type>(InteractionGroup_categories, "h_Muon_E_theta_Interaction",  Ebin_vector , MuonThetabin_vector ,"E_theta_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type> h_Muon_E_theta_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type>(ParticleGroup_categories, "h_Muon_E_theta_Particle",  Ebin_vector , MuonThetabin_vector ,"E_theta_Particle; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type> h_Muon_E_PZ_Material =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type>(MaterialGroup_categories, "h_Muon_E_PZ_Material",  Ebin_vector , Pzbin_vector ,"E_PZ_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type> h_Muon_E_PZ_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type>(InteractionGroup_categories, "h_Muon_E_PZ_Interaction",  Ebin_vector , Pzbin_vector ,"E_PZ_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type> h_Muon_E_PZ_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type>(ParticleGroup_categories, "h_Muon_E_PZ_Particle",  Ebin_vector , Pzbin_vector ,"h_Muon_E_PZ_Particle; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type> h_Muon_E_PT_Material =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type>(MaterialGroup_categories, "h_Muon_E_PT_Material",  Ebin_vector , PTbin_vector ,"E_PT_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type> h_Muon_E_PT_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type>(InteractionGroup_categories, "h_Muon_E_PT_Interaction",  Ebin_vector , PTbin_vector ,"E_PT_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type> h_Muon_E_PT_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Particle_type>(ParticleGroup_categories, "h_Muon_E_PT_Particle",  Ebin_vector , PTbin_vector ,"E_PT_Particle; [GeV];Events");


PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type> h_cryoVertex_Z_R_Material =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Material_type>(MaterialGroup_categories, "h_cryoVertex_Z_R_Material",Vertex_Zbin_vector,  Vertex_Rbin_vector  ,"vertex_z_r_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type> h_cryoVertex_Z_R_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type>(InteractionGroup_categories, "h_cryoVertex_Z_R_Interaction",Vertex_Zbin_vector,  Vertex_Rbin_vector  ,"vertex_z_r_Interaction; [GeV];Events");

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

  //std::std::vector<ECuts> kCutsVector;
  std::vector<Arachne_alltracks> Arachne_alltrks;
  std::vector<Trajector> All_True_trajectors;
  std::vector<Trajector> All_RECO_trajectors;
  std::vector<TRUE_RECO_Energies_Trajectors> True_Reco_Energies;

  EventCount_RECO EventCounter_EFF;
  EventCount_RECO EventCounter_EFF_TRUTH;
  EventCount_RECO EventCounter_RECO;


  std::cout << "size of vector " << kCutsVector.size()<<std::endl;
  for (auto cut : kCutsVector){
  std::cout<<" count= "<<cut<<std::endl;

  EventCounter_RECO[cut]=0.0;
   EventCounter_EFF[cut]=0.0;
   EventCounter_EFF_TRUTH[cut]=0.0;


  }


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


int PDG_notmatch=0;
int PDG_match=0;

  std::cout << "Memory/time used so Far: " << procInfo.fMemResident/1000<< " MB" <<" time = "<<  procInfo.fCpuSys <<  " Sec"<<"\n";

  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"MC LOOP  "<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  double Pi = 3.14159265358979323846;
  for(int i=0; i<chw_MC->GetEntries(); ++i){

    if(i%1000==0) std::cout << (i/100) << " k " << std::flush;

    //=========================================
    // For every systematic, loop over the universes, and fill the
    // appropriate histogram in the MnvH1D
    //=========================================

    for (auto band : error_bands){
        //std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
        int unv_count = 0;
      std::vector<CVUniverse*> error_band_universes = band.second;
      for (auto universe : error_band_universes){

        // Tell the Event which entry in the TChain it's looking at
        universe->SetEntry(i);

//std::cout<<"Angle = "<< universe->GetThetaYmu()*180/Pi<<std::endl;


///////////////////////////////////////////
////
////  FILL CV
////
////
///////////////////////////////////////////
        if( universe->ShortName() == "cv"){
          EventCounter(*universe, kCutsVector, EventCounter_RECO, is_mc, Playlist_Info );
          EventCounter_RECO_TRUTHApplied(*universe, kTRUTHCutsVector,
            kCutsVector, EventCounter_EFF_TRUTH,
            EventCounter_EFF ,is_mc, kWeights_v1tune);
            if(  PassesCutsRECO(*universe,  is_mc , kCutsVector) ){





              int secondTrk = universe->Getindex2ndTrackhighestKE();
              Interaction_type Interaction_type_Event =  universe->Get_InteractionStackType();
              Material_type Material_type_Event = universe->Get_MaterialStackType();
              Particle_type Particle_type_Event =  universe->Get_NonParticleStackType(secondTrk);

              double Theta = universe->GetThetamu();
              double Pmu = universe -> GetPmu()/1000;
              double theta_degs = Theta*(180.0/3.1415926);
              double Emu = universe->GetEmu()*.001;


              h_Muon_PT_PZ_Material.GetComponentHist(Material_type_Event)->Fill(Pmu*std::sin(Theta), Pmu*std::cos(Theta), universe->GetWeight(kWeights_v1tune));
              h_Muon_PT_PZ_Interaction.GetComponentHist(Interaction_type_Event)->Fill(Pmu*std::sin(Theta), Pmu*std::cos(Theta), universe->GetWeight(kWeights_v1tune));
              h_Muon_PT_PZ_Particle.GetComponentHist(Particle_type_Event)->Fill(Pmu*std::sin(Theta), Pmu*std::cos(Theta), universe->GetWeight(kWeights_v1tune));

              h_Muon_PT_theta_Material.GetComponentHist(Material_type_Event)->Fill(Pmu*std::sin(Theta), theta_degs,universe->GetWeight(kWeights_v1tune));
              h_Muon_PT_theta_Interaction.GetComponentHist(Interaction_type_Event)->Fill(Pmu*std::sin(Theta), theta_degs,universe->GetWeight(kWeights_v1tune));
              h_Muon_PT_theta_Particle.GetComponentHist(Particle_type_Event)->Fill(Pmu*std::sin(Theta), theta_degs,universe->GetWeight(kWeights_v1tune));

              h_Muon_PZ_theta_Material.GetComponentHist(Material_type_Event)->Fill(Pmu*std::cos(Theta), theta_degs,universe->GetWeight(kWeights_v1tune));
              h_Muon_PZ_theta_Interaction.GetComponentHist(Interaction_type_Event)->Fill(Pmu*std::cos(Theta), theta_degs,universe->GetWeight(kWeights_v1tune));
              h_Muon_PZ_theta_Particle.GetComponentHist(Particle_type_Event)->Fill(Pmu*std::cos(Theta), theta_degs,universe->GetWeight(kWeights_v1tune));

              h_Muon_E_theta_Material.GetComponentHist(Material_type_Event)->Fill(Emu,theta_degs,universe->GetWeight(kWeights_v1tune));
              h_Muon_E_theta_Interaction.GetComponentHist(Interaction_type_Event)->Fill(Emu,theta_degs,universe->GetWeight(kWeights_v1tune));
              h_Muon_E_theta_Particle.GetComponentHist(Particle_type_Event)->Fill(Emu,theta_degs,universe->GetWeight(kWeights_v1tune));

              h_Muon_E_PZ_Material.GetComponentHist(Material_type_Event)->Fill(Emu, Pmu*std::cos(Theta),universe->GetWeight(kWeights_v1tune));
              h_Muon_E_PZ_Interaction.GetComponentHist(Interaction_type_Event)->Fill(Emu, Pmu*std::cos(Theta),universe->GetWeight(kWeights_v1tune));
              h_Muon_E_PZ_Particle.GetComponentHist(Particle_type_Event)->Fill(Emu, Pmu*std::cos(Theta),universe->GetWeight(kWeights_v1tune));

              h_Muon_E_PT_Material.GetComponentHist(Material_type_Event)->Fill(Emu, Pmu*std::sin(Theta),universe->GetWeight(kWeights_v1tune));
              h_Muon_E_PT_Interaction.GetComponentHist(Interaction_type_Event)->Fill(Emu, Pmu*std::sin(Theta),universe->GetWeight(kWeights_v1tune));
              h_Muon_E_PT_Particle.GetComponentHist(Particle_type_Event)->Fill(Emu, Pmu*std::sin(Theta),universe->GetWeight(kWeights_v1tune));

              h_cryoVertex_Z_R_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetVertex_z(),universe->GetVertex_r(), universe->GetWeight(kWeights_v1tune));
              h_cryoVertex_Z_R_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetVertex_z(),universe->GetVertex_r(), universe->GetWeight(kWeights_v1tune));
              h_cryoVertex_Z_R_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetVertex_z(),universe->GetVertex_r(), universe->GetWeight(kWeights_v1tune));


              ///////////////////////////////////
              //END of RECO CUTs/////
              ///////////////////////////////////
            }

            ///////////////////////////////////
            //END of RECO CUTs/////
            //////////////////////////////////


            ///////////////////////////////////////////
            ////
            ////  END OF CV
            ////
            ////
            ///////////////////////////////////////////
          }
        ///////////////////////////////////////////
        ////
        ////  END OF CV
        ////
        ////
        ///////////////////////////////////////////
        //=========================================
        // CUTS in each universe
        //==========================PlayList_iteratorPlayList_iterator===============

      if(PassesCutsRECO(*universe,  is_mc , kCutsVector) ){

      //  double weight_forMK = 1.0; //universe->GetWeight(kWeights_forMK);
        //double MK_Weight = universe->GetMKmodelWeight_local(weight_MK);

        double Theta = universe->GetThetamu();
        double Pmu = universe -> GetPmu()/1000;
        double Emu = universe->GetEmu()*.001;
        double theta_degs = Theta*(180.0/3.1415926);
        double wtg = universe->GetWeight(kWeights_v1tune);
        h_Muon_PT_PZ.univHist(universe)->Fill(Pmu*std::sin(Theta), Pmu*std::cos(Theta), wtg);
        h_Muon_PT_theta.univHist(universe)->Fill(Pmu*std::sin(Theta), theta_degs,wtg);
        h_Muon_PZ_theta.univHist(universe)->Fill( Pmu*std::cos(Theta), theta_degs,wtg);
        h_Muon_E_theta.univHist(universe)->Fill(Emu,theta_degs , wtg);
        h_Muon_E_PZ.univHist(universe)->Fill(Emu, Pmu*std::cos(Theta), wtg);
        h_Muon_E_PT.univHist(universe)->Fill(Emu, Pmu*std::sin(Theta), wtg);
        h_cryoVertex_Z_R.univHist(universe)->Fill(universe->GetVertex_z(),universe->GetVertex_r() , wtg);



      }
      //=========================================
      // each universe
      //=========================================

      // End if passed RECO cuts

      //=========================================
      // each universe
      //=========================================

        ////////////
        ///TRUTH + RECO Cuts for Universes
        ///////////

        if(PassesCutsTRUTH(*universe, kTRUTHCutsVector)){
                ///////////////////////////////////
                ///////Truth + RECO Cuts
                ///////////////////////////////////
          if(PassesCutsRECO(*universe,  is_mc , kCutsVector) ){
            double Theta = universe->GetThetamu();
            double Pmu = universe -> GetPmu()/1000;
            double Emu = universe->GetEmu()*.001;
            double theta_degs = Theta*(180.0/3.1415926);
            double wtg = universe->GetWeight(kWeights_v1tune);

            auto PDG_trklist = universe->GetVector_nonMuonTk_PDG_Parent();
            auto Energy_trklist = universe-> GetVector_nonMuonTk_Energy_GeV_Parent();
            auto Angle_trklist = universe->GetVector_nonMuonTk_Angle_wrtb_Degs_Parent();
            unsigned int secondTrk = universe->Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_lessthanAngle_muonNotinlist(PDG_trklist, Energy_trklist, Angle_trklist, EnergyFraction_vector);

            if(secondTrk==-999|| secondTrk==-9999 )continue;


            int secTrk_PDG = PDG_trklist.at(secondTrk);
            double secTrkAngle  = Angle_trklist.at(secondTrk);
            double secTrkKE = Energy_trklist.at(secondTrk);

            h_Muon_PT_PZ_TRUE_RECO.univHist(universe)->Fill(Pmu*std::sin(Theta), Pmu*std::cos(Theta), wtg);
            h_Muon_PT_theta_TRUE_RECO.univHist(universe)->Fill(Pmu*std::sin(Theta), theta_degs,wtg);
            h_Muon_PZ_theta_TRUE_RECO.univHist(universe)->Fill( Pmu*std::cos(Theta), theta_degs,wtg);
            h_Muon_E_theta_TRUE_RECO.univHist(universe)->Fill(Emu,theta_degs , wtg);
            h_Muon_E_PZ_TRUE_RECO.univHist(universe)->Fill(Emu, Pmu*std::cos(Theta), wtg);
            h_Muon_E_PT_TRUE_RECO.univHist(universe)->Fill(Emu, Pmu*std::sin(Theta), wtg);
            h_cryoVertex_Z_R_TRUE_RECO.univHist(universe)->Fill(universe->GetVertex_z(),universe->GetVertex_r() , wtg);
            h_2ndtrkangle_2ndTrkE_TRUE_RECO.univHist(universe)->Fill(secTrkAngle, secTrkKE, wtg);


            MnvR_Muon_PT_PZ->Fill(Pmu*std::sin(Theta),Pmu*std::cos(Theta),universe->GetPmuTransverseTrue(),universe->GetPmuLongitudinalTrue(),universe->ShortName(),unv_count,wtg);
            MnvR_Muon_PT_theta->Fill(Pmu*std::sin(Theta),theta_degs,universe->GetPmuTransverseTrue(),universe->GetTRUE_muANGLE_WRTB_DEG(),universe->ShortName(),unv_count,wtg);
            MnvR_Muon_PZ_theta->Fill(Pmu*std::cos(Theta),theta_degs,universe->GetPmuLongitudinalTrue(),universe->GetTRUE_muANGLE_WRTB_DEG(),universe->ShortName(),unv_count,wtg);
            MnvR_Muon_E_theta->Fill(Emu, theta_degs, universe->GetTRUE_Emu(), universe->GetTRUE_muANGLE_WRTB_DEG(),universe->ShortName(),unv_count,wtg);
            MnvR_Muon_E_PZ->Fill(Emu,Pmu*std::cos(Theta),universe->GetTRUE_Emu() ,universe->GetPmuLongitudinalTrue(),universe->ShortName(),unv_count,wtg);
            MnvR_Muon_E_PT->Fill(Emu,Pmu*std::sin(Theta),universe->GetTRUE_Emu() ,universe->GetPmuTransverseTrue(),universe->ShortName(),unv_count,wtg);
            MnvR_cryoVertex_Z_R->Fill(universe->GetVertex_z(),universe->GetVertex_r(),universe->GetTRUE_Vertex_z(),universe->GetTRUE_Vertex_r() ,universe->ShortName(), unv_count, wtg);

          }// END OF TRUTH + RECO CUTS

        }//END OF TRUTH PASS CUTS



        unv_count++;
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

h_Muon_PT_PZ.SyncCVHistos();
h_Muon_PT_theta.SyncCVHistos();
h_Muon_PZ_theta.SyncCVHistos();
h_Muon_E_theta.SyncCVHistos();
h_Muon_E_PZ.SyncCVHistos();
h_Muon_E_PT.SyncCVHistos();
h_cryoVertex_Z_R.SyncCVHistos();

h_Muon_PT_PZ_TRUE_RECO.SyncCVHistos();
h_Muon_PT_theta_TRUE_RECO.SyncCVHistos();
h_Muon_PZ_theta_TRUE_RECO.SyncCVHistos();
h_Muon_E_theta_TRUE_RECO.SyncCVHistos();
h_Muon_E_PZ_TRUE_RECO.SyncCVHistos();
h_Muon_E_PT_TRUE_RECO.SyncCVHistos();
h_cryoVertex_Z_R_TRUE_RECO.SyncCVHistos();
//MnvR_Muon_PT_PZ->SyncCVHistos();
//////////////////////////////////
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
  auto datatype = String_ISMC(is_mc);
  char c[playlist_name.length() + 1];
  char d[datatype.length() + 1];
  char rootpathway[OUTputRoot_pathway.length()+1];
  char ErrorStatus[sysmatics_status.length()+1];
  strcpy(rootpathway, OUTputRoot_pathway.c_str());
  strcpy(c, playlist_name.c_str());
  strcpy(d, datatype.c_str());
  strcpy(ErrorStatus, sysmatics_status.c_str());
  PrintCutstoScreen( kCutsVector , EventCounter_RECO, c, mcscale );
  MakeEfficiencyCutCVS(EventCounter_EFF_TRUTH, EventCounter_EFF , kCutsVector,c,mcPOT);
  Make_cvsOfCutsRate( kCutsVector , EventCounter_RECO, c, true, mcscale, mcPOT);


  //outFileName = "Histograms_test.root";
  //auto outFile = TFile::Open(outFileName);
  sprintf(outFileName, "%s/%s_2D%s_%s_%s.root",rootpathway, "Histograms",c,d,ErrorStatus);

  std::cout << "Writing output file to: " <<outFileName << std::endl;

  //TFile *outFile(outFileName, "RECREATE");
  TFile *outFile = new TFile(outFileName,"RECREATE");
  TChain POT_branch("Meta");
  POT_branch.Add(RootName.c_str());
  //TTree *oldtree = (TTree*)file->Get("Meta");
  TTree *clone = POT_branch.CloneTree();
  clone->Write();

  h_Muon_PT_PZ.hist->Write();
  PlotUtils::MnvH2D* h_MuonE_PT_PZ_FluxIntegrated = PlotUtils::flux_reweighter(playlist_fluxreweighter, nu_pdg, useNuEconstraint, NFlux_universe).GetIntegratedFluxReweighted(nu_pdg, h_Muon_PT_PZ.hist, Min_NuFluxEnergy, Max_NuFluxEnergy, useMuonCorrelations);
  h_MuonE_PT_PZ_FluxIntegrated->Clone()->Write("h_MuonE_PT_PZ_FluxIntegrated");
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


  h_Muon_PT_PZ_TRUE_RECO.hist->Write();
  h_Muon_PT_theta_TRUE_RECO.hist->Write();
  h_Muon_PZ_theta_TRUE_RECO.hist->Write();
  h_Muon_E_theta_TRUE_RECO.hist->Write();
  h_Muon_E_PZ_TRUE_RECO.hist->Write();
  h_Muon_E_PT_TRUE_RECO.hist->Write();
  h_cryoVertex_Z_R_TRUE_RECO.hist->Write();



  h_Muon_PT_PZ_Material.WriteToFile(*outFile);
  h_Muon_PT_PZ_Interaction.WriteToFile(*outFile);
  h_Muon_PT_PZ_Particle.WriteToFile(*outFile);
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


  ///2d


  const bool clear_bands = true;
  for (auto cat: MnvR_vector){
    MnvH2D *migrationH = NULL;
    MnvH2D *h_reco = NULL;
    MnvH2D *h_truth = NULL;
    bool check = cat->GetMigrationObjects(migrationH, h_reco, h_truth );
    //mresp
    PlotUtils::Hist2DWrapper<CVUniverse> mresp = PlotUtils::Hist2DWrapper<CVUniverse>(migrationH, error_bands, clear_bands);
    mresp.SyncCVHistos();
    mresp.hist->Write();
    h_reco->Write();
    h_truth->Write();
  }

  //MnvR_Muon_PT_PZ.hist->Write();

////////////////////////////////////////////////


/////2D hists////
///
  outFile->Close();



  TCanvas *can = new TCanvas("can", "can",1800,1600);
  //PlotUtils::MnvPlotter *Plotter();
  MnvPlotter *mnv_plotter = new MnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
//MakeTrue_interactionPlots(All_True_trajectors,"ME1F" ,5.0 ,"TRUE_interactions_cryotank", can,mnv_plotter);
// Bin width Norm
  //h_MuonPZ.hist->Scale(1,"width");

  //h_MuonPT.hist->Scale(1,"width");
  //h_MuonE.hist->Scale(1,"width");
  //h_CryoVertex_Z.hist->Scale(1,"width");
  //h_CryoVertex_X.hist->Scale(1,"width");
  //h_CryoVertex_Y.hist->Scale(1,"width");
  //h_CryoVertex_R.hist->Scale(1,"width");


  //h_secTrk_Energy_PROTON_TRUE.hist->Scale(1,"width");
  //h_secTrk_Energy_PROTON_TRUE_RECO.hist->Scale(1,"width");
  //h_secTrk_Energy_PION_TRUE.hist->Scale(1,"width");
  //h_secTrk_Energy_PION_TRUE_RECO.hist->Scale(1,"width");

  //h_secTrk_MidTheta_PROTON_TRUE.hist->Scale(1,"width");
  //h_secTrk_MidTheta_PROTON_TRUE_RECO.hist->Scale(1,"width");
  //h_secTrk_MidTheta_PION_TRUE.hist->Scale(1,"width");
  //h_secTrk_MidTheta_PION_TRUE_RECO.hist->Scale(1,"width");

  //h_secTrk_Openangle_PROTON_TRUE.hist->Scale(1,"width");
  //h_secTrk_Openangle_PROTON_TRUE_RECO.hist->Scale(1,"width");
  //h_secTrk_Openangle_PION_TRUE.hist->Scale(1,"width");
  //h_secTrk_Openangle_PION_TRUE_RECO.hist->Scale(1,"width");

std::cout<<" PDG_notmatch = " << PDG_notmatch<< "  PDG_match = "<< PDG_match<< std::endl;


  char  pdfName[1024];
  char pdf_start[1024];
  char pdf_end[1024];
  char XaxisName[1024];
  sprintf(pdfName, "MuonVars");
  //sprintf(pdf_start, "Optimization_figures.pdf(");
  //sprintf(pdf_end, "Optimization_figures.pdf)");

  //TCanvas *can = new TCanvas("", "");
  //dPlotUtils::MnvPlotter mvnPlotter(PlotUtils::kCCInclusiveHeliumStyle);


    //PlotCVAndError(h_MuonPZ.hist, "h_MuonPZ");
  //  PlotErrorSummary(h_MuonPZ.hist, "h_MuonPZ_ERROR_SUMMARY" ,"Energy (GeV)",can);
  //  PlotCVAndError(h_MuonPT.hist, "h_MuonPT");
  //  PlotErrorSummary(h_MuonPT.hist, "h_MuonPT_ERROR_SUMMARY", "Energy (GeV)",can);
  //  PlotCVAndError(h_MuonE.hist, "h_MuonE");
    //PlotErrorSummary(h_MuonE.hist,"h_MuonE_ERROR_SUMMARY" ,"h_MuonE_ERROR_SUMMARY", "Energy (GeV)",can);
    //PlotVertBand("BeamAngleX", "BeamAngleX_MuonE_ERROR", h_MuonE.hist);
    //PlotVertBand("BeamAngleY", "BeamAngleY_MuonE_ERROR", h_MuonE.hist);

    //PlotCVAndError(h_CryoVertex_Z.hist, "h_CryoVertex_Z");
  //  PlotCVAndError(h_CryoVertex_X.hist, "h_CryoVertex_X");
  //  PlotCVAndError(h_CryoVertex_Y.hist, "h_CryoVertex_Y");
  //  PlotCVAndError(h_CryoVertex_R.hist, "h_CryoVertex_R");


    //PlotCVAndError(h_secTrk_Energy_PROTON_TRUE.hist, "h_secTrk_Energy_PROTON_TRUE");
    //PlotCVAndError(h_secTrk_Energy_PROTON_TRUE_RECO.hist, "h_secTrk_Energy_PROTON_TRUE_RECO");
    //PlotErrorSummary(h_secTrk_Energy_PROTON_TRUE.hist, "h_secTrk_Energy_PROTON_TRUE_ERRORSummary", "Energy (GeV)",can);
    //PlotErrorSummary(h_secTrk_Energy_PROTON_TRUE_RECO.hist, "h_secTrk_Energy_PROTON_TRUE_RECO_ERRORSUMMARY", "Energy (GeV)",can);

    //h_secTrk_Energy_PROTON_TRUE_RECO.hist ->Divide(h_secTrk_Energy_PROTON_TRUE_RECO.hist ,h_secTrk_Energy_PROTON_TRUE.hist,1.0,1.0,"");
    //PlotCVAndError(h_secTrk_Energy_PROTON_TRUE_RECO.hist , "Efficiency_secTrkEnergy_PROTON");
    //PlotErrorSummary(h_secTrk_Energy_PROTON_TRUE_RECO.hist , "Efficiency_secTrkEnergy_PROTON_ERRORSUMMARY", "vertex Z(mm)",can);

    //PlotCVAndError(h_secTrk_Energy_PION_TRUE.hist, "h_secTrk_Energy_PION_TRUE");
    //PlotCVAndError(h_secTrk_Energy_PION_TRUE_RECO.hist, "h_secTrk_Energy_PION_TRUE_RECO");
    //PlotErrorSummary(h_secTrk_Energy_PION_TRUE.hist, "h_secTrk_Energy_PION_TRUE_ERRORSummary", "Energy (GeV)",can);
    //PlotErrorSummary(h_secTrk_Energy_PION_TRUE_RECO.hist, "h_secTrk_Energy_PION_TRUE_RECO_ERRORSUMMARY", "Energy (GeV)",can);

  //  h_secTrk_Energy_PION_TRUE_RECO.hist->Divide(h_secTrk_Energy_PION_TRUE_RECO.hist ,h_secTrk_Energy_PION_TRUE.hist,1.0,1.0,"");
  //  PlotCVAndError(h_secTrk_Energy_PION_TRUE_RECO.hist, "Efficiency_secTrkEnergy_PION");
  //  PlotErrorSummary(h_secTrk_Energy_PION_TRUE_RECO.hist, "Efficiency_secTrkEnergy_PION_ERRORSUMMARY", "vertex Z(mm)",can);

    ///////////
  //  PlotCVAndError(h_secTrk_MidTheta_PROTON_TRUE.hist, "h_secTrk_MidTheta_PROTON_TRUE");
  //  PlotCVAndError(h_secTrk_MidTheta_PROTON_TRUE_RECO.hist, "h_secTrk_MidTheta_PROTON_TRUE_RECO");
  //  PlotErrorSummary(h_secTrk_MidTheta_PROTON_TRUE.hist, "h_secTrk_MidTheta_PROTON_TRUE_ERRORSummary", "Angle (Deg)",can);
  //  PlotErrorSummary(h_secTrk_MidTheta_PROTON_TRUE_RECO.hist, "h_secTrk_MidTheta_PROTON_TRUE_RECO_ERRORSUMMARY", "Angle (Deg)",can);

//    h_secTrk_MidTheta_PROTON_TRUE_RECO.hist ->Divide(h_secTrk_MidTheta_PROTON_TRUE_RECO.hist ,h_secTrk_MidTheta_PROTON_TRUE.hist,1.0,1.0,"");
//    PlotCVAndError(h_secTrk_MidTheta_PROTON_TRUE_RECO.hist , "Efficiencyh_secTrk_MidTheta_PROTON");
//    PlotErrorSummary(h_secTrk_MidTheta_PROTON_TRUE_RECO.hist , "Efficiencyh_secTrk_MidTheta_PROTON_ERRORSUMMARY", "Angle (Deg)",can);

//    PlotCVAndError(h_secTrk_MidTheta_PION_TRUE.hist, "h_secTrk_MidTheta_PION_TRUE");
//    PlotCVAndError(h_secTrk_MidTheta_PION_TRUE_RECO.hist, "h_secTrk_MidTheta_PION_TRUE_RECO");
//    PlotErrorSummary(h_secTrk_MidTheta_PION_TRUE.hist, "h_secTrk_MidTheta_PION_TRUE_ERRORSummary", "Angle (Deg)",can);
//    PlotErrorSummary(h_secTrk_MidTheta_PION_TRUE_RECO.hist, "h_secTrk_MidTheta_PION_TRUE_RECO_ERRORSUMMARY", "Angle (Deg)",can);

  //  h_secTrk_MidTheta_PION_TRUE_RECO.hist->Divide(h_secTrk_MidTheta_PION_TRUE_RECO.hist ,h_secTrk_MidTheta_PION_TRUE.hist,1.0,1.0,"");
  //  PlotCVAndError(h_secTrk_MidTheta_PION_TRUE_RECO.hist, "Efficiencyh_secTrk_MidTheta_PION");
  //  PlotErrorSummary(h_secTrk_MidTheta_PION_TRUE_RECO.hist, "Efficiencyh_secTrk_MidTheta_PION_ERRORSUMMARY", "Angle (Deg)",can);
    ////////////////////

    ///////////
  //  PlotCVAndError(h_secTrk_Openangle_PROTON_TRUE.hist, "h_secTrk_Openangle_PROTON_TRUE");
  //  PlotCVAndError(h_secTrk_Openangle_PROTON_TRUE_RECO.hist, "h_secTrk_Openangle_PROTON_TRUE_RECO");
  //  PlotErrorSummary(h_secTrk_Openangle_PROTON_TRUE.hist, "h_secTrk_Openangle_PROTON_TRUE_ERRORSummary", "Angle (Deg)",can);
  //  PlotErrorSummary(h_secTrk_Openangle_PROTON_TRUE_RECO.hist, "h_secTrk_Openangle_PROTON_TRUE_RECO_ERRORSUMMARY", "Angle (Deg)",can);

  //  h_secTrk_Openangle_PROTON_TRUE_RECO.hist ->Divide(h_secTrk_Openangle_PROTON_TRUE_RECO.hist ,h_secTrk_Openangle_PROTON_TRUE.hist,1.0,1.0,"");
  //  PlotCVAndError(h_secTrk_Openangle_PROTON_TRUE_RECO.hist , "Efficiency_h_secTrk_Openangle_PROTON");
  //  PlotErrorSummary(h_secTrk_Openangle_PROTON_TRUE_RECO.hist , "Efficiency_h_secTrk_Openangle_PROTON_ERRORSUMMARY", "Angle (Deg)",can);

  //  PlotCVAndError(h_secTrk_Openangle_PION_TRUE.hist, "h_secTrk_Openangle_PION_TRUE");
  //  PlotCVAndError(h_secTrk_Openangle_PION_TRUE_RECO.hist, "h_secTrk_Openangle_PION_TRUE_RECO");
  //  PlotErrorSummary(h_secTrk_Openangle_PION_TRUE.hist, "h_secTrk_Openangle_PION_TRUE_ERRORSummary", "Angle (Deg)",can);
  //  PlotErrorSummary(h_secTrk_Openangle_PION_TRUE_RECO.hist, "h_secTrk_Openangle_PION_TRUE_RECO_ERRORSUMMARY", "Angle (Deg)",can);

//    h_secTrk_Openangle_PION_TRUE_RECO.hist->Divide(h_secTrk_Openangle_PION_TRUE_RECO.hist ,h_secTrk_Openangle_PION_TRUE.hist,1.0,1.0,"");
//    PlotCVAndError(h_secTrk_Openangle_PION_TRUE_RECO.hist, "Efficiency_h_secTrk_Openangle_PION");
//    PlotErrorSummary(h_secTrk_Openangle_PION_TRUE_RECO.hist, "Efficiency__secTrkopenangle_PION_ERRORSUMMARY", "Angle (Deg)",can);
    ////////////////////





  //  PlotCVAndError(Muon_PZ_FULLMC.hist, "Muon_PZ_FULLMC");
    // Plot Error Summary
   //PlotErrorSummary(h_CryoVertex_Z.hist, "h_CryoVertex_Z_ERROR_SUMMARY", "vertex Z(mm)",can);

  //Plot individual universes

    //PlotVertUniverse("EmuRangeCurve", universe, "TEST_E 0", h_MuonE.hist);
  //  PlotVertUniverse("EmuRangeCurve", universe, "TEST_Pz", Muon_PZ_FULLMC.hist);

    //PlotVertUniverse("EmuRangeCurve", universe, "TEST", Muon_PZ_FULLMC.hist);
  //  PlotVertUniverse("EmuRangeCurve", universe, "TEST_E 1", h_MuonE.hist);
  //  PlotVertUniverse("EmuRangeCurve", universe, "TEST_Pz", Muon_PZ_FULLMC.hist);



    //for (int i = 0; i < 5; ++i){ PlotVertUniverse("Flux", 1, "TEST", Muon_E_FULLMC.hist);}

    //Plot the Bands
  //  PlotVertBand("EmuRangeCurve", "TEST", Muon_PZ_FULLMC.hist);
  //  PlotVertBand("Flux", "TEST", Muon_PZ_FULLMC.hist);

    //PlotTotalError(Muon_PZ_FULLMC.hist, "TEST");


  //PlotVertBand("EmuRangeCurve", "EmuRangeCurve", h_MuonE.hist);
  //PlotVertBand("Flux", "Flux", h_MuonE.hist);
  //PlotTotalError(Muon_E_EmptyMC.hist, "Muon_E_EmptyMC");

    std::cout << "END OF Plotting" << std::endl;




  for(auto band : error_bands){
    std::vector<CVUniverse*> band_universes = band.second;
    for(unsigned int i_universe = 0; i_universe < band_universes.size(); ++i_universe){ delete band_universes[i_universe];}
  }

  std::cout << "Success" << std::endl;



//TCanvas *can = new TCanvas("can", "can",1800,1600);
can -> Print("Test.pdf");

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
  //ret_vec.push_back(kNonMu_is_Plausible);
  ret_vec.push_back(kVeto );
  ret_vec.push_back(kSix );
  ret_vec.push_back(kMatchVetoDeadPaddle);

  ret_vec.push_back(kMinosCoil );
  ret_vec.push_back(kMinosMatch);
  ret_vec.push_back(kMinosCurvature);
  ret_vec.push_back(kMinosCharge );

  ret_vec.push_back(kVertexConverge);
  ret_vec.push_back(kFiducialVolume );
  //ret_vec.push_back(kFiducialVolume_ExtraShell);
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
  True_vec.push_back(kTRUTHFiduical );
  //True_vec.push_back(kTRUTH_2ndTrkEnergythreshold );
  //True_vec.push_back(kTRUTH_2ndTrkAnlgethreshold );
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




std::vector<ME_helium_Playlists> GetPlayListVector() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ME_helium_Playlists> Playlist;




  //EMPTY
    //Playlist.push_back(kME1G);
    //Playlist.push_back(kME1A);
    //Playlist.push_back(kME1L);
    //Playlist.push_back(kME1M);
    //Playlist.push_back(kME1N);
  //Full
    //Playlist.push_back(kME1P);
    //Playlist.push_back(kME1C);
    //Playlist.push_back(kME1D);
    Playlist.push_back(kME1F);
    //Playlist.push_back(kME1E);
  return Playlist;
//#endif
}

std::vector<ME_helium_Playlists> GetTRUEPlayListVector() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ME_helium_Playlists> Playlist;

  Playlist.push_back(kME1G_Truth);

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
