//Author: Christian Nguyen
// Helium Cross Section Extractor.cxx
// Started to Build: May 17 2020
//email: christian2nguyen@ufl.edu

#include "ExtractHeliumCrossSectionHists.h"

std::string OUTputRoot_pathway = "/minerva/data/users/cnguyen/CrossSection_Hists_ALLPlaylists";
//void ZeroDiagonal(TMatrixD &m);
//TMatrixD divideCovByHists(TMatrixD m, TH2D* num, TH2D* dem);
std::vector<ME_helium_Playlists> GetFullPlayListVector();
std::vector<ME_helium_Playlists> GetEmptyPlayListVector();


std::vector<Muon2DVar> GetCrossSection2DVaribles();
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

char title_char[2024];
bool Print1Dplots = false;
std::string title_base = GetMuon2DVar_Title(kPT_PZ);
char title_base_char[title_base.length()+1];
strcpy(title_base_char ,title_base.c_str());

std::string title_base_theta = GetMuon2DVar_Title(kE_theta);
char title_base_char_theta[title_base_theta.length()+1];
strcpy(title_base_char_theta ,title_base_theta.c_str());



char text_title_pdf1[2024];
char text_title_pdf2[2024];
char text_title_pdf3[2024];
char text_title_pdf4[2024];
sprintf(text_title_pdf1, "PLOTS_2D_CrossSection_Extraction.pdf(" );
sprintf(text_title_pdf2, "PLOTS_2D_CrossSection_Extraction.pdf");
sprintf(text_title_pdf3, "PLOTS_2D_CrossSection_Extraction.pdf)");
sprintf(text_title_pdf4, "PLOTS_2D_CrossSection_Extraction" );

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
TCanvas *can = new TCanvas("can");
MnvPlotter *mnv_plot = new MnvPlotter();
mnv_plot->ApplyStyle(PlotUtils::kCCInclusiveHeliumStyle);
can -> Print(text_title_pdf1);


std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~       Getting N Helium Atoms      ~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

double CryoTankVolume = CryoTankInnerVolume_metercube();
std::cout<< "CryoTank Volume [m^3]= " << CryoTankVolume<<std::endl;

double Helium_Density =  121.403; // kg / m^3
double Helium_Density_MC = 114; // kg / m^3 given by the MC
double mass = CryoTankVolume*Helium_Density;
double mass_MC = CryoTankVolume*Helium_Density_MC;
std::cout<< " Helium Mass [kg] = " << mass<<std::endl;

double helium_molar_mass = 4.002602 / 1000.0; // g/ mol * kg/1000g
double moles = mass / helium_molar_mass;
double moles_MC = mass_MC / helium_molar_mass;
std::cout<< "Helium moles = " << moles <<std::endl;
std::cout<< "Helium [MC] moles = " << moles_MC <<std::endl;
double NHelium = (6.02214 * moles * pow(10,23))*4; // number of nucleon
double NHelium_MC = (6.02214 * moles_MC * pow(10,23))*4; // number of nucleon
std::cout<< "NHelium = " << NHelium<<std::endl;
std::cout<< "NHelium MC = " << NHelium_MC <<std::endl;

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

Pot_MapStatusList POT_MC_Status, POT_DATA_Status;
///////////////////////////////////////////
//I want to constuct cross section as a function of muon parameters pT, Pz , E , and theta
// going to try to find E first
///////////////////////////////
// lets start with two playlist F and G
/////////////
// Full Playlist
/////////////
auto PlaylistME_1P_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2Dminervame1P_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";
auto PlaylistME_1C_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2Dminervame1C_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";
auto PlaylistME_1D_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2Dminervame1D_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";
auto PlaylistME_1F_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2Dminervame1F_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";
auto PlaylistME_1E_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2Dminervame1E_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";
/////////////
// Empty Playlist
/////////////
auto PlaylistME_1G_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2Dminervame1G_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";
auto PlaylistME_1A_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2Dminervame1A_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";
auto PlaylistME_1L_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2Dminervame1L_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";
auto PlaylistME_1M_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2Dminervame1M_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";
auto PlaylistME_1N_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2Dminervame1N_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";
/////////////
// Full Playlist Data
/////////////

auto PlaylistME_1P_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_2Dminervame1P_Data_Fid.root";
auto PlaylistME_1C_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_2Dminervame1C_Data_Fid.root";
auto PlaylistME_1D_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_2Dminervame1D_Data_Fid.root";
auto PlaylistME_1F_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_2Dminervame1F_Data_Fid.root";
auto PlaylistME_1E_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_2Dminervame1E_Data_Fid.root";

/////////////
// Empty Playlist  Data
/////////////

auto PlaylistME_1G_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_2Dminervame1G_Data_Fid.root";
auto PlaylistME_1A_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_2Dminervame1A_Data_Fid.root";
auto PlaylistME_1L_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_2Dminervame1L_Data_Fid.root";
auto PlaylistME_1M_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_2Dminervame1M_Data_Fid.root";
auto PlaylistME_1N_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_2Dminervame1N_Data_Fid.root";

/////////////
// Full Playlist Truth
/////////////

auto PlaylistME_1P_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2D_minervame1P_TRUTH_All_SysErrorsOn_Fid.root";
auto PlaylistME_1C_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2D_minervame1C_TRUTH_All_SysErrorsOn_Fid.root";
auto PlaylistME_1D_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2D_minervame1D_TRUTH_All_SysErrorsOn_Fid.root";
auto PlaylistME_1F_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2D_minervame1F_TRUTH_All_SysErrorsOn_Fid.root";
auto PlaylistME_1E_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2D_minervame1E_TRUTH_All_SysErrorsOn_Fid.root";

/////////////
// Empty Playlist  Truth
/////////////

auto PlaylistME_1G_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2D_minervame1G_TRUTH_All_SysErrorsOn_Fid.root";
auto PlaylistME_1A_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2D_minervame1A_TRUTH_All_SysErrorsOn_Fid.root";
auto PlaylistME_1L_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2D_minervame1L_TRUTH_All_SysErrorsOn_Fid.root";
auto PlaylistME_1M_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2D_minervame1M_TRUTH_All_SysErrorsOn_Fid.root";
auto PlaylistME_1N_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2D_minervame1N_TRUTH_All_SysErrorsOn_Fid.root";

///////////////////////////
// For Flux
//////////////////////////



////////////
// Full Playlist
/////////////
auto PlaylistME_1P_MC_Flux_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2Dminervame1P_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";
auto PlaylistME_1C_MC_Flux_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2Dminervame1C_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";
auto PlaylistME_1D_MC_Flux_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2Dminervame1D_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";
auto PlaylistME_1F_MC_Flux_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2Dminervame1F_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";
auto PlaylistME_1E_MC_Flux_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2Dminervame1E_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";






ME_playlist_RootPathMAP MAP_RootPath_Empty_MC_RECO;
ME_playlist_RootPathMAP MAP_RootPath_Empty_MC_TRUTH;
ME_playlist_RootPathMAP MAP_RootPath_Empty_DATA;

ME_playlist_RootPathMAP MAP_RootPath_Full_MC_RECO;
ME_playlist_RootPathMAP MAP_RootPath_Full_MC_TRUTH;
ME_playlist_RootPathMAP MAP_RootPath_Full_DATA;

/////////////////////////////
////Empty
///////////////////////////

MAP_RootPath_Empty_MC_RECO.insert(std::make_pair(EmptyME_playlist_vector.at(0), PlaylistME_1G_MC_path));
MAP_RootPath_Empty_MC_RECO.insert(std::make_pair(EmptyME_playlist_vector.at(1), PlaylistME_1A_MC_path));
MAP_RootPath_Empty_MC_RECO.insert(std::make_pair(EmptyME_playlist_vector.at(2), PlaylistME_1L_MC_path));
MAP_RootPath_Empty_MC_RECO.insert(std::make_pair(EmptyME_playlist_vector.at(3), PlaylistME_1M_MC_path));
MAP_RootPath_Empty_MC_RECO.insert(std::make_pair(EmptyME_playlist_vector.at(4), PlaylistME_1N_MC_path));

