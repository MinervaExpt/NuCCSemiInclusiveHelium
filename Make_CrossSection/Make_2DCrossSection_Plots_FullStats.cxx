#include "Make_CrossSection_Plots.h"




CrossSection_name_Map Generate_2DCrossSection_histsNames_withInteraction_DISbreakdown(std::string hist_name, Muon2DVar MuonVar_type,  std::string playlist, bool isFUll, bool PrintNames=false);
std::vector<Muon2DVar> GetMUON2DVaribles();
MnvH2D *Copy(MnvH2D *hist_input, char * name);
void Make2DCrossSectionPlots_Interaction(CrossSection_MnvH2D_Map CrossSection_map,CrossSection_MnvH2D_Map CrossSection_mapBG,
  std::string cross_section_units, std::string pdf,bool MakeXaxisLOG,bool doBinwidth,
  Muon2DVar MuonVar, char *Playlist_name, TCanvas *can, MnvPlotter *plot, double POT_Data, double POT_MC);
  void Make2DCrossSectionPlots_Interaction_Theta(CrossSection_MnvH2D_Map CrossSection_map,CrossSection_MnvH2D_Map CrossSection_mapBG,
    std::string cross_section_units, std::string pdf,bool MakeXaxisLOG,bool doBinwidth,
    Muon2DVar MuonVar, char *Playlist_name, TCanvas *can, MnvPlotter *plot, double POT_Data, double POT_MC);
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
mnv_plot->ApplyStyle(PlotUtils::kCCInclusiveHeliumStyle);
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

auto PlaylistME_CrossSection_Path = "/minerva/app/users/cnguyen/cmtuser/Minerva_v22r1p1Helium_GIT/NuCCSemiInclusiveHelium/Make_CrossSection/CrossSection2D.root";
bool is_mc=true;bool isNOT_mc=false;
std::string pdf_CV = string(text_title_pdf4);
bool Stats_only = false;




sprintf(text_title_pdf1, "PLOTS_2D_CrossSection_FullStats.pdf(" );
can -> Print(text_title_pdf1);
sprintf(text_title_pdf2, "PLOTS_2D_CrossSection_FullStats.pdf");
sprintf(text_title_pdf3, "PLOTS_2D_CrossSection_FullStats.pdf)");
sprintf(text_title_pdf4, "PLOTS_2D_CrossSection_FullStats" );
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

auto GENIE_G18_02a_02_11a_playlistPath ="/minerva/app/users/cnguyen/cmtuser/Minerva_v22r1p1Helium_GIT/NuCCSemiInclusiveHelium/eventselection2D/CrossSection_G18_02a_02_11a_new1.root";
auto GENIE_G18_10a_02_11a_playlistPath ="/minerva/app/users/cnguyen/cmtuser/Minerva_v22r1p1Helium_GIT/NuCCSemiInclusiveHelium/eventselection2D/CrossSection_G18_10b_02_11a_new1.root";
auto GENIE_G18_02b_02_11a_playlistPath ="/minerva/app/users/cnguyen/cmtuser/Minerva_v22r1p1Helium_GIT/NuCCSemiInclusiveHelium/eventselection2D/CrossSection_G18_10a_02_11a_new1.root";
auto GENIE_G18_10b_02_11a_playlistPath ="/minerva/app/users/cnguyen/cmtuser/Minerva_v22r1p1Helium_GIT/NuCCSemiInclusiveHelium/eventselection2D/CrossSection_G18_02b_02_11a_new1.root";

//ME_playlist_RootPathMAP Model_Paths;
//Model_Paths.insert(std::make_pair(kME_GENIE_G18_02a_02_11a,GENIE_G18_02a_02_11a_playlistPath));
//Model_Paths.insert(std::make_pair(kME_GENIE_G18_10a_02_11a,GENIE_G18_10a_02_11a_playlistPath));
//Model_Paths.insert(std::make_pair(kME_GENIE_G18_02b_02_11a,GENIE_G18_02b_02_11a_playlistPath));
//Model_Paths.insert(std::make_pair(kME_GENIE_G18_10b_02_11a,GENIE_G18_10b_02_11a_playlistPath));
//
//
//Genie_Models PTPZ_GenieModel("ptpz",Model_Paths);
//Genie_Models E_angle_GenieModel("E_angle",Model_Paths);


auto muon_vector = GetMUON2DVaribles();
bool isFull = true;
bool isEmpty = false;
bool DoBinWidthNorm = true;
bool DoLogAxis = false;

auto MuonPT_PZ_full_names = Generate_2DCrossSection_histsNames_withInteraction_DISbreakdown("h_MuonPT_PZ",muon_vector[0], "Full", isFull ,true);
auto MuonPT_PZ_Empty_names = Generate_2DCrossSection_histsNames_withInteraction_DISbreakdown("h_MuonPT_PZ",muon_vector[0], "Empty", isEmpty, true);

auto MuonE_Theta_full_names = Generate_2DCrossSection_histsNames_withInteraction_DISbreakdown("h_MuonE_Theta",muon_vector[1], "Full", isFull ,true);
auto MuonE_Theta_Empty_names = Generate_2DCrossSection_histsNames_withInteraction_DISbreakdown("h_MuonE_Theta",muon_vector[1], "Empty", isEmpty);

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~       Genrating CrossSection st        ~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

auto Map_PT_PZ_Full_hists = Generate_2DCrossSection_Hist_Map(*TFile_CrossSection, MuonPT_PZ_full_names);
auto Map_PT_PZ_Empty_hists = Generate_2DCrossSection_Hist_Map(*TFile_CrossSection, MuonPT_PZ_Empty_names);
auto Map_E_Theta_Full_hists = Generate_2DCrossSection_Hist_Map(*TFile_CrossSection, MuonE_Theta_full_names);
auto Map_E_Theta_Empty_hists = Generate_2DCrossSection_Hist_Map(*TFile_CrossSection, MuonE_Theta_Empty_names);

//auto Map_MuonE_Empty_hist = Generate_CrossSection_Hist_Map(*TFile_CrossSection, MuonPT_PZ_Empty_names);
PrintCrossSection_MapName(MuonPT_PZ_full_names , "FullNames");

//auto titleholder = ;
std::cout<< "Map_PT_PZ_Full_hists[True_crosssection_interaction_HeavierRes]->GetTitle() = " << Map_PT_PZ_Full_hists[True_crosssection_interaction_HeavierRes]->GetTitle()<< std::endl;

Make2DCrossSectionPlots_Interaction(Map_PT_PZ_Full_hists, Map_PT_PZ_Empty_hists,"GeV", pdf_CV,DoLogAxis, DoBinWidthNorm ,muon_vector[0], "F-E",can, mnv_plot ,FULL_POT_DATA, FULL_POT_MC);

Make2DCrossSectionPlots_Interaction_Theta(Map_E_Theta_Full_hists,Map_E_Theta_Empty_hists, "", pdf_CV,DoLogAxis, DoBinWidthNorm ,muon_vector[1], "F-E",can, mnv_plot ,FULL_POT_DATA, FULL_POT_MC);

//std::string eff_name_mvn = "h_MuonPT_PZ_Full_hist_mvnreponse_Mig";
//MnvH2D *histeff_mvnreponse = Get2DHist(*TFile_CrossSection, eff_name_mvn );
//
//std::string eff_name = "h_MuonPT_PZ_efficiency";
//MnvH2D *histeff = Get2DHist(*TFile_CrossSection, eff_name );
//
//
////Draw2DHist(histeff_mvnreponse,  "p_{T}", "P_{z}", "Event", "Reponse"  ,  text_title_pdf2, can, mnv_plot);
//
//
//std::string name1 = "h_MuonPT_PZ_Full_sub_Empty_potnorm_Data_Signal";
//MnvH2D *hist = Get2DHist(*TFile_CrossSection, name1 );
//
//std::string name2 = "h_MuonPT_PZ_Full_sub_Empty_potnorm_RECO";
//MnvH2D *histMC = Get2DHist(*TFile_CrossSection, name2 );
//
//std::string TrueCrossSection_name = "h_MuonPT_PZ_TrueCrossSection";
//MnvH2D *h_trueptpzcross = Get2DHist(*TFile_CrossSection, TrueCrossSection_name );
//
//std::string dataCrossSection_name = "h_MuonPT_PZ_CrossSection_data_unfolded";
//MnvH2D *h_dataptpzcross = Get2DHist(*TFile_CrossSection, dataCrossSection_name );
//double Scale = pow(10,-38);
//h_trueptpzcross->Scale(1/Scale);
//h_dataptpzcross->Scale(1/Scale);
//
//std::string crossSection_z_axis = "#frac{d#sigma}{d" + GetMuon2DVar_XaxisTitle_noUntils(muon_vector[0])+"d"+ GetMuon2DVar_YaxisTitle_noUntils(muon_vector[0]) + "} (10^{-38} cm^{2} / " +  GetMuon2DVar_yaxisUnits(muon_vector[0]) + " / ^{4}He)";
//char crossSection_z_axis_char[crossSection_z_axis.length()+1];
//strcpy(crossSection_z_axis_char,crossSection_z_axis.c_str());
//
//
//Draw2DHist(hist,  "data pT", "data Pz", "Signal", ""  ,  text_title_pdf2, can, mnv_plot);
//Draw2DHist(histMC,  "mc pT", "mc Pz", "Signal", ""  ,  text_title_pdf2, can, mnv_plot);
double chisqrt=999;int ndf;

//Draw2D_Panel_CV_SystematicErrFromPointer(hist, histMC,"F-E",
//       "F-E", mnv_plot,
//      text_title_pdf2, "title"," pT", " Pz",
//      "NEvent", true, false,
//      400, 400, .03, .03, chisqrt, ndf );

  //    std::string xaxis = GetMuon2DVar_XaxisTitle_noUntils(muon_vector[0]);
  //    char xaxis_char[xaxis.length()+1];
  //    strcpy(xaxis_char,xaxis.c_str());
  //    std::string yaxis =  GetMuon2DVar_YaxisTitle_noUntils(muon_vector[0]);
  //    char yaxis_char[yaxis.length()+1];
  //    strcpy(yaxis_char,yaxis.c_str());
  //    std::string title_base = GetMuon2DVar_Title(muon_vector[0]);
  //    char title_base_char[title_base.length()+1];
  //    strcpy(title_base_char,title_base.c_str());


//      Draw2DHist_Migration_Histpointer(histeff, "Efficiency",
//                        xaxis_char, yaxis_char,  "Efficiency",text_title_pdf4, can, mnv_plot);
//
//
//  Draw2D_Panel_CV_SystematicErrFromPointer_new(hist, histMC, "combined" ,
//           "F-E", mnv_plot,
//          text_title_pdf2, title_base_char, yaxis_char, xaxis_char, "NEvent" , true, false,
//          200, 100, .03,.03, chisqrt, ndf );
//
//
//
//Draw2D_Panel_CV_SystematicErrFromPointer_new(h_dataptpzcross,   h_trueptpzcross, "combined" ,
//                   "F-E", mnv_plot,
//                  text_title_pdf2, "CrossSection", yaxis_char, xaxis_char, crossSection_z_axis_char , true, false,
//                  200, 100, .03,.03, chisqrt, ndf );



////////////////////////////////////
//          std::string name3 = "h_MuonE_Theta_Full_sub_Empty_potnorm_Data_Signal";
//          MnvH2D *hist1 = Get2DHist(*TFile_CrossSection, name3 );
//
//          std::string name4 = "h_MuonE_Theta_Full_sub_Empty_potnorm_RECO";
//          MnvH2D *histMC1 = Get2DHist(*TFile_CrossSection, name4 );
//
//
//          std::string xaxis1 = GetMuon2DVar_XaxisTitle_noUntils(muon_vector[1]);
//          char xaxis1_char[xaxis1.length()+1];
//          strcpy(xaxis1_char,xaxis1.c_str());
//          std::string yaxis1 =  GetMuon2DVar_YaxisTitle_noUntils(muon_vector[1]);
//          char yaxis1_char[yaxis1.length()+1];
//          strcpy(yaxis1_char,yaxis1.c_str());
//          std::string title_base1 = GetMuon2DVar_Title(muon_vector[1]);
//          char title_base1_char[title_base1.length()+1];
//          strcpy(title_base1_char,title_base1.c_str());
//
//
//
//          Draw2D_Panel_CV_SystematicErrFromPointer_new(hist1, histMC1, "combined" ,
//                   "F-E", mnv_plot,
//                  text_title_pdf2, title_base1_char, yaxis1_char, xaxis1_char, "NEvent" , true, false,
//                  200, 100, .03,.03, chisqrt, ndf );


 can -> Print(text_title_pdf3);
 can->Close();

 //sprintf(Latex_name, "PLOTS_%s_Latex_Muon_CV_ERRORS", timeset_nonstacks);





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
std::vector<Muon2DVar> GetMUON2DVaribles() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<Muon2DVar> MuonVars;

  MuonVars.push_back(kPT_PZ);
  MuonVars.push_back(kE_theta);





  return MuonVars;
//#endif
}

