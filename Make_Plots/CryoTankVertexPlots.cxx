#include "CryoTankVertexPlots.h"
//////////////////////////////////////////////////////////////////////////////
void MakeLatexForCryoVertexFiguresCVandALLErrors(std::string output_name ,std::vector<CryoVertex> CryoVertex_vector, std::string PDF_cv_name, int NError_Groups);
void MakeLatexForCryoVertexFiguresFORStacks(std::string output_name ,std::vector<CryoVertex> CryoVertex_vector ,  std::string pdf_name);
void Draw_MCRatio_FULL_EMPTY(TFile *inputFile_MCinputFULL, TFile *inputFile_MCinputEmpty, char *histoName_MC, double Scale_MC,
          int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf , std::string title_type,
           std::string Xaxis_title, ME_helium_Playlists FULL_playlist,ME_helium_Playlists Empty_playlist  );
void Draw_MC_Efficency_Pur_FULL_EMPTY(TFile *inputFile_MCinputFULL, TFile *inputFile_MCinputEmpty, char *histoName_helium, char *histoName_Other, double Scale_MC,
          const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf, std::string title_type, char * Xaxis_title, char *Yaxis_title,
          ME_helium_Playlists FULL_playlist, ME_helium_Playlists Empty_playlist,  bool MakeXaxisLOG, bool MakeYaxisLOG  );
void Kin(bool &cutsOn, bool &my_norm, bool &my_debug, const char *userDir, int &Print_Systematics ) {
TH1::AddDirectory(false);
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~       Starting Plotter: CryoVertex Plots         ~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::vector<ME_helium_Playlists> GetPlayListVector_MC();
std::vector<ME_helium_Playlists> GetPlayListVector_DATA();
const std::vector< ME_helium_Playlists> kPlayListVector_MC = GetPlayListVector_MC();
std::vector<ME_helium_Playlists> kPlayListVector_DATA =GetPlayListVector_DATA();
const std::vector<CryoVertex> kCryoVertexVaribles_vector = GetCryoVertexVaribles();
int N_Error_groups;
if(Print_Systematics==2 || Print_Systematics == 1) {N_Error_groups=0;}
else if (Print_Systematics==0){N_Error_groups=7;}
Pot_MapList POT_MC,POT_DATA;
Pot_MapStatusList POT_MC_Status, POT_DATA_Status;
TCanvas *can = new TCanvas("can");
MnvPlotter *mnv_plot = new MnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);


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
sprintf(timeset_nonstacks,"%i_%i_%i_%i_%s_%s", 1 + ltm->tm_mon,ltm->tm_mday, ltm->tm_hour,ltm->tm_min, SysError_printLabel.c_str(), Playlist_names.c_str());
sprintf(timeset, "%i_%i_%i_%i", 1 + ltm->tm_mon,ltm->tm_mday, ltm->tm_hour,ltm->tm_min);

sprintf(text_title_pdf1, "Plots_CryoVertex_SystErrors_%s.pdf(",timeset_nonstacks );
can -> Print(text_title_pdf1);
sprintf(text_title_pdf2, "Plots_CryoVertex_SystErrors_%s.pdf",timeset_nonstacks );
sprintf(text_title_pdf2, "Plots_CryoVertex_SystErrors_%s.pdf",timeset_nonstacks );
sprintf(text_title_pdf3, "Plots_CryoVertex_SystErrors_%s.pdf)",timeset_nonstacks );
sprintf(text_title_pdf4, "Plots_CryoVertex_SystErrors_%s",timeset_nonstacks );
//auto rootinputpathfile = "/minerva/app/users/cnguyen/cmtuser/Minerva_v21r1p1Helium/Ana/VetoWallStudies/scripts/ChainWrapper_FW_ME/eventselection/STACKS_Histograms_minervame1G_MC.root";
/*
auto minervame1P_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1P_MC.root";
auto minervame1A_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1A_MC.root";
auto minervame1D_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1D_MC.root";
auto minervame1C_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1C_MC.root";
auto minervame1F_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1F_MC.root";



auto minervame1P_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1P_Data.root";
auto minervame1A_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1A_Data.root";
auto minervame1C_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1C_Data.root";
auto minervame1D_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1D_Data.root";
auto minervame1F_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1F_Data.root";
*/

//auto PlaylistME_1D_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1D_MC_All_SysErrorsOn.root";
//auto PlaylistME_1A_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1A_MC_All_SysErrorsOn.root";


//auto PlaylistMC_1D_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1D_Data.root";
//auto PlaylistMC_1A_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1A_Data.root";
auto PlaylistME_1F_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1F_MC_All_SysErrorsOn.root";
//auto PlaylistME_1F_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1F_MC_StatsONLYErrors.root";
//auto PlaylistME_1A_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1A_MC_All_SysErrorsOn.root";
//auto PlaylistME_1G_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1G_MC_All_SysErrorsOn.root";
//auto PlaylistME_1G_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1G_MC_StatsONLYErrors.root";
auto PlaylistME_1G_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1G_MC_All_SysErrorsOn.root";


auto PlaylistMC_1F_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1F_Data.root";
//auto PlaylistMC_1D_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1D_Data.root";
//auto PlaylistMC_1A_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1A_Data.root";
auto PlaylistMC_1G_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1G_Data.root";



bool is_mc=true;bool isNOT_mc=false;

std::string  pdf_CV = string(text_title_pdf4);

//PlayList_INFO Playlist_MC_1G(kPlayListVector_MC[0], is_mc );


bool Stats_only = false;
PlayList_INFO PlaylistMC_1F(kPlayListVector_MC[0], true, Stats_only );
PlayList_INFO PlaylistMC_1G(kPlayListVector_MC[1], true, Stats_only );

PlaylistMC_1F.PRINTROOT_Path();
PlaylistMC_1G.PRINTROOT_Path();


POT_MC[kPlayListVector_MC[0]] = PlaylistMC_1F.Get_Pot();
POT_MC[kPlayListVector_MC[1]] = PlaylistMC_1G.Get_Pot();
POT_MC_Status[kFULL] = PlaylistMC_1F.Get_Pot();
POT_MC_Status[kEMPTY] = PlaylistMC_1G.Get_Pot();



std::cout<< "POT_MC_Status[kFULL] = "<< POT_MC_Status[kFULL]<<std::endl;
std::cout<< "POT_MC_Status[kEMPTY] = "<< POT_MC_Status[kEMPTY]<<std::endl;
std::vector <PlayList_INFO> MC_playlist;
MC_playlist.push_back(PlaylistMC_1F);
MC_playlist.push_back(PlaylistMC_1G);


