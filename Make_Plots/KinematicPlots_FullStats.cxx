#include "KinematicPlots_FullStats.h"


std::vector<ME_helium_Playlists> GetPlayListVector();
std::vector<ME_helium_Playlists> GetPlayListVector_DATA();
std::vector<MuonVar> GetMUONVaribles_Total();
std::vector<MuonVar> GetMUONVaribles_Stacks();
void MakeLatexForMuonFiguresCVandGroupErrors_andALLSTACKS(int Systmatic_ErrorType ,std::string output_name ,
  std::vector<MuonVar> muon_vector ,  std::string pdf_name_CV, std::string pdf_stack_Material, std::string pdf_stack_Interaction,
   std::string pdf_stack_Particle,int NError_Groups);
std::vector<SecondTrkVar>Get2ndTrkVaribles();
void MakeLatexForMuonFiguresCVandALLErrors(std::string output_name, std::vector<MuonVar> muon_vector,  std::string PDF_cv_name, int NError_Groups);
void MakeLatexForMuonFiguresFORStacks(std::string output_name ,std::vector<MuonVar> muon_vector ,  std::string pdf_name);
void MakeLatexFORpot(std::string output_name, Pot_MapList POT_MAP_MC, Pot_MapList POT_MAP_Data);
std::string POTLatexString(Pot_MapList POT_MAP_MC, Pot_MapList POT_MAP_Data );
void MakeLatex_MuonCV_Error(std::string output_name, std::vector<MuonVar> muon_vector, std::string pdf_name_CV, int inputstart = 2 );
void MakeLatex_MuonStacks(std::string output_name, std::vector<MuonVar> muon_vector, std::string pdf_name_CV, int inputstart );
void Kin(bool &cutsOn, bool &my_norm, bool &my_debug, const char *userDir, bool &BinNorm , int &Print_Systematics, int &m_CVorStacks ) {
TH1::AddDirectory(false);
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~       Starting Plotter: Kinematic Plots         ~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;


const std::vector<ME_helium_Playlists> kMEPlayList_Vector = GetPlayListVector();
const std::vector<ME_helium_Playlists> kPlayListVector_DATA = GetPlayListVector_DATA();
const std::vector<MuonVar> kMuonVaribles_vector_STACKS = GetMUONVaribles_Stacks();
const std::vector<MuonVar> kMuonVaribles_vector_TOTAL = GetMUONVaribles_Total();
const std::vector<SecondTrkVar> k2ndTrkVaribles_vector = Get2ndTrkVaribles();
int N_Error_groups;
if(Print_Systematics==2 || Print_Systematics == 1) {N_Error_groups=0;}
else if (Print_Systematics==0){N_Error_groups=7;}
std::vector<StackType> StackType_vector;

StackType_vector.push_back(kMaterial );
StackType_vector.push_back(kInteraction);
StackType_vector.push_back(kParticle);



Pot_MapList POT_MC, POT_DATA;

Pot_MapStatusList POT_MC_Status, POT_DATA_Status;

TCanvas *can = new TCanvas("can");
MnvPlotter *mnv_plot = new MnvPlotter();
 char text_title_pdf1[2024];
 char text_title_pdf2[2024];
 char text_title_pdf3[2024];
 char text_title_pdf4[2024];
 char StacksInteraction_title_pdf1[2024];
 char StacksInteraction_title_pdf2[2024];
 char StacksInteraction_title_pdf3[2024];
 char StacksInteraction_title_pdf4[2024];

 char StacksMaterial_title_pdf1[2024];
 char StacksMaterial_title_pdf2[2024];
 char StacksMaterial_title_pdf3[2024];
 char StacksMaterial_title_pdf4[2024];

 char StacksParticle_title_pdf1[2024];
 char StacksParticle_title_pdf2[2024];
 char StacksParticle_title_pdf3[2024];
 char StacksParticle_title_pdf4[2024];
 char Latex_name[2024];
time_t now = time(0);
tm *ltm = localtime(&now);
 char timeset[2024];
 char timeset_nonstacks[2024];
 std::string SysError_printLabel = PrintLabel_Systematics(Print_Systematics);
 auto Playlist_names =  MakePlaylistString(kMEPlayList_Vector);
 //sprintf(timeset_nonstacks,"%i_%i_%i_%i_%s_%s", 1 + ltm->tm_mon,ltm->tm_mday, ltm->tm_hour,ltm->tm_min, SysError_printLabel.c_str(),Playlist_names.c_str());
 //sprintf(timeset, "%i_%i_%i_%i", 1 + ltm->tm_mon,ltm->tm_mday, ltm->tm_hour,ltm->tm_min);
 sprintf(timeset, "");
bool is_mc=true;bool isNOT_mc=false;
//auto Playlist_txtFILEPath = GetPlaylist_txtFILE_path(PlayList_iterator, is_mc );
/*
sprintf(text_title_pdf1, "PLOTS_%s_MuonKinematic_fullstats.pdf(",timeset_nonstacks );
can -> Print(text_title_pdf1);
sprintf(text_title_pdf2, "PLOTS_%s_MuonKinematic_fullstats.pdf",timeset_nonstacks );
sprintf(text_title_pdf3, "PLOTS_%s_MuonKinematic_fullstats.pdf)",timeset_nonstacks );
sprintf(text_title_pdf4, "PLOTS_%s_MuonKinematic_fullstats",timeset_nonstacks );
 std::string pdf_CV = string(text_title_pdf4);
*/


sprintf(text_title_pdf1, "MuonKinematic_fullstats_%s.pdf(",timeset );
can -> Print(text_title_pdf1);
sprintf(text_title_pdf2, "MuonKinematic_fullstats_%s.pdf",timeset );
sprintf(text_title_pdf3, "MuonKinematic_fullstats_%s.pdf)",timeset );
sprintf(text_title_pdf4, "MuonKinematic_fullstats_%s",timeset );
 std::string pdf_CV = string(text_title_pdf4);

 sprintf(StacksInteraction_title_pdf1, "MuonKinematic_InteractionStacks_fullstats_%s.pdf(",timeset );
 can -> Print(StacksInteraction_title_pdf1);
 sprintf(StacksInteraction_title_pdf2, "MuonKinematic_InteractionStacks_fullstats_%s.pdf",timeset );
 sprintf(StacksInteraction_title_pdf3, "MuonKinematic_InteractionStacks_fullstats_%s.pdf)",timeset );
 sprintf(StacksInteraction_title_pdf4, "MuonKinematic_InteractionStacks_fullstats_%s",timeset );
 std::string pdf_InteractionStacks = string(StacksInteraction_title_pdf4);

 sprintf(StacksParticle_title_pdf1, "MuonKinematic_ParticleStacks_fullstats_%s.pdf(",timeset );
 can -> Print(StacksParticle_title_pdf1);
 sprintf(StacksParticle_title_pdf2, "MuonKinematic_ParticleStacks_fullstats_%s.pdf",timeset );
 sprintf(StacksParticle_title_pdf3, "MuonKinematic_ParticleStacks_fullstats_%s.pdf)",timeset );
 sprintf(StacksParticle_title_pdf4, "MuonKinematic_ParticleStacks_fullstats_%s",timeset );
 std::string pdf_ParticleStacks = string(StacksParticle_title_pdf4);


 sprintf(StacksMaterial_title_pdf1, "MuonKinematic_MaterialStacks_fullstats_%s.pdf(",timeset );
 can -> Print(StacksMaterial_title_pdf1);
 sprintf(StacksMaterial_title_pdf2, "MuonKinematic_MaterialStacks_fullstats_%s.pdf",timeset );
 sprintf(StacksMaterial_title_pdf3, "MuonKinematic_MaterialStacks_fullstats_%s.pdf)",timeset );
 sprintf(StacksMaterial_title_pdf4, "MuonKinematic_MaterialStacks_fullstats_%s",timeset );
 std::string pdf_MaterialStacks = string(StacksMaterial_title_pdf4);

std::map<StackType, std::string>  PDF_stackMap;

PDF_stackMap[kMaterial] = pdf_MaterialStacks;
PDF_stackMap[kInteraction] = pdf_InteractionStacks;
PDF_stackMap[kParticle] = pdf_ParticleStacks;


 ME_playlist_RootPathMAP MAP_RootPath_Empty_MC;
 ME_playlist_RootPathMAP MAP_RootPath_OtherEmpty_MC;
 ME_playlist_RootPathMAP MAP_RootPath_Full_MC;

 ME_playlist_RootPathMAP MAP_RootPath_Empty_DATA;
 ME_playlist_RootPathMAP MAP_RootPath_Full_DATA;

/////////////////
/// MC
/////////////////
// Empty Playlist
/////////////////
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
bool DoBinwidthNorm = BinNorm;
bool MakeXaxisLOG = false;
bool MakeYaxisLOG = false;
bool DrawAllerrorGroups = false;

for(auto Muon_Var: kMuonVaribles_vector_TOTAL ){

auto histname = GetMuonVarHistName(Muon_Var);
char histnameMC_char[histname.length()+1];
strcpy( histnameMC_char,histname.c_str());

auto histname_data = GetMuonVarHist_DATAName(Muon_Var);
char histnameDATA_char[histname_data.length()+1];
strcpy( histnameDATA_char ,histname_data.c_str());

auto TITLE = GetMuonVarTitleName(Muon_Var);
char TITLE_char[TITLE.length()+1];
strcpy(TITLE_char,TITLE.c_str());

auto XAxis_name = GetMuonVarAXISName(Muon_Var);
char XAxis_name_char[XAxis_name.length()+1];
strcpy(XAxis_name_char,XAxis_name.c_str());
/*
for(auto Bluebird : StackType_vector){
   DrawSTACKfromHistFilio_FULLStats(FullTFile_Map_MC,  FullPOT_local_MC_ScaledMAP,
                                 EmptyTFile_Map_MC,  EmptyPOT_local_MC_ScaledMAP,
                                 FullTFile_Map_Data, FullPOT_local_Data_ScaledMAP,
                                 EmptyTFile_Map_Data, EmptyPOT_local_Data_ScaledMAP,
      histnameMC_char ,histnameDATA_char, TITLE_char,
     XAxis_name, PDF_stackMap[Bluebird], DoBinwidthNorm, GetMuonUnitType(Muon_Var), Bluebird, my_debug );

     DrawSTACKfromHistFilio_FULLStatsCOMBINED(FullTFile_Map_MC,  FullPOT_local_MC_MAP,
                                   EmptyTFile_Map_MC,            EmptyPOT_local_MC_MAP,
                                   FullTFile_Map_Data,           FullPOT_local_Data_MAP,
                                   EmptyTFile_Map_Data,          EmptyPOT_local_Data_MAP,
        histnameMC_char ,histnameDATA_char, TITLE_char,
       XAxis_name, PDF_stackMap[Bluebird], DoBinwidthNorm, GetMuonUnitType(Muon_Var), Bluebird, my_debug );

}*/

//DrawFULLStat_CV_SystematicErr(FullTFile_Map_MC,  FullPOT_local_MC_ScaledMAP,
//                              EmptyTFile_Map_MC,  EmptyPOT_local_MC_ScaledMAP,
//                              FullTFile_Map_Data, FullPOT_local_Data_ScaledMAP,
//                              EmptyTFile_Map_Data, EmptyPOT_local_Data_ScaledMAP,
//   histnameMC_char ,histnameDATA_char,
//   GetMuonUnitType(Muon_Var), pdf_CV, TITLE_char,
//   XAxis_name_char, "",  DoBinwidthNorm, MakeXaxisLOG, MakeYaxisLOG );

DrawFULLStatCOMBINED_CV_SystematicErr(FullTFile_Map_MC, FullPOT_local_MC_MAP,
                              EmptyTFile_Map_MC,        EmptyPOT_local_MC_MAP,
                              FullTFile_Map_Data,       FullPOT_local_Data_MAP,
                              EmptyTFile_Map_Data,      EmptyPOT_local_Data_MAP,
   histnameMC_char ,histnameDATA_char,
   GetMuonUnitType(Muon_Var), pdf_CV, TITLE_char,
   XAxis_name_char, "",  DoBinwidthNorm, MakeXaxisLOG, DrawAllerrorGroups);

}




can -> Print(text_title_pdf3);
can -> Print(StacksInteraction_title_pdf3);
can -> Print(StacksParticle_title_pdf3);
can -> Print(StacksMaterial_title_pdf3);
can->Close();


std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;

std::cout<< " Done with Muon Plots"<< std::endl;

std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;

MakeLatexFORpot("POT_Slide_FULL", FullPOT_local_MC_MAP, FullPOT_local_Data_MAP );
MakeLatexFORpot("POT_Slide_Empty", EmptyPOT_local_MC_MAP, EmptyPOT_local_Data_MAP );
char latexName[1024];
sprintf(latexName,"Muon_CV_totalerror_Latex_%s", timeset);
MakeLatex_MuonCV_Error(latexName,    kMuonVaribles_vector_TOTAL, pdf_CV, 2);
sprintf(latexName,"Muon_stacks_Interaction_Latex_%s", timeset);
MakeLatex_MuonStacks(latexName, kMuonVaribles_vector_TOTAL, pdf_InteractionStacks, 2 );
sprintf(latexName,"Muon_stacks_Particle_Latex_%s", timeset);
MakeLatex_MuonStacks(latexName,    kMuonVaribles_vector_TOTAL, pdf_ParticleStacks, 2 );
sprintf(latexName,"Muon_stacks_Material_Latex_%s", timeset);
MakeLatex_MuonStacks(latexName,    kMuonVaribles_vector_TOTAL, pdf_MaterialStacks, 2 );


   return;

}



 int main() {

bool cutsOn;
std::cout << "Run over cutsOn?  (0 = false, 1 = true) " << std::endl;
//std::cin >> cutsOn;
cutsOn= true;
std::cout << std::boolalpha << cutsOn << std::endl;

bool my_norm;
std::cout << "Which Normalization?  (0 = POT, 1 = relative equal areas) " << std::endl;
//std::cin >> my_norm;
 my_norm=true;
std::cout << std::boolalpha << my_norm << std::endl;

bool my_BinNormilzed;
std::cout << "Do you want to Bin Width Normlize?  (0 = yes, 1 = no) " << std::endl;
//std::cin >> my_BinNormilzed;
my_BinNormilzed= true;
std::cout << std::boolalpha << my_BinNormilzed << std::endl;

int my_Print_Systmatics;
std::cout << "Print Error Systmatics?  [ 0 = Total and Groups Systemtics Errors ,  1 = Total Systematic Errors , 2 = none ]" << std::endl;
std::cin >> my_Print_Systmatics;
std::cout << "Pitched: " << my_Print_Systmatics << std::endl;


bool my_debug;
std::cout << "Run in Debug Mode? (0 = NO, 1 = YES) " << std::endl;
//std::cin >> my_debug;
my_debug=true;
std::cout << std::boolalpha << my_debug << std::endl;

std::string input;
std::cout << "What is the name of the user? " << std::endl;
//std::cin >> input;
input = "cnguyen";
std::cout << input << std::endl;


int m_CVorStacks;
std::cout << "Make Stacks or CV plots (0 = CV, 1 = Stacks)" << std::endl;
std::cin >> m_CVorStacks;
//std::cout << std::boolalpha << m_CVorStacks << std::endl;
//if(m_CVorStack == true){
  //std::cout << "Making CV plots:" << std::endl;
//}
//else if(m_CVorStacks == false){
  //std::cout << "Making Stacks plots:" << std::endl;//
//}




const char *inputFileLoc = input.c_str();

Kin(cutsOn, my_norm, my_debug, inputFileLoc, my_BinNormilzed, my_Print_Systmatics, m_CVorStacks);

std::cout<< "Done with Program"<<std::endl;

return 0;

}