CrossSection_name_Map Generate_CrossSection_histsNames_withInteraction(MuonVar MuonVar_type, std::string playlist, bool isFUll){

  CrossSection_name_Map Name_Map;

  if(isFUll==true)
  {
    auto hist_name = GetMuonVarHistName(MuonVar_type);
    std::string hist1_name = hist_name + "_" + playlist + "_Data_Signal";
    Name_Map.insert(std::make_pair(Data_signal, hist1_name));

    //std::string hist1_name_pot = hist_name + "_" + playlist + "_potnorm_Data_Signal";
    //Name_Map.insert(std::make_pair(Data_signal_potNorm, hist1_name_pot));

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

CrossSection_name_Map Generate_2DCrossSection_histsNames_withInteraction_DISbreakdown(std::string hist_name, Muon2DVar MuonVar_type,  std::string playlist, bool isFUll , bool PrintNames){

  CrossSection_name_Map Name_Map;

  if(isFUll==true)
  {

    std::string hist1_name = hist_name + "_" + playlist + "_Data_Signal";
    Name_Map.insert(std::make_pair(Data_signal, hist1_name));



    std::string hist_RECO_name = hist_name + "_" + playlist + "_MC_RECO";
    Name_Map.insert(std::make_pair(MC_reco, hist_RECO_name));

    //std::string hist1_name_pot = hist_name + "_" + playlist + "_potnorm_Data_Signal";
    //Name_Map.insert(std::make_pair(Data_signal_potNorm, hist1_name_pot));

    std::string hist1_name_pot_full_empty = hist_name + "_Full_sub_Empty_potnorm_Data_Signal";
    Name_Map.insert(std::make_pair(Data_signal_BGsub_potNorm, hist1_name_pot_full_empty));

    std::string hist2_name_pot_full_empty = hist_name + "_Full_sub_Empty_potnorm_RECO";
    Name_Map.insert(std::make_pair(RECO_signal_BGsub_potNorm, hist2_name_pot_full_empty));

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

    std::string mvnreponse_Mig_name = hist_name + "_mvnreponse_Mig";
    Name_Map.insert(std::make_pair(mvnreponse_Mig, mvnreponse_Mig_name));

    std::string mvnreponse_RECO_name = hist_name + "_mvnreponse_RECO";
    Name_Map.insert(std::make_pair(mvnreponse_RECO, mvnreponse_RECO_name));

    std::string mvnreponse_true_name = hist_name + "_mvnreponse_TRUE";
    Name_Map.insert(std::make_pair(mvnreponse_TRUE, mvnreponse_true_name));

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

    if(PrintNames==true){

   std::cout<<"Printer Names of Got His"<<std::endl;
   std::cout<<"hist1_name = " << hist1_name<< std::endl;
   std::cout<<"hist_RECO_name = " << hist_RECO_name<< std::endl;
   //std::cout<<"hist1_name_pot = " << hist1_name_pot<< std::endl;
   std::cout<<"hist1_name_pot_full_empty = " << hist1_name_pot_full_empty<< std::endl;
   std::cout<<"hist2_name_pot_full_empty = " << hist2_name_pot_full_empty<< std::endl;
   std::cout<<"unfolded_name = " << unfolded_name<< std::endl;
   std::cout<<"eff_Corrected_name = " << eff_Corrected_name<< std::endl;
   std::cout<<"unfolded_crosssection_name = " << unfolded_crosssection_name<< std::endl;
   std::cout<<"truecross_name = " << truecross_name<< std::endl;
   std::cout<<"nom_Eff_name = " << nom_Eff_name<< std::endl;
   std::cout<<"dom_Eff_name = " << dom_Eff_name<< std::endl;
   std::cout<<"eff_name = " << eff_name<< std::endl;
   std::cout<<"mvnreponse_Mig_name = " << mvnreponse_Mig_name<< std::endl;
   std::cout<<"mvnreponse_RECO_name = " << mvnreponse_RECO_name<< std::endl;
   std::cout<<"mvnreponse_true_name = " << mvnreponse_true_name<< std::endl;
   std::cout<<"TRUEcrosssection_Elastic = " << TRUEcrosssection_Elastic<< std::endl;
   std::cout<<"TRUEcrosssection_DISSIS = " << TRUEcrosssection_DISSIS<< std::endl;
   std::cout<<"TRUEcrosssection_DISSoft = " << TRUEcrosssection_DISSoft<< std::endl;
   std::cout<<"TRUEcrosssection_DISHard = " << TRUEcrosssection_DISHard<< std::endl;
   std::cout<<"TRUEcrosssection_deltaRes = " << TRUEcrosssection_deltaRes<< std::endl;
   std::cout<<"TRUEcrosssection_HeavierRes = " << TRUEcrosssection_HeavierRes<< std::endl;
   std::cout<<"TRUEcrosssection_2p2h = " << TRUEcrosssection_2p2h<< std::endl;
   std::cout<<"TRUEcrosssection_Other = " << TRUEcrosssection_Other<< std::endl;
   std::cout<<"TRUEcrosssection_none = " << TRUEcrosssection_none<< std::endl;


 }


  }

  else if(isFUll==false){

    //std::string hist1_name = hist_name + "_" + playlist;
    //Name_Map.insert(std::make_pair(Data_BG, hist1_name));

    //std::string hist1_name_pot = hist1_name + "_potnorm";
    //Name_Map.insert(std::make_pair(Data_BG_potNorm, hist1_name_pot));

    std::string hist1_name = hist_name + "_" + playlist + "_Data_Signal";
    Name_Map.insert(std::make_pair(Data_signal, hist1_name));

    std::string hist_RECO_name = hist_name + "_" + playlist + "_MC_RECO";
    Name_Map.insert(std::make_pair(MC_reco, hist_RECO_name));


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


void Make2DCrossSectionPlots_Interaction(CrossSection_MnvH2D_Map CrossSection_map,CrossSection_MnvH2D_Map CrossSection_mapBG,
  std::string cross_section_units, std::string pdf,bool MakeXaxisLOG,bool doBinwidth,
  Muon2DVar MuonVar, char *Playlist_name, TCanvas *can, MnvPlotter *plot, double POT_Data, double POT_MC){

char title_char[1024];
bool Print1Dplots = false;
double chisqrt = 999;int ndf=0;
std::cout<<"Inside MakeCrossSectionPlots " << std::endl;
/// first Plot Signal Data
std::string X_axis = GetMuon2DVar_XaxisTitle(MuonVar);
std::string Y_axis = GetMuon2DVar_YaxisTitle(MuonVar);
std::string Y_axisUnits = GetMuon2DVar_yaxisUnits(MuonVar);
std::string X_axisUnits = GetMuon2DVar_xaxisUnits(MuonVar);
std::vector<double> Pzbin_vector{1.5, 3.0, 4.0, 5.0, 6.0, 8.0, 10.0, 20.0};
std::vector<double> PTbin_vector{0.0, 0.25, 0.4, 0.55, 0.7, 0.85, 2.5};

char X_axis_char[X_axis.length()+1];
char Y_axis_char[Y_axis.length()+1];
strcpy(X_axis_char, X_axis.c_str());
strcpy(Y_axis_char, Y_axis.c_str());
std::string pdfLabel = pdf + ".pdf";
char pdf_char[pdfLabel.length()+1];
strcpy(pdf_char, pdfLabel.c_str());

std::string title_base = GetMuon2DVar_Title(MuonVar);
char title_base_char[title_base.length()+1];
strcpy(title_base_char ,title_base.c_str());

double Scale = pow(10,-39);
CrossSection_map[Data_crosssection]->Scale(1/Scale);
CrossSection_map[True_crosssection]->Scale(1/Scale);
CrossSection_map[True_crosssection_interaction_Elastic]->Scale(1/Scale);
CrossSection_map[True_crosssection_interaction_DISSIS]->Scale(1/Scale);
CrossSection_map[True_crosssection_interaction_DISSoft]->Scale(1/Scale);
CrossSection_map[True_crosssection_interaction_DISHard]->Scale(1/Scale);
CrossSection_map[True_crosssection_interaction_DeltaRes]->Scale(1/Scale);
CrossSection_map[True_crosssection_interaction_HeavierRes]->Scale(1/Scale);
CrossSection_map[True_crosssection_interaction_2p2h]->Scale(1/Scale);
CrossSection_map[True_crosssection_interaction_other]->Scale(1/Scale);
CrossSection_map[True_crosssection_interaction_none]->Scale(1/Scale);

std::cout<<" 1Title HeavierRes : "<< CrossSection_map[True_crosssection_interaction_HeavierRes]->GetTitle() << std::endl;
std::cout<<" 1Title Res : "<< CrossSection_map[True_crosssection_interaction_DeltaRes]->GetTitle() << std::endl;


// PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type> hist_Stack();

 //hist_Stack.AddComponentHist("QE", CrossSection_map[True_crosssection_interaction_Elastic]);
 //hist_Stack.AddComponentHist("SIS",CrossSection_map[True_crosssection_interaction_DISSIS]);
 //hist_Stack.AddComponentHist("SoftDIS",CrossSection_map[True_crosssection_interaction_DISSoft]);
 //hist_Stack.AddComponentHist("HardDIS",CrossSection_map[True_crosssection_interaction_DISHard]);
 //hist_Stack.AddComponentHist("#DeltaRes",CrossSection_map[True_crosssection_interaction_DeltaRes]);
 //hist_Stack.AddComponentHist("HeavierRes",CrossSection_map[True_crosssection_interaction_HeavierRes]);
 //hist_Stack.AddComponentHist("2p2h",CrossSection_map[True_crosssection_interaction_2p2h]);
 //hist_Stack.AddComponentHist("Other",CrossSection_map[True_crosssection_interaction_other]);
 //hist_Stack.AddComponentHist("None",CrossSection_map[True_crosssection_interaction_none]);
sprintf(title_char, "%s  Data_signal ", title_base_char);
Draw2DHist(CrossSection_map[Data_signal], X_axis_char, Y_axis_char, "NEvents",title_char, pdf_char, can, plot);
sprintf(title_char, "%s  MC_reco ", title_base_char);
Draw2DHist(CrossSection_map[MC_reco], X_axis_char, Y_axis_char, "NEvent" , title_char , pdf_char, can,plot);
//sprintf(title_char, "%s Data_signal_potNorm ", title_base_char);
//Draw2DHist(CrossSection_map[Data_signal_potNorm], X_axis_char, Y_axis_char, "NEvent" ,title_base_char, pdf_char, can,plot);
sprintf(title_char, "%s Data_signal_BGsub_potNorm [F-E] ", title_base_char);
Draw2DHist(CrossSection_map[Data_signal_BGsub_potNorm], X_axis_char, Y_axis_char, "NEvent" , title_char,  pdf_char, can,plot);
sprintf(title_char, "%s RECO_signal_BGsub_potNorm ", title_base_char);
Draw2DHist(CrossSection_map[RECO_signal_BGsub_potNorm], X_axis_char, Y_axis_char, "NEvent" , title_char , pdf_char, can,plot);
sprintf(title_char, "%s Data_signal_unfolded ", title_base_char);
Draw2DHist(CrossSection_map[Data_signal_unfolded], X_axis_char, Y_axis_char, "NEvent" , title_char  , pdf_char, can,plot);
sprintf(title_char, "%s Data_signal_unfolded_effcorrected ", title_base_char);
Draw2DHist(CrossSection_map[Data_signal_unfolded_effcorrected], X_axis_char, Y_axis_char, "NEvent" , title_char , pdf_char, can,plot);
sprintf(title_char, "%s nom_Eff", title_base_char);
Draw2DHist(CrossSection_map[nom_Eff], X_axis_char, Y_axis_char, "NEvent" , title_char , pdf_char, can,plot);
sprintf(title_char, "%s dom_Eff", title_base_char);
Draw2DHist(CrossSection_map[dom_Eff], X_axis_char, Y_axis_char, "NEvent" , title_char , pdf_char, can,plot);

sprintf(title_char, "%s mvnreponse_Mig", title_base_char);
Draw2DHist(CrossSection_map[mvnreponse_Mig], X_axis_char, Y_axis_char, "NEvent" , title_char , pdf_char, can,plot);
sprintf(title_char, "%s mvnreponse_RECO", title_base_char);
Draw2DHist(CrossSection_map[mvnreponse_RECO], X_axis_char, Y_axis_char, "NEvent" , title_char, pdf_char, can,plot);
sprintf(title_char, "%s mvnreponse_TRUE", title_base_char);
Draw2DHist(CrossSection_map[mvnreponse_TRUE], X_axis_char, Y_axis_char, "NEvent" , title_char , pdf_char, can,plot);

bool DoBinN= true;
double Markersize = .3;

std::cout<<"Drawing:PlotDataMC_Migration_ProjX "<< std::endl;

PlotDataMC_Migration_ProjX(CrossSection_map[mvnreponse_Mig], CrossSection_map[mvnreponse_RECO],CrossSection_map[mvnreponse_TRUE],Pzbin_vector,
  pdf_char, "Migration X Projection",  "Reco P_{Z} [GeV/c]",
  "P_{T}",   "True P_{Z} [GeV/c] ",
  100, plot, can,4,.01,Markersize,DoBinN);

std::cout<<"Drawing:PlotDataMC_Migration_Proj=Y "<< std::endl;
PlotDataMC_Migration_ProjY(CrossSection_map[mvnreponse_Mig], CrossSection_map[mvnreponse_RECO],CrossSection_map[mvnreponse_TRUE],PTbin_vector,
  pdf_char, "Migration Y Projection",  "Reco P_{T} [GeV/c]",
  "P_{Z}",   "True P_{T} [GeV/c] ",
  100, plot, can,4,.01,Markersize,DoBinN) ;


PlotDataMC_Migration_ProjX(CrossSection_map[mvnreponse_Mig], CrossSection_map[mvnreponse_RECO],CrossSection_map[mvnreponse_TRUE],Pzbin_vector,
  pdf_char, "Migration X Projection (Row Norm)",  "Reco P_{Z} [GeV/c]",
  "P_{T}",   "True P_{Z} [GeV/c] ",
  1.0, plot, can,3,.01,Markersize,DoBinN) ;


PlotDataMC_Migration_ProjY(CrossSection_map[mvnreponse_Mig], CrossSection_map[mvnreponse_RECO],CrossSection_map[mvnreponse_TRUE],PTbin_vector,
  pdf_char, "Migration Y Projection (Row Norm)",  "Reco P_{T} [GeV/c]",
  "P_{Z}",   "True P_{T} [GeV/c] ",
  1.0, plot, can, 3,.01,Markersize,DoBinN) ;



//  MnvH2D *ProjectMig = GetMigration_Projection_Y_forBinN(CrossSection_map[mvnreponse_Mig], CrossSection_map[mvnreponse_RECO],CrossSection_map[mvnreponse_TRUE], Pzbin_vector , 1 );

MnvH2D *h_return =    new MnvH2D("h_return", "h_return",Pzbin_vector.size()-1, Pzbin_vector.data() ,Pzbin_vector.size()-1, Pzbin_vector.data()  );


//GetMigration_Projection_Y_forBinN_input(h_return, CrossSection_map[mvnreponse_Mig], CrossSection_map[mvnreponse_RECO],CrossSection_map[mvnreponse_TRUE], 1);


for(int  XTruthbinN = 1; XTruthbinN <= CrossSection_map[mvnreponse_TRUE]->GetNbinsX();  XTruthbinN++  ){
  for(int  XRecobinN = 1; XRecobinN <= CrossSection_map[mvnreponse_RECO]->GetNbinsX();  XRecobinN++  ){

    int globalBin =  GetGlobalBinNFrom2DMig_BinN(CrossSection_map[mvnreponse_Mig],CrossSection_map[mvnreponse_RECO], CrossSection_map[mvnreponse_TRUE], XRecobinN, 1 , XTruthbinN, 1);
    double content = CrossSection_map[mvnreponse_Mig]->GetBinContent(globalBin);

    int Global_hreturn_binN  = XTruthbinN*(h_return->GetNbinsX()+2) + XRecobinN; // Assuming Truth is Y axis
    std::cout<< "Global_hreturn_binN = " << Global_hreturn_binN << " content = " << content << std::endl;
    h_return->AddBinContent(Global_hreturn_binN,content);
  }
}


Draw2DHist(h_return, X_axis_char, X_axis_char, "NEvent" , title_char , pdf_char, can,plot);

DrawMagration_heatMap_LabelBinNumber(h_return, "x bins", "y bins",  "bin1", pdf_char, can,plot);


std::string crossSection_z_axis = "#frac{#partial^{2} #sigma}{#partial" + GetMuon2DVar_XaxisTitle_noUntils(MuonVar)+"#partial"+ GetMuon2DVar_YaxisTitle_noUntils(MuonVar) + "} #[]{10^{-39} #frac{ cm^{2}}{" +  GetMuon2DVar_yaxisUnits(MuonVar) + " N} }";
char crossSection_z_axis_char[crossSection_z_axis.length()+1];
strcpy(crossSection_z_axis_char,crossSection_z_axis.c_str());
sprintf(title_char, "%s  Data_crosssection ", title_base_char);
Draw2DHist(CrossSection_map[Data_crosssection],  "data Pt", "data Pz", crossSection_z_axis_char, title_char  ,  pdf_char, can, plot);
sprintf(title_char, "%s  True_crosssection ", title_base_char);
Draw2DHist(CrossSection_map[True_crosssection],  "true Pt", "true Pz", crossSection_z_axis_char, title_char  ,  pdf_char, can, plot);


Draw2DHist(CrossSection_map[True_crosssection_interaction_Elastic], X_axis_char, Y_axis_char, "NEvent" , "True_crosssection_interaction_Elastic" , pdf_char, can,plot);
Draw2DHist(CrossSection_map[True_crosssection_interaction_DISSIS], X_axis_char, Y_axis_char, "NEvent" , "True_crosssection_interaction_DISSIS" , pdf_char, can,plot);
Draw2DHist(CrossSection_map[True_crosssection_interaction_DISSoft], X_axis_char, Y_axis_char, "NEvent" , "True_crosssection_interaction_DISSoft" , pdf_char, can,plot);
Draw2DHist(CrossSection_map[True_crosssection_interaction_DISHard], X_axis_char, Y_axis_char, "NEvent" , "True_crosssection_interaction_DISHard" , pdf_char, can,plot);
Draw2DHist(CrossSection_map[True_crosssection_interaction_DeltaRes], X_axis_char, Y_axis_char, "NEvent" , "True_crosssection_interaction_DeltaRes" , pdf_char, can,plot);
Draw2DHist(CrossSection_map[True_crosssection_interaction_HeavierRes], X_axis_char, Y_axis_char, "NEvent" , "True_crosssection_interaction_HeavierRes" , pdf_char, can,plot);
Draw2DHist(CrossSection_map[True_crosssection_interaction_2p2h], X_axis_char, Y_axis_char, "NEvent" , "True_crosssection_interaction_2p2h" , pdf_char, can,plot);
Draw2DHist(CrossSection_map[True_crosssection_interaction_other], X_axis_char, Y_axis_char, "NEvent" , "True_crosssection_interaction_other" , pdf_char, can,plot);
Draw2DHist(CrossSection_map[True_crosssection_interaction_none], X_axis_char, Y_axis_char, "NEvent" , "True_crosssection_interaction_none" , pdf_char, can,plot);

std::cout<<" Title HeavierRes : "<< CrossSection_map[True_crosssection_interaction_HeavierRes]->GetTitle() << std::endl;
std::cout<<" Title Res : "<< CrossSection_map[True_crosssection_interaction_DeltaRes]->GetTitle() << std::endl;

sprintf(title_char, "%s  Efficiency ", title_base_char);
Draw2DHist(CrossSection_map[Eff], X_axis_char, Y_axis_char, "Eff" , title_char , pdf_char, can,plot);

sprintf(title_char, "%s True denominator Fractional Uncertainty ", title_base_char);
DrawPanel_SystematicErrorPlots_ProjectionY(CrossSection_map[dom_Eff],X_axis, Y_axis, title_char, pdf_char ,.25, true, Print1Dplots );
DrawPanel_SystematicErrorPlots_ProjectionY_model(CrossSection_map[dom_Eff],X_axis, Y_axis, title_char, pdf_char ,.25, true, Print1Dplots );
DrawPanel_SystematicErrorPlots_ProjectionX(CrossSection_map[dom_Eff],X_axis, Y_axis, title_char, pdf_char ,.25, true, Print1Dplots );
DrawPanel_SystematicErrorPlots_ProjectionX_model(CrossSection_map[dom_Eff],X_axis, Y_axis, title_char, pdf_char ,.25, true, Print1Dplots );


sprintf(title_char, "%s  True Denominator", title_base_char);
CrossSection_map[dom_Eff]->Scale(1.0/1000);
CrossSection_map[Data_signal_unfolded]->Scale(1.0/1000);
CrossSection_map[Data_signal_unfolded_effcorrected]->Scale(1.0/1000);
Draw_2D_Panel_MC_Only_frompointer(CrossSection_map[dom_Eff] , title_char, "True Denominator",
Y_axis,Y_axisUnits, X_axis, X_axisUnits,"NEvents(10^{-3})" , 1.1, pdf_char, doBinwidth, MakeXaxisLOG,
.03, .03, false);

sprintf(title_char, "%s Numerator Fractional Uncertainty ", title_base_char);
DrawPanel_SystematicErrorPlots_ProjectionY(CrossSection_map[nom_Eff],X_axis, Y_axis, title_char, pdf_char,.35, true, Print1Dplots );
DrawPanel_SystematicErrorPlots_ProjectionX(CrossSection_map[nom_Eff],X_axis, Y_axis, title_char, pdf_char,.35, true, Print1Dplots );
CrossSection_map[nom_Eff]->Scale(1.0/1000);

sprintf(title_char, "%s  Numerator", title_base_char);
Draw_2D_Panel_MC_Only_frompointer(CrossSection_map[nom_Eff] , title_char, "True Numerator",
Y_axis,Y_axisUnits, X_axis, X_axisUnits,"NEvents(10^{-3})" , 1.1, pdf_char, doBinwidth, MakeXaxisLOG,
.03, .03, false);


sprintf(title_char, "%s  Efficiency Fractional Uncertainty ", title_base_char);
DrawPanel_SystematicErrorPlots_ProjectionY(CrossSection_map[Eff], X_axis, Y_axis, title_char, pdf_char, .1, true, Print1Dplots );
DrawPanel_SystematicErrorPlots_ProjectionX(CrossSection_map[Eff], X_axis, Y_axis, title_char, pdf_char, .1, true, Print1Dplots );

sprintf(title_char, "Efficiency Fractional Uncertainty [ProjX] %s " , title_base_char);
Plot2D_FractionError_ProjX(CrossSection_map[Eff], pdf_char, title_char,  X_axis_char, Y_axis_char, .1,.02);

sprintf(title_char, "Efficiency Fractional Uncertainty [ProjY] %s " , title_base_char);
Plot2D_FractionError_ProjY(CrossSection_map[Eff], pdf_char, title_char,  X_axis_char, Y_axis_char, .1,.02);

//Plot2D_FractionError_ProjY_Group(PlotUtils::MnvH2D* HistInput,
//        char *pdf_label, char *histotitle,  char *xaxislabel, char *GroupName,
//        char *yaxislabel,
//        double Ymax,
//        double text_size);

std::cout<< "Drawing indivdual Systematic errors "<<std::endl;

//DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE FSI",           CrossSection_map[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false  );
//DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE Cross Section", CrossSection_map[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false  );
//DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE CrossSection QE", CrossSection_map[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false, true  );
//DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE CrossSection 1#pi", CrossSection_map[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false, true  );
//DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE CrossSection DIS", CrossSection_map[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false, true  );
//DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE CrossSection NC" ,CrossSection_map[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false, true  );
//DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE Nucleon FSI", CrossSection_map[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false, true  );
//DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE Pion FSI", CrossSection_map[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false, true  );
//DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "Vertex Smearing",     CrossSection_map[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false  );
//DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "2p2h RPA Mvn1Tune",   CrossSection_map[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false  );
//DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "Beam Angle",          CrossSection_map[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false  );
//DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "Muon Reconstruction", CrossSection_map[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false  );
//
//DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "GENIE FSI",           CrossSection_map[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false  );
//DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "GENIE Cross Section", CrossSection_map[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false  );
//DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "GENIE CrossSection QE", CrossSection_map[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false, true  );
//DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "GENIE CrossSection 1#pi", CrossSection_map[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false, true  );
//DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "GENIE CrossSection DIS", CrossSection_map[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false, true  );
//DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "GENIE CrossSection NC", CrossSection_map[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false, true  );
//DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "GENIE Nucleon FSI", CrossSection_map[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false, true  );
//DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "GENIE Pion FSI", CrossSection_map[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false, true  );
//DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "Vertex Smearing",     CrossSection_map[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false  );
//DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "2p2h RPA Mvn1Tune",   CrossSection_map[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false  );
//DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "Beam Angle",          CrossSection_map[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false  );
//DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "Muon Reconstruction", CrossSection_map[Eff], "P_{Z}", "P_{T}",  title_char, pdf_char, .05, true, false  );


DrawPanel_SystematicErrorPlots_ProjectionX(CrossSection_map[Eff], X_axis, Y_axis, title_char, pdf_char, .15, true, Print1Dplots );



sprintf(title_char, "%s  Efficiency ", title_base_char);
Draw_2D_Panel_MC_Only_frompointer(CrossSection_map[Eff], title_char, "Efficiency",
  Y_axis, Y_axisUnits, X_axis, X_axisUnits, "Efficiency" , 1.1, pdf_char, doBinwidth, MakeXaxisLOG,
  .03, .03, false);

Draw_2D_Panel_MC_Only_frompointer_WithErrorBand(CrossSection_map[Eff], title_char, "Efficiency",
Y_axis, Y_axisUnits, X_axis, X_axisUnits, "Efficiency" , 1.1, pdf_char, doBinwidth, MakeXaxisLOG,
.03, .03, false);

std::vector<double> XMultipliers{1,1,1,1,1,1,1,1};
bool do_bin_width_norm_eff = false;
bool statPlusSysDATA = true;
 bool statPlusSysMC  = true;


PlotMC_ErrorBand2D_ProjX(CrossSection_map[Eff],  pdf_char, title_char,  X_axis_char,
  Y_axis_char,   "Efficiency", .1 , false,  false, XMultipliers,
  statPlusSysDATA , statPlusSysMC , do_bin_width_norm_eff, true , .03);

PlotMC_ErrorBand2D_ProjY(CrossSection_map[Eff],  pdf_char, title_char,  Y_axis_char,
    X_axis_char,   "Efficiency", .1 , false,  false, XMultipliers,
    statPlusSysDATA , statPlusSysMC , do_bin_width_norm_eff, true , .03);



sprintf(title_char, "%s Unfolded Data Fractional Uncertainty", title_base_char);
DrawPanel_SystematicErrorPlots_ProjectionY(CrossSection_map[Data_signal_unfolded],X_axis, Y_axis, title_char, pdf_char ,.5, true, Print1Dplots );
DrawPanel_SystematicErrorPlots_ProjectionX(CrossSection_map[Data_signal_unfolded], Y_axis, X_axis, title_char, pdf_char ,.5, true, Print1Dplots );


//CrossSection_map[dom_Eff]->Scale(1.0/1000);
sprintf(title_char, "%s  BG subtracted Unfolded Data ", title_base_char);
//Draw_2D_Panel_MC_Only_frompointer(CrossSection_map[Data_signal_unfolded] , title_char, "Unfolded Data",
//Y_axis,Y_axisUnits, X_axis, X_axisUnits,"NEvents(10^{-3})" , 1.1, pdf_char, doBinwidth, MakeXaxisLOG,
//.03, .03, false);

Draw2D_Panel_CV_SystematicErrFromPointer(CrossSection_map[Data_signal_unfolded], CrossSection_map[dom_Eff], Playlist_name,
   "Combined", plot,
  pdf_char, title_char, Y_axis_char, X_axis_char,
  "NEvents(10^{-3}) / [GeV^{2}/c^{2}]", doBinwidth, MakeXaxisLOG,
  15, 5, .03, .03, chisqrt, ndf, false );

  PlotDataMC_ErrorBand2D_ProjY(CrossSection_map[Data_signal_unfolded], CrossSection_map[dom_Eff],
    pdf_char, title_char ,  Y_axis_char, X_axis_char,   "Events(10^{-3}) / [GeV^{2}/c^{2}]",
    99, false,  true, XMultipliers,
    true , true , doBinwidth,  false, .03);

    PlotDataMC_ErrorBand2D_ProjX(CrossSection_map[Data_signal_unfolded], CrossSection_map[dom_Eff],
      pdf_char, title_char ,  X_axis_char, Y_axis_char,   "Events(10^{-3}) / [GeV^{2}/c^{2}]",
      99, false,  true, XMultipliers,
      true , true , doBinwidth,  false, .03);
      //bool statPlusSysDATA , bool statPlusSysMC ,
        //                 bool do_bin_width_norm,  bool useHistTitles, double text_size


sprintf(title_char, "%s Unfolded Eff corrected Data Fractional Uncertainty", title_base_char);
DrawPanel_SystematicErrorPlots_ProjectionY(CrossSection_map[Data_signal_unfolded_effcorrected],X_axis, Y_axis, title_char, pdf_char ,.35, true, Print1Dplots );
DrawPanel_SystematicErrorPlots_ProjectionX(CrossSection_map[Data_signal_unfolded_effcorrected], Y_axis, X_axis, title_char, pdf_char ,.35, true, Print1Dplots );



sprintf(title_char, "%s  BG subtracted Unfolded Eff corrected Data", title_base_char);
//Draw_2D_Panel_MC_Only_frompointer(CrossSection_map[Data_signal_unfolded_effcorrected] , title_char, "Unfolded Eff corrected Data",
//Y_axis,Y_axisUnits, X_axis, X_axisUnits,"NEvents" , 1.1, pdf_char, doBinwidth, MakeXaxisLOG,
//.03, .03, false);

//Draw2D_Panel_CV_SystematicErrFromPointer(CrossSection_map[Data_signal_unfolded_effcorrected], CrossSection_map[dom_Eff], Playlist_name,
//   "Combined", plot,
//  pdf_char, title_char, Y_axis_char, X_axis_char,
//  "NEvents", doBinwidth, MakeXaxisLOG,
//  15, 5, .03, .03, chisqrt, ndf, false );

//  Draw2D_Panel_CV_SystematicErrFromPointer(CrossSection_map[Data_signal_unfolded_effcorrected],
//    CrossSection_map[dom_Eff],Playlist_name,
//    "Combined", plot,
//    pdf_char, title_char, Y_axis_char, X_axis_char,
//    "Events(10^{-3}) / [GeV^2]", doBinwidth, MakeXaxisLOG,
//    15, 15, .03, .03, chisqrt, ndf, false );


    PlotDataMC_ErrorBand2D_ProjY(CrossSection_map[Data_signal_unfolded_effcorrected], CrossSection_map[dom_Eff],
      pdf_char, title_char ,  Y_axis_char, X_axis_char,   "Events(10^{-3})/[GeV^{2}/c^{2}]",
      99, false,  true, XMultipliers,
      true , true , doBinwidth,  false, .03);

      PlotDataMC_ErrorBand2D_ProjX(CrossSection_map[Data_signal_unfolded_effcorrected], CrossSection_map[dom_Eff],
        pdf_char, title_char ,  X_axis_char, Y_axis_char,   "Events(10^{-3})/[GeV^{2}/c^{2}]",
        99, false,  true, XMultipliers,
        true , true , doBinwidth,  false, .03);


//sprintf(title_char, "%s  Efficiency denominator Fractional uncertainty ", title_base_char);
//DrawPanel_SystematicErrorPlots(CrossSection_map[dom_Eff], Y_axis, X_axis,title_char, pdf_char );
//sprintf(title_char, "%s  Efficiency numeratorFractional uncertainty ", title_base_char);
//DrawPanel_SystematicErrorPlots(CrossSection_map[nom_Eff], Y_axis, X_axis,title_char, pdf_char );
//sprintf(title_char, "%s NEvent ", title_base_char);
// DrawPanel_MC_dataErrorPlots(CrossSection_map[Data_signal],CrossSection_map[MC_reco], Y_axis, X_axis,title_char, pdf_char);

sprintf(title_char, "%s Event Selection", title_base_char);

Draw2D_Panel_CV_SystematicErrFromPointer(CrossSection_map[Data_signal], CrossSection_map[MC_reco],Playlist_name  ,
  "Full", plot,
  pdf_char, title_char, Y_axis_char, X_axis_char,
"Events / [GeV^{2}/c^{2}]", doBinwidth, MakeXaxisLOG,
  100, 100, .03, .03, chisqrt, ndf, false );

PlotDataMC_ErrorBand2D_ProjY(CrossSection_map[Data_signal], CrossSection_map[MC_reco],
  pdf_char, title_char ,  Y_axis_char, X_axis_char,   "Events / [GeV^{2}/c^{2}]",
  99, false,  true, XMultipliers,
  true , true , true,  false, .03);

PlotDataMC_ErrorBand2D_ProjY(CrossSection_map[Data_signal], CrossSection_map[MC_reco],
  CrossSection_mapBG[Data_signal], CrossSection_mapBG[MC_reco],
  pdf_char, title_char ,  Y_axis_char, X_axis_char,   "Events / [GeV^{2}/c^{2}]",
  99, false,  true, XMultipliers,
  true , true , true,  false, .03);


PlotDataMC_ErrorBand2D_ProjX(CrossSection_map[Data_signal], CrossSection_map[MC_reco],
  pdf_char, title_char ,  X_axis_char, Y_axis_char,   "Events / [GeV^{2}/c^{2}]",
  99, false,  true, XMultipliers,
  true , true , true,  false, .03);

PlotDataMC_ErrorBand2D_ProjX(CrossSection_map[Data_signal], CrossSection_map[MC_reco],
  CrossSection_mapBG[Data_signal], CrossSection_mapBG[MC_reco],
  pdf_char, title_char ,  X_axis_char, Y_axis_char,   "Events / [GeV^{2}/c^{2}]",
  99, false,  true, XMultipliers,
  true , true , true,  false, .03);


//
sprintf(title_char, "%s Event Rate BG Subtracted", title_base_char);

Draw2D_Panel_CV_SystematicErrFromPointer(CrossSection_map[Data_signal_BGsub_potNorm],
  CrossSection_map[RECO_signal_BGsub_potNorm],Playlist_name,
  "Combined", plot,
  pdf_char, title_char, Y_axis_char, X_axis_char,
  "Events / [GeV^{2}/c^{2}]", doBinwidth, MakeXaxisLOG,
  15, 15, .03, .03, chisqrt, ndf, false );


PlotDataMC_ErrorBand2D_ProjY(CrossSection_map[Data_signal_BGsub_potNorm], CrossSection_map[RECO_signal_BGsub_potNorm],
  pdf_char, title_char ,  Y_axis_char, Y_axis_char,   "Events / [GeV^{2}/c^{2}]",
  99, false,  true, XMultipliers,
  true , true , true,  false, .03);

PlotDataMC_ErrorBand2D_ProjX(CrossSection_map[Data_signal_BGsub_potNorm], CrossSection_map[RECO_signal_BGsub_potNorm],
  pdf_char, title_char ,  Y_axis_char, Y_axis_char,   "Events / [GeV^{2}/c^{2}]",
  99, false,  true, XMultipliers,
  true , true , true,  false, .03);


sprintf(title_char, "%s Efficiency [%s]",title_base_char, Playlist_name );
Draw2DHist(CrossSection_map[Eff],  X_axis_char, Y_axis_char, "[Efficiency]",
           title_char  ,  pdf_char, can, plot);
std::string titlestring(title_char);

Draw2DHist_Migration_Histpointer(CrossSection_map[Eff], titlestring,
                  X_axis, Y_axis,  "Efficiency",pdf, can, plot);
sprintf(title_char, "%s Migration [%s]",title_base_char, Playlist_name );
Draw2DHist(CrossSection_map[mvnreponse_Mig],  "BinN", "BinN", "[NEvents]", title_char  ,  pdf_char, can, plot);

std::string title_Cross_Section = title_base + " 2D Cross-Section:  #nu_{#mu} + ^{4}He #rightarrow #mu^{-} + X";
char title_Cross_Section_char[title_Cross_Section.length()+1];
strcpy(title_Cross_Section_char,title_Cross_Section.c_str());

//sprintf(title_char, "%s  [%s]",title_base_char, Playlist_name );
//std::string crossSection_z_axis = "#frac{d#sigma}{d" + GetMuon2DVar_XaxisTitle_noUntils(MuonVar)+"d"+ GetMuon2DVar_YaxisTitle_noUntils(MuonVar) + "} (10^{-38} cm^{2} / " +  GetMuon2DVar_yaxisUnits(MuonVar) + " / ^{4}He)";
//char crossSection_z_axis_char[crossSection_z_axis.length()+1];
//strcpy(crossSection_z_axis_char,crossSection_z_axis.c_str());
//
Draw2D_Panel_CV_SystematicErrFromPointer(CrossSection_map[Data_crosssection], CrossSection_map[True_crosssection], Playlist_name,
   "Combined", plot,
  pdf_char, title_Cross_Section_char, Y_axis_char, X_axis_char,
  crossSection_z_axis_char, doBinwidth, MakeXaxisLOG,
  15, 5, .03, .03, chisqrt, ndf, false );


  //Data_signal_unfolded
  //Data_signal_unfolded_effcorrected
  //dom_Eff


bool DataStat_SysError = true;
bool MC_Stat_SysError =true;

  Draw_2D_Panel_MC_andData_frompointer_DISbreakdown(CrossSection_map[Data_crosssection], CrossSection_map[True_crosssection],
    CrossSection_map[True_crosssection_interaction_Elastic],
    CrossSection_map[True_crosssection_interaction_HeavierRes] ,
    CrossSection_map[True_crosssection_interaction_DeltaRes]  ,
    CrossSection_map[True_crosssection_interaction_2p2h] ,
    CrossSection_map[True_crosssection_interaction_DISSIS] ,
     CrossSection_map[True_crosssection_interaction_DISHard] ,
     CrossSection_map[True_crosssection_interaction_DISSoft] ,
     CrossSection_map[True_crosssection_interaction_other],
     CrossSection_map[True_crosssection_interaction_none],
     DataStat_SysError,
     MC_Stat_SysError,
    title_Cross_Section_char, Y_axis,
    X_axis_char,  crossSection_z_axis_char , 1.4, 1.4, false,
    pdf_char,  doBinwidth,  MakeXaxisLOG,
    .03, .03, false);

std::vector<double> Mupl_X{4.0, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0 ,1.0};
std::vector<double> Mupl_Y{1.0, 1.0, 1.0, 1.0, 1.0, 5.0, 5.0,};

    Draw_2D_Panel_MC_andData_frompointer_DISbreakdown(CrossSection_map[Data_crosssection], CrossSection_map[True_crosssection],
      CrossSection_map[True_crosssection_interaction_Elastic],
      CrossSection_map[True_crosssection_interaction_HeavierRes] ,
      CrossSection_map[True_crosssection_interaction_DeltaRes]  ,
      CrossSection_map[True_crosssection_interaction_2p2h] ,
      CrossSection_map[True_crosssection_interaction_DISSIS] ,
       CrossSection_map[True_crosssection_interaction_DISHard] ,
       CrossSection_map[True_crosssection_interaction_DISSoft] ,
       CrossSection_map[True_crosssection_interaction_other],
       CrossSection_map[True_crosssection_interaction_none],
       DataStat_SysError,
       MC_Stat_SysError,
      title_Cross_Section_char, Y_axis,
      X_axis_char,  crossSection_z_axis_char , 25, 3.5, false,
      pdf_char,  doBinwidth,  MakeXaxisLOG,
      .03, .03, true, Mupl_Y, Mupl_X);
/*
      Draw_2D_Panel_MC_andData_frompointer_DISbreakdown_STACK(CrossSection_map[Data_crosssection], CrossSection_map[True_crosssection],
        CrossSection_map[True_crosssection_interaction_Elastic],
        CrossSection_map[True_crosssection_interaction_HeavierRes] ,
        CrossSection_map[True_crosssection_interaction_DeltaRes]  ,
        CrossSection_map[True_crosssection_interaction_2p2h] ,
        CrossSection_map[True_crosssection_interaction_DISSIS] ,
         CrossSection_map[True_crosssection_interaction_DISHard] ,
         CrossSection_map[True_crosssection_interaction_DISSoft] ,
         CrossSection_map[True_crosssection_interaction_other],
         CrossSection_map[True_crosssection_interaction_none],
         DataStat_SysError,
         MC_Stat_SysError,
        title_Cross_Section_char, Y_axis,
        X_axis_char,  crossSection_z_axis_char , 3.5, 25, true,
        pdf_char,  doBinwidth,  MakeXaxisLOG,
        .03, .03, false, Mupl_Y, Mupl_X);
*/
TObjArray stack_input;

stack_input.Add (CrossSection_map[True_crosssection_interaction_Elastic]) ;
stack_input.Add (CrossSection_map[True_crosssection_interaction_HeavierRes]);
stack_input.Add (CrossSection_map[True_crosssection_interaction_DeltaRes]);
stack_input.Add (CrossSection_map[True_crosssection_interaction_2p2h]);
stack_input.Add (CrossSection_map[True_crosssection_interaction_DISSIS]);
stack_input.Add (CrossSection_map[True_crosssection_interaction_DISHard]);
stack_input.Add (CrossSection_map[True_crosssection_interaction_DISSoft]);
stack_input.Add (CrossSection_map[True_crosssection_interaction_other]);
stack_input.Add (CrossSection_map[True_crosssection_interaction_none]);
const TObjArray  *mcHists_Breakdown_input =  &stack_input ;
std::vector<int> Helium9_colorScheme = {
  TColor::GetColor("#F1B6DA"),//pink 11

  TColor::GetColor("#DF00FF"), //'psychedelic Purple1
  TColor::GetColor(43,206,72 ), //green 2
  TColor::GetColor("#87CEEB"),//'skyblue' 3
  TColor::GetColor("#0859C6"), //blue 4
  TColor::GetColor("#654522"), // yellowishbrown,5
  TColor::GetColor("#ffc922"), //'sunset yellow'6
  TColor::GetColor("#f47835"),//2 candy Apple7
  TColor::GetColor("#800000"),  // Maroon
  TColor::GetColor("#90AD1C"),//8
  TColor::GetColor("#BABABA"), //Gray 9
  TColor::GetColor("#00FFFF"),//'aqua' 10
  TColor::GetColor("#AAF0D1"), // mint green
  TColor::GetColor(kRed),//'Jade' 12
  TColor::GetColor("#FAFAD2"),  // LightGoldenRodYellow 13

  TColor::GetColor("#555555"),  // dark grey 15
  TColor::GetColor(0, 153, 143 ), //turquoise 16
  TColor::GetColor("#654522"), // yellowishbrown, 17
  TColor::GetColor("#8db600"), // yellowgreen, 18
  TColor::GetColor("#D3D3D3"),  //'lightgrey' 19
  TColor::GetColor("#90AD1C"), // 20
  TColor::GetColor("#CCDDAA"), //21
  TColor::GetColor(kMagenta), //22
  TColor::GetColor("#EEFF00") // neonyellow,0
};

PlotDataStackedMC2D_ProjY(CrossSection_map[Data_crosssection], CrossSection_map[True_crosssection], mcHists_Breakdown_input,
                                       Helium9_colorScheme, doBinwidth,
                                      pdf_char, title_Cross_Section_char,  X_axis_char,
                                      Y_axis_char,   crossSection_z_axis_char,
                                      5.5, true,  true,
                                       Mupl_Y );

PlotDataStackedMC2D_ProjX(CrossSection_map[Data_crosssection], CrossSection_map[True_crosssection], mcHists_Breakdown_input,
 Helium9_colorScheme, doBinwidth,
  pdf_char, title_Cross_Section_char,  Y_axis_char,
  X_axis_char,   crossSection_z_axis_char,
  .95, true,  true,
  Mupl_X );


PlotFractionofEvents2D_ProjY(CrossSection_map[True_crosssection], mcHists_Breakdown_input,
                           Helium9_colorScheme,"Fraction per Bin" ,
                           "Fraction Total",
                           pdf_char, "Cross-Section Interaction Breakdown",    X_axis_char,
                           Y_axis_char,  "Fraction of Events");

PlotFractionofEvents2D_ProjX(CrossSection_map[True_crosssection], mcHists_Breakdown_input,
                              Helium9_colorScheme,"Fraction per Bin" ,
                              "Fraction Total",
                              pdf_char, "Cross-Section Interaction Breakdown",    Y_axis_char,
                              X_axis_char,  "Fraction of Events");




bool DoRatio= true;
      Draw_2D_Panel_MC_andData_frompointer_DISbreakdown(CrossSection_map[Data_crosssection], CrossSection_map[True_crosssection],
        CrossSection_map[True_crosssection_interaction_Elastic],
        CrossSection_map[True_crosssection_interaction_HeavierRes] ,
        CrossSection_map[True_crosssection_interaction_DeltaRes]  ,
        CrossSection_map[True_crosssection_interaction_2p2h] ,
        CrossSection_map[True_crosssection_interaction_DISSIS] ,
         CrossSection_map[True_crosssection_interaction_DISHard] ,
         CrossSection_map[True_crosssection_interaction_DISSoft] ,
         CrossSection_map[True_crosssection_interaction_other],
         CrossSection_map[True_crosssection_interaction_none],
         DataStat_SysError,
         false,
        title_Cross_Section_char, Y_axis,
        X_axis_char,  "Ratio to Nominal GENIE [MvnTune-v1]" , 2.4, 2.4, true,
        pdf_char,  false,  MakeXaxisLOG,
        .03, .03, false, DoRatio);



sprintf(title_char, "%s CrossSection Data Fractional Uncertainty ", title_base_char);
  DrawPanel_SystematicErrorPlots_ProjectionY(CrossSection_map[Data_crosssection], X_axis, Y_axis, title_char, pdf_char, .5, true, Print1Dplots );
  DrawPanel_SystematicErrorPlots_ProjectionX(CrossSection_map[Data_crosssection], X_axis, Y_axis, title_char, pdf_char, .5, true, Print1Dplots );

  DrawPanel_SystematicErrorPlots_ProjectionY_model(CrossSection_map[Data_crosssection], X_axis, Y_axis, title_char, pdf_char, .15, true, Print1Dplots );
  DrawPanel_SystematicErrorPlots_ProjectionX_model(CrossSection_map[Data_crosssection], X_axis, Y_axis, title_char, pdf_char, .15, true, Print1Dplots );


  //DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE FSI",           CrossSection_map[Data_crosssection], X_axis, Y_axis_char,  title_char, pdf_char, .13, true, false  );
  //DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "GENIE FSI",           CrossSection_map[Data_crosssection], Y_axis_char,X_axis,  title_char, pdf_char, .13, true, false  );
  //DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE Cross Section", CrossSection_map[Data_crosssection], X_axis, Y_axis_char,  title_char, pdf_char, .13, true, false  );
  //DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "GENIE Cross Section", CrossSection_map[Data_crosssection], Y_axis_char,X_axis,  title_char, pdf_char, .13, true, false  );
  //DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "Vertex Smearing",     CrossSection_map[Data_crosssection], X_axis, Y_axis_char,  title_char, pdf_char, .13, true, false  );
  //DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "Vertex Smearing",     CrossSection_map[Data_crosssection], Y_axis_char,X_axis,  title_char, pdf_char, .13, true, false  );
  //DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "2p2h RPA Mvn1Tune",   CrossSection_map[Data_crosssection], X_axis, Y_axis_char,  title_char, pdf_char, .13, true, false  );
  //DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "2p2h RPA Mvn1Tune",   CrossSection_map[Data_crosssection], Y_axis_char,X_axis,  title_char, pdf_char, .13, true, false  );
  //DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "Beam Angle",          CrossSection_map[Data_crosssection], X_axis, Y_axis_char,  title_char, pdf_char, .13, true, false  );
  //DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "Beam Angle",          CrossSection_map[Data_crosssection], Y_axis_char,X_axis,  title_char, pdf_char, .13, true, false  );
  //DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "Muon Reconstruction", CrossSection_map[Data_crosssection], X_axis, Y_axis_char,  title_char, pdf_char, .13, true, false  );
  //DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "Muon Reconstruction", CrossSection_map[Data_crosssection], Y_axis_char,X_axis,  title_char, pdf_char, .13, true, false  );

  Plot2D_FractionError_ProjY_Group(CrossSection_map[Data_crosssection],   pdf_char, "GENIE CrossSection QE",  Y_axis_char, "GENIE CrossSection QE",   X_axis_char,  .05, .03);
  Plot2D_FractionError_ProjY_Group(CrossSection_map[Data_crosssection],   pdf_char, "GENIE CrossSection 1#pi", Y_axis_char, "GENIE CrossSection 1#pi", X_axis_char,  .05, .03);
  Plot2D_FractionError_ProjY_Group(CrossSection_map[Data_crosssection],   pdf_char, "GENIE CrossSection DIS", Y_axis_char, "GENIE CrossSection DIS",  X_axis_char,  .05, .03);
  Plot2D_FractionError_ProjY_Group(CrossSection_map[Data_crosssection],   pdf_char, "GENIE CrossSection NC",  Y_axis_char, "GENIE CrossSection NC",   X_axis_char,  .05, .03);
  Plot2D_FractionError_ProjY_Group(CrossSection_map[Data_crosssection],   pdf_char, "GENIE Nucleon FSI",      Y_axis_char, "GENIE Nucleon FSI",       X_axis_char,  .05, .03);
  Plot2D_FractionError_ProjY_Group(CrossSection_map[Data_crosssection],   pdf_char, "GENIE Pion FSI",         Y_axis_char, "GENIE Pion FSI",          X_axis_char,  .05, .03);
  Plot2D_FractionError_ProjY_Group(CrossSection_map[Data_crosssection],   pdf_char, "Vertex Smearing",        Y_axis_char, "Vertex Smearing",         X_axis_char,  .05, .03, false);
  Plot2D_FractionError_ProjY_Group(CrossSection_map[Data_crosssection],   pdf_char, "Muon Reconstruction",    Y_axis_char, "Muon Reconstruction",     X_axis_char,  .05, .03, false);
  Plot2D_FractionError_ProjY_Group(CrossSection_map[Data_crosssection],   pdf_char, "Beam Angle",             Y_axis_char, "Beam Angle",              X_axis_char,  .05, .03, false);
  Plot2D_FractionError_ProjY_Group(CrossSection_map[Data_crosssection],   pdf_char, "2p2h RPA Mvn1Tune",             Y_axis_char, "2p2h RPA Mvn1Tune",              X_axis_char,  .05, .03, false);


  auto names = CrossSection_map[Data_crosssection]->GetErrorBandNames();

  for(auto cat : names ){std::cout<<"Error band on data name: "<<  cat << std::endl;}


  //DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE FSI",           CrossSection_map[Data_crosssection], X_axis, Y_axis,  title_char, pdf_char, .05, true, false  );
  //DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE Cross Section", CrossSection_map[Data_crosssection], X_axis, Y_axis,  title_char, pdf_char, .05, true, false  );
  DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE CrossSection QE", CrossSection_map[Data_crosssection], X_axis, Y_axis,  title_char, pdf_char, .05, true, false, true  );
  DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE CrossSection 1#pi", CrossSection_map[Data_crosssection], X_axis, Y_axis,  title_char, pdf_char,.05, true, false, true  );
  DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE CrossSection DIS", CrossSection_map[Data_crosssection], X_axis, Y_axis,  title_char, pdf_char,.05, true, false, true  );
  DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE CrossSection NC", CrossSection_map[Data_crosssection], X_axis, Y_axis,  title_char, pdf_char, .05, true, false, true  );
  DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE Nucleon FSI", CrossSection_map[Data_crosssection], X_axis, Y_axis,  title_char, pdf_char,     .05, true, false, true  );
  DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE Pion FSI",      CrossSection_map[Data_crosssection], X_axis, Y_axis,  title_char, pdf_char,        .05, true, false, true  );
  DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "Vertex Smearing",     CrossSection_map[Data_crosssection], X_axis, Y_axis,  title_char, pdf_char, .05, true, false  );
  DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "2p2h RPA Mvn1Tune",   CrossSection_map[Data_crosssection], X_axis, Y_axis,  title_char, pdf_char, .05, true, false  );
  DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "Beam Angle",          CrossSection_map[Data_crosssection], X_axis, Y_axis,  title_char, pdf_char, .05, true, false  );
  DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "Muon Reconstruction", CrossSection_map[Data_crosssection], X_axis, Y_axis,  title_char, pdf_char, .05, true, false  );
  DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "Flux", CrossSection_map[Data_crosssection], X_axis, Y_axis,  title_char, pdf_char, .05, true, false  );


  Plot2D_FractionError_ProjX_Group(CrossSection_map[Data_crosssection],   pdf_char, "GENIE CrossSection QE", X_axis_char, "GENIE CrossSection QE", Y_axis_char,  .05, .03);
  Plot2D_FractionError_ProjX_Group(CrossSection_map[Data_crosssection],   pdf_char, "GENIE CrossSection 1#pi", X_axis_char, "GENIE CrossSection 1#pi", Y_axis_char,  .05, .03);
  Plot2D_FractionError_ProjX_Group(CrossSection_map[Data_crosssection],   pdf_char, "GENIE CrossSection DIS", X_axis_char, "GENIE CrossSection DIS", Y_axis_char,  .05, .03);
  Plot2D_FractionError_ProjX_Group(CrossSection_map[Data_crosssection],   pdf_char, "GENIE CrossSection NC", X_axis_char, "GENIE CrossSection NC", Y_axis_char,  .05, .03);
  Plot2D_FractionError_ProjX_Group(CrossSection_map[Data_crosssection],   pdf_char, "GENIE Nucleon FSI", X_axis_char, "GENIE Nucleon FSI", Y_axis_char,  .05, .03);
  Plot2D_FractionError_ProjX_Group(CrossSection_map[Data_crosssection],   pdf_char, "GENIE Pion FSI", X_axis_char, "GENIE Pion FSI", Y_axis_char,  .05, .03);

  Plot2D_FractionError_ProjX_Group(CrossSection_map[Data_crosssection],   pdf_char, "Vertex Smearing", X_axis_char, "Vertex Smearing", Y_axis_char,  .05, .03, false);
  Plot2D_FractionError_ProjX_Group(CrossSection_map[Data_crosssection],   pdf_char, "Muon Reconstruction", X_axis_char, "Muon Reconstruction", Y_axis_char,  .05, .03, false);
  Plot2D_FractionError_ProjX_Group(CrossSection_map[Data_crosssection],   pdf_char, "Beam Angle", X_axis_char, "Beam Angle", Y_axis_char,  .05, .03, false);
  Plot2D_FractionError_ProjX_Group(CrossSection_map[Data_crosssection],   pdf_char, "2p2h RPA Mvn1Tune", X_axis_char, "2p2h RPA Mvn1Tune", Y_axis_char,  .05, .03, false);



  DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "GENIE FSI",           CrossSection_map[Data_crosssection], Y_axis, X_axis,  title_char, pdf_char, .05, true, false  );
  DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "GENIE Cross Section", CrossSection_map[Data_crosssection], Y_axis, X_axis,  title_char, pdf_char, .05, true, false  );
  DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "GENIE CrossSection QE", CrossSection_map[Data_crosssection], Y_axis, X_axis,  title_char, pdf_char, .05, true, false, true  );
  DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "GENIE CrossSection 1#pi", CrossSection_map[Data_crosssection], Y_axis, X_axis,  title_char, pdf_char, .05, true, false, true  );
  DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "GENIE CrossSection DIS", CrossSection_map[Data_crosssection], Y_axis, X_axis,  title_char, pdf_char, .05, true, false, true  );
  DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "GENIE CrossSection NC", CrossSection_map[Data_crosssection], Y_axis, X_axis,  title_char, pdf_char, .05, true, false, true  );
  DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "GENIE Nucleon FSI", CrossSection_map[Data_crosssection], Y_axis, X_axis,  title_char, pdf_char, .05, true, false, true  );
  DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "GENIE Pion FSI", CrossSection_map[Data_crosssection], Y_axis, X_axis,  title_char, pdf_char, .05, true, false, true  );
  DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "Vertex Smearing",     CrossSection_map[Data_crosssection], Y_axis, X_axis,  title_char, pdf_char, .05, true, false  );
  DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "2p2h RPA Mvn1Tune",   CrossSection_map[Data_crosssection], Y_axis, X_axis,  title_char, pdf_char, .05, true, false  );
  DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "Beam Angle",          CrossSection_map[Data_crosssection], Y_axis, X_axis,  title_char, pdf_char, .05, true, false  );
  DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "Muon Reconstruction", CrossSection_map[Data_crosssection], Y_axis, X_axis,  title_char, pdf_char, .05, true, false  );
  DrawPanel_SystematicErrorPlots_ProjectionX_Groups( "Flux", CrossSection_map[Data_crosssection], Y_axis, X_axis,  title_char, pdf_char, .05, true, false  );


