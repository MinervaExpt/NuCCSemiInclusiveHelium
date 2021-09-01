// ========================================================================
// Base class for an un-systematically shifted (i.e. CV) universe.  Implement
// your own base class with the functions you need. I've implemented GetEnu(),
// GetMuonE() and GetHadronE() as examples: you'll have other variables you
// want.
//
// To add a systematic, inherit from this class and override whichever
// functions you need to. For a "vertical" error, this will mean overriding the
// GetWeight() function to modify the event weight. For a "lateral" error, this
// will mean overriding the function that calculates the quantity that is being
// shifted (muon energy, or hadronic energy or whatever).
//
// For examples of each of those two cases, see ./LateralSystematics.h and
// PlotUtils/GenieSystematics.h. For an example of how to put the whole thing
// together and actually *use* the classes, see the runUniverseShift.C macro in
// this directory. `root -l runUniverseShift.C+`
// ========================================================================
#ifndef EVENT2DCOUNTING__H
#define EVENT2DCOUNTING__H
#include "../includes/CVUniverse.h"
#include <vector>
//#include "PlotUtils/ChainWrapper.h"
#include <iostream>
#include "TMath.h"
#include "../includes/Cuts.h"
#include "../includes/common_functions.h"
#include "../includes/common_2Dfunctions.h"
#include "../includes/common_stuff.h"
#include "PlotUtils/MnvVertErrorBand.h"
#include "PlotUtils/MnvPlotter.h"
#include "PlotUtils/HistogramUtils.h"
#include "PlotUtils/MnvH1D.h"
#include <iostream>
#include "../Make_Arachne/Make_Arachne_links.h"

///declear functions

void EventCounter_TRUTH(const CVUniverse& universe, std::vector<ECutsTRUTH> TrueCuts, EventCount_Truth &Event_map ,HeliumPlayListInfo Info);
void EventCounter_TRUTH(const CVUniverse& universe, std::vector<ECutsTRUTH> TrueCuts, EventCount_Truth &Event_map ,double Weight);
void EventCounter(const CVUniverse& universe, std::vector<ECuts> cuts, EventCount_RECO &Event_map ,bool is_mc, HeliumPlayListInfo Info );
void EventCounter_RECO_TRUTHApplied(const CVUniverse& universe, std::vector<ECutsTRUTH>
  TrueCuts,std::vector<ECuts> cuts, EventCount_RECO &TRUE_Event_map, EventCount_RECO &RECOEvent_map ,
  bool is_mc,HeliumPlayListInfo Info);
  //void MakeRECO_CVS_EventCuts(EventPlaylist_RecoCount cutmap, std::vector<ME_helium_Status> playlist,
    //std::vector<ECuts> Cuts, const char* title,double potscaler,bool F_E);
  //void MakeRECOF_E_CVS_EventCuts(EventCount_RECO cutmap, std::vector<ME_helium_Status> playlist,
  //  std::vector<ECuts> Cuts, const char* title,double potscaler);

  //void MakeRECO_CVS_EventCuts_F_E( EventPlaylist_RecoCount RECOCutMap ,
    //std::vector<ECuts> Cuts, const char* title, double POT_scaler[]);

void PrintCutstoScreen( std::vector<ECuts> kCutsVector , EventCount_RECO Cutnumbers, const char* datatype, double POT_scaler );

//void PrintCutstoScreenF_E( std::vector<ECuts> kCutsVector, std::vector< ME_helium_Status> kPlayListVector , EventPlaylist_RecoCount CountMap, double POT_scaler[] );

void MakeEfficiencyCutCVS(EventCount_RECO &TRUE_Event_map, EventCount_RECO &RECOEvent_map, std::vector<ECuts> kCutsVector,const char* title);


void EventCounter_TRUTH(const CVUniverse& universe, std::vector<ECutsTRUTH> TrueCuts, EventCount_Truth &Event_map, std::vector<Weights> kweight_vector )
{

  double weight;
  weight =  universe.GetWeight(kweight_vector);
  bool pass = true;

  for (auto c : TrueCuts){
    pass = pass && PassesTRUTH(universe, c);
if(pass==true){
    Event_map[c]+=weight;
  }
else{continue;}

}//end of loop

return;


}//end of function


