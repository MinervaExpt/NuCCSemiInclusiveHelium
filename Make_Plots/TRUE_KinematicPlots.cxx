#include "TRUE_KinematicPlots.h"


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
std::cout<<"~~~~~       Starting Plotter: FOR TRUE Kinematic Plots         ~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;


const std::vector<ME_helium_Playlists> kMEPlayList_Vector = GetPlayListVector_MC();
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
 auto Playlist_names =  MakePlaylistString(kMEPlayList_Vector);
 sprintf(timeset_nonstacks,"%i_%i_%i_%i_%s_%s", 1 + ltm->tm_mon,ltm->tm_mday, ltm->tm_hour,ltm->tm_min, SysError_printLabel.c_str(),Playlist_names.c_str());
 sprintf(timeset, "%i_%i_%i_%i", 1 + ltm->tm_mon,ltm->tm_mday, ltm->tm_hour,ltm->tm_min);

bool is_mc=true;
bool isNOT_mc=false;


std::string pdf_CV =std::string(text_title_pdf4);


 bool Stats_only = false;
PlayList_INFO PlaylistMC_1F(kMEPlayList_Vector.at(8), true, Stats_only );

//PlayList_INFO PlaylistMC_1A(kMEPlayList_Vector.at(0), true, false );
PlayList_INFO PlaylistMC_1G(kMEPlayList_Vector.at(0), true, Stats_only );

POT_MC[kMEPlayList_Vector.at(8)] = PlaylistMC_1F.Get_Pot();
POT_MC[kMEPlayList_Vector.at(0)] = PlaylistMC_1G.Get_Pot();

POT_MC_Status[kFULL] = PlaylistMC_1F.Get_Pot();
POT_MC_Status[kEMPTY] = PlaylistMC_1G.Get_Pot();


std::vector <PlayList_INFO> MC_playlist;

MC_playlist.push_back(PlaylistMC_1F);
MC_playlist.push_back(PlaylistMC_1G);

PlayList_INFO PlaylistDATA_1F(kPlayListVector_DATA[0], isNOT_mc,false );
PlayList_INFO PlaylistDATA_1G(kPlayListVector_DATA[1], isNOT_mc,false );


std::vector <PlayList_INFO> Data_playlist;

Data_playlist.push_back(PlaylistDATA_1F);
Data_playlist.push_back(PlaylistDATA_1G);

POT_DATA[kPlayListVector_DATA[0]] = PlaylistDATA_1F.Get_Pot();
POT_DATA[kPlayListVector_DATA[1]] = PlaylistDATA_1G.Get_Pot();

POT_DATA_Status[kFULL] = PlaylistDATA_1F.Get_Pot();
POT_DATA_Status[kEMPTY] = PlaylistDATA_1G.Get_Pot();

PlayList_INFO PlaylistTRUTH_1F(kMEPlayList_Vector.at(8), true );
PlayList_INFO PlaylistTRUTH_1G(kMEPlayList_Vector.at(0), true );

//TFile *PlaylistTRUTH_1F_noangle     = new TFile("/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1F_TRUTH_StatsONLY_nocut.root");


std::cout<< "POT_DATA_Status[kFULL] = "<< POT_DATA_Status[kFULL]<<std::endl;
std::cout<< "POT_DATA_Status[kEMPTY] = "<< POT_DATA_Status[kEMPTY]<<std::endl;



bool Dugbug_ON=my_debug;
bool BinWithNorm_ON=true;
bool IsRECO = true;
bool IsTruth = !IsRECO;

