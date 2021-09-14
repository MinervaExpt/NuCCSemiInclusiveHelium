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

void Draw_Ratio_CryoVertex_FULL_EMPTY_RecoBranch(PlayList_INFO FULL_playlist_nom, PlayList_INFO EMPTY_playlist_nom,
  const char *histoName_nom, const char *histoName_dem, int logScale, const char* title, MnvPlotter *plot,
   TCanvas *can, const char *pdf , CryoVertex CryoVertex_type );

void Draw_Migration_2D_FULL_EMPTY_TRUTH(PlayList_INFO FULL_playlist, PlayList_INFO EMPTY_playlist,
  const char *histoName, const char *Xaxis_title, const char *Yaxis_title, const char* title,
  const char* title_type_char , MnvPlotter *plot, TCanvas *can, const char *pdf);

void MakeLatexForEffMuonVar_StatsOnly(std::string output_name ,  std::string pdf_name_CV, const std::vector<MuonVar> muon_vector);

void Appendtotxt_2ndTrk(std::string output_name ,  std::string pdf_name_CV,int First_page, int Full_empty_space, char *Var_name ,char *Units_name, std::vector<double>input_vectors);

void MakeLatex_CutEfficiency_PurityTable_TGraphs(TFile *inputFile_RECO, const char* TGraphName_RECO, const char* TGraphName_TrueHelium_RECO, TFile *inputFile_TRUTH, const char* TGraphName_TRUTH,const char* Latex_title, const char* Playlistname );

void MakeLatex_WithData_CutTable_TGraphs(TFile *inputFile_Data, const char* TGraphName_Data ,TFile *inputFile_RECO, const char* TGraphName_RECO, double POTscale ,const char* Latex_title, const char* Playlistname );

void MakeLatex_TruthTable_TGraphs( TFile *inputFile_TRUTH, const char* TGraphName_TRUTH,const char* Latex_title, const char* Playlistname );
std::vector<CryoVertex> GetCryoVertexVaribles();

std::vector<ME_helium_Playlists> GetPlayListVector_DATA();
void Kin(bool &cutsOn, bool &my_norm, bool &my_debug, const char *userDir) {
TH1::AddDirectory(false);
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~       Starting Plotter: ME Efficiency Plots         ~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::vector<ME_helium_Playlists> GetPlayListVector_MC();
const std::vector< ME_helium_Playlists> kPlayListVector_MC = GetPlayListVector_MC();
std::vector<ME_helium_Playlists> kPlayListVector_DATA = GetPlayListVector_DATA();
//const std::vector< ME_helium_Playlists> kPlayListVector_DATA = GetPlayListVector_DATA();

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

 char Resolution_title_pdf1[2024];
 char Resolution_title_pdf2[2024];
 char Resolution_title_pdf3[2024];
 char Resolution_title_pdf4[2024];
 char Resolution_title_pdf5[2024];


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



TCanvas *can2 = new TCanvas("can2");
//TCanvas *can_Mig = new TCanvas("can_Mig");
sprintf(text_title_pdf1, "PLOTS_EfficiencyTRUTH.pdf(" );
can2 -> Print(text_title_pdf1);
sprintf(text_title_pdf2, "PLOTS_EfficiencyTRUTH.pdf");
sprintf(text_title_pdf5, "PLOTS_EfficiencyTRUTH" );
sprintf(text_title_pdf3, "PLOTS_EfficiencyTRUTH.pdf)");
sprintf(text_title_pdf4, "PLOTS_EfficiencyTRUTH");

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

bool PrintAllBands_muon = true;

for(auto MuonVar : kMuonVaribles){
  auto histName = GetMuonVarHistName(MuonVar);
  int n_histName = histName.length();
  char histName_char[n_histName+1];
  strcpy( histName_char,histName.c_str());

Draw_Efficiency_Muon_FULL_EMPTY_TRUTH(Efficiency_Playlist[0],PlaylistTRUTH_1F,Efficiency_Playlist[1],
                   PlaylistTRUTH_1G, histName_char ,  0, " ", mnv_plot, can2, text_title_pdf5, MuonVar, PrintAllBands_muon );
}

MakeLatexForEffMuonVar_StatsOnly("Efficency_latex" , text_title_pdf2, kMuonVaribles);

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
MakeLatex_WithData_CutTable_TGraphs(PlaylistDATA_1F.TFILE_PLAYLIST, "RECO_Data_Cuts" ,PlaylistME_1F_TFile, "RECO_Cuts", POT_Data_MC_ME1F,"ME1F", "ME1F" );
MakeLatex_TruthTable_TGraphs( PlaylistME_1F_TRUTH_TFile, "Truth_Cuts", "ME1F", "ME1F" );


Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], PlaylistTRUTH_1F, Efficiency_Playlist[1] ,PlaylistTRUTH_1G, "h_secTrk_Energy",
  0, " ", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[0] );

Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], PlaylistTRUTH_1F, Efficiency_Playlist[1] ,PlaylistTRUTH_1G, "h_secTrk_EnergyFINEBinning",
    0, " ", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[0] );



    int start=230;
    int spacing=52;
    Appendtotxt_2ndTrk("Efficency_latex" ,  text_title_pdf5, start, 4, "secTrk Energy" ,"[GeV]", Vertex_secondTrkEbin_vector);
    start=start+spacing;

//Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], PlaylistTRUTH_1D, Efficiency_Playlist[1] ,PlaylistTRUTH_1A, "h_secTrk_Energy_PROTON",
  //  0, "Proton", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[0] );

    Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], PlaylistTRUTH_1F, Efficiency_Playlist[1] ,PlaylistTRUTH_1G, "h_secTrk_Energy_PROTON",
        0, "Proton", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[0], 0.105 /*[GeV]*/, true);

  Appendtotxt_2ndTrk("Efficency_latex" ,  text_title_pdf5, start, 4, "Leading Non-muon Trk Energy [Proton]" ,"[GeV]", Vertex_secondTrkEbin_Proton_vector);
  start=start+spacing;
//Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], PlaylistTRUTH_1D, Efficiency_Playlist[1] ,PlaylistTRUTH_1A, "h_secTrk_Energy_PION",
//      0, "Pion", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[0] );

Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], PlaylistTRUTH_1F, Efficiency_Playlist[1] ,PlaylistTRUTH_1G, "h_secTrk_Energy_PION",
0, "Pion", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[0] , 0.060 /*[GeV]*/ , true);

      Appendtotxt_2ndTrk("Efficency_latex" ,  text_title_pdf5,start, 4, "Leading Non-muon Trk Energy [#pi^{#pm}]" ,"[GeV]", Vertex_secondTrkEbin_Proton_vector);
  start=start+spacing;
//Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], PlaylistTRUTH_1D, Efficiency_Playlist[1] ,PlaylistTRUTH_1A, "h_secTrk_Energy_Dimuon",
//      0, "Dimuon", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[0] );

Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], PlaylistTRUTH_1F, Efficiency_Playlist[1] ,PlaylistTRUTH_1G, "h_secTrk_Energy_Dimuon",
            0, "Dimuon", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[0] );

Appendtotxt_2ndTrk("Efficency_latex" ,  text_title_pdf5, start, 4, "Leading Non-muon Trk Energy [Dimuon]" ,"[GeV]", Vertex_secondTrkEbin_Proton_vector);
start=start+spacing;


//Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], PlaylistTRUTH_1D, Efficiency_Playlist[1] ,PlaylistTRUTH_1A, "h_secTrk_Theta",
//0, " ", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[1] );

Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], PlaylistTRUTH_1F, Efficiency_Playlist[1] ,PlaylistTRUTH_1G, "h_secTrk_Theta",
0, " ", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[1] , 56.0 /*[Deg]*/ );

Appendtotxt_2ndTrk("Efficency_latex" ,  text_title_pdf5, start, 4, "Leading Non-muon Trk Theta wrtb" ,"[Deg]", Vertex_secondTrkThetamidbin_vector);
start=start+spacing;

//Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], PlaylistTRUTH_1D, Efficiency_Playlist[1] ,PlaylistTRUTH_1A, "h_secTrk_Theta_PROTON",
//0, "Proton", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[1] );

Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], PlaylistTRUTH_1F, Efficiency_Playlist[1] ,PlaylistTRUTH_1G, "h_secTrk_Theta_PROTON",
0, "Proton", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[1] , 60 , true  );

Appendtotxt_2ndTrk("Efficency_latex" ,  text_title_pdf5, start, 4, "Leading Non-muon Trk [Proton] Theta wrtb" ,"[Deg]", Vertex_secondTrkThetamidbin_vector);
start=start+spacing;

//Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], PlaylistTRUTH_1D, Efficiency_Playlist[1] ,PlaylistTRUTH_1A, "h_secTrk_Theta_PION",
//0, "Pion", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[1] );

Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], PlaylistTRUTH_1F, Efficiency_Playlist[1] ,PlaylistTRUTH_1G, "h_secTrk_Theta_PION",
0, "Pion", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[1], 60 , true );

Appendtotxt_2ndTrk("Efficency_latex" ,  text_title_pdf5, start, 4, "Leading Non-muon Trk [#pi^{#pm}] Theta wrtb" ,"[Deg]", Vertex_secondTrkThetamidbin_vector);
start=start+spacing;


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

Draw_Efficiency_2D_FULL_EMPTY_TRUTH(Efficiency_Playlist[0],Efficiency_Playlist_TRUTH[0], Efficiency_Playlist[1],Efficiency_Playlist_TRUTH[1],
  "h_cryoVertex_Z_secTrkTheta", "Vertex Z [mm]", "#theta_{2ndtrk} [Deg](wrtb)", "Vertex Z vs #theta_{2ndtrk}" ,"Efficency" , mnv_plot, can2, text_title_pdf2);

Draw_Efficiency_2D_FULL_EMPTY_TRUTH(Efficiency_Playlist[0],Efficiency_Playlist_TRUTH[0], Efficiency_Playlist[1],Efficiency_Playlist_TRUTH[1],
  "h_cryoVertex_R_secTrkTheta", "Vertex R [mm]", "#theta_{2ndtrk} [Deg](wrtb)", "Vertex R vs #theta_{2ndtrk}" ,"Efficency" , mnv_plot, can2, text_title_pdf2);

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


Draw_Resolution_2D_FULL_EMPTY_TRUTH(Efficiency_Playlist[0],Efficiency_Playlist[1],
  "h_resolutionZ_FidiucalCut", "Fiducial Cut Distance to Cryotank Edge [mm]", "True - Reco Vertex Z [mm]",
  "Resolution Vertex Z [mm] Vs Fiducial Cut" ,"", mnv_plot, can2, Resolution_title_pdf5, 500.0); // no pdf tag format

Draw_Resolution_2D_FULL_EMPTY_TRUTH(Efficiency_Playlist[0],Efficiency_Playlist[1],
    "h_resolutionR_FidiucalCut", "Fiducial Cut Distance to Cryotank Edge [mm]", "True - Reco Vertex R [mm]",
    "Resolution Vertex R [mm] Vs Fiducial Cut" ,"", mnv_plot, can2, Resolution_title_pdf5 , 800.0);


Draw_Resolution_2D_FULL_EMPTY_TRUTH(Efficiency_Playlist[0],Efficiency_Playlist[1],
      "h_resolutionZ_FidiucalCut", "Fiducial Cut Distance to Cryotank Edge [mm]", "True - Reco Vertex Z [mm]",
      "Resolution Vertex Z [mm] Vs Fiducial Cut" ,"", mnv_plot, can2, Resolution_title_pdf5, 500.0); // no pdf tag format

Draw_Resolution_2D_FULL_EMPTY_TRUTH(Efficiency_Playlist[0],Efficiency_Playlist[1],
        "h_resolutionR_FidiucalCut", "Fiducial Cut Distance to Cryotank Edge [mm]", "True - Reco Vertex R [mm]",
        "Resolution Vertex R [mm] Vs Fiducial Cut" ,"", mnv_plot, can2, Resolution_title_pdf5 , 800.0);


  Draw2DHist_TFILE(Efficiency_Playlist[0].TFILE_PLAYLIST, "h_resolutionZ_FidiucalCut", "Resolution Vertex Z [mm] Vs Fiducial Cut [Full ME1F]", "Fiducial Cut Distance to Cryotank Edge [mm]","True - Reco Vertex Z [mm]", text_title_pdf2, can2, mnv_plot);
  Draw2DHist_TFILE(Efficiency_Playlist[0].TFILE_PLAYLIST, "h_resolutionR_FidiucalCut", "Resolution Vertex R [mm] Vs Fiducial Cut [Full ME1F]", "Fiducial Cut Distance to Cryotank Edge [mm]","True - Reco Vertex R [mm]", text_title_pdf2, can2, mnv_plot);

