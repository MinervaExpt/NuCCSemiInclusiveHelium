#include "Make_CrossSection_Plots.h"

CrossSection_name_Map Generate_CrossSection_histsNames_withInteraction(MuonVar MuonVar_type, std::string playlist, bool isFUll);
CrossSection_name_Map Generate_CrossSection_histsNames_withInteraction_DISbreakdown(MuonVar MuonVar_type, std::string playlist, bool isFUll);
std::vector<ME_helium_Playlists> GetTrackerPlayListVector();
///////////////////////////////////////////////////
///// Do all function
//////////////////////////////////////////////////
void Kin( bool &my_norm, bool &my_debug, bool &BinNorm , int &Print_Systematics ) {
TH1::AddDirectory(false);

const std::vector<ME_helium_Playlists> kPlayListVector_MC = GetPlayListVector();
int N_Error_groups;
if(Print_Systematics==2 || Print_Systematics == 1) {N_Error_groups=0;}
else if (Print_Systematics==0){N_Error_groups=7;}


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

auto PlaylistME_CrossSection_Path = "/minerva/app/users/cnguyen/cmtuser/Minerva_v22r1p1Helium_GIT/NuCCSemiInclusiveHelium/Make_CrossSection/CrossSection.root";
bool is_mc=true;bool isNOT_mc=false;
std::string pdf_CV = string(text_title_pdf4);
bool Stats_only = false;


auto PlaylistME_CrossSection_GENIE_version_Path = "/minerva/app/users/cnguyen/cmtuser/Minerva_v22r1p1Helium_GIT/NuCCSemiInclusiveHelium/Make_CrossSection/CrossSection_MK.root";






//Different Models

auto GENIE_G18_02a_02_11a_playlistPath ="/minerva/app/users/cnguyen/cmtuser/Minerva_v22r1p1Helium_GIT/NuCCSemiInclusiveHelium/eventselection2D/CrossSection_G18_02a_02_11a_new10.root";
auto GENIE_G18_10a_02_11a_playlistPath ="/minerva/app/users/cnguyen/cmtuser/Minerva_v22r1p1Helium_GIT/NuCCSemiInclusiveHelium/eventselection2D/CrossSection_G18_10b_02_11a_new10.root";
auto GENIE_G18_02b_02_11a_playlistPath ="/minerva/app/users/cnguyen/cmtuser/Minerva_v22r1p1Helium_GIT/NuCCSemiInclusiveHelium/eventselection2D/CrossSection_G18_10a_02_11a_new10.root";
auto GENIE_G18_10b_02_11a_playlistPath ="/minerva/app/users/cnguyen/cmtuser/Minerva_v22r1p1Helium_GIT/NuCCSemiInclusiveHelium/eventselection2D/CrossSection_G18_02b_02_11a_new10.root";

Model_RootPathMAP Model_Paths;
Model_Paths.insert(std::make_pair(kME_GENIE_G18_02a_02_11a,GENIE_G18_02a_02_11a_playlistPath));
Model_Paths.insert(std::make_pair(kME_GENIE_G18_10a_02_11a,GENIE_G18_10a_02_11a_playlistPath));
Model_Paths.insert(std::make_pair(kME_GENIE_G18_02b_02_11a,GENIE_G18_02b_02_11a_playlistPath));
Model_Paths.insert(std::make_pair(kME_GENIE_G18_10b_02_11a,GENIE_G18_10b_02_11a_playlistPath));


Genie_Models PT_GenieModel("pt",Model_Paths);
Genie_Models PZ_GenieModel("pz",Model_Paths);
Genie_Models EGenieModel("E",Model_Paths);
Genie_Models AngleGenieModel("Angle",Model_Paths);


sprintf(text_title_pdf1, "PLOTS_%s_CrossSection_FullStats.pdf(","" );
can -> Print(text_title_pdf1);
sprintf(text_title_pdf2, "PLOTS_%s_CrossSection_FullStats.pdf","" );
sprintf(text_title_pdf3, "PLOTS_%s_CrossSection_FullStats.pdf)","" );
sprintf(text_title_pdf4, "PLOTS_%s_CrossSection_FullStats","" );
 pdf_CV = string(text_title_pdf4);

  std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;
  std::cout<< "  Ploting 1D Cross Section "<< std::endl;
  std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;

double FULL_POT_DATA = 4.96441e+20;
double FULL_POT_MC = 4.75655e+21;


std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~       Starting Plotter: Kinematic Plots         ~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

TFile *TFile_CrossSection = new TFile(PlaylistME_CrossSection_Path);

auto muon_vector = GetMUONVaribles_Total();
bool isFull = true;
bool isEmpty = false;
bool DoBinWidthNorm = true;
bool Makelog = false;
auto muonE_full_names = Generate_CrossSection_histsNames_withInteraction_DISbreakdown(muon_vector[0], "Full", isFull);
auto muonE_Empty_names = Generate_CrossSection_histsNames_withInteraction_DISbreakdown(muon_vector[0], "Empty", isEmpty);
auto Map_MuonE_Full_hist = Generate_CrossSection_Hist_Map(*TFile_CrossSection, muonE_full_names);
auto Map_MuonE_Empty_hist = Generate_CrossSection_Hist_Map(*TFile_CrossSection, muonE_Empty_names);
auto MuonE_Mig = Get2DHist(*TFile_CrossSection, muonE_full_names[mvnreponse_Mig]);

DrawMagration_heatMap_Label(MuonE_Mig, "RECO E_{#mu}","TRUTH E_{#mu}",  "Migration E_{#mu}", text_title_pdf2, can, mnv_plot, 9);
DrawMagration_heatMap_Label(MuonE_Mig, "RECO E_{#mu}","TRUTH E_{#mu}",  "Migration E_{#mu} (ROWNorm)", text_title_pdf2, can, mnv_plot, 3);


MakeCrossSectionPlots_Interaction(Map_MuonE_Full_hist, Map_MuonE_Empty_hist, "GeV", pdf_CV,Makelog,DoBinWidthNorm ,muon_vector[0], "F-E" ,FULL_POT_DATA, FULL_POT_MC, EGenieModel);
//Migration_MnvH2D_Map MigHist = Generate_CrossSection_Mig_Hist_Map(*TFile_CrossSection,muon_vector);


PrintCrossSection_MapName(muonE_full_names,"muonE_full_names");
PrintCrossSection_MapName(muonE_Empty_names,"muonE_Empty_names");

auto muonPZ_full_names = Generate_CrossSection_histsNames_withInteraction_DISbreakdown(muon_vector[1], "Full", isFull);
auto muonPZ_Empty_names = Generate_CrossSection_histsNames_withInteraction_DISbreakdown(muon_vector[1], "Empty", isEmpty);


auto Map_MuonPZ_Full_hist = Generate_CrossSection_Hist_Map(*TFile_CrossSection, muonPZ_full_names);
auto Map_MuonPZ_Empty_hist = Generate_CrossSection_Hist_Map(*TFile_CrossSection, muonPZ_Empty_names);

auto MuonPZ_Mig = Get2DHist(*TFile_CrossSection, muonPZ_full_names[mvnreponse_Mig]);

DrawMagration_heatMap_Label(MuonPZ_Mig, "RECO P_{Z}","TRUTH P_{Z}",  "Migration P_{Z}", text_title_pdf2, can, mnv_plot, 9);
DrawMagration_heatMap_Label(MuonPZ_Mig, "RECO P_{Z}","TRUTH P_{Z}",  "Migration P_{Z} (ROWNorm)", text_title_pdf2, can, mnv_plot, 3);

MakeCrossSectionPlots_Interaction(Map_MuonPZ_Full_hist, Map_MuonPZ_Empty_hist, "GeV", pdf_CV,Makelog,DoBinWidthNorm ,muon_vector[1], "F-E", FULL_POT_DATA, FULL_POT_MC, PZ_GenieModel);




auto muonPT_full_names = Generate_CrossSection_histsNames_withInteraction_DISbreakdown(muon_vector[2], "Full", isFull);
auto muonPT_Empty_names = Generate_CrossSection_histsNames_withInteraction_DISbreakdown(muon_vector[2], "Empty", isEmpty);
auto Map_MuonPT_Full_hist = Generate_CrossSection_Hist_Map(*TFile_CrossSection, muonPT_full_names);
auto Map_MuonPT_Empty_hist = Generate_CrossSection_Hist_Map(*TFile_CrossSection, muonPT_Empty_names);

auto MuonPT_Mig = Get2DHist(*TFile_CrossSection, muonPT_full_names[mvnreponse_Mig]);

DrawMagration_heatMap_Label(MuonPT_Mig, "RECO P_{T}","TRUTH P_{T}",  "Migration P_{T}", text_title_pdf2, can, mnv_plot, 9);
DrawMagration_heatMap_Label(MuonPT_Mig, "RECO P_{T}","TRUTH P_{T}",  "Migration P_{T} (ROWNorm)", text_title_pdf2, can, mnv_plot, 3);



MakeCrossSectionPlots_Interaction(Map_MuonPT_Full_hist, Map_MuonPT_Empty_hist, "GeV", pdf_CV,Makelog,DoBinWidthNorm ,muon_vector[2], "F-E", FULL_POT_DATA, FULL_POT_MC, PT_GenieModel);



auto muonTheta_full_names = Generate_CrossSection_histsNames_withInteraction_DISbreakdown(muon_vector[3], "Full", isFull);
auto muonTheta_Empty_names = Generate_CrossSection_histsNames_withInteraction_DISbreakdown(muon_vector[3], "Empty", isEmpty);
auto Map_MuonTheta_Full_hist = Generate_CrossSection_Hist_Map(*TFile_CrossSection, muonTheta_full_names);
auto Map_MuonTheta_Empty_hist = Generate_CrossSection_Hist_Map(*TFile_CrossSection, muonTheta_Empty_names);

auto MuonTheta_Mig = Get2DHist(*TFile_CrossSection, muonTheta_full_names[mvnreponse_Mig]);

DrawMagration_heatMap_Label(MuonTheta_Mig, "RECO #theta_{#theta}","TRUTH #theta_{#theta}",  "Migration #theta_{#theta}", text_title_pdf2, can, mnv_plot, 9);
DrawMagration_heatMap_Label(MuonTheta_Mig, "RECO #theta_{#theta}","TRUTH #theta_{#theta}",  "Migration #theta_{#theta} (ROWNorm)", text_title_pdf2, can, mnv_plot, 3);


MakeCrossSectionPlots_Interaction(Map_MuonTheta_Full_hist, Map_MuonTheta_Empty_hist, "Deg", pdf_CV,Makelog,DoBinWidthNorm ,muon_vector[3], "F-E", FULL_POT_DATA, FULL_POT_MC, AngleGenieModel);



 can -> Print(text_title_pdf3);
 can->Close();

 sprintf(Latex_name, "PLOTS_%s_Latex_Muon_CV_ERRORS", timeset_nonstacks);





std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;

std::cout<< " Done with Muon Plots"<< std::endl;

std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;


//sprintf(Latex_name, "PLOTS_%s_Muon_Latex_CV_and_Stacks", timeset);
 //input_Latex_name = Latex_name;



   std::cout << "lastline" << std::endl;

   return;

}



 int main() {

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

int my_Print_Systmatics=1;
std::cout << "Print Error Systmatics?  [ 0 = Total and Groups Systemtics Errors ,  1 = Total Systematic Errors , 2 = none ]" << std::endl;
//std::cin >> my_Print_Systmatics;
std::cout << "Print Error Systmatics: " << my_Print_Systmatics << std::endl;


bool my_debug = true;
std::cout << "Run in Debug Mode? (0 = NO, 1 = YES) " << std::endl;
//std::cin >> my_debug;
std::cout << std::boolalpha << my_debug << std::endl;


Kin(my_norm, my_debug, my_BinNormilzed, my_Print_Systmatics);

std::cout<< "Done with Program"<<std::endl;

return 0;

}


