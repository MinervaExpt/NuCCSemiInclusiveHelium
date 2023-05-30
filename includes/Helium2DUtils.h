#ifndef HELIUM2DUTILS_H
#define HELIUM2DUTILS_H

#include "TKey.h"
#include "TFile.h"
#include "HeliumCVUniverse.h"
#include "HeliumDefaults.h"
// typedef UniverseMap
#include "PlotUtils/GenieSystematics.h"
#include "PlotUtils/FluxSystematics.h"
#include "PlotUtils/MnvTuneSystematics.h"
#include "PlotUtils/HistWrapper.h"
#include "PlotUtils/MnvPlotter.h"
//#include "TruthCategories/Sidebands.h" // kFitVarString
#include "plot.h"
#include <vector>
#include <algorithm>
#include "TColor.h"
#include <iostream>
//#ifndef __CINT__
//#include "Variable.h"
//#endif // __CINT__

//==============================================================================
// Variable Binning
//==============================================================================

std::string GetMuon2DVarHistName(Muon2DVar var2D);
////////////////////////////////////////////////////////////////////////////////
std::string GetMuon2DVarHist_DATAName(Muon2DVar var2D);
////////////////////////////////////////////////////////////////////////////////
std::string GetMuon2DVar_XaxisTitle(Muon2DVar var2D);
////////////////////////////////////////////////////////////////////////////////
std::string GetMuon2DVar_YaxisTitle(Muon2DVar var2D);
////////////////////////////////////////////////////////////////////////////////
std::string GetMuon2DVar_XaxisTitle_noUntils(Muon2DVar var2D);
////////////////////////////////////////////////////////////////////////////////
std::string GetMuon2DVar_YaxisTitle_noUntils(Muon2DVar var2D);
////////////////////////////////////////////////////////////////////////////////
std::string GetMuon2DVar_Title(Muon2DVar var2D);
////////////////////////////////////////////////////////////////////////////////
std::string GetMuon2DVar_pdf(Muon2DVar var2D);
////////////////////////////////////////////////////////////////////////////////
std::string GetMuon2DVar_yaxisUnits(Muon2DVar var2D);
////////////////////////////////////////////////////////////////////////////////
std::string GetMuon2DVar_xaxisUnits(Muon2DVar var2D);
////////////////////////////////////////////////////////////////////////////////
std::string GetMuon2DVar_TotalUnits(Muon2DVar var2D);
////////////////////////////////////////////////////////////////////////////////
std::string GetMuon2DVar_ReponseHistTitle(Muon2DVar var2D);
////////////////////////////////////////////////////////////////////////////////
std::vector<std::string> GetMuon2DVar_ReponseHistTitle_vector(Muon2DVar var2D);
////////////////////////////////////////////////////////////////////////////////
std::vector<std::string> GetMuon2DVar_ReponseHistTitle_vector_Daisy(
    Muon2DVar var2D, std::string Number);
////////////////////////////////////////////////////////////////////////////////
CrossSection_2DhistNames Constuct_2Dcrosssection_Histname(Muon2DVar var2D);
////////////////////////////////////////////////////////////////////////////////
CrossSection_2DhistNames Constuct_2Dcrosssection_Histname(
    Muon2DVar var2D, std::string ExtraString);
  ////////////////////////////////////////////////////////////////////////////////
CrossSection2D_Hist Constuct_2Dcrosssection_Hists(
    CrossSection_2DhistNames Names, TFile *inputFile_RECO_mc,
    TFile *inputFile_TRUE_mc, TFile *inputFile_data);
////////////////////////////////////////////////////////////////////////////////
ME_playlist_2DCrossSection_MAP Constuct_2Dcrosssection_Hists_PlaylistMap(
    CrossSection_2DhistNames Names, ME_playlist_TFileMAP MC_RECO_TfileMap,
    ME_playlist_TFileMAP MC_TRUTH_TfileMap, ME_playlist_TFileMAP Data_TfileMap);
////////////////////////////////////////////////////////////////////////////////
CrossSection2D_Hist Combine_2Dcrosssection_Hists_PlaylistMap(
    ME_playlist_2DCrossSection_MAP inputMap,
    ME_helium_Playlists playlist_combine_too);
////////////////////////////////////////////////////////////////////////////////
CrossSection2D_Hist Combine_crosssection_Hists_PlaylistMap_includeInteraction(
    ME_playlist_2DCrossSection_MAP inputMap,
    ME_helium_Playlists playlist_combine_too);
////////////////////////////////////////////////////////////////////////////////
CrossSection2D_Hist
Combine_2Dcrosssection_Hists_PlaylistMap_includeInteraction_DISbreakdown(
    ME_playlist_2DCrossSection_MAP inputMap,
    ME_helium_Playlists playlist_combine_too);
////////////////////////////////////////////////////////////////////////////////
Interaction_type_MnvH2D_Map AddInteraction2DHistMap_DISbreakdown(
    TFile &file, std::string input_hist_name, std::string extra);
