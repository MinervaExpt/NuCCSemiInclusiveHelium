//File: Helium2D_runEventLoopForDATA.cxx
//Brief: Given ntuple files from HeAnaTupleTool.cpp , extracts 2D Data EventSelction for Helium Nu interactions
//Writes a .root file Event Selection histograms.
//
//Usage: 2D DATA 2DEventSelection  =
//
//Author: Christian Nguyen  christian2nguyen@ufl.edu
#include "Helium2D_runEventLoopForDATA.h"

std::string OUTputRoot_pathway = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles";
//=====================================================
// Functions
//=====================================================
std::vector<ECuts> GetRECOCutsVector();

std::vector<MuonVar> GetMUONVaribles();
std::vector<SecondTrkVar> GetPlayListSecondTrkVector();
std::vector<CryoVertex> GetCryoVertexVaribles();


// Get container of systematics

//======================================================================
// Main
//======================================================================

void runEventLoop(bool &m_debugOn, ME_helium_Playlists &PlayList_iterator, bool &Run_EventLoopOnGid) {
  // Make a chain of events
  loadLibs();
  TH1::AddDirectory(false);

  bool isNOT_mc= false;
  bool is_counter = true;

  const std::vector< ECuts > kCutsVector = GetRECOCutsVector();

  const std::vector<MuonVar> kMuonVaribles_vector = GetMUONVaribles();
  const std::vector<SecondTrkVar> kSecTrkVaribles_vector = GetPlayListSecondTrkVector();

  const std::vector<CryoVertex> kCryoVertexVaribles_vector = GetCryoVertexVaribles();
  EventPlaylist_RecoCount EventCountMap;


MinervaUniverse::SetNuEConstraint(false);
MinervaUniverse::SetDeuteriumGeniePiTune(false);
std::string playlist = GetPlaylist(PlayList_iterator);
MinervaUniverse::SetPlaylist(playlist);
MinervaUniverse::SetTruth(false);


//======================================================================
////////////////////ADDING TO CHAIN wrapper ///////////////////////////
//======================================================================

//======================================================================
///////////////////Making/adding to error bands  ///////////////////////////
//======================================================================

POTCounter pot_counter;


  auto mcscale = 1.0; //Data_POT_full/ MC_POT_full;


//std::cout << "MC_POT_full = "<< MC_POT_full<< " MC_POT_empty = "<< MC_POT_empty << "  Data_POT_full = " << Data_POT_full << "  Data_POT_empty = " << Data_POT_empty<< std::endl;

  // Make a map of systematic universes
//  std::map< std::string, std::vector<HeliumCVUniverse*> > DATAerror_bands = GetErrorBands(chw_Data);
std::vector<double> Ebin_vector = GetBinMuonVector(kE_2D);
//std::vector<double> Pzbin_vector= GetBinMuonVector(kP_Z);
std::vector<double> PTbin_vector= GetBinMuonVector(kP_T_2D);
std::vector<double> Pzbin_vector = GetBinMuonVector(kP_Z_2D);

std::vector<double> Pzbin_vector_finebinning = GetBinMuonVector(kP_Z);
std::vector<double> PTbin_vector_finebinning = GetBinMuonVector(kP_T);
  //0.0, 0.25, 0.325, 0.4, 0.475, 0.55, 0.7, 0.85, 2.5

std::vector<double> MuonThetabin_vector= GetBinMuonVector(kAngleWRTB_2D);

std::vector<double> Vertex_Xbin_vector = GetBinvertexVector(kX_2D);
std::vector<double> Vertex_Ybin_vector = GetBinvertexVector(kY_2D);
std::vector<double> Vertex_Zbin_vector = GetBinvertexVector(kZ_2D);
std::vector<double> Vertex_Rbin_vector = GetBinvertexVector(kR_2D);
//std::vector<double> Zbins_corse{1450, 1750.00, 2050.00, 2250, 2450, 2650, 2850, 3000, 3200,  3400, 3650, 3900, 4200, 4350 };
//1400 , 1600 , 1800 , 2000, 2200,2600,3000,3400,3600,3800,4000,4200,4400
std::vector<double> Rbins_corse= GetBinvertexVector(kR_2D);
std::vector<double> VertexXYbins_coarse= GetBinvertexVector(kY_2D);
std::vector<double> bigAngle_bins{0.0, 15.0, 30.0, 45.0, 60.0};
std::vector<double> Muon_curvatureSig_vector= GetBinMuonVector(kcurvatureSig_2D);
std::vector<double> Vertex_DOCAbin_vector= GetBinMuonVector(kDOCA_muon_2D);
std::vector<double> Vertex_secondTrkEbin_vector= GetSecondTrkVarVector(ksecE_2D);
std::vector<double> Vertex_secondTrkTheta_vector= GetSecondTrkVarVector(ksecTheta_2D);
std::vector<double> SecTrk_DOCA_vector= GetSecondTrkVarVector(kDOCA_2D);
std::vector<double> SecTrk_Pathway_vector= GetSecondTrkVarVector(kPathway);
std::vector<double> SecTrk_Tracklength_vector= GetSecondTrkVarVector(ksec_tracklength_minerva_2D);
std::vector<double> Vertex_ChiSqFit_vector= GetBinvertexVector(kfitConverge_2D);
std::vector<double> BinVector_MatchToveto= GetBinMuonVector(kMuonMatchtoVeto);
std::vector<double> Minos_R_vector= GetBinMuonVector(kminos_R);
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

std::vector<double> SecTRK_StartNode_X_vector= GetSecondTrkVarVector(kFirstsecTrk_Xnode);
std::vector<double> SecTRK_StartNode_Y_vector= GetSecondTrkVarVector(kFirstsecTrk_Ynode);
std::vector<double> SecTRK_StartNode_Z_vector= GetSecondTrkVarVector(kFirstsecTrk_Znode);

std::vector<double> SecTRK_LastNode_X_vector= GetSecondTrkVarVector(kLastsecTrk_Xnode);
std::vector<double> SecTRK_LastNode_Y_vector= GetSecondTrkVarVector(kLastsecTrk_Ynode);
std::vector<double> SecTRK_LastNode_Z_vector= GetSecondTrkVarVector(kLastsecTrk_Znode);
std::vector<double> TrackSize_vector= GetBinMuonVector(ktracksize);




std::vector<double> MuonCharge_vector= GetBinMuonVector(kCharge);
std::vector<double> MuonMatchtoMinos_vector= GetBinMuonVector(kMuonMatchtoMinos);
std::vector<double> MuonMatchtoVeto_vector= GetBinMuonVector(kMuonMatchtoVeto);
std::vector<double> distance_edge_vector = GetBinvertexVector(kdistance_edge_2D);
  // Use the vector of systematic universes to make your MnvH1D

////////////////
//muon Energy///
////////////////



MnvH2D *h_Data_Muon_PZ_PT    =    new MnvH2D("h_Data_Muon_PZ_PT", "h_Data_Muon_PZ_PT", Pzbin_vector.size()-1, Pzbin_vector.data(), PTbin_vector.size()-1 ,PTbin_vector.data() );
MnvH2D *h_Data_Muon_PZ_PT_finebinning    =    new MnvH2D("h_Data_Muon_PZ_PT_finebinning", "h_Data_Muon_PZ_PT_finebinning", Pzbin_vector_finebinning.size()-1, Pzbin_vector_finebinning.data(), PTbin_vector_finebinning.size()-1 ,PTbin_vector_finebinning.data() );
MnvH2D *h_Data_Muon_PT_theta =    new MnvH2D("h_Data_Muon_PT_theta", "h_Data_Muon_PT_theta", PTbin_vector.size()-1 ,PTbin_vector.data(), MuonThetabin_vector.size()-1,MuonThetabin_vector.data());
MnvH2D *h_Data_Muon_PZ_theta =    new MnvH2D("h_Data_Muon_PZ_theta", "h_Data_Muon_PZ_theta", Pzbin_vector.size()-1 ,Pzbin_vector.data(), MuonThetabin_vector.size()-1,MuonThetabin_vector.data());
MnvH2D *h_Data_Muon_E_theta  =    new MnvH2D("h_Data_Muon_E_theta", "h_Data_Muon_E_theta",  Ebin_vector.size()-1 , Ebin_vector.data(), MuonThetabin_vector.size()-1,MuonThetabin_vector.data());
MnvH2D *h_Data_Muon_E_PZ     =    new MnvH2D("h_Data_Muon_E_PZ", "h_Data_Muon_E_PZ",  Ebin_vector.size()-1 , Ebin_vector.data(),  Pzbin_vector.size()-1, Pzbin_vector.data() );
MnvH2D *h_Data_Muon_E_PT     =    new MnvH2D("h_Data_Muon_E_PT", "h_Data_Muon_E_PT",  Ebin_vector.size()-1 , Ebin_vector.data(), PTbin_vector.size()-1, PTbin_vector.data() );

MnvH2D *h_Data_cryoVertex_Z_R      =    new MnvH2D("h_Data_cryoVertex_Z_R ", "h_Data_cryoVertex_Z_R ", Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data(), Vertex_Rbin_vector.size()-1 , Vertex_Rbin_vector.data() );
MnvH2D *h_Data_cryoVertex_Z_X      =    new MnvH2D("h_Data_cryoVertex_Z_X ", "h_Data_cryoVertex_Z_X ", Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data(), Vertex_Xbin_vector.size()-1 , Vertex_Xbin_vector.data() );
MnvH2D *h_Data_cryoVertex_Z_Y      =    new MnvH2D("h_Data_cryoVertex_Z_Y ", "h_Data_cryoVertex_Z_Y ", Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data(), Vertex_Ybin_vector.size()-1 , Vertex_Ybin_vector.data() );
MnvH2D *h_Data_cryoVertex_X_Y      =    new MnvH2D("h_Data_cryoVertex_X_Y ", "h_Data_cryoVertex_X_Y ", Vertex_Xbin_vector.size()-1, Vertex_Xbin_vector.data(), Vertex_Ybin_vector.size()-1 , Vertex_Ybin_vector.data() );
MnvH2D *h_Data_Muon_PT_cryoVertex_R =    new MnvH2D("h_Data_Muon_PT_cryoVertex_R", "h_Data_Muon_PT_cryoVertex_R", PTbin_vector.size()-1 ,PTbin_vector.data(), Vertex_Rbin_vector.size()-1,Vertex_Rbin_vector.data());


MnvH2D *h_Data_cryoVertex_Z_OpenAngle      =    new MnvH2D("h_Data_cryoVertex_Z_OpenAngle ", "h_Data_cryoVertex_Z_OpenAngle ", Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data(), bigAngle_bins.size()-1 , bigAngle_bins.data() );
MnvH2D *h_Data_cryoVertex_R_OpenAngle      =    new MnvH2D("h_Data_cryoVertex_R_OpenAngle ", "h_Data_cryoVertex_R_OpenAngle ", Vertex_Rbin_vector.size()-1, Vertex_Rbin_vector.data(), bigAngle_bins.size()-1 , bigAngle_bins.data() );
MnvH2D *h_Data_cryoVertex_Y_OpenAngle      =    new MnvH2D("h_Data_cryoVertex_Y_OpenAngle ", "h_Data_cryoVertex_Y_OpenAngle ", Vertex_Ybin_vector.size()-1, Vertex_Ybin_vector.data(), bigAngle_bins.size()-1 , bigAngle_bins.data() );
MnvH2D *h_Data_cryoVertex_X_OpenAngle      =    new MnvH2D("h_Data_cryoVertex_X_OpenAngle ", "h_Data_cryoVertex_X_OpenAngle ", Vertex_Xbin_vector.size()-1, Vertex_Xbin_vector.data(), bigAngle_bins.size()-1 , bigAngle_bins.data() );


MnvH2D *h_Data_Muontheta_OpenAngle      =    new MnvH2D("h_Data_Muontheta_OpenAngle ", "h_Data_Muontheta_OpenAngle ", MuonThetabin_vector.size()-1, MuonThetabin_vector.data(), bigAngle_bins.size()-1 , bigAngle_bins.data() );


MnvH2D *h_Data_Vertex_Z_ChiSq      =    new MnvH2D("h_Data_Vertex_Z_ChiSq", "h_Data_Vertex_Z_ChiSq", Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data(), Vertex_ChiSqFit_vector.size()-1 , Vertex_ChiSqFit_vector.data() );


MnvH2D *h_Data_Vertex_Z_MuonTheta = new MnvH2D("h_Data_Vertex_Z_MuonTheta", "h_Data_Vertex_Z_MuonTheta", Vertex_Zbin_vector.size()-1,Vertex_Zbin_vector.data(), MuonThetabin_vector.size()-1, MuonThetabin_vector.data() );


MnvH2D *h_Data_Muon_PT_CuratureSig = new MnvH2D("h_Data_Muon_PT_CuratureSig", "h_Data_Muon_PT_CuratureSig",           PTbin_vector.size()-1 ,       PTbin_vector.data(), Muon_curvatureSig_vector.size()-1, Muon_curvatureSig_vector.data());
MnvH2D *h_Data_Muon_PZ_CuratureSig = new MnvH2D("h_Data_Muon_PZ_CuratureSig", "h_Data_Muon_PZ_CuratureSig",           Pzbin_vector.size()-1,        Pzbin_vector.data(), Muon_curvatureSig_vector.size()-1, Muon_curvatureSig_vector.data());
MnvH2D *h_Data_Muon_E_CuratureSig = new MnvH2D("h_Data_Muon_E_CuratureSig", "h_Data_Muon_E_CuratureSig",              Ebin_vector.size()-1,         Ebin_vector.data(),  Muon_curvatureSig_vector.size()-1, Muon_curvatureSig_vector.data());
MnvH2D *h_Data_Muon_theta_CuratureSig = new MnvH2D("h_Data_Muon_theta_CuratureSig", "h_Data_Muon_theta_CuratureSig",  MuonThetabin_vector.size()-1, MuonThetabin_vector.data(), Muon_curvatureSig_vector.size()-1, Muon_curvatureSig_vector.data());

MnvH2D *h_Data_secTrkE_secTrkTheta =        new MnvH2D("h_Data_secTrkE_secTrkTheta",        "h_Data_secTrkE_secTrkTheta",        Vertex_secondTrkEbin_vector.size()-1, Vertex_secondTrkEbin_vector.data(),  Vertex_secondTrkTheta_vector.size()-1,  Vertex_secondTrkTheta_vector.data());
MnvH2D *h_Data_Vertex_Z_secTrkTheta = new MnvH2D("h_Data_Vertex_Z_secTrkTheta", "h_Data_Vertex_Z_secTrkTheta", Vertex_Zbin_vector.size()-1,          Vertex_Zbin_vector.data(),           Vertex_secondTrkTheta_vector.size()-1, Vertex_secondTrkTheta_vector .data());
MnvH2D *h_Data_Vertex_Z_secTrkE =     new MnvH2D("h_Data_Vertex_Z_secTrkE",     "h_Data_Vertex_Z_secTrkE",     Vertex_Zbin_vector.size()-1,          Vertex_Zbin_vector.data(),           Vertex_secondTrkEbin_vector.size()-1,  Vertex_secondTrkEbin_vector.data());
MnvH2D *h_Data_Vertex_Z_trkLength =   new MnvH2D("h_Data_Vertex_Z_trkLength",   "h_Data_Vertex_Z_trkLength",   Vertex_Zbin_vector.size()-1,          Vertex_Zbin_vector.data(),           SecTrk_Tracklength_vector.size()-1,    SecTrk_Tracklength_vector.data());


MnvH2D *h_Data_secTrkTheta_TrkLength = new MnvH2D("h_Data_secTrkTheta_TrkLength", "h_Data_secTrkTheta_TrkLength", Vertex_secondTrkTheta_vector.size()-1,Vertex_secondTrkTheta_vector.data(), SecTrk_Tracklength_vector.size()-1 , SecTrk_Tracklength_vector.data());
MnvH2D *h_Data_secTrkE_TrkLength = new MnvH2D("h_Data_secTrkE_TrkLength", "h_Data_secTrkE_TrkLength", Vertex_secondTrkEbin_vector.size()-1,Vertex_secondTrkEbin_vector.data(), SecTrk_Tracklength_vector.size()-1 , SecTrk_Tracklength_vector.data());


MnvH2D *h_Data_secTrkTheta_secTrkDoca = new MnvH2D("h_Data_secTrkTheta_secTrkDoca", "h_Data_secTrkTheta_secTrkDoca", Vertex_secondTrkTheta_vector.size()-1,Vertex_secondTrkTheta_vector.data(), SecTrk_DOCA_vector.size()-1, SecTrk_DOCA_vector.data());
MnvH2D *h_Data_secTrkE_secTrkDoca = new MnvH2D("h_Data_secTrkE_secTrkDoca", "h_Data_secTrkE_secTrkDoca", Vertex_secondTrkEbin_vector.size()-1,Vertex_secondTrkEbin_vector.data() , SecTrk_DOCA_vector.size()-1, SecTrk_DOCA_vector.data() );
MnvH2D *h_Data_MuonDoca_secTrkDoca = new MnvH2D("h_Data_MuonDoca_secTrkDoca", "h_Data_MuonDoca_secTrkDoca", Vertex_DOCAbin_vector.size()-1,Vertex_DOCAbin_vector.data() , SecTrk_DOCA_vector.size()-1, SecTrk_DOCA_vector.data() );


MnvH2D * h_Data_Vertex_Z_DistanceNearEdge= new MnvH2D("h_Data_Vertex_Z_DistanceNearEdge", "h_Data_Vertex_Z_DistanceNearEdge", Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data(), distance_edge_vector.size()-1 ,distance_edge_vector.data());
MnvH2D * h_Data_Vertex_R_DistanceNearEdge= new MnvH2D("h_Data_Vertex_R_DistanceNearEdge", "h_Data_Vertex_R_DistanceNearEdge", Vertex_Rbin_vector.size()-1, Vertex_Rbin_vector.data(), distance_edge_vector.size()-1 ,distance_edge_vector.data());
MnvH2D * h_Data_Vertex_X_DistanceNearEdge= new MnvH2D("h_Data_Vertex_X_DistanceNearEdge", "h_Data_Vertex_X_DistanceNearEdge", VertexXYbins_coarse.size()-1,VertexXYbins_coarse.data(), distance_edge_vector.size()-1 ,distance_edge_vector.data());
MnvH2D * h_Data_Vertex_Y_DistanceNearEdge= new MnvH2D("h_Data_Vertex_Y_DistanceNearEdge", "h_Data_Vertex_Y_DistanceNearEdge", VertexXYbins_coarse.size()-1,VertexXYbins_coarse.data(), distance_edge_vector.size()-1 ,distance_edge_vector.data());


MnvH2D *h_Data_Muon_PT_NTracks = new MnvH2D("h_Data_Muon_PT_NTracks", "h_Data_Muon_PT_NTracks", PTbin_vector.size()-1, PTbin_vector.data(), TrackSize_vector.size()-1, TrackSize_vector.data());


  EventCount_RECO EventCounter_data;


  std::cout << "size of vector " << kCutsVector.size()<<std::endl;
  for (auto cut : kCutsVector){
  std::cout<<" count= "<<cut<<std::endl;
  EventCounter_data[cut]=0.0;

  //std::cout << GetCutName( cut) << "  " << EventCounter_dataFull[cut] <<" " <<EventCounter_MCFull[cut]<<std::endl;

  }


  ProcInfo_t procInfo;
  gSystem->GetProcInfo(&procInfo);
  std::cout << "Mem0: " << procInfo.fMemResident << "\n";


  HeliumPlayListInfo Playlist_Info(playlist);
  std::cout<<"Working with Playlist =  "<<  Playlist_Info.GetPlaylistname()<<std::endl;



  gSystem->GetProcInfo(&procInfo);
  std::cout << "Mem1: " << procInfo.fMemResident << "\n";

  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"Data LOOP  "<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;


//////////////////////////////////////////////////////////////////////////
// Data Loop ME_playlist_1A_BranchesADDED
//////////////////////////////////////////////////////////////////////////
gSystem->GetProcInfo(&procInfo);
std::cout<<"On Playlist: "<<Playlist_Info.GetPlaylistname() << "Mem2: " << procInfo.fMemResident << "\n";
//auto Playlist_txtFILEPath = GetPlaylist_txtFILE_path("1A_BranchesADDED",  isNOT_mc );
auto Playlist_txtFILEPath = GetPlaylist_txtFILE_path(PlayList_iterator, isNOT_mc );

std::cout<<"Pathway of Root files = "<< Playlist_txtFILEPath<<std::endl;
//PlotUtils::ChainWrapper* chw_Data  = makeChainWrapperPtr("../playlists/Data_Playlist/ME_1A_DATA.txt", "Muon");
//PlotUtils::ChainWrapper* chw_Data  = makeChainWrapperPtr("../playlists/Data_Playlist/ME_1P_DATA.txt", "Muon");
PlotUtils::ChainWrapper* chw_Data  = makeChainWrapperPtr(Playlist_txtFILEPath.c_str(), "HeAnaTupleTool");
//PlotUtils::ChainWrapper* datachainPOT = makeChainWrapperPtr(Playlist_txtFILEPath.c_str(), "Meta");
//std::map< std::string, std::vector<HeliumCVUniverse*> > data_error_bands = GetErrorBands(chw_Data);
auto dataPOT = 1.0;//GetPOT(datachainPOT);
//std::cout << "POT of MC = "<< dataPOT<<std::endl;
HeliumCVUniverse* dataEvt = new HeliumCVUniverse(chw_Data);
//const std::string RootName = GetPlaylist_ROOT_path("1D_BranchesADDED", isNOT_mc );
auto intial_playlist = GetPlaylist_InitialName(PlayList_iterator);
const std::string RootName = GetPlaylist_ROOT_path(intial_playlist, isNOT_mc );

std::cout << "rootName =" << RootName<<std::endl;
//MinervaUniverse::SetPlaylist_AGAIN(playlist);
//MinervaUniverse::SetPlaylist(playlist);
//double POTFULLDATA = dataEvt->GetBatchPOT();

//std::cout << "POT = " << dataPOT<<std::endl;
//HeliumCVUniverse* universe = data_error_bands["CV"][0];
std::cout << "*** Starting 2D Data Loop ***" << std::endl;

for(Long64_t ievent=0; ievent < chw_Data->GetEntries(); ++ievent){

  if(ievent%10000==0) std::cout << (ievent/1000) << "k " << std::flush;

  dataEvt->SetEntry(ievent);
  EventCounter(*dataEvt, kCutsVector, EventCounter_data, isNOT_mc, Playlist_Info );

  if(  PassesCutsRECO(*dataEvt,  isNOT_mc , kCutsVector) ){

  //  double Theta = dataEvt->GetThetamu();
    //double Pmu =   dataEvt-> GetPmu_inhouse()/1000;
    double Theta = dataEvt->GetThetamu();
      double Pmu =   dataEvt->GetPmu()*.001;
      double Emu =   dataEvt->GetEmu()*.001;
      double phi = dataEvt->GetPhimu();

      double px = Pmu * std::sin(Theta) * std::cos(phi);
      double py = Pmu * std::sin(Theta) * std::sin(phi);

      double PT = sqrt(px*px + py*py);
      double PZ = Pmu*std::cos(Theta);
      double  Theta_Degs = Theta*TMath::RadToDeg();
      int secondTrk = dataEvt->Getindex2ndTrackhighestKE();
      double OpenAngle = dataEvt->GetOpenAngle(secondTrk);
      double CurvatureSign = dataEvt->GetCurvatureSignificance();
      double angle2ndTrk = dataEvt->GetNonmuTrkAngleWRTbeamMID(secondTrk);
      double Energy2ndTrk = dataEvt->GetNonmuTrkE_GeV(secondTrk);
      double length2ndtrk = dataEvt->GetNonmuTrkLength_InMinerva_Incm(secondTrk);

      double z = dataEvt->GetVertex_z();
      double r = dataEvt->GetVertex_r();
      double y = dataEvt->GetVertex_y();
      double x = dataEvt->GetVertex_x();

    h_Data_Muon_PZ_PT->Fill(PZ, PT, 1.0);
    h_Data_Muon_PT_cryoVertex_R->Fill(PT, r, 1.0);
    h_Data_Muon_PZ_PT_finebinning->Fill(PZ, PT, 1.0);
    h_Data_Muon_PT_theta->Fill(PT, Theta_Degs,1.0);
    h_Data_Muon_PZ_theta->Fill( PZ, Theta_Degs,1.0);
    h_Data_Muon_E_theta->Fill(Emu, Theta_Degs , 1.0);
    h_Data_Muon_E_PZ->Fill(Emu, PZ, 1.0);
    h_Data_Muon_E_PT->Fill(Emu, PT, 1.0);
    h_Data_cryoVertex_Z_R ->Fill(z,r, 1.0);
    h_Data_cryoVertex_Z_X ->Fill(z,x, 1.0);
    h_Data_cryoVertex_Z_Y ->Fill(z,y, 1.0);
    h_Data_cryoVertex_X_Y ->Fill(x,y, 1.0);

    h_Data_cryoVertex_Z_OpenAngle->Fill(z,OpenAngle, 1.0);
    h_Data_cryoVertex_R_OpenAngle->Fill(r,OpenAngle, 1.0);
    h_Data_cryoVertex_Y_OpenAngle->Fill(y,OpenAngle, 1.0);
    h_Data_cryoVertex_X_OpenAngle->Fill(x,OpenAngle, 1.0);
    h_Data_Muontheta_OpenAngle->Fill(Theta_Degs,OpenAngle, 1.0);
    h_Data_Muon_PT_NTracks->Fill(PT, dataEvt->GetTracksize() ,1.0);
    h_Data_Vertex_Z_MuonTheta->Fill(z, Theta_Degs);
    h_Data_Muon_PT_CuratureSig->Fill(PT, CurvatureSign,1.0);
    h_Data_Muon_PZ_CuratureSig->Fill(PZ, CurvatureSign,1.0);
    h_Data_Muon_E_CuratureSig->Fill(Emu, CurvatureSign,1.0);
    h_Data_Muon_theta_CuratureSig->Fill(Theta_Degs, CurvatureSign,1.0);
    h_Data_secTrkE_secTrkTheta->Fill(Energy2ndTrk, angle2ndTrk,1.0);
    h_Data_Vertex_Z_secTrkTheta->Fill(z, angle2ndTrk,1.0);
    h_Data_Vertex_Z_secTrkE->Fill(z, Energy2ndTrk,1.0);
    h_Data_Vertex_Z_trkLength->Fill(z, length2ndtrk,1.0);
    h_Data_secTrkTheta_TrkLength->Fill(angle2ndTrk, length2ndtrk,1.0);
    h_Data_secTrkE_TrkLength->Fill(Energy2ndTrk, length2ndtrk,1.0);
    h_Data_secTrkTheta_secTrkDoca->Fill(angle2ndTrk,dataEvt->GetNonmuDOCA(secondTrk) ,1.0);
    h_Data_secTrkE_secTrkDoca->Fill(Energy2ndTrk,dataEvt->GetNonmuDOCA(secondTrk) ,1.0);
    h_Data_MuonDoca_secTrkDoca->Fill(dataEvt->GetDOCAmu(), dataEvt->GetNonmuDOCA(secondTrk) ,1.0);
    h_Data_Vertex_Z_ChiSq->Fill(z, dataEvt->GetVertexChiSqrFit() ,1.0);

    double Reco_distance = RECO_Distance_to_innerTank(*dataEvt);

    h_Data_Vertex_Z_DistanceNearEdge->Fill(z, Reco_distance ,1.0);
    h_Data_Vertex_R_DistanceNearEdge->Fill(r, Reco_distance ,1.0);
    h_Data_Vertex_X_DistanceNearEdge->Fill(x, Reco_distance ,1.0);
    h_Data_Vertex_Y_DistanceNearEdge->Fill(y, Reco_distance ,1.0);


  }

}
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
//EventCountMap[kPlayListVector[0]] = EventCounter_MCFull;
//EventCountMap[kPlayListVector[0]] = EventCounter_MCEmpty;
EventCountMap[PlayList_iterator] = EventCounter_data;
//EventCountMap[kPlayListVector[3]] = EventCounter_dataEmpty;
//////////////////////////////////////////////////////////////////////////
//End of Empty data
//////////////////////////////////////////////////////////////////////////



PrintCutstoScreen( kCutsVector , EventCounter_data, "Full Data",1.0 );

//=========================================
// Plot stuff
//=========================================


char  pdfName[1024];
char pdf_start[1024];
char pdf_end[1024];
char XaxisName[1024];
sprintf(pdfName, "MuonVars");
//sprintf(pdf_start, "Optimization_figures.pdf(");
//sprintf(pdf_end, "Optimization_figures.pdf)");

//TCanvas *can = new TCanvas("", "");
TCanvas *can = new TCanvas("can", "can",1800,1600);
  std::cout << "END OF Plotting" << std::endl;

  char outFileName[1024];
  auto playlist_name = Playlist_Info.GetPlaylistname();
  auto datatype = String_ISMC(isNOT_mc);
  char c[playlist_name.size() + 1];
  char d[datatype.size() + 1];
  strcpy(c, playlist_name.c_str());
  strcpy(d, datatype.c_str());
  char rootpathway[OUTputRoot_pathway.length()+1];
  strcpy(rootpathway, OUTputRoot_pathway.c_str());
  Make_cvsOfCutsRate( kCutsVector , EventCounter_data, c, isNOT_mc, mcscale, dataPOT );
  //outFileName = "Histograms_test.root";
  //auto outFile = TFile::Open(outFileName);
  sprintf(outFileName, "%s/%s_2D%s_%s_Fid.root",rootpathway, "Histograms",c,d);

  std::cout << "Writing output file to: " <<outFileName << std::endl;

  //TFile outFile(outFileName, "RECREATE");

  TFile outFile(outFileName, "RECREATE");

  TChain POT_branch("Meta");
  POT_branch.Add(RootName.c_str());
  TTree *clone =POT_branch.CloneTree();
  clone->Write();


  h_Data_Muon_PZ_PT->Write();

  h_Data_Muon_PZ_PT_finebinning->Write();
  h_Data_Muon_PT_theta->Write();
  h_Data_Muon_PZ_theta->Write();
  h_Data_Muon_E_theta->Write();
  h_Data_Muon_E_PZ->Write();
  h_Data_Muon_E_PT->Write();
  h_Data_cryoVertex_Z_R->Write();
  h_Data_cryoVertex_Z_X->Write();
  h_Data_cryoVertex_Z_Y->Write();
  h_Data_cryoVertex_X_Y->Write();
  h_Data_Muon_PT_cryoVertex_R->Write();

  h_Data_cryoVertex_Z_OpenAngle->Write();
  h_Data_cryoVertex_R_OpenAngle->Write();
  h_Data_cryoVertex_Y_OpenAngle->Write();
  h_Data_cryoVertex_X_OpenAngle->Write();
  h_Data_Muontheta_OpenAngle->Write();
  h_Data_Vertex_Z_MuonTheta->Write();
  h_Data_Muon_PT_CuratureSig->Write();
  h_Data_Muon_PZ_CuratureSig->Write();
  h_Data_Muon_E_CuratureSig->Write();
  h_Data_Muon_theta_CuratureSig->Write();
  h_Data_secTrkE_secTrkTheta->Write();
  h_Data_Vertex_Z_secTrkTheta->Write();
  h_Data_Vertex_Z_secTrkE->Write();
  h_Data_Vertex_Z_trkLength->Write();
  h_Data_secTrkTheta_TrkLength->Write();
  h_Data_secTrkE_TrkLength->Write();
  h_Data_secTrkTheta_secTrkDoca->Write();
  h_Data_secTrkE_secTrkDoca->Write();
  h_Data_MuonDoca_secTrkDoca->Write();
  h_Data_Vertex_Z_ChiSq->Write();
  h_Data_Muon_PT_NTracks->Write();
  h_Data_Vertex_Z_DistanceNearEdge->Write();
  h_Data_Vertex_R_DistanceNearEdge->Write();
  h_Data_Vertex_X_DistanceNearEdge->Write();
  h_Data_Vertex_Y_DistanceNearEdge->Write();
  outFile.Close();

  //=========================================






  std::cout << "Success looping throught Playlist of " <<Playlist_Info.GetPlaylistname() <<std::endl;
 // END OF PLAYLIST Loop


}//END of Event Loop

