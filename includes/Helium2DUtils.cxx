
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



  std::string  GetMuon2DVarHistName( Muon2DVar var2D) {
  switch (var2D) {
    case kPT_PZ:
    return "h_Muon_PT_PZ";

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

std::string  GetMuon2DVarHist_DATAName(Muon2DVar var2D) {
switch (var2D) {
  case kPT_PZ:
  return "h_Data_Muon_PT_PZ";

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

std::string  GetMuon2DVar_yaxisUnits(Muon2DVar var2D) {
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


std::string  GetMuon2DVar_XaxisTitle(Muon2DVar var2D) {
switch (var2D) {
  case kPT_PZ:
  return "P_{T} [GeV]";

  case kPT_theta:
  return "P_{T} [GeV]";

  case kPZ_theta:
  return "P_{#parallel} [GeV]";

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

std::string  GetMuon2DVar_YaxisTitle(Muon2DVar var2D) {
switch (var2D) {
  case kPT_PZ:
  return "P_{#parallel} [GeV]";

  case kPT_theta:
  return "#theta_{#mu} [Degs]";

  case kPZ_theta:
  return "#theta_{#mu} [Degs]";

  case kE_theta:
  return "#theta_{#mu} [Degs]";

  case kE_PZ:
  return "P_{#parallel} [GeV]";

  case kE_PT:
  return "P_{T} [GeV]";

  case kVertex_Z_R:
  return "Vertex R [mm]";

  default:
  std::cout << "ERROR: unknown Playlist name for Muon !" << std::endl;
  return "";
};
}









std::string  GetMuon2DVar_ReponseHistTitle(Muon2DVar var2D) {
switch (var2D) {
  case kPT_PZ:
  return "MnvR_Muon_PT_PZ";

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


//////////////////////////////////////////////////////////////////////////
//GET Vertex Varibles
//////////////////////////////////////////////////////////////////////////


std::string Construct_string_Ending(bool isMiG,bool isStack,char *StackType, bool isYProj,int isFULLorEmpty, bool FirstorSecond ){


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


Playlist_MnvH2D_Map Constuct_MnvH2DMap_FromME_playlist_TFileMAP(ME_playlist_TFileMAP TFile_Map, const char* name ){
  Playlist_MnvH2D_Map MnvH2D_Map;
  std::cout<<"Constucting Hist map for Varible Name:" << name <<std::endl;
  std::cout<< "Input Map Has Size =  " << TFile_Map.size() <<std::endl;

  typename std::map<ME_helium_Playlists, TFile*>::const_iterator cat;

  for (cat = TFile_Map.begin(); cat != TFile_Map.end(); ++cat)
  {
    //auto hist = GetHist(cat->second, name);
    MnvH2D *hist = (MnvH2D*)(cat->second)->Get(name);
    MnvH2D_Map.insert(std::make_pair(cat->first, hist));

  }//end of loop


  return MnvH2D_Map;
}//end of function


Playlist_HistFolio_MnvH2D_Map Constuct_HistFolio_MnvH2DMap_FromME_playlist_TFileMAP(ME_playlist_TFileMAP TFile_Map, const char* name ){
  Playlist_HistFolio_MnvH2D_Map HistFolio_MnvH2D_Map;
  std::cout<<"Constucting Hist Folio map for Varible Name:" << name <<std::endl;
  std::cout<< "Input Map Has Size =  " << TFile_Map.size() <<std::endl;

  typename std::map<ME_helium_Playlists, TFile*>::const_iterator cat;

  for (cat = TFile_Map.begin(); cat != TFile_Map.end(); ++cat)
  {
    PlotUtils::HistFolio<PlotUtils::MnvH2D> Stack(PlotUtils::LoadHistFolioFromFile<PlotUtils::MnvH2D>(*(cat->second), std::string(name)),"Stack");
    HistFolio_MnvH2D_Map.insert(std::make_pair(cat->first, Stack));
  }//end of loop

  return HistFolio_MnvH2D_Map;
}//end of function




////////////////////////////////////////


void Scale_MnvH2D_Array(const TObjArray  HistArray , double Scaler){

unsigned int i = 0;
  for(auto cat : HistArray) {
    ((PlotUtils::MnvH2D*)HistArray.At(i))->Scale(Scaler);
    i++;
  }
}


void BinWidthNorm_MnvH2D_Array(const TObjArray HistArray ){
  std::cout<<"Trying to BinWidth Normalize MnvH2D Hist arrays"<<std::endl;

unsigned int i = 0;
  for(auto cat : HistArray) {
    ((PlotUtils::MnvH2D*)HistArray.At(i))->Scale(1.0,"width");
    i++;
  }
}

void AddFirst_toSecond_MnvH2D_Arrays(const TObjArray HistArray1 , const TObjArray HistArray2){
std::cout<<"Trying to Add MnvH2D Hist arrays"<<std::endl;
unsigned int i = 0;
  for(auto cat : HistArray1) {
    ((PlotUtils::MnvH2D*)HistArray1.At(i))->Add((PlotUtils::MnvH2D*)HistArray2.At(i),1.0);
    i++;
  }
}

void SubractSecond_FromFirst_MnvH2D_Arrays(const TObjArray HistArray1 , const TObjArray HistArray2){
std::cout<<"Trying to SubTract MnvH2D Hist arrays"<<std::endl;
unsigned int i = 0;
  for(auto cat : HistArray1) {
    ((PlotUtils::MnvH2D*)HistArray1.At(i))->Add((PlotUtils::MnvH2D*)HistArray2.At(i),-1.0);
    i++;
  }
}





////////////////////////////////////////

////////////////////////////////////////
