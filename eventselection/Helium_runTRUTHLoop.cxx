// Loop entries, make cuts, fill histograms.
// * Uses the New Systematics Framework and "Universe" objects.
// * loop universes, make cuts and fill histograms with the correct lateral
// shifts and weights for each universe.
// * TChain --> PlotUtils::ChainWrapper.
// * MnvHXD --> PlotUtils::HistWrapper.
// * Genie, flux, non-resonant pion, and some detector systematics calculated.
#include "Helium_runTRUTHLoop.h"
#include <chrono>
std::string OUTputRoot_pathway = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles";


//=====================================================
// Functions
//=====================================================
std::vector<ECuts> GetRECOCutsVector();
std::vector<ECutsTRUTH> GetTRUTHCutsVector();
std::vector<ECutsTRUTH> GetTRUTHCutsVector_Energy();
std::vector<Weights> GetWeightVector();
std::vector<Particle_type>  GetParicle_type();

// Get container of systematics

const bool m_RunCodeWithSystematics = true;


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
  PlotUtils::NamedCategory<Particle_type>({kParticle_N_A},      "N_A"),
  PlotUtils::NamedCategory<Particle_type>({kParticle_OTHER},    "Other"),
  PlotUtils::NamedCategory<Particle_type>({kElectron},          "Electron"),
  PlotUtils::NamedCategory<Particle_type>({kMuon},              "Muon"),
  PlotUtils::NamedCategory<Particle_type>({kGamma},             "Gamma"),
  PlotUtils::NamedCategory<Particle_type>({kNeutrino_muon},     "Neutrino_muon"),
  PlotUtils::NamedCategory<Particle_type>({kNeutrino_electron}, "Neutrino_electron"),
  PlotUtils::NamedCategory<Particle_type>({kAnti_Neutrino},     "Anti_Neutrino"),
  PlotUtils::NamedCategory<Particle_type>({kKaon},              "Kaon"),
  PlotUtils::NamedCategory<Particle_type>({kPion_0},            "Pi0"),
  PlotUtils::NamedCategory<Particle_type>({kPion_neg},          "Pi^{-}"),
  PlotUtils::NamedCategory<Particle_type>({kPion_pos},          "Pi^{+}"),
  PlotUtils::NamedCategory<Particle_type>({kProton},            "Proton"),
  PlotUtils::NamedCategory<Particle_type>({kNeutron},           "Neutron"),
  PlotUtils::NamedCategory<Particle_type>({kFourHelium},       "{}^{4}He"),
  PlotUtils::NamedCategory<Particle_type>({kLamdba},           "Lamdba"),
  PlotUtils::NamedCategory<Particle_type>({kSigma_plus},       "Sigma^{+}")
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

/*
const auto TracksGreaterThan2 = {  NamedCategory<int>({3},   "ThirdTrack"),
NamedCategory<int>({4},   "FourthTrack"),
NamedCategory<int>({5},   "FifthTrack"),
NamedCategory<int>({6},   "SixthTrack"),
NamedCategory<int>({7},   "SevethTrack"),
NamedCategory<int>({8},   "EighthTrack")

};*/

///////////////////////////////////
////// Number of Flux Universe
//////////////////////////////////

const int n_flux_universes = 100;

///////////////////////////////////
///
//////////////////////////////////


std::map< std::string, std::vector<HeliumCVUniverse*> >
  GetErrorBands(PlotUtils::ChainWrapper* chain) {
    typedef std::map< std::string, std::vector<HeliumCVUniverse*> > SystMap;
    //const int n_flux_universes = 50;
    SystMap error_bands;

    //========================================================================
    // CV
    //========================================================================

    error_bands[std::string("cv")].push_back( new HeliumCVUniverse(chain) );

    if(m_RunCodeWithSystematics==true)
    {
      //========================================================================
      // FLUX
      //========================================================================

      SystMap flux_systematics = PlotUtils::GetFluxSystematicsMap<HeliumCVUniverse>(chain,n_flux_universes);
      error_bands.insert(flux_systematics.begin(), flux_systematics.end());

      //========================================================================
      // GENIE Standards
      //========================================================================

      SystMap genie_systematics = PlotUtils::GetGenieSystematicsMap<HeliumCVUniverse>(chain);
      error_bands.insert(genie_systematics.begin(), genie_systematics.end());

      //========================================================================
      //  MnvTuned - 2p2h
      //========================================================================

      SystMap a2p2h_systematics = PlotUtils::Get2p2hSystematicsMap<HeliumCVUniverse>(chain);
      error_bands.insert(a2p2h_systematics.begin(), a2p2h_systematics.end());

      //========================================================================
      // (RPA)random phase appox , long range Nuclear correlations modeling
      //========================================================================

      SystMap RPA_systematics = PlotUtils::GetRPASystematicsMap<HeliumCVUniverse>(chain);
      error_bands.insert(RPA_systematics.begin(), RPA_systematics.end());

      //========================================================================
      // Helium Mass
      //========================================================================

      SystMap HeliumTargetMass_systematics = GetHeliumTargetMassSystematicsMap<HeliumCVUniverse>(chain);
      error_bands.insert(HeliumTargetMass_systematics.begin(), HeliumTargetMass_systematics.end());

    }


        //SystMap LowQ2Pi_systematics = PlotUtils::GetLowQ2PiSystematicsMap<HeliumCVUniverse>(chain);
        //error_bands.insert(LowQ2Pi_systematics.begin(), LowQ2Pi_systematics.end());



  // Non-res pi
  //SystMap nonrespi_systematics =
  //  PlotUtils::GetNonResPiSystematicsMap<HeliumCVUniverse>(chain);
  //error_bands.insert(nonrespi_systematics.begin(), nonrespi_systematics.end());


  return error_bands;
}
//======================================================================
// Main
//======================================================================