MAP_RootPath_Empty_MC_TRUTH.insert(std::make_pair(EmptyME_playlist_vector.at(0), PlaylistME_1G_MC_TRUTH_path));
MAP_RootPath_Empty_MC_TRUTH.insert(std::make_pair(EmptyME_playlist_vector.at(1), PlaylistME_1A_MC_TRUTH_path));
MAP_RootPath_Empty_MC_TRUTH.insert(std::make_pair(EmptyME_playlist_vector.at(2), PlaylistME_1L_MC_TRUTH_path));
MAP_RootPath_Empty_MC_TRUTH.insert(std::make_pair(EmptyME_playlist_vector.at(3), PlaylistME_1M_MC_TRUTH_path));
MAP_RootPath_Empty_MC_TRUTH.insert(std::make_pair(EmptyME_playlist_vector.at(4), PlaylistME_1N_MC_TRUTH_path));

MAP_RootPath_Empty_DATA.insert(std::make_pair(EmptyME_playlist_vector.at(0), PlaylistME_1G_Data_path));
MAP_RootPath_Empty_DATA.insert(std::make_pair(EmptyME_playlist_vector.at(1), PlaylistME_1A_Data_path));
MAP_RootPath_Empty_DATA.insert(std::make_pair(EmptyME_playlist_vector.at(2), PlaylistME_1L_Data_path));
MAP_RootPath_Empty_DATA.insert(std::make_pair(EmptyME_playlist_vector.at(3), PlaylistME_1M_Data_path));
MAP_RootPath_Empty_DATA.insert(std::make_pair(EmptyME_playlist_vector.at(4), PlaylistME_1N_Data_path));

/////////////////////////////
////Full
///////////////////////////

MAP_RootPath_Full_MC_RECO.insert(std::make_pair(FullME_playlist_vector.at(0), PlaylistME_1P_MC_path));
MAP_RootPath_Full_MC_RECO.insert(std::make_pair(FullME_playlist_vector.at(1), PlaylistME_1C_MC_path));
MAP_RootPath_Full_MC_RECO.insert(std::make_pair(FullME_playlist_vector.at(2), PlaylistME_1D_MC_path));
MAP_RootPath_Full_MC_RECO.insert(std::make_pair(FullME_playlist_vector.at(3), PlaylistME_1F_MC_path));
MAP_RootPath_Full_MC_RECO.insert(std::make_pair(FullME_playlist_vector.at(4), PlaylistME_1E_MC_path));

MAP_RootPath_Full_MC_TRUTH.insert(std::make_pair(FullME_playlist_vector.at(0), PlaylistME_1P_MC_TRUTH_path));
MAP_RootPath_Full_MC_TRUTH.insert(std::make_pair(FullME_playlist_vector.at(1), PlaylistME_1C_MC_TRUTH_path));
MAP_RootPath_Full_MC_TRUTH.insert(std::make_pair(FullME_playlist_vector.at(2), PlaylistME_1D_MC_TRUTH_path));
MAP_RootPath_Full_MC_TRUTH.insert(std::make_pair(FullME_playlist_vector.at(3), PlaylistME_1F_MC_TRUTH_path));
MAP_RootPath_Full_MC_TRUTH.insert(std::make_pair(FullME_playlist_vector.at(4), PlaylistME_1E_MC_TRUTH_path));

MAP_RootPath_Full_DATA.insert(std::make_pair(FullME_playlist_vector.at(0), PlaylistME_1P_Data_path));
MAP_RootPath_Full_DATA.insert(std::make_pair(FullME_playlist_vector.at(1), PlaylistME_1C_Data_path));
MAP_RootPath_Full_DATA.insert(std::make_pair(FullME_playlist_vector.at(2), PlaylistME_1D_Data_path));
MAP_RootPath_Full_DATA.insert(std::make_pair(FullME_playlist_vector.at(3), PlaylistME_1F_Data_path));
MAP_RootPath_Full_DATA.insert(std::make_pair(FullME_playlist_vector.at(4), PlaylistME_1E_Data_path));


/////////////////////////////////////////////////////
// Empty
/////////////////////////////////////////////////////

TFile *TFile_ME1G_MC_RECO = new TFile(PlaylistME_1G_MC_path);
TFile *TFile_ME1A_MC_RECO = new TFile(PlaylistME_1A_MC_path);
TFile *TFile_ME1L_MC_RECO = new TFile(PlaylistME_1L_MC_path);
TFile *TFile_ME1M_MC_RECO = new TFile(PlaylistME_1M_MC_path);
TFile *TFile_ME1N_MC_RECO = new TFile(PlaylistME_1N_MC_path);

TFile *TFile_ME1G_MC_TRUTH = new TFile(PlaylistME_1G_MC_TRUTH_path);
TFile *TFile_ME1A_MC_TRUTH = new TFile(PlaylistME_1A_MC_TRUTH_path);
TFile *TFile_ME1L_MC_TRUTH = new TFile(PlaylistME_1L_MC_TRUTH_path);
TFile *TFile_ME1M_MC_TRUTH = new TFile(PlaylistME_1M_MC_TRUTH_path);
TFile *TFile_ME1N_MC_TRUTH = new TFile(PlaylistME_1N_MC_TRUTH_path);

TFile *TFile_ME1G_DATA = new TFile(PlaylistME_1G_Data_path);
TFile *TFile_ME1A_DATA = new TFile(PlaylistME_1A_Data_path);
TFile *TFile_ME1L_DATA = new TFile(PlaylistME_1L_Data_path);
TFile *TFile_ME1M_DATA = new TFile(PlaylistME_1M_Data_path);
TFile *TFile_ME1N_DATA = new TFile(PlaylistME_1N_Data_path);

/////////////////////////////////////////////////////
// Full
/////////////////////////////////////////////////////
TFile *TFile_ME1P_MC_RECO = new TFile(PlaylistME_1P_MC_path);
TFile *TFile_ME1C_MC_RECO = new TFile(PlaylistME_1C_MC_path);
TFile *TFile_ME1D_MC_RECO = new TFile(PlaylistME_1D_MC_path);
TFile *TFile_ME1E_MC_RECO = new TFile(PlaylistME_1E_MC_path);
TFile *TFile_ME1F_MC_RECO = new TFile(PlaylistME_1F_MC_path);

TFile *TFile_ME1P_MC_TRUTH = new TFile(PlaylistME_1P_MC_TRUTH_path);
TFile *TFile_ME1C_MC_TRUTH = new TFile(PlaylistME_1C_MC_TRUTH_path);
TFile *TFile_ME1D_MC_TRUTH = new TFile(PlaylistME_1D_MC_TRUTH_path);
TFile *TFile_ME1E_MC_TRUTH = new TFile(PlaylistME_1E_MC_TRUTH_path);
TFile *TFile_ME1F_MC_TRUTH = new TFile(PlaylistME_1F_MC_TRUTH_path);

TFile *TFile_ME1P_DATA = new TFile(PlaylistME_1P_Data_path);
TFile *TFile_ME1C_DATA = new TFile(PlaylistME_1C_Data_path);
TFile *TFile_ME1D_DATA = new TFile(PlaylistME_1D_Data_path);
TFile *TFile_ME1E_DATA = new TFile(PlaylistME_1E_Data_path);
TFile *TFile_ME1F_DATA = new TFile(PlaylistME_1F_Data_path);

ME_playlist_TFileMAP EmptyTFile_Map_MC_RECO;
ME_playlist_TFileMAP EmptyTFile_Map_MC_TRUTH;
ME_playlist_TFileMAP EmptyTFile_Map_DATA;