Plot2D_FractionError_ProjY(CrossSection_map[Data_crosssection], pdf_char, title_char,  Y_axis_char, X_axis_char, .15,.03);
Plot2D_FractionError_ProjX(CrossSection_map[Data_crosssection], pdf_char, title_char,  X_axis_char, Y_axis_char, .15,.025);

sprintf(title_char, "%s CrossSection True Model Fractional Uncertainty ", title_base_char);
Plot2D_FractionError_ProjY(CrossSection_map[True_crosssection], pdf_char, title_char,  Y_axis_char, X_axis_char, .15,.03);
Plot2D_FractionError_ProjX(CrossSection_map[True_crosssection], pdf_char, title_char,  X_axis_char, Y_axis_char, .15,.025);



  //Draw_2D_Panel_MC_andData_frompointer(CrossSection_map[Data_crosssection], CrossSection_map[True_crosssection],
  //  hist_Stack, title_Cross_Section_char, X_axis, Y_axis, crossSection_z_axis_char , 1, 1, pdf_char, doBinwidth,  MakeXaxisLOG,
  //    .03, .03 );

//
//(MnvH2D *hist_Data, MnvH2D *hist_MC,
//  PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type> hist_Stack,
//  char *histotitle, std::string xaxislabel,
//   std::string yaxislabel,const char *Zaxislabel , double max_x, double max_y,
//    char *pdf_label, bool doBinwidth, bool MakeXaxisLOG,
//    double x_projectionTxtsize, double y_projectionTxtsize )

