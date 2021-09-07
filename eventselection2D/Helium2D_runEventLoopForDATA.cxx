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
std::vector<double> Ebin_vector = GetBinMuonVector(kE);
std::vector<double> Pzbin_vector= GetBinMuonVector(kP_Z);
std::vector<double> PTbin_vector= GetBinMuonVector(kP_T);

std::vector<double> MuonThetabin_vector= GetBinMuonVector(kAngleWRTB);

std::vector<double> Vertex_Xbin_vector= GetBinvertexVector(kX);
std::vector<double> Vertex_Ybin_vector= GetBinvertexVector(kY);
std::vector<double> Vertex_Zbin_vector= GetBinvertexVector(kZ);
std::vector<double> Vertex_Rbin_vector= GetBinvertexVector(kR);

std::vector<double> Vertex_DOCAbin_vector= GetBinMuonVector(kDOCA_muon);

std::vector<double> SecTrkEbin_vector= GetSecondTrkVarVector(ksecE);
std::vector<double> SecTrkThetamid_vector= GetSecondTrkVarVector(kThetamid);
std::vector<double> SecTrkTrkDOCA_vector= GetSecondTrkVarVector(kDOCA);
std::vector<double> SecTrkPathway_vector = GetSecondTrkVarVector(kPathway);

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

std::vector<double> Vertex_ChiSqFit_vector= GetBinvertexVector(kfitConverge);
std::vector<double> Muon_curvatureSig_vector= GetBinMuonVector(kcurvatureSig);

std::vector<double> MuonCharge_vector= GetBinMuonVector(kCharge);
std::vector<double> MuonMatchtoMinos_vector= GetBinMuonVector(kMuonMatchtoMinos);
std::vector<double> MuonMatchtoVeto_vector= GetBinMuonVector(kMuonMatchtoVeto);

  // Use the vector of systematic universes to make your MnvH1D

////////////////
//muon Energy///
////////////////



MnvH2D *h_Data_Muon_PT_PZ    =    new MnvH2D("h_Data_Muon_PT_PZ", "h_Data_Muon_PT_PZ", PTbin_vector.size()-1 ,PTbin_vector.data(), Pzbin_vector.size()-1, Pzbin_vector.data() );
MnvH2D *h_Data_Muon_PT_theta =    new MnvH2D("h_Data_Muon_PT_theta", "h_Data_Muon_PT_theta", PTbin_vector.size()-1 ,PTbin_vector.data(), MuonThetabin_vector.size()-1,MuonThetabin_vector.data());
MnvH2D *h_Data_Muon_PZ_theta =    new MnvH2D("h_Data_Muon_PZ_theta", "h_Data_Muon_PZ_theta", Pzbin_vector.size()-1 ,Pzbin_vector.data(), MuonThetabin_vector.size()-1,MuonThetabin_vector.data());
MnvH2D *h_Data_Muon_E_theta  =    new MnvH2D("h_Data_Muon_E_theta", "h_Data_Muon_E_theta",  Ebin_vector.size()-1 , Ebin_vector.data(), MuonThetabin_vector.size()-1,MuonThetabin_vector.data());
MnvH2D *h_Data_Muon_E_PZ     =    new MnvH2D("h_Data_Muon_E_PZ", "h_Data_Muon_E_PZ",  Ebin_vector.size()-1 , Ebin_vector.data(),  Pzbin_vector.size()-1, Pzbin_vector.data() );
MnvH2D *h_Data_Muon_E_PT     =    new MnvH2D("h_Data_Muon_E_PT", "h_Data_Muon_E_PT",  Ebin_vector.size()-1 , Ebin_vector.data(), PTbin_vector.size()-1, PTbin_vector.data() );

MnvH2D *h_Data_cryoVertex_Z_R      =    new MnvH2D("h_Data_cryoVertex_Z_R ", "h_Data_cryoVertex_Z_R ", Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data(), Vertex_Rbin_vector.size()-1 , Vertex_Rbin_vector.data() );

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
std::cout << "*** Starting Data Loop ***" << std::endl;

for(Long64_t ievent=0; ievent < chw_Data->GetEntries(); ++ievent){

  if(ievent%10000==0) std::cout << (ievent/1000) << "k " << std::flush;

  dataEvt->SetEntry(ievent);
  EventCounter(*dataEvt, kCutsVector, EventCounter_data, isNOT_mc, Playlist_Info );

  if(  PassesCutsRECO(*dataEvt,  isNOT_mc , kCutsVector) ){

  //  double Theta = dataEvt->GetThetamu();
    //double Pmu =   dataEvt-> GetPmu_inhouse()/1000;


    double Theta = dataEvt->GetThetamu();
    double Pmu = dataEvt -> GetPmu()/1000;
    double Emu = dataEvt->GetEmu()*.001;
    double theta_degs = Theta*(180.0/3.1415926);
    h_Data_Muon_PT_PZ->Fill(Pmu*std::sin(Theta), Pmu*std::cos(Theta), 1.0);
    h_Data_Muon_PT_theta->Fill(Pmu*std::sin(Theta), theta_degs,1.0);
    h_Data_Muon_PZ_theta->Fill( Pmu*std::cos(Theta), theta_degs,1.0);
    h_Data_Muon_E_theta->Fill(Emu, theta_degs , 1.0);
    h_Data_Muon_E_PZ->Fill(Emu, Pmu*std::cos(Theta), 1.0);
    h_Data_Muon_E_PT->Fill(Emu, Pmu*std::sin(Theta), 1.0);
    h_Data_cryoVertex_Z_R ->Fill(dataEvt->GetVertex_z(),dataEvt->GetVertex_r(), 1.0);

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
  sprintf(outFileName, "%s/%s_2D%s_%s.root",rootpathway, "Histograms",c,d);

  std::cout << "Writing output file to: " <<outFileName << std::endl;

  //TFile outFile(outFileName, "RECREATE");

  TFile outFile(outFileName, "RECREATE");

  TChain POT_branch("Meta");
  POT_branch.Add(RootName.c_str());
  TTree *clone =POT_branch.CloneTree();
  clone->Write();


  h_Data_Muon_PT_PZ->Write();
  h_Data_Muon_PT_theta->Write();
  h_Data_Muon_PZ_theta->Write();
  h_Data_Muon_E_theta->Write();
  h_Data_Muon_E_PZ->Write();
  h_Data_Muon_E_PT->Write();
  h_Data_cryoVertex_Z_R->Write();

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
