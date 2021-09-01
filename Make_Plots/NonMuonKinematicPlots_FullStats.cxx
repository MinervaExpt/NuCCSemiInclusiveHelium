

#include "NonMuonKinematicPlots_FullStats.h"
//////////////////////////////////////////////////////////////////////////////

std::vector<ME_helium_Playlists> GetPlayListVector_MC();
std::vector<ME_helium_Playlists> GetPlayListVector_DATA();
void MakeLatexForNonMuonFiguresCVandGroupErrors_andALLSTACKS(int Systmatic_ErrorType ,std::string output_name ,
std::vector<SecondTrkVar> NoN_muon_vector,  std::string pdf_name_CV, std::string pdf_stack_Material, std::string pdf_stack_Interaction,
  std::string pdf_stack_Particle,int NError_Groups);
void MakeLatexForNonMuonFiguresCVandALLErrors(std::string output_name ,std::vector<SecondTrkVar> NoN_muon_vector,
  std::string PDF_cv_name, int NError_Groups);

void MakeLatexForNonMuonFiguresFORStacks(std::string output_name ,std::vector<SecondTrkVar> NoN_muon_vector ,  std::string pdf_name);
void MakeLatex_RecoilStacks(std::string output_name, std::vector<SecondTrkVar> Recoil_vector, std::string pdf_name_CV, int inputstart );
void MakeLatex_RecoilCV_Error(std::string output_name, std::vector<SecondTrkVar> Recoil_vector, std::string pdf_name_CV, int inputstart );
void Kin(bool &cutsOn, bool &my_norm, bool &my_debug, const char *userDir, int &print_Error) {
TH1::AddDirectory(false);
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~       Starting Plotter: Non MUON Tracking Plots         ~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
const std::vector< ME_helium_Playlists> kMEPlayList_Vector = GetPlayListVector_MC();
const std::vector<ME_helium_Playlists> kPlayListVector_DATA = GetPlayListVector_DATA();
const std::vector<SecondTrkVar> kNonMuonTRK_vector = GetPlayListSecondTrkVector();
int N_Error_groups;
if(print_Error==2 || print_Error == 1) {N_Error_groups=0;}
else if (print_Error==0){N_Error_groups=7;}
Pot_MapList POT_MC,POT_DATA;
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



time_t now = time(0);
tm *ltm = localtime(&now);

 bool Stats_only = false;
 char timeset[2024];
 std::string SysError_printLabel = PrintLabel_Systematics(print_Error);
 auto Playlist_names =  MakePlaylistString(kMEPlayList_Vector);
 sprintf(timeset,"%i_%i_%i_%i", 1 + ltm->tm_mon,ltm->tm_mday, ltm->tm_hour, ltm->tm_min );


sprintf(text_title_pdf1, "PLOTS_Recoil_CV_Error_ME_fullstats_%s.pdf(",timeset );
can -> Print(text_title_pdf1);
sprintf(text_title_pdf2, "PLOTS_Recoil_CV_Error_ME_fullstats_%s.pdf",timeset );
sprintf(text_title_pdf2, "PLOTS_Recoil_CV_Error_ME_fullstats_%s.pdf",timeset );
sprintf(text_title_pdf3, "PLOTS_Recoil_CV_Error_ME_fullstats_%s.pdf)",timeset );
sprintf(text_title_pdf4, "PLOTS_Recoil_CV_Error_ME_fullstats_%s",timeset );


bool DoBinwidthNorm = true;
bool MakeXaxisLOG = false;
bool MakeYaxisLOG = false;
bool is_mc=true;
bool isNOT_mc=false;
std::string pdf_CV = string(text_title_pdf4);


sprintf(StacksInteraction_title_pdf1, "Plots_Recoil_InteractionStacks_fullstats_%s.pdf(",timeset );
can -> Print(StacksInteraction_title_pdf1);
sprintf(StacksInteraction_title_pdf2, "Plots_Recoil_InteractionStacks_fullstats_%s.pdf",timeset );
sprintf(StacksInteraction_title_pdf3, "Plots_Recoil_InteractionStacks_fullstats_%s.pdf)",timeset );
sprintf(StacksInteraction_title_pdf4, "Plots_Recoil_InteractionStacks_fullstats_%s",timeset );
std::string pdf_InteractionStacks = string(StacksInteraction_title_pdf4);

sprintf(StacksParticle_title_pdf1, "Plots_Recoil_ParticleStacks_fullstats_%s.pdf(",timeset );
can -> Print(StacksParticle_title_pdf1);
sprintf(StacksParticle_title_pdf2, "Plots_Recoil_ParticleStacks_fullstats_%s.pdf",timeset );
sprintf(StacksParticle_title_pdf3, "Plots_Recoil_ParticleStacks_fullstats_%s.pdf)",timeset );
sprintf(StacksParticle_title_pdf4, "Plots_Recoil_ParticleStacks_fullstats_%s",timeset );
std::string pdf_ParticleStacks = string(StacksParticle_title_pdf4);


sprintf(StacksMaterial_title_pdf1, "Plots_Recoil_MaterialStacks_fullstats_%s.pdf(",timeset );
can -> Print(StacksMaterial_title_pdf1);
sprintf(StacksMaterial_title_pdf2, "Plots_Recoil_MaterialStacks_fullstats_%s.pdf",timeset );
sprintf(StacksMaterial_title_pdf3, "Plots_Recoil_MaterialStacks_fullstats_%s.pdf)",timeset );
sprintf(StacksMaterial_title_pdf4, "Plots_Recoil_MaterialStacks_fullstats_%s",timeset );
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

std::vector<StackType> StackType_vector;

StackType_vector.push_back(kMaterial );
StackType_vector.push_back(kInteraction);
StackType_vector.push_back(kParticle);

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


for(auto Vertex_vertex: kNonMuonTRK_vector ){

  auto histname = GetsecondTrakHistName(Vertex_vertex);
  char histnameMC_char[histname.length()+1];
  strcpy( histnameMC_char,histname.c_str());

  auto histname_data = GetsecondTrakHistName_DATA_Name(Vertex_vertex);
  char histnameDATA_char[ histname_data.length()+1];
  strcpy( histnameDATA_char,histname_data.c_str());

  std::cout << " histname = "<< histname<<std::endl;
  std::cout << " histname_car = "<< histnameMC_char<<std::endl;
  std::cout << " histnameData = "<< histname_data<<std::endl;
  std::cout << " histname_car = "<< histnameDATA_char<<std::endl;

  auto title_his = GetsecondTrkTitleName(Vertex_vertex);
  char TITLE_char[title_his.length()+1];
  strcpy(TITLE_char,title_his.c_str());

  auto XAxis_name = GetsecondTrk_XAxisTitle(Vertex_vertex);
  char XAxis_name_char[XAxis_name.length()+1];
  strcpy(XAxis_name_char,XAxis_name.c_str());

    DrawFULLStat_CV_SystematicErr(FullTFile_Map_MC,  FullPOT_local_MC_ScaledMAP,
                                  EmptyTFile_Map_MC,  EmptyPOT_local_MC_ScaledMAP,
                                  FullTFile_Map_Data, FullPOT_local_Data_ScaledMAP,
                                  EmptyTFile_Map_Data, EmptyPOT_local_Data_ScaledMAP,
       histnameMC_char ,histnameDATA_char,
       GetsecondTrkUnitType(Vertex_vertex), pdf_CV, TITLE_char,
       XAxis_name_char, "NEvents",  DoBinwidthNorm, MakeXaxisLOG, MakeYaxisLOG );

    DrawFULLStatCOMBINED_CV_SystematicErr(FullTFile_Map_MC,  FullPOT_local_MC_MAP,
                                EmptyTFile_Map_MC,  EmptyPOT_local_MC_MAP,
                                FullTFile_Map_Data, FullPOT_local_Data_MAP,
                                EmptyTFile_Map_Data, EmptyPOT_local_Data_MAP,
     histnameMC_char ,histnameDATA_char,
     GetsecondTrkUnitType(Vertex_vertex), pdf_CV, TITLE_char,
     XAxis_name_char, "",  DoBinwidthNorm, MakeXaxisLOG);

/*
     for(auto Bluebird : StackType_vector){
        DrawSTACKfromHistFilio_FULLStats(FullTFile_Map_MC,  FullPOT_local_MC_ScaledMAP,
                                      EmptyTFile_Map_MC,  EmptyPOT_local_MC_ScaledMAP,
                                      FullTFile_Map_Data, FullPOT_local_Data_ScaledMAP,
                                      EmptyTFile_Map_Data, EmptyPOT_local_Data_ScaledMAP,
           histnameMC_char ,histnameDATA_char, TITLE_char,
          XAxis_name, PDF_stackMap[Bluebird], DoBinwidthNorm, GetsecondTrkUnitType(Vertex_vertex), Bluebird, my_debug );

          DrawSTACKfromHistFilio_FULLStatsCOMBINED(FullTFile_Map_MC,  FullPOT_local_MC_MAP,
                                        EmptyTFile_Map_MC,  EmptyPOT_local_MC_MAP,
                                        FullTFile_Map_Data, FullPOT_local_Data_MAP,
                                        EmptyTFile_Map_Data, EmptyPOT_local_Data_MAP,
             histnameMC_char ,histnameDATA_char, TITLE_char,
            XAxis_name, PDF_stackMap[Bluebird], DoBinwidthNorm, GetsecondTrkUnitType(Vertex_vertex), Bluebird, my_debug );

     }
*/

  }


  Draw2DFULLStat_CV_SystematicErr(FullTFile_Map_MC,  FullPOT_local_MC_ScaledMAP,
                                EmptyTFile_Map_MC,  EmptyPOT_local_MC_ScaledMAP,
                                FullTFile_Map_Data, FullPOT_local_Data_ScaledMAP,
                                EmptyTFile_Map_Data, EmptyPOT_local_Data_ScaledMAP,
     "h_2d_2ndtrkLength_Angle" ,"h2_Data_2ndtrkLength_Angle", text_title_pdf2, "leading Recoil: track Length Vs Angle",
     "[Deg]", " [cm]",  DoBinwidthNorm, MakeXaxisLOG, 15, 5, .03, .015);

  Draw2DFULLStatCOMBINED_CV_SystematicErr(FullTFile_Map_MC,  FullPOT_local_MC_MAP,
                              EmptyTFile_Map_MC,  EmptyPOT_local_MC_MAP,
                              FullTFile_Map_Data, FullPOT_local_Data_MAP,
                              EmptyTFile_Map_Data, EmptyPOT_local_Data_MAP,
   "h_2d_2ndtrkLength_Angle" ,"h2_Data_2ndtrkLength_Angle", text_title_pdf2, "leading Recoil: track Length Vs Angle",
   "[Deg]", "[cm]",  DoBinwidthNorm, MakeXaxisLOG, 30, 10, .03, .015);


   Draw2DFULLStat_CV_SystematicErr(FullTFile_Map_MC,  FullPOT_local_MC_ScaledMAP,
                                 EmptyTFile_Map_MC,  EmptyPOT_local_MC_ScaledMAP,
                                 FullTFile_Map_Data, FullPOT_local_Data_ScaledMAP,
                                 EmptyTFile_Map_Data, EmptyPOT_local_Data_ScaledMAP,
      "h_2d_2ndtrkLength_finerAngle" ,"h2_Data_2ndtrkLength_finerAngle", text_title_pdf2, "leading Recoil: track Length Vs Angle",
      "[Deg]", " [cm]",  DoBinwidthNorm, MakeXaxisLOG, 15, 5, .03, .015);

   Draw2DFULLStatCOMBINED_CV_SystematicErr(FullTFile_Map_MC,  FullPOT_local_MC_MAP,
                               EmptyTFile_Map_MC,  EmptyPOT_local_MC_MAP,
                               FullTFile_Map_Data, FullPOT_local_Data_MAP,
                               EmptyTFile_Map_Data, EmptyPOT_local_Data_MAP,
    "h_2d_2ndtrkLength_finerAngle" ,"h2_Data_2ndtrkLength_finerAngle", text_title_pdf2, "leading Recoil: track Length Vs Angle",
    "[Deg]", "[cm]",  DoBinwidthNorm, MakeXaxisLOG, 50, 10, .03, .015);



    Draw2DFULLStat_2dplotSingle(FullTFile_Map_MC,  FullPOT_local_MC_ScaledMAP,
                                  EmptyTFile_Map_MC,  EmptyPOT_local_MC_ScaledMAP,
                                  FullTFile_Map_Data, FullPOT_local_Data_ScaledMAP,
                                  EmptyTFile_Map_Data, EmptyPOT_local_Data_ScaledMAP,
       "h_2d_2ndtrkLength_finerAngle" ,"h2_Data_2ndtrkLength_finerAngle", text_title_pdf2, "leading Recoil: track Length Vs Angle",
       "TrkLength [cm]", "Angle (wtrb) [Deg]");

    Draw2DFULLStatCOMBINED_2dplotSingle(FullTFile_Map_MC,  FullPOT_local_MC_MAP,
                                EmptyTFile_Map_MC,  EmptyPOT_local_MC_MAP,
                                FullTFile_Map_Data, FullPOT_local_Data_MAP,
                                EmptyTFile_Map_Data, EmptyPOT_local_Data_MAP,
     "h_2d_2ndtrkLength_finerAngle" ,"h2_Data_2ndtrkLength_finerAngle", text_title_pdf2, "leading Recoil: track Length Vs Angle",
     "TrkLength [cm]", "Angle (wtrb) [Deg]");

///

   Draw2DFULLStat_CV_SystematicErr(FullTFile_Map_MC,  FullPOT_local_MC_ScaledMAP,
                                 EmptyTFile_Map_MC,  EmptyPOT_local_MC_ScaledMAP,
                                 FullTFile_Map_Data, FullPOT_local_Data_ScaledMAP,
                                 EmptyTFile_Map_Data, EmptyPOT_local_Data_ScaledMAP,
      "h_2d_2ndtrkLength_vertex_R" ,"h2_Data_secTrkLength_R", text_title_pdf2, "leading Recoil track Length Vs Vertex R",
      "R[mm] ","TrkL [cm]",  DoBinwidthNorm, MakeXaxisLOG, 10, 10, .02, .015);

   Draw2DFULLStatCOMBINED_CV_SystematicErr(FullTFile_Map_MC,  FullPOT_local_MC_MAP,
                               EmptyTFile_Map_MC,  EmptyPOT_local_MC_MAP,
                               FullTFile_Map_Data, FullPOT_local_Data_MAP,
                               EmptyTFile_Map_Data, EmptyPOT_local_Data_MAP,
    "h_2d_2ndtrkLength_vertex_R" ,"h2_Data_secTrkLength_R", text_title_pdf2, "leading Recoil track Length Vs Vertex R",
    "R[mm] ","TrkL [cm]",  DoBinwidthNorm, MakeXaxisLOG, 20, 20, .02, .015);


    Draw2DFULLStat_2dplotSingle(FullTFile_Map_MC,  FullPOT_local_MC_ScaledMAP,
                                  EmptyTFile_Map_MC,  EmptyPOT_local_MC_ScaledMAP,
                                  FullTFile_Map_Data, FullPOT_local_Data_ScaledMAP,
                                  EmptyTFile_Map_Data, EmptyPOT_local_Data_ScaledMAP,
       "h_2d_2ndtrkLength_vertex_R" ,"h2_Data_secTrkLength_R", text_title_pdf2, "leading Recoil track Length Vs Vertex R",
       "TrkLength[cm]", "Vertex R[mm]");

    Draw2DFULLStatCOMBINED_2dplotSingle(FullTFile_Map_MC,  FullPOT_local_MC_MAP,
                                EmptyTFile_Map_MC,  EmptyPOT_local_MC_MAP,
                                FullTFile_Map_Data, FullPOT_local_Data_MAP,
                                EmptyTFile_Map_Data, EmptyPOT_local_Data_MAP,
     "h_2d_2ndtrkLength_vertex_R" ,"h2_Data_secTrkLength_R", text_title_pdf2, "leading Recoil track Length Vs Vertex R",
    "TrkLength[cm]", "Vertex R[mm]");



    Draw2DFULLStat_CV_SystematicErr(FullTFile_Map_MC,  FullPOT_local_MC_ScaledMAP,
                                  EmptyTFile_Map_MC,  EmptyPOT_local_MC_ScaledMAP,
                                  FullTFile_Map_Data, FullPOT_local_Data_ScaledMAP,
                                  EmptyTFile_Map_Data, EmptyPOT_local_Data_ScaledMAP,
       "h_2d_2ndtrkLength_vertex_Z" ,"h2_Data_secTrkLength_Z", text_title_pdf2, "leading Recoil track Length Vs Vertex Z",
       "Z[mm]", "[cm]",   DoBinwidthNorm, MakeXaxisLOG, 10, 10, .015, .015);

    Draw2DFULLStatCOMBINED_CV_SystematicErr(FullTFile_Map_MC,  FullPOT_local_MC_MAP,
                                EmptyTFile_Map_MC,  EmptyPOT_local_MC_MAP,
                                FullTFile_Map_Data, FullPOT_local_Data_MAP,
                                EmptyTFile_Map_Data, EmptyPOT_local_Data_MAP,
     "h_2d_2ndtrkLength_vertex_Z" ,"h2_Data_secTrkLength_Z", text_title_pdf2, "leading Recoil track Length Vs Vertex Z",
     "Z[mm]", "[cm]",  DoBinwidthNorm, MakeXaxisLOG, 50, 50, .015, .015);


        Draw2DFULLStat_2dplotSingle(FullTFile_Map_MC,  FullPOT_local_MC_ScaledMAP,
                                       EmptyTFile_Map_MC,  EmptyPOT_local_MC_ScaledMAP,
                                       FullTFile_Map_Data, FullPOT_local_Data_ScaledMAP,
                                       EmptyTFile_Map_Data, EmptyPOT_local_Data_ScaledMAP,
            "h_2d_2ndtrkLength_vertex_Z" ,"h2_Data_secTrkLength_Z", text_title_pdf2, "leading Recoil track Length Vs Vertex Z",
            "TrkLength[cm]", "Vertex Z[mm]");

         Draw2DFULLStatCOMBINED_2dplotSingle(FullTFile_Map_MC,  FullPOT_local_MC_MAP,
                                     EmptyTFile_Map_MC,  EmptyPOT_local_MC_MAP,
                                     FullTFile_Map_Data, FullPOT_local_Data_MAP,
                                     EmptyTFile_Map_Data, EmptyPOT_local_Data_MAP,
          "h_2d_2ndtrkLength_vertex_Z" ,"h2_Data_secTrkLength_Z", text_title_pdf2, "leading Recoil track Length Vs Vertex Z",
          "TrkLength[cm]", "Vertex Z[mm]");


          Draw2DFULLStat_2dplotSingle(FullTFile_Map_MC,  FullPOT_local_MC_ScaledMAP,
                                         EmptyTFile_Map_MC,  EmptyPOT_local_MC_ScaledMAP,
                                         FullTFile_Map_Data, FullPOT_local_Data_ScaledMAP,
                                         EmptyTFile_Map_Data, EmptyPOT_local_Data_ScaledMAP,
              "h2_LastZnode_2ndTrklength" ,"h2_Data_LastZnode_2ndTrklength", text_title_pdf2, "leading Recoil track Length Vs Last Z Node",
             " TrkLength[cm]",  "Last Z Node [mm]");

           Draw2DFULLStatCOMBINED_2dplotSingle(FullTFile_Map_MC,  FullPOT_local_MC_MAP,
                                       EmptyTFile_Map_MC,  EmptyPOT_local_MC_MAP,
                                       FullTFile_Map_Data, FullPOT_local_Data_MAP,
                                       EmptyTFile_Map_Data, EmptyPOT_local_Data_MAP,
            "h2_LastZnode_2ndTrklength" ,"h2_Data_LastZnode_2ndTrklength", text_title_pdf2, "leading Recoil track Length Vs Last Z Node",
             "TrkLength[cm]",  "Last Z Node [mm]");

            Draw2DFULLStat_2dplotSingle(FullTFile_Map_MC,  FullPOT_local_MC_ScaledMAP,
                                           EmptyTFile_Map_MC,  EmptyPOT_local_MC_ScaledMAP,
                                           FullTFile_Map_Data, FullPOT_local_Data_ScaledMAP,
                                           EmptyTFile_Map_Data, EmptyPOT_local_Data_ScaledMAP,
                "h2_FirstZnode_2ndTrklength" ,"h2_Data_FirstZnode_2ndTrklength", text_title_pdf2, "leading Recoil track Length Vs First Z Node",
                "TrkLength[cm]",  "First Z Node [mm]");

             Draw2DFULLStatCOMBINED_2dplotSingle(FullTFile_Map_MC,  FullPOT_local_MC_MAP,
                                         EmptyTFile_Map_MC,  EmptyPOT_local_MC_MAP,
                                         FullTFile_Map_Data, FullPOT_local_Data_MAP,
                                         EmptyTFile_Map_Data, EmptyPOT_local_Data_MAP,
              "h2_FirstZnode_2ndTrklength" ,"h2_Data_FirstZnode_2ndTrklength", text_title_pdf2, "leading Recoil track Length Vs First Z Node",
              "TrkLength[cm]",  "First Z Node [mm]");


  std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;

  std::cout<< " Done with SecondTrkVar Plots  "<< std::endl;

  std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;

     std::cout << std::endl;
     std::cout << "Done WITH Stacks" << std::endl;

     can -> Print(text_title_pdf3);
     can -> Print(StacksInteraction_title_pdf3);
     can -> Print(StacksParticle_title_pdf3);
     can -> Print(StacksMaterial_title_pdf3);


     char latexName[1024];
     sprintf(latexName,"SecondTrkVar_CV_totalerror_Latex_%s", timeset);
     MakeLatex_RecoilCV_Error(latexName, kNonMuonTRK_vector, pdf_CV, 2 );
     //sprintf(latexName,"Recoil_stacks_Interaction_Latex_%s", timeset);
     //MakeLatex_RecoilStacks(latexName, kNonMuonTRK_vector, pdf_InteractionStacks, 2 );
     //sprintf(latexName,"Recoil_stacks_Particle_Latex_%s", timeset);
     //MakeLatex_RecoilStacks(latexName,    kNonMuonTRK_vector, pdf_ParticleStacks, 2 );
     //sprintf(latexName,"Recoil_stacks_Material_Latex_%s", timeset);
     //MakeLatex_RecoilStacks(latexName,    kNonMuonTRK_vector, pdf_MaterialStacks, 2 );


}




