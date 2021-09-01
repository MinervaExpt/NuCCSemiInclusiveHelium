#include "KinematicPlots.h"


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
std::cout<<"~~~~~       Starting Plotter: Kinematic Plots         ~~~~~"<<std::endl;
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


//PlayList_INFO Playlist_MC_1G(kPlayListVector_MC[0], is_mc );


//auto PlaylistME_1D_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1D_MC_All_SysErrorsOn.root";

//auto PlaylistME_1A_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1A_MC_All_SysErrorsOn.root";
//auto PlaylistME_1G_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1G_MC_All_SysErrorsOn.root";

//auto PlaylistME_1F_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1F_MC_StatsONLYErrors.root";
//auto PlaylistME_1A_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1A_MC_All_SysErrorsOn.root";
auto PlaylistME_1F_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1F_MC_All_SysErrorsOn.root";
auto PlaylistME_1G_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1G_MC_All_SysErrorsOn.root";
//auto PlaylistME_1G_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1G_MC_StatsONLYErrors.root";



//auto PlaylistMC_1D_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1D_Data.root";
auto PlaylistMC_1F_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1F_Data.root";

//auto PlaylistMC_1A_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1A_Data.root";
auto PlaylistMC_1G_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1G_Data.root";


bool is_mc=true;bool isNOT_mc=false;


std::string pdf_CV = string(text_title_pdf4);

//PlayList_INFO Playlist_MC_1G(kPlayListVector_MC[0], is_mc );
//PlayList_INFO PlaylistMC_1D(kPlayListVector_MC[0], true, false );
//PlayList_INFO PlaylistMC_1A(kPlayListVector_MC[1], true, false );
//PlayList_INFO PlaylistMC_1G(kPlayListVector_MC[1], true, false );
//PlayList_INFO PlaylistTRUTH_1D(kPlayListVector_MC[0], true );
//PlayList_INFO PlaylistTRUTH_1A(kPlayListVector_MC[1], true );

 bool Stats_only = false;
PlayList_INFO PlaylistMC_1F(kPlayListVector_MC[0], true, Stats_only );

//PlayList_INFO PlaylistMC_1A(kPlayListVector_MC[1], true, false );
PlayList_INFO PlaylistMC_1G(kPlayListVector_MC[1], true, Stats_only );

POT_MC[kPlayListVector_MC[0]] = PlaylistMC_1F.Get_Pot();

//POT_MC[kPlayListVector_MC[0]] = PlaylistMC_1D.Get_Pot();
//POT_MC[kPlayListVector_MC[1]] = PlaylistMC_1A.Get_Pot();
POT_MC[kPlayListVector_MC[1]] = PlaylistMC_1G.Get_Pot();

//POT_MC_Status[kFULL] = PlaylistMC_1D.Get_Pot();
POT_MC_Status[kFULL] = PlaylistMC_1F.Get_Pot();

//POT_MC_Status[kEMPTY] = PlaylistMC_1A.Get_Pot();
POT_MC_Status[kEMPTY] = PlaylistMC_1G.Get_Pot();


std::vector <PlayList_INFO> MC_playlist;

//MC_playlist.push_back(PlaylistMC_1D);
MC_playlist.push_back(PlaylistMC_1F);
//MC_playlist.push_back(PlaylistMC_1A);
MC_playlist.push_back(PlaylistMC_1G);

PlayList_INFO PlaylistDATA_1F(kPlayListVector_DATA[0], isNOT_mc,false );

//PlayList_INFO PlaylistDATA_1D(kPlayListVector_DATA[0], isNOT_mc,false );
//PlayList_INFO PlaylistDATA_1A(kPlayListVector_DATA[1], isNOT_mc,false );
PlayList_INFO PlaylistDATA_1G(kPlayListVector_DATA[1], isNOT_mc,false );


std::vector <PlayList_INFO> Data_playlist;

//Data_playlist.push_back(PlaylistDATA_1D);
Data_playlist.push_back(PlaylistDATA_1F);

//Data_playlist.push_back(PlaylistDATA_1A);
Data_playlist.push_back(PlaylistDATA_1G);

POT_DATA[kPlayListVector_DATA[0]] = PlaylistDATA_1F.Get_Pot();

//POT_DATA[kPlayListVector_DATA[0]] = PlaylistDATA_1D.Get_Pot();
//POT_DATA[kPlayListVector_DATA[1]] = PlaylistDATA_1A.Get_Pot();
POT_DATA[kPlayListVector_DATA[1]] = PlaylistDATA_1G.Get_Pot();


