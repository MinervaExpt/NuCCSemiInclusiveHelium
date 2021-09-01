#include "EfficiencyPlots_FullStats.h"
//////////////////////////////////////////////////////////////////////////////

void Draw_Efficiency_2ndTrk(std::vector <PlayList_INFO> Playlist, ME_helium_Playlists Playlist_toscaleto , const char *histoName,
  int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf , SecondTrkVar playlist_name );

void Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(PlayList_INFO FULL_playlist_nom,PlayList_INFO FULL_playlist_TRUTHDEM,
  PlayList_INFO EMPTY_playlist_nom, PlayList_INFO EMPTY_playlist_TRUTH , const char *histoName,
  int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf , SecondTrkVar playlist_name );

void Draw_Efficiency_2D_FULL_EMPTY(PlayList_INFO FULL_playlist,PlayList_INFO EMPTY_playlist , const char *histoName,const char *Xaxis_title,const char *Yaxis_title,
  int logScale,const char* title ,const char* title_type_char , MnvPlotter *plot, TCanvas *can, const char *pdf  );

  void Draw_Efficiency_2D_FULL_EMPTY_TRUTH(PlayList_INFO FULL_playlist_nom,PlayList_INFO FULL_playlist_DemTRUE,
     PlayList_INFO EMPTY_playlist_nom,PlayList_INFO EMPTY_playlist_DemTRUE, const char *histoName, const char *Xaxis_title, const char *Yaxis_title,
            int logScale, const char* title ,const char* title_type_char , MnvPlotter *plot, TCanvas *can, const char *pdf);

void Draw_Efficiency_Muon_FULL_EMPTY(PlayList_INFO FULL_playlist,PlayList_INFO EMPTY_playlist , const char *histoName,
  int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf , MuonVar playlist_name );


void MakeLatexForEffMuonVar_StatsOnly(std::string output_name ,  std::string pdf_name_CV, const std::vector<MuonVar> muon_vector);

void Appendtotxt_2ndTrk(std::string output_name ,  std::string pdf_name_CV,int First_page, char *Var_name ,char *Units_name, std::vector<double>input_vectors);

void Appendtotxt_2D_Eff(std::string output_name ,  std::string pdf_name_CV, int First_page, char *Var_name );

void Appendtotxt_2D_Eff_Panel_Combined(std::string output_name ,  std::string pdf_name_CV, int First_page, char *Var_name );

void Appendtotxt_2D_Eff_Panel_Playlists(std::string output_name ,  std::string pdf_name_CV, int First_page, char *Var_name);