PlayList_INFO PlaylistDATA_1F(kPlayListVector_DATA[0], isNOT_mc,false );
PlayList_INFO PlaylistDATA_1G(kPlayListVector_DATA[1], isNOT_mc,false );
std::vector <PlayList_INFO> Data_playlist;
Data_playlist.push_back(PlaylistDATA_1F);
Data_playlist.push_back(PlaylistDATA_1G);

POT_DATA[kPlayListVector_DATA[0]] = PlaylistDATA_1F.Get_Pot();
POT_DATA[kPlayListVector_DATA[1]] = PlaylistDATA_1G.Get_Pot();
POT_DATA_Status[kFULL] = PlaylistDATA_1F.Get_Pot();
POT_DATA_Status[kEMPTY] = PlaylistDATA_1G.Get_Pot();

TFile *Playlist_ME1F_MC     = new TFile(PlaylistME_1F_MC_path);
TFile *Playlist_ME1G_MC     = new TFile(PlaylistME_1G_MC_path);
TFile *Playlist_ME1F_DATA     = new TFile(PlaylistMC_1F_Data_path);
TFile *Playlist_ME1G_DATA     = new TFile(PlaylistMC_1G_Data_path);

std::cout<< "POT_DATA_Status[kFULL] = "<< POT_DATA_Status[kFULL]<<std::endl;
std::cout<< "POT_DATA_Status[kEMPTY] = "<< POT_DATA_Status[kEMPTY]<<std::endl;


for(auto Vertex_vertex: kCryoVertexVaribles_vector ){

  auto histname = GetVertexCryoVarHistName(Vertex_vertex);
  auto histname_data = GetVertexCryoVarHist_DATA_Name(Vertex_vertex);
  int n = histname.length();
  int n_data = histname_data.length();

  char histnameMC_char[n+1];
  char histnameDATA_char[n_data+1];

  strcpy( histnameMC_char,histname.c_str());
  strcpy( histnameDATA_char,histname_data.c_str());


  std::cout << " histname = "<< histname<<std::endl;
  std::cout << " histname_car = "<< histnameMC_char<<std::endl;
  std::cout << " histnameData = "<< histname_data<<std::endl;
  std::cout << " histname_car = "<< histnameDATA_char<<std::endl;

  auto TITLE = GetVertexCryoTitleName(Vertex_vertex);
  int n_TITLE = TITLE.length();
  char TITLE_char[n_TITLE+1];
  strcpy( TITLE_char,TITLE.c_str());


  DrawCVAndError_FromTFile(Playlist_ME1F_MC, Playlist_ME1G_MC,  histnameMC_char ,Playlist_ME1F_DATA,Playlist_ME1G_DATA,
    histnameDATA_char, POT_MC_Status, POT_DATA_Status, false, TITLE_char,
    GetVertexCryoVarAxisTitle(Vertex_vertex), pdf_CV, true, false ,"mm", Print_Systematics, my_debug, false, false);

}// end of for loop to print


// make Pie Graph showing the change of track types

Hist_phyiscs_map_withtrack Chisqrt_Physics_disturbtion_ME1F =  Make_Physics_withTrack_distribution_map_FromTFile(Playlist_ME1F_MC, "h_CryoVertexChiSqFit",false, 1.0, kPlayListVector_MC[0], true );

Hist_map_track Chisqrt_Physics_disturbtion_data_ME1F = Make_Track_distribution_map_FromTFile(Playlist_ME1F_DATA, "h_Data_CryoVertexChiSqFit" , false, 1.0,kPlayListVector_MC[0] , false , true );
Hist_map_track Chisqrt_Physics_disturbtion_data_ME1G = Make_Track_distribution_map_FromTFile(Playlist_ME1G_DATA, "h_Data_CryoVertexChiSqFit" , false, 1.0,kPlayListVector_MC[1] , false , true );
// greater than 10 chi
Hist_phyiscs_map_withtrack Chisqrtgreater10_Physics_disturbtion_ME1F =  Make_Physics_withTrack_distribution_map_FromTFile(Playlist_ME1F_MC, "h_CryoVertexChiSqFitgreater10",false, 1.0, kPlayListVector_MC[0], true );
Hist_map_track Chisqrtgreater10_Physics_disturbtion_data_ME1F = Make_Track_distribution_map_FromTFile(Playlist_ME1F_DATA, "h_Data_CryoVertexChiSqFitgreater10" , false, 1.0,kPlayListVector_MC[0] , false , true );
Hist_map_track Chisqrtgreater10_Physics_disturbtion_data_ME1G = Make_Track_distribution_map_FromTFile(Playlist_ME1G_DATA, "h_Data_CryoVertexChiSqFitgreater10" , false, 1.0,kPlayListVector_MC[1] , false , true );


Draw_TrackTypePieFigures(Chisqrt_Physics_disturbtion_data_ME1F,   text_title_pdf4, can, mnv_plot, false, true, "Data" , "No #chi^{2} Cuts" );
Draw_TrackTypePieFigures(Chisqrt_Physics_disturbtion_data_ME1G,   text_title_pdf4, can, mnv_plot, false, true, "Data" , "No #chi^{2} Cuts" );
DrawPieFigures_withTrackType(Chisqrt_Physics_disturbtion_ME1F,  text_title_pdf4, can, mnv_plot, true, true,    "RECO", "No #chi^{2} Cuts"  );

Draw_TrackTypePieFigures(Chisqrtgreater10_Physics_disturbtion_data_ME1F,   text_title_pdf4, can, mnv_plot, false, true, "Data" , "#chi^{2}>10 " );
Draw_TrackTypePieFigures(Chisqrtgreater10_Physics_disturbtion_data_ME1G,   text_title_pdf4, can, mnv_plot, false, true, "Data" , "#chi^{2}>10 " );
DrawPieFigures_withTrackType(Chisqrtgreater10_Physics_disturbtion_ME1F,  text_title_pdf4, can, mnv_plot, true, true, "Reco" , "#chi^{2}>10 " );


Draw_MCRatio_FULL_EMPTY(Playlist_ME1F_MC, Playlist_ME1G_MC, "h_CryoVertexChiSqFit", POT_MC_Status[kFULL]/POT_MC_Status[kEMPTY],
          0, "Cryo Vertex #Chi^{2} Fit", mnv_plot, can,text_title_pdf4, "title", "#Chi^{2}",
          kPlayListVector_MC[0], kPlayListVector_MC[1] );


