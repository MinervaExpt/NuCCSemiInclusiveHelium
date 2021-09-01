#ifndef HELIUMUTILS_H
#define HELIUMUTILS_H

#include "TKey.h"
#include "TFile.h"
#include "HeliumCVUniverse.h"
#include "HeliumDefaults.h" // typedef UniverseMap
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
//#ifndef __CINT__
//#include "Variable.h"
//#endif // __CINT__


//==============================================================================
// Variable Binning
//==============================================================================

TArrayD GetBinArray(const std::string var_name);
void FillMC_F_E_RecoCutMap(RECO_Cut_Map &FULL,RECO_Cut_Map &EMPTY, RECO_Cut_Map &F_E, std::vector<ECuts> kCutsVector,double POT[]);
void SetHistColorScheme(PlotUtils::MnvH1D* h, const int type, const int color_scheme);
void Array1D(MnvH1D *hist[], int index, const char *baseName, const char *title, std::vector<double> Bins);
void SortArray(TArrayD&);
ME_helium_Playlists  GetPlaylist_FromString(std::string playlist);
TArrayD MakeUniformBinArray(int nbins, double min, double max);
TArrayD GetSortedArray(const TArrayD& );
TArrayD GetTArrayFromVec(const std::vector<double>& vec);
bool IFstatusFullreturntrue(ME_helium_Status input);
bool ISTrueIFPlayListHeliumFUll(ME_helium_Playlists playlist_name);
//void SetplaylistName(std::string playlist);//end
//void FillNormWeightsPars(std::string processing_name);
std::vector <double> MakeBinVector(int Nbins,double binStart,double binEnd);
std::string GetMuonVarTitleName(MuonVar playlist_name);
std::string GetMuonVarTitleNameFORLatex(MuonVar playlist_name);
std::string GetMuon_Figure_Title(MuonVar Var, ME_helium_Playlists playlist_nameFULL,ME_helium_Playlists playlist_nameEmpty  );
std::string  GetMuonVarHistName(MuonVar playlist_name);
std::string  GetMuonVarHist_DATAName(MuonVar playlist_name);
std::string  GetMuonUnitType(MuonVar playlist_name);
std::vector<double> GetBinMuonVector(MuonVar playlist_name);
std::vector<double> GetBinvertexVector(CryoVertex playlist_name);
std::string  GetVertexCryoTitleName(CryoVertex playlist_name);
std::string  GetFULLorEmpty(ME_helium_Status playlist_name);
std::string  GetsecondTrakHistName_DATA_Name(SecondTrkVar playlist_name);
std::string GetPlaylist_ROOT_path(std::string Name, bool is_mc );
std::string GetWeight_name(Weights kweight) ;
std::string String_EventSectionROOTPath_FORTRUTH( ME_helium_Playlists playlist_name,bool StatsOnly );
bool CheckifPlaylists_haveSameHeliumStatus(ME_playlist_TFileMAP TFile_MAP);
Pot_MapList Constuct_POT_playlistMap(ME_playlist_RootPathMAP RootPath_MAP, bool m_ismc);
Pot_MapList Constuct_POT_playlistMap(PlotUtils::POTCounter *pot_counter, ME_playlist_RootPathMAP RootPath_MAP);
Pot_MapList POT_ScalersMap(Pot_MapList inputPOTMap ,double POT_toScaleTOO );
void PrintPot_MapList(Pot_MapList inputPOTMap, const char* name  );
double GetPOT_local(PlotUtils::ChainWrapper* _chain,std::string name="Data");
Playlist_MnvH1D_Map Constuct_mvnH1DMap_FromME_playlist_TFileMAP(ME_playlist_TFileMAP TFile_Map, const char* name );
Playlist_MnvH2D_Map Constuct_mvnH2DMap_FromME_playlist_TFileMAP(ME_playlist_TFileMAP TFile_Map, const char* name );
Playlist_MnvH1D_Map Scale_MnvH1D_Map_usingPot_MapList(Playlist_MnvH1D_Map MnvH1D_Map , Pot_MapList ScalerMap, const char* name  );
Playlist_MnvH2D_Map Scale_MnvH2D_Map_usingPot_MapList(Playlist_MnvH2D_Map MnvH2D_Map , Pot_MapList ScalerMap , const char* name  );
PlotUtils::MnvH1D* Combine_Hists_fromMAP(Playlist_MnvH1D_Map MnvH1D_Map , ME_helium_Playlists ADDtothisHis ,const char* name);
PlotUtils::MnvH2D* Combine_2DHists_fromMAP(Playlist_MnvH2D_Map MnvH2D_Map , ME_helium_Playlists ADDtothisHis ,const char* name);
Playlist_HistFolio_MnvH1D_Map Constuct_HistFolio_mvnH1DMap_FromME_playlist_TFileMAP(ME_playlist_TFileMAP TFile_Map, const char* name );
double Combine_POTFromMap(Pot_MapList inputPOTplaylistMAP );
bool CheckIFMap_hasonly_FULLstatus(Pot_MapList POTMap);
bool CheckIFMap_hasonly_Emptystatus(Pot_MapList POTMap);
void ScaleCutMap( RECO_Cut_Map &Map , double POTscaler);
CyroStatusPot_MapList Constuct_TOTALPOT_cryostatusMap(Pot_MapList FullMC_POTMap,
                                                      Pot_MapList EmptyMC_POTMap,
                                                      Pot_MapList FullData_POTMap,
                                                      Pot_MapList EmptyData_POTMap);