void Kin(bool &cutsOn, bool &my_norm, bool &my_debug, const char *userDir) {
TH1::AddDirectory(false);
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~       Starting Plotter: ME Efficiency Plots         ~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::vector<ME_helium_Playlists> GetPlayListVector_MC();
const std::vector< ME_helium_Playlists> kMEPlayList_Vector = GetPlayListVector_MC();
//const std::vector< ME_helium_Playlists> kPlayListVector_DATA = GetPlayListVector_DATA();
std::vector<CryoVertex> GetCryoVertexVaribles();
std::vector<SecondTrkVar> Get2ndTrkVaribles();
std::vector<MuonVar> GetMUONVaribles();
const std::vector<CryoVertex> kCryoVertexVaribles_vector = GetCryoVertexVaribles();
const std::vector<SecondTrkVar> k2ndTrk_vector = Get2ndTrkVaribles();
const std::vector<MuonVar> kMuonVaribles = GetMUONVaribles();
//FullAndEmptyPlaylistMap PLAYLIST_MAP_MC = MakeFullorEmptyList(kMEPlayList_Vector);
//FullAndEmptyPlaylistMap PLAYLIST_MAP_DATA = MakeFullorEmptyList(kPlayListVector_DATA);

ME_playlist_RootPathMAP MAP_RootPath_Empty_MC;
ME_playlist_RootPathMAP MAP_RootPath_Full_MC;

ME_playlist_RootPathMAP MAP_RootPath_Empty_MC_TRUTH;
ME_playlist_RootPathMAP MAP_RootPath_Full_MC_TRUTH;

/////////////////
/// MC RECO
/////////////////
// Empty Playlist
/////////////////
auto PlaylistME_1G_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1G_MC_All_SysErrorsOn.root";
auto PlaylistME_1A_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1A_MC_All_SysErrorsOn.root";
auto PlaylistME_1L_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1L_MC_All_SysErrorsOn.root";
auto PlaylistME_1M_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1M_MC_All_SysErrorsOn.root";
auto PlaylistME_1N_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1N_MC_All_SysErrorsOn.root";
MAP_RootPath_Empty_MC.insert(std::make_pair(kMEPlayList_Vector.at(0), PlaylistME_1G_MC_path));
MAP_RootPath_Empty_MC.insert(std::make_pair(kMEPlayList_Vector.at(1), PlaylistME_1A_MC_path));
MAP_RootPath_Empty_MC.insert(std::make_pair(kMEPlayList_Vector.at(2), PlaylistME_1L_MC_path));
MAP_RootPath_Empty_MC.insert(std::make_pair(kMEPlayList_Vector.at(3), PlaylistME_1M_MC_path));
MAP_RootPath_Empty_MC.insert(std::make_pair(kMEPlayList_Vector.at(4), PlaylistME_1N_MC_path));
////////
//Full//
////////
auto PlaylistME_1P_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1P_MC_All_SysErrorsOn.root";
auto PlaylistME_1C_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1C_MC_All_SysErrorsOn.root";
auto PlaylistME_1D_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1D_MC_All_SysErrorsOn.root";
auto PlaylistME_1F_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1F_MC_All_SysErrorsOn.root";
auto PlaylistME_1E_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1E_MC_All_SysErrorsOn.root";
MAP_RootPath_Full_MC.insert(std::make_pair(kMEPlayList_Vector.at(5), PlaylistME_1P_MC_path));
MAP_RootPath_Full_MC.insert(std::make_pair(kMEPlayList_Vector.at(6), PlaylistME_1C_MC_path));
MAP_RootPath_Full_MC.insert(std::make_pair(kMEPlayList_Vector.at(7), PlaylistME_1D_MC_path));
MAP_RootPath_Full_MC.insert(std::make_pair(kMEPlayList_Vector.at(8), PlaylistME_1F_MC_path));
MAP_RootPath_Full_MC.insert(std::make_pair(kMEPlayList_Vector.at(9), PlaylistME_1E_MC_path));


////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////
/// MC TRUTH
/////////////////
// Empty Playlist
/////////////////
auto PlaylistME_1G_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1G_TRUTH_All_SysErrorsOn.root";
auto PlaylistME_1A_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1A_TRUTH_All_SysErrorsOn.root";
auto PlaylistME_1L_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1L_TRUTH_All_SysErrorsOn.root";
auto PlaylistME_1M_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1M_TRUTH_All_SysErrorsOn.root";
auto PlaylistME_1N_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1N_TRUTH_All_SysErrorsOn.root";
MAP_RootPath_Empty_MC_TRUTH.insert(std::make_pair(kMEPlayList_Vector.at(0), PlaylistME_1G_MC_TRUTH_path));
MAP_RootPath_Empty_MC_TRUTH.insert(std::make_pair(kMEPlayList_Vector.at(1), PlaylistME_1A_MC_TRUTH_path));
MAP_RootPath_Empty_MC_TRUTH.insert(std::make_pair(kMEPlayList_Vector.at(2), PlaylistME_1L_MC_TRUTH_path));
MAP_RootPath_Empty_MC_TRUTH.insert(std::make_pair(kMEPlayList_Vector.at(3), PlaylistME_1M_MC_TRUTH_path));
MAP_RootPath_Empty_MC_TRUTH.insert(std::make_pair(kMEPlayList_Vector.at(4), PlaylistME_1N_MC_TRUTH_path));
////////
//Full//
////////
auto PlaylistME_1P_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1P_TRUTH_All_SysErrorsOn.root";
auto PlaylistME_1C_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1C_TRUTH_All_SysErrorsOn.root";
auto PlaylistME_1D_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1D_TRUTH_All_SysErrorsOn.root";
auto PlaylistME_1F_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1F_TRUTH_All_SysErrorsOn.root";
auto PlaylistME_1E_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1E_TRUTH_All_SysErrorsOn.root";
MAP_RootPath_Full_MC_TRUTH.insert(std::make_pair(kMEPlayList_Vector.at(5), PlaylistME_1P_MC_TRUTH_path));
MAP_RootPath_Full_MC_TRUTH.insert(std::make_pair(kMEPlayList_Vector.at(6), PlaylistME_1C_MC_TRUTH_path));
MAP_RootPath_Full_MC_TRUTH.insert(std::make_pair(kMEPlayList_Vector.at(7), PlaylistME_1D_MC_TRUTH_path));
MAP_RootPath_Full_MC_TRUTH.insert(std::make_pair(kMEPlayList_Vector.at(8), PlaylistME_1F_MC_TRUTH_path));
MAP_RootPath_Full_MC_TRUTH.insert(std::make_pair(kMEPlayList_Vector.at(9), PlaylistME_1E_MC_TRUTH_path));

Pot_MapList EmptyPOT_local_MC_MAP = Constuct_POT_playlistMap(MAP_RootPath_Empty_MC, true);
Pot_MapList FullPOT_local_MC_MAP  = Constuct_POT_playlistMap(MAP_RootPath_Full_MC, true);


///////////////////////////////////////////////////////////////////////////////////////////
PrintPot_MapList(EmptyPOT_local_MC_MAP, "EmptyPOT_local_MC_MAP"  );
PrintPot_MapList(FullPOT_local_MC_MAP, "FullPOT_local_MC_MAP"  );

Pot_MapList EmptyPOT_local_MC_ScaledMAP = POT_ScalersMap(EmptyPOT_local_MC_MAP ,FullPOT_local_MC_MAP[kMEPlayList_Vector.at(8)] );
Pot_MapList FullPOT_local_MC_ScaledMAP = POT_ScalersMap(FullPOT_local_MC_MAP ,FullPOT_local_MC_MAP[kMEPlayList_Vector.at(8)] );


PrintPot_MapList(EmptyPOT_local_MC_ScaledMAP, "EmptyPOT_local_MC_ScaledMAP"  );
PrintPot_MapList(FullPOT_local_MC_ScaledMAP, "FullPOT_local_MC_ScaledMAP"  );


ME_playlist_TFileMAP EmptyTFile_Map_MC;
TFile *PlaylistME_1G_TFile = new TFile(PlaylistME_1G_MC_path);
TFile *PlaylistME_1A_TFile = new TFile(PlaylistME_1A_MC_path);
TFile *PlaylistME_1L_TFile = new TFile(PlaylistME_1L_MC_path);
TFile *PlaylistME_1M_TFile = new TFile(PlaylistME_1M_MC_path);
TFile *PlaylistME_1N_TFile = new TFile(PlaylistME_1N_MC_path);
EmptyTFile_Map_MC.insert(std::make_pair(kMEPlayList_Vector.at(0),PlaylistME_1G_TFile));
EmptyTFile_Map_MC.insert(std::make_pair(kMEPlayList_Vector.at(1),PlaylistME_1A_TFile));
EmptyTFile_Map_MC.insert(std::make_pair(kMEPlayList_Vector.at(2),PlaylistME_1L_TFile));
EmptyTFile_Map_MC.insert(std::make_pair(kMEPlayList_Vector.at(3),PlaylistME_1M_TFile));
EmptyTFile_Map_MC.insert(std::make_pair(kMEPlayList_Vector.at(4),PlaylistME_1N_TFile));

ME_playlist_TFileMAP EmptyTFile_Map_MC_TRUTH;
TFile *PlaylistME_1G_TFile_TRUTH = new TFile(PlaylistME_1G_MC_TRUTH_path);
TFile *PlaylistME_1A_TFile_TRUTH = new TFile(PlaylistME_1A_MC_TRUTH_path);
TFile *PlaylistME_1L_TFile_TRUTH = new TFile(PlaylistME_1L_MC_TRUTH_path);
TFile *PlaylistME_1M_TFile_TRUTH = new TFile(PlaylistME_1M_MC_TRUTH_path);
TFile *PlaylistME_1N_TFile_TRUTH = new TFile(PlaylistME_1N_MC_TRUTH_path);
EmptyTFile_Map_MC_TRUTH.insert(std::make_pair(kMEPlayList_Vector.at(0),PlaylistME_1G_TFile_TRUTH));
EmptyTFile_Map_MC_TRUTH.insert(std::make_pair(kMEPlayList_Vector.at(1),PlaylistME_1A_TFile_TRUTH));
EmptyTFile_Map_MC_TRUTH.insert(std::make_pair(kMEPlayList_Vector.at(2),PlaylistME_1L_TFile_TRUTH));
EmptyTFile_Map_MC_TRUTH.insert(std::make_pair(kMEPlayList_Vector.at(3),PlaylistME_1M_TFile_TRUTH));
EmptyTFile_Map_MC_TRUTH.insert(std::make_pair(kMEPlayList_Vector.at(4),PlaylistME_1N_TFile_TRUTH));



ME_playlist_TFileMAP FullTFile_Map_MC;
TFile *PlaylistME_1P_TFile = new TFile(PlaylistME_1P_MC_path);
TFile *PlaylistME_1C_TFile = new TFile(PlaylistME_1C_MC_path);
TFile *PlaylistME_1D_TFile = new TFile(PlaylistME_1D_MC_path);
TFile *PlaylistME_1F_TFile = new TFile(PlaylistME_1F_MC_path);
TFile *PlaylistME_1E_TFile = new TFile(PlaylistME_1E_MC_path);
FullTFile_Map_MC.insert(std::make_pair(kMEPlayList_Vector.at(5),PlaylistME_1P_TFile));
FullTFile_Map_MC.insert(std::make_pair(kMEPlayList_Vector.at(6),PlaylistME_1C_TFile));
FullTFile_Map_MC.insert(std::make_pair(kMEPlayList_Vector.at(7),PlaylistME_1D_TFile));
FullTFile_Map_MC.insert(std::make_pair(kMEPlayList_Vector.at(8),PlaylistME_1F_TFile));
FullTFile_Map_MC.insert(std::make_pair(kMEPlayList_Vector.at(9),PlaylistME_1E_TFile));



ME_playlist_TFileMAP FullTFile_Map_MC_TRUTH;
TFile *PlaylistME_1P_TFile_TRUTH = new TFile(PlaylistME_1P_MC_TRUTH_path);
TFile *PlaylistME_1C_TFile_TRUTH = new TFile(PlaylistME_1C_MC_TRUTH_path);
TFile *PlaylistME_1D_TFile_TRUTH = new TFile(PlaylistME_1D_MC_TRUTH_path);
TFile *PlaylistME_1F_TFile_TRUTH = new TFile(PlaylistME_1F_MC_TRUTH_path);
TFile *PlaylistME_1E_TFile_TRUTH = new TFile(PlaylistME_1E_MC_TRUTH_path);
FullTFile_Map_MC_TRUTH.insert(std::make_pair(kMEPlayList_Vector.at(5),PlaylistME_1P_TFile_TRUTH));
FullTFile_Map_MC_TRUTH.insert(std::make_pair(kMEPlayList_Vector.at(6),PlaylistME_1C_TFile_TRUTH));
FullTFile_Map_MC_TRUTH.insert(std::make_pair(kMEPlayList_Vector.at(7),PlaylistME_1D_TFile_TRUTH));
FullTFile_Map_MC_TRUTH.insert(std::make_pair(kMEPlayList_Vector.at(8),PlaylistME_1F_TFile_TRUTH));
FullTFile_Map_MC_TRUTH.insert(std::make_pair(kMEPlayList_Vector.at(9),PlaylistME_1E_TFile_TRUTH));



bool Stats_only= true;
bool is_mc = true;
bool MakeLogX = true;
bool MakeNOTLogX = false;
bool MakeEffPlotsonly = true;

 char text_title_pdf1[2024];
 char text_title_pdf2[2024];
 char text_title_pdf3[2024];
 char text_title_pdf4[2024];
 char text_title_pdf5[2024];
time_t now = time(0);
tm *ltm = localtime(&now);
 char timeset[2024];
 auto Playlist_names =  MakePlaylistString(kMEPlayList_Vector);
sprintf(timeset,"%i_%i_%i_%i_%s",1 + ltm->tm_mon,ltm->tm_mday, ltm->tm_hour,ltm->tm_min,Playlist_names.c_str());

TCanvas *can1 = new TCanvas("can1");
sprintf(text_title_pdf1, "PLOTS_MuonEfficiencyTRUTH_FULLStats.pdf(");
can1 -> Print(text_title_pdf1);
sprintf(text_title_pdf2, "PLOTS_MuonEfficiencyTRUTH_FULLStats.pdf");
sprintf(text_title_pdf5, "PLOTS_MuonEfficiencyTRUTH_FULLStats");
sprintf(text_title_pdf3, "PLOTS_MuonEfficiencyTRUTH_FULLStats.pdf)");
sprintf(text_title_pdf4, "PLOTS_MuonEfficiencyTRUTH_FULLStats");



for(auto MuonVar : kMuonVaribles){
  auto histName = GetMuonVarHistName(MuonVar);
  char histName_char[histName.length()+1];
  strcpy(histName_char,histName.c_str());

  Draw_Efficiency_Muon_FULL_EMPTY_Fullstats( FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_ScaledMAP,
    EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_ScaledMAP,
    histName_char, MakeNOTLogX, "",  can1, text_title_pdf5, MuonVar, MakeEffPlotsonly, .1);

  Draw_Efficiency_Muon_FULL_EMPTY_Fullstats_Combined( FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_MAP,
    EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_MAP,
    histName_char, MakeNOTLogX, "",  can1, text_title_pdf5, MuonVar, MakeEffPlotsonly, .1);

}

std::cout << std::endl;
std::cout << "Done WITH EfficiencyPlots" << std::endl;
can1 -> Print(text_title_pdf3);

MakeLatexForEffMuonVar_StatsOnly("Efficency_latex_Muon" , text_title_pdf5, kMuonVaribles);
std::cout << "~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;


auto  Thetamid_vector = GetSecondTrkVarVector(k2ndTrk_vector[1]);
std::cout<<"checking bins"<<std::endl;

for(auto cat: Thetamid_vector){
std::cout<<"Angle bins =  "<< cat<<std::endl;

}
std::cout << "~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
std::vector<double> SecTrk_DOCA_vector= GetSecondTrkVarVector(k2ndTrk_vector[4]);
std::vector<double> Vertex_DOCAbin_vector= GetBinMuonVector(kDOCA_muon);
std::vector<double> Vertex_secondTrkEbin_vector= GetSecondTrkVarVector(k2ndTrk_vector[0]);
std::vector<double> Vertex_secondTrkEbin_Proton_vector= GetSecondTrkVarVector(k2ndTrk_vector[5]);
//std::sort(Vertex_secondTrkEbin_Proton_vector.begin(),Vertex_secondTrkEbin_Proton_vector.end());
std::vector<double> SecTrk_Pathway_vector= GetSecondTrkVarVector(k2ndTrk_vector[3]);




TCanvas *can2 = new TCanvas("can2");
sprintf(text_title_pdf1, "PLOTS_Recoil_EfficiencyTRUTH_FULLStats.pdf(");
can2 -> Print(text_title_pdf1);
sprintf(text_title_pdf2, "PLOTS_Recoil_EfficiencyTRUTH_FULLStats.pdf");
sprintf(text_title_pdf5, "PLOTS_Recoil_EfficiencyTRUTH_FULLStats" );
sprintf(text_title_pdf3, "PLOTS_Recoil_EfficiencyTRUTH_FULLStats.pdf)");
sprintf(text_title_pdf4, "PLOTS_Recoil_EfficiencyTRUTH_FULLStats" );
std::string text_title_pdf5_string(text_title_pdf5);

double max_Y_2ndtrkKE = .12;

Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH_FullStats( FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_ScaledMAP,
  EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_ScaledMAP,
  "h_secTrk_Energy", MakeLogX, "",  can2, text_title_pdf5, k2ndTrk_vector[0], MakeEffPlotsonly, max_Y_2ndtrkKE);

Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH_FullStats_COMBINED( FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_MAP,
  EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_MAP,
  "h_secTrk_Energy", MakeLogX, "",  can2, text_title_pdf5, k2ndTrk_vector[0], MakeEffPlotsonly,max_Y_2ndtrkKE);

    int start=2;
    int spacing=26;

    Appendtotxt_2ndTrk("Efficency_latex_2ndtrk", text_title_pdf5_string, start,  "secTrk KE" ,"GeV", Vertex_secondTrkEbin_vector);


Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH_FullStats( FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_ScaledMAP,
  EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_ScaledMAP,
  "h_secTrk_Energy_PROTON", MakeLogX, "Proton",  can2, text_title_pdf5, k2ndTrk_vector[0], MakeEffPlotsonly, max_Y_2ndtrkKE);

Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH_FullStats_COMBINED( FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_MAP,
  EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_MAP,
  "h_secTrk_Energy_PROTON", MakeLogX, "Proton",  can2, text_title_pdf5, k2ndTrk_vector[0], MakeEffPlotsonly,max_Y_2ndtrkKE);

    start=start+spacing;

    Appendtotxt_2ndTrk("Efficency_latex_2ndtrk", text_title_pdf5_string, start,  "secTrk KE [Proton]" ,"[GeV]", Vertex_secondTrkEbin_Proton_vector);


Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH_FullStats( FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_ScaledMAP,
  EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_ScaledMAP,
  "h_secTrk_Energy_PION", MakeLogX, "#pi^{#pm}",  can2, text_title_pdf5, k2ndTrk_vector[0], MakeEffPlotsonly,max_Y_2ndtrkKE);

Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH_FullStats_COMBINED( FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_MAP,
  EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_MAP,
  "h_secTrk_Energy_PION", MakeLogX, "#pi^{#pm}",  can2, text_title_pdf5, k2ndTrk_vector[0], MakeEffPlotsonly,max_Y_2ndtrkKE);

    start=start+spacing;
    Appendtotxt_2ndTrk("Efficency_latex_2ndtrk", text_title_pdf5_string, start,  "secTrk KE [\\pi^{\\pm}]" ,"GeV", Vertex_secondTrkEbin_Proton_vector);


Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH_FullStats( FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_ScaledMAP,
  EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_ScaledMAP,
  "h_secTrk_Energy_Dimuon", MakeLogX, "Dimuon",  can2, text_title_pdf5, k2ndTrk_vector[0], MakeEffPlotsonly,max_Y_2ndtrkKE);

Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH_FullStats_COMBINED( FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_MAP,
  EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_MAP,
  "h_secTrk_Energy_Dimuon", MakeLogX, "Dimuon",  can2, text_title_pdf5, k2ndTrk_vector[0], MakeEffPlotsonly,max_Y_2ndtrkKE);

    start=start+spacing;
    Appendtotxt_2ndTrk("Efficency_latex_2ndtrk", text_title_pdf5_string, start,  "secTrk KE [DiMuon]" ,"GeV", Vertex_secondTrkEbin_Proton_vector);

double Max_Y_2ndtrk_Angle = .12;

Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH_FullStats( FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_ScaledMAP,
  EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_ScaledMAP,
  "h_secTrk_Theta", MakeNOTLogX, "",  can2, text_title_pdf5, k2ndTrk_vector[1], MakeEffPlotsonly, Max_Y_2ndtrk_Angle);

Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH_FullStats_COMBINED( FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_MAP,
  EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_MAP,
  "h_secTrk_Theta", MakeNOTLogX, "",  can2, text_title_pdf5, k2ndTrk_vector[1], MakeEffPlotsonly, Max_Y_2ndtrk_Angle);

    start=start+spacing;
    Appendtotxt_2ndTrk("Efficency_latex_2ndtrk", text_title_pdf5_string, start,  "\\theta_{2ndTrk}" ,"Deg", Thetamid_vector);

Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH_FullStats( FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_ScaledMAP,
  EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_ScaledMAP,
  "h_secTrk_Theta_PROTON", MakeNOTLogX, "Proton",  can2, text_title_pdf5, k2ndTrk_vector[1], MakeEffPlotsonly,Max_Y_2ndtrk_Angle);

Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH_FullStats_COMBINED( FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_MAP,
  EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_MAP,
  "h_secTrk_Theta_PROTON", MakeNOTLogX, "Proton",  can2, text_title_pdf5, k2ndTrk_vector[1], MakeEffPlotsonly,Max_Y_2ndtrk_Angle);

    start=start+spacing;
    Appendtotxt_2ndTrk("Efficency_latex_2ndtrk", text_title_pdf5_string, start,  "\\theta_{2ndTrk}(Proton)" ,"Deg", Thetamid_vector);


Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH_FullStats( FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_ScaledMAP,
  EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_ScaledMAP,
  "h_secTrk_Theta_PION", MakeNOTLogX, "#pi^{#pm}",  can2, text_title_pdf5, k2ndTrk_vector[1], MakeEffPlotsonly,Max_Y_2ndtrk_Angle);

Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH_FullStats_COMBINED( FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_MAP,
  EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_MAP,
  "h_secTrk_Theta_PION", MakeNOTLogX, "#pi^{#pm}",  can2, text_title_pdf5, k2ndTrk_vector[1], MakeEffPlotsonly,Max_Y_2ndtrk_Angle);

  start=start+spacing;
  Appendtotxt_2ndTrk("Efficency_latex_2ndtrk", text_title_pdf5_string, start,  "\\theta_{2ndTrk}(\\pi^{\\pm})" ,"Deg", Thetamid_vector);

Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH_FullStats( FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_ScaledMAP,
  EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_ScaledMAP,
  "h_secTrk_Theta_Dimuon", MakeNOTLogX, "Dimuon",  can2, text_title_pdf5, k2ndTrk_vector[1], MakeEffPlotsonly,Max_Y_2ndtrk_Angle);

Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH_FullStats_COMBINED( FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_MAP,
  EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_MAP,
  "h_secTrk_Theta_Dimuon", MakeNOTLogX, "Dimuon",  can2, text_title_pdf5, k2ndTrk_vector[1], MakeEffPlotsonly,Max_Y_2ndtrk_Angle);

    start=start+spacing;
    Appendtotxt_2ndTrk("Efficency_latex_2ndtrk", text_title_pdf5_string, start,  "\\theta_{2ndTrk}(Dimuon)" ,"Deg", Thetamid_vector);
    ///////////////////
    /// PathLength
    ////////////////

    double Max_Y_2ndtrk_Pathlength = .12;
  Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH_FullStats( FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_ScaledMAP,
    EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_ScaledMAP,
    "h_secTrk_Pathlength", MakeNOTLogX, "",  can2, text_title_pdf5, k2ndTrk_vector[3], MakeEffPlotsonly,Max_Y_2ndtrk_Pathlength);

  Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH_FullStats_COMBINED( FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_MAP,
    EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_MAP,
    "h_secTrk_Pathlength", MakeNOTLogX, "",  can2, text_title_pdf5, k2ndTrk_vector[3], MakeEffPlotsonly,Max_Y_2ndtrk_Pathlength);

    start=start+spacing;
    Appendtotxt_2ndTrk("Efficency_latex_2ndtrk", text_title_pdf5_string, start,  "Pathlength" ,"cm^{2} / gram ", SecTrk_Pathway_vector);

  Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH_FullStats( FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_ScaledMAP,
    EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_ScaledMAP,
    "h_secTrk_Pathlength_PROTON", MakeNOTLogX, "Proton",  can2, text_title_pdf5, k2ndTrk_vector[3], MakeEffPlotsonly,Max_Y_2ndtrk_Pathlength);

  Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH_FullStats_COMBINED( FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_MAP,
    EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_MAP,
    "h_secTrk_Pathlength_PROTON", MakeNOTLogX, "Proton",  can2, text_title_pdf5, k2ndTrk_vector[3], MakeEffPlotsonly,Max_Y_2ndtrk_Pathlength);

    start=start+spacing;
    Appendtotxt_2ndTrk("Efficency_latex_2ndtrk", text_title_pdf5_string, start,  "Pathlength Proton" ,"cm^{2} / gram ", SecTrk_Pathway_vector);

    Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH_FullStats( FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_ScaledMAP,
      EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_ScaledMAP,
      "h_secTrk_Pathlength_PION", MakeNOTLogX, "Pion",  can2, text_title_pdf5, k2ndTrk_vector[3], MakeEffPlotsonly, .2);

    Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH_FullStats_COMBINED( FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_MAP,
      EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_MAP,
      "h_secTrk_Pathlength_PION", MakeNOTLogX, "Pion",  can2, text_title_pdf5, k2ndTrk_vector[3], MakeEffPlotsonly, .2);

      start=start+spacing;
      Appendtotxt_2ndTrk("Efficency_latex_2ndtrk", text_title_pdf5_string, start,  "Pathlength (\\pi^{\\pm}) " ,"cm^{2} / gram ", SecTrk_Pathway_vector);
      double Max_Y_2ndtrk_Doca = .8;

std::cout << std::endl;
std::cout << "Done WITH EfficiencyPlots" << std::endl;
can2 -> Print(text_title_pdf3);

TCanvas *can3 = new TCanvas("can3");
MnvPlotter *mnv_plot = new MnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
sprintf(text_title_pdf1, "PLOTS_2DEfficiency_Panel_FULLStats.pdf(");
can3 -> Print(text_title_pdf1);
sprintf(text_title_pdf2, "PLOTS_2DEfficiency_Panel_FULLStats.pdf");
sprintf(text_title_pdf5, "PLOTS_2DEfficiency_Panel_FULLStats");
sprintf(text_title_pdf3, "PLOTS_2DEfficiency_Panel_FULLStats.pdf)");
sprintf(text_title_pdf4, "PLOTS_2DEfficiency_Panel_FULLStats");
std::string Panel_pdf_string(text_title_pdf5);
//Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats(FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_ScaledMAP,
  //EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_ScaledMAP,
  //"h_2d_PZ_PT","Muon P_{#parallel} [GeV]","Muon P_{T} [GeV]" , 0, "P_{T} vs P_{#parallel}", " ", mnv_plot, can3, text_title_pdf2, MakeEffPlotsonly);

  //Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_Combined(FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_ScaledMAP,
    //EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_ScaledMAP,
    //"h_2d_PZ_PT","Muon P_{#parallel} [GeV]","Muon P_{T} [GeV]" , 0, "P_{T} vs P_{#parallel}", " ", mnv_plot, can3, text_title_pdf2, MakeEffPlotsonly);



Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_PANELPLOTS(FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_ScaledMAP,
                                                         EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_ScaledMAP,
                                                         "h_2d_PZ_PT","P_{T}" ,"P_{#parallel}", "Efficieny",
                                                         false, false, "P_{T} [GeV] vs P_{#parallel}[GeV]", " ",
                                                          mnv_plot, can3, text_title_pdf2, MakeEffPlotsonly, .3, .25);

  Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_Combined_PanelPlots(FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_MAP,
                                                                    EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_MAP,
                                                                    "h_2d_PZ_PT", "P_{T}" ,"P_{#parallel}","Efficieny",
                                                                     false, false, "P_{T}[GeV] vs P_{#parallel}[GeV]", " ",
                                                                     mnv_plot, can3, text_title_pdf2, MakeEffPlotsonly, .3, .25);
//
int Start_page = 2;
Appendtotxt_2D_Eff_Panel_Combined("Combined_2DPanel_Eff" ,  Panel_pdf_string, Start_page, "P_{T} vs P_{\\parallel}" );
Appendtotxt_2D_Eff_Panel_Playlists("Combined_2DPanel_Playlists" ,  Panel_pdf_string, Start_page, "P_{T} vs P_{\\parallel}");


Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_PANELPLOTS(FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_ScaledMAP,
                                                          EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_ScaledMAP,
                                                          "h_2d_E_PZ","P_{#parallel}" ,"E_{#mu}", "Efficieny",
                                                          false, false, "P_{#parallel} [GeV] vs E_{#mu}[GeV]", " ",
                                                          mnv_plot, can3, text_title_pdf2, MakeEffPlotsonly, .10, .15);

Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_Combined_PanelPlots(FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_MAP,
                                                                  EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_MAP,
                                                                  "h_2d_E_PZ", "P_{#parallel}" ,"E_{#mu}","Efficieny",
                                                                  false, false, "P_{#parallel}[GeV] vs E_{#mu}[GeV]", " ",
                                                                  mnv_plot, can3, text_title_pdf2, MakeEffPlotsonly, .10, .15);
Start_page = Start_page+spacing;
Appendtotxt_2D_Eff_Panel_Combined("Combined_2DPanel_Eff" ,  Panel_pdf_string, Start_page, "P_{\\parallel} vs E_{\\mu}" );
Appendtotxt_2D_Eff_Panel_Playlists("Combined_2DPanel_Playlists" ,  Panel_pdf_string, Start_page, "P_{\\parallel} vs E_{\\mu}");


Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_PANELPLOTS(FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_ScaledMAP,
                                                          EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_ScaledMAP,
                                                          "h_2d_Theta_PZ","P_{#parallel}" ,"#theta_{#mu}", "Efficieny",
                                                          false, false, "P_{#parallel} [GeV] vs #theta_{#mu}(wrtb)[Deg]", " ",
                                                          mnv_plot, can3, text_title_pdf2, MakeEffPlotsonly, .1, .1);


Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_Combined_PanelPlots(FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_MAP,
                                                                  EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_MAP,
                                                                  "h_2d_Theta_PZ", "P_{#parallel}" ,"#theta_{#mu}","Efficieny",
                                                                  false, false, "P_{#parallel}[GeV] vs #theta_{#mu}(wrtb)[Deg]", " ",
                                                                  mnv_plot, can3, text_title_pdf2, MakeEffPlotsonly, .1, .1);

Start_page = Start_page+spacing;
Appendtotxt_2D_Eff_Panel_Combined("Combined_2DPanel_Eff" ,  Panel_pdf_string, Start_page, "P_{\\parallel} vs \\theta_{\\mu}" );
Appendtotxt_2D_Eff_Panel_Playlists("Combined_2DPanel_Playlists" ,  Panel_pdf_string, Start_page, "P_{\\parallel} vs \\theta_{\\mu}");


Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_PANELPLOTS(FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_ScaledMAP,
                                                        EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_ScaledMAP,
                                                        "h_2d_Theta_PT","P_{T}" ,"#theta_{#mu}", "Efficieny",
                                                        false, false, "P_{T} [GeV] vs #theta_{#mu}(wrtb)[Deg]", " ",
                                                        mnv_plot, can3, text_title_pdf2, MakeEffPlotsonly, .3, .3);

Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_Combined_PanelPlots(FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_MAP,
                                                                 EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_MAP,
                                                                 "h_2d_Theta_PT", "P_{T}" ,"#theta_{#mu}","Efficieny",
                                                                 false, false, "P_{T}[GeV] vs #theta_{#mu}(wrtb)[Deg]", " ",
                                                                 mnv_plot, can3, text_title_pdf2, MakeEffPlotsonly, .3, .3);
////////////////////////////////////////////////////////////////////////////////
Start_page = Start_page+spacing;
Appendtotxt_2D_Eff_Panel_Combined("Combined_2DPanel_Eff" ,  Panel_pdf_string, Start_page, "P_{T} vs \\theta_{\\mu}" );
Appendtotxt_2D_Eff_Panel_Playlists("Combined_2DPanel_Playlists" ,  Panel_pdf_string, Start_page, "P_{T} vs \\theta_{\\mu}");


Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_PANELPLOTS(FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_ScaledMAP,
                                                        EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_ScaledMAP,
                                                        "h_2d_muonPT_2ndTrkE","KE_{2ndTrk}" ,"P_{T}", "Efficieny",
                                                        true, false, "P_{T} [GeV] vs KE_{2ndTrk}", " ",
                                                        mnv_plot, can3, text_title_pdf2, MakeEffPlotsonly, .35, .35, .03, .015);

Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_Combined_PanelPlots(FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_MAP,
                                                                 EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_MAP,
                                                                 "h_2d_muonPT_2ndTrkE", "KE_{2ndTrk}" ,"P_{T}","Efficieny",
                                                                 true, false, "P_{T}[GeV] vs KE_{2ndTrk}", " ",
                                                                 mnv_plot, can3, text_title_pdf2, MakeEffPlotsonly, .35, .35, .03, .015);
//
Start_page = Start_page+spacing;
Appendtotxt_2D_Eff_Panel_Combined("Combined_2DPanel_Eff" ,  Panel_pdf_string, Start_page, "P_{T} vs KE_{2ndTrk}" );
Appendtotxt_2D_Eff_Panel_Playlists("Combined_2DPanel_Playlists" ,  Panel_pdf_string, Start_page, "P_{T} vs KE_{2ndTrk}");


Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_PANELPLOTS(FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_ScaledMAP,
                                                        EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_ScaledMAP,
                                                        "h_2d_muonPZ_2ndTrkE","KE_{2ndTrk}" ,"P_{#parallel}", "Efficieny",
                                                        true, false, "P_{#parallel} [GeV] vs KE_{2ndTrk}", " ",
                                                        mnv_plot, can3, text_title_pdf2, MakeEffPlotsonly, .4, .4, .03, .015);

Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_Combined_PanelPlots(FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_MAP,
                                                                  EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_MAP,
                                                                  "h_2d_muonPZ_2ndTrkE", "KE_{2ndTrk}" ,"P_{#parallel}","Efficieny",
                                                                  true, false, "P_{#parallel}[GeV] vs KE_{2ndTrk}", " ",
                                                                  mnv_plot, can3, text_title_pdf2, MakeEffPlotsonly, .4, .4, .03, .015);
//
Start_page = Start_page+spacing;
Appendtotxt_2D_Eff_Panel_Combined("Combined_2DPanel_Eff" ,  Panel_pdf_string, Start_page, "P_{\\parallel} vs KE_{2ndTrk}" );
Appendtotxt_2D_Eff_Panel_Playlists("Combined_2DPanel_Playlists" ,  Panel_pdf_string, Start_page, "P_{\\parallel} vs KE_{2ndTrk}");

///////////////////////////////////////////////////////////////////////////////
// Proton
///////////////////////////////////////////////////////////////////////////////

Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_PANELPLOTS(FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_ScaledMAP,
                                                        EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_ScaledMAP,
                                                        "h_2d_muonPT_2ndTrkE_Proton","KE_{2ndTrk}" ,"P_{T}", "Efficieny",
                                                        true, false, "P_{T} [GeV] vs KE_{2ndTrk}", "Proton",
                                                        mnv_plot, can3, text_title_pdf2, MakeEffPlotsonly, .4, .4, .03, .015);


Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_Combined_PanelPlots(FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_MAP,
                                                                 EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_MAP,
                                                                 "h_2d_muonPT_2ndTrkE_Proton", "KE_{2ndTrk}" ,"P_{T}","Efficieny",
                                                                 true, false, "P_{T}[GeV] vs KE_{2ndTrk}", "Proton ",
                                                                 mnv_plot, can3, text_title_pdf2, MakeEffPlotsonly, .4, .4, .03, .015);
//
Start_page = Start_page+spacing;
Appendtotxt_2D_Eff_Panel_Combined("Combined_2DPanel_Eff" ,  Panel_pdf_string, Start_page, "P_{T} vs KE_{2ndTrk} (Proton)" );
Appendtotxt_2D_Eff_Panel_Playlists("Combined_2DPanel_Playlists" ,  Panel_pdf_string, Start_page, "P_{T} vs KE_{2ndTrk} (Proton)");


Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_PANELPLOTS(FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_ScaledMAP,
                                                        EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_ScaledMAP,
                                                        "h_2d_muonPZ_2ndTrkE_Proton","KE_{2ndTrk}" ,"P_{#parallel}", "Efficieny",
                                                        true, false, "P_{#parallel} [GeV] vs KE_{2ndTrk}", " Proton",
                                                        mnv_plot, can3, text_title_pdf2, MakeEffPlotsonly, .4, .4, .03, .015);

Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_Combined_PanelPlots(FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_MAP,
                                                                  EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_MAP,
                                                                  "h_2d_muonPZ_2ndTrkE_Proton", "KE_{2ndTrk}" ,"P_{#parallel}","Efficieny",
                                                                  true, false, "P_{#parallel}[GeV] vs KE_{2ndTrk}", " Proton",
                                                                  mnv_plot, can3, text_title_pdf2, MakeEffPlotsonly, .4, .4, .03, .015);
//
Start_page = Start_page+spacing;
Appendtotxt_2D_Eff_Panel_Combined("Combined_2DPanel_Eff" ,  Panel_pdf_string, Start_page, "KE_{2ndTrk} Vs P_{\\parallel} (Proton)" );
Appendtotxt_2D_Eff_Panel_Playlists("Combined_2DPanel_Playlists" ,  Panel_pdf_string, Start_page, "KE_{2ndTrk} Vs P_{\\parallel} (Proton)");



//////////////////////////////////////////////////////////////
///Pion
////////////////////////////////////////////////////////////


Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_PANELPLOTS(FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_ScaledMAP,
                                                        EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_ScaledMAP,
                                                        "h_2d_muonPT_2ndTrkE_Pion","KE_{2ndTrk}" ,"P_{T}", "Efficieny",
                                                        true, false, "P_{T} [GeV] vs KE_{2ndTrk}", "#pi^{#pm}",
                                                        mnv_plot, can3, text_title_pdf2, MakeEffPlotsonly, .4, .4, .03, .015);

Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_Combined_PanelPlots(FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_MAP,
                                                                 EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_MAP,
                                                                 "h_2d_muonPT_2ndTrkE_Pion", "KE_{2ndTrk}" ,"P_{T}","Efficieny",
                                                                 true, false, "P_{T}[GeV] vs KE_{2ndTrk}", "#pi^{#pm}",
                                                                 mnv_plot, can3, text_title_pdf2, MakeEffPlotsonly, .4, .4, .03, .015);
//
Start_page = Start_page+spacing;
Appendtotxt_2D_Eff_Panel_Combined("Combined_2DPanel_Eff" ,  Panel_pdf_string, Start_page, "KE_{2ndTrk} Vs. P_{\\parallel} (\\pi^{\\pm})" );
Appendtotxt_2D_Eff_Panel_Playlists("Combined_2DPanel_Playlists" ,  Panel_pdf_string, Start_page, "KE_{2ndTrk} Vs. P_{\\parallel} (\\pi^{\\pm})");




Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_PANELPLOTS(FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_ScaledMAP,
                                                        EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_ScaledMAP,
                                                        "h_2d_muonPZ_2ndTrkE_Pion","KE_{2ndTrk}" ,"P_{#parallel}", "Efficieny",
                                                        true, false, "P_{#parallel} [GeV] vs KE_{2ndTrk}", "#pi^{#pm}",
                                                        mnv_plot, can3, text_title_pdf2, MakeEffPlotsonly, .4, .4, .03, .015);

Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_Combined_PanelPlots(FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_MAP,
                                                                  EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_MAP,
                                                                  "h_2d_muonPZ_2ndTrkE_Pion", "KE_{2ndTrk}" ,"P_{#parallel}","Efficieny",
                                                                  true, false, "P_{#parallel}[GeV] vs KE_{2ndTrk}", "#pi^{#pm}",
                                                                  mnv_plot, can3, text_title_pdf2, MakeEffPlotsonly, .4, .4, .03, .015);
//////////////////////////////////////////////////////////////////////
//
Start_page = Start_page+spacing;
Appendtotxt_2D_Eff_Panel_Combined("Combined_2DPanel_Eff" ,  Panel_pdf_string, Start_page, "KE_{2ndTrk} Vs. P_{\\parallel}(\\pi^{\\pm})" );
Appendtotxt_2D_Eff_Panel_Playlists("Combined_2DPanel_Playlists" ,  Panel_pdf_string, Start_page, "KE_{2ndTrk} Vs. P_{\\parallel}(\\pi^{\\pm})");



Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_PANELPLOTS(FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_ScaledMAP,
                                                        EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_ScaledMAP,
                                                        "h_2d_muonPT_2ndTrkangle","#theta_{2ndTrk}" ,"P_{T}", "Efficieny",
                                                        false, false, "P_{T} [GeV] vs #theta_{2ndTrk}", "",
                                                        mnv_plot, can3, text_title_pdf2, MakeEffPlotsonly, .25, .2, .03, .015);

Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_Combined_PanelPlots(FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_MAP,
                                                                 EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_MAP,
                                                                 "h_2d_muonPT_2ndTrkangle", "#theta_{2ndTrk}" ,"P_{T}","Efficieny",
                                                                 false, false, "P_{T}[GeV] vs #theta_{2ndTrk}", " ",
                                                                 mnv_plot, can3, text_title_pdf2, MakeEffPlotsonly, .25, .2, .03, .015);
//
Start_page = Start_page+spacing;
Appendtotxt_2D_Eff_Panel_Combined("Combined_2DPanel_Eff" ,  Panel_pdf_string, Start_page, "P_{T} vs \\theta_{2ndTrk}" );
Appendtotxt_2D_Eff_Panel_Playlists("Combined_2DPanel_Playlists" ,  Panel_pdf_string, Start_page, "P_{T} vs \\theta_{2ndTrk}");



Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_PANELPLOTS(FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_ScaledMAP,
                                                        EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_ScaledMAP,
                                                        "h_2d_muonPZ_2ndTrkangle","#theta_{2ndTrk}" ,"P_{#parallel}", "Efficieny",
                                                        false, false, "P_{#parallel} [GeV] vs #theta_{2ndTrk}", " ",
                                                        mnv_plot, can3, text_title_pdf2, MakeEffPlotsonly, .25, .2, .03, .015);

Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_Combined_PanelPlots(FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_MAP,
                                                                  EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_MAP,
                                                                  "h_2d_muonPZ_2ndTrkangle", "#theta_{2ndTrk}" ,"P_{#parallel}","Efficieny",
                                                                  false, false, "P_{#parallel}[GeV] vs #theta_{2ndTrk}", " ",
                                                                  mnv_plot, can3, text_title_pdf2, MakeEffPlotsonly, .25, .2, .03, .015);
//
Start_page = Start_page+spacing;
Appendtotxt_2D_Eff_Panel_Combined("Combined_2DPanel_Eff" ,  Panel_pdf_string, Start_page, "P_{\\parallel} vs \\theta_{2ndTrk}" );
Appendtotxt_2D_Eff_Panel_Playlists("Combined_2DPanel_Playlists" ,  Panel_pdf_string, Start_page, "P_{\\parallel} vs \\theta_{2ndTrk}");


//
Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_PANELPLOTS(FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_ScaledMAP,
                                                        EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_ScaledMAP,
                                                        "h_2d_2ndtrkangle_2ndTrkE_Proton","KE_{2ndtrk}","#theta_{2ndTrk}", "Efficieny",
                                                        true, false, "KE_{2ndtrk} [GeV] vs #theta_{2ndTrk}", "Proton ",
                                                        mnv_plot, can3, text_title_pdf2, MakeEffPlotsonly, .4, .4, .015, .015);

Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_Combined_PanelPlots(FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_MAP,
                                                                  EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_MAP,
                                                                  "h_2d_2ndtrkangle_2ndTrkE_Proton", "KE_{2ndtrk}","#theta_{2ndTrk}", "Efficieny",
                                                                  true, false, "KE_{2ndtrk}[GeV] vs #theta_{2ndTrk}", "Proton",
                                                                  mnv_plot, can3, text_title_pdf2, MakeEffPlotsonly, .4, .4, .015, .015);
//
Start_page = Start_page+spacing;
Appendtotxt_2D_Eff_Panel_Combined("Combined_2DPanel_Eff" ,  Panel_pdf_string, Start_page, "KE_{2ndtrk} vs \\theta_{2ndTrk} (p)" );
Appendtotxt_2D_Eff_Panel_Playlists("Combined_2DPanel_Playlists" ,  Panel_pdf_string, Start_page, "KE_{2ndtrk} vs \\theta_{2ndTrk} (p)");


Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_PANELPLOTS(FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_ScaledMAP,
                                                        EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_ScaledMAP,
                                                        "h_2d_2ndtrkangle_2ndTrkE_Pion","KE_{2ndtrk}","#theta_{2ndTrk}" , "Efficieny",
                                                        true, false, "KE_{2ndtrk} [GeV] vs #theta_{2ndTrk}", "#pi^{#pm}",
                                                        mnv_plot, can3, text_title_pdf2, MakeEffPlotsonly, .4, .4, .015, .015);

Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_Combined_PanelPlots(FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_MAP,
                                                                  EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_MAP,
                                                                  "h_2d_2ndtrkangle_2ndTrkE_Pion","KE_{2ndtrk}","#theta_{2ndTrk}" ,"Efficieny",
                                                                  true, false, "KE_{2ndtrk}[GeV] vs #theta_{2ndTrk}[Deg]", "#pi^{#pm}",
                                                                  mnv_plot, can3, text_title_pdf2, MakeEffPlotsonly, .4, .4, .015, .015);
//
Start_page = Start_page+spacing;
Appendtotxt_2D_Eff_Panel_Combined("Combined_2DPanel_Eff" ,  Panel_pdf_string, Start_page, "KE_{2ndtrk} vs \\theta_{2ndTrk} (\\pi^{\\pm})" );
Appendtotxt_2D_Eff_Panel_Playlists("Combined_2DPanel_Playlists" ,  Panel_pdf_string, Start_page, "KE_{2ndtrk} vs \\theta_{2ndTrk} (\\pi^{\\pm})");


Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_PANELPLOTS(FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_ScaledMAP,
                                                        EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_ScaledMAP,
                                                        "h_2d_2ndtrkPathlength_2ndTrkE","KE_{2ndtrk}", "Pathlength" , "Efficieny",
                                                        true, false, "KE_{2ndtrk} [GeV] vs Pathlength [#frac{g}{cm^{2}}]", "",
                                                        mnv_plot, can3, text_title_pdf2, MakeEffPlotsonly, .4, .4, .015, .015);

Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_Combined_PanelPlots(FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_MAP,
                                                                  EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_MAP,
                                                                  "h_2d_2ndtrkPathlength_2ndTrkE","KE_{2ndtrk}","Pathlength" ,"Efficieny",
                                                                  true, false, "KE_{2ndtrk}[GeV] vs Pathlength [#frac{g}{cm^{2}}]", "",
                                                                  mnv_plot, can3, text_title_pdf2, MakeEffPlotsonly, .4, .4, .015, .015);
//
Start_page = Start_page+spacing;
Appendtotxt_2D_Eff_Panel_Combined("Combined_2DPanel_Eff" ,  Panel_pdf_string, Start_page, "KE_{2ndtrk}[GeV] vs Pathlength" );
Appendtotxt_2D_Eff_Panel_Playlists("Combined_2DPanel_Playlists" ,  Panel_pdf_string, Start_page, "KE_{2ndtrk} vs Pathlength");

Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_PANELPLOTS(FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_ScaledMAP,
                                                        EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_ScaledMAP,
                                                        "h_2d_2ndtrkPathlength_2ndTrkE_Proton","KE_{2ndtrk}", "Pathlength" , "Efficieny",
                                                        true, false, "KE_{2ndtrk} [GeV] vs Pathlength [#frac{g}{cm^{2}}]", "Proton",
                                                        mnv_plot, can3, text_title_pdf2, MakeEffPlotsonly, .4, .4, .015, .015);

Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_Combined_PanelPlots(FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_MAP,
                                                                  EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_MAP,
                                                                  "h_2d_2ndtrkPathlength_2ndTrkE_Proton","KE_{2ndtrk}","Pathlength" ,"Efficieny",
                                                                  true, false, "KE_{2ndtrk}[GeV] vs Pathlength [#frac{g}{cm^{2}}]", "Proton",
                                                                  mnv_plot, can3, text_title_pdf2, MakeEffPlotsonly, .4, .4, .015, .015);
//
Start_page = Start_page+spacing;
Appendtotxt_2D_Eff_Panel_Combined("Combined_2DPanel_Eff" ,  Panel_pdf_string, Start_page, "KE_{2ndtrk} vs Pathlength (Proton)" );
Appendtotxt_2D_Eff_Panel_Playlists("Combined_2DPanel_Playlists" ,  Panel_pdf_string, Start_page, "KE_{2ndtrk} vs Pathlength (Proton)");


Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_PANELPLOTS(FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_ScaledMAP,
                                                        EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_ScaledMAP,
                                                        "h_2d_2ndtrkPathlength_2ndTrkE_Pion","KE_{2ndtrk}", "Pathlength" , "Efficieny",
                                                        true, false, "KE_{2ndtrk} [Deg] vs Pathlength [#frac{g}{cm^{2}}]", "#pi^{#pm}",
                                                        mnv_plot, can3, text_title_pdf2, MakeEffPlotsonly, .4, .4, .015, .015);

Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_Combined_PanelPlots(FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_MAP,
                                                                  EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_MAP,
                                                                  "h_2d_2ndtrkPathlength_2ndTrkE_Pion","KE_{2ndtrk}","Pathlength" ,"Efficieny",
                                                                  true, false, "KE_{2ndtrk}[Deg] vs Pathlength [#frac{g}{cm^{2}}]", "#pi^{#pm}",
                                                                  mnv_plot, can3, text_title_pdf2, MakeEffPlotsonly, .4, .4, .015, .015);
//
Start_page = Start_page+spacing;
Appendtotxt_2D_Eff_Panel_Combined("Combined_2DPanel_Eff" ,  Panel_pdf_string, Start_page, "KE_{2ndtrk} vs Pathlength (\\pi)" );
Appendtotxt_2D_Eff_Panel_Playlists("Combined_2DPanel_Playlists" ,  Panel_pdf_string, Start_page, "KE_{2ndtrk} vs Pathlength (\\pi)");


Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_PANELPLOTS(FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_ScaledMAP,
                                                        EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_ScaledMAP,
                                                        "h_2d_2ndtrkPathlength_2ndtrkangle","#theta_{2ndTrk}", "Pathlength" , "Efficieny",
                                                        true, false, "#theta_{2ndTrk} [Deg] vs Pathlength [#frac{g}{cm^{2}}]", "",
                                                        mnv_plot, can3, text_title_pdf2, MakeEffPlotsonly, .4, .4, .015, .015);

Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_Combined_PanelPlots(FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_MAP,
                                                                  EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_MAP,
                                                                  "h_2d_2ndtrkPathlength_2ndtrkangle","#theta_{2ndTrk}","Pathlength" ,"Efficieny",
                                                                  true, false, "#theta_{2ndTrk}[Deg] vs Pathlength [#frac{g}{cm^{2}}]", "",
                                                                  mnv_plot, can3, text_title_pdf2, MakeEffPlotsonly, .4, .4, .015, .015);
//
Start_page = Start_page+spacing;
Appendtotxt_2D_Eff_Panel_Combined("Combined_2DPanel_Eff" ,  Panel_pdf_string, Start_page, "\\theta_{2ndTrk} vs Pathlength" );
Appendtotxt_2D_Eff_Panel_Playlists("Combined_2DPanel_Playlists" ,  Panel_pdf_string, Start_page, "\\theta_{2ndTrk} vs Pathlength");

Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_PANELPLOTS(FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_ScaledMAP,
                                                        EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_ScaledMAP,
                                                        "h_2d_2ndtrkPathlength_2ndtrkangle_Proton","#theta_{2ndTrk}", "Pathlength" , "Efficieny",
                                                        true, false, "#theta_{2ndTrk} [Deg] vs Pathlength [#frac{g}{cm^{2}}]", "Proton",
                                                        mnv_plot, can3, text_title_pdf2, MakeEffPlotsonly, .4, .4, .015, .015);

Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_Combined_PanelPlots(FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_MAP,
                                                                  EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_MAP,
                                                                  "h_2d_2ndtrkPathlength_2ndtrkangle_Proton","#theta_{2ndTrk}","Pathlength" ,"Efficieny",
                                                                  true, false, "#theta_{2ndTrk}[Deg] vs Pathlength [#frac{g}{cm^{2}}]", "Proton",
                                                                  mnv_plot, can3, text_title_pdf2, MakeEffPlotsonly, .4, .4, .015, .015);
//
Start_page = Start_page+spacing;
Appendtotxt_2D_Eff_Panel_Combined("Combined_2DPanel_Eff" ,  Panel_pdf_string, Start_page, "\\theta_{2ndTrk} vs Pathlength (p)" );
Appendtotxt_2D_Eff_Panel_Playlists("Combined_2DPanel_Playlists" ,  Panel_pdf_string, Start_page, "\\theta_{2ndTrk} vs Pathlength (p)");


Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_PANELPLOTS(FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_ScaledMAP,
                                                        EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_ScaledMAP,
                                                        "h_2d_2ndtrkPathlength_2ndtrkangle_Pion","#theta_{2ndTrk}", "Pathlength" , "Efficieny",
                                                        true, false, "#theta_{2ndTrk} [Deg] vs Pathlength [#frac{g}{cm^{2}}]", "#pi^{#pm}",
                                                        mnv_plot, can3, text_title_pdf2, MakeEffPlotsonly, .4, .4, .015, .015);

Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_Combined_PanelPlots(FullTFile_Map_MC, FullTFile_Map_MC_TRUTH, FullPOT_local_MC_MAP,
                                                                  EmptyTFile_Map_MC, EmptyTFile_Map_MC_TRUTH, EmptyPOT_local_MC_MAP,
                                                                  "h_2d_2ndtrkPathlength_2ndtrkangle_Pion","#theta_{2ndTrk}","Pathlength" ,"Efficieny",
                                                                  true, false, "#theta_{2ndTrk}[Deg] vs Pathlength [#frac{g}{cm^{2}}]", "#pi^{#pm}",
                                                                  mnv_plot, can3, text_title_pdf2, MakeEffPlotsonly, .4, .4, .015, .015);
//
Start_page = Start_page+spacing;
Appendtotxt_2D_Eff_Panel_Combined("Combined_2DPanel_Eff" ,  Panel_pdf_string, Start_page, "\\theta_{2ndTrk} vs Pathlength (\\pi^{\\pm})" );
Appendtotxt_2D_Eff_Panel_Playlists("Combined_2DPanel_Playlists" ,  Panel_pdf_string, Start_page, "\\theta_{2ndTrk} vs Pathlength (\\pi^{\\pm})");


can3 -> Print(text_title_pdf3);

std::cout << std::endl;
std::cout << "Done with Efficieny" << std::endl;


}
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
      hist_TRUE_FULL->AddMissingErrorBandsAndFillWithCV(*hist_TRUE_RECO_FULL);

      MnvH1D *hist_TRUE_EMPTY = (MnvH1D*)EMPTY_playlist.TFILE_PLAYLIST -> Get(histoName_TRUE);
      MnvH1D *hist_TRUE_RECO_EMPTY = (MnvH1D*)EMPTY_playlist.TFILE_PLAYLIST -> Get(histoName_TRUE_RECO);
      hist_TRUE_EMPTY->AddMissingErrorBandsAndFillWithCV(*hist_TRUE_RECO_EMPTY);
      MnvH1D* hist_TRUE_FULL_clone = (MnvH1D*)FULL_playlist.TFILE_PLAYLIST -> Get(histoName_TRUE);
      MnvH1D* hist_TRUE_RECO_FULL_clone = (MnvH1D*)FULL_playlist.TFILE_PLAYLIST -> Get(histoName_TRUE_RECO);
      hist_TRUE_FULL_clone->AddMissingErrorBandsAndFillWithCV(*hist_TRUE_RECO_FULL_clone);

      MnvH1D* hist_TRUE_EMPTY_clone = (MnvH1D*)EMPTY_playlist.TFILE_PLAYLIST -> Get(histoName_TRUE);
      MnvH1D* hist_TRUE_RECO_EMPTY_clone = (MnvH1D*)EMPTY_playlist.TFILE_PLAYLIST -> Get(histoName_TRUE_RECO);
      hist_TRUE_EMPTY_clone->AddMissingErrorBandsAndFillWithCV(*hist_TRUE_RECO_EMPTY_clone);

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
      hist_TRUE_FULL->AddMissingErrorBandsAndFillWithCV(*hist_TRUE_RECO_FULL);

      std::cout<<"hist_TRUE_EMPTY"<<std::endl;
      MnvH1D *hist_TRUE_EMPTY = (MnvH1D*)EMPTY_playlist_TRUTHDEM.TFILE_PLAYLIST -> Get(histoName_TRUE);
      std::cout<<"hist_TRUE_RECO_EMPTY"<<std::endl;
      MnvH1D *hist_TRUE_RECO_EMPTY = (MnvH1D*)EMPTY_playlist_nom.TFILE_PLAYLIST -> Get(histoName_TRUE_RECO);
      hist_TRUE_EMPTY->AddMissingErrorBandsAndFillWithCV(*hist_TRUE_RECO_EMPTY);

      MnvH1D* hist_TRUE_FULL_clone = (MnvH1D*)FULL_playlist_TRUTHDEM.TFILE_PLAYLIST -> Get(histoName_TRUE);
      MnvH1D* hist_TRUE_RECO_FULL_clone = (MnvH1D*)FULL_playlist_nom.TFILE_PLAYLIST -> Get(histoName_TRUE_RECO);
      hist_TRUE_FULL_clone->AddMissingErrorBandsAndFillWithCV(*hist_TRUE_RECO_FULL_clone);

      MnvH1D* hist_TRUE_EMPTY_clone = (MnvH1D*)EMPTY_playlist_TRUTHDEM.TFILE_PLAYLIST -> Get(histoName_TRUE);
      MnvH1D* hist_TRUE_RECO_EMPTY_clone = (MnvH1D*)EMPTY_playlist_nom.TFILE_PLAYLIST -> Get(histoName_TRUE_RECO);
      hist_TRUE_EMPTY_clone->AddMissingErrorBandsAndFillWithCV(*hist_TRUE_RECO_EMPTY_clone);

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
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Full Stats
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH_FullStats( ME_playlist_TFileMAP FullMCMap, ME_playlist_TFileMAP Full_TRUTHDEM_MCMap,
                                                        Pot_MapList FullMC_scalerMap, ME_playlist_TFileMAP EmptyMCMap,
                                                         ME_playlist_TFileMAP Empty_TRUTHDEM_MCMap, Pot_MapList EmptyMC_scalerMap,
   const char *histoName, bool logScale, const char* title, TCanvas *can, const char *pdf , SecondTrkVar playlist_name, bool OnlyEffplot, double ymax  )
  {
    char histoName_TRUE[1024];
    char histoName_TRUE_RECO[1024];
    char Title_His[1024];
    sprintf(histoName_TRUE, "%s_TRUE", histoName);
    sprintf(histoName_TRUE_RECO, "%s_TRUE_RECO", histoName);

    std::string pdf_string(pdf);

    PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
    std::cout<<"Making  FULL_numerator_MC_HistMAP (Inside:Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH_FullStats)"<<std::endl;
    Playlist_MnvH1D_Map FULL_numerator_MC_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullMCMap, histoName_TRUE_RECO );
    std::cout<<"Making  FULL_denominator_MC_HistMAP (Inside:Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH_FullStats)"<<std::endl;
    Playlist_MnvH1D_Map FULL_denominator_MC_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(Full_TRUTHDEM_MCMap, histoName_TRUE );

    AddNumeratorSysErrorsToDenominator_Playlist_MnvH1D_Map(FULL_numerator_MC_HistMAP, FULL_denominator_MC_HistMAP);



    std::cout<<"Making  FULL_numerator_MC_HistScaled (Inside:Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH_FullStats)"<<std::endl;
    Playlist_MnvH1D_Map FULL_numerator_MC_HistScaled =  Scale_MnvH1D_Map_usingPot_MapList(FULL_numerator_MC_HistMAP , FullMC_scalerMap , histoName_TRUE_RECO  );
    std::cout<<"Making  FULL_denominator_MC_HistMAPScaled (Inside:Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH_FullStats)"<<std::endl;
    Playlist_MnvH1D_Map FULL_denominator_MC_HistMAPScaled =  Scale_MnvH1D_Map_usingPot_MapList(FULL_denominator_MC_HistMAP , FullMC_scalerMap , histoName_TRUE  );

    std::cout<<"Making  Empty_numerator_MC_HistMAP (Inside:Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH_FullStats)"<<std::endl;
    Playlist_MnvH1D_Map Empty_numerator_MC_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(EmptyMCMap, histoName_TRUE_RECO );
    std::cout<<"Making  Empty_denominator_MC_HistMAP (Inside:Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH_FullStats)"<<std::endl;
    Playlist_MnvH1D_Map Empty_denominator_MC_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(Empty_TRUTHDEM_MCMap, histoName_TRUE );

    AddNumeratorSysErrorsToDenominator_Playlist_MnvH1D_Map(Empty_numerator_MC_HistMAP, Empty_denominator_MC_HistMAP);


    std::cout<<"Making  Empty_numerator_MC_HistScaled (Inside:Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH_FullStats)"<<std::endl;
    Playlist_MnvH1D_Map Empty_numerator_MC_HistScaled =  Scale_MnvH1D_Map_usingPot_MapList(Empty_numerator_MC_HistMAP , EmptyMC_scalerMap , histoName_TRUE_RECO  );
    std::cout<<"Making  Empty_numerator_MC_HistScaled (Inside:Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH_FullStats)"<<std::endl;
    Playlist_MnvH1D_Map Empty_denominator_MC_HistMAPScaled =  Scale_MnvH1D_Map_usingPot_MapList(Empty_denominator_MC_HistMAP , EmptyMC_scalerMap , histoName_TRUE  );

    typename std::map<ME_helium_Playlists, PlotUtils::MnvH1D*>::const_iterator FULLTRUTHMC;
    typename std::map<ME_helium_Playlists, PlotUtils::MnvH1D*>::const_iterator FULLRECO_TRUTHMC;
    typename std::map<ME_helium_Playlists, PlotUtils::MnvH1D*>::const_iterator EMPTYTRUTHMC;
    typename std::map<ME_helium_Playlists, PlotUtils::MnvH1D*>::const_iterator EMPTYRECO_TRUTHMC;

    for (FULLTRUTHMC = FULL_denominator_MC_HistMAPScaled.begin(), FULLRECO_TRUTHMC = FULL_numerator_MC_HistScaled.begin(); FULLTRUTHMC != FULL_denominator_MC_HistMAPScaled.end(); ++FULLTRUTHMC, ++FULLRECO_TRUTHMC)
    {
      std::string Playlist_Name = GetPlaylist_InitialName(FULLTRUTHMC->first);
      char Playlist_Name_char[Playlist_Name.length()+1];
      strcpy(Playlist_Name_char,Playlist_Name.c_str());

      std::string title_type = GetsecondTrkTitleName(playlist_name);
      char title_type_char[title_type.length()+1];
      strcpy( title_type_char, title_type.c_str());


      std::string Xaxis_title = GetsecondTrk_AXIS_TitleName(playlist_name);
      if(OnlyEffplot==false){
      sprintf(Title_His, "%s (%s)[TRUTH] [%s](Full) ", title_type_char,title, Playlist_Name_char);
      DrawCVAndError_FromHistPointer(FULLTRUTHMC->second, Title_His ,Xaxis_title, "NEvents", pdf_string, false, logScale);
      sprintf(Title_His, "%s (%s) [True+RECO] [%s](Full)", title_type_char,title,Playlist_Name_char);
      DrawCVAndError_FromHistPointer(FULLRECO_TRUTHMC->second, Title_His ,Xaxis_title, "NEvents", pdf_string, false, logScale);
    }

      FULLRECO_TRUTHMC->second->Divide(FULLRECO_TRUTHMC->second, FULLTRUTHMC->second, 1.0,1.0,"");
      sprintf(Title_His, "%s (%s) [%s](Full)", title_type_char, title, Playlist_Name_char);
      DrawCVAndError_FromHistPointer(FULLRECO_TRUTHMC->second, Title_His ,Xaxis_title, "Efficiency",pdf_string, false, logScale , ymax );
    }


    for (EMPTYTRUTHMC=Empty_denominator_MC_HistMAPScaled.begin(), EMPTYRECO_TRUTHMC=Empty_numerator_MC_HistScaled.begin(); EMPTYTRUTHMC != Empty_denominator_MC_HistMAPScaled.end(); ++EMPTYTRUTHMC,++EMPTYRECO_TRUTHMC)
    {
      std::string Playlist_Name = GetPlaylist_InitialName(EMPTYTRUTHMC->first);
      char Playlist_Name_char[Playlist_Name.length()+1];
      strcpy(Playlist_Name_char,Playlist_Name.c_str());

      std::string title_type = GetsecondTrkTitleName(playlist_name);
      char title_type_char[title_type.length()+1];
      strcpy( title_type_char, title_type.c_str());

      std::string Xaxis_title = GetsecondTrk_AXIS_TitleName(playlist_name);
      sprintf(Title_His, "%s (%s) [TRUTH] [%s](Empty) ", title_type_char, title,Playlist_Name_char);
      if(OnlyEffplot==false){
      DrawCVAndError_FromHistPointer(EMPTYTRUTHMC->second, Title_His ,Xaxis_title,"Nevents", pdf_string, false, logScale);
      sprintf(Title_His, "%s (%s) [True+RECO] [%s](Empty)", title_type_char, title,Playlist_Name_char);
      DrawCVAndError_FromHistPointer(EMPTYRECO_TRUTHMC->second, Title_His ,Xaxis_title,"Nevents", pdf_string, false, logScale);
    }

      (EMPTYRECO_TRUTHMC->second)->Divide((EMPTYRECO_TRUTHMC->second), EMPTYTRUTHMC->second, 1.0,1.0,"");
      sprintf(Title_His, "%s (%s)[%s](Empty) ", title_type_char, title, Playlist_Name_char);
      DrawCVAndError_FromHistPointer(EMPTYRECO_TRUTHMC->second, Title_His ,Xaxis_title, "Efficiency", pdf_string, false, logScale, ymax);


    }//End of Empty Loop


}//endl;
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Full Stats
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH_FullStats_COMBINED( ME_playlist_TFileMAP FullMCMap, ME_playlist_TFileMAP Full_TRUTHDEM_MCMap,
                                                                 Pot_MapList FullMC_POTMap, ME_playlist_TFileMAP EmptyMCMap,
                                                               ME_playlist_TFileMAP Empty_TRUTHDEM_MCMap, Pot_MapList EmptyMC_POTMap,
   const char *histoName, bool logScale, const char* title,  TCanvas *can, const char *pdf , SecondTrkVar playlist_name, bool OnlyEffplot, double ymax )
  {
    char histoName_TRUE[1024];
    char histoName_TRUE_RECO[1024];
    char Title_His[1024];
    sprintf(histoName_TRUE, "%s_TRUE", histoName);
    sprintf(histoName_TRUE_RECO, "%s_TRUE_RECO", histoName);
    std::string PDF_string(pdf);

    PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
    CyroStatusPot_MapList POT_MAP = Constuct_TOTALPOT_cryostatusMap(FullMC_POTMap, EmptyMC_POTMap, true);
    double ScaleEmptyToFull_MC = POT_MAP[kMC_FULL] /  POT_MAP[kMC_EMPTY];

    Playlist_MnvH1D_Map FULL_numerator_MC_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullMCMap, histoName_TRUE_RECO );
    Playlist_MnvH1D_Map FULL_denominator_MC_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(Full_TRUTHDEM_MCMap, histoName_TRUE );

    AddNumeratorSysErrorsToDenominator_Playlist_MnvH1D_Map(FULL_numerator_MC_HistMAP, FULL_denominator_MC_HistMAP);


    Playlist_MnvH1D_Map Empty_numerator_MC_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(EmptyMCMap, histoName_TRUE_RECO );
    Playlist_MnvH1D_Map Empty_denominator_MC_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(Empty_TRUTHDEM_MCMap, histoName_TRUE );

    AddNumeratorSysErrorsToDenominator_Playlist_MnvH1D_Map(Empty_numerator_MC_HistMAP, Empty_denominator_MC_HistMAP);


    auto FULL_numerator_Hist = Combine_Hists_fromMAP(FULL_numerator_MC_HistMAP  , kME1F ,"FULL_numerator_Hist");
    auto FULL_denominator_Hist = Combine_Hists_fromMAP(FULL_denominator_MC_HistMAP , kME1F ,"FULL_denominator_Hist");


    auto Empty_numerator_Hist = Combine_Hists_fromMAP(Empty_numerator_MC_HistMAP  , kME1M  ,"Empty_numerator_Hist");
    auto Empty_denominator_Hist = Combine_Hists_fromMAP(Empty_denominator_MC_HistMAP , kME1M  ,"Empty_denominator_Hist");
    Empty_numerator_Hist->Scale(ScaleEmptyToFull_MC);
    Empty_denominator_Hist->Scale(ScaleEmptyToFull_MC);

    auto FULL_EmptyMC_Hist_numerator =(MnvH1D*) FULL_numerator_Hist->Clone("FULL_EmptyMC_Hist_numerator");
    auto FULL_EmptyMC_Hist_denominator =(MnvH1D*) FULL_denominator_Hist->Clone("FULL_EmptyMC_Hist_denominator");



    std::string title_type = GetsecondTrkTitleName(playlist_name);
    char title_type_char[title_type.length()+1];
    strcpy( title_type_char, title_type.c_str());

    std::string Xaxis_title = GetsecondTrk_AXIS_TitleName(playlist_name);
    if(OnlyEffplot==false){
      sprintf(Title_His, "%s (%s)[TRUTH] [combined Full Denom]", title_type_char,title);
      DrawCVAndError_FromHistPointer(FULL_denominator_Hist, Title_His ,Xaxis_title,"Nevents", PDF_string, false, logScale);
      sprintf(Title_His, "%s (%s)[TRUTH+RECO] [combined Full Num]", title_type_char, title);
      DrawCVAndError_FromHistPointer(FULL_numerator_Hist, Title_His ,Xaxis_title,"Nevents", PDF_string, false, logScale);
    }
    FULL_numerator_Hist->Divide(FULL_numerator_Hist, FULL_denominator_Hist, 1.0,1.0,"");
    sprintf(Title_His, "%s (%s) [Combined Full]", title_type_char, title);
    DrawCVAndError_FromHistPointer(FULL_numerator_Hist, Title_His ,Xaxis_title,"Efficiency", PDF_string, false, logScale, ymax);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if(OnlyEffplot==false){
      sprintf(Title_His, "%s (%s) [TRUTH] [combined Empty Denom]", title_type_char,title);
      DrawCVAndError_FromHistPointer(Empty_denominator_Hist, Title_His ,Xaxis_title, "Nevents",PDF_string, false, logScale);
      sprintf(Title_His, "%s  (%s)[TRUTH+RECO] [combined Empty Num]", title_type_char,title);
      DrawCVAndError_FromHistPointer(Empty_numerator_Hist, Title_His ,Xaxis_title, "Nevents", PDF_string, false, logScale);
    }
    Empty_numerator_Hist->Divide(Empty_numerator_Hist, FULL_denominator_Hist, 1.0,1.0,"");
    sprintf(Title_His, "%s [%s] [Combined Empty]", title_type_char, title);
    DrawCVAndError_FromHistPointer(Empty_numerator_Hist, Title_His, Xaxis_title, "Efficiency", PDF_string, false, logScale, ymax);

    FULL_EmptyMC_Hist_numerator->Add(Empty_numerator_Hist,-1);
    FULL_EmptyMC_Hist_denominator->Add(Empty_denominator_Hist,-1);

    if(OnlyEffplot==false){
      sprintf(Title_His, "%s (%s)[TRUTH] [Denominator(F-E)]", title_type_char,title);
      DrawCVAndError_FromHistPointer(FULL_EmptyMC_Hist_denominator, Title_His, Xaxis_title, "Nevents", PDF_string, false,logScale);
      sprintf(Title_His, "%s (%s)[TRUTH+RECO] [Numerator(F-E)]", title_type_char,title);
      DrawCVAndError_FromHistPointer(FULL_EmptyMC_Hist_numerator, Title_His, Xaxis_title, "Nevents", PDF_string, false,logScale);
    }
    FULL_EmptyMC_Hist_numerator->Divide(FULL_EmptyMC_Hist_numerator, FULL_EmptyMC_Hist_denominator, 1.0,1.0,"");
    sprintf(Title_His, "%s (%s) [Combined (F-E)]", title_type_char, title);
    DrawCVAndError_FromHistPointer(FULL_EmptyMC_Hist_numerator, Title_His, Xaxis_title, "Efficiency", PDF_string, false, logScale, ymax);

}//end of function ;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Draw_Efficiency_Muon_FULL_EMPTY_Fullstats(ME_playlist_TFileMAP FullMCMap, ME_playlist_TFileMAP Full_TRUTHDEM_MCMap,
                                               Pot_MapList FullMC_scalerMap, ME_playlist_TFileMAP EmptyMCMap,
                                               ME_playlist_TFileMAP Empty_TRUTHDEM_MCMap, Pot_MapList EmptyMC_scalerMap,
                                               const char *histoName, int logScale, const char* title,
                                               TCanvas *can, const char *pdf , MuonVar playlist_name, bool OnlyEffplot, double yMax ){

      char histoName_TRUE[1024];
      char histoName_TRUE_RECO[1024];
      char Title_His[1024];
      std::string pdf_string(pdf);
      sprintf(histoName_TRUE, "%s_TRUE", histoName);
      sprintf(histoName_TRUE_RECO, "%s_TRUE_RECO", histoName);
      PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);

      std::cout<<"Making  FULL_numerator_MC_HistMAP (Inside:Draw_Efficiency_Muon_FULL_EMPTY_Fullstats)"<<std::endl;
      Playlist_MnvH1D_Map FULL_numerator_MC_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullMCMap, histoName_TRUE_RECO );
      std::cout<<"Making  FULL_denominator_MC_HistMAP (Inside:Draw_Efficiency_Muon_FULL_EMPTY_Fullstats)"<<std::endl;
      Playlist_MnvH1D_Map FULL_denominator_MC_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(Full_TRUTHDEM_MCMap, histoName_TRUE );

      AddNumeratorSysErrorsToDenominator_Playlist_MnvH1D_Map(FULL_numerator_MC_HistMAP, FULL_denominator_MC_HistMAP);

      std::cout<<"Making  FULL_numerator_MC_HistScaled (Inside:Draw_Efficiency_Muon_FULL_EMPTY_Fullstats)"<<std::endl;
      Playlist_MnvH1D_Map FULL_numerator_MC_HistScaled =  Scale_MnvH1D_Map_usingPot_MapList(FULL_numerator_MC_HistMAP , FullMC_scalerMap , histoName_TRUE_RECO  );
      std::cout<<"Making  FULL_denominator_MC_HistMAPScaled (Inside:Draw_Efficiency_Muon_FULL_EMPTY_Fullstats)"<<std::endl;
      Playlist_MnvH1D_Map FULL_denominator_MC_HistMAPScaled =  Scale_MnvH1D_Map_usingPot_MapList(FULL_denominator_MC_HistMAP , FullMC_scalerMap , histoName_TRUE  );

      std::cout<<"Making  Empty_numerator_MC_HistMAP (Inside:Draw_Efficiency_Muon_FULL_EMPTY_Fullstats)"<<std::endl;
      Playlist_MnvH1D_Map Empty_numerator_MC_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(EmptyMCMap, histoName_TRUE_RECO );
      std::cout<<"Making  Empty_denominator_MC_HistMAP (Inside:Draw_Efficiency_Muon_FULL_EMPTY_Fullstats)"<<std::endl;
      Playlist_MnvH1D_Map Empty_denominator_MC_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(Empty_TRUTHDEM_MCMap, histoName_TRUE );

      AddNumeratorSysErrorsToDenominator_Playlist_MnvH1D_Map(Empty_numerator_MC_HistMAP, Empty_denominator_MC_HistMAP);


      std::cout<<"Making  Empty_numerator_MC_HistScaled (Inside:Draw_Efficiency_Muon_FULL_EMPTY_Fullstats)"<<std::endl;
      Playlist_MnvH1D_Map Empty_numerator_MC_HistScaled =  Scale_MnvH1D_Map_usingPot_MapList(Empty_numerator_MC_HistMAP , EmptyMC_scalerMap , histoName_TRUE_RECO  );
      std::cout<<"Making  Empty_numerator_MC_HistScaled (Inside:Draw_Efficiency_Muon_FULL_EMPTY_Fullstats)"<<std::endl;
      Playlist_MnvH1D_Map Empty_denominator_MC_HistMAPScaled =  Scale_MnvH1D_Map_usingPot_MapList(Empty_denominator_MC_HistMAP , EmptyMC_scalerMap , histoName_TRUE  );

      typename std::map<ME_helium_Playlists, PlotUtils::MnvH1D*>::const_iterator FULLTRUTHMC;
      typename std::map<ME_helium_Playlists, PlotUtils::MnvH1D*>::const_iterator FULLRECO_TRUTHMC;
      typename std::map<ME_helium_Playlists, PlotUtils::MnvH1D*>::const_iterator EMPTYTRUTHMC;
      typename std::map<ME_helium_Playlists, PlotUtils::MnvH1D*>::const_iterator EMPTYRECO_TRUTHMC;

      for (FULLTRUTHMC = FULL_denominator_MC_HistMAPScaled.begin(), FULLRECO_TRUTHMC = FULL_numerator_MC_HistScaled.begin(); FULLTRUTHMC != FULL_denominator_MC_HistMAPScaled.end(); ++FULLTRUTHMC, ++FULLRECO_TRUTHMC)
      {
        std::string Playlist_Name = GetPlaylist_InitialName(FULLTRUTHMC->first);
        char Playlist_Name_char[Playlist_Name.length()+1];
        strcpy(Playlist_Name_char,Playlist_Name.c_str());


        std::string title_type = GetMuonVarTitleName(playlist_name);
        char title_type_char[title_type.length()+1];
        strcpy( title_type_char, title_type.c_str());

        //FULLTRUTHMC->second->AddMissingErrorBandsAndFillWithCV(*FULLRECO_TRUTHMC->second);
        std::string Xaxis_title = GetMuonVarAXISName(playlist_name);
        if(OnlyEffplot==false){
        sprintf(Title_His, "%s (%s)[TRUTH] [%s](Full) ", title_type_char,title, Playlist_Name_char);
        DrawCVAndError_FromHistPointer(FULLTRUTHMC->second, Title_His ,Xaxis_title, "NEvents", pdf_string, false, logScale);
        sprintf(Title_His, "%s (%s) [True+RECO] [%s](Full)", title_type_char,title,Playlist_Name_char);
        DrawCVAndError_FromHistPointer(FULLRECO_TRUTHMC->second, Title_His ,Xaxis_title, "NEvents", pdf_string, false, logScale);
      }

        //FULLRECO_TRUTHMC->second->Divide(FULLRECO_TRUTHMC->second, FULLTRUTHMC->second, 1.0,1.0,"");
        sprintf(Title_His, "Efficiency %s (%s)  [%s](Full)", title_type_char, title, Playlist_Name_char);
        DrawCVAndError_FromHistPointer(FULLRECO_TRUTHMC->second, Title_His ,Xaxis_title, "Efficiency",pdf_string, false, logScale , yMax );
      }


          for (EMPTYTRUTHMC=Empty_denominator_MC_HistMAPScaled.begin(), EMPTYRECO_TRUTHMC=Empty_numerator_MC_HistScaled.begin(); EMPTYTRUTHMC != Empty_denominator_MC_HistMAPScaled.end(); ++EMPTYTRUTHMC,++EMPTYRECO_TRUTHMC)
          {
            std::string Playlist_Name = GetPlaylist_InitialName(EMPTYTRUTHMC->first);
            char Playlist_Name_char[Playlist_Name.length()+1];
            strcpy(Playlist_Name_char,Playlist_Name.c_str());

            std::string title_type = GetMuonVarTitleName(playlist_name);
            char title_type_char[title_type.length()+1];
            strcpy( title_type_char, title_type.c_str());

            std::string Xaxis_title = GetMuonVarAXISName(playlist_name);
            sprintf(Title_His, "%s (%s) [TRUTH] [%s](Empty) ", title_type_char, title,Playlist_Name_char);
            //EMPTYTRUTHMC->second->AddMissingErrorBandsAndFillWithCV(*EMPTYRECO_TRUTHMC->second);
            if(OnlyEffplot==false){
            DrawCVAndError_FromHistPointer(EMPTYTRUTHMC->second, Title_His ,Xaxis_title,"Nevents", pdf_string, false, logScale);
            sprintf(Title_His, "%s (%s) [True+RECO] [%s](Empty)", title_type_char, title,Playlist_Name_char);
            DrawCVAndError_FromHistPointer(EMPTYRECO_TRUTHMC->second, Title_His ,Xaxis_title,"Nevents", pdf_string, false, logScale);
          }

            (EMPTYRECO_TRUTHMC->second)->Divide((EMPTYRECO_TRUTHMC->second), EMPTYTRUTHMC->second, 1.0,1.0,"");
            sprintf(Title_His, "Efficiency %s (%s)[%s](Empty) ", title_type_char, title, Playlist_Name_char);
            DrawCVAndError_FromHistPointer(EMPTYRECO_TRUTHMC->second, Title_His ,Xaxis_title, "Efficiency", pdf_string, false, logScale, yMax);


          }//End of Empty Loop




}//endl;


