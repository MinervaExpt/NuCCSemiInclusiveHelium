#include "Make_CrossSection_Plots.h"



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




sprintf(text_title_pdf1, "PLOTS_%s_CrossSection_new.pdf(","" );
can -> Print(text_title_pdf1);
sprintf(text_title_pdf2, "PLOTS_%s_CrossSection_new.pdf","" );
sprintf(text_title_pdf3, "PLOTS_%s_CrossSection_new.pdf)","" );
sprintf(text_title_pdf4, "PLOTS_%s_CrossSection_new","" );
 pdf_CV = string(text_title_pdf4);

  std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;
  std::cout<< "  Ploting 1D Cross Section "<< std::endl;
  std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;



std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~       Starting Plotter: Kinematic Plots         ~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

TFile *TFile_CrossSection = new TFile(PlaylistME_CrossSection_Path);

auto muon_vector = GetMUONVaribles_Total();
bool isFull = true;
bool isEmpty = false;
auto muonE_full_names = Generate_CrossSection_histsNames(muon_vector[0], "Full", isFull);
auto muonE_Empty_names = Generate_CrossSection_histsNames(muon_vector[0], "Empty", isEmpty);



auto Map_MuonE_Full_hist = Generate_CrossSection_Hist_Map(*TFile_CrossSection, muonE_full_names);
//auto Map_MuonE_Empty_hist = Generate_CrossSection_Hist_Map(*TFile_CrossSection, muonE_Empty_names);


MakeCrossSectionPlots(Map_MuonE_Full_hist, "GeV", pdf_CV,false,false ,muon_vector[0], "ME1F - ME1G");



Migration_MnvH2D_Map MigHist = Generate_CrossSection_Mig_Hist_Map(*TFile_CrossSection,muon_vector);




PrintCrossSection_MapName(muonE_full_names,"muonE_full_names");
PrintCrossSection_MapName(muonE_Empty_names,"muonE_Empty_names");

auto muonPZ_full_names = Generate_CrossSection_histsNames(muon_vector[1], "Full", isFull);
auto muonPZ_Empty_names = Generate_CrossSection_histsNames(muon_vector[1], "Empty", isEmpty);


auto Map_MuonPZ_Full_hist = Generate_CrossSection_Hist_Map(*TFile_CrossSection, muonPZ_full_names);
MakeCrossSectionPlots(Map_MuonPZ_Full_hist, "GeV", pdf_CV,false,false ,muon_vector[1], "F-E");




auto muonPT_full_names = Generate_CrossSection_histsNames(muon_vector[2], "Full", isFull);
auto muonPT_Empty_names = Generate_CrossSection_histsNames(muon_vector[2], "Empty", isEmpty);

auto Map_MuonPT_Full_hist = Generate_CrossSection_Hist_Map(*TFile_CrossSection, muonPT_full_names);
MakeCrossSectionPlots(Map_MuonPT_Full_hist, "GeV", pdf_CV,false,false ,muon_vector[2], "F-E");



auto muonTheta_full_names = Generate_CrossSection_histsNames(muon_vector[3], "Full", isFull);
auto muonTheta_Empty_names = Generate_CrossSection_histsNames(muon_vector[3], "Empty", isEmpty);