////////////////////////////////////////////////////////////////////////////////
void AddInteraction2DHistMap_DISbreakdown(
    ME_playlist_2DCrossSection_MAP &Hist_Map,
    ME_playlist_TFileMAP MC_TRUTH_TfileMap, std::string input_hist_name,
    std::string extra_name);
////////////////////////////////////////////////////////////////////////////////
void Print_2Dcrosssection_Histname(
    CrossSection_2DhistNames crosssection_hist_Names);
////////////////////////////////////////////////////////////////////////////////
// void Scale_MnvH2D_Array(const TObjArray  HistArray , double Scaler);
void Scale_MnvH2D_Array(TObjArray HistArray, double Scaler);
////////////////////////////////////////////////////////////////////////////////
Playlist_HistFolio_MnvH2D_Map
Constuct_HistFolio_MnvH2DMap_FromME_playlist_TFileMAP(
    ME_playlist_TFileMAP TFile_Map, const char *name);
////////////////////////////////////////////////////////////////////////////////
TObjArray Combined_HistFolio_MnvH2D_Map(ME_playlist_TFileMAP TFile_Map,
                                        const char *name,
                                        ME_helium_Playlists StartingPlaylist);
////////////////////////////////////////////////////////////////////////////////
Playlist_MnvH2D_Map Constuct_MnvH2DMap_FromME_playlist_TFileMAP(
    ME_playlist_TFileMAP TFile_Map, const char *name);
////////////////////////////////////////////////////////////////////////////////
TObjArray Combined_HistFolio_MnvH2D_Map(
    Playlist_HistFolio_MnvH2D_Map input_Map);
////////////////////////////////////////////////////////////////////////////////
TObjArray ConstuctTObjArray_HistFolio_MnvH2DMap_FromME_playlist_TFileMAP(
    ME_playlist_TFileMAP TFile_Map, const char *name);
////////////////////////////////////////////////////////////////////////////////
TObjArray
ConstuctTObjArray_HistFolio_MnvH2DMap_FromME_playlist_TFileMAP_Full_Empty(
    ME_playlist_TFileMAP TFile_MapFull, ME_playlist_TFileMAP TFile_MapEmpty,
    const char *name, double MC_ScalerFulltoFullData,
    double MC_ScalerEmptytoFullData);
////////////////////////////////////////////////////////////////////////////////
void BinWidthNorm_MnvH2D_Array(const TObjArray HistArray);
////////////////////////////////////////////////////////////////////////////////
void AddFirst_toSecond_MnvH2D_Arrays(const TObjArray HistArray1,
                                     const TObjArray HistArray2);
////////////////////////////////////////////////////////////////////////////////
// cvoid SubractSecond_FromFirst_MnvH2D_Arrays(const TObjArray HistArray1 ,
// const TObjArray HistArray2);
void SubractSecond_FromFirst_MnvH2D_Arrays(TObjArray HistArray1,
                                           TObjArray HistArray2);
////////////////////////////////////////////////////////////////////////////////
TObjArray CombinedStack_MnvH2D_Map(ME_playlist_TFileMAP TFile_Map,
                                   std::string name,
                                   std::vector<std::string> StackNames,
                                   ME_helium_Playlists StartingPlaylist);
////////////////////////////////////////////////////////////////////////////////
TObjArray MakeTObjArray_2DHists(TFile &f, std::string BaseName,
                                std::vector<std::string> StackNames);
////////////////////////////////////////////////////////////////////////////////
std::string Construct_string_Ending(bool isMiG, bool isStack, char *StackType,
                                    bool isYProj, int isFULLorEmpty,
                                    bool FirstorSecond);
////////////////////////////////////////////////////////////////////////////////
void Check2D_NSignalBins(CrossSection2D_Hist &Constuct_crosssection_Hists,
                         char *Name);
////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_2DAll(CrossSection2D_Hist &Constuct_crosssection_Hists,
                        TFile &file, char *Name);
////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_2Dmain(CrossSection2D_Hist &Constuct_crosssection_Hists,
                         TFile &file, char *Name);
////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_NormTRUECrossSection_Interaction_DISbreakdown(
    CrossSection2D_Hist &Constuct_crosssection_Hists, TFile &file, char *Name,
    const double nNucleons, const double POT);
////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_NormTRUE2DCrossSection_Interaction(
    CrossSection2D_Hist &Constuct_crosssection_Hists, TFile &file, char *Name,
    const double nNucleons, const double POT);
////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_NormTRUE2DCrossSection(
    CrossSection2D_Hist &Constuct_crosssection_Hists, TFile &file, char *Name,
    const double nNucleons, const double POT);
////////////////////////////////////////////////////////////////////////////////
int GetGlobalBinNFrom2DMig(MnvH2D *migration, MnvH2D *h_reco, MnvH2D *h_truth,
                           double meas_x, double meas_y, double truth_x,
                           double truth_y);
