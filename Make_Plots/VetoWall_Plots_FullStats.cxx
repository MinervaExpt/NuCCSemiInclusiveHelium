
#include "VetoWall_Plots_FullStats.h"
//////////////////////////////////////////////////////////////////////////////
std::vector<ME_helium_Playlists> GetPlayListVector_MC();
std::vector<ME_helium_Playlists> GetPlayListVector_DATA();
std::vector<VetoWall_vars> GetVetowall_Varibles();
void Kin(bool &cutsOn, bool &my_norm, bool &my_debug, const char *userDir) {
  TH1::AddDirectory(false);
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"~~~~~       Starting Plotter: Veto Wall Plots         ~~~~~"<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

const std::vector< ME_helium_Playlists> kMEPlayList_Vector = GetPlayListVector_MC();
const std::vector<VetoWall_vars> kVetoWallVaribles_vector = GetVetowall_Varibles();

TCanvas *can = new TCanvas("can");
MnvPlotter *mnv_plot = new MnvPlotter();
 char text_title_pdf1[2024];
 char text_title_pdf2[2024];
 char text_title_pdf3[2024];
 char text_title_pdf4[2024];
time_t now = time(0);
tm *ltm = localtime(&now);
 char timeset[2024];
sprintf(timeset,"%i_%i_%i_%i",1 + ltm->tm_mon,ltm->tm_mday, ltm->tm_hour,ltm->tm_min);


sprintf(text_title_pdf1, "Plots_VETOWALL_Fullstats.pdf(" );
can -> Print(text_title_pdf1);
sprintf(text_title_pdf2, "Plots_VETOWALL_Fullstats.pdf" );
sprintf(text_title_pdf2, "Plots_VETOWALL_Fullstats.pdf" );
sprintf(text_title_pdf3, "Plots_VETOWALL_Fullstats.pdf)" );
sprintf(text_title_pdf4, "Plots_VETOWALL_Fullstats" );
/////////////////
/// MC
/////////////////
// Empty Playlist
/////////////////


ME_playlist_RootPathMAP MAP_RootPath_Empty_MC;
ME_playlist_RootPathMAP MAP_RootPath_OtherEmpty_MC;
ME_playlist_RootPathMAP MAP_RootPath_Full_MC;

ME_playlist_RootPathMAP MAP_RootPath_Empty_DATA;
ME_playlist_RootPathMAP MAP_RootPath_Full_DATA;

auto PlaylistME_1G_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1G_MC_All_SysErrorsOn.root";
auto PlaylistME_1A_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1A_MC_All_SysErrorsOn.root";
auto PlaylistME_1L_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1L_MC_All_SysErrorsOn.root";
auto PlaylistME_1M_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1M_MC_All_SysErrorsOn.root";
auto PlaylistME_1N_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1N_MC_All_SysErrorsOn.root";
MAP_RootPath_Empty_MC.insert(std::make_pair(kMEPlayList_Vector.at(0), PlaylistME_1G_MC_path));
MAP_RootPath_Empty_MC.insert(std::make_pair(kMEPlayList_Vector.at(1), PlaylistME_1A_MC_path));
MAP_RootPath_Empty_MC.insert(std::make_pair(kMEPlayList_Vector.at(2), PlaylistME_1L_MC_path));
MAP_RootPath_Empty_MC.insert(std::make_pair(kMEPlayList_Vector.at(3), PlaylistME_1M_MC_path));
MAP_RootPath_Empty_MC.insert(std::make_pair(kMEPlayList_Vector.at(4), PlaylistME_1N_MC_path));
////////
//Full//
////////
auto PlaylistME_1P_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1P_MC_All_SysErrorsOn.root";
auto PlaylistME_1C_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1C_MC_All_SysErrorsOn.root";
auto PlaylistME_1D_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1D_MC_All_SysErrorsOn.root";
auto PlaylistME_1F_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1F_MC_All_SysErrorsOn.root";
auto PlaylistME_1E_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1E_MC_All_SysErrorsOn.root";
MAP_RootPath_Full_MC.insert(std::make_pair(kMEPlayList_Vector.at(5), PlaylistME_1P_MC_path));
MAP_RootPath_Full_MC.insert(std::make_pair(kMEPlayList_Vector.at(6), PlaylistME_1C_MC_path));
MAP_RootPath_Full_MC.insert(std::make_pair(kMEPlayList_Vector.at(7), PlaylistME_1D_MC_path));
MAP_RootPath_Full_MC.insert(std::make_pair(kMEPlayList_Vector.at(8), PlaylistME_1F_MC_path));
MAP_RootPath_Full_MC.insert(std::make_pair(kMEPlayList_Vector.at(9), PlaylistME_1E_MC_path));
/////////////////
/// Data
/////////////////
/////////////////
// Empty
/////////////////
auto PlaylistME_1G_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1G_Data.root";
auto PlaylistME_1A_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1A_Data.root";
auto PlaylistME_1L_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1L_Data.root";
auto PlaylistME_1M_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1M_Data.root";
auto PlaylistME_1N_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1N_Data.root";
//////////////////
MAP_RootPath_Empty_DATA.insert(std::make_pair(kMEPlayList_Vector.at(0), PlaylistME_1G_Data_path));
MAP_RootPath_Empty_DATA.insert(std::make_pair(kMEPlayList_Vector.at(1), PlaylistME_1A_Data_path));
MAP_RootPath_Empty_DATA.insert(std::make_pair(kMEPlayList_Vector.at(2), PlaylistME_1L_Data_path));
MAP_RootPath_Empty_DATA.insert(std::make_pair(kMEPlayList_Vector.at(3), PlaylistME_1M_Data_path));
MAP_RootPath_Empty_DATA.insert(std::make_pair(kMEPlayList_Vector.at(4), PlaylistME_1N_Data_path));
//////////////
//Full
//////////////
auto PlaylistME_1P_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1P_Data.root";
auto PlaylistME_1C_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1C_Data.root";
auto PlaylistME_1D_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1D_Data.root";
auto PlaylistME_1F_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1F_Data.root";
auto PlaylistME_1E_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1E_Data.root";

////////////////////
MAP_RootPath_Full_DATA.insert(std::make_pair(kMEPlayList_Vector.at(5), PlaylistME_1P_Data_path));
MAP_RootPath_Full_DATA.insert(std::make_pair(kMEPlayList_Vector.at(6), PlaylistME_1C_Data_path));
MAP_RootPath_Full_DATA.insert(std::make_pair(kMEPlayList_Vector.at(7), PlaylistME_1D_Data_path));
MAP_RootPath_Full_DATA.insert(std::make_pair(kMEPlayList_Vector.at(8), PlaylistME_1F_Data_path));
MAP_RootPath_Full_DATA.insert(std::make_pair(kMEPlayList_Vector.at(9), PlaylistME_1E_Data_path));
////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////

Pot_MapList EmptyPOT_local_MC_MAP = Constuct_POT_playlistMap(MAP_RootPath_Empty_MC, true);
Pot_MapList FullPOT_local_MC_MAP  = Constuct_POT_playlistMap(MAP_RootPath_Full_MC, true);

Pot_MapList EmptyPOT_local_Data_MAP = Constuct_POT_playlistMap(MAP_RootPath_Empty_DATA, false);
Pot_MapList FullPOT_local_Data_MAP  = Constuct_POT_playlistMap(MAP_RootPath_Full_DATA, false);

//PlotUtils::POTCounter *PotCounter_Object; // unsure why the plotulits pot function isn't work need to revist

//Pot_MapList EmptyPOT_MC_MAP = Constuct_POT_playlistMap(PotCounter_Object, MAP_RootPath_OtherEmpty_MC);
//Pot_MapList FullPOT_MC_MAP = Constuct_POT_playlistMap(PotCounter_Object, MAP_RootPath_Full_MC);


PrintPot_MapList(EmptyPOT_local_MC_MAP, "EmptyPOT_local_MC_MAP"  );
PrintPot_MapList(FullPOT_local_MC_MAP, "FullPOT_local_MC_MAP"  );

PrintPot_MapList(EmptyPOT_local_Data_MAP, "EmptyPOT_local_Data_MAP"  );
PrintPot_MapList(FullPOT_local_Data_MAP, "FullPOT_local_Data_MAP"  );


Pot_MapList EmptyPOT_local_MC_ScaledMAP = POT_ScalersMap(EmptyPOT_local_MC_MAP ,FullPOT_local_Data_MAP[kMEPlayList_Vector.at(8)] );
Pot_MapList FullPOT_local_MC_ScaledMAP = POT_ScalersMap(FullPOT_local_MC_MAP ,FullPOT_local_Data_MAP[kMEPlayList_Vector.at(8)] );

Pot_MapList EmptyPOT_local_Data_ScaledMAP = POT_ScalersMap(EmptyPOT_local_Data_MAP ,FullPOT_local_Data_MAP[kMEPlayList_Vector.at(8)] );
Pot_MapList FullPOT_local_Data_ScaledMAP = POT_ScalersMap(FullPOT_local_Data_MAP ,FullPOT_local_Data_MAP[kMEPlayList_Vector.at(8)] );


PrintPot_MapList(EmptyPOT_local_MC_ScaledMAP, "EmptyPOT_local_MC_ScaledMAP"  );
PrintPot_MapList(FullPOT_local_MC_ScaledMAP, "FullPOT_local_MC_ScaledMAP"  );

PrintPot_MapList(EmptyPOT_local_Data_ScaledMAP, "EmptyPOT_local_Data_ScaledMAP"  );
PrintPot_MapList(FullPOT_local_Data_ScaledMAP, "FullPOT_local_Data_ScaledMAP"  );


ME_playlist_TFileMAP EmptyTFile_Map_MC;

TFile *PlaylistME_1G_TFile = new TFile(PlaylistME_1G_MC_path);
TFile *PlaylistME_1A_TFile = new TFile(PlaylistME_1A_MC_path);
TFile *PlaylistME_1L_TFile = new TFile(PlaylistME_1L_MC_path);
TFile *PlaylistME_1M_TFile = new TFile(PlaylistME_1M_MC_path);
TFile *PlaylistME_1N_TFile = new TFile(PlaylistME_1N_MC_path);
EmptyTFile_Map_MC.insert(std::make_pair(kMEPlayList_Vector.at(0),PlaylistME_1G_TFile));
EmptyTFile_Map_MC.insert(std::make_pair(kMEPlayList_Vector.at(1),PlaylistME_1A_TFile));
EmptyTFile_Map_MC.insert(std::make_pair(kMEPlayList_Vector.at(2),PlaylistME_1L_TFile));
EmptyTFile_Map_MC.insert(std::make_pair(kMEPlayList_Vector.at(3),PlaylistME_1M_TFile));
EmptyTFile_Map_MC.insert(std::make_pair(kMEPlayList_Vector.at(4),PlaylistME_1N_TFile));



ME_playlist_TFileMAP FullTFile_Map_MC;
TFile *PlaylistME_1P_TFile = new TFile(PlaylistME_1P_MC_path);
TFile *PlaylistME_1C_TFile = new TFile(PlaylistME_1C_MC_path);
TFile *PlaylistME_1D_TFile = new TFile(PlaylistME_1D_MC_path);
TFile *PlaylistME_1F_TFile = new TFile(PlaylistME_1F_MC_path);
TFile *PlaylistME_1E_TFile = new TFile(PlaylistME_1E_MC_path);
FullTFile_Map_MC.insert(std::make_pair(kMEPlayList_Vector.at(5),PlaylistME_1P_TFile));
FullTFile_Map_MC.insert(std::make_pair(kMEPlayList_Vector.at(6),PlaylistME_1C_TFile));
FullTFile_Map_MC.insert(std::make_pair(kMEPlayList_Vector.at(7),PlaylistME_1D_TFile));
FullTFile_Map_MC.insert(std::make_pair(kMEPlayList_Vector.at(8),PlaylistME_1F_TFile));
FullTFile_Map_MC.insert(std::make_pair(kMEPlayList_Vector.at(9),PlaylistME_1E_TFile));


ME_playlist_TFileMAP FullTFile_Map_Data;

TFile *PlaylistME_1P_DATA_TFile = new TFile(PlaylistME_1P_Data_path);
TFile *PlaylistME_1C_DATA_TFile = new TFile(PlaylistME_1C_Data_path);
TFile *PlaylistME_1D_DATA_TFile = new TFile(PlaylistME_1D_Data_path);
TFile *PlaylistME_1F_DATA_TFile = new TFile(PlaylistME_1F_Data_path);
TFile *PlaylistME_1E_DATA_TFile = new TFile(PlaylistME_1E_Data_path);
FullTFile_Map_Data.insert(std::make_pair(kMEPlayList_Vector.at(5),PlaylistME_1P_DATA_TFile));
FullTFile_Map_Data.insert(std::make_pair(kMEPlayList_Vector.at(6),PlaylistME_1C_DATA_TFile));
FullTFile_Map_Data.insert(std::make_pair(kMEPlayList_Vector.at(7),PlaylistME_1D_DATA_TFile));
FullTFile_Map_Data.insert(std::make_pair(kMEPlayList_Vector.at(8),PlaylistME_1F_DATA_TFile));
FullTFile_Map_Data.insert(std::make_pair(kMEPlayList_Vector.at(9),PlaylistME_1E_DATA_TFile));



ME_playlist_TFileMAP EmptyTFile_Map_Data;

TFile *PlaylistME_1G_DATA_TFile = new TFile(PlaylistME_1G_Data_path);
TFile *PlaylistME_1A_DATA_TFile = new TFile(PlaylistME_1A_Data_path);
TFile *PlaylistME_1L_DATA_TFile = new TFile(PlaylistME_1L_Data_path);
TFile *PlaylistME_1M_DATA_TFile = new TFile(PlaylistME_1M_Data_path);
TFile *PlaylistME_1N_DATA_TFile = new TFile(PlaylistME_1N_Data_path);
EmptyTFile_Map_Data.insert(std::make_pair(kMEPlayList_Vector.at(0),PlaylistME_1G_DATA_TFile));
EmptyTFile_Map_Data.insert(std::make_pair(kMEPlayList_Vector.at(1),PlaylistME_1A_DATA_TFile));
EmptyTFile_Map_Data.insert(std::make_pair(kMEPlayList_Vector.at(2),PlaylistME_1L_DATA_TFile));
EmptyTFile_Map_Data.insert(std::make_pair(kMEPlayList_Vector.at(3),PlaylistME_1M_DATA_TFile));
EmptyTFile_Map_Data.insert(std::make_pair(kMEPlayList_Vector.at(4),PlaylistME_1N_DATA_TFile));


std::string pdf = string(text_title_pdf4);

bool DoBinwidthNorm = true;
bool MakeXaxisLOG = false;
bool is_mc=true;
bool isNOT_mc=false;
bool PrintallErrorGroups = false;
std::string pdf_CV = string(text_title_pdf4);


for(auto VetoWall_index: kVetoWallVaribles_vector ){

  auto histname = GetVetowallHistName(VetoWall_index);
  char histnameMC_char[histname.length()+1];
  strcpy( histnameMC_char,histname.c_str());

  auto histname_data = GetVetowallHist_DataName(VetoWall_index);
  char histnameDATA_char[ histname_data.length()+1];
  strcpy( histnameDATA_char,histname_data.c_str());

  std::cout << " histname = "<< histname<<std::endl;
  std::cout << " histname_car = "<< histnameMC_char<<std::endl;
  std::cout << " histnameData = "<< histname_data<<std::endl;
  std::cout << " histnameData_car = "<< histnameDATA_char<<std::endl;

  auto title_his = GetVetowall_Title(VetoWall_index);
  char TITLE_char[title_his.length()+1];
  strcpy(TITLE_char,title_his.c_str());

  auto XAxis_name = GetVetowall_XAxisTitle(VetoWall_index);
  char XAxis_name_char[XAxis_name.length()+1];
  strcpy(XAxis_name_char,XAxis_name.c_str());

    DrawFULLStat_CV_SystematicErr(FullTFile_Map_MC,  FullPOT_local_MC_ScaledMAP,
                                  EmptyTFile_Map_MC,  EmptyPOT_local_MC_ScaledMAP,
                                  FullTFile_Map_Data, FullPOT_local_Data_ScaledMAP,
                                  EmptyTFile_Map_Data, EmptyPOT_local_Data_ScaledMAP,
       histnameMC_char ,histnameDATA_char,
       GetVetowall_UnitType(VetoWall_index), pdf_CV, TITLE_char,
       XAxis_name_char, "",  DoBinwidthNorm, MakeXaxisLOG, PrintallErrorGroups);

    DrawFULLStatCOMBINED_CV_SystematicErr(FullTFile_Map_MC,  FullPOT_local_MC_MAP,
                                EmptyTFile_Map_MC,  EmptyPOT_local_MC_MAP,
                                FullTFile_Map_Data, FullPOT_local_Data_MAP,
                                EmptyTFile_Map_Data, EmptyPOT_local_Data_MAP,
     histnameMC_char ,histnameDATA_char,
     GetVetowall_UnitType(VetoWall_index), pdf_CV, TITLE_char,
     XAxis_name_char, "",  DoBinwidthNorm, MakeXaxisLOG, PrintallErrorGroups );

}


   std::cout << std::endl;
   std::cout << "Done WITH VetoWall" << std::endl;
   can -> Print(text_title_pdf3);










}//End of MainFuntion