std::vector<ME_helium_Playlists> GetPlayListVector() {
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






/////////////////////////////////////////////
std::vector<MuonVar> GetMUONVaribles_Total() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<MuonVar> MuonVars;

  //MuonVars.push_back(kMuonMatchtoVeto);
//  MuonVars.push_back(kMuonMatchtoMinos);
  //MuonVars.push_back(kCharge);
  MuonVars.push_back(kE);
  ////MuonVars.push_back(kE_nonECT);
 MuonVars.push_back(kP_Z);
  //MuonVars.push_back(kP_Z_nonECT);

  MuonVars.push_back(kP_T);
  //MuonVars.push_back(kP_T_nonECT);

  MuonVars.push_back(kAngleWRTB);
  MuonVars.push_back(kAnglePhi);
  MuonVars.push_back(kcurvatureSig);
  MuonVars.push_back(kDOCA_muon);
  //MuonVars.push_back(kminosMuon_Energy);
  MuonVars.push_back(ktracksize);
  MuonVars.push_back(kminosStart_X);
  MuonVars.push_back(kminosStart_Y);
  MuonVars.push_back(kminosStart_Z);
  MuonVars.push_back(kminosEnd_X);
  MuonVars.push_back(kminosEnd_Y);
  MuonVars.push_back(kminosEnd_Z);
  MuonVars.push_back(kmuonFirstNodeX);
  MuonVars.push_back(kmuonFirstNodeY);
  MuonVars.push_back(kmuonFirstNodeZ);
  MuonVars.push_back(kmuonLastNodeX);
  MuonVars.push_back(kmuonLastNodeY);
  MuonVars.push_back(kmuonLastNodeZ);



  return MuonVars;
//#endif
}

