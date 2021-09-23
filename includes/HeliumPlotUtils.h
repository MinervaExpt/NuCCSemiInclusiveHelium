#ifndef HELIUMPLOTUTILS_H
#define HELIUMPLOTUTILS_H


#include "TCanvas.h"
#include <TStyle.h>
#include "PlotUtils/MnvVertErrorBand.h"
#include "PlotUtils/MnvPlotter.h"
#include "PlotUtils/HistogramUtils.h"
#include "PlotUtils/MnvH1D.h"
#include "PlotUtils/MnvH2D.h"
#include "PlotUtils/HistFolio.h"
#include "HeliumCuts.h"
#include <iostream>
#include "HeliumDefaults.h"
#include "HeliumUtils.h"
#include "TPie.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "GridCanvas.h"
#include "plot.h"
#include "myPlotStyle.h"
#include <TProfile.h>
#include "TObjArray.h"
//#include "TF1Convolution.h" gvm root verson 5 doesn't have these functions

//#include "PlotUtils/MnvApplication.h"

const double xmin = 0.;
const double xmax = 20;
const int nbins   = 30;

std::vector<Interaction_Map> Interaction_vector( TObjArray * Hists_vector, bool doPOTscaling, double scaler);
std::vector<Material_Map> Material_vector( TObjArray * Hists_vector, bool doPOTscaling, double scaler);
std::vector<Particle_Map> Particle_vector( TObjArray * Hists_vector, bool doPOTscaling, double scaler);


const bool do_fractional_uncertainty = true;
const bool do_cov_area_norm          = false;
const bool include_stat_error        = false;

const std::string do_fractional_uncertainty_str = do_fractional_uncertainty ?
                                                    std::string("Frac") :
                                                    std::string("Abs");
const std::string do_cov_area_norm_str = do_cov_area_norm ?
                                           std::string("CovAreaNorm") :
                                           std::string("");

void PlotErrorSummary(PlotUtils::MnvH1D* hist, std::string pdf, std::string title, std::string xaxis, TCanvas *cE);
void PlotErrorSummaryNew(PlotUtils::MnvH1D* hist, std::string pdf, std::string title, std::string xaxis, TCanvas *cE,MnvPlotter *mnvPlotter);
void PlotErrorSummaryNew(PlotUtils::MnvH1D* hist, std::string pdf, std::string title, std::string xaxis, TCanvas *cE,MnvPlotter *mnvPlotter, bool Debug ,bool PrintAllGroupErrors);

void PlotVertBand(std::string band, std::string method_str, PlotUtils::MnvH1D* hist);
void PlotLatBand(std::string band,  std::string method_str, PlotUtils::MnvH1D* hist);
void PlotVertUniverse(std::string band, unsigned int universe, std::string method_str, PlotUtils::MnvH1D* hist);
void PlotLatUniverse(std::string band, unsigned int universe, std::string method_str,  PlotUtils::MnvH1D* hist);
void PlotCVAndError(PlotUtils::MnvH1D* hist, std::string label);
void Plot_MuonCVAndErrorWITHDATA(PlotUtils::MnvH1D* histFullMC,PlotUtils::MnvH1D* histEmptyMC, PlotUtils::MnvH1D* datahist_Full,
  PlotUtils::MnvH1D* datahist_Empty,std::string label, double POT[], MuonVar Muontype, int order,TCanvas * cE);
void PlotTotalError(PlotUtils::MnvH1D* hist, std::string method_str );
void DrawStack_Particle(bool my_debug, TFile *inputFile,  CryoVertex Vertex_type , ME_helium_Playlists PlayList , int doShape,
  int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf);
void DrawStack_Particle_MuonVar(bool my_debug, TFile *inputFile,  MuonVar MuonVar_type , ME_helium_Playlists PlayList , int doShape,
    int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf);
void DrawStack_Interaction(bool my_debug, TFile *inputFile,  CryoVertex Vertex_type , ME_helium_Playlists PlayList , int doShape,
    int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf);

void DrawStack_Interaction_MuonVar(bool my_debug, TFile *inputFile,  MuonVar MuonVar_type , ME_helium_Playlists PlayList , int doShape,
      int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf);
void DrawStack_Material(bool my_debug, TFile *inputFile,  CryoVertex Vertex_type , ME_helium_Playlists PlayList , int doShape,
      int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf);
void DrawStack_Material_MuonVar(bool my_debug, TFile *inputFile,  MuonVar MuonVar_type , ME_helium_Playlists PlayList , int doShape,
        int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf);