void EventCounter(const CVUniverse& universe, std::vector<ECuts> cuts, EventCount_RECO &Event_map ,bool is_mc, HeliumPlayListInfo Info )
{

  double weight=1.0;
  weight = is_mc ? universe.GetWeight(Info) : 1.0 /*universe.GetVetoAccpetedWeigh()*/;

  bool pass = true;

  for (auto c : cuts){
    pass = pass && PassesCut(universe, c, is_mc);
if(pass==true){
    Event_map[c]+=weight;
  }
else{continue;}

}//end of loop

return;


}//end of function


void EventCounter_RECO_TRUTHApplied(const CVUniverse& universe, std::vector<ECutsTRUTH>TrueCuts,
  std::vector<ECuts> cuts, EventCount_RECO &TRUE_Event_map, EventCount_RECO &RECOEvent_map ,
  bool is_mc,HeliumPlayListInfo Info){

  double weight;
  weight = is_mc ? universe.GetWeight(Info) : 1.0;
  bool pass = true;

  for(auto c : cuts){

    bool TRUEPASS = PassesCutsTRUTH(universe,  TrueCuts);

    if(TRUEPASS==true){
      TRUE_Event_map[c]+=weight;
    }
    else{continue;}

    pass = pass && PassesCut(universe, c, is_mc) && TRUEPASS;

    if(pass==true){
  RECOEvent_map[c]+=weight;
  }
  else{continue;}

}//end of loop

return;


}//end of function


std::string makeTableString(int number, std::string letter){
  string FinalString = letter + "|";
  for(int i = 0; i < number-1; i++){
    FinalString = FinalString + letter + "|" ;
  }
  return FinalString;
}

/*
void MakeRECO_CVS_EventCuts(EventPlaylist_RecoCount RECOCutMap, std::vector<ME_helium_Status> playlist,
  std::vector<ECuts> kCutsVector, const char* title, double potscaler[], bool F_E){
    ofstream myfile;
    char Title[1024];
    double pot= -999;



    for(auto List: playlist){


      switch (List) {
        case kData_FULL:  sprintf(Title, "%s_dataFull.cvs", title );
        break;

        case kData_EMPTY: sprintf(Title, "%s_dataEmpty.cvs", title );
        break;

        case kMC_FULL:    sprintf(Title, "%s_MCFull.cvs", title );
        break;

        case kMC_EMPTY:    sprintf(Title, "%s_MCEmpty.cvs", title );
        break;

        default: std::cout<<"FAILURE -> suck it"<<std::endl;
        break;
      }

      switch (List) {

        case kData_FULL: pot= potscaler[kData_FULL]/ potscaler[kMC_FULL]; break;

        case kData_EMPTY:  pot= potscaler[kData_FULL]/potscaler[kData_EMPTY]; break;

        case kMC_FULL:  pot= potscaler[kData_FULL]/potscaler[kMC_FULL]; break;

        case kMC_EMPTY:  pot= potscaler[kData_FULL]/potscaler[kMC_EMPTY]; break;

        default: pot=-999;break;
      }




      std::cout<<"title = " <<  Title<<std::endl;

      myfile.open(Title);
      myfile<< "Cut Name, NEvents, $/Delta$NEvents, POTscaler   \n";
      double countmc = 0.0;
      if(pot ==-999){std::cout<<"FAILLL"<<std::endl;}
      for (auto cut : kCutsVector){
        myfile<< GetCutName(cut) << "," <<RECOCutMap[List][cut]<<  "," << countmc -RECOCutMap[List][cut]* pot  <<","<<  pot<< "\n";
        countmc=RECOCutMap[List][cut]*pot;
      }
      myfile.close();

    }




if(F_E==true){
  MakeRECO_CVS_EventCuts_F_E(  RECOCutMap ,
    kCutsVector,  title, potscaler);
    }// end of if


  }//ENd of fucntion
*/
/*void MakeRECO_CVS_EventCuts_F_E( EventPlaylist_RecoCount RECOCutMap ,
  std::vector<ECuts> kCutsVector, const char* title, double POT_scaler[]){
    char Title[1024];
    sprintf(Title, "%s_MCF_E.cvs", title );
    ofstream myfile;
    myfile.open(Title);


myfile<< "Cut Name,  NEventMC(F-E), $/Delta$NEventMC(F-E), NEventdata(F-E),$/Delta$NEventMC(F-E) , POTscaler   \n";
double mcscale=POT_scaler[2]/POT_scaler[0];
double mcscaleEmpty = POT_scaler[0]/POT_scaler[1];
double mcscaleEmptydata = POT_scaler[2]/POT_scaler[3];


//double countmc = 0.0;
double countmcscaled =0.0;
double countdata =0.0;

for (auto cut : kCutsVector){
  myfile<< GetCutName(cut) << "," <<mcscale*( RECOCutMap[kMC_FULL][cut]- mcscaleEmpty*RECOCutMap[kMC_EMPTY][cut])<<"," <<
  countmcscaled - mcscale*( RECOCutMap[kMC_FULL][cut]- mcscaleEmpty*RECOCutMap[kMC_EMPTY][cut])  <<","<<
  RECOCutMap[kData_FULL][cut]-RECOCutMap[kData_EMPTY][cut]*mcscaleEmptydata<<"," <<
  countdata - (RECOCutMap[kData_FULL][cut]-RECOCutMap[kData_EMPTY][cut]*mcscaleEmptydata)<< "\n";



//countmc=potscaler[kMC_FULL]*( RECOCutMap[kMC_FULL][cut]- potscaler[kMC_EMPTY]*RECOCutMap[kMC_EMPTY][cut]);
countmcscaled=mcscale*(RECOCutMap[kMC_FULL][cut]-RECOCutMap[kMC_EMPTY][cut]*mcscaleEmpty);
countdata = RECOCutMap[kData_FULL][cut]-RECOCutMap[kData_EMPTY][cut]*mcscaleEmptydata;
}

myfile.close();

}*/