std::vector<ME_helium_Playlists> GetPlayListVector() {
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



/////////////////////////////////////////////
std::vector<MuonVar> GetMUONVaribles_Total() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<MuonVar> MuonVars;
  MuonVars.push_back(kE);
  MuonVars.push_back(kP_Z);
  MuonVars.push_back(kP_T);

  MuonVars.push_back(kAngleWRTB);


  return MuonVars;
//#endif
}

CrossSection_name_Map Generate_CrossSection_histsNames(MuonVar MuonVar_type, std::string playlist, bool isFUll){

  CrossSection_name_Map Name_Map;

  if(isFUll==true)
  {
    auto hist_name = GetMuonVarHistName(MuonVar_type);
    std::string hist1_name = hist_name + "_" + playlist + "_Data_Signal";
    Name_Map.insert(std::make_pair(Data_signal, hist1_name));

    std::string hist1_name_pot = hist_name + "_" + playlist + "_potnorm_Data_Signal";
    Name_Map.insert(std::make_pair(Data_signal_potNorm, hist1_name_pot));

    std::string hist1_name_pot_full_empty = hist_name + "_Full_sub_Empty_potnorm_Data_Signal";
    Name_Map.insert(std::make_pair(Data_signal_BGsub_potNorm, hist1_name_pot_full_empty));

    std::string hist1_name_BG_subtracted = hist_name + "_Data_BG_Subtracted";
    Name_Map.insert(std::make_pair(Data_signal_BG_subtracted, hist1_name_BG_subtracted));

    std::string unfolded_name = hist_name + "_unfolded_data";
    Name_Map.insert(std::make_pair(Data_signal_unfolded, unfolded_name));

    std::string eff_Corrected_name = hist_name +"_unfolded_data_effcorrected";
    Name_Map.insert(std::make_pair(Data_signal_unfolded_effcorrected, eff_Corrected_name));

    std::string unfolded_crosssection_name = hist_name + "_CrossSection_data_unfolded";
    Name_Map.insert(std::make_pair(Data_crosssection, unfolded_crosssection_name));

    std::string truecross_name = hist_name + "_TrueCrossSection";
    Name_Map.insert(std::make_pair(True_crosssection, truecross_name));

    std::string nom_Eff_name = hist_name+ "_" + playlist + "_effNum";
    Name_Map.insert(std::make_pair(nom_Eff, nom_Eff_name));

    std::string dom_Eff_name = hist_name + "_" + playlist + "_effDom";
    Name_Map.insert(std::make_pair(dom_Eff, dom_Eff_name));

    std::string eff_name = hist_name + "_efficiency";
    Name_Map.insert(std::make_pair(Eff, eff_name));


   std::string TRUEcrosssection_elastic = hist_name + "_efficiency";

  }

  else if(isFUll==false){
    auto hist_name = GetMuonVarHistName(MuonVar_type);
    std::string hist1_name = hist_name + "_" + playlist;
    Name_Map.insert(std::make_pair(Data_BG, hist1_name));

    std::string hist1_name_pot = hist1_name + "_potnorm";
    Name_Map.insert(std::make_pair(Data_BG_potNorm, hist1_name_pot));
  }

  return Name_Map;

}