//End of MainFuntion
///////////////////////////////////

/////////////////////////////////////////////
//Main Function
/////////////////////////////////////////////

 int main() {

bool cutsOn=true;
std::cout << "Run over cutsOn?  (0 = false, 1 = true) " << std::endl;
//std::cin >> cutsOn;
std::cout << std::boolalpha << cutsOn << std::endl;

bool my_norm=true;
std::cout << "Which Normalization?  (0 = POT, 1 = relative equal areas) " << std::endl;
//std::cin >> my_norm;
std::cout << std::boolalpha << my_norm << std::endl;

bool my_debug=true;
std::cout << "Run in Debug Mode? (0 = NO, 1 = YES) " << std::endl;
//std::cin >> my_debug;
std::cout << std::boolalpha << my_debug << std::endl;

std::string input = "cnguyen";
std::cout << "What is the name of the user? " << std::endl;
//std::cin >> input;
std::cout << input << std::endl;

int my_Print_Systmatics;
std::cout << "Print Error Systmatics?  [ 0 = Total and Groups Systemtics Errors ,  1 = Total Systematic Errors , 2 = none ]" << std::endl;
//std::cin >> my_Print_Systmatics;
my_Print_Systmatics= 2;
std::cout << "Picked : " << my_Print_Systmatics << std::endl;

const char *inputFileLoc = input.c_str();

Kin(cutsOn, my_norm, my_debug, inputFileLoc,my_Print_Systmatics);

return 0;

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
//////////////////////////////////////////////////////////////////////////
//GET Vertex Varibles
//////////////////////////////////////////////////////////////////////////


std::vector<SecondTrkVar> GetPlayListSecondTrkVector() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<SecondTrkVar> Playlist;

  Playlist.push_back(ksecE);
  Playlist.push_back(ksec_tracklength_minerva);
  Playlist.push_back(kThetamid);
  Playlist.push_back(kDOCA);
  //Playlist.push_back(kOpenAngle);
  //Playlist.push_back(kPathway);
  //
  //Playlist.push_back(kFirstsecTrk_Xnode);
  //Playlist.push_back(kFirstsecTrk_Ynode);
  //Playlist.push_back(kFirstsecTrk_Znode);
  //Playlist.push_back(kLastsecTrk_Xnode);
  //Playlist.push_back(kLastsecTrk_Ynode);
  //Playlist.push_back(kLastsecTrk_Znode);

  return Playlist;
//#endif
}

