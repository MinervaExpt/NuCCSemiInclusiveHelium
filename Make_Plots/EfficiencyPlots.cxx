#include "EfficiencyPlots.h"
//////////////////////////////////////////////////////////////////////////////

void Draw_Efficiency_2ndTrk(std::vector <PlayList_INFO> Playlist, ME_helium_Playlists Playlist_toscaleto , const char *histoName,
  int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf , SecondTrkVar playlist_name );

void Draw_Efficiency_CryoVertex_FULL_EMPTY_TRUTH(PlayList_INFO FULL_playlist_nom, PlayList_INFO FULL_playlist_TRUTHDEM,
  PlayList_INFO EMPTY_playlist_nom, PlayList_INFO EMPTY_playlist_TRUTHDEM , const char *histoName_num, const char *histoName_dem,
  int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf , CryoVertex CryoVertex_type );

void Draw_Efficiency_CryoVertex_FULL_EMPTY_TRUTH(PlayList_INFO FULL_playlist_nom, PlayList_INFO FULL_playlist_TRUTHDEM,
  PlayList_INFO EMPTY_playlist_nom, PlayList_INFO EMPTY_playlist_TRUTHDEM , const char *histoName_num, const char *histoName_dem,
  int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf, CryoVertex CryoVertex_type, bool PrintAllErrors );

void Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(PlayList_INFO FULL_playlist_nom,PlayList_INFO FULL_playlist_TRUTHDEM,
  PlayList_INFO EMPTY_playlist_nom, PlayList_INFO EMPTY_playlist_TRUTH , const char *histoName,
  int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf , SecondTrkVar playlist_name );

void Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(PlayList_INFO FULL_playlist_nom,PlayList_INFO FULL_playlist_TRUTHDEM,
  PlayList_INFO EMPTY_playlist_nom, PlayList_INFO EMPTY_playlist_TRUTHDEM , const char *histoName,
  int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf , SecondTrkVar playlist_name, double Vline_OnXaxis,  bool print_all_errors = false );

void Draw_Efficiency_2D_FULL_EMPTY(PlayList_INFO FULL_playlist,PlayList_INFO EMPTY_playlist , const char *histoName,const char *Xaxis_title,const char *Yaxis_title,
  int logScale,const char* title ,const char* title_type_char , MnvPlotter *plot, TCanvas *can, const char *pdf  );

void Draw_Efficiency_2D_FULL_EMPTY_TRUTH(PlayList_INFO FULL_playlist_nom,PlayList_INFO FULL_playlist_DemTRUE,
  PlayList_INFO EMPTY_playlist_nom,PlayList_INFO EMPTY_playlist_DemTRUE, const char *histoName, const char *Xaxis_title, const char *Yaxis_title,
  const char* title ,const char* title_type_char , MnvPlotter *plot, TCanvas *can, const char *pdf);

void Draw_Efficiency_Muon_FULL_EMPTY(PlayList_INFO FULL_playlist,PlayList_INFO EMPTY_playlist , const char *histoName,
  int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf , MuonVar playlist_name );

void Draw_Efficiency_Muon_FULL_EMPTY_TRUTH(PlayList_INFO FULL_playlist_nom,PlayList_INFO FULL_playlist_TRUTHDEM,
  PlayList_INFO EMPTY_playlist_nom, PlayList_INFO EMPTY_playlist_TRUTH , const char *histoName,
  int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf , MuonVar playlist_name, bool PrintallErrorBands );

void Draw_Resolution_CryoVertex_FULL_EMPTY_RecoBranch(PlayList_INFO FULL_playlist_nom,
  PlayList_INFO EMPTY_playlist_nom,  const char *histoName_Reco, const char *histoName_Reco_Truth,
  int logScale, const char* title,MnvPlotter *plot, TCanvas *can, const char *pdf , CryoVertex playlist_name );


void Draw_Resolution_2D_FULL_EMPTY_TRUTH(PlayList_INFO FULL_playlist_nom, PlayList_INFO EMPTY_playlist_nom,
  const char *histoName, const char *Xaxis_title, const char *Yaxis_title, const char* title ,const char* title_type_char ,
  MnvPlotter *plot, TCanvas *can, const char *pdf, Double_t ymax);

void Draw_Resolution_2D_Helium_nonHelium_FULL_TRUTH(PlayList_INFO FULL_playlist,const char *histoName, const char *Xaxis_title,
  const char *Yaxis_title, const char* title ,const char* title_type_char , MnvPlotter *plot, TCanvas *can, const char *pdf, Double_t ymax);

void Draw_Resolution_2D_Helium_nonHelium_FULL_TRUTH(PlayList_INFO FULL_playlist,PlayList_INFO Empty_playlist,
                                       const char *histoName, const char *Xaxis_title, const char *Yaxis_title,
    const char* title, const char* title_type_char, MnvPlotter *plot, TCanvas *can, const char *pdf, Double_t ymax , bool include_overflows);

void Draw_Ratio_CryoVertex_FULL_EMPTY_RecoBranch(PlayList_INFO FULL_playlist_nom, PlayList_INFO EMPTY_playlist_nom,
  const char *histoName_nom, const char *histoName_dem, int logScale, const char* title, MnvPlotter *plot,
   TCanvas *can, const char *pdf , CryoVertex CryoVertex_type );

void Draw_Migration_2D_FULL_EMPTY_TRUTH(PlayList_INFO FULL_playlist, PlayList_INFO EMPTY_playlist,
  const char *histoName, const char *Xaxis_title, const char *Yaxis_title, const char* title,
  const char* title_type_char , MnvPlotter *plot, TCanvas *can, const char *pdf);


  void Draw_Efficiency_FidiucialCut_FULL_EMPTY_TRUTH(PlayList_INFO FULL_playlist_nom, PlayList_INFO FULL_playlist_TRUTHDEM,
                                                     PlayList_INFO EMPTY_playlist_nom, PlayList_INFO EMPTY_playlist_TRUTHDEM ,
                                                     PlayList_INFO playlist_FULL_Data, PlayList_INFO playlist_EMPTY_Data,
                                                     const char *histoName_MC, const char *histoName_Data,
                                                     const char* title,std::string Xaxis_title, MnvPlotter *plot, bool doBinwidth,
                                                     TCanvas *can,  char *pdf, bool PrintErrors, bool PrintallErrorBands, std::vector<double> Bins, double EffMax );

void MakeLatexForEffMuonVar_StatsOnly(std::string output_name ,  std::string pdf_name_CV, const std::vector<MuonVar> muon_vector);

void Appendtotxt_2ndTrk(std::string output_name ,  std::string pdf_name_CV,int First_page, int Full_empty_space, char *Var_name ,char *Units_name, std::vector<double>input_vectors);

void MakeLatex_CutEfficiency_PurityTable_TGraphs(TFile *inputFile_RECO, const char* TGraphName_RECO, const char* TGraphName_TrueHelium_RECO, TFile *inputFile_TRUTH, const char* TGraphName_TRUTH,const char* Latex_title, const char* Playlistname );

void MakeLatex_WithData_CutTable_TGraphs(TFile *inputFile_Data, const char* TGraphName_Data ,TFile *inputFile_RECO, const char* TGraphName_RECO, double POTscale ,const char* Latex_title, const char* Playlistname );

void MakeLatex_TruthTable_TGraphs( TFile *inputFile_TRUTH, const char* TGraphName_TRUTH,const char* Latex_title, const char* Playlistname );
std::vector<CryoVertex> GetCryoVertexVaribles();

void AppendtoLatex(std::string output_name ,  std::string pdf_name_CV, int Figure_1_page_number,int Figure_2_page_number,
  int Figure_3_page_number, char *slideTitle);

void AppendtoLatex(std::string output_name ,  std::string pdf_name_CV, int Figure_1_page_number,int Figure_2_page_number,
   char *slideTitle , double FiducialCut, double scale );

void AppendtoLatex(std::string output_name ,  std::string pdf_name_CV, int Figure_1_page_number, int Figure_2_page_number,
  int Figure_3_page_number,int Figure_4_page_number, int Figure_5_page_number, int Figure_6_page_number, char *slideTitle);


void Draw_2D_Xaxis_FiducialCut_FULL_EMPTY_TRUTH_Eff_Puritry(PlayList_INFO FULL_TRUE_playlist,
                                                            PlayList_INFO EMPTY_TRUE_playlist,
                                                            PlayList_INFO FULL_RECO_playlist,
                                                             PlayList_INFO EMPTY_RECO_playlist,
  const char *histoName, const char *Xaxis_title, const char *Yaxis_title, const char* title,
  const char* title_type_char , MnvPlotter *plot, TCanvas *can, const char *pdf, double maxY_recoCuts_full, double maxY_TruthCuts_full);

void Draw_2D_Xaxis_FiducialCut_FULL_EMPTY(PlayList_INFO FULL_RECO_playlist,
                                          PlayList_INFO EMPTY_RECO_playlist,
  const char *histoName, const char *Xaxis_title, const char *Yaxis_title,
const char* title ,MnvPlotter *plot, TCanvas *can,
const char *pdf, double maxY_recoCuts_full);

void AppendtoText_Resolution(std::string output_name ,  std::string pdf_name_CV, int Figure_1_page_number,int Figure_2_page_number,
  int Figure_3_page_number, char *slideTitle , double FiducialCut);

void Make_Resolution_vertex_Latex(std::string output_name ,  std::string pdf_name_CV, std::vector<double>FiducialBins,
     int startingPage_figureLeft, int startingPage_figureCenter, int startingPage_figureRight,char *Resolution_type);

std::vector<ME_helium_Playlists> GetPlayListVector_DATA();
void Kin(bool &cutsOn, bool &my_norm, bool &my_debug, const char *userDir) {
TH1::AddDirectory(false);
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~       Starting Plotter: ME Efficiency Plots         ~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::vector<ME_helium_Playlists> GetPlayListVector_MC();
const std::vector< ME_helium_Playlists> kPlayListVector_MC = GetPlayListVector_MC();
std::vector<ME_helium_Playlists> kPlayListVector_DATA = GetPlayListVector_DATA();
Pot_MapStatusList POT_MC_Status, POT_DATA_Status;
std::vector<SecondTrkVar> Get2ndTrkVaribles();
std::vector<MuonVar> GetMUONVaribles();
const std::vector<CryoVertex> kCryoVertexVaribles_vector = GetCryoVertexVaribles();
const std::vector<SecondTrkVar> k2ndTrk_vector = Get2ndTrkVaribles();
const std::vector<MuonVar> kMuonVaribles = GetMUONVaribles();
//FullAndEmptyPlaylistMap PLAYLIST_MAP_MC = MakeFullorEmptyList(kPlayListVector_MC);
//FullAndEmptyPlaylistMap PLAYLIST_MAP_DATA = MakeFullorEmptyList(kPlayListVector_DATA);
SecondTrkVar ksecE, kOpenAngle,kThetamid,kTheta;

/////Playlist///////////
//PlayList_INFO PlaylistMC_1P(kPlayListVector_MC[0], true );
//PlayList_INFO PlaylistMC_1D(kPlayListVector_MC[0], true, true );
//PlayList_INFO PlaylistMC_1A(kPlayListVector_MC[1], true, true );
//PlayList_INFO PlaylistTRUTH_1D(kPlayListVector_MC[0], true );
//PlayList_INFO PlaylistTRUTH_1A(kPlayListVector_MC[1], true );

bool Stats_only= false;
bool AllSystmaticErrors= false;
bool is_mc = true;
//PlayList_INFO PlaylistMC_1F(kPlayListVector_MC[0], is_mc, Stats_only );
//PlayList_INFO PlaylistMC_1G(kPlayListVector_MC[1], is_mc, Stats_only );
//PlayList_INFO PlaylistTRUTH_1F(kPlayListVector_MC[0], Stats_only );
//PlayList_INFO PlaylistTRUTH_1G(kPlayListVector_MC[1], Stats_only );

auto PlaylistME_1F_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1F_MC_All_SysErrorsOn.root";
auto PlaylistME_1G_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1G_MC_All_SysErrorsOn.root";


auto PlaylistME_1F_MC_Efficiency_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1F_MC_All_SysErrorsOn_Efficiency.root";
auto PlaylistME_1G_MC_Efficiency_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1G_MC_All_SysErrorsOn_Efficiency.root";


TFile *PlaylistME_1F_TFile = new TFile(PlaylistME_1F_MC_path);
TFile *PlaylistME_1G_TFile = new TFile(PlaylistME_1G_MC_path);

auto PlaylistME_1F_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1F_TRUTH_All_SysErrorsOn.root";
TFile *PlaylistME_1F_TRUTH_TFile = new TFile(PlaylistME_1F_MC_TRUTH_path);

auto PlaylistME_1G_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1G_TRUTH_All_SysErrorsOn.root";
TFile *PlaylistME_1G_TRUTH_TFile = new TFile(PlaylistME_1G_MC_TRUTH_path);


auto PlaylistME_1F_MC_TRUTH_Efficiency_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1F_TRUTH_All_SysErrorsOn_Efficiency.root";
auto PlaylistME_1G_MC_TRUTH_Efficiency_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1G_TRUTH_All_SysErrorsOn_Efficiency.root";


bool isRECOBranch = false;

PlayList_INFO PlaylistMC_1F(kPlayListVector_MC[0],PlaylistME_1F_MC_Efficiency_path, is_mc, isRECOBranch, AllSystmaticErrors );
PlayList_INFO PlaylistMC_1G(kPlayListVector_MC[1],PlaylistME_1G_MC_Efficiency_path, is_mc, isRECOBranch, AllSystmaticErrors );

POT_MC_Status[kFULL] =  PlaylistMC_1F.Get_Pot();
POT_MC_Status[kEMPTY] =  PlaylistMC_1G.Get_Pot();



PlayList_INFO PlaylistTRUTH_1F(kPlayListVector_MC[0], PlaylistME_1F_MC_TRUTH_Efficiency_path, is_mc, !isRECOBranch, AllSystmaticErrors );
PlayList_INFO PlaylistTRUTH_1G(kPlayListVector_MC[1], PlaylistME_1G_MC_TRUTH_Efficiency_path, is_mc,  !isRECOBranch, AllSystmaticErrors );


PlayList_INFO PlaylistMC_1F_piePlots(kPlayListVector_MC[0],PlaylistME_1F_MC_path, is_mc, isRECOBranch, AllSystmaticErrors );
PlayList_INFO PlaylistMC_1G_piePlots(kPlayListVector_MC[1],PlaylistME_1G_MC_path, is_mc, isRECOBranch, AllSystmaticErrors );

PlayList_INFO PlaylistTRUTH_1F_piePlots(kPlayListVector_MC[0], PlaylistME_1F_MC_TRUTH_path, is_mc, !isRECOBranch, AllSystmaticErrors );
PlayList_INFO PlaylistTRUTH_1G_piePlots(kPlayListVector_MC[1], PlaylistME_1G_MC_TRUTH_path, is_mc, !isRECOBranch, AllSystmaticErrors );



//auto PlaylistMC_1F_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1F_Data.root";
//auto PlaylistMC_1G_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1G_Data.root";



//PlayList_INFO PlaylistMC_1G(kPlayListVector_MC[0], true );
//PlayList_INFO PlaylistMC_1C(kPlayListVector_MC[3], true );
//PlayList_INFO PlaylistMC_1D(kPlayListVector_MC[4], true );

std::vector <PlayList_INFO> Efficiency_Playlist;
std::vector <PlayList_INFO> Efficiency_Playlist_TRUTH;
bool isNOT_mc=false;
PlayList_INFO PlaylistDATA_1F(kPlayListVector_DATA[0], isNOT_mc,false );
PlayList_INFO PlaylistDATA_1G(kPlayListVector_DATA[1], isNOT_mc,false );
std::vector <PlayList_INFO> Data_playlist;
Data_playlist.push_back(PlaylistDATA_1F);
Data_playlist.push_back(PlaylistDATA_1G);
Efficiency_Playlist_TRUTH.push_back(PlaylistTRUTH_1F);
Efficiency_Playlist_TRUTH.push_back(PlaylistTRUTH_1G);
//POT_DATA[kPlayListVector_DATA[0]] = PlaylistDATA_1F.Get_Pot();
//POT_DATA[kPlayListVector_DATA[1]] = PlaylistDATA_1G.Get_Pot();

double PoTMC_ME1F = PlaylistMC_1F.Get_Pot();
double POTData_ME1F = PlaylistDATA_1F.Get_Pot();

POT_DATA_Status[kFULL] = PlaylistDATA_1F.Get_Pot();
POT_DATA_Status[kEMPTY] = PlaylistDATA_1G.Get_Pot();
double POT_Data_MC_ME1F = POTData_ME1F / PoTMC_ME1F;



Efficiency_Playlist.push_back(PlaylistMC_1F);
Efficiency_Playlist.push_back(PlaylistMC_1G);
//Efficiency_Playlist.push_back(PlaylistMC_1G);
//Efficiency_Playlist.push_back(PlaylistMC_1D);
//Efficiency_Playlist.push_back(PlaylistMC_1P);
//Efficiency_Playlist.push_back(PlaylistMC_1A);
//Efficiency_Playlist.push_back(PlaylistMC_1C);
//Efficiency_Playlist.push_back(PlaylistMC_1D);


MnvPlotter *mnv_plot = new MnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
 char text_title_pdf1[2024];
 char text_title_pdf2[2024];
 char text_title_pdf3[2024];
 char text_title_pdf4[2024];
 char text_title_pdf5[2024];

 char Eff2D_pdf1[2024];
 char Eff2D_pdf2[2024];
 char Eff2D_pdf3[2024];
 char Eff2D_pdf4[2024];
 char Eff2D_pdf5[2024];



 char Resolution_title_pdf1[2024];
 char Resolution_title_pdf2[2024];
 char Resolution_title_pdf3[2024];
 char Resolution_title_pdf4[2024];
 char Resolution_title_pdf5[2024];


  char Fiduical_title_pdf1[2024];
  char Fiduical_title_pdf2[2024];
  char Fiduical_title_pdf3[2024];
  char Fiduical_title_pdf4[2024];
  char Fiduical_title_pdf5[2024];


 char Migration_title_pdf1[2024];
 char Migration_title_pdf2[2024];
 char Migration_title_pdf3[2024];
 char Migration_title_pdf4[2024];
 char Migration_title_pdf5[2024];

time_t now = time(0);
tm *ltm = localtime(&now);
 char timeset[2024];
 auto Playlist_names =  MakePlaylistString(kPlayListVector_MC);
sprintf(timeset,"%i_%i_%i_%i_%s",1 + ltm->tm_mon,ltm->tm_mday, ltm->tm_hour,ltm->tm_min,Playlist_names.c_str());

std::cout<<"Start to Calculate and Plot Efficiency"<<std::endl;

std::string pdf = string(text_title_pdf4);


std::cout << std::endl;
std::cout << "Done WITH EfficiencyPlots " << std::endl;

std::ofstream outfile1 ("h_resolutionR_Z_FidiucalCut_latex.txt"); // re-create file from start of script
outfile1.close();
std::ofstream outfile3 ("h_FidiucalCut_cryoVertex_Z_R_latex.txt");
outfile3.close();

std::ofstream outfile5 ("h_FidiucalCut_cryoVertex_R_Num_Dem_latex.txt");
outfile5.close();
std::ofstream outfile6 ("h_FidiucalCut_cryoVertex_Z_Num_Dem_latex.txt");
outfile6.close();
std::ofstream outfile7 ("Efficiency_latex.txt");
outfile7.close();
std::ofstream outfile8 ("Efficiency2D_latex.txt");
outfile8.close();



TCanvas *can2 = new TCanvas("can2");
//TCanvas *can_Mig = new TCanvas("can_Mig");
sprintf(text_title_pdf1, "PLOTS_EfficiencyTRUTH.pdf(" );
can2 -> Print(text_title_pdf1);
sprintf(text_title_pdf2, "PLOTS_EfficiencyTRUTH.pdf");
sprintf(text_title_pdf5, "PLOTS_EfficiencyTRUTH" );
sprintf(text_title_pdf3, "PLOTS_EfficiencyTRUTH.pdf)");
sprintf(text_title_pdf4, "PLOTS_EfficiencyTRUTH");

sprintf(Eff2D_pdf1, "PLOTS_2D_Efficiency.pdf(" );
can2 -> Print(Eff2D_pdf1);
sprintf(Eff2D_pdf2, "PLOTS_2D_Efficiency.pdf");
sprintf(Eff2D_pdf5, "PLOTS_2D_Efficiency" );
sprintf(Eff2D_pdf3, "PLOTS_2D_Efficiency.pdf)");
sprintf(Eff2D_pdf4, "PLOTS_2D_Efficiency");



sprintf(Resolution_title_pdf1, "PLOTS_Resolution.pdf(" );
can2 -> Print(Resolution_title_pdf1);
sprintf(Resolution_title_pdf2, "PLOTS_Resolution.pdf");
sprintf(Resolution_title_pdf5, "PLOTS_Resolution");
sprintf(Resolution_title_pdf3, "PLOTS_Resolution.pdf)");
sprintf(Resolution_title_pdf4, "PLOTS_Resolution");

sprintf(Migration_title_pdf1, "PLOTS_Migration.pdf(" );
can2 -> Print(Migration_title_pdf1);
sprintf(Migration_title_pdf2, "PLOTS_Migration.pdf");
sprintf(Migration_title_pdf5, "PLOTS_Migration");
sprintf(Migration_title_pdf3, "PLOTS_Migration.pdf)");
sprintf(Migration_title_pdf4, "PLOTS_Migration");

sprintf(Fiduical_title_pdf1, "PLOTS_Fiduical.pdf(" );
can2 -> Print(Fiduical_title_pdf1);
sprintf(Fiduical_title_pdf2, "PLOTS_Fiduical.pdf");
sprintf(Fiduical_title_pdf5, "PLOTS_Fiduical");
sprintf(Fiduical_title_pdf3, "PLOTS_Fiduical.pdf)");
sprintf(Fiduical_title_pdf4, "PLOTS_Fiduical");



bool PrintAllBands_muon = true;

for(auto MuonVar : kMuonVaribles){
  auto histName = GetMuonVarHistName(MuonVar);
  int n_histName = histName.length();
  char histName_char[n_histName+1];
  strcpy( histName_char,histName.c_str());

Draw_Efficiency_Muon_FULL_EMPTY_TRUTH(Efficiency_Playlist[0],PlaylistTRUTH_1F,Efficiency_Playlist[1],
                   PlaylistTRUTH_1G, histName_char ,  0, " ", mnv_plot, can2, text_title_pdf5, MuonVar, PrintAllBands_muon );
}

MakeLatexForEffMuonVar_StatsOnly("Efficiency_latex" , text_title_pdf2, kMuonVaribles);

//Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], PlaylistTRUTH_1D, Efficiency_Playlist[1] ,PlaylistTRUTH_1A, "h_secTrk_Energy",
  //0, " ", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[0] );
  std::vector<double> SecTrk_Thetamidbin_vector= GetSecondTrkVarVector(kThetamid);
  //std::vector<double> SecTrk_Theta_TRUEbin_vector= GetSecondTrkVarVector(kFullAngle);


  std::vector<double> Vertex_DOCAbin_vector= GetBinMuonVector(kDOCA_muon);
  std::vector<double> Vertex_secondTrkEbin_vector= GetSecondTrkVarVector(ksecE);
  std::vector<double> Vertex_secondTrkEbin_Proton_vector= GetSecondTrkVarVector(ksecE_Proton);
  //std::sort(Vertex_secondTrkEbin_Proton_vector.begin(),Vertex_secondTrkEbin_Proton_vector.end());
  std::vector<double> Vertex_secondTrkThetamidbin_vector= GetSecondTrkVarVector(kThetamid);
  std::vector<double> SecTrk_DOCA_vector= GetSecondTrkVarVector(kDOCA);
  std::vector<double> SecTrk_Pathway_vector= GetSecondTrkVarVector(kPathway);

MakeLatex_CutEfficiency_PurityTable_TGraphs(PlaylistME_1F_TFile, "RECO_Cuts", "RECO_Helium_Cuts", PlaylistME_1F_TRUTH_TFile, "Truth_Cuts", "ME1F", "ME1F" );
//MakeLatex_WithData_CutTable_TGraphs(PlaylistDATA_1F.TFILE_PLAYLIST, "RECO_Data_Cuts" ,PlaylistME_1F_TFile, "RECO_Cuts", POT_Data_MC_ME1F,"ME1F", "ME1F" );
MakeLatex_TruthTable_TGraphs( PlaylistME_1F_TRUTH_TFile, "Truth_Cuts", "ME1F", "ME1F" );


Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], PlaylistTRUTH_1F, Efficiency_Playlist[1] ,PlaylistTRUTH_1G, "h_secTrk_Energy",
  0, " ", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[0] );

Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], PlaylistTRUTH_1F, Efficiency_Playlist[1] ,PlaylistTRUTH_1G, "h_secTrk_EnergyFINEBinning",
    0, " ", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[0] );

    int start=230;
    int spacing=52;
    Appendtotxt_2ndTrk("Efficiency_latex" ,  text_title_pdf5, start, 4, "secTrk Energy" ,"[GeV]", Vertex_secondTrkEbin_vector);
    start=start+spacing;

//Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], PlaylistTRUTH_1D, Efficiency_Playlist[1] ,PlaylistTRUTH_1A, "h_secTrk_Energy_PROTON",
  //  0, "Proton", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[0] );

Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], PlaylistTRUTH_1F, Efficiency_Playlist[1] ,PlaylistTRUTH_1G, "h_secTrk_Energy_PROTON",
  0, "Proton", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[0], 0.105 /*[GeV]*/, true);

  Appendtotxt_2ndTrk("Efficiency_latex" ,  text_title_pdf5, start, 4, "Leading Non-muon Trk Energy [Proton]" ,"[GeV]", Vertex_secondTrkEbin_Proton_vector);
  start=start+spacing;

Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], PlaylistTRUTH_1F, Efficiency_Playlist[1] ,PlaylistTRUTH_1G, "h_secTrk_Energy_PION",
0, "Pion", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[0] , 0.060 /*[GeV]*/ , true);

      Appendtotxt_2ndTrk("Efficiency_latex" ,  text_title_pdf5,start, 4, "Leading Non-muon Trk Energy [#pi^{#pm}]" ,"[GeV]", Vertex_secondTrkEbin_Proton_vector);
  start=start+spacing;

Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], PlaylistTRUTH_1F, Efficiency_Playlist[1] ,PlaylistTRUTH_1G, "h_secTrk_Energy_Dimuon",
            0, "Dimuon", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[0] );

Appendtotxt_2ndTrk("Efficiency_latex" ,  text_title_pdf5, start, 4, "Leading Non-muon Trk Energy [Dimuon]" ,"[GeV]", Vertex_secondTrkEbin_Proton_vector);
start=start+spacing;

Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], PlaylistTRUTH_1F, Efficiency_Playlist[1] ,PlaylistTRUTH_1G, "h_secTrk_Theta",
0, " ", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[1] , 54.0 /*[Deg]*/ );

Appendtotxt_2ndTrk("Efficiency_latex" ,  text_title_pdf5, start, 4, "Leading Non-muon Trk Theta wrtb" ,"[Deg]", Vertex_secondTrkThetamidbin_vector);
start=start+spacing;

Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], PlaylistTRUTH_1F, Efficiency_Playlist[1] ,PlaylistTRUTH_1G, "h_secTrk_Theta_PROTON",
0, "Proton", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[1] , 54.0 , true  );

Appendtotxt_2ndTrk("Efficiency_latex" ,  text_title_pdf5, start, 4, "Leading Non-muon Trk [Proton] Theta wrtb" ,"[Deg]", Vertex_secondTrkThetamidbin_vector);
start=start+spacing;

Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], PlaylistTRUTH_1F, Efficiency_Playlist[1] ,PlaylistTRUTH_1G, "h_secTrk_Theta_PION",
0, "Pion", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[1], 54.0 , true );

Appendtotxt_2ndTrk("Efficiency_latex" ,  text_title_pdf5, start, 4, "Leading Non-muon Trk [#pi^{#pm}] Theta wrtb" ,"[Deg]", Vertex_secondTrkThetamidbin_vector);
start=start+spacing;

Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], PlaylistTRUTH_1F, Efficiency_Playlist[1] ,PlaylistTRUTH_1G, "h_secTrk_Pathlength",
0, "", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[3], 0.0 , true );


///////////////////////
/// CryoTank Efficieny
///////////////////////

bool PrintAllErrors = true;

Draw_Efficiency_CryoVertex_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], Efficiency_Playlist_TRUTH[0],
 Efficiency_Playlist[1] ,Efficiency_Playlist_TRUTH[1], "h_CryoVertex_X","h_CryoVertex_X",
0, "", mnv_plot, can2, text_title_pdf5 , kCryoVertexVaribles_vector.at(0),PrintAllErrors );

Draw_Efficiency_CryoVertex_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], Efficiency_Playlist_TRUTH[0],
 Efficiency_Playlist[1] ,Efficiency_Playlist_TRUTH[1], "h_CryoVertex_Y","h_CryoVertex_Y",
0, "", mnv_plot, can2, text_title_pdf5 , kCryoVertexVaribles_vector.at(1),PrintAllErrors );

Draw_Efficiency_CryoVertex_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], Efficiency_Playlist_TRUTH[0],
 Efficiency_Playlist[1] ,Efficiency_Playlist_TRUTH[1], "h_CryoVertex_Z","h_CryoVertex_Z",
0, "", mnv_plot, can2, text_title_pdf5 , kCryoVertexVaribles_vector.at(2),PrintAllErrors );

Draw_Efficiency_CryoVertex_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], Efficiency_Playlist_TRUTH[0],
 Efficiency_Playlist[1] ,Efficiency_Playlist_TRUTH[1], "h_CryoVertex_R","h_CryoVertex_R",
0, "", mnv_plot, can2, text_title_pdf5 , kCryoVertexVaribles_vector.at(3),PrintAllErrors );

Draw_Efficiency_CryoVertex_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], Efficiency_Playlist_TRUTH[0],
 Efficiency_Playlist[1] ,Efficiency_Playlist_TRUTH[1], "h_CryoVertex_RR","h_CryoVertex_RR",
0, "", mnv_plot, can2, text_title_pdf5 , kCryoVertexVaribles_vector.at(4),PrintAllErrors );


//////////////////
//// Resolution Plots
//////////////////


///////////////////////
/// CryoTank Resolution
///////////////////////

Draw_Resolution_CryoVertex_FULL_EMPTY_RecoBranch(Efficiency_Playlist[0], Efficiency_Playlist[1],
    "h_CryoVertex_resolutionX_TRUE_RECO", "h_CryoVertex_Percent_resolutionX_TRUE_RECO",0, "",mnv_plot, can2, Resolution_title_pdf5 , kCryoVertexVaribles_vector.at(0) );

Draw_Resolution_CryoVertex_FULL_EMPTY_RecoBranch(Efficiency_Playlist[0], Efficiency_Playlist[1],
  "h_CryoVertex_resolutionY_TRUE_RECO", "h_CryoVertex_Percent_resolutionY_TRUE_RECO",0, "",mnv_plot, can2, Resolution_title_pdf5 , kCryoVertexVaribles_vector.at(1) );

Draw_Resolution_CryoVertex_FULL_EMPTY_RecoBranch(Efficiency_Playlist[0], Efficiency_Playlist[1],
  "h_CryoVertex_resolutionZ_TRUE_RECO", "h_CryoVertex_Percent_resolutionZ_TRUE_RECO",0, "",mnv_plot, can2, Resolution_title_pdf5 , kCryoVertexVaribles_vector.at(2) );

Draw_Resolution_CryoVertex_FULL_EMPTY_RecoBranch(Efficiency_Playlist[0], Efficiency_Playlist[1],
  "h_CryoVertex_resolutionR_TRUE_RECO", "h_CryoVertex_Percent_resolutionR_TRUE_RECO",0, "",mnv_plot, can2, Resolution_title_pdf5 , kCryoVertexVaribles_vector.at(3) );