sprintf(text_title_pdf1, "TRUE_PLOTS_%s.pdf(",timeset_nonstacks );
can -> Print(text_title_pdf1);
sprintf(text_title_pdf2, "TRUE_PLOTS_%s.pdf",timeset_nonstacks );
sprintf(text_title_pdf3, "TRUE_PLOTS_%s.pdf)",timeset_nonstacks );
sprintf(text_title_pdf4, "TRUE_PLOTS_%s",timeset_nonstacks );
std::string pdf_label =std::string(text_title_pdf4);

 //Hist_phyiscs_map MAP_stack =  Make_Physics_distribution_map_FromTFile(Playlist_ME1F_MC, "h_MuonCharge" , false, 1.0, kMEPlayList_Vector.at(8), true );
 //Hist_phyiscs_map MAP_stack_G =  Make_Physics_distribution_map_FromTFile(Playlist_ME1G_MC, "h_MuonCharge" , false, 1.0, kMEPlayList_Vector.at(0), true );

 Hist_phyiscs_map MAP_stack_TRUTH =  Make_Physics_distribution_map_FromTFile(PlaylistTRUTH_1F.TFILE_PLAYLIST ,"h_MuonE_TRUE" , false, 1.0, kMEPlayList_Vector.at(8), false );
 Hist_phyiscs_map MAP_stack_G_TRUTH =  Make_Physics_distribution_map_FromTFile(PlaylistTRUTH_1G.TFILE_PLAYLIST ,"h_MuonE_TRUE" , false, 1.0, kMEPlayList_Vector.at(0), false );

 Hist_phyiscs_map MAP_stack_TRUTH_leading =  Make_Physics_distribution_map_FromTFile(PlaylistTRUTH_1F.TFILE_PLAYLIST ,"h_secTrk_Theta_TRUE_leadingFULL" , false, 1.0, kMEPlayList_Vector.at(8), false );
 Hist_phyiscs_map MAP_stack_TRUTH_nonleading =  Make_Physics_distribution_map_FromTFile(PlaylistTRUTH_1F.TFILE_PLAYLIST ,"h_secTrk_KE_TRUE_NonleadingFULL" , false, 1.0, kMEPlayList_Vector.at(8), false );

 Hist_phyiscs_map MAP_stack_TRUTH_ALL =  Make_Physics_distribution_map_FromTFile(PlaylistTRUTH_1F.TFILE_PLAYLIST ,"h_secTrk_ALLKE_TRUE" , false, 1.0, kMEPlayList_Vector.at(8), false );
 Hist_phyiscs_map MAP_stack_TRUTH_ALLangle =  Make_Physics_distribution_map_FromTFile(PlaylistTRUTH_1F.TFILE_PLAYLIST ,"h_secTrk_ALLanglesFULL_TRUE" , false, 1.0, kMEPlayList_Vector.at(8), false );


 Hist_phyiscs_map MAP_stack_TRUTH_Nu_mu =  Make_Physics_distribution_map_FromTFile(PlaylistTRUTH_1F.TFILE_PLAYLIST ,"h_Nu_mu_secTrk_Theta_TRUE" , false, 1.0, kMEPlayList_Vector.at(8), false );
 Hist_phyiscs_map MAP_stack_TRUTH_Nu_e =  Make_Physics_distribution_map_FromTFile(PlaylistTRUTH_1F.TFILE_PLAYLIST ,"h_Nu_e_secTrk_Theta_TRUE" , false, 1.0, kMEPlayList_Vector.at(8), false );
 Hist_phyiscs_map MAP_stack_TRUTH_e =  Make_Physics_distribution_map_FromTFile(PlaylistTRUTH_1F.TFILE_PLAYLIST ,"h_Electron_secTrk_Theta_TRUE" , false, 1.0, kMEPlayList_Vector.at(8), false );
 Hist_phyiscs_map MAP_stack_TRUTH_other =  Make_Physics_distribution_map_FromTFile(PlaylistTRUTH_1F.TFILE_PLAYLIST ,"h_Particle_OTHER_secTrk_Theta_TRUE" , false, 1.0, kMEPlayList_Vector.at(8), false );
 Hist_phyiscs_map MAP_stack_lost999 =  Make_Physics_distribution_map_FromTFile(PlaylistTRUTH_1F.TFILE_PLAYLIST ,"h_lost999" , false, 1.0, kMEPlayList_Vector.at(8), false );

 Hist_phyiscs_map MAP_leadingAngleReco_truth =  Make_Physics_distribution_map_FromTFile(PlaylistMC_1F.TFILE_PLAYLIST ,"h_secTrk_Theta_TRUE_RECO" , false, 1.0, kMEPlayList_Vector.at(8), false );

 Hist_phyiscs_map MAP_leading2ndtrkReco_nonparent_truth_ME1F =  Make_Physics_distribution_map_FromTFile(PlaylistMC_1F.TFILE_PLAYLIST ,"h_secTrk_nonparentEnergy" , false, 1.0, kMEPlayList_Vector.at(8), false );
 Hist_phyiscs_map MAP_leading2ndtrkReco_parent_truth_ME1F =  Make_Physics_distribution_map_FromTFile(PlaylistMC_1F.TFILE_PLAYLIST ,"h_secTrk_Energy" , false, 1.0, kMEPlayList_Vector.at(8), false );

 Hist_phyiscs_map MAP_leading2ndtrkReco_nonparent_truth_ME1G =  Make_Physics_distribution_map_FromTFile(PlaylistMC_1G.TFILE_PLAYLIST ,"h_secTrk_nonparentEnergy" , false, 1.0, kMEPlayList_Vector.at(0), false );
 Hist_phyiscs_map MAP_leading2ndtrkReco_parent_truth_ME1G =  Make_Physics_distribution_map_FromTFile(PlaylistMC_1G.TFILE_PLAYLIST ,"h_secTrk_Energy" , false, 1.0, kMEPlayList_Vector.at(0), false );