void MakeLatexForNonMuonFiguresFORStacks(std::string output_name ,std::vector<SecondTrkVar> NoN_muon_vector ,  std::string pdf_name){
  double scale= .23;
  std::ofstream myfile;
  string fileName = output_name + ".txt";
  myfile.open(fileName);
  std::cout<<"Name of Output File "<< fileName<<std::endl;
  LatexFormat NonMuon_latex_Latex(scale);

  int pageCount = 2;
  std::cout << " Name of input PDF = "<< pdf_name << std::endl;

  for(auto cat:NoN_muon_vector){

    auto input_vectors = GetSecondTrkVarVector(cat);
    std::string Var_name = GetsecondTrkTitleName(cat);
    std::string Units_name = GetsecondTrkUnitType(cat);
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%%  Frame Stack For  "<< Var_name <<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<NonMuon_latex_Latex.GetBeginFrame(Var_name)<< "\n";
    myfile<<NonMuon_latex_Latex.GetBeginTabular()<< "\n";
    myfile<<NonMuon_latex_Latex.GetInclude_figure(pageCount,pdf_name)<< "\n";
    myfile<<"& \n";
    myfile<<NonMuon_latex_Latex.GetInclude_figure(pageCount+1,pdf_name)<< "\n";
    myfile<<"& \n";
    myfile<<NonMuon_latex_Latex.GetInclude_figure(pageCount+2,pdf_name)<< "\n";
    myfile<<NonMuon_latex_Latex.GetEndTabular()<< "\n";
    if(input_vectors.size() < 25)
    {
      myfile<<NonMuon_latex_Latex.BinningLatexString(input_vectors, Var_name , Units_name )<< "\n";
    }
    myfile<<NonMuon_latex_Latex.GetEndFrame();
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% END FRAME Stack "<< Var_name<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";

    pageCount= pageCount + 3;
  }


  myfile.close();
}//end of Function