ME_playlist_TFileMAP FullTFile_Map_MC_RECO;
ME_playlist_TFileMAP FullTFile_Map_MC_TRUTH;
ME_playlist_TFileMAP FullTFile_Map_DATA;

/////////////////////////////////////////////////////
// Empty
/////////////////////////////////////////////////////


EmptyTFile_Map_MC_RECO.insert(std::make_pair(EmptyME_playlist_vector.at(0),TFile_ME1G_MC_RECO));
EmptyTFile_Map_MC_RECO.insert(std::make_pair(EmptyME_playlist_vector.at(1),TFile_ME1A_MC_RECO));
EmptyTFile_Map_MC_RECO.insert(std::make_pair(EmptyME_playlist_vector.at(2),TFile_ME1L_MC_RECO));
EmptyTFile_Map_MC_RECO.insert(std::make_pair(EmptyME_playlist_vector.at(3),TFile_ME1M_MC_RECO));
EmptyTFile_Map_MC_RECO.insert(std::make_pair(EmptyME_playlist_vector.at(4),TFile_ME1N_MC_RECO));

EmptyTFile_Map_MC_TRUTH.insert(std::make_pair(EmptyME_playlist_vector.at(0),TFile_ME1G_MC_TRUTH));
EmptyTFile_Map_MC_TRUTH.insert(std::make_pair(EmptyME_playlist_vector.at(1),TFile_ME1A_MC_TRUTH));
EmptyTFile_Map_MC_TRUTH.insert(std::make_pair(EmptyME_playlist_vector.at(2),TFile_ME1L_MC_TRUTH));
EmptyTFile_Map_MC_TRUTH.insert(std::make_pair(EmptyME_playlist_vector.at(3),TFile_ME1M_MC_TRUTH));
EmptyTFile_Map_MC_TRUTH.insert(std::make_pair(EmptyME_playlist_vector.at(4),TFile_ME1N_MC_TRUTH));

EmptyTFile_Map_DATA.insert(std::make_pair(EmptyME_playlist_vector.at(0),TFile_ME1G_DATA));
EmptyTFile_Map_DATA.insert(std::make_pair(EmptyME_playlist_vector.at(1),TFile_ME1A_DATA));
EmptyTFile_Map_DATA.insert(std::make_pair(EmptyME_playlist_vector.at(2),TFile_ME1L_DATA));
EmptyTFile_Map_DATA.insert(std::make_pair(EmptyME_playlist_vector.at(3),TFile_ME1M_DATA));
EmptyTFile_Map_DATA.insert(std::make_pair(EmptyME_playlist_vector.at(4),TFile_ME1N_DATA));

/////////////////////////////////////////////////////
// Full
/////////////////////////////////////////////////////
FullTFile_Map_MC_RECO.insert(std::make_pair(FullME_playlist_vector.at(0),TFile_ME1P_MC_RECO));
FullTFile_Map_MC_RECO.insert(std::make_pair(FullME_playlist_vector.at(1),TFile_ME1C_MC_RECO));
FullTFile_Map_MC_RECO.insert(std::make_pair(FullME_playlist_vector.at(2),TFile_ME1D_MC_RECO));
FullTFile_Map_MC_RECO.insert(std::make_pair(FullME_playlist_vector.at(3),TFile_ME1F_MC_RECO));
FullTFile_Map_MC_RECO.insert(std::make_pair(FullME_playlist_vector.at(4),TFile_ME1E_MC_RECO));

FullTFile_Map_MC_TRUTH.insert(std::make_pair(FullME_playlist_vector.at(0),TFile_ME1P_MC_TRUTH));
FullTFile_Map_MC_TRUTH.insert(std::make_pair(FullME_playlist_vector.at(1),TFile_ME1C_MC_TRUTH));
FullTFile_Map_MC_TRUTH.insert(std::make_pair(FullME_playlist_vector.at(2),TFile_ME1D_MC_TRUTH));
FullTFile_Map_MC_TRUTH.insert(std::make_pair(FullME_playlist_vector.at(3),TFile_ME1F_MC_TRUTH));
FullTFile_Map_MC_TRUTH.insert(std::make_pair(FullME_playlist_vector.at(4),TFile_ME1E_MC_TRUTH));

FullTFile_Map_DATA.insert(std::make_pair(FullME_playlist_vector.at(0),TFile_ME1P_DATA));
FullTFile_Map_DATA.insert(std::make_pair(FullME_playlist_vector.at(1),TFile_ME1C_DATA));
FullTFile_Map_DATA.insert(std::make_pair(FullME_playlist_vector.at(2),TFile_ME1D_DATA));
FullTFile_Map_DATA.insert(std::make_pair(FullME_playlist_vector.at(3),TFile_ME1F_DATA));
FullTFile_Map_DATA.insert(std::make_pair(FullME_playlist_vector.at(4),TFile_ME1E_DATA));
//////////////
///
/////////////


auto MuonVaribles = GetCrossSection2DVaribles();

auto outFile = TFile::Open("CrossSection2D.root", "RECREATE");

CrossSection_2DhistNames MuonPT_PZ_histNames = Constuct_2Dcrosssection_Histname(MuonVaribles[0]);
//CrossSection_2DhistNames MuonPT_PZ_FinnerhistNames = Constuct_2Dcrosssection_Histname(MuonVaribles[0], "_finebinning");
CrossSection_2DhistNames MuonE_Theta_histNames = Constuct_2Dcrosssection_Histname(MuonVaribles[1]);
std::cout<<"found names"<< std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<""<<std::endl;
Print_2Dcrosssection_Histname(MuonPT_PZ_histNames);
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
Print_2Dcrosssection_Histname(MuonE_Theta_histNames);
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"             Constructing Hists Playlist Map"<< std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;


ME_playlist_2DCrossSection_MAP FullCrossSection_Hist_Playlist_Map_MuonPT_PZ = Constuct_2Dcrosssection_Hists_PlaylistMap(MuonPT_PZ_histNames, FullTFile_Map_MC_RECO, FullTFile_Map_MC_TRUTH, FullTFile_Map_DATA );
ME_playlist_2DCrossSection_MAP EmptyCrossSection_Hist_Playlist_Map_MuonPT_PZ = Constuct_2Dcrosssection_Hists_PlaylistMap(MuonPT_PZ_histNames, EmptyTFile_Map_MC_RECO, EmptyTFile_Map_MC_TRUTH, EmptyTFile_Map_DATA );

ME_playlist_2DCrossSection_MAP FullCrossSection_Hist_Playlist_Map_MuonE_Theta = Constuct_2Dcrosssection_Hists_PlaylistMap(MuonE_Theta_histNames, FullTFile_Map_MC_RECO, FullTFile_Map_MC_TRUTH, FullTFile_Map_DATA );
ME_playlist_2DCrossSection_MAP EmptyCrossSection_Hist_Playlist_Map_MuonE_Theta = Constuct_2Dcrosssection_Hists_PlaylistMap(MuonE_Theta_histNames, EmptyTFile_Map_MC_RECO, EmptyTFile_Map_MC_TRUTH, EmptyTFile_Map_DATA );

//ME_playlist_2DCrossSection_MAP FullCrossSection_Hist_Playlist_Map_MuonPT_PZ_Finner = Constuct_2Dcrosssection_Hists_PlaylistMap(MuonPT_PZ_FinnerhistNames, FullTFile_Map_MC_RECO, FullTFile_Map_MC_TRUTH, FullTFile_Map_DATA );
//ME_playlist_2DCrossSection_MAP EmptyCrossSection_Hist_Playlist_Map_MuonPT_PZ_Finner = Constuct_2Dcrosssection_Hists_PlaylistMap(MuonPT_PZ_FinnerhistNames, EmptyTFile_Map_MC_RECO, EmptyTFile_Map_MC_TRUTH, EmptyTFile_Map_DATA );