Draw_MC_Efficency_Pur_FULL_EMPTY(Playlist_ME1F_MC, Playlist_ME1G_MC, "h_Efficiency_h_CryoVertexChiSqFit_0", "h_Efficiency_h_CryoVertexChiSqFit_1", POT_MC_Status[kFULL]/POT_MC_Status[kEMPTY],
                    "[All Track Types]", mnv_plot, can,text_title_pdf2 , "Vertex #Chi^{2}",  "#Chi^{2}", "Efficiency",
                    kPlayListVector_MC[0], kPlayListVector_MC[1], false, false  );

Draw_MC_Efficency_Pur_FULL_EMPTY(Playlist_ME1F_MC, Playlist_ME1G_MC, "h_Efficiency_h_CryoVertexChiSqFit_long_0", "h_Efficiency_h_CryoVertexChiSqFit_long_1", POT_MC_Status[kFULL]/POT_MC_Status[kEMPTY],
                                "[Long Tracks]", mnv_plot, can,text_title_pdf2 , "Vertex #Chi^{2}",  "#Chi^{2}", "Efficiency",
                                kPlayListVector_MC[0], kPlayListVector_MC[1], false, false  );

Draw_MC_Efficency_Pur_FULL_EMPTY(Playlist_ME1F_MC, Playlist_ME1G_MC, "h_Efficiency_h_CryoVertexChiSqFit_otherlong_0", "h_Efficiency_h_CryoVertexChiSqFit_otherlong_1", POT_MC_Status[kFULL]/POT_MC_Status[kEMPTY],
                                "[OtherLong Tracks]", mnv_plot, can,text_title_pdf2 , "Vertex #Chi^{2}",  "#Chi^{2}", "Efficiency",
                                kPlayListVector_MC[0], kPlayListVector_MC[1], false, false  );

Draw_MC_Efficency_Pur_FULL_EMPTY(Playlist_ME1F_MC, Playlist_ME1G_MC, "h_Efficiency_h_CryoVertexChiSqFit_short_0", "h_Efficiency_h_CryoVertexChiSqFit_short_1", POT_MC_Status[kFULL]/POT_MC_Status[kEMPTY],
                                "[Short Tracks]", mnv_plot, can,text_title_pdf2 , "Vertex #Chi^{2}",  "#Chi^{2}", "Efficiency",
                                kPlayListVector_MC[0], kPlayListVector_MC[1], false, false  );


sprintf(Latex_name, "PLOTS_%s_Latex_CryoVertex_CV_ERRORS", timeset_nonstacks);
std::string input_Latex_name = Latex_name;
MakeLatexForCryoVertexFiguresCVandALLErrors(input_Latex_name, kCryoVertexVaribles_vector, pdf_CV, N_Error_groups);

TCanvas *can_stacks = new TCanvas("can_stacks");

std::cout<< " ~~~~~~~PLOTS_~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;

std::cout<< "  Muon Material Stacks "<< std::endl;

std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;
char text_title_Material_pdf5[2024];
char text_title_Material_pdf6[2024];
char text_title_Material_pdf7[2024];
char text_title_Material_pdf8[2024];

sprintf(text_title_Material_pdf5, "PLOTS_%s_STACKS_Material_CryoVertex_Varibles.pdf(",timeset );
can_stacks -> Print(text_title_Material_pdf5);
sprintf(text_title_Material_pdf6, "PLOTS_%s_STACKS_Material_CryoVertex_Varibles.pdf",timeset );
sprintf(text_title_Material_pdf7, "PLOTS_%s_STACKS_Material_CryoVertex_Varibles.pdf)",timeset );
sprintf(text_title_Material_pdf8, "PLOTS_%s_STACKS_Material_CryoVertex_Varibles",timeset );
std::string pdf_stacks_Material = string(text_title_Material_pdf8);

