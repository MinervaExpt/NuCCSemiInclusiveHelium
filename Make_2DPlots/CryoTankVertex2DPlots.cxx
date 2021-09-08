#include "CryoTankVertex2DPlots.h"
//////////////////////////////////////////////////////////////////////////////
void MakeLatexForCryoVertexFiguresCVandALLErrors(std::string output_name ,std::vector<CryoVertex> CryoVertex_vector, std::string PDF_cv_name, int NError_Groups);
void MakeLatexForCryoVertexFiguresFORStacks(std::string output_name ,std::vector<CryoVertex> CryoVertex_vector ,  std::string pdf_name);

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
sprintf(timeset_nonstacks,"%i_%i_%i_%i_%s", 1 + ltm->tm_mon,ltm->tm_mday, ltm->tm_hour,ltm->tm_min, SysError_printLabel.c_str());
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

auto PlaylistME_1D_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1D_MC_All_SysErrorsOn.root";
auto PlaylistME_1A_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1A_MC_All_SysErrorsOn.root";


auto PlaylistMC_1D_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1D_Data.root";
auto PlaylistMC_1A_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1A_Data.root";



bool is_mc=true;bool isNOT_mc=false;

std::string  pdf_CV = string(text_title_pdf4);

//PlayList_INFO Playlist_MC_1G(kPlayListVector_MC[0], is_mc );

/*
PlayList_INFO PlaylistMC_1P(kPlayListVector_MC[0], is_mc ,false);
PlayList_INFO PlaylistMC_1A(kPlayListVector_MC[1], is_mc ,false);
PlayList_INFO PlaylistMC_1C(kPlayListVector_MC[2], is_mc ,false);
PlayList_INFO PlaylistMC_1D(kPlayListVector_MC[3], is_mc ,false);
PlayList_INFO PlaylistMC_1F(kPlayListVector_MC[4], is_mc ,false);

POT_MC[kPlayListVector_MC[0]] = PlaylistMC_1P.Get_Pot();
POT_MC[kPlayListVector_MC[1]] = PlaylistMC_1A.Get_Pot();
POT_MC[kPlayListVector_MC[2]] = PlaylistMC_1C.Get_Pot();
POT_MC[kPlayListVector_MC[3]] = PlaylistMC_1D.Get_Pot();
POT_MC[kPlayListVector_MC[4]] = PlaylistMC_1F.Get_Pot();



std::vector <PlayList_INFO> MC_playlist;
MC_playlist.push_back(PlaylistMC_1P);
MC_playlist.push_back(PlaylistMC_1A);
MC_playlist.push_back(PlaylistMC_1C);
MC_playlist.push_back(PlaylistMC_1D);
MC_playlist.push_back(PlaylistMC_1F);


PlayList_INFO PlaylistDATA_1P(kPlayListVector_DATA[0], isNOT_mc ,false);
PlayList_INFO PlaylistDATA_1A(kPlayListVector_DATA[1], isNOT_mc ,false);
PlayList_INFO PlaylistDATA_1C(kPlayListVector_DATA[2], isNOT_mc ,false);
PlayList_INFO PlaylistDATA_1D(kPlayListVector_DATA[3], isNOT_mc ,false);
PlayList_INFO PlaylistDATA_1F(kPlayListVector_DATA[4], isNOT_mc ,false);

std::vector <PlayList_INFO> Data_playlist;
Data_playlist.push_back(PlaylistDATA_1P);
Data_playlist.push_back(PlaylistDATA_1A);
Data_playlist.push_back(PlaylistDATA_1C);
Data_playlist.push_back(PlaylistDATA_1D);
Data_playlist.push_back(PlaylistDATA_1F);


POT_DATA[kPlayListVector_DATA[0]] = PlaylistDATA_1P.Get_Pot();
POT_DATA[kPlayListVector_DATA[1]] = PlaylistDATA_1A.Get_Pot();
POT_DATA[kPlayListVector_DATA[2]] = PlaylistDATA_1C.Get_Pot();
POT_DATA[kPlayListVector_DATA[3]] = PlaylistDATA_1D.Get_Pot();
POT_DATA[kPlayListVector_DATA[4]] = PlaylistDATA_1F.Get_Pot();




//auto minervame1P_MC = Playlist_MC_1P.TFILE_PLAYLIST;
TFile *minervame1P_MC     = new TFile(minervame1P_MC_path);
TFile *minervame1A_MC     = new TFile(minervame1A_MC_path);
TFile *minervame1C_MC     = new TFile(minervame1C_MC_path);
TFile *minervame1D_MC     = new TFile(minervame1D_MC_path);
TFile *minervame1F_MC     = new TFile(minervame1F_MC_path);



TFile *minervame1P_DATA     = new TFile(minervame1P_Data_path);
TFile *minervame1A_DATA     = new TFile(minervame1A_Data_path);
TFile *minervame1C_DATA     = new TFile(minervame1C_Data_path);
TFile *minervame1D_DATA     = new TFile(minervame1D_Data_path);
TFile *minervame1F_DATA     = new TFile(minervame1F_Data_path);
*/
PlayList_INFO PlaylistMC_1D(kPlayListVector_MC[0], true, false );
PlayList_INFO PlaylistMC_1A(kPlayListVector_MC[1], true, false );