CrossSection_name_Map Generate_CrossSection_histsNames_withInteraction(MuonVar MuonVar_type, std::string playlist, bool isFUll){

  CrossSection_name_Map Name_Map;

  if(isFUll==true)
  {
    auto hist_name = GetMuonVarHistName(MuonVar_type);
    std::string hist1_name = hist_name + "_" + playlist + "_Data_Signal";
    Name_Map.insert(std::make_pair(Data_signal, hist1_name));

    std::string hist1_name_pot = hist_name + "_" + playlist + "_potnorm_Data_Signal";
    Name_Map.insert(std::make_pair(Data_signal_potNorm, hist1_name_pot));

    std::string hist1_name_pot_full_empty = hist_name + "_Full_sub_Empty_potnorm_Data_Signal";
    Name_Map.insert(std::make_pair(Data_signal_BGsub_potNorm, hist1_name_pot_full_empty));

    std::string unfolded_name = hist_name + "_unfolded_data";
    Name_Map.insert(std::make_pair(Data_signal_unfolded, unfolded_name));

    std::string eff_Corrected_name = hist_name +"_unfolded_data_effcorrected";
    Name_Map.insert(std::make_pair(Data_signal_unfolded_effcorrected, eff_Corrected_name));

    std::string unfolded_crosssection_name = hist_name + "_CrossSection_data_unfolded";
    Name_Map.insert(std::make_pair(Data_crosssection, unfolded_crosssection_name));

    std::string truecross_name = hist_name + "_TrueCrossSection";
    Name_Map.insert(std::make_pair(True_crosssection, truecross_name));

    std::string nom_Eff_name = hist_name+ "_" + playlist + "_effNum";
    Name_Map.insert(std::make_pair(nom_Eff, nom_Eff_name));

    std::string dom_Eff_name = hist_name + "_" + playlist + "_effDom";
    Name_Map.insert(std::make_pair(dom_Eff, dom_Eff_name));

    std::string eff_name = hist_name + "_efficiency";
    Name_Map.insert(std::make_pair(Eff, eff_name));

   std::string TRUEcrosssection_Elastic = hist_name + "_CrossSection_Interaction_Elastic";
   Name_Map.insert(std::make_pair(True_crosssection_interaction_Elastic,TRUEcrosssection_Elastic));

   std::string TRUEcrosssection_DIS = hist_name + "_CrossSection_Interaction_DIS";
   Name_Map.insert(std::make_pair(True_crosssection_interaction_DIS,TRUEcrosssection_DIS));

   std::string TRUEcrosssection_1pion = hist_name + "_CrossSection_Interaction_1Pion";
   Name_Map.insert(std::make_pair(True_crosssection_interaction_1pion,TRUEcrosssection_1pion));

   std::string TRUEcrosssection_2p2h = hist_name + "_CrossSection_Interaction_2p2h";
   Name_Map.insert(std::make_pair(True_crosssection_interaction_2p2h, TRUEcrosssection_2p2h));

   std::string TRUEcrosssection_Other = hist_name + "_CrossSection_Interaction_Other";
   Name_Map.insert(std::make_pair(True_crosssection_interaction_other,TRUEcrosssection_Other));

   std::string TRUEcrosssection_none = hist_name + "_CrossSection_Interaction_None";
    Name_Map.insert(std::make_pair(True_crosssection_interaction_none,TRUEcrosssection_none));

  }

  else if(isFUll==false){
    auto hist_name = GetMuonVarHistName(MuonVar_type);
    std::string hist1_name = hist_name + "_" + playlist;
    Name_Map.insert(std::make_pair(Data_BG, hist1_name));

    std::string hist1_name_pot = hist1_name + "_potnorm";
    Name_Map.insert(std::make_pair(Data_BG_potNorm, hist1_name_pot));
  }

  return Name_Map;

}