//Draw2D_Panel_CV_SystematicErrFromPointer(CrossSection_map[Data_signal], CrossSection_map[Data_signal],Playlist_name  ,
//  "F-E", plot,
//  pdf_char, title_Cross_Section_char, X_axis_char, Y_axis_char,
//  crossSection_z_axis_char, doBinwidth, MakeXaxisLOG,
//  15, 15, .03, .03, chisqrt, ndf );





std::cout<<"Made CrossSection_map[dom_Eff]" << std::endl;


return;
}
/////////////////////////////////////////////////////
//
////////////////////////////////////////////////////
void Make2DCrossSectionPlots_Interaction_Theta(CrossSection_MnvH2D_Map CrossSection_map,CrossSection_MnvH2D_Map CrossSection_mapBG,
  std::string cross_section_units, std::string pdf,bool MakeXaxisLOG,bool doBinwidth,
  Muon2DVar MuonVar, char *Playlist_name, TCanvas *can, MnvPlotter *plot, double POT_Data, double POT_MC){

char title_char[1024];
bool Print1Dplots = false;
double chisqrt = 999;int ndf=0;
std::cout<<"Inside MakeCrossSectionPlots " << std::endl;
/// first Plot Signal Data
std::string X_axis = GetMuon2DVar_XaxisTitle(MuonVar);
std::string Y_axis = GetMuon2DVar_YaxisTitle(MuonVar);
std::string Y_axisUnits = GetMuon2DVar_yaxisUnits(MuonVar);
std::string X_axisUnits = GetMuon2DVar_xaxisUnits(MuonVar);
std::vector<double> Ebin_vector{2.0, 4.0, 5.0, 6.0, 8.0, 10.0, 20.0, 50.0};
std::vector<double> Thetabin_vector{0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 12.0};
std::vector<double> XMultipliers{1,1,1,1,1,1,1,1,1,1,1,1,1};
bool dontBinwidthNorm = false;

char X_axis_char[X_axis.length()+1];
char Y_axis_char[Y_axis.length()+1];
strcpy(X_axis_char, X_axis.c_str());
strcpy(Y_axis_char, Y_axis.c_str());
std::string pdfLabel = pdf + ".pdf";
char pdf_char[pdfLabel.length()+1];
strcpy(pdf_char, pdfLabel.c_str());

char pdf_char1[pdf.length()+1];
strcpy(pdf_char1, pdf.c_str());



std::string title_base = GetMuon2DVar_Title(MuonVar);
char title_base_char[title_base.length()+1];
strcpy(title_base_char ,title_base.c_str());

double Scale = pow(10,-39);
CrossSection_map[Data_crosssection]->Scale(1/Scale);
CrossSection_map[True_crosssection]->Scale(1/Scale);
CrossSection_map[True_crosssection_interaction_Elastic]->Scale(1/Scale);
CrossSection_map[True_crosssection_interaction_DISSIS]->Scale(1/Scale);
CrossSection_map[True_crosssection_interaction_DISSoft]->Scale(1/Scale);
CrossSection_map[True_crosssection_interaction_DISHard]->Scale(1/Scale);
CrossSection_map[True_crosssection_interaction_DeltaRes]->Scale(1/Scale);
CrossSection_map[True_crosssection_interaction_HeavierRes]->Scale(1/Scale);
CrossSection_map[True_crosssection_interaction_2p2h]->Scale(1/Scale);
CrossSection_map[True_crosssection_interaction_other]->Scale(1/Scale);
CrossSection_map[True_crosssection_interaction_none]->Scale(1/Scale);


// PlotUtils::HistFolio<PlotUtils::MnvH2D, Interaction_type> hist_Stack();

 //hist_Stack.AddComponentHist("QE", CrossSection_map[True_crosssection_interaction_Elastic]);
 //hist_Stack.AddComponentHist("SIS",CrossSection_map[True_crosssection_interaction_DISSIS]);
 //hist_Stack.AddComponentHist("SoftDIS",CrossSection_map[True_crosssection_interaction_DISSoft]);
 //hist_Stack.AddComponentHist("HardDIS",CrossSection_map[True_crosssection_interaction_DISHard]);
 //hist_Stack.AddComponentHist("#DeltaRes",CrossSection_map[True_crosssection_interaction_DeltaRes]);
 //hist_Stack.AddComponentHist("HeavierRes",CrossSection_map[True_crosssection_interaction_HeavierRes]);
 //hist_Stack.AddComponentHist("2p2h",CrossSection_map[True_crosssection_interaction_2p2h]);
 //hist_Stack.AddComponentHist("Other",CrossSection_map[True_crosssection_interaction_other]);
 //hist_Stack.AddComponentHist("None",CrossSection_map[True_crosssection_interaction_none]);
sprintf(title_char, "%s  Data_signal ", title_base_char);
Draw2DHist(CrossSection_map[Data_signal], X_axis_char, Y_axis_char, "NEvents",title_char, pdf_char, can, plot);
sprintf(title_char, "%s  MC_reco ", title_base_char);
Draw2DHist(CrossSection_map[MC_reco], X_axis_char, Y_axis_char, "NEvent" , title_char , pdf_char, can,plot);
//sprintf(title_char, "%s Data_signal_potNorm ", title_base_char);
//Draw2DHist(CrossSection_map[Data_signal_potNorm], X_axis_char, Y_axis_char, "NEvent" ,title_base_char, pdf_char, can,plot);
sprintf(title_char, "%s Data_signal_BGsub_potNorm [F-E] ", title_base_char);
Draw2DHist(CrossSection_map[Data_signal_BGsub_potNorm], X_axis_char, Y_axis_char, "NEvent" , title_char,  pdf_char, can,plot);
sprintf(title_char, "%s RECO_signal_BGsub_potNorm ", title_base_char);
Draw2DHist(CrossSection_map[RECO_signal_BGsub_potNorm], X_axis_char, Y_axis_char, "NEvent" , title_char , pdf_char, can,plot);
sprintf(title_char, "%s Data_signal_unfolded ", title_base_char);
Draw2DHist(CrossSection_map[Data_signal_unfolded], X_axis_char, Y_axis_char, "NEvent" , title_char  , pdf_char, can,plot);
sprintf(title_char, "%s Data_signal_unfolded_effcorrected ", title_base_char);
Draw2DHist(CrossSection_map[Data_signal_unfolded_effcorrected], X_axis_char, Y_axis_char, "NEvent" , title_char , pdf_char, can,plot);
sprintf(title_char, "%s nom_Eff", title_base_char);
Draw2DHist(CrossSection_map[nom_Eff], X_axis_char, Y_axis_char, "NEvent" , title_char , pdf_char, can,plot);
sprintf(title_char, "%s dom_Eff", title_base_char);
Draw2DHist(CrossSection_map[dom_Eff], X_axis_char, Y_axis_char, "NEvent" , title_char , pdf_char, can,plot);

sprintf(title_char, "%s mvnreponse_Mig", title_base_char);
Draw2DHist(CrossSection_map[mvnreponse_Mig], X_axis_char, Y_axis_char, "NEvent" , title_char , pdf_char, can,plot);
sprintf(title_char, "%s mvnreponse_RECO", title_base_char);
Draw2DHist(CrossSection_map[mvnreponse_RECO], X_axis_char, Y_axis_char, "NEvent" , title_char, pdf_char, can,plot);
sprintf(title_char, "%s mvnreponse_TRUE", title_base_char);
Draw2DHist(CrossSection_map[mvnreponse_TRUE], X_axis_char, Y_axis_char, "NEvent" , title_char , pdf_char, can,plot);


bool DoBinN= true;
double Markersize = .3;

std::cout<<"Drawing:PlotDataMC_Migration_ProjX "<< std::endl;

PlotDataMC_Migration_ProjX(CrossSection_map[mvnreponse_Mig], CrossSection_map[mvnreponse_RECO],CrossSection_map[mvnreponse_TRUE],Ebin_vector,
  pdf_char, "Migration X Projection",  "Reco E_{#mu} [GeV]",
  " #theta_{#mu}",   "True E_{#mu} [GeV] ",
  100, plot, can,4,.01,Markersize,DoBinN);

std::cout<<"Drawing:PlotDataMC_Migration_Proj=Y "<< std::endl;
PlotDataMC_Migration_ProjY(CrossSection_map[mvnreponse_Mig], CrossSection_map[mvnreponse_RECO],CrossSection_map[mvnreponse_TRUE],Thetabin_vector,
  pdf_char, "Migration Y Projection",  "Reco  #theta_{#mu} [Deg]",
  "E_{#mu}",   "True  #theta_{#mu} [Deg] ",
  100, plot, can,4,.01,Markersize,DoBinN) ;


PlotDataMC_Migration_ProjX(CrossSection_map[mvnreponse_Mig], CrossSection_map[mvnreponse_RECO],CrossSection_map[mvnreponse_TRUE],Ebin_vector,
  pdf_char, "Migration X Projection (Row Norm)",  "Reco E_{#mu} [GeV]",
  " #theta_{#mu}",   "True E_{#mu} [GeV] ",
  1.0, plot, can,3,.01,Markersize,DoBinN) ;


PlotDataMC_Migration_ProjY(CrossSection_map[mvnreponse_Mig], CrossSection_map[mvnreponse_RECO],CrossSection_map[mvnreponse_TRUE],Thetabin_vector,
  pdf_char, "Migration Y Projection (Row Norm)",  " #theta_{#mu} [Deg]",
  "E_{#mu}",   "True  #theta_{#mu} [Deg] ",
  1.0, plot, can, 3,.01,Markersize,DoBinN) ;


std::string crossSection_z_axis = "#frac{#partial^{2} #sigma}{#partial" + GetMuon2DVar_XaxisTitle_noUntils(MuonVar)+"#partial"+ GetMuon2DVar_YaxisTitle_noUntils(MuonVar) + "} #[]{10^{-39} #frac{ cm^{2}}{" + GetMuon2DVar_xaxisUnits(MuonVar) + " "+ GetMuon2DVar_yaxisUnits(MuonVar) + " N} }";


//std::string crossSection_z_axis = "#frac{d#sigma}{d" + GetMuon2DVar_XaxisTitle_noUntils(MuonVar)+"d"+ GetMuon2DVar_YaxisTitle_noUntils(MuonVar) + "} (10^{-39} cm^{2} / " +  GetMuon2DVar_yaxisUnits(MuonVar) + " / nucleon)";
char crossSection_z_axis_char[crossSection_z_axis.length()+1];
strcpy(crossSection_z_axis_char,crossSection_z_axis.c_str());
sprintf(title_char, "%s  Data_crosssection ", title_base_char);
Draw2DHist(CrossSection_map[Data_crosssection],  "data #theta_{#mu}", "data E_{#mu}", crossSection_z_axis_char, title_char  ,  pdf_char, can, plot);
sprintf(title_char, "%s  True_crosssection ", title_base_char);
Draw2DHist(CrossSection_map[True_crosssection],  "true #theta_{#mu}", "true E_{#mu}", crossSection_z_axis_char, title_char  ,  pdf_char, can, plot);


Draw2DHist(CrossSection_map[True_crosssection_interaction_Elastic], X_axis_char, Y_axis_char, "NEvent" , "True_crosssection_interaction_Elastic" , pdf_char, can,plot);
Draw2DHist(CrossSection_map[True_crosssection_interaction_DISSIS], X_axis_char, Y_axis_char, "NEvent" , "True_crosssection_interaction_DISSIS" , pdf_char, can,plot);
Draw2DHist(CrossSection_map[True_crosssection_interaction_DISSoft], X_axis_char, Y_axis_char, "NEvent" , "True_crosssection_interaction_DISSoft" , pdf_char, can,plot);
Draw2DHist(CrossSection_map[True_crosssection_interaction_DISHard], X_axis_char, Y_axis_char, "NEvent" , "True_crosssection_interaction_DISHard" , pdf_char, can,plot);
Draw2DHist(CrossSection_map[True_crosssection_interaction_DeltaRes], X_axis_char, Y_axis_char, "NEvent" , "True_crosssection_interaction_DeltaRes" , pdf_char, can,plot);
Draw2DHist(CrossSection_map[True_crosssection_interaction_HeavierRes], X_axis_char, Y_axis_char, "NEvent" , "True_crosssection_interaction_HeavierRes" , pdf_char, can,plot);
Draw2DHist(CrossSection_map[True_crosssection_interaction_2p2h], X_axis_char, Y_axis_char, "NEvent" , "True_crosssection_interaction_2p2h" , pdf_char, can,plot);
Draw2DHist(CrossSection_map[True_crosssection_interaction_other], X_axis_char, Y_axis_char, "NEvent" , "True_crosssection_interaction_other" , pdf_char, can,plot);
Draw2DHist(CrossSection_map[True_crosssection_interaction_none], X_axis_char, Y_axis_char, "NEvent" , "True_crosssection_interaction_none" , pdf_char, can,plot);



sprintf(title_char, "%s  Efficiency ", title_base_char);
Draw2DHist(CrossSection_map[Eff], X_axis_char, Y_axis_char, "Eff" , title_char , pdf_char, can,plot);

sprintf(title_char, "%s True denominator Fractional Uncertainty ", title_base_char);
DrawPanel_SystematicErrorPlots_ProjectionY_E_theta(CrossSection_map[dom_Eff],X_axis, Y_axis, title_char, pdf_char ,.3, true, Print1Dplots );
DrawPanel_SystematicErrorPlots_ProjectionX_E_theta(CrossSection_map[dom_Eff],X_axis, Y_axis, title_char, pdf_char ,.3, true, Print1Dplots );

sprintf(title_char, "%s  True Denominator", title_base_char);
CrossSection_map[dom_Eff]->Scale(1.0/1000);

Draw_2D_Panel_MC_Only_frompointer(CrossSection_map[dom_Eff] , title_char, "True Denominator",
Y_axis,Y_axisUnits, X_axis, X_axisUnits,"NEvents(10^{-3})" , 1.1, pdf_char, doBinwidth, MakeXaxisLOG,
.03, .03, false);
sprintf(title_char, "%s Numerator Fractional Uncertainty ", title_base_char);
DrawPanel_SystematicErrorPlots_ProjectionY_E_theta(CrossSection_map[nom_Eff],X_axis, Y_axis, title_char, pdf_char,.4, true, Print1Dplots );
DrawPanel_SystematicErrorPlots_ProjectionX_E_theta(CrossSection_map[nom_Eff],X_axis, Y_axis, title_char, pdf_char,.4, true, Print1Dplots );
CrossSection_map[nom_Eff]->Scale(1.0/1000);

sprintf(title_char, "%s  Numerator", title_base_char);
Draw_2D_Panel_MC_Only_frompointer(CrossSection_map[nom_Eff] , title_char, "True Numerator",
Y_axis,Y_axisUnits, X_axis, X_axisUnits,"NEvents(10^{-3})" , 1.1, pdf_char, doBinwidth, MakeXaxisLOG,
.03, .03, false);

sprintf(title_char, "%s  Efficiency ", title_base_char);
Draw_2D_Panel_MC_Only_frompointer_WithErrorBand(CrossSection_map[Eff], title_char, "Efficiency",
  Y_axis, Y_axisUnits, X_axis, X_axisUnits, "Efficiency" , 1.1, pdf_char, doBinwidth, MakeXaxisLOG,
  .03, .03, false);
  sprintf(title_char, "%s Efficiency Fractional Uncertainty ", title_base_char);
  DrawPanel_SystematicErrorPlots_ProjectionY_E_theta(CrossSection_map[Eff],X_axis, Y_axis, title_char, pdf_char,.4, true, Print1Dplots );
  DrawPanel_SystematicErrorPlots_ProjectionX_E_theta(CrossSection_map[Eff],X_axis, Y_axis, title_char, pdf_char,.4, true, Print1Dplots );



sprintf(title_char, "%s  Efficiency Fractional Uncertainty ", title_base_char);
DrawPanel_SystematicErrorPlots_ProjectionY_E_theta(CrossSection_map[Eff], X_axis, Y_axis, title_char, pdf_char, .3, true, Print1Dplots );

DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE FSI",           CrossSection_map[Eff], "E_{#mu}", "#theta_{#mu}",  title_char, pdf_char, .05, true, false );
DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE Cross Section", CrossSection_map[Eff], "E_{#mu}", "#theta_{#mu}",  title_char, pdf_char, .1, true, false  );


//DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE CrossSection QE", CrossSection_map[Eff], "E_{#mu}", "#theta_{#mu}",  title_char, pdf_char, .1, true, false, true  );
//DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE CrossSection RES", CrossSection_map[Eff], "E_{#mu}", "#theta_{#mu}",  title_char, pdf_char, .1, true, false, true  );
//DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE CrossSection DIS", CrossSection_map[Eff], "E_{#mu}", "#theta_{#mu}",  title_char, pdf_char, .1, true, false, true  );
//DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE CrossSection NC", CrossSection_map[Eff], "E_{#mu}", "#theta_{#mu}",  title_char, pdf_char, .1, true, false, true  );
//DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE Nucleon FSI", CrossSection_map[Eff], "E_{#mu}", "#theta_{#mu}",  title_char, pdf_char, .1, true, false, true  );
//DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE Pion FSI", CrossSection_map[Eff], "E_{#mu}", "#theta_{#mu}",  title_char, pdf_char, .1, true, false, true  );



DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "Vertex Smearing",     CrossSection_map[Eff], "E_{#mu}", "#theta_{#mu}",  title_char, pdf_char, .15, true, false  );
DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "2p2h RPA Mvn1Tune",   CrossSection_map[Eff], "E_{#mu}", "#theta_{#mu}",  title_char, pdf_char, .15, true, false  );
DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "Beam Angle",          CrossSection_map[Eff], "E_{#mu}", "#theta_{#mu}",  title_char, pdf_char, .15, true, false  );
DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "Muon Reconstruction", CrossSection_map[Eff], "E_{#mu}", "#theta_{#mu}",  title_char, pdf_char, .15, true, false  );



