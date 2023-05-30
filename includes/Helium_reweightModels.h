#ifndef HELIUM_REWEIGHTMODELS_H
#define HELIUM_REWEIGHTMODELS_H

#include "TKey.h"
#include "TFile.h"
#include "HeliumCVUniverse.h"
#include "HeliumDefaults.h"  // typedef UniverseMap
#include "PlotUtils/GenieSystematics.h"
#include "PlotUtils/FluxSystematics.h"
#include "PlotUtils/MnvTuneSystematics.h"
#include "PlotUtils/HistWrapper.h"
#include <vector>
#include <algorithm>
#include "TColor.h"
#include "PlotUtils/POTCounter.h"
#include "PlotUtils/ChainWrapper.h"
#include "PlotUtils/makeChainWrapper.h"
#include "PlotUtils/HistFolio.h"
#include "TGraphErrors.h"
#include <map>
#include "plot.h"

//#ifndef __CINT__
//#include "Variable.h"
//#endif // __CINT__
Model_TFileMAP MakeTFileModelMap(Model_RootPathMAP MAP_RootPath);
Model_MnvH1D_Map Constuct_mvnH1DMap_FromModel_TFileMAP(Model_TFileMAP TFile_Map,
                                                       const char* name);
////////////////////////////////////////////////////////////////////////////////
Model_MnvH1D_Map Constuct_mvnH1DMap_FromModel_TFileMAP(Model_TFileMAP TFile_Map,
                                                       std::string name);
////////////////////////////////////////////////////////////////////////////////
Model_MnvH1D_Map Constuct_mvnH1DMap_FromModel_TFileMAP(Model_TFileMAP TFile_Map,
                                                       const char* name,
                                                       double scale);
////////////////////////////////////////////////////////////////////////////////
Model_MnvH1D_Map Constuct_mvnH1DMap_FromModel_TFileMAP(Model_TFileMAP TFile_Map,
                                                       std::string name,
                                                       double scale);
////////////////////////////////////////////////////////////////////////////////
Model_TH1D_Map Constuct_TH1DMap_FromModel_TFileMAP(Model_TFileMAP TFile_Map,
                                                   const char* name);
////////////////////////////////////////////////////////////////////////////////
Model_TH1D_Map Constuct_TH1DMap_FromModel_TFileMAP(Model_TFileMAP TFile_Map,
                                                   std::string name);
////////////////////////////////////////////////////////////////////////////////
class Genie_Models {
 public:
  Model_RootPathMAP ModelPathWay;
  std::string HistName;
  std::vector<MC_ModelTypes> Model_Playlist;
  Model_TFileMAP TFileMap;
  Model_MnvH1D_Map ModelHistMap_1D;
  Model_TH1D_Map ModelHistMap_th1D;
  Model_MnvH2D_Map ModelHistMap_2D;
  typename std::map<MC_ModelTypes, PlotUtils::MnvH1D*>::iterator Model_iter;

  Genie_Models(std::string HistNameInput, Model_RootPathMAP ModelPath) {
    HistName = HistNameInput;
    ModelPathWay = ModelPath;
    for (auto model : ModelPath) {
      Model_Playlist.push_back(model.first);
    }
  }

  ~Genie_Models() {
    std::cout << " Destructor executed" << std::endl;
    if (TFileMap.size() != 0) {
      for (auto map : TFileMap) {
        map.second->Close();
      }
    }
  }

  void intializeTFileMap();
  void intializeHistModelMap();
  void intializeMnvH1DMap();
  void intializeMnvH2DMap();
  void Scale1DHists(double inputscale);
  void ScaleTH1DHists(double inputscale);
  void Scale2DHists(double inputscale);
  TObjArray* HistsMnvH1DArrary();
  TObjArray* HistsTH1DArrary();
  void intializeTH1DMap();
};

#endif  //
