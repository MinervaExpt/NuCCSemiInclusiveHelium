// Loop entries, make cuts, fill histograms.
// * Uses the New Systematics Framework and "Universe" objects.
// * loop universes, make cuts and fill histograms with the correct lateral
// shifts and weights for each universe.
// * TChain --> PlotUtils::ChainWrapper.
// * MnvHXD --> PlotUtils::HistWrapper.
// * Genie, flux, non-resonant pion, and some detector systematics calculated.
#include "Helium2D_runTRUTHLoop.h"

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
std::vector<Weights> GetWeightVector();
//std::vector<ME_helium_Playlists> GetTRUEPlayListVector();
std::vector<Particle_type>  GetParicle_type();


//double Mev_to_GeV=.001;

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

const int n_flux_universes = 25;
std::map< std::string, std::vector<HeliumCVUniverse*> >
  GetErrorBands(PlotUtils::ChainWrapper* chain) {
    typedef std::map< std::string, std::vector<HeliumCVUniverse*> > SystMap;
    //const int n_flux_universes = 50;
    SystMap error_bands;

    // CV
    error_bands[std::string("CV")].push_back( new HeliumCVUniverse(chain) );

    //Detector systematics, lateral shifts

    if(m_RunCodeWithSystematics==true)
    {
      //GENIE
      SystMap genie_systematics = PlotUtils::GetGenieSystematicsMap<HeliumCVUniverse>(chain);
      error_bands.insert(genie_systematics.begin(), genie_systematics.end());
      //2p2h tune talk
      SystMap a2p2h_systematics = PlotUtils::Get2p2hSystematicsMap<HeliumCVUniverse>(chain);
      error_bands.insert(a2p2h_systematics.begin(), a2p2h_systematics.end());
      //RPA model
      SystMap RPA_systematics = PlotUtils::GetRPASystematicsMap<HeliumCVUniverse>(chain);
      error_bands.insert(RPA_systematics.begin(), RPA_systematics.end());
      //Flux
      SystMap flux_systematics = PlotUtils::GetFluxSystematicsMap<HeliumCVUniverse>(chain,n_flux_universes);
      error_bands.insert(flux_systematics.begin(), flux_systematics.end());
    }



//    SystMap muonP_systematics = PlotUtils::GetMuonSystematicsMap<HeliumCVUniverse>(chain,NSFDefaults::KludgedMinosMuonMomentum_Err);
  //  error_bands.insert(muonP_systematics.begin(), muonP_systematics.end());
    //std::cout << "C++ make muon resolution systematics" << std::endl;




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
void runEventLoop(ME_helium_Playlists &PlayList_iterator, bool &m_debugOn, bool &Run_EventLoopOnGrid) {
  // Make a chain of events
  loadLibs();

//std::vector<ECuts> kTRUTHCutsVector;

double POT[4];
const std::vector<ECutsTRUTH> kTRUTHCutsVector = GetTRUTHCutsVector();
const std::vector<ME_helium_Playlists> kPlayListVector = GetPlayListVector();
//const std::vector< ME_helium_Playlists> kTRUEPlayListVector = GetTRUEPlayListVector();
const std::vector<Weights> kWeightVector = GetWeightVector();
const std::vector<MuonVar> kMuonVaribles_vector = GetMUONVaribles();
const std::vector<SecondTrkVar> kSecTrkVaribles_vector = GetPlayListSecondTrkVector();

const std::vector<CryoVertex> kCryoVertexVaribles_vector = GetCryoVertexVaribles();

const std::vector<Particle_type> kSecondary_particle_vector = GetParicle_type();

std::ofstream output("LogFile_TRUTH.txt",std::ofstream::app);


std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"MC TRUTH LOOP  "<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
//////////////////
TDatabasePDG *pdg_DATABASEobject = TDatabasePDG::Instance();





//======================================================================
////////////////////ADDING TO CHAIN wrapper ///////////////////////////
//======================================================================
bool is_mc= true;

  std::string playlist = GetPlaylist(PlayList_iterator);

  MinervaUniverse::SetPlaylist(playlist);


 std::string seestring = MinervaUniverse::GetPlaylist();
  HeliumPlayListInfo Playlist_Info(playlist);
  std::cout<<"Working with Playlist =  "<<   seestring <<std::endl;
  MinervaUniverse::SetNuEConstraint(true);
  MinervaUniverse::SetAnalysisNuPDG(14);
  MinervaUniverse::SetNFluxUniverses(n_flux_universes);
  MinervaUniverse::SetZExpansionFaReweight(false);
  MinervaUniverse::SetNonResPiReweight(true);
  MinervaUniverse::SetDeuteriumGeniePiTune(false);


  int nu_pdg = MinervaUniverse::GetAnalysisNuPDG();
  std::string playlist_fluxreweighter = MinervaUniverse::GetPlaylist();
  bool useNuEconstraint = MinervaUniverse::UseNuEConstraint();
  int NFlux_universe = MinervaUniverse::GetNFluxUniverses();
  bool useMuonCorrelations = true;
  double Min_NuFluxEnergy = 0.0;
  double Max_NuFluxEnergy = 120.0;

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
//double mcPOT = GetPOT(chw_MC, "MC");
std::cout<<"Number of Universes set is = "<< 	MinervaUniverse::GetNFluxUniverses()<<std::endl;
//std::string NumU = MinervaUniverse::GetNFluxUniverses()<<std::endl;
//Debug("Number of Universes set is = " );
//Debug(NumU);
//MinervaUniverse::SetNFluxUniverses(25);
POTCounter pot_counter;
const std::string RootName = GetPlaylist_ROOT_path(PlayList_iterator,true);
//const std::string RootName = GetPlaylist_ROOT_path("1D_EnergyFix",  is_mc );
std::cout<<"The Playlist that is set is = "<< seestring <<std::endl;
std::cout<<"The Playlist Root = "<< RootName<<std::endl;
 ///pnfs/minerva/persistent/users/cnguyen/ME_G1_Merg/*.root


  auto mcscale = 1.0; //Data_POT_full/ MC_POT_full;
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

  output<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  output<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

  output<<"Weights Applied on Event by event"<< endl;
  for(auto Weight_name:kWeightVector )
  {
    output<<"  Weights type: " <<GetWeight_name(Weight_name) <<endl;
  }

  output<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  output<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

  //LogFile LOGFILE(PlayList_iterator ,kTRUTHCutsVector , kWeightVector, kTRUTHCutsVector, 1,true,_logfile);
  //LOGFILE<<"Number of Universes set is = "<< 	MinervaUniverse::GetNFluxUniverses()<<"/n";


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
std::vector<double> Vertex_secondTrkEbins= GetSecondTrkVarVector(ksecE);
std::vector<double> Vertex_secondTrkEbin_Proton_vector= GetSecondTrkVarVector(ksecE_Proton);
std::sort(Vertex_secondTrkEbin_Proton_vector.begin(),Vertex_secondTrkEbin_Proton_vector.end());
std::vector<double> Vertex_secondTrkTheta_bins= GetSecondTrkVarVector(kFullAngle);
std::vector<double> Vertex_secondTrkDOCA_bins= GetSecondTrkVarVector(kDOCA);
std::vector<double> Vertex_secondTrkPathway_bins= GetSecondTrkVarVector(kPathway);




////////////////
//muon Varibles///
////////////////
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
MnvH2D *h_2d_2ndtrkangle_2ndTrkE_dimuon_TRUE         =    new MnvH2D("h_2d_2ndtrkangle_2ndTrkE_dimuon_TRUE", "h_2d_2ndtrkangle_2ndTrkE_dimuon_TRUE", Vertex_secondTrkTheta_bins.size()-1, Vertex_secondTrkTheta_bins.data(),Vertex_secondTrkEbins.size()-1, Vertex_secondTrkEbins.data()  );
////////////////
//Vertex Hist///
////////////////

PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_PT_PZ_TRUE("h_Muon_PT_PZ_TRUE", "h_Muon_PT_PZ_TRUE", PTbin_vector , Pzbin_vector, error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_PT_theta_TRUE("h_Muon_PT_theta_TRUE", "h_Muon_PT_theta_TRUE", PTbin_vector , MuonThetabin_vector, error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_PZ_theta_TRUE("h_Muon_PZ_theta_TRUE", "h_Muon_PZ_theta_TRUE", Pzbin_vector , MuonThetabin_vector, error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_E_theta_TRUE("h_Muon_E_theta", "h_Muon_E_theta",  Ebin_vector , MuonThetabin_vector, error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_E_PZ_TRUE("h_Muon_E_PZ_TRUE", "h_Muon_E_PZ_TRUE",  Ebin_vector ,  Pzbin_vector, error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_Muon_E_PT_TRUE("h_Muon_E_PT_TRUE", "h_Muon_E_PT_TRUE",  Ebin_vector , PTbin_vector, error_bands);
PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_cryoVertex_Z_R_TRUE("h_cryoVertex_Z_R_TRUE", "h_cryoVertex_Z_R_TRUE", Vertex_Zbins, Vertex_Rbins , error_bands);

PlotUtils::Hist2DWrapper<HeliumCVUniverse> h_2ndtrkangle_2ndTrkE_TRUE("h_2ndtrkangle_2ndTrkE_TRUE", "h_2ndtrkangle_2ndTrkE_TRUE", Vertex_secondTrkEbins, Vertex_secondTrkEbins , error_bands);


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
  EventCount_Truth EventCounter_weight;
  double wgt0,wgt1,wgt2,wgt3,wgt4,wgt_total;

  /*std::cout << "size of vector " << kTRUTHCutsVector.size()<<std::endl;
  for (auto cut : kTRUTHCutsVector){
  std::cout<<" count= "<<cut<<std::endl;

  }
*/

  ProcInfo_t procInfo;
  gSystem->GetProcInfo(&procInfo);

  std::cout << "Memory/time used so Far: " << procInfo.fMemResident/1000<< " MB" <<" time = "<<  procInfo.fCpuSys <<  " Sec"<<"\n";

  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"MC LOOP  "<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

  std::string sysmatics_status;
  if(m_RunCodeWithSystematics==true){sysmatics_status= "Systematics On";}
  else if (m_RunCodeWithSystematics==false){sysmatics_status= "Systematics Off";}
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;
  std::cout<<"~~~~~~~~~  "<< sysmatics_status <<" ~~~~~~~~~ "<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;


  for(int i=0; i<chw_MC->GetEntries(); ++i){
    if(i%5000==0) std::cout << (i/1000) << " k " << std::endl;





    //=========================================
    // For every systematic, loop over the universes, and fill the
    // appropriate histogram in the MnvH1D
    //=========================================


    for (auto band : error_bands){
        //std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
      std::vector<HeliumCVUniverse*> error_band_universes = band.second;
      for (auto universe : error_band_universes){

        // Tell the Event which entry in the TChain it's looking at
        universe->SetEntry(i);
        ///////////////////////////////////////////
        ////
        ////  FILL CV
        ////
        ///
        ///////////////////////////////////////////


        wgt0 = 1.0;
        wgt1 = universe->GetWeight(kweightFlux );
        wgt2 = universe->GetWeight(kweightGenie);
        wgt3 = universe->GetWeight(kweight2p2ptune );
        wgt4 = universe->GetWeight(kweightRPA);
        wgt_total = universe->GetWeight(kWeightVector);
        //std::cout<< "MINSO weight = "<< wgt2<<std::endl;

        //double wgt6 = universe->GetWeight(kweightLowQ2Pi);
        EventCounter_TRUTH(*universe, kTRUTHCutsVector, EventCounter_weight_0, wgt0);
        EventCounter_TRUTH(*universe, kTRUTHCutsVector, EventCounter_weight_1, wgt1);
        EventCounter_TRUTH(*universe, kTRUTHCutsVector, EventCounter_weight_2, wgt2);
        EventCounter_TRUTH(*universe, kTRUTHCutsVector, EventCounter_weight_3, wgt3);
        EventCounter_TRUTH(*universe, kTRUTHCutsVector, EventCounter_weight_4, wgt4);
        EventCounter_TRUTH(*universe, kTRUTHCutsVector, EventCounter_weight_4, wgt_total );

        if( universe->ShortName() == "cv"){
            if(PassesCutsTRUTH(*universe, kTRUTHCutsVector)){

              std::vector <int> PDG_trklist = universe->GETvector_PDG_FS_particles();
              std::vector  <double> Angle_trklist = universe->GETvector_theta_wrtb_FS_particles();
              std::vector <double> Energy_trklist   = universe->GETvector_KE_mc_FS_particles_GeV(pdg_DATABASEobject);

              if(PDG_trklist.size()==1){std::cout<<"ERROR"<<std::endl;assert(false);}
              int secondTrk = 999;
              //if(PDG_trklist.size()==0)continue;
              secondTrk = universe->Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_lessthanAngle(PDG_trklist, Energy_trklist, Angle_trklist);
              if(secondTrk == 0 || secondTrk == -999) continue; // remove 2nd trks that are leading muons
              int pdg_2ndTrk = PDG_trklist.at(secondTrk);
              double SecTrkTrueEnergy = Energy_trklist.at(secondTrk);
              double SecTrkTrueAngle = Angle_trklist.at(secondTrk);
              Particle_type Particle_type_Event = GetParticlegroup_type(pdg_2ndTrk);

              Interaction_type Interaction_type_Event =  universe->Get_InteractionStackType();
              Material_type Material_type_Event = universe->Get_MaterialStackType();
              double mvn1wgt = universe->GetWeight(kWeightVector);

              h_2d_PZ_PT_TRUE->Fill(universe->GetTRUE_PZmu(),universe->GetTRUE_PTmu(),mvn1wgt);
              h_2d_E_PZ_TRUE->Fill(universe->GetTRUE_Emu(),universe->GetTRUE_PZmu(),mvn1wgt);
              h_2d_Theta_PZ_TRUE->Fill(universe->GetTRUE_muANGLE_WRTB_DEG(),universe->GetTRUE_PZmu(),mvn1wgt);
              h_2d_E_PT_TRUE->Fill(universe->GetTRUE_Emu(),universe->GetTRUE_PTmu(),mvn1wgt);
              h_2d_Theta_PT_TRUE->Fill(universe->GetTRUE_muANGLE_WRTB_DEG(),universe->GetTRUE_PTmu(),mvn1wgt);
              h_2d_Theta_PZ_TRUE->Fill(universe->GetTRUE_muANGLE_WRTB_DEG(),universe->GetTRUE_PZmu(),mvn1wgt);
              h_2d_Theta_2ndTrkE_TRUE->Fill(universe->GetTRUE_muANGLE_WRTB_DEG(),SecTrkTrueEnergy,mvn1wgt);
              h_2d_muonE_2ndTrkE_TRUE->Fill(universe->GetTRUE_Emu(),SecTrkTrueEnergy,mvn1wgt);
              h_2d_muonPT_2ndTrkE_TRUE->Fill(universe->GetTRUE_PTmu(),SecTrkTrueEnergy,mvn1wgt);
              h_2d_muonPZ_2ndTrkE_TRUE->Fill(universe->GetTRUE_PZmu(),SecTrkTrueEnergy,mvn1wgt);
              h_2d_Theta_2ndTrKangle_TRUE->Fill(universe->GetTRUE_muANGLE_WRTB_DEG(),SecTrkTrueEnergy,mvn1wgt);
              h_2d_muonE_2ndTrkangle_TRUE->Fill(universe->GetTRUE_Emu(),SecTrkTrueAngle,mvn1wgt);
              h_2d_muonPT_2ndTrkangle_TRUE->Fill(universe->GetTRUE_PTmu(),SecTrkTrueAngle,mvn1wgt);
              h_2d_muonPZ_2ndTrkangle_TRUE->Fill(universe->GetTRUE_PZmu(),SecTrkTrueAngle,mvn1wgt);
              h_2d_2ndtrkangle_2ndTrkE_TRUE->Fill(SecTrkTrueAngle,SecTrkTrueEnergy,mvn1wgt);


              if(Particle_type_Event==kSecondary_particle_vector[0]){
                h_2d_2ndtrkangle_2ndTrkE_Proton_TRUE->Fill(SecTrkTrueAngle,SecTrkTrueEnergy,mvn1wgt);
              }
              if(Particle_type_Event==kSecondary_particle_vector[1]){
                h_2d_2ndtrkangle_2ndTrkE_Pion_TRUE ->Fill(SecTrkTrueAngle,SecTrkTrueEnergy,mvn1wgt);
              }
              if(Particle_type_Event==kSecondary_particle_vector[2]){
                h_2d_2ndtrkangle_2ndTrkE_dimuon_TRUE->Fill(SecTrkTrueAngle,SecTrkTrueEnergy,mvn1wgt);
              }

            }//end of Truth Cuts

        }// End of CV
        ///////////////////////////////////////////
        ////
        ////  END OF CV
        ////
        ////
        ///////////////////////////////////////////
        //=========================================
        // CUTS in each universe
        //=========================================
        ////////////
        ///TRUTH
        ///////////

        if(PassesCutsTRUTH(*universe, kTRUTHCutsVector)){

          std::vector <int> PDG_trklist = universe->GETvector_PDG_FS_particles();
          std::vector <double> Angle_trklist = universe->GETvector_theta_wrtb_FS_particles();
          std::vector <double> Energy_trklist   = universe->GETvector_KE_mc_FS_particles_GeV(pdg_DATABASEobject);

          int secondTrk = 999;
          if(PDG_trklist.size()==0)continue;
          secondTrk = universe->Returnindex_True_2ndTk_NO_NeutralParticles_GreatestKE_lessthanAngle(PDG_trklist, Energy_trklist, Angle_trklist ) ;

          int true_track_size = PDG_trklist.size();
          int pdg_2ndTrk = PDG_trklist.at(secondTrk);
          double SecTrkTrueEnergy = Energy_trklist.at(secondTrk);
          double SecTrkTrueAngle = Angle_trklist.at(secondTrk);
        //  Particle_type Particle_type_Event = GetParticlegroup_type(pdg_2ndTrk);
        //  Interaction_type Interaction_type_Event =  universe->Get_InteractionStackType();
        //  Material_type Material_type_Event = universe->Get_MaterialStackType();

         double Theta = universe->GetTRUE_muANGLE_WRTB_rad();
         double Pmu = universe->GetTRUE_Pmu();
         double Emu = universe->GetTRUE_Emu();
         double mvn1wgt = universe->GetWeight(kWeightVector);
         double theta_degs = Theta* TMath::RadToDeg();
          h_Muon_PT_PZ_TRUE.univHist(universe)->Fill(Pmu*std::sin(Theta), Pmu*std::cos(Theta), mvn1wgt);
          h_Muon_PT_theta_TRUE.univHist(universe)->Fill(Pmu*std::sin(Theta), theta_degs,mvn1wgt);
          h_Muon_PZ_theta_TRUE.univHist(universe)->Fill( Pmu*std::cos(Theta), theta_degs,mvn1wgt);
          h_Muon_E_theta_TRUE.univHist(universe)->Fill(Emu,theta_degs, mvn1wgt);
          h_Muon_E_PZ_TRUE.univHist(universe)->Fill(Emu, Pmu*std::cos(Theta), mvn1wgt);
          h_Muon_E_PT_TRUE.univHist(universe)->Fill(Emu, Pmu*std::sin(Theta), mvn1wgt);
          h_cryoVertex_Z_R_TRUE.univHist(universe)->Fill(universe->GetVertex_z(),universe->GetVertex_r() , mvn1wgt);
          h_2ndtrkangle_2ndTrkE_TRUE.univHist(universe)->Fill( SecTrkTrueAngle,SecTrkTrueEnergy , mvn1wgt);

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
//EventCountMap[kPlayListVector[2]] = EventCounter_dataFull;
//EventCountMap[kPlayListVector[3]] = EventCounter_dataEmpty;
//////////////////////////////////////////////////////////////////////////
//End of Empty data
//////////////////////////////////////////////////////////////////////////


double countdata= 0.0;
double countmc= 0.0;

    //////////////////////////////////
    //MuonEnergymaterial.Write();
    //outFile.cd();
    //outFile.Write();
    //LOGFILE.Close();
    //======================================
    //

    h_Muon_PT_PZ_TRUE.SyncCVHistos();
    h_Muon_PT_theta_TRUE.SyncCVHistos();
    h_Muon_PZ_theta_TRUE.SyncCVHistos();
    h_Muon_E_theta_TRUE.SyncCVHistos();
    h_Muon_E_PZ_TRUE.SyncCVHistos();
    h_Muon_E_PT_TRUE.SyncCVHistos();
    h_cryoVertex_Z_R_TRUE.SyncCVHistos();

  //=========================================
  // Plot stuff
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
  //PrintCutstoScreen( kTRUTHCutsVector , EventCounter_RECO, c, mcscale );
  char EventRateName[1024];
  sprintf(EventRateName, "TRUE_Weight_ALL_Weights_TRUEMC_%s",c);
  //MakeEfficiencyCutCVS(EventCounter_EFF_TRUTH, EventCounter_EFF , kTRUTHCutsVector,c,mcPOT);
  Make_cvsOfCutsRateTRUE( kTRUTHCutsVector , EventCounter_TRUTH_total, EventRateName, 1.0, 1.0);
  sprintf(EventRateName, "TRUE_Weight_0_noWeight_TRUEMC_%s",c);
   Make_cvsOfCutsRateTRUE( kTRUTHCutsVector , EventCounter_weight_0, EventRateName  ,1.0 ,1.0 );
   sprintf(EventRateName, "TRUE_Weight_1_FLUX_MC_%s",c);
   Make_cvsOfCutsRateTRUE( kTRUTHCutsVector , EventCounter_weight_1, EventRateName  ,1.0 ,1.0);
   sprintf(EventRateName, "TRUE_Weight_2_GeniePion_TRUEMC_%s",c);
   Make_cvsOfCutsRateTRUE( kTRUTHCutsVector , EventCounter_weight_2, EventRateName  ,1.0 ,1.0);
   sprintf(EventRateName, "TRUE_Weight_3_2p2h_TRUEMC_%s",c);
   Make_cvsOfCutsRateTRUE( kTRUTHCutsVector , EventCounter_weight_3, EventRateName  ,1.0 ,1.0);
   sprintf(EventRateName, "TRUE_Weight_4_RPA_TRUEMC_%s",c);
   Make_cvsOfCutsRateTRUE( kTRUTHCutsVector , EventCounter_weight_4, EventRateName  ,1.0 ,1.0);



  //outFileName = "Histograms_test.root";
  //auto outFile = TFile::Open(outFileName);

  std::string systematics_status;
  if(m_RunCodeWithSystematics==true){sysmatics_status= "All_SysErrorsOn";}
  else if (m_RunCodeWithSystematics==false){sysmatics_status= "StatsONLYErrors";}
  char systematics_status_char[sysmatics_status.length() + 1];
    strcpy(systematics_status_char, systematics_status.c_str());

  sprintf(outFileName, "%s/Histograms_%s_%s.root",rootpathway,c,d);

  std::cout << "Writing output file to: " <<outFileName << std::endl;

  //TFile outFile(outFileName, "RECREATE");

  //TFile *outFile(outFileName, "RECREATE");
  TFile *outFile = new TFile(outFileName,"RECREATE");
  TChain POT_branch("Meta");
  POT_branch.Add(RootName.c_str());
  //TTree *oldtree = (TTree*)file->Get("Meta");
  TTree *clone = POT_branch.CloneTree();
  clone->Write();

////////////////////////////////////////////////

h_Muon_PT_PZ_TRUE.hist->Write();
h_Muon_PT_theta_TRUE.hist->Write();
h_Muon_PZ_theta_TRUE.hist->Write();
h_Muon_E_theta_TRUE.hist->Write();
h_Muon_E_PZ_TRUE.hist->Write();
h_Muon_E_PT_TRUE.hist->Write();
h_cryoVertex_Z_R_TRUE.hist->Write();

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
h_2d_Theta_2ndTrKangle_TRUE->Write();
h_2d_muonE_2ndTrkangle_TRUE->Write();
h_2d_muonPT_2ndTrkangle_TRUE->Write();
h_2d_muonPZ_2ndTrkangle_TRUE->Write();

h_2d_2ndtrkangle_2ndTrkE_TRUE->Write();
h_2d_2ndtrkangle_2ndTrkE_Proton_TRUE->Write();
h_2d_2ndtrkangle_2ndTrkE_Pion_TRUE->Write();
h_2d_2ndtrkangle_2ndTrkE_dimuon_TRUE->Write();

outFile->Close();


  for(auto band : error_bands){
    std::vector<HeliumCVUniverse*> band_universes = band.second;
    for(unsigned int i_universe = 0; i_universe < band_universes.size(); ++i_universe){ delete band_universes[i_universe];}
  }

  std::cout << "Success in TRUTH LOOP - Gotcha !?!?" << std::endl;



TCanvas *can = new TCanvas("can", "can",1800,1600);
can -> Print("Test.pdf");


}//END of Event Loop

//=========================================
//=========================================
//////////////////////////////////////////////////////////////
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

  Playlist.push_back(kME1G);
  //Playlist.push_back(kME1P);
  //Playlist.push_back(kME1D);
  ///Playlist.push_back(kME1C);
  //Playlist.push_back(kME1A);//
  //Playlist.push_back(kME1F);//
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


  bool Run_EventLoopOnGrid = false;
  if(Run_EventLoopOnGrid==true){std::cout << "This Eventloop is step up to run on the Grid" << std::endl;}
  else{std::cout << "This Eventloop is step up to run locally" << std::endl;}



  runEventLoop(Playlist_to_run, m_debugOn,  Run_EventLoopOnGrid);
  return 0;
}
//#endif
