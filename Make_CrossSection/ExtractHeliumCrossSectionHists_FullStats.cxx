//Author: Christian Nguyen
// Helium Cross Section Extractor.cxx
// Started to Build: May 17 2020
//email: christian2nguyen@ufl.edu

#include "ExtractHeliumCrossSectionHists.h"

std::string OUTputRoot_pathway = "/minerva/data/users/cnguyen/CrossSection_Hists_ALLPlaylists";
std::vector<MuonVar> GetCrossSectionVaribles();
std::vector<ME_helium_Playlists> GetFullPlayListVector();
std::vector<ME_helium_Playlists> GetEmptyPlayListVector();
void Make_latexTables_CutMap(CutMap inputMap,char *playlist_name_char, std::string CyroTank_status );
void Playlist_CutTableLatex_Efficiency_Purity(CutMap inputMap , char *playlist_name_char, std::string CyroTank_status   );
void RunCrossSectionExtractor(bool &my_norm, bool &my_debug, int &Print_Systematics){
TH1::AddDirectory(false);
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~       Starting CrossSection Extraction for Helium 1D: ~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
auto FullME_playlist_vector = GetFullPlayListVector();
auto EmptyME_playlist_vector = GetEmptyPlayListVector();
  std::vector<ME_helium_Playlists> Playlist_Combined;
for(auto cat:FullME_playlist_vector ){Playlist_Combined.push_back(cat);}
for(auto cat:EmptyME_playlist_vector ){Playlist_Combined.push_back(cat);}




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
auto PlaylistME_1P_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1P_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";
auto PlaylistME_1C_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1C_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";
auto PlaylistME_1D_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1D_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";
auto PlaylistME_1F_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1F_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";
auto PlaylistME_1E_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1E_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";

//Flux

auto PlaylistME_1P_MC_path_Flux = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2Dminervame1P_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";
auto PlaylistME_1C_MC_path_Flux = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2Dminervame1C_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";
auto PlaylistME_1D_MC_path_Flux = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2Dminervame1D_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";
auto PlaylistME_1F_MC_path_Flux = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2Dminervame1F_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";
auto PlaylistME_1E_MC_path_Flux = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2Dminervame1E_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";


/////////////
// Empty Playlist
/////////////
auto PlaylistME_1G_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1G_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";
auto PlaylistME_1A_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1A_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";
auto PlaylistME_1L_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1L_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";
auto PlaylistME_1M_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1M_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";
auto PlaylistME_1N_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1N_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";
/////////////
// Full Playlist Data
/////////////

auto PlaylistME_1P_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1P_Data_Fid.root";
auto PlaylistME_1C_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1C_Data_Fid.root";
auto PlaylistME_1D_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1D_Data_Fid.root";
auto PlaylistME_1F_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1F_Data_Fid.root";
auto PlaylistME_1E_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1E_Data_Fid.root";

/////////////
// Empty Playlist  Data
/////////////

auto PlaylistME_1G_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1G_Data_Fid.root";
auto PlaylistME_1A_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1A_Data_Fid.root";
auto PlaylistME_1L_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1L_Data_Fid.root";
auto PlaylistME_1M_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1M_Data_Fid.root";
auto PlaylistME_1N_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1N_Data_Fid.root";

/////////////
// Full Playlist Truth
/////////////


auto PlaylistME_1P_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1P_TRUTH_All_SysErrorsOn_Fid.root";
auto PlaylistME_1C_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1C_TRUTH_All_SysErrorsOn_Fid.root";
auto PlaylistME_1D_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1D_TRUTH_All_SysErrorsOn_Fid.root";
auto PlaylistME_1F_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1F_TRUTH_All_SysErrorsOn_Fid.root";
auto PlaylistME_1E_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1E_TRUTH_All_SysErrorsOn_Fid.root";



auto PlaylistME_1P_MC_TRUTH_path_Flux = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_FLUX_minervame1P_TRUTH_All_SysErrorsOn_Fid.root";
auto PlaylistME_1C_MC_TRUTH_path_Flux = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_FLUX_minervame1C_TRUTH_All_SysErrorsOn_Fid.root";
auto PlaylistME_1D_MC_TRUTH_path_Flux = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_FLUX_minervame1D_TRUTH_All_SysErrorsOn_Fid.root";
auto PlaylistME_1F_MC_TRUTH_path_Flux = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_FLUX_minervame1F_TRUTH_All_SysErrorsOn_Fid.root";
auto PlaylistME_1E_MC_TRUTH_path_Flux = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_FLUX_minervame1E_TRUTH_All_SysErrorsOn_Fid.root";

/////////////
// Empty Playlist  Truth
/////////////

auto PlaylistME_1G_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1G_TRUTH_All_SysErrorsOn_Fid.root";
auto PlaylistME_1A_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1A_TRUTH_All_SysErrorsOn_Fid.root";
auto PlaylistME_1L_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1L_TRUTH_All_SysErrorsOn_Fid.root";
auto PlaylistME_1M_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1M_TRUTH_All_SysErrorsOn_Fid.root";
auto PlaylistME_1N_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1N_TRUTH_All_SysErrorsOn_Fid.root";

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


//TFile *TFile_ME1P_MC_RECO_Flux = new TFile(PlaylistME_1P_MC_path_Flux);
//TFile *TFile_ME1C_MC_RECO_Flux = new TFile(PlaylistME_1C_MC_path_Flux);
//TFile *TFile_ME1D_MC_RECO_Flux = new TFile(PlaylistME_1D_MC_path_Flux);
//TFile *TFile_ME1E_MC_RECO_Flux = new TFile(PlaylistME_1E_MC_path_Flux);
//TFile *TFile_ME1F_MC_RECO_Flux = new TFile(PlaylistME_1F_MC_path_Flux);


TFile *TFile_ME1P_MC_TRUTH = new TFile(PlaylistME_1P_MC_TRUTH_path);
TFile *TFile_ME1C_MC_TRUTH = new TFile(PlaylistME_1C_MC_TRUTH_path);
TFile *TFile_ME1D_MC_TRUTH = new TFile(PlaylistME_1D_MC_TRUTH_path);
TFile *TFile_ME1E_MC_TRUTH = new TFile(PlaylistME_1E_MC_TRUTH_path);
TFile *TFile_ME1F_MC_TRUTH = new TFile(PlaylistME_1F_MC_TRUTH_path);


TFile *TFile_ME1P_MC_TRUTH_Flux = new TFile(PlaylistME_1P_MC_TRUTH_path_Flux);
TFile *TFile_ME1C_MC_TRUTH_Flux = new TFile(PlaylistME_1C_MC_TRUTH_path_Flux);
TFile *TFile_ME1D_MC_TRUTH_Flux = new TFile(PlaylistME_1D_MC_TRUTH_path_Flux);
TFile *TFile_ME1E_MC_TRUTH_Flux = new TFile(PlaylistME_1E_MC_TRUTH_path_Flux);
TFile *TFile_ME1F_MC_TRUTH_Flux = new TFile(PlaylistME_1F_MC_TRUTH_path_Flux);


TFile *TFile_ME1P_DATA = new TFile(PlaylistME_1P_Data_path);
TFile *TFile_ME1C_DATA = new TFile(PlaylistME_1C_Data_path);
TFile *TFile_ME1D_DATA = new TFile(PlaylistME_1D_Data_path);
TFile *TFile_ME1E_DATA = new TFile(PlaylistME_1E_Data_path);
TFile *TFile_ME1F_DATA = new TFile(PlaylistME_1F_Data_path);

ME_playlist_TFileMAP EmptyTFile_Map_MC_RECO;
ME_playlist_TFileMAP EmptyTFile_Map_MC_TRUTH;
ME_playlist_TFileMAP EmptyTFile_Map_DATA;

ME_playlist_TFileMAP FullTFile_Map_MC_RECO;
//ME_playlist_TFileMAP FullTFile_Map_MC_RECO_Flux;
ME_playlist_TFileMAP FullTFile_Map_MC_TRUTH;
ME_playlist_TFileMAP FullTFile_Map_MC_TRUTH_Flux;
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



//FullTFile_Map_MC_RECO_Flux.insert(std::make_pair(FullME_playlist_vector.at(0),TFile_ME1P_MC_RECO_Flux));
//FullTFile_Map_MC_RECO_Flux.insert(std::make_pair(FullME_playlist_vector.at(1),TFile_ME1C_MC_RECO_Flux));
//FullTFile_Map_MC_RECO_Flux.insert(std::make_pair(FullME_playlist_vector.at(2),TFile_ME1D_MC_RECO_Flux));
//FullTFile_Map_MC_RECO_Flux.insert(std::make_pair(FullME_playlist_vector.at(3),TFile_ME1F_MC_RECO_Flux));
//FullTFile_Map_MC_RECO_Flux.insert(std::make_pair(FullME_playlist_vector.at(4),TFile_ME1E_MC_RECO_Flux));




FullTFile_Map_MC_TRUTH.insert(std::make_pair(FullME_playlist_vector.at(0),TFile_ME1P_MC_TRUTH));
FullTFile_Map_MC_TRUTH.insert(std::make_pair(FullME_playlist_vector.at(1),TFile_ME1C_MC_TRUTH));
FullTFile_Map_MC_TRUTH.insert(std::make_pair(FullME_playlist_vector.at(2),TFile_ME1D_MC_TRUTH));
FullTFile_Map_MC_TRUTH.insert(std::make_pair(FullME_playlist_vector.at(3),TFile_ME1F_MC_TRUTH));
FullTFile_Map_MC_TRUTH.insert(std::make_pair(FullME_playlist_vector.at(4),TFile_ME1E_MC_TRUTH));

FullTFile_Map_MC_TRUTH_Flux.insert(std::make_pair(FullME_playlist_vector.at(0),TFile_ME1P_MC_TRUTH_Flux));
FullTFile_Map_MC_TRUTH_Flux.insert(std::make_pair(FullME_playlist_vector.at(1),TFile_ME1C_MC_TRUTH_Flux));
FullTFile_Map_MC_TRUTH_Flux.insert(std::make_pair(FullME_playlist_vector.at(2),TFile_ME1D_MC_TRUTH_Flux));
FullTFile_Map_MC_TRUTH_Flux.insert(std::make_pair(FullME_playlist_vector.at(3),TFile_ME1F_MC_TRUTH_Flux));
FullTFile_Map_MC_TRUTH_Flux.insert(std::make_pair(FullME_playlist_vector.at(4),TFile_ME1E_MC_TRUTH_Flux));




FullTFile_Map_DATA.insert(std::make_pair(FullME_playlist_vector.at(0),TFile_ME1P_DATA));
FullTFile_Map_DATA.insert(std::make_pair(FullME_playlist_vector.at(1),TFile_ME1C_DATA));
FullTFile_Map_DATA.insert(std::make_pair(FullME_playlist_vector.at(2),TFile_ME1D_DATA));
FullTFile_Map_DATA.insert(std::make_pair(FullME_playlist_vector.at(3),TFile_ME1F_DATA));
FullTFile_Map_DATA.insert(std::make_pair(FullME_playlist_vector.at(4),TFile_ME1E_DATA));
//////////////
///
/////////////


auto MuonVaribles = GetCrossSectionVaribles();

auto outFile = TFile::Open("CrossSection.root", "RECREATE");

CrossSection_histNames MuonE_names     = Constuct_crosssection_Histname(MuonVaribles[0]);
CrossSection_histNames MuonPZ_names    = Constuct_crosssection_Histname(MuonVaribles[1]);
CrossSection_histNames MuonPT_names    = Constuct_crosssection_Histname(MuonVaribles[2]);
CrossSection_histNames MuonTheta_names = Constuct_crosssection_Histname(MuonVaribles[3]);
std::cout<<"found names"<< std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<""<<std::endl;
Print_crosssection_Histname(MuonE_names);
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
Print_crosssection_Histname(MuonPZ_names);
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
Print_crosssection_Histname(MuonPT_names);
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
Print_crosssection_Histname(MuonTheta_names);
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"             Constructing Hists Playlist Map"<< std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;



ME_playlist_CrossSection_MAP FullCrossSection_Hist_Playlist_Map_MuonE = Constuct_crosssection_Hists_PlaylistMap(MuonE_names, FullTFile_Map_MC_RECO, FullTFile_Map_MC_TRUTH, FullTFile_Map_DATA );
ME_playlist_CrossSection_MAP EmptyCrossSection_Hist_Playlist_Map_MuonE = Constuct_crosssection_Hists_PlaylistMap(MuonE_names, EmptyTFile_Map_MC_RECO, EmptyTFile_Map_MC_TRUTH, EmptyTFile_Map_DATA );

ME_playlist_CrossSection_MAP FullCrossSection_Hist_Playlist_Map_MuonPZ = Constuct_crosssection_Hists_PlaylistMap(MuonPZ_names, FullTFile_Map_MC_RECO, FullTFile_Map_MC_TRUTH, FullTFile_Map_DATA );
ME_playlist_CrossSection_MAP EmptyCrossSection_Hist_Playlist_Map_MuonPZ = Constuct_crosssection_Hists_PlaylistMap(MuonPZ_names, EmptyTFile_Map_MC_RECO, EmptyTFile_Map_MC_TRUTH, EmptyTFile_Map_DATA );

ME_playlist_CrossSection_MAP FullCrossSection_Hist_Playlist_Map_MuonPT = Constuct_crosssection_Hists_PlaylistMap(MuonPT_names, FullTFile_Map_MC_RECO, FullTFile_Map_MC_TRUTH, FullTFile_Map_DATA );
ME_playlist_CrossSection_MAP EmptyCrossSection_Hist_Playlist_Map_MuonPT = Constuct_crosssection_Hists_PlaylistMap(MuonPT_names, EmptyTFile_Map_MC_RECO, EmptyTFile_Map_MC_TRUTH, EmptyTFile_Map_DATA );

ME_playlist_CrossSection_MAP FullCrossSection_Hist_Playlist_Map_MuonTheta = Constuct_crosssection_Hists_PlaylistMap(MuonTheta_names, FullTFile_Map_MC_RECO, FullTFile_Map_MC_TRUTH, FullTFile_Map_DATA );
ME_playlist_CrossSection_MAP EmptyCrossSection_Hist_Playlist_Map_MuonTheta = Constuct_crosssection_Hists_PlaylistMap(MuonTheta_names, EmptyTFile_Map_MC_RECO, EmptyTFile_Map_MC_TRUTH, EmptyTFile_Map_DATA );

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
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

AddInteractionHistMap_DISbreakdown(FullCrossSection_Hist_Playlist_Map_MuonE,     FullTFile_Map_MC_TRUTH, MuonE_names.hist_Eff_denominator_name, "DISBreakdown" );
AddInteractionHistMap_DISbreakdown(FullCrossSection_Hist_Playlist_Map_MuonPT,    FullTFile_Map_MC_TRUTH, MuonPT_names.hist_Eff_denominator_name, "DISBreakdown" );
AddInteractionHistMap_DISbreakdown(FullCrossSection_Hist_Playlist_Map_MuonPZ,    FullTFile_Map_MC_TRUTH, MuonPZ_names.hist_Eff_denominator_name, "DISBreakdown" );
AddInteractionHistMap_DISbreakdown(FullCrossSection_Hist_Playlist_Map_MuonTheta, FullTFile_Map_MC_TRUTH, MuonTheta_names.hist_Eff_denominator_name, "DISBreakdown" );

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~Empty            ~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

AddInteractionHistMap_DISbreakdown(EmptyCrossSection_Hist_Playlist_Map_MuonE,     EmptyTFile_Map_MC_TRUTH, MuonE_names.hist_Eff_denominator_name , "DISBreakdown");
AddInteractionHistMap_DISbreakdown(EmptyCrossSection_Hist_Playlist_Map_MuonPT,    EmptyTFile_Map_MC_TRUTH, MuonPT_names.hist_Eff_denominator_name , "DISBreakdown");
AddInteractionHistMap_DISbreakdown(EmptyCrossSection_Hist_Playlist_Map_MuonPZ,    EmptyTFile_Map_MC_TRUTH, MuonPZ_names.hist_Eff_denominator_name , "DISBreakdown");
AddInteractionHistMap_DISbreakdown(EmptyCrossSection_Hist_Playlist_Map_MuonTheta, EmptyTFile_Map_MC_TRUTH, MuonTheta_names.hist_Eff_denominator_name , "DISBreakdown");



/////////

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"  Combine_crosssection_Hists_PlaylistMap_includeInteraction   "<< std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;


CrossSection_Hist Full_CombinedHist_MuonE     =  Combine_crosssection_Hists_PlaylistMap_includeInteraction_DISbreakdown(FullCrossSection_Hist_Playlist_Map_MuonE,         FullME_playlist_vector.at(3));
CrossSection_Hist Full_CombinedHist_MuonPZ    =  Combine_crosssection_Hists_PlaylistMap_includeInteraction_DISbreakdown(FullCrossSection_Hist_Playlist_Map_MuonPZ,        FullME_playlist_vector.at(3));
CrossSection_Hist Full_CombinedHist_MuonPT    =  Combine_crosssection_Hists_PlaylistMap_includeInteraction_DISbreakdown(FullCrossSection_Hist_Playlist_Map_MuonPT,        FullME_playlist_vector.at(3));
CrossSection_Hist Full_CombinedHist_MuonTheta =  Combine_crosssection_Hists_PlaylistMap_includeInteraction_DISbreakdown(FullCrossSection_Hist_Playlist_Map_MuonTheta,     FullME_playlist_vector.at(3));

CrossSection_Hist Empty_CombinedHist_MuonE     =  Combine_crosssection_Hists_PlaylistMap_includeInteraction_DISbreakdown(EmptyCrossSection_Hist_Playlist_Map_MuonE,         EmptyME_playlist_vector.at(3));
CrossSection_Hist Empty_CombinedHist_MuonPZ    =  Combine_crosssection_Hists_PlaylistMap_includeInteraction_DISbreakdown(EmptyCrossSection_Hist_Playlist_Map_MuonPZ,        EmptyME_playlist_vector.at(3));
CrossSection_Hist Empty_CombinedHist_MuonPT    =  Combine_crosssection_Hists_PlaylistMap_includeInteraction_DISbreakdown(EmptyCrossSection_Hist_Playlist_Map_MuonPT,        EmptyME_playlist_vector.at(3));
CrossSection_Hist Empty_CombinedHist_MuonTheta =  Combine_crosssection_Hists_PlaylistMap_includeInteraction_DISbreakdown(EmptyCrossSection_Hist_Playlist_Map_MuonTheta,     EmptyME_playlist_vector.at(3));


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

///////////////////
Pot_MapList FullMC_ScalingMap =  POT_ScalersMap(FullPOT_MC_RECO_MAP , FullPOT_DATA_MAP[kME1F] );
Pot_MapList EMPTYMC_ScalingMap =  POT_ScalersMap(EmptyPOT_MC_RECO_MAP , FullPOT_DATA_MAP[kME1F] );
Pot_MapList FullDATA_ScalingMap =  POT_ScalersMap(FullPOT_DATA_MAP , FullPOT_DATA_MAP[kME1F] );
Pot_MapList EmptyDATA_ScalingMap =  POT_ScalersMap(EmptyPOT_DATA_MAP , FullPOT_DATA_MAP[kME1F] );



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

POT_Normalize_CrossSection_Hist(Full_CombinedHist_MuonE , Full_MC_Full_Data);
POT_Normalize_CrossSection_Hist(Full_CombinedHist_MuonPZ , Full_MC_Full_Data);
POT_Normalize_CrossSection_Hist(Full_CombinedHist_MuonPT , Full_MC_Full_Data);
POT_Normalize_CrossSection_Hist(Full_CombinedHist_MuonTheta , Full_MC_Full_Data);


POT_Normalize_CrossSection_Hist_InteractionOnly_DISBreakdown(Full_CombinedHist_MuonE,     Full_MC_Full_Data);
POT_Normalize_CrossSection_Hist_InteractionOnly_DISBreakdown(Full_CombinedHist_MuonPZ,    Full_MC_Full_Data);
POT_Normalize_CrossSection_Hist_InteractionOnly_DISBreakdown(Full_CombinedHist_MuonPT,    Full_MC_Full_Data);
POT_Normalize_CrossSection_Hist_InteractionOnly_DISBreakdown(Full_CombinedHist_MuonTheta, Full_MC_Full_Data);


POT_Normalize_CrossSection_Hist_InteractionOnly_DISBreakdown(Empty_CombinedHist_MuonE,     Empty_MC_Full_Data);
POT_Normalize_CrossSection_Hist_InteractionOnly_DISBreakdown(Empty_CombinedHist_MuonPZ,    Empty_MC_Full_Data);
POT_Normalize_CrossSection_Hist_InteractionOnly_DISBreakdown(Empty_CombinedHist_MuonPT,    Empty_MC_Full_Data);
POT_Normalize_CrossSection_Hist_InteractionOnly_DISBreakdown(Empty_CombinedHist_MuonTheta, Empty_MC_Full_Data);

POT_Normalize_CrossSection_Hist(Empty_CombinedHist_MuonE,     Empty_MC_Full_Data ,Empty_Data_Full_Data, true );
POT_Normalize_CrossSection_Hist(Empty_CombinedHist_MuonPZ,    Empty_MC_Full_Data ,Empty_Data_Full_Data, true );
POT_Normalize_CrossSection_Hist(Empty_CombinedHist_MuonPT,    Empty_MC_Full_Data ,Empty_Data_Full_Data, true );
POT_Normalize_CrossSection_Hist(Empty_CombinedHist_MuonTheta, Empty_MC_Full_Data ,Empty_Data_Full_Data, true );

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~ Checking Binning   ~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

Check_NSignalBins(Full_CombinedHist_MuonE,      "Full_CombinedHist_MuonE");
Check_NSignalBins(Full_CombinedHist_MuonPZ,     "Full_CombinedHist_MuonPZ");
Check_NSignalBins(Full_CombinedHist_MuonPT,     "Full_CombinedHist_MuonPT");
Check_NSignalBins(Full_CombinedHist_MuonTheta,  "Full_CombinedHist_MuonTheta");
Check_NSignalBins(Empty_CombinedHist_MuonE,     "Empty_CombinedHist_MuonE");
Check_NSignalBins(Empty_CombinedHist_MuonPZ,    "Empty_CombinedHist_MuonPZ");
Check_NSignalBins(Empty_CombinedHist_MuonPT,    "Empty_CombinedHist_MuonPT");
Check_NSignalBins(Empty_CombinedHist_MuonTheta, "Empty_CombinedHist_MuonTheta");

/////////
//MAKING CUT TABLE
/////////

Playlist_CutMap Total_CutTable;
CutMap Combined_CutMap_Full;
CutMap Combined_CutMap_Empty;
CutMap Combined_CutMap_Full_Empty;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~ Starting to Make Cut Tables   ~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~ Filling Names ~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

FillCutMapPlaylists(Total_CutTable, Playlist_Combined);
FillCutMapPlaylists(Total_CutTable, "RECO_Data_Cuts",  "RECO_Cuts", "RECO_Helium_Cuts", "TRUE_RECO_Cuts", "Truth_Cuts", "Truth_Cuts");

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~ Finished Filling Names   ~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~ Filling Full ~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;


for(auto playlist : FullME_playlist_vector){
FillCutMap_fromTFiles(Total_CutTable[playlist], FullTFile_Map_MC_TRUTH[playlist],   FullTFile_Map_MC_RECO[playlist], FullTFile_Map_DATA[playlist]);
}

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~ Finished Filling Full   ~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~ Filling Empty ~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;


for(auto playlist : EmptyME_playlist_vector){
FillCutMap_fromTFiles(Total_CutTable[playlist], EmptyTFile_Map_MC_TRUTH[playlist],   EmptyTFile_Map_MC_RECO[playlist], EmptyTFile_Map_DATA[playlist]);
}

for(auto playlist : EmptyME_playlist_vector){
FillCutMap_fromTFiles(Total_CutTable[playlist], EmptyTFile_Map_MC_TRUTH[playlist],   EmptyTFile_Map_MC_RECO[playlist], EmptyTFile_Map_DATA[playlist]);
}

for(auto playlist : Playlist_Combined){
ADDCUT_same_Cut_Map_RECO(Total_CutTable[playlist], kNonMu_is_Plausible , kMu_is_Plausible);
ADDCUT_same_Cut_Map_Data(Total_CutTable[playlist], kNonMu_is_Plausible , kMu_is_Plausible);
}




std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~ Starting to Make Combined Cut Map   ~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

std::cout<< "Before: Combined_CutMap_Full.size() = "<< Combined_CutMap_Full.MC_RECO_CutsMap.size() <<std::endl;

CombinedCutMap(Combined_CutMap_Full, Total_CutTable, FullME_playlist_vector, FullME_playlist_vector.at(0) );
CombinedCutMap(Combined_CutMap_Empty, Total_CutTable, EmptyME_playlist_vector, EmptyME_playlist_vector.at(0) );
CombinedCutMap(Combined_CutMap_Full_Empty, Total_CutTable, FullME_playlist_vector, FullME_playlist_vector.at(0) );


std::cout<< "After: Combined_CutMap_Full.size() = "<< Combined_CutMap_Full.MC_RECO_CutsMap.size() <<std::endl;

std::cout<<" "<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<std::endl;
std::cout<<"Printing Events before POT scaling "<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<std::endl;
std::cout<<" "<<std::endl;
PrintCutMapMaptoScreen(Combined_CutMap_Full.MC_RECO_CutsMap);

Scale_CutMap(Combined_CutMap_Full, Full_MC_Full_Data);
Scale_CutMap(Combined_CutMap_Full_Empty, Full_MC_Full_Data);
Scale_CutMap(Combined_CutMap_Empty, Empty_MC_Full_Data, Empty_Data_Full_Data);
/////////////////////////
////// Print Total here
///////////////////////
Make_latexTables_CutMap(Combined_CutMap_Full,"Combined_Full", "Full" );
Make_latexTables_CutMap(Combined_CutMap_Empty,"Combined_Empty", "Empty" );
SubTract_Cut_Map(Combined_CutMap_Full_Empty, Combined_CutMap_Empty);
Make_latexTables_CutMap(Combined_CutMap_Full_Empty,"Combined_Full_Empty", "F-E" );


/////////////////


for(auto playlist : FullME_playlist_vector){
Scale_CutMap(Total_CutTable[playlist], FullMC_ScalingMap[playlist], FullDATA_ScalingMap[playlist] );
}

for(auto playlist : EmptyME_playlist_vector){
Scale_CutMap(Total_CutTable[playlist], EMPTYMC_ScalingMap[playlist], EmptyDATA_ScalingMap[playlist] );
}

for(auto playlist :Playlist_Combined){
std::string playlistname = GetPlaylist_InitialName(playlist);
char playistname_char[playlistname.length()+1];
strcpy(playistname_char,playlistname.c_str());
std::string cryotank_status = GetPlaylistStatusString(GetPlaylist_HeliumStatus(playlist));
Make_latexTables_CutMap(Total_CutTable[playlist], playistname_char, cryotank_status );

}


std::cout<<" "<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<std::endl;
std::cout<<"Printing Events After POT scaling "<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<std::endl;
PrintCutMapMaptoScreen(Combined_CutMap_Full.MC_RECO_CutsMap);





std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~ Writing to File Current Hists   ~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

WritetoTFile_All(Full_CombinedHist_MuonE,     *outFile,  "h_MuonE_Full");
WritetoTFile_All(Full_CombinedHist_MuonPZ,    *outFile,  "h_MuonPZ_Full");
WritetoTFile_All(Full_CombinedHist_MuonPT,    *outFile,  "h_MuonPT_Full");
WritetoTFile_All(Full_CombinedHist_MuonTheta, *outFile,  "h_MuonTheta_Full");

WritetoTFile_All(Empty_CombinedHist_MuonE,     *outFile, "h_MuonE_Empty");
WritetoTFile_All(Empty_CombinedHist_MuonPZ,    *outFile, "h_MuonPZ_Empty");
WritetoTFile_All(Empty_CombinedHist_MuonPT,    *outFile, "h_MuonPT_Empty");
WritetoTFile_All(Empty_CombinedHist_MuonTheta, *outFile, "h_MuonTheta_Empty");


WritetoTFile_main(Full_CombinedHist_MuonE,     *outFile,    "h_MuonE_Full_potnorm");
WritetoTFile_main(Full_CombinedHist_MuonPZ,    *outFile,    "h_MuonPZ_Full_potnorm");
WritetoTFile_main(Full_CombinedHist_MuonPT,    *outFile,    "h_MuonPT_Full_potnorm");
WritetoTFile_main(Full_CombinedHist_MuonTheta, *outFile,    "h_MuonTheta_Full_potnorm");

WritetoTFile_main(Empty_CombinedHist_MuonE,     *outFile,   "h_MuonE_Empty_potnorm");
WritetoTFile_main(Empty_CombinedHist_MuonPZ,    *outFile,   "h_MuonPZ_Empty_potnorm");
WritetoTFile_main(Empty_CombinedHist_MuonPT,    *outFile,   "h_MuonPT_Empty_potnorm");
WritetoTFile_main(Empty_CombinedHist_MuonTheta, *outFile,   "h_MuonTheta_Empty_potnorm");

WritetoTFile_Interaction_DISbreakdown(Full_CombinedHist_MuonE,      *outFile, "h_MuonE_Full_potnorm");
WritetoTFile_Interaction_DISbreakdown(Full_CombinedHist_MuonPZ,     *outFile, "h_MuonPZ_Full_potnorm");
WritetoTFile_Interaction_DISbreakdown(Full_CombinedHist_MuonPT,     *outFile, "h_MuonPT_Full_potnorm");
WritetoTFile_Interaction_DISbreakdown(Full_CombinedHist_MuonTheta,  *outFile, "h_MuonTheta_Full_potnorm");

WritetoTFile_Interaction_DISbreakdown(Empty_CombinedHist_MuonE,      *outFile, "h_MuonE_Full_potnorm");
WritetoTFile_Interaction_DISbreakdown(Empty_CombinedHist_MuonPZ,     *outFile, "h_MuonPZ_Full_potnorm");
WritetoTFile_Interaction_DISbreakdown(Empty_CombinedHist_MuonPT,     *outFile, "h_MuonPT_Full_potnorm");
WritetoTFile_Interaction_DISbreakdown(Empty_CombinedHist_MuonTheta,  *outFile, "h_MuonTheta_Full_potnorm");


std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~Subtraction Applied ~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

Subtract_CrossSection_Hist(Full_CombinedHist_MuonE,     Empty_CombinedHist_MuonE);
Subtract_CrossSection_Hist(Full_CombinedHist_MuonPZ,    Empty_CombinedHist_MuonPZ);
Subtract_CrossSection_Hist(Full_CombinedHist_MuonPT,    Empty_CombinedHist_MuonPT);
Subtract_CrossSection_Hist(Full_CombinedHist_MuonTheta, Empty_CombinedHist_MuonTheta);

//Subtract_CrossSection_Hist_Interaction(Full_CombinedHist_MuonE,     Empty_CombinedHist_MuonE); unsure we have to subtract bg from truth
//Subtract_CrossSection_Hist_Interaction(Full_CombinedHist_MuonPZ,    Empty_CombinedHist_MuonPZ);
//Subtract_CrossSection_Hist_Interaction(Full_CombinedHist_MuonPT,    Empty_CombinedHist_MuonPT);
//Subtract_CrossSection_Hist_Interaction(Full_CombinedHist_MuonTheta, Empty_CombinedHist_MuonTheta);

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~Writing F-E ~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

WritetoTFile_main(Full_CombinedHist_MuonE,     *outFile, "h_MuonE_Full_sub_Empty_potnorm");
WritetoTFile_main(Full_CombinedHist_MuonPT,    *outFile, "h_MuonPT_Full_sub_Empty_potnorm");
WritetoTFile_main(Full_CombinedHist_MuonPZ,    *outFile, "h_MuonPZ_Full_sub_Empty_potnorm");
WritetoTFile_main(Full_CombinedHist_MuonTheta, *outFile, "h_MuonTheta_Full_sub_Empty_potnorm");

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~Writing True Xsection ~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
int n_flux_universes =  100;
int nu_pdg = 14;
const bool use_nue_constraint = true;
bool useMuonCorrelations = true;
const std::string project_dir = "targets_12345_jointNueIMD";
double min_energy = 0;
double max_energy = 120;

auto& frw = PlotUtils::flux_reweighter("minervame1f", nu_pdg, use_nue_constraint, n_flux_universes);
auto fluxIntegral_muonE = frw.GetIntegratedTargetFlux(nu_pdg, "helium", Full_CombinedHist_MuonE.h_Data_Signal, min_energy, max_energy, project_dir);
fluxIntegral_muonE->AddMissingErrorBandsAndFillWithCV( *Full_CombinedHist_MuonE.h_Data_Signal );
Full_CombinedHist_MuonE.h_flux = fluxIntegral_muonE;

auto fluxIntegral_muonPZ = frw.GetIntegratedTargetFlux(nu_pdg, "helium", Full_CombinedHist_MuonPZ.h_Data_Signal, min_energy, max_energy, project_dir);
fluxIntegral_muonPZ->AddMissingErrorBandsAndFillWithCV( *Full_CombinedHist_MuonPZ.h_Data_Signal );
Full_CombinedHist_MuonPZ.h_flux = fluxIntegral_muonPZ;

auto fluxIntegral_muonPT = frw.GetIntegratedTargetFlux(nu_pdg, "helium", Full_CombinedHist_MuonPT.h_Data_Signal, min_energy, max_energy, project_dir);
fluxIntegral_muonPT->AddMissingErrorBandsAndFillWithCV( *Full_CombinedHist_MuonPT.h_Data_Signal );
Full_CombinedHist_MuonPT.h_flux = fluxIntegral_muonPT;

auto fluxIntegral_muontheta = frw.GetIntegratedTargetFlux(nu_pdg, "helium", Full_CombinedHist_MuonTheta.h_Data_Signal, min_energy, max_energy, project_dir);
fluxIntegral_muontheta->AddMissingErrorBandsAndFillWithCV( *Full_CombinedHist_MuonTheta.h_Data_Signal );
Full_CombinedHist_MuonTheta.h_flux = fluxIntegral_muontheta;
outFile->cd();



WritetoTFile_NormTRUECrossSection(Full_CombinedHist_MuonE,      *outFile,  "h_MuonE_TrueCrossSection",      NHelium_MC, Full_DATA_POT);
WritetoTFile_NormTRUECrossSection(Full_CombinedHist_MuonPT,     *outFile,  "h_MuonPT_TrueCrossSection",      NHelium_MC, Full_DATA_POT);
WritetoTFile_NormTRUECrossSection(Full_CombinedHist_MuonPZ,     *outFile,  "h_MuonPZ_TrueCrossSection",      NHelium_MC, Full_DATA_POT);
WritetoTFile_NormTRUECrossSection(Full_CombinedHist_MuonTheta,  *outFile,   "h_MuonTheta_TrueCrossSection",  NHelium_MC, Full_DATA_POT);

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

WritetoTFile_NormTRUECrossSection_Interaction_DISbreakdown(Full_CombinedHist_MuonE,      *outFile,  "h_MuonE",       NHelium_MC, Full_DATA_POT);
WritetoTFile_NormTRUECrossSection_Interaction_DISbreakdown(Full_CombinedHist_MuonPT,     *outFile,  "h_MuonPT",      NHelium_MC, Full_DATA_POT);
WritetoTFile_NormTRUECrossSection_Interaction_DISbreakdown(Full_CombinedHist_MuonPZ,     *outFile,  "h_MuonPZ",      NHelium_MC, Full_DATA_POT);
WritetoTFile_NormTRUECrossSection_Interaction_DISbreakdown(Full_CombinedHist_MuonTheta,  *outFile,  "h_MuonTheta",  NHelium_MC, Full_DATA_POT);
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~ BG Subtraction ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

Full_CombinedHist_MuonE.h_Data_Signal->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonE.h_RECO_BG);
Full_CombinedHist_MuonPZ.h_Data_Signal->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonPZ.h_RECO_BG);
Full_CombinedHist_MuonPT.h_Data_Signal->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonPT.h_RECO_BG);
Full_CombinedHist_MuonTheta.h_Data_Signal->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonTheta.h_RECO_BG);