/*
for(auto CryoVertex_vector: kCryoVertexVaribles_vector ){


 auto histname = GetVertexCryoVarHistName(CryoVertex_vector);
 int n = histname.length();
 char histnameMC_char[n+1];
 strcpy( histnameMC_char,histname.c_str());

 auto histname_data = GetVertexCryoVarHist_DATA_Name(CryoVertex_vector);
 int n_data = histname_data.length();
 char histnameDATA_char[n_data+1];
 strcpy( histnameDATA_char ,histname_data.c_str());

       auto TITLE = GetVertexCryoTitleName(CryoVertex_vector);
       int n_TITLE = TITLE.length();
       char TITLE_char[n_TITLE+1];
       strcpy( TITLE_char,TITLE.c_str());


    DrawSTACKfromHistFilio_FromTFile(Playlist_ME1F_MC, Playlist_ME1G_MC,  histnameMC_char ,Playlist_ME1F_DATA,Playlist_ME1G_DATA,
     histnameDATA_char, POT_MC_Status, POT_DATA_Status, false, TITLE_char,
     GetVertexCryoVarAxisTitle(CryoVertex_vector), pdf_stacks_Material, true, false ,"mm", kMaterial, my_debug );

}


can_stacks -> Print(text_title_Material_pdf7);
sprintf(Latex_name, "PLOTS_%s_CryoVertex_Latex_stack_Material", timeset);
 input_Latex_name = Latex_name;

MakeLatexForCryoVertexFiguresFORStacks(input_Latex_name ,kCryoVertexVaribles_vector , pdf_stacks_Material );

std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;

std::cout<< "  Muon Interaction Stacks "<< std::endl;

std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;
char text_title_Interaction_pdf5[2024];
char text_title_Interaction_pdf6[2024];
char text_title_Interaction_pdf7[2024];
char text_title_Interaction_pdf8[2024];

sprintf(text_title_Interaction_pdf5, "PLOTS_%s_STACKS_Interaction_CryoVertex_Varibles.pdf(",timeset );
can_stacks -> Print(text_title_Interaction_pdf5);
sprintf(text_title_Interaction_pdf6, "PLOTS_%s_STACKS_Interaction_CryoVertex_Varibles.pdf",timeset );
sprintf(text_title_Interaction_pdf7, "PLOTS_%s_STACKS_Interaction_CryoVertex_Varibles.pdf)",timeset );
sprintf(text_title_Interaction_pdf8, "PLOTS_%s_STACKS_Interaction_CryoVertex_Varibles",timeset );
std::string pdf_stacks_interaction = string(text_title_Interaction_pdf8);


for(auto CryoVertex_vector: kCryoVertexVaribles_vector ){


  auto histname = GetVertexCryoVarHistName(CryoVertex_vector);
  int n = histname.length();
  char histnameMC_char[n+1];
  strcpy( histnameMC_char,histname.c_str());

  auto histname_data = GetVertexCryoVarHist_DATA_Name(CryoVertex_vector);
  int n_data = histname_data.length();
  char histnameDATA_char[n_data+1];
  strcpy( histnameDATA_char ,histname_data.c_str());

        auto TITLE = GetVertexCryoTitleName(CryoVertex_vector);
        int n_TITLE = TITLE.length();
        char TITLE_char[n_TITLE+1];
        strcpy( TITLE_char,TITLE.c_str());


     DrawSTACKfromHistFilio_FromTFile(Playlist_ME1F_MC, Playlist_ME1G_MC,  histnameMC_char ,Playlist_ME1F_DATA,Playlist_ME1G_DATA,
      histnameDATA_char, POT_MC_Status, POT_DATA_Status, false, TITLE_char,
      GetVertexCryoVarAxisTitle(CryoVertex_vector), pdf_stacks_interaction, true, false ,"mm", kInteraction, my_debug );



}


 can_stacks -> Print(text_title_Interaction_pdf7);
 sprintf(Latex_name, "PLOTS_%s_CryoVertex_Latex_stack_Interaction", timeset);
 input_Latex_name = Latex_name;
 MakeLatexForCryoVertexFiguresFORStacks(input_Latex_name ,kCryoVertexVaribles_vector , pdf_stacks_interaction );

 std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;

 std::cout<< "  Muon Particle Stacks "<< std::endl;

 std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;
 char text_title_Particle_pdf5[2024];
 char text_title_Particle_pdf6[2024];
 char text_title_Particle_pdf7[2024];
 char text_title_Particle_pdf8[2024];

 sprintf(text_title_Particle_pdf5, "PLOTS_%s_STACKS_Particle_CryoVertex_Varibles.pdf(",timeset );
 can_stacks -> Print(text_title_Particle_pdf5);
 sprintf(text_title_Particle_pdf6, "PLOTS_%s_STACKS_Particle_CryoVertex_Varibles.pdf",timeset );
 sprintf(text_title_Particle_pdf7, "PLOTS_%s_STACKS_Particle_CryoVertex_Varibles.pdf)",timeset );
 sprintf(text_title_Particle_pdf8, "PLOTS_%s_STACKS_Particle_CryoVertex_Varibles",timeset );
 std::string pdf_stacks_Particle = string(text_title_Particle_pdf8);


 for(auto CryoVertex_vector: kCryoVertexVaribles_vector ){


   auto histname = GetVertexCryoVarHistName(CryoVertex_vector);
   int n = histname.length();
   char histnameMC_char[n+1];
   strcpy( histnameMC_char,histname.c_str());

   auto histname_data = GetVertexCryoVarHist_DATA_Name(CryoVertex_vector);
   int n_data = histname_data.length();
   char histnameDATA_char[n_data+1];
   strcpy( histnameDATA_char ,histname_data.c_str());

         auto TITLE = GetVertexCryoTitleName(CryoVertex_vector);
         int n_TITLE = TITLE.length();
         char TITLE_char[n_TITLE+1];
         strcpy( TITLE_char,TITLE.c_str());


      DrawSTACKfromHistFilio_FromTFile(Playlist_ME1F_MC, Playlist_ME1G_MC,  histnameMC_char ,Playlist_ME1F_DATA,Playlist_ME1G_DATA,
       histnameDATA_char, POT_MC_Status, POT_DATA_Status, false, TITLE_char,
       GetVertexCryoVarAxisTitle(CryoVertex_vector), pdf_stacks_Particle, true, false ,"mm", kParticle, my_debug );



 }


  can_stacks -> Print(text_title_Particle_pdf7);
sprintf(Latex_name, "PLOTS_%s_CryoVertex_Latex_stack_Particle", timeset);
  input_Latex_name = Latex_name;
  MakeLatexForCryoVertexFiguresFORStacks(input_Latex_name ,kCryoVertexVaribles_vector , pdf_stacks_Particle );
*/
std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;

std::cout<< " Done with CryoVertex Tanks  "<< std::endl;

std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;

std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;

std::cout<< "  Type type Stacks "<< std::endl;

std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;
char text_title_Tracktype_pdf5[2024];
char text_title_Tracktype_pdf6[2024];
char text_title_Tracktype_pdf7[2024];
char text_title_Tracktype_pdf8[2024];

sprintf(text_title_Tracktype_pdf5, "PLOTS_%s_STACKS_TrackType_CryoVertex_Varibles.pdf(",timeset );
can_stacks -> Print(text_title_Tracktype_pdf5);
sprintf(text_title_Tracktype_pdf6, "PLOTS_%s_STACKS_TrackType_CryoVertex_Varibles.pdf",timeset );
sprintf(text_title_Tracktype_pdf7, "PLOTS_%s_STACKS_TrackType_CryoVertex_Varibles.pdf)",timeset );
sprintf(text_title_Tracktype_pdf8, "PLOTS_%s_STACKS_TrackType_CryoVertex_Varibles",timeset );
std::string pdf_stacks_Tracktype = string(text_title_Tracktype_pdf8);

std::vector<StackType> allStacks;
allStacks.push_back(kTrackType);
allStacks.push_back(kVertexOptions);
allStacks.push_back(kboolNTrack);

