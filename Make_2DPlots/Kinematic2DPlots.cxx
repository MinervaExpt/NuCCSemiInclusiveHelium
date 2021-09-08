#include "Kinematic2DPlots.h"

std::vector<Muon2DVar> GetMUON2DVaribles_vector();
std::vector<ME_helium_Playlists> GetPlayListVector_MC();
std::vector<ME_helium_Playlists> GetPlayListVector_DATA();

void MakeLatexForMuonFiguresCVandALLErrors(std::string output_name, std::vector<MuonVar> muon_vector,  std::string PDF_cv_name, int NError_Groups);
void MakeLatexForMuonFiguresFORStacks(std::string output_name ,std::vector<MuonVar> muon_vector ,  std::string pdf_name);
std::string Playlist_INFO(int type,char *FullPlaylist, char *EmptyPlaylist);
void MakeLatexForMuonFiguresFOR2DVar(std::string output_name, Muon2DVar muon ,  std::string pdf_name, bool type1or2, bool m_debug, char *FullPlaylist, char *EmptyPlaylist);
void Kin(bool &cutsOn, bool &my_norm, bool &my_debug, const char *userDir, bool &BinNorm , int &Print_Systematics ) {
TH1::AddDirectory(false);
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~       Starting Plotter: Kinematic Plots         ~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;


const std::vector<ME_helium_Playlists> kPlayListVector_MC = GetPlayListVector_MC();
const std::vector<ME_helium_Playlists> kPlayListVector_DATA = GetPlayListVector_DATA();
const std::vector<Muon2DVar> kMuon2DVaribles_vector  = GetMUON2DVaribles_vector();
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
 sprintf(timeset_nonstacks,"%i_%i_%i_%i_%s", 1 + ltm->tm_mon,ltm->tm_mday, ltm->tm_hour,ltm->tm_min, SysError_printLabel.c_str());
 sprintf(timeset, "%i_%i_%i_%i", 1 + ltm->tm_mon,ltm->tm_mday, ltm->tm_hour,ltm->tm_min);


//PlayList_INFO Playlist_MC_1G(kPlayListVector_MC[0], is_mc );


//auto PlaylistME_1D_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1D_MC_All_SysErrorsOn.root";

//auto PlaylistME_1A_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1A_MC_All_SysErrorsOn.root";
//auto PlaylistME_1G_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1G_MC_All_SysErrorsOn.root";

auto PlaylistME_1F_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2Dminervame1F_MC_All_SysErrorsOn.root";
auto PlaylistME_1G_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2Dminervame1G_MC_All_SysErrorsOn.root";
//auto PlaylistME_1G_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1G_MC_StatsONLYErrors.root";



//auto PlaylistMC_1D_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1D_Data.root";
auto PlaylistMC_1F_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_2Dminervame1F_Data.root";

//auto PlaylistMC_1A_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1A_Data.root";
auto PlaylistMC_1G_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_2Dminervame1G_Data.root";



bool is_mc=true;bool isNOT_mc=false;


std::string pdf_CV = string(text_title_pdf4);

//PlayList_INFO Playlist_MC_1G(kPlayListVector_MC[0], is_mc );
//PlayList_INFO PlaylistMC_1D(kPlayListVector_MC[0], true, false );
//PlayList_INFO PlaylistMC_1A(kPlayListVector_MC[1], true, false );
//PlayList_INFO PlaylistMC_1G(kPlayListVector_MC[1], true, false );
//PlayList_INFO PlaylistTRUTH_1D(kPlayListVector_MC[0], true );
//PlayList_INFO PlaylistTRUTH_1A(kPlayListVector_MC[1], true );

 bool Stats_only = true;
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

std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;

std::cout<< "  Total Muon "<< std::endl;

std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;
sprintf(text_title_pdf1, "PLOTS_%s_MuonK_2DVar.pdf(",timeset_nonstacks );
//can -> Print(text_title_pdf1);
sprintf(text_title_pdf2, "PLOTS_%s_MuonK_2DVar.pdf",timeset_nonstacks );
sprintf(text_title_pdf3, "PLOTS_%s_MuonK_2DVar.pdf)",timeset_nonstacks );
//sprintf(text_title_pdf4, "PLOTS_%s_MuonK_2DVar",timeset_nonstacks );
 //pdf_CV = string(text_title_pdf4);

for(auto Muon_2DVar: kMuon2DVaribles_vector ){

  auto histname = GetMuon2DVarHistName(Muon_2DVar);
  char histnameMC_char[histname.length()+1];
  strcpy( histnameMC_char,histname.c_str());

  auto histname_data = GetMuon2DVarHist_DATAName(Muon_2DVar);
  char histnameDATA_char[histname_data.length()+1];
  strcpy( histnameDATA_char ,histname_data.c_str());

      auto TITLE = GetMuon2DVar_Title(Muon_2DVar);
      char TITLE_char[TITLE.length()+1];
      strcpy( TITLE_char,TITLE.c_str());

      auto Xaxis =GetMuon2DVar_XaxisTitle(Muon_2DVar);
      char Xaxis_char[Xaxis.length()+1];
      strcpy( Xaxis_char,Xaxis.c_str());

      auto Yaxis =GetMuon2DVar_YaxisTitle(Muon_2DVar);
      char Yaxis_char[Yaxis.length()+1];
      strcpy(Yaxis_char,Yaxis.c_str());

      auto pdf_title =  GetMuon2DVar_pdf(Muon_2DVar);
      char pdf_title_char[pdf_title.length()+1];
      strcpy(pdf_title_char, pdf_title.c_str() );

      auto Units =   GetMuon2DVar_yaxisUnits(Muon_2DVar);
      char Units_char[Units.length()+1];
      strcpy(Units_char, Units.c_str() );

      sprintf(text_title_pdf4, "PLOTS_%s_Muon_%s_2DVar",timeset_nonstacks, pdf_title_char );
      pdf_CV = string(text_title_pdf4);


      std::cout<<"Title:"<< TITLE_char<<std::endl;
      std::cout<<"MC Hist name:"<< histnameMC_char<<std::endl;
      std::cout<<"Data Hist name:"<< histnameDATA_char<<std::endl;


    Draw2DCVAndError_FromTFile(Playlist_ME1F_MC, Playlist_ME1G_MC,  histnameMC_char ,Playlist_ME1F_DATA, Playlist_ME1G_DATA,
      histnameDATA_char, POT_MC_Status, POT_DATA_Status, false, TITLE_char,Yaxis_char, Xaxis_char, Units, pdf_CV, true, false ,Print_Systematics, my_debug);

    DrawSTACKfromHistFilio_FromTFile2D(Playlist_ME1F_MC, Playlist_ME1G_MC,  histnameMC_char ,Playlist_ME1F_DATA,Playlist_ME1G_DATA,
      histnameDATA_char, POT_MC_Status, POT_DATA_Status, false, TITLE_char, Yaxis_char, Xaxis_char, Units_char, pdf_CV,
      true, false,  kMaterial,  my_debug );

    DrawSTACKfromHistFilio_FromTFile2D(Playlist_ME1F_MC, Playlist_ME1G_MC,  histnameMC_char ,Playlist_ME1F_DATA,Playlist_ME1G_DATA,
      histnameDATA_char, POT_MC_Status, POT_DATA_Status, false, TITLE_char, Yaxis_char, Xaxis_char, Units_char, pdf_CV,
      true, false,  kInteraction,  my_debug );

    DrawSTACKfromHistFilio_FromTFile2D(Playlist_ME1F_MC, Playlist_ME1G_MC,  histnameMC_char ,Playlist_ME1F_DATA,Playlist_ME1G_DATA,
      histnameDATA_char, POT_MC_Status, POT_DATA_Status, false, TITLE_char, Yaxis_char, Xaxis_char, Units_char, pdf_CV,
      true, false,  kParticle,  my_debug );

      auto Mig_Names = GetMuon2DVar_ReponseHistTitle_vector(Muon_2DVar);

      char Mig_char[Mig_Names[0].length()+1];
      strcpy(Mig_char, Mig_Names[0].c_str() );

      char Reco_char[Mig_Names[1].length()+1];
      strcpy(Reco_char, Mig_Names[1].c_str() );

      char Truth_char[Mig_Names[2].length()+1];
      strcpy(Truth_char, Mig_Names[2].c_str() );

      auto Full_playlist_name = GetPlaylist_InitialName(kPlayListVector_MC[0]);
      auto Empty_playlist_name = GetPlaylist_InitialName(kPlayListVector_MC[1]);

      char Full_playlist_name_char[Full_playlist_name.length()+1];
      strcpy(Full_playlist_name_char, Full_playlist_name.c_str() );

      char Empty_playlist_name_char[Empty_playlist_name.length()+1];
      strcpy(Empty_playlist_name_char, Empty_playlist_name.c_str() );

     Draw2D_Migration_FromTFile(Playlist_ME1F_MC, Playlist_ME1G_MC,  Mig_char,Reco_char, Truth_char,
       POT_MC_Status, TITLE_char,Full_playlist_name_char, Empty_playlist_name_char, Xaxis_char, Yaxis_char,
         Units_char, pdf_CV, false ,my_debug);


         MakeLatexForMuonFiguresFOR2DVar(pdf_CV, Muon_2DVar ,  pdf_CV, false, true,Full_playlist_name_char, Empty_playlist_name_char);


}






auto histname = GetMuonVarHistName(kE);
int n = histname.length();
char histnameMC_char[n+1];
strcpy( histnameMC_char,histname.c_str());


 can -> Print(text_title_pdf3);
 can->Close();

 sprintf(Latex_name, "PLOTS_%s_Latex_Muon_CV_ERRORS", timeset_nonstacks);
 std::string input_Latex_name = Latex_name;
 std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;

std::cout<< " Done with Muon "<< std::endl;

std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;


sprintf(Latex_name, "PLOTS_%s_Muon_Latex_CV_and_Stacks", timeset);
 input_Latex_name = Latex_name;

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

const char *inputFileLoc = input.c_str();

Kin(cutsOn, my_norm, my_debug, inputFileLoc, my_BinNormilzed, my_Print_Systmatics);

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
std::vector<Muon2DVar> GetMUON2DVaribles_vector() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<Muon2DVar> Muon2D_vector;
  //Muon2D_vector.push_back(kPT_PZ);
  //Muon2D_vector.push_back(kPT_theta);
  //Muon2D_vector.push_back(kPZ_theta);
  //Muon2D_vector.push_back(kE_theta);
  //Muon2D_vector.push_back(kE_PZ);
  //Muon2D_vector.push_back(kE_PT);
  Muon2D_vector.push_back(kVertex_Z_R);

  return Muon2D_vector;
//#endif
}