Full_CombinedHist_MuonE.h_Data_Signal->Add(Full_CombinedHist_MuonE.h_RECO_BG,-1);
Full_CombinedHist_MuonPZ.h_Data_Signal->Add(Full_CombinedHist_MuonPZ.h_RECO_BG,-1);
Full_CombinedHist_MuonPT.h_Data_Signal->Add(Full_CombinedHist_MuonPT.h_RECO_BG,-1);
Full_CombinedHist_MuonTheta.h_Data_Signal->Add(Full_CombinedHist_MuonTheta.h_RECO_BG,-1);


Full_CombinedHist_MuonE.h_Data_Signal->Clone()->Write("h_MuonE_Data_BG_Subtracted");
Full_CombinedHist_MuonPZ.h_Data_Signal->Clone()->Write("h_MuonPZ_Data_BG_Subtracted");
Full_CombinedHist_MuonPT.h_Data_Signal->Clone()->Write("h_MuonPT_Data_BG_Subtracted");
Full_CombinedHist_MuonTheta.h_Data_Signal->Clone()->Write("h_MuonTheta_Data_BG_Subtracted");


//Full_CombinedHist_MuonE.h_Data_Signal->GetTotalCorrelationMatrixTH2D().Clone()->Write("h_MuonECorrelationMatrix");

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~ UnFolding ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;


