

#include "NonMuonKinematicPlots.h"
//////////////////////////////////////////////////////////////////////////////

std::vector<ME_helium_Playlists> GetPlayListVector_MC();
std::vector<ME_helium_Playlists> GetPlayListVector_DATA();
void MakeLatexForNonMuonFiguresCVandGroupErrors_andALLSTACKS(int Systmatic_ErrorType ,std::string output_name ,
std::vector<SecondTrkVar> NoN_muon_vector,  std::string pdf_name_CV, std::string pdf_stack_Material, std::string pdf_stack_Interaction,
  std::string pdf_stack_Particle,int NError_Groups);
void MakeLatexForNonMuonFiguresCVandALLErrors(std::string output_name ,std::vector<SecondTrkVar> NoN_muon_vector,
  std::string PDF_cv_name, int NError_Groups);

void MakeLatexForNonMuonFiguresFORStacks(std::string output_name ,std::vector<SecondTrkVar> NoN_muon_vector ,  std::string pdf_name);

void Kin(bool &cutsOn, bool &my_norm, bool &my_debug, const char *userDir, int &print_Error) {
TH1::AddDirectory(false);
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~       Starting Plotter: Non MUON Tracking Plots         ~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
const std::vector<ME_helium_Playlists> kPlayListVector_MC = GetPlayListVector_MC();
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
 char Latex_name[2024];
time_t now = time(0);
tm *ltm = localtime(&now);

 bool Stats_only = false;
 char timeset_nonstacks[2024];
 std::string SysError_printLabel = PrintLabel_Systematics(print_Error);
 auto Playlist_names =  MakePlaylistString(kPlayListVector_MC);
 sprintf(timeset_nonstacks,"%i_%i_%i_%i_%s_%s", 1 + ltm->tm_mon,ltm->tm_mday, ltm->tm_hour, ltm->tm_min, SysError_printLabel.c_str(),Playlist_names.c_str() );


sprintf(text_title_pdf1, "PLOTS_%s_Non_muonTRK_secondaryTRK_CV_ErrorBand_ME.pdf(",timeset_nonstacks );
can -> Print(text_title_pdf1);
sprintf(text_title_pdf2, "PLOTS_%s_Non_muonTRK_secondaryTRK_CV_ErrorBand_ME.pdf",timeset_nonstacks );
sprintf(text_title_pdf2, "PLOTS_%s_Non_muonTRK_secondaryTRK_CV_ErrorBand_ME.pdf",timeset_nonstacks );
sprintf(text_title_pdf3, "PLOTS_%s_Non_muonTRK_secondaryTRK_CV_ErrorBand_ME.pdf)",timeset_nonstacks );
sprintf(text_title_pdf4, "PLOTS_%s_Non_muonTRK_secondaryTRK_CV_ErrorBand_ME",timeset_nonstacks );
//auto rootinputpathfile = "/minerva/app/users/cnguyen/cmtuser/Minerva_v21r1p1Helium/Ana/VetoWallStudies/scripts/ChainWrapper_FW_ME/eventselection/STACKS_Histograms_minervame1G_MC.root";

//auto PlaylistMC_1D_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1A_MC_StatsONLY.root";
//auto PlaylistME_1D_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1D_MC.root";
//auto PlaylistME_1A_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1A_MC.root";
//auto PlaylistME_1D_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1D_MC_All_SysErrorsOn.root";
//auto PlaylistME_1F_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1F_MC_StatsONLYErrors.root";
//auto PlaylistME_1A_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1A_MC_All_SysErrorsOn.root";
//auto PlaylistME_1G_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1G_MC_All_SysErrorsOn.root";
//auto PlaylistME_1F_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1F_MC_StatsONLYErrors.root";
//auto PlaylistME_1G_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1G_MC_StatsONLYErrors.root";

auto PlaylistME_1F_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1F_MC_All_SysErrorsOn.root";
auto PlaylistME_1G_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1G_MC_All_SysErrorsOn.root";


auto PlaylistMC_1F_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1F_Data.root";
//auto PlaylistMC_1D_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1D_Data.root";
//auto PlaylistMC_1A_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1A_Data.root";
auto PlaylistMC_1G_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1G_Data.root";


auto dans_rootfile_path = "/minerva/data/users/drut1186/ME_Inclusive/PubProcessing_v102_Rerun_NoBubbleConstraint/Inclusive_CV/MuonEventSelection_MakeFlux-1_Multiplicity-0_Sample-Signal_minervame1A.root";
auto andrew_rootfile_path = "/minerva/app/users/cnguyen/MINERvA101_2021/installExampleMINERvA101/opt/build/MINERvA-101-Cross-Section/OutputMichelHists.root";

TFile *dans_DATA     = new TFile(dans_rootfile_path);
TFile *andrew_DATA     = new TFile(andrew_rootfile_path);


bool is_mc=true;bool isNOT_mc=false;
bool BinNorm=true;
std::string pdf_CV = string(text_title_pdf4);

//PlayList_INFO Playlist_MC_1G(kPlayListVector_MC[0], is_mc );
//PlayList_INFO PlaylistMC_1D(kPlayListVector_MC[0], true, false );

//PlayList_INFO PlaylistMC_1A(kPlayListVector_MC[1], true, false );

//PlayList_INFO PlaylistTRUTH_1D(kPlayListVector_MC[0], true );
//PlayList_INFO PlaylistTRUTH_1A(kPlayListVector_MC[1], true );


PlayList_INFO PlaylistMC_1F(kPlayListVector_MC[0], true, Stats_only );
PlayList_INFO PlaylistMC_1G(kPlayListVector_MC[1], true, Stats_only );

PlaylistMC_1F.PRINTROOT_Path();
PlaylistMC_1G.PRINTROOT_Path();


POT_MC[kPlayListVector_MC[0]] = PlaylistMC_1F.Get_Pot();
POT_MC[kPlayListVector_MC[1]] = PlaylistMC_1G.Get_Pot();

POT_MC_Status[kFULL] = PlaylistMC_1F.Get_Pot();
POT_MC_Status[kEMPTY] = PlaylistMC_1G.Get_Pot();

//POT_MC[kPlayListVector_MC[0]] = PlaylistMC_1D.Get_Pot();

//POT_MC[kPlayListVector_MC[1]] = PlaylistMC_1A.Get_Pot();
//POT_MC_Status[kFULL] = PlaylistMC_1D.Get_Pot();
//POT_MC_Status[kEMPTY] = PlaylistMC_1A.Get_Pot();



std::cout<< "POT_MC_Status[kFULL] = "<< POT_MC_Status[kFULL]<<std::endl;
std::cout<< "POT_MC_Status[kEMPTY] = "<< POT_MC_Status[kEMPTY]<<std::endl;



std::vector <PlayList_INFO> MC_playlist;

//MC_playlist.push_back(PlaylistMC_1D);
//MC_playlist.push_back(PlaylistMC_1F);
//MC_playlist.push_back(PlaylistMC_1A);
//MC_playlist.push_back(PlaylistMC_1G);

//PlayList_INFO PlaylistDATA_1D(kPlayListVector_DATA[0], isNOT_mc,false );
PlayList_INFO PlaylistDATA_1F(kPlayListVector_DATA[0], isNOT_mc,false );

//PlayList_INFO PlaylistDATA_1A(kPlayListVector_DATA[1], isNOT_mc,false );


PlayList_INFO PlaylistDATA_1G(kPlayListVector_DATA[1], isNOT_mc,false );


std::vector <PlayList_INFO> Data_playlist;

//Data_playlist.push_back(PlaylistDATA_1D);
Data_playlist.push_back(PlaylistDATA_1F);
//Data_playlist.push_back(PlaylistDATA_1A);
Data_playlist.push_back(PlaylistDATA_1G);


//POT_DATA[kPlayListVector_DATA[0]] = PlaylistDATA_1D.Get_Pot();
POT_DATA[kPlayListVector_DATA[0]] = PlaylistDATA_1F.Get_Pot();

//POT_DATA[kPlayListVector_DATA[1]] = PlaylistDATA_1A.Get_Pot();
POT_DATA[kPlayListVector_DATA[1]] = PlaylistDATA_1G.Get_Pot();





//POT_DATA_Status[kFULL] = PlaylistDATA_1D.Get_Pot();
POT_DATA_Status[kFULL] = PlaylistDATA_1F.Get_Pot();

//POT_DATA_Status[kEMPTY] = PlaylistDATA_1A.Get_Pot();
POT_DATA_Status[kEMPTY] = PlaylistDATA_1G.Get_Pot();


//TFile *Playlist_ME1D_MC     = new TFile(PlaylistME_1D_MC_path);
TFile *Playlist_ME1F_MC     = new TFile(PlaylistME_1F_MC_path);

//TFile *Playlist_ME1A_MC     = new TFile(PlaylistME_1A_MC_path);
TFile *Playlist_ME1G_MC     = new TFile(PlaylistME_1G_MC_path);


//TFile *Playlist_ME1D_DATA     = new TFile(PlaylistMC_1D_Data_path);
//TFile *Playlist_ME1A_DATA     = new TFile(PlaylistMC_1A_Data_path);
TFile *Playlist_ME1F_DATA     = new TFile(PlaylistMC_1F_Data_path);

TFile *Playlist_ME1G_DATA     = new TFile(PlaylistMC_1G_Data_path);




std::cout<< "POT_DATA_Status[kFULL] = "<< POT_DATA_Status[kFULL]<<std::endl;

std::cout<< "POT_DATA_Status[kEMPTY] = "<< POT_DATA_Status[kEMPTY]<<std::endl;





for(auto Vertex_vertex: kNonMuonTRK_vector ){

  auto histname = GetsecondTrakHistName(Vertex_vertex);
  auto histname_data = GetsecondTrakHistName_DATA_Name(Vertex_vertex);
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

  auto title_his = GetsecondTrkTitleName(Vertex_vertex);
  int n_title_his = title_his.length();
  char title_his_char[n_title_his+1];
  strcpy( title_his_char,title_his.c_str());

  DrawCVAndError_FromTFile(Playlist_ME1F_MC, Playlist_ME1G_MC,  histnameMC_char ,Playlist_ME1F_DATA, Playlist_ME1G_DATA,
    histnameDATA_char, POT_MC_Status, POT_DATA_Status, false, title_his_char,
    GetsecondTrk_AXIS_TitleName(Vertex_vertex),pdf_CV, true, false, GetsecondTrkUnitType(Vertex_vertex), print_Error, my_debug);
  }

  DrawCVAndError_FromTFile(Playlist_ME1F_MC, Playlist_ME1G_MC,  "h_Muon_pseudorapidity" ,Playlist_ME1F_DATA, Playlist_ME1G_DATA,
  "h_Data_Muon_pseudorapidity", POT_MC_Status, POT_DATA_Status, false, "Muon pseudorapidity ",
  "pseudorapidity",pdf_CV, true, false, "pseudorapidity", print_Error, my_debug);

  DrawCVAndError_FromTFile(Playlist_ME1F_MC, Playlist_ME1G_MC,  "h_Muon_pseudorapidity_angle" ,Playlist_ME1F_DATA, Playlist_ME1G_DATA,
  "h_Data_Muon_pseudorapidity_angle", POT_MC_Status, POT_DATA_Status, false, "Muon Angle from  pseudorapidity ",
  " Angle from pseudorapidity",pdf_CV, true, false, "[degs]", print_Error, my_debug);

  DrawCVAndError_FromTFile(Playlist_ME1F_MC, Playlist_ME1G_MC,  "h_Muon_rapidity" ,Playlist_ME1F_DATA, Playlist_ME1G_DATA,
  "h_Data_Muon_rapidity", POT_MC_Status, POT_DATA_Status, false, "Muon rapidity ",
  "rapidity",pdf_CV, true, false, "rapidity", print_Error, my_debug);


  Draw2DCVAndError_FromTFile(Playlist_ME1F_MC, Playlist_ME1G_MC,  "h_2d_2ndtrkLength_vertex_R" ,Playlist_ME1F_DATA, Playlist_ME1G_DATA,
  "h2_Data_secTrkLength_R", POT_MC_Status, POT_DATA_Status, true, "SecTrk Lenght Vs Vertex R", "R",
  "TRACK LENGHT", "[cm]", pdf_CV , true, false, print_Error ,my_debug);

  Draw2DCVAndError_FromTFile(Playlist_ME1F_MC, Playlist_ME1G_MC,  "h_2d_2ndtrkLength_vertex_Z" ,Playlist_ME1F_DATA, Playlist_ME1G_DATA,
  "h2_Data_secTrkLength_Z", POT_MC_Status, POT_DATA_Status, true,"SecTrk Lenght Vs Vertex R", "Z",
  "TRACK LENGHT", "[cm]", pdf_CV , true, false, print_Error ,my_debug);

  Draw2DCVAndError_FromTFile(Playlist_ME1F_MC, Playlist_ME1G_MC,  "h_2d_2ndtrkPathlength_vertex_R" ,Playlist_ME1F_DATA, Playlist_ME1G_DATA,
  "h2_Data_secTrkpathLength_R", POT_MC_Status, POT_DATA_Status, true, "SecTrk Lenght Vs Vertex R", "R",
  "pathlength", "[cm^{2}/g]", pdf_CV , true, false, print_Error ,my_debug);

  Draw2DCVAndError_FromTFile(Playlist_ME1F_MC, Playlist_ME1G_MC,  "h_2d_2ndtrkPathlength_vertex_Z" ,Playlist_ME1F_DATA, Playlist_ME1G_DATA,
  "h2_Data_secTrkpathLength_Z", POT_MC_Status, POT_DATA_Status, true,"SecTrk Lenght Vs Vertex R", "Z",
  "pathleghth", "[cm^{2}/g]", pdf_CV , true, false, print_Error ,my_debug);

  Draw2DCVAndError_FromTFile(Playlist_ME1F_MC, Playlist_ME1G_MC,  "h_2d_2ndtrkLength_Angle" ,Playlist_ME1F_DATA, Playlist_ME1G_DATA,
  "h2_Data_2ndtrkLength_Angle", POT_MC_Status, POT_DATA_Status, true, "SecTrk Lenght Vs Vertex R", "R",
  "TRACK LENGHT", "[cm]", pdf_CV , true, false, print_Error ,my_debug);




  can -> Print(text_title_pdf3);

  sprintf(Latex_name, "PLOTS_%s_NonMuon_Latex_CV", timeset_nonstacks);
   std::string input_Latex_name = Latex_name;
  MakeLatexForNonMuonFiguresCVandALLErrors(input_Latex_name ,kNonMuonTRK_vector, pdf_CV,  N_Error_groups);


  std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;

  std::cout<< " CryoVertex Material Stacks "<< std::endl;

  std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;
  char text_title_pdf5[2024];
  char text_title_pdf6[2024];
  char text_title_pdf7[2024];
  char text_title_pdf8[2024];
  TCanvas *can_stacks = new TCanvas("can_stacks");
  sprintf(text_title_pdf5, "PLOTS_%s_STACKS_Material_NonMuonsecTrk.pdf(",timeset_nonstacks );
  can_stacks -> Print(text_title_pdf5);
  sprintf(text_title_pdf6, "PLOTS_%s_STACKS_Material_NonMuonsecTrk.pdf",timeset_nonstacks );
  sprintf(text_title_pdf7, "PLOTS_%s_STACKS_Material_NonMuonsecTrk.pdf)",timeset_nonstacks );
  sprintf(text_title_pdf8, "PLOTS_%s_STACKS_Material_NonMuonsecTrk",timeset_nonstacks );
  std::string pdf_stacks_Material = string(text_title_pdf8);

for(auto Vertex_vertex: kNonMuonTRK_vector ){

  auto histname = GetsecondTrakHistName(Vertex_vertex);
  auto histname_data = GetsecondTrakHistName_DATA_Name(Vertex_vertex);
  int n = histname.length();
  int n_data = histname_data.length();

  char histnameMC_char[n+1];
  char histnameDATA_char[n_data+1];

  strcpy( histnameMC_char,histname.c_str());
  strcpy( histnameDATA_char,histname_data.c_str());
  auto title_his = GetsecondTrkTitleName(Vertex_vertex);
  int n_title_his = title_his.length();
  char title_his_char[n_title_his+1];
  strcpy( title_his_char,title_his.c_str());

  DrawSTACKfromHistFilio_FromTFile(Playlist_ME1F_MC, Playlist_ME1G_MC,  histnameMC_char ,Playlist_ME1F_DATA,Playlist_ME1G_DATA,
        histnameDATA_char, POT_MC_Status, POT_DATA_Status, false, title_his_char,
        GetsecondTrk_AXIS_TitleName(Vertex_vertex), pdf_stacks_Material, true, false ,GetsecondTrkUnitType(Vertex_vertex), kMaterial, my_debug );


}


 can_stacks -> Print(text_title_pdf7);

 sprintf(Latex_name, "PLOTS_%s_NonMuon_Latex_Material_stacks", timeset_nonstacks);
  input_Latex_name = Latex_name;
 MakeLatexForNonMuonFiguresFORStacks(input_Latex_name ,kNonMuonTRK_vector ,  pdf_stacks_Material);




 std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;

 std::cout<< "  CryoVertex Interaction Stacks "<< std::endl;

 std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;

 sprintf(text_title_pdf5, "PLOTS_%s_STACKS_Interaction_NonMuonsecTrk.pdf(",timeset_nonstacks );
 can_stacks -> Print(text_title_pdf5);
 sprintf(text_title_pdf6, "PLOTS_%s_STACKS_Interaction_NonMuonsecTrk.pdf",timeset_nonstacks );
 sprintf(text_title_pdf7, "PLOTS_%s_STACKS_Interaction_NonMuonsecTrk.pdf)",timeset_nonstacks );
 sprintf(text_title_pdf8, "PLOTS_%s_STACKS_Interaction_NonMuonsecTrk",timeset_nonstacks );
 std::string pdf_stacks_Interaction = string(text_title_pdf8);


 for(auto Vertex_vertex: kNonMuonTRK_vector ){

   auto histname = GetsecondTrakHistName(Vertex_vertex);
   auto histname_data = GetsecondTrakHistName_DATA_Name(Vertex_vertex);
   int n = histname.length();
   int n_data = histname_data.length();

   char histnameMC_char[n+1];
   char histnameDATA_char[n_data+1];

   strcpy( histnameMC_char,histname.c_str());
   strcpy( histnameDATA_char,histname_data.c_str());

   strcpy( histnameMC_char,histname.c_str());
   strcpy( histnameDATA_char,histname_data.c_str());

   auto title_his = GetsecondTrkTitleName(Vertex_vertex);
   int n_title_his = title_his.length();
   char title_his_char[n_title_his+1];
   strcpy( title_his_char,title_his.c_str());

   DrawSTACKfromHistFilio_FromTFile(Playlist_ME1F_MC, Playlist_ME1G_MC,  histnameMC_char ,Playlist_ME1F_DATA,Playlist_ME1G_DATA,
         histnameDATA_char, POT_MC_Status, POT_DATA_Status, false, title_his_char,
         GetsecondTrk_AXIS_TitleName(Vertex_vertex), pdf_stacks_Interaction, true, false ,GetsecondTrkUnitType(Vertex_vertex), kInteraction, my_debug );


 }



 can_stacks -> Print(text_title_pdf7);
  sprintf(Latex_name, "PLOTS_%s_NonMuon_Latex_stacks_Interaction", timeset_nonstacks);
 input_Latex_name = Latex_name;
 MakeLatexForNonMuonFiguresFORStacks(input_Latex_name ,kNonMuonTRK_vector ,  pdf_stacks_Interaction);



 std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;

 std::cout<< "  CryoVertex Interaction Stacks "<< std::endl;

 std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;

 sprintf(text_title_pdf5, "PLOTS_%s_STACKS_Particle_NonMuonsecTrk.pdf(",timeset_nonstacks );
 can_stacks -> Print(text_title_pdf5);
 sprintf(text_title_pdf6, "PLOTS_%s_STACKS_Particle_NonMuonsecTrk.pdf",timeset_nonstacks );
 sprintf(text_title_pdf7, "PLOTS_%s_STACKS_Particle_NonMuonsecTrk.pdf)",timeset_nonstacks );
 sprintf(text_title_pdf8, "PLOTS_%s_STACKS_Particle_NonMuonsecTrk",timeset_nonstacks );
 std::string pdf_stacks_Particle = string(text_title_pdf8);


 for(auto Vertex_vertex: kNonMuonTRK_vector ){

   auto histname = GetsecondTrakHistName(Vertex_vertex);
   auto histname_data = GetsecondTrakHistName_DATA_Name(Vertex_vertex);
   int n = histname.length();
   int n_data = histname_data.length();

   char histnameMC_char[n+1];
   char histnameDATA_char[n_data+1];

   strcpy( histnameMC_char,histname.c_str());
   strcpy( histnameDATA_char,histname_data.c_str());

   auto title_his = GetsecondTrkTitleName(Vertex_vertex);
   int n_title_his = title_his.length();
   char title_his_char[n_title_his+1];
   strcpy( title_his_char,title_his.c_str());


   DrawSTACKfromHistFilio_FromTFile(Playlist_ME1F_MC, Playlist_ME1G_MC,  histnameMC_char ,Playlist_ME1F_DATA,Playlist_ME1G_DATA,
         histnameDATA_char, POT_MC_Status, POT_DATA_Status, false, title_his_char,
         GetsecondTrk_AXIS_TitleName(Vertex_vertex), pdf_stacks_Particle, true, false ,GetsecondTrkUnitType(Vertex_vertex), kParticle, my_debug );


 }

 DrawSTACKfromHistFilio_FromTFile(Playlist_ME1F_MC, Playlist_ME1G_MC,  "h_secTrk_nonparentEnergy" ,Playlist_ME1F_DATA,Playlist_ME1G_DATA,
       "h_Data_secTrk_Energy", POT_MC_Status, POT_DATA_Status, false, "nonpartent 2nd Trk particle type",
       GetsecondTrk_AXIS_TitleName(kNonMuonTRK_vector.at(0)), pdf_stacks_Particle, true, false ,GetsecondTrkUnitType(kNonMuonTRK_vector.at(0)), kParticle, my_debug );


 can -> Print(text_title_pdf7);
 sprintf(Latex_name, "PLOTS_%s_Latex_NonMuonstacks_Particle", timeset_nonstacks);
 input_Latex_name = Latex_name;
 MakeLatexForNonMuonFiguresFORStacks(input_Latex_name ,kNonMuonTRK_vector ,  pdf_stacks_Particle);




   std::cout << std::endl;
   std::cout << "Done WITH Stacks" << std::endl;
    sprintf(Latex_name, "PLOTS_%s_NonMuon_Latex_ALLCVandStack", timeset_nonstacks);
    input_Latex_name = Latex_name;
   MakeLatexForNonMuonFiguresCVandGroupErrors_andALLSTACKS(print_Error ,input_Latex_name,
   kNonMuonTRK_vector,  pdf_CV,  pdf_stacks_Material, pdf_stacks_Interaction,
      pdf_stacks_Particle,N_Error_groups);




      sprintf(text_title_pdf5, "PLOTS_RatioValidation.pdf(" );
      sprintf(text_title_pdf6, "PLOTS_RatioValidation.pdf" );
      sprintf(text_title_pdf7, "PLOTS_RatioValidation.pdf)" );
      sprintf(text_title_pdf8, "PLOTS_RatioValidation" );
      std::string pdf_val(text_title_pdf8);

      can -> Print(text_title_pdf5);

      Draw2DRatio_FromTFile(andrew_DATA, dans_DATA, "_data_pzmu_pTmu","h_pzmu_ptmu_data",
                                    "pT_{Andrew}", "pT_{Dan}","pZ_{Andrew}", "pZ_{Dan}", "Ratio between Andrew and Dans CC incluisve Selection", text_title_pdf6, can, mnv_plot);

      Draw2DHist_TFILE(dans_DATA, "h_pzmu_ptmu_data", "Dan", "P_{T} [Gev]","P_{Z}[Gev]",
               text_title_pdf6, can, mnv_plot);

      Draw2DHist_TFILE(andrew_DATA,"_data_pzmu_pTmu", "Andrew", "P_{T}[Gev]","P_{Z}[Gev]",
                        text_title_pdf6, can, mnv_plot);


        can -> Print(text_title_pdf7);







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

Playlist.push_back(kME1F);
//Playlist.push_back(kME1D);
//Playlist.push_back(kME1P);
  //Playlist.push_back(kME1A);
  //Playlist.push_back(kME1C);
  Playlist.push_back(kME1G);

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

std::vector<SecondTrkVar> GetPlayListSecondTrkVector() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<SecondTrkVar> Playlist;

  Playlist.push_back(ksecE);
  Playlist.push_back(kThetamid);
  Playlist.push_back(kOpenAngle);
  Playlist.push_back(kPathway);
  Playlist.push_back(kDOCA);
  //Playlist.push_back(kFirstsecTrk_Xnode);
  //Playlist.push_back(kFirstsecTrk_Ynode);
  //Playlist.push_back(kFirstsecTrk_Znode);
  //Playlist.push_back(kLastsecTrk_Xnode);
  //Playlist.push_back(kLastsecTrk_Ynode);
  //Playlist.push_back(kLastsecTrk_Znode);
  Playlist.push_back(ksec_tracklength_minerva);
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