std::vector<MuonVar> GetMUONVaribles_Stacks() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<MuonVar> MuonVars;

  //MuonVars.push_back(kMuonMatchtoVeto);
  //MuonVars.push_back(kMuonMatchtoMinos);
  //MuonVars.push_back(kCharge);
  MuonVars.push_back(kE);

  MuonVars.push_back(kP_Z);


  MuonVars.push_back(kP_T);


  MuonVars.push_back(kAngleWRTB);
  //MuonVars.push_back(kAnglePhi);
  MuonVars.push_back(kDOCA_muon);
  MuonVars.push_back(kcurvatureSig);
  //MuonVars.push_back(kminosMuon_Energy);


  //MuonVars.push_back(kminosStart_X);
  //MuonVars.push_back(kminosStart_Y);
  //MuonVars.push_back(kminosStart_Z);
  //MuonVars.push_back(kminosEnd_X);
  //MuonVars.push_back(kminosEnd_Y);
  //MuonVars.push_back(kminosEnd_Z);
  //MuonVars.push_back(kmuonFirstNodeX);
  //MuonVars.push_back(kmuonFirstNodeY);
  //MuonVars.push_back(kmuonFirstNodeZ);

  //MuonVars.push_back(kmuonLastNodeX);
  //MuonVars.push_back(kmuonLastNodeY);
  //MuonVars.push_back(kmuonLastNodeZ);

  MuonVars.push_back(ktracksize);


  return MuonVars;
