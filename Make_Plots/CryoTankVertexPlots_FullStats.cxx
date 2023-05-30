#include "CryoTankVertexPlots_FullStats.h"
//////////////////////////////////////////////////////////////////////////////
void MakeLatexForCryoVertexFiguresCVandALLErrors(std::string output_name ,std::vector<CryoVertex> CryoVertex_vector, std::string PDF_cv_name, int NError_Groups);
void MakeLatexForCryoVertexFiguresFORStacks(std::string output_name ,std::vector<CryoVertex> CryoVertex_vector ,  std::string pdf_name);
void MakeLatex_CryoVertexStacks(std::string output_name, std::vector<CryoVertex> CryoVertex_vector, std::string pdf_name_CV, int inputstart );
void MakeLatex_CryoVertexCV_Error(std::string output_name, std::vector<CryoVertex> CryoVertex_vector, std::string pdf_name_CV, int inputstart );
void Appendtotxt_2D_2_Panel_Playlists(std::string output_name ,  std::string pdf_name_CV, int First_page,int second_page, char *Var_name );
//ME_playlist_TFileMAP MakeTFileMap(ME_playlist_RootPathMAP MAP_RootPath);
void DrawEffPlots(ME_playlist_TFileMAP Full_Nom_Map, ME_playlist_TFileMAP Full_Dom_Map,
                  ME_playlist_TFileMAP Empty_Nom_Map, ME_playlist_TFileMAP Empty_Dom_Map,
                  double Full_MC_Full_Data,
                  double Empty_MC_Full_Data,
                   char *histoName_Nom,char *histoName_Dom, char *hist_histFolioName,
                   MnvPlotter *mnvPlotter, TCanvas *can,  char *pdf);


void Draw2DPlots(ME_playlist_TFileMAP Full_Map,
  ME_playlist_TFileMAP Empty_Map,
  double Full_MC_Full_Data,
  double Empty_MC_Full_Data,
  char *histoName ,char *xaxis, char *yaxis, char *Plot_title,
  MnvPlotter *mnvPlotter, TCanvas *can,  char *pdf);

  void Draw2DPlots_Panel(ME_playlist_TFileMAP Full_Map, ME_playlist_TFileMAP Full_Data_Map,
                         ME_playlist_TFileMAP Empty_Map, ME_playlist_TFileMAP Empty_Data_Map,
                    double Full_MC_Full_Data,
                    double Empty_MC_Full_Data,
                    double Empty_Data_Full_Data,
                     char *hist_MCName,
                     char *hist_DataName,
                     char *xaxis, char *yaxis,char *unitsX,char *unitsY, char *Plot_title,  std::vector<double> YMultipliers, std::vector<double> XMultipliers,
                     bool do_bin_width_norm ,bool statPlusSysDATA , bool statPlusSysMC ,
                     MnvPlotter *mnvPlotter, TCanvas *can,  char *pdf, double XprotextSize, double YprotextSize, double FractionalErrorMax);

void Draw2DMigration_Panel(ME_playlist_TFileMAP Full_Map,
  ME_playlist_TFileMAP Empty_Map,
  double Full_MC_Full_Data,
  double Empty_MC_Full_Data,
  char *hist_MCName,
  char *hist_MCName_RECO,
  char *hist_MCName_TRUTH,
  std::vector<double> Xbins_vector,
  std::vector<double> Ybins_vector,
  char *xaxis, char *yaxis ,
  MnvPlotter *mnvPlotter, TCanvas *can,  char *pdf);

  void Draw2D_EfficiencyPlots_Panel(ME_playlist_TFileMAP Full_Map, ME_playlist_TFileMAP Full_TRUTH_Map,
                    ME_playlist_TFileMAP Empty_Map, ME_playlist_TFileMAP Empty_TRUTH_Map,
                    double Full_MC_Full_Data,
                    double Empty_MC_Full_Data,
                     char *hist_MCName,
                     char *hist_TruthName,
                     char *xaxis, char *yaxis,char *unitsX,char *unitsY, char *Plot_title,  std::vector<double> YMultipliers, std::vector<double> XMultipliers,
                     bool do_bin_width_norm ,bool statPlusSysDATA , bool statPlusSysMC ,
                     MnvPlotter *mnvPlotter, TCanvas *can,  char *pdf, double XprotextSize, double YprotextSize, double FractionalErrorMax);

void Draw2D_EfficiencyPlots_Panel(ME_playlist_RootPathMAP Full_Map_RootMap, ME_playlist_RootPathMAP Full_Map_RootMapTRUTH,
  ME_playlist_RootPathMAP Empty_Map_RootMap, ME_playlist_RootPathMAP Empty_Map_RootMapTRUTH,
  double Full_MC_Full_Data,
  double Empty_MC_Full_Data,
  char *hist_MCName,
  char *hist_TruthName,
  char *xaxis, char *yaxis,char *unitsX,char *unitsY, char *Plot_title,
  std::vector<double> YMultipliers, std::vector<double> XMultipliers,
  bool do_bin_width_norm ,bool statPlusSysDATA , bool statPlusSysMC ,
  MnvPlotter *mnvPlotter, TCanvas *can,  char *pdf, double XprotextSize,
  double YprotextSize, double FractionalErrorMax);
/*
void Draw2DStackPlots_Panel(ME_playlist_TFileMAP Full_Map, ME_playlist_TFileMAP Full_Data_Map,
  ME_playlist_TFileMAP Empty_Map, ME_playlist_TFileMAP Empty_Data_Map,
  double Full_MC_Full_Data,
  double Empty_MC_Full_Data,
  double Empty_Data_Full_Data,
  char *histoName_MC,
  char *Charstacktype,
  char *hist_DataName,
  char *xaxis, char *yaxis,char *unitsX,char *unitsY, char *Plot_title,  std::vector<double> YMultipliers, std::vector<double> XMultipliers,
  bool do_bin_width_norm,
  MnvPlotter *mnvPlotter, TCanvas *can,  char *pdf, double XprotextSize, double YprotextSize, std::vector<int> fillColors);*/

  void Draw2DStackPlots_Panel_Full_Empty(ME_playlist_TFileMAP Full_Map, ME_playlist_TFileMAP Full_Data_Map,
                    ME_playlist_TFileMAP Empty_Map, ME_playlist_TFileMAP Empty_Data_Map,
                    double Full_MC_Full_Data,
                    double Empty_MC_Full_Data,
                    double Empty_Data_Full_Data,
                     char *histoName_MC,
                     char *Charstacktype,
                      std::vector<std::string> StackNames,
                     char *hist_DataName,
                     char *xaxis, char *yaxis,char *unitsX,char *unitsY, char *Plot_title,  std::vector<double> YMultipliers, std::vector<double> XMultipliers,
                     bool do_bin_width_norm,
                     MnvPlotter *mnvPlotter, TCanvas *can,  char *pdf, double XprotextSize, double YprotextSize, std::vector<int> fillColors);


void Draw2DStackPlots_Panel_Full_Empty(ME_playlist_RootPathMAP Full_Map_RootMap, ME_playlist_RootPathMAP Full_Data_Map_RootMap,
  ME_playlist_RootPathMAP Empty_Map_RootMap, ME_playlist_RootPathMAP Empty_Data_Map_RootMap,
  double Full_MC_Full_Data,
  double Empty_MC_Full_Data,
  double Empty_Data_Full_Data,
  char *histoName_MC,
  char *Charstacktype,
  std::vector<std::string> StackNames,
  char *hist_DataName,
  char *xaxis, char *yaxis,char *unitsX,char *unitsY, char *Plot_title,  std::vector<double> YMultipliers, std::vector<double> XMultipliers,
  bool do_bin_width_norm,
  MnvPlotter *mnvPlotter, TCanvas *can,  char *pdf, double XprotextSize, double YprotextSize, std::vector<int> fillColors);


void Draw2DStackPlots_Panel_Full_Empty_Extracted(TFile *TFileinput,
  char *histoName_MC,
  char *Charstacktype,
  char *hist_DataName,
  char *xaxis, char *yaxis,char *unitsX,char *unitsY, char *Plot_title,  std::vector<double> YMultipliers, std::vector<double> XMultipliers,
  bool do_bin_width_norm,
  MnvPlotter *mnvPlotter, TCanvas *can,  char *pdf, double XprotextSize, double YprotextSize, std::vector<int> fillColors);

  void Draw2DPlots_Panel(ME_playlist_RootPathMAP Full_Map_RootMap, ME_playlist_RootPathMAP Full_Data_Map_RootMap,
    ME_playlist_RootPathMAP Empty_Map_RootMap, ME_playlist_RootPathMAP Empty_Data_Map_RootMap,
    double Full_MC_Full_Data,
    double Empty_MC_Full_Data,
    double Empty_Data_Full_Data,
    char *hist_MCName,
    char *hist_DataName,
    char *xaxis, char *yaxis,char *unitsX,char *unitsY, char *Plot_title,  std::vector<double> YMultipliers, std::vector<double> XMultipliers,
    bool do_bin_width_norm ,bool statPlusSysDATA , bool statPlusSysMC ,
    MnvPlotter *mnvPlotter, TCanvas *can,  char *pdf, double XprotextSize, double YprotextSize, double FractionalErrorMax);

    void DrawCombined_Resolution_withGaussianFit(ME_playlist_RootPathMAP Full_Map_RootMap,
      ME_playlist_RootPathMAP Empty_Map_RootMap,double Full_MC_Full_Data,
    double Empty_MC_Full_Data,char *hist_MCName,char *histotitle,  std::string xaxislabel, std::string yaxislabel,
    bool Setgrid, bool PrintErrors , bool PrintallErrorGroups, bool do_bin_width_norm ,
    MnvPlotter *mnvPlotter, TCanvas *can, std::string pdf_name);

    void Draw_3Resolution_CryoVertex_FULL_EMPTY_RecoBranch(ME_playlist_RootPathMAP Full_Map_RootMap,
                                                          ME_playlist_RootPathMAP Empty_Map_RootMap,
                                                          double Full_MC_Full_Data,
                                                          double Empty_MC_Full_Data,
       const char *histoName_region1, const char *histoName_region2, const char *histoName_region3,
      int logScale, MnvPlotter *plot, TCanvas *can, const char *pdf, char *CutsApplied,
       bool doBinwidth, bool isFractional , bool isAreaNormalized, double Ymax, CryoVertex CryoVertex_type  );



