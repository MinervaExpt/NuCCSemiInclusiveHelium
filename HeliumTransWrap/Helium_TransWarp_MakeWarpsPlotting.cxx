#include "Helium_TransWarp_Plotting.h"
//////////////////////////////////////////////////////////////////////////////
bool Debug = true;

std::vector<ME_helium_Playlists> GetFullPlayListVector();
std::vector<ME_helium_Playlists> GetEmptyPlayListVector();


void Draw_TransWarp_InPutHists(TFile *inputFile, char *xaxislabel,char * yaxislabel_units,
            char* Title, MnvPlotter *plot, TCanvas *can,  char *pdf);

void Draw_TransWarp_Root_Converge_Map(TFileMAP TransWarp_TFileMap,  char* xaxislabel, char* yaxislabel, char* zaxislabel,
                             char* Title,  char* pdf, TCanvas *can, MnvPlotter *plot , double SetZMax );

void Draw_TransWarp_Root_2DConverge_Map(TFileMAP TransWarp_TFileMap,  char* xaxislabel, char* yaxislabel, char* zaxislabel,
  char* Title,  char* pdf, TCanvas *can, MnvPlotter *plot , double SetZMax );

void Draw_2DTransWarp_InPutHists(TFile *inputFile, char *xaxislabel,char * yaxislabel,
  char* Title, MnvPlotter *plot, TCanvas *can,  char *pdf);

 void Draw_TransWarp_Root_2DMeanmedian_Map(TFileMAP TransWarp_TFileMap,
    char* Title,  char * pdf  );
void FindZeroBins(MnvH2D *h_data , char *textfilename );

//void DrawMagration_heatMap_LabelBinNumber(MnvH2D *h_mig, const char* xaxislabel,const char* yaxislabel,
//  const char* Title, const char* pdf, TCanvas *can, MnvPlotter *plotter);

