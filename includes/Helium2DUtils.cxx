
#include "Helium2DUtils.h"

//==============================================================================
// Copy all hists of one file into another file
//==============================================================================
void Copy2DHists(TFile& fin, TFile& fout) {
  TIter nextkey(fin.GetListOfKeys());
  TKey *key;
  while ((key = (TKey*)nextkey())) {
    TString name=key->GetName();
    PlotUtils::MnvH2D* h=(PlotUtils::MnvH2D*)key->ReadObj();
    if (!h) {
      std::cout << "Invalid histogram " << name << "\n";
      continue;
    }

    //h->Scale(potScale);
    fout.cd();
    //std::cout << "Writing histogram " << name << "\n";
    h->Write(name);
  }
}


//==============================================================================
// WritePOT to file as a vector

//==============================================================================
// Angle and Geometry Functions
//==============================================================================
/*
std::vector<int> Helium9_colorScheme = {
  TColor::GetColor("#D3D3D3"),  //'lightgrey'
  TColor::GetColor("#DA70D6"), //'orchid'
  TColor::GetColor("#FFA500"), //'orange'
  TColor::GetColor("#87CEEB"),//'skyblue'
  TColor::GetColor("#6495ED"), //'cornflowerblue'
  TColor::GetColor("#00FFFF"),//'aqua'
  TColor::GetColor("#0000CD"),//'blue'
  TColor::GetColor("#FF0000"),//'red'
  TColor::GetColor("#32CD32"),//'limegreen'
  TColor::GetColor("#FFD700"),  // Gold
  TColor::GetColor("#800000"),  // Maroon
  TColor::GetColor("#555555")  // dark grey
};
*/


////////////////////////////////////////
//
////////////////////////////////////////
std::string  GetMuon2DVarHistName( Muon2DVar var2D) {
  switch (var2D) {
    case kPT_PZ:
    return "h_Muon_PZ_PT";

    case kPT_theta:
    return "h_Muon_PT_theta";

    case kPZ_theta:
    return "h_Muon_PZ_theta";

    case kE_theta:
    return "h_Muon_E_theta";

    case kE_PZ:
    return "h_Muon_E_PZ";

    case kE_PT:
    return "h_Muon_E_PT";

    case kVertex_Z_R:
    return "h_cryoVertex_Z_R";

    default:
    std::cout << "ERROR: unknown Playlist name for Muon !" << std::endl;
    return "";
  };
}
////////////////////////////////////////
//
////////////////////////////////////////
std::string  GetMuon2DVarHist_DATAName(Muon2DVar var2D) {
  switch (var2D) {
    case kPT_PZ:
    return "h_Data_Muon_PZ_PT";

    case kPT_theta:
    return "h_Data_Muon_PT_theta";

    case kPZ_theta:
    return "h_Data_Muon_PZ_theta";

    case kE_theta:
    return "h_Data_Muon_E_theta";

    case kE_PZ:
    return "h_Data_Muon_E_PZ";

    case kE_PT:
    return "h_Data_Muon_E_PT";

    case kVertex_Z_R:
    return "h_Data_cryoVertex_Z_R";

    default:
    std::cout << "ERROR: unknown Playlist name for Muon !" << std::endl;
    return "";
  };
}
////////////////////////////////////////
//
////////////////////////////////////////
std::string  GetMuon2DVar_Title(Muon2DVar var2D) {
  switch (var2D) {
    case kPT_PZ:
    return "P_{T} vs P_{#parallel}";

    case kPT_theta:
    return "P_{T} vs  #theta_{#mu} ";

    case kPZ_theta:
    return "P_{#parallel} vs #theta_{#mu} ";

    case kE_theta:
    return "E_{#mu} vs  #theta_{#mu} ";

    case kE_PZ:
    return "E_{#mu} vs P_{#parallel}  ";

    case kE_PT:
    return "E_{#mu} vs P_{T}   ";

    case kVertex_Z_R:
    return "Vertex R Vs Z";

    default:
    std::cout << "ERROR: unknown Playlist name for Muon !" << std::endl;
    return "";
  };
}
////////////////////////////////////////
//
////////////////////////////////////////
std::string  GetMuon2DVar_pdf(Muon2DVar var2D) {
  switch (var2D) {

    case kPT_PZ:
    return "Pt_Pz";

    case kPT_theta:
    return "Pt_theta";

    case kPZ_theta:
    return "Pz_theta";

    case kE_theta:
    return "E_theta";

    case kE_PZ:
    return "E_Pz";

    case kE_PT:
    return "E_Pt";

    case kVertex_Z_R:
    return "vertexZ_R";

    default:
    std::cout << "ERROR: unknown Playlist name for Muon !" << std::endl;
    return "";
  };
}
////////////////////////////////////////
//
////////////////////////////////////////
std::string  GetMuon2DVar_yaxisUnits(Muon2DVar var2D) {
  switch (var2D) {

    case kPT_PZ:
    return "GeV^{2}/c^{2}";

    case kPT_theta:
    return "Deg";

    case kPZ_theta:
    return "Deg";

    case kE_theta:
    return "Deg";

    case kE_PZ:
    return "GeV";

    case kE_PT:
    return "GeV";

    case kVertex_Z_R:
    return "mm";

    default:
    std::cout << "ERROR: unknown Playlist name for Muon !" << std::endl;
    return "";
  };
}
////////////////////////////////////////
//
////////////////////////////////////////
std::string  GetMuon2DVar_xaxisUnits(Muon2DVar var2D) {
  switch (var2D) {

    case kPT_PZ:
    return "GeV";

    case kPT_theta:
    return "GeV";

    case kPZ_theta:
    return "GeV";

    case kE_theta:
    return "GeV";

    case kE_PZ:
    return "GeV";

    case kE_PT:
    return "GeV";

    case kVertex_Z_R:
    return "mm";

    default:
    std::cout << "ERROR: unknown Playlist name for Muon !" << std::endl;
    return "";
  };
}
////////////////////////////////////////
//
////////////////////////////////////////
std::string  GetMuon2DVar_TotalUnits(Muon2DVar var2D) {
  switch (var2D) {

    case kPT_PZ:
    return "[GeV^{2}]";

    case kPT_theta:
    return "[GeV Deg]";

    case kPZ_theta:
    return "[GeV Deg]";

    case kE_theta:
    return "[GeV Deg]";

    case kE_PZ:
    return "[GeV^{2}]";

    case kE_PT:
    return "[GeV^{2}]";

    case kVertex_Z_R:
    return "[mm^{2}]";

    default:
    std::cout << "ERROR: unknown Playlist name for Muon !" << std::endl;
    return "";
  };
}
///////////////////////////////////////
//
////////////////////////////////////////
std::string  GetMuon2DVar_XaxisTitle(Muon2DVar var2D) {
  switch (var2D) {
    case kPT_PZ:
    return "P_{#parallel} [GeV/c]";

    case kPT_theta:
    return "P_{T} [GeV/c]";

    case kPZ_theta:
    return "P_{#parallel} [GeV/c]";

    case kE_theta:
    return "E_{#mu} [GeV]";

    case kE_PZ:
    return "E_{#mu} [GeV]";

    case kE_PT:
    return "E_{#mu} [GeV]";

    case kVertex_Z_R:
    return "Vertex Z [mm]";

    default:
    std::cout << "ERROR: unknown Playlist name for Muon !" << std::endl;
    return "";
  };
}
////////////////////////////////////////
//
////////////////////////////////////////
std::string  GetMuon2DVar_XaxisTitle_noUntils(Muon2DVar var2D) {
  switch (var2D) {
    case kPT_PZ:
    return "P_{#parallel}";

    case kPT_theta:
    return "P_{T}";

    case kPZ_theta:
    return "P_{#parallel}";

    case kE_theta:
    return "E_{#mu}";

    case kE_PZ:
    return "E_{#mu}";

    case kE_PT:
    return "E_{#mu}";

    case kVertex_Z_R:
    return "Vertex Z";

    default:
    std::cout << "ERROR: unknown Playlist name for Muon !" << std::endl;
    return "";
  };
}
////////////////////////////////////////
//
////////////////////////////////////////
std::string  GetMuon2DVar_YaxisTitle(Muon2DVar var2D) {
  switch (var2D) {
    case kPT_PZ:
    return "P_{T} [GeV/c]";

    case kPT_theta:
    return "#theta_{#mu} [Degs]";

    case kPZ_theta:
    return "#theta_{#mu} [Degs]";

    case kE_theta:
    return "#theta_{#mu} [Degs]";

    case kE_PZ:
    return "P_{#parallel} [GeV/c]";

    case kE_PT:
    return "P_{T} [GeV/c]";

    case kVertex_Z_R:
    return "Vertex R [mm]";

    default:
    std::cout << "ERROR: unknown Playlist name for Muon !" << std::endl;
    return "";
  };
}
////////////////////////////////////////
//
////////////////////////////////////////
std::string  GetMuon2DVar_YaxisTitle_noUntils(Muon2DVar var2D) {
  switch (var2D) {
    case kPT_PZ:
    return "P_{T}";

    case kPT_theta:
    return "#theta_{#mu}";

    case kPZ_theta:
    return "#theta_{#mu}";

    case kE_theta:
    return "#theta_{#mu}";

    case kE_PZ:
    return "P_{#parallel}";

    case kE_PT:
    return "P_{T}";

    case kVertex_Z_R:
    return "Vertex R";

    default:
    std::cout << "ERROR: unknown Playlist name for Muon !" << std::endl;
    return "";
  };
}
////////////////////////////////////////
//
////////////////////////////////////////
std::string  GetMuon2DVar_ReponseHistTitle(Muon2DVar var2D) {
  switch (var2D) {
    case kPT_PZ:
    return "MnvR_Muon_PZ_PT";

    case kPT_theta:
    return "MnvR_Muon_PT_theta";

    case kPZ_theta:
    return "MnvR_Muon_PZ_theta";

    case kE_theta:
    return "MnvR_Muon_E_theta";

    case kE_PZ:
    return "MnvR_Muon_E_PZ";

    case kE_PT:
    return "MnvR_Muon_E_PT";

    case kVertex_Z_R:
    return "MnvR_cryoVertex_Z_R";

    default:
    std::cout << "ERROR: unknown Playlist name for Muon !" << std::endl;
    return "";
  };
}
////////////////////////////////////////
//
////////////////////////////////////////
std::vector<std::string>  GetMuon2DVar_ReponseHistTitle_vector(Muon2DVar var2D){
  std::vector<std::string> string_vector;

  auto name = GetMuon2DVar_ReponseHistTitle(var2D);

  std::string name_mig = name + "_migration";
  std::string name_reco = name + "_reco";
  std::string name_truth = name + "_truth";

  string_vector.push_back(name_mig);
  string_vector.push_back(name_reco);
  string_vector.push_back(name_truth);

  return string_vector;


}
////////////////////////////////////////
//
////////////////////////////////////////
std::vector<std::string>  GetMuon2DVar_ReponseHistTitle_vector_Daisy(Muon2DVar var2D, std::string Number){
  std::vector<std::string> string_vector;

  auto name = GetMuon2DVar_ReponseHistTitle(var2D);
  std::string name_mig = name + "_Daisy_" + Number + "_migration";
  std::string name_reco = name + "_Daisy_" + Number  + "_reco";
  std::string name_truth = name + "_Daisy_" + Number  + "_truth";

  string_vector.push_back(name_mig);
  string_vector.push_back(name_reco);
  string_vector.push_back(name_truth);

  return string_vector;


}
//////////////////////////////////////////////////////////////////////////
//GET Vertex Varibles
//////////////////////////////////////////////////////////////////////////
std::string Construct_string_Ending(bool isMiG,bool isStack,char *StackType,
   bool isYProj,int isFULLorEmpty, bool FirstorSecond ){

  if(isMiG==true){return "_MIGRATION";}

  std::string Project_Type_END;
  if(true==isYProj){Project_Type_END="_Yproj";}
  else{Project_Type_END="_Xproj";}

  std::string firstorScondName;
  if(FirstorSecond==true){firstorScondName="1";}
  else if (FirstorSecond==false){firstorScondName="2";}

  std::string CyroTank_Type;

  if(isFULLorEmpty==0){CyroTank_Type = "Full" ;}
  else if(isFULLorEmpty==1){CyroTank_Type = "Empty"; }
  else if(isFULLorEmpty==2){CyroTank_Type = "Full_Empty" ;}
  else{CyroTank_Type = "";}
  std::string Stack_name;
  if(isStack==true)
  {
    std::string stack_str(StackType);
    Stack_name = "_" +   stack_str + "_STACKS_" + CyroTank_Type + Project_Type_END;

  }
  else
  {
    Stack_name = "_" + CyroTank_Type + firstorScondName + Project_Type_END;
  }

  return Stack_name;

}
////////////////////////////////////////
//
////////////////////////////////////////
Playlist_MnvH2D_Map Constuct_MnvH2DMap_FromME_playlist_TFileMAP(ME_playlist_TFileMAP TFile_Map, const char* name ){
  Playlist_MnvH2D_Map MnvH2D_Map;
  std::cout<<"Constucting Hist map for Varible Name:" << name <<std::endl;
  std::cout<< "Input Map Has Size =  " << TFile_Map.size() <<std::endl;

  typename std::map<ME_helium_Playlists, TFile*>::iterator cat;

  for (cat = TFile_Map.begin(); cat != TFile_Map.end(); ++cat)
  {
    //auto hist = GetHist(cat->second, name);
    //MnvH2D *hist = (MnvH2D*)(cat->second)->Get(name);
    MnvH2D *hist = Get2DHist(*cat->second,  name);
    MnvH2D_Map.insert(std::make_pair(cat->first, hist));

  }//end of loop


  return MnvH2D_Map;
}//end of function
////////////////////////////////////////
//
////////////////////////////////////////
Playlist_HistFolio_MnvH2D_Map Constuct_HistFolio_MnvH2DMap_FromME_playlist_TFileMAP(ME_playlist_TFileMAP TFile_Map, const char* name ){
  Playlist_HistFolio_MnvH2D_Map HistFolio_MnvH2D_Map;
  std::cout<<"Constucting Hist Folio map for Varible Name:" << name <<std::endl;
  std::cout<< "Input Map Has Size =  " << TFile_Map.size() <<std::endl;

  typename std::map<ME_helium_Playlists, TFile*>::iterator cat;

  for (cat = TFile_Map.begin(); cat != TFile_Map.end(); ++cat)
  {
    std::cout<<"Loading HistFoloi from Playlist:"<< GetPlaylist_InitialName(cat->first)<< std::endl;
    PlotUtils::HistFolio<PlotUtils::MnvH2D> Stack(PlotUtils::LoadHistFolioFromFile<PlotUtils::MnvH2D>(*(cat->second), std::string(name)),"Stack");
    HistFolio_MnvH2D_Map.insert(std::make_pair(cat->first, Stack));
  }//end of loop

  return HistFolio_MnvH2D_Map;
}//end of function
////////////////////////////////////////
//
////////////////////////////////////////
TObjArray Combined_HistFolio_MnvH2D_Map(Playlist_HistFolio_MnvH2D_Map input_Map ){

  typename std::map<ME_helium_Playlists, PlotUtils::HistFolio<PlotUtils::MnvH2D>>::iterator HistFoliocat;

  auto Combined = (input_Map.begin()->second).GetHistArray();

  for(HistFoliocat = input_Map.begin(); HistFoliocat != input_Map.end(); ++HistFoliocat)
  {

    if(HistFoliocat->first != input_Map.begin()->first ){
      auto MC_Stack_array = (HistFoliocat->second).GetHistArray();
      AddFirst_toSecond_MnvH2D_Arrays(Combined, MC_Stack_array );

    }

  }

  return Combined;

}
////////////////////////////////////////
//
////////////////////////////////////////
TObjArray Combined_HistFolio_MnvH2D_Map(ME_playlist_TFileMAP TFile_Map, const char* name ,ME_helium_Playlists StartingPlaylist  ){

  PlotUtils::HistFolio<PlotUtils::MnvH2D> StackStart(PlotUtils::LoadHistFolioFromFile<PlotUtils::MnvH2D>(*(TFile_Map[StartingPlaylist]), std::string(name)),"Stack");
  auto Combined = StackStart.GetHistArray();
  typename std::map<ME_helium_Playlists, TFile*>::iterator TfileMap_iter;

  for(TfileMap_iter = TFile_Map.begin(); TfileMap_iter != TFile_Map.end(); ++TfileMap_iter)
  {
    if(TfileMap_iter->first==StartingPlaylist)continue;
    std::cout<<"Loading HistFolo from Playlist:"<< GetPlaylist_InitialName(TfileMap_iter->first)<< std::endl;
    PlotUtils::HistFolio<PlotUtils::MnvH2D> Stack_Add(PlotUtils::LoadHistFolioFromFile<PlotUtils::MnvH2D>(*(TfileMap_iter->second), std::string(name)),"Stack");
    std::cout<<"Finished"<<std::endl;
    auto MC_Stack_array = Stack_Add.GetHistArray();
    AddFirst_toSecond_MnvH2D_Arrays(Combined, MC_Stack_array );
  }

  return Combined;

}
////////////////////////////////////////
//
////////////////////////////////////////
TObjArray CombinedStack_MnvH2D_Map(ME_playlist_TFileMAP TFile_Map, std::string name,std::vector<std::string> StackNames, ME_helium_Playlists StartingPlaylist  ){

  TObjArray Combined = MakeTObjArray_2DHists(*(TFile_Map[StartingPlaylist]), name,  StackNames);
  int nEntries = Combined.GetEntries();
  Combined.SetOwner(kTRUE);
  TObjArray Combined_return;
  Combined_return.SetOwner(kTRUE);

  typename std::map<ME_helium_Playlists, TFile*>::iterator TfileMap_iter;

  for(int  Entry = 0; Entry < nEntries ;Entry++){
    for(TfileMap_iter = TFile_Map.begin(); TfileMap_iter != TFile_Map.end(); ++TfileMap_iter)
    {
      if(TfileMap_iter->first==StartingPlaylist)continue;
      std::string Hist_stack_signture = ((PlotUtils::MnvH2D*)Combined.At(Entry))->GetTitle();
      std::string histName = name + "_"  + Hist_stack_signture;
      MnvH2D *hist = Get2DHist(*TfileMap_iter->second,  histName);
      ((PlotUtils::MnvH2D*)Combined.At(Entry))->Add(hist);
    }
  }

  for(int  Entry = 0; Entry < nEntries ;Entry++){
    MnvH2D *hist =  ((PlotUtils::MnvH2D*)Combined.At(Entry))->Clone();
    Combined_return.Add(hist);
  }

  Combined.Delete();


  return Combined_return;

}
////////////////////////////////////////
//
////////////////////////////////////////
TObjArray MakeTObjArray_2DHists(TFile& f, std::string BaseName, std::vector<std::string> StackNames){

  TObjArray Combined_return;
  for(auto histname : StackNames){
    std::string finalname  = BaseName + "_" + histname;
    MnvH2D *hist = Get2DHist(f,  finalname);
    char histname_char[histname.length()+1];
    strcpy(histname_char, histname.c_str());
    hist->SetTitle(histname_char);
    Combined_return.Add(hist);
  }

  return Combined_return;

}