auto Map_MuonTheta_Full_hist = Generate_CrossSection_Hist_Map(*TFile_CrossSection, muonTheta_full_names);
MakeCrossSectionPlots(Map_MuonTheta_Full_hist, "Deg", pdf_CV,false,false ,muon_vector[3], "F-E");




















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
  {std::cout<<"HistName = "<< it->second << std::endl;
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


void MakeCrossSectionPlots(CrossSection_MnvH1D_Map CrossSection_map,std::string cross_section_units, std::string pdf,bool MakeXaxisLOG,bool doBinwidth ,MuonVar MuonVar, char *Playlist_name){


std::cout<<"Inside MakeCrossSectionPlots " << std::endl;
/// first Plot Signal Data
std::string X_axis = GetMuonVarAXISName(MuonVar);
std::string title_Signal_TRUTH = GetMuonVarTitleName(MuonVar) + " TRUTH Signal Selection Dom Eff";
char title_Signal_TRUTH_char[title_Signal_TRUTH.length()+1];
strcpy(title_Signal_TRUTH_char,title_Signal_TRUTH.c_str());
DrawCVAndError_FromHistPointer(CrossSection_map[dom_Eff], title_Signal_TRUTH_char ,X_axis, "Event Rate", pdf,  doBinwidth, MakeXaxisLOG);
std::cout<<"Made CrossSection_map[dom_Eff]" << std::endl;

std::string title_Signal_nomEff = GetMuonVarTitleName(MuonVar) + " Selection Nom Eff";
char title_Signal_nomEff_char[title_Signal_nomEff.length()+1];
strcpy(title_Signal_nomEff_char,title_Signal_nomEff.c_str());
DrawCVAndError_FromHistPointer(CrossSection_map[nom_Eff], title_Signal_nomEff_char ,X_axis, "Event Rate", pdf,  doBinwidth, MakeXaxisLOG);
std::cout<<"Made CrossSection_map[nom_Eff]" << std::endl;


std::string title_Signal = GetMuonVarTitleName(MuonVar) + " Data Signal Selection";
char title_Signal_char[title_Signal.length()+1];
strcpy(title_Signal_char,title_Signal.c_str());
DrawCVAndError_FromHistPointer(CrossSection_map[Data_signal], title_Signal_char ,X_axis, "Event Rate", pdf,  doBinwidth, MakeXaxisLOG);
std::cout<<"Made CrossSection_map[Data_signal]" << std::endl;

std::string title_Signal_Pot = GetMuonVarTitleName(MuonVar) + " Data Signal Selection [POT normalize]";
char title_Signal_Pot_char[title_Signal_Pot.length()+1];
strcpy(title_Signal_Pot_char,title_Signal_Pot.c_str());
DrawCVAndError_FromHistPointer(CrossSection_map[Data_signal_potNorm], title_Signal_Pot_char ,X_axis, "Event Rate", pdf,  doBinwidth, MakeXaxisLOG);
std::cout<<"CrossSection_map[Data_signal_potNorm]" << std::endl;


std::string title_Signal_BG_Sub_Pot = GetMuonVarTitleName(MuonVar) + " Data Signal Selection [POT normalize][BGsub]";
char title_Signal_BG_Sub_Pot_char[title_Signal_BG_Sub_Pot.length()+1];
strcpy(title_Signal_BG_Sub_Pot_char,title_Signal_BG_Sub_Pot.c_str());
DrawCVAndError_FromHistPointer(CrossSection_map[Data_signal_BGsub_potNorm], title_Signal_BG_Sub_Pot_char ,X_axis, "Event Rate", pdf,  doBinwidth, MakeXaxisLOG);
std::cout<<"CossSection_map[Data_signal_BGsub_potNorm]" << std::endl;


std::string title_unfolded = GetMuonVarTitleName(MuonVar) + " Data Signal Selection [POT normalize][BGsub][Unfolded]";
char title_unfolded_char[title_unfolded.length()+1];
strcpy(title_unfolded_char,title_unfolded.c_str());

DrawCVAndError_FromHistPointer(CrossSection_map[Data_signal_unfolded], title_unfolded_char ,X_axis, "Event Rate", pdf,  doBinwidth, MakeXaxisLOG);

std::cout<<"CrossSection_map[Data_signal_unfolded" << std::endl;

std::string title_EffCorr_Pot = GetMuonVarTitleName(MuonVar) + " Data Signal Selection [POT normalize][BGsub][Unfolded][Eff Corr]";
char title_EffCorr_Pot_char[title_EffCorr_Pot.length()+1];
strcpy(title_EffCorr_Pot_char,title_EffCorr_Pot.c_str());

DrawCVAndError_FromHistPointer(CrossSection_map[Data_signal_unfolded_effcorrected], title_EffCorr_Pot_char ,X_axis, "Event Rate", pdf,  doBinwidth, MakeXaxisLOG);
std::cout<<"CrossSection_map[Data_signal_unfolded_effcorrected]" << std::endl;

std::string title_eff = GetMuonVarTitleName(MuonVar) + " Efficiency";
char title_eff_char[title_eff.length()+1];
strcpy(title_eff_char,title_eff.c_str());
DrawCVAndError_FromHistPointer(CrossSection_map[Eff], title_eff_char ,X_axis, "Event Rate", pdf,  doBinwidth, MakeXaxisLOG);

std::cout<<"CrossSection_map[Eff]" << std::endl;

std::string title_Cross_Section = GetMuonVarTitleName(MuonVar) + " Cross-Section:  #nu_{#mu} + ^{4}He #rightarrow #mu^{-} + X";
char title_Cross_Section_char[title_Cross_Section.length()+1];
strcpy(title_Cross_Section_char,title_Cross_Section.c_str());

std::string crossSection_y_axis = "#frac{d#sigma}{d" + GetMuonVar_crosssection(MuonVar) + "} (10^{-38} cm^{2} / " +  cross_section_units + " / ^{4}He)";
char X_axis_char[X_axis.length()+1];
strcpy(X_axis_char,X_axis.c_str());

char crossSection_y_axis_char[crossSection_y_axis.length()+1];
strcpy(crossSection_y_axis_char,crossSection_y_axis.c_str());

double Scale = pow(10,-38);
CrossSection_map[True_crosssection]->Scale(1/Scale);
CrossSection_map[Data_crosssection]->Scale(1/Scale);
Draw_DataWITHMC_SingleHistinput_withRatioCrossSection(CrossSection_map[True_crosssection], CrossSection_map[Data_crosssection],
                                           Playlist_name, pdf, title_Cross_Section_char, "", X_axis_char, crossSection_y_axis_char,
                                          doBinwidth, MakeXaxisLOG,  false);



std::cout<<"CrossSection_map[True_crosssection]" << std::endl;
 //void Draw_DataWITHMC_SingleHistinput_withRatio(MnvH1D *hist_MC, MnvH1D *hist_Data,
     //char *Playlist_name, std::string pdf_label, char *histotitle, std::string units,
      //char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG , bool drawAllErrorGroups= true);


return;
}
/////////////////////////////////////////////////////
//
////////////////////////////////////////////////////
void MakeCrossSection_MigrationPlots(){






}
