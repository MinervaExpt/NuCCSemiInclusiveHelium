// Loop entries, make cuts, fill histograms.
// * Uses the New Systematics Framework and "Universe" objects.
// * loop universes, make cuts and fill histograms with the correct lateral
// shifts and weights for each universe.
// * TChain --> PlotUtils::ChainWrapper.
// * MnvHXD --> PlotUtils::HistWrapper.
// * Genie, flux, non-resonant pion, and some detector systematics calculated.
#include "Helium_runTRUTHLoop_NXLE_Validation.h"

std::string OUTputRoot_pathway = "/minerva/data/users/cnguyen/NX_LE_validation";


//=====================================================
// Functions
//=====================================================
std::vector<ECuts> GetRECOCutsVector();
std::vector<ECutsTRUTH> GetTRUTHCutsVector();
std::vector<ECutsTRUTH> GetTRUTHCutsVector_Energy();
std::vector<ECutsTRUTH> GetTRUTHCutsVector_Smearing();
std::vector<MuonVar> GetMUONVaribles();
std::vector<SecondTrkVar> GetPlayListSecondTrkVector();
std::vector<CryoVertex> GetCryoVertexVaribles();
std::vector<ME_helium_Playlists> GetPlayListVector();
std::vector<Weights> GetWeightVector();
//std::vector<ME_helium_Playlists> GetTRUEPlayListVector();
std::vector<Particle_type>  GetParicle_type();


//double Mev_to_GeV=.001;

// Get container of systematics

const bool m_RunCodeWithSystematics = false;





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





const std::vector<PlotUtils::NamedCategory<Particle_type>>
ParticleGroup_leadingvsnonleading_categories = {
  PlotUtils::NamedCategory<Particle_type>({kParticle_OTHER}, "Other"),
  PlotUtils::NamedCategory<Particle_type>({kPion_0},         "Pi0"),
  PlotUtils::NamedCategory<Particle_type>({kPion_neg},       "Pi^{-}"),
  PlotUtils::NamedCategory<Particle_type>({kPion_pos},       "Pi^{+}"),
  PlotUtils::NamedCategory<Particle_type>({kProton},         "Proton"),
  PlotUtils::NamedCategory<Particle_type>({kNeutron},   "Neutron")

};


/*const auto TracksGreaterThan2 = {  NamedCategory<int>({3},   "ThirdTrack"),
                                   NamedCategory<int>({4},   "FourthTrack"),
                                   NamedCategory<int>({5},   "FifthTrack"),
                                   NamedCategory<int>({6},   "SixthTrack"),
                                   NamedCategory<int>({7},   "SevethTrack"),
                                   NamedCategory<int>({8},   "EighthTrack")

                                 };*/

const int n_flux_universes = 25;
std::map< std::string, std::vector<HeliumCVUniverse_LENX_validation*> >
  GetErrorBands(PlotUtils::ChainWrapper* chain) {
    typedef std::map< std::string, std::vector<HeliumCVUniverse_LENX_validation*> > SystMap;
    //const int n_flux_universes = 50;
    SystMap error_bands;

    // CV
    error_bands[std::string("cv")].push_back( new HeliumCVUniverse_LENX_validation(chain) );

    //Detector systematics, lateral shifts

    if(m_RunCodeWithSystematics==true)
    {
      //GENIE
      //SystMap genie_systematics = PlotUtils::GetGenieSystematicsMap<HeliumCVUniverse_LENX_validation>(chain);
    //  error_bands.insert(genie_systematics.begin(), genie_systematics.end());

      //SystMap a2p2h_systematics = PlotUtils::Get2p2hSystematicsMap<HeliumCVUniverse_LENX_validation>(chain);
      //error_bands.insert(a2p2h_systematics.begin(), a2p2h_systematics.end());

      //SystMap RPA_systematics = PlotUtils::GetRPASystematicsMap<HeliumCVUniverse_LENX_validation>(chain);
      //error_bands.insert(RPA_systematics.begin(), RPA_systematics.end());
    }



//    SystMap muonP_systematics = PlotUtils::GetMuonSystematicsMap<HeliumCVUniverse>(chain,NSFDefaults::KludgedMinosMuonMomentum_Err);
  //  error_bands.insert(muonP_systematics.begin(), muonP_systematics.end());
    //std::cout << "C++ make muon resolution systematics" << std::endl;

    ///// MINOS ERROR systems
  //  SystMap MinervaMuon_systematics = PlotUtils::GetMinervaMuonSystematicsMap<HeliumCVUniverse>(chain);
  //  error_bands.insert(MinervaMuon_systematics.begin(), MinervaMuon_systematics.end());
    // Minerva Error System

    // MINOS efficiency
  //  SystMap MinosMuon_systematics = PlotUtils::GetMinosMuonSystematicsMap<HeliumCVUniverse>(chain);
  //  error_bands.insert(MinosMuon_systematics.begin(), MinosMuon_systematics.end());



    // Muon resolution
    //SystMap muonR_systematics = PlotUtils::GetMuonResolutionSystematicsMap<HeliumCVUniverse>(chain,NSFDefaults::muonResolution_Err);
    //error_bands.insert(muonR_systematics.begin(), muonR_systematics.end());
    //std::cout << "C++ make minos efficiency systematics" << std::endl;

    // Muon match efficiency
    //SystMap MinosEff_systematics = PlotUtils::GetMinosEfficiencySystematicsMap<HeliumCVUniverse>(chain);
    //error_bands.insert(MinosEff_systematics.begin(), MinosEff_systematics.end());

    // response efficiency
    //SystMap recoil_systematics = PlotUtils::GetRecoilSystematicsMap<HeliumCVUniverse>(chain,true);
    //error_bands.insert(recoil_systematics.begin(), recoil_systematics.end());
    //Flux

//    error_bands[std::string("MuonERC")].push_back(new MuonERangeCurvatureShiftUniverse(chain, -1)); //rob said bad need to fix
//    error_bands[std::string("MuonERC")].push_back(new MuonERangeCurvatureShiftUniverse(chain, +1));

  //  error_bands[std::string("MuonResolution_Lateal")].push_back(new MuonEnergyResolution(chain, -1));
    //error_bands[std::string("MuonResolution_Lateal")].push_back(new MuonEnergyResolution(chain, +1));


        //Flux


        //SystMap flux_systematics = PlotUtils::GetFluxSystematicsMap<HeliumCVUniverse>(chain,n_flux_universes);
        //error_bands.insert(flux_systematics.begin(), flux_systematics.end());

        //SystMap angle_systematics = PlotUtils::GetAngleSystematicsMap<HeliumCVUniverse>(chain,NSFDefaults::beamThetaX_Err,NSFDefaults::beamThetaY_Err);
        //error_bands.insert(angle_systematics.begin(), angle_systematics.end());
        //SystMap LowQ2Pi_systematics = PlotUtils::GetLowQ2PiSystematicsMap<HeliumCVUniverse>(chain);
        //error_bands.insert(LowQ2Pi_systematics.begin(), LowQ2Pi_systematics.end());



  // Non-res pi
  //SystMap nonrespi_systematics =
  //  PlotUtils::GetNonResPiSystematicsMap<HeliumCVUniverse>(chain);
  //error_bands.insert(nonrespi_systematics.begin(), nonrespi_systematics.end());


  return error_bands;
}
//======================================================================
//void EventCounter(const HeliumCVUniverse& , std::vector<ECuts> cuts, EventCount_Truth &Event_map ,bool is_mc,HeliumPlayListInfo Info );