////////////////////////////////////////
//
////////////////////////////////////////

TObjArray ConstuctTObjArray_HistFolio_MnvH2DMap_FromME_playlist_TFileMAP(ME_playlist_TFileMAP TFile_Map, const char* name ){

  return Combined_HistFolio_MnvH2D_Map(Constuct_HistFolio_MnvH2DMap_FromME_playlist_TFileMAP( TFile_Map,  name ));
}

////////////////////////////////////////
//
////////////////////////////////////////

TObjArray ConstuctTObjArray_HistFolio_MnvH2DMap_FromME_playlist_TFileMAP_Full_Empty(ME_playlist_TFileMAP TFile_MapFull,
   ME_playlist_TFileMAP TFile_MapEmpty,const char* name,
    double MC_ScalerFulltoFullData,double MC_ScalerEmptytoFullData  ){
    std::cout<<"ConstuctTObjArray_HistFolio_MnvH2DMap_FromME_playlist_TFileMAP_Full_Empty:2"<<std::endl;
    auto Empty_ObjArray =  ConstuctTObjArray_HistFolio_MnvH2DMap_FromME_playlist_TFileMAP( TFile_MapEmpty,  name );
    std::cout<<"ConstuctTObjArray_HistFolio_MnvH2DMap_FromME_playlist_TFileMAP_Full_Empty:1"<<std::endl;
    auto Full_ObjArray =  ConstuctTObjArray_HistFolio_MnvH2DMap_FromME_playlist_TFileMAP( TFile_MapFull,  name );
    std::cout<<"ConstuctTObjArray_HistFolio_MnvH2DMap_FromME_playlist_TFileMAP_Full_Empty:3"<<std::endl;
    Scale_MnvH2D_Array(Full_ObjArray, MC_ScalerFulltoFullData);
    std::cout<<"ConstuctTObjArray_HistFolio_MnvH2DMap_FromME_playlist_TFileMAP_Full_Empty:4"<<std::endl;
    Scale_MnvH2D_Array(Empty_ObjArray, MC_ScalerEmptytoFullData);
    std::cout<<"ConstuctTObjArray_HistFolio_MnvH2DMap_FromME_playlist_TFileMAP_Full_Empty:5"<<std::endl;
    SubractSecond_FromFirst_MnvH2D_Arrays(Full_ObjArray,  Empty_ObjArray);

    return Full_ObjArray;
}

////////////////////////////////////////
//
////////////////////////////////////////
void Scale_MnvH2D_Array(TObjArray  HistArray , double Scaler){

  unsigned int i = 0;
  for(auto cat : HistArray) {
    ((PlotUtils::MnvH2D*)HistArray.At(i))->Scale(Scaler);
    i++;
  }
}
////////////////////////////////////////
//
////////////////////////////////////////
void BinWidthNorm_MnvH2D_Array(const TObjArray HistArray ){
  std::cout<<"Trying to BinWidth Normalize MnvH2D Hist arrays"<<std::endl;

  unsigned int i = 0;
  for(auto cat : HistArray) {
    ((PlotUtils::MnvH2D*)HistArray.At(i))->Scale(1.0,"width");
    i++;
  }
}
////////////////////////////////////////
//
////////////////////////////////////////
void AddFirst_toSecond_MnvH2D_Arrays(const TObjArray HistArray1 , const TObjArray HistArray2){
  std::cout<<"Trying to Add MnvH2D Hist arrays"<<std::endl;
  unsigned int i = 0;
  for(auto cat : HistArray1) {
    ((PlotUtils::MnvH2D*)HistArray1.At(i))->Add((PlotUtils::MnvH2D*)HistArray2.At(i),1.0);
    i++;
  }
}
////////////////////////////////////////
//
////////////////////////////////////////
void SubractSecond_FromFirst_MnvH2D_Arrays( TObjArray HistArray1 ,  TObjArray HistArray2){
  std::cout<<"Trying to SubTract MnvH2D Hist arrays"<<std::endl;
  unsigned int i = 0;
  for(auto cat : HistArray1) {
    ((PlotUtils::MnvH2D*)HistArray1.At(i))->Add((PlotUtils::MnvH2D*)HistArray2.At(i),-1.0);
    i++;
  }
}
////////////////////////////////////////
//
////////////////////////////////////////
CrossSection_2DhistNames Constuct_2Dcrosssection_Histname(Muon2DVar var2D){

  CrossSection_2DhistNames crosssection_hist_Names;

  crosssection_hist_Names.Muon2DType = var2D;

  auto string_vector = GetMuon2DVar_ReponseHistTitle_vector(var2D);
  crosssection_hist_Names.Data_hist_name = GetMuon2DVarHist_DATAName(var2D);
  crosssection_hist_Names.hist_Eff_denominator_name = GetMuon2DVarHistName(var2D) + "_TRUE";
  crosssection_hist_Names.hist_Eff_numerator_name = GetMuon2DVarHistName( var2D) + "_TRUE_RECO";
  crosssection_hist_Names.MnvReponse_Name_Mig  = string_vector.at(0);
  crosssection_hist_Names.MnvReponse_Name_reco = string_vector.at(1);
  crosssection_hist_Names.MnvReponse_Name_true = string_vector.at(2);

  crosssection_hist_Names.hist_Flux_name =  GetMuon2DVarHistName( var2D) + "_FluxIntegrated";
  crosssection_hist_Names.RECO_MC_name =  GetMuon2DVarHistName(var2D);
  crosssection_hist_Names.RECO_MC_BG_name = GetMuon2DVarHistName(var2D) + "_BG";
  return crosssection_hist_Names;
}
////////////////////////////////////////
//
////////////////////////////////////////
CrossSection_2DhistNames Constuct_2Dcrosssection_Histname_Daisy(Muon2DVar var2D, std::string petalNumber ){

  CrossSection_2DhistNames crosssection_hist_Names;

  crosssection_hist_Names.Muon2DType = var2D;
  std::string Daisy_name = "_Daisy_" + petalNumber;

  auto string_vector = GetMuon2DVar_ReponseHistTitle_vector_Daisy(var2D, petalNumber);
  crosssection_hist_Names.Data_hist_name = GetMuon2DVarHist_DATAName(var2D) + Daisy_name;
  crosssection_hist_Names.hist_Eff_denominator_name = GetMuon2DVarHistName(var2D) + "_TRUE_Daisy_" + petalNumber;
  crosssection_hist_Names.hist_Eff_numerator_name = GetMuon2DVarHistName( var2D) + "_TRUE_RECO_Daisy_" + petalNumber;
  crosssection_hist_Names.MnvReponse_Name_Mig  = string_vector.at(0);
  crosssection_hist_Names.MnvReponse_Name_reco = string_vector.at(1);
  crosssection_hist_Names.MnvReponse_Name_true = string_vector.at(2);

  crosssection_hist_Names.hist_Flux_name =  GetMuon2DVarHistName( var2D) + "_FluxIntegrated";
  crosssection_hist_Names.RECO_MC_name =  GetMuon2DVarHistName(var2D) + Daisy_name ;
  crosssection_hist_Names.RECO_MC_BG_name = GetMuon2DVarHistName(var2D) + "_BG_Daisy_" +petalNumber ;
  return crosssection_hist_Names;
}
////////////////////////////////////////
//
////////////////////////////////////////
CrossSection_2DhistNames Constuct_2Dcrosssection_Histname(Muon2DVar var2D, std::string ExtraString){

  CrossSection_2DhistNames crosssection_hist_Names;

  crosssection_hist_Names.Muon2DType = var2D;

  auto string_vector = GetMuon2DVar_ReponseHistTitle_vector(var2D);
  crosssection_hist_Names.Data_hist_name = GetMuon2DVarHist_DATAName(var2D) +  ExtraString;
  crosssection_hist_Names.hist_Eff_denominator_name = GetMuon2DVarHistName(var2D) + "_TRUE";
  crosssection_hist_Names.hist_Eff_numerator_name = GetMuon2DVarHistName( var2D) + "_TRUE_RECO";
  crosssection_hist_Names.MnvReponse_Name_Mig  = string_vector.at(0);
  crosssection_hist_Names.MnvReponse_Name_reco = string_vector.at(1);
  crosssection_hist_Names.MnvReponse_Name_true = string_vector.at(2);

  crosssection_hist_Names.hist_Flux_name =  GetMuon2DVarHistName( var2D) + "_FluxIntegrated";
  crosssection_hist_Names.RECO_MC_name =  GetMuon2DVarHistName(var2D) +  ExtraString;
  return crosssection_hist_Names;

}
////////////////////////////////////////
//
////////////////////////////////////////
void Print_2Dcrosssection_Histname(CrossSection_2DhistNames crosssection_hist_Names){

  std::cout<< "printing out names of 2D Cross section hists"<< std::endl;
  std::cout <<"Data_hist_name =  " << crosssection_hist_Names.Data_hist_name <<std::endl;
  std::cout <<"hist_Eff_denominator_name =  " << crosssection_hist_Names.hist_Eff_denominator_name <<std::endl;
  std::cout <<"hist_Eff_numerator_name =  " << crosssection_hist_Names.hist_Eff_numerator_name <<std::endl;
  std::cout <<"MnvReponse_Name_Mig =  " << crosssection_hist_Names.MnvReponse_Name_Mig <<std::endl;
  std::cout <<"MnvReponse_Name_reco =  " << crosssection_hist_Names.MnvReponse_Name_reco <<std::endl;
  std::cout <<"MnvReponse_Name_true =  " << crosssection_hist_Names.MnvReponse_Name_true <<std::endl;
  std::cout <<"Flux_name =  " << crosssection_hist_Names.hist_Flux_name <<std::endl;
  std::cout <<"RECO Name =  " << crosssection_hist_Names.RECO_MC_name <<std::endl;
  std::cout <<"RECO BG Name =  " << crosssection_hist_Names.RECO_MC_BG_name <<std::endl;

}

