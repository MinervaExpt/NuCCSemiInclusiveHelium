
#include "VetoWall_Plots.h"
//////////////////////////////////////////////////////////////////////////////



void Kin(bool &cutsOn, bool &my_norm, bool &my_debug, const char *userDir) {

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~       Starting Plotter: CryoVertex Plots         ~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

const std::vector< ME_helium_Playlists> kPlayListVector = GetPlayListVector();
const std::vector<CryoVertex> kCryoVertexVaribles_vector = GetCryoVertexVaribles();

TCanvas *can = new TCanvas("can");
MnvPlotter *mnv_plot = new MnvPlotter();
 char text_title_pdf1[2024];
 char text_title_pdf2[2024];
 char text_title_pdf3[2024];
 char text_title_pdf4[2024];
time_t now = time(0);
tm *ltm = localtime(&now);
 char timeset[2024];
sprintf(timeset,"%i_%i_%i_%i",1 + ltm->tm_mon,ltm->tm_mday, ltm->tm_hour,ltm->tm_min);


sprintf(text_title_pdf1, "Plots_VETOWALL_%s.pdf(",timeset );
can -> Print(text_title_pdf1);
sprintf(text_title_pdf2, "Plots_VETOWALL_%s.pdf",timeset );
sprintf(text_title_pdf2, "Plots_VETOWALL_%s.pdf",timeset );
sprintf(text_title_pdf3, "Plots_VETOWALL_%s.pdf)",timeset );
sprintf(text_title_pdf4, "Plots_VETOWALL_%s",timeset );
//auto rootinputpathfile = "/minerva/app/users/cnguyen/cmtuser/Minerva_v21r1p1Helium/Ana/VetoWallStudies/scripts/ChainWrapper_FW_ME/eventselection/STACKS_Histograms_minervame1G_MC.root";
//auto minervame1A_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1A_MC.root";

//auto TO_Data = "/minerva/data/users/cnguyen/ME_DATA_EventSection_RootFiles/";

//auto minervame1P_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1P.root";
//auto minervame1A_MC_path = "/minerva/data/users/cnguyen/ME_MC_EventSection_RootFiles/Histograms_minervame1A.root";

//auto minervame1P_DATA_path = TO_Data + "Histograms_minervame1P_Data.root"
//auto minervame1A_DATA_path = TO_Data + "Histograms_minervame1A_Data.root"


//TFile *minervame1P_MC     = new TFile(minervame1P_MC_path);
//TFile *minervame1A_MC     = new TFile(minervame1A_MC_path);

//TFile *minervame1P_DATA     = new TFile(minervame1P_DATA_path);
//TFile *minervame1A_DATA     = new TFile(minervame1A_DATA_path);


std::string pdf = string(text_title_pdf4);


PlayList_INFO PlaylistMC_1P(kPlayListVector[0], true );
PlayList_INFO PlaylistDATA_1P(kPlayListVector[0], false );

std::string pathway =PlaylistMC_1P.GETROOT_Path();
std::string pathway_1 =PlaylistDATA_1P.GETROOT_Path();
ChainWrapper* mcchainPOT = makeChainWrapperPtr(pathway.c_str(), "Meta");
ChainWrapper* mcDATAPOT =makeChainWrapperPtr(pathway_1.c_str(), "Meta");
double mcPOT = GetPOT_local(mcchainPOT,"MC");
double mcPOT_data = GetPOT_local(mcDATAPOT);
std::cout<< "pot out "<< mcPOT<<std::endl;
std::cout<< "pot ou datat "<< mcPOT_data<<std::endl;
PlaylistMC_1P.PrintPlaylistName();
PlaylistMC_1P.PRINTROOT_Path();
PlaylistMC_1P.Set_Pot();
PlaylistMC_1P.PRINT_Pot();

PlaylistDATA_1P.Set_Pot();
PlaylistDATA_1P.PRINT_Pot();



/*
for(auto Vertex_vertex: kCryoVertexVaribles_vector ){
  auto histname = GetVertexCryoVarHistName(Vertex_vertex );
  int n = histname.length();
  char histname_char[n+1];
  strcpy( histname_char,histname.c_str());
  DrawCVAndError_FromTFile(minervame1P_MC, histname_char, histname_char ,GetVertexCryoVarAxisTitle(Vertex_vertex), pdf );
  DrawCVAndError_FromTFile(minervame1A_MC, histname_char, histname_char ,GetVertexCryoVarAxisTitle(Vertex_vertex), pdf );

}
*/







   std::cout << std::endl;
   std::cout << "Done WITH Stacks" << std::endl;
   can -> Print(text_title_pdf3);

}


//End of MainFuntion





/////////////////////////////////////////////
//Main Function
/////////////////////////////////////////////

 int main() {

bool cutsOn;
std::cout << "Run over cutsOn?  (0 = false, 1 = true) " << std::endl;
std::cin >> cutsOn;
std::cout << std::boolalpha << cutsOn << std::endl;

bool my_norm;
std::cout << "Which Normalization?  (0 = POT, 1 = relative equal areas) " << std::endl;
std::cin >> my_norm;
std::cout << std::boolalpha << my_norm << std::endl;

bool my_debug;
std::cout << "Run in Debug Mode? (0 = NO, 1 = YES) " << std::endl;
std::cin >> my_debug;
std::cout << std::boolalpha << my_debug << std::endl;

std::string input;
std::cout << "What is the name of the user? " << std::endl;
std::cin >> input;
std::cout << input << std::endl;

const char *inputFileLoc = input.c_str();

Kin(cutsOn, my_norm, my_debug, inputFileLoc);

return 0;

}



std::vector<ME_helium_Playlists> GetPlayListVector() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ME_helium_Playlists> Playlist;

  //Playlist.push_back(kME1G);
  Playlist.push_back(kME1P);
  Playlist.push_back(kME1A);

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
  CryoVertexVars.push_back(kZ);
  CryoVertexVars.push_back(kR);


  return CryoVertexVars;
//#endif
}