// Main
void runEventLoop() {
  // Make a chain of events
  loadLibs();
double POT[4];
const std::vector<ECutsTRUTH> kTRUTHCutsVector = GetTRUTHCutsVector();
const std::vector<ECutsTRUTH> r = GetTRUTHCutsVector_Smearing();
const std::vector<ECutsTRUTH> kTRUTHCutsVector_Energy = GetTRUTHCutsVector_Energy();

const std::vector<ME_helium_Playlists> kPlayListVector = GetPlayListVector();
//const std::vector< ME_helium_Playlists> kTRUEPlayListVector = GetTRUEPlayListVector();
const std::vector<Weights> kWeightVector = GetWeightVector();
const std::vector<MuonVar> kMuonVaribles_vector = GetMUONVaribles();
const std::vector<SecondTrkVar> ksecTrkVaribles_vector = GetPlayListSecondTrkVector();

const std::vector<CryoVertex> kCryoVertexVaribles_vector = GetCryoVertexVaribles();

const std::vector<Particle_type> kSecondary_particle_vector = GetParicle_type();



//======================================================================
////////////////////ADDING TO CHAIN wrapper ///////////////////////////
//======================================================================
bool is_mc= true;

std::vector <True_Event_info> Nu_mu_secTrkParticle;
std::vector <True_Event_info> Nu_e_secTrkParticle;
std::vector <True_Event_info> Electron_secTrkParticle;
std::vector <True_Event_info> Other_secTrkParticle;
std::vector <True_Event_info> fourHelium_secTrkParticle;
std::vector <True_Event_info> N_A_secTrkParticle;
std::vector <True_Event_info> secTrk_999_Particle;
std::vector <ALL_True_Event_info> ALL_EventInfoNu_e_secTrkParticle;
std::vector <ALL_True_Event_info> ALL_EventInfoNu_mu_secTrkParticle;


  MinervaUniverse::SetNuEConstraint(true);
  MinervaUniverse::SetAnalysisNuPDG(14);
  MinervaUniverse::SetNFluxUniverses(n_flux_universes);
  MinervaUniverse::SetProcessingEroica();

  //std::string playlist = GetPlaylist(PlayList_iterator);
  //MinervaUniverse::SetPlaylist(playlist);


 //std::string seestring = MinervaUniverse::GetPlaylist();
  //MinervaUniverse::Set_Multiple_resetPlaylist(true);
  //HeliumPlayListInfo Playlist_Info(playlist);
//  std::cout<<"Working with Playlist =  "<<   seestring <<std::endl;

  //MinervaUniverse::SetNonResPiReweight(true);
  //auto Playlist_txtFILEPath = GetPlaylist_txtFILE_path(PlayList_iterator, is_mc );
  //std::string Playlist_txtFILEPath = "/minerva/data/users/mascenci/genie_DAN/SIM_minerva13B_minerva_000110_10111213_GENIE_v21r1p1.root";
//std::string Playlist_txtFILEPath = "/minerva/data/users/mascenci/genie_DAN/SIM_minerva13A_minerva_00011000_GENIE_v21r1p1.root";
  //std::string Playlist_txtFILEPath = "/minerva/data/users/mascenci/genie_DAN/SIM_minerva13B_minerva_000110_10111213_GENIE_v21r1p1.root";


//mvn13C


// new
//std::string Playlist_txtFILEPath = "/minerva/data/users/mascenci/genie_DAN/SIM_minerva13C_000120_00-24_GENIE_v21r1p1.root"; //NX Mvn13C
//std::string Playlist_txtFILEPath = "/pnfs/minerva/persistent/users/drut1186/CCQENu_Anatuples/LowEnergy_BugFix/MC/ccqenu_mc_minerva13C_FinalProc/grid/central_value/minerva/ana/v10r8p9/00/01/32/*/*.root"; // Erocia
std::string Playlist_txtFILEPath ="/minerva/app/users/cnguyen/cmtuser/Minerva_v22r1p1Helium/Ana/VetoWallStudies/scripts/ChainWrapper_LE/playlists/Minerva13C_MC_merg.txt";
// old
///pnfs/minerva/persistent/users/drut1186/CCQENu_Anatuples/LowEnergy_BugFix/MC/ccqenu_mc_minerva13C_FinalProc/grid/central_value/minerva/ana/


  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"Adding to Chain Wrapper For Loop   "<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  PlotUtils::ChainWrapper* chw_MC = makeChainWrapperPtr(Playlist_txtFILEPath.c_str(), "Truth");
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"Adding to Chain Wrapper For POT counter   "<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  //PlotUtils::ChainWrapper* mcchainPOT = makeChainWrapperPtr(Playlist_txtFILEPath.c_str(), "Meta");

  //======================================================================
  ///////////////////Making/adding to error bands  ///////////////////////////
  //======================================================================
//std::map< std::string, std::vector<HeliumCVUniverse*> > error_bands = GetErrorBands(chw_FullMC);
std::map< std::string, std::vector<HeliumCVUniverse_LENX_validation*> > error_bands= GetErrorBands(chw_MC);
//double mcPOT = GetPOT(chw_MC, "MC");
std::cout<<"Number of Universes set is = "<< 	MinervaUniverse::GetNFluxUniverses()<<std::endl;
//std::string NumU = MinervaUniverse::GetNFluxUniverses()<<std::endl;
//Debug("Number of Universes set is = " );
//Debug(NumU);
//MinervaUniverse::SetNFluxUniverses(25);
POTCounter pot_counter;


//std::cout<<"The Playlist that is set is = "<< seestring <<std::endl;
std::cout<<"The Playlist Root = "<< Playlist_txtFILEPath<<std::endl;
 ///pnfs/minerva/persistent/users/cnguyen/ME_G1_Merg/*.root



  auto mcscale = 1.0; //Data_POT_full/ MC_POT_full;
  time_t now = time(0);
  tm *ltm = localtime(&now);
   int m_datemonth = 1 + ltm->tm_mon;
   int m_datehour= ltm->tm_hour;
   int m_datemin=ltm->tm_min;
   int m_dateday=ltm->tm_mday;


  int count=1;


//Bins for varibles //
//Muons ///////////////////
std::vector<double> Ebin_vector = GetBinMuonVector(kE);
std::vector<double> Pzbin_vector= GetBinMuonVector(kP_Z);
std::vector<double> PTbin_vector= GetBinMuonVector(kP_T);
std::vector<double> MuonThetabin_vector= GetBinMuonVector(kAngleWRTB);
std::vector<double> Muon_curvatureSig_vector= GetBinMuonVector(kcurvatureSig);
std::vector<double> MuonCharge_vector= GetBinMuonVector(kCharge);
std::vector<double> MuonMatchtoMinos_vector= GetBinMuonVector(kMuonMatchtoMinos);
std::vector<double> MuonMatchtoVeto_vector= GetBinMuonVector(kMuonMatchtoVeto);

std::vector<double> Minos_R_vector= GetBinMuonVector(kminos_R);
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
std::vector<double> TrackSize_vector= GetBinMuonVector(ktracksize);

////////////////////////
std::vector<double> Vertex_Xbins= GetBinvertexVector(kX);
std::vector<double> Vertex_Ybins= GetBinvertexVector(kY);
std::vector<double> Vertex_Zbins= GetBinvertexVector(kZ);
std::vector<double> Vertex_Rbins= GetBinvertexVector(kR);

std::vector<double> Vertex_DOCAbins= GetBinMuonVector(kDOCA_muon);
std::vector<double> Vertex_secondTrkEbins= GetSecondTrkVarVector(ksecE_Proton); //GetSecondTrkVarVector(ksecE);
std::vector<double> Vertex_secondTrkEbin_Proton_vector= GetSecondTrkVarVector(ksecE_Proton);
std::sort(Vertex_secondTrkEbin_Proton_vector.begin(),Vertex_secondTrkEbin_Proton_vector.end());
std::vector<double> Vertex_secondTrkTheta_bins= GetSecondTrkVarVector(kFullAngle);
std::vector<double> Vertex_secondTrkDOCA_bins= GetSecondTrkVarVector(kDOCA);
std::vector<double> Vertex_secondTrkPathway_bins= GetSecondTrkVarVector(kPathway);

////////////////
//muon Varibles///
////////////////
/*
//PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE("h_MuonE", "Muon_{E} NEW Method", Ebin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonE_TRUE("h_MuonE_TRUE", "Muon_{E} NEW Method", Ebin_vector , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonE_TRUE_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonE_TRUE_Material", Ebin_vector ,"MuonE_TRUE_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonE_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_MuonE_TRUE_Interaction", Ebin_vector ,"MuonE_TRUE_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_MuonE_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_MuonE_TRUE_Particle", Ebin_vector ,"MuonE_TRUE_Particle; [GeV];Events");


PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPZ_TRUE("h_MuonPZ_TRUE", "Muon_{PZ} NEW Method",  Pzbin_vector , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonPZ_TRUE_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonPZ_TRUE_Material", Pzbin_vector ,"h_MuonPZ_TRUE_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonPZ_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_MuonPZ_TRUE_Interaction", Pzbin_vector ,"h_MuonPZ_TRUE_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_MuonPZ_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_MuonPZ_TRUE_Particle", Pzbin_vector ,"h_MuonPZ_TRUE_Particle; [GeV];Events");


PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPT_TRUE("h_MuonPT_TRUE", "Muon_{PT} NEW Method",  PTbin_vector , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonPT_TRUE_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonPT_TRUE_Material", PTbin_vector ,"h_MuonPT_TRUE_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonPT_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_MuonPT_TRUE_Interaction", PTbin_vector ,"h_MuonPT_TRUE_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_MuonPT_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_MuonPT_TRUE_Particle", PTbin_vector ,"h_MuonPT_TRUE_Particle; [GeV];Events");



PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonTheta_TRUE("h_MuonTheta_TRUE", "MuonTheta [Deg]",  MuonThetabin_vector , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonTheta_TRUE_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonTheta_TRUE_Material", MuonThetabin_vector ,"h_MuonTheta_TRUE_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonTheta_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_MuonTheta_TRUE_Interaction", MuonThetabin_vector ,"h_MuonTheta_TRUE_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_MuonTheta_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_MuonTheta_TRUE_Particle", MuonThetabin_vector ,"h_MuonTheta_TRUE_Particle; [GeV];Events");

PlotUtils::HistWrapper<HeliumCVUniverse> h_MuonPhi_TRUE("h_MuonPhi_TRUE", "MuonTheta [Deg]",  MuonThetabin_vector , error_bands);//
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_MuonPhi_TRUE_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_MuonPhi_TRUE_Material", AnglePhi_vector ,"h_MuonPhi_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_MuonPhi_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_MuonPhi_TRUE_Interaction", AnglePhi_vector ,"h_MuonPhi_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_MuonPhi_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_MuonPhi_TRUE_Particle", AnglePhi_vector ,"h_MuonPhi_Particle; [GeV];Events");




PlotUtils::HistWrapper<HeliumCVUniverse> h_Tracksize_TRUE("h_Tracksize_TRUE", "Track size [N]",  TrackSize_vector , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_Tracksize_TRUE_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_Tracksize_TRUE_Material", TrackSize_vector ,"h_Tracksize_TRUE_Material; [Tracknumber];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_Tracksize_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_Tracksize_TRUE_Interaction", TrackSize_vector ,"h_Tracksize_TRUE_Interaction; [Tracknumber];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_Tracksize_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_Tracksize_TRUE_Particle", TrackSize_vector ,"h_Tracksize_TRUE_Particle; [Tracknumber];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_TracksizeALL_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_TracksizeALL_TRUE_Particle", TrackSize_vector ,"h_TracksizeALL_TRUE_Particle; [Tracknumber];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_TracksizeALL_leadingTRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_TracksizeALL_leadingTRUE_Particle", TrackSize_vector ,"h_TracksizeALL_leadingTRUE_Particle; [Tracknumber];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_TracksizeALL_nonleadingTRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_TracksizeALL_nonleadingTRUE_Particle", TrackSize_vector ,"h_TracksizeALL_nonleadingTRUE_Particle; [Tracknumber];Events");


///////////////////////////////////////
//
///////////////////////////////////////
MnvH2D *h_2d_PZ_PT_TRUE            =    new MnvH2D("h_2d_PZ_PT_TRUE", "h_2d_PZ_PT_TRUE",Pzbin_vector.size()-1, Pzbin_vector.data() ,PTbin_vector.size()-1, PTbin_vector.data()  );

MnvH2D *h_2d_E_PZ_TRUE             =    new MnvH2D("h_2d_E_PZ_TRUE", "h_2d_E_PZ_TRUE", Ebin_vector.size()-1, Ebin_vector.data(),Pzbin_vector.size()-1, Pzbin_vector.data()  );

MnvH2D *h_2d_Theta_PZ_TRUE         =    new MnvH2D("h_2d_Theta_PZ_TRUE", "h_2d_Theta_PZ_TRUE", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),Pzbin_vector.size()-1, Pzbin_vector.data()  );

MnvH2D *h_2d_E_PT_TRUE             =    new MnvH2D("h_2d_E_PT_TRUE", "h_2d_E_PT_TRUE", Ebin_vector.size()-1, Ebin_vector.data(),PTbin_vector.size()-1, PTbin_vector.data()  );
MnvH2D *h_2d_Theta_PT_TRUE         =    new MnvH2D("h_2d_Theta_PT_TRUE", "h_2d_Theta_PT_TRUE", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),PTbin_vector.size()-1, PTbin_vector.data()  );
//MnvH2D *h_2d_Theta_PT_TRUE_RECO    =    new MnvH2D("h_2d_Theta_PT_TRUE_RECO", "h_2d_Theta_PT_TRUE_RECO", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),PTbin_vector.size()-1, PTbin_vector.data()  );

///////////////////////////////////////
//
///////////////////////////////////////
MnvH2D *h_2d_Theta_2ndTrkE_TRUE         =    new MnvH2D("h_2d_Theta_2ndTrkE_TRUE", "h_2d_Theta_2ndTrkE_TRUE", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );
MnvH2D *h_2d_muonE_2ndTrkE_TRUE         =    new MnvH2D("h_2d_muonE_2ndTrkE_TRUE", "h_2d_muonE_2ndTrkE_TRUE", Ebin_vector.size()-1, Ebin_vector.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );
MnvH2D *h_2d_muonPT_2ndTrkE_TRUE         =    new MnvH2D("h_2d_muonPT_2ndTrkE_TRUE", "h_2d_muonPT_2ndTrkE_TRUE",  PTbin_vector.size()-1,  PTbin_vector.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );
MnvH2D *h_2d_muonPZ_2ndTrkE_TRUE         =    new MnvH2D("h_2d_muonPZ_2ndTrkE_TRUE", "h_2d_muonPZ_2ndTrkE_TRUE",  Pzbin_vector.size()-1,  Pzbin_vector.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );
///////////////////////////////////////
//
///////////////////////////////////////
MnvH2D *h_2d_Theta_2ndTrKangle_TRUE         =    new MnvH2D("h_2d_Theta_2ndTrKangle_TRUE", "h_2d_Theta_2ndTrKangle_TRUE", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),Vertex_secondTrkTheta_bins.size()-1, Vertex_secondTrkTheta_bins.data()  );
MnvH2D *h_2d_muonE_2ndTrkangle_TRUE         =    new MnvH2D("h_2d_muonE_2ndTrkangle_TRUE", "h_2d_muonE_2ndTrkangle_TRUE", Ebin_vector.size()-1, Ebin_vector.data(),Vertex_secondTrkTheta_bins.size()-1, Vertex_secondTrkTheta_bins.data()  );
MnvH2D *h_2d_muonPT_2ndTrkangle_TRUE         =    new MnvH2D("h_2d_muonPT_2ndTrkangle_TRUE", "h_2d_muonPT_2ndTrkangle_TRUE",  PTbin_vector.size()-1,  PTbin_vector.data(),Vertex_secondTrkTheta_bins.size()-1, Vertex_secondTrkTheta_bins.data()  );
MnvH2D *h_2d_muonPZ_2ndTrkangle_TRUE         =    new MnvH2D("h_2d_muonPZ_2ndTrkangle_TRUE", "h_2d_muonPZ_2ndTrkangle_TRUE",  Pzbin_vector.size()-1,  Pzbin_vector.data(),Vertex_secondTrkTheta_bins.size()-1, Vertex_secondTrkTheta_bins.data()  );
///////////////////////////////////////
//
///////////////////////////////////////


//MnvH2D *h_2d_Theta_PT_TRUE         =    new MnvH2D("h_2d_Theta_PT_TRUE", "h_2d_Theta_PT_TRUE", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),PTbin_vector.size()-1, PTbin_vector.data()  );
//MnvH2D *h_2d_Theta_PT_TRUE_RECO    =    new MnvH2D("h_2d_Theta_PT_TRUE_RECO", "h_2d_Theta_PT_TRUE_RECO", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),PTbin_vector.size()-1, PTbin_vector.data()  );
///////////////////////////////////////
//
///////////////////////////////////////

MnvH2D *h_2d_2ndtrkangle_2ndTrkE_TRUE         =    new MnvH2D("h_2d_2ndtrkangle_2ndTrkE_TRUE", "h_2d_2ndtrkangle_2ndTrkE_TRUE", Vertex_secondTrkTheta_bins.size()-1, Vertex_secondTrkTheta_bins.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );
MnvH2D *h_2d_2ndtrkangle_2ndTrkE_Proton_TRUE         =    new MnvH2D("h_2d_2ndtrkangle_2ndTrkE_Proton_TRUE", "h_2d_2ndtrkangle_2ndTrkE_Proton_TRUE", Vertex_secondTrkTheta_bins.size()-1, Vertex_secondTrkTheta_bins.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );
MnvH2D *h_2d_2ndtrkangle_2ndTrkE_Pion_TRUE         =    new MnvH2D("h_2d_2ndtrkangle_2ndTrkE_Pion_TRUE", "h_2d_2ndtrkangle_2ndTrkE_Pion_TRUE", Vertex_secondTrkTheta_bins.size()-1, Vertex_secondTrkTheta_bins.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );
MnvH2D *h_2d_2ndtrkangle_2ndTrkE_Pion0_TRUE         =    new MnvH2D("h_2d_2ndtrkangle_2ndTrkE_Pion0_TRUE", "h_2d_2ndtrkangle_2ndTrkE_Pion0_TRUE", Vertex_secondTrkTheta_bins.size()-1, Vertex_secondTrkTheta_bins.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );
MnvH2D *h_2d_2ndtrkangle_2ndTrkE_Pion_neg_pos_TRUE         =    new MnvH2D("h_2d_2ndtrkangle_2ndTrkE_Pion_neg_pos_TRUE", "h_2d_2ndtrkangle_2ndTrkE_Pion_neg_pos_TRUE", Vertex_secondTrkTheta_bins.size()-1, Vertex_secondTrkTheta_bins.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );
MnvH2D *h_2d_2ndtrkangle_2ndTrkE_dimuon_TRUE         =    new MnvH2D("h_2d_2ndtrkangle_2ndTrkE_dimuon_TRUE", "h_2d_2ndtrkangle_2ndTrkE_dimuon_TRUE", Vertex_secondTrkTheta_bins.size()-1, Vertex_secondTrkTheta_bins.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );
////////////////
//Vertex Hist///
////////////////
PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_X_TRUE("h_CryoVertex_X_TRUE", "h_CryoVertex_X",  Vertex_Xbins , error_bands);
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_X_TRUE_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_X_TRUE_Material", Vertex_Xbins ,"h_CryoVertex_X_TRUE_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_CryoVertex_X_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_CryoVertex_X_TRUE_Interaction", Vertex_Xbins ,"h_CryoVertex_X_TRUE_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_CryoVertex_X_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_CryoVertex_X_TRUE_Particle", Vertex_Xbins ,"h_CryoVertex_X_TRUE_Particle; [mm];Events");

PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Y_TRUE("h_CryoVertex_Y_TRUE", "Vertex_Y",  Vertex_Ybins , error_bands);
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Y_TRUE_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Y_TRUE_Material", Vertex_Ybins ,"h_CryoVertex_Y_TRUE_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_CryoVertex_Y_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_CryoVertex_Y_TRUE_Interaction", Vertex_Ybins ,"h_CryoVertex_Y_TRUE_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_CryoVertex_Y_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_CryoVertex_Y_TRUE_Particle", Vertex_Ybins ,"h_CryoVertex_Y_TRUE_Particle; [mm];Events");


PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_Z_TRUE("h_CryoVertex_Z_TRUE", "Vertex_Z",  Vertex_Zbins , error_bands);//
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Z_TRUE_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Z_TRUE_Material", Vertex_Zbins ,"h_CryoVertex_Z_TRUE_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_CryoVertex_Z_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_CryoVertex_Z_TRUE_Interaction", Vertex_Zbins ,"h_CryoVertex_Z_TRUE_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_CryoVertex_Z_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_CryoVertex_Z_TRUE_Particle", Vertex_Zbins ,"h_CryoVertex_Z_TRUE_Particle; [mm];Events");


PlotUtils::HistWrapper<HeliumCVUniverse> h_CryoVertex_R_TRUE("h_CryoVertex_R_TRUE", "h_CryoVertex_R",  Vertex_Rbins , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_R_TRUE_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_R_TRUE_Material", Vertex_Rbins ,"h_CryoVertex_R_TRUE_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_CryoVertex_R_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_CryoVertex_R_TRUE_Interaction", Vertex_Rbins ,"h_CryoVertex_R_TRUE_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_CryoVertex_R_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_CryoVertex_R_TRUE_Particle", Vertex_Rbins ,"h_CryoVertex_R_TRUE_Particle; [mm];Events");




PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Openangle_TRUE("h_secTrk_Openangle_TRUE", "h_secTrk_TRUE_Openangle ",  Vertex_secondTrkTheta_bins , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_Openangle_TRUE_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_Openangle_TRUE_Material", Vertex_secondTrkTheta_bins ,"h_secTrk_Openangle_TRUE_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_secTrk_Openangle_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_secTrk_Openangle_TRUE_Interaction", Vertex_secondTrkTheta_bins ,"h_secTrk_Openangle_TRUE_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_Openangle_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_Openangle_TRUE_Particle", Vertex_secondTrkTheta_bins ,"h_secTrk_Openangle_TRUE_Particle; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_Openangle_TRUE_RECO_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_Openangle_TRUE_RECO_Material", Vertex_secondTrkTheta_bins ,"h_secTrk_Openangle_TRUE_Material; [mm];Events");



//PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Pathlength("h_secTrk_Pathlength", "h_secTrk Pathlength ",  Vertex_secondTrkPathway_bins , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Pathlength_TRUE("h_secTrk_Pathlength_TRUE", "h_secTrk Pathlength ",  Vertex_secondTrkPathway_bins , error_bands);
//PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Pathlength_TRUE_RECO("h_secTrk_Pathlength_TRUE_RECO", "h_secTrk Pathlength ",  Vertex_secondTrkPathway_bins , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_Pathlength_TRUE_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_Pathlength_TRUE_Material", Vertex_secondTrkPathway_bins ,"h_secTrk_Pathlength_TRUE_Material; [cm^2/g];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_secTrk_Pathlength_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_secTrk_Pathlength_TRUE_Interaction", Vertex_secondTrkPathway_bins ,"h_secTrk_Pathlength_TRUE_Interaction; [cm^2/g];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_Pathlength_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_Pathlength_TRUE_Particle", Vertex_secondTrkPathway_bins ,"h_secTrk_Pathlength_TRUE_Particle; [cm^2/g];Events");

PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Theta_TRUE("h_secTrk_Theta_TRUE", "h_secTrk_Theta NEW Method",  Vertex_secondTrkTheta_bins , error_bands);
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_Theta_TRUE_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_Theta_TRUE_Material", Vertex_secondTrkTheta_bins ,"h_secTrk_Theta_TRUE_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_secTrk_Theta_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_secTrk_Theta_TRUE_Interaction", Vertex_secondTrkTheta_bins ,"h_secTrk_Theta_TRUE_Interaction; [[GeV;Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_Theta_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_Theta_TRUE_Particle", Vertex_secondTrkTheta_bins ,"h_secTrk_Theta_TRUE_Particle; [GeV];Events");


PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_Theta_TRUE_leading_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_leadingvsnonleading_categories, "h_secTrk_Theta_TRUE_leading_Particle", Vertex_secondTrkTheta_bins ,"h_secTrk_Theta_TRUE_leading_Particle; [Deg];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_Theta_TRUE_Nonleading_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_leadingvsnonleading_categories, "h_secTrk_Theta_TRUE_Nonleading_Particle", Vertex_secondTrkTheta_bins ,"h_secTrk_Theta_TRUE_nonleading_Particle; [Deg];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_Theta_TRUE_leadingFULL_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_Theta_TRUE_leadingFULL_Particle", Vertex_secondTrkTheta_bins ,"h_secTrk_Theta_TRUE_leadingFULL_Particle; [Deg];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_Theta_TRUE_NonleadingFULL_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_Theta_TRUE_NonleadingFULL_Particle", Vertex_secondTrkTheta_bins ,"h_secTrk_Theta_TRUE_NonleadingFULL_Particle; [Deg];Events");



PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Energy_TRUE("h_secTrk_Energy_TRUE", "h_secTrk_Energy NEW Method",  Vertex_secondTrkEbins, error_bands);
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_Energy_TRUE_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_Energy_TRUE_Material", Vertex_secondTrkEbins ,"h_secTrk_Energy_TRUE_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_secTrk_Energy_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_secTrk_Energy_TRUE_Interaction", Vertex_secondTrkEbins ,"h_secTrk_Energy_TRUE_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_Energy_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_Energy_TRUE_Particle", Vertex_secondTrkEbins ,"h_secTrk_Energy_TRUE_Particle; [GeV];Events");

/////////////////

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_ALLKE_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_ALLKE_TRUE_Particle", Vertex_secondTrkEbins ,"h_secTrk_ALLKE_TRUE_Particle; [Deg];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_ALLKEFULL_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories ,"h_secTrk_ALLKEFULL_TRUE_Particle", Vertex_secondTrkEbins ,"h_secTrk_ALLKEFULL_TRUE_Particle; [Deg];Events");


PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_KE_TRUE_leading_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_leadingvsnonleading_categories, "h_secTrk_KE_TRUE_leading_Particle", Vertex_secondTrkEbins ,"h_secTrk_KE_TRUE_leading_Particle; [Deg];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_KE_TRUE_Nonleading_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_leadingvsnonleading_categories, "h_secTrk_KE_TRUE_Nonleading_Particle", Vertex_secondTrkEbins ,"h_secTrk_KE_TRUE_nonleading_Particle; [Deg];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_KE_TRUE_leadingFULL_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_KE_TRUE_leadingFULL_Particle", Vertex_secondTrkEbins ,"h_secTrk_KE_TRUE_leadingFULL_Particle; [Deg];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_KE_TRUE_NonleadingFULL_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_KE_TRUE_NonleadingFULL_Particle", Vertex_secondTrkEbins ,"h_secTrk_KE_TRUE_NonleadingFULL_Particle; [Deg];Events");





PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Energy_PION_TRUE("h_secTrk_Energy_PION_TRUE", "h_secTrk_Energy PION (TRUE) ",  Vertex_secondTrkEbin_Proton_vector, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Theta_PION_TRUE("h_secTrk_Theta_PION_TRUE", "h_secTrk_Theta PION(TRUE)",  Vertex_secondTrkTheta_bins , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrkopenangle_PION_TRUE("h_secTrkopenangle_PION_TRUE", "h_secTrkopenangle PION (TRUE)",  Vertex_secondTrkTheta_bins , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Energy_PION0_TRUE("h_secTrk_Energy_PION0_TRUE", "h_secTrk_Energy PION0 (TRUE) ",  Vertex_secondTrkEbin_Proton_vector, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Theta_PION0_TRUE("h_secTrk_Theta_PION0_TRUE", "h_secTrk_Theta PION0(TRUE)",  Vertex_secondTrkTheta_bins , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrkopenangle_PION0_TRUE("h_secTrkopenangle_PION0_TRUE", "h_secTrkopenangle PION0 (TRUE)",  Vertex_secondTrkTheta_bins , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Energy_PION_neg_pos_TRUE("h_secTrk_Energy_PION_neg_pos_TRUE", "h_secTrk_Energy PION_neg_pos (TRUE) ",  Vertex_secondTrkEbin_Proton_vector, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Theta_PION_neg_pos_TRUE("h_secTrk_Theta_PION_neg_pos_TRUE", "h_secTrk_Theta PION_neg_pos(TRUE)",  Vertex_secondTrkTheta_bins , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrkopenangle_PION_neg_pos_TRUE("h_secTrkopenangle_PION_neg_pos_TRUE", "h_secTrkopenangle PION_neg_pos (TRUE)",  Vertex_secondTrkTheta_bins , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_ALLangles_TRUE("h_secTrk_ALLangles_TRUE", "h_secTrk_Theta PION0(TRUE)",  Vertex_secondTrkTheta_bins , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_ALLangles_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_ALLangles_TRUE_Particle", Vertex_secondTrkTheta_bins ,"h_secTrk_ALLangles_TRUE_Particle; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_ALLanglesFULL_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_ALLanglesFULL_TRUE_Particle", Vertex_secondTrkTheta_bins ,"h_secTrk_ALLanglesFULL_TRUE_Particle; [mm];Events");



PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Energy_PROTON_TRUE("h_secTrk_Energy_PROTON_TRUE", "h_secTrk_Energy Proton(TRUE)",  Vertex_secondTrkEbin_Proton_vector, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Theta_PROTON_TRUE("h_secTrk_Theta_PROTON_TRUE", "h_secTrk_Theta Proton(TRUE)",  Vertex_secondTrkTheta_bins , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrkopenangle_PROTON_TRUE("h_secTrkopenangle_PROTON_TRUE", "h_secTrkopenangle Proton(TRUE)",  Vertex_secondTrkTheta_bins , error_bands);

PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Energy_Dimuon_TRUE("h_secTrk_Energy_Dimuon_TRUE", "h_secTrk_Energy Dimuon(TRUE)",  Vertex_secondTrkEbin_Proton_vector, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Theta_Dimuon_TRUE("h_secTrk_Theta_Dimuon_TRUE", "h_secTrk_Theta Dimuon(TRUE)",  Vertex_secondTrkTheta_bins , error_bands);



//PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_DOCA("h_secTrk_DOCA", "h_secTrk DOCA NEW Method",  Vertex_secondTrkDOCA_bins , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_DOCA_TRUE("h_secTrk_DOCA_TRUE", "h_secTrk DOCA NEW Method",  Vertex_secondTrkDOCA_bins , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_DOCA_TRUE_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_DOCA_TRUE_Material", Vertex_secondTrkDOCA_bins ,"h_secTrk_DOCA_TRUE_RECO_Material; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_secTrk_DOCA_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_secTrk_DOCA_TRUE_Interaction", Vertex_secondTrkDOCA_bins ,"h_secTrk_DOCA_TRUE_RECO_Interaction; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_DOCA_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_DOCA_TRUE_Particle", Vertex_secondTrkDOCA_bins ,"h_secTrk_DOCA_TRUE_RECO_Particle; [mm];Events");



PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_Particle_N_A_secTrk_Theta_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_Particle_N_A_secTrk_Theta_TRUE_Interaction", Vertex_secondTrkTheta_bins ,"h_Particle_N_A_secTrk_Theta_TRUE_Interaction; [Degs];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_Particle_OTHER_secTrk_Theta_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_Particle_OTHER_secTrk_Theta_TRUE_Interaction", Vertex_secondTrkTheta_bins ,"h_Particle_OTHER_secTrk_Theta_TRUE_Interaction; [Degs];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_Electron_secTrk_Theta_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_Electron_secTrk_Theta_TRUE_Interaction", Vertex_secondTrkTheta_bins ,"h_Electron_secTrk_Theta_TRUE_Interaction; [Degs];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_Muon_secTrk_Theta_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_Muon_secTrk_Theta_TRUE_Interaction", Vertex_secondTrkTheta_bins ,"h_Muon_secTrk_Theta_TRUE_Interaction; [Degs];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_Gamma_secTrk_Theta_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_Gamma_secTrk_Theta_TRUE_Interaction", Vertex_secondTrkTheta_bins ,"h_Gamma_secTrk_Theta_TRUE_Interaction; [Degs];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_Nu_mu_secTrk_Theta_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_Nu_mu_secTrk_Theta_TRUE_Interaction", Vertex_secondTrkTheta_bins ,"h_Nu_mu_secTrk_Theta_TRUE_Interaction; [Degs];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_Nu_e_secTrk_Theta_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_Nu_e_secTrk_Theta_TRUE_Interaction", Vertex_secondTrkTheta_bins ,"h_Nu_e_secTrk_Theta_TRUE_Interaction; [Degs];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_Anti_nu_secTrk_Theta_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_Anti_Nu_secTrk_Theta_TRUE_Interaction", Vertex_secondTrkTheta_bins ,"h_Anti_Nu_secTrk_Theta_TRUE_Interaction; [Degs];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_Kaon_secTrk_Theta_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_Kaon_secTrk_Theta_TRUE_Interaction", Vertex_secondTrkTheta_bins ,"h_Kaon_secTrk_Theta_TRUE_Interaction; [Degs];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_Pion0_secTrk_Theta_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_Pion0_secTrk_Theta_TRUE_Interaction", Vertex_secondTrkTheta_bins ,"h_Pion0_secTrk_Theta_TRUE_Interaction; [Degs];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_Pion_neg_secTrk_Theta_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_Pion_neg_secTrk_Theta_TRUE_Interaction", Vertex_secondTrkTheta_bins ,"h_Pion_neg_secTrk_Theta_TRUE_Interaction; [Degs];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_Pion_pos_secTrk_Theta_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_Pion_pos_secTrk_Theta_TRUE_Interaction", Vertex_secondTrkTheta_bins ,"h_Pion_pos_secTrk_Theta_TRUE_Interaction; [Degs];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_Proton_secTrk_Theta_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_Proton_secTrk_Theta_TRUE_Interaction", Vertex_secondTrkTheta_bins ,"h_Proton_secTrk_Theta_TRUE_Interaction; [Degs];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_Neutron_secTrk_Theta_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_Neutron_secTrk_Theta_TRUE_Interaction", Vertex_secondTrkTheta_bins ,"h_Neutron_secTrk_Theta_TRUE_Interaction; [Degs];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_4helium_secTrk_Theta_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_4helium_secTrk_Theta_TRUE_Interaction", Vertex_secondTrkTheta_bins ,"h_4helium_secTrk_Theta_TRUE_Interaction; [Degs];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_Lamdba_secTrk_Theta_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_Lamdba_secTrk_Theta_TRUE_Interaction", Vertex_secondTrkTheta_bins ,"h_Lamdba_secTrk_Theta_TRUE_Interaction; [Degs];Events");
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_Sigma_plus_secTrk_Theta_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_Sigma_plus_secTrk_Theta_TRUE_Interaction", Vertex_secondTrkTheta_bins ,"h_Sigma_plus_secTrk_Theta_TRUE_Interaction; [Degs];Events");


PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_lost999_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_lost999_Particle", Vertex_secondTrkTheta_bins ,"h_lost999_Particle; [Degs];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_lost999_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_lost999_Interaction", Vertex_secondTrkTheta_bins ,"h_lost999_Interaction; [Degs];Events");

// testing the neutrino Electron type

MnvH1D *h_mc_current_neturino_electron_TRUE           =    new MnvH1D("h_mc_current_neturino_electron_TRUE", "h_mc_current_neturino_electron_TRUE",6,-1.5,4.5 );
MnvH1D *h_mc_incoming_neturino_electron_TRUE           =    new MnvH1D("h_mc_incoming_neturino_electron_TRUE", "h_mc_incoming_neturino_electron_TRUE",37,-18.5,18.5 );



*/

std::vector<double> Vertex_Zbins_MORE{1500, 1550,1600,1650,1700,1750,1800,1850,1900,1950,2000,
  2050,2100,2150,2200,2250,2300,2350,2400,2450,2500,2550,2600,2650,2700,2750,2800,2850,2900,2950,
  3000,3050,3100,3150,3200,3250,3300,3350,3400,3450,3500,3550,3600,3650,3700,3750,3800,3850,3900,
  3950,4000,4050,4100,4150,4200,4250,4300};

 //{ 1500.0, 1700.0, 2088.0, 2293.0, 2500.0, 2700.00, 2900.00, 3100.00, 3300.00, 3482, 3687.0 ,3800.0,4500.0}


std::vector<double> Vertex_Rbins_vectorMOREbins_vec = {0,50,100,150,200,250,300,350,400,450,500,550,600,650,700,750,800,850,900,950,1000 };

std::vector<double> Vertex_RRbins_vectorMOREbins_vec;
for(auto cat : Vertex_Rbins_vectorMOREbins_vec ) {Vertex_RRbins_vectorMOREbins_vec.push_back(cat * cat);}

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Z_TRUE_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Z_TRUE_Material", Vertex_Zbins_MORE ,"h_CryoVertex_Z_TRUE_Material; vertex Z [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_Y_TRUE_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_Y_TRUE_Material", Vertex_Ybins ,"h_CryoVertex_Y_TRUE_Material; vertex Y [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_X_TRUE_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_X_TRUE_Material", Vertex_Xbins ,"h_CryoVertex_X_TRUE_Material; vertex X [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_R_TRUE_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_R_TRUE_Material", Vertex_Rbins_vectorMOREbins_vec ,"h_CryoVertex_R_TRUE_Material; vertex R [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_CryoVertex_RR_TRUE_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_CryoVertex_RR_TRUE_Material", Vertex_RRbins_vectorMOREbins_vec ,"h_CryoVertex_RR_TRUE_Material; vertex R^2 [mm];Events");




PlotUtils::HistWrapper<HeliumCVUniverse_LENX_validation> h_MuonPZ_TRUE("h_MuonPZ_TRUE", "Muon_{PZ}",  Pzbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse_LENX_validation> h_MuonPT_TRUE("h_MuonPT_TRUE", "Muon_{PT}",  PTbin_vector , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse_LENX_validation> h_MuonTheta_TRUE("h_MuonTheta_TRUE", "MuonTheta [Deg]",  MuonThetabin_vector , error_bands);


///////////
///Vetowall
///////////
/////////////////////////////////////////

  //=========================================
  // Entry Loop For MC
  //=========================================

  //std::vector<ECuts> kTRUTHCutsVector;


  bool is_counter = true;

  //EventCount_Truth EventCounter_EFF;
  //EventCount_RECO EventCounter_EFF_TRUTH;
  EventCount_Truth EventCounter_TRUTH_total;

  EventCount_Truth EventCounter_weight_0;
  EventCount_Truth EventCounter_weight_1;
  EventCount_Truth EventCounter_weight_2;
  EventCount_Truth EventCounter_weight_3;
  EventCount_Truth EventCounter_weight_4;

  std::vector<Vertex_XYZ> CryoTank_vector;
  std::vector<Vertex_XYZ> CryoTank_vector_He;
  std::vector<Vertex_XYZ> CryoTank_vector_Al;



  for(auto cat : kTRUTHCutsVector_Energy){EventCounter_TRUTH_total[cat]=0;}
  for(auto cat : kTRUTHCutsVector){
    EventCounter_weight_0[cat]=0;

    }




  int counter_test=20;
  int kk=0;
  int non_leading_removed=0;
  int non_leading=0;



  double wgt0,wgt1,wgt2,wgt3,wgt4,wgt_total;

  ProcInfo_t procInfo;
  gSystem->GetProcInfo(&procInfo);

  std::cout << "Memory/time used so Far: " << procInfo.fMemResident/1000<< " MB" <<" time = "<<  procInfo.fCpuSys <<  " Sec"<<"\n";

  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"MC TRUTH LOOP  "<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
//////////////////
TDatabasePDG *pdg_DATABASEobject = TDatabasePDG::Instance();
int otherMaterial;
  std::string sysmatics_status;
  if(m_RunCodeWithSystematics==true){sysmatics_status= "Systematics On";}
  else if (m_RunCodeWithSystematics==false){sysmatics_status= "Systematics Off";}
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;
  std::cout<<"~~~~~~~~~  "<< sysmatics_status <<" ~~~~~~~~~ "<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;


  for(int ii=0; ii<chw_MC->GetEntries(); ++ii){
    if(ii%100000==0) std::cout << (ii/1000) << " k " << std::endl;

    //=========================================
    // For every systematic, loop over the universes, and fill the
    // appropriate histogram in the MnvH1D
    //=========================================


    for (auto band : error_bands){

      std::vector<HeliumCVUniverse_LENX_validation*> error_band_universes = band.second;
      for (auto universe : error_band_universes){

        // Tell the Event which entry in the TChain it's looking at
        universe->SetEntry(ii);

        /*
        auto cc = universe->GetCC_LENXVal();
        auto Z = universe->Get_atomic_Z_LENXVal();
        auto LeptonE = universe->GetP_E_lepton_LENXVal();
        auto Lepton_angle_wrtb = universe->GetAnglewrtb_Degs_lepton_LENXVal();
        auto Nu_type = universe->Get_imcomingNUtype_LENXVal() ;
        auto Vertex_Z = universe->GetVertex_Z_LENXVal();//  mm
        */

        auto cc = universe->GetCC_MC();
        auto Z = universe->Get_atomic_Z_MC();
        auto LeptonE = universe->GetP_E_lepton_MC();
        auto Lepton_angle_wrtb = universe->GetAnglewrtb_Degs_lepton_MC();
        auto Nu_type = universe->Get_imcomingNUtype_MC() ;
        auto Vertex_Z = universe->GetVertex_Z_MC();//  mm
        //4293.04 first plane of Minerva

//std::cout << "Vertex Z = "<< universe->GetVertex_Z_MC()<<std::endl;

// apply cuts
 if(cc == 1 && LeptonE > 2.0 && LeptonE < 50.0 &&  Lepton_angle_wrtb < 17 && Nu_type== 14 && Vertex_Z < 4293.04 && Vertex_Z > 1500.0){
// is CC interaction
// 2 GeV < muon E< 50
// Muon_angle < 17
// incoming Muon neutrino

//std::cout << "Pt = "<< universe->GetPmuTransverse_MC()<<std::endl;
//std::cout << "PmuLongitudinal = "<< universe->GetPmuLongitudinal_MC()<<std::endl;

   //double wgt = universe->GetWeight_LENXVal();
   double wgt = universe->GetWeight_MC();
   auto Material_type_Event = calculate_Target_materialtype(Z);
        ///////////////////////////////////////////
        ////
        ////  FILL CV
        ////
        ///
        ///////////////////////////////////////////

        if( universe->ShortName() == "cv"){

          //          Vertex_XYZ XYZinput{universe->GetVertex_X_LENXVal(),universe->GetVertex_Y_LENXVal(),universe->GetVertex_Z_LENXVal()};
          Vertex_XYZ XYZinput{universe->GetVertex_X_MC(),universe->GetVertex_Y_MC(),universe->GetVertex_Z_MC()};

          CryoTank_vector.push_back(XYZinput);
          if(Material_type_Event==kHelium){CryoTank_vector_He.push_back(XYZinput);}
          else if(Material_type_Event==kAluminium){CryoTank_vector_Al.push_back(XYZinput);}
          else{otherMaterial++;}
          CryoTank_vector.push_back(XYZinput);


/*
          h_CryoVertex_Z_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetVertex_Z_LENXVal(),wgt);
          h_CryoVertex_Y_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetVertex_Y_LENXVal(),wgt);
          h_CryoVertex_X_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetVertex_X_LENXVal(),wgt);
          h_CryoVertex_R_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetVertex_R_LENXVal(),wgt);
          h_CryoVertex_RR_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetVertex_RR_LENXVal(),wgt);
*/
//std::cout<<"Material_type_Event = "<< Material_type_Event<<std::endl;
h_CryoVertex_Z_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetVertex_Z_MC(),wgt);
//std::cout<<"Material_type_Event = "<< Material_type_Event<<std::endl;
h_CryoVertex_Y_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetVertex_Y_MC(),wgt);
//std::cout<<"Material_type_Event = "<< Material_type_Event<<std::endl;
h_CryoVertex_X_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetVertex_X_MC(),wgt);
//std::cout<<"Material_type_Event = "<< Material_type_Event<<std::endl;
h_CryoVertex_R_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetVertex_R_MC(),wgt);
//std::cout<<"Material_type_Event = "<< Material_type_Event<<std::endl;
h_CryoVertex_RR_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetVertex_RR_MC(),wgt);



          //////////////////////////////////////////////////////////
          //// CUTS HAVE BEEN APPLIED
          ///////////////////////////////////////////////////////////
          if(Z==2){
            //h_MuonPT_TRUE.univHist(universe)->Fill(universe->GetPmuTransverse_LENXVal(),wgt);
            //h_MuonPZ_TRUE.univHist(universe)->Fill(universe->GetPmuLongitudinal_LENXVal(),wgt);
            //h_MuonTheta_TRUE.univHist(universe)->Fill(universe->GetAnglewrtb_Degs_lepton_LENXVal(),wgt);

            h_MuonPT_TRUE.univHist(universe)->Fill(universe->GetPmuTransverse_MC(),wgt);
            h_MuonPZ_TRUE.univHist(universe)->Fill(universe->GetPmuLongitudinal_MC(),wgt);
            h_MuonTheta_TRUE.univHist(universe)->Fill(universe->GetAnglewrtb_Degs_lepton_MC(),wgt);


          }

        }


        ///////////////////////////////////////////
        ////
        ////  END OF CV
        ////
        ////
        ///////////////////////////////////////////



        //std::cout<< "GetMuonAngleWRTB() > 12.0" << universe->GetMuonAngleWRTB() <<std::endl;
        //=========================================
        // CUTS in each universe
        //=========================================




        //  }//END OF TRUTH PASS CUTS
      }// end of if()for cuts
    } // End band's universe loop
  } // End Band loop
} //End entries loop

h_MuonPZ_TRUE.SyncCVHistos();
h_MuonPT_TRUE.SyncCVHistos();
h_MuonTheta_TRUE.SyncCVHistos();



gSystem->GetProcInfo(&procInfo);
std::cout << " Done with loop Mem1: " << procInfo.fMemResident/1000 << " MB" << " time = "<<  procInfo.fCpuSys  <<  " sec""\n";
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
//EventCountMap[kPlayListVector[0]] = EventCounter_MCFull;
//EventCountMap[kPlayListVector[2]] = EventCounter_dataFull;
//EventCountMap[kPlayListVector[3]] = EventCounter_dataEmpty;



//////////////////////////////////////////////////////////////////////////
//End of Empty data
//////////////////////////////////////////////////////////////////////////


double countdata= 0.0;
double countmc= 0.0;


//    h_CryoVertex_X_TRUE.SyncCVHistos();
  //  h_CryoVertex_Y_TRUE.SyncCVHistos();
  //  h_CryoVertex_R_TRUE.SyncCVHistos();
    //h_CryoVertex_Z_TRUE.SyncCVHistos();


    //////////////////////////////////
    //////////////////////////////////
    //MuonEnergymaterial.Write();
    //outFile.cd();
    //outFile.Write();
    //LOGFILE.Close();
  //=========================================
  // Plot stuff
  //=========================================

  // DrawMCWithErrorBand
//  PlotCVAndError(Muon_PZ_FULLMC.hist, "TEST");



  char outFileName[1024];
  //auto playlist_name = Playlist_Info.GetPlaylistname();
  std::string datatype = "TRUTH";
  //char c[playlist_name.length() + 1];
  char d[datatype.length() + 1];
  char * c = "Minerva13C_Eroica";
  char rootpathway[OUTputRoot_pathway.length()+1];
  strcpy(rootpathway, OUTputRoot_pathway.c_str());
  //strcpy(c, playlist_name.c_str());
  strcpy(d, datatype.c_str());
  //PrintCutstoScreen( kTRUTHCutsVector , EventCounter_RECO, c, mcscale );
  char EventRateName[1024];
  //sprintf(EventRateName, "TRUE_Weight_ALL_Weights_TRUEMC_%s",c);
  //MakeEfficiencyCutCVS(EventCounter_EFF_TRUTH, EventCounter_EFF , kTRUTHCutsVector,c,mcPOT);
//  Make_cvsOfCutsRateTRUE(kTRUTHCutsVector , EventCounter_TRUTH_total, EventRateName, 1.0, 1.0);
//sprintf(EventRateName, "TRUE_Weight_0_noWeight_TRUEMC_%s",c);
//Make_cvsOfCutsRateTRUE( kTRUTHCutsVector , EventCounter_weight_0, EventRateName  ,1.0 ,1.0 );

  //outFileName = "Histograms_test.root";
  //auto outFile = TFile::Open(outFileName);

  std::string systematics_status;
  if(m_RunCodeWithSystematics==true){
    sysmatics_status= "All_SysErrorsOn";
    std::cout<<"print to: "<< sysmatics_status <<std::endl ;
    }
  else if (m_RunCodeWithSystematics==false){
    sysmatics_status= "StatsONLY";}

    std::cout<<"print to: "<< sysmatics_status <<std::endl ;
    char sysmatics_status_char[sysmatics_status.length()+1];
    strcpy(sysmatics_status_char, sysmatics_status.c_str());


  sprintf(outFileName, "%s/Histograms_NX_LE_Validation_%s_%s_%s.root",rootpathway,c,d,sysmatics_status_char);

  std::cout << "Writing output file to: " <<outFileName << std::endl;

  TFile *outFile = new TFile(outFileName,"RECREATE");

  //TFile *outFile(outFileName, "RECREATE");
  //TFile *outFile = new TFile(outFileName,"RECREATE");
  //TChain POT_branch("Meta");
  //POT_branch.Add(RootName.c_str());
  //TTree *oldtree = (TTree*)file->Get("Meta");
  //TTree *clone = POT_branch.CloneTree();
  //clone->Write();


  h_CryoVertex_Z_TRUE_Material.WriteToFile(*outFile);
  h_CryoVertex_Y_TRUE_Material.WriteToFile(*outFile);
  h_CryoVertex_X_TRUE_Material.WriteToFile(*outFile);
  h_CryoVertex_R_TRUE_Material.WriteToFile(*outFile);
  h_CryoVertex_RR_TRUE_Material.WriteToFile(*outFile);

  h_MuonPZ_TRUE.hist->Write();
  h_MuonPT_TRUE.hist->Write();
  h_MuonTheta_TRUE.hist->Write();



  outFile->Close();
  TCanvas *can = new TCanvas("", "");
    TFile *TFILE_PLAYLIST;
    TFILE_PLAYLIST = new TFile(outFileName);
  //TCanvas *can = new TCanvas("can", "can",1800,1600);
  MnvPlotter *mnv_plotter = new MnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
std::cout<< " the Number of Material that isn;t helium or AL in the cryotank region = "<< otherMaterial<<std::endl;

char pdf_name[1024];
char pdf_start[1024];
char pdf_mid[1024];
char pdf_end[1024];
sprintf(pdf_name, "NXLE_PLOTS_%s_%s",c,d);
std::string pdfstring(pdf_name);
sprintf(pdf_start,"%s.pdf(",pdf_name);
sprintf(pdf_mid,  "%s.pdf",pdf_name);
sprintf(pdf_end,  "%s.pdf)",pdf_name);

can -> Print(pdf_start);

std::vector<int> PieColors = {
    TColor::GetColor("#EEFF00"), // neonyellow,
    TColor::GetColor("#DF00FF"), //'psychedelic Purple
    TColor::GetColor("#ffc922"), //'sunset yellow'
    TColor::GetColor("#87CEEB"),//'skyblue'
    TColor::GetColor("#0859C6"), //blue
    TColor::GetColor("#654522"), // yellowishbrown,
    TColor::GetColor(  43, 206,  72 ), //green
    TColor::GetColor("#FF0800"),//2 candy Apple
    TColor::GetColor("#90AD1C"),
    TColor::GetColor("#BABABA"), //Gray
    TColor::GetColor("#00FFFF"),//'aqua'
    TColor::GetColor("#F1B6DA"),//pink
    TColor::GetColor("#00A86B"),//'Jade'
    TColor::GetColor("#FAFAD2"),  // LightGoldenRodYellow
    TColor::GetColor("#800000"),  // Maroon
    TColor::GetColor("#555555"),  // dark grey
    TColor::GetColor(0, 153, 143 ), //turquoise
    TColor::GetColor("#654522"), // yellowishbrown,
    TColor::GetColor("#8db600"), // yellowgreen,
    TColor::GetColor("#D3D3D3"),  //'lightgrey'
     TColor::GetColor("#90AD1C"),
     TColor::GetColor("#CCDDAA")
  };

//std::vector<Material_type> material_vector{kMaterial_OTHER, kIron,  kCarbon, kLead, kAluminium,   kHelium };
/*
h_CryoVertex_Z_TRUE_Material.ApplyColorPalette(PieColors);
h_CryoVertex_Y_TRUE_Material.ApplyColorPalette(PieColors);
h_CryoVertex_X_TRUE_Material.ApplyColorPalette(PieColors);
h_CryoVertex_R_TRUE_Material.ApplyColorPalette(PieColors);
h_CryoVertex_RR_TRUE_Material.ApplyColorPalette(PieColors);

for(auto cat :material_vector ){
  h_CryoVertex_Z_TRUE_Material.GetComponentHist(cat)->SetLineColor(0);
  h_CryoVertex_Y_TRUE_Material.GetComponentHist(cat)->SetLineColor(0);
  h_CryoVertex_X_TRUE_Material.GetComponentHist(cat)->SetLineColor(0);
  h_CryoVertex_R_TRUE_Material.GetComponentHist(cat)->SetLineColor(0);
  h_CryoVertex_RR_TRUE_Material.GetComponentHist(cat)->SetLineColor(0);
}
*/

DrawVertex_Cryotank_X_Y_R_Vs_Z(CryoTank_vector, "Minerva13B", "[TRUTH] NX LE " ,pdf_name, can, mnv_plotter);
DrawVertex_Cryotank_X_Y_R_Vs_Z(CryoTank_vector_He ,CryoTank_vector_Al, "Minerva13B", "[TRUTH] NX LE ", pdf_name , can, mnv_plotter);
DrawSINGLESTACKMCHistFilio_FromTFile(TFILE_PLAYLIST,  "h_CryoVertex_Z_TRUE_Material" , "Truth Vertex Z stack [Minerva13B]", "vertex Z [mm]", pdfstring, false, true );
DrawSINGLESTACKMCHistFilio_FromTFile(TFILE_PLAYLIST,  "h_CryoVertex_X_TRUE_Material" , "Truth Vertex X stack [Minerva13B]", "vertex X [mm]", pdfstring, false, true );
DrawSINGLESTACKMCHistFilio_FromTFile(TFILE_PLAYLIST,  "h_CryoVertex_Y_TRUE_Material" , "Truth Vertex Y stack [Minerva13B]", "vertex Y [mm]", pdfstring, false, true );
DrawSINGLESTACKMCHistFilio_FromTFile(TFILE_PLAYLIST,  "h_CryoVertex_R_TRUE_Material" , "Truth Vertex R stack [Minerva13B]", "vertex R [mm]", pdfstring, false, true );
DrawSINGLESTACKMCHistFilio_FromTFile(TFILE_PLAYLIST,  "h_CryoVertex_RR_TRUE_Material" , "Truth Vertex R^2 stack [Minerva13B]", "vertex R^2 [mm]", pdfstring, false, true );
Draw_MCHist_withErrorSys_fromTFile(TFILE_PLAYLIST,  "h_MuonPZ_TRUE", pdfstring, "Muon P_{L} [Z=2][Minerva13B]","P_{L} [GeV]","Nevents ",  false);
Draw_MCHist_withErrorSys_fromTFile(TFILE_PLAYLIST,  "h_MuonPZ_TRUE", pdfstring, "Muon P_{L} [Z=2][Minerva13B]","P_{L} [GeV]","Nevents / Bin ",  true);
Draw_MCHist_withErrorSys_fromTFile(TFILE_PLAYLIST,  "h_MuonPT_TRUE", pdfstring, "Muon P_{T} [Z=2][Minerva13B]","P_{T} [GeV]","Nevents ",  false);
Draw_MCHist_withErrorSys_fromTFile(TFILE_PLAYLIST,  "h_MuonPT_TRUE", pdfstring, "Muon P_{T} [Z=2][Minerva13B]","P_{T} [GeV]","Nevents / Bin ",  true);
Draw_MCHist_withErrorSys_fromTFile(TFILE_PLAYLIST,  "h_MuonTheta_TRUE", pdfstring, "Muon #theta [Z=2][Minerva13B]","#theta_{#mu} [DeG]","Nevents ",  false);
Draw_MCHist_withErrorSys_fromTFile(TFILE_PLAYLIST,  "h_MuonTheta_TRUE", pdfstring, "Muon #theta [Z=2][Minerva13B]","#theta_{#mu} [DeG]","Nevents / Bin ",  true);
can -> Print(pdf_end);

  for(auto band : error_bands){
    std::vector<HeliumCVUniverse_LENX_validation*> band_universes = band.second;
    for(unsigned int i_universe = 0; i_universe < band_universes.size(); ++i_universe){ delete band_universes[i_universe];}
  }

  std::cout << "Success in TRUTH LOOP - Gotcha !?!?" << std::endl;



TCanvas *can1 = new TCanvas("can", "can",1800,1600);
can1 -> Print("Test.pdf");


}//END of Event Loop

//=========================================
//=========================================
//////////////////////////////////////////////////////////////
std::vector<ECutsTRUTH> GetTRUTHCutsVector() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ECutsTRUTH> True_vec;
  True_vec.push_back(kTRUTHNoCuts   );
  True_vec.push_back(kTRUTHneutrino);
  True_vec.push_back(kTRUTHCCInteraction );
  True_vec.push_back(kTRUTHtarget);
  True_vec.push_back(kTRUTHMuonEnergy );
  True_vec.push_back(kTRUTHMuonAngle );
  True_vec.push_back(kTRUTHFiduical );
  True_vec.push_back(kTRUTH_greaterthanoneFS);
  //True_vec.push_back(kTRUTH_secTrk_Angle_threshold);
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);
  True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold_withProtonanPionThresholds);
  True_vec.push_back(kAllTRUTHCuts);

  return True_vec;