void MakeLatexForMuonFiguresFORStacks(std::string output_name ,std::vector<MuonVar> muon_vector ,  std::string pdf_name){
  double scale= .23;
  std::ofstream myfile;
  string fileName = output_name + ".txt";
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

   int Column_Spacing;
   int pageCount=2;
   if(NError_Groups==2||NError_Groups==1){

     Column_Spacing = NError_Groups + 2;
   }
   else if (NError_Groups==0){

     Column_Spacing = NError_Groups + 1;}



  string fileName = output_name + ".txt";
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
    myfile<<Muon_latex_Latex.GetInclude_figure(pageCount + Column_Spacing+ Column_Spacing, PDF_cv_name)<< "\n";
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

  string fileName = output_name + ".txt";
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


std::string Playlist_INFO(int type,char *FullPlaylist, char *EmptyPlaylist){

std::string  playlist;

if(type==0){
std::string Playlist_full(FullPlaylist);
playlist = "(F)["+ Playlist_full + "]";
 }
else if(type==1){
std::string Playlist_Empty(EmptyPlaylist);
  playlist = "(E)["+ Playlist_Empty + "]";
}
else if(type==2){
  std::string Playlist_full(FullPlaylist);
  std::string Playlist_Empty(EmptyPlaylist);
  playlist = "(F-E)["+ Playlist_full + " - "+ Playlist_Empty + "]";

}
else {playlist ="";}

return playlist;
}


void MakeLatexForMuonFiguresFOR2DVar(std::string output_name, Muon2DVar var2D ,  std::string pdf_name, bool type1or2, bool m_debug, char *FullPlaylist, char *EmptyPlaylist ){
  double scale= .6;
  std::ofstream myfile;
  string fileName = output_name + "_LatexFormat.txt";
  myfile.open(fileName,	std::ios::trunc);
  std::cout<<"Name of Output File "<< fileName<<std::endl;
  LatexFormat Muon_latex_Latex(scale);
  std::vector<bool> projectionsXorY = {true,false};
  std::vector<int> FullorEmpty = {0,1,2};
  int pageCount = 2;
  std::cout << " Name of input PDF = "<< pdf_name << std::endl;

  std::vector<std::string> StacksXProjection_pdf;
  std::vector<std::string> StacksYProjection_pdf;
  std::vector<std::string> nonStacksXProjection_pdf;
  std::vector<std::string> nonStacksYProjection_pdf;
  std::string Mig_pdf;
  Mig_pdf = pdf_name + Construct_string_Ending(true,true,"material", projectionsXorY[0], 0, true );

for(auto cat:FullorEmpty){
  StacksXProjection_pdf.push_back(pdf_name + Construct_string_Ending(false,true,"material", projectionsXorY[0],cat, true ));
}
for(auto cat:FullorEmpty){
  StacksXProjection_pdf.push_back(pdf_name + Construct_string_Ending(false,true,"interaction", projectionsXorY[0],cat, true ));
}
for(auto cat:FullorEmpty){
  StacksXProjection_pdf.push_back(pdf_name + Construct_string_Ending(false,true,"Particle", projectionsXorY[0],cat, true ));
}

for(auto cat:FullorEmpty){
  StacksYProjection_pdf.push_back(pdf_name + Construct_string_Ending(false,true,"material", projectionsXorY[1],cat, true ));
}
for(auto cat:FullorEmpty){
  StacksYProjection_pdf.push_back(pdf_name + Construct_string_Ending(false,true,"interaction", projectionsXorY[1],cat, true ));
}
for(auto cat:FullorEmpty){
  StacksYProjection_pdf.push_back(pdf_name + Construct_string_Ending(false,true,"Particle", projectionsXorY[1],cat, true ));
}

for(auto cat:FullorEmpty){
nonStacksXProjection_pdf.push_back(pdf_name + Construct_string_Ending(false, false, "", projectionsXorY[0],cat, type1or2 ));
}

for(auto cat:FullorEmpty){
nonStacksYProjection_pdf.push_back(pdf_name + Construct_string_Ending(false, false, "", projectionsXorY[1],cat, type1or2 ));
}

if(m_debug==true){
std::cout<< " Mig name = "<< Mig_pdf<< std::endl;
std::cout<<" xprojection Stacke Pdf Names: "<< std::endl;
for(auto cat :StacksXProjection_pdf ){std::cout<<" Stacke xprojection Pdf Names:  "<< cat<<std::endl; }
std::cout<<"yprojection stacks Pdf Names: "<< std::endl;
for(auto cat :StacksYProjection_pdf ){std::cout<<" Stacke yprojection Pdf Names:  "<< cat<<std::endl; }

std::cout<<"XProjection Pdf Names: "<< std::endl;
for(auto cat : nonStacksXProjection_pdf){std::cout<<" xprojection  Pdf Names:  "<< cat<<std::endl; }
std::cout<<"YProjection Pdf Names: "<< std::endl;
for(auto cat : nonStacksYProjection_pdf){std::cout<<" yprojection  Pdf Names:  "<< cat<<std::endl; }

}

std::string Var_name = GetMuon2DVar_Title(var2D);
myfile<<"\n";
myfile<<"%%%%%%%%%%%%%%%%% \n";
myfile<<"%%%  2d For X Projection  "<< Var_name <<"\n";
myfile<<"%%%%%%%%%%%%%%%%% \n";
myfile<<Muon_latex_Latex.GetSubSection(Var_name);
myfile<<"%%%%%%%%%%%%%%%%% \n";
int playlist=0;
  for(auto cat: nonStacksXProjection_pdf){
    std::string playlist_info = "[Xprojection]Event Distrubution" + Playlist_INFO(playlist,FullPlaylist, EmptyPlaylist);
    myfile<<Muon_latex_Latex.GetBeginFrame(playlist_info)<< "\n";
    myfile<<Muon_latex_Latex.GetCentering() <<" \n";
    myfile<<Muon_latex_Latex.GetBeginTabular()<< "\n";
    myfile<<Muon_latex_Latex.GetInclude_figure(cat)<< "\n";
    myfile<<Muon_latex_Latex.GetEndTabular()<< "\n";
    myfile<<Muon_latex_Latex.GetEndFrame();
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% END FRAME "<< Var_name<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    playlist++;
  }
  playlist=0;

  for(auto cat: StacksXProjection_pdf){
    std::string playlist_info = "[Xprojection]Stack" + Playlist_INFO(playlist, FullPlaylist, EmptyPlaylist);
    myfile<<Muon_latex_Latex.GetBeginFrame(playlist_info)<< "\n";
    myfile<<Muon_latex_Latex.GetCentering() <<" \n";
    myfile<<Muon_latex_Latex.GetBeginTabular()<< "\n";
    myfile<<Muon_latex_Latex.GetInclude_figure(cat)<< "\n";
    myfile<<Muon_latex_Latex.GetEndTabular()<< "\n";
    myfile<<Muon_latex_Latex.GetEndFrame();
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% END FRAME Stack "<< Var_name<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    playlist++;
    if(playlist==3){playlist=0;}
  }

  myfile<<"\n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<"%%%  2d For  Y Projection"<< Var_name <<"\n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<" \n";
    playlist=0;
    for(auto cat: nonStacksYProjection_pdf){
      myfile<<" \n";
      std::string playlist_info = "Event Distrubution" + Playlist_INFO(playlist, FullPlaylist, EmptyPlaylist);
      myfile<<Muon_latex_Latex.GetBeginFrame(playlist_info)<< "\n";
      myfile<<Muon_latex_Latex.GetCentering() <<" \n";
      myfile<<Muon_latex_Latex.GetBeginTabular()<< "\n";
      myfile<<Muon_latex_Latex.GetInclude_figure(cat)<< "\n";
      myfile<<Muon_latex_Latex.GetEndTabular()<< "\n";
      myfile<<Muon_latex_Latex.GetEndFrame();
      myfile<<"\n";
      myfile<<"%%%%%%%%%%%%%%%%% \n";
      myfile<<"%%% END FRAME  "<< Var_name<<"\n";
      myfile<<"%%%%%%%%%%%%%%%%% \n";
      playlist++;
    }
    playlist=0;
    for(auto cat: StacksYProjection_pdf){
      std::string playlist_info = "[Y]projection]Stack" + Playlist_INFO(playlist, FullPlaylist, EmptyPlaylist);
      myfile<<Muon_latex_Latex.GetBeginFrame(playlist_info)<< "\n";
      myfile<<Muon_latex_Latex.GetCentering() <<" \n";
      myfile<<Muon_latex_Latex.GetBeginTabular()<< "\n";
      myfile<<Muon_latex_Latex.GetInclude_figure(cat)<< "\n";
      myfile<<Muon_latex_Latex.GetEndTabular()<< "\n";
      myfile<<Muon_latex_Latex.GetEndFrame();
      myfile<<"\n";
      myfile<<"%%%%%%%%%%%%%%%%% \n";
      myfile<<"%%% END FRAME Stack "<< Var_name<<"\n";
      myfile<<"%%%%%%%%%%%%%%%%% \n";
      myfile<<" \n";
      playlist++;
      if(playlist==3){playlist=0;}
    }

    myfile<<" \n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% Beging Migration"<< Var_name<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";

    myfile<<" \n";
    playlist=0;
    std::vector <int> page_2dmigration= {1,8,15};
    for(auto page: page_2dmigration){
      myfile<<" \n";
      std::string playlist_info = "Migration " + Playlist_INFO(playlist, FullPlaylist, EmptyPlaylist);
      myfile<<Muon_latex_Latex.GetBeginFrame(" ")<< "\n";
      myfile<<Muon_latex_Latex.GetCentering() <<" \n";
      myfile<<Muon_latex_Latex.GetBeginTabular()<< "\n";
      myfile<<Muon_latex_Latex.GetInclude_figure(page, Mig_pdf, .5)<< "\n";
      myfile<<Muon_latex_Latex.GetEndTabular()<< "\n";
      myfile<<Muon_latex_Latex.GetEndFrame();
      myfile<<"\n";
      myfile<<"%%%%%%%%%%%%%%%%% \n";
      myfile<<"%%% END FRAME Stack "<< Var_name<<"\n";
      myfile<<"%%%%%%%%%%%%%%%%% \n";
      myfile<<" \n";
      playlist++;
    }





  myfile.close();
}//end of Function
