//Author: Christian Nguyen
// Helium Cross Section Extractor.cxx
// Started to Build: May 17 2020
//email: christian2nguyen@ufl.edu

#include "ExtractHeliumCrossSectionHists.h"

std::string OUTputRoot_pathway = "/minerva/data/users/cnguyen/CrossSection_Hists";
std::vector<MuonVar> GetCrossSectionVaribles();
std::vector<ME_helium_Playlists> GetFullPlayListVector();
std::vector<ME_helium_Playlists> GetEmptyPlayListVector();
void RunCrossSectionExtractor(bool &my_norm, bool &my_debug, int &Print_Systematics){
TH1::AddDirectory(false);
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~       Starting CrossSection Extraction for Helium 1D: ~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
auto FullME_playlist_vector = GetFullPlayListVector();
auto EmptyME_playlist_vector = GetEmptyPlayListVector();
auto full_playlist_initial = GetPlaylist_InitialName(FullME_playlist_vector[0]);
auto empty_playlist_initial = GetPlaylist_InitialName(EmptyME_playlist_vector[0]);

char fullplaylist_char[full_playlist_initial.length()+1];
strcpy( fullplaylist_char,full_playlist_initial.c_str());

char emptyplaylist_char[empty_playlist_initial.length()+1];
strcpy( emptyplaylist_char,empty_playlist_initial.c_str());


std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~       Getting N Helium Atoms      ~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

double CryoTankVolume = CryoTankInnerVolume_metercube();
std::cout<< "CryoTank Volume [m^3]= " << CryoTankVolume<<std::endl;

double Helium_Density =  121.403; // kg / m^3
double mass = CryoTankVolume*Helium_Density;
std::cout<< " Helium Mass [kg] = " << mass<<std::endl;

double helium_molar_mass = 4.002602 / 1000.0; // g/ mol * kg/1000g
double moles = mass / helium_molar_mass;
std::cout<< "Helium moles = " << moles <<std::endl;
double NHelium = 6.02214 * moles * pow(10,23);
std::cout<< "NHelium = " << NHelium<<std::endl;

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

Pot_MapStatusList POT_MC_Status, POT_DATA_Status;
///////////////////////////////////////////
//I want to constuct cross section as a function of muon parameters pT, Pz , E , and theta
// going to try to find E first
///////////////////////////////
// lets start with two playlist F and G
auto PlaylistME_1L_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1L_MC_All_SysErrorsOn.root";
auto PlaylistME_1G_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1G_MC_All_SysErrorsOn.root";


auto PlaylistME_1L_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1L_Data.root";
auto PlaylistME_1G_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1G_Data.root";


auto PlaylistME_1L_TRUTH_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1L_TRUTH_All_SysErrorsOn.root";
auto PlaylistME_1G_TRUTH_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1G_TRUTH_All_SysErrorsOn.root";


//auto PlaylistME_1L_TRUTH_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1L_TRUTH_StatsONLY.root";
//auto PlaylistME_1G_TRUTH_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1G_TRUTH_StatsONLY.root";



TFile *TFile_ME1L_RECO_MC = new TFile(PlaylistME_1L_MC_path);
TFile *TFile_ME1G_RECO_MC = new TFile(PlaylistME_1G_MC_path);

TFile *TFile_ME1L_TRUTH_MC = new TFile(PlaylistME_1L_TRUTH_MC_path);
TFile *TFile_ME1G_TRUTH_MC = new TFile(PlaylistME_1G_TRUTH_MC_path);

TFile *TFile_ME1L_DATA = new TFile(PlaylistME_1L_Data_path);
TFile *TFile_ME1G_DATA = new TFile(PlaylistME_1G_Data_path);


auto MuonVaribles = GetCrossSectionVaribles();

auto outFile = TFile::Open("CrossSection_closureTest.root", "RECREATE");

CrossSection_histNames MuonE_names = Constuct_crosssection_Histname(MuonVaribles[0]);
CrossSection_histNames MuonPZ_names = Constuct_crosssection_Histname(MuonVaribles[1]);
CrossSection_histNames MuonPT_names = Constuct_crosssection_Histname(MuonVaribles[2]);
CrossSection_histNames MuonTheta_names = Constuct_crosssection_Histname(MuonVaribles[3]);
std::cout<<"found names"<< std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
Print_crosssection_Histname(MuonE_names);
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
Print_crosssection_Histname(MuonPZ_names);
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
Print_crosssection_Histname(MuonPT_names);
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
Print_crosssection_Histname(MuonTheta_names);
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

CrossSection_Hist MuonE_CrossSection_Hists_Full = Constuct_crosssection_Hists(MuonE_names, TFile_ME1L_RECO_MC, TFile_ME1L_TRUTH_MC, TFile_ME1L_DATA);
std::cout<<"got full hist"<< std::endl;
CrossSection_Hist MuonE_CrossSection_Hists_Empty = Constuct_crosssection_Hists(MuonE_names, TFile_ME1G_RECO_MC, TFile_ME1G_TRUTH_MC, TFile_ME1G_DATA);
std::cout<<"got empty hist"<< std::endl;
Check_NSignalBins(MuonE_CrossSection_Hists_Full,"MuonE_CrossSection_Hists_Full" );
Check_NSignalBins(MuonE_CrossSection_Hists_Empty,"MuonE_CrossSection_Hists_Empty" );

WritetoTFile_All(MuonE_CrossSection_Hists_Full, *outFile, "h_MuonE_Full");
WritetoTFile_All(MuonE_CrossSection_Hists_Empty, *outFile, "h_MuonE_Empty");


CrossSection_Hist MuonPZ_CrossSection_Hists_Full = Constuct_crosssection_Hists(MuonPZ_names, TFile_ME1L_RECO_MC, TFile_ME1L_TRUTH_MC, TFile_ME1L_DATA);
std::cout<<"got full hist"<< std::endl;
CrossSection_Hist MuonPZ_CrossSection_Hists_Empty = Constuct_crosssection_Hists(MuonPZ_names, TFile_ME1G_RECO_MC, TFile_ME1G_TRUTH_MC, TFile_ME1G_DATA);
std::cout<<"got empty hist"<< std::endl;


Check_NSignalBins(MuonPZ_CrossSection_Hists_Full,"MuonPZ_CrossSection_Hists_Full" );
Check_NSignalBins(MuonPZ_CrossSection_Hists_Empty,"MuonPZ_CrossSection_Hists_Empty" );


WritetoTFile_All(MuonPZ_CrossSection_Hists_Full, *outFile, "h_MuonPZ_Full");
WritetoTFile_All(MuonPZ_CrossSection_Hists_Empty, *outFile, "h_MuonPZ_Empty");



CrossSection_Hist MuonPT_CrossSection_Hists_Full = Constuct_crosssection_Hists(MuonPT_names, TFile_ME1L_RECO_MC, TFile_ME1L_TRUTH_MC, TFile_ME1L_DATA);
std::cout<<"got full hist"<< std::endl;
CrossSection_Hist MuonPT_CrossSection_Hists_Empty = Constuct_crosssection_Hists(MuonPT_names, TFile_ME1G_RECO_MC, TFile_ME1G_TRUTH_MC, TFile_ME1G_DATA);
std::cout<<"got empty hist"<< std::endl;

Check_NSignalBins(MuonPT_CrossSection_Hists_Full,"MuonPT_CrossSection_Hists_Full" );
Check_NSignalBins(MuonPT_CrossSection_Hists_Empty,"MuonPT_CrossSection_Hists_Empty" );
WritetoTFile_All(MuonPT_CrossSection_Hists_Full, *outFile, "h_MuonPT_Full");
WritetoTFile_All(MuonPT_CrossSection_Hists_Empty, *outFile, "h_MuonPT_Empty");

CrossSection_Hist MuonTheta_CrossSection_Hists_Full = Constuct_crosssection_Hists(MuonTheta_names, TFile_ME1L_RECO_MC, TFile_ME1L_TRUTH_MC, TFile_ME1L_DATA);
std::cout<<"got full hist"<< std::endl;
CrossSection_Hist MuonTheta_CrossSection_Hists_Empty = Constuct_crosssection_Hists(MuonTheta_names, TFile_ME1G_RECO_MC, TFile_ME1G_TRUTH_MC, TFile_ME1G_DATA);
std::cout<<"got empty hist"<< std::endl;

Check_NSignalBins(MuonTheta_CrossSection_Hists_Full,"MuonTheta_CrossSection_Hists_Full" );
Check_NSignalBins(MuonTheta_CrossSection_Hists_Empty,"MuonTheta_CrossSection_Hists_Empty" );
WritetoTFile_All(MuonTheta_CrossSection_Hists_Full, *outFile, "h_MuonTheta_Full");
WritetoTFile_All(MuonTheta_CrossSection_Hists_Empty, *outFile, "h_MuonTheta_Empty");

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~GET POT    ~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;


//POT_MC_Status[kFULL] = Pot_from_rootpathway(PlaylistME_1L_MC_path, true );
POT_MC_Status[kEMPTY] = Pot_from_rootpathway(PlaylistME_1G_MC_path, true );

POT_DATA_Status[kFULL] = Pot_from_rootpathway(PlaylistME_1L_Data_path, false );
POT_DATA_Status[kEMPTY] = Pot_from_rootpathway(PlaylistME_1G_Data_path, false );

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~Normalize Hist ~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
;
POT_MC_Status[kFULL] =  CountPOT(PlaylistME_1L_MC_path);

POT_Normalize_CrossSection_Hist(MuonE_CrossSection_Hists_Full, POT_DATA_Status[kFULL]/POT_MC_Status[kFULL]);
POT_Normalize_CrossSection_Hist(MuonE_CrossSection_Hists_Empty, POT_DATA_Status[kFULL]/POT_MC_Status[kEMPTY], POT_DATA_Status[kFULL] / POT_DATA_Status[kEMPTY], true );
WritetoTFile_main(MuonE_CrossSection_Hists_Full, *outFile, "h_MuonE_Full_potnorm");
WritetoTFile_main(MuonE_CrossSection_Hists_Empty, *outFile, "h_MuonE_Empty_potnorm");
Subtract_CrossSection_Hist(MuonE_CrossSection_Hists_Full, MuonE_CrossSection_Hists_Empty);
WritetoTFile_main(MuonE_CrossSection_Hists_Full, *outFile, "h_MuonE_Full_sub_Empty_potnorm");
WritetoTFile_NormTRUECrossSection(MuonE_CrossSection_Hists_Full, *outFile,  "h_MuonE_TrueCrossSection",  NHelium, POT_DATA_Status[kFULL]);

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;


POT_Normalize_CrossSection_Hist(MuonPZ_CrossSection_Hists_Full, POT_DATA_Status[kFULL]/POT_MC_Status[kFULL]);
POT_Normalize_CrossSection_Hist(MuonPZ_CrossSection_Hists_Empty, POT_DATA_Status[kFULL]/POT_MC_Status[kEMPTY], POT_DATA_Status[kFULL] / POT_DATA_Status[kEMPTY], true );
WritetoTFile_main(MuonPZ_CrossSection_Hists_Full, *outFile, "h_MuonPZ_Full_potnorm");
WritetoTFile_main(MuonPZ_CrossSection_Hists_Empty, *outFile, "h_MuonPZ_Empty_potnorm");
Subtract_CrossSection_Hist(MuonPZ_CrossSection_Hists_Full, MuonPZ_CrossSection_Hists_Empty);
WritetoTFile_main(MuonPZ_CrossSection_Hists_Full, *outFile, "h_MuonPZ_Full_sub_Empty_potnorm");
WritetoTFile_NormTRUECrossSection(MuonPZ_CrossSection_Hists_Full, *outFile, "h_MuonPZ_TrueCrossSection",  NHelium, POT_DATA_Status[kFULL]);

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

POT_Normalize_CrossSection_Hist(MuonPT_CrossSection_Hists_Full, 1.0);
POT_Normalize_CrossSection_Hist(MuonPT_CrossSection_Hists_Empty, POT_DATA_Status[kFULL]/POT_MC_Status[kEMPTY], POT_DATA_Status[kFULL] / POT_DATA_Status[kEMPTY], true );
WritetoTFile_main(MuonPT_CrossSection_Hists_Full, *outFile, "h_MuonPT_Full_potnorm");
WritetoTFile_main(MuonPT_CrossSection_Hists_Empty, *outFile, "h_MuonPT_Empty_potnorm");
//Subtract_CrossSection_Hist(MuonPT_CrossSection_Hists_Full, MuonPT_CrossSection_Hists_Empty);
WritetoTFile_main(MuonPT_CrossSection_Hists_Full, *outFile, "h_MuonPT_Full_sub_Empty_potnorm");
const double trackerAtomsC = 2.22311e+27 * 92.;
WritetoTFile_NormTRUECrossSection(MuonPT_CrossSection_Hists_Full,*outFile, "h_MuonPT_TrueCrossSection",  NHelium, POT_MC_Status[kFULL]);
std::cout<<"POT MC PT = "<< POT_MC_Status[kFULL] <<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;




POT_Normalize_CrossSection_Hist(MuonTheta_CrossSection_Hists_Full, POT_DATA_Status[kFULL]/POT_MC_Status[kFULL]);
POT_Normalize_CrossSection_Hist(MuonTheta_CrossSection_Hists_Empty, POT_DATA_Status[kFULL]/POT_MC_Status[kEMPTY], POT_DATA_Status[kFULL] / POT_DATA_Status[kEMPTY], true );
WritetoTFile_main(MuonTheta_CrossSection_Hists_Full, *outFile, "h_MuonTheta_Full_potnorm");
WritetoTFile_main(MuonTheta_CrossSection_Hists_Empty, *outFile, "h_MuonTheta_Empty_potnorm");
Subtract_CrossSection_Hist(MuonTheta_CrossSection_Hists_Full, MuonTheta_CrossSection_Hists_Empty);
WritetoTFile_main(MuonTheta_CrossSection_Hists_Full, *outFile, "h_MuonTheta_Full_sub_Empty_potnorm");



WritetoTFile_NormTRUECrossSection(MuonTheta_CrossSection_Hists_Full,*outFile, "h_MuonTheta_TrueCrossSection",  NHelium, POT_DATA_Status[kFULL]);

/*
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~ UnFolding ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
MuonE_CrossSection_Hists_Full.h_Mig->Clone()->Write("h_MuonE_Mig");
auto unfoldedMuonE_data = UnfoldHist( MuonE_CrossSection_Hists_Full.h_Data_Signal, MuonE_CrossSection_Hists_Full.h_Mig, 6 );
unfoldedMuonE_data->Clone()->Write("h_MuonE_unfolded_data");
MuonPZ_CrossSection_Hists_Full.h_Mig->Clone()->Write("h_MuonPZ_Mig");
auto unfoldedMuonPZ_data = UnfoldHist( MuonPZ_CrossSection_Hists_Full.h_Data_Signal, MuonPZ_CrossSection_Hists_Full.h_Mig, 6 );
unfoldedMuonPZ_data->Clone()->Write("h_MuonPZ_unfolded_data");
MuonPT_CrossSection_Hists_Full.h_Mig->Clone()->Write("h_MuonPT_Mig");
auto unfoldedMuonPT_data = UnfoldHist( MuonPT_CrossSection_Hists_Full.h_Data_Signal, MuonPT_CrossSection_Hists_Full.h_Mig, 6 );
unfoldedMuonPT_data->Clone()->Write("h_MuonPT_unfolded_data");

MuonTheta_CrossSection_Hists_Full.h_Mig->Clone()->Write("h_MuonTheta_Mig");
auto unfoldedMuonTheta_data = UnfoldHist( MuonTheta_CrossSection_Hists_Full.h_Data_Signal, MuonTheta_CrossSection_Hists_Full.h_Mig, 6 );
unfoldedMuonTheta_data->Clone()->Write("h_MuonTheta_unfolded_data");





std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~ efficiency Correct ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
AddErrorBands_TOEffDom(MuonE_CrossSection_Hists_Full);
MuonE_CrossSection_Hists_Full.h_effNum->Divide(MuonE_CrossSection_Hists_Full.h_effNum, MuonE_CrossSection_Hists_Full.h_effDom);
MuonE_CrossSection_Hists_Full.h_effNum->Clone()->Write("h_MuonE_efficiency");

unfoldedMuonE_data->Divide(unfoldedMuonE_data, MuonE_CrossSection_Hists_Full.h_effNum);
unfoldedMuonE_data->Clone()->Write("h_MuonE_unfolded_data_effcorrected");
///////////////////////////////
MuonPZ_CrossSection_Hists_Full.h_effNum->Divide(MuonPZ_CrossSection_Hists_Full.h_effNum, MuonPZ_CrossSection_Hists_Full.h_effDom);
MuonPZ_CrossSection_Hists_Full.h_effNum->Clone()->Write("h_MuonPZ_efficiency");

unfoldedMuonPZ_data->Divide(unfoldedMuonPZ_data, MuonPZ_CrossSection_Hists_Full.h_effNum);
unfoldedMuonPZ_data->Clone()->Write("h_MuonPZ_unfolded_data_effcorrected");
////////////////////////////////
AddErrorBands_TOEffDom(MuonPT_CrossSection_Hists_Full);
MuonPT_CrossSection_Hists_Full.h_effNum->Divide(MuonPT_CrossSection_Hists_Full.h_effNum, MuonPT_CrossSection_Hists_Full.h_effDom);
MuonPT_CrossSection_Hists_Full.h_effNum->Clone()->Write("h_MuonPT_efficiency");

unfoldedMuonPT_data->Divide(unfoldedMuonPT_data, MuonPT_CrossSection_Hists_Full.h_effNum);
unfoldedMuonPT_data->Clone()->Write("h_MuonPT_unfolded_data_effcorrected");

AddErrorBands_TOEffDom(MuonTheta_CrossSection_Hists_Full);
MuonTheta_CrossSection_Hists_Full.h_effNum->Divide(MuonTheta_CrossSection_Hists_Full.h_effNum, MuonTheta_CrossSection_Hists_Full.h_effDom);
MuonTheta_CrossSection_Hists_Full.h_effNum->Clone()->Write("h_MuonTheta_efficiency");

unfoldedMuonTheta_data->Divide(unfoldedMuonTheta_data, MuonTheta_CrossSection_Hists_Full.h_effNum);
unfoldedMuonTheta_data->Clone()->Write("h_MuonTheta_unfolded_data_effcorrected");


std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~ Cross Section ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;



auto h_crossSection_MuonE = normalize(unfoldedMuonE_data, MuonE_CrossSection_Hists_Full.h_flux, NHelium, POT_DATA_Status[kFULL]);
h_crossSection_MuonE->Clone()->Write("h_MuonE_CrossSection_data_unfolded");

auto h_crossSection_MuonPZ = normalize(unfoldedMuonPZ_data, MuonPZ_CrossSection_Hists_Full.h_flux, NHelium, POT_DATA_Status[kFULL]);
h_crossSection_MuonPZ->Clone()->Write("h_MuonPZ_CrossSection_data_unfolded");

auto h_crossSection_MuonPT = normalize(unfoldedMuonPT_data, MuonPT_CrossSection_Hists_Full.h_flux, NHelium, POT_DATA_Status[kFULL]);
h_crossSection_MuonPT->Clone()->Write("h_MuonPT_CrossSection_data_unfolded");

auto h_crossSection_MuonTheta = normalize(unfoldedMuonTheta_data, MuonTheta_CrossSection_Hists_Full.h_flux, NHelium, POT_DATA_Status[kFULL]);
h_crossSection_MuonTheta->Clone()->Write("h_MuonTheta_CrossSection_data_unfolded");

*/
outFile->Close();

} // end of RunCrossSectionExtractor