std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
Full_CombinedHist_MuonE.h_Mig->Clone()->Write("h_MuonE_Mig");
auto unfoldedMuonE_data = UnfoldHist(Full_CombinedHist_MuonE.h_Data_Signal, Full_CombinedHist_MuonE.h_Mig, 3 );
unfoldedMuonE_data->ModifyStatisticalUnc(10.0, "unfoldingCov");
unfoldedMuonE_data->Clone()->Write("h_MuonE_unfolded_data");
////////////////////////////////////////////////////////////////////////////////
Full_CombinedHist_MuonPZ.h_Mig->Clone()->Write("h_MuonPZ_Mig");
auto unfoldedMuonPZ_data = UnfoldHist( Full_CombinedHist_MuonPZ.h_Data_Signal, Full_CombinedHist_MuonPZ.h_Mig, 3 );
unfoldedMuonPZ_data->ModifyStatisticalUnc(25.5, "unfoldingCov");
unfoldedMuonPZ_data->Clone()->Write("h_MuonPZ_unfolded_data");
////////////////////////////////////////////////////////////////////////////////
Full_CombinedHist_MuonPT.h_Mig->Clone()->Write("h_MuonPT_Mig");
auto unfoldedMuonPT_data = UnfoldHist( Full_CombinedHist_MuonPT.h_Data_Signal, Full_CombinedHist_MuonPT.h_Mig, 3 );
unfoldedMuonPT_data->ModifyStatisticalUnc(9.0, "unfoldingCov");
unfoldedMuonPT_data->Clone()->Write("h_MuonPT_unfolded_data");
////////////////////////////////////////////////////////////////////////////////
Full_CombinedHist_MuonTheta.h_Mig->Clone()->Write("h_MuonTheta_Mig");
auto unfoldedMuonTheta_data = UnfoldHist( Full_CombinedHist_MuonTheta.h_Data_Signal, Full_CombinedHist_MuonTheta.h_Mig, 3 );
unfoldedMuonTheta_data->ModifyStatisticalUnc(22.0, "unfoldingCov");
unfoldedMuonTheta_data->Clone()->Write("h_MuonTheta_unfolded_data");

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~ efficiency Correct ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
AddErrorBands_TOEffDom(Full_CombinedHist_MuonE);
Full_CombinedHist_MuonE.h_effNum->Divide(Full_CombinedHist_MuonE.h_effNum, Full_CombinedHist_MuonE.h_effDom);
Full_CombinedHist_MuonE.h_effNum->Clone()->Write("h_MuonE_efficiency");