void DrawCVAndError_FromTFile(TFile *inputFile, char *histoName,char *histotitle ,std::string xaxislabel, std::string label);
void DrawCVAndError_FromTFile(bool PrintallErrors ,TFile *inputFile, char *histoName, char *histotitle ,std::string xaxislabel, std::string label);
void DrawCVAndError_FromTFile(TFile *inputFile_MCFULL, TFile *inputFile_MCEMPTY,  char *histoName_MC ,TFile *inputFile_DATAFULL,TFile *inputFile_DATAEMPTY,
          char *histoName_Data, Pot_MapStatusList POT_MC, Pot_MapStatusList POT_DATA, char *histotitle,
          std::string xaxislabel, std::string label, bool DoBinwidthNorm, bool doSmallerrorgrounps, std::string units);
void DrawCVAndError_FromTFile(TFile *inputFile_MCFULL, TFile *inputFile_MCEMPTY,  char *histoName_MC ,TFile *inputFile_DATAFULL,TFile *inputFile_DATAEMPTY,
    char *histoName_Data, Pot_MapStatusList POT_MC, Pot_MapStatusList POT_DATA,bool TrueifFullelseEmpty, char *histotitle,
    std::string xaxislabel, std::string label, bool DoBinwidthNorm, bool doSmallerrorgrounps, std::string units, int Print_Error ,bool Debug);
void DrawCVAndError_FromTFile(TFile *inputFile_MCFULL, TFile *inputFile_MCEMPTY,  char *histoName_MC ,TFile *inputFile_DATAFULL,TFile *inputFile_DATAEMPTY,
                    char *histoName_Data, Pot_MapStatusList POT_MC, Pot_MapStatusList POT_DATA,bool TrueifFullelseEmpty, char *histotitle,
                    std::string xaxislabel, std::string label, bool DoBinwidthNorm, bool doSmallerrorgrounps, std::string units, int Print_Error ,bool Debug, bool Makelogx, bool Makelogy );


void DrawDATAWITHCV_AndError_FromTFile(TFile *inputFile, TFile *inputFile_data,char *histoName,
  char *histoName_data, char *histotitle ,std::string xaxislabel, std::string label);
void PlotCVAndError_second_Track(PlotUtils::MnvH1D* hist, std::string label, SecondTrkVar second_Track, TCanvas *can, std::string title);
void DrawDATAWITHCV_AndError_FromTFile_Single_playlist(TFile *inputFile, TFile *inputFile_data,Pot_MapList POT_MC,Pot_MapList POT_DATA,
 ME_helium_Playlists playlist_name, char *histoName,char *histoName_data, char *histotitle ,std::string xaxislabel, std::string label, bool MakeBinwidth_Norm);

 void DrawDATAWITHCV_AndError_FromTFile_Single_playlist_Full_EMPTY(TFile *inputFileFULL,
   TFile *inputFileEMPTY, TFile *inputFile_Fulldata,TFile *inputFile_Emptydata,Pot_MapList POT_MC,Pot_MapList POT_DATA,
   ME_helium_Playlists playlist_name_FULL,ME_helium_Playlists playlist_name_EMPTY, char *histoName,
   char *histoName_data, char *histotitle ,std::string xaxislabel, std::string label, bool MakeBinwidth_Norm);


void DrawCVAndError_FromHIST(MnvH1D *hist_INCOMING, char *histotitle ,std::string xaxislabel,std::string yaxislabel, std::string pdf_name, bool Setgrid);
void DrawCVAndError_FromHIST(MnvH1D *hist, char *histotitle ,std::string xaxislabel,std::string yaxislabel, std::string pdf_name, bool Setgrid, bool LogX);
void DrawCVAndError_FromHIST(bool PrintALLerrorGroups , MnvH1D *hist, char *histotitle ,std::string xaxislabel,std::string yaxislabel,
  std::string pdf_name, bool Setgrid);
void DrawCVAndError_FromHIST_withVLine(MnvH1D *hist, char *histotitle ,std::string xaxislabel,std::string yaxislabel,
   std::string pdf_name, bool Setgrid, bool LogX, bool LogY, double xAxis_Vline);