////////////////////////////////////////
//
////////////////////////////////////////
CrossSection2D_Hist Constuct_2Dcrosssection_Hists(CrossSection_2DhistNames Names,
   TFile *inputFile_RECO_mc,TFile *inputFile_TRUE_mc, TFile *inputFile_data ){

  CrossSection2D_Hist Hist_struct;

  MnvH2D *hist_Flux=nullptr;
  MnvH2D *hist_DATA=nullptr;
  MnvH2D *hist_numerator=nullptr;
  MnvH2D *hist_demonator=nullptr;
  MnvH2D *hist_mvnreponse_Mig=nullptr;
  MnvH2D *hist_mvnreponse_reco=nullptr;
  MnvH2D *hist_mvnreponse_true=nullptr;
  MnvH2D *hist_RECO=nullptr;
  MnvH2D *hist_RECO_BG=nullptr;

  Hist_struct.Muon2DType = Names.Muon2DType;


  hist_Flux = Get2DHist(*inputFile_RECO_mc,  Names.hist_Flux_name.c_str());

  char *Data_hist_name_char = new char[Names.Data_hist_name.length() + 1];
  strcpy(Data_hist_name_char, Names.Data_hist_name.c_str());
  //std::cout<<"looking for data hist with name = "<< Data_hist_name_char<<std::endl;
  hist_DATA = Get2DHist(*inputFile_data, Names.Data_hist_name.c_str());
  //std::cout<<"Found for data hist with name = "<< Data_hist_name_char<<std::endl;

  //std::cout<<"looking for Reco hist with name = "<< Names.hist_Eff_numerator_name<<std::endl;
  char *numerator_name_char = new char[Names.hist_Eff_numerator_name.length() + 1];
  strcpy(numerator_name_char, Names.hist_Eff_numerator_name.c_str());
  hist_numerator =  Get2DHist(*inputFile_RECO_mc, Names.hist_Eff_numerator_name.c_str());
  //std::cout<<"Found Reco hist with name = "<< numerator_name_char<<std::endl;

  char *hist_Eff_denominator_name_char = new char[Names.hist_Eff_denominator_name.length() + 1];
  strcpy(hist_Eff_denominator_name_char, Names.hist_Eff_denominator_name.c_str());
  //std::cout<<"looking for Eff Dem hist with name = "<< hist_Eff_denominator_name_char<<std::endl;
  hist_demonator =  Get2DHist(*inputFile_TRUE_mc, Names.hist_Eff_denominator_name.c_str());

  //std::cout<<"Found Eff Dem hist with name = "<< hist_Eff_denominator_name_char<<std::endl;

  char *Migration_name_char = new char[Names.MnvReponse_Name_Mig.length() + 1];
  strcpy(Migration_name_char, Names.MnvReponse_Name_Mig.c_str());
  //std::cout<<"looking for MnvReponse_Name_Mig = "<< Migration_name_char<<std::endl;
  //std::cout<<"Found for MnvReponse_Name_Mig = "<< Migration_name_char<<std::endl;
  hist_mvnreponse_Mig =  Get2DHist(*inputFile_RECO_mc, Names.MnvReponse_Name_Mig.c_str());


  char *mvnreponse_Reco_name_char = new char[Names.MnvReponse_Name_reco.length() + 1];
  strcpy(mvnreponse_Reco_name_char, Names.MnvReponse_Name_reco.c_str());
  //std::cout<<"looking for MnvReponse_Name_reco = "<< mvnreponse_Reco_name_char<<std::endl;
  //std::cout<<"Found MnvReponse_Name_reco = "<< mvnreponse_Reco_name_char<<std::endl;
  hist_mvnreponse_reco =  Get2DHist(*inputFile_RECO_mc, Names.MnvReponse_Name_reco.c_str());


  char *mvnreponse_TRUE_name_char = new char[Names.MnvReponse_Name_true.length() + 1];
  strcpy(mvnreponse_TRUE_name_char, Names.MnvReponse_Name_true.c_str());
  //std::cout<<"looking for MnvReponse_Name_true = "<< mvnreponse_TRUE_name_char<<std::endl;
  //std::cout<<"Found MnvReponse_Name_true = "<< mvnreponse_TRUE_name_char<<std::endl;
  hist_mvnreponse_true =  Get2DHist(*inputFile_RECO_mc,Names.MnvReponse_Name_true.c_str());

  char *RECO_name_char = new char[Names.RECO_MC_name.length() + 1];
  strcpy(RECO_name_char, Names.RECO_MC_name.c_str());
  //std::cout<<"looking for RECO Name = "<< RECO_name_char<<std::endl;
  hist_RECO =  Get2DHist(*inputFile_RECO_mc, Names.RECO_MC_name.c_str());

  //std::cout<<"Found RECO MC = "<< RECO_name_char<<std::endl;


  char *RECO_BG_name_char = new char[Names.RECO_MC_BG_name.length() + 1];
  strcpy(RECO_BG_name_char, Names.RECO_MC_BG_name.c_str());
  //std::cout<<"looking for RECO Name = "<< RECO_BG_name_char<<std::endl;
  hist_RECO_BG =  Get2DHist(*inputFile_RECO_mc, Names.RECO_MC_BG_name.c_str());
  //std::cout<<"Found RECO BG MC = "<< RECO_name_char<<std::endl;



  //std::cout<< "Adding Error bands to " << hist_Eff_denominator_name_char<<  " and "<< Data_hist_name_char<<std::endl;
  //std::cout<<"trying to get universe names"<< std::endl;

  int nXBins  = hist_numerator->GetXaxis()->GetNbins();

  //std::cout<< " nXBins = " << nXBins << std::endl;

  hist_demonator->AddMissingErrorBandsAndFillWithCV(*hist_numerator); // this function should work for 2d
  //std::cout<<"Finished adding to Demonator "<< std::endl;
  //hist_DATA->AddMissingErrorBandsAndFillWithCV(*hist_numerator); // took off for now will add back
  //std::cout<<"Finished adding to data "<< std::endl;
  hist_mvnreponse_true->AddMissingErrorBandsAndFillWithCV(*hist_numerator);
  //hist_Flux->AddMissingErrorBandsAndFillWithCV(*hist_numerator);
  //std::cout<<"Finished adding to Demonator "<< std::endl;


  Hist_struct.h_flux = hist_Flux;
  Hist_struct.h_Data_Signal = hist_DATA;
  Hist_struct.h_effNum = hist_numerator;
  Hist_struct.h_effDom = hist_demonator;
  Hist_struct.h_mvnreponse_Mig = hist_mvnreponse_Mig;
  Hist_struct.h_mvnreponse_RECO = hist_mvnreponse_reco;
  Hist_struct.h_mvnreponse_TRUE = hist_mvnreponse_true;
  Hist_struct.h_RECO = hist_RECO;
  Hist_struct.h_RECO_BG =hist_RECO_BG;
  return Hist_struct;

}

////////////////////////////////////////
//
////////////////////////////////////////