unfoldedMuonE_data->Divide(unfoldedMuonE_data, Full_CombinedHist_MuonE.h_effNum);
unfoldedMuonE_data->Clone()->Write("h_MuonE_unfolded_data_effcorrected");
///////////////////////////////
Full_CombinedHist_MuonPZ.h_effNum->Divide(Full_CombinedHist_MuonPZ.h_effNum, Full_CombinedHist_MuonPZ.h_effDom);
Full_CombinedHist_MuonPZ.h_effNum->Clone()->Write("h_MuonPZ_efficiency");

unfoldedMuonPZ_data->Divide(unfoldedMuonPZ_data, Full_CombinedHist_MuonPZ.h_effNum);
unfoldedMuonPZ_data->Clone()->Write("h_MuonPZ_unfolded_data_effcorrected");
////////////////////////////////
AddErrorBands_TOEffDom(Full_CombinedHist_MuonPT);
Full_CombinedHist_MuonPT.h_effNum->Divide(Full_CombinedHist_MuonPT.h_effNum, Full_CombinedHist_MuonPT.h_effDom);
Full_CombinedHist_MuonPT.h_effNum->Clone()->Write("h_MuonPT_efficiency");

unfoldedMuonPT_data->Divide(unfoldedMuonPT_data, Full_CombinedHist_MuonPT.h_effNum);
unfoldedMuonPT_data->Clone()->Write("h_MuonPT_unfolded_data_effcorrected");