void DrawStack_secTrk_Particle_FUll_EMPTY(bool my_debug, TFile *inputFile_FULL,TFile *inputFile_EMPTY,
   Pot_MapList POT_MC ,SecondTrkVar second_Trk_type ,ME_helium_Playlists PlayListFULL , ME_helium_Playlists PlayListEmpty,int doShape,
int logScale, std::string Hist_name_addON, MnvPlotter *plot, TCanvas *can, const char *pdf);
void DrawStack_secTrk_Particle_FUll_EMPTY_WITHDATA(bool my_debug, TFile *inputFile_FULL,TFile *inputFile_EMPTY,TFile *inputFile__DATA_FULL,TFile *inputFile_DATA_EMPTY, Pot_MapList POT_MC ,Pot_MapList POT_DATA ,SecondTrkVar second_Trk_type ,ME_helium_Playlists PlayListFULL , ME_helium_Playlists PlayListEmpty,int doShape,
  int logScale, std::string Hist_name_addON, MnvPlotter *plot, TCanvas *can, const char *pdf);

void Draw2DHist(MnvH2D *hist,   const char* xaxislabel,const char* yaxislabel,const char* Title, const char* pdf, TCanvas *can, MnvPlotter *plot);


void Draw2DHist_TFILE(TFile *inputFile, const char* histoName, const char *Title, const char* xaxislabel,const char* yaxislabel,
  const char* pdf, TCanvas *can, MnvPlotter *plot,  bool PrintText= true);

void Draw2DHist_Migration_TFILE(TFile *inputFile, const char* histoName, const char *Title, const char* xaxislabel,const char* yaxislabel,
  const char* pdf, TCanvas *can, MnvPlotter *plot, bool PrintText);

void Draw2DHist_histWithTProfile(MnvH2D *hist_input, const char *Title, const char* xaxislabel,const char* yaxislabel,
  const char* pdf, TCanvas *can, MnvPlotter *plot);


void DrawStack_Vertex_Material_FUll_EMPTY_WITHDATA(bool my_debug, TFile *inputFile_FULL,TFile *inputFile_EMPTY,TFile *inputFile_DATA_FULL,TFile *inputFile_DATA_EMPTY,
                                                   Pot_MapList POT_MC ,Pot_MapList POT_DATA ,CryoVertex CryroVertex_type,ME_helium_Playlists PlayListFULL , ME_helium_Playlists PlayListEmpty,int doShape,
                                                   int logScale, std::string Hist_name_addON, MnvPlotter *plot, TCanvas *can, const char *pdf);

void DrawMagration_heatMap(TH2D *h_migration, const char* xaxislabel,const char* yaxislabel, const char* Title, const char* pdf, TCanvas *can, MnvPlotter *plotter , bool includeFlows= false );
void DrawMagration_heatMap(MnvH2D *h_mig, const char* xaxislabel,const char* yaxislabel, const char* Title, const char* pdf, TCanvas *can, MnvPlotter *plotter , bool includeFlows= false ); // overloading function
void DrawMagration_heatMap_noText(MnvH2D *h_mig, const char* xaxislabel,const char* yaxislabel, const char* Title, const char* pdf, TCanvas *can, MnvPlotter *plotter , bool includeFlows= false );
void Draw2DHist_NumberFigures_TFILE(TFile *inputFile, const char* histoName, const char *Title, const char* xaxislabel,const char* yaxislabel,
               const char* pdf, TCanvas *can, MnvPlotter *plot);

void DrawSTACKfromHistFilio_FromTFile(TFile *inputFile_MCFULL, TFile *inputFile_MCEMPTY,  char *histoName_MC ,
  TFile *inputFile_DATAFULL,TFile *inputFile_DATAEMPTY,
  char *histoName_Data, Pot_MapStatusList POT_MC, Pot_MapStatusList POT_DATA,bool TrueifFullelseEmpty, char *histotitle,
  std::string xaxislabel, std::string pdf_label, bool DoBinwidthNorm, bool doSmallerrorgrounps, std::string units, StackType STACKTYPE, bool Debug );

  void DrawSTACKfromHistFilio_FromTFileNoData(TFile *inputFile_MCFULL, TFile *inputFile_MCEMPTY,  char *histoName_MC ,
    Pot_MapStatusList POT_MC, Pot_MapStatusList POT_DATA, char *histotitle, std::string xaxislabel, std::string pdf_label,
     bool DoBinwidthNorm, std::string units, StackType STACKTYPE, bool Debug, bool SetMaximum=false, double Maximum_group = 1 );


void DrawSINGLESTACKMCHistFilio_FromTFile(TFile *inputFile_MCinput,  char *histoName_MC ,char *histotitle, std::string xaxislabel, std::string pdf_label, bool DoBinwidthNorm, bool Debug );

