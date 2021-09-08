#include "Efficiency2DPlots.h"
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

void Draw_Efficiency_Muon_FULL_EMPTY_TRUTH(PlayList_INFO FULL_playlist_nom,PlayList_INFO FULL_playlist_TRUTHDEM,
  PlayList_INFO EMPTY_playlist_nom, PlayList_INFO EMPTY_playlist_TRUTH , const char *histoName,
  int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf , MuonVar playlist_name );

void Kin(bool &cutsOn, bool &my_norm, bool &my_debug, const char *userDir) {

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~       Starting Plotter: ME Efficiency Plots         ~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::vector<ME_helium_Playlists> GetPlayListVector_MC();
const std::vector< ME_helium_Playlists> kPlayListVector_MC = GetPlayListVector_MC();
//const std::vector< ME_helium_Playlists> kPlayListVector_DATA = GetPlayListVector_DATA();
std::vector<CryoVertex> GetCryoVertexVaribles();
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
PlayList_INFO PlaylistMC_1D(kPlayListVector_MC[0], true, true );
PlayList_INFO PlaylistMC_1A(kPlayListVector_MC[1], true, true );
PlayList_INFO PlaylistTRUTH_1D(kPlayListVector_MC[0], true );
PlayList_INFO PlaylistTRUTH_1A(kPlayListVector_MC[1], true );



//PlayList_INFO PlaylistMC_1G(kPlayListVector_MC[0], true );
//PlayList_INFO PlaylistMC_1C(kPlayListVector_MC[3], true );
//PlayList_INFO PlaylistMC_1D(kPlayListVector_MC[4], true );

std::vector <PlayList_INFO> Efficiency_Playlist;

//Efficiency_Playlist.push_back(PlaylistMC_1G);
Efficiency_Playlist.push_back(PlaylistMC_1D);
//Efficiency_Playlist.push_back(PlaylistMC_1P);
Efficiency_Playlist.push_back(PlaylistMC_1A);
//Efficiency_Playlist.push_back(PlaylistMC_1C);
//Efficiency_Playlist.push_back(PlaylistMC_1D);


TCanvas *can = new TCanvas("can");
MnvPlotter *mnv_plot = new MnvPlotter();
 char text_title_pdf1[2024];
 char text_title_pdf2[2024];
 char text_title_pdf3[2024];
 char text_title_pdf4[2024];
 char text_title_pdf5[2024];
time_t now = time(0);
tm *ltm = localtime(&now);
 char timeset[2024];
sprintf(timeset,"%i_%i_%i_%i",1 + ltm->tm_mon,ltm->tm_mday, ltm->tm_hour,ltm->tm_min);

sprintf(text_title_pdf1, "Plots_Efficiency_%s.pdf(",timeset );
can -> Print(text_title_pdf1);
sprintf(text_title_pdf2, "Plots_Efficiency_%s.pdf",timeset );
sprintf(text_title_pdf5, "Plots_Efficiency_%s",timeset );
sprintf(text_title_pdf3, "Plots_Efficiency_%s.pdf)",timeset );
sprintf(text_title_pdf4, "Plots_Efficiency_%s",timeset );

std::cout<<"Start to Calculate Efficienies"<<std::endl;

std::string pdf = string(text_title_pdf4);
/*
for(auto MuonVar : kMuonVaribles){
  auto histName = GetMuonVarHistName(MuonVar);
  int n_histName = histName.length();
  char histName_char[n_histName+1];
  strcpy( histName_char,histName.c_str());

  std::cout<<"Calculate Efficiency for "<< histName << std::endl;

Draw_Efficiency_Muon_FULL_EMPTY(Efficiency_Playlist[0],Efficiency_Playlist[1] , histName_char ,  0, " ", mnv_plot, can, text_title_pdf5, MuonVar );
}
*/

//Draw_Efficiency_2ndTrk(Efficiency_Playlist, kPlayListVector_MC[1] , "h_secTrk_Energy_PROTON",
//0, "Proton Energy", mnv_plot, can, text_title_pdf5, ksecE );


//Draw_Efficiency_2ndTrk(Efficiency_Playlist, kPlayListVector_MC[0] , "h_secTrk_Energy",
//0, "Secondary Energy", mnv_plot, can, text_title_pdf5, ksecE );
/*
Draw_Efficiency_2ndTrk_FULL_EMPTY(Efficiency_Playlist[0],Efficiency_Playlist[1] , "h_secTrk_Energy",
  0, " ", mnv_plot, can, text_title_pdf5, k2ndTrk_vector[0] );

Draw_Efficiency_2ndTrk_FULL_EMPTY(Efficiency_Playlist[0],Efficiency_Playlist[1] , "h_secTrk_Energy_PROTON",
    0, "Proton", mnv_plot, can, text_title_pdf5, k2ndTrk_vector[0] );

Draw_Efficiency_2ndTrk_FULL_EMPTY(Efficiency_Playlist[0],Efficiency_Playlist[1] , "h_secTrk_Energy_PION",
      0, "Pion", mnv_plot, can, text_title_pdf5, k2ndTrk_vector[0] );

Draw_Efficiency_2ndTrk_FULL_EMPTY(Efficiency_Playlist[0],Efficiency_Playlist[1] , "h_secTrk_Energy_Dimuon",
      0, "Dimuon", mnv_plot, can, text_title_pdf5, k2ndTrk_vector[0] );


Draw_Efficiency_2ndTrk_FULL_EMPTY(Efficiency_Playlist[0],Efficiency_Playlist[1] , "h_secTrk_MidTheta",
0, " ", mnv_plot, can, text_title_pdf5, k2ndTrk_vector[1] );

Draw_Efficiency_2ndTrk_FULL_EMPTY(Efficiency_Playlist[0],Efficiency_Playlist[1] , "h_secTrk_MidTheta_PROTON",
0, "Proton", mnv_plot, can, text_title_pdf5, k2ndTrk_vector[1] );

Draw_Efficiency_2ndTrk_FULL_EMPTY(Efficiency_Playlist[0],Efficiency_Playlist[1] , "h_secTrk_MidTheta_PION",
0, "Pion", mnv_plot, can, text_title_pdf5, k2ndTrk_vector[1] );

Draw_Efficiency_2ndTrk_FULL_EMPTY(Efficiency_Playlist[0],Efficiency_Playlist[1] , "h_secTrk_MidTheta_PION",
0, "Pion", mnv_plot, can, text_title_pdf5, k2ndTrk_vector[1] );

Draw_Efficiency_2ndTrk_FULL_EMPTY(Efficiency_Playlist[0],Efficiency_Playlist[1] , "h_secTrk_MidTheta_Dimuon",
      0, "Dimuon", mnv_plot, can, text_title_pdf5, k2ndTrk_vector[1] );


//Draw_Efficiency_2ndTrk_FULL_EMPTY(Efficiency_Playlist[0],Efficiency_Playlist[1] , "h_secTrk_Openangle",
//0, " ", mnv_plot, can, text_title_pdf5, k2ndTrk_vector[2] );

//Draw_Efficiency_2ndTrk_FULL_EMPTY(Efficiency_Playlist[0],Efficiency_Playlist[1] , "h_secTrk_Openangle_PROTON",
//0, "Proton", mnv_plot, can, text_title_pdf5, k2ndTrk_vector[2] );

//Draw_Efficiency_2ndTrk_FULL_EMPTY(Efficiency_Playlist[0],Efficiency_Playlist[1] , "h_secTrk_Openangle_PION",
//0, "Pion", mnv_plot, can, text_title_pdf5, k2ndTrk_vector[2] );



Draw_Efficiency_2D_FULL_EMPTY(Efficiency_Playlist[0], Efficiency_Playlist[1] , "h_2d_PZ_PT","Muon Pz (GeV)","Muon Pt (GeV)" , 0, "2d Efficieny Pt vs pz", " ", mnv_plot, can, text_title_pdf2  );

Draw_Efficiency_2D_FULL_EMPTY(Efficiency_Playlist[0], Efficiency_Playlist[1] , "h_2d_E_PZ","Muon Energy (GeV)", "Pz", 0, "2d Efficieny Muon E vs pz", " ", mnv_plot, can, text_title_pdf2  );

Draw_Efficiency_2D_FULL_EMPTY(Efficiency_Playlist[0], Efficiency_Playlist[1] , "h_2d_Theta_PT","Muon Angle(wrtb) (deg)", "Muon Pt (GeV)", 0, "Efficieny Muon Angle vs Muon Pt", " ", mnv_plot, can, text_title_pdf2  );
Draw_Efficiency_2D_FULL_EMPTY(Efficiency_Playlist[0], Efficiency_Playlist[1] , "h_2d_Theta_PZ","Muon Angle(wrtb) (deg)", "muon Pz", 0, "Efficieny Pz vs Muon angle", " ", mnv_plot, can, text_title_pdf2  );
Draw_Efficiency_2D_FULL_EMPTY(Efficiency_Playlist[0], Efficiency_Playlist[1] , "h_2d_E_PT", "Muon Energy (GeV)", "muon Pt", 0, "2d Efficieny Pt Vs. Muon E", " ", mnv_plot, can, text_title_pdf2  );
Draw_Efficiency_2D_FULL_EMPTY(Efficiency_Playlist[0], Efficiency_Playlist[1] , "h_2d_Theta_2ndTrkE","Muon Angle(wrtb) (deg)", "2ndTrk Energy (GeV)", 0, "Efficieny Muon angle vs  2ndTrk E", " ", mnv_plot, can, text_title_pdf2  );
Draw_Efficiency_2D_FULL_EMPTY(Efficiency_Playlist[0], Efficiency_Playlist[1] , "h_2d_muonE_2ndTrkE","Muon Energy (GeV)", "2ndTrk Energy (GeV)", 0, "Efficieny Muon Energy vs  2ndTrk E", " ", mnv_plot, can, text_title_pdf2  );
Draw_Efficiency_2D_FULL_EMPTY(Efficiency_Playlist[0], Efficiency_Playlist[1] , "h_2d_muonPT_2ndTrkE","Muon Pt (GeV)", "2ndTrk Energy (GeV)", 0, "Efficieny Muon Pt vs  2ndTrk E", " ", mnv_plot, can, text_title_pdf2  );
Draw_Efficiency_2D_FULL_EMPTY(Efficiency_Playlist[0], Efficiency_Playlist[1] , "h_2d_muonE_2ndTrkangle","Muon E (GeV)", "2ndTrk Angle (wrtb) (GeV)", 0, "Efficieny Muon E vs  2ndTrk Angle", " ", mnv_plot, can, text_title_pdf2  );
Draw_Efficiency_2D_FULL_EMPTY(Efficiency_Playlist[0], Efficiency_Playlist[1] , "h_2d_muonPT_2ndTrkangle","Muon Pt (GeV)", "2ndTrk Angle (wrtb) (GeV)", 0, "Efficieny Muon Pt vs  2ndTrk Angle", " ", mnv_plot, can, text_title_pdf2  );
Draw_Efficiency_2D_FULL_EMPTY(Efficiency_Playlist[0], Efficiency_Playlist[1] , "h_2d_2ndtrkangle_2ndTrkE" ,"2ndTrk angle (Deg)", "2ndTrk Energy (GeV)", 0, "Efficieny 2ndTrk Angle vs  2ndTrk Energy", " ", mnv_plot, can, text_title_pdf2  );
Draw_Efficiency_2D_FULL_EMPTY(Efficiency_Playlist[0], Efficiency_Playlist[1] , "h_2d_2ndtrkangle_2ndTrkE_Proton","(Proton)2ndTrk angle (Deg)", "2ndTrk (Proton)Energy (GeV)", 0, "Efficieny (Proton) 2ndTrk Angle vs  2ndTrk Energy", "Proton ", mnv_plot, can, text_title_pdf2  );
Draw_Efficiency_2D_FULL_EMPTY(Efficiency_Playlist[0], Efficiency_Playlist[1] , "h_2d_2ndtrkangle_2ndTrkE_Pion","(Pion)2ndTrk angle (Deg)", "2ndTrk (Pion)Energy (GeV)", 0, "Efficieny(Pion) 2ndTrk Angle vs  2ndTrk Energy", "Pion", mnv_plot, can, text_title_pdf2  );
Draw_Efficiency_2D_FULL_EMPTY(Efficiency_Playlist[0], Efficiency_Playlist[1] , "h_2d_2ndtrkangle_2ndTrkE_dimuon","(Dimuon)2ndTrk angle (Deg)", "2ndTrk (Dimuon)Energy (GeV)", 0, "Efficieny(Dimuon) 2ndTrk Angle vs  2ndTrk Energy", "Pion", mnv_plot, can, text_title_pdf2  );


Draw_Efficiency_2ndTrk_FULL_EMPTY(Efficiency_Playlist[0],Efficiency_Playlist[1] , "h_secTrk_Pathlength",
0, " ", mnv_plot, can, text_title_pdf5, k2ndTrk_vector[3] );

Draw_Efficiency_2ndTrk_FULL_EMPTY(Efficiency_Playlist[0],Efficiency_Playlist[1] , "h_secTrk_DOCA",
0, " ", mnv_plot, can, text_title_pdf5, k2ndTrk_vector[4] );

std::cout << std::endl;
std::cout << "Done WITH EfficiencyPlots " << std::endl;
can -> Print(text_title_pdf3);
*/
TCanvas *can2 = new TCanvas("can2");
sprintf(text_title_pdf1, "Plots_EfficiencyTRUTH_%s.pdf(",timeset );
can2 -> Print(text_title_pdf1);
sprintf(text_title_pdf2, "Plots_EfficiencyTRUTH_%s.pdf",timeset );
sprintf(text_title_pdf5, "Plots_EfficiencyTRUTH_%s",timeset );
sprintf(text_title_pdf3, "Plots_EfficiencyTRUTH_%s.pdf)",timeset );
sprintf(text_title_pdf4, "Plots_EfficiencyTRUTH_%s",timeset );



for(auto MuonVar : kMuonVaribles){
  auto histName = GetMuonVarHistName(MuonVar);
  int n_histName = histName.length();
  char histName_char[n_histName+1];
  strcpy( histName_char,histName.c_str());

Draw_Efficiency_Muon_FULL_EMPTY_TRUTH(Efficiency_Playlist[0],PlaylistTRUTH_1D,Efficiency_Playlist[1] ,PlaylistTRUTH_1A, histName_char ,  0, " ", mnv_plot, can2, text_title_pdf5, MuonVar );
}

//Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], PlaylistTRUTH_1D, Efficiency_Playlist[1] ,PlaylistTRUTH_1A, "h_secTrk_Energy",
  //0, " ", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[0] );

  Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], PlaylistTRUTH_1D, Efficiency_Playlist[1] ,PlaylistTRUTH_1A, "h_secTrk_MinEnergy",
    0, " ", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[0] );


//Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], PlaylistTRUTH_1D, Efficiency_Playlist[1] ,PlaylistTRUTH_1A, "h_secTrk_Energy_PROTON",
  //  0, "Proton", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[0] );

    Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], PlaylistTRUTH_1D, Efficiency_Playlist[1] ,PlaylistTRUTH_1A, "h_secTrk_MinEnergy_PROTON",
        0, "Proton", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[0] );

//Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], PlaylistTRUTH_1D, Efficiency_Playlist[1] ,PlaylistTRUTH_1A, "h_secTrk_Energy_PION",
//      0, "Pion", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[0] );

      Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], PlaylistTRUTH_1D, Efficiency_Playlist[1] ,PlaylistTRUTH_1A, "h_secTrk_MinEnergy_PION",
            0, "Pion", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[0] );

//Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], PlaylistTRUTH_1D, Efficiency_Playlist[1] ,PlaylistTRUTH_1A, "h_secTrk_Energy_Dimuon",
//      0, "Dimuon", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[0] );

      Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], PlaylistTRUTH_1D, Efficiency_Playlist[1] ,PlaylistTRUTH_1A, "h_secTrk_MinEnergy_Dimuon",
            0, "Dimuon", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[0] );


//Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], PlaylistTRUTH_1D, Efficiency_Playlist[1] ,PlaylistTRUTH_1A, "h_secTrk_Theta",
//0, " ", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[1] );

Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], PlaylistTRUTH_1D, Efficiency_Playlist[1] ,PlaylistTRUTH_1A, "h_secTrk_MinKETheta",
0, " ", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[1] );

//Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], PlaylistTRUTH_1D, Efficiency_Playlist[1] ,PlaylistTRUTH_1A, "h_secTrk_Theta_PROTON",
//0, "Proton", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[1] );

Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], PlaylistTRUTH_1D, Efficiency_Playlist[1] ,PlaylistTRUTH_1A, "h_secTrk_MinKETheta_PROTON",
0, "Proton", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[1] );

//Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], PlaylistTRUTH_1D, Efficiency_Playlist[1] ,PlaylistTRUTH_1A, "h_secTrk_Theta_PION",
//0, "Pion", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[1] );

Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], PlaylistTRUTH_1D, Efficiency_Playlist[1] ,PlaylistTRUTH_1A, "h_secTrk_MinKETheta_PION",
0, "Pion", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[1] );


//Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], PlaylistTRUTH_1D, Efficiency_Playlist[1] ,PlaylistTRUTH_1A, "h_secTrk_Theta_PION",
//0, "Pion", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[1] );

//Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], PlaylistTRUTH_1D, Efficiency_Playlist[1] ,PlaylistTRUTH_1A, "h_secTrk_Theta_Dimuon",
//      0, "Dimuon", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[1] );

Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], PlaylistTRUTH_1D, Efficiency_Playlist[1] ,PlaylistTRUTH_1A, "h_secTrk_MinKETheta_Dimuon",
0, "Dimuon", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[1] );

Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], PlaylistTRUTH_1D, Efficiency_Playlist[1] ,PlaylistTRUTH_1A, "h_secTrk_Openangle",
0, " ", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[2] );


//Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], PlaylistTRUTH_1D, Efficiency_Playlist[1] ,PlaylistTRUTH_1A, "h_secTrk_Openangle_PROTON",
//0, "Proton", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[2] );

//Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], PlaylistTRUTH_1D, Efficiency_Playlist[1] ,PlaylistTRUTH_1A, "h_secTrk_Openangle_PION",
//0, "Pion", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[2] );

Draw_Efficiency_2D_FULL_EMPTY_TRUTH(Efficiency_Playlist[0],PlaylistTRUTH_1D, Efficiency_Playlist[1] ,PlaylistTRUTH_1A, "h_2d_PZ_PT","Muon Pz (GeV)","Muon Pt (GeV)" , 0, "2d Efficieny Pt vs pz", " ", mnv_plot, can, text_title_pdf2  );

Draw_Efficiency_2D_FULL_EMPTY_TRUTH(Efficiency_Playlist[0],PlaylistTRUTH_1D, Efficiency_Playlist[1] ,PlaylistTRUTH_1A, "h_2d_E_PZ","Muon Energy (GeV)", "Pz", 0, "2d Efficieny Muon E vs pz", " ", mnv_plot, can, text_title_pdf2  );

Draw_Efficiency_2D_FULL_EMPTY_TRUTH(Efficiency_Playlist[0],PlaylistTRUTH_1D, Efficiency_Playlist[1] ,PlaylistTRUTH_1A, "h_2d_Theta_PT","Muon Angle(wrtb) (deg)", "Muon Pt (GeV)", 0, "Efficieny Muon Angle vs Muon Pt", " ", mnv_plot, can, text_title_pdf2  );
Draw_Efficiency_2D_FULL_EMPTY_TRUTH(Efficiency_Playlist[0],PlaylistTRUTH_1D, Efficiency_Playlist[1] ,PlaylistTRUTH_1A, "h_2d_Theta_PZ","Muon Angle(wrtb) (deg)", "muon Pz", 0, "Efficieny Pz vs Muon angle", " ", mnv_plot, can, text_title_pdf2  );
Draw_Efficiency_2D_FULL_EMPTY_TRUTH(Efficiency_Playlist[0],PlaylistTRUTH_1D, Efficiency_Playlist[1] ,PlaylistTRUTH_1A, "h_2d_E_PT", "Muon Energy (GeV)", "muon Pt", 0, "2d Efficieny Pt Vs. Muon E", " ", mnv_plot, can, text_title_pdf2  );
Draw_Efficiency_2D_FULL_EMPTY_TRUTH(Efficiency_Playlist[0],PlaylistTRUTH_1D, Efficiency_Playlist[1] ,PlaylistTRUTH_1A, "h_2d_Theta_2ndTrkE","Muon Angle(wrtb) (deg)", "2ndTrk Energy (GeV)", 0, "Efficieny Muon angle vs  2ndTrk E", " ", mnv_plot, can, text_title_pdf2  );
Draw_Efficiency_2D_FULL_EMPTY_TRUTH(Efficiency_Playlist[0],PlaylistTRUTH_1D, Efficiency_Playlist[1] ,PlaylistTRUTH_1A, "h_2d_muonE_2ndTrkE","Muon Energy (GeV)", "2ndTrk Energy (GeV)", 0, "Efficieny Muon Energy vs  2ndTrk E", " ", mnv_plot, can, text_title_pdf2  );
Draw_Efficiency_2D_FULL_EMPTY_TRUTH(Efficiency_Playlist[0],PlaylistTRUTH_1D, Efficiency_Playlist[1] ,PlaylistTRUTH_1A, "h_2d_muonPT_2ndTrkE","Muon Pt (GeV)", "2ndTrk Energy (GeV)", 0, "Efficieny Muon Pt vs  2ndTrk E", " ", mnv_plot, can, text_title_pdf2  );
Draw_Efficiency_2D_FULL_EMPTY_TRUTH(Efficiency_Playlist[0],PlaylistTRUTH_1D, Efficiency_Playlist[1] ,PlaylistTRUTH_1A, "h_2d_muonE_2ndTrkangle","Muon E (GeV)", "2ndTrk Angle (wrtb) (GeV)", 0, "Efficieny Muon E vs  2ndTrk Angle", " ", mnv_plot, can, text_title_pdf2  );
Draw_Efficiency_2D_FULL_EMPTY_TRUTH(Efficiency_Playlist[0],PlaylistTRUTH_1D, Efficiency_Playlist[1] ,PlaylistTRUTH_1A, "h_2d_muonPT_2ndTrkangle","Muon Pt (GeV)", "2ndTrk Angle (wrtb) (GeV)", 0, "Efficieny Muon Pt vs  2ndTrk Angle", " ", mnv_plot, can, text_title_pdf2  );
Draw_Efficiency_2D_FULL_EMPTY_TRUTH(Efficiency_Playlist[0],PlaylistTRUTH_1D, Efficiency_Playlist[1] ,PlaylistTRUTH_1A, "h_2d_2ndtrkangle_2ndTrkE" ,"2ndTrk angle (Deg)", "2ndTrk Energy (GeV)", 0, "Efficieny 2ndTrk Angle vs  2ndTrk Energy", " ", mnv_plot, can, text_title_pdf2  );
Draw_Efficiency_2D_FULL_EMPTY_TRUTH(Efficiency_Playlist[0],PlaylistTRUTH_1D, Efficiency_Playlist[1] ,PlaylistTRUTH_1A, "h_2d_2ndtrkangle_2ndTrkE_Proton","(Proton)2ndTrk angle (Deg)", "2ndTrk (Proton)Energy (GeV)", 0, "Efficieny (Proton) 2ndTrk Angle vs  2ndTrk Energy", "Proton ", mnv_plot, can, text_title_pdf2  );
Draw_Efficiency_2D_FULL_EMPTY_TRUTH(Efficiency_Playlist[0],PlaylistTRUTH_1D, Efficiency_Playlist[1] ,PlaylistTRUTH_1A, "h_2d_2ndtrkangle_2ndTrkE_Pion","(Pion)2ndTrk angle (Deg)", "2ndTrk (Pion)Energy (GeV)", 0, "Efficieny(Pion) 2ndTrk Angle vs  2ndTrk Energy", "Pion", mnv_plot, can, text_title_pdf2  );
Draw_Efficiency_2D_FULL_EMPTY_TRUTH(Efficiency_Playlist[0],PlaylistTRUTH_1D, Efficiency_Playlist[1] ,PlaylistTRUTH_1A, "h_2d_2ndtrkangle_2ndTrkE_dimuon","(Dimuon)2ndTrk angle (Deg)", "2ndTrk (Dimuon)Energy (GeV)", 0, "Efficieny(Dimuon) 2ndTrk Angle vs  2ndTrk Energy", "Pion", mnv_plot, can, text_title_pdf2  );

Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], PlaylistTRUTH_1D, Efficiency_Playlist[1] ,PlaylistTRUTH_1A, "h_secTrk_Pathlength",
0, " ", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[3] );