CyroStatusPot_MapList Constuct_TOTALPOT_cryostatusMap(Pot_MapList Full_POTMap, Pot_MapList Empty_POTMap, bool ForMC);
CyroStatusPot_MapList MakeScaler_TOTALPOT_cryostatusMapTOFULLDATA(CyroStatusPot_MapList Total_Map);
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
std::vector<std::vector<HeliumCVUniverse*>> groupCompatibleUniverses(const std::map<std::string, std::vector<HeliumCVUniverse*>> bands);
bool isCV(const HeliumCVUniverse& univ);
TRUE_Cut_Map ConstuctTRUTHCountingMap(std::vector<ECutsTRUTH> inputTRUECuts);
RECO_Cut_Map ConstuctRecoCountingMap(std::vector<ECuts> inputRECOCuts);
void FillingRecoCountingMap(std::vector<ECuts> inputRECOCuts, RECO_Cut_Map &OutputMap);
void FillingTruthCountingMap(std::vector<ECutsTRUTH> inputTRUTHCuts, TRUE_Cut_Map &OutputMap);
void FillRECO_CutMap_FromTGraph(TGraph *TGraph_RECO_CUTS , RECO_Cut_Map &FillMap);
void FillTRUTH_CutMap_FromTGraph(TGraph *TGraph_TRUTH_CUTS , TRUE_Cut_Map &FillMap);
ME_helium_Status  GetPlaylist_HeliumStatus(ME_helium_Playlists playlist_name);
void print_POT_ME_helium_Status(Pot_MapStatusList input);
std::string GetPlaylistStatusString(ME_helium_Status status);
std::string GetPlaylist_InitialName(ME_helium_Playlists playlist_name);
std::string  GetVertexCryoVarHist_DATA_Name(CryoVertex playlist_name);
std::string  GetVertexCryoVarHistName(CryoVertex playlist_name);
std::string  GetsecondTrakHistName(SecondTrkVar playlist_name);
std::string GetsecondTrk_XAxisTitle(SecondTrkVar playlist_name);
std::string GetPlaylist_Name(ME_helium_Playlists playlist_name);
std::string GetPlaylist(ME_helium_Playlists playlist_name);
std::string GetVertexCryoVarAxisTitle(CryoVertex playlist_name);
std::string  GetMuonVarAXISName(MuonVar playlist_name);
FullAndEmptyPlaylistMap  MakeFullorEmptyList(std::vector <ME_helium_Playlists> InPutList );
std::vector<ME_helium_Playlists>  MakeFullorEmptyVector(std::vector <ME_helium_Playlists> InPutList, char FullorEmpty );
std::string  GetParticle_group_Name(Particle_type Particle);
Particle_type GetParticlegroup_type(int Particle_input );
std::string  GetVertexCryoVarHIST_Title(CryoVertex Var ,ME_helium_Playlists playlist_name );
std::string  GetVertexCryoVarHIST_Title(CryoVertex Var ,ME_helium_Playlists playlist_nameFULL,ME_helium_Playlists playlist_nameEMPTY );
std::string  GetMuon_Figure_Title(MuonVar Var, ME_helium_Playlists playlist_name );
std::string  GetFULL_EMPTYSTRING(ME_helium_Playlists playlist_name_FULL, ME_helium_Playlists playlist_name_EMPTY );
Material_type GetMaterial_TargetZenum(int targetZ);
Interaction_type GetInteractionenum(int Interaction);
Particle_type GetParticlegroup_type(int Particle_input );
std::vector<Particle_type> getParticle_typeVector();
std::string GetMuonVar_crosssection(MuonVar playlist_name);
//==============================================================================
// Get hist by name from an in-file
//==============================================================================
PlotUtils::MnvH1D* GetHist(TFile& fin, const char* name);
PlotUtils::MnvH1D* GetHist(TFile& fin, std::string name );
PlotUtils::MnvH2D* Get2DHist(TFile& fin, const char* name);
PlotUtils::MnvH2D* Get2DHist(TFile& fin, const char* name, bool isFull);
PlotUtils::MnvH2D* Get2DHist(TFile& fin, std::string name );