//Playlist_MnvH2D_Map MCMapFinnerFull = Constuct_MnvH2DMap_FromME_playlist_TFileMAP(FullTFile_Map_MC_RECO, "h_Muon_PZ_PT_finebinning" );
//Playlist_MnvH2D_Map MCMapFinnerFull_Data = Constuct_MnvH2DMap_FromME_playlist_TFileMAP(FullTFile_Map_DATA, "h_Data_Muon_PZ_PT_finebinning" );
//Playlist_MnvH2D_Map MCMapFinnerEmpty = Constuct_MnvH2DMap_FromME_playlist_TFileMAP(EmptyTFile_Map_MC_RECO, "h_Muon_PZ_PT_finebinning" );
//Playlist_MnvH2D_Map MCMapFinnerEmpty_Data = Constuct_MnvH2DMap_FromME_playlist_TFileMAP(EmptyTFile_Map_DATA, "h_Data_Muon_PZ_PT_finebinning" );

//auto h_MCMapFinnerFull_total = Combine_2DHists_fromMAP(MCMapFinnerFull ,        FullME_playlist_vector.at(3) ,"MCMapFinnerFull_total");
//auto h_dataMapFinnerFull_total = Combine_2DHists_fromMAP(MCMapFinnerFull_Data ,  FullME_playlist_vector.at(3) ,"h_dataMapFinnerFull_total");
//auto h_MCMapFinnerEmpty_total = Combine_2DHists_fromMAP(MCMapFinnerEmpty ,        EmptyME_playlist_vector.at(3) ,"MCMapFinnerFull_total");
//auto h_dataMapFinnerEmpty_total = Combine_2DHists_fromMAP(MCMapFinnerEmpty_Data ,  EmptyME_playlist_vector.at(3) ,"h_dataMapFinnerFull_total");
//std::cout<<"h_MCMapFinnerFull_total Xbin = " << h_MCMapFinnerFull_total->GetNbinsX() << std::endl;
//std::cout<<"h_MCMapFinnerFull_total Ybin = " << h_MCMapFinnerFull_total->GetNbinsY() << std::endl;
//std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
//
//std::cout<<"MCMapFinnerFull_Data Xbin = " << h_dataMapFinnerFull_total->GetNbinsX() << std::endl;
//std::cout<<"MCMapFinnerFull_Data Ybin = " << h_dataMapFinnerFull_total->GetNbinsY() << std::endl;
//
//
//std::cout<<"h_MCMapFinnerEmpty_total Xbin = " << h_MCMapFinnerEmpty_total->GetNbinsX() << std::endl;
//std::cout<<"h_MCMapFinnerEmpty_total Ybin = " << h_MCMapFinnerEmpty_total->GetNbinsY() << std::endl;
//std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
//
//std::cout<<"MCMapFinnerEmpty_Data Xbin = " << h_dataMapFinnerEmpty_total->GetNbinsX() << std::endl;
//std::cout<<"MCMapFinnerEmpty_Data Ybin = " << h_dataMapFinnerEmpty_total->GetNbinsY() << std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"                          Combined Maps                     "<< std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;


std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"                          AddInteractionHistMap                     "<< std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~Full             ~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

AddInteraction2DHistMap_DISbreakdown(FullCrossSection_Hist_Playlist_Map_MuonPT_PZ,   FullTFile_Map_MC_TRUTH, "h_Muon_PZ_PT", "" );
AddInteraction2DHistMap_DISbreakdown(FullCrossSection_Hist_Playlist_Map_MuonE_Theta, FullTFile_Map_MC_TRUTH, "h_Muon_E_theta", "" );

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~Empty            ~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

AddInteraction2DHistMap_DISbreakdown(EmptyCrossSection_Hist_Playlist_Map_MuonPT_PZ,     EmptyTFile_Map_MC_TRUTH,  "h_Muon_PZ_PT", "");
AddInteraction2DHistMap_DISbreakdown(EmptyCrossSection_Hist_Playlist_Map_MuonE_Theta,    EmptyTFile_Map_MC_TRUTH, "h_Muon_E_theta" , "");


/////////

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"  Combine_crosssection_Hists_PlaylistMap_includeInteraction   "<< std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

std::cout<<"Full_CombinedHist_MuonPT_PZ "<<std::endl;
CrossSection2D_Hist Full_CombinedHist_MuonPT_PZ     =  Combine_2Dcrosssection_Hists_PlaylistMap_includeInteraction_DISbreakdown(FullCrossSection_Hist_Playlist_Map_MuonPT_PZ,         FullME_playlist_vector.at(3));
std::cout<<"Full_CombinedHist_MuonE_Theta "<<std::endl;
CrossSection2D_Hist Full_CombinedHist_MuonE_Theta    =  Combine_2Dcrosssection_Hists_PlaylistMap_includeInteraction_DISbreakdown(FullCrossSection_Hist_Playlist_Map_MuonE_Theta,        FullME_playlist_vector.at(3));
std::cout<<"Empty_CombinedHist_MuonPT_PZ "<<std::endl;
CrossSection2D_Hist Empty_CombinedHist_MuonPT_PZ      =  Combine_2Dcrosssection_Hists_PlaylistMap_includeInteraction_DISbreakdown(EmptyCrossSection_Hist_Playlist_Map_MuonPT_PZ,         EmptyME_playlist_vector.at(3));
std::cout<<"Empty_CombinedHist_MuonE_Theta "<<std::endl;
CrossSection2D_Hist Empty_CombinedHist_MuonE_Theta    =  Combine_2Dcrosssection_Hists_PlaylistMap_includeInteraction_DISbreakdown(EmptyCrossSection_Hist_Playlist_Map_MuonE_Theta,        EmptyME_playlist_vector.at(3));

//std::cout<<"Full_CombinedHist_MuonPT_PZ_finner "<<std::endl;
//CrossSection2D_Hist Full_CombinedHist_MuonPT_PZ_finner     = Combine_2Dcrosssection_Hists_PlaylistMap(FullCrossSection_Hist_Playlist_Map_MuonPT_PZ_Finner,         FullME_playlist_vector.at(3));
//CrossSection2D_Hist Empty_CombinedHist_MuonPT_PZ_finner     = Combine_2Dcrosssection_Hists_PlaylistMap(EmptyCrossSection_Hist_Playlist_Map_MuonPT_PZ_Finner,         EmptyME_playlist_vector.at(3));


std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~Normalize Hist ~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;


std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~GET POT    ~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
Pot_MapList EmptyPOT_MC_RECO_MAP = Constuct_POT_playlistMap(MAP_RootPath_Empty_MC_RECO, true);
Pot_MapList FullPOT_MC_RECO_MAP  = Constuct_POT_playlistMap(MAP_RootPath_Full_MC_RECO, true);

Pot_MapList EmptyPOT_DATA_MAP = Constuct_POT_playlistMap(MAP_RootPath_Empty_DATA, false);
Pot_MapList FullPOT_DATA_MAP  = Constuct_POT_playlistMap(MAP_RootPath_Full_DATA, false);
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~Combined  POT    ~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

const double Empty_MC_POT = Combine_POTFromMap(EmptyPOT_MC_RECO_MAP );
const double Full_MC_POT = Combine_POTFromMap(FullPOT_MC_RECO_MAP );

const double Empty_DATA_POT = Combine_POTFromMap(EmptyPOT_DATA_MAP );
const double Full_DATA_POT = Combine_POTFromMap(FullPOT_DATA_MAP );

const double Full_MC_Full_Data = Full_DATA_POT / Full_MC_POT;
const double Empty_MC_Full_Data = Full_DATA_POT / Empty_MC_POT;
const double Empty_Data_Full_Data = Full_DATA_POT / Empty_DATA_POT;