//POT_DATA_Status[kFULL] = PlaylistDATA_1D.Get_Pot();
POT_DATA_Status[kFULL] = PlaylistDATA_1F.Get_Pot();

//POT_DATA_Status[kEMPTY] = PlaylistDATA_1A.Get_Pot();
POT_DATA_Status[kEMPTY] = PlaylistDATA_1G.Get_Pot();

PlayList_INFO PlaylistTRUTH_1F(kPlayListVector_MC[0], true );
PlayList_INFO PlaylistTRUTH_1G(kPlayListVector_MC[1], true );

TFile *PlaylistTRUTH_1F_noangle     = new TFile("/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1F_TRUTH_StatsONLY_nocut.root");


std::cout<< "POT_DATA_Status[kFULL] = "<< POT_DATA_Status[kFULL]<<std::endl;

std::cout<< "POT_DATA_Status[kEMPTY] = "<< POT_DATA_Status[kEMPTY]<<std::endl;


//TFile *Playlist_ME1D_MC     = new TFile(PlaylistME_1D_MC_path);
TFile *Playlist_ME1F_MC     = new TFile(PlaylistME_1F_MC_path);

//TFile *Playlist_ME1A_MC     = new TFile(PlaylistME_1A_MC_path);

TFile *Playlist_ME1G_MC     = new TFile(PlaylistME_1G_MC_path);

TFile *Playlist_ME1F_DATA     = new TFile(PlaylistMC_1F_Data_path);

//TFile *Playlist_ME1D_DATA     = new TFile(PlaylistMC_1D_Data_path);
//TFile *Playlist_ME1A_DATA     = new TFile(PlaylistMC_1A_Data_path);
TFile *Playlist_ME1G_DATA     = new TFile(PlaylistMC_1G_Data_path);


//auto minervame1P_MC = Playlist_MC_1P.TFILE_PLAYLIST;




sprintf(text_title_pdf1, "PLOTS_%s_MuonKinematic_Varibles_CVwithSystmatics.pdf(",timeset_nonstacks );
can -> Print(text_title_pdf1);
sprintf(text_title_pdf2, "PLOTS_%s_MuonKinematic_Varibles_CVwithSystmatics.pdf",timeset_nonstacks );
sprintf(text_title_pdf3, "PLOTS_%s_MuonKinematic_Varibles_CVwithSystmatics.pdf)",timeset_nonstacks );
sprintf(text_title_pdf4, "PLOTS_%s_MuonKinematic_Varibles_CVwithSystmatics",timeset_nonstacks );
 pdf_CV = string(text_title_pdf4);


  std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;

  std::cout<< "  Total Muon "<< std::endl;

  std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;


for(auto Muon_Var: kMuonVaribles_vector_TOTAL ){

  auto histname = GetMuonVarHistName(Muon_Var);
  int n = histname.length();
  char histnameMC_char[n+1];
  strcpy( histnameMC_char,histname.c_str());

  auto histname_data = GetMuonVarHist_DATAName(Muon_Var);
  int n_data = histname_data.length();
  char histnameDATA_char[n_data+1];
  strcpy( histnameDATA_char ,histname_data.c_str());

  auto Emptytitle = GetMuon_Figure_Title(Muon_Var ,kPlayListVector_MC[1] );
  int n_Emptytitle = Emptytitle.length();
  char Emptytitle_char[n_Emptytitle+1];
  strcpy( Emptytitle_char,Emptytitle.c_str());


      auto TITLE = GetMuonVarTitleName(Muon_Var);
      int n_TITLE = TITLE.length();
      char TITLE_char[n_TITLE+1];
      strcpy( TITLE_char,TITLE.c_str());

      std::cout<<"Title:"<< TITLE_char<<std::endl;
      std::cout<<"MC Hist name:"<< histnameMC_char<<std::endl;
      std::cout<<"Data Hist name:"<< histnameDATA_char<<std::endl;

      if(m_CVorStacks==0){
        std::cout<<"making CV"<<std::endl;
        DrawCVAndError_FromTFile(Playlist_ME1F_MC, Playlist_ME1G_MC,  histnameMC_char ,Playlist_ME1F_DATA, Playlist_ME1G_DATA,
          histnameDATA_char, POT_MC_Status, POT_DATA_Status, false, TITLE_char,
          GetMuonVarAXISName(Muon_Var), pdf_CV, true, true ,GetMuonUnitType(Muon_Var), Print_Systematics, my_debug);
      }

}