DrawPanel_SystematicErrorPlots_ProjectionX(CrossSection_map[Eff], X_axis, Y_axis, title_char, pdf_char, .3, true, Print1Dplots );


sprintf(title_char, "%s EventSection with BG ", title_base_char);
PlotDataMC_ErrorBand2D_ProjY(CrossSection_map[Data_signal], CrossSection_map[MC_reco],
  CrossSection_mapBG[Data_signal], CrossSection_mapBG[MC_reco],
  pdf_char, title_char ,  Y_axis_char, X_axis_char,   "Events / [GeV]",
  99, false,  true, XMultipliers,
  true , true , true,  false, .03);

PlotDataMC_ErrorBand2D_ProjX(CrossSection_map[Data_signal], CrossSection_map[MC_reco],
  CrossSection_mapBG[Data_signal], CrossSection_mapBG[MC_reco],
  pdf_char, title_char ,  X_axis_char, Y_axis_char,   "Events / [GeV]",
  99, false,  true, XMultipliers,
  true , true , true,  false, .03);


sprintf(title_char, "%s Event Rate BG Subtracted", title_base_char);

  PlotDataMC_ErrorBand2D_ProjY(CrossSection_map[Data_signal_BGsub_potNorm], CrossSection_map[RECO_signal_BGsub_potNorm],
    pdf_char, title_char ,  Y_axis_char, X_axis_char,   "Events",
    99, false,  true, XMultipliers,
    true , true , true,  false, .03);

  PlotDataMC_ErrorBand2D_ProjX(CrossSection_map[Data_signal_BGsub_potNorm], CrossSection_map[RECO_signal_BGsub_potNorm],
    pdf_char, title_char ,  X_axis_char, Y_axis_char,   "Events ",
    99, false,  true, XMultipliers,
    true , true , true,  false, .03);

    sprintf(title_char, "%s  Efficiency ", title_base_char);
    bool do_bin_width_norm_eff = false;
    bool statPlusSysDATA = true;
     bool statPlusSysMC  = true;

      PlotMC_ErrorBand2D_ProjX(CrossSection_map[Eff],  pdf_char, title_char,  X_axis_char,
      Y_axis_char,   "Efficiency", .1 , false,  false, XMultipliers,
      statPlusSysDATA , statPlusSysMC , do_bin_width_norm_eff, true , .03);

    PlotMC_ErrorBand2D_ProjY(CrossSection_map[Eff],  pdf_char, title_char,  Y_axis_char,
        X_axis_char,   "Efficiency", .1 , false,  false, XMultipliers,
        statPlusSysDATA , statPlusSysMC , do_bin_width_norm_eff, true , .03);


  //      PlotUtils::MnvH2D* mc,
  //                               char *pdf_label, char *histotitle,  char *xaxislabel,
  //                               char *yaxislabel,   char * zaxislabel_units,
  //                                double Ymax, bool setMaxY,  bool doMultipliers,
  //                                std::vector<double> XMultipliers,
  //                               bool statPlusSysDATA , bool statPlusSysMC ,
  //                                bool do_bin_width_norm,  bool useHistTitles, double text_size