ME_playlist_2DCrossSection_MAP Constuct_2Dcrosssection_Hists_PlaylistMap(CrossSection_2DhistNames Names,
                                                         ME_playlist_TFileMAP MC_RECO_TfileMap,
                                                         ME_playlist_TFileMAP MC_TRUTH_TfileMap,
                                                         ME_playlist_TFileMAP Data_TfileMap )
{
  std::cout<< "Constuct playlist_2DCrossSection_MAP"<< std::endl;
ME_playlist_2DCrossSection_MAP OutPut_Hist_Map;


  typename std::map<ME_helium_Playlists, TFile*>::const_iterator MC_RECO_it;
  typename std::map<ME_helium_Playlists, TFile*>::const_iterator MC_TRUTH_it;
  typename std::map<ME_helium_Playlists, TFile*>::const_iterator Data_it;

  for (MC_RECO_it = MC_RECO_TfileMap.begin(), Data_it = Data_TfileMap.begin(), MC_TRUTH_it= MC_TRUTH_TfileMap.begin() ; MC_RECO_it != MC_RECO_TfileMap.end(); ++MC_RECO_it, ++MC_TRUTH_it, ++Data_it)
  {
    if(MC_RECO_it->first != MC_TRUTH_it->first || Data_it->first != MC_TRUTH_it->first){assert(("The TFiles making ME_playlist_CrossSection_MAP do not Match for 2D ", false));}
    std::cout<< " Playlist : " << GetPlaylist_InitialName(MC_RECO_it->first) << std::endl;
    CrossSection2D_Hist CrossSection_Hist_forplaylist = Constuct_2Dcrosssection_Hists(Names, MC_RECO_it->second, MC_TRUTH_it->second, Data_it->second);
    OutPut_Hist_Map.insert(std::make_pair(MC_RECO_it->first, CrossSection_Hist_forplaylist));
  }

return OutPut_Hist_Map;

}//end function
////////////////////////////////////////
//
////////////////////////////////////////
Interaction_type_MnvH2D_Map AddInteraction2DHistMap_DISbreakdown(TFile& file, std::string input_hist_name, std::string extra){

  Interaction_type_MnvH2D_Map Interaction_HistMap_output;

  std::string Hist_name = input_hist_name + "_Interaction"+ extra +"_QE";
  MnvH2D* h_elastic =  Get2DHist(file, Hist_name );
  Interaction_HistMap_output.insert ( std::pair<Interaction_type, PlotUtils::MnvH2D*>(kElastic,h_elastic) );

  Hist_name = input_hist_name + "_Interaction"+ extra +"_#DeltaRes";
  MnvH2D* h_deltaRES =  Get2DHist(file, Hist_name );
  Interaction_HistMap_output.insert ( std::pair<Interaction_type, PlotUtils::MnvH2D*>(kdeltaRES,h_deltaRES) );

  Hist_name = input_hist_name + "_Interaction"+ extra +"_HeavierRes";
  MnvH2D* h_HeavierRes =  Get2DHist(file, Hist_name );
  Interaction_HistMap_output.insert ( std::pair<Interaction_type, PlotUtils::MnvH2D*>(kHeavierRES, h_HeavierRes) );

  Hist_name = input_hist_name + "_Interaction"+ extra +"_2p2h";
  MnvH2D* h_2p2h =  Get2DHist(file, Hist_name );
  Interaction_HistMap_output.insert ( std::pair<Interaction_type, PlotUtils::MnvH2D*>(k2p2h,h_2p2h) );

  Hist_name = input_hist_name + "_Interaction"+ extra +"_SoftDIS";
  MnvH2D* h_DISSoft =  Get2DHist(file, Hist_name );
  Interaction_HistMap_output.insert ( std::pair<Interaction_type, PlotUtils::MnvH2D*>(kDISSoft,h_DISSoft) );


  Hist_name = input_hist_name + "_Interaction"+ extra +"_HardDIS";
  MnvH2D* h_DISHard =  Get2DHist(file, Hist_name );
  Interaction_HistMap_output.insert ( std::pair<Interaction_type, PlotUtils::MnvH2D*>(kDISHard,h_DISHard) );

  Hist_name = input_hist_name + "_Interaction"+ extra +"_SIS";
  MnvH2D* h_SIS =  Get2DHist(file, Hist_name );
  Interaction_HistMap_output.insert ( std::pair<Interaction_type, PlotUtils::MnvH2D*>(kDISSIS,h_SIS) );

  Hist_name = input_hist_name + "_Interaction"+ extra +"_None";
  MnvH2D* h_Interaction_NONE =  Get2DHist(file, Hist_name );
  Interaction_HistMap_output.insert ( std::pair<Interaction_type, PlotUtils::MnvH2D*>(kInteraction_NONE,h_Interaction_NONE) );

  Hist_name = input_hist_name + "_Interaction"+ extra +"_Other";
  MnvH2D* h_Interaction_OTHER =  Get2DHist(file, Hist_name );
  Interaction_HistMap_output.insert ( std::pair<Interaction_type, PlotUtils::MnvH2D*>(kInteraction_OTHER,h_Interaction_OTHER) );


return Interaction_HistMap_output;
}
////////////////////////////////////////
//
////////////////////////////////////////
void AddInteraction2DHistMap_DISbreakdown(ME_playlist_2DCrossSection_MAP &Hist_Map, ME_playlist_TFileMAP MC_TRUTH_TfileMap, std::string input_hist_name, std::string extra_name){


  typename std::map<ME_helium_Playlists, TFile*>::const_iterator MC_TRUTH_it;
  typename std::map<ME_helium_Playlists, CrossSection2D_Hist>::const_iterator Hist_Map_it;
  for (MC_TRUTH_it= MC_TRUTH_TfileMap.begin(), Hist_Map_it= Hist_Map.begin() ; MC_TRUTH_it != MC_TRUTH_TfileMap.end();  ++MC_TRUTH_it,++Hist_Map_it){

    if(Hist_Map_it->first != MC_TRUTH_it->first){std::cout<<"Maps not in same Playlist order: need to fix" << std::endl; assert(false);}
    Interaction_type_MnvH2D_Map Interaction_HistMap_output = AddInteraction2DHistMap_DISbreakdown(*MC_TRUTH_it->second, input_hist_name, extra_name);

    Hist_Map[Hist_Map_it->first].Interaction_HistMap = Interaction_HistMap_output;

  }
}
////////////////////////////////////////
//
////////////////////////////////////////
CrossSection2D_Hist Combine_2Dcrosssection_Hists_PlaylistMap(ME_playlist_2DCrossSection_MAP inputMap, ME_helium_Playlists playlist_combine_too ){

  CrossSection2D_Hist output_hist;

  MnvH2D *hist_Flux=nullptr;
  MnvH2D *hist_DATA=nullptr;
  MnvH2D *hist_numerator=nullptr;
  MnvH2D *hist_demonator=nullptr;
  MnvH2D *hist_mvnreponse_Mig=nullptr;
  MnvH2D *hist_mvnreponse_reco=nullptr;
  MnvH2D *hist_mvnreponse_true=nullptr;

  typename std::map<ME_helium_Playlists, CrossSection2D_Hist>::const_iterator inputMap_it;

  hist_DATA = inputMap[playlist_combine_too].h_Data_Signal;
  hist_numerator = inputMap[playlist_combine_too].h_effNum;
  hist_demonator = inputMap[playlist_combine_too].h_effDom;
  hist_mvnreponse_Mig= inputMap[playlist_combine_too].h_mvnreponse_Mig;
  hist_mvnreponse_reco= inputMap[playlist_combine_too].h_mvnreponse_RECO;
  hist_mvnreponse_true= inputMap[playlist_combine_too].h_mvnreponse_TRUE;
  hist_Flux= inputMap[playlist_combine_too].h_flux;


  for (inputMap_it = inputMap.begin(); inputMap_it != inputMap.end(); ++inputMap_it){

    if(inputMap_it->first == playlist_combine_too ) continue;

    hist_DATA->Add(inputMap_it->second.h_Data_Signal);
    hist_numerator->Add(inputMap_it->second.h_effNum);
    hist_demonator->Add(inputMap_it->second.h_effDom);
    hist_mvnreponse_Mig->Add(inputMap_it->second.h_mvnreponse_Mig);
    hist_mvnreponse_reco->Add(inputMap_it->second.h_mvnreponse_RECO);
    hist_mvnreponse_true->Add(inputMap_it->second.h_mvnreponse_TRUE);

  } // end of loop

    output_hist.h_flux = hist_Flux;
    output_hist.h_Data_Signal = hist_DATA;
    output_hist.h_effNum = hist_numerator;
    output_hist.h_effDom = hist_demonator;
    output_hist.h_mvnreponse_Mig = hist_mvnreponse_Mig;
    output_hist.h_mvnreponse_RECO = hist_mvnreponse_reco;
    output_hist.h_mvnreponse_TRUE = hist_mvnreponse_true;


return output_hist;

}//end of function
////////////////////////////////////////
//
////////////////////////////////////////
CrossSection2D_Hist Combine_crosssection_Hists_PlaylistMap_includeInteraction(ME_playlist_2DCrossSection_MAP inputMap, ME_helium_Playlists playlist_combine_too ){

  CrossSection2D_Hist output_hist;
  typename std::map<ME_helium_Playlists, CrossSection2D_Hist>::const_iterator inputMap_it;

  MnvH2D *hist_Flux=nullptr;
  MnvH2D *hist_DATA=nullptr;
  MnvH2D *hist_numerator=nullptr;
  MnvH2D *hist_demonator=nullptr;
  MnvH2D *hist_mvnreponse_Mig=nullptr;
  MnvH2D *hist_mvnreponse_reco=nullptr;
  MnvH2D *hist_mvnreponse_true=nullptr;
  Interaction_type_MnvH2D_Map Interaction_HistMap;
  std::cout<< "First hist from playlist: "<< GetPlaylist_InitialName(playlist_combine_too)<< std::endl;
  hist_DATA = inputMap[playlist_combine_too].h_Data_Signal;
  hist_numerator = inputMap[playlist_combine_too].h_effNum;
  hist_demonator = inputMap[playlist_combine_too].h_effDom;
  hist_mvnreponse_Mig= inputMap[playlist_combine_too].h_mvnreponse_Mig;
  hist_mvnreponse_reco= inputMap[playlist_combine_too].h_mvnreponse_RECO;
  hist_mvnreponse_true= inputMap[playlist_combine_too].h_mvnreponse_TRUE;
  hist_Flux= inputMap[playlist_combine_too].h_flux;
  Interaction_HistMap = inputMap[playlist_combine_too].Interaction_HistMap;


  for (inputMap_it = inputMap.begin(); inputMap_it != inputMap.end(); ++inputMap_it){

    if(inputMap_it->first == playlist_combine_too ) continue;
    std::cout<< " Playlist: "<< GetPlaylist_InitialName(inputMap_it->first)<< std::endl;
    hist_DATA->Add(inputMap_it->second.h_Data_Signal);
    hist_numerator->Add(inputMap_it->second.h_effNum);
    hist_demonator->Add(inputMap_it->second.h_effDom);
    hist_mvnreponse_Mig->Add(inputMap_it->second.h_mvnreponse_Mig);
    hist_mvnreponse_reco->Add(inputMap_it->second.h_mvnreponse_RECO);
    hist_mvnreponse_true->Add(inputMap_it->second.h_mvnreponse_TRUE);



    Interaction_HistMap[kElastic]->Add(inputMap[inputMap_it->first].Interaction_HistMap[kElastic]);
    Interaction_HistMap[kRes_Coh_Pion]->Add(inputMap[inputMap_it->first].Interaction_HistMap[kRes_Coh_Pion]);
    Interaction_HistMap[k2p2h]->Add(inputMap[inputMap_it->first].Interaction_HistMap[k2p2h]);
    Interaction_HistMap[kDIS]->Add(inputMap[inputMap_it->first].Interaction_HistMap[kDIS]);
    Interaction_HistMap[kInteraction_NONE]->Add(inputMap[inputMap_it->first].Interaction_HistMap[kInteraction_NONE]);
    Interaction_HistMap[kInteraction_OTHER]->Add(inputMap[inputMap_it->first].Interaction_HistMap[kInteraction_OTHER]);

  } // end of loop

  output_hist.h_flux = hist_Flux;
  output_hist.h_Data_Signal = hist_DATA;
  output_hist.h_effNum = hist_numerator;
  output_hist.h_effDom = hist_demonator;
  output_hist.h_mvnreponse_Mig = hist_mvnreponse_Mig;
  output_hist.h_mvnreponse_RECO = hist_mvnreponse_reco;
  output_hist.h_mvnreponse_TRUE = hist_mvnreponse_true;
  output_hist.Interaction_HistMap = Interaction_HistMap;

    return output_hist;

}//end of function
////////////////////////////////////////
//
////////////////////////////////////////
CrossSection2D_Hist Combine_2Dcrosssection_Hists_PlaylistMap_includeInteraction_DISbreakdown(ME_playlist_2DCrossSection_MAP inputMap, ME_helium_Playlists playlist_combine_too ){

  CrossSection2D_Hist output_hist;
  typename std::map<ME_helium_Playlists, CrossSection2D_Hist>::const_iterator inputMap_it;

  MnvH2D *hist_Flux=nullptr;
  MnvH2D *hist_DATA=nullptr;
  MnvH2D *hist_numerator=nullptr;
  MnvH2D *hist_demonator=nullptr;
  MnvH2D *hist_mvnreponse_Mig=nullptr;
  MnvH2D *hist_mvnreponse_reco=nullptr;
  MnvH2D *hist_mvnreponse_true=nullptr;
  MnvH2D *hist_RECO=nullptr;
  MnvH2D *hist_RECO_BG=nullptr;

  Interaction_type_MnvH2D_Map Interaction_HistMap;
  std::cout<< "First hist from playlist: "<< GetPlaylist_InitialName(playlist_combine_too)<< std::endl;
  hist_DATA = inputMap[playlist_combine_too].h_Data_Signal;
  hist_numerator = inputMap[playlist_combine_too].h_effNum;
  hist_demonator = inputMap[playlist_combine_too].h_effDom;
  hist_mvnreponse_Mig= inputMap[playlist_combine_too].h_mvnreponse_Mig;
  hist_mvnreponse_reco= inputMap[playlist_combine_too].h_mvnreponse_RECO;
  hist_mvnreponse_true= inputMap[playlist_combine_too].h_mvnreponse_TRUE;
  hist_Flux= inputMap[playlist_combine_too].h_flux;
  Interaction_HistMap = inputMap[playlist_combine_too].Interaction_HistMap;
  hist_RECO = inputMap[playlist_combine_too].h_RECO;
  hist_RECO_BG= inputMap[playlist_combine_too].h_RECO_BG;
  for (inputMap_it = inputMap.begin(); inputMap_it != inputMap.end(); ++inputMap_it){

    if(inputMap_it->first == playlist_combine_too ) continue;
    std::cout<< " Playlist: "<< GetPlaylist_InitialName(inputMap_it->first)<< std::endl;
    hist_DATA->Add(inputMap_it->second.h_Data_Signal);
    hist_numerator->Add(inputMap_it->second.h_effNum);
    hist_demonator->Add(inputMap_it->second.h_effDom);
    hist_mvnreponse_Mig->Add(inputMap_it->second.h_mvnreponse_Mig);
    hist_mvnreponse_reco->Add(inputMap_it->second.h_mvnreponse_RECO);
    hist_mvnreponse_true->Add(inputMap_it->second.h_mvnreponse_TRUE);
    hist_RECO->Add(inputMap_it->second.h_RECO);
    hist_RECO_BG->Add(inputMap_it->second.h_RECO_BG);

    Interaction_HistMap[kElastic]->Add(inputMap[inputMap_it->first].Interaction_HistMap[kElastic]);
    Interaction_HistMap[kHeavierRES]->Add(inputMap[inputMap_it->first].Interaction_HistMap[kHeavierRES]);
    Interaction_HistMap[kdeltaRES]->Add(inputMap[inputMap_it->first].Interaction_HistMap[kdeltaRES]);
    Interaction_HistMap[k2p2h]->Add(inputMap[inputMap_it->first].Interaction_HistMap[k2p2h]);
    Interaction_HistMap[kDISSIS]->Add(inputMap[inputMap_it->first].Interaction_HistMap[kDISSIS]);
    Interaction_HistMap[kDISSoft]->Add(inputMap[inputMap_it->first].Interaction_HistMap[kDISSoft]);
    Interaction_HistMap[kDISHard]->Add(inputMap[inputMap_it->first].Interaction_HistMap[kDISHard]);

    Interaction_HistMap[kInteraction_NONE]->Add(inputMap[inputMap_it->first].Interaction_HistMap[kInteraction_NONE]);
    Interaction_HistMap[kInteraction_OTHER]->Add(inputMap[inputMap_it->first].Interaction_HistMap[kInteraction_OTHER]);



  } // end of loop

  output_hist.h_flux = hist_Flux;
  output_hist.h_Data_Signal = hist_DATA;
  output_hist.h_effNum = hist_numerator;
  output_hist.h_effDom = hist_demonator;
  output_hist.h_mvnreponse_Mig = hist_mvnreponse_Mig;
  output_hist.h_mvnreponse_RECO = hist_mvnreponse_reco;
  output_hist.h_mvnreponse_TRUE = hist_mvnreponse_true;
  output_hist.Interaction_HistMap = Interaction_HistMap;
  output_hist.h_RECO = hist_RECO;
  output_hist.h_RECO_BG = hist_RECO_BG;
    return output_hist;

}
//end of function
////////////////////////////////////////
//
////////////////////////////////////////
void Check2D_NSignalBins(CrossSection2D_Hist &Constuct_crosssection_Hists,char* Name ){

  int NBins_Eff_numX = Constuct_crosssection_Hists.h_effNum->GetNbinsX();
  int NBins_Dom_numX = Constuct_crosssection_Hists.h_effDom->GetNbinsX();
  int NBins_data_numX = Constuct_crosssection_Hists.h_Data_Signal->GetNbinsX();


  int NBins_Eff_numY = Constuct_crosssection_Hists.h_effNum->GetNbinsY();
  int NBins_Dom_numY = Constuct_crosssection_Hists.h_effDom->GetNbinsY();

  int NBins_data_numY = Constuct_crosssection_Hists.h_Data_Signal->GetNbinsY();

std::cout<<"checking bins for :"<<Name << std::endl;

  std::vector<int> myvectorX;
  myvectorX.push_back(NBins_Eff_numX);
  myvectorX.push_back(NBins_Dom_numX);
  myvectorX.push_back(NBins_data_numX);

  std::cout<<"NBins_Eff_numX = " << NBins_Eff_numX << std::endl;
  std::cout<<"NBins_Dom_numX = " << NBins_Dom_numX << std::endl;
  std::cout<<"NBins_data_numX = " << NBins_data_numX << std::endl;


  std::cout<<"NBins_Eff_numY = " << NBins_Eff_numY << std::endl;
  std::cout<<"NBins_Dom_numY = " << NBins_Dom_numY << std::endl;
  std::cout<<"NBins_data_numY = " << NBins_data_numY << std::endl;


  std::vector<int> myvectorY;
  myvectorY.push_back(NBins_Eff_numY);
  myvectorY.push_back(NBins_Dom_numY);
  myvectorY.push_back(NBins_data_numY);


  if ( std::adjacent_find( myvectorX.begin(), myvectorX.end(), std::not_equal_to<int>() ) == myvectorX.end() )
  {
    std::cout << "All Bins are equal each other for  = " << Name<< std::endl;
  }
  else{
    std::cout << "Opps Bins are NOT Equal for Cross- Section Hists " << Name<< std::endl;
    std::cout << " NBins_Eff_numX = " << NBins_Eff_numX << std::endl;
    std::cout << " NBins_Dom_numX = " << NBins_Dom_numX << std::endl;
    std::cout << " NBins_data_numX = " << NBins_data_numX << std::endl;


  }

  if ( std::adjacent_find( myvectorY.begin(), myvectorY.end(), std::not_equal_to<int>() ) == myvectorY.end() )
  {
    std::cout << "All Bins are equal each other for  = " << Name<< std::endl;
  }
  else{
    std::cout << "Opps Bins are NOT Equal for Cross- Section Hists " << Name<< std::endl;
    std::cout << " NBins_Eff_numY = " << NBins_Eff_numY << std::endl;
    std::cout << " NBins_Dom_numY = " << NBins_Dom_numY << std::endl;
    std::cout << " NBins_data_numY = " << NBins_data_numY << std::endl;


  }



}
////////////////////////////////////////
//
////////////////////////////////////////
void WritetoTFile_2DAll(CrossSection2D_Hist &Constuct_crosssection_Hists, TFile& file, char* Name){

file.cd(); // write to this Tfile

char Print_Name[2024];

sprintf(Print_Name, "%s_FluxIntegrated",Name);
std::cout<<"writing filename = " << Print_Name<<std::endl;
Constuct_crosssection_Hists.h_flux->Clone()->Write(Print_Name);
sprintf(Print_Name, "%s_Data_Signal",Name);
std::cout<<"writing filename = " << Print_Name<<std::endl;
Constuct_crosssection_Hists.h_Data_Signal ->Clone()->Write(Print_Name);
sprintf(Print_Name, "%s_effNum",Name);
std::cout<<"writing filename = " << Print_Name<<std::endl;
Constuct_crosssection_Hists.h_effNum ->Clone()->Write(Print_Name);
sprintf(Print_Name, "%s_effDom",Name);
std::cout<<"writing filename = " << Print_Name<<std::endl;
Constuct_crosssection_Hists.h_effDom ->Clone()->Write(Print_Name);
sprintf(Print_Name, "%s_hist_mvnreponse_Mig",Name);
std::cout<<"writing filename = " << Print_Name<<std::endl;
Constuct_crosssection_Hists.h_mvnreponse_Mig ->Clone()->Write(Print_Name);
sprintf(Print_Name, "%s_hist_mvnreponse_RECO",Name);
std::cout<<"writing filename = " << Print_Name<<std::endl;
Constuct_crosssection_Hists.h_mvnreponse_RECO ->Clone()->Write(Print_Name);
sprintf(Print_Name, "%s_hist_mvnreponse_TRUE",Name);
std::cout<<"writing filename = " << Print_Name<<std::endl;
Constuct_crosssection_Hists.h_mvnreponse_TRUE ->Clone()->Write(Print_Name);
sprintf(Print_Name, "%s_MC_RECO",Name);
std::cout<<"writing filename = " << Print_Name<<std::endl;
Constuct_crosssection_Hists.h_RECO ->Clone()->Write(Print_Name);

sprintf(Print_Name, "%s_MC_RECO_BG",Name);
std::cout<<"writing filename = " << Print_Name<<std::endl;
Constuct_crosssection_Hists.h_RECO_BG ->Clone()->Write(Print_Name);

return;

}//end of function
////////////////////////////////////////
//
////////////////////////////////////////
void WritetoTFile_Interaction(CrossSection2D_Hist &Constuct_crosssection_Hists, TFile& file, char* Name){

  file.cd(); // write to this Tfile

  char Print_Name[2024];

  sprintf(Print_Name, "%s_Interaction_Elastic",Name);
  Constuct_crosssection_Hists.Interaction_HistMap[kElastic]->Clone()->Write(Print_Name);
  sprintf(Print_Name, "%s_Interaction_Res_Coh_Pion",Name);
  Constuct_crosssection_Hists.Interaction_HistMap[kRes_Coh_Pion]->Clone()->Write(Print_Name);
  sprintf(Print_Name, "%s_Interaction_2p2h",Name);
  Constuct_crosssection_Hists.Interaction_HistMap[k2p2h]->Clone()->Write(Print_Name);
  sprintf(Print_Name, "%s_Interaction_DIS",Name);
  Constuct_crosssection_Hists.Interaction_HistMap[kDIS]->Clone()->Write(Print_Name);
  sprintf(Print_Name, "%s_Interaction_None",Name);
  Constuct_crosssection_Hists.Interaction_HistMap[kInteraction_NONE]->Clone()->Write(Print_Name);
  sprintf(Print_Name, "%s_Interaction_Other",Name);
  Constuct_crosssection_Hists.Interaction_HistMap[kInteraction_OTHER]->Clone()->Write(Print_Name);

  return;


}//end of function
////////////////////////////////////////
//
////////////////////////////////////////
void WritetoTFile_Interaction_DISbreakdown(CrossSection2D_Hist &Constuct_crosssection_Hists, TFile& file, char* Name){

  file.cd(); // write to this Tfile

  char Print_Name[2024];

  sprintf(Print_Name, "%s_Interaction_QE",Name);
  Constuct_crosssection_Hists.Interaction_HistMap[kElastic]->Clone()->Write(Print_Name);
  sprintf(Print_Name, "%s_Interaction_#DeltaRes",Name);
  Constuct_crosssection_Hists.Interaction_HistMap[kdeltaRES]->Clone()->Write(Print_Name);
  sprintf(Print_Name, "%s_Interaction_HeavierRes",Name);
  Constuct_crosssection_Hists.Interaction_HistMap[kHeavierRES]->Clone()->Write(Print_Name);
  sprintf(Print_Name, "%s_Interaction_2p2h",Name);
  Constuct_crosssection_Hists.Interaction_HistMap[k2p2h]->Clone()->Write(Print_Name);
  sprintf(Print_Name, "%s_Interaction_SIS",Name);
  Constuct_crosssection_Hists.Interaction_HistMap[kDISSIS]->Clone()->Write(Print_Name);
  sprintf(Print_Name, "%s_Interaction_SoftDIS",Name);
  Constuct_crosssection_Hists.Interaction_HistMap[kDISSoft]->Clone()->Write(Print_Name);
  sprintf(Print_Name, "%s_Interaction_HardDIS",Name);
  Constuct_crosssection_Hists.Interaction_HistMap[kDISHard]->Clone()->Write(Print_Name);
  sprintf(Print_Name, "%s_Interaction_None",Name);
  Constuct_crosssection_Hists.Interaction_HistMap[kInteraction_NONE]->Clone()->Write(Print_Name);
  sprintf(Print_Name, "%s_Interaction_Other",Name);
  Constuct_crosssection_Hists.Interaction_HistMap[kInteraction_OTHER]->Clone()->Write(Print_Name);

  return;


}//end of function
////////////////////////////////////////
//
////////////////////////////////////////
void WritetoTFile_2Dmain(CrossSection2D_Hist &Constuct_crosssection_Hists, TFile& file, char* Name){

  file.cd(); // write to this Tfile

  char Print_Name[2024];

  sprintf(Print_Name, "%s_Data_Signal",Name);
  Constuct_crosssection_Hists.h_Data_Signal ->Clone()->Write(Print_Name);
  sprintf(Print_Name, "%s_effNum",Name);
  Constuct_crosssection_Hists.h_effNum ->Clone()->Write(Print_Name);
  sprintf(Print_Name, "%s_effDom",Name);
  Constuct_crosssection_Hists.h_effDom ->Clone()->Write(Print_Name);
  sprintf(Print_Name, "%s_RECO",Name);
  Constuct_crosssection_Hists.h_RECO ->Clone()->Write(Print_Name);
  sprintf(Print_Name, "%s_RECO_BG",Name);
  Constuct_crosssection_Hists.h_RECO_BG ->Clone()->Write(Print_Name);
  return;

}//end of function
////////////////////////////////////////
//
////////////////////////////////////////
void WritetoTFile_NormTRUE2DCrossSection(CrossSection2D_Hist &Constuct_crosssection_Hists, TFile& file, char* Name, const double nNucleons, const double POT){

  file.cd(); // write to this Tfile

  char Print_Name[2024];
  sprintf(Print_Name, "%s",Name);
  MnvH2D *True_CrossSection = (MnvH2D*)Constuct_crosssection_Hists.h_effDom->Clone(Print_Name);
  MnvH2D *fluxIntegral = (MnvH2D*)Constuct_crosssection_Hists.h_flux->Clone("fluxIntegral");
 fluxIntegral->AddMissingErrorBandsAndFillWithCV(*True_CrossSection);


 True_CrossSection->Divide(True_CrossSection, fluxIntegral);
 True_CrossSection->Scale(1./nNucleons/POT);
 True_CrossSection->Scale(1.e4); //Flux histogram is in m^-2, but convention is to report cm^2
 //True_CrossSection->Scale(1., "width");

 //True_CrossSection->Scale(PotNorm_MC_TO_Data);
 True_CrossSection->Clone()->Write(Print_Name);

}//end of function
////////////////////////////////////////
//
////////////////////////////////////////
void WritetoTFile_NormTRUE2DCrossSection_Interaction(CrossSection2D_Hist &Constuct_crosssection_Hists, TFile& file, char* Name, const double nNucleons, const double POT){

 file.cd(); // write to this Tfile
 MnvH2D *fluxIntegral = (MnvH2D*)Constuct_crosssection_Hists.h_flux->Clone("fluxIntegral");
 fluxIntegral->AddMissingErrorBandsAndFillWithCV(*Constuct_crosssection_Hists.Interaction_HistMap[kElastic]);
 char Print_Name[2024];
 sprintf(Print_Name, "%s_CrossSection_Interaction_Elastic",Name);
  MnvH2D *True_CrossSection_Elastic = (MnvH2D*)Constuct_crosssection_Hists.Interaction_HistMap[kElastic]->Clone(Print_Name);
  True_CrossSection_Elastic->Divide(True_CrossSection_Elastic, fluxIntegral);
  True_CrossSection_Elastic->Scale(1./nNucleons/POT);
  True_CrossSection_Elastic->Scale(1.e4); //Flux histogram is in m^-2, but convention is to report cm^2
  //True_CrossSection_Elastic->Scale(1., "width");
  True_CrossSection_Elastic->Clone()->Write(Print_Name);

 sprintf(Print_Name, "%s_CrossSection_Interaction_1Pion",Name);
  MnvH2D *True_CrossSection_res_coh_pion = (MnvH2D*)Constuct_crosssection_Hists.Interaction_HistMap[kRes_Coh_Pion]->Clone(Print_Name);
  True_CrossSection_res_coh_pion->Divide(True_CrossSection_res_coh_pion, fluxIntegral);
  True_CrossSection_res_coh_pion->Scale(1./nNucleons/POT);
  True_CrossSection_res_coh_pion->Scale(1.e4); //Flux histogram is in m^-2, but convention is to report cm^2
  //True_CrossSection_res_coh_pion->Scale(1., "width");
  True_CrossSection_res_coh_pion->Clone()->Write(Print_Name);
 sprintf(Print_Name, "%s_CrossSection_Interaction_2p2h",Name);
  MnvH2D *True_CrossSection_2p2h = (MnvH2D*)Constuct_crosssection_Hists.Interaction_HistMap[k2p2h]->Clone(Print_Name);
  True_CrossSection_2p2h->Divide(True_CrossSection_2p2h, fluxIntegral);
  True_CrossSection_2p2h->Scale(1./nNucleons/POT);
  True_CrossSection_2p2h->Scale(1.e4); //Flux histogram is in m^-2, but convention is to report cm^2
  //True_CrossSection_2p2h->Scale(1., "width");
  True_CrossSection_2p2h->Clone()->Write(Print_Name);


 sprintf(Print_Name, "%s_CrossSection_Interaction_DIS",Name);
  MnvH2D *True_CrossSection_DIS = (MnvH2D*)Constuct_crosssection_Hists.Interaction_HistMap[kDIS]->Clone(Print_Name);

  True_CrossSection_DIS->Divide(True_CrossSection_DIS, fluxIntegral);
  True_CrossSection_DIS->Scale(1./nNucleons/POT);
  True_CrossSection_DIS->Scale(1.e4); //Flux histogram is in m^-2, but convention is to report cm^2
  //True_CrossSection_DIS->Scale(1., "width");
  True_CrossSection_DIS->Clone()->Write(Print_Name);

 sprintf(Print_Name, "%s_CrossSection_Interaction_None",Name);
  MnvH2D *True_CrossSection_None = (MnvH2D*)Constuct_crosssection_Hists.Interaction_HistMap[kInteraction_NONE]->Clone(Print_Name);

  True_CrossSection_None->Divide(True_CrossSection_None, fluxIntegral);
  True_CrossSection_None->Scale(1./nNucleons/POT);
  True_CrossSection_None->Scale(1.e4); //Flux histogram is in m^-2, but convention is to report cm^2
  //True_CrossSection_None->Scale(1., "width");
  True_CrossSection_None->Clone()->Write(Print_Name);


 sprintf(Print_Name, "%s_CrossSection_Interaction_Other",Name);
  MnvH2D *True_CrossSection_other = (MnvH2D*)Constuct_crosssection_Hists.Interaction_HistMap[kInteraction_OTHER]->Clone(Print_Name);

  True_CrossSection_other->Divide(True_CrossSection_other, fluxIntegral);
  True_CrossSection_other->Scale(1./nNucleons/POT);
  True_CrossSection_other->Scale(1.e4); //Flux histogram is in m^-2, but convention is to report cm^2
  //True_CrossSection_other->Scale(1., "width");
  True_CrossSection_other->Clone()->Write(Print_Name);
}//end of function
////////////////////////////////////////
//
////////////////////////////////////////
void WritetoTFile_NormTRUECrossSection_Interaction_DISbreakdown(CrossSection2D_Hist &Constuct_crosssection_Hists, TFile& file, char* Name, const double nNucleons, const double POT){

  file.cd(); // write to this Tfile
  MnvH2D *fluxIntegral = (MnvH2D*)Constuct_crosssection_Hists.h_flux->Clone("fluxIntegral");
  fluxIntegral->AddMissingErrorBandsAndFillWithCV(*Constuct_crosssection_Hists.Interaction_HistMap[kElastic]);
  char Print_Name[2024];

  sprintf(Print_Name, "%s_CrossSection_Interaction_QE",Name);
  MnvH2D *True_CrossSection_Elastic = (MnvH2D*)Constuct_crosssection_Hists.Interaction_HistMap[kElastic]->Clone(Print_Name);
  True_CrossSection_Elastic->Divide(True_CrossSection_Elastic, fluxIntegral);
  True_CrossSection_Elastic->Scale(1./nNucleons/POT);
  True_CrossSection_Elastic->Scale(1.e4); //Flux histogram is in m^-2, but convention is to report cm^2
  //True_CrossSection_Elastic->Scale(1., "width");
  True_CrossSection_Elastic->Clone()->Write(Print_Name);

  sprintf(Print_Name, "%s_CrossSection_Interaction_#DeltaRes",Name);
  MnvH2D *True_CrossSection_DeltaRES = (MnvH2D*)Constuct_crosssection_Hists.Interaction_HistMap[kdeltaRES]->Clone(Print_Name);
  True_CrossSection_DeltaRES->Divide(True_CrossSection_DeltaRES, fluxIntegral);
  True_CrossSection_DeltaRES->Scale(1./nNucleons/POT);
  True_CrossSection_DeltaRES->Scale(1.e4); //Flux histogram is in m^-2, but convention is to report cm^2
  //True_CrossSection_DeltaRES->Scale(1., "width");
  True_CrossSection_DeltaRES->Clone()->Write(Print_Name);

  sprintf(Print_Name, "%s_CrossSection_Interaction_HeavierRes",Name);
  MnvH2D *True_CrossSection_HeavierRes = (MnvH2D*)Constuct_crosssection_Hists.Interaction_HistMap[kHeavierRES]->Clone(Print_Name);
  True_CrossSection_HeavierRes->Divide(True_CrossSection_HeavierRes, fluxIntegral);
  True_CrossSection_HeavierRes->Scale(1./nNucleons/POT);
  True_CrossSection_HeavierRes->Scale(1.e4); //Flux histogram is in m^-2, but convention is to report cm^2
  //True_CrossSection_DeltaRES->Scale(1., "width");
  True_CrossSection_HeavierRes->Clone()->Write(Print_Name);

  sprintf(Print_Name, "%s_CrossSection_Interaction_2p2h",Name);
  MnvH2D *True_CrossSection_2p2h = (MnvH2D*)Constuct_crosssection_Hists.Interaction_HistMap[k2p2h]->Clone(Print_Name);
  True_CrossSection_2p2h->Divide(True_CrossSection_2p2h, fluxIntegral);
  True_CrossSection_2p2h->Scale(1./nNucleons/POT);
  True_CrossSection_2p2h->Scale(1.e4); //Flux histogram is in m^-2, but convention is to report cm^2
  //True_CrossSection_2p2h->Scale(1., "width");
  True_CrossSection_2p2h->Clone()->Write(Print_Name);


  sprintf(Print_Name, "%s_CrossSection_Interaction_DISSIS",Name);
  MnvH2D *True_CrossSection_DISSIS = (MnvH2D*)Constuct_crosssection_Hists.Interaction_HistMap[kDISSIS]->Clone(Print_Name);
  True_CrossSection_DISSIS->Divide(True_CrossSection_DISSIS, fluxIntegral);
  True_CrossSection_DISSIS->Scale(1./nNucleons/POT);
  True_CrossSection_DISSIS->Scale(1.e4); //Flux histogram is in m^-2, but convention is to report cm^2
  //True_CrossSection_DISSIS->Scale(1., "width");
  True_CrossSection_DISSIS->Clone()->Write(Print_Name);

  sprintf(Print_Name, "%s_CrossSection_Interaction_DISSoft",Name);
  MnvH2D *True_CrossSection_DISSoft = (MnvH2D*)Constuct_crosssection_Hists.Interaction_HistMap[kDISSoft]->Clone(Print_Name);
  True_CrossSection_DISSoft->Divide(True_CrossSection_DISSoft, fluxIntegral);
  True_CrossSection_DISSoft->Scale(1./nNucleons/POT);
  True_CrossSection_DISSoft->Scale(1.e4); //Flux histogram is in m^-2, but convention is to report cm^2
  // True_CrossSection_DISSoft->Scale(1., "width");
  True_CrossSection_DISSoft->Clone()->Write(Print_Name);

  sprintf(Print_Name, "%s_CrossSection_Interaction_DISHard",Name);
  MnvH2D *True_CrossSection_DISHard = (MnvH2D*)Constuct_crosssection_Hists.Interaction_HistMap[kDISHard]->Clone(Print_Name);
  True_CrossSection_DISHard->Divide(True_CrossSection_DISHard, fluxIntegral);
  True_CrossSection_DISHard->Scale(1./nNucleons/POT);
  True_CrossSection_DISHard->Scale(1.e4); //Flux histogram is in m^-2, but convention is to report cm^2
  //True_CrossSection_DISHard->Scale(1., "width");
  True_CrossSection_DISHard->Clone()->Write(Print_Name);


  sprintf(Print_Name, "%s_CrossSection_Interaction_None",Name);
  MnvH2D *True_CrossSection_None = (MnvH2D*)Constuct_crosssection_Hists.Interaction_HistMap[kInteraction_NONE]->Clone(Print_Name);

  True_CrossSection_None->Divide(True_CrossSection_None, fluxIntegral);
  True_CrossSection_None->Scale(1./nNucleons/POT);
  True_CrossSection_None->Scale(1.e4); //Flux histogram is in m^-2, but convention is to report cm^2
  //True_CrossSection_None->Scale(1., "width");
  True_CrossSection_None->Clone()->Write(Print_Name);


  sprintf(Print_Name, "%s_CrossSection_Interaction_Other",Name);
  MnvH2D *True_CrossSection_other = (MnvH2D*)Constuct_crosssection_Hists.Interaction_HistMap[kInteraction_OTHER]->Clone(Print_Name);

  True_CrossSection_other->Divide(True_CrossSection_other, fluxIntegral);
  True_CrossSection_other->Scale(1./nNucleons/POT);
  True_CrossSection_other->Scale(1.e4); //Flux histogram is in m^-2, but convention is to report cm^2
  //True_CrossSection_other->Scale(1., "width");
  True_CrossSection_other->Clone()->Write(Print_Name);

}//end of function
////////////////////////////////////////
//
////////////////////////////////////////
int GetGlobalBinNFrom2DMig(MnvH2D *migration,MnvH2D *h_reco, MnvH2D *h_truth, double meas_x , double meas_y, double truth_x, double truth_y){

  auto XbinA =         migration->GetXaxis()->FindBin( migration->GetXaxis()->GetBinCenter(h_reco->FindFixBin(meas_x,meas_y)));
  auto YbinA =         migration->GetYaxis()->FindBin( migration->GetYaxis()->GetBinCenter(h_truth->FindFixBin(truth_x,truth_y)));
  return YbinA * (migration->GetXaxis()->GetNbins() + 2) + XbinA;
}
////////////////////////////////////////
//
////////////////////////////////////////
int GetGlobalBinNFrom2DMig_BinN(MnvH2D *migration,MnvH2D *h_reco, MnvH2D *h_truth, int meas_xBinN , int meas_yBinN, int truth_xBinN, int truth_yBinN){

  auto XbinCenter_RECO = h_reco->GetXaxis()->GetBinCenter(meas_xBinN);
  auto YbinCenter_RECO = h_reco->GetYaxis()->GetBinCenter(meas_yBinN);
  auto XbinCenter_TRUTH = h_truth->GetXaxis()->GetBinCenter(truth_xBinN);
  auto YbinCenter_TRUTH = h_truth->GetYaxis()->GetBinCenter(truth_yBinN);
  return GetGlobalBinNFrom2DMig(migration,h_reco, h_truth, XbinCenter_RECO, YbinCenter_RECO, XbinCenter_TRUTH, YbinCenter_TRUTH);

}
////////////////////////////////////////
//
////////////////////////////////////////
MnvH2D * GetMigration_Projection_Y_forBinN(MnvH2D *migration, MnvH2D *h_reco, MnvH2D *h_truth, std::vector<double> ProjectBinning , int BinN_project ){

  MnvH2D *h_return =    new MnvH2D("h_return", "h_return",ProjectBinning.size()-1, ProjectBinning.data() ,ProjectBinning.size()-1, ProjectBinning.data()  );

  for(int  XTruthbinN = 1; XTruthbinN <= h_truth->GetNbinsX();  XTruthbinN++  ){
    for(int  XRecobinN = 1; XRecobinN <= h_reco->GetNbinsX();  XRecobinN++  ){

      int globalBin =  GetGlobalBinNFrom2DMig_BinN(migration,h_reco, h_truth, XRecobinN, BinN_project , XTruthbinN, BinN_project);
      double content = migration->GetBinContent(globalBin);

      int Global_hreturn_binN  = XTruthbinN*(h_return->GetNbinsX()+2) + XRecobinN; // Assuming Truth is Y axis

      h_return->AddBinContent(Global_hreturn_binN,content);
    }
  }
return h_return;
}
////////////////////////////////////////
//
////////////////////////////////////////
void GetMigration_Projection_Y_forBinN_input(MnvH2D &h_return, MnvH2D *migration,
  MnvH2D *h_reco, MnvH2D *h_truth, int BinN_project ){

    for(int  XTruthbinN = 1; XTruthbinN <= h_truth->GetNbinsX();  XTruthbinN++  ){
      for(int  XRecobinN = 1; XRecobinN <= h_reco->GetNbinsX();  XRecobinN++  ){

        int globalBin =  GetGlobalBinNFrom2DMig_BinN(migration,h_reco, h_truth, XRecobinN, BinN_project , XTruthbinN, BinN_project);
        double content = migration->GetBinContent(globalBin);

        int Global_hreturn_binN  = XTruthbinN*(h_return.GetNbinsX()+2) + XRecobinN; // Assuming Truth is Y axis
        //std::cout<< "Global_hreturn_binN = " << Global_hreturn_binN << " content = " << content << std::endl;
        h_return.AddBinContent(Global_hreturn_binN,content);
      }
    }

    return;
  }