Draw_Efficiency_2ndTrk_FULL_EMPTY_TRUTH(Efficiency_Playlist[0], PlaylistTRUTH_1D, Efficiency_Playlist[1] ,PlaylistTRUTH_1A, "h_secTrk_DOCA",
0, " ", mnv_plot, can2, text_title_pdf5, k2ndTrk_vector[4] );

std::cout << std::endl;
std::cout << "Done WITH EfficiencyPlots" << std::endl;
can2 -> Print(text_title_pdf3);


/*


Draw_Efficiency_2ndTrk(Efficiency_Playlist, kPlayListVector_MC[1] , "h_secTrk_Energy_PION",
0, "PION Energy", mnv_plot, can, text_title_pdf5, ksecE );



Draw_Efficiency_2ndTrk(Efficiency_Playlist, kPlayListVector_MC[1] , "h_secTrk_Openangle_PROTON",
0, "Proton Energy", mnv_plot, can, text_title_pdf5, kOpenAngle );

Draw_Efficiency_2ndTrk(Efficiency_Playlist, kPlayListVector_MC[1] , "h_secTrk_Openangle_PION",
0, "PION Energy", mnv_plot, can, text_title_pdf5, kOpenAngle );


Draw_Efficiency_2ndTrk(Efficiency_Playlist, kPlayListVector_MC[1] , "h_secTrkMidAngle_PROTON",
0, "Proton Energy", mnv_plot, can, text_title_pdf5, kThetamid );

Draw_Efficiency_2ndTrk(Efficiency_Playlist, kPlayListVector_MC[1] , "h_secTrkMidAngle_PION",
0, "PION Energy", mnv_plot, can, text_title_pdf5, kThetamid );
*/