//Unfolding function from Aaron Bercelle
//TODO: Trim it down a little?  Remove that static?
/*
PlotUtils::MnvH1D* UnfoldHist( PlotUtils::MnvH1D* h_folded, PlotUtils::MnvH2D* h_migration, int num_iter )
{
  static MinervaUnfold::MnvUnfold unfold;
  PlotUtils::MnvH1D* h_unfolded = nullptr;

  //bool bUnfolded = false;

  TMatrixD dummyCovMatrix;
  if(!unfold.UnfoldHisto( h_unfolded, dummyCovMatrix, h_migration, h_folded, RooUnfold::kBayes, num_iter, true, false ))
    return nullptr;

  /////////////////////////////////////////////////////////////////////////////////////////
  //No idea if this is still needed
  //Probably.  This gets your stat unfolding covariance matrix
  TMatrixD unfoldingCovMatrixOrig;
  int correctNbins;
  int matrixRows;
  TH1D* hUnfoldedDummy  = new TH1D(h_unfolded->GetCVHistoWithStatError());
  TH1D* hRecoDummy      = new TH1D(h_migration->ProjectionX()->GetCVHistoWithStatError());
  TH1D* hTruthDummy     = new TH1D(h_migration->ProjectionY()->GetCVHistoWithStatError());
  TH1D* hBGSubDataDummy = new TH1D(h_folded->GetCVHistoWithStatError());
  TH2D* hMigrationDummy = new TH2D(h_migration->GetCVHistoWithStatError());
  unfold.UnfoldHisto(hUnfoldedDummy, unfoldingCovMatrixOrig, hMigrationDummy, hRecoDummy, hTruthDummy, hBGSubDataDummy,RooUnfold::kBayes, num_iter);//Stupid RooUnfold.  This is dummy, we don't need iterations

  correctNbins=hUnfoldedDummy->fN;
  matrixRows=unfoldingCovMatrixOrig.GetNrows();
  if(correctNbins!=matrixRows){
    std::cout << "****************************************************************************" << std::endl;
    std::cout << "*  Fixing unfolding matrix size because of RooUnfold bug. From " << matrixRows << " to " << correctNbins << std::endl;
    std::cout << "****************************************************************************" << std::endl;
    // It looks like this, since the extra last two bins don't have any content
    unfoldingCovMatrixOrig.ResizeTo(correctNbins, correctNbins);
  }

  for(int i=0; i<unfoldingCovMatrixOrig.GetNrows(); ++i) unfoldingCovMatrixOrig(i,i)=0;
  delete hUnfoldedDummy;
  delete hMigrationDummy;
  delete hRecoDummy;
  delete hTruthDummy;
  delete hBGSubDataDummy;
  h_unfolded->PushCovMatrix("unfoldingCov",unfoldingCovMatrixOrig);

  /////////////////////////////////////////////////////////////////////////////////////////
  return h_unfolded;
}

*/
/*
//The final step of cross section extraction: normalize by flux, bin width, POT, and number of targets
PlotUtils::MnvH1D* normalize(PlotUtils::MnvH1D* efficiencyCorrected, PlotUtils::MnvH1D* fluxIntegral, const double nNucleons, const double POT)
{
  efficiencyCorrected->Divide(efficiencyCorrected, fluxIntegral);

  efficiencyCorrected->Scale(1./nNucleons/POT);
  efficiencyCorrected->Scale(1.e4); //Flux histogram is in m^-2, but convention is to report cm^2
  efficiencyCorrected->Scale(1., "width");

  return efficiencyCorrected;
}
*/
/////////////////////////////////////////////
std::vector<MuonVar> GetCrossSectionVaribles() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<MuonVar> MuonVars;

  MuonVars.push_back(kE);
  MuonVars.push_back(kP_Z);
  MuonVars.push_back(kP_T);
  MuonVars.push_back(kAngleWRTB);

  return MuonVars;