Draw_2D_Panel_MC_Only_frompointer(CrossSection_map[Eff], title_char, "Efficiency",
  Y_axis, Y_axisUnits, X_axis, X_axisUnits, "Efficiency" , 1.1, pdf_char, doBinwidth, MakeXaxisLOG,
  .03, .03, false);

  Draw_2D_Panel_MC_Only_frompointer_WithErrorBand(CrossSection_map[Eff], title_char, "Efficiency",
    Y_axis, Y_axisUnits, X_axis, X_axisUnits, "Efficiency" , 1.1, pdf_char, doBinwidth, MakeXaxisLOG,
    .03, .03, false);

sprintf(title_char, "%s Unfolded Data Fractional Uncertainty", title_base_char);
DrawPanel_SystematicErrorPlots_ProjectionY_E_theta(CrossSection_map[Data_signal_unfolded],X_axis, Y_axis, title_char, pdf_char ,.5, true, Print1Dplots );
DrawPanel_SystematicErrorPlots_ProjectionX_E_theta(CrossSection_map[Data_signal_unfolded],X_axis, Y_axis, title_char, pdf_char ,.5, true, Print1Dplots );

CrossSection_map[Data_signal_unfolded]->Scale(1.0/1000);
sprintf(title_char, "%s  Unfolded Data", title_base_char);
//Draw_2D_Panel_MC_Only_frompointer(CrossSection_map[Data_signal_unfolded] , title_char, "Unfolded Data",
//Y_axis,Y_axisUnits, X_axis, X_axisUnits,"NEvents(10^{-3})" , 1.1, pdf_char, doBinwidth, MakeXaxisLOG,
//.03, .03, false);