void PrintCutstoScreen( std::vector<ECuts> kCutsVector , EventCount_RECO Cutnumbers, const char* datatype, double POT_scaler ){
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<datatype<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  double countdata=0.0;

  auto start = Cutnumbers[kCutsVector[0]];
  for (auto cut : kCutsVector){

    printf("%15s:  NEventFULL:   %.2f ,   LOSS: %.2f , PrecentLoss: %.2f, OverallPrecentLoss: %.3f  , POT scaler: %.2f \n" , GetCutName(cut).c_str(),Cutnumbers[cut]*POT_scaler, countdata - Cutnumbers[cut]*POT_scaler, 100*(countdata - Cutnumbers[cut]*POT_scaler) / countdata,100*(countdata - Cutnumbers[cut]*POT_scaler) / start     ,POT_scaler);
    countdata=Cutnumbers[cut]*POT_scaler;
  }
}


void Make_cvsOfCutsRate( std::vector<ECuts> kCutsVector , EventCount_RECO Cutnumbers, const char* File_title , bool is_mc ,double POT_scaler,double POT_count){
    std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
    std::cout<<"Printing CutRate for:" <<File_title<<std::endl;
    std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
    double countdata,countdata_scale;
    char ismC[1024];


    if(is_mc==true){sprintf(ismC, "RECO" );}
    else if(is_mc==false){sprintf(ismC, "DATA" );}


    char Title[1024];
    sprintf(Title, "EventRateCuts_%s_%s.cvs", ismC, File_title );
    std::ofstream myfile;
    myfile.open(Title);
    myfile<<"#Playlist"<< File_title << "\n";
    myfile<<"CutName, CutNum ,NEvent,NEvent(POT),LOSS ,LOSS(POT), PrecentLoss,OverallPrecentLoss, POT scaler,POT_PLAYLIST" << "\n";

    auto start = Cutnumbers[kCutsVector[0]];
    countdata=start;
    countdata_scale=start*POT_scaler;
    for (auto cut : kCutsVector){
     myfile<< GetCutName(cut)<<","<< cut <<","<<
     Cutnumbers[cut] << "," <<
     Cutnumbers[cut]*POT_scaler << "," <<
     countdata - Cutnumbers[cut] << "," <<
     countdata_scale - Cutnumbers[cut]*POT_scaler << "," <<
     100*(countdata - Cutnumbers[cut]) / countdata<<","<<
     100*(countdata - Cutnumbers[cut]) / start    << "," <<
    POT_scaler <<","<<POT_count<<"\n";

    countdata=Cutnumbers[cut];
    countdata_scale=Cutnumbers[cut]*POT_scaler;

    }

}//end of function