//#endif
}


std::vector<SecondTrkVar> Get2ndTrkVaribles() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<SecondTrkVar> Vector_Vars;

  Vector_Vars.push_back(ksecE);
  Vector_Vars.push_back(kThetamid);
  Vector_Vars.push_back(kOpenAngle);
  Vector_Vars.push_back(kDOCA);
  //Vector_Vars.push_back(ksecDOCA_TRUTH);
  Vector_Vars.push_back(kPathway);

  return Vector_Vars;
//#endif
}


void MakeLatexForMuonFiguresFORStacks(std::string output_name,
  std::vector<MuonVar> muon_vector,  std::string pdf_name)
{
  double scale= .23;
  std::ofstream myfile;
  std::string fileName = output_name + ".txt";
  myfile.open(fileName,	std::ios::trunc);
  std::cout<<"Name of Output File "<< fileName<<std::endl;
  LatexFormat Muon_latex_Latex(scale);

  int pageCount = 2;
  std::cout << " Name of input PDF = "<< pdf_name << std::endl;

  for(auto cat:muon_vector){

    auto input_vectors = GetBinMuonVector(cat);
    std::string Var_name = GetMuonVarTitleName(cat);
    std::string Units_name = GetMuonUnitType(cat);
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%%  Frame Stack For  "<< Var_name <<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<Muon_latex_Latex.GetSubSection(Var_name);
    myfile<<Muon_latex_Latex.GetBeginFrame(Var_name)<< "\n";
    myfile<<Muon_latex_Latex.GetBeginTabular()<< "\n";
    myfile<<Muon_latex_Latex.GetInclude_figure(pageCount,pdf_name)<< "\n";
    myfile<<"& \n";
    myfile<<Muon_latex_Latex.GetInclude_figure(pageCount+1,pdf_name)<< "\n";
    myfile<<"& \n";
    myfile<<Muon_latex_Latex.GetInclude_figure(pageCount+2,pdf_name)<< "\n";
    myfile<<Muon_latex_Latex.GetEndTabular()<< "\n";
    if(input_vectors.size() < 25)
    {
      myfile<<Muon_latex_Latex.BinningLatexString(input_vectors, Var_name , Units_name )<< "\n";
    }
    myfile<<Muon_latex_Latex.GetEndFrame();
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% END FRAME Stack "<< Var_name<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";

    pageCount= pageCount + 3;
  }
  myfile.close();
}//end of Function