//#endif
}

std::vector<ECutsTRUTH> GetTRUTHCutsVector_Energy() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ECutsTRUTH> True_vec;
  True_vec.push_back(kTRUTHNoCuts   );
  True_vec.push_back(kTRUTHneutrino);
  True_vec.push_back(kTRUTHCCInteraction );
  True_vec.push_back(kTRUTHtarget);
  True_vec.push_back(kTRUTHMuonEnergy );
  True_vec.push_back(kTRUTHMuonAngle );
  True_vec.push_back(kTRUTHFiduical );
  True_vec.push_back(kTRUTH_greaterthanoneFS);
  //True_vec.push_back(kTRUTH_secTrk_Angle_threshold);
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);
  True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold_withProtonanPionThresholds);

  //True_vec.push_back(kTRUTH_2ndTrkProtonEnergythreshold);
  //True_vec.push_back(kTRUTH_2ndTrkPionEnergythreshold);
  True_vec.push_back(kAllTRUTHCuts);


  //int n = sizeof(kCutsArray) / sizeof(kCutsArray[0]);
  //static std::vector<ECuts> ret_vec(kCutsArray, kCutsArray + n);
  return True_vec;
//#endif
}


std::vector<ECutsTRUTH> GetTRUTHCutsVector_Smearing() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ECutsTRUTH> True_vec;
  True_vec.push_back(kTRUTHNoCuts   );
  True_vec.push_back(kTRUTHneutrino);
  True_vec.push_back(kTRUTHCCInteraction );
  //True_vec.push_back(kTRUTHtarget); removed target
  True_vec.push_back(kTRUTHMuonEnergy );
  True_vec.push_back(kTRUTHMuonAngle );
  True_vec.push_back(kTRUTHFiduical_ExtraShell);
  True_vec.push_back(kTRUTH_greaterthanoneFS);
  //True_vec.push_back(kTRUTH_secTrk_Angle_threshold);
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);
  True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold_withProtonanPionThresholds);
  True_vec.push_back(kAllTRUTHCuts);

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

  Playlist.push_back(kME1F);
  //Playlist.push_back(kME1P);
  //Playlist.push_back(kME1D);
  ///Playlist.push_back(kME1C);
  //Playlist.push_back(kME1A);//
  //Playlist.push_back(kME1G);//
  //Playlist.push_back(kME1E);//

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
  //weight_vec.push_back(kweightMinos ); Don't apply Minos efficiency weight to truth
  weight_vec.push_back(kweightGenie);
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
int main(){
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


  runEventLoop();
  return 0;
}
//#endif
