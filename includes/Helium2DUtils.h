#ifndef HELIUM2DUTILS_H
#define HELIUM2DUTILS_H

#include "TKey.h"
#include "TFile.h"
#include "HeliumCVUniverse.h"
#include "HeliumDefaults.h" // typedef UniverseMap
#include "PlotUtils/GenieSystematics.h"
#include "PlotUtils/FluxSystematics.h"
#include "PlotUtils/MnvTuneSystematics.h"
//#include "TruthCategories/Sidebands.h" // kFitVarString
#include "PlotUtils/HistWrapper.h"
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

std::string  GetMuon2DVarHistName( Muon2DVar var2D);
std::string  GetMuon2DVarHist_DATAName(Muon2DVar var2D);
std::string  GetMuon2DVar_XaxisTitle(Muon2DVar var2D);
std::string  GetMuon2DVar_YaxisTitle(Muon2DVar var2D);
std::string  GetMuon2DVar_Title(Muon2DVar var2D);
std::string  GetMuon2DVar_pdf(Muon2DVar var2D);
std::string GetMuon2DVar_yaxisUnits(Muon2DVar var2D);
std::string  GetMuon2DVar_ReponseHistTitle(Muon2DVar var2D);
std::vector<std::string>  GetMuon2DVar_ReponseHistTitle_vector(Muon2DVar var2D);
void Scale_MnvH2D_Array(const TObjArray  HistArray , double Scaler);
Playlist_HistFolio_MnvH2D_Map Constuct_HistFolio_MnvH2DMap_FromME_playlist_TFileMAP(ME_playlist_TFileMAP TFile_Map, const char* name );
Playlist_MnvH2D_Map Constuct_MnvH2DMap_FromME_playlist_TFileMAP(ME_playlist_TFileMAP TFile_Map, const char* name );
void BinWidthNorm_MnvH2D_Array(const TObjArray HistArray );
void AddFirst_toSecond_MnvH2D_Arrays(const TObjArray HistArray1 , const TObjArray HistArray2);
void SubractSecond_FromFirst_MnvH2D_Arrays(const TObjArray HistArray1 , const TObjArray HistArray2);

/*
//==============================================================================
// Make a HistWrapper from a variable's binning
//==============================================================================
void InitializeHW(Variable* var, std::string name, std::string label,
                  UniverseMap error_bands, CVHW& hw) {
  MH1D* hist = new MH1D(name.c_str(), label.c_str(), var->NBins(),
                        var->m_hists.m_bins_array.GetArray());

  // make CVHW from MH1D
  const bool clear_bands = true;
  hw = CVHW(hist, error_bands, clear_bands);

  delete hist;
}
*/




//==============================================================================
// Get hist by name from an in-file
//==============================================================================

//==============================================================================
// Copy all hists of one file into another file
//==============================================================================


//==============================================================================
// Get pointer to a variable with name from vector of variables
//==============================================================================

#endif // common_functions_h