void Draw_Efficiency_Muon_FULL_EMPTY_Fullstats_Combined(ME_playlist_TFileMAP FullMCMap, ME_playlist_TFileMAP Full_TRUTHDEM_MCMap,
                                                      Pot_MapList FullMC_POTMap, ME_playlist_TFileMAP EmptyMCMap,
                                                      ME_playlist_TFileMAP Empty_TRUTHDEM_MCMap, Pot_MapList EmptyMC_POTMap,
                                                      const char *histoName, int logScale, const char* title,
                                                      TCanvas *can, const char *pdf , MuonVar playlist_name, bool OnlyEffplot , double yMax ){

      char histoName_TRUE[1024];
      char histoName_TRUE_RECO[1024];
      char Title_His[1024];

      sprintf(histoName_TRUE, "%s_TRUE", histoName);
      sprintf(histoName_TRUE_RECO, "%s_TRUE_RECO", histoName);
      std::string PDF_string(pdf);

      CyroStatusPot_MapList POT_MAP = Constuct_TOTALPOT_cryostatusMap(FullMC_POTMap, EmptyMC_POTMap, true);
      double ScaleEmptyToFull_MC = POT_MAP[kMC_FULL] /  POT_MAP[kMC_EMPTY];
      Playlist_MnvH1D_Map FULL_numerator_MC_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullMCMap, histoName_TRUE_RECO );
      Playlist_MnvH1D_Map FULL_denominator_MC_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(Full_TRUTHDEM_MCMap, histoName_TRUE );

      AddNumeratorSysErrorsToDenominator_Playlist_MnvH1D_Map(FULL_numerator_MC_HistMAP , FULL_denominator_MC_HistMAP);


      Playlist_MnvH1D_Map Empty_numerator_MC_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(EmptyMCMap, histoName_TRUE_RECO );
      Playlist_MnvH1D_Map Empty_denominator_MC_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(Empty_TRUTHDEM_MCMap, histoName_TRUE );


      AddNumeratorSysErrorsToDenominator_Playlist_MnvH1D_Map(Empty_numerator_MC_HistMAP , Empty_denominator_MC_HistMAP);


      auto FULL_numerator_Hist = Combine_Hists_fromMAP(FULL_numerator_MC_HistMAP  , kME1F ,"FULL_numerator_Hist");
      auto FULL_denominator_Hist = Combine_Hists_fromMAP(FULL_denominator_MC_HistMAP , kME1F ,"FULL_denominator_Hist");


      auto Empty_numerator_Hist = Combine_Hists_fromMAP(Empty_numerator_MC_HistMAP  , kME1M  ,"Empty_numerator_Hist");
      auto Empty_denominator_Hist = Combine_Hists_fromMAP(Empty_denominator_MC_HistMAP , kME1M  ,"Empty_denominator_Hist");
      Empty_numerator_Hist->Scale(ScaleEmptyToFull_MC);
      Empty_denominator_Hist->Scale(ScaleEmptyToFull_MC);

      auto FULL_EmptyMC_Hist_numerator =(MnvH1D*) FULL_numerator_Hist->Clone("FULL_EmptyMC_Hist_numerator");
      auto FULL_EmptyMC_Hist_denominator =(MnvH1D*) FULL_denominator_Hist->Clone("FULL_EmptyMC_Hist_denominator");
      std::string title_type = GetMuonVarTitleName(playlist_name);
      char title_type_char[title_type.length()+1];
      strcpy( title_type_char, title_type.c_str());

      std::string Xaxis_title = GetMuonVarAXISName(playlist_name);
      if(OnlyEffplot==false){
        sprintf(Title_His, "%s (%s)[TRUTH] [combined Full Denom]", title_type_char,title);
        DrawCVAndError_FromHistPointer(FULL_denominator_Hist, Title_His ,Xaxis_title,"Nevents", PDF_string, false, logScale);
        sprintf(Title_His, "%s (%s)[TRUTH+RECO] [combined Full Num]", title_type_char, title);
        DrawCVAndError_FromHistPointer(FULL_numerator_Hist, Title_His ,Xaxis_title,"Nevents", PDF_string, false, logScale);
      }
      FULL_numerator_Hist->Divide(FULL_numerator_Hist, FULL_denominator_Hist, 1.0,1.0,"");
      sprintf(Title_His, "Efficiency %s (%s) (Full Combined) ", title_type_char, title);
      DrawCVAndError_FromHistPointer(FULL_numerator_Hist, Title_His ,Xaxis_title,"Efficiency", PDF_string, false, logScale, yMax);
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////
      if(OnlyEffplot==false){
        sprintf(Title_His, "%s (%s) [TRUTH] [combined Empty Denom]", title_type_char,title);
        DrawCVAndError_FromHistPointer(Empty_denominator_Hist, Title_His ,Xaxis_title, "Nevents",PDF_string, false, logScale);
        sprintf(Title_His, "%s  (%s)[TRUTH+RECO] [combined Empty Num]", title_type_char,title);
        DrawCVAndError_FromHistPointer(Empty_numerator_Hist, Title_His ,Xaxis_title, "Nevents", PDF_string, false, logScale);
      }
      Empty_numerator_Hist->Divide(Empty_numerator_Hist, FULL_denominator_Hist, 1.0,1.0,"");
      sprintf(Title_His, "Efficiency %s (%s) (Empty Combined) ", title_type_char, title);
      DrawCVAndError_FromHistPointer(Empty_numerator_Hist, Title_His, Xaxis_title, "Efficiency", PDF_string, false, logScale , yMax);

      FULL_EmptyMC_Hist_numerator->Add(Empty_numerator_Hist,-1);
      FULL_EmptyMC_Hist_denominator->Add(Empty_denominator_Hist,-1);

      if(OnlyEffplot==false){
        sprintf(Title_His, "%s (%s)[TRUTH] [Denominator(F-E)]", title_type_char,title);
        DrawCVAndError_FromHistPointer(FULL_EmptyMC_Hist_denominator, Title_His, Xaxis_title, "Nevents", PDF_string, false,logScale);
        sprintf(Title_His, "%s (%s)[TRUTH+RECO] [Numerator(F-E)]", title_type_char,title);
        DrawCVAndError_FromHistPointer(FULL_EmptyMC_Hist_numerator, Title_His, Xaxis_title, "Nevents", PDF_string, false,logScale);
      }
      FULL_EmptyMC_Hist_numerator->Divide(FULL_EmptyMC_Hist_numerator, FULL_EmptyMC_Hist_denominator, 1.0,1.0,"");
      sprintf(Title_His, "Efficiency %s (%s) [Combined (F-E)]", title_type_char, title);
      DrawCVAndError_FromHistPointer(FULL_EmptyMC_Hist_numerator, Title_His, Xaxis_title, "Efficiency", PDF_string, false, logScale, yMax);
}//endl;