Draw_Resolution_CryoVertex_FULL_EMPTY_RecoBranch(Efficiency_Playlist[0], Efficiency_Playlist[1],
    "h_CryoVertex_resolutionRR_TRUE_RECO", "h_CryoVertex_Percent_resolutionRR_TRUE_RECO",0, "",mnv_plot, can2, Resolution_title_pdf5 , kCryoVertexVaribles_vector.at(4) );

Draw_Ratio_CryoVertex_FULL_EMPTY_RecoBranch(Efficiency_Playlist[0], Efficiency_Playlist[1],
  "h_CryoVertex_recoX_TRUE_RECO", "h_CryoVertex_X_TRUE_RECO",0, "",mnv_plot, can2, Resolution_title_pdf5 , kCryoVertexVaribles_vector[0] );

Draw_Ratio_CryoVertex_FULL_EMPTY_RecoBranch(Efficiency_Playlist[0], Efficiency_Playlist[1],
  "h_CryoVertex_recoY_TRUE_RECO", "h_CryoVertex_Y_TRUE_RECO",0, "",mnv_plot, can2, Resolution_title_pdf5 , kCryoVertexVaribles_vector[1] );

Draw_Ratio_CryoVertex_FULL_EMPTY_RecoBranch(Efficiency_Playlist[0], Efficiency_Playlist[1],
  "h_CryoVertex_recoZ_TRUE_RECO", "h_CryoVertex_Z_TRUE_RECO",0, "",mnv_plot, can2, Resolution_title_pdf5 , kCryoVertexVaribles_vector[2] );

Draw_Ratio_CryoVertex_FULL_EMPTY_RecoBranch(Efficiency_Playlist[0], Efficiency_Playlist[1],
  "h_CryoVertex_recoR_TRUE_RECO", "h_CryoVertex_R_TRUE_RECO",0, "",mnv_plot, can2, Resolution_title_pdf5 , kCryoVertexVaribles_vector[3] );

Draw_Ratio_CryoVertex_FULL_EMPTY_RecoBranch(Efficiency_Playlist[0], Efficiency_Playlist[1],
  "h_CryoVertex_recoRR_TRUE_RECO", "h_CryoVertex_RR_TRUE_RECO",0, "",mnv_plot, can2, Resolution_title_pdf5 , kCryoVertexVaribles_vector[4] );


//std::vector<double> CutToSurface_bins{-300,-290,-280,-270,-260,-250,-240,-230,-220,-210,-200,-190,-180,-170,-160,-150,-140,-130,-120,-110,-100,-90,-80,-70,-60,-50,-40,-30,-20,-10,0.0,20,30,40,50,60,70,80,90,100,110,120,130,140,150};
std::vector<double> CutToSurface_bins{ -390, -380, -370, -360, -350, -340, -330, -320, -310, -300, -290, -280, -270, -260, -250, -240, -230, -220, -210, -200, -190, -180, -170, -160, -150, -140, -130, -120, -110, -100, -90, -80, -70, -60, -50, -40, -30, -20, -10, 0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120};
bool include_overflows = false;

Draw_Resolution_2D_Helium_nonHelium_FULL_TRUTH(Efficiency_Playlist[0],Efficiency_Playlist[1],"h_resolutionZ_FidiucalCut",
"Fiducial Cut Distance to Cryotank Edge [mm]", "True - Reco Vertex Z [mm]", "Resolution Vertex Z [mm] Vs Fiducial Cut",
"", mnv_plot, can2, Resolution_title_pdf5, 1000.0, include_overflows);

Make_Resolution_vertex_Latex("h_resolutionZ_FidiucalCut_latex" ,  "PLOTS_Resolution", CutToSurface_bins,
  89, 138, 187,"TRUE Vertex Z");

Draw_Resolution_2D_Helium_nonHelium_FULL_TRUTH(Efficiency_Playlist[0], Efficiency_Playlist[1],"h_resolutionR_FidiucalCut",
"Fiducial Cut Distance to Cryotank Edge [mm]", "True - Reco Vertex R [mm]", "Resolution Vertex R [mm] Vs Fiducial Cut",
"", mnv_plot, can2, Resolution_title_pdf5, 2000.0, include_overflows);




Draw_2D_Xaxis_FiducialCut_FULL_EMPTY_TRUTH_Eff_Puritry(Efficiency_Playlist_TRUTH[0], Efficiency_Playlist_TRUTH[1],
                                                       Efficiency_Playlist[0],       Efficiency_Playlist[1],
                                                       "h_FidiucalCut_cryoVertex_R",
                                                       "Fiducial Cut Distance to Cryotank Edge [mm]", "TRUE Vertex R [mm]",
"TRUE Vertex R Vs Fiducial Cut" ,"" , mnv_plot, can2, Resolution_title_pdf5, 165.0, 500.0);

Make_Resolution_vertex_Latex("h_resolutionR_FidiucalCut_latex" ,  "PLOTS_Resolution", CutToSurface_bins,
  431, 525, 619,"TRUE Vertex R");

Make_Resolution_vertex_Latex("h_FidiucalCut_cryoVertex_R_Num_Dem_latex" ,  "PLOTS_Resolution", CutToSurface_bins,
    476, 570, 664,"TRUE Vertex R");


Draw_2D_Xaxis_FiducialCut_FULL_EMPTY(Efficiency_Playlist[0], Efficiency_Playlist[1],
  "h_FidiucalCut_cryoVertex_R_RECO","Fiducial Cut Distance to Cryotank Edge [mm]" , "RECO Vertex R [mm]",
"RECO Vertex R Vs Fiducial Cut"  , mnv_plot, can2, Resolution_title_pdf5, 110.0);

Make_Resolution_vertex_Latex("h_FidiucalCut_cryoVertex_R_RECO_latex" ,  "PLOTS_Resolution", CutToSurface_bins,
  740, 787, 834,"RECO Vertex R");



  Draw_2D_Xaxis_FiducialCut_FULL_EMPTY_TRUTH_Eff_Puritry(Efficiency_Playlist_TRUTH[0], Efficiency_Playlist_TRUTH[1],
                                                         Efficiency_Playlist[0], Efficiency_Playlist[1],
                                                              "h_FidiucalCut_cryoVertex_Z",
                                                              "Fiducial Cut Distance to Cryotank Edge [mm]", "TRUE Vertex Z [mm]",
  "TRUE Vertex Z Vs Fiducial Cut" ,"" , mnv_plot, can2, Resolution_title_pdf5, 35.0 ,160.0);

bool printErrors = true;
bool printALLErrors = false;


Make_Resolution_vertex_Latex("h_FidiucalCut_cryoVertex_Z_TRUE_latex" ,  "PLOTS_Resolution", CutToSurface_bins,
902, 996, 1090,"TRUE Vertex Z");

Make_Resolution_vertex_Latex("h_FidiucalCut_cryoVertex_Z_Num_Dem_latex" ,  "PLOTS_Resolution", CutToSurface_bins,
947, 1041, 1135,"TRUE Vertex Z");

Draw_2D_Xaxis_FiducialCut_FULL_EMPTY(Efficiency_Playlist[0], Efficiency_Playlist[1],
  "h_FidiucalCut_cryoVertex_Z_RECO","Fiducial Cut Distance to Cryotank Edge [mm]" , "RECO Vertex Z [mm]",
  "RECO Vertex Z Vs Fiducial Cut" , mnv_plot, can2, Resolution_title_pdf5, 35.0);

Make_Resolution_vertex_Latex("h_FidiucalCut_cryoVertex_Z_RECO_latex" ,  "PLOTS_Resolution", CutToSurface_bins,
1121, 1258, 1305,"RECO Vertex Z");
///////////
// Total 2D
///////////
bool doBinwidth = true;



Draw_Efficiency_FidiucialCut_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], Efficiency_Playlist_TRUTH[0],
                                                     Efficiency_Playlist[1], Efficiency_Playlist_TRUTH[1],
                                                     PlaylistDATA_1F, PlaylistDATA_1G,
                                                     "h_FidiucalCut", "h_Data_FidiucalCut",
                                                     "Fiducial Cut","Fiducial Cut Distance to Cryotank Edge [mm]", mnv_plot, false,
                                                     can2,  Fiduical_title_pdf5, printErrors, printALLErrors, CutToSurface_bins , .1 );

Draw_Resolution_CryoVertex_FULL_EMPTY_RecoBranch(Efficiency_Playlist[0], Efficiency_Playlist[1],
  "h_Distance_to_InnerTank_Resolution", "h_Distance_to_InnerTank_Resolution_Percent",0, "",mnv_plot, can2, Fiduical_title_pdf5 , kCryoVertexVaribles_vector.at(5) );


Draw_Efficiency_FidiucialCut_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], Efficiency_Playlist_TRUTH[0],
                                              Efficiency_Playlist[1], Efficiency_Playlist_TRUTH[1],
                                              PlaylistDATA_1F, PlaylistDATA_1G,
                                              "h_Distance_to_InnerTank", "h_Data_Distance_to_InnerTank",
                                              "Distance to Cryotank surface","Distance to Cryotank surface [mm]", mnv_plot, doBinwidth,
                                              can2,  Fiduical_title_pdf5, printErrors, printALLErrors, CutToSurface_bins ,  .3 );

DrawSTACKfromHistFilio_FromTFile(Efficiency_Playlist[0].TFILE_PLAYLIST, Efficiency_Playlist[1].TFILE_PLAYLIST, "h_Distance_to_InnerTank",
                                 PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_Distance_to_InnerTank",
                                 POT_MC_Status, POT_DATA_Status, false, "Material Stack: Distance to Cryotank Edge",
                                 "RECO Distance to Cryotank surface [mm]", Fiduical_title_pdf5, doBinwidth, false , "mm", kMaterial, my_debug );

DrawSTACKfromHistFilio_FromTFileNoData(Efficiency_Playlist[0].TFILE_PLAYLIST, Efficiency_Playlist[1].TFILE_PLAYLIST,  "h_Distance_to_InnerTank_TRUE" ,
                                   POT_MC_Status, POT_DATA_Status, "TRUE Distance to Cryotank Edge", "TRUE Distance to Cryotank surface [mm]", Fiduical_title_pdf5,
                                    doBinwidth, "mm", kMaterial, my_debug, false, 9999  );

DrawSTACKfromHistFilio_FromTFile(Efficiency_Playlist[0].TFILE_PLAYLIST, Efficiency_Playlist[1].TFILE_PLAYLIST, "h_Distance_to_InnerTank",
                                  PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_Distance_to_InnerTank",
                                  POT_MC_Status, POT_DATA_Status, false, "Distance to Cryotank Edge",
                                  "RECO Distance to Cryotank surface [mm]", Fiduical_title_pdf5, doBinwidth, false , "mm", kInteraction, my_debug );

DrawSTACKfromHistFilio_FromTFile(Efficiency_Playlist[0].TFILE_PLAYLIST, Efficiency_Playlist[1].TFILE_PLAYLIST, "h_Distance_to_InnerTank",
                                PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_Distance_to_InnerTank",
                                POT_MC_Status, POT_DATA_Status, false, "Distance to Cryotank Edge",
                                "RECO Distance to Cryotank surface [mm]", Fiduical_title_pdf5, doBinwidth, false , "mm", kParticle, my_debug );

DrawSTACKfromHistFilio_FromTFile(Efficiency_Playlist[0].TFILE_PLAYLIST, Efficiency_Playlist[1].TFILE_PLAYLIST, "h_Distance_to_InnerTank",
                                PlaylistDATA_1F.TFILE_PLAYLIST, PlaylistDATA_1G.TFILE_PLAYLIST, "h_Data_Distance_to_InnerTank",
                                POT_MC_Status, POT_DATA_Status, false, "Distance to Cryotank Edge",
                                "RECO Distance to Cryotank surface [mm]", Fiduical_title_pdf5, doBinwidth, false , "mm", kTrackType, my_debug );

Draw2DHist_Migration_TFILE(Efficiency_Playlist[0].TFILE_PLAYLIST, "h_Mig_Distance_to_InnerTank","Distance to Cryotank Edge [RECO Cuts no Fiduical][F(ME1F)]",  "RECO Distance to Cryotank Edge [mm]", "TRUE Distance to Cryotank Edge [mm]", Fiduical_title_pdf2, can2, mnv_plot, true);
Draw2DHist_Migration_TFILE(Efficiency_Playlist[0].TFILE_PLAYLIST, "h_Mig_Distance_to_InnerTank_TRUE","Distance to Cryotank Edge [TRUE+RECO Cuts no Fiduical] [F(ME1F)]",  "RECO Distance to Cryotank Edge [mm]", "TRUE Distance to Cryotank Edge [mm]", Fiduical_title_pdf2, can2, mnv_plot, true);



AppendtoLatex("h_resolutionR_Z_FidiucalCut_latex" , "PLOTS_Resolution", 62, 71, 80, "2D Nevents Z resolution ");
AppendtoLatex("h_resolutionR_Z_FidiucalCut_latex" , "PLOTS_Resolution", 65, 74, 83, "Nevents Z resolution[Helium]");
AppendtoLatex("h_resolutionR_Z_FidiucalCut_latex" , "PLOTS_Resolution", 68, 77, 86, "Nevents Z resolution[nonHelium]");
//////////////////////
AppendtoLatex("h_resolutionR_Z_FidiucalCut_latex" , "PLOTS_Resolution", 141, 197, 253, "Nevents Z resolution");
AppendtoLatex("h_resolutionR_Z_FidiucalCut_latex" , "PLOTS_Resolution", 142, 198, 254, "Nevents Z resolution");

AppendtoLatex("h_resolutionR_Z_FidiucalCut_latex" , "PLOTS_Resolution", 143, 199, 255, "$\\sigma$ GaussianFit Z resolution");
AppendtoLatex("h_resolutionR_Z_FidiucalCut_latex" , "PLOTS_Resolution", 144, 200, 256, "$\\mu$ GaussianFit Z resolution");

///////////////////////////////
AppendtoLatex("h_resolutionR_Z_FidiucalCut_latex" , "PLOTS_Resolution", 257, 266, 275, "2D Nevents Z resolution");
AppendtoLatex("h_resolutionR_Z_FidiucalCut_latex" , "PLOTS_Resolution", 260, 269, 278, "Nevents R resolution[Helium]");
AppendtoLatex("h_resolutionR_Z_FidiucalCut_latex" , "PLOTS_Resolution", 263, 272, 281, "Nevents R resolution[nonHelium]");

AppendtoLatex("h_resolutionR_Z_FidiucalCut_latex" , "PLOTS_Resolution", 336, 392, 448, "$\\sigma$ GaussianFit R resolution");
AppendtoLatex("h_resolutionR_Z_FidiucalCut_latex" , "PLOTS_Resolution", 337, 393, 449, "$\\mu$ GaussianFit R resolution");
AppendtoLatex("h_resolutionR_Z_FidiucalCut_latex" , "PLOTS_Resolution", 338, 394, 450, "$\\mu$ GaussianFit R resolution");
AppendtoLatex("h_resolutionR_Z_FidiucalCut_latex" , "PLOTS_Resolution", 339, 395, 451, "$\\mu$ GaussianFit R resolution");


int figure_1 = 89; // good
int figure_2 = 145; // check
int figure_3 = 201; // check
int figure_4 = 284; // check
int figure_5 = 340; // check
int figure_6 = 396; // check

char slideTitle[2024];
for(auto Bin : CutToSurface_bins ){
  sprintf(slideTitle, "Vertex R and Z Resolution distribution Fiducial Cut : %.2f", Bin);
  AppendtoLatex("h_resolutionR_Z_FidiucalCut_latex" ,  "PLOTS_Resolution", figure_1,  figure_2, figure_3, figure_4,  figure_5,  figure_6, slideTitle);
  figure_1++;
  figure_2++;
  figure_3++;
  figure_4++;
  figure_5++;
  figure_6++;
}



AppendtoLatex("h_FidiucalCut_cryoVertex_Z_R_latex" , "PLOTS_Resolution", 962, 973, 980, "Event Rate From R Vs Fiducial Cut ");
AppendtoLatex("h_FidiucalCut_cryoVertex_Z_R_latex" , "PLOTS_Resolution", 927, 974, 1021, "Purity From R Vs Fiducial Cut ");


//Vertex R
 figure_1 = 479; // check
 figure_2 = 640; //check
 figure_3 = 801;//check
 figure_4 = 989;// check
 figure_5 = 1043;// check
 figure_6 = 1097;// check


for(auto Bin : CutToSurface_bins ){
  sprintf(slideTitle, "Vertex R TRUE and RECO distribution for Fiducial Cut : %.2f", Bin);
  AppendtoLatex("h_FidiucalCut_cryoVertex_Z_R_latex" ,  "PLOTS_Resolution", figure_1,  figure_2, figure_3, figure_4,  figure_5,  figure_6, slideTitle);
  figure_1++;
  figure_2++;
  figure_3++;
  figure_4++;
  figure_5++;
  figure_6++;
}




AppendtoLatex("h_FidiucalCut_cryoVertex_Z_R_latex" , "PLOTS_Resolution", 1041, 1095, 1149, "Event Rate From RECO Z Vs Fiducial Cut ");
AppendtoLatex("h_FidiucalCut_cryoVertex_Z_R_latex" , "PLOTS_Resolution", 1042, 1096, 1150, "Purity From  RECO Z Vs Fiducial Cut ");




AppendtoLatex("h_FidiucalCut_cryoVertex_Z_R_latex" , "PLOTS_Resolution", 1282, 1443, 1604, "Event Rate From RECO Z Vs Fiducial Cut ");
AppendtoLatex("h_FidiucalCut_cryoVertex_Z_R_latex" , "PLOTS_Resolution", 1284, 1445, 1605, "Purity From  RECO Z Vs Fiducial Cut ");
AppendtoLatex("h_FidiucalCut_cryoVertex_Z_R_latex" , "PLOTS_Resolution", 1285, 1446, 1607, "Efficieny From  RECO Z Vs Fiducial Cut ");

/// Vertex Z
figure_1 = 1178; //check
figure_2 = 1338; //chck
figure_3 = 1500; //check
figure_4 = 1688; //check
figure_5 = 1742; //check
figure_6 = 1796; // Check

for(auto Bin : CutToSurface_bins ){
  sprintf(slideTitle, "Vertex Z TRUE and RECO distribution for Fiducial Cut : %.2f", Bin);
  AppendtoLatex("h_FidiucalCut_cryoVertex_Z_R_latex" ,  "PLOTS_Resolution", figure_1,  figure_2, figure_3, figure_4,  figure_5,  figure_6, slideTitle);
  figure_1++;
  figure_2++;
  figure_3++;
  figure_4++;
  figure_5++;
  figure_6++;
}




AppendtoLatex("Efficieny_projections_R_Z" , "PLOTS_Resolution", 452, 458, 464, "2D Numerator R vs Fiducial Cut");
AppendtoLatex("Efficieny_projections_R_Z" , "PLOTS_Resolution", 455, 461, 466, "2D Denominator R vs Fiducial Cut");
AppendtoLatex("Efficieny_projections_R_Z" , "PLOTS_Resolution", 470, 473, 476, "2D Efficiency R vs Fiducial Cut");


AppendtoLatex("Efficieny_projections_R_Z" , "PLOTS_Resolution", 583, 666, 805, "Projection Event R vs Fiducial Cut");
AppendtoLatex("Efficieny_projections_R_Z" , "PLOTS_Resolution", 584, 667, 806, "Projection Purity R vs Fiducial Cut");
AppendtoLatex("Efficieny_projections_R_Z" , "PLOTS_Resolution", 586, 668, 807, "Projection Efficiency R vs Fiducial Cut");
AppendtoLatex("Efficieny_projections_R_Z" , "PLOTS_Resolution", 530, 669, 808, "Projection Num + Dem R vs Fiducial Cut");



AppendtoLatex("Efficieny_projections_R_Z" , "PLOTS_Resolution", 1151, 1057, 1163, "2D Numerator Z vs Fiducial Cut");
AppendtoLatex("Efficieny_projections_R_Z" , "PLOTS_Resolution", 1154, 1061, 1166, "2D Denominator Z vs Fiducial Cut");
AppendtoLatex("Efficieny_projections_R_Z" , "PLOTS_Resolution", 1169, 1172, 1175, "2D Efficiency Z vs Fiducial Cut");
AppendtoLatex("Efficieny_projections_R_Z" , "PLOTS_Resolution", 1170, 1073, 1076, "2D Efficiency Z vs Fiducial Cut[ColNorm]");

AppendtoLatex("Efficieny_projections_R_Z" , "PLOTS_Resolution", 1139, 1278, 1417, "Projection Event Z vs Fiducial Cut");
AppendtoLatex("Efficieny_projections_R_Z" , "PLOTS_Resolution", 1140, 1279, 1418, "Projection Purity Z vs Fiducial Cut");
AppendtoLatex("Efficieny_projections_R_Z" , "PLOTS_Resolution", 1141, 1280, 1419, "Projection Efficiency Z vs Fiducial Cut");
AppendtoLatex("Efficieny_projections_R_Z" , "PLOTS_Resolution", 1142, 1281, 1420, "Projection Num + Dem Z vs Fiducial Cut");


/////////////

figure_1 = 588; //check
figure_2 = 749;//chck
figure_3 = 910;//chck
figure_4 = 1287;//chck
figure_5 = 1448;//chck
figure_6 = 1609;//chck

for(auto Bin : CutToSurface_bins ){
  sprintf(slideTitle, "Efficieny for Vertex R and Z for Fiducial Cut : %.2f", Bin);
  AppendtoLatex("Efficieny_projections_R_Z" ,  "PLOTS_Resolution", figure_1,  figure_2, figure_3, figure_4,  figure_5,  figure_6, slideTitle);
  figure_1++;
  figure_2++;
  figure_3++;
  figure_4++;
  figure_5++;
  figure_6++;
}





std::string pdf_label =std::string(Resolution_title_pdf5);
bool Dugbug_ON = true;
bool BinWithNorm_ON = false;
bool setMax = true;
double MaxMaterial = 325;
/*
DrawSTACKfromHistFilio_FromTFileNoData(Efficiency_Playlist[0].TFILE_PLAYLIST, Efficiency_Playlist[1].TFILE_PLAYLIST,"h_CryoVertex_resolutionR_RECO" ,
  POT_MC_Status, POT_DATA_Status, "Resolution Stack Vertex R [no Fiducial]", "TRUE - RECO Vertex R" ,pdf_label ,BinWithNorm_ON, "[mm]",kParticle , Dugbug_ON , setMax ,  MaxMaterial);

DrawSTACKfromHistFilio_FromTFileNoData(Efficiency_Playlist[0].TFILE_PLAYLIST, Efficiency_Playlist[1].TFILE_PLAYLIST,"h_CryoVertex_resolutionR_RECO" ,
  POT_MC_Status, POT_DATA_Status, "Resolution Stack Vertex R [no Fiducial]", "TRUE - RECO Vertex R" ,pdf_label ,BinWithNorm_ON, "[mm]",kInteraction , Dugbug_ON , setMax ,  MaxMaterial);

DrawSTACKfromHistFilio_FromTFileNoData(Efficiency_Playlist[0].TFILE_PLAYLIST, Efficiency_Playlist[1].TFILE_PLAYLIST,"h_CryoVertex_resolutionR_RECO" ,
    POT_MC_Status, POT_DATA_Status, "Resolution Stack Vertex R [no Fiducial]", "TRUE - RECO Vertex R" ,pdf_label ,BinWithNorm_ON, "[mm]",kMaterial , Dugbug_ON, setMax ,  MaxMaterial );


DrawSTACKfromHistFilio_FromTFileNoData(Efficiency_Playlist[0].TFILE_PLAYLIST, Efficiency_Playlist[1].TFILE_PLAYLIST,"h_CryoVertex_resolutionZ_RECO" ,
POT_MC_Status, POT_DATA_Status, "Resolution Stack Vertex Z[no Fiducial]", "TRUE - RECO Vertex Z" ,pdf_label ,BinWithNorm_ON, "[mm]",kParticle , Dugbug_ON, setMax ,  MaxMaterial );

DrawSTACKfromHistFilio_FromTFileNoData(Efficiency_Playlist[0].TFILE_PLAYLIST, Efficiency_Playlist[1].TFILE_PLAYLIST,"h_CryoVertex_resolutionZ_RECO" ,
POT_MC_Status, POT_DATA_Status, "Resolution Stack Vertex Z[no Fiducial]", "TRUE - RECO Vertex Z" ,pdf_label ,BinWithNorm_ON, "[mm]",kInteraction , Dugbug_ON, setMax ,  MaxMaterial );

DrawSTACKfromHistFilio_FromTFileNoData(Efficiency_Playlist[0].TFILE_PLAYLIST, Efficiency_Playlist[1].TFILE_PLAYLIST,"h_CryoVertex_resolutionZ_RECO" ,
POT_MC_Status, POT_DATA_Status, "Resolution Stack Vertex Z[no Fiducial]", "TRUE - RECO Vertex Z" ,pdf_label ,BinWithNorm_ON, "[mm]",kMaterial , Dugbug_ON , setMax ,  MaxMaterial  );
///////
DrawSTACKfromHistFilio_FromTFileNoData(Efficiency_Playlist[0].TFILE_PLAYLIST, Efficiency_Playlist[1].TFILE_PLAYLIST,"h_CryoVertex_resolutionR_fidiucal_Neg100_RECO" ,
  POT_MC_Status, POT_DATA_Status, "Resolution Stack Vertex R [Fiducial -100 mm]", "TRUE - RECO Vertex R" ,pdf_label ,BinWithNorm_ON, "[mm]",kParticle , Dugbug_ON, setMax ,  MaxMaterial );

DrawSTACKfromHistFilio_FromTFileNoData(Efficiency_Playlist[0].TFILE_PLAYLIST, Efficiency_Playlist[1].TFILE_PLAYLIST,"h_CryoVertex_resolutionR_fidiucal_Neg100_RECO" ,
  POT_MC_Status, POT_DATA_Status, "Resolution Stack Vertex R [Fiducial -100 mm]", "TRUE - RECO Vertex R" ,pdf_label ,BinWithNorm_ON, "[mm]",kInteraction , Dugbug_ON, setMax ,  MaxMaterial );

DrawSTACKfromHistFilio_FromTFileNoData(Efficiency_Playlist[0].TFILE_PLAYLIST, Efficiency_Playlist[1].TFILE_PLAYLIST,"h_CryoVertex_resolutionR_fidiucal_Neg100_RECO" ,
    POT_MC_Status, POT_DATA_Status, "Resolution Stack Vertex R [Fiducial -100 mm]", "TRUE - RECO Vertex R" ,pdf_label ,BinWithNorm_ON, "[mm]",kMaterial , Dugbug_ON , setMax ,  MaxMaterial  );


DrawSTACKfromHistFilio_FromTFileNoData(Efficiency_Playlist[0].TFILE_PLAYLIST, Efficiency_Playlist[1].TFILE_PLAYLIST,"h_CryoVertex_resolutionZ_fidiucal_Neg100_RECO" ,
POT_MC_Status, POT_DATA_Status, "Resolution Stack Vertex Z [Fiducial -100 mm]", "TRUE - RECO Vertex Z" ,pdf_label ,BinWithNorm_ON, "[mm]",kParticle , Dugbug_ON, setMax ,  MaxMaterial );

DrawSTACKfromHistFilio_FromTFileNoData(Efficiency_Playlist[0].TFILE_PLAYLIST, Efficiency_Playlist[1].TFILE_PLAYLIST,"h_CryoVertex_resolutionZ_fidiucal_Neg100_RECO" ,
POT_MC_Status, POT_DATA_Status, "Resolution Stack Vertex Z [Fiducial -100 mm]", "TRUE - RECO Vertex Z" ,pdf_label ,BinWithNorm_ON, "[mm]",kInteraction , Dugbug_ON, setMax ,  MaxMaterial );

DrawSTACKfromHistFilio_FromTFileNoData(Efficiency_Playlist[0].TFILE_PLAYLIST, Efficiency_Playlist[1].TFILE_PLAYLIST,"h_CryoVertex_resolutionZ_fidiucal_Neg100_RECO" ,
POT_MC_Status, POT_DATA_Status, "Resolution Stack Vertex Z [Fiducial -100 mm]", "TRUE - RECO Vertex Z" ,pdf_label ,BinWithNorm_ON, "[mm]",kMaterial , Dugbug_ON , setMax ,  MaxMaterial  );
//////////

DrawSTACKfromHistFilio_FromTFileNoData(Efficiency_Playlist[0].TFILE_PLAYLIST, Efficiency_Playlist[1].TFILE_PLAYLIST,"h_CryoVertex_resolutionR_fidiucal_Neg50_RECO" ,
  POT_MC_Status, POT_DATA_Status, "Resolution Stack Vertex R [Fiducial -50 mm]", "TRUE - RECO Vertex R" ,pdf_label ,BinWithNorm_ON, "[mm]",kParticle , Dugbug_ON, setMax ,  MaxMaterial );

DrawSTACKfromHistFilio_FromTFileNoData(Efficiency_Playlist[0].TFILE_PLAYLIST, Efficiency_Playlist[1].TFILE_PLAYLIST,"h_CryoVertex_resolutionR_fidiucal_Neg50_RECO" ,
  POT_MC_Status, POT_DATA_Status, "Resolution Stack Vertex R [Fiducial -50 mm]", "TRUE - RECO Vertex R" ,pdf_label ,BinWithNorm_ON, "[mm]",kInteraction , Dugbug_ON, setMax ,  MaxMaterial );

DrawSTACKfromHistFilio_FromTFileNoData(Efficiency_Playlist[0].TFILE_PLAYLIST, Efficiency_Playlist[1].TFILE_PLAYLIST,"h_CryoVertex_resolutionR_fidiucal_Neg50_RECO" ,
    POT_MC_Status, POT_DATA_Status, "Resolution Stack Vertex R [Fiducial -50 mm]", "TRUE - RECO Vertex R" ,pdf_label ,BinWithNorm_ON, "[mm]",kMaterial , Dugbug_ON , setMax ,  MaxMaterial  );


DrawSTACKfromHistFilio_FromTFileNoData(Efficiency_Playlist[0].TFILE_PLAYLIST, Efficiency_Playlist[1].TFILE_PLAYLIST,"h_CryoVertex_resolutionZ_fidiucal_Neg50_RECO" ,
POT_MC_Status, POT_DATA_Status, "Resolution Stack Vertex Z [Fiducial -50 mm]", "TRUE - RECO Vertex Z" ,pdf_label ,BinWithNorm_ON, "[mm]",kParticle , Dugbug_ON, setMax ,  MaxMaterial );

DrawSTACKfromHistFilio_FromTFileNoData(Efficiency_Playlist[0].TFILE_PLAYLIST, Efficiency_Playlist[1].TFILE_PLAYLIST,"h_CryoVertex_resolutionZ_fidiucal_Neg50_RECO" ,
POT_MC_Status, POT_DATA_Status, "Resolution Stack Vertex Z [Fiducial -50 mm]", "TRUE - RECO Vertex Z" ,pdf_label ,BinWithNorm_ON, "[mm]",kInteraction , Dugbug_ON, setMax ,  MaxMaterial );

DrawSTACKfromHistFilio_FromTFileNoData(Efficiency_Playlist[0].TFILE_PLAYLIST, Efficiency_Playlist[1].TFILE_PLAYLIST,"h_CryoVertex_resolutionZ_fidiucal_Neg50_RECO" ,
POT_MC_Status, POT_DATA_Status, "Resolution Stack Vertex Z [Fiducial -50 mm]", "TRUE - RECO Vertex Z" ,pdf_label ,BinWithNorm_ON, "[mm]",kMaterial , Dugbug_ON , setMax ,  MaxMaterial  );
/////


//////////
DrawSTACKfromHistFilio_FromTFileNoData(Efficiency_Playlist[0].TFILE_PLAYLIST, Efficiency_Playlist[1].TFILE_PLAYLIST,"h_CryoVertex_resolutionR_fidiucal_RECO" ,
  POT_MC_Status, POT_DATA_Status, "Resolution Stack Vertex R [Fiducial 20 mm]", "TRUE - RECO Vertex R" ,pdf_label ,BinWithNorm_ON, "[mm]",kParticle , Dugbug_ON , setMax ,  MaxMaterial);

DrawSTACKfromHistFilio_FromTFileNoData(Efficiency_Playlist[0].TFILE_PLAYLIST, Efficiency_Playlist[1].TFILE_PLAYLIST,"h_CryoVertex_resolutionR_fidiucal_RECO" ,
  POT_MC_Status, POT_DATA_Status, "Resolution Stack Vertex R [Fiducial 20 mm]", "TRUE - RECO Vertex R" ,pdf_label ,BinWithNorm_ON, "[mm]",kInteraction , Dugbug_ON , setMax ,  MaxMaterial);

DrawSTACKfromHistFilio_FromTFileNoData(Efficiency_Playlist[0].TFILE_PLAYLIST, Efficiency_Playlist[1].TFILE_PLAYLIST,"h_CryoVertex_resolutionR_fidiucal_RECO" ,
    POT_MC_Status, POT_DATA_Status, "Resolution Stack Vertex R [Fiducial 20 mm]", "TRUE - RECO Vertex R" ,pdf_label ,BinWithNorm_ON, "[mm]",kMaterial , Dugbug_ON , setMax ,  MaxMaterial  );


DrawSTACKfromHistFilio_FromTFileNoData(Efficiency_Playlist[0].TFILE_PLAYLIST, Efficiency_Playlist[1].TFILE_PLAYLIST,"h_CryoVertex_resolutionZ_fidiucal_RECO" ,
POT_MC_Status, POT_DATA_Status, "Resolution Stack Vertex Z [Fiducial 20 mm]", "TRUE - RECO Vertex Z" ,pdf_label ,BinWithNorm_ON, "[mm]",kParticle , Dugbug_ON , setMax ,  MaxMaterial);

DrawSTACKfromHistFilio_FromTFileNoData(Efficiency_Playlist[0].TFILE_PLAYLIST, Efficiency_Playlist[1].TFILE_PLAYLIST,"h_CryoVertex_resolutionZ_fidiucal_RECO" ,
POT_MC_Status, POT_DATA_Status, "Resolution Stack Vertex Z [Fiducial 20 mm]", "TRUE - RECO Vertex Z" ,pdf_label ,BinWithNorm_ON, "[mm]",kInteraction , Dugbug_ON , setMax ,  MaxMaterial);

DrawSTACKfromHistFilio_FromTFileNoData(Efficiency_Playlist[0].TFILE_PLAYLIST, Efficiency_Playlist[1].TFILE_PLAYLIST,"h_CryoVertex_resolutionZ_fidiucal_RECO" ,
POT_MC_Status, POT_DATA_Status, "Resolution Stack Vertex Z [Fiducial 20 mm]", "TRUE - RECO Vertex Z" ,pdf_label ,BinWithNorm_ON, "[mm]",kMaterial , Dugbug_ON , setMax ,  MaxMaterial  );
//////


DrawSTACKfromHistFilio_FromTFileNoData(Efficiency_Playlist[0].TFILE_PLAYLIST, Efficiency_Playlist[1].TFILE_PLAYLIST,"h_CryoVertex_resolutionR_fidiucal_50_RECO" ,
  POT_MC_Status, POT_DATA_Status, "Resolution Stack Vertex R [Fiducial 50 mm]", "TRUE - RECO Vertex R" ,pdf_label ,BinWithNorm_ON, "[mm]",kParticle , Dugbug_ON , setMax ,  MaxMaterial);

DrawSTACKfromHistFilio_FromTFileNoData(Efficiency_Playlist[0].TFILE_PLAYLIST, Efficiency_Playlist[1].TFILE_PLAYLIST,"h_CryoVertex_resolutionR_fidiucal_50_RECO" ,
  POT_MC_Status, POT_DATA_Status, "Resolution Stack Vertex R [Fiducial 50 mm]", "TRUE - RECO Vertex R" ,pdf_label ,BinWithNorm_ON, "[mm]",kInteraction , Dugbug_ON, setMax ,  MaxMaterial );

DrawSTACKfromHistFilio_FromTFileNoData(Efficiency_Playlist[0].TFILE_PLAYLIST, Efficiency_Playlist[1].TFILE_PLAYLIST,"h_CryoVertex_resolutionR_fidiucal_50_RECO" ,
    POT_MC_Status, POT_DATA_Status, "Resolution Stack Vertex R [Fiducial 50 mm]", "TRUE - RECO Vertex R" ,pdf_label ,BinWithNorm_ON, "[mm]",kMaterial , Dugbug_ON , setMax ,  MaxMaterial  );


DrawSTACKfromHistFilio_FromTFileNoData(Efficiency_Playlist[0].TFILE_PLAYLIST, Efficiency_Playlist[1].TFILE_PLAYLIST,"h_CryoVertex_resolutionZ_fidiucal_50_RECO" ,
POT_MC_Status, POT_DATA_Status, "Resolution Stack Vertex Z [Fiducial 50 mm]", "TRUE - RECO Vertex Z" ,pdf_label ,BinWithNorm_ON, "[mm]",kParticle , Dugbug_ON , setMax ,  MaxMaterial);

DrawSTACKfromHistFilio_FromTFileNoData(Efficiency_Playlist[0].TFILE_PLAYLIST, Efficiency_Playlist[1].TFILE_PLAYLIST,"h_CryoVertex_resolutionZ_fidiucal_50_RECO" ,
POT_MC_Status, POT_DATA_Status, "Resolution Stack Vertex Z [Fiducial 50 mm]", "TRUE - RECO Vertex Z" ,pdf_label ,BinWithNorm_ON, "[mm]",kInteraction , Dugbug_ON, setMax ,  MaxMaterial );

DrawSTACKfromHistFilio_FromTFileNoData(Efficiency_Playlist[0].TFILE_PLAYLIST, Efficiency_Playlist[1].TFILE_PLAYLIST,"h_CryoVertex_resolutionZ_fidiucal_50_RECO" ,
POT_MC_Status, POT_DATA_Status, "Resolution Stack Vertex Z [Fiducial 50 mm]", "TRUE - RECO Vertex Z" ,pdf_label ,BinWithNorm_ON, "[mm]",kMaterial , Dugbug_ON  , setMax ,  MaxMaterial );
/////

DrawSTACKfromHistFilio_FromTFileNoData(Efficiency_Playlist[0].TFILE_PLAYLIST, Efficiency_Playlist[1].TFILE_PLAYLIST,"h_CryoVertex_resolutionR_fidiucal_100_RECO" ,
  POT_MC_Status, POT_DATA_Status, "Resolution Stack Vertex R [Fiducial 100 mm]", "TRUE - RECO Vertex R" ,pdf_label ,BinWithNorm_ON, "[mm]",kParticle , Dugbug_ON , setMax ,  MaxMaterial);

DrawSTACKfromHistFilio_FromTFileNoData(Efficiency_Playlist[0].TFILE_PLAYLIST, Efficiency_Playlist[1].TFILE_PLAYLIST,"h_CryoVertex_resolutionR_fidiucal_100_RECO" ,
  POT_MC_Status, POT_DATA_Status, "Resolution Stack Vertex R [Fiducial 100 mm]", "TRUE - RECO Vertex R" ,pdf_label ,BinWithNorm_ON, "[mm]",kInteraction , Dugbug_ON, setMax ,  MaxMaterial );

DrawSTACKfromHistFilio_FromTFileNoData(Efficiency_Playlist[0].TFILE_PLAYLIST, Efficiency_Playlist[1].TFILE_PLAYLIST,"h_CryoVertex_resolutionR_fidiucal_100_RECO" ,
    POT_MC_Status, POT_DATA_Status, "Resolution Stack Vertex R [Fiducial 100 mm]", "TRUE - RECO Vertex R" ,pdf_label ,BinWithNorm_ON, "[mm]",kMaterial , Dugbug_ON  , setMax ,  MaxMaterial );


DrawSTACKfromHistFilio_FromTFileNoData(Efficiency_Playlist[0].TFILE_PLAYLIST, Efficiency_Playlist[1].TFILE_PLAYLIST,"h_CryoVertex_resolutionZ_fidiucal_100_RECO" ,
POT_MC_Status, POT_DATA_Status, "Resolution Stack Vertex Z [Fiducial 100 mm]", "TRUE - RECO Vertex Z" ,pdf_label ,BinWithNorm_ON, "[mm]",kParticle , Dugbug_ON , setMax ,  MaxMaterial);

DrawSTACKfromHistFilio_FromTFileNoData(Efficiency_Playlist[0].TFILE_PLAYLIST, Efficiency_Playlist[1].TFILE_PLAYLIST,"h_CryoVertex_resolutionZ_fidiucal_100_RECO" ,
POT_MC_Status, POT_DATA_Status, "Resolution Stack Vertex Z [Fiducial 100 mm]", "TRUE - RECO Vertex Z" ,pdf_label ,BinWithNorm_ON, "[mm]",kInteraction , Dugbug_ON, setMax ,  MaxMaterial );

DrawSTACKfromHistFilio_FromTFileNoData(Efficiency_Playlist[0].TFILE_PLAYLIST, Efficiency_Playlist[1].TFILE_PLAYLIST,"h_CryoVertex_resolutionZ_fidiucal_100_RECO" ,
POT_MC_Status, POT_DATA_Status, "Resolution Stack Vertex Z [Fiducial 100 mm]", "TRUE - RECO Vertex Z" ,pdf_label ,BinWithNorm_ON, "[mm]",kMaterial , Dugbug_ON , setMax ,  MaxMaterial  );
*/