void DrawRatio_FromTFile(TFile *inputFile_numerator, TFile *inputFile_demonator,  char *histoName_num,char *histoName_dem ,char *histotitle,
              std::string xaxislabel, std::string pdf_label, std::string units);

void Draw2DHist_Full_Empty_TFILE(TFile *inputFile_Full,TFile *inputFile_Empty, const char* histoName, Pot_MapList POT_MC, ME_helium_Playlists PlayListFULL, ME_helium_Playlists PlayListEmpty,
                const char *Title, const char* xaxislabel,const char* yaxislabel, const char* pdf, TCanvas *can, MnvPlotter *plot);

void MakeTrue_interactionPlots(std::vector <Trajector> input_vector,const char* Playlist ,double Spaceingcm ,const char* pdf, TCanvas *can, MnvPlotter *plot);

void MakeTrue_interactionPlots_WithRECOtrajector(std::vector <Trajector> input_vector,std::vector <Trajector_withTrueEnergyFraction> input_vector_RECO,const char* Playlist ,double Spaceingcm ,const char* pdf, TCanvas *can, MnvPlotter *plot);


void SetHist(PlotUtils::MnvH1D* hist, char *xaxislabel , char *yaxislabel);
void SetHist(TH1F * hist, char *xaxislabel , char *yaxislabel);
void SetHist_Data(PlotUtils::MnvH1D* hist, char *xaxislabel , char *yaxislabel);
void SetMaxforDraw(PlotUtils::MnvH1D* hist_to_Draw,PlotUtils::MnvH1D* hist);
void SetMaxforDraw(PlotUtils::MnvH1D* hist_to_Draw, PlotUtils::MnvH1D* hist,PlotUtils::MnvH1D* hist3 );
Hist_phyiscs_map Make_Physics_distribution_map_FromTFile(TFile *inputTFile, char *histoName_MC , bool UsePotScaling, double POTScale, ME_helium_Playlists playlist, bool IsRecoOrTruth );

void DrawCVAndError_FromHistPointer(MnvH1D *hist, char *histotitle ,std::string xaxislabel, std::string yaxislabel, std::string label, bool doBinwidth, bool MakeXaxisLOG);
void DrawCVAndError_FromHistPointer(MnvH1D *hist, char *histotitle ,std::string xaxislabel, std::string yaxislabel, std::string label, bool doBinwidth, bool MakeXaxisLOG, double maxY);
void Draw_2D_Panel_MC_Only_frompointer(MnvH2D *hist, char *histotitle, char *legend_title, std::string xaxislabel, std::string yaxislabel, const char* Zaxislabel , double max_x, double max_y, char *pdf_label, bool doBinwidth, bool MakeXaxisLOG, double x_projectionTxtsize = .025,  double y_projectionTxtsize = .03);
void Draw_2D_Panel_MC_Only_frompointer_YProjection(MnvH2D *hist, char *histotitle, char *legend_title, std::string xaxislabel, std::string yaxislabel,const char *Zaxislabel , double max_y, char *pdf_label, bool doBinwidth, bool MakeXaxisLOG);
void Draw_2D_Panel_MC_Only_frompointer_XProjection(MnvH2D *hist, char *histotitle, char *legend_title, std::string xaxislabel, std::string yaxislabel,const char *Zaxislabel , double max_x, char *pdf_label, bool doBinwidth, bool MakeXaxisLOG);

void Draw_Data_RECO_TRUTH_Hist_fromTFile_withConvolution( char *histoName_TRUTH,char *histoName_TRUTHConvolution,
  TFile *inputFile_MCinputFULL, TFile *inputFile_MCinputEmpty, char *histoName_MC,
  TFile *inputFile_DatainputFULL, TFile *inputFile_DatainputEmpty,char *histoName_data,
  char *Playlist_name_FULL, char *Playlist_name_EMPTY, std::string pdf_label, char *histotitle,
  char *xaxislabel,char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG,
   Pot_MapStatusList POT_DATA, Pot_MapStatusList POT_MC );

void Draw_Data_RECO_TRUTH_Hist_withConvolution_fromPointers(MnvH1D *hist_Data,
   MnvH1D *hist_RECOMC, MnvH1D *hist_TRUTH_Convolution,MnvH1D *hist_TRUTH,
  char *Playlist_name, std::string pdf_label, char *histotitle,char* playlist_status,
   char *xaxislabel,char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG, double Ymax, double ConvolutedBymm );