CrossSection_name_Map Generate_CrossSection_histsNames_withInteraction_DISbreakdown(MuonVar MuonVar_type, std::string playlist, bool isFUll){

  CrossSection_name_Map Name_Map;
    auto hist_name = GetMuonVarHistName(MuonVar_type);

  if(isFUll==true)
  {

    std::string hist1_name = hist_name + "_" + playlist + "_Data_Signal";
    Name_Map.insert(std::make_pair(Data_signal, hist1_name));

    std::string hist1_reco = hist_name + "_" + playlist + "_potnorm_RECO_Signal";
    Name_Map.insert(std::make_pair(RECO_signal, hist1_reco));

    std::string hist1_name_pot = hist_name + "_" + playlist + "_potnorm_Data_Signal";
    Name_Map.insert(std::make_pair(Data_signal_potNorm, hist1_name_pot));

    std::string hist_RECO_BG = hist_name + "_" + playlist + "_potnorm_RECO_BG";
    Name_Map.insert(std::make_pair(MC_reco_BG, hist_RECO_BG));

    std::string hist1_name_pot_full_empty = hist_name + "_Full_sub_Empty_potnorm_Data_Signal";
    Name_Map.insert(std::make_pair(Data_signal_BGsub_potNorm, hist1_name_pot_full_empty));

    std::string hist2_name_pot_full_empty = hist_name + "_Full_sub_Empty_potnorm_RECO_Signal";
    Name_Map.insert(std::make_pair(RECO_signal_BGsub_potNorm, hist2_name_pot_full_empty));

    std::string hist1_name_pot_full_empty_BG = hist_name + "_Full_sub_Empty_potnorm_RECO_BG";
    Name_Map.insert(std::make_pair(MC_reco_subtracted_BG, hist1_name_pot_full_empty_BG));

    std::string hist1_name_Data_signal_BG_subtracted = hist_name + "_Data_BG_Subtracted";
    Name_Map.insert(std::make_pair(Data_signal_BG_subtracted, hist1_name_Data_signal_BG_subtracted));

    std::string unfolded_name = hist_name + "_unfolded_data";
    Name_Map.insert(std::make_pair(Data_signal_unfolded, unfolded_name));

    std::string eff_Corrected_name = hist_name +"_unfolded_data_effcorrected";
    Name_Map.insert(std::make_pair(Data_signal_unfolded_effcorrected, eff_Corrected_name));

    std::string unfolded_crosssection_name = hist_name + "_CrossSection_data_unfolded";
    Name_Map.insert(std::make_pair(Data_crosssection, unfolded_crosssection_name));

    std::string truecross_name = hist_name + "_TrueCrossSection";
    Name_Map.insert(std::make_pair(True_crosssection, truecross_name));

    std::string nom_Eff_name = hist_name+ "_" + playlist + "_effNum";
    Name_Map.insert(std::make_pair(nom_Eff, nom_Eff_name));

    std::string dom_Eff_name = hist_name + "_" + playlist + "_effDom";
    Name_Map.insert(std::make_pair(dom_Eff, dom_Eff_name));

    std::string eff_name = hist_name + "_efficiency";
    Name_Map.insert(std::make_pair(Eff, eff_name));

   std::string TRUEcrosssection_Elastic = hist_name + "_CrossSection_Interaction_QE";
   Name_Map.insert(std::make_pair(True_crosssection_interaction_Elastic,TRUEcrosssection_Elastic));

   std::string TRUEcrosssection_DISSIS = hist_name + "_CrossSection_Interaction_DISSIS";
   Name_Map.insert(std::make_pair(True_crosssection_interaction_DISSIS,TRUEcrosssection_DISSIS));

   std::string TRUEcrosssection_DISSoft = hist_name + "_CrossSection_Interaction_DISSoft";
   Name_Map.insert(std::make_pair(True_crosssection_interaction_DISSoft,TRUEcrosssection_DISSoft));

   std::string TRUEcrosssection_DISHard = hist_name + "_CrossSection_Interaction_DISHard";
   Name_Map.insert(std::make_pair(True_crosssection_interaction_DISHard,TRUEcrosssection_DISHard));

   std::string TRUEcrosssection_deltaRes = hist_name + "_CrossSection_Interaction_#DeltaRes";
   Name_Map.insert(std::make_pair(True_crosssection_interaction_DeltaRes,TRUEcrosssection_deltaRes));

   std::string TRUEcrosssection_HeavierRes = hist_name + "_CrossSection_Interaction_HeavierRes";
   Name_Map.insert(std::make_pair(True_crosssection_interaction_HeavierRes,TRUEcrosssection_HeavierRes));

   std::string TRUEcrosssection_2p2h = hist_name + "_CrossSection_Interaction_2p2h";
   Name_Map.insert(std::make_pair(True_crosssection_interaction_2p2h, TRUEcrosssection_2p2h));

   std::string TRUEcrosssection_Other = hist_name + "_CrossSection_Interaction_Other";
   Name_Map.insert(std::make_pair(True_crosssection_interaction_other,TRUEcrosssection_Other));

   std::string TRUEcrosssection_none = hist_name + "_CrossSection_Interaction_None";
    Name_Map.insert(std::make_pair(True_crosssection_interaction_none,TRUEcrosssection_none));

    std::string Mig = hist_name + "_Mig";
     Name_Map.insert(std::make_pair(mvnreponse_Mig,Mig));



  }

  else if(isFUll==false){

    //auto hist_name = GetMuonVarHistName(MuonVar_type);
  //  std::string hist1_name = hist_name + "_" + playlist + "_Data_Signal";
    //Name_Map.insert(std::make_pair(Data_signal, hist1_name));

    //std::string hist1_RECO = hist_name + "_" + playlist + "_RECO_Signal";
    //Name_Map.insert(std::make_pair(RECO_signal, hist1_RECO));

    std::string hist1_reco = hist_name + "_" + playlist + "_potnorm_RECO_Signal";
    Name_Map.insert(std::make_pair(RECO_signal, hist1_reco));

    std::string hist1_name_pot = hist_name + "_" + playlist + "_potnorm_Data_Signal";
    Name_Map.insert(std::make_pair(Data_signal, hist1_name_pot));


    //std::string hist1_name = hist_name + "_" + playlist;
    //Name_Map.insert(std::make_pair(Data_BG, hist1_name));

    std::string hist_RECO_BG = hist_name + "_" + playlist + "_potnorm_RECO_BG";
    Name_Map.insert(std::make_pair(MC_reco_BG, hist_RECO_BG));

    std::string hist2_name_pot = hist_name + "_potnorm";
    Name_Map.insert(std::make_pair(Data_BG_potNorm, hist2_name_pot));
  }

  return Name_Map;

}

void PrintCrossSection_MapName(CrossSection_name_Map Map , char * outputLabel){

 std::map<CrossSectionHist, std::string>::iterator it;
 std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;
 std::cout<< " Printing Hist Map for : "<< outputLabel << std::endl;
 std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;

 for (it = Map.begin(); it != Map.end(); it++)
 {

     std::cout <<"Map key = "
               << it->first    // string (key)
               << ": Hist String = "
               << it->second   // string's value
               << std::endl;
 }
 std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;
 std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;



return;

}