//////
  Draw2DHist_TFILE(Efficiency_Playlist[0].TFILE_PLAYLIST, "h_resolutionZ_FidiucalCut", "Resolution Vertex Z [mm] Vs Fiducial Cut [Full ME1F]", "Fiducial Cut Distance to Cryotank Edge [mm]","True - Reco Vertex Z [mm]", text_title_pdf2, can2, mnv_plot);
  Draw2DHist_TFILE(Efficiency_Playlist[0].TFILE_PLAYLIST, "h_resolutionR_FidiucalCut", "Resolution Vertex R [mm] Vs Fiducial Cut [Full ME1F]", "Fiducial Cut Distance to Cryotank Edge [mm]","True - Reco Vertex R [mm]", text_title_pdf2, can2, mnv_plot);


Draw_Efficiency_2D_FULL_EMPTY_TRUTH(Efficiency_Playlist[0],Efficiency_Playlist_TRUTH[0], Efficiency_Playlist[1],Efficiency_Playlist_TRUTH[1],
  "h_cryoVertex_Z_secTrkTheta", "Vertex Z [mm]", "#theta_{2ndtrk} [Deg](wrtb)", "Vertex Z vs #theta_{2ndtrk}" ,"Efficiency" , mnv_plot, can2, Eff2D_pdf2);
AppendtoLatex("Efficiency2D_latex" , "PLOTS_2D_Efficiency", 14, 15, 16, "Efficiency Vertex Z vs $\\theta_{2ndtrk}$");


Draw_Efficiency_2D_FULL_EMPTY_TRUTH(Efficiency_Playlist[0],Efficiency_Playlist_TRUTH[0], Efficiency_Playlist[1],Efficiency_Playlist_TRUTH[1],
  "h_cryoVertex_R_secTrkTheta", "Vertex R [mm]", "#theta_{2ndtrk} [Deg](wrtb)", "Vertex R vs #theta_{2ndtrk}" ,"Efficiency" , mnv_plot, can2, Eff2D_pdf2);
AppendtoLatex("Efficiency2D_latex" , "PLOTS_2D_Efficiency", 29, 30, 31, "Efficiency Vertex R vs $\\theta_{2ndtrk}$");

Draw_Efficiency_2D_FULL_EMPTY_TRUTH(Efficiency_Playlist[0],Efficiency_Playlist_TRUTH[0], Efficiency_Playlist[1],Efficiency_Playlist_TRUTH[1],
  "h_muonPT_2ndTrkangle", "Muon P_{T} [GeV]", "#theta_{2ndtrk} [Deg](wrtb)", "Muon P_{T} vs #theta_{2ndtrk}" ,"Efficiency" , mnv_plot, can2, Eff2D_pdf2);
AppendtoLatex("Efficiency2D_latex" , "PLOTS_2D_Efficiency", 44, 45, 46, "Efficiency Muon $P_{T}$ vs $\\theta_{2ndtrk}$");

Draw_Efficiency_2D_FULL_EMPTY_TRUTH(Efficiency_Playlist[0],Efficiency_Playlist_TRUTH[0], Efficiency_Playlist[1],Efficiency_Playlist_TRUTH[1],
  "h_muonPZ_2ndTrkangle", "Muon P_{Z} [GeV]", "#theta_{2ndtrk} [Deg](wrtb)", "Muon P_{Z} vs #theta_{2ndtrk}" ,"Efficiency" , mnv_plot, can2, Eff2D_pdf2);
AppendtoLatex("Efficiency2D_latex" , "PLOTS_2D_Efficiency", 59, 60, 61, "Efficiency Muon $P_{Z}$ vs $\\theta_{2ndtrk}$");

Draw_Efficiency_2D_FULL_EMPTY_TRUTH(Efficiency_Playlist[0],Efficiency_Playlist_TRUTH[0], Efficiency_Playlist[1],Efficiency_Playlist_TRUTH[1],
  "h_muontheta_2ndTrkangle", "#theta_{#mu} [Deg]", "#theta_{2ndtrk} [Deg](wrtb)", "#theta_{#mu} vs #theta_{2ndtrk}" ,"Efficiency" , mnv_plot, can2, Eff2D_pdf2);
AppendtoLatex("Efficiency2D_latex" , "PLOTS_2D_Efficiency", 74, 75, 76, "Efficiency $\\theta_{\\mu}$ vs $\\theta_{2ndtrk}$");

Draw_Efficiency_2D_FULL_EMPTY_TRUTH(Efficiency_Playlist[0],Efficiency_Playlist_TRUTH[0], Efficiency_Playlist[1],Efficiency_Playlist_TRUTH[1],
  "h_2ndTrkE_2ndtrkangle", "KE_{2ndTrk} [GeV]", "#theta_{2ndtrk} [Deg](wrtb)", "KE_{2ndTrk} vs #theta_{2ndtrk}" ,"Efficiency" , mnv_plot, can2, Eff2D_pdf2);
AppendtoLatex("Efficiency2D_latex" , "PLOTS_2D_Efficiency", 89, 90, 91, "Efficiency $KE_{2ndTrk}$ vs $\\theta_{2ndtrk}$");

Draw_Efficiency_2D_FULL_EMPTY_TRUTH(Efficiency_Playlist[0],Efficiency_Playlist_TRUTH[0], Efficiency_Playlist[1],Efficiency_Playlist_TRUTH[1],
  "h_2ndTrkE_2ndtrkangle_Proton", "KE_{2ndTrk} [GeV]", "#theta_{2ndtrk} [Deg](wrtb)", "KE_{2ndTrk} vs #theta_{2ndtrk} [Proton]" ,"Efficiency" , mnv_plot, can2, Eff2D_pdf2);
AppendtoLatex("Efficiency2D_latex" , "PLOTS_2D_Efficiency", 104, 105, 106, "Efficiency $KE_{2ndTrk}$ vs $\\theta_{2ndtrk}$[Proton]");

Draw_Efficiency_2D_FULL_EMPTY_TRUTH(Efficiency_Playlist[0],Efficiency_Playlist_TRUTH[0], Efficiency_Playlist[1],Efficiency_Playlist_TRUTH[1],
  "h_2ndTrkE_2ndtrkangle_Pion", "KE_{2ndTrk} [GeV]", "#theta_{2ndtrk} [Deg](wrtb)", "KE_{2ndTrk} vs #theta_{2ndtrk} [Pion]" ,"Efficiency" , mnv_plot, can2, Eff2D_pdf2);
AppendtoLatex("Efficiency2D_latex" , "PLOTS_2D_Efficiency", 119, 120, 121, "Efficiency $KE_{2ndTrk}$ vs $\\theta_{2ndtrk}$[Pion]");

Draw_Efficiency_2D_FULL_EMPTY_TRUTH(Efficiency_Playlist[0],Efficiency_Playlist_TRUTH[0], Efficiency_Playlist[1],Efficiency_Playlist_TRUTH[1],
    "h_cryoVertex_Z_Pathlength", "Vertex Z [mm]", "Pathway [g/cm^{2}]", "Vertex Z vs Pathway" ,"Efficiency" , mnv_plot, can2, Eff2D_pdf2);
AppendtoLatex("Efficiency2D_latex" , "PLOTS_2D_Efficiency", 134, 135, 136, "Efficiency Vertex Z vs Pathway");

Draw_Efficiency_2D_FULL_EMPTY_TRUTH(Efficiency_Playlist[0],Efficiency_Playlist_TRUTH[0], Efficiency_Playlist[1],Efficiency_Playlist_TRUTH[1],
    "h_cryoVertex_R_Pathlength", "Vertex R [mm]", "Pathway [g/cm^{2}]", "Vertex R vs Pathway" ,"Efficiency" , mnv_plot, can2, Eff2D_pdf2);
AppendtoLatex("Efficiency2D_latex" , "PLOTS_2D_Efficiency", 149, 150, 151, "Efficiency Vertex R vs Pathway");

Draw_Efficiency_2D_FULL_EMPTY_TRUTH(Efficiency_Playlist[0],Efficiency_Playlist_TRUTH[0], Efficiency_Playlist[1],Efficiency_Playlist_TRUTH[1],
  "h_cryoVertex_Z_DOCA", "Vertex R [mm]", "DOCA [mm]", "Vertex Z vs DOCA" ,"Efficiency" , mnv_plot, can2, Eff2D_pdf2);
AppendtoLatex("Efficiency2D_latex" , "PLOTS_2D_Efficiency", 164, 165, 166, " Efficiency Vertex Z vs DOCA");

Draw_Efficiency_2D_FULL_EMPTY_TRUTH(Efficiency_Playlist[0],Efficiency_Playlist_TRUTH[0], Efficiency_Playlist[1],Efficiency_Playlist_TRUTH[1],
    "h_cryoVertex_R_DOCA", "Vertex R [mm]", "DOCA [mm]", "Vertex R vs DOCA" ,"Efficiency" , mnv_plot, can2, Eff2D_pdf2);
AppendtoLatex("Efficiency2D_latex" , "PLOTS_2D_Efficiency", 179, 180, 181, " Efficiency Vertex R vs DOCA");


  //Draw_Efficiency_2ndTrk_FULL_EMPTY(Efficiency_Playlist[0],Efficiency_Playlist[1] , "h_secTrk_Pathlength",
  //0, " ", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[3] );

  //Draw_Efficiency_2ndTrk_FULL_EMPTY(Efficiency_Playlist[0],Efficiency_Playlist[1] , "h_secTrk_DOCA",
  //0, " ", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[4] );

Draw2DHist_Migration_TFILE(PlaylistMC_1F_piePlots.TFILE_PLAYLIST, "h_Mig_MuonE", "Migration", "RECO E_{#mu}", "TRUE E_{#mu}", Migration_title_pdf2, can2, mnv_plot, true);

Draw2DHist_Migration_TFILE(PlaylistMC_1F_piePlots.TFILE_PLAYLIST, "h_Mig_MuonPZ","Migration Muon P_{Z}", "RECO Muon P_{Z}", "TRUE Muon P_{Z}", Migration_title_pdf2, can2, mnv_plot, true);

Draw2DHist_Migration_TFILE(PlaylistMC_1F_piePlots.TFILE_PLAYLIST, "h_Mig_MuonPT", "Migration Muon P_{T}", "RECO Muon P_{T}", "TRUE Muon P_{T}", Migration_title_pdf2, can2, mnv_plot, true);

Draw2DHist_Migration_TFILE(PlaylistMC_1F_piePlots.TFILE_PLAYLIST, "h_Mig_MuonTheta","Migration Muon #theta_{#mu}", "RECO Muon #theta_{#mu}", "TRUE Muon #theta_{#mu}",  Migration_title_pdf2, can2, mnv_plot, true);

Draw2DHist_Migration_TFILE(PlaylistMC_1F_piePlots.TFILE_PLAYLIST, "h_Mig_Vertex_X","Migration Vertex X", "RECO Vertex X", "TRUE Vertex X",  Migration_title_pdf2, can2, mnv_plot, true);

Draw2DHist_Migration_TFILE(PlaylistMC_1F_piePlots.TFILE_PLAYLIST, "h_Mig_Vertex_Y","Migration Vertex Y", "RECO Vertex Y", "TRUE Vertex Y",  Migration_title_pdf2, can2, mnv_plot, true);

Draw2DHist_Migration_TFILE(PlaylistMC_1F_piePlots.TFILE_PLAYLIST, "h_Mig_Vertex_R","Migration Vertex R", "RECO Vertex R", "TRUE Vertex R",  Migration_title_pdf2, can2, mnv_plot, true);

Draw2DHist_Migration_TFILE(PlaylistMC_1F_piePlots.TFILE_PLAYLIST, "h_Mig_Vertex_Z","Migration Vertex Z",  "RECO Vertex Z", "TRUE Vertex Z", Migration_title_pdf2, can2, mnv_plot, true);



DrawPie_Figures_EventCutRate(PlaylistTRUTH_1F_piePlots.TFILE_PLAYLIST,  "Truth_Cuts",
PlaylistMC_1F_piePlots.TFILE_PLAYLIST, "Truth_Cuts" , "TRUE_RECO_Cuts", PlaylistMC_1F_piePlots.m_playlist,
PlaylistMC_1F_piePlots.m_Helium_status,  text_title_pdf5, can2, mnv_plot, "Event Cuts");


Hist_phyiscs_map MAP_stack_TRUTH_F_MFP_pi =  Make_Physics_distribution_map_FromTFile(PlaylistTRUTH_1F_piePlots.TFILE_PLAYLIST, "h_MuonE_MFP_pi_TRUE" , false, 1.0, kPlayListVector_MC.at(0), false );
DrawPieFigures(MAP_stack_TRUTH_F_MFP_pi ,  text_title_pdf5, can2, mnv_plot, true, false, "MuonE");

///////////////
// Migration
//////////////
/*
Draw_Migration_2D_FULL_EMPTY_TRUTH(PlaylistMC_1F_piePlots,  PlaylistMC_1G_piePlots,
   "h_Mig_MuonE", "RECO E_{#mu}", "TRUE E_{#mu}", "Migration Muon Energy",
   "" , mnv_plot, can2, text_title_pdf2);


Draw_Migration_2D_FULL_EMPTY_TRUTH(PlaylistMC_1F_piePlots,  PlaylistMC_1G_piePlots,
      "h_Mig_MuonPZ", "RECO Muon P_{Z}", "TRUE Muon P_{Z}", "Migration Muon P_{Z}",
      "" , mnv_plot, can2, text_title_pdf2);

Draw_Migration_2D_FULL_EMPTY_TRUTH(PlaylistMC_1F_piePlots,  PlaylistMC_1G_piePlots,
  "h_Mig_MuonPT", "RECO Muon P_{T}", "TRUE Muon P_{T}", "Migration Muon P_{T}",
  "" , mnv_plot, can2, text_title_pdf2);


Draw_Migration_2D_FULL_EMPTY_TRUTH(PlaylistMC_1F_piePlots,  PlaylistMC_1G_piePlots,
  "h_Mig_MuonTheta", "RECO Muon #theta_{#mu}", "TRUE Muon #theta_{#mu}", "Migration Muon #theta_{#mu}",
  "" , mnv_plot, can2, text_title_pdf2);


Draw_Migration_2D_FULL_EMPTY_TRUTH(PlaylistMC_1F_piePlots,  PlaylistMC_1G_piePlots,
    "h_Mig_Vertex_X", "RECO Vertex X", "TRUE Vertex X", "Migration Vertex X",
    "" , mnv_plot, can2, text_title_pdf2);

Draw_Migration_2D_FULL_EMPTY_TRUTH(PlaylistMC_1F_piePlots,  PlaylistMC_1G_piePlots,
  "h_Mig_Vertex_Y", "RECO Vertex Y", "TRUE Vertex Y", "Migration Vertex Y",
  "" , mnv_plot, can2, text_title_pdf2);

Draw_Migration_2D_FULL_EMPTY_TRUTH(PlaylistMC_1F_piePlots,  PlaylistMC_1G_piePlots,
  "h_Mig_Vertex_R", "RECO Vertex R", "TRUE Vertex R ", "Migration Vertex R",
  "" , mnv_plot, can2, text_title_pdf2);

Draw_Migration_2D_FULL_EMPTY_TRUTH(PlaylistMC_1F_piePlots,  PlaylistMC_1G_piePlots,
    "h_Mig_Vertex_Z", "RECO Vertex Z", "TRUE Vertex Z ", "Migration Vertex Z",
    "" , mnv_plot, can2, text_title_pdf2);
*/
std::cout << std::endl;
std::cout << "Done WITH EfficiencyPlots" << std::endl;
can2 -> Print(text_title_pdf3);
can2 -> Print(Resolution_title_pdf3);
can2 -> Print(Fiduical_title_pdf3);
can2 -> Print(Eff2D_pdf3);
can2 -> Print(Migration_title_pdf3);

can2->Close();
}// end of Function

///////////////////////////////////////////////////////////////////////////////
///// FUNCTIONS//////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