AddErrorBands_TOEffDom(Full_CombinedHist_MuonTheta);
Full_CombinedHist_MuonTheta.h_effNum->Divide(Full_CombinedHist_MuonTheta.h_effNum, Full_CombinedHist_MuonTheta.h_effDom);
Full_CombinedHist_MuonTheta.h_effNum->Clone()->Write("h_MuonTheta_efficiency");

unfoldedMuonTheta_data->Divide(unfoldedMuonTheta_data, Full_CombinedHist_MuonTheta.h_effNum);
unfoldedMuonTheta_data->Clone()->Write("h_MuonTheta_unfolded_data_effcorrected");


std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~ Cross Section ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;



auto h_crossSection_MuonE = normalize(unfoldedMuonE_data, /*Full_CombinedHist_MuonE.h_flux*/fluxIntegral_muonE, NHelium, Full_DATA_POT);

auto h_crossSection_MuonPZ = normalize(unfoldedMuonPZ_data, /*Full_CombinedHist_MuonPZ.h_flux*/fluxIntegral_muonPZ, NHelium, Full_DATA_POT);

auto h_crossSection_MuonPT = normalize(unfoldedMuonPT_data, /*Full_CombinedHist_MuonPT.h_flux*/fluxIntegral_muonPT, NHelium, Full_DATA_POT);

auto h_crossSection_MuonTheta = normalize(unfoldedMuonTheta_data, /*Full_CombinedHist_MuonPT.h_flux*/fluxIntegral_muontheta, NHelium, Full_DATA_POT);



h_crossSection_MuonPZ->Clone()->Write("h_MuonPZ_CrossSection_data_unfolded");
h_crossSection_MuonE->Clone()->Write("h_MuonE_CrossSection_data_unfolded");
h_crossSection_MuonPT->Clone()->Write("h_MuonPT_CrossSection_data_unfolded");
h_crossSection_MuonTheta->Clone()->Write("h_MuonTheta_CrossSection_data_unfolded");


Playlist_MnvH1D_Map NuE_true_Map =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullTFile_Map_MC_TRUTH_Flux, "h_Enu_TRUE" );
//Playlist_MnvH1D_Map NuE_true_reco_Map =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullTFile_Map_MC_RECO_Flux, "h_Enu_TRUE_RECO" );

Playlist_MnvH2D_Map NuE_true_Enu_slice_Map =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(FullTFile_Map_MC_TRUTH_Flux, "h_Enu_Slice_TRUE" );
//Playlist_MnvH2D_Map NuE_true_RECO_Enu_slice_Map =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(FullTFile_Map_MC_RECO_Flux, "h_Enu_Slice_TRUE_RECO" );

Playlist_MnvH2D_Map NuE_true_Enu_daisy_Map =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(FullTFile_Map_MC_TRUTH_Flux, "h2_Enu_DAISY_TRUE" );



Playlist_MnvH1D_Map NuE_true_Map_Slice1 =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullTFile_Map_MC_TRUTH_Flux, "h_Enu_TRUE_Slice1" );
//Playlist_MnvH1D_Map NuE_true_reco_Map_Slice1 =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullTFile_Map_MC_RECO_Flux, "h_Enu_TRUE_RECO_Slice1" );

Playlist_MnvH1D_Map NuE_true_Map_Slice2 =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullTFile_Map_MC_TRUTH_Flux, "h_Enu_TRUE_Slice2" );
//Playlist_MnvH1D_Map NuE_true_reco_Map_Slice2 =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullTFile_Map_MC_RECO_Flux, "h_Enu_TRUE_RECO_Slice2" );

Playlist_MnvH1D_Map NuE_true_Map_Slice3 =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullTFile_Map_MC_TRUTH_Flux, "h_Enu_TRUE_Slice3" );
//Playlist_MnvH1D_Map NuE_true_reco_Map_Slice3 =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullTFile_Map_MC_RECO_Flux, "h_Enu_TRUE_RECO_Slice3" );

Playlist_MnvH1D_Map NuE_true_Map_Slice4 =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullTFile_Map_MC_TRUTH_Flux, "h_Enu_TRUE_Slice4" );
//Playlist_MnvH1D_Map NuE_true_reco_Map_Slice4 =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullTFile_Map_MC_RECO_Flux, "h_Enu_TRUE_RECO_Slice4" );


Playlist_MnvH1D_Map h_Enu_TRUE_Daisy0_map = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullTFile_Map_MC_TRUTH_Flux, "h_Enu_TRUE_Daisy0" );
Playlist_MnvH1D_Map h_Enu_TRUE_Daisy1_map = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullTFile_Map_MC_TRUTH_Flux, "h_Enu_TRUE_Daisy1" );
Playlist_MnvH1D_Map h_Enu_TRUE_Daisy2_map = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullTFile_Map_MC_TRUTH_Flux, "h_Enu_TRUE_Daisy2" );
Playlist_MnvH1D_Map h_Enu_TRUE_Daisy3_map = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullTFile_Map_MC_TRUTH_Flux, "h_Enu_TRUE_Daisy3" );
Playlist_MnvH1D_Map h_Enu_TRUE_Daisy4_map = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullTFile_Map_MC_TRUTH_Flux, "h_Enu_TRUE_Daisy4" );
Playlist_MnvH1D_Map h_Enu_TRUE_Daisy5_map = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullTFile_Map_MC_TRUTH_Flux, "h_Enu_TRUE_Daisy5" );
Playlist_MnvH1D_Map h_Enu_TRUE_Daisy6_map = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullTFile_Map_MC_TRUTH_Flux, "h_Enu_TRUE_Daisy6" );
Playlist_MnvH1D_Map h_Enu_TRUE_Daisy7_map = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullTFile_Map_MC_TRUTH_Flux, "h_Enu_TRUE_Daisy7" );
Playlist_MnvH1D_Map h_Enu_TRUE_Daisy8_map = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullTFile_Map_MC_TRUTH_Flux, "h_Enu_TRUE_Daisy8" );
Playlist_MnvH1D_Map h_Enu_TRUE_Daisy9_map = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullTFile_Map_MC_TRUTH_Flux, "h_Enu_TRUE_Daisy9" );
Playlist_MnvH1D_Map h_Enu_TRUE_Daisy10_map = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullTFile_Map_MC_TRUTH_Flux, "h_Enu_TRUE_Daisy10" );
Playlist_MnvH1D_Map h_Enu_TRUE_Daisy11_map = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullTFile_Map_MC_TRUTH_Flux, "h_Enu_TRUE_Daisy11" );



PlotUtils::MnvH1D *h_Enu_TRUE = Combine_Hists_fromMAP(NuE_true_Map , FullME_playlist_vector.at(3) ,"h_Enu_TRUE");
//PlotUtils::MnvH1D *h_Enu_TRUE_RECO = Combine_Hists_fromMAP(NuE_true_reco_Map ,FullME_playlist_vector.at(3) ,"h_Enu_TRUE_RECO");

PlotUtils::MnvH1D *h_Enu_TRUE_Slice1 = Combine_Hists_fromMAP(NuE_true_Map_Slice1 , FullME_playlist_vector.at(3) ,"h_Enu_TRUE_Slice1");
//PlotUtils::MnvH1D *h_Enu_TRUE_RECO_Slice1 = Combine_Hists_fromMAP(NuE_true_reco_Map_Slice1 ,FullME_playlist_vector.at(3) ,"h_Enu_TRUE_RECO_Slice1");

PlotUtils::MnvH1D *h_Enu_TRUE_Slice2 = Combine_Hists_fromMAP(NuE_true_Map_Slice2 , FullME_playlist_vector.at(3) ,"h_Enu_TRUE_Slice2");
//PlotUtils::MnvH1D *h_Enu_TRUE_RECO_Slice2 = Combine_Hists_fromMAP(NuE_true_reco_Map_Slice2 ,FullME_playlist_vector.at(3) ,"h_Enu_TRUE_RECO_Slice2");

PlotUtils::MnvH1D *h_Enu_TRUE_Slice3 = Combine_Hists_fromMAP(NuE_true_Map_Slice3 , FullME_playlist_vector.at(3) ,"h_Enu_TRUE_Slice3");
//PlotUtils::MnvH1D * h_Enu_TRUE_RECO_Slice3 = Combine_Hists_fromMAP(NuE_true_reco_Map_Slice3 ,FullME_playlist_vector.at(3) ,"h_Enu_TRUE_RECO_Slice3");