std::vector<int> FindGlobalBinNumberForZeroBins(MnvH2D *hist_input);
void Kin(bool &cutsOn, bool &my_norm, bool &my_debug, const char *userDir) {
TH1::AddDirectory(false);
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~       Starting Plotter: ME Efficiency Plots         ~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::vector<ME_helium_Playlists> GetPlayListVector_MC();
const std::vector< ME_helium_Playlists> kMEPlayList_Vector = GetPlayListVector_MC();
//const std::vector< ME_helium_Playlists> kPlayListVector_DATA = GetPlayListVector_DATA();

std::vector<SecondTrkVar> Get2ndTrkVaribles();
std::vector<MuonVar> GetMUONVaribles();
const std::vector<MuonVar> kMuonVaribles = GetMUONVaribles();
/////////////////
/// MC RECO
/////////////////
// Empty Playlist
/////////////////
MnvPlotter *mnv_plotter = new MnvPlotter();
mnv_plotter->ApplyStyle(PlotUtils::kCCInclusiveHeliumStyle);


auto FullME_playlist_vector = GetFullPlayListVector();
auto EmptyME_playlist_vector = GetEmptyPlayListVector();
auto full_playlist_initial = GetPlaylist_InitialName(FullME_playlist_vector[0]);
auto empty_playlist_initial = GetPlaylist_InitialName(EmptyME_playlist_vector[0]);
/////////////
// Full Playlist Data
/////////////


/////////////
// Empty Playlist  Data


auto CrossSection2D = "../Make_CrossSection/CrossSection2D.root";
TFile *TFile2D = new TFile(CrossSection2D);


auto CrossSection = "../Make_CrossSection/CrossSection.root";
TFile *TFile1D = new TFile(CrossSection);

PlotUtils::MnvH2D* h_2Dhist_data =  Get2DHist(*TFile2D,"h_MuonPT_PZ_Full_sub_Empty_potnorm_Data_Signal");
PlotUtils::MnvH2D* h_2Dhist_MC =  Get2DHist(*TFile2D,"h_MuonPT_PZ_Full_sub_Empty_potnorm_RECO");
h_2Dhist_data->Divide(h_2Dhist_data,h_2Dhist_MC);

PlotUtils::MnvH1D* h_1DhistPZ_data =  Get1DHist(*TFile1D,"h_MuonPZ_Full_sub_Empty_potnorm_Data_Signal");
PlotUtils::MnvH1D* h_1DhistPZ_MC =  Get1DHist(*TFile1D,"h_MuonPZ_Full_sub_Empty_potnorm_RECO_Signal");
h_1DhistPZ_data->Divide(h_1DhistPZ_data, h_1DhistPZ_MC);
PlotUtils::MnvH1D* h_1DhistPT_data =  Get1DHist(*TFile1D,"h_MuonPT_Full_sub_Empty_potnorm_Data_Signal");
PlotUtils::MnvH1D* h_1DhistPT_MC =  Get1DHist(*TFile1D,"h_MuonPT_Full_sub_Empty_potnorm_RECO_Signal");
h_1DhistPT_data->Divide(h_1DhistPT_data,h_1DhistPT_MC);
PlotUtils::MnvH1D* h_1DhistE_data =  Get1DHist(*TFile1D,"h_MuonE_Full_sub_Empty_potnorm_Data_Signal");
PlotUtils::MnvH1D* h_1DhistE_MC =  Get1DHist(*TFile1D,"h_MuonE_Full_sub_Empty_potnorm_RECO_Signal");
h_1DhistE_data->Divide(h_1DhistE_data,h_1DhistE_MC);
PlotUtils::MnvH1D* h_1Dhisttheta_data =  Get1DHist(*TFile1D,"h_MuonTheta_Full_sub_Empty_potnorm_Data_Signal");
PlotUtils::MnvH1D* h_1Dhisttheta_MC =  Get1DHist(*TFile1D,"h_MuonTheta_Full_sub_Empty_potnorm_RECO_Signal");
h_1Dhisttheta_data->Divide(h_1Dhisttheta_data,h_1Dhisttheta_MC);


PlotUtils::MnvH2D* h_2Dhisttheta_data_Finner =  Get2DHist(*TFile2D,"h_MuonPT_PZ_Finner_data");
PlotUtils::MnvH2D* h_2Dhisttheta_MC_Finner =  Get2DHist(*TFile2D,"h_MuonPT_PZ_Finner_MC");
h_2Dhisttheta_data_Finner->Divide(h_2Dhisttheta_data_Finner,h_2Dhisttheta_MC_Finner);





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
sprintf(text_title_pdf1, "PLOTS_MakeWarp.pdf(");
can1 -> Print(text_title_pdf1);
sprintf(text_title_pdf2, "PLOTS_MakeWarp.pdf");
sprintf(text_title_pdf5, "PLOTS_MakeWarp");
sprintf(text_title_pdf3, "PLOTS_MakeWarp.pdf)");
sprintf(text_title_pdf4, "PLOTS_MakeWarp");

DrawMagration_heatMap(h_2Dhist_data,"P_{Z}", "P_{T}", "Ratio #frac{data}{MC}", text_title_pdf2, can1, mnv_plotter, false  );
Draw2DHist_Migration_Histpointer(h_2Dhist_data , "Ratio #frac{data}{MC}",  "P_{Z}", "P_{T}", "Ratio #frac{data}{MC}", text_title_pdf5, can1, mnv_plotter );
Draw2DHist_warp(h_2Dhist_data, "P_{Z}", "P_{T}", "Ratio #frac{data}{MC}" , text_title_pdf2, can1, mnv_plotter);

Draw2DHist_warpFit(h_2Dhist_data, "P_{Z}", "P_{T}", "Ratio #frac{data}{MC}" , text_title_pdf2, can1, mnv_plotter);
can1->Clear();
Draw2DHist_warpFit_show(h_2Dhist_data, "P_{Z}", "P_{T}", "Ratio #frac{data}{MC}" , text_title_pdf2, can1, mnv_plotter);


Draw2DHist_warp(h_2Dhisttheta_data_Finner, "P_{Z}", "P_{T}", "Ratio #frac{data}{MC}" , text_title_pdf2, can1, mnv_plotter);
DrawMagration_heatMap(h_2Dhisttheta_data_Finner,"P_{Z}", "P_{T}", "Ratio #frac{data}{MC}", text_title_pdf2, can1, mnv_plotter, false  );
Draw2DHist_Migration_Histpointer(h_2Dhisttheta_data_Finner , "Ratio #frac{data}{MC}",  "P_{Z}", "P_{T}", "Ratio #frac{data}{MC}", text_title_pdf5, can1, mnv_plotter );



Draw_2D_Panel_MC_Only_frompointer(h_2Dhist_data, "ratio", "Ratio #frac{data}{MC}","P_{Z}", "GeV",
 "P_{T}", "GeV",  "Ratio #frac{data}{MC}",  1.1, text_title_pdf2,false,false,  .025,   .03,  false);

 DrawCVAndError_FromHIST(h_1DhistPZ_data, "Ratio PZ #frac{data}{MC}" ,"P_{Z}", "Ratio #frac{data}{MC}", text_title_pdf5, true);
 DrawCVAndError_FromHIST(h_1DhistPT_data, "Ratio PT #frac{data}{MC}" ,"P_{T}", "Ratio #frac{data}{MC}", text_title_pdf5, true);
 DrawCVAndError_FromHIST(h_1DhistE_data, "Ratio E_{#mu} #frac{data}{MC}" ,"E_{#mu}", "Ratio #frac{data}{MC}", text_title_pdf5, true);
 DrawCVAndError_FromHIST(h_1Dhisttheta_data, "Ratio PZ #frac{data}{MC}" ,"P_{Z}", "Ratio #frac{data}{MC}", text_title_pdf5, true);

DrawCVAndError_FromHIST_withFit_Npoly(h_1DhistPZ_data, "Ratio P_{Z} #frac{data}{MC}"  ,"P_{Z} [GeV]","Ratio #frac{data}{MC}",
text_title_pdf5, true, "pol 4" , 4 , "PZ_data_poly4.txt");

DrawCVAndError_FromHIST_withFit_Npoly(h_1DhistPZ_data, "Ratio P_{Z} #frac{data}{MC}"  ,"P_{Z} [GeV]","Ratio #frac{data}{MC}",
text_title_pdf5, true, "pol 5" , 5 , "PZ_data_poly5.txt");

DrawCVAndError_FromHIST_withFit_Npoly_PZ(h_1DhistPZ_data, "Ratio P_{Z} #frac{data}{MC}"  ,"P_{Z} [GeV]","Ratio #frac{data}{MC}",
text_title_pdf5, true );

DrawCVAndError_FromHIST_withFit_Npoly(h_1DhistPZ_data, "Ratio P_{Z} #frac{data}{MC}"  ,"P_{Z} [GeV]","Ratio #frac{data}{MC}",
text_title_pdf5, true, "pol 6" , 6 , "PZ_data_poly6.txt");


DrawCVAndError_FromHIST_withFit_Npoly(h_1DhistPZ_data, "Ratio P_{Z} #frac{data}{MC}"  ,"P_{Z} [GeV]","Ratio #frac{data}{MC}",
text_title_pdf5, true, "pol 7" , 7 , "PZ_data_poly7.txt");

DrawCVAndError_FromHIST_withFit_Npoly(h_1DhistPT_data, "Ratio P_{T} #frac{data}{MC}"  ,"P_{T} [GeV]","Ratio #frac{data}{MC}",
text_title_pdf5, true, "pol 4" , 4 , "PT_data_poly4.txt" );

DrawCVAndError_FromHIST_withFit_Npoly_PT(h_1DhistPT_data, "Ratio P_{T} #frac{data}{MC}"  ,"P_{T} [GeV]","Ratio #frac{data}{MC}",
text_title_pdf5, true );

DrawCVAndError_FromHIST_withFit_Npoly(h_1DhistPT_data, "Ratio P_{T} #frac{data}{MC}"  ,"P_{T} [GeV]","Ratio #frac{data}{MC}",
text_title_pdf5, true, "pol 5" , 5, "PT_data_poly5.txt"  );

DrawCVAndError_FromHIST_withFit_Npoly(h_1DhistPT_data, "Ratio P_{T} #frac{data}{MC}"  ,"P_{T} [GeV]","Ratio #frac{data}{MC}",
               text_title_pdf5, true, "pol 6" , 6, "PT_data_poly6.txt"  );

DrawCVAndError_FromHIST_withFit_Npoly(h_1DhistPT_data, "Ratio P_{T} #frac{data}{MC}"  ,"P_{T} [GeV]","Ratio #frac{data}{MC}",
text_title_pdf5, true, "pol 7" , 7 , "PT_data_poly7.txt" );



DrawCVAndError_FromHIST_withFit_Npoly(h_1DhistE_data, "Ratio E_{#mu} #frac{data}{MC}"  ,"E_{#mu} [GeV]","Ratio #frac{data}{MC}",
text_title_pdf5, true, "pol 4" , 4 ,"E_data_poly4.txt");
DrawCVAndError_FromHIST_withFit_Npoly(h_1DhistE_data, "Ratio E_{#mu} #frac{data}{MC}"  ,"E_{#mu} [GeV]","Ratio #frac{data}{MC}",
text_title_pdf5, true, "pol 5" , 5 ,"E_data_poly5.txt");
DrawCVAndError_FromHIST_withFit_Npoly(h_1DhistE_data, "Ratio E_{#mu} #frac{data}{MC}"  ,"E_{#mu} [GeV]","Ratio #frac{data}{MC}",
text_title_pdf5, true, "pol 6" , 6 ,"E_data_poly6.txt");
DrawCVAndError_FromHIST_withFit_Npoly_E(h_1DhistE_data, "Ratio E_{#mu} #frac{data}{MC}"  ,"E_{#mu} [GeV]","Ratio #frac{data}{MC}",
text_title_pdf5, true );

DrawCVAndError_FromHIST_withFit_Npoly(h_1DhistE_data, "Ratio E_{#mu} #frac{data}{MC}"  ,"E_{#mu} [GeV]","Ratio #frac{data}{MC}",
text_title_pdf5, true, "pol 7" , 7 ,"E_data_poly7.txt");

DrawCVAndError_FromHIST_withFit_Npoly(h_1Dhisttheta_data, "Ratio #theta_{#mu} #frac{data}{MC}"  ,"#theta_{#mu} (wrtb) [Deg]","Ratio #frac{data}{MC}",
text_title_pdf5, true, "pol 4" , 4,"theta_data_poly4.txt" );

DrawCVAndError_FromHIST_withFit_Npoly_theta(h_1Dhisttheta_data, "Ratio #theta_{#mu} #frac{data}{MC}"  ,"#theta_{#mu} (wrtb) [Deg]","Ratio #frac{data}{MC}",
text_title_pdf5, true );

DrawCVAndError_FromHIST_withFit_Npoly(h_1Dhisttheta_data, "Ratio #theta_{#mu} #frac{data}{MC}"  ,"#theta_{#mu} (wrtb) [Deg]","Ratio #frac{data}{MC}",
text_title_pdf5, true, "pol 5" , 5,"theta_data_poly5.txt" );

DrawCVAndError_FromHIST_withFit_Npoly(h_1Dhisttheta_data, "Ratio #theta_{#mu} #frac{data}{MC}"  ,"#theta_{#mu} (wrtb) [Deg]","Ratio #frac{data}{MC}",
text_title_pdf5, true, "pol 6" , 6,"theta_data_poly6.txt" );

DrawCVAndError_FromHIST_withGaussianPeak(h_1DhistE_MC, "MC 1.1 peak E_{#mu}" ,"E_{#mu} [GeV]","Norm to Peak of Gaussian",
text_title_pdf5, true, 3 , 1.1, 6.5, .8, 0 , 20 );

DrawCVAndError_FromHIST_withGaussianPeak(h_1DhistE_MC, "MC .9 peak E_{#mu}" ,"E_{#mu} [GeV]","Norm to Peak of Gaussian",
text_title_pdf5, true, 3 , .9, 6.5, .8, 0 , 20 );


DrawCVAndError_FromHIST_withGaussianPeak(h_1DhistPZ_MC, "MC 1.1 peak P_{Z}" ,"P_{Z} [GeV]","Norm to Peak of Gaussian",
text_title_pdf5, true, 2, 1.1, 6.5, 1 , 0, 12 );

DrawCVAndError_FromHIST_withGaussianPeak(h_1DhistPZ_MC, "MC .9 peak P_{Z}" ,"P_{Z} [GeV]","Norm to Peak of Gaussian",
text_title_pdf5, true, 2,  .9, 6.5, 1 , 0, 12 );


DrawCVAndError_FromHIST_withGaussianPeak(h_1DhistPT_MC, "MC 1.1 peak P_{T}" ,"P_{T} [GeV]","Norm to Peak of Gaussian",
text_title_pdf5, true, 2,  1.1, .65, 12 , 0,1.5 );

DrawCVAndError_FromHIST_withGaussianPeak(h_1DhistPT_MC, "MC .9 peak P_{T}" ,"P_{T} [GeV]","Norm to Peak of Gaussian",
text_title_pdf5, true, 2 , .9, .65, 12 , 0,1.5 );


DrawCVAndError_FromHIST_withGaussianPeak(h_1Dhisttheta_MC, "MC 1.1 peak #theta_{#mu}" ,"#theta_{#mu} [Deg]","Norm to Peak of Gaussian",
text_title_pdf5, true, 1, 1.1, 4.5, 2,0, 12  );

DrawCVAndError_FromHIST_withGaussianPeak(h_1Dhisttheta_MC, "MC .9 peak #theta_{#mu}" ,"#theta_{#mu} [Deg]","Norm to Peak of Gaussian",
text_title_pdf5, true, 1,  .9, 4.5, 2,0, 12 );



can1 -> Print(text_title_pdf3);
std::cout << std::endl;
std::cout << "Done with TransWarp Plots" << std::endl;





}
///////////////////////////////////////////////////////////////////////////////
///// FUNCTIONS//////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void Draw_TransWarp_InPutHists(TFile *inputFile, char *xaxislabel,char * yaxislabel_units,
            char* Title, MnvPlotter *plot, TCanvas *can,  char *pdf){

      char histoName_TRUE[1024];
      char histoName_TRUE_RECO[1024];
      char Title_His[1024];
      char pdf_pdf[1024];
      bool AreaNorm_todata = false;
      bool DoBinwidthNorm = true;
      bool MakeXaxisLOG = false;
      bool doYmax = false;
      double Ymax = 99;
      char Axis_Y[1024];
      MnvH1D *h_data = Get1DHist(*inputFile, "Input_Hists/h_data");
      if(Debug==true) std::cout<<"fouund::h_data"<<std::endl;
      MnvH1D *h_data_truth = Get1DHist(*inputFile, "Input_Hists/h_data_truth");
      if(Debug==true) std::cout<<"fouund::h_data_truth"<<std::endl;
      MnvH1D *h_mc_reco = Get1DHist(*inputFile, "Input_Hists/h_mc_reco");
      if(Debug==true) std::cout<<"fouund::h_mc_reco"<<std::endl;
      MnvH1D *h_mc_truth = Get1DHist(*inputFile, "Input_Hists/h_mc_truth");
      if(Debug==true) std::cout<<"fouund::h_mc_truth"<<std::endl;
      std::string pdf_string(pdf);
      MnvH2D *h_Mig = Get2DHist(*inputFile, "Input_Hists/h_migration_matrix");

      MnvH1D *h_ratio_unfolded_trueData_stat0 = Get1DHist(*inputFile, "Ratio_Unfolded_True_Histograms/Ratio_modelData_trueData_Stat_0_Iter_1;1-Ratio_modelData_trueData_Stat_991_Iter_10/Ratio_modelData_TrueData_Stat_0_Iter_1");
      if(Debug==true) std::cout<<"fouund::h_mc_truth"<<std::endl;

      MnvH2D *h_Chi2_Iteration_Dists = Get2DHist(*inputFile, "Chi2_Iteration_Dists/h_chi2_modelData_trueData_iter_chi2");

      MnvH1D *h_medianHist = Get1DHist(*inputFile, "Chi2_Iteration_Dists/h_median_chi2_modelData_trueData_iter_chi2");
      MnvH1D *h_meanHist = Get1DHist(*inputFile, "Chi2_Iteration_Dists/m_avg_chi2_modelData_trueData_iter_chi2_truncated");
      int NBins = h_data->GetNbinsX();

      TH1D *h_medianHist_clone = (TH1D*)h_medianHist->Clone("h_medianHist_clone");
      TH1D *h_meanHist_clone = (TH1D*)h_meanHist->Clone("h_meanHist_clone");


     Draw_inputTranswarpHist_fromPointers(
        h_data,
        h_data_truth,
        h_mc_reco,
        h_mc_truth,
         AreaNorm_todata,
        pdf_string,
        Title,
        xaxislabel,
        yaxislabel_units,
         DoBinwidthNorm,
         MakeXaxisLOG,
         Ymax,doYmax);

         char xaxislabel_RECO[1024];char xaxislabel_TRUE[1024];
         sprintf(xaxislabel_RECO,"RECO %s", xaxislabel);
         sprintf(xaxislabel_TRUE,"TRUE %s", xaxislabel);


      Draw2DHist_Migration_Histpointer(h_Mig, "Migration",
            xaxislabel_RECO , xaxislabel_TRUE,  "",
           pdf, can, plot);

           sprintf(pdf_pdf,"%s.pdf", pdf);
      Draw2DHist_hist(h_Mig, "Migration",  xaxislabel_RECO , xaxislabel_TRUE, pdf_pdf, can,plot);
      std::string xaxislabel_string(xaxislabel);

      DrawMagration_heatMap(h_Mig, xaxislabel_RECO , xaxislabel_TRUE,
      "Migration Under/Over Flow included ",  pdf_pdf, can,plot, true );



 DrawCVAndError_FromHistPointer(h_ratio_unfolded_trueData_stat0, "Closure Hist 1 interation 1, Universe 0" ,xaxislabel_string, "Unfolded Data/ True Data", pdf_string, false, false);


sprintf(Axis_Y , "#chi^{2} (ndf=%d)",NBins);
std::string Axis_Y_string(Axis_Y);

sprintf(Title_His, "%s Mean and median ",Title);

DrawCVAndError_From2HIST(h_meanHist_clone, "Mean" ,h_medianHist_clone, "Median", Title_His ,"2D Unfolded Data:True Data # of iterations", Axis_Y_string,
         pdf_string, false ,  false, -99,  true);



 Draw_TransWarp_converage(h_Chi2_Iteration_Dists, h_meanHist, h_medianHist  , NBins,   "Unfolded Data:True Data # of iterations", Axis_Y, "",
                        Title  ,  pdf_pdf, can, plot , 50 );





}//endl;