void Draw_Efficiency_2ndTrk_FULL_EMPTY(PlayList_INFO FULL_playlist,PlayList_INFO EMPTY_playlist , const char *histoName,
          int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf , SecondTrkVar playlist_name ){

      char histoName_TRUE[1024];
      char histoName_TRUE_RECO[1024];
      char Title_His[1024];

      double FULL_POT = FULL_playlist.Get_Pot();
      double EMPTY_POT = EMPTY_playlist.Get_Pot();
      double Scale_MC = FULL_POT / EMPTY_POT;

      sprintf(histoName_TRUE, "%s_TRUE", histoName);
      sprintf(histoName_TRUE_RECO, "%s_TRUE_RECO", histoName);

      MnvH1D *hist_TRUE_FULL = (MnvH1D*)FULL_playlist.TFILE_PLAYLIST -> Get(histoName_TRUE);
      MnvH1D *hist_TRUE_RECO_FULL = (MnvH1D*)FULL_playlist.TFILE_PLAYLIST -> Get(histoName_TRUE_RECO);
      MnvH1D *hist_TRUE_EMPTY = (MnvH1D*)EMPTY_playlist.TFILE_PLAYLIST -> Get(histoName_TRUE);
      MnvH1D *hist_TRUE_RECO_EMPTY = (MnvH1D*)EMPTY_playlist.TFILE_PLAYLIST -> Get(histoName_TRUE_RECO);

      MnvH1D* hist_TRUE_FULL_clone = (MnvH1D*)FULL_playlist.TFILE_PLAYLIST -> Get(histoName_TRUE);
      MnvH1D* hist_TRUE_RECO_FULL_clone = (MnvH1D*)FULL_playlist.TFILE_PLAYLIST -> Get(histoName_TRUE_RECO);
      MnvH1D* hist_TRUE_EMPTY_clone = (MnvH1D*)EMPTY_playlist.TFILE_PLAYLIST -> Get(histoName_TRUE);
      MnvH1D* hist_TRUE_RECO_EMPTY_clone = (MnvH1D*)EMPTY_playlist.TFILE_PLAYLIST -> Get(histoName_TRUE_RECO);

      ///Calculation FOR FINAL Eff
      hist_TRUE_EMPTY_clone->Scale(Scale_MC);
      hist_TRUE_RECO_EMPTY_clone->Scale(Scale_MC);
      hist_TRUE_FULL_clone->Add(hist_TRUE_EMPTY_clone,-1);
      hist_TRUE_RECO_FULL_clone->Add(hist_TRUE_RECO_EMPTY_clone,-1);
      hist_TRUE_RECO_FULL_clone->Divide(hist_TRUE_RECO_FULL_clone, hist_TRUE_FULL_clone, 1.0,1.0,"");



      std::string title_type = GetsecondTrkTitleName(playlist_name);
      std::string Xaxis_title = GetsecondTrk_AXIS_TitleName(playlist_name);
      auto FULL_name = FULL_playlist.GetPlaylist();
      auto Empty_name = EMPTY_playlist.GetPlaylist();
      std::string playlistFull =   GetPlaylist_InitialName(FULL_name); //FULL_playlist.GetPlaylistName();
      std::string playlistEmpty = GetPlaylist_InitialName(Empty_name); //EMPTY_playlist.GetPlaylistName();


      char title_type_char[title_type.length()+1];
      strcpy( title_type_char, title_type.c_str());

      char playlistFull_char[playlistFull.length()+1];
      strcpy( playlistFull_char, playlistFull.c_str());

      char playlistEmpty_char[ playlistEmpty.length()+1];
      strcpy( playlistEmpty_char,  playlistEmpty.c_str());

      sprintf(Title_His, "%s (%s) (True) (%s)(F) ", title_type_char,title,playlistFull_char);
      DrawCVAndError_FromTFile(FULL_playlist.TFILE_PLAYLIST, histoName_TRUE, Title_His  , Xaxis_title, pdf );
      sprintf(Title_His, "%s (%s) (True+RECO) (%s)(F)", title_type_char,title,playlistFull_char);
      DrawCVAndError_FromTFile(FULL_playlist.TFILE_PLAYLIST, histoName_TRUE_RECO, Title_His , Xaxis_title, pdf );
      sprintf(Title_His, "%s (%s) (True) (%s)(E)", title_type_char,title,playlistEmpty_char);
      DrawCVAndError_FromTFile(EMPTY_playlist.TFILE_PLAYLIST, histoName_TRUE,Title_His, Xaxis_title, pdf );
      sprintf(Title_His, "%s (%s) (True+RECO) (%s)(E)", title_type_char,title,playlistEmpty_char);
      DrawCVAndError_FromTFile(EMPTY_playlist.TFILE_PLAYLIST, histoName_TRUE_RECO,  Title_His , Xaxis_title, pdf );


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

void Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(PlayList_INFO FULL_playlist_nom,PlayList_INFO FULL_playlist_TRUTHDEM,
  PlayList_INFO EMPTY_playlist_nom, PlayList_INFO EMPTY_playlist_TRUTHDEM , const char *histoName,
  int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf , SecondTrkVar playlist_name, double Vline_OnXaxis, bool print_all_errors ){

      char histoName_TRUE[1024];
      char histoName_TRUE_RECO[1024];
      char Title_His[1024];

      double FULL_POT_Dem = FULL_playlist_TRUTHDEM.Get_Pot();
      double FULL_POT_nom = FULL_playlist_nom.Get_Pot();
      if(FULL_POT_Dem!=FULL_POT_nom){std::cout<<"POT it different for Dem and Nom for Full playlist"<<std::endl;}

      double EMPTY_POT_nom = EMPTY_playlist_nom.Get_Pot();
      double EMPTY_POT_Dem = EMPTY_playlist_TRUTHDEM.Get_Pot();

      if(EMPTY_POT_Dem!=EMPTY_POT_nom){std::cout<<"POT it different for Dem and Nom for EMPTY playlist"<<std::endl;}


      double Scale_MC = FULL_POT_nom / EMPTY_POT_nom;

      sprintf(histoName_TRUE, "%s_TRUE", histoName);
      sprintf(histoName_TRUE_RECO, "%s_TRUE_RECO", histoName);

      std::cout<<"Making plot with Hist(TRUE) name: "<< histoName_TRUE<<std::endl;
      std::cout<<"Making plot with Hist(TRUE+RECO) name: "<< histoName_TRUE_RECO<<std::endl;
      bool isfull = true;
      bool isempty=false;
      std::cout<<"hist_TRUE_FULL"<<std::endl;
      MnvH1D *hist_TRUE_FULL = Get1DHist(*FULL_playlist_TRUTHDEM.TFILE_PLAYLIST, histoName_TRUE, isfull);
      std::cout<<"hist_TRUE_RECO_FULL"<<std::endl;
      MnvH1D *hist_TRUE_RECO_FULL = Get1DHist(*FULL_playlist_nom.TFILE_PLAYLIST, histoName_TRUE_RECO, isfull);
      std::cout<<"hist_TRUE_EMPTY"<<std::endl;
      MnvH1D *hist_TRUE_EMPTY = Get1DHist(*EMPTY_playlist_TRUTHDEM.TFILE_PLAYLIST, histoName_TRUE, isempty);
      std::cout<<"hist_TRUE_RECO_EMPTY"<<std::endl;
      MnvH1D *hist_TRUE_RECO_EMPTY = Get1DHist(*EMPTY_playlist_nom.TFILE_PLAYLIST, histoName_TRUE_RECO, isempty);

      MnvH1D* hist_TRUE_FULL_clone = Get1DHist(*FULL_playlist_TRUTHDEM.TFILE_PLAYLIST, histoName_TRUE, isfull);
      MnvH1D* hist_TRUE_RECO_FULL_clone = Get1DHist(*FULL_playlist_nom.TFILE_PLAYLIST, histoName_TRUE_RECO, isfull);
      MnvH1D* hist_TRUE_EMPTY_clone = Get1DHist(*EMPTY_playlist_TRUTHDEM.TFILE_PLAYLIST, histoName_TRUE, isempty);
      MnvH1D* hist_TRUE_RECO_EMPTY_clone = Get1DHist(*EMPTY_playlist_nom.TFILE_PLAYLIST, histoName_TRUE_RECO, isempty);


      hist_TRUE_FULL->AddMissingErrorBandsAndFillWithCV(*hist_TRUE_RECO_FULL);
      hist_TRUE_EMPTY->AddMissingErrorBandsAndFillWithCV(*hist_TRUE_RECO_FULL);
      hist_TRUE_FULL_clone->AddMissingErrorBandsAndFillWithCV(*hist_TRUE_RECO_FULL);
      hist_TRUE_EMPTY_clone->AddMissingErrorBandsAndFillWithCV(*hist_TRUE_RECO_FULL);


      ///Calculation FOR FINAL Eff
      hist_TRUE_EMPTY_clone->Scale(Scale_MC);
      hist_TRUE_RECO_EMPTY_clone->Scale(Scale_MC);
      hist_TRUE_FULL_clone->Add(hist_TRUE_EMPTY_clone,-1);
      hist_TRUE_RECO_FULL_clone->Add(hist_TRUE_RECO_EMPTY_clone,-1);
      hist_TRUE_RECO_FULL_clone->Divide(hist_TRUE_RECO_FULL_clone, hist_TRUE_FULL_clone, 1.0,1.0,"");



      std::string title_type = GetsecondTrkTitleName(playlist_name);
      std::string Xaxis_title = GetsecondTrk_AXIS_TitleName(playlist_name);
      auto FULL_name = FULL_playlist_nom.GetPlaylist();
      auto Empty_name = EMPTY_playlist_nom.GetPlaylist();
      std::string playlistFull =   GetPlaylist_InitialName(FULL_name); //FULL_playlist.GetPlaylistName();
      std::string playlistEmpty = GetPlaylist_InitialName(Empty_name); //EMPTY_playlist.GetPlaylistName();


      char title_type_char[title_type.length()+1];
      strcpy( title_type_char, title_type.c_str());

      char playlistFull_char[playlistFull.length()+1];
      strcpy( playlistFull_char, playlistFull.c_str());

      char playlistEmpty_char[ playlistEmpty.length()+1];
      strcpy( playlistEmpty_char,  playlistEmpty.c_str());

      sprintf(Title_His, "%s (%s) (True) (%s)(F) ", title_type_char,title,playlistFull_char);
      DrawCVAndError_FromTFile(print_all_errors, FULL_playlist_TRUTHDEM.TFILE_PLAYLIST, histoName_TRUE, Title_His  , Xaxis_title, pdf );
      sprintf(Title_His, "%s (%s) (True+RECO) (%s)(F)", title_type_char,title,playlistFull_char);
      DrawCVAndError_FromTFile(print_all_errors, FULL_playlist_nom.TFILE_PLAYLIST, histoName_TRUE_RECO, Title_His , Xaxis_title, pdf );
      sprintf(Title_His, "%s (%s) (True) (%s)(E)", title_type_char,title,playlistEmpty_char);
      DrawCVAndError_FromTFile(print_all_errors, EMPTY_playlist_TRUTHDEM.TFILE_PLAYLIST, histoName_TRUE,Title_His, Xaxis_title, pdf );
      sprintf(Title_His, "%s (%s) (True+RECO) (%s)(E)", title_type_char,title,playlistEmpty_char);
      DrawCVAndError_FromTFile(print_all_errors, EMPTY_playlist_nom.TFILE_PLAYLIST, histoName_TRUE_RECO,  Title_His , Xaxis_title, pdf );


      hist_TRUE_RECO_FULL->Divide(hist_TRUE_RECO_FULL, hist_TRUE_FULL, 1.0,1.0,"");
      hist_TRUE_RECO_EMPTY->Divide(hist_TRUE_RECO_EMPTY, hist_TRUE_EMPTY, 1.0,1.0,"");

      sprintf(Title_His, "Eff(FULL) %s (%s)  (%s)(F) ", title_type_char,title,playlistFull_char);
      DrawCVAndError_FromHIST(hist_TRUE_RECO_FULL, Title_His ,Xaxis_title,"Efficiency", pdf,true);
      sprintf(Title_His, "Eff(Empty) %s (%s)  (%s)(E) ", title_type_char,title,playlistEmpty_char);
      DrawCVAndError_FromHIST(hist_TRUE_RECO_EMPTY, Title_His ,Xaxis_title,"Efficiency", pdf,true);

      sprintf(Title_His, "%s (%s) (%s-%s)", title_type_char,title,playlistFull_char,playlistEmpty_char);
      DrawCVAndError_FromHIST_withVLine(hist_TRUE_RECO_FULL_clone, Title_His ,Xaxis_title,"Efficiency", pdf,true, false, false, Vline_OnXaxis);

      DrawCVAndError_FromHIST_withVLine(hist_TRUE_RECO_FULL_clone, Title_His ,Xaxis_title,"Efficiency", pdf,true, true, false , Vline_OnXaxis);


}//endl;
/////////////////////////////////////////////////////

void Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(PlayList_INFO FULL_playlist_nom,PlayList_INFO FULL_playlist_TRUTHDEM,
  PlayList_INFO EMPTY_playlist_nom, PlayList_INFO EMPTY_playlist_TRUTHDEM , const char *histoName,
  int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf , SecondTrkVar playlist_name ){

      char histoName_TRUE[1024];
      char histoName_TRUE_RECO[1024];
      char Title_His[1024];

      double FULL_POT_Dem = FULL_playlist_TRUTHDEM.Get_Pot();
      double FULL_POT_nom = FULL_playlist_nom.Get_Pot();
      if(FULL_POT_Dem!=FULL_POT_nom){std::cout<<"POT it different for Dem and Nom for Full playlist"<<std::endl;}

      double EMPTY_POT_nom = EMPTY_playlist_nom.Get_Pot();
      double EMPTY_POT_Dem = EMPTY_playlist_TRUTHDEM.Get_Pot();

      if(EMPTY_POT_Dem!=EMPTY_POT_nom){std::cout<<"POT it different for Dem and Nom for EMPTY playlist"<<std::endl;}


      double Scale_MC = FULL_POT_nom / EMPTY_POT_nom;

      sprintf(histoName_TRUE, "%s_TRUE", histoName);
      sprintf(histoName_TRUE_RECO, "%s_TRUE_RECO", histoName);

      std::cout<<"Making plot with Hist(TRUE) name: "<< histoName_TRUE<<std::endl;
      std::cout<<"Making plot with Hist(TRUE+RECO) name: "<< histoName_TRUE_RECO<<std::endl;

      std::cout<<"hist_TRUE_FULL"<<std::endl;
      MnvH1D *hist_TRUE_FULL = (MnvH1D*)FULL_playlist_TRUTHDEM.TFILE_PLAYLIST -> Get(histoName_TRUE);
      std::cout<<"hist_TRUE_RECO_FULL"<<std::endl;
      MnvH1D *hist_TRUE_RECO_FULL = (MnvH1D*)FULL_playlist_nom.TFILE_PLAYLIST -> Get(histoName_TRUE_RECO);
      std::cout<<"hist_TRUE_EMPTY"<<std::endl;
      MnvH1D *hist_TRUE_EMPTY = (MnvH1D*)EMPTY_playlist_TRUTHDEM.TFILE_PLAYLIST -> Get(histoName_TRUE);
      std::cout<<"hist_TRUE_RECO_EMPTY"<<std::endl;
      MnvH1D *hist_TRUE_RECO_EMPTY = (MnvH1D*)EMPTY_playlist_nom.TFILE_PLAYLIST -> Get(histoName_TRUE_RECO);

      MnvH1D* hist_TRUE_FULL_clone = (MnvH1D*)FULL_playlist_TRUTHDEM.TFILE_PLAYLIST -> Get(histoName_TRUE);
      MnvH1D* hist_TRUE_RECO_FULL_clone = (MnvH1D*)FULL_playlist_nom.TFILE_PLAYLIST -> Get(histoName_TRUE_RECO);
      MnvH1D* hist_TRUE_EMPTY_clone = (MnvH1D*)EMPTY_playlist_TRUTHDEM.TFILE_PLAYLIST -> Get(histoName_TRUE);
      MnvH1D* hist_TRUE_RECO_EMPTY_clone = (MnvH1D*)EMPTY_playlist_nom.TFILE_PLAYLIST -> Get(histoName_TRUE_RECO);


      hist_TRUE_FULL->AddMissingErrorBandsAndFillWithCV(*hist_TRUE_RECO_FULL);
      hist_TRUE_EMPTY->AddMissingErrorBandsAndFillWithCV(*hist_TRUE_RECO_FULL);
      hist_TRUE_FULL_clone->AddMissingErrorBandsAndFillWithCV(*hist_TRUE_RECO_FULL);
      hist_TRUE_EMPTY_clone->AddMissingErrorBandsAndFillWithCV(*hist_TRUE_RECO_FULL);


      ///Calculation FOR FINAL Eff
      hist_TRUE_EMPTY_clone->Scale(Scale_MC);
      hist_TRUE_RECO_EMPTY_clone->Scale(Scale_MC);
      hist_TRUE_FULL_clone->Add(hist_TRUE_EMPTY_clone,-1);
      hist_TRUE_RECO_FULL_clone->Add(hist_TRUE_RECO_EMPTY_clone,-1);
      hist_TRUE_RECO_FULL_clone->Divide(hist_TRUE_RECO_FULL_clone, hist_TRUE_FULL_clone, 1.0,1.0,"");



      std::string title_type = GetsecondTrkTitleName(playlist_name);
      std::string Xaxis_title = GetsecondTrk_AXIS_TitleName(playlist_name);
      auto FULL_name = FULL_playlist_nom.GetPlaylist();
      auto Empty_name = EMPTY_playlist_nom.GetPlaylist();
      std::string playlistFull =   GetPlaylist_InitialName(FULL_name); //FULL_playlist.GetPlaylistName();
      std::string playlistEmpty = GetPlaylist_InitialName(Empty_name); //EMPTY_playlist.GetPlaylistName();


      char title_type_char[title_type.length()+1];
      strcpy( title_type_char, title_type.c_str());

      char playlistFull_char[playlistFull.length()+1];
      strcpy( playlistFull_char, playlistFull.c_str());

      char playlistEmpty_char[ playlistEmpty.length()+1];
      strcpy( playlistEmpty_char,  playlistEmpty.c_str());

      sprintf(Title_His, "%s (%s) (True) (%s)(F) ", title_type_char,title,playlistFull_char);
      DrawCVAndError_FromTFile(FULL_playlist_TRUTHDEM.TFILE_PLAYLIST, histoName_TRUE, Title_His  , Xaxis_title, pdf );
      sprintf(Title_His, "%s (%s) (True+RECO) (%s)(F)", title_type_char,title,playlistFull_char);
      DrawCVAndError_FromTFile(FULL_playlist_nom.TFILE_PLAYLIST, histoName_TRUE_RECO, Title_His , Xaxis_title, pdf );
      sprintf(Title_His, "%s (%s) (True) (%s)(E)", title_type_char,title,playlistEmpty_char);
      DrawCVAndError_FromTFile(EMPTY_playlist_TRUTHDEM.TFILE_PLAYLIST, histoName_TRUE,Title_His, Xaxis_title, pdf );
      sprintf(Title_His, "%s (%s) (True+RECO) (%s)(E)", title_type_char,title,playlistEmpty_char);
      DrawCVAndError_FromTFile(EMPTY_playlist_nom.TFILE_PLAYLIST, histoName_TRUE_RECO,  Title_His , Xaxis_title, pdf );


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

/////////////////////////////////////
void Draw_Efficiency_Muon_FULL_EMPTY(PlayList_INFO FULL_playlist,PlayList_INFO EMPTY_playlist , const char *histoName,
          int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf , MuonVar playlist_name ){

      char histoName_TRUE[1024];
      char histoName_TRUE_RECO[1024];
      char Title_His[1024];

      double FULL_POT = FULL_playlist.Get_Pot();
      double EMPTY_POT = EMPTY_playlist.Get_Pot();
      double Scale_MC = FULL_POT / EMPTY_POT;

      sprintf(histoName_TRUE, "%s_TRUE", histoName);
      sprintf(histoName_TRUE_RECO, "%s_TRUE_RECO", histoName);
      std::cout<<"hist_TRUE_FULL"<<std::endl;
      MnvH1D *hist_TRUE_FULL = (MnvH1D*)FULL_playlist.TFILE_PLAYLIST -> Get(histoName_TRUE);
      std::cout<<"hist_TRUE_RECO_FULL"<<std::endl;
      MnvH1D *hist_TRUE_RECO_FULL = (MnvH1D*)FULL_playlist.TFILE_PLAYLIST -> Get(histoName_TRUE_RECO);
       std::cout<<"hist_TRUE_Empty"<<std::endl;
      MnvH1D *hist_TRUE_EMPTY = (MnvH1D*)EMPTY_playlist.TFILE_PLAYLIST -> Get(histoName_TRUE);
      std::cout<<"hist_TRUE_RECO_Empty"<<std::endl;
      MnvH1D *hist_TRUE_RECO_EMPTY = (MnvH1D*)EMPTY_playlist.TFILE_PLAYLIST -> Get(histoName_TRUE_RECO);

      std::cout<<"hist_TRUE_Full_clone"<<std::endl;
      MnvH1D* hist_TRUE_FULL_clone = (MnvH1D*)FULL_playlist.TFILE_PLAYLIST -> Get(histoName_TRUE);
      std::cout<<"hist_TRUE_RECO_Full_clone"<<std::endl;
      MnvH1D* hist_TRUE_RECO_FULL_clone = (MnvH1D*)FULL_playlist.TFILE_PLAYLIST -> Get(histoName_TRUE_RECO);
      std::cout<<"hist_TRUE_Empty_clone"<<std::endl;
      MnvH1D* hist_TRUE_EMPTY_clone = (MnvH1D*)EMPTY_playlist.TFILE_PLAYLIST -> Get(histoName_TRUE);
      std::cout<<"hist_TRUE_RECO_EMPTY_clone"<<std::endl;
      MnvH1D* hist_TRUE_RECO_EMPTY_clone = (MnvH1D*)EMPTY_playlist.TFILE_PLAYLIST -> Get(histoName_TRUE_RECO);

      std::cout<<"scaling TRUE EMPTY Clone scale =  "<< Scale_MC <<std::endl;
      ///Calculation FOR FINAL Eff
      hist_TRUE_EMPTY_clone->Scale(Scale_MC);

      std::cout<<"scaling TRUE RECO EMPTY Clone"<<std::endl;

      hist_TRUE_RECO_EMPTY_clone->Scale(Scale_MC);
      std::cout<<"F - E  TRUE clone "<<std::endl;

      hist_TRUE_FULL_clone->Add(hist_TRUE_EMPTY_clone,-1);
      hist_TRUE_RECO_FULL_clone->Add(hist_TRUE_RECO_EMPTY_clone,-1);
      hist_TRUE_RECO_FULL_clone->Divide(hist_TRUE_RECO_FULL_clone, hist_TRUE_FULL_clone, 1.0,1.0,"");



      std::string title_type = GetMuonVarTitleName(playlist_name);
      std::string Xaxis_title = GetMuonVarAXISName(playlist_name);
      auto FULL_name = FULL_playlist.GetPlaylist();
      auto Empty_name = EMPTY_playlist.GetPlaylist();
      std::string playlistFull =   GetPlaylist_InitialName(FULL_name); //FULL_playlist.GetPlaylistName();
      std::string playlistEmpty = GetPlaylist_InitialName(Empty_name); //EMPTY_playlist.GetPlaylistName();


      char title_type_char[title_type.length()+1];
      strcpy( title_type_char, title_type.c_str());

      char playlistFull_char[playlistFull.length()+1];
      strcpy( playlistFull_char, playlistFull.c_str());

      char playlistEmpty_char[ playlistEmpty.length()+1];
      strcpy( playlistEmpty_char,  playlistEmpty.c_str());

      std::cout<<"Drawing"<<std::endl;
      sprintf(Title_His, "%s (%s) (True) (%s)(F) ", title_type_char,title,playlistFull_char);
      DrawCVAndError_FromTFile(FULL_playlist.TFILE_PLAYLIST, histoName_TRUE, Title_His  , Xaxis_title, pdf );
      sprintf(Title_His, "%s (%s) (True+RECO) (%s)(F)", title_type_char,title,playlistFull_char);
      DrawCVAndError_FromTFile(FULL_playlist.TFILE_PLAYLIST, histoName_TRUE_RECO, Title_His , Xaxis_title, pdf );
      sprintf(Title_His, "%s (%s) (True) (%s)(E)", title_type_char,title,playlistEmpty_char);
      DrawCVAndError_FromTFile(EMPTY_playlist.TFILE_PLAYLIST, histoName_TRUE,Title_His, Xaxis_title, pdf );
      sprintf(Title_His, "%s (%s) (True+RECO) (%s)(E)", title_type_char,title,playlistEmpty_char);
      DrawCVAndError_FromTFile(EMPTY_playlist.TFILE_PLAYLIST, histoName_TRUE_RECO,  Title_His , Xaxis_title, pdf );


      hist_TRUE_RECO_FULL->Divide(hist_TRUE_RECO_FULL, hist_TRUE_FULL, 1.0,1.0,"");
      hist_TRUE_RECO_EMPTY->Divide(hist_TRUE_RECO_EMPTY, hist_TRUE_EMPTY, 1.0,1.0,"");

      sprintf(Title_His, "Eff(FULL) %s (%s)  (%s)(F) ", title_type_char,title,playlistFull_char);
      DrawCVAndError_FromHIST(hist_TRUE_RECO_FULL, Title_His ,Xaxis_title,"Efficiency", pdf,true);
      sprintf(Title_His, "Eff(Empty) %s (%s)  (%s)(E) ", title_type_char,title,playlistEmpty_char);
      DrawCVAndError_FromHIST(hist_TRUE_RECO_EMPTY, Title_His ,Xaxis_title,"Efficiency", pdf,true);
// need to change

      sprintf(Title_His, "%s (%s) (%s-%s)", title_type_char,title,playlistFull_char,playlistEmpty_char);
      DrawCVAndError_FromHIST(hist_TRUE_RECO_FULL_clone, Title_His ,Xaxis_title,"Efficiency", pdf,true);


}//endl;

void Draw_Efficiency_Muon_FULL_EMPTY_TRUTH(PlayList_INFO FULL_playlist_nom, PlayList_INFO FULL_playlist_TRUTHDEM,
                                           PlayList_INFO EMPTY_playlist_nom, PlayList_INFO EMPTY_playlist_TRUTH ,
                                            const char *histoName, int logScale, const char* title, MnvPlotter *plot,
                                             TCanvas *can, const char *pdf , MuonVar playlist_name, bool PrintallErrorBands ){

      char histoName_TRUE[1024];
      char histoName_TRUE_RECO[1024];
      char Title_His[1024];

      double FULL_POT = FULL_playlist_nom.Get_Pot();
      double EMPTY_POT = EMPTY_playlist_nom.Get_Pot();
      double Scale_MC = FULL_POT / EMPTY_POT;

      sprintf(histoName_TRUE, "%s_TRUE", histoName);
      sprintf(histoName_TRUE_RECO, "%s_TRUE_RECO", histoName);

      MnvH1D *hist_TRUE_FULL = (MnvH1D*)FULL_playlist_TRUTHDEM.TFILE_PLAYLIST -> Get(histoName_TRUE);
      MnvH1D *hist_TRUE_RECO_FULL = (MnvH1D*)FULL_playlist_nom.TFILE_PLAYLIST -> Get(histoName_TRUE_RECO);
      hist_TRUE_FULL->AddMissingErrorBandsAndFillWithCV(*hist_TRUE_RECO_FULL);
      MnvH1D *hist_TRUE_EMPTY = (MnvH1D*)EMPTY_playlist_TRUTH.TFILE_PLAYLIST -> Get(histoName_TRUE);
      MnvH1D *hist_TRUE_RECO_EMPTY = (MnvH1D*)EMPTY_playlist_nom.TFILE_PLAYLIST -> Get(histoName_TRUE_RECO);
      hist_TRUE_EMPTY->AddMissingErrorBandsAndFillWithCV(*hist_TRUE_RECO_EMPTY);
      MnvH1D* hist_TRUE_FULL_clone = (MnvH1D*)FULL_playlist_TRUTHDEM.TFILE_PLAYLIST -> Get(histoName_TRUE);
      MnvH1D* hist_TRUE_RECO_FULL_clone = (MnvH1D*)FULL_playlist_nom.TFILE_PLAYLIST -> Get(histoName_TRUE_RECO);
      hist_TRUE_FULL_clone->AddMissingErrorBandsAndFillWithCV(*hist_TRUE_RECO_FULL_clone);
      MnvH1D* hist_TRUE_EMPTY_clone = (MnvH1D*)EMPTY_playlist_TRUTH.TFILE_PLAYLIST -> Get(histoName_TRUE);
      MnvH1D* hist_TRUE_RECO_EMPTY_clone = (MnvH1D*)EMPTY_playlist_nom.TFILE_PLAYLIST -> Get(histoName_TRUE_RECO);
      hist_TRUE_EMPTY_clone->AddMissingErrorBandsAndFillWithCV(*hist_TRUE_RECO_EMPTY_clone);

      ///Calculation FOR FINAL Eff
      hist_TRUE_EMPTY_clone->Scale(Scale_MC);
      hist_TRUE_RECO_EMPTY_clone->Scale(Scale_MC);
      hist_TRUE_FULL_clone->Add(hist_TRUE_EMPTY_clone,-1);
      hist_TRUE_RECO_FULL_clone->Add(hist_TRUE_RECO_EMPTY_clone,-1);


      std::string title_type = GetMuonVarTitleName(playlist_name);
      std::string Xaxis_title = GetMuonVarAXISName(playlist_name);
      auto FULL_name = FULL_playlist_nom.GetPlaylist();
      auto Empty_name = EMPTY_playlist_nom.GetPlaylist();
      std::string playlistFull =   GetPlaylist_InitialName(FULL_name); //FULL_playlist.GetPlaylistName();
      std::string playlistEmpty = GetPlaylist_InitialName(Empty_name); //EMPTY_playlist.GetPlaylistName();


      char title_type_char[title_type.length()+1];
      strcpy( title_type_char, title_type.c_str());

      char playlistFull_char[playlistFull.length()+1];
      strcpy( playlistFull_char, playlistFull.c_str());

      char playlistEmpty_char[ playlistEmpty.length()+1];
      strcpy( playlistEmpty_char,  playlistEmpty.c_str());

      sprintf(Title_His, "%s (%s) (TRUTH) (%s)(F) ", title_type_char,title,playlistFull_char);
      DrawCVAndError_FromTFile(PrintallErrorBands,FULL_playlist_TRUTHDEM.TFILE_PLAYLIST, histoName_TRUE, Title_His  , Xaxis_title, pdf );
      sprintf(Title_His, "%s (%s) (True+RECO) (%s)(F)", title_type_char,title,playlistFull_char);
      DrawCVAndError_FromTFile(PrintallErrorBands,FULL_playlist_nom.TFILE_PLAYLIST, histoName_TRUE_RECO, Title_His , Xaxis_title, pdf );
      sprintf(Title_His, "%s (%s) (TRUTH) (%s)(E)", title_type_char,title,playlistEmpty_char);
      DrawCVAndError_FromTFile(PrintallErrorBands,EMPTY_playlist_TRUTH.TFILE_PLAYLIST, histoName_TRUE,Title_His, Xaxis_title, pdf );
      sprintf(Title_His, "%s (%s) (True+RECO) (%s)(E)", title_type_char,title,playlistEmpty_char);
      DrawCVAndError_FromTFile(PrintallErrorBands,EMPTY_playlist_nom.TFILE_PLAYLIST, histoName_TRUE_RECO,  Title_His , Xaxis_title, pdf );

      auto bandnames_before = hist_TRUE_RECO_FULL_clone->GetErrorBandNames();
      auto bandnames_Truebefore = hist_TRUE_FULL_clone->GetErrorBandNames();
      for(auto bands:  bandnames_before){
        std::cout<<"RECO band names BEFORE divide  = " << bands<<std::endl;
      }

      for(auto bands:  bandnames_Truebefore){
        std::cout<<"TRUE band names BEFORE divide  = " << bands<<std::endl;
      }

      hist_TRUE_RECO_FULL->Divide(hist_TRUE_RECO_FULL, hist_TRUE_FULL, 1.0,1.0,""); // cl=0.683 b(1,1) mode , this is suppose to be the bayesdividion but didnn't work , if using biomional error if universe are equal then dividion cancels them to equal  zero
      hist_TRUE_RECO_EMPTY->Divide(hist_TRUE_RECO_EMPTY, hist_TRUE_EMPTY, 1.0,1.0,"");
      hist_TRUE_RECO_FULL_clone->Divide(hist_TRUE_RECO_FULL_clone, hist_TRUE_FULL_clone, 1.0,1.0,"");

      auto bandnames_AFTER = hist_TRUE_RECO_FULL_clone->GetErrorBandNames();
      auto bandnames_TrueAFTER = hist_TRUE_FULL_clone->GetErrorBandNames();
      for(auto bands:  bandnames_AFTER){
        std::cout<<"RECO band names AFTER divide  = " << bands<<std::endl;
      }

      for(auto bands:  bandnames_TrueAFTER){
        std::cout<<"TRUE band names AFTER divide  = " << bands<<std::endl;
      }


      sprintf(Title_His, "Eff(FULL) %s (%s)  (%s)(F) ", title_type_char,title,playlistFull_char);
      DrawCVAndError_FromHIST(PrintallErrorBands,hist_TRUE_RECO_FULL, Title_His ,Xaxis_title,"Efficiency", pdf,true);
      sprintf(Title_His, "Eff(Empty) %s (%s)  (%s)(E) ", title_type_char,title,playlistEmpty_char);
      DrawCVAndError_FromHIST(PrintallErrorBands,hist_TRUE_RECO_EMPTY, Title_His ,Xaxis_title,"Efficiency", pdf,true);


      sprintf(Title_His, "%s (%s) (%s-%s)", title_type_char,title,playlistFull_char,playlistEmpty_char);
      DrawCVAndError_FromHIST(PrintallErrorBands,hist_TRUE_RECO_FULL_clone, Title_His ,Xaxis_title,"Efficiency", pdf,true);


}//endl;B
///////////////////////////////////////////////////////////////////////////////////////

void Draw_Efficiency_CryoVertex_FULL_EMPTY_TRUTH(PlayList_INFO FULL_playlist_nom, PlayList_INFO FULL_playlist_TRUTHDEM,
  PlayList_INFO EMPTY_playlist_nom, PlayList_INFO EMPTY_playlist_TRUTHDEM , const char *histoName_num, const char *histoName_dem,
  int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf, CryoVertex CryoVertex_type ){

      char histoName_TRUE[1024];
      char histoName_TRUE_RECO[1024];
      char Title_His[1024];

      double FULL_POT_Dem = FULL_playlist_TRUTHDEM.Get_Pot();
      double FULL_POT_nom = FULL_playlist_nom.Get_Pot();
      if(FULL_POT_Dem!=FULL_POT_nom){std::cout<<"POT it different for Dem and Nom for Full playlist"<<std::endl;}

      double EMPTY_POT_nom = EMPTY_playlist_nom.Get_Pot();
      double EMPTY_POT_Dem = EMPTY_playlist_TRUTHDEM.Get_Pot();

      if(EMPTY_POT_Dem!=EMPTY_POT_nom){std::cout<<"POT it different for Dem and Nom for EMPTY playlist"<<std::endl;}


      double Scale_MC = FULL_POT_nom / EMPTY_POT_nom;

      sprintf(histoName_TRUE, "%s_TRUE", histoName_dem);
      sprintf(histoName_TRUE_RECO, "%s_TRUE_RECO", histoName_num);

      std::cout<<"Making plot with Hist(TRUE) name: "<< histoName_TRUE<<std::endl;
      std::cout<<"Making plot with Hist(TRUE+RECO) name: "<< histoName_TRUE_RECO<<std::endl;

      std::cout<<"hist_TRUE_FULL"<<std::endl;
      MnvH1D *hist_TRUE_FULL = (MnvH1D*)FULL_playlist_TRUTHDEM.TFILE_PLAYLIST -> Get(histoName_TRUE);
      std::cout<<"hist_TRUE_RECO_FULL"<<std::endl;
      MnvH1D *hist_TRUE_RECO_FULL = (MnvH1D*)FULL_playlist_nom.TFILE_PLAYLIST -> Get(histoName_TRUE_RECO);
      std::cout<<"hist_TRUE_EMPTY"<<std::endl;
      MnvH1D *hist_TRUE_EMPTY = (MnvH1D*)EMPTY_playlist_TRUTHDEM.TFILE_PLAYLIST -> Get(histoName_TRUE);
      std::cout<<"hist_TRUE_RECO_EMPTY"<<std::endl;
      MnvH1D *hist_TRUE_RECO_EMPTY = (MnvH1D*)EMPTY_playlist_nom.TFILE_PLAYLIST -> Get(histoName_TRUE_RECO);

      MnvH1D* hist_TRUE_FULL_clone = (MnvH1D*)FULL_playlist_TRUTHDEM.TFILE_PLAYLIST -> Get(histoName_TRUE);
      MnvH1D* hist_TRUE_RECO_FULL_clone = (MnvH1D*)FULL_playlist_nom.TFILE_PLAYLIST -> Get(histoName_TRUE_RECO);
      MnvH1D* hist_TRUE_EMPTY_clone = (MnvH1D*)EMPTY_playlist_TRUTHDEM.TFILE_PLAYLIST -> Get(histoName_TRUE);
      MnvH1D* hist_TRUE_RECO_EMPTY_clone = (MnvH1D*)EMPTY_playlist_nom.TFILE_PLAYLIST -> Get(histoName_TRUE_RECO);


      hist_TRUE_FULL->AddMissingErrorBandsAndFillWithCV(*hist_TRUE_RECO_FULL);
      hist_TRUE_EMPTY->AddMissingErrorBandsAndFillWithCV(*hist_TRUE_RECO_FULL);
      hist_TRUE_FULL_clone->AddMissingErrorBandsAndFillWithCV(*hist_TRUE_RECO_FULL);
      hist_TRUE_EMPTY_clone->AddMissingErrorBandsAndFillWithCV(*hist_TRUE_RECO_FULL);


      ///Calculation FOR FINAL Eff
      hist_TRUE_EMPTY_clone->Scale(Scale_MC);
      hist_TRUE_RECO_EMPTY_clone->Scale(Scale_MC);
      hist_TRUE_FULL_clone->Add(hist_TRUE_EMPTY_clone,-1);
      hist_TRUE_RECO_FULL_clone->Add(hist_TRUE_RECO_EMPTY_clone,-1);
      hist_TRUE_RECO_FULL_clone->Divide(hist_TRUE_RECO_FULL_clone, hist_TRUE_FULL_clone, 1.0,1.0,"");



      std::string title_type = GetVertexCryoTitleName(CryoVertex_type);
      std::string Xaxis_title = GetVertexCryoVarAxisTitle(CryoVertex_type);
      auto FULL_name = FULL_playlist_nom.GetPlaylist();
      auto Empty_name = EMPTY_playlist_nom.GetPlaylist();
      std::string playlistFull =   GetPlaylist_InitialName(FULL_name); //FULL_playlist.GetPlaylistName();
      std::string playlistEmpty = GetPlaylist_InitialName(Empty_name); //EMPTY_playlist.GetPlaylistName();


      char title_type_char[title_type.length()+1];
      strcpy( title_type_char, title_type.c_str());

      char playlistFull_char[playlistFull.length()+1];
      strcpy( playlistFull_char, playlistFull.c_str());

      char playlistEmpty_char[ playlistEmpty.length()+1];
      strcpy( playlistEmpty_char,  playlistEmpty.c_str());

      sprintf(Title_His, "%s (%s) (True) (%s)(F) ", title_type_char,title,playlistFull_char);
      DrawCVAndError_FromTFile(FULL_playlist_TRUTHDEM.TFILE_PLAYLIST, histoName_TRUE, Title_His  , Xaxis_title, pdf ); //no pdf format
      sprintf(Title_His, "%s (%s) (True+RECO) (%s)(F)", title_type_char,title,playlistFull_char);
      DrawCVAndError_FromTFile(FULL_playlist_nom.TFILE_PLAYLIST, histoName_TRUE_RECO, Title_His , Xaxis_title, pdf ); //no pdf format
      sprintf(Title_His, "%s (%s) (True) (%s)(E)", title_type_char,title,playlistEmpty_char);
      DrawCVAndError_FromTFile(EMPTY_playlist_TRUTHDEM.TFILE_PLAYLIST, histoName_TRUE,Title_His, Xaxis_title, pdf ); //no pdf format
      sprintf(Title_His, "%s (%s) (True+RECO) (%s)(E)", title_type_char,title,playlistEmpty_char);
      DrawCVAndError_FromTFile(EMPTY_playlist_nom.TFILE_PLAYLIST, histoName_TRUE_RECO,  Title_His , Xaxis_title, pdf ); //no pdf format


      hist_TRUE_RECO_FULL->Divide(hist_TRUE_RECO_FULL, hist_TRUE_FULL, 1.0,1.0,"");
      hist_TRUE_RECO_EMPTY->Divide(hist_TRUE_RECO_EMPTY, hist_TRUE_EMPTY, 1.0,1.0,"");

      sprintf(Title_His, "Eff(FULL) %s (%s)  (%s)(F) ", title_type_char,title,playlistFull_char);
      DrawCVAndError_FromHIST(hist_TRUE_RECO_FULL, Title_His ,Xaxis_title,"Efficiency", pdf,true); //no pdf format
      sprintf(Title_His, "Eff(Empty) %s (%s)  (%s)(E) ", title_type_char,title,playlistEmpty_char);
      DrawCVAndError_FromHIST(hist_TRUE_RECO_EMPTY, Title_His ,Xaxis_title,"Efficiency", pdf,true); //no pdf format

      sprintf(Title_His, "%s (%s) (%s-%s)", title_type_char,title,playlistFull_char,playlistEmpty_char);
      DrawCVAndError_FromHIST(hist_TRUE_RECO_FULL_clone, Title_His ,Xaxis_title,"Efficiency", pdf,true); //no pdf format

      DrawCVAndError_FromHIST(hist_TRUE_RECO_FULL_clone, Title_His ,Xaxis_title,"Efficiency", pdf,true,true); //no pdf format


}//endl;


void Draw_Efficiency_CryoVertex_FULL_EMPTY_TRUTH(PlayList_INFO FULL_playlist_nom, PlayList_INFO FULL_playlist_TRUTHDEM,
  PlayList_INFO EMPTY_playlist_nom, PlayList_INFO EMPTY_playlist_TRUTHDEM , const char *histoName_num, const char *histoName_dem,
  int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf, CryoVertex CryoVertex_type, bool PrintAllErrors ){

      char histoName_TRUE[1024];
      char histoName_TRUE_RECO[1024];
      char Title_His[1024];

      double FULL_POT_Dem = FULL_playlist_TRUTHDEM.Get_Pot();
      double FULL_POT_nom = FULL_playlist_nom.Get_Pot();
      if(FULL_POT_Dem!=FULL_POT_nom){std::cout<<"POT it different for Dem and Nom for Full playlist"<<std::endl;}

      double EMPTY_POT_nom = EMPTY_playlist_nom.Get_Pot();
      double EMPTY_POT_Dem = EMPTY_playlist_TRUTHDEM.Get_Pot();

      if(EMPTY_POT_Dem!=EMPTY_POT_nom){std::cout<<"POT it different for Dem and Nom for EMPTY playlist"<<std::endl;}

      double Scale_MC = FULL_POT_nom / EMPTY_POT_nom;

      sprintf(histoName_TRUE, "%s_TRUE", histoName_dem);
      sprintf(histoName_TRUE_RECO, "%s_TRUE_RECO", histoName_num);

      std::cout<<"Making plot with Hist(TRUE) name: "<< histoName_TRUE<<std::endl;
      std::cout<<"Making plot with Hist(TRUE+RECO) name: "<< histoName_TRUE_RECO<<std::endl;

      std::cout<<"hist_TRUE_FULL"<<std::endl;
      MnvH1D *hist_TRUE_FULL = (MnvH1D*)FULL_playlist_TRUTHDEM.TFILE_PLAYLIST -> Get(histoName_TRUE);
      std::cout<<"hist_TRUE_RECO_FULL"<<std::endl;
      MnvH1D *hist_TRUE_RECO_FULL = (MnvH1D*)FULL_playlist_nom.TFILE_PLAYLIST -> Get(histoName_TRUE_RECO);
      std::cout<<"hist_TRUE_EMPTY"<<std::endl;
      MnvH1D *hist_TRUE_EMPTY = (MnvH1D*)EMPTY_playlist_TRUTHDEM.TFILE_PLAYLIST -> Get(histoName_TRUE);
      std::cout<<"hist_TRUE_RECO_EMPTY"<<std::endl;
      MnvH1D *hist_TRUE_RECO_EMPTY = (MnvH1D*)EMPTY_playlist_nom.TFILE_PLAYLIST -> Get(histoName_TRUE_RECO);

      MnvH1D* hist_TRUE_FULL_clone = (MnvH1D*)FULL_playlist_TRUTHDEM.TFILE_PLAYLIST -> Get(histoName_TRUE);
      MnvH1D* hist_TRUE_RECO_FULL_clone = (MnvH1D*)FULL_playlist_nom.TFILE_PLAYLIST -> Get(histoName_TRUE_RECO);
      MnvH1D* hist_TRUE_EMPTY_clone = (MnvH1D*)EMPTY_playlist_TRUTHDEM.TFILE_PLAYLIST -> Get(histoName_TRUE);
      MnvH1D* hist_TRUE_RECO_EMPTY_clone = (MnvH1D*)EMPTY_playlist_nom.TFILE_PLAYLIST -> Get(histoName_TRUE_RECO);


      hist_TRUE_FULL->AddMissingErrorBandsAndFillWithCV(*hist_TRUE_RECO_FULL);
      hist_TRUE_EMPTY->AddMissingErrorBandsAndFillWithCV(*hist_TRUE_RECO_FULL);
      hist_TRUE_FULL_clone->AddMissingErrorBandsAndFillWithCV(*hist_TRUE_RECO_FULL);
      hist_TRUE_EMPTY_clone->AddMissingErrorBandsAndFillWithCV(*hist_TRUE_RECO_FULL);


      ///Calculation FOR FINAL Eff
      hist_TRUE_EMPTY_clone->Scale(Scale_MC);
      hist_TRUE_RECO_EMPTY_clone->Scale(Scale_MC);
      hist_TRUE_FULL_clone->Add(hist_TRUE_EMPTY_clone,-1);
      hist_TRUE_RECO_FULL_clone->Add(hist_TRUE_RECO_EMPTY_clone,-1);
      hist_TRUE_RECO_FULL_clone->Divide(hist_TRUE_RECO_FULL_clone, hist_TRUE_FULL_clone, 1.0,1.0,"");



      std::string title_type = GetVertexCryoTitleName(CryoVertex_type);
      std::string Xaxis_title = GetVertexCryoVarAxisTitle(CryoVertex_type);
      auto FULL_name = FULL_playlist_nom.GetPlaylist();
      auto Empty_name = EMPTY_playlist_nom.GetPlaylist();
      std::string playlistFull =   GetPlaylist_InitialName(FULL_name); //FULL_playlist.GetPlaylistName();
      std::string playlistEmpty = GetPlaylist_InitialName(Empty_name); //EMPTY_playlist.GetPlaylistName();


      char title_type_char[title_type.length()+1];
      strcpy( title_type_char, title_type.c_str());

      char playlistFull_char[playlistFull.length()+1];
      strcpy( playlistFull_char, playlistFull.c_str());

      char playlistEmpty_char[ playlistEmpty.length()+1];
      strcpy( playlistEmpty_char,  playlistEmpty.c_str());

      sprintf(Title_His, "%s (%s) (True) (%s)(F) ", title_type_char,title,playlistFull_char);
      DrawCVAndError_FromTFile(PrintAllErrors,FULL_playlist_TRUTHDEM.TFILE_PLAYLIST, histoName_TRUE, Title_His  , Xaxis_title, pdf );
      sprintf(Title_His, "%s (%s) (True+RECO) (%s)(F)", title_type_char,title,playlistFull_char);
      DrawCVAndError_FromTFile(PrintAllErrors, FULL_playlist_nom.TFILE_PLAYLIST, histoName_TRUE_RECO, Title_His , Xaxis_title, pdf );
      sprintf(Title_His, "%s (%s) (True) (%s)(E)", title_type_char,title,playlistEmpty_char);
      DrawCVAndError_FromTFile(PrintAllErrors,EMPTY_playlist_TRUTHDEM.TFILE_PLAYLIST, histoName_TRUE,Title_His, Xaxis_title, pdf );
      sprintf(Title_His, "%s (%s) (True+RECO) (%s)(E)", title_type_char,title,playlistEmpty_char);
      DrawCVAndError_FromTFile(PrintAllErrors,EMPTY_playlist_nom.TFILE_PLAYLIST, histoName_TRUE_RECO,  Title_His , Xaxis_title, pdf );


      hist_TRUE_RECO_FULL->Divide(hist_TRUE_RECO_FULL, hist_TRUE_FULL, 1.0,1.0,"");
      hist_TRUE_RECO_EMPTY->Divide(hist_TRUE_RECO_EMPTY, hist_TRUE_EMPTY, 1.0,1.0,"");

      sprintf(Title_His, "Eff(FULL) %s (%s)  (%s)(F) ", title_type_char,title,playlistFull_char);
      DrawCVAndError_FromHIST(PrintAllErrors, hist_TRUE_RECO_FULL, Title_His ,Xaxis_title,"Efficiency", pdf,true);
      sprintf(Title_His, "Eff(Empty) %s (%s)  (%s)(E) ", title_type_char,title,playlistEmpty_char);
      DrawCVAndError_FromHIST(PrintAllErrors, hist_TRUE_RECO_EMPTY, Title_His ,Xaxis_title,"Efficiency", pdf,true);

      sprintf(Title_His, "%s (%s) (%s-%s)", title_type_char,title,playlistFull_char,playlistEmpty_char);
      DrawCVAndError_FromHIST(PrintAllErrors, hist_TRUE_RECO_FULL_clone, Title_His ,Xaxis_title,"Efficiency", pdf,true);

      DrawCVAndError_FromHIST( hist_TRUE_RECO_FULL_clone, Title_His ,Xaxis_title,"Efficiency", pdf,true,true);


}//endl;
void Draw_Resolution_CryoVertex_FULL_EMPTY_RecoBranch(PlayList_INFO FULL_playlist_nom,
  PlayList_INFO EMPTY_playlist_nom,  const char *histoName_diff, const char *histoName_percent,
  int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf , CryoVertex CryoVertex_type ){

      char Title_His[1024];

      double FULL_POT_nom = FULL_playlist_nom.Get_Pot();
      double EMPTY_POT_nom = EMPTY_playlist_nom.Get_Pot();
      double Scale_MC = FULL_POT_nom / EMPTY_POT_nom;

      bool isfull = true;
      bool isempty = false;

      std::cout<<"hist_TRUE_RECO_FULL"<<std::endl;

      MnvH1D *hist_full_diff = (MnvH1D*)FULL_playlist_nom.TFILE_PLAYLIST -> Get(histoName_diff);
      MnvH1D *hist_full_Percent_diff = (MnvH1D*)FULL_playlist_nom.TFILE_PLAYLIST -> Get(histoName_percent);


      std::cout<<"hist_TRUE_EMPTY"<<std::endl;
      MnvH1D *hist_empty_diff = (MnvH1D*)EMPTY_playlist_nom.TFILE_PLAYLIST -> Get(histoName_diff);
      std::cout<<"hist_TRUE_RECO_EMPTY"<<std::endl;
      MnvH1D *hist_empty_Percent_diff = (MnvH1D*)EMPTY_playlist_nom.TFILE_PLAYLIST -> Get(histoName_percent);

      MnvH1D* hist_full_diff_clone = (MnvH1D*)FULL_playlist_nom.TFILE_PLAYLIST -> Get(histoName_diff);
      MnvH1D* hist_full_Percent_diff_clone = (MnvH1D*)FULL_playlist_nom.TFILE_PLAYLIST -> Get(histoName_percent);

      MnvH1D* hist_empty_diff_clone = (MnvH1D*)EMPTY_playlist_nom.TFILE_PLAYLIST -> Get(histoName_diff);
      MnvH1D* hist_empty_Percent_diff_clone = (MnvH1D*)EMPTY_playlist_nom.TFILE_PLAYLIST -> Get(histoName_percent);

      ///Calculation FOR FINAL Eff
      hist_empty_diff_clone->Scale(Scale_MC);
      hist_empty_Percent_diff_clone->Scale(Scale_MC);

      hist_full_diff_clone->Add(hist_empty_diff_clone,-1);
      hist_full_Percent_diff_clone->Add(hist_empty_Percent_diff_clone,-1);

      std::string title_type = GetVertexCryoTitleName(CryoVertex_type);
      std::string Xaxis_title = GetVertexCryoVarAxisTitle(CryoVertex_type);
      auto FULL_name = FULL_playlist_nom.GetPlaylist();
      auto Empty_name = EMPTY_playlist_nom.GetPlaylist();
      std::string playlistFull =   GetPlaylist_InitialName(FULL_name); //FULL_playlist.GetPlaylistName();
      std::string playlistEmpty = GetPlaylist_InitialName(Empty_name); //EMPTY_playlist.GetPlaylistName();


      char title_type_char[title_type.length()+1];
      strcpy( title_type_char, title_type.c_str());

      char playlistFull_char[playlistFull.length()+1];
      strcpy( playlistFull_char, playlistFull.c_str());

      char playlistEmpty_char[ playlistEmpty.length()+1];
      strcpy( playlistEmpty_char,  playlistEmpty.c_str());


      sprintf(Title_His, "True - Reco  %s (%s) (%s)(Full)", title_type_char, title , playlistFull_char);
      DrawCVAndError_FromHIST_withFit(hist_full_diff, Title_His ,Xaxis_title,"Resolution", pdf,true);

      sprintf(Title_His, "(True - Reco) / True  %s (%s) (%s)(Full)", title_type_char, title , playlistFull_char);
      DrawCVAndError_FromHIST_withFit(hist_full_Percent_diff, Title_His ,Xaxis_title,"Resolution", pdf,true);


      sprintf(Title_His, "True - Reco  %s (%s) (%s)(Empty)", title_type_char, title , playlistEmpty_char);
      DrawCVAndError_FromHIST_withFit(hist_empty_diff, Title_His ,Xaxis_title,"Resolution", pdf,true);

      sprintf(Title_His, "(True - Reco) / True  %s (%s) (%s)(Empty)", title_type_char, title , playlistEmpty_char);
      DrawCVAndError_FromHIST_withFit(hist_empty_Percent_diff, Title_His ,Xaxis_title,"Resolution", pdf,true);

      sprintf(Title_His, " True - Reco %s (%s) (%s-%s)", title_type_char,title,playlistFull_char,playlistEmpty_char);
      DrawCVAndError_FromHIST_withFit(hist_full_diff_clone, Title_His ,Xaxis_title,"Resolution", pdf,true);

      sprintf(Title_His, " (True - Reco) / True  %s (%s) (%s-%s)", title_type_char,title,playlistFull_char,playlistEmpty_char);
      DrawCVAndError_FromHIST_withFit(hist_full_Percent_diff_clone, Title_His ,Xaxis_title,"Resolution", pdf,true);



}//endl;
//////////////////////////////////////////////////////////////////////////////////////

void Draw_Ratio_CryoVertex_FULL_EMPTY_RecoBranch(PlayList_INFO FULL_playlist_nom,
  PlayList_INFO EMPTY_playlist_nom,  const char *histoName_nom, const char *histoName_dem,
  int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf , CryoVertex CryoVertex_type ){

      char Title_His[1024];

      double FULL_POT_nom = FULL_playlist_nom.Get_Pot();
      double EMPTY_POT_nom = EMPTY_playlist_nom.Get_Pot();
      double Scale_MC = FULL_POT_nom / EMPTY_POT_nom;
      bool isfull = true;
      bool isempty = false;

      MnvH1D *hist_full_nom = Get1DHist(*FULL_playlist_nom.TFILE_PLAYLIST, histoName_nom, isfull); //(MnvH1D*)FULL_playlist_nom.TFILE_PLAYLIST -> Get(histoName_nom);
      MnvH1D *hist_full_dem = Get1DHist(*FULL_playlist_nom.TFILE_PLAYLIST, histoName_dem, isfull); //(MnvH1D*)FULL_playlist_nom.TFILE_PLAYLIST -> Get(histoName_dem);

      MnvH1D *hist_empty_nom = Get1DHist(*EMPTY_playlist_nom.TFILE_PLAYLIST, histoName_nom, isempty); //(MnvH1D*)EMPTY_playlist_nom.TFILE_PLAYLIST -> Get(histoName_nom);
      MnvH1D *hist_empty_dem = Get1DHist(*EMPTY_playlist_nom.TFILE_PLAYLIST, histoName_dem, isempty); //(MnvH1D*)EMPTY_playlist_nom.TFILE_PLAYLIST -> Get(histoName_dem);

      MnvH1D* hist_full_nom_clone = Get1DHist(*FULL_playlist_nom.TFILE_PLAYLIST, histoName_nom, isfull);//(MnvH1D*)FULL_playlist_nom.TFILE_PLAYLIST -> Get(histoName_nom);
      MnvH1D* hist_full_dem_clone = Get1DHist(*FULL_playlist_nom.TFILE_PLAYLIST, histoName_dem, isfull); //(MnvH1D*)FULL_playlist_nom.TFILE_PLAYLIST -> Get(histoName_dem);

      MnvH1D* hist_empty_nom_clone = Get1DHist(*EMPTY_playlist_nom.TFILE_PLAYLIST, histoName_nom, isempty); //(MnvH1D*)EMPTY_playlist_nom.TFILE_PLAYLIST -> Get(histoName_nom);
      MnvH1D* hist_empty_dem_clone = Get1DHist(*EMPTY_playlist_nom.TFILE_PLAYLIST, histoName_dem, isempty);//(MnvH1D*)EMPTY_playlist_nom.TFILE_PLAYLIST -> Get(histoName_dem);

      ///Calculation FOR FINAL Eff
      hist_empty_nom_clone ->Scale(Scale_MC);
      hist_empty_dem_clone ->Scale(Scale_MC);

      hist_full_nom_clone->Add(hist_empty_nom_clone,-1);
      hist_full_dem_clone->Add(hist_empty_dem_clone,-1);

      std::string title_type = GetVertexCryoTitleName(CryoVertex_type);
      std::string Xaxis_title = GetVertexCryoVarAxisTitle(CryoVertex_type);
      auto FULL_name = FULL_playlist_nom.GetPlaylist();
      auto Empty_name = EMPTY_playlist_nom.GetPlaylist();
      std::string playlistFull =   GetPlaylist_InitialName(FULL_name); //FULL_playlist.GetPlaylistName();
      std::string playlistEmpty = GetPlaylist_InitialName(Empty_name); //EMPTY_playlist.GetPlaylistName();


      char title_type_char[title_type.length()+1];
      strcpy( title_type_char, title_type.c_str());

      char playlistFull_char[playlistFull.length()+1];
      strcpy( playlistFull_char, playlistFull.c_str());

      char playlistEmpty_char[ playlistEmpty.length()+1];
      strcpy( playlistEmpty_char,  playlistEmpty.c_str());

      hist_full_nom->Divide(hist_full_nom,hist_full_dem, 1.0,1.0,"");

      sprintf(Title_His, "Vertex Ratio %s (%s) (%s)(Full)", title_type_char, title , playlistFull_char);
      DrawCVAndError_FromHIST(hist_full_nom, Title_His ,Xaxis_title,"#frac{reco}{true}", pdf,true);

      hist_empty_nom->Divide(hist_empty_nom,hist_empty_dem,1.0,1.0,"");

      sprintf(Title_His, "Vertex Ratio  %s (%s) (%s)(Empty)", title_type_char, title , playlistFull_char);
      DrawCVAndError_FromHIST(hist_empty_nom, Title_His ,Xaxis_title,"#frac{reco}{true}", pdf,true);

      hist_full_nom_clone->Divide(hist_full_nom_clone,hist_full_dem_clone,1.0,1.0,"");
      sprintf(Title_His, "Vertex Ratio %s (%s) (%s-%s)", title_type_char,title,playlistFull_char,playlistEmpty_char);
      DrawCVAndError_FromHIST(hist_full_nom_clone, Title_His ,Xaxis_title,"#frac{reco}{true}", pdf,true);


}//endl;




//////////////////////////////////////////////////////////////////////////////////////
void Draw_Efficiency_2D_FULL_EMPTY(PlayList_INFO FULL_playlist, PlayList_INFO EMPTY_playlist , const char *histoName, const char *Xaxis_title, const char *Yaxis_title,
          int logScale, const char* title ,const char* title_type_char , MnvPlotter *plot, TCanvas *can, const char *pdf)
          {

      char histoName_TRUE[1024];
      char histoName_TRUE_RECO[1024];
      char Title_His[1024];

      double FULL_POT = FULL_playlist.Get_Pot();
      double EMPTY_POT = EMPTY_playlist.Get_Pot();
      double Scale_MC = FULL_POT / EMPTY_POT;

      sprintf(histoName_TRUE, "%s_TRUE", histoName);
      sprintf(histoName_TRUE_RECO, "%s_TRUE_RECO", histoName);
      bool isfull = true;
      bool isempty = false;
      MnvH2D *hist_TRUE_FULL = Get2DHist(*FULL_playlist.TFILE_PLAYLIST, histoName_TRUE, isfull);
      MnvH2D *hist_TRUE_RECO_FULL = Get2DHist(*FULL_playlist.TFILE_PLAYLIST , histoName_TRUE_RECO, isfull);
      MnvH2D *hist_TRUE_EMPTY = Get2DHist(*EMPTY_playlist.TFILE_PLAYLIST, histoName_TRUE, isempty);
      MnvH2D *hist_TRUE_RECO_EMPTY = Get2DHist(*EMPTY_playlist.TFILE_PLAYLIST, histoName_TRUE_RECO, isempty);

      MnvH2D* hist_TRUE_FULL_clone = Get2DHist(*FULL_playlist.TFILE_PLAYLIST, histoName_TRUE, isfull);
      MnvH2D* hist_TRUE_RECO_FULL_clone = Get2DHist(*FULL_playlist.TFILE_PLAYLIST , histoName_TRUE_RECO, isfull);
      MnvH2D* hist_TRUE_EMPTY_clone = Get2DHist(*EMPTY_playlist.TFILE_PLAYLIST, histoName_TRUE, isempty);
      MnvH2D* hist_TRUE_RECO_EMPTY_clone = Get2DHist(*EMPTY_playlist.TFILE_PLAYLIST, histoName_TRUE_RECO, isempty);
      /////////////////////

      //MnvH2D *hist_TRUE_FULL = (MnvH2D*)FULL_playlist.TFILE_PLAYLIST -> Get(histoName_TRUE);
      //MnvH2D *hist_TRUE_RECO_FULL = (MnvH2D*)FULL_playlist.TFILE_PLAYLIST -> Get(histoName_TRUE_RECO);
      //MnvH2D *hist_TRUE_EMPTY = (MnvH2D*)EMPTY_playlist.TFILE_PLAYLIST -> Get(histoName_TRUE);
      //MnvH2D *hist_TRUE_RECO_EMPTY = (MnvH2D*)EMPTY_playlist.TFILE_PLAYLIST -> Get(histoName_TRUE_RECO);

      //MnvH2D* hist_TRUE_FULL_clone = (MnvH2D*)FULL_playlist.TFILE_PLAYLIST -> Get(histoName_TRUE);
      //MnvH2D* hist_TRUE_RECO_FULL_clone = (MnvH2D*)FULL_playlist.TFILE_PLAYLIST -> Get(histoName_TRUE_RECO);
      //MnvH2D* hist_TRUE_EMPTY_clone = (MnvH2D*)EMPTY_playlist.TFILE_PLAYLIST -> Get(histoName_TRUE);
      //MnvH2D* hist_TRUE_RECO_EMPTY_clone = (MnvH2D*)EMPTY_playlist.TFILE_PLAYLIST -> Get(histoName_TRUE_RECO);

      ///Calculation FOR FINAL Eff
      hist_TRUE_EMPTY_clone->Scale(Scale_MC);
      hist_TRUE_RECO_EMPTY_clone->Scale(Scale_MC);
      hist_TRUE_FULL_clone->Add(hist_TRUE_EMPTY_clone,-1);
      hist_TRUE_RECO_FULL_clone->Add(hist_TRUE_RECO_EMPTY_clone,-1);
      hist_TRUE_RECO_FULL_clone->Divide(hist_TRUE_RECO_FULL_clone, hist_TRUE_FULL_clone, 1.0,1.0,"");



      //std::string title_type = GetsecondTrkTitleName(playlist_name);
      //std::string Xaxis_title = GetsecondTrk_AXIS_TitleName(playlist_name);
      auto FULL_name = FULL_playlist.GetPlaylist();
      auto Empty_name = EMPTY_playlist.GetPlaylist();
      std::string playlistFull =   GetPlaylist_InitialName(FULL_name); //FULL_playlist.GetPlaylistName();
      std::string playlistEmpty = GetPlaylist_InitialName(Empty_name); //EMPTY_playlist.GetPlaylistName();



    //  char title_type_char[title_type.length()+1];
      //strcpy( title_type_char, title_type.c_str());

      char playlistFull_char[playlistFull.length()+1];
      strcpy( playlistFull_char, playlistFull.c_str());

      char playlistEmpty_char[ playlistEmpty.length()+1];
      strcpy( playlistEmpty_char,  playlistEmpty.c_str());

      sprintf(Title_His, "%s (%s) (True) (%s)(F) ", title, title_type_char, playlistFull_char);
      Draw2DHist_TFILE(FULL_playlist.TFILE_PLAYLIST, histoName_TRUE, Title_His  , Xaxis_title,Yaxis_title, pdf,can, plot );
      sprintf(Title_His, "%s (%s) (True+RECO) (%s)(F)", title,title_type_char,playlistFull_char);
      Draw2DHist_TFILE(FULL_playlist.TFILE_PLAYLIST, histoName_TRUE_RECO, Title_His , Xaxis_title,Yaxis_title, pdf ,can, plot);
      sprintf(Title_His, "%s (%s) (True) (%s)(E)", title,title_type_char,playlistEmpty_char);
      Draw2DHist_TFILE(EMPTY_playlist.TFILE_PLAYLIST, histoName_TRUE,Title_His, Xaxis_title,Yaxis_title, pdf,can, plot );
      sprintf(Title_His, "%s (%s) (True+RECO) (%s)(E)", title, title_type_char, playlistEmpty_char);
      Draw2DHist_TFILE(EMPTY_playlist.TFILE_PLAYLIST, histoName_TRUE_RECO,  Title_His , Xaxis_title,Yaxis_title, pdf,can, plot );


      hist_TRUE_RECO_FULL->Divide(hist_TRUE_RECO_FULL, hist_TRUE_FULL, 1.0,1.0,"");
      hist_TRUE_RECO_EMPTY->Divide(hist_TRUE_RECO_EMPTY, hist_TRUE_EMPTY, 1.0,1.0,"");

      sprintf(Title_His, "Eff(FULL) %s (%s)(F) ", title,playlistFull_char);
      //DrawCVAndError_FromHIST(hist_TRUE_RECO_FULL, Title_His ,Xaxis_title,"Efficiency", pdf,true);
      DrawMagration_heatMap(hist_TRUE_RECO_FULL, Xaxis_title,Yaxis_title, Title_His, pdf, can, plot);
      sprintf(Title_His, "Eff(Empty) %s (%s)(E) ", title,playlistEmpty_char);
    //  DrawCVAndError_FromHIST(hist_TRUE_RECO_EMPTY, Title_His ,Xaxis_title,"Efficiency", pdf,true);
      DrawMagration_heatMap(hist_TRUE_RECO_EMPTY, Xaxis_title,Yaxis_title, Title_His, pdf, can, plot);

      sprintf(Title_His, "%s (%s-%s)", title, playlistFull_char,playlistEmpty_char);
      //DrawCVAndError_FromHIST(hist_TRUE_RECO_FULL_clone, Title_His ,Xaxis_title,"Efficiency", pdf,true);
      DrawMagration_heatMap(hist_TRUE_RECO_FULL_clone, Xaxis_title,Yaxis_title, Title_His, pdf, can, plot);


}//endl;


void Draw_Efficiency_2D_FULL_EMPTY_TRUTH(PlayList_INFO FULL_playlist_nom,PlayList_INFO FULL_playlist_DemTRUE,
   PlayList_INFO EMPTY_playlist_nom,PlayList_INFO EMPTY_playlist_DemTRUE, const char *histoName, const char *Xaxis_title,
   const char *Yaxis_title, const char* title ,const char* title_type_char , MnvPlotter *plot, TCanvas *can, const char *pdf)
   {

      char histoName_TRUE[1024];
      char histoName_TRUE_RECO[1024];
      char Title_His[1024];

      double FULL_POT = FULL_playlist_nom.Get_Pot();
      double EMPTY_POT = EMPTY_playlist_nom.Get_Pot();
      double Scale_MC = FULL_POT / EMPTY_POT;

      sprintf(histoName_TRUE, "%s_TRUE", histoName);
      sprintf(histoName_TRUE_RECO, "%s_TRUE_RECO", histoName);
      std::cout<< "Getting Hist Named for True = " << histoName_TRUE<<std::endl;
      std::cout<< "Getting Hist Named for RECO True = " << histoName_TRUE_RECO <<std::endl;
      bool isfull = true;
      bool isempty = false;
      MnvH2D *hist_TRUE_FULL = Get2DHist(*FULL_playlist_DemTRUE.TFILE_PLAYLIST, histoName_TRUE, isfull);
      MnvH2D *hist_TRUE_RECO_FULL = Get2DHist(*FULL_playlist_nom.TFILE_PLAYLIST, histoName_TRUE_RECO, isfull);
      MnvH2D *hist_TRUE_EMPTY = Get2DHist(*EMPTY_playlist_DemTRUE.TFILE_PLAYLIST, histoName_TRUE, isempty);
      MnvH2D *hist_TRUE_RECO_EMPTY = Get2DHist(*EMPTY_playlist_nom.TFILE_PLAYLIST, histoName_TRUE_RECO, isempty);

      MnvH2D* hist_TRUE_FULL_clone = Get2DHist(*FULL_playlist_DemTRUE.TFILE_PLAYLIST, histoName_TRUE, isfull);
      MnvH2D* hist_TRUE_RECO_FULL_clone = Get2DHist(*FULL_playlist_nom.TFILE_PLAYLIST, histoName_TRUE_RECO, isfull);
      MnvH2D* hist_TRUE_EMPTY_clone = Get2DHist(*EMPTY_playlist_DemTRUE.TFILE_PLAYLIST, histoName_TRUE, isempty);
      MnvH2D* hist_TRUE_RECO_EMPTY_clone = Get2DHist(*EMPTY_playlist_nom.TFILE_PLAYLIST, histoName_TRUE_RECO, isempty);

            ///Calculation FOR FINAL Eff

      hist_TRUE_EMPTY_clone->Scale(Scale_MC);
      hist_TRUE_RECO_EMPTY_clone->Scale(Scale_MC);
      hist_TRUE_FULL_clone->Add(hist_TRUE_EMPTY_clone,-1);
      hist_TRUE_RECO_FULL_clone->Add(hist_TRUE_RECO_EMPTY_clone,-1);
      hist_TRUE_RECO_FULL_clone->Divide(hist_TRUE_RECO_FULL_clone,  hist_TRUE_FULL_clone, 1.0, 1.0,"");



      //std::string title_type = GetsecondTrkTitleName(playlist_name);
      //std::string Xaxis_title = GetsecondTrk_AXIS_TitleName(playlist_name);
      auto FULL_name = FULL_playlist_nom.GetPlaylist();
      auto Empty_name = EMPTY_playlist_nom.GetPlaylist();
      std::string playlistFull =   GetPlaylist_InitialName(FULL_name); //FULL_playlist.GetPlaylistName();
      std::string playlistEmpty = GetPlaylist_InitialName(Empty_name); //EMPTY_playlist.GetPlaylistName();

    //  char title_type_char[title_type.length()+1];
      //strcpy( title_type_char, title_type.c_str());

      char playlistFull_char[playlistFull.length()+1];
      strcpy( playlistFull_char, playlistFull.c_str());

      char playlistEmpty_char[ playlistEmpty.length()+1];
      strcpy( playlistEmpty_char,  playlistEmpty.c_str());
      // .pdf
      sprintf(Title_His, "%s (True) (%s)(F) ", title,   playlistFull_char);
      Draw2DHist_TFILE(FULL_playlist_DemTRUE.TFILE_PLAYLIST, histoName_TRUE, Title_His  , Xaxis_title,Yaxis_title, pdf,can, plot,false );
      sprintf(Title_His, "%s (True+RECO) (%s)(F)", title, playlistFull_char);
      Draw2DHist_TFILE(FULL_playlist_nom.TFILE_PLAYLIST, histoName_TRUE_RECO, Title_His , Xaxis_title,Yaxis_title, pdf ,can, plot,false);
      sprintf(Title_His, "%s (True) (%s)(E)", title, playlistEmpty_char);
      Draw2DHist_TFILE(EMPTY_playlist_DemTRUE.TFILE_PLAYLIST, histoName_TRUE,Title_His, Xaxis_title, Yaxis_title, pdf,can, plot,false );
      sprintf(Title_His, "%s (True+RECO) (%s)(E)", title,   playlistEmpty_char);
      Draw2DHist_TFILE(EMPTY_playlist_nom.TFILE_PLAYLIST, histoName_TRUE_RECO,  Title_His , Xaxis_title, Yaxis_title, pdf,can, plot,false );


      hist_TRUE_RECO_FULL->Divide(hist_TRUE_RECO_FULL, hist_TRUE_FULL, 1.0,1.0,"");
      hist_TRUE_RECO_EMPTY->Divide(hist_TRUE_RECO_EMPTY, hist_TRUE_EMPTY, 1.0,1.0,"");

      sprintf(Title_His, "%s %s (%s)(Full) ", title_type_char, title, playlistFull_char);
      //DrawCVAndError_FromHIST(hist_TRUE_RECO_FULL, Title_His ,Xaxis_title,"Efficiency", pdf,true);
      //DrawMagration_heatMap(hist_TRUE_RECO_FULL, Xaxis_title,Yaxis_title, Title_His, pdf, can, plot);
      DrawMagration_heatMap_noText(hist_TRUE_RECO_FULL, Xaxis_title,Yaxis_title, Title_His, pdf, can, plot); // need .pdf
      sprintf(Title_His, "%s %s (%s)(Empty) ", title_type_char, title, playlistEmpty_char);
    //  DrawCVAndError_FromHIST(hist_TRUE_RECO_EMPTY, Title_His ,Xaxis_title,"Efficiency", pdf,true);
      //DrawMagration_heatMap(hist_TRUE_RECO_EMPTY, Xaxis_title,Yaxis_title, Title_His, pdf, can, plot);
      DrawMagration_heatMap_noText(hist_TRUE_RECO_EMPTY, Xaxis_title,Yaxis_title, Title_His, pdf, can, plot);

      sprintf(Title_His, "%s %s (%s-%s)",title_type_char, title, playlistFull_char, playlistEmpty_char);
      //DrawCVAndError_FromHIST(hist_TRUE_RECO_FULL_clone, Title_His ,Xaxis_title,"Efficiency", pdf,true);
      //DrawMagration_heatMap(hist_TRUE_RECO_FULL_clone, Xaxis_title,Yaxis_title, Title_His, pdf, can, plot);
      DrawMagration_heatMap_noText(hist_TRUE_RECO_FULL_clone, Xaxis_title,Yaxis_title, Title_His, pdf, can, plot);

}//endl;



void Draw_Migration_2D_FULL_EMPTY_TRUTH( PlayList_INFO FULL_playlist, PlayList_INFO EMPTY_playlist,
   const char *histoName, const char *Xaxis_title, const char *Yaxis_title, const char* title,
   const char* title_type_char , MnvPlotter *plot, TCanvas *can, const char *pdf) /*Needs .pdf */
   {

    // gStyle->SetPalette(kGreenPink); //
     char Title_His[1024];

      double FULL_POT = FULL_playlist.Get_Pot();
      double EMPTY_POT = EMPTY_playlist.Get_Pot();
      double Scale_MC = FULL_POT / EMPTY_POT;

      bool isfull = true;
      bool isempty = false;

      MnvH2D *hMigration_FULL = Get2DHist(*FULL_playlist.TFILE_PLAYLIST, histoName, isfull);
      MnvH2D *hMigration_EMPTY = Get2DHist(*EMPTY_playlist.TFILE_PLAYLIST, histoName, isempty);

      MnvH2D *hMigration_FULL_clone = Get2DHist(*FULL_playlist.TFILE_PLAYLIST, histoName, isfull);
      MnvH2D *hMigration_EMPTY_clone = Get2DHist(*EMPTY_playlist.TFILE_PLAYLIST, histoName, isempty);

      hMigration_EMPTY_clone->Scale(Scale_MC);
      hMigration_EMPTY_clone->Scale(Scale_MC);
      hMigration_FULL_clone->Add(hMigration_EMPTY_clone,-1);

      auto FULL_name = FULL_playlist.GetPlaylist();
      auto Empty_name = EMPTY_playlist.GetPlaylist();
      std::string playlistFull =   GetPlaylist_InitialName(FULL_name);
      std::string playlistEmpty = GetPlaylist_InitialName(Empty_name);

      char playlistFull_char[playlistFull.length()+1];
      strcpy( playlistFull_char, playlistFull.c_str());

      char playlistEmpty_char[ playlistEmpty.length()+1];
      strcpy( playlistEmpty_char,  playlistEmpty.c_str());
      // .pdf
      sprintf(Title_His, "Migration %s [Full(%s)]", title,   playlistFull_char);
      Draw2DHist_TFILE(FULL_playlist.TFILE_PLAYLIST, histoName, Title_His  , Xaxis_title,Yaxis_title, pdf,can, plot, false );

      sprintf(Title_His, "Migration %s [Empty(%s)]", title, playlistEmpty_char);
      Draw2DHist_TFILE(EMPTY_playlist.TFILE_PLAYLIST, histoName,Title_His, Xaxis_title, Yaxis_title, pdf,can, plot, false );

      sprintf(Title_His, "Migration %s [Full(%s)]",  title, playlistFull_char);
      DrawMagration_heatMap_noText(hMigration_FULL, Xaxis_title,Yaxis_title, Title_His, pdf, can, plot); // need .pdf

      sprintf(Title_His, "Migration %s [Empty(%s)]", title, playlistEmpty_char);
      DrawMagration_heatMap_noText(hMigration_EMPTY, Xaxis_title,Yaxis_title, Title_His, pdf, can, plot);

      sprintf(Title_His, "Migration %s (%s-%s)", title, playlistFull_char, playlistEmpty_char);
      DrawMagration_heatMap_noText(hMigration_FULL_clone, Xaxis_title,Yaxis_title, Title_His, pdf, can, plot);

}//endl;





void Draw_Resolution_2D_FULL_EMPTY_TRUTH(PlayList_INFO FULL_playlist,
  PlayList_INFO EMPTY_playlist, const char *histoName, const char *Xaxis_title, const char *Yaxis_title,
  const char* title ,const char* title_type_char , MnvPlotter *plot, TCanvas *can, const char *pdf, Double_t ymax)
  {
    gStyle->SetPalette(kBird);
    char Title_His[1024];
    bool isFull = true;
    bool isEmpty= false;
    double FULL_POT = FULL_playlist.Get_Pot();
    double EMPTY_POT = EMPTY_playlist.Get_Pot();
    double Scale_MC = FULL_POT / EMPTY_POT;

    MnvH2D *hist_FULL = Get2DHist(*FULL_playlist.TFILE_PLAYLIST, histoName, isFull);
    MnvH2D *hist_EMPTY = Get2DHist(*EMPTY_playlist.TFILE_PLAYLIST, histoName, isEmpty);

    MnvH2D *hist_FULL_clone = Get2DHist(*FULL_playlist.TFILE_PLAYLIST, histoName, isFull);
    MnvH2D *hist_EMPTY_clone = Get2DHist(*EMPTY_playlist.TFILE_PLAYLIST, histoName, isEmpty);


    //MnvH2D *hist_FULL = (MnvH2D*)FULL_playlist.TFILE_PLAYLIST -> Get(histoName);
    //MnvH2D *hist_EMPTY = (MnvH2D*)EMPTY_playlist.TFILE_PLAYLIST -> Get(histoName);

    //MnvH2D *hist_FULL_clone = (MnvH2D*)FULL_playlist.TFILE_PLAYLIST -> Get(histoName);
    //MnvH2D *hist_EMPTY_clone = (MnvH2D*)EMPTY_playlist.TFILE_PLAYLIST -> Get(histoName);

    ///Calculation FOR FINAL Eff
    hist_EMPTY_clone->Scale(Scale_MC);
    hist_EMPTY->Scale(Scale_MC);

    hist_FULL_clone->Add(hist_EMPTY_clone,-1);

    //ProjectionY()
    //std::string title_type = GetsecondTrkTitleName(playlist_name);
    //std::string Xaxis_title = GetsecondTrk_AXIS_TitleName(playlist_name);
    auto FULL_name = FULL_playlist.GetPlaylist();
    auto Empty_name = EMPTY_playlist.GetPlaylist();
    std::string playlistFull =   GetPlaylist_InitialName(FULL_name); //FULL_playlist.GetPlaylistName();
    std::string playlistEmpty = GetPlaylist_InitialName(Empty_name); //EMPTY_playlist.GetPlaylistName();


    char playlistFull_char[playlistFull.length()+1];
    strcpy( playlistFull_char, playlistFull.c_str());

    char playlistEmpty_char[ playlistEmpty.length()+1];
    strcpy( playlistEmpty_char,  playlistEmpty.c_str());

    char pdf_withTag[1024];
    sprintf(pdf_withTag, "%s.pdf", pdf);

    sprintf(Title_His, "(Resolution) %s (%s)(Full)", title, playlistFull_char);
    //DrawCVAndError_FromHIST(hist_TRUE_RECO_FULL, Title_His ,Xaxis_title,"Efficiency", pdf,true);
    std::cout<<"inside:Draw_Resolution_2D_FULL_EMPTY_TRUTH:->DrawMagration_heatMap "<<std::endl;
    DrawMagration_heatMap(hist_FULL, Xaxis_title, Yaxis_title, Title_His, pdf_withTag, can, plot); //pdf
    std::cout<<"inside:Draw_Resolution_2D_FULL_EMPTY_TRUTH:->Draw2DHist_hist "<<std::endl;
    Draw2DHist_hist(hist_FULL,Title_His, Xaxis_title ,Yaxis_title, pdf_withTag, can, plot); //pdf
    std::cout<<"inside:Draw_Resolution_2D_FULL_EMPTY_TRUTH:->Draw2DHist_histWithTProfile "<<std::endl;
    Draw2DHist_histWithTProfile(hist_FULL,Title_His, Xaxis_title ,Yaxis_title, pdf_withTag, can, plot); //pdf
    sprintf(Title_His, "(Resolution) %s (%s)(Empty)", title, playlistEmpty_char);
    //  DrawCVAndError_FromHIST(hist_TRUE_RECO_EMPTY, Title_His ,Xaxis_title,"Efficiency", pdf,true);
    std::cout<<"inside:Draw_Resolution_2D_FULL_EMPTY_TRUTH:->Draw2DHist_hist "<<std::endl;
    Draw2DHist_hist(hist_EMPTY,Title_His, Xaxis_title ,Yaxis_title, pdf_withTag, can, plot);
    std::cout<<"inside:Draw_Resolution_2D_FULL_EMPTY_TRUTH:->DrawMagration_heatMap "<<std::endl;
    DrawMagration_heatMap(hist_EMPTY, Xaxis_title, Yaxis_title, Title_His, pdf_withTag, can, plot); //pdf

    sprintf(Title_His, "%s (%s-%s)", title, playlistFull_char,playlistEmpty_char);
    //DrawCVAndError_FromHIST(hist_TRUE_RECO_FULL_clone, Title_His ,Xaxis_title,"Efficiency", pdf,true);
    std::cout<<"inside:Draw_Resolution_2D_FULL_EMPTY_TRUTH:->Draw2DHist_hist "<<std::endl;

    Draw2DHist_hist(hist_FULL_clone, Title_His, Xaxis_title ,Yaxis_title, pdf_withTag, can, plot);
    std::cout<<"inside:Draw_Resolution_2D_FULL_EMPTY_TRUTH:->Draw2DHist_histWithTProfile "<<std::endl;
    Draw2DHist_histWithTProfile(hist_FULL_clone,Title_His, Xaxis_title ,Yaxis_title, pdf_withTag, can, plot); //pdf
    std::cout<<"inside:Draw_Resolution_2D_FULL_EMPTY_TRUTH:->DrawMagration_heatMap "<<std::endl;
    DrawMagration_heatMap(hist_FULL_clone, Xaxis_title,Yaxis_title, Title_His, pdf_withTag, can, plot); //pdf
    std::cout<<"inside:Draw_Resolution_2D_FULL_EMPTY_TRUTH:->Draw_XDistribution_PerBinWithGaussFit_2DHist"<<std::endl;
    bool setGrid = true;
    Draw_XDistribution_PerBinWithGaussFit_2DHist(hist_FULL_clone, Title_His, Yaxis_title ,"NEvents", pdf, can, plot,setGrid, ymax); //needs no pdf format

  }//endl;


  void Draw_Resolution_2D_Helium_nonHelium_FULL_TRUTH(PlayList_INFO FULL_playlist,
     const char *histoName, const char *Xaxis_title, const char *Yaxis_title,
    const char* title ,const char* title_type_char , MnvPlotter *plot, TCanvas *can, const char *pdf, Double_t ymax)
    {
      gStyle->SetPalette(kBird);
      char Title_His[1024];
      bool isFull = true;

      char histoName_helium[1024];
      char histoName_nonhelium[1024];
      sprintf(histoName_helium, "%s_helium", histoName);
      sprintf(histoName_nonhelium, "%s_nonhelium", histoName);

      MnvH2D *hist_FULL_Total = Get2DHist(*FULL_playlist.TFILE_PLAYLIST, histoName, isFull);
      MnvH2D *hist_FULL_helium = Get2DHist(*FULL_playlist.TFILE_PLAYLIST, histoName_helium, isFull);
      MnvH2D *hist_FULL_nonhelium = Get2DHist(*FULL_playlist.TFILE_PLAYLIST, histoName_nonhelium, isFull);

      auto FULL_name = FULL_playlist.GetPlaylist();
      std::string playlistFull =   GetPlaylist_InitialName(FULL_name); //FULL_playlist.GetPlaylistName();


      char playlistFull_char[playlistFull.length()+1];
      strcpy( playlistFull_char, playlistFull.c_str());

      char pdf_withTag[1024];
      sprintf(pdf_withTag, "%s.pdf", pdf);

      sprintf(Title_His, "%s (%s)[Helium]", title, playlistFull_char);
      std::cout<<"inside:Draw_Resolution_2D_FULL_EMPTY_TRUTH:->Draw2DHist_hist "<<std::endl;
      Draw2DHist_hist(hist_FULL_helium, Title_His, Xaxis_title, Yaxis_title, pdf_withTag, can, plot); //pdf
      Draw2DHist_histWithTProfile(hist_FULL_helium, Title_His, Xaxis_title ,Yaxis_title, pdf_withTag, can, plot); //pdf
      sprintf(Title_His, "%s (%s)[Non-Helium]", title, playlistFull_char);
      Draw2DHist_hist(hist_FULL_nonhelium, Title_His, Xaxis_title ,Yaxis_title, pdf_withTag, can, plot); //pdf
      Draw2DHist_histWithTProfile(hist_FULL_nonhelium,Title_His, Xaxis_title ,Yaxis_title, pdf_withTag, can, plot); //pdf

      bool setGrid= true;
      char Playlist_tag[1024];
      std::cout<<"inside:Draw_Resolution_2D_FULL_EMPTY_TRUTH:->Draw2DHist_histWithTProfile "<<std::endl;
      sprintf(Playlist_tag, "F(%s)", playlistFull_char);
      sprintf(Title_His, "%s [%s]", title, Playlist_tag);

      //  DrawCVAndError_FromHIST(hist_TRUE_RECO_EMPTY, Title_His ,Xaxis_title,"Efficiency", pdf,true);
      Draw_XDistribution_PerBinWithGaussFit_2DHist(hist_FULL_Total, hist_FULL_helium, hist_FULL_nonhelium, Title_His, Yaxis_title ,"NEvents", pdf, Playlist_tag,  can, plot, setGrid, ymax, false, false); //needs no pdf format






    }//endl;

    void Draw_Resolution_2D_Helium_nonHelium_FULL_TRUTH(PlayList_INFO FULL_playlist,PlayList_INFO Empty_playlist,
       const char *histoName, const char *Xaxis_title, const char *Yaxis_title,
      const char* title ,const char* title_type_char , MnvPlotter *plot, TCanvas *can, const char *pdf, Double_t ymax , bool include_overflows)
      {
        gStyle->SetPalette(kBird);
        char Title_His[1024];
        bool isFull = true;

        char histoName_helium[1024];
        char histoName_nonhelium[1024];
        sprintf(histoName_helium, "%s_helium", histoName);
        sprintf(histoName_nonhelium, "%s_nonhelium", histoName);

        MnvH2D *hist_FULL_Total = Get2DHist(*FULL_playlist.TFILE_PLAYLIST, histoName, isFull);
        MnvH2D *hist_FULL_helium = Get2DHist(*FULL_playlist.TFILE_PLAYLIST, histoName_helium, isFull);
        MnvH2D *hist_FULL_nonhelium = Get2DHist(*FULL_playlist.TFILE_PLAYLIST, histoName_nonhelium, isFull);

        MnvH2D *hist_EMPTY_Total = Get2DHist(*Empty_playlist.TFILE_PLAYLIST, histoName, isFull);
        MnvH2D *hist_EMPTY_helium = Get2DHist(*Empty_playlist.TFILE_PLAYLIST, histoName_helium, isFull);
        MnvH2D *hist_EMPTY_nonhelium = Get2DHist(*Empty_playlist.TFILE_PLAYLIST, histoName_nonhelium, isFull);


        MnvH2D *hist_FULL_EMPTY_Total = Get2DHist(*FULL_playlist.TFILE_PLAYLIST, histoName, isFull);
        MnvH2D *hist_FULL_EMPTY_helium = Get2DHist(*FULL_playlist.TFILE_PLAYLIST, histoName_helium, isFull);
        MnvH2D *hist_FULL_EMPTY_nonhelium = Get2DHist(*FULL_playlist.TFILE_PLAYLIST, histoName_nonhelium, isFull);

        double FULL_POT = FULL_playlist.Get_Pot();
        double EMPTY_POT = Empty_playlist.Get_Pot();
        double Scale_MC = FULL_POT / EMPTY_POT;
        hist_EMPTY_Total->Scale(Scale_MC);
        hist_EMPTY_helium->Scale(Scale_MC);
        hist_EMPTY_nonhelium->Scale(Scale_MC);
        Subtract_FullHist(*hist_FULL_EMPTY_Total, hist_EMPTY_Total);
        Subtract_FullHist(*hist_FULL_EMPTY_helium, hist_EMPTY_helium);
        Subtract_FullHist(*hist_FULL_EMPTY_nonhelium, hist_EMPTY_nonhelium);


        auto FULL_name = FULL_playlist.GetPlaylist();
        std::string playlistFull =   GetPlaylist_InitialName(FULL_name); //FULL_playlist.GetPlaylistName();

        auto EMPTY_name = Empty_playlist.GetPlaylist();
        std::string playlistEmpty =   GetPlaylist_InitialName(EMPTY_name); //FULL_playlist.GetPlaylistName();


        char playlistFull_char[playlistFull.length()+1];
        strcpy( playlistFull_char, playlistFull.c_str());
        char playlistEmpty_char[playlistFull.length()+1];
        strcpy( playlistEmpty_char, playlistEmpty.c_str());


        char pdf_withTag[1024];
        sprintf(pdf_withTag, "%s.pdf", pdf);

        char Playlist_tag[1024];

//================================================================
// FULL
//================================================================
sprintf(Playlist_tag, "F(%s)", playlistFull_char);
sprintf(Title_His, "%s [total][%s]", title, Playlist_tag);
Draw2DHist_hist_notext(hist_FULL_Total, Title_His, Xaxis_title, Yaxis_title, pdf_withTag, can, plot, include_overflows); //pdf
std::cout<<"inside:Draw_Resolution_2D_FULL_EMPTY_TRUTH:->Draw2DHist_hist "<<std::endl;
sprintf(Title_His, "%s [Helium][%s]", title, Playlist_tag);
std::cout<<"inside:Draw_Resolution_2D_FULL_EMPTY_TRUTH:->Draw2DHist_hist "<<std::endl;
Draw2DHist_hist_notext(hist_FULL_helium, Title_His, Xaxis_title, Yaxis_title, pdf_withTag, can, plot, include_overflows); //pdf
//Draw2DHist_histWithTProfile(hist_FULL_helium, Title_His, Xaxis_title ,Yaxis_title, pdf_withTag, can, plot); //pdf
sprintf(Title_His, "%s [%s][Non-Helium]", title, Playlist_tag);
Draw2DHist_hist_notext(hist_FULL_nonhelium, Title_His, Xaxis_title ,Yaxis_title, pdf_withTag, can, plot, include_overflows); //pdf
//Draw2DHist_histWithTProfile(hist_FULL_nonhelium,Title_His, Xaxis_title ,Yaxis_title, pdf_withTag, can, plot); //pdf


//================================================================
// Empty
//================================================================
sprintf(Playlist_tag, "E(%s)", playlistEmpty_char);
sprintf(Title_His, "%s [total][%s]", title, Playlist_tag);
Draw2DHist_hist_notext(hist_EMPTY_Total, Title_His, Xaxis_title, Yaxis_title, pdf_withTag, can, plot, include_overflows); //pdf
sprintf(Title_His, "%s [Helium][%s]", title, Playlist_tag);
Draw2DHist_hist_notext(hist_EMPTY_helium, Title_His, Xaxis_title, Yaxis_title, pdf_withTag, can, plot, include_overflows); //pdf
sprintf(Title_His, "%s [%s][Non-Helium]", title, Playlist_tag);
Draw2DHist_hist_notext(hist_EMPTY_nonhelium, Title_His, Xaxis_title ,Yaxis_title, pdf_withTag, can, plot, include_overflows); //pdf
//================================================================
// Full - Empty
//================================================================
sprintf(Playlist_tag, "F(%s)-E(%s)", playlistFull_char, playlistEmpty_char);
sprintf(Title_His, "%s [total][%s]", title,Playlist_tag);
Draw2DHist_hist_notext(hist_FULL_EMPTY_Total, Title_His, Xaxis_title, Yaxis_title, pdf_withTag, can, plot, include_overflows); //pdf
sprintf(Title_His, "%s [Helium][%s]", title, Playlist_tag);
Draw2DHist_hist_notext(hist_FULL_EMPTY_helium, Title_His, Xaxis_title, Yaxis_title, pdf_withTag, can, plot, include_overflows); //pdf
sprintf(Title_His, "%s [Non-Helium][%s]", title,Playlist_tag);
Draw2DHist_hist_notext(hist_FULL_EMPTY_nonhelium, Title_His, Xaxis_title ,Yaxis_title, pdf_withTag, can, plot, include_overflows); //pdf

bool setGrid= true;

std::cout<<"inside:Draw_Resolution_2D_FULL_EMPTY_TRUTH:->Draw_XDistribution_PerBinWithGaussFit_2DHist"<<std::endl;
sprintf(Playlist_tag, "F(%s)", playlistFull_char);
sprintf(Title_His, "%s [%s]", title, Playlist_tag);
//  DrawCVAndError_FromHIST(hist_TRUE_RECO_EMPTY, Title_His ,Xaxis_title,"Efficiency", pdf,true);
Draw_XDistribution_PerBinWithGaussFit_2DHist(hist_FULL_Total, hist_FULL_helium, hist_FULL_nonhelium, Title_His, Yaxis_title ,"NEvents", pdf, Playlist_tag, can, plot, setGrid, ymax, false, false); //needs no pdf format
sprintf(Playlist_tag, "E(%s)", playlistEmpty_char);
sprintf(Title_His, "%s [%s]", title, Playlist_tag);
//  DrawCVAndError_FromHIST(hist_TRUE_RECO_EMPTY, Title_His ,Xaxis_title,"Efficiency", pdf,true);
Draw_XDistribution_PerBinWithGaussFit_2DHist(hist_EMPTY_Total, hist_EMPTY_helium, hist_EMPTY_nonhelium, Title_His, Yaxis_title ,"NEvents", pdf, Playlist_tag, can, plot, setGrid, ymax, false, false); //needs no pdf format

sprintf(Playlist_tag, "F(%s)-E(%s)", playlistFull_char, playlistEmpty_char);
sprintf(Title_His, "%s [%s]", title, Playlist_tag);
//  DrawCVAndError_FromHIST(hist_TRUE_RECO_EMPTY, Title_His ,Xaxis_title,"Efficiency", pdf,true);
Draw_XDistribution_PerBinWithGaussFit_2DHist(hist_FULL_EMPTY_Total, hist_FULL_EMPTY_helium, hist_FULL_EMPTY_nonhelium, Title_His, Yaxis_title ,"NEvents", pdf, Playlist_tag, can, plot, setGrid, ymax, false, false); //needs no pdf format


}//endl;




void Draw_2D_Xaxis_FiducialCut_FULL_EMPTY_TRUTH_Eff_Puritry(PlayList_INFO FULL_TRUE_playlist,
                                                            PlayList_INFO EMPTY_TRUE_playlist,
                                                            PlayList_INFO FULL_RECO_playlist,
                                                            PlayList_INFO EMPTY_RECO_playlist,
                                                            const char *histoName,
                                                            const char *Xaxis_title, const char *Yaxis_title,
const char* title ,const char* title_type_char , MnvPlotter *plot, TCanvas *can, const char *pdf, double maxY_recoCuts_full, double maxY_TruthCuts_full)
{
  gStyle->SetPalette(kBird);
  bool includeFlows = false;
  char Title_His[1024];
  bool isFull = true;
  bool isEmpty= false;

  char histoName_TRUE[1024];
  char histoName_TRUE_RECO[1024];

  char histoName_helium[1024];
  char histoName_nonhelium[1024];

  sprintf(histoName_TRUE, "%s_TRUE", histoName);
  sprintf(histoName_TRUE_RECO, "%s_TRUE_RECO", histoName);

  sprintf(histoName_helium, "%s_helium", histoName);
  sprintf(histoName_nonhelium, "%s_nonhelium", histoName);

  double FULL_POT = FULL_RECO_playlist.Get_Pot();
  double EMPTY_POT = EMPTY_RECO_playlist.Get_Pot();
  double Scale_MC = FULL_POT / EMPTY_POT;

  // Get RECO HISTs
  MnvH2D *hist_FULL_Numerator = Get2DHist(*FULL_RECO_playlist.TFILE_PLAYLIST, histoName_TRUE_RECO, isFull);
  MnvH2D *hist_EMPTY_Numerator = Get2DHist(*EMPTY_RECO_playlist.TFILE_PLAYLIST, histoName_TRUE_RECO, isEmpty);
  MnvH2D *hist_FULL_EMPTY_Numerator = Get2DHist(*FULL_RECO_playlist.TFILE_PLAYLIST, histoName_TRUE_RECO, isFull);
  MnvH2D *hist_FULL_EMPTY_Eff = Get2DHist(*FULL_RECO_playlist.TFILE_PLAYLIST, histoName_TRUE_RECO, isFull);
  MnvH2D *hist_FULL_EMPTY_Eff_Full = Get2DHist(*FULL_RECO_playlist.TFILE_PLAYLIST, histoName_TRUE_RECO, isFull);
  MnvH2D *hist_EMPTY_Eff = Get2DHist(*EMPTY_RECO_playlist.TFILE_PLAYLIST, histoName_TRUE_RECO, isEmpty);


  MnvH2D *hist_FULL_Denominator = Get2DHist(*FULL_TRUE_playlist.TFILE_PLAYLIST, histoName_TRUE, isFull);
  MnvH2D *hist_EMPTY_Denominator = Get2DHist(*EMPTY_TRUE_playlist.TFILE_PLAYLIST, histoName_TRUE, isEmpty);
  MnvH2D *hist_FULL_EMPTY_Denominator = Get2DHist(*FULL_TRUE_playlist.TFILE_PLAYLIST, histoName_TRUE, isFull);

  MnvH2D *hist_FULL_total = Get2DHist(*FULL_RECO_playlist.TFILE_PLAYLIST, histoName, isFull);
  MnvH2D *hist_EMPTY_total = Get2DHist(*EMPTY_RECO_playlist.TFILE_PLAYLIST, histoName, isEmpty);
  MnvH2D *hist_FULL_EMPTY_total = Get2DHist(*FULL_RECO_playlist.TFILE_PLAYLIST, histoName, isFull);

  MnvH2D *hist_FULL_RECO_helium = Get2DHist(*FULL_RECO_playlist.TFILE_PLAYLIST, histoName_helium, isFull);
  MnvH2D *hist_EMPTY_RECO_helium = Get2DHist(*EMPTY_RECO_playlist.TFILE_PLAYLIST, histoName_helium, isEmpty);
  MnvH2D *hist_FULL_EMPTY_RECO_helium = Get2DHist(*FULL_RECO_playlist.TFILE_PLAYLIST, histoName_helium, isFull);

  MnvH2D *hist_FULL_RECO_nonhelium = Get2DHist(*FULL_RECO_playlist.TFILE_PLAYLIST, histoName_nonhelium, isFull);
  MnvH2D *hist_EMPTY_RECO_nonhelium = Get2DHist(*EMPTY_RECO_playlist.TFILE_PLAYLIST, histoName_nonhelium, isEmpty);
  MnvH2D *hist_FULL_EMPTY_RECO_nonhelium = Get2DHist(*FULL_RECO_playlist.TFILE_PLAYLIST, histoName_nonhelium, isFull);

  hist_EMPTY_Eff->Scale(Scale_MC);
  hist_EMPTY_Numerator->Scale(Scale_MC);
  hist_EMPTY_Denominator->Scale(Scale_MC);
  hist_EMPTY_RECO_helium->Scale(Scale_MC);
  hist_EMPTY_RECO_nonhelium->Scale(Scale_MC);
  hist_EMPTY_total->Scale(Scale_MC);

  Subtract_FullHist(*hist_FULL_EMPTY_Numerator, hist_EMPTY_Numerator);
  Subtract_FullHist(*hist_FULL_EMPTY_Eff,       hist_EMPTY_Numerator);

  Subtract_FullHist(*hist_FULL_EMPTY_Denominator,    hist_EMPTY_Denominator);
  Subtract_FullHist(*hist_FULL_EMPTY_RECO_helium,    hist_EMPTY_RECO_helium);
  Subtract_FullHist(*hist_FULL_EMPTY_RECO_nonhelium, hist_EMPTY_RECO_nonhelium);
  Subtract_FullHist(*hist_FULL_EMPTY_total,          hist_EMPTY_total);


  auto FULL_name = FULL_RECO_playlist.GetPlaylist();
  auto Empty_name = EMPTY_RECO_playlist.GetPlaylist();
  std::string playlistFull =   GetPlaylist_InitialName(FULL_name); //FULL_playlist.GetPlaylistName();
  std::string playlistEmpty = GetPlaylist_InitialName(Empty_name); //EMPTY_playlist.GetPlaylistName();


  char playlistFull_char[playlistFull.length()+1];
  strcpy( playlistFull_char, playlistFull.c_str());

  char playlistEmpty_char[ playlistEmpty.length()+1];
  strcpy( playlistEmpty_char,  playlistEmpty.c_str());

  char pdf_withTag[1024];
  sprintf(pdf_withTag, "%s.pdf", pdf);

  ///////////////////////////
  //// Full
  ///////////////////////////

  sprintf(Title_His, "[Numerator RECO+TRUE cuts] %s [F(%s)]", title, playlistFull_char);
  Draw2DHist_hist_notext(hist_FULL_Numerator ,Title_His, Xaxis_title ,Yaxis_title, pdf_withTag, can, plot, includeFlows); //pdf

  sprintf(Title_His, "[denominator TRUE] %s [F(%s)]", title, playlistFull_char);
  std::cout<<"inside:Draw_2D_Xaxis_FiducialCut_FULL_EMPTY_TRUTH_Eff_Puritry:->Draw2DHist_hist "<<std::endl;
  Draw2DHist_hist_notext(hist_FULL_Denominator, Title_His, Xaxis_title ,Yaxis_title, pdf_withTag, can, plot, includeFlows); //pdf

  ///////////////////////////
  //// EMPTY
  ///////////////////////////

  sprintf(Title_His, "[Numerator RECO+TRUE cuts] %s [E(%s)]", title, playlistFull_char);
  //DrawCVAndError_FromHIST(hist_TRUE_RECO_FULL, Title_His ,Xaxis_title,"Efficiency", pdf,true);
  std::cout<<"inside:Draw_2D_Xaxis_FiducialCut_FULL_EMPTY_TRUTH_Eff_Puritry:->DrawMagration_heatMap "<<std::endl;
  Draw2DHist_hist_notext(hist_EMPTY_Numerator,Title_His, Xaxis_title, Yaxis_title,  pdf_withTag, can, plot, includeFlows); //pdf

  sprintf(Title_His, "[denominator TRUE] %s [E(%s)]", title, playlistFull_char);
  std::cout<<"inside:Draw_Resolution_2D_EMPTY_TRUTH:->Draw2DHist_hist "<<std::endl;
  Draw2DHist_hist_notext(hist_EMPTY_Denominator,Title_His, Xaxis_title ,Yaxis_title, pdf_withTag, can, plot, includeFlows); //pdf


  ///////////////////////////
  //// FULL - EMPTY
  ///////////////////////////

  sprintf(Title_His, "[Numerator RECO+TRUE cuts] %s [F(%s)-E(%s)]", title, playlistFull_char,playlistEmpty_char );
  std::cout<<"inside:Draw_2D_Xaxis_FiducialCut_FULL_EMPTY_TRUTH_Eff_Puritry:->Draw2DHist_hist "<<std::endl;
  Draw2DHist_hist_notext(hist_FULL_EMPTY_Numerator, Title_His, Xaxis_title ,Yaxis_title, pdf_withTag, can, plot, includeFlows); //pdf


  sprintf(Title_His, "[denominator TRUE] %s [F(%s)-E(%s)]", title, playlistFull_char,playlistEmpty_char );
  std::cout<<"inside:Draw_2D_Xaxis_FiducialCut_FULL_EMPTY_TRUTH_Eff_Puritry:->Draw2DHist_hist "<<std::endl;
  Draw2DHist_hist_notext(hist_FULL_EMPTY_Denominator, Title_His, Xaxis_title ,Yaxis_title, pdf_withTag, can, plot, includeFlows); //pdf

  /////////////////////////////////
  // Calculate Efficiency
  /////////////////////////////////
  hist_FULL_EMPTY_Eff->Divide(hist_FULL_EMPTY_Eff, hist_FULL_EMPTY_Denominator,1.0,1.0,"");
  hist_FULL_EMPTY_Eff_Full->Divide(hist_FULL_EMPTY_Eff_Full, hist_FULL_Denominator,1.0,1.0,"");
  hist_EMPTY_Eff->Divide(hist_EMPTY_Eff,hist_EMPTY_Denominator ,1.0,1.0,"");

  sprintf(Title_His, "[Efficiency] %s [F(%s)]", title, playlistFull_char );
  Draw2DHist_hist_notext(hist_FULL_EMPTY_Eff_Full, Title_His, Xaxis_title, Yaxis_title, pdf_withTag, can, plot, includeFlows); //pdf

  sprintf(Title_His, "[Efficiency] %s [E(%s)]", title,  playlistEmpty_char );
  Draw2DHist_hist_notext(hist_EMPTY_Eff, Title_His, Xaxis_title, Yaxis_title, pdf_withTag, can, plot, includeFlows); //pdf

  sprintf(Title_His, "[Efficiency] %s [F(%s)-E(%s)]", title, playlistFull_char, playlistEmpty_char );
  Draw2DHist_hist_notext(hist_FULL_EMPTY_Eff, Title_His, Xaxis_title ,Yaxis_title, pdf_withTag, can, plot, includeFlows); //pdf


  bool setGrid = true;
  bool LogX = false;
  bool LogY = false;

  //double maxY_recoCuts_full  = 180;
  //double maxY_TruthCuts_full  = 500;
  char PlayList_INFO[1024];
  sprintf(PlayList_INFO, "F(%s)", playlistFull_char);
  sprintf(Title_His, "%s ", title);
  Draw_YDistribution_PerBin_2DHist_Purity_Efficiency(hist_FULL_Numerator,
                                                     hist_FULL_Denominator,
                                                     hist_FULL_total,
                                                     hist_FULL_RECO_helium,
                                                     hist_FULL_RECO_nonhelium,
                                                     hist_FULL_EMPTY_Eff_Full,
 Title_His, Xaxis_title,Yaxis_title,PlayList_INFO, pdf, can, plot, setGrid, maxY_recoCuts_full, maxY_TruthCuts_full, LogX, LogY );

  sprintf(PlayList_INFO, "E(%s)", playlistEmpty_char);
  sprintf(Title_His, "%s", title);
  Draw_YDistribution_PerBin_2DHist_Purity_Efficiency(hist_EMPTY_Numerator,
                                                     hist_EMPTY_Denominator,
                                                     hist_EMPTY_total,
                                                     hist_EMPTY_RECO_helium,
                                                     hist_EMPTY_RECO_nonhelium,
                                                     hist_EMPTY_Eff,
Title_His, Xaxis_title,Yaxis_title, PlayList_INFO, pdf, can, plot, setGrid, maxY_recoCuts_full, maxY_TruthCuts_full, LogX, LogY );

  sprintf(PlayList_INFO, "F(%s)-E(%s)", playlistFull_char,playlistEmpty_char);
  sprintf(Title_His, "%s ", title);

  Draw_YDistribution_PerBin_2DHist_Purity_Efficiency(hist_FULL_EMPTY_Numerator,
                                                     hist_FULL_EMPTY_Denominator,
                                                     hist_FULL_EMPTY_total,
                                                     hist_FULL_EMPTY_RECO_helium,
                                                     hist_FULL_EMPTY_RECO_nonhelium,
                                                     hist_FULL_EMPTY_Eff,
 Title_His, Xaxis_title,Yaxis_title, PlayList_INFO, pdf, can, plot, setGrid, maxY_recoCuts_full, maxY_TruthCuts_full,  LogX, LogY );


  }//endl;
///////////////////////////////////
//
/////////////////////////////////////
void Draw_2D_Xaxis_FiducialCut_FULL_EMPTY(PlayList_INFO FULL_RECO_playlist,
                                          PlayList_INFO EMPTY_RECO_playlist,
  const char *histoName, const char *Xaxis_title, const char *Yaxis_title,
const char* title , MnvPlotter *plot, TCanvas *can,
const char *pdf, double maxY_recoCuts_full)
{
  gStyle->SetPalette(kBird);
  bool includeFlows = false;
  char Title_His[1024];
  bool isFull = true;
  bool isEmpty= false;

  char histoName_helium[1024];
  char histoName_nonhelium[1024];

  sprintf(histoName_helium, "%s_helium", histoName);
  sprintf(histoName_nonhelium, "%s_nonhelium", histoName);

  double FULL_POT = FULL_RECO_playlist.Get_Pot();
  double EMPTY_POT = EMPTY_RECO_playlist.Get_Pot();
  double Scale_MC = FULL_POT / EMPTY_POT;

  // Get RECO HISTs

  MnvH2D *hist_FULL_total = Get2DHist(*FULL_RECO_playlist.TFILE_PLAYLIST, histoName, isFull);
  MnvH2D *hist_EMPTY_total = Get2DHist(*EMPTY_RECO_playlist.TFILE_PLAYLIST, histoName, isEmpty);
  MnvH2D *hist_FULL_EMPTY_total = Get2DHist(*FULL_RECO_playlist.TFILE_PLAYLIST, histoName, isFull);

  MnvH2D *hist_FULL_RECO_helium = Get2DHist(*FULL_RECO_playlist.TFILE_PLAYLIST, histoName_helium, isFull);
  MnvH2D *hist_EMPTY_RECO_helium = Get2DHist(*EMPTY_RECO_playlist.TFILE_PLAYLIST, histoName_helium, isEmpty);
  MnvH2D *hist_FULL_EMPTY_RECO_helium = Get2DHist(*FULL_RECO_playlist.TFILE_PLAYLIST, histoName_helium, isFull);

  MnvH2D *hist_FULL_RECO_nonhelium = Get2DHist(*FULL_RECO_playlist.TFILE_PLAYLIST, histoName_nonhelium, isFull);
  MnvH2D *hist_EMPTY_RECO_nonhelium = Get2DHist(*EMPTY_RECO_playlist.TFILE_PLAYLIST, histoName_nonhelium, isEmpty);
  MnvH2D *hist_FULL_EMPTY_RECO_nonhelium = Get2DHist(*FULL_RECO_playlist.TFILE_PLAYLIST, histoName_nonhelium, isFull);

  hist_EMPTY_RECO_helium->Scale(Scale_MC);
  hist_EMPTY_RECO_nonhelium->Scale(Scale_MC);
  hist_EMPTY_total->Scale(Scale_MC);

  Subtract_FullHist(*hist_FULL_EMPTY_RECO_helium,    hist_EMPTY_RECO_helium);
  Subtract_FullHist(*hist_FULL_EMPTY_RECO_nonhelium, hist_EMPTY_RECO_nonhelium);
  Subtract_FullHist(*hist_FULL_EMPTY_total,          hist_EMPTY_total);


  auto FULL_name = FULL_RECO_playlist.GetPlaylist();
  auto Empty_name = EMPTY_RECO_playlist.GetPlaylist();
  std::string playlistFull =   GetPlaylist_InitialName(FULL_name); //FULL_playlist.GetPlaylistName();
  std::string playlistEmpty = GetPlaylist_InitialName(Empty_name); //EMPTY_playlist.GetPlaylistName();


  char playlistFull_char[playlistFull.length()+1];
  strcpy( playlistFull_char, playlistFull.c_str());

  char playlistEmpty_char[ playlistEmpty.length()+1];
  strcpy( playlistEmpty_char,  playlistEmpty.c_str());

  char pdf_withTag[1024];
  sprintf(pdf_withTag, "%s.pdf", pdf);

  ///////////////////////////
  //// Full
  ///////////////////////////

  sprintf(Title_His, "[RECO cuts] %s [F(%s)]", title, playlistFull_char);
  Draw2DHist_hist_notext(hist_FULL_total,Title_His, Xaxis_title ,Yaxis_title, pdf_withTag, can, plot, includeFlows); //pdf
  sprintf(Title_His, "[RECO cuts][Helium] %s [F(%s)]", title, playlistFull_char);
  Draw2DHist_hist_notext(hist_FULL_RECO_helium, Title_His, Xaxis_title ,Yaxis_title, pdf_withTag, can, plot, includeFlows); //pdf
  sprintf(Title_His, "[RECO cuts][nonHelium] %s [F(%s)]", title, playlistFull_char);
  Draw2DHist_hist_notext(hist_FULL_RECO_nonhelium, Title_His, Xaxis_title ,Yaxis_title, pdf_withTag, can, plot, includeFlows); //pdf

  ///////////////////////////
  //// EMPTY
  ///////////////////////////

  sprintf(Title_His, "[RECO cuts] %s [E(%s)]", title, playlistEmpty_char);
  Draw2DHist_hist_notext(hist_EMPTY_total,Title_His, Xaxis_title ,Yaxis_title, pdf_withTag, can, plot, includeFlows); //pdf
  sprintf(Title_His, "[RECO cuts][Helium] %s [E(%s)]", title, playlistEmpty_char);
  Draw2DHist_hist_notext(hist_EMPTY_RECO_helium, Title_His, Xaxis_title ,Yaxis_title, pdf_withTag, can, plot, includeFlows); //pdf
  sprintf(Title_His, "[RECO cuts][nonHelium] %s [E(%s)]", title, playlistEmpty_char);
  Draw2DHist_hist_notext(hist_EMPTY_RECO_nonhelium, Title_His, Xaxis_title ,Yaxis_title, pdf_withTag, can, plot, includeFlows); //pdf

  ///////////////////////////
  //// FULL - EMPTY
  ///////////////////////////

  sprintf(Title_His, "[RECO cuts] %s [F(%s)-E(%s)]", title,playlistFull_char, playlistEmpty_char);
  Draw2DHist_hist_notext(hist_FULL_EMPTY_total,Title_His, Xaxis_title ,Yaxis_title, pdf_withTag, can, plot, includeFlows); //pdf
  sprintf(Title_His, "[RECO cuts][Helium] %s [F(%s)-E(%s)]", title,playlistFull_char, playlistEmpty_char);
  Draw2DHist_hist_notext(hist_FULL_EMPTY_RECO_helium, Title_His, Xaxis_title ,Yaxis_title, pdf_withTag, can, plot, includeFlows); //pdf
  sprintf(Title_His, "[RECO cuts][nonHelium] %s [F(%s)-E(%s)]", title,playlistFull_char, playlistEmpty_char);
  Draw2DHist_hist_notext(hist_FULL_EMPTY_RECO_nonhelium, Title_His, Xaxis_title ,Yaxis_title, pdf_withTag, can, plot, includeFlows); //pdf



  bool setGrid = true;
  bool LogX = false;
  bool LogY = false;

  //double maxY_recoCuts_full  = 180;
  //double maxY_TruthCuts_full  = 500;
  char PlayList_INFO[1024];
  sprintf(PlayList_INFO, "F(%s)", playlistFull_char);
  sprintf(Title_His, "%s ", title);
  Draw_YDistribution_PerBin_2DHist(hist_FULL_total,
                                  hist_FULL_RECO_helium,
                                  hist_FULL_RECO_nonhelium,
 Title_His, Xaxis_title,Yaxis_title,PlayList_INFO, pdf, can, plot, setGrid, maxY_recoCuts_full, LogX, LogY );

  sprintf(PlayList_INFO, "E(%s)", playlistEmpty_char);
  sprintf(Title_His, "%s", title);
  Draw_YDistribution_PerBin_2DHist(hist_EMPTY_total,
                                 hist_EMPTY_RECO_helium,
                                 hist_EMPTY_RECO_nonhelium,
  Title_His, Xaxis_title,Yaxis_title, PlayList_INFO, pdf, can, plot, setGrid, maxY_recoCuts_full, LogX, LogY );

  sprintf(PlayList_INFO, "F(%s)-E(%s)", playlistFull_char,playlistEmpty_char);
  sprintf(Title_His, "%s ", title);

  Draw_YDistribution_PerBin_2DHist(hist_FULL_EMPTY_total,
                                  hist_FULL_EMPTY_RECO_helium,
                                  hist_FULL_EMPTY_RECO_nonhelium,
  Title_His, Xaxis_title,Yaxis_title, PlayList_INFO, pdf, can, plot, setGrid, maxY_recoCuts_full,  LogX, LogY );


  }//endl;




/////////////////////////////////////////////////////////////
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



void MakeLatexForEffMuonVar_StatsOnly(std::string output_name ,  std::string pdf_name_CV, const std::vector<MuonVar>muon_vector)
  {
  double scale= .23;
  std::ofstream myfile;

 std::string fileName = output_name + ".txt";
  myfile.open(fileName,std::ios::trunc);
  std::cout<<"Name of Output File "<< fileName<<std::endl;
  LatexFormat Muon_latex_Latex(scale);

  int pageCount = 38;

  int Full_empty_space = 4;
  int Var_space = 40;


  myfile<<Muon_latex_Latex.GetSubSection("Muon Varibles");

  for(auto cat: muon_vector){

    auto input_vectors = GetBinMuonVector(cat);
    std::string Var_name = GetMuonVarTitleName(cat);
    std::string Units_name = GetMuonUnitType(cat);


    myfile<<"\n";
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% Eff for Muon Var "<< Var_name <<" \n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<Muon_latex_Latex.GetBeginFrame(Var_name)<< "\n";
    myfile<<Muon_latex_Latex.GetBeginTabular()<< "\n";
    myfile<<Muon_latex_Latex.GetInclude_figure(pageCount, pdf_name_CV)<< "\n";
    myfile<<"& \n";
    myfile<<Muon_latex_Latex.GetInclude_figure(pageCount + Full_empty_space, pdf_name_CV )<< "\n";
    myfile<<"& \n";
    myfile<<Muon_latex_Latex.GetInclude_figure(pageCount + Full_empty_space + Full_empty_space, pdf_name_CV)<< "\n";
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
    pageCount = pageCount + Full_empty_space + Full_empty_space + Var_space ;

  }


  myfile.close();




}//end of





void Appendtotxt_2ndTrk(std::string output_name ,  std::string pdf_name_CV, int First_page, int Full_empty_space, char *Var_name ,char *Units_name, std::vector<double>input_vectors)
  {
  double scale= .23;
  std::ofstream myfile;

 std::string fileName = output_name + ".txt";
  myfile.open(fileName, std::ios_base::app);
  std::cout<<"Adding to Latex File "<< fileName<<std::endl;
  LatexFormat Muon_latex_Latex(scale);

  myfile<<Muon_latex_Latex.GetSubSection(Var_name);


    myfile<<"\n";
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% Eff for Muon Var "<< Var_name <<" \n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<Muon_latex_Latex.GetBeginFrame(Var_name)<< "\n";
    myfile<<Muon_latex_Latex.GetBeginTabular()<< "\n";
    myfile<<Muon_latex_Latex.GetInclude_figure(First_page, pdf_name_CV)<< "\n";
    myfile<<"& \n";
    myfile<<Muon_latex_Latex.GetInclude_figure(First_page + Full_empty_space, pdf_name_CV )<< "\n";
    myfile<<"& \n";
    myfile<<Muon_latex_Latex.GetInclude_figure(First_page + Full_empty_space + Full_empty_space, pdf_name_CV)<< "\n";
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





    myfile.close();




}//end of



void AppendtoText_Resolution(std::string output_name ,  std::string pdf_name_CV, int Figure_1_page_number,int Figure_2_page_number,
  int Figure_3_page_number, char *slideTitle , double FiducialCut)
  {
  double scale= .27;
  std::ofstream myfile;
  std::string fileName = output_name + ".txt";
  myfile.open(fileName, std::ios_base::app);
  std::cout<<"Adding to Latex File "<< fileName<<std::endl;
  LatexFormat Resolution_Latex(scale);
  myfile<<"\n";
  myfile<<"\n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<"%%% Resolution Fiducial Cut =   "<< FiducialCut<<" \n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<Resolution_Latex.GetBeginFrame(slideTitle)<< "\n";
  myfile<<Resolution_Latex.GetBeginTabular()<< "\n";
  myfile<<Resolution_Latex.GetInclude_figure(Figure_1_page_number, pdf_name_CV)<< "\n";
  myfile<<"& \n";
  myfile<<Resolution_Latex.Get_hSpace("-1cm")<< "\n";
  myfile<<Resolution_Latex.GetInclude_figure(Figure_2_page_number, pdf_name_CV )<< "\n";
  myfile<<"& \n";
  myfile<<Resolution_Latex.Get_hSpace("-1cm")<< "\n";
  myfile<<Resolution_Latex.GetInclude_figure(Figure_3_page_number, pdf_name_CV)<< "\n";
  myfile<<Resolution_Latex.GetEndTabular()<< "\n";
  myfile<<Resolution_Latex.GetEndFrame();

  myfile<<"\n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<"%%% END FRAME for Resolution \n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";

  myfile.close();

}//end of


void AppendtoLatex(std::string output_name ,  std::string pdf_name_CV, int Figure_1_page_number,int Figure_2_page_number,
 char *slideTitle , double FiducialCut, double scale )
  {

  std::ofstream myfile;
  std::string fileName = output_name + ".txt";
  myfile.open(fileName, std::ios_base::app);
  std::cout<<"Adding to Latex File "<< fileName<<std::endl;
  LatexFormat Resolution_Latex(scale);
  myfile<<"\n";
  myfile<<"\n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<"%%%" <<  slideTitle  << "  Fiducial Cut =   "<< FiducialCut<<" \n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<Resolution_Latex.GetBeginFrame(slideTitle)<< "\n";
  myfile<<Resolution_Latex.GetBeginTabular("cc")<< "\n";
  myfile<<Resolution_Latex.GetInclude_figure(Figure_1_page_number, pdf_name_CV)<< "\n";
  myfile<<"& \n";
  myfile<<Resolution_Latex.Get_hSpace("-1cm")<< "\n";
  myfile<<Resolution_Latex.GetInclude_figure(Figure_2_page_number, pdf_name_CV )<< "\n";
  myfile<<Resolution_Latex.GetEndTabular()<< "\n";
  myfile<<Resolution_Latex.GetEndFrame();

  myfile<<"\n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<"%%% END FRAME  \n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";

  myfile.close();

}//end of




void AppendtoLatex(std::string output_name ,  std::string pdf_name_CV, int Figure_1_page_number,int Figure_2_page_number,
  int Figure_3_page_number, char *slideTitle){
  double scale= .27;
  std::ofstream myfile;
  std::string fileName = output_name + ".txt";
  myfile.open(fileName, std::ios_base::app);
  std::cout<<"Adding to Latex File "<< fileName<<std::endl;
  LatexFormat Latex_output(scale);
  myfile<<"\n";
  myfile<<"\n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<"%%%  Start   "<< slideTitle<<" \n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<Latex_output.GetBeginFrame(slideTitle)<< "\n";
  myfile<<Latex_output.GetBeginTabular()<< "\n";
  myfile<<Latex_output.GetInclude_figure(Figure_1_page_number, pdf_name_CV)<< "\n";
  myfile<<"& \n";
  myfile<<Latex_output.Get_hSpace("-1cm")<< "\n";
  myfile<<Latex_output.GetInclude_figure(Figure_2_page_number, pdf_name_CV )<< "\n";
  myfile<<"& \n";
  myfile<<Latex_output.Get_hSpace("-1cm")<< "\n";
  myfile<<Latex_output.GetInclude_figure(Figure_3_page_number, pdf_name_CV)<< "\n";
  myfile<<Latex_output.GetEndTabular()<< "\n";
  myfile<<Latex_output.GetEndFrame();

  myfile<<"\n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<"%%% END FRAME  \n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";

  myfile.close();


}// end of function



void AppendtoLatex(std::string output_name ,  std::string pdf_name_CV, int Figure_1_page_number, int Figure_2_page_number,
  int Figure_3_page_number,int Figure_4_page_number, int Figure_5_page_number, int Figure_6_page_number, char *slideTitle){
  double scale= .24;
  std::ofstream myfile;
  std::string fileName = output_name + ".txt";
  myfile.open(fileName, std::ios_base::app);
  std::cout<<"Adding to Latex File "<< fileName<<std::endl;
  LatexFormat Latex_output(scale);
  myfile<<"\n";
  myfile<<"\n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<"%%%  Start   "<< slideTitle<<" \n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<Latex_output.GetBeginFrame(slideTitle)<< "\n";
  myfile<<Latex_output.GetBeginTabular()<< "\n";
  myfile<<Latex_output.GetInclude_figure(Figure_1_page_number, pdf_name_CV)<< "\n";
  myfile<<"& \n";
  myfile<<Latex_output.GetInclude_figure(Figure_2_page_number, pdf_name_CV )<< "\n";
  myfile<<"& \n";
  myfile<<Latex_output.GetInclude_figure(Figure_3_page_number, pdf_name_CV)<< "\n";
  myfile<<Latex_output.Get_vSpace("-.28cm")<< "\n";
  myfile<<"\\\\ \n";
  myfile<<Latex_output.GetInclude_figure(Figure_4_page_number, pdf_name_CV)<< "\n";
  myfile<<"& \n";
  myfile<<Latex_output.GetInclude_figure(Figure_5_page_number, pdf_name_CV )<< "\n";
  myfile<<"& \n";
  myfile<<Latex_output.GetInclude_figure(Figure_6_page_number, pdf_name_CV)<< "\n";
  myfile<<Latex_output.GetEndTabular()<< "\n";
  myfile<<Latex_output.GetEndFrame();

  myfile<<"\n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<"%%% END FRAME  \n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";

  myfile.close();


}// end of function




void Make_Resolution_vertex_Latex(std::string output_name ,  std::string pdf_name_CV, std::vector<double>FiducialBins,
   int startingPage_figureLeft, int startingPage_figureCenter, int startingPage_figureRight,char *Resolution_type){

     int Figure1Page = startingPage_figureLeft;
     int Figure2Page = startingPage_figureCenter;
     int Figure3Page = startingPage_figureRight;
     char SlideTitle[1024];


     for(auto Bin : FiducialBins){

       sprintf(SlideTitle, "%s Fiducial Cut = %.1f [mm]", Resolution_type, Bin);

       AppendtoText_Resolution(output_name ,  pdf_name_CV, Figure1Page, Figure2Page,
         Figure3Page, SlideTitle, Bin);

         Figure1Page++;
         Figure2Page++;
         Figure3Page++;
       }

     }





void MakeLatex_TruthTable_TGraphs( TFile *inputFile_TRUTH, const char* TGraphName_TRUTH,const char* Latex_title, const char* Playlistname ){

  TGraph *TGraph_TRUTH_CUTS = (TGraph*)inputFile_TRUTH -> Get(TGraphName_TRUTH);

  TRUE_Cut_Map TRUTH_CutMap;

  //Get_Truth
  FillTRUTH_CutMap_FromTGraph(TGraph_TRUTH_CUTS , TRUTH_CutMap);


  double TotalStart = TRUTH_CutMap[kTRUTHNoCuts];
  double TotalStart_counter = TRUTH_CutMap[kTRUTHNoCuts];

  std::map<ECutsTRUTH, double>::iterator TRUTH_it;

  char Title[1024];
  sprintf(Title, "Latex_Truth_Table_%s.txt", Playlistname );

  std::ostringstream output_string;
  output_string.precision(4);
  output_string<<std::fixed;

  //output_string << "\\resizebox{\\textwidth}{!}{" << "\n";
  output_string << "\\begin{table}[h]" << "\n";
  output_string <<"\\adjustbox{max height=\\dimexpr\\textheight-4.5cm\\relax,max width=\\textwidth}{"<< "\n";
  output_string << "\\begin{tabular}{||l|l|l|l|l||} \n";
  output_string << "\\hline \n";
  output_string << "\\hline \n";
  output_string << " Cut Name (Playlist " <<  Playlistname <<  " ) &  NEvents & Loss & \\% loss & Prev \\% loss \\\\" << "\n";
  output_string << "\\hline \n";

  for (TRUTH_it = TRUTH_CutMap.begin() ; TRUTH_it != TRUTH_CutMap.end(); TRUTH_it++)
  {
    output_string << GetCutNameLatexTRUTH(TRUTH_it->first) << " & "<<  TRUTH_it->second <<
    " & " << TotalStart_counter - TRUTH_it->second <<
    " & " << (TRUTH_it->second / TotalStart) * 100  <<
    " & " << 100*((TotalStart_counter - TRUTH_it->second) / TotalStart_counter)  <<" \\\\" << "\n";
    TotalStart_counter= TRUTH_it->second;
    output_string << "\\hline \n";


  }
  output_string << "\\hline \n";
  output_string << "\\end{tabular}} \n";
  output_string << "\\end{table} \n";

  std::ofstream myfile;
  myfile.open(Title);
  myfile<<output_string.str();
  myfile.close();
}//end of functio

//////////////////////////////////////////////////////////////////////////////
  //  ________________________________________________________________________________________
  // |                                                                                        |
  // |    COUT STATEMENTS TO DETERMINE EFFICIENCIES AND PURITIES                              |
  // |                                                                                        |
  // |             # He events pass cuts                           # He events pass cuts      |
  // |Efficiency = ----------------------        &        Purity = ------------------------   |
  // |             # He events (total) TRUTH                      # total events pass cuts   |
  // |________________________________________________________________________________________|
  //                                                              ____________________________


void MakeLatex_CutEfficiency_PurityTable_TGraphs(TFile *inputFile_RECO, const char* TGraphName_RECO, const char* TGraphName_TrueHelium_RECO, TFile *inputFile_TRUTH, const char* TGraphName_TRUTH,const char* Latex_title, const char* Playlistname ){

  TGraph *TGraph_RECO_CUTS = (TGraph*)inputFile_RECO -> Get(TGraphName_RECO);
  TGraph *TGraph_RECO_CUTS_isTrue_helium = (TGraph*)inputFile_RECO -> Get(TGraphName_TrueHelium_RECO);
  TGraph *TGraph_TRUTH_CUTS = (TGraph*)inputFile_TRUTH -> Get(TGraphName_TRUTH);

  RECO_Cut_Map RECO_CutMap;
  RECO_Cut_Map RECO_isHeliumCutMap;
  TRUE_Cut_Map TRUTH_CutMap;
  //Fill Map with NEvents
  FillRECO_CutMap_FromTGraph(TGraph_RECO_CUTS , RECO_CutMap);
  FillRECO_CutMap_FromTGraph(TGraph_RECO_CUTS_isTrue_helium , RECO_isHeliumCutMap);
  //Get_Truth
  FillTRUTH_CutMap_FromTGraph(TGraph_TRUTH_CUTS , TRUTH_CutMap);


  //std::assert( RECO_CutMap.size() == RECO_isHeliumCutMap.size()  );// && "Got Different Size Maps From inputs of RECO and RECO  Helium - Something is WRONG !!"
if(RECO_CutMap.size() != RECO_isHeliumCutMap.size()){
  std::cout<<"Input Maps are differnet sizses Someting is wrong: inside MakeLatex_CutEfficiency_PurityTable_TGraphs - Killing !!"<<std::endl;
  abort();}

// what to sort the Maps




  double Total_Truth_NEvents = TRUTH_CutMap[kAllTRUTHCuts];
  std::cout<< " Total_Truth_NEvents = " << Total_Truth_NEvents<<std::endl;
  double TotalStart = RECO_CutMap[kNoCuts];
  double TotalStart_counter = RECO_CutMap[kNoCuts];

  std::map<ECuts, double>::iterator Reco_it;
  std::map<ECuts, double>::iterator RecoHelium_it;

  char Title[1024];
  sprintf(Title, "LatexEff_Table_%s.txt", Playlistname );

  std::ostringstream output_string;
  output_string.precision(4);
  output_string<<std::fixed;

  //output_string << "\\resizebox{\\textwidth}{!}{" << "\n";
  output_string << "\\begin{table}[h]" << "\n";
  output_string <<"\\adjustbox{max height=\\dimexpr\\textheight-4.5cm\\relax,max width=\\textwidth}{"<< "\n";
  output_string << "\\begin{tabular}{||l|l|l|l|l|l|l|} \n";
  output_string << "\\hline \n";
  output_string << "\\hline \n";
  output_string << " Cut Name (Playlist " <<  Playlistname <<  " ) &  NEvents & Loss & \\% loss & Prev \\% loss & Eff & Purity \\\\" << "\n";
  output_string << "\\hline \n";

  for (Reco_it = RECO_CutMap.begin(), RecoHelium_it = RECO_isHeliumCutMap.begin() ; Reco_it != RECO_CutMap.end(); Reco_it++, RecoHelium_it++)
  {
    output_string << GetCutNameforLatex(Reco_it->first) << " & "<<  Reco_it->second <<
    " & " << TotalStart_counter - Reco_it->second <<
    " & " << (Reco_it->second / TotalStart) * 100  <<
    " & " << 100*((TotalStart_counter - Reco_it->second) / TotalStart_counter)  <<
    " & " << Reco_it->second / Total_Truth_NEvents << // Eff
    " & " << RecoHelium_it->second / Reco_it->second << " \\\\" << "\n"; // Purity

    TotalStart_counter= Reco_it->second;
    output_string << "\\hline \n";


  }
  output_string << "\\hline \n";
  output_string << "\\end{tabular}} \n";
  output_string << "\\end{table} \n";

  std::ofstream myfile;
  myfile.open(Title);
  myfile<<output_string.str();
  myfile.close();
}//end of function


void MakeLatex_WithData_CutTable_TGraphs(TFile *inputFile_Data, const char* TGraphName_Data ,TFile *inputFile_RECO, const char* TGraphName_RECO, double POTscale ,const char* Latex_title, const char* Playlistname ){

  TGraph *TGraph_RECO_CUTS = (TGraph*)inputFile_RECO -> Get(TGraphName_RECO);
  TGraph *TGraph_Data_CUTS = (TGraph*)inputFile_Data -> Get(TGraphName_Data);

  RECO_Cut_Map RECO_CutMap;
  RECO_Cut_Map Data_CutMap;

  //Fill Map with NEvents
  FillRECO_CutMap_FromTGraph(TGraph_RECO_CUTS , RECO_CutMap);
  FillRECO_CutMap_FromTGraph(TGraph_Data_CUTS , Data_CutMap);
  ScaleCutMap( RECO_CutMap , POTscale);

  //std::assert( RECO_CutMap.size() == RECO_isHeliumCutMap.size()  );// && "Got Different Size Maps From inputs of RECO and RECO  Helium - Something is WRONG !!"
//if(RECO_CutMap.size() != Data_CutMap.size()){
//  std::cout<<"Input Maps are differnet sizses Someting is wrong: inside MakeLatex_CutEfficiency_PurityTable_TGraphs - Killing !!"<<std::endl;
//  abort();}

// what to sort the Maps

  double TotalStart = RECO_CutMap[kNoCuts];
  double TotalStart_counter = RECO_CutMap[kNoCuts];

  double TotalStart_DATA = Data_CutMap[kNoCuts];
  double TotalStart_DATA_counter = Data_CutMap[kNoCuts];


  std::map<ECuts, double>::iterator Reco_it;
  std::map<ECuts, double>::iterator RecoData_it;

  char Title[1024];
  sprintf(Title, "LatexMC_Data_Table_%s.txt", Playlistname );

  std::ostringstream output_string;
  output_string.precision(3);
  output_string<<std::fixed;
  output_string << "\\begin{table}[]" << "\n";
  output_string <<"\\adjustbox{max height=\\dimexpr\\textheight-4.5cm\\relax, max width=\\textwidth}{"<< "\n";
  //output_string << "\\resizebox{\\textwidth}{!}{" << "\n";
  output_string << "\\begin{tabular}{||l|l|l|l|l||l|l|l|l|} \n";
  output_string << "\\hline \n";
  output_string << "\\hline \n";
  output_string << " Cut Name (Playlist " <<  Playlistname <<  " )& NEvents(Data) & Loss(Data)&  \\% loss (Data) & Pre \\% loss (Data) &  NEvents(MC) & Loss(MC) &  \\% loss (MC) & Pre \\% loss (MC)  \\\\" << "\n";
  output_string << "\\hline \n";

  for (Reco_it = RECO_CutMap.begin(), RecoData_it = Data_CutMap.begin() ; Reco_it != RECO_CutMap.end(); Reco_it++, RecoData_it++)
  {
    if(Reco_it->first != RecoData_it->first){
      std::cout<<"Input Maps have different Cuts being applied - Killed !!"<<std::endl;
        abort();
    }
    output_string << GetCutNameforLatex(Reco_it->first) <<

    " & "<<  RecoData_it->second <<
    " & " << TotalStart_DATA_counter - RecoData_it->second <<
    " & " << (RecoData_it->second / TotalStart_DATA) * 100  <<
    " & " << 100*((TotalStart_DATA_counter - RecoData_it->second) / TotalStart_DATA_counter) <<
    " & "<<  Reco_it->second <<
    " & " << TotalStart_counter - Reco_it->second <<
    " & " << (Reco_it->second / TotalStart) * 100  <<
    " & " << 100*((TotalStart_counter - Reco_it->second) / TotalStart_counter)  << " \\\\" << "\n"; // Purity

    TotalStart_counter= Reco_it->second;
    TotalStart_DATA_counter= RecoData_it->second;
    output_string << "\\hline \n";


  }
  output_string << "\\hline \n";
  output_string << "\\end{tabular}} \n";
  output_string << "\\end{table} \n";

  std::ofstream myfile;
  myfile.open(Title);
  myfile<<output_string.str();
  myfile.close();
}//end of function







/////////////////////////////////////////////
//Main Function
/////////////////////////////////////////////

 int main() {

bool cutsOn;
std::cout << "Run over cutsOn?  (0 = false, 1 = true) " << std::endl;
//std::cin >> cutsOn;
cutsOn = true;
std::cout << std::boolalpha << cutsOn << std::endl;

bool my_norm;
std::cout << "Which Normalization?  (0 = POT, 1 = relative equal areas) " << std::endl;
//std::cin >> my_norm;
my_norm = true;
std::cout << std::boolalpha << my_norm << std::endl;

bool my_debug;
std::cout << "Run in Debug Mode? (0 = NO, 1 = YES) " << std::endl;
//std::cin >> my_debug;
my_debug = false;
std::cout << std::boolalpha << my_debug << std::endl;

std::string input = "cnguyen";
std::cout << "What is the name of the user? " << std::endl;
//std::cin >> input;

std::cout << input << std::endl;

const char *inputFileLoc = input.c_str();

Kin(cutsOn, my_norm, my_debug, inputFileLoc);

return 0;

}



std::vector<ME_helium_Playlists> GetPlayListVector_MC() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ME_helium_Playlists> Playlist;
  Playlist.push_back(kME1F);
  Playlist.push_back(kME1G);
  //Playlist.push_back(kME1D);

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
  CryoVertexVars.push_back(kRR);
  CryoVertexVars.push_back(kdistance_edge);

  return CryoVertexVars;
//#endif
}


std::vector<SecondTrkVar> Get2ndTrkVaribles() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<SecondTrkVar> Vector_Vars;

  Vector_Vars.push_back(ksecE);
  Vector_Vars.push_back(kThetamid);
  Vector_Vars.push_back(kOpenAngle);
  Vector_Vars.push_back(kPathway);
  Vector_Vars.push_back(kDOCA);


  return Vector_Vars;
//#endif
}


