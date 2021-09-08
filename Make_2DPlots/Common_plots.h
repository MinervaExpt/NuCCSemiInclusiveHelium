#ifndef COMMON_PLOTS_H
#define COMMON_PLOTS_H


#include "PlotUtils/MnvH1D.h"
#include "PlotUtils/HistWrapper.h"
#include "PlotUtils/Hist2DWrapper.h"
#include "TObjArray.h"
#include "TArrayD.h"
#include "TMath.h"
#include <algorithm> // erase, remove_if
#include "PlotUtils/MnvNormalization.h"
#include "PlotUtils/ChainWrapper.h"
#include "PlotUtils/makeChainWrapper.h"

#include "../includes/HeliumPlotUtils.h"
#include "../includes/CryoTankUtils.h"
#include "../includes/HeliumDefaults.h"
#include "../includes/HeliumUtils.h"
#include "../includes/Helium2DUtils.h"
#include "../includes/POTCounter.h"

//==============================================================================
// Typedefs and enum
//==============================================================================
class HeliumCVUniverse;
using namespace PlotUtils;
//==============================================================================
// Color schemes
//==============================================================================
namespace HELIUM_Plotting {
  //const int N_COLORS=10;
  //const int colors[N_COLORS] = {kRed+1, kOrange+8, kGray+1, kOrange-7, kGreen+2, kYellow+2, kCyan-3, kBlue-7, kMagenta-6, kMagenta+2};

  //const int colors[N_COLORS] = {kRed+3, kOrange+9, kGray+2, kOrange+3, kGreen+3, kYellow+3, kCyan-2, kBlue-7, kMagenta-6, kMagenta+2};
  //const int fill_colors[N_COLORS] = {kRed+1, kOrange+6, kGray+1, kOrange-5, kGreen-2, kYellow+2, kCyan-8, kBlue-9, kMagenta-9, kMagenta-2};

  const int N_COLORS = 8;
  const int colors[N_COLORS] = {kRed+3, kOrange+9, kGray+2,kBlue , kCyan-2,kGreen+3 , kMagenta-6, kMagenta+2 };
  const int fill_colors[N_COLORS] = {kRed+1, kOrange+6, kGray+1,kBlue-6 , kCyan-8, kGreen-2, kMagenta-9, kMagenta-2};

   const int nColors2 = 12;
   const int colors2[nColors2]={
                       kMagenta+1,
                       kOrange+2,
                       kTeal-7,
                       kRed-6,
                       kSpring-1,
                       kBlue,
                       kAzure+7,
                       kCyan+2,
                       kViolet-4,
                       kGreen+3,
                       kYellow+2,
                       kGray+2,
   };
   const int fill_colors2[nColors2]={
                       kMagenta-1,
                       kOrange,
                       kTeal-9,
                       kRed-8,
                       kSpring-3,
                       kBlue-2,
                       kAzure+5,
                       kCyan,
                       kViolet-6,
                       kGreen+1,
                       kYellow,
                       kGray,
   };

   const int nColors3 = 7;
   const int colors3[nColors3]={
                       kGreen+3,
                       kYellow+2,
                       kOrange+6,
                       kBlue,
                       kCyan+2,
                       kRed+3,
                       kAzure+7
   };
   const int fill_colors3[nColors3]={
                       kGreen+1,
                       kYellow,
                       kOrange+5,
                       kAzure-2,
                       kCyan,
                       kRed+1,
                       kAzure+5
   };

   const int nColors4 = 6;
   const int colors4[nColors4]={
                       kRed+3,
                       kBlue-6,
                       kMagenta-6,
                       kOrange+6,
                       kGreen-2,
                       kAzure+8
   };
   const int fill_colors4[nColors4]={
                       kRed+1,
                       kBlue-2,
                       kMagenta-3,
                       kOrange+5,
                       kGreen-6,
                       kAzure+7
   };

   const int nColors5 = 7;
   const int colors5[nColors5]={
                       kGreen+3,
                       kGray+2,
                       kBlue,
                       kYellow+2,
                       kCyan+2,
                       kRed+3,
                       kAzure+7
   };
   const int fill_colors5[nColors5]={
                       kGreen+1,
                       kGray,
                       kBlue-2,
                       kYellow,
                       kCyan,
                       kRed+1,
                       kAzure+5
   };

  const int coherent_fill_color = kRed-7;
  const int coherent_color = kRed-3;
}