void Draw_2DTransWarp_InPutHists(TFile *inputFile, char *xaxislabel,char * yaxislabel,
            char* Title, MnvPlotter *plot, TCanvas *can,  char *pdf){

      char histoName_TRUE[1024];
      char histoName_TRUE_RECO[1024];
      char Title_His[1024];
      char pdf_pdf[1024];
      sprintf(pdf_pdf,"%s.pdf", pdf);
      bool AreaNorm_todata = false;
      bool DoBinwidthNorm = true;
      bool MakeXaxisLOG = false;
      bool doYmax = false;
      double Ymax = 99;
      bool doMultipliers = true;
      std::vector<double> multipleX{15,5,10,10,10,20,40};
      std::vector<double> multipleY{10,1,1,1,1,10,10,50};
      char Axis_Y[1024];

      MnvH2D *h_data = Get2DHist(*inputFile, "Input_Hists/h_data");
      if(Debug==true) std::cout<<"fouund::h_data"<<std::endl;
      MnvH2D *h_data_true = Get2DHist(*inputFile, "Input_Hists/h_data_truth");
      if(Debug==true) std::cout<<"fouund::h_data_truth"<<std::endl;
      MnvH2D *h_mc_reco = Get2DHist(*inputFile, "Input_Hists/h_mc_reco");
      if(Debug==true) std::cout<<"fouund::h_mc_reco"<<std::endl;
      MnvH2D *h_mc_true = Get2DHist(*inputFile, "Input_Hists/h_mc_truth");
      if(Debug==true) std::cout<<"fouund::h_mc_truth"<<std::endl;
      std::string pdf_string(pdf);
      MnvH2D *h_Mig = Get2DHist(*inputFile, "Input_Hists/h_migration_matrix");

      MnvH1D *h_ratio_unfolded_trueData_stat0 = Get1DHist(*inputFile, "Ratio_Unfolded_True_Histograms/Ratio_modelData_trueData_Stat_0_Iter_1;1-Ratio_modelData_trueData_Stat_991_Iter_10/Ratio_modelData_TrueData_Stat_0_Iter_1");
      if(Debug==true) std::cout<<"fouund::h_mc_truth"<<std::endl;

      MnvH2D *h_Chi2_Iteration_Dists = Get2DHist(*inputFile, "Chi2_Iteration_Dists/h_chi2_modelData_trueData_iter_chi2");

      MnvH1D *h_medianHist = Get1DHist(*inputFile, "Chi2_Iteration_Dists/h_median_chi2_modelData_trueData_iter_chi2");
      MnvH1D *h_meanHist = Get1DHist(*inputFile, "Chi2_Iteration_Dists/m_avg_chi2_modelData_trueData_iter_chi2_truncated");
      TH1D *h_medianHist_clone = (TH1D*)h_medianHist->Clone("h_medianHist_clone");
      TH1D *h_meanHist_clone = (TH1D*)h_meanHist->Clone("h_meanHist_clone");

      int NBinsX = h_data->GetNbinsX();
      int NBinsY = h_data->GetNbinsY();
      int NBins_total = NBinsX*NBinsY;
      double NBins_total_double  = NBins_total;
      std::cout<<" NBins_total = " <<  NBins_total << std::endl;

      FindZeroBins(h_data_true , "h_data_true_zerobins.txt");
      FindZeroBins(h_mc_true , "h_mc_true_zerobins.txt");

      FindZeroBins(h_data , "h_data_zerobins.txt");
      FindZeroBins(h_mc_reco , "h_mc_reco_zerobins.txt");


sprintf(Axis_Y , "#chi^{2} (ndf=%d)",NBins_total);

std::string Axis_Y_string(Axis_Y);

Draw_TransWarp_converage(h_Chi2_Iteration_Dists, h_meanHist, h_medianHist  , NBins_total,   "2D Unfolded Data:True Data # of iterations", Axis_Y, "",
                        Title  ,  pdf_pdf, can, plot , 50, false );

sprintf(Title_His, "%s Mean and median ",Title);

DrawCVAndError_From2HIST_ndflines(h_meanHist, "Mean" ,h_medianHist, "Median",  Title_His ,"2D Unfolded Data:True Data # of iterations", Axis_Y_string,
                              pdf_string, false, false, -99,  true , NBins_total_double );


Draw_inputTranswarp2DHist_fromPointers(
  h_data,
  h_data_true,
  h_mc_reco,
  h_mc_true,
  AreaNorm_todata,
  pdf_pdf,
  Title,
  xaxislabel,
  yaxislabel,
  "[GeV^{2}]",
  DoBinwidthNorm,
  MakeXaxisLOG,
  Ymax, doYmax, doMultipliers, multipleY,  multipleX);


DrawMagration_heatMap(h_data, yaxislabel, xaxislabel,
"h_data",  pdf_pdf, can,plot, true );

DrawMagration_heatMap(h_data_true, yaxislabel, xaxislabel,
"h_data_true",  pdf_pdf, can,plot, true );

DrawMagration_heatMap(h_mc_reco, yaxislabel, xaxislabel,
"h_mc_reco",  pdf_pdf, can,plot, true );

DrawMagration_heatMap(h_mc_true, yaxislabel, xaxislabel,
"h_mc_true",  pdf_pdf, can,plot, true );

DrawMagration_heatMap_LabelBinNumber(h_data,  yaxislabel, xaxislabel,
  "h_data: Global Bin Number Labels", pdf_pdf, can,plot);

DrawMagration_heatMap_LabelBinNumber(h_data_true,  yaxislabel, xaxislabel,
  "h_data_true: Global Bin Number Labels", pdf_pdf, can,plot);

DrawMagration_heatMap_LabelBinNumber(h_mc_true,  yaxislabel, xaxislabel,
  "h_mc_true: Global Bin Number Labels", pdf_pdf, can,plot);

DrawMagration_heatMap_LabelBinNumber(h_mc_reco,  yaxislabel, xaxislabel,
  "h_mc_reco: Global Bin Number Labels", pdf_pdf, can,plot);


}//endl;