CrossSection_MnvH1D_Map Generate_CrossSection_Hist_Map(TFile& file, CrossSection_name_Map Map){
  CrossSection_MnvH1D_Map Hist_Map;

  std::map<CrossSectionHist, std::string>::iterator it;
  for (it = Map.begin(); it != Map.end(); it++)
  {
    std::cout<<"HistName = "<< it->second << std::endl;
    auto hist = Get1DHist(file, it->second );
    //MnvH1D *hist = (MnvH1D*)(cat->second)->Get(name);
    Hist_Map.insert(std::make_pair(it->first, hist));

  }

  return Hist_Map;

}


Migration_MnvH2D_Map Generate_CrossSection_Mig_Hist_Map(TFile& file, std::vector<MuonVar> muon_vector){
  Migration_MnvH2D_Map Hist_Map;
  for(auto Muon:muon_vector){
    auto mig_type = Migration_muonType(Muon);
    std::string Name = GetMuonVarHistName(Muon) + "_Mig";
    auto hist_2D = Get2DHist(file, Name );
    Hist_Map.insert(std::make_pair(mig_type, hist_2D));

  }

    return Hist_Map;
}


void MakeCrossSectionPlots_Interaction(CrossSection_MnvH1D_Map CrossSection_map, CrossSection_MnvH1D_Map CrossSection_mapEmpty,
  std::string cross_section_units, std::string pdf,bool MakeXaxisLOG,bool doBinwidth ,
  MuonVar MuonVar, char *Playlist_name, double POT_Data, double POT_MC, Genie_Models Modelinputs){


std::cout<<"Inside MakeCrossSectionPlots " << std::endl;
/// first Plot Signal Data
std::string X_axis = GetMuonVarAXISName(MuonVar);
char X_axis_char[X_axis.length()+1];
strcpy(X_axis_char,X_axis.c_str());

std::string X_axis_true = "TRUE " + GetMuonVarAXISName(MuonVar);
char X_axis_true_char[X_axis_true.length()+1];
strcpy(X_axis_true_char,X_axis_true.c_str());


std::string MuonTitle = GetMuonVarTitleName(MuonVar);
std::string pdfname= GetMuonVarpdfName(MuonVar);
std::string unit = GetMuonUnitType(MuonVar);
std::string title_Signal_TRUTH = MuonTitle + " TRUTH Signal Selection Dom Eff";
std::string EventBin = "Event Rate / [" + unit +"]";
std::string Efficiency_name  = "Efficiency" ;
std::string EventBin_noUnits = "Event Rate";
char EventBin_char[EventBin.length()+1];
strcpy(EventBin_char,EventBin.c_str());
char EventBin_noUnits_char[EventBin_noUnits.length()+1];
strcpy(EventBin_noUnits_char,EventBin_noUnits.c_str());





char title_Signal_TRUTH_char[title_Signal_TRUTH.length()+1];
strcpy(title_Signal_TRUTH_char,title_Signal_TRUTH.c_str());
DrawCVAndError_FromHistPointer(CrossSection_map[dom_Eff], title_Signal_TRUTH_char ,X_axis, EventBin, pdf,  doBinwidth, MakeXaxisLOG);
std::cout<<"Made CrossSection_map[dom_Eff]" << std::endl;

std::string title_Signal_nomEff = MuonTitle + " Selection Nom Eff";
char title_Signal_nomEff_char[title_Signal_nomEff.length()+1];
strcpy(title_Signal_nomEff_char,title_Signal_nomEff.c_str());
DrawCVAndError_FromHistPointer(CrossSection_map[nom_Eff], title_Signal_nomEff_char ,X_axis, EventBin, pdf,  doBinwidth, MakeXaxisLOG);
std::cout<<"Made CrossSection_map[nom_Eff]" << std::endl;


std::string title_Signal = MuonTitle + " Data Signal Selection";
char title_Signal_char[title_Signal.length()+1];
strcpy(title_Signal_char,title_Signal.c_str());
DrawCVAndError_FromHistPointer(CrossSection_map[Data_signal], title_Signal_char ,X_axis, EventBin, pdf,  doBinwidth, MakeXaxisLOG);
std::cout<<"Made CrossSection_map[Data_signal]" << std::endl;

std::string title_Signal_Pot = MuonTitle + " Data Signal [POT normalize]";
char title_Signal_Pot_char[title_Signal_Pot.length()+1];
strcpy(title_Signal_Pot_char,title_Signal_Pot.c_str());
DrawCVAndError_FromHistPointer(CrossSection_map[Data_signal_potNorm], title_Signal_Pot_char ,X_axis, EventBin, pdf,  doBinwidth, MakeXaxisLOG);
std::cout<<"CrossSection_map[Data_signal_potNorm]" << std::endl;

std::string title_Signal_Pot2 = MuonTitle + " Data Signal with BG";
char title_Signal_Pot2_char[title_Signal_Pot2.length()+1];
strcpy(title_Signal_Pot2_char,title_Signal_Pot2.c_str());

 DrawCVAndError_FromHistPointer(CrossSection_map[Data_signal], CrossSection_map[RECO_signal],CrossSection_mapEmpty[Data_signal], CrossSection_mapEmpty[RECO_signal], title_Signal_Pot2_char, X_axis,EventBin ,
pdf, true, false, false, -99, false);

std::string title_Signal_BG_Sub_Pot = MuonTitle + " [F-E]";
char title_Signal_BG_Sub_Pot_char[title_Signal_BG_Sub_Pot.length()+1];
strcpy(title_Signal_BG_Sub_Pot_char,title_Signal_BG_Sub_Pot.c_str());
DrawCVAndError_FromHistPointer(CrossSection_map[Data_signal_BGsub_potNorm], title_Signal_BG_Sub_Pot_char ,X_axis, EventBin, pdf,  doBinwidth, MakeXaxisLOG);
std::cout<<"CossSection_map[Data_signal_BGsub_potNorm]" << std::endl;

std::string title_Signal_BG_Sub_Pot_BG = MuonTitle + "  [F-E - MC BGsub]";
char title_Signal_BG_Sub_Pot_BG_char[title_Signal_BG_Sub_Pot_BG.length()+1];
strcpy(title_Signal_BG_Sub_Pot_BG_char,title_Signal_BG_Sub_Pot_BG.c_str());
DrawCVAndError_FromHistPointer(CrossSection_map[Data_signal_BG_subtracted], title_Signal_BG_Sub_Pot_BG_char ,X_axis, EventBin, pdf,  doBinwidth, MakeXaxisLOG);
std::cout<<"CossSection_map[Data_signal_BGsub_potNorm]" << std::endl;


std::string title_BG = MuonTitle + " BG Subtracted";
char title_BG_char[title_BG.length()+1];
strcpy(title_BG_char,title_BG.c_str());


//DrawCVAndError_FromHistPointer(CrossSection_map[MC_reco_subtracted_BG], title_BG_char ,X_axis, EventBin, pdf,  doBinwidth, MakeXaxisLOG);
//std::cout<<"CossSection_map[Data_signal_BGsub_potNorm]" << std::endl;
bool dontBinwidthNorm = false;

Draw_DataWITHMC_SingleHistinput_withRatioCrossSection(CrossSection_map[RECO_signal_BGsub_potNorm], CrossSection_map[Data_signal_BGsub_potNorm],
                                           Playlist_name, pdf, title_BG_char, unit, X_axis_char, "NEvent",
                                          doBinwidth, MakeXaxisLOG,  false);

  Draw_DataWITHMC_SingleHistinput_withRatio(CrossSection_map[RECO_signal_BGsub_potNorm],
    CrossSection_map[Data_signal_BGsub_potNorm],
    Playlist_name, pdf, title_BG_char, unit,
    X_axis_char, EventBin_noUnits_char, doBinwidth, MakeXaxisLOG,
    false, false);

    std::string title_BGSubtracted = MuonTitle + " [F-E-BG]";
    char title_BGSubtracted_char[title_BGSubtracted.length()+1];
    strcpy(title_BGSubtracted_char,title_BGSubtracted.c_str());

auto true_clone = CrossSection_map[dom_Eff]->Clone("true_clone");
true_clone->GetXaxis()->SetTitle(X_axis_true_char);
  //  Draw_DataWITHMC_SingleHistinput_withRatio(true_clone, CrossSection_map[MC_reco_subtracted_BG],
  //                                              Playlist_name, pdf, title_BGSubtracted_char, unit,
  //                                              X_axis_true_char, EventBin_noUnits_char, doBinwidth, MakeXaxisLOG,
  //                                              false, false);

  Draw_DataWITHMC_SingleHistinput_withRatioCrossSection(true_clone, CrossSection_map[MC_reco_subtracted_BG],
    Playlist_name, pdf, title_BGSubtracted_char, unit, X_axis_true_char, "NEvent",
    doBinwidth, MakeXaxisLOG,  false);



std::string title_unfolded = MuonTitle + " [BGsub][Unfolded]";
char title_unfolded_char[title_unfolded.length()+1];
strcpy(title_unfolded_char,title_unfolded.c_str());
//DrawCVAndError_FromHistPointer(CrossSection_map[Data_signal_unfolded], title_unfolded_char ,X_axis, EventBin, pdf,  doBinwidth, MakeXaxisLOG);


//true_clone->Scale(POT_Data /  POT_MC);


//Draw_DataWITHMC_SingleHistinput_withRatio(true_clone, CrossSection_map[Data_signal_unfolded],
//                                            Playlist_name, pdf, title_unfolded_char, unit,
//                                            X_axis_true_char, EventBin_noUnits_char, doBinwidth, MakeXaxisLOG,
//                                            false, false);

Draw_DataWITHMC_SingleHistinput_withRatioCrossSection(true_clone, CrossSection_map[Data_signal_unfolded],
  Playlist_name, pdf, title_unfolded_char, unit, X_axis_true_char, "Events",
  doBinwidth, MakeXaxisLOG,  false);



std::cout<<"CrossSection_map[Data_signal_unfolded]" << std::endl;




std::string title_EffCorr_Pot = MuonTitle + " [BGsub][Unfolded][Eff Corr]";
char title_EffCorr_Pot_char[title_EffCorr_Pot.length()+1];
strcpy(title_EffCorr_Pot_char,title_EffCorr_Pot.c_str());

//DrawCVAndError_FromHistPointer(CrossSection_map[Data_signal_unfolded_effcorrected], title_EffCorr_Pot_char ,X_axis, EventBin, pdf,  doBinwidth, MakeXaxisLOG);
//std::cout<<"CrossSection_map[Data_signal_unfolded_effcorrected]" << std::endl;

//Draw_DataWITHMC_SingleHistinput_withRatio(true_clone, CrossSection_map[Data_signal_unfolded_effcorrected],
//                                            Playlist_name, pdf, title_EffCorr_Pot_char, unit,
//                                            X_axis_true_char, EventBin_noUnits_char, doBinwidth, MakeXaxisLOG,
//                                            false, false);

Draw_DataWITHMC_SingleHistinput_withRatioCrossSection(true_clone, CrossSection_map[Data_signal_unfolded_effcorrected],
  Playlist_name, pdf, title_EffCorr_Pot_char, unit, X_axis_true_char, "Events",
  doBinwidth, MakeXaxisLOG,  false);



std::string title_eff = MuonTitle + " Efficiency";
char title_eff_char[title_eff.length()+1];
strcpy(title_eff_char,title_eff.c_str());
DrawCVAndError_FromHistPointer(CrossSection_map[Eff], title_eff_char ,X_axis, Efficiency_name, pdf,  false, MakeXaxisLOG);
std::cout<<"CrossSection_map[Eff]" << std::endl;

std::string title_Cross_Section = MuonTitle + " Cross-Section:  #nu_{#mu} + ^{4}He #rightarrow #mu^{-} + X";
char title_Cross_Section_char[title_Cross_Section.length()+1];
strcpy(title_Cross_Section_char,title_Cross_Section.c_str());

std::string crossSection_y_axis = "#frac{d#sigma}{d" + GetMuonVar_crosssection(MuonVar) + "} (10^{-38} cm^{2} / " +  cross_section_units + " / nucleon)";


char crossSection_y_axis_char[crossSection_y_axis.length()+1];
strcpy(crossSection_y_axis_char,crossSection_y_axis.c_str());
std::cout<<"Scaling Hists" << std::endl;

 auto names = CrossSection_map[True_crosssection]->GetErrorBandNames();
for(auto name : names){

std::cout<< " Name os TRUE crossection band 1 "<< name << std::endl;

}
//fauto ccma_band = CrossSection_map[True_crosssection]->GetLatErrorBand( "GENIE_MaCCQE" );

 //PlotVertBand("Flux", "flux",CrossSection_map[True_crosssection]);


double Scale = pow(10,-38);
CrossSection_map[True_crosssection]->Scale(1/Scale);
CrossSection_map[Data_crosssection]->Scale(1/Scale);
CrossSection_map[True_crosssection_interaction_Elastic]->Scale(1/Scale);
//CrossSection_map[True_crosssection_interaction_DIS]->Scale(1/Scale);
CrossSection_map[True_crosssection_interaction_DISSIS]->Scale(1/Scale);
CrossSection_map[True_crosssection_interaction_DISSoft]->Scale(1/Scale);
CrossSection_map[True_crosssection_interaction_DISHard]->Scale(1/Scale);
CrossSection_map[True_crosssection_interaction_DeltaRes]->Scale(1/Scale);
CrossSection_map[True_crosssection_interaction_HeavierRes]->Scale(1/Scale);
//CrossSection_map[True_crosssection_interaction_DIS]->Scale(1/Scale);
//CrossSection_map[True_crosssection_interaction_1pion]->Scale(1/Scale);
CrossSection_map[True_crosssection_interaction_2p2h]->Scale(1/Scale);
CrossSection_map[True_crosssection_interaction_other]->Scale(1/Scale);
CrossSection_map[True_crosssection_interaction_none]->Scale(1/Scale);

std::string inputname1 = pdfname + "Old_ZexpTRUE";
std::string inputname2 = pdfname + "Old_ZexpData";
//PlotVertBand("GENIE_MaZExpCCQE", inputname1 ,"MaCCQE Systematic universes MC TRUE", X_axis, crossSection_y_axis, CrossSection_map[True_crosssection]);
//PlotVertBand("GENIE_MaZExpCCQE", inputname2 ,"MaCCQE Systematic universes DATA", X_axis, crossSection_y_axis, CrossSection_map[Data_crosssection]);


//



std::cout<<"Writing First XSec method" << std::endl;
//Draw_DataWITHMC_SingleHistinput_withRatioCrossSection(CrossSection_map[True_crosssection], CrossSection_map[Data_crosssection],
//                                           Playlist_name, pdf, title_Cross_Section_char, "", X_axis_char, crossSection_y_axis_char,
//                                          doBinwidth, MakeXaxisLOG,  true);

Draw_DataWITHMC_SingleHistinput_withRatio(CrossSection_map[True_crosssection], CrossSection_map[Data_crosssection],
                                            Playlist_name, pdf, title_Cross_Section_char, "",
                                            X_axis_char, crossSection_y_axis_char, dontBinwidthNorm, MakeXaxisLOG,
                                            false, false);



                                        //  auto names2 = CrossSection_map[True_crosssection]->GetErrorBandNames();
                                        // for(auto name : names2){

                                        // std::cout<< " Name os TRUE crossection band 2 "<< name << std::endl;

                                        // }


Modelinputs.intializeTFileMap();
Modelinputs.intializeTH1DMap();
Modelinputs.ScaleTH1DHists(1/Scale);
double Area = CrossSection_map[True_crosssection]->Integral();
std::cout<<"Modelinputs.ModelHistMap_1D.size() = "<< Modelinputs.ModelHistMap_th1D.size()<<std::endl;
TH1D*  hMC_Model_nominal =  (TH1D*)CrossSection_map[True_crosssection]->Clone(uniq());
TH1D*  hMC_Model_nominal2 =  (TH1D*)CrossSection_map[True_crosssection]->Clone(uniq());
TH1D*  hMC_Model_G18_02a_02_11a =  (TH1D*)Modelinputs.ModelHistMap_th1D[kME_GENIE_G18_02a_02_11a]->Clone("G18_02a_02_11a");
TH1D*  hMC_Model_G18_10a_02_11a =  (TH1D*)Modelinputs.ModelHistMap_th1D[kME_GENIE_G18_10a_02_11a]->Clone("G18_10a_02_11a");
TH1D*  hMC_Model_G18_02b_02_11a =  (TH1D*)Modelinputs.ModelHistMap_th1D[kME_GENIE_G18_02b_02_11a]->Clone("G18_02b_02_11a");
TH1D*  hMC_Model_G18_10b_02_11a =  (TH1D*)Modelinputs.ModelHistMap_th1D[kME_GENIE_G18_10b_02_11a]->Clone("G18_10b_02_11a");

//Double_t NormBinWidth = CrossSection_map[True_crosssection]->GetNormBinWidth();
  MnvH1D hist_new(*hMC_Model_nominal2);
  MnvH1D *hist_new2 = &hist_new;

//hMC_Model_G18_02a_02_11a->Scale(Area/ hMC_Model_G18_02a_02_11a->Integral());
//hMC_Model_G18_10a_02_11a->Scale(Area/ hMC_Model_G18_10a_02_11a->Integral());
//hMC_Model_G18_02b_02_11a->Scale(Area/ hMC_Model_G18_02b_02_11a->Integral());
//hMC_Model_G18_10b_02_11a->Scale(Area/ hMC_Model_G18_10b_02_11a->Integral());




//DrawCVAndError_From2HIST(hMC_Model_nominal, "nominal" ,hMC_Model_G18_10a_02_11a,
//         "G18_10a_02_11a",  "model test" ,X_axis, crossSection_y_axis ,
//pdf, false, true, -99 , false);

std::vector<int> Helium9_colorScheme = {
  TColor::GetColor("#DA70D6"), //'orchid'
  TColor::GetColor("#FFA500"), //'orange'
  TColor::GetColor("#87CEEB"),//'skyblue'
  TColor::GetColor("#6495ED"), //'cornflowerblue'
  TColor::GetColor("#00FFFF"),//'aqua'
  TColor::GetColor("#0000CD"),//'blue'
  TColor::GetColor("#FF0000"),//'red'
  TColor::GetColor("#32CD32"),//'limegreen'
  TColor::GetColor("#FFD700"),  // Gold
  TColor::GetColor("#800000"),  // Maroon
  TColor::GetColor("#555555")  // dark grey
};


//Draw_DataWITHMC_SingleHistinput_withRatio(CrossSection_map[True_crosssection], CrossSection_map[Data_crosssection],
//                                            Playlist_name, pdf, title_Cross_Section_char, "",
//                                            X_axis_char, crossSection_y_axis_char, dontBinwidthNorm, MakeXaxisLOG,
//                                            false, false);

if(MuonVar!=kAngleWRTB){

//per Nucleon

//hMC_Model_G18_02a_02_11a->Scale(.25);
//hMC_Model_G18_10a_02_11a->Scale(.25);
//hMC_Model_G18_02b_02_11a->Scale(.25);
//hMC_Model_G18_10b_02_11a->Scale(.25);


  hMC_Model_G18_02a_02_11a->Scale(1,"width");
  hMC_Model_G18_10a_02_11a->Scale(1,"width");
  hMC_Model_G18_02b_02_11a->Scale(1,"width");
  hMC_Model_G18_10b_02_11a->Scale(1,"width");

// I think i have to bin width normalize
DrawCVAndError_From5HIST(CrossSection_map[Data_crosssection], "Data",
                              hMC_Model_nominal, "Minerva v1",
                              hMC_Model_G18_02a_02_11a, "GENIE: G18_02a_02_11a",
                              hMC_Model_G18_10a_02_11a, "GENIE: G18_10a_02_11a",
                              hMC_Model_G18_02b_02_11a, "GENIE: G18_02b_02_11a",
                              hMC_Model_G18_10b_02_11a, "GENIE: G18_10b_02_11a",
                              Helium9_colorScheme,
                              "Model Comparson" ,X_axis, crossSection_y_axis,
   pdf, false, dontBinwidthNorm, -99 , false);
}








//TObjArray *TobjMC_Model;
//TobjMC_Model->SetOwner(kTRUE);
//
//TobjMC_Model->Add(hMC_Model_G18_02a_02_11a);
//TobjMC_Model->Add(hMC_Model_G18_10a_02_11a);
//TobjMC_Model->Add(hMC_Model_G18_02b_02_11a);
//TobjMC_Model->Add(hMC_Model_G18_10b_02_11a);

//hMC_Model_clone->Scale(1.0,"width");
//hMC_Model_clone->Scale(Scale);

//MC_ModelTypes{kME_GENIE_MnvTune1,
//  kME_GENIE_G18_02a_02_11a,
//  kME_GENIE_G18_10a_02_11a,
//  kME_GENIE_G18_02b_02_11a,
//  kME_GENIE_G18_10b_02_11a
//

//std::cout<<"TITLE outside class " << Modelinputs.ModelHistMap_1D[0]->GetTitle()<<std::endl;
std::cout<<"apout Draw_DataWITHMC_SingleHistinput_withRatioCrossSection " << std::endl;
//Draw_DataWITHMC_SingleHistinput_withRatioCrossSection(CrossSection_map[True_crosssection], CrossSection_map[Data_crosssection], TobjMC_Model,
//Playlist_name, pdf, title_Cross_Section_char, "", X_axis_char, crossSection_y_axis_char, MakeXaxisLOG );




std::cout<<"CrossSection_map[True_crosssection]" << std::endl;
 //void Draw_DataWITHMC_SingleHistinput_withRatio(MnvH1D *hist_MC, MnvH1D *hist_Data,
     //char *Playlist_name, std::string pdf_label, char *histotitle, std::string units,
      //char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG , bool drawAllErrorGroups= true);
      std::cout<<"Writing First XSec method with Interactions" << std::endl;

      Draw_DataWITHMC_SingleHistinput_withRatioCrossSection_Interactions_DISbreakdown(
        CrossSection_map[True_crosssection], CrossSection_map[Data_crosssection],
        CrossSection_map[True_crosssection_interaction_Elastic],
        CrossSection_map[True_crosssection_interaction_2p2h],
        CrossSection_map[True_crosssection_interaction_DeltaRes],
        CrossSection_map[True_crosssection_interaction_HeavierRes],
        CrossSection_map[True_crosssection_interaction_DISSIS],
        CrossSection_map[True_crosssection_interaction_DISSoft],
        CrossSection_map[True_crosssection_interaction_DISHard],
        CrossSection_map[True_crosssection_interaction_none],
        CrossSection_map[True_crosssection_interaction_other],
        Playlist_name, pdf, title_Cross_Section_char, "",
        X_axis_char, crossSection_y_axis_char, dontBinwidthNorm, MakeXaxisLOG,  false, POT_MC, POT_Data);
        std::string pdf_pdf = pdf + ".pdf";

        char matrixtitle[1024];
        sprintf(matrixtitle, "[DATA] %s ",X_axis_char );
      DrawCovarientMatrix_FromHistPointer(CrossSection_map[Data_crosssection], matrixtitle, "Bin Number","Bin Number ", pdf_pdf);


        Draw_MCInteractions_FractionEvents(
      CrossSection_map[True_crosssection],
    CrossSection_map[True_crosssection_interaction_Elastic],
    CrossSection_map[True_crosssection_interaction_2p2h],
    CrossSection_map[True_crosssection_interaction_DeltaRes],
    CrossSection_map[True_crosssection_interaction_HeavierRes],
    CrossSection_map[True_crosssection_interaction_DISSIS],
    CrossSection_map[True_crosssection_interaction_DISSoft],
    CrossSection_map[True_crosssection_interaction_DISHard],
    CrossSection_map[True_crosssection_interaction_none],
    CrossSection_map[True_crosssection_interaction_other],
      pdf, "Cross-Section Interaction Breakdown",
         X_axis_char, "Fraction of Events");

if(MuonVar!=kAngleWRTB){

CrossSection_map[Data_crosssection]->Divide(CrossSection_map[Data_crosssection],hist_new2);
hMC_Model_G18_02a_02_11a->Divide(hMC_Model_G18_02a_02_11a,hMC_Model_nominal);
hMC_Model_G18_10a_02_11a->Divide(hMC_Model_G18_10a_02_11a,hMC_Model_nominal);
hMC_Model_G18_02b_02_11a->Divide(hMC_Model_G18_02b_02_11a,hMC_Model_nominal);
hMC_Model_G18_10b_02_11a->Divide(hMC_Model_G18_10b_02_11a,hMC_Model_nominal);
hMC_Model_nominal->Divide(hMC_Model_nominal,hMC_Model_nominal);


         DrawCVAndError_From5HIST(CrossSection_map[Data_crosssection], "Data",
                                       hMC_Model_nominal, "Minerva v1",
                                       hMC_Model_G18_02a_02_11a, "GENIE: G18_02a_02_11a",
                                       hMC_Model_G18_10a_02_11a, "GENIE: G18_10a_02_11a",
                                       hMC_Model_G18_02b_02_11a, "GENIE: G18_02b_02_11a",
                                       hMC_Model_G18_10b_02_11a, "GENIE: G18_10b_02_11a",
                                       Helium9_colorScheme,
                                       "Model Comparson" ,X_axis, "Cross Section Ratio to MvnTune 1 ",
            pdf, true, dontBinwidthNorm, -99 , false);

}



return;
}
/////////////////////////////////////////////////////
//
////////////////////////////////////////////////////
void MakeCrossSection_MigrationPlots(){





















}