bool MakCVS=true;

  std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;

  std::cout<< "Printing Truth Varibles "<< std::endl;

  std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;

 can -> Print(text_title_pdf1);
//Print Pie Figures
  DrawPieFigures(MAP_stack_TRUTH ,  text_title_pdf4, can, mnv_plot, IsTruth,MakCVS,"MuonE");
  DrawPieFigures(MAP_stack_G_TRUTH ,  text_title_pdf4, can, mnv_plot, IsTruth,MakCVS,"MuonE");

  Draw_MCHist_fromTFile(PlaylistTRUTH_1F.TFILE_PLAYLIST,  "h_Tracksize_TRUE", text_title_pdf4,
   "TRUE Tracksize ", "N FS Particles", "Nevents", false );


  DrawSTACKfromHistFilio_FromTFileNoData(PlaylistTRUTH_1F.TFILE_PLAYLIST, PlaylistTRUTH_1G.TFILE_PLAYLIST,"h_secTrk_Theta_TRUE_leading" ,
  POT_MC_Status, POT_DATA_Status, "Leading Non-muon Track True KE", "[True GeV]" ,pdf_label ,BinWithNorm_ON, "[GeV]",kParticle , Dugbug_ON );

  DrawSTACKfromHistFilio_FromTFileNoData(PlaylistTRUTH_1F.TFILE_PLAYLIST, PlaylistTRUTH_1G.TFILE_PLAYLIST,"h_secTrk_Theta_TRUE_Nonleading" ,
  POT_MC_Status, POT_DATA_Status, "Non Leading Non-muon Track True KE", "[True GeV]" ,pdf_label ,BinWithNorm_ON, "[GeV]",kParticle , Dugbug_ON );

  DrawSTACKfromHistFilio_FromTFileNoData(PlaylistTRUTH_1F.TFILE_PLAYLIST, PlaylistTRUTH_1G.TFILE_PLAYLIST,"h_secTrk_Theta_TRUE_Nonleading" ,
  POT_MC_Status, POT_DATA_Status, "Non Leading Non-muon Track True KE", "[True GeV]" ,pdf_label ,BinWithNorm_ON, "[GeV]",kParticle , Dugbug_ON );

  DrawSTACKfromHistFilio_FromTFileNoData(PlaylistTRUTH_1F.TFILE_PLAYLIST, PlaylistTRUTH_1G.TFILE_PLAYLIST,"h_TracksizeALL_TRUE" ,
  POT_MC_Status, POT_DATA_Status, "Number of True Tracks", "[TRUE NTrks]" ,pdf_label ,BinWithNorm_ON, "",kParticle , Dugbug_ON );

  DrawSTACKfromHistFilio_FromTFileNoData(PlaylistTRUTH_1F.TFILE_PLAYLIST, PlaylistTRUTH_1G.TFILE_PLAYLIST,"h_Tracksize_TRUE" ,
  POT_MC_Status, POT_DATA_Status, "Number of True Tracks", "[TRUE NTrks]" ,pdf_label ,BinWithNorm_ON, "",kParticle , Dugbug_ON );

  DrawSTACKfromHistFilio_FromTFileNoData(PlaylistTRUTH_1F.TFILE_PLAYLIST, PlaylistTRUTH_1G.TFILE_PLAYLIST,"h_Tracksize_TRUE" ,
  POT_MC_Status, POT_DATA_Status, "Number of True Tracks", "[TRUE NTrks]" ,pdf_label ,BinWithNorm_ON, "",kInteraction , Dugbug_ON );

  DrawSTACKfromHistFilio_FromTFileNoData(PlaylistTRUTH_1F.TFILE_PLAYLIST, PlaylistTRUTH_1G.TFILE_PLAYLIST,"h_TracksizeALL_TRUE" ,
  POT_MC_Status, POT_DATA_Status, "Number of True Tracks", "[TRUE NTrks]" ,pdf_label ,BinWithNorm_ON, "",kParticle , Dugbug_ON );

  DrawSTACKfromHistFilio_FromTFileNoData(PlaylistTRUTH_1F.TFILE_PLAYLIST, PlaylistTRUTH_1G.TFILE_PLAYLIST,"h_TracksizeALL_leadingTRUE" ,
  POT_MC_Status, POT_DATA_Status, "Number of True Leading Tracks", "[TRUE NTrks]" ,pdf_label ,BinWithNorm_ON, "",kParticle , Dugbug_ON );

  DrawSTACKfromHistFilio_FromTFileNoData(PlaylistTRUTH_1F.TFILE_PLAYLIST, PlaylistTRUTH_1G.TFILE_PLAYLIST,"h_TracksizeALL_nonleadingTRUE" ,
  POT_MC_Status, POT_DATA_Status, "Number of True Non-Leading Tracks", "[TRUE NTrks]" ,pdf_label ,BinWithNorm_ON, "",kParticle , Dugbug_ON );


  DrawSTACKfromHistFilio_FromTFileNoData(PlaylistTRUTH_1F.TFILE_PLAYLIST, PlaylistTRUTH_1G.TFILE_PLAYLIST,"h_secTrk_ALLanglesFULL_TRUE" ,
  POT_MC_Status, POT_DATA_Status, "ALL Tracks True Theta (wrtb)", "[TRUE Degs]" ,pdf_label ,BinWithNorm_ON, "[Degs]",kParticle , Dugbug_ON );
  DrawPieFigures(MAP_stack_TRUTH_ALLangle,  text_title_pdf4, can, mnv_plot, IsTruth,MakCVS, "All_nonmuon_tracks_theta");

  DrawSTACKfromHistFilio_FromTFileNoData(PlaylistTRUTH_1F.TFILE_PLAYLIST, PlaylistTRUTH_1G.TFILE_PLAYLIST,"h_secTrk_Theta_TRUE_leadingFULL" ,
  POT_MC_Status, POT_DATA_Status, "Leading Non-muon Track True Theta (wrtb)", "[TRUE Degs]" ,pdf_label ,BinWithNorm_ON, "[Degs]",kParticle , Dugbug_ON, true, 850.0 );
  DrawPieFigures(MAP_stack_TRUTH_leading ,  text_title_pdf4, can, mnv_plot,IsTruth,MakCVS,"leading_nonmuon_Theta");

  DrawSTACKfromHistFilio_FromTFileNoData(PlaylistTRUTH_1F.TFILE_PLAYLIST, PlaylistTRUTH_1G.TFILE_PLAYLIST,"h_secTrk_Theta_TRUE_NonleadingFULL" ,
  POT_MC_Status, POT_DATA_Status, "Non Leading Non-muon Track True Theta (wrtb)", "[TRUE Degs]" ,pdf_label ,BinWithNorm_ON, "[Degs]",kParticle , Dugbug_ON );
  DrawPieFigures(MAP_stack_TRUTH_nonleading ,  text_title_pdf4, can, mnv_plot,IsTruth,MakCVS,"Nonleading_nonmuon_Theta");

  DrawSTACKfromHistFilio_FromTFileNoData(PlaylistTRUTH_1F.TFILE_PLAYLIST, PlaylistTRUTH_1G.TFILE_PLAYLIST,"h_secTrk_ALLKE_TRUE" ,
  POT_MC_Status, POT_DATA_Status, "ALL Tracks True KE", "[TRUE GeV]" ,pdf_label ,BinWithNorm_ON, "[GeV]",kParticle , Dugbug_ON );
  DrawPieFigures(MAP_stack_TRUTH_ALL ,  text_title_pdf4, can, mnv_plot,IsTruth);

  DrawSTACKfromHistFilio_FromTFileNoData(PlaylistTRUTH_1F.TFILE_PLAYLIST, PlaylistTRUTH_1G.TFILE_PLAYLIST,"h_secTrk_KE_TRUE_leadingFULL" ,
  POT_MC_Status, POT_DATA_Status, "Leading Non-muon Track True KE", "[GeV]" ,pdf_label ,BinWithNorm_ON, "[GeV]",kParticle , Dugbug_ON );

  //DrawSTACKfromHistFilio_FromTFileNoData(PlaylistTRUTH_1F.TFILE_PLAYLIST, PlaylistTRUTH_1G.TFILE_PLAYLIST,"h_secTrk_KE_TRUE_leadingFULL" ,
  //POT_MC_Status, POT_DATA_Status, "Leading Non-muon Track True KE", "[GeV]" ,pdf_label ,BinWithNorm_ON, "[GeV]",kInteraction , Dugbug_ON );


  DrawSTACKfromHistFilio_FromTFileNoData(PlaylistTRUTH_1F.TFILE_PLAYLIST, PlaylistTRUTH_1G.TFILE_PLAYLIST,"h_secTrk_KE_TRUE_NonleadingFULL" ,
  POT_MC_Status, POT_DATA_Status, "NonLeading Non-muon Track True KE", "[GeV]" ,pdf_label ,BinWithNorm_ON, "[GeV]",kParticle, Dugbug_ON );

  DrawSTACKfromHistFilio_FromTFileNoData(PlaylistTRUTH_1F.TFILE_PLAYLIST, PlaylistTRUTH_1G.TFILE_PLAYLIST,"h_secTrk_ALLKE_TRUE" ,
  POT_MC_Status, POT_DATA_Status, "ALL Tracks True KE", "[TRUE GeV]" ,pdf_label ,BinWithNorm_ON, "[GeV]",kParticle , Dugbug_ON );
  DrawPieFigures(MAP_stack_TRUTH_ALL ,  text_title_pdf4, can, mnv_plot,IsTruth);

  DrawSTACKfromHistFilio_FromTFileNoData(PlaylistMC_1F.TFILE_PLAYLIST, PlaylistMC_1G.TFILE_PLAYLIST,"h_secTrk_Energy" ,
  POT_MC_Status, POT_DATA_Status, "RECO branch 2ndTRK KE [parent]", "[TRUE GeV]" ,pdf_label ,BinWithNorm_ON, "[GeV]",kParticle , Dugbug_ON );
  DrawPieFigures(MAP_leading2ndtrkReco_parent_truth_ME1F ,  text_title_pdf4, can, mnv_plot,IsTruth);
  DrawPieFigures(MAP_leading2ndtrkReco_parent_truth_ME1G ,  text_title_pdf4, can, mnv_plot,IsTruth);


  DrawSTACKfromHistFilio_FromTFileNoData(PlaylistMC_1F.TFILE_PLAYLIST, PlaylistMC_1G.TFILE_PLAYLIST,"h_secTrk_nonparentEnergy" ,
  POT_MC_Status, POT_DATA_Status, "RECO branch 2ndTrk KE [Non_parent]", "[TRUE GeV]" ,pdf_label ,BinWithNorm_ON, "[GeV]",kParticle , Dugbug_ON );
  DrawPieFigures(MAP_leading2ndtrkReco_nonparent_truth_ME1F ,  text_title_pdf4, can, mnv_plot,IsTruth);
  DrawPieFigures(MAP_leading2ndtrkReco_nonparent_truth_ME1G ,  text_title_pdf4, can, mnv_plot,IsTruth);