void Draw_TransWarp_Root_Converge_Map(TFileMAP TransWarp_TFileMap,  char* xaxislabel, char* yaxislabel, char* zaxislabel,
                 char* Title,  char* pdf, TCanvas *can, MnvPlotter *plot , double SetZMax ){


char FinalTitle[1024];
char Yaxis[1024];

for(auto TFile : TransWarp_TFileMap){

  MnvH1D *h_data = Get1DHist(*TFile.second, "Input_Hists/h_data");
  MnvH2D *h_Chi2_Iteration_Dists = Get2DHist(*TFile.second, "Chi2_Iteration_Dists/h_chi2_modelData_trueData_iter_chi2");
  MnvH1D *h_medianHist = Get1DHist(*TFile.second, "Chi2_Iteration_Dists/h_median_chi2_modelData_trueData_iter_chi2");
  MnvH1D *h_meanHist = Get1DHist(*TFile.second, "Chi2_Iteration_Dists/m_avg_chi2_modelData_trueData_iter_chi2_truncated");
  int NBins = h_data->GetNbinsX();
sprintf(FinalTitle, "%s [%.4f] ", Title , TFile.first);
sprintf(Yaxis , "#chi^{2}(ndf = %d)",NBins );
  Draw_TransWarp_converage(h_Chi2_Iteration_Dists,h_meanHist, h_medianHist, NBins ,   "Unfolded Data:True Data # of Iterations", Yaxis, "",
                    FinalTitle ,   pdf, can, plot ,  SetZMax );


}

}