std::cout<< "Full_DATA_POT = " <<  Full_DATA_POT << std::endl;
std::cout<< "Full_MC_POT = " <<  Full_MC_POT << std::endl;

POT_Normalize_2DCrossSection_Hist(Full_CombinedHist_MuonPT_PZ ,   Full_MC_Full_Data);

POT_Normalize_2DCrossSection_Hist(Full_CombinedHist_MuonE_Theta , Full_MC_Full_Data);

POT_Normalize_2DCrossSection_Hist(Empty_CombinedHist_MuonPT_PZ,      Empty_MC_Full_Data ,Empty_Data_Full_Data, true );

POT_Normalize_2DCrossSection_Hist(Empty_CombinedHist_MuonE_Theta,    Empty_MC_Full_Data ,Empty_Data_Full_Data, true );

POT_Normalize_2DCrossSection_Hist_InteractionOnly_DISBreakdown(Full_CombinedHist_MuonPT_PZ,     Full_MC_Full_Data);
POT_Normalize_2DCrossSection_Hist_InteractionOnly_DISBreakdown(Full_CombinedHist_MuonE_Theta,    Full_MC_Full_Data);

POT_Normalize_2DCrossSection_Hist_InteractionOnly_DISBreakdown(Empty_CombinedHist_MuonPT_PZ,     Empty_MC_Full_Data);
POT_Normalize_2DCrossSection_Hist_InteractionOnly_DISBreakdown(Empty_CombinedHist_MuonE_Theta,    Empty_MC_Full_Data);
std::cout<<"POT noralizeing " <<  std::endl;
//
//POT_Normalize_2DCrossSection_Hist_RECO_Data(Full_CombinedHist_MuonPT_PZ_finner ,   Full_MC_Full_Data);
//POT_Normalize_2DCrossSection_Hist_RECO_Data(Empty_CombinedHist_MuonPT_PZ_finner,      Empty_MC_Full_Data ,Empty_Data_Full_Data, true );

//h_MCMapFinnerFull_total->Scale(Full_MC_Full_Data);
//h_MCMapFinnerEmpty_total->Scale(Empty_MC_Full_Data);
//h_dataMapFinnerEmpty_total->Scale(Empty_Data_Full_Data);
//
//h_MCMapFinnerFull_total->Add(h_MCMapFinnerEmpty_total,-1);
//h_dataMapFinnerFull_total->Add(h_dataMapFinnerEmpty_total,-1);
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~ Checking Binning   ~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

Check2D_NSignalBins(Full_CombinedHist_MuonPT_PZ,      "Full_CombinedHist_MuonPT_PZ");
Check2D_NSignalBins(Empty_CombinedHist_MuonPT_PZ,      "Empty_CombinedHist_MuonPT_PZ");

Check2D_NSignalBins(Full_CombinedHist_MuonE_Theta,      "Full_CombinedHist_MuonE_Theta");
Check2D_NSignalBins(Empty_CombinedHist_MuonE_Theta,      "Empty_CombinedHist_MuonE_Theta");

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~ Writing to File Current Hists   ~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

WritetoTFile_2DAll(Full_CombinedHist_MuonPT_PZ,     *outFile,  "h_MuonPT_PZ_Full");
WritetoTFile_2DAll(Full_CombinedHist_MuonE_Theta,    *outFile,  "h_MuonE_Theta_Full");

WritetoTFile_2DAll(Empty_CombinedHist_MuonPT_PZ,     *outFile,  "h_MuonPT_PZ_Empty");
WritetoTFile_2DAll(Empty_CombinedHist_MuonE_Theta,    *outFile,  "h_MuonE_Theta_Empty");

//WritetoTFile_2Dmain(Full_CombinedHist_MuonE,     *outFile,    "h_MuonE_Full_potnorm");
//WritetoTFile_2Dmain(Full_CombinedHist_MuonPZ,    *outFile,    "h_MuonPZ_Full_potnorm");
//WritetoTFile_2Dmain(Full_CombinedHist_MuonPT,    *outFile,    "h_MuonPT_Full_potnorm");
//WritetoTFile_2Dmain(Full_CombinedHist_MuonTheta, *outFile,    "h_MuonTheta_Full_potnorm");
//
//WritetoTFile_2Dmain(Empty_CombinedHist_MuonE,     *outFile,   "h_MuonE_Empty_potnorm");
//WritetoTFile_2Dmain(Empty_CombinedHist_MuonPZ,    *outFile,   "h_MuonPZ_Empty_potnorm");
//WritetoTFile_2Dmain(Empty_CombinedHist_MuonPT,    *outFile,   "h_MuonPT_Empty_potnorm");
//WritetoTFile_2Dmain(Empty_CombinedHist_MuonTheta, *outFile,   "h_MuonTheta_Empty_potnorm");

//WritetoTFile_Interaction_DISbreakdown(Full_CombinedHist_MuonPT_PZ,      *outFile, "h_Full_CombinedHist_MuonPT_PZ_potnorm");
//WritetoTFile_Interaction_DISbreakdown(Full_CombinedHist_MuonE_Theta,     *outFile, "h_Full_CombinedHist_MuonE_Theta_potnorm");
//
//WritetoTFile_Interaction_DISbreakdown(Empty_CombinedHist_MuonPT_PZ,      *outFile, "h_Empty_CombinedHist_MuonPT_PZ_potnorm");
//WritetoTFile_Interaction_DISbreakdown(Empty_CombinedHist_MuonE_Theta,     *outFile, "h_Empty_CombinedHist_MuonE_Theta_potnorm");

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~Subtraction Applied ~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~ applying Subtract_CrossSection_Hist ~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

std::cout<<"~~~~~~Full_CombinedHist_MuonPT_PZ~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

Subtract_CrossSection_Hist(Full_CombinedHist_MuonPT_PZ,     Empty_CombinedHist_MuonPT_PZ);
std::cout<<"~~~~~~Full_CombinedHist_MuonPT_PZfinner~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
//Subtract_CrossSection_Hist(Full_CombinedHist_MuonPT_PZ_finner,     Empty_CombinedHist_MuonPT_PZ_finner);

std::cout<<"~~~~~~Full_CombinedHist_MuonE_Theta~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
Subtract_CrossSection_Hist(Full_CombinedHist_MuonE_Theta,    Empty_CombinedHist_MuonE_Theta);

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~ applying Subtract_CrossSection_Hist_Interaction ~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~Full_CombinedHist_MuonPT_PZ~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

Subtract_CrossSection_Hist_Interaction_DISBreakdown(Full_CombinedHist_MuonPT_PZ,     Empty_CombinedHist_MuonPT_PZ); //unsure we have to subtract bg from truth
std::cout<<"~~~~~~Full_CombinedHist_MuonE_Theta~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

Subtract_CrossSection_Hist_Interaction_DISBreakdown(Full_CombinedHist_MuonE_Theta,    Empty_CombinedHist_MuonE_Theta);
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~Writing F-E ~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

WritetoTFile_2Dmain(Full_CombinedHist_MuonPT_PZ,     *outFile, "h_MuonPT_PZ_Full_sub_Empty_potnorm");
//WritetoTFile_2Dmain(Full_CombinedHist_MuonPT_PZ_finner,     *outFile, "h_MuonPT_PZ_Full_sub_Empty_potnorm_Fine");
WritetoTFile_2Dmain(Full_CombinedHist_MuonE_Theta,    *outFile, "h_MuonE_Theta_Full_sub_Empty_potnorm");

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~Writing True Xsection ~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~1~~"<<std::endl;