POT_MC[kPlayListVector_MC[0]] = PlaylistMC_1D.Get_Pot();
POT_MC[kPlayListVector_MC[1]] = PlaylistMC_1A.Get_Pot();

POT_MC_Status[kFULL] = PlaylistMC_1D.Get_Pot();
POT_MC_Status[kEMPTY] = PlaylistMC_1A.Get_Pot();

std::vector <PlayList_INFO> MC_playlist;

MC_playlist.push_back(PlaylistMC_1D);
MC_playlist.push_back(PlaylistMC_1A);


PlayList_INFO PlaylistDATA_1D(kPlayListVector_DATA[0], isNOT_mc,false );
PlayList_INFO PlaylistDATA_1A(kPlayListVector_DATA[1], isNOT_mc,false );

std::vector <PlayList_INFO> Data_playlist;

Data_playlist.push_back(PlaylistDATA_1D);
Data_playlist.push_back(PlaylistDATA_1A);


POT_DATA[kPlayListVector_DATA[0]] = PlaylistDATA_1D.Get_Pot();
POT_DATA[kPlayListVector_DATA[1]] = PlaylistDATA_1A.Get_Pot();

POT_DATA_Status[kFULL] = PlaylistDATA_1D.Get_Pot();
POT_DATA_Status[kEMPTY] = PlaylistDATA_1A.Get_Pot();


std::cout<< "POT_DATA_Status[kFULL] = "<< POT_DATA_Status[kFULL]<<std::endl;

std::cout<< "POT_DATA_Status[kEMPTY] = "<< POT_DATA_Status[kEMPTY]<<std::endl;


TFile *Playlist_ME1D_MC     = new TFile(PlaylistME_1D_MC_path);
TFile *Playlist_ME1A_MC     = new TFile(PlaylistME_1A_MC_path);