void MakeLatexForMuonFiguresCVandALLErrors(std::string output_name ,std::vector<MuonVar> muon_vector,
  std::string PDF_cv_name, int NError_Groups)
  {
    double scale= .24;
    std::ofstream myfile;

    int Column_Spacing=0;
    int pageCount=2;

    if(NError_Groups > 0){

      Column_Spacing = NError_Groups + 2;
    }
    else if (NError_Groups==0){

      Column_Spacing = NError_Groups + 1;
    }

    std::string fileName = output_name + ".txt";
    myfile.open(fileName,	std::ios::trunc);
    std::cout<<"Name of Output File "<< fileName<<std::endl;
    LatexFormat Muon_latex_Latex(scale);

    for(auto cat:muon_vector){

      auto input_vectors = GetBinMuonVector(cat);
      std::string Var_name = GetMuonVarTitleName(cat);
      std::string Units_name = GetMuonUnitType(cat);

      myfile<<"\n";
      myfile<<Muon_latex_Latex.GetSubSection(Var_name);
      myfile<<"\n";
      myfile<<"%%%%%%%%%%%%%%%%% \n";
      myfile<<"%%%  Frame CV and Error grounps For  "<< Var_name <<"\n";
      myfile<<"%%%%%%%%%%%%%%%%% \n";
      myfile<<Muon_latex_Latex.GetBeginFrame(Var_name)<< "\n";
      myfile<<Muon_latex_Latex.GetBeginTabular()<< "\n";
      myfile<<Muon_latex_Latex.GetInclude_figure(pageCount,PDF_cv_name)<< "\n";
      myfile<<"& \n";
      myfile<<Muon_latex_Latex.GetInclude_figure(pageCount + Column_Spacing,PDF_cv_name)<< "\n";
      myfile<<"& \n";
      myfile<<Muon_latex_Latex.GetInclude_figure(pageCount + Column_Spacing + Column_Spacing, PDF_cv_name)<< "\n";
      myfile<<Muon_latex_Latex.GetEndTabular()<< "\n";
      if(input_vectors.size() < 25)
      {
        myfile<<Muon_latex_Latex.BinningLatexString(input_vectors, Var_name , Units_name )<< "\n";
      }
      myfile<<Muon_latex_Latex.GetEndFrame();
      myfile<<"\n";

      myfile<<"%%%%%%%%%%%%%%%%% \n";
      myfile<<"%%% END FRAME Frame CV "<< Var_name<<"\n";
      myfile<<"%%%%%%%%%%%%%%%%% \n";

      if(NError_Groups !=0){


        myfile<<"\n";
        myfile<<"%%%%%%%%%%%%%%%%% \n";
        myfile<<"%%%  Full Error group  "<< Var_name <<"\n";
        myfile<<"%%%%%%%%%%%%%%%%% \n";
        myfile<<Muon_latex_Latex.GetBeginFrame(Var_name)<< "\n";
        myfile<<Muon_latex_Latex.GetBeginTabular()<< "\n";
        myfile<<Muon_latex_Latex.GetInclude_figure(pageCount + 1, PDF_cv_name)<< "\n";
        myfile<<"& \n";
        myfile<<Muon_latex_Latex.GetInclude_figure(pageCount + Column_Spacing + 1, PDF_cv_name )<< "\n";
        myfile<<"& \n";
        myfile<<Muon_latex_Latex.GetInclude_figure(pageCount +  Column_Spacing +  Column_Spacing + 1, PDF_cv_name )<< "\n";
        myfile<<Muon_latex_Latex.GetEndTabular()<< "\n";
        myfile<<Muon_latex_Latex.GetEndFrame();
        myfile<<"\n";
        myfile<<"%%%%%%%%%%%%%%%%% \n";
        myfile<<"%%% END FRAME Frame CV and Error groups "<< Var_name<<"\n";
        myfile<<"%%%%%%%%%%%%%%%%% \n";


        if(NError_Groups != 0){

          for(int i = 0 ; i < NError_Groups; i++ ){

            myfile<<"\n";
            myfile<<"%%%%%%%%%%%%%%%%% \n";
            myfile<<"%%%  Full Error groups  "<< Var_name <<"\n";
            myfile<<"%%%%%%%%%%%%%%%%% \n";
            myfile<<Muon_latex_Latex.GetBeginFrame(Var_name)<< "\n";
            myfile<<Muon_latex_Latex.GetBeginTabular()<< "\n";
            myfile<<Muon_latex_Latex.GetInclude_figure(pageCount + i + 2,PDF_cv_name)<< "\n";
            myfile<<"& \n";
            myfile<<Muon_latex_Latex.GetInclude_figure(pageCount + Column_Spacing + i + 2 ,PDF_cv_name)<< "\n";
            myfile<<"& \n";
            myfile<<Muon_latex_Latex.GetInclude_figure(pageCount +  Column_Spacing + Column_Spacing + i + 2,PDF_cv_name)<< "\n";
            myfile<<Muon_latex_Latex.GetEndTabular()<< "\n";
            myfile<<Muon_latex_Latex.GetEndFrame();
            myfile<<"\n";
            myfile<<"%%%%%%%%%%%%%%%%% \n";
            myfile<<"%%% END FRAME Error groups "<< Var_name<<"\n";
            myfile<<"%%%%%%%%%%%%%%%%% \n";
          }
        }
      }
      pageCount= pageCount +  Column_Spacing +  Column_Spacing + Column_Spacing;
    }
    myfile.close();

  }//end of

  void MakeLatexFORpot(std::string output_name, Pot_MapList POT_MAP_MC, Pot_MapList POT_MAP_Data )
  {
    std::ofstream myfile;
    std::string fileName = output_name + ".txt";
    myfile.open(fileName,std::ios::trunc);
    std::cout<<"Name of Output File "<< fileName<<std::endl;
    LatexFormat Muon_latex_Latex(.25);

    myfile<<Muon_latex_Latex.GetSubSection("POT Info");

    myfile<<"\n";
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% Frame FOR POT INFO \n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<Muon_latex_Latex.GetBeginFrame("POT")<< "\n";
    myfile<<POTLatexString( POT_MAP_MC, POT_MAP_Data )<< "\n";
    myfile<<Muon_latex_Latex.GetEndFrame();

    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% END FRAME  FOR POT Map\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";

    myfile.close();
}//end of function