void MakeLatexForNonMuonFiguresCVandALLErrors(std::string output_name ,std::vector<SecondTrkVar> NoN_muon_vector,
   std::string PDF_cv_name, int NError_Groups){
  double scale= .24;
  std::ofstream myfile;

  const int  Column_Spacing = NError_Groups + 2;

  string fileName = output_name + ".txt";
  myfile.open(fileName);
  std::cout<<"Name of Output File "<< fileName<<std::endl;
  LatexFormat NonMuon_latex_Latex(scale);

  int pageCount = 2;


  for(auto cat:NoN_muon_vector){

    auto input_vectors = GetSecondTrkVarVector(cat);
    std::string Var_name = GetsecondTrkTitleName(cat);
    std::string Units_name = GetsecondTrkUnitType(cat);

    myfile<<"\n";
    myfile<<NonMuon_latex_Latex.GetSubSection(Var_name);
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%%  Frame CV and Error grounps For  "<< Var_name <<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<NonMuon_latex_Latex.GetBeginFrame(Var_name)<< "\n";
    myfile<<NonMuon_latex_Latex.GetBeginTabular()<< "\n";
    myfile<<NonMuon_latex_Latex.GetInclude_figure(pageCount,PDF_cv_name)<< "\n";
    myfile<<"& \n";
    myfile<<NonMuon_latex_Latex.GetInclude_figure(pageCount + Column_Spacing,PDF_cv_name)<< "\n";
    myfile<<"& \n";
    myfile<<NonMuon_latex_Latex.GetInclude_figure(pageCount + Column_Spacing+ Column_Spacing,PDF_cv_name)<< "\n";
    myfile<<NonMuon_latex_Latex.GetEndTabular()<< "\n";
    if(input_vectors.size() < 25)
    {
      myfile<<NonMuon_latex_Latex.BinningLatexString(input_vectors, Var_name , Units_name )<< "\n";
    }




    myfile<<NonMuon_latex_Latex.GetEndFrame();
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% END FRAME Frame CV and Error groups "<< Var_name<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";

    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%%  Full Error group  "<< Var_name <<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<NonMuon_latex_Latex.GetBeginFrame(Var_name)<< "\n";
    myfile<<NonMuon_latex_Latex.GetBeginTabular()<< "\n";
    myfile<<NonMuon_latex_Latex.GetInclude_figure(pageCount + 1, PDF_cv_name)<< "\n";
    myfile<<"& \n";
    myfile<<NonMuon_latex_Latex.GetInclude_figure(pageCount + Column_Spacing + 1, PDF_cv_name )<< "\n";
    myfile<<"& \n";
    myfile<<NonMuon_latex_Latex.GetInclude_figure(pageCount +  Column_Spacing +  Column_Spacing + 1, PDF_cv_name )<< "\n";
    myfile<<NonMuon_latex_Latex.GetEndTabular()<< "\n";
    myfile<<NonMuon_latex_Latex.GetEndFrame();
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
      myfile<<NonMuon_latex_Latex.GetBeginFrame(Var_name)<< "\n";
      myfile<<NonMuon_latex_Latex.GetBeginTabular()<< "\n";
      myfile<<NonMuon_latex_Latex.GetInclude_figure(pageCount + i + 2,PDF_cv_name)<< "\n";
      myfile<<"& \n";
      myfile<<NonMuon_latex_Latex.GetInclude_figure(pageCount + Column_Spacing + i + 2 ,PDF_cv_name)<< "\n";
      myfile<<"& \n";
      myfile<<NonMuon_latex_Latex.GetInclude_figure(pageCount +  Column_Spacing + Column_Spacing + i + 2,PDF_cv_name)<< "\n";
      myfile<<NonMuon_latex_Latex.GetEndTabular()<< "\n";
      myfile<<NonMuon_latex_Latex.GetEndFrame();
      myfile<<"\n";
      myfile<<"%%%%%%%%%%%%%%%%% \n";
      myfile<<"%%% END FRAME Error groups "<< Var_name<<"\n";
      myfile<<"%%%%%%%%%%%%%%%%% \n";

    }
  }




    pageCount= pageCount +  Column_Spacing + Column_Spacing + Column_Spacing ;
  }


  myfile.close();

}//end of