TFile *Playlist_ME1D_DATA     = new TFile(PlaylistMC_1D_Data_path);
TFile *Playlist_ME1A_DATA     = new TFile(PlaylistMC_1A_Data_path);






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


  DrawCVAndError_FromTFile(Playlist_ME1D_MC, Playlist_ME1A_MC,  histnameMC_char ,Playlist_ME1D_DATA,Playlist_ME1A_DATA,
    histnameDATA_char, POT_MC_Status, POT_DATA_Status, false, TITLE_char,
    GetVertexCryoVarAxisTitle(Vertex_vertex), pdf_CV, true, false ,"mm", Print_Systematics, my_debug);


  /*
  DrawCVAndError_FromTFile(minervame1P_MC, histname_char, histname_char ,GetVertexCryoVarAxisTitle(Vertex_vertex), pdf );
  auto title_his = GetVertexCryoVarHIST_Title(Vertex_vertex ,kPlayListVector_MC[0] );
  int n_title_his = title_his.length();
  char title_his_char[n_title_his+1];
  strcpy( title_his_char,title_his.c_str());
  DrawDATAWITHCV_AndError_FromTFile_Single_playlist(minervame1P_MC, minervame1P_DATA ,POT_MC, POT_DATA, kPlayListVector_MC[0], histname_char, histnameDATA_char , title_his_char,GetVertexCryoVarAxisTitle(Vertex_vertex), pdf, true);
  DrawStack_Material( my_debug,  minervame1P_MC,  Vertex_vertex , kPlayListVector_MC[0] ,  0, 0,"Material    ", mnv_plot, can, text_title_pdf2);
  DrawStack_Interaction( my_debug,  minervame1P_MC,  Vertex_vertex , kPlayListVector_MC[0] ,0,0,"Interaction    ", mnv_plot, can, text_title_pdf2);
  DrawStack_Particle( my_debug,  minervame1P_MC,  Vertex_vertex , kPlayListVector_MC[0] ,0,0, "Particle    ", mnv_plot, can, text_title_pdf2);


  auto title_his_1 = GetVertexCryoVarHIST_Title(Vertex_vertex ,kPlayListVector_MC[1] );
  int n_title_his_1 = title_his_1.length();
  char title_his_char_1[n_title_his_1+1];
  strcpy( title_his_char_1,title_his_1.c_str());

  DrawCVAndError_FromTFile(minervame1A_MC, histname_char, histname_char ,GetVertexCryoVarAxisTitle(Vertex_vertex), pdf );
  DrawDATAWITHCV_AndError_FromTFile_Single_playlist(minervame1A_MC, minervame1A_DATA ,POT_MC,POT_DATA, kPlayListVector_MC[1], histname_char, histnameDATA_char, title_his_char_1 ,GetVertexCryoVarAxisTitle(Vertex_vertex), pdf, true);
  DrawStack_Material( my_debug,  minervame1A_MC,  Vertex_vertex , kPlayListVector_MC[1] ,  0, 0,"Material    ", mnv_plot, can, text_title_pdf2);
  DrawStack_Interaction( my_debug,  minervame1A_MC,  Vertex_vertex , kPlayListVector_MC[1] ,0,0,"Interaction    ", mnv_plot, can, text_title_pdf2);
  DrawStack_Particle( my_debug,  minervame1A_MC,  Vertex_vertex , kPlayListVector_MC[1] ,0,0, "Particle    ", mnv_plot, can, text_title_pdf2);

  auto title_his_2 = GetVertexCryoVarHIST_Title(Vertex_vertex ,kPlayListVector_MC[2] );
  int n_title_his_2 = title_his_2.length();
  char title_his_char_2[n+1];
  strcpy( title_his_char_2,title_his_2.c_str());

  DrawCVAndError_FromTFile(minervame1C_MC, histname_char, histname_char ,GetVertexCryoVarAxisTitle(Vertex_vertex), pdf );
  DrawDATAWITHCV_AndError_FromTFile_Single_playlist(minervame1C_MC, minervame1C_DATA ,POT_MC,POT_DATA, kPlayListVector_MC[2], histname_char, histnameDATA_char,title_his_char_2 ,GetVertexCryoVarAxisTitle(Vertex_vertex), pdf, true);
  DrawStack_Material( my_debug,  minervame1C_MC,  Vertex_vertex , kPlayListVector_MC[2] ,  0, 0,"Material    ", mnv_plot, can, text_title_pdf2);
  DrawStack_Interaction( my_debug,  minervame1C_MC,  Vertex_vertex , kPlayListVector_MC[2] ,0,0,"Interaction    ", mnv_plot, can, text_title_pdf2);
  DrawStack_Particle( my_debug,  minervame1C_MC,  Vertex_vertex , kPlayListVector_MC[2] ,0,0, "Particle    ", mnv_plot, can, text_title_pdf2);


  auto T3 = GetVertexCryoVarHIST_Title(Vertex_vertex ,kPlayListVector_MC[3],kPlayListVector_MC[1] );
  int n_T3 = T3.length();
  char T3_char[n_T3+1];
  strcpy( T3_char,T3.c_str());

  DrawStack_Vertex_Material_FUll_EMPTY_WITHDATA(false, minervame1D_MC,minervame1A_MC, minervame1D_DATA,minervame1A_DATA,POT_MC,POT_DATA ,Vertex_vertex, kPlayListVector_MC[3],kPlayListVector_MC[1],
    0,false, "", mnv_plot, can, text_title_pdf2);

  DrawDATAWITHCV_AndError_FromTFile_Single_playlist_Full_EMPTY(minervame1D_MC,minervame1A_MC, minervame1D_DATA,minervame1A_DATA,POT_MC,POT_DATA,
    kPlayListVector_MC[3],kPlayListVector_MC[1], histname_char, histnameDATA_char, T3_char ,GetVertexCryoVarAxisTitle(Vertex_vertex), pdf, true);




            auto T4 = GetVertexCryoVarHIST_Title(Vertex_vertex ,kPlayListVector_MC[0],kPlayListVector_MC[1] );
            int n_T4 = T4.length();
            char T4_char[n_T4+1];
            strcpy( T4_char,T4.c_str());

  DrawDATAWITHCV_AndError_FromTFile_Single_playlist_Full_EMPTY(minervame1P_MC,minervame1A_MC, minervame1P_DATA,minervame1A_DATA,POT_MC,POT_DATA,
                 kPlayListVector_MC[0],kPlayListVector_MC[1], histname_char, histnameDATA_char, T4_char ,GetVertexCryoVarAxisTitle(Vertex_vertex), pdf, true);


                 auto T5 = GetVertexCryoVarHIST_Title(Vertex_vertex ,kPlayListVector_MC[4],kPlayListVector_MC[1] );
                 int n_T5 = T5.length();
                 char T5_char[n_T5+1];
                 strcpy( T5_char,T5.c_str());

DrawDATAWITHCV_AndError_FromTFile_Single_playlist_Full_EMPTY(minervame1F_MC,minervame1A_MC, minervame1F_DATA,minervame1A_DATA,POT_MC,POT_DATA,
                                kPlayListVector_MC[4],kPlayListVector_MC[1], histname_char, histnameDATA_char, T5_char ,GetVertexCryoVarAxisTitle(Vertex_vertex), pdf, true);

*/






}// end of for loop to print


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


    DrawSTACKfromHistFilio_FromTFile(Playlist_ME1D_MC, Playlist_ME1A_MC,  histnameMC_char ,Playlist_ME1D_DATA,Playlist_ME1A_DATA,
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


     DrawSTACKfromHistFilio_FromTFile(Playlist_ME1D_MC, Playlist_ME1A_MC,  histnameMC_char ,Playlist_ME1D_DATA,Playlist_ME1A_DATA,
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


      DrawSTACKfromHistFilio_FromTFile(Playlist_ME1D_MC, Playlist_ME1A_MC,  histnameMC_char ,Playlist_ME1D_DATA,Playlist_ME1A_DATA,
       histnameDATA_char, POT_MC_Status, POT_DATA_Status, false, TITLE_char,
       GetVertexCryoVarAxisTitle(CryoVertex_vector), pdf_stacks_Particle, true, false ,"mm", kParticle, my_debug );



 }


  can_stacks -> Print(text_title_Particle_pdf7);
sprintf(Latex_name, "PLOTS_%s_CryoVertex_Latex_stack_Particle", timeset);
  input_Latex_name = Latex_name;
  MakeLatexForCryoVertexFiguresFORStacks(input_Latex_name ,kCryoVertexVaribles_vector , pdf_stacks_Particle );

std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;

std::cout<< " Done with Muon "<< std::endl;

std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;


sprintf(Latex_name, "PLOTS_%s_CryoVertex_Latex_CV_and_Stacks", timeset);
input_Latex_name = Latex_name;

//MakeLatexForMuonFiguresCVandGroupErrors_andALLSTACKS(Print_Systematics ,input_Latex_name,
 // kCryoVertexVaribles_vector, pdf_CV, pdf_stacks_Material, pdf_stacks_interaction,
 // pdf_stacks_Particle, N_Error_groups);


  std::cout << std::endl;
  std::cout << "Done WITH Stacks" << std::endl;




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

bool cutsOn;
std::cout << "Run over cutsOn?  (0 = false, 1 = true) " << std::endl;
std::cin >> cutsOn;
std::cout << std::boolalpha << cutsOn << std::endl;

bool my_norm;
std::cout << "Which Normalization?  (0 = POT, 1 = relative equal areas) " << std::endl;
std::cin >> my_norm;
std::cout << std::boolalpha << my_norm << std::endl;

bool my_debug;
std::cout << "Run in Debug Mode? (0 = NO, 1 = YES) " << std::endl;
std::cin >> my_debug;
std::cout << std::boolalpha << my_debug << std::endl;

int my_Print_Systmatics;
std::cout << "Print Error Systmatics?  [ 0 = Total and Groups Systemtics Errors ,  1 = Total Systematic Errors , 2 = none ]" << std::endl;
std::cin >> my_Print_Systmatics;
std::cout << "Pitched: " << my_Print_Systmatics << std::endl;


std::string input;
std::cout << "What is the name of the user? " << std::endl;
std::cin >> input;
std::cout << input << std::endl;

const char *inputFileLoc = input.c_str();

Kin(cutsOn, my_norm, my_debug, inputFileLoc, my_Print_Systmatics);

return 0;

}


std::vector<ME_helium_Playlists> GetPlayListVector_MC() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ME_helium_Playlists> Playlist;
  Playlist.push_back(kME1D);
  Playlist.push_back(kME1A);
  //Playlist.push_back(kME1G);
  //Playlist.push_back(kME1P);

  //Playlist.push_back(kME1C);

  //Playlist.push_back(kME1F);
  return Playlist;
//#endif
}


std::vector<ME_helium_Playlists> GetPlayListVector_DATA() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ME_helium_Playlists> Playlist;

Playlist.push_back(kME1D);
Playlist.push_back(kME1A);
  //Playlist.push_back(kME1G);
  //Playlist.push_back(kME1P);

  //Playlist.push_back(kME1C);

  //Playlist.push_back(kME1F);
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


  return CryoVertexVars;
//#endif
}


void MakeLatexForCryoVertexFiguresCVandALLErrors(std::string output_name ,std::vector<CryoVertex> CryoVertex_vector, std::string PDF_cv_name, int NError_Groups){
  double scale= .24;
  std::ofstream myfile;

  const int  Column_Spacing = NError_Groups + 2;

  string fileName = output_name + ".txt";
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
  string fileName = output_name + ".txt";
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