PlotUtils::MnvH1D *h_Enu_TRUE_Slice4 = Combine_Hists_fromMAP(NuE_true_Map_Slice4 , FullME_playlist_vector.at(3) ,"h_Enu_TRUE_Slice4");
//PlotUtils::MnvH1D *h_Enu_TRUE_RECO_Slice4 = Combine_Hists_fromMAP(NuE_true_reco_Map_Slice4 ,FullME_playlist_vector.at(3) ,"h_Enu_TRUE_RECO_Slice4");



PlotUtils::MnvH1D *h_Enu_TRUE_Daisy0 = Combine_Hists_fromMAP(h_Enu_TRUE_Daisy0_map , FullME_playlist_vector.at(3) ,"h_Enu_TRUE_Daisy0");
PlotUtils::MnvH1D *h_Enu_TRUE_Daisy1 = Combine_Hists_fromMAP(h_Enu_TRUE_Daisy1_map , FullME_playlist_vector.at(3) ,"h_Enu_TRUE_Daisy1");
PlotUtils::MnvH1D *h_Enu_TRUE_Daisy2 = Combine_Hists_fromMAP(h_Enu_TRUE_Daisy2_map , FullME_playlist_vector.at(3) ,"h_Enu_TRUE_Daisy2");
PlotUtils::MnvH1D *h_Enu_TRUE_Daisy3 = Combine_Hists_fromMAP(h_Enu_TRUE_Daisy3_map , FullME_playlist_vector.at(3) ,"h_Enu_TRUE_Daisy3");
PlotUtils::MnvH1D *h_Enu_TRUE_Daisy4 = Combine_Hists_fromMAP(h_Enu_TRUE_Daisy4_map , FullME_playlist_vector.at(3) ,"h_Enu_TRUE_Daisy4");
PlotUtils::MnvH1D *h_Enu_TRUE_Daisy5 = Combine_Hists_fromMAP(h_Enu_TRUE_Daisy5_map , FullME_playlist_vector.at(3) ,"h_Enu_TRUE_Daisy5");
PlotUtils::MnvH1D *h_Enu_TRUE_Daisy6 = Combine_Hists_fromMAP(h_Enu_TRUE_Daisy6_map , FullME_playlist_vector.at(3) ,"h_Enu_TRUE_Daisy6");
PlotUtils::MnvH1D *h_Enu_TRUE_Daisy7 = Combine_Hists_fromMAP(h_Enu_TRUE_Daisy7_map , FullME_playlist_vector.at(3) ,"h_Enu_TRUE_Daisy7");
PlotUtils::MnvH1D *h_Enu_TRUE_Daisy8 = Combine_Hists_fromMAP(h_Enu_TRUE_Daisy8_map , FullME_playlist_vector.at(3) ,"h_Enu_TRUE_Daisy8");
PlotUtils::MnvH1D *h_Enu_TRUE_Daisy9 = Combine_Hists_fromMAP(h_Enu_TRUE_Daisy9_map , FullME_playlist_vector.at(3) ,"h_Enu_TRUE_Daisy9");
PlotUtils::MnvH1D *h_Enu_TRUE_Daisy10 =Combine_Hists_fromMAP(h_Enu_TRUE_Daisy10_map , FullME_playlist_vector.at(3) ,"h_Enu_TRUE_Daisy10");
PlotUtils::MnvH1D *h_Enu_TRUE_Daisy11 =Combine_Hists_fromMAP(h_Enu_TRUE_Daisy11_map , FullME_playlist_vector.at(3) ,"h_Enu_TRUE_Daisy11");

//h_Enu_TRUE->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonE.h_effDom);
//h_Enu_TRUE->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonE.h_effDom);
//h_Enu_TRUE_Slice1->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonE.h_effDom);
//h_Enu_TRUE_Slice2->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonE.h_effDom);
//h_Enu_TRUE_Slice3->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonE.h_effDom);
//h_Enu_TRUE_Slice4->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonE.h_effDom);
//h_Enu_TRUE_Daisy0->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonE.h_effDom);
//h_Enu_TRUE_Daisy1->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonE.h_effDom);
//h_Enu_TRUE_Daisy2->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonE.h_effDom);
//h_Enu_TRUE_Daisy3->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonE.h_effDom);
//h_Enu_TRUE_Daisy4->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonE.h_effDom);
//h_Enu_TRUE_Daisy5->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonE.h_effDom);
//h_Enu_TRUE_Daisy6->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonE.h_effDom);
//h_Enu_TRUE_Daisy7->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonE.h_effDom);
//h_Enu_TRUE_Daisy8->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonE.h_effDom);
//h_Enu_TRUE_Daisy9->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonE.h_effDom);
//h_Enu_TRUE_Daisy10->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonE.h_effDom);
//h_Enu_TRUE_Daisy11->AddMissingErrorBandsAndFillWithCV(*Full_CombinedHist_MuonE.h_effDom);
////Playlist_MnvH2D_Map h_Enu_TRUE_vertex_X_Map =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(FullTFile_Map_MC_TRUTH_Flux, "h_Enu_TRUE_vertex_X" );
//Playlist_MnvH2D_Map h_Enu_TRUE_vertex_Y_Map =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(FullTFile_Map_MC_TRUTH_Flux, "h_Enu_TRUE_vertex_Y" );



auto h2d_Enu_TRUE_Slice = Combine_2DHists_fromMAP(NuE_true_Enu_slice_Map , FullME_playlist_vector.at(3) ,"h2d_Enu_TRUE_Slice");


auto h2d_Enu_TRUE_Daisy = Combine_2DHists_fromMAP(NuE_true_Enu_daisy_Map , FullME_playlist_vector.at(3) ,"h2d_Enu_TRUE_Daisy");



//auto h2d_Enu_TRUE_RECO_Slice = Combine_2DHists_fromMAP(NuE_true_RECO_Enu_slice_Map ,FullME_playlist_vector.at(3) ,"h_Enu_TRUE_RECO_Slice");
//auto h2d_Enu_TRUE_vertex_Y = Combine_2DHists_fromMAP(NuE_true_Enu_slice_Map , FullME_playlist_vector.at(3) ,"h_Enu_TRUE_vertex_X");
//auto h2d_Enu_TRUE_vertex_X = Combine_2DHists_fromMAP(NuE_true_Enu_slice_Map , FullME_playlist_vector.at(3) ,"h2d_Enu_TRUE_vertex_Y");

//auto h2d_Enu_TRUE_Slice = Combine_2DHists_fromMAP(NuE_true_Enu_slice_Map , FullME_playlist_vector.at(3) ,"h2d_Enu_TRUE_Slice");


Playlist_MnvH2D_Map h2d_Enu_TRUE_vertex_X_Map =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(FullTFile_Map_MC_TRUTH_Flux, "h_Enu_TRUE_vertex_X" );
Playlist_MnvH2D_Map h2d_Enu_TRUE_vertex_Y_Map =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(FullTFile_Map_MC_TRUTH_Flux, "h_Enu_TRUE_vertex_Y" );


Playlist_MnvH2D_Map h2d_Enu_TRUE_vertex_X_Map1 =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(FullTFile_Map_MC_TRUTH_Flux, "h_Enu_TRUE_vertex_X_reduced" );
Playlist_MnvH2D_Map h2d_Enu_TRUE_vertex_Y_Map1 =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(FullTFile_Map_MC_TRUTH_Flux, "h_Enu_TRUE_vertex_Y_reduced" );

Playlist_MnvH2D_Map h2d_Enu_TRUE_vertex_X_Map2 =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(FullTFile_Map_MC_TRUTH_Flux, "h_Enu_TRUE_vertex_X_reduced1" );
Playlist_MnvH2D_Map h2d_Enu_TRUE_vertex_Y_Map2 =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(FullTFile_Map_MC_TRUTH_Flux, "h_Enu_TRUE_vertex_Y_reduced1" );



auto h2d_Enu_TRUE_vertex_Y = Combine_2DHists_fromMAP(h2d_Enu_TRUE_vertex_Y_Map , FullME_playlist_vector.at(3) ,"h2d_Enu_TRUE_vertex_Y");
auto h2d_Enu_TRUE_vertex_X = Combine_2DHists_fromMAP(h2d_Enu_TRUE_vertex_X_Map , FullME_playlist_vector.at(3) ,"h2d_Enu_TRUE_vertex_X");

auto h2d_Enu_TRUE_vertex_Y1 = Combine_2DHists_fromMAP(h2d_Enu_TRUE_vertex_Y_Map1 , FullME_playlist_vector.at(3) ,"h2d_Enu_TRUE_vertex_Y1");
auto h2d_Enu_TRUE_vertex_X1 = Combine_2DHists_fromMAP(h2d_Enu_TRUE_vertex_X_Map1 , FullME_playlist_vector.at(3) ,"h2d_Enu_TRUE_vertex_X1");

auto h2d_Enu_TRUE_vertex_Y2 = Combine_2DHists_fromMAP(h2d_Enu_TRUE_vertex_Y_Map2 , FullME_playlist_vector.at(3) ,"h2d_Enu_TRUE_vertex_Y2");
auto h2d_Enu_TRUE_vertex_X2 = Combine_2DHists_fromMAP(h2d_Enu_TRUE_vertex_X_Map2 , FullME_playlist_vector.at(3) ,"h2d_Enu_TRUE_vertex_X2");


h2d_Enu_TRUE_vertex_Y->Clone()->Write("h2d_Enu_TRUE_vertex_Y");
h2d_Enu_TRUE_vertex_X->Clone()->Write("h2d_Enu_TRUE_vertex_X");

h2d_Enu_TRUE_vertex_Y1->Clone()->Write("h2d_Enu_TRUE_vertex_Y_reduced");
h2d_Enu_TRUE_vertex_X1->Clone()->Write("h2d_Enu_TRUE_vertex_X_reduced");

h2d_Enu_TRUE_vertex_Y2->Clone()->Write("h2d_Enu_TRUE_vertex_Y_reduced1");
h2d_Enu_TRUE_vertex_X2->Clone()->Write("h2d_Enu_TRUE_vertex_X_reduced1");

//uto h2d_Enu_TRUE_vertex_X = Get2DHist(*TFile_ME1C_MC_TRUTH_Flux, "h_Enu_TRUE_vertex_X" );