PlotDataMC_ErrorBand2D_ProjY(CrossSection_map[Data_signal_unfolded], CrossSection_map[dom_Eff],
  pdf_char, title_char ,  Y_axis_char, X_axis_char,   "Events(10^{-3})",
  99, false,  true, XMultipliers,
  true , true , true,  false, .03);

  PlotDataMC_ErrorBand2D_ProjX(CrossSection_map[Data_signal_unfolded], CrossSection_map[dom_Eff],
    pdf_char, title_char ,  X_axis_char, Y_axis_char,   "Events(10^{-3})",
    99, false,  true, XMultipliers,
    true , true , true,  false, .03);



sprintf(title_char, "%s Unfolded Eff corrected Data Fractional Uncertainty", title_base_char);
DrawPanel_SystematicErrorPlots_ProjectionY_E_theta(CrossSection_map[Data_signal_unfolded_effcorrected],X_axis, Y_axis, title_char, pdf_char ,.5, true, Print1Dplots );
DrawPanel_SystematicErrorPlots_ProjectionX_E_theta(CrossSection_map[Data_signal_unfolded_effcorrected],X_axis, Y_axis, title_char, pdf_char ,.5, true, Print1Dplots );


sprintf(title_char, "%s  BG subtracted Unfolded Eff corrected Data", title_base_char);
//Draw_2D_Panel_MC_Only_frompointer(CrossSection_map[Data_signal_unfolded_effcorrected] , title_char, "Unfolded Eff corrected Data",
//Y_axis,Y_axisUnits, X_axis, X_axisUnits,"NEvents" , 1.1, pdf_char, doBinwidth, MakeXaxisLOG,
//.03, .03, false);

CrossSection_map[Data_signal_unfolded_effcorrected]->Scale(1.0/1000);