void MakeLatex_MuonCV_Error(std::string output_name, std::vector<MuonVar> muon_vector, std::string pdf_name_CV, int inputstart ){
  std::ofstream myfile;
  std::string fileName = output_name + ".txt";
  myfile.open(fileName,std::ios::trunc);
  std::cout<<"Name of Output File "<< fileName<<std::endl;
  int index = inputstart;
  LatexFormat Muon_latex_Latex(.2);
  int Column_Spacing =11;


  for(auto cat: muon_vector){

    auto input_vectors = GetBinMuonVector(cat);
    std::string Var_name = GetMuonVarTitleName(cat);
    std::string Units_name = GetMuonUnitType(cat);

    myfile<<Muon_latex_Latex.GetSubSection(Var_name);
    myfile<<"\n";
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% Frame  ALL FULL Playlist Breakdown"<< Var_name <<" \n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<Muon_latex_Latex.GetBeginFrame(GetMuonVarAXISName(cat))<< "\n";
    myfile<<Muon_latex_Latex.GetBeginTabular("ccc")<< "\n";
    myfile<<Muon_latex_Latex.GetInclude_figure(index, pdf_name_CV)<< "\n";
    myfile<<"& \n";
    myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing, pdf_name_CV )<< "\n";
    myfile<<"& \n";
    myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 2, pdf_name_CV)<< "\n";
    myfile<<"\\\\ \n";
    myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 3, pdf_name_CV )<< "\n";
    myfile<<"& \n";
    myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 4, pdf_name_CV)<< "\n";
    myfile<<Muon_latex_Latex.GetEndTabular()<< "\n";
    if(input_vectors.size() < 25)
    {
      myfile<<Muon_latex_Latex.BinningLatexString(input_vectors, Var_name , Units_name )<< "\n";
    }
    myfile<<Muon_latex_Latex.GetEndFrame();

    myfile<<"\n";
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% Frame  ALL  FULL Playlist Error Breakdown"<< Var_name <<" \n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<Muon_latex_Latex.GetBeginFrame(GetMuonVarAXISName(cat))<< "\n";
    myfile<<Muon_latex_Latex.GetBeginTabular("ccc")<< "\n";
    myfile<<Muon_latex_Latex.GetInclude_figure(index + 1, pdf_name_CV)<< "\n";
    myfile<<"& \n";
    myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing + 1, pdf_name_CV )<< "\n";
    myfile<<"& \n";
    myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 2 + 1, pdf_name_CV)<< "\n";
    myfile<<"\\\\ \n";
    myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 3 + 1, pdf_name_CV )<< "\n";
    myfile<<"& \n";
    myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 4 + 1, pdf_name_CV)<< "\n";
    myfile<<Muon_latex_Latex.GetEndTabular()<< "\n";
    if(input_vectors.size() < 25)
    {
      myfile<<Muon_latex_Latex.BinningLatexString(input_vectors, Var_name , Units_name )<< "\n";
    }
    myfile<<Muon_latex_Latex.GetEndFrame();

    //////////////////////////////////////////////////
    //Empty
    /////////////////////////////////////////////////
    myfile<<"\n";
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% Frame  ALL FULL Playlist Breakdown"<< Var_name <<" \n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<Muon_latex_Latex.GetBeginFrame(GetMuonVarAXISName(cat))<< "\n";
    myfile<<Muon_latex_Latex.GetBeginTabular("ccc")<< "\n";
    myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 5, pdf_name_CV)<< "\n";
    myfile<<"& \n";
    myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 6, pdf_name_CV )<< "\n";
    myfile<<"& \n";
    myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 7, pdf_name_CV)<< "\n";
    myfile<<"\\\\ \n";
    myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 8, pdf_name_CV )<< "\n";
    myfile<<"& \n";
    myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 9, pdf_name_CV)<< "\n";
    myfile<<Muon_latex_Latex.GetEndTabular()<< "\n";
    if(input_vectors.size() < 25)
    {
      myfile<<Muon_latex_Latex.BinningLatexString(input_vectors, Var_name , Units_name )<< "\n";
    }
    myfile<<Muon_latex_Latex.GetEndFrame();

    myfile<<"\n";
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% Frame  ALL  FULL Playlist Error Breakdown"<< Var_name <<" \n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<Muon_latex_Latex.GetBeginFrame(GetMuonVarAXISName(cat))<< "\n";
    myfile<<Muon_latex_Latex.GetBeginTabular("ccc")<< "\n";
    myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 5 + 1, pdf_name_CV)<< "\n";
    myfile<<"& \n";
    myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 6 + 1, pdf_name_CV )<< "\n";
    myfile<<"& \n";
    myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 7 + 1, pdf_name_CV)<< "\n";
    myfile<<"\\\\ \n";
    myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 8 + 1, pdf_name_CV )<< "\n";
    myfile<<"& \n";
    myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 9 + 1, pdf_name_CV)<< "\n";
    myfile<<Muon_latex_Latex.GetEndTabular()<< "\n";
    if(input_vectors.size() < 25)
    {
      myfile<<Muon_latex_Latex.BinningLatexString(input_vectors, Var_name , Units_name )<< "\n";
    }
    myfile<<Muon_latex_Latex.GetEndFrame();





    //////////////////////////////////////////////////
    //Full - Empty
    /////////////////////////////////////////////////


    myfile<<"\n";
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% Frame  Total"<< Var_name <<" \n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<Muon_latex_Latex.GetBeginFrame(GetMuonVarAXISName(cat))<< "\n";
    myfile<<Muon_latex_Latex.GetBeginTabular("ccc")<< "\n";
    myfile<<Muon_latex_Latex.GetInclude_figure(index + 110, pdf_name_CV, .24)<< "\n";
    myfile<<"& \n";
    myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing + 110, pdf_name_CV, .24 )<< "\n";
    myfile<<"& \n";
    myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 2 + 110, pdf_name_CV, .24)<< "\n";
    myfile<<Muon_latex_Latex.GetEndTabular()<< "\n";
    if(input_vectors.size() < 25)
    {
      myfile<<Muon_latex_Latex.BinningLatexString(input_vectors, Var_name , Units_name )<< "\n";
    }

      myfile<<Muon_latex_Latex.GetEndFrame();


      myfile<<"\n";
      myfile<<"\n";
      myfile<<"%%%%%%%%%%%%%%%%% \n";
      myfile<<"%%% Frame  Total Error"<< Var_name <<" \n";
      myfile<<"%%%%%%%%%%%%%%%%% \n";
      myfile<<Muon_latex_Latex.GetBeginFrame(GetMuonVarAXISName(cat))<< "\n";
      myfile<<Muon_latex_Latex.GetBeginTabular("ccc")<< "\n";
      myfile<<Muon_latex_Latex.GetInclude_figure(index + 110+1, pdf_name_CV, .24)<< "\n";
      myfile<<"& \n";
      myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing + 110+1, pdf_name_CV, .24 )<< "\n";
      myfile<<"& \n";
      myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 2 + 110+1, pdf_name_CV, .24)<< "\n";
      myfile<<Muon_latex_Latex.GetEndTabular()<< "\n";
      if(input_vectors.size() < 25)
      {
        myfile<<Muon_latex_Latex.BinningLatexString(input_vectors, Var_name , Units_name )<< "\n";
      }

        myfile<<Muon_latex_Latex.GetEndFrame();

        index = index + 143;
      }
      myfile.close();

    }//end of function