for(auto stack_index : allStacks){

for(auto CryoVertex_vector: kCryoVertexVaribles_vector ){


  auto histname = GetVertexCryoVarHistName(CryoVertex_vector);
  int n = histname.length();
  char histnameMC_char[n+1];
  strcpy( histnameMC_char,histname.c_str());

  auto histname_data = GetVertexCryoVarHist_DATA_Name(CryoVertex_vector);
  int n_data = histname_data.length();
  char histnameDATA_char[n_data+1];
  strcpy( histnameDATA_char ,histname_data.c_str());

        auto TITLE = GetVertexCryoTitleName(CryoVertex_vector);
        std::string TITLE_data = "[DATA Only]" + TITLE;
        char TITLE_char[TITLE.length()+1];
        strcpy( TITLE_char,TITLE.c_str());

        char TITLE_data_char[TITLE_data.length()+1];
        strcpy( TITLE_data_char,TITLE_data.c_str());



     DrawSTACKfromHistFilio_FromTFile(Playlist_ME1F_MC, Playlist_ME1G_MC,  histnameMC_char ,Playlist_ME1F_DATA,Playlist_ME1G_DATA,
      histnameDATA_char, POT_MC_Status, POT_DATA_Status, false, TITLE_char,
      GetVertexCryoVarAxisTitle(CryoVertex_vector), pdf_stacks_Tracktype, true, false ,"mm", stack_index, my_debug );


      DrawSTACK_FORDATAONLY_fromHistFilio_FromTFile( Playlist_ME1F_DATA,Playlist_ME1G_DATA , histnameDATA_char,  POT_DATA_Status, false, TITLE_data_char,
      GetVertexCryoVarAxisTitle(CryoVertex_vector), pdf_stacks_Tracktype, true ,"mm", stack_index, my_debug);

}

}





can_stacks -> Print(text_title_Tracktype_pdf7);




sprintf(Latex_name, "PLOTS_%s_CryoVertex_Latex_CV_and_Stacks", timeset);
input_Latex_name = Latex_name;

//MakeLatexForMuonFiguresCVandGroupErrors_andALLSTACKS(Print_Systematics ,input_Latex_name,
 // kCryoVertexVaribles_vector, pdf_CV, pdf_stacks_Material, pdf_stacks_interaction,
 // pdf_stacks_Particle, N_Error_groups);


  std::cout << std::endl;
  std::cout << "Done WITH Stacks" << std::endl;

   can -> Print(text_title_pdf3);

}


//End of MainFuntion
///////////////////////////////////

/////////////////////////////////////////////
//Main Function
/////////////////////////////////////////////

 int main() {

bool cutsOn= true;
std::cout << "Run over cutsOn?  (0 = false, 1 = true) " << std::endl;
//std::cin >> cutsOn;
std::cout << std::boolalpha << cutsOn << std::endl;

bool my_norm = true;
std::cout << "Which Normalization?  (0 = POT, 1 = relative equal areas) " << std::endl;
//std::cin >> my_norm;
std::cout << std::boolalpha << my_norm << std::endl;

bool my_debug= true;
std::cout << "Run in Debug Mode? (0 = NO, 1 = YES) " << std::endl;
//std::cin >> my_debug;
std::cout << std::boolalpha << my_debug << std::endl;

int my_Print_Systmatics;
std::cout << "Print Error Systmatics?  [ 0 = Total and Groups Systemtics Errors ,  1 = Total Systematic Errors , 2 = none ]" << std::endl;
std::cin >> my_Print_Systmatics;
std::cout << "Pitched: " << my_Print_Systmatics << std::endl;


std::string input = "cnguyen";
std::cout << "What is the name of the user? " << std::endl;
//std::cin >> input;
std::cout << input << std::endl;

const char *inputFileLoc = input.c_str();

Kin(cutsOn, my_norm, my_debug, inputFileLoc, my_Print_Systmatics);

return 0;

}


std::vector<ME_helium_Playlists> GetPlayListVector_MC() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ME_helium_Playlists> Playlist;
  //Playlist.push_back(kME1D);
  //Playlist.push_back(kME1A);
  //Playlist.push_back(kME1G);
  //Playlist.push_back(kME1P);

  //Playlist.push_back(kME1C);

  //Playlist.push_back(kME1F);

  Playlist.push_back(kME1F);
  Playlist.push_back(kME1G);
  return Playlist;
//#endif
}


std::vector<ME_helium_Playlists> GetPlayListVector_DATA() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ME_helium_Playlists> Playlist;

//Playlist.push_back(kME1D);
//Playlist.push_back(kME1A);
  //Playlist.push_back(kME1G);
  //Playlist.push_back(kME1P);

  //Playlist.push_back(kME1C);

  Playlist.push_back(kME1F);
  Playlist.push_back(kME1G);
  return Playlist;
//#endif
}
//////////////////////////////////////////////////////////////////////////
//GET Vertex Varibles
//////////////////////////////////////////////////////////////////////////
std::vector<CryoVertex> GetCryoVertexVaribles() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<CryoVertex> CryoVertexVars;

  CryoVertexVars.push_back(kX);
  CryoVertexVars.push_back(kY);
  CryoVertexVars.push_back(kZ);
  CryoVertexVars.push_back(kR);
  CryoVertexVars.push_back(kfitConverge);


  return CryoVertexVars;
//#endif
}


