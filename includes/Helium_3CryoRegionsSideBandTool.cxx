#include "Helium_3CryoRegionsSideBandTool.h"

Helium_3CryoRegionsSideBandTool::Helium_3CryoRegionsSideBandTool(){
current_unv = 0;
}

void Helium_3CryoRegionsSideBandTool::init_Tool_2playlist(std::vector<ME_helium_Playlists> Full_PlaylistInput,
                                                      std::vector<ME_helium_Playlists> Empty_PlaylistInput)
{
  Full_Playlist = Full_PlaylistInput;
  Empty_Playlist = Empty_PlaylistInput;

  current_unv = 0;

  //////
  //Hist  Names
  ///////////

    ConstructVertex_FitHistName_Map(Empty, "");
    ConstructVertex_FitHistName_Map(Empty_UpstreamCap, "_UpstreamCap");
    ConstructVertex_FitHistName_Map(Empty_Barrel, "_Barrel");
    ConstructVertex_FitHistName_Map(Empty_DownstreamCap, "_DownstreamCap");
    ConstructVertex_FitHistName_Map(Empty_DownstreamConcaveCap, "_Downstream_ConcaveCap");


    SetNames(Empty,               "Empty" );
    SetNames(Empty_UpstreamCap,   "Empty_UpstreamCap"  );
    SetNames(Empty_Barrel,        "Empty_Barrel" );
    SetNames(Empty_DownstreamCap, "Empty_DownstreamCap" );
    SetNames(Empty_DownstreamConcaveCap, "Empty_DownstreamCap" );


    ConstructVertex_FitHistName_Map(Full, "");
    ConstructVertex_FitHistName_Map(Full_UpstreamCap,          "_UpstreamCap");
    ConstructVertex_FitHistName_Map(Full_Barrel,               "_Barrel");
    ConstructVertex_FitHistName_Map(Full_DownstreamCap,        "_DownstreamCap");
    ConstructVertex_FitHistName_Map(Full_DownstreamConcaveCap, "_Downstream_ConcaveCap");

    SetNames(Full, "Full" );
    SetNames(Full_UpstreamCap,          "Full_UpstreamCap"  );
    SetNames(Full_Barrel,               "Full_Barrel" );
    SetNames(Full_DownstreamCap,        "Full_DownstreamCap" );
    SetNames(Full_DownstreamConcaveCap, "Full_Downstream_ConcaveCap" );


    ConstructVertex_FitHistName_Map(Full_Empty, "");
    ConstructVertex_FitHistName_Map(Full_Empty_UpstreamCap,          "_UpstreamCap");
    ConstructVertex_FitHistName_Map(Full_Empty_Barrel,               "_Barrel");
    ConstructVertex_FitHistName_Map(Full_Empty_DownstreamCap,        "_DownstreamCap");
    ConstructVertex_FitHistName_Map(Full_Empty_DownstreamConcaveCap, "_Downstream_ConcaveCap");

    SetNames(Full_Empty, "Full_Empty" );
    SetNames(Full_Empty_UpstreamCap,          "Full_Empty_UpstreamCap"  );
    SetNames(Full_Empty_Barrel,               "Full_Empty_Barrel" );
    SetNames(Full_Empty_DownstreamCap,        "Full_Empty_DownstreamCap" );
    SetNames(Full_Empty_DownstreamConcaveCap, "Full_Empty_DownstreamConcaveCap" );
    std::cout<<"Finished SetNames() "<<std::endl;


    ConstuctandFill2Playlist_POT_forSideBands(Full_PlaylistInput.at(0) , Empty_PlaylistInput.at(0));

    const ME_helium_Playlists input_full = Full_PlaylistInput.at(0);
    const ME_helium_Playlists input_empty = Empty_PlaylistInput.at(0);

    initSideBands_2playlist(input_full, input_empty);
    std::cout<<"init_Tool: COMPLETE"<<std::endl;
    std::cout<<"init_Tool: POT scaling initial Hist "<<std::endl;
    init_POTScale_AllHist();
    std::cout<<"init_Tool: Finished POT scaling initial Hist "<<std::endl;
    std::cout<<"initTool: Full - Empty intial Hist"<<std::endl;
    init_Hist_Full_minus_Empty();
    std::cout<<"initTool: FINSIHED Full - Empty intial Hist"<<std::endl;
  }


  void Helium_3CryoRegionsSideBandTool::init_MC_PlaylistCombined_SideBand_Resolution_Histograms(){
     ME_helium_Playlists input_full = Full_Playlist.at(0);
     ME_helium_Playlists input_empty = Empty_Playlist.at(0);
     std::cout<<"Inside::init_MC_PlaylistCombined_SideBand_Resolution_Histograms"<<std::endl;
    init_MC_PlaylistCombined_SideBand_Resolution_Histograms(input_full, input_empty);

  }



  void Helium_3CryoRegionsSideBandTool::init_Tool_SingleEmptyplaylist(std::vector<ME_helium_Playlists> Empty_PlaylistInput)
  {

    Empty_Playlist = Empty_PlaylistInput;

    current_unv = 0;

      ConstructVertex_FitHistName_MapData(Empty, "");
      ConstructVertex_FitHistName_MapData(Empty_UpstreamCap,          "_UpstreamCap");
      ConstructVertex_FitHistName_MapData(Empty_Barrel,               "_Barrel");
      ConstructVertex_FitHistName_MapData(Empty_DownstreamCap,        "_DownstreamCap");
      ConstructVertex_FitHistName_MapData(Empty_DownstreamConcaveCap, "_Downstream_ConcaveCap");

      ConstructVertex_FitMC_shifted_HistName_Map(Empty, "");
      ConstructVertex_FitMC_shifted_HistName_Map(Empty_UpstreamCap,          "_upstreamcap");
      ConstructVertex_FitMC_shifted_HistName_Map(Empty_Barrel,               "_barrel");
      ConstructVertex_FitMC_shifted_HistName_Map(Empty_DownstreamCap,        "_downstreamcap");
      ConstructVertex_FitMC_shifted_HistName_Map(Empty_DownstreamConcaveCap, "_downstreamconcavecap");

      SetNames(Empty,                      "Empty" );
      SetNames(Empty_UpstreamCap,          "Empty_UpstreamCap"  );
      SetNames(Empty_Barrel,               "Empty_Barrel" );
      SetNames(Empty_DownstreamCap,        "Empty_DownstreamCap" );
      SetNames(Empty_DownstreamConcaveCap, "Empty_DownstreamConcaveCap" );

      ConstuctandFill_EmptyPlaylist_POT_forSideBands(Empty_PlaylistInput.at(0));
      initSideBands_EmptyDataplaylist(Empty_PlaylistInput.at(0) );

    }

    void Helium_3CryoRegionsSideBandTool::init_Tool_CompleteEmptyplaylist(std::vector<ME_helium_Playlists> Empty_PlaylistInput, std::vector<ME_helium_Playlists> Full_PlaylistInput)
    {

      Empty_Playlist = Empty_PlaylistInput;

      current_unv = 0;

        ConstructVertex_FitHistName_MapData(Empty, "");
        ConstructVertex_FitHistName_MapData(Empty_UpstreamCap,          "_UpstreamCap");
        ConstructVertex_FitHistName_MapData(Empty_Barrel,               "_Barrel");
        ConstructVertex_FitHistName_MapData(Empty_DownstreamCap,        "_DownstreamCap");
        ConstructVertex_FitHistName_MapData(Empty_DownstreamConcaveCap, "_Downstream_ConcaveCap");

        ConstructVertex_FitMC_shifted_HistName_Map(Empty, "");
        ConstructVertex_FitMC_shifted_HistName_Map(Empty_UpstreamCap,          "_upstreamcap");
        ConstructVertex_FitMC_shifted_HistName_Map(Empty_Barrel,               "_barrel");
        ConstructVertex_FitMC_shifted_HistName_Map(Empty_DownstreamCap,        "_downstreamcap");
        ConstructVertex_FitMC_shifted_HistName_Map(Empty_DownstreamConcaveCap, "_downstreamconcavecap");

        SetNames(Empty,                      "Empty" );
        SetNames(Empty_UpstreamCap,          "Empty_UpstreamCap"  );
        SetNames(Empty_Barrel,               "Empty_Barrel" );
        SetNames(Empty_DownstreamCap,        "Empty_DownstreamCap" );
        SetNames(Empty_DownstreamConcaveCap, "Empty_DownstreamConcaveCap" );

        ConstuctandFill_Complete_EMPTYNuMEPlaylist_POT_forSideBands(Empty_PlaylistInput, Full_PlaylistInput);
        initSideBands_CombinedEmptyDataplaylist();


      }

void Helium_3CryoRegionsSideBandTool::init_Tool_CompleteEmptyplaylist_Xregions(std::vector<ME_helium_Playlists> Empty_PlaylistInput)
{

  Empty_Playlist = Empty_PlaylistInput;

  current_unv = 0;
  ConstructVertex_FitHistName_MapData(Empty, "");
  ConstructVertex_FitHistName_MapData(Empty_XCenter,        "_XCenter");
  ConstructVertex_FitHistName_MapData(Empty_XLeftShelf,     "_XLeftShelf");
  ConstructVertex_FitHistName_MapData(Empty_XRightShelf,    "_XRightShelf");
  ConstructVertex_FitHistName_MapData(Empty_XoutsideEdges,  "_XoutsideEdges");


  ConstructVertex_FitMC_shifted_HistName_Map(Empty, "");
  ConstructVertex_FitMC_shifted_HistName_Map(Empty_XCenter,       "_XCenter");
  ConstructVertex_FitMC_shifted_HistName_Map(Empty_XLeftShelf,    "_XLeftShelf");
  ConstructVertex_FitMC_shifted_HistName_Map(Empty_XRightShelf,   "_XRightShelf");
  ConstructVertex_FitMC_shifted_HistName_Map(Empty_XoutsideEdges, "_XoutsideEdges");

  ConstructVertex_FitHistName_Map(Empty, "");
  ConstructVertex_FitHistName_Map(Empty_XCenter,       "_XCenter");
  ConstructVertex_FitHistName_Map(Empty_XLeftShelf,    "_XLeftShelf");
  ConstructVertex_FitHistName_Map(Empty_XRightShelf,   "_XRightShelf");
  ConstructVertex_FitHistName_Map(Empty_XoutsideEdges, "_XoutsideEdges");

  SetNames(Empty,               "Empty" );
  SetNames(Empty_XCenter,       "Empty_XCenter"  );
  SetNames(Empty_XLeftShelf,    "Empty_XLeftShelf" );
  SetNames(Empty_XRightShelf,   "Empty_XRightShelf" );
  SetNames(Empty_XoutsideEdges, "Empty_XoutsideEdges" );


  ConstuctandFill_Complete_EMPTYNuMEPlaylist_POT_forSideBands_Xregions(Empty_PlaylistInput);

  initSideBand_PlaylistCombinedFitDataHistograms(Empty_XCenter ,      TFile_Map_Empty_Data  );
  initSideBand_PlaylistCombinedFitDataHistograms(Empty_XLeftShelf,    TFile_Map_Empty_Data  );
  initSideBand_PlaylistCombinedFitDataHistograms(Empty_XRightShelf,   TFile_Map_Empty_Data  );
  initSideBand_PlaylistCombinedFitDataHistograms(Empty_XoutsideEdges, TFile_Map_Empty_Data  );
}

void Helium_3CryoRegionsSideBandTool::init_Tool_CompleteEmptyplaylist_XZregions(std::vector<ME_helium_Playlists> Empty_PlaylistInput)
{

  Empty_Playlist = Empty_PlaylistInput;

  current_unv = 0;
  ConstructVertex_FitHistName_MapData(Empty, "");
  ConstructVertex_FitHistName_MapData(Empty_XCenter,               "_ZXCenter");
  ConstructVertex_FitHistName_MapData(Empty_XLeftShelf,            "_ZXLeftShelf");
  ConstructVertex_FitHistName_MapData(Empty_XRightShelf,           "_ZXRightShelf");
  ConstructVertex_FitHistName_MapData(Empty_DownstreamConcaveCap,  "_ZXDownstream_ConcaveCap");


  ConstructVertex_FitMC_shifted_HistName_Map(Empty, "");
  ConstructVertex_FitMC_shifted_HistName_Map(Empty_XCenter,              "_XCenter");
  ConstructVertex_FitMC_shifted_HistName_Map(Empty_XLeftShelf,           "_XLeftShelf");
  ConstructVertex_FitMC_shifted_HistName_Map(Empty_XRightShelf,          "_XRightShelf");
  ConstructVertex_FitMC_shifted_HistName_Map(Empty_DownstreamConcaveCap, "_XDownstream_ConcaveCap");

  ConstructVertex_FitHistName_Map(Empty, "");
  ConstructVertex_FitHistName_Map(Empty_XCenter,       "_XCenter");
  ConstructVertex_FitHistName_Map(Empty_XLeftShelf,    "_XLeftShelf");
  ConstructVertex_FitHistName_Map(Empty_XRightShelf,   "_XRightShelf");
  ConstructVertex_FitHistName_Map(Empty_DownstreamConcaveCap, "_XDownstream_ConcaveCap");

  SetNames(Empty,               "Empty" );
  SetNames(Empty_XCenter,       "Empty_XCenter"  );
  SetNames(Empty_XLeftShelf,    "Empty_XLeftShelf" );
  SetNames(Empty_XRightShelf,   "Empty_XRightShelf" );
  SetNames(Empty_DownstreamConcaveCap, "Empty_DownstreamConcaveCap" );


  ConstuctandFill_Complete_EMPTYNuMEPlaylist_POT_forSideBands_XZregions(Empty_PlaylistInput);

  initSideBand_PlaylistCombinedFitDataHistograms(Empty_XCenter ,      TFile_Map_Empty_Data  );
  initSideBand_PlaylistCombinedFitDataHistograms(Empty_XLeftShelf,    TFile_Map_Empty_Data  );
  initSideBand_PlaylistCombinedFitDataHistograms(Empty_XRightShelf,   TFile_Map_Empty_Data  );
  initSideBand_PlaylistCombinedFitDataHistograms(Empty_DownstreamConcaveCap, TFile_Map_Empty_Data  );

  //initSideBands_Multipleplaylists_Xregions(Empty_PlaylistInput.at(1));
std::cout<<"finished init_Tool_CompleteEmptyplaylist_XZregions"<<std::endl;

}

void Helium_3CryoRegionsSideBandTool::init_playlists(std::vector<ME_helium_Playlists> Full_PlaylistInput,
                                                                       std::vector<ME_helium_Playlists> Empty_PlaylistInput){

                                                                         Full_Playlist = Full_PlaylistInput;
                                                                         Empty_Playlist = Empty_PlaylistInput;

                                                                       }



void Helium_3CryoRegionsSideBandTool::init_Tool_CompleteNuMEplaylist(std::vector<ME_helium_Playlists> Full_PlaylistInput,
                                                                       std::vector<ME_helium_Playlists> Empty_PlaylistInput)
{
  current_unv = 0;
  //////
  //Hist  Names
  ///////////
  Full_Playlist = Full_PlaylistInput;
  Empty_Playlist = Empty_PlaylistInput;

  ConstructVertex_FitHistName_Map(Empty, "");
  ConstructVertex_FitHistName_Map(Empty_UpstreamCap,          "_UpstreamCap");
  ConstructVertex_FitHistName_Map(Empty_Barrel,               "_Barrel");
  ConstructVertex_FitHistName_Map(Empty_DownstreamCap,        "_DownstreamCap");
  ConstructVertex_FitHistName_Map(Empty_DownstreamConcaveCap, "_Downstream_ConcaveCap");

  SetNames(Empty,               "Empty" );
  SetNames(Empty_UpstreamCap,   "Empty_UpstreamCap"  );
  SetNames(Empty_Barrel,        "Empty_Barrel" );
  SetNames(Empty_DownstreamCap, "Empty_DownstreamCap" );
  SetNames(Empty_DownstreamConcaveCap, "Empty_DownstreamConcaveCap" );

  ConstructVertex_FitHistName_Map(Full, "");
  ConstructVertex_FitHistName_Map(Full_UpstreamCap,          "_UpstreamCap");
  ConstructVertex_FitHistName_Map(Full_Barrel,               "_Barrel");
  ConstructVertex_FitHistName_Map(Full_DownstreamCap,        "_DownstreamCap");
  ConstructVertex_FitHistName_Map(Full_DownstreamConcaveCap, "_Downstream_ConcaveCap");

  SetNames(Full, "Full" );
  SetNames(Full_UpstreamCap,"Full_UpstreamCap"  );
  SetNames(Full_Barrel, "Full_Barrel" );
  SetNames(Full_DownstreamCap, "Full_DownstreamCap" );
  SetNames(Full_DownstreamConcaveCap, "Full_Downstream_ConcaveCap" );


  ConstructVertex_FitHistName_Map(Full_Empty, "");
  ConstructVertex_FitHistName_Map(Full_Empty_UpstreamCap,           "_UpstreamCap");
  ConstructVertex_FitHistName_Map(Full_Empty_Barrel,                "_Barrel");
  ConstructVertex_FitHistName_Map(Full_Empty_DownstreamCap,         "_DownstreamCap");
  ConstructVertex_FitHistName_Map(Full_Empty_DownstreamConcaveCap,  "_Downstream_ConcaveCap");



  SetNames(Full_Empty, "Full_Empty" );
  SetNames(Full_Empty_UpstreamCap,"Full_Empty_UpstreamCap"  );
  SetNames(Full_Empty_Barrel, "Full_Empty_Barrel" );
  SetNames(Full_Empty_DownstreamCap, "Full_Empty_DownstreamCap" );
  SetNames(Full_Empty_DownstreamConcaveCap, "Full_Empty_DownstreamConcaveCap" );
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"~~~~~~~~~~~~Finished SetNames()~~~~~~~~~~ "<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;


  ConstuctandFill_Complete_NuMEPlaylist_POT_forSideBands(Full_PlaylistInput , Empty_PlaylistInput);

  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"~~~~~~~~~~~~Finished: ConstuctandFill_Complete_NuMEPlaylist_POT_forSideBands ~~~~~~~~~~ "<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

  const ME_helium_Playlists input_full = Full_PlaylistInput.at(3);
  const ME_helium_Playlists input_empty = Empty_PlaylistInput.at(0);
  initSideBands_Multipleplaylists( input_full,  input_empty );
  //initSideBands_2playlist(input_full, input_empty);
  std::cout<<"init_Tool: COMPLETE"<<std::endl;
  std::cout<<"init_Tool: POT scaling initial Hist "<<std::endl;
  init_POTScale_AllHist();
  std::cout<<"init_Tool: Finished POT scaling initial Hist "<<std::endl;
  std::cout<<"initTool: Full - Empty intial Hist"<<std::endl;
  init_Hist_Full_minus_Empty();
  std::cout<<"initTool: FINSIHED Full - Empty intial Hist"<<std::endl;

}



void Helium_3CryoRegionsSideBandTool::Clear_Al_wgt(){
wgt_Aluminium.clear();
err_Aluminium.clear();
}


void Helium_3CryoRegionsSideBandTool::Fill_Alwgt(std::vector<double> inputWgt, std::vector<double> inputwgt_errors ){

for(auto cat: inputWgt){
  wgt_Aluminium.push_back(cat);
}

for(auto cat: inputwgt_errors){
  err_Aluminium.push_back(cat);
}

}

void Helium_3CryoRegionsSideBandTool::Fill_AlandHewgts(std::vector<double> inputWgt, std::vector<double> inputWgt_errors ){

  wgt_Aluminium.push_back(inputWgt.at(0));
  wgt_Aluminium.push_back(inputWgt.at(1));
  wgt_Aluminium.push_back(inputWgt.at(2));
  wgt_Aluminium.push_back(inputWgt.at(3));

  wgt_Helium.push_back(inputWgt.at(4));
  wgt_Helium.push_back(inputWgt.at(5));
  wgt_Helium.push_back(inputWgt.at(6));
  wgt_Helium.push_back(inputWgt.at(7));

  err_Aluminium.push_back(inputWgt_errors.at(0));
  err_Aluminium.push_back(inputWgt_errors.at(1));
  err_Aluminium.push_back(inputWgt_errors.at(2));
  err_Aluminium.push_back(inputWgt_errors.at(3));

  err_Helium.push_back(inputWgt_errors.at(4));
  err_Helium.push_back(inputWgt_errors.at(5));
  err_Helium.push_back(inputWgt_errors.at(6));
  err_Helium.push_back(inputWgt_errors.at(7));
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"~~~~~~Fill Al and He Weights~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  for(auto cat:wgt_Aluminium){std::cout<<"Al wgt = "<< cat<<std::endl;}
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  for(auto cat:wgt_Helium){std::cout<<"He wgt = "<< cat<<std::endl;}
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
}


void Helium_3CryoRegionsSideBandTool::FillPOTScalar(Helium3SideBand& sb, double POTMC_input, double POTData_input ){
sb.POT_MC = POTMC_input;
sb.POT_Data = POTData_input;
}
void Helium_3CryoRegionsSideBandTool::FillPOTScalar(HeliumNSideBand& sb, double POTMC_input, double POTData_input ){
sb.POT_MC = POTMC_input;
sb.POT_Data = POTData_input;
}



void Helium_3CryoRegionsSideBandTool::ConstuctandFill2Playlist_POT_forSideBands(ME_helium_Playlists FullPlaylist , ME_helium_Playlists EmptyPlaylist){

double FullMC_toFullData = POTMap_Full_Data[FullPlaylist] / POTMap_Full_MC[FullPlaylist];
double EmptyMC_toFullData = POTMap_Full_Data[FullPlaylist] / POTMap_Empty_MC[EmptyPlaylist];
double EmptyData_toFullData = POTMap_Full_Data[FullPlaylist] / POTMap_Empty_Data[EmptyPlaylist];

FillPOTScalar(Empty,                      EmptyMC_toFullData, EmptyData_toFullData);
FillPOTScalar(Empty_UpstreamCap,          EmptyMC_toFullData, EmptyData_toFullData);
FillPOTScalar(Empty_Barrel,               EmptyMC_toFullData, EmptyData_toFullData);
FillPOTScalar(Empty_DownstreamCap,        EmptyMC_toFullData, EmptyData_toFullData);
FillPOTScalar(Empty_DownstreamConcaveCap, EmptyMC_toFullData, EmptyData_toFullData);

FillPOTScalar(Full,                      FullMC_toFullData, 1.0 );
FillPOTScalar(Full_UpstreamCap,          FullMC_toFullData, 1.0 );
FillPOTScalar(Full_Barrel,               FullMC_toFullData, 1.0 );
FillPOTScalar(Full_DownstreamCap,        FullMC_toFullData, 1.0 );
FillPOTScalar(Full_DownstreamConcaveCap, FullMC_toFullData, 1.0 );

FillPOTScalar(Full_Empty,                      FullMC_toFullData, 1.0 );
FillPOTScalar(Full_Empty_UpstreamCap,          FullMC_toFullData, 1.0 );
FillPOTScalar(Full_Empty_Barrel,               FullMC_toFullData, 1.0 );
FillPOTScalar(Full_Empty_DownstreamCap,        FullMC_toFullData, 1.0 );
FillPOTScalar(Full_Empty_DownstreamConcaveCap, FullMC_toFullData, 1.0 );
}


void Helium_3CryoRegionsSideBandTool::ConstuctandFill_EmptyPlaylist_POT_forSideBands(ME_helium_Playlists EmptyPlaylist){

  double EmptyMC_toEmptyData = POTMap_Empty_Data[EmptyPlaylist] / POTMap_Empty_MC[EmptyPlaylist];
  FillPOTScalar(Empty,                      EmptyMC_toEmptyData, 1.0);
  FillPOTScalar(Empty_UpstreamCap,          EmptyMC_toEmptyData, 1.0);
  FillPOTScalar(Empty_Barrel,               EmptyMC_toEmptyData, 1.0);
  FillPOTScalar(Empty_DownstreamCap,        EmptyMC_toEmptyData, 1.0);
  FillPOTScalar(Empty_DownstreamConcaveCap, EmptyMC_toEmptyData, 1.0);
}



void Helium_3CryoRegionsSideBandTool::ConstuctandFill_Complete_NuMEPlaylist_POT_forSideBands(std::vector<ME_helium_Playlists> FullPlaylist , std::vector<ME_helium_Playlists> EmptyPlaylist){

  double Total_MCFull_POT  = 0.0;
  double Total_MCEmpty_POT = 0.0;
  double Total_DataFull_POT  = 0.0;
  double Total_DataEmpty_POT  = 0.0;

  for(auto cat:FullPlaylist){
    Total_MCFull_POT+=POTMap_Full_MC[cat];
    Total_DataFull_POT+=POTMap_Full_Data[cat];
  }

  for(auto cat:EmptyPlaylist){
    Total_MCEmpty_POT+=POTMap_Empty_MC[cat];
    Total_DataEmpty_POT+=POTMap_Empty_Data[cat];
  }


  std::cout<< "total POT: Full MC" << Total_MCFull_POT <<std::endl;
  std::cout<< "total POT: Empty MC" << Total_MCEmpty_POT <<std::endl;

  std::cout<< "total POT: Full Data" << Total_DataFull_POT <<std::endl;
  std::cout<< "total POT: Empty Data" << Total_DataEmpty_POT <<std::endl;

  double FullMC_toFullData = Total_DataFull_POT / Total_MCFull_POT;
  double EmptyMC_toFullData = Total_DataFull_POT / Total_MCEmpty_POT;
  double EmptyData_toFullData = Total_DataFull_POT / Total_DataEmpty_POT;


FillPOTScalar(Empty,                      EmptyMC_toFullData, EmptyData_toFullData);
FillPOTScalar(Empty_UpstreamCap,          EmptyMC_toFullData, EmptyData_toFullData);
FillPOTScalar(Empty_Barrel,               EmptyMC_toFullData, EmptyData_toFullData);
FillPOTScalar(Empty_DownstreamCap,        EmptyMC_toFullData, EmptyData_toFullData);
FillPOTScalar(Empty_DownstreamConcaveCap, EmptyMC_toFullData, EmptyData_toFullData);

FillPOTScalar(Full,                      FullMC_toFullData, 1.0 );
FillPOTScalar(Full_UpstreamCap,          FullMC_toFullData, 1.0 );
FillPOTScalar(Full_Barrel,               FullMC_toFullData, 1.0 );
FillPOTScalar(Full_DownstreamCap,        FullMC_toFullData, 1.0 );
FillPOTScalar(Full_DownstreamConcaveCap, FullMC_toFullData, 1.0 );

FillPOTScalar(Full_Empty,                      FullMC_toFullData, 1.0 );
FillPOTScalar(Full_Empty_UpstreamCap,          FullMC_toFullData, 1.0 );
FillPOTScalar(Full_Empty_Barrel,               FullMC_toFullData, 1.0 );
FillPOTScalar(Full_Empty_DownstreamCap,        FullMC_toFullData, 1.0 );
FillPOTScalar(Full_Empty_DownstreamConcaveCap, FullMC_toFullData, 1.0 );
}


void Helium_3CryoRegionsSideBandTool::Get_TotalPOT_scalers(std::vector<ME_helium_Playlists> FullPlaylist , std::vector<ME_helium_Playlists> EmptyPlaylist,
  double &FullMC_toFullData,double &EmptyMC_toFullData, double &EmptyData_toFullData){

  double Total_MCFull_POT  = 0.0;
  double Total_MCEmpty_POT = 0.0;
  double Total_DataFull_POT  = 0.0;
  double Total_DataEmpty_POT  = 0.0;

  for(auto cat:FullPlaylist){
    Total_MCFull_POT+=POTMap_Full_MC[cat];
    Total_DataFull_POT+=POTMap_Full_Data[cat];
  }

  for(auto cat:EmptyPlaylist){
    Total_MCEmpty_POT+=POTMap_Empty_MC[cat];
    Total_DataEmpty_POT+=POTMap_Empty_Data[cat];
  }


  std::cout<< "total POT: Full MC = " << Total_MCFull_POT <<std::endl;
  std::cout<< "total POT: Empty MC = " << Total_MCEmpty_POT <<std::endl;

  std::cout<< "total POT: Full Data = " << Total_DataFull_POT <<std::endl;
  std::cout<< "total POT: Empty Data = " << Total_DataEmpty_POT <<std::endl;

   FullMC_toFullData = Total_DataFull_POT / Total_MCFull_POT;
   EmptyMC_toFullData = Total_DataFull_POT / Total_MCEmpty_POT;
   EmptyData_toFullData = Total_DataFull_POT / Total_DataEmpty_POT;

}


void Helium_3CryoRegionsSideBandTool::FillPOT_NSideBandMap(CryoRegion_HeliumNSideBand_Map &inputMap, double POT_MC_Data, double POT_Empty_data_toFUll){
  // Looping throught each region
  for(auto Region :CryoRegion14_vector){
    FillPOTScalar(inputMap[Region], POT_Empty_data_toFUll, POT_MC_Data );
  }
}

void Helium_3CryoRegionsSideBandTool::FillPOT_HeliumNSideBand_Map(){

  double FullMC_toFullData = 999; double EmptyMC_toFullData = 999; double EmptyData_toFullData = 999;
  Get_TotalPOT_scalers(Full_Playlist , Empty_Playlist, FullMC_toFullData, EmptyMC_toFullData, EmptyData_toFullData);

  if(FullMC_toFullData == 999 || EmptyMC_toFullData == 999 || EmptyData_toFullData == 999){
    std::cout<<"POT failed to be filled in FillPOT_HeliumNSideBand_Map "<< std::endl; assert(false);
  }
std::cout<< "EmptyMC_toFullData = " << EmptyMC_toFullData<<std::endl;
std::cout<< "EmptyData_toFullData = " << EmptyData_toFullData<<std::endl;
  FillPOT_NSideBandMap(CryoRegionMap_Full, FullMC_toFullData,1.0);
  FillPOT_NSideBandMap(CryoRegionMap_Empty, EmptyData_toFullData, EmptyMC_toFullData);
  FillPOT_NSideBandMap(CryoRegionMap_Full_Empty,FullMC_toFullData,1.0);
std::cout<<"Finished Filling POT vars "<< std::endl;
}
//=========================================================================

void Helium_3CryoRegionsSideBandTool::Scale_intit_Empty_NSideBand_Map(){
  std::cout<<"Scale_intit_Empty_NSideBand_Ma"<<std::endl;
  for(auto Region :CryoRegion14_vector){
    std::cout<< "POTScale_SideBand_MC_Material 0 Region : "<<Region<< std::endl;
    POTScale_SideBand_MC_Material(CryoRegionMap_Empty[Region], 0 );
    std::cout<< "POTScale_SideBand_MC_Material 1 Region : "<<Region<< std::endl;
    POTScale_SideBand_MC_Material_FitVars(CryoRegionMap_Empty[Region], 1 );
    std::cout<< "OTScale_SideBand_Data Region : "<<Region<< std::endl;
    POTScale_SideBand_Data(CryoRegionMap_Empty[Region]);
  }

}

void Helium_3CryoRegionsSideBandTool::Scale_intit_Full_NSideBand_Map(){
  for(auto Region :CryoRegion14_vector){
    POTScale_SideBand_MC_Material(CryoRegionMap_Full[Region], 0 );
    POTScale_SideBand_Data(CryoRegionMap_Full[Region]);
  }
}

void Helium_3CryoRegionsSideBandTool::Scale_intit_Full_Empty_NSideBand_Map(){
  for(auto Region :CryoRegion14_vector){
    POTScale_SideBand_MC_Material(CryoRegionMap_Full_Empty[Region], 0 );
    POTScale_SideBand_Data(CryoRegionMap_Full_Empty[Region]);
  }
}




void Helium_3CryoRegionsSideBandTool::ConstuctandFill_Complete_EMPTYNuMEPlaylist_POT_forSideBands( std::vector<ME_helium_Playlists> EmptyPlaylist, std::vector<ME_helium_Playlists> FullPlaylist){

  double Total_MCEmpty_POT = 0.0;
  double Total_DataFull_POT  = 0.0;
  double Total_DataEmpty_POT  = 0.0;

  for(auto cat:EmptyPlaylist){
    Total_MCEmpty_POT+=POTMap_Empty_MC[cat];
    Total_DataEmpty_POT+=POTMap_Empty_Data[cat];
  }

  for(auto cat:FullPlaylist){
    Total_DataFull_POT+=POTMap_Full_Data[cat];
  }


  std::cout<< "total POT: Empty MC" << Total_MCEmpty_POT <<std::endl;
  std::cout<< "total POT: Empty Data" << Total_DataEmpty_POT <<std::endl;
  double EmptyMC_toFullData = Total_DataFull_POT / Total_MCEmpty_POT;
  double EmptyData_toFullData = Total_DataFull_POT / Total_DataEmpty_POT;


  FillPOTScalar(Empty,                      EmptyMC_toFullData, EmptyData_toFullData);
  FillPOTScalar(Empty_UpstreamCap,          EmptyMC_toFullData, EmptyData_toFullData);
  FillPOTScalar(Empty_Barrel,               EmptyMC_toFullData, EmptyData_toFullData);
  FillPOTScalar(Empty_DownstreamCap,        EmptyMC_toFullData, EmptyData_toFullData);
  FillPOTScalar(Empty_DownstreamConcaveCap, EmptyMC_toFullData, EmptyData_toFullData);
}


void Helium_3CryoRegionsSideBandTool::ConstuctandFill_Complete_EMPTYNuMEPlaylist_POT_forSideBands_Xregions( std::vector<ME_helium_Playlists> EmptyPlaylist){


  double Total_MCEmpty_POT = 0.0;
  double Total_DataEmpty_POT  = 0.0;

  for(auto cat:EmptyPlaylist){
    Total_MCEmpty_POT+=POTMap_Empty_MC[cat];
    Total_DataEmpty_POT+=POTMap_Empty_Data[cat];
  }

  std::cout<< "total POT: Empty MC" << Total_MCEmpty_POT <<std::endl;
  std::cout<< "total POT: Empty Data" << Total_DataEmpty_POT <<std::endl;

  double EmptyMC_toEmptyData = Total_DataEmpty_POT / Total_MCEmpty_POT;

  FillPOTScalar(Empty_XoutsideEdges,  EmptyMC_toEmptyData, 1.0);
  FillPOTScalar(Empty_XRightShelf,    EmptyMC_toEmptyData, 1.0);
  FillPOTScalar(Empty_XLeftShelf,     EmptyMC_toEmptyData, 1.0);
  FillPOTScalar(Empty_XCenter,        EmptyMC_toEmptyData, 1.0);

}

void Helium_3CryoRegionsSideBandTool::ConstuctandFill_Complete_EMPTYNuMEPlaylist_POT_forSideBands_XZregions( std::vector<ME_helium_Playlists> EmptyPlaylist){

  double Total_MCEmpty_POT = 0.0;
  double Total_DataEmpty_POT  = 0.0;

  for(auto cat:EmptyPlaylist){
    Total_MCEmpty_POT+=POTMap_Empty_MC[cat];
    Total_DataEmpty_POT+=POTMap_Empty_Data[cat];
  }

  std::cout<< "total POT: Empty MC" << Total_MCEmpty_POT <<std::endl;
  std::cout<< "total POT: Empty Data" << Total_DataEmpty_POT <<std::endl;

  double EmptyMC_toEmptyData = Total_DataEmpty_POT / Total_MCEmpty_POT;

  FillPOTScalar(Empty_XCenter,                     EmptyMC_toEmptyData, 1.0);
  FillPOTScalar(Empty_XRightShelf,                 EmptyMC_toEmptyData, 1.0);
  FillPOTScalar(Empty_XLeftShelf,                  EmptyMC_toEmptyData, 1.0);
  FillPOTScalar(Empty_DownstreamConcaveCap,        EmptyMC_toEmptyData, 1.0);

}




void Helium_3CryoRegionsSideBandTool::InputPDFLabel(std::string input){
  PDF_printingLabel_input = input + ".pdf";
  LatexPdfLabel = input;
}

void Helium_3CryoRegionsSideBandTool::Plot_initHist(std::string Full_info, std::string Empty_info, std::string axisName_fit)
{

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~Ploting Intial Input Hist~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
int FitType = 0;
double POT_ratio =1.0;
std::string title;

title = "Before Fit [E("+ Empty_info + ")] " + axisName_fit;
Plot(Empty, 0, POT_ratio, title, PDF_printingLabel_input, title, "", 0);

PlotCombinedRegions_Fitting_Vars(Empty_UpstreamCap, Empty_Barrel,
  Empty_DownstreamCap, Empty_DownstreamConcaveCap, 0, POT_ratio, title, PDF_printingLabel_input,
  ChiSqrt_beforeCryoVertex_EmptyMap, ChiSqrt_afterCryoVertex_EmptyMap);

PlotCombinedRegions_Fitting_Vars_NoStack(Empty_UpstreamCap,
                                         Empty_Barrel,
                                         Empty_DownstreamCap,
                                         Empty_DownstreamConcaveCap,
                       0,POT_ratio, title, PDF_printingLabel_input,
    ChiSqrt_beforeCryoVertex_EmptyMap, ChiSqrt_afterCryoVertex_EmptyMap);


title = "Before Fit [F("+ Full_info + ")]" + axisName_fit;
Plot(Full, 0, POT_ratio, title, PDF_printingLabel_input, title, "", 0);

PlotCombinedRegions_Fitting_Vars(Full_UpstreamCap,
                                Full_Barrel,
                                Full_DownstreamCap,
                                Full_DownstreamConcaveCap,
                                0,POT_ratio, title, PDF_printingLabel_input,
  ChiSqrt_beforeCryoVertex_FullMap,  ChiSqrt_afterCryoVertex_FullMap);

PlotCombinedRegions_Fitting_Vars_NoStack(Full_UpstreamCap, Full_Barrel,
    Full_DownstreamCap, Full_DownstreamConcaveCap, 0,POT_ratio, title, PDF_printingLabel_input,
    ChiSqrt_beforeCryoVertex_FullMap,  ChiSqrt_afterCryoVertex_FullMap);


title = "Before Fit [F("+Full_info + ") - E(" + Empty_info + ")] " + axisName_fit;
Plot(Full_Empty, 0, POT_ratio, title, PDF_printingLabel_input, title, "", 0);
PlotCombinedRegions_Fitting_Vars(Full_Empty_UpstreamCap,
                                 Full_Empty_Barrel,
                                 Full_Empty_DownstreamCap,
                                 Full_Empty_DownstreamConcaveCap,
                                0,POT_ratio, title, PDF_printingLabel_input,
   ChiSqrt_beforeCryoVertex_Full_EmptyMap, ChiSqrt_afterCryoVertex_Full_EmptyMap);

PlotCombinedRegions_Fitting_Vars_NoStack(Full_Empty_UpstreamCap,
                                         Full_Empty_Barrel,
                                         Full_Empty_DownstreamCap,
                                         Full_Empty_DownstreamConcaveCap,
                                         0,POT_ratio, title, PDF_printingLabel_input,
      ChiSqrt_beforeCryoVertex_Full_EmptyMap, ChiSqrt_afterCryoVertex_Full_EmptyMap);






  title = "Before Fit P_{T,#mu} [E(" + Empty_info + ")]" + axisName_fit;
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Empty, Empty.muon_PT,"muon_PT",title, "P_{T,#mu} [GeV]", true, YaxisMax_PT);
  title = "Before Fit P_{Z,#mu} [E(" + Empty_info + ")]" + axisName_fit;
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Empty, Empty.muon_PZ,"muon_PZ",title, "P_{Z,#mu} [GeV]", true, YaxisMax_PZ);
  title = "Before Fit #theta_{#mu} [E(" + Empty_info + ")]" + axisName_fit;
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Empty, Empty.muon_theta,"muon_theta",title, "#theta_{#mu} [Deg]", true, YaxisMax_theta);
  title = "Before Fit E_{#mu} [E(" + Empty_info + ")]" + axisName_fit;
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Empty, Empty.muon_E,"muon_E",title,"E_{#mu} [GeV]", true, YaxisMax_E );
  title = "Before Fit Distance to Nearest Wall [E(" + Empty_info + ")]" + axisName_fit;
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Empty, Empty.DistancetoEdge,"DistancetoEdge",title, "Distance Nearest wall [mm]");

  title = "Before Fit Distance to USCap  [E(" + Empty_info + ")]" + axisName_fit;
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Empty, Empty.DistancetoUpstreamCap,"DistancetoUSCap",title, "Distance to USCap [mm]");

  title = "Before Fit Distance to DSCap  [E(" + Empty_info + ")]" + axisName_fit;
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Empty, Empty.DistancetoDownstreamCap,"DistancetoDSCap",title, "Distance to DSCap [mm]");

  title = "Before Fit Distance to USCap [RCut] [E(" + Empty_info + ")]" + axisName_fit;
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Empty, Empty.DistancetoUpstreamCap_RCut,"DistancetoUSCap",title, "Distance to USCap [mm]");

  title = "Before Fit Distance to DSCap [RCut] [E(" + Empty_info + ")]" + axisName_fit;
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Empty, Empty.DistancetoDownstreamCap_RCut,"DistancetoDSCap",title, "Distance to DSCap [mm]");

  title = "Before Fit Vertex Z [RCut] [E(" + Empty_info + ")]" + axisName_fit;
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Empty, Empty.Vertex_Z_RCut,"VertexZ",title, "Vertex Z [mm]");

  title = "Before Fit Vertex X [RCut] [E(" + Empty_info + ")]" + axisName_fit;
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Empty, Empty.Vertex_X_RCut,"VertexZ",title, "Vertex X [mm]");

  title = "Before Fit Vertex Y [RCut] [E(" + Empty_info + ")]" + axisName_fit;
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Empty, Empty.Vertex_Y_RCut,"VertexZ",title, "Vertex Y [mm]");

  title = "Before Fit Vertex R [RCut] [E(" + Empty_info + ")]" + axisName_fit;
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Empty, Empty.Vertex_R_RCut,"VertexZ",title, "Vertex R [mm]");



  title = " Before Fit [E(" + Empty_info + ")]" + axisName_fit;

  Plot_4RegionsVar(PDF_printingLabel_input,  POT_ratio, 0,
    Empty_UpstreamCap,
    Empty_Barrel,
    Empty_DownstreamCap,
    Empty_DownstreamConcaveCap,
    title, ChiSqrt_beforeCryoVertex_EmptyMap,  ChiSqrt_beforeMuonVar_EmptyMap,
    ChiSqrt_afterCryoVertex_EmptyMap,  ChiSqrt_afterMuonVar_EmptyMap, FitType);

  Plot_4RegionsVar_noStack(PDF_printingLabel_input,  POT_ratio, 0,
    Empty_UpstreamCap,
    Empty_Barrel,
    Empty_DownstreamCap,
    Empty_DownstreamConcaveCap,
    title, ChiSqrt_beforeCryoVertex_EmptyMap,  ChiSqrt_beforeMuonVar_EmptyMap,
    ChiSqrt_afterCryoVertex_EmptyMap,  ChiSqrt_afterMuonVar_EmptyMap, FitType);




  title = "Before Fit P_{T,#mu} [GeV] [F(" + Full_info + ")]" + axisName_fit;
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Full, Full.muon_PT, "muon_PT", title, "P_{T,#mu} [GeV]" ,true, YaxisMax_PT);
  title = "Before Fit P_{Z,#mu} [GeV] [F(" + Full_info + ")]" + axisName_fit;
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Full, Full.muon_PZ, "muon_PZ", title, "P_{Z,#mu} [GeV]", true, YaxisMax_PZ);
  title = "Before Fit #theta_{#mu} [Deg] [F(" + Full_info + ")]" + axisName_fit;
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Full, Full.muon_theta,"muon_theta", title, "#theta_{#mu} [Deg]", true, YaxisMax_theta);
  title = "Before E_{#mu} [GeV] Fit  [F(" + Full_info + ")]" + axisName_fit;
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Full, Full.muon_E,"muon_E", title, "E_{#mu} [GeV]", true, YaxisMax_E );
  title = "Before Fit Distance to Nearest Wall  [mm] [F(" + Full_info + ")]" + axisName_fit;
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Full, Full.DistancetoEdge,"DistancetoEdge", title, "Distance to Nearest Wall  [mm]");

  title = "Before Fit Distance to USCap [mm] [F(" + Full_info + ")]" + axisName_fit;
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Full, Full.DistancetoUpstreamCap,"DistancetoUSCap",title, "Distance to USCap [mm]");

  title = "Before Fit Distance to DSCap [mm] [F(" + Full_info + ")]" + axisName_fit;
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Full, Full.DistancetoDownstreamCap,"DistancetoDSCap",title, "Distance to DSCap [mm]");

  title = "Before Fit Distance to USCap [mm][RCut] [F(" + Full_info + ")]" + axisName_fit;
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Full, Full.DistancetoUpstreamCap_RCut,"DistancetoUSCap",title, "Distance to USCap [mm]");

  title = "Before Fit Distance to DSCap [mm][RCut] [F(" + Full_info + ")]" + axisName_fit;
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Full, Full.DistancetoDownstreamCap_RCut,"DistancetoDSCap",title, "Distance to DSCap [mm]");

  title = "Before Fit Vertex Z [mm][RCut] [F(" + Full_info + ")]" + axisName_fit;
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Full, Full.Vertex_Z_RCut,"VertexZ",title, "Vertex Z [mm]");

  title = "Before Fit Vertex X [mm][RCut] [F(" + Full_info + ")]" + axisName_fit;
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Full, Full.Vertex_X_RCut,"VertexZ",title, "Vertex X [mm]");

  title = "Before Fit Vertex Y [mm][RCut] [F(" + Full_info + ")]" + axisName_fit;
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Full, Full.Vertex_Y_RCut,"VertexZ",title, "Vertex Y [mm]");

  title = "Before Fit Vertex R [mm][RCut] [F(" + Full_info + ")]" + axisName_fit;
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Full, Full.Vertex_R_RCut,"VertexZ",title, "Vertex R [mm]");



  title = " Before Fit [F(" + Full_info + ")]" + axisName_fit;
  Plot_4RegionsVar(PDF_printingLabel_input,  POT_ratio, 0,
    Full_UpstreamCap,
    Full_Barrel,
    Full_DownstreamCap,
    Full_DownstreamConcaveCap ,
     title, ChiSqrt_beforeCryoVertex_FullMap, ChiSqrt_beforeMuonVar_FullMap,
      ChiSqrt_afterCryoVertex_FullMap, ChiSqrt_afterMuonVar_FullMap, FitType);

  Plot_4RegionsVar_noStack(PDF_printingLabel_input,  POT_ratio, 0,
        Full_UpstreamCap,
        Full_Barrel,
        Full_DownstreamCap,
        Full_DownstreamConcaveCap ,
         title, ChiSqrt_beforeCryoVertex_FullMap, ChiSqrt_beforeMuonVar_FullMap,
          ChiSqrt_afterCryoVertex_FullMap, ChiSqrt_afterMuonVar_FullMap, FitType);



  title = "Before Fit P_{T,#mu} [F(" + Full_info + ") - E(" + Empty_info + ")]" + axisName_fit;
  Plot(PDF_printingLabel_input,  POT_ratio,  0,Full_Empty, Full_Empty.muon_PT,"muon_PT",title, "P_{T,#mu} [GeV]", true, YaxisMax_PT);
  title = "Before Fit P_{Z,#mu} [F(" + Full_info + ") - E(" + Empty_info + ")]" + axisName_fit;
  Plot(PDF_printingLabel_input,  POT_ratio,  0,Full_Empty, Full_Empty.muon_PZ,"muon_PZ",title, "P_{Z,#mu} [GeV]", true, YaxisMax_PZ);
  title = "Before Fit #theta_{#mu} [F(" + Full_info + ") - E(" + Empty_info + ")]" + axisName_fit;
  Plot(PDF_printingLabel_input,  POT_ratio,  0,Full_Empty, Full_Empty.muon_theta,"muon_theta",title, "#theta_{#mu} [Deg]",  true, YaxisMax_theta);
  title = "Before Fit E_{#mu}  [F(" + Full_info + ") - E(" + Empty_info + ")]" + axisName_fit;
  Plot(PDF_printingLabel_input,  POT_ratio,  0,Full_Empty, Full_Empty.muon_E,"muon_E",title, "E_{#mu} [GeV]", true, YaxisMax_E );
  title = "Before Fit Distance to Nearest Wall  [F(" + Full_info + ") - E(" + Empty_info + ")]" + axisName_fit;
  Plot(PDF_printingLabel_input,  POT_ratio,  0,Full_Empty, Full_Empty.DistancetoEdge,"DistancetoEdge",title, "Distance to Nearest Wall  [mm]");

  title = "Before Fit Distance to USCap [F(" + Full_info + ") - E(" + Empty_info + ")]" + axisName_fit;
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Full_Empty, Full_Empty.DistancetoUpstreamCap,"DistancetoUSCap",title, "Distance to USCap [mm]");

  title = "Before Fit Distance to DSCap [F(" + Full_info + ") - E(" + Empty_info + ")]" + axisName_fit;
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Full_Empty, Full_Empty.DistancetoDownstreamCap,"DistancetoDSCap",title, "Distance to DSCap [mm]");

  title = "Before Fit Distance to USCap [RCut] [F(" + Full_info + ") - E(" + Empty_info + ")]" + axisName_fit;
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Full_Empty, Full_Empty.DistancetoUpstreamCap_RCut,"DistancetoUSCap",title, " [RCut] Distance to USCap [mm]");

  title = "Before Fit Distance to DSCap [RCut] [F(" + Full_info + ") - E(" + Empty_info + ")]" + axisName_fit;
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Full_Empty, Full_Empty.DistancetoDownstreamCap_RCut,"DistancetoDSCap",title, "[RCut] Distance to DSCap [mm]");

  title = "Before Fit Vertex Z [RCut] [F(" + Full_info + ") - E(" + Empty_info + ")]" + axisName_fit;
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Full_Empty, Full_Empty.Vertex_Z_RCut,"VertexZ",title, "[RCut] Vertex Z [mm]");

  title = "Before Fit Vertex X [RCut] [F(" + Full_info + ") - E(" + Empty_info + ")]" + axisName_fit;
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Full_Empty, Full_Empty.Vertex_X_RCut,"VertexX",title, "[RCut] Vertex X [mm]");

  title = "Before Fit Vertex Y [RCut] [F(" + Full_info + ") - E(" + Empty_info + ")]" + axisName_fit;
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Full_Empty, Full_Empty.Vertex_Y_RCut,"VertexY",title, "[RCut] Vertex Y [mm]");

  title = "Before Fit Vertex R [RCut] [F(" + Full_info + ") - E(" + Empty_info + ")]" + axisName_fit;
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Full_Empty, Full_Empty.Vertex_R_RCut,"VertexZ",title, "[RCut] Vertex R [mm]");



  title = "Before Fit  [F(" + Full_info + ") - E(" + Empty_info + ")]" + axisName_fit;
  Plot_4RegionsVar(PDF_printingLabel_input,  POT_ratio, 0,
    Full_Empty_UpstreamCap,
    Full_Empty_Barrel,
    Full_Empty_DownstreamCap,
    Full_Empty_DownstreamConcaveCap, title,
      ChiSqrt_beforeCryoVertex_Full_EmptyMap, ChiSqrt_beforeMuonVar_Full_EmptyMap,
       ChiSqrt_afterCryoVertex_Full_EmptyMap, ChiSqrt_afterMuonVar_Full_EmptyMap );

  Plot_4RegionsVar_noStack(PDF_printingLabel_input,  POT_ratio, 0,
    Full_Empty_UpstreamCap,
    Full_Empty_Barrel,
    Full_Empty_DownstreamCap,
    Full_Empty_DownstreamConcaveCap , title,
    ChiSqrt_beforeCryoVertex_Full_EmptyMap, ChiSqrt_beforeMuonVar_Full_EmptyMap,
    ChiSqrt_afterCryoVertex_Full_EmptyMap, ChiSqrt_afterMuonVar_Full_EmptyMap );



  cout<<"======================================================================"<<endl;
  cout<<"Finished Plotting Intial Hist :)"<<endl;
  cout<<"======================================================================"<<endl;

}

void Helium_3CryoRegionsSideBandTool::Plot_initResolutionHist(std::string title_info, std::string Full_info, std::string Empty_info){
std::string title;

title = title_info + " [E("+ Empty_info + ")]" ;
Plot_Resolution_vertex_Material(PDF_printingLabel_input, 1.0, 0,
  Empty_UpstreamCap, Empty_Barrel,  Empty_DownstreamCap, Empty_DownstreamConcaveCap, title);

title = title_info + " [F("+ Full_info + ")]" ;
Plot_Resolution_vertex_Material(PDF_printingLabel_input, 1.0, 0,
  Full_UpstreamCap, Full_Barrel,  Full_DownstreamCap, Full_DownstreamConcaveCap, title);
}


void Helium_3CryoRegionsSideBandTool::Plot_AfterFit_ResolutionHist(std::string title_info, std::string Full_info, std::string Empty_info){
std::string title;

title = title_info + " [E("+ Empty_info + ")]" ;
Plot_Resolution_vertex_Material(PDF_printingLabel_input, 1.0, 1,
  Empty_UpstreamCap, Empty_Barrel,  Empty_DownstreamCap, Empty_DownstreamConcaveCap, title);

title = title_info + " [F("+ Full_info + ")]" ;
Plot_Resolution_vertex_Material(PDF_printingLabel_input, 1.0, 1,
  Full_UpstreamCap, Full_Barrel,  Full_DownstreamCap, Full_DownstreamConcaveCap, title);
}


void Helium_3CryoRegionsSideBandTool::PlotCurrent_init_EmptyHist(std::string title_info ,std::string Empty_info)
{

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~Ploting Intial Input Hist~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

double POT_ratio =1.0;
std::string title;
title = "[E("+ Empty_info + ")]" + title_info;
//Plot(Empty, 0, POT_ratio, title, PDF_printingLabel_input, title, "", 0);

PlotCombinedRegions_Fitting_Vars(Empty_UpstreamCap, Empty_Barrel,
  Empty_DownstreamCap, Empty_DownstreamConcaveCap, 0,POT_ratio, title, PDF_printingLabel_input,
  ChiSqrt_beforeCryoVertex_EmptyMap, ChiSqrt_afterCryoVertex_EmptyMap);


  cout<<"======================================================================"<<endl;
  cout<<"Finished Plotting Intial Hist :)"<<endl;
  cout<<"======================================================================"<<endl;



}
void Helium_3CryoRegionsSideBandTool::PlotCurrent_init_EmptyHist_regionX(std::string title_info ,std::string Empty_info)
{

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~Ploting Intial Input Hist~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

double POT_ratio =1.0;
std::string title;
title = "[E("+ Empty_info + ")]" + title_info;
//Plot(Empty, 0, POT_ratio, title, PDF_printingLabel_input, title, "", 0);

PlotCombinedRegions_Fitting_Vars(Empty_XCenter, Empty_XLeftShelf,
  Empty_XRightShelf, Empty_XoutsideEdges, 0,POT_ratio, title, PDF_printingLabel_input,
  ChiSqrt_beforeCryoVertex_EmptyMap, ChiSqrt_afterCryoVertex_EmptyMap , 3);


  cout<<"======================================================================"<<endl;
  cout<<"Finished Plotting Intial Hist :)"<<endl;
  cout<<"======================================================================"<<endl;

  /*Plot_4RegionsVar(PDF_printingLabel_input,  POT_ratio, 0,
    Empty_XCenter, Empty_XLeftShelf, Empty_XRightShelf, Empty_XoutsideEdges,
    "Before X Regions:", ChiSqrt_beforeCryoVertex_EmptyMap,  ChiSqrt_beforeMuonVar_EmptyMap,
    ChiSqrt_afterCryoVertex_EmptyMap,  ChiSqrt_afterMuonVar_EmptyMap , 3);
*/



}
void Helium_3CryoRegionsSideBandTool::PlotCurrent_init_EmptyHist_regionXZ(std::string title_info ,std::string Empty_info)
{

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~Ploting Intial Input Hist~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

double POT_ratio =1.0;
std::string title;
title = "[E("+ Empty_info + ")]" + title_info;
//Plot(Empty, 0, POT_ratio, title, PDF_printingLabel_input, title, "", 0);

PlotCombinedRegions_Fitting_Vars(Empty_XCenter, Empty_XLeftShelf,
  Empty_XRightShelf, Empty_DownstreamConcaveCap, 0,POT_ratio, title, PDF_printingLabel_input,
  ChiSqrt_beforeCryoVertex_EmptyMap, ChiSqrt_afterCryoVertex_EmptyMap , 4);


  cout<<"======================================================================"<<endl;
  cout<<"Finished Plotting Intial Hist :)"<<endl;
  cout<<"======================================================================"<<endl;

  /*Plot_4RegionsVar(PDF_printingLabel_input,  POT_ratio, 0,
    Empty_XCenter, Empty_XLeftShelf, Empty_XRightShelf, Empty_XoutsideEdges,
    "Before X Regions:", ChiSqrt_beforeCryoVertex_EmptyMap,  ChiSqrt_beforeMuonVar_EmptyMap,
    ChiSqrt_afterCryoVertex_EmptyMap,  ChiSqrt_afterMuonVar_EmptyMap , 3);
*/



}


void Helium_3CryoRegionsSideBandTool::Plot_AfterFitHist(std::string Full_info,
  std::string Empty_info, std::string axisName_fit , int isCombinedFit)
  {

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~Ploting FITTED Hist~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
double POT_ratio =1.0;
std::string title;

title = "After Fit [E(" + Empty_info + ")] " + axisName_fit;
PlotCombinedRegions_Fitting_Vars(  Empty_UpstreamCap, Empty_Barrel, Empty_DownstreamCap, Empty_DownstreamConcaveCap, 1, POT_ratio,
   title, PDF_printingLabel_input, ChiSqrt_beforeCryoVertex_EmptyMap, ChiSqrt_afterCryoVertex_EmptyMap, isCombinedFit);

PlotCombinedRegions_Fitting_Vars_NoStack(Empty_UpstreamCap,
                                         Empty_Barrel,
                                         Empty_DownstreamCap,
                                         Empty_DownstreamConcaveCap, 1, POT_ratio,
      title, PDF_printingLabel_input, ChiSqrt_beforeCryoVertex_EmptyMap, ChiSqrt_afterCryoVertex_EmptyMap, isCombinedFit);


Plot_4RegionsVar(PDF_printingLabel_input,  POT_ratio, 1,
  Empty_UpstreamCap, Empty_Barrel, Empty_DownstreamCap, Empty_DownstreamConcaveCap , title,
  ChiSqrt_beforeCryoVertex_EmptyMap, ChiSqrt_beforeMuonVar_EmptyMap,
  ChiSqrt_afterCryoVertex_EmptyMap, ChiSqrt_afterMuonVar_EmptyMap, isCombinedFit);

Plot_4RegionsVar_noStack(PDF_printingLabel_input,  POT_ratio, 1,
    Empty_UpstreamCap, Empty_Barrel, Empty_DownstreamCap, Empty_DownstreamConcaveCap , title,
    ChiSqrt_beforeCryoVertex_EmptyMap, ChiSqrt_beforeMuonVar_EmptyMap,
    ChiSqrt_afterCryoVertex_EmptyMap, ChiSqrt_afterMuonVar_EmptyMap, isCombinedFit);


title = " After Fit [F(" + Full_info + ")] " + axisName_fit;
PlotCombinedRegions_Fitting_Vars(  Full_UpstreamCap, Full_Barrel, Full_DownstreamCap, Full_DownstreamConcaveCap, 1, POT_ratio,
   title, PDF_printingLabel_input, ChiSqrt_beforeCryoVertex_FullMap, ChiSqrt_afterCryoVertex_FullMap, isCombinedFit);

PlotCombinedRegions_Fitting_Vars_NoStack(  Full_UpstreamCap, Full_Barrel, Full_DownstreamCap, Full_DownstreamConcaveCap, 1, POT_ratio,
      title, PDF_printingLabel_input, ChiSqrt_beforeCryoVertex_FullMap, ChiSqrt_afterCryoVertex_FullMap, isCombinedFit);



Plot_4RegionsVar(PDF_printingLabel_input,  POT_ratio, 1,
  Full_UpstreamCap, Full_Barrel, Full_DownstreamCap, Full_DownstreamConcaveCap , title,
  ChiSqrt_beforeCryoVertex_FullMap, ChiSqrt_beforeMuonVar_FullMap,
ChiSqrt_afterCryoVertex_FullMap, ChiSqrt_afterMuonVar_FullMap, isCombinedFit);



Plot_4RegionsVar_noStack(PDF_printingLabel_input,  POT_ratio, 1,
  Full_UpstreamCap, Full_Barrel, Full_DownstreamCap, Full_DownstreamConcaveCap , title,
  ChiSqrt_beforeCryoVertex_FullMap, ChiSqrt_beforeMuonVar_FullMap,
ChiSqrt_afterCryoVertex_FullMap, ChiSqrt_afterMuonVar_FullMap, isCombinedFit);

  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"Plotting Full - Empty fitting vars"<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

  title = " After Fit [F(" + Full_info + ") - E(" + Empty_info + ")] " + axisName_fit;
  PlotCombinedRegions_Fitting_Vars( Full_Empty_UpstreamCap, Full_Empty_Barrel,
    Full_Empty_DownstreamCap, Full_Empty_DownstreamConcaveCap, 1, POT_ratio,
     title, PDF_printingLabel_input, ChiSqrt_beforeCryoVertex_Full_EmptyMap, ChiSqrt_afterCryoVertex_Full_EmptyMap, isCombinedFit);

PlotCombinedRegions_Fitting_Vars_NoStack(  Full_Empty_UpstreamCap,
           Full_Empty_Barrel,
       Full_Empty_DownstreamCap, Full_Empty_DownstreamConcaveCap, 1, POT_ratio,
        title, PDF_printingLabel_input, ChiSqrt_beforeCryoVertex_Full_EmptyMap, ChiSqrt_afterCryoVertex_Full_EmptyMap, isCombinedFit);

     std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
     std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
     std::cout<<"Plotting Full - Empty Muon vars"<<std::endl;
     std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

  Plot_4RegionsVar(PDF_printingLabel_input,  POT_ratio, 1,
    Full_Empty_UpstreamCap, Full_Empty_Barrel, Full_Empty_DownstreamCap, Full_Empty_DownstreamConcaveCap,
     title, ChiSqrt_beforeCryoVertex_Full_EmptyMap, ChiSqrt_beforeMuonVar_Full_EmptyMap,
     ChiSqrt_afterCryoVertex_Full_EmptyMap, ChiSqrt_afterMuonVar_Full_EmptyMap, isCombinedFit);

  Plot_4RegionsVar_noStack(PDF_printingLabel_input,  POT_ratio, 1,
       Full_Empty_UpstreamCap, Full_Empty_Barrel, Full_Empty_DownstreamCap, Full_Empty_DownstreamConcaveCap,
        title, ChiSqrt_beforeCryoVertex_Full_EmptyMap, ChiSqrt_beforeMuonVar_Full_EmptyMap,
        ChiSqrt_afterCryoVertex_Full_EmptyMap, ChiSqrt_afterMuonVar_Full_EmptyMap, isCombinedFit);



}

void Helium_3CryoRegionsSideBandTool::Plot_AfterFit_EMPTY_Hist(
  std::string title_info, std::string Empty_info, int isCombinedFit)
  {

//std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
//std::cout<<"~~~~~~~~~~~~~Ploting FITTED  EMPTY Hist~~~~~~~~~~~~~~~~~~~"<<std::endl;
//std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
double POT_ratio =1.0;
std::string title;

title  = "[E("+ Empty_info + ")]" + title_info ;
PlotCombinedRegions_Fitting_Vars(  Empty_UpstreamCap, Empty_Barrel, Empty_DownstreamCap, Empty_DownstreamConcaveCap, 1, POT_ratio,
   title, PDF_printingLabel_input, ChiSqrt_beforeCryoVertex_EmptyMap, ChiSqrt_afterCryoVertex_EmptyMap, 1);


}


void Helium_3CryoRegionsSideBandTool::Plot_AfterFit_EMPTY_Hist_regionX_shift(
  std::string title_info, std::string Empty_info, int isCombinedFit)
  {

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~Ploting FITTED  EMPTY Hist~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
double POT_ratio =1.0;
std::string title;

title  = "[E("+ Empty_info + ")]" + title_info ;
PlotCombinedRegions_Fitting_Vars(Empty_XCenter, Empty_XLeftShelf,
  Empty_XRightShelf, Empty_XoutsideEdges, 1, POT_ratio,
   title, PDF_printingLabel_input, ChiSqrt_beforeCryoVertex_EmptyMap, ChiSqrt_afterCryoVertex_EmptyMap,3);



}

void Helium_3CryoRegionsSideBandTool::Plot_AfterFit_EMPTY_Hist_regionXZ_shift(
  std::string title_info, std::string Empty_info, int isCombinedFit)
  {

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~Ploting FITTED  EMPTY Hist~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
double POT_ratio =1.0;
std::string title;

title  = "[E("+ Empty_info + ")]" + title_info ;
PlotCombinedRegions_Fitting_Vars(  Empty_XCenter, Empty_XLeftShelf,
  Empty_XRightShelf, Empty_DownstreamConcaveCap, 1, POT_ratio,
   title, PDF_printingLabel_input, ChiSqrt_beforeCryoVertex_EmptyMap, ChiSqrt_afterCryoVertex_EmptyMap,4);



}


void Helium_3CryoRegionsSideBandTool::Plot_AfterFit_EMPTY_Hist_RegionX(
  std::string title_info, std::string Empty_info, int isCombinedFit)
  {

std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~Ploting FITTED Hist~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
double POT_ratio =1.0;
std::string title;

title  = "[E("+ Empty_info + ")]" + title_info ;
PlotCombinedRegions_Fitting_Vars(Empty_XCenter, Empty_XLeftShelf,
  Empty_XRightShelf, Empty_XoutsideEdges, 1, POT_ratio, title, PDF_printingLabel_input,
   ChiSqrt_beforeCryoVertex_EmptyMap, ChiSqrt_afterCryoVertex_EmptyMap, isCombinedFit);

Plot_4RegionsVar(PDF_printingLabel_input,  POT_ratio, 1,
  Empty_XCenter, Empty_XLeftShelf, Empty_XRightShelf, Empty_XoutsideEdges , title,
  ChiSqrt_beforeCryoVertex_EmptyMap, ChiSqrt_beforeMuonVar_EmptyMap,
  ChiSqrt_afterCryoVertex_EmptyMap, ChiSqrt_afterMuonVar_EmptyMap, isCombinedFit);


}

void Helium_3CryoRegionsSideBandTool::Plot( std::string fitName, std::string pdf_label, std::string xaxislabel)
{
    double POT_ratio = 1.0;
    std::string title;
    title = "Fitting Parameter Before Fit [E()]";
    Plot(Empty,  POT_ratio, fitName, pdf_label,title, xaxislabel);
        title = "Fitting Parameter Before Fit [F()]";
    Plot(Full,  POT_ratio, fitName, pdf_label,title, xaxislabel);


    title = " Total Before Fit [E()]";
    Plot(pdf_label,  POT_ratio,  0, Empty, Empty.muon_PT,"muon_PT",title, "P_{T,#mu} [GeV]");
    Plot(pdf_label,  POT_ratio,  0, Empty, Empty.muon_PZ,"muon_PZ",title, "P_{Z,#mu} [GeV]");
    Plot(pdf_label,  POT_ratio,  0, Empty, Empty.muon_theta,"muon_theta",title, "#theta_{#mu} [Deg]");
    Plot(pdf_label,  POT_ratio,  0, Empty, Empty.muon_E,"muon_E",title, "E_{#mu} [GeV]" );
    Plot(pdf_label,  POT_ratio,  0, Empty, Empty.DistancetoEdge,"DistancetoEdge",title, "Distance to Nearest Wall  [mm]");

    Plot(pdf_label,  POT_ratio,  0, Empty, Empty.DistancetoUpstreamCap, "DistancetoUSCap",title, "Distance to USCap [mm]");
    Plot(pdf_label,  POT_ratio,  0, Empty, Empty.DistancetoDownstreamCap, "DistancetoDSCap",title, "Distance to DSCap [mm]");
    Plot(pdf_label,  POT_ratio,  0, Empty, Empty.DistancetoUpstreamCap_RCut, "DistancetoUSCap",title, "[RCut] Distance to USCap [mm]");
    Plot(pdf_label,  POT_ratio,  0, Empty, Empty.DistancetoDownstreamCap_RCut, "DistancetoDSCap",title, "[RCut] Distance to DSCap [mm]");
    Plot(pdf_label,  POT_ratio,  0, Empty, Empty.Vertex_Z_RCut, "VertexZ",title, "[RCut] Vertex Z [mm]");
    Plot(pdf_label,  POT_ratio,  0, Empty, Empty.Vertex_X_RCut, "VertexX",title, "[RCut] Vertex X [mm]");
    Plot(pdf_label,  POT_ratio,  0, Empty, Empty.Vertex_Y_RCut, "VertexY",title, "[RCut] Vertex Y [mm]");
    Plot(pdf_label,  POT_ratio,  0, Empty, Empty.Vertex_R_RCut, "VertexR",title, "[RCut] Vertex R [mm]");



    Plot(pdf_label,  POT_ratio,  0, Empty_UpstreamCap, Empty_UpstreamCap.muon_PT,"muon_PT",title, "P_{T,#mu} [GeV]");
    Plot(pdf_label,  POT_ratio,  0, Empty_UpstreamCap, Empty_UpstreamCap.muon_PZ,"muon_PZ",title, "P_{Z,#mu} [GeV]");
    Plot(pdf_label,  POT_ratio,  0, Empty_UpstreamCap, Empty_UpstreamCap.muon_theta,"muon_theta",title, "#theta_{#mu} [Deg]");
    Plot(pdf_label,  POT_ratio,  0, Empty_UpstreamCap, Empty_UpstreamCap.muon_E,"muon_E",title, "E_{#mu} [GeV]" );
    Plot(pdf_label,  POT_ratio,  0, Empty_UpstreamCap, Empty_UpstreamCap.DistancetoEdge,"DistancetoEdge",title, "Distance to Nearest Wall  [mm]");

    Plot(pdf_label,  POT_ratio,  0, Empty_UpstreamCap, Empty_UpstreamCap.DistancetoUpstreamCap, "DistancetoUSCap",title, "Distance to USCap [mm]");
    Plot(pdf_label,  POT_ratio,  0, Empty_UpstreamCap, Empty_UpstreamCap.DistancetoDownstreamCap, "DistancetoDSCap",title, "Distance to DSCap [mm]");
    Plot(pdf_label,  POT_ratio,  0, Empty_UpstreamCap, Empty_UpstreamCap.DistancetoUpstreamCap_RCut, "DistancetoUSCap",title, "[RCut] Distance to USCap [mm]");
    Plot(pdf_label,  POT_ratio,  0, Empty_UpstreamCap, Empty_UpstreamCap.DistancetoDownstreamCap_RCut, "DistancetoDSCap",title, "[RCut] Distance to DSCap [mm]");
    Plot(pdf_label,  POT_ratio,  0, Empty_UpstreamCap, Empty_UpstreamCap.Vertex_Z_RCut, "VertexZ",title, "[RCut] Vertex Z [mm]");
    Plot(pdf_label,  POT_ratio,  0, Empty_UpstreamCap, Empty_UpstreamCap.Vertex_X_RCut, "VertexZ",title, "[RCut] Vertex X [mm]");
    Plot(pdf_label,  POT_ratio,  0, Empty_UpstreamCap, Empty_UpstreamCap.Vertex_Y_RCut, "VertexZ",title, "[RCut] Vertex Y [mm]");
    Plot(pdf_label,  POT_ratio,  0, Empty_UpstreamCap, Empty_UpstreamCap.Vertex_R_RCut, "VertexZ",title, "[RCut] Vertex R [mm]");



    Plot(pdf_label,  POT_ratio,  0, Empty_Barrel, Empty_Barrel.muon_PT,"muon_PT",title, "P_{T,#mu} [GeV]");
    Plot(pdf_label,  POT_ratio,  0, Empty_Barrel, Empty_Barrel.muon_PZ,"muon_PZ",title, "P_{Z,#mu} [GeV]");
    Plot(pdf_label,  POT_ratio,  0, Empty_Barrel, Empty_Barrel.muon_theta,"muon_theta",title, "#theta_{#mu} [Deg]");
    Plot(pdf_label,  POT_ratio,  0, Empty_Barrel, Empty_Barrel.muon_E,"muon_E",title, "E_{#mu} [GeV]" );
    Plot(pdf_label,  POT_ratio,  0, Empty_Barrel, Empty_Barrel.DistancetoEdge,"DistancetoEdge",title, "Distance to Nearest Wall  [mm]");
    Plot(pdf_label,  POT_ratio,  0, Empty_Barrel, Empty_Barrel.DistancetoUpstreamCap, "DistancetoUSCap",title, "Distance to USCap [mm]");
    Plot(pdf_label,  POT_ratio,  0, Empty_Barrel, Empty_Barrel.DistancetoDownstreamCap, "DistancetoDSCap",title, "Distance to DSCap [mm]");
    Plot(pdf_label,  POT_ratio,  0, Empty_Barrel, Empty_Barrel.DistancetoUpstreamCap_RCut, "DistancetoUSCap",title, "Distance to USCap [mm]");
    Plot(pdf_label,  POT_ratio,  0, Empty_Barrel, Empty_Barrel.DistancetoDownstreamCap_RCut, "DistancetoDSCap",title, "Distance to DSCap [mm]");
    Plot(pdf_label,  POT_ratio,  0, Empty_Barrel, Empty_Barrel.Vertex_Z_RCut, "VertexZ",title, "Vertex Z [mm]");
    Plot(pdf_label,  POT_ratio,  0, Empty_Barrel, Empty_Barrel.Vertex_X_RCut, "VertexX",title, "Vertex X [mm]");
    Plot(pdf_label,  POT_ratio,  0, Empty_Barrel, Empty_Barrel.Vertex_Y_RCut, "VertexY",title, "Vertex Y [mm]");
    Plot(pdf_label,  POT_ratio,  0, Empty_Barrel, Empty_Barrel.Vertex_R_RCut, "VertexR",title, "Vertex R [mm]");




    Plot(pdf_label,  POT_ratio,  0, Empty_DownstreamCap, Empty_DownstreamCap.muon_PT,   "muon_PT",title,    "P_{T,#mu} [GeV]");
    Plot(pdf_label,  POT_ratio,  0, Empty_DownstreamCap, Empty_DownstreamCap.muon_PZ,   "muon_PZ",title,    "P_{Z,#mu} [GeV]");
    Plot(pdf_label,  POT_ratio,  0, Empty_DownstreamCap, Empty_DownstreamCap.muon_theta,"muon_theta",title, "#theta_{#mu} [Deg]");
    Plot(pdf_label,  POT_ratio,  0, Empty_DownstreamCap, Empty_DownstreamCap.muon_E,    "muon_E",title,     "E_{#mu} [GeV]" );
    Plot(pdf_label,  POT_ratio,  0, Empty_DownstreamCap, Empty_DownstreamCap.DistancetoEdge,"DistancetoEdge",title, "Distance to Nearest Wall  [mm]");

    Plot(pdf_label,  POT_ratio,  0, Empty_DownstreamCap, Empty_DownstreamCap.DistancetoUpstreamCap, "DistancetoUSCap",title, "Distance to USCap [mm]");
    Plot(pdf_label,  POT_ratio,  0, Empty_DownstreamCap, Empty_DownstreamCap.DistancetoDownstreamCap, "DistancetoDSCap",title, "Distance to DSCap [mm]");
    Plot(pdf_label,  POT_ratio,  0, Empty_DownstreamCap, Empty_DownstreamCap.DistancetoUpstreamCap_RCut, "DistancetoUSCap",title, "[RCut] Distance to USCap [mm]");
    Plot(pdf_label,  POT_ratio,  0, Empty_DownstreamCap, Empty_DownstreamCap.DistancetoDownstreamCap_RCut, "DistancetoDSCap",title, "[RCut] Distance to DSCap [mm]");
    Plot(pdf_label,  POT_ratio,  0, Empty_DownstreamCap, Empty_DownstreamCap.Vertex_Z_RCut, "VertexZ",title, "[RCut] Vertex Z [mm]");
    Plot(pdf_label,  POT_ratio,  0, Empty_DownstreamCap, Empty_DownstreamCap.Vertex_X_RCut, "VertexX",title, "[RCut] Vertex X [mm]");
    Plot(pdf_label,  POT_ratio,  0, Empty_DownstreamCap, Empty_DownstreamCap.Vertex_Y_RCut, "VertexY",title, "[RCut] Vertex Y [mm]");
    Plot(pdf_label,  POT_ratio,  0, Empty_DownstreamCap, Empty_DownstreamCap.Vertex_R_RCut, "VertexR",title, "[RCut] Vertex R [mm]");




    title = "Before Fit [F())]";
    //Plot(pdf_label,  POT_ratio,  0, Helium_Full,  Helium_Full.muon_PT,"muon_PT",title, "P_{T,#mu} [GeV]");
    //Plot(pdf_label,  POT_ratio,  0, Helium_Full,  Helium_Full.muon_PZ,"muon_PZ",title, "P_{Z,#mu} [GeV]");
    //Plot(pdf_label,  POT_ratio,  0, Helium_Full,  Helium_Full.muon_theta,"muon_theta",title, "#theta_{#mu} [Deg]");
    //Plot(pdf_label,  POT_ratio,  0, Helium_Full,  Helium_Full.muon_E,"muon_E",title, "E_{#mu} [GeV]" );
    //Plot(pdf_label,  POT_ratio,  0, Helium_Full,  Helium_Full.DistancetoEdge,"DistancetoEdge",title, "Distance to Nearest Wall  [mm]");


    // Plot XSec Variables in Each Side Band
    //std::cout<<"Plotting Data MC With Error Band"<<std::endl;
    //DrawDataMCWithErrorBand(Original);
    //DrawDataMCWithErrorBand(Michel);
    //DrawDataMCWithErrorBand(pID);
    //DrawDataMCWithErrorBand(LowInvMass);
    //DrawDataMCWithErrorBand(HighInvMass);

}

void Helium_3CryoRegionsSideBandTool::FillHistName_Map(Helium3SideBand& sb, std::vector<std::string> histNames , std::vector<Fit_Parms_Names> FitParms ){
//std::cout<<"Filling Map"<<std::endl;
  if(histNames.size() != FitParms.size()){std::cout<<"Error input for FillHistName_Map: vectors size is different , Opps !! "<<std::endl;assert(false);}

  for(int i = 0; i < histNames.size(); i++){
    //std::cout<<"FIlline Hist Name: "<< histNames.at(i)<<std::endl;
    sb.HistName_Map.insert ( std::pair<Fit_Parms_Names,std::string>(FitParms.at(i),histNames.at(i)));
  }
}

void Helium_3CryoRegionsSideBandTool::ConstructVertex_FitHistName_Map(Helium3SideBand& sb, std::string ExtraTag){
  //std::cout<<"Filling Map"<<std::endl;

  std::string Var;
  Var = "h_Data_CryoVertex_X" + ExtraTag;
  sb.HistName_Map.insert ( std::pair<Fit_Parms_Names,std::string>( kh_Name_Data_fitTo_vertexX, Var));
  Var = "h_Data_CryoVertex_Y" + ExtraTag;
  sb.HistName_Map.insert ( std::pair<Fit_Parms_Names,std::string>( kh_Name_Data_fitTo_vertexY, Var ));
  Var = "h_Data_CryoVertex_Z" + ExtraTag;
  sb.HistName_Map.insert ( std::pair<Fit_Parms_Names,std::string>( kh_Name_Data_fitTo_vertexZ, Var ));
  Var = "h_Data_CryoVertex_R" + ExtraTag;
  sb.HistName_Map.insert ( std::pair<Fit_Parms_Names,std::string>( kh_Name_Data_fitTo_vertexR, Var ));

  Var = "h_CryoVertex_X" + ExtraTag;
  sb.HistName_Map.insert ( std::pair<Fit_Parms_Names,std::string>( kh_Name_MC_fitTo_vertexX, Var));

  Var = "h_CryoVertex_Y" + ExtraTag;
  sb.HistName_Map.insert ( std::pair<Fit_Parms_Names,std::string>( kh_Name_MC_fitTo_vertexY, Var));

  Var = "h_CryoVertex_Z" + ExtraTag;
  sb.HistName_Map.insert ( std::pair<Fit_Parms_Names,std::string>( kh_Name_MC_fitTo_vertexZ, Var));

  Var = "h_CryoVertex_R" + ExtraTag;
  sb.HistName_Map.insert ( std::pair<Fit_Parms_Names,std::string>( kh_Name_MC_fitTo_vertexR, Var));

}
void Helium_3CryoRegionsSideBandTool::ConstructVertex_FitHistName_MapData(Helium3SideBand& sb, std::string ExtraTag){
  //std::cout<<"Filling Map"<<std::endl;

  std::string Var;
  Var = "h_Data_CryoVertex_X" + ExtraTag;
  sb.HistName_Map.insert ( std::pair<Fit_Parms_Names,std::string>( kh_Name_Data_fitTo_vertexX, Var));
  Var = "h_Data_CryoVertex_Y" + ExtraTag;
  sb.HistName_Map.insert ( std::pair<Fit_Parms_Names,std::string>( kh_Name_Data_fitTo_vertexY, Var ));
  Var = "h_Data_CryoVertex_Z" + ExtraTag;
  sb.HistName_Map.insert ( std::pair<Fit_Parms_Names,std::string>( kh_Name_Data_fitTo_vertexZ, Var ));
  Var = "h_Data_CryoVertex_R" + ExtraTag;
  sb.HistName_Map.insert ( std::pair<Fit_Parms_Names,std::string>( kh_Name_Data_fitTo_vertexR, Var ));


}

void Helium_3CryoRegionsSideBandTool::ConstructVertex_FitMC_shifted_HistName_Map(Helium3SideBand& sb, std::string ExtraTag){
  //std::cout<<"Filling Map"<<std::endl;

  std::string Var;

  Var = "h_offset_Vertex_X" + ExtraTag;
  sb.HistName_Map.insert ( std::pair<Fit_Parms_Names,std::string>( kh_Name_MC_fitTo_vertexX, Var));

  Var = "h_offset_Vertex_Y" + ExtraTag;
  sb.HistName_Map.insert ( std::pair<Fit_Parms_Names,std::string>( kh_Name_MC_fitTo_vertexY, Var));

  Var = "h_offset_Vertex_Z" + ExtraTag;
  sb.HistName_Map.insert ( std::pair<Fit_Parms_Names,std::string>( kh_Name_MC_fitTo_vertexZ, Var));

  Var = "h_offset_Vertex_R" + ExtraTag;
  sb.HistName_Map.insert ( std::pair<Fit_Parms_Names,std::string>( kh_Name_MC_fitTo_vertexR, Var));


}



MnvH1D* Helium_3CryoRegionsSideBandTool::GetMnvH1D(TFile* f, std::string var_name){
  //std::cout<<"Initialize Hist Name: " << var_name<< std::endl;
  MnvH1D* h = new MnvH1D(*dynamic_cast<MnvH1D*>(f->Get(var_name.c_str())) );
  if (h==0) std::cout << "Could not get 1D hist " << var_name << "\n";
  h->SetDirectory(NULL);
  return h;
}


std::string Helium_3CryoRegionsSideBandTool::GetName(){
return Full.name;
}


  void Helium_3CryoRegionsSideBandTool::initSideBands_2playlist( const ME_helium_Playlists Full_Playlist, const ME_helium_Playlists Empty_Playlist )
  {
    std::cout<<"Inside:initSideBands_2playlist() "<<std::endl;

    std::cout<<"~~~~initSideBand_FitHistograms : for Helium Empty WITH REGION upstream Cap , Barrel , and downstream Cap: ~~~~~~ "<<std::endl;
    std::cout<<"Init SidesBands for Full "<<std::endl;
    initSideBand_FitHistograms(Empty,              TFile_Map_Empty_MC[Empty_Playlist] ,TFile_Map_Empty_Data[Empty_Playlist]);
    initSideBand_FitHistograms(Empty_UpstreamCap,  TFile_Map_Empty_MC[Empty_Playlist] ,TFile_Map_Empty_Data[Empty_Playlist]);
    initSideBand_FitHistograms(Empty_Barrel,       TFile_Map_Empty_MC[Empty_Playlist] ,TFile_Map_Empty_Data[Empty_Playlist]);
    initSideBand_FitHistograms(Empty_DownstreamCap,TFile_Map_Empty_MC[Empty_Playlist] ,TFile_Map_Empty_Data[Empty_Playlist]);
    initSideBand_FitHistograms(Empty_DownstreamConcaveCap,TFile_Map_Empty_MC[Empty_Playlist] ,TFile_Map_Empty_Data[Empty_Playlist]);
    std::cout<<"Init SidesBands for Full "<<std::endl;
    initSideBand_FitHistograms(Full,              TFile_Map_Full_MC[Full_Playlist] ,TFile_Map_Full_Data[Full_Playlist]);
    initSideBand_FitHistograms(Full_UpstreamCap,  TFile_Map_Full_MC[Full_Playlist] ,TFile_Map_Full_Data[Full_Playlist]);
    initSideBand_FitHistograms(Full_Barrel,       TFile_Map_Full_MC[Full_Playlist] ,TFile_Map_Full_Data[Full_Playlist]);
    initSideBand_FitHistograms(Full_DownstreamCap,TFile_Map_Full_MC[Full_Playlist] ,TFile_Map_Full_Data[Full_Playlist]);
    initSideBand_FitHistograms(Full_DownstreamConcaveCap,TFile_Map_Full_MC[Full_Playlist] ,TFile_Map_Full_Data[Full_Playlist]);
    std::cout<<"Init SidesBands for Full "<<std::endl;
    initSideBand_FitHistograms(Full_Empty,              TFile_Map_Full_MC[Full_Playlist] ,TFile_Map_Full_Data[Full_Playlist]);
    initSideBand_FitHistograms(Full_Empty_UpstreamCap,  TFile_Map_Full_MC[Full_Playlist] ,TFile_Map_Full_Data[Full_Playlist]);
    initSideBand_FitHistograms(Full_Empty_Barrel,       TFile_Map_Full_MC[Full_Playlist] ,TFile_Map_Full_Data[Full_Playlist]);
    initSideBand_FitHistograms(Full_Empty_DownstreamCap,TFile_Map_Full_MC[Full_Playlist] ,TFile_Map_Full_Data[Full_Playlist]);
    initSideBand_FitHistograms(Full_Empty_DownstreamConcaveCap, TFile_Map_Full_MC[Full_Playlist] ,TFile_Map_Full_Data[Full_Playlist]);


    initSideBand_XSecHistograms(Empty , "",                              TFile_Map_Empty_MC[Empty_Playlist] ,TFile_Map_Empty_Data[Empty_Playlist]);
    initSideBand_XSecHistograms(Empty_UpstreamCap ,    "_UpstreamCap",   TFile_Map_Empty_MC[Empty_Playlist] ,TFile_Map_Empty_Data[Empty_Playlist]);
    initSideBand_XSecHistograms(Empty_Barrel ,         "_Barrel",        TFile_Map_Empty_MC[Empty_Playlist] ,TFile_Map_Empty_Data[Empty_Playlist]);
    initSideBand_XSecHistograms(Empty_DownstreamCap ,  "_DownstreamCap", TFile_Map_Empty_MC[Empty_Playlist] ,TFile_Map_Empty_Data[Empty_Playlist]);
    initSideBand_XSecHistograms(Empty_DownstreamConcaveCap , "_Downstream_ConcaveCap", TFile_Map_Empty_MC[Empty_Playlist] ,TFile_Map_Empty_Data[Empty_Playlist]);

    initSideBand_XSecHistograms(Full , "",                             TFile_Map_Full_MC[Full_Playlist] ,TFile_Map_Full_Data[Full_Playlist]);
    initSideBand_XSecHistograms(Full_UpstreamCap ,   "_UpstreamCap",   TFile_Map_Full_MC[Full_Playlist] ,TFile_Map_Full_Data[Full_Playlist]);
    initSideBand_XSecHistograms(Full_Barrel ,        "_Barrel",        TFile_Map_Full_MC[Full_Playlist] ,TFile_Map_Full_Data[Full_Playlist]);
    initSideBand_XSecHistograms(Full_DownstreamCap , "_DownstreamCap", TFile_Map_Full_MC[Full_Playlist] ,TFile_Map_Full_Data[Full_Playlist]);
    initSideBand_XSecHistograms(Full_DownstreamConcaveCap , "_Downstream_ConcaveCap", TFile_Map_Full_MC[Full_Playlist] ,TFile_Map_Full_Data[Full_Playlist]);

    initSideBand_XSecHistograms(Full_Empty , "",                             TFile_Map_Full_MC[Full_Playlist] ,TFile_Map_Full_Data[Full_Playlist]);
    initSideBand_XSecHistograms(Full_Empty_UpstreamCap ,   "_UpstreamCap",   TFile_Map_Full_MC[Full_Playlist] ,TFile_Map_Full_Data[Full_Playlist]);
    initSideBand_XSecHistograms(Full_Empty_Barrel ,        "_Barrel",        TFile_Map_Full_MC[Full_Playlist] ,TFile_Map_Full_Data[Full_Playlist]);
    initSideBand_XSecHistograms(Full_Empty_DownstreamCap , "_DownstreamCap", TFile_Map_Full_MC[Full_Playlist] ,TFile_Map_Full_Data[Full_Playlist]);
    initSideBand_XSecHistograms(Full_Empty_DownstreamConcaveCap , "_Downstream_ConcaveCap", TFile_Map_Full_MC[Full_Playlist] ,TFile_Map_Full_Data[Full_Playlist]);


    std::cout<<"initSideBand_AllUniverses : for Helium_Full "<<std::endl;
      initSideBand_AllUniverses(Empty);
      //std::cout<<"initSideBand_AllUniverses : for Helium_Empty "<<std::endl;
      //initSideBand_AllUniverses(Helium_Empty)


      //init_POTScale_AllHist();
      std::cout<<"POT Scale All inti hist"<<std::endl;

      //initSideBand_AllUniverses(Helium_Full_Empty);


      //std::cout<<"GetStatistics : for Helium_Full "<<std::endl;
      //GetStatistics(Helium_Full);
      //std::cout<<"GetStatistics : for Helium_Empty "<<std::endl;
      //GetStatistics(Helium_Empty);

      // Calc Global ChiSq Before Fit
      /*
      for (unsigned int i = 0; i < Helium_Full.data_all_universes.size(); ++i){
          double Global_ChiSq = calc_Global_ChiSq(i, 1.0);
          ChiSq_before_fit.push_back(Global_ChiSq);
      }
*/
}

void Helium_3CryoRegionsSideBandTool::initSideBands_EmptyDataplaylist( const ME_helium_Playlists Empty_Playlist )
{
  std::cout<<"Inside:initSideBands_EmptyDataplaylist() "<<std::endl;

  std::cout<<"~~~~initSideBand Data FitHistograms : for Helium Empty WITH REGION upstream Cap , Barrel , and downstream Cap: ~~~~~~ "<<std::endl;
  std::cout<<"Init SidesBands for Empty "<<std::endl;

  initSideBand_FitDataHistograms(Empty ,                     TFile_Map_Empty_Data[Empty_Playlist]  );
  initSideBand_FitDataHistograms(Empty_UpstreamCap ,         TFile_Map_Empty_Data[Empty_Playlist]  );
  initSideBand_FitDataHistograms(Empty_Barrel ,              TFile_Map_Empty_Data[Empty_Playlist]  );
  initSideBand_FitDataHistograms(Empty_DownstreamCap ,       TFile_Map_Empty_Data[Empty_Playlist]  );
  initSideBand_FitDataHistograms(Empty_DownstreamConcaveCap ,TFile_Map_Empty_Data[Empty_Playlist]  );


}

void Helium_3CryoRegionsSideBandTool::initSideBands_CombinedEmptyDataplaylist()
{
  std::cout<<"Inside:initSideBands_EmptyDataplaylist() "<<std::endl;

  std::cout<<"~~~~initSideBand Data FitHistograms : for Helium Empty WITH REGION upstream Cap , Barrel , and downstream Cap: ~~~~~~ "<<std::endl;
  std::cout<<"Init SidesBands for Empty "<<std::endl;
  initSideBand_PlaylistCombinedFitDataHistograms(Empty ,                     TFile_Map_Empty_Data  );
  initSideBand_PlaylistCombinedFitDataHistograms(Empty_UpstreamCap ,         TFile_Map_Empty_Data  );
  initSideBand_PlaylistCombinedFitDataHistograms(Empty_Barrel ,              TFile_Map_Empty_Data  );
  initSideBand_PlaylistCombinedFitDataHistograms(Empty_DownstreamCap ,       TFile_Map_Empty_Data  );
  initSideBand_PlaylistCombinedFitDataHistograms(Empty_DownstreamConcaveCap ,TFile_Map_Empty_Data  );


}

void Helium_3CryoRegionsSideBandTool::initSideBands_CombinedEmptyDataplaylist_Combinedonly()
{
  std::cout<<"Inside:initSideBands_EmptyDataplaylist() "<<std::endl;

  std::cout<<"~~~~initSideBand Data FitHistograms : for Helium Empty WITH REGION upstream Cap , Barrel , and downstream Cap: ~~~~~~ "<<std::endl;
  std::cout<<"Init SidesBands for Empty "<<std::endl;
    ConstructVertex_FitHistName_Map(Empty, "");
  initSideBand_PlaylistCombinedFitDataHistograms(Empty ,                     TFile_Map_Empty_Data  );

}


void Helium_3CryoRegionsSideBandTool::initSideBands_Multipleplaylists( ME_helium_Playlists Full_Playlist,  ME_helium_Playlists Empty_Playlist )
{
  std::cout<<"Inside:initSideBands_Multipleplaylists() "<<std::endl;

  std::cout<<"~~~~initSideBand_FitHistograms : for Helium Empty WITH REGION upstream Cap , Barrel , and downstream Cap: ~~~~~~ "<<std::endl;
  std::cout<<"Init SidesBands for Full "<<std::endl;

  initSideBand_FitHistogramsFromTFileMap(Empty,                      TFile_Map_Empty_MC, TFile_Map_Empty_Data, Empty_Playlist);
  initSideBand_FitHistogramsFromTFileMap(Empty_UpstreamCap,          TFile_Map_Empty_MC, TFile_Map_Empty_Data, Empty_Playlist);
  initSideBand_FitHistogramsFromTFileMap(Empty_Barrel,               TFile_Map_Empty_MC, TFile_Map_Empty_Data, Empty_Playlist);
  initSideBand_FitHistogramsFromTFileMap(Empty_DownstreamCap,        TFile_Map_Empty_MC, TFile_Map_Empty_Data, Empty_Playlist);
  initSideBand_FitHistogramsFromTFileMap(Empty_DownstreamConcaveCap, TFile_Map_Empty_MC, TFile_Map_Empty_Data, Empty_Playlist);

  std::cout<<"Init SidesBands for Full "<<std::endl;
  initSideBand_FitHistogramsFromTFileMap(Full,                      TFile_Map_Full_MC, TFile_Map_Full_Data, Full_Playlist);
  initSideBand_FitHistogramsFromTFileMap(Full_UpstreamCap,          TFile_Map_Full_MC, TFile_Map_Full_Data, Full_Playlist);
  initSideBand_FitHistogramsFromTFileMap(Full_Barrel,               TFile_Map_Full_MC, TFile_Map_Full_Data, Full_Playlist);
  initSideBand_FitHistogramsFromTFileMap(Full_DownstreamCap,        TFile_Map_Full_MC, TFile_Map_Full_Data, Full_Playlist);
  initSideBand_FitHistogramsFromTFileMap(Full_DownstreamConcaveCap, TFile_Map_Full_MC, TFile_Map_Full_Data, Full_Playlist);
  std::cout<<"Init SidesBands for Full "<<std::endl;
  initSideBand_FitHistogramsFromTFileMap(Full_Empty,                      TFile_Map_Full_MC, TFile_Map_Full_Data, Full_Playlist);
  initSideBand_FitHistogramsFromTFileMap(Full_Empty_UpstreamCap,          TFile_Map_Full_MC, TFile_Map_Full_Data, Full_Playlist);
  initSideBand_FitHistogramsFromTFileMap(Full_Empty_Barrel,               TFile_Map_Full_MC, TFile_Map_Full_Data, Full_Playlist);
  initSideBand_FitHistogramsFromTFileMap(Full_Empty_DownstreamCap,        TFile_Map_Full_MC, TFile_Map_Full_Data, Full_Playlist);
  initSideBand_FitHistogramsFromTFileMap(Full_Empty_DownstreamConcaveCap, TFile_Map_Full_MC, TFile_Map_Full_Data, Full_Playlist);

  initSideBand_XSecHistograms(Empty , "",                                          TFile_Map_Empty_MC, TFile_Map_Empty_Data, Empty_Playlist );
  initSideBand_XSecHistograms(Empty_UpstreamCap,          "_UpstreamCap",          TFile_Map_Empty_MC, TFile_Map_Empty_Data, Empty_Playlist );
  initSideBand_XSecHistograms(Empty_Barrel,               "_Barrel",               TFile_Map_Empty_MC, TFile_Map_Empty_Data, Empty_Playlist );
  initSideBand_XSecHistograms(Empty_DownstreamCap,        "_DownstreamCap",        TFile_Map_Empty_MC, TFile_Map_Empty_Data, Empty_Playlist );
  initSideBand_XSecHistograms(Empty_DownstreamConcaveCap, "_Downstream_ConcaveCap", TFile_Map_Empty_MC, TFile_Map_Empty_Data, Empty_Playlist );

  initSideBand_XSecHistograms(Full , "",                                          TFile_Map_Full_MC, TFile_Map_Full_Data, Full_Playlist );
  initSideBand_XSecHistograms(Full_UpstreamCap,          "_UpstreamCap",          TFile_Map_Full_MC, TFile_Map_Full_Data, Full_Playlist );
  initSideBand_XSecHistograms(Full_Barrel,               "_Barrel",               TFile_Map_Full_MC, TFile_Map_Full_Data, Full_Playlist );
  initSideBand_XSecHistograms(Full_DownstreamCap,        "_DownstreamCap",        TFile_Map_Full_MC, TFile_Map_Full_Data, Full_Playlist );
  initSideBand_XSecHistograms(Full_DownstreamConcaveCap, "_Downstream_ConcaveCap", TFile_Map_Full_MC, TFile_Map_Full_Data, Full_Playlist );

  initSideBand_XSecHistograms(Full_Empty , "",                                          TFile_Map_Full_MC, TFile_Map_Full_Data, Full_Playlist );
  initSideBand_XSecHistograms(Full_Empty_UpstreamCap,          "_UpstreamCap",          TFile_Map_Full_MC, TFile_Map_Full_Data, Full_Playlist );
  initSideBand_XSecHistograms(Full_Empty_Barrel,               "_Barrel",               TFile_Map_Full_MC, TFile_Map_Full_Data, Full_Playlist );
  initSideBand_XSecHistograms(Full_Empty_DownstreamCap,        "_DownstreamCap",        TFile_Map_Full_MC, TFile_Map_Full_Data, Full_Playlist );
  initSideBand_XSecHistograms(Full_Empty_DownstreamConcaveCap, "_Downstream_ConcaveCap", TFile_Map_Full_MC, TFile_Map_Full_Data, Full_Playlist );



  std::cout<<"initSideBand_AllUniverses : for Helium_Full "<<std::endl;
    initSideBand_AllUniverses(Empty);
    //std::cout<<"initSideBand_AllUniverses : for Helium_Empty "<<std::endl;
    //initSideBand_AllUniverses(Helium_Empty)


    //init_POTScale_AllHist();
    std::cout<<"POT Scale All inti hist"<<std::endl;

    //initSideBand_AllUniverses(Helium_Full_Empty);


    //std::cout<<"GetStatistics : for Helium_Full "<<std::endl;
    //GetStatistics(Helium_Full);
    //std::cout<<"GetStatistics : for Helium_Empty "<<std::endl;
    //GetStatistics(Helium_Empty);

    // Calc Global ChiSq Before Fit

    //for (unsigned int i = 0; i < Helium_Full.data_all_universes.size(); ++i){
        //double Global_ChiSq = calc_Global_ChiSq(i, 1.0);
        //ChiSq_before_fit.push_back(Global_ChiSq);
    //}



}

void Helium_3CryoRegionsSideBandTool::initSideBands_Multipleplaylists_Xregions( ME_helium_Playlists Empty_Playlist )
{
  std::cout<<"Inside:initSideBands_Multipleplaylists_Xregions() "<<std::endl;
  std::cout<<"~~~~initSideBand_FitHistograms : for Helium Empty WITH REGION Center right and left shelfs and outsideedges: ~~~~~~ "<<std::endl;
  std::cout<<"Init SidesBands for Full "<<std::endl;

  initSideBand_FitHistogramsFromTFileMap(Empty,                   TFile_Map_Empty_MC, TFile_Map_Empty_Data, Empty_Playlist);
  initSideBand_FitHistogramsFromTFileMap(Empty_XoutsideEdges,     TFile_Map_Empty_MC, TFile_Map_Empty_Data, Empty_Playlist);
  initSideBand_FitHistogramsFromTFileMap(Empty_XRightShelf,       TFile_Map_Empty_MC, TFile_Map_Empty_Data, Empty_Playlist);
  initSideBand_FitHistogramsFromTFileMap(Empty_XLeftShelf,        TFile_Map_Empty_MC, TFile_Map_Empty_Data, Empty_Playlist);
  initSideBand_FitHistogramsFromTFileMap(Empty_XCenter,           TFile_Map_Empty_MC, TFile_Map_Empty_Data, Empty_Playlist);


  //initSideBand_XSecHistograms(Empty , "",                            TFile_Map_Empty_MC, TFile_Map_Empty_Data, Empty_Playlist );
  //initSideBand_XSecHistograms(Empty_XoutsideEdges, "_XoutsideEdges", TFile_Map_Empty_MC, TFile_Map_Empty_Data, Empty_Playlist );
  //initSideBand_XSecHistograms(Empty_XRightShelf,   "_XRightShelf",   TFile_Map_Empty_MC, TFile_Map_Empty_Data, Empty_Playlist );
  //initSideBand_XSecHistograms(Empty_XLeftShelf,    "_XLeftShelf",    TFile_Map_Empty_MC, TFile_Map_Empty_Data, Empty_Playlist );
  //initSideBand_XSecHistograms(Empty_XCenter,       "_XCenter",       TFile_Map_Empty_MC, TFile_Map_Empty_Data, Empty_Playlist );

  std::cout<<"initSideBand_AllUniverses : for Helium_Full "<<std::endl;
    initSideBand_AllUniverses(Empty);
    //std::cout<<"initSideBand_AllUniverses : for Helium_Empty "<<std::endl;
    //initSideBand_AllUniverses(Helium_Empty)


    //init_POTScale_AllHist();
    std::cout<<"POT Scale All inti hist"<<std::endl;


}


  MnvH2D* Helium_3CryoRegionsSideBandTool::GetMnvH2D(TFile* f, std::string var_name){
    //std::cout<<"Initialize Hist Name: " << var_name<< std::endl;
    MnvH2D* h = new MnvH2D( * dynamic_cast<MnvH2D*>(f->Get(var_name.c_str())) );
    if (h==0) std::cout << "Could not get 1D hist " << var_name << "\n";
       h->SetDirectory(NULL);
       return h;

  }

  void Helium_3CryoRegionsSideBandTool::FillResolutionHistnames(Resolution_hists& resolution_var , std::string hist_name){
    resolution_var.name = hist_name;
  }

  void Helium_3CryoRegionsSideBandTool::FillResolutionHistnames(Helium3SideBand& sb){
    sb.Vertex_X_Resolution.name = "h_CryoVertex_X";
    FillResolutionHistnames(sb.Resolution_hists_Vertex_X , "h_CryoVertex_X");
    sb.Vertex_Y_Resolution.name = "h_CryoVertex_Y";
    FillResolutionHistnames(sb.Resolution_hists_Vertex_Y, "h_CryoVertex_Y" );
    sb.Vertex_Z_Resolution.name = "h_CryoVertex_Z";
    FillResolutionHistnames(sb.Resolution_hists_Vertex_Z, "h_CryoVertex_Z" );
    sb.Vertex_R_Resolution.name = "h_CryoVertex_R";
    FillResolutionHistnames(sb.Resolution_hists_Vertex_R, "h_CryoVertex_R" );
  }

  void Helium_3CryoRegionsSideBandTool::FillResolutionHistnames(){
        FillResolutionHistnames(Empty);
        FillResolutionHistnames(Empty_UpstreamCap);
        FillResolutionHistnames(Empty_Barrel);
        FillResolutionHistnames(Empty_DownstreamCap);
        FillResolutionHistnames(Empty_DownstreamConcaveCap);

        FillResolutionHistnames(Full);
        FillResolutionHistnames(Full_UpstreamCap);
        FillResolutionHistnames(Full_Barrel);
        FillResolutionHistnames(Full_DownstreamCap);
        FillResolutionHistnames(Full_DownstreamConcaveCap);


  }


void Helium_3CryoRegionsSideBandTool::initSideBand_FitHistograms(Helium3SideBand& sb, TFile* TFile_MC, TFile* TFile_Data )
{

    std::string var;
    std::cout<<"Inside:initSideBand_FitHistograms "<<std::endl;
    std::cout <<"SideBand has Name : "<< sb.name << std::endl;

      var = sb.HistName_Map[kh_Name_Data_fitTo_vertexX];
      sb.MnvH1D_Vertex_X_data = GetMnvH1D(TFile_Data, var);

      var = sb.HistName_Map[kh_Name_Data_fitTo_vertexY];
      sb.MnvH1D_Vertex_Y_data = GetMnvH1D(TFile_Data, var);

      var = sb.HistName_Map[kh_Name_Data_fitTo_vertexZ];
      sb.MnvH1D_Vertex_Z_data = GetMnvH1D(TFile_Data, var);

      var = sb.HistName_Map[kh_Name_Data_fitTo_vertexR];
      sb.MnvH1D_Vertex_R_data = GetMnvH1D(TFile_Data, var);

      /////////////////////////////////

      var = sb.HistName_Map[kh_Name_MC_fitTo_vertexX];
      sb.MnvH1D_Vertex_X_mc_total = GetMnvH1D(TFile_MC, var);

      var = sb.HistName_Map[kh_Name_MC_fitTo_vertexY];
      sb.MnvH1D_Vertex_Y_mc_total = GetMnvH1D(TFile_MC, var);

      var = sb.HistName_Map[kh_Name_MC_fitTo_vertexZ];
      sb.MnvH1D_Vertex_Z_mc_total = GetMnvH1D(TFile_MC, var);

      var = sb.HistName_Map[kh_Name_MC_fitTo_vertexR];
      sb.MnvH1D_Vertex_R_mc_total = GetMnvH1D(TFile_MC, var);

      /////////////////////////////////////

      var = sb.HistName_Map[kh_Name_MC_fitTo_vertexX] + "_Material_Helium";
      sb.MnvH1D_Vertex_X_Helium[0] = GetMnvH1D(TFile_MC, var);
      var = sb.HistName_Map[kh_Name_MC_fitTo_vertexX] + "_Material_Aluminium";
      sb.MnvH1D_Vertex_X_Aluminium[0]= GetMnvH1D(TFile_MC, var);
      var = sb.HistName_Map[kh_Name_MC_fitTo_vertexX] + "_Material_Carbon";
      sb.MnvH1D_Vertex_X_Carbon[0]= GetMnvH1D(TFile_MC, var);
      var = sb.HistName_Map[kh_Name_MC_fitTo_vertexX] + "_Material_Iron";
      sb.MnvH1D_Vertex_X_Iron[0]= GetMnvH1D(TFile_MC, var);
      var = sb.HistName_Map[kh_Name_MC_fitTo_vertexX] + "_Material_Lead";
      sb.MnvH1D_Vertex_X_Lead[0]= GetMnvH1D(TFile_MC, var);
      var = sb.HistName_Map[kh_Name_MC_fitTo_vertexX] + "_Material_Other";
      sb.MnvH1D_Vertex_X_Other[0]= GetMnvH1D(TFile_MC, var);


      var = sb.HistName_Map[kh_Name_MC_fitTo_vertexY]  + "_Material_Helium";
      sb.MnvH1D_Vertex_Y_Helium[0] = GetMnvH1D(TFile_MC, var);
      var = sb.HistName_Map[kh_Name_MC_fitTo_vertexY]  + "_Material_Aluminium";
      sb.MnvH1D_Vertex_Y_Aluminium[0]= GetMnvH1D(TFile_MC, var);
      var = sb.HistName_Map[kh_Name_MC_fitTo_vertexY]  + "_Material_Carbon";
      sb.MnvH1D_Vertex_Y_Carbon[0]= GetMnvH1D(TFile_MC, var);
      var = sb.HistName_Map[kh_Name_MC_fitTo_vertexY]  + "_Material_Iron";
      sb.MnvH1D_Vertex_Y_Iron[0]= GetMnvH1D(TFile_MC, var);
      var = sb.HistName_Map[kh_Name_MC_fitTo_vertexY]  + "_Material_Lead";
      sb.MnvH1D_Vertex_Y_Lead[0]= GetMnvH1D(TFile_MC, var);
      var = sb.HistName_Map[kh_Name_MC_fitTo_vertexY]  + "_Material_Other";
      sb.MnvH1D_Vertex_Y_Other[0]= GetMnvH1D(TFile_MC, var);

      var = sb.HistName_Map[kh_Name_MC_fitTo_vertexZ] + "_Material_Helium";
      sb.MnvH1D_Vertex_Z_Helium[0] = GetMnvH1D(TFile_MC, var);
      var = sb.HistName_Map[kh_Name_MC_fitTo_vertexZ] + "_Material_Aluminium";
      sb.MnvH1D_Vertex_Z_Aluminium[0]= GetMnvH1D(TFile_MC, var);
      var = sb.HistName_Map[kh_Name_MC_fitTo_vertexZ] + "_Material_Carbon";
      sb.MnvH1D_Vertex_Z_Carbon[0]= GetMnvH1D(TFile_MC, var);
      var = sb.HistName_Map[kh_Name_MC_fitTo_vertexZ] + "_Material_Iron";
      sb.MnvH1D_Vertex_Z_Iron[0]= GetMnvH1D(TFile_MC, var);
      var = sb.HistName_Map[kh_Name_MC_fitTo_vertexZ] + "_Material_Lead";
      sb.MnvH1D_Vertex_Z_Lead[0]= GetMnvH1D(TFile_MC, var);
      var = sb.HistName_Map[kh_Name_MC_fitTo_vertexZ] + "_Material_Other";
      sb.MnvH1D_Vertex_Z_Other[0]= GetMnvH1D(TFile_MC, var);

      var = sb.HistName_Map[kh_Name_MC_fitTo_vertexR] + "_Material_Helium";
      sb.MnvH1D_Vertex_R_Helium[0] = GetMnvH1D(TFile_MC, var);
      var = sb.HistName_Map[kh_Name_MC_fitTo_vertexR] + "_Material_Aluminium";
      sb.MnvH1D_Vertex_R_Aluminium[0]= GetMnvH1D(TFile_MC, var);
      var = sb.HistName_Map[kh_Name_MC_fitTo_vertexR] + "_Material_Carbon";
      sb.MnvH1D_Vertex_R_Carbon[0]= GetMnvH1D(TFile_MC, var);
      var = sb.HistName_Map[kh_Name_MC_fitTo_vertexR] + "_Material_Iron";
      sb.MnvH1D_Vertex_R_Iron[0]= GetMnvH1D(TFile_MC, var);
      var = sb.HistName_Map[kh_Name_MC_fitTo_vertexR] + "_Material_Lead";
      sb.MnvH1D_Vertex_R_Lead[0]= GetMnvH1D(TFile_MC, var);
      var = sb.HistName_Map[kh_Name_MC_fitTo_vertexR] + "_Material_Other";
      sb.MnvH1D_Vertex_R_Other[0]= GetMnvH1D(TFile_MC, var);

}

void Helium_3CryoRegionsSideBandTool::init_MCShifted_SideBand_FitHistograms(Helium3SideBand& sb, TFile* TFile_MC, int i , int j, int k )
{
  std::string string_i = std::to_string(i);
  std::string string_j = std::to_string(j);
  std::string string_k = std::to_string(k);
  std::string var;

//std::cout<<"inside::init_MCShifted_SideBand_FitHistograms"<<std::endl;
    /////////////////////////////////

    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexX] + "_i_j_k_" + string_i + "_" +  string_j + "_" + string_k;
    sb.MnvH1D_Vertex_X_mc_total = GetMnvH1D(TFile_MC, var);

    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexY] + "_i_j_k_" + string_i + "_" +  string_j + "_" + string_k;
    sb.MnvH1D_Vertex_Y_mc_total = GetMnvH1D(TFile_MC, var);

    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexZ] + "_i_j_k_" + string_i + "_" +  string_j + "_" + string_k;
    sb.MnvH1D_Vertex_Z_mc_total = GetMnvH1D(TFile_MC, var);

    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexR] + "_i_j_k_" + string_i + "_" +  string_j + "_" + string_k;
    sb.MnvH1D_Vertex_R_mc_total = GetMnvH1D(TFile_MC, var);

    /////////////////////////////////////

    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexX] + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Helium";
    sb.MnvH1D_Vertex_X_Helium[0] = GetMnvH1D(TFile_MC, var);
    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexX] + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Aluminium";
    sb.MnvH1D_Vertex_X_Aluminium[0]= GetMnvH1D(TFile_MC, var);
    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexX] + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Carbon";
    sb.MnvH1D_Vertex_X_Carbon[0]= GetMnvH1D(TFile_MC, var);
    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexX] + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Iron";
    sb.MnvH1D_Vertex_X_Iron[0]= GetMnvH1D(TFile_MC, var);
    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexX] + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Lead";
    sb.MnvH1D_Vertex_X_Lead[0]= GetMnvH1D(TFile_MC, var);
    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexX] + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Other";
    sb.MnvH1D_Vertex_X_Other[0]= GetMnvH1D(TFile_MC, var);


    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexY]  + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Helium";
    sb.MnvH1D_Vertex_Y_Helium[0] = GetMnvH1D(TFile_MC, var);
    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexY]  + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Aluminium";
    sb.MnvH1D_Vertex_Y_Aluminium[0]= GetMnvH1D(TFile_MC, var);
    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexY]  + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Carbon";
    sb.MnvH1D_Vertex_Y_Carbon[0]= GetMnvH1D(TFile_MC, var);
    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexY]  + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Iron";
    sb.MnvH1D_Vertex_Y_Iron[0]= GetMnvH1D(TFile_MC, var);
    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexY]  + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Lead";
    sb.MnvH1D_Vertex_Y_Lead[0]= GetMnvH1D(TFile_MC, var);
    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexY]  + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Other";
    sb.MnvH1D_Vertex_Y_Other[0]= GetMnvH1D(TFile_MC, var);

    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexZ] + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Helium";
    sb.MnvH1D_Vertex_Z_Helium[0] = GetMnvH1D(TFile_MC, var);
    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexZ] + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Aluminium";
    sb.MnvH1D_Vertex_Z_Aluminium[0]= GetMnvH1D(TFile_MC, var);
    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexZ] + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Carbon";
    sb.MnvH1D_Vertex_Z_Carbon[0]= GetMnvH1D(TFile_MC, var);
    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexZ] + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Iron";
    sb.MnvH1D_Vertex_Z_Iron[0]= GetMnvH1D(TFile_MC, var);
    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexZ] + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Lead";
    sb.MnvH1D_Vertex_Z_Lead[0]= GetMnvH1D(TFile_MC, var);
    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexZ] + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Other";
    sb.MnvH1D_Vertex_Z_Other[0]= GetMnvH1D(TFile_MC, var);

    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexR] + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Helium";
    sb.MnvH1D_Vertex_R_Helium[0] = GetMnvH1D(TFile_MC, var);
    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexR] + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Aluminium";
    sb.MnvH1D_Vertex_R_Aluminium[0]= GetMnvH1D(TFile_MC, var);
    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexR] + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Carbon";
    sb.MnvH1D_Vertex_R_Carbon[0]= GetMnvH1D(TFile_MC, var);
    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexR] + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Iron";
    sb.MnvH1D_Vertex_R_Iron[0]= GetMnvH1D(TFile_MC, var);
    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexR] + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Lead";
    sb.MnvH1D_Vertex_R_Lead[0]= GetMnvH1D(TFile_MC, var);
    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexR] + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Other";
    sb.MnvH1D_Vertex_R_Other[0]= GetMnvH1D(TFile_MC, var);

}
//=============================================================================
void Helium_3CryoRegionsSideBandTool::init_MCShifted_PlaylistCombined_SideBand_FitHistograms(Helium3SideBand& sb, ME_playlist_TFileMAP TFile_Map_MC, int i , int j, int k, ME_helium_Playlists StartingPlaylist )
{
  std::string string_i = std::to_string(i);
  std::string string_j = std::to_string(j);
  std::string string_k = std::to_string(k);
  std::string var;

    //std::cout<<"inside::init_MCShifted_SideBand_FitHistograms"<<std::endl;
    /////////////////////////////////

    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexX] + "_i_j_k_" + string_i + "_" +  string_j + "_" + string_k;
    Playlist_MnvH1D_Map  vertex_X_total_Map =    Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
    sb.MnvH1D_Vertex_X_mc_total =  Combine_Hists_fromMAP(vertex_X_total_Map , StartingPlaylist ,"MnvH1D_Vertex_X_mc_total");

    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexY] + "_i_j_k_" + string_i + "_" +  string_j + "_" + string_k;
    Playlist_MnvH1D_Map  vertex_Y_total_Map = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
    sb.MnvH1D_Vertex_Y_mc_total =  Combine_Hists_fromMAP(vertex_Y_total_Map , StartingPlaylist ,"MnvH1D_Vertex_Y_mc_total");


    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexZ] + "_i_j_k_" + string_i + "_" +  string_j + "_" + string_k;
    Playlist_MnvH1D_Map  vertex_Z_total_Map =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
    sb.MnvH1D_Vertex_Z_mc_total =  Combine_Hists_fromMAP(vertex_Z_total_Map , StartingPlaylist ,"MnvH1D_Vertex_Z_mc_total");


    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexR] + "_i_j_k_" + string_i + "_" +  string_j + "_" + string_k;
    Playlist_MnvH1D_Map  vertex_R_total_Map = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
    sb.MnvH1D_Vertex_R_mc_total =  Combine_Hists_fromMAP(vertex_R_total_Map , StartingPlaylist ,"MnvH1D_Vertex_R_mc_total");

    /////////////////////////////////////

    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexX] + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Helium";
     Playlist_MnvH1D_Map  vertex_X_helium = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
    sb.MnvH1D_Vertex_X_Helium[0] =  Combine_Hists_fromMAP(vertex_X_helium , StartingPlaylist ,"MnvH1D_Vertex_X_helium");


    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexX] + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Aluminium";
    Playlist_MnvH1D_Map  vertex_X_aluminium = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
    sb.MnvH1D_Vertex_X_Aluminium[0] =  Combine_Hists_fromMAP(vertex_X_aluminium , StartingPlaylist ,"MnvH1D_Vertex_X_aluminium");


    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexX] + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Carbon";
    Playlist_MnvH1D_Map  vertex_X_carbon = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
    sb.MnvH1D_Vertex_X_Carbon[0] =  Combine_Hists_fromMAP(vertex_X_carbon , StartingPlaylist ,"MnvH1D_Vertex_X_carbon");


    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexX] + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Iron";
    Playlist_MnvH1D_Map  vertex_X_iron = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
    sb.MnvH1D_Vertex_X_Iron[0] =  Combine_Hists_fromMAP(vertex_X_iron , StartingPlaylist ,"MnvH1D_Vertex_X_iron");


    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexX] + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Lead";
    Playlist_MnvH1D_Map  vertex_X_lead = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
    sb.MnvH1D_Vertex_X_Lead[0] =  Combine_Hists_fromMAP(vertex_X_lead , StartingPlaylist ,"MnvH1D_Vertex_X_lead");


    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexX] + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Other";
    Playlist_MnvH1D_Map  vertex_X_Other = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
    sb.MnvH1D_Vertex_X_Other[0] =  Combine_Hists_fromMAP(vertex_X_Other , StartingPlaylist ,"MnvH1D_Vertex_X_other");
    ///////////////////////////////////

    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexY]  + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Helium";
    Playlist_MnvH1D_Map  vertex_Y_helium = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
    sb.MnvH1D_Vertex_Y_Helium[0] =  Combine_Hists_fromMAP(vertex_Y_helium , StartingPlaylist ,"MnvH1D_Vertex_Y_helium");

    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexY]  + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Aluminium";
    Playlist_MnvH1D_Map  vertex_Y_aluminium = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
    sb.MnvH1D_Vertex_Y_Aluminium[0] =  Combine_Hists_fromMAP(vertex_Y_aluminium , StartingPlaylist ,"MnvH1D_Vertex_Y_aluminium");

    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexY]  + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Carbon";
    Playlist_MnvH1D_Map  vertex_Y_carbon = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
    sb.MnvH1D_Vertex_Y_Carbon[0] =  Combine_Hists_fromMAP(vertex_Y_carbon , StartingPlaylist ,"MnvH1D_Vertex_Y_carbon");

    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexY]  + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Iron";
    Playlist_MnvH1D_Map  vertex_Y_iron = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
    sb.MnvH1D_Vertex_Y_Iron[0] =  Combine_Hists_fromMAP(vertex_Y_iron , StartingPlaylist ,"MnvH1D_Vertex_Y_iron");

    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexY]  + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Lead";
    Playlist_MnvH1D_Map  vertex_Y_lead = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
    sb.MnvH1D_Vertex_Y_Lead[0] =  Combine_Hists_fromMAP(vertex_Y_lead , StartingPlaylist ,"MnvH1D_Vertex_Y_lead");

    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexY]  + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Other";
    Playlist_MnvH1D_Map  vertex_Y_Other = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
    sb.MnvH1D_Vertex_Y_Other[0] =  Combine_Hists_fromMAP(vertex_Y_Other , StartingPlaylist ,"MnvH1D_Vertex_Y_other");
    /////////////

    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexZ] + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Helium";
    Playlist_MnvH1D_Map  vertex_Z_helium  = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
    sb.MnvH1D_Vertex_Z_Helium[0] =  Combine_Hists_fromMAP(vertex_Z_helium , StartingPlaylist ,"MnvH1D_Vertex_Z_helium");

    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexZ] + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Aluminium";
    Playlist_MnvH1D_Map  vertex_Z_aluminium = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
    sb.MnvH1D_Vertex_Z_Aluminium[0] =  Combine_Hists_fromMAP(vertex_Z_aluminium , StartingPlaylist ,"MnvH1D_Vertex_Z_aluminium");

    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexZ] + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Carbon";
    Playlist_MnvH1D_Map  vertex_Z_carbon = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
    sb.MnvH1D_Vertex_Z_Carbon[0] =  Combine_Hists_fromMAP(vertex_Z_carbon , StartingPlaylist ,"MnvH1D_Vertex_Z_carbon");

    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexZ] + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Iron";
    Playlist_MnvH1D_Map  vertex_Z_iron = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
    sb.MnvH1D_Vertex_Z_Iron[0] =  Combine_Hists_fromMAP(vertex_Z_iron , StartingPlaylist ,"MnvH1D_Vertex_Z_iron");

    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexZ] + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Lead";
    Playlist_MnvH1D_Map  vertex_Z_lead = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
    sb.MnvH1D_Vertex_Z_Lead[0] =  Combine_Hists_fromMAP(vertex_Z_lead , StartingPlaylist ,"MnvH1D_Vertex_Z_lead");

    var = sb.HistName_Map[kh_Name_MC_fitTo_vertexZ] + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Other";
    Playlist_MnvH1D_Map  vertex_Z_Other = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
    sb.MnvH1D_Vertex_Z_Other[0] =  Combine_Hists_fromMAP(vertex_Z_Other , StartingPlaylist ,"MnvH1D_Vertex_Z_other");
  ///////////////////

  var = sb.HistName_Map[kh_Name_MC_fitTo_vertexR] + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Helium";
  Playlist_MnvH1D_Map  vertex_R_helium  = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  sb.MnvH1D_Vertex_R_Helium[0] =  Combine_Hists_fromMAP(vertex_R_helium , StartingPlaylist ,"MnvH1D_Vertex_R_helium");

  var = sb.HistName_Map[kh_Name_MC_fitTo_vertexR] + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Aluminium";
  Playlist_MnvH1D_Map  vertex_R_aluminium = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  sb.MnvH1D_Vertex_R_Aluminium[0] =  Combine_Hists_fromMAP(vertex_R_aluminium , StartingPlaylist ,"MnvH1D_Vertex_R_aluminium");

  var = sb.HistName_Map[kh_Name_MC_fitTo_vertexR] + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Carbon";
  Playlist_MnvH1D_Map  vertex_R_carbon = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  sb.MnvH1D_Vertex_R_Carbon[0] =  Combine_Hists_fromMAP(vertex_R_carbon , StartingPlaylist ,"MnvH1D_Vertex_R_carbon");

  var = sb.HistName_Map[kh_Name_MC_fitTo_vertexR] + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Iron";
  Playlist_MnvH1D_Map  vertex_R_iron = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  sb.MnvH1D_Vertex_R_Iron[0] =  Combine_Hists_fromMAP(vertex_R_iron , StartingPlaylist ,"MnvH1D_Vertex_R_iron");

  var = sb.HistName_Map[kh_Name_MC_fitTo_vertexR] + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Lead";
  Playlist_MnvH1D_Map  vertex_R_lead = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  sb.MnvH1D_Vertex_R_Lead[0] =  Combine_Hists_fromMAP(vertex_R_lead , StartingPlaylist ,"MnvH1D_Vertex_R_lead");

  var = sb.HistName_Map[kh_Name_MC_fitTo_vertexR] + "_Material_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Other";
  Playlist_MnvH1D_Map  vertex_R_Other = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  sb.MnvH1D_Vertex_R_Other[0] =  Combine_Hists_fromMAP(vertex_R_Other , StartingPlaylist ,"MnvH1D_Vertex_R_other");

}
//=============================================================================
void Helium_3CryoRegionsSideBandTool::init_MC_Resolution_PlaylistCombined_Histograms(XSec_Var3band& xsec_var, std::string regionstring,  ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist )
{
  std::string var;

    var = xsec_var.name + regionstring + "_Material_Helium";
    Playlist_MnvH1D_Map MC_map_Helium =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
    xsec_var.MnvH1D_Helium[0] = Combine_Hists_fromMAP(MC_map_Helium, StartingPlaylist ,"MnvH1D_MC_vertex_X_Resolution_Helium");

    var = xsec_var.name + regionstring +  "_Material_Aluminium";
    Playlist_MnvH1D_Map MC_map_Aluminium =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
    xsec_var.MnvH1D_Aluminium[0] = Combine_Hists_fromMAP(MC_map_Aluminium , StartingPlaylist ,"MnvH1D_MC_vertex_X_Resolution_Aluminium");

    var = xsec_var.name + regionstring +  "_Material_Carbon";
    Playlist_MnvH1D_Map MC_map_Carbon =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
    xsec_var.MnvH1D_Carbon[0] = Combine_Hists_fromMAP(MC_map_Carbon , StartingPlaylist ,"MnvH1D_MC_vertex_X_Resolution_Carbon");

    var = xsec_var.name + regionstring +  "_Material_Iron";
    Playlist_MnvH1D_Map MC_map_Iron =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
    xsec_var.MnvH1D_Iron[0] = Combine_Hists_fromMAP(MC_map_Iron , StartingPlaylist ,"MnvH1D_MC_vertex_X_Resolution_Iron");

    var = xsec_var.name + regionstring +  "_Material_Lead";
    Playlist_MnvH1D_Map MC_map_Lead =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
    xsec_var.MnvH1D_Lead[0] = Combine_Hists_fromMAP(MC_map_Lead , StartingPlaylist ,"MnvH1D_MC_vertex_X_Resolution_Lead");

    var = xsec_var.name + regionstring +  "_Material_Other";
    Playlist_MnvH1D_Map MC_map_Other =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
    xsec_var.MnvH1D_Other[0] = Combine_Hists_fromMAP(MC_map_Other , StartingPlaylist ,"MnvH1D_MC_vertex_X_Resolution_Other");

    xsec_var.MnvH1D_mc_total = (MnvH1D*) xsec_var.MnvH1D_Helium[0]->Clone();
    xsec_var.MnvH1D_mc_total->Add(xsec_var.MnvH1D_Aluminium[0]);
    xsec_var.MnvH1D_mc_total->Add(xsec_var.MnvH1D_Carbon[0]);
    xsec_var.MnvH1D_mc_total->Add(xsec_var.MnvH1D_Iron[0]);
    xsec_var.MnvH1D_mc_total->Add(xsec_var.MnvH1D_Lead[0]);
    xsec_var.MnvH1D_mc_total->Add(xsec_var.MnvH1D_Other[0]);

}
//=============================================================================
void Helium_3CryoRegionsSideBandTool::init_MC_ResolutionVars_PlaylistCombined_Histograms(Resolution_hists& Resolution_var, std::string regionstring,
   ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist )
{
  std::string var;
  var = Resolution_var.name + regionstring + "resolution_RECO";
  Playlist_MnvH1D_Map MC_map_Reco =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  Resolution_var.MnvH1D_Resolution_RECO = Combine_Hists_fromMAP(MC_map_Reco, StartingPlaylist ,"MnvH1D_MC_Resolution_RECO");

  var = Resolution_var.name + regionstring + "resolution_TRUE_RECO";
  Playlist_MnvH1D_Map MC_map_TRUE_Reco =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  Resolution_var.MnvH1D_Resolution_TRUE_RECO = Combine_Hists_fromMAP(MC_map_TRUE_Reco, StartingPlaylist ,"MnvH1D_MC_Resolution_TRUE_RECO");

  var = Resolution_var.name + regionstring + "percentresolution_RECO";
  Playlist_MnvH1D_Map MC_map_percentage_Reco =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  Resolution_var.MnvH1D_percentageResolution_RECO = Combine_Hists_fromMAP(MC_map_percentage_Reco, StartingPlaylist ,"MnvH1D_MC_Resolution_Percentage_RECO");

  var = Resolution_var.name + regionstring + "percentresolution_TRUE_RECO";
  Playlist_MnvH1D_Map MC_map_percentage_TRUE_Reco =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  Resolution_var.MnvH1D_percentageResolution_TRUE_RECO = Combine_Hists_fromMAP(MC_map_percentage_TRUE_Reco, StartingPlaylist ,"MnvH1D_MC_Resolution_Percentage_TRUE_RECO");
}
//=============================================================================
void Helium_3CryoRegionsSideBandTool::init_MC_Mig_Histograms(Helium3SideBand& sb, std::string regionstring,
   ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist )
{
  std::string var;
  var = "h_Mig_Vertex_X" + regionstring;
  Playlist_MnvH2D_Map Mig_vertex_X =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  sb.MnvH2D_Mig_vertex_X = Combine_2DHists_fromMAP(Mig_vertex_X, StartingPlaylist ,"MnvH2D_Mig_vertex_X");

  var = "h_Mig_Vertex_Y" + regionstring;
  Playlist_MnvH2D_Map Mig_vertex_Y =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  sb.MnvH2D_Mig_vertex_Y = Combine_2DHists_fromMAP(Mig_vertex_Y, StartingPlaylist ,"MnvH2D_Mig_vertex_Y");

  var = "h_Mig_Vertex_R" + regionstring;
  Playlist_MnvH2D_Map Mig_vertex_R =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  sb.MnvH2D_Mig_vertex_R = Combine_2DHists_fromMAP(Mig_vertex_R, StartingPlaylist ,"MnvH2D_Mig_vertex_R");

  var = "h_Mig_Vertex_Z" + regionstring;
  Playlist_MnvH2D_Map Mig_vertex_Z =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  sb.MnvH2D_Mig_vertex_Z = Combine_2DHists_fromMAP(Mig_vertex_Z, StartingPlaylist ,"MnvH2D_Mig_vertex_Z");
}
//=============================================================================
void Helium_3CryoRegionsSideBandTool::init_Region_N_MaterialHists(HeliumNSideBand &input_HeliumNSideBand,
   ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist){
std::string Var_hist_name;

  Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_vertexX] + "_Helium";
  Playlist_MnvH1D_Map MC_Vertex_X_map_Helium =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
  input_HeliumNSideBand.MnvH1D_Vertex_X_Helium[0] = Combine_Hists_fromMAP(MC_Vertex_X_map_Helium, StartingPlaylist ,"MnvH1D_MC_vertex_X_RegionN_Helium");

  Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_vertexX] + "_Aluminium";
  Playlist_MnvH1D_Map MC_Vertex_X_map_Aluminium =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
  input_HeliumNSideBand.MnvH1D_Vertex_X_Aluminium[0] = Combine_Hists_fromMAP(MC_Vertex_X_map_Aluminium, StartingPlaylist ,"MnvH1D_MC_vertex_X_RegionN_Aluminum");

  Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_vertexX] + "_Carbon";
  Playlist_MnvH1D_Map MC_Vertex_X_map_Carbon =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
  input_HeliumNSideBand.MnvH1D_Vertex_X_Carbon[0] = Combine_Hists_fromMAP(MC_Vertex_X_map_Carbon, StartingPlaylist ,"MnvH1D_MC_vertex_X_RegionN_Carbon");

  Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_vertexX] + "_Iron";
  Playlist_MnvH1D_Map MC_Vertex_X_map_Iron =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
  input_HeliumNSideBand.MnvH1D_Vertex_X_Iron[0] = Combine_Hists_fromMAP(MC_Vertex_X_map_Iron, StartingPlaylist ,"MnvH1D_MC_vertex_X_RegionN_Iron");

  Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_vertexX] + "_Lead";
  Playlist_MnvH1D_Map MC_Vertex_X_map_Lead =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
  input_HeliumNSideBand.MnvH1D_Vertex_X_Lead[0] = Combine_Hists_fromMAP(MC_Vertex_X_map_Lead, StartingPlaylist ,"MnvH1D_MC_vertex_X_RegionN_Lead");

  Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_vertexX] + "_Other";
  Playlist_MnvH1D_Map MC_Vertex_X_map_Other =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
  input_HeliumNSideBand.MnvH1D_Vertex_X_Other[0] = Combine_Hists_fromMAP(MC_Vertex_X_map_Other, StartingPlaylist ,"MnvH1D_MC_vertex_X_RegionN_Other");
  ///////////////////////////////////////////////////////////////////////////////

  Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_vertexY] + "_Helium";
  Playlist_MnvH1D_Map MC_Vertex_Y_map_Helium =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
  input_HeliumNSideBand.MnvH1D_Vertex_Y_Helium[0] = Combine_Hists_fromMAP(MC_Vertex_Y_map_Helium, StartingPlaylist ,"MnvH1D_MC_vertex_Y_RegionN_Helium");

  Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_vertexY] + "_Aluminium";
  Playlist_MnvH1D_Map MC_Vertex_Y_map_Aluminium =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
  input_HeliumNSideBand.MnvH1D_Vertex_Y_Aluminium[0] = Combine_Hists_fromMAP(MC_Vertex_Y_map_Aluminium, StartingPlaylist ,"MnvH1D_MC_vertex_Y_RegionN_Aluminum");

  Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_vertexY] + "_Carbon";
  Playlist_MnvH1D_Map MC_Vertex_Y_map_Carbon =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
  input_HeliumNSideBand.MnvH1D_Vertex_Y_Carbon[0] = Combine_Hists_fromMAP(MC_Vertex_Y_map_Carbon, StartingPlaylist ,"MnvH1D_MC_vertex_Y_RegionN_Carbon");

  Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_vertexY] + "_Iron";
  Playlist_MnvH1D_Map MC_Vertex_Y_map_Iron =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
  input_HeliumNSideBand.MnvH1D_Vertex_Y_Iron[0] = Combine_Hists_fromMAP(MC_Vertex_Y_map_Iron, StartingPlaylist ,"MnvH1D_MC_vertex_Y_RegionN_Iron");

  Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_vertexY] + "_Lead";
  Playlist_MnvH1D_Map MC_Vertex_Y_map_Lead =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
  input_HeliumNSideBand.MnvH1D_Vertex_Y_Lead[0] = Combine_Hists_fromMAP(MC_Vertex_Y_map_Lead, StartingPlaylist ,"MnvH1D_MC_vertex_Y_RegionN_Lead");

  Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_vertexY] + "_Other";
  Playlist_MnvH1D_Map MC_Vertex_Y_map_Other =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
  input_HeliumNSideBand.MnvH1D_Vertex_Y_Other[0] = Combine_Hists_fromMAP(MC_Vertex_Y_map_Other, StartingPlaylist ,"MnvH1D_MC_vertex_Y_RegionN_Other");
  ////////////////////////////////////////////////////////////////
    Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_vertexZ] + "_Helium";
    Playlist_MnvH1D_Map MC_Vertex_Z_map_Helium =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
    input_HeliumNSideBand.MnvH1D_Vertex_Z_Helium[0] = Combine_Hists_fromMAP(MC_Vertex_Z_map_Helium, StartingPlaylist ,"MnvH1D_MC_vertex_Z_RegionN_Helium");

    Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_vertexZ] + "_Aluminium";
    Playlist_MnvH1D_Map MC_Vertex_Z_map_Aluminium =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
    input_HeliumNSideBand.MnvH1D_Vertex_Z_Aluminium[0] = Combine_Hists_fromMAP(MC_Vertex_Z_map_Aluminium, StartingPlaylist ,"MnvH1D_MC_vertex_Z_RegionN_Aluminum");

    Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_vertexZ] + "_Carbon";
    Playlist_MnvH1D_Map MC_Vertex_Z_map_Carbon =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
    input_HeliumNSideBand.MnvH1D_Vertex_Z_Carbon[0] = Combine_Hists_fromMAP(MC_Vertex_Z_map_Carbon, StartingPlaylist ,"MnvH1D_MC_vertex_Z_RegionN_Carbon");

    Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_vertexZ] + "_Iron";
    Playlist_MnvH1D_Map MC_Vertex_Z_map_Iron =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
    input_HeliumNSideBand.MnvH1D_Vertex_Z_Iron[0] = Combine_Hists_fromMAP(MC_Vertex_Z_map_Iron, StartingPlaylist ,"MnvH1D_MC_vertex_Z_RegionN_Iron");

    Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_vertexZ] + "_Lead";
    Playlist_MnvH1D_Map MC_Vertex_Z_map_Lead =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
    input_HeliumNSideBand.MnvH1D_Vertex_Z_Lead[0] = Combine_Hists_fromMAP(MC_Vertex_Z_map_Lead, StartingPlaylist ,"MnvH1D_MC_vertex_Z_RegionN_Lead");

    Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_vertexZ] + "_Other";
    Playlist_MnvH1D_Map MC_Vertex_Z_map_Other =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
    input_HeliumNSideBand.MnvH1D_Vertex_Z_Other[0] = Combine_Hists_fromMAP(MC_Vertex_Z_map_Other, StartingPlaylist ,"MnvH1D_MC_vertex_Z_RegionN_Other");

    ////////////////////////////////////////////////////////////////
      Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_vertexR] + "_Helium";
      Playlist_MnvH1D_Map MC_Vertex_R_map_Helium =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
      input_HeliumNSideBand.MnvH1D_Vertex_R_Helium[0] = Combine_Hists_fromMAP(MC_Vertex_R_map_Helium, StartingPlaylist ,"MnvH1D_MC_vertex_R_RegionN_Helium");

      Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_vertexR] + "_Aluminium";
      Playlist_MnvH1D_Map MC_Vertex_R_map_Aluminium =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
      input_HeliumNSideBand.MnvH1D_Vertex_R_Aluminium[0] = Combine_Hists_fromMAP(MC_Vertex_R_map_Aluminium, StartingPlaylist ,"MnvH1D_MC_vertex_R_RegionN_Aluminum");

      Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_vertexR] + "_Carbon";
      Playlist_MnvH1D_Map MC_Vertex_R_map_Carbon =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
      input_HeliumNSideBand.MnvH1D_Vertex_R_Carbon[0] = Combine_Hists_fromMAP(MC_Vertex_R_map_Carbon, StartingPlaylist ,"MnvH1D_MC_vertex_R_RegionN_Carbon");

      Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_vertexR] + "_Iron";
      Playlist_MnvH1D_Map MC_Vertex_R_map_Iron =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
      input_HeliumNSideBand.MnvH1D_Vertex_R_Iron[0] = Combine_Hists_fromMAP(MC_Vertex_R_map_Iron, StartingPlaylist ,"MnvH1D_MC_vertex_R_RegionN_Iron");

      Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_vertexR] + "_Lead";
      Playlist_MnvH1D_Map MC_Vertex_R_map_Lead =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
      input_HeliumNSideBand.MnvH1D_Vertex_R_Lead[0] = Combine_Hists_fromMAP(MC_Vertex_R_map_Lead, StartingPlaylist ,"MnvH1D_MC_vertex_R_RegionN_Lead");

      Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_vertexR] + "_Other";
      Playlist_MnvH1D_Map MC_Vertex_R_map_Other =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
      input_HeliumNSideBand.MnvH1D_Vertex_R_Other[0] = Combine_Hists_fromMAP(MC_Vertex_R_map_Other, StartingPlaylist ,"MnvH1D_MC_vertex_Z_RegionN_Other");

      initNSideBandFromTFileMap_XSecHistograms_MC(TFile_Map_MC,  input_HeliumNSideBand,  input_HeliumNSideBand.muon_PT,        StartingPlaylist );
      initNSideBandFromTFileMap_XSecHistograms_MC(TFile_Map_MC,  input_HeliumNSideBand,  input_HeliumNSideBand.muon_PZ,        StartingPlaylist );
      initNSideBandFromTFileMap_XSecHistograms_MC( TFile_Map_MC, input_HeliumNSideBand,  input_HeliumNSideBand.muon_theta,     StartingPlaylist );
      initNSideBandFromTFileMap_XSecHistograms_MC(TFile_Map_MC,  input_HeliumNSideBand,  input_HeliumNSideBand.muon_E,         StartingPlaylist );
      initNSideBandFromTFileMap_XSecHistograms_MC(TFile_Map_MC,  input_HeliumNSideBand,  input_HeliumNSideBand.muon_doca,      StartingPlaylist );
      initNSideBandFromTFileMap_XSecHistograms_MC(TFile_Map_MC,  input_HeliumNSideBand,  input_HeliumNSideBand.DistancetoEdge, StartingPlaylist );
      initNSideBandFromTFileMap_XSecHistograms_MC( TFile_Map_MC, input_HeliumNSideBand,  input_HeliumNSideBand.SecTrk_doca,    StartingPlaylist );
      initNSideBandFromTFileMap_XSecHistograms_MC(TFile_Map_MC,  input_HeliumNSideBand,  input_HeliumNSideBand.TrackLength,    StartingPlaylist );



    }
//=============================================================================
void Helium_3CryoRegionsSideBandTool::init_Region_N_MaterialHists_TRUEMeasure(HeliumNSideBand &input_HeliumNSideBand,
   ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist){
std::string Var_hist_name;

  Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_TRUE_vertexX] + "_Helium";
  Playlist_MnvH1D_Map MC_Vertex_X_map_Helium =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
  input_HeliumNSideBand.MnvH1D_Vertex_X_Helium[1] = Combine_Hists_fromMAP(MC_Vertex_X_map_Helium, StartingPlaylist ,"MnvH1D_MC_vertex_X_RegionN_Helium");

  Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_TRUE_vertexX] + "_Aluminium";
  Playlist_MnvH1D_Map MC_Vertex_X_map_Aluminium =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
  input_HeliumNSideBand.MnvH1D_Vertex_X_Aluminium[1] = Combine_Hists_fromMAP(MC_Vertex_X_map_Aluminium, StartingPlaylist ,"MnvH1D_MC_vertex_X_RegionN_Aluminum");

  Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_TRUE_vertexX] + "_Carbon";
  Playlist_MnvH1D_Map MC_Vertex_X_map_Carbon =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
  input_HeliumNSideBand.MnvH1D_Vertex_X_Carbon[1] = Combine_Hists_fromMAP(MC_Vertex_X_map_Carbon, StartingPlaylist ,"MnvH1D_MC_vertex_X_RegionN_Carbon");

  Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_TRUE_vertexX] + "_Iron";
  Playlist_MnvH1D_Map MC_Vertex_X_map_Iron =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
  input_HeliumNSideBand.MnvH1D_Vertex_X_Iron[1] = Combine_Hists_fromMAP(MC_Vertex_X_map_Iron, StartingPlaylist ,"MnvH1D_MC_vertex_X_RegionN_Iron");

  Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_TRUE_vertexX] + "_Lead";
  Playlist_MnvH1D_Map MC_Vertex_X_map_Lead =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
  input_HeliumNSideBand.MnvH1D_Vertex_X_Lead[1] = Combine_Hists_fromMAP(MC_Vertex_X_map_Lead, StartingPlaylist ,"MnvH1D_MC_vertex_X_RegionN_Lead");

  Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_TRUE_vertexX] + "_Other";
  Playlist_MnvH1D_Map MC_Vertex_X_map_Other =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
  input_HeliumNSideBand.MnvH1D_Vertex_X_Other[1] = Combine_Hists_fromMAP(MC_Vertex_X_map_Other, StartingPlaylist ,"MnvH1D_MC_vertex_X_RegionN_Other");
  ///////////////////////////////////////////////////////////////////////////////

  Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_TRUE_vertexY] + "_Helium";
  Playlist_MnvH1D_Map MC_Vertex_Y_map_Helium =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
  input_HeliumNSideBand.MnvH1D_Vertex_Y_Helium[1] = Combine_Hists_fromMAP(MC_Vertex_Y_map_Helium, StartingPlaylist ,"MnvH1D_MC_vertex_Y_RegionN_Helium");

  Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_TRUE_vertexY] + "_Aluminium";
  Playlist_MnvH1D_Map MC_Vertex_Y_map_Aluminium =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
  input_HeliumNSideBand.MnvH1D_Vertex_Y_Aluminium[1] = Combine_Hists_fromMAP(MC_Vertex_Y_map_Aluminium, StartingPlaylist ,"MnvH1D_MC_vertex_Y_RegionN_Aluminum");

  Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_TRUE_vertexY] + "_Carbon";
  Playlist_MnvH1D_Map MC_Vertex_Y_map_Carbon =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
  input_HeliumNSideBand.MnvH1D_Vertex_Y_Carbon[1] = Combine_Hists_fromMAP(MC_Vertex_Y_map_Carbon, StartingPlaylist ,"MnvH1D_MC_vertex_Y_RegionN_Carbon");

  Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_TRUE_vertexY] + "_Iron";
  Playlist_MnvH1D_Map MC_Vertex_Y_map_Iron =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
  input_HeliumNSideBand.MnvH1D_Vertex_Y_Iron[1] = Combine_Hists_fromMAP(MC_Vertex_Y_map_Iron, StartingPlaylist ,"MnvH1D_MC_vertex_Y_RegionN_Iron");

  Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_TRUE_vertexY] + "_Lead";
  Playlist_MnvH1D_Map MC_Vertex_Y_map_Lead =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
  input_HeliumNSideBand.MnvH1D_Vertex_Y_Lead[1] = Combine_Hists_fromMAP(MC_Vertex_Y_map_Lead, StartingPlaylist ,"MnvH1D_MC_vertex_Y_RegionN_Lead");

  Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_TRUE_vertexY] + "_Other";
  Playlist_MnvH1D_Map MC_Vertex_Y_map_Other =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
  input_HeliumNSideBand.MnvH1D_Vertex_Y_Other[1] = Combine_Hists_fromMAP(MC_Vertex_Y_map_Other, StartingPlaylist ,"MnvH1D_MC_vertex_Y_RegionN_Other");
  ////////////////////////////////////////////////////////////////
    Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_TRUE_vertexZ] + "_Helium";
    Playlist_MnvH1D_Map MC_Vertex_Z_map_Helium =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
    input_HeliumNSideBand.MnvH1D_Vertex_Z_Helium[1] = Combine_Hists_fromMAP(MC_Vertex_Z_map_Helium, StartingPlaylist ,"MnvH1D_MC_vertex_Z_RegionN_Helium");

    Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_TRUE_vertexZ] + "_Aluminium";
    Playlist_MnvH1D_Map MC_Vertex_Z_map_Aluminium =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
    input_HeliumNSideBand.MnvH1D_Vertex_Z_Aluminium[1] = Combine_Hists_fromMAP(MC_Vertex_Z_map_Aluminium, StartingPlaylist ,"MnvH1D_MC_vertex_Z_RegionN_Aluminum");

    Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_TRUE_vertexZ] + "_Carbon";
    Playlist_MnvH1D_Map MC_Vertex_Z_map_Carbon =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
    input_HeliumNSideBand.MnvH1D_Vertex_Z_Carbon[1] = Combine_Hists_fromMAP(MC_Vertex_Z_map_Carbon, StartingPlaylist ,"MnvH1D_MC_vertex_Z_RegionN_Carbon");

    Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_TRUE_vertexZ] + "_Iron";
    Playlist_MnvH1D_Map MC_Vertex_Z_map_Iron =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
    input_HeliumNSideBand.MnvH1D_Vertex_Z_Iron[1] = Combine_Hists_fromMAP(MC_Vertex_Z_map_Iron, StartingPlaylist ,"MnvH1D_MC_vertex_Z_RegionN_Iron");

    Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_TRUE_vertexZ] + "_Lead";
    Playlist_MnvH1D_Map MC_Vertex_Z_map_Lead =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
    input_HeliumNSideBand.MnvH1D_Vertex_Z_Lead[1] = Combine_Hists_fromMAP(MC_Vertex_Z_map_Lead, StartingPlaylist ,"MnvH1D_MC_vertex_Z_RegionN_Lead");

    Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_TRUE_vertexZ] + "_Other";
    Playlist_MnvH1D_Map MC_Vertex_Z_map_Other =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
    input_HeliumNSideBand.MnvH1D_Vertex_Z_Other[1] = Combine_Hists_fromMAP(MC_Vertex_Z_map_Other, StartingPlaylist ,"MnvH1D_MC_vertex_Z_RegionN_Other");

    ////////////////////////////////////////////////////////////////
      Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_TRUE_vertexR] + "_Helium";
      Playlist_MnvH1D_Map MC_Vertex_R_map_Helium =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
      input_HeliumNSideBand.MnvH1D_Vertex_R_Helium[1] = Combine_Hists_fromMAP(MC_Vertex_R_map_Helium, StartingPlaylist ,"MnvH1D_MC_vertex_R_RegionN_Helium");

      Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_TRUE_vertexR] + "_Aluminium";
      Playlist_MnvH1D_Map MC_Vertex_R_map_Aluminium =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
      input_HeliumNSideBand.MnvH1D_Vertex_R_Aluminium[1] = Combine_Hists_fromMAP(MC_Vertex_R_map_Aluminium, StartingPlaylist ,"MnvH1D_MC_vertex_R_RegionN_Aluminum");

      Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_TRUE_vertexR] + "_Carbon";
      Playlist_MnvH1D_Map MC_Vertex_R_map_Carbon =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
      input_HeliumNSideBand.MnvH1D_Vertex_R_Carbon[1] = Combine_Hists_fromMAP(MC_Vertex_R_map_Carbon, StartingPlaylist ,"MnvH1D_MC_vertex_R_RegionN_Carbon");

      Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_TRUE_vertexR] + "_Iron";
      Playlist_MnvH1D_Map MC_Vertex_R_map_Iron =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
      input_HeliumNSideBand.MnvH1D_Vertex_R_Iron[1] = Combine_Hists_fromMAP(MC_Vertex_R_map_Iron, StartingPlaylist ,"MnvH1D_MC_vertex_R_RegionN_Iron");

      Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_TRUE_vertexR] + "_Lead";
      Playlist_MnvH1D_Map MC_Vertex_R_map_Lead =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
      input_HeliumNSideBand.MnvH1D_Vertex_R_Lead[1] = Combine_Hists_fromMAP(MC_Vertex_R_map_Lead, StartingPlaylist ,"MnvH1D_MC_vertex_R_RegionN_Lead");

      Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_MC_fitTo_TRUE_vertexR] + "_Other";
      Playlist_MnvH1D_Map MC_Vertex_R_map_Other =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, Var_hist_name );
      input_HeliumNSideBand.MnvH1D_Vertex_R_Other[1] = Combine_Hists_fromMAP(MC_Vertex_R_map_Other, StartingPlaylist ,"MnvH1D_MC_vertex_Z_RegionN_Other");


    }
//=============================================================================
void Helium_3CryoRegionsSideBandTool::init_Region_Map_MaterialHists(CryoRegion_HeliumNSideBand_Map &input_Map, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist){
std::cout<<"Inside:init_Region_Map_MaterialHists"<<std::endl;
  std::cout<<"Checking if CryoRegion_HeliumNSideBand_Map is Initialied with size = "<< input_Map.size()<<std::endl;
  for(auto Region :CryoRegion14_vector){
    std::cout<< "Region"<< GetRegionString(Region) <<std::endl;
    init_Region_N_MaterialHists(input_Map[Region], TFile_Map_MC, StartingPlaylist);
    init_Region_N_MaterialHists_TRUEMeasure(input_Map[Region], TFile_Map_MC, StartingPlaylist);
    init_Region_N_MaterialHists_Data(input_Map[Region], TFile_Map_Empty_Data, StartingPlaylist);
  }
}
//=============================================================================
void Helium_3CryoRegionsSideBandTool::init_Region_Map_MaterialHists_Empty(){
  std::cout<<"Inside::init_Region_Map_MaterialHists_Empty "<<std::endl;
  init_Region_Map_MaterialHists(CryoRegionMap_Empty, TFile_Map_Empty_MC, Empty_Playlist.at(0));



}

//=============================================================================
void Helium_3CryoRegionsSideBandTool::init_Region_N_MaterialHists_Data(HeliumNSideBand &input_HeliumNSideBand,
   ME_playlist_TFileMAP TFile_Map_Data, ME_helium_Playlists StartingPlaylist){
std::string Var_hist_name;

  Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_Data_fitTo_vertexX];
  Playlist_MnvH1D_Map Data_Vertex_X_map =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_Data, Var_hist_name );
  input_HeliumNSideBand.MnvH1D_Vertex_X_data = Combine_Hists_fromMAP(Data_Vertex_X_map, StartingPlaylist ,"MnvH1D_data_vertex_X");

  Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_Data_fitTo_vertexY];
  Playlist_MnvH1D_Map Data_Vertex_Y_map =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_Data, Var_hist_name );
  input_HeliumNSideBand.MnvH1D_Vertex_Y_data = Combine_Hists_fromMAP(Data_Vertex_Y_map, StartingPlaylist ,"MnvH1D_data_vertex_Y");

  Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_Data_fitTo_vertexZ];
  Playlist_MnvH1D_Map Data_Vertex_Z_map =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_Data, Var_hist_name );
  input_HeliumNSideBand.MnvH1D_Vertex_Z_data = Combine_Hists_fromMAP(Data_Vertex_Z_map, StartingPlaylist ,"MnvH1D_data_vertex_Z");

  Var_hist_name = input_HeliumNSideBand.HistName_Map[kh_Name_Data_fitTo_vertexR];
  Playlist_MnvH1D_Map Data_Vertex_R_map =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_Data, Var_hist_name );
  input_HeliumNSideBand.MnvH1D_Vertex_R_data = Combine_Hists_fromMAP(Data_Vertex_R_map, StartingPlaylist ,"MnvH1D_data_vertex_R");

  initNSideBandFromTFileMap_XSecHistograms_data( TFile_Map_Data , input_HeliumNSideBand, input_HeliumNSideBand.muon_PT, StartingPlaylist  );


  initNSideBandFromTFileMap_XSecHistograms_data( TFile_Map_Data , input_HeliumNSideBand, input_HeliumNSideBand.muon_PZ, StartingPlaylist  );
  initNSideBandFromTFileMap_XSecHistograms_data( TFile_Map_Data , input_HeliumNSideBand, input_HeliumNSideBand.muon_theta, StartingPlaylist  );
  initNSideBandFromTFileMap_XSecHistograms_data( TFile_Map_Data , input_HeliumNSideBand, input_HeliumNSideBand.muon_E, StartingPlaylist  );
  initNSideBandFromTFileMap_XSecHistograms_data( TFile_Map_Data , input_HeliumNSideBand, input_HeliumNSideBand.muon_doca, StartingPlaylist  );
  initNSideBandFromTFileMap_XSecHistograms_data( TFile_Map_Data , input_HeliumNSideBand, input_HeliumNSideBand.DistancetoEdge, StartingPlaylist  );
  initNSideBandFromTFileMap_XSecHistograms_data( TFile_Map_Data , input_HeliumNSideBand, input_HeliumNSideBand.SecTrk_doca, StartingPlaylist  );
  initNSideBandFromTFileMap_XSecHistograms_data( TFile_Map_Data , input_HeliumNSideBand, input_HeliumNSideBand.TrackLength, StartingPlaylist  );



}



//=============
void Helium_3CryoRegionsSideBandTool::init_MC_PlaylistCombined_SideBand_Resolution_Histograms(Helium3SideBand& sb,
  std::string regionstring, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist )
{
  //std::cout<<"INSIDE::Helium_3CryoRegionsSideBandTool::init_MC_PlaylistCombined_SideBand_Resolution_Histograms"<<std::endl;
  init_MC_Resolution_PlaylistCombined_Histograms( sb.Vertex_X_Resolution,  regionstring,  TFile_Map_MC,  StartingPlaylist );
  init_MC_Resolution_PlaylistCombined_Histograms( sb.Vertex_Y_Resolution,  regionstring,  TFile_Map_MC,  StartingPlaylist );
  init_MC_Resolution_PlaylistCombined_Histograms( sb.Vertex_Z_Resolution,  regionstring,  TFile_Map_MC,  StartingPlaylist );
  init_MC_Resolution_PlaylistCombined_Histograms( sb.Vertex_R_Resolution,  regionstring,  TFile_Map_MC,  StartingPlaylist );
}

void Helium_3CryoRegionsSideBandTool::init_MC_PlaylistCombined_SideBand_Resolution_RECOandTRUE_Histograms(Helium3SideBand& sb,
  std::string regionstring, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist )
{
//  std::cout<<"INSIDE::Helium_3CryoRegionsSideBandTool::init_MC_PlaylistCombined_SideBand_Resolution_RECOandTRUE_Histograms"<<std::endl;

  init_MC_ResolutionVars_PlaylistCombined_Histograms(sb.Resolution_hists_Vertex_X,  regionstring,  TFile_Map_MC,  StartingPlaylist );
  init_MC_ResolutionVars_PlaylistCombined_Histograms(sb.Resolution_hists_Vertex_Y,  regionstring,  TFile_Map_MC,  StartingPlaylist );
  init_MC_ResolutionVars_PlaylistCombined_Histograms(sb.Resolution_hists_Vertex_Z,  regionstring,  TFile_Map_MC,  StartingPlaylist );
  init_MC_ResolutionVars_PlaylistCombined_Histograms(sb.Resolution_hists_Vertex_R,  regionstring,  TFile_Map_MC,  StartingPlaylist );

}





void Helium_3CryoRegionsSideBandTool::init_MC_PlaylistCombined_SideBand_Resolution_Histograms(ME_helium_Playlists Full_Playlist,
    ME_helium_Playlists Empty_Playlist)
{
init_MC_PlaylistCombined_SideBand_Resolution_Histograms(Empty,                      "_resolution",                       TFile_Map_Empty_MC, Empty_Playlist);
init_MC_PlaylistCombined_SideBand_Resolution_Histograms(Empty_UpstreamCap,          "_UpstreamCap_resolution",           TFile_Map_Empty_MC, Empty_Playlist);
init_MC_PlaylistCombined_SideBand_Resolution_Histograms(Empty_Barrel,               "_Barrel_resolution",                TFile_Map_Empty_MC, Empty_Playlist);
init_MC_PlaylistCombined_SideBand_Resolution_Histograms(Empty_DownstreamCap,        "_DownstreamCap_resolution",         TFile_Map_Empty_MC, Empty_Playlist);
init_MC_PlaylistCombined_SideBand_Resolution_Histograms(Empty_DownstreamConcaveCap, "_Downstream_ConcaveCap_resolution", TFile_Map_Empty_MC, Empty_Playlist);

init_MC_PlaylistCombined_SideBand_Resolution_Histograms(Full,                      "_resolution",                       TFile_Map_Full_MC, Full_Playlist);
init_MC_PlaylistCombined_SideBand_Resolution_Histograms(Full_UpstreamCap,          "_UpstreamCap_resolution",           TFile_Map_Full_MC, Full_Playlist);
init_MC_PlaylistCombined_SideBand_Resolution_Histograms(Full_Barrel,               "_Barrel_resolution",                TFile_Map_Full_MC, Full_Playlist);
init_MC_PlaylistCombined_SideBand_Resolution_Histograms(Full_DownstreamCap,        "_DownstreamCap_resolution",         TFile_Map_Full_MC, Full_Playlist);
init_MC_PlaylistCombined_SideBand_Resolution_Histograms(Full_DownstreamConcaveCap, "_Downstream_ConcaveCap_resolution", TFile_Map_Full_MC, Full_Playlist);

init_MC_PlaylistCombined_SideBand_Resolution_RECOandTRUE_Histograms(Empty,                      "_",                       TFile_Map_Empty_MC, Empty_Playlist);
init_MC_PlaylistCombined_SideBand_Resolution_RECOandTRUE_Histograms(Empty_UpstreamCap,          "_UpstreamCap_",           TFile_Map_Empty_MC, Empty_Playlist);
init_MC_PlaylistCombined_SideBand_Resolution_RECOandTRUE_Histograms(Empty_Barrel,               "_Barrel_",                TFile_Map_Empty_MC, Empty_Playlist);
init_MC_PlaylistCombined_SideBand_Resolution_RECOandTRUE_Histograms(Empty_DownstreamCap,        "_DownstreamCap_",         TFile_Map_Empty_MC, Empty_Playlist);
init_MC_PlaylistCombined_SideBand_Resolution_RECOandTRUE_Histograms(Empty_DownstreamConcaveCap, "_Downstream_ConcaveCap_", TFile_Map_Empty_MC, Empty_Playlist);

init_MC_PlaylistCombined_SideBand_Resolution_RECOandTRUE_Histograms(Full,                      "_",                       TFile_Map_Full_MC, Full_Playlist);
init_MC_PlaylistCombined_SideBand_Resolution_RECOandTRUE_Histograms(Full_UpstreamCap,          "_UpstreamCap_",           TFile_Map_Full_MC, Full_Playlist);
init_MC_PlaylistCombined_SideBand_Resolution_RECOandTRUE_Histograms(Full_Barrel,               "_Barrel_",                TFile_Map_Full_MC, Full_Playlist);
init_MC_PlaylistCombined_SideBand_Resolution_RECOandTRUE_Histograms(Full_DownstreamCap,        "_DownstreamCap_",         TFile_Map_Full_MC, Full_Playlist);
init_MC_PlaylistCombined_SideBand_Resolution_RECOandTRUE_Histograms(Full_DownstreamConcaveCap, "_Downstream_ConcaveCap_", TFile_Map_Full_MC, Full_Playlist);



}


void Helium_3CryoRegionsSideBandTool::init_MC_PlaylistCombined_Mig_Histograms(ME_helium_Playlists Full_Playlist,
    ME_helium_Playlists Empty_Playlist){

      init_MC_Mig_Histograms(Empty,                      "",                    TFile_Map_Empty_MC, Empty_Playlist );
      init_MC_Mig_Histograms(Empty_UpstreamCap,         "_UpstreamCap",         TFile_Map_Empty_MC, Empty_Playlist );
      init_MC_Mig_Histograms(Empty_Barrel,              "_Barrel",              TFile_Map_Empty_MC, Empty_Playlist );
      init_MC_Mig_Histograms(Empty_DownstreamCap,       "_DownstreamCap",       TFile_Map_Empty_MC, Empty_Playlist );
      init_MC_Mig_Histograms(Empty_DownstreamConcaveCap,"_Downstream_ConcaveCap",TFile_Map_Empty_MC, Empty_Playlist );

      init_MC_Mig_Histograms(Full,                      "",                    TFile_Map_Full_MC, Full_Playlist );
      init_MC_Mig_Histograms(Full_UpstreamCap,         "_UpstreamCap",         TFile_Map_Full_MC, Full_Playlist );
      init_MC_Mig_Histograms(Full_Barrel,              "_Barrel",              TFile_Map_Full_MC, Full_Playlist );
      init_MC_Mig_Histograms(Full_DownstreamCap,       "_DownstreamCap",       TFile_Map_Full_MC, Full_Playlist );
      init_MC_Mig_Histograms(Full_DownstreamConcaveCap,"_Downstream_ConcaveCap",TFile_Map_Full_MC, Full_Playlist );




    }





void Helium_3CryoRegionsSideBandTool::init_EMPTY_MCShifted_SideBand_FitHistograms(int i , int j, int k, const ME_helium_Playlists Empty_Playlist){
//std::cout<<"Inside::init_EMPTY_MCShifted_SideBand_FitHistograms"<<std::endl;
//init_MCShifted_SideBand_FitHistograms(Empty,                      TFile_Map_Empty_MC[Empty_Playlist], i,  j, k);
init_MCShifted_SideBand_FitHistograms(Empty_UpstreamCap,          TFile_Map_Empty_MC[Empty_Playlist], i,  j, k);
init_MCShifted_SideBand_FitHistograms(Empty_Barrel,               TFile_Map_Empty_MC[Empty_Playlist], i,  j, k);
init_MCShifted_SideBand_FitHistograms(Empty_DownstreamCap,        TFile_Map_Empty_MC[Empty_Playlist], i,  j, k);
init_MCShifted_SideBand_FitHistograms(Empty_DownstreamConcaveCap, TFile_Map_Empty_MC[Empty_Playlist], i,  j, k);
std::cout<<"Finished"<<std::endl;
}

void Helium_3CryoRegionsSideBandTool::init_EMPTY_Combined_MCShifted_SideBand_FitHistograms(int i , int j, int k){
//std::cout<<"Getting index (i,j,k) = ("<< i<<" , "<< j << "," << k <<") " <<std::endl;
///init_MCShifted_SideBand_FitHistograms(Empty,                      TFile_Map_Empty_MC[Empty_Playlist], i,  j, k);
init_MCShifted_PlaylistCombined_SideBand_FitHistograms(Empty_UpstreamCap,          TFile_Map_Empty_MC, i, j, k);
init_MCShifted_PlaylistCombined_SideBand_FitHistograms(Empty_Barrel,               TFile_Map_Empty_MC, i, j, k);
init_MCShifted_PlaylistCombined_SideBand_FitHistograms(Empty_DownstreamCap,        TFile_Map_Empty_MC, i, j, k);
init_MCShifted_PlaylistCombined_SideBand_FitHistograms(Empty_DownstreamConcaveCap, TFile_Map_Empty_MC, i, j, k);
//std::cout<<"Finished"<<std::endl;
}

void Helium_3CryoRegionsSideBandTool::init_EMPTY_Combined_MCShifted_SideBand_FitHistograms_RegionX(int i , int j, int k){
//std::cout<<"Getting index (i,j,k) = ("<< i<<" , "<< j << "," << k <<") " <<std::endl;
//init_MCShifted_SideBand_FitHistograms(Empty,                      TFile_Map_Empty_MC[Empty_Playlist], i,  j, k);
init_MCShifted_PlaylistCombined_SideBand_FitHistograms(Empty_XCenter,         TFile_Map_Empty_MC, i, j, k);
init_MCShifted_PlaylistCombined_SideBand_FitHistograms(Empty_XLeftShelf,      TFile_Map_Empty_MC, i, j, k);
init_MCShifted_PlaylistCombined_SideBand_FitHistograms(Empty_XRightShelf,     TFile_Map_Empty_MC, i, j, k);
init_MCShifted_PlaylistCombined_SideBand_FitHistograms(Empty_XoutsideEdges,   TFile_Map_Empty_MC, i, j, k);
//std::cout<<"Finished"<<std::endl;
}

void Helium_3CryoRegionsSideBandTool::init_EMPTY_Combined_MCShifted_SideBand_FitHistograms_RegionXZ(int i , int j, int k){
//std::cout<<"Getting index (i,j,k) = ("<< i<<" , "<< j << "," << k <<") " <<std::endl;
//init_MCShifted_SideBand_FitHistograms(Empty,                      TFile_Map_Empty_MC[Empty_Playlist], i,  j, k);
init_MCShifted_PlaylistCombined_SideBand_FitHistograms(Empty_XCenter,         TFile_Map_Empty_MC, i, j, k);
init_MCShifted_PlaylistCombined_SideBand_FitHistograms(Empty_XLeftShelf,      TFile_Map_Empty_MC, i, j, k);
init_MCShifted_PlaylistCombined_SideBand_FitHistograms(Empty_XRightShelf,     TFile_Map_Empty_MC, i, j, k);
init_MCShifted_PlaylistCombined_SideBand_FitHistograms(Empty_DownstreamConcaveCap,   TFile_Map_Empty_MC, i, j, k);
//std::cout<<"Finished"<<std::endl;
}

void Helium_3CryoRegionsSideBandTool::initSideBand_FitDataHistograms(Helium3SideBand& sb ,TFile* TFile_Data  )
{
  std::string var;
  std::cout<<"initSideBand_FitDataHistograms "<<std::endl;
  var = sb.HistName_Map[kh_Name_Data_fitTo_vertexX];
  sb.MnvH1D_Vertex_X_data = GetMnvH1D(TFile_Data, var);

  var = sb.HistName_Map[kh_Name_Data_fitTo_vertexY];
  sb.MnvH1D_Vertex_Y_data = GetMnvH1D(TFile_Data, var);

  var = sb.HistName_Map[kh_Name_Data_fitTo_vertexZ];
  sb.MnvH1D_Vertex_Z_data = GetMnvH1D(TFile_Data, var);

  var = sb.HistName_Map[kh_Name_Data_fitTo_vertexR];
  sb.MnvH1D_Vertex_R_data = GetMnvH1D(TFile_Data, var);
}


void Helium_3CryoRegionsSideBandTool::initSideBand_PlaylistCombinedFitDataHistograms(Helium3SideBand& sb, ME_playlist_TFileMAP TFile_Map_Data, ME_helium_Playlists StartingPlaylist )
{
  std::string var;
  std::cout<<"initSideBand_FitDataHistograms "<<std::endl;
  var = sb.HistName_Map[kh_Name_Data_fitTo_vertexX];
  Playlist_MnvH1D_Map  Vertex_X_data = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_Data, var );
  sb.MnvH1D_Vertex_X_data =  Combine_Hists_fromMAP(Vertex_X_data , StartingPlaylist ,"Vertex_X_data");

  var = sb.HistName_Map[kh_Name_Data_fitTo_vertexY];
  Playlist_MnvH1D_Map  Vertex_Y_data = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_Data, var );
  sb.MnvH1D_Vertex_Y_data =  Combine_Hists_fromMAP(Vertex_Y_data , StartingPlaylist ,"Vertex_Y_data");

  var = sb.HistName_Map[kh_Name_Data_fitTo_vertexZ];
  Playlist_MnvH1D_Map  Vertex_Z_data = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_Data, var );
  sb.MnvH1D_Vertex_Z_data =  Combine_Hists_fromMAP(Vertex_Z_data , StartingPlaylist ,"Vertex_Z_data");

  var = sb.HistName_Map[kh_Name_Data_fitTo_vertexR];
  Playlist_MnvH1D_Map  Vertex_R_data = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_Data, var );
  sb.MnvH1D_Vertex_R_data =  Combine_Hists_fromMAP(Vertex_R_data , StartingPlaylist ,"Vertex_R_data");

}







void Helium_3CryoRegionsSideBandTool::initSideBand_FitHistogramsFromTFileMap(Helium3SideBand& sb,
     ME_playlist_TFileMAP TFile_Map_MC, ME_playlist_TFileMAP TFile_Map_Data,
     ME_helium_Playlists StartingPlaylist)
{
  std::string var;

  var = sb.HistName_Map[kh_Name_Data_fitTo_vertexX];
  Playlist_MnvH1D_Map Vertex_X_Data_map =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_Data, var );
  var = sb.HistName_Map[kh_Name_Data_fitTo_vertexY];
  Playlist_MnvH1D_Map Vertex_Y_Data_map =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_Data, var );
  var = sb.HistName_Map[kh_Name_Data_fitTo_vertexZ];
  Playlist_MnvH1D_Map Vertex_Z_Data_map =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_Data, var );
  var = sb.HistName_Map[kh_Name_Data_fitTo_vertexR];
  Playlist_MnvH1D_Map Vertex_R_Data_map =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_Data, var );

  var = sb.HistName_Map[kh_Name_MC_fitTo_vertexX];
  Playlist_MnvH1D_Map Vertex_X_MC_Total_map =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );

  var = sb.HistName_Map[kh_Name_MC_fitTo_vertexY];
  Playlist_MnvH1D_Map Vertex_Y_MC_Total_map =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );

  var = sb.HistName_Map[kh_Name_MC_fitTo_vertexZ];
  Playlist_MnvH1D_Map Vertex_Z_MC_Total_map =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );

  var = sb.HistName_Map[kh_Name_MC_fitTo_vertexR];
  Playlist_MnvH1D_Map Vertex_R_MC_Total_map =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );

  var = sb.HistName_Map[kh_Name_MC_fitTo_vertexX] + "_Material_Helium";
  Playlist_MnvH1D_Map Vertex_X_MC_Helium_map =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  var = sb.HistName_Map[kh_Name_MC_fitTo_vertexX] + "_Material_Aluminium";
  Playlist_MnvH1D_Map Vertex_X_MC_Aluminium_map =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  var = sb.HistName_Map[kh_Name_MC_fitTo_vertexX] + "_Material_Carbon";
  Playlist_MnvH1D_Map Vertex_X_MC_Carbon_map =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  var = sb.HistName_Map[kh_Name_MC_fitTo_vertexX] + "_Material_Iron";
  Playlist_MnvH1D_Map Vertex_X_MC_Iron_map =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  var = sb.HistName_Map[kh_Name_MC_fitTo_vertexX] + "_Material_Lead";
  Playlist_MnvH1D_Map Vertex_X_MC_Lead_map =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  var = sb.HistName_Map[kh_Name_MC_fitTo_vertexX] + "_Material_Other";
  Playlist_MnvH1D_Map Vertex_X_MC_Other_map =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );

  var = sb.HistName_Map[kh_Name_MC_fitTo_vertexY]  + "_Material_Helium";
  Playlist_MnvH1D_Map Vertex_Y_MC_Helium_map =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  var = sb.HistName_Map[kh_Name_MC_fitTo_vertexY]  + "_Material_Aluminium";
  Playlist_MnvH1D_Map Vertex_Y_MC_Aluminium_map =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  var = sb.HistName_Map[kh_Name_MC_fitTo_vertexY]  + "_Material_Carbon";
  Playlist_MnvH1D_Map Vertex_Y_MC_Carbon_map =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  var = sb.HistName_Map[kh_Name_MC_fitTo_vertexY]  + "_Material_Iron";
  Playlist_MnvH1D_Map Vertex_Y_MC_Iron_map =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  var = sb.HistName_Map[kh_Name_MC_fitTo_vertexY]  + "_Material_Lead";
  Playlist_MnvH1D_Map Vertex_Y_MC_Lead_map =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  var = sb.HistName_Map[kh_Name_MC_fitTo_vertexY]  + "_Material_Other";
  Playlist_MnvH1D_Map Vertex_Y_MC_Other_map =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );

  var = sb.HistName_Map[kh_Name_MC_fitTo_vertexZ] + "_Material_Helium";
  Playlist_MnvH1D_Map Vertex_Z_MC_Helium_map =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  var = sb.HistName_Map[kh_Name_MC_fitTo_vertexZ] + "_Material_Aluminium";
  Playlist_MnvH1D_Map Vertex_Z_MC_Aluminium_map =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  var = sb.HistName_Map[kh_Name_MC_fitTo_vertexZ] + "_Material_Carbon";
  Playlist_MnvH1D_Map Vertex_Z_MC_Carbon_map =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  var = sb.HistName_Map[kh_Name_MC_fitTo_vertexZ] + "_Material_Iron";
  Playlist_MnvH1D_Map Vertex_Z_MC_Iron_map =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  var = sb.HistName_Map[kh_Name_MC_fitTo_vertexZ] + "_Material_Lead";
  Playlist_MnvH1D_Map Vertex_Z_MC_Lead_map =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  var = sb.HistName_Map[kh_Name_MC_fitTo_vertexZ] + "_Material_Other";
  Playlist_MnvH1D_Map Vertex_Z_MC_Other_map =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );

  var = sb.HistName_Map[kh_Name_MC_fitTo_vertexR] + "_Material_Helium";
  Playlist_MnvH1D_Map Vertex_R_MC_Helium_map =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  var = sb.HistName_Map[kh_Name_MC_fitTo_vertexR] + "_Material_Aluminium";
  Playlist_MnvH1D_Map Vertex_R_MC_Aluminium_map =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  var = sb.HistName_Map[kh_Name_MC_fitTo_vertexR] + "_Material_Carbon";
  Playlist_MnvH1D_Map Vertex_R_MC_Carbon_map =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  var = sb.HistName_Map[kh_Name_MC_fitTo_vertexR] + "_Material_Iron";
  Playlist_MnvH1D_Map Vertex_R_MC_Iron_map =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  var = sb.HistName_Map[kh_Name_MC_fitTo_vertexR] + "_Material_Lead";
  Playlist_MnvH1D_Map Vertex_R_MC_Lead_map =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  var = sb.HistName_Map[kh_Name_MC_fitTo_vertexR] + "_Material_Other";
  Playlist_MnvH1D_Map Vertex_R_MC_Other_map =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );


  sb.MnvH1D_Vertex_X_data = Combine_Hists_fromMAP(Vertex_X_Data_map , StartingPlaylist ,"MnvH1D_Vertex_X_data");
  sb.MnvH1D_Vertex_Y_data = Combine_Hists_fromMAP(Vertex_Y_Data_map , StartingPlaylist ,"MnvH1D_Vertex_Y_data");
  sb.MnvH1D_Vertex_Z_data = Combine_Hists_fromMAP(Vertex_Z_Data_map , StartingPlaylist ,"MnvH1D_Vertex_Z_data");
  sb.MnvH1D_Vertex_R_data = Combine_Hists_fromMAP(Vertex_R_Data_map , StartingPlaylist ,"MnvH1D_Vertex_R_data");

  sb.MnvH1D_Vertex_X_mc_total = Combine_Hists_fromMAP(Vertex_X_MC_Total_map , StartingPlaylist ,"MnvH1D_Vertex_X_mc_total");
  sb.MnvH1D_Vertex_Y_mc_total = Combine_Hists_fromMAP(Vertex_Y_MC_Total_map , StartingPlaylist ,"MnvH1D_Vertex_Y_mc_total");
  sb.MnvH1D_Vertex_Z_mc_total = Combine_Hists_fromMAP(Vertex_Z_MC_Total_map , StartingPlaylist ,"MnvH1D_Vertex_Z_mc_total");
  sb.MnvH1D_Vertex_R_mc_total = Combine_Hists_fromMAP(Vertex_R_MC_Total_map , StartingPlaylist ,"MnvH1D_Vertex_R_mc_total");

  //Vectex X material
  sb.MnvH1D_Vertex_X_Helium[0] =    Combine_Hists_fromMAP(Vertex_X_MC_Helium_map,   StartingPlaylist, "MnvH1D_Vertex_X_Helium");
  sb.MnvH1D_Vertex_X_Aluminium[0] = Combine_Hists_fromMAP(Vertex_X_MC_Aluminium_map, StartingPlaylist, "MnvH1D_Vertex_X_Aluminium");
  sb.MnvH1D_Vertex_X_Carbon[0] =    Combine_Hists_fromMAP(Vertex_X_MC_Carbon_map,   StartingPlaylist, "MnvH1D_Vertex_X_Carbon");
  sb.MnvH1D_Vertex_X_Iron[0] =      Combine_Hists_fromMAP(Vertex_X_MC_Iron_map,     StartingPlaylist, "MnvH1D_Vertex_X_Iron");
  sb.MnvH1D_Vertex_X_Lead[0] =      Combine_Hists_fromMAP(Vertex_X_MC_Lead_map,     StartingPlaylist, "MnvH1D_Vertex_X_Lead");
  sb.MnvH1D_Vertex_X_Other[0] =     Combine_Hists_fromMAP(Vertex_X_MC_Other_map,    StartingPlaylist, "MnvH1D_Vertex_X_Other");

  //Vectex Y material
  sb.MnvH1D_Vertex_Y_Helium[0] =    Combine_Hists_fromMAP(Vertex_Y_MC_Helium_map,   StartingPlaylist, "MnvH1D_Vertex_Y_Helium");
  sb.MnvH1D_Vertex_Y_Aluminium[0] = Combine_Hists_fromMAP(Vertex_Y_MC_Aluminium_map, StartingPlaylist, "MnvH1D_Vertex_Y_Aluminium");
  sb.MnvH1D_Vertex_Y_Carbon[0] =    Combine_Hists_fromMAP(Vertex_Y_MC_Carbon_map,   StartingPlaylist, "MnvH1D_Vertex_Y_Carbon");
  sb.MnvH1D_Vertex_Y_Iron[0] =      Combine_Hists_fromMAP(Vertex_Y_MC_Iron_map,     StartingPlaylist, "MnvH1D_Vertex_Y_Iron");
  sb.MnvH1D_Vertex_Y_Lead[0] =      Combine_Hists_fromMAP(Vertex_Y_MC_Lead_map,     StartingPlaylist, "MnvH1D_Vertex_Y_Lead");
  sb.MnvH1D_Vertex_Y_Other[0] =     Combine_Hists_fromMAP(Vertex_Y_MC_Other_map,    StartingPlaylist, "MnvH1D_Vertex_Y_Other");

  //Vectex Z material
  sb.MnvH1D_Vertex_Z_Helium[0] =    Combine_Hists_fromMAP(Vertex_Z_MC_Helium_map,   StartingPlaylist, "MnvH1D_Vertex_Z_Helium");
  sb.MnvH1D_Vertex_Z_Aluminium[0] = Combine_Hists_fromMAP(Vertex_Z_MC_Aluminium_map, StartingPlaylist, "MnvH1D_Vertex_Z_Aluminium");
  sb.MnvH1D_Vertex_Z_Carbon[0] =    Combine_Hists_fromMAP(Vertex_Z_MC_Carbon_map,   StartingPlaylist, "MnvH1D_Vertex_Z_Carbon");
  sb.MnvH1D_Vertex_Z_Iron[0] =      Combine_Hists_fromMAP(Vertex_Z_MC_Iron_map,     StartingPlaylist, "MnvH1D_Vertex_Z_Iron");
  sb.MnvH1D_Vertex_Z_Lead[0] =      Combine_Hists_fromMAP(Vertex_Z_MC_Lead_map,     StartingPlaylist, "MnvH1D_Vertex_Z_Lead");
  sb.MnvH1D_Vertex_Z_Other[0] =     Combine_Hists_fromMAP(Vertex_Z_MC_Other_map,    StartingPlaylist, "MnvH1D_Vertex_Z_Other");

  //Vectex Z material
  sb.MnvH1D_Vertex_R_Helium[0] =    Combine_Hists_fromMAP(Vertex_R_MC_Helium_map,   StartingPlaylist, "MnvH1D_Vertex_R_Helium");
  sb.MnvH1D_Vertex_R_Aluminium[0] = Combine_Hists_fromMAP(Vertex_R_MC_Aluminium_map, StartingPlaylist, "MnvH1D_Vertex_R_Aluminium");
  sb.MnvH1D_Vertex_R_Carbon[0] =    Combine_Hists_fromMAP(Vertex_R_MC_Carbon_map,   StartingPlaylist, "MnvH1D_Vertex_R_Carbon");
  sb.MnvH1D_Vertex_R_Iron[0] =      Combine_Hists_fromMAP(Vertex_R_MC_Iron_map,     StartingPlaylist, "MnvH1D_Vertex_R_Iron");
  sb.MnvH1D_Vertex_R_Lead[0] =      Combine_Hists_fromMAP(Vertex_R_MC_Lead_map,     StartingPlaylist, "MnvH1D_Vertex_R_Lead");
  sb.MnvH1D_Vertex_R_Other[0] =     Combine_Hists_fromMAP(Vertex_R_MC_Other_map,    StartingPlaylist, "MnvH1D_Vertex_R_Other");

}






  void Helium_3CryoRegionsSideBandTool::initSideBand_XSecHistograms( TFile* TFile_MC, TFile* TFile_Data ,
    Helium3SideBand& sb, XSec_Var3band& xsec_var, std::string Data_hist, std::string MChist_name,
      std::string Xaxis_name,std::string Var_name  )
  {
    xsec_var.Xaxis_Title = Xaxis_name;
    xsec_var.name = Var_name;
    std::string var;
    //std::cout<<"inside:initSideBand_XSecHistograms"<<std::endl;
    xsec_var.MnvH1D_data = GetMnvH1D(TFile_Data, Data_hist);
    xsec_var.MnvH1D_mc_total = GetMnvH1D(TFile_MC, MChist_name);

    var = MChist_name + "_Material_Helium";
    xsec_var.MnvH1D_Helium[0] = GetMnvH1D(TFile_MC, var);

    var = MChist_name + "_Material_Aluminium";
    xsec_var.MnvH1D_Aluminium[0] = GetMnvH1D(TFile_MC, var);

    var = MChist_name + "_Material_Carbon";
    xsec_var.MnvH1D_Carbon[0] = GetMnvH1D(TFile_MC, var);

    var = MChist_name + "_Material_Lead";
    xsec_var.MnvH1D_Lead[0] = GetMnvH1D(TFile_MC, var);

    var = MChist_name + "_Material_Iron";
    xsec_var.MnvH1D_Iron[0] = GetMnvH1D(TFile_MC, var);

    var = MChist_name + "_Material_Other";
    xsec_var.MnvH1D_Other[0] = GetMnvH1D(TFile_MC, var);
}

void Helium_3CryoRegionsSideBandTool::initSideBandFromTFileMap_XSecHistograms( ME_playlist_TFileMAP TFile_Map_MC, ME_playlist_TFileMAP TFile_Map_Data ,
  Helium3SideBand& sb, XSec_Var3band& xsec_var, std::string Data_hist, std::string MChist_name,
    std::string Xaxis_name,std::string Var_name, ME_helium_Playlists StartingPlaylist  )
{
  xsec_var.Xaxis_Title = Xaxis_name;
  xsec_var.name = Var_name;
  std::string var;
  //std::cout<<"initSideBandFromTFileMap_XSecHistograms"<<std::endl;

  Playlist_MnvH1D_Map Data_map =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_Data, Data_hist );
  xsec_var.MnvH1D_data = Combine_Hists_fromMAP(Data_map , StartingPlaylist ,"MnvH1D_data");


  Playlist_MnvH1D_Map MC_map =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, MChist_name );
  xsec_var.MnvH1D_mc_total = Combine_Hists_fromMAP(MC_map , StartingPlaylist ,"MnvH1D_data");

  var = MChist_name + "_Material_Helium";
  Playlist_MnvH1D_Map MC_map_Helium =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  xsec_var.MnvH1D_Helium[0]= Combine_Hists_fromMAP(MC_map_Helium, StartingPlaylist ,"MnvH1D_MC_Helium");

  var = MChist_name + "_Material_Aluminium";
  Playlist_MnvH1D_Map MC_map_Aluminium =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  xsec_var.MnvH1D_Aluminium[0] = Combine_Hists_fromMAP(MC_map_Aluminium , StartingPlaylist ,"MnvH1D_MC_Aluminium");

  var = MChist_name + "_Material_Carbon";
  Playlist_MnvH1D_Map MC_map_Carbon =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  xsec_var.MnvH1D_Carbon[0] = Combine_Hists_fromMAP(MC_map_Carbon , StartingPlaylist ,"MnvH1D_MC_Carbon");

  var = MChist_name + "_Material_Lead";
  Playlist_MnvH1D_Map MC_map_Lead =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  xsec_var.MnvH1D_Lead[0] = Combine_Hists_fromMAP(MC_map_Lead , StartingPlaylist ,"MnvH1D_MC_Lead");

  var = MChist_name + "_Material_Iron";
  Playlist_MnvH1D_Map MC_map_Iron =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  xsec_var.MnvH1D_Iron[0] = Combine_Hists_fromMAP(MC_map_Iron , StartingPlaylist ,"MnvH1D_MC_Iron");

  var = MChist_name + "_Material_Other";
  Playlist_MnvH1D_Map MC_map_Other =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  xsec_var.MnvH1D_Other[0] = Combine_Hists_fromMAP(MC_map_Other , StartingPlaylist ,"MnvH1D_MC_Other");

}

void Helium_3CryoRegionsSideBandTool::initNSideBandFromTFileMap_XSecHistograms_data(
  ME_playlist_TFileMAP TFile_Map_Data ,
  HeliumNSideBand& sb,
  XSec_VarNband& xsec_var,
  ME_helium_Playlists StartingPlaylist  )
  {
     //std::cout<<"initSideBandFromTFileMap_XSecHistograms"<<std::endl;
     Playlist_MnvH1D_Map Data_map =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_Data, xsec_var.name_data );
     xsec_var.MnvH1D_data = Combine_Hists_fromMAP(Data_map , StartingPlaylist ,"MnvH1D_data");
   }


   void Helium_3CryoRegionsSideBandTool::initNSideBandFromTFileMap_XSecHistograms_MC(
     ME_playlist_TFileMAP TFile_Map_MC,
     HeliumNSideBand& sb,
     XSec_VarNband& xsec_var,
     ME_helium_Playlists StartingPlaylist  )
     {
       std::string var;
        std::string MChist_name =   xsec_var.name;
        var = MChist_name + "_Helium";
        Playlist_MnvH1D_Map MC_map_Helium =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
        xsec_var.MnvH1D_Helium[0]= Combine_Hists_fromMAP(MC_map_Helium, StartingPlaylist ,"MnvH1D_MC_Helium");

        var = MChist_name + "_Aluminium";
        Playlist_MnvH1D_Map MC_map_Aluminium =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
        xsec_var.MnvH1D_Aluminium[0] = Combine_Hists_fromMAP(MC_map_Aluminium , StartingPlaylist ,"MnvH1D_MC_Aluminium");

        var = MChist_name + "_Carbon";
        Playlist_MnvH1D_Map MC_map_Carbon =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
        xsec_var.MnvH1D_Carbon[0] = Combine_Hists_fromMAP(MC_map_Carbon , StartingPlaylist ,"MnvH1D_MC_Carbon");

        var = MChist_name + "_Lead";
        Playlist_MnvH1D_Map MC_map_Lead =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
        xsec_var.MnvH1D_Lead[0] = Combine_Hists_fromMAP(MC_map_Lead , StartingPlaylist ,"MnvH1D_MC_Lead");

        var = MChist_name + "_Iron";
        Playlist_MnvH1D_Map MC_map_Iron =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
        xsec_var.MnvH1D_Iron[0] = Combine_Hists_fromMAP(MC_map_Iron , StartingPlaylist ,"MnvH1D_MC_Iron");

        var = MChist_name + "_Other";
        Playlist_MnvH1D_Map MC_map_Other =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
        xsec_var.MnvH1D_Other[0] = Combine_Hists_fromMAP(MC_map_Other , StartingPlaylist ,"MnvH1D_MC_Other");

      }





void Helium_3CryoRegionsSideBandTool::Inti_XSec_Xaxis_label(XSec_Var3band& xsec_var, std::string xaxislabel){

  xsec_var.MnvH1D_data->GetXaxis()->SetTitle(xaxislabel.c_str());
  xsec_var.MnvH1D_mc_total->GetXaxis()->SetTitle(xaxislabel.c_str());
  xsec_var.MnvH1D_Helium[0]->GetXaxis()->SetTitle(xaxislabel.c_str());
  xsec_var.MnvH1D_Aluminium[0]->GetXaxis()->SetTitle(xaxislabel.c_str());
  xsec_var.MnvH1D_Carbon[0]->GetXaxis()->SetTitle(xaxislabel.c_str());
  xsec_var.MnvH1D_Iron[0]->GetXaxis()->SetTitle(xaxislabel.c_str());
  xsec_var.MnvH1D_Lead[0]->GetXaxis()->SetTitle(xaxislabel.c_str());
  xsec_var.MnvH1D_Other[0]->GetXaxis()->SetTitle(xaxislabel.c_str());
}

void Helium_3CryoRegionsSideBandTool::Inti_Xaxis_labels(Helium3SideBand &sb,  std::string xaxislabel ){

Inti_XSec_Xaxis_label(sb.muon_PT,                 "P_{T,#mu} [GeV]");
Inti_XSec_Xaxis_label(sb.muon_PZ,                 "P_{Z,#mu} [GeV]");
Inti_XSec_Xaxis_label(sb.muon_theta,              "#theta_{#mu} [Deg]");
Inti_XSec_Xaxis_label(sb.muon_E,                  "E_{#mu} [GeV]" );
Inti_XSec_Xaxis_label(sb.DistancetoEdge,          "Distance to Nearest Wall [mm]");
Inti_XSec_Xaxis_label(sb.DistancetoUpstreamCap,   "Distance to USCap [mm]");
Inti_XSec_Xaxis_label(sb.DistancetoDownstreamCap, "Distance to DSCap [mm]");

Inti_XSec_Xaxis_label(sb.DistancetoUpstreamCap_RCut,   "[RCut] Distance to USCap [mm]");
Inti_XSec_Xaxis_label(sb.DistancetoDownstreamCap_RCut, "[RCut] Distance to DSCap [mm]");
Inti_XSec_Xaxis_label(sb.Vertex_Z_RCut,                "[RCut] Vertex Z [mm]");
Inti_XSec_Xaxis_label(sb.Vertex_X_RCut,                "[RCut] Vertex X [mm]");
Inti_XSec_Xaxis_label(sb.Vertex_Y_RCut,                "[RCut] Vertex Y [mm]");
Inti_XSec_Xaxis_label(sb.Vertex_R_RCut,                "[RCut] Vertex R [mm]");
//Inti_XSec_Xaxis_label(sb.DistancetoEdge_Caps,                "[Caps] Distance to Nearest Wall [mm]");
//Inti_XSec_Xaxis_label(sb.DistancetoEdge_Barrel,                "[Barrel] Distance to Nearest Wall [mm]");



}





void Helium_3CryoRegionsSideBandTool::initFull_EmptySideBand_XSecHistograms()
{

  //initSideBand_XSecHistograms(Empty , "");
  //initSideBand_XSecHistograms(Empty_UpstreamCap , "_UpstreamCap");
  //initSideBand_XSecHistograms(Empty_Barrel , "_Barrel");
  //initSideBand_XSecHistograms(Empty_DownstreamCap , "_DownstreamCap");

  //initSideBand_XSecHistograms(Full , "");
  //initSideBand_XSecHistograms(Full_UpstreamCap , "_UpstreamCap");
  //initSideBand_XSecHistograms(Full_Barrel , "_Barrel");
  //initSideBand_XSecHistograms(Full_DownstreamCap , "_DownstreamCap");

}




  void Helium_3CryoRegionsSideBandTool::initSideBand_XSecHistograms(Helium3SideBand& sb , std::string ExtraLabel,
     TFile* TFile_MC, TFile* TFile_Data )
  {

    std::string Data_hist_name;
    std::string MC_hist_name;
    MC_hist_name = "h_MuonPT" + ExtraLabel;
    Data_hist_name = "h_Data_MuonPT" + ExtraLabel;
    initSideBand_XSecHistograms(TFile_MC, TFile_Data, sb, sb.muon_PT,    Data_hist_name,   MC_hist_name," P_{T, #mu} [GeV]", "Muon P{T}");
    MC_hist_name = "h_MuonPZ" + ExtraLabel;
    Data_hist_name = "h_Data_MuonPZ" + ExtraLabel;
    initSideBand_XSecHistograms(TFile_MC, TFile_Data, sb, sb.muon_PZ,   Data_hist_name,   MC_hist_name," P_{Z, #mu} [GeV]", "Muon P{Z}");
    MC_hist_name = "h_MuonTheta" + ExtraLabel;
    Data_hist_name = "h_Data_MuonTheta" + ExtraLabel;
    initSideBand_XSecHistograms(TFile_MC, TFile_Data, sb, sb.muon_theta,  Data_hist_name,   MC_hist_name," #theta_{#mu} [Deg]", "Muon #theta");
    MC_hist_name = "h_MuonE" + ExtraLabel;
    Data_hist_name = "h_Data_MuonE" + ExtraLabel;
    initSideBand_XSecHistograms(TFile_MC, TFile_Data, sb, sb.muon_E, Data_hist_name,   MC_hist_name," KE_{#mu} [GeV]", "Muon KE");
    MC_hist_name = "h_MuonDOCA" + ExtraLabel;
    Data_hist_name = "h_Data_MuonDOCA" + ExtraLabel;
    initSideBand_XSecHistograms(TFile_MC, TFile_Data, sb, sb.muon_doca, Data_hist_name,   MC_hist_name,"Muon DOCA [mm]", "Muon Doca");
    MC_hist_name = "h_Distance_to_InnerTank" + ExtraLabel;
    Data_hist_name = "h_Data_Distance_to_InnerTank" + ExtraLabel;
    initSideBand_XSecHistograms(TFile_MC, TFile_Data, sb, sb.DistancetoEdge, Data_hist_name,   MC_hist_name, "Distance to Nearest Wall  [mm]", "Distance to Nearest Wall ");
    MC_hist_name = "h_secTrk_DOCA" + ExtraLabel;
    Data_hist_name = "h_Data_secTrk_DOCA" + ExtraLabel;
    initSideBand_XSecHistograms(TFile_MC, TFile_Data, sb, sb.SecTrk_doca, Data_hist_name,   MC_hist_name,"2ndTrk Doca [mm]", "DOCA");
    MC_hist_name = "h_secTrk_tracklength" + ExtraLabel;
    Data_hist_name = "h_Data_secTrk_Length" + ExtraLabel;
    initSideBand_XSecHistograms(TFile_MC, TFile_Data, sb, sb.TrackLength, Data_hist_name,   MC_hist_name,"2ndTrk Length [mm]", "Trk Length");

    MC_hist_name = "h_CryoVertex_Z_RCut" + ExtraLabel;
    Data_hist_name = "h_Data_CryoVertex_Z_RCut" + ExtraLabel;
    initSideBand_XSecHistograms(TFile_MC, TFile_Data, sb, sb.Vertex_Z_RCut, Data_hist_name,   MC_hist_name," [RCut] Vertex Z [mm]", "Vertex Z");

    MC_hist_name = "h_CryoVertex_X_RCut" + ExtraLabel;
    Data_hist_name = "h_Data_CryoVertex_X_RCut" + ExtraLabel;
    initSideBand_XSecHistograms(TFile_MC, TFile_Data, sb, sb.Vertex_X_RCut, Data_hist_name,   MC_hist_name," [RCut] Vertex X [mm]", "Vertex X");

    MC_hist_name = "h_CryoVertex_Y_RCut" + ExtraLabel;
    Data_hist_name = "h_Data_CryoVertex_Y_RCut" + ExtraLabel;
    initSideBand_XSecHistograms(TFile_MC, TFile_Data, sb, sb.Vertex_Y_RCut, Data_hist_name,   MC_hist_name," [RCut] Vertex Y [mm]", "Vertex Y");

    MC_hist_name = "h_CryoVertex_R_RCut" + ExtraLabel;
    Data_hist_name = "h_Data_CryoVertex_R_RCut" + ExtraLabel;
    initSideBand_XSecHistograms(TFile_MC, TFile_Data, sb, sb.Vertex_R_RCut, Data_hist_name,   MC_hist_name," [RCut] Vertex R [mm]", "Vertex R");

    MC_hist_name = "h_Distance_to_upstreamCap" + ExtraLabel;
    Data_hist_name = "h_Data_Distance_to_UpstreamCap" + ExtraLabel;
    initSideBand_XSecHistograms(TFile_MC, TFile_Data, sb, sb.DistancetoUpstreamCap, Data_hist_name,   MC_hist_name,"Distance USCap [mm]", " Distance upstream Cap");
    MC_hist_name = "h_Distance_to_downstreamCap" + ExtraLabel;
    Data_hist_name = "h_Data_Distance_to_DownstreamCap" + ExtraLabel;
    initSideBand_XSecHistograms(TFile_MC, TFile_Data, sb, sb.DistancetoDownstreamCap, Data_hist_name,   MC_hist_name,"Distance DSCap [mm]", " Distance downstream Cap");

    MC_hist_name = "h_Distance_to_upstreamCap_RCut" + ExtraLabel;
    Data_hist_name = "h_Data_Distance_to_UpstreamCap_RCut" + ExtraLabel;
    initSideBand_XSecHistograms(TFile_MC, TFile_Data, sb, sb.DistancetoUpstreamCap_RCut, Data_hist_name,   MC_hist_name,"[RCut] Distance USCap [mm]", " Distance upstream Cap");

    MC_hist_name = "h_Distance_to_downstreamCap_RCut" + ExtraLabel;
    Data_hist_name = "h_Data_Distance_to_DownstreamCap_RCut" + ExtraLabel;
    initSideBand_XSecHistograms(TFile_MC, TFile_Data, sb, sb.DistancetoDownstreamCap_RCut, Data_hist_name,   MC_hist_name,"[RCut] Distance DSCap [mm]", " Distance downstream Cap");

  //  MC_hist_name = "h_Distance_to_downstreamCap_RCut" + ExtraLabel;
  //  Data_hist_name = "h_Data_Distance_to_DownstreamCap_RCut" + ExtraLabel;
  //  initSideBand_XSecHistograms(TFile_MC, TFile_Data, sb, sb.DistancetoEdge_Caps, Data_hist_name,   MC_hist_name,"[Caps] Distance to Nearest Wall  [mm]", " Distance downstream Cap");

  //  MC_hist_name = "h_Distance_to_downstreamCap_RCut" + ExtraLabel;
  //  Data_hist_name = "h_Data_Distance_to_DownstreamCap_RCut" + ExtraLabel;
  //  initSideBand_XSecHistograms(TFile_MC, TFile_Data, sb, sb.DistancetoEdge_Barrel, Data_hist_name,   MC_hist_name,"[Barrel] Distance to Nearest Wall  [mm]", " Distance downstream Cap");


  }

  void Helium_3CryoRegionsSideBandTool::initSideBand_XSecHistograms(Helium3SideBand& sb,
     std::string ExtraLabel, ME_playlist_TFileMAP TFile_Map_MC,
     ME_playlist_TFileMAP TFile_Map_Data, ME_helium_Playlists StartingPlaylist )
{
  //std::cout<<"inside MultPlaylist:initSideBand_XSecHistograms "<<std::endl;
  std::string Data_hist_name;
  std::string MC_hist_name;
  MC_hist_name = "h_MuonPT" + ExtraLabel;
  Data_hist_name = "h_Data_MuonPT" + ExtraLabel;
  initSideBandFromTFileMap_XSecHistograms( TFile_Map_MC, TFile_Map_Data ,
    sb, sb.muon_PT,    Data_hist_name,   MC_hist_name," P_{T, #mu} [GeV]", "Muon P{T}", StartingPlaylist  );

  MC_hist_name = "h_MuonPZ" + ExtraLabel;
  Data_hist_name = "h_Data_MuonPZ" + ExtraLabel;
  initSideBandFromTFileMap_XSecHistograms( TFile_Map_MC, TFile_Map_Data ,
    sb, sb.muon_PZ,    Data_hist_name,   MC_hist_name,"P_{Z, #mu} [GeV]", "Muon P{Z}", StartingPlaylist  );

  MC_hist_name = "h_MuonTheta" + ExtraLabel;
  Data_hist_name = "h_Data_MuonTheta" + ExtraLabel;
  initSideBandFromTFileMap_XSecHistograms( TFile_Map_MC, TFile_Map_Data ,
    sb, sb.muon_theta,    Data_hist_name,   MC_hist_name, "#theta_{#mu} [Deg]", "Muon #theta", StartingPlaylist  );
  MC_hist_name = "h_MuonE" + ExtraLabel;
  Data_hist_name = "h_Data_MuonE" + ExtraLabel;
  initSideBandFromTFileMap_XSecHistograms( TFile_Map_MC, TFile_Map_Data ,
  sb, sb.muon_E,    Data_hist_name,   MC_hist_name, "T_{#mu} [GeV]", "Muon T", StartingPlaylist  );
  MC_hist_name = "h_MuonDOCA" + ExtraLabel;
  Data_hist_name = "h_Data_MuonDOCA" + ExtraLabel;
  initSideBandFromTFileMap_XSecHistograms( TFile_Map_MC, TFile_Map_Data ,
  sb, sb.muon_doca,    Data_hist_name,   MC_hist_name, "DOCA [mm]", "Muon DOCA", StartingPlaylist  );
  MC_hist_name = "h_Distance_to_InnerTank" + ExtraLabel;
  Data_hist_name = "h_Data_Distance_to_InnerTank" + ExtraLabel;
  initSideBandFromTFileMap_XSecHistograms( TFile_Map_MC, TFile_Map_Data ,
  sb, sb.DistancetoEdge,    Data_hist_name,   MC_hist_name, "Distance to Nearest Wall  [mm]", "Distance to Nearest Wall ", StartingPlaylist  );
  MC_hist_name = "h_secTrk_DOCA" + ExtraLabel;
  Data_hist_name = "h_Data_secTrk_DOCA" + ExtraLabel;
  initSideBandFromTFileMap_XSecHistograms( TFile_Map_MC, TFile_Map_Data ,
  sb, sb.SecTrk_doca,    Data_hist_name,   MC_hist_name, "2ndTrk DOCA [mm]", "2ndTrk DOCA", StartingPlaylist  );

  MC_hist_name = "h_secTrk_tracklength" + ExtraLabel;
  Data_hist_name = "h_Data_secTrk_Length" + ExtraLabel;
  initSideBandFromTFileMap_XSecHistograms( TFile_Map_MC, TFile_Map_Data ,
  sb, sb.TrackLength,    Data_hist_name,   MC_hist_name, "TrkLength [cm]", "TrkLength", StartingPlaylist  );

  MC_hist_name = "h_CryoVertex_Z_RCut" + ExtraLabel;
  Data_hist_name = "h_Data_CryoVertex_Z_RCut" + ExtraLabel;
  initSideBandFromTFileMap_XSecHistograms( TFile_Map_MC, TFile_Map_Data, sb, sb.Vertex_Z_RCut, Data_hist_name,   MC_hist_name," [RCut] Vertex Z [mm]", " Vertex Z", StartingPlaylist );

  MC_hist_name = "h_CryoVertex_X_RCut" + ExtraLabel;
  Data_hist_name = "h_Data_CryoVertex_X_RCut" + ExtraLabel;
  initSideBandFromTFileMap_XSecHistograms( TFile_Map_MC, TFile_Map_Data, sb, sb.Vertex_X_RCut, Data_hist_name,   MC_hist_name," [RCut] Vertex X [mm]", " Vertex X", StartingPlaylist );

  MC_hist_name = "h_CryoVertex_Y_RCut" + ExtraLabel;
  Data_hist_name = "h_Data_CryoVertex_Y_RCut" + ExtraLabel;
  initSideBandFromTFileMap_XSecHistograms( TFile_Map_MC, TFile_Map_Data, sb, sb.Vertex_Y_RCut, Data_hist_name,   MC_hist_name," [RCut] Vertex Y [mm]", " Vertex Y", StartingPlaylist );

  MC_hist_name = "h_CryoVertex_R_RCut" + ExtraLabel;
  Data_hist_name = "h_Data_CryoVertex_R_RCut" + ExtraLabel;
  initSideBandFromTFileMap_XSecHistograms( TFile_Map_MC, TFile_Map_Data, sb, sb.Vertex_R_RCut, Data_hist_name,   MC_hist_name," [RCut] Vertex R [mm]", " Vertex R", StartingPlaylist );



  MC_hist_name = "h_Distance_to_upstreamCap" + ExtraLabel;
  Data_hist_name = "h_Data_Distance_to_UpstreamCap" + ExtraLabel;
  initSideBandFromTFileMap_XSecHistograms( TFile_Map_MC, TFile_Map_Data, sb, sb.DistancetoUpstreamCap, Data_hist_name,   MC_hist_name,"Distance USCap [mm]", " Distance upstream Cap", StartingPlaylist );

  MC_hist_name = "h_Distance_to_downstreamCap" + ExtraLabel;
  Data_hist_name = "h_Data_Distance_to_DownstreamCap" + ExtraLabel;
  initSideBandFromTFileMap_XSecHistograms( TFile_Map_MC, TFile_Map_Data, sb, sb.DistancetoDownstreamCap, Data_hist_name,   MC_hist_name,"Distance DSCap [mm]", " Distance downstream Cap", StartingPlaylist );

  MC_hist_name = "h_Distance_to_upstreamCap_RCut" + ExtraLabel;
  Data_hist_name = "h_Data_Distance_to_UpstreamCap_RCut" + ExtraLabel;
  initSideBandFromTFileMap_XSecHistograms( TFile_Map_MC, TFile_Map_Data, sb, sb.DistancetoUpstreamCap_RCut, Data_hist_name,   MC_hist_name,"Distance USCap [mm]", " Distance upstream Cap", StartingPlaylist );

  MC_hist_name = "h_Distance_to_downstreamCap_RCut" + ExtraLabel;
  Data_hist_name = "h_Data_Distance_to_DownstreamCap_RCut" + ExtraLabel;
  initSideBandFromTFileMap_XSecHistograms( TFile_Map_MC, TFile_Map_Data, sb, sb.DistancetoDownstreamCap_RCut, Data_hist_name,   MC_hist_name,"Distance DSCap [mm]", " Distance downstream Cap", StartingPlaylist );




}



void Helium_3CryoRegionsSideBandTool::subtract_Data_total(Helium3SideBand& sb_toSubtract, Helium3SideBand& Empty){

  sb_toSubtract.MnvH1D_Vertex_X_data->Add(Empty.MnvH1D_Vertex_X_data, -1.0);
  sb_toSubtract.MnvH1D_Vertex_Y_data->Add(Empty.MnvH1D_Vertex_Y_data, -1.0);
  sb_toSubtract.MnvH1D_Vertex_Z_data->Add(Empty.MnvH1D_Vertex_Z_data, -1.0);
  sb_toSubtract.MnvH1D_Vertex_R_data->Add(Empty.MnvH1D_Vertex_R_data, -1.0);

}


void Helium_3CryoRegionsSideBandTool::subtract_MC_total(Helium3SideBand& sb_toSubtract, Helium3SideBand& Empty){
  sb_toSubtract.MnvH1D_Vertex_X_mc_total->Add(Empty.MnvH1D_Vertex_X_mc_total,-1.0);
  sb_toSubtract.MnvH1D_Vertex_Y_mc_total->Add(Empty.MnvH1D_Vertex_Y_mc_total,-1.0);
  sb_toSubtract.MnvH1D_Vertex_Z_mc_total->Add(Empty.MnvH1D_Vertex_Z_mc_total,-1.0);
  sb_toSubtract.MnvH1D_Vertex_R_mc_total->Add(Empty.MnvH1D_Vertex_R_mc_total,-1.0);

}

void Helium_3CryoRegionsSideBandTool::subtract_MC_Material(Helium3SideBand& sb_toSubtract, Helium3SideBand& Empty, int ind){

  sb_toSubtract.MnvH1D_Vertex_X_Helium[ind]->Add(Empty.MnvH1D_Vertex_X_Helium[ind] ,-1.0);
  sb_toSubtract.MnvH1D_Vertex_X_Aluminium[ind]->Add(Empty.MnvH1D_Vertex_X_Aluminium[ind] ,-1.0);
  sb_toSubtract.MnvH1D_Vertex_X_Carbon[ind]->Add(Empty.MnvH1D_Vertex_X_Carbon[ind] ,-1.0);
  sb_toSubtract.MnvH1D_Vertex_X_Iron[ind]->Add(Empty.MnvH1D_Vertex_X_Iron[ind] ,-1.0);
  sb_toSubtract.MnvH1D_Vertex_X_Lead[ind]->Add(Empty.MnvH1D_Vertex_X_Lead[ind] ,-1.0);
  sb_toSubtract.MnvH1D_Vertex_X_Other[ind]->Add(Empty.MnvH1D_Vertex_X_Other[ind] ,-1.0);
  sb_toSubtract.MnvH1D_Vertex_Y_Helium[ind]->Add(Empty.MnvH1D_Vertex_Y_Helium[ind] ,-1.0);
  sb_toSubtract.MnvH1D_Vertex_Y_Aluminium[ind]->Add(Empty.MnvH1D_Vertex_Y_Aluminium[ind] ,-1.0);
  sb_toSubtract.MnvH1D_Vertex_Y_Carbon[ind]->Add(Empty.MnvH1D_Vertex_Y_Carbon[ind] ,-1.0);
  sb_toSubtract.MnvH1D_Vertex_Y_Iron[ind]->Add(Empty.MnvH1D_Vertex_Y_Iron[ind] ,-1.0);
  sb_toSubtract.MnvH1D_Vertex_Y_Lead[ind]->Add(Empty.MnvH1D_Vertex_Y_Lead[ind] ,-1.0);
  sb_toSubtract.MnvH1D_Vertex_Y_Other[ind]->Add(Empty.MnvH1D_Vertex_Y_Other[ind] ,-1.0);
  sb_toSubtract.MnvH1D_Vertex_Z_Helium[ind]->Add(Empty.MnvH1D_Vertex_Z_Helium[ind],-1.0);
  sb_toSubtract.MnvH1D_Vertex_Z_Aluminium[ind]->Add(Empty.MnvH1D_Vertex_Z_Aluminium[ind],-1.0);
  sb_toSubtract.MnvH1D_Vertex_Z_Carbon[ind]->Add(Empty.MnvH1D_Vertex_Z_Carbon[ind],-1.0);
  sb_toSubtract.MnvH1D_Vertex_Z_Iron[ind]->Add(Empty.MnvH1D_Vertex_Z_Iron[ind],-1.0);
  sb_toSubtract.MnvH1D_Vertex_Z_Lead[ind]->Add(Empty.MnvH1D_Vertex_Z_Lead[ind],-1.0);
  sb_toSubtract.MnvH1D_Vertex_Z_Other[ind]->Add(Empty.MnvH1D_Vertex_Z_Other[ind],-1.0);

  sb_toSubtract.MnvH1D_Vertex_R_Helium[ind]->Add(Empty.MnvH1D_Vertex_R_Helium[ind],-1.0);
  sb_toSubtract.MnvH1D_Vertex_R_Aluminium[ind]->Add(Empty.MnvH1D_Vertex_R_Aluminium[ind],-1.0);
  sb_toSubtract.MnvH1D_Vertex_R_Carbon[ind]->Add(Empty.MnvH1D_Vertex_R_Carbon[ind],-1.0);
  sb_toSubtract.MnvH1D_Vertex_R_Iron[ind]->Add(Empty.MnvH1D_Vertex_R_Iron[ind],-1.0);
  sb_toSubtract.MnvH1D_Vertex_R_Lead[ind]->Add(Empty.MnvH1D_Vertex_R_Lead[ind],-1.0);
  sb_toSubtract.MnvH1D_Vertex_R_Other[ind]->Add(Empty.MnvH1D_Vertex_R_Other[ind],-1.0);


}

void Helium_3CryoRegionsSideBandTool::subtract_XSecHistograms_MCtotal(XSec_Var3band& xsec_var_Full, XSec_Var3band& xsec_var_Empty)
{
  xsec_var_Full.MnvH1D_mc_total->Add(xsec_var_Empty.MnvH1D_mc_total,-1.0);
}

void Helium_3CryoRegionsSideBandTool::subtract_XSecHistograms_datatotal(XSec_Var3band& xsec_var_Full, XSec_Var3band& xsec_var_Empty)
{
  xsec_var_Full.MnvH1D_data->Add(xsec_var_Empty.MnvH1D_data,-1.0);
}



void Helium_3CryoRegionsSideBandTool::subtract_XSecHistograms_MC_Material(XSec_Var3band& xsec_var_Full,
  XSec_Var3band& xsec_var_Empty , int ind)
  {
    xsec_var_Full.MnvH1D_Helium[ind]->Add(xsec_var_Empty.MnvH1D_Helium[ind],-1);
    xsec_var_Full.MnvH1D_Aluminium[ind]->Add(xsec_var_Empty.MnvH1D_Aluminium[ind],-1);
    xsec_var_Full.MnvH1D_Lead[ind]->Add(xsec_var_Empty.MnvH1D_Lead[ind],-1);
    xsec_var_Full.MnvH1D_Carbon[ind]->Add(xsec_var_Empty.MnvH1D_Carbon[ind],-1);
    xsec_var_Full.MnvH1D_Iron[ind]->Add(xsec_var_Empty.MnvH1D_Iron[ind],-1);
    xsec_var_Full.MnvH1D_Other[ind]->Add(xsec_var_Empty.MnvH1D_Other[ind],-1);
  }

void Helium_3CryoRegionsSideBandTool::init_subtract_XSecHistograms(XSec_Var3band& xsec_var_Full, XSec_Var3band& xsec_var_Empty){

  subtract_XSecHistograms_MCtotal( xsec_var_Full, xsec_var_Empty);
  subtract_XSecHistograms_datatotal(xsec_var_Full, xsec_var_Empty);
  subtract_XSecHistograms_MC_Material(xsec_var_Full, xsec_var_Empty , 0);
}





  void Helium_3CryoRegionsSideBandTool::init_Hist_Full_minus_Empty(){

    subtract_Data_total(  Full_Empty, Empty);
    subtract_MC_total(    Full_Empty, Empty);
    subtract_MC_Material( Full_Empty, Empty, 0);

    subtract_Data_total(  Full_Empty_UpstreamCap, Empty_UpstreamCap);
    subtract_MC_total(    Full_Empty_UpstreamCap, Empty_UpstreamCap);
    subtract_MC_Material( Full_Empty_UpstreamCap, Empty_UpstreamCap, 0);

    subtract_Data_total( Full_Empty_Barrel,  Empty_Barrel);
    subtract_MC_total(   Full_Empty_Barrel,  Empty_Barrel);
    subtract_MC_Material(Full_Empty_Barrel,  Empty_Barrel, 0);

    subtract_Data_total( Full_Empty_DownstreamCap,  Empty_DownstreamCap);
    subtract_MC_total(   Full_Empty_DownstreamCap,  Empty_DownstreamCap);
    subtract_MC_Material(Full_Empty_DownstreamCap,  Empty_DownstreamCap, 0);

    subtract_Data_total( Full_Empty_DownstreamConcaveCap,  Empty_DownstreamConcaveCap);
    subtract_MC_total(   Full_Empty_DownstreamConcaveCap,  Empty_DownstreamConcaveCap);
    subtract_MC_Material(Full_Empty_DownstreamConcaveCap,  Empty_DownstreamConcaveCap, 0);

    init_subtract_XSecHistograms(Full_Empty.muon_PT,        Empty.muon_PT);
    init_subtract_XSecHistograms(Full_Empty.muon_PZ,        Empty.muon_PZ);
    init_subtract_XSecHistograms(Full_Empty.muon_theta,     Empty.muon_theta);
    init_subtract_XSecHistograms(Full_Empty.muon_E,         Empty.muon_E);
    init_subtract_XSecHistograms(Full_Empty.muon_doca,      Empty.muon_doca);
    init_subtract_XSecHistograms(Full_Empty.DistancetoEdge, Empty.DistancetoEdge);
    init_subtract_XSecHistograms(Full_Empty.SecTrk_doca,    Empty.SecTrk_doca);
    init_subtract_XSecHistograms(Full_Empty.TrackLength,    Empty.TrackLength);
    init_subtract_XSecHistograms(Full_Empty.DistancetoUpstreamCap ,        Empty.DistancetoUpstreamCap);
    init_subtract_XSecHistograms(Full_Empty.DistancetoDownstreamCap ,      Empty.DistancetoDownstreamCap);
    init_subtract_XSecHistograms(Full_Empty.DistancetoUpstreamCap_RCut,    Empty.DistancetoUpstreamCap_RCut);
    init_subtract_XSecHistograms(Full_Empty.DistancetoDownstreamCap_RCut , Empty.DistancetoDownstreamCap_RCut);
    init_subtract_XSecHistograms(Full_Empty.Vertex_Z_RCut ,                Empty.Vertex_Z_RCut);
    init_subtract_XSecHistograms(Full_Empty.Vertex_X_RCut ,                Empty.Vertex_X_RCut);
    init_subtract_XSecHistograms(Full_Empty.Vertex_Y_RCut ,                Empty.Vertex_Y_RCut);
    init_subtract_XSecHistograms(Full_Empty.Vertex_R_RCut ,                Empty.Vertex_R_RCut);

    init_subtract_XSecHistograms(Full_Empty_UpstreamCap.muon_PT,        Empty_UpstreamCap.muon_PT);
    init_subtract_XSecHistograms(Full_Empty_UpstreamCap.muon_PZ,        Empty_UpstreamCap.muon_PZ);
    init_subtract_XSecHistograms(Full_Empty_UpstreamCap.muon_theta,     Empty_UpstreamCap.muon_theta);
    init_subtract_XSecHistograms(Full_Empty_UpstreamCap.muon_E,         Empty_UpstreamCap.muon_E);
    init_subtract_XSecHistograms(Full_Empty_UpstreamCap.muon_doca,      Empty_UpstreamCap.muon_doca);
    init_subtract_XSecHistograms(Full_Empty_UpstreamCap.DistancetoEdge, Empty_UpstreamCap.DistancetoEdge);
    init_subtract_XSecHistograms(Full_Empty_UpstreamCap.SecTrk_doca,    Empty_UpstreamCap.SecTrk_doca);
    init_subtract_XSecHistograms(Full_Empty_UpstreamCap.TrackLength,    Empty_UpstreamCap.TrackLength);
    init_subtract_XSecHistograms(Full_Empty_UpstreamCap.DistancetoUpstreamCap,         Empty_UpstreamCap.DistancetoUpstreamCap);
    init_subtract_XSecHistograms(Full_Empty_UpstreamCap.DistancetoDownstreamCap,       Empty_UpstreamCap.DistancetoDownstreamCap);
    init_subtract_XSecHistograms(Full_Empty_UpstreamCap.DistancetoUpstreamCap_RCut,    Empty_UpstreamCap.DistancetoUpstreamCap_RCut);
    init_subtract_XSecHistograms(Full_Empty_UpstreamCap.DistancetoDownstreamCap_RCut,  Empty_UpstreamCap.DistancetoDownstreamCap_RCut);
    init_subtract_XSecHistograms(Full_Empty_UpstreamCap.Vertex_Z_RCut,                 Empty_UpstreamCap.Vertex_Z_RCut);
    init_subtract_XSecHistograms(Full_Empty_UpstreamCap.Vertex_X_RCut,                 Empty_UpstreamCap.Vertex_X_RCut);
    init_subtract_XSecHistograms(Full_Empty_UpstreamCap.Vertex_Y_RCut,                 Empty_UpstreamCap.Vertex_Y_RCut);
    init_subtract_XSecHistograms(Full_Empty_UpstreamCap.Vertex_R_RCut,                 Empty_UpstreamCap.Vertex_R_RCut);


    init_subtract_XSecHistograms(Full_Empty_Barrel.muon_PT,                       Empty_Barrel.muon_PT);
    init_subtract_XSecHistograms(Full_Empty_Barrel.muon_PZ,                       Empty_Barrel.muon_PZ);
    init_subtract_XSecHistograms(Full_Empty_Barrel.muon_theta,                    Empty_Barrel.muon_theta);
    init_subtract_XSecHistograms(Full_Empty_Barrel.muon_E,                        Empty_Barrel.muon_E);
    init_subtract_XSecHistograms(Full_Empty_Barrel.muon_doca,                     Empty_Barrel.muon_doca);
    init_subtract_XSecHistograms(Full_Empty_Barrel.DistancetoEdge,                Empty_Barrel.DistancetoEdge);
    init_subtract_XSecHistograms(Full_Empty_Barrel.SecTrk_doca,                   Empty_Barrel.SecTrk_doca);
    init_subtract_XSecHistograms(Full_Empty_Barrel.TrackLength,                   Empty_Barrel.TrackLength);
    init_subtract_XSecHistograms(Full_Empty_Barrel.DistancetoUpstreamCap,         Empty_Barrel.DistancetoUpstreamCap);
    init_subtract_XSecHistograms(Full_Empty_Barrel.DistancetoDownstreamCap,       Empty_Barrel.DistancetoDownstreamCap);
    init_subtract_XSecHistograms(Full_Empty_Barrel.DistancetoUpstreamCap_RCut,    Empty_Barrel.DistancetoUpstreamCap_RCut);
    init_subtract_XSecHistograms(Full_Empty_Barrel.DistancetoDownstreamCap_RCut,  Empty_Barrel.DistancetoDownstreamCap_RCut);
    init_subtract_XSecHistograms(Full_Empty_Barrel.Vertex_Z_RCut,                 Empty_Barrel.Vertex_Z_RCut);
    init_subtract_XSecHistograms(Full_Empty_Barrel.Vertex_X_RCut,                 Empty_Barrel.Vertex_X_RCut);
    init_subtract_XSecHistograms(Full_Empty_Barrel.Vertex_Y_RCut,                 Empty_Barrel.Vertex_Y_RCut);
    init_subtract_XSecHistograms(Full_Empty_Barrel.Vertex_R_RCut,                 Empty_Barrel.Vertex_R_RCut);

    init_subtract_XSecHistograms(Full_Empty_DownstreamCap.muon_PT,        Empty_DownstreamCap.muon_PT);
    init_subtract_XSecHistograms(Full_Empty_DownstreamCap.muon_PZ,        Empty_DownstreamCap.muon_PZ);
    init_subtract_XSecHistograms(Full_Empty_DownstreamCap.muon_theta,     Empty_DownstreamCap.muon_theta);
    init_subtract_XSecHistograms(Full_Empty_DownstreamCap.muon_E,         Empty_DownstreamCap.muon_E);
    init_subtract_XSecHistograms(Full_Empty_DownstreamCap.muon_doca,      Empty_DownstreamCap.muon_doca);
    init_subtract_XSecHistograms(Full_Empty_DownstreamCap.DistancetoEdge, Empty_DownstreamCap.DistancetoEdge);
    init_subtract_XSecHistograms(Full_Empty_DownstreamCap.SecTrk_doca,    Empty_DownstreamCap.SecTrk_doca);
    init_subtract_XSecHistograms(Full_Empty_DownstreamCap.TrackLength,    Empty_DownstreamCap.TrackLength);
    init_subtract_XSecHistograms(Full_Empty_DownstreamCap.DistancetoUpstreamCap,         Empty_DownstreamCap.DistancetoUpstreamCap);
    init_subtract_XSecHistograms(Full_Empty_DownstreamCap.DistancetoDownstreamCap,       Empty_DownstreamCap.DistancetoDownstreamCap);
    init_subtract_XSecHistograms(Full_Empty_DownstreamCap.DistancetoUpstreamCap_RCut,    Empty_DownstreamCap.DistancetoUpstreamCap_RCut);
    init_subtract_XSecHistograms(Full_Empty_DownstreamCap.DistancetoDownstreamCap_RCut,  Empty_DownstreamCap.DistancetoDownstreamCap_RCut);
    init_subtract_XSecHistograms(Full_Empty_DownstreamCap.Vertex_Z_RCut,                 Empty_DownstreamCap.Vertex_Z_RCut);
    init_subtract_XSecHistograms(Full_Empty_DownstreamCap.Vertex_X_RCut,                 Empty_DownstreamCap.Vertex_X_RCut);
    init_subtract_XSecHistograms(Full_Empty_DownstreamCap.Vertex_Y_RCut,                 Empty_DownstreamCap.Vertex_Y_RCut);
    init_subtract_XSecHistograms(Full_Empty_DownstreamCap.Vertex_R_RCut,                 Empty_DownstreamCap.Vertex_R_RCut);



    init_subtract_XSecHistograms(Full_Empty_DownstreamConcaveCap.muon_PT,        Empty_DownstreamConcaveCap.muon_PT);
    init_subtract_XSecHistograms(Full_Empty_DownstreamConcaveCap.muon_PZ,        Empty_DownstreamConcaveCap.muon_PZ);
    init_subtract_XSecHistograms(Full_Empty_DownstreamConcaveCap.muon_theta,     Empty_DownstreamConcaveCap.muon_theta);
    init_subtract_XSecHistograms(Full_Empty_DownstreamConcaveCap.muon_E,         Empty_DownstreamConcaveCap.muon_E);
    init_subtract_XSecHistograms(Full_Empty_DownstreamConcaveCap.muon_doca,      Empty_DownstreamConcaveCap.muon_doca);
    init_subtract_XSecHistograms(Full_Empty_DownstreamConcaveCap.DistancetoEdge, Empty_DownstreamConcaveCap.DistancetoEdge);
    init_subtract_XSecHistograms(Full_Empty_DownstreamConcaveCap.SecTrk_doca,    Empty_DownstreamConcaveCap.SecTrk_doca);
    init_subtract_XSecHistograms(Full_Empty_DownstreamConcaveCap.TrackLength,    Empty_DownstreamConcaveCap.TrackLength);

    init_subtract_XSecHistograms(Full_Empty_DownstreamConcaveCap.DistancetoUpstreamCap,         Empty_DownstreamConcaveCap.DistancetoUpstreamCap);
    init_subtract_XSecHistograms(Full_Empty_DownstreamConcaveCap.DistancetoDownstreamCap,       Empty_DownstreamConcaveCap.DistancetoDownstreamCap);
    init_subtract_XSecHistograms(Full_Empty_DownstreamConcaveCap.DistancetoUpstreamCap_RCut,    Empty_DownstreamConcaveCap.DistancetoUpstreamCap_RCut);
    init_subtract_XSecHistograms(Full_Empty_DownstreamConcaveCap.DistancetoDownstreamCap_RCut,  Empty_DownstreamConcaveCap.DistancetoDownstreamCap_RCut);
    init_subtract_XSecHistograms(Full_Empty_DownstreamConcaveCap.Vertex_Z_RCut,                 Empty_DownstreamConcaveCap.Vertex_Z_RCut);
    init_subtract_XSecHistograms(Full_Empty_DownstreamConcaveCap.Vertex_X_RCut,                 Empty_DownstreamConcaveCap.Vertex_X_RCut);
    init_subtract_XSecHistograms(Full_Empty_DownstreamConcaveCap.Vertex_Y_RCut,                 Empty_DownstreamConcaveCap.Vertex_Y_RCut);
    init_subtract_XSecHistograms(Full_Empty_DownstreamConcaveCap.Vertex_R_RCut,                 Empty_DownstreamConcaveCap.Vertex_R_RCut);




  }




  void Helium_3CryoRegionsSideBandTool::GetAllUniverses(MnvH1D* mnvh1d_hist, std::vector<TH1D*> &all_universes, std::vector<std::string> &err_bands, std::vector<int> &hist_ind)
  {
      // Check for input vector
      if (!all_universes.empty()){
          std::cout<<"WARNING! input vector<TH1D*> all_universes is NOT empty"<<std::endl;
          std::cout<<"Returning without change!"<<std::endl;
          return;
      }

      // ------------------------------------------------------------------------
      // Add CV Histogram as first element -- all_universes[0]
      // ------------------------------------------------------------------------
      TH1D* cv_hist =  new TH1D(mnvh1d_hist->GetCVHistoWithStatError());
      all_universes.push_back(cv_hist);
      err_bands.push_back("CentralValue");
      hist_ind.push_back(0);

      // ------------------------------------------------------------------------
      // Add Other Universes from Error Bands
      // ------------------------------------------------------------------------
      // Get Vert Error Band Names
      std::vector<std::string> vert_err_names = mnvh1d_hist->GetVertErrorBandNames();

      // Loop over all Vertical Error Bands
      for (unsigned int i = 0; i < vert_err_names.size(); ++i){
          MnvVertErrorBand* err_band =  mnvh1d_hist->GetVertErrorBand(vert_err_names[i]);
          // Get All Histograms from it
          std::vector<TH1D*> err_hists = err_band->GetHists();
          for (unsigned int j = 0; j < err_hists.size(); ++j){
              TH1D* temp = new TH1D(*err_hists[j]);
              all_universes.push_back(temp);
              err_bands.push_back(vert_err_names[i]);
              hist_ind.push_back(j);
          }
      }

      // Get Lat Error Band Names
      std::vector<std::string> lat_err_names = mnvh1d_hist->GetLatErrorBandNames();

      // Loop over all Lateral Error Bands
      for (unsigned int i = 0; i < lat_err_names.size(); ++i){
          MnvLatErrorBand* err_band =  mnvh1d_hist->GetLatErrorBand(lat_err_names[i]);
          // Get All Histograms from it
          std::vector<TH1D*> err_hists = err_band->GetHists();
          for (unsigned int j = 0; j < err_hists.size(); ++j){
              TH1D* temp = new TH1D(*err_hists[j]);
              all_universes.push_back(temp);
              err_bands.push_back(lat_err_names[i]);
              hist_ind.push_back(j);
          }
      }
  }

  void Helium_3CryoRegionsSideBandTool::initSideBand_AllUniverses(Helium3SideBand& sb)
  {
      GetAllUniverses(sb.MnvH1D_Vertex_X_data,         sb.Vertex_X_data_all_universes,      sb.Vertex_X_err_bands_data_all_universes,      sb.Vertex_X_hist_ind_data_all_universes);
      GetAllUniverses(sb.MnvH1D_Vertex_X_mc_total,     sb.Vertex_X_mc_total_all_universes,  sb.Vertex_X_err_bands_mc_total_all_universes,  sb.Vertex_X_hist_ind_mc_total_all_universes);
      GetAllUniverses(sb.MnvH1D_Vertex_X_Helium[0],    sb.Vertex_X_Helium_all_universes,    sb.Vertex_X_err_bands_Helium_all_universes,    sb.Vertex_X_hist_ind_Helium_all_universes);
      GetAllUniverses(sb.MnvH1D_Vertex_X_Aluminium[0], sb.Vertex_X_Aluminium_all_universes, sb.Vertex_X_err_bands_Aluminium_all_universes, sb.Vertex_X_hist_ind_Aluminium_all_universes);
      GetAllUniverses(sb.MnvH1D_Vertex_X_Carbon[0],    sb.Vertex_X_Carbon_all_universes,    sb.Vertex_X_err_bands_Carbon_all_universes,    sb.Vertex_X_hist_ind_Carbon_all_universes);
      GetAllUniverses(sb.MnvH1D_Vertex_X_Iron[0],      sb.Vertex_X_Iron_all_universes,      sb.Vertex_X_err_bands_Iron_all_universes,      sb.Vertex_X_hist_ind_Iron_all_universes);
      GetAllUniverses(sb.MnvH1D_Vertex_X_Lead[0],      sb.Vertex_X_Lead_all_universes,      sb.Vertex_X_err_bands_Lead_all_universes,      sb.Vertex_X_hist_ind_Lead_all_universes);
      GetAllUniverses(sb.MnvH1D_Vertex_X_Other[0],     sb.Vertex_X_Other_all_universes,     sb.Vertex_X_err_bands_Other_all_universes,     sb.Vertex_X_hist_ind_Other_all_universes);

      GetAllUniverses(sb.MnvH1D_Vertex_Y_data,         sb.Vertex_Y_data_all_universes,      sb.Vertex_Y_err_bands_data_all_universes,      sb.Vertex_Y_hist_ind_data_all_universes);
      GetAllUniverses(sb.MnvH1D_Vertex_Y_mc_total,     sb.Vertex_Y_mc_total_all_universes,  sb.Vertex_Y_err_bands_mc_total_all_universes,  sb.Vertex_Y_hist_ind_mc_total_all_universes);
      GetAllUniverses(sb.MnvH1D_Vertex_Y_Helium[0],    sb.Vertex_Y_Helium_all_universes,    sb.Vertex_Y_err_bands_Helium_all_universes,    sb.Vertex_Y_hist_ind_Helium_all_universes);
      GetAllUniverses(sb.MnvH1D_Vertex_Y_Aluminium[0], sb.Vertex_Y_Aluminium_all_universes, sb.Vertex_Y_err_bands_Aluminium_all_universes, sb.Vertex_Y_hist_ind_Aluminium_all_universes);
      GetAllUniverses(sb.MnvH1D_Vertex_Y_Carbon[0],    sb.Vertex_Y_Carbon_all_universes,    sb.Vertex_Y_err_bands_Carbon_all_universes,    sb.Vertex_Y_hist_ind_Carbon_all_universes);
      GetAllUniverses(sb.MnvH1D_Vertex_Y_Iron[0],      sb.Vertex_Y_Iron_all_universes,      sb.Vertex_Y_err_bands_Iron_all_universes,      sb.Vertex_Y_hist_ind_Iron_all_universes);
      GetAllUniverses(sb.MnvH1D_Vertex_Y_Lead[0],      sb.Vertex_Y_Lead_all_universes,      sb.Vertex_Y_err_bands_Lead_all_universes,      sb.Vertex_Y_hist_ind_Lead_all_universes);
      GetAllUniverses(sb.MnvH1D_Vertex_Y_Other[0],     sb.Vertex_Y_Other_all_universes,     sb.Vertex_Y_err_bands_Other_all_universes,     sb.Vertex_Y_hist_ind_Other_all_universes);

      GetAllUniverses(sb.MnvH1D_Vertex_Z_data,         sb.Vertex_Z_data_all_universes,      sb.Vertex_Z_err_bands_data_all_universes,      sb.Vertex_Z_hist_ind_data_all_universes);
      GetAllUniverses(sb.MnvH1D_Vertex_Z_mc_total,     sb.Vertex_Z_mc_total_all_universes,  sb.Vertex_Z_err_bands_mc_total_all_universes,  sb.Vertex_Z_hist_ind_mc_total_all_universes);
      GetAllUniverses(sb.MnvH1D_Vertex_Z_Helium[0],    sb.Vertex_Z_Helium_all_universes,    sb.Vertex_Z_err_bands_Helium_all_universes,    sb.Vertex_Z_hist_ind_Helium_all_universes);
      GetAllUniverses(sb.MnvH1D_Vertex_Z_Aluminium[0], sb.Vertex_Z_Aluminium_all_universes, sb.Vertex_Z_err_bands_Aluminium_all_universes, sb.Vertex_Z_hist_ind_Aluminium_all_universes);
      GetAllUniverses(sb.MnvH1D_Vertex_Z_Carbon[0],    sb.Vertex_Z_Carbon_all_universes,    sb.Vertex_Z_err_bands_Carbon_all_universes,    sb.Vertex_Z_hist_ind_Carbon_all_universes);
      GetAllUniverses(sb.MnvH1D_Vertex_Z_Iron[0],      sb.Vertex_Z_Iron_all_universes,      sb.Vertex_Z_err_bands_Iron_all_universes,      sb.Vertex_Z_hist_ind_Iron_all_universes);
      GetAllUniverses(sb.MnvH1D_Vertex_Z_Lead[0],      sb.Vertex_Z_Lead_all_universes,      sb.Vertex_Z_err_bands_Lead_all_universes,      sb.Vertex_Z_hist_ind_Lead_all_universes);
      GetAllUniverses(sb.MnvH1D_Vertex_Z_Other[0],     sb.Vertex_Z_Other_all_universes,     sb.Vertex_Z_err_bands_Other_all_universes,     sb.Vertex_Z_hist_ind_Other_all_universes);

      GetAllUniverses(sb.MnvH1D_Vertex_R_data,         sb.Vertex_R_data_all_universes,      sb.Vertex_R_err_bands_data_all_universes,      sb.Vertex_R_hist_ind_data_all_universes);
      GetAllUniverses(sb.MnvH1D_Vertex_R_mc_total,     sb.Vertex_R_mc_total_all_universes,  sb.Vertex_R_err_bands_mc_total_all_universes,  sb.Vertex_R_hist_ind_mc_total_all_universes);
      GetAllUniverses(sb.MnvH1D_Vertex_R_Helium[0],    sb.Vertex_R_Helium_all_universes,    sb.Vertex_R_err_bands_Helium_all_universes,    sb.Vertex_R_hist_ind_Helium_all_universes);
      GetAllUniverses(sb.MnvH1D_Vertex_R_Aluminium[0], sb.Vertex_R_Aluminium_all_universes, sb.Vertex_R_err_bands_Aluminium_all_universes, sb.Vertex_R_hist_ind_Aluminium_all_universes);
      GetAllUniverses(sb.MnvH1D_Vertex_R_Carbon[0],    sb.Vertex_R_Carbon_all_universes,    sb.Vertex_R_err_bands_Carbon_all_universes,    sb.Vertex_R_hist_ind_Carbon_all_universes);
      GetAllUniverses(sb.MnvH1D_Vertex_R_Iron[0],      sb.Vertex_R_Iron_all_universes,      sb.Vertex_R_err_bands_Iron_all_universes,      sb.Vertex_R_hist_ind_Iron_all_universes);
      GetAllUniverses(sb.MnvH1D_Vertex_R_Lead[0],      sb.Vertex_R_Lead_all_universes,      sb.Vertex_R_err_bands_Lead_all_universes,      sb.Vertex_R_hist_ind_Lead_all_universes);
      GetAllUniverses(sb.MnvH1D_Vertex_R_Other[0],     sb.Vertex_R_Other_all_universes,     sb.Vertex_R_err_bands_Other_all_universes,     sb.Vertex_R_hist_ind_Other_all_universes);


      N_Universes = sb.Vertex_X_data_all_universes.size();
      std::cout<<"initSideBand_AllUniverses::N_Universes = "<< N_Universes<<std::endl;
  }


  double Helium_3CryoRegionsSideBandTool::calc_ChiSq(TH1D* data, TH1D* Helium, TH1D* Aluminium, TH1D* Carbon, TH1D* Lead, TH1D* Iron, TH1D* Other)
  {
      //double mc_ratio = POT_ratio;
      double mc_ratio = 1.0;
      double chi_sq = 0.0;

      for (int i = 1; i <= data->GetNbinsX(); ++i){
          // Get N(Events) in Single Bin
          double err = data->GetBinError(i);
          double nData = data->GetBinContent(i);
          if (nData == 0) continue;
          double nHelium = Helium->GetBinContent(i);
          double nAluminium = Aluminium->GetBinContent(i);
          double nCarbon = Carbon->GetBinContent(i);
          double nLead = Lead->GetBinContent(i);
          double nIron = Iron->GetBinContent(i);
          double nOther = Other->GetBinContent(i);

          // Add All MC and scale them
          double nMC_total = (nHelium + nAluminium + nCarbon + nLead + nIron  + nOther) * mc_ratio;

          double delta = pow((nData-nMC_total),2) / pow(err,2);
          chi_sq += delta;
      }
      return chi_sq;
  }
  /////////
  double Helium_3CryoRegionsSideBandTool::calc_LogChiSq(TH1D* data, TH1D* Helium, TH1D* Aluminium, TH1D* Carbon, TH1D* Lead, TH1D* Iron, TH1D* Other)
  {
      //double mc_ratio = POT_ratio;
      double mc_ratio = 1.0;
      double chi_sq = 0.0;


      for (int i = 1; i <= data->GetNbinsX(); ++i){
          // Get N(Events) in Single Bin
          double nData = data->GetBinContent(i);
          if (nData == 0) continue;
          double nHelium = Helium->GetBinContent(i);
          double nAluminium = Aluminium->GetBinContent(i);
          double nCarbon = Carbon->GetBinContent(i);
          double nLead = Lead->GetBinContent(i);
          double nIron = Iron->GetBinContent(i);
          double nOther = Other->GetBinContent(i);

          // Add All MC and scale them
          double nMC_total = (nHelium + nAluminium + nCarbon + nLead + nIron  + nOther) * mc_ratio;
          if (nMC_total <= 0) continue;
          double c = nData * log(nMC_total);
          double delta = 2 * (nMC_total - c);
          chi_sq += delta;
      }

      return chi_sq;
  }
///////////////////////////////////////////////////////////////////////////////
double Helium_3CryoRegionsSideBandTool::calc_ChiSq(TH1D* data, TH1D* Helium_upstream,
  TH1D* Helium_barrel, TH1D* Helium_downstream,TH1D* Helium_downstreamconcave, TH1D* Aluminium_upstream,
  TH1D* Aluminium_barrel, TH1D* Aluminium_downstream,TH1D* Aluminium_downstreamconcave,
  TH1D* Carbon, TH1D* Lead, TH1D* Iron, TH1D* Other)
{
    //double mc_ratio = POT_ratio;
    double mc_ratio = 1.0;
    double chi_sq = 0.0;

    for (int i = 1; i <= data->GetNbinsX(); ++i){
        // Get N(Events) in Single Bin
        double err = data->GetBinError(i);
        double nData = data->GetBinContent(i);
        if (nData == 0) continue;
        double nHelium_upstream = Helium_upstream->GetBinContent(i);
        double nHelium_barrel = Helium_barrel->GetBinContent(i);
        double nHelium_downstream = Helium_downstream->GetBinContent(i);
        double nHelium_downstreamconcave = Helium_downstreamconcave->GetBinContent(i);

        double nAluminium_upstream = Aluminium_upstream->GetBinContent(i);
        double nAluminium_barrel = Aluminium_barrel->GetBinContent(i);
        double nAluminium_downstream = Aluminium_downstream->GetBinContent(i);
        double nAluminium_downstreamconcave = Aluminium_downstreamconcave->GetBinContent(i);

        double nCarbon = Carbon->GetBinContent(i);
        double nLead = Lead->GetBinContent(i);
        double nIron = Iron->GetBinContent(i);
        double nOther = Other->GetBinContent(i);

        // Add All MC and scale them
        double nMC_total = (nHelium_upstream +  nHelium_barrel + nHelium_downstream +
          nHelium_downstreamconcave + nAluminium_upstream + nAluminium_barrel + nAluminium_downstream +
           nAluminium_downstreamconcave  + nCarbon + nLead + nIron  + nOther) * mc_ratio;

        double delta = pow((nData-nMC_total),2) / pow(err,2);
        chi_sq += delta;
    }
    return chi_sq;
}

double Helium_3CryoRegionsSideBandTool::calc_LogChiSq(TH1D* data, TH1D* Helium_upstream,
  TH1D* Helium_barrel, TH1D* Helium_downstream,TH1D* Helium_downstreamconcave, TH1D* Aluminium_upstream,
  TH1D* Aluminium_barrel, TH1D* Aluminium_downstream,TH1D* Aluminium_downstreamconcave,
  TH1D* Carbon, TH1D* Lead, TH1D* Iron, TH1D* Other)
{
    //double mc_ratio = POT_ratio;
    double mc_ratio = 1.0;
    double chi_sq = 0.0;

    for (int i = 1; i <= data->GetNbinsX(); ++i){
        // Get N(Events) in Single Bin
        double nData = data->GetBinContent(i);
        if (nData == 0) continue;
        double nHelium_upstream = Helium_upstream->GetBinContent(i);
        double nHelium_barrel = Helium_barrel->GetBinContent(i);
        double nHelium_downstream = Helium_downstream->GetBinContent(i);
        double nHelium_downstreamconcave = Helium_downstreamconcave->GetBinContent(i);

        double nAluminium_upstream = Aluminium_upstream->GetBinContent(i);
        double nAluminium_barrel = Aluminium_barrel->GetBinContent(i);
        double nAluminium_downstream = Aluminium_downstream->GetBinContent(i);
        double nAluminium_downstreamconcave = Aluminium_downstreamconcave->GetBinContent(i);

        double nCarbon = Carbon->GetBinContent(i);
        double nLead = Lead->GetBinContent(i);
        double nIron = Iron->GetBinContent(i);
        double nOther = Other->GetBinContent(i);

        // Add All MC and scale them
        double nMC_total = (nHelium_upstream +  nHelium_barrel + nHelium_downstream +
          nHelium_downstreamconcave + nAluminium_upstream + nAluminium_barrel + nAluminium_downstream +
           nAluminium_downstreamconcave  + nCarbon + nLead + nIron  + nOther) * mc_ratio;
           if (nMC_total <= 0) continue;
           double c = nData * log(nMC_total);
           double delta = 2 * (nMC_total - c);
        chi_sq += delta;
    }

    return chi_sq;
}
double Helium_3CryoRegionsSideBandTool::calc_ChiSq(
  CryoRegion_HistMap Data_Map,
  CryoRegion_HistMap Helium_Map,
  CryoRegion_HistMap Al_Map,
  CryoRegion_HistMap Other_Map)
{
  std::cout<<"Inside::calc_ChiSq"<<std::endl;

if( Data_Map.size() != Helium_Map.size() || Data_Map.size() != Al_Map.size() || Data_Map.size() != Other_Map.size()){std::cout<<"Maps are different sizes for ChiSqt: Somethings WRONG!! "<<std::endl; assert(false); }

    //double mc_ratio = POT_ratio;
    double mc_ratio = 1.0;
    double chi_sq = 0.0;
    int NBins = Data_Map.begin()->second->GetNbinsX();

    double err = 0.0;
    double nData = 0.0;

    double nHelium = 0.0;
    double nOther = 0.0;
    double nAluminium = 0.0;

    for (int i = 1; i <= NBins; ++i){
        // Get N(Events) in Single Bin
      //  std::cout<<" ~~~~~~~~~~~~~~"<< std::endl;
        //std::cout<<" Bin(i) "<< i << std::endl;
        //  std::cout<<" ~~~~~~~~~~~~~~"<< std::endl;
        err = 0.0;
        nData = 0.0;

        nHelium = 0.0;
        nOther = 0.0;
        nAluminium = 0.0;



        for(auto Regions : CryoRegion14_vector){
          //std::cout<<" Regions: "<<  GetRegionString( Regions) << std::endl;
         //double nData_current =
           err += Data_Map[Regions]->GetBinError(i);
           nData += Data_Map[Regions]->GetBinContent(i);

           nHelium += Helium_Map[Regions]->GetBinContent(i);
           nAluminium += Al_Map[Regions]->GetBinContent(i);
           nOther += Other_Map[Regions]->GetBinContent(i);

           //std::cout<< "err = " <<  err << std::endl;
           //std::cout<< "nData = " <<  nData << std::endl;
           //std::cout<< "nHelium = " <<  nHelium << std::endl;
           //std::cout<< "nAluminium = " << nAluminium << std::endl;
           //std::cout<< "nOther = " <<  nOther << std::endl;
         }

         if (nData == 0) continue;

      double nMC_total = (nHelium + nAluminium  + nOther);

      double delta = pow((nData-nMC_total),2) / nData ;//pow(err,2);

      if (isnan(delta)==true) {
        std::cout<<"nMC_total = "<< nMC_total << std::endl;
        std::cout<< "err = " <<  err << std::endl;
        std::cout<< "nData = " <<  nData << std::endl;
        std::cout<< "nHelium = " <<  nHelium << std::endl;
        std::cout<< "nAluminium = " << nAluminium << std::endl;
        std::cout<< "nOther = " <<  nOther << std::endl;
        std::cout<<"delta = "<< delta << std::endl;
          continue;
      }

      chi_sq += delta;
    }

    return chi_sq;
  }
/////////
double Helium_3CryoRegionsSideBandTool::calc_ChiSq_Log(
  CryoRegion_HistMap Data_Map,
  CryoRegion_HistMap Helium_Map,
  CryoRegion_HistMap Al_Map,
  CryoRegion_HistMap Other_Map)
{


if( Data_Map.size() != Helium_Map.size() || Data_Map.size() != Al_Map.size() || Data_Map.size() != Other_Map.size()){std::cout<<"Maps are different sizes for ChiSqt: Somethings WRONG!! "<<std::endl; assert(false); }

    //double mc_ratio = POT_ratio;
    double mc_ratio = 1.0;
    double chi_sq = 0.0;
    int NBins = Data_Map.begin()->second->GetNbinsX();

    double err = 0.0;
    double nData = 0.0;
    double nHelium = 0.0;
    double nOther = 0.0;
    double nAluminium = 0.0;

    for (int i = 1; i <= NBins; ++i){
        // Get N(Events) in Single Bin

        err = 0.0;
        nData = 0.0;
        nHelium = 0.0;
        nOther = 0.0;
        nAluminium = 0.0;

        for(auto Regions: CryoRegion14_vector){
         err += Data_Map[Regions]->GetBinError(i);
         nData += Data_Map[Regions]->GetBinContent(i);
         nHelium += Helium_Map[Regions]->GetBinContent(i);
         nAluminium += Al_Map[Regions]->GetBinContent(i);
         nOther += Other_Map[Regions]->GetBinContent(i);
       }
       if (nData == 0) continue;

        double nMC_total = (nHelium + nAluminium  + nOther);
        if (nMC_total <= 0) continue;
        double c = nData * log(nMC_total);
        double delta = 2 * (nMC_total - c);


        chi_sq += delta;
      }
      return chi_sq;
    }
///////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////

double Helium_3CryoRegionsSideBandTool::calc_ChiSq_SideBand_Vertex_X(Helium3SideBand &sb, double POT_ratio, int unv, bool isPartial, int min_bin, int max_bin)
{
    if (!isPartial){
        min_bin = 1;
        max_bin = sb.MnvH1D_Vertex_X_data->GetNbinsX();
    }

    if (min_bin == max_bin){
        std::cout<<"Wrong Range for Fit"<<std::endl;
        exit(EXIT_FAILURE);
    }

    double ChiSq = 0.0;

    for (int i = 1; i <= max_bin; ++i) {
        double nData = sb.Vertex_X_data_all_universes[unv]->GetBinContent(i);
        if (nData == 0) continue;

        // Do not use Signal and Other in Fit
        double nHelium    = sb.Vertex_X_Helium_all_universes[unv]->GetBinContent(i) * POT_ratio;
        double nAluminium = sb.Vertex_X_Aluminium_all_universes[unv]->GetBinContent(i) * POT_ratio;
        double nCarbon    = sb.Vertex_X_Carbon_all_universes[unv]->GetBinContent(i) * POT_ratio;
        double nIron      = sb.Vertex_X_Iron_all_universes[unv]->GetBinContent(i) * POT_ratio;
        double nLead      = sb.Vertex_X_Lead_all_universes[unv]->GetBinContent(i) * POT_ratio;
        double nOther     = sb.Vertex_X_Other_all_universes[unv]->GetBinContent(i) * POT_ratio;

        double nTotalMC = nHelium + nAluminium + nCarbon + nIron + nLead + nOther;

        double delta  = std::pow((nData - nTotalMC),2)/nData;
        ChiSq += delta;
    }

    return ChiSq;
}

double Helium_3CryoRegionsSideBandTool::calc_ChiSq_SideBand_Vertex_Y(Helium3SideBand &sb, double POT_ratio, int unv, bool isPartial, int min_bin, int max_bin)
{
    if (!isPartial){
        min_bin = 1;
        max_bin = sb.MnvH1D_Vertex_Y_data->GetNbinsX();
    }

    if (min_bin == max_bin){
        std::cout<<"Wrong Range for Fit"<<std::endl;
        exit(EXIT_FAILURE);
    }

    double ChiSq = 0.0;

    for (int i = 1; i <= max_bin; ++i) {
        double nData = sb.Vertex_Y_data_all_universes[unv]->GetBinContent(i);
        if (nData == 0) continue;

        // Do not use Signal and Other in Fit
        double nHelium    = sb.Vertex_Y_Helium_all_universes[unv]->GetBinContent(i) * POT_ratio;
        double nAluminium = sb.Vertex_Y_Aluminium_all_universes[unv]->GetBinContent(i) * POT_ratio;
        double nCarbon    = sb.Vertex_Y_Carbon_all_universes[unv]->GetBinContent(i) * POT_ratio;
        double nIron      = sb.Vertex_Y_Iron_all_universes[unv]->GetBinContent(i) * POT_ratio;
        double nLead      = sb.Vertex_Y_Lead_all_universes[unv]->GetBinContent(i) * POT_ratio;
        double nOther     = sb.Vertex_Y_Other_all_universes[unv]->GetBinContent(i) * POT_ratio;

        double nTotalMC = nHelium + nAluminium + nCarbon + nIron + nLead + nOther;

        double delta  = std::pow((nData - nTotalMC),2)/nData;
        ChiSq += delta;
    }

    return ChiSq;
}


double Helium_3CryoRegionsSideBandTool::calc_ChiSq_SideBand_Vertex_Z(Helium3SideBand &sb, double POT_ratio, int unv, bool isPartial, int min_bin, int max_bin)
{
    if (!isPartial){
        min_bin = 1;
        max_bin = sb.MnvH1D_Vertex_Z_data->GetNbinsX();
    }

    if (min_bin == max_bin){
        std::cout<<"Wrong Range for Fit"<<std::endl;
        exit(EXIT_FAILURE);
    }

    double ChiSq = 0.0;

    for (int i = 1; i <= max_bin; ++i) {
        double nData = sb.Vertex_Z_data_all_universes[unv]->GetBinContent(i);
        if (nData == 0) continue;

        // Do not use Signal and Other in Fit
        double nHelium    = sb.Vertex_Z_Helium_all_universes[unv]->GetBinContent(i) * POT_ratio;
        double nAluminium = sb.Vertex_Z_Aluminium_all_universes[unv]->GetBinContent(i) * POT_ratio;
        double nCarbon    = sb.Vertex_Z_Carbon_all_universes[unv]->GetBinContent(i) * POT_ratio;
        double nIron      = sb.Vertex_Z_Iron_all_universes[unv]->GetBinContent(i) * POT_ratio;
        double nLead      = sb.Vertex_Z_Lead_all_universes[unv]->GetBinContent(i) * POT_ratio;
        double nOther     = sb.Vertex_Z_Other_all_universes[unv]->GetBinContent(i) * POT_ratio;

        double nTotalMC = nHelium + nAluminium + nCarbon + nIron + nLead + nOther;

        double delta  = std::pow((nData - nTotalMC),2)/nData;
        ChiSq += delta;
    }

    return ChiSq;
}

double Helium_3CryoRegionsSideBandTool::calc_ChiSq_SideBand_Vertex_R(Helium3SideBand &sb, double POT_ratio, int unv, bool isPartial, int min_bin, int max_bin)
{
    if (!isPartial){
        min_bin = 1;
        max_bin = sb.MnvH1D_Vertex_R_data->GetNbinsX();
    }

    if (min_bin == max_bin){
        std::cout<<"Wrong Range for Fit"<<std::endl;
        exit(EXIT_FAILURE);
    }

    double ChiSq = 0.0;

    for (int i = 1; i <= max_bin; ++i) {
        double nData = sb.Vertex_R_data_all_universes[unv]->GetBinContent(i);
        if (nData == 0) continue;

        // Do not use Signal and Other in Fit
        double nHelium    = sb.Vertex_R_Helium_all_universes[unv]->GetBinContent(i) * POT_ratio;
        double nAluminium = sb.Vertex_R_Aluminium_all_universes[unv]->GetBinContent(i) * POT_ratio;
        double nCarbon    = sb.Vertex_R_Carbon_all_universes[unv]->GetBinContent(i) * POT_ratio;
        double nIron      = sb.Vertex_R_Iron_all_universes[unv]->GetBinContent(i) * POT_ratio;
        double nLead      = sb.Vertex_R_Lead_all_universes[unv]->GetBinContent(i) * POT_ratio;
        double nOther     = sb.Vertex_R_Other_all_universes[unv]->GetBinContent(i) * POT_ratio;

        double nTotalMC = nHelium + nAluminium + nCarbon + nIron + nLead + nOther;

        double delta  = std::pow((nData - nTotalMC),2)/nData;
        ChiSq += delta;
    }

    return ChiSq;
}

////////////////////////////////////////////////////////////////////////////////

void Helium_3CryoRegionsSideBandTool::SetNames(Helium3SideBand &sb, std::string name)
{
    sb.name = name;
    sb.model_names[0] = "Helium";
    sb.model_names[1] = "Aluminium";
    sb.model_names[2] = "Carbon";
    sb.model_names[3] = "Iron";
    sb.model_names[4] = "Lead";
    sb.model_names[4] = "Other";
    sb.model_names[6] = "Total";
}

void Helium_3CryoRegionsSideBandTool::GetStatistics_Vertex_X(Helium3SideBand &sb)
{
    //int first_bin = 1; //don't include overflow
    //int last_bin = sb.nData->GetNbinsX() ;
std::cout<<"inside::GetStatistics vertex X "<<std::endl;
std::cout<<"sb.data_all_universes.size() = " << sb.Vertex_X_data_all_universes.size()<<std::endl;


    for (unsigned int i = 0; i < sb.Vertex_X_data_all_universes.size(); ++i){
        sb.Vertex_X_nData.push_back(sb.Vertex_X_data_all_universes[i]->Integral());//first_bin, last_bin));
        sb.Vertex_X_nMC.push_back(sb.Vertex_X_mc_total_all_universes[i]->Integral());//first_bin, last_bin));

        sb.Vertex_X_nHelium.push_back(sb.Vertex_X_Helium_all_universes[i]->Integral());//first_bin, last_bin));
        sb.Vertex_X_nAluminium.push_back(sb.Vertex_X_Aluminium_all_universes[i]->Integral());//first_bin, last_bin));
        sb.Vertex_X_nCarbon.push_back(sb.Vertex_X_Carbon_all_universes[i]->Integral());//first_bin, last_bin));
        sb.Vertex_X_nIron.push_back(sb.Vertex_X_Iron_all_universes[i]->Integral());//first_bin, last_bin));
        sb.Vertex_X_nLead.push_back(sb.Vertex_X_Lead_all_universes[i]->Integral());//first_bin, last_bin));
        sb.Vertex_X_nOther.push_back(sb.Vertex_X_Other_all_universes[i]->Integral());//first_bin, last_bin));
    }
}

void Helium_3CryoRegionsSideBandTool::GetStatistics_Vertex_Y(Helium3SideBand &sb)
{
    //int first_bin = 1; //don't include overflow
    //int last_bin = sb.nData->GetNbinsX() ;
std::cout<<"inside::GetStatistics Vertex Y"<<std::endl;
std::cout<<"sb.data_all_universes.size() = " << sb.Vertex_Y_data_all_universes.size()<<std::endl;


    for (unsigned int i = 0; i < sb.Vertex_Y_data_all_universes.size(); ++i){
        sb.Vertex_Y_nData.push_back(sb.Vertex_Y_data_all_universes[i]->Integral());//first_bin, last_bin));
        sb.Vertex_Y_nMC.push_back(sb.Vertex_Y_mc_total_all_universes[i]->Integral());//first_bin, last_bin));

        sb.Vertex_Y_nHelium.push_back(sb.Vertex_Y_Helium_all_universes[i]->Integral());//first_bin, last_bin));
        sb.Vertex_Y_nAluminium.push_back(sb.Vertex_Y_Aluminium_all_universes[i]->Integral());//first_bin, last_bin));
        sb.Vertex_Y_nCarbon.push_back(sb.Vertex_Y_Carbon_all_universes[i]->Integral());//first_bin, last_bin));
        sb.Vertex_Y_nIron.push_back(sb.Vertex_Y_Iron_all_universes[i]->Integral());//first_bin, last_bin));
        sb.Vertex_Y_nLead.push_back(sb.Vertex_Y_Lead_all_universes[i]->Integral());//first_bin, last_bin));
        sb.Vertex_Y_nOther.push_back(sb.Vertex_Y_Other_all_universes[i]->Integral());//first_bin, last_bin));
    }
}

void Helium_3CryoRegionsSideBandTool::GetStatistics_Vertex_Z(Helium3SideBand &sb)
{
    //int first_bin = 1; //don't include overflow
    //int last_bin = sb.nData->GetNbinsX() ;
std::cout<<"inside::GetStatistics vertex Z "<<std::endl;
std::cout<<"sb.data_all_universes.size() = " << sb.Vertex_Z_data_all_universes.size()<<std::endl;


    for (unsigned int i = 0; i < sb.Vertex_Z_data_all_universes.size(); ++i){
        sb.Vertex_Z_nData.push_back(sb.Vertex_Z_data_all_universes[i]->Integral());//first_bin, last_bin));
        sb.Vertex_Z_nMC.push_back(sb.Vertex_Z_mc_total_all_universes[i]->Integral());//first_bin, last_bin));

        sb.Vertex_Z_nHelium.push_back(sb.Vertex_Z_Helium_all_universes[i]->Integral());//first_bin, last_bin));
        sb.Vertex_Z_nAluminium.push_back(sb.Vertex_Z_Aluminium_all_universes[i]->Integral());//first_bin, last_bin));
        sb.Vertex_Z_nCarbon.push_back(sb.Vertex_Z_Carbon_all_universes[i]->Integral());//first_bin, last_bin));
        sb.Vertex_Z_nIron.push_back(sb.Vertex_Z_Iron_all_universes[i]->Integral());//first_bin, last_bin));
        sb.Vertex_Z_nLead.push_back(sb.Vertex_Z_Lead_all_universes[i]->Integral());//first_bin, last_bin));
        sb.Vertex_Z_nOther.push_back(sb.Vertex_Z_Other_all_universes[i]->Integral());//first_bin, last_bin));
    }
}


void Helium_3CryoRegionsSideBandTool::GetStatistics_Vertex_R(Helium3SideBand &sb)
{
    //int first_bin = 1; //don't include overflow
    //int last_bin = sb.nData->GetNbinsX() ;
std::cout<<"inside::GetStatistics vertex R "<<std::endl;
std::cout<<"sb.data_all_universes.size() = " << sb.Vertex_R_data_all_universes.size()<<std::endl;


    for (unsigned int i = 0; i < sb.Vertex_R_data_all_universes.size(); ++i){
        sb.Vertex_R_nData.push_back(sb.Vertex_R_data_all_universes[i]->Integral());//first_bin, last_bin));
        sb.Vertex_R_nMC.push_back(sb.Vertex_R_mc_total_all_universes[i]->Integral());//first_bin, last_bin));

        sb.Vertex_R_nHelium.push_back(sb.Vertex_R_Helium_all_universes[i]->Integral());//first_bin, last_bin));
        sb.Vertex_R_nAluminium.push_back(sb.Vertex_R_Aluminium_all_universes[i]->Integral());//first_bin, last_bin));
        sb.Vertex_R_nCarbon.push_back(sb.Vertex_R_Carbon_all_universes[i]->Integral());//first_bin, last_bin));
        sb.Vertex_R_nIron.push_back(sb.Vertex_R_Iron_all_universes[i]->Integral());//first_bin, last_bin));
        sb.Vertex_R_nLead.push_back(sb.Vertex_R_Lead_all_universes[i]->Integral());//first_bin, last_bin));
        sb.Vertex_R_nOther.push_back(sb.Vertex_R_Other_all_universes[i]->Integral());//first_bin, last_bin));
    }
}
void Helium_3CryoRegionsSideBandTool::GetStatistics(Helium3SideBand &sb){

GetStatistics_Vertex_X(sb);
GetStatistics_Vertex_Y(sb);
GetStatistics_Vertex_Z(sb);

}

void Helium_3CryoRegionsSideBandTool::MakeLatexChiSqrt_table(std::string output_name, std::string CryoTank_status,
  std::vector<std::string> VectorName,
  std::vector<double> Chisqt_Before,
  std::vector<double> Chisqt_After,
  std::vector<double> NDF, double scale
){


std::cout<<"inside::MakeLatexChiSqrt_table"<<std::endl;
std::cout<<"VectorName.size() = " << VectorName.size()<<std::endl;
std::cout<<"Chisqt_Before.size() = " << Chisqt_Before.size()<<std::endl;
std::cout<<"Chisqt_After.size() = " << Chisqt_After.size()<<std::endl;





  std::ofstream myfile;
  std::string fileName = output_name + ".txt";
  std::cout<<" File name  = "<<  fileName << std::endl;
  myfile.open(fileName, std::ios_base::out);

  std::cout<<"Adding to Latex File "<< fileName<<std::endl;
  LatexFormat Latex_output(scale);
  myfile<<"\n";
  myfile<<"\n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<"%%%  Start: " << CryoTank_status<<  " Chi Sqrt table   \n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<Latex_output.ChiSqrt_table_LatexString(
     VectorName,
     Chisqt_Before,
     Chisqt_After,
     NDF,
    output_name )<<"\n";
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% END FRAME  \n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile.close();

}

void Helium_3CryoRegionsSideBandTool::MakeLatexChiSqrt_table_new(std::string output_name, std::string CryoTank_status,
  std::vector<std::string> VectorName,
  std::vector<double> Chisqt_Before,
  std::vector<double> Chisqt_shifted,
  std::vector<double> Chisqt_shifted_weighted,
  std::vector<double> NDF, double scale
){


std::cout<<"inside::MakeLatexChiSqrt_table"<<std::endl;
std::cout<<"VectorName.size() = " << VectorName.size()<<std::endl;
std::cout<<"Chisqt_Before.size() = " << Chisqt_Before.size()<<std::endl;
std::cout<<"Chisqt_shifted.size() = " << Chisqt_shifted.size()<<std::endl;
std::cout<<"Chisqt_shifted_weighted.size() = " << Chisqt_shifted_weighted.size()<<std::endl;




  std::ofstream myfile;
  std::string fileName = output_name + ".txt";
  std::cout<<" File name  = "<<  fileName << std::endl;
  myfile.open(fileName, std::ios_base::out);

  std::cout<<"Adding to Latex File "<< fileName<<std::endl;
  LatexFormat Latex_output(scale);
  myfile<<"\n";
  myfile<<"\n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<"%%%  Start: " << CryoTank_status<<  " Chi Sqrt table   \n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<Latex_output.ChiSqrt_table_LatexString_shifted_weighted(
     VectorName,
     Chisqt_Before,
     Chisqt_shifted,
     Chisqt_shifted_weighted,
     NDF)<<"\n";
    myfile<<"\n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile<<"%%% END FRAME  \n";
    myfile<<"%%%%%%%%%%%%%%%%% \n";
    myfile.close();

}



void Helium_3CryoRegionsSideBandTool::WriteBeforeChi(std::string FileName){
std::vector<double> before_Empty;
std::vector<double> before_Full;
std::vector<double> before_Full_Empty;

before_Full.push_back(ChiSqrt_beforeCryoVertex_FullMap[kX]);
before_Full.push_back(ChiSqrt_beforeCryoVertex_FullMap[kY]);
before_Full.push_back(ChiSqrt_beforeCryoVertex_FullMap[kZ]);
before_Full.push_back(ChiSqrt_beforeCryoVertex_FullMap[kR]);
before_Full.push_back(ChiSqrt_beforeCryoVertex_FullMap[kdistance_edge]);
before_Full.push_back(ChiSqrt_beforeMuonVar_FullMap[kP_T]);
before_Full.push_back(ChiSqrt_beforeMuonVar_FullMap[kP_Z]);
before_Full.push_back(ChiSqrt_beforeMuonVar_FullMap[kE]);
before_Full.push_back(ChiSqrt_beforeMuonVar_FullMap[kAngleWRTB]);
before_Full.push_back(ChiSqrt_beforeMuonVar_FullMap[kDOCA_muon]);
before_Full.push_back(ChiSqrt_beforeCryoVertex_FullMap[krecoil_DOCA]);
before_Full.push_back(ChiSqrt_beforeCryoVertex_FullMap[krecoil_tracklength_minerva]);
before_Full.push_back(ChiSqrt_beforeCryoVertex_FullMap[kdistance_downstreamcap]);
before_Full.push_back(ChiSqrt_beforeCryoVertex_FullMap[kdistance_downstreamcap_RCut]);
before_Full.push_back(ChiSqrt_beforeCryoVertex_FullMap[kdistance_upstreamcap]);
before_Full.push_back(ChiSqrt_beforeCryoVertex_FullMap[kdistance_upstreamcap_RCut]);
before_Full.push_back(ChiSqrt_beforeCryoVertex_FullMap[kZ_RCut]);
before_Full.push_back(ChiSqrt_beforeCryoVertex_FullMap[kX_RCut]);
before_Full.push_back(ChiSqrt_beforeCryoVertex_FullMap[kY_RCut]);
before_Full.push_back(ChiSqrt_beforeCryoVertex_FullMap[kR_RCut]);




before_Empty.push_back(ChiSqrt_beforeCryoVertex_EmptyMap[kX]);
before_Empty.push_back(ChiSqrt_beforeCryoVertex_EmptyMap[kY]);
before_Empty.push_back(ChiSqrt_beforeCryoVertex_EmptyMap[kZ]);
before_Empty.push_back(ChiSqrt_beforeCryoVertex_EmptyMap[kR]);
before_Empty.push_back(ChiSqrt_beforeCryoVertex_EmptyMap[kdistance_edge]);
before_Empty.push_back(ChiSqrt_beforeMuonVar_EmptyMap[kP_T]);
before_Empty.push_back(ChiSqrt_beforeMuonVar_EmptyMap[kP_Z]);
before_Empty.push_back(ChiSqrt_beforeMuonVar_EmptyMap[kE]);
before_Empty.push_back(ChiSqrt_beforeMuonVar_EmptyMap[kAngleWRTB]);
before_Empty.push_back(ChiSqrt_beforeMuonVar_EmptyMap[kDOCA_muon]);
before_Empty.push_back(ChiSqrt_beforeCryoVertex_EmptyMap[krecoil_DOCA]);
before_Empty.push_back(ChiSqrt_beforeCryoVertex_EmptyMap[krecoil_tracklength_minerva]);
before_Empty.push_back(ChiSqrt_beforeCryoVertex_EmptyMap[kdistance_downstreamcap]);
before_Empty.push_back(ChiSqrt_beforeCryoVertex_EmptyMap[kdistance_downstreamcap_RCut]);
before_Empty.push_back(ChiSqrt_beforeCryoVertex_EmptyMap[kdistance_upstreamcap]);
before_Empty.push_back(ChiSqrt_beforeCryoVertex_EmptyMap[kdistance_upstreamcap_RCut]);
before_Empty.push_back(ChiSqrt_beforeCryoVertex_EmptyMap[kZ_RCut]);
before_Empty.push_back(ChiSqrt_beforeCryoVertex_EmptyMap[kX_RCut]);
before_Empty.push_back(ChiSqrt_beforeCryoVertex_EmptyMap[kY_RCut]);
before_Empty.push_back(ChiSqrt_beforeCryoVertex_EmptyMap[kR_RCut]);


before_Full_Empty.push_back(ChiSqrt_beforeCryoVertex_Full_EmptyMap[kX]);
before_Full_Empty.push_back(ChiSqrt_beforeCryoVertex_Full_EmptyMap[kY]);
before_Full_Empty.push_back(ChiSqrt_beforeCryoVertex_Full_EmptyMap[kZ]);
before_Full_Empty.push_back(ChiSqrt_beforeCryoVertex_Full_EmptyMap[kR]);
before_Full_Empty.push_back(ChiSqrt_beforeCryoVertex_Full_EmptyMap[kdistance_edge]);
before_Full_Empty.push_back(ChiSqrt_beforeMuonVar_Full_EmptyMap[kP_T]);
before_Full_Empty.push_back(ChiSqrt_beforeMuonVar_Full_EmptyMap[kP_Z]);
before_Full_Empty.push_back(ChiSqrt_beforeMuonVar_Full_EmptyMap[kE]);
before_Full_Empty.push_back(ChiSqrt_beforeMuonVar_Full_EmptyMap[kAngleWRTB]);
before_Full_Empty.push_back(ChiSqrt_beforeMuonVar_Full_EmptyMap[kDOCA_muon]);
before_Full_Empty.push_back(ChiSqrt_afterCryoVertex_Full_EmptyMap[krecoil_DOCA]);
before_Full_Empty.push_back(ChiSqrt_afterCryoVertex_Full_EmptyMap[krecoil_tracklength_minerva]);
before_Full_Empty.push_back(ChiSqrt_beforeCryoVertex_Full_EmptyMap[kdistance_downstreamcap]);
before_Full_Empty.push_back(ChiSqrt_beforeCryoVertex_Full_EmptyMap[kdistance_downstreamcap_RCut]);
before_Full_Empty.push_back(ChiSqrt_beforeCryoVertex_Full_EmptyMap[kdistance_upstreamcap]);
before_Full_Empty.push_back(ChiSqrt_beforeCryoVertex_Full_EmptyMap[kdistance_upstreamcap_RCut]);
before_Full_Empty.push_back(ChiSqrt_beforeCryoVertex_Full_EmptyMap[kZ_RCut]);
before_Full_Empty.push_back(ChiSqrt_beforeCryoVertex_Full_EmptyMap[kX_RCut]);
before_Full_Empty.push_back(ChiSqrt_beforeCryoVertex_Full_EmptyMap[kY_RCut]);
before_Full_Empty.push_back(ChiSqrt_beforeCryoVertex_Full_EmptyMap[kR_RCut]);


std::string Final_Name;

Final_Name = FileName + "Empty.txt";
SaveVector_toFile(before_Empty, Final_Name);
Final_Name = FileName + "Full.txt";
SaveVector_toFile(before_Full, Final_Name);
Final_Name = FileName + "Full_Empty.txt";
SaveVector_toFile(before_Full_Empty, Final_Name);

}


void Helium_3CryoRegionsSideBandTool::Fill_ChiSqt(
  std::vector<double> &Full_Chisqt_before, std::vector<double> &Full_Chisqt_after,
  std::vector<double> &Empty_Chisqt_before, std::vector<double> &Empty_Chisqt_after,
  std::vector<double> &Full_Empty_Chisqt_before, std::vector<double> &Full_Empty_Chisqt_after)
{
std::cout<<"inside:Fill_ChiSqt "<<std::endl;

Full_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_FullMap[kX]);
Full_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_FullMap[kY]);
Full_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_FullMap[kZ]);
Full_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_FullMap[kR]);
Full_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_FullMap[kdistance_edge]);
Full_Chisqt_before.push_back(ChiSqrt_beforeMuonVar_FullMap[kP_T]);
Full_Chisqt_before.push_back(ChiSqrt_beforeMuonVar_FullMap[kP_Z]);
Full_Chisqt_before.push_back(ChiSqrt_beforeMuonVar_FullMap[kE]);
Full_Chisqt_before.push_back(ChiSqrt_beforeMuonVar_FullMap[kAngleWRTB]);
Full_Chisqt_before.push_back(ChiSqrt_beforeMuonVar_FullMap[kDOCA_muon]);
Full_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_FullMap[krecoil_DOCA]);
Full_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_FullMap[krecoil_tracklength_minerva]);
Full_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_FullMap[kdistance_downstreamcap]);
Full_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_FullMap[kdistance_downstreamcap_RCut]);
Full_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_FullMap[kdistance_upstreamcap]);
Full_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_FullMap[kdistance_upstreamcap_RCut]);
Full_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_FullMap[kZ_RCut]);
Full_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_FullMap[kX_RCut]);
Full_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_FullMap[kY_RCut]);
Full_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_FullMap[kR_RCut]);


Empty_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_EmptyMap[kX]);
Empty_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_EmptyMap[kY]);
Empty_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_EmptyMap[kZ]);
Empty_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_EmptyMap[kR]);
Empty_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_EmptyMap[kdistance_edge]);
Empty_Chisqt_before.push_back(ChiSqrt_beforeMuonVar_EmptyMap[kP_T]);
Empty_Chisqt_before.push_back(ChiSqrt_beforeMuonVar_EmptyMap[kP_Z]);
Empty_Chisqt_before.push_back(ChiSqrt_beforeMuonVar_EmptyMap[kE]);
Empty_Chisqt_before.push_back(ChiSqrt_beforeMuonVar_EmptyMap[kAngleWRTB]);
Empty_Chisqt_before.push_back(ChiSqrt_beforeMuonVar_EmptyMap[kDOCA_muon]);
Empty_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_EmptyMap[krecoil_DOCA]);
Empty_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_EmptyMap[krecoil_tracklength_minerva]);
Empty_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_EmptyMap[kdistance_downstreamcap]);
Empty_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_EmptyMap[kdistance_downstreamcap_RCut]);
Empty_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_EmptyMap[kdistance_upstreamcap]);
Empty_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_EmptyMap[kdistance_upstreamcap_RCut]);
Empty_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_EmptyMap[kZ_RCut]);
Empty_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_EmptyMap[kX_RCut]);
Empty_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_EmptyMap[kY_RCut]);
Empty_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_EmptyMap[kR_RCut]);

Full_Empty_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_Full_EmptyMap[kX]);
Full_Empty_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_Full_EmptyMap[kY]);
Full_Empty_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_Full_EmptyMap[kZ]);
Full_Empty_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_Full_EmptyMap[kR]);
Full_Empty_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_Full_EmptyMap[kdistance_edge]);
Full_Empty_Chisqt_before.push_back(ChiSqrt_beforeMuonVar_Full_EmptyMap[kP_T]);
Full_Empty_Chisqt_before.push_back(ChiSqrt_beforeMuonVar_Full_EmptyMap[kP_Z]);
Full_Empty_Chisqt_before.push_back(ChiSqrt_beforeMuonVar_Full_EmptyMap[kE]);
Full_Empty_Chisqt_before.push_back(ChiSqrt_beforeMuonVar_Full_EmptyMap[kAngleWRTB]);
Full_Empty_Chisqt_before.push_back(ChiSqrt_beforeMuonVar_Full_EmptyMap[kDOCA_muon]);
Full_Empty_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_Full_EmptyMap[krecoil_DOCA]);
Full_Empty_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_Full_EmptyMap[krecoil_tracklength_minerva]);
Full_Empty_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_Full_EmptyMap[kdistance_downstreamcap]);
Full_Empty_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_Full_EmptyMap[kdistance_downstreamcap_RCut]);
Full_Empty_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_Full_EmptyMap[kdistance_upstreamcap]);
Full_Empty_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_Full_EmptyMap[kdistance_upstreamcap_RCut]);
Full_Empty_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_Full_EmptyMap[kZ_RCut]);
Full_Empty_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_Full_EmptyMap[kX_RCut]);
Full_Empty_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_Full_EmptyMap[kY_RCut]);
Full_Empty_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_Full_EmptyMap[kR_RCut]);
/////////////////////////////////////////////////////////////

Full_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_FullMap[kX]);
Full_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_FullMap[kY]);
Full_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_FullMap[kZ]);
Full_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_FullMap[kR]);
Full_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_FullMap[kdistance_edge]);
Full_Chisqt_after.push_back(ChiSqrt_afterMuonVar_FullMap[kP_T]);
Full_Chisqt_after.push_back(ChiSqrt_afterMuonVar_FullMap[kP_Z]);
Full_Chisqt_after.push_back(ChiSqrt_afterMuonVar_FullMap[kE]);
Full_Chisqt_after.push_back(ChiSqrt_afterMuonVar_FullMap[kAngleWRTB]);
Full_Chisqt_after.push_back(ChiSqrt_afterMuonVar_FullMap[kDOCA_muon]);
Full_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_FullMap[krecoil_DOCA]);
Full_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_FullMap[krecoil_tracklength_minerva]);
Full_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_FullMap[kdistance_downstreamcap]);
Full_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_FullMap[kdistance_downstreamcap_RCut]);
Full_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_FullMap[kdistance_upstreamcap]);
Full_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_FullMap[kdistance_upstreamcap_RCut]);
Full_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_FullMap[kZ_RCut]);
Full_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_FullMap[kX_RCut]);
Full_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_FullMap[kY_RCut]);
Full_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_FullMap[kR_RCut]);




Empty_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_EmptyMap[kX]);
Empty_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_EmptyMap[kY]);
Empty_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_EmptyMap[kZ]);
Empty_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_EmptyMap[kR]);
Empty_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_EmptyMap[kdistance_edge]);
Empty_Chisqt_after.push_back(ChiSqrt_afterMuonVar_EmptyMap[kP_T]);
Empty_Chisqt_after.push_back(ChiSqrt_afterMuonVar_EmptyMap[kP_Z]);
Empty_Chisqt_after.push_back(ChiSqrt_afterMuonVar_EmptyMap[kE]);
Empty_Chisqt_after.push_back(ChiSqrt_afterMuonVar_EmptyMap[kAngleWRTB]);
Empty_Chisqt_after.push_back(ChiSqrt_afterMuonVar_EmptyMap[kDOCA_muon]);
Empty_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_EmptyMap[krecoil_DOCA]);
Empty_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_EmptyMap[krecoil_tracklength_minerva]);
Empty_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_EmptyMap[kdistance_downstreamcap]);
Empty_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_EmptyMap[kdistance_downstreamcap_RCut]);
Empty_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_EmptyMap[kdistance_upstreamcap]);
Empty_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_EmptyMap[kdistance_upstreamcap_RCut]);
Empty_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_EmptyMap[kZ_RCut]);
Empty_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_EmptyMap[kX_RCut]);
Empty_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_EmptyMap[kY_RCut]);
Empty_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_EmptyMap[kR_RCut]);


Full_Empty_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_Full_EmptyMap[kX]);
Full_Empty_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_Full_EmptyMap[kY]);
Full_Empty_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_Full_EmptyMap[kZ]);
Full_Empty_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_Full_EmptyMap[kR]);
Full_Empty_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_Full_EmptyMap[kdistance_edge]);
Full_Empty_Chisqt_after.push_back(ChiSqrt_afterMuonVar_Full_EmptyMap[kP_T]);
Full_Empty_Chisqt_after.push_back(ChiSqrt_afterMuonVar_Full_EmptyMap[kP_Z]);
Full_Empty_Chisqt_after.push_back(ChiSqrt_afterMuonVar_Full_EmptyMap[kE]);
Full_Empty_Chisqt_after.push_back(ChiSqrt_afterMuonVar_Full_EmptyMap[kAngleWRTB]);
Full_Empty_Chisqt_after.push_back(ChiSqrt_afterMuonVar_Full_EmptyMap[kDOCA_muon]);
Full_Empty_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_Full_EmptyMap[krecoil_DOCA]);
Full_Empty_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_Full_EmptyMap[krecoil_tracklength_minerva]);
Full_Empty_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_Full_EmptyMap[kdistance_downstreamcap]);
Full_Empty_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_Full_EmptyMap[kdistance_downstreamcap_RCut]);
Full_Empty_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_Full_EmptyMap[kdistance_upstreamcap]);
Full_Empty_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_Full_EmptyMap[kdistance_upstreamcap_RCut]);
Full_Empty_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_Full_EmptyMap[kZ_RCut]);
Full_Empty_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_Full_EmptyMap[kX_RCut]);
Full_Empty_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_Full_EmptyMap[kY_RCut]);
Full_Empty_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_Full_EmptyMap[kR_RCut]);

std::cout<<"inside: Fill_ChiSqt Finished and sizes of Vectors are :  "<<std::endl;
std::cout<<"inside: Full_Chisqt_before.size() =    "<< Full_Chisqt_before.size()<< std::endl;
std::cout<<"inside: Empty_Chisqt_before.size() =    "<< Empty_Chisqt_before.size()<< std::endl;
std::cout<<"inside: Full_Empty_Chisqt_before.size() =    "<< Full_Empty_Chisqt_before.size()<< std::endl;

std::cout<<"inside: Full_Chisqt_after.size() =    "<< Full_Chisqt_after.size()<< std::endl;
std::cout<<"inside: Empty_Chisqt_after.size() =    "<< Empty_Chisqt_after.size()<< std::endl;
std::cout<<"inside: Full_Empty_Chisqt_after.size() =    "<< Full_Empty_Chisqt_after.size()<< std::endl;
}

void Helium_3CryoRegionsSideBandTool::Fill_ChiSqt_Empty(
  std::vector<double> &Empty_Chisqt_before, std::vector<double> &Empty_Chisqt_after)
{

Empty_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_EmptyMap[kX]);
Empty_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_EmptyMap[kY]);
Empty_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_EmptyMap[kZ]);
Empty_Chisqt_before.push_back(ChiSqrt_beforeCryoVertex_EmptyMap[kR]);

Empty_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_EmptyMap[kX]);
Empty_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_EmptyMap[kY]);
Empty_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_EmptyMap[kZ]);
Empty_Chisqt_after.push_back(ChiSqrt_afterCryoVertex_EmptyMap[kR]);


std::cout<<"inside: Fill_ChiSqt Finished and sizes of Vectors are :  "<<std::endl;
std::cout<<"inside: Empty_Chisqt_before.size() =    "<< Empty_Chisqt_before.size()<< std::endl;

std::cout<<"inside: Empty_Chisqt_after.size() =    "<< Empty_Chisqt_after.size()<< std::endl;

}

void Helium_3CryoRegionsSideBandTool::Fill_ndf_vars(Helium3SideBand &sb , std::vector<double> &ndf_vector){

std::cout<<"inside: Fill_ndf_vars "<<std::endl;

ndf_vector.push_back((double)sb.MnvH1D_Vertex_X_data->GetNbinsX()-1);
ndf_vector.push_back((double)sb.MnvH1D_Vertex_Y_data->GetNbinsX()-1);
ndf_vector.push_back((double)sb.MnvH1D_Vertex_Z_data->GetNbinsX()-1);
ndf_vector.push_back((double)sb.MnvH1D_Vertex_R_data->GetNbinsX()-1);
ndf_vector.push_back((double)sb.DistancetoEdge.MnvH1D_data->GetNbinsX()-1);
ndf_vector.push_back((double)sb.muon_PT.MnvH1D_data->GetNbinsX()-1);
ndf_vector.push_back((double)sb.muon_PZ.MnvH1D_data->GetNbinsX()-1);
ndf_vector.push_back((double)sb.muon_E.MnvH1D_data->GetNbinsX()-1);
ndf_vector.push_back((double)sb.muon_theta.MnvH1D_data->GetNbinsX()-1);
ndf_vector.push_back((double)sb.muon_doca.MnvH1D_data->GetNbinsX()-1);
ndf_vector.push_back((double)sb.SecTrk_doca.MnvH1D_data->GetNbinsX()-1);
ndf_vector.push_back((double)sb.TrackLength.MnvH1D_data->GetNbinsX()-1);
ndf_vector.push_back((double)sb.DistancetoUpstreamCap.MnvH1D_data->GetNbinsX()-1);
ndf_vector.push_back((double)sb.DistancetoDownstreamCap.MnvH1D_data->GetNbinsX()-1);
ndf_vector.push_back((double)sb.DistancetoUpstreamCap_RCut.MnvH1D_data->GetNbinsX()-1);
ndf_vector.push_back((double)sb.DistancetoDownstreamCap_RCut.MnvH1D_data->GetNbinsX()-1);
ndf_vector.push_back((double)sb.Vertex_Z_RCut.MnvH1D_data->GetNbinsX()-1);
ndf_vector.push_back((double)sb.Vertex_X_RCut.MnvH1D_data->GetNbinsX()-1);
ndf_vector.push_back((double)sb.Vertex_Y_RCut.MnvH1D_data->GetNbinsX()-1);
ndf_vector.push_back((double)sb.Vertex_R_RCut.MnvH1D_data->GetNbinsX()-1);


}

void Helium_3CryoRegionsSideBandTool::Fill_ndf_Fitting(Helium3SideBand &sb , std::vector<double> &ndf_vector){

std::cout<<"inside: Fill_ndf_vars "<<std::endl;

ndf_vector.push_back((double)sb.MnvH1D_Vertex_X_data->GetNbinsX()-1);
ndf_vector.push_back((double)sb.MnvH1D_Vertex_Y_data->GetNbinsX()-1);
ndf_vector.push_back((double)sb.MnvH1D_Vertex_Z_data->GetNbinsX()-1);
ndf_vector.push_back((double)sb.MnvH1D_Vertex_R_data->GetNbinsX()-1);
}


void Helium_3CryoRegionsSideBandTool::MakeChiSqrt_table(std::string input_name, double scale){

std::cout<<"Inside:MakeChiSqrt_table "<<std::endl;

std::vector<double> Full_Chisqt_before;
std::vector<double> Full_Chisqt_after;
std::vector<double> Empty_Chisqt_before;
std::vector<double> Empty_Chisqt_after;
std::vector<double> Full_Empty_Chisqt_before;
std::vector<double> Full_Empty_Chisqt_after;

std::vector<double> ndf_vector;
std::vector<std::string> String_names_for_sideBand;
Vector_string_names(String_names_for_sideBand);
//std::cout<<"String_names_for_sideBand.size() = " << String_names_for_sideBand.size()<<std::endl;
//for(auto cat:String_names_for_sideBand){std::cout<< "Name: "<<cat<<std::endl;}
Fill_ndf_vars(Empty , ndf_vector);

//std::cout<<"ndf_vector.size() = " << ndf_vector.size()<<std::endl;

Fill_ChiSqt(Full_Chisqt_before, Full_Chisqt_after,
  Empty_Chisqt_before, Empty_Chisqt_after,
  Full_Empty_Chisqt_before, Full_Empty_Chisqt_after);

std::string output_name;
output_name= "CryoTank_F_ChiSqrt_fits_" + input_name;

std::cout<<"Making First Table [Full]"<<std::endl;

MakeLatexChiSqrt_table(output_name, "Full",
String_names_for_sideBand,
Full_Chisqt_before,
Full_Chisqt_after,
ndf_vector, scale
);

output_name= "CryoTank_E_ChiSqrt_fits_" + input_name;

std::cout<<"Making second Table [Empty]"<<std::endl;
MakeLatexChiSqrt_table(output_name, "Empty",
String_names_for_sideBand,
Empty_Chisqt_before,
Empty_Chisqt_after,
ndf_vector, scale
);

output_name= "CryoTank_F_E_ChiSqrt_fits_" + input_name;

std::cout<<"Making second Table [F-E]"<<std::endl;
MakeLatexChiSqrt_table(output_name, "F - E",
String_names_for_sideBand,
Full_Empty_Chisqt_before,
Full_Empty_Chisqt_after,
ndf_vector, scale
);


}
void Helium_3CryoRegionsSideBandTool::MakeChiSqrt_table_beforeShiftincluded(std::string input_name,
  double scale, std::vector<double> Full_input_before , std::vector<double> Empty_input_before,
  std::vector<double> Full_Empty_input_before){

std::cout<<"Inside:MakeChiSqrt_table "<<std::endl;

std::vector<double> Full_Chisqt_before;
std::vector<double> Full_Chisqt_after;
std::vector<double> Empty_Chisqt_before;
std::vector<double> Empty_Chisqt_after;
std::vector<double> Full_Empty_Chisqt_before;
std::vector<double> Full_Empty_Chisqt_after;

std::vector<double> ndf_vector;
std::vector<std::string> String_names_for_sideBand;
Vector_string_names(String_names_for_sideBand);
//std::cout<<"String_names_for_sideBand.size() = " << String_names_for_sideBand.size()<<std::endl;
//for(auto cat:String_names_for_sideBand){std::cout<< "Name: "<<cat<<std::endl;}
Fill_ndf_vars(Empty , ndf_vector);

//std::cout<<"ndf_vector.size() = " << ndf_vector.size()<<std::endl;

Fill_ChiSqt(Full_Chisqt_before, Full_Chisqt_after,
  Empty_Chisqt_before, Empty_Chisqt_after,
  Full_Empty_Chisqt_before, Full_Empty_Chisqt_after);

std::string output_name;
output_name= "CryoTank_F_ChiSqrt_fits_" + input_name;

std::cout<<"Making First Table [Full]"<<std::endl;

MakeLatexChiSqrt_table_new(output_name, "Full", String_names_for_sideBand,
  Full_input_before,
  Full_Chisqt_before,
  Full_Chisqt_after,
  ndf_vector, scale);


output_name= "CryoTank_E_ChiSqrt_fits_" + input_name;

std::cout<<"Making second Table [Empty]"<<std::endl;
MakeLatexChiSqrt_table_new(output_name, "Empty", String_names_for_sideBand,
  Empty_input_before,
  Empty_Chisqt_before,
  Empty_Chisqt_after,
  ndf_vector, scale);



output_name= "CryoTank_F_E_ChiSqrt_fits_" + input_name;

std::cout<<"Making second Table [F-E]"<<std::endl;

MakeLatexChiSqrt_table_new(output_name, "Full_Empty", String_names_for_sideBand,
  Full_Empty_input_before,
  Full_Empty_Chisqt_before,
  Full_Empty_Chisqt_after,
  ndf_vector, scale);

}

void Helium_3CryoRegionsSideBandTool::MakeChiSqrt_table_vertex_Empty(std::string input_name, std::vector<double>beforeChi_zeroshift,
  std::vector<double>afterChi_zeroshift,  double scale){

std::cout<<"Inside:MakeChiSqrt_table "<<std::endl;


  std::vector<double> Empty_Chisqt_before;
  std::vector<double> Empty_Chisqt_after;

  std::vector<double> ndf_vector;
  std::vector<std::string> String_names_for_sideBand;
  Vector_string_Fittingnames(String_names_for_sideBand);
  //std::cout<<"String_names_for_sideBand.size() = " << String_names_for_sideBand.size()<<std::endl;
  //for(auto cat:String_names_for_sideBand){std::cout<< "Name: "<<cat<<std::endl;}
  Fill_ndf_Fitting(Empty , ndf_vector);

  //std::cout<<"ndf_vector.size() = " << ndf_vector.size()<<std::endl;

  Fill_ChiSqt_Empty(Empty_Chisqt_before, Empty_Chisqt_after);

  std::string output_name;
  output_name= "CryoTank_F_ChiSqrt_fits_" + input_name;

  std::cout<<"Making First Table"<<std::endl;


    output_name= "CryoTank_Empty_ChiSqrt_Noshiftfits_" + input_name;
        MakeLatexChiSqrt_table(output_name, "Empty no Shift",
          String_names_for_sideBand,
          beforeChi_zeroshift,
          afterChi_zeroshift,
          ndf_vector, scale
        );


        output_name= "CryoTank_Empty_ChiSqrt_shiftfits_" + input_name;
            MakeLatexChiSqrt_table(output_name, "Empty no Shift",
              String_names_for_sideBand,
              Empty_Chisqt_before,
              Empty_Chisqt_after,
              ndf_vector, scale
            );


}






void Helium_3CryoRegionsSideBandTool::AppendtoLatex(std::string output_name ,  std::string pdf_name_CV, int Figure_1_page_number,int Figure_2_page_number,
  int Figure_3_page_number, std::string slideTitle ){
  double scale= .27;
  std::ofstream myfile;
  std::string fileName = output_name + ".txt";
  myfile.open(fileName, std::ios_base::app);
  std::cout<<"Adding to Latex File "<< fileName<<std::endl;
  LatexFormat Latex_output(scale);
  myfile<<"\n";
  myfile<<"\n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<"%%%  Start   "<< slideTitle<<" \n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<Latex_output.GetBeginFrame(slideTitle)<< "\n";
  myfile<<Latex_output.GetBeginTabular()<< "\n";
  myfile<<Latex_output.GetInclude_figure(Figure_1_page_number, pdf_name_CV)<< "\n";
  myfile<<"& \n";
  myfile<<Latex_output.Get_hSpace("-1cm")<< "\n";
  myfile<<Latex_output.GetInclude_figure(Figure_2_page_number, pdf_name_CV )<< "\n";
  myfile<<"& \n";
  myfile<<Latex_output.Get_hSpace("-1cm")<< "\n";
  myfile<<Latex_output.GetInclude_figure(Figure_3_page_number, pdf_name_CV)<< "\n";
  myfile<<Latex_output.GetEndTabular()<< "\n";
  myfile<<Latex_output.GetEndFrame();

  myfile<<"\n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";
  myfile<<"%%% END FRAME  \n";
  myfile<<"%%%%%%%%%%%%%%%%% \n";

  myfile.close();


}// end of function

void Helium_3CryoRegionsSideBandTool::MakeLatexSlides(std::string output_name){

  std::string SlideTitle;

  int Before_page_full_Stack = 26;
  int Before_page_empty_Stack = 10;
  int Before_page_F_E_Stack = 42;

  int Before_page_full_NONStack = 30;
  int Before_page_empty_NONStack = 14;
  int Before_page_F_E_NONStack = 46;

  int After_page_full_Stack = 241;
  int After_page_empty_Stack = 201;
  int After_page_F_E_Stack = 281;

  int After_page_full_NONStack = 245;
  int After_page_empty_NONStack = 205;
  int After_page_F_E_NONStack = 285;

  /////////////////
  ///Stacks /////
  ////////////////

  SlideTitle = "Vertex X Before";
  AppendtoLatex( output_name ,  LatexPdfLabel, Before_page_full_Stack, Before_page_empty_Stack , Before_page_F_E_Stack, SlideTitle);
  SlideTitle = "Vertex X After";
  AppendtoLatex( output_name ,  LatexPdfLabel, After_page_full_Stack, After_page_empty_Stack , After_page_F_E_Stack, SlideTitle);
  Before_page_full_Stack++;Before_page_empty_Stack++;Before_page_F_E_Stack++;
  After_page_full_Stack++;After_page_empty_Stack++;After_page_F_E_Stack++;
  SlideTitle = "Vertex Y Before";
  AppendtoLatex( output_name ,  LatexPdfLabel, Before_page_full_Stack, Before_page_empty_Stack , Before_page_F_E_Stack, SlideTitle);
  SlideTitle = "Vertex Y After";
  AppendtoLatex( output_name ,  LatexPdfLabel, After_page_full_Stack, After_page_empty_Stack , After_page_F_E_Stack, SlideTitle);
  Before_page_full_Stack++;Before_page_empty_Stack++;Before_page_F_E_Stack++;
  After_page_full_Stack++;After_page_empty_Stack++;After_page_F_E_Stack++;
  SlideTitle = "Vertex Z Before";
  AppendtoLatex( output_name ,  LatexPdfLabel, Before_page_full_Stack, Before_page_empty_Stack , Before_page_F_E_Stack, SlideTitle);
  SlideTitle = "Vertex Z After";
  AppendtoLatex( output_name ,  LatexPdfLabel, After_page_full_Stack, After_page_empty_Stack , After_page_F_E_Stack, SlideTitle);
  Before_page_full_Stack++;Before_page_empty_Stack++;Before_page_F_E_Stack++;
  After_page_full_Stack++;After_page_empty_Stack++;After_page_F_E_Stack++;
  SlideTitle = "Vertex R Before";
  AppendtoLatex( output_name ,  LatexPdfLabel, Before_page_full_Stack, Before_page_empty_Stack , Before_page_F_E_Stack, SlideTitle);
  SlideTitle = "Vertex R After";
  AppendtoLatex( output_name ,  LatexPdfLabel, After_page_full_Stack, After_page_empty_Stack , After_page_F_E_Stack, SlideTitle);


  /////////////////
  /// non-Stacks /////
  ////////////////

  SlideTitle = "Vertex X Before";
  AppendtoLatex( output_name ,  LatexPdfLabel, Before_page_full_NONStack, Before_page_empty_NONStack , Before_page_F_E_NONStack, SlideTitle);
  SlideTitle = "Vertex X After";
  AppendtoLatex( output_name ,  LatexPdfLabel, After_page_full_NONStack, After_page_empty_NONStack , After_page_F_E_NONStack, SlideTitle);
  Before_page_full_NONStack++;Before_page_empty_NONStack++;Before_page_F_E_NONStack++;
  After_page_full_NONStack++;After_page_empty_NONStack++;After_page_F_E_NONStack++;
  SlideTitle = "Vertex Y Before";
  AppendtoLatex( output_name ,  LatexPdfLabel, Before_page_full_NONStack, Before_page_empty_NONStack , Before_page_F_E_NONStack, SlideTitle);
  SlideTitle = "Vertex Y After";
  AppendtoLatex( output_name ,  LatexPdfLabel, After_page_full_NONStack, After_page_empty_NONStack , After_page_F_E_NONStack, SlideTitle);
  Before_page_full_NONStack++;Before_page_empty_NONStack++;Before_page_F_E_NONStack++;
  After_page_full_NONStack++;After_page_empty_NONStack++;After_page_F_E_NONStack++;
  SlideTitle = "Vertex Z Before";
  AppendtoLatex( output_name ,  LatexPdfLabel, Before_page_full_NONStack, Before_page_empty_NONStack , Before_page_F_E_NONStack, SlideTitle);
  SlideTitle = "Vertex Z After";
  AppendtoLatex( output_name ,  LatexPdfLabel, After_page_full_NONStack, After_page_empty_NONStack , After_page_F_E_NONStack, SlideTitle);
  Before_page_full_NONStack++;Before_page_empty_NONStack++;Before_page_F_E_NONStack++;
  After_page_full_NONStack++;After_page_empty_NONStack++;After_page_F_E_NONStack++;
  SlideTitle = "Vertex R Before";
  AppendtoLatex( output_name ,  LatexPdfLabel, Before_page_full_NONStack, Before_page_empty_NONStack , Before_page_F_E_NONStack, SlideTitle);
  SlideTitle = "Vertex R After";
  AppendtoLatex( output_name ,  LatexPdfLabel, After_page_full_NONStack, After_page_empty_NONStack , After_page_F_E_NONStack, SlideTitle);

///////////////////
/// Non Fitting Parama
/////////////////


  Before_page_full_Stack = 108;   Before_page_full_NONStack = 124;
  Before_page_empty_Stack = 63;   Before_page_empty_NONStack = 79;
  Before_page_F_E_Stack = 153;    Before_page_F_E_NONStack = 169;
  After_page_full_Stack = 249;    After_page_full_NONStack = 265;
  After_page_empty_Stack = 209; After_page_empty_NONStack = 225;
  After_page_F_E_Stack = 289;   After_page_F_E_NONStack = 305;

  SlideTitle = "$P_{T}$ Before";
  AppendtoLatex( output_name ,  LatexPdfLabel, Before_page_full_Stack, Before_page_empty_Stack , Before_page_F_E_Stack, SlideTitle);
  SlideTitle = "$P_{T}$ After";
  AppendtoLatex( output_name ,  LatexPdfLabel, After_page_full_Stack, After_page_empty_Stack , After_page_F_E_Stack, SlideTitle);
  Before_page_full_Stack++;Before_page_empty_Stack++;Before_page_F_E_Stack++;
  After_page_full_Stack++;After_page_empty_Stack++;After_page_F_E_Stack++;
  SlideTitle = "$P_{Z}$ Before";
  AppendtoLatex( output_name ,  LatexPdfLabel, Before_page_full_Stack, Before_page_empty_Stack , Before_page_F_E_Stack, SlideTitle);
  SlideTitle = "$P_{Z}$ After";
  AppendtoLatex( output_name ,  LatexPdfLabel, After_page_full_Stack, After_page_empty_Stack , After_page_F_E_Stack, SlideTitle);
  Before_page_full_Stack++;Before_page_empty_Stack++;Before_page_F_E_Stack++;
  After_page_full_Stack++;After_page_empty_Stack++;After_page_F_E_Stack++;
  SlideTitle = "$\\theta_{\\mu}$ Before";
  AppendtoLatex( output_name ,  LatexPdfLabel, Before_page_full_Stack, Before_page_empty_Stack , Before_page_F_E_Stack, SlideTitle);
  SlideTitle = "$\\theta_{\\mu}$ After";
  AppendtoLatex( output_name ,  LatexPdfLabel, After_page_full_Stack, After_page_empty_Stack , After_page_F_E_Stack, SlideTitle);
  Before_page_full_Stack++;Before_page_empty_Stack++;Before_page_F_E_Stack++;
  After_page_full_Stack++;After_page_empty_Stack++;After_page_F_E_Stack++;
  SlideTitle = "E_{\\mu} Before";
  AppendtoLatex( output_name ,  LatexPdfLabel, Before_page_full_Stack, Before_page_empty_Stack , Before_page_F_E_Stack, SlideTitle);
  SlideTitle = "E_{\\mu} After";
  AppendtoLatex( output_name ,  LatexPdfLabel, After_page_full_Stack, After_page_empty_Stack , After_page_F_E_Stack, SlideTitle);
  Before_page_full_Stack++;Before_page_empty_Stack++;Before_page_F_E_Stack++;
  After_page_full_Stack++;After_page_empty_Stack++;After_page_F_E_Stack++;
  SlideTitle = "Muon DOCA  Before";
  AppendtoLatex( output_name ,  LatexPdfLabel, Before_page_full_Stack, Before_page_empty_Stack , Before_page_F_E_Stack, SlideTitle);
  SlideTitle = "Muon DOCA  After";
  AppendtoLatex( output_name ,  LatexPdfLabel, After_page_full_Stack, After_page_empty_Stack , After_page_F_E_Stack, SlideTitle);

  Before_page_full_Stack++;Before_page_empty_Stack++;Before_page_F_E_Stack++;
  After_page_full_Stack++;After_page_empty_Stack++;After_page_F_E_Stack++;
  SlideTitle = "Distance to Nearest Wall  Before";
  AppendtoLatex( output_name ,  LatexPdfLabel, Before_page_full_Stack, Before_page_empty_Stack , Before_page_F_E_Stack, SlideTitle);
  SlideTitle = "Distance to Nearest Wall  After";
  AppendtoLatex( output_name ,  LatexPdfLabel, After_page_full_Stack, After_page_empty_Stack , After_page_F_E_Stack, SlideTitle);

  Before_page_full_Stack++;Before_page_empty_Stack++;Before_page_F_E_Stack++;
  After_page_full_Stack++;After_page_empty_Stack++;After_page_F_E_Stack++;
  SlideTitle = "Recoil DOCA  Before";
  AppendtoLatex( output_name ,  LatexPdfLabel, Before_page_full_Stack, Before_page_empty_Stack , Before_page_F_E_Stack, SlideTitle);
  SlideTitle = "Recoil DOCA  After";
  AppendtoLatex( output_name ,  LatexPdfLabel, After_page_full_Stack, After_page_empty_Stack , After_page_F_E_Stack, SlideTitle);
  Before_page_full_Stack++;Before_page_empty_Stack++;Before_page_F_E_Stack++;
  After_page_full_Stack++;After_page_empty_Stack++;After_page_F_E_Stack++;
  SlideTitle = "Recoil TrackLength  Before";
  AppendtoLatex( output_name ,  LatexPdfLabel, Before_page_full_Stack, Before_page_empty_Stack , Before_page_F_E_Stack, SlideTitle);
  SlideTitle = "Recoil TrackLength  After";
  AppendtoLatex( output_name ,  LatexPdfLabel, After_page_full_Stack, After_page_empty_Stack , After_page_F_E_Stack, SlideTitle);
  Before_page_full_Stack++;Before_page_empty_Stack++;Before_page_F_E_Stack++;
  After_page_full_Stack++;After_page_empty_Stack++;After_page_F_E_Stack++;
  SlideTitle = "Distance To DSCap Before";
  AppendtoLatex( output_name ,  LatexPdfLabel, Before_page_full_Stack, Before_page_empty_Stack , Before_page_F_E_Stack, SlideTitle);
  SlideTitle = "Distance To DSCap After";
  AppendtoLatex( output_name ,  LatexPdfLabel, After_page_full_Stack, After_page_empty_Stack , After_page_F_E_Stack, SlideTitle);
  Before_page_full_Stack++;Before_page_empty_Stack++;Before_page_F_E_Stack++;
  After_page_full_Stack++;After_page_empty_Stack++;After_page_F_E_Stack++;
  SlideTitle = "Distance To USCap [RCUT] Before";
  AppendtoLatex( output_name ,  LatexPdfLabel, Before_page_full_Stack, Before_page_empty_Stack , Before_page_F_E_Stack, SlideTitle);
  SlideTitle = "Distance To USCap [RCUT] After";
  AppendtoLatex( output_name ,  LatexPdfLabel, After_page_full_Stack, After_page_empty_Stack , After_page_F_E_Stack, SlideTitle);
  Before_page_full_Stack++;Before_page_empty_Stack++;Before_page_F_E_Stack++;
  After_page_full_Stack++;After_page_empty_Stack++;After_page_F_E_Stack++;
  SlideTitle = "Distance To DSCap Before";
  AppendtoLatex( output_name ,  LatexPdfLabel, Before_page_full_Stack, Before_page_empty_Stack , Before_page_F_E_Stack, SlideTitle);
  SlideTitle = "Distance To DSCap After";
  AppendtoLatex( output_name ,  LatexPdfLabel, After_page_full_Stack, After_page_empty_Stack , After_page_F_E_Stack, SlideTitle);
  Before_page_full_Stack++;Before_page_empty_Stack++;Before_page_F_E_Stack++;
  After_page_full_Stack++;After_page_empty_Stack++;After_page_F_E_Stack++;
  SlideTitle = "Distance To DSCap [RCUT] Before";
  AppendtoLatex( output_name ,  LatexPdfLabel, Before_page_full_Stack, Before_page_empty_Stack , Before_page_F_E_Stack, SlideTitle);
  SlideTitle = "Distance To DSCap [RCUT] After";
  AppendtoLatex( output_name ,  LatexPdfLabel, After_page_full_Stack, After_page_empty_Stack , After_page_F_E_Stack, SlideTitle);
  Before_page_full_Stack++;Before_page_empty_Stack++;Before_page_F_E_Stack++;
  After_page_full_Stack++;After_page_empty_Stack++;After_page_F_E_Stack++;
  SlideTitle = "Vertex Z [RCUT] Before";
  AppendtoLatex( output_name ,  LatexPdfLabel, Before_page_full_Stack, Before_page_empty_Stack , Before_page_F_E_Stack, SlideTitle);
  SlideTitle = "Vertex Z [RCUT] After";
  AppendtoLatex( output_name ,  LatexPdfLabel, After_page_full_Stack, After_page_empty_Stack , After_page_F_E_Stack, SlideTitle);
  Before_page_full_Stack++;Before_page_empty_Stack++;Before_page_F_E_Stack++;
  After_page_full_Stack++;After_page_empty_Stack++;After_page_F_E_Stack++;
  SlideTitle = "Vertex X [RCUT] Before";
  AppendtoLatex( output_name ,  LatexPdfLabel, Before_page_full_Stack, Before_page_empty_Stack , Before_page_F_E_Stack, SlideTitle);
  SlideTitle = "Vertex X [RCUT] After";
  AppendtoLatex( output_name ,  LatexPdfLabel, After_page_full_Stack, After_page_empty_Stack , After_page_F_E_Stack, SlideTitle);
  Before_page_full_Stack++;Before_page_empty_Stack++;Before_page_F_E_Stack++;
  After_page_full_Stack++;After_page_empty_Stack++;After_page_F_E_Stack++;
  SlideTitle = "Vertex Y [RCUT] Before";
  AppendtoLatex( output_name ,  LatexPdfLabel, Before_page_full_Stack, Before_page_empty_Stack , Before_page_F_E_Stack, SlideTitle);
  SlideTitle = "Vertex Y [RCUT] After";
  AppendtoLatex( output_name ,  LatexPdfLabel, After_page_full_Stack, After_page_empty_Stack , After_page_F_E_Stack, SlideTitle);

///////////////
// NonStack
//////////////
SlideTitle = "$P_{T}$ Before";
AppendtoLatex( output_name ,  LatexPdfLabel, Before_page_full_NONStack, Before_page_empty_NONStack , Before_page_F_E_NONStack, SlideTitle);
SlideTitle = "$P_{T}$ After";
AppendtoLatex( output_name ,  LatexPdfLabel, After_page_full_NONStack, After_page_empty_NONStack , After_page_F_E_NONStack, SlideTitle);
Before_page_full_NONStack++;Before_page_empty_NONStack++;Before_page_F_E_NONStack++;
After_page_full_NONStack++;After_page_empty_NONStack++;After_page_F_E_NONStack++;
SlideTitle = "$P_{Z}$ Before";
AppendtoLatex( output_name ,  LatexPdfLabel, Before_page_full_NONStack, Before_page_empty_NONStack , Before_page_F_E_NONStack, SlideTitle);
SlideTitle = "$P_{Z}$ After";
AppendtoLatex( output_name ,  LatexPdfLabel, After_page_full_NONStack, After_page_empty_NONStack , After_page_F_E_NONStack, SlideTitle);
Before_page_full_NONStack++;Before_page_empty_NONStack++;Before_page_F_E_NONStack++;
After_page_full_NONStack++;After_page_empty_NONStack++;After_page_F_E_NONStack++;
SlideTitle = "$\\theta_{\\mu}$ Before";
AppendtoLatex( output_name ,  LatexPdfLabel, Before_page_full_NONStack, Before_page_empty_NONStack , Before_page_F_E_NONStack, SlideTitle);
SlideTitle = "$\\theta_{\\mu}$ After";
AppendtoLatex( output_name ,  LatexPdfLabel, After_page_full_NONStack, After_page_empty_NONStack , After_page_F_E_NONStack, SlideTitle);
Before_page_full_NONStack++;Before_page_empty_NONStack++;Before_page_F_E_NONStack++;
After_page_full_NONStack++;After_page_empty_NONStack++;After_page_F_E_NONStack++;
SlideTitle = "E_{\\mu} Before";
AppendtoLatex( output_name ,  LatexPdfLabel, Before_page_full_NONStack, Before_page_empty_NONStack , Before_page_F_E_NONStack, SlideTitle);
SlideTitle = "E_{\\mu} After";
AppendtoLatex( output_name ,  LatexPdfLabel, After_page_full_NONStack, After_page_empty_NONStack , After_page_F_E_NONStack, SlideTitle);
Before_page_full_NONStack++;Before_page_empty_NONStack++;Before_page_F_E_NONStack++;
After_page_full_NONStack++;After_page_empty_NONStack++;After_page_F_E_NONStack++;
SlideTitle = "Muon DOCA  Before";
AppendtoLatex( output_name ,  LatexPdfLabel, Before_page_full_NONStack, Before_page_empty_NONStack , Before_page_F_E_NONStack, SlideTitle);
SlideTitle = "Muon DOCA  After";
AppendtoLatex( output_name ,  LatexPdfLabel, After_page_full_NONStack, After_page_empty_NONStack , After_page_F_E_NONStack, SlideTitle);

Before_page_full_NONStack++;Before_page_empty_NONStack++;Before_page_F_E_NONStack++;
After_page_full_NONStack++;After_page_empty_NONStack++;After_page_F_E_NONStack++;
SlideTitle = "Distance to Nearest Wall  Before";
AppendtoLatex( output_name ,  LatexPdfLabel, Before_page_full_NONStack, Before_page_empty_NONStack , Before_page_F_E_NONStack, SlideTitle);
SlideTitle = "Distance to Nearest Wall  After";
AppendtoLatex( output_name ,  LatexPdfLabel, After_page_full_NONStack, After_page_empty_NONStack , After_page_F_E_NONStack, SlideTitle);

Before_page_full_NONStack++;Before_page_empty_NONStack++;Before_page_F_E_NONStack++;
After_page_full_NONStack++;After_page_empty_NONStack++;After_page_F_E_NONStack++;
SlideTitle = "Recoil DOCA  Before";
AppendtoLatex( output_name ,  LatexPdfLabel, Before_page_full_NONStack, Before_page_empty_NONStack , Before_page_F_E_NONStack, SlideTitle);
SlideTitle = "Recoil DOCA  After";
AppendtoLatex( output_name ,  LatexPdfLabel, After_page_full_NONStack, After_page_empty_NONStack , After_page_F_E_NONStack, SlideTitle);
Before_page_full_NONStack++;Before_page_empty_NONStack++;Before_page_F_E_NONStack++;
After_page_full_NONStack++;After_page_empty_NONStack++;After_page_F_E_NONStack++;
SlideTitle = "Recoil TrackLength  Before";
AppendtoLatex( output_name ,  LatexPdfLabel, Before_page_full_NONStack, Before_page_empty_NONStack , Before_page_F_E_NONStack, SlideTitle);
SlideTitle = "Recoil TrackLength  After";
AppendtoLatex( output_name ,  LatexPdfLabel, After_page_full_NONStack, After_page_empty_NONStack , After_page_F_E_NONStack, SlideTitle);
Before_page_full_NONStack++;Before_page_empty_NONStack++;Before_page_F_E_NONStack++;
After_page_full_NONStack++;After_page_empty_NONStack++;After_page_F_E_NONStack++;
SlideTitle = "Distance To DSCap Before";
AppendtoLatex( output_name ,  LatexPdfLabel, Before_page_full_NONStack, Before_page_empty_NONStack , Before_page_F_E_NONStack, SlideTitle);
SlideTitle = "Distance To DSCap After";
AppendtoLatex( output_name ,  LatexPdfLabel, After_page_full_NONStack, After_page_empty_NONStack , After_page_F_E_NONStack, SlideTitle);
Before_page_full_NONStack++;Before_page_empty_NONStack++;Before_page_F_E_NONStack++;
After_page_full_NONStack++;After_page_empty_NONStack++;After_page_F_E_NONStack++;
SlideTitle = "Distance To USCap [RCUT] Before";
AppendtoLatex( output_name ,  LatexPdfLabel, Before_page_full_NONStack, Before_page_empty_NONStack , Before_page_F_E_NONStack, SlideTitle);
SlideTitle = "Distance To USCap [RCUT] After";
AppendtoLatex( output_name ,  LatexPdfLabel, After_page_full_NONStack, After_page_empty_NONStack , After_page_F_E_NONStack, SlideTitle);
Before_page_full_NONStack++;Before_page_empty_NONStack++;Before_page_F_E_NONStack++;
After_page_full_NONStack++;After_page_empty_NONStack++;After_page_F_E_NONStack++;
SlideTitle = "Distance To DSCap Before";
AppendtoLatex( output_name ,  LatexPdfLabel, Before_page_full_NONStack, Before_page_empty_NONStack , Before_page_F_E_NONStack, SlideTitle);
SlideTitle = "Distance To DSCap After";
AppendtoLatex( output_name ,  LatexPdfLabel, After_page_full_NONStack, After_page_empty_NONStack , After_page_F_E_NONStack, SlideTitle);
Before_page_full_NONStack++;Before_page_empty_NONStack++;Before_page_F_E_NONStack++;
After_page_full_NONStack++;After_page_empty_NONStack++;After_page_F_E_NONStack++;
SlideTitle = "Distance To DSCap [RCUT] Before";
AppendtoLatex( output_name ,  LatexPdfLabel, Before_page_full_NONStack, Before_page_empty_NONStack , Before_page_F_E_NONStack, SlideTitle);
SlideTitle = "Distance To DSCap [RCUT] After";
AppendtoLatex( output_name ,  LatexPdfLabel, After_page_full_NONStack, After_page_empty_NONStack , After_page_F_E_NONStack, SlideTitle);
Before_page_full_NONStack++;Before_page_empty_NONStack++;Before_page_F_E_NONStack++;
After_page_full_NONStack++;After_page_empty_NONStack++;After_page_F_E_NONStack++;
SlideTitle = "Vertex Z [RCUT] Before";
AppendtoLatex( output_name ,  LatexPdfLabel, Before_page_full_NONStack, Before_page_empty_NONStack , Before_page_F_E_NONStack, SlideTitle);
SlideTitle = "Vertex Z [RCUT] After";
AppendtoLatex( output_name ,  LatexPdfLabel, After_page_full_NONStack, After_page_empty_NONStack , After_page_F_E_NONStack, SlideTitle);
Before_page_full_NONStack++;Before_page_empty_NONStack++;Before_page_F_E_NONStack++;
After_page_full_NONStack++;After_page_empty_NONStack++;After_page_F_E_NONStack++;
SlideTitle = "Vertex X [RCUT] Before";
AppendtoLatex( output_name ,  LatexPdfLabel, Before_page_full_NONStack, Before_page_empty_NONStack , Before_page_F_E_NONStack, SlideTitle);
SlideTitle = "Vertex X [RCUT] After";
AppendtoLatex( output_name ,  LatexPdfLabel, After_page_full_NONStack, After_page_empty_NONStack , After_page_F_E_NONStack, SlideTitle);
Before_page_full_NONStack++;Before_page_empty_NONStack++;Before_page_F_E_NONStack++;
After_page_full_NONStack++;After_page_empty_NONStack++;After_page_F_E_NONStack++;
SlideTitle = "Vertex Y [RCUT] Before";
AppendtoLatex( output_name ,  LatexPdfLabel, Before_page_full_NONStack, Before_page_empty_NONStack , Before_page_F_E_NONStack, SlideTitle);
SlideTitle = "Vertex Y [RCUT] After";
AppendtoLatex( output_name ,  LatexPdfLabel, After_page_full_NONStack, After_page_empty_NONStack , After_page_F_E_NONStack, SlideTitle);





}





void Helium_3CryoRegionsSideBandTool::WriteStatistics(Helium3SideBand &sb)
{
    // Open Text File
    std::string file_name = "EmptyFillResults.txt";
    std::ofstream file;
    file.open(file_name.c_str());

    // Write Header
    file<<std::left;
    file.width(12); file<<"Vertex_X_Universe"<<" ";
    file.width(12); file<<"Vertex_X_N(Data)"<<" ";
    file.width(12); file<<"Vertex_X_N(MC)"<<" ";
    file.width(12); file<<"Vertex_X_N(Helium)"<<" ";
    file.width(12); file<<"Vertex_X_N(Aluminium)"<<" ";
    file.width(12); file<<"Vertex_X_N(Carbon)"<<" ";
    file.width(12); file<<"Vertex_X_N(Iron)"<<" ";
    file.width(12); file<<"Vertex_X_N(Lead)"<<" ";
    file.width(12); file<<"Vertex_X_N(Other)"<<" ";
    file<<std::endl;

    for (unsigned int i = 0; i < sb.Vertex_X_nData.size(); ++i){
        file.width(12); file<<i<<" ";
        file.width(12); file<<sb.Vertex_X_nData[i]<<" ";
        file.width(12); file<<sb.Vertex_X_nMC[i]<<" ";
        file.width(12); file<<sb.Vertex_X_nHelium[i]<<" ";
        file.width(12); file<<sb.Vertex_X_nAluminium[i]<<" ";
        file.width(12); file<<sb.Vertex_X_nCarbon[i]<<" ";
        file.width(12); file<<sb.Vertex_X_nIron[i]<<" ";
        file.width(12); file<<sb.Vertex_X_nLead[i]<<" ";
        file.width(12); file<<sb.Vertex_X_nOther[i]<<" ";


        file<<std::endl;
    }


    file.width(12); file<<"Vertex_Y_Universe"<<" ";
    file.width(12); file<<"Vertex_Y_N(Data)"<<" ";
    file.width(12); file<<"Vertex_Y_N(MC)"<<" ";
    file.width(12); file<<"Vertex_Y_N(Helium)"<<" ";
    file.width(12); file<<"Vertex_Y_N(Aluminium)"<<" ";
    file.width(12); file<<"Vertex_Y_N(Carbon)"<<" ";
    file.width(12); file<<"Vertex_Y_N(Iron)"<<" ";
    file.width(12); file<<"Vertex_Y_N(Lead)"<<" ";
    file.width(12); file<<"Vertex_Y_N(Other)"<<" ";
    file<<std::endl;

    for (unsigned int i = 0; i < sb.Vertex_Y_nData.size(); ++i){
        file.width(12); file<<i<<" ";
        file.width(12); file<<sb.Vertex_Y_nData[i]<<" ";
        file.width(12); file<<sb.Vertex_Y_nMC[i]<<" ";
        file.width(12); file<<sb.Vertex_Y_nHelium[i]<<" ";
        file.width(12); file<<sb.Vertex_Y_nAluminium[i]<<" ";
        file.width(12); file<<sb.Vertex_Y_nCarbon[i]<<" ";
        file.width(12); file<<sb.Vertex_Y_nIron[i]<<" ";
        file.width(12); file<<sb.Vertex_Y_nLead[i]<<" ";
        file.width(12); file<<sb.Vertex_Y_nOther[i]<<" ";


        file<<std::endl;
    }


        file.width(12); file<<"Vertex_Z_Universe"<<" ";
        file.width(12); file<<"Vertex_Z_N(Data)"<<" ";
        file.width(12); file<<"Vertex_Z_N(MC)"<<" ";
        file.width(12); file<<"Vertex_Z_N(Helium)"<<" ";
        file.width(12); file<<"Vertex_Z_N(Aluminium)"<<" ";
        file.width(12); file<<"Vertex_Z_N(Carbon)"<<" ";
        file.width(12); file<<"Vertex_Z_N(Iron)"<<" ";
        file.width(12); file<<"Vertex_Z_N(Lead)"<<" ";
        file.width(12); file<<"Vertex_Z_N(Other)"<<" ";
        file<<std::endl;

        for (unsigned int i = 0; i < sb.Vertex_Z_nData.size(); ++i){
            file.width(12); file<<i<<" ";
            file.width(12); file<<sb.Vertex_Z_nData[i]<<" ";
            file.width(12); file<<sb.Vertex_Z_nMC[i]<<" ";
            file.width(12); file<<sb.Vertex_Z_nHelium[i]<<" ";
            file.width(12); file<<sb.Vertex_Z_nAluminium[i]<<" ";
            file.width(12); file<<sb.Vertex_Z_nCarbon[i]<<" ";
            file.width(12); file<<sb.Vertex_Z_nIron[i]<<" ";
            file.width(12); file<<sb.Vertex_Z_nLead[i]<<" ";
            file.width(12); file<<sb.Vertex_Z_nOther[i]<<" ";


            file<<std::endl;
        }




    std::cout<<"Writing "<<file_name<<std::endl;
    file.close();
}




void Helium_3CryoRegionsSideBandTool::WriteFitResults(std::string file_name)
{
    std::cout<<"Writing List of Weights for all Universes"<<std::endl;
    // Open Text File
    std::ofstream file;
    file.open(file_name.c_str());

    // Write Header
    file<<std::left;
    file.width(32); file<<"Error Band"<<" ";
    file.width(6);  file<<"Hist"<<" ";
    file.width(12); file<<"ChiSq Before Fit"<<" ";
    file.width(12); file<<"ChiSq After Fit"<<" ";
    file.width(12); file<<"wgt(Aluminium)"<<" ";
    file.width(12); file<<"err(Aluminium)"<<" ";
    file<<std::endl;

    /*for (unsigned int i = 0; i < ChiSq_after_fit.size(); ++i){
        file.width(32); file<< Helium_Full.err_bands_data_all_universes[i]<<" ";
        file.width(6); file<< Helium_Full.hist_ind_data_all_universes[i]<<" ";
        file.width(12); file<<ChiSq_before_fit[i]<<" ";
        file.width(12); file<<ChiSq_after_fit[i]<<" ";
        file.width(12); file<<wgt_Aluminium[i]<<" ";
        file.width(12); file<<err_Aluminium[i]<<" ";
        file<<std::endl;
    }
*/
    std::cout<<"Writing "<<file_name<<std::endl;
    file.close();
}


void Helium_3CryoRegionsSideBandTool::ApplyFitResults(Helium3SideBand &sb, double Alwgt)
{
    //std::cout<<"Applying Fit Result to "<<sb.name<<std::endl;
    // Clone Original Histograms

    sb.MnvH1D_Vertex_X_Helium[1] = (MnvH1D*) sb.MnvH1D_Vertex_X_Helium[0]->Clone();
    sb.MnvH1D_Vertex_X_Aluminium[1] = (MnvH1D*) sb.MnvH1D_Vertex_X_Aluminium[0]->Clone();
    sb.MnvH1D_Vertex_X_Carbon[1] = (MnvH1D*) sb.MnvH1D_Vertex_X_Carbon[0]->Clone();
    sb.MnvH1D_Vertex_X_Iron[1] = (MnvH1D*) sb.MnvH1D_Vertex_X_Iron[0]->Clone();
    sb.MnvH1D_Vertex_X_Lead[1] = (MnvH1D*) sb.MnvH1D_Vertex_X_Lead[0]->Clone();
    sb.MnvH1D_Vertex_X_Other[1] =(MnvH1D*) sb.MnvH1D_Vertex_X_Other[0]->Clone();

    // Clone Original Histograms
    sb.MnvH1D_Vertex_Y_Helium[1] = (MnvH1D*) sb.MnvH1D_Vertex_Y_Helium[0]->Clone();
    sb.MnvH1D_Vertex_Y_Aluminium[1] = (MnvH1D*) sb.MnvH1D_Vertex_Y_Aluminium[0]->Clone();
    sb.MnvH1D_Vertex_Y_Carbon[1] = (MnvH1D*) sb.MnvH1D_Vertex_Y_Carbon[0]->Clone();
    sb.MnvH1D_Vertex_Y_Iron[1] = (MnvH1D*) sb.MnvH1D_Vertex_Y_Iron[0]->Clone();
    sb.MnvH1D_Vertex_Y_Lead[1] = (MnvH1D*) sb.MnvH1D_Vertex_Y_Lead[0]->Clone();
    sb.MnvH1D_Vertex_Y_Other[1] =(MnvH1D*) sb.MnvH1D_Vertex_Y_Other[0]->Clone();

    // Clone Original Histograms
    sb.MnvH1D_Vertex_Z_Helium[1] = (MnvH1D*) sb.MnvH1D_Vertex_Z_Helium[0]->Clone();
    sb.MnvH1D_Vertex_Z_Aluminium[1] = (MnvH1D*) sb.MnvH1D_Vertex_Z_Aluminium[0]->Clone();
    sb.MnvH1D_Vertex_Z_Carbon[1] = (MnvH1D*) sb.MnvH1D_Vertex_Z_Carbon[0]->Clone();
    sb.MnvH1D_Vertex_Z_Iron[1] = (MnvH1D*) sb.MnvH1D_Vertex_Z_Iron[0]->Clone();
    sb.MnvH1D_Vertex_Z_Lead[1] = (MnvH1D*) sb.MnvH1D_Vertex_Z_Lead[0]->Clone();
    sb.MnvH1D_Vertex_Z_Other[1] = (MnvH1D*) sb.MnvH1D_Vertex_Z_Other[0]->Clone();

    // Clone Original Histograms
    sb.MnvH1D_Vertex_R_Helium[1] = (MnvH1D*) sb.MnvH1D_Vertex_R_Helium[0]->Clone();
    sb.MnvH1D_Vertex_R_Aluminium[1] = (MnvH1D*) sb.MnvH1D_Vertex_R_Aluminium[0]->Clone();
    sb.MnvH1D_Vertex_R_Carbon[1] = (MnvH1D*) sb.MnvH1D_Vertex_R_Carbon[0]->Clone();
    sb.MnvH1D_Vertex_R_Iron[1] = (MnvH1D*) sb.MnvH1D_Vertex_R_Iron[0]->Clone();
    sb.MnvH1D_Vertex_R_Lead[1] = (MnvH1D*) sb.MnvH1D_Vertex_R_Lead[0]->Clone();
    sb.MnvH1D_Vertex_R_Other[1] = (MnvH1D*) sb.MnvH1D_Vertex_R_Other[0]->Clone();

    // Scale
    //auto NXbins = sb.MnvH1D_Vertex_X_Aluminium[1]->GetNbinsX();
    //std::cout<<"applying scaler vertex X: "<< Alwgt<< std::endl;
    //std::cout<<"Checking bins  = " << NXbins<<std::endl;
    sb.MnvH1D_Vertex_X_Aluminium[1]->Scale(Alwgt);


    //auto NYbins = sb.MnvH1D_Vertex_Y_Aluminium[1]->GetNbinsX();
    //std::cout<<"applying scaler vertex Y: "<< Alwgt<< std::endl;
    //std::cout<<"Checking bins  = " << NYbins<<std::endl;
    sb.MnvH1D_Vertex_Y_Aluminium[1]->Scale(Alwgt);


    //auto NZbins = sb.MnvH1D_Vertex_Z_Aluminium[1]->GetNbinsX();
    //std::cout<<"applying scaler vertex Z: "<< Alwgt<< std::endl;
    //std::cout<<"Checking bins  = " << NZbins<<std::endl;
    sb.MnvH1D_Vertex_Z_Aluminium[1]->Scale(Alwgt);

    //auto NRbins = sb.MnvH1D_Vertex_R_Aluminium[1]->GetNbinsX();
    //std::cout<<"applying scaler vertex R: "<< Alwgt<< std::endl;
    //std::cout<<"Checking bins  = " << NRbins<<std::endl;
    sb.MnvH1D_Vertex_R_Aluminium[1]->Scale(Alwgt);


    ApplyFitResults(sb.muon_PT, Alwgt);
    ApplyFitResults(sb.muon_PZ, Alwgt);
    ApplyFitResults(sb.muon_theta, Alwgt);
    ApplyFitResults(sb.muon_E, Alwgt);
    ApplyFitResults(sb.DistancetoEdge, Alwgt);
    ApplyFitResults(sb.muon_doca, Alwgt);
    ApplyFitResults(sb.SecTrk_doca, Alwgt);
    ApplyFitResults(sb.TrackLength, Alwgt);
    ApplyFitResults(sb.DistancetoUpstreamCap, Alwgt);
    ApplyFitResults(sb.DistancetoDownstreamCap, Alwgt);
    ApplyFitResults(sb.DistancetoUpstreamCap_RCut, Alwgt);
    ApplyFitResults(sb.DistancetoDownstreamCap_RCut, Alwgt);
    ApplyFitResults(sb.Vertex_Z_RCut, Alwgt);
    ApplyFitResults(sb.Vertex_X_RCut, Alwgt);
    ApplyFitResults(sb.Vertex_Y_RCut, Alwgt);
    ApplyFitResults(sb.Vertex_R_RCut, Alwgt);


  }
//=======================================================================================
void Helium_3CryoRegionsSideBandTool::ApplyFitResultsNSideBand(HeliumNSideBand &sb, double Alwgt)
{
      //std::cout<<"Applying Fit Result to "<<sb.name<<std::endl;
      // Clone Original Histograms

      sb.MnvH1D_Vertex_X_Helium[2] = (MnvH1D*) sb.MnvH1D_Vertex_X_Helium[0]->Clone();
      sb.MnvH1D_Vertex_X_Aluminium[2] = (MnvH1D*) sb.MnvH1D_Vertex_X_Aluminium[0]->Clone();
      sb.MnvH1D_Vertex_X_Carbon[2] = (MnvH1D*) sb.MnvH1D_Vertex_X_Carbon[0]->Clone();
      sb.MnvH1D_Vertex_X_Iron[2] = (MnvH1D*) sb.MnvH1D_Vertex_X_Iron[0]->Clone();
      sb.MnvH1D_Vertex_X_Lead[2] = (MnvH1D*) sb.MnvH1D_Vertex_X_Lead[0]->Clone();
      sb.MnvH1D_Vertex_X_Other[2] =(MnvH1D*) sb.MnvH1D_Vertex_X_Other[0]->Clone();

      // Clone Original Histograms
      sb.MnvH1D_Vertex_Y_Helium[2] = (MnvH1D*) sb.MnvH1D_Vertex_Y_Helium[0]->Clone();
      sb.MnvH1D_Vertex_Y_Aluminium[2] = (MnvH1D*) sb.MnvH1D_Vertex_Y_Aluminium[0]->Clone();
      sb.MnvH1D_Vertex_Y_Carbon[2] = (MnvH1D*) sb.MnvH1D_Vertex_Y_Carbon[0]->Clone();
      sb.MnvH1D_Vertex_Y_Iron[2] = (MnvH1D*) sb.MnvH1D_Vertex_Y_Iron[0]->Clone();
      sb.MnvH1D_Vertex_Y_Lead[2] = (MnvH1D*) sb.MnvH1D_Vertex_Y_Lead[0]->Clone();
      sb.MnvH1D_Vertex_Y_Other[2] =(MnvH1D*) sb.MnvH1D_Vertex_Y_Other[0]->Clone();

      // Clone Original Histograms
      sb.MnvH1D_Vertex_Z_Helium[2] = (MnvH1D*) sb.MnvH1D_Vertex_Z_Helium[0]->Clone();
      sb.MnvH1D_Vertex_Z_Aluminium[2] = (MnvH1D*) sb.MnvH1D_Vertex_Z_Aluminium[0]->Clone();
      sb.MnvH1D_Vertex_Z_Carbon[2] = (MnvH1D*) sb.MnvH1D_Vertex_Z_Carbon[0]->Clone();
      sb.MnvH1D_Vertex_Z_Iron[2] = (MnvH1D*) sb.MnvH1D_Vertex_Z_Iron[0]->Clone();
      sb.MnvH1D_Vertex_Z_Lead[2] = (MnvH1D*) sb.MnvH1D_Vertex_Z_Lead[0]->Clone();
      sb.MnvH1D_Vertex_Z_Other[2] = (MnvH1D*) sb.MnvH1D_Vertex_Z_Other[0]->Clone();

      // Clone Original Histograms
      sb.MnvH1D_Vertex_R_Helium[2] = (MnvH1D*) sb.MnvH1D_Vertex_R_Helium[0]->Clone();
      sb.MnvH1D_Vertex_R_Aluminium[2] = (MnvH1D*) sb.MnvH1D_Vertex_R_Aluminium[0]->Clone();
      sb.MnvH1D_Vertex_R_Carbon[2] = (MnvH1D*) sb.MnvH1D_Vertex_R_Carbon[0]->Clone();
      sb.MnvH1D_Vertex_R_Iron[2] = (MnvH1D*) sb.MnvH1D_Vertex_R_Iron[0]->Clone();
      sb.MnvH1D_Vertex_R_Lead[2] = (MnvH1D*) sb.MnvH1D_Vertex_R_Lead[0]->Clone();
      sb.MnvH1D_Vertex_R_Other[2] = (MnvH1D*) sb.MnvH1D_Vertex_R_Other[0]->Clone();

      // Scale
      //auto NXbins = sb.MnvH1D_Vertex_X_Aluminium[1]->GetNbinsX();
      //std::cout<<"applying scaler vertex X: "<< Alwgt<< std::endl;
      //std::cout<<"Checking bins  = " << NXbins<<std::endl;
      sb.MnvH1D_Vertex_X_Aluminium[2]->Scale(Alwgt);


      //auto NYbins = sb.MnvH1D_Vertex_Y_Aluminium[1]->GetNbinsX();
      //std::cout<<"applying scaler vertex Y: "<< Alwgt<< std::endl;
      //std::cout<<"Checking bins  = " << NYbins<<std::endl;
      sb.MnvH1D_Vertex_Y_Aluminium[2]->Scale(Alwgt);


      //auto NZbins = sb.MnvH1D_Vertex_Z_Aluminium[1]->GetNbinsX();
      //std::cout<<"applying scaler vertex Z: "<< Alwgt<< std::endl;
      //std::cout<<"Checking bins  = " << NZbins<<std::endl;
      sb.MnvH1D_Vertex_Z_Aluminium[2]->Scale(Alwgt);

      //auto NRbins = sb.MnvH1D_Vertex_R_Aluminium[1]->GetNbinsX();
      //std::cout<<"applying scaler vertex R: "<< Alwgt<< std::endl;
      //std::cout<<"Checking bins  = " << NRbins<<std::endl;
      sb.MnvH1D_Vertex_R_Aluminium[2]->Scale(Alwgt);


      ApplyFitResults(sb.muon_PT, Alwgt);
      ApplyFitResults(sb.muon_PZ, Alwgt);
      ApplyFitResults(sb.muon_theta, Alwgt);
      ApplyFitResults(sb.muon_E, Alwgt);
      ApplyFitResults(sb.muon_doca, Alwgt);
      ApplyFitResults(sb.DistancetoEdge, Alwgt);
      ApplyFitResults(sb.SecTrk_doca, Alwgt);
      ApplyFitResults(sb.TrackLength, Alwgt);

    }
//=======================================================================================
void Helium_3CryoRegionsSideBandTool::ApplyFitResults_toFitParsOnly(Helium3SideBand &sb, double Alwgt)
{
      //std::cout<<"Applying Fit Result to "<<sb.name<<std::endl;
      // Clone Original Histograms
    /*  sb.MnvH1D_Vertex_X_Helium[1] = new MnvH1D (         *sb.MnvH1D_Vertex_X_Helium[0]);
      sb.MnvH1D_Vertex_X_Aluminium[1] = new MnvH1D (      *sb.MnvH1D_Vertex_X_Aluminium[0]);
      sb.MnvH1D_Vertex_X_Carbon[1] = new MnvH1D (         *sb.MnvH1D_Vertex_X_Carbon[0]);
      sb.MnvH1D_Vertex_X_Iron[1] = new MnvH1D (           *sb.MnvH1D_Vertex_X_Iron[0]);
      sb.MnvH1D_Vertex_X_Lead[1] = new MnvH1D (           *sb.MnvH1D_Vertex_X_Lead[0]);
      sb.MnvH1D_Vertex_X_Other[1] = new MnvH1D (          *sb.MnvH1D_Vertex_X_Other[0]);

      // Clone Original Histograms
      sb.MnvH1D_Vertex_Y_Helium[1] = new MnvH1D (         *sb.MnvH1D_Vertex_Y_Helium[0]);
      sb.MnvH1D_Vertex_Y_Aluminium[1] = new MnvH1D (      *sb.MnvH1D_Vertex_Y_Aluminium[0]);
      sb.MnvH1D_Vertex_Y_Carbon[1] = new MnvH1D (         *sb.MnvH1D_Vertex_Y_Carbon[0]);
      sb.MnvH1D_Vertex_Y_Iron[1] = new MnvH1D (           *sb.MnvH1D_Vertex_Y_Iron[0]);
      sb.MnvH1D_Vertex_Y_Lead[1] = new MnvH1D (           *sb.MnvH1D_Vertex_Y_Lead[0]);
      sb.MnvH1D_Vertex_Y_Other[1] = new MnvH1D (          *sb.MnvH1D_Vertex_Y_Other[0]);

      // Clone Original Histograms
      sb.MnvH1D_Vertex_Z_Helium[1] = new MnvH1D (         *sb.MnvH1D_Vertex_Z_Helium[0]);
      sb.MnvH1D_Vertex_Z_Aluminium[1] = new MnvH1D (      *sb.MnvH1D_Vertex_Z_Aluminium[0]);
      sb.MnvH1D_Vertex_Z_Carbon[1] = new MnvH1D (         *sb.MnvH1D_Vertex_Z_Carbon[0]);
      sb.MnvH1D_Vertex_Z_Iron[1] = new MnvH1D (           *sb.MnvH1D_Vertex_Z_Iron[0]);
      sb.MnvH1D_Vertex_Z_Lead[1] = new MnvH1D (           *sb.MnvH1D_Vertex_Z_Lead[0]);
      sb.MnvH1D_Vertex_Z_Other[1] = new MnvH1D (          *sb.MnvH1D_Vertex_Z_Other[0]);

      // Clone Original Histograms
      sb.MnvH1D_Vertex_R_Helium[1] = new MnvH1D (         *sb.MnvH1D_Vertex_R_Helium[0]);
      sb.MnvH1D_Vertex_R_Aluminium[1] = new MnvH1D (      *sb.MnvH1D_Vertex_R_Aluminium[0]);
      sb.MnvH1D_Vertex_R_Carbon[1] = new MnvH1D (         *sb.MnvH1D_Vertex_R_Carbon[0]);
      sb.MnvH1D_Vertex_R_Iron[1] = new MnvH1D (           *sb.MnvH1D_Vertex_R_Iron[0]);
      sb.MnvH1D_Vertex_R_Lead[1] = new MnvH1D (           *sb.MnvH1D_Vertex_R_Lead[0]);
      sb.MnvH1D_Vertex_R_Other[1] = new MnvH1D (          *sb.MnvH1D_Vertex_R_Other[0]);
*/

sb.MnvH1D_Vertex_X_Helium[1] = (MnvH1D*) sb.MnvH1D_Vertex_X_Helium[0]->Clone();
sb.MnvH1D_Vertex_X_Aluminium[1] = (MnvH1D*) sb.MnvH1D_Vertex_X_Aluminium[0]->Clone();
sb.MnvH1D_Vertex_X_Carbon[1] = (MnvH1D*) sb.MnvH1D_Vertex_X_Carbon[0]->Clone();
sb.MnvH1D_Vertex_X_Iron[1] = (MnvH1D*) sb.MnvH1D_Vertex_X_Iron[0]->Clone();
sb.MnvH1D_Vertex_X_Lead[1] = (MnvH1D*) sb.MnvH1D_Vertex_X_Lead[0]->Clone();
sb.MnvH1D_Vertex_X_Other[1] =(MnvH1D*) sb.MnvH1D_Vertex_X_Other[0]->Clone();

// Clone Original Histograms
sb.MnvH1D_Vertex_Y_Helium[1] = (MnvH1D*) sb.MnvH1D_Vertex_Y_Helium[0]->Clone();
sb.MnvH1D_Vertex_Y_Aluminium[1] = (MnvH1D*) sb.MnvH1D_Vertex_Y_Aluminium[0]->Clone();
sb.MnvH1D_Vertex_Y_Carbon[1] = (MnvH1D*) sb.MnvH1D_Vertex_Y_Carbon[0]->Clone();
sb.MnvH1D_Vertex_Y_Iron[1] = (MnvH1D*) sb.MnvH1D_Vertex_Y_Iron[0]->Clone();
sb.MnvH1D_Vertex_Y_Lead[1] = (MnvH1D*) sb.MnvH1D_Vertex_Y_Lead[0]->Clone();
sb.MnvH1D_Vertex_Y_Other[1] =(MnvH1D*) sb.MnvH1D_Vertex_Y_Other[0]->Clone();

// Clone Original Histograms
sb.MnvH1D_Vertex_Z_Helium[1] = (MnvH1D*) sb.MnvH1D_Vertex_Z_Helium[0]->Clone();
sb.MnvH1D_Vertex_Z_Aluminium[1] = (MnvH1D*) sb.MnvH1D_Vertex_Z_Aluminium[0]->Clone();
sb.MnvH1D_Vertex_Z_Carbon[1] = (MnvH1D*) sb.MnvH1D_Vertex_Z_Carbon[0]->Clone();
sb.MnvH1D_Vertex_Z_Iron[1] = (MnvH1D*) sb.MnvH1D_Vertex_Z_Iron[0]->Clone();
sb.MnvH1D_Vertex_Z_Lead[1] = (MnvH1D*) sb.MnvH1D_Vertex_Z_Lead[0]->Clone();
sb.MnvH1D_Vertex_Z_Other[1] = (MnvH1D*) sb.MnvH1D_Vertex_Z_Other[0]->Clone();

// Clone Original Histograms
sb.MnvH1D_Vertex_R_Helium[1] = (MnvH1D*) sb.MnvH1D_Vertex_R_Helium[0]->Clone();
sb.MnvH1D_Vertex_R_Aluminium[1] = (MnvH1D*) sb.MnvH1D_Vertex_R_Aluminium[0]->Clone();
sb.MnvH1D_Vertex_R_Carbon[1] = (MnvH1D*) sb.MnvH1D_Vertex_R_Carbon[0]->Clone();
sb.MnvH1D_Vertex_R_Iron[1] = (MnvH1D*) sb.MnvH1D_Vertex_R_Iron[0]->Clone();
sb.MnvH1D_Vertex_R_Lead[1] = (MnvH1D*) sb.MnvH1D_Vertex_R_Lead[0]->Clone();
sb.MnvH1D_Vertex_R_Other[1] = (MnvH1D*) sb.MnvH1D_Vertex_R_Other[0]->Clone();

      // Scale
      //auto NXbins = sb.MnvH1D_Vertex_X_Aluminium[1]->GetNbinsX();
      //std::cout<<"applying scaler vertex X: "<< Alwgt<< std::endl;
      //std::cout<<"Checking bins  = " << NXbins<<std::endl;
      sb.MnvH1D_Vertex_X_Aluminium[1]->Scale(Alwgt);


      //auto NYbins = sb.MnvH1D_Vertex_Y_Aluminium[1]->GetNbinsX();
      //std::cout<<"applying scaler vertex Y: "<< Alwgt<< std::endl;
      //std::cout<<"Checking bins  = " << NYbins<<std::endl;
      sb.MnvH1D_Vertex_Y_Aluminium[1]->Scale(Alwgt);


      //auto NZbins = sb.MnvH1D_Vertex_Z_Aluminium[1]->GetNbinsX();
      //std::cout<<"applying scaler vertex Z: "<< Alwgt<< std::endl;
      //std::cout<<"Checking bins  = " << NZbins<<std::endl;
      sb.MnvH1D_Vertex_Z_Aluminium[1]->Scale(Alwgt);

      //auto NRbins = sb.MnvH1D_Vertex_R_Aluminium[1]->GetNbinsX();
      //std::cout<<"applying scaler vertex R: "<< Alwgt<< std::endl;
      //std::cout<<"Checking bins  = " << NRbins<<std::endl;
      sb.MnvH1D_Vertex_R_Aluminium[1]->Scale(Alwgt);


    }
//=======================================================================================
void Helium_3CryoRegionsSideBandTool::ApplyFitResults(Helium3SideBand &sb, double Alwgt, double Hewgt)
{
      //std::cout<<"Applying Fit Result to "<<sb.name<<std::endl;
      // Clone Original Histograms
      sb.MnvH1D_Vertex_X_Helium[1] = (MnvH1D*) sb.MnvH1D_Vertex_X_Helium[0]->Clone(); // new MnvH1D (         *sb.MnvH1D_Vertex_X_Helium[0]);
      sb.MnvH1D_Vertex_X_Aluminium[1] = (MnvH1D*) sb.MnvH1D_Vertex_X_Aluminium[0]->Clone(); //new MnvH1D (      *sb.MnvH1D_Vertex_X_Aluminium[0]);
      sb.MnvH1D_Vertex_X_Carbon[1] = (MnvH1D*) sb.MnvH1D_Vertex_X_Carbon[0]->Clone(); //new MnvH1D (         *sb.MnvH1D_Vertex_X_Carbon[0]);
      sb.MnvH1D_Vertex_X_Iron[1] = (MnvH1D*) sb.MnvH1D_Vertex_X_Iron[0]->Clone(); //new MnvH1D (           *sb.MnvH1D_Vertex_X_Iron[0]);
      sb.MnvH1D_Vertex_X_Lead[1] = (MnvH1D*) sb.MnvH1D_Vertex_X_Lead[0]->Clone(); //new MnvH1D (           *sb.MnvH1D_Vertex_X_Lead[0]);
      sb.MnvH1D_Vertex_X_Other[1] =(MnvH1D*) sb.MnvH1D_Vertex_X_Other[0]->Clone(); // new MnvH1D (          *sb.MnvH1D_Vertex_X_Other[0]);

      // Clone Original Histograms
      sb.MnvH1D_Vertex_Y_Helium[1] = (MnvH1D*) sb.MnvH1D_Vertex_Y_Helium[0]->Clone(); //new MnvH1D (         *sb.MnvH1D_Vertex_Y_Helium[0]);
      sb.MnvH1D_Vertex_Y_Aluminium[1] = (MnvH1D*) sb.MnvH1D_Vertex_Y_Aluminium[0]->Clone();//new MnvH1D (      *sb.MnvH1D_Vertex_Y_Aluminium[0]);
      sb.MnvH1D_Vertex_Y_Carbon[1] = (MnvH1D*) sb.MnvH1D_Vertex_Y_Carbon[0]->Clone();//new MnvH1D (         *sb.MnvH1D_Vertex_Y_Carbon[0]);
      sb.MnvH1D_Vertex_Y_Iron[1] = (MnvH1D*) sb.MnvH1D_Vertex_Y_Iron[0]->Clone();//new MnvH1D (           *sb.MnvH1D_Vertex_Y_Iron[0]);
      sb.MnvH1D_Vertex_Y_Lead[1] = (MnvH1D*) sb.MnvH1D_Vertex_Y_Lead[0]->Clone();//new MnvH1D (           *sb.MnvH1D_Vertex_Y_Lead[0]);
      sb.MnvH1D_Vertex_Y_Other[1] =(MnvH1D*) sb.MnvH1D_Vertex_Y_Other[0]->Clone(); // new MnvH1D (          *sb.MnvH1D_Vertex_Y_Other[0]);

      // Clone Original Histograms
      sb.MnvH1D_Vertex_Z_Helium[1] = (MnvH1D*) sb.MnvH1D_Vertex_Z_Helium[0]->Clone(); //new MnvH1D (         *sb.MnvH1D_Vertex_Z_Helium[0]);
      sb.MnvH1D_Vertex_Z_Aluminium[1] = (MnvH1D*) sb.MnvH1D_Vertex_Z_Aluminium[0]->Clone();//new MnvH1D (      *sb.MnvH1D_Vertex_Z_Aluminium[0]);
      sb.MnvH1D_Vertex_Z_Carbon[1] = (MnvH1D*) sb.MnvH1D_Vertex_Z_Carbon[0]->Clone();//new MnvH1D (         *sb.MnvH1D_Vertex_Z_Carbon[0]);
      sb.MnvH1D_Vertex_Z_Iron[1] = (MnvH1D*) sb.MnvH1D_Vertex_Z_Iron[0]->Clone();//new MnvH1D (           *sb.MnvH1D_Vertex_Z_Iron[0]);
      sb.MnvH1D_Vertex_Z_Lead[1] = (MnvH1D*) sb.MnvH1D_Vertex_Z_Lead[0]->Clone();//new MnvH1D (           *sb.MnvH1D_Vertex_Z_Lead[0]);
      sb.MnvH1D_Vertex_Z_Other[1] = (MnvH1D*) sb.MnvH1D_Vertex_Z_Other[0]->Clone(); //new MnvH1D (          *sb.MnvH1D_Vertex_Z_Other[0]);

      // Clone Original Histograms
      sb.MnvH1D_Vertex_R_Helium[1] = (MnvH1D*) sb.MnvH1D_Vertex_R_Helium[0]->Clone(); //new MnvH1D (         *sb.MnvH1D_Vertex_R_Helium[0]);
      sb.MnvH1D_Vertex_R_Aluminium[1] = (MnvH1D*) sb.MnvH1D_Vertex_R_Aluminium[0]->Clone();//new MnvH1D (      *sb.MnvH1D_Vertex_R_Aluminium[0]);
      sb.MnvH1D_Vertex_R_Carbon[1] = (MnvH1D*) sb.MnvH1D_Vertex_R_Carbon[0]->Clone();//new MnvH1D (         *sb.MnvH1D_Vertex_R_Carbon[0]);
      sb.MnvH1D_Vertex_R_Iron[1] = (MnvH1D*) sb.MnvH1D_Vertex_R_Iron[0]->Clone();//new MnvH1D (           *sb.MnvH1D_Vertex_R_Iron[0]);
      sb.MnvH1D_Vertex_R_Lead[1] = (MnvH1D*) sb.MnvH1D_Vertex_R_Lead[0]->Clone();//new MnvH1D (           *sb.MnvH1D_Vertex_R_Lead[0]);
      sb.MnvH1D_Vertex_R_Other[1] = (MnvH1D*) sb.MnvH1D_Vertex_R_Other[0]->Clone(); //new MnvH1D (          *sb.MnvH1D_Vertex_R_Other[0]);

      // Scale

      //std::cout<<"applying scaler vertex X: "<< Alwgt<< std::endl;
      //std::cout<<"Checking bins  = " << NXbins<<std::endl;
      sb.MnvH1D_Vertex_X_Aluminium[1]->Scale(Alwgt);
      sb.MnvH1D_Vertex_X_Helium[1]->Scale(Hewgt);

      //std::cout<<"applying scaler vertex Y: "<< Alwgt<< std::endl;
      //std::cout<<"Checking bins  = " << NYbins<<std::endl;
      sb.MnvH1D_Vertex_Y_Aluminium[1]->Scale(Alwgt);
      sb.MnvH1D_Vertex_Y_Helium[1]->Scale(Hewgt);

      //std::cout<<"applying scaler vertex Z: "<< Alwgt<< std::endl;
      //std::cout<<"Checking bins  = " << NZbins<<std::endl;
      sb.MnvH1D_Vertex_Z_Aluminium[1]->Scale(Alwgt);
      sb.MnvH1D_Vertex_Z_Helium[1]->Scale(Hewgt);

      //std::cout<<"applying scaler vertex R: "<< Alwgt<< std::endl;
      //std::cout<<"Checking bins  = " << NRbins<<std::endl;
      sb.MnvH1D_Vertex_R_Aluminium[1]->Scale(Alwgt);
      sb.MnvH1D_Vertex_R_Helium[1]->Scale(Hewgt);




      ApplyFitResults(sb.muon_PT,        Alwgt, Hewgt);
      ApplyFitResults(sb.muon_PZ,        Alwgt, Hewgt);
      ApplyFitResults(sb.muon_theta,     Alwgt, Hewgt);
      ApplyFitResults(sb.muon_E,         Alwgt, Hewgt);
      ApplyFitResults(sb.DistancetoEdge, Alwgt, Hewgt);
      ApplyFitResults(sb.muon_doca, Alwgt, Hewgt);
      ApplyFitResults(sb.SecTrk_doca, Alwgt, Hewgt);
      ApplyFitResults(sb.TrackLength, Alwgt, Hewgt);
      ApplyFitResults(sb.DistancetoUpstreamCap, Alwgt, Hewgt);
      ApplyFitResults(sb.DistancetoDownstreamCap, Alwgt, Hewgt);
      ApplyFitResults(sb.DistancetoUpstreamCap_RCut, Alwgt, Hewgt);
      ApplyFitResults(sb.DistancetoDownstreamCap_RCut, Alwgt, Hewgt);
      ApplyFitResults(sb.Vertex_Z_RCut, Alwgt, Hewgt);
      ApplyFitResults(sb.Vertex_X_RCut, Alwgt, Hewgt);
      ApplyFitResults(sb.Vertex_Y_RCut, Alwgt, Hewgt);
      ApplyFitResults(sb.Vertex_R_RCut, Alwgt, Hewgt);



    }
//=======================================================================================
void Helium_3CryoRegionsSideBandTool::ApplyFitResults(XSec_Var3band &xsec_var , double Alwgt)
{
    // Clone Original Histograms
    xsec_var.MnvH1D_Helium[1] =  (MnvH1D*) xsec_var.MnvH1D_Helium[0]->Clone();   //new MnvH1D (*xsec_var.MnvH1D_Helium[0]);
    xsec_var.MnvH1D_Aluminium[1] =  (MnvH1D*) xsec_var.MnvH1D_Aluminium[0]->Clone();   //new MnvH1D (*xsec_var.MnvH1D_Aluminium[0]);
    xsec_var.MnvH1D_Carbon[1] =  (MnvH1D*) xsec_var.MnvH1D_Carbon[0]->Clone();   //new MnvH1D (*xsec_var.MnvH1D_Carbon[0]);
    xsec_var.MnvH1D_Lead[1] =  (MnvH1D*) xsec_var.MnvH1D_Lead[0]->Clone();   //new MnvH1D (*xsec_var.MnvH1D_Lead[0]);
    xsec_var.MnvH1D_Iron[1] =  (MnvH1D*) xsec_var.MnvH1D_Iron[0]->Clone();   //new MnvH1D (*xsec_var.MnvH1D_Iron[0]);
    xsec_var.MnvH1D_Other[1] = (MnvH1D*) xsec_var.MnvH1D_Other[0]->Clone();   // new MnvH1D (*xsec_var.MnvH1D_Other[0]);

    // Scale
    xsec_var.MnvH1D_Aluminium[1]->Scale(Alwgt);
}
//=======================================================================================
void Helium_3CryoRegionsSideBandTool::ApplyFitResults(XSec_VarNband &xsec_var , double Alwgt)
{
    // Clone Original Histograms
    xsec_var.MnvH1D_Helium[1] =  (MnvH1D*) xsec_var.MnvH1D_Helium[0]->Clone();   //new MnvH1D (*xsec_var.MnvH1D_Helium[0]);
    xsec_var.MnvH1D_Aluminium[1] =  (MnvH1D*) xsec_var.MnvH1D_Aluminium[0]->Clone();   //new MnvH1D (*xsec_var.MnvH1D_Aluminium[0]);
    xsec_var.MnvH1D_Carbon[1] =  (MnvH1D*) xsec_var.MnvH1D_Carbon[0]->Clone();   //new MnvH1D (*xsec_var.MnvH1D_Carbon[0]);
    xsec_var.MnvH1D_Lead[1] =  (MnvH1D*) xsec_var.MnvH1D_Lead[0]->Clone();   //new MnvH1D (*xsec_var.MnvH1D_Lead[0]);
    xsec_var.MnvH1D_Iron[1] =  (MnvH1D*) xsec_var.MnvH1D_Iron[0]->Clone();   //new MnvH1D (*xsec_var.MnvH1D_Iron[0]);
    xsec_var.MnvH1D_Other[1] = (MnvH1D*) xsec_var.MnvH1D_Other[0]->Clone();   // new MnvH1D (*xsec_var.MnvH1D_Other[0]);

    // Scale
    xsec_var.MnvH1D_Aluminium[1]->Scale(Alwgt);
}
//=======================================================================================
void Helium_3CryoRegionsSideBandTool::ApplyFitResults(XSec_Var3band &xsec_var , double Alwgt, double Hewgt)
{
    // Clone Original Histograms
    xsec_var.MnvH1D_Helium[1] = new MnvH1D (*xsec_var.MnvH1D_Helium[0]);
    xsec_var.MnvH1D_Aluminium[1] = new MnvH1D (*xsec_var.MnvH1D_Aluminium[0]);
    xsec_var.MnvH1D_Carbon[1] = new MnvH1D (*xsec_var.MnvH1D_Carbon[0]);
    xsec_var.MnvH1D_Lead[1] = new MnvH1D (*xsec_var.MnvH1D_Lead[0]);
    xsec_var.MnvH1D_Iron[1] = new MnvH1D (*xsec_var.MnvH1D_Iron[0]);
    xsec_var.MnvH1D_Other[1] = new MnvH1D (*xsec_var.MnvH1D_Other[0]);

    // Scale
    xsec_var.MnvH1D_Aluminium[1]->Scale(Alwgt);
    xsec_var.MnvH1D_Helium[1]->Scale(Hewgt);
}
//=======================================================================================
void Helium_3CryoRegionsSideBandTool::ApplyFitResultsNSideBand(CryoRegion_HeliumNSideBand_Map &RegionMap, std::vector<double> Alwgt_vector)
{
  int vector_count=0;
  for(auto Region : CryoRegion14_vector){
    ApplyFitResultsNSideBand(RegionMap[Region],Alwgt_vector.at(vector_count));
    vector_count++;
  }
}
//=======================================================================================
void Helium_3CryoRegionsSideBandTool::ApplyFitResultsNSideBand_Empty(){
  ApplyFitResultsNSideBand(CryoRegionMap_Empty, wgt_Aluminium);
}
//=======================================================================================




void Helium_3CryoRegionsSideBandTool::ApplyFitToBands(
  Helium3SideBand &sb_region1,
   Helium3SideBand &sb_region2,
   Helium3SideBand &sb_region3,
   Helium3SideBand &sb_region4,
   std::vector<double> Alwgt_vector){
     std::cout<<"Order of Fit Weights"<<std::endl;
     std::cout<<"USCAP = "<< Alwgt_vector.at(0)<<std::endl;
     std::cout<<"Barrel = "<< Alwgt_vector.at(1)<<std::endl;
     std::cout<<"DSCap = "<< Alwgt_vector.at(2)<<std::endl;
     std::cout<<"DSConcave = "<< Alwgt_vector.at(3)<<std::endl;

  ApplyFitResults(sb_region1, Alwgt_vector.at(0));
  ApplyFitResults(sb_region2, Alwgt_vector.at(1));
  ApplyFitResults(sb_region3, Alwgt_vector.at(2));
  ApplyFitResults(sb_region4, Alwgt_vector.at(3));
}

void Helium_3CryoRegionsSideBandTool::ApplyFitResults_Xsecvar(Helium3SideBand &sb , double Alwgt){

  ApplyFitResults(sb.muon_PT , Alwgt);
  ApplyFitResults(sb.muon_PZ , Alwgt);
  ApplyFitResults(sb.muon_theta , Alwgt);
  ApplyFitResults(sb.muon_E , Alwgt);
  ApplyFitResults(sb.DistancetoEdge , Alwgt);
  ApplyFitResults(sb.muon_doca , Alwgt);
  ApplyFitResults(sb.SecTrk_doca , Alwgt);
  ApplyFitResults(sb.TrackLength , Alwgt);
  ApplyFitResults(sb.DistancetoUpstreamCap, Alwgt);
  ApplyFitResults(sb.DistancetoDownstreamCap, Alwgt);
  ApplyFitResults(sb.DistancetoUpstreamCap_RCut, Alwgt);
  ApplyFitResults(sb.DistancetoDownstreamCap_RCut, Alwgt);
  ApplyFitResults(sb.Vertex_Z_RCut, Alwgt);
  ApplyFitResults(sb.Vertex_X_RCut, Alwgt);
  ApplyFitResults(sb.Vertex_Y_RCut, Alwgt);
  ApplyFitResults(sb.Vertex_R_RCut, Alwgt);



}

void Helium_3CryoRegionsSideBandTool::ApplyFitResults_Resolution(Helium3SideBand &sb , double Alwgt){

    ApplyFitResults(sb.Vertex_X_Resolution, Alwgt);
    ApplyFitResults(sb.Vertex_Y_Resolution, Alwgt);
    ApplyFitResults(sb.Vertex_Z_Resolution, Alwgt);
    ApplyFitResults(sb.Vertex_R_Resolution, Alwgt);

}
void Helium_3CryoRegionsSideBandTool::ApplyFitToResolution_Bands(
  Helium3SideBand &sb_region1,
   Helium3SideBand &sb_region2,
   Helium3SideBand &sb_region3,
   Helium3SideBand &sb_region4,
   std::vector<double> Alwgt_vector){
  ApplyFitResults_Resolution(sb_region1, Alwgt_vector.at(0));
  ApplyFitResults_Resolution(sb_region2, Alwgt_vector.at(1));
  ApplyFitResults_Resolution(sb_region3, Alwgt_vector.at(2));
  ApplyFitResults_Resolution(sb_region4, Alwgt_vector.at(3));
}

void Helium_3CryoRegionsSideBandTool::ApplyFitToBands(Helium3SideBand &sb_upstreamCap,
   Helium3SideBand &sb_barrel,Helium3SideBand &sb_downstreamCap,Helium3SideBand &sb_downstreamconcaveCap,
   std::vector<double> Alwgt_vector, std::vector<double> Hewgt_vector){
  ApplyFitResults(sb_upstreamCap,          Alwgt_vector.at(0) , Hewgt_vector.at(0));
  ApplyFitResults(sb_barrel,               Alwgt_vector.at(1) , Hewgt_vector.at(1));
  ApplyFitResults(sb_downstreamCap,        Alwgt_vector.at(2) , Hewgt_vector.at(2));
  ApplyFitResults(sb_downstreamconcaveCap, Alwgt_vector.at(3) , Hewgt_vector.at(3));
}





void Helium_3CryoRegionsSideBandTool::ApplyFitResults_Int_Full_Empty(XSec_Var3band &xsec_var_Full_Empty,
  XSec_Var3band &xsec_var_Full, XSec_Var3band &xsec_var_Empty)
{
    // Clone Original Histograms
    xsec_var_Full_Empty.MnvH1D_Helium[1] =  (MnvH1D*) xsec_var_Full.MnvH1D_Helium[1]->Clone(); // = new MnvH1D (*xsec_var_Full.MnvH1D_Helium[0]);
    xsec_var_Full_Empty.MnvH1D_Aluminium[1] = (MnvH1D*)xsec_var_Full.MnvH1D_Aluminium[1]->Clone(); // new MnvH1D (*xsec_var_Full.MnvH1D_Aluminium[0]);
    xsec_var_Full_Empty.MnvH1D_Carbon[1] = (MnvH1D*) xsec_var_Full.MnvH1D_Carbon[1]->Clone(); //new MnvH1D (*xsec_var_Full.MnvH1D_Carbon[0]);
    xsec_var_Full_Empty.MnvH1D_Lead[1] = (MnvH1D*) xsec_var_Full.MnvH1D_Lead[1]->Clone(); //new MnvH1D (*xsec_var_Full.MnvH1D_Lead[0]);
    xsec_var_Full_Empty.MnvH1D_Iron[1] = (MnvH1D*) xsec_var_Full.MnvH1D_Iron[1]->Clone(); //new MnvH1D (*xsec_var_Full.MnvH1D_Iron[0]);
    xsec_var_Full_Empty.MnvH1D_Other[1] = (MnvH1D*) xsec_var_Full.MnvH1D_Other[1]->Clone(); //new MnvH1D (*xsec_var_Full.MnvH1D_Other[0]);

    // Scale

    xsec_var_Full_Empty.MnvH1D_Helium[1]->Add(xsec_var_Empty.MnvH1D_Helium[1],-1.0) ;
    xsec_var_Full_Empty.MnvH1D_Aluminium[1]->Add(xsec_var_Empty.MnvH1D_Aluminium[1],-1.0) ;
    xsec_var_Full_Empty.MnvH1D_Carbon[1]->Add(xsec_var_Empty.MnvH1D_Carbon[1],-1.0) ;
    xsec_var_Full_Empty.MnvH1D_Lead[1]->Add(xsec_var_Empty.MnvH1D_Lead[1],-1.0) ;
    xsec_var_Full_Empty.MnvH1D_Iron[1]->Add(xsec_var_Empty.MnvH1D_Iron[1],-1.0) ;
    xsec_var_Full_Empty.MnvH1D_Other[1]->Add(xsec_var_Empty.MnvH1D_Other[1],-1.0) ;
}


void Helium_3CryoRegionsSideBandTool::ApplyFitResults(Helium3SideBand &sb_Full_Empty, Helium3SideBand &sb_Full, Helium3SideBand &sb_Empty )
{
    //std::cout<<"Applying Fit Result to contructed Full - Empty Hists "<< sb_Full_Empty.name<<std::endl;
    // Clone Original Histograms
    //std::cout<<"vertex X  copy Full "<<std::endl;
    sb_Full_Empty.MnvH1D_Vertex_X_Helium[1] =  (MnvH1D*) sb_Full.MnvH1D_Vertex_X_Helium[1]->Clone(); // new MnvH1D (   *sb_Full.MnvH1D_Vertex_X_Helium[1]);
    sb_Full_Empty.MnvH1D_Vertex_X_Aluminium[1] = (MnvH1D*) sb_Full.MnvH1D_Vertex_X_Aluminium[1]->Clone();//  new MnvH1D( *sb_Full.MnvH1D_Vertex_X_Aluminium[1]);
    sb_Full_Empty.MnvH1D_Vertex_X_Carbon[1] = (MnvH1D*) sb_Full.MnvH1D_Vertex_X_Carbon[1]->Clone();//  new MnvH1D (   *sb_Full.MnvH1D_Vertex_X_Carbon[1]);
    sb_Full_Empty.MnvH1D_Vertex_X_Iron[1] =  (MnvH1D*) sb_Full.MnvH1D_Vertex_X_Iron[1]->Clone();// new MnvH1D (     *sb_Full.MnvH1D_Vertex_X_Iron[1]);
    sb_Full_Empty.MnvH1D_Vertex_X_Lead[1] = (MnvH1D*) sb_Full.MnvH1D_Vertex_X_Lead[1]->Clone();//  new MnvH1D (     *sb_Full.MnvH1D_Vertex_X_Lead[1]);
    sb_Full_Empty.MnvH1D_Vertex_X_Other[1] = (MnvH1D*) sb_Full.MnvH1D_Vertex_X_Other[1]->Clone(); //  new MnvH1D (    *sb_Full.MnvH1D_Vertex_X_Other[1]);

    std::cout<<"vertex Y  copy Full "<<std::endl;
    sb_Full_Empty.MnvH1D_Vertex_Y_Helium[1] =    (MnvH1D*) sb_Full.MnvH1D_Vertex_Y_Helium[1]->Clone();
    sb_Full_Empty.MnvH1D_Vertex_Y_Aluminium[1] = (MnvH1D*) sb_Full.MnvH1D_Vertex_Y_Aluminium[1]->Clone();
    sb_Full_Empty.MnvH1D_Vertex_Y_Carbon[1] =    (MnvH1D*) sb_Full.MnvH1D_Vertex_Y_Carbon[1]->Clone();
    sb_Full_Empty.MnvH1D_Vertex_Y_Iron[1] =      (MnvH1D*) sb_Full.MnvH1D_Vertex_Y_Iron[1]->Clone();
    sb_Full_Empty.MnvH1D_Vertex_Y_Lead[1] =      (MnvH1D*) sb_Full.MnvH1D_Vertex_Y_Lead[1]->Clone();
    sb_Full_Empty.MnvH1D_Vertex_Y_Other[1] =     (MnvH1D*) sb_Full.MnvH1D_Vertex_Y_Other[1]->Clone();
    std::cout<<"vertex Z  copy Full "<<std::endl;
    sb_Full_Empty.MnvH1D_Vertex_Z_Helium[1] =    (MnvH1D*) sb_Full.MnvH1D_Vertex_Z_Helium[1]->Clone();
    sb_Full_Empty.MnvH1D_Vertex_Z_Aluminium[1] = (MnvH1D*) sb_Full.MnvH1D_Vertex_Z_Aluminium[1]->Clone();
    sb_Full_Empty.MnvH1D_Vertex_Z_Carbon[1] =    (MnvH1D*) sb_Full.MnvH1D_Vertex_Z_Carbon[1]->Clone();
    sb_Full_Empty.MnvH1D_Vertex_Z_Iron[1] =      (MnvH1D*) sb_Full.MnvH1D_Vertex_Z_Iron[1]->Clone();
    sb_Full_Empty.MnvH1D_Vertex_Z_Lead[1] =      (MnvH1D*) sb_Full.MnvH1D_Vertex_Z_Lead[1]->Clone();
    sb_Full_Empty.MnvH1D_Vertex_Z_Other[1] =     (MnvH1D*) sb_Full.MnvH1D_Vertex_Z_Other[1]->Clone();

    std::cout<<"vertex R  copy Full "<<std::endl;
    sb_Full_Empty.MnvH1D_Vertex_R_Helium[1] =    (MnvH1D*) sb_Full.MnvH1D_Vertex_R_Helium[1]->Clone();
    sb_Full_Empty.MnvH1D_Vertex_R_Aluminium[1] = (MnvH1D*) sb_Full.MnvH1D_Vertex_R_Aluminium[1]->Clone();
    sb_Full_Empty.MnvH1D_Vertex_R_Carbon[1] =    (MnvH1D*) sb_Full.MnvH1D_Vertex_R_Carbon[1]->Clone();
    sb_Full_Empty.MnvH1D_Vertex_R_Iron[1] =      (MnvH1D*) sb_Full.MnvH1D_Vertex_R_Iron[1]->Clone();
    sb_Full_Empty.MnvH1D_Vertex_R_Lead[1] =      (MnvH1D*) sb_Full.MnvH1D_Vertex_R_Lead[1]->Clone();
    sb_Full_Empty.MnvH1D_Vertex_R_Other[1] =     (MnvH1D*) sb_Full.MnvH1D_Vertex_R_Other[1]->Clone();

    // SubTract
    std::cout<<"Subtract vertex X full- Empty "<<std::endl;
    sb_Full_Empty.MnvH1D_Vertex_X_Helium[1]->Add(   sb_Empty.MnvH1D_Vertex_X_Helium[1],-1.0);
    sb_Full_Empty.MnvH1D_Vertex_X_Aluminium[1]->Add(sb_Empty.MnvH1D_Vertex_X_Aluminium[1],-1.0);
    sb_Full_Empty.MnvH1D_Vertex_X_Carbon[1]->Add(   sb_Empty.MnvH1D_Vertex_X_Carbon[1],-1.0);
    sb_Full_Empty.MnvH1D_Vertex_X_Iron[1]->Add(     sb_Empty.MnvH1D_Vertex_X_Iron[1],-1.0);
    sb_Full_Empty.MnvH1D_Vertex_X_Lead[1]->Add(     sb_Empty.MnvH1D_Vertex_X_Lead[1],-1.0);
    sb_Full_Empty.MnvH1D_Vertex_X_Other[1]->Add(    sb_Empty.MnvH1D_Vertex_X_Other[1],-1.0);

    std::cout<<"Subtract vertex Y full- Empty "<<std::endl;
    sb_Full_Empty.MnvH1D_Vertex_Y_Helium[1]->Add(   sb_Empty.MnvH1D_Vertex_Y_Helium[1],-1.0);
    sb_Full_Empty.MnvH1D_Vertex_Y_Aluminium[1]->Add(sb_Empty.MnvH1D_Vertex_Y_Aluminium[1],-1.0);
    sb_Full_Empty.MnvH1D_Vertex_Y_Carbon[1]->Add(   sb_Empty.MnvH1D_Vertex_Y_Carbon[1],-1.0);
    sb_Full_Empty.MnvH1D_Vertex_Y_Iron[1]->Add(     sb_Empty.MnvH1D_Vertex_Y_Iron[1],-1.0);
    sb_Full_Empty.MnvH1D_Vertex_Y_Lead[1]->Add(     sb_Empty.MnvH1D_Vertex_Y_Lead[1],-1.0);
    sb_Full_Empty.MnvH1D_Vertex_Y_Other[1]->Add(    sb_Empty.MnvH1D_Vertex_Y_Other[1],-1.0);

    std::cout<<"Subtract vertex Z full- Empty "<<std::endl;

    sb_Full_Empty.MnvH1D_Vertex_Z_Helium[1]->Add(   sb_Empty.MnvH1D_Vertex_Z_Helium[1],-1.0);
    sb_Full_Empty.MnvH1D_Vertex_Z_Aluminium[1]->Add(sb_Empty.MnvH1D_Vertex_Z_Aluminium[1],-1.0);
    sb_Full_Empty.MnvH1D_Vertex_Z_Carbon[1]->Add(   sb_Empty.MnvH1D_Vertex_Z_Carbon[1],-1.0);
    sb_Full_Empty.MnvH1D_Vertex_Z_Iron[1]->Add(     sb_Empty.MnvH1D_Vertex_Z_Iron[1],-1.0);
    sb_Full_Empty.MnvH1D_Vertex_Z_Lead[1]->Add(     sb_Empty.MnvH1D_Vertex_Z_Lead[1],-1.0);
    sb_Full_Empty.MnvH1D_Vertex_Z_Other[1]->Add(    sb_Empty.MnvH1D_Vertex_Z_Other[1],-1.0);

    //std::cout<<"Subtract vertex R Helium  "<<std::endl;

    sb_Full_Empty.MnvH1D_Vertex_R_Helium[1]->Add(   sb_Empty.MnvH1D_Vertex_R_Helium[1],-1.0);
    //std::cout<<" R Aluminium "<<std::endl;
    sb_Full_Empty.MnvH1D_Vertex_R_Aluminium[1]->Add(sb_Empty.MnvH1D_Vertex_R_Aluminium[1],-1.0);
    //std::cout<<"R_Carbon "<<std::endl;
    sb_Full_Empty.MnvH1D_Vertex_R_Carbon[1]->Add(   sb_Empty.MnvH1D_Vertex_R_Carbon[1], -1.0);
    //std::cout<<"R_Iron "<<std::endl;
    sb_Full_Empty.MnvH1D_Vertex_R_Iron[1]->Add(     sb_Empty.MnvH1D_Vertex_R_Iron[1],  -1.0);
    //std::cout<<"R_Lead"<<std::endl;
    sb_Full_Empty.MnvH1D_Vertex_R_Lead[1]->Add(     sb_Empty.MnvH1D_Vertex_R_Lead[1],  -1.0);
    //std::cout<<"R_Other"<<std::endl;
    sb_Full_Empty.MnvH1D_Vertex_R_Other[1]->Add(    sb_Empty.MnvH1D_Vertex_R_Other[1], -1.0);



std::cout<< " subtraction of Varibles"<< std::endl;
    // Cross Section Variables
    ApplyFitResults_Int_Full_Empty(sb_Full_Empty.muon_PT,       sb_Full.muon_PT,       sb_Empty.muon_PT);
    ApplyFitResults_Int_Full_Empty(sb_Full_Empty.muon_PZ,       sb_Full.muon_PZ,       sb_Empty.muon_PZ);
    ApplyFitResults_Int_Full_Empty(sb_Full_Empty.muon_theta,    sb_Full.muon_theta,    sb_Empty.muon_theta);
    ApplyFitResults_Int_Full_Empty(sb_Full_Empty.muon_E,        sb_Full.muon_E,        sb_Empty.muon_E);
    ApplyFitResults_Int_Full_Empty(sb_Full_Empty.DistancetoEdge,sb_Full.DistancetoEdge,sb_Empty.DistancetoEdge);
    ApplyFitResults_Int_Full_Empty(sb_Full_Empty.muon_doca,     sb_Full.muon_doca,     sb_Empty.muon_doca);
    ApplyFitResults_Int_Full_Empty(sb_Full_Empty.SecTrk_doca,   sb_Full.SecTrk_doca,   sb_Empty.SecTrk_doca);
    ApplyFitResults_Int_Full_Empty(sb_Full_Empty.TrackLength,   sb_Full.TrackLength,   sb_Empty.TrackLength);

    ApplyFitResults_Int_Full_Empty(sb_Full_Empty.DistancetoUpstreamCap ,        sb_Full.DistancetoUpstreamCap,        sb_Empty.DistancetoUpstreamCap );
    ApplyFitResults_Int_Full_Empty(sb_Full_Empty.DistancetoDownstreamCap ,      sb_Full.DistancetoDownstreamCap,      sb_Empty.DistancetoDownstreamCap );
    ApplyFitResults_Int_Full_Empty(sb_Full_Empty.DistancetoUpstreamCap_RCut ,   sb_Full.DistancetoUpstreamCap_RCut,   sb_Empty.DistancetoUpstreamCap_RCut );
    ApplyFitResults_Int_Full_Empty(sb_Full_Empty.DistancetoDownstreamCap_RCut , sb_Full.DistancetoDownstreamCap_RCut, sb_Empty.DistancetoDownstreamCap_RCut );
    ApplyFitResults_Int_Full_Empty(sb_Full_Empty.Vertex_Z_RCut ,                sb_Full.Vertex_Z_RCut,                sb_Empty.Vertex_Z_RCut );
    ApplyFitResults_Int_Full_Empty(sb_Full_Empty.Vertex_X_RCut ,                sb_Full.Vertex_X_RCut,                sb_Empty.Vertex_X_RCut );
    ApplyFitResults_Int_Full_Empty(sb_Full_Empty.Vertex_Y_RCut ,                sb_Full.Vertex_Y_RCut,                sb_Empty.Vertex_Y_RCut );
    ApplyFitResults_Int_Full_Empty(sb_Full_Empty.Vertex_R_RCut ,                sb_Full.Vertex_R_RCut,                sb_Empty.Vertex_R_RCut );


}





void Helium_3CryoRegionsSideBandTool::ApplyFitResults()
{
  if(wgt_Aluminium.size()==4 ){

ApplyFitToBands(Empty_UpstreamCap, Empty_Barrel,    Empty_DownstreamCap, Empty_DownstreamConcaveCap, wgt_Aluminium);
ApplyFitToBands(Full_UpstreamCap,  Full_Barrel,     Full_DownstreamCap, Full_DownstreamConcaveCap, wgt_Aluminium);

//ApplyFitToBands(Full_Empty_UpstreamCap, Full_Empty_Barrel,Full_Empty_DownstreamCap,Full_Empty_DownstreamConcaveCap, wgt_Aluminium);
//std::cout<<"applying fit results to Full_Empty_UpstreamCap"<< std::endl;
ApplyFitResults(Full_Empty_UpstreamCap, Full_UpstreamCap, Empty_UpstreamCap );
//std::cout<<"applying fit results to Full_Empty_Barrel"<< std::endl;
ApplyFitResults(Full_Empty_Barrel, Full_Barrel, Empty_Barrel );
//std::cout<<"applying fit results to Full_Empty_downstreamCap"<< std::endl;
ApplyFitResults(Full_Empty_DownstreamCap, Full_DownstreamCap, Empty_DownstreamCap );
//std::cout<<"applying fit results to Full_Empty_ConcaveCap"<< std::endl;
ApplyFitResults(Full_Empty_DownstreamConcaveCap, Full_DownstreamConcaveCap, Empty_DownstreamConcaveCap );
//std::cout<<"applying fit parameters to hists"<< std::endl;
}

else{
  std::cout<<"Fit can't be applied wrong number of wgts not correct"<<std::endl;
  std::cout << "wgt_Aluminium.size() = "<< wgt_Aluminium.size()<<std::endl;
exit(EXIT_FAILURE);}
}
void Helium_3CryoRegionsSideBandTool::ApplyFitResults_Al_He_combined()
{
  //std::cout<<"Inside:ApplyFitResults_Al_He_combined"<<std::endl;
  if(wgt_Aluminium.size()==4 && wgt_Helium.size()== 4 ){

    ApplyFitToBands(Empty_UpstreamCap, Empty_Barrel, Empty_DownstreamCap, Empty_DownstreamConcaveCap, wgt_Aluminium , wgt_Helium);
    ApplyFitToBands(Full_UpstreamCap,  Full_Barrel,  Full_DownstreamCap,  Full_DownstreamConcaveCap,  wgt_Aluminium , wgt_Helium);

    ApplyFitResults(Full_Empty_UpstreamCap,          Full_UpstreamCap,          Empty_UpstreamCap );
    ApplyFitResults(Full_Empty_Barrel,               Full_Barrel,               Empty_Barrel );
    ApplyFitResults(Full_Empty_DownstreamCap,        Full_DownstreamCap,        Empty_DownstreamCap );
    ApplyFitResults(Full_Empty_DownstreamConcaveCap, Full_DownstreamConcaveCap, Empty_DownstreamConcaveCap );
    //std::cout<<"applying fit parameters to hists"<< std::endl;
  }


else{
  std::cout<<"Fit can't be applied wrong number of wgts not correct"<<std::endl;
  std::cout << "wgt_Aluminium.size() = "<< wgt_Aluminium.size()<<std::endl;
exit(EXIT_FAILURE);}
}

void Helium_3CryoRegionsSideBandTool::ApplyFitResults_toResolution()
{
  ApplyFitToResolution_Bands(Empty_UpstreamCap, Empty_Barrel, Empty_DownstreamCap, Empty_DownstreamConcaveCap, wgt_Aluminium);
  ApplyFitToResolution_Bands(Full_UpstreamCap, Full_Barrel, Full_DownstreamCap, Full_DownstreamConcaveCap, wgt_Aluminium);


}





void Helium_3CryoRegionsSideBandTool::ApplyFitResults_To_Full_EmptyFits()
{
  if(wgt_Aluminium.size()==4 || wgt_Aluminium.size()==8 ){
std::vector<double> noscale{1.0,1.0,1.0,1.0};
// Fill [1] with copy of [0]
ApplyFitToBands(Empty_UpstreamCap, Empty_Barrel, Empty_DownstreamCap, Empty_DownstreamConcaveCap, noscale);
ApplyFitToBands(Full_UpstreamCap,  Full_Barrel,  Full_DownstreamCap,  Full_DownstreamConcaveCap, noscale);
///////////
// Do SubTraction
///////////
//std::cout<<"applying fit results to Full_Empty_UpstreamCap"<< std::endl;
ApplyFitResults(Full_Empty_UpstreamCap,          Full_UpstreamCap,          Empty_UpstreamCap );
ApplyFitResults(Full_Empty_Barrel,               Full_Barrel,               Empty_Barrel );
ApplyFitResults(Full_Empty_DownstreamCap,        Full_DownstreamCap,        Empty_DownstreamCap );
ApplyFitResults(Full_Empty_DownstreamConcaveCap, Full_DownstreamConcaveCap, Empty_DownstreamConcaveCap );
//apply the fit to F-E only
ApplyFitToBands(Full_Empty_UpstreamCap, Full_Empty_Barrel, Full_Empty_DownstreamCap, Full_Empty_DownstreamConcaveCap, wgt_Aluminium);

}

else{
  std::cout<<"Fit can't be applied wrong number of wgts not correct"<<std::endl;
  std::cout << "wgt_Aluminium.size() = "<< wgt_Aluminium.size()<<std::endl;
exit(EXIT_FAILURE);}
}


void Helium_3CryoRegionsSideBandTool::ApplyFitResults_toFitParmsOnly_Empty(){

  if(wgt_Aluminium.size()==4 ){
    //std::cout<<"apply UPSTREAM Cap Al wgt = " << wgt_Aluminium.at(0)<<std::endl;
    //std::cout<<"apply Barrel Cap Al wgt = " << wgt_Aluminium.at(1)<<std::endl;
    //std::cout<<"apply Downstream Cap Al wgt = " << wgt_Aluminium.at(2)<<std::endl;
    //std::cout<<"apply Downstream Concave Cap Al wgt = " << wgt_Aluminium.at(3)<<std::endl;

    ApplyFitResults_toFitParsOnly(Empty_UpstreamCap,  wgt_Aluminium.at(0));
    ApplyFitResults_toFitParsOnly(Empty_Barrel,       wgt_Aluminium.at(1));
    ApplyFitResults_toFitParsOnly(Empty_DownstreamCap,  wgt_Aluminium.at(2));
    ApplyFitResults_toFitParsOnly(Empty_DownstreamConcaveCap,  wgt_Aluminium.at(3));

  }
  else{
    std::cout<<"Fit can't be applied wrong number of wgts not correct"<<std::endl;
    std::cout << "wgt_Aluminium.size() = "<< wgt_Aluminium.size()<<std::endl;
    exit(EXIT_FAILURE);
  }
}
void Helium_3CryoRegionsSideBandTool::ApplyFitResults_toFitParmsOnly_Empty_regionX(){

  if(wgt_Aluminium.size()==4 ){

    ApplyFitResults_toFitParsOnly(Empty_XCenter,      wgt_Aluminium.at(0));
    ApplyFitResults_toFitParsOnly(Empty_XLeftShelf,       wgt_Aluminium.at(1));
    ApplyFitResults_toFitParsOnly(Empty_XRightShelf,  wgt_Aluminium.at(2));
    ApplyFitResults_toFitParsOnly(Empty_XoutsideEdges,  wgt_Aluminium.at(3));

    //ApplyFitResults_Xsecvar(Empty_XCenter,      wgt_Aluminium.at(0));
    //ApplyFitResults_Xsecvar(Empty_XLeftShelf,      wgt_Aluminium.at(1));
    //ApplyFitResults_Xsecvar(Empty_XRightShelf,      wgt_Aluminium.at(2));
    //ApplyFitResults_Xsecvar(Empty_XoutsideEdges,      wgt_Aluminium.at(3));


  }
  else{
    std::cout<<"Fit can't be applied wrong number of wgts not correct"<<std::endl;
    std::cout << "wgt_Aluminium.size() = "<< wgt_Aluminium.size()<<std::endl;
    exit(EXIT_FAILURE);
  }
}

void Helium_3CryoRegionsSideBandTool::ApplyFitResults_toFitParmsOnly_Empty_regionXZ(){

  if(wgt_Aluminium.size()==4 ){

    ApplyFitResults_toFitParsOnly(Empty_XCenter,      wgt_Aluminium.at(0));
    ApplyFitResults_toFitParsOnly(Empty_XLeftShelf,       wgt_Aluminium.at(1));
    ApplyFitResults_toFitParsOnly(Empty_XRightShelf,  wgt_Aluminium.at(2));
    ApplyFitResults_toFitParsOnly(Empty_DownstreamConcaveCap,  wgt_Aluminium.at(3));

    //ApplyFitResults_Xsecvar(Empty_XCenter,      wgt_Aluminium.at(0));
    //ApplyFitResults_Xsecvar(Empty_XLeftShelf,      wgt_Aluminium.at(1));
    //ApplyFitResults_Xsecvar(Empty_XRightShelf,      wgt_Aluminium.at(2));
    //ApplyFitResults_Xsecvar(Empty_XoutsideEdges,      wgt_Aluminium.at(3));


  }
  else{
    std::cout<<"Fit can't be applied wrong number of wgts not correct"<<std::endl;
    std::cout << "wgt_Aluminium.size() = "<< wgt_Aluminium.size()<<std::endl;
    exit(EXIT_FAILURE);
  }
}


void Helium_3CryoRegionsSideBandTool::WriteStatistics()
{
    WriteStatistics(Full);
    WriteStatistics(Empty);

    WriteStatistics(Full_UpstreamCap);
    WriteStatistics(Empty_UpstreamCap);

    WriteStatistics(Full_Barrel);
    WriteStatistics(Empty_Barrel);

    WriteStatistics(Full_DownstreamCap);
    WriteStatistics(Empty_DownstreamCap);


}

void Helium_3CryoRegionsSideBandTool::SaveFitResults(double chisq, double par_values[4], double par_errors[4])
{
//std::cout<< "inside Helium_3CryoRegionsSideBandTool::SaveFitResults | chisq =  "<< chisq << " | par_values[1] =  "<< par_values[0] << " | par_errors[1] =  " << par_errors[0]<<std::endl;

    ChiSq_after_fit.push_back(chisq);
    wgt_Aluminium.push_back(par_values[0]);
    err_Aluminium.push_back(par_errors[0]);

    wgt_Aluminium.push_back(par_values[1]);
    err_Aluminium.push_back(par_errors[1]);

    wgt_Aluminium.push_back(par_values[2]);
    err_Aluminium.push_back(par_errors[2]);

    wgt_Aluminium.push_back(par_values[3]);
    err_Aluminium.push_back(par_errors[3]);

}

void Helium_3CryoRegionsSideBandTool::SaveFitResults_Al_and_He(double chisq, double par_values[8], double par_errors[8])
{
std::cout<< "inside Helium_3CryoRegionsSideBandTool::SaveFitResults_Al_and_He | chisq =  "<< chisq << " | par_values[1] =  "<< par_values[0] << " | par_errors[1] =  " << par_errors[0]<<std::endl;

    ChiSq_after_fit.push_back(chisq);
    wgt_Aluminium.push_back(par_values[0]);
    err_Aluminium.push_back(par_errors[0]);

    wgt_Aluminium.push_back(par_values[1]);
    err_Aluminium.push_back(par_errors[1]);

    wgt_Aluminium.push_back(par_values[2]);
    err_Aluminium.push_back(par_errors[2]);

    wgt_Aluminium.push_back(par_values[3]);
    err_Aluminium.push_back(par_errors[3]);


    wgt_Helium.push_back(par_values[4]);
    err_Helium.push_back(par_errors[4]);

    wgt_Helium.push_back(par_values[5]);
    err_Helium.push_back(par_errors[5]);

    wgt_Helium.push_back(par_values[6]);
    err_Helium.push_back(par_errors[6]);

    wgt_Helium.push_back(par_values[7]);
    err_Helium.push_back(par_errors[7]);


}



Helium_3CryoRegionsSideBandTool::~Helium_3CryoRegionsSideBandTool()
{

}
////////////////////////////////////////////////////////////
///Plotting
/////////////////////////////////////////////////////////////
///////////////
void Helium_3CryoRegionsSideBandTool::Plot(std::string pdf_label, int ind, double POT_ratio, std::string sb_name,
   std::string var_name, MnvH1D* data, MnvH1D* mc_total, MnvH1D* Helium, MnvH1D* Aluminium, MnvH1D* Carbon,
    MnvH1D* Iron, MnvH1D* Lead, MnvH1D* Other, std::string Hist_title, std::string xaxislabel,
     int index, bool UseLogChi, bool applyMaxY, double MaxY)
{
  data->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  mc_total->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));


    std::string type;
    if (ind == 0) type = "Nominal";
    else type = "Fitted";
    //std::cout<<"Ploting type:  "<< type<<std::endl;

    std::string norm = "POT";
    std::string plot_title = "Side Band: " + sb_name + " " + type + " " + norm + " Normalized";
    //PlotUtils::MnvPlotter* plotter= new mnvPlotter();
     MnvPlotter* plotter = new MnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
    //plotter(PlotUtils::kCCInclusiveHeliumStyle);
    data->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
    TH1D* h_data = new TH1D(data->GetCVHistoWithError());
    TH1D* h_Helium = new TH1D(Helium->GetCVHistoWithError());
    TH1D* h_Aluminium = new TH1D(Aluminium->GetCVHistoWithError());
    TH1D* h_Carbon = new TH1D(Carbon->GetCVHistoWithError());
    TH1D* h_Iron = new TH1D(Iron->GetCVHistoWithError());
    TH1D* h_Lead = new TH1D(Lead->GetCVHistoWithError());
    TH1D* h_Other = new TH1D(Other->GetCVHistoWithError());

    ColorHists(h_data, h_Helium, h_Aluminium, h_Carbon, h_Iron,h_Lead,  h_Other);
    // MC Total depend on the Modification
    //      If Raws - take the mc_total directly
    //      If Modified - Add all mc models;
    TH1D* h_mc_total;
    if (ind == 0){
        h_mc_total =(TH1D*)mc_total->Clone("h_mc_total"); //new TH1D(mc_total->GetCVHistoWithError());
    }
    else{
      h_mc_total = (TH1D*)mc_total->Clone("h_mc_total"); //new TH1D(*h_Helium);
      h_mc_total->Add(h_Aluminium);
      h_mc_total->Add(h_Carbon);
      h_mc_total->Add(h_Iron);
      h_mc_total->Add(h_Lead);
      h_mc_total->Add(h_Other);
    }

    // Scale Histograms
    //double mc_ratio = POT_ratio;
    double plot_chisq ;
    if(UseLogChi==true){plot_chisq = calc_ChiSq(h_data, h_Helium, h_Aluminium, h_Carbon, h_Lead, h_Iron, h_Other);}
    else if(UseLogChi==false){plot_chisq = calc_LogChiSq(h_data, h_Helium, h_Aluminium, h_Carbon, h_Lead, h_Iron, h_Other);}

    std::string yaxis;
    if(MakeBinWidth==true){

      h_mc_total->Scale(1.0, "width");
      h_Helium->Scale(1.0, "width");
      h_Aluminium->Scale(1.0, "width");
      h_Carbon->Scale(1.0, "width");
      h_Iron->Scale(1.0, "width");
      h_Lead->Scale(1.0, "width");
      h_Other->Scale(1.0, "width");
      h_data->Scale(1.0, "width");
      double binwidth_title = mc_total -> GetBinWidth(3);
      yaxis = Form("N(Events) / %.2f",binwidth_title);
      //std::cout<< "yaxis = "<< yaxis<<std::endl;
      //std::cout<<"Finished Bin width Norm"<<std::endl;
    }
    else{
      yaxis = "N(Events)";
    //  std::cout<<"FInished Bin NOT width Norm"<<std::endl;
    }

    // ------------------------------------------------------------------------
    // Unique Plot for Single Error Band, Single Universe
    //      Comment this section out
    // ------------------------------------------------------------------------


    // Create Canvas and Divide it into two
    TCanvas* c = new TCanvas("c","c",800, 800);
    //TCanvas cE("cE","cE", 800, 800);
    // Upper Pad is the Data vs MC
    //OLDTPad *pad1 = new TPad("pad1", "pad1", 0.05, 0.3, 1, 1.0);
    TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
    pad1->SetBottomMargin(0); // Top and Bottom Plots attached
    pad1->Draw();
    pad1->cd(); // pad1 is the current pad
      // Plot MC Models as THStack
    THStack* hs = new THStack("hs",plot_title.c_str());
    hs->Add(h_Helium);
    hs->Add(h_Aluminium);
    hs->Add(h_Carbon);
    hs->Add(h_Iron);
    hs->Add(h_Lead);
    hs->Add(h_Other);

    //std::cout<<"Finished adding hist to hs I"<<std::endl;

    // Styling
    //h_mc_total->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
    //h_mc_total->GetYaxis()->SetTitle(Form("%s",yaxis.c_str()));



    hs->Draw("HIST");
    h_mc_total->SetMarkerStyle(0);
    h_mc_total->SetLineWidth(2);
    h_mc_total->SetLineColor(kBlack);
    h_mc_total->SetFillStyle(0);
    h_mc_total->Draw("same Hist");
    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0);

    hs->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
    hs->GetYaxis()->SetTitle(Form("%s",yaxis.c_str()));
    hs->GetYaxis()->SetTitleFont(62);
    hs->GetYaxis()->SetTitleSize(0.06);
    //hs->GetYaxis()->CenterTitle();
    //hs->GetYaxis()->SetTitleOffset(1.2);
    hs->GetYaxis()->SetLabelFont(42);
    hs->GetYaxis()->SetLabelSize(0.05);

    double hist_max = h_data->GetMaximum();
    //std::cout<<"GetMaximum() =  "<<hist_max<<std::endl;
     if (applyMaxY==false){
        hs->SetMaximum(hist_max * 1.45);
    }
    else if (applyMaxY==true){
     hs->SetMaximum(MaxY);
    }

    hs->SetMinimum(-1);
    //std::cout<<"Finshed Drawing Hist "<<std::endl;

    // Add Data Plot
    //h_data->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
    h_data->Draw("SAME E1 X0");

    //std::cout<<"FInished Drawing h_data"<<std::endl;

    // Add Legend
    TLegend *legend = new TLegend(0.6,0.65,0.9,0.9);

    legend->AddEntry(h_data, "Data");
    legend->AddEntry(h_mc_total, "Total MC");
    legend->AddEntry(h_Helium,    "Helium", "f");
    legend->AddEntry(h_Aluminium, "Al: ", "f");
    legend->AddEntry(h_Carbon,    "C: ", "f");
    legend->AddEntry(h_Iron,      "Fe: ", "f");
    legend->AddEntry(h_Lead,      "Pb: ", "f");
    legend->AddEntry(h_Other,     "Other", "f");
    legend->SetTextSize(0.04);
    legend->SetTextFont(42);
    legend->Draw();
    //std::cout<<"FInished Drawing legend"<<std::endl;

    // Add Weights as Text to Modified Plot
    int nPoints = h_data->GetNbinsX()-1;

    //std::cout<<"nPoints = "<<nPoints<< std::endl;

    // Add Plot-ChiSq
    TLatex* text = new TLatex;
    text->SetNDC();
    text->SetTextSize(0.03);
    text->SetTextColor(kBlue);
    //double plot_chisq = calc_ChiSq(data, signal, WithPi0, QELike, SinglePiPlus, Other);


    if (ind == 0){ChiSq_before_fit_var.push_back(plot_chisq);}

    if (ind != 0){
        int nPars = 1;
        std::cout<<"making Fit info" <<  std::endl;
        //std::cout<<"ChiSq_before_fit[0] = "<< ChiSq_before_fit[0]<<std::endl;
          std::cout<<"ChiSq_after_fit[0] = "<< plot_chisq<<std::endl;
        TLatex* text = new TLatex;
        text->SetTextSize(0.025);
        text->SetNDC();
        text->DrawLatex(0.55, 0.60, Form("Fit Results with %d points, %d pars", nPoints, nPars));
        text->DrawLatex(0.55, 0.57, Form("Before Fit #chi^{2} = %3.2f", ChiSq_before_fit_var.at(index)));
        text->DrawLatex(0.55, 0.54, Form("Before Fit #chi^{2}/dof = %3.2f", ChiSq_before_fit_var.at(index)/(nPoints-nPars)));
        text->DrawLatex(0.55, 0.51, Form("After Fit #chi^{2} = %3.2f", plot_chisq));
        text->DrawLatex(0.55, 0.48, Form("After Fit #chi^{2}/dof = %3.2f", plot_chisq/(double)(nPoints-nPars)));
        text->DrawLatex(0.55, 0.44, Form("#color[4]{wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[0], err_Aluminium[0]));

      //  delete text;
    }
    text->SetTextSize(0.03);
    text->DrawLatex(0.2, 0.85, Form("Plot #chi^{2} = %3.2f", plot_chisq));
    text->DrawLatex(0.2, 0.82, Form("Plot #chi^{2}/dof = %3.2f", plot_chisq / (double) nPoints));
    delete text;
    plotter->AddHistoTitle(Hist_title.c_str(),.04);
    plotter->WritePreliminary("TL", .025, 0, 0, false);
    // Plot Lower Plot: Data vs MC Ratio
    c->cd(); // Go back to default_Ymax Canvas before creating 2nd Pad
    //TPad *pad2 = new TPad("pad2", "pad2", 0.05, 0.05, 1, 0.3);

    //pad2->SetTopMargin(0);
    //pad2->SetBottomMargin(0.2);

    TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
    pad2->SetTopMargin(0);
    pad2->SetBottomMargin(0.2);
    pad2->SetGridx(); // vertical grid
    pad2->Draw();
    pad2->cd();

    // Calculate the Ratio
    plotter->axis_title_size_x = 0.1;
    plotter->axis_title_offset_y = .4;
    plotter->axis_title_size_y = 0.12;
    plotter->axis_label_size = 0.1;
    plotter->axis_maximum = 2.5;
    plotter->axis_minimum = .5;

    plotter->DrawDataMCRatio(data, mc_total, 1.0, false, false , -.5, 2, "#frac{Data}{MC}", false);
    // Add Ratio = 1 Line
    TLine ratio_1;
    ratio_1.SetLineWidth(2);
    ratio_1.SetLineStyle(7);
    ratio_1.SetLineColor(kBlue);
    double line_min = h_data->GetBinLowEdge(1);
    double line_max = h_data->GetBinLowEdge(h_data->GetNbinsX()+1);
    ratio_1.DrawLine(line_min,1,line_max,1);

    // Plot Output
    c->Update();
    c->cd();
    c->Print(pdf_label.c_str(),"pdf");

    delete legend;
    delete hs;
    delete pad1;
    delete pad2;
    delete c;

    delete h_data;
    delete h_Helium;
    delete h_Aluminium;
    delete h_Carbon;
    delete h_Iron;
    delete h_Lead;
    delete h_Other;
}

void Helium_3CryoRegionsSideBandTool::Plot(std::string pdf_label, int ind, double POT_ratio,
   MnvH1D* data_UpstreamCap, MnvH1D* mc_total_UpstreamCap, MnvH1D* Helium_UpstreamCap, MnvH1D* Aluminium_UpstreamCap, MnvH1D* Carbon_UpstreamCap,
   MnvH1D* Iron_UpstreamCap, MnvH1D* Lead_UpstreamCap, MnvH1D* Other_UpstreamCap,
   MnvH1D* data_Barrel, MnvH1D* mc_total_Barrel, MnvH1D* Helium_Barrel, MnvH1D* Aluminium_Barrel, MnvH1D* Carbon_Barrel,
   MnvH1D* Iron_Barrel, MnvH1D* Lead_Barrel, MnvH1D* Other_Barrel,
   MnvH1D* data_DownstreamCap, MnvH1D* mc_total_DownstreamCap, MnvH1D* Helium_DownstreamCap, MnvH1D* Aluminium_DownstreamCap, MnvH1D* Carbon_DownstreamCap,
   MnvH1D* Iron_DownstreamCap, MnvH1D* Lead_DownstreamCap, MnvH1D* Other_DownstreamCap,
   MnvH1D* data_DownstreamConcaveCap, MnvH1D* mc_total_DownstreamConcaveCap, MnvH1D* Helium_DownstreamConcaveCap, MnvH1D* Aluminium_DownstreamConcaveCap, MnvH1D* Carbon_DownstreamConcaveCap,
   MnvH1D* Iron_DownstreamConcaveCap, MnvH1D* Lead_DownstreamConcaveCap, MnvH1D* Other_DownstreamConcaveCap,
   std::string Hist_title, std::string xaxislabel, double &ChiSqrt, double &ChiSqrtAfter, bool He_and_AlFit, bool UseLogChi, bool doAreaNormalized )
   {

    std::string type;
    if (ind == 0) type = "Nominal";
    else type = "Fitted";
    //std::cout<<"Ploting type: Combined CryoRegions  "<< type<<std::endl;

    //PlotUtils::MnvPlotter* plotter= new mnvPlotter();
     MnvPlotter* plotter = new MnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
    //plotter(PlotUtils::kCCInclusiveHeliumStyle);
    MnvH1D *data = (PlotUtils::MnvH1D*)data_UpstreamCap->Clone("data");
    data->Add(data_Barrel);
    data->Add(data_DownstreamCap);
    data->Add(data_DownstreamConcaveCap);
    MnvH1D *mc_total = (PlotUtils::MnvH1D*)Helium_UpstreamCap->Clone("mc_total");
    mc_total->Add(Aluminium_UpstreamCap );
    mc_total->Add(Carbon_UpstreamCap);
    mc_total->Add(Iron_UpstreamCap );
    mc_total->Add(Lead_UpstreamCap );
    mc_total->Add(Other_UpstreamCap);
    mc_total->Add(Helium_Barrel );
    mc_total->Add(Aluminium_Barrel );
    mc_total->Add(Carbon_Barrel);
    mc_total->Add(Iron_Barrel );
    mc_total->Add(Lead_Barrel );
    mc_total->Add(Other_Barrel);
    mc_total->Add(Helium_DownstreamCap );
    mc_total->Add(Aluminium_DownstreamCap );
    mc_total->Add(Carbon_DownstreamCap);
    mc_total->Add(Iron_DownstreamCap );
    mc_total->Add(Lead_DownstreamCap );
    mc_total->Add(Other_DownstreamCap);
    mc_total->Add(Helium_DownstreamConcaveCap );
    mc_total->Add(Aluminium_DownstreamConcaveCap );
    mc_total->Add(Carbon_DownstreamConcaveCap);
    mc_total->Add(Iron_DownstreamConcaveCap );
    mc_total->Add(Lead_DownstreamConcaveCap );
    mc_total->Add(Other_DownstreamConcaveCap);

    data->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
    mc_total->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));


    TH1D* h_data_Combined = new TH1D(data_UpstreamCap->GetCVHistoWithError());
    TH1D* h_Helium_UpstreamCap = new TH1D(Helium_UpstreamCap->GetCVHistoWithError());
    TH1D* h_Aluminium_UpstreamCap = new TH1D(Aluminium_UpstreamCap->GetCVHistoWithError());

    TH1D* h_Carbon_Combined = new TH1D(Carbon_UpstreamCap->GetCVHistoWithError());
    TH1D* h_Iron_Combined = new TH1D(Iron_UpstreamCap->GetCVHistoWithError());
    TH1D* h_Lead_Combined = new TH1D(Lead_UpstreamCap->GetCVHistoWithError());
    TH1D* h_Other_Combined = new TH1D(Other_UpstreamCap->GetCVHistoWithError());

    TH1D* h_data_Barrel = new TH1D(data_Barrel->GetCVHistoWithError());
    TH1D* h_Helium_Barrel = new TH1D(Helium_Barrel->GetCVHistoWithError());
    TH1D* h_Aluminium_Barrel = new TH1D(Aluminium_Barrel->GetCVHistoWithError());
    TH1D* h_Carbon_Barrel = new TH1D(Carbon_Barrel->GetCVHistoWithError());
    TH1D* h_Iron_Barrel = new TH1D(Iron_Barrel->GetCVHistoWithError());
    TH1D* h_Lead_Barrel = new TH1D(Lead_Barrel->GetCVHistoWithError());
    TH1D* h_Other_Barrel = new TH1D(Other_Barrel->GetCVHistoWithError());

    h_Carbon_Combined->Add(h_Carbon_Barrel);
    h_Iron_Combined->Add(h_Iron_Barrel);
    h_Lead_Combined->Add(h_Lead_Barrel);
    h_Other_Combined->Add(h_Other_Barrel);
    h_data_Combined->Add(h_data_Barrel);

    TH1D* h_data_DownstreamCap = new TH1D(data_DownstreamCap->GetCVHistoWithError());
    TH1D* h_Helium_DownstreamCap = new TH1D(Helium_DownstreamCap->GetCVHistoWithError());
    TH1D* h_Aluminium_DownstreamCap = new TH1D(Aluminium_DownstreamCap->GetCVHistoWithError());

    TH1D* h_Carbon_DownstreamCap = new TH1D(Carbon_DownstreamCap->GetCVHistoWithError());
    TH1D* h_Iron_DownstreamCap = new TH1D(Iron_DownstreamCap->GetCVHistoWithError());
    TH1D* h_Lead_DownstreamCap = new TH1D(Lead_DownstreamCap->GetCVHistoWithError());
    TH1D* h_Other_DownstreamCap = new TH1D(Other_DownstreamCap->GetCVHistoWithError());

    h_Carbon_Combined->Add(h_Carbon_DownstreamCap);
    h_Iron_Combined->Add(h_Iron_DownstreamCap);
    h_Lead_Combined->Add(h_Lead_DownstreamCap);
    h_Other_Combined->Add(h_Other_DownstreamCap);
    h_data_Combined->Add(h_data_DownstreamCap);

    TH1D* h_data_DownstreamConcaveCap = new TH1D(data_DownstreamConcaveCap->GetCVHistoWithError());
    TH1D* h_Helium_DownstreamConcaveCap = new TH1D(Helium_DownstreamConcaveCap->GetCVHistoWithError());
    TH1D* h_Aluminium_DownstreamConcaveCap = new TH1D(Aluminium_DownstreamConcaveCap->GetCVHistoWithError());

    TH1D* h_Carbon_DownstreamConcaveCap = new TH1D(Carbon_DownstreamConcaveCap->GetCVHistoWithError());
    TH1D* h_Iron_DownstreamConcaveCap = new TH1D(Iron_DownstreamConcaveCap->GetCVHistoWithError());
    TH1D* h_Lead_DownstreamConcaveCap = new TH1D(Lead_DownstreamConcaveCap->GetCVHistoWithError());
    TH1D* h_Other_DownstreamConcaveCap = new TH1D(Other_DownstreamConcaveCap->GetCVHistoWithError());


    h_Carbon_Combined->Add(h_Carbon_DownstreamConcaveCap);
    h_Iron_Combined->Add(h_Iron_DownstreamConcaveCap);
    h_Lead_Combined->Add(h_Lead_DownstreamConcaveCap);
    h_Other_Combined->Add(h_Other_DownstreamConcaveCap);
    h_data_Combined->Add(h_data_DownstreamConcaveCap);

    ColorHists(h_Carbon_Combined, h_Iron_Combined, h_Lead_Combined,  h_Other_Combined);
    ColorData(h_data_Combined);
    Color_HeliumHists(h_Helium_UpstreamCap, h_Helium_Barrel, h_Helium_DownstreamCap, h_Helium_DownstreamConcaveCap);
    Color_AluminiumHists(h_Aluminium_UpstreamCap, h_Aluminium_Barrel, h_Aluminium_DownstreamCap, h_Aluminium_DownstreamConcaveCap);

    // MC Total depend on the Modification
    //      If Raws - take the mc_total directly
    //      If Modified - Add all mc models;

    TH1D* h_mc_total;
    if (ind == 0){
        h_mc_total = new TH1D(mc_total_UpstreamCap->GetCVHistoWithError());
        h_mc_total->Add(mc_total_Barrel);
        h_mc_total->Add(mc_total_DownstreamCap);
        h_mc_total->Add(mc_total_DownstreamConcaveCap);
    }
    else{
      h_mc_total =  (TH1D*)h_Helium_UpstreamCap->Clone("h_mc_total");
      //h_mc_total = new TH1D(*h_Helium_UpstreamCap);
      h_mc_total->Add(h_Helium_Barrel);
      h_mc_total->Add(h_Helium_DownstreamCap);
      h_mc_total->Add(h_Helium_DownstreamConcaveCap);

      h_mc_total->Add(h_Aluminium_UpstreamCap);
      h_mc_total->Add(h_Aluminium_Barrel);
      h_mc_total->Add(h_Aluminium_DownstreamCap);
      h_mc_total->Add(h_Aluminium_DownstreamConcaveCap);

      h_mc_total->Add(h_Carbon_Combined);
      h_mc_total->Add(h_Iron_Combined);
      h_mc_total->Add(h_Lead_Combined);
      h_mc_total->Add(h_Other_Combined);
    }

    // Scale Histograms
    //double mc_ratio = POT_ratio;

    double plot_chisq;
    if(UseLogChi == false){

      plot_chisq = calc_ChiSq(h_data_Combined,
       h_Helium_UpstreamCap,
       h_Helium_Barrel,
       h_Helium_DownstreamCap,
       h_Helium_DownstreamConcaveCap,
       h_Aluminium_UpstreamCap,
       h_Aluminium_Barrel,
       h_Aluminium_DownstreamCap,
       h_Aluminium_DownstreamConcaveCap,
       h_Carbon_Combined, h_Lead_Combined, h_Iron_Combined, h_Other_Combined);


    }
    else if(UseLogChi == true){

      plot_chisq = calc_LogChiSq(h_data_Combined,
       h_Helium_UpstreamCap,
       h_Helium_Barrel,
       h_Helium_DownstreamCap,
       h_Helium_DownstreamConcaveCap,
       h_Aluminium_UpstreamCap,
       h_Aluminium_Barrel,
       h_Aluminium_DownstreamCap,
       h_Aluminium_DownstreamConcaveCap,
       h_Carbon_Combined, h_Lead_Combined, h_Iron_Combined, h_Other_Combined);


    }

    if(doAreaNormalized == true){

      if(h_mc_total->GetNbinsX() !=h_data_Combined->GetNbinsX()){std::cout<<"~~~ Whoah Data and MC have different number of Bins HistTitle : "<< Hist_title<<std::endl; assert(false); }
      double MCArea = h_mc_total->Integral(1,h_mc_total->GetNbinsX());
      double DataArea = h_data_Combined->Integral(1,h_data_Combined->GetNbinsX());
      double areascaler = DataArea / MCArea;

      h_mc_total->Scale(areascaler);

      h_Helium_UpstreamCap->Scale(areascaler);
      h_Aluminium_UpstreamCap->Scale(areascaler);

      h_Helium_Barrel->Scale(areascaler);
      h_Aluminium_Barrel->Scale(areascaler);

      h_Helium_DownstreamCap->Scale(areascaler);
      h_Aluminium_DownstreamCap->Scale(areascaler);

      h_Helium_DownstreamConcaveCap->Scale(areascaler);
      h_Aluminium_DownstreamConcaveCap->Scale(areascaler);

      h_Carbon_Combined->Scale(areascaler);
      h_Iron_Combined->Scale(areascaler);
      h_Lead_Combined->Scale(areascaler);
      h_Other_Combined->Scale(areascaler);

    }

    h_Other_Combined->Add(h_Carbon_Combined);
    h_Other_Combined->Add(h_Iron_Combined);
    h_Other_Combined->Add(h_Lead_Combined);


    std::string yaxis;
    if(MakeBinWidth==true){

      h_mc_total->Scale(1.0, "width");

      h_Helium_UpstreamCap->Scale(1.0, "width");
      h_Aluminium_UpstreamCap->Scale(1.0, "width");

      h_Helium_Barrel->Scale(1.0, "width");
      h_Aluminium_Barrel->Scale(1.0, "width");

      h_Helium_DownstreamCap->Scale(1.0, "width");
      h_Aluminium_DownstreamCap->Scale(1.0, "width");

      h_Helium_DownstreamConcaveCap->Scale(1.0, "width");
      h_Aluminium_DownstreamConcaveCap->Scale(1.0, "width");

      //h_Carbon_Combined->Scale(1.0, "width");
      //h_Iron_Combined->Scale(1.0, "width");
      //h_Lead_Combined->Scale(1.0, "width");
      h_Other_Combined->Scale(1.0, "width");
      h_data_Combined->Scale(1.0, "width");

      double binwidth_title = h_mc_total -> GetBinWidth(3);
      yaxis = Form("NEvents / %.2f",binwidth_title);
      if(doAreaNormalized == true){yaxis = Form("[DataAreaNorm] NEvents / %.2f",binwidth_title);}
      //std::cout<< "yaxis = "<< yaxis<<std::endl;
      //std::cout<<"Finished Bin width Norm"<<std::endl;
    }
    else{
      yaxis = "NEvents";
    //  std::cout<<"FInished Bin NOT width Norm"<<std::endl;
    }

    // ------------------------------------------------------------------------
    // Unique Plot for Single Error Band, Single Universe
    //      Comment this section out
    // ------------------------------------------------------------------------


    // Create Canvas and Divide it into two
    TCanvas* c = new TCanvas("c","c",800, 800);
    //TCanvas cE("cE","cE", 800, 800);
    // Upper Pad is the Data vs MC
    //OLDTPad *pad1 = new TPad("pad1", "pad1", 0.05, 0.3, 1, 1.0);
    TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
    pad1->SetBottomMargin(0); // Top and Bottom Plots attached
    pad1->Draw();
    pad1->cd(); // pad1 is the current pad
      // Plot MC Models as THStack
    THStack* hs = new THStack("hs","");
    h_Helium_UpstreamCap->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
    hs->Add(h_Helium_UpstreamCap);
    hs->Add(h_Helium_Barrel);
    hs->Add(h_Helium_DownstreamCap);
    hs->Add(h_Helium_DownstreamConcaveCap);
    hs->Add(h_Aluminium_UpstreamCap);
    hs->Add(h_Aluminium_Barrel);
    hs->Add(h_Aluminium_DownstreamCap);
    hs->Add(h_Aluminium_DownstreamConcaveCap);
    //hs->Add(h_Carbon_Combined);
    //hs->Add(h_Iron_Combined);
    //hs->Add(h_Lead_Combined);
    hs->Add(h_Other_Combined);

    //std::cout<<"Finished adding hist to hs II"<<std::endl;

    // Styling
    hs->Draw("HIST");
    h_mc_total->SetMarkerStyle(0);
    h_mc_total->SetLineWidth(2);
    h_mc_total->SetLineColor(kBlack);
    h_mc_total->SetFillStyle(0);
    h_mc_total->Draw("same Hist");
    //gStyle->SetOptTitle(0);
    //gStyle->SetOptStat(0);


    hs->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
    hs->GetYaxis()->SetTitle(Form("%s",yaxis.c_str()));
    hs->GetYaxis()->SetTitleFont(62);
    hs->GetYaxis()->SetTitleSize(0.06);
    hs->GetXaxis()->SetTitleSize(0.06);
    hs->GetXaxis()->CenterTitle();
    //hs->GetYaxis()->SetTitleOffset(1.2);
    hs->GetYaxis()->SetLabelFont(42);
    hs->GetYaxis()->SetLabelSize(0.05);

    double hist_max = h_data_Combined->GetMaximum();
    //std::cout<<"GetMaximum() =  "<<hist_max<<std::endl;
    hs->SetMaximum(hist_max * 2.5);
    hs->SetMinimum(-1);
    c->Modified();

    //std::cout<<"Finshed Drawing Hist "<<std::endl;

    // Add Data Plot
    //h_data->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
    h_data_Combined->Draw("SAME E1 X0");

    //std::cout<<"FInished Drawing h_data"<<std::endl;

    // Add Legend
    TLegend *legend = new TLegend(0.75,0.55,0.91,0.92);
    legend->AddEntry(h_data_Combined, "Data");
    legend->AddEntry(h_mc_total, "Total MC" );
    legend->AddEntry(h_Helium_UpstreamCap,            "^{4}He USCap ",        "f");
    legend->AddEntry(h_Helium_Barrel,                 "^{4}He Barrel ",       "f");
    legend->AddEntry(h_Helium_DownstreamCap,          "^{4}He DSCap ",         "f");
    legend->AddEntry(h_Helium_DownstreamConcaveCap,   "^{4}He DSConcave", "f");
    legend->AddEntry(h_Aluminium_UpstreamCap,         "^{27}Al USCap",        "f");
    legend->AddEntry(h_Aluminium_Barrel,              "^{27}Al Barrel",       "f");
    legend->AddEntry(h_Aluminium_DownstreamCap,       "^{27}Al DSCap",         "f");
    legend->AddEntry(h_Aluminium_DownstreamConcaveCap,"^{27}Al DSConcave", "f");

    //legend->AddEntry(h_Carbon_Combined, "C: ",    "f");
    //legend->AddEntry(h_Iron_Combined,   "Fe: ",   "f");
    //legend->AddEntry(h_Lead_Combined,   "Pb: ",   "f");
    legend->AddEntry(h_Other_Combined,  "Other","f");
    legend->SetTextSize(0.025);
    legend->SetTextFont(42);
    legend->Draw();
    //std::cout<<"FInished Drawing legend"<<std::endl;

    // Add Weights as Text to Modified Plot
    int nPoints = h_data_Combined->GetNbinsX()-1;

    //std::cout<<"nPoints = "<<nPoints<< std::endl;

    // Add Plot-ChiSq
    TLatex* text = new TLatex;
    text->SetNDC();
    text->SetTextColor(kBlue);
    text->SetTextSize(0.03);
    text->DrawLatex(0.2, 0.85, Form("Plot #chi^{2} = %3.2f", plot_chisq));
    text->DrawLatex(0.2, 0.82, Form("Plot #chi^{2}/dof = %3.2f", plot_chisq / (double) nPoints));

      if (ind == 0){
        ChiSq_before_fit_var.push_back(plot_chisq);
        ChiSqrt = plot_chisq;
      }
      text->SetTextSize(0.03);

    if (ind != 0 && He_and_AlFit== false){
        int nPars = 4;
        //int nPoints = 136;
        //ChiSq_after_fit[0] = plot_chisq;
        //ChiSq_before_fit[0]= 17.65;
        //std::cout<<"making Fit info" <<  std::endl;
        //std::cout<<"ChiSq_before_fit[0] = "<< ChiSq_before_fit[0]<<std::endl;
          //std::cout<<"ChiSq_after_fit[0] = "<< plot_chisq<<std::endl;
        TLatex* text = new TLatex;

        text->SetNDC();
        double xplace = .2;
        double yplace = 0.80;
        text->DrawLatex(xplace, yplace, Form("Fit Results with %d points, %d pars", nPoints, nPars));
        yplace-=.02;
        text->DrawLatex(xplace, yplace , Form("Before Fit #chi^{2} = %3.2f", ChiSqrt));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("Before Fit #chi^{2}/dof = %3.2f", ChiSqrt/(nPoints-nPars)));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2} = %3.2f", plot_chisq));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2}/dof = %3.2f", plot_chisq/(double)(nPoints-nPars)));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{USCap wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[0], err_Aluminium[0]));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{Barrel wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[1], err_Aluminium[1]));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{DSCap wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[2], err_Aluminium[2]));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{DSConcave  wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[3], err_Aluminium[3]));
        yplace-=.02;
        ChiSqrtAfter = plot_chisq;
      //  delete text;
    }
    if (ind != 0 && He_and_AlFit== true){
        int nPars = 4;
        //int nPoints = 136;
        //ChiSq_after_fit[0] = plot_chisq;
        //ChiSq_before_fit[0]= 17.65;
        //std::cout<<"making Fit info" <<  std::endl;
        //std::cout<<"ChiSq_before_fit[0] = "<< ChiSq_before_fit[0]<<std::endl;
          //std::cout<<"ChiSq_after_fit[0] = "<< plot_chisq<<std::endl;
        TLatex* text = new TLatex;
        text->SetNDC();
        double xplace = .2;
        double yplace = 0.80;
        text->DrawLatex(xplace, yplace, Form("Fit Results with %d points, %d pars", nPoints, nPars));
        yplace-=.02;
        text->DrawLatex(xplace, yplace , Form("Before Fit #chi^{2} = %3.2f", ChiSqrt));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("Before Fit #chi^{2}/dof = %3.2f", ChiSqrt/(nPoints-nPars)));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2} = %3.2f", plot_chisq));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2}/dof = %3.2f", plot_chisq/(double)(nPoints-nPars)));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{USCap wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[0], err_Aluminium[0]));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{Barrel wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[1], err_Aluminium[1]));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{DSCap wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[2], err_Aluminium[2]));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{DSConcave wgt(He) = %3.2f #pm %3.2f}", wgt_Aluminium[3], err_Aluminium[3]));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{USCap wgt(He) = %3.2f #pm %3.2f}", wgt_Helium[0], err_Helium[0]));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{barrel wgt(He) = %3.2f #pm %3.2f}", wgt_Helium[1], err_Helium[1]));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{DSCap wgt(He) = %3.2f #pm %3.2f}", wgt_Helium[2], err_Helium[2]));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{DSConcave  wgt(He) = %3.2f #pm %3.2f}", wgt_Helium[3], err_Helium[3]));

        ChiSqrtAfter = plot_chisq;
      //  delete text;
    }
    delete text;
    plotter->AddHistoTitle(Hist_title.c_str(),.04);
    plotter->WritePreliminary("TL", .025, 0, 0, false);
    // Plot Lower Plot: Data vs MC Ratio
    c->cd(); // Go back to default Canvas before creating 2nd Pad
    //TPad *pad2 = new TPad("pad2", "pad2", 0.05, 0.05, 1, 0.3);

    //pad2->SetTopMargin(0);
    //pad2->SetBottomMargin(0.2);
    c->Modified();
    TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
    pad2->SetTopMargin(0);
    pad2->SetBottomMargin(0.2);
    pad2->SetGridx(); // vertical grid
    pad2->Draw();
    pad2->cd();

    // Calculate the Ratio

    //h_data_mc_ratio->Draw("HIST");
    plotter->axis_title_size_x = 0.1;
    plotter->axis_title_offset_y = .4;
    plotter->axis_title_offset_x = 1.35;
    plotter->axis_title_size_y = 0.12;
    plotter->axis_label_size = 0.1;
    plotter->axis_maximum = 2.5;
    plotter->axis_minimum = .5;
    plotter->DrawDataMCRatio(data, mc_total, 1.0, false, false , -.5, 2, "#frac{Data}{MC}", false);
    // Add Ratio = 1 Line
    TLine ratio_1;
    ratio_1.SetLineWidth(2);
    ratio_1.SetLineStyle(7);
    ratio_1.SetLineColor(kBlue);
    double line_min = h_data_Combined->GetBinLowEdge(1);
    double line_max = h_data_Combined->GetBinLowEdge(h_data_Combined->GetNbinsX()+1);
    ratio_1.DrawLine(line_min,1,line_max,1);
    // Plot Output
    c->Update();
    c->cd();
    c->Print(pdf_label.c_str(),"pdf");

    delete legend;
    delete hs;
    delete pad1;
    delete pad2;
    delete c;
    delete data;
    delete mc_total;
    delete h_data_Combined;
    delete h_Helium_UpstreamCap;
    delete h_Aluminium_UpstreamCap;
    delete h_Carbon_Combined;
    delete h_Iron_Combined;
    delete h_Lead_Combined;
    delete h_Other_Combined;
    delete h_data_Barrel;
    delete h_Helium_Barrel;
    delete h_Aluminium_Barrel;
    delete h_Carbon_Barrel;
    delete h_Iron_Barrel;
    delete h_Lead_Barrel;
    delete h_Other_Barrel;
    delete h_data_DownstreamCap;
    delete h_Helium_DownstreamCap;
    delete h_Aluminium_DownstreamCap;
    delete h_Carbon_DownstreamCap;
    delete h_Iron_DownstreamCap;
    delete h_Lead_DownstreamCap;
    delete h_Other_DownstreamCap;
    delete h_data_DownstreamConcaveCap;
    delete h_Helium_DownstreamConcaveCap;
    delete h_Aluminium_DownstreamConcaveCap;
    delete h_Carbon_DownstreamConcaveCap;
    delete h_Iron_DownstreamConcaveCap;
    delete h_Lead_DownstreamConcaveCap;
    delete h_Other_DownstreamConcaveCap;
  }


void Helium_3CryoRegionsSideBandTool::Plot_regions(std::string pdf_label, int ind, double POT_ratio,
       MnvH1D* data_region1, MnvH1D* mc_total_region1, MnvH1D* Helium_region1, MnvH1D* Aluminium_region1, MnvH1D* Carbon_region1,
       MnvH1D* Iron_region1, MnvH1D* Lead_region1, MnvH1D* Other_region1,

       MnvH1D* data_region2, MnvH1D* mc_total_region2, MnvH1D* Helium_region2, MnvH1D* Aluminium_region2, MnvH1D* Carbon_region2,
       MnvH1D* Iron_region2, MnvH1D* Lead_region2, MnvH1D* Other_region2,

       MnvH1D* data_region3, MnvH1D* mc_total_region3, MnvH1D* Helium_region3, MnvH1D* Aluminium_region3, MnvH1D* Carbon_region3,
       MnvH1D* Iron_region3, MnvH1D* Lead_region3, MnvH1D* Other_region3,

       MnvH1D* data_region4, MnvH1D* mc_total_region4, MnvH1D* Helium_region4, MnvH1D* Aluminium_region4, MnvH1D* Carbon_region4,
       MnvH1D* Iron_region4, MnvH1D* Lead_region4, MnvH1D* Other_region4,

       std::string Hist_title, std::string xaxislabel, double &ChiSqrt,
       double &ChiSqrtAfter, int FitType, bool UseLogChi, bool doAreaNormalized, bool applyMaxY , double MaxY)
       {

        std::string type;
        if (ind == 0) type = "Nominal";
        else type = "Fitted";
        //std::cout<<"Ploting type: Combined CryoRegions  "<< type<<std::endl;

        //PlotUtils::MnvPlotter* plotter= new mnvPlotter();
         MnvPlotter* plotter = new MnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
        //plotter(PlotUtils::kCCInclusiveHeliumStyle);
        MnvH1D *data = (PlotUtils::MnvH1D*)data_region1->Clone("data");

        data->Add(data_region2);
        data->Add(data_region3);
        data->Add(data_region4);

        MnvH1D *mc_total = (PlotUtils::MnvH1D*)Helium_region1->Clone("mc_total");

        mc_total->Add(Aluminium_region1 );
        mc_total->Add(Carbon_region1);
        mc_total->Add(Iron_region1 );
        mc_total->Add(Lead_region1 );
        mc_total->Add(Other_region1);

        mc_total->Add(Helium_region2 );
        mc_total->Add(Aluminium_region2 );
        mc_total->Add(Carbon_region2);
        mc_total->Add(Iron_region2 );
        mc_total->Add(Lead_region2 );
        mc_total->Add(Other_region2);

        mc_total->Add(Helium_region3 );
        mc_total->Add(Aluminium_region3 );
        mc_total->Add(Carbon_region3);
        mc_total->Add(Iron_region3 );
        mc_total->Add(Lead_region3 );
        mc_total->Add(Other_region3);

        mc_total->Add(Helium_region4 );
        mc_total->Add(Aluminium_region4 );
        mc_total->Add(Carbon_region4);
        mc_total->Add(Iron_region4 );
        mc_total->Add(Lead_region4 );
        mc_total->Add(Other_region4);

        data->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
        mc_total->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));


        TH1D* h_data_Combined = new TH1D(data_region1->GetCVHistoWithError());
        //TH1D* h_TOTAL = new TH1D(Helium_region1->GetCVHistoWithError());

        TH1D* h_Helium_region1 = new TH1D(Helium_region1->GetCVHistoWithError());
        TH1D* h_Aluminium_region1 = new TH1D(Aluminium_region1->GetCVHistoWithError());
        TH1D* h_Carbon_Combined = new TH1D(Carbon_region1->GetCVHistoWithError());
        TH1D* h_Iron_Combined = new TH1D(Iron_region1->GetCVHistoWithError());
        TH1D* h_Lead_Combined = new TH1D(Lead_region1->GetCVHistoWithError());
        TH1D* h_Other_Combined = new TH1D(Other_region1->GetCVHistoWithError());

        TH1D* h_data_region2 = new TH1D(data_region2->GetCVHistoWithError());
        TH1D* h_Helium_region2 = new TH1D(Helium_region2->GetCVHistoWithError());
        TH1D* h_Aluminium_region2 = new TH1D(Aluminium_region2->GetCVHistoWithError());
        TH1D* h_Carbon_region2 = new TH1D(Carbon_region2->GetCVHistoWithError());
        TH1D* h_Iron_region2 = new TH1D(Iron_region2->GetCVHistoWithError());
        TH1D* h_Lead_region2 = new TH1D(Lead_region2->GetCVHistoWithError());
        TH1D* h_Other_region2 = new TH1D(Other_region2->GetCVHistoWithError());

        h_Carbon_Combined->Add(h_Carbon_region2);
        h_Iron_Combined->Add(h_Iron_region2);
        h_Lead_Combined->Add(h_Lead_region2);
        h_Other_Combined->Add(h_Other_region2);
        h_data_Combined->Add(h_data_region2);

        TH1D* h_data_region3 = new TH1D(data_region3->GetCVHistoWithError());
        TH1D* h_Helium_region3 = new TH1D(Helium_region3->GetCVHistoWithError());
        TH1D* h_Aluminium_region3 = new TH1D(Aluminium_region3->GetCVHistoWithError());

        TH1D* h_Carbon_region3 = new TH1D(Carbon_region3->GetCVHistoWithError());
        TH1D* h_Iron_region3 = new TH1D(Iron_region3->GetCVHistoWithError());
        TH1D* h_Lead_region3 = new TH1D(Lead_region3->GetCVHistoWithError());
        TH1D* h_Other_region3 = new TH1D(Other_region3->GetCVHistoWithError());

        h_Carbon_Combined->Add(h_Carbon_region3);
        h_Iron_Combined->Add(  h_Iron_region3);
        h_Lead_Combined->Add(  h_Lead_region3);
        h_Other_Combined->Add( h_Other_region3);
        h_data_Combined->Add(  h_data_region3);

        TH1D* h_data_region4 = new TH1D(data_region4->GetCVHistoWithError());
        TH1D* h_Helium_region4 = new TH1D(Helium_region4->GetCVHistoWithError());
        TH1D* h_Aluminium_region4 = new TH1D(Aluminium_region4->GetCVHistoWithError());

        TH1D* h_Carbon_region4 = new TH1D(Carbon_region4->GetCVHistoWithError());
        TH1D* h_Iron_region4 = new TH1D(Iron_region4->GetCVHistoWithError());
        TH1D* h_Lead_region4 = new TH1D(Lead_region4->GetCVHistoWithError());
        TH1D* h_Other_region4 = new TH1D(Other_region4->GetCVHistoWithError());


        h_Carbon_Combined->Add(h_Carbon_region4);
        h_Iron_Combined->Add(h_Iron_region4);
        h_Lead_Combined->Add(h_Lead_region4);
        h_Other_Combined->Add(h_Other_region4);

        h_data_Combined->Add(h_data_region4);

          //h_TOTAL->Add(h_Aluminium_region1 );
          //h_TOTAL->Add(h_Helium_region2 );
          //h_TOTAL->Add(h_Aluminium_region2 );
          //h_TOTAL->Add(h_Helium_region3 );
          //h_TOTAL->Add(h_Aluminium_region3 );
          //h_TOTAL->Add(h_Helium_region4 );
          //h_TOTAL->Add(h_Aluminium_region4 );

          //h_TOTAL->Add(h_Carbon_Combined );
          //h_TOTAL->Add(h_Iron_Combined );
          //h_TOTAL->Add(h_Lead_Combined );
          //h_TOTAL->Add(h_Other_Combined );


        ColorHists(h_Carbon_Combined, h_Iron_Combined, h_Lead_Combined,  h_Other_Combined);
        ColorData(h_data_Combined);
        Color_HeliumHists(h_Helium_region1, h_Helium_region2, h_Helium_region3, h_Helium_region4);
        Color_AluminiumHists(h_Aluminium_region1, h_Aluminium_region2, h_Aluminium_region3, h_Aluminium_region4);

        // MC Total depend on the Modification
        //      If Raws - take the mc_total directly
        //      If Modified - Add all mc models;


        TH1D* h_mc_total = new TH1D(mc_total->GetCVHistoWithError());


      //double total1 =   h_TOTAL->Integral(1,h_TOTAL->GetNbinsX());
      double total2 =   h_mc_total->Integral(1,h_mc_total->GetNbinsX());
/*if(total1 !=total2){
std::cout<<"Checking the intergal of the histgrams"<<std::endl;


std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"total1 = " <<total1<<std::endl;
std::cout<<"total2 = " <<total2<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<< "Hist_title = "<< Hist_title<<std::endl;
}
*/

/*
        if (ind == 0){
            h_mc_total = new TH1D(mc_total_region1->GetCVHistoWithError());
            h_mc_total->Add(mc_total_region2);
            h_mc_total->Add(mc_total_region3);
            h_mc_total->Add(mc_total_region4);
        }
        else{

//TH1F *hnew =
          h_mc_total = (TH1D*)h_Helium_region1->Clone();  //new TH1D(h_Helium_region1->GetCVHistoWithError());
          h_mc_total->Add(h_Helium_region2);
          h_mc_total->Add(h_Helium_region3);
          h_mc_total->Add(h_Helium_region4);

          h_mc_total->Add(h_Aluminium_region1);
          h_mc_total->Add(h_Aluminium_region2);
          h_mc_total->Add(h_Aluminium_region3);
          h_mc_total->Add(h_Aluminium_region4);

          h_mc_total->Add(h_Carbon_Combined);
          h_mc_total->Add(h_Iron_Combined);
          h_mc_total->Add(h_Lead_Combined);
          h_mc_total->Add(h_Other_Combined);
        }
*/
        h_mc_total->SetName("h_mc_total");

        double plot_chisq;
        //double plot_chisq = calc_ChiSq(data, signal, WithPi0, QELike, SinglePiPlus, Other);

        if(UseLogChi == false){plot_chisq = calc_ChiSq(h_data_Combined,
          h_Helium_region1,
          h_Helium_region2,
          h_Helium_region3,
          h_Helium_region4,
          h_Aluminium_region1,
          h_Aluminium_region2,
          h_Aluminium_region3,
          h_Aluminium_region4,
          h_Carbon_Combined, h_Lead_Combined, h_Iron_Combined, h_Other_Combined);}
        else if(UseLogChi == true){plot_chisq = calc_LogChiSq(h_data_Combined,
          h_Helium_region1,
          h_Helium_region2,
          h_Helium_region3,
          h_Helium_region4,
          h_Aluminium_region1,
          h_Aluminium_region2,
          h_Aluminium_region3,
          h_Aluminium_region4,
          h_Carbon_Combined, h_Lead_Combined, h_Iron_Combined, h_Other_Combined);}


          h_Other_Combined->Add(h_Carbon_Combined);
          h_Other_Combined->Add(h_Iron_Combined);
          h_Other_Combined->Add(h_Lead_Combined);


          if(doAreaNormalized == true){

            if(h_mc_total->GetNbinsX() !=h_data_Combined->GetNbinsX()){std::cout<<"~~~ Whoah Data and MC have different number of Bins HistTitle : "<< Hist_title<<std::endl; assert(false); }
            double MCArea = h_mc_total->Integral(1,h_mc_total->GetNbinsX());
            double DataArea = h_data_Combined->Integral(1,h_data_Combined->GetNbinsX());
            double areascaler = DataArea / MCArea;

            h_mc_total->Scale(areascaler);
            //h_TOTAL->Scale(areascaler);
            h_Helium_region1->Scale(areascaler);
            h_Aluminium_region1->Scale(areascaler);

            h_Helium_region2->Scale(areascaler);
            h_Aluminium_region2->Scale(areascaler);

            h_Helium_region3->Scale(areascaler);
            h_Aluminium_region3->Scale(areascaler);

            h_Helium_region4->Scale(areascaler);
            h_Aluminium_region4->Scale(areascaler);

            //h_Carbon_Combined->Scale(areascaler);
            //h_Iron_Combined->Scale(areascaler);
            //h_Lead_Combined->Scale(areascaler);
            h_Other_Combined->Scale(areascaler);

          }

          //////////////////////////////////////
          //// Combining All Other
          //////////////////////////////////////



        std::string yaxis;
        if(MakeBinWidth==true){
        //  h_TOTAL->Scale(1.0, "width");
          h_mc_total->Scale(1.0, "width");

          h_Helium_region1->Scale(1.0, "width");
          h_Aluminium_region1->Scale(1.0, "width");

          h_Helium_region2->Scale(1.0, "width");
          h_Aluminium_region2->Scale(1.0, "width");

          h_Helium_region3->Scale(1.0, "width");
          h_Aluminium_region3->Scale(1.0, "width");

          h_Helium_region4->Scale(1.0, "width");
          h_Aluminium_region4->Scale(1.0, "width");

          //h_Carbon_Combined->Scale(1.0, "width");
          //h_Iron_Combined->Scale(1.0, "width");
          //h_Lead_Combined->Scale(1.0, "width");
          h_Other_Combined->Scale(1.0, "width");
          h_data_Combined->Scale(1.0, "width");

          double binwidth_title = h_mc_total -> GetBinWidth(3);
          yaxis = Form("NEvents / %.2f",binwidth_title);
          if(doAreaNormalized == true){yaxis = Form("[DataAreaNorm] NEvents / %.2f",binwidth_title);}
          //std::cout<< "yaxis = "<< yaxis<<std::endl;
          //std::cout<<"Finished Bin width Norm"<<std::endl;
        }
        else{
          yaxis = "NEvents";
        //  std::cout<<"FInished Bin NOT width Norm"<<std::endl;
        }

        // ------------------------------------------------------------------------
        // Unique Plot for Single Error Band, Single Universe
        //      Comment this section out
        // ------------------------------------------------------------------------


        // Create Canvas and Divide it into two
        TCanvas* c = new TCanvas("c","c",800, 800);
        //TCanvas cE("cE","cE", 800, 800);
        // Upper Pad is the Data vs MC
        //OLDTPad *pad1 = new TPad("pad1", "pad1", 0.05, 0.3, 1, 1.0);
        TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
        pad1->SetBottomMargin(0); // Top and Bottom Plots attached
        pad1->Draw();
        pad1->cd(); // pad1 is the current pad
          // Plot MC Models as THStack
        THStack* hs = new THStack("hs","");
        h_Helium_region1->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
        hs->Add(h_Helium_region1);
        hs->Add(h_Helium_region2);
        hs->Add(h_Helium_region3);
        hs->Add(h_Helium_region4);
        hs->Add(h_Aluminium_region1);
        hs->Add(h_Aluminium_region2);
        hs->Add(h_Aluminium_region3);
        hs->Add(h_Aluminium_region4);
      //  hs->Add(h_Carbon_Combined);
        //hs->Add(h_Iron_Combined);
        //hs->Add(h_Lead_Combined);
        hs->Add(h_Other_Combined);

/*
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~Checking ~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
double total_mctotal = h_mc_total->Integral(1,h_mc_total->GetNbinsX());
double N_Helium_region1 =  h_Helium_region1->Integral(1, h_Helium_region1->GetNbinsX());
double N_Helium_region2 =  h_Helium_region2->Integral(1, h_Helium_region2->GetNbinsX());
double N_Helium_region3 =  h_Helium_region3->Integral(1, h_Helium_region3->GetNbinsX());
double N_Helium_region4 =  h_Helium_region4->Integral(1, h_Helium_region4->GetNbinsX());
double N_Aluminium_region1 =  h_Aluminium_region1->Integral(1, h_Aluminium_region1->GetNbinsX());
double N_Aluminium_region2 =  h_Aluminium_region2->Integral(1, h_Aluminium_region2->GetNbinsX());
double N_Aluminium_region3 =  h_Aluminium_region3->Integral(1, h_Aluminium_region3->GetNbinsX());
double N_Aluminium_region4 =  h_Aluminium_region4->Integral(1, h_Aluminium_region4->GetNbinsX());
double N_Other_Combined =  h_Other_Combined->Integral(1, h_Other_Combined->GetNbinsX());
double totalRegions = N_Helium_region1 + N_Helium_region2 + N_Helium_region3 + N_Helium_region4 + N_Aluminium_region1 + N_Aluminium_region2 + N_Aluminium_region3 + N_Aluminium_region4 + N_Other_Combined;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

std::cout<<" total_mctotal =" << total_mctotal << std::endl;

std::cout<<" totalRegions =" << totalRegions << std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"N_Helium_region1 = " << N_Helium_region1 << std::endl;
std::cout<<"N_Helium_region2 = " << N_Helium_region2 << std::endl;
std::cout<<"N_Helium_region3 = " << N_Helium_region3 << std::endl;
std::cout<<"N_Helium_region4 = " << N_Helium_region4 << std::endl;
std::cout<<"N_Aluminium_region1 = " << N_Aluminium_region1 << std::endl;
std::cout<<"N_Aluminium_region2 = " << N_Aluminium_region2 << std::endl;
std::cout<<"N_Aluminium_region3 = " << N_Aluminium_region3 << std::endl;
std::cout<<"N_Aluminium_region4 = " << N_Aluminium_region4 << std::endl;
std::cout<<"N_Other_Combined = " << N_Other_Combined << std::endl;

*/



        //std::cout<<"Finished adding hist to hs II"<<std::endl;

        // Styling
        hs->Draw("HIST");
        hs->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
        hs->GetYaxis()->SetTitle(Form("%s",yaxis.c_str()));
        hs->GetYaxis()->SetTitleFont(62);
        hs->GetYaxis()->SetTitleSize(0.06);
        hs->GetXaxis()->SetTitleSize(0.06);
        hs->GetXaxis()->CenterTitle();
        //hs->GetYaxis()->SetTitleOffset(1.2);
        hs->GetYaxis()->SetLabelFont(42);
        hs->GetYaxis()->SetLabelSize(0.05);

      if(applyMaxY==false){
        if(h_mc_total->GetMaximum()>h_data_Combined->GetMaximum()  ){
          hs->SetMaximum(h_mc_total->GetMaximum() * 1.45);
        }
        else { hs->SetMaximum(h_data_Combined->GetMaximum() * 1.45);}
       }
      else if (applyMaxY==true){
       hs->SetMaximum(MaxY);
      }

      hs->SetMinimum(-1);
//        hs->SetMaximum(hist_max * 1.45);
 //
        h_mc_total->SetMarkerStyle(0);
        h_mc_total->SetLineWidth(2);
        h_mc_total->SetLineColor(kBlack);
        h_mc_total->SetFillStyle(0);
        //h_mc_total->Draw("SAME HIST");


        //std::cout<<"Finshed Drawing Hist "<<std::endl;

        // Add Data Plot
        h_data_Combined->Draw("SAME E1 X0");
        //std::cout<<"FInished Drawing h_data"<<std::endl;

        // Add Legend
        TLegend *legend = new TLegend(0.75,0.55,0.91,0.92);
        legend->AddEntry(h_data_Combined, "Data");
        //legend->AddEntry(h_mc_total, "Total MC");
        // Add Weights as Text to Modified Plot
        int nPoints = h_data_Combined->GetNbinsX()-1;

        //std::cout<<"nPoints = "<<nPoints<< std::endl;

        // Add Plot-ChiSq
        TLatex* text = new TLatex;
        text->SetNDC();
        text->SetTextSize(0.03);
        text->SetTextColor(kBlue);




          if (ind == 0){
            ChiSq_before_fit_var.push_back(plot_chisq);
            ChiSqrt = plot_chisq;
          }


          if(FitType == 3){
            legend->AddEntry(h_Helium_region1,          "XCenter He: ",           "f");
            legend->AddEntry(h_Helium_region2,          "XLeftShelf He: ",        "f");
            legend->AddEntry(h_Helium_region3,          "XRightShelf He: ",       "f");
            legend->AddEntry(h_Helium_region4,          "XoutsideEdges He: ",     "f");
            legend->AddEntry(h_Aluminium_region1,       "XCenter Al: ",           "f");
            legend->AddEntry(h_Aluminium_region2,       "XLeftShelf Al: ",       "f");
            legend->AddEntry(h_Aluminium_region3,       "XRightShelf Al: ",      "f");
            legend->AddEntry(h_Aluminium_region4,       "XoutsideEdges Al: ", "f");
          }
          else if(FitType == 4){
            legend->AddEntry(h_Helium_region1,          "XCenter He: ",           "f");
            legend->AddEntry(h_Helium_region2,          "XLeftShelf He: ",        "f");
            legend->AddEntry(h_Helium_region3,          "XRightShelf He: ",       "f");
            legend->AddEntry(h_Helium_region4,          "^{4}He DSConcave ",     "f");
            legend->AddEntry(h_Aluminium_region1,       "XCenter Al: ",           "f");
            legend->AddEntry(h_Aluminium_region2,       "XLeftShelf Al: ",       "f");
            legend->AddEntry(h_Aluminium_region3,       "XRightShelf Al: ",      "f");
            legend->AddEntry(h_Aluminium_region4,       "^{27}Al DSConcave ", "f");
          }

          else{
            legend->AddEntry(h_Helium_region1,    "^{4}He USCap ",         "f");
            legend->AddEntry(h_Helium_region2,    "^{4}He Barrel ",        "f");
            legend->AddEntry(h_Helium_region3,    "^{4}He DSCap ",         "f");
            legend->AddEntry(h_Helium_region4,    "^{4}He DSConcave",      "f");
            legend->AddEntry(h_Aluminium_region1, "^{27}Al USCap ",        "f");
            legend->AddEntry(h_Aluminium_region2, "^{27}Al Barrel ",       "f");
            legend->AddEntry(h_Aluminium_region3, "^{27}Al DSCap ",         "f");
            legend->AddEntry(h_Aluminium_region4, "^{27}Al DSConcave",      "f");
          }

          //legend->AddEntry(h_Carbon_Combined, "C: ",    "f");
          //legend->AddEntry(h_Iron_Combined,   "Fe: ",   "f");
          //legend->AddEntry(h_Lead_Combined,   "Pb: ",   "f");
          legend->AddEntry(h_Other_Combined,  "Other","f");

          text->SetTextSize(0.03);
          text->DrawLatex(0.2, 0.85, Form("Plot #chi^{2} = %3.2f", plot_chisq));
          text->DrawLatex(0.2, 0.82, Form("Plot #chi^{2}/dof = %3.2f", plot_chisq / (double) nPoints));

          legend->SetTextSize(0.025);
          legend->SetTextFont(42);
          legend->Draw();
          text->SetTextSize(0.02);
          text->SetTextColor(kBlack);

        if (ind != 0 &&  FitType== 1){
        int nPars = 4;
        double xplace = .2;
        double yplace = 0.80;
        text->DrawLatex(xplace, yplace, Form("Fit Results with %d points, %d pars", nPoints, nPars));
        yplace-=.02;
        text->DrawLatex(xplace, yplace , Form("Before Fit #chi^{2} = %3.2f", ChiSqrt));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("Before Fit #chi^{2}/dof = %3.2f", ChiSqrt/(nPoints-nPars)));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2} = %3.2f", plot_chisq));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2}/dof = %3.2f", plot_chisq/(double)(nPoints-nPars)));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{USCap wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[0], err_Aluminium[0]));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{Barrel wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[1], err_Aluminium[1]));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{DSCap wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[2], err_Aluminium[2]));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{DSConcave  wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[3], err_Aluminium[3]));
        yplace-=.02;
        ChiSqrtAfter = plot_chisq;

        }
        else if (ind != 0 && FitType == 2){
        int nPars = 4;
          double xplace = .2;
          double yplace = 0.80;
          text->DrawLatex(xplace, yplace, Form("Fit Results with %d points, %d pars", nPoints, nPars));
          yplace-=.02;
          text->DrawLatex(xplace, yplace , Form("Before Fit #chi^{2} = %3.2f", ChiSqrt));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("Before Fit #chi^{2}/dof = %3.2f", ChiSqrt/(nPoints-nPars)));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2} = %3.2f", plot_chisq));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2}/dof = %3.2f", plot_chisq/(double)(nPoints-nPars)));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("#color[4]{USCap wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[0], err_Aluminium[0]));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("#color[4]{Barrel wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[1], err_Aluminium[1]));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("#color[4]{DSCap wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[2], err_Aluminium[2]));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("#color[4]{DSConcave  wgt(He) = %3.2f #pm %3.2f}", wgt_Aluminium[3], err_Aluminium[3]));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("#color[4]{USCap wgt(He) = %3.2f #pm %3.2f}", wgt_Helium[0], err_Helium[0]));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("#color[4]{barrel wgt(He) = %3.2f #pm %3.2f}", wgt_Helium[1], err_Helium[1]));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("#color[4]{DSCap wgt(He) = %3.2f #pm %3.2f}", wgt_Helium[2], err_Helium[2]));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("#color[4]{DSConcave  wgt(He) = %3.2f #pm %3.2f}", wgt_Helium[3], err_Helium[3]));

          ChiSqrtAfter = plot_chisq;

        }
        else if(ind != 0 && FitType == 3){
        int nPars = 4;

        double xplace = .2;
        double yplace = 0.80;
        text->DrawLatex(xplace, yplace, Form("Fit Results with %d points, %d pars", nPoints, nPars));
        yplace-=.02;
        text->DrawLatex(xplace, yplace ,Form("Before Fit #chi^{2} = %3.2f", ChiSqrt));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("Before Fit #chi^{2}/dof = %3.2f", ChiSqrt/(nPoints-nPars)));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2} = %3.2f", plot_chisq));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2}/dof = %3.2f", plot_chisq/(double)(nPoints-nPars)));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{XCenter wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[0], err_Aluminium[0]));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{XLeftShelf wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[1], err_Aluminium[1]));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{XRightShelf wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[2], err_Aluminium[2]));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{XoutsideEdges cap wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[3], err_Aluminium[3]));
        yplace-=.02;
        ChiSqrtAfter = plot_chisq;

        }
        else if(ind != 0 && FitType == 4){
        int nPars = 4;
        double xplace = .2;
        double yplace = 0.80;
        text->DrawLatex(xplace, yplace, Form("Fit Results with %d points, %d pars", nPoints, nPars));
        yplace-=.02;
        text->DrawLatex(xplace, yplace ,Form("Before Fit #chi^{2} = %3.2f", ChiSqrt));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("Before Fit #chi^{2}/dof = %3.2f", ChiSqrt/(nPoints-nPars)));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2} = %3.2f", plot_chisq));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2}/dof = %3.2f", plot_chisq/(double)(nPoints-nPars)));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{XCenter wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[0], err_Aluminium[0]));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{XLeftShelf wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[1], err_Aluminium[1]));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{XRightShelf wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[2], err_Aluminium[2]));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{DSConcave  wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[3], err_Aluminium[3]));
        yplace-=.02;
        ChiSqrtAfter = plot_chisq;

        }

        delete text;
        plotter->AddHistoTitle(Hist_title.c_str(),.04);
        plotter->WritePreliminary("TL", .025, 0, 0, false);
        // Plot Lower Plot: Data vs MC Ratio
        c->cd(); // Go back to default Canvas before creating 2nd Pad
        //TPad *pad2 = new TPad("pad2", "pad2", 0.05, 0.05, 1, 0.3);

        //pad2->SetTopMargin(0);
        //pad2->SetBottomMargin(0.2);
        c->Modified();
        TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
        pad2->SetTopMargin(0);
        pad2->SetBottomMargin(0.2);
        pad2->SetGridx(); // vertical grid
        pad2->Draw();
        pad2->cd();

        // Calculate the Ratio

        //h_data_mc_ratio->Draw("HIST");
        plotter->axis_title_size_x = 0.1;
        plotter->axis_title_offset_y = .4;
        plotter->axis_title_offset_x = 1.35;
        plotter->axis_title_size_y = 0.12;
        plotter->axis_label_size = 0.1;
        plotter->axis_maximum = 2.5;
        plotter->axis_minimum = .5;
        plotter->DrawDataMCRatio(data, mc_total, 1.0, false, false , -.5, 2, "#frac{Data}{MC}", false);
        // Add Ratio = 1 Line
        TLine ratio_1;
        ratio_1.SetLineWidth(2);
        ratio_1.SetLineStyle(7);
        ratio_1.SetLineColor(kBlue);
        double line_min = h_data_Combined->GetBinLowEdge(1);
        double line_max = h_data_Combined->GetBinLowEdge(h_data_Combined->GetNbinsX()+1);
        ratio_1.DrawLine(line_min,1,line_max,1);
        // Plot Output
        c->Update();
        c->cd();
        c->Print(pdf_label.c_str(),"pdf");
        delete plotter;
        delete legend;
        delete hs;
        delete pad1;
        delete pad2;
        delete c;
        delete data;
        delete mc_total;
        delete h_data_Combined;
        delete h_Helium_region1;
        delete h_Aluminium_region1;
        delete h_Carbon_Combined;
        delete h_Iron_Combined;
        delete h_Lead_Combined;
        delete h_Other_Combined;
        delete h_data_region2;
        delete h_Helium_region2;
        delete h_Aluminium_region2;
        delete h_Carbon_region2;
        delete h_Iron_region2;
        delete h_Lead_region2;
        delete h_Other_region2;
        delete h_data_region3;
        delete h_Helium_region3;
        delete h_Aluminium_region3;
        delete h_Carbon_region3;
        delete h_Iron_region3;
        delete h_Lead_region3;
        delete h_Other_region3;
        delete h_data_region4;
        delete h_Helium_region4;
        delete h_Aluminium_region4;
        delete h_Carbon_region4;
        delete h_Iron_region4;
        delete h_Lead_region4;
        delete h_Other_region4;
      }
////////////////////////////////////////////////////////////////////////////////
void Helium_3CryoRegionsSideBandTool::fill_CryoRegion14_HistMap_vertex_X_Material(
  CryoRegion_HeliumNSideBand_Map CryoRegionMap,
  CryoRegion_HistMap &Helium_Map,
  CryoRegion_HistMap &Al_Map,
  CryoRegion_HistMap &Other_Map, int ind){

    for(auto region : CryoRegion14_vector){

      MnvH1D* h_MC_Helium = (MnvH1D*)CryoRegionMap[region].MnvH1D_Vertex_X_Helium[ind]->Clone("h_MC_Helium");
      MnvH1D* h_MC_Al = (MnvH1D*)CryoRegionMap[region].MnvH1D_Vertex_X_Aluminium[ind]->Clone("h_MC_Al");
      MnvH1D* h_MC_Other = (MnvH1D*)CryoRegionMap[region].MnvH1D_Vertex_X_Other[ind]->Clone("h_MC_Other");

      h_MC_Other->Add(CryoRegionMap[region].MnvH1D_Vertex_X_Carbon[ind]);
      h_MC_Other->Add(CryoRegionMap[region].MnvH1D_Vertex_X_Iron[ind]);
      h_MC_Other->Add(CryoRegionMap[region].MnvH1D_Vertex_X_Lead[ind]);

      Helium_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_MC_Helium));
      Al_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_MC_Al));
      Other_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_MC_Other));

    }

  }
  ////////////////////////////////////////////////////////////////////////////////
  void Helium_3CryoRegionsSideBandTool::fill_CryoRegion14_HistMap_vertex_Y_Material(
    CryoRegion_HeliumNSideBand_Map CryoRegionMap,
    CryoRegion_HistMap &Helium_Map,
    CryoRegion_HistMap &Al_Map,
    CryoRegion_HistMap &Other_Map, int ind){

      for(auto region : CryoRegion14_vector){

        MnvH1D* h_MC_Helium = (MnvH1D*)CryoRegionMap[region].MnvH1D_Vertex_Y_Helium[ind]->Clone("h_MC_Helium");
        MnvH1D* h_MC_Al = (MnvH1D*)CryoRegionMap[region].MnvH1D_Vertex_Y_Aluminium[ind]->Clone("h_MC_Al");
        MnvH1D* h_MC_Other = (MnvH1D*)CryoRegionMap[region].MnvH1D_Vertex_Y_Other[ind]->Clone("h_MC_Other");
        h_MC_Other->Add(CryoRegionMap[region].MnvH1D_Vertex_Y_Carbon[ind]);
        h_MC_Other->Add(CryoRegionMap[region].MnvH1D_Vertex_Y_Iron[ind]);
        h_MC_Other->Add(CryoRegionMap[region].MnvH1D_Vertex_Y_Lead[ind]);

        Helium_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_MC_Helium));
        Al_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_MC_Al));
        Other_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_MC_Other));

      }

    }

    ////////////////////////////////////////////////////////////////////////////////
    void Helium_3CryoRegionsSideBandTool::fill_CryoRegion14_HistMap_vertex_Z_Material(
      CryoRegion_HeliumNSideBand_Map CryoRegionMap,
      CryoRegion_HistMap &Helium_Map,
      CryoRegion_HistMap &Al_Map,
      CryoRegion_HistMap &Other_Map, int ind){

        for(auto region : CryoRegion14_vector){

          MnvH1D* h_MC_Helium = (MnvH1D*)CryoRegionMap[region].MnvH1D_Vertex_Z_Helium[ind]->Clone("h_MC_Helium");
          MnvH1D* h_MC_Al = (MnvH1D*)CryoRegionMap[region].MnvH1D_Vertex_Z_Aluminium[ind]->Clone("h_MC_Al");
          MnvH1D* h_MC_Other = (MnvH1D*)CryoRegionMap[region].MnvH1D_Vertex_Z_Other[ind]->Clone("h_MC_Other");
          h_MC_Other->Add(CryoRegionMap[region].MnvH1D_Vertex_Z_Carbon[ind]);
          h_MC_Other->Add(CryoRegionMap[region].MnvH1D_Vertex_Z_Iron[ind]);
          h_MC_Other->Add(CryoRegionMap[region].MnvH1D_Vertex_Z_Lead[ind]);

          Helium_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_MC_Helium));
          Al_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_MC_Al));
          Other_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_MC_Other));

        }

      }

      ////////////////////////////////////////////////////////////////////////////////
      void Helium_3CryoRegionsSideBandTool::fill_CryoRegion14_HistMap_vertex_R_Material(
        CryoRegion_HeliumNSideBand_Map CryoRegionMap,
        CryoRegion_HistMap &Helium_Map,
        CryoRegion_HistMap &Al_Map,
        CryoRegion_HistMap &Other_Map, int ind){

          for(auto region : CryoRegion14_vector){

            MnvH1D* h_MC_Helium = (MnvH1D*)CryoRegionMap[region].MnvH1D_Vertex_R_Helium[ind]->Clone("h_MC_Helium");
            MnvH1D* h_MC_Al = (MnvH1D*)CryoRegionMap[region].MnvH1D_Vertex_R_Aluminium[ind]->Clone("h_MC_Al");
            MnvH1D* h_MC_Other = (MnvH1D*)CryoRegionMap[region].MnvH1D_Vertex_R_Other[ind]->Clone("h_MC_Other");
            h_MC_Other->Add(CryoRegionMap[region].MnvH1D_Vertex_R_Carbon[ind]);
            h_MC_Other->Add(CryoRegionMap[region].MnvH1D_Vertex_R_Iron[ind]);
            h_MC_Other->Add(CryoRegionMap[region].MnvH1D_Vertex_R_Lead[ind]);

            Helium_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_MC_Helium));
            Al_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_MC_Al));
            Other_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_MC_Other));

          }

        }
        ////////////////////////////////////////////////////////////////////////////////
        void Helium_3CryoRegionsSideBandTool::fill_CryoRegion14_HistMap_muon_PT_Material(
          CryoRegion_HeliumNSideBand_Map CryoRegionMap,
          CryoRegion_HistMap &Helium_Map,
          CryoRegion_HistMap &Al_Map,
          CryoRegion_HistMap &Other_Map, int ind){

            for(auto region : CryoRegion14_vector){
              MnvH1D* h_MC_Helium = (MnvH1D*)CryoRegionMap[region].muon_PT.MnvH1D_Helium[ind]->Clone("h_MC_Helium");
              MnvH1D* h_MC_Al = (MnvH1D*)CryoRegionMap[region].muon_PT.MnvH1D_Aluminium[ind]->Clone("h_MC_Al");
              MnvH1D* h_MC_Other = (MnvH1D*)CryoRegionMap[region].muon_PT.MnvH1D_Other[ind]->Clone("h_MC_Other");
              h_MC_Other->Add(CryoRegionMap[region].muon_PT.MnvH1D_Carbon[ind]);
              h_MC_Other->Add(CryoRegionMap[region].muon_PT.MnvH1D_Iron[ind]);
              h_MC_Other->Add(CryoRegionMap[region].muon_PT.MnvH1D_Lead[ind]);

              Helium_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_MC_Helium));
              Al_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_MC_Al));
              Other_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_MC_Other));

            }

          }
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void Helium_3CryoRegionsSideBandTool::fill_CryoRegion14_HistMap_muon_PZ_Material(
  CryoRegion_HeliumNSideBand_Map CryoRegionMap,
  CryoRegion_HistMap &Helium_Map,
  CryoRegion_HistMap &Al_Map,
  CryoRegion_HistMap &Other_Map, int ind){

    for(auto region : CryoRegion14_vector){
      MnvH1D* h_MC_Helium = (MnvH1D*)CryoRegionMap[region].muon_PZ.MnvH1D_Helium[ind]->Clone("h_MC_Helium");
      MnvH1D* h_MC_Al = (MnvH1D*)CryoRegionMap[region].muon_PZ.MnvH1D_Aluminium[ind]->Clone("h_MC_Al");
      MnvH1D* h_MC_Other = (MnvH1D*)CryoRegionMap[region].muon_PZ.MnvH1D_Other[ind]->Clone("h_MC_Other");
      h_MC_Other->Add(CryoRegionMap[region].muon_PZ.MnvH1D_Carbon[ind]);
      h_MC_Other->Add(CryoRegionMap[region].muon_PZ.MnvH1D_Iron[ind]);
      h_MC_Other->Add(CryoRegionMap[region].muon_PZ.MnvH1D_Lead[ind]);

      Helium_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_MC_Helium));
      Al_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_MC_Al));
      Other_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_MC_Other));

    }

  }
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void Helium_3CryoRegionsSideBandTool::fill_CryoRegion14_HistMap_muon_theta_Material(
  CryoRegion_HeliumNSideBand_Map CryoRegionMap,
  CryoRegion_HistMap &Helium_Map,
  CryoRegion_HistMap &Al_Map,
  CryoRegion_HistMap &Other_Map, int ind){

    for(auto region : CryoRegion14_vector){
      MnvH1D* h_MC_Helium = (MnvH1D*)CryoRegionMap[region].muon_theta.MnvH1D_Helium[ind]->Clone("h_MC_Helium");
      MnvH1D* h_MC_Al = (MnvH1D*)CryoRegionMap[region].muon_theta.MnvH1D_Aluminium[ind]->Clone("h_MC_Al");
      MnvH1D* h_MC_Other = (MnvH1D*)CryoRegionMap[region].muon_theta.MnvH1D_Other[ind]->Clone("h_MC_Other");
      h_MC_Other->Add(CryoRegionMap[region].muon_theta.MnvH1D_Carbon[ind]);
      h_MC_Other->Add(CryoRegionMap[region].muon_theta.MnvH1D_Iron[ind]);
      h_MC_Other->Add(CryoRegionMap[region].muon_theta.MnvH1D_Lead[ind]);

      Helium_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_MC_Helium));
      Al_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_MC_Al));
      Other_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_MC_Other));

    }

  }
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void Helium_3CryoRegionsSideBandTool::fill_CryoRegion14_HistMap_muon_E_Material(
  CryoRegion_HeliumNSideBand_Map CryoRegionMap,
  CryoRegion_HistMap &Helium_Map,
  CryoRegion_HistMap &Al_Map,
  CryoRegion_HistMap &Other_Map, int ind){

    for(auto region : CryoRegion14_vector){
      MnvH1D* h_MC_Helium = (MnvH1D*)CryoRegionMap[region].muon_E.MnvH1D_Helium[ind]->Clone("h_MC_Helium");
      MnvH1D* h_MC_Al = (MnvH1D*)CryoRegionMap[region].muon_E.MnvH1D_Aluminium[ind]->Clone("h_MC_Al");
      MnvH1D* h_MC_Other = (MnvH1D*)CryoRegionMap[region].muon_E.MnvH1D_Other[ind]->Clone("h_MC_Other");
      h_MC_Other->Add(CryoRegionMap[region].muon_E.MnvH1D_Carbon[ind]);
      h_MC_Other->Add(CryoRegionMap[region].muon_E.MnvH1D_Iron[ind]);
      h_MC_Other->Add(CryoRegionMap[region].muon_E.MnvH1D_Lead[ind]);

      Helium_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_MC_Helium));
      Al_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_MC_Al));
      Other_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_MC_Other));

    }

  }
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void Helium_3CryoRegionsSideBandTool::fill_CryoRegion14_HistMap_muon_doca_Material(
  CryoRegion_HeliumNSideBand_Map CryoRegionMap,
  CryoRegion_HistMap &Helium_Map,
  CryoRegion_HistMap &Al_Map,
  CryoRegion_HistMap &Other_Map, int ind){

    for(auto region : CryoRegion14_vector){
      MnvH1D* h_MC_Helium = (MnvH1D*)CryoRegionMap[region].muon_doca.MnvH1D_Helium[ind]->Clone("h_MC_Helium");
      MnvH1D* h_MC_Al = (MnvH1D*)CryoRegionMap[region].muon_doca.MnvH1D_Aluminium[ind]->Clone("h_MC_Al");
      MnvH1D* h_MC_Other = (MnvH1D*)CryoRegionMap[region].muon_doca.MnvH1D_Other[ind]->Clone("h_MC_Other");
      h_MC_Other->Add(CryoRegionMap[region].muon_doca.MnvH1D_Carbon[ind]);
      h_MC_Other->Add(CryoRegionMap[region].muon_doca.MnvH1D_Iron[ind]);
      h_MC_Other->Add(CryoRegionMap[region].muon_doca.MnvH1D_Lead[ind]);

      Helium_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_MC_Helium));
      Al_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_MC_Al));
      Other_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_MC_Other));

    }

  }
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void Helium_3CryoRegionsSideBandTool::fill_CryoRegion14_HistMap_DistancetoEdge_Material(
  CryoRegion_HeliumNSideBand_Map CryoRegionMap,
  CryoRegion_HistMap &Helium_Map,
  CryoRegion_HistMap &Al_Map,
  CryoRegion_HistMap &Other_Map, int ind){

    for(auto region : CryoRegion14_vector){
      MnvH1D* h_MC_Helium = (MnvH1D*)CryoRegionMap[region].DistancetoEdge.MnvH1D_Helium[ind]->Clone("h_MC_Helium");
      MnvH1D* h_MC_Al = (MnvH1D*)CryoRegionMap[region].DistancetoEdge.MnvH1D_Aluminium[ind]->Clone("h_MC_Al");
      MnvH1D* h_MC_Other = (MnvH1D*)CryoRegionMap[region].DistancetoEdge.MnvH1D_Other[ind]->Clone("h_MC_Other");
      h_MC_Other->Add(CryoRegionMap[region].DistancetoEdge.MnvH1D_Carbon[ind]);
      h_MC_Other->Add(CryoRegionMap[region].DistancetoEdge.MnvH1D_Iron[ind]);
      h_MC_Other->Add(CryoRegionMap[region].DistancetoEdge.MnvH1D_Lead[ind]);

      Helium_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_MC_Helium));
      Al_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_MC_Al));
      Other_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_MC_Other));

    }

  }
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void Helium_3CryoRegionsSideBandTool::fill_CryoRegion14_HistMap_SecTrk_doca_Material(
  CryoRegion_HeliumNSideBand_Map CryoRegionMap,
  CryoRegion_HistMap &Helium_Map,
  CryoRegion_HistMap &Al_Map,
  CryoRegion_HistMap &Other_Map, int ind){

    for(auto region : CryoRegion14_vector){
      MnvH1D* h_MC_Helium = (MnvH1D*)CryoRegionMap[region].SecTrk_doca.MnvH1D_Helium[ind]->Clone("h_MC_Helium");
      MnvH1D* h_MC_Al = (MnvH1D*)CryoRegionMap[region].SecTrk_doca.MnvH1D_Aluminium[ind]->Clone("h_MC_Al");
      MnvH1D* h_MC_Other = (MnvH1D*)CryoRegionMap[region].SecTrk_doca.MnvH1D_Other[ind]->Clone("h_MC_Other");
      h_MC_Other->Add(CryoRegionMap[region].SecTrk_doca.MnvH1D_Carbon[ind]);
      h_MC_Other->Add(CryoRegionMap[region].SecTrk_doca.MnvH1D_Iron[ind]);
      h_MC_Other->Add(CryoRegionMap[region].SecTrk_doca.MnvH1D_Lead[ind]);

      Helium_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_MC_Helium));
      Al_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_MC_Al));
      Other_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_MC_Other));

    }

  }
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void Helium_3CryoRegionsSideBandTool::fill_CryoRegion14_HistMap_TrackLength_Material(
  CryoRegion_HeliumNSideBand_Map CryoRegionMap,
  CryoRegion_HistMap &Helium_Map,
  CryoRegion_HistMap &Al_Map,
  CryoRegion_HistMap &Other_Map, int ind){

    for(auto region : CryoRegion14_vector){
      MnvH1D* h_MC_Helium = (MnvH1D*)CryoRegionMap[region].TrackLength.MnvH1D_Helium[ind]->Clone("h_MC_Helium");
      MnvH1D* h_MC_Al = (MnvH1D*)CryoRegionMap[region].TrackLength.MnvH1D_Aluminium[ind]->Clone("h_MC_Al");
      MnvH1D* h_MC_Other = (MnvH1D*)CryoRegionMap[region].TrackLength.MnvH1D_Other[ind]->Clone("h_MC_Other");
      h_MC_Other->Add(CryoRegionMap[region].TrackLength.MnvH1D_Carbon[ind]);
      h_MC_Other->Add(CryoRegionMap[region].TrackLength.MnvH1D_Iron[ind]);
      h_MC_Other->Add(CryoRegionMap[region].TrackLength.MnvH1D_Lead[ind]);

      Helium_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_MC_Helium));
      Al_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_MC_Al));
      Other_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_MC_Other));

    }

  }
////////////////////////////////////////////////////////////////////////////////
void Helium_3CryoRegionsSideBandTool::fill_CryoRegion14_HistMap_vertex_X_data(CryoRegion_HeliumNSideBand_Map CryoRegionMap, CryoRegion_HistMap &Data_Map){
  for(auto region : CryoRegion14_vector){
    MnvH1D* h_total_data = (MnvH1D*)CryoRegionMap[region].MnvH1D_Vertex_X_data->Clone("h_total_data");
    Data_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_total_data));
  }
}

void Helium_3CryoRegionsSideBandTool::fill_CryoRegion14_HistMap_vertex_Y_data(CryoRegion_HeliumNSideBand_Map CryoRegionMap, CryoRegion_HistMap &Data_Map){
  for(auto region : CryoRegion14_vector){
    MnvH1D* h_total_data = (MnvH1D*)CryoRegionMap[region].MnvH1D_Vertex_Y_data->Clone("h_total_data");
    Data_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_total_data));
  }
}

void Helium_3CryoRegionsSideBandTool::fill_CryoRegion14_HistMap_vertex_Z_data(CryoRegion_HeliumNSideBand_Map CryoRegionMap, CryoRegion_HistMap &Data_Map){
  for(auto region : CryoRegion14_vector){
    MnvH1D* h_total_data = (MnvH1D*)CryoRegionMap[region].MnvH1D_Vertex_Z_data->Clone("h_total_data");
    Data_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_total_data));
  }
}

void Helium_3CryoRegionsSideBandTool::fill_CryoRegion14_HistMap_vertex_R_data(CryoRegion_HeliumNSideBand_Map CryoRegionMap, CryoRegion_HistMap &Data_Map){
  for(auto region : CryoRegion14_vector){
    MnvH1D* h_total_data = (MnvH1D*)CryoRegionMap[region].MnvH1D_Vertex_R_data->Clone("h_total_data");
    Data_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_total_data));
  }
}


void Helium_3CryoRegionsSideBandTool::fill_CryoRegion14_HistMap_muon_PT_data(CryoRegion_HeliumNSideBand_Map CryoRegionMap, CryoRegion_HistMap &Data_Map){
  for(auto region : CryoRegion14_vector){
    MnvH1D* h_total_data = (MnvH1D*)CryoRegionMap[region].muon_PT.MnvH1D_data->Clone("h_total_data");
    Data_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_total_data));
  }
}

void Helium_3CryoRegionsSideBandTool::fill_CryoRegion14_HistMap_muon_PZ_data(CryoRegion_HeliumNSideBand_Map CryoRegionMap, CryoRegion_HistMap &Data_Map){
  for(auto region : CryoRegion14_vector){
    MnvH1D* h_total_data = (MnvH1D*)CryoRegionMap[region].muon_PZ.MnvH1D_data->Clone("h_total_data");
    Data_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_total_data));
  }
}

void Helium_3CryoRegionsSideBandTool::fill_CryoRegion14_HistMap_muon_theta_data(CryoRegion_HeliumNSideBand_Map CryoRegionMap, CryoRegion_HistMap &Data_Map){
  for(auto region : CryoRegion14_vector){
    MnvH1D* h_total_data = (MnvH1D*)CryoRegionMap[region].muon_theta.MnvH1D_data->Clone("h_total_data");
    Data_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_total_data));
  }
}

void Helium_3CryoRegionsSideBandTool::fill_CryoRegion14_HistMap_muon_E_data(CryoRegion_HeliumNSideBand_Map CryoRegionMap, CryoRegion_HistMap &Data_Map){
  for(auto region : CryoRegion14_vector){
    MnvH1D* h_total_data = (MnvH1D*)CryoRegionMap[region].muon_E.MnvH1D_data->Clone("h_total_data");
    Data_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_total_data));
  }
}

void Helium_3CryoRegionsSideBandTool::fill_CryoRegion14_HistMap_muon_doca_data(CryoRegion_HeliumNSideBand_Map CryoRegionMap, CryoRegion_HistMap &Data_Map){
  for(auto region : CryoRegion14_vector){
    MnvH1D* h_total_data = (MnvH1D*)CryoRegionMap[region].muon_doca.MnvH1D_data->Clone("h_total_data");
    Data_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_total_data));
  }
}

void Helium_3CryoRegionsSideBandTool::fill_CryoRegion14_HistMap_DistancetoEdge_data(CryoRegion_HeliumNSideBand_Map CryoRegionMap, CryoRegion_HistMap &Data_Map){
  for(auto region : CryoRegion14_vector){
    MnvH1D* h_total_data = (MnvH1D*)CryoRegionMap[region].DistancetoEdge.MnvH1D_data->Clone("h_total_data");
    Data_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_total_data));
  }
}
void Helium_3CryoRegionsSideBandTool::fill_CryoRegion14_HistMap_SecTrk_doca_data(CryoRegion_HeliumNSideBand_Map CryoRegionMap, CryoRegion_HistMap &Data_Map){
  for(auto region : CryoRegion14_vector){
    MnvH1D* h_total_data = (MnvH1D*)CryoRegionMap[region].SecTrk_doca.MnvH1D_data->Clone("h_total_data");
    Data_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_total_data));
  }
}
void Helium_3CryoRegionsSideBandTool::fill_CryoRegion14_HistMap_TrackLength_doca_data(CryoRegion_HeliumNSideBand_Map CryoRegionMap, CryoRegion_HistMap &Data_Map){
  for(auto region : CryoRegion14_vector){
    MnvH1D* h_total_data = (MnvH1D*)CryoRegionMap[region].TrackLength.MnvH1D_data->Clone("h_total_data");
    Data_Map.insert(std::pair<CryoTank_REGIONS, PlotUtils::MnvH1D*>(region,h_total_data));
  }
}







void Helium_3CryoRegionsSideBandTool::Plot_regions_Region14(
  std::string pdf_label,
  CryoRegion_HistMap Data_Map,
  CryoRegion_HistMap Helium_Map,
  CryoRegion_HistMap Al_Map,
  CryoRegion_HistMap Other_Map,
  std::string Hist_title, std::string xaxislabel, double &ChiSqrt,
  double &ChiSqrtAfter, int FitType, bool UseLogChi, bool doAreaNormalized, bool applyMaxY , double MaxY, int index){
    std::string type;

    MnvPlotter* plotter = new MnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);

    TH1D* h_total_data = (TH1D*)Data_Map[CryoRegion14_vector.at(0)]->Clone("h_total_data");

    TH1D* h_total_MC_helium = (TH1D*)Helium_Map[CryoRegion14_vector.at(0)]->Clone("h_total_MC_helium");
    TH1D* h_total_MC_Other = (TH1D*)Other_Map[CryoRegion14_vector.at(0)]->Clone("h_total_MC_Other");

    TH1D* h_total_MC = (TH1D*)Other_Map[CryoRegion14_vector.at(0)]->Clone("h_total_MC");
    h_total_MC->Add(h_total_MC_helium);


    TH1D* h_Al_region1 = (TH1D*)Al_Map[CryoRegion14_vector.at(0)]->Clone("h_Al_region1");
    TH1D* h_Al_region2 = (TH1D*)Al_Map[CryoRegion14_vector.at(1)]->Clone("h_Al_region2");
    TH1D* h_Al_region3 = (TH1D*)Al_Map[CryoRegion14_vector.at(2)]->Clone("h_Al_region3");
    TH1D* h_Al_region4 = (TH1D*)Al_Map[CryoRegion14_vector.at(3)]->Clone("h_Al_region4");
    TH1D* h_Al_region5 = (TH1D*)Al_Map[CryoRegion14_vector.at(4)]->Clone("h_Al_region5");
    TH1D* h_Al_region6 = (TH1D*)Al_Map[CryoRegion14_vector.at(5)]->Clone("h_Al_region6");
    TH1D* h_Al_region7 = (TH1D*)Al_Map[CryoRegion14_vector.at(6)]->Clone("h_Al_region7");
    TH1D* h_Al_region8 = (TH1D*)Al_Map[CryoRegion14_vector.at(7)]->Clone("h_Al_region8");
    TH1D* h_Al_region9 = (TH1D*)Al_Map[CryoRegion14_vector.at(8)]->Clone("h_Al_region9");
    TH1D* h_Al_region10 =(TH1D*)Al_Map[CryoRegion14_vector.at(9)]->Clone("h_Al_region10");
    TH1D* h_Al_region11 =(TH1D*)Al_Map[CryoRegion14_vector.at(10)]->Clone("h_Al_region11");
    TH1D* h_Al_region12 =(TH1D*)Al_Map[CryoRegion14_vector.at(11)]->Clone("h_Al_region12");
    TH1D* h_Al_region13 =(TH1D*)Al_Map[CryoRegion14_vector.at(12)]->Clone("h_Al_region13");
    TH1D* h_Al_region14 =(TH1D*)Al_Map[CryoRegion14_vector.at(13)]->Clone("h_Al_region14");

    h_total_MC->Add(h_Al_region1);

    int nPoints = h_total_data->GetNbinsX()-1;

    std::vector<TH1D*> Al_region_vector{
      h_Al_region1,
      h_Al_region2,
      h_Al_region3,
      h_Al_region4,
      h_Al_region5,
      h_Al_region6,
      h_Al_region7,
      h_Al_region8,
      h_Al_region9,
      h_Al_region10,
      h_Al_region11,
      h_Al_region12,
      h_Al_region13,
      h_Al_region14
    };



    for(auto Region: CryoRegion14_vector ){

      if(Region==CryoRegion14_vector.at(0)) continue;
      h_total_data->Add(Data_Map[Region]);

      h_total_MC_helium->Add(Helium_Map[Region]);
      h_total_MC_Other->Add(Other_Map[Region]);

      h_total_MC->Add(Helium_Map[Region]);
      h_total_MC->Add(Other_Map[Region]);
      h_total_MC->Add(Al_Map[Region]);
    }

    h_total_data->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
    h_total_MC->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));

    ColorData(h_total_data);

    h_total_MC_helium->SetFillColor(kRed);
    h_total_MC_helium->SetFillStyle(1001);
    h_total_MC_Other->SetFillColor(kBlue);
    h_total_MC_Other->SetFillStyle(1001);
    int color = 0;

    for(auto Hist_AL:Al_region_vector ){
      Hist_AL->SetFillColor(Helium16_distinct.at(color));
      Hist_AL->SetFillStyle(1001);
      color++;
    }

    double plot_chisq =999;
        std::cout<<"About to cal calc_ChiSq for  : " << xaxislabel << std::endl;
    if(UseLogChi == false){
      plot_chisq = calc_ChiSq(Data_Map, Helium_Map, Al_Map, Other_Map);}
    else if(UseLogChi == true){plot_chisq = calc_ChiSq_Log(Data_Map, Helium_Map, Al_Map, Other_Map);}



    /*if(doAreaNormalized == true){

            if(h_mc_total->GetNbinsX() !=h_data_Combined->GetNbinsX()){std::cout<<"~~~ Whoah Data and MC have different number of Bins HistTitle : "<< Hist_title<<std::endl; assert(false); }
            double MCArea = h_mc_total->Integral(1,h_mc_total->GetNbinsX());
            double DataArea = h_data_Combined->Integral(1,h_data_Combined->GetNbinsX());
            double areascaler = DataArea / MCArea;

            h_mc_total->Scale(areascaler);
            //h_TOTAL->Scale(areascaler);
            h_Helium_region1->Scale(areascaler);
            h_Aluminium_region1->Scale(areascaler);

            h_Helium_region2->Scale(areascaler);
            h_Aluminium_region2->Scale(areascaler);

            h_Helium_region3->Scale(areascaler);
            h_Aluminium_region3->Scale(areascaler);

            h_Helium_region4->Scale(areascaler);
            h_Aluminium_region4->Scale(areascaler);

            //h_Carbon_Combined->Scale(areascaler);
            //h_Iron_Combined->Scale(areascaler);
            //h_Lead_Combined->Scale(areascaler);
            h_Other_Combined->Scale(areascaler);

          }*/
    //////////////////////////////////////
    //// Combining All Other
    //////////////////////////////////////
    MnvH1D *mvn_total_data = (PlotUtils::MnvH1D*)h_total_data->Clone("mvn_total_data");
    MnvH1D *mvn_total_mc = (PlotUtils::MnvH1D*)h_total_MC->Clone("mvn_total_mc");


    std::string yaxis;
    if(MakeBinWidth==true){

      h_total_data->Scale(1.0, "width");
      h_total_MC_helium->Scale(1.0, "width");
      h_total_MC_Other->Scale(1.0, "width");
      h_total_MC->Scale(1.0, "width");

      for(auto Hist_AL:Al_region_vector ){
        Hist_AL->Scale(1.0, "width");
      }

      double binwidth_title = h_total_MC -> GetBinWidth(3);
      yaxis = Form("NEvents / %.2f",binwidth_title);
      if(doAreaNormalized == true){yaxis = Form("[DataAreaNorm] NEvents / %.2f",binwidth_title);}
      //std::cout<< "yaxis = "<< yaxis<<std::endl;
      //std::cout<<"Finished Bin width Norm"<<std::endl;
    }
    else{
      yaxis = "NEvents";
      //  std::cout<<"FInished Bin NOT width Norm"<<std::endl;
    }

    // ------------------------------------------------------------------------
    // Unique Plot for Single Error Band, Single Universe
    //      Comment this section out
    // ------------------------------------------------------------------------


    // Create Canvas and Divide it into two
    TCanvas* c = new TCanvas("c","c",800, 800);
    TLegend *legend = new TLegend(0.85,0.35,0.95,0.93);
    //TCanvas cE("cE","cE", 800, 800);
    // Upper Pad is the Data vs MC
    TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
    pad1->SetBottomMargin(0); // Top and Bottom Plots attached
    pad1->Draw();
    pad1->cd(); // pad1 is the current pad
    // Plot MC Models as THStack


    THStack* hs = new THStack("hs","");
    h_total_MC_helium->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
    legend->AddEntry(h_total_data, "Data");
    legend->AddEntry(h_total_MC, "Total MC", "l");
    hs->Add(h_total_MC_helium);legend->AddEntry(h_total_MC_helium,    "^{4}He",         "f");
    hs->Add(h_total_MC_Other);legend->AddEntry(h_total_MC_Other,    "Other",         "f");
    hs->Add(h_Al_region1);    legend->AddEntry(h_Al_region1,    "^{27}Al  1",         "f");
    hs->Add(h_Al_region2);    legend->AddEntry(h_Al_region2,    "^{27}Al  2",         "f");
    hs->Add(h_Al_region3);    legend->AddEntry(h_Al_region3,    "^{27}Al  3",         "f");
    hs->Add(h_Al_region4);    legend->AddEntry(h_Al_region4,    "^{27}Al  4",         "f");
    hs->Add(h_Al_region5);    legend->AddEntry(h_Al_region5,    "^{27}Al  5",         "f");
    hs->Add(h_Al_region6);    legend->AddEntry(h_Al_region6,    "^{27}Al  6",         "f");
    hs->Add(h_Al_region7);    legend->AddEntry(h_Al_region7,    "^{27}Al  7",         "f");
    hs->Add(h_Al_region8);    legend->AddEntry(h_Al_region8,    "^{27}Al  8",         "f");
    hs->Add(h_Al_region9);    legend->AddEntry(h_Al_region9,    "^{27}Al  9",         "f");
    hs->Add(h_Al_region10);   legend->AddEntry(h_Al_region10,    "^{27}Al 10",         "f");
    hs->Add(h_Al_region11);   legend->AddEntry(h_Al_region11,    "^{27}Al 11",         "f");
    hs->Add(h_Al_region12);   legend->AddEntry(h_Al_region12,    "^{27}Al 12",         "f");
    hs->Add(h_Al_region13);   legend->AddEntry(h_Al_region13,    "^{27}Al 13",         "f");
    hs->Add(h_Al_region14);   legend->AddEntry(h_Al_region14,    "^{27}Al 14",         "f");

    //std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
    //std::cout<<"~~~~~~~~~~~~~~~~~~~Checking ~~~~~~~~~~~~~~~~~~~"<<std::endl;
    //std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
    // Styling
    hs->Draw("HIST");
    hs->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
    hs->GetYaxis()->SetTitle(Form("%s",yaxis.c_str()));
    hs->GetYaxis()->SetTitleFont(62);
    hs->GetYaxis()->SetTitleSize(0.06);
    hs->GetXaxis()->SetTitleSize(0.06);
    hs->GetXaxis()->CenterTitle();
    //hs->GetYaxis()->SetTitleOffset(1.2);
    hs->GetYaxis()->SetLabelFont(42);
    hs->GetYaxis()->SetLabelSize(0.05);

    if(applyMaxY==false){
      if(h_total_MC->GetMaximum() > h_total_data->GetMaximum()  ){
        hs->SetMaximum(h_total_MC->GetMaximum() * 1.45);
      }
      else { hs->SetMaximum(h_total_data->GetMaximum() * 1.45);}
    }
    else if (applyMaxY==true){
      hs->SetMaximum(MaxY);
    }

    hs->SetMinimum(-1);
    h_total_MC->SetMarkerStyle(0);
    h_total_MC->SetLineWidth(2);
    h_total_MC->SetLineColor(kBlack);
    h_total_MC->SetFillStyle(0);
    h_total_MC->Draw("same Hist");
    h_total_data->Draw("SAME E1 X0");
    // Add Legend

    //  int nPoints = h_total_data->GetNbinsX()-1;

    //std::cout<<"nPoints = "<<nPoints<< std::endl;

    // Add Plot-ChiSq
    TLatex* text = new TLatex;
    text->SetNDC();
    text->SetTextSize(0.03);
    text->SetTextColor(kBlue);
    text->DrawLatex(0.2, 0.85, Form("Plot #chi^{2} = %3.2f", plot_chisq));
    text->DrawLatex(0.2, 0.82, Form("Plot #chi^{2}/dof = %3.2f", plot_chisq / (double) nPoints));


    legend->SetTextSize(0.025);
    legend->SetTextFont(42);
    legend->Draw();
    text->SetTextSize(0.02);
    text->SetTextColor(kBlack);

    if (FitType == 0){ChiSq_before_fit_var.push_back(plot_chisq);
      ChiSqrt = plot_chisq;
    }

    if (FitType == 1 ){
      ChiSqrtAfter = plot_chisq;
        int nPars = 14;
        std::cout<<"making Fit info" <<  std::endl;
        //std::cout<<"ChiSq_before_fit[0] = "<< ChiSq_before_fit[0]<<std::endl;
          std::cout<<"ChiSq_after_fit[0] = "<< plot_chisq<<std::endl;
        TLatex* text = new TLatex;
        text->SetTextSize(0.012);
        text->SetNDC();
        double xplace = .70; double yplace = 0.88;
        text->DrawLatex(xplace, yplace, Form("Fit Results with %d points, %d pars", nPoints, nPars));
        yplace-=.015;
        text->DrawLatex(xplace, yplace, Form("Before Fit #chi^{2} = %3.2f",     ChiSq_before_fit_var.at(index)));
        yplace-=.015;
        text->DrawLatex(xplace, yplace, Form("Before Fit #chi^{2}/dof = %3.2f", ChiSq_before_fit_var.at(index)/(nPoints-nPars)));
        yplace-=.015;
        text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2} = %3.2f", plot_chisq));
        yplace-=.015;
        text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2}/dof = %3.2f", plot_chisq/(double)(nPoints-nPars)));
        yplace-=.015;
        text->DrawLatex(xplace, yplace, Form("#color[4]{Region1(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[0], err_Aluminium[0]));
        yplace-=.015;
        text->DrawLatex(xplace, yplace, Form("#color[4]{Region2(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[1], err_Aluminium[1]));
        yplace-=.015;
        text->DrawLatex(xplace, yplace, Form("#color[4]{Region3(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[2], err_Aluminium[2]));
        yplace-=.015;
        text->DrawLatex(xplace, yplace, Form("#color[4]{Region4(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[3], err_Aluminium[3]));
        yplace-=.015;
        text->DrawLatex(xplace, yplace, Form("#color[4]{Region5(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[4], err_Aluminium[4]));
        yplace-=.015;
        text->DrawLatex(xplace, yplace, Form("#color[4]{Region6(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[5], err_Aluminium[5]));
        yplace-=.015;
        text->DrawLatex(xplace, yplace, Form("#color[4]{Region7(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[6], err_Aluminium[6]));
        yplace-=.015;
        text->DrawLatex(xplace, yplace, Form("#color[4]{Region8(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[7], err_Aluminium[7]));
        yplace-=.015;
        text->DrawLatex(xplace, yplace, Form("#color[4]{Region9(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[8], err_Aluminium[8]));
        yplace-=.015;
        text->DrawLatex(xplace, yplace, Form("#color[4]{Region10(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[9], err_Aluminium[9]));
        yplace-=.015;
        text->DrawLatex(xplace, yplace, Form("#color[4]{Region11(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[10], err_Aluminium[10]));
        yplace-=.015;
        text->DrawLatex(xplace, yplace, Form("#color[4]{Region12(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[11], err_Aluminium[11]));
        yplace-=.015;
        text->DrawLatex(xplace, yplace, Form("#color[4]{Region13(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[12], err_Aluminium[12]));
        yplace-=.015;
        text->DrawLatex(xplace, yplace, Form("#color[4]{Region14(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[13], err_Aluminium[13]));

      //  delete text;
    }


        plotter->AddHistoTitle(Hist_title.c_str(),.04);
        plotter->WritePreliminary("TL", .025, 0, 0, false);
        // Plot Lower Plot: Data vs MC Ratio
        c->cd(); // Go back to default Canvas before creating 2nd Pad
        //TPad *pad2 = new TPad("pad2", "pad2", 0.05, 0.05, 1, 0.3);

        //pad2->SetTopMargin(0);
        //pad2->SetBottomMargin(0.2);
        c->Modified();
        TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
        pad2->SetTopMargin(0);
        pad2->SetBottomMargin(0.2);
        pad2->SetGridx(); // vertical grid
        pad2->Draw();
        pad2->cd();

        plotter->axis_title_size_x = 0.1;
        plotter->axis_title_offset_y = .4;
        plotter->axis_title_offset_x = 1.35;
        plotter->axis_title_size_y = 0.12;
        plotter->axis_label_size = 0.1;
        plotter->axis_maximum = 2.5;
        plotter->axis_minimum = .5;


        int ndf;
        Double_t chi_2 = plotter->Chi2DataMC(mvn_total_data,mvn_total_mc,ndf,1.0,false,false );
          std::cout<<"Divide for : " << xaxislabel << std::endl;
          std::cout<<"chi_2 : " << chi_2 << std::endl;
          std::cout<<"plot_chisq(local) " << plot_chisq << std::endl;
        plotter->DrawDataMCRatio(mvn_total_data, mvn_total_mc, 1.0, false, false , -.5, 2, "#frac{Data}{MC}", false);

        c->Update();
        c->cd();
        pad1->cd();

        text->DrawLatex(0.2, 0.80, Form("Plot Chi2DataMC #chi^{2} = %3.2f", chi_2));
        text->DrawLatex(0.2, 0.78, Form("Plot Chi2DataMC #chi^{2}/dof = %3.2f", chi_2 / (double) ndf));
        delete text;
        c->cd();
        c->Print(pdf_label.c_str(),"pdf");
        delete plotter;
        delete legend;
        delete hs;
        delete pad1;
        delete pad2;
        delete c;
      }
/////////////////////////////////////////////////////////////////////////
void Helium_3CryoRegionsSideBandTool::Plot_Fit_vars_Region14(std::string Hist_title,
  bool doAreaNormalized,bool UseLogChi, CryoRegion_HeliumNSideBand_Map CryoRegionMap,
   bool doBinWidthNorm , std::string pdf_label , int ind, int fittype){


CryoRegion_HistMap Data_Map_X;   CryoRegion_HistMap Data_Map_Y;   CryoRegion_HistMap Data_Map_Z;   CryoRegion_HistMap Data_Map_R;
CryoRegion_HistMap Helium_Map_X; CryoRegion_HistMap Helium_Map_Y; CryoRegion_HistMap Helium_Map_Z; CryoRegion_HistMap Helium_Map_R;
CryoRegion_HistMap Al_Map_X;     CryoRegion_HistMap Al_Map_Y;     CryoRegion_HistMap Al_Map_Z;     CryoRegion_HistMap Al_Map_R;
CryoRegion_HistMap Other_Map_X;  CryoRegion_HistMap Other_Map_Y;  CryoRegion_HistMap Other_Map_Z;  CryoRegion_HistMap Other_Map_R;

  fill_CryoRegion14_HistMap_vertex_X_data(CryoRegionMap, Data_Map_X);
  fill_CryoRegion14_HistMap_vertex_Y_data(CryoRegionMap, Data_Map_Y);
  fill_CryoRegion14_HistMap_vertex_Z_data(CryoRegionMap, Data_Map_Z);
  fill_CryoRegion14_HistMap_vertex_R_data(CryoRegionMap, Data_Map_R);

  fill_CryoRegion14_HistMap_vertex_X_Material(CryoRegionMap, Helium_Map_X, Al_Map_X, Other_Map_X,  ind);
  fill_CryoRegion14_HistMap_vertex_Y_Material(CryoRegionMap, Helium_Map_Y, Al_Map_Y, Other_Map_Y,  ind);
  fill_CryoRegion14_HistMap_vertex_Z_Material(CryoRegionMap, Helium_Map_Z, Al_Map_Z, Other_Map_Z,  ind);
  fill_CryoRegion14_HistMap_vertex_R_Material(CryoRegionMap, Helium_Map_R, Al_Map_R, Other_Map_R,  ind);

  double ChiSqrt = 999;
  double ChiSqrtAfter = 999;


  Plot_regions_Region14(
  pdf_label, Data_Map_X, Helium_Map_X, Al_Map_X, Other_Map_X,  Hist_title, "Vertex X [mm]",
  ChiSqrt, ChiSqrtAfter, fittype, UseLogChi, doAreaNormalized, false , 99, 0);

  Plot_regions_Region14(
  pdf_label, Data_Map_Y,Helium_Map_Y, Al_Map_Y, Other_Map_Y,  Hist_title, "Vertex Y [mm]",
  ChiSqrt, ChiSqrtAfter, fittype, UseLogChi, doAreaNormalized, false , 99, 1);

  Plot_regions_Region14(
  pdf_label, Data_Map_Z, Helium_Map_Z, Al_Map_Z, Other_Map_Z,  Hist_title, "Vertex Z [mm]",
  ChiSqrt, ChiSqrtAfter, fittype, UseLogChi, doAreaNormalized, false , 99, 2);

  Plot_regions_Region14(
  pdf_label, Data_Map_R, Helium_Map_R, Al_Map_R, Other_Map_R,  Hist_title, "Vertex R [mm]",
  ChiSqrt, ChiSqrtAfter, fittype, UseLogChi, doAreaNormalized, false , 99, 3);

}

/////////////////////////////////////////////////////////////////////////

void Helium_3CryoRegionsSideBandTool::Plot_Fit_vars_Region14_Vars(std::string Hist_title,
  bool doAreaNormalized,bool UseLogChi, CryoRegion_HeliumNSideBand_Map CryoRegionMap,
   bool doBinWidthNorm , std::string pdf_label , int ind, int fittype){

     CryoRegion_HistMap Data_muon_PT; CryoRegion_HistMap        Helium_muon_PT;        CryoRegion_HistMap Al_muon_PT;        CryoRegion_HistMap Other_muon_PT;
     CryoRegion_HistMap Data_muon_PZ; CryoRegion_HistMap        Helium_muon_PZ;        CryoRegion_HistMap Al_muon_PZ;        CryoRegion_HistMap Other_muon_PZ;
     CryoRegion_HistMap Data_muon_theta; CryoRegion_HistMap     Helium_muon_theta;     CryoRegion_HistMap Al_muon_theta;     CryoRegion_HistMap Other_muon_theta;
     CryoRegion_HistMap Data_muon_E; CryoRegion_HistMap         Helium_muon_E;         CryoRegion_HistMap Al_muon_E;         CryoRegion_HistMap Other_muon_E;
     CryoRegion_HistMap Data_muon_doca; CryoRegion_HistMap      Helium_muon_doca;      CryoRegion_HistMap Al_muon_doca;      CryoRegion_HistMap Other_muon_doca;
     CryoRegion_HistMap Data_DistancetoEdge; CryoRegion_HistMap Helium_DistancetoEdge; CryoRegion_HistMap Al_DistancetoEdge; CryoRegion_HistMap Other_DistancetoEdge;
     CryoRegion_HistMap Data_SecTrk_doca; CryoRegion_HistMap    Helium_SecTrk_doca;    CryoRegion_HistMap Al_SecTrk_doca;    CryoRegion_HistMap Other_SecTrk_doca;
     CryoRegion_HistMap Data_TrackLength; CryoRegion_HistMap    Helium_TrackLength;    CryoRegion_HistMap Al_TrackLength;    CryoRegion_HistMap Other_TrackLength;

  fill_CryoRegion14_HistMap_muon_PT_data(CryoRegionMap,          Data_muon_PT);
  fill_CryoRegion14_HistMap_muon_PZ_data(CryoRegionMap,         Data_muon_PZ );
  fill_CryoRegion14_HistMap_muon_theta_data(CryoRegionMap,      Data_muon_theta );
  fill_CryoRegion14_HistMap_muon_E_data(CryoRegionMap,          Data_muon_E );
  fill_CryoRegion14_HistMap_muon_doca_data(CryoRegionMap,       Data_muon_doca );
  fill_CryoRegion14_HistMap_DistancetoEdge_data(CryoRegionMap,  Data_DistancetoEdge );
  fill_CryoRegion14_HistMap_SecTrk_doca_data(CryoRegionMap,     Data_SecTrk_doca );
  fill_CryoRegion14_HistMap_TrackLength_doca_data(CryoRegionMap,Data_TrackLength );

  fill_CryoRegion14_HistMap_muon_PT_Material(       CryoRegionMap, Helium_muon_PT,        Al_muon_PT,       Other_muon_PT,         ind);
  fill_CryoRegion14_HistMap_muon_PZ_Material(       CryoRegionMap, Helium_muon_PZ,        Al_muon_PZ,       Other_muon_PZ,         ind);
  fill_CryoRegion14_HistMap_muon_theta_Material(    CryoRegionMap, Helium_muon_theta,     Al_muon_theta,    Other_muon_theta,      ind);
  fill_CryoRegion14_HistMap_muon_E_Material(        CryoRegionMap, Helium_muon_E,         Al_muon_E,        Other_muon_E,          ind);
  fill_CryoRegion14_HistMap_muon_doca_Material(     CryoRegionMap, Helium_muon_doca,      Al_muon_doca,     Other_muon_doca,       ind);
  fill_CryoRegion14_HistMap_DistancetoEdge_Material(CryoRegionMap, Helium_DistancetoEdge, Al_DistancetoEdge, Other_DistancetoEdge,  ind);
  fill_CryoRegion14_HistMap_SecTrk_doca_Material(   CryoRegionMap, Helium_SecTrk_doca,    Al_SecTrk_doca,   Other_SecTrk_doca,     ind);
  fill_CryoRegion14_HistMap_TrackLength_Material(   CryoRegionMap, Helium_TrackLength,    Al_TrackLength,   Other_TrackLength,     ind);

  double ChiSqrt = 999;
  double ChiSqrtAfter = 999;

  Plot_regions_Region14(
  pdf_label, Data_muon_PT, Helium_muon_PT, Al_muon_PT, Other_muon_PT,  Hist_title, "P_{T} [GeV]",
  ChiSqrt, ChiSqrtAfter, fittype, UseLogChi, doAreaNormalized, false , 99, 4);

  Plot_regions_Region14(
  pdf_label, Data_muon_PZ, Helium_muon_PZ, Al_muon_PZ, Other_muon_PZ,  Hist_title, "P_{Z} [GeV]",
  ChiSqrt, ChiSqrtAfter, fittype, UseLogChi, doAreaNormalized, false , 99, 5);

  Plot_regions_Region14(
  pdf_label, Data_muon_theta, Helium_muon_theta, Al_muon_theta, Other_muon_theta,  Hist_title, "#theta_{#mu}[Deg]",
  ChiSqrt, ChiSqrtAfter, fittype, UseLogChi, doAreaNormalized, false , 99, 6);

  Plot_regions_Region14(
  pdf_label, Data_muon_E, Helium_muon_E, Al_muon_E, Other_muon_E,  Hist_title, "T_{#mu} [GeV]",
  ChiSqrt, ChiSqrtAfter, fittype, UseLogChi, doAreaNormalized, false , 99, 7);

  Plot_regions_Region14(
    pdf_label, Data_muon_doca, Helium_muon_doca, Al_muon_doca, Other_muon_doca,  Hist_title, "DOCA_{#mu}[mm]",
    ChiSqrt, ChiSqrtAfter, fittype, UseLogChi, doAreaNormalized, false , 99, 8);

  Plot_regions_Region14(
    pdf_label, Data_DistancetoEdge, Helium_DistancetoEdge, Al_DistancetoEdge, Other_DistancetoEdge,  Hist_title, "Vertex Distance to Nearest Wall[mm]",
    ChiSqrt, ChiSqrtAfter, fittype, UseLogChi, doAreaNormalized, false , 99, 9);

Plot_regions_Region14(
      pdf_label, Data_SecTrk_doca, Helium_SecTrk_doca, Al_SecTrk_doca, Other_SecTrk_doca,  Hist_title, "DOCA_{Recoil}[mm]",
      ChiSqrt, ChiSqrtAfter, fittype, UseLogChi, doAreaNormalized, false , 99, 10);

Plot_regions_Region14(
        pdf_label, Data_TrackLength, Helium_TrackLength, Al_TrackLength, Other_TrackLength,  Hist_title, "Recoil TrackLength [mm]",
        ChiSqrt, ChiSqrtAfter, fittype, UseLogChi, doAreaNormalized, false , 99, 11);


}




void Helium_3CryoRegionsSideBandTool::Plot_init_FitVar_Region14_Empty(){

bool MakeAreaNorm = false;
Plot_Fit_vars_Region14(" Intial Plots 14 Regions [RECO Bins]",MakeAreaNorm,false, CryoRegionMap_Empty,MakeBinWidth , PDF_printingLabel_input , 0, 0);
Plot_Fit_vars_Region14(" Intial Plots 14 Regions [TRUE Bins]",MakeAreaNorm,false, CryoRegionMap_Empty,MakeBinWidth , PDF_printingLabel_input , 1, 0);
Plot_Fit_vars_Region14_Vars(" Intial Plots 14 Regions", MakeAreaNorm,false,       CryoRegionMap_Empty, MakeBinWidth , PDF_printingLabel_input , 0, 0);

}


void Helium_3CryoRegionsSideBandTool::Plot_after_FitVar_Region14_Empty(){

bool MakeAreaNorm = false;
Plot_Fit_vars_Region14(" Intial Plots 14 Regions [RECO Bins]",MakeAreaNorm,false, CryoRegionMap_Empty,MakeBinWidth , PDF_printingLabel_input , 2, 1);
Plot_Fit_vars_Region14_Vars(" Intial Plots 14 Regions", MakeAreaNorm,false,       CryoRegionMap_Empty, MakeBinWidth , PDF_printingLabel_input , 1, 1);

}



//////////////////////////////////////////////////////////////////////////
      void Helium_3CryoRegionsSideBandTool::Plot_regions_addlinerFittoRatio(std::string pdf_label, int ind, double POT_ratio,
             MnvH1D* data_region1, MnvH1D* mc_total_region1, MnvH1D* Helium_region1, MnvH1D* Aluminium_region1, MnvH1D* Carbon_region1,
             MnvH1D* Iron_region1, MnvH1D* Lead_region1, MnvH1D* Other_region1,

             MnvH1D* data_region2, MnvH1D* mc_total_region2, MnvH1D* Helium_region2, MnvH1D* Aluminium_region2, MnvH1D* Carbon_region2,
             MnvH1D* Iron_region2, MnvH1D* Lead_region2, MnvH1D* Other_region2,

             MnvH1D* data_region3, MnvH1D* mc_total_region3, MnvH1D* Helium_region3, MnvH1D* Aluminium_region3, MnvH1D* Carbon_region3,
             MnvH1D* Iron_region3, MnvH1D* Lead_region3, MnvH1D* Other_region3,

             MnvH1D* data_region4, MnvH1D* mc_total_region4, MnvH1D* Helium_region4, MnvH1D* Aluminium_region4, MnvH1D* Carbon_region4,
             MnvH1D* Iron_region4, MnvH1D* Lead_region4, MnvH1D* Other_region4,

             std::string Hist_title, std::string xaxislabel, double &ChiSqrt,
             double &ChiSqrtAfter, int FitType, bool UseLogChi, bool doAreaNormalized, bool applyMaxY , double MaxY)
             {

              std::string type;
              if (ind == 0) type = "Nominal";
              else type = "Fitted";
              //std::cout<<"Ploting type: Combined CryoRegions  "<< type<<std::endl;

              //PlotUtils::MnvPlotter* plotter= new mnvPlotter();
               MnvPlotter* plotter = new MnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
              //plotter(PlotUtils::kCCInclusiveHeliumStyle);
              MnvH1D *data = (PlotUtils::MnvH1D*)data_region1->Clone("data");

              data->Add(data_region2);
              data->Add(data_region3);
              data->Add(data_region4);

              MnvH1D *mc_total = (PlotUtils::MnvH1D*)Helium_region1->Clone("mc_total");

              mc_total->Add(Aluminium_region1 );
              mc_total->Add(Carbon_region1);
              mc_total->Add(Iron_region1 );
              mc_total->Add(Lead_region1 );
              mc_total->Add(Other_region1);

              mc_total->Add(Helium_region2 );
              mc_total->Add(Aluminium_region2 );
              mc_total->Add(Carbon_region2);
              mc_total->Add(Iron_region2 );
              mc_total->Add(Lead_region2 );
              mc_total->Add(Other_region2);

              mc_total->Add(Helium_region3 );
              mc_total->Add(Aluminium_region3 );
              mc_total->Add(Carbon_region3);
              mc_total->Add(Iron_region3 );
              mc_total->Add(Lead_region3 );
              mc_total->Add(Other_region3);

              mc_total->Add(Helium_region4 );
              mc_total->Add(Aluminium_region4 );
              mc_total->Add(Carbon_region4);
              mc_total->Add(Iron_region4 );
              mc_total->Add(Lead_region4 );
              mc_total->Add(Other_region4);

              data->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
              mc_total->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));


              TH1D* h_data_Combined = new TH1D(data_region1->GetCVHistoWithError());
              //TH1D* h_TOTAL = new TH1D(Helium_region1->GetCVHistoWithError());

              TH1D* h_Helium_region1 = new TH1D(Helium_region1->GetCVHistoWithError());
              TH1D* h_Aluminium_region1 = new TH1D(Aluminium_region1->GetCVHistoWithError());
              TH1D* h_Carbon_Combined = new TH1D(Carbon_region1->GetCVHistoWithError());
              TH1D* h_Iron_Combined = new TH1D(Iron_region1->GetCVHistoWithError());
              TH1D* h_Lead_Combined = new TH1D(Lead_region1->GetCVHistoWithError());
              TH1D* h_Other_Combined = new TH1D(Other_region1->GetCVHistoWithError());

              TH1D* h_data_region2 = new TH1D(data_region2->GetCVHistoWithError());
              TH1D* h_Helium_region2 = new TH1D(Helium_region2->GetCVHistoWithError());
              TH1D* h_Aluminium_region2 = new TH1D(Aluminium_region2->GetCVHistoWithError());
              TH1D* h_Carbon_region2 = new TH1D(Carbon_region2->GetCVHistoWithError());
              TH1D* h_Iron_region2 = new TH1D(Iron_region2->GetCVHistoWithError());
              TH1D* h_Lead_region2 = new TH1D(Lead_region2->GetCVHistoWithError());
              TH1D* h_Other_region2 = new TH1D(Other_region2->GetCVHistoWithError());

              h_Carbon_Combined->Add(h_Carbon_region2);
              h_Iron_Combined->Add(h_Iron_region2);
              h_Lead_Combined->Add(h_Lead_region2);
              h_Other_Combined->Add(h_Other_region2);
              h_data_Combined->Add(h_data_region2);

              TH1D* h_data_region3 = new TH1D(data_region3->GetCVHistoWithError());
              TH1D* h_Helium_region3 = new TH1D(Helium_region3->GetCVHistoWithError());
              TH1D* h_Aluminium_region3 = new TH1D(Aluminium_region3->GetCVHistoWithError());

              TH1D* h_Carbon_region3 = new TH1D(Carbon_region3->GetCVHistoWithError());
              TH1D* h_Iron_region3 = new TH1D(Iron_region3->GetCVHistoWithError());
              TH1D* h_Lead_region3 = new TH1D(Lead_region3->GetCVHistoWithError());
              TH1D* h_Other_region3 = new TH1D(Other_region3->GetCVHistoWithError());

              h_Carbon_Combined->Add(h_Carbon_region3);
              h_Iron_Combined->Add(  h_Iron_region3);
              h_Lead_Combined->Add(  h_Lead_region3);
              h_Other_Combined->Add( h_Other_region3);
              h_data_Combined->Add(  h_data_region3);

              TH1D* h_data_region4 = new TH1D(data_region4->GetCVHistoWithError());
              TH1D* h_Helium_region4 = new TH1D(Helium_region4->GetCVHistoWithError());
              TH1D* h_Aluminium_region4 = new TH1D(Aluminium_region4->GetCVHistoWithError());

              TH1D* h_Carbon_region4 = new TH1D(Carbon_region4->GetCVHistoWithError());
              TH1D* h_Iron_region4 = new TH1D(Iron_region4->GetCVHistoWithError());
              TH1D* h_Lead_region4 = new TH1D(Lead_region4->GetCVHistoWithError());
              TH1D* h_Other_region4 = new TH1D(Other_region4->GetCVHistoWithError());


              h_Carbon_Combined->Add(h_Carbon_region4);
              h_Iron_Combined->Add(h_Iron_region4);
              h_Lead_Combined->Add(h_Lead_region4);
              h_Other_Combined->Add(h_Other_region4);

              h_data_Combined->Add(h_data_region4);



              ColorHists(h_Carbon_Combined, h_Iron_Combined, h_Lead_Combined,  h_Other_Combined);
              ColorData(h_data_Combined);
              Color_HeliumHists(h_Helium_region1, h_Helium_region2, h_Helium_region3, h_Helium_region4);
              Color_AluminiumHists(h_Aluminium_region1, h_Aluminium_region2, h_Aluminium_region3, h_Aluminium_region4);

              TH1D* h_mc_total = new TH1D(mc_total->GetCVHistoWithError());


            //double total1 =   h_TOTAL->Integral(1,h_TOTAL->GetNbinsX());
            double total2 =   h_mc_total->Integral(1,h_mc_total->GetNbinsX());

              h_mc_total->SetName("h_mc_total");

              double plot_chisq = 999;
              //double plot_chisq = calc_ChiSq(data, signal, WithPi0, QELike, SinglePiPlus, Other);

              if(UseLogChi == false){plot_chisq = calc_ChiSq(h_data_Combined,
                h_Helium_region1,
                h_Helium_region2,
                h_Helium_region3,
                h_Helium_region4,
                h_Aluminium_region1,
                h_Aluminium_region2,
                h_Aluminium_region3,
                h_Aluminium_region4,
                h_Carbon_Combined, h_Lead_Combined, h_Iron_Combined, h_Other_Combined);}
              else if(UseLogChi == true){plot_chisq = calc_LogChiSq(h_data_Combined,
                h_Helium_region1,
                h_Helium_region2,
                h_Helium_region3,
                h_Helium_region4,
                h_Aluminium_region1,
                h_Aluminium_region2,
                h_Aluminium_region3,
                h_Aluminium_region4,
                h_Carbon_Combined, h_Lead_Combined, h_Iron_Combined, h_Other_Combined);}


                h_Other_Combined->Add(h_Carbon_Combined);
                h_Other_Combined->Add(h_Iron_Combined);
                h_Other_Combined->Add(h_Lead_Combined);


                if(doAreaNormalized == true){

                  if(h_mc_total->GetNbinsX() !=h_data_Combined->GetNbinsX()){std::cout<<"~~~ Whoah Data and MC have different number of Bins HistTitle : "<< Hist_title<<std::endl; assert(false); }
                  double MCArea = h_mc_total->Integral(1,h_mc_total->GetNbinsX());
                  double DataArea = h_data_Combined->Integral(1,h_data_Combined->GetNbinsX());
                  double areascaler = DataArea / MCArea;

                  h_mc_total->Scale(areascaler);
                  //h_TOTAL->Scale(areascaler);
                  h_Helium_region1->Scale(areascaler);
                  h_Aluminium_region1->Scale(areascaler);

                  h_Helium_region2->Scale(areascaler);
                  h_Aluminium_region2->Scale(areascaler);

                  h_Helium_region3->Scale(areascaler);
                  h_Aluminium_region3->Scale(areascaler);

                  h_Helium_region4->Scale(areascaler);
                  h_Aluminium_region4->Scale(areascaler);

                  //h_Carbon_Combined->Scale(areascaler);
                  //h_Iron_Combined->Scale(areascaler);
                  //h_Lead_Combined->Scale(areascaler);
                  h_Other_Combined->Scale(areascaler);

                }

                //////////////////////////////////////
                //// Combining All Other
                //////////////////////////////////////



              std::string yaxis;
              if(MakeBinWidth==true){
              //  h_TOTAL->Scale(1.0, "width");
                h_mc_total->Scale(1.0, "width");

                h_Helium_region1->Scale(1.0, "width");
                h_Aluminium_region1->Scale(1.0, "width");

                h_Helium_region2->Scale(1.0, "width");
                h_Aluminium_region2->Scale(1.0, "width");

                h_Helium_region3->Scale(1.0, "width");
                h_Aluminium_region3->Scale(1.0, "width");

                h_Helium_region4->Scale(1.0, "width");
                h_Aluminium_region4->Scale(1.0, "width");

                //h_Carbon_Combined->Scale(1.0, "width");
                //h_Iron_Combined->Scale(1.0, "width");
                //h_Lead_Combined->Scale(1.0, "width");
                h_Other_Combined->Scale(1.0, "width");
                h_data_Combined->Scale(1.0, "width");

                double binwidth_title = h_mc_total -> GetBinWidth(3);
                yaxis = Form("NEvents / %.2f",binwidth_title);
                if(doAreaNormalized == true){yaxis = Form("[DataAreaNorm] NEvents / %.2f",binwidth_title);}
                //std::cout<< "yaxis = "<< yaxis<<std::endl;
                //std::cout<<"Finished Bin width Norm"<<std::endl;
              }
              else{
                yaxis = "NEvents";
              //  std::cout<<"FInished Bin NOT width Norm"<<std::endl;
              }

              // ------------------------------------------------------------------------
              // Unique Plot for Single Error Band, Single Universe
              //      Comment this section out
              // ------------------------------------------------------------------------


              // Create Canvas and Divide it into two
              TCanvas* c = new TCanvas("c","c",800, 800);
              //TCanvas cE("cE","cE", 800, 800);
              // Upper Pad is the Data vs MC
              //OLDTPad *pad1 = new TPad("pad1", "pad1", 0.05, 0.3, 1, 1.0);
              TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
              pad1->SetBottomMargin(0); // Top and Bottom Plots attached
              pad1->Draw();
              pad1->cd(); // pad1 is the current pad
                // Plot MC Models as THStack
              THStack* hs = new THStack("hs","");
              h_Helium_region1->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
              hs->Add(h_Helium_region1);
              hs->Add(h_Helium_region2);
              hs->Add(h_Helium_region3);
              hs->Add(h_Helium_region4);
              hs->Add(h_Aluminium_region1);
              hs->Add(h_Aluminium_region2);
              hs->Add(h_Aluminium_region3);
              hs->Add(h_Aluminium_region4);
            //  hs->Add(h_Carbon_Combined);
              //hs->Add(h_Iron_Combined);
              //hs->Add(h_Lead_Combined);
              hs->Add(h_Other_Combined);

              //std::cout<<"Finished adding hist to hs II"<<std::endl;

              // Styling
              hs->Draw("HIST");
              hs->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
              hs->GetYaxis()->SetTitle(Form("%s",yaxis.c_str()));
              hs->GetYaxis()->SetTitleFont(62);
              hs->GetYaxis()->SetTitleSize(0.06);
              hs->GetXaxis()->SetTitleSize(0.06);
              hs->GetXaxis()->CenterTitle();
              //hs->GetYaxis()->SetTitleOffset(1.2);
              hs->GetYaxis()->SetLabelFont(42);
              hs->GetYaxis()->SetLabelSize(0.05);

            if(applyMaxY==false){
              if(h_mc_total->GetMaximum()>h_data_Combined->GetMaximum()  ){
                hs->SetMaximum(h_mc_total->GetMaximum() * 1.45);
              }
              else { hs->SetMaximum(h_data_Combined->GetMaximum() * 1.45);}
             }
            else if (applyMaxY==true){
             hs->SetMaximum(MaxY);
            }

            hs->SetMinimum(-1);
      //        hs->SetMaximum(hist_max * 1.45);
       //
              h_mc_total->SetMarkerStyle(0);
              h_mc_total->SetLineWidth(2);
              h_mc_total->SetLineColor(kBlack);
              h_mc_total->SetFillStyle(0);
              //h_mc_total->Draw("SAME HIST");


              //std::cout<<"Finshed Drawing Hist "<<std::endl;

              // Add Data Plot
              h_data_Combined->Draw("SAME E1 X0");
              //std::cout<<"FInished Drawing h_data"<<std::endl;

              // Add Legend
              TLegend *legend = new TLegend(0.75,0.55,0.91,0.92);
              legend->AddEntry(h_data_Combined, "Data");
              //legend->AddEntry(h_mc_total, "Total MC");
              // Add Weights as Text to Modified Plot
              int nPoints = h_data_Combined->GetNbinsX()-1;

              //std::cout<<"nPoints = "<<nPoints<< std::endl;

              // Add Plot-ChiSq
              TLatex* text = new TLatex;
              text->SetNDC();
              text->SetTextSize(0.03);
              text->SetTextColor(kBlue);




                if (ind == 0){
                  ChiSq_before_fit_var.push_back(plot_chisq);
                  ChiSqrt = plot_chisq;
                }


                  legend->AddEntry(h_Helium_region1,    "^{4}He USCap ",         "f");
                  legend->AddEntry(h_Helium_region2,    "^{4}He Barrel ",        "f");
                  legend->AddEntry(h_Helium_region3,    "^{4}He DSCap ",         "f");
                  legend->AddEntry(h_Helium_region4,    "^{4}He DSConcave",      "f");
                  legend->AddEntry(h_Aluminium_region1, "^{27}Al USCap ",        "f");
                  legend->AddEntry(h_Aluminium_region2, "^{27}Al Barrel ",       "f");
                  legend->AddEntry(h_Aluminium_region3, "^{27}Al DSCap ",         "f");
                  legend->AddEntry(h_Aluminium_region4, "^{27}Al DSConcave",      "f");
                  legend->AddEntry(h_Other_Combined,  "Other","f");

                text->SetTextSize(0.03);
                text->DrawLatex(0.2, 0.85, Form("Plot #chi^{2} = %3.2f", plot_chisq));
                text->DrawLatex(0.2, 0.82, Form("Plot #chi^{2}/dof = %3.2f", plot_chisq / (double) nPoints));

                legend->SetTextSize(0.025);
                legend->SetTextFont(42);
                legend->Draw();

                text->SetTextSize(0.02);
                text->SetTextColor(kBlack);

              if (ind != 0 &&  FitType== 1){
              int nPars = 4;
              double xplace = .2;
              double yplace = 0.80;
              text->DrawLatex(xplace, yplace, Form("Fit Results with %d points, %d pars", nPoints, nPars));
              yplace-=.02;
              text->DrawLatex(xplace, yplace , Form("Before Fit #chi^{2} = %3.2f", ChiSqrt));
              yplace-=.02;
              text->DrawLatex(xplace, yplace, Form("Before Fit #chi^{2}/dof = %3.2f", ChiSqrt/(nPoints-nPars)));
              yplace-=.02;
              text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2} = %3.2f", plot_chisq));
              yplace-=.02;
              text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2}/dof = %3.2f", plot_chisq/(double)(nPoints-nPars)));
              yplace-=.02;
              text->DrawLatex(xplace, yplace, Form("#color[4]{USCap wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[0], err_Aluminium[0]));
              yplace-=.02;
              text->DrawLatex(xplace, yplace, Form("#color[4]{Barrel wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[1], err_Aluminium[1]));
              yplace-=.02;
              text->DrawLatex(xplace, yplace, Form("#color[4]{DSCap wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[2], err_Aluminium[2]));
              yplace-=.02;
              text->DrawLatex(xplace, yplace, Form("#color[4]{DSConcave  wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[3], err_Aluminium[3]));
              yplace-=.02;
              ChiSqrtAfter = plot_chisq;

              }
              delete text;
              plotter->AddHistoTitle(Hist_title.c_str(),.04);
              plotter->WritePreliminary("TL", .025, 0, 0, false);
              // Plot Lower Plot: Data vs MC Ratio
              c->cd(); // Go back to default Canvas before creating 2nd Pad
              //TPad *pad2 = new TPad("pad2", "pad2", 0.05, 0.05, 1, 0.3);

              //pad2->SetTopMargin(0);
              //pad2->SetBottomMargin(0.2);
              c->Modified();
              TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
              pad2->SetTopMargin(0);
              pad2->SetBottomMargin(0.2);
              pad2->SetGridx(); // vertical grid
              pad2->Draw();
              pad2->cd();

              // Calculate the Ratio

              //h_data_mc_ratio->Draw("HIST");
              plotter->axis_title_size_x = 0.1;
              plotter->axis_title_offset_y = .4;
              plotter->axis_title_offset_x = 1.35;
              plotter->axis_title_size_y = 0.12;
              plotter->axis_label_size = 0.1;
              plotter->axis_maximum = 2.5;
              plotter->axis_minimum = .5;
              TH1D*mc_total_clone = (TH1D*)mc_total->Clone("mc_total_clone");
              TH1D*data_clone = (TH1D*)data->Clone("data_clone");
              mc_total_clone->Divide(data_clone, mc_total_clone);
              double min,max;
              min =  mc_total_clone->GetXaxis()->GetXmin();
              max =  mc_total_clone->GetXaxis()->GetXmax();
              int nbins = mc_total_clone->GetNbinsX();

              TGraph *gr = new TGraph(nbins);
              gr->SetName("GraphNoError");
              int counter =1;
              for(int i = 2; i <= nbins; i++ ){
                double binContent = mc_total_clone->GetBinContent(i);
                double binedge = mc_total_clone-> GetXaxis() ->GetBinUpEdge(i);

                if(binContent >0.0){
                gr->SetPoint(i, binedge, binContent);
                counter++;}
                }

                TF1 *fpol = new TF1("fpol", "pol1",min,max);
                gr->Fit("fpol","RQ");
                gr->SetLineWidth(2);
                auto chi_sq = fpol->GetChisquare();
                auto NDF_int = fpol->GetNDF();
                auto par1 = fpol->GetParameter(0);
                auto par2 = fpol->GetParameter(1);
              plotter->DrawDataMCRatio(data, mc_total, 1.0, false, false , -.5, 2, "#frac{Data}{MC}", false);

              fpol->SetLineColor(kRed);
              fpol->SetLineStyle(7);
              fpol->Draw("SAME");

              TLine ratio_1;
              ratio_1.SetLineWidth(2);
              ratio_1.SetLineStyle(7);
              ratio_1.SetLineColor(kBlue);
              double line_min = h_data_Combined->GetBinLowEdge(1);
              double line_max = h_data_Combined->GetBinLowEdge(h_data_Combined->GetNbinsX()+1);
              ratio_1.DrawLine(line_min,1,line_max,1);


              TLatex* textnew = new TLatex;
              textnew->SetNDC();
              textnew->SetTextSize(0.07);
              textnew->SetTextColor(kRed);
              textnew->DrawLatex(0.22, 0.9, Form("Fitted Line: %.4f + %.4f * x,  #chi^{2}/ndf = %.2f / %i ", par1, par2, chi_sq , NDF_int));


              // Plot Output
              c->Update();
              c->cd();
              c->Print(pdf_label.c_str(),"pdf");
              delete plotter;
              delete legend;
              delete hs;
              delete pad1;
              delete pad2;
              delete c;
              delete data;
              delete mc_total;
              delete h_data_Combined;
              delete h_Helium_region1;
              delete h_Aluminium_region1;
              delete h_Carbon_Combined;
              delete h_Iron_Combined;
              delete h_Lead_Combined;
              delete h_Other_Combined;
              delete h_data_region2;
              delete h_Helium_region2;
              delete h_Aluminium_region2;
              delete h_Carbon_region2;
              delete h_Iron_region2;
              delete h_Lead_region2;
              delete h_Other_region2;
              delete h_data_region3;
              delete h_Helium_region3;
              delete h_Aluminium_region3;
              delete h_Carbon_region3;
              delete h_Iron_region3;
              delete h_Lead_region3;
              delete h_Other_region3;
              delete h_data_region4;
              delete h_Helium_region4;
              delete h_Aluminium_region4;
              delete h_Carbon_region4;
              delete h_Iron_region4;
              delete h_Lead_region4;
              delete h_Other_region4;
              delete gr;
              delete fpol;

            }
/////////
void Helium_3CryoRegionsSideBandTool::Plot_regions_addArrow(std::string pdf_label, int ind, double POT_ratio,
       MnvH1D* data_region1, MnvH1D* mc_total_region1, MnvH1D* Helium_region1, MnvH1D* Aluminium_region1, MnvH1D* Carbon_region1,
       MnvH1D* Iron_region1, MnvH1D* Lead_region1, MnvH1D* Other_region1,

       MnvH1D* data_region2, MnvH1D* mc_total_region2, MnvH1D* Helium_region2, MnvH1D* Aluminium_region2, MnvH1D* Carbon_region2,
       MnvH1D* Iron_region2, MnvH1D* Lead_region2, MnvH1D* Other_region2,

       MnvH1D* data_region3, MnvH1D* mc_total_region3, MnvH1D* Helium_region3, MnvH1D* Aluminium_region3, MnvH1D* Carbon_region3,
       MnvH1D* Iron_region3, MnvH1D* Lead_region3, MnvH1D* Other_region3,

       MnvH1D* data_region4, MnvH1D* mc_total_region4, MnvH1D* Helium_region4, MnvH1D* Aluminium_region4, MnvH1D* Carbon_region4,
       MnvH1D* Iron_region4, MnvH1D* Lead_region4, MnvH1D* Other_region4,

       std::string Hist_title, std::string xaxislabel, double &ChiSqrt, double &ChiSqrtAfter, int FitType,
        double cut_location, double y1_arrow,  double y2_arrow,  double arrow_length, bool UseLogChi, bool doAreaNormalized )
  {

    std::string type;
    if (ind == 0) type = "Nominal";
    else type = "Fitted";
    //  std::cout<<"Ploting type: Combined CryoRegions  "<< type<<std::endl;

    //PlotUtils::MnvPlotter* plotter= new mnvPlotter();
    MnvPlotter* plotter = new MnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
    //plotter(PlotUtils::kCCInclusiveHeliumStyle);
    MnvH1D *data = (PlotUtils::MnvH1D*)data_region1->Clone("data");
    data->Add(data_region2);
    data->Add(data_region3);
    data->Add(data_region4);

    MnvH1D *mc_total = (PlotUtils::MnvH1D*)Helium_region1->Clone("mc_total");
    mc_total->Add(Aluminium_region1 );
    mc_total->Add(Carbon_region1);
    mc_total->Add(Iron_region1 );
    mc_total->Add(Lead_region1 );
    mc_total->Add(Other_region1);

    mc_total->Add(Helium_region2 );
    mc_total->Add(Aluminium_region2 );
    mc_total->Add(Carbon_region2);
    mc_total->Add(Iron_region2 );
    mc_total->Add(Lead_region2 );
    mc_total->Add(Other_region2);

    mc_total->Add(Helium_region3 );
    mc_total->Add(Aluminium_region3 );
    mc_total->Add(Carbon_region3);
    mc_total->Add(Iron_region3 );
    mc_total->Add(Lead_region3 );
    mc_total->Add(Other_region3);

    mc_total->Add(Helium_region4 );
    mc_total->Add(Aluminium_region4 );
    mc_total->Add(Carbon_region4);
    mc_total->Add(Iron_region4 );
    mc_total->Add(Lead_region4 );
    mc_total->Add(Other_region4);

    data->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
    mc_total->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));


    TH1D* h_data_Combined = new TH1D(data_region1->GetCVHistoWithError());
    TH1D* h_Helium_region1 = new TH1D(Helium_region1->GetCVHistoWithError());
    TH1D* h_Aluminium_region1 = new TH1D(Aluminium_region1->GetCVHistoWithError());

    TH1D* h_Carbon_Combined = new TH1D(Carbon_region1->GetCVHistoWithError());
    TH1D* h_Iron_Combined = new TH1D(Iron_region1->GetCVHistoWithError());
    TH1D* h_Lead_Combined = new TH1D(Lead_region1->GetCVHistoWithError());
    TH1D* h_Other_Combined = new TH1D(Other_region1->GetCVHistoWithError());

    TH1D* h_data_region2 = new TH1D(data_region2->GetCVHistoWithError());
    TH1D* h_Helium_region2 = new TH1D(Helium_region2->GetCVHistoWithError());
    TH1D* h_Aluminium_region2 = new TH1D(Aluminium_region2->GetCVHistoWithError());
    TH1D* h_Carbon_region2 = new TH1D(Carbon_region2->GetCVHistoWithError());
    TH1D* h_Iron_region2 = new TH1D(Iron_region2->GetCVHistoWithError());
    TH1D* h_Lead_region2 = new TH1D(Lead_region2->GetCVHistoWithError());
    TH1D* h_Other_region2 = new TH1D(Other_region2->GetCVHistoWithError());

    h_Carbon_Combined->Add(h_Carbon_region2);
    h_Iron_Combined->Add(h_Iron_region2);
    h_Lead_Combined->Add(h_Lead_region2);
    h_Other_Combined->Add(h_Other_region2);
    h_data_Combined->Add(h_data_region2);

    TH1D* h_data_region3 = new TH1D(data_region3->GetCVHistoWithError());
    TH1D* h_Helium_region3 = new TH1D(Helium_region3->GetCVHistoWithError());
    TH1D* h_Aluminium_region3 = new TH1D(Aluminium_region3->GetCVHistoWithError());

    TH1D* h_Carbon_region3 = new TH1D(Carbon_region3->GetCVHistoWithError());
    TH1D* h_Iron_region3 = new TH1D(Iron_region3->GetCVHistoWithError());
    TH1D* h_Lead_region3 = new TH1D(Lead_region3->GetCVHistoWithError());
    TH1D* h_Other_region3 = new TH1D(Other_region3->GetCVHistoWithError());

    h_Carbon_Combined->Add(h_Carbon_region3);
    h_Iron_Combined->Add(h_Iron_region3);
    h_Lead_Combined->Add(h_Lead_region3);
    h_Other_Combined->Add(h_Other_region3);
    h_data_Combined->Add(h_data_region3);

    TH1D* h_data_region4 = new TH1D(data_region4->GetCVHistoWithError());
    TH1D* h_Helium_region4 = new TH1D(Helium_region4->GetCVHistoWithError());
    TH1D* h_Aluminium_region4 = new TH1D(Aluminium_region4->GetCVHistoWithError());

    TH1D* h_Carbon_region4 = new TH1D(Carbon_region4->GetCVHistoWithError());
    TH1D* h_Iron_region4 = new TH1D(Iron_region4->GetCVHistoWithError());
    TH1D* h_Lead_region4 = new TH1D(Lead_region4->GetCVHistoWithError());
    TH1D* h_Other_region4 = new TH1D(Other_region4->GetCVHistoWithError());


    h_Carbon_Combined->Add(h_Carbon_region4);
    h_Iron_Combined->Add(h_Iron_region4);
    h_Lead_Combined->Add(h_Lead_region4);
    h_Other_Combined->Add(h_Other_region4);
    h_data_Combined->Add(h_data_region4);

    ColorHists(h_Carbon_Combined, h_Iron_Combined, h_Lead_Combined,  h_Other_Combined);
    ColorData(h_data_Combined);
    Color_HeliumHists(h_Helium_region1, h_Helium_region2, h_Helium_region3, h_Helium_region4);
    Color_AluminiumHists(h_Aluminium_region1, h_Aluminium_region2, h_Aluminium_region3, h_Aluminium_region4);

    // MC Total depend on the Modification
    //      If Raws - take the mc_total directly
    //      If Modified - Add all mc models;
    TH1D* h_mc_total = new TH1D(mc_total->GetCVHistoWithError());
    //TH1D* h_mc_total;
  /*  if (ind == 0){
      h_mc_total = new TH1D(mc_total_region1->GetCVHistoWithError());
      h_mc_total->Add(mc_total_region2);
      h_mc_total->Add(mc_total_region3);
      h_mc_total->Add(mc_total_region4);
    }
    else{
      h_mc_total = new TH1D(*h_Helium_region1);
      h_mc_total->Add(h_Helium_region2);
      h_mc_total->Add(h_Helium_region3);
      h_mc_total->Add(h_Helium_region4);

      h_mc_total->Add(h_Aluminium_region1);
      h_mc_total->Add(h_Aluminium_region2);
      h_mc_total->Add(h_Aluminium_region3);
      h_mc_total->Add(h_Aluminium_region4);

      h_mc_total->Add(h_Carbon_Combined);
      h_mc_total->Add(h_Iron_Combined);
      h_mc_total->Add(h_Lead_Combined);
      h_mc_total->Add(h_Other_Combined);
    }
*/

    double plot_chisq;
    if(UseLogChi==false){
      plot_chisq = calc_ChiSq(h_data_Combined,
        h_Helium_region1,
        h_Helium_region2,
        h_Helium_region3,
        h_Helium_region4,
        h_Aluminium_region1,
        h_Aluminium_region2,
        h_Aluminium_region3,
        h_Aluminium_region4,
        h_Carbon_Combined, h_Lead_Combined, h_Iron_Combined, h_Other_Combined);


      }
    else if(UseLogChi==true){

      plot_chisq = calc_LogChiSq(h_data_Combined,
        h_Helium_region1,
        h_Helium_region2,
        h_Helium_region3,
        h_Helium_region4,
        h_Aluminium_region1,
        h_Aluminium_region2,
        h_Aluminium_region3,
        h_Aluminium_region4,
        h_Carbon_Combined, h_Lead_Combined, h_Iron_Combined, h_Other_Combined);

      }


      if(doAreaNormalized == true){

        if(h_mc_total->GetNbinsX() !=h_data_Combined->GetNbinsX()){std::cout<<"~~~ Whoah Data and MC have different number of Bins HistTitle : "<< Hist_title<<std::endl; assert(false); }
        double MCArea = h_mc_total->Integral(1,h_mc_total->GetNbinsX());
        double DataArea = h_data_Combined->Integral(1,h_data_Combined->GetNbinsX());
        double areascaler = DataArea / MCArea;

        h_mc_total->Scale(areascaler);
        h_Helium_region1->Scale(areascaler);
        h_Aluminium_region1->Scale(areascaler);

        h_Helium_region2->Scale(areascaler);
        h_Aluminium_region2->Scale(areascaler);

        h_Helium_region3->Scale(areascaler);
        h_Aluminium_region3->Scale(areascaler);

        h_Helium_region4->Scale(areascaler);
        h_Aluminium_region4->Scale(areascaler);

        h_Carbon_Combined->Scale(areascaler);
        h_Iron_Combined->Scale(areascaler);
        h_Lead_Combined->Scale(areascaler);
        h_Other_Combined->Scale(areascaler);

      }

      h_Other_Combined->Add(h_Carbon_Combined);
      h_Other_Combined->Add(h_Iron_Combined);
      h_Other_Combined->Add(h_Lead_Combined);

      std::string yaxis;
      if(MakeBinWidth==true){

        h_mc_total->Scale(1.0, "width");

        h_Helium_region1->Scale(1.0, "width");
        h_Aluminium_region1->Scale(1.0, "width");

        h_Helium_region2->Scale(1.0, "width");
        h_Aluminium_region2->Scale(1.0, "width");

        h_Helium_region3->Scale(1.0, "width");
        h_Aluminium_region3->Scale(1.0, "width");

        h_Helium_region4->Scale(1.0, "width");
        h_Aluminium_region4->Scale(1.0, "width");

        //h_Carbon_Combined->Scale(1.0, "width");
        //h_Iron_Combined->Scale(1.0, "width");
        //h_Lead_Combined->Scale(1.0, "width");
        h_Other_Combined->Scale(1.0, "width");
        h_data_Combined->Scale(1.0, "width");

        double binwidth_title = h_mc_total -> GetBinWidth(3);
        yaxis = Form("NEvents / %.2f",binwidth_title);
        if(doAreaNormalized == true){yaxis = Form("[DataAreaNorm] NEvents / %.2f",binwidth_title);}
        //std::cout<< "yaxis = "<< yaxis<<std::endl;
        //std::cout<<"Finished Bin width Norm"<<std::endl;
      }
      else{
        yaxis = "NEvents";
        //  std::cout<<"FInished Bin NOT width Norm"<<std::endl;
      }

      // ------------------------------------------------------------------------
      // Unique Plot for Single Error Band, Single Universe
      //      Comment this section out
      // ------------------------------------------------------------------------


      // Create Canvas and Divide it into two
      TCanvas* c = new TCanvas("c","c",800, 800);
      //TCanvas cE("cE","cE", 800, 800);
      // Upper Pad is the Data vs MC
      //OLDTPad *pad1 = new TPad("pad1", "pad1", 0.05, 0.3, 1, 1.0);
      TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
      pad1->SetBottomMargin(0); // Top and Bottom Plots attached
      pad1->Draw();
      pad1->cd(); // pad1 is the current pad
      // Plot MC Models as THStack
      THStack* hs = new THStack("hs","");
      h_Helium_region1->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
      hs->Add(h_Helium_region1);
      hs->Add(h_Helium_region2);
      hs->Add(h_Helium_region3);
      hs->Add(h_Helium_region4);
      hs->Add(h_Aluminium_region1);
      hs->Add(h_Aluminium_region2);
      hs->Add(h_Aluminium_region3);
      hs->Add(h_Aluminium_region4);
      //hs->Add(h_Carbon_Combined);
      //hs->Add(h_Iron_Combined);
      //hs->Add(h_Lead_Combined);
      hs->Add(h_Other_Combined);

      //std::cout<<"Finished adding hist to hs II"<<std::endl;

      // Styling
      hs->Draw("HIST");
      hs->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
      hs->GetYaxis()->SetTitle(Form("%s",yaxis.c_str()));
      hs->GetYaxis()->SetTitleFont(62);
      hs->GetYaxis()->SetTitleSize(0.06);
      hs->GetXaxis()->SetTitleSize(0.06);
      hs->GetXaxis()->CenterTitle();
      //hs->GetYaxis()->SetTitleOffset(1.2);
      hs->GetYaxis()->SetLabelFont(42);
      hs->GetYaxis()->SetLabelSize(0.05);

      double hist_max = h_data_Combined->GetMaximum();
      //std::cout<<"GetMaximum() =  "<<hist_max<<std::endl;
      hs->SetMaximum(hist_max * 1.85);
      hs->SetMinimum(-1);

      c->Modified();

      //std::cout<<"Finshed Drawing Hist "<<std::endl;
      h_mc_total->SetMarkerStyle(0);
      h_mc_total->SetLineWidth(2);
      h_mc_total->SetFillStyle(0);
      h_mc_total->SetLineColor(kBlack);
      // Styling
      //h_mc_total->Draw("same HIST");
      // Add Data Plot
      h_data_Combined->Draw("SAME E1 X0");
      //  std::cout<<"FInished Drawing h_data"<<std::endl;

      // Add Legend
      TLegend *legend = new TLegend(0.75,0.55,0.91,0.92);
      legend->AddEntry(h_data_Combined, "Data");
      // Add Weights as Text to Modified Plot
      int nPoints = h_data_Combined->GetNbinsX()-1;

      //std::cout<<"nPoints = "<<nPoints<< std::endl;

      // Add Plot-ChiSq
      TLatex* text = new TLatex;
      text->SetNDC();
      text->SetTextSize(0.03);
      text->SetTextColor(kBlue);
      //double plot_chisq = calc_ChiSq(data, signal, WithPi0, QELike, SinglePiPlus, Other);



      if (ind == 0){
        ChiSq_before_fit_var.push_back(plot_chisq);
        ChiSqrt = plot_chisq;
      }


      if(FitType == 3){
        legend->AddEntry(h_Helium_region1,          "XCenter He: ",           "f");
        legend->AddEntry(h_Helium_region2,          "XLeftShelf He: ",        "f");
        legend->AddEntry(h_Helium_region3,          "XRightShelf He: ",       "f");
        legend->AddEntry(h_Helium_region4,          "XoutsideEdges He: ",     "f");
        legend->AddEntry(h_Aluminium_region1,       "XCenter Al: ",           "f");
        legend->AddEntry(h_Aluminium_region2,       "XLeftShelf Al: ",       "f");
        legend->AddEntry(h_Aluminium_region3,       "XRightShelf Al: ",      "f");
        legend->AddEntry(h_Aluminium_region4,       "XoutsideEdges Al: ", "f");
      }
      else if(FitType == 4){
        legend->AddEntry(h_Helium_region1,          "XCenter He: ",           "f");
        legend->AddEntry(h_Helium_region2,          "XLeftShelf He: ",        "f");
        legend->AddEntry(h_Helium_region3,          "XRightShelf He: ",       "f");
        legend->AddEntry(h_Helium_region4,          "^{4}He DSConcave ",     "f");
        legend->AddEntry(h_Aluminium_region1,       "XCenter Al: ",           "f");
        legend->AddEntry(h_Aluminium_region2,       "XLeftShelf Al: ",       "f");
        legend->AddEntry(h_Aluminium_region3,       "XRightShelf Al: ",      "f");
        legend->AddEntry(h_Aluminium_region4,       "^{27}Al DSConcave ", "f");
      }

      else{
        legend->AddEntry(h_Helium_region1,    "^{4}He USCap",        "f");
        legend->AddEntry(h_Helium_region2,    "^{4}He Barrel",       "f");
        legend->AddEntry(h_Helium_region3,    "^{4}He DSCap",         "f");
        legend->AddEntry(h_Helium_region4,    "^{4}He DSConcave", "f");
        legend->AddEntry(h_Aluminium_region1, "^{27}Al USCap",        "f");
        legend->AddEntry(h_Aluminium_region2, "^{27}Al Barrel",       "f");
        legend->AddEntry(h_Aluminium_region3, "^{27}Al DSCap",         "f");
        legend->AddEntry(h_Aluminium_region4, "^{27}Al DSConcave ", "f");
      }

      //legend->AddEntry(h_Carbon_Combined, "C: ",    "f");
      //legend->AddEntry(h_Iron_Combined,   "Fe: ",   "f");
      //legend->AddEntry(h_Lead_Combined,   "Pb: ",   "f");
      legend->AddEntry(h_Other_Combined,  "Other","f");
      legend->SetTextSize(0.025);
      legend->SetTextFont(42);
      legend->Draw();
      text->SetTextSize(0.02);
      text->SetTextColor(kBlack);
    if (ind != 0 &&  FitType== 1){
        int nPars = 4;
        double xplace = .2;
        double yplace = 0.80;
        text->DrawLatex(xplace, yplace, Form("Fit Results with %d points, %d pars", nPoints, nPars));
        yplace-=.02;
        text->DrawLatex(xplace, yplace , Form("Before Fit #chi^{2} = %3.2f", ChiSqrt));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("Before Fit #chi^{2}/dof = %3.2f", ChiSqrt/(nPoints-nPars)));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2} = %3.2f", plot_chisq));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2}/dof = %3.2f", plot_chisq/(double)(nPoints-nPars)));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{USCap wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[0], err_Aluminium[0]));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{Barrel wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[1], err_Aluminium[1]));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{DSCap wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[2], err_Aluminium[2]));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{DSConcave  wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[3], err_Aluminium[3]));
        yplace-=.02;
        ChiSqrtAfter = plot_chisq;

        }
    else if(ind != 0 && FitType == 2){
        int nPars = 4;
          double xplace = .2;
          double yplace = 0.80;
          text->DrawLatex(xplace, yplace, Form("Fit Results with %d points, %d pars", nPoints, nPars));
          yplace-=.02;
          text->DrawLatex(xplace, yplace , Form("Before Fit #chi^{2} = %3.2f", ChiSqrt));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("Before Fit #chi^{2}/dof = %3.2f", ChiSqrt/(nPoints-nPars)));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2} = %3.2f", plot_chisq));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2}/dof = %3.2f", plot_chisq/(double)(nPoints-nPars)));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("#color[4]{USCap wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[0], err_Aluminium[0]));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("#color[4]{Barrel wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[1], err_Aluminium[1]));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("#color[4]{DSCap wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[2], err_Aluminium[2]));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("#color[4]{DSConcave  wgt(He) = %3.2f #pm %3.2f}", wgt_Aluminium[3], err_Aluminium[3]));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("#color[4]{USCap wgt(He) = %3.2f #pm %3.2f}", wgt_Helium[0], err_Helium[0]));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("#color[4]{barrel wgt(He) = %3.2f #pm %3.2f}", wgt_Helium[1], err_Helium[1]));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("#color[4]{DSCap wgt(He) = %3.2f #pm %3.2f}", wgt_Helium[2], err_Helium[2]));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("#color[4]{DSConcave  wgt(He) = %3.2f #pm %3.2f}", wgt_Helium[3], err_Helium[3]));

          ChiSqrtAfter = plot_chisq;

        }
    else if(ind != 0 && FitType == 3){
        int nPars = 4;

        double xplace = .2;
        double yplace = 0.80;
        text->DrawLatex(xplace, yplace, Form("Fit Results with %d points, %d pars", nPoints, nPars));
        yplace-=.02;
        text->DrawLatex(xplace, yplace ,Form("Before Fit #chi^{2} = %3.2f", ChiSqrt));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("Before Fit #chi^{2}/dof = %3.2f", ChiSqrt/(nPoints-nPars)));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2} = %3.2f", plot_chisq));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2}/dof = %3.2f", plot_chisq/(double)(nPoints-nPars)));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{XCenter wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[0], err_Aluminium[0]));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{XLeftShelf wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[1], err_Aluminium[1]));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{XRightShelf wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[2], err_Aluminium[2]));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{XoutsideEdges cap wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[3], err_Aluminium[3]));
        yplace-=.02;
        ChiSqrtAfter = plot_chisq;

        }
    else if(ind != 0 && FitType == 4){
        int nPars = 4;
        double xplace = .2;
        double yplace = 0.80;
        text->DrawLatex(xplace, yplace, Form("Fit Results with %d points, %d pars", nPoints, nPars));
        yplace-=.02;
        text->DrawLatex(xplace, yplace ,Form("Before Fit #chi^{2} = %3.2f", ChiSqrt));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("Before Fit #chi^{2}/dof = %3.2f", ChiSqrt/(nPoints-nPars)));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2} = %3.2f", plot_chisq));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2}/dof = %3.2f", plot_chisq/(double)(nPoints-nPars)));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{XCenter wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[0], err_Aluminium[0]));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{XLeftShelf wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[1], err_Aluminium[1]));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{XRightShelf wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[2], err_Aluminium[2]));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{DSConcave  wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[3], err_Aluminium[3]));
        yplace-=.02;
        ChiSqrtAfter = plot_chisq;

        }

  //std::cout<<"FInished Drawing legend"<<std::endl;
  text->SetTextSize(0.03);
  text->DrawLatex(0.2, 0.85, Form("Plot #chi^{2} = %3.2f", plot_chisq));
  text->DrawLatex(0.2, 0.82, Form("Plot #chi^{2}/dof = %3.2f", plot_chisq / (double) nPoints));
  delete text;
  plotter->AddHistoTitle(Hist_title.c_str(),.04);
  plotter->WritePreliminary("TL", .025, 0, 0, false);
  double y2_arrow_max = hist_max *1.25;
  plotter->AddCutArrow(cut_location, y1_arrow,  y2_arrow_max,  arrow_length, "R");
  // Plot Lower Plot: Data vs MC Ratio
  c->cd(); // Go back to default Canvas before creating 2nd Pad
  //TPad *pad2 = new TPad("pad2", "pad2", 0.05, 0.05, 1, 0.3);

  //pad2->SetTopMargin(0);
  //pad2->SetBottomMargin(0.2);
  c->Modified();
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.2);
  pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();

  // Calculate the Ratio

  //h_data_mc_ratio->Draw("HIST");
  plotter->axis_title_size_x = 0.1;
  plotter->axis_title_offset_y = .4;
  plotter->axis_title_offset_x = 1.35;
  plotter->axis_title_size_y = 0.12;
  plotter->axis_label_size = 0.1;
  plotter->axis_maximum = 2.5;
  plotter->axis_minimum = .5;
  plotter->DrawDataMCRatio(data, mc_total, 1.0, false, false , -.5, 2, "#frac{Data}{MC}", false);
  // Add Ratio = 1 Line
  TLine ratio_1;
  ratio_1.SetLineWidth(2);
  ratio_1.SetLineStyle(7);
  ratio_1.SetLineColor(kBlue);
  double line_min = h_data_Combined->GetBinLowEdge(1);
  double line_max = h_data_Combined->GetBinLowEdge(h_data_Combined->GetNbinsX()+1);
  ratio_1.DrawLine(line_min,1,line_max,1);
  // Plot Output
  c->Update();
  c->cd();
  c->Print(pdf_label.c_str(),"pdf");

  delete plotter;
  delete legend;
  delete hs;
  delete pad1;
  delete pad2;
  delete c;
  delete data;
  delete mc_total;
  delete h_data_Combined;
  delete h_Helium_region1;
  delete h_Aluminium_region1;
  delete h_Carbon_Combined;
  delete h_Iron_Combined;
  delete h_Lead_Combined;
  delete h_Other_Combined;
  delete h_data_region2;
  delete h_Helium_region2;
  delete h_Aluminium_region2;
  delete h_Carbon_region2;
  delete h_Iron_region2;
  delete h_Lead_region2;
  delete h_Other_region2;
  delete h_data_region3;
  delete h_Helium_region3;
  delete h_Aluminium_region3;
  delete h_Carbon_region3;
  delete h_Iron_region3;
  delete h_Lead_region3;
  delete h_Other_region3;
  delete h_data_region4;
  delete h_Helium_region4;
  delete h_Aluminium_region4;
  delete h_Carbon_region4;
  delete h_Iron_region4;
  delete h_Lead_region4;
  delete h_Other_region4;
}
////////

void Helium_3CryoRegionsSideBandTool::Plot_regionsNoStack_addArrow(std::string pdf_label, int ind, double POT_ratio,
       MnvH1D* data_region1, MnvH1D* mc_total_region1, MnvH1D* Helium_region1, MnvH1D* Aluminium_region1, MnvH1D* Carbon_region1,
       MnvH1D* Iron_region1, MnvH1D* Lead_region1, MnvH1D* Other_region1,
       MnvH1D* data_region2, MnvH1D* mc_total_region2, MnvH1D* Helium_region2, MnvH1D* Aluminium_region2, MnvH1D* Carbon_region2,
       MnvH1D* Iron_region2, MnvH1D* Lead_region2, MnvH1D* Other_region2,
       MnvH1D* data_region3, MnvH1D* mc_total_region3, MnvH1D* Helium_region3, MnvH1D* Aluminium_region3, MnvH1D* Carbon_region3,
       MnvH1D* Iron_region3, MnvH1D* Lead_region3, MnvH1D* Other_region3,
       MnvH1D* data_region4, MnvH1D* mc_total_region4, MnvH1D* Helium_region4, MnvH1D* Aluminium_region4, MnvH1D* Carbon_region4,
       MnvH1D* Iron_region4, MnvH1D* Lead_region4, MnvH1D* Other_region4,

       std::string Hist_title, std::string xaxislabel, double &ChiSqrt, double &ChiSqrtAfter,
        int FitType, double cut_location, double y1_arrow,  double y2_arrow,  double arrow_length, bool UseLogChi, bool doAreaNormalized  )
       {

        std::string type;
        if (ind == 0) type = "Nominal";
        else type = "Fitted";
      //  std::cout<<"Ploting type: Combined CryoRegions  "<< type<<std::endl;

        //PlotUtils::MnvPlotter* plotter= new mnvPlotter();
         MnvPlotter* plotter = new MnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
        //plotter(PlotUtils::kCCInclusiveHeliumStyle);
        MnvH1D *data = (PlotUtils::MnvH1D*)data_region1->Clone("data");
        data->Add(data_region2);
        data->Add(data_region3);
        data->Add(data_region4);
        MnvH1D *mc_total = (PlotUtils::MnvH1D*)Helium_region1->Clone("mc_total");
        mc_total->Add(Aluminium_region1 );
        mc_total->Add(Carbon_region1);
        mc_total->Add(Iron_region1 );
        mc_total->Add(Lead_region1 );
        mc_total->Add(Other_region1);
        mc_total->Add(Helium_region2 );
        mc_total->Add(Aluminium_region2 );
        mc_total->Add(Carbon_region2);
        mc_total->Add(Iron_region2 );
        mc_total->Add(Lead_region2 );
        mc_total->Add(Other_region2);
        mc_total->Add(Helium_region3 );
        mc_total->Add(Aluminium_region3 );
        mc_total->Add(Carbon_region3);
        mc_total->Add(Iron_region3 );
        mc_total->Add(Lead_region3 );
        mc_total->Add(Other_region3);
        mc_total->Add(Helium_region4 );
        mc_total->Add(Aluminium_region4 );
        mc_total->Add(Carbon_region4);
        mc_total->Add(Iron_region4 );
        mc_total->Add(Lead_region4 );
        mc_total->Add(Other_region4);

        data->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
        mc_total->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));


        TH1D* h_data_Combined = new TH1D(data_region1->GetCVHistoWithError());
        TH1D* h_Helium_region1 = new TH1D(Helium_region1->GetCVHistoWithError());
        TH1D* h_Aluminium_region1 = new TH1D(Aluminium_region1->GetCVHistoWithError());

        TH1D* h_Carbon_Combined = new TH1D(Carbon_region1->GetCVHistoWithError());
        TH1D* h_Iron_Combined = new TH1D(Iron_region1->GetCVHistoWithError());
        TH1D* h_Lead_Combined = new TH1D(Lead_region1->GetCVHistoWithError());
        TH1D* h_Other_Combined = new TH1D(Other_region1->GetCVHistoWithError());

        TH1D* h_data_region2 = new TH1D(data_region2->GetCVHistoWithError());
        TH1D* h_Helium_region2 = new TH1D(Helium_region2->GetCVHistoWithError());
        TH1D* h_Aluminium_region2 = new TH1D(Aluminium_region2->GetCVHistoWithError());
        TH1D* h_Carbon_region2 = new TH1D(Carbon_region2->GetCVHistoWithError());
        TH1D* h_Iron_region2 = new TH1D(Iron_region2->GetCVHistoWithError());
        TH1D* h_Lead_region2 = new TH1D(Lead_region2->GetCVHistoWithError());
        TH1D* h_Other_region2 = new TH1D(Other_region2->GetCVHistoWithError());

        h_Carbon_Combined->Add(h_Carbon_region2);
        h_Iron_Combined->Add(h_Iron_region2);
        h_Lead_Combined->Add(h_Lead_region2);
        h_Other_Combined->Add(h_Other_region2);
        h_data_Combined->Add(h_data_region2);

        TH1D* h_data_region3 = new TH1D(data_region3->GetCVHistoWithError());
        TH1D* h_Helium_region3 = new TH1D(Helium_region3->GetCVHistoWithError());
        TH1D* h_Aluminium_region3 = new TH1D(Aluminium_region3->GetCVHistoWithError());

        TH1D* h_Carbon_region3 = new TH1D(Carbon_region3->GetCVHistoWithError());
        TH1D* h_Iron_region3 = new TH1D(Iron_region3->GetCVHistoWithError());
        TH1D* h_Lead_region3 = new TH1D(Lead_region3->GetCVHistoWithError());
        TH1D* h_Other_region3 = new TH1D(Other_region3->GetCVHistoWithError());

        h_Carbon_Combined->Add(h_Carbon_region3);
        h_Iron_Combined->Add(h_Iron_region3);
        h_Lead_Combined->Add(h_Lead_region3);
        h_Other_Combined->Add(h_Other_region3);
        h_data_Combined->Add(h_data_region3);

        TH1D* h_data_region4 = new TH1D(data_region4->GetCVHistoWithError());
        TH1D* h_Helium_region4 = new TH1D(Helium_region4->GetCVHistoWithError());
        TH1D* h_Aluminium_region4 = new TH1D(Aluminium_region4->GetCVHistoWithError());

        TH1D* h_Carbon_region4 = new TH1D(Carbon_region4->GetCVHistoWithError());
        TH1D* h_Iron_region4 = new TH1D(Iron_region4->GetCVHistoWithError());
        TH1D* h_Lead_region4 = new TH1D(Lead_region4->GetCVHistoWithError());
        TH1D* h_Other_region4 = new TH1D(Other_region4->GetCVHistoWithError());

        h_Carbon_Combined->Add(h_Carbon_region4);
        h_Iron_Combined->Add(h_Iron_region4);
        h_Lead_Combined->Add(h_Lead_region4);
        h_Other_Combined->Add(h_Other_region4);
        h_data_Combined->Add(h_data_region4);

        double plot_chisq;
         if(UseLogChi==false){
           plot_chisq = calc_ChiSq(h_data_Combined,
          h_Helium_region1,
          h_Helium_region2,
          h_Helium_region3,
          h_Helium_region4,
          h_Aluminium_region1,
          h_Aluminium_region2,
          h_Aluminium_region3,
          h_Aluminium_region4,
          h_Carbon_Combined, h_Lead_Combined, h_Iron_Combined, h_Other_Combined);


         }
         else if(UseLogChi==true){

           plot_chisq = calc_LogChiSq(h_data_Combined,
          h_Helium_region1,
          h_Helium_region2,
          h_Helium_region3,
          h_Helium_region4,
          h_Aluminium_region1,
          h_Aluminium_region2,
          h_Aluminium_region3,
          h_Aluminium_region4,
          h_Carbon_Combined, h_Lead_Combined, h_Iron_Combined, h_Other_Combined);

         }

        ColorHistsForLines(h_Carbon_Combined, h_Iron_Combined, h_Lead_Combined,  h_Other_Combined);
        ColorData(h_data_Combined);
        Color_HeliumHistsForLines(h_Helium_region1, h_Helium_region2, h_Helium_region3, h_Helium_region4);
        Color_AluminiumHistsForLines(h_Aluminium_region1, h_Aluminium_region2, h_Aluminium_region3, h_Aluminium_region4);

        // MC Total depend on the Modification
        //      If Raws - take the mc_total directly
        //      If Modified - Add all mc models;
        h_Other_Combined->Add(h_Carbon_Combined);
        h_Other_Combined->Add(h_Iron_Combined);
        h_Other_Combined->Add(h_Lead_Combined);

    TH1D* h_mc_total = new TH1D(mc_total->GetCVHistoWithError());

        if(doAreaNormalized == true){

          if(h_mc_total->GetNbinsX() != h_data_Combined->GetNbinsX()){std::cout<<"~~~ Whoah Data and MC have different number of Bins HistTitle : "<< Hist_title<<std::endl; assert(false); }
          double MCArea = h_mc_total->Integral(1, h_mc_total->GetNbinsX());
          double DataArea = h_data_Combined->Integral(1, h_data_Combined->GetNbinsX());
          double areascaler = DataArea / MCArea;

          h_mc_total->Scale(areascaler);

          h_Helium_region1->Scale(areascaler);
          h_Aluminium_region1->Scale(areascaler);

          h_Helium_region2->Scale(areascaler);
          h_Aluminium_region2->Scale(areascaler);

          h_Helium_region3->Scale(areascaler);
          h_Aluminium_region3->Scale(areascaler);

          h_Helium_region4->Scale(areascaler);
          h_Aluminium_region4->Scale(areascaler);

          //h_Carbon_Combined->Scale(areascaler);
          //h_Iron_Combined->Scale(areascaler);
          //h_Lead_Combined->Scale(areascaler);
          h_Other_Combined->Scale(areascaler);

        }



        std::string yaxis;
        if(MakeBinWidth==true){

          h_mc_total->Scale(1.0, "width");

          h_Helium_region1->Scale(1.0, "width");
          h_Aluminium_region1->Scale(1.0, "width");

          h_Helium_region2->Scale(1.0, "width");
          h_Aluminium_region2->Scale(1.0, "width");

          h_Helium_region3->Scale(1.0, "width");
          h_Aluminium_region3->Scale(1.0, "width");

          h_Helium_region4->Scale(1.0, "width");
          h_Aluminium_region4->Scale(1.0, "width");

          //h_Carbon_Combined->Scale(1.0, "width");
          //h_Iron_Combined->Scale(1.0, "width");
          //h_Lead_Combined->Scale(1.0, "width");
          h_Other_Combined->Scale(1.0, "width");
          h_data_Combined->Scale(1.0, "width");

          double binwidth_title = h_mc_total -> GetBinWidth(3);
          yaxis = Form("NEvents / %.2f",binwidth_title);
          if(doAreaNormalized == true){yaxis = Form("[DataAreaNorm] NEvents / %.2f",binwidth_title);}
          //std::cout<< "yaxis = "<< yaxis<<std::endl;
          //std::cout<<"Finished Bin width Norm"<<std::endl;
        }
        else{
          yaxis = "NEvents";
        //  std::cout<<"FInished Bin NOT width Norm"<<std::endl;
        }

        // ------------------------------------------------------------------------
        // Unique Plot for Single Error Band, Single Universe
        //      Comment this section out
        // ------------------------------------------------------------------------


        // Create Canvas and Divide it into two
        TCanvas* c = new TCanvas("c","c",800, 800);
        TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
        pad1->SetBottomMargin(0); // Top and Bottom Plots attached
        pad1->Draw();
        pad1->cd(); // pad1 is the current pad
          // Plot MC Models as THStack
          data->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
          h_mc_total->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
          h_mc_total->GetYaxis()->SetTitle(Form("%s",yaxis.c_str()));
          h_mc_total->GetYaxis()->SetTitleFont(62);
          h_mc_total->GetYaxis()->SetTitleSize(0.06);
          //hs->GetYaxis()->CenterTitle();
          //hs->GetYaxis()->SetTitleOffset(1.2);
          h_mc_total->GetXaxis()->SetTitleFont(62);
          h_mc_total->GetXaxis()->SetTitleSize(0.06);

          h_mc_total->GetYaxis()->SetLabelFont(42);
          h_mc_total->GetYaxis()->SetLabelSize(0.05);

          double hist_max;
          if(h_mc_total->GetMaximum()>h_data_Combined->GetMaximum()){
            hist_max= h_mc_total->GetMaximum();
            h_mc_total->SetMaximum(h_mc_total->GetMaximum() * 1.45);
          }
          else { hist_max= h_data_Combined->GetMaximum();
            h_mc_total->SetMaximum(h_data_Combined->GetMaximum() * 1.45);}

          //h_mc_total->SetMarkerStyle(0);
          h_mc_total->SetLineWidth(2);
          h_mc_total->SetLineColor(kBlack);
          //h_mc_total->SetFillColor(41);
          // Styling
          h_mc_total->Smooth();
          h_Helium_region1->Smooth();
          h_Helium_region2->Smooth();
          h_Helium_region3->Smooth();
          h_Helium_region4->Smooth();
          h_Aluminium_region1->Smooth();
          h_Aluminium_region2->Smooth();
          h_Aluminium_region3->Smooth();
          h_Aluminium_region4->Smooth();
          h_Other_Combined->Smooth();


          h_mc_total->Draw("HIST L");
          h_Helium_region1->DrawCopy("SAME HIST L");
          h_Helium_region2->DrawCopy("SAME HIST L");
          h_Helium_region3->DrawCopy("SAME HIST L");
          h_Helium_region4->DrawCopy("SAME HIST L");
          h_Aluminium_region1->DrawCopy("SAME HIST L");
          h_Aluminium_region2->DrawCopy("SAME HIST L");
          h_Aluminium_region3->DrawCopy("SAME HIST L");
          h_Aluminium_region4->DrawCopy("SAME HIST L");
          //h_Carbon_Combined->Draw("SAME L");
          //h_Iron_Combined->Draw("SAME L");
          //h_Lead_Combined->Draw("SAME L");
          h_Other_Combined->DrawCopy("SAME HIST L");

          c->Modified();

        //std::cout<<"Finshed Drawing Hist "<<std::endl;

        // Add Data Plot
        h_data_Combined->Draw("SAME E1 X0");
      //  std::cout<<"FInished Drawing h_data"<<std::endl;

        // Add Legend
        TLegend *legend = new TLegend(0.75,0.55,0.91,0.92);
        legend->AddEntry(h_data_Combined, "Data");
        legend->AddEntry(h_mc_total, "Total MC",           "l");
        // Add Weights as Text to Modified Plot
        int nPoints = h_data_Combined->GetNbinsX()-1;


        // Add Plot-ChiSq
        TLatex* text = new TLatex;
        text->SetNDC();
        text->SetTextSize(0.03);
        text->SetTextColor(kBlue);
        text->DrawLatex(0.2, 0.85, Form("Plot #chi^{2} = %3.2f", plot_chisq));
        text->DrawLatex(0.2, 0.82, Form("Plot #chi^{2}/dof = %3.2f", plot_chisq / (double) nPoints));

          if (ind == 0){
            ChiSq_before_fit_var.push_back(plot_chisq);
            ChiSqrt = plot_chisq;
          }


          if(FitType == 3){
            legend->AddEntry(h_Helium_region1,          "XCenter He: ",           "l");
            legend->AddEntry(h_Helium_region2,          "XLeftShelf He: ",        "l");
            legend->AddEntry(h_Helium_region3,          "XRightShelf He: ",       "l");
            legend->AddEntry(h_Helium_region4,          "XoutsideEdges He: ",     "l");
            legend->AddEntry(h_Aluminium_region1,       "XCenter Al: ",           "l");
            legend->AddEntry(h_Aluminium_region2,       "XLeftShelf Al: ",       "l");
            legend->AddEntry(h_Aluminium_region3,       "XRightShelf Al: ",      "l");
            legend->AddEntry(h_Aluminium_region4,       "XoutsideEdges Al: ", "l");
          }
          else if(FitType == 4){
            legend->AddEntry(h_Helium_region1,          "XCenter He: ",           "l");
            legend->AddEntry(h_Helium_region2,          "XLeftShelf He: ",        "l");
            legend->AddEntry(h_Helium_region3,          "XRightShelf He: ",       "l");
            legend->AddEntry(h_Helium_region4,          "^{4}He DSConcave ",     "l");
            legend->AddEntry(h_Aluminium_region1,       "XCenter Al: ",           "l");
            legend->AddEntry(h_Aluminium_region2,       "XLeftShelf Al: ",       "l");
            legend->AddEntry(h_Aluminium_region3,       "XRightShelf Al: ",      "l");
            legend->AddEntry(h_Aluminium_region4,       "^{27}Al DSConcave ", "l");
          }

          else{
            legend->AddEntry(h_Helium_region1,    "^{4}He USCap ",        "l");
            legend->AddEntry(h_Helium_region2,    "^{4}He Barrel ",       "l");
            legend->AddEntry(h_Helium_region3,    "^{4}He DSCap ",         "l");
            legend->AddEntry(h_Helium_region4,    "^{4}He DSConcave", "l");
            legend->AddEntry(h_Aluminium_region1, "^{27}Al USCap ",        "l");
            legend->AddEntry(h_Aluminium_region2, "^{27}Al Barrel ",       "l");
            legend->AddEntry(h_Aluminium_region3, "^{27}Al DSCap ",         "l");
            legend->AddEntry(h_Aluminium_region4, "^{27}Al DSConcave ", "l");
          }

          //legend->AddEntry(h_Carbon_Combined, "C: ",    "l");
          //legend->AddEntry(h_Iron_Combined,   "Fe: ",   "l");
          //legend->AddEntry(h_Lead_Combined,   "Pb: ",   "l");
          legend->AddEntry(h_Other_Combined,  "Other","l");
          legend->SetTextSize(0.025);
          legend->SetTextFont(42);
          legend->Draw();
          text->SetTextSize(0.02);
          text->SetTextColor(kBlack);
        if (ind != 0 &&  FitType== 1){
        int nPars = 4;
  //      std::cout<<"making Fit info" <<  std::endl;
        //std::cout<<"ChiSq_before_fit[0] = "<< ChiSq_before_fit[0]<<std::endl;
//          std::cout<<"ChiSq_after_fit[0] = "<< plot_chisq<<std::endl;

        double xplace = .2;
        double yplace = 0.80;
        text->DrawLatex(xplace, yplace, Form("Fit Results with %d points, %d pars", nPoints, nPars));
        yplace-=.02;
        text->DrawLatex(xplace, yplace , Form("Before Fit #chi^{2} = %3.2f", ChiSqrt));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("Before Fit #chi^{2}/dof = %3.2f", ChiSqrt/(nPoints-nPars)));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2} = %3.2f", plot_chisq));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2}/dof = %3.2f", plot_chisq/(double)(nPoints-nPars)));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{USCap wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[0], err_Aluminium[0]));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{Barrel wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[1], err_Aluminium[1]));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{DSCap wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[2], err_Aluminium[2]));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{DSConcave  wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[3], err_Aluminium[3]));
        yplace-=.02;
        ChiSqrtAfter = plot_chisq;

        }
        else if(ind != 0 && FitType == 2){
        int nPars = 4;
          //std::cout<<"ChiSq_before_fit[0] = "<< ChiSq_before_fit[0]<<std::endl;

          text->SetNDC();
          double xplace = .2;
          double yplace = 0.80;
          text->DrawLatex(xplace, yplace, Form("Fit Results with %d points, %d pars", nPoints, nPars));
          yplace-=.02;
          text->DrawLatex(xplace, yplace , Form("Before Fit #chi^{2} = %3.2f", ChiSqrt));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("Before Fit #chi^{2}/dof = %3.2f", ChiSqrt/(nPoints-nPars)));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2} = %3.2f", plot_chisq));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2}/dof = %3.2f", plot_chisq/(double)(nPoints-nPars)));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("#color[4]{USCap wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[0], err_Aluminium[0]));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("#color[4]{Barrel wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[1], err_Aluminium[1]));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("#color[4]{DSCap wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[2], err_Aluminium[2]));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("#color[4]{DSConcave  wgt(He) = %3.2f #pm %3.2f}", wgt_Aluminium[3], err_Aluminium[3]));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("#color[4]{USCap wgt(He) = %3.2f #pm %3.2f}", wgt_Helium[0], err_Helium[0]));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("#color[4]{barrel wgt(He) = %3.2f #pm %3.2f}", wgt_Helium[1], err_Helium[1]));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("#color[4]{DSCap wgt(He) = %3.2f #pm %3.2f}", wgt_Helium[2], err_Helium[2]));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("#color[4]{DSConcave  wgt(He) = %3.2f #pm %3.2f}", wgt_Helium[3], err_Helium[3]));

          ChiSqrtAfter = plot_chisq;

        }
        else if(ind != 0 && FitType == 3){
        int nPars = 4;
        double xplace = .2;
        double yplace = 0.80;
        text->DrawLatex(xplace, yplace, Form("Fit Results with %d points, %d pars", nPoints, nPars));
        yplace-=.02;
        text->DrawLatex(xplace, yplace ,Form("Before Fit #chi^{2} = %3.2f", ChiSqrt));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("Before Fit #chi^{2}/dof = %3.2f", ChiSqrt/(nPoints-nPars)));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2} = %3.2f", plot_chisq));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2}/dof = %3.2f", plot_chisq/(double)(nPoints-nPars)));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{XCenter wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[0], err_Aluminium[0]));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{XLeftShelf wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[1], err_Aluminium[1]));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{XRightShelf wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[2], err_Aluminium[2]));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{XoutsideEdges cap wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[3], err_Aluminium[3]));
        yplace-=.02;
        ChiSqrtAfter = plot_chisq;

        }
        else if(ind != 0 && FitType == 4){
        int nPars = 4;
        double xplace = .2;
        double yplace = 0.80;
        text->DrawLatex(xplace, yplace, Form("Fit Results with %d points, %d pars", nPoints, nPars));
        yplace-=.02;
        text->DrawLatex(xplace, yplace ,Form("Before Fit #chi^{2} = %3.2f", ChiSqrt));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("Before Fit #chi^{2}/dof = %3.2f", ChiSqrt/(nPoints-nPars)));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2} = %3.2f", plot_chisq));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2}/dof = %3.2f", plot_chisq/(double)(nPoints-nPars)));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{XCenter wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[0], err_Aluminium[0]));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{XLeftShelf wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[1], err_Aluminium[1]));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{XRightShelf wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[2], err_Aluminium[2]));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{DSConcave  wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[3], err_Aluminium[3]));
        yplace-=.02;
        ChiSqrtAfter = plot_chisq;

        }


        delete text;
        plotter->AddHistoTitle(Hist_title.c_str(),.04);
        plotter->WritePreliminary("TL", .025, 0, 0, false);
        double y2_arrow_max = hist_max *1.1;
        plotter->AddCutArrow(cut_location, y1_arrow,  y2_arrow_max,  arrow_length, "R");
        // Plot Lower Plot: Data vs MC Ratio
        c->cd(); // Go back to default Canvas before creating 2nd Pad
        //TPad *pad2 = new TPad("pad2", "pad2", 0.05, 0.05, 1, 0.3);
        //pad2->SetTopMargin(0);
        //pad2->SetBottomMargin(0.2);
        c->Modified();
        TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
        pad2->SetTopMargin(0);
        pad2->SetBottomMargin(0.2);
        pad2->SetGridx(); // vertical grid
        pad2->Draw();
        pad2->cd();

        // Calculate the Ratio

        //h_data_mc_ratio->Draw("HIST");
        plotter->axis_title_size_x = 0.1;
        plotter->axis_title_offset_y = .4;
        plotter->axis_title_offset_x = 1.35;
        plotter->axis_title_size_y = 0.12;
        plotter->axis_label_size = 0.1;
        plotter->axis_maximum = 2.5;
        plotter->axis_minimum = .5;

        plotter->DrawDataMCRatio(data, mc_total, 1.0, false, false , -.5, 2, "#frac{Data}{MC}", false);
        // Add Ratio = 1 Line
        TLine ratio_1;
        ratio_1.SetLineWidth(2);
        ratio_1.SetLineStyle(7);
        ratio_1.SetLineColor(kBlue);
        double line_min = h_data_Combined->GetBinLowEdge(1);
        double line_max = h_data_Combined->GetBinLowEdge(h_data_Combined->GetNbinsX()+1);
        ratio_1.DrawLine(line_min,1,line_max,1);
        // Plot Output
        c->Update();
        c->cd();
        c->Print(pdf_label.c_str(),"pdf");

        delete plotter;
        delete legend;
        delete pad1;
        delete pad2;
        delete c;
        delete data;
        delete mc_total;
        delete h_data_Combined;
        delete h_Helium_region1;
        delete h_Aluminium_region1;
        delete h_Carbon_Combined;
        delete h_Iron_Combined;
        delete h_Lead_Combined;
        delete h_Other_Combined;
        delete h_data_region2;
        delete h_Helium_region2;
        delete h_Aluminium_region2;
        delete h_Carbon_region2;
        delete h_Iron_region2;
        delete h_Lead_region2;
        delete h_Other_region2;
        delete h_data_region3;
        delete h_Helium_region3;
        delete h_Aluminium_region3;
        delete h_Carbon_region3;
        delete h_Iron_region3;
        delete h_Lead_region3;
        delete h_Other_region3;
        delete h_data_region4;
        delete h_Helium_region4;
        delete h_Aluminium_region4;
        delete h_Carbon_region4;
        delete h_Iron_region4;
        delete h_Lead_region4;
        delete h_Other_region4;
      }


////////
void Helium_3CryoRegionsSideBandTool::Plot_regions_noData(std::string pdf_label, int ind, double POT_ratio,
  MnvH1D* mc_total_region1, MnvH1D* Helium_region1, MnvH1D* Aluminium_region1, MnvH1D* Carbon_region1,
  MnvH1D* Iron_region1, MnvH1D* Lead_region1, MnvH1D* Other_region1,

  MnvH1D* mc_total_region2, MnvH1D* Helium_region2, MnvH1D* Aluminium_region2, MnvH1D* Carbon_region2,
  MnvH1D* Iron_region2, MnvH1D* Lead_region2, MnvH1D* Other_region2,

  MnvH1D* mc_total_region3, MnvH1D* Helium_region3, MnvH1D* Aluminium_region3, MnvH1D* Carbon_region3,
  MnvH1D* Iron_region3, MnvH1D* Lead_region3, MnvH1D* Other_region3,

  MnvH1D* mc_total_region4, MnvH1D* Helium_region4, MnvH1D* Aluminium_region4, MnvH1D* Carbon_region4,
  MnvH1D* Iron_region4, MnvH1D* Lead_region4, MnvH1D* Other_region4,

  std::string Hist_title, std::string xaxislabel)
  {

               bool doArea_norm = true;


              //std::cout<<"Ploting type: Resolution Combined CryoRegions  "<<std::endl;

              //PlotUtils::MnvPlotter* plotter= new mnvPlotter();
               MnvPlotter* plotter = new MnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
              //plotter(PlotUtils::kCCInclusiveHeliumStyle);
              MnvH1D *mc_total = (PlotUtils::MnvH1D*)Helium_region1->Clone("mc_total");
              mc_total->Add(Aluminium_region1 );
              mc_total->Add(Carbon_region1);
              mc_total->Add(Iron_region1 );
              mc_total->Add(Lead_region1 );
              mc_total->Add(Other_region1);
              mc_total->Add(Helium_region2 );
              mc_total->Add(Aluminium_region2 );
              mc_total->Add(Carbon_region2);
              mc_total->Add(Iron_region2 );
              mc_total->Add(Lead_region2 );
              mc_total->Add(Other_region2);
              mc_total->Add(Helium_region3 );
              mc_total->Add(Aluminium_region3 );
              mc_total->Add(Carbon_region3);
              mc_total->Add(Iron_region3 );
              mc_total->Add(Lead_region3 );
              mc_total->Add(Other_region3);
              mc_total->Add(Helium_region4 );
              mc_total->Add(Aluminium_region4 );
              mc_total->Add(Carbon_region4);
              mc_total->Add(Iron_region4 );
              mc_total->Add(Lead_region4 );
              mc_total->Add(Other_region4);
              mc_total->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));


              TH1D* h_Helium_region1 = new TH1D(Helium_region1->GetCVHistoWithError());
              TH1D* h_Aluminium_region1 = new TH1D(Aluminium_region1->GetCVHistoWithError());

              TH1D* h_Carbon_Combined = new TH1D(Carbon_region1->GetCVHistoWithError());
              TH1D* h_Iron_Combined = new TH1D(Iron_region1->GetCVHistoWithError());
              TH1D* h_Lead_Combined = new TH1D(Lead_region1->GetCVHistoWithError());
              TH1D* h_Other_Combined = new TH1D(Other_region1->GetCVHistoWithError());

              TH1D* h_Helium_region2 = new TH1D(Helium_region2->GetCVHistoWithError());
              TH1D* h_Aluminium_region2 = new TH1D(Aluminium_region2->GetCVHistoWithError());
              TH1D* h_Carbon_region2 = new TH1D(Carbon_region2->GetCVHistoWithError());
              TH1D* h_Iron_region2 = new TH1D(Iron_region2->GetCVHistoWithError());
              TH1D* h_Lead_region2 = new TH1D(Lead_region2->GetCVHistoWithError());
              TH1D* h_Other_region2 = new TH1D(Other_region2->GetCVHistoWithError());

              h_Carbon_Combined->Add(h_Carbon_region2);
              h_Iron_Combined->Add(h_Iron_region2);
              h_Lead_Combined->Add(h_Lead_region2);
              h_Other_Combined->Add(h_Other_region2);

              TH1D* h_Helium_region3 = new TH1D(Helium_region3->GetCVHistoWithError());
              TH1D* h_Aluminium_region3 = new TH1D(Aluminium_region3->GetCVHistoWithError());

              TH1D* h_Carbon_region3 = new TH1D(Carbon_region3->GetCVHistoWithError());
              TH1D* h_Iron_region3 = new TH1D(Iron_region3->GetCVHistoWithError());
              TH1D* h_Lead_region3 = new TH1D(Lead_region3->GetCVHistoWithError());
              TH1D* h_Other_region3 = new TH1D(Other_region3->GetCVHistoWithError());

              h_Carbon_Combined->Add(h_Carbon_region3);
              h_Iron_Combined->Add(h_Iron_region3);
              h_Lead_Combined->Add(h_Lead_region3);
              h_Other_Combined->Add(h_Other_region3);


              TH1D* h_Helium_region4 = new TH1D(Helium_region4->GetCVHistoWithError());
              TH1D* h_Aluminium_region4 = new TH1D(Aluminium_region4->GetCVHistoWithError());

              TH1D* h_Carbon_region4 = new TH1D(Carbon_region4->GetCVHistoWithError());
              TH1D* h_Iron_region4 = new TH1D(Iron_region4->GetCVHistoWithError());
              TH1D* h_Lead_region4 = new TH1D(Lead_region4->GetCVHistoWithError());
              TH1D* h_Other_region4 = new TH1D(Other_region4->GetCVHistoWithError());


              h_Carbon_Combined->Add(h_Carbon_region4);
              h_Iron_Combined->Add(h_Iron_region4);
              h_Lead_Combined->Add(h_Lead_region4);
              h_Other_Combined->Add(h_Other_region4);

              ColorHists(h_Carbon_Combined, h_Iron_Combined, h_Lead_Combined,  h_Other_Combined);
              Color_HeliumHists(h_Helium_region1, h_Helium_region2, h_Helium_region3, h_Helium_region4);
              Color_AluminiumHists(h_Aluminium_region1, h_Aluminium_region2, h_Aluminium_region3, h_Aluminium_region4);

              // MC Total depend on the Modification
              //      If Raws - take the mc_total directly
              //      If Modified - Add all mc models;

              TH1D* h_mc_total;
              if (ind == 0){
                  /*h_mc_total = new TH1D(mc_total_region1->GetCVHistoWithError());
                  h_mc_total->Add(mc_total_region2);
                  h_mc_total->Add(mc_total_region3);
                  h_mc_total->Add(mc_total_region4);*/

                  h_mc_total = (TH1D*)mc_total->Clone("h_mc_total");
                  //h_mc_total->Add(h_Helium_region2);
                  //h_mc_total->Add(h_Helium_region3);
                  //h_mc_total->Add(h_Helium_region4);

                  //h_mc_total->Add(h_Aluminium_region1);
                  //h_mc_total->Add(h_Aluminium_region2);
                  //h_mc_total->Add(h_Aluminium_region3);
                  //h_mc_total->Add(h_Aluminium_region4);

                  //h_mc_total->Add(h_Carbon_Combined);
                  //h_mc_total->Add(h_Iron_Combined);
                  //h_mc_total->Add(h_Lead_Combined);
                  //h_mc_total->Add(h_Other_Combined);
              }
              else{

            h_mc_total = (TH1D*)mc_total->Clone("h_mc_total");
              //  h_mc_total->Add(h_Helium_region2);
              //  h_mc_total->Add(h_Helium_region3);
              //  h_mc_total->Add(h_Helium_region4);

              //  h_mc_total->Add(h_Aluminium_region1);
              //  h_mc_total->Add(h_Aluminium_region2);
              //  h_mc_total->Add(h_Aluminium_region3);
              //  h_mc_total->Add(h_Aluminium_region4);

              //  h_mc_total->Add(h_Carbon_Combined);
              //  h_mc_total->Add(h_Iron_Combined);
              //  h_mc_total->Add(h_Lead_Combined);
              //  h_mc_total->Add(h_Other_Combined);
              }
              if(doArea_norm == true){

                int endBin = h_mc_total->GetNbinsX();
                double Area = h_mc_total->Integral(1,endBin);
                double areascaler = 1.0 / Area;
                h_mc_total->Scale(areascaler);

                h_Helium_region1->Scale(areascaler);
                h_Aluminium_region1->Scale(areascaler);

                h_Helium_region2->Scale(areascaler);
                h_Aluminium_region2->Scale(areascaler);

                h_Helium_region3->Scale(areascaler);
                h_Aluminium_region3->Scale(areascaler);

                h_Helium_region4->Scale(areascaler);
                h_Aluminium_region4->Scale(areascaler);

                h_Carbon_Combined->Scale(areascaler);
                h_Iron_Combined->Scale(areascaler);
                h_Lead_Combined->Scale(areascaler);
                h_Other_Combined->Scale(areascaler);


              }


              std::string yaxis;
              double RMS_value = h_mc_total->GetRMS();

              if(MakeBinWidth==true){

                h_mc_total->Scale(1.0, "width");

                h_Helium_region1->Scale(1.0, "width");
                h_Aluminium_region1->Scale(1.0, "width");

                h_Helium_region2->Scale(1.0, "width");
                h_Aluminium_region2->Scale(1.0, "width");

                h_Helium_region3->Scale(1.0, "width");
                h_Aluminium_region3->Scale(1.0, "width");

                h_Helium_region4->Scale(1.0, "width");
                h_Aluminium_region4->Scale(1.0, "width");

                h_Carbon_Combined->Scale(1.0, "width");
                h_Iron_Combined->Scale(1.0, "width");
                h_Lead_Combined->Scale(1.0, "width");
                h_Other_Combined->Scale(1.0, "width");

                double binwidth_title = h_mc_total -> GetBinWidth(3);
                yaxis = Form("NEvents / %.2f",binwidth_title);
                if(doArea_norm == true){yaxis = Form("AreaNormalized NEvents / %.2f",binwidth_title);}
              //  std::cout<< "yaxis = "<< yaxis<<std::endl;
                //std::cout<<"Finished Bin width Norm"<<std::endl;

              }
              else{
                yaxis = "NEvents";
              //  std::cout<<"FInished Bin NOT width Norm"<<std::endl;
              if(doArea_norm == true){yaxis =  "AreaNormalized NEvents";}
              }

              // ------------------------------------------------------------------------
              // Unique Plot for Single Error Band, Single Universe
              //      Comment this section out
              // ------------------------------------------------------------------------


              // Create Canvas and Divide it into two
              TCanvas* c = new TCanvas("c","c",800, 800);
              //TCanvas cE("cE","cE", 800, 800);

              THStack* hs = new THStack("hs","");
              h_Helium_region1->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
              hs->Add(h_Helium_region1);
              hs->Add(h_Helium_region2);
              hs->Add(h_Helium_region3);
              hs->Add(h_Helium_region4);
              hs->Add(h_Aluminium_region1);
              hs->Add(h_Aluminium_region2);
              hs->Add(h_Aluminium_region3);
              hs->Add(h_Aluminium_region4);
              hs->Add(h_Carbon_Combined);
              hs->Add(h_Iron_Combined);
              hs->Add(h_Lead_Combined);
              hs->Add(h_Other_Combined);

              //std::cout<<"Finished adding hist to hs II"<<std::endl;

              // Styling
              hs->Draw("HIST");
              hs->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
              hs->GetYaxis()->SetTitle(Form("%s",yaxis.c_str()));
              hs->GetYaxis()->SetTitleFont(62);
              hs->GetYaxis()->SetTitleSize(0.06);
              hs->GetXaxis()->SetTitleSize(0.06);
              hs->GetXaxis()->CenterTitle();
              //hs->GetYaxis()->SetTitleOffset(1.2);
              hs->GetYaxis()->SetLabelFont(42);
              hs->GetYaxis()->SetLabelSize(0.05);
              hs->GetXaxis()->SetLabelSize(0.04);

              double hist_max = h_mc_total->GetMaximum();
              //std::cout<<"GetMaximum() =  "<<hist_max<<std::endl;
              hs->SetMaximum(hist_max * 5.5);
              hs->SetMinimum(-1);
              c->Modified();

              //std::cout<<"Finshed Drawing Hist "<<std::endl;

              // Add Legend
              TLegend *legend = new TLegend(0.75,0.55,0.91,0.92);
              // Add Weights as Text to Modified Plot
              // Add Plot-ChiSq
              TLatex* text = new TLatex;
              text->SetNDC();
              text->SetTextSize(0.03);
              text->SetTextColor(kBlue);

              legend->AddEntry(h_Helium_region1,    "^{4}He USCap ",        "f");
              legend->AddEntry(h_Helium_region2,    "^{4}He Barrel ",       "f");
              legend->AddEntry(h_Helium_region3,    "^{4}He DSCap ",         "f");
              legend->AddEntry(h_Helium_region4,    "^{4}He DSConcave ", "f");
              legend->AddEntry(h_Aluminium_region1, "^{27}Al USCap ",        "f");
              legend->AddEntry(h_Aluminium_region2, "^{27}Al Barrel ",       "f");
              legend->AddEntry(h_Aluminium_region3, "^{27}Al DSCap ",         "f");
              legend->AddEntry(h_Aluminium_region4, "^{27}Al DSConcave ", "f");

              legend->AddEntry(h_Carbon_Combined, "C: ",    "f");
              legend->AddEntry(h_Iron_Combined,   "Fe: ",   "f");
              legend->AddEntry(h_Lead_Combined,   "Pb: ",   "f");
              legend->AddEntry(h_Other_Combined,  "Other","f");

              legend->SetTextSize(0.025);
              legend->SetTextFont(42);
              legend->Draw();

              //std::cout<<"FInished Drawing legend"<<std::endl;



              text->DrawLatex(0.2, 0.85, Form("RMS = %3.2f", RMS_value));
              //text->DrawLatex(0.2, 0.82, Form("Plot #chi^{2}/dof = %3.2f", plot_chisq / (double) nPoints));
              delete text;
              plotter->AddHistoTitle(Hist_title.c_str(),.04);
              plotter->WritePreliminary("TL", .025, 0, 0, false);
              c->Modified();
              c->Print(pdf_label.c_str(),"pdf");

              delete legend;
              delete hs;
              delete c;

              delete mc_total;

              delete h_Helium_region1;
              delete h_Aluminium_region1;
              delete h_Carbon_Combined;
              delete h_Iron_Combined;
              delete h_Lead_Combined;
              delete h_Other_Combined;

              delete h_Helium_region2;
              delete h_Aluminium_region2;
              delete h_Carbon_region2;
              delete h_Iron_region2;
              delete h_Lead_region2;
              delete h_Other_region2;

              delete h_Helium_region3;
              delete h_Aluminium_region3;
              delete h_Carbon_region3;
              delete h_Iron_region3;
              delete h_Lead_region3;
              delete h_Other_region3;

              delete h_Helium_region4;
              delete h_Aluminium_region4;
              delete h_Carbon_region4;
              delete h_Iron_region4;
              delete h_Lead_region4;
              delete h_Other_region4;
            }

double Helium_3CryoRegionsSideBandTool::ChiSqrt(
  MnvH1D* data_Region1, MnvH1D* Helium_Region1,
  MnvH1D* Aluminium_Region1, MnvH1D* Carbon_Region1,
  MnvH1D* Iron_Region1, MnvH1D* Lead_Region1, MnvH1D* Other_Region1,

  MnvH1D* data_Region2, MnvH1D* Helium_Region2, MnvH1D* Aluminium_Region2, MnvH1D* Carbon_Region2,
  MnvH1D* Iron_Region2, MnvH1D* Lead_Region2, MnvH1D* Other_Region2,

  MnvH1D* data_Region3, MnvH1D* Helium_Region3, MnvH1D* Aluminium_Region3, MnvH1D* Carbon_Region3,
  MnvH1D* Iron_Region3, MnvH1D* Lead_Region3, MnvH1D* Other_Region3,

  MnvH1D* data_Region4, MnvH1D* Helium_Region4, MnvH1D* Aluminium_Region4,
  MnvH1D* Carbon_Region4,
  MnvH1D* Iron_Region4, MnvH1D* Lead_Region4, MnvH1D* Other_Region4)
  {

    TH1D* h_data_Combined = new TH1D(data_Region1->GetCVHistoWithError());
    TH1D* h_Helium_Region1 = new TH1D(Helium_Region1->GetCVHistoWithError());
    TH1D* h_Aluminium_Region1 = new TH1D(Aluminium_Region1->GetCVHistoWithError());

    TH1D* h_Carbon_Combined = new TH1D(Carbon_Region1->GetCVHistoWithError());
    TH1D* h_Iron_Combined = new TH1D(Iron_Region1->GetCVHistoWithError());
    TH1D* h_Lead_Combined = new TH1D(Lead_Region1->GetCVHistoWithError());
    TH1D* h_Other_Combined = new TH1D(Other_Region1->GetCVHistoWithError());

    TH1D* h_data_Region2 = new TH1D(data_Region2->GetCVHistoWithError());
    TH1D* h_Helium_Region2 = new TH1D(Helium_Region2->GetCVHistoWithError());
    TH1D* h_Aluminium_Region2 = new TH1D(Aluminium_Region2->GetCVHistoWithError());
    TH1D* h_Carbon_Region2 = new TH1D(Carbon_Region2->GetCVHistoWithError());
    TH1D* h_Iron_Region2 = new TH1D(Iron_Region2->GetCVHistoWithError());
    TH1D* h_Lead_Region2 = new TH1D(Lead_Region2->GetCVHistoWithError());
    TH1D* h_Other_Region2 = new TH1D(Other_Region2->GetCVHistoWithError());

    h_Carbon_Combined->Add(h_Carbon_Region2);
    h_Iron_Combined->Add(h_Iron_Region2);
    h_Lead_Combined->Add(h_Lead_Region2);
    h_Other_Combined->Add(h_Other_Region2);
    h_data_Combined->Add(h_data_Region2);
    TH1D* h_data_Region3 = new TH1D(data_Region3->GetCVHistoWithError());
    TH1D* h_Helium_Region3 = new TH1D(Helium_Region3->GetCVHistoWithError());
    TH1D* h_Aluminium_Region3 = new TH1D(Aluminium_Region3->GetCVHistoWithError());

    TH1D* h_Carbon_Region3 = new TH1D(Carbon_Region3->GetCVHistoWithError());
    TH1D* h_Iron_Region3 = new TH1D(Iron_Region3->GetCVHistoWithError());
    TH1D* h_Lead_Region3 = new TH1D(Lead_Region3->GetCVHistoWithError());
    TH1D* h_Other_Region3 = new TH1D(Other_Region3->GetCVHistoWithError());

    h_Carbon_Combined->Add(h_Carbon_Region3);
    h_Iron_Combined->Add(h_Iron_Region3);
    h_Lead_Combined->Add(h_Lead_Region3);
    h_Other_Combined->Add(h_Other_Region3);
    h_data_Combined->Add(h_data_Region3);
    TH1D* h_data_Region4 = new TH1D(data_Region4->GetCVHistoWithError());
    TH1D* h_Helium_Region4 = new TH1D(Helium_Region4->GetCVHistoWithError());
    TH1D* h_Aluminium_Region4 = new TH1D(Aluminium_Region4->GetCVHistoWithError());

    TH1D* h_Carbon_Region4 = new TH1D(Carbon_Region4->GetCVHistoWithError());
    TH1D* h_Iron_Region4 = new TH1D(Iron_Region4->GetCVHistoWithError());
    TH1D* h_Lead_Region4 = new TH1D(Lead_Region4->GetCVHistoWithError());
    TH1D* h_Other_Region4 = new TH1D(Other_Region4->GetCVHistoWithError());


    h_Carbon_Combined->Add(h_Carbon_Region4);
    h_Iron_Combined->Add(h_Iron_Region4);
    h_Lead_Combined->Add(h_Lead_Region4);
    h_Other_Combined->Add(h_Other_Region4);
    h_data_Combined->Add(h_data_Region4);

    double plot_chisq = calc_ChiSq(h_data_Combined,
    h_Helium_Region1,
    h_Helium_Region2,
    h_Helium_Region3,
    h_Helium_Region4,
    h_Aluminium_Region1,
    h_Aluminium_Region2,
    h_Aluminium_Region3,
    h_Aluminium_Region4,
    h_Carbon_Combined, h_Lead_Combined, h_Iron_Combined, h_Other_Combined);

    delete h_data_Combined;
    delete h_Helium_Region1;
    delete h_Aluminium_Region1;
    delete h_Carbon_Combined;
    delete h_Iron_Combined;
    delete h_Lead_Combined;
    delete h_Other_Combined;
    delete h_data_Region2;
    delete h_Helium_Region2;
    delete h_Aluminium_Region2;
    delete h_Carbon_Region2;
    delete h_Iron_Region2;
    delete h_Lead_Region2;
    delete h_Other_Region2;
    delete h_data_Region3;
    delete h_Helium_Region3;
    delete h_Aluminium_Region3;
    delete h_Carbon_Region3;
    delete h_Iron_Region3;
    delete h_Lead_Region3;
    delete h_Other_Region3;
    delete h_data_Region4;
    delete h_Helium_Region4;
    delete h_Aluminium_Region4;
    delete h_Carbon_Region4;
    delete h_Iron_Region4;
    delete h_Lead_Region4;
    delete h_Other_Region4;



    return plot_chisq;

    }

    double Helium_3CryoRegionsSideBandTool::LogChiSqrt(
      MnvH1D* data_Region1, MnvH1D* Helium_Region1,
      MnvH1D* Aluminium_Region1, MnvH1D* Carbon_Region1,
      MnvH1D* Iron_Region1, MnvH1D* Lead_Region1, MnvH1D* Other_Region1,

      MnvH1D* data_Region2, MnvH1D* Helium_Region2, MnvH1D* Aluminium_Region2, MnvH1D* Carbon_Region2,
      MnvH1D* Iron_Region2, MnvH1D* Lead_Region2, MnvH1D* Other_Region2,

      MnvH1D* data_Region3, MnvH1D* Helium_Region3, MnvH1D* Aluminium_Region3, MnvH1D* Carbon_Region3,
      MnvH1D* Iron_Region3, MnvH1D* Lead_Region3, MnvH1D* Other_Region3,

      MnvH1D* data_Region4, MnvH1D* Helium_Region4, MnvH1D* Aluminium_Region4,
      MnvH1D* Carbon_Region4,
      MnvH1D* Iron_Region4, MnvH1D* Lead_Region4, MnvH1D* Other_Region4)
      {

        TH1D* h_data_Combined = new TH1D(data_Region1->GetCVHistoWithError());
        TH1D* h_Helium_Region1 = new TH1D(Helium_Region1->GetCVHistoWithError());
        TH1D* h_Aluminium_Region1 = new TH1D(Aluminium_Region1->GetCVHistoWithError());

        TH1D* h_Carbon_Combined = new TH1D(Carbon_Region1->GetCVHistoWithError());
        TH1D* h_Iron_Combined = new TH1D(Iron_Region1->GetCVHistoWithError());
        TH1D* h_Lead_Combined = new TH1D(Lead_Region1->GetCVHistoWithError());
        TH1D* h_Other_Combined = new TH1D(Other_Region1->GetCVHistoWithError());

        TH1D* h_data_Region2 = new TH1D(data_Region2->GetCVHistoWithError());
        TH1D* h_Helium_Region2 = new TH1D(Helium_Region2->GetCVHistoWithError());
        TH1D* h_Aluminium_Region2 = new TH1D(Aluminium_Region2->GetCVHistoWithError());
        TH1D* h_Carbon_Region2 = new TH1D(Carbon_Region2->GetCVHistoWithError());
        TH1D* h_Iron_Region2 = new TH1D(Iron_Region2->GetCVHistoWithError());
        TH1D* h_Lead_Region2 = new TH1D(Lead_Region2->GetCVHistoWithError());
        TH1D* h_Other_Region2 = new TH1D(Other_Region2->GetCVHistoWithError());

        h_Carbon_Combined->Add(h_Carbon_Region2);
        h_Iron_Combined->Add(h_Iron_Region2);
        h_Lead_Combined->Add(h_Lead_Region2);
        h_Other_Combined->Add(h_Other_Region2);
        h_data_Combined->Add(h_data_Region2);
        TH1D* h_data_Region3 = new TH1D(data_Region3->GetCVHistoWithError());
        TH1D* h_Helium_Region3 = new TH1D(Helium_Region3->GetCVHistoWithError());
        TH1D* h_Aluminium_Region3 = new TH1D(Aluminium_Region3->GetCVHistoWithError());

        TH1D* h_Carbon_Region3 = new TH1D(Carbon_Region3->GetCVHistoWithError());
        TH1D* h_Iron_Region3 = new TH1D(Iron_Region3->GetCVHistoWithError());
        TH1D* h_Lead_Region3 = new TH1D(Lead_Region3->GetCVHistoWithError());
        TH1D* h_Other_Region3 = new TH1D(Other_Region3->GetCVHistoWithError());

        h_Carbon_Combined->Add(h_Carbon_Region3);
        h_Iron_Combined->Add(h_Iron_Region3);
        h_Lead_Combined->Add(h_Lead_Region3);
        h_Other_Combined->Add(h_Other_Region3);
        h_data_Combined->Add(h_data_Region3);
        TH1D* h_data_Region4 = new TH1D(data_Region4->GetCVHistoWithError());
        TH1D* h_Helium_Region4 = new TH1D(Helium_Region4->GetCVHistoWithError());
        TH1D* h_Aluminium_Region4 = new TH1D(Aluminium_Region4->GetCVHistoWithError());

        TH1D* h_Carbon_Region4 = new TH1D(Carbon_Region4->GetCVHistoWithError());
        TH1D* h_Iron_Region4 = new TH1D(Iron_Region4->GetCVHistoWithError());
        TH1D* h_Lead_Region4 = new TH1D(Lead_Region4->GetCVHistoWithError());
        TH1D* h_Other_Region4 = new TH1D(Other_Region4->GetCVHistoWithError());


        h_Carbon_Combined->Add(h_Carbon_Region4);
        h_Iron_Combined->Add(h_Iron_Region4);
        h_Lead_Combined->Add(h_Lead_Region4);
        h_Other_Combined->Add(h_Other_Region4);
        h_data_Combined->Add(h_data_Region4);

        double plot_chisq = calc_LogChiSq(h_data_Combined,
        h_Helium_Region1,
        h_Helium_Region2,
        h_Helium_Region3,
        h_Helium_Region4,
        h_Aluminium_Region1,
        h_Aluminium_Region2,
        h_Aluminium_Region3,
        h_Aluminium_Region4,
        h_Carbon_Combined, h_Lead_Combined, h_Iron_Combined, h_Other_Combined);

        delete h_data_Combined;
        delete h_Helium_Region1;
        delete h_Aluminium_Region1;
        delete h_Carbon_Combined;
        delete h_Iron_Combined;
        delete h_Lead_Combined;
        delete h_Other_Combined;
        delete h_data_Region2;
        delete h_Helium_Region2;
        delete h_Aluminium_Region2;
        delete h_Carbon_Region2;
        delete h_Iron_Region2;
        delete h_Lead_Region2;
        delete h_Other_Region2;
        delete h_data_Region3;
        delete h_Helium_Region3;
        delete h_Aluminium_Region3;
        delete h_Carbon_Region3;
        delete h_Iron_Region3;
        delete h_Lead_Region3;
        delete h_Other_Region3;
        delete h_data_Region4;
        delete h_Helium_Region4;
        delete h_Aluminium_Region4;
        delete h_Carbon_Region4;
        delete h_Iron_Region4;
        delete h_Lead_Region4;
        delete h_Other_Region4;


        return plot_chisq;

        }

double Helium_3CryoRegionsSideBandTool::GetChiSqt_X(Helium3SideBand &sb_upstreamCap, Helium3SideBand &sb_Barrel,
  Helium3SideBand &sb_downstreamCap, Helium3SideBand &sb_downstreamConcaveCap , int ind)
  {

  double ChiSqrt_return =   ChiSqrt(sb_upstreamCap.MnvH1D_Vertex_X_data, sb_upstreamCap.MnvH1D_Vertex_X_Helium[ind], sb_upstreamCap.MnvH1D_Vertex_X_Aluminium[ind], sb_upstreamCap.MnvH1D_Vertex_X_Carbon[ind],
                   sb_upstreamCap.MnvH1D_Vertex_X_Iron[ind], sb_upstreamCap.MnvH1D_Vertex_X_Lead[ind], sb_upstreamCap.MnvH1D_Vertex_X_Other[ind],

                   sb_Barrel.MnvH1D_Vertex_X_data, sb_Barrel.MnvH1D_Vertex_X_Helium[ind], sb_Barrel.MnvH1D_Vertex_X_Aluminium[ind], sb_Barrel.MnvH1D_Vertex_X_Carbon[ind],
                   sb_Barrel.MnvH1D_Vertex_X_Iron[ind], sb_Barrel.MnvH1D_Vertex_X_Lead[ind], sb_Barrel.MnvH1D_Vertex_X_Other[ind],

                   sb_downstreamCap.MnvH1D_Vertex_X_data, sb_downstreamCap.MnvH1D_Vertex_X_Helium[ind], sb_downstreamCap.MnvH1D_Vertex_X_Aluminium[ind], sb_downstreamCap.MnvH1D_Vertex_X_Carbon[ind],
                   sb_downstreamCap.MnvH1D_Vertex_X_Iron[ind], sb_downstreamCap.MnvH1D_Vertex_X_Lead[ind], sb_downstreamCap.MnvH1D_Vertex_X_Other[ind],

                   sb_downstreamConcaveCap.MnvH1D_Vertex_X_data, sb_downstreamConcaveCap.MnvH1D_Vertex_X_Helium[ind], sb_downstreamConcaveCap.MnvH1D_Vertex_X_Aluminium[ind],
                   sb_downstreamConcaveCap.MnvH1D_Vertex_X_Carbon[ind],
                   sb_downstreamConcaveCap.MnvH1D_Vertex_X_Iron[ind], sb_downstreamConcaveCap.MnvH1D_Vertex_X_Lead[ind], sb_downstreamConcaveCap.MnvH1D_Vertex_X_Other[ind]);

return ChiSqrt_return;

}

double Helium_3CryoRegionsSideBandTool::GetLogChiSqt_X(Helium3SideBand &sb_upstreamCap, Helium3SideBand &sb_Barrel,
  Helium3SideBand &sb_downstreamCap, Helium3SideBand &sb_downstreamConcaveCap , int ind)
  {

  double ChiSqrt_return =   LogChiSqrt(sb_upstreamCap.MnvH1D_Vertex_X_data,
                                          sb_upstreamCap.MnvH1D_Vertex_X_Helium[ind], sb_upstreamCap.MnvH1D_Vertex_X_Aluminium[ind], sb_upstreamCap.MnvH1D_Vertex_X_Carbon[ind],
                   sb_upstreamCap.MnvH1D_Vertex_X_Iron[ind], sb_upstreamCap.MnvH1D_Vertex_X_Lead[ind], sb_upstreamCap.MnvH1D_Vertex_X_Other[ind],

                   sb_Barrel.MnvH1D_Vertex_X_data, sb_Barrel.MnvH1D_Vertex_X_Helium[ind], sb_Barrel.MnvH1D_Vertex_X_Aluminium[ind], sb_Barrel.MnvH1D_Vertex_X_Carbon[ind],
                   sb_Barrel.MnvH1D_Vertex_X_Iron[ind], sb_Barrel.MnvH1D_Vertex_X_Lead[ind], sb_Barrel.MnvH1D_Vertex_X_Other[ind],

                   sb_downstreamCap.MnvH1D_Vertex_X_data, sb_downstreamCap.MnvH1D_Vertex_X_Helium[ind], sb_downstreamCap.MnvH1D_Vertex_X_Aluminium[ind], sb_downstreamCap.MnvH1D_Vertex_X_Carbon[ind],
                   sb_downstreamCap.MnvH1D_Vertex_X_Iron[ind], sb_downstreamCap.MnvH1D_Vertex_X_Lead[ind], sb_downstreamCap.MnvH1D_Vertex_X_Other[ind],

                   sb_downstreamConcaveCap.MnvH1D_Vertex_X_data, sb_downstreamConcaveCap.MnvH1D_Vertex_X_Helium[ind], sb_downstreamConcaveCap.MnvH1D_Vertex_X_Aluminium[ind],
                   sb_downstreamConcaveCap.MnvH1D_Vertex_X_Carbon[ind],
                   sb_downstreamConcaveCap.MnvH1D_Vertex_X_Iron[ind], sb_downstreamConcaveCap.MnvH1D_Vertex_X_Lead[ind], sb_downstreamConcaveCap.MnvH1D_Vertex_X_Other[ind]);

return ChiSqrt_return;

}



double Helium_3CryoRegionsSideBandTool::GetChiSqt_Y(Helium3SideBand &sb_upstreamCap, Helium3SideBand &sb_Barrel,
  Helium3SideBand &sb_downstreamCap, Helium3SideBand &sb_downstreamConcaveCap , int ind){

  double ChiSqrt_return =   ChiSqrt(sb_upstreamCap.MnvH1D_Vertex_Y_data,
    sb_upstreamCap.MnvH1D_Vertex_Y_Helium[ind],
    sb_upstreamCap.MnvH1D_Vertex_Y_Aluminium[ind],
    sb_upstreamCap.MnvH1D_Vertex_Y_Carbon[ind],
    sb_upstreamCap.MnvH1D_Vertex_Y_Iron[ind],
    sb_upstreamCap.MnvH1D_Vertex_Y_Lead[ind],
    sb_upstreamCap.MnvH1D_Vertex_Y_Other[ind],

    sb_Barrel.MnvH1D_Vertex_Y_data,
    sb_Barrel.MnvH1D_Vertex_Y_Helium[ind],
    sb_Barrel.MnvH1D_Vertex_Y_Aluminium[ind],
    sb_Barrel.MnvH1D_Vertex_Y_Carbon[ind],
    sb_Barrel.MnvH1D_Vertex_Y_Iron[ind],
    sb_Barrel.MnvH1D_Vertex_Y_Lead[ind],
    sb_Barrel.MnvH1D_Vertex_Y_Other[ind],

    sb_downstreamCap.MnvH1D_Vertex_Y_data,
    sb_downstreamCap.MnvH1D_Vertex_Y_Helium[ind],
    sb_downstreamCap.MnvH1D_Vertex_Y_Aluminium[ind],
    sb_downstreamCap.MnvH1D_Vertex_Y_Carbon[ind],
    sb_downstreamCap.MnvH1D_Vertex_Y_Iron[ind],
    sb_downstreamCap.MnvH1D_Vertex_Y_Lead[ind],
    sb_downstreamCap.MnvH1D_Vertex_Y_Other[ind],

    sb_downstreamConcaveCap.MnvH1D_Vertex_Y_data,
    sb_downstreamConcaveCap.MnvH1D_Vertex_Y_Helium[ind],
    sb_downstreamConcaveCap.MnvH1D_Vertex_Y_Aluminium[ind],
    sb_downstreamConcaveCap.MnvH1D_Vertex_Y_Carbon[ind],
    sb_downstreamConcaveCap.MnvH1D_Vertex_Y_Iron[ind],
    sb_downstreamConcaveCap.MnvH1D_Vertex_Y_Lead[ind],
    sb_downstreamConcaveCap.MnvH1D_Vertex_Y_Other[ind]);

return ChiSqrt_return;

}

double Helium_3CryoRegionsSideBandTool::GetLogChiSqt_Y(Helium3SideBand &sb_upstreamCap, Helium3SideBand &sb_Barrel,
  Helium3SideBand &sb_downstreamCap, Helium3SideBand &sb_downstreamConcaveCap , int ind){

  double ChiSqrt_return =   LogChiSqrt(sb_upstreamCap.MnvH1D_Vertex_Y_data,
    sb_upstreamCap.MnvH1D_Vertex_Y_Helium[ind],
    sb_upstreamCap.MnvH1D_Vertex_Y_Aluminium[ind],
    sb_upstreamCap.MnvH1D_Vertex_Y_Carbon[ind],
    sb_upstreamCap.MnvH1D_Vertex_Y_Iron[ind],
    sb_upstreamCap.MnvH1D_Vertex_Y_Lead[ind],
    sb_upstreamCap.MnvH1D_Vertex_Y_Other[ind],

    sb_Barrel.MnvH1D_Vertex_Y_data,
    sb_Barrel.MnvH1D_Vertex_Y_Helium[ind],
    sb_Barrel.MnvH1D_Vertex_Y_Aluminium[ind],
    sb_Barrel.MnvH1D_Vertex_Y_Carbon[ind],
    sb_Barrel.MnvH1D_Vertex_Y_Iron[ind],
    sb_Barrel.MnvH1D_Vertex_Y_Lead[ind],
    sb_Barrel.MnvH1D_Vertex_Y_Other[ind],

    sb_downstreamCap.MnvH1D_Vertex_Y_data,
    sb_downstreamCap.MnvH1D_Vertex_Y_Helium[ind],
    sb_downstreamCap.MnvH1D_Vertex_Y_Aluminium[ind],
    sb_downstreamCap.MnvH1D_Vertex_Y_Carbon[ind],
    sb_downstreamCap.MnvH1D_Vertex_Y_Iron[ind],
    sb_downstreamCap.MnvH1D_Vertex_Y_Lead[ind],
    sb_downstreamCap.MnvH1D_Vertex_Y_Other[ind],

    sb_downstreamConcaveCap.MnvH1D_Vertex_Y_data,
    sb_downstreamConcaveCap.MnvH1D_Vertex_Y_Helium[ind],
    sb_downstreamConcaveCap.MnvH1D_Vertex_Y_Aluminium[ind],
    sb_downstreamConcaveCap.MnvH1D_Vertex_Y_Carbon[ind],
    sb_downstreamConcaveCap.MnvH1D_Vertex_Y_Iron[ind],
    sb_downstreamConcaveCap.MnvH1D_Vertex_Y_Lead[ind],
    sb_downstreamConcaveCap.MnvH1D_Vertex_Y_Other[ind]);

return ChiSqrt_return;

}



double Helium_3CryoRegionsSideBandTool::GetChiSqt_Z(Helium3SideBand &sb_upstreamCap, Helium3SideBand &sb_Barrel,
  Helium3SideBand &sb_downstreamCap, Helium3SideBand &sb_downstreamConcaveCap , int ind){

  double ChiSqrt_return =   ChiSqrt(sb_upstreamCap.MnvH1D_Vertex_Z_data, sb_upstreamCap.MnvH1D_Vertex_Z_Helium[ind], sb_upstreamCap.MnvH1D_Vertex_Z_Aluminium[ind], sb_upstreamCap.MnvH1D_Vertex_Z_Carbon[ind],
                   sb_upstreamCap.MnvH1D_Vertex_Z_Iron[ind], sb_upstreamCap.MnvH1D_Vertex_Z_Lead[ind], sb_upstreamCap.MnvH1D_Vertex_Z_Other[ind],

                   sb_Barrel.MnvH1D_Vertex_Z_data, sb_Barrel.MnvH1D_Vertex_Z_Helium[ind], sb_Barrel.MnvH1D_Vertex_Z_Aluminium[ind], sb_Barrel.MnvH1D_Vertex_Z_Carbon[ind],
                   sb_Barrel.MnvH1D_Vertex_Z_Iron[ind], sb_Barrel.MnvH1D_Vertex_Z_Lead[ind], sb_Barrel.MnvH1D_Vertex_Z_Other[ind],

                   sb_downstreamCap.MnvH1D_Vertex_Z_data, sb_downstreamCap.MnvH1D_Vertex_Z_Helium[ind], sb_downstreamCap.MnvH1D_Vertex_Z_Aluminium[ind], sb_downstreamCap.MnvH1D_Vertex_Z_Carbon[ind],
                   sb_downstreamCap.MnvH1D_Vertex_Z_Iron[ind], sb_downstreamCap.MnvH1D_Vertex_Z_Lead[ind], sb_downstreamCap.MnvH1D_Vertex_Z_Other[ind],

                   sb_downstreamConcaveCap.MnvH1D_Vertex_Z_data, sb_downstreamConcaveCap.MnvH1D_Vertex_Z_Helium[ind], sb_downstreamConcaveCap.MnvH1D_Vertex_Z_Aluminium[ind],
                   sb_downstreamConcaveCap.MnvH1D_Vertex_Z_Carbon[ind],
                   sb_downstreamConcaveCap.MnvH1D_Vertex_Z_Iron[ind], sb_downstreamConcaveCap.MnvH1D_Vertex_Z_Lead[ind], sb_downstreamConcaveCap.MnvH1D_Vertex_Z_Other[ind]);

return ChiSqrt_return;

}

double Helium_3CryoRegionsSideBandTool::GetLogChiSqt_Z(Helium3SideBand &sb_upstreamCap, Helium3SideBand &sb_Barrel,
  Helium3SideBand &sb_downstreamCap, Helium3SideBand &sb_downstreamConcaveCap , int ind){

  double ChiSqrt_return =   LogChiSqrt(sb_upstreamCap.MnvH1D_Vertex_Z_data, sb_upstreamCap.MnvH1D_Vertex_Z_Helium[ind], sb_upstreamCap.MnvH1D_Vertex_Z_Aluminium[ind], sb_upstreamCap.MnvH1D_Vertex_Z_Carbon[ind],
                   sb_upstreamCap.MnvH1D_Vertex_Z_Iron[ind], sb_upstreamCap.MnvH1D_Vertex_Z_Lead[ind], sb_upstreamCap.MnvH1D_Vertex_Z_Other[ind],

                   sb_Barrel.MnvH1D_Vertex_Z_data, sb_Barrel.MnvH1D_Vertex_Z_Helium[ind], sb_Barrel.MnvH1D_Vertex_Z_Aluminium[ind], sb_Barrel.MnvH1D_Vertex_Z_Carbon[ind],
                   sb_Barrel.MnvH1D_Vertex_Z_Iron[ind], sb_Barrel.MnvH1D_Vertex_Z_Lead[ind], sb_Barrel.MnvH1D_Vertex_Z_Other[ind],

                   sb_downstreamCap.MnvH1D_Vertex_Z_data, sb_downstreamCap.MnvH1D_Vertex_Z_Helium[ind], sb_downstreamCap.MnvH1D_Vertex_Z_Aluminium[ind], sb_downstreamCap.MnvH1D_Vertex_Z_Carbon[ind],
                   sb_downstreamCap.MnvH1D_Vertex_Z_Iron[ind], sb_downstreamCap.MnvH1D_Vertex_Z_Lead[ind], sb_downstreamCap.MnvH1D_Vertex_Z_Other[ind],

                   sb_downstreamConcaveCap.MnvH1D_Vertex_Z_data, sb_downstreamConcaveCap.MnvH1D_Vertex_Z_Helium[ind], sb_downstreamConcaveCap.MnvH1D_Vertex_Z_Aluminium[ind],
                   sb_downstreamConcaveCap.MnvH1D_Vertex_Z_Carbon[ind],
                   sb_downstreamConcaveCap.MnvH1D_Vertex_Z_Iron[ind], sb_downstreamConcaveCap.MnvH1D_Vertex_Z_Lead[ind], sb_downstreamConcaveCap.MnvH1D_Vertex_Z_Other[ind]);

return ChiSqrt_return;

}




double Helium_3CryoRegionsSideBandTool::GetChiSqt_R(Helium3SideBand &sb_upstreamCap, Helium3SideBand &sb_Barrel,
  Helium3SideBand &sb_downstreamCap, Helium3SideBand &sb_downstreamConcaveCap , int ind)
  {
    double ChiSqrt_return =   ChiSqrt(sb_upstreamCap.MnvH1D_Vertex_R_data,
      sb_upstreamCap.MnvH1D_Vertex_R_Helium[ind],
      sb_upstreamCap.MnvH1D_Vertex_R_Aluminium[ind],
      sb_upstreamCap.MnvH1D_Vertex_R_Carbon[ind],
      sb_upstreamCap.MnvH1D_Vertex_R_Iron[ind],
      sb_upstreamCap.MnvH1D_Vertex_R_Lead[ind],
      sb_upstreamCap.MnvH1D_Vertex_R_Other[ind],

      sb_Barrel.MnvH1D_Vertex_R_data,
      sb_Barrel.MnvH1D_Vertex_R_Helium[ind],
      sb_Barrel.MnvH1D_Vertex_R_Aluminium[ind],
      sb_Barrel.MnvH1D_Vertex_R_Carbon[ind],
      sb_Barrel.MnvH1D_Vertex_R_Iron[ind],
      sb_Barrel.MnvH1D_Vertex_R_Lead[ind],
      sb_Barrel.MnvH1D_Vertex_R_Other[ind],

      sb_downstreamCap.MnvH1D_Vertex_R_data,
      sb_downstreamCap.MnvH1D_Vertex_R_Helium[ind],
      sb_downstreamCap.MnvH1D_Vertex_R_Aluminium[ind],
      sb_downstreamCap.MnvH1D_Vertex_R_Carbon[ind],
      sb_downstreamCap.MnvH1D_Vertex_R_Iron[ind],
      sb_downstreamCap.MnvH1D_Vertex_R_Lead[ind],
      sb_downstreamCap.MnvH1D_Vertex_R_Other[ind],

      sb_downstreamConcaveCap.MnvH1D_Vertex_R_data,
      sb_downstreamConcaveCap.MnvH1D_Vertex_R_Helium[ind],
      sb_downstreamConcaveCap.MnvH1D_Vertex_R_Aluminium[ind],
      sb_downstreamConcaveCap.MnvH1D_Vertex_R_Carbon[ind],
      sb_downstreamConcaveCap.MnvH1D_Vertex_R_Iron[ind],
      sb_downstreamConcaveCap.MnvH1D_Vertex_R_Lead[ind],
      sb_downstreamConcaveCap.MnvH1D_Vertex_R_Other[ind]);
      return ChiSqrt_return;

    }


    double Helium_3CryoRegionsSideBandTool::GetLogChiSqt_R(Helium3SideBand &sb_upstreamCap, Helium3SideBand &sb_Barrel,
      Helium3SideBand &sb_downstreamCap, Helium3SideBand &sb_downstreamConcaveCap , int ind)
      {
        double ChiSqrt_return =    LogChiSqrt(sb_upstreamCap.MnvH1D_Vertex_R_data,
          sb_upstreamCap.MnvH1D_Vertex_R_Helium[ind],
          sb_upstreamCap.MnvH1D_Vertex_R_Aluminium[ind],
          sb_upstreamCap.MnvH1D_Vertex_R_Carbon[ind],
          sb_upstreamCap.MnvH1D_Vertex_R_Iron[ind],
          sb_upstreamCap.MnvH1D_Vertex_R_Lead[ind],
          sb_upstreamCap.MnvH1D_Vertex_R_Other[ind],

          sb_Barrel.MnvH1D_Vertex_R_data,
          sb_Barrel.MnvH1D_Vertex_R_Helium[ind],
          sb_Barrel.MnvH1D_Vertex_R_Aluminium[ind],
          sb_Barrel.MnvH1D_Vertex_R_Carbon[ind],
          sb_Barrel.MnvH1D_Vertex_R_Iron[ind],
          sb_Barrel.MnvH1D_Vertex_R_Lead[ind],
          sb_Barrel.MnvH1D_Vertex_R_Other[ind],

          sb_downstreamCap.MnvH1D_Vertex_R_data,
          sb_downstreamCap.MnvH1D_Vertex_R_Helium[ind],
          sb_downstreamCap.MnvH1D_Vertex_R_Aluminium[ind],
          sb_downstreamCap.MnvH1D_Vertex_R_Carbon[ind],
          sb_downstreamCap.MnvH1D_Vertex_R_Iron[ind],
          sb_downstreamCap.MnvH1D_Vertex_R_Lead[ind],
          sb_downstreamCap.MnvH1D_Vertex_R_Other[ind],

          sb_downstreamConcaveCap.MnvH1D_Vertex_R_data,
          sb_downstreamConcaveCap.MnvH1D_Vertex_R_Helium[ind],
          sb_downstreamConcaveCap.MnvH1D_Vertex_R_Aluminium[ind],
          sb_downstreamConcaveCap.MnvH1D_Vertex_R_Carbon[ind],
          sb_downstreamConcaveCap.MnvH1D_Vertex_R_Iron[ind],
          sb_downstreamConcaveCap.MnvH1D_Vertex_R_Lead[ind],
          sb_downstreamConcaveCap.MnvH1D_Vertex_R_Other[ind]);
          return ChiSqrt_return;

        }


void Helium_3CryoRegionsSideBandTool::GetChiSqt_FitParms(Helium3SideBand &sb_upstreamCap, Helium3SideBand &sb_Barrel,
  Helium3SideBand &sb_downstreamCap, Helium3SideBand &sb_downstreamConcaveCap , int ind,
  double &chisqrt_X, double &chisqrt_Y, double &chisqrt_Z, double &chisqrt_R)
  {
    //std::cout<<"find Chisqr X"<<std::endl;
    chisqrt_X = GetChiSqt_X(sb_upstreamCap, sb_Barrel, sb_downstreamCap, sb_downstreamConcaveCap ,  ind);
    //std::cout<<"find Chisqr Y"<<std::endl;
    chisqrt_Y = GetChiSqt_Y(sb_upstreamCap, sb_Barrel, sb_downstreamCap, sb_downstreamConcaveCap ,  ind);
    //std::cout<<"find Chisqr Z"<<std::endl;
    chisqrt_Z = GetChiSqt_Z(sb_upstreamCap, sb_Barrel, sb_downstreamCap, sb_downstreamConcaveCap ,  ind);
    //std::cout<<"find Chisqr R"<<std::endl;
    chisqrt_R = GetChiSqt_R(sb_upstreamCap, sb_Barrel, sb_downstreamCap, sb_downstreamConcaveCap ,  ind);
    //std::cout<<"Finished"<<std::endl;
  }

  void Helium_3CryoRegionsSideBandTool::GetLogChiSqt_FitParms(Helium3SideBand &sb_upstreamCap, Helium3SideBand &sb_Barrel,
    Helium3SideBand &sb_downstreamCap, Helium3SideBand &sb_downstreamConcaveCap , int ind,
    double &chisqrt_X, double &chisqrt_Y, double &chisqrt_Z, double &chisqrt_R)
    {
      //std::cout<<"find Chisqr X"<<std::endl;
      chisqrt_X = GetLogChiSqt_X(sb_upstreamCap, sb_Barrel, sb_downstreamCap, sb_downstreamConcaveCap ,  ind);
      //std::cout<<"find Chisqr Y"<<std::endl;
      chisqrt_Y = GetLogChiSqt_Y(sb_upstreamCap, sb_Barrel, sb_downstreamCap, sb_downstreamConcaveCap ,  ind);
      //std::cout<<"find Chisqr Z"<<std::endl;
      chisqrt_Z = GetLogChiSqt_Z(sb_upstreamCap, sb_Barrel, sb_downstreamCap, sb_downstreamConcaveCap ,  ind);
      //std::cout<<"find Chisqr R"<<std::endl;
      chisqrt_R = GetLogChiSqt_R(sb_upstreamCap, sb_Barrel, sb_downstreamCap, sb_downstreamConcaveCap ,  ind);
      //std::cout<<"Finished"<<std::endl;
    }



void Helium_3CryoRegionsSideBandTool::GetEMPTYChiSqt_FitParmsBefore( double &chisqrt_X, double &chisqrt_Y, double &chisqrt_Z, double &chisqrt_R){
  //std::cout<<"inside::GetEMPTYChiSqt_FitParmsBefore"<<std::endl;
  GetChiSqt_FitParms(Empty_UpstreamCap, Empty_Barrel, Empty_DownstreamCap,
    Empty_DownstreamConcaveCap , 0, chisqrt_X, chisqrt_Y, chisqrt_Z, chisqrt_R);

  }

  void Helium_3CryoRegionsSideBandTool::GetEMPTY_LOGChiSqt_FitParmsBefore( double &chisqrt_X, double &chisqrt_Y, double &chisqrt_Z, double &chisqrt_R){
    //std::cout<<"inside::GetEMPTYChiSqt_FitParmsBefore"<<std::endl;
    GetLogChiSqt_FitParms(Empty_UpstreamCap, Empty_Barrel, Empty_DownstreamCap,
      Empty_DownstreamConcaveCap , 0, chisqrt_X, chisqrt_Y, chisqrt_Z, chisqrt_R);

    }


  void Helium_3CryoRegionsSideBandTool::GetEMPTYChiSqt_FitParmsBefore_regionX( double &chisqrt_X, double &chisqrt_Y, double &chisqrt_Z, double &chisqrt_R){
    //std::cout<<"inside::GetEMPTYChiSqt_FitParmsBefore"<<std::endl;
    GetChiSqt_FitParms(Empty_XCenter, Empty_XLeftShelf, Empty_XRightShelf,
      Empty_XoutsideEdges, 0, chisqrt_X, chisqrt_Y, chisqrt_Z, chisqrt_R);

    }

    void Helium_3CryoRegionsSideBandTool::GetEMPTYChiSqt_FitParmsBefore_regionXZ( double &chisqrt_X, double &chisqrt_Y, double &chisqrt_Z, double &chisqrt_R){
      //std::cout<<"inside::GetEMPTYChiSqt_FitParmsBefore"<<std::endl;
      GetChiSqt_FitParms(Empty_XCenter, Empty_XLeftShelf, Empty_XRightShelf,
        Empty_DownstreamConcaveCap, 0, chisqrt_X, chisqrt_Y, chisqrt_Z, chisqrt_R);

      }


void Helium_3CryoRegionsSideBandTool::GetEMPTYChiSqt_FitParmsAfter( double &chisqrt_X, double &chisqrt_Y, double &chisqrt_Z, double &chisqrt_R){

   GetChiSqt_FitParms(Empty_UpstreamCap, Empty_Barrel, Empty_DownstreamCap,
      Empty_DownstreamConcaveCap , 1, chisqrt_X, chisqrt_Y, chisqrt_Z, chisqrt_R);

}

void Helium_3CryoRegionsSideBandTool::GetEMPTY_LOG_ChiSqt_FitParmsAfter( double &chisqrt_X, double &chisqrt_Y, double &chisqrt_Z, double &chisqrt_R){

   GetLogChiSqt_FitParms(Empty_UpstreamCap, Empty_Barrel, Empty_DownstreamCap,
      Empty_DownstreamConcaveCap , 1, chisqrt_X, chisqrt_Y, chisqrt_Z, chisqrt_R);

}

void Helium_3CryoRegionsSideBandTool::GetEMPTYChiSqt_FitParmsAfter_regionX( double &chisqrt_X, double &chisqrt_Y, double &chisqrt_Z, double &chisqrt_R){

   GetChiSqt_FitParms(Empty_XCenter, Empty_XLeftShelf, Empty_XRightShelf,
     Empty_XoutsideEdges , 1, chisqrt_X, chisqrt_Y, chisqrt_Z, chisqrt_R);

}

void Helium_3CryoRegionsSideBandTool::GetEMPTYChiSqt_FitParmsAfter_regionXZ( double &chisqrt_X, double &chisqrt_Y, double &chisqrt_Z, double &chisqrt_R){

   GetChiSqt_FitParms(Empty_XCenter, Empty_XLeftShelf, Empty_XRightShelf,
     Empty_DownstreamConcaveCap , 1, chisqrt_X, chisqrt_Y, chisqrt_Z, chisqrt_R);

}


void Helium_3CryoRegionsSideBandTool::Plot_NoStack(std::string pdf_label, int ind, double POT_ratio, std::string sb_name,
   std::string var_name, MnvH1D* data, MnvH1D* mc_total, MnvH1D* Helium, MnvH1D* Aluminium, MnvH1D* Carbon,
    MnvH1D* Iron, MnvH1D* Lead, MnvH1D* Other, std::string Hist_title, std::string xaxislabel, int index, bool UseLogChi)
{
  data->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  mc_total->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));

    std::string type;
    if (ind == 0) type = "Nominal";
    else type = "Fitted";
    //std::cout<<"Ploting type:  "<< type<<std::endl;

    std::string norm = "POT";
    std::string plot_title = "Side Band: " + sb_name + " " + type + " " + norm + " Normalized";

     MnvPlotter* plotter = new MnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);

    TH1D* h_data = new TH1D(data->GetCVHistoWithError());
    TH1D* h_Helium = new TH1D(Helium->GetCVHistoWithError());
    TH1D* h_Aluminium = new TH1D(Aluminium->GetCVHistoWithError());
    TH1D* h_Carbon = new TH1D(Carbon->GetCVHistoWithError());
    TH1D* h_Iron = new TH1D(Iron->GetCVHistoWithError());
    TH1D* h_Lead = new TH1D(Lead->GetCVHistoWithError());
    TH1D* h_Other = new TH1D(Other->GetCVHistoWithError());

    ColorHistsForLines(h_data, h_Helium, h_Aluminium, h_Carbon, h_Iron, h_Lead,  h_Other);
    // MC Total depend on the Modification
    //      If Raws - take the mc_total directly
    //      If Modified - Add all mc models;
    TH1D* h_mc_total;
    if (ind == 0){
        h_mc_total = new TH1D(mc_total->GetCVHistoWithError());
    }
    else{
      h_mc_total = new TH1D(*h_Helium);
      h_mc_total->Add(h_Aluminium);
      h_mc_total->Add(h_Carbon);
      h_mc_total->Add(h_Iron);
      h_mc_total->Add(h_Lead);
      h_mc_total->Add(h_Other);
    }

    // Scale Histograms
    //double mc_ratio = POT_ratio;

    std::string yaxis;
    if(MakeBinWidth==true){

      h_mc_total->Scale(1.0, "width");
      h_Helium->Scale(1.0, "width");
      h_Aluminium->Scale(1.0, "width");
      h_Carbon->Scale(1.0, "width");
      h_Iron->Scale(1.0, "width");
      h_Lead->Scale(1.0, "width");
      h_Other->Scale(1.0, "width");
      h_data->Scale(1.0, "width");
      double binwidth_title = h_mc_total -> GetBinWidth(3);
      yaxis = Form("NEvents / %.2f",binwidth_title);
      //std::cout<< "yaxis = "<< yaxis<<std::endl;
      //std::cout<<"Finished Bin width Norm"<<std::endl;
    }
    else{
      yaxis = "NEvents";
    //  std::cout<<"FInished Bin NOT width Norm"<<std::endl;
    }

    // ------------------------------------------------------------------------
    // Unique Plot for Single Error Band, Single Universe
    //      Comment this section out
    // ------------------------------------------------------------------------


    // Create Canvas and Divide it into two
    TCanvas* c = new TCanvas("c","c",800, 800);
    //TCanvas cE("cE","cE", 800, 800);
    // Upper Pad is the Data vs MC
    //OLDTPad *pad1 = new TPad("pad1", "pad1", 0.05, 0.3, 1, 1.0);
    TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
    pad1->SetBottomMargin(0); // Top and Bottom Plots attached
    pad1->Draw();
    pad1->cd(); // pad1 is the current pad
      // Plot MC Models as THStack
      //std::cout<< " Printing label Xaxis = "<< xaxislabel.c_str()<<std::endl;

      data->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
      h_mc_total->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
      h_mc_total->GetYaxis()->SetTitle(Form("%s",yaxis.c_str()));
      h_mc_total->GetYaxis()->SetTitleFont(62);
      h_mc_total->GetYaxis()->SetTitleSize(0.06);
      //hs->GetYaxis()->CenterTitle();
      //hs->GetYaxis()->SetTitleOffset(1.2);
      h_mc_total->GetXaxis()->SetTitleFont(62);
      h_mc_total->GetXaxis()->SetTitleSize(0.06);

      h_mc_total->GetYaxis()->SetLabelFont(42);
      h_mc_total->GetYaxis()->SetLabelSize(0.05);

      h_mc_total->SetLineWidth(3);
      h_mc_total->SetFillStyle(0);
      h_mc_total->SetLineColor(kBlack);
      h_mc_total->Smooth();
      h_Helium->Smooth();
      h_Aluminium->Smooth();
      h_Carbon->Smooth();
      h_Iron->Smooth();
      h_Lead->Smooth();
      h_Other->Smooth();

      // Styling
      h_mc_total->Draw("HIST L");

      h_Helium->DrawCopy("SAME HIST L");
      h_Aluminium->DrawCopy("SAME HIST L");
      h_Carbon->DrawCopy("SAME HIST L");
      h_Iron->DrawCopy("SAME HIST L");
      h_Lead->DrawCopy("SAME HIST L");
      h_Other->DrawCopy("SAME HIST L");

      //gStyle->SetOptTitle(0);
      //gStyle->SetOptStat(0);


    double hist_max = h_data->GetMaximum();
    //std::cout<<"GetMaximum() =  "<<hist_max<<std::endl;
    h_mc_total->SetMaximum(hist_max * 1.45);

    //std::cout<<"Finshed Drawing Hist "<<std::endl;

    // Add Data Plot
    //h_data->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
    h_data->Draw("SAME E1 X0");

    //std::cout<<"FInished Drawing h_data"<<std::endl;

    // Add Legend
    TLegend *legend = new TLegend(0.75,0.55,0.91,0.92);
    legend->AddEntry(h_data, "Data");
    legend->AddEntry(h_mc_total, "Total MC");
    legend->AddEntry(h_Helium,    "Helium", "l");
    legend->AddEntry(h_Aluminium, "Aluminium: ", "l");
    legend->AddEntry(h_Carbon,    "Carbon: ", "l");
    legend->AddEntry(h_Iron,      "Iron: ", "l");
    legend->AddEntry(h_Lead,      "Lead: ", "l");
    legend->AddEntry(h_Other,     "Other", "l");
    legend->SetTextSize(0.04);
    legend->SetTextFont(42);
    legend->Draw();
    //std::cout<<"FInished Drawing legend"<<std::endl;

    // Add Weights as Text to Modified Plot
    int nPoints = h_data->GetNbinsX()-1;

    //std::cout<<"nPoints = "<<nPoints<< std::endl;

    // Add Plot-ChiSq
    TLatex* text = new TLatex;
    text->SetNDC();
    text->SetTextSize(0.03);
    text->SetTextColor(kBlue);
    double plot_chisq;
    if(UseLogChi == false){ plot_chisq = calc_ChiSq(h_data, h_Helium, h_Aluminium, h_Carbon, h_Lead, h_Iron, h_Other);}
    else if (UseLogChi == false){plot_chisq = calc_LogChiSq(h_data, h_Helium, h_Aluminium, h_Carbon, h_Lead, h_Iron, h_Other);}
    //double plot_chisq = calc_ChiSq(data, signal, WithPi0, QELike, SinglePiPlus, Other);

    if (ind == 0){ChiSq_before_fit_var.push_back(plot_chisq);}

    if (ind != 0){
        int nPars = 1;
        //int nPoints = 136;
        //ChiSq_after_fit[0] = plot_chisq;
        //ChiSq_before_fit[0]= 17.65;
        //std::cout<<"making Fit info" <<  std::endl;
        //std::cout<<"ChiSq_before_fit[0] = "<< ChiSq_before_fit[0]<<std::endl;
          //std::cout<<"ChiSq_after_fit[0] = "<< plot_chisq<<std::endl;
        TLatex* text = new TLatex;
        text->SetTextSize(0.03);
        text->SetNDC();
        text->DrawLatex(0.55, 0.60, Form("Fit Results with %d points, %d pars", nPoints, nPars));
        text->DrawLatex(0.55, 0.57, Form("Before Fit #chi^{2} = %3.2f", ChiSq_before_fit_var.at(index)));
        text->DrawLatex(0.55, 0.54, Form("Before Fit #chi^{2}/dof = %3.2f", ChiSq_before_fit_var.at(index)/(nPoints-nPars)));
        text->DrawLatex(0.55, 0.51, Form("After Fit #chi^{2} = %3.2f", plot_chisq));
        text->DrawLatex(0.55, 0.48, Form("After Fit #chi^{2}/dof = %3.2f", plot_chisq/(double)(nPoints-nPars)));
        text->DrawLatex(0.55, 0.44, Form("#color[4]{wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[0], err_Aluminium[0]));

      //  delete text;
    }

    text->DrawLatex(0.2, 0.85, Form("Plot #chi^{2} = %3.2f", plot_chisq));
    text->DrawLatex(0.2, 0.82, Form("Plot #chi^{2}/dof = %3.2f", plot_chisq / (double) nPoints));
    delete text;
    plotter->AddHistoTitle(Hist_title.c_str(),.04);
    plotter->WritePreliminary("TL", .025, 0, 0, false);
    // Plot Lower Plot: Data vs MC Ratio
    c->cd(); // Go back to default Canvas before creating 2nd Pad
    //TPad *pad2 = new TPad("pad2", "pad2", 0.05, 0.05, 1, 0.3);

    //pad2->SetTopMargin(0);
    //pad2->SetBottomMargin(0.2);

    TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
    pad2->SetTopMargin(0);
    pad2->SetBottomMargin(0.2);
    pad2->SetGridx(); // vertical grid
    pad2->Draw();
    pad2->cd();

    // Calculate the Ratio

    //h_data_mc_ratio->Draw("HIST");
    plotter->axis_title_size_x = 0.1;
    plotter->axis_title_offset_y = .4;
    plotter->axis_title_size_y = 0.12;
    plotter->axis_label_size = 0.1;
    plotter->axis_maximum = 2.5;
    plotter->axis_minimum = .5;
    plotter->DrawDataMCRatio(data, mc_total, 1.0, false, false , -.5, 2, "#frac{Data}{MC}", false);
    // Add Ratio = 1 Line
    TLine ratio_1;
    ratio_1.SetLineWidth(2);
    ratio_1.SetLineStyle(7);
    ratio_1.SetLineColor(kBlue);
    double line_min = h_data->GetBinLowEdge(1);
    double line_max = h_data->GetBinLowEdge(h_data->GetNbinsX()+1);
    ratio_1.DrawLine(line_min,1,line_max,1);

    // Plot Output
    c->Update();
    c->cd();
    c->Print(pdf_label.c_str(),"pdf");

    delete legend;
    delete pad1;
    delete pad2;
    delete c;
    delete h_data;
    delete h_Helium;
    delete h_Aluminium;
    delete h_Carbon ;
    delete h_Iron;
    delete h_Lead;
    delete h_Other;
}
////////////////////////////////////
void Helium_3CryoRegionsSideBandTool::Plot_regions_noStack(std::string pdf_label, int ind, double POT_ratio,
       MnvH1D* data_region1, MnvH1D* mc_total_region1, MnvH1D* Helium_region1, MnvH1D* Aluminium_region1, MnvH1D* Carbon_region1,
       MnvH1D* Iron_region1, MnvH1D* Lead_region1, MnvH1D* Other_region1,
       MnvH1D* data_region2, MnvH1D* mc_total_region2, MnvH1D* Helium_region2, MnvH1D* Aluminium_region2, MnvH1D* Carbon_region2,
       MnvH1D* Iron_region2, MnvH1D* Lead_region2, MnvH1D* Other_region2,
       MnvH1D* data_region3, MnvH1D* mc_total_region3, MnvH1D* Helium_region3, MnvH1D* Aluminium_region3, MnvH1D* Carbon_region3,
       MnvH1D* Iron_region3, MnvH1D* Lead_region3, MnvH1D* Other_region3,
       MnvH1D* data_region4, MnvH1D* mc_total_region4, MnvH1D* Helium_region4, MnvH1D* Aluminium_region4, MnvH1D* Carbon_region4,
       MnvH1D* Iron_region4, MnvH1D* Lead_region4, MnvH1D* Other_region4,

       std::string Hist_title, std::string xaxislabel, double &ChiSqrt, double &ChiSqrtAfter, int FitType, bool UseLogChi, bool doAreaNormalized)
       {

        std::string type;
        if (ind == 0) type = "Nominal";
        else type = "Fitted";
        //std::cout<<"Ploting type: Combined CryoRegions  "<< type<<std::endl;

        //PlotUtils::MnvPlotter* plotter= new mnvPlotter();
         MnvPlotter* plotter = new MnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
        //plotter(PlotUtils::kCCInclusiveHeliumStyle);
        MnvH1D *data = (PlotUtils::MnvH1D*)data_region1->Clone("data");
        data->Add(data_region2);
        data->Add(data_region3);
        data->Add(data_region4);

        MnvH1D *mc_total = (PlotUtils::MnvH1D*)Helium_region1->Clone("mc_total");

        mc_total->Add(Aluminium_region1 );
        mc_total->Add(Carbon_region1);
        mc_total->Add(Iron_region1 );
        mc_total->Add(Lead_region1 );
        mc_total->Add(Other_region1);

        mc_total->Add(Helium_region2 );
        mc_total->Add(Aluminium_region2 );
        mc_total->Add(Carbon_region2);
        mc_total->Add(Iron_region2 );
        mc_total->Add(Lead_region2 );
        mc_total->Add(Other_region2);

        mc_total->Add(Helium_region3 );
        mc_total->Add(Aluminium_region3 );
        mc_total->Add(Carbon_region3);
        mc_total->Add(Iron_region3 );
        mc_total->Add(Lead_region3 );
        mc_total->Add(Other_region3);

        mc_total->Add(Helium_region4 );
        mc_total->Add(Aluminium_region4 );
        mc_total->Add(Carbon_region4);
        mc_total->Add(Iron_region4 );
        mc_total->Add(Lead_region4 );
        mc_total->Add(Other_region4);

        data->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
        mc_total->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));


        TH1D* h_data_Combined = new TH1D(data_region1->GetCVHistoWithError());
        TH1D* h_Helium_region1 = new TH1D(Helium_region1->GetCVHistoWithError());
        TH1D* h_Aluminium_region1 = new TH1D(Aluminium_region1->GetCVHistoWithError());

        TH1D* h_Carbon_Combined = new TH1D(Carbon_region1->GetCVHistoWithError());
        TH1D* h_Iron_Combined = new TH1D(Iron_region1->GetCVHistoWithError());
        TH1D* h_Lead_Combined = new TH1D(Lead_region1->GetCVHistoWithError());
        TH1D* h_Other_Combined = new TH1D(Other_region1->GetCVHistoWithError());

        TH1D* h_data_region2 = new TH1D(data_region2->GetCVHistoWithError());
        TH1D* h_Helium_region2 = new TH1D(Helium_region2->GetCVHistoWithError());

        TH1D* h_Aluminium_region2 = new TH1D(Aluminium_region2->GetCVHistoWithError());
        TH1D* h_Carbon_region2 = new TH1D(Carbon_region2->GetCVHistoWithError());
        TH1D* h_Iron_region2 = new TH1D(Iron_region2->GetCVHistoWithError());
        TH1D* h_Lead_region2 = new TH1D(Lead_region2->GetCVHistoWithError());
        TH1D* h_Other_region2 = new TH1D(Other_region2->GetCVHistoWithError());

        h_Carbon_Combined->Add(h_Carbon_region2);
        h_Iron_Combined->Add(  h_Iron_region2);
        h_Lead_Combined->Add(  h_Lead_region2);
        h_Other_Combined->Add( h_Other_region2);
        h_data_Combined->Add(  h_data_region2);

        TH1D* h_data_region3 = new TH1D(data_region3->GetCVHistoWithError());
        TH1D* h_Helium_region3 = new TH1D(Helium_region3->GetCVHistoWithError());
        TH1D* h_Aluminium_region3 = new TH1D(Aluminium_region3->GetCVHistoWithError());

        TH1D* h_Carbon_region3 = new TH1D(Carbon_region3->GetCVHistoWithError());
        TH1D* h_Iron_region3 = new TH1D(Iron_region3->GetCVHistoWithError());
        TH1D* h_Lead_region3 = new TH1D(Lead_region3->GetCVHistoWithError());
        TH1D* h_Other_region3 = new TH1D(Other_region3->GetCVHistoWithError());

        h_Carbon_Combined->Add(h_Carbon_region3);
        h_Iron_Combined->Add(  h_Iron_region3);
        h_Lead_Combined->Add(  h_Lead_region3);
        h_Other_Combined->Add( h_Other_region3);
        h_data_Combined->Add(  h_data_region3);

        TH1D* h_data_region4 = new TH1D(data_region4->GetCVHistoWithError());
        TH1D* h_Helium_region4 = new TH1D(Helium_region4->GetCVHistoWithError());
        TH1D* h_Aluminium_region4 = new TH1D(Aluminium_region4->GetCVHistoWithError());

        TH1D* h_Carbon_region4 = new TH1D(Carbon_region4->GetCVHistoWithError());
        TH1D* h_Iron_region4 = new TH1D(Iron_region4->GetCVHistoWithError());
        TH1D* h_Lead_region4 = new TH1D(Lead_region4->GetCVHistoWithError());
        TH1D* h_Other_region4 = new TH1D(Other_region4->GetCVHistoWithError());


        h_Carbon_Combined->Add(h_Carbon_region4);
        h_Iron_Combined->Add(  h_Iron_region4);
        h_Lead_Combined->Add(  h_Lead_region4);
        h_Other_Combined->Add( h_Other_region4);

        ///////////////// Combining all others to Other
        h_data_Combined->Add(  h_data_region4);


        ColorHistsForLines(h_Carbon_Combined, h_Iron_Combined, h_Lead_Combined,  h_Other_Combined);
        ColorData(h_data_Combined);
        Color_HeliumHistsForLines(h_Helium_region1, h_Helium_region2, h_Helium_region3, h_Helium_region4);
        Color_AluminiumHistsForLines(h_Aluminium_region1, h_Aluminium_region2, h_Aluminium_region3, h_Aluminium_region4);

        // MC Total depend on the Modification
        // If Raws - take the mc_total directly
        // If Modified - Add all mc models;

        TH1D* h_mc_total = new TH1D(mc_total->GetCVHistoWithError());
    /*    if (ind == 0){
            h_mc_total = new TH1D(mc_total_region1->GetCVHistoWithError());
            h_mc_total->Add(mc_total_region2);
            h_mc_total->Add(mc_total_region3);
            h_mc_total->Add(mc_total_region4);
        }

        else{

          h_mc_total = new TH1D(*h_Helium_region1);
          h_mc_total->Add(h_Helium_region2);
          h_mc_total->Add(h_Helium_region3);
          h_mc_total->Add(h_Helium_region4);

          h_mc_total->Add(h_Aluminium_region1);
          h_mc_total->Add(h_Aluminium_region2);
          h_mc_total->Add(h_Aluminium_region3);
          h_mc_total->Add(h_Aluminium_region4);

          h_mc_total->Add(h_Carbon_Combined);
          h_mc_total->Add(h_Iron_Combined);
          h_mc_total->Add(h_Lead_Combined);
          h_mc_total->Add(h_Other_Combined);
        }
*/
        double plot_chisq;
        //double plot_chisq = calc_ChiSq(data, signal, WithPi0, QELike, SinglePiPlus, Other);
        if(UseLogChi==false){
         plot_chisq = calc_ChiSq(h_data_Combined,
          h_Helium_region1,
          h_Helium_region2,
          h_Helium_region3,
          h_Helium_region4,
          h_Aluminium_region1,
          h_Aluminium_region2,
          h_Aluminium_region3,
          h_Aluminium_region4,
          h_Carbon_Combined, h_Lead_Combined, h_Iron_Combined, h_Other_Combined);
        }
        else if(UseLogChi==true){
         plot_chisq = calc_LogChiSq(h_data_Combined,
          h_Helium_region1,
          h_Helium_region2,
          h_Helium_region3,
          h_Helium_region4,
          h_Aluminium_region1,
          h_Aluminium_region2,
          h_Aluminium_region3,
          h_Aluminium_region4,
          h_Carbon_Combined, h_Lead_Combined, h_Iron_Combined, h_Other_Combined);
        }

        h_Other_Combined->Add(h_Carbon_Combined);
        h_Other_Combined->Add(h_Iron_Combined);
        h_Other_Combined->Add(h_Lead_Combined);

        if(doAreaNormalized == true){

          if(h_mc_total->GetNbinsX() !=h_data_Combined->GetNbinsX()){std::cout<<"~~~ Whoah Data and MC have different number of Bins HistTitle : "<< Hist_title<<std::endl; assert(false); }
          double MCArea = h_mc_total->Integral(1,h_mc_total->GetNbinsX());
          double DataArea = h_data_Combined->Integral(1,h_data_Combined->GetNbinsX());
          double areascaler = DataArea / MCArea;

          h_mc_total->Scale(areascaler);

          h_Helium_region1->Scale(areascaler);
          h_Aluminium_region1->Scale(areascaler);

          h_Helium_region2->Scale(areascaler);
          h_Aluminium_region2->Scale(areascaler);

          h_Helium_region3->Scale(areascaler);
          h_Aluminium_region3->Scale(areascaler);

          h_Helium_region4->Scale(areascaler);
          h_Aluminium_region4->Scale(areascaler);

        //  h_Carbon_Combined->Scale(areascaler);
        //  h_Iron_Combined->Scale(areascaler);
        //  h_Lead_Combined->Scale(areascaler);
          h_Other_Combined->Scale(areascaler);


        }


        ////////////////////////////
        // going to combined the Carbon , Tron , Lead , Other
        ////////////////////////////



      ////////////////////////////

        std::string yaxis;
        if(MakeBinWidth==true){

          h_mc_total->Scale(1.0, "width");

          h_Helium_region1->Scale(1.0, "width");
          h_Aluminium_region1->Scale(1.0, "width");

          h_Helium_region2->Scale(1.0, "width");
          h_Aluminium_region2->Scale(1.0, "width");

          h_Helium_region3->Scale(1.0, "width");
          h_Aluminium_region3->Scale(1.0, "width");

          h_Helium_region4->Scale(1.0, "width");
          h_Aluminium_region4->Scale(1.0, "width");

          //h_Carbon_Combined->Scale(1.0, "width");
          //h_Iron_Combined->Scale(1.0, "width");
          //h_Lead_Combined->Scale(1.0, "width");
          h_Other_Combined->Scale(1.0, "width");
          h_data_Combined->Scale(1.0, "width");

          double binwidth_title = h_mc_total -> GetBinWidth(3);
          yaxis = Form("NEvents / %.2f",binwidth_title);
          if(doAreaNormalized == true){yaxis = Form("[DataAreaNorm] NEvents / %.2f",binwidth_title);}
          //std::cout<< "yaxis = "<< yaxis<<std::endl;
          //std::cout<<"Finished Bin width Norm"<<std::endl;
        }
        else{
          yaxis = "NEvents";
        //  std::cout<<"FInished Bin NOT width Norm"<<std::endl;
        }

        // ------------------------------------------------------------------------
        // Unique Plot for Single Error Band, Single Universe
        //      Comment this section out
        // ------------------------------------------------------------------------


        // Create Canvas and Divide it into two
        TCanvas* c = new TCanvas("c","c",800, 800);
        //TCanvas cE("cE","cE", 800, 800);
        // Upper Pad is the Data vs MC
        //OLDTPad *pad1 = new TPad("pad1", "pad1", 0.05, 0.3, 1, 1.0);
        TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
        pad1->SetBottomMargin(0); // Top and Bottom Plots attached
        pad1->Draw();
        pad1->cd(); // pad1 is the current pad
        // Styling
        data->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
        h_mc_total->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
        h_mc_total->GetYaxis()->SetTitle(Form("%s",yaxis.c_str()));
        h_mc_total->GetYaxis()->SetTitleFont(62);
        h_mc_total->GetYaxis()->SetTitleSize(0.06);
        //hs->GetYaxis()->CenterTitle();
        //hs->GetYaxis()->SetTitleOffset(1.2);
        h_mc_total->GetXaxis()->SetTitleFont(62);
        h_mc_total->GetXaxis()->SetTitleSize(0.06);

        h_mc_total->GetYaxis()->SetLabelFont(42);
        h_mc_total->GetYaxis()->SetLabelSize(0.05);

        //double hist_max_data = h_data_Combined->GetMaximum();
        //double hist_max_mc = h_mc_total->GetMaximum();

        if(h_mc_total->GetMaximum()>h_data_Combined->GetMaximum()){
          h_mc_total->SetMaximum(h_mc_total->GetMaximum() * 1.45);
        }
        else { h_mc_total->SetMaximum(h_data_Combined->GetMaximum() * 1.45);}

        //h_mc_total->SetMarkerStyle(0);
        h_mc_total->SetLineWidth(2);
        h_mc_total->SetLineColor(kBlack);
        //h_mc_total->SetFillColor(41);

        // Styling
        //h_mc_total->Smooth();
        h_mc_total->Smooth();
        h_Helium_region1->Smooth();
        h_Helium_region2->Smooth();
        h_Helium_region3->Smooth();
        h_Helium_region4->Smooth();
        h_Aluminium_region1->Smooth();
        h_Aluminium_region2->Smooth();
        h_Aluminium_region3->Smooth();
        h_Aluminium_region4->Smooth();
        h_Other_Combined->Smooth();

        h_mc_total->Draw("HIST L");
        h_Helium_region1->DrawCopy("SAME HIST L");
        h_Helium_region2->DrawCopy("SAME HIST L");
        h_Helium_region3->DrawCopy("SAME HIST L");
        h_Helium_region4->DrawCopy("SAME HIST L");
        h_Aluminium_region1->DrawCopy("SAME HIST L");
        h_Aluminium_region2->DrawCopy("SAME HIST L");
        h_Aluminium_region3->DrawCopy("SAME HIST L");
        h_Aluminium_region4->DrawCopy("SAME HIST L");
        //h_Carbon_Combined->Draw("SAME L");
        //h_Iron_Combined->Draw("SAME L");
        //h_Lead_Combined->Draw("SAME L");
        h_Other_Combined->DrawCopy("SAME HIST L");


        c->Modified();

        //std::cout<<"Finshed Drawing Hist "<<std::endl;

        // Add Data Plot
        h_data_Combined->Draw("SAME E1 X0");
        //std::cout<<"FInished Drawing h_data"<<std::endl;

        // Add Legend
        TLegend *legend = new TLegend(0.75,0.55,0.91,0.92);              //0.56,0.50,0.9,0.94);
        legend->AddEntry(h_data_Combined, "Data");
        // Add Weights as Text to Modified Plot
        int nPoints = h_data_Combined->GetNbinsX()-1;

        //std::cout<<"nPoints = "<<nPoints<< std::endl;

        // Add Plot-ChiSq
        TLatex* text = new TLatex;
        text->SetNDC();
        text->SetTextColor(kBlue);
        text->SetTextSize(0.03);
        text->DrawLatex(0.2, 0.85, Form("Plot #chi^{2} = %3.2f", plot_chisq));
        text->DrawLatex(0.2, 0.82, Form("Plot #chi^{2}/dof = %3.2f", plot_chisq / (double) nPoints));

          if (ind == 0){
            ChiSq_before_fit_var.push_back(plot_chisq);
            ChiSqrt = plot_chisq;
          }


          if(FitType == 3){
            legend->AddEntry(h_Helium_region1,          "XCenter He: ",           "f");
            legend->AddEntry(h_Helium_region2,          "XLeftShelf He: ",        "f");
            legend->AddEntry(h_Helium_region3,          "XRightShelf He: ",       "f");
            legend->AddEntry(h_Helium_region4,          "XoutsideEdges He: ",     "f");
            legend->AddEntry(h_Aluminium_region1,       "XCenter Al: ",           "f");
            legend->AddEntry(h_Aluminium_region2,       "XLeftShelf Al: ",       "f");
            legend->AddEntry(h_Aluminium_region3,       "XRightShelf Al: ",      "f");
            legend->AddEntry(h_Aluminium_region4,       "XoutsideEdges Al: ", "f");
          }
          else if(FitType == 4){
            legend->AddEntry(h_Helium_region1,          "XCenter He: ",           "f");
            legend->AddEntry(h_Helium_region2,          "XLeftShelf He: ",        "f");
            legend->AddEntry(h_Helium_region3,          "XRightShelf He: ",       "f");
            legend->AddEntry(h_Helium_region4,          "^{4}He DSConcave ",     "f");
            legend->AddEntry(h_Aluminium_region1,       "XCenter Al: ",           "f");
            legend->AddEntry(h_Aluminium_region2,       "XLeftShelf Al: ",       "f");
            legend->AddEntry(h_Aluminium_region3,       "XRightShelf Al: ",      "f");
            legend->AddEntry(h_Aluminium_region4,       "^{27}Al DSConcave ", "f");
          }

          else{
            legend->AddEntry(h_mc_total,    "Total MC ",        "l");
            legend->AddEntry(h_Helium_region1,    "^{4}He USCap ",        "l");
            legend->AddEntry(h_Helium_region2,    "^{4}He Barrel ",       "l");
            legend->AddEntry(h_Helium_region3,    "^{4}He DSCap ",         "l");
            legend->AddEntry(h_Helium_region4,    "^{4}He DSConcave ", "l");
            legend->AddEntry(h_Aluminium_region1, "^{27}Al USCap ",        "l");
            legend->AddEntry(h_Aluminium_region2, "^{27}Al Barrel ",       "l");
            legend->AddEntry(h_Aluminium_region3, "^{27}Al DSCap ",         "l");
            legend->AddEntry(h_Aluminium_region4, "^{27}Al DSConcave ", "l");
          }


          //legend->AddEntry(h_Carbon_Combined, "C: ",    "l");
          //legend->AddEntry(h_Iron_Combined,   "Fe: ",   "l");
          //legend->AddEntry(h_Lead_Combined,   "Pb: ",   "l");
          legend->AddEntry(h_Other_Combined,  "Other","l");

          legend->SetTextSize(0.025);
          legend->SetTextFont(42);
          legend->Draw();
          text->SetTextSize(0.02);
          text->SetTextColor(kBlack);
        if (ind != 0 &&  FitType== 1){
        int nPars = 4;
        //std::cout<<"making Fit info" <<  std::endl;
        //std::cout<<"ChiSq_before_fit[0] = "<< ChiSq_before_fit[0]<<std::endl;
        //  std::cout<<"ChiSq_after_fit[0] = "<< plot_chisq<<std::endl;
        double xplace = .2;
        double yplace = 0.80;
        text->DrawLatex(xplace, yplace, Form("Fit Results with %d points, %d pars", nPoints, nPars));
        yplace-=.02;
        text->DrawLatex(xplace, yplace , Form("Before Fit #chi^{2} = %3.2f", ChiSqrt));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("Before Fit #chi^{2}/dof = %3.2f", ChiSqrt/(nPoints-nPars)));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2} = %3.2f", plot_chisq));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2}/dof = %3.2f", plot_chisq/(double)(nPoints-nPars)));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{USCap wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[0], err_Aluminium[0]));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{Barrel wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[1], err_Aluminium[1]));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{DSCap wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[2], err_Aluminium[2]));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{DSConcave  wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[3], err_Aluminium[3]));
        yplace-=.02;
        ChiSqrtAfter = plot_chisq;

        }
        else if (ind != 0 && FitType == 2){
        int nPars = 4;
          double xplace = .2;
          double yplace = 0.80;
          text->DrawLatex(xplace, yplace, Form("Fit Results with %d points, %d pars", nPoints, nPars));
          yplace-=.02;
          text->DrawLatex(xplace, yplace , Form("Before Fit #chi^{2} = %3.2f", ChiSqrt));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("Before Fit #chi^{2}/dof = %3.2f", ChiSqrt/(nPoints-nPars)));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2} = %3.2f", plot_chisq));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2}/dof = %3.2f", plot_chisq/(double)(nPoints-nPars)));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("#color[4]{USCap wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[0], err_Aluminium[0]));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("#color[4]{Barrel wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[1], err_Aluminium[1]));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("#color[4]{DSCap wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[2], err_Aluminium[2]));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("#color[4]{DSConcave  wgt(He) = %3.2f #pm %3.2f}", wgt_Aluminium[3], err_Aluminium[3]));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("#color[4]{USCap wgt(He) = %3.2f #pm %3.2f}", wgt_Helium[0], err_Helium[0]));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("#color[4]{barrel wgt(He) = %3.2f #pm %3.2f}", wgt_Helium[1], err_Helium[1]));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("#color[4]{DSCap wgt(He) = %3.2f #pm %3.2f}", wgt_Helium[2], err_Helium[2]));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("#color[4]{DSConcave  wgt(He) = %3.2f #pm %3.2f}", wgt_Helium[3], err_Helium[3]));

          ChiSqrtAfter = plot_chisq;

        }
        else if(ind != 0 && FitType == 3){
        int nPars = 4;

        double xplace = .2;
        double yplace = 0.80;
        text->DrawLatex(xplace, yplace, Form("Fit Results with %d points, %d pars", nPoints, nPars));
        yplace-=.02;
        text->DrawLatex(xplace, yplace ,Form("Before Fit #chi^{2} = %3.2f", ChiSqrt));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("Before Fit #chi^{2}/dof = %3.2f", ChiSqrt/(nPoints-nPars)));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2} = %3.2f", plot_chisq));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2}/dof = %3.2f", plot_chisq/(double)(nPoints-nPars)));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{XCenter wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[0], err_Aluminium[0]));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{XLeftShelf wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[1], err_Aluminium[1]));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{XRightShelf wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[2], err_Aluminium[2]));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{XoutsideEdges cap wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[3], err_Aluminium[3]));
        yplace-=.02;
        ChiSqrtAfter = plot_chisq;

        }
        else if(ind != 0 && FitType == 4){
        int nPars = 4;

        double xplace = .2;
        double yplace = 0.80;
        text->DrawLatex(xplace, yplace, Form("Fit Results with %d points, %d pars", nPoints, nPars));
        yplace-=.02;
        text->DrawLatex(xplace, yplace ,Form("Before Fit #chi^{2} = %3.2f", ChiSqrt));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("Before Fit #chi^{2}/dof = %3.2f", ChiSqrt/(nPoints-nPars)));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2} = %3.2f", plot_chisq));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2}/dof = %3.2f", plot_chisq/(double)(nPoints-nPars)));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{XCenter wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[0], err_Aluminium[0]));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{XLeftShelf wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[1], err_Aluminium[1]));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{XRightShelf wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[2], err_Aluminium[2]));
        yplace-=.02;
        text->DrawLatex(xplace, yplace, Form("#color[4]{DSConcave  wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[3], err_Aluminium[3]));
        yplace-=.02;
        ChiSqrtAfter = plot_chisq;

        }
        //std::cout<<"FInished Drawing legend"<<std::endl;
        delete text;
        plotter->AddHistoTitle(Hist_title.c_str(),.04);
        plotter->WritePreliminary("TL", .025, 0, 0, false);
        // Plot Lower Plot: Data vs MC Ratio
        c->cd(); // Go back to default Canvas before creating 2nd Pad
        //TPad *pad2 = new TPad("pad2", "pad2", 0.05, 0.05, 1, 0.3);

        //pad2->SetTopMargin(0);
        //pad2->SetBottomMargin(0.2);
        c->Modified();
        TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
        pad2->SetTopMargin(0);
        pad2->SetBottomMargin(0.2);
        pad2->SetGridx(); // vertical grid
        pad2->Draw();
        pad2->cd();

        // Calculate the Ratio

        //h_data_mc_ratio->Draw("HIST");
        plotter->axis_title_size_x = 0.1;
        plotter->axis_title_offset_y = .4;
        plotter->axis_title_offset_x = 1.35;
        plotter->axis_title_size_y = 0.12;
        plotter->axis_label_size = 0.1;
        plotter->axis_maximum = 2.5;
        plotter->axis_minimum = .5;

        plotter->DrawDataMCRatio(data, mc_total, 1.0, false, false , -.5, 2, "#frac{Data}{MC}", false);
        // Add Ratio = 1 Line
        TLine ratio_1;
        ratio_1.SetLineWidth(2);
        ratio_1.SetLineStyle(7);
        ratio_1.SetLineColor(kBlue);
        double line_min = h_data_Combined->GetBinLowEdge(1);
        double line_max = h_data_Combined->GetBinLowEdge(h_data_Combined->GetNbinsX()+1);
        ratio_1.DrawLine(line_min,1,line_max,1);
        // Plot Output
        c->Update();
        c->cd();
        c->Print(pdf_label.c_str(),"pdf");

        delete legend;
        delete pad1;
        delete pad2;
        delete c;
        delete data;
        delete mc_total;
        delete h_data_Combined;
        delete h_Helium_region1;
        delete h_Aluminium_region1;
        delete h_Carbon_Combined;
        delete h_Iron_Combined;
        delete h_Lead_Combined;
        delete h_Other_Combined;
        delete h_data_region2;
        delete h_Helium_region2;
        delete h_Aluminium_region2;
        delete h_Carbon_region2;
        delete h_Iron_region2;
        delete h_Lead_region2;
        delete h_Other_region2;
        delete h_data_region3;
        delete h_Helium_region3;
        delete h_Aluminium_region3;
        delete h_Carbon_region3;
        delete h_Iron_region3;
        delete h_Lead_region3;
        delete h_Other_region3;
        delete h_data_region4;
        delete h_Helium_region4;
        delete h_Aluminium_region4;
        delete h_Carbon_region4;
        delete h_Iron_region4;
        delete h_Lead_region4;
        delete h_Other_region4;
      }

void Helium_3CryoRegionsSideBandTool::Plot_Al_RatioMCANDData_Full_OverEmpty_Combined(std::string pdf_label, int ind,
       MnvH1D* data_region1_Full, MnvH1D* mc_total_region1_Full,  MnvH1D* Aluminium_region1_Full,
       MnvH1D* data_region2_Full, MnvH1D* mc_total_region2_Full,  MnvH1D* Aluminium_region2_Full,
       MnvH1D* data_region3_Full, MnvH1D* mc_total_region3_Full,  MnvH1D* Aluminium_region3_Full,
       MnvH1D* data_region4_Full, MnvH1D* mc_total_region4_Full,  MnvH1D* Aluminium_region4_Full,

       MnvH1D* data_region1_Empty, MnvH1D* mc_total_region1_Empty,  MnvH1D* Aluminium_region1_Empty,
       MnvH1D* data_region2_Empty, MnvH1D* mc_total_region2_Empty,  MnvH1D* Aluminium_region2_Empty,
       MnvH1D* data_region3_Empty, MnvH1D* mc_total_region3_Empty,  MnvH1D* Aluminium_region3_Empty,
       MnvH1D* data_region4_Empty, MnvH1D* mc_total_region4_Empty,  MnvH1D* Aluminium_region4_Empty,
       std::string Hist_title, std::string xaxislabel)
       {

        TCanvas* c = new TCanvas("c","c",800, 800);

         MnvPlotter* plotter = new MnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
         TH1D* h_data_Total_Empty = new TH1D(data_region1_Empty->GetCVHistoWithError());
         TH1D* h_data_region2_Empty= new TH1D(data_region2_Empty->GetCVHistoWithError());
         TH1D* h_data_region3_Empty= new TH1D(data_region3_Empty->GetCVHistoWithError());
         TH1D* h_data_region4_Empty= new TH1D(data_region4_Empty->GetCVHistoWithError());

         h_data_Total_Empty->Add(h_data_region2_Empty);
         h_data_Total_Empty->Add(h_data_region3_Empty);
         h_data_Total_Empty->Add(h_data_region4_Empty);

        TH1D* tmpRatio_Total_Data = new TH1D(data_region1_Full->GetCVHistoWithError());
        TH1D* tmpRatio_Data_Region2 = new TH1D(data_region2_Full->GetCVHistoWithError());
        TH1D* tmpRatio_Data_Region3 = new TH1D(data_region3_Full->GetCVHistoWithError());
        TH1D* tmpRatio_Data_Region4 = new TH1D(data_region4_Full->GetCVHistoWithError());

        tmpRatio_Total_Data->Add(tmpRatio_Data_Region2);
        tmpRatio_Total_Data->Add(tmpRatio_Data_Region3);
        tmpRatio_Total_Data->Add(tmpRatio_Data_Region4);

        TH1D* tmpRatio_MC_total = new TH1D(mc_total_region1_Full->GetCVHistoWithError());
        TH1D* h_mc_total_region2_Full = new TH1D(mc_total_region2_Full->GetCVHistoWithError());
        TH1D* h_mc_total_region3_Full = new TH1D(mc_total_region3_Full->GetCVHistoWithError());
        TH1D* h_mc_total_region4_Full = new TH1D(mc_total_region4_Full->GetCVHistoWithError());

        tmpRatio_MC_total->Add(h_mc_total_region2_Full);
        tmpRatio_MC_total->Add(h_mc_total_region3_Full);
        tmpRatio_MC_total->Add(h_mc_total_region4_Full);

        TH1D* h_mc_total_Empty = new TH1D(mc_total_region1_Empty->GetCVHistoWithError());
        TH1D* h_mc_total_region2_Empty = new TH1D(mc_total_region2_Empty->GetCVHistoWithError());
        TH1D* h_mc_total_region3_Empty = new TH1D(mc_total_region3_Empty->GetCVHistoWithError());
        TH1D* h_mc_total_region4_Empty = new TH1D(mc_total_region4_Empty->GetCVHistoWithError());

        h_mc_total_Empty->Add(h_mc_total_region2_Empty);
        h_mc_total_Empty->Add(h_mc_total_region3_Empty);
        h_mc_total_Empty->Add(h_mc_total_region4_Empty);

        tmpRatio_MC_total->Divide(tmpRatio_MC_total, h_mc_total_Empty);
        tmpRatio_Total_Data->Divide(tmpRatio_Total_Data, h_data_Total_Empty);

        tmpRatio_MC_total->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));

        TH1D* tmpRatio_Al_Empty_total = new TH1D(Aluminium_region1_Empty->GetCVHistoWithError());
        TH1D* tmpRatio_Al_total = new TH1D(Aluminium_region1_Full->GetCVHistoWithError());

        TH1D* tmpRatio_Alregion2 = new TH1D(Aluminium_region2_Full->GetCVHistoWithError());
        TH1D* tmpRatio_Alregion2_empty = new TH1D(Aluminium_region2_Empty->GetCVHistoWithError());
        tmpRatio_Al_total->Add(tmpRatio_Alregion2);
        tmpRatio_Al_Empty_total->Add(tmpRatio_Alregion2_empty);

        TH1D* tmpRatio_Alregion3 = new TH1D(Aluminium_region3_Full->GetCVHistoWithError());
        TH1D* tmpRatio_Alregion3_empty = new TH1D(Aluminium_region3_Empty->GetCVHistoWithError());
        tmpRatio_Al_total->Add(tmpRatio_Alregion3);
        tmpRatio_Al_Empty_total->Add(tmpRatio_Alregion3_empty);

        TH1D* tmpRatio_Alregion4 = new TH1D(Aluminium_region4_Full->GetCVHistoWithError());
        TH1D* tmpRatio_Alregion4_empty = new TH1D(Aluminium_region4_Empty->GetCVHistoWithError());

        tmpRatio_Al_total->Add(tmpRatio_Alregion4);
        tmpRatio_Al_Empty_total->Add(tmpRatio_Alregion4_empty);

        tmpRatio_Al_total->Divide(tmpRatio_Al_total, tmpRatio_Al_Empty_total);



        plotter->axis_title_size_x = 0.07;
        plotter->axis_title_offset_y = .4;
        plotter->axis_title_offset_x = .9;
        plotter->axis_title_size_y = 0.04;
        plotter->axis_label_size = 0.02;
        gPad->SetGridx(); // vertical grid
        gPad->SetGridy(); // vertical grid

        tmpRatio_MC_total->SetMinimum( -1.0 );
        tmpRatio_MC_total->SetMaximum( 6.0 );

        tmpRatio_MC_total->GetYaxis()->SetTitle("#frac{NEvent [Full]}{NEvent[Empty]}" );
        tmpRatio_MC_total->GetXaxis()->SetTitleFont(plotter->axis_title_font_x);
        tmpRatio_MC_total->GetYaxis()->SetTitleFont(plotter->axis_title_font_y);
        tmpRatio_MC_total->GetXaxis()->SetTitleSize(plotter->axis_title_size_x);
        tmpRatio_MC_total->GetYaxis()->SetTitleSize(plotter->axis_title_size_y);
        tmpRatio_MC_total->GetXaxis()->SetLabelFont(plotter->axis_label_font);
        tmpRatio_MC_total->GetYaxis()->SetLabelFont(plotter->axis_label_font);
        tmpRatio_MC_total->GetXaxis()->SetLabelSize(plotter->axis_label_size);
        tmpRatio_MC_total->GetYaxis()->SetLabelSize(plotter->axis_label_size);
        tmpRatio_MC_total->GetXaxis()->CenterTitle(kTRUE);
        tmpRatio_MC_total->GetYaxis()->CenterTitle(kTRUE);
        tmpRatio_MC_total->SetMarkerStyle(0);
        tmpRatio_Al_total->SetMarkerStyle(0);
        tmpRatio_Al_total->SetLineColor(kBlack);
        tmpRatio_MC_total->GetXaxis()->SetNdivisions(509);
        tmpRatio_Al_total->SetLineStyle(3);
        tmpRatio_Al_total->SetFillStyle(0);
        tmpRatio_MC_total->SetLineColor(kRed);
        tmpRatio_MC_total->Draw("hist");

        tmpRatio_Total_Data->SetMarkerStyle(29);
        tmpRatio_MC_total->SetLineWidth(3);
        tmpRatio_Al_total->SetLineWidth(3);

        tmpRatio_Al_total->Draw("same hist");

        TLine ratio_1;
        ratio_1.SetLineWidth(1);
        ratio_1.SetLineStyle(7);
        ratio_1.SetLineColor(kBlue);
        double line_min = tmpRatio_MC_total->GetBinLowEdge(1);
        double line_max = tmpRatio_MC_total->GetBinLowEdge(tmpRatio_MC_total->GetNbinsX()+1);
        ratio_1.DrawLine(line_min,1,line_max,1);



        //std::cout<<"Finshed Drawing Hist "<<std::endl;
        // Add Data Plot
        tmpRatio_Total_Data->Draw("SAME E1 X0");

        // Add Legend
        TLegend *legend = new TLegend(0.75,0.75,0.9,0.9);
        legend->AddEntry(tmpRatio_Total_Data,   "Total data");           //0.56,0.50,0.9,0.94)
        legend->AddEntry(tmpRatio_MC_total,  "MC Total",        "l");
        legend->AddEntry(tmpRatio_Al_total,  "MC Total Al",     "l");
        legend->SetTextSize(0.025);
        legend->SetTextFont(42);
        legend->Draw();



        // Plot Output
        plotter->AddHistoTitle(Hist_title.c_str(),.04);
        plotter->WritePreliminary("TL", .025, 0, 0, false);
        c->Update();
        c->Print(pdf_label.c_str(),"pdf");

        delete legend;
        delete c;
        delete tmpRatio_Data_Region2;
        delete tmpRatio_Data_Region3;
        delete tmpRatio_Data_Region4;
        delete tmpRatio_Alregion2;
        delete tmpRatio_Alregion3;
        delete tmpRatio_Alregion4;
        delete tmpRatio_MC_total;
        delete plotter;
        delete h_mc_total_Empty;
        delete h_mc_total_region2_Full;
        delete h_mc_total_region3_Full;
        delete h_mc_total_region4_Full;
        delete h_mc_total_region2_Empty;
        delete h_mc_total_region3_Empty;
        delete h_mc_total_region4_Empty;
        delete tmpRatio_Al_total;

      }
      void Helium_3CryoRegionsSideBandTool::Plot_Al_RatioMCANDData_Full_OverEmpty(std::string pdf_label, int ind,
             MnvH1D* data_region1_Full, MnvH1D* mc_total_region1_Full,  MnvH1D* Aluminium_region1_Full,
             MnvH1D* data_region2_Full, MnvH1D* mc_total_region2_Full,  MnvH1D* Aluminium_region2_Full,
             MnvH1D* data_region3_Full, MnvH1D* mc_total_region3_Full,  MnvH1D* Aluminium_region3_Full,
             MnvH1D* data_region4_Full, MnvH1D* mc_total_region4_Full,  MnvH1D* Aluminium_region4_Full,

             MnvH1D* data_region1_Empty, MnvH1D* mc_total_region1_Empty,  MnvH1D* Aluminium_region1_Empty,
             MnvH1D* data_region2_Empty, MnvH1D* mc_total_region2_Empty,  MnvH1D* Aluminium_region2_Empty,
             MnvH1D* data_region3_Empty, MnvH1D* mc_total_region3_Empty,  MnvH1D* Aluminium_region3_Empty,
             MnvH1D* data_region4_Empty, MnvH1D* mc_total_region4_Empty,  MnvH1D* Aluminium_region4_Empty,
             std::string Hist_title, std::string xaxislabel)
             {

              TCanvas* c = new TCanvas("c","c",800, 800);

               MnvPlotter* plotter = new MnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
               TH1D* h_data_Total_Empty = new TH1D(data_region1_Empty->GetCVHistoWithError());
               TH1D* h_data_region1_Empty = new TH1D(data_region1_Empty->GetCVHistoWithError());
               TH1D* h_data_region2_Empty= new TH1D(data_region2_Empty->GetCVHistoWithError());
               TH1D* h_data_region3_Empty= new TH1D(data_region3_Empty->GetCVHistoWithError());
               TH1D* h_data_region4_Empty= new TH1D(data_region4_Empty->GetCVHistoWithError());

               h_data_Total_Empty->Add(h_data_region2_Empty);
               h_data_Total_Empty->Add(h_data_region3_Empty);
               h_data_Total_Empty->Add(h_data_region4_Empty);

              TH1D* tmpRatio_Data_Region1 = new TH1D(data_region1_Full->GetCVHistoWithError());
              TH1D* tmpRatio_Total_Data = new TH1D(data_region1_Full->GetCVHistoWithError());
              tmpRatio_Data_Region1->Divide(tmpRatio_Data_Region1, h_data_region1_Empty);

              TH1D* tmpRatio_Data_Region2 = new TH1D(data_region2_Full->GetCVHistoWithError());
              tmpRatio_Total_Data->Add(tmpRatio_Data_Region2);
              tmpRatio_Data_Region2->Divide(tmpRatio_Data_Region2, h_data_region2_Empty);

              TH1D* tmpRatio_Data_Region3 = new TH1D(data_region3_Full->GetCVHistoWithError());
              tmpRatio_Total_Data->Add(tmpRatio_Data_Region3);
              tmpRatio_Data_Region3->Divide(tmpRatio_Data_Region3, h_data_region3_Empty);

              TH1D* tmpRatio_Data_Region4 = new TH1D(data_region4_Full->GetCVHistoWithError());
              tmpRatio_Total_Data->Add(tmpRatio_Data_Region4);
              tmpRatio_Data_Region4->Divide(tmpRatio_Data_Region4, h_data_region4_Empty);

              tmpRatio_Total_Data->Divide(tmpRatio_Total_Data, h_data_Total_Empty );

              TH1D* tmpRatio_MC_total = new TH1D(mc_total_region1_Full->GetCVHistoWithError());
              TH1D* h_mc_total_region1_Full = new TH1D(mc_total_region1_Full->GetCVHistoWithError());
              TH1D* h_mc_total_region2_Full = new TH1D(mc_total_region2_Full->GetCVHistoWithError());
              TH1D* h_mc_total_region3_Full = new TH1D(mc_total_region3_Full->GetCVHistoWithError());
              TH1D* h_mc_total_region4_Full = new TH1D(mc_total_region4_Full->GetCVHistoWithError());

              tmpRatio_MC_total->Add(h_mc_total_region2_Full);
              tmpRatio_MC_total->Add(h_mc_total_region3_Full);
              tmpRatio_MC_total->Add(h_mc_total_region4_Full);

              TH1D* h_mc_total_Empty = new TH1D(mc_total_region1_Empty->GetCVHistoWithError());
              TH1D* h_mc_total_region1_Empty = new TH1D(mc_total_region1_Empty->GetCVHistoWithError());
              TH1D* h_mc_total_region2_Empty = new TH1D(mc_total_region2_Empty->GetCVHistoWithError());
              TH1D* h_mc_total_region3_Empty = new TH1D(mc_total_region3_Empty->GetCVHistoWithError());
              TH1D* h_mc_total_region4_Empty = new TH1D(mc_total_region4_Empty->GetCVHistoWithError());

              h_mc_total_Empty->Add(h_mc_total_region2_Empty);
              h_mc_total_Empty->Add(h_mc_total_region3_Empty);
              h_mc_total_Empty->Add(h_mc_total_region4_Empty);

              tmpRatio_MC_total->Divide(tmpRatio_MC_total, h_mc_total_Empty);
              tmpRatio_MC_total->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));

              TH1D* tmpRatio_Alregion1 = new TH1D(Aluminium_region1_Full->GetCVHistoWithError());
              TH1D* tmpRatio_Al_Empty_total = new TH1D(Aluminium_region1_Empty->GetCVHistoWithError());
              TH1D* tmpRatio_Al_total = new TH1D(Aluminium_region1_Full->GetCVHistoWithError());
              tmpRatio_Alregion1->Divide(tmpRatio_Alregion1, tmpRatio_Al_Empty_total);

              TH1D* tmpRatio_Alregion2 = new TH1D(Aluminium_region2_Full->GetCVHistoWithError());
              TH1D* tmpRatio_Alregion2_empty = new TH1D(Aluminium_region2_Empty->GetCVHistoWithError());
              tmpRatio_Al_total->Add(tmpRatio_Alregion2);
              tmpRatio_Al_Empty_total->Add(tmpRatio_Alregion2_empty);
              tmpRatio_Alregion2->Divide(tmpRatio_Alregion2 , Aluminium_region2_Empty);

              TH1D* tmpRatio_Alregion3 = new TH1D(Aluminium_region3_Full->GetCVHistoWithError());
              TH1D* tmpRatio_Alregion3_empty = new TH1D(Aluminium_region3_Empty->GetCVHistoWithError());
              tmpRatio_Al_total->Add(tmpRatio_Alregion3);
              tmpRatio_Al_Empty_total->Add(tmpRatio_Alregion3_empty);
              tmpRatio_Alregion3->Divide(tmpRatio_Alregion3 , tmpRatio_Alregion3_empty);

              TH1D* tmpRatio_Alregion4 = new TH1D(Aluminium_region4_Full->GetCVHistoWithError());
              TH1D* tmpRatio_Alregion4_empty = new TH1D(Aluminium_region4_Empty->GetCVHistoWithError());

              tmpRatio_Al_total->Add(tmpRatio_Alregion4);
              tmpRatio_Al_Empty_total->Add(tmpRatio_Alregion4_empty);

              tmpRatio_Alregion4->Divide(tmpRatio_Alregion4, Aluminium_region4_Empty);
              tmpRatio_Al_total->Divide(tmpRatio_Al_total, tmpRatio_Al_Empty_total);



              Color_AluminiumHistsForLines(tmpRatio_Alregion1, tmpRatio_Alregion2, tmpRatio_Alregion3,  tmpRatio_Alregion4);

              plotter->axis_title_size_x = 0.07;
              plotter->axis_title_offset_y = .4;
              plotter->axis_title_offset_x = .9;
              plotter->axis_title_size_y = 0.04;
              plotter->axis_label_size = 0.02;
              gPad->SetGridx(); // vertical grid
              gPad->SetGridy(); // vertical grid

              tmpRatio_MC_total->SetMinimum( -1.0 );
              tmpRatio_MC_total->SetMaximum( 6.0 );

              tmpRatio_MC_total->GetYaxis()->SetTitle("#frac{NEvent [Full]}{NEvent[Empty]}" );
              tmpRatio_MC_total->GetXaxis()->SetTitleFont(plotter->axis_title_font_x);
              tmpRatio_MC_total->GetYaxis()->SetTitleFont(plotter->axis_title_font_y);
              tmpRatio_MC_total->GetXaxis()->SetTitleSize(plotter->axis_title_size_x);
              tmpRatio_MC_total->GetYaxis()->SetTitleSize(plotter->axis_title_size_y);
              tmpRatio_MC_total->GetXaxis()->SetLabelFont(plotter->axis_label_font);
              tmpRatio_MC_total->GetYaxis()->SetLabelFont(plotter->axis_label_font);
              tmpRatio_MC_total->GetXaxis()->SetLabelSize(plotter->axis_label_size);
              tmpRatio_MC_total->GetYaxis()->SetLabelSize(plotter->axis_label_size);
              tmpRatio_MC_total->GetXaxis()->CenterTitle(kTRUE);
              tmpRatio_MC_total->GetYaxis()->CenterTitle(kTRUE);
              tmpRatio_MC_total->SetMarkerStyle(0);
              tmpRatio_Al_total->SetMarkerStyle(0);
              tmpRatio_Al_total->SetLineColor(kBlack);
              tmpRatio_MC_total->GetXaxis()->SetNdivisions(509);

              tmpRatio_MC_total->SetLineColor(kRed);
              tmpRatio_MC_total->Draw("hist");

              tmpRatio_Total_Data->SetMarkerStyle(29);
              tmpRatio_Data_Region1->SetMarkerStyle(24);
              tmpRatio_Data_Region2->SetMarkerStyle(25);
              tmpRatio_Data_Region3->SetMarkerStyle(26);
              tmpRatio_Data_Region4->SetMarkerStyle(32);
              tmpRatio_MC_total->SetLineWidth(3);
              tmpRatio_Al_total->SetLineWidth(3);
              tmpRatio_Alregion1->SetLineWidth(2);
              tmpRatio_Alregion2->SetLineWidth(2);
              tmpRatio_Alregion3->SetLineWidth(2);
              tmpRatio_Alregion4->SetLineWidth(2);
              tmpRatio_Al_total->SetLineStyle(3);
              tmpRatio_Al_total->SetFillStyle(0);
              tmpRatio_Alregion1->SetFillStyle(0);
              tmpRatio_Alregion2->SetFillStyle(0);
              tmpRatio_Alregion3->SetFillStyle(0);
              tmpRatio_Alregion4->SetFillStyle(0);

              tmpRatio_Alregion1->Draw(" same hist");
              tmpRatio_Alregion2->Draw(" same hist");
              tmpRatio_Alregion3->Draw(" same hist");
              tmpRatio_Alregion4->Draw(" same hist");
              tmpRatio_Al_total->Draw("  same hist");

              TLine ratio_1;
              ratio_1.SetLineWidth(1);
              ratio_1.SetLineStyle(7);
              ratio_1.SetLineColor(kBlue);
              double line_min = tmpRatio_MC_total->GetBinLowEdge(1);
              double line_max = tmpRatio_MC_total->GetBinLowEdge(tmpRatio_MC_total->GetNbinsX()+1);
              ratio_1.DrawLine(line_min,1,line_max,1);



              //std::cout<<"Finshed Drawing Hist "<<std::endl;
              // Add Data Plot
              tmpRatio_Total_Data->Draw("SAME E1 X0");
              tmpRatio_Data_Region1->Draw("SAME E1 X0");
              tmpRatio_Data_Region2->Draw("SAME E1 X0");
              tmpRatio_Data_Region3->Draw("SAME E1 X0");
              tmpRatio_Data_Region4->Draw("SAME E1 X0");


              // Add Legend
              TLegend *legend = new TLegend(0.85,0.7,0.98,0.98);
              legend->AddEntry(tmpRatio_Total_Data,   "Total data");           //0.56,0.50,0.9,0.94)
              legend->AddEntry(tmpRatio_Data_Region1, "data USCap");
              legend->AddEntry(tmpRatio_Data_Region2, "data Barrel");
              legend->AddEntry(tmpRatio_Data_Region3, "data DSCap");
              legend->AddEntry(tmpRatio_Data_Region4, "data Concave");
              legend->AddEntry(tmpRatio_MC_total,  "MC Total",        "l");
              legend->AddEntry(tmpRatio_Al_total,  "MC Total Al",     "l");
              legend->AddEntry(tmpRatio_Alregion1, "^{27}Al USCap",   "l");
              legend->AddEntry(tmpRatio_Alregion2, "^{27}Al Barrel",  "l");
              legend->AddEntry(tmpRatio_Alregion3, "^{27}Al DSCap",   "l");
              legend->AddEntry(tmpRatio_Alregion4, "^{27}Al Concave", "l");
              legend->SetTextSize(0.015);
              legend->SetTextFont(42);
              legend->Draw();



              // Plot Output
              plotter->AddHistoTitle(Hist_title.c_str(),.04);
              plotter->WritePreliminary("TL", .025, 0, 0, false);
              c->Update();
              c->Print(pdf_label.c_str(),"pdf");

              delete legend;
              delete c;
              delete tmpRatio_Data_Region1;
              delete tmpRatio_Data_Region2;
              delete tmpRatio_Data_Region3;
              delete tmpRatio_Data_Region4;
              delete tmpRatio_Alregion1;
              delete tmpRatio_Alregion2;
              delete tmpRatio_Alregion3;
              delete tmpRatio_Alregion4;
              delete tmpRatio_MC_total;
              delete plotter;
              delete h_mc_total_Empty;
              delete h_mc_total_region1_Full;
              delete h_mc_total_region2_Full;
              delete h_mc_total_region3_Full;
              delete h_mc_total_region4_Full;
              delete h_mc_total_region1_Empty;
              delete h_mc_total_region2_Empty;
              delete h_mc_total_region3_Empty;
              delete h_mc_total_region4_Empty;
              delete tmpRatio_Al_total;

            }
////////////////////////////////////
void Helium_3CryoRegionsSideBandTool::MakeRatioPlot_forXYZR(std::string Title, int ind){

  std::string FinalTitle;

  FinalTitle =  Title + "Ratio #frac{Full}{Empty}";

  Plot_Al_RatioMCANDData_Full_OverEmpty(PDF_printingLabel_input, ind,
         Full_UpstreamCap.MnvH1D_Vertex_X_data,          Full_UpstreamCap.MnvH1D_Vertex_X_mc_total,          Full_UpstreamCap.MnvH1D_Vertex_X_Aluminium[ind],
         Full_Barrel.MnvH1D_Vertex_X_data,               Full_Barrel.MnvH1D_Vertex_X_mc_total,               Full_Barrel.MnvH1D_Vertex_X_Aluminium[ind],
         Full_DownstreamCap.MnvH1D_Vertex_X_data,        Full_DownstreamCap.MnvH1D_Vertex_X_mc_total,        Full_DownstreamCap.MnvH1D_Vertex_X_Aluminium[ind],
         Full_DownstreamConcaveCap.MnvH1D_Vertex_X_data, Full_DownstreamConcaveCap.MnvH1D_Vertex_X_mc_total, Full_DownstreamConcaveCap.MnvH1D_Vertex_X_Aluminium[ind],

         Empty_UpstreamCap.MnvH1D_Vertex_X_data,          Empty_UpstreamCap.MnvH1D_Vertex_X_mc_total,          Empty_UpstreamCap.MnvH1D_Vertex_X_Aluminium[ind],
         Empty_Barrel.MnvH1D_Vertex_X_data,               Empty_Barrel.MnvH1D_Vertex_X_mc_total,               Empty_Barrel.MnvH1D_Vertex_X_Aluminium[ind],
         Empty_DownstreamCap.MnvH1D_Vertex_X_data,        Empty_DownstreamCap.MnvH1D_Vertex_X_mc_total,        Empty_DownstreamCap.MnvH1D_Vertex_X_Aluminium[ind],
         Empty_DownstreamConcaveCap.MnvH1D_Vertex_X_data, Empty_DownstreamConcaveCap.MnvH1D_Vertex_X_mc_total, Empty_DownstreamConcaveCap.MnvH1D_Vertex_X_Aluminium[ind],
       FinalTitle, "Vertex X [mm]");

       Plot_Al_RatioMCANDData_Full_OverEmpty_Combined(PDF_printingLabel_input, ind,
              Full_UpstreamCap.MnvH1D_Vertex_X_data,          Full_UpstreamCap.MnvH1D_Vertex_X_mc_total,          Full_UpstreamCap.MnvH1D_Vertex_X_Aluminium[ind],
              Full_Barrel.MnvH1D_Vertex_X_data,               Full_Barrel.MnvH1D_Vertex_X_mc_total,               Full_Barrel.MnvH1D_Vertex_X_Aluminium[ind],
              Full_DownstreamCap.MnvH1D_Vertex_X_data,        Full_DownstreamCap.MnvH1D_Vertex_X_mc_total,        Full_DownstreamCap.MnvH1D_Vertex_X_Aluminium[ind],
              Full_DownstreamConcaveCap.MnvH1D_Vertex_X_data, Full_DownstreamConcaveCap.MnvH1D_Vertex_X_mc_total, Full_DownstreamConcaveCap.MnvH1D_Vertex_X_Aluminium[ind],

              Empty_UpstreamCap.MnvH1D_Vertex_X_data,          Empty_UpstreamCap.MnvH1D_Vertex_X_mc_total,          Empty_UpstreamCap.MnvH1D_Vertex_X_Aluminium[ind],
              Empty_Barrel.MnvH1D_Vertex_X_data,               Empty_Barrel.MnvH1D_Vertex_X_mc_total,               Empty_Barrel.MnvH1D_Vertex_X_Aluminium[ind],
              Empty_DownstreamCap.MnvH1D_Vertex_X_data,        Empty_DownstreamCap.MnvH1D_Vertex_X_mc_total,        Empty_DownstreamCap.MnvH1D_Vertex_X_Aluminium[ind],
              Empty_DownstreamConcaveCap.MnvH1D_Vertex_X_data, Empty_DownstreamConcaveCap.MnvH1D_Vertex_X_mc_total, Empty_DownstreamConcaveCap.MnvH1D_Vertex_X_Aluminium[ind],
            FinalTitle, "Vertex X [mm]");

  Plot_Al_RatioMCANDData_Full_OverEmpty(PDF_printingLabel_input, ind,
    Full_UpstreamCap.MnvH1D_Vertex_Y_data,          Full_UpstreamCap.MnvH1D_Vertex_Y_mc_total,          Full_UpstreamCap.MnvH1D_Vertex_Y_Aluminium[ind],
    Full_Barrel.MnvH1D_Vertex_Y_data,               Full_Barrel.MnvH1D_Vertex_Y_mc_total,               Full_Barrel.MnvH1D_Vertex_Y_Aluminium[ind],
    Full_DownstreamCap.MnvH1D_Vertex_Y_data,        Full_DownstreamCap.MnvH1D_Vertex_Y_mc_total,        Full_DownstreamCap.MnvH1D_Vertex_Y_Aluminium[ind],
    Full_DownstreamConcaveCap.MnvH1D_Vertex_Y_data, Full_DownstreamConcaveCap.MnvH1D_Vertex_Y_mc_total, Full_DownstreamConcaveCap.MnvH1D_Vertex_Y_Aluminium[ind],

    Empty_UpstreamCap.MnvH1D_Vertex_Y_data,          Empty_UpstreamCap.MnvH1D_Vertex_Y_mc_total,          Empty_UpstreamCap.MnvH1D_Vertex_Y_Aluminium[ind],
    Empty_Barrel.MnvH1D_Vertex_Y_data,               Empty_Barrel.MnvH1D_Vertex_Y_mc_total,               Empty_Barrel.MnvH1D_Vertex_Y_Aluminium[ind],
    Empty_DownstreamCap.MnvH1D_Vertex_Y_data,        Empty_DownstreamCap.MnvH1D_Vertex_Y_mc_total,        Empty_DownstreamCap.MnvH1D_Vertex_Y_Aluminium[ind],
    Empty_DownstreamConcaveCap.MnvH1D_Vertex_Y_data, Empty_DownstreamConcaveCap.MnvH1D_Vertex_Y_mc_total, Empty_DownstreamConcaveCap.MnvH1D_Vertex_Y_Aluminium[ind],
    FinalTitle, "Vertex Y [mm]");

    Plot_Al_RatioMCANDData_Full_OverEmpty_Combined(PDF_printingLabel_input, ind,
      Full_UpstreamCap.MnvH1D_Vertex_Y_data,          Full_UpstreamCap.MnvH1D_Vertex_Y_mc_total,          Full_UpstreamCap.MnvH1D_Vertex_Y_Aluminium[ind],
      Full_Barrel.MnvH1D_Vertex_Y_data,               Full_Barrel.MnvH1D_Vertex_Y_mc_total,               Full_Barrel.MnvH1D_Vertex_Y_Aluminium[ind],
      Full_DownstreamCap.MnvH1D_Vertex_Y_data,        Full_DownstreamCap.MnvH1D_Vertex_Y_mc_total,        Full_DownstreamCap.MnvH1D_Vertex_Y_Aluminium[ind],
      Full_DownstreamConcaveCap.MnvH1D_Vertex_Y_data, Full_DownstreamConcaveCap.MnvH1D_Vertex_Y_mc_total, Full_DownstreamConcaveCap.MnvH1D_Vertex_Y_Aluminium[ind],

      Empty_UpstreamCap.MnvH1D_Vertex_Y_data,          Empty_UpstreamCap.MnvH1D_Vertex_Y_mc_total,          Empty_UpstreamCap.MnvH1D_Vertex_Y_Aluminium[ind],
      Empty_Barrel.MnvH1D_Vertex_Y_data,               Empty_Barrel.MnvH1D_Vertex_Y_mc_total,               Empty_Barrel.MnvH1D_Vertex_Y_Aluminium[ind],
      Empty_DownstreamCap.MnvH1D_Vertex_Y_data,        Empty_DownstreamCap.MnvH1D_Vertex_Y_mc_total,        Empty_DownstreamCap.MnvH1D_Vertex_Y_Aluminium[ind],
      Empty_DownstreamConcaveCap.MnvH1D_Vertex_Y_data, Empty_DownstreamConcaveCap.MnvH1D_Vertex_Y_mc_total, Empty_DownstreamConcaveCap.MnvH1D_Vertex_Y_Aluminium[ind],
      FinalTitle, "Vertex Y [mm]");

  Plot_Al_RatioMCANDData_Full_OverEmpty(PDF_printingLabel_input, ind,
    Full_UpstreamCap.MnvH1D_Vertex_Z_data,          Full_UpstreamCap.MnvH1D_Vertex_Z_mc_total,          Full_UpstreamCap.MnvH1D_Vertex_Z_Aluminium[ind],
    Full_Barrel.MnvH1D_Vertex_Z_data,               Full_Barrel.MnvH1D_Vertex_Z_mc_total,               Full_Barrel.MnvH1D_Vertex_Z_Aluminium[ind],
    Full_DownstreamCap.MnvH1D_Vertex_Z_data,        Full_DownstreamCap.MnvH1D_Vertex_Z_mc_total,        Full_DownstreamCap.MnvH1D_Vertex_Z_Aluminium[ind],
    Full_DownstreamConcaveCap.MnvH1D_Vertex_Z_data, Full_DownstreamConcaveCap.MnvH1D_Vertex_Z_mc_total, Full_DownstreamConcaveCap.MnvH1D_Vertex_Z_Aluminium[ind],

    Empty_UpstreamCap.MnvH1D_Vertex_Z_data,          Empty_UpstreamCap.MnvH1D_Vertex_Z_mc_total,          Empty_UpstreamCap.MnvH1D_Vertex_Z_Aluminium[ind],
    Empty_Barrel.MnvH1D_Vertex_Z_data,               Empty_Barrel.MnvH1D_Vertex_Z_mc_total,               Empty_Barrel.MnvH1D_Vertex_Z_Aluminium[ind],
    Empty_DownstreamCap.MnvH1D_Vertex_Z_data,        Empty_DownstreamCap.MnvH1D_Vertex_Z_mc_total,        Empty_DownstreamCap.MnvH1D_Vertex_Z_Aluminium[ind],
    Empty_DownstreamConcaveCap.MnvH1D_Vertex_Z_data, Empty_DownstreamConcaveCap.MnvH1D_Vertex_Z_mc_total, Empty_DownstreamConcaveCap.MnvH1D_Vertex_Z_Aluminium[ind],
    FinalTitle, "Vertex Z [mm]");

    Plot_Al_RatioMCANDData_Full_OverEmpty_Combined(PDF_printingLabel_input, ind,
      Full_UpstreamCap.MnvH1D_Vertex_Z_data,          Full_UpstreamCap.MnvH1D_Vertex_Z_mc_total,          Full_UpstreamCap.MnvH1D_Vertex_Z_Aluminium[ind],
      Full_Barrel.MnvH1D_Vertex_Z_data,               Full_Barrel.MnvH1D_Vertex_Z_mc_total,               Full_Barrel.MnvH1D_Vertex_Z_Aluminium[ind],
      Full_DownstreamCap.MnvH1D_Vertex_Z_data,        Full_DownstreamCap.MnvH1D_Vertex_Z_mc_total,        Full_DownstreamCap.MnvH1D_Vertex_Z_Aluminium[ind],
      Full_DownstreamConcaveCap.MnvH1D_Vertex_Z_data, Full_DownstreamConcaveCap.MnvH1D_Vertex_Z_mc_total, Full_DownstreamConcaveCap.MnvH1D_Vertex_Z_Aluminium[ind],

      Empty_UpstreamCap.MnvH1D_Vertex_Z_data,          Empty_UpstreamCap.MnvH1D_Vertex_Z_mc_total,          Empty_UpstreamCap.MnvH1D_Vertex_Z_Aluminium[ind],
      Empty_Barrel.MnvH1D_Vertex_Z_data,               Empty_Barrel.MnvH1D_Vertex_Z_mc_total,               Empty_Barrel.MnvH1D_Vertex_Z_Aluminium[ind],
      Empty_DownstreamCap.MnvH1D_Vertex_Z_data,        Empty_DownstreamCap.MnvH1D_Vertex_Z_mc_total,        Empty_DownstreamCap.MnvH1D_Vertex_Z_Aluminium[ind],
      Empty_DownstreamConcaveCap.MnvH1D_Vertex_Z_data, Empty_DownstreamConcaveCap.MnvH1D_Vertex_Z_mc_total, Empty_DownstreamConcaveCap.MnvH1D_Vertex_Z_Aluminium[ind],
      FinalTitle, "Vertex Z [mm]");



    Plot_Al_RatioMCANDData_Full_OverEmpty(PDF_printingLabel_input, ind,
      Full_UpstreamCap.MnvH1D_Vertex_R_data,          Full_UpstreamCap.MnvH1D_Vertex_R_mc_total,          Full_UpstreamCap.MnvH1D_Vertex_R_Aluminium[ind],
      Full_Barrel.MnvH1D_Vertex_R_data,               Full_Barrel.MnvH1D_Vertex_R_mc_total,               Full_Barrel.MnvH1D_Vertex_R_Aluminium[ind],
      Full_DownstreamCap.MnvH1D_Vertex_R_data,        Full_DownstreamCap.MnvH1D_Vertex_R_mc_total,        Full_DownstreamCap.MnvH1D_Vertex_R_Aluminium[ind],
      Full_DownstreamConcaveCap.MnvH1D_Vertex_R_data, Full_DownstreamConcaveCap.MnvH1D_Vertex_R_mc_total, Full_DownstreamConcaveCap.MnvH1D_Vertex_R_Aluminium[ind],

      Empty_UpstreamCap.MnvH1D_Vertex_R_data,          Empty_UpstreamCap.MnvH1D_Vertex_R_mc_total,          Empty_UpstreamCap.MnvH1D_Vertex_R_Aluminium[ind],
      Empty_Barrel.MnvH1D_Vertex_R_data,               Empty_Barrel.MnvH1D_Vertex_R_mc_total,               Empty_Barrel.MnvH1D_Vertex_R_Aluminium[ind],
      Empty_DownstreamCap.MnvH1D_Vertex_R_data,        Empty_DownstreamCap.MnvH1D_Vertex_R_mc_total,        Empty_DownstreamCap.MnvH1D_Vertex_R_Aluminium[ind],
      Empty_DownstreamConcaveCap.MnvH1D_Vertex_R_data, Empty_DownstreamConcaveCap.MnvH1D_Vertex_R_mc_total, Empty_DownstreamConcaveCap.MnvH1D_Vertex_R_Aluminium[ind],
      FinalTitle, "Vertex R [mm]");

      Plot_Al_RatioMCANDData_Full_OverEmpty_Combined(PDF_printingLabel_input, ind,
        Full_UpstreamCap.MnvH1D_Vertex_R_data,          Full_UpstreamCap.MnvH1D_Vertex_R_mc_total,          Full_UpstreamCap.MnvH1D_Vertex_R_Aluminium[ind],
        Full_Barrel.MnvH1D_Vertex_R_data,               Full_Barrel.MnvH1D_Vertex_R_mc_total,               Full_Barrel.MnvH1D_Vertex_R_Aluminium[ind],
        Full_DownstreamCap.MnvH1D_Vertex_R_data,        Full_DownstreamCap.MnvH1D_Vertex_R_mc_total,        Full_DownstreamCap.MnvH1D_Vertex_R_Aluminium[ind],
        Full_DownstreamConcaveCap.MnvH1D_Vertex_R_data, Full_DownstreamConcaveCap.MnvH1D_Vertex_R_mc_total, Full_DownstreamConcaveCap.MnvH1D_Vertex_R_Aluminium[ind],

        Empty_UpstreamCap.MnvH1D_Vertex_R_data,          Empty_UpstreamCap.MnvH1D_Vertex_R_mc_total,          Empty_UpstreamCap.MnvH1D_Vertex_R_Aluminium[ind],
        Empty_Barrel.MnvH1D_Vertex_R_data,               Empty_Barrel.MnvH1D_Vertex_R_mc_total,               Empty_Barrel.MnvH1D_Vertex_R_Aluminium[ind],
        Empty_DownstreamCap.MnvH1D_Vertex_R_data,        Empty_DownstreamCap.MnvH1D_Vertex_R_mc_total,        Empty_DownstreamCap.MnvH1D_Vertex_R_Aluminium[ind],
        Empty_DownstreamConcaveCap.MnvH1D_Vertex_R_data, Empty_DownstreamConcaveCap.MnvH1D_Vertex_R_mc_total, Empty_DownstreamConcaveCap.MnvH1D_Vertex_R_Aluminium[ind],
        FinalTitle, "Vertex R [mm]");


}

////////////////////////////////////
void Helium_3CryoRegionsSideBandTool::Plot_MigHist(MnvH2D *hist, std::string Title_string,
     std::string xaxislabel_string, std::string yaxislabel_string,  std::string zaxislabel_string,
  std::string pdf_label){

  TCanvas* can = new TCanvas("c","c",800, 800);
  MnvPlotter* plotter = new MnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);

 Draw2DHist_Migration_Histpointer(hist,  Title_string,
   xaxislabel_string, yaxislabel_string,  zaxislabel_string,
 pdf_label, can, plotter);

    delete can;
    delete plotter;

}
void Helium_3CryoRegionsSideBandTool::Plot_MigHist_RowNormalize(MnvH2D *hist, std::string Title_string,
     std::string xaxislabel_string, std::string yaxislabel_string,  std::string zaxislabel_string,
  std::string pdf_label){

  TCanvas* can = new TCanvas("c","c",800, 800);
  MnvPlotter* plotter = new MnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  MnvH2D *h_mig_rowNorm = (MnvH2D*)hist->Clone("h_mig_Full_rowNorm");

  rowNormalize(*h_mig_rowNorm);

 Draw2DHist_Migration_Histpointer(h_mig_rowNorm,  Title_string,
   xaxislabel_string, yaxislabel_string,  zaxislabel_string,
 pdf_label, can, plotter);

    delete can;
    delete plotter;
    delete h_mig_rowNorm;

}

void Helium_3CryoRegionsSideBandTool::Plot_MigHist_ColNormalize(MnvH2D *hist, std::string Title_string,
     std::string xaxislabel_string, std::string yaxislabel_string,  std::string zaxislabel_string,
  std::string pdf_label){

  TCanvas* can = new TCanvas("c","c",800, 800);
  MnvPlotter* plotter = new MnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  MnvH2D *h_mig_colNorm = (MnvH2D*)hist->Clone("h_mig_colNorm");

  colNormalize(*h_mig_colNorm);

 Draw2DHist_Migration_Histpointer(h_mig_colNorm,  Title_string,
   xaxislabel_string, yaxislabel_string,  zaxislabel_string,
 pdf_label, can, plotter);

    delete can;
    delete plotter;
    delete h_mig_colNorm;

}
/////////////////////////////////////////////////////////////////
void Helium_3CryoRegionsSideBandTool::Plot_MigHist(Helium3SideBand &sb,
  std::string pdf_label, std::string Title_input){
std::string Title;

Title =     "Vertex X " + Title_input;
Plot_MigHist(sb.MnvH2D_Mig_vertex_X, Title,
  "RECO Vertex X", "TRUE Vertex X",  "NEvents",
  pdf_label);

Plot_MigHist_RowNormalize(sb.MnvH2D_Mig_vertex_X, Title,
    "RECO Vertex X", "TRUE Vertex X",  "NEvents[RowNormalized]",
    pdf_label);

Title =  "Vertex Y " + Title_input;
Plot_MigHist(sb.MnvH2D_Mig_vertex_Y, Title,
  "RECO Vertex Y", "TRUE Vertex Y",  "NEvents",
  pdf_label);

Plot_MigHist_RowNormalize(sb.MnvH2D_Mig_vertex_Y, Title,
    "RECO Vertex Y", "TRUE Vertex Y",  "NEvents[RowNormalized]",
    pdf_label);


Title =     "Vertex R " + Title_input;
Plot_MigHist(sb.MnvH2D_Mig_vertex_R, Title,
  "RECO Vertex R", "TRUE Vertex R",  "NEvents",
  pdf_label);

Plot_MigHist_RowNormalize(sb.MnvH2D_Mig_vertex_R, Title,
    "RECO Vertex R", "TRUE Vertex R",  "NEvents[RowNormalized]",
    pdf_label);


Title =     "Vertex Z " + Title_input;
Plot_MigHist(sb.MnvH2D_Mig_vertex_Z, Title,
  "RECO Vertex Z", "TRUE Vertex Z",  "NEvents",
  pdf_label);

Plot_MigHist_RowNormalize(sb.MnvH2D_Mig_vertex_Z, Title,
    "RECO Vertex Z", "TRUE Vertex Z",  "NEvents [RowNormalized]",
    pdf_label);

}

void Helium_3CryoRegionsSideBandTool::Plot_Empty_MigHist(std::string Title_input){
std::string Title;
Title = Title_input + "E[(all)]" ;
    Plot_MigHist(Empty,LatexPdfLabel, Title);
    Title = Title_input + "[USCap] E[(all)]" ;
    Plot_MigHist(Empty_UpstreamCap,LatexPdfLabel, Title);
    Title = Title_input + "[barrel] E[(all)]" ;
    Plot_MigHist(Empty_Barrel,LatexPdfLabel, Title);
    Title = Title_input + "[DSCap] E[(all)]" ;
    Plot_MigHist(Empty_DownstreamCap,LatexPdfLabel, Title);
    Title = Title_input + "[DS Concave] E[(all)]";
    Plot_MigHist(Empty_DownstreamConcaveCap,LatexPdfLabel, Title);

}
void Helium_3CryoRegionsSideBandTool::Plot_Full_MigHist(std::string Title_input){
std::string Title;
Title = Title_input + " F[(all)]";
    Plot_MigHist(Full,LatexPdfLabel, Title);
    Title = Title_input + "[USCap] F[(all)]" ;
    Plot_MigHist(Full_UpstreamCap,LatexPdfLabel, Title);
    Title = Title_input + "[barrel] F[(all)]" ;
    Plot_MigHist(Full_Barrel,LatexPdfLabel, Title);
    Title = Title_input + "[DSCap] F[(all)]";
    Plot_MigHist(Full_DownstreamCap,LatexPdfLabel, Title);
    Title = Title_input + "[DS Concave] F[(all)]" ;
    Plot_MigHist(Full_DownstreamConcaveCap,LatexPdfLabel, Title);

}

void Helium_3CryoRegionsSideBandTool::Plot_All_MigHist(std::string Title_input){

Plot_Full_MigHist(Title_input);
Plot_Empty_MigHist(Title_input);

}

/////////////////////////////////////
void Helium_3CryoRegionsSideBandTool::Plot_Resolution_HistwithError(MnvH1D* input_hist,
  std::string pdf_label, std::string Hist_title, std::string xaxislabel, bool withfitorRMS, bool PrintRMS_percentage){
    bool PrintallErrorGroups=false;
    bool PrintErrors = false;
    bool doBinwidth = true;
    bool Setgrid = true;
    bool AreaNormalized = true;
    char Hist_title_char[1024];
    sprintf(Hist_title_char, "%s", Hist_title.c_str());
  //  std::cout<<"Plot_Resolution_HistwithError"<<std::endl;
    //std::cout<<"Drawing: "<< Hist_title_char<<std::endl;
    if(withfitorRMS==true){
      DrawCVAndError_FromHIST_withFit(input_hist, Hist_title_char ,xaxislabel, "NEvents",
      pdf_label,  Setgrid, PrintErrors,  PrintallErrorGroups);
    }

    else{
      DrawCVAndError_FromHIST_withRMS(input_hist, Hist_title_char ,xaxislabel, "NEvents", "mm",
      pdf_label,  Setgrid,  doBinwidth,   PrintErrors ,  PrintallErrorGroups, PrintRMS_percentage,  AreaNormalized );
    }

  }
  ////////////////////////////////////
void Helium_3CryoRegionsSideBandTool::Plot_Resolutions(Resolution_hists hists,
  std::string pdf_label, std::string Hist_title, std::string xaxislabel, bool withfitorRMS){
//std::cout<<"inside::Plot_Resolutions"<<std::endl;
bool ispercentage = true;
std::string Title;
std::string Axis_Title;
Axis_Title = xaxislabel + "TRUE - RECO [mm]";
Title = Hist_title + " [RECO cuts]";
Plot_Resolution_HistwithError(hists.MnvH1D_Resolution_RECO,
  pdf_label, Title,  Axis_Title,  withfitorRMS, !ispercentage);

Title = Hist_title + " [TRUE+RECO cuts]";
Axis_Title = xaxislabel + "TRUE - RECO";
Plot_Resolution_HistwithError(hists.MnvH1D_Resolution_TRUE_RECO,
      pdf_label, Title,  Axis_Title,  withfitorRMS, !ispercentage);

Title = Hist_title + " [RECO cuts]";
Axis_Title = xaxislabel + "(TRUE - RECO)/ True";
Plot_Resolution_HistwithError(hists.MnvH1D_percentageResolution_RECO,
  pdf_label, Title,  Axis_Title,  withfitorRMS, ispercentage);

Title = Hist_title + " [TRUE+RECO cuts]";
Axis_Title = xaxislabel + "(TRUE - RECO)/ True";
Plot_Resolution_HistwithError(hists.MnvH1D_percentageResolution_TRUE_RECO,
  pdf_label, Title,  Axis_Title,  withfitorRMS, ispercentage);

 }

 void Helium_3CryoRegionsSideBandTool::plot_Resolutions(Helium3SideBand &sb,
   std::string pdf_label, bool withfitorRMS, std::string Hist_title_sideband){

    // std::cout<<"inside::plot_Resolutions"<<std::endl;
    // std::cout<<"inside::plot_Resolutions::Vertex_X"<<std::endl;

  Plot_Resolutions(sb.Resolution_hists_Vertex_X,
        pdf_label,  Hist_title_sideband, "Vertex X [mm] ",  withfitorRMS);

   //std::cout<<"inside::plot_Resolutions::Vertex_Y"<<std::endl;
  Plot_Resolutions(sb.Resolution_hists_Vertex_Y,
    pdf_label,  Hist_title_sideband, "Vertex Y [mm] ",  withfitorRMS);

   //std::cout<<"inside::plot_Resolutions::Vertex_R"<<std::endl;
  Plot_Resolutions(sb.Resolution_hists_Vertex_R,
    pdf_label,  Hist_title_sideband, "Vertex R [mm] ",  withfitorRMS);

   //std::cout<<"inside::plot_Resolutions::Vertex_Z"<<std::endl;
  Plot_Resolutions(sb.Resolution_hists_Vertex_Z,
    pdf_label,  Hist_title_sideband, "Vertex Z [mm] ",  withfitorRMS);

   }

   void Helium_3CryoRegionsSideBandTool::plotEmpty_Resolutions(bool withfitorRMS){

     //std::cout<<"inside::plotEmpty_Resolutions"<<std::endl;

     std::string Hist_title_sideband;

     Hist_title_sideband = "Total Region [E(All)] ";
     plot_Resolutions(Empty,LatexPdfLabel,  withfitorRMS,  Hist_title_sideband);

     Hist_title_sideband = "[USCap] [E(All)] ";
     plot_Resolutions(Empty_UpstreamCap,LatexPdfLabel,  withfitorRMS,  Hist_title_sideband);

     Hist_title_sideband = "[Barrel]  [E(All)] ";
     plot_Resolutions(Empty_Barrel,LatexPdfLabel,  withfitorRMS,  Hist_title_sideband);

     Hist_title_sideband = "[DSCap] [E(All)]  ";
     plot_Resolutions(Empty_DownstreamCap,LatexPdfLabel,  withfitorRMS,  Hist_title_sideband);

     Hist_title_sideband = "[DSConcave] [E(All)]  ";
     plot_Resolutions(Empty_DownstreamConcaveCap ,LatexPdfLabel,  withfitorRMS,  Hist_title_sideband);

     }

     void Helium_3CryoRegionsSideBandTool::plotFull_Resolutions(bool withfitorRMS){


       std::string Hist_title_sideband;
       Hist_title_sideband = "Total Region [F(All)] ";
       plot_Resolutions(Full,LatexPdfLabel,  withfitorRMS,  Hist_title_sideband);

       Hist_title_sideband = "[USCap] [F(All)] ";
       plot_Resolutions(Full_UpstreamCap,LatexPdfLabel,  withfitorRMS,  Hist_title_sideband);

       Hist_title_sideband = "[Barrel][F(All)] ";
       plot_Resolutions(Full_Barrel,LatexPdfLabel,  withfitorRMS,  Hist_title_sideband);

       Hist_title_sideband = "[DSCap] [F(All)]  ";
       plot_Resolutions(Full_DownstreamCap,LatexPdfLabel,  withfitorRMS,  Hist_title_sideband);

       Hist_title_sideband = "[DSConcave] Region [F(All)]  ";
       plot_Resolutions(Full_DownstreamConcaveCap ,LatexPdfLabel,  withfitorRMS,  Hist_title_sideband);

       }

void Helium_3CryoRegionsSideBandTool::plotFull_Empty_Resolutions(bool withfitorRMS){
  plotEmpty_Resolutions( withfitorRMS);
  plotFull_Resolutions( withfitorRMS);

}

////////////////////////////////////
void Helium_3CryoRegionsSideBandTool::Plot(std::string pdf_label, double POT_ratio, int ind,
  Helium3SideBand &sb, XSec_Var3band &xsec_var,  std::string var_name, std::string Hist_title,
   std::string xaxislabel, int index , bool ApplyMaxY, double MaxY)
{
    Plot(pdf_label, ind, POT_ratio, sb.name, var_name,
                xsec_var.MnvH1D_data,
                xsec_var.MnvH1D_mc_total,
                xsec_var.MnvH1D_Helium[ind],
                xsec_var.MnvH1D_Aluminium[ind],
                xsec_var.MnvH1D_Carbon[ind],
                xsec_var.MnvH1D_Lead[ind],
                xsec_var.MnvH1D_Iron[ind],
                xsec_var.MnvH1D_Other[ind], Hist_title, xaxislabel, index, UseLogChi_Tool ,ApplyMaxY, MaxY );

}
////////////////////////////////////////////////////
void Helium_3CryoRegionsSideBandTool::Plot_Resolution_vertex_Material(std::string pdf_label, double POT_ratio, int ind,
  Helium3SideBand &sb_region1, Helium3SideBand &sb_region2, Helium3SideBand &sb_region3,
  Helium3SideBand &sb_region4, std::string histTitle){

std::string var;

var = histTitle +" Vertex X";
  Plot_regions_noData(pdf_label, ind, POT_ratio,
    sb_region1.Vertex_X_Resolution.MnvH1D_mc_total,
    sb_region1.Vertex_X_Resolution.MnvH1D_Helium[ind],
    sb_region1.Vertex_X_Resolution.MnvH1D_Aluminium[ind],
    sb_region1.Vertex_X_Resolution.MnvH1D_Carbon[ind],
    sb_region1.Vertex_X_Resolution.MnvH1D_Iron[ind],
    sb_region1.Vertex_X_Resolution.MnvH1D_Lead[ind],
    sb_region1.Vertex_X_Resolution.MnvH1D_Other[ind],

    sb_region2.Vertex_X_Resolution.MnvH1D_mc_total,
    sb_region2.Vertex_X_Resolution.MnvH1D_Helium[ind],
    sb_region2.Vertex_X_Resolution.MnvH1D_Aluminium[ind],
    sb_region2.Vertex_X_Resolution.MnvH1D_Carbon[ind],
    sb_region2.Vertex_X_Resolution.MnvH1D_Iron[ind],
    sb_region2.Vertex_X_Resolution.MnvH1D_Lead[ind],
    sb_region2.Vertex_X_Resolution.MnvH1D_Other[ind],

    sb_region3.Vertex_X_Resolution.MnvH1D_mc_total,
    sb_region3.Vertex_X_Resolution.MnvH1D_Helium[ind],
    sb_region3.Vertex_X_Resolution.MnvH1D_Aluminium[ind],
    sb_region3.Vertex_X_Resolution.MnvH1D_Carbon[ind],
    sb_region3.Vertex_X_Resolution.MnvH1D_Iron[ind],
    sb_region3.Vertex_X_Resolution.MnvH1D_Lead[ind],
    sb_region3.Vertex_X_Resolution.MnvH1D_Other[ind],

    sb_region4.Vertex_X_Resolution.MnvH1D_mc_total,
    sb_region4.Vertex_X_Resolution.MnvH1D_Helium[ind],
    sb_region4.Vertex_X_Resolution.MnvH1D_Aluminium[ind],
    sb_region4.Vertex_X_Resolution.MnvH1D_Carbon[ind],
    sb_region4.Vertex_X_Resolution.MnvH1D_Iron[ind],
    sb_region4.Vertex_X_Resolution.MnvH1D_Lead[ind],
    sb_region4.Vertex_X_Resolution.MnvH1D_Other[ind],

    var, "Vertex X TRUE - RECO [mm]");

    var = histTitle +" Vertex Y ";
Plot_regions_noData(pdf_label, ind, POT_ratio,
  sb_region1.Vertex_Y_Resolution.MnvH1D_mc_total,
  sb_region1.Vertex_Y_Resolution.MnvH1D_Helium[ind],
  sb_region1.Vertex_Y_Resolution.MnvH1D_Aluminium[ind],
  sb_region1.Vertex_Y_Resolution.MnvH1D_Carbon[ind],
  sb_region1.Vertex_Y_Resolution.MnvH1D_Iron[ind],
  sb_region1.Vertex_Y_Resolution.MnvH1D_Lead[ind],
  sb_region1.Vertex_Y_Resolution.MnvH1D_Other[ind],
  sb_region2.Vertex_Y_Resolution.MnvH1D_mc_total,
  sb_region2.Vertex_Y_Resolution.MnvH1D_Helium[ind],
  sb_region2.Vertex_Y_Resolution.MnvH1D_Aluminium[ind],
  sb_region2.Vertex_Y_Resolution.MnvH1D_Carbon[ind],
  sb_region2.Vertex_Y_Resolution.MnvH1D_Iron[ind],
  sb_region2.Vertex_Y_Resolution.MnvH1D_Lead[ind],
  sb_region2.Vertex_Y_Resolution.MnvH1D_Other[ind],
  sb_region3.Vertex_Y_Resolution.MnvH1D_mc_total,
  sb_region3.Vertex_Y_Resolution.MnvH1D_Helium[ind],
  sb_region3.Vertex_Y_Resolution.MnvH1D_Aluminium[ind],
  sb_region3.Vertex_Y_Resolution.MnvH1D_Carbon[ind],
  sb_region3.Vertex_Y_Resolution.MnvH1D_Iron[ind],
  sb_region3.Vertex_Y_Resolution.MnvH1D_Lead[ind],
  sb_region3.Vertex_Y_Resolution.MnvH1D_Other[ind],
  sb_region4.Vertex_Y_Resolution.MnvH1D_mc_total,
  sb_region4.Vertex_Y_Resolution.MnvH1D_Helium[ind],
  sb_region4.Vertex_Y_Resolution.MnvH1D_Aluminium[ind],
  sb_region4.Vertex_Y_Resolution.MnvH1D_Carbon[ind],
  sb_region4.Vertex_Y_Resolution.MnvH1D_Iron[ind],
  sb_region4.Vertex_Y_Resolution.MnvH1D_Lead[ind],
  sb_region4.Vertex_Y_Resolution.MnvH1D_Other[ind],
  var, "Vertex Y TRUE - RECO [mm]");

  var = histTitle +" Vertex R ";
  Plot_regions_noData(pdf_label, ind, POT_ratio,
    sb_region1.Vertex_R_Resolution.MnvH1D_mc_total,
    sb_region1.Vertex_R_Resolution.MnvH1D_Helium[ind],
    sb_region1.Vertex_R_Resolution.MnvH1D_Aluminium[ind],
    sb_region1.Vertex_R_Resolution.MnvH1D_Carbon[ind],
    sb_region1.Vertex_R_Resolution.MnvH1D_Iron[ind],
    sb_region1.Vertex_R_Resolution.MnvH1D_Lead[ind],
    sb_region1.Vertex_R_Resolution.MnvH1D_Other[ind],
    sb_region2.Vertex_R_Resolution.MnvH1D_mc_total,
    sb_region2.Vertex_R_Resolution.MnvH1D_Helium[ind],
    sb_region2.Vertex_R_Resolution.MnvH1D_Aluminium[ind],
    sb_region2.Vertex_R_Resolution.MnvH1D_Carbon[ind],
    sb_region2.Vertex_R_Resolution.MnvH1D_Iron[ind],
    sb_region2.Vertex_R_Resolution.MnvH1D_Lead[ind],
    sb_region2.Vertex_R_Resolution.MnvH1D_Other[ind],
    sb_region3.Vertex_R_Resolution.MnvH1D_mc_total,
    sb_region3.Vertex_R_Resolution.MnvH1D_Helium[ind],
    sb_region3.Vertex_R_Resolution.MnvH1D_Aluminium[ind],
    sb_region3.Vertex_R_Resolution.MnvH1D_Carbon[ind],
    sb_region3.Vertex_R_Resolution.MnvH1D_Iron[ind],
    sb_region3.Vertex_R_Resolution.MnvH1D_Lead[ind],
    sb_region3.Vertex_R_Resolution.MnvH1D_Other[ind],
    sb_region4.Vertex_R_Resolution.MnvH1D_mc_total,
    sb_region4.Vertex_R_Resolution.MnvH1D_Helium[ind],
    sb_region4.Vertex_R_Resolution.MnvH1D_Aluminium[ind],
    sb_region4.Vertex_R_Resolution.MnvH1D_Carbon[ind],
    sb_region4.Vertex_R_Resolution.MnvH1D_Iron[ind],
    sb_region4.Vertex_R_Resolution.MnvH1D_Lead[ind],
    sb_region4.Vertex_R_Resolution.MnvH1D_Other[ind],
    var, "Vertex R TRUE - RECO [mm]");

var = histTitle +" Vertex Z ";
    Plot_regions_noData(pdf_label, ind, POT_ratio,
      sb_region1.Vertex_Z_Resolution.MnvH1D_mc_total,
      sb_region1.Vertex_Z_Resolution.MnvH1D_Helium[ind],
      sb_region1.Vertex_Z_Resolution.MnvH1D_Aluminium[ind],
      sb_region1.Vertex_Z_Resolution.MnvH1D_Carbon[ind],
      sb_region1.Vertex_Z_Resolution.MnvH1D_Iron[ind],
      sb_region1.Vertex_Z_Resolution.MnvH1D_Lead[ind],
      sb_region1.Vertex_Z_Resolution.MnvH1D_Other[ind],
      sb_region2.Vertex_Z_Resolution.MnvH1D_mc_total,
      sb_region2.Vertex_Z_Resolution.MnvH1D_Helium[ind],
      sb_region2.Vertex_Z_Resolution.MnvH1D_Aluminium[ind],
      sb_region2.Vertex_Z_Resolution.MnvH1D_Carbon[ind],
      sb_region2.Vertex_Z_Resolution.MnvH1D_Iron[ind],
      sb_region2.Vertex_Z_Resolution.MnvH1D_Lead[ind],
      sb_region2.Vertex_Z_Resolution.MnvH1D_Other[ind],
      sb_region3.Vertex_Z_Resolution.MnvH1D_mc_total,
      sb_region3.Vertex_Z_Resolution.MnvH1D_Helium[ind],
      sb_region3.Vertex_Z_Resolution.MnvH1D_Aluminium[ind],
      sb_region3.Vertex_Z_Resolution.MnvH1D_Carbon[ind],
      sb_region3.Vertex_Z_Resolution.MnvH1D_Iron[ind],
      sb_region3.Vertex_Z_Resolution.MnvH1D_Lead[ind],
      sb_region3.Vertex_Z_Resolution.MnvH1D_Other[ind],
      sb_region4.Vertex_Z_Resolution.MnvH1D_mc_total,
      sb_region4.Vertex_Z_Resolution.MnvH1D_Helium[ind],
      sb_region4.Vertex_Z_Resolution.MnvH1D_Aluminium[ind],
      sb_region4.Vertex_Z_Resolution.MnvH1D_Carbon[ind],
      sb_region4.Vertex_Z_Resolution.MnvH1D_Iron[ind],
      sb_region4.Vertex_Z_Resolution.MnvH1D_Lead[ind],
      sb_region4.Vertex_Z_Resolution.MnvH1D_Other[ind],
      var, "Vertex Z TRUE - RECO [mm]");
  }
///////////////////////////////////////////////






///////////////////////////////////////////////
void Helium_3CryoRegionsSideBandTool::Plot_4RegionsVar(std::string pdf_label, double POT_ratio, int ind,
  Helium3SideBand &sb_region1,
  Helium3SideBand &sb_region2,
  Helium3SideBand &sb_region3,
  Helium3SideBand &sb_region4, std::string histTitle, CryoVertexDoubleMap &chisqrt_mapvertex_before,
   MuonVarDoubleMap &chisqrt_MuonVar_before,
   CryoVertexDoubleMap &chisqrt_mapvertex_after, MuonVarDoubleMap &chisqrt_MuonVar_after , int FitType )
{
  std::string title;
  double default_Ymax = 99;
  bool setmaxY = false;
  bool setmaxY_true = true;
  title ="P_{T,#mu} [GeV]" + histTitle;
  std::cout<<"P_{T,#mu} [GeV]"<<std::endl;

  Plot_regions(pdf_label, ind, POT_ratio,
    sb_region1.muon_PT.MnvH1D_data, sb_region1.muon_PT.MnvH1D_mc_total, sb_region1.muon_PT.MnvH1D_Helium[ind], sb_region1.muon_PT.MnvH1D_Aluminium[ind],sb_region1.muon_PT.MnvH1D_Carbon[ind],
    sb_region1.muon_PT.MnvH1D_Iron[ind], sb_region1.muon_PT.MnvH1D_Lead[ind], sb_region1.muon_PT.MnvH1D_Other[ind],

    sb_region2.muon_PT.MnvH1D_data, sb_region2.muon_PT.MnvH1D_mc_total, sb_region2.muon_PT.MnvH1D_Helium[ind], sb_region2.muon_PT.MnvH1D_Aluminium[ind],sb_region2.muon_PT.MnvH1D_Carbon[ind],
    sb_region2.muon_PT.MnvH1D_Iron[ind], sb_region2.muon_PT.MnvH1D_Lead[ind], sb_region2.muon_PT.MnvH1D_Other[ind],

    sb_region3.muon_PT.MnvH1D_data, sb_region3.muon_PT.MnvH1D_mc_total, sb_region3.muon_PT.MnvH1D_Helium[ind], sb_region3.muon_PT.MnvH1D_Aluminium[ind],sb_region3.muon_PT.MnvH1D_Carbon[ind],
    sb_region3.muon_PT.MnvH1D_Iron[ind], sb_region3.muon_PT.MnvH1D_Lead[ind], sb_region3.muon_PT.MnvH1D_Other[ind],

    sb_region4.muon_PT.MnvH1D_data,      sb_region4.muon_PT.MnvH1D_mc_total, sb_region4.muon_PT.MnvH1D_Helium[ind], sb_region4.muon_PT.MnvH1D_Aluminium[ind],sb_region4.muon_PT.MnvH1D_Carbon[ind],
    sb_region4.muon_PT.MnvH1D_Iron[ind], sb_region4.muon_PT.MnvH1D_Lead[ind], sb_region4.muon_PT.MnvH1D_Other[ind],

    title, sb_region3.muon_PT.Xaxis_Title, chisqrt_MuonVar_before[kP_T], chisqrt_MuonVar_after[kP_T] , FitType, UseLogChi_Tool, doAreaNormalized_Tool, setmaxY_true, YaxisMax_PT );





    title ="P_{Z,#mu} " + histTitle;
    std::cout<<"P_{Z,#mu} [GeV]"<<std::endl;
  Plot_regions(pdf_label, ind, POT_ratio,
    sb_region1.muon_PZ.MnvH1D_data, sb_region1.muon_PZ.MnvH1D_mc_total, sb_region1.muon_PZ.MnvH1D_Helium[ind], sb_region1.muon_PZ.MnvH1D_Aluminium[ind],sb_region1.muon_PZ.MnvH1D_Carbon[ind],
    sb_region1.muon_PZ.MnvH1D_Iron[ind], sb_region1.muon_PZ.MnvH1D_Lead[ind], sb_region1.muon_PZ.MnvH1D_Other[ind],

    sb_region2.muon_PZ.MnvH1D_data, sb_region2.muon_PZ.MnvH1D_mc_total, sb_region2.muon_PZ.MnvH1D_Helium[ind], sb_region2.muon_PZ.MnvH1D_Aluminium[ind],sb_region2.muon_PZ.MnvH1D_Carbon[ind],
    sb_region2.muon_PZ.MnvH1D_Iron[ind], sb_region2.muon_PZ.MnvH1D_Lead[ind], sb_region2.muon_PZ.MnvH1D_Other[ind],

    sb_region3.muon_PZ.MnvH1D_data, sb_region3.muon_PZ.MnvH1D_mc_total, sb_region3.muon_PZ.MnvH1D_Helium[ind], sb_region3.muon_PZ.MnvH1D_Aluminium[ind],sb_region3.muon_PZ.MnvH1D_Carbon[ind],
    sb_region3.muon_PZ.MnvH1D_Iron[ind], sb_region3.muon_PZ.MnvH1D_Lead[ind], sb_region3.muon_PZ.MnvH1D_Other[ind],

    sb_region4.muon_PZ.MnvH1D_data, sb_region4.muon_PZ.MnvH1D_mc_total, sb_region4.muon_PZ.MnvH1D_Helium[ind], sb_region4.muon_PZ.MnvH1D_Aluminium[ind],sb_region4.muon_PZ.MnvH1D_Carbon[ind],
    sb_region4.muon_PZ.MnvH1D_Iron[ind], sb_region4.muon_PZ.MnvH1D_Lead[ind], sb_region4.muon_PZ.MnvH1D_Other[ind],
    title, sb_region3.muon_PZ.Xaxis_Title, chisqrt_MuonVar_before[kP_Z], chisqrt_MuonVar_after[kP_Z], FitType, UseLogChi_Tool, doAreaNormalized_Tool, setmaxY_true, YaxisMax_PZ);

title ="#theta_{#mu} " + histTitle;
std::cout<<"#theta_{#mu} [Deg]"<<std::endl;
  Plot_regions(pdf_label, ind, POT_ratio,
    sb_region1.muon_theta.MnvH1D_data, sb_region1.muon_theta.MnvH1D_mc_total, sb_region1.muon_theta.MnvH1D_Helium[ind], sb_region1.muon_theta.MnvH1D_Aluminium[ind],sb_region1.muon_theta.MnvH1D_Carbon[ind],
    sb_region1.muon_theta.MnvH1D_Iron[ind], sb_region1.muon_theta.MnvH1D_Lead[ind], sb_region1.muon_theta.MnvH1D_Other[ind],

    sb_region2.muon_theta.MnvH1D_data, sb_region2.muon_theta.MnvH1D_mc_total, sb_region2.muon_theta.MnvH1D_Helium[ind], sb_region2.muon_theta.MnvH1D_Aluminium[ind],sb_region2.muon_theta.MnvH1D_Carbon[ind],
    sb_region2.muon_theta.MnvH1D_Iron[ind], sb_region2.muon_theta.MnvH1D_Lead[ind], sb_region2.muon_theta.MnvH1D_Other[ind],

    sb_region3.muon_theta.MnvH1D_data, sb_region3.muon_theta.MnvH1D_mc_total, sb_region3.muon_theta.MnvH1D_Helium[ind], sb_region3.muon_theta.MnvH1D_Aluminium[ind],sb_region3.muon_theta.MnvH1D_Carbon[ind],
    sb_region3.muon_theta.MnvH1D_Iron[ind], sb_region3.muon_theta.MnvH1D_Lead[ind], sb_region3.muon_theta.MnvH1D_Other[ind],

    sb_region4.muon_theta.MnvH1D_data, sb_region4.muon_theta.MnvH1D_mc_total, sb_region4.muon_theta.MnvH1D_Helium[ind], sb_region4.muon_theta.MnvH1D_Aluminium[ind],sb_region4.muon_theta.MnvH1D_Carbon[ind],
    sb_region4.muon_theta.MnvH1D_Iron[ind], sb_region4.muon_theta.MnvH1D_Lead[ind], sb_region4.muon_theta.MnvH1D_Other[ind],
    title, sb_region3.muon_theta.Xaxis_Title, chisqrt_MuonVar_before[kAngleWRTB], chisqrt_MuonVar_after[kAngleWRTB], FitType, UseLogChi_Tool, doAreaNormalized_Tool, setmaxY_true, YaxisMax_theta);

    title ="E_{#mu} " + histTitle;
    std::cout<<"E_{#mu} [GeV]"<<std::endl;
  Plot_regions(pdf_label, ind, POT_ratio,
    sb_region1.muon_E.MnvH1D_data, sb_region1.muon_E.MnvH1D_mc_total, sb_region1.muon_E.MnvH1D_Helium[ind], sb_region1.muon_E.MnvH1D_Aluminium[ind],sb_region1.muon_E.MnvH1D_Carbon[ind],
    sb_region1.muon_E.MnvH1D_Iron[ind], sb_region1.muon_E.MnvH1D_Lead[ind], sb_region1.muon_E.MnvH1D_Other[ind],

    sb_region2.muon_E.MnvH1D_data, sb_region2.muon_E.MnvH1D_mc_total, sb_region2.muon_E.MnvH1D_Helium[ind], sb_region2.muon_E.MnvH1D_Aluminium[ind],sb_region2.muon_E.MnvH1D_Carbon[ind],
    sb_region2.muon_E.MnvH1D_Iron[ind], sb_region2.muon_E.MnvH1D_Lead[ind], sb_region2.muon_E.MnvH1D_Other[ind],

    sb_region3.muon_E.MnvH1D_data, sb_region3.muon_E.MnvH1D_mc_total, sb_region3.muon_E.MnvH1D_Helium[ind], sb_region3.muon_E.MnvH1D_Aluminium[ind],sb_region3.muon_E.MnvH1D_Carbon[ind],
    sb_region3.muon_E.MnvH1D_Iron[ind], sb_region3.muon_E.MnvH1D_Lead[ind], sb_region3.muon_E.MnvH1D_Other[ind],

    sb_region4.muon_E.MnvH1D_data, sb_region4.muon_E.MnvH1D_mc_total, sb_region4.muon_E.MnvH1D_Helium[ind], sb_region4.muon_E.MnvH1D_Aluminium[ind],sb_region4.muon_E.MnvH1D_Carbon[ind],
    sb_region4.muon_E.MnvH1D_Iron[ind], sb_region4.muon_E.MnvH1D_Lead[ind], sb_region4.muon_E.MnvH1D_Other[ind],
    title, sb_region3.muon_E.Xaxis_Title, chisqrt_MuonVar_before[kE], chisqrt_MuonVar_after[kE], FitType, UseLogChi_Tool, doAreaNormalized_Tool, setmaxY_true, YaxisMax_E);


    title ="Muon DOCA" + histTitle;
    std::cout<<"Muon DOCA"<<std::endl;
  Plot_regions(pdf_label, ind, POT_ratio,
    sb_region1.muon_doca.MnvH1D_data, sb_region1.muon_doca.MnvH1D_mc_total, sb_region1.muon_doca.MnvH1D_Helium[ind], sb_region1.muon_doca.MnvH1D_Aluminium[ind],sb_region1.muon_doca.MnvH1D_Carbon[ind],
    sb_region1.muon_doca.MnvH1D_Iron[ind], sb_region1.muon_doca.MnvH1D_Lead[ind], sb_region1.muon_doca.MnvH1D_Other[ind],

    sb_region2.muon_doca.MnvH1D_data, sb_region2.muon_doca.MnvH1D_mc_total, sb_region2.muon_doca.MnvH1D_Helium[ind], sb_region2.muon_doca.MnvH1D_Aluminium[ind],sb_region2.muon_doca.MnvH1D_Carbon[ind],
    sb_region2.muon_doca.MnvH1D_Iron[ind], sb_region2.muon_doca.MnvH1D_Lead[ind], sb_region2.muon_doca.MnvH1D_Other[ind],

    sb_region3.muon_doca.MnvH1D_data, sb_region3.muon_doca.MnvH1D_mc_total, sb_region3.muon_doca.MnvH1D_Helium[ind], sb_region3.muon_doca.MnvH1D_Aluminium[ind],sb_region3.muon_doca.MnvH1D_Carbon[ind],
    sb_region3.muon_doca.MnvH1D_Iron[ind], sb_region3.muon_doca.MnvH1D_Lead[ind], sb_region3.muon_doca.MnvH1D_Other[ind],

    sb_region4.muon_doca.MnvH1D_data, sb_region4.muon_doca.MnvH1D_mc_total, sb_region4.muon_doca.MnvH1D_Helium[ind], sb_region4.muon_doca.MnvH1D_Aluminium[ind],sb_region4.muon_doca.MnvH1D_Carbon[ind],
    sb_region4.muon_doca.MnvH1D_Iron[ind], sb_region4.muon_doca.MnvH1D_Lead[ind], sb_region4.muon_doca.MnvH1D_Other[ind],
    title, sb_region3.muon_doca.Xaxis_Title, chisqrt_MuonVar_before[kDOCA_muon], chisqrt_MuonVar_after[kDOCA_muon], FitType, UseLogChi_Tool, doAreaNormalized_Tool, setmaxY, default_Ymax);

    title ="Distance to Nearest Wall " + histTitle;
    std::cout<<"Distance to Nearest Wall  [mm]"<<std::endl;

  Plot_regions_addArrow(pdf_label, ind, POT_ratio,
    sb_region1.DistancetoEdge.MnvH1D_data, sb_region1.DistancetoEdge.MnvH1D_mc_total, sb_region1.DistancetoEdge.MnvH1D_Helium[ind], sb_region1.DistancetoEdge.MnvH1D_Aluminium[ind],sb_region1.DistancetoEdge.MnvH1D_Carbon[ind],
    sb_region1.DistancetoEdge.MnvH1D_Iron[ind], sb_region1.DistancetoEdge.MnvH1D_Lead[ind], sb_region1.DistancetoEdge.MnvH1D_Other[ind],

    sb_region2.DistancetoEdge.MnvH1D_data, sb_region2.DistancetoEdge.MnvH1D_mc_total, sb_region2.DistancetoEdge.MnvH1D_Helium[ind], sb_region2.DistancetoEdge.MnvH1D_Aluminium[ind],sb_region2.DistancetoEdge.MnvH1D_Carbon[ind],
    sb_region2.DistancetoEdge.MnvH1D_Iron[ind], sb_region2.DistancetoEdge.MnvH1D_Lead[ind], sb_region2.DistancetoEdge.MnvH1D_Other[ind],

    sb_region3.DistancetoEdge.MnvH1D_data, sb_region3.DistancetoEdge.MnvH1D_mc_total, sb_region3.DistancetoEdge.MnvH1D_Helium[ind], sb_region3.DistancetoEdge.MnvH1D_Aluminium[ind],sb_region3.DistancetoEdge.MnvH1D_Carbon[ind],
    sb_region3.DistancetoEdge.MnvH1D_Iron[ind], sb_region3.DistancetoEdge.MnvH1D_Lead[ind], sb_region3.DistancetoEdge.MnvH1D_Other[ind],

    sb_region4.DistancetoEdge.MnvH1D_data, sb_region4.DistancetoEdge.MnvH1D_mc_total, sb_region4.DistancetoEdge.MnvH1D_Helium[ind], sb_region4.DistancetoEdge.MnvH1D_Aluminium[ind],sb_region4.DistancetoEdge.MnvH1D_Carbon[ind],
    sb_region4.DistancetoEdge.MnvH1D_Iron[ind], sb_region4.DistancetoEdge.MnvH1D_Lead[ind], sb_region4.DistancetoEdge.MnvH1D_Other[ind],
    title, sb_region3.DistancetoEdge.Xaxis_Title, chisqrt_mapvertex_before[kdistance_edge], chisqrt_mapvertex_after[kdistance_edge], FitType, 50.0, 0 ,30, 75, UseLogChi_Tool, doAreaNormalized_Tool );

    title ="Recoil DOCA " + histTitle;
    std::cout<<"Recoil DOCA [mm]"<<std::endl;
  Plot_regions(pdf_label, ind, POT_ratio,
    sb_region1.SecTrk_doca.MnvH1D_data, sb_region1.SecTrk_doca.MnvH1D_mc_total, sb_region1.SecTrk_doca.MnvH1D_Helium[ind], sb_region1.SecTrk_doca.MnvH1D_Aluminium[ind],sb_region1.SecTrk_doca.MnvH1D_Carbon[ind],
    sb_region1.SecTrk_doca.MnvH1D_Iron[ind], sb_region1.SecTrk_doca.MnvH1D_Lead[ind], sb_region1.SecTrk_doca.MnvH1D_Other[ind],

    sb_region2.SecTrk_doca.MnvH1D_data, sb_region2.SecTrk_doca.MnvH1D_mc_total, sb_region2.SecTrk_doca.MnvH1D_Helium[ind], sb_region2.SecTrk_doca.MnvH1D_Aluminium[ind],sb_region2.SecTrk_doca.MnvH1D_Carbon[ind],
    sb_region2.SecTrk_doca.MnvH1D_Iron[ind], sb_region2.SecTrk_doca.MnvH1D_Lead[ind], sb_region2.SecTrk_doca.MnvH1D_Other[ind],

    sb_region3.SecTrk_doca.MnvH1D_data, sb_region3.SecTrk_doca.MnvH1D_mc_total, sb_region3.SecTrk_doca.MnvH1D_Helium[ind], sb_region3.SecTrk_doca.MnvH1D_Aluminium[ind],sb_region3.SecTrk_doca.MnvH1D_Carbon[ind],
    sb_region3.SecTrk_doca.MnvH1D_Iron[ind], sb_region3.SecTrk_doca.MnvH1D_Lead[ind], sb_region3.SecTrk_doca.MnvH1D_Other[ind],

    sb_region4.SecTrk_doca.MnvH1D_data, sb_region4.SecTrk_doca.MnvH1D_mc_total, sb_region4.SecTrk_doca.MnvH1D_Helium[ind], sb_region4.SecTrk_doca.MnvH1D_Aluminium[ind],sb_region4.SecTrk_doca.MnvH1D_Carbon[ind],
    sb_region4.SecTrk_doca.MnvH1D_Iron[ind], sb_region4.SecTrk_doca.MnvH1D_Lead[ind], sb_region4.SecTrk_doca.MnvH1D_Other[ind],
    title, sb_region3.SecTrk_doca.Xaxis_Title, chisqrt_mapvertex_before[krecoil_DOCA], chisqrt_mapvertex_after[krecoil_DOCA], FitType, UseLogChi_Tool, doAreaNormalized_Tool, setmaxY, default_Ymax);

    title ="Recoil Tracklength " + histTitle;
    std::cout<<"Recoil Tracklength [cm]"<<std::endl;
  Plot_regions(pdf_label, ind, POT_ratio,
    sb_region1.TrackLength.MnvH1D_data, sb_region1.TrackLength.MnvH1D_mc_total, sb_region1.TrackLength.MnvH1D_Helium[ind], sb_region1.TrackLength.MnvH1D_Aluminium[ind],sb_region1.TrackLength.MnvH1D_Carbon[ind],
    sb_region1.TrackLength.MnvH1D_Iron[ind], sb_region1.TrackLength.MnvH1D_Lead[ind], sb_region1.TrackLength.MnvH1D_Other[ind],

    sb_region2.TrackLength.MnvH1D_data, sb_region2.TrackLength.MnvH1D_mc_total, sb_region2.TrackLength.MnvH1D_Helium[ind], sb_region2.TrackLength.MnvH1D_Aluminium[ind],sb_region2.TrackLength.MnvH1D_Carbon[ind],
    sb_region2.TrackLength.MnvH1D_Iron[ind], sb_region2.TrackLength.MnvH1D_Lead[ind], sb_region2.TrackLength.MnvH1D_Other[ind],

    sb_region3.TrackLength.MnvH1D_data, sb_region3.TrackLength.MnvH1D_mc_total, sb_region3.TrackLength.MnvH1D_Helium[ind], sb_region3.TrackLength.MnvH1D_Aluminium[ind],sb_region3.TrackLength.MnvH1D_Carbon[ind],
    sb_region3.TrackLength.MnvH1D_Iron[ind], sb_region3.TrackLength.MnvH1D_Lead[ind], sb_region3.TrackLength.MnvH1D_Other[ind],

    sb_region4.TrackLength.MnvH1D_data, sb_region4.TrackLength.MnvH1D_mc_total, sb_region4.TrackLength.MnvH1D_Helium[ind], sb_region4.TrackLength.MnvH1D_Aluminium[ind],sb_region4.TrackLength.MnvH1D_Carbon[ind],
    sb_region4.TrackLength.MnvH1D_Iron[ind], sb_region4.TrackLength.MnvH1D_Lead[ind], sb_region4.TrackLength.MnvH1D_Other[ind],
    title, sb_region3.TrackLength.Xaxis_Title, chisqrt_mapvertex_before[krecoil_tracklength_minerva], chisqrt_mapvertex_after[krecoil_tracklength_minerva], FitType, UseLogChi_Tool, doAreaNormalized_Tool, setmaxY, default_Ymax);




    title ="Distance To DSCap " + histTitle;
    std::cout<<"Distance To DSCap [mm]"<<std::endl;
  Plot_regions(pdf_label, ind, POT_ratio,
    sb_region1.DistancetoDownstreamCap.MnvH1D_data, sb_region1.DistancetoDownstreamCap.MnvH1D_mc_total, sb_region1.DistancetoDownstreamCap.MnvH1D_Helium[ind], sb_region1.DistancetoDownstreamCap.MnvH1D_Aluminium[ind],sb_region1.DistancetoDownstreamCap.MnvH1D_Carbon[ind],
    sb_region1.DistancetoDownstreamCap.MnvH1D_Iron[ind], sb_region1.DistancetoDownstreamCap.MnvH1D_Lead[ind], sb_region1.DistancetoDownstreamCap.MnvH1D_Other[ind],

    sb_region2.DistancetoDownstreamCap.MnvH1D_data, sb_region2.DistancetoDownstreamCap.MnvH1D_mc_total, sb_region2.DistancetoDownstreamCap.MnvH1D_Helium[ind], sb_region2.DistancetoDownstreamCap.MnvH1D_Aluminium[ind],sb_region2.DistancetoDownstreamCap.MnvH1D_Carbon[ind],
    sb_region2.DistancetoDownstreamCap.MnvH1D_Iron[ind], sb_region2.DistancetoDownstreamCap.MnvH1D_Lead[ind], sb_region2.DistancetoDownstreamCap.MnvH1D_Other[ind],

    sb_region3.DistancetoDownstreamCap.MnvH1D_data, sb_region3.DistancetoDownstreamCap.MnvH1D_mc_total, sb_region3.DistancetoDownstreamCap.MnvH1D_Helium[ind], sb_region3.DistancetoDownstreamCap.MnvH1D_Aluminium[ind],sb_region3.DistancetoDownstreamCap.MnvH1D_Carbon[ind],
    sb_region3.DistancetoDownstreamCap.MnvH1D_Iron[ind], sb_region3.DistancetoDownstreamCap.MnvH1D_Lead[ind], sb_region3.DistancetoDownstreamCap.MnvH1D_Other[ind],

    sb_region4.DistancetoDownstreamCap.MnvH1D_data, sb_region4.DistancetoDownstreamCap.MnvH1D_mc_total, sb_region4.DistancetoDownstreamCap.MnvH1D_Helium[ind], sb_region4.DistancetoDownstreamCap.MnvH1D_Aluminium[ind],sb_region4.DistancetoDownstreamCap.MnvH1D_Carbon[ind],
    sb_region4.DistancetoDownstreamCap.MnvH1D_Iron[ind], sb_region4.DistancetoDownstreamCap.MnvH1D_Lead[ind], sb_region4.DistancetoDownstreamCap.MnvH1D_Other[ind],
    title, sb_region3.DistancetoDownstreamCap.Xaxis_Title, chisqrt_mapvertex_before[kdistance_downstreamcap], chisqrt_mapvertex_after[kdistance_downstreamcap], FitType, UseLogChi_Tool, doAreaNormalized_Tool, setmaxY, default_Ymax);


        title ="Distance To DSCap [RCut] " + histTitle;
        std::cout<<"Distance To DSCap [mm]"<<std::endl;
  Plot_regions(pdf_label, ind, POT_ratio,
    sb_region1.DistancetoDownstreamCap_RCut.MnvH1D_data, sb_region1.DistancetoDownstreamCap_RCut.MnvH1D_mc_total, sb_region1.DistancetoDownstreamCap_RCut.MnvH1D_Helium[ind], sb_region1.DistancetoDownstreamCap_RCut.MnvH1D_Aluminium[ind],sb_region1.DistancetoDownstreamCap_RCut.MnvH1D_Carbon[ind],
    sb_region1.DistancetoDownstreamCap_RCut.MnvH1D_Iron[ind], sb_region1.DistancetoDownstreamCap_RCut.MnvH1D_Lead[ind], sb_region1.DistancetoDownstreamCap_RCut.MnvH1D_Other[ind],

    sb_region2.DistancetoDownstreamCap_RCut.MnvH1D_data, sb_region2.DistancetoDownstreamCap_RCut.MnvH1D_mc_total, sb_region2.DistancetoDownstreamCap_RCut.MnvH1D_Helium[ind], sb_region2.DistancetoDownstreamCap_RCut.MnvH1D_Aluminium[ind],sb_region2.DistancetoDownstreamCap_RCut.MnvH1D_Carbon[ind],
    sb_region2.DistancetoDownstreamCap_RCut.MnvH1D_Iron[ind], sb_region2.DistancetoDownstreamCap_RCut.MnvH1D_Lead[ind], sb_region2.DistancetoDownstreamCap_RCut.MnvH1D_Other[ind],

    sb_region3.DistancetoDownstreamCap_RCut.MnvH1D_data, sb_region3.DistancetoDownstreamCap_RCut.MnvH1D_mc_total, sb_region3.DistancetoDownstreamCap_RCut.MnvH1D_Helium[ind], sb_region3.DistancetoDownstreamCap_RCut.MnvH1D_Aluminium[ind],sb_region3.DistancetoDownstreamCap_RCut.MnvH1D_Carbon[ind],
    sb_region3.DistancetoDownstreamCap_RCut.MnvH1D_Iron[ind], sb_region3.DistancetoDownstreamCap_RCut.MnvH1D_Lead[ind], sb_region3.DistancetoDownstreamCap_RCut.MnvH1D_Other[ind],

    sb_region4.DistancetoDownstreamCap_RCut.MnvH1D_data, sb_region4.DistancetoDownstreamCap_RCut.MnvH1D_mc_total, sb_region4.DistancetoDownstreamCap_RCut.MnvH1D_Helium[ind], sb_region4.DistancetoDownstreamCap_RCut.MnvH1D_Aluminium[ind],sb_region4.DistancetoDownstreamCap_RCut.MnvH1D_Carbon[ind],
    sb_region4.DistancetoDownstreamCap_RCut.MnvH1D_Iron[ind], sb_region4.DistancetoDownstreamCap_RCut.MnvH1D_Lead[ind], sb_region4.DistancetoDownstreamCap_RCut.MnvH1D_Other[ind],
    title, sb_region3.DistancetoDownstreamCap_RCut.Xaxis_Title, chisqrt_mapvertex_before[kdistance_downstreamcap_RCut], chisqrt_mapvertex_after[kdistance_downstreamcap_RCut], FitType, UseLogChi_Tool, doAreaNormalized_Tool, setmaxY, default_Ymax);


    title ="Distance To USCap " + histTitle;
    std::cout<<"Distance To USCap [mm]"<<std::endl;
  Plot_regions(pdf_label, ind, POT_ratio,
    sb_region1.DistancetoUpstreamCap.MnvH1D_data, sb_region1.DistancetoUpstreamCap.MnvH1D_mc_total, sb_region1.DistancetoUpstreamCap.MnvH1D_Helium[ind], sb_region1.DistancetoUpstreamCap.MnvH1D_Aluminium[ind],sb_region1.DistancetoUpstreamCap.MnvH1D_Carbon[ind],
    sb_region1.DistancetoUpstreamCap.MnvH1D_Iron[ind], sb_region1.DistancetoUpstreamCap.MnvH1D_Lead[ind], sb_region1.DistancetoUpstreamCap.MnvH1D_Other[ind],

    sb_region2.DistancetoUpstreamCap.MnvH1D_data, sb_region2.DistancetoUpstreamCap.MnvH1D_mc_total, sb_region2.DistancetoUpstreamCap.MnvH1D_Helium[ind], sb_region2.DistancetoUpstreamCap.MnvH1D_Aluminium[ind],sb_region2.DistancetoUpstreamCap.MnvH1D_Carbon[ind],
    sb_region2.DistancetoUpstreamCap.MnvH1D_Iron[ind], sb_region2.DistancetoUpstreamCap.MnvH1D_Lead[ind], sb_region2.DistancetoUpstreamCap.MnvH1D_Other[ind],

    sb_region3.DistancetoUpstreamCap.MnvH1D_data, sb_region3.DistancetoUpstreamCap.MnvH1D_mc_total, sb_region3.DistancetoUpstreamCap.MnvH1D_Helium[ind], sb_region3.DistancetoUpstreamCap.MnvH1D_Aluminium[ind],sb_region3.DistancetoUpstreamCap.MnvH1D_Carbon[ind],
    sb_region3.DistancetoUpstreamCap.MnvH1D_Iron[ind], sb_region3.DistancetoUpstreamCap.MnvH1D_Lead[ind], sb_region3.DistancetoUpstreamCap.MnvH1D_Other[ind],

    sb_region4.DistancetoUpstreamCap.MnvH1D_data, sb_region4.DistancetoUpstreamCap.MnvH1D_mc_total, sb_region4.DistancetoUpstreamCap.MnvH1D_Helium[ind], sb_region4.DistancetoUpstreamCap.MnvH1D_Aluminium[ind],sb_region4.DistancetoUpstreamCap.MnvH1D_Carbon[ind],
    sb_region4.DistancetoUpstreamCap.MnvH1D_Iron[ind], sb_region4.DistancetoUpstreamCap.MnvH1D_Lead[ind], sb_region4.DistancetoUpstreamCap.MnvH1D_Other[ind],
    title, sb_region3.DistancetoUpstreamCap.Xaxis_Title, chisqrt_mapvertex_before[kdistance_upstreamcap], chisqrt_mapvertex_after[kdistance_upstreamcap], FitType, UseLogChi_Tool, doAreaNormalized_Tool, setmaxY, default_Ymax);


        title ="Distance To USCap [RCut] " + histTitle;
        std::cout<<"Distance To USCap [mm]"<<std::endl;
  Plot_regions(pdf_label, ind, POT_ratio,
    sb_region1.DistancetoUpstreamCap_RCut.MnvH1D_data, sb_region1.DistancetoUpstreamCap_RCut.MnvH1D_mc_total, sb_region1.DistancetoUpstreamCap_RCut.MnvH1D_Helium[ind], sb_region1.DistancetoUpstreamCap_RCut.MnvH1D_Aluminium[ind],sb_region1.DistancetoUpstreamCap_RCut.MnvH1D_Carbon[ind],
    sb_region1.DistancetoUpstreamCap_RCut.MnvH1D_Iron[ind], sb_region1.DistancetoUpstreamCap_RCut.MnvH1D_Lead[ind], sb_region1.DistancetoUpstreamCap_RCut.MnvH1D_Other[ind],

    sb_region2.DistancetoUpstreamCap_RCut.MnvH1D_data, sb_region2.DistancetoUpstreamCap_RCut.MnvH1D_mc_total, sb_region2.DistancetoUpstreamCap_RCut.MnvH1D_Helium[ind], sb_region2.DistancetoUpstreamCap_RCut.MnvH1D_Aluminium[ind],sb_region2.DistancetoUpstreamCap_RCut.MnvH1D_Carbon[ind],
    sb_region2.DistancetoUpstreamCap_RCut.MnvH1D_Iron[ind], sb_region2.DistancetoUpstreamCap_RCut.MnvH1D_Lead[ind], sb_region2.DistancetoUpstreamCap_RCut.MnvH1D_Other[ind],

    sb_region3.DistancetoUpstreamCap_RCut.MnvH1D_data, sb_region3.DistancetoUpstreamCap_RCut.MnvH1D_mc_total, sb_region3.DistancetoUpstreamCap_RCut.MnvH1D_Helium[ind], sb_region3.DistancetoUpstreamCap_RCut.MnvH1D_Aluminium[ind],sb_region3.DistancetoUpstreamCap_RCut.MnvH1D_Carbon[ind],
    sb_region3.DistancetoUpstreamCap_RCut.MnvH1D_Iron[ind], sb_region3.DistancetoUpstreamCap_RCut.MnvH1D_Lead[ind], sb_region3.DistancetoUpstreamCap_RCut.MnvH1D_Other[ind],

    sb_region4.DistancetoUpstreamCap_RCut.MnvH1D_data, sb_region4.DistancetoUpstreamCap_RCut.MnvH1D_mc_total, sb_region4.DistancetoUpstreamCap_RCut.MnvH1D_Helium[ind], sb_region4.DistancetoUpstreamCap_RCut.MnvH1D_Aluminium[ind],sb_region4.DistancetoUpstreamCap_RCut.MnvH1D_Carbon[ind],
    sb_region4.DistancetoUpstreamCap_RCut.MnvH1D_Iron[ind], sb_region4.DistancetoUpstreamCap_RCut.MnvH1D_Lead[ind], sb_region4.DistancetoUpstreamCap_RCut.MnvH1D_Other[ind],
    title, sb_region3.DistancetoUpstreamCap_RCut.Xaxis_Title, chisqrt_mapvertex_before[kdistance_upstreamcap_RCut], chisqrt_mapvertex_after[kdistance_upstreamcap_RCut], FitType, UseLogChi_Tool, doAreaNormalized_Tool, setmaxY, default_Ymax);


        title ="Vertex Z [RCut] " + histTitle;
        std::cout<<"Vertex Z  [RCut][mm]"<<std::endl;
  Plot_regions(pdf_label, ind, POT_ratio,
    sb_region1.Vertex_Z_RCut.MnvH1D_data, sb_region1.Vertex_Z_RCut.MnvH1D_mc_total, sb_region1.Vertex_Z_RCut.MnvH1D_Helium[ind], sb_region1.Vertex_Z_RCut.MnvH1D_Aluminium[ind],sb_region1.Vertex_Z_RCut.MnvH1D_Carbon[ind],
    sb_region1.Vertex_Z_RCut.MnvH1D_Iron[ind], sb_region1.Vertex_Z_RCut.MnvH1D_Lead[ind], sb_region1.Vertex_Z_RCut.MnvH1D_Other[ind],

    sb_region2.Vertex_Z_RCut.MnvH1D_data, sb_region2.Vertex_Z_RCut.MnvH1D_mc_total, sb_region2.Vertex_Z_RCut.MnvH1D_Helium[ind], sb_region2.Vertex_Z_RCut.MnvH1D_Aluminium[ind],sb_region2.Vertex_Z_RCut.MnvH1D_Carbon[ind],
    sb_region2.Vertex_Z_RCut.MnvH1D_Iron[ind], sb_region2.Vertex_Z_RCut.MnvH1D_Lead[ind], sb_region2.Vertex_Z_RCut.MnvH1D_Other[ind],

    sb_region3.Vertex_Z_RCut.MnvH1D_data, sb_region3.Vertex_Z_RCut.MnvH1D_mc_total, sb_region3.Vertex_Z_RCut.MnvH1D_Helium[ind], sb_region3.Vertex_Z_RCut.MnvH1D_Aluminium[ind],sb_region3.Vertex_Z_RCut.MnvH1D_Carbon[ind],
    sb_region3.Vertex_Z_RCut.MnvH1D_Iron[ind], sb_region3.Vertex_Z_RCut.MnvH1D_Lead[ind], sb_region3.Vertex_Z_RCut.MnvH1D_Other[ind],

    sb_region4.Vertex_Z_RCut.MnvH1D_data, sb_region4.Vertex_Z_RCut.MnvH1D_mc_total, sb_region4.Vertex_Z_RCut.MnvH1D_Helium[ind], sb_region4.Vertex_Z_RCut.MnvH1D_Aluminium[ind],sb_region4.Vertex_Z_RCut.MnvH1D_Carbon[ind],
    sb_region4.Vertex_Z_RCut.MnvH1D_Iron[ind], sb_region4.Vertex_Z_RCut.MnvH1D_Lead[ind], sb_region4.Vertex_Z_RCut.MnvH1D_Other[ind],
    title, sb_region3.Vertex_Z_RCut.Xaxis_Title, chisqrt_mapvertex_before[kZ_RCut], chisqrt_mapvertex_after[kZ_RCut], FitType, UseLogChi_Tool, doAreaNormalized_Tool, setmaxY, default_Ymax);


    title ="Vertex X [RCut] " + histTitle;
    std::cout<<"Vertex X  [RCut][mm]"<<std::endl;
Plot_regions(pdf_label, ind, POT_ratio,
sb_region1.Vertex_X_RCut.MnvH1D_data, sb_region1.Vertex_X_RCut.MnvH1D_mc_total, sb_region1.Vertex_X_RCut.MnvH1D_Helium[ind], sb_region1.Vertex_X_RCut.MnvH1D_Aluminium[ind],sb_region1.Vertex_X_RCut.MnvH1D_Carbon[ind],
sb_region1.Vertex_X_RCut.MnvH1D_Iron[ind], sb_region1.Vertex_X_RCut.MnvH1D_Lead[ind], sb_region1.Vertex_X_RCut.MnvH1D_Other[ind],

sb_region2.Vertex_X_RCut.MnvH1D_data, sb_region2.Vertex_X_RCut.MnvH1D_mc_total, sb_region2.Vertex_X_RCut.MnvH1D_Helium[ind], sb_region2.Vertex_X_RCut.MnvH1D_Aluminium[ind],sb_region2.Vertex_X_RCut.MnvH1D_Carbon[ind],
sb_region2.Vertex_X_RCut.MnvH1D_Iron[ind], sb_region2.Vertex_X_RCut.MnvH1D_Lead[ind], sb_region2.Vertex_X_RCut.MnvH1D_Other[ind],

sb_region3.Vertex_X_RCut.MnvH1D_data, sb_region3.Vertex_X_RCut.MnvH1D_mc_total, sb_region3.Vertex_X_RCut.MnvH1D_Helium[ind], sb_region3.Vertex_X_RCut.MnvH1D_Aluminium[ind],sb_region3.Vertex_X_RCut.MnvH1D_Carbon[ind],
sb_region3.Vertex_X_RCut.MnvH1D_Iron[ind], sb_region3.Vertex_X_RCut.MnvH1D_Lead[ind], sb_region3.Vertex_X_RCut.MnvH1D_Other[ind],

sb_region4.Vertex_X_RCut.MnvH1D_data, sb_region4.Vertex_X_RCut.MnvH1D_mc_total, sb_region4.Vertex_X_RCut.MnvH1D_Helium[ind], sb_region4.Vertex_X_RCut.MnvH1D_Aluminium[ind],sb_region4.Vertex_X_RCut.MnvH1D_Carbon[ind],
sb_region4.Vertex_X_RCut.MnvH1D_Iron[ind], sb_region4.Vertex_X_RCut.MnvH1D_Lead[ind], sb_region4.Vertex_X_RCut.MnvH1D_Other[ind],
title, sb_region3.Vertex_X_RCut.Xaxis_Title, chisqrt_mapvertex_before[kX_RCut], chisqrt_mapvertex_after[kX_RCut], FitType, UseLogChi_Tool, doAreaNormalized_Tool, setmaxY, default_Ymax);


title ="Vertex Y [RCut] " + histTitle;
std::cout<<"Vertex Y  [RCut][mm]"<<std::endl;
Plot_regions(pdf_label, ind, POT_ratio,
sb_region1.Vertex_Y_RCut.MnvH1D_data, sb_region1.Vertex_Y_RCut.MnvH1D_mc_total, sb_region1.Vertex_Y_RCut.MnvH1D_Helium[ind], sb_region1.Vertex_Y_RCut.MnvH1D_Aluminium[ind],sb_region1.Vertex_Y_RCut.MnvH1D_Carbon[ind],
sb_region1.Vertex_Y_RCut.MnvH1D_Iron[ind], sb_region1.Vertex_Y_RCut.MnvH1D_Lead[ind], sb_region1.Vertex_Y_RCut.MnvH1D_Other[ind],

sb_region2.Vertex_Y_RCut.MnvH1D_data, sb_region2.Vertex_Y_RCut.MnvH1D_mc_total, sb_region2.Vertex_Y_RCut.MnvH1D_Helium[ind], sb_region2.Vertex_Y_RCut.MnvH1D_Aluminium[ind],sb_region2.Vertex_Y_RCut.MnvH1D_Carbon[ind],
sb_region2.Vertex_Y_RCut.MnvH1D_Iron[ind], sb_region2.Vertex_Y_RCut.MnvH1D_Lead[ind], sb_region2.Vertex_Y_RCut.MnvH1D_Other[ind],

sb_region3.Vertex_Y_RCut.MnvH1D_data, sb_region3.Vertex_Y_RCut.MnvH1D_mc_total, sb_region3.Vertex_Y_RCut.MnvH1D_Helium[ind], sb_region3.Vertex_Y_RCut.MnvH1D_Aluminium[ind],sb_region3.Vertex_Y_RCut.MnvH1D_Carbon[ind],
sb_region3.Vertex_Y_RCut.MnvH1D_Iron[ind], sb_region3.Vertex_Y_RCut.MnvH1D_Lead[ind], sb_region3.Vertex_Y_RCut.MnvH1D_Other[ind],

sb_region4.Vertex_Y_RCut.MnvH1D_data, sb_region4.Vertex_Y_RCut.MnvH1D_mc_total, sb_region4.Vertex_Y_RCut.MnvH1D_Helium[ind], sb_region4.Vertex_Y_RCut.MnvH1D_Aluminium[ind],sb_region4.Vertex_Y_RCut.MnvH1D_Carbon[ind],
sb_region4.Vertex_Y_RCut.MnvH1D_Iron[ind], sb_region4.Vertex_Y_RCut.MnvH1D_Lead[ind], sb_region4.Vertex_Y_RCut.MnvH1D_Other[ind],
title, sb_region3.Vertex_Y_RCut.Xaxis_Title, chisqrt_mapvertex_before[kY_RCut], chisqrt_mapvertex_after[kY_RCut], FitType, UseLogChi_Tool, doAreaNormalized_Tool, setmaxY, default_Ymax);


title ="Vertex R [RCut] " + histTitle;
std::cout<<"Vertex R  [RCut][mm]"<<std::endl;
Plot_regions(pdf_label, ind, POT_ratio,
sb_region1.Vertex_R_RCut.MnvH1D_data, sb_region1.Vertex_R_RCut.MnvH1D_mc_total, sb_region1.Vertex_R_RCut.MnvH1D_Helium[ind], sb_region1.Vertex_R_RCut.MnvH1D_Aluminium[ind],sb_region1.Vertex_R_RCut.MnvH1D_Carbon[ind],
sb_region1.Vertex_R_RCut.MnvH1D_Iron[ind], sb_region1.Vertex_R_RCut.MnvH1D_Lead[ind], sb_region1.Vertex_R_RCut.MnvH1D_Other[ind],

sb_region2.Vertex_R_RCut.MnvH1D_data, sb_region2.Vertex_R_RCut.MnvH1D_mc_total, sb_region2.Vertex_R_RCut.MnvH1D_Helium[ind], sb_region2.Vertex_R_RCut.MnvH1D_Aluminium[ind],sb_region2.Vertex_R_RCut.MnvH1D_Carbon[ind],
sb_region2.Vertex_R_RCut.MnvH1D_Iron[ind], sb_region2.Vertex_R_RCut.MnvH1D_Lead[ind], sb_region2.Vertex_R_RCut.MnvH1D_Other[ind],

sb_region3.Vertex_R_RCut.MnvH1D_data, sb_region3.Vertex_R_RCut.MnvH1D_mc_total, sb_region3.Vertex_R_RCut.MnvH1D_Helium[ind], sb_region3.Vertex_R_RCut.MnvH1D_Aluminium[ind],sb_region3.Vertex_R_RCut.MnvH1D_Carbon[ind],
sb_region3.Vertex_R_RCut.MnvH1D_Iron[ind], sb_region3.Vertex_R_RCut.MnvH1D_Lead[ind], sb_region3.Vertex_R_RCut.MnvH1D_Other[ind],

sb_region4.Vertex_R_RCut.MnvH1D_data, sb_region4.Vertex_R_RCut.MnvH1D_mc_total, sb_region4.Vertex_R_RCut.MnvH1D_Helium[ind], sb_region4.Vertex_R_RCut.MnvH1D_Aluminium[ind],sb_region4.Vertex_R_RCut.MnvH1D_Carbon[ind],
sb_region4.Vertex_R_RCut.MnvH1D_Iron[ind], sb_region4.Vertex_R_RCut.MnvH1D_Lead[ind], sb_region4.Vertex_R_RCut.MnvH1D_Other[ind],
title, sb_region3.Vertex_R_RCut.Xaxis_Title, chisqrt_mapvertex_before[kR_RCut], chisqrt_mapvertex_after[kR_RCut], FitType, UseLogChi_Tool, doAreaNormalized_Tool, setmaxY, default_Ymax);



  }
/////////
void Helium_3CryoRegionsSideBandTool::Plot_4RegionsVar_noStack(std::string pdf_label, double POT_ratio, int ind,
  Helium3SideBand &sb_region1,
  Helium3SideBand &sb_region2,
  Helium3SideBand &sb_region3,
  Helium3SideBand &sb_region4, std::string histTitle, CryoVertexDoubleMap &chisqrt_mapvertex_before,
   MuonVarDoubleMap &chisqrt_MuonVar_before,
   CryoVertexDoubleMap &chisqrt_mapvertex_after, MuonVarDoubleMap &chisqrt_MuonVar_after , int FitType )
{
  std::string title;

  title ="P_{T,#mu} [GeV]" + histTitle;
  std::cout<<"P_{T,#mu} [GeV]"<<std::endl;

  Plot_regions_noStack(pdf_label, ind, POT_ratio,
    sb_region1.muon_PT.MnvH1D_data, sb_region1.muon_PT.MnvH1D_mc_total, sb_region1.muon_PT.MnvH1D_Helium[ind], sb_region1.muon_PT.MnvH1D_Aluminium[ind],sb_region1.muon_PT.MnvH1D_Carbon[ind],
    sb_region1.muon_PT.MnvH1D_Iron[ind], sb_region1.muon_PT.MnvH1D_Lead[ind], sb_region1.muon_PT.MnvH1D_Other[ind],

    sb_region2.muon_PT.MnvH1D_data, sb_region2.muon_PT.MnvH1D_mc_total, sb_region2.muon_PT.MnvH1D_Helium[ind], sb_region2.muon_PT.MnvH1D_Aluminium[ind],sb_region2.muon_PT.MnvH1D_Carbon[ind],
    sb_region2.muon_PT.MnvH1D_Iron[ind], sb_region2.muon_PT.MnvH1D_Lead[ind], sb_region2.muon_PT.MnvH1D_Other[ind],

    sb_region3.muon_PT.MnvH1D_data, sb_region3.muon_PT.MnvH1D_mc_total, sb_region3.muon_PT.MnvH1D_Helium[ind], sb_region3.muon_PT.MnvH1D_Aluminium[ind],sb_region3.muon_PT.MnvH1D_Carbon[ind],
    sb_region3.muon_PT.MnvH1D_Iron[ind], sb_region3.muon_PT.MnvH1D_Lead[ind], sb_region3.muon_PT.MnvH1D_Other[ind],

    sb_region4.muon_PT.MnvH1D_data, sb_region4.muon_PT.MnvH1D_mc_total, sb_region4.muon_PT.MnvH1D_Helium[ind], sb_region4.muon_PT.MnvH1D_Aluminium[ind],sb_region4.muon_PT.MnvH1D_Carbon[ind],
    sb_region4.muon_PT.MnvH1D_Iron[ind], sb_region4.muon_PT.MnvH1D_Lead[ind], sb_region4.muon_PT.MnvH1D_Other[ind],
    title, sb_region3.muon_PT.Xaxis_Title, chisqrt_MuonVar_before[kP_T], chisqrt_MuonVar_after[kP_T] , FitType, UseLogChi_Tool, doAreaNormalized_Tool );


    title ="P_{Z,#mu} " + histTitle;
    std::cout<<"P_{Z,#mu} [GeV]"<<std::endl;
  Plot_regions_noStack(pdf_label, ind, POT_ratio,
    sb_region1.muon_PZ.MnvH1D_data, sb_region1.muon_PZ.MnvH1D_mc_total, sb_region1.muon_PZ.MnvH1D_Helium[ind], sb_region1.muon_PZ.MnvH1D_Aluminium[ind],sb_region1.muon_PZ.MnvH1D_Carbon[ind],
    sb_region1.muon_PZ.MnvH1D_Iron[ind], sb_region1.muon_PZ.MnvH1D_Lead[ind], sb_region1.muon_PZ.MnvH1D_Other[ind],

    sb_region2.muon_PZ.MnvH1D_data, sb_region2.muon_PZ.MnvH1D_mc_total, sb_region2.muon_PZ.MnvH1D_Helium[ind], sb_region2.muon_PZ.MnvH1D_Aluminium[ind],sb_region2.muon_PZ.MnvH1D_Carbon[ind],
    sb_region2.muon_PZ.MnvH1D_Iron[ind], sb_region2.muon_PZ.MnvH1D_Lead[ind], sb_region2.muon_PZ.MnvH1D_Other[ind],

    sb_region3.muon_PZ.MnvH1D_data, sb_region3.muon_PZ.MnvH1D_mc_total, sb_region3.muon_PZ.MnvH1D_Helium[ind], sb_region3.muon_PZ.MnvH1D_Aluminium[ind],sb_region3.muon_PZ.MnvH1D_Carbon[ind],
    sb_region3.muon_PZ.MnvH1D_Iron[ind], sb_region3.muon_PZ.MnvH1D_Lead[ind], sb_region3.muon_PZ.MnvH1D_Other[ind],

    sb_region4.muon_PZ.MnvH1D_data, sb_region4.muon_PZ.MnvH1D_mc_total, sb_region4.muon_PZ.MnvH1D_Helium[ind], sb_region4.muon_PZ.MnvH1D_Aluminium[ind],sb_region4.muon_PZ.MnvH1D_Carbon[ind],
    sb_region4.muon_PZ.MnvH1D_Iron[ind], sb_region4.muon_PZ.MnvH1D_Lead[ind], sb_region4.muon_PZ.MnvH1D_Other[ind],
    title, sb_region3.muon_PZ.Xaxis_Title, chisqrt_MuonVar_before[kP_Z], chisqrt_MuonVar_after[kP_Z], FitType, UseLogChi_Tool, doAreaNormalized_Tool);

title ="#theta_{#mu}" + histTitle;
std::cout<<"#theta_{#mu} [Deg]"<<std::endl;
  Plot_regions_noStack(pdf_label, ind, POT_ratio,
    sb_region1.muon_theta.MnvH1D_data, sb_region1.muon_theta.MnvH1D_mc_total, sb_region1.muon_theta.MnvH1D_Helium[ind], sb_region1.muon_theta.MnvH1D_Aluminium[ind],sb_region1.muon_theta.MnvH1D_Carbon[ind],
    sb_region1.muon_theta.MnvH1D_Iron[ind], sb_region1.muon_theta.MnvH1D_Lead[ind], sb_region1.muon_theta.MnvH1D_Other[ind],

    sb_region2.muon_theta.MnvH1D_data, sb_region2.muon_theta.MnvH1D_mc_total, sb_region2.muon_theta.MnvH1D_Helium[ind], sb_region2.muon_theta.MnvH1D_Aluminium[ind],sb_region2.muon_theta.MnvH1D_Carbon[ind],
    sb_region2.muon_theta.MnvH1D_Iron[ind], sb_region2.muon_theta.MnvH1D_Lead[ind], sb_region2.muon_theta.MnvH1D_Other[ind],

    sb_region3.muon_theta.MnvH1D_data, sb_region3.muon_theta.MnvH1D_mc_total, sb_region3.muon_theta.MnvH1D_Helium[ind], sb_region3.muon_theta.MnvH1D_Aluminium[ind],sb_region3.muon_theta.MnvH1D_Carbon[ind],
    sb_region3.muon_theta.MnvH1D_Iron[ind], sb_region3.muon_theta.MnvH1D_Lead[ind], sb_region3.muon_theta.MnvH1D_Other[ind],

    sb_region4.muon_theta.MnvH1D_data, sb_region4.muon_theta.MnvH1D_mc_total, sb_region4.muon_theta.MnvH1D_Helium[ind], sb_region4.muon_theta.MnvH1D_Aluminium[ind],sb_region4.muon_theta.MnvH1D_Carbon[ind],
    sb_region4.muon_theta.MnvH1D_Iron[ind], sb_region4.muon_theta.MnvH1D_Lead[ind], sb_region4.muon_theta.MnvH1D_Other[ind],
    title, sb_region3.muon_theta.Xaxis_Title, chisqrt_MuonVar_before[kAngleWRTB], chisqrt_MuonVar_after[kAngleWRTB], FitType, UseLogChi_Tool, doAreaNormalized_Tool);

    title ="E_{#mu} " + histTitle;
    std::cout<<"E_{#mu} [GeV]"<<std::endl;
  Plot_regions_noStack(pdf_label, ind, POT_ratio,
    sb_region1.muon_E.MnvH1D_data, sb_region1.muon_E.MnvH1D_mc_total, sb_region1.muon_E.MnvH1D_Helium[ind], sb_region1.muon_E.MnvH1D_Aluminium[ind],sb_region1.muon_E.MnvH1D_Carbon[ind],
    sb_region1.muon_E.MnvH1D_Iron[ind], sb_region1.muon_E.MnvH1D_Lead[ind], sb_region1.muon_E.MnvH1D_Other[ind],

    sb_region2.muon_E.MnvH1D_data, sb_region2.muon_E.MnvH1D_mc_total, sb_region2.muon_E.MnvH1D_Helium[ind], sb_region2.muon_E.MnvH1D_Aluminium[ind],sb_region2.muon_E.MnvH1D_Carbon[ind],
    sb_region2.muon_E.MnvH1D_Iron[ind], sb_region2.muon_E.MnvH1D_Lead[ind], sb_region2.muon_E.MnvH1D_Other[ind],

    sb_region3.muon_E.MnvH1D_data, sb_region3.muon_E.MnvH1D_mc_total, sb_region3.muon_E.MnvH1D_Helium[ind], sb_region3.muon_E.MnvH1D_Aluminium[ind],sb_region3.muon_E.MnvH1D_Carbon[ind],
    sb_region3.muon_E.MnvH1D_Iron[ind], sb_region3.muon_E.MnvH1D_Lead[ind], sb_region3.muon_E.MnvH1D_Other[ind],

    sb_region4.muon_E.MnvH1D_data, sb_region4.muon_E.MnvH1D_mc_total, sb_region4.muon_E.MnvH1D_Helium[ind], sb_region4.muon_E.MnvH1D_Aluminium[ind],sb_region4.muon_E.MnvH1D_Carbon[ind],
    sb_region4.muon_E.MnvH1D_Iron[ind], sb_region4.muon_E.MnvH1D_Lead[ind], sb_region4.muon_E.MnvH1D_Other[ind],
    title, sb_region3.muon_E.Xaxis_Title, chisqrt_MuonVar_before[kE], chisqrt_MuonVar_after[kE], FitType, UseLogChi_Tool, doAreaNormalized_Tool);


    title ="Muon DOCA" + histTitle;
    std::cout<<"Muon DOCA"<<std::endl;
  Plot_regions_noStack(pdf_label, ind, POT_ratio,
    sb_region1.muon_doca.MnvH1D_data, sb_region1.muon_doca.MnvH1D_mc_total, sb_region1.muon_doca.MnvH1D_Helium[ind], sb_region1.muon_doca.MnvH1D_Aluminium[ind],sb_region1.muon_doca.MnvH1D_Carbon[ind],
    sb_region1.muon_doca.MnvH1D_Iron[ind], sb_region1.muon_doca.MnvH1D_Lead[ind], sb_region1.muon_doca.MnvH1D_Other[ind],

    sb_region2.muon_doca.MnvH1D_data, sb_region2.muon_doca.MnvH1D_mc_total, sb_region2.muon_doca.MnvH1D_Helium[ind], sb_region2.muon_doca.MnvH1D_Aluminium[ind],sb_region2.muon_doca.MnvH1D_Carbon[ind],
    sb_region2.muon_doca.MnvH1D_Iron[ind], sb_region2.muon_doca.MnvH1D_Lead[ind], sb_region2.muon_doca.MnvH1D_Other[ind],

    sb_region3.muon_doca.MnvH1D_data, sb_region3.muon_doca.MnvH1D_mc_total, sb_region3.muon_doca.MnvH1D_Helium[ind], sb_region3.muon_doca.MnvH1D_Aluminium[ind],sb_region3.muon_doca.MnvH1D_Carbon[ind],
    sb_region3.muon_doca.MnvH1D_Iron[ind], sb_region3.muon_doca.MnvH1D_Lead[ind], sb_region3.muon_doca.MnvH1D_Other[ind],

    sb_region4.muon_doca.MnvH1D_data, sb_region4.muon_doca.MnvH1D_mc_total, sb_region4.muon_doca.MnvH1D_Helium[ind], sb_region4.muon_doca.MnvH1D_Aluminium[ind],sb_region4.muon_doca.MnvH1D_Carbon[ind],
    sb_region4.muon_doca.MnvH1D_Iron[ind], sb_region4.muon_doca.MnvH1D_Lead[ind], sb_region4.muon_doca.MnvH1D_Other[ind],
    title, sb_region3.muon_doca.Xaxis_Title, chisqrt_MuonVar_before[kDOCA_muon], chisqrt_MuonVar_after[kDOCA_muon], FitType, UseLogChi_Tool, doAreaNormalized_Tool);

    title ="Distance to Nearest Wall " + histTitle;
    std::cout<<"Distance to Nearest Wall  [mm]"<<std::endl;

  Plot_regionsNoStack_addArrow(pdf_label, ind, POT_ratio,
    sb_region1.DistancetoEdge.MnvH1D_data, sb_region1.DistancetoEdge.MnvH1D_mc_total, sb_region1.DistancetoEdge.MnvH1D_Helium[ind], sb_region1.DistancetoEdge.MnvH1D_Aluminium[ind],sb_region1.DistancetoEdge.MnvH1D_Carbon[ind],
    sb_region1.DistancetoEdge.MnvH1D_Iron[ind], sb_region1.DistancetoEdge.MnvH1D_Lead[ind], sb_region1.DistancetoEdge.MnvH1D_Other[ind],

    sb_region2.DistancetoEdge.MnvH1D_data, sb_region2.DistancetoEdge.MnvH1D_mc_total, sb_region2.DistancetoEdge.MnvH1D_Helium[ind], sb_region2.DistancetoEdge.MnvH1D_Aluminium[ind],sb_region2.DistancetoEdge.MnvH1D_Carbon[ind],
    sb_region2.DistancetoEdge.MnvH1D_Iron[ind], sb_region2.DistancetoEdge.MnvH1D_Lead[ind], sb_region2.DistancetoEdge.MnvH1D_Other[ind],

    sb_region3.DistancetoEdge.MnvH1D_data, sb_region3.DistancetoEdge.MnvH1D_mc_total, sb_region3.DistancetoEdge.MnvH1D_Helium[ind], sb_region3.DistancetoEdge.MnvH1D_Aluminium[ind],sb_region3.DistancetoEdge.MnvH1D_Carbon[ind],
    sb_region3.DistancetoEdge.MnvH1D_Iron[ind], sb_region3.DistancetoEdge.MnvH1D_Lead[ind], sb_region3.DistancetoEdge.MnvH1D_Other[ind],

    sb_region4.DistancetoEdge.MnvH1D_data, sb_region4.DistancetoEdge.MnvH1D_mc_total, sb_region4.DistancetoEdge.MnvH1D_Helium[ind], sb_region4.DistancetoEdge.MnvH1D_Aluminium[ind],sb_region4.DistancetoEdge.MnvH1D_Carbon[ind],
    sb_region4.DistancetoEdge.MnvH1D_Iron[ind], sb_region4.DistancetoEdge.MnvH1D_Lead[ind], sb_region4.DistancetoEdge.MnvH1D_Other[ind],
    title, sb_region3.DistancetoEdge.Xaxis_Title, chisqrt_mapvertex_before[kdistance_edge], chisqrt_mapvertex_after[kdistance_edge], FitType, 50.0, 0 ,30, 75, UseLogChi_Tool , doAreaNormalized_Tool );

    title ="Recoil DOCA " + histTitle;
    std::cout<<"Recoil DOCA [mm]"<<std::endl;
  Plot_regions_noStack(pdf_label, ind, POT_ratio,
    sb_region1.SecTrk_doca.MnvH1D_data, sb_region1.SecTrk_doca.MnvH1D_mc_total, sb_region1.SecTrk_doca.MnvH1D_Helium[ind], sb_region1.SecTrk_doca.MnvH1D_Aluminium[ind],sb_region1.SecTrk_doca.MnvH1D_Carbon[ind],
    sb_region1.SecTrk_doca.MnvH1D_Iron[ind], sb_region1.SecTrk_doca.MnvH1D_Lead[ind], sb_region1.SecTrk_doca.MnvH1D_Other[ind],

    sb_region2.SecTrk_doca.MnvH1D_data, sb_region2.SecTrk_doca.MnvH1D_mc_total, sb_region2.SecTrk_doca.MnvH1D_Helium[ind], sb_region2.SecTrk_doca.MnvH1D_Aluminium[ind],sb_region2.SecTrk_doca.MnvH1D_Carbon[ind],
    sb_region2.SecTrk_doca.MnvH1D_Iron[ind], sb_region2.SecTrk_doca.MnvH1D_Lead[ind], sb_region2.SecTrk_doca.MnvH1D_Other[ind],

    sb_region3.SecTrk_doca.MnvH1D_data, sb_region3.SecTrk_doca.MnvH1D_mc_total, sb_region3.SecTrk_doca.MnvH1D_Helium[ind], sb_region3.SecTrk_doca.MnvH1D_Aluminium[ind],sb_region3.SecTrk_doca.MnvH1D_Carbon[ind],
    sb_region3.SecTrk_doca.MnvH1D_Iron[ind], sb_region3.SecTrk_doca.MnvH1D_Lead[ind], sb_region3.SecTrk_doca.MnvH1D_Other[ind],

    sb_region4.SecTrk_doca.MnvH1D_data, sb_region4.SecTrk_doca.MnvH1D_mc_total, sb_region4.SecTrk_doca.MnvH1D_Helium[ind], sb_region4.SecTrk_doca.MnvH1D_Aluminium[ind],sb_region4.SecTrk_doca.MnvH1D_Carbon[ind],
    sb_region4.SecTrk_doca.MnvH1D_Iron[ind], sb_region4.SecTrk_doca.MnvH1D_Lead[ind], sb_region4.SecTrk_doca.MnvH1D_Other[ind],
    title, sb_region3.SecTrk_doca.Xaxis_Title, chisqrt_mapvertex_before[krecoil_DOCA], chisqrt_mapvertex_after[krecoil_DOCA], FitType, UseLogChi_Tool, doAreaNormalized_Tool);

    title ="Recoil Tracklength" + histTitle;
    std::cout<<"Recoil Tracklength [cm]"<<std::endl;

  Plot_regions_noStack(pdf_label, ind, POT_ratio,
    sb_region1.TrackLength.MnvH1D_data, sb_region1.TrackLength.MnvH1D_mc_total, sb_region1.TrackLength.MnvH1D_Helium[ind], sb_region1.TrackLength.MnvH1D_Aluminium[ind],sb_region1.TrackLength.MnvH1D_Carbon[ind],
    sb_region1.TrackLength.MnvH1D_Iron[ind], sb_region1.TrackLength.MnvH1D_Lead[ind], sb_region1.TrackLength.MnvH1D_Other[ind],

    sb_region2.TrackLength.MnvH1D_data, sb_region2.TrackLength.MnvH1D_mc_total, sb_region2.TrackLength.MnvH1D_Helium[ind], sb_region2.TrackLength.MnvH1D_Aluminium[ind],sb_region2.TrackLength.MnvH1D_Carbon[ind],
    sb_region2.TrackLength.MnvH1D_Iron[ind], sb_region2.TrackLength.MnvH1D_Lead[ind], sb_region2.TrackLength.MnvH1D_Other[ind],

    sb_region3.TrackLength.MnvH1D_data, sb_region3.TrackLength.MnvH1D_mc_total, sb_region3.TrackLength.MnvH1D_Helium[ind], sb_region3.TrackLength.MnvH1D_Aluminium[ind],sb_region3.TrackLength.MnvH1D_Carbon[ind],
    sb_region3.TrackLength.MnvH1D_Iron[ind], sb_region3.TrackLength.MnvH1D_Lead[ind], sb_region3.TrackLength.MnvH1D_Other[ind],

    sb_region4.TrackLength.MnvH1D_data, sb_region4.TrackLength.MnvH1D_mc_total, sb_region4.TrackLength.MnvH1D_Helium[ind], sb_region4.TrackLength.MnvH1D_Aluminium[ind],sb_region4.TrackLength.MnvH1D_Carbon[ind],
    sb_region4.TrackLength.MnvH1D_Iron[ind], sb_region4.TrackLength.MnvH1D_Lead[ind], sb_region4.TrackLength.MnvH1D_Other[ind],
    title, sb_region3.TrackLength.Xaxis_Title, chisqrt_mapvertex_before[krecoil_tracklength_minerva], chisqrt_mapvertex_after[krecoil_tracklength_minerva], FitType, UseLogChi_Tool, doAreaNormalized_Tool);




    title ="Distance To DSCap " + histTitle;
    std::cout<<"Distance To DSCap [mm]"<<std::endl;
  Plot_regions_noStack(pdf_label, ind, POT_ratio,
    sb_region1.DistancetoDownstreamCap.MnvH1D_data, sb_region1.DistancetoDownstreamCap.MnvH1D_mc_total, sb_region1.DistancetoDownstreamCap.MnvH1D_Helium[ind], sb_region1.DistancetoDownstreamCap.MnvH1D_Aluminium[ind],sb_region1.DistancetoDownstreamCap.MnvH1D_Carbon[ind],
    sb_region1.DistancetoDownstreamCap.MnvH1D_Iron[ind], sb_region1.DistancetoDownstreamCap.MnvH1D_Lead[ind], sb_region1.DistancetoDownstreamCap.MnvH1D_Other[ind],

    sb_region2.DistancetoDownstreamCap.MnvH1D_data, sb_region2.DistancetoDownstreamCap.MnvH1D_mc_total, sb_region2.DistancetoDownstreamCap.MnvH1D_Helium[ind], sb_region2.DistancetoDownstreamCap.MnvH1D_Aluminium[ind],sb_region2.DistancetoDownstreamCap.MnvH1D_Carbon[ind],
    sb_region2.DistancetoDownstreamCap.MnvH1D_Iron[ind], sb_region2.DistancetoDownstreamCap.MnvH1D_Lead[ind], sb_region2.DistancetoDownstreamCap.MnvH1D_Other[ind],

    sb_region3.DistancetoDownstreamCap.MnvH1D_data, sb_region3.DistancetoDownstreamCap.MnvH1D_mc_total, sb_region3.DistancetoDownstreamCap.MnvH1D_Helium[ind], sb_region3.DistancetoDownstreamCap.MnvH1D_Aluminium[ind],sb_region3.DistancetoDownstreamCap.MnvH1D_Carbon[ind],
    sb_region3.DistancetoDownstreamCap.MnvH1D_Iron[ind], sb_region3.DistancetoDownstreamCap.MnvH1D_Lead[ind], sb_region3.DistancetoDownstreamCap.MnvH1D_Other[ind],

    sb_region4.DistancetoDownstreamCap.MnvH1D_data, sb_region4.DistancetoDownstreamCap.MnvH1D_mc_total, sb_region4.DistancetoDownstreamCap.MnvH1D_Helium[ind], sb_region4.DistancetoDownstreamCap.MnvH1D_Aluminium[ind],sb_region4.DistancetoDownstreamCap.MnvH1D_Carbon[ind],
    sb_region4.DistancetoDownstreamCap.MnvH1D_Iron[ind], sb_region4.DistancetoDownstreamCap.MnvH1D_Lead[ind], sb_region4.DistancetoDownstreamCap.MnvH1D_Other[ind],
    title, sb_region3.DistancetoDownstreamCap.Xaxis_Title, chisqrt_mapvertex_before[kdistance_downstreamcap], chisqrt_mapvertex_after[kdistance_downstreamcap], FitType, UseLogChi_Tool, doAreaNormalized_Tool);


        title ="Distance To DSCap [RCut] " + histTitle;
        std::cout<<"Distance To DSCap [mm]"<<std::endl;
  Plot_regions_noStack(pdf_label, ind, POT_ratio,
    sb_region1.DistancetoDownstreamCap_RCut.MnvH1D_data, sb_region1.DistancetoDownstreamCap_RCut.MnvH1D_mc_total, sb_region1.DistancetoDownstreamCap_RCut.MnvH1D_Helium[ind], sb_region1.DistancetoDownstreamCap_RCut.MnvH1D_Aluminium[ind],sb_region1.DistancetoDownstreamCap_RCut.MnvH1D_Carbon[ind],
    sb_region1.DistancetoDownstreamCap_RCut.MnvH1D_Iron[ind], sb_region1.DistancetoDownstreamCap_RCut.MnvH1D_Lead[ind], sb_region1.DistancetoDownstreamCap_RCut.MnvH1D_Other[ind],

    sb_region2.DistancetoDownstreamCap_RCut.MnvH1D_data, sb_region2.DistancetoDownstreamCap_RCut.MnvH1D_mc_total, sb_region2.DistancetoDownstreamCap_RCut.MnvH1D_Helium[ind], sb_region2.DistancetoDownstreamCap_RCut.MnvH1D_Aluminium[ind],sb_region2.DistancetoDownstreamCap_RCut.MnvH1D_Carbon[ind],
    sb_region2.DistancetoDownstreamCap_RCut.MnvH1D_Iron[ind], sb_region2.DistancetoDownstreamCap_RCut.MnvH1D_Lead[ind], sb_region2.DistancetoDownstreamCap_RCut.MnvH1D_Other[ind],

    sb_region3.DistancetoDownstreamCap_RCut.MnvH1D_data, sb_region3.DistancetoDownstreamCap_RCut.MnvH1D_mc_total, sb_region3.DistancetoDownstreamCap_RCut.MnvH1D_Helium[ind], sb_region3.DistancetoDownstreamCap_RCut.MnvH1D_Aluminium[ind],sb_region3.DistancetoDownstreamCap_RCut.MnvH1D_Carbon[ind],
    sb_region3.DistancetoDownstreamCap_RCut.MnvH1D_Iron[ind], sb_region3.DistancetoDownstreamCap_RCut.MnvH1D_Lead[ind], sb_region3.DistancetoDownstreamCap_RCut.MnvH1D_Other[ind],

    sb_region4.DistancetoDownstreamCap_RCut.MnvH1D_data, sb_region4.DistancetoDownstreamCap_RCut.MnvH1D_mc_total, sb_region4.DistancetoDownstreamCap_RCut.MnvH1D_Helium[ind], sb_region4.DistancetoDownstreamCap_RCut.MnvH1D_Aluminium[ind],sb_region4.DistancetoDownstreamCap_RCut.MnvH1D_Carbon[ind],
    sb_region4.DistancetoDownstreamCap_RCut.MnvH1D_Iron[ind], sb_region4.DistancetoDownstreamCap_RCut.MnvH1D_Lead[ind], sb_region4.DistancetoDownstreamCap_RCut.MnvH1D_Other[ind],
    title, sb_region3.DistancetoDownstreamCap_RCut.Xaxis_Title, chisqrt_mapvertex_before[kdistance_downstreamcap_RCut], chisqrt_mapvertex_after[kdistance_downstreamcap_RCut], FitType, UseLogChi_Tool, doAreaNormalized_Tool);


    title ="Distance To USCap " + histTitle;
    std::cout<<"Distance To USCap [mm]"<<std::endl;
  Plot_regions_noStack(pdf_label, ind, POT_ratio,
    sb_region1.DistancetoUpstreamCap.MnvH1D_data, sb_region1.DistancetoUpstreamCap.MnvH1D_mc_total, sb_region1.DistancetoUpstreamCap.MnvH1D_Helium[ind], sb_region1.DistancetoUpstreamCap.MnvH1D_Aluminium[ind],sb_region1.DistancetoUpstreamCap.MnvH1D_Carbon[ind],
    sb_region1.DistancetoUpstreamCap.MnvH1D_Iron[ind], sb_region1.DistancetoUpstreamCap.MnvH1D_Lead[ind], sb_region1.DistancetoUpstreamCap.MnvH1D_Other[ind],

    sb_region2.DistancetoUpstreamCap.MnvH1D_data, sb_region2.DistancetoUpstreamCap.MnvH1D_mc_total, sb_region2.DistancetoUpstreamCap.MnvH1D_Helium[ind], sb_region2.DistancetoUpstreamCap.MnvH1D_Aluminium[ind],sb_region2.DistancetoUpstreamCap.MnvH1D_Carbon[ind],
    sb_region2.DistancetoUpstreamCap.MnvH1D_Iron[ind], sb_region2.DistancetoUpstreamCap.MnvH1D_Lead[ind], sb_region2.DistancetoUpstreamCap.MnvH1D_Other[ind],

    sb_region3.DistancetoUpstreamCap.MnvH1D_data, sb_region3.DistancetoUpstreamCap.MnvH1D_mc_total, sb_region3.DistancetoUpstreamCap.MnvH1D_Helium[ind], sb_region3.DistancetoUpstreamCap.MnvH1D_Aluminium[ind],sb_region3.DistancetoUpstreamCap.MnvH1D_Carbon[ind],
    sb_region3.DistancetoUpstreamCap.MnvH1D_Iron[ind], sb_region3.DistancetoUpstreamCap.MnvH1D_Lead[ind], sb_region3.DistancetoUpstreamCap.MnvH1D_Other[ind],

    sb_region4.DistancetoUpstreamCap.MnvH1D_data, sb_region4.DistancetoUpstreamCap.MnvH1D_mc_total, sb_region4.DistancetoUpstreamCap.MnvH1D_Helium[ind], sb_region4.DistancetoUpstreamCap.MnvH1D_Aluminium[ind],sb_region4.DistancetoUpstreamCap.MnvH1D_Carbon[ind],
    sb_region4.DistancetoUpstreamCap.MnvH1D_Iron[ind], sb_region4.DistancetoUpstreamCap.MnvH1D_Lead[ind], sb_region4.DistancetoUpstreamCap.MnvH1D_Other[ind],
    title, sb_region3.DistancetoUpstreamCap.Xaxis_Title, chisqrt_mapvertex_before[kdistance_upstreamcap], chisqrt_mapvertex_after[kdistance_upstreamcap], FitType, UseLogChi_Tool, doAreaNormalized_Tool);


        title ="Distance To DSCap [RCut] " + histTitle;
        std::cout<<"Distance To DSCap [mm]"<<std::endl;
  Plot_regions_noStack(pdf_label, ind, POT_ratio,
    sb_region1.DistancetoUpstreamCap_RCut.MnvH1D_data, sb_region1.DistancetoUpstreamCap_RCut.MnvH1D_mc_total, sb_region1.DistancetoUpstreamCap_RCut.MnvH1D_Helium[ind], sb_region1.DistancetoUpstreamCap_RCut.MnvH1D_Aluminium[ind],sb_region1.DistancetoUpstreamCap_RCut.MnvH1D_Carbon[ind],
    sb_region1.DistancetoUpstreamCap_RCut.MnvH1D_Iron[ind], sb_region1.DistancetoUpstreamCap_RCut.MnvH1D_Lead[ind], sb_region1.DistancetoUpstreamCap_RCut.MnvH1D_Other[ind],

    sb_region2.DistancetoUpstreamCap_RCut.MnvH1D_data, sb_region2.DistancetoUpstreamCap_RCut.MnvH1D_mc_total, sb_region2.DistancetoUpstreamCap_RCut.MnvH1D_Helium[ind], sb_region2.DistancetoUpstreamCap_RCut.MnvH1D_Aluminium[ind],sb_region2.DistancetoUpstreamCap_RCut.MnvH1D_Carbon[ind],
    sb_region2.DistancetoUpstreamCap_RCut.MnvH1D_Iron[ind], sb_region2.DistancetoUpstreamCap_RCut.MnvH1D_Lead[ind], sb_region2.DistancetoUpstreamCap_RCut.MnvH1D_Other[ind],

    sb_region3.DistancetoUpstreamCap_RCut.MnvH1D_data, sb_region3.DistancetoUpstreamCap_RCut.MnvH1D_mc_total, sb_region3.DistancetoUpstreamCap_RCut.MnvH1D_Helium[ind], sb_region3.DistancetoUpstreamCap_RCut.MnvH1D_Aluminium[ind],sb_region3.DistancetoUpstreamCap_RCut.MnvH1D_Carbon[ind],
    sb_region3.DistancetoUpstreamCap_RCut.MnvH1D_Iron[ind], sb_region3.DistancetoUpstreamCap_RCut.MnvH1D_Lead[ind], sb_region3.DistancetoUpstreamCap_RCut.MnvH1D_Other[ind],

    sb_region4.DistancetoUpstreamCap_RCut.MnvH1D_data, sb_region4.DistancetoUpstreamCap_RCut.MnvH1D_mc_total, sb_region4.DistancetoUpstreamCap_RCut.MnvH1D_Helium[ind], sb_region4.DistancetoUpstreamCap_RCut.MnvH1D_Aluminium[ind],sb_region4.DistancetoUpstreamCap_RCut.MnvH1D_Carbon[ind],
    sb_region4.DistancetoUpstreamCap_RCut.MnvH1D_Iron[ind], sb_region4.DistancetoUpstreamCap_RCut.MnvH1D_Lead[ind], sb_region4.DistancetoUpstreamCap_RCut.MnvH1D_Other[ind],
    title, sb_region3.DistancetoUpstreamCap_RCut.Xaxis_Title, chisqrt_mapvertex_before[kdistance_upstreamcap_RCut], chisqrt_mapvertex_after[kdistance_upstreamcap_RCut], FitType, UseLogChi_Tool, doAreaNormalized_Tool);


        title ="Vertex Z [RCut] " + histTitle;
        std::cout<<"Vertex Z  [RCut][mm]"<<std::endl;
  Plot_regions_noStack(pdf_label, ind, POT_ratio,
    sb_region1.Vertex_Z_RCut.MnvH1D_data, sb_region1.Vertex_Z_RCut.MnvH1D_mc_total, sb_region1.Vertex_Z_RCut.MnvH1D_Helium[ind], sb_region1.Vertex_Z_RCut.MnvH1D_Aluminium[ind],sb_region1.Vertex_Z_RCut.MnvH1D_Carbon[ind],
    sb_region1.Vertex_Z_RCut.MnvH1D_Iron[ind], sb_region1.Vertex_Z_RCut.MnvH1D_Lead[ind], sb_region1.Vertex_Z_RCut.MnvH1D_Other[ind],

    sb_region2.Vertex_Z_RCut.MnvH1D_data, sb_region2.Vertex_Z_RCut.MnvH1D_mc_total, sb_region2.Vertex_Z_RCut.MnvH1D_Helium[ind], sb_region2.Vertex_Z_RCut.MnvH1D_Aluminium[ind],sb_region2.Vertex_Z_RCut.MnvH1D_Carbon[ind],
    sb_region2.Vertex_Z_RCut.MnvH1D_Iron[ind], sb_region2.Vertex_Z_RCut.MnvH1D_Lead[ind], sb_region2.Vertex_Z_RCut.MnvH1D_Other[ind],

    sb_region3.Vertex_Z_RCut.MnvH1D_data, sb_region3.Vertex_Z_RCut.MnvH1D_mc_total, sb_region3.Vertex_Z_RCut.MnvH1D_Helium[ind], sb_region3.Vertex_Z_RCut.MnvH1D_Aluminium[ind],sb_region3.Vertex_Z_RCut.MnvH1D_Carbon[ind],
    sb_region3.Vertex_Z_RCut.MnvH1D_Iron[ind], sb_region3.Vertex_Z_RCut.MnvH1D_Lead[ind], sb_region3.Vertex_Z_RCut.MnvH1D_Other[ind],

    sb_region4.Vertex_Z_RCut.MnvH1D_data, sb_region4.Vertex_Z_RCut.MnvH1D_mc_total, sb_region4.Vertex_Z_RCut.MnvH1D_Helium[ind], sb_region4.Vertex_Z_RCut.MnvH1D_Aluminium[ind],sb_region4.Vertex_Z_RCut.MnvH1D_Carbon[ind],
    sb_region4.Vertex_Z_RCut.MnvH1D_Iron[ind], sb_region4.Vertex_Z_RCut.MnvH1D_Lead[ind], sb_region4.Vertex_Z_RCut.MnvH1D_Other[ind],
    title, sb_region3.Vertex_Z_RCut.Xaxis_Title, chisqrt_mapvertex_before[kZ_RCut], chisqrt_mapvertex_after[kZ_RCut], FitType, UseLogChi_Tool, doAreaNormalized_Tool);


    title ="Vertex X  [RCut] " + histTitle;
    std::cout<<"Vertex X  [RCut][mm]"<<std::endl;
Plot_regions_noStack(pdf_label, ind, POT_ratio,
sb_region1.Vertex_X_RCut.MnvH1D_data, sb_region1.Vertex_X_RCut.MnvH1D_mc_total, sb_region1.Vertex_X_RCut.MnvH1D_Helium[ind], sb_region1.Vertex_X_RCut.MnvH1D_Aluminium[ind],sb_region1.Vertex_X_RCut.MnvH1D_Carbon[ind],
sb_region1.Vertex_X_RCut.MnvH1D_Iron[ind], sb_region1.Vertex_X_RCut.MnvH1D_Lead[ind], sb_region1.Vertex_X_RCut.MnvH1D_Other[ind],

sb_region2.Vertex_X_RCut.MnvH1D_data, sb_region2.Vertex_X_RCut.MnvH1D_mc_total, sb_region2.Vertex_X_RCut.MnvH1D_Helium[ind], sb_region2.Vertex_X_RCut.MnvH1D_Aluminium[ind],sb_region2.Vertex_X_RCut.MnvH1D_Carbon[ind],
sb_region2.Vertex_X_RCut.MnvH1D_Iron[ind], sb_region2.Vertex_X_RCut.MnvH1D_Lead[ind], sb_region2.Vertex_X_RCut.MnvH1D_Other[ind],

sb_region3.Vertex_X_RCut.MnvH1D_data, sb_region3.Vertex_X_RCut.MnvH1D_mc_total, sb_region3.Vertex_X_RCut.MnvH1D_Helium[ind], sb_region3.Vertex_X_RCut.MnvH1D_Aluminium[ind],sb_region3.Vertex_X_RCut.MnvH1D_Carbon[ind],
sb_region3.Vertex_X_RCut.MnvH1D_Iron[ind], sb_region3.Vertex_X_RCut.MnvH1D_Lead[ind], sb_region3.Vertex_X_RCut.MnvH1D_Other[ind],

sb_region4.Vertex_X_RCut.MnvH1D_data, sb_region4.Vertex_X_RCut.MnvH1D_mc_total, sb_region4.Vertex_X_RCut.MnvH1D_Helium[ind], sb_region4.Vertex_X_RCut.MnvH1D_Aluminium[ind],sb_region4.Vertex_X_RCut.MnvH1D_Carbon[ind],
sb_region4.Vertex_X_RCut.MnvH1D_Iron[ind], sb_region4.Vertex_X_RCut.MnvH1D_Lead[ind], sb_region4.Vertex_X_RCut.MnvH1D_Other[ind],
title, sb_region3.Vertex_X_RCut.Xaxis_Title, chisqrt_mapvertex_before[kX_RCut], chisqrt_mapvertex_after[kX_RCut], FitType, UseLogChi_Tool, doAreaNormalized_Tool);


title ="Vertex Y  [RCut] " + histTitle;
std::cout<<"Vertex Y  [RCut][mm]"<<std::endl;
Plot_regions_noStack(pdf_label, ind, POT_ratio,
sb_region1.Vertex_Y_RCut.MnvH1D_data, sb_region1.Vertex_Y_RCut.MnvH1D_mc_total, sb_region1.Vertex_Y_RCut.MnvH1D_Helium[ind], sb_region1.Vertex_Y_RCut.MnvH1D_Aluminium[ind],sb_region1.Vertex_Y_RCut.MnvH1D_Carbon[ind],
sb_region1.Vertex_Y_RCut.MnvH1D_Iron[ind], sb_region1.Vertex_Y_RCut.MnvH1D_Lead[ind], sb_region1.Vertex_Y_RCut.MnvH1D_Other[ind],

sb_region2.Vertex_Y_RCut.MnvH1D_data, sb_region2.Vertex_Y_RCut.MnvH1D_mc_total, sb_region2.Vertex_Y_RCut.MnvH1D_Helium[ind], sb_region2.Vertex_Y_RCut.MnvH1D_Aluminium[ind],sb_region2.Vertex_Y_RCut.MnvH1D_Carbon[ind],
sb_region2.Vertex_Y_RCut.MnvH1D_Iron[ind], sb_region2.Vertex_Y_RCut.MnvH1D_Lead[ind], sb_region2.Vertex_Y_RCut.MnvH1D_Other[ind],

sb_region3.Vertex_Y_RCut.MnvH1D_data, sb_region3.Vertex_Y_RCut.MnvH1D_mc_total, sb_region3.Vertex_Y_RCut.MnvH1D_Helium[ind], sb_region3.Vertex_Y_RCut.MnvH1D_Aluminium[ind],sb_region3.Vertex_Y_RCut.MnvH1D_Carbon[ind],
sb_region3.Vertex_Y_RCut.MnvH1D_Iron[ind], sb_region3.Vertex_Y_RCut.MnvH1D_Lead[ind], sb_region3.Vertex_Y_RCut.MnvH1D_Other[ind],

sb_region4.Vertex_Y_RCut.MnvH1D_data, sb_region4.Vertex_Y_RCut.MnvH1D_mc_total, sb_region4.Vertex_Y_RCut.MnvH1D_Helium[ind], sb_region4.Vertex_Y_RCut.MnvH1D_Aluminium[ind],sb_region4.Vertex_Y_RCut.MnvH1D_Carbon[ind],
sb_region4.Vertex_Y_RCut.MnvH1D_Iron[ind], sb_region4.Vertex_Y_RCut.MnvH1D_Lead[ind], sb_region4.Vertex_Y_RCut.MnvH1D_Other[ind],
title, sb_region3.Vertex_Y_RCut.Xaxis_Title, chisqrt_mapvertex_before[kY_RCut], chisqrt_mapvertex_after[kY_RCut], FitType, UseLogChi_Tool, doAreaNormalized_Tool);


title ="Vertex R [RCut] " + histTitle;
std::cout<<"Vertex R  [RCut][mm]"<<std::endl;
Plot_regions_noStack(pdf_label, ind, POT_ratio,
sb_region1.Vertex_R_RCut.MnvH1D_data, sb_region1.Vertex_R_RCut.MnvH1D_mc_total, sb_region1.Vertex_R_RCut.MnvH1D_Helium[ind], sb_region1.Vertex_R_RCut.MnvH1D_Aluminium[ind],sb_region1.Vertex_R_RCut.MnvH1D_Carbon[ind],
sb_region1.Vertex_R_RCut.MnvH1D_Iron[ind], sb_region1.Vertex_R_RCut.MnvH1D_Lead[ind], sb_region1.Vertex_R_RCut.MnvH1D_Other[ind],

sb_region2.Vertex_R_RCut.MnvH1D_data, sb_region2.Vertex_R_RCut.MnvH1D_mc_total, sb_region2.Vertex_R_RCut.MnvH1D_Helium[ind], sb_region2.Vertex_R_RCut.MnvH1D_Aluminium[ind],sb_region2.Vertex_R_RCut.MnvH1D_Carbon[ind],
sb_region2.Vertex_R_RCut.MnvH1D_Iron[ind], sb_region2.Vertex_R_RCut.MnvH1D_Lead[ind], sb_region2.Vertex_R_RCut.MnvH1D_Other[ind],

sb_region3.Vertex_R_RCut.MnvH1D_data, sb_region3.Vertex_R_RCut.MnvH1D_mc_total, sb_region3.Vertex_R_RCut.MnvH1D_Helium[ind], sb_region3.Vertex_R_RCut.MnvH1D_Aluminium[ind],sb_region3.Vertex_R_RCut.MnvH1D_Carbon[ind],
sb_region3.Vertex_R_RCut.MnvH1D_Iron[ind], sb_region3.Vertex_R_RCut.MnvH1D_Lead[ind], sb_region3.Vertex_R_RCut.MnvH1D_Other[ind],

sb_region4.Vertex_R_RCut.MnvH1D_data, sb_region4.Vertex_R_RCut.MnvH1D_mc_total, sb_region4.Vertex_R_RCut.MnvH1D_Helium[ind], sb_region4.Vertex_R_RCut.MnvH1D_Aluminium[ind],sb_region4.Vertex_R_RCut.MnvH1D_Carbon[ind],
sb_region4.Vertex_R_RCut.MnvH1D_Iron[ind], sb_region4.Vertex_R_RCut.MnvH1D_Lead[ind], sb_region4.Vertex_R_RCut.MnvH1D_Other[ind],
title, sb_region3.Vertex_R_RCut.Xaxis_Title, chisqrt_mapvertex_before[kR_RCut], chisqrt_mapvertex_after[kR_RCut], FitType, UseLogChi_Tool, doAreaNormalized_Tool);



  }



void Helium_3CryoRegionsSideBandTool::Plot(Helium3SideBand &sb, double POT_ratio,
   std::string fitName, std::string pdf_label, std::string Hist_title, std::string xaxislabel)
{
    std::cout<<"Plotting "<<sb.name<<std::endl;

    // Fit Results

    Plot(sb, 1, POT_ratio , fitName, pdf_label, Hist_title, xaxislabel); // Modified

}
void Helium_3CryoRegionsSideBandTool::Plot(Helium3SideBand &sb, int ind, double POT_ratio,
   std::string fitName, std::string pdf_label, std::string Hist_title, std::string xaxislabel, int index)
{
  Plot(pdf_label, ind, POT_ratio, sb.name, fitName,
    sb.MnvH1D_Vertex_X_data,
    sb.MnvH1D_Vertex_X_mc_total,
    sb.MnvH1D_Vertex_X_Helium[ind],
    sb.MnvH1D_Vertex_X_Aluminium[ind],
    sb.MnvH1D_Vertex_X_Carbon[ind],
    sb.MnvH1D_Vertex_X_Iron[ind],
    sb.MnvH1D_Vertex_X_Lead[ind],
    sb.MnvH1D_Vertex_X_Other[ind], Hist_title, sb.Xaxis_Title_Vertex_X, index,  UseLogChi_Tool);

  Plot_NoStack(pdf_label, ind, POT_ratio, sb.name, fitName,
    sb.MnvH1D_Vertex_X_data,
    sb.MnvH1D_Vertex_X_mc_total,
    sb.MnvH1D_Vertex_X_Helium[ind],
    sb.MnvH1D_Vertex_X_Aluminium[ind],
    sb.MnvH1D_Vertex_X_Carbon[ind],
    sb.MnvH1D_Vertex_X_Iron[ind],
    sb.MnvH1D_Vertex_X_Lead[ind],
    sb.MnvH1D_Vertex_X_Other[ind], Hist_title, sb.Xaxis_Title_Vertex_X, index, UseLogChi_Tool);

  Plot(pdf_label, ind, POT_ratio, sb.name, fitName,
    sb.MnvH1D_Vertex_Y_data,
    sb.MnvH1D_Vertex_Y_mc_total,
    sb.MnvH1D_Vertex_Y_Helium[ind],
    sb.MnvH1D_Vertex_Y_Aluminium[ind],
    sb.MnvH1D_Vertex_Y_Carbon[ind],
    sb.MnvH1D_Vertex_Y_Iron[ind],
    sb.MnvH1D_Vertex_Y_Lead[ind],
    sb.MnvH1D_Vertex_Y_Other[ind], Hist_title, sb.Xaxis_Title_Vertex_Y, index,  UseLogChi_Tool);

  Plot_NoStack(pdf_label, ind, POT_ratio, sb.name, fitName,
    sb.MnvH1D_Vertex_Y_data,
    sb.MnvH1D_Vertex_Y_mc_total,
    sb.MnvH1D_Vertex_Y_Helium[ind],
    sb.MnvH1D_Vertex_Y_Aluminium[ind],
    sb.MnvH1D_Vertex_Y_Carbon[ind],
    sb.MnvH1D_Vertex_Y_Iron[ind],
    sb.MnvH1D_Vertex_Y_Lead[ind],
    sb.MnvH1D_Vertex_Y_Other[ind], Hist_title, sb.Xaxis_Title_Vertex_Y, index, UseLogChi_Tool);


  Plot(pdf_label, ind, POT_ratio, sb.name, fitName,
    sb.MnvH1D_Vertex_Z_data,
    sb.MnvH1D_Vertex_Z_mc_total,
    sb.MnvH1D_Vertex_Z_Helium[ind],
    sb.MnvH1D_Vertex_Z_Aluminium[ind],
    sb.MnvH1D_Vertex_Z_Carbon[ind],
    sb.MnvH1D_Vertex_Z_Iron[ind],
    sb.MnvH1D_Vertex_Z_Lead[ind],
    sb.MnvH1D_Vertex_Z_Other[ind], Hist_title, sb.Xaxis_Title_Vertex_Z, index,  UseLogChi_Tool);

  Plot_NoStack(pdf_label, ind, POT_ratio, sb.name, fitName,
    sb.MnvH1D_Vertex_Z_data,
    sb.MnvH1D_Vertex_Z_mc_total,
    sb.MnvH1D_Vertex_Z_Helium[ind],
    sb.MnvH1D_Vertex_Z_Aluminium[ind],
    sb.MnvH1D_Vertex_Z_Carbon[ind],
    sb.MnvH1D_Vertex_Z_Iron[ind],
    sb.MnvH1D_Vertex_Z_Lead[ind],
    sb.MnvH1D_Vertex_Z_Other[ind], Hist_title, sb.Xaxis_Title_Vertex_Z, index, UseLogChi_Tool);


  Plot(pdf_label, ind, POT_ratio, sb.name, fitName,
        sb.MnvH1D_Vertex_R_data,
        sb.MnvH1D_Vertex_R_mc_total,
        sb.MnvH1D_Vertex_R_Helium[ind],
        sb.MnvH1D_Vertex_R_Aluminium[ind],
        sb.MnvH1D_Vertex_R_Carbon[ind],
        sb.MnvH1D_Vertex_R_Iron[ind],
        sb.MnvH1D_Vertex_R_Lead[ind],
        sb.MnvH1D_Vertex_R_Other[ind], Hist_title,
        sb.Xaxis_Title_Vertex_R, index, UseLogChi_Tool);

      Plot_NoStack(pdf_label, ind, POT_ratio, sb.name, fitName,
        sb.MnvH1D_Vertex_R_data,
        sb.MnvH1D_Vertex_R_mc_total,
        sb.MnvH1D_Vertex_R_Helium[ind],
        sb.MnvH1D_Vertex_R_Aluminium[ind],
        sb.MnvH1D_Vertex_R_Carbon[ind],
        sb.MnvH1D_Vertex_R_Iron[ind],
        sb.MnvH1D_Vertex_R_Lead[ind],
        sb.MnvH1D_Vertex_R_Other[ind], Hist_title, sb.Xaxis_Title_Vertex_R, index, UseLogChi_Tool);

  }



  void Helium_3CryoRegionsSideBandTool::PlotCombinedRegions_Fitting_Vars(
    Helium3SideBand &sb_region1,
    Helium3SideBand &sb_region2,
    Helium3SideBand &sb_region3,
    Helium3SideBand &sb_region4, int ind, double POT_ratio,
     std::string histTitle, std::string pdf_label,  CryoVertexDoubleMap &chisqrt_map_before,
      CryoVertexDoubleMap &chisqrt_map_after , int FitType)
  {



    //if(ind!=0){ chisqrt=chisqrt_map[kX];}

    Plot_regions(pdf_label, ind, POT_ratio,
       sb_region1.MnvH1D_Vertex_X_data, sb_region1.MnvH1D_Vertex_X_mc_total, sb_region1.MnvH1D_Vertex_X_Helium[ind], sb_region1.MnvH1D_Vertex_X_Aluminium[ind],sb_region1.MnvH1D_Vertex_X_Carbon[ind],
       sb_region1.MnvH1D_Vertex_X_Iron[ind], sb_region1.MnvH1D_Vertex_X_Lead[ind], sb_region1.MnvH1D_Vertex_X_Other[ind],

       sb_region2.MnvH1D_Vertex_X_data, sb_region2.MnvH1D_Vertex_X_mc_total, sb_region2.MnvH1D_Vertex_X_Helium[ind], sb_region2.MnvH1D_Vertex_X_Aluminium[ind],sb_region2.MnvH1D_Vertex_X_Carbon[ind],
       sb_region2.MnvH1D_Vertex_X_Iron[ind], sb_region2.MnvH1D_Vertex_X_Lead[ind], sb_region2.MnvH1D_Vertex_X_Other[ind],

       sb_region3.MnvH1D_Vertex_X_data, sb_region3.MnvH1D_Vertex_X_mc_total, sb_region3.MnvH1D_Vertex_X_Helium[ind], sb_region3.MnvH1D_Vertex_X_Aluminium[ind],sb_region3.MnvH1D_Vertex_X_Carbon[ind],
       sb_region3.MnvH1D_Vertex_X_Iron[ind], sb_region3.MnvH1D_Vertex_X_Lead[ind], sb_region3.MnvH1D_Vertex_X_Other[ind],

       sb_region4.MnvH1D_Vertex_X_data, sb_region4.MnvH1D_Vertex_X_mc_total, sb_region4.MnvH1D_Vertex_X_Helium[ind], sb_region4.MnvH1D_Vertex_X_Aluminium[ind],sb_region4.MnvH1D_Vertex_X_Carbon[ind],
       sb_region4.MnvH1D_Vertex_X_Iron[ind], sb_region4.MnvH1D_Vertex_X_Lead[ind], sb_region4.MnvH1D_Vertex_X_Other[ind],
       histTitle, sb_region3.Xaxis_Title_Vertex_X, chisqrt_map_before[kX], chisqrt_map_after[kX], FitType, UseLogChi_Tool, doAreaNormalized_Tool, set_ymax_forFitVars, YaxisMax_X);

       //if(ind==0){chisqrt_map[kX] = chisqrt;}
       //if(ind!=0){ chisqrt=chisqrt_map[kY];}

       Plot_regions(pdf_label, ind, POT_ratio,
         sb_region1.MnvH1D_Vertex_Y_data,
         sb_region1.MnvH1D_Vertex_Y_mc_total,
         sb_region1.MnvH1D_Vertex_Y_Helium[ind],
         sb_region1.MnvH1D_Vertex_Y_Aluminium[ind],
         sb_region1.MnvH1D_Vertex_Y_Carbon[ind],
         sb_region1.MnvH1D_Vertex_Y_Iron[ind],
         sb_region1.MnvH1D_Vertex_Y_Lead[ind],
         sb_region1.MnvH1D_Vertex_Y_Other[ind],

         sb_region2.MnvH1D_Vertex_Y_data,
         sb_region2.MnvH1D_Vertex_Y_mc_total,
         sb_region2.MnvH1D_Vertex_Y_Helium[ind],
         sb_region2.MnvH1D_Vertex_Y_Aluminium[ind],
         sb_region2.MnvH1D_Vertex_Y_Carbon[ind],
         sb_region2.MnvH1D_Vertex_Y_Iron[ind],
         sb_region2.MnvH1D_Vertex_Y_Lead[ind],
         sb_region2.MnvH1D_Vertex_Y_Other[ind],

         sb_region3.MnvH1D_Vertex_Y_data,
         sb_region3.MnvH1D_Vertex_Y_mc_total,
         sb_region3.MnvH1D_Vertex_Y_Helium[ind],
         sb_region3.MnvH1D_Vertex_Y_Aluminium[ind],
         sb_region3.MnvH1D_Vertex_Y_Carbon[ind],
         sb_region3.MnvH1D_Vertex_Y_Iron[ind],
         sb_region3.MnvH1D_Vertex_Y_Lead[ind],
         sb_region3.MnvH1D_Vertex_Y_Other[ind],

         sb_region4.MnvH1D_Vertex_Y_data,
         sb_region4.MnvH1D_Vertex_Y_mc_total,
         sb_region4.MnvH1D_Vertex_Y_Helium[ind],
         sb_region4.MnvH1D_Vertex_Y_Aluminium[ind],
         sb_region4.MnvH1D_Vertex_Y_Carbon[ind],
         sb_region4.MnvH1D_Vertex_Y_Iron[ind],
         sb_region4.MnvH1D_Vertex_Y_Lead[ind],
         sb_region4.MnvH1D_Vertex_Y_Other[ind],
         histTitle, sb_region3.Xaxis_Title_Vertex_Y, chisqrt_map_before[kY], chisqrt_map_after[kY], FitType , UseLogChi_Tool, doAreaNormalized_Tool, set_ymax_forFitVars, YaxisMax_Y );

          //if(ind==0){chisqrt_map[kY] = chisqrt;}
          //if(ind!=0){ chisqrt=chisqrt_map[kZ];}

          Plot_regions(pdf_label, ind, POT_ratio,
             sb_region1.MnvH1D_Vertex_Z_data, sb_region1.MnvH1D_Vertex_Z_mc_total, sb_region1.MnvH1D_Vertex_Z_Helium[ind], sb_region1.MnvH1D_Vertex_Z_Aluminium[ind],sb_region1.MnvH1D_Vertex_Z_Carbon[ind],
             sb_region1.MnvH1D_Vertex_Z_Iron[ind], sb_region1.MnvH1D_Vertex_Z_Lead[ind], sb_region1.MnvH1D_Vertex_Z_Other[ind],

             sb_region2.MnvH1D_Vertex_Z_data, sb_region2.MnvH1D_Vertex_Z_mc_total, sb_region2.MnvH1D_Vertex_Z_Helium[ind], sb_region2.MnvH1D_Vertex_Z_Aluminium[ind],sb_region2.MnvH1D_Vertex_Z_Carbon[ind],
             sb_region2.MnvH1D_Vertex_Z_Iron[ind], sb_region2.MnvH1D_Vertex_Z_Lead[ind], sb_region2.MnvH1D_Vertex_Z_Other[ind],

             sb_region3.MnvH1D_Vertex_Z_data, sb_region3.MnvH1D_Vertex_Z_mc_total, sb_region3.MnvH1D_Vertex_Z_Helium[ind], sb_region3.MnvH1D_Vertex_Z_Aluminium[ind],sb_region3.MnvH1D_Vertex_Z_Carbon[ind],
             sb_region3.MnvH1D_Vertex_Z_Iron[ind], sb_region3.MnvH1D_Vertex_Z_Lead[ind], sb_region3.MnvH1D_Vertex_Z_Other[ind],

             sb_region4.MnvH1D_Vertex_Z_data, sb_region4.MnvH1D_Vertex_Z_mc_total, sb_region4.MnvH1D_Vertex_Z_Helium[ind], sb_region4.MnvH1D_Vertex_Z_Aluminium[ind],sb_region4.MnvH1D_Vertex_Z_Carbon[ind],
             sb_region4.MnvH1D_Vertex_Z_Iron[ind], sb_region4.MnvH1D_Vertex_Z_Lead[ind], sb_region4.MnvH1D_Vertex_Z_Other[ind],
             histTitle, sb_region3.Xaxis_Title_Vertex_Z, chisqrt_map_before[kZ], chisqrt_map_after[kZ], FitType, UseLogChi_Tool, doAreaNormalized_Tool, set_ymax_forFitVars, YaxisMax_Z);

             Plot_regions_addlinerFittoRatio(pdf_label, ind, POT_ratio,
               sb_region1.MnvH1D_Vertex_Z_data, sb_region1.MnvH1D_Vertex_Z_mc_total, sb_region1.MnvH1D_Vertex_Z_Helium[ind], sb_region1.MnvH1D_Vertex_Z_Aluminium[ind],sb_region1.MnvH1D_Vertex_Z_Carbon[ind],
               sb_region1.MnvH1D_Vertex_Z_Iron[ind], sb_region1.MnvH1D_Vertex_Z_Lead[ind], sb_region1.MnvH1D_Vertex_Z_Other[ind],

               sb_region2.MnvH1D_Vertex_Z_data, sb_region2.MnvH1D_Vertex_Z_mc_total, sb_region2.MnvH1D_Vertex_Z_Helium[ind], sb_region2.MnvH1D_Vertex_Z_Aluminium[ind],sb_region2.MnvH1D_Vertex_Z_Carbon[ind],
               sb_region2.MnvH1D_Vertex_Z_Iron[ind], sb_region2.MnvH1D_Vertex_Z_Lead[ind], sb_region2.MnvH1D_Vertex_Z_Other[ind],

               sb_region3.MnvH1D_Vertex_Z_data, sb_region3.MnvH1D_Vertex_Z_mc_total, sb_region3.MnvH1D_Vertex_Z_Helium[ind], sb_region3.MnvH1D_Vertex_Z_Aluminium[ind],sb_region3.MnvH1D_Vertex_Z_Carbon[ind],
               sb_region3.MnvH1D_Vertex_Z_Iron[ind], sb_region3.MnvH1D_Vertex_Z_Lead[ind], sb_region3.MnvH1D_Vertex_Z_Other[ind],

               sb_region4.MnvH1D_Vertex_Z_data, sb_region4.MnvH1D_Vertex_Z_mc_total, sb_region4.MnvH1D_Vertex_Z_Helium[ind], sb_region4.MnvH1D_Vertex_Z_Aluminium[ind],sb_region4.MnvH1D_Vertex_Z_Carbon[ind],
               sb_region4.MnvH1D_Vertex_Z_Iron[ind], sb_region4.MnvH1D_Vertex_Z_Lead[ind], sb_region4.MnvH1D_Vertex_Z_Other[ind],
               histTitle, sb_region3.Xaxis_Title_Vertex_Z, chisqrt_map_before[kZ], chisqrt_map_after[kZ], FitType, UseLogChi_Tool, doAreaNormalized_Tool, set_ymax_forFitVars, YaxisMax_Z);

               //if(ind==0){chisqrt_map[kZ] = chisqrt;}
               //if(ind!=0){ chisqrt=chisqrt_map[kR];}

             Plot_regions(pdf_label, ind, POT_ratio,
                sb_region1.MnvH1D_Vertex_R_data, sb_region1.MnvH1D_Vertex_R_mc_total, sb_region1.MnvH1D_Vertex_R_Helium[ind], sb_region1.MnvH1D_Vertex_R_Aluminium[ind],sb_region1.MnvH1D_Vertex_R_Carbon[ind],
                sb_region1.MnvH1D_Vertex_R_Iron[ind], sb_region1.MnvH1D_Vertex_R_Lead[ind], sb_region1.MnvH1D_Vertex_R_Other[ind],

                sb_region2.MnvH1D_Vertex_R_data, sb_region2.MnvH1D_Vertex_R_mc_total, sb_region2.MnvH1D_Vertex_R_Helium[ind], sb_region2.MnvH1D_Vertex_R_Aluminium[ind],sb_region2.MnvH1D_Vertex_R_Carbon[ind],
                sb_region2.MnvH1D_Vertex_R_Iron[ind], sb_region2.MnvH1D_Vertex_R_Lead[ind], sb_region2.MnvH1D_Vertex_R_Other[ind],

                sb_region3.MnvH1D_Vertex_R_data, sb_region3.MnvH1D_Vertex_R_mc_total, sb_region3.MnvH1D_Vertex_R_Helium[ind], sb_region3.MnvH1D_Vertex_R_Aluminium[ind],sb_region3.MnvH1D_Vertex_R_Carbon[ind],
                sb_region3.MnvH1D_Vertex_R_Iron[ind], sb_region3.MnvH1D_Vertex_R_Lead[ind], sb_region3.MnvH1D_Vertex_R_Other[ind],

                sb_region4.MnvH1D_Vertex_R_data, sb_region4.MnvH1D_Vertex_R_mc_total, sb_region4.MnvH1D_Vertex_R_Helium[ind], sb_region4.MnvH1D_Vertex_R_Aluminium[ind],sb_region4.MnvH1D_Vertex_R_Carbon[ind],
                sb_region4.MnvH1D_Vertex_R_Iron[ind], sb_region4.MnvH1D_Vertex_R_Lead[ind], sb_region4.MnvH1D_Vertex_R_Other[ind],
                histTitle, sb_region3.Xaxis_Title_Vertex_R, chisqrt_map_before[kR], chisqrt_map_after[kR], FitType, UseLogChi_Tool, doAreaNormalized_Tool, set_ymax_forFitVars, YaxisMax_R);

                //if(ind==0){chisqrt_map[kR] = chisqrt;}
    }

    void Helium_3CryoRegionsSideBandTool::PlotCombinedRegions_Fitting_Vars_NoStack(
      Helium3SideBand &sb_region1,
      Helium3SideBand &sb_region2,
      Helium3SideBand &sb_region3,
      Helium3SideBand &sb_region4, int ind, double POT_ratio,
       std::string histTitle, std::string pdf_label,  CryoVertexDoubleMap &chisqrt_map_before,
        CryoVertexDoubleMap &chisqrt_map_after , int FitType)
    {


      //if(ind!=0){ chisqrt=chisqrt_map[kX];}

      Plot_regions_noStack(pdf_label, ind, POT_ratio,
         sb_region1.MnvH1D_Vertex_X_data, sb_region1.MnvH1D_Vertex_X_mc_total, sb_region1.MnvH1D_Vertex_X_Helium[ind], sb_region1.MnvH1D_Vertex_X_Aluminium[ind],sb_region1.MnvH1D_Vertex_X_Carbon[ind],
         sb_region1.MnvH1D_Vertex_X_Iron[ind], sb_region1.MnvH1D_Vertex_X_Lead[ind], sb_region1.MnvH1D_Vertex_X_Other[ind],
         sb_region2.MnvH1D_Vertex_X_data, sb_region2.MnvH1D_Vertex_X_mc_total, sb_region2.MnvH1D_Vertex_X_Helium[ind], sb_region2.MnvH1D_Vertex_X_Aluminium[ind],sb_region2.MnvH1D_Vertex_X_Carbon[ind],
         sb_region2.MnvH1D_Vertex_X_Iron[ind], sb_region2.MnvH1D_Vertex_X_Lead[ind], sb_region2.MnvH1D_Vertex_X_Other[ind],
         sb_region3.MnvH1D_Vertex_X_data, sb_region3.MnvH1D_Vertex_X_mc_total, sb_region3.MnvH1D_Vertex_X_Helium[ind], sb_region3.MnvH1D_Vertex_X_Aluminium[ind],sb_region3.MnvH1D_Vertex_X_Carbon[ind],
         sb_region3.MnvH1D_Vertex_X_Iron[ind], sb_region3.MnvH1D_Vertex_X_Lead[ind], sb_region3.MnvH1D_Vertex_X_Other[ind],
         sb_region4.MnvH1D_Vertex_X_data, sb_region4.MnvH1D_Vertex_X_mc_total, sb_region4.MnvH1D_Vertex_X_Helium[ind], sb_region4.MnvH1D_Vertex_X_Aluminium[ind],sb_region4.MnvH1D_Vertex_X_Carbon[ind],
         sb_region4.MnvH1D_Vertex_X_Iron[ind], sb_region4.MnvH1D_Vertex_X_Lead[ind], sb_region4.MnvH1D_Vertex_X_Other[ind],
         histTitle, sb_region3.Xaxis_Title_Vertex_X, chisqrt_map_before[kX], chisqrt_map_after[kX], FitType, UseLogChi_Tool, doAreaNormalized_Tool);

         //if(ind==0){chisqrt_map[kX] = chisqrt;}
         //if(ind!=0){ chisqrt=chisqrt_map[kY];}

         Plot_regions_noStack(pdf_label, ind, POT_ratio,
           sb_region1.MnvH1D_Vertex_Y_data,
           sb_region1.MnvH1D_Vertex_Y_mc_total,
           sb_region1.MnvH1D_Vertex_Y_Helium[ind],
           sb_region1.MnvH1D_Vertex_Y_Aluminium[ind],
           sb_region1.MnvH1D_Vertex_Y_Carbon[ind],
           sb_region1.MnvH1D_Vertex_Y_Iron[ind],
           sb_region1.MnvH1D_Vertex_Y_Lead[ind],
           sb_region1.MnvH1D_Vertex_Y_Other[ind],

           sb_region2.MnvH1D_Vertex_Y_data,
           sb_region2.MnvH1D_Vertex_Y_mc_total,
           sb_region2.MnvH1D_Vertex_Y_Helium[ind],
           sb_region2.MnvH1D_Vertex_Y_Aluminium[ind],
           sb_region2.MnvH1D_Vertex_Y_Carbon[ind],
           sb_region2.MnvH1D_Vertex_Y_Iron[ind],
           sb_region2.MnvH1D_Vertex_Y_Lead[ind],
           sb_region2.MnvH1D_Vertex_Y_Other[ind],

           sb_region3.MnvH1D_Vertex_Y_data,
           sb_region3.MnvH1D_Vertex_Y_mc_total,
           sb_region3.MnvH1D_Vertex_Y_Helium[ind],
           sb_region3.MnvH1D_Vertex_Y_Aluminium[ind],
           sb_region3.MnvH1D_Vertex_Y_Carbon[ind],
           sb_region3.MnvH1D_Vertex_Y_Iron[ind],
           sb_region3.MnvH1D_Vertex_Y_Lead[ind],
           sb_region3.MnvH1D_Vertex_Y_Other[ind],

           sb_region4.MnvH1D_Vertex_Y_data,
           sb_region4.MnvH1D_Vertex_Y_mc_total,
           sb_region4.MnvH1D_Vertex_Y_Helium[ind],
           sb_region4.MnvH1D_Vertex_Y_Aluminium[ind],
           sb_region4.MnvH1D_Vertex_Y_Carbon[ind],
           sb_region4.MnvH1D_Vertex_Y_Iron[ind],
           sb_region4.MnvH1D_Vertex_Y_Lead[ind],
           sb_region4.MnvH1D_Vertex_Y_Other[ind],
           histTitle, sb_region3.Xaxis_Title_Vertex_Y, chisqrt_map_before[kY], chisqrt_map_after[kY], FitType , UseLogChi_Tool , doAreaNormalized_Tool );

            //if(ind==0){chisqrt_map[kY] = chisqrt;}
            //if(ind!=0){ chisqrt=chisqrt_map[kZ];}

          Plot_regions_noStack(pdf_label, ind, POT_ratio,
            sb_region1.MnvH1D_Vertex_Z_data,
            sb_region1.MnvH1D_Vertex_Z_mc_total,
            sb_region1.MnvH1D_Vertex_Z_Helium[ind],
            sb_region1.MnvH1D_Vertex_Z_Aluminium[ind],
            sb_region1.MnvH1D_Vertex_Z_Carbon[ind],
            sb_region1.MnvH1D_Vertex_Z_Iron[ind],
            sb_region1.MnvH1D_Vertex_Z_Lead[ind],
            sb_region1.MnvH1D_Vertex_Z_Other[ind],

            sb_region2.MnvH1D_Vertex_Z_data,
            sb_region2.MnvH1D_Vertex_Z_mc_total,
            sb_region2.MnvH1D_Vertex_Z_Helium[ind],
            sb_region2.MnvH1D_Vertex_Z_Aluminium[ind],
            sb_region2.MnvH1D_Vertex_Z_Carbon[ind],
            sb_region2.MnvH1D_Vertex_Z_Iron[ind],
            sb_region2.MnvH1D_Vertex_Z_Lead[ind],
            sb_region2.MnvH1D_Vertex_Z_Other[ind],

            sb_region3.MnvH1D_Vertex_Z_data,
            sb_region3.MnvH1D_Vertex_Z_mc_total,
            sb_region3.MnvH1D_Vertex_Z_Helium[ind],
            sb_region3.MnvH1D_Vertex_Z_Aluminium[ind],
            sb_region3.MnvH1D_Vertex_Z_Carbon[ind],
            sb_region3.MnvH1D_Vertex_Z_Iron[ind],
            sb_region3.MnvH1D_Vertex_Z_Lead[ind],
            sb_region3.MnvH1D_Vertex_Z_Other[ind],

            sb_region4.MnvH1D_Vertex_Z_data,
            sb_region4.MnvH1D_Vertex_Z_mc_total,
            sb_region4.MnvH1D_Vertex_Z_Helium[ind],
            sb_region4.MnvH1D_Vertex_Z_Aluminium[ind],
            sb_region4.MnvH1D_Vertex_Z_Carbon[ind],
            sb_region4.MnvH1D_Vertex_Z_Iron[ind],
            sb_region4.MnvH1D_Vertex_Z_Lead[ind],
            sb_region4.MnvH1D_Vertex_Z_Other[ind],
            histTitle, sb_region3.Xaxis_Title_Vertex_Z, chisqrt_map_before[kZ], chisqrt_map_after[kZ], FitType, UseLogChi_Tool, doAreaNormalized_Tool);

               //if(ind==0){chisqrt_map[kZ] = chisqrt;}
               //if(ind!=0){ chisqrt=chisqrt_map[kR];}

              Plot_regions_noStack(pdf_label, ind, POT_ratio,
                  sb_region1.MnvH1D_Vertex_R_data, sb_region1.MnvH1D_Vertex_R_mc_total, sb_region1.MnvH1D_Vertex_R_Helium[ind], sb_region1.MnvH1D_Vertex_R_Aluminium[ind],sb_region1.MnvH1D_Vertex_R_Carbon[ind],
                  sb_region1.MnvH1D_Vertex_R_Iron[ind], sb_region1.MnvH1D_Vertex_R_Lead[ind], sb_region1.MnvH1D_Vertex_R_Other[ind],

                  sb_region2.MnvH1D_Vertex_R_data, sb_region2.MnvH1D_Vertex_R_mc_total, sb_region2.MnvH1D_Vertex_R_Helium[ind], sb_region2.MnvH1D_Vertex_R_Aluminium[ind],sb_region2.MnvH1D_Vertex_R_Carbon[ind],
                  sb_region2.MnvH1D_Vertex_R_Iron[ind], sb_region2.MnvH1D_Vertex_R_Lead[ind], sb_region2.MnvH1D_Vertex_R_Other[ind],

                  sb_region3.MnvH1D_Vertex_R_data, sb_region3.MnvH1D_Vertex_R_mc_total, sb_region3.MnvH1D_Vertex_R_Helium[ind], sb_region3.MnvH1D_Vertex_R_Aluminium[ind],sb_region3.MnvH1D_Vertex_R_Carbon[ind],
                  sb_region3.MnvH1D_Vertex_R_Iron[ind], sb_region3.MnvH1D_Vertex_R_Lead[ind], sb_region3.MnvH1D_Vertex_R_Other[ind],

                  sb_region4.MnvH1D_Vertex_R_data, sb_region4.MnvH1D_Vertex_R_mc_total, sb_region4.MnvH1D_Vertex_R_Helium[ind], sb_region4.MnvH1D_Vertex_R_Aluminium[ind],sb_region4.MnvH1D_Vertex_R_Carbon[ind],
                  sb_region4.MnvH1D_Vertex_R_Iron[ind], sb_region4.MnvH1D_Vertex_R_Lead[ind], sb_region4.MnvH1D_Vertex_R_Other[ind],
                  histTitle, sb_region3.Xaxis_Title_Vertex_R, chisqrt_map_before[kR], chisqrt_map_after[kR], FitType, UseLogChi_Tool, doAreaNormalized_Tool);

                  //if(ind==0){chisqrt_map[kR] = chisqrt;}
      }


void Helium_3CryoRegionsSideBandTool::POTScale_SideBand_MC_total(Helium3SideBand &sb){
  if( sb.POT_MC == 9999  ){
    sb.POT_MC = 1.0;
    exit(EXIT_FAILURE);
  }

  //std::cout<<"inside: POTScale_SideBand_MC_total"<<std::endl;

  sb.MnvH1D_Vertex_X_mc_total->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_Y_mc_total->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_Z_mc_total->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_R_mc_total->Scale(sb.POT_MC);
}




void Helium_3CryoRegionsSideBandTool::POTScale_SideBand_MC_Material(Helium3SideBand &sb, int ind ){
  if( sb.POT_MC == 9999  ){
    std::cout<<"POTScale_SideBand_MC_Material::POT Hasn't been set: returing and set values to 1.0 "<<std::endl;
    exit(EXIT_FAILURE);
    sb.POT_MC = 1.0;
  }

  sb.MnvH1D_Vertex_X_Helium[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_X_Aluminium[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_X_Carbon[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_X_Iron[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_X_Lead[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_X_Other[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_Y_Helium[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_Y_Aluminium[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_Y_Carbon[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_Y_Iron[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_Y_Lead[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_Y_Other[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_Z_Helium[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_Z_Aluminium[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_Z_Carbon[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_Z_Iron[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_Z_Lead[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_Z_Other[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_R_Helium[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_R_Aluminium[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_R_Carbon[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_R_Iron[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_R_Lead[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_R_Other[ind]->Scale(sb.POT_MC);

}

void Helium_3CryoRegionsSideBandTool::POTScale_SideBand_MC_Material(HeliumNSideBand &sb, int ind ){
  if( sb.POT_MC == 9999  ){
    std::cout<<"POTScale_SideBand_MC_Material::POT Hasn't been set: returing and set values to 1.0 "<<std::endl;
    exit(EXIT_FAILURE);
    sb.POT_MC = 1.0;
  }

  sb.MnvH1D_Vertex_X_Helium[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_X_Aluminium[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_X_Carbon[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_X_Iron[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_X_Lead[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_X_Other[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_Y_Helium[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_Y_Aluminium[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_Y_Carbon[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_Y_Iron[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_Y_Lead[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_Y_Other[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_Z_Helium[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_Z_Aluminium[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_Z_Carbon[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_Z_Iron[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_Z_Lead[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_Z_Other[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_R_Helium[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_R_Aluminium[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_R_Carbon[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_R_Iron[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_R_Lead[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_R_Other[ind]->Scale(sb.POT_MC);

  POTScale_Var_MC_Material(sb.muon_PZ,    sb.POT_MC,  ind);
  POTScale_Var_MC_Material(sb.muon_PT,    sb.POT_MC,  ind);
  POTScale_Var_MC_Material(sb.muon_theta, sb.POT_MC,  ind);
  POTScale_Var_MC_Material(sb.muon_E,     sb.POT_MC,  ind);
  POTScale_Var_MC_Material(sb.muon_doca,  sb.POT_MC,  ind);
  POTScale_Var_MC_Material(sb.DistancetoEdge, sb.POT_MC,  ind);
  POTScale_Var_MC_Material(sb.SecTrk_doca, sb.POT_MC,  ind);
  POTScale_Var_MC_Material(sb.TrackLength, sb.POT_MC,  ind);

}

void Helium_3CryoRegionsSideBandTool::POTScale_SideBand_MC_Material_FitVars(HeliumNSideBand &sb, int ind ){
  if( sb.POT_MC == 9999  ){
    std::cout<<"POTScale_SideBand_MC_Material::POT Hasn't been set: returing and set values to 1.0 "<<std::endl;
    exit(EXIT_FAILURE);
    sb.POT_MC = 1.0;
  }
  std::cout<<"POTScale_SideBand_MC_Material_FitVars : Pot Scaler: "<< sb.POT_MC << std::endl;

  sb.MnvH1D_Vertex_X_Helium[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_X_Aluminium[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_X_Carbon[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_X_Iron[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_X_Lead[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_X_Other[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_Y_Helium[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_Y_Aluminium[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_Y_Carbon[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_Y_Iron[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_Y_Lead[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_Y_Other[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_Z_Helium[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_Z_Aluminium[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_Z_Carbon[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_Z_Iron[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_Z_Lead[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_Z_Other[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_R_Helium[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_R_Aluminium[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_R_Carbon[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_R_Iron[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_R_Lead[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Vertex_R_Other[ind]->Scale(sb.POT_MC);


}

void Helium_3CryoRegionsSideBandTool::POTScale_SideBand_Data(Helium3SideBand &sb){

  sb.MnvH1D_Vertex_X_data->Scale(sb.POT_Data);
  sb.MnvH1D_Vertex_Y_data->Scale(sb.POT_Data);
  sb.MnvH1D_Vertex_Z_data->Scale(sb.POT_Data);
  sb.MnvH1D_Vertex_R_data->Scale(sb.POT_Data);

}


void Helium_3CryoRegionsSideBandTool::POTScale_SideBand_Data(HeliumNSideBand &sb){
std::cout<< "POTScale_SideBand_Data :  "<< sb.POT_Data << std::endl;
  sb.MnvH1D_Vertex_X_data->Scale(sb.POT_Data);
  sb.MnvH1D_Vertex_Y_data->Scale(sb.POT_Data);
  sb.MnvH1D_Vertex_Z_data->Scale(sb.POT_Data);
  sb.MnvH1D_Vertex_R_data->Scale(sb.POT_Data);

  POTScale_Var_Data(sb.muon_PT,    sb.POT_Data);
  POTScale_Var_Data(sb.muon_PZ,    sb.POT_Data);
  POTScale_Var_Data(sb.muon_theta, sb.POT_Data);
  POTScale_Var_Data(sb.muon_E,     sb.POT_Data);
  POTScale_Var_Data(sb.muon_doca,  sb.POT_Data);
  POTScale_Var_Data(sb.DistancetoEdge, sb.POT_Data);
  POTScale_Var_Data(sb.SecTrk_doca, sb.POT_Data);
  POTScale_Var_Data(sb.TrackLength, sb.POT_Data);

}




void Helium_3CryoRegionsSideBandTool::POTScale_Var_MC_total(XSec_Var3band &xsec_var, double POTscaler){
//std::cout<<"Inside::POTScale_Var_MC_total- Scaling MnvH1D_mc_total "<<std::endl;
xsec_var.MnvH1D_mc_total->Scale( POTscaler);
//std::cout<<"Finshed Scaling MC Total Var"<<std::endl;

}

void Helium_3CryoRegionsSideBandTool::POTScale_Var_Data(XSec_Var3band &xsec_var, double POTscaler){
  xsec_var.MnvH1D_data->Scale( POTscaler);
  //std::cout<<"Finshed Scaling data Var"<<std::endl;
}
void Helium_3CryoRegionsSideBandTool::POTScale_Var_Data(XSec_VarNband &xsec_var, double POTscaler){
  xsec_var.MnvH1D_data->Scale( POTscaler);
  //std::cout<<"Finshed Scaling data Var"<<std::endl;
}


void Helium_3CryoRegionsSideBandTool::POTScale_Var_MC_Material(XSec_Var3band &xsec_var, double POTscaler, int ind){
  xsec_var.MnvH1D_Helium[ind]->Scale( POTscaler);
  xsec_var.MnvH1D_Aluminium[ind]->Scale( POTscaler);
  xsec_var.MnvH1D_Carbon[ind]->Scale( POTscaler);
  xsec_var.MnvH1D_Lead[ind]->Scale( POTscaler);
  xsec_var.MnvH1D_Iron[ind]->Scale( POTscaler);
  xsec_var.MnvH1D_Other[ind]->Scale( POTscaler);
    //std::cout<<"Finshed Scaling MC material Var"<<std::endl;
}

void Helium_3CryoRegionsSideBandTool::POTScale_Var_MC_Material(XSec_VarNband &xsec_var, double POTscaler, int ind){
  xsec_var.MnvH1D_Helium[ind]->Scale( POTscaler);
  xsec_var.MnvH1D_Aluminium[ind]->Scale( POTscaler);
  xsec_var.MnvH1D_Carbon[ind]->Scale( POTscaler);
  xsec_var.MnvH1D_Lead[ind]->Scale( POTscaler);
  xsec_var.MnvH1D_Iron[ind]->Scale( POTscaler);
  xsec_var.MnvH1D_Other[ind]->Scale( POTscaler);
    //std::cout<<"Finshed Scaling MC material Var"<<std::endl;
}



void Helium_3CryoRegionsSideBandTool::init_POTScale_Var(XSec_Var3band &xsec_var, double POTscaler_MC, double Potscaler_data){
  //std::cout<<"inside::init_POTScale_Var"<<std::endl;

  POTScale_Var_MC_total(xsec_var, POTscaler_MC);
  POTScale_Var_MC_Material(xsec_var, POTscaler_MC, 0);
  POTScale_Var_Data(xsec_var, Potscaler_data);

}

void Helium_3CryoRegionsSideBandTool::init_POTScale_Var(XSec_VarNband &xsec_var, double POTscaler_MC, double Potscaler_data){
  //std::cout<<"inside::init_POTScale_Var"<<std::endl;
  POTScale_Var_Data(xsec_var, Potscaler_data);

}



void Helium_3CryoRegionsSideBandTool::init_POTScale_SideBand(Helium3SideBand &sb){
  //std::cout<<"inside::init_POTScale_SideBand including Vars"<<std::endl;
  POTScale_SideBand_MC_total(sb);
  POTScale_SideBand_MC_Material(sb, 0 );
  POTScale_SideBand_Data(sb);

  //std::cout<<"Scaling vars" <<std::endl;

  init_POTScale_Var(sb.muon_PT,                      sb.POT_MC ,sb.POT_Data );
  init_POTScale_Var(sb.muon_PZ,                      sb.POT_MC ,sb.POT_Data );
  init_POTScale_Var(sb.muon_theta,                   sb.POT_MC ,sb.POT_Data );
  init_POTScale_Var(sb.muon_E,                       sb.POT_MC ,sb.POT_Data );
  init_POTScale_Var(sb.muon_doca,                    sb.POT_MC ,sb.POT_Data );
  init_POTScale_Var(sb.DistancetoEdge,               sb.POT_MC ,sb.POT_Data );
  init_POTScale_Var(sb.SecTrk_doca,                  sb.POT_MC ,sb.POT_Data );
  init_POTScale_Var(sb.TrackLength,                  sb.POT_MC ,sb.POT_Data );
  init_POTScale_Var(sb.DistancetoUpstreamCap,        sb.POT_MC ,sb.POT_Data );
  init_POTScale_Var(sb.DistancetoDownstreamCap,      sb.POT_MC ,sb.POT_Data );
  init_POTScale_Var(sb.DistancetoUpstreamCap_RCut,   sb.POT_MC ,sb.POT_Data );
  init_POTScale_Var(sb.DistancetoDownstreamCap_RCut, sb.POT_MC ,sb.POT_Data );
  init_POTScale_Var(sb.Vertex_Z_RCut,                sb.POT_MC ,sb.POT_Data );
  init_POTScale_Var(sb.Vertex_X_RCut,                sb.POT_MC ,sb.POT_Data );
  init_POTScale_Var(sb.Vertex_Y_RCut,                sb.POT_MC ,sb.POT_Data );
  init_POTScale_Var(sb.Vertex_R_RCut,                sb.POT_MC ,sb.POT_Data );
  //init_POTScale_Var(sb.DistancetoEdge_Caps,                sb.POT_MC ,sb.POT_Data );
  //init_POTScale_Var(sb.DistancetoEdge_Barrel,                sb.POT_MC ,sb.POT_Data );


}


void Helium_3CryoRegionsSideBandTool::init_POTScale_SideBand_Vars(Helium3SideBand &sb)
{
init_POTScale_Var(sb.muon_PT,                      sb.POT_MC ,sb.POT_Data );
init_POTScale_Var(sb.muon_PZ,                      sb.POT_MC ,sb.POT_Data );
init_POTScale_Var(sb.muon_theta,                   sb.POT_MC ,sb.POT_Data );
init_POTScale_Var(sb.muon_E,                       sb.POT_MC ,sb.POT_Data );
init_POTScale_Var(sb.DistancetoEdge,               sb.POT_MC ,sb.POT_Data );
init_POTScale_Var(sb.SecTrk_doca,                  sb.POT_MC ,sb.POT_Data );
init_POTScale_Var(sb.TrackLength,                  sb.POT_MC ,sb.POT_Data );
init_POTScale_Var(sb.DistancetoUpstreamCap,        sb.POT_MC ,sb.POT_Data );
init_POTScale_Var(sb.DistancetoDownstreamCap,      sb.POT_MC ,sb.POT_Data );
init_POTScale_Var(sb.DistancetoUpstreamCap_RCut,   sb.POT_MC ,sb.POT_Data );
init_POTScale_Var(sb.DistancetoDownstreamCap_RCut, sb.POT_MC ,sb.POT_Data );
init_POTScale_Var(sb.Vertex_Z_RCut,                sb.POT_MC ,sb.POT_Data );
init_POTScale_Var(sb.Vertex_X_RCut,                sb.POT_MC ,sb.POT_Data );
init_POTScale_Var(sb.Vertex_Y_RCut,                sb.POT_MC ,sb.POT_Data );
init_POTScale_Var(sb.Vertex_R_RCut,                sb.POT_MC ,sb.POT_Data );

//init_POTScale_Var(sb.DistancetoEdge_Caps,               sb.POT_MC ,sb.POT_Data );
//init_POTScale_Var(sb.DistancetoEdge_Barrel,               sb.POT_MC ,sb.POT_Data );


}

void Helium_3CryoRegionsSideBandTool::init_POTScale_FittingVar_onlySideBand(Helium3SideBand &sb){
  //std::cout<<"init_POTScale_FittingVar_onlySideBand"<<std::endl;
  POTScale_SideBand_MC_total(sb);
  POTScale_SideBand_MC_Material(sb, 0 );
  POTScale_SideBand_Data(sb);
}



void Helium_3CryoRegionsSideBandTool::init_POTScale_Full(){

  init_POTScale_SideBand(Full);
  init_POTScale_SideBand(Full_UpstreamCap);
  init_POTScale_SideBand(Full_Barrel);
  init_POTScale_SideBand(Full_DownstreamCap);
  init_POTScale_SideBand(Full_DownstreamConcaveCap);
}

void Helium_3CryoRegionsSideBandTool::init_POTScale_Empty(){
  init_POTScale_SideBand(Empty);
  init_POTScale_SideBand(Empty_UpstreamCap);
  init_POTScale_SideBand(Empty_Barrel);
  init_POTScale_SideBand(Empty_DownstreamCap);
  init_POTScale_SideBand(Empty_DownstreamConcaveCap);
}

void Helium_3CryoRegionsSideBandTool::init_POTScale_Empty_RegionX(){
  init_POTScale_SideBand(Empty_XCenter);
  init_POTScale_SideBand(Empty_XLeftShelf);
  init_POTScale_SideBand(Empty_XRightShelf);
  init_POTScale_SideBand(Empty_XoutsideEdges);



}

void Helium_3CryoRegionsSideBandTool::init_POTScale_Empty_RegionXZ(){
  init_POTScale_SideBand(Empty_XCenter);
  init_POTScale_SideBand(Empty_XLeftShelf);
  init_POTScale_SideBand(Empty_XRightShelf);
  init_POTScale_SideBand(Empty_DownstreamConcaveCap);



}


void Helium_3CryoRegionsSideBandTool::init_POTScale_Full_Empty(){

  init_POTScale_SideBand(Full_Empty);
  init_POTScale_SideBand(Full_Empty_UpstreamCap);
  init_POTScale_SideBand(Full_Empty_Barrel);
  init_POTScale_SideBand(Full_Empty_DownstreamCap);
  init_POTScale_SideBand(Full_Empty_DownstreamConcaveCap);
}

void Helium_3CryoRegionsSideBandTool::init_POTScale_FitVarsEmpty(){
  std::cout<<"init_POTScale_FitVarsEmpty"<<std::endl;
  std::cout<<"POT upstreamCap"<<std::endl;
  init_POTScale_FittingVar_onlySideBand(Empty_UpstreamCap);
  std::cout<<"POT barrel"<<std::endl;
  init_POTScale_FittingVar_onlySideBand(Empty_Barrel);
  std::cout<<"POT downstreamCap"<<std::endl;
  init_POTScale_FittingVar_onlySideBand(Empty_DownstreamCap);
  std::cout<<"POT downstream concave Cap"<<std::endl;
  init_POTScale_FittingVar_onlySideBand(Empty_DownstreamConcaveCap);
}

void Helium_3CryoRegionsSideBandTool::init_POTScale_FitVarsEmpty_RegionX(){
  std::cout<<"init_POTScale_FitVarsEmpty"<<std::endl;
  std::cout<<"POT upstreamCap"<<std::endl;
  init_POTScale_FittingVar_onlySideBand(Empty_XCenter);
  std::cout<<"POT barrel"<<std::endl;
  init_POTScale_FittingVar_onlySideBand(Empty_XLeftShelf);
  std::cout<<"POT downstreamCap"<<std::endl;
  init_POTScale_FittingVar_onlySideBand(Empty_XRightShelf);
  std::cout<<"POT downstream concave Cap"<<std::endl;
  init_POTScale_FittingVar_onlySideBand(Empty_XoutsideEdges);
}

void Helium_3CryoRegionsSideBandTool::init_POTScale_FitVarsEmpty_RegionXZ(){
  std::cout<<"init_POTScale_FitVarsEmpty"<<std::endl;
  std::cout<<"POT upstreamCap"<<std::endl;
  init_POTScale_FittingVar_onlySideBand(Empty_XCenter);
  std::cout<<"POT barrel"<<std::endl;
  init_POTScale_FittingVar_onlySideBand(Empty_XLeftShelf);
  std::cout<<"POT downstreamCap"<<std::endl;
  init_POTScale_FittingVar_onlySideBand(Empty_XRightShelf);
  std::cout<<"POT downstream concave Cap"<<std::endl;
  init_POTScale_FittingVar_onlySideBand(Empty_DownstreamConcaveCap);
}

void Helium_3CryoRegionsSideBandTool::init_POTScale_AllHist(){
  std::cout<<"Scalling all Init Hist"<<std::endl;
  init_POTScale_Full();
  init_POTScale_Empty();
  init_POTScale_Full_Empty();
}


void Helium_3CryoRegionsSideBandTool::POTScale_New_Fit_EmptyMCHist(){
  //std::cout<<"Scalling all EMPTY Init Hist"<<std::endl;
  POTScale_SideBand_MC_total(Empty_UpstreamCap);
  POTScale_SideBand_MC_total(Empty_Barrel);
  POTScale_SideBand_MC_total(Empty_DownstreamCap);
  POTScale_SideBand_MC_total(Empty_DownstreamConcaveCap);

  POTScale_SideBand_MC_Material(Empty_UpstreamCap, 0);
  POTScale_SideBand_MC_Material(Empty_Barrel, 0);
  POTScale_SideBand_MC_Material(Empty_DownstreamCap, 0);
  POTScale_SideBand_MC_Material(Empty_DownstreamConcaveCap, 0);




}

void Helium_3CryoRegionsSideBandTool::POTScale_New_Fit_EmptyDataHist(){
  POTScale_SideBand_Data(Empty_UpstreamCap);
  POTScale_SideBand_Data(Empty_Barrel);
  POTScale_SideBand_Data(Empty_DownstreamCap);
  POTScale_SideBand_Data(Empty_DownstreamConcaveCap);
}



void Helium_3CryoRegionsSideBandTool::POTScale_New_Fit_EmptyMCHist_regionX(){
  //std::cout<<"Scalling all EMPTY Init Hist"<<std::endl;
  POTScale_SideBand_MC_total(Empty_XCenter);
  POTScale_SideBand_MC_total(Empty_XLeftShelf);
  POTScale_SideBand_MC_total(Empty_XRightShelf);
  POTScale_SideBand_MC_total(Empty_XoutsideEdges);

  POTScale_SideBand_MC_Material(Empty_XCenter, 0);
  POTScale_SideBand_MC_Material(Empty_XLeftShelf, 0);
  POTScale_SideBand_MC_Material(Empty_XRightShelf, 0);
  POTScale_SideBand_MC_Material(Empty_XoutsideEdges, 0);


}

void Helium_3CryoRegionsSideBandTool::POTScale_New_Fit_EmptyMCHist_regionXZ(){
  //std::cout<<"Scalling all EMPTY Init Hist"<<std::endl;
  POTScale_SideBand_MC_total(Empty_XCenter);
  POTScale_SideBand_MC_total(Empty_XLeftShelf);
  POTScale_SideBand_MC_total(Empty_XRightShelf);
  POTScale_SideBand_MC_total(Empty_DownstreamConcaveCap);

  POTScale_SideBand_MC_Material(Empty_XCenter, 0);
  POTScale_SideBand_MC_Material(Empty_XLeftShelf, 0);
  POTScale_SideBand_MC_Material(Empty_XRightShelf, 0);
  POTScale_SideBand_MC_Material(Empty_DownstreamConcaveCap, 0);


}


void Helium_3CryoRegionsSideBandTool::ColorHists(TH1D* data, TH1D* Helium, TH1D* Aluminium, TH1D* Carbon, TH1D* Iron, TH1D* Lead,  TH1D* Other)
{
    // MC
    Helium->SetFillColor(Helium9_colorScheme.at(1));
    Helium->SetFillStyle(3001);

    Aluminium->SetFillColor(Helium9_colorScheme.at(4));
    Aluminium->SetFillStyle(3001);

    Carbon->SetFillColor(Helium9_colorScheme.at(2));
    Carbon->SetFillStyle(3001);

    Iron->SetFillColor(Helium9_colorScheme.at(0));
    Iron->SetFillStyle(3001);

    Lead->SetFillColor(Helium9_colorScheme.at(3));
    Lead->SetFillStyle(3001);

    Other->SetFillColor(Helium9_colorScheme.at(5));
    Other->SetFillStyle(3001);

    // Data
    data->SetMarkerColor(kBlack);
    data->SetMarkerStyle(20);
    data->SetMarkerSize(1);
    data->SetLineWidth(1);
    data->SetLineColor(kBlack);
    data->SetFillStyle(0);
}

void Helium_3CryoRegionsSideBandTool::ColorHistsForLines(TH1D* data, TH1D* Helium, TH1D* Aluminium, TH1D* Carbon, TH1D* Iron, TH1D* Lead,  TH1D* Other)
{
    // MC
    Helium->SetLineColor(Helium9_colorScheme.at(1));
    Aluminium->SetLineColor(Helium9_colorScheme.at(4));
    Carbon->SetLineColor(Helium9_colorScheme.at(2));
    Iron->SetLineColor(Helium9_colorScheme.at(0));
    Lead->SetLineColor(Helium9_colorScheme.at(3));
    Other->SetLineColor(Helium9_colorScheme.at(5));

    Helium->SetLineWidth(3);
    Aluminium->SetLineWidth(3);
    Carbon->SetLineWidth(3);
    Iron->SetLineWidth(3);
    Lead->SetLineWidth(3);
    Other->SetLineWidth(3);

    Helium->SetFillStyle(0);
    Aluminium->SetFillStyle(0);
    Carbon->SetFillStyle(0);
    Iron->SetFillStyle(0);
    Lead->SetFillStyle(0);
    Other->SetFillStyle(0);

    // Data
    data->SetMarkerColor(kBlack);
    data->SetMarkerStyle(20);
    data->SetMarkerSize(1);
    data->SetLineWidth(1);
    data->SetLineColor(kBlack);
    data->SetFillStyle(0);
}

void Helium_3CryoRegionsSideBandTool::ColorHists(TH1D* Carbon, TH1D* Iron, TH1D* Lead,  TH1D* Other)
{

    Carbon->SetFillColor(Helium9_colorScheme.at(2));
    Carbon->SetFillStyle(3001);

    Iron->SetFillColor(Helium9_colorScheme.at(0));
    Iron->SetFillStyle(3001);

    Lead->SetFillColor(Helium9_colorScheme.at(3));
    Lead->SetFillStyle(3001);

    Other->SetFillColor(Helium9_colorScheme.at(5));
    Other->SetFillStyle(3001);


}
void Helium_3CryoRegionsSideBandTool::ColorHistsForLines(TH1D* Carbon, TH1D* Iron, TH1D* Lead,  TH1D* Other)
{

  Carbon->SetLineColor(Helium9_colorScheme.at(2));
  Iron->SetLineColor(41);
  Lead->SetLineColor(47);
  Other->SetLineColor(Helium9_colorScheme.at(5));

  Carbon->SetLineWidth(3);
  Iron->SetLineWidth(3);
  Lead->SetLineWidth(3);
  Other->SetLineWidth(3);

  Carbon->SetFillStyle(0);
  Iron->SetFillStyle(0);
  Lead->SetFillStyle(0);
  Other->SetFillStyle(0);




}


void Helium_3CryoRegionsSideBandTool::ColorData(TH1D* data){
  data->SetMarkerColor(kBlack);
  data->SetMarkerStyle(20);
  data->SetMarkerSize(1);
  data->SetLineWidth(1);
  data->SetLineColor(kBlack);
  data->SetFillStyle(0);
}

void Helium_3CryoRegionsSideBandTool::Color_HeliumHists(TH1D* Helium_UpsteamCap, TH1D* Helium_Barrel, TH1D* Helium_DownstreamCap, TH1D* Helium_DownstreamConcaveCap)
{
    // MC
    Helium_UpsteamCap->SetFillColor(TColor::GetColor("#be29ec"));
    Helium_UpsteamCap->SetFillStyle(3001);

    Helium_Barrel->SetFillColor(TColor::GetColor("#d24f09"));
    Helium_Barrel->SetFillStyle(3001);

    Helium_DownstreamCap->SetFillColor(TColor::GetColor("#b8be10"));
    Helium_DownstreamCap->SetFillStyle(3001);

    Helium_DownstreamConcaveCap->SetFillColor(TColor::GetColor("#274e13"));
    Helium_DownstreamConcaveCap->SetFillStyle(3001);

}
void Helium_3CryoRegionsSideBandTool::Color_HeliumHistsForLines(TH1D* Helium_UpsteamCap, TH1D* Helium_Barrel, TH1D* Helium_DownstreamCap, TH1D* Helium_DownstreamConcaveCap)
{

    // MC
    Helium_UpsteamCap->SetLineColor(TColor::GetColor("#be29ec"));
  //  Helium_UpsteamCap->SetMarkerStyle(0);
    Helium_UpsteamCap->SetLineWidth(3);
    Helium_Barrel->SetLineColor(TColor::GetColor("#d24f09"));
    //Helium_Barrel->SetMarkerStyle(0);
    Helium_Barrel->SetLineWidth(3);
    Helium_DownstreamCap->SetLineColor(TColor::GetColor("#b8be10"));
    //Helium_DownstreamCap->SetMarkerStyle(0);
    Helium_DownstreamCap->SetLineWidth(3);
    Helium_DownstreamConcaveCap->SetLineColor(TColor::GetColor("#274e13"));
    //Helium_DownstreamConcaveCap->SetMarkerStyle(0);
    Helium_DownstreamConcaveCap->SetLineWidth(3);

    Helium_UpsteamCap->SetFillStyle(0);
    Helium_Barrel->SetFillStyle(0);
    Helium_DownstreamCap->SetFillStyle(0);
    Helium_DownstreamConcaveCap->SetFillStyle(0);



}
void Helium_3CryoRegionsSideBandTool::Color_AluminiumHists(TH1D* Aluminium_UpsteamCap, TH1D* Aluminium_Barrel, TH1D* Aluminium_DownstreamCap, TH1D* Aluminium_DownstreamConcaveCap)
{
    // MC
    Aluminium_UpsteamCap->SetFillColor(TColor::GetColor("#09ae51"));  //Helium9_colorScheme.at(4));
    Aluminium_UpsteamCap->SetFillStyle(3001);

    Aluminium_Barrel->SetFillColor( TColor::GetColor("#098cd2"));///Helium9_colorScheme.at(3));
    Aluminium_Barrel->SetFillStyle(3001);

    Aluminium_DownstreamCap->SetFillColor(Helium9_colorScheme.at(10));
    Aluminium_DownstreamCap->SetFillStyle(3001);

    Aluminium_DownstreamConcaveCap->SetFillColor(Helium9_colorScheme.at(15));
    Aluminium_DownstreamConcaveCap->SetFillStyle(3001);

}
void Helium_3CryoRegionsSideBandTool::Color_AluminiumHistsForLines(TH1D* Aluminium_UpsteamCap, TH1D* Aluminium_Barrel, TH1D* Aluminium_DownstreamCap, TH1D* Aluminium_DownstreamConcaveCap)
{
    // MC

    Aluminium_UpsteamCap->SetLineColor(TColor::GetColor("#09ae51"));
    //Aluminium_UpsteamCap->SetMarkerStyle(0);
    Aluminium_UpsteamCap->SetLineWidth(3);
    Aluminium_Barrel->SetLineColor(TColor::GetColor("#098cd2"));
    //Aluminium_Barrel->SetMarkerStyle(0);
    Aluminium_Barrel->SetLineWidth(3);
    Aluminium_DownstreamCap->SetLineColor(Helium9_colorScheme.at(10));
  //  Aluminium_DownstreamCap->SetMarkerStyle(0);
    Aluminium_DownstreamCap->SetLineWidth(3);
    Aluminium_DownstreamConcaveCap->SetLineColor(Helium9_colorScheme.at(15));
  //  Aluminium_DownstreamConcaveCap->SetMarkerStyle(0);
    Aluminium_DownstreamConcaveCap->SetLineWidth(3);
    Aluminium_UpsteamCap->SetFillStyle(0);
    Aluminium_Barrel->SetFillStyle(0);
    Aluminium_DownstreamCap->SetFillStyle(0);
    Aluminium_DownstreamConcaveCap->SetFillStyle(0);

}


void  Helium_3CryoRegionsSideBandTool::Vector_string_names(std::vector<std::string> &SideBand_name){
  std::string name = "Vertex X";
  SideBand_name.push_back(name);
  name = "Vertex Y";
  SideBand_name.push_back(name);
  name = "Vertex Z";
  SideBand_name.push_back(name);
  name = "Vertex R";
  SideBand_name.push_back(name);
  name = "Distance to Nearest Wall ";
  SideBand_name.push_back(name);
  name = "P_{T,\\mu}";
  SideBand_name.push_back(name);
  name = "P_{Z,\\mu}";
  SideBand_name.push_back(name);
  name = "E_{\\mu}";
  SideBand_name.push_back(name);
  name = "\\theta_{\\mu}";
  SideBand_name.push_back(name);
  name = "DOCA_{\\mu}";
  SideBand_name.push_back(name);
  name = "DOCA_{recoil}";
  SideBand_name.push_back(name);
  name = "TrkLength_{recoil}";
  SideBand_name.push_back(name);
  name = "Distance USCap";
  SideBand_name.push_back(name);
  name = "Distance USCap[RCut]";
  SideBand_name.push_back(name);
  name = "Distance DSCap";
  SideBand_name.push_back(name);
  name = "Distance DSCap[RCut]";
  SideBand_name.push_back(name);
  name = "Vertex Z[RCut]";
  SideBand_name.push_back(name);
  name = "Vertex X[RCut]";
  SideBand_name.push_back(name);
  name = "Vertex Y[RCut]";
  SideBand_name.push_back(name);
  name = "Vertex R[RCut]";
  SideBand_name.push_back(name);

  std::cout<<"Finished making Var Names vector "<<std::endl;
};


void  Helium_3CryoRegionsSideBandTool::Vector_string_Fittingnames(std::vector<std::string> &SideBand_name){
  std::string name = "Vertex X";
  SideBand_name.push_back(name);
   name = "Vertex Y";
  SideBand_name.push_back(name);
   name = "Vertex Z";
  SideBand_name.push_back(name);
   name = "Vertex R";
  SideBand_name.push_back(name);
  std::cout<<"Finished making Var Names vector "<<std::endl;
};

void Helium_3CryoRegionsSideBandTool::SaveVector_toFile(std::vector<double>input, std::string name){
 std::ofstream outFile(name);
    for (const auto &e : input) outFile << e << "\n";
    outFile.close();
}



std::vector <double> Helium_3CryoRegionsSideBandTool::ReadFile_vector(std::string filename)
{std::cout<<"inside::ReadFile_vector"<<std::endl;
  std::vector<double> v1;
  std::string line;
  std::string Name;
  std::ifstream myFile(filename);
   while(getline(myFile, line))
   {
     std::istringstream lineStream(line);
     double first;
     lineStream >> first;
     std::cout<<first<<std::endl;
     v1.push_back(first);
   }


   return v1;

}


void Helium_3CryoRegionsSideBandTool::Fill_vectors_file(std::vector<double> &Full_vector
   , std::vector<double> &Empty_vector, std::vector<double> &Full_Empty_vector, std::string FileName ){

std::string Final_Name;
  Final_Name = FileName + "Empty.txt";
  Empty_vector = ReadFile_vector(Final_Name);
  Final_Name = FileName + "Full.txt";
  Full_vector= ReadFile_vector(Final_Name);
  Final_Name = FileName + "Full_Empty.txt";
  Full_Empty_vector = ReadFile_vector(Final_Name);






}
///==============================================================================
void Helium_3CryoRegionsSideBandTool::FillHistName_Map_NRegions(HeliumNSideBand& sb, std::vector<std::string> histNames , std::vector<Fit_Parms_Names> FitParms ){
//std::cout<<"Filling Map"<<std::endl;
  if(histNames.size() != FitParms.size()){std::cout<<"Error input for FillHistName_Map: vectors size is different , Opps !! "<<std::endl;assert(false);}

  for(int i = 0; i < histNames.size(); i++){
    //std::cout<<"FIlline Hist Name: "<< histNames.at(i)<<std::endl;
    sb.HistName_Map.insert ( std::pair<Fit_Parms_Names,std::string>(FitParms.at(i),histNames.at(i)));
  }
}
///==============================================================================

void Helium_3CryoRegionsSideBandTool::FillXsec_VarNbandName(XSec_VarNband &xsec, std::string InputName, std::string XAxis){
  xsec.name = InputName;
  xsec.Xaxis_Title = XAxis;
}
void Helium_3CryoRegionsSideBandTool::FillXsec_VarNbandName_Data(XSec_VarNband &xsec, std::string InputName){
  xsec.name_data = InputName;
}

///==============================================================================
void Helium_3CryoRegionsSideBandTool::ConstructVertex_FitMC_shifted_HistName_Map(HeliumNSideBand& sb, std::string CyroRegion){
  //std::cout<<"Filling Map"<<std::endl;
  std::string Var;

  Var = "h_Region14_Vertex_X_Material_Region_" + CyroRegion;
  sb.HistName_Map.insert ( std::pair<Fit_Parms_Names,std::string>( kh_Name_MC_fitTo_vertexX, Var));

  Var = "h_Region14_Vertex_Y_Material_Region_" + CyroRegion;
  sb.HistName_Map.insert ( std::pair<Fit_Parms_Names,std::string>( kh_Name_MC_fitTo_vertexY, Var));

  Var = "h_Region14_Vertex_Z_Material_Region_" + CyroRegion;
  sb.HistName_Map.insert ( std::pair<Fit_Parms_Names,std::string>( kh_Name_MC_fitTo_vertexZ, Var));

  Var = "h_Region14_Vertex_R_Material_Region_" + CyroRegion;
  sb.HistName_Map.insert ( std::pair<Fit_Parms_Names,std::string>( kh_Name_MC_fitTo_vertexR, Var));

  Var = "h_Region14_TRUE_Vertex_X_Material_Region_" + CyroRegion;
  sb.HistName_Map.insert ( std::pair<Fit_Parms_Names,std::string>( kh_Name_MC_fitTo_TRUE_vertexX, Var));

  Var = "h_Region14_TRUE_Vertex_Y_Material_Region_" + CyroRegion;
  sb.HistName_Map.insert ( std::pair<Fit_Parms_Names,std::string>( kh_Name_MC_fitTo_TRUE_vertexY, Var));

  Var = "h_Region14_TRUE_Vertex_Z_Material_Region_" + CyroRegion;
  sb.HistName_Map.insert ( std::pair<Fit_Parms_Names,std::string>( kh_Name_MC_fitTo_TRUE_vertexZ, Var));

  Var = "h_Region14_TRUE_Vertex_R_Material_Region_" + CyroRegion;
  sb.HistName_Map.insert ( std::pair<Fit_Parms_Names,std::string>( kh_Name_MC_fitTo_TRUE_vertexR, Var));

  Var = "h_Region14_Muon_PT_Material_Region_" + CyroRegion;
  FillXsec_VarNbandName(sb.muon_PT, Var,"P_{T} [GeV]");

  Var = "h_Region14_Muon_PZ_Material_Region_" + CyroRegion;
  FillXsec_VarNbandName(sb.muon_PZ, Var,"P_{Z} [GeV]");

  Var = "h_Region14_MuonTheta_Material_Region_" + CyroRegion;
  FillXsec_VarNbandName(sb.muon_theta, Var,"#theta_{#mu} [GeV]");

  Var = "h_Region14_Muon_E_Material_Region_" + CyroRegion;
  FillXsec_VarNbandName(sb.muon_E, Var,"E_{#mu}");

  Var = "h_Region14_Muon_DOCA_Material_Region_" + CyroRegion;
  FillXsec_VarNbandName(sb.muon_doca, Var,"Muon DOCA [mm]");

  Var = "h_Region14_NearestWall_Material_Region_" + CyroRegion;
  FillXsec_VarNbandName(sb.DistancetoEdge, Var,"Nearest Wall [mm]");

  Var = "h_Region14_secTrk_DOCA_Material_Region_" + CyroRegion;
  FillXsec_VarNbandName(sb.SecTrk_doca, Var,"Leading Recoil DOCA");

  Var = "h_Region14_secTrk_Tracklength_Material_Region_" + CyroRegion;
  FillXsec_VarNbandName(sb.TrackLength, Var,"TrackLength [cm]");

}
void Helium_3CryoRegionsSideBandTool::ConstructVertex_FitDATA_shifted_HistName_Map(HeliumNSideBand& sb, std::string CyroRegion){
  //std::cout<<"Filling Map"<<std::endl;
  std::string Var;

  Var = "h_Data_CryoVertex_X_CryoRegion14_Region_" + CyroRegion;
  sb.HistName_Map.insert ( std::pair<Fit_Parms_Names,std::string>( kh_Name_Data_fitTo_vertexX, Var));

  Var = "h_Data_CryoVertex_Y_CryoRegion14_Region_" + CyroRegion;
  sb.HistName_Map.insert ( std::pair<Fit_Parms_Names,std::string>( kh_Name_Data_fitTo_vertexY, Var));

  Var = "h_Data_CryoVertex_Z_CryoRegion14_Region_" + CyroRegion;
  sb.HistName_Map.insert ( std::pair<Fit_Parms_Names,std::string>( kh_Name_Data_fitTo_vertexZ, Var));

  Var = "h_Data_CryoVertex_R_CryoRegion14_Region_" + CyroRegion;
  sb.HistName_Map.insert ( std::pair<Fit_Parms_Names,std::string>( kh_Name_Data_fitTo_vertexR, Var));

  Var = "h_Data_MuonPT_CryoRegion14_Region_" + CyroRegion;
  FillXsec_VarNbandName_Data(sb.muon_PT, Var);

  Var = "h_Data_MuonPZ_CryoRegion14_Region_" + CyroRegion;
  FillXsec_VarNbandName_Data(sb.muon_PZ, Var);

  Var = "h_Data_MuonTheta_CryoRegion14_Region_" + CyroRegion;
  FillXsec_VarNbandName_Data(sb.muon_theta, Var);

  Var = "h_Data_MuonE_CryoRegion14_Region_" + CyroRegion;
  FillXsec_VarNbandName_Data(sb.muon_E, Var);

  Var = "h_Data_MuonDOCA_CryoRegion14_Region_" + CyroRegion;
  FillXsec_VarNbandName_Data(sb.muon_doca, Var);

  Var = "h_Data_Distance_to_InnerTank_CryoRegion14_Region_" + CyroRegion;
  FillXsec_VarNbandName_Data(sb.DistancetoEdge, Var);

  Var = "h_Data_secTrk_DOCA_CryoRegion14_Region_" + CyroRegion;
  FillXsec_VarNbandName_Data(sb.SecTrk_doca, Var);

  Var = "h_Data_secTrk_Length_CryoRegion14_Region_" + CyroRegion;
  FillXsec_VarNbandName_Data(sb.TrackLength, Var);

}


///==============================================================================
void Helium_3CryoRegionsSideBandTool::ConstructVertex_FitMC_shifted_HistName_Map(CryoRegion_HeliumNSideBand_Map& sb,
  std::vector<CryoTank_REGIONS> CryoRegion14_vector)
  {
    for(auto region : CryoRegion14_vector){
      HeliumNSideBand SideBand;
      std::string RegionNum = GetRegionString(region);
      ConstructVertex_FitMC_shifted_HistName_Map(SideBand, RegionNum);
      ConstructVertex_FitDATA_shifted_HistName_Map(SideBand, RegionNum);
      sb.insert(std::pair<CryoTank_REGIONS, HeliumNSideBand>(region,SideBand));
    }
  }
//==============================================================================
void Helium_3CryoRegionsSideBandTool::initNRegionsNames_Empty(){
   ConstructVertex_FitMC_shifted_HistName_Map(CryoRegionMap_Empty,
  CryoRegion14_vector);
}
///==============================================================================
void Helium_3CryoRegionsSideBandTool::PrintNRegionsNames_Empty(){

for(auto HeliumNSideBand_Map_iterator = CryoRegionMap_Empty.begin();HeliumNSideBand_Map_iterator != CryoRegionMap_Empty.end();HeliumNSideBand_Map_iterator++ )
{
std::cout<<"Looking at Region: "<< HeliumNSideBand_Map_iterator->first << std::endl;
std::cout<< "///=============================================================================="<<std::endl;
//auto message1=  HeliumNSideBand_Macp_iterator->second.HistName_Map[kh_Name_MC_fitTo_vertexY];
//std::cout<< "kh_Name_MC_fitTo_vertexY = "<< message1<< std::endl;

std::cout<< "kh_Name_MC_fitTo_vertexY = "<< HeliumNSideBand_Map_iterator->second.HistName_Map[kh_Name_MC_fitTo_vertexY]<< std::endl;
std::cout<< "kh_Name_MC_fitTo_vertexX = "<< HeliumNSideBand_Map_iterator->second.HistName_Map[kh_Name_MC_fitTo_vertexX]<< std::endl;
std::cout<< "kh_Name_MC_fitTo_vertexZ = "<< HeliumNSideBand_Map_iterator->second.HistName_Map[kh_Name_MC_fitTo_vertexZ]<< std::endl;
std::cout<< "kh_Name_MC_fitTo_vertexR = "<< HeliumNSideBand_Map_iterator->second.HistName_Map[kh_Name_MC_fitTo_vertexR]<< std::endl;


std::cout<< "kh_Name_DATA_fitTo_vertexY = "<< HeliumNSideBand_Map_iterator->second.HistName_Map[kh_Name_Data_fitTo_vertexY]<< std::endl;
std::cout<< "kh_Name_DATA_fitTo_vertexX = "<< HeliumNSideBand_Map_iterator->second.HistName_Map[kh_Name_Data_fitTo_vertexX]<< std::endl;
std::cout<< "kh_Name_DATA_fitTo_vertexZ = "<< HeliumNSideBand_Map_iterator->second.HistName_Map[kh_Name_Data_fitTo_vertexZ]<< std::endl;
std::cout<< "kh_Name_DATA_fitTo_vertexR = "<< HeliumNSideBand_Map_iterator->second.HistName_Map[kh_Name_Data_fitTo_vertexR]<< std::endl;

std::cout<< "///=============================================================================="<<std::endl;
}
std::cout<< "///=============================================================================="<<std::endl;
std::cout<< "///======= FINSHED PrintNRegionsNames_Empty================="<<std::endl;
std::cout<< "///=============================================================================="<<std::endl;




}
///==============================================================================