WritetoTFile_NormTRUE2DCrossSection(Full_CombinedHist_MuonPT_PZ,      *outFile,  "h_MuonPT_PZ_TrueCrossSection",       NHelium_MC, Full_DATA_POT);
std::cout<<"~~~~~~~~~2~~"<<std::endl;
WritetoTFile_NormTRUE2DCrossSection(Full_CombinedHist_MuonE_Theta,     *outFile,  "h_MuonE_Theta_TrueCrossSection",      NHelium_MC, Full_DATA_POT);

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~3~~"<<std::endl;
WritetoTFile_NormTRUECrossSection_Interaction_DISbreakdown(Full_CombinedHist_MuonPT_PZ,      *outFile,  "h_MuonPT_PZ",       NHelium_MC, Full_DATA_POT);
WritetoTFile_NormTRUECrossSection_Interaction_DISbreakdown(Full_CombinedHist_MuonE_Theta,     *outFile,  "h_MuonE_Theta",      NHelium_MC, Full_DATA_POT);
std::cout<<"~~~~~~~~~4~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~ UnFolding ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

sprintf(title_char, "%s h_mvnreponse_RECO before Pop ", title_base_char);

DrawPanel_SystematicErrorPlots_ProjectionY(Full_CombinedHist_MuonPT_PZ.h_mvnreponse_RECO,"P_{Z}", "P_{T}", title_char, text_title_pdf2 , .8, true, Print1Dplots );
sprintf(title_char, "%s h_mvnreponse_TRUE before Pop ", title_base_char);
DrawPanel_SystematicErrorPlots_ProjectionY(Full_CombinedHist_MuonPT_PZ.h_mvnreponse_TRUE,"P_{Z}", "P_{T}", title_char, text_title_pdf2 , .8, true, Print1Dplots );


sprintf(title_char, "%s h_mvnreponse_RECO before Pop ", title_base_char_theta);
DrawPanel_SystematicErrorPlots_ProjectionY(Full_CombinedHist_MuonE_Theta.h_mvnreponse_RECO,"E_{#mu}", "#theta_{#mu}", title_char, text_title_pdf2 , .8, true, Print1Dplots );
sprintf(title_char, "%s h_mvnreponse_TRUE before Pop ", title_base_char_theta);
DrawPanel_SystematicErrorPlots_ProjectionY(Full_CombinedHist_MuonE_Theta.h_mvnreponse_TRUE,"E_{#mu}", "#theta_{#mu}", title_char, text_title_pdf2 , .8, true, Print1Dplots );


std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~BG subtraction to Data~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

Full_CombinedHist_MuonPT_PZ.h_Data_Signal->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonPT_PZ.h_RECO_BG);
Full_CombinedHist_MuonE_Theta.h_Data_Signal->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonE_Theta.h_RECO_BG);

Full_CombinedHist_MuonPT_PZ.h_Data_Signal->Add(Full_CombinedHist_MuonPT_PZ.h_RECO_BG,-1);
Full_CombinedHist_MuonE_Theta.h_Data_Signal->Add(Full_CombinedHist_MuonE_Theta.h_RECO_BG,-1);


//////////////////
// PT vs Pz
/////////////////
sprintf(title_char, "%s Full_CombinedHist_MuonPT_PZ.h_Data_Signal [Folded Data, BG sub (F-E)] ", title_base_char);
Draw_2D_Panel_MC_Only_frompointer(Full_CombinedHist_MuonPT_PZ.h_Data_Signal, title_char, "Data F - E [Folded]",
"P_{Z}","GeV", "P_{T}", "GeV","NEvents" , 1.1, text_title_pdf2, true, false,
.03, .03, false);
Full_CombinedHist_MuonPT_PZ.h_Data_Signal->GetXaxis()->SetTitle("P_{Z}");
Full_CombinedHist_MuonPT_PZ.h_Data_Signal->GetYaxis()->SetTitle("P_{T}");
sprintf(title_char, "%s Full_CombinedHist_MuonPT_PZ.h_Data_Signal [Folded Data, BG sub (F-E)]  ", title_base_char);
DrawPanel_SystematicErrorPlots_ProjectionY(Full_CombinedHist_MuonPT_PZ.h_Data_Signal,"P_{Z}", "P_{T}", title_char, text_title_pdf2 , 1.2, true, Print1Dplots );

//////////////////
// E vs theta
/////////////////
sprintf(title_char, "%s Full_CombinedHist_MuonE_Theta.h_Data_Signal [Folded Data, BG sub (F-E)] ", title_base_char_theta);
Draw_2D_Panel_MC_Only_frompointer(Full_CombinedHist_MuonE_Theta.h_Data_Signal, title_char, "Data F - E [Folded]",
"#theta_{#mu}","Deg", "E_{#mu}", "GeV","NEvents" , 1.1, text_title_pdf2, true, false,
.03, .03, false);
Full_CombinedHist_MuonPT_PZ.h_Data_Signal->GetXaxis()->SetTitle("E_{#mu}");
Full_CombinedHist_MuonE_Theta.h_Data_Signal->GetYaxis()->SetTitle("#theta_{#mu}");
sprintf(title_char, "%s Full_CombinedHist_MuonE_Theta.h_Data_Signal  [Folded Data, BG sub (F-E)]", title_base_char);
DrawPanel_SystematicErrorPlots_ProjectionY(Full_CombinedHist_MuonE_Theta.h_Data_Signal,"E_{#mu}", "#theta_{#mu}", title_char, text_title_pdf2 , 1.2, true, Print1Dplots );




bool addSystematics = true;
bool useSysVariatedMigrations = false;
int num_iter=2;

//Full_CombinedHist_MuonPT_PZ.h_mvnreponse_Mig->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonPT_PZ.h_effNum);
//Full_CombinedHist_MuonPT_PZ.h_mvnreponse_RECO->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonPT_PZ.h_effNum);
//Full_CombinedHist_MuonPT_PZ.h_mvnreponse_TRUE->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonPT_PZ.h_effNum);

Full_CombinedHist_MuonPT_PZ.h_mvnreponse_Mig->Clone()->Write("h_MuonPT_PZ_mvnreponse_Mig");
Full_CombinedHist_MuonPT_PZ.h_mvnreponse_RECO->Clone()->Write("h_MuonPT_PZ_mvnreponse_RECO" );
Full_CombinedHist_MuonPT_PZ.h_mvnreponse_TRUE->Clone()->Write("h_MuonPT_PZ_mvnreponse_TRUE");

auto h_mvnreponse_Mig_clone = (PlotUtils::MnvH2D*)Full_CombinedHist_MuonPT_PZ.h_mvnreponse_Mig->Clone("h_mvnreponse_Mig_clone");
auto h_mvnreponse_RECO_clone = (PlotUtils::MnvH2D*)Full_CombinedHist_MuonPT_PZ.h_mvnreponse_RECO->Clone("h_mvnreponse_RECO_clone");
auto h_mvnreponse_TRUE_clone = (PlotUtils::MnvH2D*)Full_CombinedHist_MuonPT_PZ.h_mvnreponse_TRUE->Clone("h_mvnreponse_TRUE_clone");


//h_mvnreponse_Mig_clone->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonPT_PZ.h_effNum);
std::vector<std::string> error_names1 = h_mvnreponse_RECO_clone->GetVertErrorBandNames();
std::vector<std::string> error_names2 = h_mvnreponse_Mig_clone->GetVertErrorBandNames();
std::vector<std::string> error_names3 = h_mvnreponse_TRUE_clone->GetVertErrorBandNames();
std::vector<std::string> error_names4 = Full_CombinedHist_MuonPT_PZ.h_Data_Signal->GetVertErrorBandNames();
std::cout<<"error_names1.size(RECO) = "<< error_names1.size()<<std::endl;
std::cout<<"error_names2.size(MIG) = "<< error_names2.size()<<std::endl;
std::cout<<"error_names3.size(TRUE) = "<< error_names3.size()<<std::endl;
std::cout<<"error_names4.size(Data) = "<< error_names4.size()<<std::endl;