void DrawCVAndError_FromHIST_withFit(MnvH1D *hist, char *histotitle ,std::string xaxislabel,std::string yaxislabel,
  std::string pdf_name, bool Setgrid, bool PrintErrors=false , bool PrintallErrorGroups=false);

void DrawCVAndError_FromHIST_withFit(MnvH1D *hist, char *histotitle ,std::string xaxislabel,std::string yaxislabel,
  std::string pdf_name, bool Setgrid , double &sigma_return , double &TotalN_return, double &chi_sq_return, int &NDF_return,
  double &Mean_return,  double &Constant_return, bool PrintErrors=false , bool PrintallErrorGroups=false );




//draw fits
/*
void DrawConvolutedGassian_SingleFit(TFile *input_TFile,  char *histoName, char *histoName_Label , std::string pdf_label,
  char *histotitle, char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm,
  double MinY, double MaxY, double FitRange_lowX, double FitRange_highX);*/
void MakeCVS_from_hist(TFile *input_TFile,  char *histoName, char *histoName_Label );

void MakeCVS_from_HISTS(char *histoName_TRUTH, TFile *inputFile_MCinputFULL, TFile *inputFile_MCinputEmpty, char *histoName_MC,
  TFile *inputFile_DatainputFULL, TFile *inputFile_DatainputEmpty,char *histoName_data,
  char *Playlist_name_FULL, char *Playlist_name_EMPTY, char *File_Title,char *varibleName, Pot_MapStatusList POT_DATA, Pot_MapStatusList POT_MC );

void Draw_DataHist_fromTFile(TFile *inputFile_DatainputFULL, TFile *inputFile_DatainputEmpty,
   char *histoName_data, char *Playlist_name_FULL, char *Playlist_name_Empty, std::string pdf_label,
    char *histotitle, char *xaxislabel,char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG, Pot_MapStatusList POT_DATA );

void Draw_DataWITHMC_Hist_fromTFile(TFile *inputFile_MCinputFULL, TFile *inputFile_MCinputEmpty, char *histoName_MC,
  TFile *inputFile_DatainputFULL, TFile *inputFile_DatainputEmpty,char *histoName_data,
  char *Playlist_name_FULL, char *Playlist_name_EMPTY, std::string pdf_label, char *histotitle,
  char *xaxislabel,char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG, Pot_MapStatusList POT_DATA, Pot_MapStatusList POT_MC );

void Draw_DataWITHMC_SingleHistinput(MnvH1D *hist_MC, MnvH1D *hist_Data,
  char *Playlist_name, std::string pdf_label, char *histotitle, std::string units,
  char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG);

  void Draw_DataWITHMC_SingleHistinput_withRatio(MnvH1D *hist_MC, MnvH1D *hist_Data,
    char *Playlist_name, std::string pdf_label, char *histotitle, std::string units,
     char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG,
     bool MakeYaxisLOG=false, bool drawAllErrorGroups= true);

     void Draw_DataWITHMC_SingleHistinput_withRatioCrossSection(MnvH1D *hist_MC, MnvH1D *hist_Data,
       char *Playlist_name, std::string pdf_label, char *histotitle, std::string units,
        char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG , bool drawAllErrorGroups = true );

void Draw_DataWITHMC_SingleHistinput(MnvH1D *hist_MC, MnvH1D *hist_Data,
  char *Playlist_name, std::string pdf_label, char *histotitle, std::string units,
  char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG, double POT_data, double POT_MC,  bool drawAllErrorGroups=true);

void Draw_DataWITHMC_SingleHistinput_withRatio(MnvH1D *hist_MC, MnvH1D *hist_Data,
  char *Playlist_name, std::string pdf_label, char *histotitle, std::string units,
  char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG,
  double POT_data, double POT_MC , bool drawAllErrorGroups= true );