void MakeLatexForCryoVertexFiguresCVandALLErrors(std::string output_name ,std::vector<CryoVertex> CryoVertex_vector, std::string PDF_cv_name, int NError_Groups){
  double scale= .24;
  std::ofstream myfile;

  const int  Column_Spacing = NError_Groups + 2;

 std::string fileName = output_name + ".txt";
  myfile.open(fileName,	std::ios::trunc);
  std::cout<<"Name of Output File "<< fileName<<std::endl;
  LatexFormat CryoVertex_latex_Latex(scale);

  int pageCount = 2;


  for(auto cat:CryoVertex_vector){

    auto input_vectors = GetBinvertexVector(cat);
    std::string Var_name = GetVertexCryoTitleName(cat);
    std::string Units_name = "mm";

    myfile<<"\n";
    myfile<<CryoVertex_latex_Latex.GetSubSection(Var_name);
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%%  Frame CV and Error grounps For  "<< Var_name <<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<CryoVertex_latex_Latex.GetBeginFrame(Var_name)<< "\n";
    myfile<<CryoVertex_latex_Latex.GetBeginTabular()<< "\n";
    myfile<<CryoVertex_latex_Latex.GetInclude_figure(pageCount,PDF_cv_name)<< "\n";
    myfile<<"& \n";
    myfile<<CryoVertex_latex_Latex.GetInclude_figure(pageCount + Column_Spacing,PDF_cv_name)<< "\n";
    myfile<<"& \n";
    myfile<<CryoVertex_latex_Latex.GetInclude_figure(pageCount + Column_Spacing+ Column_Spacing, PDF_cv_name)<< "\n";
    myfile<<CryoVertex_latex_Latex.GetEndTabular()<< "\n";
    if(input_vectors.size() < 25)
    {
      myfile<<CryoVertex_latex_Latex.BinningLatexString(input_vectors, Var_name , Units_name )<< "\n";
    }
    myfile<<CryoVertex_latex_Latex.GetEndFrame();
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% END FRAME Frame CV and Error groups "<< Var_name<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";

    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%%  Full Error group  "<< Var_name <<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<CryoVertex_latex_Latex.GetBeginFrame(Var_name)<< "\n";
    myfile<<CryoVertex_latex_Latex.GetBeginTabular()<< "\n";
    myfile<<CryoVertex_latex_Latex.GetInclude_figure(pageCount + 1, PDF_cv_name)<< "\n";
    myfile<<"& \n";
    myfile<<CryoVertex_latex_Latex.GetInclude_figure(pageCount + Column_Spacing + 1, PDF_cv_name )<< "\n";
    myfile<<"& \n";
    myfile<<CryoVertex_latex_Latex.GetInclude_figure(pageCount +  Column_Spacing +  Column_Spacing + 1, PDF_cv_name )<< "\n";
    myfile<<CryoVertex_latex_Latex.GetEndTabular()<< "\n";
    myfile<<CryoVertex_latex_Latex.GetEndFrame();
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
        myfile<<CryoVertex_latex_Latex.GetBeginFrame(Var_name)<< "\n";
        myfile<<CryoVertex_latex_Latex.GetBeginTabular()<< "\n";
        myfile<<CryoVertex_latex_Latex.GetInclude_figure(pageCount + i + 2,PDF_cv_name)<< "\n";
        myfile<<"& \n";
        myfile<<CryoVertex_latex_Latex.GetInclude_figure(pageCount + Column_Spacing + i + 2 ,PDF_cv_name)<< "\n";
        myfile<<"& \n";
        myfile<<CryoVertex_latex_Latex.GetInclude_figure(pageCount +  Column_Spacing + Column_Spacing + i + 2,PDF_cv_name)<< "\n";
        myfile<<CryoVertex_latex_Latex.GetEndTabular()<< "\n";
        myfile<<CryoVertex_latex_Latex.GetEndFrame();
        myfile<<"\n";
        myfile<<"%%%%%%%%%%%%%%%%% \n";
        myfile<<"%%% END FRAME Error groups "<< Var_name<<"\n";
        myfile<<"%%%%%%%%%%%%%%%%% \n";
      }

    }




    pageCount= pageCount +  Column_Spacing +  Column_Spacing + Column_Spacing;
  }


  myfile.close();

}//end of




void MakeLatexForCryoVertexFiguresFORStacks(std::string output_name ,std::vector<CryoVertex> CryoVertex_vector ,  std::string pdf_name){
  double scale= .23;
  std::ofstream myfile;
 std::string fileName = output_name + ".txt";
  myfile.open(fileName,	std::ios::trunc);
  std::cout<<"Name of Output File "<< fileName<<std::endl;
  LatexFormat CryoVertex_latex_Latex(scale);

  int pageCount = 2;
  std::cout << " Name of input PDF = "<< pdf_name << std::endl;

  for(auto cat:CryoVertex_vector){

    auto input_vectors = GetBinvertexVector(cat);
    std::string Var_name = GetVertexCryoTitleName(cat);
    std::string Units_name = "mm";
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%%  Frame Stack For  "<< Var_name <<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<CryoVertex_latex_Latex.GetBeginFrame(Var_name)<< "\n";
    myfile<<CryoVertex_latex_Latex.GetBeginTabular()<< "\n";
    myfile<<CryoVertex_latex_Latex.GetInclude_figure(pageCount,pdf_name)<< "\n";
    myfile<<"& \n";
    myfile<<CryoVertex_latex_Latex.GetInclude_figure(pageCount+1,pdf_name)<< "\n";
    myfile<<"& \n";
    myfile<<CryoVertex_latex_Latex.GetInclude_figure(pageCount+2,pdf_name)<< "\n";
    myfile<<CryoVertex_latex_Latex.GetEndTabular()<< "\n";
    if(input_vectors.size() < 25)
    {
      myfile<<CryoVertex_latex_Latex.BinningLatexString(input_vectors, Var_name , Units_name )<< "\n";
    }
    myfile<<CryoVertex_latex_Latex.GetEndFrame();
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% END FRAME Stack "<< Var_name<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";

    pageCount= pageCount + 3;
  }


  myfile.close();
}//end of Function