h_mvnreponse_TRUE_clone->GetXaxis()->SetTitle("P_{T}");
h_mvnreponse_TRUE_clone->GetYaxis()->SetTitle("P_{Z}");

h_mvnreponse_RECO_clone->GetXaxis()->SetTitle("P_{T}");
h_mvnreponse_RECO_clone->GetYaxis()->SetTitle("P_{Z}");
Draw2DHist(h_mvnreponse_TRUE_clone, "P_{T}", "P_{Z}", "NEvent" , "h_mvnreponse_TRUE_clone" , text_title_pdf2, can,mnv_plot);
Draw2DHist(h_mvnreponse_RECO_clone, "P_{T}", "P_{Z}", "NEvent" , "h_mvnreponse_RECO_clone" , text_title_pdf2, can,mnv_plot);

sprintf(title_char, "%s h_mvnreponse_RECO_clone ", title_base_char);
DrawPanel_SystematicErrorPlots_ProjectionY(h_mvnreponse_RECO_clone,"P_{Z}", "P_{T}", title_char, text_title_pdf2 , .8, true, Print1Dplots );
sprintf(title_char, "%s h_mvnreponse_TRUE_clone ", title_base_char);
DrawPanel_SystematicErrorPlots_ProjectionY(h_mvnreponse_TRUE_clone,"P_{Z}", "P_{T}", title_char, text_title_pdf2 , .8, true, Print1Dplots );
DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE FSI", h_mvnreponse_RECO_clone, "P_{Z}", "P_{T}",  title_base_char, text_title_pdf2, .15, true, false  );
DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE Cross Section", h_mvnreponse_RECO_clone, "P_{Z}", "P_{T}",  title_base_char, text_title_pdf2, .15, true, false  );
DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "Vertex Smearing", h_mvnreponse_RECO_clone, "P_{Z}", "P_{T}",  title_base_char, text_title_pdf2, .4, true, false  );
DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "2p2h RPA Mvn1Tune", h_mvnreponse_RECO_clone, "P_{Z}", "P_{T}",  title_base_char, text_title_pdf2, .4, true, false  );
DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "Beam Angle", h_mvnreponse_RECO_clone, "P_{Z}", "P_{T}",  title_base_char, text_title_pdf2, .4, true, false  );



//auto h_FoldedData_MuonPT_PZ = (PlotUtils::MnvH2D*)Full_CombinedHist_MuonPT_PZ.h_Data_Signal->Clone("h_FoldedData_MuonPT_PZ");
MnvH2D* h_unfoldedData_MuonPT_PZ = nullptr;
MnvH2D* h_unfoldedData_MuonE_Theta = nullptr;
std::cout<<"Adding missing error bands"<<std::endl;


std::cout<<"Finished error bands"<<std::endl;
std::cout<<"Unfolding h_unfoldedData_MuonPT_PZ"<<std::endl;
h_unfoldedData_MuonPT_PZ = UnfoldHist2D_new(Full_CombinedHist_MuonPT_PZ.h_Data_Signal, Full_CombinedHist_MuonPT_PZ.h_mvnreponse_RECO, Full_CombinedHist_MuonPT_PZ.h_mvnreponse_TRUE, Full_CombinedHist_MuonPT_PZ.h_mvnreponse_Mig, num_iter, addSystematics, useSysVariatedMigrations );
//h_unfoldedData_MuonPT_PZ = UnfoldHistOld(Full_CombinedHist_MuonPT_PZ.h_Data_Signal, Full_CombinedHist_MuonPT_PZ.h_RECO,
  //Full_CombinedHist_MuonPT_PZ.h_mvnreponse_RECO, Full_CombinedHist_MuonPT_PZ.h_mvnreponse_TRUE, Full_CombinedHist_MuonPT_PZ.h_mvnreponse_Mig, num_iter, mnv_plot, text_title_pdf2  );
h_unfoldedData_MuonPT_PZ->ModifyStatisticalUnc(7.0, "unfoldingCov");
//h_unfoldedData_MuonPT_PZ = UnfoldHist2D_new(Full_CombinedHist_MuonPT_PZ.h_Data_Signal, h_mvnreponse_RECO_clone, h_mvnreponse_TRUE_clone,h_mvnreponse_Mig_clone, num_iter,addSystematics,useSysVariatedMigrations );
h_unfoldedData_MuonPT_PZ->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonPT_PZ.h_effNum);
h_unfoldedData_MuonPT_PZ->Clone()->Write("h_MuonPT_PZ_unfolded_data");
sprintf(title_char, "%s h_unfoldedData_MuonPT_PZ Unfolding and AddMissingErrorBandsAndFillWithCV applied  ", title_base_char);
h_unfoldedData_MuonPT_PZ->GetXaxis()->SetTitle("P_{Z}");
h_unfoldedData_MuonPT_PZ->GetYaxis()->SetTitle("P_{T}");
std::cout<<"About to unfold"<<std::endl;
//bool data_unfolded = unfold.UnfoldHisto2D(h_unfoldedData_MuonPT_PZ, h_mvnreponse_Mig_clone, h_mvnreponse_RECO_clone,h_mvnreponse_TRUE_clone, h_FoldedData_MuonPT_PZ , num_iter,true,true);
sprintf(title_char, "%s h_unfoldedData_MuonPT_PZ: Right after unfolding", title_base_char);
DrawPanel_SystematicErrorPlots_ProjectionY(h_unfoldedData_MuonPT_PZ,"P_{Z}", "P_{T}", title_char, text_title_pdf2 , .8, true, Print1Dplots );

sprintf(title_char, "%s h_unfoldedData_MuonPT_PZ: Right after unfolding", title_base_char);
Draw_2D_Panel_MC_Only_frompointer(h_unfoldedData_MuonPT_PZ, title_char, "Data F - E [unFolded]",
"P_{Z}","GeV", "P_{T}", "GeV","NEvents" , 1.1, text_title_pdf2, true, false,
.03, .03, false);




std::cout<<"Finished  unfolding PT_PZ  trying to do Muon E vs Theta"<<std::endl;

Full_CombinedHist_MuonE_Theta.h_mvnreponse_Mig->Clone()->Write("h_MuonE_Theta_mvnreponse_Mig");
Full_CombinedHist_MuonE_Theta.h_mvnreponse_RECO->Clone()->Write("h_MuonE_Theta_mvnreponse_RECO");
Full_CombinedHist_MuonE_Theta.h_mvnreponse_TRUE->Clone()->Write("h_MuonE_Theta_mvnreponse_TRUE");
//
auto h_mvnreponse_Mig_clone2 = (PlotUtils::MnvH2D*)Full_CombinedHist_MuonE_Theta.h_mvnreponse_Mig->Clone("h_mvnreponse_Mig_clone2");
auto h_mvnreponse_RECO_clone2 = (PlotUtils::MnvH2D*)Full_CombinedHist_MuonE_Theta.h_mvnreponse_RECO->Clone("h_mvnreponse_RECO_clone2");
auto h_mvnreponse_TRUE_clone2 = (PlotUtils::MnvH2D*)Full_CombinedHist_MuonE_Theta.h_mvnreponse_TRUE->Clone("h_mvnreponse_TRUE_clone2");

h_mvnreponse_TRUE_clone2->GetXaxis()->SetTitle("#theta_{#mu}");
h_mvnreponse_TRUE_clone2->GetYaxis()->SetTitle("E_{#mu}");

h_mvnreponse_RECO_clone->GetXaxis()->SetTitle("#theta_{#mu}");
h_mvnreponse_RECO_clone->GetYaxis()->SetTitle("E_{#mu}");
Draw2DHist(h_mvnreponse_TRUE_clone, "#theta_{#mu}", "E_{#mu}", "NEvent" , "h_mvnreponse_TRUE_clone" , text_title_pdf2, can,mnv_plot);
Draw2DHist(h_mvnreponse_RECO_clone, "#theta_{#mu}", "E_{#mu}", "NEvent" , "h_mvnreponse_RECO_clone" , text_title_pdf2, can,mnv_plot);