////////////////////////////////////////////////////////////////////////////////
int GetGlobalBinNFrom2DMig_BinN(MnvH2D *migration, MnvH2D *h_reco,
                                MnvH2D *h_truth, int meas_xBinN, int meas_yBinN,
                                int truth_xBinN, int truth_yBinN);
////////////////////////////////////////////////////////////////////////////////
MnvH2D *GetMigration_Projection_Y_forBinN(MnvH2D *migration, MnvH2D *h_reco,
                                          MnvH2D *h_truth,
                                          std::vector<double> ProjectBinning,
                                          int BinN_project);
////////////////////////////////////////////////////////////////////////////////
MnvH2D *GetMigration_Projection_X_forBinN(MnvH2D *migration, MnvH2D *h_reco,
                                          MnvH2D *h_truth,
                                          std::vector<double> ProjectBinning,
                                          int BinN_project);
////////////////////////////////////////////////////////////////////////////////
void GetMigration_Projection_Y_forBinN_input(MnvH2D &h_return,
                                             MnvH2D *migration, MnvH2D *h_reco,
                                             MnvH2D *h_truth, int BinN_project);
////////////////////////////////////////////////////////////////////////////////
void drawBinRange(MnvH2D *h, int axis, int bin, const char *varName,
                  double text_size, const char *numFormatStr, bool left);
////////////////////////////////////////////////////////////////////////////////
void drawBinRange_Red(MnvH2D *h, int axis, int bin, const char *varName,
                      double text_size, const char *numFormatStr, bool left);
////////////////////////////////////////////////////////////////////////////////
double GetMaxFromProjectionY(MnvH2D *h1, MnvH2D *h2, bool checkBinwidth);
////////////////////////////////////////////////////////////////////////////////
double GetMaxFromProjectionY(MnvH2D *h1, bool checkBinwidth);
////////////////////////////////////////////////////////////////////////////////
double GetMaxFromProjectionX(MnvH2D *h1, MnvH2D *h2, bool checkBinwidth);
////////////////////////////////////////////////////////////////////////////////
double GetMaxFromProjectionX(MnvH2D *h1, bool checkBinwidth);
////////////////////////////////////////////////////////////////////////////////
std::vector<double> calculateMeanValues(MnvH2D *hist);
////////////////////////////////////////////////////////////////////////////////
std::vector<double> extractXBins(MnvH2D *hist);
////////////////////////////////////////////////////////////////////////////////
TH2D *rebinXAxis(TH2D *hist, const std::vector<double> rebinFactors);
////////////////////////////////////////////////////////////////////////////////
MnvH2D *rebinXAxis(MnvH2D *hist, const std::vector<double> rebinFactors);
////////////////////////////////////////////////////////////////////////////////
CrossSection_2DhistNames MakeDaisy_names(
    CrossSection_2DhistNames crosssection_hist_Names, std::string DaisyNum);
////////////////////////////////////////////////////////////////////////////////
CrossSection2D_Hist MakeDaisyCrossSectionHist(CrossSection_2DhistNames Names,
                                              std::string DaisyN,
                                              TFile *inputFile_RECO_mc,
                                              TFile *inputFile_TRUE_mc,
                                              TFile *inputFile_data);
////////////////////////////////////////////////////////////////////////////////
CrossSection2D_Hist_Daisy Constuct_crosssection_Hists_Daisy(
    CrossSection_2DhistNames Names, TFile *inputFile_RECO_mc,
    TFile *inputFile_TRUE_mc, TFile *inputFile_data);
////////////////////////////////////////////////////////////////////////////////
ME_playlist_2D_CrossSection_MAP_DAISY
Constuct_crosssection_2DHists_PlaylistMap_DAISY(
    CrossSection_2DhistNames Names, ME_playlist_TFileMAP MC_RECO_TfileMap,
    ME_playlist_TFileMAP MC_TRUTH_TfileMap, ME_playlist_TFileMAP Data_TfileMap);
////////////////////////////////////////////////////////////////////////////////
void Add2DCrossSectionHis_noFlux(CrossSection2D_Hist &AddTo,
                                 CrossSection2D_Hist input);
////////////////////////////////////////////////////////////////////////////////
void AddCrossSectionHist_Daisy_noFlux(CrossSection2D_Hist_Daisy &AddTo,
                                      CrossSection2D_Hist_Daisy input);
////////////////////////////////////////////////////////////////////////////////                                      
CrossSection2D_Hist_Daisy Combine_crosssection_Hists_PlaylistMap_Daisy(
    ME_playlist_2D_CrossSection_MAP_DAISY inputMap,
    ME_helium_Playlists playlist_combine_too);
//==============================================================================
// Get hist by name from an in-file
//==============================================================================

//==============================================================================
// Copy all hists of one file into another file
//==============================================================================

//==============================================================================
// Get pointer to a variable with name from vector of variables
//==============================================================================

#endif  // common_functions_h