Draw_Efficiency_2D_FULL_EMPTY_TRUTH(Efficiency_Playlist[0],Efficiency_Playlist_TRUTH[0], Efficiency_Playlist[1],Efficiency_Playlist_TRUTH[1],
  "h_muonPT_2ndTrkangle", "Muon P_{T} [GeV]", "#theta_{2ndtrk} [Deg](wrtb)", "Muon P_{T} vs #theta_{2ndtrk}" ,"Efficency" , mnv_plot, can2, text_title_pdf2);

Draw_Efficiency_2D_FULL_EMPTY_TRUTH(Efficiency_Playlist[0],Efficiency_Playlist_TRUTH[0], Efficiency_Playlist[1],Efficiency_Playlist_TRUTH[1],
  "h_muonPZ_2ndTrkangle", "Muon P_{Z} [GeV]", "#theta_{2ndtrk} [Deg](wrtb)", "Muon P_{Z} vs #theta_{2ndtrk}" ,"Efficency" , mnv_plot, can2, text_title_pdf2);

Draw_Efficiency_2D_FULL_EMPTY_TRUTH(Efficiency_Playlist[0],Efficiency_Playlist_TRUTH[0], Efficiency_Playlist[1],Efficiency_Playlist_TRUTH[1],
  "h_muontheta_2ndTrkangle", "#theta_{#mu} [Deg]", "#theta_{2ndtrk} [Deg](wrtb)", "#theta_{#mu} vs #theta_{2ndtrk}" ,"Efficency" , mnv_plot, can2, text_title_pdf2);

Draw_Efficiency_2D_FULL_EMPTY_TRUTH(Efficiency_Playlist[0],Efficiency_Playlist_TRUTH[0], Efficiency_Playlist[1],Efficiency_Playlist_TRUTH[1],
  "h_2ndTrkE_2ndtrkangle", "KE_{2ndTrk} [GeV]", "#theta_{2ndtrk} [Deg](wrtb)", "KE_{2ndTrk} vs #theta_{2ndtrk}" ,"Efficency" , mnv_plot, can2, text_title_pdf2);

Draw_Efficiency_2D_FULL_EMPTY_TRUTH(Efficiency_Playlist[0],Efficiency_Playlist_TRUTH[0], Efficiency_Playlist[1],Efficiency_Playlist_TRUTH[1],
  "h_2ndTrkE_2ndtrkangle_Proton", "KE_{2ndTrk} [GeV]", "#theta_{2ndtrk} [Deg](wrtb)", "KE_{2ndTrk} vs #theta_{2ndtrk} [Proton]" ,"Efficency" , mnv_plot, can2, text_title_pdf2);

Draw_Efficiency_2D_FULL_EMPTY_TRUTH(Efficiency_Playlist[0],Efficiency_Playlist_TRUTH[0], Efficiency_Playlist[1],Efficiency_Playlist_TRUTH[1],
  "h_2ndTrkE_2ndtrkangle_Pion", "KE_{2ndTrk} [GeV]", "#theta_{2ndtrk} [Deg](wrtb)", "KE_{2ndTrk} vs #theta_{2ndtrk} [Pion]" ,"Efficency" , mnv_plot, can2, text_title_pdf2);

  //Draw_Efficiency_2ndTrk_FULL_EMPTY(Efficiency_Playlist[0],Efficiency_Playlist[1] , "h_secTrk_Pathlength",
  //0, " ", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[3] );

  //Draw_Efficiency_2ndTrk_FULL_EMPTY(Efficiency_Playlist[0],Efficiency_Playlist[1] , "h_secTrk_DOCA",
  //0, " ", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[4] );

Draw2DHist_TFILE(PlaylistMC_1F_piePlots.TFILE_PLAYLIST, "h_Mig_MuonE", "Migration", "RECO E_{#mu}", "TRUE E_{#mu}", text_title_pdf2, can2, mnv_plot);

Draw2DHist_TFILE(PlaylistMC_1F_piePlots.TFILE_PLAYLIST, "h_Mig_MuonPZ", "RECO Muon P_{Z}", "TRUE Muon P_{Z}", "Migration Muon P_{Z}", text_title_pdf2, can2, mnv_plot);