std::vector<MuonVar> GetMUONVaribles() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<MuonVar> MuonVars;

  MuonVars.push_back(kE);
  //MuonVars.push_back(kP_Z);
  //MuonVars.push_back(kP_T);
  //MuonVars.push_back(kAngleWRTB);
  //MuonVars.push_back(kDOCA_muon); there is no true Muon DOCA


  return MuonVars;
//#endif
}
///////////////////////////////////////////////
// Fiducical Cut
/////////////////////////////////////////////
void Draw_Efficiency_FidiucialCut_FULL_EMPTY_TRUTH(PlayList_INFO FULL_playlist_nom, PlayList_INFO FULL_playlist_TRUTHDEM,
                                                   PlayList_INFO EMPTY_playlist_nom, PlayList_INFO EMPTY_playlist_TRUTHDEM ,
                                                   PlayList_INFO playlist_FULL_Data, PlayList_INFO playlist_EMPTY_Data,
                                                   const char *histoName_MC, const char *histoName_Data,
                                                   const char* title, std::string Xaxis_title, MnvPlotter *plot, bool doBinwidth,
                                                   TCanvas *can,  char *pdf, bool PrintErrors, bool PrintallErrorBands , std::vector<double> Bins , double EffMax ){

  char histoName_TRUE[1024];
  char histoName_TRUE_RECO[1024];
  char histoName_RECO_helium[1024];
  char histoName_RECO_nonhelium[1024];
  char Title_His[1024];
  char pdf_char[1024];
  sprintf(pdf_char, "%s.pdf", pdf);


  double FULL_POT = FULL_playlist_nom.Get_Pot();
  double EMPTY_POT = EMPTY_playlist_nom.Get_Pot();
  double Scale_MC = FULL_POT / EMPTY_POT;

  double FULL_POT_data = playlist_FULL_Data.Get_Pot();
  double EMPTY_POT_data = playlist_EMPTY_Data.Get_Pot();
  double Scale_data = FULL_POT_data / EMPTY_POT_data;

  double Scale_FULL_MC_data = FULL_POT_data / FULL_POT;
  double Scale_Empty_MC_data = FULL_POT_data / EMPTY_POT;


  sprintf(histoName_TRUE, "%s_TRUE", histoName_MC);
  sprintf(histoName_TRUE_RECO, "%s_TRUE_RECO", histoName_MC);

  sprintf(histoName_RECO_helium, "%s_helium", histoName_MC);
  sprintf(histoName_RECO_nonhelium, "%s_nonhelium", histoName_MC);
  bool isfull=true;
  bool isempty=false;

  MnvH1D* hist_TRUE_FULL = Get1DHist(*FULL_playlist_TRUTHDEM.TFILE_PLAYLIST, histoName_TRUE, isfull);//(MnvH1D*)FULL_playlist_nom.TFILE_PLAYLIST -> Get(histoName_nom);
  MnvH1D* hist_TRUE_RECO_FULL = Get1DHist(*FULL_playlist_nom.TFILE_PLAYLIST, histoName_TRUE_RECO, isfull);//(MnvH1D*)FULL_playlist_nom.TFILE_PLAYLIST -> Get(histoName_nom);
  MnvH1D* hist_RECO_FULL = Get1DHist(*FULL_playlist_nom.TFILE_PLAYLIST, histoName_MC, isfull);//(MnvH1D*)FULL_playlist_nom.TFILE_PLAYLIST -> Get(histoName_nom);

  MnvH1D* hist_RECO_FULL_Total = Get1DHist(*FULL_playlist_nom.TFILE_PLAYLIST, histoName_MC, isfull);//(MnvH1D*)FULL_playlist_nom.TFILE_PLAYLIST -> Get(histoName_nom);
  MnvH1D* hist_RECO_FULL_helium = Get1DHist(*FULL_playlist_nom.TFILE_PLAYLIST, histoName_RECO_helium, isfull);//(MnvH1D*)FULL_playlist_nom.TFILE_PLAYLIST -> Get(histoName_nom);
  MnvH1D* hist_RECO_FULL_nonhelium = Get1DHist(*FULL_playlist_nom.TFILE_PLAYLIST, histoName_RECO_nonhelium, isfull);//(MnvH1D*)FULL_playlist_nom.TFILE_PLAYLIST -> Get(histoName_nom);
  MnvH1D *Purity_Dom_Full = (PlotUtils::MnvH1D*)hist_RECO_FULL_Total->Clone("Purity_Dom_Full");
  MnvH1D *Purity_Dom_Full_EMPTY = (PlotUtils::MnvH1D*)hist_RECO_FULL_Total->Clone("Purity_Dom_Full_EMPTY");

  hist_RECO_FULL_Total->Scale(Scale_FULL_MC_data);
  hist_RECO_FULL_helium->Scale(Scale_FULL_MC_data);
  hist_RECO_FULL_nonhelium->Scale(Scale_FULL_MC_data);

  MnvH1D* hist_RECO_EMPTY_Total = Get1DHist(*EMPTY_playlist_nom.TFILE_PLAYLIST, histoName_MC, isfull);//(MnvH1D*)FULL_playlist_nom.TFILE_PLAYLIST -> Get(histoName_nom);
  MnvH1D* hist_RECO_EMPTY_helium = Get1DHist(*EMPTY_playlist_nom.TFILE_PLAYLIST, histoName_RECO_helium, isfull);//(MnvH1D*)FULL_playlist_nom.TFILE_PLAYLIST -> Get(histoName_nom);
  MnvH1D* hist_RECO_EMPTY_nonhelium = Get1DHist(*EMPTY_playlist_nom.TFILE_PLAYLIST, histoName_RECO_nonhelium, isfull);//(MnvH1D*)FULL_playlist_nom.TFILE_PLAYLIST -> Get(histoName_nom);
  MnvH1D *Purity_Dom_Empty = (PlotUtils::MnvH1D*)hist_RECO_EMPTY_Total->Clone("Purity_Dom_Empty");
  MnvH1D *Purity_Dom_Empty_clone = (PlotUtils::MnvH1D*)hist_RECO_EMPTY_Total->Clone("Purity_Dom_Empty_clone");

  Purity_Dom_Empty->Scale(Scale_MC);
  Purity_Dom_Empty_clone->Scale(Scale_MC);

  hist_RECO_EMPTY_Total->Scale(Scale_Empty_MC_data);
  hist_RECO_EMPTY_helium->Scale(Scale_Empty_MC_data);
  hist_RECO_EMPTY_nonhelium->Scale(Scale_Empty_MC_data);



  MnvH1D* Purity_Full = Get1DHist(*FULL_playlist_nom.TFILE_PLAYLIST, histoName_RECO_helium, isfull);//(MnvH1D*)FULL_playlist_nom.TFILE_PLAYLIST -> Get(histoName_nom);
  MnvH1D* Purity_Empty = Get1DHist(*EMPTY_playlist_nom.TFILE_PLAYLIST, histoName_RECO_helium, isempty);//(MnvH1D*)FULL_playlist_nom.TFILE_PLAYLIST -> Get(histoName_nom);
  MnvH1D* Purity_Full_Empty = Get1DHist(*FULL_playlist_nom.TFILE_PLAYLIST, histoName_RECO_helium, isfull);//(MnvH1D*)FULL_playlist_nom.TFILE_PLAYLIST -> Get(histoName_nom);
  MnvH1D *Purity_Empty_clone = (PlotUtils::MnvH1D*)Purity_Empty->Clone("Purity_Empty_clone");

  Purity_Empty->Scale(Scale_MC);
  Purity_Empty_clone->Scale(Scale_MC);

  hist_TRUE_FULL->AddMissingErrorBandsAndFillWithCV(*hist_TRUE_RECO_FULL);

  MnvH1D* hist_TRUE_EMPTY = Get1DHist(*EMPTY_playlist_TRUTHDEM.TFILE_PLAYLIST, histoName_TRUE, isempty);//(MnvH1D*)FULL_playlist_nom.TFILE_PLAYLIST -> Get(histoName_nom);
  MnvH1D* hist_TRUE_RECO_EMPTY = Get1DHist(*EMPTY_playlist_nom.TFILE_PLAYLIST, histoName_TRUE_RECO, isempty);//(MnvH1D*)FULL_playlist_nom.TFILE_PLAYLIST -> Get(histoName_nom);
  MnvH1D* hist_RECO_EMPTY = Get1DHist(*EMPTY_playlist_nom.TFILE_PLAYLIST, histoName_MC, isempty);//(MnvH1D*)FULL_playlist_nom.TFILE_PLAYLIST -> Get(histoName_nom);

  hist_TRUE_EMPTY->AddMissingErrorBandsAndFillWithCV(*hist_TRUE_RECO_EMPTY);

  MnvH1D* hist_TRUE_FULL_clone = Get1DHist(*FULL_playlist_TRUTHDEM.TFILE_PLAYLIST, histoName_TRUE, isfull);//(MnvH1D*)FULL_playlist_nom.TFILE_PLAYLIST -> Get(histoName_nom);
  MnvH1D* hist_TRUE_RECO_FULL_clone = Get1DHist(*FULL_playlist_nom.TFILE_PLAYLIST, histoName_TRUE_RECO, isfull);//(MnvH1D*)FULL_playlist_nom.TFILE_PLAYLIST -> Get(histoName_nom);
  MnvH1D* hist_RECO_FULL_clone = Get1DHist(*FULL_playlist_nom.TFILE_PLAYLIST, histoName_MC, isfull);//(MnvH1D*)FULL_playlist_nom.TFILE_PLAYLIST -> Get(histoName_nom);

  hist_TRUE_FULL_clone->AddMissingErrorBandsAndFillWithCV(*hist_TRUE_RECO_FULL_clone);

  MnvH1D* hist_TRUE_EMPTY_clone = Get1DHist(*EMPTY_playlist_TRUTHDEM.TFILE_PLAYLIST, histoName_TRUE, isempty);//(MnvH1D*)FULL_playlist_nom.TFILE_PLAYLIST -> Get(histoName_nom);
  MnvH1D* hist_TRUE_RECO_EMPTY_clone = Get1DHist(*EMPTY_playlist_nom.TFILE_PLAYLIST, histoName_TRUE_RECO, isempty);//(MnvH1D*)FULL_playlist_nom.TFILE_PLAYLIST -> Get(histoName_nom);
  MnvH1D* hist_RECO_EMPTY_clone = Get1DHist(*EMPTY_playlist_nom.TFILE_PLAYLIST, histoName_MC, isempty);//(MnvH1D*)FULL_playlist_nom.TFILE_PLAYLIST -> Get(histoName_nom);

  hist_TRUE_EMPTY_clone->AddMissingErrorBandsAndFillWithCV(*hist_TRUE_RECO_EMPTY_clone);

  MnvH1D* hist_FULL_data = Get1DHist(*playlist_FULL_Data.TFILE_PLAYLIST, histoName_Data, isfull);//(MnvH1D*)FULL_playlist_nom.TFILE_PLAYLIST -> Get(histoName_nom);
  MnvH1D* hist_EMPTY_data = Get1DHist(*playlist_EMPTY_Data.TFILE_PLAYLIST, histoName_Data, isempty);//(MnvH1D*)FULL_playlist_nom.TFILE_PLAYLIST -> Get(histoName_nom);

  double Ymax_reco = 1.15 * hist_FULL_data->GetMaximum();

  MnvH1D* hist_FULL_data_clone = Get1DHist(*playlist_FULL_Data.TFILE_PLAYLIST, histoName_Data, isfull);//(MnvH1D*)FULL_playlist_nom.TFILE_PLAYLIST -> Get(histoName_nom);
  MnvH1D* hist_EMPTY_data_clone = Get1DHist(*playlist_EMPTY_Data.TFILE_PLAYLIST, histoName_Data, isempty);//(MnvH1D*)FULL_playlist_nom.TFILE_PLAYLIST -> Get(histoName_nom);

  ///Calculation FOR FINAL Eff
  hist_TRUE_EMPTY_clone->Scale(Scale_MC);
  hist_TRUE_RECO_EMPTY_clone->Scale(Scale_MC);


  // Data
  hist_EMPTY_data_clone->Scale(Scale_data);
  hist_EMPTY_data->Scale(Scale_data);


  hist_TRUE_FULL_clone->Add(hist_TRUE_EMPTY_clone,-1);
  hist_TRUE_RECO_FULL_clone->Add(hist_TRUE_RECO_EMPTY_clone,-1);

  hist_RECO_EMPTY_clone->Scale(Scale_Empty_MC_data);
  hist_RECO_FULL_clone->Scale(Scale_FULL_MC_data);
  hist_RECO_FULL_clone->Add(hist_RECO_EMPTY_clone,-1);

  //Data

  hist_FULL_data_clone->Add(hist_EMPTY_data_clone,-1);


  std::string title_type = "Fiducial Cut";

  //std::string Xaxis_title = "Fiducial Cut Distance to Cryotank Edge [mm]";

  double binwidth_title = hist_FULL_data -> GetBinWidth(4);
  char ytitle[1024];



  if(doBinwidth==true){
    sprintf(ytitle, "Number of Events / %.2f [mm]", binwidth_title); //
  }
  else{    sprintf(ytitle, "Number of Events"); //
}

  std::string Yaxis_title(ytitle);

  auto FULL_name = FULL_playlist_nom.GetPlaylist();
  auto Empty_name = EMPTY_playlist_nom.GetPlaylist();

  std::string playlistFull =   GetPlaylist_InitialName(FULL_name); //FULL_playlist.GetPlaylistName();
  std::string playlistEmpty = GetPlaylist_InitialName(Empty_name); //EMPTY_playlist.GetPlaylistName();


  char title_type_char[title_type.length()+1];
  strcpy( title_type_char, title_type.c_str());

  char playlistFull_char[playlistFull.length()+1];
  strcpy( playlistFull_char, playlistFull.c_str());

  char playlistEmpty_char[ playlistEmpty.length()+1];
  strcpy( playlistEmpty_char,  playlistEmpty.c_str());

  std::string pdf_string(pdf);

  hist_RECO_FULL->Scale(Scale_FULL_MC_data);
  sprintf(Title_His, "Fiducial Cut Event Rate [F(%s)]",playlistFull_char);
  DrawCVAndError_FromHistPointer(hist_RECO_FULL , hist_FULL_data, Title_His ,Xaxis_title, Yaxis_title,
    pdf_string, doBinwidth, false , PrintErrors, Ymax_reco, PrintallErrorBands );

  hist_RECO_EMPTY->Scale(Scale_Empty_MC_data);
  Ymax_reco = .6* Ymax_reco;
  sprintf(Title_His, "Fiducial Cut Event Rate [E(%s)]",playlistEmpty_char);
  DrawCVAndError_FromHistPointer(hist_RECO_EMPTY , hist_EMPTY_data, Title_His ,Xaxis_title, Yaxis_title,
  pdf_string, doBinwidth, false , PrintErrors, Ymax_reco, PrintallErrorBands );



sprintf(Title_His, "Fiducial Cut Event Rate [F(%s)- E(%s)]", playlistFull_char, playlistEmpty_char);
DrawCVAndError_FromHistPointer(hist_RECO_FULL_clone, hist_FULL_data_clone, Title_His ,Xaxis_title, Yaxis_title,
    pdf_string, doBinwidth, false , PrintErrors, Ymax_reco, PrintallErrorBands );
///////////////////////////////////////////////////////////////////////////////
sprintf(Title_His, "Fiducial Cut Event Rate [F(%s)]",playlistFull_char);
Ymax_reco = hist_RECO_FULL_Total->GetMaximum();
DrawCVAndError_From2HIST(hist_RECO_FULL_Total, hist_RECO_FULL_helium , hist_RECO_FULL_nonhelium ,
  Title_His ,Xaxis_title,Yaxis_title,
  pdf_string, false , PrintallErrorBands , false , doBinwidth, Ymax_reco );

Ymax_reco = hist_TRUE_FULL->GetMaximum();
sprintf(Title_His, "Numerator and Denominator [F(%s)]",playlistFull_char);
DrawCVAndError_From2HIST(hist_TRUE_FULL, "Denominator" ,hist_TRUE_RECO_FULL, "Numerator",  Title_His , Xaxis_title, "Nevents",
pdf_string, true,  PrintallErrorBands , false , doBinwidth, Ymax_reco );
////////////////////

sprintf(Title_His, "Fiducial Cut Event Rate [E(%s)]",playlistEmpty_char);
DrawCVAndError_From2HIST(hist_RECO_EMPTY_Total, hist_RECO_EMPTY_helium , hist_RECO_EMPTY_nonhelium,
                                Title_His ,Xaxis_title,Yaxis_title,
 pdf_string, false , PrintallErrorBands , false , doBinwidth, Ymax_reco );

sprintf(Title_His, "Numerator and Denominator [E(%s)]", playlistEmpty_char);
DrawCVAndError_From2HIST(hist_TRUE_EMPTY, "Denominator" ,hist_TRUE_RECO_EMPTY, "Numerator",  Title_His , Xaxis_title, "Nevents",
pdf_string, true,  PrintallErrorBands , false , doBinwidth, Ymax_reco );
//////////////////////////
hist_RECO_FULL_Total->Add(hist_RECO_EMPTY_Total,-1.0);
hist_RECO_FULL_helium->Add(hist_RECO_EMPTY_helium,-1.0);
hist_RECO_FULL_nonhelium->Add(hist_RECO_EMPTY_nonhelium,-1.0);

sprintf(Title_His, "Fiducial Cut Event Rate [F(%s)- E(%s)]", playlistFull_char, playlistEmpty_char);
DrawCVAndError_From2HIST(hist_RECO_FULL_Total, hist_RECO_FULL_helium, hist_RECO_FULL_nonhelium,
                                Title_His ,Xaxis_title, Yaxis_title,
 pdf_string, false , PrintallErrorBands , false , doBinwidth, Ymax_reco );

sprintf(Title_His, "Numerator and Denominator [F(%s)- E(%s)]", playlistFull_char, playlistEmpty_char);
DrawCVAndError_From2HIST(hist_TRUE_FULL_clone, "Denominator" ,hist_TRUE_RECO_FULL_clone, "Numerator",  Title_His , Xaxis_title, "Nevents",
pdf_string, true,  PrintallErrorBands , false , doBinwidth, Ymax_reco );
///////////////////////////////
hist_TRUE_RECO_FULL->Divide(hist_TRUE_RECO_FULL, hist_TRUE_FULL, 1.0,1.0,""); // cl=0.683 b(1,1) mode , this is suppose to be the bayesdividion but didnn't work , if using biomional error if universe are equal then dividion cancels them to equal  zero
hist_TRUE_RECO_EMPTY->Divide(hist_TRUE_RECO_EMPTY, hist_TRUE_EMPTY, 1.0,1.0,"");
hist_TRUE_RECO_FULL_clone->Divide(hist_TRUE_RECO_FULL_clone, hist_TRUE_FULL_clone, 1.0,1.0,"");
bool SetYAxis = true;
double yMax = EffMax;
double yMin = .05;
sprintf(Title_His, "Efficiency %s [F(%s)] ", title_type_char, playlistFull_char);
DrawCVAndError_FromHIST(PrintallErrorBands,hist_TRUE_RECO_FULL, Title_His ,Xaxis_title,"Efficiency", pdf,true, doBinwidth, SetYAxis,yMax, yMin );
sprintf(Title_His, "Efficiency  %s [E(%s)]", title_type_char, playlistEmpty_char);
DrawCVAndError_FromHIST(PrintallErrorBands,hist_TRUE_RECO_EMPTY, Title_His ,Xaxis_title,"Efficiency", pdf,true, doBinwidth, SetYAxis,yMax, yMin );
sprintf(Title_His, "Efficiency %s [F(%s)- E(%s)]", title_type_char, playlistFull_char,playlistEmpty_char);
DrawCVAndError_FromHIST(PrintallErrorBands, hist_TRUE_RECO_FULL_clone, Title_His ,Xaxis_title,"Efficiency", pdf, true, doBinwidth, SetYAxis,yMax, yMin );


sprintf(Title_His, "Purity %s [F(%s)] ", title_type_char, playlistFull_char);
Purity_Full->Divide(Purity_Full, Purity_Dom_Full ,  1.0,1.0,"");
DrawCVAndError_FromHIST(PrintallErrorBands, Purity_Full, Title_His ,Xaxis_title, "Purity", pdf,true, doBinwidth);
sprintf(Title_His, "Purity %s [E(%s)]", title_type_char,playlistEmpty_char);
Purity_Empty->Divide(Purity_Empty, Purity_Dom_Empty ,  1.0,1.0,"");
DrawCVAndError_FromHIST(PrintallErrorBands, Purity_Empty, Title_His ,Xaxis_title, "Purity", pdf,true, doBinwidth);

sprintf(Title_His, "Purity %s [F(%s)- E(%s)]", title_type_char, playlistFull_char, playlistEmpty_char);
Purity_Full_Empty->Add(Purity_Empty_clone,-1.0);
Purity_Dom_Full_EMPTY->Add(Purity_Dom_Empty_clone,-1.0);
Purity_Full_Empty->Divide(Purity_Full_Empty, Purity_Dom_Full_EMPTY ,  1.0,1.0,"");

DrawCVAndError_FromHIST(PrintallErrorBands, Purity_Full_Empty, Title_His ,Xaxis_title, "Purity", pdf,true, doBinwidth);

sprintf(Title_His, "Fractional uncertainty %s [F(%s)] ", title_type_char, playlistFull_char);
DrawCVAndError_eff_purity_EOM_ERROR(hist_TRUE_RECO_FULL,  Purity_Full, Title_His ,Xaxis_title,
pdf_char, doBinwidth, EffMax , Bins);

sprintf(Title_His, "Fractional uncertainty %s [E(%s)] ", title_type_char, playlistEmpty_char);
DrawCVAndError_eff_purity_EOM_ERROR(hist_TRUE_RECO_EMPTY,  Purity_Empty, Title_His ,Xaxis_title,
pdf_char, doBinwidth, .5 , Bins);

sprintf(Title_His, "Fractional uncertainty %s [F(%s)- E(%s)]", title_type_char, playlistFull_char, playlistEmpty_char);
DrawCVAndError_eff_purity_EOM_ERROR(hist_TRUE_RECO_FULL_clone,  Purity_Full_Empty, Title_His ,Xaxis_title,
pdf_char, doBinwidth, EffMax , Bins);


hist_TRUE_RECO_FULL->Multiply(hist_TRUE_RECO_FULL, Purity_Full, 1.0, 1.0);
hist_TRUE_RECO_EMPTY->Multiply(hist_TRUE_RECO_EMPTY, Purity_Empty, 1.0, 1.0);
hist_TRUE_RECO_FULL_clone->Multiply(hist_TRUE_RECO_FULL_clone, Purity_Full_Empty, 1.0, 1.0);

sprintf(Title_His, "Eff*Purity %s [F(%s)] ", title_type_char, playlistFull_char);
DrawCVAndError_FromHIST(PrintallErrorBands,hist_TRUE_RECO_FULL, Title_His ,Xaxis_title,"Eff*Purity", pdf,true, doBinwidth);
sprintf(Title_His, "Eff*Purity  %s [E(%s)]", title_type_char, playlistEmpty_char);
DrawCVAndError_FromHIST(PrintallErrorBands,hist_TRUE_RECO_EMPTY, Title_His ,Xaxis_title,"Eff*Purity", pdf,true, doBinwidth);
sprintf(Title_His, "Eff*Purity %s [F(%s)- E(%s)]", title_type_char, playlistFull_char, playlistEmpty_char);
DrawCVAndError_FromHIST(PrintallErrorBands, hist_TRUE_RECO_FULL_clone, Title_His ,Xaxis_title,"Eff*Purity", pdf,true, doBinwidth);




}//endl;B