void MakeLatex_MuonStacks(std::string output_name, std::vector<MuonVar> muon_vector, std::string pdf_name_CV, int inputstart ){
  std::ofstream myfile;
  std::string fileName = output_name + ".txt";
  myfile.open(fileName,std::ios::trunc);
  std::cout<<"Name of Output File "<< fileName<<std::endl;
  int index = inputstart;
  LatexFormat Muon_latex_Latex(.2);
  int Column_Spacing =1;

  for(auto cat: muon_vector){

    auto input_vectors = GetBinMuonVector(cat);
    std::string Var_name = GetMuonVarTitleName(cat);
    std::string Units_name = GetMuonUnitType(cat);

    myfile<<Muon_latex_Latex.GetSubSection(Var_name);
    myfile<<"\n";
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% Frame  ALL FULL Playlist Breakdown"<< Var_name <<" \n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<Muon_latex_Latex.GetBeginFrame(GetMuonVarAXISName(cat))<< "\n";
    myfile<<Muon_latex_Latex.GetBeginTabular("ccc")<< "\n";
    myfile<<Muon_latex_Latex.GetInclude_figure(index, pdf_name_CV)<< "\n";
    myfile<<"& \n";
    myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing, pdf_name_CV )<< "\n";
    myfile<<"& \n";
    myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 2, pdf_name_CV)<< "\n";
    myfile<<"\\\\ \n";
    myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 3, pdf_name_CV )<< "\n";
    myfile<<"& \n";
    myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 4, pdf_name_CV)<< "\n";
    myfile<<Muon_latex_Latex.GetEndTabular()<< "\n";
    if(input_vectors.size() < 25)
    {

      myfile<<Muon_latex_Latex.BinningLatexString(input_vectors, Var_name , Units_name )<< "\n";
      }
      myfile<<Muon_latex_Latex.GetEndFrame();

      myfile<<"\n";
      myfile<<"\n";
      myfile<<"%%%%%%%%%%%%%%%%% \n";
      myfile<<"%%% Frame ALL FULL Playlist Breakdown"<< Var_name <<" \n";
      myfile<<"%%%%%%%%%%%%%%%%% \n";
      myfile<<Muon_latex_Latex.GetBeginFrame(GetMuonVarAXISName(cat))<< "\n";
      myfile<<Muon_latex_Latex.GetBeginTabular("ccc")<< "\n";
      myfile<<Muon_latex_Latex.GetInclude_figure(index+ Column_Spacing * 5, pdf_name_CV)<< "\n";
      myfile<<"& \n";
      myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 6, pdf_name_CV )<< "\n";
      myfile<<"& \n";
      myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 7, pdf_name_CV)<< "\n";
      myfile<<"\\\\ \n";
      myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 8, pdf_name_CV )<< "\n";
      myfile<<"& \n";
      myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 9, pdf_name_CV)<< "\n";
      myfile<<Muon_latex_Latex.GetEndTabular()<< "\n";
      if(input_vectors.size() < 25)
      {

        myfile<<Muon_latex_Latex.BinningLatexString(input_vectors, Var_name , Units_name )<< "\n";
        }
        myfile<<Muon_latex_Latex.GetEndFrame();


        myfile<<"\n";
        myfile<<"\n";
        myfile<<"%%%%%%%%%%%%%%%%% \n";
        myfile<<"%%% Frame  Total Error"<< Var_name <<" \n";
        myfile<<"%%%%%%%%%%%%%%%%% \n";
        myfile<<Muon_latex_Latex.GetBeginFrame(GetMuonVarAXISName(cat))<< "\n";
        myfile<<Muon_latex_Latex.GetBeginTabular("ccc")<< "\n";
        myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 10, pdf_name_CV, .24)<< "\n";
        myfile<<"& \n";
        myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 11, pdf_name_CV, .24 )<< "\n";
        myfile<<"& \n";
        myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 12, pdf_name_CV, .24)<< "\n";
        myfile<<Muon_latex_Latex.GetEndTabular()<< "\n";
        if(input_vectors.size() < 25)
        {
          myfile<<Muon_latex_Latex.BinningLatexString(input_vectors, Var_name , Units_name )<< "\n";
        }

          myfile<<Muon_latex_Latex.GetEndFrame();

          index= index + 13;

  }

  myfile.close();


}//end of function





std::string POTLatexString(Pot_MapList POT_MAP_MC, Pot_MapList POT_MAP_Data ){
  assert(CompareMap_ME_helium_PlaylistsKeys(POT_MAP_MC,  POT_MAP_Data) && "POT list for LATEX DONT matches ");

  typename std::map<ME_helium_Playlists, double>::const_iterator cat;
  typename std::map<ME_helium_Playlists, double>::const_iterator dog;

  double total_MC = 0.0;
  double total_data = 0.0;

  std::ostringstream output_string;
  output_string.precision(4);
  output_string << "\\resizebox{\\textwidth}{!}{" << "\n";
  output_string << "\\begin{tabular}{||c|c|c|c||} \n";
  output_string << "\\hline \n";
  output_string << "Playlist & MC POT & Data POT & CryoTank Status  \\\\ \n ";
  for(cat = POT_MAP_MC.begin(), dog = POT_MAP_Data.begin(); cat != POT_MAP_MC.end(); ++cat, ++dog)
  {
    std::string Playlist_Intial =  GetPlaylist_InitialName(cat->first);
    auto status = GetPlaylist_HeliumStatus(cat->first);
    std::string helium_status_string = GetPlaylistStatusString(status);

    output_string <<   Playlist_Intial <<"&"<<cat->second  <<"&"<<dog->second <<"&" << helium_status_string <<" \\\\ \n" ;
    total_MC = total_MC + cat->second;
    total_data = total_data  + dog->second;
  }

  output_string << "\\hline \n";
  output_string << "& & & \\\\ \n";
  output_string << "\\hline \n";
  output_string << "Total POT &" << total_MC << "&" << total_data << "& \\\\ \n";
  output_string << "\\end{tabular}} \n";
  return output_string.str();


}