std::string  GetNameMaterial(Material_type playlist_name);
std::string  GetNameInteraction(Interaction_type playlist_name);
std::string  GetNameParticle(Particle_type playlist_name);
std::vector<Interaction_type> GetInteraction_typeList();
std::vector<Particle_type> GetParticle_typeList();
std::vector<Material_type> GetMaterial_typeList();
std::string GetcommonNamefromPDG(int pdg);
std::string GetcommonNamefromPDG(int pdg, bool latex_true);
void Scale_MnvH1D_Array(const TObjArray HistArray , double Scaler);
void BinWidthNorm_MnvH1D_Array(const TObjArray HistArray);
void AddFirst_toSecond_MnvH1D_Arrays(const TObjArray HistArray1 , const TObjArray HistArray2);
void SubractSecond_FromFirst_MnvH1D_Arrays(const TObjArray HistArray1 , const TObjArray HistArray2);
void AddNumeratorSysErrorsToDenominator_Playlist_MnvH1D_Map(Playlist_MnvH1D_Map &Numerator_Map , Playlist_MnvH1D_Map &Denominator_Map);
//==============================================================================
// Copy all hists of one file into another file
//==============================================================================
void CopyHists(TFile& , TFile& );
void WritePOT(TFile& , const bool is_mc, const float pot);
double FixAngle(double angle);
double ConvertRadToDeg(double rad);

double PerpDist( std::vector<double> v0, std::vector<double> v1, std::vector<double> v2);

std::vector<double> GetSecondTrkVarVector(SecondTrkVar playlist_name);
std::string  GetsecondTrakHistName(SecondTrkVar playlist_name);
std::string GetsecondTrkTitleName(SecondTrkVar playlist_name);
std::string GetsecondTrkTitleNameforLatex(SecondTrkVar playlist_name);
std::string String_ISMC(bool is_mc);


//! Basic calculation functions that are usually in MinervaMathTool
double calcYfromUV(double U, double V);
double calcYfromXU(double X, double U);
double calcYfromXV(double X, double V);
double calcXfromUV(double U, double V);
double calcUfromXY(double X, double Y);
double calcVfromXY(double X, double Y);


double getmassfromPDG(int pdg,int& count);
int calculate_Target(int targetZ);
 Material_type calculate_Target_materialtype(int targetZ);