PlotDataMC_ErrorBand2D_ProjY(CrossSection_map[Data_signal_unfolded_effcorrected], CrossSection_map[dom_Eff],
  pdf_char, title_char ,  Y_axis_char, X_axis_char,   "Events(10^{-3})",
  99, false,  true, XMultipliers,
  true , true , true,  false, .03);

  PlotDataMC_ErrorBand2D_ProjX(CrossSection_map[Data_signal_unfolded_effcorrected], CrossSection_map[dom_Eff],
    pdf_char, title_char ,  X_axis_char, Y_axis_char,   "Events(10^{-3})",
    99, false,  true, XMultipliers,
    true , true , true,  false, .03);



//sprintf(title_char, "%s  Efficiency denominator Fractional uncertainty ", title_base_char);
//DrawPanel_SystematicErrorPlots(CrossSection_map[dom_Eff], Y_axis, X_axis,title_char, pdf_char );
//sprintf(title_char, "%s  Efficiency numeratorFractional uncertainty ", title_base_char);
//DrawPanel_SystematicErrorPlots(CrossSection_map[nom_Eff], Y_axis, X_axis,title_char, pdf_char );
//sprintf(title_char, "%s NEvent ", title_base_char);
// DrawPanel_MC_dataErrorPlots(CrossSection_map[Data_signal],CrossSection_map[MC_reco], Y_axis, X_axis,title_char, pdf_char);

sprintf(title_char, "%s  Full  ", title_base_char);
Draw2D_Panel_CV_SystematicErrFromPointer(CrossSection_map[Data_signal], CrossSection_map[MC_reco],Playlist_name  ,
  "Full", plot,
  pdf_char, title_char, Y_axis_char, X_axis_char,
"Nevent", doBinwidth, MakeXaxisLOG,
  100, 100, .03, .03, chisqrt, ndf, false );
//

//
//
sprintf(title_char, "%s Event Rate", title_base_char);
Draw2D_Panel_CV_SystematicErrFromPointer(CrossSection_map[Data_signal_BGsub_potNorm],
  CrossSection_map[RECO_signal_BGsub_potNorm],Playlist_name,
       "Combined", plot,
    pdf_char, title_char, Y_axis_char, X_axis_char,
    "Events / [GeV]", doBinwidth, MakeXaxisLOG,
    15, 15, .03, .03, chisqrt, ndf, false );


sprintf(title_char, "%s Efficiency [%s]",title_base_char, Playlist_name );
Draw2DHist(CrossSection_map[Eff],  X_axis_char, Y_axis_char, "[Efficiency]",
           title_char  ,  pdf_char, can, plot);
std::string titlestring(title_char);

Draw2DHist_Migration_Histpointer(CrossSection_map[Eff], titlestring,
                  X_axis, Y_axis,  "Efficiency",pdf, can, plot);
sprintf(title_char, "%s Migration [%s]",title_base_char, Playlist_name );
Draw2DHist(CrossSection_map[mvnreponse_Mig],  "BinN", "BinN", "[NEvents]", title_char  ,  pdf_char, can, plot);

std::string title_Cross_Section = title_base + " 2D Cross-Section:  #nu_{#mu} + ^{4}He #rightarrow #mu^{-} + X";
char title_Cross_Section_char[title_Cross_Section.length()+1];
strcpy(title_Cross_Section_char,title_Cross_Section.c_str());

//sprintf(title_char, "%s  [%s]",title_base_char, Playlist_name );
//std::string crossSection_z_axis = "#frac{d#sigma}{d" + GetMuon2DVar_XaxisTitle_noUntils(MuonVar)+"d"+ GetMuon2DVar_YaxisTitle_noUntils(MuonVar) + "} (10^{-38} cm^{2} / " +  GetMuon2DVar_yaxisUnits(MuonVar) + " / ^{4}He)";
//char crossSection_z_axis_char[crossSection_z_axis.length()+1];
//strcpy(crossSection_z_axis_char,crossSection_z_axis.c_str());
//
Draw2D_Panel_CV_SystematicErrFromPointer(CrossSection_map[Data_crosssection], CrossSection_map[True_crosssection], Playlist_name,
   "Combined", plot, pdf_char, title_Cross_Section_char, Y_axis_char, X_axis_char,
  crossSection_z_axis_char, dontBinwidthNorm, MakeXaxisLOG, 15, 5, .03, .03, chisqrt, ndf, false );

bool DataStat_SysError = true;
bool MC_Stat_SysError =true;
  Draw_2D_Panel_MC_andData_frompointer_DISbreakdown_E_theta(CrossSection_map[Data_crosssection], CrossSection_map[True_crosssection],
    CrossSection_map[True_crosssection_interaction_Elastic],
    CrossSection_map[True_crosssection_interaction_HeavierRes] ,
    CrossSection_map[True_crosssection_interaction_DeltaRes]  ,
    CrossSection_map[True_crosssection_interaction_2p2h] ,
    CrossSection_map[True_crosssection_interaction_DISSIS] ,
     CrossSection_map[True_crosssection_interaction_DISHard] ,
     CrossSection_map[True_crosssection_interaction_DISSoft] ,
     CrossSection_map[True_crosssection_interaction_other],
     CrossSection_map[True_crosssection_interaction_none],
     DataStat_SysError,
     MC_Stat_SysError,
    title_Cross_Section_char, Y_axis,
    X_axis_char,  crossSection_z_axis_char , 1.4, 1.4, false,
    pdf_char,  dontBinwidthNorm,  MakeXaxisLOG,
    .03, .03, false);

std::vector<double> Mupl_X{30.0, 10.0, 5.0, 2.0, 2.0, 2.0, 2.0 ,2.0, 2.0, 2.0, 1.0};
std::vector<double> Mupl_Y{1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 2.0, 1.0, 10.0, 10.0, 10.0, 10.0};

    Draw_2D_Panel_MC_andData_frompointer_DISbreakdown_E_theta(CrossSection_map[Data_crosssection], CrossSection_map[True_crosssection],
      CrossSection_map[True_crosssection_interaction_Elastic],
      CrossSection_map[True_crosssection_interaction_HeavierRes] ,
      CrossSection_map[True_crosssection_interaction_DeltaRes]  ,
      CrossSection_map[True_crosssection_interaction_2p2h] ,
      CrossSection_map[True_crosssection_interaction_DISSIS] ,
       CrossSection_map[True_crosssection_interaction_DISHard] ,
       CrossSection_map[True_crosssection_interaction_DISSoft] ,
       CrossSection_map[True_crosssection_interaction_other],
       CrossSection_map[True_crosssection_interaction_none],
       DataStat_SysError,
       MC_Stat_SysError,
      title_Cross_Section_char, Y_axis,
      X_axis_char,  crossSection_z_axis_char , 1.0, 1.0, true,
      pdf_char,  dontBinwidthNorm,  MakeXaxisLOG,
      .03, .03, true, Mupl_Y, Mupl_X);


      bool DoRatio= true;
    Draw_2D_Panel_MC_andData_frompointer_DISbreakdown_E_theta(CrossSection_map[Data_crosssection], CrossSection_map[True_crosssection],
              CrossSection_map[True_crosssection_interaction_Elastic],
              CrossSection_map[True_crosssection_interaction_HeavierRes] ,
              CrossSection_map[True_crosssection_interaction_DeltaRes]  ,
              CrossSection_map[True_crosssection_interaction_2p2h] ,
              CrossSection_map[True_crosssection_interaction_DISSIS] ,
               CrossSection_map[True_crosssection_interaction_DISHard] ,
               CrossSection_map[True_crosssection_interaction_DISSoft] ,
               CrossSection_map[True_crosssection_interaction_other],
               CrossSection_map[True_crosssection_interaction_none],
               DataStat_SysError,
               false,
              title_Cross_Section_char, Y_axis,
              X_axis_char,  "Ratio to Nominal GENIE [MvnTune-v1]" , 1.0, 1.0, true,
              pdf_char,  false,  MakeXaxisLOG,
              .03, .03, false, DoRatio);



sprintf(title_char, "%s CrossSection Data Fractional Uncertainty ", title_base_char);
  DrawPanel_SystematicErrorPlots_ProjectionY_E_theta(CrossSection_map[Data_crosssection], X_axis, Y_axis, title_char, pdf_char, .5, true, Print1Dplots );
  DrawPanel_SystematicErrorPlots_ProjectionX_E_theta(CrossSection_map[Data_crosssection], X_axis, Y_axis, title_char, pdf_char, .5, true, Print1Dplots );

  DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE FSI",           CrossSection_map[Data_crosssection], "E_{#mu}", "#theta_{#mu}",  title_char, pdf_char, .13, true, false  );
  DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "GENIE Cross Section", CrossSection_map[Data_crosssection], "E_{#mu}", "#theta_{#mu}",  title_char, pdf_char, .13, true, false  );
  DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "Vertex Smearing",     CrossSection_map[Data_crosssection], "E_{#mu}", "#theta_{#mu}",  title_char, pdf_char, .13, true, false  );
  DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "2p2h RPA Mvn1Tune",   CrossSection_map[Data_crosssection], "E_{#mu}", "#theta_{#mu}",  title_char, pdf_char, .13, true, false  );
  DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "Beam Angle",          CrossSection_map[Data_crosssection], "E_{#mu}", "#theta_{#mu}",  title_char, pdf_char, .13, true, false  );
  DrawPanel_SystematicErrorPlots_ProjectionY_Groups( "Muon Reconstruction", CrossSection_map[Data_crosssection], "E_{#mu}", "#theta_{#mu}",  title_char, pdf_char, .13, true, false  );


  TObjArray stack_input;

  stack_input.Add (CrossSection_map[True_crosssection_interaction_Elastic]) ;
  stack_input.Add (CrossSection_map[True_crosssection_interaction_HeavierRes]);
  stack_input.Add (CrossSection_map[True_crosssection_interaction_DeltaRes]);
  stack_input.Add (CrossSection_map[True_crosssection_interaction_2p2h]);
  stack_input.Add (CrossSection_map[True_crosssection_interaction_DISSIS]);
  stack_input.Add (CrossSection_map[True_crosssection_interaction_DISHard]);
  stack_input.Add (CrossSection_map[True_crosssection_interaction_DISSoft]);
  stack_input.Add (CrossSection_map[True_crosssection_interaction_other]);
  stack_input.Add (CrossSection_map[True_crosssection_interaction_none]);
  const TObjArray  *mcHists_Breakdown_input =  &stack_input ;
   TObjArray  *mcHists_Breakdown_input1 =  &stack_input ;
  std::vector<int> Helium9_colorScheme = {
    TColor::GetColor("#F1B6DA"),//pink 11

    TColor::GetColor("#DF00FF"), //'psychedelic Purple1
    TColor::GetColor(43,206,72 ), //green 2
    TColor::GetColor("#87CEEB"),//'skyblue' 3
    TColor::GetColor("#0859C6"), //blue 4
    TColor::GetColor("#654522"), // yellowishbrown,5
    TColor::GetColor("#ffc922"), //'sunset yellow'6
    TColor::GetColor("#f47835"),//2 candy Apple7
    TColor::GetColor("#800000"),  // Maroon
    TColor::GetColor("#90AD1C"),//8
    TColor::GetColor("#BABABA"), //Gray 9
    TColor::GetColor("#00FFFF"),//'aqua' 10
    TColor::GetColor("#AAF0D1"), // mint green
    TColor::GetColor(kRed),//'Jade' 12
    TColor::GetColor("#FAFAD2"),  // LightGoldenRodYellow 13

    TColor::GetColor("#555555"),  // dark grey 15
    TColor::GetColor(0, 153, 143 ), //turquoise 16
    TColor::GetColor("#654522"), // yellowishbrown, 17
    TColor::GetColor("#8db600"), // yellowgreen, 18
    TColor::GetColor("#D3D3D3"),  //'lightgrey' 19
    TColor::GetColor("#90AD1C"), // 20
    TColor::GetColor("#CCDDAA"), //21
    TColor::GetColor(kMagenta), //22
    TColor::GetColor("#EEFF00") // neonyellow,0
  };

  PlotDataStackedMC2D_ProjY(CrossSection_map[Data_crosssection], CrossSection_map[True_crosssection], mcHists_Breakdown_input,
                                         Helium9_colorScheme, dontBinwidthNorm,
                                        pdf_char, title_Cross_Section_char,  X_axis_char,
                                        Y_axis_char,   crossSection_z_axis_char,
                                        .65, true,  true,
                                         Mupl_Y );

  PlotDataStackedMC2D_ProjX(CrossSection_map[Data_crosssection], CrossSection_map[True_crosssection], mcHists_Breakdown_input,
   Helium9_colorScheme, dontBinwidthNorm,
    pdf_char, title_Cross_Section_char,  Y_axis_char,
    X_axis_char,   crossSection_z_axis_char,
    .85, true,  true,
    Mupl_X );

    std::vector<Interaction_Map> Interaction_Map_vector =  Interaction_vector( mcHists_Breakdown_input1, false, 1.0);
    DrawPieFigures_Interaction(Interaction_Map_vector,  pdf_char1, can, plot, false, false, "none", "True Cross-Section Interaction" );



    PlotFractionofEvents2D_ProjY(CrossSection_map[True_crosssection], mcHists_Breakdown_input,
                               Helium9_colorScheme,"Fraction per Bin" ,
                               "Fraction Total",
                               pdf_char, "Cross Sections Interaction Breakdown",    X_axis_char,
                               Y_axis_char,  "Fraction of Events");

    PlotFractionofEvents2D_ProjX(CrossSection_map[True_crosssection], mcHists_Breakdown_input,
                                  Helium9_colorScheme,"Fraction per Bin" ,
                                  "Fraction Total",
                                  pdf_char, "Cross Sections Interaction Breakdown",    Y_axis_char,
                                  X_axis_char,  "Fraction of Events");




std::cout<<"Made CrossSection_map[dom_Eff]" << std::endl;


return;
}




MnvH2D *Copy(MnvH2D *hist_input, char * name){
  MnvH2D *hist = (PlotUtils::MnvH2D*)hist_input->Clone(name);

  return hist;

}