//h_Enu_TRUE->AddMissingErrorBandsAndFillWithCV(*h_Enu_TRUE_RECO);
//h2d_Enu_TRUE_Slice->AddMissingErrorBandsAndFillWithCV(*h2d_Enu_TRUE_RECO_Slice);
//h_Enu_TRUE_Slice1->AddMissingErrorBandsAndFillWithCV(*h_Enu_TRUE_RECO);
//h_Enu_TRUE_Slice2->AddMissingErrorBandsAndFillWithCV(*h_Enu_TRUE_RECO);
//h_Enu_TRUE_Slice3->AddMissingErrorBandsAndFillWithCV(*h_Enu_TRUE_RECO);
//h_Enu_TRUE_Slice4->AddMissingErrorBandsAndFillWithCV(*h_Enu_TRUE_RECO);



//h_Enu_TRUE->Scale(Full_MC_Full_Data);
//h_Enu_TRUE_RECO->Scale(Full_MC_Full_Data);
//h2d_Enu_TRUE_Slice->Scale(Full_MC_Full_Data);
//h2d_Enu_TRUE_RECO_Slice->Scale(Full_MC_Full_Data);

//h_Enu_TRUE_Slice1->Scale(Full_MC_Full_Data);
//h_Enu_TRUE_RECO_Slice1->Scale(Full_MC_Full_Data);
//h_Enu_TRUE_Slice2->Scale(Full_MC_Full_Data);
//h_Enu_TRUE_RECO_Slice2->Scale(Full_MC_Full_Data);
//h_Enu_TRUE_Slice3->Scale(Full_MC_Full_Data);
//h_Enu_TRUE_RECO_Slice3->Scale(Full_MC_Full_Data);
//h_Enu_TRUE_Slice4->Scale(Full_MC_Full_Data);
//h_Enu_TRUE_RECO_Slice4->Scale(Full_MC_Full_Data);

h_Enu_TRUE->Clone()->Write("h_Enu_helium_TRUE");
//h_Enu_TRUE_RECO->Clone()->Write("h_Enu_helium_TRUE_RECO");

h_Enu_TRUE_Slice1->Clone()->Write("h_Enu_helium_TRUE_Slice1");
//h_Enu_TRUE_RECO_Slice1->Clone()->Write("h_Enu_helium_TRUE_RECO_Slice1");
h_Enu_TRUE_Slice2->Clone()->Write("h_Enu_helium_TRUE_Slice2");
//h_Enu_TRUE_RECO_Slice2->Clone()->Write("h_Enu_helium_TRUE_RECO_Slice2");
h_Enu_TRUE_Slice3->Clone()->Write("h_Enu_helium_TRUE_Slice3");
//h_Enu_TRUE_RECO_Slice3->Clone()->Write("h_Enu_helium_TRUE_RECO_Slice3");
h_Enu_TRUE_Slice4->Clone()->Write("h_Enu_helium_TRUE_Slice4");
//h_Enu_TRUE_RECO_Slice4->Clone()->Write("h_Enu_helium_TRUE_RECO_Slice4");

h2d_Enu_TRUE_Slice->Clone()->Write("h2d_Enu_TRUE_Slice");
h2d_Enu_TRUE_Daisy->Clone()->Write("h2d_Enu_TRUE_Daisy");
//h2d_Enu_TRUE_RECO_Slice->Clone()->Write("h2d_Enu_TRUE_RECO_Slice");



h_Enu_TRUE_Daisy0->Clone()->Write("h_Enu_TRUE_helium_Daisy0");
h_Enu_TRUE_Daisy1->Clone()->Write("h_Enu_TRUE_helium_Daisy1");
h_Enu_TRUE_Daisy2->Clone()->Write("h_Enu_TRUE_helium_Daisy2");
h_Enu_TRUE_Daisy3->Clone()->Write("h_Enu_TRUE_helium_Daisy3");
h_Enu_TRUE_Daisy4->Clone()->Write("h_Enu_TRUE_helium_Daisy4");
h_Enu_TRUE_Daisy5->Clone()->Write("h_Enu_TRUE_helium_Daisy5");
h_Enu_TRUE_Daisy6->Clone()->Write("h_Enu_TRUE_helium_Daisy6");
h_Enu_TRUE_Daisy7->Clone()->Write("h_Enu_TRUE_helium_Daisy7");
h_Enu_TRUE_Daisy8->Clone()->Write("h_Enu_TRUE_helium_Daisy8");
h_Enu_TRUE_Daisy9->Clone()->Write("h_Enu_TRUE_helium_Daisy9");
h_Enu_TRUE_Daisy10->Clone()->Write("h_Enu_TRUE_helium_Daisy10");
h_Enu_TRUE_Daisy11->Clone()->Write("h_Enu_TRUE_helium_Daisy11");





//h_Enu_TRUE_RECO->Divide(h_Enu_TRUE_RECO, h_Enu_TRUE);
//h_Enu_TRUE_RECO->Clone()->Write("h_Enu_helium_efficiency");
//
//h_Enu_TRUE_RECO_Slice1->Divide(h_Enu_TRUE_RECO_Slice1, h_Enu_TRUE_Slice1);
//h_Enu_TRUE_RECO_Slice1->Clone()->Write("h_Enu_helium_efficiency_Slice1");
//h_Enu_TRUE_RECO_Slice2->Divide(h_Enu_TRUE_RECO_Slice2, h_Enu_TRUE_Slice2);
//h_Enu_TRUE_RECO_Slice2->Clone()->Write("h_Enu_helium_efficiency_Slice2");
//h_Enu_TRUE_RECO_Slice3->Divide(h_Enu_TRUE_RECO_Slice3, h_Enu_TRUE_Slice3);
//h_Enu_TRUE_RECO_Slice3->Clone()->Write("h_Enu_helium_efficiency_Slice3");
//h_Enu_TRUE_RECO_Slice4->Divide(h_Enu_TRUE_RECO_Slice4, h_Enu_TRUE_Slice4);
//h_Enu_TRUE_RECO_Slice4->Clone()->Write("h_Enu_helium_efficiency_Slice4");


//h2d_Enu_TRUE_RECO_Slice->Divide(h2d_Enu_TRUE_RECO_Slice, h2d_Enu_TRUE_Slice);
//h2d_Enu_TRUE_RECO_Slice->Clone()->Write("h2d_Enu_TRUE_RECO_Slice_efficieny");


//h_Enu_TRUE->Divide(h_Enu_TRUE, h_Enu_TRUE_RECO);
//h_Enu_TRUE->Clone()->Write("h_Enu_helium_TRUE_efficiency_corrected");


//h_Enu_TRUE_Slice1->Divide(h_Enu_TRUE_Slice1, h_Enu_TRUE_RECO_Slice1);
//h_Enu_TRUE_Slice1->Clone()->Write("h_Enu_helium_TRUE_efficiency_corrected_Slice1");
//h_Enu_TRUE_Slice2->Divide(h_Enu_TRUE_Slice2, h_Enu_TRUE_RECO_Slice2);
//h_Enu_TRUE_Slice2->Clone()->Write("h_Enu_helium_TRUE_efficiency_corrected_Slice2");
//h_Enu_TRUE_Slice3->Divide(h_Enu_TRUE_Slice3, h_Enu_TRUE_RECO_Slice3);
//h_Enu_TRUE_Slice3->Clone()->Write("h_Enu_helium_TRUE_efficiency_corrected_Slice3");
//h_Enu_TRUE_Slice4->Divide(h_Enu_TRUE_Slice4, h_Enu_TRUE_RECO_Slice4);
//h_Enu_TRUE_Slice4->Clone()->Write("h_Enu_helium_TRUE_efficiency_corrected_slice4");


//h2d_Enu_TRUE_Slice->Divide(h2d_Enu_TRUE_Slice, h2d_Enu_TRUE_RECO_Slice);
//h2d_Enu_TRUE_Slice->Clone()->Write("h2d_Enu_TRUE_Slice_efficiency_corrected");



outFile->Close();



std::cout<< "Full_DATA_POT = " <<  Full_DATA_POT << std::endl;
std::cout<< "Full_MC_POT = " <<  Full_MC_POT << std::endl;


} // end of RunCrossSectionExtractor



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


void Playlist_CutTableLatex_TRUTH(CutMap inputMap , char *playlist_name_char, std::string CyroTank_status  )
{
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"Printing CutRate for:" <<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

  char Title[1024];

  sprintf(Title, "LatexCut_Table_TRUTH_%s.txt", playlist_name_char );


std::map<ECutsTRUTH, double>::iterator Cut_iter;

  std::ostringstream output_string;
  output_string.precision(6);

  auto table = makeTableString(5,"l");

  output_string <<"\\begin{frame}{"<<  playlist_name_char << " TRUE Cut Table}"<< "\n";
  output_string << "\\resizebox{\\textwidth}{!}{" << "\n";
  output_string << "\\begin{table}[]" << "\n";
  output_string << "\\begin{tabular}{||" << table << "|} \n";
  output_string << "\\hline \n";
  output_string << "Cut name (Playlist " <<  playlist_name_char << " [CryoTank "<< CyroTank_status <<  "] ) & NEvents & loss &  $\\%$ loss & Total $\\%$ loss \\\\" << "\n";
  output_string << "\\hline \n";
  output_string << "\\hline \n";
double CutValue_previous = inputMap.MC_TRUTH_CutsMap.begin()->second;
double total_events = CutValue_previous;

for(Cut_iter = inputMap.MC_TRUTH_CutsMap.begin(); Cut_iter!= inputMap.MC_TRUTH_CutsMap.end(); ++Cut_iter  ){

double CutValue = Cut_iter->second;
double loss = CutValue_previous -  CutValue;
double loss_percent = (loss / CutValue_previous) * 100;
double total_precent_loss = ((total_events - CutValue) / total_events)* 100;

CutValue = roundtoTenth(CutValue);
loss = roundtoTenth(loss);
loss_percent = roundToHundreths(loss_percent);
total_precent_loss = roundToHundreths(total_precent_loss);

output_string << GetCutNameLatexTRUTH(Cut_iter->first) << " & "<< Cut_iter->second << " & " << loss << " & " << loss_percent << "&" << total_precent_loss << " \\\\" << "\n";
CutValue_previous = Cut_iter->second;
output_string << "\\hline \n";
}

  output_string << "\\hline \n";
  output_string << "\\end{tabular} \n";
  output_string << "\\end{table}} \n";
  output_string << "\\end{frame} \n";
  std::ofstream myfile;
  myfile.open(Title);
  myfile<<output_string.str();

  myfile.close();


}//end function