void Draw_MCRatio_FULL_EMPTY(TFile *inputFile_MCinputFULL, TFile *inputFile_MCinputEmpty, char *histoName_MC, double Scale_MC,
          int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf, std::string title_type, std::string Xaxis_title,
          ME_helium_Playlists FULL_playlist, ME_helium_Playlists Empty_playlist  ){

      char histoName_TRUE[1024];
      char histoName_TRUE_RECO[1024];
      char Title_His[1024];

      sprintf(histoName_TRUE, "%s_TRUE", histoName_MC);
      sprintf(histoName_TRUE_RECO, "%s_TRUE_RECO", histoName_MC);

      MnvH1D *hist_TRUE_FULL = (MnvH1D*)inputFile_MCinputFULL -> Get(histoName_TRUE);
      MnvH1D *hist_TRUE_RECO_FULL = (MnvH1D*)inputFile_MCinputFULL -> Get(histoName_TRUE_RECO);
      MnvH1D *hist_TRUE_EMPTY = (MnvH1D*)inputFile_MCinputEmpty -> Get(histoName_TRUE);
      MnvH1D *hist_TRUE_RECO_EMPTY = (MnvH1D*)inputFile_MCinputEmpty -> Get(histoName_TRUE_RECO);

      MnvH1D* hist_TRUE_FULL_clone = (MnvH1D*)inputFile_MCinputFULL -> Get(histoName_TRUE);
      MnvH1D* hist_TRUE_RECO_FULL_clone = (MnvH1D*)inputFile_MCinputFULL -> Get(histoName_TRUE_RECO);
      MnvH1D* hist_TRUE_EMPTY_clone = (MnvH1D*)inputFile_MCinputEmpty -> Get(histoName_TRUE);
      MnvH1D* hist_TRUE_RECO_EMPTY_clone = (MnvH1D*)inputFile_MCinputEmpty -> Get(histoName_TRUE_RECO);

      ///Calculation FOR FINAL Eff
      hist_TRUE_EMPTY_clone->Scale(Scale_MC);
      hist_TRUE_RECO_EMPTY_clone->Scale(Scale_MC);
      hist_TRUE_FULL_clone->Add(hist_TRUE_EMPTY_clone,-1);
      hist_TRUE_RECO_FULL_clone->Add(hist_TRUE_RECO_EMPTY_clone,-1);
      hist_TRUE_RECO_FULL_clone->Divide(hist_TRUE_RECO_FULL_clone, hist_TRUE_FULL_clone, 1.0,1.0,"");

      std::string playlistFull =   GetPlaylist_InitialName(FULL_playlist); //FULL_playlist.GetPlaylistName();
      std::string playlistEmpty = GetPlaylist_InitialName(Empty_playlist); //EMPTY_playlist.GetPlaylistName();

      char title_type_char[title_type.length()+1];
      strcpy( title_type_char, title_type.c_str());

      char playlistFull_char[playlistFull.length()+1];
      strcpy( playlistFull_char, playlistFull.c_str());

      char playlistEmpty_char[ playlistEmpty.length()+1];
      strcpy( playlistEmpty_char,  playlistEmpty.c_str());

      sprintf(Title_His, "%s (%s) (True) (%s)(F) ", title_type_char,title,playlistFull_char);
      DrawCVAndError_FromTFile(inputFile_MCinputFULL, histoName_TRUE, Title_His  , Xaxis_title, pdf );
      sprintf(Title_His, "%s (%s) (True+RECO) (%s)(F)", title_type_char,title,playlistFull_char);
      DrawCVAndError_FromTFile(inputFile_MCinputFULL, histoName_TRUE_RECO, Title_His , Xaxis_title, pdf );
      sprintf(Title_His, "%s (%s) (True) (%s)(E)", title_type_char,title,playlistEmpty_char);
      DrawCVAndError_FromTFile(inputFile_MCinputEmpty, histoName_TRUE,Title_His, Xaxis_title, pdf );
      sprintf(Title_His, "%s (%s) (True+RECO) (%s)(E)", title_type_char,title,playlistEmpty_char);
      DrawCVAndError_FromTFile(inputFile_MCinputEmpty, histoName_TRUE_RECO,  Title_His , Xaxis_title, pdf );


      hist_TRUE_RECO_FULL->Divide(hist_TRUE_RECO_FULL, hist_TRUE_FULL, 1.0,1.0,"");
      hist_TRUE_RECO_EMPTY->Divide(hist_TRUE_RECO_EMPTY, hist_TRUE_EMPTY, 1.0,1.0,"");

      sprintf(Title_His, "Eff(FULL) %s (%s)  (%s)(F) ", title_type_char,title,playlistFull_char);
      DrawCVAndError_FromHIST(hist_TRUE_RECO_FULL, Title_His ,Xaxis_title,"Efficiency", pdf,true);
      sprintf(Title_His, "Eff(Empty) %s (%s)  (%s)(E) ", title_type_char,title,playlistEmpty_char);
      DrawCVAndError_FromHIST(hist_TRUE_RECO_EMPTY, Title_His ,Xaxis_title,"Efficiency", pdf,true);

      sprintf(Title_His, "%s (%s) (%s-%s)", title_type_char,title,playlistFull_char,playlistEmpty_char);
      DrawCVAndError_FromHIST(hist_TRUE_RECO_FULL_clone, Title_His ,Xaxis_title,"Efficiency", pdf,true);

      DrawCVAndError_FromHIST(hist_TRUE_RECO_FULL_clone, Title_His ,Xaxis_title,"Efficiency", pdf,true,true);


}//endl;