void Draw_Data_RECO_TRUTH_Hist_fromTFile(char *histoName_TRUTH,
    TFile *inputFile_MCinputFULL, TFile *inputFile_MCinputEmpty, char *histoName_MC,
    TFile *inputFile_DatainputFULL, TFile *inputFile_DatainputEmpty,char *histoName_data,
    char *Playlist_name_FULL, char *Playlist_name_EMPTY, std::string pdf_label, char *histotitle,
    char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG, Pot_MapStatusList POT_DATA, Pot_MapStatusList POT_MC );

    void Draw_Data_RECO_TRUTH_Hist_fromPointer( MnvH1D *histMC_TRUTH, MnvH1D *histMC_RECO,  MnvH1D *hist_Data,
      char *Playlist_name, char* playlist_status, std::string pdf_label, char *histotitle,
       char *xaxislabel,char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG, double Ymax );


    void   DrawPie_Figures_EventCutRate(TFile *inputFile_TRUTHBranch,  char* TGraphName_TRUTHBranch,
          TFile *inputFile_RECOBranch,  char* TGraphName_RECOBranch_TRUE ,  char* TGraphName_RECOBranch_TRUE_RECO,
          ME_helium_Playlists playlist, ME_helium_Status Crytank_status,  const char* pdf,
         TCanvas *can, MnvPlotter *plotter, char * Title);

void DrawPieFigures(Hist_phyiscs_map Input_map,  const char* pdf, TCanvas *can, MnvPlotter *plotter, bool IsReco, bool MakCVS=false, const char* CVS_title = "");
void DrawPieFigures_withTrackType(Hist_phyiscs_map_withtrack Input_map,  const char* pdf, TCanvas *can, MnvPlotter *plotter, bool IsReco, bool MakCVS, const char* CVS_title, char * Title );
void Draw_TrackTypePieFigures(Hist_map_track Input_map,  const char* pdf, TCanvas *can, MnvPlotter *plotter, bool IsRecoOrData, bool MakCVS, const char* CVS_title, char * Title );
void Draw_MCHist_fromTFile(TFile *inputFile_MCinput,  char *histoName_MC, std::string pdf_label, char *histotitle, char *xaxislabel,char* yaxislabel, bool DoBinwidthNorm );
TGraphErrors  *MakeTGraph_from_Mvn1HD(TFile *inputFile_MCinput,  char *histoName_MC);
TGraphErrors  *MakeTGraph_from_Vectors(std::vector<double> Y_para,  std::vector<double> X_para);
TGraphErrors  *MakeTGraph_from_VectorsErrors(std::vector<double> Y_para, std::vector<double> y_para_errors, std::vector<double> X_para);
TGraphErrors  *MakeTGraph_from_VectorsNoErrors(std::vector<double> Y_para,  std::vector<double> X_para);
void Draw_TGraph_fit(TFile *inputFile_MCinput,  char *histoName_MC, std::string pdf_label, char *histotitle, char *xaxislabel,char* yaxislabel);
void Draw_MCHist_fromTFile_andFIT(TFile *inputFile_MCinput,  char *histoName_MC, std::string pdf_label, char *histotitle, char *xaxislabel,char* yaxislabel);
void Draw_MCHist_WithErrorBands_fromTFile_andFIT(TFile *inputFile_MCinput,  char *histoName_MC, std::string pdf_label, char *histotitle, char *xaxislabel,char* yaxislabel);
void Draw_MCHist_fromTFile_SMEARING(TFile *inputFile_MCinput,  char *histoName_MC_CV, char *histoName_MC_shifts, std::string pdf_label, char *histotitle, char *xaxislabel,char* yaxislabel );
void Draw_MCHist_withErrorSys_fromTFile(TFile *inputFile_MCinput,  char *histoName_MC, std::string pdf_label, char *histotitle, char *xaxislabel,char* yaxislabel, bool DoBinwidthNorm );

void Draw_RATIO_fromTFiles(TFile *inputFile_Top,  char *histoName_Top, char *histoName_TopLabel ,
  TFile *inputFile_Bottom,  char *histoName_Bottom,char *histoName_BottomLabel, char *histoName_Ratio, std::string pdf_label,
   char *histotitle, char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm );

void Draw_RATIO_fromTFiles(TFile *inputFile_Top,  char *histoName_Top, char *histoName_TopLabel ,
  TFile *inputFile_Bottom,  char *histoName_Bottom,char *histoName_BottomLabel, char *histoName_Ratio, std::string pdf_label,
  char *histotitle, char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm, double MinY, double MaxY  );

void Draw_MCHist_withErrorSys_fromTFile(TFile *inputFile_MCFull,TFile *inputFile_MCEmpty,  char *histoName_MC,
  Pot_MapStatusList POT_MC, Pot_MapStatusList POT_DATA , std::string pdf_label, char *histotitle, char *xaxislabel,
  char* yaxislabel, bool DoBinwidthNorm );