/*void PrintCutstoScreenF_E( std::vector<ECuts> kCutsVector, std::vector< ME_helium_Status> kPlayListVector , EventPlaylist_RecoCount CountMap, double POT_scaler[] ){
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"F - E MC" <<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

  double mcscale=POT_scaler[2]/POT_scaler[0];
  double mcscaleEmpty = POT_scaler[0]/POT_scaler[1];
  double mcscaleEmptydata = POT_scaler[2]/POT_scaler[3];
   double countdata=0.0;
   //double countmcscaled =0.0;
   double countmc = 0.0;

  for (auto cut : kCutsVector){

  printf("%15s:          NEventMC(F-E):   %.2f       Loss:   %.2f     |     NEventdata(F-E):   %.2f,        , Loss %.2f\n" , GetCutName(cut).c_str(), mcscale*( CountMap[kPlayListVector[0]][cut]- mcscaleEmpty*CountMap[kPlayListVector[1]][cut]),   countmc - mcscale*( CountMap[kPlayListVector[0]][cut]- mcscaleEmpty*CountMap[kPlayListVector[1]][cut]) , CountMap[kPlayListVector[2]][cut]-CountMap[kPlayListVector[3]][cut]*mcscaleEmptydata, countdata - (CountMap[kPlayListVector[2]][cut]-CountMap[kPlayListVector[3]][cut]*mcscaleEmptydata) );
  countmc=mcscale*( CountMap[kPlayListVector[0]][cut]- mcscaleEmpty*CountMap[kPlayListVector[1]][cut]);
  //countmcscaled=mcscale*(CountMap[kPlayListVector[2]][cut]-CountMap[kPlayListVector[3]][cut]*mcscaleEmpty);
  countdata = CountMap[kPlayListVector[2]][cut]-CountMap[kPlayListVector[3]][cut]*mcscaleEmptydata;
  }

  std::cout << "MC(F-E ) = "<<mcscale*(CountMap[kPlayListVector[0]][kCutsVector[16]]-CountMap[kPlayListVector[1]][kCutsVector[16]]*mcscaleEmpty) <<std::endl;
  std::cout << "Data(F-E ) = "<<CountMap[kPlayListVector[2]][kCutsVector[16]]-CountMap[kPlayListVector[3]][kCutsVector[16]]*mcscaleEmptydata <<std::endl;

}//end of function
*/
std::string EnergyTableLatexString(TRUE_RECO_Energies_Trajectors input_vector  ){

  auto PDG_mcFS_vector = input_vector.PDG_mcFS;
  int PDG_mcFS_place=0;
  auto KE_mcFS_vector = input_vector.KE_mcFS; //toGeV
  double KE_mcFS_place=0;
  auto Angle_mcFS_vector = input_vector.Angle_mcFS;
  double Angle_mcFS_place=0;
  auto  PDG_TRUETrajectors_vector =  input_vector.PDG_TRUETrajectors;
  int PDG_TRUETrajectors_place=0;
  auto  KE_TRUETrajectors_vector =  input_vector.KE_TRUETrajectors; //toGeV;
  double KE_TRUETrajectors_place=0.0;
  auto  Angle_TRUETrajectors_vector =  input_vector.Angle_TRUETrajectors;
  double Angle_TRUETrajectors_place =0.0;

  auto PDG_TRUE_RECOtrks_vector = input_vector.PDG_TRUE_RECOtrks;
  int PDG_TRUE_RECOtrks_place = 0;
  auto KE_TRUE_RECOtrks_vector = input_vector.KE_TRUE_RECOtrks; //toGeV;
  double KE_TRUE_RECOtrks_place =0;
  auto Angle_TRUE_RECOtrks_vector = input_vector.Angle_TRUE_RECOtrks;
  double Angle_TRUE_RECOtrks_place=0;




  int size_mcFS = PDG_mcFS_vector.size();
  int j=0;
  int size_Traj =  PDG_TRUETrajectors_vector.size();
  int k=0;
  int size_Reco = PDG_TRUE_RECOtrks_vector.size();
  int h=0;

  std::vector<int>index={size_mcFS,size_Traj,size_Reco};
  int max_size = 0;
  for(auto dog : index){
    if(dog>max_size){max_size=dog;}
  }




  std::ostringstream output_string;
  output_string.precision(4);

  string cline = "\\cline{2-13}";

  auto table = makeTableString(13,"l");
  output_string << "\\resizebox{\\textwidth}{!}{" << "\n";
  output_string << "\\begin{table}[]" << "\n";
  output_string << "\\begin{tabular}{||" << table << "|} \n";
  output_string << cline << "\n";
  output_string << "\\hline \n";
  output_string << " & \\multicolumn{4}{c|}{TRUE mc_FS} & \\multicolumn{4}{c|}{True Trajector} & \\multicolumn{4}{c|}{RECO Tracks}  \\\\ \\cline{2-13} \n";
  output_string << "\\hline \n";
  string mcFS_Particlename;
  string Trajector_Particlename;
  string RECO_Particlename;
  output_string<<" & PDG & Name & KE Energy [GeV] & Angle (wrtb) [Degs] & PDG  & Name & KE Energy [GeV] & Angle (wrtb) [Degs] & PDG  & Name & KE Energy [GeV] & Angle (wrtb) [Degs] \\ \\cline{2-13} \n";
  output_string << "\\hline \n";
  for(int gg=0; gg < max_size;gg++){

    if(j<size_mcFS)
    {
      PDG_mcFS_place=input_vector.PDG_mcFS.at(j);
      KE_mcFS_place=input_vector.KE_mcFS.at(j)*.001; //toGeV
      Angle_mcFS_place=input_vector.Angle_mcFS.at(j);
      mcFS_Particlename = GetcommonNamefromPDG(PDG_mcFS_place,true);

    }
    else
    {
      PDG_mcFS_place=-9999;
      KE_mcFS_place=-9999;
      Angle_mcFS_place=-9999;
      mcFS_Particlename = " ";
    }
    if(k<size_Traj)
    {
      PDG_TRUETrajectors_place =  input_vector.PDG_TRUETrajectors.at(k);
      KE_TRUETrajectors_place =  input_vector.KE_TRUETrajectors.at(k)*.001; // to GeV
      Angle_TRUETrajectors_place =  input_vector.Angle_TRUETrajectors.at(k);
      Trajector_Particlename = GetcommonNamefromPDG(PDG_TRUETrajectors_place,true);
    }
    else
    {
      PDG_TRUETrajectors_place =  -9999;
      KE_TRUETrajectors_place =   -9999;
      Angle_TRUETrajectors_place = -9999;
      Trajector_Particlename = " ";
    }
    if(h<size_Reco)
    {
      PDG_TRUE_RECOtrks_place = input_vector.PDG_TRUE_RECOtrks.at(h);
      KE_TRUE_RECOtrks_place =input_vector.KE_TRUE_RECOtrks.at(h)*.001; // toGeV
      Angle_TRUE_RECOtrks_place = input_vector.Angle_TRUE_RECOtrks.at(h) * (180 / 3.141592);
      RECO_Particlename = GetcommonNamefromPDG(PDG_TRUE_RECOtrks_place,true);
    }
    else
    {
      PDG_TRUE_RECOtrks_place = -9999;
      KE_TRUE_RECOtrks_place =-9999;
      Angle_TRUE_RECOtrks_place = -9999;
      RECO_Particlename = " ";
    }


    output_string << "&"<<PDG_mcFS_place <<" & " << mcFS_Particlename << " & "<< KE_mcFS_place << " & " << Angle_mcFS_place
                  << "&"<< PDG_TRUETrajectors_place <<" & " << Trajector_Particlename << " & "<< KE_TRUETrajectors_place << " & " << Angle_TRUETrajectors_place
                  << "&"<< PDG_TRUE_RECOtrks_place <<" & " << RECO_Particlename << " & "<< KE_TRUE_RECOtrks_place << " & " << Angle_TRUE_RECOtrks_place
                  << " \\\\" <<cline<<"\n";

                  j++;
                  k++;
                  h++;


  }
  output_string << "\\hline \n";
  output_string << "\\end{tabular} \n";
  output_string << "\\end{table}} \n";




  return output_string.str();
}//end of function