auto histname = GetMuonVarHistName(kE);
int n = histname.length();
char histnameMC_char[n+1];
strcpy( histnameMC_char,histname.c_str());

//DrawRatio_FromTFile(Playlist_ME1F_MC, Playlist_ME1D_MC_Old,  histnameMC_char,"h_muonE_ECT_0","Muon E Ratio",
//"Muon E [GeV]",pdf_CV , "GeV");

//DrawRatio_FromTFile(Playlist_ME1D_MC_nuEoff, Playlist_ME1D_MC_Old,  histnameMC_char,"h_muonE_ECT_0","Muon E Ratio",
//"Muon E [GeV]",pdf_CV , "GeV");

 can -> Print(text_title_pdf3);
 can->Close();

 sprintf(Latex_name, "PLOTS_%s_Latex_Muon_CV_ERRORS", timeset_nonstacks);




std::string input_Latex_name = Latex_name;

if(m_CVorStacks==0){MakeLatexForMuonFiguresCVandALLErrors(input_Latex_name, kMuonVaribles_vector_TOTAL, pdf_CV, N_Error_groups);}



TCanvas *can_stacks = new TCanvas("can_stacks");


std::cout<< " ~~~~~~~PLOTS_~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;

std::cout<< "  Muon Material Stacks "<< std::endl;

std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;
char text_title_Material_pdf5[2024];
char text_title_Material_pdf6[2024];
char text_title_Material_pdf7[2024];
char text_title_Material_pdf8[2024];

sprintf(text_title_Material_pdf5, "PLOTS_%s_STACKS_Material_Kinematic_Varibles.pdf(",timeset );
can_stacks -> Print(text_title_Material_pdf5);
sprintf(text_title_Material_pdf6, "PLOTS_%s_STACKS_Material_Kinematic_Varibles.pdf",timeset );
sprintf(text_title_Material_pdf7, "PLOTS_%s_STACKS_Material_Kinematic_Varibles.pdf)",timeset );
sprintf(text_title_Material_pdf8, "PLOTS_%s_STACKS_Material_Kinematic_Varibles",timeset );
std::string pdf_stacks_Material = string(text_title_Material_pdf8);