void Draw_MC_Efficency_Pur_FULL_EMPTY(TFile *inputFile_MCinputFULL, TFile *inputFile_MCinputEmpty, char *histoName_helium, char *histoName_Other, double Scale_MC,
          const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf, std::string title_type,  char * Xaxis_title, char *Yaxis_title,
          ME_helium_Playlists FULL_playlist, ME_helium_Playlists Empty_playlist,  bool MakeXaxisLOG, bool MakeYaxisLOG  ){


      char Title_His[1024];
      MnvH1D *hist_Helium_FULL = (MnvH1D*)inputFile_MCinputFULL -> Get(histoName_helium);
      MnvH1D *hist_Other_FULL = (MnvH1D*)inputFile_MCinputFULL -> Get(histoName_Other);
      MnvH1D *hist_Helium_EMPTY = (MnvH1D*)inputFile_MCinputEmpty -> Get(histoName_helium);
      MnvH1D *hist_Other_EMPTY = (MnvH1D*)inputFile_MCinputEmpty -> Get(histoName_Other);

      MnvH1D* hist_Helium_clone = (MnvH1D*)inputFile_MCinputFULL -> Get(histoName_helium);
      MnvH1D* hist_Other_FULL_clone = (MnvH1D*)inputFile_MCinputFULL -> Get(histoName_Other);
      MnvH1D* hist_Helium_EMPTY_clone = (MnvH1D*)inputFile_MCinputEmpty -> Get(histoName_helium);
      MnvH1D* hist_Other_EMPTY_clone = (MnvH1D*)inputFile_MCinputEmpty -> Get(histoName_Other);

      ///Calculation FOR FINAL Eff
      hist_Helium_EMPTY_clone->Scale(Scale_MC);
      hist_Other_EMPTY_clone->Scale(Scale_MC);
      hist_Helium_clone->Add(hist_Helium_EMPTY_clone,-1);
      hist_Other_FULL_clone->Add(hist_Other_EMPTY_clone,-1);

      auto g_TGraph_Eff_Full = MakeForwardIntergrationEfficiency_TGraphError(hist_Helium_FULL);
      auto g_TGraph_pure_Full =MakeForwardIntergrationPurity_TGraphError(hist_Helium_FULL, hist_Other_FULL );
      auto g_TGraph_Eff_pure_Full =MakeForwardIntergrationEfficiency_times_Purity_TGraphError(hist_Helium_FULL, hist_Other_FULL );

      auto g_TGraph_Eff_Empty = MakeForwardIntergrationEfficiency_TGraphError(hist_Helium_EMPTY);
      auto g_TGraph_pure_Empty =MakeForwardIntergrationPurity_TGraphError(hist_Helium_EMPTY, hist_Other_EMPTY );
      auto g_TGraph_Eff_pure_Empty =MakeForwardIntergrationEfficiency_times_Purity_TGraphError(hist_Helium_FULL, hist_Other_EMPTY );

      auto g_TGraph_Eff_Full_Empty = MakeForwardIntergrationEfficiency_TGraphError(hist_Helium_clone);
      auto g_TGraph_pure_Full_Empty =MakeForwardIntergrationPurity_TGraphError(hist_Helium_clone, hist_Other_FULL_clone );
      auto g_TGraph_Eff_pure_Full_Empty =MakeForwardIntergrationEfficiency_times_Purity_TGraphError(hist_Helium_clone, hist_Other_FULL_clone );


      std::string playlistFull =   GetPlaylist_InitialName(FULL_playlist);
      std::string playlistEmpty = GetPlaylist_InitialName(Empty_playlist);

      char title_type_char[title_type.length()+1];
      strcpy( title_type_char, title_type.c_str());

      char playlistFull_char[playlistFull.length()+1];
      strcpy( playlistFull_char, playlistFull.c_str());

      char playlistEmpty_char[ playlistEmpty.length()+1];
      strcpy( playlistEmpty_char,  playlistEmpty.c_str());

      sprintf(Title_His, "%s (%s) (Reco True Helium) (%s)(F) ", title_type_char, title,playlistFull_char);
      DrawCVAndError_FromTFile(inputFile_MCinputFULL, histoName_helium, Title_His  , Xaxis_title, pdf );
      sprintf(Title_His, "%s (%s) (Reco True Other) (%s)(F)", title_type_char,title,playlistFull_char);
      DrawCVAndError_FromTFile(inputFile_MCinputFULL, histoName_Other, Title_His , Xaxis_title, pdf );
      sprintf(Title_His, "%s (%s) (Reco True Helium) (%s)(E)", title_type_char,title,playlistEmpty_char);
      DrawCVAndError_FromTFile(inputFile_MCinputEmpty, histoName_helium,Title_His, Xaxis_title, pdf );
      sprintf(Title_His, "%s (%s) (Reco True Other) (%s)(E)", title_type_char,title,playlistEmpty_char);
      DrawCVAndError_FromTFile(inputFile_MCinputEmpty, histoName_Other,  Title_His , Xaxis_title, pdf );

      sprintf(Title_His, "Efficieny for %s [Full(%s)]",  title, playlistFull_char);
      DrawTGraph(g_TGraph_Eff_Full, Xaxis_title, Yaxis_title, Title_His,
                "Efficieny", pdf, can, plot,  MakeXaxisLOG, MakeYaxisLOG );

      sprintf(Title_His, "Efficieny for %s [Empty(%s)]",  title, playlistEmpty_char);
      DrawTGraph(g_TGraph_Eff_Empty, Xaxis_title, Yaxis_title, Title_His,
                 "Efficieny", pdf, can, plot,  MakeXaxisLOG, MakeYaxisLOG );

      sprintf(Title_His, "Efficieny  for %s [F(%s)-E(%s)]", title, playlistFull_char, playlistEmpty_char);
      DrawTGraph(g_TGraph_Eff_Full_Empty, Xaxis_title, Yaxis_title,Title_His,
                 "Efficieny", pdf, can, plot,  MakeXaxisLOG, MakeYaxisLOG );

      sprintf(Title_His, "Purity for %s [Full(%s)]",  title, playlistFull_char);
      DrawTGraph( g_TGraph_pure_Full, Xaxis_title, Yaxis_title, Title_His,
                 "purity", pdf, can, plot,  MakeXaxisLOG, MakeYaxisLOG );

      sprintf(Title_His, "Purity for %s [Empty(%s)]",  title, playlistEmpty_char);
      DrawTGraph( g_TGraph_pure_Empty, Xaxis_title, Yaxis_title, Title_His,
                "purity", pdf, can, plot,  MakeXaxisLOG, MakeYaxisLOG );

      sprintf(Title_His, "Purity for %s [F(%s)-E(%s)]", title,playlistFull_char, playlistEmpty_char);
      DrawTGraph( g_TGraph_pure_Full_Empty, Xaxis_title, Yaxis_title,Title_His,
                "purity" ,pdf, can, plot,  MakeXaxisLOG, MakeYaxisLOG );


      sprintf(Title_His, "Efficieny and Purity for %s [Full(%s)]",  title, playlistFull_char);
      DrawTGraph(g_TGraph_Eff_Full, g_TGraph_pure_Full, g_TGraph_Eff_pure_Full, Xaxis_title, Yaxis_title, Title_His,
                "Efficieny", "purity", "Efficieny* purity", pdf, can, plot,  MakeXaxisLOG, MakeYaxisLOG );

      sprintf(Title_His, "Efficieny and Purity for %s [Empty(%s)]",  title, playlistEmpty_char);
      DrawTGraph(g_TGraph_Eff_Empty, g_TGraph_pure_Empty, g_TGraph_Eff_pure_Empty, Xaxis_title, Yaxis_title, Title_His,
                 "Efficieny", "purity", "Efficieny* purity", pdf, can, plot,  MakeXaxisLOG, MakeYaxisLOG );

      sprintf(Title_His, "Efficieny and Purity for %s [F(%s)-E(%s)]", title,playlistFull_char, playlistEmpty_char);
      DrawTGraph(g_TGraph_Eff_Full_Empty, g_TGraph_pure_Full_Empty, g_TGraph_Eff_pure_Full_Empty, Xaxis_title, Yaxis_title,Title_His,
                 "Efficieny", "purity", "Efficieny*purity", pdf, can, plot,  MakeXaxisLOG, MakeYaxisLOG );

      sprintf(Title_His, "Purity*Efficieny %s [Full(%s)]",  title, playlistFull_char);
      DrawTGraph( g_TGraph_Eff_pure_Full, Xaxis_title, Yaxis_title, Title_His,
                    "Purity*Efficieny", pdf, can, plot,  MakeXaxisLOG, MakeYaxisLOG );

      sprintf(Title_His, "Purity*Efficieny for %s [Empty(%s)]",  title, playlistEmpty_char);
      DrawTGraph( g_TGraph_Eff_pure_Empty, Xaxis_title, Yaxis_title, Title_His,
                  "Purity*Efficieny", pdf, can, plot,  MakeXaxisLOG, MakeYaxisLOG );

      sprintf(Title_His, "Purity*Efficieny for %s [F(%s)-E(%s)]", title,playlistFull_char, playlistEmpty_char);
      DrawTGraph(g_TGraph_Eff_pure_Full_Empty, Xaxis_title, Yaxis_title,Title_His,
                  "Purity*Efficieny", pdf, can, plot,  MakeXaxisLOG, MakeYaxisLOG );



}//endl;