void MakeLatexForNonMuonFiguresCVandGroupErrors_andALLSTACKS(int Systmatic_ErrorType ,std::string output_name ,
std::vector<SecondTrkVar> NoN_muon_vector,  std::string pdf_name_CV, std::string pdf_stack_Material, std::string pdf_stack_Interaction,
  std::string pdf_stack_Particle,int NError_Groups)
  {
  double scale= .25;
  std::ofstream myfile;
  int error_space;
  if(Systmatic_ErrorType==2){error_space=1;}
  else if(Systmatic_ErrorType==1 || Systmatic_ErrorType==0){error_space=2;}

  const int  Column_Spacing = NError_Groups + error_space;

  string fileName = output_name + ".txt";
  myfile.open(fileName);
  std::cout<<"Name of Output File "<< fileName<<std::endl;
  LatexFormat NonMuon_latex_Latex(scale);

  int pageCount = 2;
  int StackpageCount=2;

  myfile<<"\n";
  myfile<<NonMuon_latex_Latex.GetSubSection("Secondary Tk Variables");
  myfile<<"\n";
  for(auto cat:NoN_muon_vector){

    auto input_vectors = GetSecondTrkVarVector(cat);
    std::string Var_name = GetsecondTrkTitleName(cat);
    std::string Units_name = GetsecondTrkUnitType(cat);


    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% Frame CV "<< Var_name <<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<NonMuon_latex_Latex.GetBeginFrame(Var_name)<< "\n";
    myfile<<NonMuon_latex_Latex.GetBeginTabular()<< "\n";
    myfile<<NonMuon_latex_Latex.GetInclude_figure(pageCount, pdf_name_CV)<< "\n";
    myfile<<"& \n";
    myfile<<NonMuon_latex_Latex.GetInclude_figure(pageCount + Column_Spacing, pdf_name_CV )<< "\n";
    myfile<<"& \n";
    myfile<<NonMuon_latex_Latex.GetInclude_figure(pageCount + Column_Spacing + Column_Spacing, pdf_name_CV)<< "\n";
    myfile<<NonMuon_latex_Latex.GetEndTabular()<< "\n";
    if(input_vectors.size() < 25)
    {
      myfile<<NonMuon_latex_Latex.BinningLatexString(input_vectors, Var_name , Units_name )<< "\n";
    }
    myfile<<NonMuon_latex_Latex.GetEndFrame();
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% END FRAME Frame CV and Error groups "<< Var_name<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";

    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%%  Material Stacks  "<< Var_name <<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<NonMuon_latex_Latex.GetBeginFrame(Var_name+ " Material Stacks ")<< "\n";
    myfile<<NonMuon_latex_Latex.GetBeginTabular()<< "\n";
    myfile<<NonMuon_latex_Latex.GetInclude_figure(StackpageCount ,pdf_stack_Material)<< "\n";
    myfile<<"& \n";
    myfile<<NonMuon_latex_Latex.GetInclude_figure(StackpageCount + 1, pdf_stack_Material )<< "\n";
    myfile<<"& \n";
    myfile<<NonMuon_latex_Latex.GetInclude_figure(StackpageCount + 2, pdf_stack_Material )<< "\n";
    myfile<<NonMuon_latex_Latex.GetEndTabular()<< "\n";
    myfile<<NonMuon_latex_Latex.GetEndFrame();
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% END FRAME Frame CV and Error groups "<< Var_name<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";

    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%%  Interaction  Stacks  "<< Var_name <<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<NonMuon_latex_Latex.GetBeginFrame(Var_name+ " Interaction Stacks ")<< "\n";
    myfile<<NonMuon_latex_Latex.GetBeginTabular()<< "\n";
    myfile<<NonMuon_latex_Latex.GetInclude_figure(StackpageCount ,pdf_stack_Interaction)<< "\n";
    myfile<<"& \n";
    myfile<<NonMuon_latex_Latex.GetInclude_figure(StackpageCount + 1, pdf_stack_Interaction )<< "\n";
    myfile<<"& \n";
    myfile<<NonMuon_latex_Latex.GetInclude_figure(StackpageCount + 2, pdf_stack_Interaction )<< "\n";
    myfile<<NonMuon_latex_Latex.GetEndTabular()<< "\n";
    myfile<<NonMuon_latex_Latex.GetEndFrame();
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% END FRAME Interaction "<< Var_name<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";


    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%%  Particle  Stacks  "<< Var_name <<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<NonMuon_latex_Latex.GetBeginFrame(Var_name+ " Particle Stacks ")<< "\n";
    myfile<<NonMuon_latex_Latex.GetBeginTabular()<< "\n";
    myfile<<NonMuon_latex_Latex.GetInclude_figure(StackpageCount ,pdf_stack_Particle)<< "\n";
    myfile<<"& \n";
    myfile<<NonMuon_latex_Latex.GetInclude_figure(StackpageCount +  1, pdf_stack_Particle )<< "\n";
    myfile<<"& \n";
    myfile<<NonMuon_latex_Latex.GetInclude_figure(StackpageCount +  2, pdf_stack_Particle )<< "\n";
    myfile<<NonMuon_latex_Latex.GetEndTabular()<< "\n";
    myfile<<NonMuon_latex_Latex.GetEndFrame();
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% END FRAME Particle "<< Var_name<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";

    pageCount= pageCount +  Column_Spacing +  Column_Spacing+1;
    StackpageCount  = StackpageCount  + 3;
  }


  myfile.close();

}//end of