for(auto Muon_Var: kMuonVaribles_vector_STACKS ){


  auto histname = GetMuonVarHistName(Muon_Var);
  int n = histname.length();
  char histnameMC_char[n+1];
  strcpy( histnameMC_char,histname.c_str());

  auto histname_data = GetMuonVarHist_DATAName(Muon_Var);
  int n_data = histname_data.length();
  char histnameDATA_char[n_data+1];
  strcpy( histnameDATA_char ,histname_data.c_str());

        auto TITLE = GetMuonVarTitleName(Muon_Var);
        int n_TITLE = TITLE.length();
        char TITLE_char[n_TITLE+1];
        strcpy( TITLE_char,TITLE.c_str());

if(m_CVorStacks==1){
     DrawSTACKfromHistFilio_FromTFile(Playlist_ME1F_MC, Playlist_ME1G_MC,  histnameMC_char ,Playlist_ME1F_DATA,Playlist_ME1G_DATA,
      histnameDATA_char, POT_MC_Status, POT_DATA_Status, false, TITLE_char,
      GetMuonVarAXISName(Muon_Var), pdf_stacks_Material, true, false ,GetMuonUnitType(Muon_Var), kMaterial, my_debug );
    }


}


 can_stacks -> Print(text_title_Material_pdf7);
 sprintf(Latex_name, "PLOTS_%s_Muon_Latex_stack_Material", timeset);
  input_Latex_name = Latex_name;

 MakeLatexForMuonFiguresFORStacks(input_Latex_name ,kMuonVaribles_vector_STACKS , pdf_stacks_Material );

 std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;

 std::cout<< "  Muon Interaction Stacks "<< std::endl;

 std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;
 char text_title_Interaction_pdf5[2024];
 char text_title_Interaction_pdf6[2024];
 char text_title_Interaction_pdf7[2024];
 char text_title_Interaction_pdf8[2024];

 sprintf(text_title_Interaction_pdf5, "PLOTS_%s_STACKS_Interaction_Kinematic_Varibles.pdf(",timeset );
 can_stacks -> Print(text_title_Interaction_pdf5);
 sprintf(text_title_Interaction_pdf6, "PLOTS_%s_STACKS_Interaction_Kinematic_Varibles.pdf",timeset );
 sprintf(text_title_Interaction_pdf7, "PLOTS_%s_STACKS_Interaction_Kinematic_Varibles.pdf)",timeset );
 sprintf(text_title_Interaction_pdf8, "PLOTS_%s_STACKS_Interaction_Kinematic_Varibles",timeset );
 std::string pdf_stacks_interaction = string(text_title_Interaction_pdf8);


 for(auto Muon_Var: kMuonVaribles_vector_STACKS ){


   auto histname = GetMuonVarHistName(Muon_Var);
   int n = histname.length();
   char histnameMC_char[n+1];
   strcpy( histnameMC_char,histname.c_str());

   auto histname_data = GetMuonVarHist_DATAName(Muon_Var);
   int n_data = histname_data.length();
   char histnameDATA_char[n_data+1];
   strcpy( histnameDATA_char ,histname_data.c_str());

   auto TITLE = GetMuonVarTitleName(Muon_Var);
   int n_TITLE = TITLE.length();
   char TITLE_char[n_TITLE+1];
   strcpy( TITLE_char,TITLE.c_str());

   if(m_CVorStacks==1){
     DrawSTACKfromHistFilio_FromTFile(Playlist_ME1F_MC, Playlist_ME1G_MC,  histnameMC_char ,Playlist_ME1F_DATA,Playlist_ME1G_DATA,
       histnameDATA_char, POT_MC_Status, POT_DATA_Status, false, TITLE_char,
       GetMuonVarAXISName(Muon_Var), pdf_stacks_interaction, true, false ,GetMuonUnitType(Muon_Var), kInteraction, my_debug );
     }


 }


  can_stacks -> Print(text_title_Interaction_pdf7);
  sprintf(Latex_name, "PLOTS_%s_Muon_Latex_stack_Interaction", timeset);
  input_Latex_name = Latex_name;
  MakeLatexForMuonFiguresFORStacks(input_Latex_name ,kMuonVaribles_vector_STACKS , pdf_stacks_interaction );

  std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;

  std::cout<< "  Muon Particle Stacks "<< std::endl;

  std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;
  char text_title_Particle_pdf5[2024];
  char text_title_Particle_pdf6[2024];
  char text_title_Particle_pdf7[2024];
  char text_title_Particle_pdf8[2024];

  sprintf(text_title_Particle_pdf5, "PLOTS_%s_STACKS_Particle_Kinematic_Varibles.pdf(",timeset );
  can_stacks -> Print(text_title_Particle_pdf5);
  sprintf(text_title_Particle_pdf6, "PLOTS_%s_STACKS_Particle_Kinematic_Varibles.pdf",timeset );
  sprintf(text_title_Particle_pdf7, "PLOTS_%s_STACKS_Particle_Kinematic_Varibles.pdf)",timeset );
  sprintf(text_title_Particle_pdf8, "PLOTS_%s_STACKS_Particle_Kinematic_Varibles",timeset );
  std::string pdf_stacks_Particle = string(text_title_Particle_pdf8);


  for(auto Muon_Var: kMuonVaribles_vector_STACKS ){


    auto histname = GetMuonVarHistName(Muon_Var);
    int n = histname.length();
    char histnameMC_char[n+1];
    strcpy( histnameMC_char,histname.c_str());

    auto histname_data = GetMuonVarHist_DATAName(Muon_Var);
    int n_data = histname_data.length();
    char histnameDATA_char[n_data+1];
    strcpy( histnameDATA_char ,histname_data.c_str());

          auto TITLE = GetMuonVarTitleName(Muon_Var);
          int n_TITLE = TITLE.length();
          char TITLE_char[n_TITLE+1];
          strcpy( TITLE_char,TITLE.c_str());

if(m_CVorStacks==1){
       DrawSTACKfromHistFilio_FromTFile(Playlist_ME1F_MC, Playlist_ME1G_MC,  histnameMC_char ,Playlist_ME1F_DATA,Playlist_ME1G_DATA,
        histnameDATA_char, POT_MC_Status, POT_DATA_Status, false, TITLE_char,
        GetMuonVarAXISName(Muon_Var), pdf_stacks_Particle, true, false ,GetMuonUnitType(Muon_Var), kParticle, my_debug );
}


  }