void MakeEfficiencyCutCVS(EventCount_RECO &TRUE_Event_map, EventCount_RECO &RECOEvent_map, std::vector<ECuts> kCutsVector,const char* title,double POT_scaler){

  char Title[1024];
  sprintf(Title, "CutEfficiency_%s.cvs", title );
  std::ofstream myfile;
  myfile.open(Title);
  myfile<<"#Playlist"<< title << "\n";
  myfile<<" CutName, CutNum,denominator , Numerator , Efficiency,POT_playlist " << "\n";
  for (auto cut : kCutsVector){
    myfile<<GetCutName(cut) <<","<< cut<< ","<< TRUE_Event_map[cut]<< ","<<RECOEvent_map[cut]<<","<<RECOEvent_map[cut]/TRUE_Event_map[cut]<<","<< POT_scaler<< "\n";
  }

    myfile.close();

}//end of function




void MakeSecTrkArachne(std::vector <ArachneSecTrk> input_vector,const char* title){

  char Title[1024];
  sprintf(Title, "Arachne_%s.txt", title );
  std::ofstream myfile;
  myfile.open(Title);
  myfile<<"#Playlist"<< title << "\n";
  myfile<<" Run, subrun,gate , slice , Angle (Degs),KE(GeV),pdg " << "\n";
for(auto Arachne : input_vector ){

myfile<< Arachne.run << "," << Arachne.subrun << "," << Arachne.gate << "," << Arachne.slice << "," << Arachne.SecTrk_angle_wrtb << "," << Arachne.SecTrk_KE<< ","<< Arachne.SecTrk_PDG<< "\n";

}

  myfile.close();


}