//PlaylistMC_1P.PrintPlaylistName();
//PlaylistMC_1P.PRINTROOT_Path();
//PlaylistMC_1P.Set_Pot();
//PlaylistMC_1P.PRINT_Pot();

//PlaylistDATA_1P.Set_Pot();
//PlaylistDATA_1P.PRINT_Pot();





}
///////////////////////////////////////////////////////////////////////////////
///// FUNCTIONS//////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


/*

void Draw_Efficiency_2ndTrk(std::vector <PlayList_INFO> Playlist, ME_helium_Playlists Playlist_toscaleto , const char *histoName,
          int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf , SecondTrkVar playlist_name ){


struct playlistMap_struct{
  ME_helium_Status status;
  ME_helium_Playlists playlist;
  MnvH2D *hist_TRUE;
  MnvH2D *hist_TRUE_RECO;
  MnvH2D *EFF;
};


std::vector <ME_helium_Playlists> Playlist_FULL;
std::vector <ME_helium_Playlists> Playlist_EMPTY;

std::vector <playlistMap_struct> Status_playlistFULL_vector;
std::vector <playlistMap_struct> Status_playlistEMPTY_vector;

std::string Var_title = GetsecondTrkTitleName(playlist_name);

//std::map<std::map<ME_helium_Status,ME_helium_Playlists>, MnvH1D*> Map_TRUE,Map_TRUE_RECO,Map_EFF_HIST;


//Hist_map Eff_map;
char histoName_TRUE[1024];
char histoName_TRUE_RECO[1024];


typedef std::map<ME_helium_Playlists, double > POT_MAP;
typedef std::map<ME_helium_Playlists, double > POT_MAP_scaler;
POT_MAP potmap;
POT_MAP_scaler potmap_scaler;


for(auto Playlist_vector: Playlist){
potmap[Playlist_vector.GetPlaylist()]= Playlist_vector.Get_Pot();
}

for(auto Playlist_vector: Playlist){
  potmap_scaler[Playlist_vector.GetPlaylist()]=  potmap[Playlist_toscaleto]/potmap[Playlist_vector.GetPlaylist()] ;
}
MnvH1D *hist_FINAL_FULL;


for(auto Playlist_vector:Playlist){
auto Helium_status = Playlist_vector.GetHeliumStatus();
std::string playlistname = Playlist_vector.GetPlaylistName();

std::string Helium_status_name = GetFULLorEmpty(Helium_status) ;
sprintf(histoName_TRUE, "%s_TRUE", histoName);
sprintf(histoName_TRUE_RECO, "%s_TRUE_RECO", histoName);

MnvH1D *hist_TRUE;
MnvH1D *hist_TRUE_RECO;
playlistMap_struct temp_struct;
hist_TRUE = (MnvH1D*)Playlist_vector.TFILE_PLAYLIST -> Get(histoName_TRUE);
hist_TRUE_RECO = (MnvH1D*)Playlist_vector.TFILE_PLAYLIST -> Get(histoName_TRUE_RECO);
std::string True_name_before = Var_title + " (TRUE) " + playlistname + " " + Helium_status_name;
std::string True_reco_name_before= Var_title  + " (TRUE+RECO) " +playlistname + " " + Helium_status_name;

PlotCVAndError_second_Track(hist_TRUE, pdf, playlist_name, can, True_name_before.c_str() );
PlotCVAndError_second_Track(hist_TRUE_RECO, pdf, playlist_name, can, True_reco_name_before.c_str() );



hist_TRUE->Scale(potmap_scaler[Playlist_vector.GetPlaylist()]);
hist_TRUE_RECO->Scale(potmap_scaler[Playlist_vector.GetPlaylist()]);
std::string True_name = Var_title + " (POTscaled)(TRUE) " + playlistname+ " " + Helium_status_name;
std::string True_reco_name= Var_title  + " (POTscaled)(TRUE+RECO) " +playlistname + " " + Helium_status_name;

PlotCVAndError_second_Track(hist_TRUE, pdf, playlist_name, can, True_name.c_str() );
PlotCVAndError_second_Track(hist_TRUE_RECO, pdf, playlist_name, can, True_reco_name.c_str() );

if(Helium_status==kFULL){
  temp_struct.status = kFULL;
  temp_struct.playlist = Playlist_vector.GetPlaylist();
  temp_struct.hist_TRUE =hist_TRUE;
  temp_struct.hist_TRUE_RECO =hist_TRUE_RECO;
  hist_TRUE_RECO->Divide(hist_TRUE_RECO,hist_TRUE,1.0,1.0,"");
  temp_struct.EFF = hist_TRUE_RECO;
  Status_playlistFULL_vector.push_back(temp_struct);
  if(Playlist_vector.GetPlaylist()==Playlist_toscaleto){hist_FINAL_FULL = hist_TRUE_RECO;}
}

else if(Helium_status==kEMPTY){
  temp_struct.status = kEMPTY;
  temp_struct.playlist = Playlist_vector.GetPlaylist();
  temp_struct.hist_TRUE =hist_TRUE;
  temp_struct.hist_TRUE_RECO =hist_TRUE_RECO;
  hist_TRUE_RECO->Divide(hist_TRUE_RECO,hist_TRUE,1.0,1.0,"");
  temp_struct.EFF =hist_TRUE_RECO;
    Status_playlistEMPTY_vector.push_back(temp_struct);
}

}



for (auto vector :Status_playlistFULL_vector){
if(vector.playlist==Playlist_toscaleto)continue;
hist_FINAL_FULL->Add(vector.EFF);
}

for (auto vector :Status_playlistEMPTY_vector){
hist_FINAL_FULL->Add(vector.EFF,-1);
}


////////////////////////////////////////
// Time to Plot
////////////////////////////////////////
double x1, x2, y1, y2;
plot->DecodeLegendPosition(x1, y1, x2, y2, "R", .5, 10, .025);
TLegend *legend = new TLegend(x1 - .02, y1+.31 , x2 +.06 , y2 +.42  );

legend->SetNColumns(1);
legend->SetTextSize(.03);
legend->SetFillColor(0);


PlotCVAndError_second_Track(hist_FINAL_FULL, pdf, playlist_name, can, "NAME");



//Playlist_toscaleto


//for(std::vector <playlistMap>::iterator it=Status_playlistFULL_vector.begin(); it!=Status_playlistFULL_vector.end(); ++it){
//if(it->second==Playlist_toscaleto)continue;

//}



}//End of function
////////////////////////////////////////////////////////////////

*/









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
                                             TCanvas *can, const char *pdf , MuonVar playlist_name ){

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
      MnvH1D *hist_TRUE_EMPTY = (MnvH1D*)EMPTY_playlist_TRUTH.TFILE_PLAYLIST -> Get(histoName_TRUE);
      MnvH1D *hist_TRUE_RECO_EMPTY = (MnvH1D*)EMPTY_playlist_nom.TFILE_PLAYLIST -> Get(histoName_TRUE_RECO);

      MnvH1D* hist_TRUE_FULL_clone = (MnvH1D*)FULL_playlist_TRUTHDEM.TFILE_PLAYLIST -> Get(histoName_TRUE);
      MnvH1D* hist_TRUE_RECO_FULL_clone = (MnvH1D*)FULL_playlist_nom.TFILE_PLAYLIST -> Get(histoName_TRUE_RECO);
      MnvH1D* hist_TRUE_EMPTY_clone = (MnvH1D*)EMPTY_playlist_TRUTH.TFILE_PLAYLIST -> Get(histoName_TRUE);
      MnvH1D* hist_TRUE_RECO_EMPTY_clone = (MnvH1D*)EMPTY_playlist_nom.TFILE_PLAYLIST -> Get(histoName_TRUE_RECO);

      ///Calculation FOR FINAL Eff
      hist_TRUE_EMPTY_clone->Scale(Scale_MC);
      hist_TRUE_RECO_EMPTY_clone->Scale(Scale_MC);
      hist_TRUE_FULL_clone->Add(hist_TRUE_EMPTY_clone,-1);
      hist_TRUE_RECO_FULL_clone->Add(hist_TRUE_RECO_EMPTY_clone,-1);
      hist_TRUE_RECO_FULL_clone->Divide(hist_TRUE_RECO_FULL_clone, hist_TRUE_FULL_clone, 1.0,1.0,"");



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
      DrawCVAndError_FromTFile(FULL_playlist_TRUTHDEM.TFILE_PLAYLIST, histoName_TRUE, Title_His  , Xaxis_title, pdf );
      sprintf(Title_His, "%s (%s) (True+RECO) (%s)(F)", title_type_char,title,playlistFull_char);
      DrawCVAndError_FromTFile(FULL_playlist_nom.TFILE_PLAYLIST, histoName_TRUE_RECO, Title_His , Xaxis_title, pdf );
      sprintf(Title_His, "%s (%s) (TRUTH) (%s)(E)", title_type_char,title,playlistEmpty_char);
      DrawCVAndError_FromTFile(EMPTY_playlist_TRUTH.TFILE_PLAYLIST, histoName_TRUE,Title_His, Xaxis_title, pdf );
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


}//endl;
/*void Draw_Efficiency_2ndTrk_FULL_EMPTY(PlayList_INFO FULL_playlist,PlayList_INFO EMPTY_playlist , const char *histoName,
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


}//endl;
*/
///
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
      MnvH2D *hist_TRUE_EMPTY = (MnvH2D*)EMPTY_playlist.TFILE_PLAYLIST -> Get(histoName_TRUE);
      MnvH2D *hist_TRUE_RECO_EMPTY = (MnvH2D*)EMPTY_playlist.TFILE_PLAYLIST -> Get(histoName_TRUE_RECO);

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

std::string input;
std::cout << "What is the name of the user? " << std::endl;
std::cin >> input;
std::cout << input << std::endl;

const char *inputFileLoc = input.c_str();

Kin(cutsOn, my_norm, my_debug, inputFileLoc);

return 0;

}



std::vector<ME_helium_Playlists> GetPlayListVector_MC() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ME_helium_Playlists> Playlist;

//  Playlist.push_back(kME1G);
Playlist.push_back(kME1D);
//Playlist.push_back(kME1P);
  Playlist.push_back(kME1A);
  //Playlist.push_back(kME1C);
  //Playlist.push_back(kME1D);

  return Playlist;
//#endif
}

std::vector<ME_helium_Playlists> GetPlayListVector_DATA() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ME_helium_Playlists> Playlist;

  //Playlist.push_back(kME1G);
  //Playlist.push_back(kME1P);
  //Playlist.push_back(kME1A);
  //Playlist.push_back(kME1C);
  //Playlist.push_back(kME1D);

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