if(m_CVorStacks==1){

  //DrawSTACKfromHistFilio_FromTFile(Playlist_ME1F_MC, Playlist_ME1G_MC,  "h_secTrk_MidTheta_leading" ,Playlist_ME1F_DATA,Playlist_ME1G_DATA,
   //histnameDATA_char, POT_MC_Status, POT_DATA_Status, false, "leading non-muon Trk Angle",
   //GetMuonVarAXISName(kThetamid), pdf_stacks_Particle, true, false ,GetMuonUnitType(kThetamid), kParticle, my_debug );

   //DrawSTACKfromHistFilio_FromTFile(Playlist_ME1F_MC, Playlist_ME1G_MC,  "h_secTrk_MidTheta_Nonleading" ,Playlist_ME1F_DATA,Playlist_ME1G_DATA,
    //histnameDATA_char, POT_MC_Status, POT_DATA_Status, false, "Non-leading non-muon Trk Angle",
    //GetMuonVarAXISName(kThetamid), pdf_stacks_Particle, true, false ,GetMuonUnitType(kThetamid), kParticle, my_debug );



Hist_phyiscs_map MAP_stack =  Make_Physics_distribution_map_FromTFile(Playlist_ME1F_MC, "h_MuonCharge" , false, 1.0, kPlayListVector_MC[0], true );
Hist_phyiscs_map MAP_stack_G =  Make_Physics_distribution_map_FromTFile(Playlist_ME1G_MC, "h_MuonCharge" , false, 1.0, kPlayListVector_MC[1], true );

//Hist_phyiscs_map MAP_stack_F_leading =  Make_Physics_distribution_map_FromTFile(Playlist_ME1F_MC, "h_MuonCharge" , false, 1.0, kPlayListVector_MC[0], true );
//Hist_phyiscs_map MAP_stack_G =  Make_Physics_distribution_map_FromTFile(Playlist_ME1G_MC, "h_MuonCharge" , false, 1.0, kPlayListVector_MC[1], true );



Hist_phyiscs_map MAP_stack_TRUTH =  Make_Physics_distribution_map_FromTFile(PlaylistTRUTH_1F.TFILE_PLAYLIST ,"h_MuonE_TRUE" , false, 1.0, kPlayListVector_MC[0], true );
Hist_phyiscs_map MAP_stack_G_TRUTH =  Make_Physics_distribution_map_FromTFile(PlaylistTRUTH_1G.TFILE_PLAYLIST ,"h_MuonE_TRUE" , false, 1.0, kPlayListVector_MC[1], true );



//Hist_phyiscs_map MAP_stack_TRUTH_noangle =  Make_Physics_distribution_map_FromTFile(PlaylistTRUTH_1F_noangle,"h_MuonE_TRUE" , false, 1.0, kPlayListVector_MC[0], true );


bool IsReco = true;
bool IsTruth = false;

DrawPieFigures(MAP_stack,  text_title_Particle_pdf8, can_stacks, mnv_plot,IsReco);
DrawPieFigures(MAP_stack_G,  text_title_Particle_pdf8, can_stacks, mnv_plot,IsReco);

DrawPieFigures(MAP_stack_TRUTH ,  text_title_Particle_pdf8, can_stacks, mnv_plot,IsTruth);
DrawPieFigures(MAP_stack_G_TRUTH ,  text_title_Particle_pdf8, can_stacks, mnv_plot,IsTruth);

//DrawPieFigures(MAP_stack_TRUTH_noangle ,  text_title_Particle_pdf8, can_stacks, mnv_plot,IsTruth);




}


can_stacks -> Print(text_title_Particle_pdf7);
sprintf(Latex_name, "PLOTS_%s_Muon_Latex_stack_Particle", timeset);
input_Latex_name = Latex_name;
if(m_CVorStacks==1){MakeLatexForMuonFiguresFORStacks(input_Latex_name ,kMuonVaribles_vector_STACKS , pdf_stacks_Particle );
}



std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;

std::cout<< " Done with Muon Plots"<< std::endl;

std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;


//sprintf(Latex_name, "PLOTS_%s_Muon_Latex_CV_and_Stacks", timeset);
 //input_Latex_name = Latex_name;

 //MakeLatexForMuonFiguresCVandGroupErrors_andALLSTACKS(Print_Systematics ,input_Latex_name,
  // kMuonVaribles_vector_STACKS, pdf_CV, pdf_stacks_Material, pdf_stacks_interaction,
  // pdf_stacks_Particle, N_Error_groups);


   std::cout << std::endl;
   std::cout << "Done WITH Stacks" << std::endl;



   std::cout << "lastline" << std::endl;

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





}//end of