int calculate_Interaction(int interaction);
std::string Interaction_name(int interaction);
std::string GetPlaylist_txtFILE_path(ME_helium_Playlists playlist, bool is_mc );
std::string GetPlaylist_txtFILE_path(std::string Name, bool is_mc);
std::string GetPlaylist_ROOT_path(ME_helium_Playlists playlist, bool is_mc );
std::string String_ISMC_EventSectionROOT(bool is_mc);
std::string String_EventSectionROOTPath(bool is_mc,ME_helium_Playlists playlist_name,bool StatsOnly );
std::string GetsecondTrk_AXIS_TitleName(SecondTrkVar playlist_name);
std::string  Get2ndTrkHIST_Title(SecondTrkVar Var ,ME_helium_Playlists playlist_name );
std::string  Get2ndTrkHIST_Title(SecondTrkVar Var ,ME_helium_Playlists playlist_nameFull,ME_helium_Playlists playlist_nameEMPTY ); //Overloaded
std::vector<double> DetermineBinning(TH2D* input_hist, double limit);
template<typename T> void PrintVECTOR_toscreen(std::vector<T> A , std::string name){
std::cout<<"~~~~~~~~~~~~~~~~~~ "<<  std::endl;
std::cout<<"print vector of "<< name << std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~ "<<  std::endl;
for(auto A_index:A ){std::cout<<A_index<<std::endl;}
std::cout<<"~~~~~~~~~~~~~~~~~~ "<<  std::endl;
std::cout<<"END print vector of "<< name << std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~ "<<  std::endl;
}
std::string GetsecondTrkUnitType(SecondTrkVar playlist_name) ;
std::vector<double> Return_scaled_vector(std::vector<double> input_vector, double scale);
std::string arachne(SliceID &id, const bool isData, const bool useRodriges=false);
std::string PrintLabel_Systematics(int input);
std::vector<bool> Print_Systematics(int input);
std::string  GetMigrationTiteName(Migration playlist_name);
std::string  GetMigrationXaxisName(Migration playlist_name);
std::string  GetMigrationYaxisName(Migration playlist_name);
std::string  GetMigrationHistName(Migration playlist_name);
std::string  GetMigrationUnitType(Migration playlist_name);
void rowNormalize(TH2& hist);
void colNormalize(TH2& hist);
void rowNormalize(MnvH2D& hist);
void colNormalize(MnvH2D& hist);


Migration Migration_muonType(MuonVar playlist_name);
std::string MigrationHistName_frommuonType(MuonVar playlist_name);
parameterizationEquation_params MakeParameterizelineParasFromPoints(int pdg, double KE, double X_Start,double Y_Start, double Z_Start,double X_End,double Y_End,double Z_End );
parameterizationEquation_params_DATA MakeParameterizelineParasFromDataPoints(double KE, double angle, double length, double X_Start, double Y_Start, double Z_Start,double X_End,double Y_End,double Z_End);
parameterizationEquation_paramsWithTrueFraction MakeParameterizelineParasFromPoints(int pdg, double KE, double trueEFraction ,double X_Start,double Y_Start, double Z_Start,double X_End,double Y_End,double Z_End);
double FindDistance(Vertex_XYZ upstream_point,Vertex_XYZ downstream_point );
Vertex_XYZ Parameterization3dFunction(parameterizationEquation_params input, double t);
Vertex_XYZ Parameterization3dFunction(parameterizationEquation_paramsWithTrueFraction input, double t);
Vertex_XYZ Parameterization3dFunction(parameterizationEquation_params_DATA input, double t);
std::vector<Vertex_XYZ> MakeVectorofPath(parameterizationEquation_params Input, double Spaceingcm, double t_finish);
std::vector<Vertex_XYZ> MakeVectorofPath(parameterizationEquation_paramsWithTrueFraction Input, double Spaceingcm, double t_finish);
std::vector<Vertex_XYZ> MakeVectorofPath(parameterizationEquation_params_DATA Input, double Spaceingcm, double t_finish);
int Find_NPoints(parameterizationEquation_params input ,double Spaceingcm);
int Find_NPoints(parameterizationEquation_paramsWithTrueFraction input ,double Spaceingcm);
int Find_NPoints(parameterizationEquation_params_DATA input ,double Spaceingcm);
std::vector <parameterizationEquation_params> MakeParameterizelineParasTrajector_ParticeVectorForSingleTrajector(Trajector input_Trajector);
std::vector <parameterizationEquation_paramsWithTrueFraction> MakeParameterizelineParasTrajector_ParticeVectorForSingleTrajector_withTRUEFraction(Trajector_withTrueEnergyFraction input_Trajector);
std::vector <parameterizationEquation_params_DATA> MakeParameterizelineParasTrajector_ForDataStruct(Trajector_DATA inputVector);
TGraph  *Make_X_vs_Z_Tgraph_fromVector(std::vector<Vertex_XYZ> input);
TGraph  *Make_Y_vs_Z_Tgraph_fromVector(std::vector<Vertex_XYZ>input);
TGraph  *Make_R_vs_Z_Tgraph_fromVector(std::vector<Vertex_XYZ>input);
TGraph  *Make_RR_vs_Z_Tgraph_fromVector(std::vector<Vertex_XYZ>input);