////////////////////////////////////////
//
////////////////////////////////////////
MnvH2D * GetMigration_Projection_X_forBinN(MnvH2D *migration, MnvH2D *h_reco,
   MnvH2D *h_truth, std::vector<double> ProjectBinning , int BinN_project ){

     MnvH2D *h_return =    new MnvH2D("h_return", "h_return",ProjectBinning.size()-1, ProjectBinning.data() ,ProjectBinning.size()-1, ProjectBinning.data()  );

     for(int  YTruthbinN = 1; YTruthbinN <= h_truth->GetNbinsY();  YTruthbinN++  ){
       for(int  YRecobinN = 1; YRecobinN <= h_reco->GetNbinsY();  YRecobinN++  ){

      int globalBin =  GetGlobalBinNFrom2DMig_BinN(migration,h_reco, h_truth, BinN_project, YRecobinN , BinN_project,YTruthbinN);
      double content = migration->GetBinContent(globalBin);

      int Global_hreturn_binN  = YTruthbinN*(h_return->GetNbinsY()+2) + YRecobinN; // Assuming Truth is X axis

      h_return->AddBinContent(Global_hreturn_binN,content);
    }
  }

  return h_return;

}
////////////////////////////////////////
//
////////////////////////////////////////
void drawBinRange( MnvH2D * h, int axis, int bin, const char* varName, double text_size, const char* numFormatStr, bool left )
{
  double varmin=axis==1 ? h->GetXaxis()->GetBinLowEdge(bin) : h->GetYaxis()->GetBinLowEdge(bin);
  double varmax=axis==1 ? h->GetXaxis()->GetBinUpEdge(bin) :  h->GetYaxis()->GetBinUpEdge(bin);

  TString formatStr(TString::Format("%%%s < %%s < %%%s", numFormatStr, numFormatStr));

  TLatex* la=0;
  TString text(TString::Format(formatStr.Data(), varmin, varName, varmax));
  if(left){
    la=new TLatex(gPad->GetLeftMargin()+0.02,
                  1-gPad->GetTopMargin()-0.01,
                  text);
    la->SetTextAlign(13); // top left
  }
  else{
    la=new TLatex(1-gPad->GetRightMargin()-0.01,
                  1-gPad->GetTopMargin()-0.01,
                  text);
    la->SetTextAlign(33); // top right
  }

  la->SetNDC();
  la->SetTextFont(42);
  la->SetTextSize(text_size);
  la->Draw();
}
////////////////////////////////////////
//
////////////////////////////////////////
void drawBinRange_Red( MnvH2D * h, int axis, int bin, const char* varName, double text_size, const char* numFormatStr, bool left )
{
  double varmin=axis==1 ? h->GetXaxis()->GetBinLowEdge(bin) : h->GetYaxis()->GetBinLowEdge(bin);
  double varmax=axis==1 ? h->GetXaxis()->GetBinUpEdge(bin) :  h->GetYaxis()->GetBinUpEdge(bin);

  TString formatStr(TString::Format("%%%s < %%s < %%%s", numFormatStr, numFormatStr));

  TLatex* la=0;
  TString text(TString::Format(formatStr.Data(), varmin, varName, varmax));
  if(left){
    la=new TLatex(gPad->GetLeftMargin()+0.02,
    1-gPad->GetTopMargin()-0.01,
    text);
    la->SetTextAlign(13); // top left
  }
  else{
    la=new TLatex(1-gPad->GetRightMargin()-0.01,
    1-gPad->GetTopMargin()-0.01,text);
    la->SetTextAlign(33); // top right
  }

  la->SetNDC();
  la->SetTextFont(42);
  la->SetTextColor(kRed);
  la->SetTextSize(text_size);
  la->Draw();
}
////////////////////////////////////////
//
////////////////////////////////////////
double GetMaxFromProjectionY(MnvH2D * h1, MnvH2D * h2, bool checkBinwidth){

  PlotUtils::MnvH2D* hist1 = h1->Clone("hist1");
  PlotUtils::MnvH2D* hist2 = h2->Clone("hist2");

  int Nbins1 = hist1->GetNbinsX();
  int Nbins2 = hist2->GetNbinsX();

  if(Nbins1 !=Nbins2){std::cout<<"Bins are not matching for GetMaxFromProjectionX "<<std::endl;
    std::cout<< " Nbins1 =  "<< Nbins1 << "  Nbins2 = "<< Nbins2 << std::endl;
    std::cout<< " Title1 =  "<< hist1->GetTitle()<< "  title2 = "<< hist2->GetTitle() << std::endl;

    assert(false);}
  double MaxValue = -1;

  for(int i = 1; i <=Nbins1; ++i) {
    PlotUtils::MnvH1D* hproj_1 =
    hist1->ProjectionY(uniq(), i, i)->Clone();

    PlotUtils::MnvH1D* hproj_2 =
    hist2->ProjectionY(uniq(), i, i)->Clone();


    if(checkBinwidth==true){
      hproj_1->Scale(1,"width");
      hproj_2->Scale(1,"width");
    }

    double max1 = hproj_1->GetMaximum();
    double max2 = hproj_2->GetMaximum();
    double Maxpro = (max1 < max2) ? max2 : max1;

    if (Maxpro > MaxValue){MaxValue = Maxpro;}

  }

  return MaxValue;
}
////////////////////////////////////////
//
////////////////////////////////////////
double GetMaxFromProjectionY(MnvH2D * h1, bool checkBinwidth){

  PlotUtils::MnvH2D* hist1 = h1->Clone("hist1");


  int Nbins1 = hist1->GetNbinsX();
  double MaxValue = -1;

  for(int i = 1; i <=Nbins1; ++i) {
    PlotUtils::MnvH1D* hproj_1 =
    hist1->ProjectionY(uniq(), i, i)->Clone();

    if(checkBinwidth==true){
      hproj_1->Scale(1,"width");
    }

    double Maxpro = hproj_1->GetMaximum();

    if (Maxpro > MaxValue){MaxValue = Maxpro;}

  }

  return MaxValue;
}
////////////////////////////////////////
//
////////////////////////////////////////
double GetMaxFromProjectionX( MnvH2D * h1, MnvH2D * h2, bool checkBinwidth){

  PlotUtils::MnvH2D* hist1 = h1->Clone("hist1");
  PlotUtils::MnvH2D* hist2 = h2->Clone("hist2");

  int Nbins1 = hist1->GetNbinsY();
  int Nbins2 = hist2->GetNbinsY();

  if(Nbins1 !=Nbins2){std::cout<<"Bins are not matching for GetMaxFromProjectionX "<<std::endl;
  std::cout<< " Nbins1 =  "<< Nbins1 << "  Nbins2 = "<< Nbins2 << std::endl;
   std::cout<< " Title1 =  "<< hist1->GetTitle()<< "  title2 = "<< hist2->GetTitle() << std::endl;
  assert(false);}
  double MaxValue = -1;

  for(int i = 1; i <=Nbins1; ++i) {
    PlotUtils::MnvH1D* hproj_1 =
    hist1->ProjectionX(uniq(), i, i)->Clone();

    PlotUtils::MnvH1D* hproj_2 =
    hist2->ProjectionX(uniq(), i, i)->Clone();


    if(checkBinwidth==true){
      hproj_1->Scale(1,"width");
      hproj_2->Scale(1,"width");
    }

    double max1 = hproj_1->GetMaximum();
    double max2 = hproj_2->GetMaximum();
    double Maxpro = (max1 < max2) ? max2 : max1;

    if (Maxpro > MaxValue){MaxValue = Maxpro;}

  }

  return MaxValue;
}
////////////////////////////////////////
//
////////////////////////////////////////
double GetMaxFromProjectionX( MnvH2D * h1, bool checkBinwidth){

  PlotUtils::MnvH2D* hist1 = h1->Clone("hist1");


  int Nbins1 = hist1->GetNbinsY();

  double MaxValue = -1;

  for(int i = 1; i <=Nbins1; ++i) {
    PlotUtils::MnvH1D* hproj_1 =
    hist1->ProjectionX(uniq(), i, i)->Clone();


    if(checkBinwidth==true){
      hproj_1->Scale(1,"width");

    }

    double Maxpro = hproj_1->GetMaximum();
    if (Maxpro > MaxValue){MaxValue = Maxpro;}

  }

  return MaxValue;
}
////////////////////////////////////////
//
////////////////////////////////////////
std::vector<double> calculateMeanValues(MnvH2D* hist) {
    std::vector<double> meanValues;
    int nXBins = hist->GetXaxis()->GetNbins();
    for (int i = 1; i <= nXBins; ++i) {
        double sumY = 0.0;
        double sumWeights = 0.0;
        int nYBins = hist->GetYaxis()->GetNbins();
        for (int j = 1; j <= nYBins; ++j) {
            double binContent = hist->GetBinContent(i, j);
            double binError = hist->GetBinError(i, j);
            double binCenterY = hist->GetYaxis()->GetBinCenter(j);
            double binWidthY = hist->GetYaxis()->GetBinWidth(j);
            double weight = binContent / binWidthY;
            sumY += weight * binCenterY;
            sumWeights += weight;
        }
        double meanValue = sumY / sumWeights;
        meanValues.push_back(meanValue);
    }
    return meanValues;
}
////////////////////////////////////////
//
////////////////////////////////////////
std::vector<double> extractXBins( MnvH2D* hist) {
    std::vector<double> xBins;
    int nXBins = hist->GetXaxis()->GetNbins();
    for (int i = 1; i <= nXBins; ++i) {
        double binCenterX = hist->GetXaxis()->GetBinCenter(i);
        xBins.push_back(binCenterX);
    }
    return xBins;
}
////////////////////////////////////////
//
////////////////////////////////////////
TH2D* rebinXAxis(TH2D* hist, const std::vector<double> rebinFactors) {
    // Extract original histogram properties
    int nXBins = hist->GetNbinsX();
    int nYBins = hist->GetNbinsY();
    auto xBins = hist->GetXaxis()->GetXbins()->GetArray();
    auto yBins = hist->GetYaxis()->GetXbins()->GetArray();

    // Create a new histogram with the rebinned bin centers
    TH2D* rebinnedHist = new TH2D(hist->GetName(), hist->GetTitle(),
                                  rebinFactors.size() - 1,
                                  rebinFactors.data(),
                                  nYBins, yBins);

    for (int i = 0; i < nXBins; ++i) {
        double binCenter = hist->GetXaxis()->GetBinCenter(i + 1);
        int rebinnedXBinIdx = rebinnedHist->GetXaxis()->FindFixBin(binCenter); // Index for the rebinned X-axis bin centers
        for (int j = 0; j <= nYBins; ++j) {
            double sum = 0.0;
            double binWidth = hist->GetXaxis()->GetBinWidth(i + 1);
            sum = hist->GetBinContent(i + 1, j) * binWidth;
            rebinnedHist->Fill(rebinnedHist->GetXaxis()->GetBinCenter(rebinnedXBinIdx),
                                rebinnedHist->GetYaxis()->GetBinCenter(j + 1),
                                sum); // Fill the rebinned bin content
        }
    }

    return rebinnedHist;
}
////////////////////////////////////////
//
////////////////////////////////////////
MnvH2D* rebinXAxis(MnvH2D* hist, const std::vector<double> rebinFactors) {
  // Extract original histogram properties
  int nXBins = hist->GetNbinsX();
  int nYBins = hist->GetNbinsY();
  auto xBins = hist->GetXaxis()->GetXbins()->GetArray();
  auto yBins = hist->GetYaxis()->GetXbins()->GetArray();

  // Create a new histogram with the rebinned bin centers
  MnvH2D* rebinnedHist = new MnvH2D(hist->GetName(), hist->GetTitle(),
  rebinFactors.size() - 1,
  rebinFactors.data(),
  nYBins, yBins);

  for (int i = 0; i < nXBins; ++i) {
    double binCenter = hist->GetXaxis()->GetBinCenter(i + 1);
    int rebinnedXBinIdx = rebinnedHist->GetXaxis()->FindFixBin(binCenter); // Index for the rebinned X-axis bin centers
    for (int j = 0; j <= nYBins; ++j) {
      double sum = 0.0;
      double binWidth = hist->GetXaxis()->GetBinWidth(i + 1);
      sum = hist->GetBinContent(i + 1, j) * binWidth;
      rebinnedHist->Fill(rebinnedHist->GetXaxis()->GetBinCenter(rebinnedXBinIdx),
      rebinnedHist->GetYaxis()->GetBinCenter(j + 1),
      sum); // Fill the rebinned bin content
    }
  }

  return rebinnedHist;
}
////////////////////////////////////////
//
////////////////////////////////////////
CrossSection_2DhistNames MakeDaisy_names(CrossSection_2DhistNames crosssection_hist_Names,  std::string DaisyNum){

  CrossSection_2DhistNames DaisyName_CrossSection;

  std::string DaisyName = "_Daisy_" + DaisyNum;
  //std::cout<<"adding DaisyName  = " << DaisyName<<std::endl;
  DaisyName_CrossSection.Muon2DType = crosssection_hist_Names.Muon2DType;
  DaisyName_CrossSection.RECO_MC_name = crosssection_hist_Names.RECO_MC_name + DaisyName;
  //std::cout<<"DaisyName_CrossSection.Reco_hist_name  = " << DaisyName_CrossSection.Reco_hist_name<<std::endl;
  DaisyName_CrossSection.RECO_MC_BG_name = crosssection_hist_Names.RECO_MC_BG_name + DaisyName;
  //std::cout<<"DaisyName_CrossSection.Reco_hist_BG_name  = " << DaisyName_CrossSection.Reco_hist_BG_name<<std::endl;
  DaisyName_CrossSection.Data_hist_name =crosssection_hist_Names.Data_hist_name + DaisyName;
  //std::cout<<"DaisyName_CrossSection.Data_hist_name  = " << DaisyName_CrossSection.Data_hist_name<<std::endl;
  DaisyName_CrossSection.hist_Eff_denominator_name = crosssection_hist_Names.hist_Eff_denominator_name + DaisyName;
  //std::cout<<"DaisyName_CrossSection.hist_Eff_denominator_name  = " << DaisyName_CrossSection.hist_Eff_denominator_name<<std::endl;
  DaisyName_CrossSection.hist_Eff_numerator_name = crosssection_hist_Names.hist_Eff_numerator_name + DaisyName;
  //std::cout<<"DaisyName_CrossSection.hist_Eff_numerator_name  = " << DaisyName_CrossSection.hist_Eff_numerator_name<<std::endl;
  DaisyName_CrossSection.MnvReponse_Name_Mig = crosssection_hist_Names.MnvReponse_Name_Mig + DaisyName;
  DaisyName_CrossSection.MnvReponse_Name_reco = crosssection_hist_Names.MnvReponse_Name_reco + DaisyName;
  DaisyName_CrossSection.MnvReponse_Name_true = crosssection_hist_Names.MnvReponse_Name_true + DaisyName;
  //std::cout<<"DaisyName_CrossSection.Migration_name  = " << DaisyName_CrossSection.Migration_name<<std::endl;
  DaisyName_CrossSection.hist_Flux_name = crosssection_hist_Names.hist_Flux_name;
  //std::cout<<"DaisyName_CrossSection.hist_Flux_name  = " << DaisyName_CrossSection.hist_Flux_name<<std::endl;

  return DaisyName_CrossSection;

}
////////////////////////////////////////
//
////////////////////////////////////////
CrossSection2D_Hist MakeDaisyCrossSectionHist(CrossSection_2DhistNames Names, std::string DaisyN,  TFile *inputFile_RECO_mc,TFile *inputFile_TRUE_mc, TFile *inputFile_data ){
 CrossSection_2DhistNames Daisy_names =Constuct_2Dcrosssection_Histname_Daisy(Names.Muon2DType,  DaisyN );
  //Print_crosssection_Histname(Daisy_names);
  CrossSection2D_Hist Daisy = Constuct_2Dcrosssection_Hists( Daisy_names, inputFile_RECO_mc, inputFile_TRUE_mc, inputFile_data );

  return Daisy;
}
////////////////////////////////////////
//
////////////////////////////////////////
CrossSection2D_Hist_Daisy Constuct_crosssection_Hists_Daisy(CrossSection_2DhistNames Names,
  TFile *inputFile_RECO_mc,TFile *inputFile_TRUE_mc, TFile *inputFile_data ){

  CrossSection2D_Hist_Daisy Daisy_hists;
  //std::cout << "Size of Daisy_hists: " << sizeof(Daisy_hists) << " bytes" << std::endl;

  CrossSection2D_Hist Daisy0 = MakeDaisyCrossSectionHist(Names, "0", inputFile_RECO_mc, inputFile_TRUE_mc, inputFile_data );
  Daisy_hists.Daisy0 = Daisy0;

  CrossSection2D_Hist Daisy1 = MakeDaisyCrossSectionHist(Names,"1", inputFile_RECO_mc, inputFile_TRUE_mc, inputFile_data );
  Daisy_hists.Daisy1 = Daisy1;

  CrossSection2D_Hist Daisy2 = MakeDaisyCrossSectionHist(Names,"2", inputFile_RECO_mc, inputFile_TRUE_mc, inputFile_data );
  Daisy_hists.Daisy2 = Daisy2;

  CrossSection2D_Hist Daisy3 = MakeDaisyCrossSectionHist(Names,"3", inputFile_RECO_mc, inputFile_TRUE_mc, inputFile_data );
  Daisy_hists.Daisy3 = Daisy3;

  CrossSection2D_Hist Daisy4 = MakeDaisyCrossSectionHist(Names,"4", inputFile_RECO_mc, inputFile_TRUE_mc, inputFile_data );
  Daisy_hists.Daisy4 = Daisy4;

  CrossSection2D_Hist Daisy5 = MakeDaisyCrossSectionHist(Names,"5", inputFile_RECO_mc, inputFile_TRUE_mc, inputFile_data );
  Daisy_hists.Daisy5 = Daisy5;

  CrossSection2D_Hist Daisy6 = MakeDaisyCrossSectionHist(Names,"6", inputFile_RECO_mc, inputFile_TRUE_mc, inputFile_data );
  Daisy_hists.Daisy6 = Daisy6;

  CrossSection2D_Hist Daisy7 = MakeDaisyCrossSectionHist(Names,"7", inputFile_RECO_mc, inputFile_TRUE_mc, inputFile_data );
  Daisy_hists.Daisy7 = Daisy7;

  CrossSection2D_Hist Daisy8 = MakeDaisyCrossSectionHist(Names,"8", inputFile_RECO_mc, inputFile_TRUE_mc, inputFile_data );
  Daisy_hists.Daisy8 = Daisy8;

  CrossSection2D_Hist Daisy9 = MakeDaisyCrossSectionHist(Names,"9", inputFile_RECO_mc, inputFile_TRUE_mc, inputFile_data );
  Daisy_hists.Daisy9 = Daisy9;

  CrossSection2D_Hist Daisy10 = MakeDaisyCrossSectionHist( Names,"10", inputFile_RECO_mc, inputFile_TRUE_mc, inputFile_data );
  Daisy_hists.Daisy10 = Daisy10;

  CrossSection2D_Hist Daisy11 = MakeDaisyCrossSectionHist( Names,"11", inputFile_RECO_mc, inputFile_TRUE_mc, inputFile_data );
  Daisy_hists.Daisy11 = Daisy11;

  return Daisy_hists;

}
////////////////////////////////////////
//
////////////////////////////////////////
ME_playlist_2D_CrossSection_MAP_DAISY Constuct_crosssection_2DHists_PlaylistMap_DAISY(CrossSection_2DhistNames Names,
                                                         ME_playlist_TFileMAP MC_RECO_TfileMap,
                                                         ME_playlist_TFileMAP MC_TRUTH_TfileMap,
                                                         ME_playlist_TFileMAP Data_TfileMap )
{
  std::cout<< "Constuct Cross Section Hist Map"<< std::endl;
  ME_playlist_2D_CrossSection_MAP_DAISY OutPut_Hist_Map;


  typename std::map<ME_helium_Playlists, TFile*>::const_iterator MC_RECO_it;
  typename std::map<ME_helium_Playlists, TFile*>::const_iterator MC_TRUTH_it;
  typename std::map<ME_helium_Playlists, TFile*>::const_iterator Data_it;

  for (MC_RECO_it = MC_RECO_TfileMap.begin(), Data_it = Data_TfileMap.begin(), MC_TRUTH_it= MC_TRUTH_TfileMap.begin() ; MC_RECO_it != MC_RECO_TfileMap.end(); ++MC_RECO_it, ++MC_TRUTH_it, ++Data_it)
  {
    if(MC_RECO_it->first != MC_TRUTH_it->first || Data_it->first != MC_TRUTH_it->first){assert(("The TFiles making ME_playlist_CrossSection_MAP do not Match ", false));}
std::cout<<"Making CrossSection_Hist_Daisy First Playlist THIS IS MF 2D!!! ::"<< GetPlaylist_Name(MC_RECO_it->first)<<std::endl;

    CrossSection2D_Hist_Daisy CrossSection_Hist_forplaylist = Constuct_crosssection_Hists_Daisy(Names, MC_RECO_it->second, MC_TRUTH_it->second, Data_it->second);
    OutPut_Hist_Map.insert(std::make_pair(MC_RECO_it->first, CrossSection_Hist_forplaylist));
  }

return OutPut_Hist_Map;

}//end function
////////////////////////////////////////
//
////////////////////////////////////////