sprintf(title_char, "%s h_mvnreponse_RECO_clone ", title_base_char_theta);
DrawPanel_SystematicErrorPlots_ProjectionY(h_mvnreponse_RECO_clone2,"E_{#mu}", "#theta_{#mu}", title_char, text_title_pdf2 , .8, true, Print1Dplots );
sprintf(title_char, "%s h_mvnreponse_TRUE_clone ", title_base_char_theta);
DrawPanel_SystematicErrorPlots_ProjectionY(h_mvnreponse_TRUE_clone2,"E_{#mu}", "#theta_{#mu}", title_char, text_title_pdf2 , .8, true, Print1Dplots );
DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE FSI", h_mvnreponse_RECO_clone2, "E_{#mu}", "#theta_{#mu}",  title_base_char, text_title_pdf2, .15, true, false  );
DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE Cross Section", h_mvnreponse_RECO_clone2, "E_{#mu}", "#theta_{#mu}",  title_base_char, text_title_pdf2, .15, true, false  );
DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "Vertex Smearing", h_mvnreponse_RECO_clone2, "E_{#mu}", "#theta_{#mu}",  title_base_char, text_title_pdf2, .4, true, false  );
DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "2p2h RPA Mvn1Tune", h_mvnreponse_RECO_clone2, "E_{#mu}", "#theta_{#mu}",  title_base_char, text_title_pdf2, .4, true, false  );
DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "Beam Angle", h_mvnreponse_RECO_clone2, "E_{#mu}", "#theta_{#mu}",  title_base_char, text_title_pdf2, .4, true, false  );

std::cout<<"Unfolding unfoldedMuonE_Theta_data"<<std::endl;
h_unfoldedData_MuonE_Theta = UnfoldHist2D_new(Full_CombinedHist_MuonE_Theta.h_Data_Signal,Full_CombinedHist_MuonE_Theta.h_mvnreponse_RECO, Full_CombinedHist_MuonE_Theta.h_mvnreponse_TRUE,Full_CombinedHist_MuonE_Theta.h_mvnreponse_Mig,num_iter,addSystematics,useSysVariatedMigrations );
h_unfoldedData_MuonE_Theta->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonE_Theta.h_effNum);
h_unfoldedData_MuonE_Theta->Clone()->Write("h_MuonE_Theta_unfolded_data");
//
sprintf(title_char, "%s h_unfoldedData_MuonE_Theta: Right after unfolding", title_base_char);
Draw_2D_Panel_MC_Only_frompointer(h_unfoldedData_MuonE_Theta, title_char, "Data F - E [unFolded]",
"E_{#mu}","GeV", "#theta_{#mu}", "Deg","NEvents" , 1.1, text_title_pdf2, true, false,
.03, .03, false);
//
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~ efficiency Correct ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
AddErrorBands_TOEffDom(Full_CombinedHist_MuonPT_PZ);
Full_CombinedHist_MuonPT_PZ.h_effNum->Divide(Full_CombinedHist_MuonPT_PZ.h_effNum, Full_CombinedHist_MuonPT_PZ.h_effDom, 1.0,1.0,"B");
Full_CombinedHist_MuonPT_PZ.h_effNum->Clone()->Write("h_MuonPT_PZ_efficiency");
h_unfoldedData_MuonPT_PZ->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonPT_PZ.h_effNum);


h_unfoldedData_MuonPT_PZ->Divide(h_unfoldedData_MuonPT_PZ, Full_CombinedHist_MuonPT_PZ.h_effNum);
h_unfoldedData_MuonPT_PZ->Clone()->Write("h_MuonPT_PZ_unfolded_data_effcorrected");
///////////////////////////////
sprintf(title_char, "%s h_unfoldedData_MuonPT_PZ: Right after Efficiency correction", title_base_char);

//DrawPanel_SystematicErrorPlots_ProjectionY(h_unfoldedData_MuonPT_PZ,"P_{Z}", "P_{T}", title_char, text_title_pdf2 , .8, true, Print1Dplots );



AddErrorBands_TOEffDom(Full_CombinedHist_MuonE_Theta);
Full_CombinedHist_MuonE_Theta.h_effNum->Divide(Full_CombinedHist_MuonE_Theta.h_effNum, Full_CombinedHist_MuonE_Theta.h_effDom, 1.0,1.0,"B");
Full_CombinedHist_MuonE_Theta.h_effNum->Clone()->Write("h_MuonE_Theta_efficiency");
h_unfoldedData_MuonE_Theta->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonE_Theta.h_effNum);
h_unfoldedData_MuonE_Theta->Divide(h_unfoldedData_MuonE_Theta, Full_CombinedHist_MuonE_Theta.h_effNum);
h_unfoldedData_MuonE_Theta->Clone()->Write("h_MuonE_Theta_unfolded_data_effcorrected");
////////////////////////////////
//DrawPanel_SystematicErrorPlots_ProjectionY(unfoldedMuonE_Theta_data,"E_{#mu}", "#theta_{#mu}", title_char, text_title_pdf2 , .8, true, Print1Dplots );


std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~ Cross Section ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

Full_CombinedHist_MuonPT_PZ.h_flux->AddMissingErrorBandsAndFillWithCV( *Full_CombinedHist_MuonPT_PZ.h_effNum );
Full_CombinedHist_MuonE_Theta.h_flux->AddMissingErrorBandsAndFillWithCV( *Full_CombinedHist_MuonE_Theta.h_effNum );

auto h_crossSection_MuonPT_PZ = normalize2D(h_unfoldedData_MuonPT_PZ, Full_CombinedHist_MuonPT_PZ.h_flux, NHelium, Full_DATA_POT);
h_crossSection_MuonPT_PZ->Clone()->Write("h_MuonPT_PZ_CrossSection_data_unfolded");

auto h_crossSection_MuonE_Theta = normalize2D(h_unfoldedData_MuonE_Theta, Full_CombinedHist_MuonE_Theta.h_flux, NHelium, Full_DATA_POT);
h_crossSection_MuonE_Theta->Clone()->Write("h_MuonE_Theta_CrossSection_data_unfolded");



//h_MCMapFinnerFull_total->Clone()->Write("h_MuonPT_PZ_Finner_MC");
//h_dataMapFinnerFull_total->Clone()->Write("h_MuonPT_PZ_Finner_data");


std::cout<<"trying to divide"<<std::endl;
//h_dataMapFinnerFull_total->Divide(h_dataMapFinnerFull_total,h_MCMapFinnerFull_total);
//h_dataMapFinnerFull_total->Clone()->Write("h_MuonPT_PZ_Finner_RATIO");

can -> Print(text_title_pdf3);
can->Close();
outFile->Close();

} // end of RunCrossSectionExtractor


/////////////////////////////////////////////
std::vector<Muon2DVar> GetCrossSection2DVaribles() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<Muon2DVar> MuonVars;

  MuonVars.push_back(kPT_PZ);
  MuonVars.push_back(kE_theta);


  return MuonVars;
//#endif
}





std::vector<ME_helium_Playlists> GetFullPlayListVector() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ME_helium_Playlists> Playlist;

  Playlist.push_back(kME1P);
  Playlist.push_back(kME1C);
  Playlist.push_back(kME1D);
  Playlist.push_back(kME1F);
  Playlist.push_back(kME1E);


  return Playlist;
//#endif
}

std::vector<ME_helium_Playlists> GetEmptyPlayListVector() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ME_helium_Playlists> Playlist;
  Playlist.push_back(kME1G);
  Playlist.push_back(kME1A);
  Playlist.push_back(kME1L);
  Playlist.push_back(kME1M);
  Playlist.push_back(kME1N);


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