//=========================================
//=========================================
//////////////////////////////////////////////////////////////


std::vector<ECuts> GetRECOCutsVector() {
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


//////////////////////////////////////////////////////////////////////////
//GET MUON Varibles
//////////////////////////////////////////////////////////////////////////
std::vector<MuonVar> GetMUONVaribles() {
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
}

//////////////////////////////////////////////////////////////////////////
//GET Vertex Varibles
//////////////////////////////////////////////////////////////////////////
std::vector<CryoVertex> GetCryoVertexVaribles() {
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
}


std::vector<SecondTrkVar> GetPlayListSecondTrkVector() {
  std::vector<SecondTrkVar> Playlist;

  Playlist.push_back(ksecE);
  Playlist.push_back(kThetamid);

  return Playlist;
}



//////////////////////////////////////////////////////////////////////////
//GET CryoTank Varibles
//////////////////////////////////////////////////////////////////////////


//////////////////////////
///Main
/////////////////////////
int main(int argc, char* argv[]){
  TH1::AddDirectory(false);

  std::cout << "This is the playlist "<< argv[1] << std::endl;
  std::string playlist_string(argv[1]);
  ME_helium_Playlists Playlist_to_run = GetPlaylist_FromString(playlist_string);

  bool m_debugOn=true;
  std::cout << "Run in Debug Mode? (0 = NO, 1 = YES) " << std::endl;
  //std::cin >> my_debug;
  std::cout << std::boolalpha << m_debugOn << std::endl;

  bool Run_EventLoopOnGid = false;
  if(Run_EventLoopOnGid==true){std::cout << "This Eventloop is step up to run on the Grid" << std::endl;}
  else{std::cout << "This Eventloop is step up locally" << std::endl;}




  runEventLoop(m_debugOn, Playlist_to_run, Run_EventLoopOnGid);
  return 0;
}