void  DrawVertex_Cryotank_X_Y_R_Vs_Z(std::vector<Vertex_XYZ> input_XYZ_vector ,
    const char* Playlist, const char* title ,const char* pdf, TCanvas *can, MnvPlotter *plot);
void DrawVertex_Cryotank_X_Y_R_Vs_Z(std::vector<Vertex_XYZ> input_XYZ_vector_He ,std::vector<Vertex_XYZ> input_XYZ_vector_Al,
  const char* Playlist, const char* title ,const char* pdf, TCanvas *can, MnvPlotter *plot);

  void DrawFULLStat_CV_SystematicErr(ME_playlist_TFileMAP FullMCMap, Pot_MapList FullMC_scalerMap,
                                      ME_playlist_TFileMAP EmptyMCMap,     Pot_MapList EmptyMC_scalerMap,
                                      ME_playlist_TFileMAP FullDataMap, Pot_MapList FullData_scalerMap,
                                      ME_playlist_TFileMAP EmptyDataMap, Pot_MapList EmptyData_scalerMap,
     char *histoName_MC ,char *histoName_data, std::string units, std::string pdf_label, char* hist_title,
     char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG, bool MakeYaxisLOG, bool DrawallErrorGroups=true
   );



void DrawFULLStatCOMBINED_CV_SystematicErr(ME_playlist_TFileMAP FullMCMap, Pot_MapList FullMC_scalerMap,
                                       ME_playlist_TFileMAP EmptyMCMap,     Pot_MapList EmptyMC_scalerMap,
                                       ME_playlist_TFileMAP FullDataMap, Pot_MapList FullData_scalerMap,
                                       ME_playlist_TFileMAP EmptyDataMap, Pot_MapList EmptyData_scalerMap,
      char *histoName_MC ,char *histoName_data, std::string units, std::string pdf_label, char* hist_title,
      char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG, bool DrawallErrorGroups=true
    );

void DrawSTACKfromHistFilio_FULLStats(ME_playlist_TFileMAP FullMCMap, Pot_MapList FullMC_scalerMap,
                                        ME_playlist_TFileMAP EmptyMCMap,     Pot_MapList EmptyMC_scalerMap,
                                        ME_playlist_TFileMAP FullDataMap, Pot_MapList FullData_scalerMap,
                                        ME_playlist_TFileMAP EmptyDataMap, Pot_MapList EmptyData_scalerMap,
                                       char *histoName_MC , char *histoName_Data, char *histotitle,
     std::string xaxislabel, std::string pdf_label, bool DoBinwidthNorm, std::string units, StackType STACKTYPE, bool Debug );


void DrawSTACKfromHistFilio_FULLStatsCOMBINED(ME_playlist_TFileMAP FullMCMap, Pot_MapList FullMC_scalerMap,
                                          ME_playlist_TFileMAP EmptyMCMap,     Pot_MapList EmptyMC_scalerMap,
                                          ME_playlist_TFileMAP FullDataMap, Pot_MapList FullData_scalerMap,
                                          ME_playlist_TFileMAP EmptyDataMap, Pot_MapList EmptyData_scalerMap,
                                         char *histoName_MC , char *histoName_Data, char *histotitle,
       std::string xaxislabel, std::string pdf_label, bool DoBinwidthNorm, std::string units, StackType STACKTYPE, bool Debug );

void Draw_2D_Panel_MC_andData_frompointer(MnvH2D *hist_Data, MnvH2D *hist_MC, char *histotitle, std::string xaxislabel,
          std::string yaxislabel,const char *Zaxislabel , double max_x, double max_y, char *pdf_label, bool doBinwidth, bool MakeXaxisLOG,
           double x_projectionTxtsize, double y_projectionTxtsize );

void MakeData_trajector(std::vector <Trajector_DATA> input_vector, const char* Playlist ,double Spaceingcm ,const char* pdf, TCanvas *can, MnvPlotter *plot);

void Draw2DHist_hist(MnvH2D *hist_input, const char *Title, const char* xaxislabel,const char* yaxislabel,
   const char* pdf, TCanvas *can, MnvPlotter *plot);

   void Draw2DRatio_FromTFile(TFile *inputFile_numerator, TFile *inputFile_demonator,char *histoName_num,char *histoName_dem,
      char *num_labelname_y, char *dem_labelname_y, char *num_labelname_x, char *dem_labelname_x,char *histotitle, const char* pdf,TCanvas *can, MnvPlotter *plot);