TGraph  *Make_V_vs_Z_Tgraph_fromVector(std::vector<Vertex_XYZ> input);
TGraph  *Make_U_vs_Z_Tgraph_fromVector(std::vector<Vertex_XYZ> input);
TGraph  *Make_TruthCut_Tgraph_fromCutMap(const char* fileName, TRUE_Cut_Map input_Map);
TGraph  *Make_RECOCut_Tgraph_fromCutMap(const char* fileName, RECO_Cut_Map input_Map);





TGraph  *Make_VertLineTgraph(int N_points,double Zpostion, double Start_Xaxis, double End_Xaxis);
bool CheckIfTrajectorsHaveEqual_RunInfo(Trajector input_TrajectorA ,Trajector input_TrajectorB  );
bool CheckIfTrajectors_VectorsHaveEqual_RunInfo(std::vector<Trajector> input_vectorTrajectorA ,std::vector<Trajector> input_vectorTrajectorB  );
bool CheckIfTrajectors_VectorsHaveEqual_RunInfo(std::vector<Trajector> input_vectorTrajectorA ,std::vector<Trajector_withTrueEnergyFraction> input_vectorTrajectorB  );
bool CheckIfTrajectors_TRUERECO_KEVectorsHaveEqual_RunInfo(std::vector<Trajector> input_vectorTrajectorA ,std::vector<TRUE_RECO_Energies_Trajectors> input_vectorTRUE_RECO_Energies  );
bool CheckIfTrajectors_TRUERECO_KEVectorsHaveEqual_RunInfo(std::vector<Trajector> input_vectorTrajectorA ,std::vector<Trajector_withTrueEnergyFraction> input_vectorTrajector_withTrueEnergyFraction  );
int  GetColorNParticle(Particle_type playlist_name);
int  GetColorNMaterial(Material_type playlist_name);
int  GetColorNInteraction(Interaction_type playlist_name);
Particle_type getParticle_fromstring(const char *type);
Interaction_type getInteraction_fromstring(const char *type);
Material_type getMaterial_fromstring(const char *type);
TrackType getTrackType_fromstring(const char *type);
boolNTrack getboolNTrack_fromstring(const char *type);
VertexOptions getVertexOptions_fromstring(const char *type);
std::string  GetVetowallHistName( VetoWall_vars vetowall_input);
std::string  GetVetowall_XAxisTitle( VetoWall_vars vetowall_input);
std::string  GetVetowall_Title( VetoWall_vars vetowall_input);
std::string  GetVetowall_UnitType( VetoWall_vars vetowall_input);
std::vector<double>  GetVetowall_BinVetor( VetoWall_vars vetowall_input);
std::string  GetVetowallHist_DataName( VetoWall_vars vetowall_input);
std::vector<parameterizationEquation_params_bare> MakeParameterizelineParasFromPoints(Vertex_XYZ VertexP,  std::vector<Vertex_XYZ> EndPoints);
std::vector<parameterizationEquation_params_bare> MakeParameterize_bare_lineParasFromPoints(Vertex_XYZ VertexP,  std::vector<Vertex_XYZ> EndPoints);
std::vector<double> FindVector_TforParameterizeLinesAtZ(std::vector<parameterizationEquation_params_bare> Input_vector , double ZPoint_start);
std::vector<double> FindDistance_vector(std::vector<Vertex_XYZ> upstream_points, std::vector<Vertex_XYZ> downstream_points );
std::vector<Vertex_XYZ> GetTrueMinervaStartPostion(std::vector<parameterizationEquation_params_bare> InputPara_vector, std::vector<double> t_vector, double ZPoint_start );
inline double round( double val );
std::string  GetNameTrack(TrackType playlist_name);
std::string String_Reco_orData(bool isReco);

/*EventCut_Rate_STRUCT MakeEventCut_Rate_STRUCT_fromTFiles(TFile *inputFile_TRUTHBranch, const char* TGraphName_TRUTHBranch,
   TFile *inputFile_RECOBranch, const char* TGraphName_RECOBranch_TRUE , const char* TGraphName_RECOBranch_TRUE_RECO,
   ME_helium_Playlists playlist, ME_helium_Status Crytank_status);*/

   void  MakeEventCut_Rate_STRUCT_fromTFiles(EventCut_Rate_STRUCT &RETURN_Event_STRUCT, TFile *inputFile_TRUTHBranch,  char* TGraphName_TRUTHBranch,
      TFile *inputFile_RECOBranch,  char* TGraphName_RECOBranch_TRUE ,  char* TGraphName_RECOBranch_TRUE_RECO,
      ME_helium_Playlists playlist, ME_helium_Status Crytank_status);