///////////////////////////////


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

      MnvH2D *hist_TRUE_FULL = (MnvH2D*)FULL_playlist.TFILE_PLAYLIST -> Get(histoName_TRUE);
      MnvH2D *hist_TRUE_RECO_FULL = (MnvH2D*)FULL_playlist.TFILE_PLAYLIST -> Get(histoName_TRUE_RECO);
      hist_TRUE_FULL->AddMissingErrorBandsAndFillWithCV(*hist_TRUE_RECO_FULL);


      MnvH2D *hist_TRUE_EMPTY = (MnvH2D*)EMPTY_playlist.TFILE_PLAYLIST -> Get(histoName_TRUE);
      MnvH2D *hist_TRUE_RECO_EMPTY = (MnvH2D*)EMPTY_playlist.TFILE_PLAYLIST -> Get(histoName_TRUE_RECO);
      hist_TRUE_EMPTY->AddMissingErrorBandsAndFillWithCV(*hist_TRUE_RECO_EMPTY);




      MnvH2D* hist_TRUE_FULL_clone = (MnvH2D*)FULL_playlist.TFILE_PLAYLIST -> Get(histoName_TRUE);
      MnvH2D* hist_TRUE_RECO_FULL_clone = (MnvH2D*)FULL_playlist.TFILE_PLAYLIST -> Get(histoName_TRUE_RECO);
      MnvH2D* hist_TRUE_EMPTY_clone = (MnvH2D*)EMPTY_playlist.TFILE_PLAYLIST -> Get(histoName_TRUE);
      MnvH2D* hist_TRUE_RECO_EMPTY_clone = (MnvH2D*)EMPTY_playlist.TFILE_PLAYLIST -> Get(histoName_TRUE_RECO);

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