void Kin(bool &cutsOn, bool &my_norm, bool &my_debug, const char *userDir, int &Print_Systematics ) {
TH1::AddDirectory(false);
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~       Starting Plotter: CryoVertex Plots         ~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::vector<ME_helium_Playlists> GetPlayListVector_MC();
std::vector<ME_helium_Playlists> GetPlayListVector_DATA();
const std::vector< ME_helium_Playlists> kMEPlayList_Vector = GetPlayListVector_MC();
std::vector<ME_helium_Playlists> kPlayListVector_DATA =GetPlayListVector_DATA();
const std::vector<CryoVertex> kCryoVertexVaribles_vector = GetCryoVertexVaribles();
int N_Error_groups;
if(Print_Systematics==2 || Print_Systematics == 1) {N_Error_groups=0;}
else if (Print_Systematics==0){N_Error_groups=7;}
Pot_MapList POT_MC,POT_DATA;
Pot_MapStatusList POT_MC_Status, POT_DATA_Status;
TCanvas *can = new TCanvas("can");
MnvPlotter *mnv_plot = new MnvPlotter();
 char text_title_pdf1[2024];
 char text_title_pdf2[2024];
 char text_title_pdf3[2024];
 char text_title_pdf4[2024];
 char StacksInteraction_title_pdf1[2024];
 char StacksInteraction_title_pdf2[2024];
 char StacksInteraction_title_pdf3[2024];
 char StacksInteraction_title_pdf4[2024];

 char StacksMaterial_title_pdf1[2024];
 char StacksMaterial_title_pdf2[2024];
 char StacksMaterial_title_pdf3[2024];
 char StacksMaterial_title_pdf4[2024];

 char StacksParticle_title_pdf1[2024];
 char StacksParticle_title_pdf2[2024];
 char StacksParticle_title_pdf3[2024];
 char StacksParticle_title_pdf4[2024];

time_t now = time(0);
tm *ltm = localtime(&now);
char timeset[2024];
char timeset_nonstacks[2024];
std::string SysError_printLabel = PrintLabel_Systematics(Print_Systematics);
auto Playlist_names =  MakePlaylistString(kMEPlayList_Vector);
sprintf(timeset_nonstacks,"%i_%i_%i_%i_%s_%s", 1 + ltm->tm_mon,ltm->tm_mday, ltm->tm_hour,ltm->tm_min, SysError_printLabel.c_str(), Playlist_names.c_str());
sprintf(timeset, "%i_%i_%i_%i", 1 + ltm->tm_mon,ltm->tm_mday, ltm->tm_hour,ltm->tm_min);

sprintf(text_title_pdf1, "Plots_CryoVertex_SystErrors_%s.pdf(",timeset );
//can -> Print(text_title_pdf1);
sprintf(text_title_pdf2, "Plots_CryoVertex_SystErrors_%s.pdf",timeset );
sprintf(text_title_pdf2, "Plots_CryoVertex_SystErrors_%s.pdf",timeset );
sprintf(text_title_pdf3, "Plots_CryoVertex_SystErrors_%s.pdf)",timeset );
sprintf(text_title_pdf4, "Plots_CryoVertex_SystErrors_%s",timeset );



sprintf(StacksInteraction_title_pdf1, "Plots_CryoVertex_InteractionStacks_fullstats_%s.pdf(",timeset );
//can -> Print(StacksInteraction_title_pdf1);
sprintf(StacksInteraction_title_pdf2, "Plots_CryoVertex_InteractionStacks_fullstats_%s.pdf",timeset );
sprintf(StacksInteraction_title_pdf3, "Plots_CryoVertex_InteractionStacks_fullstats_%s.pdf)",timeset );
sprintf(StacksInteraction_title_pdf4, "Plots_CryoVertex_InteractionStacks_fullstats_%s",timeset );
std::string pdf_InteractionStacks = string(StacksInteraction_title_pdf4);
//
//sprintf(StacksParticle_title_pdf1, "Plots_CryoVertex_ParticleStacks_fullstats_%s.pdf(",timeset );
//can -> Print(StacksParticle_title_pdf1);
//sprintf(StacksParticle_title_pdf2, "Plots_CryoVertex_ParticleStacks_fullstats_%s.pdf",timeset );
//sprintf(StacksParticle_title_pdf3, "Plots_CryoVertex_ParticleStacks_fullstats_%s.pdf)",timeset );
//sprintf(StacksParticle_title_pdf4, "Plots_CryoVertex_ParticleStacks_fullstats_%s",timeset );
std::string pdf_ParticleStacks = string(StacksParticle_title_pdf4);


sprintf(StacksMaterial_title_pdf1, "Plots_CryoVertex_MaterialStacks_fullstats_Fid_convolution_wgts.pdf(" );
can -> Print(StacksMaterial_title_pdf1);
sprintf(StacksMaterial_title_pdf2, "Plots_CryoVertex_MaterialStacks_fullstats_Fid_convolution_wgts.pdf" );
sprintf(StacksMaterial_title_pdf3, "Plots_CryoVertex_MaterialStacks_fullstats_Fid_convolution_wgts.pdf)" );
sprintf(StacksMaterial_title_pdf4, "Plots_CryoVertex_MaterialStacks_fullstats_Fid_convolution_wgts" );
std::string pdf_MaterialStacks = string(StacksMaterial_title_pdf4);

std::map<StackType, std::string>  PDF_stackMap;

PDF_stackMap[kMaterial] = pdf_MaterialStacks;
PDF_stackMap[kInteraction] = pdf_InteractionStacks;
PDF_stackMap[kParticle] = pdf_ParticleStacks;


ME_playlist_RootPathMAP MAP_RootPath_Empty_MC;
//ME_playlist_RootPathMAP MAP_RootPath_OtherEmpty_MC;
ME_playlist_RootPathMAP MAP_RootPath_Full_MC;

ME_playlist_RootPathMAP MAP_RootPath_Empty_DATA;
ME_playlist_RootPathMAP MAP_RootPath_Full_DATA;


ME_playlist_RootPathMAP MAP_RootPath_Empty_MC_TRUTH;
ME_playlist_RootPathMAP MAP_RootPath_Full_MC_TRUTH;
ME_playlist_RootPathMAP MAP_RootPath_Empty_MC_Eff;
ME_playlist_RootPathMAP MAP_RootPath_Full_MC_Eff;

std::vector<StackType> StackType_vector;

StackType_vector.push_back(kMaterial );
//StackType_vector.push_back(kInteraction);
//StackType_vector.push_back(kParticle);





//StackType_vector.push_back(kTrackType);
//StackType_vector.push_back(kVertexOptions);
//StackType_vector.push_back(kboolNTrack);


/////////////////
/// MC
/////////////////
// Empty Playlist
/////////////////
//auto PlaylistME_1G_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1G_MC_All_SysErrorsOn.root";
//auto PlaylistME_1A_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1A_MC_All_SysErrorsOn.root";
//auto PlaylistME_1L_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1L_MC_All_SysErrorsOn.root";
//auto PlaylistME_1M_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1M_MC_All_SysErrorsOn.root";
//auto PlaylistME_1N_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1N_MC_All_SysErrorsOn.root";

auto PlaylistME_1G_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1G_MC_StatsONLYErrors_ThreeRegion_sideBandShift_Noshift_noWgts_NoFid_ShiftAll_Convolution.root";
auto PlaylistME_1A_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1A_MC_StatsONLYErrors_ThreeRegion_sideBandShift_Noshift_noWgts_NoFid_ShiftAll_Convolution.root";
auto PlaylistME_1L_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1L_MC_StatsONLYErrors_ThreeRegion_sideBandShift_Noshift_noWgts_NoFid_ShiftAll_Convolution.root";
auto PlaylistME_1M_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1M_MC_StatsONLYErrors_ThreeRegion_sideBandShift_Noshift_noWgts_NoFid_ShiftAll_Convolution.root";
auto PlaylistME_1N_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1N_MC_StatsONLYErrors_ThreeRegion_sideBandShift_Noshift_noWgts_NoFid_ShiftAll_Convolution.root";

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

auto PlaylistME_1G_MC_path_1D = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1G_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";
auto PlaylistME_1A_MC_path_1D = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1A_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";
auto PlaylistME_1L_MC_path_1D = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1L_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";
auto PlaylistME_1M_MC_path_1D = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1M_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";
auto PlaylistME_1N_MC_path_1D = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1N_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";

ME_playlist_TFileMAP EmptyTFile_Map_MC_1D;
TFile *PlaylistME_1G_TFile_1D = new TFile(PlaylistME_1G_MC_path_1D);
TFile *PlaylistME_1A_TFile_1D = new TFile(PlaylistME_1A_MC_path_1D);
TFile *PlaylistME_1L_TFile_1D = new TFile(PlaylistME_1L_MC_path_1D);
TFile *PlaylistME_1M_TFile_1D = new TFile(PlaylistME_1M_MC_path_1D);
TFile *PlaylistME_1N_TFile_1D = new TFile(PlaylistME_1N_MC_path_1D);

EmptyTFile_Map_MC_1D.insert(std::make_pair(kMEPlayList_Vector.at(0),PlaylistME_1G_TFile_1D));
EmptyTFile_Map_MC_1D.insert(std::make_pair(kMEPlayList_Vector.at(1),PlaylistME_1A_TFile_1D));
EmptyTFile_Map_MC_1D.insert(std::make_pair(kMEPlayList_Vector.at(2),PlaylistME_1L_TFile_1D));
EmptyTFile_Map_MC_1D.insert(std::make_pair(kMEPlayList_Vector.at(3),PlaylistME_1M_TFile_1D));
EmptyTFile_Map_MC_1D.insert(std::make_pair(kMEPlayList_Vector.at(4),PlaylistME_1N_TFile_1D));



auto PlaylistME_1G_MC_path_Eff = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1G_MC_StatsONLYErrors_Efficiency.root";
auto PlaylistME_1A_MC_path_Eff = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1A_MC_StatsONLYErrors_Efficiency.root";
auto PlaylistME_1L_MC_path_Eff = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1L_MC_StatsONLYErrors_Efficiency.root";
auto PlaylistME_1M_MC_path_Eff = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1M_MC_StatsONLYErrors_Efficiency.root";
auto PlaylistME_1N_MC_path_Eff = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1N_MC_StatsONLYErrors_Efficiency.root";

MAP_RootPath_Empty_MC_Eff.insert(std::make_pair(kMEPlayList_Vector.at(0), PlaylistME_1G_MC_path_Eff));
MAP_RootPath_Empty_MC_Eff.insert(std::make_pair(kMEPlayList_Vector.at(1), PlaylistME_1A_MC_path_Eff));
MAP_RootPath_Empty_MC_Eff.insert(std::make_pair(kMEPlayList_Vector.at(2), PlaylistME_1L_MC_path_Eff));
MAP_RootPath_Empty_MC_Eff.insert(std::make_pair(kMEPlayList_Vector.at(3), PlaylistME_1M_MC_path_Eff));
MAP_RootPath_Empty_MC_Eff.insert(std::make_pair(kMEPlayList_Vector.at(4), PlaylistME_1N_MC_path_Eff));

ME_playlist_TFileMAP EmptyTFile_Map_MC_Nom;
TFile *PlaylistME_1G_Nom_TFile = new TFile(PlaylistME_1G_MC_path_Eff);
TFile *PlaylistME_1A_Nom_TFile = new TFile(PlaylistME_1A_MC_path_Eff);
TFile *PlaylistME_1L_Nom_TFile = new TFile(PlaylistME_1L_MC_path_Eff);
TFile *PlaylistME_1M_Nom_TFile = new TFile(PlaylistME_1M_MC_path_Eff);
TFile *PlaylistME_1N_Nom_TFile = new TFile(PlaylistME_1N_MC_path_Eff);

EmptyTFile_Map_MC_Nom.insert(std::make_pair(kMEPlayList_Vector.at(0),PlaylistME_1G_Nom_TFile));
EmptyTFile_Map_MC_Nom.insert(std::make_pair(kMEPlayList_Vector.at(1),PlaylistME_1A_Nom_TFile));
EmptyTFile_Map_MC_Nom.insert(std::make_pair(kMEPlayList_Vector.at(2),PlaylistME_1L_Nom_TFile));
EmptyTFile_Map_MC_Nom.insert(std::make_pair(kMEPlayList_Vector.at(3),PlaylistME_1M_Nom_TFile));
EmptyTFile_Map_MC_Nom.insert(std::make_pair(kMEPlayList_Vector.at(4),PlaylistME_1N_Nom_TFile));



auto PlaylistME_1G_Data_path_2D = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_2Dminervame1G_Data_Fid.root";
auto PlaylistME_1A_Data_path_2D = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_2Dminervame1A_Data_Fid.root";
auto PlaylistME_1L_Data_path_2D = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_2Dminervame1L_Data_Fid.root";
auto PlaylistME_1M_Data_path_2D = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_2Dminervame1M_Data_Fid.root";
auto PlaylistME_1N_Data_path_2D = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_2Dminervame1N_Data_Fid.root";

//////////////////
MAP_RootPath_Empty_DATA.insert(std::make_pair(kMEPlayList_Vector.at(0), PlaylistME_1G_Data_path_2D));
MAP_RootPath_Empty_DATA.insert(std::make_pair(kMEPlayList_Vector.at(1), PlaylistME_1A_Data_path_2D));
MAP_RootPath_Empty_DATA.insert(std::make_pair(kMEPlayList_Vector.at(2), PlaylistME_1L_Data_path_2D));
MAP_RootPath_Empty_DATA.insert(std::make_pair(kMEPlayList_Vector.at(3), PlaylistME_1M_Data_path_2D));
MAP_RootPath_Empty_DATA.insert(std::make_pair(kMEPlayList_Vector.at(4), PlaylistME_1N_Data_path_2D));

TFile *PlaylistME_1G_DATA_TFile_2D = new TFile(PlaylistME_1G_Data_path_2D);
TFile *PlaylistME_1A_DATA_TFile_2D = new TFile(PlaylistME_1A_Data_path_2D);
TFile *PlaylistME_1L_DATA_TFile_2D = new TFile(PlaylistME_1L_Data_path_2D);
TFile *PlaylistME_1M_DATA_TFile_2D = new TFile(PlaylistME_1M_Data_path_2D);
TFile *PlaylistME_1N_DATA_TFile_2D = new TFile(PlaylistME_1N_Data_path_2D);
ME_playlist_TFileMAP EmptyTFile_Map_Data2D;
EmptyTFile_Map_Data2D.insert(std::make_pair(kMEPlayList_Vector.at(0),PlaylistME_1G_DATA_TFile_2D));
EmptyTFile_Map_Data2D.insert(std::make_pair(kMEPlayList_Vector.at(1),PlaylistME_1A_DATA_TFile_2D));
EmptyTFile_Map_Data2D.insert(std::make_pair(kMEPlayList_Vector.at(2),PlaylistME_1L_DATA_TFile_2D));
EmptyTFile_Map_Data2D.insert(std::make_pair(kMEPlayList_Vector.at(3),PlaylistME_1M_DATA_TFile_2D));
EmptyTFile_Map_Data2D.insert(std::make_pair(kMEPlayList_Vector.at(4),PlaylistME_1N_DATA_TFile_2D));




//Histograms_2Dminervame1L_RECO_MC_All_SysErrorsOn_noFid
//RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid
auto PlaylistME_1G_MC_path_2D = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2Dminervame1G_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";
auto PlaylistME_1A_MC_path_2D = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2Dminervame1A_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";
auto PlaylistME_1L_MC_path_2D = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2Dminervame1L_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";
auto PlaylistME_1M_MC_path_2D = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2Dminervame1M_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";
auto PlaylistME_1N_MC_path_2D = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2Dminervame1N_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";



MAP_RootPath_Empty_MC.insert(std::make_pair(kMEPlayList_Vector.at(0), PlaylistME_1G_MC_path_2D));
MAP_RootPath_Empty_MC.insert(std::make_pair(kMEPlayList_Vector.at(1), PlaylistME_1A_MC_path_2D));
MAP_RootPath_Empty_MC.insert(std::make_pair(kMEPlayList_Vector.at(2), PlaylistME_1L_MC_path_2D));
MAP_RootPath_Empty_MC.insert(std::make_pair(kMEPlayList_Vector.at(3), PlaylistME_1M_MC_path_2D));
MAP_RootPath_Empty_MC.insert(std::make_pair(kMEPlayList_Vector.at(4), PlaylistME_1N_MC_path_2D));



auto PlaylistME_1G_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2D_minervame1G_TRUTH_All_SysErrorsOn.root";
auto PlaylistME_1A_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2D_minervame1A_TRUTH_All_SysErrorsOn.root";
auto PlaylistME_1L_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2D_minervame1L_TRUTH_All_SysErrorsOn.root";
auto PlaylistME_1M_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2D_minervame1M_TRUTH_All_SysErrorsOn.root";
auto PlaylistME_1N_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2D_minervame1N_TRUTH_All_SysErrorsOn.root";

MAP_RootPath_Empty_MC_TRUTH.insert(std::make_pair(kMEPlayList_Vector.at(0), PlaylistME_1G_MC_TRUTH_path));
MAP_RootPath_Empty_MC_TRUTH.insert(std::make_pair(kMEPlayList_Vector.at(1), PlaylistME_1A_MC_TRUTH_path));
MAP_RootPath_Empty_MC_TRUTH.insert(std::make_pair(kMEPlayList_Vector.at(2), PlaylistME_1L_MC_TRUTH_path));
MAP_RootPath_Empty_MC_TRUTH.insert(std::make_pair(kMEPlayList_Vector.at(3), PlaylistME_1M_MC_TRUTH_path));
MAP_RootPath_Empty_MC_TRUTH.insert(std::make_pair(kMEPlayList_Vector.at(4), PlaylistME_1N_MC_TRUTH_path));



////////
//Full//
////////
auto PlaylistME_1P_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1P_MC_StatsONLYErrors_ThreeRegion_sideBandShift_Noshift_noWgts_NoFid_ShiftAll_Convolution.root";
auto PlaylistME_1C_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1C_MC_StatsONLYErrors_ThreeRegion_sideBandShift_Noshift_noWgts_NoFid_ShiftAll_Convolution.root";
auto PlaylistME_1D_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1D_MC_StatsONLYErrors_ThreeRegion_sideBandShift_Noshift_noWgts_NoFid_ShiftAll_Convolution.root";
auto PlaylistME_1F_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1F_MC_StatsONLYErrors_ThreeRegion_sideBandShift_Noshift_noWgts_NoFid_ShiftAll_Convolution.root";
auto PlaylistME_1E_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1E_MC_StatsONLYErrors_ThreeRegion_sideBandShift_Noshift_noWgts_NoFid_ShiftAll_Convolution.root";



auto PlaylistME_1P_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2D_minervame1P_TRUTH_All_SysErrorsOn.root";
auto PlaylistME_1C_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2D_minervame1C_TRUTH_All_SysErrorsOn.root";
auto PlaylistME_1D_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2D_minervame1D_TRUTH_All_SysErrorsOn.root";
auto PlaylistME_1F_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2D_minervame1F_TRUTH_All_SysErrorsOn.root";
auto PlaylistME_1E_MC_TRUTH_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2D_minervame1E_TRUTH_All_SysErrorsOn.root";


MAP_RootPath_Full_MC_TRUTH.insert(std::make_pair(kMEPlayList_Vector.at(5), PlaylistME_1P_MC_TRUTH_path));
MAP_RootPath_Full_MC_TRUTH.insert(std::make_pair(kMEPlayList_Vector.at(6), PlaylistME_1C_MC_TRUTH_path));
MAP_RootPath_Full_MC_TRUTH.insert(std::make_pair(kMEPlayList_Vector.at(7), PlaylistME_1D_MC_TRUTH_path));
MAP_RootPath_Full_MC_TRUTH.insert(std::make_pair(kMEPlayList_Vector.at(8), PlaylistME_1F_MC_TRUTH_path));
MAP_RootPath_Full_MC_TRUTH.insert(std::make_pair(kMEPlayList_Vector.at(9), PlaylistME_1E_MC_TRUTH_path));


auto PlaylistME_1P_MC_path_Eff = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1P_MC_StatsONLYErrors_Efficiency.root";
auto PlaylistME_1C_MC_path_Eff = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1C_MC_StatsONLYErrors_Efficiency.root";
auto PlaylistME_1D_MC_path_Eff = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1D_MC_StatsONLYErrors_Efficiency.root";
auto PlaylistME_1F_MC_path_Eff = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1F_MC_StatsONLYErrors_Efficiency.root";
auto PlaylistME_1E_MC_path_Eff = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1E_MC_StatsONLYErrors_Efficiency.root";

MAP_RootPath_Full_MC_Eff.insert(std::make_pair(kMEPlayList_Vector.at(5), PlaylistME_1P_MC_path_Eff));
MAP_RootPath_Full_MC_Eff.insert(std::make_pair(kMEPlayList_Vector.at(6), PlaylistME_1C_MC_path_Eff));
MAP_RootPath_Full_MC_Eff.insert(std::make_pair(kMEPlayList_Vector.at(7), PlaylistME_1D_MC_path_Eff));
MAP_RootPath_Full_MC_Eff.insert(std::make_pair(kMEPlayList_Vector.at(8), PlaylistME_1F_MC_path_Eff));
MAP_RootPath_Full_MC_Eff.insert(std::make_pair(kMEPlayList_Vector.at(9), PlaylistME_1E_MC_path_Eff));



auto PlaylistME_1P_MC_path_2D = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2Dminervame1P_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";
auto PlaylistME_1C_MC_path_2D = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2Dminervame1C_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";
auto PlaylistME_1D_MC_path_2D = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2Dminervame1D_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";
auto PlaylistME_1F_MC_path_2D = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2Dminervame1F_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";
auto PlaylistME_1E_MC_path_2D = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_2Dminervame1E_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";




MAP_RootPath_Full_MC.insert(std::make_pair(kMEPlayList_Vector.at(5), PlaylistME_1P_MC_path_2D));
MAP_RootPath_Full_MC.insert(std::make_pair(kMEPlayList_Vector.at(6), PlaylistME_1C_MC_path_2D));
MAP_RootPath_Full_MC.insert(std::make_pair(kMEPlayList_Vector.at(7), PlaylistME_1D_MC_path_2D));
MAP_RootPath_Full_MC.insert(std::make_pair(kMEPlayList_Vector.at(8), PlaylistME_1F_MC_path_2D));
MAP_RootPath_Full_MC.insert(std::make_pair(kMEPlayList_Vector.at(9), PlaylistME_1E_MC_path_2D));



auto PlaylistME_1P_Data_path_2D = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_2Dminervame1P_Data_Fid.root";
auto PlaylistME_1C_Data_path_2D = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_2Dminervame1C_Data_Fid.root";
auto PlaylistME_1D_Data_path_2D = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_2Dminervame1D_Data_Fid.root";
auto PlaylistME_1F_Data_path_2D = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_2Dminervame1F_Data_Fid.root";
auto PlaylistME_1E_Data_path_2D = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_2Dminervame1E_Data_Fid.root";
MAP_RootPath_Full_DATA.insert(std::make_pair(kMEPlayList_Vector.at(5), PlaylistME_1P_Data_path_2D));
MAP_RootPath_Full_DATA.insert(std::make_pair(kMEPlayList_Vector.at(6), PlaylistME_1C_Data_path_2D));
MAP_RootPath_Full_DATA.insert(std::make_pair(kMEPlayList_Vector.at(7), PlaylistME_1D_Data_path_2D));
MAP_RootPath_Full_DATA.insert(std::make_pair(kMEPlayList_Vector.at(8), PlaylistME_1F_Data_path_2D));
MAP_RootPath_Full_DATA.insert(std::make_pair(kMEPlayList_Vector.at(9), PlaylistME_1E_Data_path_2D));


////////////////////////////////////////////
//////
////////////////////////////////////////////

auto PlaylistME_1P_Data_path_1D = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1P_Data_Fid.root";
auto PlaylistME_1C_Data_path_1D = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1C_Data_Fid.root";
auto PlaylistME_1D_Data_path_1D = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1D_Data_Fid.root";
auto PlaylistME_1F_Data_path_1D = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1F_Data_Fid.root";
auto PlaylistME_1E_Data_path_1D = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1E_Data_Fid.root";


ME_playlist_TFileMAP FullTFile_Map_Data_1D;
TFile *PlaylistME_1P_DATA_TFile_1D = new TFile(PlaylistME_1P_Data_path_1D);
TFile *PlaylistME_1C_DATA_TFile_1D = new TFile(PlaylistME_1C_Data_path_1D);
TFile *PlaylistME_1D_DATA_TFile_1D = new TFile(PlaylistME_1D_Data_path_1D);
TFile *PlaylistME_1F_DATA_TFile_1D = new TFile(PlaylistME_1F_Data_path_1D);
TFile *PlaylistME_1E_DATA_TFile_1D = new TFile(PlaylistME_1E_Data_path_1D);

FullTFile_Map_Data_1D.insert(std::make_pair(kMEPlayList_Vector.at(5),PlaylistME_1P_DATA_TFile_1D));
FullTFile_Map_Data_1D.insert(std::make_pair(kMEPlayList_Vector.at(6),PlaylistME_1C_DATA_TFile_1D));
FullTFile_Map_Data_1D.insert(std::make_pair(kMEPlayList_Vector.at(7),PlaylistME_1D_DATA_TFile_1D));
FullTFile_Map_Data_1D.insert(std::make_pair(kMEPlayList_Vector.at(8),PlaylistME_1F_DATA_TFile_1D));
FullTFile_Map_Data_1D.insert(std::make_pair(kMEPlayList_Vector.at(9),PlaylistME_1E_DATA_TFile_1D));
/////////

auto PlaylistME_1G_Data_path_1D = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1G_Data_Fid.root";
auto PlaylistME_1A_Data_path_1D = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1A_Data_Fid.root";
auto PlaylistME_1L_Data_path_1D = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1L_Data_Fid.root";
auto PlaylistME_1M_Data_path_1D = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1M_Data_Fid.root";
auto PlaylistME_1N_Data_path_1D = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1N_Data_Fid.root";
ME_playlist_RootPathMAP MAP_RootPath_Empty_Data_1D;

MAP_RootPath_Empty_Data_1D.insert(std::make_pair(kMEPlayList_Vector.at(0), PlaylistME_1G_Data_path_1D));
MAP_RootPath_Empty_Data_1D.insert(std::make_pair(kMEPlayList_Vector.at(1), PlaylistME_1A_Data_path_1D));
MAP_RootPath_Empty_Data_1D.insert(std::make_pair(kMEPlayList_Vector.at(2), PlaylistME_1L_Data_path_1D));
MAP_RootPath_Empty_Data_1D.insert(std::make_pair(kMEPlayList_Vector.at(3), PlaylistME_1M_Data_path_1D));
MAP_RootPath_Empty_Data_1D.insert(std::make_pair(kMEPlayList_Vector.at(4), PlaylistME_1N_Data_path_1D));


TFile *PlaylistME_1G_DATA_TFile_1D = new TFile(PlaylistME_1G_Data_path_1D);
TFile *PlaylistME_1A_DATA_TFile_1D = new TFile(PlaylistME_1A_Data_path_1D);
TFile *PlaylistME_1L_DATA_TFile_1D = new TFile(PlaylistME_1L_Data_path_1D);
TFile *PlaylistME_1M_DATA_TFile_1D = new TFile(PlaylistME_1M_Data_path_1D);
TFile *PlaylistME_1N_DATA_TFile_1D = new TFile(PlaylistME_1N_Data_path_1D);
ME_playlist_TFileMAP EmptyTFile_Map_Data_1D;
EmptyTFile_Map_Data_1D.insert(std::make_pair(kMEPlayList_Vector.at(0),PlaylistME_1G_DATA_TFile_1D));
EmptyTFile_Map_Data_1D.insert(std::make_pair(kMEPlayList_Vector.at(1),PlaylistME_1A_DATA_TFile_1D));
EmptyTFile_Map_Data_1D.insert(std::make_pair(kMEPlayList_Vector.at(2),PlaylistME_1L_DATA_TFile_1D));
EmptyTFile_Map_Data_1D.insert(std::make_pair(kMEPlayList_Vector.at(3),PlaylistME_1M_DATA_TFile_1D));
EmptyTFile_Map_Data_1D.insert(std::make_pair(kMEPlayList_Vector.at(4),PlaylistME_1N_DATA_TFile_1D));


//////////////////////////////////////////
ME_playlist_TFileMAP EmptyTFile_Map_MC_TRUTH;
TFile *PlaylistME_1G_TRUTH_TFile = new TFile(PlaylistME_1G_MC_TRUTH_path);
TFile *PlaylistME_1A_TRUTH_TFile = new TFile(PlaylistME_1A_MC_TRUTH_path);
TFile *PlaylistME_1L_TRUTH_TFile = new TFile(PlaylistME_1L_MC_TRUTH_path);
TFile *PlaylistME_1M_TRUTH_TFile = new TFile(PlaylistME_1M_MC_TRUTH_path);
TFile *PlaylistME_1N_TRUTH_TFile = new TFile(PlaylistME_1N_MC_TRUTH_path);

EmptyTFile_Map_MC_TRUTH.insert(std::make_pair(kMEPlayList_Vector.at(0),PlaylistME_1G_TRUTH_TFile));
EmptyTFile_Map_MC_TRUTH.insert(std::make_pair(kMEPlayList_Vector.at(1),PlaylistME_1A_TRUTH_TFile));
EmptyTFile_Map_MC_TRUTH.insert(std::make_pair(kMEPlayList_Vector.at(2),PlaylistME_1L_TRUTH_TFile));
EmptyTFile_Map_MC_TRUTH.insert(std::make_pair(kMEPlayList_Vector.at(3),PlaylistME_1M_TRUTH_TFile));
EmptyTFile_Map_MC_TRUTH.insert(std::make_pair(kMEPlayList_Vector.at(4),PlaylistME_1N_TRUTH_TFile));



ME_playlist_TFileMAP EmptyTFile_Map_MC_2D;
TFile *PlaylistME_1G_2D_TFile = new TFile(PlaylistME_1G_MC_path_2D);
TFile *PlaylistME_1A_2D_TFile = new TFile(PlaylistME_1A_MC_path_2D);
TFile *PlaylistME_1L_2D_TFile = new TFile(PlaylistME_1L_MC_path_2D);
TFile *PlaylistME_1M_2D_TFile = new TFile(PlaylistME_1M_MC_path_2D);
TFile *PlaylistME_1N_2D_TFile = new TFile(PlaylistME_1N_MC_path_2D);
//
EmptyTFile_Map_MC_2D.insert(std::make_pair(kMEPlayList_Vector.at(0),PlaylistME_1G_2D_TFile));
EmptyTFile_Map_MC_2D.insert(std::make_pair(kMEPlayList_Vector.at(1),PlaylistME_1A_2D_TFile));
EmptyTFile_Map_MC_2D.insert(std::make_pair(kMEPlayList_Vector.at(2),PlaylistME_1L_2D_TFile));
EmptyTFile_Map_MC_2D.insert(std::make_pair(kMEPlayList_Vector.at(3),PlaylistME_1M_2D_TFile));
EmptyTFile_Map_MC_2D.insert(std::make_pair(kMEPlayList_Vector.at(4),PlaylistME_1N_2D_TFile));
//////////////////////////////
ME_playlist_TFileMAP FullTFile_Map_MC_TRUTH;
TFile *PlaylistME_1P_TRUTH_TFile = new TFile(PlaylistME_1P_MC_TRUTH_path);
TFile *PlaylistME_1C_TRUTH_TFile = new TFile(PlaylistME_1C_MC_TRUTH_path);
TFile *PlaylistME_1D_TRUTH_TFile = new TFile(PlaylistME_1D_MC_TRUTH_path);
TFile *PlaylistME_1F_TRUTH_TFile = new TFile(PlaylistME_1F_MC_TRUTH_path);
TFile *PlaylistME_1E_TRUTH_TFile = new TFile(PlaylistME_1E_MC_TRUTH_path);

FullTFile_Map_MC_TRUTH.insert(std::make_pair(kMEPlayList_Vector.at(5),PlaylistME_1P_TRUTH_TFile));
FullTFile_Map_MC_TRUTH.insert(std::make_pair(kMEPlayList_Vector.at(6),PlaylistME_1C_TRUTH_TFile));
FullTFile_Map_MC_TRUTH.insert(std::make_pair(kMEPlayList_Vector.at(7),PlaylistME_1D_TRUTH_TFile));
FullTFile_Map_MC_TRUTH.insert(std::make_pair(kMEPlayList_Vector.at(8),PlaylistME_1F_TRUTH_TFile));
FullTFile_Map_MC_TRUTH.insert(std::make_pair(kMEPlayList_Vector.at(9),PlaylistME_1E_TRUTH_TFile));
//
ME_playlist_TFileMAP FullTFile_Map_MC_Nom;
TFile *PlaylistME_1P_Eff_TFile = new TFile(PlaylistME_1P_MC_path_Eff);
TFile *PlaylistME_1C_Eff_TFile = new TFile(PlaylistME_1C_MC_path_Eff);
TFile *PlaylistME_1D_Eff_TFile = new TFile(PlaylistME_1D_MC_path_Eff);
TFile *PlaylistME_1F_Eff_TFile = new TFile(PlaylistME_1F_MC_path_Eff);
TFile *PlaylistME_1E_Eff_TFile = new TFile(PlaylistME_1E_MC_path_Eff);
FullTFile_Map_MC_Nom.insert(std::make_pair(kMEPlayList_Vector.at(5),PlaylistME_1P_Eff_TFile));
FullTFile_Map_MC_Nom.insert(std::make_pair(kMEPlayList_Vector.at(6),PlaylistME_1C_Eff_TFile));
FullTFile_Map_MC_Nom.insert(std::make_pair(kMEPlayList_Vector.at(7),PlaylistME_1D_Eff_TFile));
FullTFile_Map_MC_Nom.insert(std::make_pair(kMEPlayList_Vector.at(8),PlaylistME_1F_Eff_TFile));
FullTFile_Map_MC_Nom.insert(std::make_pair(kMEPlayList_Vector.at(9),PlaylistME_1E_Eff_TFile));



ME_playlist_TFileMAP FullTFile_Map_MC_2D;
TFile *PlaylistME_1P_2D_TFile = new TFile(PlaylistME_1P_MC_path_2D);
TFile *PlaylistME_1C_2D_TFile = new TFile(PlaylistME_1C_MC_path_2D);
TFile *PlaylistME_1D_2D_TFile = new TFile(PlaylistME_1D_MC_path_2D);
TFile *PlaylistME_1F_2D_TFile = new TFile(PlaylistME_1F_MC_path_2D);
TFile *PlaylistME_1E_2D_TFile = new TFile(PlaylistME_1E_MC_path_2D);
FullTFile_Map_MC_2D.insert(std::make_pair(kMEPlayList_Vector.at(5),PlaylistME_1P_2D_TFile));
FullTFile_Map_MC_2D.insert(std::make_pair(kMEPlayList_Vector.at(6),PlaylistME_1C_2D_TFile));
FullTFile_Map_MC_2D.insert(std::make_pair(kMEPlayList_Vector.at(7),PlaylistME_1D_2D_TFile));
FullTFile_Map_MC_2D.insert(std::make_pair(kMEPlayList_Vector.at(8),PlaylistME_1F_2D_TFile));
FullTFile_Map_MC_2D.insert(std::make_pair(kMEPlayList_Vector.at(9),PlaylistME_1E_2D_TFile));




/////////////////
/// Data
/////////////////
/////////////////
// Empty
/////////////////
//auto PlaylistME_1G_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1G_Data.root";
//auto PlaylistME_1A_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1A_Data.root";
//auto PlaylistME_1L_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1L_Data.root";
//auto PlaylistME_1M_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1M_Data.root";
//auto PlaylistME_1N_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1N_Data.root";


auto PlaylistME_1G_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1G_Data_SmearingStudy.root";
auto PlaylistME_1A_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1A_Data_SmearingStudy.root";
auto PlaylistME_1L_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1L_Data_SmearingStudy.root";
auto PlaylistME_1M_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1M_Data_SmearingStudy.root";
auto PlaylistME_1N_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1N_Data_SmearingStudy.root";



//////////////
//Full
//////////////
//auto PlaylistME_1P_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1P_Data.root";
//auto PlaylistME_1C_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1C_Data.root";
//auto PlaylistME_1D_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1D_Data.root";
//auto PlaylistME_1F_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1F_Data.root";
//auto PlaylistME_1E_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1E_Data.root";


auto PlaylistME_1P_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1P_Data_SmearingStudy.root";
auto PlaylistME_1C_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1C_Data_SmearingStudy.root";
auto PlaylistME_1D_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1D_Data_SmearingStudy.root";
auto PlaylistME_1F_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1F_Data_SmearingStudy.root";
auto PlaylistME_1E_Data_path = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/Histograms_minervame1E_Data_SmearingStudy.root";



////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////

Pot_MapList EmptyPOT_local_MC_MAP = Constuct_POT_playlistMap(MAP_RootPath_Empty_MC, true);
Pot_MapList FullPOT_local_MC_MAP  = Constuct_POT_playlistMap(MAP_RootPath_Full_MC, true);

Pot_MapList EmptyPOT_local_Data_MAP = Constuct_POT_playlistMap(MAP_RootPath_Empty_DATA, false);
Pot_MapList FullPOT_local_Data_MAP  = Constuct_POT_playlistMap(MAP_RootPath_Full_DATA, false);

//PlotUtils::POTCounter *PotCounter_Object; // unsure why the plotulits pot function isn't work need to revist

//Pot_MapList EmptyPOT_MC_MAP = Constuct_POT_playlistMap(PotCounter_Object, MAP_RootPath_OtherEmpty_MC);
//Pot_MapList FullPOT_MC_MAP = Constuct_POT_playlistMap(PotCounter_Object, MAP_RootPath_Full_MC);


const double Empty_MC_POT = Combine_POTFromMap( EmptyPOT_local_MC_MAP );
const double Full_MC_POT = Combine_POTFromMap( FullPOT_local_MC_MAP);

const double Empty_DATA_POT = Combine_POTFromMap(EmptyPOT_local_Data_MAP);
const double Full_DATA_POT = Combine_POTFromMap(FullPOT_local_Data_MAP );

const double Full_MC_Full_Data = Full_DATA_POT / Full_MC_POT;
const double Empty_MC_Full_Data = Full_DATA_POT / Empty_MC_POT;
const double Empty_Data_Full_Data = Full_DATA_POT / Empty_DATA_POT;


PrintPot_MapList(EmptyPOT_local_MC_MAP, "EmptyPOT_local_MC_MAP"  );
PrintPot_MapList(FullPOT_local_MC_MAP, "FullPOT_local_MC_MAP"  );

PrintPot_MapList(EmptyPOT_local_Data_MAP, "EmptyPOT_local_Data_MAP"  );
PrintPot_MapList(FullPOT_local_Data_MAP, "FullPOT_local_Data_MAP"  );








Pot_MapList EmptyPOT_local_MC_ScaledMAP = POT_ScalersMap(EmptyPOT_local_MC_MAP ,FullPOT_local_Data_MAP[kMEPlayList_Vector.at(8)] );
Pot_MapList FullPOT_local_MC_ScaledMAP = POT_ScalersMap(FullPOT_local_MC_MAP ,FullPOT_local_Data_MAP[kMEPlayList_Vector.at(8)] );

Pot_MapList EmptyPOT_local_Data_ScaledMAP = POT_ScalersMap(EmptyPOT_local_Data_MAP ,FullPOT_local_Data_MAP[kMEPlayList_Vector.at(8)] );
Pot_MapList FullPOT_local_Data_ScaledMAP = POT_ScalersMap(FullPOT_local_Data_MAP ,FullPOT_local_Data_MAP[kMEPlayList_Vector.at(8)] );


PrintPot_MapList(EmptyPOT_local_MC_ScaledMAP, "EmptyPOT_local_MC_ScaledMAP"  );
PrintPot_MapList(FullPOT_local_MC_ScaledMAP, "FullPOT_local_MC_ScaledMAP"  );

PrintPot_MapList(EmptyPOT_local_Data_ScaledMAP, "EmptyPOT_local_Data_ScaledMAP"  );
PrintPot_MapList(FullPOT_local_Data_ScaledMAP, "FullPOT_local_Data_ScaledMAP"  );





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


auto PlaylistME_1P_MC_path_1D = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1P_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";
auto PlaylistME_1C_MC_path_1D = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1C_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";
auto PlaylistME_1D_MC_path_1D = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1D_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";
auto PlaylistME_1F_MC_path_1D = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1F_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";
auto PlaylistME_1E_MC_path_1D = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1E_RECO_MC_All_SysErrorsOn_ConvolutionApp_wgtApp_Fid.root";

ME_playlist_TFileMAP FullTFile_Map_MC_1D;
TFile *PlaylistME_1P_TFile_MC_1D = new TFile(PlaylistME_1P_MC_path_1D);
TFile *PlaylistME_1C_TFile_MC_1D = new TFile(PlaylistME_1C_MC_path_1D);
TFile *PlaylistME_1D_TFile_MC_1D = new TFile(PlaylistME_1D_MC_path_1D);
TFile *PlaylistME_1F_TFile_MC_1D = new TFile(PlaylistME_1F_MC_path_1D);
TFile *PlaylistME_1E_TFile_MC_1D = new TFile(PlaylistME_1E_MC_path_1D);
FullTFile_Map_MC_1D.insert(std::make_pair(kMEPlayList_Vector.at(5),PlaylistME_1P_TFile_MC_1D));
FullTFile_Map_MC_1D.insert(std::make_pair(kMEPlayList_Vector.at(6),PlaylistME_1C_TFile_MC_1D));
FullTFile_Map_MC_1D.insert(std::make_pair(kMEPlayList_Vector.at(7),PlaylistME_1D_TFile_MC_1D));
FullTFile_Map_MC_1D.insert(std::make_pair(kMEPlayList_Vector.at(8),PlaylistME_1F_TFile_MC_1D));
FullTFile_Map_MC_1D.insert(std::make_pair(kMEPlayList_Vector.at(9),PlaylistME_1E_TFile_MC_1D));





ME_playlist_TFileMAP FullTFile_Map_Data;

ME_playlist_TFileMAP FullTFile_Map_Data2D;
TFile *PlaylistME_1P_DATA_TFile = new TFile(PlaylistME_1P_Data_path);
TFile *PlaylistME_1C_DATA_TFile = new TFile(PlaylistME_1C_Data_path);
TFile *PlaylistME_1D_DATA_TFile = new TFile(PlaylistME_1D_Data_path);
TFile *PlaylistME_1F_DATA_TFile = new TFile(PlaylistME_1F_Data_path);
TFile *PlaylistME_1E_DATA_TFile = new TFile(PlaylistME_1E_Data_path);
FullTFile_Map_Data.insert(std::make_pair(kMEPlayList_Vector.at(5),PlaylistME_1P_DATA_TFile));
FullTFile_Map_Data.insert(std::make_pair(kMEPlayList_Vector.at(6),PlaylistME_1C_DATA_TFile));
FullTFile_Map_Data.insert(std::make_pair(kMEPlayList_Vector.at(7),PlaylistME_1D_DATA_TFile));
FullTFile_Map_Data.insert(std::make_pair(kMEPlayList_Vector.at(8),PlaylistME_1F_DATA_TFile));
FullTFile_Map_Data.insert(std::make_pair(kMEPlayList_Vector.at(9),PlaylistME_1E_DATA_TFile));


TFile *PlaylistME_1P_DATA_TFile2D = new TFile(PlaylistME_1P_Data_path_2D);
TFile *PlaylistME_1C_DATA_TFile2D = new TFile(PlaylistME_1C_Data_path_2D);
TFile *PlaylistME_1D_DATA_TFile2D = new TFile(PlaylistME_1D_Data_path_2D);
TFile *PlaylistME_1F_DATA_TFile2D = new TFile(PlaylistME_1F_Data_path_2D);
TFile *PlaylistME_1E_DATA_TFile2D = new TFile(PlaylistME_1E_Data_path_2D);

FullTFile_Map_Data2D.insert(std::make_pair(kMEPlayList_Vector.at(5),PlaylistME_1P_DATA_TFile2D));
FullTFile_Map_Data2D.insert(std::make_pair(kMEPlayList_Vector.at(6),PlaylistME_1C_DATA_TFile2D));
FullTFile_Map_Data2D.insert(std::make_pair(kMEPlayList_Vector.at(7),PlaylistME_1D_DATA_TFile2D));
FullTFile_Map_Data2D.insert(std::make_pair(kMEPlayList_Vector.at(8),PlaylistME_1F_DATA_TFile2D));
FullTFile_Map_Data2D.insert(std::make_pair(kMEPlayList_Vector.at(9),PlaylistME_1E_DATA_TFile2D));



ME_playlist_TFileMAP EmptyTFile_Map_Data;

//TFile *PlaylistME_1G_DATA_TFile = new TFile(PlaylistME_1G_Data_path);
//TFile *PlaylistME_1A_DATA_TFile = new TFile(PlaylistME_1A_Data_path);
//TFile *PlaylistME_1L_DATA_TFile = new TFile(PlaylistME_1L_Data_path);
//TFile *PlaylistME_1M_DATA_TFile = new TFile(PlaylistME_1M_Data_path);
//TFile *PlaylistME_1N_DATA_TFile = new TFile(PlaylistME_1N_Data_path);
//EmptyTFile_Map_Data.insert(std::make_pair(kMEPlayList_Vector.at(0),PlaylistME_1G_DATA_TFile));
//EmptyTFile_Map_Data.insert(std::make_pair(kMEPlayList_Vector.at(1),PlaylistME_1A_DATA_TFile));
//EmptyTFile_Map_Data.insert(std::make_pair(kMEPlayList_Vector.at(2),PlaylistME_1L_DATA_TFile));
//EmptyTFile_Map_Data.insert(std::make_pair(kMEPlayList_Vector.at(3),PlaylistME_1M_DATA_TFile));
//EmptyTFile_Map_Data.insert(std::make_pair(kMEPlayList_Vector.at(4),PlaylistME_1N_DATA_TFile));



bool DoBinwidthNorm = true;
bool MakeXaxisLOG = false;
bool MakeYaxisLOG = false;
bool is_mc=true;
bool isNOT_mc=false;

std::string  pdf_CV = string(text_title_pdf4);




  // auto histname_data1 = GetVertexCryoVarHist_DATA_Name(kZ);
  // char histnameDATA_char1[histname_data1.length()+1];
  // strcpy( histnameDATA_char1 ,histname_data1.c_str());

//DrawSTACKfromHistFilio_FULLStatsCOMBINED(FullTFile_Map_MC_Nom,  FullPOT_local_MC_MAP,
//  EmptyTFile_Map_MC_Nom,  EmptyPOT_local_MC_MAP,
//  FullTFile_Map_Data, FullPOT_local_Data_MAP,
//  EmptyTFile_Map_Data, EmptyPOT_local_Data_MAP,
//  "h_CryoVertex_Z" ,histnameDATA_char1, "openAngle and Vertex Z",
//  "Vertex Z [mm]", PDF_stackMap[kMaterial], DoBinwidthNorm, "mm", kOpenAnglestack, my_debug );
//
//  auto histname_data2 = GetVertexCryoVarHist_DATA_Name(kX);
//  char histnameDATA_char2[histname_data2.length()+1];
//  strcpy( histnameDATA_char2 ,histname_data2.c_str());
//
//DrawSTACKfromHistFilio_FULLStatsCOMBINED(FullTFile_Map_MC_Nom,  FullPOT_local_MC_MAP,
//  EmptyTFile_Map_MC_Nom,  EmptyPOT_local_MC_MAP,
//  FullTFile_Map_Data, FullPOT_local_Data_MAP,
//  EmptyTFile_Map_Data, EmptyPOT_local_Data_MAP,
//  "h_CryoVertex_X" ,histnameDATA_char2, "openAngle and Vertex X",
//  "Vertex X [mm]", PDF_stackMap[kMaterial], DoBinwidthNorm, "mm", kOpenAnglestack, my_debug );
//
//  auto histname_data3 = GetVertexCryoVarHist_DATA_Name(kY);
//  char histnameDATA_char3[histname_data3.length()+1];
//  strcpy( histnameDATA_char3 ,histname_data3.c_str());
//
//
//DrawSTACKfromHistFilio_FULLStatsCOMBINED(FullTFile_Map_MC_Nom,  FullPOT_local_MC_MAP,
//  EmptyTFile_Map_MC_Nom,  EmptyPOT_local_MC_MAP,
//  FullTFile_Map_Data, FullPOT_local_Data_MAP,
//  EmptyTFile_Map_Data, EmptyPOT_local_Data_MAP,
//  "h_CryoVertex_Y" ,histnameDATA_char3, "openAngle and Vertex Y",
//  "Vertex Y [mm]", PDF_stackMap[kMaterial], DoBinwidthNorm, "mm", kOpenAnglestack, my_debug );
//
//  auto histname_data4 = GetVertexCryoVarHist_DATA_Name(kR);
//  char histnameDATA_char4[histname_data4.length()+1];
//  strcpy( histnameDATA_char4 ,histname_data4.c_str());
//
//
//DrawSTACKfromHistFilio_FULLStatsCOMBINED(FullTFile_Map_MC_Nom,  FullPOT_local_MC_MAP,
//  EmptyTFile_Map_MC_Nom,  EmptyPOT_local_MC_MAP,
//  FullTFile_Map_Data, FullPOT_local_Data_MAP,
//  EmptyTFile_Map_Data, EmptyPOT_local_Data_MAP,
//  "h_CryoVertex_R" ,histnameDATA_char4, "openAngle and Vertex R",
//  "Vertex X [mm]", PDF_stackMap[kMaterial], DoBinwidthNorm, "mm", kOpenAnglestack, my_debug );
//
//  auto histname_data5 = GetVertexCryoVarHist_DATA_Name(kdistance_edge);
//  char histnameDATA_char5[histname_data5.length()+1];
//  strcpy( histnameDATA_char5 ,histname_data5.c_str());
//
//DrawSTACKfromHistFilio_FULLStatsCOMBINED(FullTFile_Map_MC_Nom,  FullPOT_local_MC_MAP,
//  EmptyTFile_Map_MC_Nom,  EmptyPOT_local_MC_MAP,
//  FullTFile_Map_Data, FullPOT_local_Data_MAP,
//  EmptyTFile_Map_Data, EmptyPOT_local_Data_MAP,
//  "h_Distance_to_InnerTank" ,histnameDATA_char5, "openAngle and Distance to nearest edge",
//  "Distance to nearest edge [mm]", PDF_stackMap[kMaterial], DoBinwidthNorm, "mm", kOpenAnglestack, my_debug );
//
//

//DrawEffPlots( FullTFile_Map_MC_Nom,  FullTFile_Map_MC_TRUTH,
//                      EmptyTFile_Map_MC_Nom,  EmptyTFile_Map_MC_TRUTH,
//                      Full_MC_Full_Data,
//                      Empty_MC_Full_Data,
//                      "h_CryoVertex_Z_TRUE_RECO","h_CryoVertex_Z_TRUE","h_CryoVertex_Z_Material_Purity",
//                      mnv_plot, can,  StacksMaterial_title_pdf4);


//Draw2DPlots(FullTFile_Map_MC_Nom,
//  EmptyTFile_Map_MC_Nom,
//  Full_MC_Full_Data,
//  Empty_MC_Full_Data,
//  "h_2d_vertexZ_openAngle" ,"Vertex Z [mm]", "OpenAngle [Deg]", "2D vertex Vs Open Angle",
//  mnv_plot, can,  StacksMaterial_title_pdf2);
//
//Draw2DPlots(FullTFile_Map_MC_Nom,
//  EmptyTFile_Map_MC_Nom,
//  Full_MC_Full_Data,
//  Empty_MC_Full_Data,
//  "h_2d_vertexR_openAngle" ,"Vertex R [mm]", "OpenAngle [Deg]", "2D vertex Vs Open Angle",
//  mnv_plot, can,  StacksMaterial_title_pdf2);
//
//Draw2DPlots(FullTFile_Map_MC_Nom,
//  EmptyTFile_Map_MC_Nom,
//  Full_MC_Full_Data,
//  Empty_MC_Full_Data,
//  "h_2d_vertexX_openAngle" ,"Vertex X [mm]", "OpenAngle [Deg]", "2D vertex Vs Open Angle",
//  mnv_plot, can,  StacksMaterial_title_pdf2);
//
//Draw2DPlots(FullTFile_Map_MC_Nom,
//  EmptyTFile_Map_MC_Nom,
//  Full_MC_Full_Data,
//  Empty_MC_Full_Data,
//  "h_2d_vertexY_openAngle" ,"Vertex Y [mm]", "OpenAngle [Deg]", "2D vertex Vs Open Angle",
//  mnv_plot, can,  StacksMaterial_title_pdf2);
//
//

std::string inputstring("h_cryoVertex_Z_R_Particle");
//PlotUtils::HistFolio<PlotUtils::MnvH2D> StackEmpty_test(PlotUtils::LoadHistFolioFromFile<PlotUtils::MnvH2D>(*PlaylistME_1L_2D_TFile, inputstring));





std::vector<double> YMultipliers1{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
std::vector<double> XMultipliers1{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

 bool do_bin_width_norm = true; bool statPlusSysDATA = false; bool statPlusSysMC = true;
double XprotextSize =.03; double YprotextSize =.02;


Draw2DPlots_Panel(MAP_RootPath_Full_MC, MAP_RootPath_Full_DATA,
  MAP_RootPath_Empty_MC, MAP_RootPath_Empty_DATA,
  Full_MC_Full_Data,
  Empty_MC_Full_Data,
  Empty_Data_Full_Data,
  "h_Vertex_Z_R",
  "h_Data_cryoVertex_Z_R",
  "Vertex R [mm]", "Vertex Z [mm]", "[mm]", "[mm]" ,"Vertex Z vs R ",   YMultipliers1,  XMultipliers1,
  do_bin_width_norm , statPlusSysDATA ,  statPlusSysMC ,
  mnv_plot, can,  StacksMaterial_title_pdf2, XprotextSize, YprotextSize, .25);

 XprotextSize =.02;  YprotextSize =.02;
//YMultipliers.clear();
//XMultipliers.clear();
//YMultipliers{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
//XMultipliers{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

std::vector<double> YMultipliers{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
std::vector<double> XMultipliers{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};


  Draw2DPlots_Panel(MAP_RootPath_Full_MC, MAP_RootPath_Full_DATA,
    MAP_RootPath_Empty_MC, MAP_RootPath_Empty_DATA,
    Full_MC_Full_Data,
    Empty_MC_Full_Data,
    Empty_Data_Full_Data,
    "h_Vertex_Z_X",
    "h_Data_cryoVertex_Z_X",
    "Vertex X [mm]", "Vertex Z [mm]", "[mm]", "[mm]" ,"Vertex Z vs X ",   YMultipliers,  XMultipliers,
    do_bin_width_norm , statPlusSysDATA ,  statPlusSysMC ,
    mnv_plot, can,  StacksMaterial_title_pdf2, XprotextSize, YprotextSize, .5);



    std::vector<int> Helium9_colorScheme = {
      TColor::GetColor("#F1B6DA"),//pink 11
      TColor::GetColor("#0859C6"), //blue 4
      TColor::GetColor(43,206,72 ), //green 2
      TColor::GetColor("#87CEEB"),//'skyblue' 3
      TColor::GetColor("#DF00FF"), //'psychedelic Purple1
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

YprotextSize =.018;

std::vector<std::string> histMaterialstring{"Helium","Aluminium","Iron","Carbon","Lead","Other"};
std::vector<std::string> histParticlestring{"Proton","Pion_pos_neg","Neutral","Muon","Pion_0_Electron_kGamma","Other"};
std::vector<std::string> histAnglestring{"angle5","angle10","angle15","angle20","angle25","angle30","angle45","angle60"};
std::vector<std::string> histInteractionstring{"QE","2p2h","#DeltaRes","HeavierRes","SIS", "SoftDIS","HardDIS", "Other"};




Draw2DStackPlots_Panel_Full_Empty(MAP_RootPath_Full_MC, MAP_RootPath_Full_DATA,
  MAP_RootPath_Empty_MC, MAP_RootPath_Empty_DATA,
  Full_MC_Full_Data,
  Empty_MC_Full_Data,
  Empty_Data_Full_Data,
  "h_cryoVertex_Z_R",
  "Material",
  histMaterialstring,
  "h_Data_cryoVertex_Z_R",
  "Vertex R [mm]", "Vertex Z [mm]", "[mm]", "[mm]" ,"Vertex Z vs R ",   YMultipliers1,  XMultipliers1,
  do_bin_width_norm,
  mnv_plot, can,  StacksMaterial_title_pdf2, XprotextSize, YprotextSize, Helium9_colorScheme);

  Draw2DStackPlots_Panel_Full_Empty(MAP_RootPath_Full_MC, MAP_RootPath_Full_DATA,
    MAP_RootPath_Empty_MC, MAP_RootPath_Empty_DATA,
    Full_MC_Full_Data,
    Empty_MC_Full_Data,
    Empty_Data_Full_Data,
    "h_cryoVertex_Z_X",
    "Material",
    histMaterialstring,
    "h_Data_cryoVertex_Z_X",
    "Vertex X [mm]", "Vertex Z [mm]", "[mm]", "[mm]" ,"Vertex Z vs X",   YMultipliers1,  XMultipliers1,
    do_bin_width_norm,
    mnv_plot, can,  StacksMaterial_title_pdf2, XprotextSize, YprotextSize, Helium9_colorScheme);

    Draw2DStackPlots_Panel_Full_Empty(MAP_RootPath_Full_MC, MAP_RootPath_Full_DATA,
      MAP_RootPath_Empty_MC, MAP_RootPath_Empty_DATA,
      Full_MC_Full_Data,
      Empty_MC_Full_Data,
      Empty_Data_Full_Data,
      "h_cryoVertex_Z_Y",
      "Material",
      histMaterialstring,
      "h_Data_cryoVertex_Z_Y",
      "Vertex Y [mm]", "Vertex Z [mm]", "[mm]", "[mm]" ,"Vertex Z vs Y",   YMultipliers1,  XMultipliers1,
      do_bin_width_norm,
      mnv_plot, can,  StacksMaterial_title_pdf2, XprotextSize, YprotextSize, Helium9_colorScheme);

      Draw2DStackPlots_Panel_Full_Empty(MAP_RootPath_Full_MC, MAP_RootPath_Full_DATA,
        MAP_RootPath_Empty_MC, MAP_RootPath_Empty_DATA,
        Full_MC_Full_Data,
        Empty_MC_Full_Data,
        Empty_Data_Full_Data,
        "h_cryoVertex_X_Y",
        "Material",
        histMaterialstring,
        "h_Data_cryoVertex_X_Y",
        "Vertex Y [mm]", "Vertex X [mm]", "[mm]", "[mm]" ,"Vertex X vs Y",   YMultipliers1,  XMultipliers1,
        do_bin_width_norm,
        mnv_plot, can,  StacksMaterial_title_pdf2, XprotextSize, YprotextSize, Helium9_colorScheme);




//
Draw2DStackPlots_Panel_Full_Empty(MAP_RootPath_Full_MC, MAP_RootPath_Full_DATA,
  MAP_RootPath_Empty_MC, MAP_RootPath_Empty_DATA,
  Full_MC_Full_Data,
  Empty_MC_Full_Data,
  Empty_Data_Full_Data,
  "h_cryoVertex_Z_R",
  "OpenAngle",
  histAnglestring,
  "h_Data_cryoVertex_Z_R",
  "Vertex R [mm]", "Vertex Z [mm]", "[mm]", "[mm]" ,"Vertex Z vs R ",   YMultipliers1,  XMultipliers1,
  do_bin_width_norm,
  mnv_plot, can,  StacksMaterial_title_pdf2, XprotextSize, YprotextSize, Helium9_colorScheme);

Draw2DStackPlots_Panel_Full_Empty(MAP_RootPath_Full_MC, MAP_RootPath_Full_DATA,
  MAP_RootPath_Empty_MC, MAP_RootPath_Empty_DATA,
  Full_MC_Full_Data,
  Empty_MC_Full_Data,
  Empty_Data_Full_Data,
  "h_cryoVertex_Z_R",
  "Particle",
  histParticlestring,
  "h_Data_cryoVertex_Z_R",
  "Vertex R [mm]", "Vertex Z [mm]", "[mm]", "[mm]" ,"Vertex Z vs R ",   YMultipliers1,  XMultipliers1,
  do_bin_width_norm,
  mnv_plot, can,  StacksMaterial_title_pdf2, XprotextSize, YprotextSize, Helium9_colorScheme);

Draw2DStackPlots_Panel_Full_Empty(MAP_RootPath_Full_MC, MAP_RootPath_Full_DATA,
  MAP_RootPath_Empty_MC, MAP_RootPath_Empty_DATA,
  Full_MC_Full_Data,
  Empty_MC_Full_Data,
  Empty_Data_Full_Data,
  "h_cryoVertex_Z_R",
  "Interaction",
  histInteractionstring,
  "h_Data_cryoVertex_Z_R",
  "Vertex R [mm]", "Vertex Z [mm]", "[mm]", "[mm]" ,"Vertex Z vs R ",   YMultipliers1,  XMultipliers1,
  do_bin_width_norm,
  mnv_plot, can,  StacksMaterial_title_pdf2, XprotextSize, YprotextSize, Helium9_colorScheme);

//
  Draw2DStackPlots_Panel_Full_Empty(MAP_RootPath_Full_MC, MAP_RootPath_Full_DATA,
    MAP_RootPath_Empty_MC, MAP_RootPath_Empty_DATA,
    Full_MC_Full_Data,
    Empty_MC_Full_Data,
    Empty_Data_Full_Data,
    "h_Muon_PZ_PT",
    "Interaction",
    histInteractionstring,
    "h_Data_Muon_PZ_PT",
    "P_{T}","P_{Z}", "[GeV]" , "[GeV]", "P_{T} [GeV] vs P_{Z}",   YMultipliers1,  XMultipliers1,
    do_bin_width_norm,
    mnv_plot, can,  StacksMaterial_title_pdf2, XprotextSize, YprotextSize, Helium9_colorScheme);

    Draw2DStackPlots_Panel_Full_Empty(MAP_RootPath_Full_MC,  MAP_RootPath_Full_DATA,
      MAP_RootPath_Empty_MC, MAP_RootPath_Empty_DATA,
      Full_MC_Full_Data,
      Empty_MC_Full_Data,
      Empty_Data_Full_Data,
      "h_Muon_PZ_PT",
      "Particle",
      histParticlestring,
      "h_Data_Muon_PZ_PT",
      "P_{T}","P_{Z}", "[GeV]" , "[GeV]", "P_{T} [GeV] vs P_{Z}",   YMultipliers1,  XMultipliers1,
      do_bin_width_norm,
      mnv_plot, can,  StacksMaterial_title_pdf2, XprotextSize, YprotextSize, Helium9_colorScheme);

    Draw2DStackPlots_Panel_Full_Empty(MAP_RootPath_Full_MC, MAP_RootPath_Full_DATA,
      MAP_RootPath_Empty_MC, MAP_RootPath_Empty_DATA,
      Full_MC_Full_Data,
      Empty_MC_Full_Data,
      Empty_Data_Full_Data,
      "h_Muon_PZ_PT",
      "OpenAngle",
      histAnglestring,
      "h_Data_Muon_PZ_PT",
      "P_{T}","P_{Z}", "[GeV]" , "[GeV]", "P_{T} [GeV] vs P_{Z}",   YMultipliers1,  XMultipliers1,
      do_bin_width_norm,
      mnv_plot, can,  StacksMaterial_title_pdf2, XprotextSize, YprotextSize, Helium9_colorScheme);



YprotextSize =.02;

    Draw2DPlots_Panel(MAP_RootPath_Full_MC, MAP_RootPath_Full_DATA,
      MAP_RootPath_Empty_MC, MAP_RootPath_Empty_DATA,
      Full_MC_Full_Data,
      Empty_MC_Full_Data,
      Empty_Data_Full_Data,
      "h_Vertex_Z_Y",
      "h_Data_cryoVertex_Z_Y",
      "Vertex Y [mm]", "Vertex Z [mm]", "[mm]", "[mm]" ,"Vertex Z vs Y ",   YMultipliers,  XMultipliers,
      do_bin_width_norm , statPlusSysDATA ,  statPlusSysMC ,
      mnv_plot, can,  StacksMaterial_title_pdf2, XprotextSize, YprotextSize, .5);

      Draw2DPlots_Panel(MAP_RootPath_Full_MC, MAP_RootPath_Full_DATA,
        MAP_RootPath_Empty_MC, MAP_RootPath_Empty_DATA,
        Full_MC_Full_Data,
        Empty_MC_Full_Data,
        Empty_Data_Full_Data,
        "h_Vertex_X_Y",
        "h_Data_cryoVertex_X_Y",
        "Vertex Y [mm]", "Vertex X [mm]", "[mm]", "[mm]" ,"Vertex X vs Y ",   YMultipliers,  XMultipliers,
        do_bin_width_norm , statPlusSysDATA ,  statPlusSysMC ,
        mnv_plot, can,  StacksMaterial_title_pdf2, XprotextSize, YprotextSize, .5);


    std::vector<double> YMultipliers3{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    std::vector<double> XMultipliers3{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};


Draw2DPlots_Panel(MAP_RootPath_Full_MC, MAP_RootPath_Full_DATA,
  MAP_RootPath_Empty_MC, MAP_RootPath_Empty_DATA,
  Full_MC_Full_Data,
  Empty_MC_Full_Data,
  Empty_Data_Full_Data,
  "h_Vertex_Z_openAngle",
  "h_Data_cryoVertex_Z_OpenAngle",
   "#theta_{open}","Z [mm]", "[mm]" , "[Deg]", "Vertex Z vs #theta_{open} ",   YMultipliers3,  XMultipliers3,
  do_bin_width_norm , statPlusSysDATA ,  statPlusSysMC ,
  mnv_plot, can,  StacksMaterial_title_pdf2, XprotextSize, YprotextSize ,.4);

Draw2DPlots_Panel(MAP_RootPath_Full_MC, MAP_RootPath_Full_DATA,
  MAP_RootPath_Empty_MC, MAP_RootPath_Empty_DATA,
  Full_MC_Full_Data,
  Empty_MC_Full_Data,
  Empty_Data_Full_Data,
  "h_Vertex_R_openAngle",
  "h_Data_cryoVertex_R_OpenAngle",
  "#theta_{open}","R [mm]", "[mm]" , "[Deg]", "Vertex R vs #theta_{open} ",   YMultipliers3,  XMultipliers3,
  do_bin_width_norm , statPlusSysDATA ,  statPlusSysMC ,
  mnv_plot, can,  StacksMaterial_title_pdf2, XprotextSize, YprotextSize, .4);

Draw2DPlots_Panel(MAP_RootPath_Full_MC, MAP_RootPath_Full_DATA,
  MAP_RootPath_Empty_MC, MAP_RootPath_Empty_DATA,
  Full_MC_Full_Data,
  Empty_MC_Full_Data,
  Empty_Data_Full_Data,
  "h_Vertex_Y_openAngle",
  "h_Data_cryoVertex_Y_OpenAngle",
 "#theta_{open}",  "Y [mm]","[mm]" , "[Deg]", "Vertex Y vs #theta_{open} ",   YMultipliers3,  XMultipliers3,
  do_bin_width_norm , statPlusSysDATA ,  statPlusSysMC ,
  mnv_plot, can,  StacksMaterial_title_pdf2, XprotextSize, YprotextSize, .4);

Draw2DPlots_Panel(MAP_RootPath_Full_MC, MAP_RootPath_Full_DATA,
  MAP_RootPath_Empty_MC, MAP_RootPath_Empty_DATA,
  Full_MC_Full_Data,
  Empty_MC_Full_Data,
  Empty_Data_Full_Data,
  "h_Vertex_X_openAngle",
  "h_Data_cryoVertex_X_OpenAngle",
  "#theta_{open}", "X [mm]", "[mm]" , "[Deg]", "Vertex X vs #theta_{open} ",   YMultipliers3,  XMultipliers3,
  do_bin_width_norm , statPlusSysDATA ,  statPlusSysMC ,
  mnv_plot, can,  StacksMaterial_title_pdf2, XprotextSize, YprotextSize, .5);

Draw2DPlots_Panel(MAP_RootPath_Full_MC, MAP_RootPath_Full_DATA,
  MAP_RootPath_Empty_MC, MAP_RootPath_Empty_DATA,
  Full_MC_Full_Data,
  Empty_MC_Full_Data,
  Empty_Data_Full_Data,
  "h_Vertex_Z_ChiSq",
  "h_Data_Vertex_Z_ChiSq",
  "#chi^{2}", "Z [mm]", " " , "#chi^{2}", "Vertex Z vs #chi^{2}",   YMultipliers3,  XMultipliers3,
  do_bin_width_norm , statPlusSysDATA ,  statPlusSysMC ,
  mnv_plot, can,  StacksMaterial_title_pdf2, XprotextSize, YprotextSize, .3);

Draw2DPlots_Panel(MAP_RootPath_Full_MC, MAP_RootPath_Full_DATA,
  MAP_RootPath_Empty_MC, MAP_RootPath_Empty_DATA,
  Full_MC_Full_Data,
  Empty_MC_Full_Data,
  Empty_Data_Full_Data,
  "h_Vertex_Z_MuonTheta",
  "h_Data_Vertex_Z_MuonTheta",
  "#theta_{#mu}", "Z [mm]", "Deg" , "#theta_{#mu}", "Vertex Z vs #theta_{#mu}",   YMultipliers3,  XMultipliers3,
  do_bin_width_norm , statPlusSysDATA ,  statPlusSysMC ,
  mnv_plot, can,  StacksMaterial_title_pdf2, XprotextSize, YprotextSize, .25);


Draw2DPlots_Panel(MAP_RootPath_Full_MC, MAP_RootPath_Full_DATA,
  MAP_RootPath_Empty_MC, MAP_RootPath_Empty_DATA,
  Full_MC_Full_Data,
  Empty_MC_Full_Data,
  Empty_Data_Full_Data,
  "h_Vertex_Z_DistanceNearEdge",
  "h_Data_Vertex_Z_DistanceNearEdge",
  "Nearest edge","Z [mm]", "[mm]" , "[mm]", "Vertex Z vs Nearest edge [mm]",   YMultipliers3,  XMultipliers3,
  do_bin_width_norm , statPlusSysDATA ,  statPlusSysMC ,
  mnv_plot, can,  StacksMaterial_title_pdf2, XprotextSize, YprotextSize, .3);

Draw2DPlots_Panel(MAP_RootPath_Full_MC, MAP_RootPath_Full_DATA,
  MAP_RootPath_Empty_MC, MAP_RootPath_Empty_DATA,
  Full_MC_Full_Data,
  Empty_MC_Full_Data,
  Empty_Data_Full_Data,
  "h_Vertex_R_DistanceNearEdge",
  "h_Data_Vertex_R_DistanceNearEdge",
  "Nearest edge","R [mm]", "[mm]" , "[mm]", "Vertex R vs Nearest edge [mm]",   YMultipliers3,  XMultipliers3,
  do_bin_width_norm , statPlusSysDATA ,  statPlusSysMC ,
  mnv_plot, can,  StacksMaterial_title_pdf2, XprotextSize, YprotextSize, .25);

Draw2DPlots_Panel(MAP_RootPath_Full_MC, MAP_RootPath_Full_DATA,
  MAP_RootPath_Empty_MC, MAP_RootPath_Empty_DATA,
  Full_MC_Full_Data,
  Empty_MC_Full_Data,
  Empty_Data_Full_Data,
  "h_Vertex_X_DistanceNearEdge",
  "h_Data_Vertex_X_DistanceNearEdge",
  "Nearest edge","X [mm]", "[mm]" , "[mm]", "Vertex X vs Nearest edge [mm]",   YMultipliers3,  XMultipliers3,
  do_bin_width_norm , statPlusSysDATA ,  statPlusSysMC ,
  mnv_plot, can,  StacksMaterial_title_pdf2, XprotextSize, YprotextSize, .5);

Draw2DPlots_Panel(MAP_RootPath_Full_MC, MAP_RootPath_Full_DATA,
  MAP_RootPath_Empty_MC, MAP_RootPath_Empty_DATA,
  Full_MC_Full_Data,
  Empty_MC_Full_Data,
  Empty_Data_Full_Data,
  "h_Vertex_Y_DistanceNearEdge",
  "h_Data_Vertex_Y_DistanceNearEdge",
  "Nearest edge [mm]","vertex Y [mm]", "[mm]" , "[mm]", "Vertex Y vs Nearest edge [mm]",   YMultipliers3,  XMultipliers3,
  do_bin_width_norm , statPlusSysDATA ,  statPlusSysMC ,
  mnv_plot, can,  StacksMaterial_title_pdf2, XprotextSize, YprotextSize, .5);


Draw2DPlots_Panel(MAP_RootPath_Full_MC, MAP_RootPath_Full_DATA,
  MAP_RootPath_Empty_MC, MAP_RootPath_Empty_DATA,
  Full_MC_Full_Data,
  Empty_MC_Full_Data,
  Empty_Data_Full_Data,
  "h_Muon_PZ_CuratureSig",
  "h_Data_Muon_PZ_CuratureSig",
  "(q/p)/#sigma(q/p)","P_{Z}", "[GeV]" , "[mm]", "Muon P_{Z} vs Curature sig [mm]",   YMultipliers3,  XMultipliers3,
  do_bin_width_norm , statPlusSysDATA ,  statPlusSysMC ,
  mnv_plot, can,  StacksMaterial_title_pdf2, XprotextSize, YprotextSize, .5);

Draw2DPlots_Panel(MAP_RootPath_Full_MC, MAP_RootPath_Full_DATA,
  MAP_RootPath_Empty_MC, MAP_RootPath_Empty_DATA,
  Full_MC_Full_Data,
  Empty_MC_Full_Data,
  Empty_Data_Full_Data,
  "h_Muon_PT_CuratureSig",
  "h_Data_Muon_PT_CuratureSig",
  "(q/p)/#sigma(q/p)","P_{T}", "[GeV]" , "[mm]", "Muon P_{T} vs Curature sig [mm]",   YMultipliers3,  XMultipliers3,
  do_bin_width_norm , statPlusSysDATA ,  statPlusSysMC ,
  mnv_plot, can,  StacksMaterial_title_pdf2, XprotextSize, YprotextSize, .5);

Draw2DPlots_Panel(MAP_RootPath_Full_MC, MAP_RootPath_Full_DATA,
  MAP_RootPath_Empty_MC, MAP_RootPath_Empty_DATA,
  Full_MC_Full_Data,
  Empty_MC_Full_Data,
  Empty_Data_Full_Data,
  "h_secTrkE_secTrkTheta",
  "h_Data_secTrkE_secTrkTheta",
  "#theta_{2ndTrk}","2ndTrk KE", "[Deg]" , "[GeV]", "2ndTrk KE vs #theta_{2ndTrk} [Deg]",   YMultipliers3,  XMultipliers3,
  do_bin_width_norm , statPlusSysDATA ,  statPlusSysMC ,
  mnv_plot, can,  StacksMaterial_title_pdf2, XprotextSize, YprotextSize, .1);

Draw2DPlots_Panel(MAP_RootPath_Full_MC, MAP_RootPath_Full_DATA,
  MAP_RootPath_Empty_MC, MAP_RootPath_Empty_DATA,
  Full_MC_Full_Data,
  Empty_MC_Full_Data,
  Empty_Data_Full_Data,
  "h_Vertex_Z_secTrkTheta",
  "h_Data_Vertex_Z_secTrkTheta",
  "#theta_{2ndTrk}","Vertex Z [mm]", "[Deg]" , "[mm]", "Vertex Z[mm] vs #theta_{2ndTrk} [Deg]",   YMultipliers3,  XMultipliers3,
  do_bin_width_norm , statPlusSysDATA ,  statPlusSysMC ,
  mnv_plot, can,  StacksMaterial_title_pdf2, XprotextSize, YprotextSize, .3);

Draw2DPlots_Panel(MAP_RootPath_Full_MC, MAP_RootPath_Full_DATA,
  MAP_RootPath_Empty_MC, MAP_RootPath_Empty_DATA,
  Full_MC_Full_Data,
  Empty_MC_Full_Data,
  Empty_Data_Full_Data,
  "h_Vertex_Z_secTrkE",
  "h_Data_Vertex_Z_secTrkE",
  "Vertex Z[mm]","E_{2ndTrk}", "[GeV]" , "[GeV]", "Vertex Z[mm] vs E_{2ndTrk} [GeV]",   YMultipliers3,  XMultipliers3,
  do_bin_width_norm , statPlusSysDATA ,  statPlusSysMC ,
  mnv_plot, can,  StacksMaterial_title_pdf2, XprotextSize, YprotextSize, .3);

  Draw2DPlots_Panel(MAP_RootPath_Full_MC, MAP_RootPath_Full_DATA,
    MAP_RootPath_Empty_MC, MAP_RootPath_Empty_DATA,
    Full_MC_Full_Data,
    Empty_MC_Full_Data,
    Empty_Data_Full_Data,
    "h_Vertex_Z_trkLength",
    "h_Data_Vertex_Z_trkLength",
    "Length_{2ndtrk}","Vertex Z[mm]", "[mm]" , "[GeV]", "Vertex Z[mm] vs Length_{2ndtrk} [mm]",   YMultipliers3,  XMultipliers3,
    do_bin_width_norm , statPlusSysDATA ,  statPlusSysMC ,
    mnv_plot, can,  StacksMaterial_title_pdf2, XprotextSize, YprotextSize, .25);


Draw2DPlots_Panel(MAP_RootPath_Full_MC, MAP_RootPath_Full_DATA,
  MAP_RootPath_Empty_MC, MAP_RootPath_Empty_DATA,
  Full_MC_Full_Data,
  Empty_MC_Full_Data,
  Empty_Data_Full_Data,
  "h_secTrkTheta_TrkLength",
  "h_Data_secTrkTheta_TrkLength",
  "Length_{2ndtrk}","#theta_{2ndTrk}", "[mm]" , "[GeV]", "#theta_{2ndTrk} [Deg] vs 2ndTrk Length [mm]",   YMultipliers3,  XMultipliers3,
  do_bin_width_norm , statPlusSysDATA ,  statPlusSysMC ,
  mnv_plot, can,  StacksMaterial_title_pdf2, XprotextSize, YprotextSize, .25);

Draw2DPlots_Panel(MAP_RootPath_Full_MC, MAP_RootPath_Full_DATA,
  MAP_RootPath_Empty_MC, MAP_RootPath_Empty_DATA,
  Full_MC_Full_Data,
  Empty_MC_Full_Data,
  Empty_Data_Full_Data,
  "h_MuonDoca_secTrkDoca",
  "h_Data_MuonDoca_secTrkDoca",
  "DOCA_{#mu}","DOCA_{2ndTrk}", "[mm]" , "[mm]", "DOCA_{#mu} [mm] vs DOCA_{2ndTrk} [mm]",   YMultipliers3,  XMultipliers3,
  do_bin_width_norm , statPlusSysDATA ,  statPlusSysMC ,
  mnv_plot, can,  StacksMaterial_title_pdf2, XprotextSize, YprotextSize, .25);


Draw2DPlots_Panel(MAP_RootPath_Full_MC, MAP_RootPath_Full_DATA,
  MAP_RootPath_Empty_MC, MAP_RootPath_Empty_DATA,
  Full_MC_Full_Data,
  Empty_MC_Full_Data,
  Empty_Data_Full_Data,
  "h_secTrkE_TrkLength",
  "h_Data_secTrkE_TrkLength",
  "Length_{2ndTrk}","E_{2ndTrk}", "[cm]" , "[GeV]", "E_{2ndTrk} [GeV] vs Length_{2ndTrk} [cm]",   YMultipliers3,  XMultipliers3,
  do_bin_width_norm , statPlusSysDATA ,  statPlusSysMC ,
  mnv_plot, can,  StacksMaterial_title_pdf2, XprotextSize, YprotextSize, .25);

Draw2DPlots_Panel(MAP_RootPath_Full_MC, MAP_RootPath_Full_DATA,
  MAP_RootPath_Empty_MC, MAP_RootPath_Empty_DATA,
  Full_MC_Full_Data,
  Empty_MC_Full_Data,
  Empty_Data_Full_Data,
  "h_secTrkTheta_secTrkDoca",
  "h_Data_secTrkTheta_secTrkDoca",
  "Doca_{2ndTrk}","#theta_{2ndTrk}", "[mm]" , "[Deg]", "#theta_{2ndTrk} [mm] vs Doca_{2ndTrk} [mm]",   YMultipliers3,  XMultipliers3,
  do_bin_width_norm , statPlusSysDATA ,  statPlusSysMC ,
  mnv_plot, can,  StacksMaterial_title_pdf2, XprotextSize, YprotextSize, .15);

Draw2DPlots_Panel(MAP_RootPath_Full_MC, MAP_RootPath_Full_DATA,
  MAP_RootPath_Empty_MC, MAP_RootPath_Empty_DATA,
  Full_MC_Full_Data,
  Empty_MC_Full_Data,
  Empty_Data_Full_Data,
  "h_secTrkE_secTrkDoca",
  "h_Data_secTrkE_secTrkDoca",
  "Doca_{2ndTrk}","E_{2ndTrk}", "[mm]" , "[GeV]", "E_{2ndTrk} [GeV] vs Doca_{2ndTrk} [mm]",   YMultipliers3,  XMultipliers3,
  do_bin_width_norm , statPlusSysDATA ,  statPlusSysMC ,
  mnv_plot, can,  StacksMaterial_title_pdf2, XprotextSize, YprotextSize, .25);

Draw2DPlots_Panel(MAP_RootPath_Full_MC, MAP_RootPath_Full_DATA,
  MAP_RootPath_Empty_MC, MAP_RootPath_Empty_DATA,
  Full_MC_Full_Data,
  Empty_MC_Full_Data,
  Empty_Data_Full_Data,
  "h_Muon_PT_NTracks",
  "h_Data_Muon_PT_NTracks",
  "Ntracks","P_{T}", "[N]" , "[GeV]", "P_{T} [GeV] vs Ntracks",   YMultipliers3,  XMultipliers3,
  do_bin_width_norm , statPlusSysDATA ,  statPlusSysMC ,
  mnv_plot, can,  StacksMaterial_title_pdf2, XprotextSize, YprotextSize, .25);



Draw2DPlots_Panel(MAP_RootPath_Full_MC, MAP_RootPath_Full_DATA,
  MAP_RootPath_Empty_MC, MAP_RootPath_Empty_DATA,
  Full_MC_Full_Data,
  Empty_MC_Full_Data,
  Empty_Data_Full_Data,
  "h_Muon_theta_CuratureSig",
  "h_Data_Muon_theta_CuratureSig",
  "(q/p)/#sigma(q/p)","#theta_{#mu}", "(q/p)/#sigma(q/p)" , "[Deg]", "#theta_{#mu} [Deg] vs Curature sig",   YMultipliers3,  XMultipliers3,
  do_bin_width_norm , statPlusSysDATA ,  statPlusSysMC ,
  mnv_plot, can,  StacksMaterial_title_pdf2, XprotextSize, YprotextSize, .25);


Draw2DPlots_Panel(MAP_RootPath_Full_MC, MAP_RootPath_Full_DATA,
  MAP_RootPath_Empty_MC, MAP_RootPath_Empty_DATA,
  Full_MC_Full_Data,
  Empty_MC_Full_Data,
  Empty_Data_Full_Data,
  "h_Muon_PZ_PT",
  "h_Data_Muon_PZ_PT",
  "P_{T}","P_{Z}", "[GeV]" , "[GeV]", "P_{T} [GeV] vs P_{Z}",   YMultipliers3,  XMultipliers3,
  do_bin_width_norm , statPlusSysDATA ,  statPlusSysMC ,
  mnv_plot, can,  StacksMaterial_title_pdf2, XprotextSize, YprotextSize, .25);


Draw2DPlots_Panel(MAP_RootPath_Full_MC, MAP_RootPath_Full_DATA,
  MAP_RootPath_Empty_MC, MAP_RootPath_Empty_DATA,
  Full_MC_Full_Data,
  Empty_MC_Full_Data,
  Empty_Data_Full_Data,
  "h_Muon_E_theta",
  "h_Data_Muon_E_theta",
  "#theta_{#mu}","E_{#mu}", "[GeV]" , "[Deg]", "E_{#mu} [GeV] vs #theta_{#mu} (wrtb) [GeV]",   YMultipliers3,  XMultipliers3,
  do_bin_width_norm , statPlusSysDATA ,  statPlusSysMC ,
  mnv_plot, can,  StacksMaterial_title_pdf2, XprotextSize, YprotextSize, .25);


std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;
std::cout<<"Starting Efficiency Plots "<< std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;


/*

Draw2D_EfficiencyPlots_Panel(MAP_RootPath_Full_MC, MAP_RootPath_Full_MC_TRUTH,
  MAP_RootPath_Empty_MC, MAP_RootPath_Empty_MC_TRUTH,
  Full_MC_Full_Data,
  Empty_MC_Full_Data,
  "h_cryoVertex_Z_R_TRUE_RECO",
  "h_cryoVertex_Z_R_TRUE",
  "True Vertex Z", "True Vertex R","[mm]","[mm]", "Efficiency Vertex Z vs Vertex R",   YMultipliers3,  XMultipliers3,
  do_bin_width_norm , statPlusSysDATA ,  statPlusSysMC ,
  mnv_plot, can,  StacksMaterial_title_pdf2, XprotextSize, YprotextSize, .12);

Draw2D_EfficiencyPlots_Panel(MAP_RootPath_Full_MC, MAP_RootPath_Full_MC_TRUTH,
  MAP_RootPath_Empty_MC, MAP_RootPath_Empty_MC_TRUTH,
  Full_MC_Full_Data,
  Empty_MC_Full_Data,
  "h_cryoVertex_Z_X_TRUE_RECO",
  "h_cryoVertex_Z_X_TRUE",
  "True Vertex Z", "True Vertex X","[mm]","[mm]", "Efficiency Vertex Z vs Vertex X",   YMultipliers3,  XMultipliers3,
  do_bin_width_norm , statPlusSysDATA ,  statPlusSysMC ,
  mnv_plot, can,  StacksMaterial_title_pdf2, XprotextSize, YprotextSize, .12);

Draw2D_EfficiencyPlots_Panel(MAP_RootPath_Full_MC, MAP_RootPath_Full_MC_TRUTH,
  MAP_RootPath_Empty_MC, MAP_RootPath_Empty_MC_TRUTH,
  Full_MC_Full_Data,
  Empty_MC_Full_Data,
  "h_cryoVertex_Z_Y_TRUE_RECO",
  "h_cryoVertex_Z_Y_TRUE",
  "True Vertex Z", "True Vertex Y","[mm]","[mm]", "Efficiency Vertex Z vs Vertex Y",   YMultipliers3,  XMultipliers3,
  do_bin_width_norm , statPlusSysDATA ,  statPlusSysMC ,
  mnv_plot, can,  StacksMaterial_title_pdf2, XprotextSize, YprotextSize, .12);

Draw2D_EfficiencyPlots_Panel(MAP_RootPath_Full_MC, MAP_RootPath_Full_MC_TRUTH,
  MAP_RootPath_Empty_MC, MAP_RootPath_Empty_MC_TRUTH,
  Full_MC_Full_Data,
  Empty_MC_Full_Data,
  "h_cryoVertex_Z_theta_TRUE_RECO",
  "h_cryoVertex_Z_theta_TRUE",
  "True Vertex Z", "True #theta_{#mu}", "[mm]", "[Deg]", "Efficiency #theta_{#mu} vs Vertex Z",   YMultipliers3,  XMultipliers3,
  do_bin_width_norm , statPlusSysDATA ,  statPlusSysMC ,
  mnv_plot, can,  StacksMaterial_title_pdf2, XprotextSize, YprotextSize, .4);

Draw2D_EfficiencyPlots_Panel(MAP_RootPath_Full_MC, MAP_RootPath_Full_MC_TRUTH,
  MAP_RootPath_Empty_MC, MAP_RootPath_Empty_MC_TRUTH,
  Full_MC_Full_Data,
  Empty_MC_Full_Data,
  "h_cryoVertex_Z_OpenAngle_TRUE_RECO",
  "h_cryoVertex_Z_openAngle_TRUE",
  "True Vertex Z","True #theta_{OpeningAngle}","[mm]", "[Deg]", "Efficiency #theta_{OpeningAngle} vs Vertex Z",   YMultipliers3,  XMultipliers3,
  do_bin_width_norm , statPlusSysDATA ,  statPlusSysMC ,
  mnv_plot, can,  StacksMaterial_title_pdf2, XprotextSize, YprotextSize, .4);

//
Draw2D_EfficiencyPlots_Panel(MAP_RootPath_Full_MC, MAP_RootPath_Full_MC_TRUTH,
  MAP_RootPath_Empty_MC, MAP_RootPath_Empty_MC_TRUTH,
  Full_MC_Full_Data,
  Empty_MC_Full_Data,
  "h_cryoVertex_R_theta_TRUE_RECO",
  "h_cryoVertex_R_theta_TRUE",
  "True #theta_{#mu}", "True Vertex R","[mm]","[Deg]", "Efficiency #theta_{#mu} vs Vertex Z",   YMultipliers3,  XMultipliers3,
  do_bin_width_norm , statPlusSysDATA ,  statPlusSysMC ,
  mnv_plot, can,  StacksMaterial_title_pdf2, XprotextSize, YprotextSize, .4);


//Draw2D_EfficiencyPlots_Panel(MAP_RootPath_Full_MC, MAP_RootPath_Full_MC_TRUTH,
//  MAP_RootPath_Empty_MC, MAP_RootPath_Empty_MC_TRUTH,
//  Full_MC_Full_Data,
//  Empty_MC_Full_Data,
//  "h_2ndtrkangle_2ndTrkE_TRUE_RECO",
//  "h_2ndtrkangle_2ndTrkE_TRUE",
//  "True T_{2ndTrk}", "True #theta_{2ndTrk}","[Gev]","[Deg]", "Efficiency T_{2ndTrk} vs #theta_{2ndTrk}",   YMultipliers3,  XMultipliers3,
//  do_bin_width_norm , statPlusSysDATA ,  statPlusSysMC ,
//  mnv_plot, can,  StacksMaterial_title_pdf2, XprotextSize, YprotextSize, .4);


Draw2D_EfficiencyPlots_Panel(MAP_RootPath_Full_MC, MAP_RootPath_Full_MC_TRUTH,
  MAP_RootPath_Empty_MC, MAP_RootPath_Empty_MC_TRUTH,
  Full_MC_Full_Data,
  Empty_MC_Full_Data,
  "h_theta_openAngle_TRUE_RECO",
  "h_theta_openAngle_TRUE",
  "True #theta_{#mu}", "True #theta_{OpeningAngle}","[Deg]","[Deg]", "Efficiency #theta_{OpeningAngle} vs #theta_{2ndTrk}",   YMultipliers3,  XMultipliers3,
  do_bin_width_norm , statPlusSysDATA ,  statPlusSysMC ,
  mnv_plot, can,  StacksMaterial_title_pdf2, XprotextSize, YprotextSize, .4);
*/




    DrawCombined_Resolution_withGaussianFit(MAP_RootPath_Full_MC_Eff, MAP_RootPath_Empty_MC_Eff,Full_MC_Full_Data,
    Empty_MC_Full_Data, "h_Distance_to_InnerTank_Resolution", "Resolution",  "Distance to Nearest Edge Resolution (Reco-True)", " NEvents / [mm]",
    true, false , false, true,
    mnv_plot, can,  pdf_MaterialStacks);

    DrawCombined_Resolution_withGaussianFit(MAP_RootPath_Full_MC_Eff, MAP_RootPath_Empty_MC_Eff,Full_MC_Full_Data,
    Empty_MC_Full_Data, "h_CryoVertex_Percent_resolutionX_RECO", "Resolution",  "Vertex X Resolution (Reco-True)", " NEvents / [mm]",
    true, false , false, true,
    mnv_plot, can,  pdf_MaterialStacks);

    DrawCombined_Resolution_withGaussianFit(MAP_RootPath_Full_MC_Eff, MAP_RootPath_Empty_MC_Eff,Full_MC_Full_Data,
    Empty_MC_Full_Data, "h_CryoVertex_Percent_resolutionY_RECO", "Resolution",  "Vertex Y Resolution (Reco-True)", " NEvents / [mm]",
    true, false , false, true,
    mnv_plot, can,  pdf_MaterialStacks);

    DrawCombined_Resolution_withGaussianFit(MAP_RootPath_Full_MC_Eff, MAP_RootPath_Empty_MC_Eff,Full_MC_Full_Data,
    Empty_MC_Full_Data, "h_CryoVertex_Percent_resolutionZ_RECO", "Resolution",  "Vertex Z Resolution (Reco-True)", " NEvents / [mm]",
    true, false , false, true,
    mnv_plot, can,  pdf_MaterialStacks);

    DrawCombined_Resolution_withGaussianFit(MAP_RootPath_Full_MC_Eff, MAP_RootPath_Empty_MC_Eff,Full_MC_Full_Data,
    Empty_MC_Full_Data, "h_CryoVertex_Percent_resolutionR_RECO", "Resolution",  "Vertex R Resolution (Reco-True)", " NEvents / [mm]",
    true, false , false, true,
    mnv_plot, can,  pdf_MaterialStacks);

    int logScale = 0;

    bool doBinwidth =true;
     bool isFractional = false;
     bool isAreaNormalized = true;

     Draw_3Resolution_CryoVertex_FULL_EMPTY_RecoBranch(MAP_RootPath_Full_MC_Eff,
                                  MAP_RootPath_Empty_MC_Eff,
                                  Full_MC_Full_Data,
                                  Empty_MC_Full_Data,
                                  "h_CryoVertex_Y_upstreamCap_resolution_RECO",
                                  "h_CryoVertex_Y_barrel_resolution_RECO",
                                  "h_CryoVertex_Y_downstreamCap_resolution_RECO",
                                  logScale,   mnv_plot, can, StacksMaterial_title_pdf4, "No Fiduical ",
                                  doBinwidth, isFractional , isAreaNormalized, 8, kY  );

   Draw_3Resolution_CryoVertex_FULL_EMPTY_RecoBranch(MAP_RootPath_Full_MC_Eff,
                                 MAP_RootPath_Empty_MC_Eff,
                                 Full_MC_Full_Data,
                                 Empty_MC_Full_Data,
                                 "h_CryoVertex_X_upstreamCap_resolution_RECO",
                                 "h_CryoVertex_X_barrel_resolution_RECO",
                                 "h_CryoVertex_X_downstreamCap_resolution_RECO",
                                 logScale,   mnv_plot, can, StacksMaterial_title_pdf4, "No Fiduical",
                                 doBinwidth, isFractional , isAreaNormalized, 8, kX  );


  Draw_3Resolution_CryoVertex_FULL_EMPTY_RecoBranch(MAP_RootPath_Full_MC_Eff,
                                                    MAP_RootPath_Empty_MC_Eff,
                                                    Full_MC_Full_Data,
                                                    Empty_MC_Full_Data,
                                                    "h_CryoVertex_R_upstreamCap_resolution_RECO",
                                                    "h_CryoVertex_R_barrel_resolution_RECO",
                                                    "h_CryoVertex_R_downstreamCap_resolution_RECO",
                                                    logScale,   mnv_plot, can, StacksMaterial_title_pdf4, "No Fiduical",
                                                    doBinwidth, isFractional , isAreaNormalized, 8, kR  );

  Draw_3Resolution_CryoVertex_FULL_EMPTY_RecoBranch(MAP_RootPath_Full_MC_Eff,
                                     MAP_RootPath_Empty_MC_Eff,
                                     Full_MC_Full_Data,
                                     Empty_MC_Full_Data,
                                     "h_CryoVertex_Z_upstreamCap_resolution_RECO",
                                     "h_CryoVertex_Z_barrel_resolution_RECO",
                                     "h_CryoVertex_Z_downstreamCap_resolution_RECO",
                                     logScale,   mnv_plot, can, StacksMaterial_title_pdf4, "Fiduical",
                                     doBinwidth, isFractional , isAreaNormalized, 4, kZ  );

 Draw_3Resolution_CryoVertex_FULL_EMPTY_RecoBranch(MAP_RootPath_Full_MC_Eff,
                                MAP_RootPath_Empty_MC_Eff,
                                Full_MC_Full_Data,
                                Empty_MC_Full_Data,
                                "h_Distance_to_InnerTank_upstreamCap_Resolution",
                                "h_Distance_to_InnerTank_barrel_Resolution",
                                "h_Distance_to_InnerTank_downstreamCap_Resolution",
                                logScale,   mnv_plot, can, StacksMaterial_title_pdf4, "No Fiduical",
                                doBinwidth, isFractional , isAreaNormalized, 8, kdistance_edge  );



DrawFULLStat_CV_SystematicErr( FullTFile_Map_MC_Nom,    FullPOT_local_MC_ScaledMAP,
  EmptyTFile_Map_MC_Nom,  EmptyPOT_local_MC_ScaledMAP,
  "h_AverageDataoverlayFraction",  StacksMaterial_title_pdf4, "Average data overlay",
  "fractionisTrue", "NEvent", false, false);

  for(auto Vertex_vertex: kCryoVertexVaribles_vector ){

    auto histname = GetVertexCryoVarHistName(Vertex_vertex);
    char histnameMC_char[histname.length()+1];
    strcpy( histnameMC_char,histname.c_str());

    auto histname_data = GetVertexCryoVarHist_DATA_Name(Vertex_vertex);
    char histnameDATA_char[histname_data.length()+1];
    strcpy( histnameDATA_char ,histname_data.c_str());


    std::cout << " histname = "<< histname<<std::endl;
    std::cout << " histname_car = "<< histnameMC_char<<std::endl;
    std::cout << " histnameData = "<< histname_data<<std::endl;
    std::cout << " histname_car = "<< histnameDATA_char<<std::endl;

    auto TITLE = GetVertexCryoTitleName(Vertex_vertex);
    char TITLE_char[TITLE.length()+1];
    strcpy(TITLE_char,TITLE.c_str());


    auto XAxis_name = GetVertexCryoVarAxisTitle(Vertex_vertex);
    char XAxis_name_char[XAxis_name.length()+1];
    strcpy(XAxis_name_char,XAxis_name.c_str());

    std::cout<<"  DrawFULLStat_CV_SystematicErr"<<std::endl;
    std::cout<<"  DrawFULLStatCOMBINED_CV_SystematicErr"<<std::endl;

    DrawFULLStatCOMBINED_CV_SystematicErr(FullTFile_Map_MC_1D,  FullPOT_local_MC_MAP,
      EmptyTFile_Map_MC_1D,  EmptyPOT_local_MC_MAP,
      FullTFile_Map_Data_1D, FullPOT_local_Data_MAP,
      EmptyTFile_Map_Data_1D, EmptyPOT_local_Data_MAP,
      histnameMC_char ,histnameDATA_char,
      "mm", PDF_stackMap[kMaterial], TITLE_char,
      XAxis_name_char, "",  DoBinwidthNorm, MakeXaxisLOG);



      /*
      DrawFULLStat_CV_SystematicErr(FullTFile_Map_MC,  FullPOT_local_MC_ScaledMAP,
      EmptyTFile_Map_MC,  EmptyPOT_local_MC_ScaledMAP,
      FullTFile_Map_Data, FullPOT_local_Data_ScaledMAP,
      EmptyTFile_Map_Data, EmptyPOT_local_Data_ScaledMAP,
      histnameMC_char ,histnameDATA_char,
      "mm", pdf_CV, TITLE_char,
      XAxis_name_char, "NEvent",  DoBinwidthNorm, MakeXaxisLOG, MakeYaxisLOG);


      */


      std::cout<<"  Draw Stacks "<<std::endl;

      for(auto Bluebird : StackType_vector){

        std::cout<<"Drawing Seperate stacks"<<std::endl;

        //    DrawSTACKfromHistFilio_FULLStats(FullTFile_Map_MC,  FullPOT_local_MC_ScaledMAP,
        //                                  EmptyTFile_Map_MC,  EmptyPOT_local_MC_ScaledMAP,
        //                                  FullTFile_Map_Data, FullPOT_local_Data_ScaledMAP,
        //                                  EmptyTFile_Map_Data, EmptyPOT_local_Data_ScaledMAP,
        //       histnameMC_char ,histnameDATA_char, TITLE_char,
        //      XAxis_name, PDF_stackMap[Bluebird], DoBinwidthNorm, "mm", Bluebird, my_debug );

        std::cout<<"Drawing Combined "<<std::endl;

        //    DrawSTACKfromHistFilio_FULLStatsCOMBINED(FullTFile_Map_MC,  FullPOT_local_MC_MAP,
        //                                  EmptyTFile_Map_MC,  EmptyPOT_local_MC_MAP,
        //                                  FullTFile_Map_Data, FullPOT_local_Data_MAP,
        //                                  EmptyTFile_Map_Data, EmptyPOT_local_Data_MAP,
        //       histnameMC_char ,histnameDATA_char, TITLE_char,
        //      XAxis_name, PDF_stackMap[Bluebird], DoBinwidthNorm, "mm", Bluebird, my_debug );


  //DrawSTACKfromHistFilio_FULLStatsCOMBINED(FullTFile_Map_Data,  FullPOT_local_Data_MAP,
  //                                        EmptyTFile_Map_Data,  EmptyPOT_local_Data_MAP,
  //                                        FullTFile_Map_Data, FullPOT_local_Data_MAP,
  //                                        EmptyTFile_Map_Data, EmptyPOT_local_Data_MAP,
  //            histnameDATA_char ,histnameDATA_char, "DATA Type Vertex Z ",
  //            XAxis_name, PDF_stackMap[kMaterial], DoBinwidthNorm, "mm", Bluebird, my_debug, true );


  DrawSTACKfromHistFilio_FULLStatsCOMBINED(FullTFile_Map_MC_1D,  FullPOT_local_MC_MAP,
    EmptyTFile_Map_MC_1D,  EmptyPOT_local_MC_MAP,
    FullTFile_Map_Data_1D, FullPOT_local_Data_MAP,
    EmptyTFile_Map_Data_1D, EmptyPOT_local_Data_MAP,
    histnameMC_char ,histnameDATA_char, TITLE_char,
    XAxis_name, PDF_stackMap[kMaterial], DoBinwidthNorm, "mm", Bluebird, my_debug, false );



  }

}




/*

    h_Muon_PT_NTracks
    h_theta_openAngle

    h_Muon_PT_CuratureSig

    h_Muon_E_CuratureSig








    h_Data_cryoVertex_Z_OpenAngle
    h_Data_cryoVertex_R_OpenAngle
    h_Data_cryoVertex_Y_OpenAngle
    h_Data_cryoVertex_X_OpenAngle


    h_Data_Muon_PT_CuratureSig

    h_Data_Muon_E_CuratureSig













     h_Data_Vertex_R_DistanceNearEdge
     h_Data_Vertex_X_DistanceNearEdge
     h_Data_Vertex_Y_DistanceNearEdge

*/


  //  Draw2DPlots(FullTFile_Map_MC_Nom,
  //    EmptyTFile_Map_MC_Nom,
  //    Full_MC_Full_Data,
  //    Empty_MC_Full_Data,
  //    "h_2d_vertex_Z_mig" ,"RECO vertex Z [mm]", "True vertex Z [mm]", "title",
  //  mnv_plot,can, StacksMaterial_title_pdf2);


  //  Draw2DPlots(FullTFile_Map_MC_Nom,
  //    EmptyTFile_Map_MC_Nom,
  //    Full_MC_Full_Data,
  //    Empty_MC_Full_Data,
  //    "h_2d_vertex_R_mig" ,"RECO vertex R [mm]", "True vertex R [mm]", "title",
  //  mnv_plot,can, StacksMaterial_title_pdf2);







///////////////////////////////////////////
/// Migration
/////////////////////////////////////////
//std::vector<double> Zbins_corse{1450, 1750.00, 2050.00, 2250, 2450, 2650, 2850, 3000, 3200,  3400, 3650, 3900, 4200, 4350 };
////1400 , 1600 , 1800 , 2000, 2200,2600,3000,3400,3600,3800,4000,4200,4400
//std::vector<double> Rbins_corse{0, 200, 400, 600,  700,   800,  1000,  1200};
//std::vector<double> VertexXYbins_coarse{-1200, -1000, -800, -600, -400, -200, 0, 200, 400, 600, 800, 1000, 1200};

//std::vector<double> Vertex_Xbin_vector = GetBinvertexVector(kX_2D);
std::vector<double> VertexXYbins_coarse = GetBinvertexVector(kY_2D);
std::vector<double> Zbins_corse = GetBinvertexVector(kZ_2D);
std::vector<double> Rbins_corse = GetBinvertexVector(kR_2D);
std::vector<double> Ebin_vector = GetBinMuonVector(kE_2D);
std::vector<double> MuonThetabin_vector= GetBinMuonVector(kAngleWRTB);
std::vector<double> PTbin_vector= GetBinMuonVector(kP_T_2D);
std::vector<double> Pzbin_vector = GetBinMuonVector(kP_Z_2D);

/*
 Draw2DMigration_Panel(FullTFile_Map_MC_Nom,
                  EmptyTFile_Map_MC_Nom,
                  Full_MC_Full_Data,
                  Empty_MC_Full_Data,
                  "MnvR_Vertex_Z_R_migration",
                  "MnvR_Vertex_Z_R_reco",
                  "MnvR_Vertex_Z_R_truth",
                   Zbins_corse,
                   Rbins_corse,
                  "Vertex Z [mm]", "Vertex R [mm]" ,
                  mnv_plot,can, StacksMaterial_title_pdf2);


Draw2DMigration_Panel(FullTFile_Map_MC_Nom,
  EmptyTFile_Map_MC_Nom,
  Full_MC_Full_Data,
  Empty_MC_Full_Data,
  "MnvR_Vertex_Z_X_migration",
  "MnvR_Vertex_Z_X_reco",
  "MnvR_Vertex_Z_X_truth",
  Zbins_corse,
  VertexXYbins_coarse,
  "Vertex Z [mm]", "Vertex X [mm]" ,
  mnv_plot,can, StacksMaterial_title_pdf2);

Draw2DMigration_Panel(FullTFile_Map_MC_Nom,
  EmptyTFile_Map_MC_Nom,
  Full_MC_Full_Data,
  Empty_MC_Full_Data,
  "MnvR_Vertex_Z_Y_migration",
  "MnvR_Vertex_Z_Y_reco",
  "MnvR_Vertex_Z_Y_truth",
  Zbins_corse,
  VertexXYbins_coarse,
  "Vertex Z [mm]", "Vertex Y [mm]" ,
  mnv_plot,can, StacksMaterial_title_pdf2);

Draw2DMigration_Panel(FullTFile_Map_MC_Nom,
  EmptyTFile_Map_MC_Nom,
  Full_MC_Full_Data,
  Empty_MC_Full_Data,
  "MnvR_Vertex_X_Y_migration",
  "MnvR_Vertex_X_Y_reco",
  "MnvR_Vertex_X_Y_truth",
  Zbins_corse,
  VertexXYbins_coarse,
  "Vertex X [mm]", "Vertex Y [mm]" ,
  mnv_plot,can, StacksMaterial_title_pdf2);



Draw2DMigration_Panel(FullTFile_Map_MC_2D,
  EmptyTFile_Map_MC_2D,
  Full_MC_Full_Data,
  Empty_MC_Full_Data,
  "MnvR_Muon_PZ_PT_migration",
  "MnvR_Muon_PZ_PT_reco",
  "MnvR_Muon_PZ_PT_truth",
  Pzbin_vector,
  PTbin_vector,
  "P_{Z} [GeV]", "P_{T} [GeV]" ,
  mnv_plot,can, StacksMaterial_title_pdf2);


  Draw2DMigration_Panel(FullTFile_Map_MC_2D,
    EmptyTFile_Map_MC_2D,
    Full_MC_Full_Data,
    Empty_MC_Full_Data,
    "MnvR_Muon_E_theta_migration",
    "MnvR_Muon_E_theta_reco",
    "MnvR_Muon_E_theta_truth",
    Ebin_vector,
    MuonThetabin_vector,
    "E_{#mu} [GeV]", "#theta_{#mu} [Deg]" ,
    mnv_plot,can, StacksMaterial_title_pdf2);

*/

/*


std::vector<double> test_Xbins{1,2,3,4};
std::vector<double> test_Ybins{1,2,3};

std::vector<double> test_Xbins_1{1.5,2.5,3.5};
std::vector<double> test_Ybins_1{1.5,2.5};

std::vector<double> test_Xbins_2{1.5,2.5,3.5};
std::vector<double> test_Ybins_2{1.5,2.5};

std::vector<int> truthbinsX{1,2,3};
std::vector<int> truthbinsY{1,2};

std::vector<int> RecobinsX{1,2,3};
std::vector<int> RecobinsY{1,2};


error_name_Map error_name;
error_name.insert(std::pair<std::string, const int>("cv", 1));

MinervaUnfold::MnvResponse *MnvR_Test = new MinervaUnfold::MnvResponse( "MnvR_Test",  "MnvR_Test", test_Xbins,  test_Ybins,  error_name);
MinervaUnfold::MnvResponse *MnvR_Test2 = new MinervaUnfold::MnvResponse( "MnvR_Test2",  "MnvR_Test2", test_Xbins,  test_Ybins,  error_name);
//MinervaUnfold::MnvResponse *MnvR_Test3 = new MinervaUnfold::MnvResponse( "MnvR_Test3",  "MnvR_Test3", test_Xbins,  test_Ybins,  error_name);

MnvH2D *h_bin1            =    new MnvH2D("h_bin1", "h_bin1",test_Ybins.size()-1, test_Ybins.data() ,test_Ybins.size()-1, test_Ybins.data()  );
MnvH2D *h_bin2            =    new MnvH2D("h_bin2", "h_bin2",test_Ybins.size()-1, test_Ybins.data() ,test_Ybins.size()-1, test_Ybins.data()  );

MnvH2D *h_binX            =    new MnvH2D("h_binX", "h_binX",test_Xbins.size()-1, test_Xbins.data() ,test_Xbins.size()-1, test_Xbins.data()  );
MnvH2D *h_binY            =    new MnvH2D("h_binY", "h_binY",test_Ybins.size()-1, test_Ybins.data() ,test_Ybins.size()-1, test_Ybins.data()  );


double count =1;
//MnvR_Test->Fill(1.5,4.5, 1.5,4.5,"cv",0,1);
//MnvR_Test->Fill(1.5,4.5, 2.5,4.5,"cv",0,2);

//MnvR_Test->Fill(1.5,5.5, 1.5,5.5,"cv",0,3);
//MnvR_Test->Fill(1.5,5.5, 1.5,4.5,"cv",0,4);


//MnvR_Test->Fill(2.5,4.5, 1.5,4.5,"cv",0,5);
//MnvR_Test->Fill(2.5,4.5, 2.5,4.5,"cv",0,6);

//MnvR_Test->Fill(2.5,5.5, 1.5,5.5,"cv",0,7);
//MnvR_Test->Fill(2.5,5.5, 1.5,4.5,"cv",0,8);

for(auto Xbin : test_Xbins_1  ){
   for(auto Ybin:test_Ybins_1 ){

     for(auto Xbin1 : test_Xbins_2  ){
        for(auto Ybin1:test_Ybins_2 ){
          if(Xbin == Xbin1  &&  Ybin ==  Ybin1){
        //    MnvR_Test->Fill(Xbin,Ybin, Xbin1, Ybin1,"cv",0,2);
            if(1.5 == Ybin  && 1.5 == Ybin1  ) {
              h_bin1->Fill(Xbin,Xbin1,2);
            }
          }
          else if (Xbin == Xbin1  &&  Ybin !=  Ybin1){
          //  MnvR_Test->Fill(Xbin,Ybin, Xbin1, Ybin1,"cv",0,3);
            if(1.5 == Ybin  && 1.5 == Ybin1  ){ h_bin1->Fill(Xbin,Xbin1,3); }
          }
          else if (Xbin != Xbin1  &&  Ybin ==  Ybin1) {
            //MnvR_Test->Fill(Xbin,Ybin, Xbin1, Ybin1,"cv",0,5);
            if(1.5 == Ybin  && 1.5 == Ybin1  ){ h_bin1->Fill(Xbin,Xbin1,5); }
          }
          else {
            //MnvR_Test->Fill(Xbin,Ybin, Xbin1, Ybin1,"cv",0,7);
            if(1.5 == Ybin  && 1.5 == Ybin1  ) h_bin1->Fill(Xbin,Xbin1,7);
          }

      MnvR_Test2->Fill(Xbin,Ybin, Xbin1, Ybin1,"cv",0,count);


    //  MnvR_Test->Fill(Xbin,Ybin, Xbin1, Ybin1,"cv",0,count);
      count++;
   }
 }


   }





}







MnvH2D *migrationH = NULL;
MnvH2D *h_reco = NULL;
MnvH2D *h_truth = NULL;
bool check = MnvR_Test->GetMigrationObjects(migrationH, h_reco, h_truth );

MnvH2D *migrationH1 = NULL;
MnvH2D *h_reco1 = NULL;
MnvH2D *h_truth1 = NULL;
 check = MnvR_Test2->GetMigrationObjects(migrationH1, h_reco1, h_truth1 );






for(auto Xbin : test_Xbins_1  ){
   for(auto Ybin:test_Ybins_1 ){

     for(auto Xbin1 : test_Xbins_2  ){
        for(auto Ybin1:test_Ybins_2 ){
          //if(1.5 == Ybin  && 1.5 == Ybin1  ){

            int numb1 = h_reco1->FindFixBin(Xbin,Ybin);
            int numb2 = h_truth1->FindFixBin(Xbin1,Ybin1);

            double nXbin = migrationH1->GetXaxis()->GetBinCenter(numb1);

            double nYbin = migrationH1->GetYaxis()->GetBinCenter(numb2);

            auto XbinA =         migrationH1->GetXaxis()->FindBin(nXbin);
            auto YbinA =         migrationH1->GetYaxis()->FindBin(nYbin);

            //bin  = biny*(fXaxis.GetNbins()+2) + binx;

            int globalBinN = YbinA * (migrationH1->GetXaxis()->GetNbins() + 2) + XbinA;


            int globalBinN1 = GetGlobalBinNFrom2DMig(migrationH1,h_reco1, h_truth1, Xbin,Ybin, Xbin1,Ybin1);



          //int globalBinN  =   migrationH1->GetBin(nXbin,nYbin );
          double content = migrationH1->GetBinContent(globalBinN);
          std::cout<< "check1= "<< numb1 << "  check2 = "<< numb2<< std::endl;
          std::cout<<"nbins =" << globalBinN1<< " nXbin = "<< nXbin << " nYbin = "  <<  nYbin <<"  content = "<<content<<std::endl;
          std::cout<< " meas_x " << Xbin << " meas_y " << Ybin<<   " truth_x " << Xbin1 << " truth_y " << Ybin1<< std::endl;
          if(1.5 == Ybin  && 1.5 == Ybin1  ){
            h_bin2->Fill( Xbin, Xbin1,content);}

        }
      }
    }
  }


std::cout<<"Testing by Bin Number "<< std::endl;



  for(int  XTruthbinN = 1; XTruthbinN <= h_truth1->GetNbinsX();  XTruthbinN++  ){
    for(int  YTruthbinN = 1; YTruthbinN <= h_truth1->GetNbinsY();  YTruthbinN++ ){

      for(int  XRecobinN = 1; XRecobinN <= h_reco1->GetNbinsX();  XRecobinN++  ){
        for(int  YRecobinN = 1; YRecobinN <= h_reco1->GetNbinsY();  YRecobinN++  ){


          //auto XbinCenter_TRUTH = h_truth1->GetXaxis()->GetBinCenter(XTruthbinN);
          //auto YbinCenter_TRUTH = h_truth1->GetYaxis()->GetBinCenter(YTruthbinN);
          //auto XbinCenter_RECO = h_reco1->GetXaxis()->GetBinCenter(XRecobinN);
          //auto YbinCenter_RECO = h_reco1->GetYaxis()->GetBinCenter(YRecobinN);

          //int globalBinN1 = GetGlobalBinNFrom2DMig(migrationH1,h_reco1, h_truth1, XbinCenter_TRUTH,YbinCenter_TRUTH, XbinCenter_RECO,YbinCenter_RECO);
          //std::cout<<"nbins =" << globalBinN1<<std::endl;

        int globalBinN1 =  GetGlobalBinNFrom2DMig_BinN(migrationH1,h_reco1, h_truth1, XRecobinN, YRecobinN, XTruthbinN,YTruthbinN);
        double content = migrationH1->GetBinContent(globalBinN1);
        std::cout<<"nbins =" << globalBinN1<< "Content = "<< content<<std::endl;

        }
      }
    }
  }







DrawMagration_heatMap_LabelBinNumber(migrationH, "x bins", "y bins",
  "title", StacksMaterial_title_pdf2, can,mnv_plot);

  DrawMagration_heatMap_LabelBinNumber(migrationH1, "x bins", "y bins",
    "title", StacksMaterial_title_pdf2, can,mnv_plot);


    DrawMagration_heatMap_LabelBinNumber(h_reco, "x bins", "y bins",
      "h_reco", StacksMaterial_title_pdf2, can,mnv_plot);



      DrawMagration_heatMap_LabelBinNumber(h_bin1, "x bins", "y bins",
        "bin1", StacksMaterial_title_pdf2, can,mnv_plot);

        DrawMagration_heatMap_LabelBinNumber(h_bin2, "x bins", "y bins",
          "bin2", StacksMaterial_title_pdf2, can,mnv_plot);
*/

//DrawMagration_heatMap(migrationH, "x bins", "y bins", "NEvent"  , StacksMaterial_title_pdf2, can,mnv_plot);

//void DrawMagration_heatMap(MnvH2D *h_mig, const char* xaxislabel,const char* yaxislabel, const char* Title, const char* pdf, TCanvas *can, MnvPlotter *plotter , bool includeFlows= false ); // overloading function

//}// end of for loop to print



std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;

std::cout<< " Done with CryoVertex Plots  "<< std::endl;

std::cout<< " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;

   std::cout << std::endl;
   std::cout << "Done WITH Stacks" << std::endl;

   //can -> Print(text_title_pdf3);
   //can -> Print(StacksInteraction_title_pdf3);
  // can -> Print(StacksParticle_title_pdf3);
   can -> Print(StacksMaterial_title_pdf3);
   char latexName[1024];

  // sprintf(latexName,"CryoVertex_CV_totalerror_Latex_%s", timeset);
  // MakeLatex_CryoVertexCV_Error(latexName, kCryoVertexVaribles_vector, pdf_CV, 2 );
  // sprintf(latexName,"CryoVertex_stacks_Interaction_Latex_%s", timeset);
  // MakeLatex_CryoVertexStacks(latexName, kCryoVertexVaribles_vector, pdf_InteractionStacks, 2 );
  // sprintf(latexName,"CryoVertex_stacks_Particle_Latex_%s", timeset);
  // MakeLatex_CryoVertexStacks(latexName,    kCryoVertexVaribles_vector, pdf_ParticleStacks, 2 );
  // sprintf(latexName,"CryoVertex_stacks_Material_Latex_%s", timeset);
  // MakeLatex_CryoVertexStacks(latexName,    kCryoVertexVaribles_vector, pdf_MaterialStacks, 2 );



for(int i = 2; i < 349; i=i+4)
Appendtotxt_2D_2_Panel_Playlists("TwoPlots", "name.pdf",i,i+2, "" );
}


//End of MainFuntion
///////////////////////////////////

/////////////////////////////////////////////
//Main Function
/////////////////////////////////////////////

 int main() {

bool cutsOn = true;
std::cout << "Run over cutsOn?  (0 = false, 1 = true) " << std::endl;
//std::cin >> cutsOn;
std::cout << std::boolalpha << cutsOn << std::endl;

bool my_norm = 0;
std::cout << "Which Normalization?  (0 = POT, 1 = relative equal areas) " << std::endl;
//std::cin >> my_norm;
std::cout << std::boolalpha << my_norm << std::endl;

bool my_debug = 0;
std::cout << "Run in Debug Mode? (0 = NO, 1 = YES) " << std::endl;
//std::cin >> my_debug ;
std::cout << std::boolalpha << my_debug << std::endl;

int my_Print_Systmatics = 0;
std::cout << "Print Error Systmatics?  [ 0 = Total and Groups Systemtics Errors ,  1 = Total Systematic Errors , 2 = none ]" << std::endl;
//std::cin >> my_Print_Systmatics;
std::cout << "Pitched: " << my_Print_Systmatics << std::endl;


std::string input = "cnguyen";
std::cout << "What is the name of the user? " << std::endl;
//std::cin >> input;
std::cout << input << std::endl;

const char *inputFileLoc = input.c_str();

Kin(cutsOn, my_norm, my_debug, inputFileLoc, my_Print_Systmatics);

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


std::vector<ME_helium_Playlists> GetPlayListVector_DATA() {
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
  CryoVertexVars.push_back(kR);
  CryoVertexVars.push_back(kZ);
  CryoVertexVars.push_back(kdistance_edge_fiducial);


  return CryoVertexVars;
//#endif
}


void MakeLatexForCryoVertexFiguresCVandALLErrors(std::string output_name ,std::vector<CryoVertex> CryoVertex_vector, std::string PDF_cv_name, int NError_Groups){
  double scale= .24;
  std::ofstream myfile;

  const int  Column_Spacing = NError_Groups + 2;

 std::string fileName = output_name + ".txt";
  myfile.open(fileName,	std::ios::trunc);
  std::cout<<"Name of Output File "<< fileName<<std::endl;
  LatexFormat CryoVertex_latex_Latex(scale);

  int pageCount = 2;


  for(auto cat:CryoVertex_vector){

    auto input_vectors = GetBinvertexVector(cat);
    std::string Var_name = GetVertexCryoTitleName(cat);
    std::string Units_name = "mm";

    myfile<<"\n";
    myfile<<CryoVertex_latex_Latex.GetSubSection(Var_name);
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%%  Frame CV and Error grounps For  "<< Var_name <<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<CryoVertex_latex_Latex.GetBeginFrame(Var_name)<< "\n";
    myfile<<CryoVertex_latex_Latex.GetBeginTabular()<< "\n";
    myfile<<CryoVertex_latex_Latex.GetInclude_figure(pageCount,PDF_cv_name)<< "\n";
    myfile<<"& \n";
    myfile<<CryoVertex_latex_Latex.GetInclude_figure(pageCount + Column_Spacing,PDF_cv_name)<< "\n";
    myfile<<"& \n";
    myfile<<CryoVertex_latex_Latex.GetInclude_figure(pageCount + Column_Spacing+ Column_Spacing, PDF_cv_name)<< "\n";
    myfile<<CryoVertex_latex_Latex.GetEndTabular()<< "\n";
    if(input_vectors.size() < 25)
    {
      myfile<<CryoVertex_latex_Latex.BinningLatexString(input_vectors, Var_name , Units_name )<< "\n";
    }
    myfile<<CryoVertex_latex_Latex.GetEndFrame();
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% END FRAME Frame CV and Error groups "<< Var_name<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";

    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%%  Full Error group  "<< Var_name <<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<CryoVertex_latex_Latex.GetBeginFrame(Var_name)<< "\n";
    myfile<<CryoVertex_latex_Latex.GetBeginTabular()<< "\n";
    myfile<<CryoVertex_latex_Latex.GetInclude_figure(pageCount + 1, PDF_cv_name)<< "\n";
    myfile<<"& \n";
    myfile<<CryoVertex_latex_Latex.GetInclude_figure(pageCount + Column_Spacing + 1, PDF_cv_name )<< "\n";
    myfile<<"& \n";
    myfile<<CryoVertex_latex_Latex.GetInclude_figure(pageCount +  Column_Spacing +  Column_Spacing + 1, PDF_cv_name )<< "\n";
    myfile<<CryoVertex_latex_Latex.GetEndTabular()<< "\n";
    myfile<<CryoVertex_latex_Latex.GetEndFrame();
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
        myfile<<CryoVertex_latex_Latex.GetBeginFrame(Var_name)<< "\n";
        myfile<<CryoVertex_latex_Latex.GetBeginTabular()<< "\n";
        myfile<<CryoVertex_latex_Latex.GetInclude_figure(pageCount + i + 2,PDF_cv_name)<< "\n";
        myfile<<"& \n";
        myfile<<CryoVertex_latex_Latex.GetInclude_figure(pageCount + Column_Spacing + i + 2 ,PDF_cv_name)<< "\n";
        myfile<<"& \n";
        myfile<<CryoVertex_latex_Latex.GetInclude_figure(pageCount +  Column_Spacing + Column_Spacing + i + 2,PDF_cv_name)<< "\n";
        myfile<<CryoVertex_latex_Latex.GetEndTabular()<< "\n";
        myfile<<CryoVertex_latex_Latex.GetEndFrame();
        myfile<<"\n";
        myfile<<"%%%%%%%%%%%%%%%%% \n";
        myfile<<"%%% END FRAME Error groups "<< Var_name<<"\n";
        myfile<<"%%%%%%%%%%%%%%%%% \n";
      }

    }




    pageCount= pageCount +  Column_Spacing +  Column_Spacing + Column_Spacing;
  }


  myfile.close();

}//end of

void MakeLatexForCryoVertexFiguresFORStacks(std::string output_name ,std::vector<CryoVertex> CryoVertex_vector ,  std::string pdf_name){
  double scale= .23;
  std::ofstream myfile;
 std::string fileName = output_name + ".txt";
  myfile.open(fileName,	std::ios::trunc);
  std::cout<<"Name of Output File "<< fileName<<std::endl;
  LatexFormat CryoVertex_latex_Latex(scale);

  int pageCount = 2;
  std::cout << " Name of input PDF = "<< pdf_name << std::endl;

  for(auto cat:CryoVertex_vector){

    auto input_vectors = GetBinvertexVector(cat);
    std::string Var_name = GetVertexCryoTitleName(cat);
    std::string Units_name = "mm";
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%%  Frame Stack For  "<< Var_name <<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<CryoVertex_latex_Latex.GetBeginFrame(Var_name)<< "\n";
    myfile<<CryoVertex_latex_Latex.GetBeginTabular()<< "\n";
    myfile<<CryoVertex_latex_Latex.GetInclude_figure(pageCount,pdf_name)<< "\n";
    myfile<<"& \n";
    myfile<<CryoVertex_latex_Latex.GetInclude_figure(pageCount+1,pdf_name)<< "\n";
    myfile<<"& \n";
    myfile<<CryoVertex_latex_Latex.GetInclude_figure(pageCount+2,pdf_name)<< "\n";
    myfile<<CryoVertex_latex_Latex.GetEndTabular()<< "\n";
    if(input_vectors.size() < 25)
    {
      myfile<<CryoVertex_latex_Latex.BinningLatexString(input_vectors, Var_name , Units_name )<< "\n";
    }
    myfile<<CryoVertex_latex_Latex.GetEndFrame();
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% END FRAME Stack "<< Var_name<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";

    pageCount= pageCount + 3;
  }


  myfile.close();
}//end of Function

void MakeLatex_CryoVertexCV_Error(std::string output_name, std::vector<CryoVertex> CryoVertex_vector, std::string pdf_name_CV, int inputstart ){
  std::ofstream myfile;
  std::string fileName = output_name + ".txt";
  myfile.open(fileName,std::ios::trunc);
  std::cout<<"Name of Output File "<< fileName<<std::endl;
  int index = inputstart;
  LatexFormat CryoVertex_latex_Latex(.2);
  int Column_Spacing =11;


  for(auto cat: CryoVertex_vector){

    auto input_vectors = GetBinvertexVector(cat);
    std::string Var_name = GetVertexCryoTitleName(cat);
    std::string Units_name = "mm";


    myfile<<CryoVertex_latex_Latex.GetSubSection(Var_name);
    myfile<<"\n";
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% Frame  ALL FULL Playlist Breakdown"<< Var_name <<" \n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<CryoVertex_latex_Latex.GetBeginFrame(GetVertexCryoVarAxisTitle(cat))<< "\n";
    myfile<<CryoVertex_latex_Latex.GetBeginTabular("ccc")<< "\n";
    myfile<<CryoVertex_latex_Latex.GetInclude_figure(index, pdf_name_CV)<< "\n";
    myfile<<"& \n";
    myfile<<CryoVertex_latex_Latex.GetInclude_figure(index + Column_Spacing, pdf_name_CV )<< "\n";
    myfile<<"& \n";
    myfile<<CryoVertex_latex_Latex.GetInclude_figure(index + Column_Spacing * 2, pdf_name_CV)<< "\n";
    myfile<<"\\\\ \n";
    myfile<<CryoVertex_latex_Latex.GetInclude_figure(index + Column_Spacing * 3, pdf_name_CV )<< "\n";
    myfile<<"& \n";
    myfile<<CryoVertex_latex_Latex.GetInclude_figure(index + Column_Spacing * 4, pdf_name_CV)<< "\n";
    myfile<<CryoVertex_latex_Latex.GetEndTabular()<< "\n";
    if(input_vectors.size() < 25)
    {
      myfile<<CryoVertex_latex_Latex.BinningLatexString(input_vectors, Var_name , Units_name )<< "\n";
    }
    myfile<<CryoVertex_latex_Latex.GetEndFrame();

    myfile<<"\n";
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% Frame  ALL  FULL Playlist Error Breakdown"<< Var_name <<" \n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<CryoVertex_latex_Latex.GetBeginFrame(GetVertexCryoVarAxisTitle(cat))<< "\n";
    myfile<<CryoVertex_latex_Latex.GetBeginTabular("ccc")<< "\n";
    myfile<<CryoVertex_latex_Latex.GetInclude_figure(index + 1, pdf_name_CV)<< "\n";
    myfile<<"& \n";
    myfile<<CryoVertex_latex_Latex.GetInclude_figure(index + Column_Spacing + 1, pdf_name_CV )<< "\n";
    myfile<<"& \n";
    myfile<<CryoVertex_latex_Latex.GetInclude_figure(index + Column_Spacing * 2 + 1, pdf_name_CV)<< "\n";
    myfile<<"\\\\ \n";
    myfile<<CryoVertex_latex_Latex.GetInclude_figure(index + Column_Spacing * 3 + 1, pdf_name_CV )<< "\n";
    myfile<<"& \n";
    myfile<<CryoVertex_latex_Latex.GetInclude_figure(index + Column_Spacing * 4 + 1, pdf_name_CV)<< "\n";
    myfile<<CryoVertex_latex_Latex.GetEndTabular()<< "\n";
    if(input_vectors.size() < 25)
    {
      myfile<<CryoVertex_latex_Latex.BinningLatexString(input_vectors, Var_name , Units_name )<< "\n";
    }
    myfile<<CryoVertex_latex_Latex.GetEndFrame();

    //////////////////////////////////////////////////
    //Empty
    /////////////////////////////////////////////////
    myfile<<"\n";
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% Frame  ALL FULL Playlist Breakdown"<< Var_name <<" \n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<CryoVertex_latex_Latex.GetBeginFrame(GetVertexCryoVarAxisTitle(cat))<< "\n";
    myfile<<CryoVertex_latex_Latex.GetBeginTabular("ccc")<< "\n";
    myfile<<CryoVertex_latex_Latex.GetInclude_figure(index + Column_Spacing * 5, pdf_name_CV)<< "\n";
    myfile<<"& \n";
    myfile<<CryoVertex_latex_Latex.GetInclude_figure(index + Column_Spacing * 6, pdf_name_CV )<< "\n";
    myfile<<"& \n";
    myfile<<CryoVertex_latex_Latex.GetInclude_figure(index + Column_Spacing * 7, pdf_name_CV)<< "\n";
    myfile<<"\\\\ \n";
    myfile<<CryoVertex_latex_Latex.GetInclude_figure(index + Column_Spacing * 8, pdf_name_CV )<< "\n";
    myfile<<"& \n";
    myfile<<CryoVertex_latex_Latex.GetInclude_figure(index + Column_Spacing * 9, pdf_name_CV)<< "\n";
    myfile<<CryoVertex_latex_Latex.GetEndTabular()<< "\n";
    if(input_vectors.size() < 25)
    {
      myfile<<CryoVertex_latex_Latex.BinningLatexString(input_vectors, Var_name , Units_name )<< "\n";
    }
    myfile<<CryoVertex_latex_Latex.GetEndFrame();

    myfile<<"\n";
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% Frame  ALL  FULL Playlist Error Breakdown"<< Var_name <<" \n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<CryoVertex_latex_Latex.GetBeginFrame(GetVertexCryoVarAxisTitle(cat))<< "\n";
    myfile<<CryoVertex_latex_Latex.GetBeginTabular("ccc")<< "\n";
    myfile<<CryoVertex_latex_Latex.GetInclude_figure(index + Column_Spacing * 5 + 1, pdf_name_CV)<< "\n";
    myfile<<"& \n";
    myfile<<CryoVertex_latex_Latex.GetInclude_figure(index + Column_Spacing * 6 + 1, pdf_name_CV )<< "\n";
    myfile<<"& \n";
    myfile<<CryoVertex_latex_Latex.GetInclude_figure(index + Column_Spacing * 7 + 1, pdf_name_CV)<< "\n";
    myfile<<"\\\\ \n";
    myfile<<CryoVertex_latex_Latex.GetInclude_figure(index + Column_Spacing * 8 + 1, pdf_name_CV )<< "\n";
    myfile<<"& \n";
    myfile<<CryoVertex_latex_Latex.GetInclude_figure(index + Column_Spacing * 9 + 1, pdf_name_CV)<< "\n";
    myfile<<CryoVertex_latex_Latex.GetEndTabular()<< "\n";
    if(input_vectors.size() < 25)
    {
      myfile<<CryoVertex_latex_Latex.BinningLatexString(input_vectors, Var_name , Units_name )<< "\n";
    }
    myfile<<CryoVertex_latex_Latex.GetEndFrame();





    //////////////////////////////////////////////////
    //Full - Empty
    /////////////////////////////////////////////////


    myfile<<"\n";
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% Frame  Total"<< Var_name <<" \n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<CryoVertex_latex_Latex.GetBeginFrame(GetVertexCryoVarAxisTitle(cat))<< "\n";
    myfile<<CryoVertex_latex_Latex.GetBeginTabular("ccc")<< "\n";
    myfile<<CryoVertex_latex_Latex.GetInclude_figure(index + 110, pdf_name_CV, .24)<< "\n";
    myfile<<"& \n";
    myfile<<CryoVertex_latex_Latex.GetInclude_figure(index + Column_Spacing + 110, pdf_name_CV, .24 )<< "\n";
    myfile<<"& \n";
    myfile<<CryoVertex_latex_Latex.GetInclude_figure(index + Column_Spacing * 2 + 110, pdf_name_CV, .24)<< "\n";
    myfile<<CryoVertex_latex_Latex.GetEndTabular()<< "\n";
    if(input_vectors.size() < 25)
    {
      myfile<<CryoVertex_latex_Latex.BinningLatexString(input_vectors, Var_name , Units_name )<< "\n";
    }

      myfile<<CryoVertex_latex_Latex.GetEndFrame();


      myfile<<"\n";
      myfile<<"\n";
      myfile<<"%%%%%%%%%%%%%%%%% \n";
      myfile<<"%%% Frame  Total Error"<< Var_name <<" \n";
      myfile<<"%%%%%%%%%%%%%%%%% \n";
      myfile<<CryoVertex_latex_Latex.GetBeginFrame(GetVertexCryoVarAxisTitle(cat))<< "\n";
      myfile<<CryoVertex_latex_Latex.GetBeginTabular("ccc")<< "\n";
      myfile<<CryoVertex_latex_Latex.GetInclude_figure(index + 110+1, pdf_name_CV, .24)<< "\n";
      myfile<<"& \n";
      myfile<<CryoVertex_latex_Latex.GetInclude_figure(index + Column_Spacing + 110+1, pdf_name_CV, .24 )<< "\n";
      myfile<<"& \n";
      myfile<<CryoVertex_latex_Latex.GetInclude_figure(index + Column_Spacing * 2 + 110+1, pdf_name_CV, .24)<< "\n";
      myfile<<CryoVertex_latex_Latex.GetEndTabular()<< "\n";
      if(input_vectors.size() < 25)
      {
        myfile<<CryoVertex_latex_Latex.BinningLatexString(input_vectors, Var_name , Units_name )<< "\n";
      }

        myfile<<CryoVertex_latex_Latex.GetEndFrame();

        index = index + 143;
      }
      myfile.close();

    }//end of function

void MakeLatex_CryoVertexStacks(std::string output_name, std::vector<CryoVertex> CryoVertex_vector, std::string pdf_name_CV, int inputstart ){
      std::ofstream myfile;
      std::string fileName = output_name + ".txt";
      myfile.open(fileName,std::ios::trunc);
      std::cout<<"Name of Output File "<< fileName<<std::endl;
      int index = inputstart;
      LatexFormat CryoVertex_latex_Latex(.2);
      int Column_Spacing =1;

      for(auto cat: CryoVertex_vector){

        auto input_vectors = GetBinvertexVector(cat);
        std::string Var_name = GetVertexCryoTitleName(cat);
        std::string Units_name = "mm";

        myfile<<CryoVertex_latex_Latex.GetSubSection(Var_name);
        myfile<<"\n";
        myfile<<"\n";
        myfile<<"%%%%%%%%%%%%%%%%% \n";
        myfile<<"%%% Frame  ALL FULL Playlist Breakdown"<< Var_name <<" \n";
        myfile<<"%%%%%%%%%%%%%%%%% \n";
        myfile<<CryoVertex_latex_Latex.GetBeginFrame(GetVertexCryoVarAxisTitle(cat))<< "\n";
        myfile<<CryoVertex_latex_Latex.GetBeginTabular("ccc")<< "\n";
        myfile<<CryoVertex_latex_Latex.GetInclude_figure(index, pdf_name_CV)<< "\n";
        myfile<<"& \n";
        myfile<<CryoVertex_latex_Latex.GetInclude_figure(index + Column_Spacing, pdf_name_CV )<< "\n";
        myfile<<"& \n";
        myfile<<CryoVertex_latex_Latex.GetInclude_figure(index + Column_Spacing * 2, pdf_name_CV)<< "\n";
        myfile<<"\\\\ \n";
        myfile<<CryoVertex_latex_Latex.GetInclude_figure(index + Column_Spacing * 3, pdf_name_CV )<< "\n";
        myfile<<"& \n";
        myfile<<CryoVertex_latex_Latex.GetInclude_figure(index + Column_Spacing * 4, pdf_name_CV)<< "\n";
        myfile<<CryoVertex_latex_Latex.GetEndTabular()<< "\n";
        if(input_vectors.size() < 25)
        {

          myfile<<CryoVertex_latex_Latex.BinningLatexString(input_vectors, Var_name , Units_name )<< "\n";
          }
          myfile<<CryoVertex_latex_Latex.GetEndFrame();

          myfile<<"\n";
          myfile<<"\n";
          myfile<<"%%%%%%%%%%%%%%%%% \n";
          myfile<<"%%% Frame ALL FULL Playlist Breakdown"<< Var_name <<" \n";
          myfile<<"%%%%%%%%%%%%%%%%% \n";
          myfile<<CryoVertex_latex_Latex.GetBeginFrame(GetVertexCryoVarAxisTitle(cat))<< "\n";
          myfile<<CryoVertex_latex_Latex.GetBeginTabular("ccc")<< "\n";
          myfile<<CryoVertex_latex_Latex.GetInclude_figure(index+ Column_Spacing * 5, pdf_name_CV)<< "\n";
          myfile<<"& \n";
          myfile<<CryoVertex_latex_Latex.GetInclude_figure(index + Column_Spacing * 6, pdf_name_CV )<< "\n";
          myfile<<"& \n";
          myfile<<CryoVertex_latex_Latex.GetInclude_figure(index + Column_Spacing * 7, pdf_name_CV)<< "\n";
          myfile<<"\\\\ \n";
          myfile<<CryoVertex_latex_Latex.GetInclude_figure(index + Column_Spacing * 8, pdf_name_CV )<< "\n";
          myfile<<"& \n";
          myfile<<CryoVertex_latex_Latex.GetInclude_figure(index + Column_Spacing * 9, pdf_name_CV)<< "\n";
          myfile<<CryoVertex_latex_Latex.GetEndTabular()<< "\n";
          if(input_vectors.size() < 25)
          {

            myfile<<CryoVertex_latex_Latex.BinningLatexString(input_vectors, Var_name , Units_name )<< "\n";
            }
            myfile<<CryoVertex_latex_Latex.GetEndFrame();


            myfile<<"\n";
            myfile<<"\n";
            myfile<<"%%%%%%%%%%%%%%%%% \n";
            myfile<<"%%% Frame  Total Error"<< Var_name <<" \n";
            myfile<<"%%%%%%%%%%%%%%%%% \n";
            myfile<<CryoVertex_latex_Latex.GetBeginFrame(GetVertexCryoVarAxisTitle(cat))<< "\n";
            myfile<<CryoVertex_latex_Latex.GetBeginTabular("ccc")<< "\n";
            myfile<<CryoVertex_latex_Latex.GetInclude_figure(index + Column_Spacing * 10, pdf_name_CV, .24)<< "\n";
            myfile<<"& \n";
            myfile<<CryoVertex_latex_Latex.GetInclude_figure(index + Column_Spacing * 11, pdf_name_CV, .24 )<< "\n";
            myfile<<"& \n";
            myfile<<CryoVertex_latex_Latex.GetInclude_figure(index + Column_Spacing * 12, pdf_name_CV, .24)<< "\n";
            myfile<<CryoVertex_latex_Latex.GetEndTabular()<< "\n";
            if(input_vectors.size() < 25)
            {
              myfile<<CryoVertex_latex_Latex.BinningLatexString(input_vectors, Var_name , Units_name )<< "\n";
            }

              myfile<<CryoVertex_latex_Latex.GetEndFrame();

              index= index + 13;

      }

      myfile.close();


    }//end of function



void DrawEffPlots(ME_playlist_TFileMAP Full_Nom_Map, ME_playlist_TFileMAP Full_Dom_Map,
                  ME_playlist_TFileMAP Empty_Nom_Map, ME_playlist_TFileMAP Empty_Dom_Map,
                  double Full_MC_Full_Data,
                  double Empty_MC_Full_Data,
                   char *histoName_Nom,char *histoName_Dom, char *hist_histFolioName,
                   MnvPlotter *mnvPlotter, TCanvas *can,  char *pdf){

std::string pdf_string(pdf);
char pdf_char[1024];
sprintf(pdf_char, "%s.pdf" , pdf);
Playlist_MnvH1D_Map NomFull_Map = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(Full_Nom_Map, histoName_Nom );
Playlist_MnvH1D_Map NomEmpty_Map = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(Empty_Nom_Map, histoName_Nom );

Playlist_MnvH1D_Map DomFull_Map = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(Full_Dom_Map, histoName_Dom );
Playlist_MnvH1D_Map DomEmpty_Map = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(Empty_Dom_Map, histoName_Dom );


auto h_NomFull_Combined = Combine_Hists_fromMAP(NomFull_Map , kME1F ,"h_NomFull_Combined");
auto h_NomEmpty_Combined = Combine_Hists_fromMAP(NomEmpty_Map , kME1M ,"h_NomEmpty_Combined");

auto h_DomFull_Combined = Combine_Hists_fromMAP(DomFull_Map , kME1F ,"h_DomFull_Combined");
auto h_DomEmpty_Combined = Combine_Hists_fromMAP(DomEmpty_Map , kME1M ,"h_DomEmpty_Combined");
////
//Scale
//
h_NomFull_Combined->Scale(Full_MC_Full_Data);
h_DomFull_Combined->Scale(Full_MC_Full_Data);

h_NomEmpty_Combined->Scale(Empty_MC_Full_Data);
h_DomEmpty_Combined->Scale(Empty_MC_Full_Data);


MnvH1D *h_NomFull_Combined_clone = (PlotUtils::MnvH1D*)h_NomFull_Combined->Clone("h_NomFull_Combined_Clone");
MnvH1D *h_DomFull_Combined_clone = (PlotUtils::MnvH1D*)h_DomFull_Combined->Clone("h_DomFull_Combined_Clone");

MnvH1D *h_NomEmpty_Combined_clone = (PlotUtils::MnvH1D*)h_NomEmpty_Combined->Clone("h_NomEmpty_Combined_Clone");
MnvH1D *h_DomEmpty_Combined_clone = (PlotUtils::MnvH1D*)h_DomEmpty_Combined->Clone("h_DomEmpty_Combined_Clone");



DrawCVAndError_FromHIST(h_NomFull_Combined_clone, "Nom" , "Vertex Z [mm]","Events", pdf_string, false);
DrawCVAndError_FromHIST(h_DomFull_Combined_clone, "Dom" , "Vertex Z [mm]","Events", pdf_string, false);

DrawCVAndError_FromHIST(h_NomEmpty_Combined_clone, "Nom" , "Vertex Z [mm]","Events", pdf_string, false);
DrawCVAndError_FromHIST(h_DomEmpty_Combined_clone, "Dom" , "Vertex Z [mm]","Events", pdf_string, false);


h_NomFull_Combined->Add(h_NomEmpty_Combined,-1);
h_DomFull_Combined->Add(h_DomEmpty_Combined,-1);

DrawCVAndError_FromHIST(h_NomFull_Combined, "Nom" , "Vertex Z [mm]","Events", pdf_string, false);
DrawCVAndError_FromHIST(h_DomFull_Combined, "Dom" , "Vertex Z [mm]","Events", pdf_string, false);

h_NomFull_Combined->Divide(h_NomFull_Combined,h_DomFull_Combined,1.0);

DrawCVAndError_FromHIST(h_NomFull_Combined, "Efficieny" , "Vertex Z [mm]","Events", pdf_string, false);


Playlist_HistFolio_MnvH1D_Map HistFolio_PlaylistMap_Full =  Constuct_HistFolio_mvnH1DMap_FromME_playlist_TFileMAP(Full_Nom_Map, hist_histFolioName );
Playlist_HistFolio_MnvH1D_Map HistFolio_PlaylistMap_Empty =  Constuct_HistFolio_mvnH1DMap_FromME_playlist_TFileMAP(Empty_Nom_Map, hist_histFolioName );

typename std::map<ME_helium_Playlists, PlotUtils::HistFolio<PlotUtils::MnvH1D>>::const_iterator HistFoliocat;

auto CombinedFULL = (HistFolio_PlaylistMap_Full.begin()->second).GetHistArray();

  for(HistFoliocat = HistFolio_PlaylistMap_Full.begin(); HistFoliocat != HistFolio_PlaylistMap_Full.end(); ++HistFoliocat)
  {

    if(HistFoliocat->first != HistFolio_PlaylistMap_Full.begin()->first ){
      auto Full_MC_Stack_array = (HistFoliocat->second).GetHistArray();
      AddFirst_toSecond_MnvH1D_Arrays(CombinedFULL, Full_MC_Stack_array );

    }


  }//end of Loop


    //if( CompareMap_ME_helium_PlaylistsKeys(HistFolio_PlaylistMap_Empty,  EmptyMC_POTMap) == false ){assert(false && "HistFolio_PlaylistMap_Empty and EmptyMC_scalerMap have different Keys " );}
    //if( CompareMap_ME_helium_PlaylistsKeys(HistFolio_PlaylistMap_Empty,  EmptyData_POTMap) == false ){assert(false && "HistFolio_PlaylistMap_Empty and EmptyData_HistMAPScaled have different Keys " );}
    //auto  Empty_Stats_MC_Stack_Array = ((HistFolio_PlaylistMap_Empty.begin())->second).GetHistArray();
    //const TObjArray Empty_Stats_MC_Stack_Array_clone = (TObjArray)Empty_Stats_MC_Stack_Array.Clone();
    //TObjArray*  Empty_Stats_MC_Stack_Array = (TObjArray*)(*(((HistFolio_PlaylistMap_Empty.begin())->second).GetHistArray())).Clone();

   auto CombinedEmpty = (HistFolio_PlaylistMap_Empty.begin()->second).GetHistArray();

    for(HistFoliocat = HistFolio_PlaylistMap_Empty.begin(); HistFoliocat != HistFolio_PlaylistMap_Empty.end(); ++HistFoliocat)
    {
      if(HistFoliocat->first != HistFolio_PlaylistMap_Empty.begin()->first ){
        auto Empty_MC_Stack_array = (HistFoliocat->second).GetHistArray();
        AddFirst_toSecond_MnvH1D_Arrays(CombinedEmpty, Empty_MC_Stack_array);
      }

    }





  Scale_MnvH1D_Array(CombinedFULL , Full_MC_Full_Data);
  Scale_MnvH1D_Array(CombinedEmpty , Empty_MC_Full_Data);

  std::vector<double> Vertex_Zbin_vector= GetBinvertexVector(kZ);

  PlotUtils::MnvH1D* datahist =new PlotUtils::MnvH1D("adsf", " ", Vertex_Zbin_vector.size()-1, Vertex_Zbin_vector.data());

  mnvPlotter->draw_normalized_to_bin_width=true;

  mnvPlotter->DrawDataStackedMC(datahist, &CombinedEmpty, 1.0, "TR", "Data", -1, -1,
  1001, "Vertex Z [mm]", "Events", false);
  mnvPlotter->WritePreliminary("TR", .03, 0, 0, false);
  mnvPlotter->AddHistoTitle("Combined Empty",.038);
  mnvPlotter->MultiPrint(can, pdf_string, "pdf");


  mnvPlotter->DrawDataStackedMC(datahist, &CombinedFULL, 1.0, "TR", "Data", -1, -1,
  1001, "Vertex Z [mm]", "Events", false);
  mnvPlotter->WritePreliminary("TR", .03, 0, 0, false);
  mnvPlotter->AddHistoTitle("Combined Full",.038);
  mnvPlotter->MultiPrint(can, pdf_string, "pdf");

SubractSecond_FromFirst_MnvH1D_Arrays(CombinedFULL, CombinedEmpty);

PlotUtils::MnvH1D* mcHist_Helium;
PlotUtils::MnvH1D* mcHist_Helium_Combined= (PlotUtils::MnvH1D*)CombinedFULL.At(0)->Clone("mcHist_Helium_Combined");
    int nVars = CombinedFULL.GetEntries();

    for (int iHist = 0; iHist < nVars; ++iHist) {
      if(iHist==0)continue;

        PlotUtils::MnvH1D* mcHist_stack = (PlotUtils::MnvH1D*)CombinedFULL.At(iHist)->Clone();
        std::string words = mcHist_stack->GetTitle();
        std::cout<< "words " << words << std::endl;
        if(words=="Helium")mcHist_Helium = mcHist_stack;
        mcHist_Helium_Combined->Add(mcHist_stack,1.0);

      }

      mcHist_Helium ->Divide(mcHist_Helium, mcHist_Helium_Combined);

      DrawCVAndError_FromHIST(mcHist_Helium, "Purity" , "Vertex Z [mm]","Events", pdf_string, false);


DrawCVAndError_eff_purity_EOM_ERROR(h_NomFull_Combined,  mcHist_Helium, "" ,"Vertex Z [mm]",
  pdf_char, true, 1.0 , Vertex_Zbin_vector);


 //DrawCVAndError_FromHIST(MnvH1D *hist_INCOMING, char *histotitle ,std::string xaxislabel,std::string yaxislabel, std::string pdf_name, bool Setgrid);





}
///////////////////////////////////////////////////////////////////////

void Draw2DPlots(ME_playlist_TFileMAP Full_Map,
                  ME_playlist_TFileMAP Empty_Map,
                  double Full_MC_Full_Data,
                  double Empty_MC_Full_Data,
                   char *histoName ,char *xaxis, char *yaxis, char *Plot_title,
                   MnvPlotter *mnvPlotter, TCanvas *can,  char *pdf){

std::string pdf_string(pdf);
char pdf_char[1024];
sprintf(pdf_char, "%s.pdf" , pdf);

char Title[1024];


Playlist_MnvH2D_Map Full_MnvH2D_Map = Constuct_mvnH2DMap_FromME_playlist_TFileMAP(Full_Map, histoName );
Playlist_MnvH2D_Map Empty_MnvH2D_Map = Constuct_mvnH2DMap_FromME_playlist_TFileMAP(Empty_Map, histoName );


auto h_Full_Combined = Combine_2DHists_fromMAP(Full_MnvH2D_Map , kME1F ,"h_Full_Combined");
auto h_Empty_Combined = Combine_2DHists_fromMAP(Empty_MnvH2D_Map , kME1M ,"h_Empty_Combined");


////
//Scale
//
h_Full_Combined->Scale(Full_MC_Full_Data);
h_Empty_Combined->Scale(Empty_MC_Full_Data);


MnvH2D *h_Full_Combined_clone = (PlotUtils::MnvH2D*)h_Full_Combined->Clone("h_Full_Combined_Clone");
MnvH2D *h_Empty_Combined_clone = (PlotUtils::MnvH2D*)h_Empty_Combined->Clone("h_Empty_Combined_Clone");



sprintf(Title, "%s [Full]" , Plot_title);
DrawMagration_heatMap_Mig(h_Full_Combined_clone,xaxis ,yaxis, Title, pdf, can, mnvPlotter);
DrawMagration_heatMap_MigBinN(h_Full_Combined_clone,xaxis ,yaxis, Title, pdf, can, mnvPlotter,3);
Draw2DHist(h_Full_Combined_clone,   xaxis,yaxis,Title,  pdf, can, mnvPlotter);
sprintf(Title, "%s [Empty]" , Plot_title);
Draw2DHist(h_Empty_Combined_clone,   xaxis,yaxis,Title,  pdf, can, mnvPlotter);
DrawMagration_heatMap_Mig(h_Empty_Combined_clone,xaxis ,yaxis, Title, pdf, can, mnvPlotter);
DrawMagration_heatMap_MigBinN(h_Empty_Combined_clone,xaxis ,yaxis, Title, pdf, can, mnvPlotter,3);
sprintf(Title, "%s [F-E]" , Plot_title);
h_Full_Combined->Add(h_Empty_Combined,-1);
Draw2DHist(h_Full_Combined_clone,   xaxis,yaxis,Title,  pdf, can, mnvPlotter);
sprintf(Title, "%s [E/F]" , Plot_title);
h_Full_Combined_clone->Divide(h_Full_Combined_clone,h_Empty_Combined_clone,1);
Draw2DHist(h_Full_Combined_clone,   xaxis, "#frac{E}{F}", Title,  pdf, can, mnvPlotter);


 DrawMagration_heatMap_Mig(h_Full_Combined_clone,xaxis ,yaxis, Title, pdf, can, mnvPlotter);


 Full_MnvH2D_Map.clear();
 Empty_MnvH2D_Map.clear();

}

////////////////////////////////////////////////////////////////////////////////

void Draw2DPlots_Panel(ME_playlist_TFileMAP Full_Map, ME_playlist_TFileMAP Full_Data_Map,
                  ME_playlist_TFileMAP Empty_Map, ME_playlist_TFileMAP Empty_Data_Map,
                  double Full_MC_Full_Data,
                  double Empty_MC_Full_Data,
                  double Empty_Data_Full_Data,
                   char *hist_MCName,
                   char *hist_DataName,
                   char *xaxis, char *yaxis,char *unitsX,char *unitsY, char *Plot_title,  std::vector<double> YMultipliers, std::vector<double> XMultipliers,
                   bool do_bin_width_norm ,bool statPlusSysDATA , bool statPlusSysMC ,
                   MnvPlotter *mnvPlotter, TCanvas *can,  char *pdf, double XprotextSize, double YprotextSize, double FractionalErrorMax){

std::string pdf_string(pdf);
char pdf_char[1024];
sprintf(pdf_char, "%s.pdf" , pdf);
char ZaxisTitle[1024];
char Title[1024];


Playlist_MnvH2D_Map Full_MnvH2D_Map = Constuct_mvnH2DMap_FromME_playlist_TFileMAP(Full_Map, hist_MCName );
Playlist_MnvH2D_Map Empty_MnvH2D_Map = Constuct_mvnH2DMap_FromME_playlist_TFileMAP(Empty_Map, hist_MCName );

Playlist_MnvH2D_Map Full_MnvH2D_Data_Map = Constuct_mvnH2DMap_FromME_playlist_TFileMAP(Full_Data_Map, hist_DataName );
Playlist_MnvH2D_Map Empty_MnvH2D_Data_Map = Constuct_mvnH2DMap_FromME_playlist_TFileMAP(Empty_Data_Map, hist_DataName );

std::cout<<"Combine MC"<< std::endl;
auto h_Full_Combined = Combine_2DHists_fromMAP(Full_MnvH2D_Map , kME1F ,"h_Full_Combined");
auto h_Empty_Combined = Combine_2DHists_fromMAP(Empty_MnvH2D_Map , kME1M ,"h_Empty_Combined");
std::cout<<"Combine  Data"<< std::endl;
auto h_Full_Combined_Data = Combine_2DHists_fromMAP(Full_MnvH2D_Data_Map , kME1F ,"h_Full_Data_Combined");
auto h_Empty_Combined_Data = Combine_2DHists_fromMAP(Empty_MnvH2D_Data_Map , kME1M ,"h_EmptyData_Combined");

////
//Scale
//
h_Full_Combined->Scale(Full_MC_Full_Data);
h_Empty_Combined->Scale(Empty_MC_Full_Data);
h_Empty_Combined_Data->Scale(Empty_Data_Full_Data);

MnvH2D *h_Full_Combined_clone = (PlotUtils::MnvH2D*)h_Full_Combined->Clone("h_Full_Combined_Clone");
MnvH2D *h_Empty_Combined_clone = (PlotUtils::MnvH2D*)h_Empty_Combined->Clone("h_Empty_Combined_Clone");

MnvH2D *h_Full_Combined_Dataclone = (PlotUtils::MnvH2D*)h_Full_Combined_Data->Clone("h_Full_Combined_DataClone");
MnvH2D *h_Empty_Combined_Dataclone = (PlotUtils::MnvH2D*)h_Empty_Combined_Data->Clone("h_Empty_Combined_DataClone");

sprintf(ZaxisTitle,"Event /  %s ",unitsY );
sprintf(Title, "%s [Full][ProjY]" , Plot_title);
 PlotDataMC_ErrorBand2D_ProjY(h_Full_Combined_Data, h_Full_Combined,
  pdf, Title ,  xaxis, yaxis,   ZaxisTitle,
 99, false,  true, YMultipliers,
   statPlusSysDATA , statPlusSysMC , do_bin_width_norm,  false, YprotextSize);

sprintf(Title, "Fractional Error %s [Full][ProjY]" , Plot_title);
Plot2D_FractionError_ProjY(h_Full_Combined,
           pdf, Title,  xaxis, yaxis, FractionalErrorMax,.02);

sprintf(ZaxisTitle,"Event /  %s ",unitsX );
sprintf(Title, "%s [Full][ProjX]" , Plot_title);
 PlotDataMC_ErrorBand2D_ProjX(h_Full_Combined_Data, h_Full_Combined,
  pdf, Title,  yaxis, xaxis,   ZaxisTitle,
  99, false,  true,  XMultipliers,
statPlusSysDATA ,  statPlusSysMC , do_bin_width_norm,  false, XprotextSize);

sprintf(Title, "Fractional Error %s [Full][ProjX]" , Plot_title);
Plot2D_FractionError_ProjX(h_Full_Combined,
        pdf, Title,  xaxis, yaxis, FractionalErrorMax,.02);



sprintf(Title, "%s [Empty][ProjY]" , Plot_title);
sprintf(ZaxisTitle,"Event /  %s ",unitsY );
 PlotDataMC_ErrorBand2D_ProjY(h_Empty_Combined_Data, h_Empty_Combined,
  pdf, Title ,  xaxis, yaxis,   ZaxisTitle,
 99, false,  true, YMultipliers,
   statPlusSysDATA , statPlusSysMC , do_bin_width_norm,  false, YprotextSize);

sprintf(Title, "Fractional Error %s [Empty][ProjY]" , Plot_title);
Plot2D_FractionError_ProjY(h_Empty_Combined,  pdf, Title,  xaxis, yaxis, FractionalErrorMax,.02);


sprintf(Title, "%s [Empty][ProjX]" , Plot_title);
sprintf(ZaxisTitle,"Event /  %s ",unitsX );
 PlotDataMC_ErrorBand2D_ProjX(h_Empty_Combined_Data, h_Empty_Combined,
  pdf, Title ,  yaxis, xaxis,   ZaxisTitle,
  99, false,  true,   XMultipliers,
statPlusSysDATA ,  statPlusSysMC , do_bin_width_norm,  false, XprotextSize);

sprintf(Title, "Fractional Error %s [Empty][ProjX]" , Plot_title);
Plot2D_FractionError_ProjX(h_Empty_Combined,  pdf, Title,  xaxis, yaxis, FractionalErrorMax,.02);


h_Full_Combined_clone->Add(h_Empty_Combined_clone,-1);
h_Full_Combined_Dataclone->Add(h_Empty_Combined_Dataclone,-1);

sprintf(Title, "%s [F-E][ProjY]" , Plot_title);
sprintf(ZaxisTitle,"Event /  %s ",unitsY );
 PlotDataMC_ErrorBand2D_ProjY(h_Full_Combined_Dataclone, h_Full_Combined_clone,
  pdf, Title ,  xaxis, yaxis,   ZaxisTitle,
 99, false,  true, YMultipliers,
   statPlusSysDATA , statPlusSysMC , do_bin_width_norm,  false, YprotextSize);

printf(Title, "Fractional Error %s [F-E][ProjY]" , Plot_title);
(h_Empty_Combined,  pdf, Title,  xaxis, yaxis, FractionalErrorMax,.02);


sprintf(Title, "%s [F-E][ProjX]" , Plot_title);
sprintf(ZaxisTitle,"Event /  %s ",unitsX );
 PlotDataMC_ErrorBand2D_ProjX(h_Full_Combined_Dataclone, h_Full_Combined_clone,
  pdf, Title ,  yaxis, xaxis,   ZaxisTitle,
  99, false,  true,   XMultipliers,
statPlusSysDATA ,  statPlusSysMC , do_bin_width_norm,  false, XprotextSize);

sprintf(Title, "Fractional Error %s [F-E][ProjX]" , Plot_title);
Plot2D_FractionError_ProjX(h_Full_Combined_clone,  pdf, Title,  xaxis, yaxis, FractionalErrorMax,.02);


Full_MnvH2D_Map.clear();
Empty_MnvH2D_Map.clear();
Full_MnvH2D_Data_Map.clear();
Empty_MnvH2D_Data_Map.clear();
}
///////////////////////////////////////////////////////////////////////////////////


void Draw2DMigration_Panel(ME_playlist_TFileMAP Full_Map,
                  ME_playlist_TFileMAP Empty_Map,
                  double Full_MC_Full_Data,
                  double Empty_MC_Full_Data,
                  char *hist_MCName,
                  char *hist_MCName_RECO,
                  char *hist_MCName_TRUTH,
                  std::vector<double> Xbins_vector,
                  std::vector<double> Ybins_vector,
                  char *xaxis, char *yaxis ,
                  MnvPlotter *mnvPlotter, TCanvas *can,  char *pdf_char)
{

  char TRUTHbinX[1024];
  char RECObinX[1024];
  sprintf(TRUTHbinX, "TRUTH %s" , xaxis);
  sprintf(RECObinX, "RECO %s" , xaxis);

  char TRUTHbinY[1024];
  char RECObinY[1024];
  sprintf(TRUTHbinY, "TRUTH %s" , yaxis);
  sprintf(RECObinY, "RECO %s" , yaxis);

  Playlist_MnvH2D_Map Full_MnvH2D_Map_MIG = Constuct_mvnH2DMap_FromME_playlist_TFileMAP(Full_Map, hist_MCName );
  Playlist_MnvH2D_Map Empty_MnvH2D_Map_MIG = Constuct_mvnH2DMap_FromME_playlist_TFileMAP(Empty_Map, hist_MCName );

  auto h_Full_Combined_MIG = Combine_2DHists_fromMAP(Full_MnvH2D_Map_MIG , kME1F ,"h_Full_Combined_MIG");
  auto h_Empty_Combined_MIG = Combine_2DHists_fromMAP(Empty_MnvH2D_Map_MIG , kME1M ,"h_Empty_Combined_MIG");

  Full_MnvH2D_Map_MIG.clear();
  Empty_MnvH2D_Map_MIG.clear();

  Playlist_MnvH2D_Map Full_MnvH2D_Map_RECO = Constuct_mvnH2DMap_FromME_playlist_TFileMAP(Full_Map, hist_MCName_RECO );
  Playlist_MnvH2D_Map Empty_MnvH2D_Map_RECO = Constuct_mvnH2DMap_FromME_playlist_TFileMAP(Empty_Map, hist_MCName_RECO );

  auto h_Full_Combined_RECO = Combine_2DHists_fromMAP(Full_MnvH2D_Map_RECO , kME1F ,"h_Full_Combined_RECO");
  auto h_Empty_Combined_RECO = Combine_2DHists_fromMAP(Empty_MnvH2D_Map_RECO , kME1M ,"h_Empty_Combined_RECO");

  Full_MnvH2D_Map_RECO.clear();
  Empty_MnvH2D_Map_RECO.clear();

  Playlist_MnvH2D_Map Full_MnvH2D_Map_TRUTH = Constuct_mvnH2DMap_FromME_playlist_TFileMAP(Full_Map, hist_MCName_TRUTH );
  Playlist_MnvH2D_Map Empty_MnvH2D_Map_TRUTH = Constuct_mvnH2DMap_FromME_playlist_TFileMAP(Empty_Map, hist_MCName_TRUTH );

  auto h_Full_Combined_TRUTH = Combine_2DHists_fromMAP(Full_MnvH2D_Map_TRUTH , kME1F ,"h_Full_Combined_TRUTH");
  auto h_Empty_Combined_TRUTH = Combine_2DHists_fromMAP(Empty_MnvH2D_Map_TRUTH , kME1M ,"h_Empty_Combined_TRUTH");

  Full_MnvH2D_Map_TRUTH.clear();
  Empty_MnvH2D_Map_TRUTH.clear();

  bool DoBinN= true;
  double Markersize = .3;

  h_Full_Combined_MIG->Scale(Full_MC_Full_Data);
  h_Empty_Combined_MIG->Scale(Empty_MC_Full_Data);

  h_Full_Combined_RECO->Scale(Full_MC_Full_Data);
  h_Empty_Combined_RECO->Scale(Empty_MC_Full_Data);

  h_Full_Combined_TRUTH->Scale(Full_MC_Full_Data);
  h_Empty_Combined_TRUTH->Scale(Empty_MC_Full_Data);






  PlotDataMC_Migration_ProjX(h_Full_Combined_MIG, h_Full_Combined_RECO, h_Full_Combined_TRUTH,Xbins_vector,
    pdf_char, "Migration X Projection [Full]",  RECObinX,
    yaxis,   TRUTHbinX,
    100, mnvPlotter, can,4,.015,Markersize,DoBinN) ;

    PlotDataMC_Migration_ProjY(h_Full_Combined_MIG, h_Full_Combined_RECO,h_Full_Combined_TRUTH,Ybins_vector,
      pdf_char, "Migration Y Projection [Full]",  RECObinY,
      xaxis,   TRUTHbinY,
      100, mnvPlotter, can,4,.01,Markersize,DoBinN) ;

    PlotDataMC_Migration_ProjX(h_Full_Combined_MIG, h_Full_Combined_RECO,h_Full_Combined_TRUTH,Xbins_vector,
      pdf_char, "Migration X Projection  [Full](Row Norm)",  RECObinX,
      yaxis,   TRUTHbinX,
      1.0, mnvPlotter, can,3,.015,Markersize,DoBinN) ;

      PlotDataMC_Migration_ProjY(h_Full_Combined_MIG, h_Full_Combined_RECO,h_Full_Combined_TRUTH,Ybins_vector,
          pdf_char, "Migration Y Projection [Full] (Row Norm)",  RECObinY,
          xaxis,   TRUTHbinY,
          1.0, mnvPlotter, can, 3, .01,Markersize,DoBinN) ;
//////////////////////////////////////////////////////////
PlotDataMC_Migration_ProjX(h_Empty_Combined_MIG, h_Empty_Combined_RECO,h_Empty_Combined_TRUTH,Xbins_vector,
  pdf_char, "Migration X Projection [Empty]",  RECObinX,
  yaxis,   TRUTHbinX,
  100, mnvPlotter, can,4,.015,Markersize,DoBinN) ;

  PlotDataMC_Migration_ProjY(h_Empty_Combined_MIG, h_Empty_Combined_RECO,h_Empty_Combined_TRUTH,Ybins_vector,
    pdf_char, "Migration Y Projection [Empty]",  RECObinY,
    xaxis,   TRUTHbinY,
    100, mnvPlotter, can,4,.01,Markersize,DoBinN) ;

  PlotDataMC_Migration_ProjX(h_Empty_Combined_MIG, h_Empty_Combined_RECO,h_Empty_Combined_TRUTH,Xbins_vector,
    pdf_char, "Migration X Projection  [Empty](Row Norm)",  RECObinX,
    yaxis,   TRUTHbinX,
    1.0, mnvPlotter, can,3,.015,Markersize,DoBinN) ;

  PlotDataMC_Migration_ProjY(h_Empty_Combined_MIG, h_Empty_Combined_RECO,h_Empty_Combined_TRUTH,Ybins_vector,
    pdf_char, "Migration Y Projection [Empty] (Row Norm)",  RECObinY,
    xaxis,   TRUTHbinY,
    1.0, mnvPlotter, can, 3,.01,Markersize,DoBinN) ;

    h_Full_Combined_MIG->Add(h_Empty_Combined_MIG, -1);
    h_Full_Combined_RECO->Add(h_Empty_Combined_RECO, -1);
    h_Full_Combined_TRUTH->Add(  h_Empty_Combined_TRUTH, -1);

    PlotDataMC_Migration_ProjX(h_Full_Combined_MIG, h_Full_Combined_RECO,h_Full_Combined_TRUTH,Xbins_vector,
      pdf_char, "Migration X Projection [F-E]",  RECObinX,
      yaxis,   TRUTHbinX,
      100, mnvPlotter, can,4,.015,Markersize,DoBinN) ;

    PlotDataMC_Migration_ProjY(h_Full_Combined_MIG, h_Full_Combined_RECO,h_Full_Combined_TRUTH,Ybins_vector,
      pdf_char, "Migration Y Projection [F-E]",  RECObinY,
      xaxis,   TRUTHbinY,
      100, mnvPlotter, can,4,.01,Markersize,DoBinN) ;

    PlotDataMC_Migration_ProjX(h_Full_Combined_MIG, h_Full_Combined_RECO,h_Full_Combined_TRUTH,Xbins_vector,
      pdf_char, "Migration X Projection  [F-E](Row Norm)",  RECObinX,
      yaxis,   TRUTHbinX,
      1.0, mnvPlotter, can,3,.015,Markersize,DoBinN) ;

    PlotDataMC_Migration_ProjY(h_Full_Combined_MIG, h_Full_Combined_RECO,h_Full_Combined_TRUTH,Ybins_vector,
      pdf_char, "Migration Y Projection [F-E] (Row Norm)",  RECObinY,
      xaxis,   TRUTHbinY,
      1.0, mnvPlotter, can, 3,.01,Markersize,DoBinN) ;

      Full_MnvH2D_Map_MIG.clear();
      Empty_MnvH2D_Map_MIG.clear();
      Full_MnvH2D_Map_RECO.clear();
      Empty_MnvH2D_Map_RECO.clear();
      Full_MnvH2D_Map_TRUTH.clear();
      Empty_MnvH2D_Map_TRUTH.clear();


    }
///////////////////////////////////////////////////////////

void Draw2D_EfficiencyPlots_Panel(ME_playlist_TFileMAP Full_Map, ME_playlist_TFileMAP Full_TRUTH_Map,
                  ME_playlist_TFileMAP Empty_Map, ME_playlist_TFileMAP Empty_TRUTH_Map,
                  double Full_MC_Full_Data,
                  double Empty_MC_Full_Data,
                   char *hist_MCName,
                   char *hist_TruthName,
                   char *xaxis, char *yaxis,char *unitsX,char *unitsY, char *Plot_title,  std::vector<double> YMultipliers, std::vector<double> XMultipliers,
                   bool do_bin_width_norm ,bool statPlusSysDATA , bool statPlusSysMC ,
                   MnvPlotter *mnvPlotter, TCanvas *can,  char *pdf, double XprotextSize, double YprotextSize, double FractionalErrorMax){

std::string pdf_string(pdf);
char pdf_char[1024];
sprintf(pdf_char, "%s.pdf" , pdf);
char ZaxisTitle[1024];
char Title[1024];

std::cout<<"Trying Efficiency Plot with names  "<<std::endl;
std::cout<<"hist_MCName : "<< hist_MCName<<std::endl;
std::cout<<"hist_TruthName : "<< hist_TruthName<<std::endl;
Playlist_MnvH2D_Map Full_MnvH2D_Map = Constuct_mvnH2DMap_FromME_playlist_TFileMAP(Full_Map, hist_MCName );
Playlist_MnvH2D_Map Empty_MnvH2D_Map = Constuct_mvnH2DMap_FromME_playlist_TFileMAP(Empty_Map, hist_MCName );

Playlist_MnvH2D_Map Full_MnvH2D_TRUTH_Map = Constuct_mvnH2DMap_FromME_playlist_TFileMAP(Full_TRUTH_Map, hist_TruthName );
Playlist_MnvH2D_Map Empty_MnvH2D_TRUTH_Map = Constuct_mvnH2DMap_FromME_playlist_TFileMAP(Empty_TRUTH_Map, hist_TruthName );

std::cout<<"Combine MC Full "<< std::endl;
auto h_Full_Combined = Combine_2DHists_fromMAP(Full_MnvH2D_Map , kME1F ,"h_Full_Combined");
std::cout<<"Combine MC Empty "<< std::endl;
auto h_Empty_Combined = Combine_2DHists_fromMAP(Empty_MnvH2D_Map , kME1M ,"h_Empty_Combined");
std::cout<<"Combine Truth Full "<< std::endl;
auto h_Full_Combined_TRUTH = Combine_2DHists_fromMAP(Full_MnvH2D_TRUTH_Map , kME1F ,"h_Full_TRUTH_Combined");
std::cout<<"Combine Truth Empty "<< std::endl;
auto h_Empty_Combined_TRUTH = Combine_2DHists_fromMAP(Empty_MnvH2D_TRUTH_Map , kME1M ,"h_EmptyTRUTH_Combined");

////
//Scale
//


h_Full_Combined->Scale(Full_MC_Full_Data);
h_Empty_Combined->Scale(Empty_MC_Full_Data);

h_Full_Combined_TRUTH->Scale(Full_MC_Full_Data);
h_Empty_Combined_TRUTH->Scale(Empty_MC_Full_Data);

h_Full_Combined_TRUTH->AddMissingErrorBandsAndFillWithCV(*h_Full_Combined);
h_Empty_Combined_TRUTH->AddMissingErrorBandsAndFillWithCV(*h_Full_Combined);

MnvH2D *h_Full_Combined_clone = (PlotUtils::MnvH2D*)h_Full_Combined->Clone("h_Full_Combined_Clone");
MnvH2D *h_Empty_Combined_clone = (PlotUtils::MnvH2D*)h_Empty_Combined->Clone("h_Empty_Combined_Clone");

MnvH2D *h_Full_Combined_TRUTHclone = (PlotUtils::MnvH2D*)h_Full_Combined_TRUTH->Clone("h_Full_Combined_TRUTHClone");
MnvH2D *h_Empty_Combined_TRUTHclone = (PlotUtils::MnvH2D*)h_Empty_Combined_TRUTH->Clone("h_Empty_Combined_TRUTHClone");



h_Full_Combined_clone->Add(h_Empty_Combined_clone,-1);
h_Full_Combined_TRUTHclone->Add(h_Empty_Combined_TRUTHclone,-1);

sprintf(ZaxisTitle,"Event /  %s ",unitsX );
sprintf(Title, "%s [Full][ProjX]" , Plot_title);

Plot2MC_ErrorBand2D_ProjX(h_Full_Combined, "RECO",
h_Full_Combined_TRUTH, "TRUTH",
pdf, Title ,  xaxis, yaxis,   ZaxisTitle,
99, false,  true, YMultipliers,
statPlusSysDATA ,  statPlusSysMC , do_bin_width_norm,  false, XprotextSize);

sprintf(ZaxisTitle,"Event /  %s ",unitsY );
sprintf(Title, "%s [Full][ProjY]" , Plot_title);

Plot2MC_ErrorBand2D_ProjY(h_Full_Combined, "RECO",
h_Full_Combined_TRUTH, "TRUTH",
pdf, Title ,  xaxis, yaxis,   ZaxisTitle,
99, false,  true, YMultipliers,
statPlusSysDATA ,  statPlusSysMC , do_bin_width_norm,  false, XprotextSize);


h_Full_Combined_clone->Divide(h_Full_Combined_clone, h_Full_Combined_TRUTHclone);

sprintf(ZaxisTitle,"Efficiency /  %s ",unitsY );
sprintf(Title, "%s [F-E][ProjX]" , Plot_title);
PlotMC_ErrorBand2D_ProjX(h_Full_Combined_clone,
  pdf, Title ,  xaxis, yaxis,   ZaxisTitle,
  99, false,  true, YMultipliers,
  statPlusSysDATA ,  statPlusSysMC , do_bin_width_norm,  false, XprotextSize);
sprintf(Title, "%s [F-E][ProjY]" , Plot_title);

PlotMC_ErrorBand2D_ProjY(h_Full_Combined_clone,
  pdf, Title ,  yaxis, xaxis,   ZaxisTitle,
  99, false,  true, YMultipliers,
  statPlusSysDATA ,  statPlusSysMC , do_bin_width_norm,  false, XprotextSize);

  sprintf(Title, "Fractional Error %s [F-E][ProjY]" , Plot_title);
  Plot2D_FractionError_ProjY(h_Full_Combined_clone,
             pdf, Title,  yaxis, xaxis, FractionalErrorMax,.02);


sprintf(Title, "Fractional Error %s [F-E][ProjX]" , Plot_title);
Plot2D_FractionError_ProjX(h_Full_Combined_clone,
  pdf, Title,  xaxis, yaxis, FractionalErrorMax,.02);

////////////////////////////////////////////////////////////
Full_MnvH2D_Map.clear();
Empty_MnvH2D_Map.clear();
Full_MnvH2D_TRUTH_Map.clear();
Empty_MnvH2D_TRUTH_Map.clear();


}

///////////////////////////////////////////////////////////

void Draw2D_EfficiencyPlots_Panel(ME_playlist_RootPathMAP Full_Map_RootMap, ME_playlist_RootPathMAP Full_Map_RootMapTRUTH,
  ME_playlist_RootPathMAP Empty_Map_RootMap, ME_playlist_RootPathMAP Empty_Map_RootMapTRUTH,
  double Full_MC_Full_Data,
  double Empty_MC_Full_Data,
  char *hist_MCName,
  char *hist_TruthName,
  char *xaxis, char *yaxis,char *unitsX,char *unitsY, char *Plot_title,
  std::vector<double> YMultipliers, std::vector<double> XMultipliers,
  bool do_bin_width_norm ,bool statPlusSysDATA , bool statPlusSysMC ,
  MnvPlotter *mnvPlotter, TCanvas *can,  char *pdf, double XprotextSize,
  double YprotextSize, double FractionalErrorMax){


ME_playlist_TFileMAP Full_Map = MakeTFileMap(Full_Map_RootMap);
ME_playlist_TFileMAP Empty_Map = MakeTFileMap(Empty_Map_RootMap);


ME_playlist_TFileMAP Full_Map_TRUTH = MakeTFileMap(Full_Map_RootMapTRUTH);
ME_playlist_TFileMAP Empty_Map_TRUTH = MakeTFileMap(Empty_Map_RootMapTRUTH);


Draw2D_EfficiencyPlots_Panel(Full_Map, Full_Map_TRUTH,
  Empty_Map, Empty_Map_TRUTH,
  Full_MC_Full_Data,
  Empty_MC_Full_Data,
  hist_MCName,
  hist_TruthName,
  xaxis, yaxis,unitsX,unitsY, Plot_title,  YMultipliers,  XMultipliers,
  do_bin_width_norm , statPlusSysDATA ,  statPlusSysMC ,
  mnvPlotter, can,pdf,  XprotextSize,  YprotextSize,  FractionalErrorMax);


  ME_playlist_TFileMAP::iterator MC_Map;
  ME_playlist_TFileMAP::iterator Truth_Map;
  for( MC_Map = Full_Map.begin(), Truth_Map=Full_Map_TRUTH.begin() ; MC_Map != Full_Map.end();  MC_Map++,Truth_Map++){

    MC_Map->second->Close();
    Truth_Map->second->Close();
    delete Truth_Map->second;
    delete MC_Map->second;
  }



  for( MC_Map = Empty_Map.begin(), Truth_Map=Empty_Map_TRUTH.begin() ; MC_Map != Empty_Map.end();  MC_Map++,Truth_Map++){

    MC_Map->second->Close();
    Truth_Map->second->Close();
    delete Truth_Map->second;
    delete MC_Map->second;
  }

  Full_Map.clear();
  Empty_Map.clear();
  Full_Map_TRUTH.clear();
  Empty_Map_TRUTH.clear();

  return;



}


/*
void Draw_Efficiency_2D_FULL_EMPTY_TRUTH_FullStats_Combined_PanelPlots_new(ME_playlist_TFileMAP FullMCMap, ME_playlist_TFileMAP Full_TRUTHDEM_MCMap,
                                                                           ME_playlist_TFileMAP EmptyMCMap,
                                                                          ME_playlist_TFileMAP Empty_TRUTHDEM_MCMap
                                                                         double ScaleFullMCtoFullDataMC, double Scale_EmptyMCtoFulldataMC
                                                                        char *histoName_nom,
                                                                        char *histoName_dem,
                                                                         const char *Xaxis_title, const char *Yaxis_title,const char * Zaxis_title,
                                                                       bool logScale, bool doBinwidth, const char* title_type_char, const char* title ,MnvPlotter *mnvPlotter,
                                                                       TCanvas *can,  char *pdf, bool OnlyEffplot, double max_x, double max_y , double txt_sizeY , double txt_sizeX )
{

      char histoName_TRUE[1024];
      char histoName_TRUE_RECO[1024];
      char Title_His[1024];
      std::string Xaxis_title_string(Xaxis_title);
      std::string Yaxis_title_string(Yaxis_title);

      Playlist_MnvH2D_Map FULL_numerator_MC_HistMAP =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(FullMCMap, histoName_nom );
      Playlist_MnvH2D_Map FULL_denominator_MC_HistMAP =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(Full_TRUTHDEM_MCMap, histoName_dem );

      Playlist_MnvH2D_Map Empty_numerator_MC_HistMAP =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(EmptyMCMap, histoName_nom );
      Playlist_MnvH2D_Map Empty_denominator_MC_HistMAP =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(Empty_TRUTHDEM_MCMap, histoName_dem );


      auto FULL_numerator_Hist = Combine_2DHists_fromMAP(FULL_numerator_MC_HistMAP  , kME1F ,"FULL_numerator_Hist");
      auto FULL_denominator_Hist = Combine_2DHists_fromMAP(FULL_denominator_MC_HistMAP , kME1F ,"FULL_denominator_Hist");

      auto Empty_numerator_Hist = Combine_2DHists_fromMAP(Empty_numerator_MC_HistMAP  , kME1M  ,"Empty_numerator_Hist");
      auto Empty_denominator_Hist = Combine_2DHists_fromMAP(Empty_denominator_MC_HistMAP , kME1M  ,"Empty_denominator_Hist");


      Empty_numerator_Hist->Scale(Scale_EmptyMCtoFulldataMC);
      Empty_denominator_Hist->Scale(Scale_EmptyMCtoFulldataMC);

      FULL_numerator_Hist->Scale(ScaleFullMCtoFullDataMC);
      FULL_denominator_Hist->Scale(ScaleFullMCtoFullDataMC);

      Empty_denominator_Hist->AddMissingErrorBandsAndFillWithCV(*Empty_numerator_Hist);
      Full_denominator_Hist->AddMissingErrorBandsAndFillWithCV(*Full_numerator_Hist);

      auto FULL_EmptyMC_Hist_numerator =(MnvH2D*) FULL_numerator_Hist->Clone("FULL_EmptyMC_Hist_numerator");
      auto FULL_EmptyMC_Hist_denominator =(MnvH2D*) FULL_denominator_Hist->Clone("FULL_EmptyMC_Hist_denominator");

      if(OnlyEffplot==false){
        sprintf(Title_His, "%s (%s)[TRUTH] [combined Full Denom]", title_type_char, title);
        Draw_2D_Panel_MC_Only_frompointer(FULL_denominator_Hist, Title_His, "MC", Xaxis_title_string,"", Yaxis_title_string,"", Zaxis_title, 1.25, pdf, doBinwidth, logScale, txt_sizeX, txt_sizeY);

        sprintf(Title_His, "%s (%s)[TRUTH+RECO] [combined Full Num]", title_type_char, title);
        Draw_2D_Panel_MC_Only_frompointer(FULL_numerator_Hist, Title_His, "MC", Xaxis_title_string,"", Yaxis_title_string,"", Zaxis_title, 1.25, pdf, doBinwidth, logScale, txt_sizeX, txt_sizeY);

      }

      FULL_numerator_Hist->Divide(FULL_numerator_Hist, FULL_denominator_Hist, 1.0,1.0,"");
      sprintf(Title_His, "2D Efficiency %s (%s) (Full Combined) ", title_type_char, title);
      Draw_2D_Panel_MC_Only_frompointer(FULL_numerator_Hist, Title_His, "MC", Xaxis_title_string,"", Yaxis_title_string,"", Zaxis_title, 1.25, pdf, doBinwidth, logScale, txt_sizeX, txt_sizeY);


      ////////////////////////////////////////////////////////////////////////////////////////////////////////////
      if(OnlyEffplot==false){
        sprintf(Title_His, "%s (%s) [TRUTH] [combined Empty Denom]", title_type_char,title);
        Draw_2D_Panel_MC_Only_frompointer(Empty_denominator_Hist, Title_His, "MC", Xaxis_title_string,"", Yaxis_title_string,"", Zaxis_title, 1.25, pdf, doBinwidth, logScale, txt_sizeX, txt_sizeY);

        sprintf(Title_His, "%s  (%s)[TRUTH+RECO] [combined Empty Num]", title_type_char,title);
        Draw_2D_Panel_MC_Only_frompointer(Empty_numerator_Hist, Title_His, "MC", Xaxis_title_string,"", Yaxis_title_string,"", Zaxis_title, 1.25, pdf, doBinwidth, logScale, txt_sizeX, txt_sizeY);

      }
      Empty_numerator_Hist->Divide(Empty_numerator_Hist, FULL_denominator_Hist, 1.0,1.0,"");
      sprintf(Title_His, "2D Efficiency %s (%s) (Empty Combined) ", title_type_char, title);
      Draw_2D_Panel_MC_Only_frompointer(Empty_numerator_Hist, Title_His, "MC", Xaxis_title_string,"", Yaxis_title_string,"", Zaxis_title, 1.25, pdf, doBinwidth, logScale, txt_sizeX, txt_sizeY);

      FULL_EmptyMC_Hist_numerator->Add(Empty_numerator_Hist,-1);
      FULL_EmptyMC_Hist_denominator->Add(Empty_denominator_Hist,-1);

      if(OnlyEffplot==false){
        sprintf(Title_His, "%s (%s)[TRUTH] [Denominator(F-E)]", title_type_char,title);
        Draw_2D_Panel_MC_Only_frompointer(FULL_EmptyMC_Hist_denominator, Title_His, "MC", Xaxis_title_string,"", Yaxis_title_string,"", Zaxis_title, 1.25, pdf, doBinwidth, logScale, txt_sizeX, txt_sizeY);


        sprintf(Title_His, "%s (%s)[TRUTH+RECO] [Numerator(F-E)]", title_type_char,title);
        Draw_2D_Panel_MC_Only_frompointer(FULL_EmptyMC_Hist_numerator, Title_His, "MC", Xaxis_title_string,"", Yaxis_title_string,"", Zaxis_title, 1.25, pdf, doBinwidth, logScale, txt_sizeX, txt_sizeY);


      }
      FULL_EmptyMC_Hist_numerator->Divide(FULL_EmptyMC_Hist_numerator, FULL_EmptyMC_Hist_denominator, 1.0,1.0,"");
      sprintf(Title_His, "2D Efficiency %s (%s) [Combined (F-E)]", title_type_char, title);
      Draw_2D_Panel_MC_Only_frompointer(FULL_EmptyMC_Hist_numerator, Title_His, "MC", Xaxis_title_string,"", Yaxis_title_string,"", Zaxis_title, 1.25, pdf, doBinwidth, logScale, txt_sizeX, txt_sizeY);



}//endl;
*/



void Appendtotxt_2D_2_Panel_Playlists(std::string output_name ,  std::string pdf_name_CV, int First_page,int second_page, char *Var_name )
  {
  double scale= .37;
  std::ofstream myfile;

 std::string fileName = output_name + ".txt";
  myfile.open(fileName, std::ios_base::app);
  std::cout<<"Adding to Latex File "<< fileName<<std::endl;
  LatexFormat Eff2d(scale);

  myfile<<Eff2d.GetSubSection(Var_name);
  int Column_Spacing = 1;

    myfile<<"\n";
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% Frame FUll Projection Y "<< Var_name <<" \n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<Eff2d.GetBeginFrame(Var_name)<< "\n";
    myfile<<Eff2d.GetBeginTabular("cc")<< "\n";
    myfile<<Eff2d.GetInclude_figure(First_page  , pdf_name_CV, scale)<< "\n";
    myfile<<"& \n";
    myfile<<Eff2d.GetInclude_figure(second_page  , pdf_name_CV, scale)<< "\n";
    myfile<<Eff2d.GetEndTabular()<< "\n";
    myfile<<Eff2d.GetEndFrame();
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% Frame FUll Projection Y END "<< Var_name <<" \n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";

    myfile.close();


}//end of

//////////////////////////////////////////////////////////////////////////////
/*
void Draw2DStackPlots_Panel(ME_playlist_TFileMAP Full_Map, ME_playlist_TFileMAP Full_Data_Map,
                  ME_playlist_TFileMAP Empty_Map, ME_playlist_TFileMAP Empty_Data_Map,
                  double Full_MC_Full_Data,
                  double Empty_MC_Full_Data,
                  double Empty_Data_Full_Data,
                   char *histoName_MC,
                   char *Charstacktype,
                   char *hist_DataName,
                   char *xaxis, char *yaxis,char *unitsX,char *unitsY, char *Plot_title,  std::vector<double> YMultipliers, std::vector<double> XMultipliers,
                   bool do_bin_width_norm,
                   MnvPlotter *mnvPlotter, TCanvas *can,  char *pdf, double XprotextSize, double YprotextSize, std::vector<int> fillColors){

std::string pdf_string(pdf);
char pdf_char[1024];
sprintf(pdf_char, "%s.pdf" , pdf);
char ZaxisTitle[1024];
char Title[1024];

char Stack_Name[1024];
sprintf(Stack_Name, "%s_%s",histoName_MC, Charstacktype );
std::string Stack_Name_string(Stack_Name);
//Playlist_HistFolio_MnvH2D_Map Full_MnvH2D_Map = Constuct_HistFolio_MnvH2DMap_FromME_playlist_TFileMAP(Full_Map, Stack_Name);
//TObjArray Full_ObjArray =  Combined_HistFolio_MnvH2D_Map( Full_Map );
TObjArray Full_ObjArray = CombinedStack_MnvH2D_Map(Full_Map, Stack_Name_string ,kME1F  );
//TObjArray Full_ObjArray = ConstuctTObjArray_HistFolio_MnvH2DMap_FromME_playlist_TFileMAP(Full_Map, Stack_Name );
//
//Full_MnvH2D_Map.clear();
Scale_MnvH2D_Array(Full_ObjArray, Full_MC_Full_Data);
//Scale_MnvH2D_Array(Empty_ObjArray, Empty_MC_Full_Data);
//Scale_MnvH2D_Array(Empty_ObjArray, Empty_MC_Full_Data);
//TObjArray* Full_Empty_ObjArray = (*TObjArray)Full_ObjArray.Clone();

//SubractSecond_FromFirst_MnvH2D_Arrays(Full_ObjArray,  Empty_ObjArray);

Playlist_MnvH2D_Map Full_MnvH2D_Data_Map = Constuct_mvnH2DMap_FromME_playlist_TFileMAP(Full_Data_Map, hist_DataName );
Playlist_MnvH2D_Map Empty_MnvH2D_Data_Map = Constuct_mvnH2DMap_FromME_playlist_TFileMAP(Empty_Data_Map, hist_DataName );

std::cout<<"Combine  Data"<< std::endl;
auto h_Full_Combined_Data = Combine_2DHists_fromMAP(Full_MnvH2D_Data_Map , kME1F ,"h_Full_Data_Combined");
auto h_Empty_Combined_Data = Combine_2DHists_fromMAP(Empty_MnvH2D_Data_Map , kME1M ,"h_EmptyData_Combined");


Full_MnvH2D_Data_Map.clear();
Empty_MnvH2D_Data_Map.clear();
//Empty_MnvH2D_Data_Map.erase (Empty_MnvH2D_Data_Map.begin(),Empty_MnvH2D_Data_Map.end());
////
//Scale
//

//h_Empty_Combined_Data->Scale(Empty_Data_Full_Data);
//h_Full_Combined_Data->Add(h_Empty_Combined_Data,-1);
//MnvH2D *h_Full_Combined_Dataclone = (PlotUtils::cMnvH2D*)h_Full_Combined_Data->Clone("h_Full_Combined_DataClone");
//MnvH2D *h_Empty_Combined_Dataclone = (PlotUtils::MnvH2D*)h_Empty_Combined_Data->Clone("h_Empty_Combined_DataClone");


//////////////////////////////////////////////////
///  F
/////////////////////////////////////////////////
//const TObjArray  *mcHists_Breakdown_Full =  &Full_ObjArray ;


sprintf(ZaxisTitle,"Event /  %s ",unitsX );
sprintf(Title, "%s [F][ProjX]" , Plot_title);

std::cout<<"plot: F-E::PlotDataStackedMC2D_ProjX"<<std::endl;

PlotDataStackedMC2D_ProjX(h_Full_Combined_Data, Full_ObjArray,
                        fillColors,
                        pdf, Title ,  xaxis, yaxis, ZaxisTitle,
                         99, false,  true, YMultipliers,
                         do_bin_width_norm, XprotextSize);

sprintf(ZaxisTitle,"Event /  %s ",unitsY );
sprintf(Title, "%s [F][ProjY]" , Plot_title);
std::cout<<"plot: F::PlotDataStackedMC2D_ProjY"<<std::endl;

PlotDataStackedMC2D_ProjY(h_Full_Combined_Data,
  Full_ObjArray,
  fillColors,
  pdf, Title ,  yaxis, xaxis, ZaxisTitle,
  99, false,  true, YMultipliers,
  do_bin_width_norm, YprotextSize);


//////////////////////////////////////////////////
///  E
/////////////////////////////////////////////////

//Playlist_HistFolio_MnvH2D_Map Empty_MnvH2D_Map = Constuct_HistFolio_MnvH2DMap_FromME_playlist_TFileMAP(Empty_Map, Stack_Name);
//TObjArray Empty_ObjArray =  Combined_HistFolio_MnvH2D_Map( Empty_Map );
TObjArray Empty_ObjArray = CombinedStack_MnvH2D_Map(Empty_Map, Stack_Name_string ,kME1M  );


//TObjArray Empty_ObjArray = ConstuctTObjArray_HistFolio_MnvH2DMap_FromME_playlist_TFileMAP(Empty_Map, Stack_Name );

//Empty_MnvH2D_Map.clear();
Scale_MnvH2D_Array(Empty_ObjArray, Empty_MC_Full_Data);


//const TObjArray  *mcHists_Breakdown_Empty =  &Empty_ObjArray ;
//mcHists_Breakdown =  &Empty_ObjArray ;
sprintf(ZaxisTitle,"Event /  %s ",unitsY );
sprintf(Title, "%s [Empty][ProjY]" , Plot_title);
std::cout<<"plot: Empty::PlotDataStackedMC2D_ProjY"<<std::endl;
PlotDataStackedMC2D_ProjY(h_Empty_Combined_Data,
                          Empty_ObjArray,
                        fillColors,
                        pdf, Title ,  yaxis, xaxis, ZaxisTitle,
                         99, false,  true, YMultipliers,
                         do_bin_width_norm, YprotextSize);


sprintf(ZaxisTitle,"Event /  %s ",unitsX );
sprintf(Title, "%s [Empty][ProjX]" , Plot_title);
std::cout<<"plot: Empty::PlotDataStackedMC2D_ProjX"<<std::endl;
PlotDataStackedMC2D_ProjX(h_Empty_Combined_Data, Empty_ObjArray,
                       fillColors,
                       pdf, Title ,  xaxis, yaxis, ZaxisTitle,
                        99, false,  true, YMultipliers,
                        do_bin_width_norm, XprotextSize);
//////////////////////////////////////////////////////////////
/// F - E
/////////////////////////////////////////////////

//ch_Full_Combined_Dataclone->Add(h_Empty_Combined_Dataclone,-1);

sprintf(Title, "%s [F-E][ProjY]" , Plot_title);
sprintf(ZaxisTitle,"Event /  %s ",unitsY );



sprintf(Title, "%s [F-E][ProjX]" , Plot_title);
sprintf(ZaxisTitle,"Event /  %s ",unitsX );

//Full_MnvH2D_Map.erase (Full_MnvH2D_Map.begin(),Full_MnvH2D_Map.end());
//Full_MnvH2D_Data_Map.erase (Full_MnvH2D_Data_Map.begin(),Full_MnvH2D_Data_Map.end());

//Empty_MnvH2D_Map.erase (Empty_MnvH2D_Map.begin(),Empty_MnvH2D_Map.end());
//Empty_MnvH2D_Data_Map.erase (Empty_MnvH2D_Data_Map.begin(),Empty_MnvH2D_Data_Map.end());

return;

}*/
///////////////////////////////////////////////////////////////////////////////
void Draw2DStackPlots_Panel_Full_Empty(ME_playlist_TFileMAP Full_Map, ME_playlist_TFileMAP Full_Data_Map,
                  ME_playlist_TFileMAP Empty_Map, ME_playlist_TFileMAP Empty_Data_Map,
                  double Full_MC_Full_Data,
                  double Empty_MC_Full_Data,
                  double Empty_Data_Full_Data,
                   char *histoName_MC,
                   char *Charstacktype,
                   std::vector<std::string> StackNames,
                   char *hist_DataName,
                   char *xaxis, char *yaxis,char *unitsX,char *unitsY, char *Plot_title,  std::vector<double> YMultipliers, std::vector<double> XMultipliers,
                   bool do_bin_width_norm,
                   MnvPlotter *mnvPlotter, TCanvas *can,  char *pdf, double XprotextSize, double YprotextSize, std::vector<int> fillColors){

std::string pdf_string(pdf);
char pdf_char[1024];
sprintf(pdf_char, "%s.pdf" , pdf);
char ZaxisTitle[1024];
char Title[1024];

char Stack_Name[1024];
sprintf(Stack_Name, "%s_%s",histoName_MC, Charstacktype );
std::string Stack_Name_string(Stack_Name);
//Playlist_HistFolio_MnvH2D_Map Full_MnvH2D_Map = Constuct_HistFolio_MnvH2DMap_FromME_playlist_TFileMAP(Full_Map, Stack_Name);
//TObjArray Full_ObjArray =  Combined_HistFolio_MnvH2D_Map( Full_MnvH2D_Map );

//TObjArray Full_ObjArray = ConstuctTObjArray_HistFolio_MnvH2DMap_FromME_playlist_TFileMAP(Full_Map, Stack_Name );
std::cout<< "Starting to make:Full_ObjArray "<<std::endl;
//TObjArray Full_ObjArray = ConstuctTObjArray_HistFolio_MnvH2DMap_FromME_playlist_TFileMAP_Full_Empty(Full_Map, Empty_Map,
//    Stack_Name , Full_MC_Full_Data, Empty_MC_Full_Data );
//
TObjArray Full_ObjArray = CombinedStack_MnvH2D_Map(Full_Map, Stack_Name_string, StackNames, kME1F  );
//Full_MnvH2D_Map.clear();
Scale_MnvH2D_Array(Full_ObjArray, Full_MC_Full_Data);
//Scale_MnvH2D_Array(Empty_ObjArray, Empty_MC_Full_Data);
//TObjArray Empty_ObjArray = ConstuctTObjArray_HistFolio_MnvH2DMap_FromME_playlist_TFileMAP(Empty_Map, Stack_Name );
//Scale_MnvH2D_Array(Empty_ObjArray, Empty_MC_Full_Data);
//TObjArray* Full_Empty_ObjArray = (*TObjArray)Full_ObjArray.Clone();

//SubractSecond_FromFirst_MnvH2D_Arrays(Full_ObjArray,  Empty_ObjArray);

Playlist_MnvH2D_Map Full_MnvH2D_Data_Map = Constuct_mvnH2DMap_FromME_playlist_TFileMAP(Full_Data_Map, hist_DataName );
Playlist_MnvH2D_Map Empty_MnvH2D_Data_Map = Constuct_mvnH2DMap_FromME_playlist_TFileMAP(Empty_Data_Map, hist_DataName );

std::cout<<"Combine  Data"<< std::endl;
auto h_Full_Combined_Data = Combine_2DHists_fromMAP(Full_MnvH2D_Data_Map , kME1F ,"h_Full_Data_Combined");
auto h_Empty_Combined_Data = Combine_2DHists_fromMAP(Empty_MnvH2D_Data_Map , kME1M ,"h_EmptyData_Combined");


Full_MnvH2D_Data_Map.clear();
Empty_MnvH2D_Data_Map.clear();
//Empty_MnvH2D_Data_Map.erase (Empty_MnvH2D_Data_Map.begin(),Empty_MnvH2D_Data_Map.end());
////
//Scale
//

h_Empty_Combined_Data->Scale(Empty_Data_Full_Data);
//h_Full_Combined_Data->Add(h_Empty_Combined_Data,-1);
//MnvH2D *h_Full_Combined_Dataclone = (PlotUtils::cMnvH2D*)h_Full_Combined_Data->Clone("h_Full_Combined_DataClone");
//MnvH2D *h_Empty_Combined_Dataclone = (PlotUtils::MnvH2D*)h_Empty_Combined_Data->Clone("h_Empty_Combined_DataClone");


//////////////////////////////////////////////////
///  F
/////////////////////////////////////////////////
//const TObjArray  *mcHists_Breakdown_Full =  &Full_ObjArray ;


sprintf(ZaxisTitle,"Event /  %s ",unitsX );
sprintf(Title, "%s [F][ProjX]" , Plot_title);

std::cout<<"plot: F::PlotDataStackedMC2D_ProjX"<<std::endl;

if(Charstacktype=="Particle"){Rename_particleStacks(Full_ObjArray);}

PlotDataStackedMC2D_ProjX(h_Full_Combined_Data, Full_ObjArray,
                        fillColors,
                        pdf, Title ,  xaxis, yaxis, ZaxisTitle,
                         99, false,  true, YMultipliers,
                         do_bin_width_norm, XprotextSize);

sprintf(ZaxisTitle,"Event /  %s ",unitsY );
sprintf(Title, "%s [F][ProjY]" , Plot_title);
std::cout<<"plot: F::PlotDataStackedMC2D_ProjY"<<std::endl;

PlotDataStackedMC2D_ProjY(h_Full_Combined_Data,
  Full_ObjArray,
  fillColors,
  pdf, Title ,  yaxis, xaxis, ZaxisTitle,
  99, false,  true, YMultipliers,
  do_bin_width_norm, YprotextSize);


//////////////////////////////////////////////////
///  E
/////////////////////////////////////////////////

//Playlist_HistFolio_MnvH2D_Map Empty_MnvH2D_Map = Constuct_HistFolio_MnvH2DMap_FromME_playlist_TFileMAP(Empty_Map, Stack_Name);
//TObjArray Empty_ObjArray =  Combined_HistFolio_MnvH2D_Map( Empty_Map );

std::cout<< "Starting to make:Empty_ObjArray "<<std::endl;
TObjArray Empty_ObjArray = CombinedStack_MnvH2D_Map(Empty_Map, Stack_Name_string, StackNames, kME1M  );

//TObjArray Empty_ObjArray = ConstuctTObjArray_HistFolio_MnvH2DMap_FromME_playlist_TFileMAP(Empty_Map, Stack_Name );
//Scale_MnvH2D_Array(Empty_ObjArray, Empty_MC_Full_Data);
//Empty_MnvH2D_Map.clear();
Scale_MnvH2D_Array(Empty_ObjArray, Empty_MC_Full_Data);
if(Charstacktype=="Particle"){Rename_particleStacks(Empty_ObjArray);}

//const TObjArray  *mcHists_Breakdown_Empty =  &Empty_ObjArray ;
//mcHists_Breakdown =  &Empty_ObjArray ;

sprintf(ZaxisTitle,"Event /  %s ",unitsX );
sprintf(Title, "%s [Empty][ProjX]" , Plot_title);
std::cout<<"plot: Empty::PlotDataStackedMC2D_ProjX"<<std::endl;
PlotDataStackedMC2D_ProjX(h_Empty_Combined_Data, Empty_ObjArray,
                       fillColors,
                       pdf, Title ,  xaxis, yaxis, ZaxisTitle,
                        99, false,  true, YMultipliers,
                        do_bin_width_norm, XprotextSize);



sprintf(ZaxisTitle,"Event /  %s ",unitsY );
sprintf(Title, "%s [Empty][ProjY]" , Plot_title);
std::cout<<"plot: Empty::PlotDataStackedMC2D_ProjY"<<std::endl;
PlotDataStackedMC2D_ProjY(h_Empty_Combined_Data,
                          Empty_ObjArray,
                        fillColors,
                        pdf, Title ,  yaxis, xaxis, ZaxisTitle,
                         99, false,  true, YMultipliers,
                         do_bin_width_norm, YprotextSize);



//////////////////////////////////////////////////////////////
/// F - E
/////////////////////////////////////////////////
std::cout<<"plot: F-E::PlotDataStackedMC2D_ProjX"<<std::endl;
//ch_Full_Combined_Dataclone->Add(h_Empty_Combined_Dataclone,-1);
h_Full_Combined_Data->Add(h_Empty_Combined_Data,-1);
SubractSecond_FromFirst_MnvH2D_Arrays(Full_ObjArray,  Empty_ObjArray);


sprintf(Title, "%s [F-E][ProjX]" , Plot_title);
sprintf(ZaxisTitle,"Event /  %s ",unitsX );
PlotDataStackedMC2D_ProjX(h_Full_Combined_Data, Full_ObjArray,
                       fillColors,
                       pdf, Title ,  xaxis, yaxis, ZaxisTitle,
                        99, false,  true, YMultipliers,
                        do_bin_width_norm, XprotextSize);



sprintf(Title, "%s [F-E][ProjY]" , Plot_title);
sprintf(ZaxisTitle,"Event /  %s ",unitsY );
PlotDataStackedMC2D_ProjY(h_Full_Combined_Data,
                          Full_ObjArray,
                        fillColors,
                        pdf, Title ,  yaxis, xaxis, ZaxisTitle,
                         99, false,  true, YMultipliers,
                         do_bin_width_norm, YprotextSize);





//Full_MnvH2D_Map.erase (Full_MnvH2D_Map.begin(),Full_MnvH2D_Map.end());
//Full_MnvH2D_Data_Map.erase (Full_MnvH2D_Data_Map.begin(),Full_MnvH2D_Data_Map.end());

//Empty_MnvH2D_Map.erase (Empty_MnvH2D_Map.begin(),Empty_MnvH2D_Map.end());
//Empty_MnvH2D_Data_Map.erase (Empty_MnvH2D_Data_Map.begin(),Empty_MnvH2D_Data_Map.end());
//Full_ObjArray.SetOwner(kTRUE);
//Empty_ObjArray.SetOwner(kTRUE);
//Full_ObjArray.Delete();
//Empty_ObjArray.Delete();

return;

}
///////////////////////////////////////////////////////////////////////////////
void Draw2DStackPlots_Panel_Full_Empty_Extracted(TFile *TFileinput,
                   char *histoName_MC,
                   char *Charstacktype,
                   char *hist_DataName,
                   char *xaxis, char *yaxis,char *unitsX,char *unitsY, char *Plot_title,  std::vector<double> YMultipliers, std::vector<double> XMultipliers,
                   bool do_bin_width_norm,
                   MnvPlotter *mnvPlotter, TCanvas *can,  char *pdf, double XprotextSize, double YprotextSize, std::vector<int> fillColors){

std::string pdf_string(pdf);
char pdf_char[1024];
sprintf(pdf_char, "%s.pdf" , pdf);
char ZaxisTitle[1024];
char Title[1024];
//cchar Title[1024];
char HIST_NAME[1024];
std::cout<< "Starting to make:Full_ObjArray "<<std::endl;
sprintf(HIST_NAME, "%s_CombinedFull_%s",histoName_MC, Charstacktype );
PlotUtils::HistFolio<PlotUtils::MnvH2D> StackFull(PlotUtils::LoadHistFolioFromFile<PlotUtils::MnvH2D>(*(TFileinput), std::string(HIST_NAME)),"FullStack");
auto Full_ObjArray = StackFull.GetHistArray();
sprintf(HIST_NAME, "%s_FullCombined",hist_DataName);
MnvH2D *h_Full_Combined_Data = Get2DHist(*TFileinput,  HIST_NAME);


////
//Scale
//

//MnvH2D *h_Full_Combined_Dataclone = (PlotUtils::cMnvH2D*)h_Full_Combined_Data->Clone("h_Full_Combined_DataClone");
//MnvH2D *h_Empty_Combined_Dataclone = (PlotUtils::MnvH2D*)h_Empty_Combined_Data->Clone("h_Empty_Combined_DataClone");


//////////////////////////////////////////////////
///  F
/////////////////////////////////////////////////
//const TObjArray  *mcHists_Breakdown_Full =  &Full_ObjArray ;


sprintf(ZaxisTitle,"Event /  %s ",unitsX );
sprintf(Title, "%s [F][ProjX]" , Plot_title);

std::cout<<"plot: F::PlotDataStackedMC2D_ProjX"<<std::endl;

PlotDataStackedMC2D_ProjX(h_Full_Combined_Data, Full_ObjArray,
                        fillColors,
                        pdf, Title ,  xaxis, yaxis, ZaxisTitle,
                         99, false,  true, YMultipliers,
                         do_bin_width_norm, XprotextSize);

sprintf(ZaxisTitle,"Event /  %s ",unitsY );
sprintf(Title, "%s [F][ProjY]" , Plot_title);
std::cout<<"plot: F::PlotDataStackedMC2D_ProjY"<<std::endl;

PlotDataStackedMC2D_ProjY(h_Full_Combined_Data,
  Full_ObjArray,
  fillColors,
  pdf, Title ,  yaxis, xaxis, ZaxisTitle,
  99, false,  true, YMultipliers,
  do_bin_width_norm, YprotextSize);


//////////////////////////////////////////////////
///  E
/////////////////////////////////////////////////
std::cout<< "Starting to make:Full_ObjArray "<<std::endl;
sprintf(HIST_NAME, "%s_CombinedEmpty_%s",histoName_MC, Charstacktype );
PlotUtils::HistFolio<PlotUtils::MnvH2D> StackEmpty(PlotUtils::LoadHistFolioFromFile<PlotUtils::MnvH2D>(*(TFileinput), std::string(HIST_NAME)),"EmptyStack");
auto Empty_ObjArray = StackEmpty.GetHistArray();
sprintf(HIST_NAME, "%s_EmptyCombined",hist_DataName);
MnvH2D *h_Empty_Combined_Data = Get2DHist(*TFileinput,  HIST_NAME);

//const TObjArray  *mcHists_Breakdown_Empty =  &Empty_ObjArray ;
//mcHists_Breakdown =  &Empty_ObjArray ;
sprintf(ZaxisTitle,"Event /  %s ",unitsY );
sprintf(Title, "%s [Empty][ProjY]" , Plot_title);
std::cout<<"plot: Empty::PlotDataStackedMC2D_ProjY"<<std::endl;
PlotDataStackedMC2D_ProjY(h_Empty_Combined_Data,
                          Empty_ObjArray,
                        fillColors,
                        pdf, Title ,  yaxis, xaxis, ZaxisTitle,
                         99, false,  true, YMultipliers,
                         do_bin_width_norm, YprotextSize);


sprintf(ZaxisTitle,"Event /  %s ",unitsX );
sprintf(Title, "%s [Empty][ProjX]" , Plot_title);
std::cout<<"plot: Empty::PlotDataStackedMC2D_ProjX"<<std::endl;
PlotDataStackedMC2D_ProjX(h_Empty_Combined_Data, Empty_ObjArray,
                       fillColors,
                       pdf, Title ,  xaxis, yaxis, ZaxisTitle,
                        99, false,  true, YMultipliers,
                        do_bin_width_norm, XprotextSize);
//////////////////////////////////////////////////////////////
/// F - E
/////////////////////////////////////////////////
std::cout<<"plot: F-E::PlotDataStackedMC2D_ProjX"<<std::endl;
h_Full_Combined_Data->Add(h_Empty_Combined_Data,-1);
SubractSecond_FromFirst_MnvH2D_Arrays(Full_ObjArray,  Empty_ObjArray);
SubractSecond_FromFirst_MnvH2D_Arrays(Full_ObjArray,  Empty_ObjArray);
sprintf(Title, "%s [F-E][ProjY]" , Plot_title);
sprintf(ZaxisTitle,"Event /  %s ",unitsY );
PlotDataStackedMC2D_ProjY(h_Full_Combined_Data,
                          Full_ObjArray,
                        fillColors,
                        pdf, Title ,  yaxis, xaxis, ZaxisTitle,
                         99, false,  true, YMultipliers,
                         do_bin_width_norm, YprotextSize);



sprintf(Title, "%s [F-E][ProjX]" , Plot_title);
sprintf(ZaxisTitle,"Event /  %s ",unitsX );
PlotDataStackedMC2D_ProjX(h_Full_Combined_Data, Full_ObjArray,
                       fillColors,
                       pdf, Title ,  xaxis, yaxis, ZaxisTitle,
                        99, false,  true, YMultipliers,
                        do_bin_width_norm, XprotextSize);






return;

}

////////////////////////////////////////////////////////
void Draw2DStackPlots_Panel_Full_Empty(ME_playlist_RootPathMAP Full_Map_RootMap, ME_playlist_RootPathMAP Full_Data_Map_RootMap,
  ME_playlist_RootPathMAP Empty_Map_RootMap, ME_playlist_RootPathMAP Empty_Data_Map_RootMap,
  double Full_MC_Full_Data,
  double Empty_MC_Full_Data,
  double Empty_Data_Full_Data,
  char *histoName_MC,
  char *Charstacktype,
  std::vector<std::string> StackNames,
  char *hist_DataName,
  char *xaxis, char *yaxis,char *unitsX,char *unitsY, char *Plot_title,  std::vector<double> YMultipliers, std::vector<double> XMultipliers,
  bool do_bin_width_norm,
  MnvPlotter *mnvPlotter, TCanvas *can,  char *pdf, double XprotextSize, double YprotextSize, std::vector<int> fillColors){

    //////
    // Having memory issue when doing stack , think it's because of leaving The TFiles open, going to try this method
    /////

ME_playlist_TFileMAP Full_Map = MakeTFileMap(Full_Map_RootMap);
ME_playlist_TFileMAP Empty_Map = MakeTFileMap(Empty_Map_RootMap);


ME_playlist_TFileMAP Full_Map_DATA = MakeTFileMap(Full_Data_Map_RootMap);
ME_playlist_TFileMAP Empty_Map_DATA = MakeTFileMap(Empty_Data_Map_RootMap);


Draw2DStackPlots_Panel_Full_Empty( Full_Map, Full_Map_DATA,  Empty_Map,  Empty_Map_DATA,
   Full_MC_Full_Data,
   Empty_MC_Full_Data,
   Empty_Data_Full_Data,
   histoName_MC,
   Charstacktype,
   StackNames,
   hist_DataName,
  xaxis, yaxis,unitsX,unitsY, Plot_title, YMultipliers, XMultipliers, do_bin_width_norm,
  mnvPlotter, can, pdf, XprotextSize, YprotextSize,  fillColors);

  ME_playlist_TFileMAP::iterator MC_Map;
  ME_playlist_TFileMAP::iterator Data_Map;
  for( MC_Map = Full_Map.begin(), Data_Map=Full_Map_DATA.begin() ; MC_Map != Full_Map.end();  MC_Map++,Data_Map++){

    MC_Map->second->Close();
    Data_Map->second->Close();
    delete Data_Map->second;
    delete MC_Map->second;
  }



  for( MC_Map = Empty_Map.begin(), Data_Map=Empty_Map_DATA.begin() ; MC_Map != Empty_Map.end();  MC_Map++,Data_Map++){

    MC_Map->second->Close();
    Data_Map->second->Close();
    delete Data_Map->second;
    delete MC_Map->second;
  }

  Full_Map.clear();
  Empty_Map.clear();
  Full_Map_DATA.clear();
  Empty_Map_DATA.clear();

  return;


}

void Draw2DPlots_Panel(ME_playlist_RootPathMAP Full_Map_RootMap, ME_playlist_RootPathMAP Full_Data_Map_RootMap,
  ME_playlist_RootPathMAP Empty_Map_RootMap, ME_playlist_RootPathMAP Empty_Data_Map_RootMap,
  double Full_MC_Full_Data,
  double Empty_MC_Full_Data,
  double Empty_Data_Full_Data,
  char *hist_MCName,
  char *hist_DataName,
  char *xaxis, char *yaxis,char *unitsX,char *unitsY, char *Plot_title,  std::vector<double> YMultipliers, std::vector<double> XMultipliers,
  bool do_bin_width_norm ,bool statPlusSysDATA , bool statPlusSysMC ,
  MnvPlotter *mnvPlotter, TCanvas *can,  char *pdf, double XprotextSize, double YprotextSize, double FractionalErrorMax){



    ME_playlist_TFileMAP Full_Map = MakeTFileMap(Full_Map_RootMap);
    ME_playlist_TFileMAP Empty_Map = MakeTFileMap(Empty_Map_RootMap);


    ME_playlist_TFileMAP Full_Map_DATA = MakeTFileMap(Full_Data_Map_RootMap);
    ME_playlist_TFileMAP Empty_Map_DATA = MakeTFileMap(Empty_Data_Map_RootMap);


    Draw2DPlots_Panel( Full_Map,  Full_Map_DATA,
      Empty_Map,  Empty_Map_DATA,
      Full_MC_Full_Data,
      Empty_MC_Full_Data,
      Empty_Data_Full_Data,
      hist_MCName,
      hist_DataName,
      xaxis, yaxis,unitsX,unitsY, Plot_title,   YMultipliers,  XMultipliers,
       do_bin_width_norm , statPlusSysDATA ,  statPlusSysMC ,
      mnvPlotter, can,  pdf,  XprotextSize,  YprotextSize,  FractionalErrorMax);

      ME_playlist_TFileMAP::iterator MC_Map;
      ME_playlist_TFileMAP::iterator Data_Map;
      for( MC_Map = Full_Map.begin(), Data_Map=Full_Map_DATA.begin() ; MC_Map != Full_Map.end();  MC_Map++,Data_Map++){

        MC_Map->second->Close();
        Data_Map->second->Close();
        delete Data_Map->second;
        delete MC_Map->second;
      }



      for( MC_Map = Empty_Map.begin(), Data_Map=Empty_Map_DATA.begin() ; MC_Map != Empty_Map.end();  MC_Map++,Data_Map++){

        MC_Map->second->Close();
        Data_Map->second->Close();
        delete Data_Map->second;
        delete MC_Map->second;
      }

      Full_Map.clear();
      Empty_Map.clear();
      Full_Map_DATA.clear();
      Empty_Map_DATA.clear();

      return;




}



void DrawCombined_Resolution_withGaussianFit(ME_playlist_RootPathMAP Full_Map_RootMap,
  ME_playlist_RootPathMAP Empty_Map_RootMap,double Full_MC_Full_Data,
double Empty_MC_Full_Data, char *hist_MCName, char *histotitle,  std::string xaxislabel, std::string yaxislabel,
bool Setgrid, bool PrintErrors , bool PrintallErrorGroups, bool do_bin_width_norm ,
MnvPlotter *mnvPlotter, TCanvas *can, std::string pdf_name){

  ME_playlist_TFileMAP Full_Map = MakeTFileMap(Full_Map_RootMap);
  ME_playlist_TFileMAP Empty_Map = MakeTFileMap(Empty_Map_RootMap);

  Playlist_MnvH1D_Map Full_MnvH1D_MC_Map = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(Full_Map, hist_MCName );
  Playlist_MnvH1D_Map Empty_MnvH1D_MC_Map = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(Empty_Map, hist_MCName );

  std::cout<<"Combine MC Full "<< std::endl;
  auto h_Full_Combined = Combine_Hists_fromMAP(Full_MnvH1D_MC_Map , kME1F ,"h_Full_Combined");
  h_Full_Combined->Scale(Full_MC_Full_Data);

  std::cout<<"Combine MC Empty "<< std::endl;
  auto h_Empty_Combined = Combine_Hists_fromMAP(Empty_MnvH1D_MC_Map , kME1M ,"h_Empty_Combined");
  h_Empty_Combined->Scale(Empty_MC_Full_Data);
  char Plot_title[1024];


  if(do_bin_width_norm==true){
    h_Full_Combined->Scale(1,"width");
    h_Empty_Combined->Scale(1,"width");
  }

  sprintf(Plot_title,  "%s [Full]", histotitle);

  DrawCVAndError_FromHIST_withFit(h_Full_Combined, Plot_title , xaxislabel, yaxislabel,
          pdf_name,  Setgrid,  PrintErrors , PrintallErrorGroups );

 sprintf(Plot_title,  "%s [Empty]", histotitle);
 DrawCVAndError_FromHIST_withFit(h_Empty_Combined, Plot_title , xaxislabel, yaxislabel,
   pdf_name,  Setgrid,  PrintErrors , PrintallErrorGroups );

   h_Full_Combined->Add(h_Empty_Combined,-1);

   sprintf(Plot_title,  "%s [F-E]", histotitle);

   DrawCVAndError_FromHIST_withFit(h_Full_Combined, Plot_title , xaxislabel, yaxislabel,
     pdf_name,  Setgrid,  PrintErrors , PrintallErrorGroups );



}


void Draw_3Resolution_CryoVertex_FULL_EMPTY_RecoBranch(ME_playlist_RootPathMAP Full_Map_RootMap,
                                                      ME_playlist_RootPathMAP Empty_Map_RootMap,
                                                      double Full_MC_Full_Data,
                                                      double Empty_MC_Full_Data,
   const char *histoName_region1, const char *histoName_region2, const char *histoName_region3,
  int logScale, MnvPlotter *plot, TCanvas *can, const char *pdf, char *CutsApplied,
   bool doBinwidth, bool isFractional , bool isAreaNormalized, double Ymax, CryoVertex CryoVertex_type  ){

      char Title_His[1024];
      bool isfull = true;
      bool isempty = false;

      std::cout<<"Inside:Draw_3Resolution_CryoVertex_FULL_EMPTY_RecoBranch"<<std::endl;

      ME_playlist_TFileMAP Full_Map = MakeTFileMap(Full_Map_RootMap);
      ME_playlist_TFileMAP Empty_Map = MakeTFileMap(Empty_Map_RootMap);

      Playlist_MnvH1D_Map Full_MnvH1D_MC_Map_region1 = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(Full_Map, histoName_region1 );
      Playlist_MnvH1D_Map Empty_MnvH1D_MC_Map_region1 = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(Empty_Map, histoName_region1 );

      std::cout<<"Combine MC Full region1"<< std::endl;
      auto hist_region1_Full = Combine_Hists_fromMAP(Full_MnvH1D_MC_Map_region1 , kME1F ,"h_Full_region1_Combined");
      hist_region1_Full->Scale(Full_MC_Full_Data);

      std::cout<<"Combine MC Empty region1 "<< std::endl;
      auto hist_region1_EMPTY = Combine_Hists_fromMAP(Empty_MnvH1D_MC_Map_region1 , kME1M ,"h_Empty_region1_Combined");
      hist_region1_EMPTY->Scale(Empty_MC_Full_Data);

      Playlist_MnvH1D_Map Full_MnvH1D_MC_Map_region2 = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(Full_Map, histoName_region2 );
      Playlist_MnvH1D_Map Empty_MnvH1D_MC_Map_region2 = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(Empty_Map, histoName_region2 );

      std::cout<<"Combine MC Full region2"<< std::endl;
      auto hist_region2_Full = Combine_Hists_fromMAP(Full_MnvH1D_MC_Map_region2 , kME1F ,"h_Full_region2_Combined");
      hist_region2_Full->Scale(Full_MC_Full_Data);

      std::cout<<"Combine MC Empty region1 "<< std::endl;
      auto hist_region2_EMPTY = Combine_Hists_fromMAP(Empty_MnvH1D_MC_Map_region2 , kME1M ,"h_Empty_region2_Combined");
      hist_region2_EMPTY->Scale(Empty_MC_Full_Data);

      //double Ymax1 = hist_region2_Full->GetMaximum();

      Playlist_MnvH1D_Map Full_MnvH1D_MC_Map_region3 = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(Full_Map, histoName_region3 );
      Playlist_MnvH1D_Map Empty_MnvH1D_MC_Map_region3 = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(Empty_Map, histoName_region3 );

      std::cout<<"Combine MC Full region3"<< std::endl;
      auto hist_region3_Full = Combine_Hists_fromMAP(Full_MnvH1D_MC_Map_region3 , kME1F ,"h_Full_region3_Combined");
      hist_region3_Full->Scale(Full_MC_Full_Data);

      std::cout<<"Combine MC Empty region3 "<< std::endl;
      auto hist_region3_EMPTY = Combine_Hists_fromMAP(Empty_MnvH1D_MC_Map_region3 , kME1M ,"h_Empty_region3_Combined");
      hist_region3_EMPTY->Scale(Empty_MC_Full_Data);



    //  hist_region1_Full_EMPTY->Add(hist_region1_EMPTY,-1);
    //  hist_region2_Full_EMPTY->Add(hist_region2_EMPTY,-1);
    //  hist_region3_Full_EMPTY->Add(hist_region3_EMPTY,-1);


      std::string pdf_string(pdf);

      std::string title_type = GetVertexCryoTitleName(CryoVertex_type);

      std::string Xaxis_title;
      if(isFractional==false){Xaxis_title =  "Absolute " + GetVertexCryoVarAxisTitleNoUnits(CryoVertex_type) + " residual (true - reco [mm])" ;}
      else{Xaxis_title = "Fractional " + GetVertexCryoVarAxisTitleNoUnits(CryoVertex_type) + " residual (true - reco) / true";}

      char title_type_char[title_type.length()+1];
      strcpy( title_type_char, title_type.c_str());


      bool Setgrid = true;

      sprintf(Title_His, "%s [%s][F]", title_type_char, CutsApplied);
      DrawCVAndError_3tankRegionsHIST_withRMS(hist_region1_Full, hist_region2_Full, hist_region3_Full,
         Title_His ,Xaxis_title, "NEvents", "mm", pdf_string, Setgrid, doBinwidth, isFractional , isAreaNormalized , Ymax);

      sprintf(Title_His, "%s [%s][E]", title_type_char , CutsApplied);
      DrawCVAndError_3tankRegionsHIST_withRMS(hist_region1_EMPTY, hist_region2_EMPTY, hist_region3_EMPTY,
         Title_His ,Xaxis_title, "NEvents", "mm", pdf_string, Setgrid, doBinwidth, isFractional , isAreaNormalized, Ymax );

         hist_region1_Full->Add(hist_region1_EMPTY,-1);
         hist_region2_Full->Add(hist_region2_EMPTY,-1);
         hist_region3_Full->Add(hist_region3_EMPTY,-1);


      sprintf(Title_His, "%s [%s][F-E]", title_type_char, CutsApplied);
      DrawCVAndError_3tankRegionsHIST_withRMS(hist_region1_Full, hist_region2_Full, hist_region3_Full,
         Title_His ,Xaxis_title, "NEvents", "mm", pdf_string, Setgrid, doBinwidth, isFractional , isAreaNormalized, Ymax );



}//endl;

/*
void Draw_Efficiency_FidiucialCut_FULL_EMPTY_TRUTH_Combined(
                                                    ME_playlist_TFileMAP FULL_playlist_nom, ME_playlist_TFileMAP FULL_playlist_TRUTHDEM,
                                                    ME_playlist_TFileMAP EMPTY_playlist_nom, ME_playlist_TFileMAP EMPTY_playlist_TRUTHDEM,
                                                    ME_playlist_TFileMAP playlist_FULL_Data, ME_playlist_TFileMAP Elaylist_EMPTY_Data,
                                                    double Full_MC_Full_Data,
                                                    double Empty_MC_Full_Data,
                                                    double Empty_Data_Full_Data,

                                                   const char *histoName_MC, const char *histoName_Data,
                                                   const char* title, std::string Xaxis_title, MnvPlotter *plot, bool doBinwidth,
                                                   TCanvas *can,  char *pdf, bool PrintErrors, bool PrintallErrorBands,
                                                   std::vector<double> Bins , double EffMax, double EffMin )
{
 char histoName_TRUE[1024];
 char histoName_TRUE_RECO[1024];
 char histoName_RECO_TRUE_RECO[1024];
 char histoName_RECO_helium[1024];
 char histoName_RECO_nonhelium[1024];
 char histoName_TRUE_helium[1024];
 char histoName_TRUE_nonhelium[1024];
 char Title_His[1024];
 char pdf_char[1024];
 sprintf(pdf_char, "%s.pdf", pdf);

std::string Xaxis_title_RECO = "[RECO] " + Xaxis_title;
std::string Xaxis_title_TRUE = "[TRUE] " + Xaxis_title;

 sprintf(histoName_TRUE, "%s_TRUE", histoName_MC);
 sprintf(histoName_TRUE_RECO, "%s_TRUE_RECO", histoName_MC);
 sprintf(histoName_RECO_TRUE_RECO, "%s_RECO_TRUE_RECO", histoName_MC);

 sprintf(histoName_TRUE_helium, "%s_helium", histoName_MC);
 sprintf(histoName_TRUE_nonhelium, "%s_nonhelium", histoName_MC);

 sprintf(histoName_RECO_helium, "%s_RECO_helium", histoName_MC);
 sprintf(histoName_RECO_nonhelium, "%s_RECO_nonhelium", histoName_MC);

 bool isfull=true;
 bool isempty=false;


 Playlist_MnvH1D_Map hist_TRUE_FULL_Map = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FULL_playlist_TRUTHDEM, histoName_TRUE );
 MnvH1D* hist_TRUE_FULL = Combine_Hists_fromMAP(NomFull_Map , kME1F ,"hist_TRUE_FULL");

 Playlist_MnvH1D_Map hist_TRUE_RECO_FULL_Map = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FULL_playlist_nom, histoName_TRUE );
 MnvH1D* hist_TRUE_RECO_FULL = Combine_Hists_fromMAP(NomFull_Map , kME1F ,"hist_TRUE_RECO_FULL");


 MnvH1D* hist_RECO_FULL      = Get1DHist(*FULL_playlist_nom.TFILE_PLAYLIST, histoName_MC, isfull);

 MnvH1D* hist_TRUE_EMPTY      = Get1DHist(*EMPTY_playlist_TRUTHDEM.TFILE_PLAYLIST, histoName_TRUE, isempty);
 MnvH1D* hist_TRUE_RECO_EMPTY = Get1DHist(*EMPTY_playlist_nom.TFILE_PLAYLIST, histoName_TRUE_RECO, isempty);

 MnvH1D* Acceptance_EMPTY     = Get1DHist(*EMPTY_playlist_nom.TFILE_PLAYLIST, histoName_RECO_TRUE_RECO, isempty);
 MnvH1D *Acceptance_EMPTY_clone        = (PlotUtils::MnvH1D*)Acceptance_EMPTY->Clone("Acceptance_EMPTY_clone");
 MnvH1D* Acceptance_EMPTY_DOM      = Get1DHist(*EMPTY_playlist_TRUTHDEM.TFILE_PLAYLIST, histoName_TRUE, isempty);
 MnvH1D *Acceptance_EMPTY_DOM_clone        = (PlotUtils::MnvH1D*)Acceptance_EMPTY_DOM->Clone("Acceptance_EMPTY_DOM_clone");

 Acceptance_EMPTY_DOM->AddMissingErrorBandsAndFillWithCV(*Acceptance_EMPTY);
 Acceptance_EMPTY_DOM_clone->AddMissingErrorBandsAndFillWithCV(*Acceptance_EMPTY);


 MnvH1D* hist_RECO_EMPTY      = Get1DHist(*EMPTY_playlist_nom.TFILE_PLAYLIST, histoName_MC, isempty);

 MnvH1D* hist_RECO_FULL_Total = Get1DHist(*FULL_playlist_nom.TFILE_PLAYLIST, histoName_MC, isfull);
 MnvH1D* hist_RECO_EMPTY_Total = Get1DHist(*EMPTY_playlist_nom.TFILE_PLAYLIST, histoName_MC, isempty);

 MnvH1D* hist_RECO_FULL_Total_TRUE = Get1DHist(*FULL_playlist_nom.TFILE_PLAYLIST, histoName_TRUE, isfull);
 MnvH1D* hist_TRUE_FULL_helium     = Get1DHist(*FULL_playlist_nom.TFILE_PLAYLIST, histoName_TRUE_helium, isfull);
 MnvH1D* hist_TRUE_FULL_nonhelium  =  Get1DHist(*FULL_playlist_nom.TFILE_PLAYLIST, histoName_TRUE_nonhelium, isfull);

 MnvH1D* hist_RECO_FULL_helium =     Get1DHist(*FULL_playlist_nom.TFILE_PLAYLIST, histoName_RECO_helium, isfull);
 MnvH1D* hist_RECO_FULL_nonhelium =  Get1DHist(*FULL_playlist_nom.TFILE_PLAYLIST, histoName_RECO_nonhelium, isfull);

 MnvH1D* hist_RECO_EMPTY_Total_TRUE = Get1DHist(*EMPTY_playlist_nom.TFILE_PLAYLIST, histoName_TRUE, isempty);
 MnvH1D* hist_TRUE_EMPTY_helium =     Get1DHist(*EMPTY_playlist_nom.TFILE_PLAYLIST, histoName_TRUE_helium, isempty);
 MnvH1D* hist_TRUE_EMPTY_nonhelium =  Get1DHist(*EMPTY_playlist_nom.TFILE_PLAYLIST, histoName_TRUE_nonhelium, isempty);

 MnvH1D* hist_RECO_EMPTY_helium =     Get1DHist(*EMPTY_playlist_nom.TFILE_PLAYLIST, histoName_RECO_helium, isempty);
 MnvH1D* hist_RECO_EMPTY_nonhelium =  Get1DHist(*EMPTY_playlist_nom.TFILE_PLAYLIST, histoName_RECO_nonhelium, isempty);

 MnvH1D *Purity_Dom_Full_TRUEbins = (PlotUtils::MnvH1D*)hist_RECO_FULL_Total_TRUE->Clone("Purity_Dom_Full_TRUEbins");
 MnvH1D *Purity_Dom_Full_EMPTY_TRUEbins = (PlotUtils::MnvH1D*)hist_RECO_FULL_Total_TRUE->Clone("Purity_Dom_Full_EMPTY_TRUEbins");

 MnvH1D *Purity_Dom_Empty_TRUEBins = (PlotUtils::MnvH1D*)hist_RECO_EMPTY_Total_TRUE->Clone("Purity_Dom_Empty_TRUEBins");
 MnvH1D *Purity_Dom_Empty_clone_TRUEbins = (PlotUtils::MnvH1D*)hist_RECO_EMPTY_Total_TRUE->Clone("Purity_Dom_Empty_clone_TRUEbins");


 MnvH1D *Purity_Dom_Full_RECObins        = (PlotUtils::MnvH1D*)hist_RECO_FULL->Clone("Purity_Dom_Full_RECObins");
 MnvH1D *Purity_Dom_Full_EMPTY_RECObins  = (PlotUtils::MnvH1D*)hist_RECO_FULL->Clone("Purity_Dom_Full_EMPTY_RECObins");
 MnvH1D *Purity_Dom_Empty_RECOBins       = (PlotUtils::MnvH1D*)hist_RECO_EMPTY->Clone("Purity_Dom_Empty_RECOBins");
 MnvH1D *Purity_Dom_Empty_clone_RECObins = (PlotUtils::MnvH1D*)hist_RECO_EMPTY->Clone("Purity_Dom_Empty_clone_RECObins");

 hist_RECO_FULL_Total->Scale(Scale_FULL_MC_data);
 hist_RECO_FULL_Total_TRUE->Scale(Scale_FULL_MC_data);
 hist_TRUE_FULL_helium->Scale(Scale_FULL_MC_data);
 hist_TRUE_FULL_nonhelium->Scale(Scale_FULL_MC_data);

 hist_RECO_FULL_helium->Scale(Scale_FULL_MC_data);
 hist_RECO_FULL_nonhelium->Scale(Scale_FULL_MC_data);


 Purity_Dom_Empty_TRUEBins->Scale(Scale_MC);
 Purity_Dom_Empty_clone_TRUEbins->Scale(Scale_MC);

 Purity_Dom_Empty_RECOBins->Scale(Scale_Empty_MC_data);
 Purity_Dom_Empty_clone_RECObins->Scale(Scale_Empty_MC_data);

 Acceptance_EMPTY->Scale(Scale_MC);
 Acceptance_EMPTY_clone->Scale(Scale_MC);

 Acceptance_EMPTY_DOM->Scale(Scale_MC);
 Acceptance_EMPTY_DOM_clone->Scale(Scale_MC);

 hist_RECO_EMPTY_Total     ->Scale(Scale_Empty_MC_data);
 hist_RECO_EMPTY_Total_TRUE->Scale(Scale_Empty_MC_data);
 hist_RECO_EMPTY_helium    ->Scale(Scale_Empty_MC_data);
 hist_RECO_EMPTY_nonhelium ->Scale(Scale_Empty_MC_data);

 hist_TRUE_EMPTY_helium    ->Scale(Scale_Empty_MC_data);
 hist_TRUE_EMPTY_nonhelium ->Scale(Scale_Empty_MC_data);

 MnvH1D* Purity_Full_RECOBins        = (PlotUtils::MnvH1D*)hist_RECO_FULL_helium->Clone("Purity_Full_RECOBins");
 MnvH1D* Purity_Full_EMPTY_RECOBins  = (PlotUtils::MnvH1D*)hist_RECO_FULL_helium->Clone("Purity_Full_EMPTY_RECOBins");

 MnvH1D* Purity_EMPTY_RECOBins       = (PlotUtils::MnvH1D*)hist_RECO_EMPTY_helium ->Clone("Purity_EMPTY_RECOBins");
 MnvH1D* Purity_EMPTY_RECOBins_clone = (PlotUtils::MnvH1D*)hist_RECO_EMPTY_helium ->Clone("Purity_EMPTY_RECOBins_clone");

 hist_TRUE_FULL->AddMissingErrorBandsAndFillWithCV(*hist_TRUE_RECO_FULL);
 hist_TRUE_EMPTY->AddMissingErrorBandsAndFillWithCV(*hist_TRUE_RECO_EMPTY);

 MnvH1D* hist_TRUE_FULL_clone = Get1DHist(*FULL_playlist_TRUTHDEM.TFILE_PLAYLIST, histoName_TRUE, isfull);
 MnvH1D* hist_TRUE_RECO_FULL_clone = Get1DHist(*FULL_playlist_nom.TFILE_PLAYLIST, histoName_TRUE_RECO, isfull);
 MnvH1D* hist_RECO_FULL_clone = Get1DHist(*FULL_playlist_nom.TFILE_PLAYLIST, histoName_MC, isfull);

 hist_TRUE_FULL_clone->AddMissingErrorBandsAndFillWithCV(*hist_TRUE_RECO_FULL_clone);

 MnvH1D* hist_TRUE_EMPTY_clone = Get1DHist(*EMPTY_playlist_TRUTHDEM.TFILE_PLAYLIST, histoName_TRUE, isempty);
 MnvH1D* hist_TRUE_RECO_EMPTY_clone = Get1DHist(*EMPTY_playlist_nom.TFILE_PLAYLIST, histoName_TRUE_RECO, isempty);
 MnvH1D* hist_RECO_EMPTY_clone = Get1DHist(*EMPTY_playlist_nom.TFILE_PLAYLIST, histoName_MC, isempty);

 hist_TRUE_EMPTY_clone->AddMissingErrorBandsAndFillWithCV(*hist_TRUE_RECO_EMPTY_clone);

 MnvH1D* hist_FULL_data = Get1DHist(*playlist_FULL_Data.TFILE_PLAYLIST, histoName_Data, isfull);
 MnvH1D* hist_EMPTY_data = Get1DHist(*playlist_EMPTY_Data.TFILE_PLAYLIST, histoName_Data, isempty);

 MnvH1D* hist_FULL_data_clone = Get1DHist(*playlist_FULL_Data.TFILE_PLAYLIST, histoName_Data, isfull);
 MnvH1D* hist_EMPTY_data_clone = Get1DHist(*playlist_EMPTY_Data.TFILE_PLAYLIST, histoName_Data, isempty);

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

 double binwidth_title = hist_FULL_data -> GetBinWidth(4);
 char ytitle[1024];
 if(doBinwidth==true){
   sprintf(ytitle, "Number of Events / %.2f [mm]", binwidth_title); //
 }
 else{
   sprintf(ytitle, "Number of Events"); //
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
 double Ymax_reco = 1.10 * hist_RECO_FULL->GetMaximum();
 sprintf(Title_His, "%s Event Rate [F(%s)]",title, playlistFull_char);
 DrawCVAndError_FromHistPointer(hist_RECO_FULL , hist_FULL_data, Title_His ,Xaxis_title_RECO, Yaxis_title,
   pdf_string, doBinwidth, false , PrintErrors, Ymax_reco, PrintallErrorBands );

 hist_RECO_EMPTY->Scale(Scale_Empty_MC_data);

 sprintf(Title_His, "%s Event Rate [E(%s)]",title, playlistEmpty_char);
 DrawCVAndError_FromHistPointer(hist_RECO_EMPTY , hist_EMPTY_data, Title_His ,Xaxis_title_RECO, Yaxis_title,
   pdf_string, doBinwidth, false , PrintErrors, Ymax_reco, PrintallErrorBands );

 sprintf(Title_His, "%s Event Rate [F(%s)- E(%s)]",title, playlistFull_char, playlistEmpty_char);
 DrawCVAndError_FromHistPointer(hist_RECO_FULL_clone, hist_FULL_data_clone, Title_His ,Xaxis_title_RECO, Yaxis_title,
   pdf_string, doBinwidth, false , PrintErrors, Ymax_reco, PrintallErrorBands );
///////////////////////////////////////////////////////////////////////////////
 sprintf(Title_His, "%s Event Rate [F(%s)]",title, playlistFull_char);
 double Ymax_reco_helium = hist_RECO_FULL_Total_TRUE->GetMaximum()*1.25;

 DrawCVAndError_From6HIST_RECO_vs_TRUE(hist_RECO_FULL_Total_TRUE, hist_TRUE_FULL_helium , hist_TRUE_FULL_nonhelium ,
                         hist_RECO_FULL, hist_RECO_FULL_helium, hist_RECO_FULL_nonhelium,
  Title_His ,Xaxis_title_TRUE, Yaxis_title,
  pdf_string, false , PrintallErrorBands , false , doBinwidth, Ymax_reco_helium );

 double Ymax_reco_Denominator = hist_TRUE_FULL->GetMaximum() * 1.75;

 sprintf(Title_His, "%s Numerator and Denominator [F(%s)]", title, playlistFull_char);
 DrawCVAndError_From2HIST(hist_TRUE_FULL, "Denominator" ,hist_TRUE_RECO_FULL, "Numerator",  Title_His , Xaxis_title_TRUE, "Nevents",
 pdf_string, true,  PrintallErrorBands , false , doBinwidth, Ymax_reco_Denominator, true );
////////////////////
 sprintf(Title_His, "%s Event Rate [E(%s)]",title, playlistEmpty_char);
 DrawCVAndError_From6HIST_RECO_vs_TRUE(hist_RECO_EMPTY_Total_TRUE, hist_TRUE_EMPTY_helium , hist_TRUE_EMPTY_nonhelium,
                                       hist_RECO_EMPTY, hist_RECO_EMPTY_helium, hist_RECO_EMPTY_nonhelium,
                                       Title_His , Xaxis_title,Yaxis_title,
 pdf_string, false , PrintallErrorBands , false , doBinwidth, Ymax_reco_helium );

 sprintf(Title_His, " %s Numerator and Denominator [E(%s)]", title, playlistEmpty_char);
 DrawCVAndError_From2HIST(hist_TRUE_EMPTY, "Denominator" ,hist_TRUE_RECO_EMPTY, "Numerator",  Title_His , Xaxis_title_RECO, "Nevents",
 pdf_string, true,  PrintallErrorBands , false , doBinwidth, Ymax_reco_Denominator, true );
 //////////////////////////
 hist_RECO_FULL_Total_TRUE->Add(hist_RECO_EMPTY_Total_TRUE,-1.0);
 hist_TRUE_FULL_helium->Add(hist_TRUE_EMPTY_helium,-1.0);
 hist_TRUE_FULL_nonhelium->Add(hist_TRUE_EMPTY_nonhelium,-1.0);

 hist_RECO_FULL_helium->Add(hist_RECO_EMPTY_helium,-1.0);
 hist_RECO_FULL_nonhelium->Add(hist_RECO_EMPTY_nonhelium,-1.0);
 MnvH1D* Background = (PlotUtils::MnvH1D*)hist_RECO_FULL_nonhelium->Clone("Background");

 sprintf(Title_His, "%s Event Rate [F(%s)- E(%s)]",title, playlistFull_char, playlistEmpty_char);
DrawCVAndError_From6HIST_RECO_vs_TRUE(hist_RECO_FULL_Total_TRUE, hist_TRUE_FULL_helium, hist_TRUE_FULL_nonhelium,
                          hist_RECO_FULL_clone, hist_RECO_FULL_helium, hist_RECO_FULL_nonhelium,
   Title_His ,Xaxis_title, Yaxis_title,
   pdf_string, false , PrintallErrorBands , false , doBinwidth, Ymax_reco_helium );

 sprintf(Title_His, "%s Numerator and Denominator [F(%s)- E(%s)]",title, playlistFull_char, playlistEmpty_char);
 DrawCVAndError_From2HIST(hist_TRUE_FULL_clone, "Denominator" ,hist_TRUE_RECO_FULL_clone, "Numerator",  Title_His , Xaxis_title_TRUE, "Nevents",
 pdf_string, true,  PrintallErrorBands , false , doBinwidth, Ymax_reco_Denominator, true );
  ///////////////////////////////
 hist_TRUE_RECO_FULL->Divide(hist_TRUE_RECO_FULL, hist_TRUE_FULL, 1.0,1.0,""); // cl=0.683 b(1,1) mode , this is suppose to be the bayesdividion but didnn't work , if using biomional error if universe are equal then dividion cancels them to equal  zero
 hist_TRUE_RECO_EMPTY->Divide(hist_TRUE_RECO_EMPTY, hist_TRUE_EMPTY, 1.0,1.0,"");
 hist_TRUE_RECO_FULL_clone->Divide(hist_TRUE_RECO_FULL_clone, hist_TRUE_FULL_clone, 1.0,1.0,"");
 bool SetYAxis = true;
 double yMax = EffMax;
 double yMin = EffMin;

 sprintf(Title_His, "%s Efficiency [F(%s)] ",title, playlistFull_char);
 DrawCVAndError_FromHIST(PrintallErrorBands,hist_TRUE_RECO_FULL, Title_His ,Xaxis_title,"Efficiency", pdf,true, doBinwidth, SetYAxis, yMin, yMax);
 sprintf(Title_His, "%s Efficiency [E(%s)]",title, playlistEmpty_char);
 DrawCVAndError_FromHIST(PrintallErrorBands,hist_TRUE_RECO_EMPTY, Title_His ,Xaxis_title,"Efficiency", pdf,true, doBinwidth, SetYAxis,yMin, yMax);
 sprintf(Title_His, "%s Efficiency [F(%s)- E(%s)]",title, playlistFull_char,playlistEmpty_char);
 DrawCVAndError_FromHIST(PrintallErrorBands, hist_TRUE_RECO_FULL_clone, Title_His ,Xaxis_title,"Efficiency", pdf, true, doBinwidth, SetYAxis,yMin, yMax);
 MnvH1D* Final_Efficiency_CLONE = (PlotUtils::MnvH1D*)hist_TRUE_RECO_FULL_clone ->Clone("Final_Efficiency_CLONE");



 //Acceptance_FULL ->Divide(Acceptance_FULL,Acceptance_FULL_DOM,1.0, 1.0, "");
 //Acceptance_EMPTY ->Divide(Acceptance_EMPTY,Acceptance_EMPTY_DOM,1.0, 1.0, "");
 //Acceptance_FULL_EMPTY_DOM->Add(Acceptance_EMPTY_DOM_clone,-1);
 //Acceptance_FULL_EMPTY->Add(Acceptance_EMPTY_clone,-1);
 //Acceptance_FULL_EMPTY->Divide(Acceptance_FULL_EMPTY,Acceptance_FULL_EMPTY_DOM,1.0, 1.0, "");

 //sprintf(Title_His, "%s Acceptance [F(%s)] ",title, playlistFull_char);
 //DrawCVAndError_FromHIST(PrintallErrorBands,Acceptance_FULL, Title_His ,Xaxis_title,"Acceptance", pdf,true, doBinwidth, SetYAxis, yMin, yMax);
 //sprintf(Title_His, "%s Acceptance [E(%s)]",title, playlistEmpty_char);
 //DrawCVAndError_FromHIST(PrintallErrorBands,Acceptance_EMPTY, Title_His ,Xaxis_title,"Acceptance", pdf,true, doBinwidth, SetYAxis,yMin, yMax);
 //sprintf(Title_His, "%s Acceptance [F(%s)- E(%s)]",title, playlistFull_char,playlistEmpty_char);
 //DrawCVAndError_FromHIST(PrintallErrorBands, Acceptance_FULL_EMPTY, Title_His ,Xaxis_title,"Acceptance", pdf, true, doBinwidth, SetYAxis,yMin, yMax);

///////////////////
sprintf(Title_His, "%s Purity [F(%s)] ",title, playlistFull_char);
Purity_Full_RECOBins->Divide(Purity_Full_RECOBins, Purity_Dom_Full_RECObins  ,  1.0,1.0,"");
DrawCVAndError_FromHIST(PrintallErrorBands, Purity_Full_RECOBins, Title_His ,Xaxis_title, "Purity", pdf,true, doBinwidth, SetYAxis,0.0, .5);
sprintf(Title_His, "%s Purity [E(%s)]",title, playlistEmpty_char);

Purity_EMPTY_RECOBins->Divide(Purity_EMPTY_RECOBins, Purity_Dom_Empty_RECOBins ,  1.0,1.0,"");
DrawCVAndError_FromHIST(PrintallErrorBands, Purity_EMPTY_RECOBins, Title_His ,Xaxis_title, "Purity", pdf,true, doBinwidth, SetYAxis,0.0, .5);
sprintf(Title_His, "%s Purity [F(%s)- E(%s)]",title,  playlistFull_char, playlistEmpty_char);

Purity_Full_EMPTY_RECOBins->Add(Purity_EMPTY_RECOBins_clone,-1.0);
Purity_Dom_Full_EMPTY_RECObins->Add(Purity_Dom_Empty_clone_RECObins,-1.0);
MnvH1D* Signal = (PlotUtils::MnvH1D*)Purity_Full_EMPTY_RECOBins->Clone("Signal");

Purity_Full_EMPTY_RECOBins->Divide(Purity_Full_EMPTY_RECOBins, Purity_Dom_Full_EMPTY_RECObins ,  1.0, 1.0, "");
std::vector<double> Signal_bins = GetXBinningfrom1DHist(Signal, false);
std::vector<double> Signal_vector = GetYContentfrom1DHist(Signal, false);
std::vector<double> Background_vector = GetYContentfrom1DHist(Background, false);

std::vector<double> Significance_vector = GetSignificance(Signal_vector ,Background_vector );
std::vector<double> Significance_vector_error = GetSignificanceError(Signal_vector ,Background_vector);
TGraphErrors  *TG_Significance = MakeTGraph_from_VectorsErrors(Significance_vector, Significance_vector_error,  Signal_bins);
sprintf(Title_His, "%s Significance [F(%s)- E(%s)]",title,  playlistFull_char, playlistEmpty_char);
char Xaxis_title_char[Xaxis_title.length()+1];
 strcpy( Xaxis_title_char,  Xaxis_title.c_str());
 const double  y1_arrow = 0.0;
 const double  y2_arrow = 0.015;
  const double  y2_arrow_Significance = TG_Significance->GetHistogram()->GetMaximum();
 const double  arrowLength = 100;

DrawTGraph_withArrow(TG_Significance, Xaxis_title_char, "Significance", Title_His, "",pdf_char, can, plot, false, false, 50, y1_arrow,  y2_arrow_Significance, arrowLength, "R" );

sprintf(Title_His, "%s Purity [F(%s)- E(%s)]",title,  playlistFull_char, playlistEmpty_char);
DrawCVAndError_FromHIST(PrintallErrorBands, Purity_Full_EMPTY_RECOBins, Title_His ,Xaxis_title, "Purity", pdf,true, doBinwidth, SetYAxis, 0.0, .5);
//////////////////////
MnvH1D* Final_Purity_CLONE = (PlotUtils::MnvH1D*)Purity_Full_EMPTY_RECOBins ->Clone("Final_Efficiency_CLONE");
std::vector<double> Purity_vector = GetYContentfrom1DHist(Final_Purity_CLONE, false);
std::vector<double> Eff_vector = GetYContentfrom1DHist(Final_Efficiency_CLONE, false);
TGraphErrors  *TG_Purity_VsEff = MakeTGraph_from_Vectors(Purity_vector,  Eff_vector);
DrawTGraph(TG_Purity_VsEff,"Efficieny","Purity", "Purity vs Efficieny", "",pdf_char, can, plot, false, false );

MnvH1D* Efficieny_FULL_clone = (PlotUtils::MnvH1D*)hist_TRUE_RECO_FULL ->Clone("Efficieny_FULL_clone");
MnvH1D* Efficieny_EMPTY_clone = (PlotUtils::MnvH1D*)hist_TRUE_RECO_EMPTY ->Clone("Efficieny_EMPTY_clone");
MnvH1D* Efficieny_FULL_EMPTY_clone = (PlotUtils::MnvH1D*)hist_TRUE_RECO_FULL_clone ->Clone("Efficieny_FULL_EMPTY_clone");

Efficieny_FULL_clone->Multiply(Efficieny_FULL_clone,Purity_Full_RECOBins, 1.0, 1.0 );
Efficieny_EMPTY_clone->Multiply(Efficieny_EMPTY_clone,Purity_EMPTY_RECOBins, 1.0, 1.0 );
Efficieny_FULL_EMPTY_clone->Multiply(Efficieny_FULL_EMPTY_clone,Purity_Full_EMPTY_RECOBins, 1.0, 1.0 );




 sprintf(Title_His, "%s [F(%s)] ",title, playlistFull_char);
 DrawCVAndError_FromHIST(PrintallErrorBands,Efficieny_FULL_clone, Title_His ,Xaxis_title, "Eff*Purity", pdf,true, doBinwidth, SetYAxis, 0.0, .025, 50, y1_arrow,  y2_arrow, arrowLength, "R");
 sprintf(Title_His, "%s [E(%s)]",title, playlistEmpty_char);
 DrawCVAndError_FromHIST(PrintallErrorBands,Efficieny_EMPTY_clone, Title_His ,Xaxis_title, "Eff*Purity", pdf,true, doBinwidth, SetYAxis, 0.0, .025, 50, y1_arrow,  y2_arrow, arrowLength, "R");
 sprintf(Title_His, "%s [F(%s)- E(%s)]",title, playlistFull_char, playlistEmpty_char);
 DrawCVAndError_FromHIST(PrintallErrorBands, Efficieny_FULL_EMPTY_clone, Title_His ,Xaxis_title, "Eff*Purity", pdf,true, doBinwidth, SetYAxis, 0.0, .025, 50, y1_arrow,  y2_arrow, arrowLength, "R");


 //Acceptance_FULL->Multiply(Acceptance_FULL,Purity_Full_RECOBins, 1.0, 1.0);
 //Acceptance_EMPTY->Multiply(Acceptance_EMPTY,Purity_EMPTY_RECOBins, 1.0, 1.0);
 //Acceptance_FULL_EMPTY->Multiply(Acceptance_FULL_EMPTY,Purity_Full_EMPTY_RECOBins, 1.0, 1.0);



 //sprintf(Title_His, "%s [F(%s)] ",title, playlistFull_char);
 //DrawCVAndError_FromHIST(PrintallErrorBands,Acceptance_FULL, Title_His ,Xaxis_title, "Acceptance*Purity", pdf,true, doBinwidth, SetYAxis, 0.0, .045, 50, y1_arrow,  y2_arrow, arrowLength, "R");
 //sprintf(Title_His, "%s [E(%s)]",title, playlistEmpty_char);
 //DrawCVAndError_FromHIST(PrintallErrorBands, Acceptance_EMPTY, Title_His ,Xaxis_title, "Acceptance*Purity", pdf,true, doBinwidth, SetYAxis, 0.0, .045, 50, y1_arrow,  y2_arrow, arrowLength, "R");
 //sprintf(Title_His, "%s [F(%s)- E(%s)]",title, playlistFull_char, playlistEmpty_char);
 //DrawCVAndError_FromHIST(PrintallErrorBands, Acceptance_FULL_EMPTY, Title_His ,Xaxis_title, "Acceptance*Purity", pdf,true, doBinwidth, SetYAxis, 0.0, .045, 50, y1_arrow,  y2_arrow, arrowLength, "R");

//BinByBinMuplication_byVector(*Acceptance_FULL_EMPTY, Significance_vector , false );
//BinByBinMuplication_byVector(*Efficieny_FULL_EMPTY_clone, Significance_vector , false );

double y2_arrow_new =.15;

//sprintf(Title_His, "%s [F(%s)- E(%s)]",title, playlistFull_char, playlistEmpty_char);
//DrawCVAndError_FromHIST(PrintallErrorBands, Efficieny_FULL_EMPTY_clone, Title_His ,Xaxis_title, "Eff*Purity*Significance", pdf,true, doBinwidth, SetYAxis, 0.0, .25, 50, y1_arrow,  y2_arrow_new, arrowLength, "R");
//y2_arrow_new =.12;
//sprintf(Title_His, "%s [F(%s)- E(%s)]",title, playlistFull_char, playlistEmpty_char);
//DrawCVAndError_FromHIST(PrintallErrorBands, Acceptance_FULL_EMPTY, Title_His ,Xaxis_title, "Acceptance*Purity*Significance", pdf,true, doBinwidth, SetYAxis, 0.0, .25, 50, y1_arrow,  y2_arrow_new, arrowLength, "R");

}//end of function
c
*/




/*
  ME_playlist_TFileMAP MakeTFileMap(ME_playlist_RootPathMAP MAP_RootPath){
    ME_playlist_TFileMAP Output_Map;
    std::cout<<"Making MakeTFileMap"<< std::endl;
     std::map<ME_helium_Playlists, std::string>::iterator RootPath_iter;

    for( RootPath_iter = MAP_RootPath.begin(); RootPath_iter != MAP_RootPath.end(); RootPath_iter++ ){

      auto pathname = RootPath_iter->second;
      auto playlist = RootPath_iter->first;
      char name_char[pathname.length()+1];
      strcpy(name_char, pathname.c_str());
      TFile *inputTFile = new TFile(name_char);
      std::cout<<"Made a Tfile with Path :"<< name_char<<std::endl;
      Output_Map.insert(std::make_pair(playlist,inputTFile));

    }

    return Output_Map;
  }
*/