void MakeSecTrkArachneClean(std::vector <ArachneSecTrk> input_vector,const char* title){

  char Title[1024];
  sprintf(Title, "Arachne_%s.txt", title );
  std::ofstream myfile;
  myfile.open(Title);
  myfile<<"#Playlist"<< title << "\n";
  myfile<<" Run, subrun,gate , slice "<< "\n";
for(auto Arachne : input_vector ){

myfile<< Arachne.run << "," << Arachne.subrun << "," << Arachne.gate << "," << Arachne.slice  << "\n";

}

  myfile.close();


}


void EventCounter_TRUTH(const CVUniverse& universe, std::vector<ECutsTRUTH> TrueCuts, EventCount_Truth &Event_map ,double Weight  )
{

  bool pass = true;

  for (auto c : TrueCuts){
    pass = pass && PassesTRUTH(universe, c);
if(pass==true){
    Event_map[c]+=Weight;
  }
else{continue;}

}//end of loop

return;


}//end of function



void Make_cvsOfCutsRateTRUE( std::vector<ECutsTRUTH> kCutsVector , EventCount_Truth Cutnumbers, const char* File_title , double POT_scaler, double POT_count ){
    std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
    std::cout<<"Printing CutRate for:" <<File_title<<std::endl;
    std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
    double countdata,countdata_scale;
    char ismC[1024];


    sprintf(ismC, "TRUTH" );



    char Title[1024];
    sprintf(Title, "EventRateCuts_ME_%s_%s.txt", ismC, File_title );
    std::ofstream myfile;
    myfile.open(Title);
    myfile<<"#Playlist"<< File_title << "\n";
    myfile<<"CutName, CutNum ,NEventFULL, NEventFULL(POT), Loss, Loss(POT), PrecentLoss, OverallPrecentLoss, POT scaler" << "\n";

    double  start = Cutnumbers[kCutsVector[0]];
    countdata=start;
    countdata_scale=start*POT_scaler;

    for (auto cut : kCutsVector){
    myfile<< GetCutNameTRUTH(cut)<<","<<
    (int)cut <<","<<
    Cutnumbers[cut] << ","<<
    Cutnumbers[cut]*POT_scaler << "," <<
    countdata - Cutnumbers[cut]<<","<<
    countdata_scale - Cutnumbers[cut]*POT_scaler << "," <<
    100*(countdata - Cutnumbers[cut]) / countdata<<","<<
    100*(countdata - Cutnumbers[cut]) / start     << "," <<
    POT_scaler <<","<<POT_count<<"\n";

    countdata_scale=Cutnumbers[cut]*POT_scaler;
    countdata=Cutnumbers[cut];

    }

}//end of function