void Playlist_CutTableLatex_RECO(CutMap inputMap , char *playlist_name_char, std::string CyroTank_status  )
{
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"Printing CutRate for:" <<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

  char Title[1024];

  sprintf(Title, "LatexCut_Table_RECO_%s.txt", playlist_name_char );


std::map<ECutsTRUTH, double>::iterator Cut_iter;

  std::ostringstream output_string;
  output_string.precision(6);
  output_string <<"\\begin{frame}{"<<  playlist_name_char << " Cut Table}"<< "\n";

  auto table = makeTableString(5,"l");
  output_string << "\\resizebox{\\textwidth}{!}{" << "\n";
  output_string << "\\begin{table}[]" << "\n";
  output_string << "\\begin{tabular}{||" << table << "|} \n";
  output_string << "Cut name (Playlist " <<  playlist_name_char << " [CryoTank "<< CyroTank_status <<  "]  ) & NEvents & loss &  $\\%$ loss & Total $\\%$ loss \\\\" << "\n";
  output_string << "\\hline \n";
  output_string << "\\hline \n";
double CutValue_previous = inputMap.MC_TRUTH_CutsMap.begin()->second;
double total_events = CutValue_previous;
double combined = 0;
for(Cut_iter = inputMap.MC_TRUTH_CutsMap.begin(); Cut_iter!= inputMap.MC_TRUTH_CutsMap.end(); ++Cut_iter  ){

double CutValue = Cut_iter->second;
double loss = CutValue_previous -  CutValue;
combined = combined + loss;
double loss_percent = (loss / CutValue_previous) * 100;
double total_precent_loss = ((total_events - combined ) / total_events)* 100;

CutValue = roundtoTenth(CutValue);
loss = roundtoTenth(loss);
loss_percent = roundToHundreths(loss_percent);
total_precent_loss = roundToHundreths(total_precent_loss);

output_string << GetCutNameLatexTRUTH(Cut_iter->first) << " & "<< CutValue << " & " << loss << " & " << loss_percent << "&" << total_precent_loss << " \\\\" << "\n";
CutValue_previous = Cut_iter->second;
  output_string << "\\hline \n";

}

  output_string << "\\hline \n";
  output_string << "\\end{tabular} \n";
  output_string << "\\end{table}} \n";
  output_string << "\\end{frame} \n";
  std::ofstream myfile;
  myfile.open(Title);
  myfile<<output_string.str();

  myfile.close();


}//end function


void Playlist_CutTableLatex_Efficiency_Purity(CutMap inputMap , char *playlist_name_char, std::string CyroTank_status   )
{
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"Printing CutRate for:" <<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

  char Title[1024];

  sprintf(Title, "LatexCut_Table_RECO_%s.txt", playlist_name_char );

  double TotalNTruth_forEff = inputMap.MC_TRUTH_CutsMap[kAllTRUTHCuts];



  std::map<ECuts, double>::iterator CutData_iter;
  std::map<ECuts, double>::iterator CutRECO_iter;
  std::map<ECuts, double>::iterator CutRECOHelium_iter;
  std::map<ECuts, double>::iterator TRUTH_RECO_iter;


  std::ostringstream output_string;
  output_string.precision(6);

  output_string <<"\\begin{frame}{"<<  playlist_name_char << " RECO Cut Table}"<< "\n";

  auto table = makeTableString(12,"l");
  output_string << "\\resizebox{\\textwidth}{!}{" << "\n";
  output_string << "\\begin{table}[]" << "\n";
  output_string << "\\begin{tabular}{||" << table << "|} \n";
  output_string << "\\hline \n";
  output_string << "Cut name (Playlist " <<  playlist_name_char <<" [CryoTank "<< CyroTank_status <<  "]  ) & NEvents DATA & loss &  $\\%$ loss & Total $\\%$ loss  & NEvents MC & loss &  $\\%$ loss & Total $\\%$ loss  & $\\%$ Eff &  $\\%$ Purity \\\\" << "\n";
  output_string << "\\hline \n";
  output_string << "\\hline \n";
double CutValue_previous_data = inputMap.DATA_CutsMap.begin()->second;
double total_eventsData = CutValue_previous_data;
double CutValue_previous_Reco = inputMap.MC_RECO_CutsMap.begin()->second;
double total_eventsReco = CutValue_previous_Reco;

double combined_data = 0;
double combined_mc = 0;

for(CutData_iter = inputMap.DATA_CutsMap.begin(),
    CutRECO_iter = inputMap.MC_RECO_CutsMap.begin(),
    CutRECOHelium_iter = inputMap.MC_RECO_Helium_CutsMap.begin(),
    TRUTH_RECO_iter = inputMap.MCRecoBr_TRUTH_RECO_CutsMap.begin();
    CutRECO_iter!= inputMap.MC_RECO_CutsMap.end();
    ++CutRECO_iter, ++CutData_iter, ++CutRECOHelium_iter, ++TRUTH_RECO_iter)
    {

      auto name1 = GetCutNameforLatex(CutData_iter->first);
      auto name2 = GetCutNameforLatex(CutRECO_iter->first);
      auto name3 = GetCutNameforLatex(CutRECOHelium_iter->first);
      auto name4 = GetCutNameforLatex(TRUTH_RECO_iter->first);

      std::cout<< "CutData_iter = " << name1<<std::endl;
      std::cout<< "CutRECO_iter = " << name2<<std::endl;
      std::cout<< "CutRECOHelium_iter = " << name3<<std::endl;
      std::cout<< "TRUTH_RECO_iter = " << name4<<std::endl;
      std::cout<< " "<<std::endl;
      std::cout<< " "<<std::endl;

      if(CutData_iter->first != CutRECO_iter->first ||
        CutData_iter->first != CutRECOHelium_iter->first /*||
        CutData_iter->first != TRUTH_RECO_iter->first*/ ) {

          std::cout<<"Cuts are not the same in loop something needs to be Checked" <<std::endl;
          std::cout<< "CutData_iter->first " << GetCutNameforLatex(CutData_iter->first)<< std::endl;
          std::cout<< "CutRECO_iter->first" << GetCutNameforLatex(CutRECO_iter->first)<< std::endl;
          std::cout<< "CutRECOHelium_iter->first " << GetCutNameforLatex(CutRECOHelium_iter->first)  <<std::endl;
          std::cout<< "TRUTH_RECO_iter->first " << GetCutNameforLatex(TRUTH_RECO_iter->first) <<std::endl;

          assert(false);
        }

        double CutValue_data = CutData_iter->second;
        double loss_data = CutValue_previous_data -  CutValue_data;
        combined_data = combined_data + loss_data;
        double loss_percent_data = (loss_data / CutValue_previous_data) * 100;
        double total_precent_loss_data = ((total_eventsData - CutValue_previous_data) / total_eventsData)* 100;

        double CutValue_MCRECO = CutRECO_iter->second;
        double loss_MCRECO = CutValue_previous_Reco -  CutValue_MCRECO;
        combined_mc = combined_mc + loss_MCRECO;
        double loss_percent_MCRECO = (loss_MCRECO / CutValue_previous_Reco) * 100;
        double total_precent_loss_MCRECO = ((total_eventsReco - combined_mc) / total_eventsReco)* 100;

        double Efficiency =  (TRUTH_RECO_iter->second / TotalNTruth_forEff) * 100 ;
        double Purity =   (CutRECOHelium_iter->second / CutValue_MCRECO) * 100 ;

        std::cout<< "Purity = "<< Purity << "  top = " << CutRECOHelium_iter->second << " bottom =  " << CutValue_MCRECO << std::endl;

        CutValue_data = roundtoTenth(CutValue_data);
        loss_data = roundtoTenth(loss_data);
        loss_percent_data = roundToHundreths(loss_percent_data);
        total_precent_loss_data = roundToHundreths(total_precent_loss_data);
        CutValue_MCRECO = roundtoTenth(CutValue_MCRECO);
        loss_MCRECO = roundToHundreths(loss_MCRECO);
        loss_percent_MCRECO = roundToHundreths(loss_percent_MCRECO);
        total_precent_loss_MCRECO = roundToHundreths(total_precent_loss_MCRECO);
        Efficiency = roundToHundreths(Efficiency);
        Purity = roundToHundreths(Purity);




        output_string << GetCutNameforLatex(CutRECO_iter->first) << " & "<< CutValue_data << " & " << loss_data << " & " << loss_percent_data << "&" <<
        total_precent_loss_data << " & "  <<  CutValue_MCRECO << " & " << loss_MCRECO << " & " << loss_percent_MCRECO << "&" <<
        total_precent_loss_MCRECO <<  " & " <<    Efficiency << " & " << Purity     << " \\\\" << "\n";
        CutValue_previous_data = CutData_iter->second;
        CutValue_previous_Reco = CutRECO_iter->second;
output_string << "\\hline \n";
      }//end function

      output_string << "\\hline \n";
      output_string << "\\end{tabular} \n";
      output_string << "\\end{table}} \n";
      output_string << "\\end{frame} \n";

      std::ofstream myfile;
      myfile.open(Title);
      myfile<<output_string.str();

      myfile.close();



    }


void Make_latexTables_CutMap(CutMap inputMap,char *playlist_name_char, std::string CyroTank_status ){
  std::cout<<"Making Latex Table"<< std::endl;
  Playlist_CutTableLatex_RECO(inputMap , playlist_name_char , CyroTank_status );
  Playlist_CutTableLatex_Efficiency_Purity(inputMap , playlist_name_char, CyroTank_status );
  Playlist_CutTableLatex_TRUTH(inputMap , playlist_name_char, CyroTank_status  );

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