//void SetStackColorsMaterial(TObjArray * mcHists);
//void SetStackColorsInteraction(TObjArray * mcHists);
//void SetStackColorsParticle(TObjArray * mcHists);

std::string MakePlaylistString(std::vector<ME_helium_Playlists> input );


template<typename T>
bool compare(std::vector<T>& v1, std::vector<T>& v2)
{
    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());
    return v1 == v2;
}

template<typename T>
bool isEqual(std::vector<T> const &v1, std::vector<T> const &v2)
{
    auto pair = std::mismatch(v1.begin(), v1.end(), v2.begin());
    return (pair.first == v1.end() && pair.second == v2.end());
}

std::string String_Reco_orTruth(bool isReco);
Particle_type  GetParticlegroup_typeProtonandpion_other(int pdg);
std::vector<double> GetScales(std::vector<std::pair<TH2*, const char*> >histopts, bool pzProj);
std::vector<double> Normlized_to_lowest_Mulitplers(std::vector <double> multiply_vector);
std::vector<double> GetScales(std::vector<std::pair<TH2*, const char*> >histopts, bool pzProj, bool  donormalized);

CrossSection_histNames Constuct_crosssection_Histname(MuonVar muon_input_type);
CrossSection_Hist Constuct_crosssection_Hists(CrossSection_histNames Names, TFile *inputFile_RECO_mc,TFile *inputFile_TRUE_mc, TFile *inputFile_data );

double Pot_from_rootpathway(std::string pathway, bool m_ismc );

void Print_crosssection_Histname(CrossSection_histNames crosssection_hist_Names);
void WritetoTFile_All(CrossSection_Hist &Constuct_crosssection_Hists, TFile& file, char* Name);
void WritetoTFile_All(ME_playlist_CrossSection_MAP &Constuct_crosssection_Map, TFile& file, char* Name);
void WritetoTFile_main(CrossSection_Hist &Constuct_crosssection_Hists, TFile& file, char* Name);
void Check_NSignalBins(CrossSection_Hist &Constuct_crosssection_Hists,char* Name );
//void WritetoTFile_NormCrossSection(CrossSection_Hist &Constuct_crosssection_Hists, TFile& file, char* Name, double PotNorm_MC_TO_Data);
void WritetoTFile_NormTRUECrossSection(CrossSection_Hist &Constuct_crosssection_Hists, TFile& file, char* Name, const double nNucleons, const double POT);
ME_playlist_CrossSection_MAP Constuct_crosssection_Hists_PlaylistMap(CrossSection_histNames Names,
              ME_playlist_TFileMAP MC_RECO_TfileMap, ME_playlist_TFileMAP MC_TRUTH_TfileMap,
              ME_playlist_TFileMAP Data_TfileMap );
CrossSection_Hist Combine_crosssection_Hists_PlaylistMap(ME_playlist_CrossSection_MAP inputMap, ME_helium_Playlists playlist_combine_too );
double Hists1DTotal(MnvH1D * hist);
float eff_error(double num, double denom, int statFlag);
std::vector<double> Backwards_intergration(MnvH1D *hist);
std::vector<double> Foward_intergration(MnvH1D *hist);
std::vector<double> Foward_intergration_combined(MnvH1D *hist1, MnvH1D *hist2);
std::vector<double> GetBinUpEdges(MnvH1D *hist);
std::vector <double> MakeBinVector_chiSqrt();
TGraphErrors *MakeForwardIntergrationPurity_TGraphError(MnvH1D *hist_Helium, MnvH1D *hist_Other );
TGraphErrors *MakeForwardIntergrationEfficiency_TGraphError(MnvH1D *hist_Helium);
TGraphErrors *MakeForwardIntergrationEfficiency_times_Purity_TGraphError(MnvH1D *hist_Helium, MnvH1D *hist_Other );
std::string  GetNameVertexOption(VertexOptions playlist_name);
std::string  GetName_boolNTrack(boolNTrack playlist_name);


#endif // common_functions_h