//==============================================================================
// Constants from CryoTank
//==============================================================================
class PlayList_INFO{
  std::string m_Root_Pathway;
  std::string m_playlist_title;
  std::string m_Helium_status_title;
  bool m_isPOT_set =false;
  ME_helium_Playlists m_playlist;
  ME_helium_Status m_Helium_status;
  double m_POT;
  bool m_ismc;
  bool m_IsTRUTH;
  bool m_IsStatsOnly;

public:
  TFile *TFILE_PLAYLIST;
  //  TFile *TFILE_PLAYLIST;
  PlayList_INFO(ME_helium_Playlists playlist, bool is_mc, bool Stats_only ){
    m_IsTRUTH=false;
    m_ismc = is_mc;
    m_IsStatsOnly=Stats_only;
    m_playlist = playlist;
    m_Helium_status = GetPlaylist_HeliumStatus(playlist);
    m_playlist_title = GetPlaylist_Name(playlist);
    m_Helium_status_title  =GetFULLorEmpty( m_Helium_status);
    m_Root_Pathway = String_EventSectionROOTPath( is_mc, playlist, m_IsStatsOnly);

    TFILE_PLAYLIST = new TFile(m_Root_Pathway.c_str());
    Set_Pot();
}


PlayList_INFO(ME_helium_Playlists playlist, bool StatsOnly){
  m_ismc = true;
  m_IsTRUTH = true;
  m_playlist = playlist;
  m_IsStatsOnly = StatsOnly;

  m_Helium_status = GetPlaylist_HeliumStatus(playlist);
  m_playlist_title = GetPlaylist_Name(playlist);
  m_Helium_status_title  =GetFULLorEmpty( m_Helium_status);
  m_Root_Pathway = String_EventSectionROOTPath_FORTRUTH(playlist, StatsOnly );

  TFILE_PLAYLIST = new TFile(m_Root_Pathway.c_str());
  Set_Pot();

}




//void SetPOT(double POT){m_POT = POT;isPOT_set =true;}
void PrintPlaylistName(){ std::cout<<m_playlist_title<<std::endl; }
std::string GetPlaylistName(){return m_playlist_title; }
std::string  GETROOT_Path(){ return m_Root_Pathway;  }
void PRINTROOT_Path(){ std::cout<<"Root Pathway = "<< m_Root_Pathway<< std::endl;  }
bool ISThisPlaylistMC(){return m_ismc;}

double Get_Pot(){
if(m_isPOT_set==false){/*std::cout<<"ERROR POT not set"<<std::endl;*/ return -9999; }
else if (m_isPOT_set==true){return m_POT; }
else{std::cout<<"FAILED"<<std::endl; return -9999;}
}

//TFile GetTFile(){return TFILE_PLAYLIST; }



void PRINT_Pot(){
  if(m_isPOT_set==false){std::cout<<"ERROR POT not set"<<std::endl; }
  else if (m_isPOT_set==true){
    std::cout<<"Playlist:"<< m_playlist_title << "  POT = "<< m_POT<<std::endl;
  }
}



void Set_Pot( ){
  if(m_isPOT_set==true){std::cout<<"ERROR:POT alreay SET for this Construtor!!-> "<<std::endl; return;}

  std::string pathway = this->GETROOT_Path();
  double Pot;

  if(m_ismc==true){  ChainWrapper* mcchainPOT = makeChainWrapperPtr(pathway.c_str(), "Meta");
                     Pot = GetPOT(mcchainPOT,"MC");
                   }
  else if(m_ismc==false){ ChainWrapper* datachainPOT = makeChainWrapperPtr(pathway.c_str(), "Meta");
                         Pot = GetPOT(datachainPOT);
                       }
      m_isPOT_set=true;
      m_POT = Pot;

    }//end of get POT

ME_helium_Status GetHeliumStatus(){return m_Helium_status;}
ME_helium_Playlists GetPlaylist(){return m_playlist;}


};//end of class




bool CheckPlaylistHeliumStatus(std::vector<PlayList_INFO> playlist , bool ISFull  ){

std::vector<ME_helium_Status> Status;

ME_helium_Status Test;
bool Status_return;


if(ISFull==true){Status.push_back(kFULL);}
else if (ISFull==false){Status.push_back(kEMPTY);}

for(auto Playlist_vector : playlist){
Test = Playlist_vector.GetHeliumStatus();

if(Test==Status[0]){Status_return = true;}
else{std::cout<<"Oops This Playlist isn't Mark in correct Helium Status Playlist"<<std::endl;
  return false;}
}//end of for loop


return Status_return;



}//endoffunctio






#endif // common_stuff_h
