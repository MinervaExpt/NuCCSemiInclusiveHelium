//File: HeliumUtils.cxx
//Brief: Common functions that deal with the ME 1D Helium Analysis framework
//Author: Christian Nguyen christian2nguyen@ufl.edu

#include "HeliumUtils.h"

bool Debugmode = true;
//#ifndef __CINT__
//#include "Variable.h"
//#endif // __CINT__

////////////////////////////////////////
//
////////////////////////////////////////

double GetMax(MnvH1D *h_1,
  MnvH1D *h_2,
  MnvH1D *h_3
){
  double Amax = h_1->GetMaximum();
  double Bmax = h_2->GetMaximum();
  double Cmax = h_3->GetMaximum();
  if(Amax  >= Bmax  && Amax >= Cmax){return Amax;}
  else if (Amax  <= Bmax && Cmax <= Bmax){return Bmax;}
  else{return Cmax;}
}
////////////////////////////////////////
//
////////////////////////////////////////
double GetMax(MnvH1D *h_1,
  MnvH1D *h_2,
  MnvH1D *h_3,
  MnvH1D *h_4
)
{
  double A1  = GetMax(h_1, h_2, h_3);
  double A2 = h_4->GetMaximum();
  if(A1>A2){return A1;}
  else {return A2;}
}

////////////////////////////////////////
//
////////////////////////////////////////
TArrayD GetBinArray(const std::string var_name) {
  std::vector<double> bins_vec;
  if (var_name == "muon_E") {
    bins_vec = {0.0, 2., 3., 4., 5., 8., 10., 13., 16., 25., 35., 50};
  }
  else if (var_name == "muon_PT") {
    bins_vec = {0.0, 0.075, 0.15, 0.25, 0.325, 0.4 ,0.475, 0.55, 0.7 ,0.85, 1.0, 1.25, 1.5, 2.5};
  }
  else if (var_name == "muon_PZ") {
    bins_vec = {1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 6.0, 8.0, 10.0, 15.0, 20.0};
  }
  else if (var_name == "thetamu_deg") {
    bins_vec = {0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 12.0, 14};
  }
  // prepare an array from the bin vector
  TArrayD bins_array(GetTArrayFromVec(bins_vec));
  SortArray(bins_array);
  return bins_array;
}

//==============================================================================
// make vector of bins
//==============================================================================
void Array1D(MnvH1D *hist[], int index, const char *baseName, const char *title, std::vector<double> Bins) {
  std::cout << "Making histogram array: " << baseName << ", of size: " << index << std::endl;
  char tempName[1024];

  for (int i = 0; i < index; i++) {
    sprintf(tempName,"%s_%d",baseName, i);
    hist[i] = new MnvH1D(tempName, tempName, Bins.size()-1,Bins.data());
  }//looping over the first index
}//end of Array1D
////////////////////////////////////////
//
////////////////////////////////////////
void Array2D(MnvH2D *hist[], int index, const char *baseName, const char *title,
  std::vector<double> BinsX, std::vector<double> BinsY) {
    std::cout << "Making histogram array: " << baseName << ", of size: " << index << std::endl;

  char tempName[1024];

  for (int i = 0; i < index; i++) {
    sprintf(tempName,"%s_%d",baseName, i);
    hist[i] = new MnvH2D(tempName, tempName, BinsX.size()-1, BinsX.data(), BinsY.size()-1, BinsY.data());
  }//looping over the first index
}//end of Array1D
////////////////////////////////////////
//
////////////////////////////////////////

std::vector <double> MakeBinVector(int Nbins, double binStart, double binEnd)
{
  std::vector <double> return_vector;
  double Spaceing = (binEnd - binStart) / (double)Nbins;
  double Start = binStart;
  return_vector.push_back(binStart);
  for(int i=0; i<Nbins; ++i )
  {
    Start = Start + Spaceing;
    return_vector.push_back(Start);
  }
  return return_vector;

}
std::vector<double> Make_minervaTrkLenghtBins(){
  std::vector <double> return_vector;
  double recoil_bin_count=0.0;
  for(int ww = 0; ww < 50; ww++ ){
    return_vector.push_back(recoil_bin_count);
    recoil_bin_count = recoil_bin_count + 2.54; // bins in [cm]
  }

  return return_vector;
}
////////////////////////////////////////
//
////////////////////////////////////////
std::vector <double> MakeBinVector_chiSqrt()
{
  std::vector <double> A = MakeBinVector(25, 0.0, 25);
  std::vector <double> B = MakeBinVector(15, 25, 100 );
  std::vector <double> C = MakeBinVector(5, 100, 200 );
  std::vector <double> ABC;
  ABC.reserve( A.size() + B.size() + C.size()); // preallocate memory
  ABC.insert( ABC.end(), A.begin(), A.end() );
  ABC.insert( ABC.end(), B.begin(), B.end() );
  ABC.insert( ABC.end(), C.begin(), C.end() );
  sort( ABC.begin(), ABC.end() );
  ABC.erase( unique( ABC.begin(), ABC.end() ), ABC.end() );
  return ABC;

}
//==============================================================================
// Copy all hists of one file into another file
//==============================================================================
void CopyHists(TFile& fin, TFile& fout) {
  TIter nextkey(fin.GetListOfKeys());
  TKey *key;
  while ((key = (TKey*)nextkey())) {
    TString name=key->GetName();
    PlotUtils::MnvH1D* h=(PlotUtils::MnvH1D*)key->ReadObj();
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
void WritePOT(TFile& fout, const bool is_mc, const float pot) {
  fout.Write(0,TObject::kOverwrite);
  fout.cd();
  const char* name = is_mc ? "mc_pot" : "data_pot";
  PlotUtils::MnvH1D* h_pot = new PlotUtils::MnvH1D(name, name, 1, 0., 1.);
  h_pot->Fill(0.5, pot);
  h_pot->Write();

  //TVectorD mc_pot(1);
  //mc_pot[0] = util.m_mc_pot;
  //mc_pot.Write("mc_pot");
}
//==============================================================================
//==============================================================================

void SetHistColorScheme(PlotUtils::MnvH1D* h, const int type,
                        const int color_scheme) {
  switch(color_scheme){
    case 2:
      h->SetFillColor(CCNuPionIncPlotting::fill_colors2[type]);
      h->SetLineColor(CCNuPionIncPlotting::colors2[type]);
      break;
    case 3:
      h->SetFillColor(CCNuPionIncPlotting::fill_colors3[type]);
      h->SetLineColor(CCNuPionIncPlotting::colors3[type]);
      break;
    case 4:
      h->SetFillColor(CCNuPionIncPlotting::fill_colors4[type]);
      h->SetLineColor(CCNuPionIncPlotting::colors4[type]);
      break;
    default:
      h->SetFillColor(CCNuPionIncPlotting::fill_colors[type]);
      h->SetLineColor(CCNuPionIncPlotting::colors[type]);
  }
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void SortArray(TArrayD& arr) {
  // store in index the correct order of arr
  int size = arr.GetSize();
  int *index = new int[size];
  TMath::Sort(size,arr.GetArray(),index, kFALSE); // default ordering is decreasing. y tho.

  // then make a new array from that correct ordering
  TArrayD dummy(size);
  for(int i=0; i<size; i++) dummy[i] = arr[index[i]];

  // finally set arr
  arr = dummy;
}
//==============================================================================
// Angle and Geometry Functions
//==============================================================================

double FixAngle(double angle) {
  double ret = angle;
  if (ret < 0.0) ret = -1.0*ret;
  if (ret > TMath::Pi()) ret = 2.0*TMath::Pi() - ret;
  return ret;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

double PerpDist( std::vector<double> v0, std::vector<double> v1, std::vector<double> v2) {
  if(v0.size()!=3 || v1.size()!=3 || v2.size()!=3) return -1;

  double ret;

  double M2 = (v2[0]-v1[0])*(v2[0]-v1[0]) + (v2[1]-v1[1])*(v2[1]-v1[1]) +(v2[2]-v1[2])*(v2[2]-v1[2]);
  double V2 = (v1[0]-v0[0])*(v1[0]-v0[0]) + (v1[1]-v0[1])*(v1[1]-v0[1]) +(v1[2]-v0[2])*(v1[2]-v0[2]);
  double MV = (v1[0]-v0[0])*(v2[0]-v1[0]) + (v1[1]-v0[1])*(v2[1]-v1[1]) +(v1[2]-v0[2])*(v2[2]-v1[2]);

  ret = sqrt( V2 - ( MV*MV / M2) );

  return ret;
}


////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

double calcYfromUV(double U, double V) { return (1./sqrt(3.))*(V-U); }
double calcYfromXU(double X, double U) { return (1./sqrt(3.))*(X-2*U); }
double calcYfromXV(double X, double V) { return (1./sqrt(3.))*(2*V-X); }
double calcXfromUV(double U, double V) { return U + V; }
double calcUfromXY(double X, double Y) { return (1./ 2.)*(X - sqrt(3)*Y); }
double calcVfromXY(double X, double Y) { return (1./ 2.)*(X + sqrt(3)*Y); }
double ConvertRadToDeg(double rad) { return rad* TMath::RadToDeg(); }
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

PlotUtils::MnvH1D* Get1DHist(TFile& fin, const char* name) {
  PlotUtils::MnvH1D* h=(PlotUtils::MnvH1D*)fin.Get(name);
  if (h==0) std::cout << "Could not get 1D hist " << name << "\n";
  return h;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

TH1D* GetTH1DHist(TFile& fin, const char* name) {
  TH1D* h=(TH1D*)fin.Get(name);
  if (h==0) std::cout << "Could not get 1D  TH1D hist " << name << "\n";
  return h;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
PlotUtils::MnvH1D* Get1DHist(TFile& fin, std::string name ){
  const char* name_char = name.c_str();
  PlotUtils::MnvH1D* hist = Get1DHist(fin, name_char);
  return hist;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

TH1D* GetTH1DHist(TFile& fin, std::string name ){
  const char* name_char = name.c_str();
  TH1D* hist = GetTH1DHist(fin, name_char);
  return hist;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

PlotUtils::MnvH1D* Get1DHist(TFile& fin, const char* name, bool isFull) {
  PlotUtils::MnvH1D* h=(PlotUtils::MnvH1D*)fin.Get(name);
  std::string Status = isFull ? "Cyro Full" : "Cryo Empty";
  if (h==0) std::cout << "Could not get 1D hist " << name <<" Helium Status  = "<< Status <<"\n";
  return h;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
PlotUtils::MnvH2D* Get2DHist(TFile& fin, const char* name) {
  PlotUtils::MnvH2D* h=(PlotUtils::MnvH2D*)fin.Get(name);
  if (h==0) std::cout << "Could not get 2D hist " << name << "\n";
  return h;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
PlotUtils::MnvH2D* Get2DHist(TFile& fin, const char* name, bool isFull) {
  PlotUtils::MnvH2D* h=(PlotUtils::MnvH2D*)fin.Get(name);
  std::string Status = isFull ? "Cyro Full" : "Cryo Empty";
  if (h==0) std::cout << "Could not get 2D hist " << name <<" Helium Status  = "<< Status <<"\n";
  return h;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
PlotUtils::MnvH2D* Get2DHist(TFile& fin, std::string name ){
  const char* name_char = name.c_str();
  auto hist = Get2DHist(fin, name_char);
  return hist;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
TGraph* GetTGraph(TFile& fin, const char* name){
  TGraph* T_graph =(TGraph*)fin.Get(name);
  if (T_graph==0) std::cout << "Could not get TGraph with name " << name << std::endl;
  return T_graph;

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
TGraph* GetTGraph(TFile& fin, std::string name){
  const char* name_char = name.c_str();
  TGraph* T_graph =GetTGraph(fin, name_char);
  return T_graph;

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
Normal_Fit_Parameters init_default_Normal_Fit_Parameters(){
  Normal_Fit_Parameters output;
  output.mean = 99999;
  output.stddev = 99999;
  return output;

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
TArrayD MakeUniformBinArray(int nbins, double min, double max) {
  double step_size = (max - min)/nbins;
  double arr[nbins+1]; // +1 because binning arrays include top edge.
  for(int i = 0; i <= nbins; ++i) arr[i] = min + i*step_size;
  const int size = sizeof(arr)/sizeof(*arr);
  return TArrayD(size, arr);
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
TArrayD GetSortedArray(const TArrayD& arr) {
  // store in index the correct order of arr
  int size = arr.GetSize();
  int *index = new int[size];
  TMath::Sort(size,arr.GetArray(),index, kFALSE); // default ordering is decreasing. y tho.

  // then make a new array from that correct ordering
  double sorted_array[size];
  for(int i=0; i<size; i++) sorted_array[i] = arr[index[i]];

    // finally return sorted
    return TArrayD(size, sorted_array);
  }

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
TArrayD GetTArrayFromVec(const std::vector<double>& vec) {
  double array[vec.size()];
  std::copy(vec.begin(), vec.end(), array);
  const int size = sizeof(array)/sizeof(*array);
  return TArrayD(size, array);
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string GetPlaylist_Name(ME_helium_Playlists playlist_name) {
  switch (playlist_name) {

    case kME1P:
    return "Minerva ME1P";

    case kME1C:
    return "Minerva ME1C";

    case kME1D:
    return "Minerva ME1D";

    case kME1E:
    return "Minerva ME1E";

    case kME1F:
    return "Minerva ME1F";

    case kME1A:
    return "Minerva ME1A";

    case kME1G:
    return "Minerva ME1G";

    case kME1L:
    return "Minerva ME1L";

    case kME1M:
    return "Minerva ME1M";

    case kME1N:
    return "Minerva ME1N";

    case kME1B:
    return "Minerva ME1B";

    case kME1O:
    return "Minerva ME1O";


    default:
    std::cout << "ERROR: unknown Playlist!" << std::endl;
    return "";
  };
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string GetPlaylist(ME_helium_Playlists playlist_name) {
  switch (playlist_name) {

    case kME1P:
    return "minervame1P";

    case kME1C:
    return "minervame1C";

    case kME1D:
    return "minervame1D";

    case kME1E:
    return "minervame1E";

    case kME1F:
    return "minervame1F";

    case kME1A:
    return "minervame1A";

    case kME1G:
    return "minervame1G";

    case kME1L:
    return "minervame1L";

    case kME1M:
    return "minervame1M";

    case kME1N:
    return "minervame1N";

    case kME1B:
    return "minervame1B";

    case kME1O:
    return "minervame1O";



    default:
    std::cout << "ERROR: unknown Playlist!" << std::endl;
    return "";
  };
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
ME_helium_Status  GetPlaylist_HeliumStatus(ME_helium_Playlists playlist_name) {
  switch (playlist_name) {

    case kME1P:
    return kFULL;

    case kME1C:
    return kFULL;

    case kME1D:
    return kFULL;

    case kME1E:
    return kFULL;

    case kME1F:
    return kFULL;

    case kME1A:
    return kEMPTY;

    case kME1G:
    return kEMPTY;

    case kME1L:
    return kEMPTY;

    case kME1M:
    return kEMPTY;

    case kME1N:
    return kEMPTY;

    default:
    std::cout << "ERROR: unknown Playlist!" << std::endl;
    return kNULL;
  };
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

std::string GetPlaylistStatusString(ME_helium_Status status) {
  switch (status) {
    case kFULL:
    return "Full";

    case kEMPTY:
    return "Empty";

    case kFull_Empty:
    return "F-E";

    case kMC_FULL:
    return "MC Full";

    case kMC_EMPTY:
    return "MC Empty";

    case kDATA_FULL:
    return "Data Full";

    case kDATA_EMPTY:
    return "Data Empty";

    default:
    return "ERROR: unknown playlist cryotank Status !";
  };
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void print_POT_ME_helium_Status(Pot_MapStatusList input){
  std::cout<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;
  std::cout<< "~~~~~~~~~~~Helium Status POT/Scaler Map~~~~~~~"<< std::endl;
  std::cout<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;

for(auto Status: input){
  std::cout<< "Type:  "<< GetPlaylistStatusString(Status.first) << "  POT =  "<< Status.second <<  std::endl;
}

std::cout<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;
std::cout<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
bool IFstatusFullreturntrue(ME_helium_Status input){
  if(input==kFULL){return true;}
  else if (input==kEMPTY){return false;}
  else{
    std::cout<<"Error in failing Status of CryoTank"<<std::endl;
    return false;
  }
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
bool ISTrueIFPlayListHeliumFUll(ME_helium_Playlists playlist_name){
  auto CryoTankStatus  = GetPlaylist_HeliumStatus(playlist_name);
  return IFstatusFullreturntrue(CryoTankStatus);

};
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string GetPlaylist_InitialName(ME_helium_Playlists playlist_name) {
  switch (playlist_name) {
    case kME1P:
    return "1P";

    case kME1C:
    return "1C";

    case kME1D:
    return "1D";

    case kME1E:
    return "1E";

    case kME1F:
    return "1F";

    case kME1A:
    return "1A";

    case kME1G:
    return "1G";

    case kME1L:
    return "1L";

    case kME1M:
    return "1M";

    case kME1N:
    return "1N";

    case kME1B:
    return "1B";

    case kME1O:
    return "1O";
    default:
    std::cout << "ERROR: unknown Playlist!" << std::endl;
    return "ERROR_GetPlaylist_InitialName";
  };
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
ME_helium_Playlists  GetPlaylist_FromString(std::string playlist) {
  /// case-independent
  std::transform(playlist.begin(), playlist.end(), playlist.begin(), ::tolower);

  if(playlist == "minervame1p"){return kME1P; }
  else if(playlist == "minervame1c"){return kME1C; }
  else if(playlist == "minervame1d"){return kME1D; }
  else if(playlist == "minervame1e"){return kME1E; }
  else if(playlist == "minervame1f"){return kME1F; }
  else if(playlist == "minervame1a"){return kME1A; }
  else if(playlist == "minervame1g"){return kME1G; }
  else if(playlist == "minervame1l"){return kME1L; }
  else if(playlist == "minervame1m"){return kME1M; }
  else if(playlist == "minervame1n"){return kME1N; }
  else if(playlist == "minervame1b"){return kME1B; }
  else if(playlist == "minervame1o"){return kME1O; }
  else {assert(0 && "Input Isn't a Helium Playlist ERROR:EventLoop FAIL");}

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string GetPlaylist_txtFILE_path_MasterAnaDev(ME_helium_Playlists playlist, bool is_mc) {

  std::string InitialPlaylist_Name = GetPlaylist_InitialName( playlist);
  std::string Path;
  if(is_mc==true){

    Path = HeliumPlayListInfo_Pathways::MasterAnaDev_ME_LOCAL_PLAYLIST_txtFILE_mc + "MasterAna_MC_ME"+ InitialPlaylist_Name+ ".txt";

  }

  else {
    Path = HeliumPlayListInfo_Pathways::MasterAnaDev_ME_LOCAL_PLAYLIST_txtFILE_data + "MasterAna_ME"+ InitialPlaylist_Name+ "_DATA.txt";

  }

  return Path;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string GetPlaylist_txtFILE_path(ME_helium_Playlists playlist, bool is_mc) {

  std::string InitialPlaylist_Name = GetPlaylist_InitialName( playlist);
  std::string Path;
  if(is_mc==true){

    Path = HeliumPlayListInfo_Pathways::ME_LOCAL_PLAYLIST_txtFILE_mc + "ME_"+ InitialPlaylist_Name+ "_MC.txt";

  }
  else {
    Path = HeliumPlayListInfo_Pathways::ME_LOCAL_PLAYLIST_txtFILE_data + "ME_"+ InitialPlaylist_Name+ "_DATA.txt";

  }

return Path;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string GetPlaylist_txtFILE_path(std::string Name, bool is_mc) {

  std::string Path;
  if(is_mc==true){

    Path = HeliumPlayListInfo_Pathways::ME_LOCAL_PLAYLIST_txtFILE_mc + "ME_"+ Name+ "_MC.txt";

  }
  else {
    Path = HeliumPlayListInfo_Pathways::ME_LOCAL_PLAYLIST_txtFILE_data + "ME_"+ Name+ "_DATA.txt";

  }

  return Path;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string GetPlaylist_ROOT_path(ME_helium_Playlists playlist, bool is_mc ) {

  std::string InitialPlaylist_Name = GetPlaylist_InitialName(playlist);
  std::string Path;

  if(is_mc==true){

    Path = HeliumPlayListInfo_Pathways::ME_PNFS_ROOT_Pathway + "ME_playlist_"+ InitialPlaylist_Name+ "_Merg/*.root";

  }
  else {
    Path = HeliumPlayListInfo_Pathways::ME_PNFS_ROOT_Pathway + "ME_playlist_"+ InitialPlaylist_Name+ "_DATA_Merg/*.root";

  }
  return Path;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string GetPlaylist_ROOT_path(std::string Name, bool is_mc ) {
  std::string Path;

  if(is_mc==true){
    Path = HeliumPlayListInfo_Pathways::ME_PNFS_ROOT_Pathway + "ME_playlist_"+ Name+ "_Merg/*.root";
  }
  else {
    Path = HeliumPlayListInfo_Pathways::ME_PNFS_ROOT_Pathway + "ME_playlist_"+ Name+ "_DATA_Merg/*.root";
  }
  return Path;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string GetPlaylist_ROOT_path_MasterAnaDev(std::string Name, bool is_mc ) {

  std::string Path;

  if(is_mc==true){
    Path = HeliumPlayListInfo_Pathways::ME_PNFS_ROOT_Pathway_MasterAnaDevP2 + "FullDetector/Merged_mc_ana_me"+ Name + "_DualVertex_p2/*.root";
  }
  else {
    Path = HeliumPlayListInfo_Pathways::ME_PNFS_ROOT_Pathway_MasterAnaDevP2 + "Data/Merged_data_ana_me"+ Name + "_DualVertex_p2/*.root";
  }
  return Path;
}

std::string GetPlaylist_ROOT_path_MasterAnaDev(ME_helium_Playlists playlist, bool is_mc ) {

  std::string InitialPlaylist_Name = GetPlaylist_InitialName(playlist);
  std::string Path;

  if(is_mc==true){

    Path = HeliumPlayListInfo_Pathways::ME_PNFS_ROOT_Pathway_MasterAnaDevP2 + "FullDetector/Merged_mc_ana_me"+ InitialPlaylist_Name + "_DualVertex_p2/*.root";

  }
  else {
    Path = HeliumPlayListInfo_Pathways::ME_PNFS_ROOT_Pathway_MasterAnaDevP2 + "Data/Merged_data_ana_me"+ InitialPlaylist_Name+ "_DualVertex_p2/*.root";
  }
  return Path;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string  GetFULLorEmpty(ME_helium_Status playlist_name) {
  switch (playlist_name) {
    case kFULL:
    return "Full";

    case kEMPTY:
    return "Empty";

    default:
    std::cout << "ERROR: unknown CryoTank status!" << std::endl;
    return "";
  };
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
Particle_type  GetParticlegroup_type(int pdg) {

  int count=-999;
  Particle_type Particle;

  //std::cout<< "pdg= "<<pdg<<std::endl;
 if(pdg == 11)                 {count=1;}//MeV electron
  else if (pdg == -11)          {count=2;} // e+
  else if (pdg == 111)          {count=3;} //Pion0
  else if (pdg == 211)          {count=4;} //Pion_plus
  else if (pdg == -211)         {count=5;} //Pion_neg
  else if (pdg == 321)          {count=6;} //Kaon_plus
  else if (pdg == -321)         {count=7;} //Kaon_neg
  else if (pdg == 311)          {count=8;} //Kaon_0)
  else if (pdg == -311)         {count=9;} //anti-Kaon_0)
  else if (pdg == 130)          {count=10;} //Kaon^0_L) //
  else if (pdg == 2212)         {count=11;} //Proton
  else if (pdg == -2212)        {count=12;} //antiProton
  else if (pdg == 2112 || pdg == -2112){count=13;} //neutron
  else if (pdg == 22)           {count=14;} //photon
  else if (pdg == -13)           {count=15;} //muon_plus
  else if (pdg == 13)           {count=16;} //muon_neg
  else if (pdg == 3122||pdg == -3122)         {count=17;} //Lamdba
  else if (pdg == 3222)         {count=18;} //Sigma_plus
  else if (pdg == 3212||pdg == -3212)         {count=19;} //Sigma_0
  else if (pdg == 221)          {count=20;} //eta
  else if (pdg == 1000130270)   {count=21;} //27Al
  else if (pdg == 1000020040)   {count=22;} //4He
  else if (pdg == 1000020030)   {count=23;} //3He
  else if (pdg == 1000010020)   {count=24;} //2 deuterium
  else if (pdg == 1000010060)   {count=25;} //16Oxygen)
  else if (pdg == 1000030060)   {count=26;} //Li6
  else if (pdg == 12)           {count=27;} // electron neutrino
  else if (pdg == -12)           {count=28;} // electron neutrino
  else if (pdg == 14)           {count=29;} // muon neutrino
  else if (pdg == -14)          {count=30;} // muon  antineutrino
  else if (pdg == 1000030070)   {count=31;}  // Li7Nucleus
  else if (pdg == -9999 || pdg == -999 )        {count=0;}  // particle has unknown trajectory thus no particle
  else {count= 0; }



  if (count == 0 ) {Particle = kParticle_N_A;}
  else if (count == 1 || count == 2)  {Particle = kElectron;}
  else if (count == 3) { Particle = kPion_0;}
  else if (count == 4) { Particle = kPion_pos;}
  else if (count == 5) { Particle = kPion_neg;}
  else if (count == 6 || count == 7 || count == 8 || count == 9 || count == 10) {Particle = kKaon;}
  else if (count == 11 || count == 12) {Particle = kProton;}
  else if (count == 13) {Particle = kNeutron;}
  else if (count == 14) {Particle = kGamma;}
  else if (count == 15 || count == 16) {Particle = kMuon;}
  else if ((count > 18 && count < 22) ||(count > 22 && count < 27) || count == 31) {Particle = kParticle_OTHER;}
  else if (count == 27 ) {Particle = kNeutrino_electron;}
  else if (count == 28 || count == 30 ) {Particle = kAnti_Neutrino;}
  else if (count == 29 ) {Particle = kNeutrino_muon;}
  else if (count == 22 ) {Particle = kFourHelium;}
  else if (count == 17 ) {Particle = kLamdba;}
  else if (count == 18 ) {Particle = kSigma_plus;}
  else{Particle = kParticle_N_A;}
  return Particle;
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
Particle_type  GetParticlegroup_typeReduced(int pdg) {

  int count=-999;
  Particle_type Particle;

  //std::cout<< "pdg= "<<pdg<<std::endl;
 if(pdg == 11)                 {count=1;}//MeV electron
  else if (pdg == -11)          {count=2;} // e+
  else if (pdg == 111)          {count=3;} //Pion0
  else if (pdg == 211)          {count=4;} //Pion_plus
  else if (pdg == -211)         {count=5;} //Pion_neg
  else if (pdg == 321)          {count=6;} //Kaon_plus
  else if (pdg == -321)         {count=7;} //Kaon_neg
  else if (pdg == 311)          {count=8;} //Kaon_0)
  else if (pdg == -311)         {count=9;} //anti-Kaon_0)
  else if (pdg == 130)          {count=10;} //Kaon^0_L) //
  else if (pdg == 2212)         {count=11;} //Proton
  else if (pdg == -2212)        {count=12;} //antiProton
  else if (pdg == 2112 || pdg == -2112){count=13;} //neutron
  else if (pdg == 22)           {count=14;} //photon
  else if (pdg == -13)           {count=15;} //muon_plus
  else if (pdg == 13)           {count=16;} //muon_neg
  else if (pdg == 3122||pdg == -3122)         {count=17;} //Lamdba
  else if (pdg == 3222)         {count=18;} //Sigma_plus
  else if (pdg == 3212||pdg == -3212)         {count=19;} //Sigma_0
  else if (pdg == 221)          {count=20;} //eta
  else if (pdg == 1000130270)   {count=21;} //27Al
  else if (pdg == 1000020040)   {count=22;} //4He
  else if (pdg == 1000020030)   {count=23;} //3He
  else if (pdg == 1000010020)   {count=24;} //2 deuterium
  else if (pdg == 1000010060)   {count=25;} //16Oxygen)
  else if (pdg == 1000030060)   {count=26;} //Li6
  else if (pdg == 12)           {count=27;} // electron neutrino
  else if (pdg == -12)           {count=28;} // electron neutrino
  else if (pdg == 14)           {count=29;} // muon neutrino
  else if (pdg == -14)          {count=30;} // muon  antineutrino
  else if (pdg == 1000030070)   {count=31;}  // Li7Nucleus
  else if (pdg == -9999 || pdg == -999 )        {count=0;}  // particle has unknown trajectory thus no particle
  else {count= 0; }


  if (count == 0 ) {Particle = kParticle_OTHER;}
  else if (count == 1 || count == 2||count == 3||count == 14)  {Particle = kPion_0_Electron_kGamma;}
  else if ( count == 8 || count == 9 || count == 13||
    count == 27||count == 28 ||count == 29||count == 30) { Particle = kParticle_neutral;}
  else if (count == 4||count == 5) { Particle = kPion_pos_neg;}
  else if (count == 11 || count == 12) {Particle = kProton;}
  else if (count == 15 || count == 16) {Particle = kMuon;}
  else if (count == 6 || count == 7 ||  count == 10||
    (count > 18 && count < 22) ||(count > 22 && count < 27)
     || count == 31||count == 22||count == 17||count == 18) {Particle = kParticle_OTHER;}
  else{Particle = kParticle_OTHER;}

  return Particle;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void Rename_particleStacks(TObjArray ObjArry_input){

  int nEntries =ObjArry_input.GetEntries();

  for(int  Entry = 0; Entry < nEntries ;Entry++){

    std::string ParticleName = ((PlotUtils::MnvH2D*)ObjArry_input.At(Entry))->GetTitle();
    if(ParticleName=="Proton"){((PlotUtils::MnvH2D*)ObjArry_input.At(Entry))->SetTitle("Proton");}
    else if(ParticleName=="Pion_pos_neg"){((PlotUtils::MnvH2D*)ObjArry_input.At(Entry))->SetTitle("#pi^{#pm}");}
    else if(ParticleName=="Neutral"){((PlotUtils::MnvH2D*)ObjArry_input.At(Entry))->SetTitle("Neutral 0#pi^{0}");}
    else if(ParticleName=="Muon"){((PlotUtils::MnvH2D*)ObjArry_input.At(Entry))->SetTitle("#mu^{#pm}");}
    else if(ParticleName=="Pion_0_Electron_kGamma"){((PlotUtils::MnvH2D*)ObjArry_input.At(Entry))->SetTitle("#pi^{0}, e^{#pm}, #gamma");}
    else if(ParticleName=="Other"){((PlotUtils::MnvH2D*)ObjArry_input.At(Entry))->SetTitle("Other");}
  }

  return;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::vector<Particle_type> MakeParticle_list(std::vector<int> inputpdgs ){
  std::vector<Particle_type> outputvector;

  for(auto cat :inputpdgs ){
    auto input_Particle = GetParticlegroup_type(cat);
    outputvector.push_back(input_Particle);
  }
  return outputvector;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
Topologies_type GetTopologiesType(std::vector <Particle_type> inputVector){

  int NProtons = 0;
  int NPions = 0;
  int NOther = 0;

  for(auto particle:inputVector ){

    if(kProton==particle){NProtons++;}
    else if(kPion_neg==particle || kPion_pos==particle ||kPion_0==particle){NPions++;}
    else{NOther++;}

  }
  if(NProtons==0 && NPions==0 ){return kCC0P0Pi;}
  else if(NProtons==1 && NPions==0 ){return kCC1P0Pi;}
  else if(NProtons==2 && NPions==0 ){return kCC2P0Pi;}
  else{return kCCOther;}
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

Particle_type  GetParticlegroup_typeProtonandpion_other(int pdg) {

  Particle_type type =  GetParticlegroup_type (pdg);

  switch (type) {
    case kPion_0:
    return kPion_0;

    case kPion_neg:
    return kPion_neg;

    case kPion_pos:
    return kPion_pos;

    case kProton:
    return kProton;

    case kNeutron:
    return kNeutron;

    default:
    return kParticle_OTHER;
  };
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
Interaction_type GetInteractionenum(int Interaction) {

  Interaction_type Interaction_type;
  if(Interaction==0){Interaction_type = kInteraction_NONE;}
  else if(Interaction==1){Interaction_type = kElastic;}
  else if(Interaction==2 ||Interaction==4 ) {Interaction_type = kRes_Coh_Pion;}
   else if(Interaction==3){Interaction_type = kDIS;}
   else if(Interaction==8){Interaction_type = k2p2h;}
   else {Interaction_type = kInteraction_OTHER;} // all other types, 5-8 5-kamnugamma , KimD-6, kNUEEL,7, KunknownINT-8
   return Interaction_type;

 }
 ////////////////////////////////////////////////////////////////////////////////
 //
 ////////////////////////////////////////////////////////////////////////////////
Interaction_type returnDIStype_InputWmassGeV(double Wmass, double Q_sqrt){

  if(Wmass > 2 && Q_sqrt > 1.0){ return kDISHard;}
  else if(Wmass > 2 && Q_sqrt <  1.0){ return kDISSoft;}
  else{return kDISSIS;}

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
Interaction_type GetInteractionenum_DISBreakdown(int Interaction , double Wmass, double Q_sqrt, int resID) {

  Interaction_type Interaction_type;

  if(Interaction==1)
  {
    Interaction_type = kElastic;
  }

  else if(Interaction==2 )
  {
    if(resID == 0) {Interaction_type = kdeltaRES;}
    else if(resID != 0){Interaction_type = kHeavierRES;}
  }

  else if(Interaction==3)
  {
    Interaction_type =  returnDIStype_InputWmassGeV(Wmass, Q_sqrt);
  }

  else if(Interaction==8)
  {
    Interaction_type = k2p2h;
  }

  else {Interaction_type = kInteraction_OTHER;} // all other types, 5-8 5-kamnugamma , KimD-6, kNUEEL,7, KunknownINT-8 coh pions


  return Interaction_type;

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
Topologies_type GetTopologic_type(std::vector<int> input_pdg){

  std::vector<Particle_type> Particle_vector;
  for(auto cat: input_pdg){

    Particle_type input = GetParticlegroup_typeReduced(cat);
    Particle_vector.push_back(input);
  }

  return  GetTopologiesType(Particle_vector);

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
  Material_type GetMaterial_TargetZenum(int targetZ_input){
    Material_type targetZ;

    if (targetZ_input == 2){ targetZ = kHelium;}//Helium}
    else if (targetZ_input == 6) {targetZ = kCarbon;}//Carbon
    else if (targetZ_input == 26) {targetZ = kIron;}//Iron
    else if (targetZ_input == 82) {targetZ = kLead;}//Lead
    else if (targetZ_input == 13){targetZ = kAluminium;}//Aluminium
    else {targetZ_input = kMaterial_OTHER;} //other
    return targetZ;
 }
 ////////////////////////////////////////////////////////////////////////////////
 //
 ////////////////////////////////////////////////////////////////////////////////
 int  GetColorNInteraction(Interaction_type playlist_name) {
   switch (playlist_name) {
     case kElastic:
     return TColor::GetColor("#FFD700");

     case kRes_Coh_Pion:
     return TColor::GetColor("#FF0000");

     case kDIS:
     return TColor::GetColor("#87CEEB");

     case k2p2h:
     return TColor::GetColor( 148, 255, 181 );

     case kInteraction_OTHER:
     return TColor::GetColor("#32CD32");

     case kInteraction_NONE :
     return TColor::GetColor("#DA70D6");

     case kInteraction_Total:
     return 0;

     default:
     std::cout << "ERROR: unknown Interaction Type!" << std::endl;
     return 0;
   };
 }
 ////////////////////////////////////////////////////////////////////////////////
 //
 ////////////////////////////////////////////////////////////////////////////////
int  GetColorNMaterial(Material_type playlist_name) {
  int color=1;
  switch (playlist_name) {
    case kIron:
    return  TColor::GetColor("#FFD700");

    case kHelium:
    return  TColor::GetColor("#87CEEB");

    case kCarbon:
    return  TColor::GetColor("#ed9c00");

    case kLead:
    return  TColor::GetColor("#D3D3D3");

    case kAluminium:
    return  TColor::GetColor("#DA70D6");

    case kMaterial_OTHER:
    return  TColor::GetColor("#32CD32");

    case kMaterial_Total:
    return  TColor::GetColor("#00FFFF");

    default:
    std::cout << "ERROR: unknown Material Type!" << std::endl;
    return color;
  };

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
int  GetColorNParticle(Particle_type playlist_name) {
  switch (playlist_name) {
    case kElectron:
    return TColor::GetColor("#FFD700");

    case kPion_0:
    return TColor::GetColor("#FF0000");

    case kPion_neg:
    return TColor::GetColor("#FF0000");

    case kPion_pos:
    return TColor::GetColor("#FF0000");

    case kKaon:
    return TColor::GetColor("#DA70D6");

    case kProton:
    return TColor::GetColor("#87CEEB");

    case kNeutron:
    return TColor::GetColor("#FF0800");

    case kMuon:
    return TColor::GetColor("#D3D3D3");

    case kParticle_OTHER:
    return TColor::GetColor("#800000");

    case kGamma:
    return TColor::GetColor("#555555");

    case kNeutrino_muon:
    return TColor::GetColor("#32CD32");

    case kNeutrino_electron:
    return TColor::GetColor("#32CD32");


    case kAnti_Neutrino:
    return TColor::GetColor("#32CD32");

    case kParticle_N_A:
    return TColor::GetColor("#00FFFF");

    case kFourHelium:
    return TColor::GetColor("#00FFFF");

    case kParticle_Total:
    return 0;

    default:
    std::cout << "ERROR: unknown Particle Type!" << std::endl;
    return 0;
  };
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
Material_type getMaterial_fromstring(const char *type){

  if(!(strcmp(type,"Other"))){return kMaterial_OTHER;}
  else if(!(strcmp(type,"Iron"))){return kIron;}
  else if(!(strcmp(type,"Carbon"))){return kCarbon;}
  else if(!(strcmp(type,"Lead"))){return kLead;}
  else if(!(strcmp(type,"Aluminium"))){return kAluminium;}
  else if(!(strcmp(type,"Helium"))){return kHelium;}

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
Interaction_type getInteraction_fromstring(const char *type){

  if(!(strcmp(type,"Other"))){return kInteraction_OTHER;}
  else if(!(strcmp(type,"None"))){return kInteraction_NONE;}
  else if(!(strcmp(type,"DIS"))){return kDIS;}
  else if(!(strcmp(type,"2p2h"))){return k2p2h;}
  else if(!(strcmp(type,"1Pion"))){return kRes_Coh_Pion;}
  else if(!(strcmp(type,"Elastic"))){return kElastic;}
  else if(!(strcmp(type,"QE"))){return kElastic;}
  else if(!(strcmp(type,"HeavierRes"))){return kHeavierRES;}
  else if(!(strcmp(type,"#DeltaRes"))){return kdeltaRES;}
  else if(!(strcmp(type,"SIS"))){return kDISSIS;}
  else if(!(strcmp(type,"SoftDIS"))){return kDISSoft;}
  else if(!(strcmp(type,"HardDIS"))){return kDISHard;}



}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
Particle_type getParticle_fromstring(const char *type){
  if(!(strcmp(type,"N_A"))){return kParticle_N_A;}
  else if(!(strcmp(type,"Other"))){return kParticle_OTHER;}
  else if(!(strcmp(type,"Electron"))){return kElectron;}
  else if(!(strcmp(type,"Muon"))){return kMuon;}
  else if(!(strcmp(type,"Gamma"))){return kGamma;}
  else if(!(strcmp(type,"Neutrino_muon"))){return kNeutrino_muon;}
  else if(!(strcmp(type,"Neutrino_electron"))){return kNeutrino_electron;}
  else if(!(strcmp(type,"Anti_Neutrino"))){return kAnti_Neutrino;}
  else if(!(strcmp(type,"Kaon"))){return kKaon;}
  else if(!(strcmp(type,"Pi0"))){return kPion_0;}
  else if(!(strcmp(type,"Pi^{-}"))){return kPion_neg;}
  else if(!(strcmp(type,"Pi^{+}"))){return kPion_pos;}
  else if(!(strcmp(type,"Proton"))){return kProton;}
  else if(!(strcmp(type,"Neutron"))){return kNeutron;}
  else if(!(strcmp(type,"{}^{4}He"))){return kFourHelium;}
  else if(!(strcmp(type,"Lamdba"))){return kLamdba;}
  else if(!(strcmp(type,"Sigma^{+}"))){return kSigma_plus;}
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
TrackType getTrackType_fromstring(const char *type){

  if(!(strcmp(type,"ShortTracks"))){return kShort;}
  else if(!(strcmp(type,"LongTracks"))){return kLong;}
  else if(!(strcmp(type,"OtherLongTracks"))){return kOtherLong;}
  else if(!(strcmp(type,"NotDefinedTracks"))){return kNotdefinedTrack;}
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
VertexOptions getVertexOptions_fromstring(const char *type){
  if(!(strcmp(type,     "VertexOpt1"))){return kOpt_1;}
  else if(!(strcmp(type,"VertexOpt2"))){return kOpt_2;}
  else if(!(strcmp(type,"VertexOpt3"))){return kOpt_3;}
  else if(!(strcmp(type,"VertexOpt4"))){return kOpt_4;}
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
boolNTrack getboolNTrack_fromstring(const char *type){
  if(!(strcmp(type,"OneTrkTrue"))){return kone_Trk;}
  else if(!(strcmp(type,"TwoTrkTrue"))){return ktwo_Trk;}
  else if(!(strcmp(type,"morethan2TrkTrue"))){return kmore_Trk;}
  else if(!(strcmp(type,"AllfalseTrk"))){return kallfalseTrk;}
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string  GetVetowall_Title( VetoWall_vars vetowall_input) {
  switch (vetowall_input) {

    case kmatchToVeto:
    return "Match to Veto wall";

    case knumbermatchToVeto:
    return "Number of Track Match to Vetowall";

    case kSixPush:
    return "SixPush Matches";

    case kextrapnowalls:
    return "Extrapolated to No Vetowalls";

    case kextrapwall1:
    return "Extrapolated to Vetowall One";

    case  kextrapwall2:
    return "Extrapolated to Vetowall Two";

    case kextrapbothwalls:
    return "Extrapolated to Vetowall Both";

    case kMuonTrkMatchToVETOwalloff:
    return "Extrapolated to Vetowall when Off Voltage";

    case kPMTMap_On:
    return "Veto Wall PMT Status Voltage is On";

    case kPMTMap_Off:
    return "Veto Wall PMT Status Voltage is OFF";


    default: std::cout << "ERROR: unknown case for Vetwall name!" << std::endl;
    return "";

  };//end of switch

}//
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string  GetVertexCryoTitleName(CryoVertex playlist_name) {
  switch (playlist_name) {
    case kX:
    return "Vertex X";

    case kY:
    return "Vertex Y";

    case kZ:
    return "Vertex Z";

    case kR:
    return "Vertex R";

    case kRR:
    return "Vertex R^{2}";

    case kTRUTH_X:
    return "TrueVertex X";

    case kTRUTH_Y:
    return "TrueVertex Y";

    case kTRUTH_Z:
    return "TrueVertex Z";

    case kTRUTH_R:
    return "TrueVertex R";

    case kfitConverge:
    return "CryoVertex ChiSqFit";

    case kdistance_edge:
    return "Vertex Distance to Nearest Wall";

    case kdistance_edge_fiducial:
    return "Vertex Distance to Nearest Wall";

    case kdistance_downstreamcap:
    return"Vertex Distance to Downstream Cap";

    case kdistance_upstreamcap:
    return"Vertex Distance to Upstream Cap";

    default:
    std::cout << "ERROR: unknown Truth Varible Name!" << std::endl;
    return "";
  };
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string GetMuonVarTitleName(MuonVar playlist_name) {
  switch (playlist_name) {
    case kP_T:
    return "Muon P_{T}";

    case kE:
    return "Muon E";

    case kP_Z:
    return "Muon P_{#parallel}";

    case kAngleWRTB:
    return "#theta_{#mu} (wrtb)";

    case kTRUTH_P_T:
    return "Muon TRUE P_{T}";

    case kTRUTH_E:
    return "Muon TRUE E";

    case kTRUTH_P_Z:
    return "Muon TRUE P_{Z}";

    case kTRUTH_AngleWRTB:
    return "TRUE #theta_{#mu} (wrtb)";

    case kDOCA_muon:
    return "Muon DOCA";

    case kcurvatureSig:
    return "Muon Curvature Significance";

    case kminosMuon_Energy:
    return "Muon Minos Energy (GeV)";

    case kminosStart_X:
    return "Starting X Position of Muon in Minos";

    case kminosStart_Y:
    return "Starting Y Position of Muon in Minos";

    case kminosStart_Z:
    return "Starting Z Position of Muon in Minos";

    case kminosEnd_X:
    return "Ending X Position of Muon in Minos";

    case kminosEnd_Y:
    return "Ending Y Position of Muon in Minos";

    case kminosEnd_Z:
    return "Ending Z Position of Muon in Minos";

    case kmuonFirstNodeX:
    return "X Position of First Node of Muon Track";

    case kmuonFirstNodeY:
    return "Y Position of First Node of Muon Track";

    case kmuonFirstNodeZ:
    return "Z Position of First Node of Muon Track";

    case kmuonLastNodeX:
    return "X Position of Last Node of Muon Track";

    case kmuonLastNodeY:
    return "Y Position of Last Node of Muon Track";

    case kmuonLastNodeZ:
    return "Z Position of Last Node of Muon Track";

    case kCharge:
    return "Muon Charge";

    case kMuonMatchtoMinos:
    return "Muon Match to Minos ";

    case  ktracksize:
    return "Number of Trks";

    default:
    std::cout << "Unknown Muon Varible Title" << std::endl;
    return "";
  };
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

std::string GetMuonVarpdfName(MuonVar playlist_name) {

  switch (playlist_name) {
    case kP_T:
    return "muonPT";

    case kE:
    return "MuonE";

    case kP_Z:
    return "MuonPZ";

    case kAngleWRTB:
    return "Muontheta";

    case kTRUTH_P_T:
    return "TRUEmuonPT";

    case kTRUTH_E:
    return "TRUEmuonE";

    case kTRUTH_P_Z:
    return "TRUEmuonPZ";

    case kTRUTH_AngleWRTB:
    return "TRUEMuontheta";

    case kDOCA_muon:
    return "MuonDOCA";

    case kcurvatureSig:
    return "Muon_Curvature_Significance";

    case kminosMuon_Energy:
    return "Muon_Minos_Energy";

    case kminosStart_X:
    return "minosStart_X";

    case kminosStart_Y:
    return "minosStart_Y";

    case kminosStart_Z:
    return "minosStart_Z";

    case kminosEnd_X:
    return "kminosEnd_X";

    case kminosEnd_Y:
    return "kminosEnd_Y";

    case kminosEnd_Z:
    return "kminosEnd_Z";

    case kmuonFirstNodeX:
    return "muonFirstNodeX";

    case kmuonFirstNodeY:
    return "muonFirstNodeY";

    case kmuonFirstNodeZ:
    return "muonFirstNodeZ";

    case kmuonLastNodeX:
    return "muonLastNodeX";

    case kmuonLastNodeY:
    return "muonLastNodeY";

    case kmuonLastNodeZ:
    return "muonLastNodeZ";

    case kCharge:
    return "MuonCharge";

    case kMuonMatchtoMinos:
    return "MuonMatchMinos ";

    case  ktracksize:
    return "NTrks";

    default:
    std::cout << "Unknown Muon Varible Title" << std::endl;
    return "";
  };
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string GetMuonVarTitleNameFORLatex(MuonVar playlist_name) {

  switch (playlist_name) {
    case kP_T:
    return "Muon P_{T}";

    case kE:
    return "E_{\\mu}";

    case kP_Z:
    return "Muon P_{\\parallel}";

    case kAngleWRTB:
    return "\\theta_{\\mu} (wrtb)";

    case kTRUTH_P_T:
    return "Muon TRUE P_{T}";

    case kTRUTH_E:
    return "Muon TRUE E";

    case kTRUTH_P_Z:
    return "Muon TRUE P_{Z}";

    case kTRUTH_AngleWRTB:
    return "TRUE \\theta_{\\mu} (wrtb)";

    case kDOCA_muon:
    return "Muon DOCA";

    case kcurvatureSig:
    return "Muon Curvature Significance";

    case kminosMuon_Energy:
    return "Muon Minos Energy (GeV)";

    case kminosStart_X:
    return "Starting X Position of Muon in Minos";

    case kminosStart_Y:
    return "Starting Y Position of Muon in Minos";

    case kminosStart_Z:
    return "Starting Z Position of Muon in Minos";

    case kminosEnd_X:
    return "Ending X Position of Muon in Minos";

    case kminosEnd_Y:
    return "Ending Y Position of Muon in Minos";

    case kminosEnd_Z:
    return "Ending Z Position of Muon in Minos";

    case kmuonFirstNodeX:
    return "X Position of First Node of Muon Track";

    case kmuonFirstNodeY:
    return "Y Position of First Node of Muon Track";

    case kmuonFirstNodeZ:
    return "Z Position of First Node of Muon Track";

    case kmuonLastNodeX:
    return "X Position of Last Node of Muon Track";

    case kmuonLastNodeY:
    return "Y Position of Last Node of Muon Track";

    case kmuonLastNodeZ:
    return "Z Position of Last Node of Muon Track";

    case kCharge:
    return "Muon Charge";

    case kMuonMatchtoMinos:
    return "Muon Match to Minos ";

    case kMuonMatchtoVeto:
    return "Muon not match to Veto";

    case  ktracksize:
    return "Number of Trks";

    default:
    std::cout << "Unknown Muon Varible Title" << std::endl;
    return "";
  };
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string GetMuonVar_crosssection(MuonVar playlist_name) {

  switch (playlist_name) {
    case kP_T:
    return "P_{T}";

    case kE:
    return "E_{#mu}";

    case kP_Z:
    return "P_{#parallel}";

    case kAngleWRTB:
    return "#theta_{#mu}";

    default:
    std::cout << "Unknown Muon Varible Title" << std::endl;
    return "";
  };
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string GetsecondTrkTitleName(SecondTrkVar playlist_name) {

  switch (playlist_name) {
    case ksecE:
    return "KE_{2ndTrk}";

    case kThetamid:
    return "#theta_{2ndTrk}";

    case kTheta:
    return "#theta_{2ndTrk}";

    case kOpenAngle:
    return "#theta_{Open}";

    case kPathway:
    return "2ndTrk_{PathLength}";

    case ksec_tracklength_minerva:
    return "2ndTrk_{Length}";

    case kDOCA:
    return "2ndTrk DOCA";

    case kFirstsecTrk_Xnode:
    return "2ndTrk First X Node";

    case kFirstsecTrk_Ynode:
    return "2ndTrk First Y Node";

    case kFirstsecTrk_Znode:
    return "2ndTrk First Z Node";

    case  kLastsecTrk_Xnode:
    return "2ndTrk Last X Node";

    case  kLastsecTrk_Ynode:
    return "2ndTrk Last Y Node";

    case  kLastsecTrk_Znode:
    return "2ndTrk Last Z Node";

    default:
    std::cout << "ERROR: unknown name!" << std::endl;
    return "";

  };//end of switch


}//end of funtion

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string GetsecondTrkTitleNameforLatex(SecondTrkVar playlist_name) {

  switch (playlist_name) {
    case ksecE:
    return "KE_{2ndTrk}";

    case kThetamid:
    return "\\theta_{2ndTrk}";

    case kTheta:
    return "\\theta_{2ndTrk}";

    case kOpenAngle:
    return "\\theta_{Open}";

    case kPathway:
    return "PathLength_{2ndTrk}";

    case ksec_tracklength_minerva:
    return "2ndTrk_{Length}";

    case kDOCA:
    return "2ndTrk DOCA";

    case kFirstsecTrk_Xnode:
    return "2ndTrk First X Node";

    case kFirstsecTrk_Ynode:
    return "2ndTrk First Y Node";

    case kFirstsecTrk_Znode:
    return "2ndTrk First Z Node";

    case  kLastsecTrk_Xnode:
    return "2ndTrk Last X Node";

    case  kLastsecTrk_Ynode:
    return "2ndTrk Last Y Node";

    case  kLastsecTrk_Znode:
    return "2ndTrk Last Z Node";

    default:
    std::cout << "ERROR: unknown name!" << std::endl;
    return "";

  };//end of switch


}//end of funtion
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string GetsecondTrk_AXIS_TitleName(SecondTrkVar playlist_name) {

  switch (playlist_name) {
    case ksecE:
    return "KE [GeV]";

    case kThetamid:
    return "Angle (wrtb) [Deg]";

    case kTheta:
    return "Angle (wrtb) [Deg]";

    case kOpenAngle:
    return "OpenAngle [Deg]";

    case kPathway:
    return "PathLength [g/cm^{2}]";

    case ksec_tracklength_minerva:
    return "Track Length [cm]";

    case kDOCA:
    return "DOCA [mm]";

    case kFirstsecTrk_Xnode:
    return  "2ndTrk First Node X [mm]";

    case kFirstsecTrk_Ynode:
    return  "2ndTrk First Node Y [mm]";

    case kFirstsecTrk_Znode:
    return  "2ndTrk First Node Z [mm]";

    case  kLastsecTrk_Xnode:
    return "2ndTrk last Node X [mm]";

    case  kLastsecTrk_Ynode:
    return "2ndTrk last Node Y [mm]";

    case  kLastsecTrk_Znode:
    return "2ndTrk last Node Z [mm]";


    default:
    std::cout << "ERROR: unknown name!" << std::endl;
    return "";

  };//end of switch

}//end of funtion
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////


std::string  GetNameInteraction(Interaction_type playlist_name) {
  switch (playlist_name) {
    case kElastic:
    return "QE";

    case kRes_Coh_Pion:
    return "Res + Coh Pion";

    case kHeavierRES:
    return "HeavierRes";

    case kdeltaRES:
    return "#DeltaRes";

    case kDIS:
    return "DIS";

    case kDISSIS:
    return "SIS";

    case kDISHard:
    return "Soft DIS";

    case kDISSoft:
    return "Hard DIS";

    case k2p2h:
    return "2p2h";

    case kInteraction_OTHER:
    return "Other";

    case kInteraction_Total:
    return "total";

    case kInteraction_NONE:
    return "None";

    default:
    std::cout << "ERROR: unknown Interaction Type!" << std::endl;
    return "";
  };
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string  GetNameMaterial(Material_type playlist_name) {
  switch (playlist_name) {
    case kIron:
    return "Iron";

    case kHelium:
    return "Helium";

    case kCarbon:
    return "Carbon";

    case kLead:
    return "Lead";

    case kAluminium:
    return "Aluminium";

    case kMaterial_OTHER:
    return "Other";

    case kMaterial_Total:
    return "total";

    default:
    std::cout << "ERROR: unknown Material Type!" << std::endl;
    return "";
  };
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string  GetNameTrack(TrackType playlist_name) {
  switch (playlist_name) {

    case kShort:
    return "ShortTracks";

    case kLong:
    return "LongTracks";

    case kOtherLong:
    return "OtherLongTracks";

    case kNotdefinedTrack:
    return "NotDefinedTracks";
    default:
    std::cout << "ERROR: unknown Track Type!" << std::endl;
    return "";
  };
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string  GetNameVertexOption(VertexOptions playlist_name) {
  switch (playlist_name) {

    case kOpt_1:
    return "VertexOpt1";

    case kOpt_2:
    return "VertexOpt2";

    case kOpt_3:
    return "VertexOpt3";

    case kOpt_4:
    return "VertexOpt4";

    default:
    std::cout << "ERROR: unknown Track Type!" << std::endl;
    return "";
  };
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string  GetName_boolNTrack(boolNTrack playlist_name) {
  switch (playlist_name) {

    case kone_Trk:
    return "OneTrkTrue";

    case ktwo_Trk:
    return "TwoTrkTrue";

    case kmore_Trk:
    return "morethan2TrkTrue";

    case kallfalseTrk:
    return "AllfalseTrk";

    default:
    std::cout << "ERROR: unknown boolNTrack Type!" << std::endl;
    return "";
  };
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string  GetNameParticle(Particle_type playlist_name) {
  switch (playlist_name) {
    case kElectron:
    return "Electron";

    case kPion_0:
    return "Pi0";

    case kPion_neg:
    return "Pi^{-}";

    case kPion_pos:
    return "Pi^{+}";

    case kKaon:
    return "Kaon";

    case kProton:
    return "Proton";

    case kNeutron:
    return "Neutron";

    case kMuon:
    return "Muon";

    case kParticle_OTHER:
    return "Other";

    case kParticle_Total:
    return "total";

    default:
    std::cout << "ERROR: unknown Particle Type!" << std::endl;
    return "";
  };
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string  GetMuonVarHistName(MuonVar playlist_name) {
  switch (playlist_name) {
    case kP_T:
    return "h_MuonPT";

    case kE:
    return "h_MuonE";

    case kP_Z:
    return "h_MuonPZ";

    case kAngleWRTB:
    return "h_MuonTheta";

    case kCharge:
    return "h_MuonCharge";

    case kMuonMatchtoMinos:
    return "h_MuonMatchtoMinos";

    case kAngleWRTBhelium:
    return "h_MuonTheta_helium";

    case kAnglePhi:
    return "h_MuonPhi";

    case kDOCA_muon:
    return "h_MuonDOCA";

    case kcurvatureSig:
    return "h_MuonCurvatureSig";

    case kminosMuon_Energy:
    return "h_muon_MINOS_E";

    case kminos_R:
    return "h_muon_minosR";

    case kminosStart_X:
    return "h_muon_minosStart_X";

    case kminosStart_Y:
    return "h_muon_minosStart_Y";

    case kminosStart_Z:
    return "h_muon_minosStart_Z";

    case kminosEnd_X:
    return "h_muon_minosEnd_X";

    case kminosEnd_Y:
    return "h_muon_minosEnd_Y";

    case kminosEnd_Z:
    return "h_muon_minosEnd_Z";

    case kmuonFirstNodeX:
    return "h_muon_StartNode_X";

    case kmuonFirstNodeY:
    return "h_muon_StartNode_Y";

    case kmuonFirstNodeZ:
    return "h_muon_StartNode_Z";

    case kmuonLastNodeX:
    return "h_muon_LastNode_X";

    case kmuonLastNodeY:
    return "h_muon_LastNode_Y";

    case kmuonLastNodeZ:
    return "h_muon_LastNode_Z";

    case ktracksize:
    return "h_Tracksize";

    case kTRUTH_P_T:
    return "h_TRUTH_MuonP_T";

    case kTRUTH_E:
    return "h_TRUTH_Muon_E";

    case kTRUTH_P_Z:
    return "h_TRUTH_MuonP_Z";

    case kTRUTH_AngleWRTB:
    return "h_TRUTH_MuonangleWRTB";

    case kmuonVertexTiming:
    return "h_muon_VertexTiming";

    default:
    std::cout << "ERROR: unknown Playlist name for Muon !" << std::endl;
    return "";
  };
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string  GetMuonVarHist_DATAName(MuonVar playlist_name) {
  switch (playlist_name) {
    case kP_T:
    return "h_Data_MuonPT";

    case kE:
    return "h_Data_MuonE";

    case kP_Z:
    return "h_Data_MuonPZ";

    case kAngleWRTB:
    return "h_Data_MuonTheta";

    case kAngleWRTBhelium:
    return "h_Data_MuonTheta_helium";

    case kAnglePhi:
    return "h_Data_MuonPhi";

    case kDOCA_muon:
    return "h_Data_MuonDOCA";

    case kCharge:
    return "h_Data_MuonCharge";

    case kMuonMatchtoMinos:
    return "h_Data_MuonMatchtoMinos";

    case kcurvatureSig:
    return "h_Data_MuoncurvatureSig";

    case kminos_R:
    return "h_Data_minosR";

    case kminosStart_X:
    return "h_Data_minosStart_X";

    case kminosStart_Y:
    return "h_Data_minosStart_Y";

    case kminosStart_Z:
    return "h_Data_minosStart_Z";

    case kminosEnd_X:
    return "h_Data_minosEnd_X";

    case kminosEnd_Y:
    return "h_Data_minosEnd_Y";

    case kminosEnd_Z:
    return "h_Data_minosEnd_Z";

    case kmuonFirstNodeX:
    return "h_Data_muonFirstNodeX";

    case kmuonFirstNodeY:
    return "h_Data_muonFirstNodeY";

    case kmuonFirstNodeZ:
    return "h_Data_muonFirstNodeZ";

    case kmuonLastNodeX:
    return "h_Data_muonLastNodeX";

    case kmuonLastNodeY:
    return "h_Data_muonLastNodeY";

    case kmuonLastNodeZ:
    return "h_Data_muonLastNodeZ";

    case ktracksize:
    return "h_Data_Tracksize";

    default:
    std::cout << "ERROR: unknown Muon var Data Name!" << std::endl;
    return "";
  };
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string  GetMuonVarAXISName(MuonVar playlist_name) {
  switch (playlist_name) {
    case kP_T:
    return "P_{T} [GeV/c]";

    case kE:
    return "E_{#mu} [GeV]";

    case kP_Z:
    return "P_{#parallel} [GeV/c]";

    case kAngleWRTB:
    return "#theta_{#mu} (wrtb)[Deg]";

    case kAnglePhi:
    return "#Phi_{#mu} (wrtb)[Deg]";

    case kcurvatureSig:
    return "(q/p)/#sigma(q/p)";

    case kTRUTH_P_T:
    return "P_{T}(True) [GeV/c]";

    case kTRUTH_E:
    return "E_{#mu} (True) [GeV]";

    case kTRUTH_P_Z:
    return "P_{Z}(True) [GeV/c]";

    case kTRUTH_AngleWRTB:
    return "True #theta_{#mu} (wrtb) [Deg]";

    case kDOCA_muon:
    return "Muon DOCA [mm]";

    case kminosStart_X:
    return "Minos Start X [mm]";

    case kminosStart_Y:
    return "Minos Start Y [mm]";

    case kminosStart_Z:
    return "Minos Start Z [mm]";

    case kminosEnd_X:
    return " Minos End X [mm]";

    case kminosEnd_Y:
    return " Minos End Y [mm]";

    case kminosEnd_Z:
    return " Minos End Z [mm]";

    case kmuonFirstNodeX:
    return "Muon First node X [mm]";

    case kmuonFirstNodeY:
    return "Muon First node Y [mm]";

    case kmuonFirstNodeZ:
    return "Muon First node Z [mm]";

    case kmuonLastNodeX:
    return " Muon Last Node X [mm]";

    case kmuonLastNodeY:
    return " Muon Last Node Y [mm]";

    case kmuonLastNodeZ:
    return " Muon Last Node Z [mm]";

    case  ktracksize:
    return "NTrks [N]";

    default:
    std::cout << "Unknown MuonVarAXISName" << std::endl;
    return "";
  };
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string  GetsecondTrakHistName_DATA_Name(SecondTrkVar playlist_name) {
  switch (playlist_name) {

    case ksecE:
    return "h_Data_secTrk_Energy";

    case kThetamid :
    return "h_Data_secTrk_MidAngle";

    case kTheta:
    return "h_Data_secTrk_Angle";

    case kOpenAngle:
    return "h_Data_secTrk_Openangle";

    case kPathway:
    return "h_Data_secTrk_Pathlength";

    case ksec_tracklength_minerva:
    return "h_Data_secTrk_Length";

    case kDOCA:
    return "h_Data_secTrk_DOCA";

    case kFirstsecTrk_Xnode:
    return "h_Data_secTrk_FirstNodeX";

    case kFirstsecTrk_Ynode:
    return "h_Data_secTrk_FirstNodeY";

    case kFirstsecTrk_Znode:
    return "h_Data_secTrk_FirstNodeZ";

    case  kLastsecTrk_Xnode:
    return "h_Data_secTrk_LastNodeX";

    case  kLastsecTrk_Ynode:
    return "h_Data_secTrk_LastNodeY";

    case  kLastsecTrk_Znode:
    return "h_Data_secTrk_LastNodeZ";

    default: std::cout << "ERROR: unknown case for data name!" << std::endl;
    return "";

  };//end of switch
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string  GetVertexCryoVarHistName(CryoVertex playlist_name) {
  switch (playlist_name) {
    case kX:
    return "h_CryoVertex_X";

    case kY:
    return "h_CryoVertex_Y";

    case kZ:
    return "h_CryoVertex_Z";

    case kR:
    return "h_CryoVertex_R";

    case kRR:
    return "h_CryoVertex_R";

    case kTRUTH_X:
    return "h_TRUE_CryoVertex_X";

    case kTRUTH_Y:
    return "h_TRUE_CryoVertex_Y";

    case kTRUTH_Z:
    return "h_TRUE_CryoVertex_Z";

    case kTRUTH_R:
    return "h_TRUE_CryoVertex_R";

    case kfitConverge:
    return "h_CryoVertexChiSqFit";

    case kdistance_edge:
    return "h_Distance_to_InnerTank";

    case kdistance_edge_fiducial:
    return "h_Distance_to_InnerTank";

    case kdistance_upstreamcap:
    return "h_Distance_to_upstreamCap";

    case kdistance_downstreamcap:
    return "h_Distance_to_downstreamCap";

    default:
    std::cout << "Unknown Truth CryoVertex name" << std::endl;
    return "";
  };
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string  GetVertexCryoVarHist_DATA_Name(CryoVertex playlist_name) {
  switch (playlist_name) {
    case kX:
    return "h_Data_CryoVertex_X";

    case kY:
    return "h_Data_CryoVertex_Y";

    case kZ:
    return "h_Data_CryoVertex_Z";

    case kR:
    return "h_Data_CryoVertex_R";

    case kfitConverge:
    return "h_Data_CryoVertexChiSqFit";

    case kdistance_edge:
    return "h_Data_Distance_to_InnerTank";

    case kdistance_edge_fiducial:
    return "h_Data_Distance_to_InnerTank_Fidiucal";

    case kdistance_upstreamcap:
    return "h_Data_Distance_to_UpstreamCap";

    case kdistance_downstreamcap:
    return "h_Data_Distance_to_DownstreamCap";

    default:
    std::cout << "Unknown Cryo Data name" << std::endl;
    return "";
  };
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string  GetVetowallHist_DataName( VetoWall_vars vetowall_input) {
  switch (vetowall_input) {

    case kmatchToVeto:
    return "h_Data_VetoWall_matchToVeto";

    case knumbermatchToVeto:
    return "h_Data_VetoWall_NumbermatchToVeto";

    case kSixPush:
    return "h_Data_VetoWall_vetoSixPush";

    case kextrapnowalls:
    return "h_Data_VetoWall_extrapnowalls";

    case kextrapwall1:
    return "h_Data_VetoWall_extrapwall1";

    case  kextrapwall2:
    return "h_Data_VetoWall_extrapwall2";

    case kextrapbothwalls:
    return "h_Data_VetoWall_extrapbothwalls";

    case kMuonTrkMatchToVETOwalloff:
    return "h_Data_VetoWall_MuonTrkMatchToVETOwalloff";

    case kPMTMap_On:
    return "h_Data_VetoWall_PMTMAP_ON";

    case kPMTMap_Off:
    return "h_Data_VetoWall_PMTMAP_OFF";


    default: std::cout << "ERROR: unknown case for Vetwall name!" << std::endl;
    return "";

  };//end of switch

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string  GetVertexCryoVarAxisTitle(CryoVertex playlist_name) {
  switch (playlist_name) {
    case kX:
    return "Vertex X [mm]";

    case kY:
    return "Vertex Y [mm]";

    case kZ:
    return "Vertex Z [mm]";

    case kR:
    return "Vertex R [mm]";

    case kRR:
    return "Vertex R^{2} [mm^{2}]";

    case kTRUTH_X:
    return "Vertex(TRUE) X [mm]";

    case kTRUTH_Y:
    return "Vertex(TRUE) Y [mm]";

    case kTRUTH_Z:
    return "Vertex(TRUE) Z [mm]";

    case kTRUTH_R:
    return "Vertex(TRUE) R [mm]";

    case kfitConverge:
    return "ChiSqr fit";

    case kdistance_edge:
    return "Vertex Distance to Nearest Wall [mm]";

    case kdistance_edge_fiducial:
    return "Vertex Distance to Nearest Wall  [mm]";

    case kdistance_downstreamcap:
    return"Vertex Distance to Downstream Cap [mm]";

    case kdistance_upstreamcap:
    return"Vertex Distance to Upstream Cap [mm]";

    default:
    std::cout << "Unknown Vertex Naming: "<< playlist_name << std::endl;
    return "";
  };
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string  GetVertexCryoVarAxisTitleNoUnits(CryoVertex playlist_name) {
  switch (playlist_name) {
    case kX:
    return "Vertex X";

    case kY:
    return "Vertex Y";

    case kZ:
    return "Vertex Z";

    case kR:
    return "Vertex R";

    case kRR:
    return "Vertex R^{2}";

    case kTRUTH_X:
    return "Vertex(TRUE) X";

    case kTRUTH_Y:
    return "Vertex(TRUE) Y";

    case kTRUTH_Z:
    return "Vertex(TRUE) Z";

    case kTRUTH_R:
    return "Vertex(TRUE) R [mm]";

    case kfitConverge:
    return "ChiSqr fit";

    case kdistance_edge:
    return "Distance to Cryotank surface [mm]";

    case kdistance_edge_fiducial:
    return "Distance to Cryotank surface [mm]";

    default:
    std::cout << "Unknown Vertex Naming" << std::endl;
    return "";
  };
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string  GetsecondTrakHistName(SecondTrkVar playlist_name) {
  switch (playlist_name) {

    case ksecE:
    return "h_secTrk_Energy";

    case kThetamid :
    return "h_secTrk_MidTheta";

    case kTheta:
    return "h_secTrk_Theta";

    case kOpenAngle:
    return "h_secTrk_Openangle";

    case kPathway:
    return "h_secTrk_Pathlength";

    case ksec_tracklength_minerva:
    return "h_secTrk_tracklength";

    case kDOCA:
    return "h_secTrk_DOCA";

    case ksecDOCA_TRUTH:
    return "h_nonMuon_DOCA";

    case kFirstsecTrk_Xnode:
    return "h_secTrk_FirstNodeX";

    case kFirstsecTrk_Ynode:
    return "h_secTrk_FirstNodeY";

    case kFirstsecTrk_Znode:
    return "h_secTrk_FirstNodeZ";

    case  kLastsecTrk_Xnode:
    return "h_secTrk_LastNodeX";

    case  kLastsecTrk_Ynode:
    return "h_secTrk_LastNodeY";

    case  kLastsecTrk_Znode:
    return "h_secTrk_LastNodeZ";

    default: std::cout << "ERROR: unknown case for 2nd track name!" << std::endl;
    return "";

  };//end of switch
} // end of function
///
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string  GetVetowallHistName( VetoWall_vars vetowall_input) {
  switch (vetowall_input) {
    case kmatchToVeto:
    return "h_VetoWall_matchToVeto";

    case knumbermatchToVeto:
    return "h_VetoWall_NumbermatchToVeto";

    case kSixPush:
    return "h_VetoWall_vetoSixPush";

    case kextrapnowalls:
    return "h_VetoWall_extrapnowalls";

    case kextrapwall1:
    return "h_VetoWall_extrapwall1";

    case  kextrapwall2:
    return "h_VetoWall_extrapwall2";

    case kextrapbothwalls:
    return "h_VetoWall_extrapbothwalls";

    case kMuonTrkMatchToVETOwalloff:
    return "h_VetoWall_MuonTrkMatchToVETOwalloff";

    case kPMTMap_On:
    return "h_VetoWall_PMTmap_ON";

    case kPMTMap_Off:
    return "h_VetoWall_PMTmap_OFF";


    default: std::cout << "ERROR: unknown case for Vetwall name!" << std::endl;
    return "";

  };//end of switch
}//end of funtion
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string GetsecondTrk_XAxisTitle(SecondTrkVar playlist_name) {

  switch (playlist_name) {
    case ksecE:
    return "KE [GeV]";

    case kThetamid:
    return "NonMuon Angle wrtb [Degs]";

    case kTheta:
    return "NonMuon Angle wrtb [Degs]";

    case kOpenAngle:
    return "Open Angle wrtb [Degs]";

    case kPathway:
    return "2ndTrk_{PathLength} [g/cm^{2}]";

    case ksec_tracklength_minerva:
    return "2ndTrk_{Length} [cm]";

    case kDOCA:
    return "NonMuon DOCA [mm]";

    case kFirstsecTrk_Xnode:
    return  "2ndTrk First Node X [mm]";

    case kFirstsecTrk_Ynode:
    return  "2ndTrk First Node Y [mm]";

    case kFirstsecTrk_Znode:
    return  "2ndTrk First Node Z [mm]";

    case  kLastsecTrk_Xnode:
    return "2ndTrk last Node X [mm]";

    case  kLastsecTrk_Ynode:
    return "2ndTrk last Node Y [mm]";

    case  kLastsecTrk_Znode:
    return "2ndTrk last Node Z [mm]";

    default:
    std::cout << "ERROR: unknown case for 2nd track title name !" << std::endl;
    return "";

  };//end of switch
}//end of funtion
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string  GetVetowall_XAxisTitle( VetoWall_vars vetowall_input) {
  switch (vetowall_input) {

    case kmatchToVeto:
    return "bool";

    case knumbermatchToVeto:
    return "N";

    case kSixPush:
    return "bool";

    case kextrapnowalls:
    return "bool";

    case kextrapwall1:
    return "bool";

    case  kextrapwall2:
    return "bool";

    case kextrapbothwalls:
    return "bool";

    case kMuonTrkMatchToVETOwalloff:
    return "bool";

    case kPMTMap_On:
    return "Vetowall PMT Paddle N";

    case kPMTMap_Off:
    return "Vetowall PMT Paddle N";


    default: std::cout << "ERROR: unknown case for Vetwall name!" << std::endl;
    return "";

  };//end of switch

}//
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string  GetVertexCryoVarHIST_Title(CryoVertex Var ,ME_helium_Playlists playlist_name ){

  auto Var_name = GetVertexCryoTitleName(Var);
  auto playlist_name_STRING = GetPlaylist(playlist_name);
  auto helium_status = GetPlaylist_HeliumStatus(playlist_name);
  auto playlist_helium_status = GetFULLorEmpty(helium_status);

  std::string title_name = Var_name + " "+ playlist_name_STRING +"  ("+  playlist_helium_status + ")";

  return  title_name;

}//end of function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string  GetVertexCryoVarHIST_Title(CryoVertex Var ,ME_helium_Playlists playlist_nameFULL, ME_helium_Playlists playlist_nameEMPTY ){

  auto Var_name = GetVertexCryoTitleName(Var);
  auto Status = GetFULL_EMPTYSTRING(playlist_nameFULL , playlist_nameEMPTY);

  std::string title_name = Var_name + " "+ Status;

  return  title_name;

}//end of function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string  Get2ndTrkHIST_Title(SecondTrkVar Var ,ME_helium_Playlists playlist_name ){

  auto Var_name = GetsecondTrkTitleName(Var);
  auto playlist_name_STRING = GetPlaylist(playlist_name);
  auto helium_status = GetPlaylist_HeliumStatus(playlist_name);
  auto playlist_helium_status = GetFULLorEmpty(helium_status);

  std::string title_name = Var_name + " "+ playlist_name_STRING +"  ("+  playlist_helium_status + ")";

  return  title_name;

}//end of function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string  Get2ndTrkHIST_Title(SecondTrkVar Var ,ME_helium_Playlists playlist_nameFull,ME_helium_Playlists playlist_nameEMPTY ){
  auto Var_name = GetsecondTrkTitleName(Var);

  auto Status = GetFULL_EMPTYSTRING(playlist_nameFull,playlist_nameEMPTY);

  std::string title_name = Var_name + " "+ Status;

  return  title_name;

}//end of function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string  GetFULL_EMPTYSTRING(ME_helium_Playlists playlist_name_FULL,ME_helium_Playlists playlist_name_EMPTY ){

  auto FULL_intial = GetPlaylist_InitialName(playlist_name_FULL);
  auto EMPTY_intial = GetPlaylist_InitialName(playlist_name_EMPTY);

  std::string title_name =  "("+ FULL_intial +" - "+  EMPTY_intial + ")";

  return  title_name;

}//end of function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string  GetMuon_Figure_Title(MuonVar Var, ME_helium_Playlists playlist_name ){

  auto Var_name = GetMuonVarTitleName(Var);
  auto playlist_name_STRING = GetPlaylist(playlist_name);
  auto helium_status = GetPlaylist_HeliumStatus(playlist_name);
  auto playlist_helium_status = GetFULLorEmpty(helium_status);

  std::string title_name = Var_name + " "+ playlist_name_STRING +"  ("+  playlist_helium_status + ")";

  return  title_name;

}//end of function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string  GetMuon_Figure_Title(MuonVar Var, ME_helium_Playlists playlist_nameFULL,ME_helium_Playlists playlist_nameEmpty  ){

  auto Var_name = GetMuonVarTitleName(Var);
  auto Status = GetFULL_EMPTYSTRING(playlist_nameFULL,playlist_nameEmpty );
  std::string title_name = Var_name + " "+ Status;

  return  title_name;

}//end of function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::vector<double> GetBinMuonVector(MuonVar playlist_name) {
  std::vector<double> bins_vec;

  switch (playlist_name) {

    case kP_T:
    bins_vec = {0.0, 0.075, 0.15, 0.25, 0.325, 0.4, 0.475, 0.55, 0.7, 0.85, 1.0, 1.25, 1.5, 2.5};
    return bins_vec;

    case kP_T_2D:
    bins_vec = {0.0, 0.25, 0.4, 0.55, 0.7, 0.85, 2.5};
    return bins_vec;

    case kE:
    bins_vec = {2.0, 4.0, 5.0, 6.0, 8.0, 10.0, 12.0, 16.0, 20.0, 26.0, 32.0, 42.0, 50.0}; // removed first bin
    return bins_vec;

    case kE_2D:
    bins_vec = {2.0, 4.0, 5.0, 6.0, 8.0, 10.0, 20.0, 50.0}; // removed first bin
    return bins_vec;

    case kP_Z:
    bins_vec = {1.5, 3.0, 4.0, 5.0, 6.0, 8.0, 10.0, 15.0, 20.0}; // 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 6.0, 8.0, 10.0, 15.0, 20.0 old, going to combined bins
    return bins_vec;

    case kP_Z_2D:
    bins_vec = {1.5, 3.0, 4.0, 5.0, 6.0, 8.0, 10.0, 20.0}; // 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 6.0, 8.0, 10.0, 15.0, 20.0 old, going to combined bins
    return bins_vec;

    case kAngleWRTB:
    bins_vec = {0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 12.0}; // removed last bin 14
    return bins_vec;

    case kAngleWRTB_2D:
    bins_vec = {0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 12.0}; // removed last bin 14
    return bins_vec;

    case kDOCA_muon:
    bins_vec = {0.0, 4.0, 8.0, 12.0, 14.0, 16.0, 20.0, 24.0, 28.0, 32.0, 36.0, 40.0, 50.0, 60.0, 80.0};
    return bins_vec;

    case kDOCA_muon_2D:
    bins_vec = {0.0, 10.0, 15.0, 25.0, 40.0, 80.0};
    return bins_vec;

    case kcurvatureSig:
    bins_vec = {-60, -54, -48, -42, -36, -30, -24, -18, -12, -6, 0, 6, 12, 18, 24, 30, 36, 42, 48, 54, 60};
    return bins_vec;


    case kcurvatureSig_2D:
    bins_vec = {-60, -48, -36, -24, -18, -10, -5};
    return bins_vec;


    case kMuonMatchtoMinos:
    bins_vec = {0.5, 1.5, 2.5, 3.5};
    return bins_vec;

    case kMuonMatchtoVeto:
    bins_vec =  {-1.5,-0.5, 0.5, 1.5};
    return bins_vec;

    case kminos_R:
    bins_vec = {0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200,
      1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000, 2100, 2200, 2300,
      2400, 2500, 2600, 2700, 2800, 2900, 3000};
      return bins_vec;

    case kminosStart_X:
    bins_vec = MakeBinVector(20, 0, 1500);
    return bins_vec;

    case kminosStart_Y:
    bins_vec = MakeBinVector(20, 0, 1500);
    return bins_vec;

    case kminosStart_Z:
    bins_vec = MakeBinVector(300, 10500, 13500);
    return bins_vec;

    case kminosEnd_X:
    bins_vec = MakeBinVector(20, 0, 1500);
    return bins_vec;

    case kminosEnd_Y:
    bins_vec = MakeBinVector(20, 0, 1500);
    return bins_vec;

    case kminosEnd_Z:
    bins_vec = MakeBinVector(50, 10500, 30500);
    return bins_vec;

    case kmuonFirstNodeX:
    bins_vec = MakeBinVector(24, -1200.0, 1200.0);
    return bins_vec;

    case kmuonFirstNodeY:
    bins_vec = MakeBinVector(24, -1200.0, 1200.0);
    return bins_vec;

    case kmuonFirstNodeZ:
    bins_vec = MakeBinVector(30, 4200.0, 4500.0);
    return bins_vec;

    case kmuonLastNodeX:
    bins_vec = MakeBinVector(24, -1200.0, 1200.0);
    return bins_vec;

    case kmuonLastNodeY:
    bins_vec = MakeBinVector(24, -1200.0, 1200.0);
    return bins_vec;

    case kmuonLastNodeZ:
    bins_vec = MakeBinVector(50, 9000, 10500);
    return bins_vec;

    case kCharge:
    bins_vec = {-1.5,-0.5, 0.5, 1.5};
    return bins_vec;

    case kAnglePhi:
    bins_vec = MakeBinVector(12, -180.0, 180.0);
    return bins_vec;

    case ktracksize:
    bins_vec = MakeBinVector(8, -.5, 7.5);
    return bins_vec;

    case  kmuonVertexTiming:
    bins_vec = MakeBinVector(50,  0.0, 15000.0);
    return bins_vec;

    default:
    std::cout << "ERROR: unknown BIN with name!" << std::endl;
    bins_vec = {0.0};
    return bins_vec;
  };
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::vector<double> GetBinvertexVector(CryoVertex playlist_name) {
  std::vector<double> bins_vec;

  switch (playlist_name) {

    case kX:
    bins_vec = {-1200, -1150, -1100, -1050, -1000, -950, -900, -850, -800, -750, -700, -650, -600, -550, -500, -450, -400, -350, -300, -250, -200, -150, -100, -50, 0, 50, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 950, 1000, 1050, 1100, 1150, 1200};//{ -1200.0, -1104.0, -1008.0, -912.0, -816.0, -720.0, -624.0, -528.0, -432.0, -336.0, -240.0, -144.0, -48.0, 48.0, 144.0, 240.0, 336.0, 432.0, 528.0, 624.0, 720.0, 816.0, 912.0, 1008.0, 1104.0, 1200.0};
    return bins_vec;

    case kX_2D:
    bins_vec = {-1200, -1000, -800, -600, -400, -200, 0, 200, 400, 600, 800, 1000, 1200};//
    return bins_vec;

    case kY:
    bins_vec = {-1200, -1150, -1100, -1050, -1000, -950, -900, -850, -800, -750, -700, -650, -600, -550, -500, -450, -400, -350, -300, -250, -200, -150, -100, -50, 0, 50, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 950, 1000, 1050, 1100, 1150, 1200};//{-1200.0, -1104.0, -1008.0, -912.0, -816.0, -720.0, -624.0, -528.0, -432.0, -336.0, -240.0, -144.0, -48.0, 48.0, 144.0, 240.0, 336.0, 432.0, 528.0, 624.0, 720.0, 816.0, 912.0, 1008.0, 1104.0, 1200.0};
    return bins_vec;

    case kY_2D:
    bins_vec = {-1200, -1000, -800, -600, -400, -200, 0, 200, 400, 600, 800, 1000, 1200};//{-1200.0, -1104.0, -1008.0, -912.0, -816.0, -720.0, -624.0, -528.0, -432.0, -336.0, -240.0, -144.0, -48.0, 48.0, 144.0, 240.0, 336.0, 432.0, 528.0, 624.0, 720.0, 816.0, 912.0, 1008.0, 1104.0, 1200.0};
    return bins_vec;


    case kZ:
    bins_vec = {1450 ,1481.25, 1512.5 ,1543.75, 1575 ,1606.25, 1637.5 ,1668.75, 1700 ,1748.55, 1797.1 ,1845.65, 1894.2 ,1942.75, 1991.3 ,2039.85, 2088.4 ,2113.99, 2139.59 ,2165.19, 2190.78 ,2216.37, 2241.96 ,2267.56, 2293.15 ,2317.9, 2342.66 ,2367.41, 2392.16 ,2416.91, 2441.67 ,2466.42, 2491.17 ,2515.94, 2540.71 ,2565.48, 2590.25 ,2615.02, 2639.79 ,2664.56, 2689.33 ,2714.1, 2738.87 ,2763.64, 2788.41 ,2813.18, 2837.96 ,2862.73, 2887.5 ,2912.27, 2937.04 ,2961.82, 2986.59 ,3011.36, 3036.13 ,3060.9, 3085.67 ,3110.44, 3135.21 ,3159.99, 3184.76 ,3209.53, 3234.3 ,3259.07, 3283.84 ,3308.61, 3333.38 ,3358.15, 3382.92 ,3407.69, 3432.46 ,3457.23, 3482 ,3507.62, 3533.25 ,3558.88, 3584.5 ,3610.12, 3635.75 ,3661.38, 3687.0 ,3712.62, 3738.25 ,3763.88, 3789.5 ,3815.12, 3840.75 ,3866.38, 3892 ,3917.62, 3943.25 ,3968.88, 3994.5 ,4020.12, 4045.75 ,4071.38, 4097 ,4127.03, 4157.06 ,4187.09, 4217.12 ,4247.15, 4277.19 ,4307.22, 4337.25}; //{1450, 1512.5, 1575, 1637.5, 1700, 1797.1, 1894.2, 1991.3, 2088.4, 2139.59, 2190.78, 2241.96, 2293.15, 2342.66, 2392.16, 2441.67, 2491.17, 2540.71, 2590.25, 2639.79, 2689.33, 2738.87, 2788.41, 2837.96, 2887.5, 2937.04, 2986.59, 3036.13, 3085.67, 3135.21, 3184.76, 3234.3, 3283.84, 3333.38, 3382.92, 3432.46, 3482, 3533.25, 3584.5, 3635.75, 3687.0, 3738.25, 3789.5, 3840.75, 3892, 3943.25, 3994.5, 4045.75, 4097, 4157.06, 4217.12, 4277.19, 4337.25};     //{1450.0, 1512.5, 1575, 1637.5, 1700.0, 2088.4, 2293.15, 2491.17, 2689.33, 2887.5, 3085.67, 3283.84, 3482.0, 3687.0, 3892.0, 4097.0, 4337.25}; // removed first bin 1450.0, older last bin 4302.0  Events what be reconstructed farther upstream than 4337.25 [mm]  3687.0
    return bins_vec;

    case kZ_2D:
    bins_vec = {1450, 1750.00, 2050.00, 2250, 2450, 2650, 2850, 3000, 3200, 3400, 3650, 3900, 4200, 4350};
    return bins_vec;


    case kR:
    bins_vec = {0, 50, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 950, 1000, 1050, 1100, 1150, 1200}; //  { 0.0, 100.0, 200.0, 300.0, 400.0, 500.0, 600.0, 700.0, 750, 800.0, 850.0, 900.0, 1050.0, 1100.0, 1150.0, 1200.0}};
    return bins_vec;

    case kR_2D:
    bins_vec = {0, 200, 400, 600,  700,   800,   1000}; //  { 0.0, 100.0, 200.0, 300.0, 400.0, 500.0, 600.0, 700.0, 750, 800.0, 850.0, 900.0, 1050.0, 1100.0, 1150.0, 1200.0}};
    return bins_vec;



    case kRR:
    bins_vec = {0 ,10000 ,40000 ,90000 ,160000 ,250000 ,360000 ,490000 , 640000, 810000 ,1.21e+06 , 1.44e+06};//{0 ,10000 ,40000 ,90000 ,160000 ,250000 ,360000 ,490000 ,562500 ,640000 ,722500 ,810000 ,1.1025e+06 ,1.21e+06 ,1.3225e+06 ,1.44e+06
    return bins_vec;

    case kX_eff:
    bins_vec = MakeBinVector(30, -1200.0, 1200.0);// { -1200.0, -1104.0, -1008.0, -912.0, -816.0, -720.0, -624.0, -528.0, -432.0, -336.0, -240.0, -144.0, -48.0, 48.0, 144.0, 240.0, 336.0, 432.0, 528.0, 624.0, 720.0, 816.0, 912.0, 1008.0, 1104.0, 1200.0};
    return bins_vec;

    case kY_eff:
    bins_vec =  MakeBinVector(30, -1200.0, 1200.0); //{-1200.0, -1104.0, -1008.0, -912.0, -816.0, -720.0, -624.0, -528.0, -432.0, -336.0, -240.0, -144.0, -48.0, 48.0, 144.0, 240.0, 336.0, 432.0, 528.0, 624.0, 720.0, 816.0, 912.0, 1008.0, 1104.0, 1200.0};
    return bins_vec;

    case kZ_eff:
    bins_vec = MakeBinVector(80, 1400.0, 4600);//MakeBinVector_chiSqrt();
    return bins_vec;

    case kR_eff:
    bins_vec = MakeBinVector(50, 0.0, 1000.0);
    return bins_vec;

    case kRR_eff:
    bins_vec = MakeBinVector(40, 0.0, 810000.0); //{0, 2500.0, 10000, 22500.0, 55225.0, 122500.0, 202500.0, 250000.0, 360000.0, 490000.0, 562500.0};
    return bins_vec;

    case kX_resolution:
    bins_vec = MakeBinVector(40, -60, 60);// { -1200.0, -1104.0, -1008.0, -912.0, -816.0, -720.0, -624.0, -528.0, -432.0, -336.0, -240.0, -144.0, -48.0, 48.0, 144.0, 240.0, 336.0, 432.0, 528.0, 624.0, 720.0, 816.0, 912.0, 1008.0, 1104.0, 1200.0};
    return bins_vec;

    case kY_resolution:
    bins_vec =  MakeBinVector(40, -60, 60); //{-1200.0, -1104.0, -1008.0, -912.0, -816.0, -720.0, -624.0, -528.0, -432.0, -336.0, -240.0, -144.0, -48.0, 48.0, 144.0, 240.0, 336.0, 432.0, 528.0, 624.0, 720.0, 816.0, 912.0, 1008.0, 1104.0, 1200.0};
    return bins_vec;

    case kZ_resolution:
    bins_vec = MakeBinVector(30, -300, 300);//MakeBinVector_chiSqrt();
    return bins_vec;

    case kR_resolution:
    bins_vec = MakeBinVector(40, -60, 60);
    return bins_vec;

    case kRR_resolution:
    bins_vec = MakeBinVector(100, -1600, 1600); //{0, 2500.0, 10000, 22500.0, 55225.0, 122500.0, 202500.0, 250000.0, 360000.0, 490000.0, 562500.0};
    return bins_vec;

    case kX_Precent_resolution:
    bins_vec = MakeBinVector(30, -0.8, .8);// { -1200.0, -1104.0, -1008.0, -912.0, -816.0, -720.0, -624.0, -528.0, -432.0, -336.0, -240.0, -144.0, -48.0, 48.0, 144.0, 240.0, 336.0, 432.0, 528.0, 624.0, 720.0, 816.0, 912.0, 1008.0, 1104.0, 1200.0};
    return bins_vec;

    case kY_Precent_resolution:
    bins_vec =  MakeBinVector(30, -0.8, .8); //{-1200.0, -1104.0, -1008.0, -912.0, -816.0, -720.0, -624.0, -528.0, -432.0, -336.0, -240.0, -144.0, -48.0, 48.0, 144.0, 240.0, 336.0, 432.0, 528.0, 624.0, 720.0, 816.0, 912.0, 1008.0, 1104.0, 1200.0};
    return bins_vec;

    case kZ_Precent_resolution:
    bins_vec = MakeBinVector(25, -1.0, 1.0);//MakeBinVector_chiSqrt();
    return bins_vec;

    case kR_Precent_resolution:
    bins_vec = MakeBinVector(30, -0.8, .8);
    return bins_vec;

    case kRR_Precent_resolution:
    bins_vec = MakeBinVector(25, -1.0, 1.0); //{0, 2500.0, 10000, 22500.0, 55225.0, 122500.0, 202500.0, 250000.0, 360000.0, 490000.0, 562500.0};
    return bins_vec;

    case kfitConverge:
    bins_vec = MakeBinVector(50, 0, 50);//MakeBinVector_chiSqrt();
    return bins_vec;

    case kfitConverge_2D:
    bins_vec = {0,5,10,15,20,50};
    return bins_vec;

    case kdistance_edge:
    bins_vec = {-1200, -1150, -1100, -1050, -1000, -950, -900, -850, -800, -750, -700, -650, -600, -550, -500, -450, -400, -350, -300, -250, -200, -150, -100, -50, 0, 50, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900};//{-1000, -800, -600, -400, -350,-300,-250,-200,-150,-100, -50, 0, 50, 100,150, 200, 250, 300, 350,400,450, 500, 550, 600, 650, 700, 750,800
    return bins_vec;

    case kdistance_edge_2D:
    bins_vec = {-1000, -800,  -600, -400, -200,  0, 200, 400, 600};//{-1000, -800, -600, -400, -350,-300,-250,-200,-150,-100, -50, 0, 50, 100,150, 200, 250, 300, 350,400,450, 500, 550, 600, 650, 700, 750,800
    return bins_vec;


    case kdistance_edge_fiducial:
    bins_vec =  {0, 50, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800}; // {0, 20, 50, 80, 120, 160, 200,240,280,320,360,400,440,480,520,560,600,640,680,720,750,800};
    return bins_vec;

    case kdistance_downstreamcap:
    bins_vec =  {-1200, -1150, -1100, -1050, -1000, -950, -900, -850, -800, -750, -700, -650, -600, -550, -500, -450, -400, -350, -300, -250, -200, -150, -100, -50, 0, 50, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 950, 1000, 1050, 1100, 1150, 1200, 1250, 1300, 1350, 1400, 1450, 1500};
    return bins_vec;

    case kdistance_upstreamcap:
    bins_vec =  {-1200, -1150, -1100, -1050, -1000, -950, -900, -850, -800, -750, -700, -650, -600, -550, -500, -450, -400, -350, -300, -250, -200, -150, -100, -50, 0, 50, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 950, 1000, 1050, 1100, 1150, 1200, 1250, 1300, 1350, 1400, 1450, 1500};// -600, -400, -350,-300,-250,-200,-150,-100, -50, 0, 50, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850,900,950,1000,1050,1100,1150,1200
    return bins_vec;

    default:
    std::cout << "ERROR: unknown BIN with name!" << std::endl;
    bins_vec = {0.0};
    return bins_vec;
  };
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::vector<double> GetSecondTrkVarVector(SecondTrkVar playlist_name) {
  std::vector<double> bins_vec;
  switch (playlist_name) {

    case ksecE:
    bins_vec = {0.0, 0.075, 0.15, 0.25, 0.325, 0.4 ,0.475, 0.55, 0.7 ,0.85, 1.0, 1.25, 1.5, 2.5}; //GeV
    return bins_vec;

    case ksecE_2D:
    bins_vec = {0.0, 0.075, .15, 0.25, 0.5, 1.5}; //GeV
    return bins_vec;

    //0.0,0.05, 0.075, 0.1, 0.115, 0.125, 0.13, 0.135, 0.14, 0.145, 0.15, 0.155 0.15, 0.25, 0.325, 0.4 ,0.475, 0.55, 0.7 ,0.85, 1.0, 1.25, 1.5, 2.5
    case ksecE_Proton:
    bins_vec =  {0.005, 0.01, 0.015, 0.02, 0.025, 0.03, 0.035, 0.04, 0.045, 0.05, 0.055, 0.06, 0.065, 0.07, 0.075, 0.08, 0.085, 0.09, 0.095, 0.1,
      0.105, 0.11, 0.115, 0.12, 0.125, 0.13, 0.135, 0.14, 0.145, 0.15, 0.155, 0.16, 0.165, 0.17, 0.175, 0.18, 0.185, 0.19, 0.195, 0.2,
      0.205, 0.25, 0.325, 0.4 ,0.475, 0.55, 0.7 ,0.85, 1.0, 1.25, 1.5, 2.5}; //GeV
    return bins_vec;

    case kThetamid:
    bins_vec = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60}; //Deg
    return bins_vec;

    case ksecTheta_2D:
    bins_vec = {0,10,20,30,40,50,60}; //Deg
    return bins_vec;

    case kFullAngle:
    bins_vec = MakeBinVector(60, 0, 180.0);  //Deg
    return bins_vec;

    case kTheta:
    bins_vec = {0,4,8,12,16,20,24,28,32,36,40,44,48,52,56,60};
    return bins_vec;

    case kOpenAngle:
    bins_vec = {0,4,8,12,16,20,24,28,32,36,40,44,48,52,56,60,65,70,80};
    return bins_vec;

    case kPathway:
    bins_vec = {0,20,40,60,90,120,150,180,210,240,270,300,330,360,390,420,450};
    return bins_vec;

    case kDOCA:
    bins_vec = {0, 5, 10, 15, 20 , 30 , 40, 50, 60, 70, 80, 90, 100, 120};
    return bins_vec;

    case kDOCA_2D:
    bins_vec = {0, 5, 10, 15, 20, 40, 120};
    return bins_vec;


    case kFirstsecTrk_Xnode:
    bins_vec = MakeBinVector(24, -1200.0, 1200.0);
    return bins_vec;

    case kFirstsecTrk_Ynode:
    bins_vec = MakeBinVector(24, -1200.0, 1200.0);
    return bins_vec;

    case kFirstsecTrk_Znode:
    bins_vec = MakeBinVector(30, 4200.0, 4500.0);
    return bins_vec;

    case  kLastsecTrk_Xnode:
    bins_vec = MakeBinVector(24, -1200.0, 1200.0);
    return bins_vec;

    case  kLastsecTrk_Ynode:
    bins_vec = MakeBinVector(24, -1200.0, 1200.0);
    return bins_vec;

    case  kLastsecTrk_Znode:
    bins_vec = MakeBinVector(30, 4200.0, 4800.0);
    return bins_vec;

    case ksec_vertexTiming:
    bins_vec = MakeBinVector(50,  0.0, 15000.0);
    return bins_vec;

    case ksec_tracklength_minerva:
    bins_vec = Make_minervaTrkLenghtBins();
    return bins_vec;

    case ksec_tracklength_minerva_2D:
    bins_vec = {0, 25, 50, 75, 150, 250, 400 };
    return bins_vec;

    default:
    std::cout << "ERROR: unknown BIN with name!" << std::endl;
    bins_vec = {0.0};
    return bins_vec;

  };//end of switch

}//end of funtion
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::vector<double>  GetVetowall_BinVetor( VetoWall_vars vetowall_input) {
  std::vector<double> bins_vec;

  switch (vetowall_input) {

    case kmatchToVeto:
    bins_vec =  {-1.5,-0.5, 0.5, 1.5};
    return bins_vec;

    case knumbermatchToVeto:
    bins_vec =  {-0.5, 1.5, 2.5, 3.5, 4.5, 5.5};
    return bins_vec;

    case kSixPush:
    bins_vec =  {-1.5,-0.5, 0.5, 1.5};
    return bins_vec;

    case kextrapnowalls:
    bins_vec =  {-1.5,-0.5, 0.5, 1.5};
    return bins_vec;

    case kextrapwall1:
    bins_vec =  {-1.5,-0.5, 0.5, 1.5};
    return bins_vec;

    case  kextrapwall2:
    bins_vec =  {-1.5,-0.5, 0.5, 1.5};
    return bins_vec;

    case kextrapbothwalls:
    bins_vec =  {-1.5,-0.5, 0.5, 1.5};
    return bins_vec;

    case kMuonTrkMatchToVETOwalloff:
    bins_vec =  {-1.5,-0.5, 0.5, 1.5};
    return bins_vec;

    case kPMTMap:
    bins_vec =  {-1.5,-0.5, 0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.5, 11.5, 12.5, 13.5, 14.5, 15.5, 16.5, 17.5, 18.5, 19.5, 20.5, 21.5, 22.5, 23.5, 24.5, 25.5};
    return bins_vec;

    default: std::cout << "ERROR: unknown BIN with name!" << std::endl;
    bins_vec = {0.0};
    return bins_vec;

  };//end of switch

}//
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string  GetMuonUnitType(MuonVar playlist_name) {
  switch (playlist_name) {
    case kP_T:
    return "GeV/c";

    case kE:
    return "GeV";

    case kP_Z:
    return "GeV/c";

    case kAngleWRTB:
    return "Deg";

    case kDOCA_muon:
    return "mm";

    case kCharge:
    return "Charge";

    case kTRUTH_P_T:
    return "True GeV/c";

    case kTRUTH_DOCA:
    return "True mm";

    case kTRUTH_E:
    return "True GeV";

    case kTRUTH_P_Z:
    return "True /c";

    case kTRUTH_AngleWRTB:
    return "True deg";

    case kTRUTH_Charge:
    return "True charge";

    case kminosMuon_Energy:
    return "GeV";

    case kminosStart_X:
    return "mm";

    case kminosStart_Y:
    return "mm";

    case kminosStart_Z:
    return "mm";

    case kminosEnd_X:
    return "mm";

    case kminosEnd_Y:
    return "mm";

    case kminosEnd_Z:
    return "mm";

    case kmuonFirstNodeX:
    return "mm";

    case kmuonFirstNodeY:
    return "mm";

    case kmuonFirstNodeZ:
    return "mm";

    case kmuonLastNodeX:
    return "mm";

    case kmuonLastNodeY:
    return "mm";

    case kmuonLastNodeZ:
    return "mm";

    case kMuonMatchtoMinos:
    return "bool";

    case  ktracksize:
    return "NTrks";

    case kcurvatureSig:
    return "(q/p)/#sigma(q/p)";

    case kNONE:
    return " ";

    default:
    std::cout << "unknown Muon Varible units" << std::endl;
    return "";
  };
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string  GetVetowall_UnitType( VetoWall_vars vetowall_input) {
  switch (vetowall_input) {

    case kmatchToVeto:
    return "bool";

    case knumbermatchToVeto:
    return "N";

    case kSixPush:
    return "bool";

    case kextrapnowalls:
    return "bool";

    case kextrapwall1:
    return "bool";

    case  kextrapwall2:
    return "bool";

    case kextrapbothwalls:
    return "bool";

    case kMuonTrkMatchToVETOwalloff:
    return "bool";

    case kPMTMap_On:
    return "Vetowall PMT Paddle N";

    case kPMTMap_Off:
    return "Vetowall PMT Paddle N";

    default: std::cout << "ERROR: unknown case for Vetwall Unit type!" << std::endl;
    return "";

  };//end of switch

}//
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void FillMC_F_E_RecoCutMap(RECO_Cut_Map &FULL,RECO_Cut_Map &EMPTY,RECO_Cut_Map &F_E,
   std::vector<ECuts> kCutsVector,double POT[]){
     double scaleEmptyMCtoFullMC = (POT[0]/POT[1]);

     for (auto cut : kCutsVector){
       F_E[cut]= FULL[cut] - scaleEmptyMCtoFullMC*EMPTY[cut];
    }//end loop
}//endl;
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string GetWeight_name(Weights kweight)  {
  switch (kweight) {

    case kweightFlux:
    return "Flux Reweigher";

    case kweightMinos:
    return "Minos Efficiency";

    case kweight2p2ptune:
    return "2p2h Tune";

    case kweightRPA:
    return  "RPA";

    case kweightGenie:
    return "Genie Weight";

    case kweightLowQ2Pi:
    return "Low Q^2 suppression";

    default:
    return "ERROR: Unknown weight name " ;

  };//end of switch
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
FullAndEmptyPlaylistMap  MakeFullorEmptyList(std::vector <ME_helium_Playlists> InPutList  ){
  FullAndEmptyPlaylistMap MapOUTPut;

  std::vector <ME_helium_Status> Heliumstatus;

  Heliumstatus.push_back(kFULL);
  Heliumstatus.push_back(kEMPTY);

  std::vector <ME_helium_Playlists> Full_playlist;
  std::vector <ME_helium_Playlists> EMPTY_playlist;

  for(auto vector : InPutList){
    auto Label = GetPlaylist(vector);
    auto Status = GetPlaylist_HeliumStatus(vector);
    if(Status==Heliumstatus[0]){
      Full_playlist.push_back(vector);
      std::cout<< "Added Playlist ~~~~"<< Label.c_str() << " was Put in the Helium FULL Vector"<<std::endl;
    }
    else if(Status==Heliumstatus[1]){
      EMPTY_playlist.push_back(vector);
      std::cout<< "Added Playlist ~~~~"<< Label.c_str() << " was Put in the Helium EMPTY Vector"<<std::endl;
    }
    else{std::cout<<"ERROR: Not right format: trying to make Full or Empty List!!"<<std::endl;}
  }//end of Loop

  MapOUTPut[Heliumstatus[0]]=Full_playlist;
  MapOUTPut[Heliumstatus[1]]=EMPTY_playlist;
  return MapOUTPut;

}//END of FUnction
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::vector<ME_helium_Playlists>  MakeFullorEmptyVector(std::vector <ME_helium_Playlists> InPutList, ME_helium_Status FullorEmpty ){

  //vector <ME_helium_Status> Heliumstatus;
  std::vector <ME_helium_Playlists> OutputList;

  for(auto vector : InPutList){
    auto Label = GetPlaylist(vector);
    auto Status = GetPlaylist_HeliumStatus(vector);
    if(Status==FullorEmpty){
      OutputList.push_back(vector);
      std::cout<< "Added Playlist ~~~~"<< Label.c_str() << " was Put in the Helium FULL Vector"<<std::endl;
    }
  }
  return OutputList;
}//end of function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string String_ISMC(bool is_mc){

switch (is_mc) {
  case true:
  return "MC";

  case false:
  return "Data";

  default:
  std::cout << "ERROR: Must me true or false input" << std::endl;
  return "";
};

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string String_ISMC_EventSectionROOT(bool is_mc){

  switch (is_mc) {
    case true:
    return "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/";

    case false:
    return "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/";

    default:
    std::cout << "ERROR: Must me true or false input" << std::endl;
    return "";
  };

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string String_Reco_orTruth(bool isReco){

  switch (isReco) {
    case true:
    return "Reco";

    case false:
    return "Truth";

    default:
    std::cout << "ERROR: Must me true or false input" << std::endl;
    return "";
  };
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string String_Reco_orData(bool isReco){

  switch (isReco) {
    case true:
    return "Reco";

    case false:
    return "Data";

    default:
    std::cout << "ERROR: Must me true or false input" << std::endl;
    return "";
  };
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string String_EventSectionROOTPath(bool is_mc,ME_helium_Playlists playlist_name,bool StatsOnly ){

  std::string Final_path;
  std::string Path = String_ISMC_EventSectionROOT(is_mc);
  std::string Playlist_Intial = GetPlaylist_InitialName(playlist_name);

  if(StatsOnly==false){
    if(is_mc==true){
      Final_path = Path + "Histograms_minervame" + Playlist_Intial + "_MC_All_SysErrorsOn.root";
    }


    else if (is_mc==false){
      Final_path = Path + "Histograms_minervame" + Playlist_Intial + "_Data.root";
    }
  }



  else if(StatsOnly==true){
    if(is_mc==true){
      Final_path = Path + "Histograms_minervame" + Playlist_Intial + "_MC_StatsONLYErrors.root";
    }


    else if (is_mc==false){
      Final_path = Path + "Histograms_minervame" + Playlist_Intial + "_Data.root";
    }
  }

  return Final_path;

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string String_EventSectionROOTPath_FORTRUTH( ME_helium_Playlists playlist_name,bool StatsOnly ){
  std::string Final_path;
  std::string Path = String_ISMC_EventSectionROOT(true);
  std::string Playlist_Intial = GetPlaylist_InitialName(playlist_name);

  if(StatsOnly==true){
    Final_path = Path + "Histograms_minervame" + Playlist_Intial + "_TRUTH_StatsONLY.root";
  }


  else if (StatsOnly==false){
    Final_path = Path + "Histograms_minervame" + Playlist_Intial + "_TRUTH_All_SysErrorsOn.root";
  }
  return Final_path;

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string MakePlaylistString(std::vector<ME_helium_Playlists> input ){

  std::vector<std::string> Full_playlist_vector;
  std::vector<std::string> Empty_playlist_vector;

  for(auto cat : input){
    auto Playlist_status = GetPlaylist_HeliumStatus(cat);
    auto Playlist_name = GetPlaylist_InitialName(cat);
    if(kFULL==Playlist_status){Full_playlist_vector.push_back(Playlist_name);}
    else if(kEMPTY==Playlist_status){Empty_playlist_vector.push_back(Playlist_name);}
  }//end of forloop

  std::string Full_playlist =   "Full";
  std::string Empty_playlist = "Empty";
  for(auto cat: Full_playlist_vector){
    Full_playlist.append("_");
    Full_playlist.append(cat);
  }

  for(auto cat: Empty_playlist_vector){
    Empty_playlist.append("_");
    Empty_playlist.append(cat);
  }
  Full_playlist.append("_");
  Full_playlist.append(Empty_playlist);

  return Full_playlist;
}


//////////////////////////////////////////////////////////////////////////
//GET Vertex Varibles
//////////////////////////////////////////////////////////////////////////
std::vector<Material_type> GetMaterial_typeList() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<Material_type> Material;
  Material.push_back(kMaterial_Total);
  Material.push_back(kIron);
  Material.push_back(kHelium);
  Material.push_back(kCarbon);
  Material.push_back(kLead);
  Material.push_back(kAluminium);
  Material.push_back(kMaterial_OTHER);

  return Material;
//#endif
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::vector<Interaction_type> GetInteraction_typeList() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<Interaction_type> Interaction;
  Interaction.push_back(kInteraction_Total);
  Interaction.push_back(kElastic);
  Interaction.push_back(kRes_Coh_Pion);
  Interaction.push_back(kDIS);
  Interaction.push_back(k2p2h);
  Interaction.push_back(kInteraction_OTHER);

  return Interaction;
//#endif
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::vector<Particle_type> GetParticle_typeList() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<Particle_type> Particle;
  Particle.push_back(kParticle_Total);
  Particle.push_back(kElectron);
  Particle.push_back(kPion_0);
  Particle.push_back(kPion_pos);
  Particle.push_back(kPion_neg);
  Particle.push_back(kKaon);
  Particle.push_back(kProton);
  Particle.push_back(kNeutron);
  Particle.push_back(kMuon);
  Particle.push_back(kParticle_OTHER);

  return Particle;
//#endif
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
double getmassfromPDG(int pdg,int& count) {
   double mass = 0;
   if(pdg == 11)         {mass = .511;count=1;}//MeV electron
   else if (pdg == -11)  {mass = .511;count=2;} // e+
   else if (pdg == 111)  {mass = 134.97;count=3;} //Pion0
   else if (pdg == 211)  {mass = 139.57;count=4;} //Pion_plus
   else if (pdg == -211) {mass = 139.57;count=5;} //Pion_neg
   else if (pdg == 321)  {mass = 493.677;count=6;} //Kaon_plus
   else if (pdg == -321) {mass = 493.677;count=7;} //Kaon_neg
   else if (pdg == 311)  {mass = 497.614;count=8;} //Kaon_0)
   else if (pdg == -311) {mass = 497.614;count=9;} //anti-Kaon_0)
   else if (pdg == 130)  {mass = 497.614;count=10;} //Kaon^0_L) //
   else if (pdg == 2212) {mass = 938.28;count=11;} //Proton
   else if (pdg == -2212){mass = 938.28;count=12;} //antiProton
   else if (pdg == 2112 || pdg == -2112) {mass = 939.28;count=13;} //neutron + antineutron
   else if (pdg == 22)   {mass = 0.0;count=14;} //photon
   else if (pdg == -13)   {mass = 0.0;count=15;} //muon_plus
   else if (pdg == 13)  {mass = 0.0;count=16;} //muon_neg
   else if (pdg == 3122 || pdg == -3122 ) {mass = 0.0;count=17;} //Lamdba
   else if (pdg == 3222) {mass = 0.0;count=18;} //Sigma_plus
   else if (pdg == 3212||pdg == -3212) {mass = 0.0;count=19;} //Sigma_0 + antiSigma
   else if (pdg == 221)  {mass = 547.862;count=20;} //eta
   else if (pdg == 1000130270)   {mass = 26.9*931.494;count=21;} //27Al
   else if (pdg == 1000020040)   {mass = 3.72*931.494;count=22;} //4He
   else if (pdg == 1000020030)   {mass = 3.016*931.494;count=23;} //3He
   else if (pdg == 1000010020)   {mass = 2.014*931.494;count=24;} //2 deuterium
   else if (pdg == 1000010060)   {mass = 15.99491461*931.494;count=25;} //16Oxygen)
   else if (pdg == 1000030060)   {mass = 6.015*931.494;count=26;} //Li6
   else if (pdg == 12)           {mass = 0.0;count=27;} // electron neutrino
   else if (pdg == 14)           {mass = 0.0;count=28;} // muon neutrino
   else if (pdg == -14)          {mass = 0.0;count=29;} // muon  antineutrino
   else if (pdg == 1000030070)   {mass = 0.0;count=30;}  // Li7Nucleus
   else if (pdg == -9999)        {mass = 0.0;count=0;}  // particle has unknown trajectory thus no particle
   else {mass=0.0; count= 0; /*std::cout<< "not in particle type function " << pdg<<std::endl;*/}
   return mass;
 }

 std::string GetcommonNamefromPDG(int pdg) {
   std::string Particle_name;
   if(pdg == 11)         { Particle_name = "e^{-}"; }//MeV
   else if (pdg == -11)  { Particle_name = "e^{+}"; } // e+
   else if (pdg == 111)  { Particle_name = "#pi_{0}"; } //
   else if (pdg == 211)  { Particle_name = "#pi_{+}";} //
   else if (pdg == -211) { Particle_name = "#pi_{-}" ;} //
   else if (pdg == 321)  { Particle_name = "Kaon_{+}";} //K
   else if (pdg == -321) { Particle_name = "Kaon_{-}"; } //
   else if (pdg == 311)  { Particle_name = "Kaon_{0}"; } //
   else if (pdg == -311) { Particle_name = "antiKaon_{0}";} //)
   else if (pdg == 130)  { Particle_name = "Kaon^{0}_{L}";} //) //
   else if (pdg == 310)  { Particle_name = "Kaon^{0}_{S}";} //) //
   else if (pdg == 2212) { Particle_name = "Proton";} //
   else if (pdg == -2212){ Particle_name = "antiProton";} //
   else if (pdg == 2112||pdg == -2112) { Particle_name = "neutron";} //
   else if (pdg == 22)   { Particle_name = "photon";} //
   else if (pdg == 13)   { Particle_name = "#mu_{-}";} //
   else if (pdg == -13)  { Particle_name = "#mu_{+}";} //
   else if (pdg == 3122||pdg == -3122) { Particle_name = "Lamdba";} //
   else if (pdg == 3222) { Particle_name = "Sigma_{+}"; } //
   else if (pdg == 3212||pdg == 3212) { Particle_name = "Sigma_{0}";} //
   else if (pdg == 221)  { Particle_name = "Eta";} //
   else if (pdg == 1000130270)   { Particle_name = "{}^{27}Al";} //
   else if (pdg == 1000020040)   { Particle_name = "{}^{4}He";} //
   else if (pdg == 1000020030)   { Particle_name = "{}^{3}He";} //
   else if (pdg == 1000010020)   { Particle_name = "deuterium";} //2
   else if (pdg == 1000010060)   { Particle_name = "{}^{16}O";} //)
   else if (pdg == 1000030060)   { Particle_name = "Li6";} //
   else if (pdg == 1000010030)   { Particle_name = "triton";} //
   else if (pdg == 12)           { Particle_name = "#nu_{e}";} //
   else if (pdg == 14)           { Particle_name = "#nu_{#mu}";} //
   else if (pdg == -14)          { Particle_name = "muon  antineutrino";} //
   else if (pdg == 1000030070)   { Particle_name = "Li7Nucleus";}  //
   else if (pdg == -9999)        { Particle_name = "None";}  // particle has unknown trajectory thus no particle
   else {  Particle_name = "FAILURE not a particle in list";}

   return Particle_name;

 }
 ////////////////////////////////////////////////////////////////////////////////
 //
 ////////////////////////////////////////////////////////////////////////////////
std::string GetcommonNamefromPDG(int pdg, bool latex_true) {
  std::string Particle_name;
  if(pdg == 11)         { Particle_name = "e^{-}"; }//MeV
  else if (pdg == -11)  { Particle_name = "e^{+}"; } // e+
  else if (pdg == 111)
  {
    if(latex_true==true)
    {
      Particle_name = "$\\pi_{0}$";}
      else{
        Particle_name = "#pi_{0}";}
      } //
  else if (pdg == 211)
  {
    if(latex_true==true){Particle_name = "$\\pi_{+}$";}
    else{Particle_name = "#pi_{+}";}
  } //
  else if (pdg == -211) {
    if(latex_true==true){Particle_name = "$\\pi_{-}$" ;}
    else{Particle_name = "#pi_{-}" ;}
  } //
  else if (pdg == 321)  { Particle_name = "K_{+}";} //K
  else if (pdg == -321) { Particle_name = "K_{-}"; } //
  else if (pdg == 311)  { Particle_name = "K_{0}"; } //
  else if (pdg == -311) { Particle_name = "antiKaon_{0}";} //)
  else if (pdg == 411) { Particle_name = "D_{+}";} //)
  else if (pdg == 421) { Particle_name = "D_{0}";} //)
  else if (pdg == 431) { Particle_name = "D^{+}_{s}";} //)
  else if (pdg == 130)  { Particle_name = "Kaon_0_L";} //) //
  else if (pdg == 2212) { Particle_name = "Proton";} //
  else if (pdg == -2212){ Particle_name = "antiProton";} //
  else if (pdg == 2112|| pdg == -2112) { Particle_name = "neutron";} //

  else if (pdg == 22)   { Particle_name = "photon";} //
  else if (pdg == 13)   {
    if(latex_true==true){Particle_name = "$\\mu_{-}$";}
    else{Particle_name = "#mu_{-}";}
  } //
  else if (pdg == -13){
        if(latex_true==true){Particle_name = "$\\mu_{+}$";}
        else{Particle_name = "#mu_{+}";}
      } //
  else if (pdg == 3122||pdg == -3122) {
        if(latex_true==true){Particle_name = "$\\Lambda$";}
        else{Particle_name = "#Lambda";}
      }
  else if (pdg == 4122) {
        if(latex_true==true){Particle_name = "$\\Lambda^{+}_{c}$";}
        else{Particle_name = "#Lambda^{+}_{c}";}
      }
  else if (pdg == 3222) {
        if(latex_true==true){Particle_name = "$\\Sigma_{+}$";}
        else{Particle_name = "#Sigma_{+}";}
      }
  else if (pdg == 4222) {
     if(latex_true==true){Particle_name = "$\\Sigma_{++}_{c}$";}
     else{Particle_name = "#Sigma_{++}_{c}";}
   }
   else if (pdg == 4212) {
     if(latex_true==true){Particle_name = "$\\Sigma_{+}_{c}$";}
     else{Particle_name = "#Sigma_{+}_{c}";}
   }
   else if (pdg == 3212||pdg == -3212) {
     if(latex_true==true){Particle_name = "$\\Sigma_{0}$";}
     else{Particle_name = "#Sigma_{0}";}} //
   else if (pdg == 221)  { Particle_name = "Eta";} //
   else if (pdg == 1000130270)   { Particle_name = "{}^{27}Al";} //
   else if (pdg == 1000020040)   { Particle_name = "{}^{4}He";} //
   else if (pdg == 1000020030)   { Particle_name = "{}^{3}He";} //
   else if (pdg == 1000010020)   { Particle_name = "deuterium";} //2
   else if (pdg == 1000010060)   { Particle_name = "{}^{16}O";} //)
   else if (pdg == 1000030060)   { Particle_name = "Li6";} //
   else if (pdg == 1000010030)   { Particle_name = "triton";} //
   else if (pdg == 2000000001)   { Particle_name = "HadrSyst";} //
   else if (pdg == 2000000002)   { Particle_name = "HadrBlob";} //
   else if (pdg == 12)           {
     if(latex_true==true){Particle_name = "$\\nu_{e}$";}
     else{Particle_name = "#nu_{e}";}
     } //
   else if (pdg == 14)           {
     if(latex_true==true){Particle_name = "$\\nu_{\\mu}$";}
     else{Particle_name = "#nu_{#mu}";}
      } //
   else if (pdg == -14)          { Particle_name = "muon  antineutrino";} //
   else if (pdg == 1000030070)   { Particle_name = "Li7Nucleus";}  //
   else if (pdg == 2000000101)   { Particle_name = "BindingEnergy";}  //
   else if (pdg == -9999)        { Particle_name = "None";}  // particle has unknown trajectory thus no particle
   else {  Particle_name = "FAILURE not a particle in list";}

   return Particle_name;

 }
 ////////////////////////////////////////////////////////////////////////////////
 //
 ////////////////////////////////////////////////////////////////////////////////
int calculate_Target(int targetZ) {

   int whichhist = 9999;

   if (targetZ == 2) whichhist = 0;//Helium
   else if (targetZ == 6) whichhist = 1;//Carbon
   else if (targetZ == 26) whichhist = 2;//Iron
   else if (targetZ == 82) whichhist = 3;//Lead
   else if (targetZ == 13) whichhist = 4;//Aluminium
   else whichhist = 5; //other

   return whichhist;

 }//end of calculate_Target
 ////////////////////////////////////////////////////////////////////////////////
 //
 ////////////////////////////////////////////////////////////////////////////////
 Material_type calculate_Target_materialtype(int targetZ) {
   if (targetZ == 2) return kHelium;//Helium
   else if (targetZ == 6) return kCarbon;//Carbon
   else if (targetZ == 26) return kIron;//Iron
   else if (targetZ == 82) return kLead;//Lead
   else if (targetZ == 13) return kAluminium;//Aluminium
   else return kMaterial_OTHER; //other

 }//end of calculate_Target
 ////////////////////////////////////////////////////////////////////////////////
 //
 ////////////////////////////////////////////////////////////////////////////////
int calculate_Interaction(int interaction) {

  int whichhist = 9999;

  if (interaction == 0) whichhist = 0; // none
  else if (interaction == 1) whichhist = 1; // elastic
  else if (interaction == 2 || interaction == 4) whichhist = 2; // res + coh
  else if (interaction == 3) whichhist = 3; // DIS, but not really DIS, GENIE's DIS which is actually everything non-elastic and non-resonant
  else if (interaction == 8) whichhist = 4; // 2p2h
  else { whichhist = 5;} // all other types, 5-8 // had to put negivite condition because sometimes get n

  return whichhist;

}//end of calculate_Interaction
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string Interaction_name(int interaction)
{
  if(interaction ==0 ) { return "NoInteraction";}
  else if(interaction ==1 ) { return "QEL";}
  else if(interaction == 2) { return "RES";}
  else if(interaction == 3) { return "DIS";}
  else if(interaction == 4) { return "COHPI";}
  else if(interaction == 5) { return "AMNUGAMMA";}
  else if(interaction == 6) { return "IMD";}
  else if(interaction == 7) { return "NUEEL";}
  else if(interaction == 8) { return "MEC ";}
  else if(interaction == 10) { return "UnknownInt";}
  else {return "FAILED";}
}//end of function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
inline double round( double val )
{
    if( val < 0 ) return ceil(val - 0.5);
    return floor(val + 0.5);
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
double roundtoTenth( double number )
{
  double roundedNum;
     roundedNum = floor(number * 10.0 + .5) / 10.0;
     return roundedNum;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
double roundToHundreths( double number )
{
  double roundedNum;
     roundedNum = floor(number * 100.0 + .5) / 100.0;
     return roundedNum;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string  GetParticle_group_Name(Particle_type Particle) {
  switch (Particle) {
    case kElectron:
    return "e^{#pm}";

    case kPion_neg:
    return "#pi^{-}";

    case  kPion_pos:
    return "#pi^{+}";

    case kPion_0:
    return "#pi^{0}";

    case kKaon:
    return "#Kappa^{#pm},#Kappa^{0}_{(L)},#bar{#Kappa^{0}}";

    case kProton:
    return "p,#bar{p}";

    case kNeutron:
    return "n,#bar{n}";

    case kGamma:
    return "#gamma";

    case kMuon:
    return "#mu^{#pm}";

    case kParticle_OTHER:
    return "Other";

    case kParticle_N_A:
    return "N/A";

    case kNeutrino_muon:
    return "#nu_{#mu}";

    case kNeutrino_electron:
    return "#nu_{e}";

    case kAnti_Neutrino:
    return "#bar{#nu_{l}}";

    case kFourHelium:
    return "{}^{4}He";

    case kLamdba:
    return "#Lambda,#bar{#Lambda}";

    case kSigma_plus:
    return "#Sigma^{+}";


    default:
    std::cout << "ERROR: unknown Particle name!" << std::endl;
    return "";
  };
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::vector<double> DetermineBinning(TH2D* input_hist, double limit)
{
  std::vector<double> output_bins;
  int start_bin=1;
  int stop_bin=start_bin+1;
  if (input_hist->GetNbinsX()!= input_hist->GetNbinsY()){ std::cout<<"You can't use a non-square matrix to do this dummy"<<std::endl;}
  output_bins.push_back(input_hist->GetXaxis()->GetBinLowEdge(start_bin));
  std::cout<<input_hist->GetTitle()<<std::endl;
  while (stop_bin<input_hist->GetNbinsX()+1) {
    double true_sum=0.;
    double diag_bin=0.;
    //        cout<<"Start at the Start  "<<start_bin<<" Stop bin at the Start "<<stop_bin<<endl;
    for (int reco_bin=start_bin; reco_bin<stop_bin; reco_bin++) {
      for (int true_bin=1; true_bin<input_hist->GetNbinsX()+1; true_bin++) {
        true_sum+=input_hist->GetBinContent(reco_bin,true_bin);
        //                cout<<"Reco bin "<<reco_bin<<" True bin "<<true_bin<<" sum "<<true_sum<<endl;
      }
    }
    for (int reco_bin=start_bin; reco_bin<stop_bin; reco_bin++) {
      for (int true_bin=start_bin; true_bin<stop_bin; true_bin++) {
        diag_bin+=input_hist->GetBinContent(reco_bin,true_bin);
        //                cout<<"Diagonal Bin "<<diag_bin<<" Sum Bin "<<true_sum<<endl;
      }
    }
    if (diag_bin/true_sum <=limit || diag_bin==0) {
      std::cout<<"NOT THERE YET!!! "<<diag_bin<<"  "<<true_sum<<"  "<<diag_bin/true_sum<<std::endl;
      stop_bin++;
    }
    else{
      std::cout<<"Congrats! You found a good bin!!! "<<diag_bin/true_sum<<"  "<<input_hist->GetXaxis()->GetBinLowEdge(start_bin)<<"  "<<input_hist->GetXaxis()->GetBinLowEdge(stop_bin)<<std::endl;
      output_bins.push_back(input_hist->GetXaxis()->GetBinLowEdge(stop_bin));
      start_bin=stop_bin;//start the process over again starting at the next bin
      stop_bin=start_bin+1;
    }
    //        cout<<"Start Bin "<<input_hist->GetXaxis()->GetLowEdge(start_bin)<<"  Stop Bin "<<input_hist->GetXaxis()->GetLowEdge(stop_bin)<<endl;
    //        cout<<"Start Bin "<<start_bin<<"  Stop Bin "<<stop_bin<<endl;
    //        bin++;
  }
  //    output_bins.push_back(input_hist->GetXaxis()->GetBinLowEdge(stop_bin+1));
  output_bins.push_back(input_hist->GetXaxis()->GetBinLowEdge(input_hist->GetNbinsX()+1));
  return output_bins;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::vector <double> Return_scaled_vector(std::vector <double> input_vector, double scale){

  std::vector <double> return_vector;
  for(auto input_vector_index: input_vector){
    double return_double =  input_vector_index*scale;
    return_vector.push_back(return_double);
  }

  return return_vector;
}


std::string arachne(SliceID &id, const bool isData, const bool useRodriges){
    return std::string("http://minerva05.fnal.gov") + (useRodriges?"/rodriges":"") + std::string("/Arachne/arachne.html?det=") + (isData?"MV":"SIM_minerva") +
                       "&recoVer=v21r1p1&run=" + std::to_string(id.run) +
                       "&subrun=" + std::to_string(id.subrun) +
                       "&gate=" + std::to_string(id.gate + !isData) +
                       "&slice=" + std::to_string(id.slice);
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string GetsecondTrkUnitType(SecondTrkVar playlist_name) {

  switch (playlist_name) {
    case ksecE:
    return "GeV";

    case kThetamid:
    return "Degs";

    case kTheta:
    return "Degs";

    case kOpenAngle:
    return "Degs";

    case kPathway:
    return "g/cm^{2}";

    case ksec_tracklength_minerva:
    return "cm";

    case kDOCA:
    return "mm";

    case kFirstsecTrk_Xnode:
    return  "mm";

    case kFirstsecTrk_Ynode:
    return  "mm";

    case kFirstsecTrk_Znode:
    return  "mm";

    case  kLastsecTrk_Xnode:
    return "mm";

    case  kLastsecTrk_Ynode:
    return "mm";

    case  kLastsecTrk_Znode:
    return "mm";

    default:
    std::cout << "ERROR: unknown case for 2nd track title name !" << std::endl;
    return "";
  };//end of switch


}//end of funtion
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::vector<bool> Print_Systematics(int input){
  std::vector<bool> print_vector;

  if(input==0)
  {
    print_vector.push_back(true);
    print_vector.push_back(true);
  }
  else if(input==1)
  {
    print_vector.push_back(true);
    print_vector.push_back(false);
  }
  else if(input==2)
  {
    print_vector.push_back(false);
    print_vector.push_back(false);
  }

  return print_vector;

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string PrintLabel_Systematics(int input){
  std::string printLabel;

  if(input==0)
  {
    printLabel="ALL_sysErrors";
  }
  else if(input==1)
  {
    printLabel="Group_SysErrors";
  }
  else if(input==2)
  {
    printLabel="CVONLY";
  }
  else{printLabel="";}

  return printLabel;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void rowNormalize(TH2& hist)
{
  const auto nXBins = hist.GetXaxis()->GetNbins(),
  nYBins = hist.GetYaxis()->GetNbins();
  for(int row = 0; row <= nYBins; ++row)
  {
    const double denom = hist.Integral(0, nXBins+1, row, row);
    for(int col = 0; col <= nXBins; ++col)
    {
      double input =   hist.GetBinContent(col, row)/denom;
      bool isnan_bool = std::isnan(input);
      if(isnan_bool==false || input <  .01)  hist.SetBinContent(col, row,input);
      else hist.SetBinContent(col, row, 0);

    }
  }
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void rowNormalize(MnvH2D& hist)
{
  const auto nXBins = hist.GetXaxis()->GetNbins(),
  nYBins = hist.GetYaxis()->GetNbins();
  for(int row = 0; row <= nYBins; ++row)
  {
    const double denom = hist.Integral(0, nXBins+1, row, row);
    for(int col = 0; col <= nXBins; ++col)
    {
      hist.SetBinContent(col, row, hist.GetBinContent(col, row)/denom);
    }
  }
}

void rowNormalize_Mig(TH2& hist, bool includeFlows)
{
  int first_bin = includeFlows ? 0 : 1;
  int last_bin = includeFlows ? hist.GetNbinsX()+1 : hist.GetNbinsX();
  //  Int_t nbins = includeFlows ? hist.GetNbinsX()+2 : hist.GetNbinsX();
  //const auto nXBins = nbins;
  //const auto nYBins = nbins;

  for(int y = first_bin; y <= last_bin; ++y)
  { Double_t norm = 0.;
    for (int x = first_bin; x <= last_bin; ++x) norm += hist.GetBinContent(x,y);

    for(int x = first_bin; x <= last_bin; ++x)
    {
      if (fabs(norm) > 1E-8) {
        double percentage =  100 * hist.GetBinContent(x,y) / norm;
        hist.SetBinContent(x, y, percentage);
      }
    }
  }
} // end of function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void rowNormalize_Mig(MnvH2D& hist, bool includeFlows)
{
  int first_bin = includeFlows ? 0 : 1;
  int last_bin = includeFlows ? hist.GetNbinsX()+1 : hist.GetNbinsX();
  for(int y = first_bin; y <= last_bin; ++y)
  { Double_t norm = 0.;
    for (int x = first_bin; x <= last_bin; ++x) norm += hist.GetBinContent(x,y);

    for(int x = first_bin; x <= last_bin; ++x)
    {
      if (fabs(norm) > 1E-8) {
        double percentage =  100 * hist.GetBinContent(x,y) / norm;
        hist.SetBinContent(x, y, percentage);
      }
    }
  }

}// new of function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void colNormalize(TH2& hist)
{
  const auto nXBins = hist.GetXaxis()->GetNbins(),
  nYBins = hist.GetYaxis()->GetNbins();
  for(int col = 0; col <= nXBins; ++col)
  {
    const double denom = hist.Integral(col, col, 0, nYBins+1);
    for(int row = 0; row <= nYBins; ++row)
    {
      double input =   hist.GetBinContent(col, row)/denom;
      bool isnan_bool = std::isnan(input);
      if(isnan_bool==false || input <  .01)  hist.SetBinContent(col, row,input);
      else hist.SetBinContent(col, row, 0);
    }
  }
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void colNormalize_Mig(TH2& hist, bool includeFlows)
{
  int first_bin = includeFlows ? 0 : 1;
  int last_bin = includeFlows ? hist.GetNbinsX()+1 : hist.GetNbinsX();
  //Int_t nbins = includeFlows ? hist.GetNbinsX()+2 : hist.GetNbinsX();
  //const auto nXBins = nbins;
  //const auto nYBins = nbins;
  for(int col = first_bin; col <= last_bin; ++col)
  {
    const double denom = hist.Integral(col, col, 0, last_bin);
    for(int row = first_bin; row <= last_bin; ++row)
    {
      hist.SetBinContent(col, row, hist.GetBinContent(col, row)/denom);
    }
  }
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void colNormalize(MnvH2D& hist)
{
  const auto nXBins = hist.GetXaxis()->GetNbins(),
  nYBins = hist.GetYaxis()->GetNbins();
  for(int col = 0; col <= nXBins; ++col)
  {
    const double denom = hist.Integral(col, col, 0, nYBins+1);
    for(int row = 0; row <= nYBins; ++row)
    {
      hist.SetBinContent(col, row, hist.GetBinContent(col, row)/denom);
    }
  }
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
Migration Migration_muonType(MuonVar playlist_name){
  switch (playlist_name) {
    case kP_T:
    return Mig_PT;

    case kE:
    return Mig_E;

    case kP_Z:
    return Mig_PZ;

    case kAngleWRTB:
    return Mig_theta;

    default:
    std::cout << "ERROR: unknown Playlist name for Cryotank vertex!" << std::endl;
    return Mig_E;
  };
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string MigrationHistName_frommuonType(MuonVar playlist_name){
  switch (playlist_name) {
    case kP_T:
    return "h_Mig_MuonPT";

    case kE:
    return "h_Mig_MuonE";

    case kP_Z:
    return "h_Mig_MuonPZ";

    case kAngleWRTB:
    return "h_Mig_MuonTheta";

    default:
    std::cout << "ERROR: unknown Playlist name for Cryotank vertex!" << std::endl;
    return "h_Mig_MuonE";
  };
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string  GetMigrationHistName(Migration playlist_name) {

  switch (playlist_name) {
    case Mig_E:
    return "h_Mig_MuonE";

    case Mig_PT:
    return "h_Mig_MuonPT";

    case Mig_PZ:
    return "h_Mig_MuonPZ";

    case Mig_theta:
    return "h_Mig_MuonTheta";

    default:
    std::cout << "ERROR: unknown Playlist name for Cryotank vertex!" << std::endl;
    return "";
  };
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string  GetMigrationTiteName(Migration playlist_name) {
  switch (playlist_name) {

    case Mig_E:
    return "Migration Muon E";

    case Mig_PT:
    return "Migration Muon P_{T}";

    case Mig_PZ:
    return "Migration Muon P_{#parallel}";

    case Mig_theta:
    return "Migration Muon Theta";

    default:
    std::cout << "ERROR: unknown Playlist name for Migration unit name!" << std::endl;
    return "";
  };
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string  GetMigrationXaxisName(Migration playlist_name) {
  switch (playlist_name) {

    case Mig_E:
    return "Reco Muon E";

    case Mig_PT:
    return "Reco Muon P_{T}";

    case Mig_PZ:
    return "Reco Muon P_{#parallel}";

    case Mig_theta:
    return "Reco Muon Theta";

    default:
    std::cout << "ERROR: unknown Playlist name for Migration unit name!" << std::endl;
    return "";
  };
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string  GetMigrationYaxisName(Migration playlist_name) {
  switch (playlist_name) {
    case Mig_E:
    return "TRUE Muon E";

    case Mig_PT:
    return "TRUE Muon P_{T}";

    case Mig_PZ:
    return "TRUE Muon P_{#parallel}";

    case Mig_theta:
    return "TRUE Muon Theta";

    default:
    std::cout << "ERROR: unknown Playlist name for Migration unit name!" << std::endl;
    return "";
  };
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::string  GetMigrationUnitType(Migration playlist_name) {
  switch (playlist_name) {
    case Mig_E:
    return "GeV";

    case Mig_PT:
    return "GeV/c";

    case Mig_PZ:
    return "GeV/c";

    case Mig_theta:
    return "Degs";

    default:
    std::cout << "ERROR: unknown Playlist name for Migration unit name!" << std::endl;
    return "";
  };
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
CrossSection_histNames Constuct_crosssection_Histname(MuonVar muon_input_type){

  CrossSection_histNames crosssection_hist_Names;

  crosssection_hist_Names.MuonType = muon_input_type;

  crosssection_hist_Names.Reco_hist_name = GetMuonVarHistName(muon_input_type);
  crosssection_hist_Names.Reco_hist_BG_name = GetMuonVarHistName(muon_input_type) + "_BG";
  crosssection_hist_Names.Data_hist_name = GetMuonVarHist_DATAName(muon_input_type);
  crosssection_hist_Names.hist_Eff_denominator_name = GetMuonVarHistName(muon_input_type) + "_TRUE";
  crosssection_hist_Names.hist_Eff_numerator_name = GetMuonVarHistName(muon_input_type) + "_TRUE_RECO";
  crosssection_hist_Names.Migration_name = MigrationHistName_frommuonType(muon_input_type);
  crosssection_hist_Names.hist_Flux_name =  GetMuonVarHistName(muon_input_type) + "_FluxIntegrated";
  return crosssection_hist_Names;

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
CrossSection_histNames MakeDaisy_names(CrossSection_histNames crosssection_hist_Names,  std::string DaisyNum){

//std::cout<<"inside::MakeDaisy_names "<< std::endl;

CrossSection_histNames DaisyName_CrossSection;

std::string DaisyName = "_Daisy_" + DaisyNum;
//std::cout<<"adding DaisyName  = " << DaisyName<<std::endl;
DaisyName_CrossSection.MuonType = crosssection_hist_Names.MuonType;

DaisyName_CrossSection.Reco_hist_name = crosssection_hist_Names.Reco_hist_name + DaisyName;
//std::cout<<"DaisyName_CrossSection.Reco_hist_name  = " << DaisyName_CrossSection.Reco_hist_name<<std::endl;
DaisyName_CrossSection.Reco_hist_BG_name = crosssection_hist_Names.Reco_hist_BG_name + DaisyName;
//std::cout<<"DaisyName_CrossSection.Reco_hist_BG_name  = " << DaisyName_CrossSection.Reco_hist_BG_name<<std::endl;
DaisyName_CrossSection.Data_hist_name =crosssection_hist_Names.Data_hist_name + DaisyName;
//std::cout<<"DaisyName_CrossSection.Data_hist_name  = " << DaisyName_CrossSection.Data_hist_name<<std::endl;
DaisyName_CrossSection.hist_Eff_denominator_name = crosssection_hist_Names.hist_Eff_denominator_name + DaisyName;
//std::cout<<"DaisyName_CrossSection.hist_Eff_denominator_name  = " << DaisyName_CrossSection.hist_Eff_denominator_name<<std::endl;
DaisyName_CrossSection.hist_Eff_numerator_name = crosssection_hist_Names.hist_Eff_numerator_name + DaisyName;
//std::cout<<"DaisyName_CrossSection.hist_Eff_numerator_name  = " << DaisyName_CrossSection.hist_Eff_numerator_name<<std::endl;
DaisyName_CrossSection.Migration_name = crosssection_hist_Names.Migration_name + DaisyName;
//std::cout<<"DaisyName_CrossSection.Migration_name  = " << DaisyName_CrossSection.Migration_name<<std::endl;
DaisyName_CrossSection.hist_Flux_name = crosssection_hist_Names.hist_Flux_name;
//std::cout<<"DaisyName_CrossSection.hist_Flux_name  = " << DaisyName_CrossSection.hist_Flux_name<<std::endl;

return DaisyName_CrossSection;

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
TransWarp_histNames Constuct_Unfolding_Histname(MuonVar muon_input_type,
  std::string MC_RECO_input,
  std::string MC_TRUTH_input,
  std::string Mig_input,
  std::string DATA_RECO_input,
  std::string DATA_TRUTH_input
){

  TransWarp_histNames Unfolding_hist_Names;

  Unfolding_hist_Names.MuonType = muon_input_type;

  Unfolding_hist_Names.mc_reco_name = MC_RECO_input;
  Unfolding_hist_Names.mc_truth_name = MC_TRUTH_input;
  Unfolding_hist_Names.Migration_name = Mig_input;
  Unfolding_hist_Names.data_reco_name = DATA_RECO_input;
  Unfolding_hist_Names.data_truth_name = DATA_TRUTH_input;

  return Unfolding_hist_Names;

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void Print_Transwarp_Histname(TransWarp_histNames inputHistnames){
  std::cout<< "printing out names of TransWarp hists"<< std::endl;
  std::cout <<"mc_reco_name =  " << inputHistnames.mc_reco_name <<std::endl;
  std::cout <<"mc_truth_name =  " << inputHistnames.mc_truth_name <<std::endl;
  std::cout <<"data_reco_name =  " << inputHistnames.data_reco_name <<std::endl;
  std::cout <<"data_truth_name =  " << inputHistnames.data_truth_name <<std::endl;
  std::cout <<"Migration_name =  " << inputHistnames.Migration_name <<std::endl;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
TransWarp_Hist Constuct_TransWarp_Hists(TransWarp_histNames Names, TFile *inputFile_RECO_mc){

  TransWarp_Hist Hist_struct;

  MnvH1D *mc_reco =nullptr;
  MnvH1D *mc_truth =nullptr;
  MnvH1D *data_reco =nullptr;
  MnvH1D *data_truth =nullptr;
  MnvH2D *h_Mig =nullptr;

  Hist_struct.MuonType = Names.MuonType;

  if(Debugmode==true)std::cout<<"looking formc_reco hist with name = "<< Names.mc_reco_name<<std::endl;
  char *Reco_hist_name_char = new char[Names.mc_reco_name.length() + 1];
  strcpy(Reco_hist_name_char, Names.mc_reco_name.c_str());
  if(Debugmode==true)std::cout<<"looking for mc_reco hist with name = "<< Reco_hist_name_char<<std::endl;
  mc_reco = (MnvH1D*)(inputFile_RECO_mc)->Get(Reco_hist_name_char);
  if(Debugmode==true)std::cout<<"Found Reco hist with name = "<< Reco_hist_name_char<<std::endl;

  if(Debugmode==true)std::cout<<"looking for mc_truth hist with name = "<< Names.mc_truth_name<<std::endl;
  char *mc_truth_name_char = new char[Names.mc_truth_name.length() + 1];
  strcpy(mc_truth_name_char, Names.mc_truth_name.c_str());
  if(Debugmode==true)std::cout<<"looking for mc_truth with name = "<< mc_truth_name_char<<std::endl;
  mc_truth = (MnvH1D*)(inputFile_RECO_mc)->Get(mc_truth_name_char);
  if(Debugmode==true)std::cout<<"Found mc_truth with name = "<< mc_truth_name_char<<std::endl;


  char *data_reco_name_char = new char[Names.data_reco_name.length() + 1];
  strcpy(data_reco_name_char, Names.data_reco_name.c_str());
  if(Debugmode==true)std::cout<<"looking for data_reco with name = "<< data_reco_name_char<<std::endl;
  data_reco = (MnvH1D*)(inputFile_RECO_mc)->Get(data_reco_name_char);
  if(Debugmode==true)std::cout<<"Found for data_reco with name = "<< data_reco_name_char<<std::endl;


  char *data_truth_name_char = new char[Names.data_truth_name.length() + 1];
  strcpy(data_truth_name_char, Names.data_truth_name.c_str());
  if(Debugmode==true)std::cout<<"looking for data_truth with name = "<< data_truth_name_char<<std::endl;
  data_truth = (MnvH1D*)(inputFile_RECO_mc)->Get(data_truth_name_char);
  if(Debugmode==true)std::cout<<"Found for Eff Num hist with name = "<< data_truth_name_char<<std::endl;

  char *Migration_name_char = new char[Names.Migration_name.length() + 1];
  strcpy(Migration_name_char, Names.Migration_name.c_str());
  h_Mig = (MnvH2D*)(inputFile_RECO_mc)->Get(Migration_name_char);

  Hist_struct.mc_reco =    mc_reco;
  Hist_struct.mc_truth =   mc_truth;
  Hist_struct.data_reco =  data_reco;
  Hist_struct.data_truth = data_truth;
  Hist_struct.h_Mig =      h_Mig;


  return Hist_struct;

}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

TransWarp_2DHist Constuct_TransWarp_2DHists(TransWarp_histNames Names, TFile *inputFile_RECO_mc){

TransWarp_2DHist Hist_struct;

MnvH2D *mc_reco =nullptr;
MnvH2D *mc_truth =nullptr;
MnvH2D *data_reco =nullptr;
MnvH2D *data_truth =nullptr;
MnvH2D *h_Mig =nullptr;

  Hist_struct.MuonType = Names.MuonType;

  if(Debugmode==true)std::cout<<"looking formc_reco hist with name = "<< Names.mc_reco_name<<std::endl;
  char *Reco_hist_name_char = new char[Names.mc_reco_name.length() + 1];
  strcpy(Reco_hist_name_char, Names.mc_reco_name.c_str());
  if(Debugmode==true)std::cout<<"looking for mc_reco hist with name = "<< Reco_hist_name_char<<std::endl;
    mc_reco =Get2DHist(*inputFile_RECO_mc ,Reco_hist_name_char );
  //mc_reco = (MnvH1D*)(inputFile_RECO_mc)->Get(Reco_hist_name_char);
  if(Debugmode==true)std::cout<<"Found Reco hist with name = "<< Reco_hist_name_char<<std::endl;

  if(Debugmode==true)std::cout<<"looking for mc_truth hist with name = "<< Names.mc_truth_name<<std::endl;
  char *mc_truth_name_char = new char[Names.mc_truth_name.length() + 1];
  strcpy(mc_truth_name_char, Names.mc_truth_name.c_str());
  if(Debugmode==true)std::cout<<"looking for mc_truth with name = "<< mc_truth_name_char<<std::endl;
  //mc_truth = (MnvH1D*)(inputFile_RECO_mc)->Get(mc_truth_name_char);
  mc_truth =Get2DHist(*inputFile_RECO_mc ,mc_truth_name_char );

  if(Debugmode==true)std::cout<<"Found mc_truth with name = "<< mc_truth_name_char<<std::endl;


  char *data_reco_name_char = new char[Names.data_reco_name.length() + 1];
  strcpy(data_reco_name_char, Names.data_reco_name.c_str());
  if(Debugmode==true)std::cout<<"looking for data_reco with name = "<< data_reco_name_char<<std::endl;
  //data_reco = (MnvH1D*)(inputFile_RECO_mc)->Get(data_reco_name_char);
  data_reco =Get2DHist(*inputFile_RECO_mc ,data_reco_name_char );
  if(Debugmode==true)std::cout<<"Found for data_reco with name = "<< data_reco_name_char<<std::endl;


  char *data_truth_name_char = new char[Names.data_truth_name.length() + 1];
  strcpy(data_truth_name_char, Names.data_truth_name.c_str());
  if(Debugmode==true)std::cout<<"looking for data_truth with name = "<< data_truth_name_char<<std::endl;
  //data_truth = (MnvH1D*)(inputFile_RECO_mc)->Get(data_truth_name_char);
  data_truth =Get2DHist(*inputFile_RECO_mc ,data_truth_name_char );
  if(Debugmode==true)std::cout<<"Found for Eff Num hist with name = "<< data_truth_name_char<<std::endl;

  char *Migration_name_char = new char[Names.Migration_name.length() + 1];
  strcpy(Migration_name_char, Names.Migration_name.c_str());
  //h_Mig = (MnvH2D*)(inputFile_RECO_mc)->Get(Migration_name_char);
  h_Mig =Get2DHist(*inputFile_RECO_mc ,Migration_name_char );
  Hist_struct.mc_reco =    mc_reco;
  Hist_struct.mc_truth =   mc_truth;
  Hist_struct.data_reco =  data_reco;
  Hist_struct.data_truth = data_truth;
  Hist_struct.h_Mig =      h_Mig;

  return Hist_struct;

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

ME_playlist_TransWarp_Hist_Map Constuct_TransWarp_Hists_PlaylistMap(TransWarp_histNames Names,
                                                         ME_playlist_TFileMAP MC_RECO_TfileMap)
{
  std::cout<< "Inside::Constuct_TransWarp_Hists_PlaylistMap"<< std::endl;
  ME_playlist_TransWarp_Hist_Map OutPut_Hist_Map;


  typename std::map<ME_helium_Playlists, TFile*>::const_iterator MC_RECO_it;


  for (MC_RECO_it = MC_RECO_TfileMap.begin(); MC_RECO_it != MC_RECO_TfileMap.end(); ++MC_RECO_it)
  {
    if(Debugmode==true)std::cout<<" "<< std::endl;
    if(Debugmode==true)std::cout<<"Looking for TransWarp Hist from Playlist  = "<< GetPlaylist_InitialName(MC_RECO_it->first)<<std::endl;
    TransWarp_Hist TransWarp_Hist_forplaylist = Constuct_TransWarp_Hists(Names, MC_RECO_it->second);
    OutPut_Hist_Map.insert(std::make_pair(MC_RECO_it->first, TransWarp_Hist_forplaylist));
    if(Debugmode==true)std::cout<<"~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;
    if(Debugmode==true)std::cout<<" "<< std::endl;
  }


return OutPut_Hist_Map;

}//end function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
ME_playlist_TransWarp_2DHist_Map Constuct_TransWarp_2DHists_PlaylistMap(TransWarp_histNames Names,
                                                         ME_playlist_TFileMAP MC_RECO_TfileMap
                                                         )
{
  std::cout<< "Inside::Constuct_TransWarp_2DHists_PlaylistMap"<< std::endl;
  ME_playlist_TransWarp_2DHist_Map OutPut_Hist_Map;
  typename std::map<ME_helium_Playlists, TFile*>::const_iterator MC_RECO_it;


  for (MC_RECO_it = MC_RECO_TfileMap.begin(); MC_RECO_it != MC_RECO_TfileMap.end(); ++MC_RECO_it)
  {
    if(Debugmode==true)std::cout<<" "<< std::endl;
    if(Debugmode==true)std::cout<<"Looking for TransWarp Hist from Playlist  = "<< GetPlaylist_InitialName(MC_RECO_it->first)<<std::endl;
    TransWarp_2DHist TransWarp_Hist_forplaylist = Constuct_TransWarp_2DHists(Names, MC_RECO_it->second);
    OutPut_Hist_Map.insert(std::make_pair(MC_RECO_it->first, TransWarp_Hist_forplaylist));
    if(Debugmode==true)std::cout<<"~~~~~~~~~~~~~~~~~~~~~ "<< std::endl;
    if(Debugmode==true)std::cout<<" "<< std::endl;
  }
  return OutPut_Hist_Map;

}//end function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void Print_crosssection_Histname(CrossSection_histNames crosssection_hist_Names){
  std::cout<< "printing out names of Cross section hists"<< std::endl;
  std::cout <<"Reco_hist_name =  " << crosssection_hist_Names.Reco_hist_name <<std::endl;
  std::cout <<"Reco_hist_name BG =  " << crosssection_hist_Names.Reco_hist_BG_name <<std::endl;
  std::cout <<"Data_hist_name =  " << crosssection_hist_Names.Data_hist_name <<std::endl;
  std::cout <<"hist_Eff_denominator_name =  " << crosssection_hist_Names.hist_Eff_denominator_name <<std::endl;
  std::cout <<"hist_Eff_numerator_name =  " << crosssection_hist_Names.hist_Eff_numerator_name <<std::endl;
  std::cout <<"Migration_name =  " << crosssection_hist_Names.Migration_name <<std::endl;
  std::cout <<"Flux_name =  " << crosssection_hist_Names.hist_Flux_name <<std::endl;

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
CrossSection_Hist Constuct_crosssection_Hists(CrossSection_histNames Names, TFile *inputFile_RECO_mc,TFile *inputFile_TRUE_mc, TFile *inputFile_data ){

  //std::cout<<"Inside::Constuct_crosssection_Hists"<<std::endl;
  CrossSection_Hist Hist_struct;

  MnvH1D *hist_Flux=nullptr;
  MnvH1D *hist_DATA=nullptr;
  MnvH1D *hist_RECO=nullptr;
  MnvH1D *hist_RECO_BG=nullptr;
  MnvH1D *hist_numerator=nullptr;
  MnvH1D *hist_demonator=nullptr;
  MnvH2D *hist_Mig=nullptr;

  Hist_struct.MuonType = Names.MuonType;

  char *Reco_hist_name_char = new char[Names.Reco_hist_name.length() + 1];
  strcpy(Reco_hist_name_char, Names.Reco_hist_name.c_str());
  //std::cout<<" Reco_hist_name_char " << Reco_hist_name_char<< std::endl;
  hist_RECO = Get1DHist(*inputFile_RECO_mc, Reco_hist_name_char);

  char *Reco_hist_BG_name_char = new char[Names.Reco_hist_BG_name.length() + 1];
  strcpy(Reco_hist_BG_name_char, Names.Reco_hist_BG_name.c_str());
  //std::cout<<" Reco_hist_BG_name_char " << Reco_hist_BG_name_char<< std::endl;
  hist_RECO_BG = Get1DHist(*inputFile_RECO_mc, Reco_hist_BG_name_char);

  char *Data_hist_name_char = new char[Names.Data_hist_name.length() + 1];
  strcpy(Data_hist_name_char, Names.Data_hist_name.c_str());
  //std::cout<<" Data_hist_name_char " << Data_hist_name_char<< std::endl;
  hist_DATA = Get1DHist(*inputFile_data, Data_hist_name_char);

  char *hist_Eff_numerator_name_char = new char[Names.hist_Eff_numerator_name.length() + 1];
  strcpy(hist_Eff_numerator_name_char, Names.hist_Eff_numerator_name.c_str());
  //std::cout<<" hist_Eff_numerator_name_char " << hist_Eff_numerator_name_char<< std::endl;
  hist_numerator = Get1DHist(*inputFile_RECO_mc, hist_Eff_numerator_name_char);

  char *hist_Eff_denominator_name_char = new char[Names.hist_Eff_denominator_name.length() + 1];
  strcpy(hist_Eff_denominator_name_char, Names.hist_Eff_denominator_name.c_str());
  //std::cout<<" hist_Eff_denominator_name_char " << hist_Eff_denominator_name_char<< std::endl;
  hist_demonator = Get1DHist(*inputFile_TRUE_mc, hist_Eff_denominator_name_char);

  char *Migration_name_char = new char[Names.Migration_name.length() + 1];
  strcpy(Migration_name_char, Names.Migration_name.c_str());
  //std::cout<<" Migration_name_char " << Migration_name_char<< std::endl;
  hist_Mig = (MnvH2D*)(inputFile_RECO_mc)->Get(Migration_name_char);

  char *Flux_name_char = new char[Names.hist_Flux_name.length() + 1];
  strcpy(Flux_name_char, Names.hist_Flux_name.c_str());
  //std::cout<<" Flux_name_char " << Flux_name_char<< std::endl;
  hist_Flux = Get1DHist(*inputFile_RECO_mc, Flux_name_char);

  hist_demonator->AddMissingErrorBandsAndFillWithCV(*hist_numerator);
  hist_DATA->AddMissingErrorBandsAndFillWithCV(*hist_numerator);
  //hist_Flux->AddMissingErrorBandsAndFillWithCV(*hist_numerator);

  Hist_struct.h_flux = hist_Flux;
  Hist_struct.h_Data_Signal = hist_DATA;
  Hist_struct.h_RECO_Signal = hist_RECO;
  Hist_struct.h_RECO_BG = hist_RECO_BG;
  Hist_struct.h_effNum = hist_numerator;
  Hist_struct.h_effDom = hist_demonator;
  Hist_struct.h_Mig = hist_Mig;

  return Hist_struct;

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
CrossSection_Hist MakeDaisyCrossSectionHist(CrossSection_histNames Names, std::string DaisyN,  TFile *inputFile_RECO_mc,TFile *inputFile_TRUE_mc, TFile *inputFile_data ){
  CrossSection_histNames Daisy_names = MakeDaisy_names(Names,  DaisyN);
  //Print_crosssection_Histname(Daisy_names);

  CrossSection_Hist Daisy = Constuct_crosssection_Hists( Daisy_names, inputFile_RECO_mc, inputFile_TRUE_mc, inputFile_data );

  return Daisy;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
CrossSection_Hist_Daisy Constuct_crosssection_Hists_Daisy(CrossSection_histNames Names, TFile *inputFile_RECO_mc,TFile *inputFile_TRUE_mc, TFile *inputFile_data ){

  CrossSection_Hist_Daisy Daisy_hists;
  //std::cout << "Size of Daisy_hists: " << sizeof(Daisy_hists) << " bytes" << std::endl;


  CrossSection_histNames Daisy0_names = MakeDaisy_names(Names,  "0");
  //Print_crosssection_Histname(Daisy0_names);
  CrossSection_Hist Daisy0 = Constuct_crosssection_Hists( Daisy0_names, inputFile_RECO_mc, inputFile_TRUE_mc, inputFile_data );
  Daisy_hists.Daisy0 = Daisy0;

  CrossSection_histNames Daisy1_names = MakeDaisy_names(Names,  "1");
  CrossSection_Hist Daisy1 = Constuct_crosssection_Hists( Daisy1_names, inputFile_RECO_mc, inputFile_TRUE_mc, inputFile_data );
  Daisy_hists.Daisy1 = Daisy1;

  CrossSection_histNames Daisy2_names = MakeDaisy_names(Names,  "2");
  CrossSection_Hist Daisy2 = Constuct_crosssection_Hists( Daisy2_names, inputFile_RECO_mc, inputFile_TRUE_mc, inputFile_data );
  Daisy_hists.Daisy2 = Daisy2;

  CrossSection_histNames Daisy3_names = MakeDaisy_names(Names,  "3");
  CrossSection_Hist Daisy3 = Constuct_crosssection_Hists( Daisy3_names, inputFile_RECO_mc, inputFile_TRUE_mc, inputFile_data );
  Daisy_hists.Daisy3 = Daisy3;

  CrossSection_histNames Daisy4_names = MakeDaisy_names(Names,  "4");
  CrossSection_Hist Daisy4 = Constuct_crosssection_Hists( Daisy4_names, inputFile_RECO_mc, inputFile_TRUE_mc, inputFile_data );
  Daisy_hists.Daisy4 = Daisy4;

  CrossSection_histNames Daisy5_names = MakeDaisy_names(Names,  "5");
  CrossSection_Hist Daisy5 = Constuct_crosssection_Hists( Daisy5_names, inputFile_RECO_mc, inputFile_TRUE_mc, inputFile_data );
  Daisy_hists.Daisy5 = Daisy5;

  CrossSection_histNames Daisy6_names = MakeDaisy_names(Names,  "6");
  CrossSection_Hist Daisy6 = Constuct_crosssection_Hists( Daisy6_names, inputFile_RECO_mc, inputFile_TRUE_mc, inputFile_data );
  Daisy_hists.Daisy6 = Daisy6;

  CrossSection_histNames Daisy7_names = MakeDaisy_names(Names,  "7");
  CrossSection_Hist Daisy7 = Constuct_crosssection_Hists( Daisy7_names, inputFile_RECO_mc, inputFile_TRUE_mc, inputFile_data );
  Daisy_hists.Daisy7 = Daisy7;

  CrossSection_histNames Daisy8_names = MakeDaisy_names(Names,  "8");
  CrossSection_Hist Daisy8 = Constuct_crosssection_Hists( Daisy8_names, inputFile_RECO_mc, inputFile_TRUE_mc, inputFile_data );
  Daisy_hists.Daisy8 = Daisy8;

  CrossSection_histNames Daisy9_names = MakeDaisy_names(Names,  "9");
  CrossSection_Hist Daisy9 = Constuct_crosssection_Hists( Daisy9_names, inputFile_RECO_mc, inputFile_TRUE_mc, inputFile_data );
  Daisy_hists.Daisy9 = Daisy9;

  CrossSection_histNames Daisy10_names = MakeDaisy_names(Names,  "10");
  CrossSection_Hist Daisy10 = Constuct_crosssection_Hists( Daisy10_names, inputFile_RECO_mc, inputFile_TRUE_mc, inputFile_data );
  Daisy_hists.Daisy10 = Daisy10;

  CrossSection_histNames Daisy11_names = MakeDaisy_names(Names,  "11");
  CrossSection_Hist Daisy11 = Constuct_crosssection_Hists( Daisy11_names, inputFile_RECO_mc, inputFile_TRUE_mc, inputFile_data );
  Daisy_hists.Daisy11 = Daisy11;

  return Daisy_hists;

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
CrossSection_Hist Constuct_crosssection_Hists_noBG(CrossSection_histNames Names, TFile *inputFile_RECO_mc,TFile *inputFile_TRUE_mc, TFile *inputFile_data ){

  CrossSection_Hist Hist_struct;

  MnvH1D *hist_Flux=nullptr;
  MnvH1D *hist_DATA=nullptr;
  MnvH1D *hist_RECO=nullptr;
  MnvH1D *hist_numerator=nullptr;
  MnvH1D *hist_demonator=nullptr;
  MnvH2D *hist_Mig=nullptr;

  Hist_struct.MuonType = Names.MuonType;

  std::cout<<"looking for Reco hist with name = "<< Names.Reco_hist_name<<std::endl;
  char *Reco_hist_name_char = new char[Names.Reco_hist_name.length() + 1];
  strcpy(Reco_hist_name_char, Names.Reco_hist_name.c_str());
  std::cout<<"looking for Reco hist with name = "<< Reco_hist_name_char<<std::endl;
  hist_RECO = (MnvH1D*)(inputFile_RECO_mc)->Get(Reco_hist_name_char);
  std::cout<<"Found Reco hist with name = "<< Reco_hist_name_char<<std::endl;


  char *Data_hist_name_char = new char[Names.Data_hist_name.length() + 1];
  strcpy(Data_hist_name_char, Names.Data_hist_name.c_str());
  std::cout<<"looking for data hist with name = "<< Data_hist_name_char<<std::endl;
  hist_DATA = (MnvH1D*)(inputFile_data)->Get(Data_hist_name_char);
  std::cout<<"Found for data hist with name = "<< Data_hist_name_char<<std::endl;


  char *hist_Eff_numerator_name_char = new char[Names.hist_Eff_numerator_name.length() + 1];
  strcpy(hist_Eff_numerator_name_char, Names.hist_Eff_numerator_name.c_str());
  std::cout<<"looking for Eff Num hist with name = "<< hist_Eff_numerator_name_char<<std::endl;
  hist_numerator = (MnvH1D*)(inputFile_RECO_mc)->Get(hist_Eff_numerator_name_char);
  std::cout<<"Found for Eff Num hist with name = "<< hist_Eff_numerator_name_char<<std::endl;


  char *hist_Eff_denominator_name_char = new char[Names.hist_Eff_denominator_name.length() + 1];
  strcpy(hist_Eff_denominator_name_char, Names.hist_Eff_denominator_name.c_str());
  std::cout<<"looking for Eff Dem hist with name = "<< hist_Eff_denominator_name_char<<std::endl;
  hist_demonator = (MnvH1D*)(inputFile_TRUE_mc)->Get(hist_Eff_denominator_name_char);

  std::cout<<"Found for Eff Dem hist with name = "<< hist_Eff_denominator_name_char<<std::endl;

  char *Migration_name_char = new char[Names.Migration_name.length() + 1];
  strcpy(Migration_name_char, Names.Migration_name.c_str());
  hist_Mig = (MnvH2D*)(inputFile_RECO_mc)->Get(Migration_name_char);


  char *Flux_name_char = new char[Names.hist_Flux_name.length() + 1];
  strcpy(Flux_name_char, Names.hist_Flux_name.c_str());
  std::cout<<"looking for Flux hist with name = "<< Flux_name_char<<std::endl;
  hist_Flux = (MnvH1D*)(inputFile_RECO_mc)->Get(Flux_name_char);


  hist_demonator->AddMissingErrorBandsAndFillWithCV(*hist_numerator);
  hist_DATA->AddMissingErrorBandsAndFillWithCV(*hist_numerator);
  //hist_Flux->AddMissingErrorBandsAndFillWithCV(*hist_numerator);

  Hist_struct.h_flux = hist_Flux;
  Hist_struct.h_Data_Signal = hist_DATA;
  Hist_struct.h_RECO_Signal = hist_RECO;
  Hist_struct.h_effNum = hist_numerator;
  Hist_struct.h_effDom = hist_demonator;
  Hist_struct.h_Mig = hist_Mig;

  return Hist_struct;

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
CrossSection_Hist Constuct_crosssection_Hists_noMig_Flux_BG(CrossSection_histNames Names, TFile *inputFile_RECO_mc,TFile *inputFile_TRUE_mc, TFile *inputFile_data ){

  CrossSection_Hist Hist_struct;

  MnvH1D *hist_DATA=nullptr;
  MnvH1D *hist_RECO=nullptr;
  MnvH1D *hist_numerator=nullptr;
  MnvH1D *hist_demonator=nullptr;


  std::cout<<"looking for Reco hist with name = "<< Names.Reco_hist_name<<std::endl;
  char *Reco_hist_name_char = new char[Names.Reco_hist_name.length() + 1];
  strcpy(Reco_hist_name_char, Names.Reco_hist_name.c_str());
  std::cout<<"looking for Reco hist with name = "<< Reco_hist_name_char<<std::endl;
  hist_RECO =  Get1DHist(*inputFile_RECO_mc,Reco_hist_name_char);
  //hist_RECO = (MnvH1D*)()->Get(Reco_hist_name_char);
  std::cout<<"Found Reco hist with name = "<< Reco_hist_name_char<<std::endl;


  char *Data_hist_name_char = new char[Names.Data_hist_name.length() + 1];
  strcpy(Data_hist_name_char, Names.Data_hist_name.c_str());
  std::cout<<"looking for data hist with name = "<< Data_hist_name_char<<std::endl;
  hist_DATA =Get1DHist(*inputFile_data,Data_hist_name_char);
//  hist_DATA = (MnvH1D*)(inputFile_data)->Get(Data_hist_name_char);
  std::cout<<"Found for data hist with name = "<< Data_hist_name_char<<std::endl;


  char *hist_Eff_numerator_name_char = new char[Names.hist_Eff_numerator_name.length() + 1];
  strcpy(hist_Eff_numerator_name_char, Names.hist_Eff_numerator_name.c_str());
  std::cout<<"looking for Eff Num hist with name = "<< hist_Eff_numerator_name_char<<std::endl;
  //hist_numerator = (MnvH1D*)(inputFile_RECO_mc)->Get(hist_Eff_numerator_name_char);
    hist_numerator =Get1DHist(*inputFile_RECO_mc,hist_Eff_numerator_name_char);
  std::cout<<"Found for Eff Num hist with name = "<< hist_Eff_numerator_name_char<<std::endl;


  char *hist_Eff_denominator_name_char = new char[Names.hist_Eff_denominator_name.length() + 1];
  strcpy(hist_Eff_denominator_name_char, Names.hist_Eff_denominator_name.c_str());
  std::cout<<"looking for Eff Dem hist with name = "<< hist_Eff_denominator_name_char<<std::endl;
  //hist_demonator = (MnvH1D*)(inputFile_TRUE_mc)->Get(hist_Eff_denominator_name_char);
  hist_demonator =Get1DHist(*inputFile_TRUE_mc,hist_Eff_denominator_name_char);
  std::cout<<"Found for Eff Dem hist with name = "<< hist_Eff_denominator_name_char<<std::endl;


  hist_demonator->AddMissingErrorBandsAndFillWithCV(*hist_numerator);
  hist_DATA->AddMissingErrorBandsAndFillWithCV(*hist_numerator);
  //hist_Flux->AddMissingErrorBandsAndFillWithCV(*hist_numerator);

  Hist_struct.h_Data_Signal = hist_DATA;
  Hist_struct.h_RECO_Signal = hist_RECO;
  Hist_struct.h_effNum = hist_numerator;
  Hist_struct.h_effDom = hist_demonator;
  return Hist_struct;

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
ME_playlist_CrossSection_MAP Constuct_crosssection_Hists_PlaylistMap(CrossSection_histNames Names,
                                                         ME_playlist_TFileMAP MC_RECO_TfileMap,
                                                         ME_playlist_TFileMAP MC_TRUTH_TfileMap,
                                                         ME_playlist_TFileMAP Data_TfileMap )
{
  std::cout<< "Constuct Cross Section Hist Map"<< std::endl;
  ME_playlist_CrossSection_MAP OutPut_Hist_Map;


  typename std::map<ME_helium_Playlists, TFile*>::const_iterator MC_RECO_it;
  typename std::map<ME_helium_Playlists, TFile*>::const_iterator MC_TRUTH_it;
  typename std::map<ME_helium_Playlists, TFile*>::const_iterator Data_it;

  for (MC_RECO_it = MC_RECO_TfileMap.begin(), Data_it = Data_TfileMap.begin(), MC_TRUTH_it= MC_TRUTH_TfileMap.begin() ; MC_RECO_it != MC_RECO_TfileMap.end(); ++MC_RECO_it, ++MC_TRUTH_it, ++Data_it)
  {
    if(MC_RECO_it->first != MC_TRUTH_it->first || Data_it->first != MC_TRUTH_it->first){assert(("The TFiles making ME_playlist_CrossSection_MAP do not Match ", false));}
    CrossSection_Hist CrossSection_Hist_forplaylist = Constuct_crosssection_Hists(Names, MC_RECO_it->second, MC_TRUTH_it->second, Data_it->second);
    OutPut_Hist_Map.insert(std::make_pair(MC_RECO_it->first, CrossSection_Hist_forplaylist));
  }

return OutPut_Hist_Map;

}//end function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
ME_playlist_CrossSection_MAP_DAISY Constuct_crosssection_Hists_PlaylistMap_DAISY(CrossSection_histNames Names,
                                                         ME_playlist_TFileMAP MC_RECO_TfileMap,
                                                         ME_playlist_TFileMAP MC_TRUTH_TfileMap,
                                                         ME_playlist_TFileMAP Data_TfileMap )
{
  std::cout<< "Constuct Cross Section Hist Map"<< std::endl;
  ME_playlist_CrossSection_MAP_DAISY OutPut_Hist_Map;


  typename std::map<ME_helium_Playlists, TFile*>::const_iterator MC_RECO_it;
  typename std::map<ME_helium_Playlists, TFile*>::const_iterator MC_TRUTH_it;
  typename std::map<ME_helium_Playlists, TFile*>::const_iterator Data_it;

  for (MC_RECO_it = MC_RECO_TfileMap.begin(), Data_it = Data_TfileMap.begin(), MC_TRUTH_it= MC_TRUTH_TfileMap.begin() ; MC_RECO_it != MC_RECO_TfileMap.end(); ++MC_RECO_it, ++MC_TRUTH_it, ++Data_it)
  {
    if(MC_RECO_it->first != MC_TRUTH_it->first || Data_it->first != MC_TRUTH_it->first){assert(("The TFiles making ME_playlist_CrossSection_MAP do not Match ", false));}
std::cout<<"Making CrossSection_Hist_Daisy First Playlist::"<< GetPlaylist_Name(MC_RECO_it->first)<<std::endl;

    CrossSection_Hist_Daisy CrossSection_Hist_forplaylist = Constuct_crosssection_Hists_Daisy(Names, MC_RECO_it->second, MC_TRUTH_it->second, Data_it->second);
    OutPut_Hist_Map.insert(std::make_pair(MC_RECO_it->first, CrossSection_Hist_forplaylist));
  }

return OutPut_Hist_Map;

}//end function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
ME_playlist_CrossSection_MAP Constuct_crosssection_Hists_PlaylistMap_noBG(CrossSection_histNames Names,
                                                         ME_playlist_TFileMAP MC_RECO_TfileMap,
                                                         ME_playlist_TFileMAP MC_TRUTH_TfileMap,
                                                         ME_playlist_TFileMAP Data_TfileMap )
{
  std::cout<< "Constuct Cross Section Hist Map"<< std::endl;
  ME_playlist_CrossSection_MAP OutPut_Hist_Map;


  typename std::map<ME_helium_Playlists, TFile*>::const_iterator MC_RECO_it;
  typename std::map<ME_helium_Playlists, TFile*>::const_iterator MC_TRUTH_it;
  typename std::map<ME_helium_Playlists, TFile*>::const_iterator Data_it;

  for (MC_RECO_it = MC_RECO_TfileMap.begin(), Data_it = Data_TfileMap.begin(), MC_TRUTH_it= MC_TRUTH_TfileMap.begin() ; MC_RECO_it != MC_RECO_TfileMap.end(); ++MC_RECO_it, ++MC_TRUTH_it, ++Data_it)
  {
    if(MC_RECO_it->first != MC_TRUTH_it->first || Data_it->first != MC_TRUTH_it->first){assert(("The TFiles making ME_playlist_CrossSection_MAP do not Match ", false));}
    CrossSection_Hist CrossSection_Hist_forplaylist = Constuct_crosssection_Hists_noBG(Names, MC_RECO_it->second, MC_TRUTH_it->second, Data_it->second);
    OutPut_Hist_Map.insert(std::make_pair(MC_RECO_it->first, CrossSection_Hist_forplaylist));
  }

return OutPut_Hist_Map;

}//end function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
ME_playlist_CrossSection_MAP Constuct_crosssection_Hists_PlaylistMap_noMig_Flux_BG(CrossSection_histNames Names,
                                                         ME_playlist_TFileMAP MC_RECO_TfileMap,
                                                         ME_playlist_TFileMAP MC_TRUTH_TfileMap,
                                                         ME_playlist_TFileMAP Data_TfileMap )
{
  std::cout<< "Constuct Cross Section Hist Map"<< std::endl;
  ME_playlist_CrossSection_MAP OutPut_Hist_Map;


  typename std::map<ME_helium_Playlists, TFile*>::const_iterator MC_RECO_it;
  typename std::map<ME_helium_Playlists, TFile*>::const_iterator MC_TRUTH_it;
  typename std::map<ME_helium_Playlists, TFile*>::const_iterator Data_it;

  for (MC_RECO_it = MC_RECO_TfileMap.begin(), Data_it = Data_TfileMap.begin(), MC_TRUTH_it= MC_TRUTH_TfileMap.begin() ; MC_RECO_it != MC_RECO_TfileMap.end(); ++MC_RECO_it, ++MC_TRUTH_it, ++Data_it)
  {
    if(MC_RECO_it->first != MC_TRUTH_it->first || Data_it->first != MC_TRUTH_it->first){assert(("The TFiles making ME_playlist_CrossSection_MAP do not Match ", false));}
    CrossSection_Hist CrossSection_Hist_forplaylist = Constuct_crosssection_Hists_noMig_Flux_BG(Names, MC_RECO_it->second, MC_TRUTH_it->second, Data_it->second);
    OutPut_Hist_Map.insert(std::make_pair(MC_RECO_it->first, CrossSection_Hist_forplaylist));
  }

return OutPut_Hist_Map;

}//end function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
Interaction_type_MnvH1D_Map AddInteractionHistMap(TFile& file, std::string input_hist_name){

std::string Hist_name;

Interaction_type_MnvH1D_Map Interaction_HistMap_output;

  Hist_name = input_hist_name + "_Interaction_Elastic";
  MnvH1D* h_elastic =  Get1DHist(file, Hist_name );
  Interaction_HistMap_output.insert ( std::pair<Interaction_type, PlotUtils::MnvH1D*>(kElastic,h_elastic) );

  Hist_name = input_hist_name + "_Interaction_1Pion";
  MnvH1D* h_Res_Coh_Pion =  Get1DHist(file, Hist_name );
  Interaction_HistMap_output.insert ( std::pair<Interaction_type, PlotUtils::MnvH1D*>(kRes_Coh_Pion,h_Res_Coh_Pion) );

  Hist_name = input_hist_name + "_Interaction_2p2h";
  MnvH1D* h_2p2h =  Get1DHist(file, Hist_name );
  Interaction_HistMap_output.insert ( std::pair<Interaction_type, PlotUtils::MnvH1D*>(k2p2h,h_2p2h) );

  Hist_name = input_hist_name + "_Interaction_DIS";
  MnvH1D* h_DIS =  Get1DHist(file, Hist_name );
  Interaction_HistMap_output.insert ( std::pair<Interaction_type, PlotUtils::MnvH1D*>(kDIS,h_DIS) );

  Hist_name = input_hist_name + "_Interaction_None";
  MnvH1D* h_Interaction_NONE =  Get1DHist(file, Hist_name );
  Interaction_HistMap_output.insert ( std::pair<Interaction_type, PlotUtils::MnvH1D*>(kInteraction_NONE,h_Interaction_NONE) );

  Hist_name = input_hist_name + "_Interaction_Other";
  MnvH1D* h_Interaction_OTHER =  Get1DHist(file, Hist_name );
  Interaction_HistMap_output.insert ( std::pair<Interaction_type, PlotUtils::MnvH1D*>(kInteraction_OTHER,h_Interaction_OTHER) );

return Interaction_HistMap_output;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
Interaction_type_MnvH1D_Map AddInteractionHistMap_DISbreakdown(TFile& file, std::string input_hist_name, std::string extra){
  Interaction_type_MnvH1D_Map Interaction_HistMap_output;

  std::string Hist_name = input_hist_name + "_Interaction"+ extra +"_QE";
  MnvH1D* h_elastic =  Get1DHist(file, Hist_name );
  Interaction_HistMap_output.insert ( std::pair<Interaction_type, PlotUtils::MnvH1D*>(kElastic,h_elastic) );

  Hist_name = input_hist_name + "_Interaction"+ extra +"_#DeltaRes";
  MnvH1D* h_deltaRES =  Get1DHist(file, Hist_name );
  Interaction_HistMap_output.insert ( std::pair<Interaction_type, PlotUtils::MnvH1D*>(kdeltaRES,h_deltaRES) );

  Hist_name = input_hist_name + "_Interaction"+ extra +"_HeavierRes";
  MnvH1D* h_HeavierRes =  Get1DHist(file, Hist_name );
  Interaction_HistMap_output.insert ( std::pair<Interaction_type, PlotUtils::MnvH1D*>(kHeavierRES, h_HeavierRes) );

  Hist_name = input_hist_name + "_Interaction"+ extra +"_2p2h";
  MnvH1D* h_2p2h =  Get1DHist(file, Hist_name );
  Interaction_HistMap_output.insert ( std::pair<Interaction_type, PlotUtils::MnvH1D*>(k2p2h,h_2p2h) );

  Hist_name = input_hist_name + "_Interaction"+ extra +"_SoftDIS";
  MnvH1D* h_DISSoft =  Get1DHist(file, Hist_name );
  Interaction_HistMap_output.insert ( std::pair<Interaction_type, PlotUtils::MnvH1D*>(kDISSoft,h_DISSoft) );

  Hist_name = input_hist_name + "_Interaction"+ extra +"_HardDIS";
  MnvH1D* h_DISHard =  Get1DHist(file, Hist_name );
  Interaction_HistMap_output.insert ( std::pair<Interaction_type, PlotUtils::MnvH1D*>(kDISHard,h_DISHard) );

  Hist_name = input_hist_name + "_Interaction"+ extra +"_SIS";
  MnvH1D* h_SIS =  Get1DHist(file, Hist_name );
  Interaction_HistMap_output.insert ( std::pair<Interaction_type, PlotUtils::MnvH1D*>(kDISSIS,h_SIS) );

  Hist_name = input_hist_name + "_Interaction"+ extra +"_None";
  MnvH1D* h_Interaction_NONE =  Get1DHist(file, Hist_name );
  Interaction_HistMap_output.insert ( std::pair<Interaction_type, PlotUtils::MnvH1D*>(kInteraction_NONE,h_Interaction_NONE) );

  Hist_name = input_hist_name + "_Interaction"+ extra +"_Other";
  MnvH1D* h_Interaction_OTHER =  Get1DHist(file, Hist_name );
  Interaction_HistMap_output.insert ( std::pair<Interaction_type, PlotUtils::MnvH1D*>(kInteraction_OTHER,h_Interaction_OTHER) );


return Interaction_HistMap_output;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
Material_type_MnvH1D_Map AddMaterialHistMap(TFile& file, std::string input_hist_name){

  Material_type_MnvH1D_Map Material_HistMap_output;

  std::string Hist_name = input_hist_name + "_Material_Other";
  MnvH1D* h_Other =  Get1DHist(file, Hist_name );
  Material_HistMap_output.insert ( std::pair<Material_type, PlotUtils::MnvH1D*>(kMaterial_OTHER,h_Other) );

  Hist_name = input_hist_name + "_Material_Iron";
  MnvH1D* h_Iron =  Get1DHist(file, Hist_name );
  Material_HistMap_output.insert ( std::pair<Material_type, PlotUtils::MnvH1D*>(kIron,h_Iron) );

  Hist_name = input_hist_name + "_Material_Carbon";
  MnvH1D* h_Carbon =  Get1DHist(file, Hist_name );
  Material_HistMap_output.insert ( std::pair<Material_type, PlotUtils::MnvH1D*>(kCarbon, h_Carbon) );

  Hist_name = input_hist_name + "_Material_Lead";
  MnvH1D* h_Lead =  Get1DHist(file, Hist_name );
  Material_HistMap_output.insert ( std::pair<Material_type, PlotUtils::MnvH1D*>(kLead,h_Lead) );

  Hist_name = input_hist_name + "_Material_Aluminium";
  MnvH1D* h_Aluminium =  Get1DHist(file, Hist_name );
  Material_HistMap_output.insert ( std::pair<Material_type, PlotUtils::MnvH1D*>(kAluminium,h_Aluminium) );

  Hist_name = input_hist_name + "_Material_Helium";
  MnvH1D* h_Helium =  Get1DHist(file, Hist_name );
  Material_HistMap_output.insert ( std::pair<Material_type, PlotUtils::MnvH1D*>(kHelium,h_Helium) );



return Material_HistMap_output;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void AddInteractionHistMap(ME_playlist_CrossSection_MAP &Hist_Map, ME_playlist_TFileMAP MC_TRUTH_TfileMap,
  std::string input_hist_name){
  typename std::map<ME_helium_Playlists, TFile*>::const_iterator MC_TRUTH_it;
  typename std::map<ME_helium_Playlists, CrossSection_Hist>::const_iterator Hist_Map_it;
  for (MC_TRUTH_it= MC_TRUTH_TfileMap.begin(), Hist_Map_it= Hist_Map.begin() ; MC_TRUTH_it != MC_TRUTH_TfileMap.end();  ++MC_TRUTH_it,++Hist_Map_it){

    if(Hist_Map_it->first != MC_TRUTH_it->first){std::cout<<"Maps not in same Playlist order: need to fix" << std::endl; assert(false);}
    Interaction_type_MnvH1D_Map Interaction_HistMap_output = AddInteractionHistMap(*MC_TRUTH_it->second, input_hist_name);

    Hist_Map[Hist_Map_it->first].Interaction_HistMap = Interaction_HistMap_output;

  }
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void AddInteractionHistMap_DISbreakdown(ME_playlist_CrossSection_MAP &Hist_Map,
  ME_playlist_TFileMAP MC_TRUTH_TfileMap, std::string input_hist_name, std::string extra_name){


  typename std::map<ME_helium_Playlists, TFile*>::const_iterator MC_TRUTH_it;
  typename std::map<ME_helium_Playlists, CrossSection_Hist>::const_iterator Hist_Map_it;
  for (MC_TRUTH_it= MC_TRUTH_TfileMap.begin(), Hist_Map_it= Hist_Map.begin() ; MC_TRUTH_it != MC_TRUTH_TfileMap.end();  ++MC_TRUTH_it,++Hist_Map_it){

    if(Hist_Map_it->first != MC_TRUTH_it->first){std::cout<<"Maps not in same Playlist order: need to fix" << std::endl; assert(false);}
    Interaction_type_MnvH1D_Map Interaction_HistMap_output = AddInteractionHistMap_DISbreakdown(*MC_TRUTH_it->second, input_hist_name, extra_name);

    Hist_Map[Hist_Map_it->first].Interaction_HistMap = Interaction_HistMap_output;

  }
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void AddRECOMaterialHistMap(ME_playlist_CrossSection_MAP &Hist_Map, ME_playlist_TFileMAP MC_RECO_TfileMap,
  std::string input_hist_name){

  typename std::map<ME_helium_Playlists, TFile*>::const_iterator MC_RECO_it;
  typename std::map<ME_helium_Playlists, CrossSection_Hist>::const_iterator Hist_Map_it;
  for (MC_RECO_it= MC_RECO_TfileMap.begin(), Hist_Map_it= Hist_Map.begin() ; MC_RECO_it != MC_RECO_TfileMap.end();  ++MC_RECO_it,++Hist_Map_it){

    if(Hist_Map_it->first != MC_RECO_it->first){std::cout<<"Maps not in same Playlist order: need to fix" << std::endl; assert(false);}
    Material_type_MnvH1D_Map Material_HistMap_output = AddMaterialHistMap(*MC_RECO_it->second, input_hist_name);

    Hist_Map[Hist_Map_it->first].Material_HistMap_RECO = Material_HistMap_output;

  }
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
CrossSection_Hist Combine_crosssection_Hists_PlaylistMap(ME_playlist_CrossSection_MAP inputMap,
  ME_helium_Playlists playlist_combine_too ){

  CrossSection_Hist output_hist;
  typename std::map<ME_helium_Playlists, CrossSection_Hist>::const_iterator inputMap_it;

  MnvH1D *hist_Flux=nullptr;
  MnvH1D *hist_DATA=nullptr;
  MnvH1D *hist_RECO=nullptr;
  MnvH1D *hist_numerator=nullptr;
  MnvH1D *hist_demonator=nullptr;
  MnvH2D *hist_Mig=nullptr;


  hist_DATA = inputMap[playlist_combine_too].h_Data_Signal;
  hist_RECO = inputMap[playlist_combine_too].h_RECO_Signal;
  hist_numerator = inputMap[playlist_combine_too].h_effNum;
  hist_demonator = inputMap[playlist_combine_too].h_effDom;
  hist_Mig = inputMap[playlist_combine_too].h_Mig;
  hist_Flux= inputMap[playlist_combine_too].h_flux;

  for (inputMap_it = inputMap.begin(); inputMap_it != inputMap.end(); ++inputMap_it){

    if(inputMap_it->first == playlist_combine_too ) continue;

    hist_DATA->Add(inputMap_it->second.h_Data_Signal);
    hist_RECO->Add(inputMap_it->second.h_RECO_Signal);
    hist_numerator->Add(inputMap_it->second.h_effNum);
    hist_demonator->Add(inputMap_it->second.h_effDom);
    hist_Mig->Add(inputMap_it->second.h_Mig);
  } // end of loop

    output_hist.h_flux = hist_Flux;
    output_hist.h_Data_Signal = hist_DATA;
    output_hist.h_RECO_Signal = hist_RECO;
    output_hist.h_effNum = hist_numerator;
    output_hist.h_effDom = hist_demonator;
    output_hist.h_Mig = hist_Mig;

return output_hist;

}//end of function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

CrossSection_Hist Combine_crosssection_Hists_PlaylistMap_includeInteraction(ME_playlist_CrossSection_MAP inputMap,
   ME_helium_Playlists playlist_combine_too ){

  CrossSection_Hist output_hist;
  typename std::map<ME_helium_Playlists, CrossSection_Hist>::const_iterator inputMap_it;

  MnvH1D *hist_Flux=nullptr;
  MnvH1D *hist_DATA=nullptr;
  MnvH1D *hist_RECO=nullptr;
  MnvH1D *hist_numerator=nullptr;
  MnvH1D *hist_demonator=nullptr;
  MnvH2D *hist_Mig=nullptr;
  Interaction_type_MnvH1D_Map Interaction_HistMap;
  std::cout<< "First hist from playlist: "<< GetPlaylist_InitialName(playlist_combine_too)<< std::endl;
  hist_DATA = inputMap[playlist_combine_too].h_Data_Signal;
  hist_RECO = inputMap[playlist_combine_too].h_RECO_Signal;
  hist_numerator = inputMap[playlist_combine_too].h_effNum;
  hist_demonator = inputMap[playlist_combine_too].h_effDom;
  hist_Mig = inputMap[playlist_combine_too].h_Mig;
  hist_Flux= inputMap[playlist_combine_too].h_flux;
  Interaction_HistMap = inputMap[playlist_combine_too].Interaction_HistMap;


  for (inputMap_it = inputMap.begin(); inputMap_it != inputMap.end(); ++inputMap_it){

    if(inputMap_it->first == playlist_combine_too ) continue;
    std::cout<< " Playlist: "<< GetPlaylist_InitialName(inputMap_it->first)<< std::endl;
    hist_DATA->Add(inputMap_it->second.h_Data_Signal);
    hist_RECO->Add(inputMap_it->second.h_RECO_Signal);
    hist_numerator->Add(inputMap_it->second.h_effNum);
    hist_demonator->Add(inputMap_it->second.h_effDom);
    hist_Mig->Add(inputMap_it->second.h_Mig);
    Interaction_HistMap[kElastic]->Add(inputMap[inputMap_it->first].Interaction_HistMap[kElastic]);
    Interaction_HistMap[kRes_Coh_Pion]->Add(inputMap[inputMap_it->first].Interaction_HistMap[kRes_Coh_Pion]);
    Interaction_HistMap[k2p2h]->Add(inputMap[inputMap_it->first].Interaction_HistMap[k2p2h]);
    Interaction_HistMap[kDIS]->Add(inputMap[inputMap_it->first].Interaction_HistMap[kDIS]);
    Interaction_HistMap[kInteraction_NONE]->Add(inputMap[inputMap_it->first].Interaction_HistMap[kInteraction_NONE]);
    Interaction_HistMap[kInteraction_OTHER]->Add(inputMap[inputMap_it->first].Interaction_HistMap[kInteraction_OTHER]);

  } // end of loop

    output_hist.h_flux = hist_Flux;
    output_hist.h_Data_Signal = hist_DATA;
    output_hist.h_RECO_Signal = hist_RECO;
    output_hist.h_effNum = hist_numerator;
    output_hist.h_effDom = hist_demonator;
    output_hist.h_Mig = hist_Mig;
    output_hist.Interaction_HistMap = Interaction_HistMap;

    return output_hist;

}//end of function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
CrossSection_Hist Combine_crosssection_Hists_PlaylistMap_includeInteraction_DISbreakdown(ME_playlist_CrossSection_MAP inputMap, ME_helium_Playlists playlist_combine_too ){

  CrossSection_Hist output_hist;
  typename std::map<ME_helium_Playlists, CrossSection_Hist>::const_iterator inputMap_it;

  MnvH1D *hist_Flux=nullptr;
  MnvH1D *hist_DATA=nullptr;
  MnvH1D *hist_RECO=nullptr;
  MnvH1D *hist_RECO_BG=nullptr;
  MnvH1D *hist_numerator=nullptr;
  MnvH1D *hist_demonator=nullptr;
  MnvH2D *hist_Mig=nullptr;
  Interaction_type_MnvH1D_Map Interaction_HistMap;
    if(Debugmode==true) std::cout<< "First hist from playlist: "<< GetPlaylist_InitialName(playlist_combine_too)<< std::endl;
  hist_DATA = inputMap[playlist_combine_too].h_Data_Signal;
  hist_RECO = inputMap[playlist_combine_too].h_RECO_Signal;
  hist_RECO_BG = inputMap[playlist_combine_too].h_RECO_BG;
  hist_numerator = inputMap[playlist_combine_too].h_effNum;
  hist_demonator = inputMap[playlist_combine_too].h_effDom;
  hist_Mig = inputMap[playlist_combine_too].h_Mig;
  hist_Flux= inputMap[playlist_combine_too].h_flux;
  Interaction_HistMap = inputMap[playlist_combine_too].Interaction_HistMap;


  for (inputMap_it = inputMap.begin(); inputMap_it != inputMap.end(); ++inputMap_it){

    if(inputMap_it->first == playlist_combine_too ) continue;
      if(Debugmode==true) std::cout<< " Playlist: "<< GetPlaylist_InitialName(inputMap_it->first)<< std::endl;
    hist_DATA->Add(inputMap_it->second.h_Data_Signal);
    if(Debugmode==true)std::cout<< " FINISHED hist_DATA "<<std::endl;
    hist_RECO->Add(inputMap_it->second.h_RECO_Signal);
    if(Debugmode==true)std::cout<< " FINISHED hist_RECO "<<std::endl;
    hist_RECO_BG->Add(inputMap_it->second.h_RECO_BG);
    if(Debugmode==true)std::cout<< " FINISHED hist_RECO_BG "<<std::endl;
    hist_numerator->Add(inputMap_it->second.h_effNum);
    if(Debugmode==true)std::cout<< " FINISHED hist_numerator "<<std::endl;
    hist_demonator->Add(inputMap_it->second.h_effDom);
    if(Debugmode==true)std::cout<< " FINISHED hist_demonator "<<std::endl;
    hist_Mig->Add(inputMap_it->second.h_Mig);
    if(Debugmode==true)std::cout<< " FINISHED hist_Mig "<<std::endl;
    Interaction_HistMap[kElastic]->Add(inputMap[inputMap_it->first].Interaction_HistMap[kElastic]);
    if(Debugmode==true)std::cout<< " FINISHED Interaction_HistMap[kElastic] "<<std::endl;
    Interaction_HistMap[kHeavierRES]->Add(inputMap[inputMap_it->first].Interaction_HistMap[kHeavierRES]);
    if(Debugmode==true)std::cout<< " FINISHED Interaction_HistMap[kHeavierRES] "<<std::endl;
    Interaction_HistMap[kdeltaRES]->Add(inputMap[inputMap_it->first].Interaction_HistMap[kdeltaRES]);
    if(Debugmode==true)std::cout<< " FINISHED Interaction_HistMap[kdeltaRES] "<<std::endl;
    Interaction_HistMap[k2p2h]->Add(inputMap[inputMap_it->first].Interaction_HistMap[k2p2h]);
    if(Debugmode==true)std::cout<< " FINISHED Interaction_HistMap[k2p2h] "<<std::endl;
    Interaction_HistMap[kDISSIS]->Add(inputMap[inputMap_it->first].Interaction_HistMap[kDISSIS]);
    if(Debugmode==true)std::cout<< " FINISHED Interaction_HistMap[kDISSIS] "<<std::endl;
    Interaction_HistMap[kDISSoft]->Add(inputMap[inputMap_it->first].Interaction_HistMap[kDISSoft]);
    if(Debugmode==true)std::cout<< " FINISHED Interaction_HistMap[kDISSoft] "<<std::endl;
    Interaction_HistMap[kDISHard]->Add(inputMap[inputMap_it->first].Interaction_HistMap[kDISHard]);
    if(Debugmode==true)std::cout<< " FINISHED Interaction_HistMap[kDISHard] "<<std::endl;

    Interaction_HistMap[kInteraction_NONE]->Add(inputMap[inputMap_it->first].Interaction_HistMap[kInteraction_NONE]);
        if(Debugmode==true)std::cout<< " FINISHED Interaction_HistMap[kInteraction_NONE] "<<std::endl;
    Interaction_HistMap[kInteraction_OTHER]->Add(inputMap[inputMap_it->first].Interaction_HistMap[kInteraction_OTHER]);

    if(Debugmode==true)std::cout<< " FINISHED Interaction_HistMap[kInteraction_OTHER] "<<std::endl;

  } // end of loop

    output_hist.h_flux = hist_Flux;
    output_hist.h_Data_Signal = hist_DATA;
    output_hist.h_RECO_Signal = hist_RECO;
    output_hist.h_RECO_BG = hist_RECO_BG;
    output_hist.h_effNum = hist_numerator;
    output_hist.h_effDom = hist_demonator;
    output_hist.h_Mig = hist_Mig;
    output_hist.Interaction_HistMap = Interaction_HistMap;

    return output_hist;

}//end of function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
CrossSection_Hist Combine_crosssection_Hists_PlaylistMap_includeInteraction_DISbreakdown_noBG(ME_playlist_CrossSection_MAP inputMap, ME_helium_Playlists playlist_combine_too ){

  CrossSection_Hist output_hist;
  typename std::map<ME_helium_Playlists, CrossSection_Hist>::const_iterator inputMap_it;

  MnvH1D *hist_Flux=nullptr;
  MnvH1D *hist_DATA=nullptr;
  MnvH1D *hist_RECO=nullptr;
  MnvH1D *hist_numerator=nullptr;
  MnvH1D *hist_demonator=nullptr;
  MnvH2D *hist_Mig=nullptr;
  Interaction_type_MnvH1D_Map Interaction_HistMap;
    if(Debugmode==true) std::cout<< "First hist from playlist: "<< GetPlaylist_InitialName(playlist_combine_too)<< std::endl;
  hist_DATA = inputMap[playlist_combine_too].h_Data_Signal;
  hist_RECO = inputMap[playlist_combine_too].h_RECO_Signal;
  hist_numerator = inputMap[playlist_combine_too].h_effNum;
  hist_demonator = inputMap[playlist_combine_too].h_effDom;
  hist_Mig = inputMap[playlist_combine_too].h_Mig;
  hist_Flux= inputMap[playlist_combine_too].h_flux;
  Interaction_HistMap = inputMap[playlist_combine_too].Interaction_HistMap;


  for (inputMap_it = inputMap.begin(); inputMap_it != inputMap.end(); ++inputMap_it){

    if(inputMap_it->first == playlist_combine_too ) continue;
      if(Debugmode==true) std::cout<< " Playlist: "<< GetPlaylist_InitialName(inputMap_it->first)<< std::endl;
    hist_DATA->Add(inputMap_it->second.h_Data_Signal);
    if(Debugmode==true) std::cout<<"added : hist_DATA "<<std::endl;
    hist_RECO->Add(inputMap_it->second.h_RECO_Signal);
    if(Debugmode==true) std::cout<<"added : hist_RECO "<<std::endl;
    hist_numerator->Add(inputMap_it->second.h_effNum);
    if(Debugmode==true) std::cout<<"added : hist_numerator "<<std::endl;
    hist_demonator->Add(inputMap_it->second.h_effDom);
    if(Debugmode==true) std::cout<<"added : hist_demonator "<<std::endl;
    hist_Mig->Add(inputMap_it->second.h_Mig);
    if(Debugmode==true) std::cout<<"added : hist_Mig "<<std::endl;
        if(Debugmode==true) std::cout<<"added : Interaction hists "<<std::endl;
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
    output_hist.h_RECO_Signal = hist_RECO;
    output_hist.h_effNum = hist_numerator;
    output_hist.h_effDom = hist_demonator;
    output_hist.h_Mig = hist_Mig;
    output_hist.Interaction_HistMap = Interaction_HistMap;

    return output_hist;

}//end of function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
CrossSection_Hist Combine_crosssection_Hists_PlaylistMap_includeInteraction_DISbreakdown_WithMaterial(ME_playlist_CrossSection_MAP inputMap, ME_helium_Playlists playlist_combine_too ){

  CrossSection_Hist output_hist;
  typename std::map<ME_helium_Playlists, CrossSection_Hist>::const_iterator inputMap_it;

  MnvH1D *hist_Flux=nullptr;
  MnvH1D *hist_DATA=nullptr;
  MnvH1D *hist_RECO=nullptr;
  MnvH1D *hist_RECO_BG=nullptr;
  MnvH1D *hist_numerator=nullptr;
  MnvH1D *hist_demonator=nullptr;
  MnvH2D *hist_Mig=nullptr;
  Interaction_type_MnvH1D_Map Interaction_HistMap;
  Material_type_MnvH1D_Map Material_Hist_Map;
    if(Debugmode==true) std::cout<< "First hist from playlist: "<< GetPlaylist_InitialName(playlist_combine_too)<< std::endl;
  hist_DATA = inputMap[playlist_combine_too].h_Data_Signal;
  hist_RECO = inputMap[playlist_combine_too].h_RECO_Signal;
  hist_RECO_BG = inputMap[playlist_combine_too].h_RECO_BG;
  hist_numerator = inputMap[playlist_combine_too].h_effNum;
  hist_demonator = inputMap[playlist_combine_too].h_effDom;
  hist_Mig = inputMap[playlist_combine_too].h_Mig;
  hist_Flux= inputMap[playlist_combine_too].h_flux;
  Interaction_HistMap = inputMap[playlist_combine_too].Interaction_HistMap;
  Material_Hist_Map = inputMap[playlist_combine_too].Material_HistMap_RECO;

  for (inputMap_it = inputMap.begin(); inputMap_it != inputMap.end(); ++inputMap_it){

    if(inputMap_it->first == playlist_combine_too ) continue;
std::cout<< " Playlist: "<< GetPlaylist_InitialName(inputMap_it->first)<< std::endl;
    hist_DATA->Add(inputMap_it->second.h_Data_Signal);
    hist_RECO->Add(inputMap_it->second.h_RECO_Signal);
    hist_RECO_BG->Add(inputMap_it->second.h_RECO_BG);
    hist_numerator->Add(inputMap_it->second.h_effNum);
    hist_demonator->Add(inputMap_it->second.h_effDom);
    hist_Mig->Add(inputMap_it->second.h_Mig);
    Interaction_HistMap[kElastic]->Add(inputMap[inputMap_it->first].Interaction_HistMap[kElastic]);
    Interaction_HistMap[kHeavierRES]->Add(inputMap[inputMap_it->first].Interaction_HistMap[kHeavierRES]);
    Interaction_HistMap[kdeltaRES]->Add(inputMap[inputMap_it->first].Interaction_HistMap[kdeltaRES]);
    Interaction_HistMap[k2p2h]->Add(inputMap[inputMap_it->first].Interaction_HistMap[k2p2h]);
    Interaction_HistMap[kDISSIS]->Add(inputMap[inputMap_it->first].Interaction_HistMap[kDISSIS]);
    Interaction_HistMap[kDISSoft]->Add(inputMap[inputMap_it->first].Interaction_HistMap[kDISSoft]);
    Interaction_HistMap[kDISHard]->Add(inputMap[inputMap_it->first].Interaction_HistMap[kDISHard]);

    Interaction_HistMap[kInteraction_NONE]->Add(inputMap[inputMap_it->first].Interaction_HistMap[kInteraction_NONE]);
    Interaction_HistMap[kInteraction_OTHER]->Add(inputMap[inputMap_it->first].Interaction_HistMap[kInteraction_OTHER]);

    Material_Hist_Map[kIron]->Add(inputMap[inputMap_it->first].Material_HistMap_RECO[kIron]);
    Material_Hist_Map[kHelium]->Add(inputMap[inputMap_it->first].Material_HistMap_RECO[kHelium]);
    Material_Hist_Map[kCarbon]->Add(inputMap[inputMap_it->first].Material_HistMap_RECO[kCarbon]);
    Material_Hist_Map[kLead]->Add(inputMap[inputMap_it->first].Material_HistMap_RECO[kLead]);
    Material_Hist_Map[kAluminium]->Add(inputMap[inputMap_it->first].Material_HistMap_RECO[kAluminium]);
    Material_Hist_Map[kMaterial_OTHER]->Add(inputMap[inputMap_it->first].Material_HistMap_RECO[kMaterial_OTHER]);

  } // end of loop

    output_hist.h_flux = hist_Flux;
    output_hist.h_Data_Signal = hist_DATA;
    output_hist.h_RECO_Signal = hist_RECO;
    output_hist.h_RECO_BG = hist_RECO_BG;
    output_hist.h_effNum = hist_numerator;
    output_hist.h_effDom = hist_demonator;
    output_hist.h_Mig = hist_Mig;
    output_hist.Interaction_HistMap = Interaction_HistMap;
    output_hist.Material_HistMap_RECO = Material_Hist_Map;

    return output_hist;

}//end of function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
CrossSection_Hist Combine_crosssection_Hists_PlaylistMap_noFlux_mig_BG(ME_playlist_CrossSection_MAP inputMap, ME_helium_Playlists playlist_combine_too ){
if(Debugmode==true) std::cout<< "INSIDE::Combine_crosssection_Hists_PlaylistMap_noFlux_mig_BG"<<::std::endl;
  CrossSection_Hist output_hist;
  typename std::map<ME_helium_Playlists, CrossSection_Hist>::const_iterator inputMap_it;

  MnvH1D *hist_DATA=nullptr;
  MnvH1D *hist_RECO=nullptr;
  MnvH1D *hist_numerator=nullptr;
  MnvH1D *hist_demonator=nullptr;

    if(Debugmode==true) std::cout<< "First hist from playlist: "<< GetPlaylist_InitialName(playlist_combine_too)<< std::endl;
  hist_DATA = inputMap[playlist_combine_too].h_Data_Signal;
  hist_RECO = inputMap[playlist_combine_too].h_RECO_Signal;
  hist_numerator = inputMap[playlist_combine_too].h_effNum;
  hist_demonator = inputMap[playlist_combine_too].h_effDom;


  for (inputMap_it = inputMap.begin(); inputMap_it != inputMap.end(); ++inputMap_it){

    if(inputMap_it->first == playlist_combine_too ) continue;
      if(Debugmode==true) std::cout<< " Playlist: "<< GetPlaylist_InitialName(inputMap_it->first)<< std::endl;
    hist_DATA->Add(inputMap_it->second.h_Data_Signal);
    if(Debugmode==true) std::cout<< "Finished: hist_DATA"<<std::endl;
    hist_RECO->Add(inputMap_it->second.h_RECO_Signal);
    if(Debugmode==true) std::cout<< "Finished: hist_RECO"<<std::endl;
    hist_numerator->Add(inputMap_it->second.h_effNum);
    if(Debugmode==true) std::cout<< "Finished: hist_numerator"<<std::endl;
    hist_demonator->Add(inputMap_it->second.h_effDom);
    if(Debugmode==true) std::cout<< "Finished: hist_demonator"<<std::endl;

  } // end of loop


    output_hist.h_Data_Signal = hist_DATA;
    output_hist.h_RECO_Signal = hist_RECO;
    output_hist.h_effNum = hist_numerator;
    output_hist.h_effDom = hist_demonator;


    return output_hist;

}//end of function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void AddCrossSectionHis_noFlux(CrossSection_Hist &AddTo, CrossSection_Hist input){

AddTo.h_Data_Signal->Add(input.h_Data_Signal);
AddTo.h_RECO_Signal->Add(input.h_RECO_Signal);
AddTo.h_RECO_BG->Add(input.h_RECO_BG);
AddTo.h_effNum->Add(input.h_effNum);
AddTo.h_effDom->Add(input.h_effDom);
AddTo.h_Mig->Add(input.h_Mig);

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

void ApplyBGSubtraction_todata_CrossSection(CrossSection_Hist &input){
input.h_Data_Signal->Add(input.h_RECO_BG,-1);
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void ApplyBGSubtraction_toRECO_CrossSection(CrossSection_Hist &input){
input.h_RECO_Signal->Add(input.h_RECO_BG,-1);
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

void ApplyBGSubtraction_todata_CrossSection(CrossSection2D_Hist &input){
input.h_Data_Signal->Add(input.h_RECO_BG,-1);
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void ApplyBGSubtraction_toRECO_CrossSection(CrossSection2D_Hist &input){
input.h_RECO->Add(input.h_RECO_BG,-1);
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void AddMissingErrorBands_todata_CrossSection(CrossSection2D_Hist &input){
input.h_Data_Signal->AddMissingErrorBandsAndFillWithCV(*input.h_RECO_BG);
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void AddMissingErrorBands_todata_CrossSection(CrossSection_Hist &input){
input.h_Data_Signal->AddMissingErrorBandsAndFillWithCV(*input.h_RECO_BG);
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

void AddCrossSectionHist_Daisy_noFlux(CrossSection_Hist_Daisy &AddTo, CrossSection_Hist_Daisy input){

  AddCrossSectionHis_noFlux(AddTo.Daisy0 , input.Daisy0);
  AddCrossSectionHis_noFlux(AddTo.Daisy1 , input.Daisy1);
  AddCrossSectionHis_noFlux(AddTo.Daisy2 , input.Daisy2);
  AddCrossSectionHis_noFlux(AddTo.Daisy3 , input.Daisy3);
  AddCrossSectionHis_noFlux(AddTo.Daisy4 , input.Daisy4);
  AddCrossSectionHis_noFlux(AddTo.Daisy5 , input.Daisy5);
  AddCrossSectionHis_noFlux(AddTo.Daisy6 , input.Daisy6);
  AddCrossSectionHis_noFlux(AddTo.Daisy7 , input.Daisy7);
  AddCrossSectionHis_noFlux(AddTo.Daisy8 , input.Daisy8);
  AddCrossSectionHis_noFlux(AddTo.Daisy9 , input.Daisy9);
  AddCrossSectionHis_noFlux(AddTo.Daisy10 , input.Daisy10);
  AddCrossSectionHis_noFlux(AddTo.Daisy11 , input.Daisy11);
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void ApplyBGSubtraction_todata_CrossSection_Daisy(CrossSection_Hist_Daisy &input){

  ApplyBGSubtraction_todata_CrossSection(input.Daisy0 );
  ApplyBGSubtraction_todata_CrossSection(input.Daisy1 );
  ApplyBGSubtraction_todata_CrossSection(input.Daisy2 );
  ApplyBGSubtraction_todata_CrossSection(input.Daisy3 );
  ApplyBGSubtraction_todata_CrossSection(input.Daisy4 );
  ApplyBGSubtraction_todata_CrossSection(input.Daisy5 );
  ApplyBGSubtraction_todata_CrossSection(input.Daisy6 );
  ApplyBGSubtraction_todata_CrossSection(input.Daisy7 );
  ApplyBGSubtraction_todata_CrossSection(input.Daisy8 );
  ApplyBGSubtraction_todata_CrossSection(input.Daisy9 );
  ApplyBGSubtraction_todata_CrossSection(input.Daisy10);
  ApplyBGSubtraction_todata_CrossSection(input.Daisy11);
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void ApplyBGSubtraction_toRECO_CrossSection_Daisy(CrossSection_Hist_Daisy &input){

  ApplyBGSubtraction_toRECO_CrossSection(input.Daisy0 );
  ApplyBGSubtraction_toRECO_CrossSection(input.Daisy1 );
  ApplyBGSubtraction_toRECO_CrossSection(input.Daisy2 );
  ApplyBGSubtraction_toRECO_CrossSection(input.Daisy3 );
  ApplyBGSubtraction_toRECO_CrossSection(input.Daisy4 );
  ApplyBGSubtraction_toRECO_CrossSection(input.Daisy5 );
  ApplyBGSubtraction_toRECO_CrossSection(input.Daisy6 );
  ApplyBGSubtraction_toRECO_CrossSection(input.Daisy7 );
  ApplyBGSubtraction_toRECO_CrossSection(input.Daisy8 );
  ApplyBGSubtraction_toRECO_CrossSection(input.Daisy9 );
  ApplyBGSubtraction_toRECO_CrossSection(input.Daisy10);
  ApplyBGSubtraction_toRECO_CrossSection(input.Daisy11);
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void ApplyBGSubtraction_todata_CrossSection_Daisy(CrossSection2D_Hist_Daisy &input){

  ApplyBGSubtraction_todata_CrossSection(input.Daisy0 );
  ApplyBGSubtraction_todata_CrossSection(input.Daisy1 );
  ApplyBGSubtraction_todata_CrossSection(input.Daisy2 );
  ApplyBGSubtraction_todata_CrossSection(input.Daisy3 );
  ApplyBGSubtraction_todata_CrossSection(input.Daisy4 );
  ApplyBGSubtraction_todata_CrossSection(input.Daisy5 );
  ApplyBGSubtraction_todata_CrossSection(input.Daisy6 );
  ApplyBGSubtraction_todata_CrossSection(input.Daisy7 );
  ApplyBGSubtraction_todata_CrossSection(input.Daisy8 );
  ApplyBGSubtraction_todata_CrossSection(input.Daisy9 );
  ApplyBGSubtraction_todata_CrossSection(input.Daisy10);
  ApplyBGSubtraction_todata_CrossSection(input.Daisy11);
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void ApplyBGSubtraction_toRECO_CrossSection_Daisy(CrossSection2D_Hist_Daisy &input){

  ApplyBGSubtraction_toRECO_CrossSection(input.Daisy0 );
  ApplyBGSubtraction_toRECO_CrossSection(input.Daisy1 );
  ApplyBGSubtraction_toRECO_CrossSection(input.Daisy2 );
  ApplyBGSubtraction_toRECO_CrossSection(input.Daisy3 );
  ApplyBGSubtraction_toRECO_CrossSection(input.Daisy4 );
  ApplyBGSubtraction_toRECO_CrossSection(input.Daisy5 );
  ApplyBGSubtraction_toRECO_CrossSection(input.Daisy6 );
  ApplyBGSubtraction_toRECO_CrossSection(input.Daisy7 );
  ApplyBGSubtraction_toRECO_CrossSection(input.Daisy8 );
  ApplyBGSubtraction_toRECO_CrossSection(input.Daisy9 );
  ApplyBGSubtraction_toRECO_CrossSection(input.Daisy10);
  ApplyBGSubtraction_toRECO_CrossSection(input.Daisy11);
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void AddMissingErrorBandsAndFillWithCV_toData_ForDaisy(CrossSection_Hist_Daisy &input){

  AddMissingErrorBands_todata_CrossSection(input.Daisy0 );
  AddMissingErrorBands_todata_CrossSection(input.Daisy1 );
  AddMissingErrorBands_todata_CrossSection(input.Daisy2 );
  AddMissingErrorBands_todata_CrossSection(input.Daisy3 );
  AddMissingErrorBands_todata_CrossSection(input.Daisy4 );
  AddMissingErrorBands_todata_CrossSection(input.Daisy5 );
  AddMissingErrorBands_todata_CrossSection(input.Daisy6 );
  AddMissingErrorBands_todata_CrossSection(input.Daisy7 );
  AddMissingErrorBands_todata_CrossSection(input.Daisy8 );
  AddMissingErrorBands_todata_CrossSection(input.Daisy9 );
  AddMissingErrorBands_todata_CrossSection(input.Daisy10);
  AddMissingErrorBands_todata_CrossSection(input.Daisy11);

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void AddMissingErrorBandsAndFillWithCV_toData_ForDaisy(CrossSection2D_Hist_Daisy &input){

  AddMissingErrorBands_todata_CrossSection(input.Daisy0 );
  AddMissingErrorBands_todata_CrossSection(input.Daisy1 );
  AddMissingErrorBands_todata_CrossSection(input.Daisy2 );
  AddMissingErrorBands_todata_CrossSection(input.Daisy3 );
  AddMissingErrorBands_todata_CrossSection(input.Daisy4 );
  AddMissingErrorBands_todata_CrossSection(input.Daisy5 );
  AddMissingErrorBands_todata_CrossSection(input.Daisy6 );
  AddMissingErrorBands_todata_CrossSection(input.Daisy7 );
  AddMissingErrorBands_todata_CrossSection(input.Daisy8 );
  AddMissingErrorBands_todata_CrossSection(input.Daisy9 );
  AddMissingErrorBands_todata_CrossSection(input.Daisy10);
  AddMissingErrorBands_todata_CrossSection(input.Daisy11);

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
CrossSection_Hist_Daisy Combine_crosssection_Hists_PlaylistMap_Daisy(ME_playlist_CrossSection_MAP_DAISY inputMap, ME_helium_Playlists playlist_combine_too ){

  CrossSection_Hist_Daisy output_hist;
  typename std::map<ME_helium_Playlists, CrossSection_Hist_Daisy>::const_iterator inputMap_it;

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


TransWarp_Hist Combine_TranWarp_Hists_PlaylistMap(ME_playlist_TransWarp_Hist_Map inputMap,
  ME_helium_Playlists playlist_combine_too ){

if(Debugmode==true)std::cout<<"inside :Combine_TranWarp_Hists_PlaylistMap"<< std::endl;
  TransWarp_Hist output_hist;

  typename std::map<ME_helium_Playlists, TransWarp_Hist>::const_iterator inputMap_it;

  MnvH1D *h_mc_reco =nullptr;
  MnvH1D *h_mc_truth =nullptr;
  MnvH1D *h_data_reco =nullptr;
  MnvH1D *h_data_truth =nullptr;
  MnvH2D *h_Mig =nullptr;

  if(Debugmode==true) std::cout<< "Starting hist from playlist to Combined too : "<< GetPlaylist_InitialName(playlist_combine_too)<< std::endl;

  h_mc_reco    = inputMap[playlist_combine_too].mc_reco;
  h_mc_truth   = inputMap[playlist_combine_too].mc_truth;
  h_data_reco  = inputMap[playlist_combine_too].data_reco;
  h_data_truth = inputMap[playlist_combine_too].data_truth;
  h_Mig        = inputMap[playlist_combine_too].h_Mig;


  for (inputMap_it = inputMap.begin(); inputMap_it != inputMap.end(); ++inputMap_it){

    if(inputMap_it->first == playlist_combine_too ) continue;

    if(Debugmode==true) std::cout<< "Trying  Playlist: "<< GetPlaylist_InitialName(inputMap_it->first)<< std::endl;

    if(Debugmode==true)std::cout<<"Adding MC_reco"<<std::endl;
    h_mc_reco->Add(inputMap_it->second.mc_reco);
    if(Debugmode==true)std::cout<<"Adding mc_truth"<<std::endl;
    h_mc_truth->Add(inputMap_it->second.mc_truth);
    if(Debugmode==true)std::cout<<"Adding data_reco"<<std::endl;
    h_data_reco->Add(inputMap_it->second.data_reco);
    if(Debugmode==true)std::cout<<"Adding data_truth"<<std::endl;
    h_data_truth->Add(inputMap_it->second.data_truth);
    if(Debugmode==true)std::cout<<"Adding h_Mig"<<std::endl;
    h_Mig->Add(inputMap_it->second.h_Mig);

  } // end of loop

    output_hist.h_Mig = h_Mig;
    output_hist.mc_reco = h_mc_reco;
    output_hist.mc_truth = h_mc_truth;
    output_hist.data_reco = h_data_reco;
    output_hist.data_truth = h_data_truth;

    return output_hist;

}//end of function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

TransWarp_2DHist Combine_TranWarp_2DHists_PlaylistMap(ME_playlist_TransWarp_2DHist_Map inputMap,
   ME_helium_Playlists playlist_combine_too ){

if(Debugmode==true)std::cout<<"inside :Combine_TranWarp_2DHists_PlaylistMap"<< std::endl;
  TransWarp_2DHist output_hist;

  typename std::map<ME_helium_Playlists, TransWarp_2DHist>::const_iterator inputMap_it;

  MnvH2D *h_mc_reco =nullptr;
  MnvH2D *h_mc_truth =nullptr;
  MnvH2D *h_data_reco =nullptr;
  MnvH2D *h_data_truth =nullptr;
  MnvH2D *h_Mig =nullptr;

  if(Debugmode==true) std::cout<< "Starting 2Dhist from playlist to Combined too : "<< GetPlaylist_InitialName(playlist_combine_too)<< std::endl;

  h_mc_reco    = inputMap[playlist_combine_too].mc_reco;
  h_mc_truth   = inputMap[playlist_combine_too].mc_truth;
  h_data_reco  = inputMap[playlist_combine_too].data_reco;
  h_data_truth = inputMap[playlist_combine_too].data_truth;
  h_Mig        = inputMap[playlist_combine_too].h_Mig;


  for (inputMap_it = inputMap.begin(); inputMap_it != inputMap.end(); ++inputMap_it){

    if(inputMap_it->first == playlist_combine_too ) continue;

    if(Debugmode==true) std::cout<< "Trying  Playlist: "<< GetPlaylist_InitialName(inputMap_it->first)<< std::endl;

    if(Debugmode==true)std::cout<<"Adding MC_reco"<<std::endl;
    h_mc_reco->Add(inputMap_it->second.mc_reco);
    if(Debugmode==true)std::cout<<"Adding mc_truth"<<std::endl;
    h_mc_truth->Add(inputMap_it->second.mc_truth);
    if(Debugmode==true)std::cout<<"Adding data_reco"<<std::endl;
    h_data_reco->Add(inputMap_it->second.data_reco);
    if(Debugmode==true)std::cout<<"Adding data_truth"<<std::endl;
    h_data_truth->Add(inputMap_it->second.data_truth);
    if(Debugmode==true)std::cout<<"Adding h_Mig"<<std::endl;
    h_Mig->Add(inputMap_it->second.h_Mig);

  } // end of loop

    output_hist.h_Mig = h_Mig;
    output_hist.mc_reco = h_mc_reco;
    output_hist.mc_truth = h_mc_truth;
    output_hist.data_reco = h_data_reco;
    output_hist.data_truth = h_data_truth;

    return output_hist;

}//end of function

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

void WritetoTFile_All(CrossSection_Hist &Constuct_crosssection_Hists, TFile& file, char* Name){

  file.cd(); // write to this Tfile

  char Print_Name[2024];
  sprintf(Print_Name, "%s_FluxIntegrated",Name);
  std::cout<<"writing : "<< Print_Name<<std::endl;
  Constuct_crosssection_Hists.h_flux->Clone()->Write(Print_Name);
  sprintf(Print_Name, "%s_Data_Signal",Name);
  std::cout<<"writing : "<< Print_Name<<std::endl;
  Constuct_crosssection_Hists.h_Data_Signal ->Clone()->Write(Print_Name);
  sprintf(Print_Name, "%s_RECO_Signal",Name);
  std::cout<<"writing : "<< Print_Name<<std::endl;
  Constuct_crosssection_Hists.h_RECO_Signal ->Clone()->Write(Print_Name);
  sprintf(Print_Name, "%s_RECO_BG",Name);
  std::cout<<"writing : "<< Print_Name<<std::endl;
  Constuct_crosssection_Hists.h_RECO_BG ->Clone()->Write(Print_Name);
  sprintf(Print_Name, "%s_effNum",Name);
  std::cout<<"writing : "<< Print_Name<<std::endl;
  Constuct_crosssection_Hists.h_effNum ->Clone()->Write(Print_Name);
  sprintf(Print_Name, "%s_effDom",Name);
  std::cout<<"writing : "<< Print_Name<<std::endl;
  Constuct_crosssection_Hists.h_effDom ->Clone()->Write(Print_Name);


  return;

}//end of function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_All(ME_playlist_CrossSection_MAP &Constuct_crosssection_Map, TFile& file, char* Name){

file.cd(); // write to this Tfile

char Print_Name[2024];

typename std::map<ME_helium_Playlists, CrossSection_Hist>::const_iterator it;

 for (it = Constuct_crosssection_Map.begin(); it != Constuct_crosssection_Map.end(); ++it){

   auto playlist_name = GetPlaylist_InitialName(it->first);

   char playlist_name_char[playlist_name.length()+1];
   strcpy(playlist_name_char,playlist_name.c_str());

   sprintf(Print_Name, "%s_FluxIntegrated_%s",Name,playlist_name_char);
   it->second.h_flux->Clone()->Write(Print_Name);
   sprintf(Print_Name, "%s_Data_Signal_%s",Name,playlist_name_char);
   it->second.h_Data_Signal ->Clone()->Write(Print_Name);
   sprintf(Print_Name, "%s_RECO_Signal_%s",Name,playlist_name_char);
   it->second.h_RECO_Signal ->Clone()->Write(Print_Name);
   sprintf(Print_Name, "%s_effNum_%s",Name,playlist_name_char);
   it->second.h_effNum ->Clone()->Write(Print_Name);
   sprintf(Print_Name, "%s_effDom_%s",Name,playlist_name_char);
   it->second.h_effDom ->Clone()->Write(Print_Name);
   sprintf(Print_Name, "%s_Mig_%s",Name,playlist_name_char);
   it->second.h_Mig ->Clone()->Write(Print_Name);

 }

 return;


}//end of function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_main(CrossSection_Hist &Constuct_crosssection_Hists, TFile& file, char* Name){

file.cd(); // write to this Tfile

char Print_Name[2024];

sprintf(Print_Name, "%s_Data_Signal",Name);
Constuct_crosssection_Hists.h_Data_Signal ->Clone()->Write(Print_Name);
sprintf(Print_Name, "%s_RECO_Signal",Name);
Constuct_crosssection_Hists.h_RECO_Signal ->Clone()->Write(Print_Name);
sprintf(Print_Name, "%s_RECO_BG",Name);
Constuct_crosssection_Hists.h_RECO_BG ->Clone()->Write(Print_Name);
sprintf(Print_Name, "%s_effNum",Name);
Constuct_crosssection_Hists.h_effNum ->Clone()->Write(Print_Name);
sprintf(Print_Name, "%s_effDom",Name);
Constuct_crosssection_Hists.h_effDom ->Clone()->Write(Print_Name);

return;

}//end of function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_Interaction(CrossSection_Hist &Constuct_crosssection_Hists, TFile& file, char* Name){

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
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

void WritetoTFile_Interaction_DISbreakdown(CrossSection_Hist &Constuct_crosssection_Hists, TFile& file, char* Name){

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
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

void WritetoTFile_NormTRUECrossSection(CrossSection_Hist &Constuct_crosssection_Hists, TFile& file, char* Name, const double nNucleons, const double POT){

 file.cd(); // write to this Tfile

 char Print_Name[2024];
 sprintf(Print_Name, "%s",Name);
 MnvH1D *True_CrossSection = (MnvH1D*)Constuct_crosssection_Hists.h_effDom->Clone(Print_Name);
 MnvH1D *fluxIntegral = (MnvH1D*)Constuct_crosssection_Hists.h_flux->Clone("fluxIntegral");
 fluxIntegral->AddMissingErrorBandsAndFillWithCV(*True_CrossSection);
 //True_CrossSection->Scale(1., "width"); //are you supposed to binwidth before ?
 //fluxIntegral->Scale(1., "width");
 True_CrossSection->Divide(True_CrossSection, fluxIntegral);
 True_CrossSection->Scale(1./nNucleons/POT);
 std::cout<<"POT = "<< POT<<std::endl;
 std::cout<<"nNucleons = "<< nNucleons<<std::endl;
 True_CrossSection->Scale(1.e4); //Flux histogram is in m^-2, but convention is to report cm^2
 True_CrossSection->Scale(1., "width");

 //True_CrossSection->Scale(PotNorm_MC_TO_Data);
 True_CrossSection->Clone()->Write(Print_Name);

}//end of function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

void WritetoTFile_NormTRUECrossSection_Interaction(CrossSection_Hist &Constuct_crosssection_Hists, TFile& file, char* Name, const double nNucleons, const double POT){

 file.cd(); // write to this Tfile
 MnvH1D *fluxIntegral = (MnvH1D*)Constuct_crosssection_Hists.h_flux->Clone("fluxIntegral");
 fluxIntegral->AddMissingErrorBandsAndFillWithCV(*Constuct_crosssection_Hists.Interaction_HistMap[kElastic]);
 char Print_Name[2024];
 sprintf(Print_Name, "%s_CrossSection_Interaction_Elastic",Name);
  MnvH1D *True_CrossSection_Elastic = (MnvH1D*)Constuct_crosssection_Hists.Interaction_HistMap[kElastic]->Clone(Print_Name);
  True_CrossSection_Elastic->Divide(True_CrossSection_Elastic, fluxIntegral);
  True_CrossSection_Elastic->Scale(1./nNucleons/POT);
  True_CrossSection_Elastic->Scale(1.e4); //Flux histogram is in m^-2, but convention is to report cm^2
  True_CrossSection_Elastic->Scale(1., "width");
  True_CrossSection_Elastic->Clone()->Write(Print_Name);

 sprintf(Print_Name, "%s_CrossSection_Interaction_1Pion",Name);
  MnvH1D *True_CrossSection_res_coh_pion = (MnvH1D*)Constuct_crosssection_Hists.Interaction_HistMap[kRes_Coh_Pion]->Clone(Print_Name);
  True_CrossSection_res_coh_pion->Divide(True_CrossSection_res_coh_pion, fluxIntegral);
  True_CrossSection_res_coh_pion->Scale(1./nNucleons/POT);
  True_CrossSection_res_coh_pion->Scale(1.e4); //Flux histogram is in m^-2, but convention is to report cm^2
  True_CrossSection_res_coh_pion->Scale(1., "width");
  True_CrossSection_res_coh_pion->Clone()->Write(Print_Name);
 sprintf(Print_Name, "%s_CrossSection_Interaction_2p2h",Name);
  MnvH1D *True_CrossSection_2p2h = (MnvH1D*)Constuct_crosssection_Hists.Interaction_HistMap[k2p2h]->Clone(Print_Name);
  True_CrossSection_2p2h->Divide(True_CrossSection_2p2h, fluxIntegral);
  True_CrossSection_2p2h->Scale(1./nNucleons/POT);
  True_CrossSection_2p2h->Scale(1.e4); //Flux histogram is in m^-2, but convention is to report cm^2
  True_CrossSection_2p2h->Scale(1., "width");
  True_CrossSection_2p2h->Clone()->Write(Print_Name);


 sprintf(Print_Name, "%s_CrossSection_Interaction_DIS",Name);
  MnvH1D *True_CrossSection_DIS = (MnvH1D*)Constuct_crosssection_Hists.Interaction_HistMap[kDIS]->Clone(Print_Name);

  True_CrossSection_DIS->Divide(True_CrossSection_DIS, fluxIntegral);
  True_CrossSection_DIS->Scale(1./nNucleons/POT);
  True_CrossSection_DIS->Scale(1.e4); //Flux histogram is in m^-2, but convention is to report cm^2
  True_CrossSection_DIS->Scale(1., "width");
  True_CrossSection_DIS->Clone()->Write(Print_Name);

 sprintf(Print_Name, "%s_CrossSection_Interaction_None",Name);
  MnvH1D *True_CrossSection_None = (MnvH1D*)Constuct_crosssection_Hists.Interaction_HistMap[kInteraction_NONE]->Clone(Print_Name);

  True_CrossSection_None->Divide(True_CrossSection_None, fluxIntegral);
  True_CrossSection_None->Scale(1./nNucleons/POT);
  True_CrossSection_None->Scale(1.e4); //Flux histogram is in m^-2, but convention is to report cm^2
  True_CrossSection_None->Scale(1., "width");
  True_CrossSection_None->Clone()->Write(Print_Name);


 sprintf(Print_Name, "%s_CrossSection_Interaction_Other",Name);
  MnvH1D *True_CrossSection_other = (MnvH1D*)Constuct_crosssection_Hists.Interaction_HistMap[kInteraction_OTHER]->Clone(Print_Name);

  True_CrossSection_other->Divide(True_CrossSection_other, fluxIntegral);
  True_CrossSection_other->Scale(1./nNucleons/POT);
  True_CrossSection_other->Scale(1.e4); //Flux histogram is in m^-2, but convention is to report cm^2
  True_CrossSection_other->Scale(1., "width");
  True_CrossSection_other->Clone()->Write(Print_Name);

}//end of function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

void WritetoTFile_NormTRUECrossSection_Interaction_DISbreakdown(CrossSection_Hist &Constuct_crosssection_Hists, TFile& file, char* Name, const double nNucleons, const double POT){

 file.cd(); // write to this Tfile
 MnvH1D *fluxIntegral = (MnvH1D*)Constuct_crosssection_Hists.h_flux->Clone("fluxIntegral");
 fluxIntegral->AddMissingErrorBandsAndFillWithCV(*Constuct_crosssection_Hists.Interaction_HistMap[kElastic]);
 char Print_Name[2024];

 sprintf(Print_Name, "%s_CrossSection_Interaction_QE",Name);
  MnvH1D *True_CrossSection_Elastic = (MnvH1D*)Constuct_crosssection_Hists.Interaction_HistMap[kElastic]->Clone(Print_Name);
  True_CrossSection_Elastic->Divide(True_CrossSection_Elastic, fluxIntegral);
  True_CrossSection_Elastic->Scale(1./nNucleons/POT);
  True_CrossSection_Elastic->Scale(1.e4); //Flux histogram is in m^-2, but convention is to report cm^2
  True_CrossSection_Elastic->Scale(1., "width");
  True_CrossSection_Elastic->Clone()->Write(Print_Name);

//cstd::cout<<"True_CrossSection_Elastic title = " <<  True_CrossSection_Elastic->GetTitle(); << std::endl;

 sprintf(Print_Name, "%s_CrossSection_Interaction_#DeltaRes",Name);
  MnvH1D *True_CrossSection_DeltaRES = (MnvH1D*)Constuct_crosssection_Hists.Interaction_HistMap[kdeltaRES]->Clone(Print_Name);
  True_CrossSection_DeltaRES->Divide(True_CrossSection_DeltaRES, fluxIntegral);
  True_CrossSection_DeltaRES->Scale(1./nNucleons/POT);
  True_CrossSection_DeltaRES->Scale(1.e4); //Flux histogram is in m^-2, but convention is to report cm^2
  True_CrossSection_DeltaRES->Scale(1., "width");
  True_CrossSection_DeltaRES->Clone()->Write(Print_Name);

  sprintf(Print_Name, "%s_CrossSection_Interaction_HeavierRes",Name);
   MnvH1D *True_CrossSection_HeavierRes = (MnvH1D*)Constuct_crosssection_Hists.Interaction_HistMap[kHeavierRES]->Clone(Print_Name);
   True_CrossSection_HeavierRes->Divide(True_CrossSection_HeavierRes, fluxIntegral);
   True_CrossSection_HeavierRes->Scale(1./nNucleons/POT);
   True_CrossSection_HeavierRes->Scale(1.e4); //Flux histogram is in m^-2, but convention is to report cm^2
   True_CrossSection_HeavierRes->Scale(1., "width");
   True_CrossSection_HeavierRes->Clone()->Write(Print_Name);

 sprintf(Print_Name, "%s_CrossSection_Interaction_2p2h",Name);
  MnvH1D *True_CrossSection_2p2h = (MnvH1D*)Constuct_crosssection_Hists.Interaction_HistMap[k2p2h]->Clone(Print_Name);
  True_CrossSection_2p2h->Divide(True_CrossSection_2p2h, fluxIntegral);
  True_CrossSection_2p2h->Scale(1./nNucleons/POT);
  True_CrossSection_2p2h->Scale(1.e4); //Flux histogram is in m^-2, but convention is to report cm^2
  True_CrossSection_2p2h->Scale(1., "width");
  True_CrossSection_2p2h->Clone()->Write(Print_Name);


 sprintf(Print_Name, "%s_CrossSection_Interaction_DISSIS",Name);
  MnvH1D *True_CrossSection_DISSIS = (MnvH1D*)Constuct_crosssection_Hists.Interaction_HistMap[kDISSIS]->Clone(Print_Name);
  True_CrossSection_DISSIS->Divide(True_CrossSection_DISSIS, fluxIntegral);
  True_CrossSection_DISSIS->Scale(1./nNucleons/POT);
  True_CrossSection_DISSIS->Scale(1.e4); //Flux histogram is in m^-2, but convention is to report cm^2
  True_CrossSection_DISSIS->Scale(1., "width");
  True_CrossSection_DISSIS->Clone()->Write(Print_Name);

  sprintf(Print_Name, "%s_CrossSection_Interaction_DISSoft",Name);
   MnvH1D *True_CrossSection_DISSoft = (MnvH1D*)Constuct_crosssection_Hists.Interaction_HistMap[kDISSoft]->Clone(Print_Name);
   True_CrossSection_DISSoft->Divide(True_CrossSection_DISSoft, fluxIntegral);
   True_CrossSection_DISSoft->Scale(1./nNucleons/POT);
   True_CrossSection_DISSoft->Scale(1.e4); //Flux histogram is in m^-2, but convention is to report cm^2
   True_CrossSection_DISSoft->Scale(1., "width");
   True_CrossSection_DISSoft->Clone()->Write(Print_Name);

  sprintf(Print_Name, "%s_CrossSection_Interaction_DISHard",Name);
   MnvH1D *True_CrossSection_DISHard = (MnvH1D*)Constuct_crosssection_Hists.Interaction_HistMap[kDISHard]->Clone(Print_Name);
   True_CrossSection_DISHard->Divide(True_CrossSection_DISHard, fluxIntegral);
   True_CrossSection_DISHard->Scale(1./nNucleons/POT);
   True_CrossSection_DISHard->Scale(1.e4); //Flux histogram is in m^-2, but convention is to report cm^2
   True_CrossSection_DISHard->Scale(1., "width");
   True_CrossSection_DISHard->Clone()->Write(Print_Name);


 sprintf(Print_Name, "%s_CrossSection_Interaction_None",Name);
  MnvH1D *True_CrossSection_None = (MnvH1D*)Constuct_crosssection_Hists.Interaction_HistMap[kInteraction_NONE]->Clone(Print_Name);

  True_CrossSection_None->Divide(True_CrossSection_None, fluxIntegral);
  True_CrossSection_None->Scale(1./nNucleons/POT);
  True_CrossSection_None->Scale(1.e4); //Flux histogram is in m^-2, but convention is to report cm^2
  True_CrossSection_None->Scale(1., "width");
  True_CrossSection_None->Clone()->Write(Print_Name);


 sprintf(Print_Name, "%s_CrossSection_Interaction_Other",Name);
  MnvH1D *True_CrossSection_other = (MnvH1D*)Constuct_crosssection_Hists.Interaction_HistMap[kInteraction_OTHER]->Clone(Print_Name);

  True_CrossSection_other->Divide(True_CrossSection_other, fluxIntegral);
  True_CrossSection_other->Scale(1./nNucleons/POT);
  True_CrossSection_other->Scale(1.e4); //Flux histogram is in m^-2, but convention is to report cm^2
  True_CrossSection_other->Scale(1., "width");
  True_CrossSection_other->Clone()->Write(Print_Name);

}//end of function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

void WritetoTFile_TranWarpHist(TransWarp_Hist &input_transWarp_Hist, TFile& file, char* Name){

file.cd(); // write to this Tfile

char Print_Name[2024];

sprintf(Print_Name, "%s_mc_reco",Name);
input_transWarp_Hist.mc_reco ->Clone()->Write(Print_Name);

sprintf(Print_Name, "%s_mc_truth",Name);
input_transWarp_Hist.mc_truth ->Clone()->Write(Print_Name);

sprintf(Print_Name, "%s_data_reco",Name);
input_transWarp_Hist.data_reco ->Clone()->Write(Print_Name);

sprintf(Print_Name, "%s_data_truth",Name);
input_transWarp_Hist.data_truth ->Clone()->Write(Print_Name);

sprintf(Print_Name, "%s_h_Mig",Name);
input_transWarp_Hist.h_Mig ->Clone()->Write(Print_Name);

return;

}//end of function

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

void WritetoTFile_TranWarp2DHist(TransWarp_2DHist &input_transWarp_Hist, TFile& file, char* Name){

file.cd(); // write to this Tfile

char Print_Name[2024];

sprintf(Print_Name, "%s_mc_reco",Name);
input_transWarp_Hist.mc_reco ->Clone()->Write(Print_Name);

sprintf(Print_Name, "%s_mc_truth",Name);
input_transWarp_Hist.mc_truth ->Clone()->Write(Print_Name);

sprintf(Print_Name, "%s_data_reco",Name);
input_transWarp_Hist.data_reco ->Clone()->Write(Print_Name);

sprintf(Print_Name, "%s_data_truth",Name);
input_transWarp_Hist.data_truth ->Clone()->Write(Print_Name);

sprintf(Print_Name, "%s_h_Mig",Name);
input_transWarp_Hist.h_Mig ->Clone()->Write(Print_Name);

return;

}//end of function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////



void Check_NSignalBins(CrossSection_Hist &Constuct_crosssection_Hists,char* Name ){

  int NBins_Eff_num = Constuct_crosssection_Hists.h_effNum->GetNbinsX();
  int NBins_Dom_num = Constuct_crosssection_Hists.h_effDom->GetNbinsX();

  int NBins_data_num = Constuct_crosssection_Hists.h_Data_Signal->GetNbinsX();
  int NBins_reco_num = Constuct_crosssection_Hists.h_RECO_Signal->GetNbinsX();

  std::vector<int> myvector;
  myvector.push_back(NBins_Eff_num);
  myvector.push_back(NBins_Dom_num);
  myvector.push_back(NBins_data_num);
  myvector.push_back(NBins_reco_num);

  if ( std::adjacent_find( myvector.begin(), myvector.end(), std::not_equal_to<int>() ) == myvector.end() )
  {
    std::cout << "All Bins are equal each other for  = " << Name<< std::endl;
  }
  else{
    std::cout << "Opps Bins are NOT Equal for Cross- Section Hists " << Name<< std::endl;
    std::cout << " NBins_Eff_num = " << NBins_Eff_num << std::endl;
    std::cout << " NBins_Dom_num = " << NBins_Dom_num << std::endl;
    std::cout << " NBins_data_num = " << NBins_data_num << std::endl;
    std::cout << " NBins_reco_num = " << NBins_reco_num << std::endl;

  }

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////



double FindDistance(Vertex_XYZ upstream_point,Vertex_XYZ downstream_point ){

  auto deltax = (downstream_point.x-upstream_point.x);
  auto deltay = (downstream_point.y-upstream_point.y);
  auto deltaz = (downstream_point.z-upstream_point.z);

  return sqrt( pow(deltax,2)+pow(deltay,2)+pow(deltaz,2));
}

std::vector<double> FindDistance_vector(std::vector<Vertex_XYZ> upstream_points, std::vector<Vertex_XYZ> downstream_points ){

if(upstream_points.size() != downstream_points.size()){assert(false && "Size of input vector of different length in FindDistance_vector " );}

std::vector<double> output_vector; //mm

for(unsigned int i = 0; i < upstream_points.size(); ++i){
  double distance = FindDistance( upstream_points.at(i), downstream_points.at(i) );
output_vector.push_back(distance);
}

return output_vector;

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////


bool CheckIfTrajectorHaveEqual_Components(Trajector input_Trajector)
{
  std::vector <int> vector;

  vector.push_back(input_Trajector.InitalTrkx.size());
  vector.push_back(input_Trajector.InitalTrky.size());
  vector.push_back(input_Trajector.InitalTrkz.size());

  vector.push_back(input_Trajector.FinalTrkx.size());
  vector.push_back(input_Trajector.FinalTrky.size());
  vector.push_back(input_Trajector.FinalTrkz.size());

  if ( std::equal(vector.begin() + 1, vector.end(), vector.begin()) )
  {
    return true;
  }
  else
  {
    return false;
  }


}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

bool CheckIfTrajectorHaveEqual_Components(Trajector_withTrueEnergyFraction input_Trajector)
{
  std::vector <int> vector;

  vector.push_back(input_Trajector.InitalTrkx.size());
  vector.push_back(input_Trajector.InitalTrky.size());
  vector.push_back(input_Trajector.InitalTrkz.size());

  vector.push_back(input_Trajector.FinalTrkx.size());
  vector.push_back(input_Trajector.FinalTrky.size());
  vector.push_back(input_Trajector.FinalTrkz.size());

  if ( std::equal(vector.begin() + 1, vector.end(), vector.begin()) )
  {
    return true;
  }
  else
  {
    return false;
  }


}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

bool CheckIfTrajectorsHaveEqual_RunInfo(Trajector input_TrajectorA ,Trajector input_TrajectorB  )
{
  if(input_TrajectorA.RunInfo.run==input_TrajectorB.RunInfo.run &&
    input_TrajectorA.RunInfo.subrun == input_TrajectorB.RunInfo.subrun &&
    input_TrajectorA.RunInfo.gate == input_TrajectorB.RunInfo.gate &&
    input_TrajectorA.RunInfo.slice == input_TrajectorB.RunInfo.slice)
    {
      return true;
    }
    else {
      std::cout<<"Trajectors Run , subrun , gate , slice  are not equal "<< std::endl;
      return false;
    }
  }

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

bool CheckIfTrajectors_VectorsHaveEqual_RunInfo(std::vector<Trajector> input_vectorTrajectorA ,std::vector<Trajector> input_vectorTrajectorB  ){
  if(input_vectorTrajectorA.size() != input_vectorTrajectorB.size()  ){std::cout<<" Vector are different sizes for CheckIfTrajectors_VectorsHaveEqual_RunInfo"<<std::endl; return false;}

  std::vector<int> runA;
  std::vector<int> subrunA;
  std::vector<int> gateA;
  std::vector<int> sliceA;
  std::vector<int> runB;
  std::vector<int> subrunB;
  std::vector<int> gateB;
  std::vector<int> sliceB;

  for(auto cat : input_vectorTrajectorA){
    runA.push_back(cat.RunInfo.run);
    subrunA.push_back(cat.RunInfo.subrun);
    gateA.push_back(cat.RunInfo.gate);
    sliceA.push_back(cat.RunInfo.slice);
  }

  for(auto cat : input_vectorTrajectorB){
    runB.push_back(cat.RunInfo.run);
    subrunB.push_back(cat.RunInfo.subrun);
    gateB.push_back(cat.RunInfo.gate);
    sliceB.push_back(cat.RunInfo.slice);
  }

  if(compare(runA, runB)&&
  compare(subrunA, subrunB)&&
  compare(gateA, gateB)&&
  compare(sliceA, sliceB)){return true;}
  else{std::cout<<"Trajector Vectors are not equal "<< std::endl;
  return false;}

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

bool CheckIfTrajectors_VectorsHaveEqual_RunInfo(std::vector<Trajector> input_vectorTrajectorA ,std::vector<Trajector_withTrueEnergyFraction> input_vectorTrajectorB  ){
  if(input_vectorTrajectorA.size() != input_vectorTrajectorB.size()  ){std::cout<<" Vector are different sizes for CheckIfTrajectors_VectorsHaveEqual_RunInfo"<<std::endl; return false;}

  std::vector<int> runA;
  std::vector<int> subrunA;
  std::vector<int> gateA;
  std::vector<int> sliceA;
  std::vector<int> runB;
  std::vector<int> subrunB;
  std::vector<int> gateB;
  std::vector<int> sliceB;

  for(auto cat : input_vectorTrajectorA){
    runA.push_back(cat.RunInfo.run);
    subrunA.push_back(cat.RunInfo.subrun);
    gateA.push_back(cat.RunInfo.gate);
    sliceA.push_back(cat.RunInfo.slice);
  }

  for(auto cat : input_vectorTrajectorB){
    runB.push_back(cat.RunInfo.run);
    subrunB.push_back(cat.RunInfo.subrun);
    gateB.push_back(cat.RunInfo.gate);
    sliceB.push_back(cat.RunInfo.slice);
  }

  if(compare(runA, runB)&&
  compare(subrunA, subrunB)&&
  compare(gateA, gateB)&&
  compare(sliceA, sliceB)){return true;}
  else{std::cout<<"Trajector Vectors are not equal "<< std::endl;
  return false;}

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////


bool CheckIfTrajectors_TRUERECO_KEVectorsHaveEqual_RunInfo(std::vector<Trajector> input_vectorTrajectorA ,std::vector<TRUE_RECO_Energies_Trajectors> input_vectorTRUE_RECO_Energies  ){

  if(input_vectorTrajectorA.size() != input_vectorTRUE_RECO_Energies.size()  ){std::cout<<" Vector are different sizes for CheckIfTrajectors_VectorsHaveEqual_RunInfo"<<std::endl; return false;}

  std::vector<int> runA;
  std::vector<int> subrunA;
  std::vector<int> gateA;
  std::vector<int> sliceA;
  std::vector<int> runB;
  std::vector<int> subrunB;
  std::vector<int> gateB;
  std::vector<int> sliceB;

  for(auto cat : input_vectorTrajectorA){
    runA.push_back(cat.RunInfo.run);
    subrunA.push_back(cat.RunInfo.subrun);
    gateA.push_back(cat.RunInfo.gate);
    sliceA.push_back(cat.RunInfo.slice);
  }

  for(auto cat : input_vectorTRUE_RECO_Energies){
    runB.push_back(cat.RunInfo.run);
    subrunB.push_back(cat.RunInfo.subrun);
    gateB.push_back(cat.RunInfo.gate);
    sliceB.push_back(cat.RunInfo.slice);
  }

  if(compare(runA, runB)&&
  compare(subrunA, subrunB)&&
  compare(gateA, gateB)&&
  compare(sliceA, sliceB)){return true;}
  else{std::cout<<"Trajector Vectors are not equal "<< std::endl;
  return false;}

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

bool CheckIfTrajectors_TRUERECO_KEVectorsHaveEqual_RunInfo(std::vector<Trajector> input_vectorTrajectorA ,std::vector<Trajector_withTrueEnergyFraction> input_vectorTrajector_withTrueEnergyFraction  ){

  if(input_vectorTrajectorA.size() != input_vectorTrajector_withTrueEnergyFraction.size()  ){std::cout<<" Vector are different sizes for CheckIfTrajectors_VectorsHaveEqual_RunInfo"<<std::endl; return false;}

  std::vector<int> runA;
  std::vector<int> subrunA;
  std::vector<int> gateA;
  std::vector<int> sliceA;
  std::vector<int> runB;
  std::vector<int> subrunB;
  std::vector<int> gateB;
  std::vector<int> sliceB;

  for(auto cat : input_vectorTrajectorA){
    runA.push_back(cat.RunInfo.run);
    subrunA.push_back(cat.RunInfo.subrun);
    gateA.push_back(cat.RunInfo.gate);
    sliceA.push_back(cat.RunInfo.slice);
  }

  for(auto cat : input_vectorTrajector_withTrueEnergyFraction){
    runB.push_back(cat.RunInfo.run);
    subrunB.push_back(cat.RunInfo.subrun);
    gateB.push_back(cat.RunInfo.gate);
    sliceB.push_back(cat.RunInfo.slice);
  }

  if(compare(runA, runB)&&
  compare(subrunA, subrunB)&&
  compare(gateA, gateB)&&
  compare(sliceA, sliceB)){return true;}
  else{std::cout<<"Trajector Vectors are not equal "<< std::endl;
  return false;}

}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////


parameterizationEquation_params MakeParameterizelineParasFromPoints(int pdg, double KE ,double X_Start,double Y_Start, double Z_Start,double X_End,double Y_End,double Z_End){
  double a = X_End - X_Start;
  double b = Y_End - Y_Start;
  double c = Z_End - Z_Start;

  parameterizationEquation_params Equation_Map = {pdg, KE, X_Start, Y_Start, Z_Start , a , b , c};

  return Equation_Map;
}

parameterizationEquation_params_bare MakeParameterizelineParasFromPoints(double X_Start,double Y_Start, double Z_Start,double X_End,double Y_End,double Z_End){
  double a = X_End - X_Start;
  double b = Y_End - Y_Start;
  double c = Z_End - Z_Start;

  parameterizationEquation_params_bare Equation_Map = { X_Start, Y_Start, Z_Start , a , b , c};

  return Equation_Map;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

std::vector<parameterizationEquation_params_bare> MakeParameterize_bare_lineParasFromPoints(Vertex_XYZ VertexP,  std::vector<Vertex_XYZ> EndPoints){

std::vector<parameterizationEquation_params_bare> return_vector;

for(auto cat : EndPoints){
  double a = cat.x - VertexP.x; // (Final - Intial) Postion
  double b = cat.y - VertexP.y;
  double c = cat.z - VertexP.z;

  parameterizationEquation_params_bare Paras = { VertexP.x, VertexP.y, VertexP.z, a, b ,c};
  return_vector.push_back(Paras);
}

  return return_vector;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::vector<double> FindVector_TforParameterizeLinesAtZ(std::vector<parameterizationEquation_params_bare> Input_vector,
   double ZPoint_start){
     std::vector<double> t_vector;
     for(auto cat : Input_vector){
       double t = (ZPoint_start - cat.Zo) / cat.c;
    t_vector.push_back(t);
  }
  return t_vector;

}// end of Function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::vector<Vertex_XYZ> GetTrueMinervaStartPostion(std::vector<parameterizationEquation_params_bare> InputPara_vector, std::vector<double> t_vector, double ZPoint_start ){
  if(InputPara_vector.size() != t_vector.size() ) {assert(0 && "Input vectors different size In function : GetTrueMinervaStartPostion");}

  std::vector<Vertex_XYZ> return_vector;
  //std::vector<parameterizationEquation_params_bare>::iterator it_params;
  //std::vector<double>::iterator it_t;
  //for(it_params = InputPara_vector.begin(), it_t = t_vector.begin(); it_params != InputPara_vector.end(); ++it_params, ++it_t ){
for(unsigned int i = 0; i < t_vector.size(); ++i){
    double x =  InputPara_vector.at(i).Xo +  t_vector.at(i) * InputPara_vector.at(i).a;
    double y =  InputPara_vector.at(i).Yo +  t_vector.at(i) * InputPara_vector.at(i).b;
    Vertex_XYZ vertex_start_node{x,y, ZPoint_start};
    return_vector.push_back(vertex_start_node);
  }
  return return_vector;
} //end of Function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
parameterizationEquation_params_DATA MakeParameterizelineParasFromDataPoints(double KE, double angle, double length, double X_Start, double Y_Start, double Z_Start,double X_End,double Y_End,double Z_End){

  double a = X_End - X_Start;
  double b = Y_End - Y_Start;
  double c = Z_End - Z_Start;

  parameterizationEquation_params_DATA Equation_Map{KE, angle, length, X_Start, Y_Start, Z_Start, a, b, c};

return Equation_Map;

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

parameterizationEquation_paramsWithTrueFraction MakeParameterizelineParasFromPoints(int pdg, double KE, double trueEFraction ,double X_Start,double Y_Start, double Z_Start,double X_End,double Y_End,double Z_End){
  double a = X_End - X_Start;
  double b = Y_End - Y_Start;
  double c = Z_End - Z_Start;

  parameterizationEquation_paramsWithTrueFraction Equation_Map = {pdg, KE, trueEFraction, X_Start, Y_Start, Z_Start , a , b , c};

  return Equation_Map;
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
parameterizationEquation_params MakeParameterizelineParasTrajector_Vectorindex(Trajector input_Trajector, int index ){
  int pdg_output = input_Trajector.PDG.at(index);
  auto KE = input_Trajector.KE.at(index);
  auto X_Start = input_Trajector.InitalTrkx.at(index);
  auto Y_Start = input_Trajector.InitalTrky.at(index);
  auto Z_Start = input_Trajector.InitalTrkz.at(index);

  auto X_End = input_Trajector.FinalTrkx.at(index);
  auto Y_End = input_Trajector.FinalTrky.at(index);
  auto Z_End = input_Trajector.FinalTrkz.at(index);

  std::cout << " MakeParameterizelineParasTrajector_Vectorindex(" <<index << "): PDG output: "<< pdg_output<< std::endl;
  std::cout << " MakeParameterizelineParasTrajector_Vectorindex("<< index << "): KE output: "<< KE<< std::endl;

  auto Equation_Map =  MakeParameterizelineParasFromPoints(pdg_output, KE, X_Start, Y_Start,  Z_Start, X_End, Y_End, Z_End );
  return Equation_Map;

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

parameterizationEquation_paramsWithTrueFraction MakeParameterizelineParasTrajector_Vectorindex(Trajector_withTrueEnergyFraction input_Trajector, int index ){
  int pdg_output = input_Trajector.PDG.at(index);
  auto KE = input_Trajector.KE.at(index);
  auto True_EFraction = input_Trajector.true_energy_fraction.at(index);
  auto X_Start = input_Trajector.InitalTrkx.at(index);
  auto Y_Start = input_Trajector.InitalTrky.at(index);
  auto Z_Start = input_Trajector.InitalTrkz.at(index);

  auto X_End = input_Trajector.FinalTrkx.at(index);
  auto Y_End = input_Trajector.FinalTrky.at(index);
  auto Z_End = input_Trajector.FinalTrkz.at(index);

  std::cout << " MakeParameterizelineParasTrajector_Vectorindex(" <<index << "): PDG output: "<< pdg_output<< std::endl;
  std::cout << " MakeParameterizelineParasTrajector_Vectorindex("<< index << "): KE output: "<< KE<< std::endl;

  auto Equation_Map =  MakeParameterizelineParasFromPoints(pdg_output, KE,True_EFraction, X_Start, Y_Start,  Z_Start, X_End, Y_End, Z_End );
  return Equation_Map;

}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::vector <parameterizationEquation_params> MakeParameterizelineParasTrajector_ParticeVectorForSingleTrajector(Trajector input_Trajector)
{
  auto status_of_equal_components = CheckIfTrajectorHaveEqual_Components(input_Trajector);
  std::vector <parameterizationEquation_params> output_vector;
  if(status_of_equal_components==true)
  {

    int i=0;

    for( auto cat : input_Trajector.PDG)
    {
      std::cout << " MakeParameterizelineParasTrajector_ParticeVectorForSingleTrajector: PDG output: "<< cat<< " index:"<<i<< std::endl;
      auto vector_input = MakeParameterizelineParasTrajector_Vectorindex(input_Trajector, i );

      output_vector.push_back(vector_input);
      i++;
    }

  }//end of if statement

  return output_vector;

}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////


std::vector <parameterizationEquation_params_DATA> MakeParameterizelineParasTrajector_ForDataStruct(Trajector_DATA inputVector){



parameterizationEquation_params_DATA muon = MakeParameterizelineParasFromDataPoints(0.0,0.0,0.0, inputVector.muon_Intial_nodex, inputVector.muon_Intial_nodey, inputVector.muon_Intial_nodez,inputVector.muon_Final_nodex,inputVector.muon_Final_nodey,inputVector.muon_Final_nodez);

 std::vector <parameterizationEquation_params_DATA> para_vector;
 para_vector.push_back(muon);
 std::cout<< "inside parameterizationEquation_params_DATA inputVector.ShortTrk_KE.size() =  "<<inputVector.ShortTrk_KE.size() <<std::endl;


 for(unsigned int i=0;i<inputVector.ShortTrk_KE.size();i++){
   std::cout<< "inside parameterizationEquation_params_DATA Index = "<<i <<std::endl;
   std::cout<<"inputVector.ShortTrk_KE.at(i) = " << inputVector.ShortTrk_KE.at(i)<<std::endl;
   std::cout<<"inputVector.ShortTrk_Angle.at(i)= " << inputVector.ShortTrk_Angle.at(i)<<std::endl;
   std::cout<<"inputVector.ShortTrk_Length.at(i)= " << inputVector.ShortTrk_Length.at(i)<<std::endl;
   parameterizationEquation_params_DATA index = MakeParameterizelineParasFromDataPoints(inputVector.ShortTrk_KE.at(i),inputVector.ShortTrk_Angle.at(i),inputVector.ShortTrk_Length.at(i), inputVector.ShortTrk_Intialx.at(i), inputVector.ShortTrk_Intialy.at(i), inputVector.ShortTrk_Intialz.at(i),inputVector.ShortTrk_FinalTrkx.at(i),inputVector.ShortTrk_FinalTrky.at(i),inputVector.ShortTrk_FinalTrkz.at(i));
   para_vector.push_back(index);
 }

 return para_vector;

}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////



std::vector <parameterizationEquation_paramsWithTrueFraction> MakeParameterizelineParasTrajector_ParticeVectorForSingleTrajector_withTRUEFraction(Trajector_withTrueEnergyFraction input_Trajector)
{
  auto status_of_equal_components = CheckIfTrajectorHaveEqual_Components(input_Trajector);
  std::vector <parameterizationEquation_paramsWithTrueFraction> output_vector;
  if(status_of_equal_components==true)
  {

    int i=0;

    for( auto cat : input_Trajector.PDG)
    {
      std::cout << " MakeParameterizelineParasTrajector_ParticeVectorForSingleTrajector: PDG output: "<< cat<< " index:"<<i<< std::endl;
      auto vector_input = MakeParameterizelineParasTrajector_Vectorindex(input_Trajector, i );

      output_vector.push_back(vector_input);
      i++;
    }

  }//end of if statement

  return output_vector;

}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////



std::vector<Vertex_XYZ> MakeVectorofPath(parameterizationEquation_params Input, double Spaceingcm, double t_finish)
{
  std::vector<Vertex_XYZ> output_vector;
  //double start_t = 0.0;
  //double end_t = 1.0 * t_finish;
  int N_points = Find_NPoints( Input , Spaceingcm);

  double spacing = 1.0 / (double)N_points;
  double count=0;
  for(int i = 0 ;i < N_points; i++){
    auto xyzpoint = Parameterization3dFunction(Input,count );
    count = count + spacing;
    output_vector.push_back(xyzpoint);
  }

  return output_vector;

}//end of function

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////


std::vector<Vertex_XYZ> MakeVectorofPath(parameterizationEquation_params_DATA Input, double Spaceingcm, double t_finish)
{
  std::vector<Vertex_XYZ> output_vector;
  //double start_t = 0.0;
  //double end_t = 1.0 * t_finish;
  int N_points = Find_NPoints( Input , Spaceingcm);

  double spacing = 1.0 / (double)N_points;
  double count=0;
  for(int i = 0 ;i < N_points; i++){
    auto xyzpoint = Parameterization3dFunction(Input,count );
    count = count + spacing;
    output_vector.push_back(xyzpoint);
  }

  return output_vector;

}//end of function

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////


std::vector<Vertex_XYZ> MakeVectorofPath(parameterizationEquation_paramsWithTrueFraction Input, double Spaceingcm, double t_finish)
{
  std::vector<Vertex_XYZ> output_vector;
  //double start_t = 0.0;
  //double end_t = 1.0 * t_finish;
  int N_points = Find_NPoints( Input , Spaceingcm);

  double spacing = 1.0 / (double)N_points;
  double count=0;
  for(int i = 0 ;i < N_points; i++){
    auto xyzpoint = Parameterization3dFunction(Input,count );
    count = count + spacing;
    output_vector.push_back(xyzpoint);
  }

  return output_vector;

}//end of function

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

Vertex_XYZ Parameterization3dFunction(parameterizationEquation_params input, double t){

  assert(t>=0.0);
  assert(t<=1.0);
  double x = input.Xo + t * input.a;
  double y = input.Yo + t * input.b;
  double z = input.Zo + t * input.c;

  Vertex_XYZ xyz = {x,y,z};
  return xyz;

}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

Vertex_XYZ Parameterization3dFunction(parameterizationEquation_paramsWithTrueFraction input, double t){

  assert(t>=0.0);
  assert(t<=1.0);
  double x = input.Xo + t * input.a;
  double y = input.Yo + t * input.b;
  double z = input.Zo + t * input.c;

  Vertex_XYZ xyz = {x,y,z};
  return xyz;

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

Vertex_XYZ Parameterization3dFunction(parameterizationEquation_params_DATA input, double t){

  assert(t>=0.0);
  assert(t<=1.0);
  double x = input.Xo + t * input.a;
  double y = input.Yo + t * input.b;
  double z = input.Zo + t * input.c;

  Vertex_XYZ xyz = {x,y,z};
  return xyz;

}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

int Find_NPoints(parameterizationEquation_params input ,double Spaceingcm){

  auto start = Parameterization3dFunction( input, 0.0);
  auto end = Parameterization3dFunction( input, 1.0);
  auto distance = FindDistance(start,end )/10.0; //in cm
  int point = ceil(distance / Spaceingcm);

  return point;

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

int Find_NPoints(parameterizationEquation_params_DATA input ,double Spaceingcm){

  auto start = Parameterization3dFunction( input, 0.0);
  auto end = Parameterization3dFunction( input, 1.0);
  auto distance = FindDistance(start,end )/10.0; //in cm
  int point = ceil(distance / Spaceingcm);

  return point;

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
int Find_NPoints(parameterizationEquation_paramsWithTrueFraction input ,double Spaceingcm){

  auto start = Parameterization3dFunction( input, 0.0);
  auto end = Parameterization3dFunction( input, 1.0);
  auto distance = FindDistance(start,end )/10.0; //in cm
  int point = ceil(distance / Spaceingcm);

  return point;

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
TGraph  *Make_RECOCut_Tgraph_fromCutMap(const char* fileName , RECO_Cut_Map input_Map)
{
  const int size = input_Map.size();
  double CutAmount[size];
  double CutNumber[size];
  int count = 0;

  for( auto const &Cut : input_Map ) {
    CutAmount[count] = Cut.second;
    CutNumber[count] =  Cut.first; //count;
    count++;
  }

  TGraph *Tg_result = new TGraph(size, CutNumber, CutAmount);

  Tg_result->SetName(fileName);
    return Tg_result;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
TGraph  *Make_TruthCut_Tgraph_fromCutMap(const char* fileName, TRUE_Cut_Map input_Map)
{
  const int size = input_Map.size();
  double CutAmount[size];
  double CutNumber[size];
  int count = 0;

  for( auto const &Cut : input_Map ) {
    CutAmount[count] = Cut.second;
    CutNumber[count] = Cut.first;  //count;
    count++;
  }

  TGraph *Tg_result = new TGraph(size, CutNumber, CutAmount);
  Tg_result->SetName(fileName);
  return Tg_result;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
TGraph  *Make_X_vs_Z_Tgraph_fromVector(std::vector<Vertex_XYZ> input)
{
  const int size = input.size();
  double ZZ[size];
  double XX[size];

  for(unsigned int j =0; j<size;j++){
  XX[j]=input.at(j).x;
  ZZ[j]=input.at(j).z;
  }

  TGraph *Tg_result = new TGraph(size,ZZ,XX);

    return Tg_result;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
TGraph  *Make_V_vs_Z_Tgraph_fromVector(std::vector<Vertex_XYZ> input)
{
  const int size = input.size();
  double ZZ[size];
  double VV[size];

  for(unsigned int j =0; j<size;j++){

  VV[j]=calcVfromXY(input.at(j).x, input.at(j).y);
  ZZ[j]=input.at(j).z;

  }

  TGraph *Tg_result = new TGraph(size,ZZ,VV);

    return Tg_result;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
TGraph  *Make_U_vs_Z_Tgraph_fromVector(std::vector<Vertex_XYZ> input)
{
  const int size = input.size();
  double ZZ[size];
  double UU[size];

  for(unsigned int j =0; j<size;j++){

  UU[j]=calcUfromXY(input.at(j).x, input.at(j).y);
  ZZ[j]=input.at(j).z;

}

TGraph *Tg_result = new TGraph(size,ZZ,UU);

return Tg_result;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
TGraph  *Make_Y_vs_Z_Tgraph_fromVector(std::vector<Vertex_XYZ>input)
{

  const int size = input.size();
  double ZZ[size];
  double XX[size];

  for(unsigned int j =0; j<size;j++){
  XX[j]=input.at(j).y;
  ZZ[j]=input.at(j).z;
  }

  TGraph *Tg_result = new TGraph(size,ZZ,XX);


  Tg_result->GetXaxis()->CenterTitle();
  Tg_result->GetYaxis()->CenterTitle();
  Tg_result->GetXaxis()->SetTitle("Z [mm]");
  Tg_result->GetYaxis()->SetTitle("Y [mm]");
  Tg_result->GetXaxis()->SetTitleSize(0.038);
  Tg_result->GetYaxis()->SetTitleSize(0.038);
  Tg_result->SetLineColor(2);
  Tg_result->SetLineWidth(4);
  Tg_result->SetMarkerColor(1);
  Tg_result->SetMarkerSize(1);
  Tg_result->SetMarkerStyle(20);
  Tg_result->SetMaximum(1100.0);
  Tg_result->SetMinimum(-1100.0);

    return Tg_result;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
TGraph  *Make_R_vs_Z_Tgraph_fromVector(std::vector<Vertex_XYZ>input)
{
  const int size = input.size();
  double ZZ[size];
  double RR[size];

  for(unsigned int j =0; j<size;j++){
  RR[j]=sqrt(pow(input.at(j).y,2)+pow(input.at(j).x,2));
  ZZ[j]=input.at(j).z;
  }

  TGraph *Tg_result = new TGraph(size,ZZ,RR);

  Tg_result->GetXaxis()->CenterTitle();
  Tg_result->GetYaxis()->CenterTitle();
  Tg_result->GetXaxis()->SetTitle("Z [mm]");
  Tg_result->GetYaxis()->SetTitle("R [mm]");
  Tg_result->GetXaxis()->SetTitleSize(0.038);
  Tg_result->GetYaxis()->SetTitleSize(0.038);
  Tg_result->SetLineColor(2);
  Tg_result->SetLineWidth(4);
  Tg_result->SetMarkerColor(1);
  Tg_result->SetMarkerSize(1);
  Tg_result->SetMarkerStyle(20);
  Tg_result->SetMaximum(1000.0);
  Tg_result->SetMinimum(0);
    return Tg_result;

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

TGraph  *Make_RR_vs_Z_Tgraph_fromVector(std::vector<Vertex_XYZ>input)
{

  const int size = input.size();
  double ZZ[size];
  double RR[size];

  for(unsigned int j =0; j<size;j++){
  RR[j]=pow(input.at(j).y,2) + pow(input.at(j).x,2);
  ZZ[j]=input.at(j).z;
  }

  TGraph *Tg_result = new TGraph(size,ZZ,RR);

  Tg_result->GetXaxis()->CenterTitle();
  Tg_result->GetYaxis()->CenterTitle();
  Tg_result->GetXaxis()->SetTitle("Z [mm]");
  Tg_result->GetYaxis()->SetTitle("R^{2} [mm]");
  Tg_result->GetXaxis()->SetTitleSize(0.038);
  Tg_result->GetYaxis()->SetTitleSize(0.038);
  Tg_result->SetLineColor(2);
  Tg_result->SetLineWidth(4);
  Tg_result->SetMarkerColor(1);
  Tg_result->SetMarkerSize(1);
  Tg_result->SetMarkerStyle(20);
  Tg_result->SetMaximum(1000000.0);
  Tg_result->SetMinimum(0);

    return Tg_result;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

TGraph  *Make_VertLineTgraph(int N_points,double Zpostion, double Start_Xaxis, double End_Xaxis)
{

  const int size = N_points;
  double ZZ[size];
  double XX[size];
  double Space = (End_Xaxis - Start_Xaxis) / (double)N_points;
  double count = Start_Xaxis;

  for(int j =0; j<size;j++)
  {
    XX[j]=count;
    ZZ[j]=Zpostion;
    count = count + Space;
  }

  TGraph *Tg_result = new TGraph(size,ZZ,XX);


  return Tg_result;

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
bool CheckifPlaylists_haveSameHeliumStatus(ME_playlist_TFileMAP TFile_MAP){
  std::vector <ME_helium_Status> CryoTank_status_vector;

  for (auto const& cat : TFile_MAP)
  {
    auto status = GetPlaylist_HeliumStatus(cat.first);
    CryoTank_status_vector.push_back(status);
  }

//std::adjacent_find( CryoTank_status_vector.begin(), CryoTank_status_vector.end(), std::not_equal_to<>() ) == CryoTank_status_vector.end()

  if ( std::equal(CryoTank_status_vector.begin() + 1, CryoTank_status_vector.end(), CryoTank_status_vector.begin()) )
  {
    std::cout << "All elements Have Same Cryo status" << std::endl;
    return true;
  }

  else
  {
    std::cout << "This Playlist has both Full and Empty CryoTank status!!!" << std::endl;
    return false;
  }

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
Pot_MapList Constuct_POT_playlistMap(ME_playlist_RootPathMAP RootPath_MAP, bool m_ismc){
  Pot_MapList POTMap;
  std::cout<<" Constucting POT Playlist Map: for this Many playlist" <<  RootPath_MAP.size()<< std::endl;

  for (auto const& cat : RootPath_MAP)
  {
    std::string pathway = cat.second;
    std::cout<<"Getting POT from Playlist: " << GetPlaylist_Name(cat.first) << std::endl;
    std::cout<<"Using Root Pathway = "<< pathway<<std::endl;
    double Pot = 0.0;


    if(m_ismc==true)
    {
      ChainWrapper* mcchainPOT = makeChainWrapperPtr(pathway.c_str(), "Meta");
      Pot = GetPOT_local(mcchainPOT,"MC");
    }
    else if(m_ismc==false)
    {
      ChainWrapper* datachainPOT = makeChainWrapperPtr(pathway.c_str(), "Meta");
      Pot = GetPOT_local(datachainPOT);
    }

    //POTMap.insert(ME_playlist_RootPathPAIR(cat.first, Pot));
    POTMap.insert(std::make_pair(cat.first, Pot));

  }
return POTMap;

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
double Pot_from_rootpathway(std::string pathway, bool m_ismc ){

  double Pot = 0.0;


  if(m_ismc==true)
  {
    ChainWrapper* mcchainPOT = makeChainWrapperPtr(pathway.c_str(), "Meta");
    Pot = GetPOT_local(mcchainPOT,"MC");
  }
  else if(m_ismc==false)
  {
    ChainWrapper* datachainPOT = makeChainWrapperPtr(pathway.c_str(), "Meta");
    Pot = GetPOT_local(datachainPOT);
  }


return Pot;


}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
Pot_MapList Constuct_POT_playlistMap(PlotUtils::POTCounter *pot_counter, ME_playlist_RootPathMAP RootPath_MAP){
  Pot_MapList POTMap;
  std::cout<<" Constucting POT Playlist Map: for this Many playlist = " <<  RootPath_MAP.size()<< std::endl;

  for (auto const& cat : RootPath_MAP)
  {
    std::string pathway = cat.second;
    std::cout<<"Getting POT from Playlist: " << GetPlaylist_Name(cat.first) << std::endl;
    std::cout<<"Using Root Pathway = "<< pathway <<std::endl;
    double Pot = 0.0;

      Pot =  pot_counter->getPOTfromPlaylist(pathway.c_str());
      //POTMap.insert(ME_playlist_RootPathPAIR(cat.first, Pot));
        POTMap.insert(std::make_pair(cat.first, Pot));
  }


return POTMap;

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
double Combine_POTFromMap(Pot_MapList inputPOTplaylistMAP )
{
  double Total_POT = 0.0;

  for (auto const &cat : inputPOTplaylistMAP)
  {
    Total_POT = Total_POT + cat.second;
  }
  return Total_POT;
}//end of function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

Pot_MapStatusList Constuct_TOTALPOT_cryostatusMap(Pot_MapList FullMC_POTMap,
                                                      Pot_MapList EmptyMC_POTMap,
                                                      Pot_MapList FullData_POTMap,
                                                      Pot_MapList EmptyData_POTMap)
{

  Pot_MapStatusList Total_Map;


  assert(CheckIFMap_hasonly_FULLstatus(FullMC_POTMap) && "FullMC_POTMap has a Empty Playlist in it, ONLY FULL Status should in in this Playlist ");
  assert(CheckIFMap_hasonly_FULLstatus(FullData_POTMap) && "FullData_POTMap has a Empty Playlist in it, ONLY FULL Status should in in this Playlist ");

  assert(CheckIFMap_hasonly_Emptystatus(EmptyMC_POTMap) && "EmptyMC_POTMap has a FULL Playlist in it, ONLY EMPTY Status should in in this Playlist ");
  assert(CheckIFMap_hasonly_Emptystatus(EmptyData_POTMap) && "EmptyData_POTMap has a FULL Playlist in it, ONLY EMPTY Status should in in this Playlist ");

  double MC_TOTALPOT_POTforFULL = Combine_POTFromMap(FullMC_POTMap );
  Total_Map.insert(std::make_pair(kMC_FULL, MC_TOTALPOT_POTforFULL));
  double DATA_TOTALPOT_POTforFULL = Combine_POTFromMap(FullData_POTMap );
  Total_Map.insert(std::make_pair(kDATA_FULL, DATA_TOTALPOT_POTforFULL));
  double MC_TOTALPOT_POTforEMPTY = Combine_POTFromMap(EmptyMC_POTMap );
  Total_Map.insert(std::make_pair(kMC_EMPTY, MC_TOTALPOT_POTforEMPTY));
  double DATA_TOTALPOT_POTforEMPTY = Combine_POTFromMap(EmptyData_POTMap );
  Total_Map.insert(std::make_pair(kDATA_EMPTY, DATA_TOTALPOT_POTforEMPTY));

  return Total_Map;

}//end of function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
Pot_MapStatusList Constuct_TOTALPOT_cryostatusMap(Pot_MapList Full_POTMap,
                                                      Pot_MapList Empty_POTMap ,bool ForMC)
{

  Pot_MapStatusList Total_Map;

  assert(CheckIFMap_hasonly_FULLstatus(Full_POTMap) && "FullMC_POTMap has a Empty Playlist in it, ONLY FULL Status should in in this Playlist ");

  assert(CheckIFMap_hasonly_Emptystatus(Empty_POTMap) && "EmptyMC_POTMap has a FULL Playlist in it, ONLY EMPTY Status should in in this Playlist ");

  if(ForMC==true){
    double MC_TOTALPOT_POTforFULL = Combine_POTFromMap(Full_POTMap );
    Total_Map.insert(std::make_pair(kMC_FULL, MC_TOTALPOT_POTforFULL));
    double MC_TOTALPOT_POTforEMPTY = Combine_POTFromMap(Empty_POTMap );
    Total_Map.insert(std::make_pair(kMC_EMPTY, MC_TOTALPOT_POTforEMPTY));
  }

  else if(ForMC==false){
    double DATA_TOTALPOT_POTforFULL = Combine_POTFromMap(Full_POTMap );
    Total_Map.insert(std::make_pair(kDATA_FULL, DATA_TOTALPOT_POTforFULL));
    double DATA_TOTALPOT_POTforEMPTY = Combine_POTFromMap(Empty_POTMap );
    Total_Map.insert(std::make_pair(kDATA_EMPTY, DATA_TOTALPOT_POTforEMPTY));
  }


  return Total_Map;

}//end of function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
Pot_MapStatusList MakeScaler_TOTALPOT_cryostatusMapTOFULLDATA(Pot_MapStatusList Total_Map){

  Pot_MapStatusList Scaled_Total_Map;

  double TOTAL_POTfulldata = Total_Map[kDATA_FULL];

  for (auto const& cat : Total_Map)
  {
    double scaler = TOTAL_POTfulldata / cat.second;

    Scaled_Total_Map.insert(std::make_pair(cat.first, scaler));
  }

  return Scaled_Total_Map;

}//end
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
Pot_MapStatusList MakeScaler_TOTALPOT_cryostatusMapTOEMPTYDATA(Pot_MapStatusList Total_Map){

  Pot_MapStatusList Scaled_Total_Map;

  double TOTAL_POTfulldata = Total_Map[kDATA_EMPTY];

  for (auto const& cat : Total_Map)
  {
    double scaler = TOTAL_POTfulldata / cat.second;

    Scaled_Total_Map.insert(std::make_pair(cat.first, scaler));
  }

  return Scaled_Total_Map;

}//end
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
bool CheckIFMap_hasonly_FULLstatus(Pot_MapList POTMap){

  for (auto const& cat : POTMap)
  {
    auto status = GetPlaylist_HeliumStatus(cat.first);
    if(kEMPTY==status){return false;}
  }
  return true;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
bool CheckIFMap_hasonly_Emptystatus(Pot_MapList POTMap){

  for (auto const& cat : POTMap)
  {
    auto status = GetPlaylist_HeliumStatus(cat.first);
    if(kFULL==status){return false;}
  }
  return true;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
Pot_MapList POT_ScalersMap(Pot_MapList inputPOTMap ,double POT_toScaleTOO ){
  std::cout<<" Constucting POT Playlist map for POT scaling, THis Map is Scaled to this POT = " << POT_toScaleTOO <<std::endl;
  Pot_MapList POTMap;

  for (auto const& cat : inputPOTMap)
  {
    double SCALER =   POT_toScaleTOO / cat.second ;

    POTMap.insert(std::make_pair(cat.first, SCALER));

  }//end of loop

  return POTMap;

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

void PrintPot_MapList(Pot_MapList inputPOTMap, const char* name  ){
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"Printing POT Map for:  "<< name <<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

  typename std::map<ME_helium_Playlists,double>::const_iterator dog;

  for(dog = inputPOTMap.begin(); dog != inputPOTMap.end(); ++dog)
  {
    std::cout << "Playlist : " << GetPlaylist_Name(dog->first) << " Scaler = "<< dog->second<< std::endl;
  }
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"   "<<std::endl;

}//endl;
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void PrintPot_MapListStatus(Pot_MapList Pot_MapStatusList_input, const char* name  ){
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"Printing POT Map for:  "<< name <<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

  typename std::map<ME_helium_Playlists,double>::const_iterator dog;

  for(dog = Pot_MapStatusList_input.begin(); dog != Pot_MapStatusList_input.end(); ++dog)
  {
    std::cout << "Playlist : " << GetPlaylist_Name(dog->first) << " Scaler = "<< dog->second<< std::endl;
  }
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"   "<<std::endl;


}//endl;

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
double GetPOT_local(PlotUtils::ChainWrapper* _chain,std::string name){
  TChain *chain = _chain->GetChain();
  double tot_pot_data = 0.0;
  double pot_data = 0.0;
  TBranch *b_pot_data;
  chain->SetBranchAddress("POT_Used",&pot_data,&b_pot_data);
  Int_t tot_entries = chain->GetEntries();
  double global_pot_data = 0.0;
  double global_pot=0.0;
  TBranch *b_global_pot;
  chain->SetBranchAddress("POT_Total",&global_pot,&b_global_pot);
  for(int i =0;i<tot_entries;i++){
    chain->GetEntry(i);
    tot_pot_data+= pot_data;
    global_pot_data+= global_pot;
  }
  std::cout<<name << "Total POT: "<<global_pot_data<<std::endl;
  std::cout<<name << "Used POT returned: "<<tot_pot_data<<std::endl;
  return tot_pot_data;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
double CountPOT(const std::string& fileName)
{
  PlotUtils::ChainWrapper meta("Meta");
  meta.Add(fileName);

  const int nEntries = meta.GetEntries();
  assert((nEntries >= meta.GetChain()->GetListOfFiles()->GetEntriesFast())
         && "Each AnaTuple file should have exactly at least 1 entry for POT!");

  double pot_used = 0;
  for(int entry = 0; entry < nEntries; ++entry) pot_used += meta.GetValue("POT_Used", entry);

  return pot_used;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
Playlist_MnvH1D_Map Constuct_mvnH1DMap_FromME_playlist_TFileMAP(ME_playlist_TFileMAP TFile_Map, const char* name ){
  Playlist_MnvH1D_Map MnvH1D_Map;
  //std::cout<<" " <<std::endl;
  if(Debugmode==true) std::cout<<" Constucting Hist map for Varible Name:" << name <<std::endl;
  if(Debugmode==true) std::cout<< " Input Map Has Size =  " << TFile_Map.size() <<std::endl;
  typename std::map<ME_helium_Playlists, TFile*>::const_iterator cat;
   int Bins1 = 999;
  for (cat = TFile_Map.begin(); cat != TFile_Map.end(); ++cat)
  {
    //auto hist = GetHist(cat->second, name);
    if(Debugmode==true) std::cout<<" Playlist Name : "<< GetPlaylist_Name(cat->first)<<std::endl;
    //MnvH1D *hist = (MnvH1D*)(cat->second)->Get(name);
    MnvH1D *hist = Get1DHist(*cat->second,name);
    if (hist==0){std::cout<<" Playlist Name : "<< GetPlaylist_Name(cat->first)<<std::endl;}
    if(Bins1 == 999){ Bins1 =hist->GetNbinsX(); }

    if (Bins1 != hist->GetNbinsX() ) { std::cout<< "Opps :( trying to merg Hists with different Bin sizes)"<< std::endl;
    std::cout<<"Playlist Name : "<< GetPlaylist_Name(cat->first) <<" Number Bins = " << hist->GetNbinsX()<<std::endl;
    assert(false);
    }
    //

    MnvH1D_Map.insert(std::make_pair(cat->first, hist));

  }//end of loop

  //std::cout<<"~~~~FINISHED~~~~~~" <<std::endl;
  //std::cout<<" " <<std::endl;

  return MnvH1D_Map;
}//end of function

Playlist_MnvH1D_Map Constuct_mvnH1DMap_FromME_playlist_TFileMAP(ME_playlist_TFileMAP TFile_Map, std::string inputName ){
  const char* name_char = inputName.c_str();
  return Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map, name_char );
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void AddNumeratorSysErrorsToDenominator_Playlist_MnvH1D_Map(Playlist_MnvH1D_Map &Numerator_Map,
  Playlist_MnvH1D_Map &Denominator_Map){

  typename std::map<ME_helium_Playlists, PlotUtils::MnvH1D*>::const_iterator Numerator_it;
  typename std::map<ME_helium_Playlists, PlotUtils::MnvH1D*>::const_iterator Denominator_it;

  for (Numerator_it = Numerator_Map.begin(), Denominator_it = Denominator_Map.begin(); Numerator_it != Numerator_Map.end(); ++Numerator_it, ++Denominator_it )
  {
    if(Numerator_it->first != Denominator_it->first ){assert(0 && "In AddNumeratorSysErrorsToDenominator_Playlist_MnvH1D_Map : Playlist lists are not matching correctly");}
    Denominator_it->second->AddMissingErrorBandsAndFillWithCV(*Numerator_it->second);
  }//end of loop

return;

}//end of function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
Playlist_MnvH2D_Map Constuct_mvnH2DMap_FromME_playlist_TFileMAP(ME_playlist_TFileMAP TFile_Map, const char* name ){
  Playlist_MnvH2D_Map MnvH2D_Map;
  //std::cout<<"Constucting Hist map for Varible Name:" << name <<std::endl;
  //std::cout<< "Input Map Has Size =  " << TFile_Map.size() <<std::endl;

  typename std::map<ME_helium_Playlists, TFile*>::const_iterator cat;

  for (cat = TFile_Map.begin(); cat != TFile_Map.end(); ++cat)
  {  //std::cout<< " Getting 2D hist from Playlist: "<< GetPlaylist_InitialName(cat->first)<< std::endl;
    //auto hist = GetHist(cat->second, name);
    //MnvH2D *hist = (MnvH2D*)(cat->second)->Get(name);
    //std::cout<< " Playlist: "<< GetPlaylist_InitialName(cat->first)<< " Number of Bins:  "<< cat->second->GetNbinsX()<< std::endl;
    MnvH2D *hist =Get2DHist(*cat->second, name);
    MnvH2D_Map.insert(std::make_pair(cat->first, hist));
  }//end of loop
  return MnvH2D_Map;
}//end of function

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

Playlist_MnvH2D_Map Constuct_mvnH2DMap_FromME_playlist_TFileMAP(ME_playlist_TFileMAP TFile_Map, std::string inputName ){
  const char* name_char = inputName.c_str();
  return Constuct_mvnH2DMap_FromME_playlist_TFileMAP(TFile_Map, name_char );
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

Playlist_HistFolio_MnvH1D_Map Constuct_HistFolio_mvnH1DMap_FromME_playlist_TFileMAP(ME_playlist_TFileMAP TFile_Map, const char* name ){
  Playlist_HistFolio_MnvH1D_Map HistFolio_MnvH1D_Map;
  std::cout<<"Constucting Hist Folio map for Varible Name:" << name <<std::endl;
  std::cout<< "Input Map Has Size =  " << TFile_Map.size() <<std::endl;

  typename std::map<ME_helium_Playlists, TFile*>::const_iterator cat;

  for (cat = TFile_Map.begin(); cat != TFile_Map.end(); ++cat)
  {
    PlotUtils::HistFolio<PlotUtils::MnvH1D> Stack(PlotUtils::LoadHistFolioFromFile<PlotUtils::MnvH1D>(*(cat->second), std::string(name)),"Stack");
    HistFolio_MnvH1D_Map.insert(std::make_pair(cat->first, Stack));
  }//end of loop

  return HistFolio_MnvH1D_Map;
}//end of function

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////


Playlist_MnvH1D_Map Scale_MnvH1D_Map_usingPot_MapList(Playlist_MnvH1D_Map MnvH1D_Map , Pot_MapList ScalerMap , const char* name  )
{
  Playlist_MnvH1D_Map scaled_Map;
  if(CompareMap_ME_helium_PlaylistsKeys(MnvH1D_Map,  ScalerMap)){std::cout<<"Scaling mvnh1d using Scaler Map: Maps have same Playlist keys"<<std::endl;}
  else{
    std::cout<<"Maps are not same size in function: Scale_MnvH1D_Map_usingPot_MapList name = " <<name <<std::endl;
    std::cout << "MnvH1D_Map.size() =  "<< MnvH1D_Map.size() << "     ScalerMap.size() = " << ScalerMap.size()<<std::endl;
    assert(0);
  }


  typename std::map<ME_helium_Playlists, double>::const_iterator cat;
  typename std::map<ME_helium_Playlists, PlotUtils::MnvH1D*>::const_iterator dog;

  for(cat = ScalerMap.begin(), dog = MnvH1D_Map.begin(); cat != ScalerMap.end(); ++cat, ++dog)
  {
    if(cat->first == dog->first){
      PlotUtils::MnvH1D* hist = (PlotUtils::MnvH1D*)(dog->second)->Clone(name);
      hist->Scale(cat->second);
      scaled_Map.insert(std::make_pair(cat->first, hist));
    }
  }

return scaled_Map;

}//end of function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
Playlist_MnvH2D_Map Scale_MnvH2D_Map_usingPot_MapList(Playlist_MnvH2D_Map MnvH2D_Map , Pot_MapList ScalerMap , const char* name  )
{
  Playlist_MnvH2D_Map scaled_Map;
  if(CompareMap_ME_helium_PlaylistsKeys(MnvH2D_Map,  ScalerMap)){std::cout<<"Scaling mvnh1d using Scaler Map: Maps have same Playlist keys"<<std::endl;}
  else{
    std::cout<<"Maps are not same size in function: Scale_MnvH2D_Map_usingPot_MapList name = " <<name <<std::endl;
    std::cout << "MnvH2D_Map.size() =  "<< MnvH2D_Map.size() << "     ScalerMap.size() = " << ScalerMap.size()<<std::endl;
    assert(0);
  }


  typename std::map<ME_helium_Playlists, double>::const_iterator cat;
  typename std::map<ME_helium_Playlists, PlotUtils::MnvH2D*>::const_iterator dog;

  for(cat = ScalerMap.begin(), dog = MnvH2D_Map.begin(); cat != ScalerMap.end(); ++cat, ++dog)
  {
    if(cat->first == dog->first){
      PlotUtils::MnvH2D* hist = (PlotUtils::MnvH2D*)(dog->second)->Clone(name);
      hist->Scale(cat->second);
      scaled_Map.insert(std::make_pair(cat->first, hist));
    }
  }

return scaled_Map;

}//end of function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

void Scale_MnvH1D_Array(const TObjArray  HistArray , double Scaler){

unsigned int i = 0;
  for(auto cat : HistArray) {
    ((PlotUtils::MnvH1D*)HistArray.At(i))->Scale(Scaler);
    i++;
  }
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////


void BinWidthNorm_MnvH1D_Array(const TObjArray HistArray ){
  std::cout<<"Trying to BinWidth Normalize MnvH1D Hist arrays"<<std::endl;

unsigned int i = 0;
  for(auto cat : HistArray) {
    ((PlotUtils::MnvH1D*)HistArray.At(i))->Scale(1.0,"width");
    i++;
  }
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

void AddFirst_toSecond_MnvH1D_Arrays(const TObjArray HistArray1 , const TObjArray HistArray2){
std::cout<<"Trying to Add MnvH1D Hist arrays"<<std::endl;
unsigned int i = 0;
  for(auto cat : HistArray1) {
    ((PlotUtils::MnvH1D*)HistArray1.At(i))->Add((PlotUtils::MnvH1D*)HistArray2.At(i),1.0);
    i++;
  }
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

void SubractSecond_FromFirst_MnvH1D_Arrays(const TObjArray HistArray1 , const TObjArray HistArray2){
std::cout<<"Trying to SubTract MnvH1D Hist arrays"<<std::endl;
unsigned int i = 0;
  for(auto cat : HistArray1) {
    ((PlotUtils::MnvH1D*)HistArray1.At(i))->Add((PlotUtils::MnvH1D*)HistArray2.At(i),-1.0);
    i++;
  }
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

PlotUtils::MnvH1D* Combine_Hists_fromMAP(Playlist_MnvH1D_Map MnvH1D_Map , ME_helium_Playlists ADDtothisHis ,const char* name)
{
  //std::cout<<" "<<std::endl;
  //std::cout<<"Combining  Hist from Map with Size = " <<  MnvH1D_Map.size() <<" Name of New Hist  "<< name<<std::endl;
  typename std::map<ME_helium_Playlists, PlotUtils::MnvH1D*>::const_iterator cat;

  //std::cout<< "First hist from playlist: "<< GetPlaylist_InitialName(ADDtothisHis)<< std::endl;
  PlotUtils::MnvH1D* hist =  MnvH1D_Map.at(ADDtothisHis);

  for(cat = MnvH1D_Map.begin(); cat != MnvH1D_Map.end(); ++cat)
  {
    if(cat->first !=ADDtothisHis)
    {
      //std::cout<< " Playlist: "<< GetPlaylist_InitialName(cat->first)<< " Number of Bins:  "<< cat->second->GetNbinsX()<< std::endl;
      hist->Add((cat->second));
    }
    else{
     //std::cout<< "Starting playlist: "<< GetPlaylist_InitialName(cat->first)<< " Number of Bins:  "<< cat->second->GetNbinsX()<< std::endl;
    }
  }
  hist->SetName(name);

//std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~ Finished Combining ~~~~~~~~~~~~~~~"<<std::endl;


  return hist;


}//end of function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

PlotUtils::MnvH2D* Combine_2DHists_fromMAP(Playlist_MnvH2D_Map MnvH2D_Map , ME_helium_Playlists ADDtothisHis ,const char* name)
{
  //std::cout<<"Combining  Hist from Map with Size = " <<  MnvH2D_Map.size() <<" Name of New Hist  "<< name<<std::endl;
  typename std::map<ME_helium_Playlists, PlotUtils::MnvH2D*>::const_iterator cat;

  int NbinsX = MnvH2D_Map.begin()->second->GetXaxis()->GetNbins();
  int NbinsY = MnvH2D_Map.begin()->second->GetYaxis()->GetNbins();


  PlotUtils::MnvH2D* hist =  MnvH2D_Map.at(ADDtothisHis);

  for(cat = MnvH2D_Map.begin(); cat != MnvH2D_Map.end(); ++cat)
  {
    if(cat->first !=ADDtothisHis)
    {
      int NbinsX_Check = cat->second->GetXaxis()->GetNbins();
      int NbinsY_Check = cat->second->GetYaxis()->GetNbins();
      std::cout<< "2Dhist from playlist: "<< GetPlaylist_InitialName(cat->first)<< " Number of Bins:  "<< cat->second->GetNbinsX()<< std::endl;

      if(NbinsX_Check != NbinsX || NbinsY_Check != NbinsY ){std::cout<<"Number of Bins are different when trying to combined 2D hist "<<std::endl;
      std::cout<< "  NbinsX = " <<  NbinsX << "  NbinsY = "<<  NbinsY<< std::endl;
      std::cout<< "  NbinsX_Check = " <<  NbinsX_Check << "  NbinsY_check = "<<  NbinsY_Check<< std::endl;
      std::cout<< "2Dhist from playlist: "<< GetPlaylist_InitialName(cat->first)<< " Number of Bins:  "<< cat->second->GetNbinsX()<< std::endl;
      assert(false);
    }


      hist->Add((cat->second));
    }
  }
  hist->SetName(name);

  return hist;


}//end of function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::vector<double> GetScales(std::vector<std::pair<TH2*, const char*> >histopts, bool pzProj){
 std::vector<double> tmpvect;
  int nbins = histopts[0].first->GetNbinsX()+2;
  if(pzProj) nbins = histopts[0].first->GetNbinsY()+2;
  for(int i=1;i<nbins-1;i++){
    double maxval = 0;
    for(uint j=0;j<histopts.size();j++){
      TH1D *tmp = pzProj? histopts[j].first->ProjectionX("tmp",i,i): histopts[j].first->ProjectionY("tmp",i,i);
      int maxbin = tmp->GetMaximumBin();
      double content = tmp->GetBinContent(maxbin);
      if(content>maxval) maxval=content;
    }
    //we want abaout 75% of the 1.49, so 1.15
    double scale = 150./maxval;
    if(scale>1){
      int tmpscale = floor(scale*10);
      scale = tmpscale/10.0;
    }
    else{
      int tmpscale = floor(scale*10);
      scale = tmpscale/10.0;
    }
    std::cout << scale << std::endl;
    if(scale < 0){scale = 0;}
    tmpvect.push_back(scale);
  }
    return tmpvect;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::vector<double> GetMaxiumVector(std::vector<std::pair<TH2*, const char*> >histopts, bool ProjX, int intWhichHist){
 std::vector<double> tmpvect;
  int nbins = histopts[intWhichHist].first->GetNbinsX()+2;
  if(ProjX) nbins = histopts[intWhichHist].first->GetNbinsY()+2;
  for(int i=1;i<nbins-1;i++){
    double maxval = 0;
    for(uint j=0;j<histopts.size();j++){
      TH1D *tmp = ProjX? histopts[j].first->ProjectionX("tmp",i,i) : histopts[j].first->ProjectionY("tmp",i,i);
      int maxbin = tmp->GetMaximumBin();
      double content = tmp->GetBinContent(maxbin);
      if(content>maxval) maxval=content;
    }
    //we want abaout 75% of the 1.49, so 1.15

    tmpvect.push_back(maxval);
  }
    return tmpvect;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::vector<double> Normlized_to_lowest_Mulitplers(std::vector <double> multiply_vector){
  std::vector <double> multiply_vector_return;
  double lowest = 9999.0;
  for (auto cat : multiply_vector )
  {
    if( cat > 0.0 && cat < lowest )
    {
      lowest = cat;
    }
  }
  for(auto cat : multiply_vector ){multiply_vector_return.push_back(cat / lowest);}
  return multiply_vector_return;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

std::vector<double> GetScales(std::vector<std::pair<TH2*, const char*> >histopts, bool pzProj, bool  donormalized){

  auto double_vector = GetScales(histopts ,pzProj);
  auto Normal_vector =  Normlized_to_lowest_Mulitplers(double_vector);
  if(donormalized==true)
  {
    return Normal_vector;
  }
  else
  {
    return double_vector;
  }
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::vector<Particle_type> getParticle_typeVector()
{
  std::vector<Particle_type> vector;

  vector.push_back(kElectron);
  vector.push_back(kPion_neg);
  vector.push_back(kPion_pos);
  vector.push_back(kPion_0);
  vector.push_back(kKaon);
  vector.push_back(kProton);
  vector.push_back(kMuon);
  vector.push_back(kGamma);
  vector.push_back(kNeutrino_muon);
  vector.push_back(kNeutrino_electron);
  vector.push_back(kAnti_Neutrino);
  vector.push_back(kFourHelium);
  vector.push_back(kLamdba);
  vector.push_back(kSigma_plus);
  vector.push_back(kParticle_OTHER);
  vector.push_back(kParticle_N_A);
  vector.push_back(kParticle_Total);
  return vector;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

double Hists1DTotal(MnvH1D * hist){
  int NBins = hist->GetNbinsX();
  return (hist -> Integral(1, NBins));
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

float eff_error(double num, double denom, int statFlag) {

   // A is the numerator, (A + B) is the denominator.  num is a subset of denom, so we have to calc stat error differently than sqrt(N)
   double staterr_ratio;
   double eff;
   eff = num/denom;
   staterr_ratio = ( eff * (1-eff) ) / denom;

   // return either the error, or the error * 100 to match the percent
   staterr_ratio = sqrt(staterr_ratio);
   if (statFlag == 1) staterr_ratio = staterr_ratio*100.0;
   return staterr_ratio;

 } // End of eff_error
 ////////////////////////////////////////////////////////////////////////////////
 //
 ////////////////////////////////////////////////////////////////////////////////
std::vector<double> Foward_intergration(MnvH1D *hist){
  std::vector<double> return_vector;
  int NBins = hist->GetNbinsX();
  for(int i = 1; i <= NBins; i++) {
    double input = (hist -> Integral(1, i));
    return_vector.push_back(input);
  }
  return return_vector;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

std::vector<double> Foward_intergration_combined(MnvH1D *hist1, MnvH1D *hist2){
  std::vector<double> return_vector;
  int NBins1 = hist1->GetNbinsX();
  int NBins2 = hist2->GetNbinsX();
  if(NBins1 != NBins2 ){assert((" input Hist have different N Bins in Foward_intergration_combined - NOT OKAY-  ", false));}

  for(int i = 1; i <= NBins1; i++) {
    double input = (hist1 -> Integral(1, i)) + (hist2 -> Integral(1, i)) ;
    return_vector.push_back(input);
  }
  return return_vector;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

std::vector<double> Backwards_intergration(MnvH1D *hist){
  std::vector<double> return_vector;
  int NBins = hist->GetNbinsX();
  double Total = Hists1DTotal(hist);
  int count = NBins;

  for(int i = 1; i <= NBins; i++) {
    double input = (Total - hist->Integral(1,count ));
    return_vector.push_back(input);
    if(count > 1){ count = count - 1; }
  }
  return return_vector;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

std::vector<double> GetBinUpEdges(MnvH1D *hist){
  std::vector<double> return_vector;
  int NBins = hist->GetNbinsX();
  for(int i = 1; i <= NBins; i++) {
    double input = hist -> GetXaxis() -> GetBinUpEdge(i);
    return_vector.push_back(input);
  }
  return return_vector;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

TGraphErrors * MakeForwardIntergrationEfficiency_TGraphError(MnvH1D *hist_Helium){

  int NBins_helium = hist_Helium->GetNbinsX();

  std::vector<double> NBins_edges =  GetBinUpEdges(hist_Helium);
  std::vector<double> he_evts = Foward_intergration(hist_Helium);
  double Total = Hists1DTotal(hist_Helium);
  double Eff[NBins_helium];
  double Eff_error[NBins_helium];
  double Bin_edges[NBins_helium];
  for(int i = 0 ; i < NBins_helium; i++){
    Bin_edges[i] = NBins_edges.at(i);
    Eff[i]= he_evts.at(i) / Total;
    Eff_error[i] = eff_error(he_evts.at(i),Total , 0);
  }

  TGraphErrors *g_return   = new TGraphErrors(NBins_helium, Bin_edges, Eff, 0, Eff_error);   /// (,,,error in x ,error in y)

  return g_return;


}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
TGraphErrors * MakeForwardIntergrationPurity_TGraphError(MnvH1D *hist_Helium, MnvH1D *hist_Other ){

  int NBins_helium = hist_Helium->GetNbinsX();

  std::vector<double> NBins_edges =  GetBinUpEdges(hist_Helium);
  std::vector<double> Total_evts = Foward_intergration_combined(hist_Helium, hist_Other );
  std::vector<double> he_evts = Foward_intergration(hist_Helium);
  double Purity[NBins_helium];
  double Purity_error[NBins_helium];
  double Bin_edges[NBins_helium];

  for(int i = 0 ; i < NBins_helium; i++){
    Bin_edges[i] = NBins_edges.at(i);
    Purity[i]= he_evts.at(i) / Total_evts.at(i);
    Purity_error[i] = eff_error(he_evts.at(i),Total_evts.at(i) , 0);

  }

  TGraphErrors *g_return   = new TGraphErrors(NBins_helium, Bin_edges, Purity, 0, Purity_error);   /// (,,,error in x ,error in y)

  return g_return;

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
TGraphErrors * MakeForwardIntergrationEfficiency_times_Purity_TGraphError(MnvH1D *hist_Helium, MnvH1D *hist_Other ){

  int NBins_helium = hist_Helium->GetNbinsX();

  std::vector<double> NBins_edges =  GetBinUpEdges(hist_Helium);
  std::vector<double> Total_evts = Foward_intergration_combined(hist_Helium,hist_Other );
  std::vector<double> he_evts = Foward_intergration(hist_Helium);
  double Total = Hists1DTotal(hist_Helium);
  double Purity_Eff[NBins_helium];
  double Purity_error[NBins_helium];
  double Eff_error[NBins_helium];
  double Total_Error[NBins_helium];
  double Bin_edges[NBins_helium];

  for(int i = 0 ; i < NBins_helium; i++){
    Bin_edges[i] = NBins_edges.at(i);
    Purity_Eff[i]= (he_evts.at(i) / Total_evts.at(i)) * (he_evts.at(i) / Total) ;
    Purity_error[i] = eff_error(he_evts.at(i),Total_evts.at(i) , 0);
    Eff_error[i] = eff_error(he_evts.at(i),Total , 0);
    Total_Error[i] = sqrt(pow((Purity_error[i]/(he_evts.at(i) / Total_evts.at(i))),2) + pow((Eff_error[i]/(he_evts.at(i) / Total)),2));
  }

  TGraphErrors *g_return   = new TGraphErrors(NBins_helium, Bin_edges, Purity_Eff, 0, Total_Error);   /// (,,,error in x ,error in y)

  return g_return;

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

std::vector<std::vector<HeliumCVUniverse*>> groupCompatibleUniverses(const std::map<std::string, std::vector<HeliumCVUniverse*>> bands)
{
  std::vector<std::vector<HeliumCVUniverse*>> groupedUnivs;
  std::vector<HeliumCVUniverse*> vertical;
  for(const auto& band: bands)
  {
    if(band.first == "cv") vertical.insert(vertical.begin(), band.second.begin(), band.second.end());
    else
    {
      for(const auto univ: band.second)
      {
        if(univ->IsVerticalOnly()) {
          //std::cout<<"this is Vertical universe with name : " << univ->ShortName()<<std::endl;
          vertical.push_back(univ);
        }
        else {
          //std::cout<<"this is lateral universe with name : " << univ->ShortName()<<std::endl;
          groupedUnivs.push_back(std::vector<HeliumCVUniverse*>{univ});
        }
      }
    }
  }

  groupedUnivs.insert(groupedUnivs.begin(), vertical);
  return groupedUnivs;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
bool isCV(const HeliumCVUniverse& univ)
  {
    if(strcmp(univ.ShortName().c_str(), "cv")==0){return true;}
    else {return false;}
  } // end of Function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
RECO_Cut_Map ConstuctRecoCountingMap(std::vector<ECuts> inputRECOCuts){
    RECO_Cut_Map OutputMap;
    for(auto inputCut : inputRECOCuts){
      OutputMap.insert({inputCut, 0.0});
    }

  }// ENd of function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void FillingRecoCountingMap(std::vector<ECuts> inputRECOCuts, RECO_Cut_Map &OutputMap)
{
  for(auto Cuts : inputRECOCuts){
    OutputMap.insert({Cuts, 0.0});
  }
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void FillingRecoCountingMapAdd( RECO_Cut_Map &OutputMap, ECuts input)
{
    OutputMap.insert({input, 0.0});

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void FillingTruthCountingMap(std::vector<ECutsTRUTH> inputTRUTHCuts, TRUE_Cut_Map &OutputMap)
{
  for(auto Cuts : inputTRUTHCuts){
    OutputMap.insert({Cuts, 0.0});
  }
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

TRUE_Cut_Map ConstuctTRUTHCountingMap(std::vector<ECutsTRUTH> inputTRUECuts){
  TRUE_Cut_Map OutputMap;
  for(auto inputCut : inputTRUECuts){
    OutputMap.insert({inputCut, 0.0});

  }

}// ENd of function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void FillRECO_CutMap_FromTGraph(TGraph *TGraph_RECO_CUTS , RECO_Cut_Map &FillMap){
  int NPoints = TGraph_RECO_CUTS->GetN();
  double_t x,y;
  for(int i=0;i < NPoints; ++i){

    TGraph_RECO_CUTS->GetPoint(i, x, y);
    int yy = y;
    //double xx = x;
    ECuts CutType_ECuts = static_cast<ECuts>(x);
    //double NEvents = TGraph_RECO_CUTS->GetPointY(i);
    FillMap.insert(std::pair<ECuts,double>(CutType_ECuts,yy));

  }

}//end of function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void ScaleCutMap( RECO_Cut_Map &Map , double POTscaler){
  for(auto cuts : Map){
    double ScaledValue = cuts.second * POTscaler;
    Map[cuts.first] = ScaledValue;
  }//end of function

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void FillTRUTH_CutMap_FromTGraph(TGraph *TGraph_TRUTH_CUTS , TRUE_Cut_Map &FillMap){
  int NPoints = TGraph_TRUTH_CUTS->GetN();
  double_t x,y;
  for(int i=0;i < NPoints; i++){


    TGraph_TRUTH_CUTS->GetPoint(i, x, y);
    int yy = y;
    //int CutType =  TGraph_TRUTH_CUTS->GetPointX(i);
    ECutsTRUTH CutType_ECuts = static_cast<ECutsTRUTH>(x);
    //double NEvents = TGraph_TRUTH_CUTS->GetPointY(i);
    //FillMap.insert({CutType_ECuts, yy});
    FillMap.insert(std::pair<ECutsTRUTH,double>(CutType_ECuts,yy));
  }

}//end of function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void  MakeEventCut_Rate_STRUCT_fromTFiles(EventCut_Rate_STRUCT &RETURN_Event_STRUCT,
  TFile *inputFile_TRUTHBranch,  char* TGraphName_TRUTHBranch,
  TFile *inputFile_RECOBranch,  char* TGraphName_RECOBranch_TRUE ,  char* TGraphName_RECOBranch_TRUE_RECO,
  ME_helium_Playlists playlist, ME_helium_Status Crytank_status){


    RETURN_Event_STRUCT.RECOBRANCH_TGraph_RECO_TRUTH_name=TGraphName_RECOBranch_TRUE_RECO;
    RETURN_Event_STRUCT.RECOBRANCH_TGraph_RECO_name=TGraphName_RECOBranch_TRUE;
    RETURN_Event_STRUCT.TRUTHBRANCH_TGraph_name=TGraphName_TRUTHBranch;
    RETURN_Event_STRUCT.playlist = playlist;
    RETURN_Event_STRUCT.Crytank_status = Crytank_status;

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    ///FILL TRUTH CUTS EVENT Rate FROM TRUTHBRANCH
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    TGraph *TGraph_TRUTHBRANCH_TRUECUTS = (TGraph*)inputFile_TRUTHBranch -> Get(TGraphName_TRUTHBranch);
    TRUE_Cut_Map TRUTHBranch_TRUE_CutMap;
    FillTRUTH_CutMap_FromTGraph(TGraph_TRUTHBRANCH_TRUECUTS , TRUTHBranch_TRUE_CutMap);
    RETURN_Event_STRUCT.TRUTHBRANCH_TRUE_EVENTSECTION_MAP = TRUTHBranch_TRUE_CutMap ;
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //////FILL TRUTH CUTS EVENT Rate RECO BRANCH
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    TGraph *TGraph_RECOBRANCH_TRUECUTS = (TGraph*)inputFile_RECOBranch -> Get(TGraphName_RECOBranch_TRUE);
    TRUE_Cut_Map RECOBranch_TRUECutMap;
    FillTRUTH_CutMap_FromTGraph(TGraph_RECOBRANCH_TRUECUTS, RECOBranch_TRUECutMap);
    RETURN_Event_STRUCT.RECOBRANCH_TRUE_EVENTSECTION_MAP = RECOBranch_TRUECutMap;


    TGraph *TGraph_RECOBRANCH_TRUE_RECOCUTS = (TGraph*)inputFile_RECOBranch -> Get(TGraphName_RECOBranch_TRUE_RECO);
    RECO_Cut_Map RECOBranch_TRUE_RECO_CutMap;
    FillRECO_CutMap_FromTGraph(TGraph_RECOBRANCH_TRUE_RECOCUTS, RECOBranch_TRUE_RECO_CutMap);
    RETURN_Event_STRUCT.RECOBRANCH_TRUE_RECO_EVENTSECTION_MAP = RECOBranch_TRUE_RECO_CutMap;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void Fill_MnvReponse_ErrorUniv_Hist_numbers(error_name_Univ_MvnHistMap &MnvReponse_Hist_N_Map, error_name_Map  Universe_map_input){
int count=0;
  for(auto Universe_Band :Universe_map_input){
    auto Universe_vector_size = Universe_Band.second;
    for(int i = 0; i < Universe_vector_size; i++){
       MnvReponse_Hist_N_Map.insert(std::pair<int ,int >( count, i) );
      count++;
    }
  }

}//
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void Subtract_FullHist(MnvH1D &hist_Full, MnvH1D *hist_Empty){
  MnvH1D* hist_Empty_clone = (MnvH1D*) hist_Empty->Clone("hist_Empty_clone");
  hist_Full.Add(hist_Empty_clone ,-1);
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void Subtract_FullHist(MnvH2D &hist_Full, MnvH2D *hist_Empty){
  MnvH2D* hist_Empty_clone = (MnvH2D*) hist_Empty->Clone("hist_Empty_clone");
  hist_Full.Add(hist_Empty_clone,-1);
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
double GetYMaxfrombin1( MnvH2D *hist){

  MnvH1D *h_projection = hist->ProjectionY("h_projection",1,1,"");
  double Max=h_projection->GetMaximum();
  return Max;

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
float Purity_eff_error(double A, double A_error, double B, double B_error){
  double C = A*B;
  double C_error =  sqrt(pow(A_error/A,2) + pow(B_error/B,2));
  return C*C_error;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::vector<double> GetXBinningfrom2DHist(MnvH2D *hist){
  int Nbins = hist->GetNbinsX()+1;
  int bin1 = 1;
  std::vector<double> Bin_vector;
  for(int i = bin1; i <= Nbins; ++i ){
    double bin = hist->GetXaxis()->GetBinLowEdge(i);
    //std::cout<<"bin("<<i<<") = " << bin<<std::endl;
    Bin_vector.push_back(bin);
  }
  return Bin_vector;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::vector<double> GetYBinningfrom2DHist(MnvH2D *hist){
  int Nbins = hist->GetNbinsY()+1;
  int bin1 = 1;
  std::vector<double> Bin_vector;
  for(int i = bin1; i <= Nbins; ++i ){
    double bin = hist->GetYaxis()->GetBinLowEdge(i);
    //std::cout<<"bin("<<i<<") = " << bin<<std::endl;
    Bin_vector.push_back(bin);
  }
  return Bin_vector;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::vector<double> GetXBinningfrom1DHist(MnvH1D *hist, bool includeFlows){
  int first_bin = includeFlows ? 0 : 1;
  int last_bin = includeFlows ? hist->GetNbinsX()+1 : hist->GetNbinsX();
  std::vector<double> Bin_vector;
  for(int i = first_bin; i <= last_bin; ++i ){
    double bin = hist->GetXaxis()->GetBinLowEdge(i);
    //std::cout<<"bin("<<i<<") = " << bin<<std::endl;
    Bin_vector.push_back(bin);
  }
  return Bin_vector;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

std::vector<double> GetYContentfrom1DHist(MnvH1D *hist, bool includeFlows){
  int first_bin = includeFlows ? 0 : 1;
  int last_bin = includeFlows ? hist->GetNbinsX()+1 : hist->GetNbinsX();
  std::vector<double> Bin_vector;
  for(int i = first_bin; i <= last_bin; ++i ){
    double bin = hist->GetBinContent(i);
    //std::cout<<"bin("<<i<<") = " << bin<<std::endl;
    Bin_vector.push_back(bin);
  }
  return Bin_vector;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::vector<double> GetSignificance(std::vector<double> signal , std::vector<double> background ){
  std::vector<double> Significance;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~Get Significance~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

  if(signal.size() != background.size()){std::cout<<"Vector not equal in:GetSignificance ERROR "<<std::endl; assert(false);}
  for(int i = 0 ; i < signal.size();++i)
  {
    double s = signal.at(i);
    double b = background.at(i);
    double sign = s / sqrt(s+b);

    if (isnan(sign)==true) {
      sign =0.0;
    }
    std::cout<< "bin (" <<i<<" ) Significance = " << sign<<std::endl;

    Significance.push_back(sign);
  }

  return Significance;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::vector<double> GetSignificanceError(std::vector<double> signal , std::vector<double> background ){
  std::vector<double> Significance_error_vector;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~Get Significance~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

  if(signal.size() != background.size()){std::cout<<"Vector not equal in:GetSignificance ERROR "<<std::endl; assert(false);}
  for(int i = 0 ; i < signal.size();++i)
  {
    double s = signal.at(i);
    double b =  background.at(i);

    double error = 0.5 *  sqrt( (s * (4 * b + s) ) / pow((b + s),2 ) );

    if (isnan(error)==true) {
      error =0.0;
    }
    std::cout<< "bin (" <<i<<" ) Significance  Error = " << error<<std::endl;
    Significance_error_vector.push_back(error);
  }

  return Significance_error_vector;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
TH2D *ReturnTH2D_Migration_SingleCellBins(MnvH2D *hist, bool includeFlows){

  int first_bin = includeFlows ? 0 : 1;
  int last_bin = includeFlows ? hist->GetNbinsX()+1 : hist->GetNbinsX();
  Int_t nbins = includeFlows ? hist->GetNbinsX()+2 : hist->GetNbinsX();

  std::vector<double> SingleBins = MakeBinVector(nbins, 0, nbins);
  TH2D *h_tmp         =     new TH2D("h_tmp", "h_tmp",  SingleBins.size()-1,  SingleBins.data(), SingleBins.size()-1, SingleBins.data());

// Assumming the 2d his is square

for(int i =first_bin; i <=last_bin;++i){
  for(int j =first_bin; j <=last_bin;++j){

    auto  bin_content = hist->GetBinContent(i,j);

    if(bin_content < .00001 || isnan(bin_content)==true || isinf(bin_content)==true){
    //h_tmp->SetBinContent (i, j, 0.0);
    }

    else{ h_tmp->SetBinContent (i, j, bin_content);}

  }
}

return h_tmp;

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
TH2D *ReturnTH2D_Migration_removeZeros(MnvH2D *hist, bool includeFlows){

  int first_binX = includeFlows ? 0 : 1;
  int last_binX = includeFlows ? hist->GetNbinsX()+1 : hist->GetNbinsX();
  Int_t nbinsX = includeFlows ? hist->GetNbinsX()+2 : hist->GetNbinsX();

  int first_binY = includeFlows ? 0 : 1;
  int last_binY = includeFlows ? hist->GetNbinsY()+1 : hist->GetNbinsY();
  Int_t nbinsY = includeFlows ? hist->GetNbinsY()+2 : hist->GetNbinsY();


  std::vector<double> Bin_vectorX = GetXBinningfrom2DHist(hist);
  std::vector<double> Bin_vectorY = GetYBinningfrom2DHist(hist);

  TH2D *h_tmp = new TH2D("h_tmp", "h_tmp",  Bin_vectorX.size()-1,  Bin_vectorX.data(), Bin_vectorY.size()-1, Bin_vectorY.data());
  for(int i =first_binX; i <=last_binX;++i){
    for(int j =first_binY; j <=last_binY;++j){

      auto  bin_content = hist->GetBinContent(i,j);

      if(bin_content == 0 || isnan(bin_content) == true || isinf(bin_content)==true){
        // Skip and leave entry blank to remove zeros
      }

      else{
        h_tmp->SetBinContent (i, j, bin_content);
      }
    }
  }

  return h_tmp;

}// End of function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
TH2D *ReturnTH2D_removeZeros(MnvH2D *hist, bool includeFlows){

  int first_binX = includeFlows ? 0 : 1;
  int last_binX = includeFlows ? hist->GetNbinsX()+1 : hist->GetNbinsX();
  int first_binY = includeFlows ? 0 : 1;
  int last_binY = includeFlows ? hist->GetNbinsY()+1 : hist->GetNbinsY();



  std::vector<double> Bin_vectorX = GetXBinningfrom2DHist(hist);
  std::vector<double> Bin_vectorY = GetYBinningfrom2DHist(hist);

  TH2D *h_tmp = new TH2D("h_tmp", "h_tmp",  Bin_vectorX.size()-1,  Bin_vectorX.data(), Bin_vectorY.size()-1, Bin_vectorY.data());
  for(int i =first_binX; i <=last_binX;++i){
    for(int j =first_binY; j <=last_binY;++j){

      auto  bin_content = hist->GetBinContent(i,j);

      if(bin_content == 0 || isnan(bin_content) == true || isinf(bin_content)==true){
        // Skip and leave entry blank to remove zeros
      }

      else{
        h_tmp->SetBinContent (i, j, bin_content);
      }
    }
  }

  return h_tmp;

}// End of function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

void BinByBinMuplication_byVector(MnvH1D& hist, std::vector<double> vector , bool includeFlows )
{
  int first_bin = includeFlows ? 0 : 1;
  int last_bin = includeFlows ? hist.GetNbinsX()+1 : hist.GetNbinsX();
  if(vector.size() != last_bin ){std::cout<<"Error Number of bins not matching "<< std::endl; assert(false);}

  for(int row = first_bin; row <= last_bin; ++row)
  { int Vectorbin_index;
    if(includeFlows==true){Vectorbin_index = row;}
    else if (includeFlows==false) {Vectorbin_index = row-1;}
    double factor = vector.at(Vectorbin_index);

    hist.SetBinContent(row, hist.GetBinContent(row)* factor);
  }
}
////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////
int CantorPair(int x, int y ){
  int SingleValue = (x*x + 3*x + 2* x*y + y + y*y) / 2;
  return SingleValue;

}//end
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void FillOffSetMap(VertexOffSet_Map &OffSet_Map, double NegZ_offset, double PosZ_offset,
   int NumZSteps,double NegR_offset, double PosR_offset,  int NumRSteps ){

  std::vector<double> Z_offsetVector = MakeBinVector(NumZSteps, NegZ_offset, PosZ_offset);
  std::vector<double> R_offsetVector = MakeBinVector(NumRSteps, NegR_offset, PosR_offset);

  for(int i = 0; i < Z_offsetVector.size(); ++i ){
    double Z_offSet = Z_offsetVector.at(i);
    for(int j = 0; j < R_offsetVector.size(); ++j ){
      double R_offSet = R_offsetVector.at(j);
      int input_int = CantorPair(i, j);
      OffSet_Map.insert(std::make_pair(input_int, std::make_pair(R_offSet, Z_offSet)));
    }
  }
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void FillXYZOffSetMap(XYZ_VertexOffSet_Map &OffSet_Map, double NegX_offset, double PosX_offset,
    int NumXSteps, double NegY_offset, double PosY_offset,  int NumYSteps,
     double NegZ_offset, double PosZ_offset, int NumZSteps , bool AddZeroOffset ){
// index xyz-> ijk
  std::vector<double> X_offsetVector = MakeBinVector(NumXSteps, NegX_offset, PosX_offset); // i
  std::vector<double> Y_offsetVector = MakeBinVector(NumYSteps, NegY_offset, PosY_offset); // j
  std::vector<double> Z_offsetVector = MakeBinVector(NumZSteps, NegZ_offset, PosZ_offset); // k

  for(int k = 0; k < Z_offsetVector.size(); ++k ){
    double Z_offSet = Z_offsetVector.at(k);
    for(int j = 0; j < Y_offsetVector.size(); ++j ){
      double Y_offSet = Y_offsetVector.at(j);
      for(int i = 0; i < X_offsetVector.size(); ++i ){
        double X_offSet = X_offsetVector.at(i);
        Index3 ijk{i,j,k};
        Vertex_XYZ offSet{X_offSet, Y_offSet, Z_offSet};
        OffSet_Map.insert(std::make_pair(ijk, offSet));
      } // end i
    } //end j
  }//end k

  if(AddZeroOffset==true){
    Vertex_XYZ offSet{0.0, 0.0, 0.0};
    Index3 ijk{X_offsetVector.size()+1,X_offsetVector.size()+1,X_offsetVector.size()+1};
    OffSet_Map.insert(std::make_pair(ijk, offSet));
  }


}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void AddZOffSettoSetMap(XYZ_VertexOffSet_Map &OffSet_Map, double ConstantX_offset, double ConstantY_offset,
  double NegZ_offset, double PosZ_offset, int NumZSteps,  bool AddZeroOffset )
  {
    std::vector<double> Z_offsetVector = MakeBinVector(NumZSteps, NegZ_offset, PosZ_offset); // k
    int index = 1;
    for(auto cat :  Z_offsetVector ){
      Index3 ijk{0,0,index};
      Vertex_XYZ offSet{ConstantX_offset, ConstantY_offset, cat};
      OffSet_Map.insert(std::make_pair(ijk, offSet));
      index++;
    }

    if(AddZeroOffset==true){
      Vertex_XYZ offSet{0.0, 0.0, 0.0};
      Index3 ijk{Z_offsetVector.size()+1,Z_offsetVector.size()+1,Z_offsetVector.size()+1};
      OffSet_Map.insert(std::make_pair(ijk, offSet));
    }

  }
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
  void FillXYZOffSetMapconstantY(XYZ_VertexOffSet_Map &OffSet_Map, double NegX_offset, double PosX_offset,
    int NumXSteps, double inputY, double NegZ_offset, double PosZ_offset, int NumZSteps , bool AddZeroOffset ){
// index xyz-> ijk
  std::vector<double> X_offsetVector = MakeBinVector(NumXSteps, NegX_offset, PosX_offset); // i
  std::vector<double> Y_offsetVector{inputY};
  std::vector<double> Z_offsetVector = MakeBinVector(NumZSteps, NegZ_offset, PosZ_offset); // k

  for(int k = 0; k < Z_offsetVector.size(); ++k ){
    double Z_offSet = Z_offsetVector.at(k);
    for(int j = 0; j < Y_offsetVector.size(); ++j ){
      double Y_offSet = Y_offsetVector.at(j);
      for(int i = 0; i < X_offsetVector.size(); ++i ){
        double X_offSet = X_offsetVector.at(i);
        Index3 ijk{i,j,k};
        Vertex_XYZ offSet{X_offSet, Y_offSet, Z_offSet};
        OffSet_Map.insert(std::make_pair(ijk, offSet));
      } // end i
    } //end j
  }//end k

  if(AddZeroOffset==true){
    Vertex_XYZ offSet{0.0, 0.0, 0.0};
    Index3 ijk{X_offsetVector.size()+1,X_offsetVector.size()+1,X_offsetVector.size()+1};
    OffSet_Map.insert(std::make_pair(ijk, offSet));
  }
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void FillXYZOffSetMapconstantX(XYZ_VertexOffSet_Map &OffSet_Map, double inputX, double NegY_offset, double PosY_offset,  int NumYSteps,
     double NegZ_offset, double PosZ_offset, int NumZSteps , bool AddZeroOffset ){
// index xyz-> ijk
  std::vector<double> X_offsetVector{inputX};
  std::vector<double> Y_offsetVector = MakeBinVector(NumYSteps, NegY_offset, PosY_offset); // j
  std::vector<double> Z_offsetVector = MakeBinVector(NumZSteps, NegZ_offset, PosZ_offset); // k

  for(int k = 0; k < Z_offsetVector.size(); ++k ){
    double Z_offSet = Z_offsetVector.at(k);
    for(int j = 0; j < Y_offsetVector.size(); ++j ){
      double Y_offSet = Y_offsetVector.at(j);
      for(int i = 0; i < X_offsetVector.size(); ++i ){
        double X_offSet = X_offsetVector.at(i);
        Index3 ijk{i,j,k};
        Vertex_XYZ offSet{X_offSet, Y_offSet, Z_offSet};
        OffSet_Map.insert(std::make_pair(ijk, offSet));
      } // end i
    } //end j
  }//end k


  if(AddZeroOffset==true){
    Vertex_XYZ offSet{0.0, 0.0, 0.0};
    Index3 ijk{X_offsetVector.size()+1,X_offsetVector.size()+1,X_offsetVector.size()+1};
    OffSet_Map.insert(std::make_pair(ijk, offSet));
  }
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

void FillXYZOffSetMapconstantZ(XYZ_VertexOffSet_Map &OffSet_Map, double NegX_offset, double PosX_offset,
    int NumXSteps, double NegY_offset, double PosY_offset,  int NumYSteps,
     double inputZ , bool AddZeroOffset){
// index xyz-> ijk
std::vector<double> X_offsetVector = MakeBinVector(NumXSteps, NegX_offset, PosX_offset); // i
  std::vector<double> Y_offsetVector = MakeBinVector(NumYSteps, NegY_offset, PosY_offset); // j
  std::vector<double> Z_offsetVector{inputZ};
  for(int k = 0; k < Z_offsetVector.size(); ++k ){
    double Z_offSet = Z_offsetVector.at(k);
    for(int j = 0; j < Y_offsetVector.size(); ++j ){
      double Y_offSet = Y_offsetVector.at(j);
      for(int i = 0; i < X_offsetVector.size(); ++i ){
        double X_offSet = X_offsetVector.at(i);
        Index3 ijk{i,j,k};
        Vertex_XYZ offSet{X_offSet, Y_offSet, Z_offSet};
        OffSet_Map.insert(std::make_pair(ijk, offSet));
      } // end i
    } //end j
  }//end k


  if(AddZeroOffset==true){
    Vertex_XYZ offSet{0.0, 0.0, 0.0};
    Index3 ijk{X_offsetVector.size()+1,X_offsetVector.size()+1,X_offsetVector.size()+1};
    OffSet_Map.insert(std::make_pair(ijk, offSet));
  }
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

void FillXYZOffSetMapconstantXY(XYZ_VertexOffSet_Map &OffSet_Map, double inputX, double inputY,
     double NegZ_offset, double PosZ_offset, int NumZSteps , bool AddZeroOffset ){
// index xyz-> ijk
  std::vector<double> X_offsetVector{inputX};
  std::vector<double> Y_offsetVector{inputY};
  std::vector<double> Z_offsetVector = MakeBinVector(NumZSteps, NegZ_offset, PosZ_offset); // k

  for(int k = 0; k < Z_offsetVector.size(); ++k ){
    double Z_offSet = Z_offsetVector.at(k);
    for(int j = 0; j < Y_offsetVector.size(); ++j ){
      double Y_offSet = Y_offsetVector.at(j);
      for(int i = 0; i < X_offsetVector.size(); ++i ){
        double X_offSet = X_offsetVector.at(i);
        Index3 ijk{i,j,k};
        Vertex_XYZ offSet{X_offSet, Y_offSet, Z_offSet};
        OffSet_Map.insert(std::make_pair(ijk, offSet));
      } // end i
    } //end j
  }//end k

  if(AddZeroOffset==true){
    Vertex_XYZ offSet{0.0, 0.0, 0.0};
    Index3 ijk{X_offsetVector.size()+1,X_offsetVector.size()+1,X_offsetVector.size()+1};
    OffSet_Map.insert(std::make_pair(ijk, offSet));
  }

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

void FillConvolutionShiftMap(NormalParaFit_Map &ShiftMap, double stddev_start, double stddev_finish,
    int stddev_NSteps, double mean_start, double mean_finish, int mean_NSteps, bool AddZeroOffset){

      std::vector<double> stddev_Vector = MakeBinVector(stddev_NSteps, stddev_start, stddev_finish); // i
      std::vector<double> mean_Vector   = MakeBinVector(mean_NSteps, mean_start, mean_finish);// j

      for(int j = 0; j < stddev_Vector.size(); ++j ){
        double stddev = stddev_Vector.at(j);
        for(int i = 0; i < mean_Vector.size(); ++i ){
          double mean = mean_Vector.at(i);
          Index3 ijk{i,j,0};
          Normal_Fit_Parameters Parms{stddev, mean};
          ShiftMap.insert(std::make_pair(ijk, Parms));
        } // end i
      } //end j


      if(AddZeroOffset==true){
        Normal_Fit_Parameters Parms{0.0, 0.0};
        Index3 ijk{0,0,1};
        ShiftMap.insert(std::make_pair(ijk, Parms));
      }
    }
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void FillConvolutionShiftMapXY(NormalParaFit_XYMap &ShiftMap,
      double stddev_start_X, double stddev_finish_X,
      int stddev_NSteps_X, double mean_start_X,
      double mean_finish_X, int mean_NSteps_X,
      double stddev_start_Y, double stddev_finish_Y,
      int stddev_NSteps_Y, double mean_start_Y,
      double mean_finish_Y, int mean_NSteps_Y,
      bool AddZeroOffset){

  std::vector<double> stddev_Vector_X = MakeBinVector(stddev_NSteps_X, stddev_start_X, stddev_finish_X); // i
  std::vector<double> mean_Vector_X   = MakeBinVector(mean_NSteps_X, mean_start_X, mean_finish_X);// j

  std::vector<double> stddev_Vector_Y = MakeBinVector(stddev_NSteps_Y, stddev_start_Y, stddev_finish_Y); // i
  std::vector<double> mean_Vector_Y   = MakeBinVector(mean_NSteps_Y, mean_start_Y, mean_finish_Y);// j

  for(int j = 0; j < stddev_Vector_X.size(); ++j ){
    double stddev_X = stddev_Vector_X.at(j);
    for(int i = 0; i < mean_Vector_X.size(); ++i ){
      double mean_X = mean_Vector_X.at(i);
      for(int k = 0; k < stddev_Vector_Y.size(); ++k ){
        double stddev_Y = stddev_Vector_Y.at(k);
        for(int m = 0; m < mean_Vector_Y.size(); ++m ){
          double mean_Y = mean_Vector_Y.at(m);
          Index4 ijkm{i,j,k,m};
          Normal_Fit_Parameters ParmsX{stddev_X, mean_X};
          Normal_Fit_Parameters ParmsY{stddev_Y, mean_Y};
          Normal_Fit_ParametersXY inputMapXY;
          inputMapXY.insert(std::make_pair(kX, ParmsX));
          inputMapXY.insert(std::make_pair(kY, ParmsY));
          ShiftMap.insert(std::make_pair(ijkm, inputMapXY));
        } // end m
      } //end n
    } //end i
  } //end j

  if(AddZeroOffset==true){
    Normal_Fit_Parameters ParmsX{0.0, 0.0};
    Normal_Fit_Parameters ParmsY{0.0, 0.0};
    Index4 ijkm{mean_Vector_X.size(),stddev_Vector_X.size(),stddev_Vector_Y.size(),mean_Vector_Y.size()};
    Normal_Fit_ParametersXY inputMapXY;
    inputMapXY.insert(std::make_pair(kX, ParmsX));
    inputMapXY.insert(std::make_pair(kY, ParmsY));
    ShiftMap.insert(std::make_pair(ijkm, inputMapXY));
  }
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void FillOffSet_1DHistMap(MnvH1D_Map Hist_Map, int NBinZ, int NBinR, char *baseName , std::vector<double> Bins){

  char tempName[1024];

  for(int i = 0; i < NBinZ; ++i ){
    for(int j = 0; j < NBinR; ++j ){
      int input_int = CantorPair(i, j);
      sprintf(tempName,"%s_%d",baseName, input_int);
      PlotUtils::MnvH1D *hist = new PlotUtils::MnvH1D(tempName, tempName, Bins.size()-1,Bins.data());
      Hist_Map.insert(std::make_pair(input_int, hist ));
    }
  }
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void FillOffSet_MnvH1D_3indexMap(MnvH1D_3indexMap Hist_Map, int NBinX, int NBinY,
   int NBinZ, char *baseName , std::vector<double> Bins){

  char tempName[1024];

  for(int k = 0; k < NBinZ; ++k ){
    for(int j = 0; j < NBinY; ++j ){
      for(int i = 0; i < NBinX; ++i ){
        Index3 ijk{i,j,k};

        sprintf(tempName,"%s_i_j_k_%d_%d_%d",baseName, i,j,k);
        PlotUtils::MnvH1D *hist = new PlotUtils::MnvH1D(tempName, tempName, Bins.size()-1,Bins.data());
        Hist_Map.insert(std::make_pair(ijk, hist ));

      } // end i
    } //end j
  }//end k

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

void FillOffSet_2DHistMap(MnvH2D_Map Hist_Map, int NBinZ, int NBinR, char *baseName , std::vector<double> BinsX, std::vector<double> BinsY){

  char tempName[1024];

  for(int i = 0; i < NBinZ; ++i ){
    for(int j = 0; j < NBinR; ++j ){
      int input_int = CantorPair(i, j);
      sprintf(tempName,"%s_%d",baseName, input_int);
      PlotUtils::MnvH2D *hist = new PlotUtils::MnvH2D(tempName, tempName, BinsX.size()-1, BinsX.data(), BinsY.size()-1, BinsY.data());
      Hist_Map.insert(std::make_pair(input_int, hist ));
    }
  }

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void FillOffSet_MnvH2D_3indexMap(MnvH2D_3indexMap Hist_Map, int NBinX, int NBinY, int NBinZ, char *baseName , std::vector<double> BinsX, std::vector<double> BinsY){

  char tempName[1024];

  for(int k = 0; k < NBinZ; ++k ){
    for(int j = 0; j < NBinY; ++j ){
      for(int i = 0; i < NBinX; ++i ){
        Index3 ijk{i,j,k};

        sprintf(tempName,"%s_i_j_k_%d_%d_%d",baseName, i,j,k);
        PlotUtils::MnvH2D *hist = new PlotUtils::MnvH2D(tempName, tempName, BinsX.size()-1, BinsX.data(), BinsY.size()-1, BinsY.data());
        Hist_Map.insert(std::make_pair(ijk, hist ));

      } // end i
    } //end j
  }//end k

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////


void AddMnvH1D_Maps(MnvH1D_Map &Hist_MaptoAdd, MnvH1D_Map Hist_Map, int NBinZ, int NBinR){
  for(int i = 0; i < NBinZ; ++i ){
    for(int j = 0; j < NBinR; ++j ){
      int input_int = CantorPair(i, j);
      Hist_MaptoAdd[input_int]->Add(Hist_Map[input_int] , 1.0);
    }
  }
}
////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////
void AddMnvH2D_Maps(MnvH2D_Map &Hist_MaptoAdd, MnvH2D_Map Hist_Map, int NBinZ, int NBinR){
  for(int i = 0; i < NBinZ; ++i ){
    for(int j = 0; j < NBinR; ++j ){
      int input_int = CantorPair(i, j);
      Hist_MaptoAdd[input_int]->Add(Hist_Map[input_int] , 1.0);
    }
  }
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////


Index3 GetindexZeroShift(XYZ_VertexOffSet_Map inputmap){
  std::cout<<"Finding 0 offset"<<std::endl;
  typename std::map<Index3, Vertex_XYZ>::const_iterator dog;
  int mapcount =0;
  for ( dog = inputmap.begin(); dog != inputmap.end();++dog){

    std::cout<<" index = " << mapcount << " key (i,j,k) =  (" << dog->first.i <<" , "<< dog->first.j<< " , "<< dog->first.k  <<")   OffSet (x, y, z) =  (" << dog->second.x << ", " << dog->second.y<< " , "<< dog->second.z <<" ) "<<std::endl;

    if(dog->second.x == 0.0 && dog->second.y == 0.0 && dog->second.z == 0.0 ){
      Index3 returnIndex{dog->first.i, dog->first.j, dog->first.k};
      std::cout<<"Zero Off index  (ijk)= ("<< returnIndex.i<<", "<< returnIndex.j<<", "<<returnIndex.k<<") "<< std::endl;
      return returnIndex;
    }
    mapcount++;
  }
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////


double maximum(double a,double b,double c){
    double max = a;
    if(b>max)
        max = b;
    if(c>max)
        max = c;
    return max;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////



BinMap ConstuctBinMapNormal_Fit_Parameters(std::vector<double> mean_AxisBins ,std::vector<double> stddev_AxisBins ){
std::cout<< "inside ConstuctBinMapNormal_Fit_Parameters"<< std::endl;
  BinMap binmap_output;

  for(int i = 0 ;i < mean_AxisBins.size(); ++i ){
    for(int j = 0 ;j < stddev_AxisBins.size(); ++j ){
      Index2 input{i+1,j+1};
      std::cout<<"i , j "<< input.i <<", "<< input.j << std::endl;
      std::cout<<"mean_AxisBins.at(i) , stddev_AxisBins.at(j) "<< mean_AxisBins.at(i) <<", "<< stddev_AxisBins.at(j)<< std::endl;
      Normal_Fit_Parameters input_parameter{mean_AxisBins.at(i),stddev_AxisBins.at(j)};
      binmap_output.insert(std::pair<Normal_Fit_Parameters, Index2>(input_parameter,input));
    }
  }

return binmap_output;

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////



void  ConstuctBinMapNormal_Fit_Parameters(BinMap &inputmap, std::vector<double> &mean_AxisBins ,std::vector<double> &stddev_AxisBins ){
std::cout<< "inside ConstuctBinMapNormal_Fit_Parameters"<< std::endl;


  for(int i = 0 ;i < mean_AxisBins.size(); ++i ){
    for(int j = 0 ;j < stddev_AxisBins.size(); ++j ){
      Index2 input{i+1,j+1};
      std::cout<<"i , j "<< input.i <<", "<< input.j << std::endl;
      std::cout<<"mean_AxisBins.at(i) , stddev_AxisBins.at(j) "<< mean_AxisBins.at(i) <<", "<< stddev_AxisBins.at(j)<< std::endl;
      Normal_Fit_Parameters input_parameter;//{mean_AxisBins.at(i),stddev_AxisBins.at(j)};
      input_parameter.mean = mean_AxisBins.at(i);
      input_parameter.stddev = stddev_AxisBins.at(j);
      inputmap.insert(std::pair<Normal_Fit_Parameters, Index2>(input_parameter,input));

      std::cout<<"inputmap.size() = "<< inputmap.size()<<std::endl;

    }
  }
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

void BinNormalizeTOFractionOF_Events_mvnH1D(TObjArray &input_Array){

  int NEntries = input_Array.GetEntries();

  MnvH1D *TotalH = (PlotUtils::MnvH1D*)input_Array.At(0)->Clone("TotalH");

  for(int i = 1 ; i < NEntries; ++i){
    TotalH->Add((PlotUtils::MnvH1D*)input_Array.At(i),1.0);
  }
  for(int i = 0 ; i < NEntries; ++i){
    ((PlotUtils::MnvH1D*)input_Array.At(i))->Divide((PlotUtils::MnvH1D*)input_Array.At(i),TotalH);
  }


}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void  FillCutMap_fromTFiles(CutMap &inputMap, TFile *inputFile_TRUTHBranch,   TFile *inputFile_RECOBranch,
                             TFile *inputFile_DATABranch){

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  ///FILL TRUTH CUTS EVENT Rate FROM TRUTHBRANCH
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  std::cout<<"Making :: TGraph_TRUTHBRANCH_TRUECUTS::Name =  "<<inputMap.TRUTH_Tgraph_name<< std::endl;
  TGraph *TGraph_TRUTHBRANCH_TRUECUTS =  GetTGraph(*inputFile_TRUTHBranch, inputMap.TRUTH_Tgraph_name);
  TRUE_Cut_Map TRUTHBranch_TRUE_CutMap;
  FillTRUTH_CutMap_FromTGraph(TGraph_TRUTHBRANCH_TRUECUTS , TRUTHBranch_TRUE_CutMap);
  inputMap.MC_TRUTH_CutsMap = TRUTHBranch_TRUE_CutMap;

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //////FILL TRUTH CUTS EVENT Rate from RECO BRANCH
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  std::cout<<"Making :: TGraph_RECOBRANCH_TRUECUTS name ="<< inputMap.MCRecoBr_TRUE_Tgraph_name<<std::endl;
  TGraph *TGraph_RECOBRANCH_TRUECUTS = GetTGraph(*inputFile_RECOBranch,inputMap.MCRecoBr_TRUE_Tgraph_name);
  TRUE_Cut_Map RECOBranch_TRUECutMap;
  FillTRUTH_CutMap_FromTGraph(TGraph_RECOBRANCH_TRUECUTS, RECOBranch_TRUECutMap);
  inputMap.MCRecoBr_TRUTH_CutsMap = RECOBranch_TRUECutMap;

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //////FILL TRUTH + RECO CUTS EVENT Rate from RECO BRANCH
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    std::cout<<"Making :: TGraph_RECOBRANCH_TRUE_RECO_CUTSname = "<<inputMap.MCRecoBr_TRUE_RECO_Tgraph_name<< std::endl;
  TGraph *TGraph_RECOBRANCH_TRUE_RECO_CUTS = GetTGraph(*inputFile_RECOBranch,inputMap.MCRecoBr_TRUE_RECO_Tgraph_name);
  RECO_Cut_Map RECOBranch_TRUE_RECO_CutMap;
  FillRECO_CutMap_FromTGraph(TGraph_RECOBRANCH_TRUE_RECO_CUTS, RECOBranch_TRUE_RECO_CutMap);
  inputMap.MCRecoBr_TRUTH_RECO_CutsMap = RECOBranch_TRUE_RECO_CutMap;

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //////FILL RECO CUTS EVENT Rate from RECO BRANCH
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  std::cout<<"Making :: TGraph_RECOBRANCH_RECOCUTSname = "<<inputMap.RECO_Tgraph_name<< std::endl;
  TGraph *TGraph_RECOBRANCH_RECOCUTS = GetTGraph(*inputFile_RECOBranch,inputMap.RECO_Tgraph_name);
  RECO_Cut_Map MC_RECO_CutMap_input;
  FillRECO_CutMap_FromTGraph(TGraph_RECOBRANCH_RECOCUTS, MC_RECO_CutMap_input);
  inputMap.MC_RECO_CutsMap = MC_RECO_CutMap_input;


  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //////FILL RECO  Helium CUTS EVENT Rate from RECO BRANCH
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  std::cout<<"Making :: TGraph_RECOBRANCH_RECOCUTSname = "<<inputMap.RECO_Helium_Tgraph_name<< std::endl;
  TGraph *TGraph_RECO_Helium_BRANCH_RECOCUTS = GetTGraph(*inputFile_RECOBranch, inputMap.RECO_Helium_Tgraph_name);
  RECO_Cut_Map MC_RECO_Helium_CutMap_input;
  FillRECO_CutMap_FromTGraph(TGraph_RECO_Helium_BRANCH_RECOCUTS, MC_RECO_Helium_CutMap_input);
  inputMap.MC_RECO_Helium_CutsMap = MC_RECO_Helium_CutMap_input;

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //////FILL DATA CUTS EVENT
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  std::cout<<"Making :: TGraph_DATABRANCH name ="<<inputMap.RECO_Tgraph_name <<std::endl;
  TGraph *TGraph_DATABRANCH = GetTGraph(*inputFile_DATABranch,inputMap.Data_Tgraph_name);
  RECO_Cut_Map DATA_CutMap;
  FillRECO_CutMap_FromTGraph(TGraph_DATABRANCH, DATA_CutMap);
  inputMap.DATA_CutsMap = DATA_CutMap;

return;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

void FILLPlaylist_PlaylistCutMap(CutMap &inputMap , ME_helium_Playlists Playlist){
  inputMap.Playlist = Playlist;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

void FILLNames_PlaylistCutMap(CutMap &inputMap, std::string DataName,  std::string RecoName, std::string RecoName_helium ,  std::string RecoBranch_TrueRECOName, std::string RecoBranch_TrueName,  std::string TruthName){
  inputMap.Data_Tgraph_name =DataName;
  inputMap.RECO_Tgraph_name = RecoName;
  inputMap.RECO_Helium_Tgraph_name = RecoName_helium;
  inputMap.MCRecoBr_TRUE_RECO_Tgraph_name = RecoBranch_TrueRECOName;
  inputMap.MCRecoBr_TRUE_Tgraph_name = RecoBranch_TrueName;
  inputMap.TRUTH_Tgraph_name = TruthName;

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

void FILLPlaylist_PlaylistCutMap(CutMap &inputMap , ME_helium_Status Crytank_status_input){
  inputMap.Crytank_status = Crytank_status_input;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////


void FillCutMapPlaylists(Playlist_CutMap &inputMap, std::vector<ME_helium_Playlists> vectorPlaylist){

for(auto cat : vectorPlaylist){
CutMap input;
input.Playlist = cat;
input.Crytank_status =  GetPlaylist_HeliumStatus(cat);

inputMap.insert ( std::pair<ME_helium_Playlists, CutMap>(cat, input) );

}

  return;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////


void FillCutMapPlaylists(Playlist_CutMap &inputMap,std::string DataName,  std::string RecoName, std::string RecoName_Helium,  std::string RecoBranch_TrueRECOName, std::string RecoBranch_TrueName, std::string TruthName ){
  for(auto SingleMap_iter = inputMap.begin();  SingleMap_iter !=inputMap.end(); ++SingleMap_iter){
    FILLNames_PlaylistCutMap(SingleMap_iter->second,  DataName,   RecoName, RecoName_Helium, RecoBranch_TrueRECOName, RecoBranch_TrueName,  TruthName);
  }

  return;
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

void AddtoRECO_Cut_Map(RECO_Cut_Map &AddtooMap, RECO_Cut_Map &inputMap){
  for(auto AddTOMap = AddtooMap.begin(), AddMap = inputMap.begin(); AddTOMap != AddtooMap.end(); ++AddTOMap,++AddMap ){
    if(AddTOMap->first != AddMap ->first){std::cout<<"Maps are different Cuts, Something is wrong in function:: AddtoRECO_Cut_Map "<<std::endl; assert(false);}
    AddTOMap->second = AddTOMap->second + AddMap->second;
  }
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

void Scale_Cut_Map(RECO_Cut_Map &CutMap, double Scaler){
  for(auto Cut = CutMap.begin(); Cut != CutMap.end(); ++Cut ){
    Cut->second *= Scaler;
  }
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

void Scale_Cut_Map(TRUE_Cut_Map &CutMap, double Scaler){
  for(auto Cut = CutMap.begin(); Cut != CutMap.end(); ++Cut ){
    Cut->second *= Scaler;
  }
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

void Subtract_Cut_Map(RECO_Cut_Map &CutMap_SubtractFrom, RECO_Cut_Map &CutMap_Subtract){

  for(auto SubtractFrom = CutMap_SubtractFrom.begin(), Subtract = CutMap_Subtract.begin(); SubtractFrom != CutMap_SubtractFrom.end(); ++SubtractFrom, ++Subtract ){
    SubtractFrom->second = SubtractFrom->second - Subtract->second;
  }

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

void ADDCUT_same_Cut_Map(RECO_Cut_Map &CutMap_SubtractFrom, ECuts MissingCut , ECuts LetCutEqual){
CutMap_SubtractFrom.insert(std::pair<ECuts,double>{MissingCut, CutMap_SubtractFrom[LetCutEqual]});
}

void ADDCUT_same_Cut_Map_RECO(CutMap &inputMap, ECuts MissingCut , ECuts LetCutEqual){

ADDCUT_same_Cut_Map(inputMap.MC_RECO_CutsMap,  MissingCut ,  LetCutEqual);
ADDCUT_same_Cut_Map(inputMap.MC_RECO_Helium_CutsMap,  MissingCut ,  LetCutEqual);
ADDCUT_same_Cut_Map(inputMap.DATA_CutsMap,  MissingCut ,  LetCutEqual);

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

void ADDCUT_same_Cut_Map_Data(CutMap &inputMap, ECuts MissingCut , ECuts LetCutEqual){
ADDCUT_same_Cut_Map(inputMap.DATA_CutsMap,  MissingCut ,  LetCutEqual);
}


void Subtract_Cut_Map(TRUE_Cut_Map &CutMap_SubtractFrom, TRUE_Cut_Map &CutMap_Subtract){
  for(auto SubtractFrom = CutMap_SubtractFrom.begin(), Subtract = CutMap_Subtract.begin(); SubtractFrom != CutMap_SubtractFrom.end(); ++SubtractFrom, ++Subtract ){
    SubtractFrom->second = SubtractFrom->second - Subtract->second;
  }

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////


void SubTract_Cut_Map(CutMap &CutMap_SubtractFrom, CutMap &CutMap_Subtract){
  Subtract_Cut_Map(CutMap_SubtractFrom.DATA_CutsMap, CutMap_Subtract.DATA_CutsMap);
  Subtract_Cut_Map(CutMap_SubtractFrom.MC_RECO_CutsMap, CutMap_Subtract.MC_RECO_CutsMap);
  Subtract_Cut_Map(CutMap_SubtractFrom.MC_RECO_Helium_CutsMap, CutMap_Subtract.MC_RECO_Helium_CutsMap);
  Subtract_Cut_Map(CutMap_SubtractFrom.MCRecoBr_TRUTH_RECO_CutsMap, CutMap_Subtract.MCRecoBr_TRUTH_RECO_CutsMap);
  Subtract_Cut_Map(CutMap_SubtractFrom.MCRecoBr_TRUTH_CutsMap, CutMap_Subtract.MCRecoBr_TRUTH_CutsMap);
  Subtract_Cut_Map(CutMap_SubtractFrom.MC_TRUTH_CutsMap, CutMap_Subtract.MC_TRUTH_CutsMap);

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////



void Scale_CutMap(CutMap &inputMap, double scale_MC_TO_Data, double scale_DATA){

  Scale_Cut_Map(inputMap.DATA_CutsMap, scale_DATA);
  Scale_Cut_Map(inputMap.MC_RECO_CutsMap, scale_MC_TO_Data);
  Scale_Cut_Map(inputMap.MC_RECO_Helium_CutsMap, scale_MC_TO_Data);
  Scale_Cut_Map(inputMap.MCRecoBr_TRUTH_RECO_CutsMap, scale_MC_TO_Data);
  Scale_Cut_Map(inputMap.MCRecoBr_TRUTH_CutsMap, scale_MC_TO_Data);
  Scale_Cut_Map(inputMap.MC_TRUTH_CutsMap, scale_MC_TO_Data);

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

void Scale_CutMap(CutMap &inputMap, double scale_MC_TO_Data){

  Scale_Cut_Map(inputMap.MC_RECO_CutsMap, scale_MC_TO_Data);
  Scale_Cut_Map(inputMap.MC_RECO_Helium_CutsMap, scale_MC_TO_Data);
  Scale_Cut_Map(inputMap.MCRecoBr_TRUTH_RECO_CutsMap, scale_MC_TO_Data);
  Scale_Cut_Map(inputMap.MCRecoBr_TRUTH_CutsMap, scale_MC_TO_Data);
  Scale_Cut_Map(inputMap.MC_TRUTH_CutsMap, scale_MC_TO_Data);

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void PrintCutMapMaptoScreen(RECO_Cut_Map inputMap){
std::cout<<"Size of Map :"<< inputMap.size()<<std::endl;
  std::cout<< "Cut Name :  NEvent"<<std::endl;
  for(auto inter = inputMap.begin(); inter != inputMap.end(); ++inter){
    std::cout<<  GetCutName(inter->first) << inter->second << std::endl;
  }
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

void PrintCutMapMaptoScreen(TRUE_Cut_Map inputMap){
  std::cout<<"Size of Map :"<< inputMap.size()<<std::endl;
  std::cout<< "Cut Name :  NEvent"<<std::endl;
  for(auto inter = inputMap.begin(); inter != inputMap.end(); ++inter){
    std::cout<<  GetCutNameTRUTH(inter->first) << inter->second << std::endl;
  }
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

void AddtoTRUTH_Cut_Map(TRUE_Cut_Map &AddtooMap, TRUE_Cut_Map &inputMap){
  for(auto AddTOMap = AddtooMap.begin(), AddMap = inputMap.begin(); AddTOMap != AddtooMap.end(); ++AddTOMap,++AddMap ){
    if(AddTOMap->first != AddMap ->first){std::cout<<"Maps are different Cuts, Something is wrong in function:: AddtoRECO_Cut_Map "<<std::endl; assert(false);}
    AddTOMap->second = AddTOMap->second + AddMap->second;
  }
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

void CombinedCutMap(CutMap &Combined , Playlist_CutMap inputMap, std::vector<ME_helium_Playlists> Playlists_ToLoop, ME_helium_Playlists PlaylistStart ){

  RECO_Cut_Map DATA_CutsMap_new;
  RECO_Cut_Map MC_RECO_CutsMap_new;
  RECO_Cut_Map MC_RECO_Helium_CutsMap_new;
  RECO_Cut_Map MCRecoBr_TRUTH_RECO_CutsMap_new;
  TRUE_Cut_Map MCRecoBr_TRUTH_CutsMap_new;
  TRUE_Cut_Map MC_TRUTH_CutsMap_new;

  DATA_CutsMap_new = inputMap[PlaylistStart].DATA_CutsMap;
  MC_RECO_CutsMap_new = inputMap[PlaylistStart].MC_RECO_CutsMap;
  MC_RECO_Helium_CutsMap_new = inputMap[PlaylistStart].MC_RECO_Helium_CutsMap;
  MCRecoBr_TRUTH_RECO_CutsMap_new = inputMap[PlaylistStart].MCRecoBr_TRUTH_RECO_CutsMap;
  MCRecoBr_TRUTH_CutsMap_new = inputMap[PlaylistStart].MCRecoBr_TRUTH_CutsMap;
  MC_TRUTH_CutsMap_new = inputMap[PlaylistStart].MC_TRUTH_CutsMap;


  for(auto Playlist : Playlists_ToLoop){
    if(Playlist==PlaylistStart)continue;

    AddtoRECO_Cut_Map(DATA_CutsMap_new, inputMap[Playlist].DATA_CutsMap);
    AddtoRECO_Cut_Map(MC_RECO_CutsMap_new, inputMap[Playlist].MC_RECO_CutsMap);
    AddtoRECO_Cut_Map(MC_RECO_Helium_CutsMap_new, inputMap[Playlist].MC_RECO_Helium_CutsMap);
    AddtoRECO_Cut_Map(MCRecoBr_TRUTH_RECO_CutsMap_new, inputMap[Playlist].MCRecoBr_TRUTH_RECO_CutsMap);
    AddtoTRUTH_Cut_Map(MCRecoBr_TRUTH_CutsMap_new, inputMap[Playlist].MCRecoBr_TRUTH_CutsMap);
    AddtoTRUTH_Cut_Map(MC_TRUTH_CutsMap_new, inputMap[Playlist].MC_TRUTH_CutsMap);

    Combined.DATA_CutsMap = DATA_CutsMap_new;
    Combined.MC_RECO_CutsMap = MC_RECO_CutsMap_new;
    Combined.MC_RECO_Helium_CutsMap = MC_RECO_Helium_CutsMap_new;
    Combined.MCRecoBr_TRUTH_RECO_CutsMap = MCRecoBr_TRUTH_RECO_CutsMap_new;
    Combined.MCRecoBr_TRUTH_CutsMap = MCRecoBr_TRUTH_CutsMap_new;
    Combined.MC_TRUTH_CutsMap = MC_TRUTH_CutsMap_new;

  }

}


CryoTank_REGIONS CryoZRegionBreakdown14(double VertexZ){

if(1750.00 > VertexZ){return Zregion1; }
else if (1750.00 < VertexZ && VertexZ < 2050.00 ){return Zregion2; }
else if (2050.00 < VertexZ && VertexZ <2250.00){return Zregion3; }
else if (2250.00< VertexZ && VertexZ <2450.0){return Zregion4; }
else if (2450.0< VertexZ && VertexZ <2650.0){return Zregion5; }
else if (2650.0< VertexZ && VertexZ <2850.0){return Zregion6; }
else if (2850.0< VertexZ && VertexZ <3000.0){return Zregion7; }
else if (3000.0< VertexZ && VertexZ <3200.0){return Zregion8; }
else if (3200.0< VertexZ && VertexZ <3400.0){return Zregion9; }
else if (3400.0< VertexZ && VertexZ <3650.0){return Zregion10; }
else if (3650.0 < VertexZ && VertexZ <3900.0){return Zregion11; }
else if (3900.0< VertexZ && VertexZ <4200.0){return Zregion12; }
else if (4200.0< VertexZ && VertexZ < 4350.0){return Zregion13; }
else if (4350.0 < VertexZ ){return Zregion14; }
else{
std::cout<<" Outside regions abounds something is wrong go fix!!"<< std::endl;
  assert(false);}
}



//1450, 1512.5, 1575, 1637.5, 1700, | 1797.1 (5) | 1894.2, 1991.3, 2088.4, |2139.59 (9)|, 2190.78, 2241.96, 2293.15, |2342.66(13)|, 2392.16, |2441.67(15)|, 2491.17, 2540.71, 2590.25, 2639.79, 2689.33, 2738.87, 2788.41, |2837.96(23)|, 2887.5, |2937.04(25)|, 2986.59, |3036.13(27)|, 3085.67, 3135.21, 3184.76, 3234.3, 3283.84, 3333.38, |3382.92(34)|, |3432.46(35)|, 3482, 3533.25, |3584.5(38)|, 3635.75, 3687.0, |3738.25(41)|, |3789.5(42)|, 3840.75, 3892, 3943.25, 3994.5, 4045.75, 4097, 4157.06, 4217.12, |4277.19(51)|, 4337.25
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

std::vector<CryoTank_REGIONS> CryoZRegionBreakdown14_vector(){


std::vector<CryoTank_REGIONS> vector{
Zregion1,
Zregion2,
Zregion3,
Zregion4,
Zregion5,
Zregion6,
Zregion7,
Zregion8,
Zregion9,
Zregion10,
Zregion11,
Zregion12,
Zregion13,
Zregion14};


return vector;

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////


std::string  GetRegionString(CryoTank_REGIONS region) {
  switch (region) {

    case  Zregion1:
    return "1";
    case  Zregion2:
    return "2";
    case  Zregion3:
    return "3";
    case  Zregion4:
    return "4";
    case  Zregion5:
    return "5";
    case  Zregion6:
    return "6";
    case  Zregion7:
    return "7";
    case  Zregion8:
    return "8";
    case  Zregion9:
    return "9";
    case Zregion10:
    return "10";
    case Zregion11:
    return "11";
    case Zregion12:
    return "12";
    case Zregion13:
    return "13";
    case Zregion14:
    return "14";

    default:
    std::cout << "ERROR: Region name!" << std::endl;
    return "";
  };

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

int  GetRegionint(CryoTank_REGIONS region) {
  switch (region) {

    case  Zregion1:
    return 1;
    case  Zregion2:
    return 2;
    case  Zregion3:
    return 3;
    case  Zregion4:
    return 4;
    case  Zregion5:
    return 5;
    case  Zregion6:
    return 6;
    case  Zregion7:
    return 7;
    case  Zregion8:
    return 8;
    case  Zregion9:
    return 9;
    case Zregion10:
    return 10;
    case Zregion11:
    return 11;
    case Zregion12:
    return 12;
    case Zregion13:
    return 13;
    case Zregion14:
    return 14;

    default:
    std::cout << "ERROR: Region name!" << std::endl;
    return 99;
  };

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////



OpenAngle OpenAngleType(double Angle){

if(Angle < 5){return kOAngle5; }
else if(Angle > 5 && Angle < 10){return  kOAngle10; }
else if(Angle > 10 && Angle < 15){return kOAngle15; }
else if(Angle > 15 && Angle < 20){return kOAngle20; }
else if(Angle > 20 && Angle < 25){return kOAngle25; }
else if(Angle > 25 && Angle < 30){return kOAngle30; }
else if(Angle > 30 && Angle < 45){return kOAngle45; }
else {return kOAngle60; }
}

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

FluxSlices returnRegionSliceType(double x, double y){
if(x >= 0.0 && y > 0.0){return kSlice1;}
else if(x <= 0.0 && y > 0.0){return kSlice2;}
else if(x <= 0.0 && y < 0.0){return kSlice3;}
else if(x >= 0.0 && y < 0.0){return kSlice4;}
else{
std::cout<< "x = "<< x << " y = "<< y << std::endl;
  assert(("Not returning a slice this should be impossible?!?!?", false));  }

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
double FunctionGetRadinUnitCircle(double y, double x){

    if(x > 0.0 && y > 0.0){return atan(y/x);}
    else if(x < 0.0 && y >= 0.0 ){return TMath::Pi() + atan(y/x) ;}
    else if(x < 0.0 && y < 0.0 ){return TMath::Pi() + atan(y/x) ;}
    else if(x > 0.0 && y < 0.0 ){return (2*TMath::Pi()) + atan(y/x) ;}
    else if(x == 0.0 && y > 0.0 ){return TMath::Pi()/2;}
    else if(x == 0.0 && y < 0.0 ){return -TMath::Pi()/2;}
    else if(x > 0.0 && y == 0.0 ){return 0.0;}
    else if(x < 0.0 && y == 0.0 ){return TMath::Pi();}
    else if(x == 0.0 && y == 0.0 ){return -999;}
    else {return -999;}

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
FluxSlices returnHeliumdaisyType(double Degs){

if(Degs < 180.0 && Degs > 150.0 ){return kheliumdaisy0; }
else if(Degs < 150.0 && Degs > 120.0){return kheliumdaisy1; }
else if(Degs < 120.0 && Degs > 90.0){return kheliumdaisy2; }
else if(Degs < 90.0 && Degs > 60.0){return kheliumdaisy3; }
else if(Degs < 60.0 && Degs > 30.0){return kheliumdaisy4; }
else if(Degs < 30.0 && Degs > 0.0){return kheliumdaisy5; }
else if(Degs < 360.0 && Degs > 330.0){return kheliumdaisy6;}
else if(Degs < 330.0 && Degs > 300.0){return kheliumdaisy7;}
else if(Degs < 300.0 && Degs > 270.0){return kheliumdaisy8;}
else if(Degs < 270.0 && Degs > 240.0){return kheliumdaisy9;}
else if(Degs < 240.0 && Degs > 210.0){return kheliumdaisy10;}
else if(Degs < 210.0 && Degs > 180.0){return kheliumdaisy11;}
else {assert(0 && "Outside of the Daisy type , something is wrong or input equals a bound");}
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////


FluxSlices returnHeliumdaisyType_inputRad( double rad){
double inputdeg = rad * 180.0 / TMath::Pi();
return returnHeliumdaisyType(inputdeg);

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

FluxSlices returnHeliumdaisyType_inputYX( double y, double x){
double rad = FunctionGetRadinUnitCircle( y,  x);
return returnHeliumdaisyType_inputRad(rad);
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////


int returnIntfromHeliumdaisyType(FluxSlices inputflux){

if( kheliumdaisy0==inputflux){return 0; }
else if(kheliumdaisy1==inputflux){return 1; }
else if(kheliumdaisy2==inputflux){return 2; }
else if(kheliumdaisy3==inputflux){return 3; }
else if(kheliumdaisy4==inputflux){return 4; }
else if(kheliumdaisy5==inputflux){return 5; }
else if(kheliumdaisy6==inputflux){return 6;}
else if(kheliumdaisy7==inputflux){return 7;}
else if(kheliumdaisy8==inputflux){return 8;}
else if(kheliumdaisy9==inputflux){return 9;}
else if(kheliumdaisy10==inputflux){return 10;}
else if(kheliumdaisy11==inputflux){return 11;}
else {assert(0 && "Outside of the Daisy type , something is wrong or input equals a bound");}
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////


void removeFirstNElements(std::vector<double>& vec,int N_remove) {
    if (vec.size() > N_remove) {
        // Check if the vector has at least 15 elements
        vec.erase(vec.begin(), vec.begin() + N_remove); // Erase first 15 elements
    } else {
        // Vector has less than 15 elements, clear the entire vector
        vec.clear();
    }
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

PlotUtils::MnvH1D* RebinMnvH1D(PlotUtils::MnvH1D* histo, const std::vector<double>& bins) {
  // Create a new histogram with the desired bin edges
  int nBinsNew = bins.size() - 1;
  PlotUtils::MnvH1D *histoNew = new PlotUtils::MnvH1D(histo->GetName(), histo->GetTitle(), bins.size() - 1, bins.data());

  // Loop over the original histogram bins and fill the rebinned histogram
  for (int i = 0; i <= histo->GetNbinsX() + 1; i++) {
    double binCenter = histo->GetBinCenter(i);
    double binContent = histo->GetBinContent(i);
    double binError = histo->GetBinError(i);
    int binNew = histoNew->GetXaxis()->FindBin(binCenter); // Find the corresponding bin in the new histogram
    histoNew->Fill(histo->GetBinCenter(i), histo->GetBinContent(i)); // Fill the new histogram
    histoNew->SetBinError(binNew, histo->GetBinError(i)); // Set the error for the new histogram
  }

  return histoNew;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
TH1D* Rebin(TH1D *histo, const std::vector<double>& bins) {
  // Create a new histogram with the desired bin edges
  int nBinsNew = bins.size() - 1;
  TH1D *histoNew = new TH1D(histo->GetName(), histo->GetTitle(), bins.size() - 1, bins.data());

  // Loop over the original histogram bins and fill the rebinned histogram
  for (int i = 0; i <= histo->GetNbinsX() + 1; i++) {
      double binCenter = histo->GetBinCenter(i);
      double binContent = histo->GetBinContent(i);
      double binError = histo->GetBinError(i);
      int binNew = histoNew->GetXaxis()->FindBin(binCenter); // Find the corresponding bin in the new histogram
      histoNew->Fill(histo->GetBinCenter(i), histo->GetBinContent(i)); // Fill the new histogram
      histoNew->SetBinError(binNew, histo->GetBinError(i)); // Set the error for the new histogram
  }

  return histoNew;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

void UnBinWidthNormalizeMnvH1D(PlotUtils::MnvH1D &histo) {
    int nBins = histo.GetNbinsX();
    for (int i = 1; i <= nBins; i++) {
        double binWidth = histo.GetBinWidth(i);
        double binContent = histo.GetBinContent(i);
        double binError = histo.GetBinError(i);
        double unnormalizedContent = binContent * binWidth;
        double unnormalizedError = binError * binWidth;
        histo.SetBinContent(i, unnormalizedContent);
        histo.SetBinError(i, unnormalizedError);
    }
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////


void UnBinWidthNormalizeTH1D(TH1D &histo) {
    int nBins = histo.GetNbinsX();
    for (int i = 1; i <= nBins; i++) {
        double binWidth = histo.GetBinWidth(i);
        double binContent = histo.GetBinContent(i);
        double binError = histo.GetBinError(i);
        double unnormalizedContent = binContent * binWidth;
        double unnormalizedError = binError * binWidth;
        histo.SetBinContent(i, unnormalizedContent);
        histo.SetBinError(i, unnormalizedError);
    }
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////


void WidthBinNormalize(TH2D &hist)
{
    // Get number of bins in x and y directions
    int nbinsx = hist.GetNbinsX();
    int nbinsy = hist.GetNbinsY();

    // Loop over all bins in the histogram
    for (int i = 1; i <= nbinsx; i++) {
        for (int j = 1; j <= nbinsy; j++) {

            // Get content and error of the bin
            double content = hist.GetBinContent(i, j);
            double error = hist.GetBinError(i, j);

            // Calculate the width of the bin in x and y directions
            double widthx = hist.GetXaxis()->GetBinWidth(i);
            double widthy = hist.GetYaxis()->GetBinWidth(j);

            // Calculate the area of the bin
            double area = widthx * widthy;

            // Normalize content and error by the bin area
            hist.SetBinContent(i, j, content / area);
            hist.SetBinError(i, j, error / area);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::vector<double> readDoublesFromFile( std::string &filename) {
    std::vector<double> result;
    std::ifstream inputFile(filename);

    if (inputFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line)) {
            double value = std::stod(line);
            result.push_back(value);
        }
        inputFile.close();
    } else {
        std::cout << "Failed to open the file: " << filename << std::endl;
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

std::map<int, std::vector<double>> ReadFileToMakeMap(std::vector<std::string> input_vector_string){
int Petal = 0;

std::map<int, std::vector<double>> outputMap;

for(auto filename: input_vector_string)
{
std::vector<double> input_vector =  readDoublesFromFile( filename);

outputMap.insert(std::make_pair(Petal, input_vector));
Petal++;
}


return outputMap;

}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////


std::map<int, Double_t*> convertMap(const std::map<int, std::vector<double>>& inputMap) {
    std::map<int, Double_t*> outputMap;

    for (const auto& pair : inputMap) {
        int key = pair.first;
        const std::vector<double>& values = pair.second;

        // Create a new Double_t array and copy the vector values
        Double_t* doubleArray = new Double_t[values.size()];
        for (size_t i = 0; i < values.size(); ++i) {
            doubleArray[i] = values[i];
        }

        // Add the Double_t array to the output map
        outputMap[key] = doubleArray;
    }

    return outputMap;
}


////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
Double_t* readFile(std::string& filename, int& size) {
    std::ifstream file(filename);

    if (file.is_open()) {
        Double_t num;
        size = 0;
        while (file >> num) {
            size++;
        }
        file.clear();
        file.seekg(0, std::ios::beg);

        Double_t* numbers = new Double_t[size];
        for (int i = 0; i < size; i++) {
            file >> numbers[i];
        }

        file.close();
        return numbers;
    } else {
        std::cout << "Failed to open file: " << filename << std::endl;
        size = 0;
        return nullptr;
    }
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

Double_t* readFile( char* filename, int& size) {
    std::ifstream file(filename);

    if (file.is_open()) {
        Double_t num;
        size = 0;
        while (file >> num) {
            size++;
        }
        file.clear();
        file.seekg(0, std::ios::beg);

        Double_t* numbers = new Double_t[size];
        for (int i = 0; i < size; i++) {
            file >> numbers[i];
        }

        file.close();
        return numbers;
    } else {
        std::cout << "Failed to open file: " << filename << std::endl;
        size = 0;
        return nullptr;
    }
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

int getSize(double* arr) {
    // Assuming the array is null-terminated
    int size = 0;
    while (arr[size] != 0.0) {
        size++;
    }
    return size;
}