/////////////////////////////////////////////
//Main Function
/////////////////////////////////////////////

 int main() {

bool cutsOn= true;
std::cout << "Run over cutsOn?  (0 = false, 1 = true) " << std::endl;
//std::cin >> cutsOn;
std::cout << std::boolalpha << cutsOn << std::endl;

bool my_norm = false;
std::cout << "Which Normalization?  (0 = POT, 1 = relative equal areas) " << std::endl;
std::cout << std::boolalpha << my_norm << std::endl;

bool my_debug= true;
std::cout << "Run in Debug Mode? (0 = NO, 1 = YES) " << std::endl;
//std::cin >> my_debug;
std::cout << std::boolalpha << my_debug << std::endl;

std::string input = "cnguyen";
std::cout << "What is the name of the user? " << std::endl;
//std::cin >> input;
std::cout << input << std::endl;

const char *inputFileLoc = input.c_str();

Kin(cutsOn, my_norm, my_debug, inputFileLoc);

return 0;

}


//////////////////////////////////////////////////////////////////////////
//GET Vertex Varibles
//////////////////////////////////////////////////////////////////////////
std::vector<VetoWall_vars> GetVetowall_Varibles() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<VetoWall_vars> VetowallVars;


  VetowallVars.push_back(kmatchToVeto );
  VetowallVars.push_back(knumbermatchToVeto);
  VetowallVars.push_back(kSixPush);
  VetowallVars.push_back(kextrapnowalls);
  VetowallVars.push_back(kextrapwall1);
  VetowallVars.push_back(kextrapwall2);
  VetowallVars.push_back(kextrapbothwalls);
  VetowallVars.push_back(kMuonTrkMatchToVETOwalloff);
  VetowallVars.push_back(kPMTMap_On);
  //VetowallVars.push_back(kPMTMap_Off);


  return VetowallVars;
//#endif
}

std::vector<ME_helium_Playlists> GetPlayListVector_MC() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ME_helium_Playlists> Playlist;

  //EMPTY
    Playlist.push_back(kME1G);
    Playlist.push_back(kME1A);
    Playlist.push_back(kME1L);
    Playlist.push_back(kME1M);
    Playlist.push_back(kME1N);
  //Full
    Playlist.push_back(kME1P);
    Playlist.push_back(kME1C);
    Playlist.push_back(kME1D);
    Playlist.push_back(kME1F);
    Playlist.push_back(kME1E);
  return Playlist;
//#endif
}
std::vector<ME_helium_Playlists> GetPlayListVector_DATA() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ME_helium_Playlists> Playlist;


  //EMPTY
    Playlist.push_back(kME1G);
    Playlist.push_back(kME1A);
    Playlist.push_back(kME1L);
    Playlist.push_back(kME1M);
    Playlist.push_back(kME1N);
  //Full
    Playlist.push_back(kME1P);
    Playlist.push_back(kME1C);
    Playlist.push_back(kME1D);
    Playlist.push_back(kME1F);
    Playlist.push_back(kME1E);

  return Playlist;
//#endif
}