void MakeLatex_RecoilCV_Error(std::string output_name, std::vector<SecondTrkVar> Recoil_vector, std::string pdf_name_CV, int inputstart ){
  std::ofstream myfile;
  std::string fileName = output_name + ".txt";
  myfile.open(fileName,std::ios::trunc);
  std::cout<<"Name of Output File "<< fileName<<std::endl;
  int index = inputstart;
  LatexFormat Recoil_latex_Latex(.2);
  int Column_Spacing = 11;


  for(auto cat: Recoil_vector){

    auto input_vectors = GetSecondTrkVarVector(cat);
    std::string Var_name = GetsecondTrkTitleName(cat);
    std::string Units_name = GetsecondTrkUnitType(cat);
    auto Xaxis_title = GetsecondTrk_XAxisTitle(cat);

    myfile<<Recoil_latex_Latex.GetSubSection(Var_name);
    myfile<<"\n";
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% Frame  ALL FULL Playlist Breakdown"<< Var_name <<" \n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<Recoil_latex_Latex.GetBeginFrame(Xaxis_title)<< "\n";
    myfile<<Recoil_latex_Latex.GetBeginTabular("ccc")<< "\n";
    myfile<<Recoil_latex_Latex.GetInclude_figure(index, pdf_name_CV)<< "\n";
    myfile<<"& \n";
    myfile<<Recoil_latex_Latex.GetInclude_figure(index + Column_Spacing, pdf_name_CV )<< "\n";
    myfile<<"& \n";
    myfile<<Recoil_latex_Latex.GetInclude_figure(index + Column_Spacing * 2, pdf_name_CV)<< "\n";
    myfile<<"\\\\ \n";
    myfile<<Recoil_latex_Latex.GetInclude_figure(index + Column_Spacing * 3, pdf_name_CV )<< "\n";
    myfile<<"& \n";
    myfile<<Recoil_latex_Latex.GetInclude_figure(index + Column_Spacing * 4, pdf_name_CV)<< "\n";
    myfile<<Recoil_latex_Latex.GetEndTabular()<< "\n";
    if(input_vectors.size() < 25)
    {
      myfile<<Recoil_latex_Latex.BinningLatexString(input_vectors, Var_name , Units_name )<< "\n";
    }
    myfile<<Recoil_latex_Latex.GetEndFrame();

    myfile<<"\n";
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% Frame  ALL  FULL Playlist Error Breakdown"<< Var_name <<" \n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<Recoil_latex_Latex.GetBeginFrame(Xaxis_title)<< "\n";
    myfile<<Recoil_latex_Latex.GetBeginTabular("ccc")<< "\n";
    myfile<<Recoil_latex_Latex.GetInclude_figure(index + 1, pdf_name_CV)<< "\n";
    myfile<<"& \n";
    myfile<<Recoil_latex_Latex.GetInclude_figure(index + Column_Spacing + 1, pdf_name_CV )<< "\n";
    myfile<<"& \n";
    myfile<<Recoil_latex_Latex.GetInclude_figure(index + Column_Spacing * 2 + 1, pdf_name_CV)<< "\n";
    myfile<<"\\\\ \n";
    myfile<<Recoil_latex_Latex.GetInclude_figure(index + Column_Spacing * 3 + 1, pdf_name_CV )<< "\n";
    myfile<<"& \n";
    myfile<<Recoil_latex_Latex.GetInclude_figure(index + Column_Spacing * 4 + 1, pdf_name_CV)<< "\n";
    myfile<<Recoil_latex_Latex.GetEndTabular()<< "\n";
    if(input_vectors.size() < 25)
    {
      myfile<<Recoil_latex_Latex.BinningLatexString(input_vectors, Var_name , Units_name )<< "\n";
    }
    myfile<<Recoil_latex_Latex.GetEndFrame();

    //////////////////////////////////////////////////
    //Empty
    /////////////////////////////////////////////////
    myfile<<"\n";
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% Frame ALL Empty Playlist Breakdown"<< Var_name <<" \n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<Recoil_latex_Latex.GetBeginFrame(Xaxis_title)<< "\n";
    myfile<<Recoil_latex_Latex.GetBeginTabular("ccc")<< "\n";
    myfile<<Recoil_latex_Latex.GetInclude_figure(index + Column_Spacing * 5, pdf_name_CV)<< "\n";
    myfile<<"& \n";
    myfile<<Recoil_latex_Latex.GetInclude_figure(index + Column_Spacing * 6, pdf_name_CV )<< "\n";
    myfile<<"& \n";
    myfile<<Recoil_latex_Latex.GetInclude_figure(index + Column_Spacing * 7, pdf_name_CV)<< "\n";
    myfile<<"\\\\ \n";
    myfile<<Recoil_latex_Latex.GetInclude_figure(index + Column_Spacing * 8, pdf_name_CV )<< "\n";
    myfile<<"& \n";
    myfile<<Recoil_latex_Latex.GetInclude_figure(index + Column_Spacing * 9, pdf_name_CV)<< "\n";
    myfile<<Recoil_latex_Latex.GetEndTabular()<< "\n";
    if(input_vectors.size() < 25)
    {
      myfile<<Recoil_latex_Latex.BinningLatexString(input_vectors, Var_name , Units_name )<< "\n";
    }
    myfile<<Recoil_latex_Latex.GetEndFrame();

    myfile<<"\n";
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% Frame  ALL  Empty Playlist Error Breakdown"<< Var_name <<" \n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<Recoil_latex_Latex.GetBeginFrame(Xaxis_title)<< "\n";
    myfile<<Recoil_latex_Latex.GetBeginTabular("ccc")<< "\n";
    myfile<<Recoil_latex_Latex.GetInclude_figure(index + Column_Spacing * 5 + 1, pdf_name_CV)<< "\n";
    myfile<<"& \n";
    myfile<<Recoil_latex_Latex.GetInclude_figure(index + Column_Spacing * 6 + 1, pdf_name_CV )<< "\n";
    myfile<<"& \n";
    myfile<<Recoil_latex_Latex.GetInclude_figure(index + Column_Spacing * 7 + 1, pdf_name_CV)<< "\n";
    myfile<<"\\\\ \n";
    myfile<<Recoil_latex_Latex.GetInclude_figure(index + Column_Spacing * 8 + 1, pdf_name_CV )<< "\n";
    myfile<<"& \n";
    myfile<<Recoil_latex_Latex.GetInclude_figure(index + Column_Spacing * 9 + 1, pdf_name_CV)<< "\n";
    myfile<<Recoil_latex_Latex.GetEndTabular()<< "\n";
    if(input_vectors.size() < 25)
    {
      myfile<<Recoil_latex_Latex.BinningLatexString(input_vectors, Var_name , Units_name )<< "\n";
    }
    myfile<<Recoil_latex_Latex.GetEndFrame();


    //////////////////////////////////////////////////
    //Full - Empty
    /////////////////////////////////////////////////


    myfile<<"\n";
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% Frame Full - Empty  Total"<< Var_name <<" \n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<Recoil_latex_Latex.GetBeginFrame(Xaxis_title)<< "\n";
    myfile<<Recoil_latex_Latex.GetBeginTabular("ccc")<< "\n";
    myfile<<Recoil_latex_Latex.GetInclude_figure(index + 110, pdf_name_CV, .24)<< "\n";
    myfile<<"& \n";
    myfile<<Recoil_latex_Latex.GetInclude_figure(index + Column_Spacing + 110, pdf_name_CV, .24 )<< "\n";
    myfile<<"& \n";
    myfile<<Recoil_latex_Latex.GetInclude_figure(index + Column_Spacing * 2 + 110, pdf_name_CV, .24)<< "\n";
    myfile<<Recoil_latex_Latex.GetEndTabular()<< "\n";
    if(input_vectors.size() < 25)
    {
      myfile<<Recoil_latex_Latex.BinningLatexString(input_vectors, Var_name , Units_name )<< "\n";
    }

      myfile<<Recoil_latex_Latex.GetEndFrame();


      myfile<<"\n";
      myfile<<"\n";
      myfile<<"%%%%%%%%%%%%%%%%% \n";
      myfile<<"%%% Frame  Total Error"<< Var_name <<" \n";
      myfile<<"%%%%%%%%%%%%%%%%% \n";
      myfile<<Recoil_latex_Latex.GetBeginFrame(Xaxis_title)<< "\n";
      myfile<<Recoil_latex_Latex.GetBeginTabular("ccc")<< "\n";
      myfile<<Recoil_latex_Latex.GetInclude_figure(index + 110 + 1, pdf_name_CV, .24)<< "\n";
      myfile<<"& \n";
      myfile<<Recoil_latex_Latex.GetInclude_figure(index + Column_Spacing + 110 + 1 , pdf_name_CV, .24 )<< "\n";
      myfile<<"& \n";
      myfile<<Recoil_latex_Latex.GetInclude_figure(index + Column_Spacing * 2 + 110 + 1, pdf_name_CV, .24)<< "\n";
      myfile<<Recoil_latex_Latex.GetEndTabular()<< "\n";
      if(input_vectors.size() < 25)
      {
        myfile<<Recoil_latex_Latex.BinningLatexString(input_vectors, Var_name , Units_name )<< "\n";
      }

        myfile<<Recoil_latex_Latex.GetEndFrame();

        index = index + 143;
      }
      myfile.close();

    }//end of function

    void MakeLatex_RecoilStacks(std::string output_name, std::vector<SecondTrkVar> Recoil_vector, std::string pdf_name_CV, int inputstart ){
      std::ofstream myfile;
      std::string fileName = output_name + ".txt";
      myfile.open(fileName,std::ios::trunc);
      std::cout<<"Name of Output File "<< fileName<<std::endl;
      int index = inputstart;
      LatexFormat Recoil_latex_Latex(.2);
      int Column_Spacing =1;

      for(auto cat: Recoil_vector){

        auto input_vectors = GetSecondTrkVarVector(cat);
        std::string Var_name = GetsecondTrkTitleName(cat);
        std::string Units_name = GetsecondTrkUnitType(cat);
        auto Xaxis_title = GetsecondTrk_XAxisTitle(cat);

        myfile<<Recoil_latex_Latex.GetSubSection(Var_name);
        myfile<<"\n";
        myfile<<"\n";
        myfile<<"%%%%%%%%%%%%%%%%% \n";
        myfile<<"%%% Frame  ALL FULL Playlist Breakdown"<< Var_name <<" \n";
        myfile<<"%%%%%%%%%%%%%%%%% \n";
        myfile<<Recoil_latex_Latex.GetBeginFrame(Xaxis_title)<< "\n";
        myfile<<Recoil_latex_Latex.GetBeginTabular("ccc")<< "\n";
        myfile<<Recoil_latex_Latex.GetInclude_figure(index, pdf_name_CV)<< "\n";
        myfile<<"& \n";
        myfile<<Recoil_latex_Latex.GetInclude_figure(index + Column_Spacing, pdf_name_CV )<< "\n";
        myfile<<"& \n";
        myfile<<Recoil_latex_Latex.GetInclude_figure(index + Column_Spacing * 2, pdf_name_CV)<< "\n";
        myfile<<"\\\\ \n";
        myfile<<Recoil_latex_Latex.GetInclude_figure(index + Column_Spacing * 3, pdf_name_CV )<< "\n";
        myfile<<"& \n";
        myfile<<Recoil_latex_Latex.GetInclude_figure(index + Column_Spacing * 4, pdf_name_CV)<< "\n";
        myfile<<Recoil_latex_Latex.GetEndTabular()<< "\n";
        if(input_vectors.size() < 25)
        {

          myfile<<Recoil_latex_Latex.BinningLatexString(input_vectors, Var_name , Units_name )<< "\n";
          }
          myfile<<Recoil_latex_Latex.GetEndFrame();

          myfile<<"\n";
          myfile<<"\n";
          myfile<<"%%%%%%%%%%%%%%%%% \n";
          myfile<<"%%% Frame ALL FULL Playlist Breakdown"<< Var_name <<" \n";
          myfile<<"%%%%%%%%%%%%%%%%% \n";
          myfile<<Recoil_latex_Latex.GetBeginFrame(Xaxis_title)<< "\n";
          myfile<<Recoil_latex_Latex.GetBeginTabular("ccc")<< "\n";
          myfile<<Recoil_latex_Latex.GetInclude_figure(index+ Column_Spacing * 5, pdf_name_CV)<< "\n";
          myfile<<"& \n";
          myfile<<Recoil_latex_Latex.GetInclude_figure(index + Column_Spacing * 6, pdf_name_CV )<< "\n";
          myfile<<"& \n";
          myfile<<Recoil_latex_Latex.GetInclude_figure(index + Column_Spacing * 7, pdf_name_CV)<< "\n";
          myfile<<"\\\\ \n";
          myfile<<Recoil_latex_Latex.GetInclude_figure(index + Column_Spacing * 8, pdf_name_CV )<< "\n";
          myfile<<"& \n";
          myfile<<Recoil_latex_Latex.GetInclude_figure(index + Column_Spacing * 9, pdf_name_CV)<< "\n";
          myfile<<Recoil_latex_Latex.GetEndTabular()<< "\n";
          if(input_vectors.size() < 25)
          {

            myfile<<Recoil_latex_Latex.BinningLatexString(input_vectors, Var_name , Units_name )<< "\n";
            }
            myfile<<Recoil_latex_Latex.GetEndFrame();


            myfile<<"\n";
            myfile<<"\n";
            myfile<<"%%%%%%%%%%%%%%%%% \n";
            myfile<<"%%% Frame  Total Error"<< Var_name <<" \n";
            myfile<<"%%%%%%%%%%%%%%%%% \n";
            myfile<<Recoil_latex_Latex.GetBeginFrame(Xaxis_title)<< "\n";
            myfile<<Recoil_latex_Latex.GetBeginTabular("ccc")<< "\n";
            myfile<<Recoil_latex_Latex.GetInclude_figure(index + Column_Spacing * 10, pdf_name_CV, .24)<< "\n";
            myfile<<"& \n";
            myfile<<Recoil_latex_Latex.GetInclude_figure(index + Column_Spacing * 11, pdf_name_CV, .24 )<< "\n";
            myfile<<"& \n";
            myfile<<Recoil_latex_Latex.GetInclude_figure(index + Column_Spacing * 12, pdf_name_CV, .24)<< "\n";
            myfile<<Recoil_latex_Latex.GetEndTabular()<< "\n";
            if(input_vectors.size() < 25)
            {
              myfile<<Recoil_latex_Latex.BinningLatexString(input_vectors, Var_name , Units_name )<< "\n";
            }

              myfile<<Recoil_latex_Latex.GetEndFrame();

              index= index + 13;

      }

      myfile.close();


    }//end of function