CrossSection2D_Hist_Daisy Combine_crosssection_Hists_PlaylistMap_Daisy(ME_playlist_2D_CrossSection_MAP_DAISY inputMap, ME_helium_Playlists playlist_combine_too ){

  CrossSection2D_Hist_Daisy output_hist;
  typename std::map<ME_helium_Playlists, CrossSection2D_Hist_Daisy>::const_iterator inputMap_it;

  output_hist.Daisy0  = inputMap[playlist_combine_too].Daisy0;
  output_hist.Daisy1  = inputMap[playlist_combine_too].Daisy1;
  output_hist.Daisy2  = inputMap[playlist_combine_too].Daisy2;
  output_hist.Daisy3  = inputMap[playlist_combine_too].Daisy3;
  output_hist.Daisy4  = inputMap[playlist_combine_too].Daisy4;
  output_hist.Daisy5  = inputMap[playlist_combine_too].Daisy5;
  output_hist.Daisy6  = inputMap[playlist_combine_too].Daisy6;
  output_hist.Daisy7  = inputMap[playlist_combine_too].Daisy7;
  output_hist.Daisy8  = inputMap[playlist_combine_too].Daisy8;
  output_hist.Daisy9  = inputMap[playlist_combine_too].Daisy9;
  output_hist.Daisy10 = inputMap[playlist_combine_too].Daisy10;
  output_hist.Daisy11 = inputMap[playlist_combine_too].Daisy11;


  for (inputMap_it = inputMap.begin(); inputMap_it != inputMap.end(); ++inputMap_it){

    if(inputMap_it->first == playlist_combine_too ) continue;

    AddCrossSectionHist_Daisy_noFlux(output_hist, inputMap_it->second);


  } // end of loop


return output_hist;

}//end of function

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void Add2DCrossSectionHis_noFlux(CrossSection2D_Hist &AddTo, CrossSection2D_Hist input){

AddTo.h_Data_Signal->Add(input.h_Data_Signal);
AddTo.h_RECO->Add(input.h_RECO);
AddTo.h_RECO_BG->Add(input.h_RECO_BG);
AddTo.h_effNum->Add(input.h_effNum);
AddTo.h_effDom->Add(input.h_effDom);
AddTo.h_mvnreponse_Mig->Add(input.h_mvnreponse_Mig);
AddTo.h_mvnreponse_RECO->Add(input.h_mvnreponse_RECO);
AddTo.h_mvnreponse_TRUE->Add(input.h_mvnreponse_TRUE);

}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////