void Draw_TransWarp_Root_2DConverge_Map(TFileMAP TransWarp_TFileMap,  char* xaxislabel, char* yaxislabel, char* zaxislabel,
  char* Title,  char* pdf, TCanvas *can, MnvPlotter *plot , double SetZMax ){


    char FinalTitle[1024];
    char Yaxis[1024];

    for(auto TFile : TransWarp_TFileMap){

      MnvH2D *h_data = Get2DHist(*TFile.second, "Input_Hists/h_data");
      MnvH2D *h_Chi2_Iteration_Dists = Get2DHist(*TFile.second, "Chi2_Iteration_Dists/h_chi2_modelData_trueData_iter_chi2");
      MnvH1D *h_medianHist = Get1DHist(*TFile.second, "Chi2_Iteration_Dists/h_median_chi2_modelData_trueData_iter_chi2");
      MnvH1D *h_meanHist = Get1DHist(*TFile.second, "Chi2_Iteration_Dists/m_avg_chi2_modelData_trueData_iter_chi2_truncated");
      int NBinsX = h_data->GetNbinsX();
      int NBinsY = h_data->GetNbinsY();
      int n_total_bins = NBinsX*NBinsY;
      sprintf(FinalTitle, "%s [%.4f] ", Title , TFile.first);
      sprintf(Yaxis , "#chi^{2}(ndf = %d)",n_total_bins );
      Draw_TransWarp_converage(h_Chi2_Iteration_Dists,h_meanHist, h_medianHist, n_total_bins ,   "2D Unfolded Data:True Data # of iterations", Yaxis, "",
      FinalTitle ,   pdf, can, plot ,  SetZMax, true );


    }




  }

  void Draw_TransWarp_Root_2DMeanmedian_Map(TFileMAP TransWarp_TFileMap,
    char* Title,  char * pdf  ){


      char FinalTitle[1024];
      char Yaxis[1024];
      std::string pdf_string(pdf);

      for(auto TFile : TransWarp_TFileMap){
        MnvH2D *h_data = Get2DHist(*TFile.second, "Input_Hists/h_data");

        MnvH1D *h_medianHist = Get1DHist(*TFile.second, "Chi2_Iteration_Dists/h_median_chi2_modelData_trueData_iter_chi2");
        MnvH1D *h_meanHist = Get1DHist(*TFile.second, "Chi2_Iteration_Dists/m_avg_chi2_modelData_trueData_iter_chi2_truncated");
        int NBinsX = h_data->GetNbinsX();
        int NBinsY = h_data->GetNbinsY();
        int n_total_bins = NBinsX*NBinsY;
        sprintf(FinalTitle, "%s bigF = [%.4f] ", Title , TFile.first);
        sprintf(Yaxis , "#chi^{2}(ndf = %d)",n_total_bins );
        std::string Yaxis_string(Yaxis);

        DrawCVAndError_From2HIST_ndflines(h_meanHist, "Mean" ,h_medianHist, "Median",  FinalTitle ,"2D Unfolded Data:True Data # of iterations", Yaxis_string,
                                      pdf_string, false, false, -99,  true , n_total_bins );


      }




    }



