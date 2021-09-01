#include "Smearing_Study_FullStats.h"


std::vector<ME_helium_Playlists> GetPlayListVector_MC();
std::vector<ME_helium_Playlists> GetPlayListVector_DATA();
std::vector<MuonVar> GetMUONVaribles_Total();
std::vector<MuonVar> GetMUONVaribles_Stacks();
void MakeLatexForMuonFiguresCVandGroupErrors_andALLSTACKS(int Systmatic_ErrorType ,std::string output_name ,
  std::vector<MuonVar> muon_vector ,  std::string pdf_name_CV, std::string pdf_stack_Material, std::string pdf_stack_Interaction,
   std::string pdf_stack_Particle,int NError_Groups);
std::vector<SecondTrkVar>Get2ndTrkVaribles();
void MakeLatexForMuonFiguresCVandALLErrors(std::string output_name, std::vector<MuonVar> muon_vector,  std::string PDF_cv_name, int NError_Groups);
void MakeLatexForMuonFiguresFORStacks(std::string output_name ,std::vector<MuonVar> muon_vector ,  std::string pdf_name);
void Appendtotxt_SmearingPlots(std::string output_name ,  std::string pdf_name_CV, int First_page, char *Var_name ,char *Units_name);
void Kin(bool &cutsOn, bool &my_norm, bool &my_debug, const char *userDir, bool &BinNorm , int &Print_Systematics, int &m_CVorStacks ) {
TH1::AddDirectory(false);
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~       Starting Plotter: FOR Plots for Smearing Study        ~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;


const std::vector<ME_helium_Playlists> kMEPlayList_Vector = GetPlayListVector_MC();
const std::vector<ME_helium_Playlists> kPlayListVector_DATA = GetPlayListVector_DATA();
const std::vector<MuonVar> kMuonVaribles_vector_STACKS = GetMUONVaribles_Stacks();
const std::vector<MuonVar> kMuonVaribles_vector_TOTAL = GetMUONVaribles_Total();
const std::vector<SecondTrkVar> k2ndTrkVaribles_vector = Get2ndTrkVaribles();
int N_Error_groups;
if(Print_Systematics==2 || Print_Systematics == 1) {N_Error_groups=0;}
else if (Print_Systematics==0){N_Error_groups=7;}


Pot_MapList POT_MC, POT_DATA;

Pot_MapStatusList POT_MC_Status, POT_DATA_Status;

TCanvas *can = new TCanvas("can");
MnvPlotter *mnv_plot = new MnvPlotter();
 char text_title_pdf1[2024];
 char text_title_pdf2[2024];
 char text_title_pdf3[2024];
 char text_title_pdf4[2024];
 char Latex_name[2024];
time_t now = time(0);
tm *ltm = localtime(&now);
 char timeset[2024];
 char timeset_nonstacks[2024];
 std::string SysError_printLabel = PrintLabel_Systematics(Print_Systematics);
 //auto Playlist_names =  MakePlaylistString(kPlayListVector_MC);
 sprintf(timeset_nonstacks,"%i_%i_%i_%i_%s", 1 + ltm->tm_mon,ltm->tm_mday, ltm->tm_hour,ltm->tm_min, SysError_printLabel.c_str());
 sprintf(timeset, "%i_%i_%i_%i", 1 + ltm->tm_mon,ltm->tm_mday, ltm->tm_hour,ltm->tm_min);

bool is_mc=true;
bool is_Data=false;
bool isNOT_TRUTH=false;
bool is_TRUTH=true;

std::string pdf_CV = string(text_title_pdf4);

ME_playlist_RootPathMAP MAP_RootPath_Empty_MC;
ME_playlist_RootPathMAP MAP_RootPath_Full_MC;

ME_playlist_RootPathMAP MAP_RootPath_Empty_DATA;
ME_playlist_RootPathMAP MAP_RootPath_Full_DATA;


 bool Stats_only = false;
 std::string Smearing_rootFilePath = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/SMEARING_STUDY_minervame1F_MC_All_SysErrorsOn4U.root";
 std::string Smearing_rootFilePath_G = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/SMEARING_STUDY_minervame1G_MC_All_SysErrorsOn4U.root";

 std::string Smearing_rootFilePath_DATA_F = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1F_Data_SmearingStudy.root";
 std::string Smearing_rootFilePath_DATA_G = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1G_Data_SmearingStudy.root";


 /////////////////
 /// MC
 /////////////////
 // Empty Playlist
 /////////////////
 auto PlaylistME_1G_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/SMEARING_STUDY_minervame1G_MC_All_SysErrorsOn4U.root";
 auto PlaylistME_1A_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/SMEARING_STUDY_minervame1A_MC_All_SysErrorsOn4U.root";
 auto PlaylistME_1L_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/SMEARING_STUDY_minervame1L_MC_All_SysErrorsOn4U.root";
 auto PlaylistME_1M_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/SMEARING_STUDY_minervame1M_MC_All_SysErrorsOn4U.root";
 auto PlaylistME_1N_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/SMEARING_STUDY_minervame1N_MC_All_SysErrorsOn4U.root";
 MAP_RootPath_Empty_MC.insert(std::make_pair(kMEPlayList_Vector.at(0), PlaylistME_1G_MC_path));
 MAP_RootPath_Empty_MC.insert(std::make_pair(kMEPlayList_Vector.at(1), PlaylistME_1A_MC_path));
 MAP_RootPath_Empty_MC.insert(std::make_pair(kMEPlayList_Vector.at(2), PlaylistME_1L_MC_path));
 MAP_RootPath_Empty_MC.insert(std::make_pair(kMEPlayList_Vector.at(3), PlaylistME_1M_MC_path));
 MAP_RootPath_Empty_MC.insert(std::make_pair(kMEPlayList_Vector.at(4), PlaylistME_1N_MC_path));
 ////////
 //Full//
 ////////
 auto PlaylistME_1P_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/SMEARING_STUDY_minervame1P_MC_All_SysErrorsOn4U.root";
 auto PlaylistME_1C_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/SMEARING_STUDY_minervame1C_MC_All_SysErrorsOn4U.root";
 auto PlaylistME_1D_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/SMEARING_STUDY_minervame1D_MC_All_SysErrorsOn4U.root";
 auto PlaylistME_1F_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/SMEARING_STUDY_minervame1F_MC_All_SysErrorsOn4U.root";
 auto PlaylistME_1E_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/SMEARING_STUDY_minervame1E_MC_All_SysErrorsOn4U.root";
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
 auto PlaylistME_1G_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1G_Data_SmearingStudy.root";
 auto PlaylistME_1A_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1A_Data_SmearingStudy.root";
 auto PlaylistME_1L_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1L_Data_SmearingStudy.root";
 auto PlaylistME_1M_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1M_Data_SmearingStudy.root";
 auto PlaylistME_1N_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1N_Data_SmearingStudy.root";
 //////////////////
 MAP_RootPath_Empty_DATA.insert(std::make_pair(kMEPlayList_Vector.at(0), PlaylistME_1G_Data_path));
 MAP_RootPath_Empty_DATA.insert(std::make_pair(kMEPlayList_Vector.at(1), PlaylistME_1A_Data_path));
 MAP_RootPath_Empty_DATA.insert(std::make_pair(kMEPlayList_Vector.at(2), PlaylistME_1L_Data_path));
 MAP_RootPath_Empty_DATA.insert(std::make_pair(kMEPlayList_Vector.at(3), PlaylistME_1M_Data_path));
 MAP_RootPath_Empty_DATA.insert(std::make_pair(kMEPlayList_Vector.at(4), PlaylistME_1N_Data_path));
 //////////////
 //Full
 //////////////
 auto PlaylistME_1P_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1P_Data_SmearingStudy.root";
 auto PlaylistME_1C_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1C_Data_SmearingStudy.root";
 auto PlaylistME_1D_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1D_Data_SmearingStudy.root";
 auto PlaylistME_1F_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1F_Data_SmearingStudy.root";
 auto PlaylistME_1E_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1E_Data_SmearingStudy.root";

 ////////////////////
 MAP_RootPath_Full_DATA.insert(std::make_pair(kMEPlayList_Vector.at(5), PlaylistME_1P_Data_path));
 MAP_RootPath_Full_DATA.insert(std::make_pair(kMEPlayList_Vector.at(6), PlaylistME_1C_Data_path));
 MAP_RootPath_Full_DATA.insert(std::make_pair(kMEPlayList_Vector.at(7), PlaylistME_1D_Data_path));
 MAP_RootPath_Full_DATA.insert(std::make_pair(kMEPlayList_Vector.at(8), PlaylistME_1F_Data_path));
 MAP_RootPath_Full_DATA.insert(std::make_pair(kMEPlayList_Vector.at(9), PlaylistME_1E_Data_path));


 Pot_MapList EmptyPOT_local_MC_MAP = Constuct_POT_playlistMap(MAP_RootPath_Empty_MC, true);
 Pot_MapList FullPOT_local_MC_MAP  = Constuct_POT_playlistMap(MAP_RootPath_Full_MC, true);

 Pot_MapList EmptyPOT_local_Data_MAP = Constuct_POT_playlistMap(MAP_RootPath_Empty_DATA, false);
 Pot_MapList FullPOT_local_Data_MAP  = Constuct_POT_playlistMap(MAP_RootPath_Full_DATA, false);




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

 bool DoBinwidthNorm = false;
 bool MakeXaxisLOG = false;
// old method
PlayList_INFO PlaylistMC_1F(kMEPlayList_Vector.at(8),PlaylistME_1F_MC_path, is_mc, isNOT_TRUTH ,Stats_only );
PlayList_INFO PlaylistMC_1G(kMEPlayList_Vector.at(0),PlaylistME_1G_MC_path, is_mc, isNOT_TRUTH ,Stats_only );


PlayList_INFO PlaylistDATA_1F(kMEPlayList_Vector.at(8), PlaylistME_1F_Data_path, is_Data, isNOT_TRUTH ,Stats_only );
PlayList_INFO PlaylistDATA_1G(kMEPlayList_Vector.at(0), PlaylistME_1G_Data_path, is_Data, isNOT_TRUTH ,Stats_only );



//// for Nx Study
 std::string  NX_rootFilePath_MC_minerva13C_eroica = "/minerva/data/users/cnguyen/NX_LE_validation/Histograms_NX_LE_Validation_Minerva13C_Eroica_TRUTH_StatsONLY.root";
 //TFile *TFILE_minerva13C_eroica;
//  = new TFile(Smearing_rootFilePath_MC_minerva13C_eroica);

PlayList_INFO TFILE_minerva13C_eroica(NX_rootFilePath_MC_minerva13C_eroica,true,true,true);

 std::string NX_rootFilePath_MC_minerva13C_NX = "/minerva/data/users/cnguyen/NX_LE_validation/Histograms_NX_LE_Validation_Minerva13C_TRUTH_StatsONLY.root";

 PlayList_INFO TFILE_minerva13C_NX(NX_rootFilePath_MC_minerva13C_NX,true,true,true);



 //TFile *TFILE_minerva13C_NX;
 //TFILE_minerva13C_NX = new TFile(NX_rootFilePath_MC_minerva13C_NX);


//PlayList_INFO PlaylistDATA_1F(kPlayListVector_DATA[0], is_Data,false );
//PlayList_INFO PlaylistDATA_1G(kPlayListVector_DATA[1], is_Data,false );




bool Dugbug_ON=my_debug;
bool BinWithNorm_ON=false;
bool IsRECO = true;
bool IsTruth = !IsRECO;

double Convolute_R = 25.0;
double Convolute_RR = 25.0;
double Convolute_Z = 65.0;

sprintf(text_title_pdf1, "Smearing_Study_PLOTS_Fullstats.pdf(" );
can -> Print(text_title_pdf1);
sprintf(text_title_pdf2, "Smearing_Study_PLOTS_Fullstats.pdf" );
sprintf(text_title_pdf3, "Smearing_Study_PLOTS_Fullstats.pdf)" );
sprintf(text_title_pdf4, "Smearing_Study_PLOTS_Fullstats" );
std::string pdf_label = string(text_title_pdf4);

 //Hist_phyiscs_map MAP_stack =  Make_Physics_distribution_map_FromTFile(Playlist_ME1F_MC, "h_MuonCharge" , false, 1.0, kPlayListVector_MC[0], true );
 //Hist_phyiscs_map MAP_stack_G =  Make_Physics_distribution_map_FromTFile(Playlist_ME1G_MC, "h_MuonCharge" , false, 1.0, kPlayListVector_MC[1], true );



bool MakCVS=true;

  std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;

  std::cout<< "Printing Truth Varibles "<< std::endl;

  std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;

//Print Pie Figures
//  DrawPieFigures(MAP_stack_TRUTH ,  text_title_pdf4, can, mnv_plot, IsTruth,MakCVS,"MuonE");

/*
Draw_DataWITHMC_Hist_fromTFile(PlaylistMC_1F.TFILE_PLAYLIST,PlaylistMC_1G.TFILE_PLAYLIST,"h_CryoVertex_Z_upstream",
 PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_CryoVertex_Z_upstream", "1F","1G",
 pdf_label, "UpStream DATA EventRate Vertex Z","Distance to upstream Bulge [mm]","NEvents", false, false, POT_DATA_Status, POT_MC_Status );

Draw_DataWITHMC_Hist_fromTFile(PlaylistMC_1F.TFILE_PLAYLIST,PlaylistMC_1G.TFILE_PLAYLIST,"h_CryoVertex_Z_upstream",
 PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_CryoVertex_Z_upstream", "1F","1G",
pdf_label, "UpStream DATA EventRate Vertex Z","Distance to upstream Bulge [mm]","NEvents / Bin", true, false, POT_DATA_Status, POT_MC_Status );


Draw_DataWITHMC_Hist_fromTFile(PlaylistMC_1F.TFILE_PLAYLIST,PlaylistMC_1G.TFILE_PLAYLIST,"h_CryoVertex_Z_downstream",
PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_CryoVertex_Z_downstream", "1F","1G",
   pdf_label, "DownStream DATA EventRate Vertex Z","Distance to downstream Bulge [mm]","NEvents", false, false, POT_DATA_Status,POT_MC_Status );


Draw_DataWITHMC_Hist_fromTFile(PlaylistMC_1F.TFILE_PLAYLIST, PlaylistMC_1G.TFILE_PLAYLIST,"h_CryoVertex_Z_downstream",
PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_CryoVertex_Z_downstream", "1F","1G",
pdf_label, "DownStream DATA EventRate Vertex Z","Distance to downstream Bulge [mm]","NEvents / Bin", true, false, POT_DATA_Status,POT_MC_Status );

Draw_DataWITHMC_Hist_fromTFile(PlaylistMC_1F.TFILE_PLAYLIST,PlaylistMC_1G.TFILE_PLAYLIST,"h_MC_Vertex_distance_upstream",
PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_Vertex_distance_upstream", "1F","1G",
   pdf_label, "Distance to UpStream Bulge Surface","Distance to upstream Bulge [mm]","NEvents", false, false, POT_DATA_Status, POT_MC_Status );


Draw_DataWITHMC_Hist_fromTFile(PlaylistMC_1F.TFILE_PLAYLIST,PlaylistMC_1G.TFILE_PLAYLIST,"h_MC_Vertex_distance_upstream",
PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_Vertex_distance_upstream", "1F","1G",
pdf_label, "Distance to UpStream Bulge Surface","Distance to upstream Bulge [mm]","NEvents / Bin", true, false, POT_DATA_Status, POT_MC_Status );


Draw_DataWITHMC_Hist_fromTFile(PlaylistMC_1F.TFILE_PLAYLIST,PlaylistMC_1G.TFILE_PLAYLIST,"h_MC_Vertex_distance_downstream",
PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_Vertex_distance_downstream", "1F","1G",
   pdf_label, "Distance to DownStream Bulge Surface", "Distance to downstream Bulge [mm]","NEvents", false, false, POT_DATA_Status,POT_MC_Status );

Draw_DataWITHMC_Hist_fromTFile(PlaylistMC_1F.TFILE_PLAYLIST,PlaylistMC_1G.TFILE_PLAYLIST,"h_MC_Vertex_distance_downstream",
PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_Vertex_distance_downstream", "1F","1G",
pdf_label, "Distance to DownStream Bulge Surface","Distance to downstream Bulge [mm]","NEvents / Bin", true, false, POT_DATA_Status,POT_MC_Status );


Draw_DataWITHMC_Hist_fromTFile(PlaylistMC_1F.TFILE_PLAYLIST,PlaylistMC_1G.TFILE_PLAYLIST,"h_CryoVertex_R_streaming_Center",
PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_Smearing_Center_region_CryoVertex_R", "1F","1G",
   pdf_label, "EventRate[Center Region]","Vertex R [mm]","NEvents", false, false, POT_DATA_Status,POT_MC_Status );

Draw_DataWITHMC_Hist_fromTFile(PlaylistMC_1F.TFILE_PLAYLIST,PlaylistMC_1G.TFILE_PLAYLIST,"h_CryoVertex_R_streaming_Center",
PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_Smearing_Center_region_CryoVertex_R", "1F","1G",
pdf_label,    "EventRate[Center Region]","Vertex R [mm]","NEvents / Bin", true, false, POT_DATA_Status,POT_MC_Status );

Draw_DataWITHMC_Hist_fromTFile(PlaylistMC_1F.TFILE_PLAYLIST,PlaylistMC_1G.TFILE_PLAYLIST,"h_CryoVertex_R_streaming_Center",
PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_Smearing_Center_region_CryoVertex_R", "1F","1G",
   pdf_label, "EventRate[Center Region]","Vertex R [mm]","NEvents", false, true, POT_DATA_Status,POT_MC_Status );

Draw_DataWITHMC_Hist_fromTFile(PlaylistMC_1F.TFILE_PLAYLIST, PlaylistMC_1G.TFILE_PLAYLIST,"h_CryoVertex_R_streaming_Center",
PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_Smearing_Center_region_CryoVertex_R", "1F","1G",
pdf_label,   "EventRate[Center Region]","Vertex R [mm]","NEvents / Bin", true, true, POT_DATA_Status,POT_MC_Status );

Draw_DataHist_fromTFile(PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_SmearingCryoVertex_R", "1F","1G",
   pdf_label, "Vertex R [no fidical Cut]","Vertex R [mm]","NEvents", false, false, POT_DATA_Status );

Draw_DataHist_fromTFile(PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_SmearingCryoVertex_R", "1F","1G",
pdf_label, "Vertex R [no fidical Cut]","Vertex R [mm]","NEvents / Bin", true, false, POT_DATA_Status );


Draw_DataHist_fromTFile(PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_SmearingCryoVertex_R", "1F","1G",
   pdf_label, "Vertex R [no fidical Cut]","Vertex R [mm]","NEvents", false, true, POT_DATA_Status );

Draw_DataHist_fromTFile(PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_SmearingCryoVertex_R", "1F","1G",
pdf_label, "Vertex R [no fidical Cut]","Vertex R [mm]","NEvents / Bin", true, true, POT_DATA_Status );
*/

Draw_Data_RECO_TRUTH_Hist_Full_Stats("h_CryoVertex_Z_TRUTH_upstream",
                                          "h_CryoVertex_Z_upstream",
                                          "h_Data_CryoVertex_Z_upstream",
                                          FullTFile_Map_MC,  FullPOT_local_MC_ScaledMAP,
                                          EmptyTFile_Map_MC,  EmptyPOT_local_MC_ScaledMAP,
                                          FullTFile_Map_Data, FullPOT_local_Data_ScaledMAP,
                                          EmptyTFile_Map_Data, EmptyPOT_local_Data_ScaledMAP,
                                          "mm", pdf_label, "EventRate [UpStream Cap Region]",
                                          "Vertex Z [mm]", "Events", DoBinwidthNorm, MakeXaxisLOG , 180);

 Draw_Data_RECO_TRUTH_Hist_Full_Stats_Combined("h_CryoVertex_Z_TRUTH_upstream",
                                          "h_CryoVertex_Z_upstream",
                                          "h_Data_CryoVertex_Z_upstream",
                                          FullTFile_Map_MC,  FullPOT_local_MC_MAP,
                                          EmptyTFile_Map_MC,  EmptyPOT_local_MC_MAP,
                                          FullTFile_Map_Data, FullPOT_local_Data_MAP,
                                          EmptyTFile_Map_Data, EmptyPOT_local_Data_MAP,
                                          "mm", pdf_label, "EventRate [UpStream Cap Region]",
                                          "Vertex Z [mm]", "Events", DoBinwidthNorm, MakeXaxisLOG, 500);
//
int start_page=2;
int spacing=13;
Appendtotxt_SmearingPlots("Combined_Smearing" ,  pdf_label, start_page, "Vertex Z EventRate [UpStream Cap Region]" ,"mm");


//Draw_Data_RECO_TRUTH_Hist_fromTFile("h_CryoVertex_Z_TRUTH_upstream",
//PlaylistMC_1F.TFILE_PLAYLIST,PlaylistMC_1G.TFILE_PLAYLIST,"h_CryoVertex_Z_upstream",
//PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_CryoVertex_Z_upstream", "1F","1G",
//pdf_label, "UpStream DATA EventRate Vertex Z","Distance to upstream Bulge [mm]","NEvents", false, false, POT_DATA_Status, POT_MC_Status );

//Draw_Data_RECO_TRUTH_Hist_fromTFile("h_CryoVertex_Z_TRUTH_upstream",
//PlaylistMC_1F.TFILE_PLAYLIST,PlaylistMC_1G.TFILE_PLAYLIST,"h_CryoVertex_Z_upstream",
//PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_CryoVertex_Z_upstream", "1F","1G",
//pdf_label, "UpStream DATA EventRate Vertex Z","Distance to upstream Bulge [mm]","NEvents / Bin", true, false, POT_DATA_Status, POT_MC_Status );

Draw_Data_RECO_TRUTH_withConvolution_Hist_Full_Stats("h_MC_TRUTH_Vertex_distance_upstream",
                                          "h_MC_TRUTH_Vertex_distance_upstream_Convolution",
                                          "h_MC_Vertex_distance_upstream",
                                          "h_Data_Vertex_distance_upstream",
                                          FullTFile_Map_MC,  FullPOT_local_MC_ScaledMAP,
                                          EmptyTFile_Map_MC,  EmptyPOT_local_MC_ScaledMAP,
                                          FullTFile_Map_Data, FullPOT_local_Data_ScaledMAP,
                                          EmptyTFile_Map_Data, EmptyPOT_local_Data_ScaledMAP,
                                          "mm", pdf_label, "[UpStream Cap Surface] Convolute to RECO",
                                          "Distance to upstream Bulge [mm]", "Events", DoBinwidthNorm, MakeXaxisLOG, 60 ,Convolute_Z);

 Draw_Data_RECO_TRUTH_withConvolution_Hist_Full_Stats_Combined("h_MC_TRUTH_Vertex_distance_upstream",
                                          "h_MC_TRUTH_Vertex_distance_upstream_Convolution",
                                          "h_MC_Vertex_distance_upstream",
                                          "h_Data_Vertex_distance_upstream",
                                          FullTFile_Map_MC,  FullPOT_local_MC_MAP,
                                          EmptyTFile_Map_MC,  EmptyPOT_local_MC_MAP,
                                          FullTFile_Map_Data, FullPOT_local_Data_MAP,
                                          EmptyTFile_Map_Data, EmptyPOT_local_Data_MAP,
                                          "mm", pdf_label, "[UpStream Cap Surface] Convolute to RECO",
                                          "Distance to Upstream Bulge [mm]", "Events", DoBinwidthNorm, MakeXaxisLOG, 140 , Convolute_Z);
//
start_page =  start_page + spacing;
Appendtotxt_SmearingPlots("Combined_Smearing" ,  pdf_label, start_page, "[UpStream Cap Surface] Convolute to RECO" ,"mm");

Draw_Data_RECO_TRUTH_withConvolution_Hist_Full_Stats("h_MC_TRUTH_Vertex_distance_upstream",
                                          "h_MC_TRUTH_Vertex_distance_upstream_Convolution_toDATA",
                                          "h_MC_Vertex_distance_upstream",
                                          "h_Data_Vertex_distance_upstream",
                                          FullTFile_Map_MC,  FullPOT_local_MC_ScaledMAP,
                                          EmptyTFile_Map_MC,  EmptyPOT_local_MC_ScaledMAP,
                                          FullTFile_Map_Data, FullPOT_local_Data_ScaledMAP,
                                          EmptyTFile_Map_Data, EmptyPOT_local_Data_ScaledMAP,
                                          "mm", pdf_label, "[UpStream Cap Surface] Convol to DATA",
                                          "Distance to upstream Bulge [mm]", "Events", DoBinwidthNorm, MakeXaxisLOG, 60 , Convolute_Z);

 Draw_Data_RECO_TRUTH_withConvolution_Hist_Full_Stats_Combined("h_MC_TRUTH_Vertex_distance_upstream",
                                          "h_MC_TRUTH_Vertex_distance_upstream_Convolution_toDATA",
                                          "h_MC_Vertex_distance_upstream",
                                          "h_Data_Vertex_distance_upstream",
                                          FullTFile_Map_MC,  FullPOT_local_MC_MAP,
                                          EmptyTFile_Map_MC,  EmptyPOT_local_MC_MAP,
                                          FullTFile_Map_Data, FullPOT_local_Data_MAP,
                                          EmptyTFile_Map_Data, EmptyPOT_local_Data_MAP,
                                          "mm", pdf_label, "[UpStream Cap Surface] Convol to DATA",
                                          "Distance to Upstream Bulge [mm]", "Events", DoBinwidthNorm, MakeXaxisLOG, 140, Convolute_Z);
//
start_page =  start_page + spacing;
Appendtotxt_SmearingPlots("Combined_Smearing" ,  pdf_label, start_page, "[UpStream Cap Surface] Convol to DATA" ,"mm");
/////
Draw_Data_RECO_TRUTH_withConvolution_Hist_Full_Stats("h_MC_TRUTH_Vertex_distance_upstream",
                                          "h_MC_TRUTH_Vertex_distance_upstream_Convolution_toDATA_2",
                                          "h_MC_Vertex_distance_upstream",
                                          "h_Data_Vertex_distance_upstream",
                                          FullTFile_Map_MC,  FullPOT_local_MC_ScaledMAP,
                                          EmptyTFile_Map_MC,  EmptyPOT_local_MC_ScaledMAP,
                                          FullTFile_Map_Data, FullPOT_local_Data_ScaledMAP,
                                          EmptyTFile_Map_Data, EmptyPOT_local_Data_ScaledMAP,
                                          "mm", pdf_label, "[UpStream Cap Surface] double double Convol to DATA",
                                          "Distance to upstream Bulge [mm]", "Events", DoBinwidthNorm, MakeXaxisLOG, 60 , Convolute_Z);

 Draw_Data_RECO_TRUTH_withConvolution_Hist_Full_Stats_Combined("h_MC_TRUTH_Vertex_distance_upstream",
                                          "h_MC_TRUTH_Vertex_distance_upstream_Convolution_toDATA_2",
                                          "h_MC_Vertex_distance_upstream",
                                          "h_Data_Vertex_distance_upstream",
                                          FullTFile_Map_MC,  FullPOT_local_MC_MAP,
                                          EmptyTFile_Map_MC,  EmptyPOT_local_MC_MAP,
                                          FullTFile_Map_Data, FullPOT_local_Data_MAP,
                                          EmptyTFile_Map_Data, EmptyPOT_local_Data_MAP,
                                          "mm", pdf_label, "[UpStream Cap Surface] double Convol to DATA",
                                          "Distance to Upstream Bulge [mm]", "Events", DoBinwidthNorm, MakeXaxisLOG, 140, Convolute_Z);
//
start_page =  start_page + spacing;
Appendtotxt_SmearingPlots("Combined_Smearing" ,  pdf_label, start_page, "[UpStream Cap Surface] double Convol to DATA" ,"mm");


//Draw_Data_RECO_TRUTH_Hist_fromTFile("h_MC_TRUTH_Vertex_distance_upstream",
//PlaylistMC_1F.TFILE_PLAYLIST,PlaylistMC_1G.TFILE_PLAYLIST,"h_MC_Vertex_distance_upstream",
//PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_Vertex_distance_upstream", "1F","1G",
//pdf_label, "Distance to UpStream Bulge Surface","Distance to upstream Bulge [mm]","NEvents", false, false, POT_DATA_Status, POT_MC_Status );

//Draw_Data_RECO_TRUTH_Hist_fromTFile("h_MC_TRUTH_Vertex_distance_upstream",
//PlaylistMC_1F.TFILE_PLAYLIST,PlaylistMC_1G.TFILE_PLAYLIST,"h_MC_Vertex_distance_upstream",
//PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_Vertex_distance_upstream", "1F","1G",
//pdf_label, "Distance to UpStream Bulge Surface","Distance to upstream Bulge [mm]","NEvents / Bin", true, false, POT_DATA_Status, POT_MC_Status );

Draw_Data_RECO_TRUTH_Hist_Full_Stats("h_CryoVertex_Z_TRUTH_downstream",
                                          "h_CryoVertex_Z_downstream",
                                          "h_Data_CryoVertex_Z_downstream",
                                          FullTFile_Map_MC,  FullPOT_local_MC_ScaledMAP,
                                          EmptyTFile_Map_MC,  EmptyPOT_local_MC_ScaledMAP,
                                          FullTFile_Map_Data, FullPOT_local_Data_ScaledMAP,
                                          EmptyTFile_Map_Data, EmptyPOT_local_Data_ScaledMAP,
                                          "mm", pdf_label, "EventRate [Downstream Cap Region]",
                                          "Vertex Z [mm]", "Events", DoBinwidthNorm, MakeXaxisLOG , 800);

 Draw_Data_RECO_TRUTH_Hist_Full_Stats_Combined("h_CryoVertex_Z_TRUTH_downstream",
                                          "h_CryoVertex_Z_downstream",
                                          "h_Data_CryoVertex_Z_downstream",
                                          FullTFile_Map_MC,  FullPOT_local_MC_MAP,
                                          EmptyTFile_Map_MC,  EmptyPOT_local_MC_MAP,
                                          FullTFile_Map_Data, FullPOT_local_Data_MAP,
                                          EmptyTFile_Map_Data, EmptyPOT_local_Data_MAP,
                                          "mm", pdf_label, "EventRate [Downstream Cap Region]",
                                          "Vertex Z [mm]", "Events", DoBinwidthNorm, MakeXaxisLOG, 2500);
//
start_page =  start_page + spacing;
Appendtotxt_SmearingPlots("Combined_Smearing" ,  pdf_label, start_page, "EventRate [Downstream Cap Region]" ,"mm");



Draw_Data_RECO_TRUTH_withConvolution_Hist_Full_Stats("h_MC_TRUTH_Vertex_distance_downstream",
                                          "h_MC_TRUTH_Vertex_distance_downstream_Convolution",
                                          "h_MC_Vertex_distance_downstream",
                                          "h_Data_Vertex_distance_downstream",
                                          FullTFile_Map_MC,  FullPOT_local_MC_ScaledMAP,
                                          EmptyTFile_Map_MC,  EmptyPOT_local_MC_ScaledMAP,
                                          FullTFile_Map_Data, FullPOT_local_Data_ScaledMAP,
                                          EmptyTFile_Map_Data, EmptyPOT_local_Data_ScaledMAP,
                                          "mm", pdf_label, "[DownStream Cap] Convoluted to RECO",
                                          "Distance to downstream Bulge [mm]", "Events", DoBinwidthNorm, MakeXaxisLOG, 300 , Convolute_Z);


 Draw_Data_RECO_TRUTH_withConvolution_Hist_Full_Stats_Combined("h_MC_TRUTH_Vertex_distance_downstream",
                                          "h_MC_TRUTH_Vertex_distance_downstream_Convolution",
                                          "h_MC_Vertex_distance_downstream",
                                          "h_Data_Vertex_distance_downstream",
                                          FullTFile_Map_MC,  FullPOT_local_MC_MAP,
                                          EmptyTFile_Map_MC,  EmptyPOT_local_MC_MAP,
                                          FullTFile_Map_Data, FullPOT_local_Data_MAP,
                                          EmptyTFile_Map_Data, EmptyPOT_local_Data_MAP,
                                          "mm", pdf_label, "[DownStream Cap] Convoluted to RECO",
                                          "Distance to downstream Bulge [mm]", "Events", DoBinwidthNorm, MakeXaxisLOG, 900, Convolute_Z);
//
start_page =  start_page + spacing;
Appendtotxt_SmearingPlots("Combined_Smearing" ,  pdf_label, start_page, "[DownStream Cap] Convoluted to RECO" ,"mm");


Draw_Data_RECO_TRUTH_withConvolution_Hist_Full_Stats("h_MC_TRUTH_Vertex_distance_downstream",
                                          "h_MC_TRUTH_Vertex_distance_downstream_Convolution_toDATA",
                                          "h_MC_Vertex_distance_downstream",
                                          "h_Data_Vertex_distance_downstream",
                                          FullTFile_Map_MC,  FullPOT_local_MC_ScaledMAP,
                                          EmptyTFile_Map_MC,  EmptyPOT_local_MC_ScaledMAP,
                                          FullTFile_Map_Data, FullPOT_local_Data_ScaledMAP,
                                          EmptyTFile_Map_Data, EmptyPOT_local_Data_ScaledMAP,
                                          "mm", pdf_label, "[DownStream Cap] Convoluted to DATA",
                                          "Distance to downstream Bulge [mm]", "Events", DoBinwidthNorm, MakeXaxisLOG, 350 , Convolute_Z);

 Draw_Data_RECO_TRUTH_withConvolution_Hist_Full_Stats_Combined("h_MC_TRUTH_Vertex_distance_downstream",
                                          "h_MC_TRUTH_Vertex_distance_downstream_Convolution_toDATA",
                                          "h_MC_Vertex_distance_downstream",
                                          "h_Data_Vertex_distance_downstream",
                                          FullTFile_Map_MC,  FullPOT_local_MC_MAP,
                                          EmptyTFile_Map_MC,  EmptyPOT_local_MC_MAP,
                                          FullTFile_Map_Data, FullPOT_local_Data_MAP,
                                          EmptyTFile_Map_Data, EmptyPOT_local_Data_MAP,
                                          "mm", pdf_label, "[DownStream Cap] Convoluted to DATA",
                                          "Distance to downstream Bulge [mm]", "Events", DoBinwidthNorm, MakeXaxisLOG, 1000 , Convolute_Z);
//
start_page =  start_page + spacing;
Appendtotxt_SmearingPlots("Combined_Smearing" ,  pdf_label, start_page, "[DownStream Cap] Convoluted to DATA" ,"mm");


Draw_Data_RECO_TRUTH_withConvolution_Hist_Full_Stats("h_CryoVertex_R_streaming_TRUTH_Center",
                                          "h_CryoVertex_R_streaming_TRUTH_Center_Convolution",
                                          "h_CryoVertex_R_streaming_Center",
                                          "h_Data_Smearing_Center_region_CryoVertex_R",
                                          FullTFile_Map_MC,  FullPOT_local_MC_ScaledMAP,
                                          EmptyTFile_Map_MC,  EmptyPOT_local_MC_ScaledMAP,
                                          FullTFile_Map_Data, FullPOT_local_Data_ScaledMAP,
                                          EmptyTFile_Map_Data, EmptyPOT_local_Data_ScaledMAP,
                                          "mm", pdf_label, "[Barrel] Convoluted to RECO",
                                          "Vertex R [mm]", "Events", DoBinwidthNorm, MakeXaxisLOG, 450, Convolute_R);

 Draw_Data_RECO_TRUTH_withConvolution_Hist_Full_Stats_Combined("h_CryoVertex_R_streaming_TRUTH_Center",
                                          "h_CryoVertex_R_streaming_TRUTH_Center_Convolution",
                                          "h_CryoVertex_R_streaming_Center",
                                          "h_Data_Smearing_Center_region_CryoVertex_R",
                                          FullTFile_Map_MC,  FullPOT_local_MC_MAP,
                                          EmptyTFile_Map_MC,  EmptyPOT_local_MC_MAP,
                                          FullTFile_Map_Data, FullPOT_local_Data_MAP,
                                          EmptyTFile_Map_Data, EmptyPOT_local_Data_MAP,
                                          "mm", pdf_label, "[Barrel] Convoluted to RECO",
                                          "Vertex R [mm]", "Events", DoBinwidthNorm, MakeXaxisLOG, 1000, Convolute_R);
//
start_page =  start_page + spacing;
Appendtotxt_SmearingPlots("Combined_Smearing" ,  pdf_label, start_page, "[Center] Convoluted to RECO" ,"mm");


Draw_Data_RECO_TRUTH_withConvolution_Hist_Full_Stats("h_CryoVertex_R_streaming_TRUTH_Center",
                                          "h_CryoVertex_R_streaming_TRUTH_Center_Convolution_toData",
                                          "h_CryoVertex_R_streaming_Center",
                                          "h_Data_Smearing_Center_region_CryoVertex_R",
                                          FullTFile_Map_MC,  FullPOT_local_MC_ScaledMAP,
                                          EmptyTFile_Map_MC,  EmptyPOT_local_MC_ScaledMAP,
                                          FullTFile_Map_Data, FullPOT_local_Data_ScaledMAP,
                                          EmptyTFile_Map_Data, EmptyPOT_local_Data_ScaledMAP,
                                          "mm", pdf_label, "[Barrel] Convoluted to Data",
                                          "Vertex R [mm]", "Events", DoBinwidthNorm, MakeXaxisLOG, 450, Convolute_R );

 Draw_Data_RECO_TRUTH_withConvolution_Hist_Full_Stats_Combined("h_CryoVertex_R_streaming_TRUTH_Center",
                                          "h_CryoVertex_R_streaming_TRUTH_Center_Convolution_toData",
                                          "h_CryoVertex_R_streaming_Center",
                                          "h_Data_Smearing_Center_region_CryoVertex_R",
                                          FullTFile_Map_MC,  FullPOT_local_MC_MAP,
                                          EmptyTFile_Map_MC,  EmptyPOT_local_MC_MAP,
                                          FullTFile_Map_Data, FullPOT_local_Data_MAP,
                                          EmptyTFile_Map_Data, EmptyPOT_local_Data_MAP,
                                          "mm", pdf_label, "[Barrel] Convoluted to Data",
                                          "Vertex R [mm]", "Events", DoBinwidthNorm, MakeXaxisLOG, 1000, Convolute_R);
//
start_page =  start_page + spacing;
Appendtotxt_SmearingPlots("Combined_Smearing" ,  pdf_label, start_page, "[Center] Convoluted to RECO" ,"mm");






Draw_Data_RECO_TRUTH_withConvolution_Hist_Full_Stats("h_CryoVertex_RR_streaming_TRUTH_Center",
                                          "h_CryoVertex_RR_streaming_TRUTH_Center_Convolution",
                                          "h_CryoVertex_RR_streaming_Center",
                                          "h_Data_Smearing_Center_region_CryoVertex_RR",
                                          FullTFile_Map_MC,  FullPOT_local_MC_ScaledMAP,
                                          EmptyTFile_Map_MC,  EmptyPOT_local_MC_ScaledMAP,
                                          FullTFile_Map_Data, FullPOT_local_Data_ScaledMAP,
                                          EmptyTFile_Map_Data, EmptyPOT_local_Data_ScaledMAP,
                                          "mm", pdf_label, "[Barrel] Convoluted to Reco",
                                          "Vertex R^{2} [mm]", "Events", DoBinwidthNorm, MakeXaxisLOG, 400 , Convolute_RR);

 Draw_Data_RECO_TRUTH_withConvolution_Hist_Full_Stats_Combined("h_CryoVertex_RR_streaming_TRUTH_Center",
                                          "h_CryoVertex_RR_streaming_TRUTH_Center_Convolution",
                                          "h_CryoVertex_RR_streaming_Center",
                                          "h_Data_Smearing_Center_region_CryoVertex_RR",
                                          FullTFile_Map_MC,  FullPOT_local_MC_MAP,
                                          EmptyTFile_Map_MC,  EmptyPOT_local_MC_MAP,
                                          FullTFile_Map_Data, FullPOT_local_Data_MAP,
                                          EmptyTFile_Map_Data, EmptyPOT_local_Data_MAP,
                                          "mm", pdf_label, "[Barrel] Convoluted to Reco",
                                          "Vertex R^{2} [mm]", "Events", DoBinwidthNorm, MakeXaxisLOG, 1000, Convolute_RR);
//
start_page =  start_page + spacing;
Appendtotxt_SmearingPlots("Combined_Smearing" ,  pdf_label, start_page, "[Center] Convoluted to Data" ,"mm");



Draw_Data_RECO_TRUTH_withConvolution_Hist_Full_Stats("h_CryoVertex_RR_streaming_TRUTH_Center",
                                          "h_CryoVertex_RR_streaming_TRUTH_Center_Convolution_toData",
                                          "h_CryoVertex_RR_streaming_Center",
                                          "h_Data_Smearing_Center_region_CryoVertex_RR",
                                          FullTFile_Map_MC,  FullPOT_local_MC_ScaledMAP,
                                          EmptyTFile_Map_MC,  EmptyPOT_local_MC_ScaledMAP,
                                          FullTFile_Map_Data, FullPOT_local_Data_ScaledMAP,
                                          EmptyTFile_Map_Data, EmptyPOT_local_Data_ScaledMAP,
                                          "mm", pdf_label, "[Barrel] Convoluted to Data",
                                          "Vertex R^{2} [mm]", "Events", DoBinwidthNorm, MakeXaxisLOG, 400, Convolute_RR);

 Draw_Data_RECO_TRUTH_withConvolution_Hist_Full_Stats_Combined("h_CryoVertex_RR_streaming_TRUTH_Center",
                                          "h_CryoVertex_RR_streaming_TRUTH_Center_Convolution_toData",
                                          "h_CryoVertex_RR_streaming_Center",
                                          "h_Data_Smearing_Center_region_CryoVertex_RR",
                                          FullTFile_Map_MC,  FullPOT_local_MC_MAP,
                                          EmptyTFile_Map_MC,  EmptyPOT_local_MC_MAP,
                                          FullTFile_Map_Data, FullPOT_local_Data_MAP,
                                          EmptyTFile_Map_Data, EmptyPOT_local_Data_MAP,
                                          "mm", pdf_label, "[Barrel] Convoluted to Data",
                                          "Vertex R^{2} [mm]", "Events", DoBinwidthNorm, MakeXaxisLOG, 1000, Convolute_RR);
//
start_page =  start_page + spacing;
Appendtotxt_SmearingPlots("Combined_Smearing" ,  pdf_label, start_page, "[Center] Convoluted to Data" ,"mm");




/*



Draw_Data_RECO_TRUTH_Hist_Full_Stats("h_CryoVertex_R_streaming_TRUTH_Center",
                                          "h_CryoVertex_R_streaming_Center",
                                          "h_Data_Smearing_Center_region_CryoVertex_R",
                                          FullTFile_Map_MC,  FullPOT_local_MC_ScaledMAP,
                                          EmptyTFile_Map_MC,  EmptyPOT_local_MC_ScaledMAP,
                                          FullTFile_Map_Data, FullPOT_local_Data_ScaledMAP,
                                          EmptyTFile_Map_Data, EmptyPOT_local_Data_ScaledMAP,
                                          "mm", pdf_label, "EventRate [Center Region]",
                                          "Vertex R [mm]", "Events", DoBinwidthNorm, MakeXaxisLOG, 450);

 Draw_Data_RECO_TRUTH_Hist_Full_Stats_Combined("h_CryoVertex_R_streaming_TRUTH_Center",
                                          "h_CryoVertex_R_streaming_Center",
                                          "h_Data_Smearing_Center_region_CryoVertex_R",
                                          FullTFile_Map_MC,  FullPOT_local_MC_MAP,
                                          EmptyTFile_Map_MC,  EmptyPOT_local_MC_MAP,
                                          FullTFile_Map_Data, FullPOT_local_Data_MAP,
                                          EmptyTFile_Map_Data, EmptyPOT_local_Data_MAP,
                                          "mm", pdf_label, "EventRate [Center Region]",
                                          "Vertex R [mm]", "Events", DoBinwidthNorm, MakeXaxisLOG, 1200);
//

start_page =  start_page + spacing;
Appendtotxt_SmearingPlots("Combined_Smearing" ,  pdf_label, start_page, "Vertex R EventRate [Center]" ,"mm");
*/





Draw_Data_RECO_TRUTH_Hist_Full_Stats("h_CryoVertex_Z_Center_TRUTH",
                                          "h_CryoVertex_Z_Center",
                                          "h_Data_CryoVertex_Z_Center",
                                          FullTFile_Map_MC,  FullPOT_local_MC_ScaledMAP,
                                          EmptyTFile_Map_MC,  EmptyPOT_local_MC_ScaledMAP,
                                          FullTFile_Map_Data, FullPOT_local_Data_ScaledMAP,
                                          EmptyTFile_Map_Data, EmptyPOT_local_Data_ScaledMAP,
                                          "mm", pdf_label, "EventRate [Center Region]",
                                          "Vertex Z [mm]", "Events", DoBinwidthNorm, MakeXaxisLOG, 1000);

 Draw_Data_RECO_TRUTH_Hist_Full_Stats_Combined("h_CryoVertex_Z_Center_TRUTH",
                                          "h_CryoVertex_Z_Center",
                                          "h_Data_CryoVertex_Z_Center",
                                          FullTFile_Map_MC,  FullPOT_local_MC_MAP,
                                          EmptyTFile_Map_MC,  EmptyPOT_local_MC_MAP,
                                          FullTFile_Map_Data, FullPOT_local_Data_MAP,
                                          EmptyTFile_Map_Data, EmptyPOT_local_Data_MAP,
                                          "mm", pdf_label, "EventRate [Center Region]",
                                          "Vertex Z [mm]", "Events", DoBinwidthNorm, MakeXaxisLOG, 2500);
//
start_page =  start_page + spacing;
Appendtotxt_SmearingPlots("Combined_Smearing" ,  pdf_label, start_page, "Vertex Z EventRate [Center]" ,"mm");

std::vector<StackType> StackType_vector;

StackType_vector.push_back(kMaterial);
StackType_vector.push_back(kInteraction);
StackType_vector.push_back(kParticle);

for(auto Stack_type:StackType_vector){

DrawSTACKfromHistFilio_FULLStats(FullTFile_Map_MC,  FullPOT_local_MC_ScaledMAP,
                              EmptyTFile_Map_MC,  EmptyPOT_local_MC_ScaledMAP,
                              FullTFile_Map_Data, FullPOT_local_Data_ScaledMAP,
                              EmptyTFile_Map_Data, EmptyPOT_local_Data_ScaledMAP,
"h_secTrk_tracklength_upstreamCAP" ,"h_Data_secTrk_tracklength_upstreamCap", "Upstream Cap Region: TrackLength",
"TrackLength", pdf_label, DoBinwidthNorm, "mm", Stack_type, my_debug );

DrawSTACKfromHistFilio_FULLStatsCOMBINED(FullTFile_Map_MC,  FullPOT_local_MC_MAP,
                                EmptyTFile_Map_MC,  EmptyPOT_local_MC_MAP,
                                FullTFile_Map_Data, FullPOT_local_Data_MAP,
                                EmptyTFile_Map_Data, EmptyPOT_local_Data_MAP,
"h_secTrk_tracklength_upstreamCAP" ,"h_Data_secTrk_tracklength_upstreamCap", "Upstream Cap Region: TrackLength",
"TrackLength", pdf_label, DoBinwidthNorm, "mm", Stack_type, my_debug );


DrawSTACKfromHistFilio_FULLStats(FullTFile_Map_MC,  FullPOT_local_MC_ScaledMAP,
                                  EmptyTFile_Map_MC,  EmptyPOT_local_MC_ScaledMAP,
                                  FullTFile_Map_Data, FullPOT_local_Data_ScaledMAP,
                                  EmptyTFile_Map_Data, EmptyPOT_local_Data_ScaledMAP,
  "h_secTrk_tracklength_downstreamCAP" ,"h_Data_secTrk_tracklength_downstreamCap", "Downstream Cap Region: TrackLength",
  "TrackLength", pdf_label, DoBinwidthNorm, "mm", Stack_type, my_debug );

DrawSTACKfromHistFilio_FULLStatsCOMBINED(FullTFile_Map_MC,  FullPOT_local_MC_MAP,
                                    EmptyTFile_Map_MC,  EmptyPOT_local_MC_MAP,
                                    FullTFile_Map_Data, FullPOT_local_Data_MAP,
                                    EmptyTFile_Map_Data, EmptyPOT_local_Data_MAP,
"h_secTrk_tracklength_downstreamCAP" ,"h_Data_secTrk_tracklength_downstreamCap", "Downstream Cap Region: TrackLength",
"TrackLength", pdf_label, DoBinwidthNorm, "mm", Stack_type, my_debug );


DrawSTACKfromHistFilio_FULLStats(FullTFile_Map_MC,  FullPOT_local_MC_ScaledMAP,
                                      EmptyTFile_Map_MC,  EmptyPOT_local_MC_ScaledMAP,
                                      FullTFile_Map_Data, FullPOT_local_Data_ScaledMAP,
                                      EmptyTFile_Map_Data, EmptyPOT_local_Data_ScaledMAP,
"h_secTrk_tracklength_Barrel" ,"h_Data_secTrk_tracklength_Barrel", "Barrel Region: TrackLength",
"TrackLength", pdf_label, DoBinwidthNorm, "mm", Stack_type, my_debug );

DrawSTACKfromHistFilio_FULLStatsCOMBINED(FullTFile_Map_MC,  FullPOT_local_MC_MAP,
                                        EmptyTFile_Map_MC,  EmptyPOT_local_MC_MAP,
                                        FullTFile_Map_Data, FullPOT_local_Data_MAP,
                                        EmptyTFile_Map_Data, EmptyPOT_local_Data_MAP,
"h_secTrk_tracklength_Barrel" ,"h_Data_secTrk_tracklength_Barrel", "Barrel Region: TrackLength",
"TrackLength", pdf_label, DoBinwidthNorm, "mm", Stack_type, my_debug );


}


 can -> Print(text_title_pdf3);


 sprintf(text_title_pdf1, "NX_Study_PLOTS_%s.pdf(",timeset_nonstacks );
 can -> Print(text_title_pdf1);
 sprintf(text_title_pdf2, "NX_Study_PLOTS_%s.pdf",timeset_nonstacks );
 sprintf(text_title_pdf3, "NX_Study_PLOTS_%s.pdf)",timeset_nonstacks );
 sprintf(text_title_pdf4, "NX_Study_PLOTS_%s",timeset_nonstacks );
 std::string pdfstring_NX(text_title_pdf4);


 DrawSINGLESTACKMCHistFilio_FromTFile(TFILE_minerva13C_NX.TFILE_PLAYLIST,  "h_CryoVertex_Z_TRUE_Material" , "Truth Vertex Z stack [NX][Minerva13C]", "vertex Z [mm]", pdfstring_NX, false, true );
 DrawSINGLESTACKMCHistFilio_FromTFile(TFILE_minerva13C_NX.TFILE_PLAYLIST,  "h_CryoVertex_X_TRUE_Material" , "Truth Vertex X stack [NX][Minerva13C]", "vertex X [mm]", pdfstring_NX, false, true );
 DrawSINGLESTACKMCHistFilio_FromTFile(TFILE_minerva13C_NX.TFILE_PLAYLIST,  "h_CryoVertex_Y_TRUE_Material" , "Truth Vertex Y stack [NX][Minerva13C]", "vertex Y [mm]", pdfstring_NX, false, true );
 DrawSINGLESTACKMCHistFilio_FromTFile(TFILE_minerva13C_NX.TFILE_PLAYLIST,  "h_CryoVertex_R_TRUE_Material" , "Truth Vertex R stack [NX][Minerva13C]", "vertex R [mm]", pdfstring_NX, false, true );
 DrawSINGLESTACKMCHistFilio_FromTFile(TFILE_minerva13C_NX.TFILE_PLAYLIST,  "h_CryoVertex_RR_TRUE_Material" , "Truth Vertex R^2 stack [NX][Minerva13C]", "vertex R^2 [mm]", pdfstring_NX, false, true );
 Draw_MCHist_withErrorSys_fromTFile(TFILE_minerva13C_NX.TFILE_PLAYLIST,  "h_MuonPZ_TRUE", pdfstring_NX, "Muon P_{L} [Z=2][NX][Minerva13C]","P_{L} [GeV]","Nevents / Bin ",  true);
 Draw_MCHist_withErrorSys_fromTFile(TFILE_minerva13C_NX.TFILE_PLAYLIST,  "h_MuonPT_TRUE", pdfstring_NX, "Muon P_{T} [Z=2][NX][Minerva13C]","P_{T} [GeV]","Nevents / Bin ",  true);
 Draw_MCHist_withErrorSys_fromTFile(TFILE_minerva13C_NX.TFILE_PLAYLIST,  "h_MuonTheta_TRUE", pdfstring_NX, "Muon #theta [Z=2][NX][Minerva13C]","#theta_{#mu} [DeG]","Nevents / Bin ",  true);

 DrawSINGLESTACKMCHistFilio_FromTFile(TFILE_minerva13C_eroica.TFILE_PLAYLIST,  "h_CryoVertex_Z_TRUE_Material" , "Truth Vertex Z stack [eroica][Minerva13C]", "vertex Z [mm]", pdfstring_NX, false, true );
 DrawSINGLESTACKMCHistFilio_FromTFile(TFILE_minerva13C_eroica.TFILE_PLAYLIST,  "h_CryoVertex_X_TRUE_Material" , "Truth Vertex X stack [eroica][Minerva13C]", "vertex X [mm]", pdfstring_NX, false, true );
 DrawSINGLESTACKMCHistFilio_FromTFile(TFILE_minerva13C_eroica.TFILE_PLAYLIST,  "h_CryoVertex_Y_TRUE_Material" , "Truth Vertex Y stack [eroica][Minerva13C]", "vertex Y [mm]", pdfstring_NX, false, true );
 DrawSINGLESTACKMCHistFilio_FromTFile(TFILE_minerva13C_eroica.TFILE_PLAYLIST,  "h_CryoVertex_R_TRUE_Material" , "Truth Vertex R stack [eroica][Minerva13C]", "vertex R [mm]", pdfstring_NX, false, true );
 DrawSINGLESTACKMCHistFilio_FromTFile(TFILE_minerva13C_eroica.TFILE_PLAYLIST,  "h_CryoVertex_RR_TRUE_Material" , "Truth Vertex R^2 stack [eroica][Minerva13C]", "vertex R^2 [mm]", pdfstring_NX, false, true );
 Draw_MCHist_withErrorSys_fromTFile(TFILE_minerva13C_eroica.TFILE_PLAYLIST,  "h_MuonPZ_TRUE", pdfstring_NX, "Muon P_{L} [Z=2][eroica][Minerva13C]","P_{L} [GeV]","Nevents / Bin ",  true);
 Draw_MCHist_withErrorSys_fromTFile(TFILE_minerva13C_eroica.TFILE_PLAYLIST,  "h_MuonPT_TRUE", pdfstring_NX, "Muon P_{T} [Z=2][eroica][Minerva13C]","P_{T} [GeV]","Nevents / Bin ",  true);
 Draw_MCHist_withErrorSys_fromTFile(TFILE_minerva13C_eroica.TFILE_PLAYLIST,  "h_MuonTheta_TRUE", pdfstring_NX, "Muon #theta [Z=2][eroica][Minerva13C]","#theta_{#mu} [DeG]","Nevents / Bin ",  true);







double MaxY = 1.08;
double MinY = .92;


Draw_RATIO_fromTFiles(TFILE_minerva13C_NX.TFILE_PLAYLIST,  "h_CryoVertex_Z_TRUE_Material_Helium", "NX Helium" ,
TFILE_minerva13C_eroica.TFILE_PLAYLIST,  "h_CryoVertex_Z_TRUE_Material_Helium","EroicaPlus Helium", "#frac{NX}{EroicaPlus}", pdfstring_NX,
"[True Helium] CryoVertex Z", "Vertex Z [mm]","Area Normalized EventRate" ,false, MinY, MaxY );

Draw_RATIO_fromTFiles(TFILE_minerva13C_NX.TFILE_PLAYLIST,  "h_CryoVertex_Z_TRUE_Material_Aluminium", "NX Aluminium" ,
TFILE_minerva13C_eroica.TFILE_PLAYLIST,  "h_CryoVertex_Z_TRUE_Material_Aluminium","EroicaPlus Aluminium", "#frac{NX}{EroicaPlus}", pdfstring_NX,
"[True Al] CryoVertex Z", "Vertex Z [mm]","Area Normalized EventRate" ,false, MinY, MaxY );

 Draw_RATIO_fromTFiles(TFILE_minerva13C_NX.TFILE_PLAYLIST,  "h_CryoVertex_X_TRUE_Material_Helium", "NX Helium" ,
 TFILE_minerva13C_eroica.TFILE_PLAYLIST,  "h_CryoVertex_X_TRUE_Material_Helium","EroicaPlus Helium", "#frac{NX}{EroicaPlus}", pdfstring_NX,
 "[True Helium] CryoVertex X", "Vertex X [mm]","Area Normalized EventRate" ,false, MinY, MaxY );

 Draw_RATIO_fromTFiles(TFILE_minerva13C_NX.TFILE_PLAYLIST,  "h_CryoVertex_X_TRUE_Material_Aluminium", "NX Aluminium" ,
 TFILE_minerva13C_eroica.TFILE_PLAYLIST,  "h_CryoVertex_X_TRUE_Material_Aluminium","EroicaPlus Aluminium", "#frac{NX}{EroicaPlus}", pdfstring_NX,
 "[True Al] CryoVertex X", "Vertex X [mm]","Area Normalized EventRate" ,false, MinY, MaxY );

 Draw_RATIO_fromTFiles(TFILE_minerva13C_NX.TFILE_PLAYLIST,  "h_CryoVertex_Y_TRUE_Material_Helium", "NX Helium" ,
 TFILE_minerva13C_eroica.TFILE_PLAYLIST,  "h_CryoVertex_Y_TRUE_Material_Helium","EroicaPlus Helium", "#frac{NX}{EroicaPlus}", pdfstring_NX,
 "[True Helium] CryoVertex Y", "Vertex Y [mm]","Area Normalized EventRate" ,false, MinY, MaxY );

 Draw_RATIO_fromTFiles(TFILE_minerva13C_NX.TFILE_PLAYLIST,  "h_CryoVertex_Y_TRUE_Material_Aluminium", "NX Aluminium" ,
 TFILE_minerva13C_eroica.TFILE_PLAYLIST,  "h_CryoVertex_Y_TRUE_Material_Aluminium","EroicaPlus Aluminium", "#frac{NX}{EroicaPlus}", pdfstring_NX,
 "[True Al] CryoVertex Y", "Vertex Y [mm]","Area Normalized EventRate" ,false, MinY, MaxY );

 Draw_RATIO_fromTFiles(TFILE_minerva13C_NX.TFILE_PLAYLIST,  "h_CryoVertex_R_TRUE_Material_Helium", "NX Helium" ,
 TFILE_minerva13C_eroica.TFILE_PLAYLIST,  "h_CryoVertex_R_TRUE_Material_Helium","EroicaPlus Helium", "#frac{NX}{EroicaPlus}", pdfstring_NX,
 "[True Helium] CryoVertex R", "Vertex R [mm]","Area Normalized EventRate" ,false, MinY, MaxY );

 Draw_RATIO_fromTFiles(TFILE_minerva13C_NX.TFILE_PLAYLIST,  "h_CryoVertex_R_TRUE_Material_Aluminium", "NX Aluminium" ,
 TFILE_minerva13C_eroica.TFILE_PLAYLIST,  "h_CryoVertex_R_TRUE_Material_Aluminium","EroicaPlus Aluminium", "#frac{NX}{EroicaPlus}", pdfstring_NX,
 "[True Al] CryoVertex R", "Vertex R [mm]","Area Normalized EventRate" ,false, MinY, MaxY );


  Draw_RATIO_fromTFiles(TFILE_minerva13C_NX.TFILE_PLAYLIST,  "h_CryoVertex_RR_TRUE_Material_Helium", "NX Helium" ,
  TFILE_minerva13C_eroica.TFILE_PLAYLIST,  "h_CryoVertex_RR_TRUE_Material_Helium","EroicaPlus Helium", "#frac{NX}{EroicaPlus}", pdfstring_NX,
  "[True Helium] CryoVertex R^{2}", "Vertex R^{2} [mm]","Area Normalized EventRate" ,false, MinY, MaxY );

  Draw_RATIO_fromTFiles(TFILE_minerva13C_NX.TFILE_PLAYLIST,  "h_CryoVertex_RR_TRUE_Material_Aluminium", "NX Aluminium" ,
  TFILE_minerva13C_eroica.TFILE_PLAYLIST,  "h_CryoVertex_RR_TRUE_Material_Aluminium","EroicaPlus Aluminium", "#frac{NX}{EroicaPlus}", pdfstring_NX,
  "[True Al] CryoVertex R^{2}", "Vertex R^{2} [mm]","Area Normalized EventRate" ,false, MinY, MaxY );

  Draw_RATIO_fromTFiles(TFILE_minerva13C_NX.TFILE_PLAYLIST,  "h_CryoVertex_X_TRUE_Material_Helium", "NX Helium" ,
  TFILE_minerva13C_eroica.TFILE_PLAYLIST,  "h_CryoVertex_X_TRUE_Material_Helium","EroicaPlus Helium", "#frac{NX}{EroicaPlus}", pdfstring_NX,
  "[True Helium] CryoVertex X", "Vertex X [mm]","Area Normalized EventRate" ,false);


  Draw_RATIO_fromTFiles(TFILE_minerva13C_NX.TFILE_PLAYLIST,  "h_CryoVertex_Z_TRUE_Material_Aluminium", "NX Aluminium" ,
  TFILE_minerva13C_eroica.TFILE_PLAYLIST,  "h_CryoVertex_Z_TRUE_Material_Aluminium","EroicaPlus Aluminium", "#frac{NX}{EroicaPlus}", pdfstring_NX,
  "[True Al] CryoVertex Z", "Vertex Z [mm]","Area Normalized EventRate" ,false );

  can -> Print(text_title_pdf3);
  can->Close();


std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;

std::cout<< " Done with Muon Plots"<< std::endl;

std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;

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
std::cout << std::boolalpha << my_norm << std::endl;

int my_Print_Systmatics;
std::cout << "Print Error Systmatics?  [ 0 = Total and Groups Systemtics Errors ,  1 = Total Systematic Errors , 2 = none ]" << std::endl;
std::cin >> my_Print_Systmatics;
std::cout << "Pitched: " << my_Print_Systmatics << std::endl;


bool my_debug;
std::cout << "Run in Debug Mode? (0 = NO, 1 = YES) " << std::endl;
std::cin >> my_debug;
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


Playlist.push_back(kME1F);
  //Playlist.push_back(kME1A);
  Playlist.push_back(kME1G);
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
  //MuonVars.push_back(kAnglePhi);
  MuonVars.push_back(kDOCA_muon);
//  MuonVars.push_back(kcurvatureSig);

  //MuonVars.push_back(kminosMuon_Energy);

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

  MuonVars.push_back(ktracksize);

  return MuonVars;
//#endif
}