void Draw_Efficiency_2D_FULL_EMPTY_TRUTH(PlayList_INFO FULL_playlist_nom,PlayList_INFO FULL_playlist_DemTRUE, PlayList_INFO EMPTY_playlist_nom,PlayList_INFO EMPTY_playlist_DemTRUE, const char *histoName, const char *Xaxis_title, const char *Yaxis_title,
          int logScale, const char* title ,const char* title_type_char , MnvPlotter *plot, TCanvas *can, const char *pdf)
          {

      char histoName_TRUE[1024];
      char histoName_TRUE_RECO[1024];
      char Title_His[1024];

      double FULL_POT = FULL_playlist_nom.Get_Pot();
      double EMPTY_POT = EMPTY_playlist_nom.Get_Pot();
      double Scale_MC = FULL_POT / EMPTY_POT;

      sprintf(histoName_TRUE, "%s_TRUE", histoName);
      sprintf(histoName_TRUE_RECO, "%s_TRUE_RECO", histoName);

      MnvH2D *hist_TRUE_FULL = (MnvH2D*)FULL_playlist_DemTRUE.TFILE_PLAYLIST -> Get(histoName_TRUE);
      MnvH2D *hist_TRUE_RECO_FULL = (MnvH2D*)FULL_playlist_nom.TFILE_PLAYLIST -> Get(histoName_TRUE_RECO);
      MnvH2D *hist_TRUE_EMPTY = (MnvH2D*)EMPTY_playlist_DemTRUE.TFILE_PLAYLIST -> Get(histoName_TRUE);
      MnvH2D *hist_TRUE_RECO_EMPTY = (MnvH2D*)EMPTY_playlist_nom.TFILE_PLAYLIST -> Get(histoName_TRUE_RECO);

      MnvH2D* hist_TRUE_FULL_clone = (MnvH2D*)FULL_playlist_DemTRUE.TFILE_PLAYLIST -> Get(histoName_TRUE);
      MnvH2D* hist_TRUE_RECO_FULL_clone = (MnvH2D*)FULL_playlist_nom.TFILE_PLAYLIST -> Get(histoName_TRUE_RECO);
      MnvH2D* hist_TRUE_EMPTY_clone = (MnvH2D*)EMPTY_playlist_DemTRUE.TFILE_PLAYLIST -> Get(histoName_TRUE);
      MnvH2D* hist_TRUE_RECO_EMPTY_clone = (MnvH2D*)EMPTY_playlist_nom.TFILE_PLAYLIST -> Get(histoName_TRUE_RECO);

      ///Calculation FOR FINAL Eff
      hist_TRUE_EMPTY_clone->Scale(Scale_MC);
      hist_TRUE_RECO_EMPTY_clone->Scale(Scale_MC);
      hist_TRUE_FULL_clone->Add(hist_TRUE_EMPTY_clone,-1);
      hist_TRUE_RECO_FULL_clone->Add(hist_TRUE_RECO_EMPTY_clone,-1);
      hist_TRUE_RECO_FULL_clone->Divide(hist_TRUE_RECO_FULL_clone, hist_TRUE_FULL_clone, 1.0,1.0,"");



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

      sprintf(Title_His, "%s (%s) (True) (%s)(F) ", title, title_type_char, playlistFull_char);
      Draw2DHist_TFILE(FULL_playlist_DemTRUE.TFILE_PLAYLIST, histoName_TRUE, Title_His  , Xaxis_title,Yaxis_title, pdf,can, plot );
      sprintf(Title_His, "%s (%s) (True+RECO) (%s)(F)", title,title_type_char,playlistFull_char);
      Draw2DHist_TFILE(FULL_playlist_nom.TFILE_PLAYLIST, histoName_TRUE_RECO, Title_His , Xaxis_title,Yaxis_title, pdf ,can, plot);
      sprintf(Title_His, "%s (%s) (True) (%s)(E)", title,title_type_char,playlistEmpty_char);
      Draw2DHist_TFILE(EMPTY_playlist_DemTRUE.TFILE_PLAYLIST, histoName_TRUE,Title_His, Xaxis_title,Yaxis_title, pdf,can, plot );
      sprintf(Title_His, "%s (%s) (True+RECO) (%s)(E)", title, title_type_char, playlistEmpty_char);
      Draw2DHist_TFILE(EMPTY_playlist_nom.TFILE_PLAYLIST, histoName_TRUE_RECO,  Title_His , Xaxis_title,Yaxis_title, pdf,can, plot );


      hist_TRUE_RECO_FULL->Divide(hist_TRUE_RECO_FULL, hist_TRUE_FULL, 1.0,1.0,"");
      hist_TRUE_RECO_EMPTY->Divide(hist_TRUE_RECO_EMPTY, hist_TRUE_EMPTY, 1.0,1.0,"");

      sprintf(Title_His, "Eff(FULL) %s (%s)(F) ", title, playlistFull_char);
      //DrawCVAndError_FromHIST(hist_TRUE_RECO_FULL, Title_His ,Xaxis_title,"Efficiency", pdf,true);
      DrawMagration_heatMap(hist_TRUE_RECO_FULL, Xaxis_title,Yaxis_title, Title_His, pdf, can, plot);
      sprintf(Title_His, "Eff(Empty) %s (%s)(E) ", title,playlistEmpty_char);
    //  DrawCVAndError_FromHIST(hist_TRUE_RECO_EMPTY, Title_His ,Xaxis_title,"Efficiency", pdf,true);
      DrawMagration_heatMap(hist_TRUE_RECO_EMPTY, Xaxis_title,Yaxis_title, Title_His, pdf, can, plot);

      sprintf(Title_His, "%s (%s-%s)", title, playlistFull_char,playlistEmpty_char);
      //DrawCVAndError_FromHIST(hist_TRUE_RECO_FULL_clone, Title_His ,Xaxis_title,"Efficiency", pdf,true);
      DrawMagration_heatMap(hist_TRUE_RECO_FULL_clone, Xaxis_title,Yaxis_title, Title_His, pdf, can, plot);


}//endl;

void Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats(ME_playlist_TFileMAP FullMCMap, ME_playlist_TFileMAP Full_TRUTHDEM_MCMap,
                                                        Pot_MapList FullMC_scalerMap, ME_playlist_TFileMAP EmptyMCMap,
                                                         ME_playlist_TFileMAP Empty_TRUTHDEM_MCMap, Pot_MapList EmptyMC_scalerMap,
                                                         const char *histoName, const char *Xaxis_title, const char *Yaxis_title,
                                                         int logScale,const char* title_type_char, const char* title ,MnvPlotter *mnvPlotter, TCanvas *can, const char *pdf, bool OnlyEffplot)
          {

      char histoName_TRUE[1024];
      char histoName_TRUE_RECO[1024];
      char Title_His[1024];


      sprintf(histoName_TRUE, "%s_TRUE", histoName);
      sprintf(histoName_TRUE_RECO, "%s_TRUE_RECO", histoName);

      std::cout<<"Making  FULL_numerator_MC_HistMAP (Inside:Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats()"<<std::endl;
      Playlist_MnvH2D_Map FULL_numerator_MC_HistMAP =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(FullMCMap, histoName_TRUE_RECO );
      std::cout<<"Making  FULL_denominator_MC_HistMAP (Inside:Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats()"<<std::endl;
      Playlist_MnvH2D_Map FULL_denominator_MC_HistMAP =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(Full_TRUTHDEM_MCMap, histoName_TRUE );

      std::cout<<"Making  FULL_numerator_MC_HistScaled (Inside:Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats()"<<std::endl;
      Playlist_MnvH2D_Map FULL_numerator_MC_HistScaled =  Scale_MnvH2D_Map_usingPot_MapList(FULL_numerator_MC_HistMAP , FullMC_scalerMap , histoName_TRUE_RECO  );
      std::cout<<"Making  FULL_denominator_MC_HistMAPScaled (Inside:Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH_FullStats)"<<std::endl;
      Playlist_MnvH2D_Map FULL_denominator_MC_HistMAPScaled =  Scale_MnvH2D_Map_usingPot_MapList(FULL_denominator_MC_HistMAP , FullMC_scalerMap , histoName_TRUE  );

      std::cout<<"Making  Empty_numerator_MC_HistMAP (Inside:Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats()"<<std::endl;
      Playlist_MnvH2D_Map Empty_numerator_MC_HistMAP =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(EmptyMCMap, histoName_TRUE_RECO );
      std::cout<<"Making  Empty_denominator_MC_HistMAP (Inside:Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats()"<<std::endl;
      Playlist_MnvH2D_Map Empty_denominator_MC_HistMAP =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(Empty_TRUTHDEM_MCMap, histoName_TRUE );

      std::cout<<"Making  Empty_numerator_MC_HistScaled (Inside:Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats()"<<std::endl;
      Playlist_MnvH2D_Map Empty_numerator_MC_HistScaled =  Scale_MnvH2D_Map_usingPot_MapList(Empty_numerator_MC_HistMAP , EmptyMC_scalerMap , histoName_TRUE_RECO  );
      std::cout<<"Making  Empty_numerator_MC_HistScaled (Inside:Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats()"<<std::endl;
      Playlist_MnvH2D_Map Empty_denominator_MC_HistMAPScaled =  Scale_MnvH2D_Map_usingPot_MapList(Empty_denominator_MC_HistMAP , EmptyMC_scalerMap , histoName_TRUE  );



      typename std::map<ME_helium_Playlists, PlotUtils::MnvH2D*>::const_iterator FULLTRUTHMC;
      typename std::map<ME_helium_Playlists, PlotUtils::MnvH2D*>::const_iterator FULLRECO_TRUTHMC;
      typename std::map<ME_helium_Playlists, PlotUtils::MnvH2D*>::const_iterator EMPTYTRUTHMC;
      typename std::map<ME_helium_Playlists, PlotUtils::MnvH2D*>::const_iterator EMPTYRECO_TRUTHMC;

      for (FULLTRUTHMC = FULL_denominator_MC_HistMAPScaled.begin(), FULLRECO_TRUTHMC = FULL_numerator_MC_HistScaled.begin(); FULLTRUTHMC != FULL_denominator_MC_HistMAPScaled.end(); ++FULLTRUTHMC, ++FULLRECO_TRUTHMC)
      {
        std::string Playlist_Name = GetPlaylist_InitialName(FULLTRUTHMC->first);
        char Playlist_Name_char[Playlist_Name.length()+1];
        strcpy(Playlist_Name_char,Playlist_Name.c_str());

        if(OnlyEffplot==false){
        sprintf(Title_His, "%s (%s)[TRUTH] [%s](Full) ", title_type_char,title, Playlist_Name_char);
        DrawMagration_heatMap(FULLTRUTHMC->second, Xaxis_title, Yaxis_title, Title_His, pdf, can, mnvPlotter);

        sprintf(Title_His, "%s (%s) [True+RECO] [%s](Full)", title_type_char,title,Playlist_Name_char);
        DrawMagration_heatMap(FULLRECO_TRUTHMC->second, Xaxis_title, Yaxis_title, Title_His, pdf, can, mnvPlotter);
      }

        FULLRECO_TRUTHMC->second->Divide(FULLRECO_TRUTHMC->second, FULLTRUTHMC->second, 1.0,1.0,"");
        sprintf(Title_His, " 2D Efficiency %s (%s)  [%s](Full)", title_type_char, title, Playlist_Name_char);
        DrawMagration_heatMap(FULLRECO_TRUTHMC->second, Xaxis_title, Yaxis_title, Title_His, pdf, can, mnvPlotter);


      }


      for (EMPTYTRUTHMC=Empty_denominator_MC_HistMAPScaled.begin(), EMPTYRECO_TRUTHMC=Empty_numerator_MC_HistScaled.begin(); EMPTYTRUTHMC != Empty_denominator_MC_HistMAPScaled.end(); ++EMPTYTRUTHMC,++EMPTYRECO_TRUTHMC)
      {
        std::string Playlist_Name = GetPlaylist_InitialName(EMPTYTRUTHMC->first);
        char Playlist_Name_char[Playlist_Name.length()+1];
        strcpy(Playlist_Name_char,Playlist_Name.c_str());


        sprintf(Title_His, "%s (%s) [TRUTH] [%s](Empty) ", title_type_char, title,Playlist_Name_char);
        if(OnlyEffplot==false){
        DrawMagration_heatMap(EMPTYTRUTHMC->second, Xaxis_title,Yaxis_title, Title_His, pdf, can, mnvPlotter);

        sprintf(Title_His, "%s (%s) [True+RECO] [%s](Empty)", title_type_char, title,Playlist_Name_char);
        DrawMagration_heatMap(EMPTYRECO_TRUTHMC->second, Xaxis_title,Yaxis_title, Title_His, pdf, can, mnvPlotter);

      }

        (EMPTYRECO_TRUTHMC->second)->Divide((EMPTYRECO_TRUTHMC->second), EMPTYTRUTHMC->second, 1.0,1.0,"");
        sprintf(Title_His, "2D Efficiency %s (%s)[%s](Empty) ", title_type_char, title, Playlist_Name_char);
        DrawMagration_heatMap(EMPTYRECO_TRUTHMC->second, Xaxis_title,Yaxis_title, Title_His, pdf, can, mnvPlotter);


      }//End of Empty Loop

}//endl;
////////////////////////////////////////////
//end
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_PANELPLOTS(ME_playlist_TFileMAP FullMCMap, ME_playlist_TFileMAP Full_TRUTHDEM_MCMap,
                                                              Pot_MapList FullMC_scalerMap, ME_playlist_TFileMAP EmptyMCMap,
                                                              ME_playlist_TFileMAP Empty_TRUTHDEM_MCMap, Pot_MapList EmptyMC_scalerMap,
                                                              const char *histoName, const char *Xaxis_title, const char *Yaxis_title, const char *Zaxis_title,
                                                              bool logScale, bool doBinwidth, const char* title_type_char, const char* title ,
                                                              MnvPlotter *mnvPlotter, TCanvas *can, char *pdf, bool OnlyEffplot , double max_x, double max_y  )
          {

      char histoName_TRUE[1024];
      char histoName_TRUE_RECO[1024];
      char Title_His[1024];
      std::string Xaxis_title_string(Xaxis_title);
      std::string Yaxis_title_string(Yaxis_title);


      sprintf(histoName_TRUE, "%s_TRUE", histoName);
      sprintf(histoName_TRUE_RECO, "%s_TRUE_RECO", histoName);

      std::cout<<"Making  FULL_numerator_MC_HistMAP (Inside:Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_PANELPLOTS)"<<std::endl;
      Playlist_MnvH2D_Map FULL_numerator_MC_HistMAP =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(FullMCMap, histoName_TRUE_RECO );
      std::cout<<"Making  FULL_denominator_MC_HistMAP (Inside:Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_PANELPLOTS)"<<std::endl;
      Playlist_MnvH2D_Map FULL_denominator_MC_HistMAP =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(Full_TRUTHDEM_MCMap, histoName_TRUE );

      std::cout<<"Making  FULL_numerator_MC_HistScaled (Inside:Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_PANELPLOTS)"<<std::endl;
      Playlist_MnvH2D_Map FULL_numerator_MC_HistScaled =  Scale_MnvH2D_Map_usingPot_MapList(FULL_numerator_MC_HistMAP , FullMC_scalerMap , histoName_TRUE_RECO  );
      std::cout<<"Making  FULL_denominator_MC_HistMAPScaled (Inside:Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_PANELPLOTS)"<<std::endl;
      Playlist_MnvH2D_Map FULL_denominator_MC_HistMAPScaled =  Scale_MnvH2D_Map_usingPot_MapList(FULL_denominator_MC_HistMAP , FullMC_scalerMap , histoName_TRUE  );

      std::cout<<"Making  Empty_numerator_MC_HistMAP (Inside:Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_PANELPLOTS)"<<std::endl;
      Playlist_MnvH2D_Map Empty_numerator_MC_HistMAP =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(EmptyMCMap, histoName_TRUE_RECO );
      std::cout<<"Making  Empty_denominator_MC_HistMAP (Inside:Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_PANELPLOTS)"<<std::endl;
      Playlist_MnvH2D_Map Empty_denominator_MC_HistMAP =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(Empty_TRUTHDEM_MCMap, histoName_TRUE );

      std::cout<<"Making  Empty_numerator_MC_HistScaled (Inside:Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_PANELPLOTS)"<<std::endl;
      Playlist_MnvH2D_Map Empty_numerator_MC_HistScaled =  Scale_MnvH2D_Map_usingPot_MapList(Empty_numerator_MC_HistMAP , EmptyMC_scalerMap , histoName_TRUE_RECO  );
      std::cout<<"Making  Empty_numerator_MC_HistScaled (Inside:Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_PANELPLOTS)"<<std::endl;
      Playlist_MnvH2D_Map Empty_denominator_MC_HistMAPScaled =  Scale_MnvH2D_Map_usingPot_MapList(Empty_denominator_MC_HistMAP , EmptyMC_scalerMap , histoName_TRUE  );



      typename std::map<ME_helium_Playlists, PlotUtils::MnvH2D*>::const_iterator FULLTRUTHMC;
      typename std::map<ME_helium_Playlists, PlotUtils::MnvH2D*>::const_iterator FULLRECO_TRUTHMC;
      typename std::map<ME_helium_Playlists, PlotUtils::MnvH2D*>::const_iterator EMPTYTRUTHMC;
      typename std::map<ME_helium_Playlists, PlotUtils::MnvH2D*>::const_iterator EMPTYRECO_TRUTHMC;

      for (FULLTRUTHMC = FULL_denominator_MC_HistMAPScaled.begin(), FULLRECO_TRUTHMC = FULL_numerator_MC_HistScaled.begin(); FULLTRUTHMC != FULL_denominator_MC_HistMAPScaled.end(); ++FULLTRUTHMC, ++FULLRECO_TRUTHMC)
      {
        std::string Playlist_Name = GetPlaylist_InitialName(FULLTRUTHMC->first);
        char Playlist_Name_char[Playlist_Name.length()+1];
        strcpy(Playlist_Name_char,Playlist_Name.c_str());

        if(OnlyEffplot==false){
        sprintf(Title_His, "%s (%s)[TRUTH] [%s](Full) ", title_type_char,title, Playlist_Name_char);
        Draw_2D_Panel_MC_Only_frompointer(FULLTRUTHMC->second, Title_His, "MC Event Rate[Truth]", Xaxis_title_string, Yaxis_title_string, Zaxis_title, max_x , max_y, pdf, doBinwidth, logScale);
        sprintf(Title_His, "%s (%s) [True+RECO] [%s](Full)", title_type_char,title,Playlist_Name_char);
        Draw_2D_Panel_MC_Only_frompointer(FULLRECO_TRUTHMC->second, Title_His, "MC Event Rate[Truth + Reco]", Xaxis_title_string, Yaxis_title_string,Zaxis_title, max_x , max_y, pdf, doBinwidth, logScale);

      }

        FULLRECO_TRUTHMC->second->Divide(FULLRECO_TRUTHMC->second, FULLTRUTHMC->second, 1.0,1.0,"");
        sprintf(Title_His, " 2D Efficiency %s (%s)  [%s](Full)", title_type_char, title, Playlist_Name_char);
        Draw_2D_Panel_MC_Only_frompointer(FULLRECO_TRUTHMC->second, Title_His, "Efficieny", Xaxis_title_string, Yaxis_title_string,Zaxis_title, max_x , max_y, pdf, doBinwidth, logScale);



      }


      for (EMPTYTRUTHMC=Empty_denominator_MC_HistMAPScaled.begin(), EMPTYRECO_TRUTHMC=Empty_numerator_MC_HistScaled.begin(); EMPTYTRUTHMC != Empty_denominator_MC_HistMAPScaled.end(); ++EMPTYTRUTHMC,++EMPTYRECO_TRUTHMC)
      {
        std::string Playlist_Name = GetPlaylist_InitialName(EMPTYTRUTHMC->first);
        char Playlist_Name_char[Playlist_Name.length()+1];
        strcpy(Playlist_Name_char,Playlist_Name.c_str());


        sprintf(Title_His, "%s (%s) [TRUTH] [%s](Empty) ", title_type_char, title,Playlist_Name_char);
        if(OnlyEffplot==false){
        Draw_2D_Panel_MC_Only_frompointer(EMPTYTRUTHMC->second, Title_His, "MC Event Rate[Truth]", Xaxis_title_string, Yaxis_title_string, Zaxis_title, max_x , max_y, pdf, doBinwidth, logScale);


        sprintf(Title_His, "%s (%s) [True+RECO] [%s](Empty)", title_type_char, title,Playlist_Name_char);
        Draw_2D_Panel_MC_Only_frompointer(EMPTYRECO_TRUTHMC->second, Title_His, "MC Event Rate[Truth+RECO]", Xaxis_title_string, Yaxis_title_string, Zaxis_title, max_x, max_y, pdf, doBinwidth, logScale);


      }

        (EMPTYRECO_TRUTHMC->second)->Divide((EMPTYRECO_TRUTHMC->second), EMPTYTRUTHMC->second, 1.0,1.0,"");
        sprintf(Title_His, "2D Efficiency %s (%s)[%s](Empty) ", title_type_char, title, Playlist_Name_char);
        Draw_2D_Panel_MC_Only_frompointer(EMPTYRECO_TRUTHMC->second, Title_His, "Efficiency", Xaxis_title_string, Yaxis_title_string,Zaxis_title, max_x, max_y, pdf, doBinwidth, logScale);


      }//End of Empty Loop

}//endl;
////////////////////////////////////////////////////////////////
void Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_PANELPLOTS(ME_playlist_TFileMAP FullMCMap, ME_playlist_TFileMAP Full_TRUTHDEM_MCMap,
                                                              Pot_MapList FullMC_scalerMap, ME_playlist_TFileMAP EmptyMCMap,
                                                              ME_playlist_TFileMAP Empty_TRUTHDEM_MCMap, Pot_MapList EmptyMC_scalerMap,
                                                              const char *histoName, const char *Xaxis_title, const char *Yaxis_title, const char *Zaxis_title,
                                                              bool logScale, bool doBinwidth, const char* title_type_char, const char* title ,
                                                              MnvPlotter *mnvPlotter, TCanvas *can, char *pdf, bool OnlyEffplot , double max_x, double max_y, double txt_sizeY , double txt_sizeX  )
          {

      char histoName_TRUE[1024];
      char histoName_TRUE_RECO[1024];
      char Title_His[1024];
      std::string Xaxis_title_string(Xaxis_title);
      std::string Yaxis_title_string(Yaxis_title);


      sprintf(histoName_TRUE, "%s_TRUE", histoName);
      sprintf(histoName_TRUE_RECO, "%s_TRUE_RECO", histoName);

      std::cout<<"Making  FULL_numerator_MC_HistMAP (Inside:Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_PANELPLOTS)"<<std::endl;
      Playlist_MnvH2D_Map FULL_numerator_MC_HistMAP =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(FullMCMap, histoName_TRUE_RECO );
      std::cout<<"Making  FULL_denominator_MC_HistMAP (Inside:Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_PANELPLOTS)"<<std::endl;
      Playlist_MnvH2D_Map FULL_denominator_MC_HistMAP =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(Full_TRUTHDEM_MCMap, histoName_TRUE );

      std::cout<<"Making  FULL_numerator_MC_HistScaled (Inside:Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_PANELPLOTS)"<<std::endl;
      Playlist_MnvH2D_Map FULL_numerator_MC_HistScaled =  Scale_MnvH2D_Map_usingPot_MapList(FULL_numerator_MC_HistMAP , FullMC_scalerMap , histoName_TRUE_RECO  );
      std::cout<<"Making  FULL_denominator_MC_HistMAPScaled (Inside:Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_PANELPLOTS)"<<std::endl;
      Playlist_MnvH2D_Map FULL_denominator_MC_HistMAPScaled =  Scale_MnvH2D_Map_usingPot_MapList(FULL_denominator_MC_HistMAP , FullMC_scalerMap , histoName_TRUE  );

      std::cout<<"Making  Empty_numerator_MC_HistMAP (Inside:Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_PANELPLOTS)"<<std::endl;
      Playlist_MnvH2D_Map Empty_numerator_MC_HistMAP =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(EmptyMCMap, histoName_TRUE_RECO );
      std::cout<<"Making  Empty_denominator_MC_HistMAP (Inside:Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_PANELPLOTS)"<<std::endl;
      Playlist_MnvH2D_Map Empty_denominator_MC_HistMAP =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(Empty_TRUTHDEM_MCMap, histoName_TRUE );

      std::cout<<"Making  Empty_numerator_MC_HistScaled (Inside:Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_PANELPLOTS)"<<std::endl;
      Playlist_MnvH2D_Map Empty_numerator_MC_HistScaled =  Scale_MnvH2D_Map_usingPot_MapList(Empty_numerator_MC_HistMAP , EmptyMC_scalerMap , histoName_TRUE_RECO  );
      std::cout<<"Making  Empty_numerator_MC_HistScaled (Inside:Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_PANELPLOTS)"<<std::endl;
      Playlist_MnvH2D_Map Empty_denominator_MC_HistMAPScaled =  Scale_MnvH2D_Map_usingPot_MapList(Empty_denominator_MC_HistMAP , EmptyMC_scalerMap , histoName_TRUE  );



      typename std::map<ME_helium_Playlists, PlotUtils::MnvH2D*>::const_iterator FULLTRUTHMC;
      typename std::map<ME_helium_Playlists, PlotUtils::MnvH2D*>::const_iterator FULLRECO_TRUTHMC;
      typename std::map<ME_helium_Playlists, PlotUtils::MnvH2D*>::const_iterator EMPTYTRUTHMC;
      typename std::map<ME_helium_Playlists, PlotUtils::MnvH2D*>::const_iterator EMPTYRECO_TRUTHMC;

      for (FULLTRUTHMC = FULL_denominator_MC_HistMAPScaled.begin(), FULLRECO_TRUTHMC = FULL_numerator_MC_HistScaled.begin(); FULLTRUTHMC != FULL_denominator_MC_HistMAPScaled.end(); ++FULLTRUTHMC, ++FULLRECO_TRUTHMC)
      {
        std::string Playlist_Name = GetPlaylist_InitialName(FULLTRUTHMC->first);
        char Playlist_Name_char[Playlist_Name.length()+1];
        strcpy(Playlist_Name_char,Playlist_Name.c_str());

        if(OnlyEffplot==false){
        sprintf(Title_His, "%s (%s)[TRUTH] [%s](Full) ", title_type_char,title, Playlist_Name_char);
        Draw_2D_Panel_MC_Only_frompointer(FULLTRUTHMC->second, Title_His, "MC Event Rate[Truth]", Xaxis_title_string, Yaxis_title_string, Zaxis_title, max_x , max_y, pdf, doBinwidth, logScale, txt_sizeX, txt_sizeY);
        sprintf(Title_His, "%s (%s) [True+RECO] [%s](Full)", title_type_char,title,Playlist_Name_char);
        Draw_2D_Panel_MC_Only_frompointer(FULLRECO_TRUTHMC->second, Title_His, "MC Event Rate[Truth + Reco]", Xaxis_title_string, Yaxis_title_string,Zaxis_title, max_x , max_y, pdf, doBinwidth, logScale, txt_sizeX, txt_sizeY);

      }

        FULLRECO_TRUTHMC->second->Divide(FULLRECO_TRUTHMC->second, FULLTRUTHMC->second, 1.0,1.0,"");
        sprintf(Title_His, " 2D Efficiency %s (%s)  [%s](Full)", title_type_char, title, Playlist_Name_char);
        Draw_2D_Panel_MC_Only_frompointer(FULLRECO_TRUTHMC->second, Title_His, "Efficieny", Xaxis_title_string, Yaxis_title_string,Zaxis_title, max_x , max_y, pdf, doBinwidth, logScale, txt_sizeX, txt_sizeY);



      }


      for (EMPTYTRUTHMC=Empty_denominator_MC_HistMAPScaled.begin(), EMPTYRECO_TRUTHMC=Empty_numerator_MC_HistScaled.begin(); EMPTYTRUTHMC != Empty_denominator_MC_HistMAPScaled.end(); ++EMPTYTRUTHMC,++EMPTYRECO_TRUTHMC)
      {
        std::string Playlist_Name = GetPlaylist_InitialName(EMPTYTRUTHMC->first);
        char Playlist_Name_char[Playlist_Name.length()+1];
        strcpy(Playlist_Name_char,Playlist_Name.c_str());


        sprintf(Title_His, "%s (%s) [TRUTH] [%s](Empty) ", title_type_char, title,Playlist_Name_char);
        if(OnlyEffplot==false){
        Draw_2D_Panel_MC_Only_frompointer(EMPTYTRUTHMC->second, Title_His, "MC Event Rate[Truth]", Xaxis_title_string, Yaxis_title_string, Zaxis_title, max_x , max_y, pdf, doBinwidth, logScale, txt_sizeX, txt_sizeY);


        sprintf(Title_His, "%s (%s) [True+RECO] [%s](Empty)", title_type_char, title,Playlist_Name_char);
        Draw_2D_Panel_MC_Only_frompointer(EMPTYRECO_TRUTHMC->second, Title_His, "MC Event Rate[Truth+RECO]", Xaxis_title_string, Yaxis_title_string, Zaxis_title, max_x, max_y, pdf, doBinwidth, logScale, txt_sizeX, txt_sizeY);


      }

        (EMPTYRECO_TRUTHMC->second)->Divide((EMPTYRECO_TRUTHMC->second), EMPTYTRUTHMC->second, 1.0,1.0,"");
        sprintf(Title_His, "2D Efficiency %s (%s)[%s](Empty) ", title_type_char, title, Playlist_Name_char);
        Draw_2D_Panel_MC_Only_frompointer(EMPTYRECO_TRUTHMC->second, Title_His, "Efficiency", Xaxis_title_string, Yaxis_title_string,Zaxis_title, max_x, max_y, pdf, doBinwidth, logScale, txt_sizeX, txt_sizeY);


      }//End of Empty Loop

}//endl;
/////////////////////////////////////////////
// end of function
////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////
// end of function
////////////////////////////////////////////////////////////////////////////////////////////////////////
void Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_Combined(ME_playlist_TFileMAP FullMCMap, ME_playlist_TFileMAP Full_TRUTHDEM_MCMap,
                                                                 Pot_MapList FullMC_POTMap, ME_playlist_TFileMAP EmptyMCMap,
                                                               ME_playlist_TFileMAP Empty_TRUTHDEM_MCMap, Pot_MapList EmptyMC_POTMap,
                                                         const char *histoName, const char *Xaxis_title, const char *Yaxis_title,
                                                         int logScale,const char* title_type_char, const char* title ,MnvPlotter *mnvPlotter, TCanvas *can, const char *pdf, bool OnlyEffplot)
          {

      char histoName_TRUE[1024];
      char histoName_TRUE_RECO[1024];
      char Title_His[1024];


      sprintf(histoName_TRUE, "%s_TRUE", histoName);
      sprintf(histoName_TRUE_RECO, "%s_TRUE_RECO", histoName);


      CyroStatusPot_MapList POT_MAP = Constuct_TOTALPOT_cryostatusMap(FullMC_POTMap, EmptyMC_POTMap, true);
      double ScaleEmptyToFull_MC = POT_MAP[kMC_FULL] /  POT_MAP[kMC_EMPTY];
      Playlist_MnvH2D_Map FULL_numerator_MC_HistMAP =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(FullMCMap, histoName_TRUE_RECO );
      Playlist_MnvH2D_Map FULL_denominator_MC_HistMAP =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(Full_TRUTHDEM_MCMap, histoName_TRUE );

      Playlist_MnvH2D_Map Empty_numerator_MC_HistMAP =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(EmptyMCMap, histoName_TRUE_RECO );
      Playlist_MnvH2D_Map Empty_denominator_MC_HistMAP =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(Empty_TRUTHDEM_MCMap, histoName_TRUE );


      auto FULL_numerator_Hist = Combine_2DHists_fromMAP(FULL_numerator_MC_HistMAP  , kME1F ,"FULL_numerator_Hist");
      auto FULL_denominator_Hist = Combine_2DHists_fromMAP(FULL_denominator_MC_HistMAP , kME1F ,"FULL_denominator_Hist");

      auto Empty_numerator_Hist = Combine_2DHists_fromMAP(Empty_numerator_MC_HistMAP  , kME1M  ,"Empty_numerator_Hist");
      auto Empty_denominator_Hist = Combine_2DHists_fromMAP(Empty_denominator_MC_HistMAP , kME1M  ,"Empty_denominator_Hist");
      Empty_numerator_Hist->Scale(ScaleEmptyToFull_MC);
      Empty_denominator_Hist->Scale(ScaleEmptyToFull_MC);

      auto FULL_EmptyMC_Hist_numerator =(MnvH2D*) FULL_numerator_Hist->Clone("FULL_EmptyMC_Hist_numerator");
      auto FULL_EmptyMC_Hist_denominator =(MnvH2D*) FULL_denominator_Hist->Clone("FULL_EmptyMC_Hist_denominator");

      if(OnlyEffplot==false){
        sprintf(Title_His, "%s (%s)[TRUTH] [combined Full Denom]", title_type_char,title);
        DrawMagration_heatMap(FULL_denominator_Hist, Xaxis_title, Yaxis_title, Title_His, pdf, can, mnvPlotter);
        sprintf(Title_His, "%s (%s)[TRUTH+RECO] [combined Full Num]", title_type_char, title);
        DrawMagration_heatMap(FULL_numerator_Hist, Xaxis_title, Yaxis_title, Title_His, pdf, can, mnvPlotter);

      }
      FULL_numerator_Hist->Divide(FULL_numerator_Hist, FULL_denominator_Hist, 1.0,1.0,"");
      sprintf(Title_His, "2D Efficiency %s (%s) (Full Combined) ", title_type_char, title);
      DrawMagration_heatMap(FULL_numerator_Hist, Xaxis_title, Yaxis_title, Title_His, pdf, can, mnvPlotter);


      ////////////////////////////////////////////////////////////////////////////////////////////////////////////
      if(OnlyEffplot==false){
        sprintf(Title_His, "%s (%s) [TRUTH] [combined Empty Denom]", title_type_char,title);
        DrawMagration_heatMap(Empty_denominator_Hist, Xaxis_title, Yaxis_title, Title_His, pdf, can, mnvPlotter);

        sprintf(Title_His, "%s  (%s)[TRUTH+RECO] [combined Empty Num]", title_type_char,title);
        DrawMagration_heatMap(Empty_numerator_Hist, Xaxis_title, Yaxis_title, Title_His, pdf, can, mnvPlotter);

      }
      Empty_numerator_Hist->Divide(Empty_numerator_Hist, FULL_denominator_Hist, 1.0,1.0,"");
      sprintf(Title_His, "2D Efficiency %s (%s) (Empty Combined) ", title_type_char, title);
      DrawMagration_heatMap(Empty_numerator_Hist, Xaxis_title, Yaxis_title, Title_His, pdf, can, mnvPlotter);
      FULL_EmptyMC_Hist_numerator->Add(Empty_numerator_Hist,-1);
      FULL_EmptyMC_Hist_denominator->Add(Empty_denominator_Hist,-1);

      if(OnlyEffplot==false){
        sprintf(Title_His, "%s (%s)[TRUTH] [Denominator(F-E)]", title_type_char,title);
        DrawMagration_heatMap(FULL_EmptyMC_Hist_denominator, Xaxis_title, Yaxis_title, Title_His, pdf, can, mnvPlotter);

        sprintf(Title_His, "%s (%s)[TRUTH+RECO] [Numerator(F-E)]", title_type_char,title);
        DrawMagration_heatMap(FULL_EmptyMC_Hist_numerator, Xaxis_title, Yaxis_title, Title_His, pdf, can, mnvPlotter);

      }
      FULL_EmptyMC_Hist_numerator->Divide(FULL_EmptyMC_Hist_numerator, FULL_EmptyMC_Hist_denominator, 1.0,1.0,"");
      sprintf(Title_His, "2D Efficiency %s (%s) [Combined (F-E)]", title_type_char, title);
      DrawMagration_heatMap(FULL_EmptyMC_Hist_numerator, Xaxis_title, Yaxis_title, Title_His, pdf, can, mnvPlotter);


}//endl;
/////////////////////////////////////////////
// end of function
////////////////////////////////////////////////////////////////////////////////////////////////////////
void Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_Combined_PanelPlots(ME_playlist_TFileMAP FullMCMap, ME_playlist_TFileMAP Full_TRUTHDEM_MCMap,
                                                                       Pot_MapList FullMC_POTMap, ME_playlist_TFileMAP EmptyMCMap,
                                                                       ME_playlist_TFileMAP Empty_TRUTHDEM_MCMap, Pot_MapList EmptyMC_POTMap,
                                                                       const char *histoName, const char *Xaxis_title, const char *Yaxis_title,const char * Zaxis_title,
                                                                       bool logScale, bool doBinwidth, const char* title_type_char, const char* title ,MnvPlotter *mnvPlotter,
                                                                       TCanvas *can,  char *pdf, bool OnlyEffplot, double max_x, double max_y)
          {

      char histoName_TRUE[1024];
      char histoName_TRUE_RECO[1024];
      char Title_His[1024];
      std::string Xaxis_title_string(Xaxis_title);
      std::string Yaxis_title_string(Yaxis_title);

      sprintf(histoName_TRUE, "%s_TRUE", histoName);
      sprintf(histoName_TRUE_RECO, "%s_TRUE_RECO", histoName);


      CyroStatusPot_MapList POT_MAP = Constuct_TOTALPOT_cryostatusMap(FullMC_POTMap, EmptyMC_POTMap, true);
      double ScaleEmptyToFull_MC = POT_MAP[kMC_FULL] /  POT_MAP[kMC_EMPTY];
      Playlist_MnvH2D_Map FULL_numerator_MC_HistMAP =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(FullMCMap, histoName_TRUE_RECO );
      Playlist_MnvH2D_Map FULL_denominator_MC_HistMAP =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(Full_TRUTHDEM_MCMap, histoName_TRUE );

      Playlist_MnvH2D_Map Empty_numerator_MC_HistMAP =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(EmptyMCMap, histoName_TRUE_RECO );
      Playlist_MnvH2D_Map Empty_denominator_MC_HistMAP =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(Empty_TRUTHDEM_MCMap, histoName_TRUE );


      auto FULL_numerator_Hist = Combine_2DHists_fromMAP(FULL_numerator_MC_HistMAP  , kME1F ,"FULL_numerator_Hist");
      auto FULL_denominator_Hist = Combine_2DHists_fromMAP(FULL_denominator_MC_HistMAP , kME1F ,"FULL_denominator_Hist");

      auto Empty_numerator_Hist = Combine_2DHists_fromMAP(Empty_numerator_MC_HistMAP  , kME1M  ,"Empty_numerator_Hist");
      auto Empty_denominator_Hist = Combine_2DHists_fromMAP(Empty_denominator_MC_HistMAP , kME1M  ,"Empty_denominator_Hist");
      Empty_numerator_Hist->Scale(ScaleEmptyToFull_MC);
      Empty_denominator_Hist->Scale(ScaleEmptyToFull_MC);

      auto FULL_EmptyMC_Hist_numerator =(MnvH2D*) FULL_numerator_Hist->Clone("FULL_EmptyMC_Hist_numerator");
      auto FULL_EmptyMC_Hist_denominator =(MnvH2D*) FULL_denominator_Hist->Clone("FULL_EmptyMC_Hist_denominator");

      if(OnlyEffplot==false){
        sprintf(Title_His, "%s (%s)[TRUTH] [combined Full Denom]", title_type_char,title);
        Draw_2D_Panel_MC_Only_frompointer(FULL_denominator_Hist, Title_His, "MC", Xaxis_title_string, Yaxis_title_string, Zaxis_title, max_x , max_y, pdf, doBinwidth, logScale );

        sprintf(Title_His, "%s (%s)[TRUTH+RECO] [combined Full Num]", title_type_char, title);
        Draw_2D_Panel_MC_Only_frompointer(FULL_numerator_Hist, Title_His, "MC", Xaxis_title_string, Yaxis_title_string, Zaxis_title, max_x , max_y, pdf, doBinwidth, logScale);

      }
      FULL_numerator_Hist->Divide(FULL_numerator_Hist, FULL_denominator_Hist, 1.0,1.0,"");
      sprintf(Title_His, "2D Efficiency %s (%s) (Full Combined) ", title_type_char, title);
      Draw_2D_Panel_MC_Only_frompointer(FULL_numerator_Hist, Title_His, "MC", Xaxis_title_string, Yaxis_title_string, Zaxis_title, max_x , max_y, pdf, doBinwidth, logScale);


      ////////////////////////////////////////////////////////////////////////////////////////////////////////////
      if(OnlyEffplot==false){
        sprintf(Title_His, "%s (%s) [TRUTH] [combined Empty Denom]", title_type_char,title);
        Draw_2D_Panel_MC_Only_frompointer(Empty_denominator_Hist, Title_His, "MC", Xaxis_title_string, Yaxis_title_string, Zaxis_title, max_x, max_y, pdf, doBinwidth, logScale);

        sprintf(Title_His, "%s  (%s)[TRUTH+RECO] [combined Empty Num]", title_type_char,title);
        Draw_2D_Panel_MC_Only_frompointer(Empty_numerator_Hist, Title_His, "MC", Xaxis_title_string, Yaxis_title_string, Zaxis_title, max_x, max_y, pdf, doBinwidth, logScale);

      }
      Empty_numerator_Hist->Divide(Empty_numerator_Hist, FULL_denominator_Hist, 1.0,1.0,"");
      sprintf(Title_His, "2D Efficiency %s (%s) (Empty Combined) ", title_type_char, title);
      Draw_2D_Panel_MC_Only_frompointer(Empty_numerator_Hist, Title_His, "MC", Xaxis_title_string, Yaxis_title_string, Zaxis_title, max_x, max_y, pdf, doBinwidth, logScale);

      FULL_EmptyMC_Hist_numerator->Add(Empty_numerator_Hist,-1);
      FULL_EmptyMC_Hist_denominator->Add(Empty_denominator_Hist,-1);

      if(OnlyEffplot==false){
        sprintf(Title_His, "%s (%s)[TRUTH] [Denominator(F-E)]", title_type_char,title);
        Draw_2D_Panel_MC_Only_frompointer(FULL_EmptyMC_Hist_denominator, Title_His, "MC", Xaxis_title_string, Yaxis_title_string, Zaxis_title, max_x , max_y, pdf, doBinwidth, logScale);


        sprintf(Title_His, "%s (%s)[TRUTH+RECO] [Numerator(F-E)]", title_type_char,title);
        Draw_2D_Panel_MC_Only_frompointer(FULL_EmptyMC_Hist_numerator, Title_His, "MC", Xaxis_title_string, Yaxis_title_string, Zaxis_title, max_x , max_y, pdf, doBinwidth, logScale);


      }
      FULL_EmptyMC_Hist_numerator->Divide(FULL_EmptyMC_Hist_numerator, FULL_EmptyMC_Hist_denominator, 1.0,1.0,"");
      sprintf(Title_His, "2D Efficiency %s (%s) [Combined (F-E)]", title_type_char, title);
      Draw_2D_Panel_MC_Only_frompointer(FULL_EmptyMC_Hist_numerator, Title_His, "MC", Xaxis_title_string, Yaxis_title_string, Zaxis_title, max_x , max_y, pdf, doBinwidth, logScale);



}//endl;


void Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_Combined_PanelPlots(ME_playlist_TFileMAP FullMCMap, ME_playlist_TFileMAP Full_TRUTHDEM_MCMap,
                                                                       Pot_MapList FullMC_POTMap, ME_playlist_TFileMAP EmptyMCMap,
                                                                       ME_playlist_TFileMAP Empty_TRUTHDEM_MCMap, Pot_MapList EmptyMC_POTMap,
                                                                       const char *histoName, const char *Xaxis_title, const char *Yaxis_title,const char * Zaxis_title,
                                                                       bool logScale, bool doBinwidth, const char* title_type_char, const char* title ,MnvPlotter *mnvPlotter,
                                                                       TCanvas *can,  char *pdf, bool OnlyEffplot, double max_x, double max_y , double txt_sizeY , double txt_sizeX )
          {

      char histoName_TRUE[1024];
      char histoName_TRUE_RECO[1024];
      char Title_His[1024];
      std::string Xaxis_title_string(Xaxis_title);
      std::string Yaxis_title_string(Yaxis_title);

      sprintf(histoName_TRUE, "%s_TRUE", histoName);
      sprintf(histoName_TRUE_RECO, "%s_TRUE_RECO", histoName);


      CyroStatusPot_MapList POT_MAP = Constuct_TOTALPOT_cryostatusMap(FullMC_POTMap, EmptyMC_POTMap, true);
      double ScaleEmptyToFull_MC = POT_MAP[kMC_FULL] /  POT_MAP[kMC_EMPTY];
      Playlist_MnvH2D_Map FULL_numerator_MC_HistMAP =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(FullMCMap, histoName_TRUE_RECO );
      Playlist_MnvH2D_Map FULL_denominator_MC_HistMAP =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(Full_TRUTHDEM_MCMap, histoName_TRUE );

      Playlist_MnvH2D_Map Empty_numerator_MC_HistMAP =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(EmptyMCMap, histoName_TRUE_RECO );
      Playlist_MnvH2D_Map Empty_denominator_MC_HistMAP =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(Empty_TRUTHDEM_MCMap, histoName_TRUE );


      auto FULL_numerator_Hist = Combine_2DHists_fromMAP(FULL_numerator_MC_HistMAP  , kME1F ,"FULL_numerator_Hist");
      auto FULL_denominator_Hist = Combine_2DHists_fromMAP(FULL_denominator_MC_HistMAP , kME1F ,"FULL_denominator_Hist");

      auto Empty_numerator_Hist = Combine_2DHists_fromMAP(Empty_numerator_MC_HistMAP  , kME1M  ,"Empty_numerator_Hist");
      auto Empty_denominator_Hist = Combine_2DHists_fromMAP(Empty_denominator_MC_HistMAP , kME1M  ,"Empty_denominator_Hist");
      Empty_numerator_Hist->Scale(ScaleEmptyToFull_MC);
      Empty_denominator_Hist->Scale(ScaleEmptyToFull_MC);

      auto FULL_EmptyMC_Hist_numerator =(MnvH2D*) FULL_numerator_Hist->Clone("FULL_EmptyMC_Hist_numerator");
      auto FULL_EmptyMC_Hist_denominator =(MnvH2D*) FULL_denominator_Hist->Clone("FULL_EmptyMC_Hist_denominator");

      if(OnlyEffplot==false){
        sprintf(Title_His, "%s (%s)[TRUTH] [combined Full Denom]", title_type_char, title);
        Draw_2D_Panel_MC_Only_frompointer(FULL_denominator_Hist, Title_His, "MC", Xaxis_title_string, Yaxis_title_string, Zaxis_title, max_x , max_y, pdf, doBinwidth, logScale, txt_sizeX, txt_sizeY);

        sprintf(Title_His, "%s (%s)[TRUTH+RECO] [combined Full Num]", title_type_char, title);
        Draw_2D_Panel_MC_Only_frompointer(FULL_numerator_Hist, Title_His, "MC", Xaxis_title_string, Yaxis_title_string, Zaxis_title, max_x , max_y, pdf, doBinwidth, logScale, txt_sizeX, txt_sizeY);

      }
      FULL_numerator_Hist->Divide(FULL_numerator_Hist, FULL_denominator_Hist, 1.0,1.0,"");
      sprintf(Title_His, "2D Efficiency %s (%s) (Full Combined) ", title_type_char, title);
      Draw_2D_Panel_MC_Only_frompointer(FULL_numerator_Hist, Title_His, "MC", Xaxis_title_string, Yaxis_title_string, Zaxis_title, max_x , max_y, pdf, doBinwidth, logScale, txt_sizeX, txt_sizeY);


      ////////////////////////////////////////////////////////////////////////////////////////////////////////////
      if(OnlyEffplot==false){
        sprintf(Title_His, "%s (%s) [TRUTH] [combined Empty Denom]", title_type_char,title);
        Draw_2D_Panel_MC_Only_frompointer(Empty_denominator_Hist, Title_His, "MC", Xaxis_title_string, Yaxis_title_string, Zaxis_title, max_x, max_y, pdf, doBinwidth, logScale, txt_sizeX, txt_sizeY);

        sprintf(Title_His, "%s  (%s)[TRUTH+RECO] [combined Empty Num]", title_type_char,title);
        Draw_2D_Panel_MC_Only_frompointer(Empty_numerator_Hist, Title_His, "MC", Xaxis_title_string, Yaxis_title_string, Zaxis_title, max_x, max_y, pdf, doBinwidth, logScale, txt_sizeX, txt_sizeY);

      }
      Empty_numerator_Hist->Divide(Empty_numerator_Hist, FULL_denominator_Hist, 1.0,1.0,"");
      sprintf(Title_His, "2D Efficiency %s (%s) (Empty Combined) ", title_type_char, title);
      Draw_2D_Panel_MC_Only_frompointer(Empty_numerator_Hist, Title_His, "MC", Xaxis_title_string, Yaxis_title_string, Zaxis_title, max_x, max_y, pdf, doBinwidth, logScale, txt_sizeX, txt_sizeY);

      FULL_EmptyMC_Hist_numerator->Add(Empty_numerator_Hist,-1);
      FULL_EmptyMC_Hist_denominator->Add(Empty_denominator_Hist,-1);

      if(OnlyEffplot==false){
        sprintf(Title_His, "%s (%s)[TRUTH] [Denominator(F-E)]", title_type_char,title);
        Draw_2D_Panel_MC_Only_frompointer(FULL_EmptyMC_Hist_denominator, Title_His, "MC", Xaxis_title_string, Yaxis_title_string, Zaxis_title, max_x , max_y, pdf, doBinwidth, logScale, txt_sizeX, txt_sizeY);


        sprintf(Title_His, "%s (%s)[TRUTH+RECO] [Numerator(F-E)]", title_type_char,title);
        Draw_2D_Panel_MC_Only_frompointer(FULL_EmptyMC_Hist_numerator, Title_His, "MC", Xaxis_title_string, Yaxis_title_string, Zaxis_title, max_x , max_y, pdf, doBinwidth, logScale, txt_sizeX, txt_sizeY);


      }
      FULL_EmptyMC_Hist_numerator->Divide(FULL_EmptyMC_Hist_numerator, FULL_EmptyMC_Hist_denominator, 1.0,1.0,"");
      sprintf(Title_His, "2D Efficiency %s (%s) [Combined (F-E)]", title_type_char, title);
      Draw_2D_Panel_MC_Only_frompointer(FULL_EmptyMC_Hist_numerator, Title_His, "MC", Xaxis_title_string, Yaxis_title_string, Zaxis_title, max_x , max_y, pdf, doBinwidth, logScale, txt_sizeX, txt_sizeY);



}//endl;