//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Full Stats
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

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


void FindZeroBins(MnvH2D *hist_input , char *textfilename ){

  const TH2D *hist = (TH2D*)hist_input->Clone("hist");
  RooUnfoldResponse UnfoldTool;
  char list[1024];
  int NXbins = hist->GetNbinsX();
  int NYbins = hist->GetNbinsY();
  std::ofstream outfile (textfilename);
  sprintf(list , "List_%s" , textfilename);
  std::ofstream outfile2 (list);
  std::vector<int> bins;
    outfile<<"Xbin, Ybin, globalBinN, cal GlobalBin, globalbin2, globalbin3, value"<<std::endl;
  for(int x = 1; x< NXbins+1; x ++ ){
    for(int y = 1; y< NYbins+1; y ++ ){

      double value = hist -> GetBinContent (x, y);


      if (value  < 2){

        double bcx = ((TAxis*)hist->GetXaxis())->GetBinCenter(x);
        double bcy = ((TAxis*)hist->GetYaxis())->GetBinCenter(y);


        Int_t binx = hist->GetXaxis()->FindBin(x);
        Int_t biny = hist->GetYaxis()->FindBin(y);
        Int_t globalbin2 = UnfoldTool.GetBin(hist, binx,  biny);
        int global_bin =   UnfoldTool.GetBin(hist, x,  y);
        int global_bin3 =   UnfoldTool.FindBin(hist, bcx,  bcy);

        int global_bin_input = ((x+2)*(y+2))-1;
        outfile<< x << ", " << y << ", "<< global_bin<< ", " << global_bin_input << " ," <<globalbin2<<", "<< global_bin3 << ", "<< value << std::endl;
        //outfile2<<global_bin3 << ", ";
        bins.push_back(global_bin3);
      }


    }//end of loop


}// end of loop

std::sort(bins.begin(), bins.end());

for(auto bin:bins){outfile2<<bin << ",";}



outfile.close();
outfile2.close();






}