void DrawTGraph(TGraphErrors *g_TGraph1, TGraphErrors *g_TGraph2, TGraphErrors *g_TGraph3, const char* xaxislabel,const char* yaxislabel,
      const char* Title,const char* legend_Title1,const char* legend_Title2, const char* legend_Title3,
      const char* pdf, TCanvas *can, MnvPlotter *plot, bool MakeXaxisLOG, bool MakeYaxisLOG );
void DrawTGraph(TGraphErrors *g_TGraph1, TGraphErrors *g_TGraph2, const char* xaxislabel,const char* yaxislabel,
      const char* Title,const char* legend_Title1,const char* legend_Title2,
      const char* pdf, TCanvas *can, MnvPlotter *plot, bool MakeXaxisLOG, bool MakeYaxisLOG );
void DrawTGraph(TGraphErrors *g_TGraph, const char* xaxislabel,const char* yaxislabel, const char* Title,const char* legend_Title,
        const char* pdf, TCanvas *can, MnvPlotter *plot, bool MakeXaxisLOG, bool MakeYaxisLOG );

void Draw_TGraphs_fitParams(std::vector<GaussianFitsParms> GaussianFits_values_Resolution_vector,
  const char* pdf_label, char *histotitle,TCanvas *cE, MnvPlotter *mnvPlotter, bool Xlog = false ,bool Ylog=false);

void Draw_TGraphs_fitParams(std::vector<GaussianFitsParms> GaussianFits_values_Resolution_vector_helium,
                          std::vector<GaussianFitsParms> GaussianFits_values_Resolution_vector_nonhelium,
                          std::vector<GaussianFitsParms> GaussianFits_values_Resolution_vector_total,
                          const char* pdf_label, char *histotitle, TCanvas *cE, MnvPlotter *mnvPlotter,
                         bool Xlog=false ,bool Ylog=false);

std::vector<Track_Map> Track_vector( TObjArray * Hists_vector, bool doPOTscaling, double scaler);
std::vector<boolNTrack_Map> boolNTrack_vector( TObjArray * Hists_vector, bool doPOTscaling, double scaler);
std::vector<VertexOptions_Map> vertexOption_vector( TObjArray * Hists_vector, bool doPOTscaling, double scaler);
Hist_phyiscs_map_withtrack Make_Physics_withTrack_distribution_map_FromTFile(TFile *inputTFile, char *histoName_MC , bool UsePotScaling, double POTScale, ME_helium_Playlists playlist, bool IsRecoOrTruth );
Hist_map_track Make_Track_distribution_map_FromTFile(TFile *inputTFile, char *histoName , bool UsePotScaling, double POTScale, ME_helium_Playlists playlist, bool IsRecoOrTruth , bool isData );

void DrawSTACK_FORDATAONLY_fromHistFilio_FromTFile( TFile *inputFile_DATAFULL,TFile *inputFile_DATAEMPTY, char *histoName_Data, Pot_MapStatusList POT_DATA, bool TrueifFullelseEmpty, char *histotitle,
  std::string xaxislabel, std::string pdf_label, bool DoBinwidthNorm,  std::string units, StackType STACKTYPE, bool Debug );

void Draw_XDistribution_PerBinWithGaussFit_2DHist(MnvH2D *hist_input, const char *Title, const char* xaxislabel,const char* yaxislabel,
      const char* pdf, TCanvas *can, MnvPlotter *plot, bool Setgrid, Double_t maxY);

void Draw_XDistribution_PerBinWithGaussFit_2DHist(MnvH2D *hist_total, MnvH2D *hist_input_Helium, MnvH2D *hist_input_NonHelium, const char *Title, const char* xaxislabel,const char* yaxislabel,
        const char* pdf, TCanvas *can, MnvPlotter *plot, bool Setgrid, Double_t maxY , bool LogX=false, bool LogY=false  );


  void FillFitParms(TF1 *gfit, GaussianFitsParms &FitParms );

void   DrawCVAndError_From2HIST_withFit(MnvH1D *hist_total, MnvH1D *histHelium, MnvH1D *histnonHelium,
                                       char *histotitle ,std::string xaxislabel,std::string yaxislabel,
                                       std::string pdf_name, bool Setgrid ,
                                       GaussianFitsParms &total_FitParms,
                                       GaussianFitsParms &helium_FitParms ,
                                       GaussianFitsParms &nonhelium_FitParms, 
  bool PrintErrors , bool PrintallErrorGroups, bool BinWidthNorm=false );


#endif