/*
Draw_MCHist_fromTFile(PlaylistTRUTH_1F.TFILE_PLAYLIST,  "h_mc_current_neturino_electron_TRUE", text_title_pdf4,
 "TRUTH FS leading nonmuon [#nu_{e}] [Genie mc_current]", "MC Current type [GENIE]", "Nevents", false );

Draw_MCHist_fromTFile(PlaylistTRUTH_1F.TFILE_PLAYLIST,  "h_mc_incoming_neturino_electron_TRUE", text_title_pdf4,
 "TRUTH FS leading nonmuon [#nu_{e}] [Genie mc_incoming]", "MC incoming particle [GENIE]", "Nevents", false );
DrawSTACKfromHistFilio_FromTFileNoData(PlaylistTRUTH_1F.TFILE_PLAYLIST, PlaylistTRUTH_1G.TFILE_PLAYLIST,"h_Nu_e_secTrk_Theta_TRUE" ,
POT_MC_Status, POT_DATA_Status, "non-leading #nu_{e}", "[TRUE Degs]" ,pdf_label ,false, "[Degs]",kInteraction , Dugbug_ON );
  DrawPieFigures(MAP_stack_TRUTH_Nu_e ,  text_title_pdf4, can, mnv_plot,IsTruth,MakCVS,"h_Nu_e_secTrk_Theta_TRUE");

DrawSTACKfromHistFilio_FromTFileNoData(PlaylistTRUTH_1F.TFILE_PLAYLIST, PlaylistTRUTH_1G.TFILE_PLAYLIST,"h_Nu_mu_secTrk_Theta_TRUE" ,
POT_MC_Status, POT_DATA_Status, "non-leading #nu_{#mu}", "[TRUE Degs]" ,pdf_label ,false, "[Degs]",kInteraction , Dugbug_ON );
DrawPieFigures(MAP_stack_TRUTH_Nu_mu ,  text_title_pdf4, can, mnv_plot,IsTruth,MakCVS,"h_Nu_mu_secTrk_Theta_TRUE");
*/