std::vector<int> FindGlobalBinNumberForZeroBins(MnvH2D *hist_input){

  RooUnfoldResponse UnfoldTool;
  std::vector<int> output;
  const TH2D *hist = (TH2D*)hist_input->Clone("hist");

  int NXbins = hist->GetNbinsX();
  int NYbins = hist->GetNbinsY();

  for(int x = 1; x<= NXbins; x ++ ){
    for(int y = 1; y<= NYbins; y ++ ){

      double value = hist -> GetBinContent (x, y);
      if (value < 1){
        double bcx = ((TAxis*)hist->GetXaxis())->GetBinCenter(x);
        double bcy = ((TAxis*)hist->GetYaxis())->GetBinCenter(y);

        int global_bin = hist->GetBin(x, y);
        output.push_back(global_bin);
      }


    }//end of loop




  }

return output;

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


/*
void DrawMagration_heatMap_LabelBinNumber(MnvH2D *h_mig, const char* xaxislabel,const char* yaxislabel,
  const char* Title, const char* pdf, TCanvas *can, MnvPlotter *plotter)
{

  TH2D *h_migration = (TH2D*)h_mig->Clone("h_migration");

  RooUnfoldResponse UnfoldTool;

  int first_bin =  1;
  int last_bin_x =  h_migration->GetNbinsX();
  int last_bin_y =  h_migration->GetNbinsY();

  Int_t nbins_x =  h_migration->GetNbinsX();
  Int_t nbins_y =  h_migration->GetNbinsY();


  h_migration->GetXaxis()->SetTitle(xaxislabel);
  h_migration->GetXaxis()->CenterTitle();
  h_migration->GetYaxis()->SetTitle(yaxislabel);
  h_migration->GetYaxis()->CenterTitle();
  h_migration->SetMinimum(0.0);

  TMatrixD m_migration(nbins_x, nbins_y);
  TMatrixD m_migration2(nbins_x, nbins_y);
  TH2D tmp(*h_migration);
  TH2D tmp2(*h_migration);
  tmp.Reset();
  tmp2.Reset();

  for (int y = first_bin; y <= last_bin_y; ++y){
    for (int x = first_bin; x <= last_bin_x; ++x){

      double bcx = ((TAxis*)h_migration->GetXaxis())->GetBinCenter(x);
      double bcy = ((TAxis*)h_migration->GetYaxis())->GetBinCenter(y);
      //int global_bin =   UnfoldTool.FindBin(h_migration, bcx,  bcy);
      double NumberperBin =  h_migration->GetBinContent(x,y);
      int global_bin = h_migration->GetBin(x, y);
      tmp.SetBinContent(x, y, global_bin);
      tmp2.SetBinContent(x, y, NumberperBin);

    }
  }

  tmp.SetMinimum(0.0);
  gStyle->SetTickLength(0.0,"x");
  gStyle->SetTickLength(0.0,"y");
  gStyle->SetPaintTextFormat("3.1f");
  gStyle->SetPalette(kBird);
  tmp.SetMarkerSize(.42);
  tmp.SetMarkerColor(kBlack);
  tmp.GetXaxis()->SetTickLength(0.);
  tmp.GetYaxis()->SetTickLength(0.);
  tmp.SetBarOffset(0.05);

  tmp2.SetMarkerSize(.42);
  tmp2.SetMarkerColor(kRed);
  tmp2.GetXaxis()->SetTickLength(0.);
  tmp2.GetYaxis()->SetTickLength(0.);
  tmp2.SetBarOffset(-0.05);

  tmp2.DrawCopy("colz text");
  tmp.DrawCopy("text Same");

  //h_mig->Draw("COLZ");
  plotter->AddHistoTitle(Title, .04);
  can->Print(pdf);
}//end of function
*/

std::vector<ME_helium_Playlists> GetFullPlayListVector() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ME_helium_Playlists> Playlist;

  Playlist.push_back(kME1P);
  Playlist.push_back(kME1C);
  Playlist.push_back(kME1D);
  Playlist.push_back(kME1F);
  Playlist.push_back(kME1E);


  return Playlist;
//#endif
}

std::vector<ME_helium_Playlists> GetEmptyPlayListVector() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ME_helium_Playlists> Playlist;
  Playlist.push_back(kME1G);
  Playlist.push_back(kME1A);
  Playlist.push_back(kME1L);
  Playlist.push_back(kME1M);
  Playlist.push_back(kME1N);


  return Playlist;
//#endif
}
