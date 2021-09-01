#include "Smearing_Study.h"


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
void Kin(bool &cutsOn, bool &my_norm, bool &my_debug, const char *userDir, bool &BinNorm , int &Print_Systematics, int &m_CVorStacks ) {
TH1::AddDirectory(false);
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~       Starting Plotter: FOR Plots for Smearing Study        ~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;


const std::vector<ME_helium_Playlists> kPlayListVector_MC = GetPlayListVector_MC();
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
 auto Playlist_names =  MakePlaylistString(kPlayListVector_MC);
 sprintf(timeset_nonstacks,"%i_%i_%i_%i_%s_%s", 1 + ltm->tm_mon,ltm->tm_mday, ltm->tm_hour,ltm->tm_min, SysError_printLabel.c_str(),Playlist_names.c_str());
 sprintf(timeset, "%i_%i_%i_%i", 1 + ltm->tm_mon,ltm->tm_mday, ltm->tm_hour,ltm->tm_min);

bool is_mc=true;
bool is_Data=false;
bool isNOT_TRUTH=false;
bool is_TRUTH=true;

std::string pdf_CV = string(text_title_pdf4);


 bool Stats_only = false;
 std::string Smearing_rootFilePath = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/SMEARING_STUDY_minervame1F_MC_All_SysErrorsOn4U.root";
 std::string Smearing_rootFilePath_G = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/SMEARING_STUDY_minervame1G_MC_All_SysErrorsOn4U.root";

 std::string rootFilePath_F = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1F_MC_All_SysErrorsOn.root";
 std::string rootFilePath_G = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1G_MC_All_SysErrorsOn.root";


 //std::string Smearing_rootFilePathTRUTH_F = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1F_TRUTH_StatsONLY_SMEARING.root";
 //std::string Smearing_rootFilePathTRUTH_G = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1G_TRUTH_StatsONLY_SMEARING.root";

 std::string Smearing_rootFilePath_DATA_F = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1F_Data_SmearingStudy.root";
 std::string Smearing_rootFilePath_DATA_G = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1G_Data_SmearingStudy.root";

//// for Nx Study
 std::string  NX_rootFilePath_MC_minerva13C_eroica = "/minerva/data/users/cnguyen/NX_LE_validation/Histograms_NX_LE_Validation_Minerva13C_Eroica_TRUTH_StatsONLY.root";
 //TFile *TFILE_minerva13C_eroica;
//  = new TFile(Smearing_rootFilePath_MC_minerva13C_eroica);

PlayList_INFO TFILE_minerva13C_eroica(NX_rootFilePath_MC_minerva13C_eroica,true,true,true);

 std::string NX_rootFilePath_MC_minerva13C_NX = "/minerva/data/users/cnguyen/NX_LE_validation/Histograms_NX_LE_Validation_Minerva13C_TRUTH_StatsONLY.root";

 PlayList_INFO TFILE_minerva13C_NX(NX_rootFilePath_MC_minerva13C_NX,true,true,true);



 //TFile *TFILE_minerva13C_NX;
 //TFILE_minerva13C_NX = new TFile(NX_rootFilePath_MC_minerva13C_NX);



PlayList_INFO PlaylistMC_1F(kPlayListVector_MC[0],Smearing_rootFilePath, is_mc, isNOT_TRUTH ,Stats_only );
PlayList_INFO PlaylistMC_1G(kPlayListVector_MC[1],Smearing_rootFilePath_G, is_mc, isNOT_TRUTH ,Stats_only );

PlayList_INFO PlaylistMC_1F_error(kPlayListVector_MC[0],rootFilePath_F, is_mc, isNOT_TRUTH ,Stats_only );
PlayList_INFO PlaylistMC_1G_error(kPlayListVector_MC[1],rootFilePath_G, is_mc, isNOT_TRUTH ,Stats_only );


PlayList_INFO PlaylistDATA_1F(kPlayListVector_MC[0], Smearing_rootFilePath_DATA_F, is_Data, isNOT_TRUTH ,Stats_only );
PlayList_INFO PlaylistDATA_1G(kPlayListVector_MC[1], Smearing_rootFilePath_DATA_G, is_Data, isNOT_TRUTH ,Stats_only );

//PlayList_INFO PlaylistTRUTH_1F(kPlayListVector_MC[0], Smearing_rootFilePathTRUTH_F, is_mc, isNOT_TRUTH ,Stats_only );
//PlayList_INFO PlaylistTRUTH_1G(kPlayListVector_MC[1], Smearing_rootFilePathTRUTH_G, is_mc, isNOT_TRUTH ,Stats_only );


//PlayList_INFO PlaylistDATA_1F(kPlayListVector_DATA[0], is_Data,false );
//PlayList_INFO PlaylistDATA_1G(kPlayListVector_DATA[1], is_Data,false );

std::vector <PlayList_INFO> Data_playlist;


Data_playlist.push_back(PlaylistDATA_1F);
Data_playlist.push_back(PlaylistDATA_1G);

POT_DATA[kPlayListVector_DATA[0]] = PlaylistDATA_1F.Get_Pot();
POT_DATA[kPlayListVector_DATA[1]] = PlaylistDATA_1G.Get_Pot();

POT_DATA_Status[kFULL] = PlaylistDATA_1F.Get_Pot();
POT_DATA_Status[kEMPTY] = PlaylistDATA_1G.Get_Pot();

POT_MC[kPlayListVector_MC[0]] = PlaylistMC_1F.Get_Pot();
POT_MC[kPlayListVector_MC[1]] = PlaylistMC_1G.Get_Pot();


POT_MC_Status[kFULL] = PlaylistMC_1F.Get_Pot();
POT_MC_Status[kEMPTY] = PlaylistMC_1G.Get_Pot();

std::vector <PlayList_INFO> MC_playlist;
MC_playlist.push_back(PlaylistMC_1F);


bool Dugbug_ON=my_debug;
bool BinWithNorm_ON=false;
bool IsRECO = true;
bool IsTruth = !IsRECO;

sprintf(text_title_pdf1, "Smearing_Study_PLOTS_%s.pdf(",timeset_nonstacks );
can -> Print(text_title_pdf1);
sprintf(text_title_pdf2, "Smearing_Study_PLOTS_%s.pdf",timeset_nonstacks );
sprintf(text_title_pdf3, "Smearing_Study_PLOTS_%s.pdf)",timeset_nonstacks );
sprintf(text_title_pdf4, "Smearing_Study_PLOTS_%s",timeset_nonstacks );
std::string pdf_label = string(text_title_pdf4);

 //Hist_phyiscs_map MAP_stack =  Make_Physics_distribution_map_FromTFile(Playlist_ME1F_MC, "h_MuonCharge" , false, 1.0, kPlayListVector_MC[0], true );
 //Hist_phyiscs_map MAP_stack_G =  Make_Physics_distribution_map_FromTFile(Playlist_ME1G_MC, "h_MuonCharge" , false, 1.0, kPlayListVector_MC[1], true );



bool MakCVS=true;

  std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;

  std::cout<< "Printing Truth Varibles "<< std::endl;

  std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;

//Print Pie Figures
//  DrawPieFigures(MAP_stack_TRUTH ,  text_title_pdf4, can, mnv_plot, IsTruth,MakCVS,"MuonE");

Draw_MCHist_fromTFile(PlaylistMC_1F.TFILE_PLAYLIST,  "h_CryoVertex_X_RECO_smearing", text_title_pdf4,
"TRUE - RECO cryoX", "TRUE - RECO cryoX", "Nevents", false );

Draw_MCHist_WithErrorBands_fromTFile_andFIT(PlaylistMC_1F.TFILE_PLAYLIST,  "h_CryoVertex_X_RECO_smearing", text_title_pdf4, "CryoVertex X RECO smearing ",
"TRUE - RECO cryoX","NEvents");

Draw_TGraph_fit(PlaylistMC_1F.TFILE_PLAYLIST,  "h_CryoVertex_X_RECO_smearing", text_title_pdf4, "CryoVertex X RECO smearing ",
"TRUE - RECO cryoX","NEvents");

Draw_MCHist_WithErrorBands_fromTFile_andFIT(PlaylistMC_1F.TFILE_PLAYLIST,  "h_CryoVertex_X_RECO_TRUE_smearing", text_title_pdf4, "CryoVertex X RECO smearing ",
"TRUE - RECO cryoX","NEvents");

Draw_TGraph_fit(PlaylistMC_1F.TFILE_PLAYLIST,  "h_CryoVertex_X_RECO_TRUE_smearing", text_title_pdf4, "CryoVertex X RECO TRUE smearing ",
"TRUE - RECO cryoX","NEvents");


Draw_MCHist_fromTFile(PlaylistMC_1F.TFILE_PLAYLIST,  "h_CryoVertex_X_RECO_TRUE_smearing", text_title_pdf4,
"TRUE - RECO cryoX", "TRUE - RECO cryoX", "Nevents", false );


DrawSTACKfromHistFilio_FromTFileNoData(PlaylistMC_1F.TFILE_PLAYLIST, PlaylistMC_1G.TFILE_PLAYLIST,"h_X_RECO_smearing" ,
POT_MC_Status, POT_DATA_Status, "RECO smearing ", "True - RECO cyroX" ,pdf_label ,BinWithNorm_ON, "[GeV]",kCryoTankRegions , Dugbug_ON );

DrawSTACKfromHistFilio_FromTFileNoData(PlaylistMC_1F.TFILE_PLAYLIST, PlaylistMC_1G.TFILE_PLAYLIST,"h_X_TRUE_smearing" ,
POT_MC_Status, POT_DATA_Status, "TRUE smearing ", "True - RECO cyroX" ,pdf_label ,BinWithNorm_ON, "[GeV]",kCryoTankRegions , Dugbug_ON );



Draw_MCHist_fromTFile(PlaylistMC_1F.TFILE_PLAYLIST,  "h_CryoVertex_Y_RECO_smearing", text_title_pdf4,
"TRUE - RECO cryoY", "TRUE - RECO cryoY", "Nevents", false );

Draw_MCHist_WithErrorBands_fromTFile_andFIT(PlaylistMC_1F.TFILE_PLAYLIST,  "h_CryoVertex_Y_RECO_smearing", text_title_pdf4, "CryoVertex Y RECO smearing ",
"TRUE - RECO cryoY","NEvents");

Draw_TGraph_fit(PlaylistMC_1F.TFILE_PLAYLIST,  "h_CryoVertex_Y_RECO_smearing", text_title_pdf4, "CryoVertex Y RECO smearing ",
"TRUE - RECO cryoY","NEvents");


Draw_MCHist_fromTFile(PlaylistMC_1F.TFILE_PLAYLIST,  "h_CryoVertex_Y_RECO_TRUE_smearing", text_title_pdf4,
"TRUE - RECO cryoY", "TRUE - RECO cryoY", "Nevents", false );

DrawSTACKfromHistFilio_FromTFileNoData(PlaylistMC_1F.TFILE_PLAYLIST, PlaylistMC_1G.TFILE_PLAYLIST,"h_Y_RECO_smearing" ,
POT_MC_Status, POT_DATA_Status, "RECO smearing ", "True - RECO cyroY" ,pdf_label ,BinWithNorm_ON, "[GeV]",kCryoTankRegions , Dugbug_ON );

DrawSTACKfromHistFilio_FromTFileNoData(PlaylistMC_1F.TFILE_PLAYLIST, PlaylistMC_1G.TFILE_PLAYLIST,"h_Y_TRUE_smearing" ,
POT_MC_Status, POT_DATA_Status, "TRUE smearing ", "True - RECO cyroY" ,pdf_label ,BinWithNorm_ON, "[GeV]",kCryoTankRegions , Dugbug_ON );

///////////////

Draw_MCHist_fromTFile(PlaylistMC_1F.TFILE_PLAYLIST,  "h_CryoVertex_R_RECO_smearing", text_title_pdf4,
"TRUE - RECO cryoR", "TRUE - RECO cryoR", "Nevents", false );

Draw_MCHist_WithErrorBands_fromTFile_andFIT(PlaylistMC_1F.TFILE_PLAYLIST,  "h_CryoVertex_R_RECO_smearing", text_title_pdf4, "CryoVertex R RECO smearing ",
"TRUE - RECO cryoR","NEvents");

Draw_TGraph_fit(PlaylistMC_1F.TFILE_PLAYLIST,  "h_CryoVertex_R_RECO_smearing", text_title_pdf4, "CryoVertex R RECO smearing ",
"TRUE - RECO cryoR","NEvents");


Draw_MCHist_fromTFile(PlaylistMC_1F.TFILE_PLAYLIST,  "h_CryoVertex_R_RECO_TRUE_smearing", text_title_pdf4,
"TRUE - RECO cryoR", "TRUE - RECO cryoR", "Nevents", false );
//////////////////
Draw_MCHist_fromTFile(PlaylistMC_1F.TFILE_PLAYLIST,  "h_CryoVertex_Z_RECO_smearing", text_title_pdf4,
"TRUE - RECO cryoZ", "TRUE - RECO cryoZ", "Nevents", false );


Draw_MCHist_WithErrorBands_fromTFile_andFIT(PlaylistMC_1F.TFILE_PLAYLIST,  "h_CryoVertex_Z_RECO_smearing", text_title_pdf4, "CryoVertex Z RECO smearing ",
"TRUE - RECO cryoZ","NEvents");

Draw_TGraph_fit(PlaylistMC_1F.TFILE_PLAYLIST,  "h_CryoVertex_Z_RECO_smearing", text_title_pdf4, "CryoVertex Z RECO smearing ",
"TRUE - RECO cryoZ","NEvents");

Draw_MCHist_fromTFile(PlaylistMC_1F.TFILE_PLAYLIST,  "h_CryoVertex_Z_RECO_TRUE_smearing", text_title_pdf4,
"TRUE - RECO cryoZ", "TRUE - RECO cryoZ", "Nevents", false );

DrawSTACKfromHistFilio_FromTFileNoData(PlaylistMC_1F.TFILE_PLAYLIST, PlaylistMC_1G.TFILE_PLAYLIST,"h_Z_RECO_smearing" ,
POT_MC_Status, POT_DATA_Status, "RECO smearing ", "True - RECO cyroZ" ,pdf_label ,BinWithNorm_ON, "[GeV]",kCryoTankRegions , Dugbug_ON );

DrawSTACKfromHistFilio_FromTFileNoData(PlaylistMC_1F.TFILE_PLAYLIST, PlaylistMC_1G.TFILE_PLAYLIST,"h_Z_TRUE_smearing" ,
POT_MC_Status, POT_DATA_Status, "TRUE smearing ", "True - RECO cyroZ" ,pdf_label ,BinWithNorm_ON, "[GeV]",kCryoTankRegions , Dugbug_ON );

// Draw_MCHist_fromTFile_SMEARING(PlaylistMC_1F.TFILE_PLAYLIST,"h_CryoVertex_X","h_CryoVertex_X", pdf_label, "Smearing Universes with CV in the X Vertex","CryoVertx X [mm]","NEvents" );
//Draw_MCHist_fromTFile_SMEARING(PlaylistMC_1F.TFILE_PLAYLIST,"h_CryoVertex_Y","h_CryoVertex_Y", pdf_label, "Smearing Universes with CV in the Y Vertex","CryoVertx Y [mm]","NEvents" );
//Draw_MCHist_fromTFile_SMEARING(PlaylistMC_1F.TFILE_PLAYLIST,"h_CryoVertex_Z","h_CryoVertex_Z", pdf_label, "Smearing Universes with CV in the Z Vertex","CryoVertx Z [mm]","NEvents" );


Draw_MCHist_fromTFile_SMEARING(PlaylistMC_1F.TFILE_PLAYLIST,"h_CryoVertex_X", "h_CryoVertex_X_XYshifts", pdf_label, "Smearing XY Universes with CV in the X Vertex","CryoVertx X [mm]","NEvents" );
Draw_MCHist_fromTFile_SMEARING(PlaylistMC_1F.TFILE_PLAYLIST,"h_CryoVertex_Y", "h_CryoVertex_Y_XYshifts", pdf_label, "Smearing XY Universes with CV in the Y Vertex","CryoVertx Y [mm]","NEvents" );
Draw_MCHist_fromTFile_SMEARING(PlaylistMC_1F.TFILE_PLAYLIST,"h_CryoVertex_Z", "h_CryoVertex_Z_XYshifts", pdf_label, "Smearing XY Universes with CV in the Z Vertex","CryoVertx Z [mm]","NEvents" );

Draw_MCHist_fromTFile_SMEARING(PlaylistMC_1F.TFILE_PLAYLIST,"h_CryoVertex_X","h_CryoVertex_X_Zshifts", pdf_label, "Smearing Z Universes with CV in the X Vertex","CryoVertx X [mm]","NEvents" );
Draw_MCHist_fromTFile_SMEARING(PlaylistMC_1F.TFILE_PLAYLIST,"h_CryoVertex_Y","h_CryoVertex_Y_Zshifts", pdf_label, "Smearing Z Universes with CV in the Y Vertex","CryoVertx Y [mm]","NEvents" );
Draw_MCHist_fromTFile_SMEARING(PlaylistMC_1F.TFILE_PLAYLIST,"h_CryoVertex_Z","h_CryoVertex_Z_Zshifts", pdf_label, "Smearing Z Universes with CV in the Z Vertex","CryoVertx Z [mm]","NEvents" );


//Draw_MCHist_withErrorSys_fromTFile(PlaylistMC_1F.TFILE_PLAYLIST,  "h_MuonE", pdf_label, "Reco Muon E 4 Universe Smearing", "E_{#mu} [GeV]","NEvents", false);
//Draw_MCHist_withErrorSys_fromTFile(PlaylistMC_1F.TFILE_PLAYLIST,  "h_MuonPZ", pdf_label, "Reco Muno P_{#parallel} 4 Universe Smearing", "P_{#parallel} [GeV]","NEvents", false);
//Draw_MCHist_withErrorSys_fromTFile(PlaylistMC_1F.TFILE_PLAYLIST,  "h_MuonPT", pdf_label, "Reco Muon P_{T} 4 Universe Smearing", "P_{T} [GeV]","NEvents", false);
//Draw_MCHist_withErrorSys_fromTFile(PlaylistMC_1F.TFILE_PLAYLIST,  "h_MuonTheta", pdf_label, "Reco Muon #theta 4 Universe Smearing", "#theta_{#mu} (WRTB) [Degs]","NEvents", false);

Draw_MCHist_withErrorSys_fromTFile(PlaylistMC_1F_error.TFILE_PLAYLIST,  "h_MuonE", pdf_label, "Reco Muon E 4 Universe Smearing [ME1F]", "E_{#mu} [GeV]","NEvents", false);
Draw_MCHist_withErrorSys_fromTFile(PlaylistMC_1F_error.TFILE_PLAYLIST,  "h_MuonPZ", pdf_label, "Reco Muno P_{#parallel} 4 Universe Smearing [ME1F]", "P_{#parallel} [GeV]","NEvents", false);
Draw_MCHist_withErrorSys_fromTFile(PlaylistMC_1F_error.TFILE_PLAYLIST,  "h_MuonPT", pdf_label, "Reco Muon P_{T} 4 Universe Smearing", "P_{T} [GeV] [ME1F]","NEvents", false);
Draw_MCHist_withErrorSys_fromTFile(PlaylistMC_1F_error.TFILE_PLAYLIST,  "h_MuonTheta", pdf_label, "Reco Muon #theta 4 Universe Smearing [ME1F]", "#theta_{#mu} (WRTB) [Degs]","NEvents", false);

//Draw_MCHist_withErrorSys_fromTFile(PlaylistMC_1G_error.TFILE_PLAYLIST,  "h_MuonE", pdf_label, "Reco Muon E 4 Universe Smearing", "E_{#mu} [GeV]","NEvents", false);
//Draw_MCHist_withErrorSys_fromTFile(PlaylistMC_1G_error.TFILE_PLAYLIST,  "h_MuonPZ", pdf_label, "Reco Muno P_{#parallel} 4 Universe Smearing", "P_{#parallel} [GeV]","NEvents", false);
//Draw_MCHist_withErrorSys_fromTFile(PlaylistMC_1G_error.TFILE_PLAYLIST,  "h_MuonPT", pdf_label, "Reco Muon P_{T} 4 Universe Smearing", "P_{T} [GeV]","NEvents", false);
//Draw_MCHist_withErrorSys_fromTFile(PlaylistMC_1G_error.TFILE_PLAYLIST,  "h_MuonTheta", pdf_label, "Reco Muon #theta 4 Universe Smearing", "#theta_{#mu} (WRTB) [Degs]","NEvents", false);



Draw_MCHist_withErrorSys_fromTFile(PlaylistMC_1F.TFILE_PLAYLIST,PlaylistMC_1G.TFILE_PLAYLIST,  "h_MuonE",
POT_MC_Status, POT_DATA_Status, pdf_label,"Reco Muon E 4 Universe Smearing" , "E_{#mu} [GeV]","NEvents",
BinWithNorm_ON );

Draw_MCHist_withErrorSys_fromTFile(PlaylistMC_1F.TFILE_PLAYLIST,PlaylistMC_1G.TFILE_PLAYLIST,  "h_MuonPT",
POT_MC_Status, POT_DATA_Status, pdf_label,"Reco Muon P_{T} 4 Universe Smearing" , "P_{T} [GeV]","NEvents",
BinWithNorm_ON );

Draw_MCHist_withErrorSys_fromTFile(PlaylistMC_1F.TFILE_PLAYLIST,PlaylistMC_1G.TFILE_PLAYLIST,  "h_MuonPZ",
POT_MC_Status, POT_DATA_Status, pdf_label,"Reco Muon P_{#parallel} 4 Universe Smearing" , "P_{#parallel} [GeV]","NEvents",
BinWithNorm_ON );

Draw_MCHist_withErrorSys_fromTFile(PlaylistMC_1F.TFILE_PLAYLIST,PlaylistMC_1G.TFILE_PLAYLIST,  "h_MuonTheta",
POT_MC_Status, POT_DATA_Status, pdf_label,"Reco Muon #theta 4 Universe Smearing" , "#theta_{#mu} (WRTB) [Degs]","NEvents",
BinWithNorm_ON );


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
/*
Draw_DataHist_fromTFile(PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_SmearingCryoVertex_R", "1F","1G",
   pdf_label, "Vertex R [no fidical Cut]","Vertex R [mm]","NEvents", false, false, POT_DATA_Status );

Draw_DataHist_fromTFile(PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_SmearingCryoVertex_R", "1F","1G",
pdf_label, "Vertex R [no fidical Cut]","Vertex R [mm]","NEvents / Bin", true, false, POT_DATA_Status );


Draw_DataHist_fromTFile(PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_SmearingCryoVertex_R", "1F","1G",
   pdf_label, "Vertex R [no fidical Cut]","Vertex R [mm]","NEvents", false, true, POT_DATA_Status );

Draw_DataHist_fromTFile(PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_SmearingCryoVertex_R", "1F","1G",
pdf_label, "Vertex R [no fidical Cut]","Vertex R [mm]","NEvents / Bin", true, true, POT_DATA_Status );
*/

Draw_Data_RECO_TRUTH_Hist_fromTFile("h_CryoVertex_Z_TRUTH_upstream",
PlaylistMC_1F.TFILE_PLAYLIST,PlaylistMC_1G.TFILE_PLAYLIST,"h_CryoVertex_Z_upstream",
PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_CryoVertex_Z_upstream", "1F","1G",
pdf_label, "UpStream DATA EventRate Vertex Z","Distance to upstream Bulge [mm]","NEvents", false, false, POT_DATA_Status, POT_MC_Status );

Draw_Data_RECO_TRUTH_Hist_fromTFile("h_CryoVertex_Z_TRUTH_upstream",
PlaylistMC_1F.TFILE_PLAYLIST,PlaylistMC_1G.TFILE_PLAYLIST,"h_CryoVertex_Z_upstream",
PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_CryoVertex_Z_upstream", "1F","1G",
pdf_label, "UpStream DATA EventRate Vertex Z","Distance to upstream Bulge [mm]","NEvents / Bin", true, false, POT_DATA_Status, POT_MC_Status );
/*
Draw_Data_RECO_TRUTH_Hist_fromTFile_withConvolution("h_MC_TRUTH_Vertex_distance_upstream","h_MC_TRUTH_Vertex_distance_upstream_Convolution",
PlaylistMC_1F.TFILE_PLAYLIST,PlaylistMC_1G.TFILE_PLAYLIST,"h_MC_Vertex_distance_upstream",
PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_Vertex_distance_upstream", "1F","1G",
pdf_label, "Distance to UpStream Bulge Surface","Distance to upstream Bulge [mm]","NEvents", false, false, POT_DATA_Status, POT_MC_Status );
*/
Draw_Data_RECO_TRUTH_Hist_fromTFile_withConvolution("h_MC_TRUTH_Vertex_distance_upstream","h_MC_TRUTH_Vertex_distance_upstream_Convolution",
PlaylistMC_1F.TFILE_PLAYLIST,PlaylistMC_1G.TFILE_PLAYLIST,"h_MC_Vertex_distance_upstream",
PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_Vertex_distance_upstream", "1F","1G",
pdf_label, "Distance to UpStream Bulge Surface","Distance to upstream Bulge [mm]","NEvents / Bin", true, false, POT_DATA_Status, POT_MC_Status );

Draw_Data_RECO_TRUTH_Hist_fromTFile("h_CryoVertex_Z_TRUTH_downstream",
PlaylistMC_1F.TFILE_PLAYLIST,PlaylistMC_1G.TFILE_PLAYLIST,"h_CryoVertex_Z_downstream",
PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_CryoVertex_Z_downstream", "1F","1G",
pdf_label, "DownStream DATA EventRate Vertex Z","Distance to downstream Bulge [mm]","NEvents", false, false, POT_DATA_Status,POT_MC_Status );

Draw_Data_RECO_TRUTH_Hist_fromTFile("h_CryoVertex_Z_TRUTH_downstream",
PlaylistMC_1F.TFILE_PLAYLIST, PlaylistMC_1G.TFILE_PLAYLIST,"h_CryoVertex_Z_downstream",
PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_CryoVertex_Z_downstream", "1F","1G",
pdf_label, "DownStream DATA EventRate Vertex Z","Distance to downstream Bulge [mm]","NEvents / Bin", true, false, POT_DATA_Status,POT_MC_Status );

/*
Draw_Data_RECO_TRUTH_Hist_fromTFile_withConvolution("h_MC_TRUTH_Vertex_distance_downstream","h_MC_TRUTH_Vertex_distance_downstream_Convolution",
PlaylistMC_1F.TFILE_PLAYLIST,PlaylistMC_1G.TFILE_PLAYLIST,"h_MC_Vertex_distance_downstream",
PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_Vertex_distance_downstream", "1F","1G",
pdf_label, "Distance to DownStream Bulge Surface", "Distance to downstream Bulge [mm]","NEvents", false, false, POT_DATA_Status,POT_MC_Status );
*/
Draw_Data_RECO_TRUTH_Hist_fromTFile_withConvolution("h_MC_TRUTH_Vertex_distance_downstream","h_MC_TRUTH_Vertex_distance_downstream_Convolution",
PlaylistMC_1F.TFILE_PLAYLIST,PlaylistMC_1G.TFILE_PLAYLIST,"h_MC_Vertex_distance_downstream",
PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_Vertex_distance_downstream", "1F","1G",
pdf_label, "Distance to DownStream Bulge Surface", "Distance to downstream Bulge [mm]","NEvents / Bin", true, false, POT_DATA_Status,POT_MC_Status );


MakeCVS_from_hist(PlaylistDATA_1F.TFILE_PLAYLIST,  "h_Data_Vertex_distance_downstream", "h_Data_Vertex_distance_downstream_1G" );
MakeCVS_from_hist(PlaylistDATA_1F.TFILE_PLAYLIST,  "h_Data_Vertex_distance_upstream", "h_Data_Vertex_distance_upstream_1G" );




MakeCVS_from_HISTS("h_MC_TRUTH_Vertex_distance_downstream",
PlaylistMC_1F.TFILE_PLAYLIST,PlaylistMC_1G.TFILE_PLAYLIST,"h_MC_Vertex_distance_downstream",
PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_Vertex_distance_downstream", "1F","1G",
 "distance_downstream_Bulge",  "distance_downstream_Bulge", POT_DATA_Status,POT_MC_Status );


Draw_Data_RECO_TRUTH_Hist_fromTFile("h_CryoVertex_R_streaming_TRUTH_Center",
  PlaylistMC_1F.TFILE_PLAYLIST,PlaylistMC_1G.TFILE_PLAYLIST,"h_CryoVertex_R_streaming_Center",
PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_Smearing_Center_region_CryoVertex_R", "1F","1G",
   pdf_label, "EventRate[Center Region]","Vertex R [mm]","NEvents", false, false, POT_DATA_Status,POT_MC_Status );

Draw_Data_RECO_TRUTH_Hist_fromTFile("h_CryoVertex_R_streaming_TRUTH_Center",
  PlaylistMC_1F.TFILE_PLAYLIST,PlaylistMC_1G.TFILE_PLAYLIST,"h_CryoVertex_R_streaming_Center",
PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_Smearing_Center_region_CryoVertex_R", "1F","1G",
pdf_label,    "EventRate[Center Region]","Vertex R [mm]","NEvents / Bin", true, false, POT_DATA_Status,POT_MC_Status );

Draw_Data_RECO_TRUTH_Hist_fromTFile("h_CryoVertex_R_streaming_TRUTH_Center",
  PlaylistMC_1F.TFILE_PLAYLIST,PlaylistMC_1G.TFILE_PLAYLIST,"h_CryoVertex_R_streaming_Center",
PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_Smearing_Center_region_CryoVertex_R", "1F","1G",
   pdf_label, "EventRate[Center Region]","Vertex R [mm]","NEvents", false, true, POT_DATA_Status,POT_MC_Status );

Draw_Data_RECO_TRUTH_Hist_fromTFile("h_CryoVertex_R_streaming_TRUTH_Center",
  PlaylistMC_1F.TFILE_PLAYLIST, PlaylistMC_1G.TFILE_PLAYLIST,"h_CryoVertex_R_streaming_Center",
PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_Smearing_Center_region_CryoVertex_R", "1F","1G",
pdf_label,   "EventRate[Center Region]","Vertex R [mm]","NEvents / Bin", true, true, POT_DATA_Status,POT_MC_Status );

//RR

Draw_Data_RECO_TRUTH_Hist_fromTFile("h_CryoVertex_RR_streaming_TRUTH_Center",
  PlaylistMC_1F.TFILE_PLAYLIST,PlaylistMC_1G.TFILE_PLAYLIST,"h_CryoVertex_RR_streaming_Center",
PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_Smearing_Center_region_CryoVertex_RR", "1F","1G",
   pdf_label, "EventRate[Center Region]","Vertex R^{2} [mm]","NEvents", false, false, POT_DATA_Status,POT_MC_Status );

Draw_Data_RECO_TRUTH_Hist_fromTFile("h_CryoVertex_RR_streaming_TRUTH_Center",
  PlaylistMC_1F.TFILE_PLAYLIST,PlaylistMC_1G.TFILE_PLAYLIST,"h_CryoVertex_RR_streaming_Center",
PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_Smearing_Center_region_CryoVertex_RR", "1F","1G",
pdf_label,    "EventRate[Center Region]","Vertex R^{2} [mm]","NEvents / Bin", true, false, POT_DATA_Status,POT_MC_Status );

Draw_Data_RECO_TRUTH_Hist_fromTFile("h_CryoVertex_RR_streaming_TRUTH_Center",
  PlaylistMC_1F.TFILE_PLAYLIST,PlaylistMC_1G.TFILE_PLAYLIST,"h_CryoVertex_RR_streaming_Center",
PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_Smearing_Center_region_CryoVertex_RR", "1F","1G",
   pdf_label, "EventRate[Center Region]","Vertex R^{2} [mm]","NEvents", false, true, POT_DATA_Status,POT_MC_Status );

Draw_Data_RECO_TRUTH_Hist_fromTFile("h_CryoVertex_RR_streaming_TRUTH_Center",
  PlaylistMC_1F.TFILE_PLAYLIST, PlaylistMC_1G.TFILE_PLAYLIST,"h_CryoVertex_RR_streaming_Center",
PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_Smearing_Center_region_CryoVertex_RR", "1F","1G",
pdf_label,   "EventRate[Center Region]","Vertex R^{2} [mm]","NEvents / Bin", true, true, POT_DATA_Status,POT_MC_Status );


Draw_Data_RECO_TRUTH_Hist_fromTFile("h_CryoVertex_Z_Center_TRUTH",
  PlaylistMC_1F.TFILE_PLAYLIST,PlaylistMC_1G.TFILE_PLAYLIST,"h_CryoVertex_Z_Center",
PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_CryoVertex_Z_Center", "1F","1G",
   pdf_label, "EventRate[Center Region]","Vertex Z [mm]","NEvents", false, false, POT_DATA_Status,POT_MC_Status );

Draw_Data_RECO_TRUTH_Hist_fromTFile("h_CryoVertex_Z_Center_TRUTH",
  PlaylistMC_1F.TFILE_PLAYLIST,PlaylistMC_1G.TFILE_PLAYLIST,"h_CryoVertex_Z_Center",
PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_CryoVertex_Z_Center", "1F","1G",
pdf_label,    "EventRate[Center Region]","Vertex Z [mm]","NEvents / Bin", true, false, POT_DATA_Status,POT_MC_Status );

Draw_Data_RECO_TRUTH_Hist_fromTFile("h_CryoVertex_Z_Center_TRUTH",
  PlaylistMC_1F.TFILE_PLAYLIST,PlaylistMC_1G.TFILE_PLAYLIST,"h_CryoVertex_Z_Center",
PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_CryoVertex_Z_Center", "1F","1G",
   pdf_label, "EventRate[Center Region]","Vertex Z [mm]","NEvents", false, true, POT_DATA_Status,POT_MC_Status );

Draw_Data_RECO_TRUTH_Hist_fromTFile("h_CryoVertex_Z_Center_TRUTH",
  PlaylistMC_1F.TFILE_PLAYLIST, PlaylistMC_1G.TFILE_PLAYLIST,"h_CryoVertex_Z_Center",
PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_CryoVertex_Z_Center", "1F","1G",
pdf_label,   "EventRate[Center Region]","Vertex Z [mm]","NEvents / Bin", true, true, POT_DATA_Status,POT_MC_Status );







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


Playlist.push_back(kME1F);
//Playlist.push_back(kME1P);
  Playlist.push_back(kME1G);
  //Playlist.push_back(kME1A);
  //Playlist.push_back(kME1C);
  //Playlist.push_back(kME1D);

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