DrawSTACKfromHistFilio_FromTFileNoData(PlaylistTRUTH_1F.TFILE_PLAYLIST, PlaylistTRUTH_1G.TFILE_PLAYLIST,"h_Electron_secTrk_Theta_TRUE" ,
POT_MC_Status, POT_DATA_Status, "non-leading e", "[TRUE Degs]" ,pdf_label ,false, "[Degs]",kInteraction , Dugbug_ON );
DrawPieFigures(MAP_stack_TRUTH_e ,  text_title_pdf4, can, mnv_plot,IsTruth,MakCVS,"h_Electron_secTrk_Theta_TRUE");

/*
//999 only filled when neutral paticle filter is applied
DrawSTACKfromHistFilio_FromTFileNoData(PlaylistTRUTH_1F.TFILE_PLAYLIST, PlaylistTRUTH_1G.TFILE_PLAYLIST,"h_lost999" ,
POT_MC_Status, POT_DATA_Status, "failed Neutral Particle", "[TRUE Degs]" ,pdf_label ,BinWithNorm_ON, "[Degs]", kParticle, Dugbug_ON );

DrawSTACKfromHistFilio_FromTFileNoData(PlaylistTRUTH_1F.TFILE_PLAYLIST, PlaylistTRUTH_1G.TFILE_PLAYLIST,"h_lost999" ,
POT_MC_Status, POT_DATA_Status, "failed Neutral Particle", "[TRUE Degs]" ,pdf_label ,BinWithNorm_ON, "[Degs]", kInteraction, Dugbug_ON );

DrawPieFigures(MAP_stack_lost999 ,  text_title_pdf4, can, mnv_plot,IsTruth,MakCVS,"h_lost999");
*/