void MakeLatexForMuonFiguresCVandGroupErrors_andALLSTACKS(int Systmatic_ErrorType ,std::string output_name ,
std::vector<MuonVar> muon_vector ,  std::string pdf_name_CV, std::string pdf_stack_Material, std::string pdf_stack_Interaction,
std::string pdf_stack_Particle,int NError_Groups)
{
double scale= .25;
std::ofstream myfile;
int error_space;
if(Systmatic_ErrorType==2){error_space=1;}
else if(Systmatic_ErrorType==1 || Systmatic_ErrorType==0){error_space=2;}

const int  Column_Spacing = NError_Groups + error_space;

std::string fileName = output_name + ".txt";
myfile.open(fileName,std::ios::trunc);
std::cout<<"Name of Output File "<< fileName<<std::endl;
LatexFormat Muon_latex_Latex(scale);

int pageCount = 2;
int StackpageCount=2;

myfile<<Muon_latex_Latex.GetSubSection("Muon Varibles");
for(auto cat: muon_vector){

  auto input_vectors = GetBinMuonVector(cat);
  std::string Var_name = GetMuonVarTitleName(cat);
  std::string Units_name = GetMuonUnitType(cat);


  myfile<<"\n";
  myfile<<"\n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<"%%% Frame CV "<< Var_name <<" \n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<Muon_latex_Latex.GetBeginFrame(Var_name)<< "\n";
  myfile<<Muon_latex_Latex.GetBeginTabular()<< "\n";
  myfile<<Muon_latex_Latex.GetInclude_figure(pageCount, pdf_name_CV)<< "\n";
  myfile<<"& \n";
  myfile<<Muon_latex_Latex.GetInclude_figure(pageCount + Column_Spacing, pdf_name_CV )<< "\n";
  myfile<<"& \n";
  myfile<<Muon_latex_Latex.GetInclude_figure(pageCount + Column_Spacing + Column_Spacing, pdf_name_CV)<< "\n";
  myfile<<Muon_latex_Latex.GetEndTabular()<< "\n";
  if(input_vectors.size() < 25)
  {
    myfile<<Muon_latex_Latex.BinningLatexString(input_vectors, Var_name , Units_name )<< "\n";
  }
  myfile<<Muon_latex_Latex.GetEndFrame();

  myfile<<"\n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<"%%% END FRAME Frame CV and Error groups "<< Var_name<<"\n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";

  myfile<<"\n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<"%%%  Material Stacks  "<< Var_name <<"\n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<Muon_latex_Latex.GetBeginFrame(Var_name+ " Material Stacks ")<< "\n";
  myfile<<Muon_latex_Latex.GetBeginTabular()<< "\n";
  myfile<<Muon_latex_Latex.GetInclude_figure(StackpageCount ,pdf_stack_Material)<< "\n";
  myfile<<"& \n";
  myfile<<Muon_latex_Latex.GetInclude_figure(StackpageCount + 1 ,pdf_stack_Material )<< "\n";
  myfile<<"& \n";
  myfile<<Muon_latex_Latex.GetInclude_figure(StackpageCount +  2 ,pdf_stack_Material )<< "\n";
  myfile<<Muon_latex_Latex.GetEndTabular()<< "\n";
  myfile<<Muon_latex_Latex.GetEndFrame();
  myfile<<"\n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<"%%% END FRAME Frame CV and Error groups "<< Var_name<<"\n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";

  myfile<<"\n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<"%%%  Interaction  Stacks  "<< Var_name <<"\n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<Muon_latex_Latex.GetBeginFrame(Var_name + " Interaction Stacks ")<< "\n";
  myfile<<Muon_latex_Latex.GetBeginTabular()<< "\n";
  myfile<<Muon_latex_Latex.GetInclude_figure(StackpageCount , pdf_stack_Interaction)<< "\n";
  myfile<<"& \n";
  myfile<<Muon_latex_Latex.GetInclude_figure(StackpageCount + 1 ,pdf_stack_Interaction )<< "\n";
  myfile<<"& \n";
  myfile<<Muon_latex_Latex.GetInclude_figure(StackpageCount + 2 ,pdf_stack_Interaction )<< "\n";
  myfile<<Muon_latex_Latex.GetEndTabular()<< "\n";
  myfile<<Muon_latex_Latex.GetEndFrame();
  myfile<<"\n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<"%%% END FRAME Interaction "<< Var_name<<"\n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";


  myfile<<"\n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<"%%%  Particle  Stacks  "<< Var_name <<"\n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<Muon_latex_Latex.GetBeginFrame(Var_name+ " Particle Stacks ")<< "\n";
  myfile<<Muon_latex_Latex.GetBeginTabular()<< "\n";
  myfile<<Muon_latex_Latex.GetInclude_figure(StackpageCount, pdf_stack_Particle)<< "\n";
  myfile<<"& \n";
  myfile<<Muon_latex_Latex.GetInclude_figure(StackpageCount +  1 ,pdf_stack_Particle )<< "\n";
  myfile<<"& \n";
  myfile<<Muon_latex_Latex.GetInclude_figure(StackpageCount +  2 ,pdf_stack_Particle )<< "\n";
  myfile<<Muon_latex_Latex.GetEndTabular()<< "\n";
  myfile<<Muon_latex_Latex.GetEndFrame();
  myfile<<"\n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<"%%% END FRAME Particle "<< Var_name<<"\n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";

  pageCount = pageCount +  Column_Spacing + Column_Spacing + 1;
  StackpageCount  = StackpageCount  + 3;
}


myfile.close();
}//end of function