void runEventLoop(ME_helium_Playlists &PlayList_iterator , bool &Run_EventLoopOnGrid) {
  // Make a chain of events
  loadLibs();

  const std::vector<ECutsTRUTH> kTRUTHCutsVector = GetTRUTHCutsVector();
  const std::vector<ECutsTRUTH> kTRUTHCutsVector_Energy = GetTRUTHCutsVector_Energy();

  const std::vector<Weights> kWeightVector = GetWeightVector();
  const std::vector<Particle_type> kSecondary_particle_vector = GetParicle_type();

  std::ofstream output("LogFile_TRUTH.txt",std::ofstream::app);

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

std::vector <ALL_True_Event_info> ALL_EventInfoNu_e_secTrkParticle;
std::vector <ALL_True_Event_info> ALL_EventInfoNu_mu_secTrkParticle;


  MinervaUniverse::SetTruth(true);
  MinervaUniverse::SetNuEConstraint(true);
  MinervaUniverse::SetAnalysisNuPDG(14);
  MinervaUniverse::SetNFluxUniverses(n_flux_universes);
  MinervaUniverse::SetZExpansionFaReweight(false);
  MinervaUniverse::SetNonResPiReweight(true);
  MinervaUniverse::SetDeuteriumGeniePiTune(false);
  std::string playlist = GetPlaylist(PlayList_iterator);
  MinervaUniverse::SetPlaylist(playlist);


 std::string seestring = MinervaUniverse::GetPlaylist();
 HeliumPlayListInfo Playlist_Info(playlist);
 std::cout<<"Working with Playlist =  "<<   seestring <<std::endl;


  auto Playlist_txtFILEPath = GetPlaylist_txtFILE_path(PlayList_iterator, is_mc );
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
std::map< std::string, std::vector<HeliumCVUniverse*> > error_bands= GetErrorBands(chw_MC);
for(auto band :error_bands ){std::cout<<"Checking Universe this is universe with name : " << band.first<<std::endl;}
std::vector<std::vector<HeliumCVUniverse*>> Error_Band_Universe_GROUPS = groupCompatibleUniverses(error_bands);

std::cout<< "error_bands.size() = " << error_bands.size()<<std::endl;
std::cout<< "Error_Band_GROUPS.size() = " << Error_Band_Universe_GROUPS.size()<<std::endl;
std::cout<<"Number of Universes set is = "<< 	MinervaUniverse::GetNFluxUniverses()<<std::endl;
//std::string NumU = MinervaUniverse::GetNFluxUniverses()<<std::endl;

//const std::string RootName = GetPlaylist_ROOT_path("1G_Bugfix",  is_mc );
const std::string RootName = GetPlaylist_ROOT_path(PlayList_iterator,true);
std::cout<<"The Playlist that is set is = "<< seestring <<std::endl;
std::cout<<"The Playlist Root = "<< RootName<<std::endl;
 ///pnfs/minerva/persistent/users/cnguyen/ME_G1_Merg/*.root

 time_t now = time(0);
 tm *ltm = localtime(&now);
 int m_datemonth = 1 + ltm->tm_mon;
 int m_datehour= ltm->tm_hour;
 int m_datemin=ltm->tm_min;
 int m_dateday=ltm->tm_mday;

 output<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
 output<<"~~~~~~~~Helium Anaylsis Log File ~~~~~~~~~~~~~~~" << endl;
 output<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
 output<<"~~~~~~~~~~~~Created By ~~~~~~~~~~~~~~" << endl;
 output<<"~~~~~~~~~~~Christian Nguyen ~~~~~~~~~~~" << endl;
 output<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
 output<<"DateRan(min-hour-month-day-year): (" <<m_datemin<<"-"<<m_datehour<< "-"<<  m_datemonth<< "- "<<m_dateday << "-2020)"<<endl;
 output<<"EnergyType: LE" << endl;
 output<<"Playlist: " <<  GetPlaylist_Name(PlayList_iterator) << endl;
 output<<"Data TYPE : "<<  String_Reco_orTruth(false) << endl;
 output<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
 int count=1;


 output<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
 output<<"~~~~~Truth CUTS Applied for Efficiency Study ~~~~" << endl;
 output<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

  count=1;
  for(auto true_cut_name:kTRUTHCutsVector ){
    output<< count<<" TRUTHCUT name: "<<GetCutNameTRUTH(true_cut_name) <<endl;
    count++;
  }
  output<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  output<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  output<<"~~~~~WEIGHTS~~~~~~~~~~~~~" << endl;
  output<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  output<<"Weights Applied on Event by event"<< endl;
  for(auto Weight_name:kWeightVector )
  {
    output<<"  Weights type: " <<GetWeight_name(Weight_name) <<endl;
  }

  output<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  output<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;


  //========================================================================
  //  GET Binning
  //========================================================================

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
std::vector<double> Vertex_secondTrkEbins= GetSecondTrkVarVector(ksecE); //GetSecondTrkVarVector(ksecE);,ksecE_Proton
std::vector<double> Vertex_secondTrkEbin_Proton_vector= GetSecondTrkVarVector(ksecE_Proton);
//std::sort(Vertex_secondTrkEbin_Proton_vector.begin(),Vertex_secondTrkEbin_Proton_vector.end());
std::vector<double> Vertex_secondTrkTheta_bins= GetSecondTrkVarVector(kThetamid);//GetSecondTrkVarVector(kFullAngle);
std::vector<double> Vertex_secondTrkDOCA_bins= GetSecondTrkVarVector(kDOCA);
std::vector<double> Vertex_secondTrkPathway_bins= GetSecondTrkVarVector(kPathway);

std::vector<double> Recoil_track_length_vector;
double recoil_bin_count=0.0;
for(int ww = 0; ww < 50; ww++ ){
Recoil_track_length_vector.push_back(recoil_bin_count);
recoil_bin_count = recoil_bin_count + 2.54; // bins in [cm]
}
////////////////
//muon Varibles///
////////////////

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


/*
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_TracksizeALL_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_TracksizeALL_TRUE_Particle", TrackSize_vector ,"h_TracksizeALL_TRUE_Particle; [Tracknumber];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_TracksizeALL_leadingTRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_TracksizeALL_leadingTRUE_Particle", TrackSize_vector ,"h_TracksizeALL_leadingTRUE_Particle; [Tracknumber];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_TracksizeALL_nonleadingTRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_TracksizeALL_nonleadingTRUE_Particle", TrackSize_vector ,"h_TracksizeALL_nonleadingTRUE_Particle; [Tracknumber];Events");
*/


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
//Proton
///////////////////////////////////////

MnvH2D *h_2d_Theta_2ndTrkE_Proton_TRUE         =    new MnvH2D("h_2d_Theta_2ndTrkE_Proton_TRUE", "h_2d_Theta_2ndTrkE_Proton_TRUE", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );
MnvH2D *h_2d_muonE_2ndTrkE_Proton_TRUE         =    new MnvH2D("h_2d_muonE_2ndTrkE_Proton_TRUE", "h_2d_muonE_2ndTrkE_Proton_TRUE", Ebin_vector.size()-1, Ebin_vector.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );
MnvH2D *h_2d_muonPT_2ndTrkE_Proton_TRUE         =    new MnvH2D("h_2d_muonPT_2ndTrkE_Proton_TRUE", "h_2d_muonPT_2ndTrkE_Proton_TRUE",  PTbin_vector.size()-1,  PTbin_vector.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );
MnvH2D *h_2d_muonPZ_2ndTrkE_Proton_TRUE         =    new MnvH2D("h_2d_muonPZ_2ndTrkE_Proton_TRUE", "h_2d_muonPZ_2ndTrkE_Proton_TRUE",  Pzbin_vector.size()-1,  Pzbin_vector.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );

///////////////////////////////////////
//Pion
///////////////////////////////////////


MnvH2D *h_2d_Theta_2ndTrkE_Pion_TRUE         =    new MnvH2D("h_2d_Theta_2ndTrkE_Pion_TRUE", "h_2d_Theta_2ndTrkE_Pion_TRUE", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );
MnvH2D *h_2d_muonE_2ndTrkE_Pion_TRUE         =    new MnvH2D("h_2d_muonE_2ndTrkE_Pion_TRUE", "h_2d_muonE_2ndTrkE_Pion_TRUE", Ebin_vector.size()-1, Ebin_vector.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );
MnvH2D *h_2d_muonPT_2ndTrkE_Pion_TRUE         =    new MnvH2D("h_2d_muonPT_2ndTrkE_Pion_TRUE", "h_2d_muonPT_2ndTrkE_Pion_TRUE",  PTbin_vector.size()-1,  PTbin_vector.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );
MnvH2D *h_2d_muonPZ_2ndTrkE_Pion_TRUE         =    new MnvH2D("h_2d_muonPZ_2ndTrkE_Pion_TRUE", "h_2d_muonPZ_2ndTrkE_Pion_TRUE",  Pzbin_vector.size()-1,  Pzbin_vector.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );



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
/////////////////////////////////////
//
/////////////////////////////////////
MnvH2D *h_2d_2ndtrkPathlength_2ndTrkE_TRUE    =    new MnvH2D("h_2d_2ndtrkPathlength_2ndTrkE_TRUE", "h_2d_2ndtrkPathlength_2ndTrkE_TRUE", Vertex_secondTrkPathway_bins.size()-1, Vertex_secondTrkPathway_bins.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );

MnvH2D *h_2d_2ndtrkPathlength_2ndTrkE_Proton_TRUE    =    new MnvH2D("h_2d_2ndtrkPathlength_2ndTrkE_Proton_TRUE", "h_2d_2ndtrkPathlength_2ndTrkE_Proton_TRUE", Vertex_secondTrkPathway_bins.size()-1, Vertex_secondTrkPathway_bins.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );

MnvH2D *h_2d_2ndtrkPathlength_2ndTrkE_Pion_TRUE    =    new MnvH2D("h_2d_2ndtrkPathlength_2ndTrkE_Pion_TRUE", "h_2d_2ndtrkPathlength_2ndTrkE_Pion_TRUE", Vertex_secondTrkPathway_bins.size()-1, Vertex_secondTrkPathway_bins.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );

//MnvH2D *h_2d_2ndtrkPathlength_2ndTrkE_dimuon_TRUE_RECO    =    new MnvH2D("h_2d_2ndtrkPathlength_2ndTrkE_dimuon_TRUE_RECO", "h_2d_2ndtrkPathlength_2ndTrkE_dimuon_TRUE_RECO", Vertex_secondTrkPathway_bins.size()-1, Vertex_secondTrkPathway_bins.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );
//////////////////
////
/////////////////
MnvH2D *h_2d_2ndtrkPathlength_2ndtrkangle_TRUE    =    new MnvH2D("h_2d_2ndtrkPathlength_2ndtrkangle_TRUE", "h_2d_2ndtrkPathlength_2ndtrkangle_TRUE", Vertex_secondTrkPathway_bins.size()-1, Vertex_secondTrkPathway_bins.data(),Vertex_secondTrkTheta_bins.size()-1, Vertex_secondTrkTheta_bins.data()  );

MnvH2D *h_2d_2ndtrkPathlength_2ndtrkangle_Proton_TRUE    =    new MnvH2D("h_2d_2ndtrkPathlength_2ndtrkangle_Proton_TRUE", "h_2d_2ndtrkPathlength_2ndtrkangle_Proton_TRUE", Vertex_secondTrkPathway_bins.size()-1, Vertex_secondTrkPathway_bins.data(),Vertex_secondTrkTheta_bins.size()-1, Vertex_secondTrkTheta_bins.data()  );

MnvH2D *h_2d_2ndtrkPathlength_2ndtrkangle_Pion_TRUE    =    new MnvH2D("h_2d_2ndtrkPathlength_2ndtrkangle_Pion_TRUE", "h_2d_2ndtrkPathlength_2ndtrkangle_Pion_TRUE", Vertex_secondTrkPathway_bins.size()-1, Vertex_secondTrkPathway_bins.data(),Vertex_secondTrkTheta_bins.size()-1, Vertex_secondTrkTheta_bins.data()  );

//MnvH2D *h_2d_2ndtrkPathlength_2ndtrkangle_dimuon_TRUE_RECO    =    new MnvH2D("h_2d_2ndtrkPathlength_2ndtrkangle_dimuon_TRUE_RECO", "h_2d_2ndtrkPathlength_2ndtrkangle_dimuon_TRUE_RECO", Vertex_secondTrkPathway_bins.size()-1, Vertex_secondTrkPathway_bins.data(),Vertex_secondTrkTheta_bins.size()-1, Vertex_secondTrkTheta_bins.data()  );


//MnvH2D *h_2d_Theta_PT_TRUE         =    new MnvH2D("h_2d_Theta_PT_TRUE", "h_2d_Theta_PT_TRUE", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),PTbin_vector.size()-1, PTbin_vector.data()  );
//MnvH2D *h_2d_Theta_PT_TRUE_RECO    =    new MnvH2D("h_2d_Theta_PT_TRUE_RECO", "h_2d_Theta_PT_TRUE_RECO", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(),PTbin_vector.size()-1, PTbin_vector.data()  );
///////////////////////////////////////
//
///////////////////////////////////////

MnvH2D *h_2d_2ndtrkangle_2ndTrkE_TRUE         =    new MnvH2D("h_2d_2ndtrkangle_2ndTrkE_TRUE", "h_2d_2ndtrkangle_2ndTrkE_TRUE", Vertex_secondTrkTheta_bins.size()-1, Vertex_secondTrkTheta_bins.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );
MnvH2D *h_2d_2ndtrkangle_2ndTrkE_Proton_TRUE         =    new MnvH2D("h_2d_2ndtrkangle_2ndTrkE_Proton_TRUE", "h_2d_2ndtrkangle_2ndTrkE_Proton_TRUE", Vertex_secondTrkTheta_bins.size()-1, Vertex_secondTrkTheta_bins.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );
MnvH2D *h_2d_2ndtrkangle_2ndTrkE_Pion_TRUE         =    new MnvH2D("h_2d_2ndtrkangle_2ndTrkE_Pion_TRUE", "h_2d_2ndtrkangle_2ndTrkE_Pion_TRUE", Vertex_secondTrkTheta_bins.size()-1, Vertex_secondTrkTheta_bins.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );

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
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Pathlength_PROTON_TRUE("h_secTrk_Pathlength_PROTON_TRUE", "h_secTrk_Pathlength_PROTON_TRUTH",  Vertex_secondTrkPathway_bins , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Pathlength_PION_TRUE("h_secTrk_Pathlength_PION_TRUE", "h_secTrk_Pathlength_PION_TRUTH",  Vertex_secondTrkPathway_bins , error_bands);

//PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_tracklength_TRUE("h_secTrk_tracklength_TRUE", "Recoil track length  [cm] ", Recoil_track_length_vector , error_bands);



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

/*
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_Theta_TRUE_leading_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_leadingvsnonleading_categories, "h_secTrk_Theta_TRUE_leading_Particle", Vertex_secondTrkTheta_bins ,"h_secTrk_Theta_TRUE_leading_Particle; [Deg];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_Theta_TRUE_Nonleading_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_leadingvsnonleading_categories, "h_secTrk_Theta_TRUE_Nonleading_Particle", Vertex_secondTrkTheta_bins ,"h_secTrk_Theta_TRUE_nonleading_Particle; [Deg];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_Theta_TRUE_leadingFULL_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_Theta_TRUE_leadingFULL_Particle", Vertex_secondTrkTheta_bins ,"h_secTrk_Theta_TRUE_leadingFULL_Particle; [Deg];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_Theta_TRUE_NonleadingFULL_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_Theta_TRUE_NonleadingFULL_Particle", Vertex_secondTrkTheta_bins ,"h_secTrk_Theta_TRUE_NonleadingFULL_Particle; [Deg];Events");
*/


PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Energy_TRUE("h_secTrk_Energy_TRUE", "h_secTrk_Energy NEW Method",  Vertex_secondTrkEbins, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_EnergyFINEBinning_TRUE("h_secTrk_EnergyFINEBinning_TRUE", "h_secTrk_Energy NEW Method",  Vertex_secondTrkEbin_Proton_vector, error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type> h_secTrk_Energy_TRUE_Material =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Material_type>(MaterialGroup_categories, "h_secTrk_Energy_TRUE_Material", Vertex_secondTrkEbins ,"h_secTrk_Energy_TRUE_Material; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type> h_secTrk_Energy_TRUE_Interaction =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Interaction_type>(InteractionGroup_categories, "h_secTrk_Energy_TRUE_Interaction", Vertex_secondTrkEbins ,"h_secTrk_Energy_TRUE_Interaction; [GeV];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_Energy_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_Energy_TRUE_Particle", Vertex_secondTrkEbins ,"h_secTrk_Energy_TRUE_Particle; [GeV];Events");

/////////////////
/*
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_ALLKE_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_ALLKE_TRUE_Particle", Vertex_secondTrkEbins ,"h_secTrk_ALLKE_TRUE_Particle; [Deg];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_ALLKEFULL_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories ,"h_secTrk_ALLKEFULL_TRUE_Particle", Vertex_secondTrkEbins ,"h_secTrk_ALLKEFULL_TRUE_Particle; [Deg];Events");
*/
/*
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_KE_TRUE_leading_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_leadingvsnonleading_categories, "h_secTrk_KE_TRUE_leading_Particle", Vertex_secondTrkEbins ,"h_secTrk_KE_TRUE_leading_Particle; [Deg];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_KE_TRUE_Nonleading_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_leadingvsnonleading_categories, "h_secTrk_KE_TRUE_Nonleading_Particle", Vertex_secondTrkEbins ,"h_secTrk_KE_TRUE_nonleading_Particle; [Deg];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_KE_TRUE_leadingFULL_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_KE_TRUE_leadingFULL_Particle", Vertex_secondTrkEbins ,"h_secTrk_KE_TRUE_leadingFULL_Particle; [Deg];Events");
*/
//PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_KE_TRUE_NonleadingFULL_Particle =
//PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_KE_TRUE_NonleadingFULL_Particle", Vertex_secondTrkEbins ,"h_secTrk_KE_TRUE_NonleadingFULL_Particle; [Deg];Events");





PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Energy_PION_TRUE("h_secTrk_Energy_PION_TRUE", "h_secTrk_Energy PION (TRUE) ",  Vertex_secondTrkEbin_Proton_vector, error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_Theta_PION_TRUE("h_secTrk_Theta_PION_TRUE", "h_secTrk_Theta PION(TRUE)",  Vertex_secondTrkTheta_bins , error_bands);
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrkopenangle_PION_TRUE("h_secTrkopenangle_PION_TRUE", "h_secTrkopenangle PION (TRUE)",  Vertex_secondTrkTheta_bins , error_bands);

/*
PlotUtils::HistWrapper<HeliumCVUniverse> h_secTrk_ALLangles_TRUE("h_secTrk_ALLangles_TRUE", "h_secTrk_Theta PION0(TRUE)",  Vertex_secondTrkTheta_bins , error_bands);

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_ALLangles_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_ALLangles_TRUE_Particle", Vertex_secondTrkTheta_bins ,"h_secTrk_ALLangles_TRUE_Particle; [mm];Events");

PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type> h_secTrk_ALLanglesFULL_TRUE_Particle =
PlotUtils::HistFolio<PlotUtils::MnvH1D, Particle_type>(ParticleGroup_categories, "h_secTrk_ALLanglesFULL_TRUE_Particle", Vertex_secondTrkTheta_bins ,"h_secTrk_ALLanglesFULL_TRUE_Particle; [mm];Events");
*/


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


/////////////////////////////////////////
TRUE_Cut_Map Truth_Cut_Map;
FillingTruthCountingMap(kTRUTHCutsVector, Truth_Cut_Map);

std::cout << "Truth_Cut_Map.size() = " << Truth_Cut_Map.size()<< std::endl;
for(const auto & index :Truth_Cut_Map ){
  std::cout<<" Cut Name = " <<GetCutNameTRUTH(index.first).c_str() << " Amount = " << index.second << std::endl;
}


ProcInfo_t procInfo;
gSystem->GetProcInfo(&procInfo);

std::cout << "Memory/time used so Far: " << procInfo.fMemResident/1000<< " MB" <<" time = "<<  procInfo.fCpuSys <<  " Sec"<<"\n";

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"MC TRUTH LOOP  "<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
//////////////////
TDatabasePDG *pdg_DATABASEobject = TDatabasePDG::Instance();

std::string sysmatics_status;
if(m_RunCodeWithSystematics==true){sysmatics_status= "Systematics On";}
else if (m_RunCodeWithSystematics==false){sysmatics_status= "Systematics Off";}
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;
std::cout<<"~~~~~~~~~  "<< sysmatics_status <<" ~~~~~~~~~ "<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;

auto begin = std::chrono::high_resolution_clock::now();

//=========================================
// Entry Loop For MC
//=========================================

for(int ii=0; ii<chw_MC->GetEntries(); ++ii){

  if(ii%50000==0) std::cout << (ii/1000) << " k " << std::flush;

  //=========================================
  // For every systematic, loop over the universes, and fill the
  // appropriate histogram in the MnvH1D
  //=========================================


  for ( auto  Universe_GROUP: Error_Band_Universe_GROUPS){

    // std::vector<HeliumCVUniverse*> error_band_universes = band.second;
    Universe_GROUP.front()->SetEntry(ii);


    //////////////////////////////////////////////////////////
    ////  APPLY CUTS
    ///////////////////////////////////////////////////////////


    if(PassesCutsTRUTH(*Universe_GROUP.front(), kTRUTHCutsVector, kWeightVector, Truth_Cut_Map))
    {
      int secondTrk = -999;
      std::vector <int> PDG_trklist = Universe_GROUP.front()->GETvector_PDG_FS_particles();
      std::vector <double> Angle_trklist = Universe_GROUP.front()->GETvector_theta_wrtb_FS_particles();
      std::vector <double> Energy_trklist   = Universe_GROUP.front()->GETvector_KE_mc_FS_particles_GeV(pdg_DATABASEobject);
      secondTrk = Universe_GROUP.front()->Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_lessthanAngle(PDG_trklist, Energy_trklist, Angle_trklist);

      //std::vector <double> True_track_lenght_minerva = universe->MakeTRUE_VectorTrackLengthinMinerva_cm();

      if(secondTrk==-999){std::cout<<"ERROR got -999 for secondtrk "<<std::endl; assert(false);};


      /////////
      // Interaction parameters
      //////////

      int mc_incoming = Universe_GROUP.front()->Get_mc_incoming();
      int mc_current = Universe_GROUP.front()->Get_mc_current();
      int InteractionType = Universe_GROUP.front()->GetIntactionType();
      int TargetType = Universe_GROUP.front()->GetTargetType();

      //////////////////
      /// 2nd Trk
      ////////////////

      int pdg_2ndTrk = PDG_trklist.at(secondTrk);
      double secTrkTrueEnergy = Energy_trklist.at(secondTrk); // index 0 is leading FS lepton (Muon) sectrk shouldn't have 0
      double secTrkTrueAngle = Angle_trklist.at(secondTrk);
      double Pathlength2ndTrk = Universe_GROUP.front()->GetTRUE_nonMuoncolumnarDensity(secondTrk);
      double DOCA_2ndTrk = Universe_GROUP.front()->GetTRUE_nonMuonDOCA(secondTrk);

      /////////////////////////
      // Muon Varibles ///////
      ///////////////////////

      double MuonE = Universe_GROUP.front()->GetTRUE_Emu();
      double MuonPZ = Universe_GROUP.front()->GetTRUE_PZmu();
      double MuonPT = Universe_GROUP.front()->GetTRUE_PTmu();
      double MuonTheta = Universe_GROUP.front()->GetTRUE_muANGLE_WRTB_DEG();
      double OpenAngle = Universe_GROUP.front()->GetTRUE_NonmuTrkopenangle(secondTrk);
      double PhiMuonAngle = Universe_GROUP.front()->GetTRUE_Phimu();

      ////////////////////////
      /// Vertex Varibles ////
      ////////////////////////

      double VertexZ = Universe_GROUP.front()->GetTRUE_Vertex_z();
      double VertexR = Universe_GROUP.front()->GetTRUE_Vertex_r();
      double VertexX = Universe_GROUP.front()->GetTRUE_Vertex_x();
      double VertexY = Universe_GROUP.front()->GetTRUE_Vertex_y();

      ///////////////
      /// Stack Categories
      /////////////

      Particle_type Particle_type_Event = GetParticlegroup_type(pdg_2ndTrk);
      Interaction_type Interaction_type_Event =  Universe_GROUP.front()->Get_InteractionStackType();
      Material_type Material_type_Event = Universe_GROUP.front()->Get_MaterialStackType();


      for (auto universe : Universe_GROUP){


        universe->SetEntry(ii); //Tell the Event which entry in the TChain it's looking at

        /////////////////
        // Only the Weight need to calculated for each Universe since only Use Vertical Universes in TRUTH
        //////////////////
        double V1weight = universe->GetWeight(kWeightVector);
        /////////////////
        //
        //////////////////


        if(PDG_trklist.size()==1 || secondTrk==-999 || secondTrk==0){std::cout<<"ERROR"<<std::endl;assert(false); } // Double Checking if the check aren't working


        //std::cout<<" inside groups before secondTrk is found "<< std::endl;
        //secondTrk = universe->Returnindex_True_2ndTk_GreatestKE_lessthanAngle(PDG_trklist, Energy_trklist, Angle_trklist);
        //secondTrk = universe->Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_lessthanAngle_withKE_thresholdonProtonandPion(PDG_trklist, Energy_trklist, Angle_trklist );

        ///////////////////////////////////////////
        ////
        ////  FILL CV
        ////
        ///
        ///////////////////////////////////////////


        if( isCV(*universe)){

          /*
          Don't need to look at all this information
          turing off for now

          for(unsigned int i = 0; i != PDG_trklist.size(); ++i ){
            auto leadinggrounptype = GetParticlegroup_typeProtonandpion_other(PDG_trklist.at(i));
            auto FULLParticle_type_Event = GetParticlegroup_type(PDG_trklist.at(i));

            h_secTrk_ALLangles_TRUE_Particle.GetComponentHist(leadinggrounptype)->Fill(Angle_trklist.at(i), V1weight);
            h_secTrk_ALLanglesFULL_TRUE_Particle.GetComponentHist(FULLParticle_type_Event)->Fill(Angle_trklist.at(i), V1weight);
            h_secTrk_ALLKE_TRUE_Particle.GetComponentHist(leadinggrounptype)->Fill(Energy_trklist.at(i), V1weight);
            h_secTrk_ALLKEFULL_TRUE_Particle.GetComponentHist(FULLParticle_type_Event)->Fill(Energy_trklist.at(i), V1weight);
            h_TracksizeALL_TRUE_Particle.GetComponentHist(FULLParticle_type_Event)->Fill(i, V1weight);

            if(i==secondTrk && i!= 0){
              non_leading++;
              h_secTrk_Theta_TRUE_leading_Particle.GetComponentHist(leadinggrounptype)->Fill(Angle_trklist.at(i), V1weight);
              h_secTrk_Theta_TRUE_leadingFULL_Particle.GetComponentHist(FULLParticle_type_Event)->Fill(Angle_trklist.at(i), V1weight);
              h_secTrk_KE_TRUE_leading_Particle.GetComponentHist(leadinggrounptype)->Fill(Energy_trklist.at(i), V1weight);
              h_secTrk_KE_TRUE_leadingFULL_Particle.GetComponentHist(FULLParticle_type_Event)->Fill(Energy_trklist.at(i), V1weight);
              h_TracksizeALL_leadingTRUE_Particle.GetComponentHist(FULLParticle_type_Event)->Fill(i, V1weight);
            }
            else{
              h_secTrk_Theta_TRUE_Nonleading_Particle.GetComponentHist(leadinggrounptype)->Fill(Angle_trklist.at(i), V1weight);
              h_secTrk_Theta_TRUE_NonleadingFULL_Particle.GetComponentHist(FULLParticle_type_Event)->Fill(Angle_trklist.at(i), V1weight);
              h_secTrk_KE_TRUE_Nonleading_Particle.GetComponentHist(leadinggrounptype)->Fill(Energy_trklist.at(i), V1weight);
              h_secTrk_KE_TRUE_NonleadingFULL_Particle.GetComponentHist(FULLParticle_type_Event)->Fill(Energy_trklist.at(i), V1weight);
              h_TracksizeALL_nonleadingTRUE_Particle.GetComponentHist(FULLParticle_type_Event)->Fill(i, V1weight);
            }
          }
          */

          h_MuonE_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(MuonE, V1weight);
          h_MuonE_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(MuonE, V1weight);
          h_MuonE_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(MuonE, V1weight);

          h_MuonPZ_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(MuonPZ, V1weight);
          h_MuonPZ_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(MuonPZ, V1weight);
          h_MuonPZ_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(MuonPZ, V1weight);

          h_MuonPT_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(MuonPT, V1weight);
          h_MuonPT_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(MuonPT, V1weight);
          h_MuonPT_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(MuonPT, V1weight);

          h_MuonTheta_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(MuonTheta, V1weight);
          h_MuonTheta_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(MuonTheta, V1weight);
          h_MuonTheta_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(MuonTheta, V1weight);

          h_MuonPhi_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(PhiMuonAngle, V1weight);
          h_MuonPhi_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(PhiMuonAngle, V1weight);
          h_MuonPhi_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(PhiMuonAngle, V1weight);

          if(secondTrk!= 0){

            h_secTrk_Theta_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(secTrkTrueAngle, V1weight);
            h_secTrk_Theta_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(secTrkTrueAngle, V1weight);
            h_secTrk_Theta_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(secTrkTrueAngle, V1weight);

            h_secTrk_Energy_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(secTrkTrueEnergy, V1weight);
            h_secTrk_Energy_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(secTrkTrueEnergy, V1weight);
            h_secTrk_Energy_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(secTrkTrueEnergy, V1weight);
            //  std::cout<<"whats wrong 10 "<<std::endl;
            h_secTrk_DOCA_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(DOCA_2ndTrk, V1weight);
            h_secTrk_DOCA_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(DOCA_2ndTrk, V1weight);
            h_secTrk_DOCA_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(DOCA_2ndTrk, V1weight);


            h_secTrk_Pathlength_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(Pathlength2ndTrk, V1weight);
            h_secTrk_Pathlength_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(Pathlength2ndTrk, V1weight);
            h_secTrk_Pathlength_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(Pathlength2ndTrk, V1weight);

            h_2d_Theta_2ndTrkE_TRUE->Fill(MuonTheta,secTrkTrueEnergy,V1weight);
            h_2d_muonE_2ndTrkE_TRUE->Fill(MuonE,secTrkTrueEnergy,V1weight);
            h_2d_muonPT_2ndTrkE_TRUE->Fill(MuonPT,secTrkTrueEnergy,V1weight);
            h_2d_muonPZ_2ndTrkE_TRUE->Fill(MuonPZ,secTrkTrueEnergy,V1weight);
            h_2d_Theta_2ndTrKangle_TRUE->Fill(MuonTheta,secTrkTrueEnergy,V1weight);
            h_2d_muonE_2ndTrkangle_TRUE->Fill(MuonE,secTrkTrueAngle,V1weight);
            h_2d_muonPT_2ndTrkangle_TRUE->Fill(MuonPT,secTrkTrueAngle,V1weight);
            h_2d_muonPZ_2ndTrkangle_TRUE->Fill(MuonPZ,secTrkTrueAngle,V1weight);
            h_2d_2ndtrkangle_2ndTrkE_TRUE->Fill(secTrkTrueAngle,secTrkTrueEnergy,V1weight);
            h_2d_2ndtrkPathlength_2ndtrkangle_TRUE->Fill(Pathlength2ndTrk,secTrkTrueAngle,V1weight);
            h_2d_2ndtrkPathlength_2ndTrkE_TRUE->Fill(Pathlength2ndTrk,secTrkTrueEnergy,V1weight);

            if(Particle_type_Event==kSecondary_particle_vector[0]){
              h_2d_2ndtrkangle_2ndTrkE_Proton_TRUE->Fill(secTrkTrueAngle,secTrkTrueEnergy,V1weight);
              h_2d_Theta_2ndTrkE_Proton_TRUE->Fill(MuonTheta,secTrkTrueEnergy,V1weight);
              h_2d_muonE_2ndTrkE_Proton_TRUE->Fill(MuonE,secTrkTrueEnergy,V1weight);
              h_2d_muonPT_2ndTrkE_Proton_TRUE->Fill(MuonPT,secTrkTrueEnergy,V1weight);
              h_2d_muonPZ_2ndTrkE_Proton_TRUE->Fill(MuonPZ,secTrkTrueEnergy,V1weight);
              h_2d_2ndtrkPathlength_2ndtrkangle_Proton_TRUE->Fill(Pathlength2ndTrk,secTrkTrueAngle,V1weight);
              h_2d_2ndtrkPathlength_2ndTrkE_Proton_TRUE->Fill(Pathlength2ndTrk,secTrkTrueEnergy,V1weight);
            }
            if(Particle_type_Event==kSecondary_particle_vector[3]||Particle_type_Event==kSecondary_particle_vector[4]){
              // removed pi) Particle_type_Event==kSecondary_particle_vector[2]||
              h_2d_Theta_2ndTrkE_Pion_TRUE->Fill(MuonTheta,secTrkTrueEnergy,V1weight);
              h_2d_muonE_2ndTrkE_Pion_TRUE->Fill(MuonE,secTrkTrueEnergy,V1weight);
              h_2d_muonPT_2ndTrkE_Pion_TRUE->Fill(MuonPT,secTrkTrueEnergy,V1weight);
              h_2d_muonPZ_2ndTrkE_Pion_TRUE->Fill(MuonPZ,secTrkTrueEnergy,V1weight);
              h_2d_2ndtrkPathlength_2ndtrkangle_Pion_TRUE->Fill(Pathlength2ndTrk,secTrkTrueAngle,V1weight);
              h_2d_2ndtrkangle_2ndTrkE_Pion_TRUE ->Fill(secTrkTrueAngle,secTrkTrueEnergy,V1weight);
              h_2d_2ndtrkPathlength_2ndTrkE_Pion_TRUE->Fill(Pathlength2ndTrk,secTrkTrueEnergy,V1weight);

            }


            if(Particle_type_Event==kSecondary_particle_vector[1]){
              h_2d_2ndtrkangle_2ndTrkE_dimuon_TRUE->Fill(secTrkTrueAngle,secTrkTrueEnergy,V1weight);
            }


            if(Particle_type_Event== kElectron){h_Electron_secTrk_Theta_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(secTrkTrueAngle, V1weight);
              True_Event_info Electron_Event{mc_incoming,
                mc_current,
                InteractionType,
                TargetType,
                secondTrk,
                PDG_trklist,
                Angle_trklist,
                Energy_trklist
              };
              Electron_secTrkParticle.push_back(Electron_Event);
            }

            else if(Particle_type_Event== kPion_0){h_Pion0_secTrk_Theta_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(secTrkTrueAngle, V1weight);}
            else if(Particle_type_Event== kPion_neg){h_Pion_neg_secTrk_Theta_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(secTrkTrueAngle, V1weight);}
            else if(Particle_type_Event== kPion_pos){h_Pion_pos_secTrk_Theta_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(secTrkTrueAngle, V1weight);}
            else if(Particle_type_Event== kKaon){h_Kaon_secTrk_Theta_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(secTrkTrueAngle, V1weight);}
            else if(Particle_type_Event== kProton){h_Proton_secTrk_Theta_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(secTrkTrueAngle, V1weight);}
            else if(Particle_type_Event== kNeutron){h_Neutron_secTrk_Theta_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(secTrkTrueAngle, V1weight);}
            else if(Particle_type_Event== kMuon){h_Muon_secTrk_Theta_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(secTrkTrueAngle, V1weight);}
      else if(Particle_type_Event== kGamma){h_Gamma_secTrk_Theta_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(secTrkTrueAngle, V1weight);}
      else if(Particle_type_Event== kNeutrino_muon){
        std::cout<< " NEUTRINO EVENT evevnt = " << ii << std::endl;
        h_Nu_mu_secTrk_Theta_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(secTrkTrueAngle, V1weight);
        True_Event_info Nu_mu_Event{mc_incoming,
          mc_current,
          InteractionType,
          TargetType,
          secondTrk,
          PDG_trklist,
          Angle_trklist,
          Energy_trklist
        };


        auto TRUE_indexs = universe->Get_TRUE_indexs();
        auto ALLID = universe->Get_TRUE_vector_ALL_Event_PDG();
        ALL_True_Event_info Nu_E_Event_All{mc_incoming,
          mc_current,
          InteractionType,
          TargetType,
          secondTrk,
          TRUE_indexs.at(0), // Mother id
          TRUE_indexs.at(1), // Fdaugther
          TRUE_indexs.at(2), // Ldaugther
          PDG_trklist,
          Angle_trklist,
          Energy_trklist,
          ALLID};


          ALL_EventInfoNu_mu_secTrkParticle.push_back(Nu_E_Event_All);
          Nu_mu_secTrkParticle.push_back(Nu_mu_Event);
        }
        else if(Particle_type_Event== kFourHelium)
        {h_4helium_secTrk_Theta_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(secTrkTrueAngle, V1weight);

          True_Event_info fourhelium_Event{mc_incoming,
            mc_current,
            InteractionType,
            TargetType,
            secondTrk,
            PDG_trklist,
            Angle_trklist,
            Energy_trklist
          };
          fourHelium_secTrkParticle.push_back(fourhelium_Event);
        }
        else if(Particle_type_Event== kLamdba){h_Lamdba_secTrk_Theta_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(secTrkTrueAngle, V1weight);}
        else if(Particle_type_Event== kSigma_plus){h_Sigma_plus_secTrk_Theta_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(secTrkTrueAngle, V1weight);}
      } // End of Second trk condition

      h_CryoVertex_X_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(VertexX, V1weight);
      h_CryoVertex_X_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(VertexX, V1weight);
      h_CryoVertex_X_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(VertexX, V1weight);

      h_CryoVertex_Y_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(VertexY, V1weight);
      h_CryoVertex_Y_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(VertexY, V1weight);
      h_CryoVertex_Y_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(VertexY, V1weight);

      h_CryoVertex_Z_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(VertexZ, V1weight);
      h_CryoVertex_Z_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(VertexZ, V1weight);
      h_CryoVertex_Z_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(VertexZ, V1weight);

      h_CryoVertex_R_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(VertexR, V1weight);
      h_CryoVertex_R_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(VertexR, V1weight);
      h_CryoVertex_R_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(VertexR, V1weight);

      h_Tracksize_TRUE_Material.GetComponentHist(Material_type_Event)->Fill(universe->GetTRUE_Tracksize(), V1weight);
      h_Tracksize_TRUE_Interaction.GetComponentHist(Interaction_type_Event)->Fill(universe->GetTRUE_Tracksize(), V1weight);
      h_Tracksize_TRUE_Particle.GetComponentHist(Particle_type_Event)->Fill(universe->GetTRUE_Tracksize(), V1weight);


      h_2d_PZ_PT_TRUE->Fill(MuonPZ,MuonPT,V1weight);
      h_2d_E_PZ_TRUE->Fill(MuonE,MuonPZ,V1weight);
      h_2d_Theta_PZ_TRUE->Fill(MuonTheta,MuonPZ,V1weight);
      h_2d_E_PT_TRUE->Fill(MuonE,MuonPT,V1weight);
      h_2d_Theta_PT_TRUE->Fill(MuonTheta,MuonPT,V1weight);
      h_2d_Theta_PZ_TRUE->Fill(MuonTheta,MuonPZ,V1weight);


    }//end of CV

    ///////////////////////////////////////////
    ////
    ////  END OF CV
    ////
    ///////////////////////////////////////////



    //std::cout<< "GetMuonAngleWRTB() > 12.0" << universe->GetMuonAngleWRTB() <<std::endl;
    //=========================================
    // CUTS in each universe
    //=========================================
    ////////////
    ///TRUTH
    //////////
    // Different Methods Selecting 2nd Trk  MAY need to revist
    //secondTrk = universe->Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_lessthanAngle(PDG_trklist, Energy_trklist, Angle_trklist ) ;
    //secondTrk = universe->Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_lessthanAngle_withKE_thresholdonProtonandPion(PDG_trklist, Energy_trklist, Angle_trklist) ;
    //secondTrk = universe->Returnindex_True_2ndTk_GreatestKE_lessthanAngle(PDG_trklist, Energy_trklist, Angle_trklist);

    h_MuonE_TRUE.univHist(universe)->Fill(MuonE,V1weight);

    h_MuonPZ_TRUE.univHist(universe)->Fill(MuonPZ,V1weight);

    h_MuonPT_TRUE.univHist(universe)->Fill(MuonPT,V1weight);

    h_MuonTheta_TRUE.univHist(universe)->Fill(MuonTheta,V1weight);

    h_CryoVertex_X_TRUE.univHist(universe)->Fill(VertexX,V1weight);

    h_CryoVertex_Y_TRUE.univHist(universe)->Fill(VertexY,V1weight);

    h_CryoVertex_Z_TRUE.univHist(universe)->Fill(VertexZ,V1weight);

    h_CryoVertex_R_TRUE.univHist(universe)->Fill(VertexR,V1weight);

    h_Tracksize_TRUE.univHist(universe)->Fill(universe->GetTRUE_Tracksize(),V1weight);

    h_secTrk_DOCA_TRUE.univHist(universe)->Fill(DOCA_2ndTrk,V1weight);

    h_secTrk_Pathlength_TRUE.univHist(universe)->Fill(Pathlength2ndTrk,V1weight);

    h_secTrk_Energy_TRUE.univHist(universe)->Fill(secTrkTrueEnergy,V1weight);

    h_secTrk_EnergyFINEBinning_TRUE.univHist(universe)->Fill(secTrkTrueEnergy,V1weight);

    h_secTrk_Theta_TRUE.univHist(universe)->Fill(secTrkTrueAngle,V1weight);

    h_secTrk_Openangle_TRUE.univHist(universe)->Fill(OpenAngle,V1weight);

    //h_secTrk_tracklength_TRUE.univHist(universe)->Fill(secTrkTruetrackLength,V1weight);

    if(Particle_type_Event==kSecondary_particle_vector[0])
    {
      h_secTrk_Energy_PROTON_TRUE.univHist(universe)->Fill(secTrkTrueEnergy,V1weight);
      h_secTrk_Theta_PROTON_TRUE.univHist(universe)->Fill(secTrkTrueAngle,V1weight);
      h_secTrkopenangle_PROTON_TRUE.univHist(universe)->Fill(OpenAngle,V1weight);
      h_secTrk_Pathlength_PROTON_TRUE.univHist(universe)->Fill(Pathlength2ndTrk,V1weight);
    }

    if(Particle_type_Event==kSecondary_particle_vector[3]||Particle_type_Event==kSecondary_particle_vector[4])
    {
      h_secTrk_Energy_PION_TRUE.univHist(universe)->Fill(secTrkTrueEnergy,V1weight);
      h_secTrk_Theta_PION_TRUE.univHist(universe)->Fill(secTrkTrueAngle,V1weight);
      h_secTrkopenangle_PION_TRUE.univHist(universe)->Fill(OpenAngle,V1weight);
      h_secTrk_Pathlength_PION_TRUE.univHist(universe)->Fill(Pathlength2ndTrk,V1weight);
    }

    if(Particle_type_Event==kSecondary_particle_vector[1])
    {
      h_secTrk_Energy_Dimuon_TRUE.univHist(universe)->Fill(secTrkTrueEnergy,V1weight);
      h_secTrk_Theta_Dimuon_TRUE.univHist(universe)->Fill(secTrkTrueAngle,V1weight);
    }

  } //  End band's individual universe loop

} ////END OF TRUTH PASS CUTS
} // End Band Groups loop

} //End entries loop

auto end = std::chrono::high_resolution_clock::now();
auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
std::cout<<" "<<std::endl;
printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);

gSystem->GetProcInfo(&procInfo);
std::cout << " Done with loop Mem1: " << procInfo.fMemResident/1000 << " MB" << " time = "<<  procInfo.fCpuSys  <<  " sec""\n";
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

h_MuonPZ_TRUE.SyncCVHistos();
h_MuonPT_TRUE.SyncCVHistos();
h_MuonE_TRUE.SyncCVHistos();
h_MuonTheta_TRUE.SyncCVHistos();
h_secTrk_DOCA_TRUE.SyncCVHistos();
h_Tracksize_TRUE.SyncCVHistos();
//////////////////////////////////

h_CryoVertex_X_TRUE.SyncCVHistos();
h_CryoVertex_Y_TRUE.SyncCVHistos();
h_CryoVertex_R_TRUE.SyncCVHistos();
h_CryoVertex_Z_TRUE.SyncCVHistos();

//////////////////////////////////
h_secTrk_Energy_TRUE.SyncCVHistos();
h_secTrk_EnergyFINEBinning_TRUE.SyncCVHistos();
h_secTrk_Theta_TRUE.SyncCVHistos();
h_secTrk_Openangle_TRUE.SyncCVHistos();
h_secTrk_Theta_Dimuon_TRUE.SyncCVHistos();
h_secTrk_Pathlength_TRUE.SyncCVHistos();
h_secTrk_Pathlength_PROTON_TRUE.SyncCVHistos();
h_secTrk_Pathlength_PION_TRUE.SyncCVHistos();
//h_secTrk_tracklength_TRUE.SyncCVHistos();


h_secTrk_Energy_Dimuon_TRUE.SyncCVHistos();
h_secTrk_Energy_PROTON_TRUE.SyncCVHistos();
h_secTrk_Theta_PROTON_TRUE.SyncCVHistos();
h_secTrkopenangle_PROTON_TRUE.SyncCVHistos();
h_secTrk_Energy_PION_TRUE.SyncCVHistos();
h_secTrk_Theta_PION_TRUE.SyncCVHistos();
h_secTrkopenangle_PION_TRUE.SyncCVHistos();


//h_secTrk_ALLangles_TRUE.SyncCVHistos();
//////////////////////////////////
//////////////////////////////////


//=========================================
// Plotting stuff
//=========================================


//=========================================
// Write out Root filie
//=========================================



char outFileName[1024];
auto playlist_name = Playlist_Info.GetPlaylistname();
std::string datatype = "TRUTH";
char c[playlist_name.length() + 1];
char d[datatype.length() + 1];

char rootpathway[OUTputRoot_pathway.length()+1];
strcpy(rootpathway, OUTputRoot_pathway.c_str());
strcpy(c, playlist_name.c_str());
strcpy(d, datatype.c_str());

TGraph *Truth_Cuts =  Make_TruthCut_Tgraph_fromCutMap("Truth_Cuts", Truth_Cut_Map);

for(auto cuts: Truth_Cut_Map){
  std::cout<<"Cut Name: " << GetCutNameTRUTH(cuts.first ) <<  " Amount = " << cuts.second << std::endl;
}

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

  if(Run_EventLoopOnGrid==true){  sprintf(outFileName, "Histograms_%s_%s_%s.root",c,d,sysmatics_status_char);
}
else{
  sprintf(outFileName, "%s/Histograms_%s_%s_%s.root",rootpathway,c,d,sysmatics_status_char);
}

std::cout << "Writing output file to: " <<outFileName << std::endl;

TFile *outFile = new TFile(outFileName,"RECREATE");
TChain POT_branch("Meta");
POT_branch.Add(RootName.c_str());
//TTree *oldtree = (TTree*)file->Get("Meta");
TTree *clone = POT_branch.CloneTree();
clone->Write();
Truth_Cuts->Write();
h_secTrk_DOCA_TRUE.hist->Write();
h_secTrk_DOCA_TRUE_Material.WriteToFile(*outFile);
h_secTrk_DOCA_TRUE_Interaction.WriteToFile(*outFile);
h_secTrk_DOCA_TRUE_Particle.WriteToFile(*outFile);

h_secTrk_Pathlength_TRUE.hist->Write();
h_secTrk_Pathlength_TRUE_Material.WriteToFile(*outFile);
h_secTrk_Pathlength_TRUE_Interaction.WriteToFile(*outFile);
h_secTrk_Pathlength_TRUE_Particle.WriteToFile(*outFile);

//h_secTrk_tracklength_TRUE.hist->Write();

h_secTrk_Pathlength_PROTON_TRUE.hist->Write();
h_secTrk_Pathlength_PION_TRUE.hist->Write();

////////////////////////////////////////////////
h_MuonE_TRUE.hist->Write();
h_MuonE_TRUE_Material.WriteToFile(*outFile);
h_MuonE_TRUE_Interaction.WriteToFile(*outFile);
h_MuonE_TRUE_Particle.WriteToFile(*outFile);

h_MuonPZ_TRUE.hist->Write();
h_MuonPZ_TRUE_Material.WriteToFile(*outFile);
h_MuonPZ_TRUE_Interaction.WriteToFile(*outFile);
h_MuonPZ_TRUE_Particle.WriteToFile(*outFile);

h_MuonPT_TRUE.hist->Write();
h_MuonPT_TRUE_Material.WriteToFile(*outFile);
h_MuonPT_TRUE_Interaction .WriteToFile(*outFile);
h_MuonPT_TRUE_Particle.WriteToFile(*outFile);

h_MuonTheta_TRUE.hist->Write();
h_MuonTheta_TRUE_Material.WriteToFile(*outFile);
h_MuonTheta_TRUE_Interaction.WriteToFile(*outFile);
h_MuonTheta_TRUE_Particle.WriteToFile(*outFile);


h_CryoVertex_X_TRUE.hist->Write();
h_CryoVertex_X_TRUE_Material.WriteToFile(*outFile);
h_CryoVertex_X_TRUE_Interaction.WriteToFile(*outFile);
h_CryoVertex_X_TRUE_Particle.WriteToFile(*outFile);

h_CryoVertex_Y_TRUE.hist->Write();
h_CryoVertex_Y_TRUE_Material.WriteToFile(*outFile);
h_CryoVertex_Y_TRUE_Interaction.WriteToFile(*outFile);
h_CryoVertex_Y_TRUE_Particle.WriteToFile(*outFile);

h_CryoVertex_Z_TRUE.hist->Write();
h_CryoVertex_Z_TRUE_Material.WriteToFile(*outFile);
h_CryoVertex_Z_TRUE_Interaction.WriteToFile(*outFile);
h_CryoVertex_Z_TRUE_Particle.WriteToFile(*outFile);

h_CryoVertex_R_TRUE.hist->Write();
h_CryoVertex_R_TRUE_Material.WriteToFile(*outFile);
h_CryoVertex_R_TRUE_Interaction.WriteToFile(*outFile);
h_CryoVertex_R_TRUE_Particle.WriteToFile(*outFile);

h_secTrk_Openangle_TRUE.hist->Write();
h_secTrk_Openangle_TRUE_Material.WriteToFile(*outFile);
h_secTrk_Openangle_TRUE_Interaction.WriteToFile(*outFile);
h_secTrk_Openangle_TRUE_Particle.WriteToFile(*outFile);

h_secTrk_Energy_TRUE.hist->Write();
h_secTrk_EnergyFINEBinning_TRUE.hist->Write();
h_secTrk_Energy_TRUE_Material.WriteToFile(*outFile);
h_secTrk_Energy_TRUE_Interaction.WriteToFile(*outFile);
h_secTrk_Energy_TRUE_Particle.WriteToFile(*outFile);

h_secTrk_Theta_TRUE.hist->Write();
h_secTrk_Theta_TRUE_Material.WriteToFile(*outFile);
h_secTrk_Theta_TRUE_Interaction.WriteToFile(*outFile);
h_secTrk_Theta_TRUE_Particle.WriteToFile(*outFile);

//h_secTrk_ALLangles_TRUE.hist->Write();

h_Tracksize_TRUE.hist->Write();
h_Tracksize_TRUE_Material.WriteToFile(*outFile);
h_Tracksize_TRUE_Interaction.WriteToFile(*outFile);
h_Tracksize_TRUE_Particle.WriteToFile(*outFile);

h_secTrk_Energy_Dimuon_TRUE.hist->Write();
h_secTrk_Theta_Dimuon_TRUE.hist->Write();
h_secTrk_Energy_PROTON_TRUE.hist->Write();
h_secTrk_Theta_PROTON_TRUE.hist->Write();
h_secTrkopenangle_PROTON_TRUE.hist->Write();
h_secTrk_Energy_PION_TRUE.hist->Write();
h_secTrk_Theta_PION_TRUE.hist->Write();
h_secTrkopenangle_PION_TRUE.hist->Write();


//h_secTrk_Theta_TRUE_leading_Particle.WriteToFile(*outFile);
//h_secTrk_Theta_TRUE_leadingFULL_Particle.WriteToFile(*outFile);
//h_secTrk_Theta_TRUE_Nonleading_Particle.WriteToFile(*outFile);
//h_secTrk_Theta_TRUE_NonleadingFULL_Particle.WriteToFile(*outFile);

//h_secTrk_KE_TRUE_leading_Particle.WriteToFile(*outFile);
//h_secTrk_KE_TRUE_leadingFULL_Particle.WriteToFile(*outFile);
//h_secTrk_KE_TRUE_Nonleading_Particle.WriteToFile(*outFile);

//h_secTrk_ALLKE_TRUE_Particle.WriteToFile(*outFile);
//h_secTrk_ALLKEFULL_TRUE_Particle.WriteToFile(*outFile);
//h_secTrk_ALLangles_TRUE_Particle.WriteToFile(*outFile);
//h_secTrk_ALLanglesFULL_TRUE_Particle.WriteToFile(*outFile);
//h_TracksizeALL_TRUE_Particle.WriteToFile(*outFile);
//h_TracksizeALL_leadingTRUE_Particle.WriteToFile(*outFile);
//h_TracksizeALL_nonleadingTRUE_Particle.WriteToFile(*outFile);
//h_secTrk_KE_TRUE_NonleadingFULL_Particle.WriteToFile(*outFile);



h_Electron_secTrk_Theta_TRUE_Interaction.WriteToFile(*outFile);
h_Pion_neg_secTrk_Theta_TRUE_Interaction.WriteToFile(*outFile);
h_Pion_pos_secTrk_Theta_TRUE_Interaction.WriteToFile(*outFile);
h_Kaon_secTrk_Theta_TRUE_Interaction.WriteToFile(*outFile);
h_Proton_secTrk_Theta_TRUE_Interaction.WriteToFile(*outFile);
h_Neutron_secTrk_Theta_TRUE_Interaction.WriteToFile(*outFile);
h_Muon_secTrk_Theta_TRUE_Interaction.WriteToFile(*outFile);
h_Particle_OTHER_secTrk_Theta_TRUE_Interaction.WriteToFile(*outFile);
h_Gamma_secTrk_Theta_TRUE_Interaction.WriteToFile(*outFile);
h_Nu_mu_secTrk_Theta_TRUE_Interaction.WriteToFile(*outFile);
h_Nu_e_secTrk_Theta_TRUE_Interaction.WriteToFile(*outFile);
h_Anti_nu_secTrk_Theta_TRUE_Interaction.WriteToFile(*outFile);
h_Particle_N_A_secTrk_Theta_TRUE_Interaction.WriteToFile(*outFile);
h_4helium_secTrk_Theta_TRUE_Interaction.WriteToFile(*outFile);
h_Lamdba_secTrk_Theta_TRUE_Interaction.WriteToFile(*outFile);
h_Sigma_plus_secTrk_Theta_TRUE_Interaction.WriteToFile(*outFile);


h_2d_PZ_PT_TRUE->Write();
h_2d_E_PZ_TRUE->Write();
h_2d_Theta_PZ_TRUE->Write();
h_2d_E_PT_TRUE->Write();
h_2d_Theta_PZ_TRUE->Write();
h_2d_Theta_PT_TRUE->Write();
h_2d_Theta_2ndTrkE_TRUE->Write();
h_2d_muonE_2ndTrkE_TRUE->Write();
h_2d_muonPT_2ndTrkE_TRUE->Write();
h_2d_muonPZ_2ndTrkE_TRUE->Write();

h_2d_Theta_2ndTrkE_Pion_TRUE->Write();
h_2d_muonE_2ndTrkE_Pion_TRUE->Write();
h_2d_muonPT_2ndTrkE_Pion_TRUE->Write();
h_2d_muonPZ_2ndTrkE_Pion_TRUE->Write();

h_2d_Theta_2ndTrkE_Proton_TRUE->Write();
h_2d_muonE_2ndTrkE_Proton_TRUE->Write();
h_2d_muonPT_2ndTrkE_Proton_TRUE->Write();
h_2d_muonPZ_2ndTrkE_Proton_TRUE->Write();

h_2d_Theta_2ndTrKangle_TRUE->Write();
h_2d_muonE_2ndTrkangle_TRUE->Write();
h_2d_muonPT_2ndTrkangle_TRUE->Write();
h_2d_muonPZ_2ndTrkangle_TRUE->Write();

h_2d_2ndtrkangle_2ndTrkE_TRUE->Write();
h_2d_2ndtrkangle_2ndTrkE_Proton_TRUE->Write();
h_2d_2ndtrkangle_2ndTrkE_Pion_TRUE->Write();
h_2d_2ndtrkangle_2ndTrkE_dimuon_TRUE->Write();

h_2d_2ndtrkPathlength_2ndtrkangle_TRUE->Write();
h_2d_2ndtrkPathlength_2ndtrkangle_Proton_TRUE->Write();
h_2d_2ndtrkPathlength_2ndtrkangle_Pion_TRUE->Write();

h_2d_2ndtrkPathlength_2ndTrkE_TRUE->Write();
h_2d_2ndtrkPathlength_2ndTrkE_Proton_TRUE->Write();
h_2d_2ndtrkPathlength_2ndTrkE_Pion_TRUE->Write();

outFile->Close();

for(auto band : error_bands){
  std::vector<HeliumCVUniverse*> band_universes = band.second;
  for(unsigned int i_universe = 0; i_universe < band_universes.size(); ++i_universe){ delete band_universes[i_universe];}
}

std::cout << "Success in TRUTH LOOP - Gotcha !?!?" << std::endl;


}
//END of Event Loop

//=========================================
//=========================================
//////////////////////////////////////////////////////////////
std::vector<ECutsTRUTH> GetTRUTHCutsVector() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ECutsTRUTH> True_vec;
  True_vec.push_back(kTRUTHNoCuts  );
  True_vec.push_back(kTRUTHneutrino);
  True_vec.push_back(kTRUTHCCInteraction );
  True_vec.push_back(kTRUTHtarget);
  True_vec.push_back(kTRUTHMuonEnergy );
  True_vec.push_back(kTRUTHMuonAngle );
  True_vec.push_back(kTRUTHFiduical );
  True_vec.push_back(kTRUTH_greaterthanoneFS);
  //True_vec.push_back(kTRUTH_secTrk_Angle_threshold);
  True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold_withProtonanPionThresholds);
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
  //True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold_withProtonanPionThresholds);
  True_vec.push_back(kTRUTH_No_Neutral_secTrk_Angle_threshold);
  //True_vec.push_back(kTRUTH_2ndTrkProtonEnergythreshold);
  //True_vec.push_back(kTRUTH_2ndTrkPionEnergythreshold);
  True_vec.push_back(kAllTRUTHCuts);


  //int n = sizeof(kCutsArray) / sizeof(kCutsArray[0]);
  //static std::vector<ECuts> ret_vec(kCutsArray, kCutsArray + n);
  return True_vec;
//#endif
}


//////////////////////////////////////////////////////////////////////////
//GET MUON Varibles
//////////////////////////////////////////////////////////////////////////

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


std::vector<Weights> GetWeightVector() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<Weights> weight_vec;
  weight_vec.push_back(kweightFlux );

  //weight_vec.push_back(kweightMinos ); Don't apply Minos efficiency weight to truth
  weight_vec.push_back(kweightGenie);
  weight_vec.push_back(kweight2p2ptune );
  weight_vec.push_back(kweightRPA);
  weight_vec.push_back(kweight_HeliumTargetMass);
  //weight_vec.push_back(kweightLowQ2Pi);

  return weight_vec;
//#endif
}

/*
std::vector<std::vector<HeliumCVUniverse*>> groupCompatibleUniverses(const std::map<std::string, std::vector<HeliumCVUniverse*>> bands)
  {
    std::vector<std::vector<HeliumCVUniverse*>> groupedUnivs;
    std::vector<HeliumCVUniverse*> vertical;
    for(const auto& band: bands)
    {
      if(band.first == "cv") vertical.insert(vertical.begin(), band.second.begin(), band.second.end());
      else
      {
        for(const auto univ: band.second)
        {
          if(univ->IsVerticalOnly()) vertical.push_back(univ);
          else groupedUnivs.push_back(std::vector<HeliumCVUniverse*>{univ});
        }
      }
    }
    groupedUnivs.insert(groupedUnivs.begin(), vertical);
    return groupedUnivs;
  }
*/
//////////////////////////////////////////////////////////////////////////
//GET CryoTank Varibles
//////////////////////////////////////////////////////////////////////////


//////////////////////////
///Main
/////////////////////////
int main(int argc, char* argv[]){


 std::cout << "This is the playlist "<< argv[1] << std::endl;
std::string playlist_string(argv[1]);
ME_helium_Playlists Playlist_to_run = GetPlaylist_FromString(playlist_string);



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

  bool Run_EventLoopOnGrid = false;
  if(Run_EventLoopOnGrid==true){std::cout << "This Eventloop is step up to run on the Grid" << std::endl;}
  else{std::cout << "This Eventloop is step up to run locally" << std::endl;}
  //std::cin >> input_user;
  std::cout << input_user << std::endl;


  runEventLoop(Playlist_to_run, Run_EventLoopOnGrid);
  return 0;
}
//#endif