DrawSTACKfromHistFilio_FromTFileNoData(PlaylistTRUTH_1F.TFILE_PLAYLIST, PlaylistTRUTH_1G.TFILE_PLAYLIST,"h_Gamma_secTrk_Theta_TRUE" ,
POT_MC_Status, POT_DATA_Status, "non-leading Gammas", "[TRUE Degs]" ,pdf_label ,true, "[Degs]",kInteraction , Dugbug_ON );

/*
DrawSTACKfromHistFilio_FromTFileNoData(PlaylistTRUTH_1F.TFILE_PLAYLIST, PlaylistTRUTH_1G.TFILE_PLAYLIST,"h_Particle_OTHER_secTrk_Theta_TRUE" ,
POT_MC_Status, POT_DATA_Status, "non-leading OTHER", "[TRUE Degs]" ,pdf_label ,false, "[Degs]",kInteraction , Dugbug_ON );
DrawPieFigures*/
DrawSTACKfromHistFilio_FromTFileNoData(PlaylistMC_1F.TFILE_PLAYLIST, PlaylistMC_1G.TFILE_PLAYLIST,"h_secTrk_Theta_TRUE_RECO" ,
POT_MC_Status, POT_DATA_Status, "leading nonMuon trks (TRUE+RECO cuts)", "[TRUE Degs]" ,pdf_label ,true, "[Degs]",kParticle , Dugbug_ON );

DrawPieFigures(MAP_leadingAngleReco_truth ,  text_title_pdf4, can, mnv_plot,IsTruth,MakCVS,"leading nonmuon (RECO branch)(Truth+RECO)");










 can -> Print(text_title_pdf3);
 can->Close();

std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;

std::cout<< " Done with Muon Plots"<< std::endl;

std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;

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


  //EMPTY
    Playlist.push_back(kME1G);//0
    Playlist.push_back(kME1A);//1
    Playlist.push_back(kME1L);//2
    Playlist.push_back(kME1M);//3
    Playlist.push_back(kME1N);//4
  //Full
    Playlist.push_back(kME1P);//5
    Playlist.push_back(kME1C);//6
    Playlist.push_back(kME1D);//7
    Playlist.push_back(kME1F);//8
    Playlist.push_back(kME1E);//9

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