void MakeSecTrkArachne_TRKDetails(std::vector <Arachne_alltracks> input_vector,const char* title, const bool isdata ,const bool useRodriges){

  char Title[1024];
  sprintf(Title, "Arachne_%s.txt", title );
  std::ofstream myfile;
  myfile.open(Title);
  myfile<<"#Playlist"<< title << "\n";
  myfile<<" Run, subrun,gate , slice " << "\n";
  for(auto Arachne : input_vector ){
    SliceID event_id;
    event_id.run = Arachne.run;
    event_id.subrun = Arachne.subrun;
    event_id.gate = Arachne.gate;
    event_id.slice = Arachne.slice;
    std::string Link_path = arachne(event_id, isdata, useRodriges);


    myfile<<"Run, subrun, gate, slice, link " << "\n";
    myfile<< Arachne.run << "," << Arachne.subrun << "," << Arachne.gate << "," << Arachne.slice << ","<< Link_path<< "\n";
    myfile << "Number of Trks, , , , " <<  Arachne.totalNTRK << "\n";
    myfile<<","<< "PDG" << "," << "Name" << "," << " KE Energy [GeV]" << "," << "Angle (wrtb) [Degs]"<< "\n";

    auto const minsize = std::min(
      Arachne.Trk_PDG.size(),
      std::min(
        Arachne.Trk_angle.size(),
        Arachne.Trk_Energy.size()
      )
    );

    for(int i =0 ; i < minsize; i++)
    {
      auto common_name = GetcommonNamefromPDG(Arachne.Trk_PDG.at(i));
      myfile<< "," <<Arachne.Trk_PDG.at(i) << "," << common_name << "," << Arachne.Trk_Energy.at(i) << "," << Arachne.Trk_angle.at(i) << "\n";
    }
    myfile<<" , , , ," << "\n";
}

  myfile.close();


}


void MakeTrueTrajectorInfoTextfile(std::vector <Trajector> input_vector,const char* title ,const bool useRodriges){

  char Title[1024];
  sprintf(Title, "TrueTrajectorInfo_%s.txt", title );
  std::ofstream myfile;
  myfile.open(Title);
  myfile<<"#Playlist"<< title << "\n";
  for(auto Arachne : input_vector ){
    myfile<<" , , , , , , , , , ," << "\n";
    SliceID event_id;
    event_id.run = Arachne.RunInfo.run;
    event_id.subrun = Arachne.RunInfo.subrun;
    event_id.gate = Arachne.RunInfo.gate;
    event_id.slice = Arachne.RunInfo.slice;
    std::string Link_path = arachne(event_id, false, useRodriges);

    myfile<<"Run, subrun, gate, slice, link " << "\n";
    myfile<< event_id.run << "," << event_id.subrun << "," << event_id.gate << "," << event_id.slice << ","<< Link_path<< "\n";
    myfile<<" , , , , , , , , , ," << "\n";
    myfile<< "PDG,Name,KE Energy [GeV],Angle (wrtb) [Degs],Intial X, intial Y, intial Z, Final X, Final Y, Final Z,"<<"\n";

    int i=0;

    for(auto pdg : Arachne.PDG )
    {
      auto name = GetcommonNamefromPDG(pdg);
      myfile<< pdg << "," << name << "," << Arachne.KE.at(i)*.001 << "," << Arachne.Angle.at(i) << "," << Arachne.InitalTrkx.at(i) << "," << Arachne.InitalTrky.at(i)<<"," << Arachne.InitalTrkz.at(i)
      <<"," << Arachne.FinalTrkx.at(i) << "," << Arachne.FinalTrky.at(i)<<"," << Arachne.FinalTrkz.at(i)<< "\n";

      i++;
    }


  myfile<<" , , , , , , , , , ," << "\n";

}

  myfile.close();







}//end of function