void AddCrossSectionHist_Daisy_noFlux(CrossSection2D_Hist_Daisy &AddTo, CrossSection2D_Hist_Daisy input){

  Add2DCrossSectionHis_noFlux(AddTo.Daisy0 , input.Daisy0);
  Add2DCrossSectionHis_noFlux(AddTo.Daisy1 , input.Daisy1);
  Add2DCrossSectionHis_noFlux(AddTo.Daisy2 , input.Daisy2);
  Add2DCrossSectionHis_noFlux(AddTo.Daisy3 , input.Daisy3);
  Add2DCrossSectionHis_noFlux(AddTo.Daisy4 , input.Daisy4);
  Add2DCrossSectionHis_noFlux(AddTo.Daisy5 , input.Daisy5);
  Add2DCrossSectionHis_noFlux(AddTo.Daisy6 , input.Daisy6);
  Add2DCrossSectionHis_noFlux(AddTo.Daisy7 , input.Daisy7);
  Add2DCrossSectionHis_noFlux(AddTo.Daisy8 , input.Daisy8);
  Add2DCrossSectionHis_noFlux(AddTo.Daisy9 , input.Daisy9);
  Add2DCrossSectionHis_noFlux(AddTo.Daisy10 , input.Daisy10);
  Add2DCrossSectionHis_noFlux(AddTo.Daisy11 , input.Daisy11);
}
