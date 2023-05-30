#include "Helium_reweightModels.h"

bool DebugmodeModels = true;

std::string GetNameModel(MC_ModelTypes Model) {
  switch (Model) {
    case kME_GENIE_MnvTune1:
      return "MnvTune1";

    case kME_GENIE_G18_02a_02_11a:
      return "GENIE_G18_02a_02_11a";

    case kME_GENIE_G18_10a_02_11a:
      return "GENIE_G18_10a_02_11a";

    case kME_GENIE_G18_02b_02_11a:
      return "GENIE_G18_02b_02_11a";

    case kME_GENIE_G18_10b_02_11a:
      return "GENIE_G18_10b_02_11a";

    default:
      std::cout << "ERROR: unknown Model Name!" << std::endl;
      return "";
  };
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
Model_TFileMAP MakeTFileModelMap(Model_RootPathMAP MAP_RootPath) {
  Model_TFileMAP Output_Map;
  std::cout << "Making Make TFile Model Map" << std::endl;
  std::map<MC_ModelTypes, std::string>::iterator Model_iter;

  for (Model_iter = MAP_RootPath.begin(); Model_iter != MAP_RootPath.end();
       Model_iter++) {
    auto pathname = Model_iter->second;
    auto Model = Model_iter->first;
    char name_char[pathname.length() + 1];
    strcpy(name_char, pathname.c_str());
    TFile* inputTFile = new TFile(name_char);
    std::cout << "Made a Tfile with Path :" << name_char << std::endl;
    Output_Map.insert(std::make_pair(Model, inputTFile));
  }

  return Output_Map;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
Model_MnvH1D_Map Constuct_mvnH1DMap_FromModel_TFileMAP(Model_TFileMAP TFile_Map,
                                                       const char* name) {
  Model_MnvH1D_Map MnvH1D_Map;
  // std::cout<<" " <<std::endl;
  if (DebugmodeModels == true)
    std::cout << " Constucting Hist map for Varible Name:" << name << std::endl;
  if (DebugmodeModels == true)
    std::cout << " Input Map Has Size =  " << TFile_Map.size() << std::endl;
  typename std::map<MC_ModelTypes, TFile*>::iterator model_iter;
  int Bins1 = 999;
  for (model_iter = TFile_Map.begin(); model_iter != TFile_Map.end();
       ++model_iter) {
    // auto hist = GetHist(cat->second, name);
    if (DebugmodeModels == true)
      std::cout << " Playlist Name : " << GetNameModel(model_iter->first)
                << std::endl;
    // MnvH1D *hist = (MnvH1D*)(cat->second)->Get(name);
    MnvH1D* hist = Get1DHist(*model_iter->second, name);
    if (hist == 0) {
      std::cout << " Playlist Name : " << GetNameModel(model_iter->first)
                << std::endl;
    }
    if (Bins1 == 999) {
      Bins1 = hist->GetNbinsX();
    }

    if (Bins1 != hist->GetNbinsX()) {
      std::cout << "Opps :( trying to merg Hists with different Bin sizes)"
                << std::endl;
      std::cout << "Playlist Name : " << GetNameModel(model_iter->first)
                << " Number Bins = " << hist->GetNbinsX() << std::endl;
      assert(false);
    }
    //

    MnvH1D_Map.insert(std::make_pair(model_iter->first, hist));

  }  // end of loop

  // std::cout<<"~~~~FINISHED~~~~~~" <<std::endl;
  // std::cout<<" " <<std::endl;

  return MnvH1D_Map;
}  // end of function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
Model_TH1D_Map Constuct_TH1DMap_FromModel_TFileMAP(Model_TFileMAP TFile_Map,
                                                   const char* name) {
  Model_TH1D_Map TH1D_Map;
  // std::cout<<" " <<std::endl;
  if (DebugmodeModels == true)
    std::cout << " Constucting Hist map for Varible Name:" << name << std::endl;
  if (DebugmodeModels == true)
    std::cout << " Input Map Has Size =  " << TFile_Map.size() << std::endl;
  typename std::map<MC_ModelTypes, TFile*>::iterator model_iter;
  int Bins1 = 999;
  for (model_iter = TFile_Map.begin(); model_iter != TFile_Map.end();
       ++model_iter) {
    // auto hist = GetHist(cat->second, name);
    if (DebugmodeModels == true)
      std::cout << " Playlist Name : " << GetNameModel(model_iter->first)
                << std::endl;
    // MnvH1D *hist = (MnvH1D*)(cat->second)->Get(name);
    TH1D* hist = GetTH1DHist(*model_iter->second, name);
    if (hist == 0) {
      std::cout << " Playlist Name : " << GetNameModel(model_iter->first)
                << std::endl;
    }
    if (Bins1 == 999) {
      Bins1 = hist->GetNbinsX();
    }

    if (Bins1 != hist->GetNbinsX()) {
      std::cout << "Opps :( trying to merg Hists with different Bin sizes)"
                << std::endl;
      std::cout << "Playlist Name : " << GetNameModel(model_iter->first)
                << " Number Bins = " << hist->GetNbinsX() << std::endl;
      assert(false);
    }
    //

    TH1D_Map.insert(std::make_pair(model_iter->first, hist));

  }  // end of loop

  // std::cout<<"~~~~FINISHED~~~~~~" <<std::endl;
  // std::cout<<" " <<std::endl;

  return TH1D_Map;
}  // end of function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
Model_TH1D_Map Constuct_TH1DMap_FromModel_TFileMAP(Model_TFileMAP TFile_Map,
                                                   std::string name) {
  char Name_char[name.length() + 1];
  strcpy(Name_char, name.c_str());
  return Constuct_TH1DMap_FromModel_TFileMAP(TFile_Map, Name_char);
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
Model_MnvH1D_Map Constuct_mvnH1DMap_FromModel_TFileMAP(Model_TFileMAP TFile_Map,
                                                       std::string name) {
  char Name_char[name.length() + 1];
  strcpy(Name_char, name.c_str());
  return Constuct_mvnH1DMap_FromModel_TFileMAP(TFile_Map, Name_char);

}  // end of loop
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
Model_MnvH1D_Map Constuct_mvnH1DMap_FromModel_TFileMAP(Model_TFileMAP TFile_Map,
                                                       const char* name,
                                                       double scale) {
  Model_MnvH1D_Map MnvH1D_Map;
  // std::cout<<" " <<std::endl;
  if (DebugmodeModels == true)
    std::cout << " Constucting Hist map for Varible Name:" << name << std::endl;
  if (DebugmodeModels == true)
    std::cout << " Input Map Has Size =  " << TFile_Map.size() << std::endl;
  typename std::map<MC_ModelTypes, TFile*>::iterator model_iter;
  int Bins1 = 999;
  for (model_iter = TFile_Map.begin(); model_iter != TFile_Map.end();
       ++model_iter) {
    // auto hist = GetHist(cat->second, name);
    if (DebugmodeModels == true)
      std::cout << " Playlist Name : " << GetNameModel(model_iter->first)
                << std::endl;
    // MnvH1D *hist = (MnvH1D*)(cat->second)->Get(name);
    MnvH1D* hist = Get1DHist(*model_iter->second, name);
    hist->Scale(scale);
    if (hist == 0) {
      std::cout << " Playlist Name : " << GetNameModel(model_iter->first)
                << std::endl;
    }
    if (Bins1 == 999) {
      Bins1 = hist->GetNbinsX();
    }

    if (Bins1 != hist->GetNbinsX()) {
      std::cout << "Opps :( trying to merg Hists with different Bin sizes)"
                << std::endl;
      std::cout << "Playlist Name : " << GetNameModel(model_iter->first)
                << " Number Bins = " << hist->GetNbinsX() << std::endl;
      assert(false);
    }
    //

    MnvH1D_Map.insert(std::make_pair(model_iter->first, hist));

  }  // end of loop

  // std::cout<<"~~~~FINISHED~~~~~~" <<std::endl;
  // std::cout<<" " <<std::endl;

  return MnvH1D_Map;
}  // end of function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
Model_MnvH1D_Map Constuct_mvnH1DMap_FromModel_TFileMAP(Model_TFileMAP TFile_Map,
                                                       std::string name,
                                                       double scale) {
  char Name_char[name.length() + 1];
  strcpy(Name_char, name.c_str());
  return Constuct_mvnH1DMap_FromModel_TFileMAP(TFile_Map, Name_char, scale);

}  // end of loop

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void Genie_Models::intializeTFileMap() {
  if (ModelPathWay.size() == 0) {
    std::cout << "Root map 0 can't intialize TFile" << std::endl;
  } else {
    TFileMap = MakeTFileModelMap(ModelPathWay);
  }
	return;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void Genie_Models::intializeMnvH1DMap() {
  std::cout << "intializeMnvH1DMap::Finished MakeTFileMap " << std::endl;

  ModelHistMap_1D = Constuct_mvnH1DMap_FromModel_TFileMAP(TFileMap, HistName);
  std::cout << "intializeMnvH1DMap::Finished "
               "Constuct_mvnH1DMap_FromME_playlist_TFileMAP "
            << std::endl;

  for (Model_iter = ModelHistMap_1D.begin();
       Model_iter != ModelHistMap_1D.end(); Model_iter++) {
    std::string modeltitle = GetNameModel(Model_iter->first);
    Model_iter->second->SetTitle(modeltitle.c_str());
  }
	return;
  std::cout << "intializeMnvH1DMap::Finished" << std::endl;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void Genie_Models::intializeTH1DMap() {
  std::cout << "intializeMnvH1DMap::Finished MakeTFileMap " << std::endl;

  ModelHistMap_th1D = Constuct_TH1DMap_FromModel_TFileMAP(TFileMap, HistName);
  std::cout << "intializeMnvH1DMap::Finished "
               "Constuct_mvnH1DMap_FromME_playlist_TFileMAP "
            << std::endl;

  for (Model_iter = ModelHistMap_1D.begin();
       Model_iter != ModelHistMap_1D.end(); Model_iter++) {
    std::string modeltitle = GetNameModel(Model_iter->first);
    Model_iter->second->SetTitle(modeltitle.c_str());
  }

	return;

  std::cout << "intializeMnvH1DMap::Finished" << std::endl;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void Genie_Models::ScaleTH1DHists(double inputscale) {
  std::cout << "applying Scale1DHists size = " << ModelHistMap_th1D.size()
            << std::endl;
  for (auto Model : ModelHistMap_th1D) {
    std::cout << "Scaled hist title: " << Model.second->GetTitle() << std::endl;
    Model.second->Scale(inputscale);
  }
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void Genie_Models::Scale1DHists(double inputscale) {
  std::cout << "applying Scale1DHists size = " << ModelHistMap_1D.size()
            << std::endl;

  // for(Model_iter = ModelHistMap_1D.begin(); Model_iter !=
  // ModelHistMap_1D.end();  Model_iter++ ){
  //	std::cout<<"Scaled hist title: " <<
  //Model_iter->second->GetTitle()<<std::endl;
  //  Model_iter->second->Scale(inputscale);
  //}

  for (auto Model : ModelHistMap_1D) {
    std::cout << "Scaled hist title: " << Model.second->GetTitle() << std::endl;
  }
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void Genie_Models::Scale2DHists(double inputscale) {
  for (auto Model : ModelHistMap_2D) {
    Model.second->Scale(inputscale);
  }
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
TObjArray* Genie_Models::HistsMnvH1DArrary() {
  std::cout << "Trying to make HistsMnvH1DArrary" << std::endl;

  TObjArray* outputArray;

  for (Model_iter = ModelHistMap_1D.begin();
       Model_iter != ModelHistMap_1D.end(); Model_iter++) {
    PlotUtils::MnvH1D* h_model =
        (PlotUtils::MnvH1D*)Model_iter->second->Clone("");
    std::string modeltitle = GetNameModel(Model_iter->first);
    char Titlechar[modeltitle.length() + 1];
    strcpy(Titlechar, modeltitle.c_str());
    h_model->SetTitle(Titlechar);
    outputArray->Add(h_model);
  }

  return outputArray;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
TObjArray* Genie_Models::HistsTH1DArrary() {
  std::cout << "Trying to make HistsMnvH1DArrary" << std::endl;
  typename std::map<MC_ModelTypes, TH1D*>::iterator Modelth1d_iter;
  TObjArray* outputArray;

  for (Modelth1d_iter = ModelHistMap_th1D.begin();
       Modelth1d_iter != ModelHistMap_th1D.end(); Modelth1d_iter++) {
    TH1D* h_model = (TH1D*)Modelth1d_iter->second->Clone("");
    std::string modeltitle = GetNameModel(Modelth1d_iter->first);
    char Titlechar[modeltitle.length() + 1];
    strcpy(Titlechar, modeltitle.c_str());
    h_model->SetTitle(Titlechar);
    outputArray->Add(h_model);
  }

  return outputArray;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