void MakeLatex_particleTraj_True_RECO_plots(std::vector<Trajector> TRUE_trk,
                                            std::vector<Trajector> RECO_tks,
                                            std::vector<TRUE_RECO_Energies_Trajectors> inputEnergy_vector,
                                            std::string pdfWithFigs_name, std::string output_name, std::string Playlist){

    double scale= .35;
    std::ofstream myfile;
    string fileName = output_name + ".txt";
    myfile.open(fileName,	std::ios::trunc);
    std::cout<<"Name of Output File "<< fileName<<std::endl;
    LatexFormat Energy_latex_Latex(scale);

    int pageCount = 2;
    std::cout << " Name of input PDF = "<< pdfWithFigs_name << std::endl;




    if (CheckIfTrajectors_VectorsHaveEqual_RunInfo(TRUE_trk,RECO_tks)==true &&
        CheckIfTrajectors_TRUERECO_KEVectorsHaveEqual_RunInfo(TRUE_trk ,inputEnergy_vector) == true)
        {
          std::cout<< "input trajector vector have same equal Run Info"<<std::endl;}
          else
          {
            std::cout<< "ERROR input trajector vector DONT have same equal Run Info ERROR "<<std::endl;
            return;
          }

          int Size = TRUE_trk.size();


    for(auto cat:inputEnergy_vector){

      auto  run = cat.RunInfo.run;
      auto  subrun = cat.RunInfo.subrun;
      auto  gate = cat.RunInfo.gate;
      auto  slice = cat.RunInfo.slice;

      SliceID event_id;
      event_id.run = run;
      event_id.subrun = subrun;
      event_id.gate = gate;
      event_id.slice = slice;
      std::string Link_path = arachne(event_id, false, true);



      char runinfo_number[1024];
      char runinfo[1024];
      char Playlist_char[Playlist.size()+1];
      strcpy( Playlist_char,Playlist.c_str());
      sprintf(runinfo_number, "(%i/%i/%i/%i)",run,subrun,gate,slice);

      sprintf(runinfo, "TRUE and RECO trks for Playlist: %s (%i/%i/%i/%i)",Playlist_char,run,subrun,gate,slice);
      std::string section_title(runinfo_number);
      std::string title_slide(runinfo);
      string urllink_display = "Arachne Link:" + section_title;
      myfile<<"\n";
      myfile<<Energy_latex_Latex.GetSubSection(section_title);
      myfile<<"\n";
      myfile<<"%%%%%%%%%%%%%%%%% \n";
      myfile<<"%%%  PLOTS Table info slide   "<<  title_slide <<"\n";
      myfile<<"%%%%%%%%%%%%%%%%% \n";
      myfile<<Energy_latex_Latex.GetBeginFrame(title_slide)<< "\n";
      myfile<<Energy_latex_Latex.BeingItemize()<< "\n";
      myfile<<Energy_latex_Latex.GetItem()<<Energy_latex_Latex.Get_URLlink( Link_path, urllink_display)<< "\n";
      myfile<<Energy_latex_Latex.EndItemize()<< "\n";
      std::cout<<"starting Table"<<std::endl;
      myfile<<EnergyTableLatexString(cat);
      myfile<<"\n";
      myfile<<Energy_latex_Latex.GetEndFrame();
      myfile<<"\n";
      myfile<<"%%%%%%%%%%%%%%%%% \n";
      myfile<<"%%% END FRAME for Trajection Info Slide "<< title_slide<<"\n";
      myfile<<"%%%%%%%%%%%%%%%%% \n";
      myfile<<"\n";
      myfile<<"%%%%%%%%%%%%%%%%% \n";
      myfile<<"%%%  PLOTS Trajector  "<<  title_slide <<"\n";
      myfile<<"%%%%%%%%%%%%%%%%% \n";
      string Var_name = "XvsZ and YvsZ Trajector Plots " + section_title;
      myfile<<Energy_latex_Latex.GetBeginFrame(Var_name)<< "\n";
      myfile<<Energy_latex_Latex.GetBeginTabular()<< "\n";
      myfile<<Energy_latex_Latex.GetInclude_figure(pageCount,pdfWithFigs_name)<< "\n";
      myfile<<"& \n";
      myfile<<Energy_latex_Latex.GetInclude_figure(pageCount+1,pdfWithFigs_name)<< "\n";
      myfile<<Energy_latex_Latex.GetEndTabular()<< "\n";
      myfile<<Energy_latex_Latex.GetEndFrame();
      myfile<<"\n";
      myfile<<"%%%%%%%%%%%%%%%%% \n";
      myfile<<"%%% END FRAME for Trajection  "<< Var_name<< "\n";
      myfile<<"%%%%%%%%%%%%%%%%% \n";

      pageCount= pageCount + 2;
    }


    myfile.close();
  }//end of Function










#endif