std::vector<MuonVar> GetMUONVaribles_Stacks() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<MuonVar> MuonVars;

  //MuonVars.push_back(kMuonMatchtoVeto);
  //MuonVars.push_back(kMuonMatchtoMinos);
  MuonVars.push_back(kCharge);
  MuonVars.push_back(kE);

  MuonVars.push_back(kP_Z);


  MuonVars.push_back(kP_T);


  MuonVars.push_back(kAngleWRTB);
  //MuonVars.push_back(kAnglePhi);
  MuonVars.push_back(kDOCA_muon);
  MuonVars.push_back(kcurvatureSig);
  //MuonVars.push_back(kminosMuon_Energy);


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


void MakeLatexForMuonFiguresFORStacks(std::string output_name ,std::vector<MuonVar> muon_vector ,  std::string pdf_name){
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


void MakeLatexForMuonFiguresCVandALLErrors(std::string output_name ,std::vector<MuonVar> muon_vector, std::string PDF_cv_name, int NError_Groups){
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



void MakeLatexForMuonFiguresCVandGroupErrors_andALLSTACKS(int Systmatic_ErrorType ,std::string output_name ,
  std::vector<MuonVar> muon_vector,  std::string pdf_name_CV, std::string pdf_stack_Material, std::string pdf_stack_Interaction,
  std::string pdf_stack_Particle, int NError_Groups)
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

  }//end of
///////////////
//
///////////////
void Draw_Data_RECO_TRUTH_Hist_Full_Stats(char *histoName_TRUTH_RECO,
                                          char *histoName_MC_RECO,
                                          char *histoName_data,
                                          ME_playlist_TFileMAP FullMCMap,    Pot_MapList FullMC_scalerMap,
                                          ME_playlist_TFileMAP EmptyMCMap,   Pot_MapList EmptyMC_scalerMap,
                                          ME_playlist_TFileMAP FullDataMap,  Pot_MapList FullData_scalerMap,
                                          ME_playlist_TFileMAP EmptyDataMap, Pot_MapList EmptyData_scalerMap,
                                          std::string units, std::string pdf_label, char* hist_title,
                                          char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG, double Ymax
                                        ){

  Playlist_MnvH1D_Map FULLMC_TRUTH_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullMCMap, histoName_TRUTH_RECO );
  Playlist_MnvH1D_Map FULLMC_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullMCMap, histoName_MC_RECO );
  Playlist_MnvH1D_Map FULLData_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullDataMap, histoName_data );

  Playlist_MnvH1D_Map FULLMC_HistMAPScaled =  Scale_MnvH1D_Map_usingPot_MapList(FULLMC_HistMAP , FullMC_scalerMap , histoName_MC_RECO  );
  Playlist_MnvH1D_Map FULLMC_TRUTH_HistMAPScaled =  Scale_MnvH1D_Map_usingPot_MapList(FULLMC_TRUTH_HistMAP , FullMC_scalerMap , histoName_TRUTH_RECO  );
  Playlist_MnvH1D_Map FULLData_HistMAPScaled =  Scale_MnvH1D_Map_usingPot_MapList(FULLData_HistMAP , FullData_scalerMap , histoName_data  );


  Playlist_MnvH1D_Map EmptyMC_TRUTH_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(EmptyMCMap, histoName_TRUTH_RECO );
  Playlist_MnvH1D_Map EmptyMC_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(EmptyMCMap, histoName_MC_RECO );
  Playlist_MnvH1D_Map EmptyData_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(EmptyDataMap, histoName_data );

  Playlist_MnvH1D_Map EmptyMC_TRUTH_HistMAPScaled =  Scale_MnvH1D_Map_usingPot_MapList(EmptyMC_TRUTH_HistMAP , EmptyMC_scalerMap , histoName_TRUTH_RECO  );
  Playlist_MnvH1D_Map EmptyMC_HistMAPScaled =  Scale_MnvH1D_Map_usingPot_MapList(EmptyMC_HistMAP , EmptyMC_scalerMap , histoName_MC_RECO  );
  Playlist_MnvH1D_Map EmptyData_HistMAPScaled =  Scale_MnvH1D_Map_usingPot_MapList(EmptyData_HistMAP , EmptyData_scalerMap , histoName_data  );

  typename std::map<ME_helium_Playlists, PlotUtils::MnvH1D*>::const_iterator catMC;
  typename std::map<ME_helium_Playlists, PlotUtils::MnvH1D*>::const_iterator birdMC_truth;
  typename std::map<ME_helium_Playlists, PlotUtils::MnvH1D*>::const_iterator dogdata;

  for (catMC = FULLMC_HistMAPScaled.begin(), birdMC_truth = FULLMC_TRUTH_HistMAPScaled.begin(), dogdata = FULLData_HistMAPScaled.begin(); catMC != FULLMC_HistMAPScaled.end(); ++catMC, ++birdMC_truth, ++dogdata)
  {
    std::string Playlist_Name = GetPlaylist_InitialName(catMC->first);
    char Playlist_Name_char[Playlist_Name.length()+1];
    strcpy(Playlist_Name_char,Playlist_Name.c_str());

    std::string HeliumStatus_name = GetPlaylistStatusString(GetPlaylist_HeliumStatus(catMC->first));
    char HeliumStatus_name_char[HeliumStatus_name.length()+1];
    strcpy(HeliumStatus_name_char,HeliumStatus_name.c_str());


    Draw_Data_RECO_TRUTH_Hist_fromPointer( birdMC_truth->second, catMC->second,  dogdata->second,
      Playlist_Name_char, HeliumStatus_name_char, pdf_label, hist_title,
      xaxislabel,yaxislabel, DoBinwidthNorm, MakeXaxisLOG, Ymax);
    }// end of full loop

    for (catMC = EmptyMC_HistMAPScaled.begin(), birdMC_truth = EmptyMC_TRUTH_HistMAPScaled.begin(), dogdata = EmptyData_HistMAPScaled.begin(); catMC != EmptyMC_HistMAPScaled.end(); ++catMC, ++birdMC_truth, ++dogdata)
    {
      std::string Playlist_Name = GetPlaylist_InitialName(catMC->first);
      char Playlist_Name_char[Playlist_Name.length()+1];
      strcpy(Playlist_Name_char,Playlist_Name.c_str());

      std::string HeliumStatus_name = GetPlaylistStatusString(GetPlaylist_HeliumStatus(catMC->first));
      char HeliumStatus_name_char[HeliumStatus_name.length()+1];
      strcpy(HeliumStatus_name_char,HeliumStatus_name.c_str());


      Draw_Data_RECO_TRUTH_Hist_fromPointer( birdMC_truth->second, catMC->second,  dogdata->second,
        Playlist_Name_char, HeliumStatus_name_char, pdf_label, hist_title,
        xaxislabel,yaxislabel, DoBinwidthNorm, MakeXaxisLOG, Ymax);
      }// end of full loop


    }//end of function