Draw2DHist_TFILE(PlaylistMC_1F_piePlots.TFILE_PLAYLIST, "h_Mig_MuonPT", "RECO Muon P_{T}", "TRUE Muon P_{T}", "Migration Muon P_{T}", text_title_pdf2, can2, mnv_plot);

Draw2DHist_TFILE(PlaylistMC_1F_piePlots.TFILE_PLAYLIST, "h_Mig_MuonTheta", "RECO Muon #theta_{#mu}", "TRUE Muon #theta_{#mu}", "Migration Muon #theta_{#mu}", text_title_pdf2, can2, mnv_plot);

Draw2DHist_TFILE(PlaylistMC_1F_piePlots.TFILE_PLAYLIST, "h_Mig_Vertex_X", "RECO Vertex X", "TRUE Vertex X", "Migration Vertex X", text_title_pdf2, can2, mnv_plot);

Draw2DHist_TFILE(PlaylistMC_1F_piePlots.TFILE_PLAYLIST, "h_Mig_Vertex_Y", "RECO Vertex Y", "TRUE Vertex Y", "Migration Vertex Y", text_title_pdf2, can2, mnv_plot);

Draw2DHist_TFILE(PlaylistMC_1F_piePlots.TFILE_PLAYLIST, "h_Mig_Vertex_R", "RECO Vertex R", "TRUE Vertex R", "Migration Vertex R", text_title_pdf2, can2, mnv_plot);

Draw2DHist_TFILE(PlaylistMC_1F_piePlots.TFILE_PLAYLIST, "h_Mig_Vertex_Z", "RECO Vertex Z", "TRUE Vertex Z", "Migration Vertex Z", text_title_pdf2, can2, mnv_plot);


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

      hist_full_nom->Divide(hist_full_nom,hist_full_dem);

      sprintf(Title_His, "Vertex Ratio %s (%s) (%s)(Full)", title_type_char, title , playlistFull_char);
      DrawCVAndError_FromHIST(hist_full_nom, Title_His ,Xaxis_title,"#frac{reco}{true}", pdf,true);

      hist_empty_nom->Divide(hist_empty_nom,hist_empty_dem);

      sprintf(Title_His, "Vertex Ratio  %s (%s) (%s)(Empty)", title_type_char, title , playlistFull_char);
      DrawCVAndError_FromHIST(hist_empty_nom, Title_His ,Xaxis_title,"#frac{reco}{true}", pdf,true);

      hist_full_nom_clone->Divide(hist_full_nom_clone,hist_full_dem_clone);
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

      sprintf(Title_His, "Migration %s [Full(%s)]", title_type_char, title, playlistFull_char);
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

    Draw2DHist_hist(hist_FULL_clone,Title_His, Xaxis_title ,Yaxis_title, pdf_withTag, can, plot);
    std::cout<<"inside:Draw_Resolution_2D_FULL_EMPTY_TRUTH:->Draw2DHist_histWithTProfile "<<std::endl;
    Draw2DHist_histWithTProfile(hist_FULL_clone,Title_His, Xaxis_title ,Yaxis_title, pdf_withTag, can, plot); //pdf
    std::cout<<"inside:Draw_Resolution_2D_FULL_EMPTY_TRUTH:->DrawMagration_heatMap "<<std::endl;
    DrawMagration_heatMap(hist_FULL_clone, Xaxis_title,Yaxis_title, Title_His, pdf_withTag, can, plot); //pdf
    std::cout<<"inside:Draw_Resolution_2D_FULL_EMPTY_TRUTH:->Draw_XDistribution_PerBinWithGaussFit_2DHist"<<std::endl;
    Draw_XDistribution_PerBinWithGaussFit_2DHist(hist_FULL_clone, Title_His, Xaxis_title ,Yaxis_title, pdf, can, plot,false, ymax); //needs no pdf format




  }//endl;

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

  return CryoVertexVars;
//#endif
}


std::vector<SecondTrkVar> Get2ndTrkVaribles() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<SecondTrkVar> Vector_Vars;

  Vector_Vars.push_back(ksecE);
  Vector_Vars.push_back(kThetamid);
  Vector_Vars.push_back(kOpenAngle);
  //Vector_Vars.push_back(kPathway);
  //Vector_Vars.push_back(kDOCA);


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