//#endif
}




std::vector<ME_helium_Playlists> GetFullPlayListVector() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ME_helium_Playlists> Playlist;
  //Playlist.push_back(kME1D);
  //Playlist.push_back(kME1A);
  //Playlist.push_back(kME1G);
  //Playlist.push_back(kME1P);

  //Playlist.push_back(kME1C);

  Playlist.push_back(kME1L);

  //Playlist.push_back(kME1F);
  //Playlist.push_back(kME1G);
  return Playlist;
//#endif
}

std::vector<ME_helium_Playlists> GetEmptyPlayListVector() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ME_helium_Playlists> Playlist;
  //Playlist.push_back(kME1D);
  //Playlist.push_back(kME1A);
  //Playlist.push_back(kME1G);
  //Playlist.push_back(kME1P);

  //Playlist.push_back(kME1C);

  //Playlist.push_back(kME1F);

  //Playlist.push_back(kME1F);
  Playlist.push_back(kME1G);
  return Playlist;
//#endif
}

////////////////////////////////////////////
//Main Function
/////////////////////////////////////////////

 int main() {

//TH1::AddDirectory(kFALSE);

bool my_norm=0;
std::cout << "Which Normalization?  (0 = POT, 1 = relative equal areas) " << std::endl;
//std::cin >> my_norm;
std::cout << std::boolalpha << my_norm << std::endl;

bool my_debug=true;
std::cout << "Run in Debug Mode? (0 = NO, 1 = YES) " << std::endl;
//std::cin >> my_debug;
std::cout << std::boolalpha << my_debug << std::endl;

int my_Print_Systmatics=0;
std::cout << "Print Error Systmatics?  [ 0 = Total and Groups Systemtics Errors ,  1 = Total Systematic Errors , 2 = none ]" << std::endl;
//std::cin >> my_Print_Systmatics;

std::cout << "Pitched: " << my_Print_Systmatics << std::endl;




RunCrossSectionExtractor( my_norm, my_debug,  my_Print_Systmatics);

return 0;

}