/////////////////////////////////
//
/////////////////////////////////


void Draw_Data_RECO_TRUTH_Hist_Full_Stats_Combined(char *histoName_TRUTH_RECO,
                                          char *histoName_MC_RECO,
                                          char *histoName_data,
                                          ME_playlist_TFileMAP FullMCMap,    Pot_MapList FullMC_POTMap,
                                          ME_playlist_TFileMAP EmptyMCMap,   Pot_MapList EmptyMC_POTMap,
                                          ME_playlist_TFileMAP FullDataMap,  Pot_MapList FullData_POTMap,
                                          ME_playlist_TFileMAP EmptyDataMap, Pot_MapList EmptyData_POTMap,
                                          std::string units, std::string pdf_label, char* hist_title,
                                          char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG, double Ymax
                                        ){

 CyroStatusPot_MapList POT_MAP = Constuct_TOTALPOT_cryostatusMap(FullMC_POTMap, EmptyMC_POTMap, true);


  Playlist_MnvH1D_Map FULLMC_TRUTH_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullMCMap, histoName_TRUTH_RECO );
  Playlist_MnvH1D_Map FULLMC_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullMCMap, histoName_MC_RECO );
  Playlist_MnvH1D_Map FULLData_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullDataMap, histoName_data );

  Playlist_MnvH1D_Map EmptyMC_TRUTH_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(EmptyMCMap, histoName_TRUTH_RECO );
  Playlist_MnvH1D_Map EmptyMC_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(EmptyMCMap, histoName_MC_RECO );
  Playlist_MnvH1D_Map EmptyData_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(EmptyDataMap, histoName_data );

  CyroStatusPot_MapList POTMAP_TOTAL =  Constuct_TOTALPOT_cryostatusMap(FullMC_POTMap, EmptyMC_POTMap, FullData_POTMap, EmptyData_POTMap);
  CyroStatusPot_MapList POTMAP_TOTAL_scaler = MakeScaler_TOTALPOT_cryostatusMapTOFULLDATA(POTMAP_TOTAL);

  auto FULL_MC_Hist = Combine_Hists_fromMAP(FULLMC_HistMAP , kME1F ,"FULL_MC_Hist");
  auto FULL_MC_TRUTH_Hist = Combine_Hists_fromMAP(FULLMC_TRUTH_HistMAP , kME1F ,"FULL_MC_TRUTH_Hist");
  auto FULL_Data_Hist = Combine_Hists_fromMAP(FULLData_HistMAP , kME1F ,"FULL_Data_Hist");

  auto FULL_EmptyMC_Hist =(MnvH1D*) FULL_MC_Hist->Clone("FULL_EmptyMC_Hist");
  auto FULL_EmptyMC_TRUTH_Hist =(MnvH1D*) FULL_MC_TRUTH_Hist->Clone("FULL_EmptyMC_TRUTH_Hist");
  auto FULL_EmptyData_Hist =(MnvH1D*) FULL_Data_Hist->Clone("FULL_EmptyData_Hist");

  FULL_MC_Hist->Scale(POTMAP_TOTAL_scaler[kMC_FULL]);
  FULL_MC_TRUTH_Hist->Scale(POTMAP_TOTAL_scaler[kMC_FULL]);
  FULL_EmptyMC_Hist->Scale(POTMAP_TOTAL_scaler[kMC_FULL]);
  FULL_EmptyMC_TRUTH_Hist->Scale(POTMAP_TOTAL_scaler[kMC_FULL]);

  Draw_Data_RECO_TRUTH_Hist_fromPointer(FULL_MC_TRUTH_Hist, FULL_MC_Hist,  FULL_Data_Hist,
    "Combined", "Full", pdf_label, hist_title,
    xaxislabel,yaxislabel, DoBinwidthNorm, MakeXaxisLOG, Ymax);
    //////////
    //Empty
    ////////

    auto Empty_MC_Hist = Combine_Hists_fromMAP(EmptyMC_HistMAP , kME1M ,"Empty_MC_Hist");
    auto Empty_MC_Hist_clone =(MnvH1D*) Empty_MC_Hist->Clone("Empty_MC_Hist_clone");

    auto Empty_MC_TRUTH_Hist = Combine_Hists_fromMAP(EmptyMC_TRUTH_HistMAP , kME1M ,"Empty_MC_TRUTH_Hist");
    auto Empty_MC_TRUTH_Hist_clone =(MnvH1D*) Empty_MC_TRUTH_Hist->Clone("Empty_MC_TRUTH_Hist_clone");

    auto Empty_Data_Hist = Combine_Hists_fromMAP(EmptyData_HistMAP , kME1M ,"Empty_Data_Hist");
    auto Empty_Data_Hist_clone =(MnvH1D*) Empty_Data_Hist->Clone("Empty_Data_Hist_clone");


    Empty_MC_Hist->Scale(POTMAP_TOTAL_scaler[kMC_EMPTY]);
    Empty_MC_TRUTH_Hist->Scale(POTMAP_TOTAL_scaler[kMC_EMPTY]);

    Empty_MC_Hist_clone->Scale(POTMAP_TOTAL_scaler[kMC_EMPTY]);
    Empty_MC_TRUTH_Hist_clone->Scale(POTMAP_TOTAL_scaler[kMC_EMPTY]);

    Empty_Data_Hist->Scale(POTMAP_TOTAL_scaler[kDATA_EMPTY]);
    Empty_Data_Hist_clone->Scale(POTMAP_TOTAL_scaler[kDATA_EMPTY]);

    Draw_Data_RECO_TRUTH_Hist_fromPointer(Empty_MC_TRUTH_Hist, Empty_MC_Hist, Empty_Data_Hist,
      "Combined", "Empty", pdf_label, hist_title,
      xaxislabel,yaxislabel, DoBinwidthNorm, MakeXaxisLOG, Ymax);
      /////////////////////////////
      //F-E
      /////////////////////////////
      FULL_EmptyMC_Hist->Add(Empty_MC_Hist_clone,-1);
      FULL_EmptyMC_TRUTH_Hist->Add(Empty_MC_TRUTH_Hist_clone,-1);
      FULL_EmptyData_Hist->Add(Empty_Data_Hist_clone,-1);

      Draw_Data_RECO_TRUTH_Hist_fromPointer(FULL_EmptyMC_TRUTH_Hist, FULL_EmptyMC_Hist, FULL_EmptyData_Hist,
        "Combined", "F-E", pdf_label, hist_title,
        xaxislabel,yaxislabel, DoBinwidthNorm, MakeXaxisLOG, Ymax);


}//end of function

    void Appendtotxt_SmearingPlots(std::string output_name ,  std::string pdf_name_CV, int First_page, char *Var_name ,char *Units_name)
      {
      double scale= .23;
      std::ofstream myfile;

     std::string fileName = output_name + ".txt";
      myfile.open(fileName, std::ios_base::app);
      std::cout<<"Adding to Latex File "<< fileName<<std::endl;
      LatexFormat Muon_latex_Latex(scale);

      myfile<<Muon_latex_Latex.GetSubSection(Var_name);
      int index = First_page;
      int Column_Spacing = 1;

      std::cout<<"appending to latex starting with Page = "<< index<<std::endl;
      myfile<<"\n";
      myfile<<"\n";
      myfile<<"%%%%%%%%%%%%%%%%% \n";
      myfile<<"%%% Full for Smearing "<< Var_name <<" \n";
      myfile<<"%%%%%%%%%%%%%%%%% \n";
      myfile<<Muon_latex_Latex.GetBeginFrame(Var_name)<< "\n";
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

      myfile<<Muon_latex_Latex.GetEndFrame();

      myfile<<"\n";
      myfile<<"%%%%%%%%%%%%%%%%% \n";
      myfile<<"%%% Frame ALL EMPTY Playlist Breakdown"<< Var_name <<" \n";
      myfile<<"%%%%%%%%%%%%%%%%% \n";
      myfile<<Muon_latex_Latex.GetBeginFrame(Var_name)<< "\n";
      myfile<<Muon_latex_Latex.GetBeginTabular("ccc")<< "\n";
      myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 5, pdf_name_CV)<< "\n";
      myfile<<"& \n";
      myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 6, pdf_name_CV)<< "\n";
      myfile<<"& \n";
      myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 7, pdf_name_CV)<< "\n";
      myfile<<"\\\\ \n";
      myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 8, pdf_name_CV)<< "\n";
      myfile<<"& \n";
      myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 9, pdf_name_CV)<< "\n";
      myfile<<Muon_latex_Latex.GetEndTabular()<< "\n";
      myfile<<Muon_latex_Latex.GetEndFrame();


        myfile<<"\n";
        myfile<<"\n";
        myfile<<"%%%%%%%%%%%%%%%%% \n";
        myfile<<"%%% Frame FUll -  EMPTY"<< Var_name <<" \n";
        myfile<<"%%%%%%%%%%%%%%%%% \n";
        myfile<<Muon_latex_Latex.GetBeginFrame(Var_name)<< "\n";
        myfile<<Muon_latex_Latex.GetBeginTabular("ccc")<< "\n";
        myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 10, pdf_name_CV, .24)<< "\n";
        myfile<<"& \n";
        myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 11, pdf_name_CV, .24 )<< "\n";
        myfile<<"& \n";
        myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 12, pdf_name_CV, .24)<< "\n";
        myfile<<Muon_latex_Latex.GetEndTabular()<< "\n";
        myfile<<Muon_latex_Latex.GetEndFrame();


        myfile.close();


    }//end of
    //////////////////////////////////////////////////////////////
    void Draw_Data_RECO_TRUTH_withConvolution_Hist_Full_Stats(char *histoName_TRUTH_RECO,
                                              char *histoName_TRUTH_RECO_Convol,
                                              char *histoName_MC_RECO,
                                              char *histoName_data,
                                              ME_playlist_TFileMAP FullMCMap,    Pot_MapList FullMC_scalerMap,
                                              ME_playlist_TFileMAP EmptyMCMap,   Pot_MapList EmptyMC_scalerMap,
                                              ME_playlist_TFileMAP FullDataMap,  Pot_MapList FullData_scalerMap,
                                              ME_playlist_TFileMAP EmptyDataMap, Pot_MapList EmptyData_scalerMap,
                                              std::string units, std::string pdf_label, char* hist_title,
                                              char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG, double Ymax, double ConvolutedBymm
                                            ){

      Playlist_MnvH1D_Map FULLMC_TRUTH_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullMCMap, histoName_TRUTH_RECO );
      Playlist_MnvH1D_Map FULLMC_TRUTH_Colv_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullMCMap, histoName_TRUTH_RECO_Convol );

      Playlist_MnvH1D_Map FULLMC_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullMCMap, histoName_MC_RECO );
      Playlist_MnvH1D_Map FULLData_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullDataMap, histoName_data );

      Playlist_MnvH1D_Map FULLMC_HistMAPScaled =  Scale_MnvH1D_Map_usingPot_MapList(FULLMC_HistMAP , FullMC_scalerMap , histoName_MC_RECO  );
      Playlist_MnvH1D_Map FULLMC_TRUTH_HistMAPScaled =  Scale_MnvH1D_Map_usingPot_MapList(FULLMC_TRUTH_HistMAP , FullMC_scalerMap , histoName_TRUTH_RECO  );
      Playlist_MnvH1D_Map FULLMC_TRUTH_Colv_HistMAPScaled =  Scale_MnvH1D_Map_usingPot_MapList(FULLMC_TRUTH_Colv_HistMAP , FullMC_scalerMap , histoName_TRUTH_RECO_Convol);

      Playlist_MnvH1D_Map FULLData_HistMAPScaled =  Scale_MnvH1D_Map_usingPot_MapList(FULLData_HistMAP , FullData_scalerMap , histoName_data  );


      Playlist_MnvH1D_Map EmptyMC_TRUTH_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(EmptyMCMap, histoName_TRUTH_RECO );
      Playlist_MnvH1D_Map EmptyMC_TRUTH_Colv_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(EmptyMCMap, histoName_TRUTH_RECO_Convol );

      Playlist_MnvH1D_Map EmptyMC_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(EmptyMCMap, histoName_MC_RECO );
      Playlist_MnvH1D_Map EmptyData_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(EmptyDataMap, histoName_data );

      Playlist_MnvH1D_Map EmptyMC_TRUTH_HistMAPScaled =  Scale_MnvH1D_Map_usingPot_MapList(EmptyMC_TRUTH_HistMAP , EmptyMC_scalerMap , histoName_TRUTH_RECO  );
      Playlist_MnvH1D_Map EmptyMC_TRUTH_Colv_HistMAPScaled =  Scale_MnvH1D_Map_usingPot_MapList(EmptyMC_TRUTH_Colv_HistMAP , EmptyMC_scalerMap , histoName_TRUTH_RECO_Convol  );

      Playlist_MnvH1D_Map EmptyMC_HistMAPScaled =  Scale_MnvH1D_Map_usingPot_MapList(EmptyMC_HistMAP , EmptyMC_scalerMap , histoName_MC_RECO  );
      Playlist_MnvH1D_Map EmptyData_HistMAPScaled =  Scale_MnvH1D_Map_usingPot_MapList(EmptyData_HistMAP , EmptyData_scalerMap , histoName_data  );

      typename std::map<ME_helium_Playlists, PlotUtils::MnvH1D*>::const_iterator catMC;
      typename std::map<ME_helium_Playlists, PlotUtils::MnvH1D*>::const_iterator birdMC_truth;
      typename std::map<ME_helium_Playlists, PlotUtils::MnvH1D*>::const_iterator tigerMC_colvtruth;
      typename std::map<ME_helium_Playlists, PlotUtils::MnvH1D*>::const_iterator dogdata;

      for (catMC = FULLMC_HistMAPScaled.begin(), birdMC_truth = FULLMC_TRUTH_HistMAPScaled.begin(), dogdata = FULLData_HistMAPScaled.begin(), tigerMC_colvtruth = FULLMC_TRUTH_Colv_HistMAPScaled.begin(); catMC != FULLMC_HistMAPScaled.end(); ++catMC, ++birdMC_truth, ++tigerMC_colvtruth, ++dogdata)
      {
        std::string Playlist_Name = GetPlaylist_InitialName(catMC->first);
        char Playlist_Name_char[Playlist_Name.length()+1];
        strcpy(Playlist_Name_char,Playlist_Name.c_str());

        std::string HeliumStatus_name = GetPlaylistStatusString(GetPlaylist_HeliumStatus(catMC->first));
        char HeliumStatus_name_char[HeliumStatus_name.length()+1];
        strcpy(HeliumStatus_name_char,HeliumStatus_name.c_str());

          Draw_Data_RECO_TRUTH_Hist_withConvolution_fromPointers(dogdata->second,
            catMC->second, tigerMC_colvtruth->second,birdMC_truth->second,
            Playlist_Name_char, pdf_label, hist_title, HeliumStatus_name_char,
            xaxislabel, yaxislabel, DoBinwidthNorm, MakeXaxisLOG ,Ymax, ConvolutedBymm);

        }// end of full loop

        for (catMC = EmptyMC_HistMAPScaled.begin(), birdMC_truth = EmptyMC_TRUTH_HistMAPScaled.begin(), dogdata = EmptyData_HistMAPScaled.begin(), tigerMC_colvtruth = EmptyMC_TRUTH_Colv_HistMAPScaled.begin(); catMC != EmptyMC_HistMAPScaled.end(); ++catMC, ++birdMC_truth, ++tigerMC_colvtruth, ++dogdata)
        {
          std::string Playlist_Name = GetPlaylist_InitialName(catMC->first);
          char Playlist_Name_char[Playlist_Name.length()+1];
          strcpy(Playlist_Name_char,Playlist_Name.c_str());

          std::string HeliumStatus_name = GetPlaylistStatusString(GetPlaylist_HeliumStatus(catMC->first));
          char HeliumStatus_name_char[HeliumStatus_name.length()+1];
          strcpy(HeliumStatus_name_char,HeliumStatus_name.c_str());


          Draw_Data_RECO_TRUTH_Hist_withConvolution_fromPointers(dogdata->second,
            catMC->second, tigerMC_colvtruth->second,birdMC_truth->second,
            Playlist_Name_char, pdf_label, hist_title, HeliumStatus_name_char,
            xaxislabel, yaxislabel, DoBinwidthNorm, MakeXaxisLOG ,Ymax, ConvolutedBymm);
          }// end of full loop


        }//end of function




        void Draw_Data_RECO_TRUTH_withConvolution_Hist_Full_Stats_Combined(char *histoName_TRUTH_RECO,
                                                    char *histoName_TRUTH_RECO_Convol,
                                                  char *histoName_MC_RECO,
                                                  char *histoName_data,
                                                  ME_playlist_TFileMAP FullMCMap,    Pot_MapList FullMC_POTMap,
                                                  ME_playlist_TFileMAP EmptyMCMap,   Pot_MapList EmptyMC_POTMap,
                                                  ME_playlist_TFileMAP FullDataMap,  Pot_MapList FullData_POTMap,
                                                  ME_playlist_TFileMAP EmptyDataMap, Pot_MapList EmptyData_POTMap,
                                                  std::string units, std::string pdf_label, char* hist_title,
                                                  char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG, double Ymax, double ConvolutedBymm
                                                ){

         CyroStatusPot_MapList POT_MAP = Constuct_TOTALPOT_cryostatusMap(FullMC_POTMap, EmptyMC_POTMap, true);


          Playlist_MnvH1D_Map FULLMC_TRUTH_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullMCMap, histoName_TRUTH_RECO );
          Playlist_MnvH1D_Map FULLMC_TRUTH_Convol_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullMCMap, histoName_TRUTH_RECO_Convol );

          Playlist_MnvH1D_Map FULLMC_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullMCMap, histoName_MC_RECO );
          Playlist_MnvH1D_Map FULLData_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullDataMap, histoName_data );

          Playlist_MnvH1D_Map EmptyMC_TRUTH_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(EmptyMCMap, histoName_TRUTH_RECO );
          Playlist_MnvH1D_Map EmptyMC_TRUTH_Convol_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(EmptyMCMap, histoName_TRUTH_RECO_Convol );
          Playlist_MnvH1D_Map EmptyMC_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(EmptyMCMap, histoName_MC_RECO );
          Playlist_MnvH1D_Map EmptyData_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(EmptyDataMap, histoName_data );

          CyroStatusPot_MapList POTMAP_TOTAL =  Constuct_TOTALPOT_cryostatusMap(FullMC_POTMap, EmptyMC_POTMap, FullData_POTMap, EmptyData_POTMap);
          CyroStatusPot_MapList POTMAP_TOTAL_scaler = MakeScaler_TOTALPOT_cryostatusMapTOFULLDATA(POTMAP_TOTAL);

          auto FULL_MC_Hist = Combine_Hists_fromMAP(FULLMC_HistMAP , kME1F ,"FULL_MC_Hist");
          auto FULL_MC_TRUTH_Hist = Combine_Hists_fromMAP(FULLMC_TRUTH_HistMAP , kME1F ,"FULL_MC_TRUTH_Hist");
          auto FULL_MC_TRUTH_Convol_Hist = Combine_Hists_fromMAP(FULLMC_TRUTH_Convol_HistMAP , kME1F ,"FULL_MC_TRUTH_Convol_Hist");
          auto FULL_Data_Hist = Combine_Hists_fromMAP(FULLData_HistMAP , kME1F ,"FULL_Data_Hist");

          auto FULL_EmptyMC_Hist =(MnvH1D*) FULL_MC_Hist->Clone("FULL_EmptyMC_Hist");
          auto FULL_EmptyMC_TRUTH_Hist =(MnvH1D*) FULL_MC_TRUTH_Hist->Clone("FULL_EmptyMC_TRUTH_Hist");
          auto FULL_EmptyMC_TRUTH_Convol_Hist =(MnvH1D*) FULL_MC_TRUTH_Convol_Hist->Clone("FULL_MC_TRUTH_Convol_Hist");

          auto FULL_EmptyData_Hist =(MnvH1D*) FULL_Data_Hist->Clone("FULL_EmptyData_Hist");

          FULL_MC_Hist->Scale(POTMAP_TOTAL_scaler[kMC_FULL]);
          FULL_MC_TRUTH_Hist->Scale(POTMAP_TOTAL_scaler[kMC_FULL]);
          FULL_MC_TRUTH_Convol_Hist->Scale(POTMAP_TOTAL_scaler[kMC_FULL]);

          FULL_EmptyMC_Hist->Scale(POTMAP_TOTAL_scaler[kMC_FULL]);
          FULL_EmptyMC_TRUTH_Hist->Scale(POTMAP_TOTAL_scaler[kMC_FULL]);
          FULL_EmptyMC_TRUTH_Convol_Hist->Scale(POTMAP_TOTAL_scaler[kMC_FULL]);

            Draw_Data_RECO_TRUTH_Hist_withConvolution_fromPointers(FULL_Data_Hist,
              FULL_MC_Hist, FULL_MC_TRUTH_Convol_Hist, FULL_MC_TRUTH_Hist,
              "Combined", pdf_label, hist_title, "Full",
              xaxislabel, yaxislabel, DoBinwidthNorm, MakeXaxisLOG ,Ymax, ConvolutedBymm);

            //////////
            //Empty
            ////////

            auto Empty_MC_Hist = Combine_Hists_fromMAP(EmptyMC_HistMAP , kME1M ,"Empty_MC_Hist");
            auto Empty_MC_Hist_clone =(MnvH1D*) Empty_MC_Hist->Clone("Empty_MC_Hist_clone");

            auto Empty_MC_TRUTH_Hist = Combine_Hists_fromMAP(EmptyMC_TRUTH_HistMAP , kME1M ,"Empty_MC_TRUTH_Hist");
            auto Empty_MC_Convol_TRUTH_Hist = Combine_Hists_fromMAP(EmptyMC_TRUTH_Convol_HistMAP , kME1M ,"Empty_MC_Convol_TRUTH_Hist");
            auto Empty_MC_TRUTH_Hist_clone =(MnvH1D*) Empty_MC_TRUTH_Hist->Clone("Empty_MC_TRUTH_Hist_clone");
            auto Empty_MC_Convol_TRUTH_Hist_clone =(MnvH1D*) Empty_MC_Convol_TRUTH_Hist->Clone("Empty_MC_Convol_TRUTH_Hist_clone");

            auto Empty_Data_Hist = Combine_Hists_fromMAP(EmptyData_HistMAP , kME1M ,"Empty_Data_Hist");
            auto Empty_Data_Hist_clone =(MnvH1D*) Empty_Data_Hist->Clone("Empty_Data_Hist_clone");


            Empty_MC_Hist->Scale(POTMAP_TOTAL_scaler[kMC_EMPTY]);
            Empty_MC_TRUTH_Hist->Scale(POTMAP_TOTAL_scaler[kMC_EMPTY]);
            Empty_MC_Convol_TRUTH_Hist->Scale(POTMAP_TOTAL_scaler[kMC_EMPTY]);

            Empty_MC_Hist_clone->Scale(POTMAP_TOTAL_scaler[kMC_EMPTY]);
            Empty_MC_TRUTH_Hist_clone->Scale(POTMAP_TOTAL_scaler[kMC_EMPTY]);
            Empty_MC_Convol_TRUTH_Hist_clone->Scale(POTMAP_TOTAL_scaler[kMC_EMPTY]);


            Empty_Data_Hist->Scale(POTMAP_TOTAL_scaler[kDATA_EMPTY]);
            Empty_Data_Hist_clone->Scale(POTMAP_TOTAL_scaler[kDATA_EMPTY]);

              Draw_Data_RECO_TRUTH_Hist_withConvolution_fromPointers(Empty_Data_Hist,
                Empty_MC_Hist, Empty_MC_Convol_TRUTH_Hist, Empty_MC_TRUTH_Hist,
                "Combined", pdf_label, hist_title, "Empty",
                xaxislabel, yaxislabel, DoBinwidthNorm, MakeXaxisLOG ,Ymax , ConvolutedBymm);

              /////////////////////////////
              //F-E
              /////////////////////////////
              FULL_EmptyMC_Hist->Add(Empty_MC_Hist_clone,-1);
              FULL_EmptyMC_TRUTH_Hist->Add(Empty_MC_TRUTH_Hist_clone,-1);
              FULL_EmptyMC_TRUTH_Convol_Hist->Add(Empty_MC_Convol_TRUTH_Hist_clone,-1);
              FULL_EmptyData_Hist->Add(Empty_Data_Hist_clone,-1);


                Draw_Data_RECO_TRUTH_Hist_withConvolution_fromPointers(FULL_EmptyData_Hist,
                  FULL_EmptyMC_Hist, FULL_EmptyMC_TRUTH_Convol_Hist, FULL_EmptyMC_TRUTH_Hist,
                  "Combined", pdf_label, hist_title, "F-E",
                  xaxislabel, yaxislabel, DoBinwidthNorm, MakeXaxisLOG ,Ymax, ConvolutedBymm);

        }//end of function