/////////////////////////////////////////////
// end of function
////////////////////////////////////////////////////////////////////////////////////////////////////////

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

  int pageCount = 26;
  int index = 2;
  int Column_Spacing = 2;

  myfile<<Muon_latex_Latex.GetSubSection("Muon Variables Efficiency");

  for(auto cat: muon_vector){

    auto input_vectors = GetBinMuonVector(cat);
    std::string Var_name = GetMuonVarTitleNameFORLatex(cat);
    std::string Units_name = GetMuonUnitType(cat);


    myfile<<"\n";
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% Eff for FULL Muon Var "<< Var_name <<" \n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<Muon_latex_Latex.GetBeginFrame(Var_name)<< "\n";
    myfile<<Muon_latex_Latex.GetBeginTabular("ccc")<< "\n";
    myfile<<Muon_latex_Latex.GetInclude_figure(index, pdf_name_CV)<< "\n";
    myfile<<"& \n";
    myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing, pdf_name_CV )<< "\n";
    myfile<<"& \n";
    myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 2, pdf_name_CV)<< "\n";
    myfile<<"\\\\ \n";
    myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 3, pdf_name_CV )<< "\n";
    myfile<<"& \n";
    myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 4, pdf_name_CV)<< "\n";
    myfile<<Muon_latex_Latex.GetEndTabular()<< "\n";
    if(input_vectors.size() < 25)
    {
      myfile<<Muon_latex_Latex.BinningLatexString(input_vectors, Var_name , Units_name )<< "\n";
    }
    myfile<<Muon_latex_Latex.GetEndFrame();

    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% Frame ALL EMPTY Playlist Breakdown"<< Var_name <<" \n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<Muon_latex_Latex.GetBeginFrame(Var_name)<< "\n";
    myfile<<Muon_latex_Latex.GetBeginTabular("ccc")<< "\n";
    myfile<<Muon_latex_Latex.GetInclude_figure(index+ Column_Spacing * 5, pdf_name_CV)<< "\n";
    myfile<<"& \n";
    myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 6, pdf_name_CV )<< "\n";
    myfile<<"& \n";
    myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 7, pdf_name_CV)<< "\n";
    myfile<<"\\\\ \n";
    myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 8, pdf_name_CV )<< "\n";
    myfile<<"& \n";
    myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 9, pdf_name_CV)<< "\n";
    myfile<<Muon_latex_Latex.GetEndTabular()<< "\n";
    if(input_vectors.size() < 25)
    {

      myfile<<Muon_latex_Latex.BinningLatexString(input_vectors, Var_name , Units_name )<< "\n";
      }
      myfile<<Muon_latex_Latex.GetEndFrame();


      myfile<<"\n";
      myfile<<"\n";
      myfile<<"%%%%%%%%%%%%%%%%% \n";
      myfile<<"%%% Frame FUll -  EMPTY"<< Var_name <<" \n";
      myfile<<"%%%%%%%%%%%%%%%%% \n";
      myfile<<Muon_latex_Latex.GetBeginFrame(Var_name)<< "\n";
      myfile<<Muon_latex_Latex.GetBeginTabular("ccc")<< "\n";
      myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 10, pdf_name_CV, .24)<< "\n";
      myfile<<"& \n";
      myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 11, pdf_name_CV, .24 )<< "\n";
      myfile<<"& \n";
      myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 12, pdf_name_CV, .24)<< "\n";
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
  index= index + pageCount;

  }


  myfile.close();




}//end of



void Appendtotxt_2ndTrk(std::string output_name ,  std::string pdf_name_CV, int First_page, char *Var_name ,char *Units_name, std::vector<double>input_vectors)
  {
  double scale= .23;
  std::ofstream myfile;

 std::string fileName = output_name + ".txt";
  myfile.open(fileName, std::ios_base::app);
  std::cout<<"Adding to Latex File "<< fileName<<std::endl;
  LatexFormat Muon_latex_Latex(scale);

  myfile<<Muon_latex_Latex.GetSubSection(Var_name);
  int index = First_page;
  int Column_Spacing = 2;

  std::cout<<"appending to latex starting with Page = "<< index<<std::endl;
  myfile<<"\n";
  myfile<<"\n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<"%%% Eff for 2nd Trks "<< Var_name <<" \n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<Muon_latex_Latex.GetBeginFrame(Var_name)<< "\n";
  myfile<<Muon_latex_Latex.GetBeginTabular("ccc")<< "\n";
  myfile<<Muon_latex_Latex.GetInclude_figure(index, pdf_name_CV)<< "\n";
  myfile<<"& \n";
  myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing, pdf_name_CV )<< "\n";
  myfile<<"& \n";
  myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 2, pdf_name_CV)<< "\n";
  myfile<<"\\\\ \n";
  myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 3, pdf_name_CV )<< "\n";
  myfile<<"& \n";
  myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 4, pdf_name_CV)<< "\n";
  myfile<<Muon_latex_Latex.GetEndTabular()<< "\n";
  if(input_vectors.size() < 25)
  {
    myfile<<Muon_latex_Latex.BinningLatexString(input_vectors, Var_name , Units_name )<< "\n";
  }
  myfile<<Muon_latex_Latex.GetEndFrame();

  myfile<<"\n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<"%%% Frame ALL EMPTY Playlist Breakdown"<< Var_name <<" \n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<Muon_latex_Latex.GetBeginFrame(Var_name)<< "\n";
  myfile<<Muon_latex_Latex.GetBeginTabular("ccc")<< "\n";
  myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 5, pdf_name_CV)<< "\n";
  myfile<<"& \n";
  myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 6, pdf_name_CV)<< "\n";
  myfile<<"& \n";
  myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 7, pdf_name_CV)<< "\n";
  myfile<<"\\\\ \n";
  myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 8, pdf_name_CV)<< "\n";
  myfile<<"& \n";
  myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 9, pdf_name_CV)<< "\n";
  myfile<<Muon_latex_Latex.GetEndTabular()<< "\n";
  if(input_vectors.size() < 25)
  {

    myfile<<Muon_latex_Latex.BinningLatexString(input_vectors, Var_name , Units_name )<< "\n";
    }
    myfile<<Muon_latex_Latex.GetEndFrame();


    myfile<<"\n";
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% Frame FUll -  EMPTY"<< Var_name <<" \n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<Muon_latex_Latex.GetBeginFrame(Var_name)<< "\n";
    myfile<<Muon_latex_Latex.GetBeginTabular("ccc")<< "\n";
    myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 10, pdf_name_CV, .24)<< "\n";
    myfile<<"& \n";
    myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 11, pdf_name_CV, .24 )<< "\n";
    myfile<<"& \n";
    myfile<<Muon_latex_Latex.GetInclude_figure(index + Column_Spacing * 12, pdf_name_CV, .24)<< "\n";
    myfile<<Muon_latex_Latex.GetEndTabular()<< "\n";
    if(input_vectors.size() < 25)
    {
      myfile<<Muon_latex_Latex.BinningLatexString(input_vectors, Var_name , Units_name )<< "\n";
    }

      myfile<<Muon_latex_Latex.GetEndFrame();

    myfile.close();




}//end of
//////////////////////////////////////////////////////////////
void Appendtotxt_2D_Eff(std::string output_name ,  std::string pdf_name_CV, int First_page, char *Var_name )
  {
  double scale= .23;
  std::ofstream myfile;

 std::string fileName = output_name + ".txt";
  myfile.open(fileName, std::ios_base::app);
  std::cout<<"Adding to Latex File "<< fileName<<std::endl;
  LatexFormat Eff2d(scale);

  myfile<<Eff2d.GetSubSection(Var_name);
  int index = First_page;
  int Column_Spacing = 1;


  myfile<<"\n";
  myfile<<"\n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<"%%% 2DEff FULL "<< Var_name <<" \n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<Eff2d.GetBeginFrame(Var_name)<< "\n";
  myfile<<Eff2d.GetBeginTabular("ccc")<< "\n";
  myfile<<Eff2d.GetInclude_figure(index, pdf_name_CV)<< "\n";
  myfile<<"& \n";
  myfile<<Eff2d.GetInclude_figure(index + Column_Spacing, pdf_name_CV )<< "\n";
  myfile<<"& \n";
  myfile<<Eff2d.GetInclude_figure(index + Column_Spacing * 2, pdf_name_CV)<< "\n";
  myfile<<"\\\\ \n";
  myfile<<Eff2d.GetInclude_figure(index + Column_Spacing * 3, pdf_name_CV )<< "\n";
  myfile<<"& \n";
  myfile<<Eff2d.GetInclude_figure(index + Column_Spacing * 4, pdf_name_CV)<< "\n";
  myfile<<Eff2d.GetEndTabular()<< "\n";
  myfile<<Eff2d.GetEndFrame();

  myfile<<"\n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<"%%% 2DEff Empty"<< Var_name <<" \n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<Eff2d.GetBeginFrame(Var_name)<< "\n";
  myfile<<Eff2d.GetBeginTabular("ccc")<< "\n";
  myfile<<Eff2d.GetInclude_figure(index + Column_Spacing * 5, pdf_name_CV)<< "\n";
  myfile<<"& \n";
  myfile<<Eff2d.GetInclude_figure(index + Column_Spacing * 6, pdf_name_CV)<< "\n";
  myfile<<"& \n";
  myfile<<Eff2d.GetInclude_figure(index + Column_Spacing * 7, pdf_name_CV)<< "\n";
  myfile<<"\\\\ \n";
  myfile<<Eff2d.GetInclude_figure(index + Column_Spacing * 8, pdf_name_CV)<< "\n";
  myfile<<"& \n";
  myfile<<Eff2d.GetInclude_figure(index + Column_Spacing * 9, pdf_name_CV)<< "\n";
  myfile<<Eff2d.GetEndTabular()<< "\n";
  myfile<<Eff2d.GetEndFrame();


    myfile<<"\n";
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% Frame FUll -  EMPTY"<< Var_name <<" \n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<Eff2d.GetBeginFrame(Var_name)<< "\n";
    myfile<<Eff2d.GetBeginTabular("ccc")<< "\n";
    myfile<<Eff2d.GetInclude_figure(index + Column_Spacing * 10, pdf_name_CV, .24)<< "\n";
    myfile<<"& \n";
    myfile<<Eff2d.GetInclude_figure(index + Column_Spacing * 11, pdf_name_CV, .24 )<< "\n";
    myfile<<"& \n";
    myfile<<Eff2d.GetInclude_figure(index + Column_Spacing * 12, pdf_name_CV, .24)<< "\n";
    myfile<<Eff2d.GetEndTabular()<< "\n";
    myfile<<Eff2d.GetEndFrame();



    myfile.close();




}//end of



void Appendtotxt_2D_Eff_Panel_Combined(std::string output_name ,  std::string pdf_name_CV, int First_page, char *Var_name )
  {
  std::ofstream myfile;

 std::string fileName = output_name + ".txt";
  myfile.open(fileName, std::ios_base::app);
  std::cout<<"Adding to Latex File "<< fileName<<std::endl;
  double scale = .6;
  LatexFormat Eff2d(scale);

  myfile<<Eff2d.GetSubSection(Var_name);
  int index = First_page;
  int Column_Spacing = 1;

    myfile<<"\n";
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% Frame FUll Projection Y "<< Var_name <<" \n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<Eff2d.GetBeginFrame(Var_name)<< "\n";
    myfile<<Eff2d.GetBeginTabular("c")<< "\n";
    myfile<<Eff2d.GetInclude_figure(index + 20, pdf_name_CV, scale)<< "\n";
    myfile<<Eff2d.GetEndTabular()<< "\n";
    myfile<<Eff2d.GetEndFrame();
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% Frame FUll Projection X END "<< Var_name <<" \n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";

    myfile<<"\n";
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% Frame Empty Projection Y "<< Var_name <<" \n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<Eff2d.GetBeginFrame(Var_name)<< "\n";
    myfile<<Eff2d.GetBeginTabular("c")<< "\n";
    myfile<<Eff2d.GetInclude_figure(index + 22, pdf_name_CV, scale)<< "\n";
    myfile<<Eff2d.GetEndTabular()<< "\n";
    myfile<<Eff2d.GetEndFrame();
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% Frame Empty Projection X END "<< Var_name <<" \n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";

    myfile<<"\n";
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% Frame F-E Projection Y "<< Var_name <<" \n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<Eff2d.GetBeginFrame(Var_name)<< "\n";
    myfile<<Eff2d.GetBeginTabular("c")<< "\n";
    myfile<<Eff2d.GetInclude_figure(index + 24 , pdf_name_CV, scale)<< "\n";
    myfile<<Eff2d.GetEndTabular()<< "\n";
    myfile<<Eff2d.GetEndFrame();
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% Frame F-E Projection X END "<< Var_name <<" \n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";


    myfile<<"\n";
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% Frame FUll Projection X "<< Var_name <<" \n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<Eff2d.GetBeginFrame(Var_name)<< "\n";
    myfile<<Eff2d.GetBeginTabular("c")<< "\n";
    myfile<<Eff2d.GetInclude_figure(index + 21, pdf_name_CV, scale)<< "\n";
    myfile<<Eff2d.GetEndTabular()<< "\n";
    myfile<<Eff2d.GetEndFrame();
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% Frame FUll Projection X END "<< Var_name <<" \n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";

    myfile<<"\n";
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% Frame Empty Projection X "<< Var_name <<" \n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<Eff2d.GetBeginFrame(Var_name)<< "\n";
    myfile<<Eff2d.GetBeginTabular("c")<< "\n";
    myfile<<Eff2d.GetInclude_figure(index +23, pdf_name_CV, scale)<< "\n";
    myfile<<Eff2d.GetEndTabular()<< "\n";
    myfile<<Eff2d.GetEndFrame();
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% Frame Empty Projection X END "<< Var_name <<" \n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";

    myfile<<"\n";
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% Frame F-E Projection X "<< Var_name <<" \n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<Eff2d.GetBeginFrame(Var_name)<< "\n";
    myfile<<Eff2d.GetBeginTabular("c")<< "\n";
    myfile<<Eff2d.GetInclude_figure(index + 25, pdf_name_CV, scale)<< "\n";
    myfile<<Eff2d.GetEndTabular()<< "\n";
    myfile<<Eff2d.GetEndFrame();
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% Frame F-E Projection X END "<< Var_name <<" \n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";


    myfile.close();


}//end of

void Appendtotxt_2D_Eff_Panel_Playlists(std::string output_name ,  std::string pdf_name_CV, int First_page, char *Var_name )
  {
  double scale= .6;
  std::ofstream myfile;

 std::string fileName = output_name + ".txt";
  myfile.open(fileName, std::ios_base::app);
  std::cout<<"Adding to Latex File "<< fileName<<std::endl;
  LatexFormat Eff2d(scale);

  myfile<<Eff2d.GetSubSection(Var_name);
  int Column_Spacing = 1;

  for(int index = 0 ; index < 10; index++){
    myfile<<"\n";
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% Frame FUll Projection Y "<< Var_name <<" \n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<Eff2d.GetBeginFrame(Var_name)<< "\n";
    myfile<<Eff2d.GetBeginTabular("c")<< "\n";
    myfile<<Eff2d.GetInclude_figure(First_page + 2 * index , pdf_name_CV, scale)<< "\n";
    myfile<<Eff2d.GetEndTabular()<< "\n";
    myfile<<Eff2d.GetEndFrame();
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% Frame FUll Projection Y END "<< Var_name <<" \n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
  }

  for(int index = 0 ; index < 10; index++){
    myfile<<"\n";
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% Frame FUll Projection X "<< Var_name <<" \n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<Eff2d.GetBeginFrame(Var_name)<< "\n";
    myfile<<Eff2d.GetBeginTabular("c")<< "\n";
    myfile<<Eff2d.GetInclude_figure(First_page + 2 * index + 1  , pdf_name_CV, scale)<< "\n";
    myfile<<Eff2d.GetEndTabular()<< "\n";
    myfile<<Eff2d.GetEndFrame();
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% Frame FUll Projection X END "<< Var_name <<" \n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
  }




    myfile.close();


}//end of



/////////////////////////////////////////////
//Main Function
/////////////////////////////////////////////

 int main() {

bool cutsOn =true;
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
  //EMPTY
    Playlist.push_back(kME1G);
    Playlist.push_back(kME1A);
    Playlist.push_back(kME1L);
    Playlist.push_back(kME1M);
    Playlist.push_back(kME1N);
  //Full
    Playlist.push_back(kME1P);
    Playlist.push_back(kME1C);
    Playlist.push_back(kME1D);
    Playlist.push_back(kME1F);
    Playlist.push_back(kME1E);

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


std::vector<SecondTrkVar> Get2ndTrkVaribles() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<SecondTrkVar> Vector_Vars;

  Vector_Vars.push_back(ksecE);
  Vector_Vars.push_back(kThetamid);
  Vector_Vars.push_back(kOpenAngle);
  Vector_Vars.push_back(kPathway);
  Vector_Vars.push_back(kDOCA);
  Vector_Vars.push_back(ksecE_Proton);


  return Vector_Vars;
//#endif
}


std::vector<MuonVar> GetMUONVaribles() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<MuonVar> MuonVars;

  MuonVars.push_back(kE);
  MuonVars.push_back(kP_Z);
  MuonVars.push_back(kP_T);
  MuonVars.push_back(kAngleWRTB);
  //MuonVars.push_back(kDOCA_muon); there is no true Muon DOCA


  return MuonVars;
//#endif
}
