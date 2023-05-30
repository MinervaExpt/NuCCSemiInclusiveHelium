#include "Helium_SideBandTool.h"

Helium_SideBandTool::Helium_SideBandTool(){
current_unv = 0;
}

 Helium_SideBandTool::Helium_SideBandTool(std::string input_PathtoRootMC_empty,
                                         std::string input_PathtoRootData_empty,
                                         std::string input_PathtoRootMC_full,
                                         std::string input_PathtoRootData_full,
                                         std::vector<std::string> histNames,
                                         std::vector<Fit_Parms_Names> FitParms,
                                         double FullPOTMC, double EmptyPOTMC, double FullPOTdata, double EmptyPOTdata )
{
    current_unv = 0;
    OpenRootFiles_Empty(input_PathtoRootMC_empty,  input_PathtoRootData_empty);
    OpenRootFiles_Full( input_PathtoRootMC_full,   input_PathtoRootData_full);
    OpenRootFiles_Full_Empty(input_PathtoRootMC_full,   input_PathtoRootData_full );
    FillHistName_Map(Helium_Empty, histNames , FitParms );
    FillHistName_Map(Helium_Full, histNames , FitParms );
    FillHistName_Map(Helium_Full_Empty, histNames , FitParms );
    std::cout<<"Finished Filling HistName map "<<std::endl;
    FillPotScaler(Helium_Full, FullPOTdata, FullPOTMC);
    FillPotScaler(Helium_Empty, EmptyPOTdata, EmptyPOTMC);
    FillPotScaler(Helium_Full_Empty, FullPOTdata, FullPOTMC);
    std::cout<<"Finished Filling Pot Scaler"<<std::endl;
    initSideBands_2playlist();

}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::init_Tool_2playlist(std::string input_PathtoRootMC_empty,
  std::string input_PathtoRootData_empty,
  std::string input_PathtoRootMC_full,
  std::string input_PathtoRootData_full,
  std::vector<std::string> histNames,
  std::vector<Fit_Parms_Names> FitParms,
  double FullPOTMC, double EmptyPOTMC, double FullPOTdata, double EmptyPOTdata ){

    current_unv = 0;
    OpenRootFiles_Empty(input_PathtoRootMC_empty,  input_PathtoRootData_empty);
    OpenRootFiles_Full( input_PathtoRootMC_full,   input_PathtoRootData_full);
    OpenRootFiles_Full_Empty(input_PathtoRootMC_full,   input_PathtoRootData_full );
    FillHistName_Map(Helium_Empty, histNames , FitParms );
    FillHistName_Map(Helium_Full, histNames , FitParms );
    FillHistName_Map(Helium_Full_Empty, histNames , FitParms );
    FillPotScaler(Helium_Full, FullPOTdata, FullPOTMC);
    FillPotScaler(Helium_Empty, EmptyPOTdata, EmptyPOTMC);
    FillPotScaler(Helium_Full_Empty,  FullPOTdata, FullPOTMC); // Shoulder have to sale Full - Minus
    initSideBands_2playlist();
    std::cout<<"init_Tool: COMPLETE"<<std::endl;


  }
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::InputPDFLabel(std::string input){
    PDF_printingLabel_input = input+ ".pdf";
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::Plot_initHist(std::string Full_info, std::string Empty_info, std::string axisName_fit)
{
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"~~~~~~~~~~~~~Ploting Intial Input Hist~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  double POT_ratio =1.0;
  std::string title;
  title = "Fitting Parameter Before Vertex R [mm] Fit [F("+Full_info + ")]";
  Plot(Helium_Full, 0, POT_ratio , "FitName", PDF_printingLabel_input, title, axisName_fit); // Raw
  title = "Fitting Parameter Before Vertex R [mm] Fit [E("+Empty_info + ")]";
  Plot(Helium_Empty, 0, POT_ratio , "FitName", PDF_printingLabel_input, title, axisName_fit); // Raw
  title = "Fitting Parameter Before Vertex R [mm] Fit [F("+Full_info + ") - E(" + Empty_info + ")]";
  Plot(Helium_Full_Empty, 0, POT_ratio , "FitName", PDF_printingLabel_input, title, axisName_fit); // Raw
  title = "Before Fit P_{T,#mu} [GeV] [E(" + Empty_info + ")]";
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Helium_Empty,  Helium_Empty.muon_PT,"muon_PT",title, "P_{T,#mu} [GeV]");
  title = "Before Fit P_{Z,#mu} [GeV] [E(" + Empty_info + ")]";
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Helium_Empty,  Helium_Empty.muon_PZ,"muon_PZ",title, "P_{Z,#mu} [GeV]");
  title = "Before Fit #theta_{#mu} [Deg] [E(" + Empty_info + ")]";
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Helium_Empty,  Helium_Empty.muon_theta,"muon_theta",title, "#theta_{#mu} [Deg]");
  title = "Before Fit E_{#mu} [GeV] [E(" + Empty_info + ")]";
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Helium_Empty,  Helium_Empty.muon_E,"muon_E",title,"E_{#mu} [GeV]" );
  title = "Before Fit Vertex X [mm] [E(" + Empty_info + ")]";
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Helium_Empty,  Helium_Empty.Vertex_X,"Vertex_X",title, "Vertex X [mm]" );
  title = "Before Fit Vertex Y [mm] [E(" + Empty_info + ")]";
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Helium_Empty,  Helium_Empty.Vertex_Y,"Vertex_Y",title, "Vertex Y [mm]" );
  title = "Before Fit Vertex Z [mm] [E(" + Empty_info + ")]";
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Helium_Empty,  Helium_Empty.Vertex_Z,"Vertex_Z",title, "Vertex Z [mm]" );
  title = "Before Fit Distance to Edge [mm] [E(" + Empty_info + ")]";
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Helium_Empty,  Helium_Empty.DistancetoEdge,"DistancetoEdge",title, "Distance to Edge [mm]");

  title = "Before Fit P_{T,#mu} [GeV] [F(" + Full_info + ")]";
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Helium_Full,  Helium_Full.muon_PT,"muon_PT", title, "P_{T,#mu} [GeV]");
  title = "Before Fit P_{Z,#mu} [GeV] [F(" + Full_info + ")]";
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Helium_Full,  Helium_Full.muon_PZ,"muon_PZ", title, "P_{Z,#mu} [GeV]");
  title = "Before Fit #theta_{#mu} [Deg] [F(" + Full_info + ")]";
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Helium_Full,  Helium_Full.muon_theta,"muon_theta", title, "#theta_{#mu} [Deg]");
  title = "Before E_{#mu} [GeV] Fit  [F(" + Full_info + ")]";
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Helium_Full,  Helium_Full.muon_E,"muon_E", title, "E_{#mu} [GeV]" );
  title = "Before Fit Vertex X [mm] [F(" + Full_info + ")]";
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Helium_Full,  Helium_Full.Vertex_X,"Vertex_X", title, "Vertex X [mm]" );
  title = "Before Fit Vertex Y [mm] [F(" + Full_info + ")]";
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Helium_Full,  Helium_Full.Vertex_Y,"Vertex_Y", title, "Vertex Y [mm]" );
  title = "Before Fit Vertex Z [mm] [F(" + Full_info + ")]";
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Helium_Full,  Helium_Full.Vertex_Z,"Vertex_Z", title, "Vertex Z [mm]" );
  title = "Before Fit Distance to Edge [mm] [F(" + Full_info + ")]";
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Helium_Full,  Helium_Full.DistancetoEdge,"DistancetoEdge", title, "Distance to Edge [mm]");

  title = "Before Fit P_{T,#mu} [GeV] [F(" + Full_info + ") - E(" + Empty_info + ")]";
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Helium_Full_Empty,  Helium_Full_Empty.muon_PT,"muon_PT",title, "P_{T,#mu} [GeV]");
  title = "Before Fit P_{Z,#mu} [GeV] [F(" + Full_info + ") - E(" + Empty_info + ")]";
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Helium_Full_Empty,  Helium_Full_Empty.muon_PZ,"muon_PZ",title, "P_{Z,#mu} [GeV]");
  title = "Before Fit #theta_{#mu} [Deg] [F(" + Full_info + ") - E(" + Empty_info + ")]";
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Helium_Full_Empty,  Helium_Full_Empty.muon_theta,"muon_theta",title, "#theta_{#mu} [Deg]");
  title = "Before Fit E_{#mu} [GeV] [F(" + Full_info + ") - E(" + Empty_info + ")]";
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Helium_Full_Empty,  Helium_Full_Empty.muon_E,"muon_E",title, "E_{#mu} [GeV]" );
  title = "Before Fit Vertex X [mm] [F(" + Full_info + ") - E(" + Empty_info + ")]";
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Helium_Full_Empty,  Helium_Full_Empty.Vertex_X,"Vertex_X",title, "Vertex X [mm]" );
  title = "Before Fit Vertex Y [mm] [F(" + Full_info + ") - E(" + Empty_info + ")]";
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Helium_Full_Empty,  Helium_Full_Empty.Vertex_Y,"Vertex_Y",title, "Vertex Y [mm]" );
  title = "Before Fit Vertex Z [mm] [F(" + Full_info + ") - E(" + Empty_info + ")]";
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Helium_Full_Empty,  Helium_Full_Empty.Vertex_Z,"Vertex_Z",title, "Vertex Z [mm]" );
  title = "Before Fit Distance to Edge [mm] [F(" + Full_info + ") - E(" + Empty_info + ")]";
  Plot(PDF_printingLabel_input,  POT_ratio,  0, Helium_Full_Empty,  Helium_Full_Empty.DistancetoEdge,"DistancetoEdge",title, "Distance to Edge [mm]");

  cout<<"======================================================================"<<endl;
  cout<<"Finished Plotting Intial Hist :)"<<endl;
  cout<<"======================================================================"<<endl;
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::Plot_AfterFitHist(std::string Full_info,
  std::string Empty_info, std::string axisName_fit){

    std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
    std::cout<<"~~~~~~~~~~~~~Ploting FITTED Hist~~~~~~~~~~~~~~~~~~~"<<std::endl;
    std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
    double POT_ratio =1.0;
    std::string title;

    title = "Fitting Parameter Vertex R [mm] After Fit [F("+Full_info + ")]";
    Plot(Helium_Full, 1, POT_ratio , "FitName", PDF_printingLabel_input, title, axisName_fit,0); // Raw
    title = "Fitting Parameter Vertex R [mm] After Fit [E("+Empty_info + ")]";
    std::cout<<"Hist Title : " << title<<std::endl;
    Plot(Helium_Empty, 1, POT_ratio , "FitName", PDF_printingLabel_input, title, axisName_fit,1); // Raw
    title = "Fitting Parameter Vertex R [mm] After Fit [F("+Full_info + ") - E(" + Empty_info + ")]";
    Plot(Helium_Full_Empty, 1, POT_ratio , "FitName", PDF_printingLabel_input, title, axisName_fit,2); // Raw
    title = "After Fit P_{T,#mu} [GeV] [E(" + Empty_info + ")]";
    Plot(PDF_printingLabel_input,  POT_ratio,  1, Helium_Empty,  Helium_Empty.muon_PT,"muon_PT",title, "P_{T,#mu} [GeV]",3);
    title = "After Fit P_{Z,#mu} [GeV] [E(" + Empty_info + ")]";
    Plot(PDF_printingLabel_input,  POT_ratio,  1, Helium_Empty,  Helium_Empty.muon_PZ,"muon_PZ",title, "P_{Z,#mu} [GeV]",4);
    title = "After Fit #theta_{#mu} [Deg] [E(" + Empty_info + ")]";
    Plot(PDF_printingLabel_input,  POT_ratio,  1, Helium_Empty,  Helium_Empty.muon_theta,"muon_theta",title, "#theta_{#mu} [Deg]",5);
    title = "After Fit E_{#mu} [GeV] [E(" + Empty_info + ")]";
    Plot(PDF_printingLabel_input,  POT_ratio,  1, Helium_Empty,  Helium_Empty.muon_E,"muon_E",title,"E_{#mu} [GeV]",6 );
    title = "After Fit Vertex X [mm] [E(" + Empty_info + ")]";
    Plot(PDF_printingLabel_input,  POT_ratio,  1, Helium_Empty,  Helium_Empty.Vertex_X,"Vertex_X",title, " Vertex X [mm]",7 );
    title = "After Fit Vertex Y [mm] [E(" + Empty_info + ")]";
    Plot(PDF_printingLabel_input,  POT_ratio,  1, Helium_Empty,  Helium_Empty.Vertex_Y,"Vertex_Y",title, "Vertex Y [mm]" ,8);
    title = "After Fit Vertex Z [mm] [E(" + Empty_info + ")]";
    Plot(PDF_printingLabel_input,  POT_ratio,  1, Helium_Empty,  Helium_Empty.Vertex_Z,"Vertex_Z",title, "Vertex Z [mm]",9 );
    title = "After Fit Distance to Edge [mm] [E(" + Empty_info + ")]";
    Plot(PDF_printingLabel_input,  POT_ratio,  1, Helium_Empty,  Helium_Empty.DistancetoEdge,"DistancetoEdge",title, "Distance to Edge [mm]",10);

    title = "After Fit P_{T,#mu} [GeV] [F(" + Full_info + ")]";
    Plot(PDF_printingLabel_input,  POT_ratio,  1, Helium_Full,  Helium_Full.muon_PT,"muon_PT", title, "P_{T,#mu} [GeV]",11);
    title = "After Fit P_{Z,#mu} [GeV] [F(" + Full_info + ")]";
    Plot(PDF_printingLabel_input,  POT_ratio,  1, Helium_Full,  Helium_Full.muon_PZ,"muon_PZ", title, "P_{Z,#mu} [GeV]",12);
    title = "After Fit #theta_{#mu} [Deg] [F(" + Full_info + ")]";
    Plot(PDF_printingLabel_input,  POT_ratio,  1, Helium_Full,  Helium_Full.muon_theta,"muon_theta", title, "#theta_{#mu} [Deg]",13);
    title = "After Fit E_{#mu} [GeV] [F(" + Full_info + ")]";
    Plot(PDF_printingLabel_input,  POT_ratio,  1, Helium_Full,  Helium_Full.muon_E,"muon_E", title, "E_{#mu} [GeV]",14 );
    title = "After Fit Vertex X [mm] Vertex X [mm] [F(" + Full_info + ")]";
    Plot(PDF_printingLabel_input,  POT_ratio,  1, Helium_Full,  Helium_Full.Vertex_X,"Vertex_X", title, "Vertex X [mm]",15 );
    title = "After Fit Vertex Y [mm] Vertex X [mm] [F(" + Full_info + ")]";
    Plot(PDF_printingLabel_input,  POT_ratio,  1, Helium_Full,  Helium_Full.Vertex_Y,"Vertex_Y", title, "Vertex Y [mm]",16 );
    title = "After Fit Vertex Z [mm] Vertex X [mm] [F(" + Full_info + ")]";
    Plot(PDF_printingLabel_input,  POT_ratio,  1, Helium_Full,  Helium_Full.Vertex_Z,"Vertex_Z", title, "Vertex Z [mm]" ,17);
    title = "After Fit Distance to Edge [mm] [F(" + Full_info + ")]";
    Plot(PDF_printingLabel_input,  POT_ratio,  1, Helium_Full,  Helium_Full.DistancetoEdge,"DistancetoEdge", title, "Distance to Edge [mm]",18);


    title = "After Fit P_{T,#mu} [GeV] [F(" + Full_info + ") - E(" + Empty_info + ")]";
    Plot(PDF_printingLabel_input,  POT_ratio,  1, Helium_Full_Empty,  Helium_Full_Empty.muon_PT,"muon_PT", title, "P_{T,#mu} [GeV]",19);
    title = "After Fit P_{Z,#mu} [GeV] [F(" + Full_info + ") - E(" + Empty_info + ")]";
    Plot(PDF_printingLabel_input,  POT_ratio,  1, Helium_Full_Empty,  Helium_Full_Empty.muon_PZ,"muon_PZ", title, "P_{Z,#mu} [GeV]",20);
    title = "After Fit #theta_{#mu} [Deg] [F(" + Full_info + ") - E(" + Empty_info + ")]";
    Plot(PDF_printingLabel_input,  POT_ratio,  1, Helium_Full_Empty,  Helium_Full_Empty.muon_theta,"muon_theta", title, "#theta_{#mu} [Deg]",21);
    title = "After Fit E_{#mu} [GeV] [F(" + Full_info + ") - E(" + Empty_info + ")]";
    Plot(PDF_printingLabel_input,  POT_ratio,  1, Helium_Full_Empty,  Helium_Full_Empty.muon_E,"muon_E", title, "E_{#mu} [GeV]",22 );
    title = "After Fit Vertex X [mm] [F(" + Full_info + ") - E(" + Empty_info + ")]";
    Plot(PDF_printingLabel_input,  POT_ratio,  1, Helium_Full_Empty,  Helium_Full_Empty.Vertex_X,"Vertex_X", title, "Vertex X [mm]",23 );
    title = "After Fit Vertex Y [mm] [F(" + Full_info + ") - E(" + Empty_info + ")]";
    Plot(PDF_printingLabel_input,  POT_ratio,  1, Helium_Full_Empty,  Helium_Full_Empty.Vertex_Y,"Vertex_Y", title, "Vertex Y [mm]",24 );
    title = "After Fit Vertex Z [mm] [F(" + Full_info + ") - E(" + Empty_info + ")]";
    Plot(PDF_printingLabel_input,  POT_ratio,  1, Helium_Full_Empty,  Helium_Full_Empty.Vertex_Z,"Vertex_Z", title, "Vertex Z [mm]",25 );
    title = "After Fit Distance to Edge [mm] [F(" + Full_info + ") - E(" + Empty_info + ")]";
    Plot(PDF_printingLabel_input,  POT_ratio,  1, Helium_Full_Empty,  Helium_Full_Empty.DistancetoEdge,"DistancetoEdge", title, "Distance to Edge [mm]",26);
    return;
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::Plot( std::string fitName, std::string pdf_label, std::string xaxislabel)
{
    double POT_ratio = 1.0;
    std::string title;
    title = "Fitting Parameter Before Fit [E()]";
    Plot(Helium_Empty,  POT_ratio, fitName, pdf_label,title, xaxislabel);
        title = "Fitting Parameter Before Fit [F()]";
    Plot(Helium_Full,  POT_ratio, fitName, pdf_label,title, xaxislabel);

    title = "Before Fit [E()]";
    Plot(pdf_label,  POT_ratio,  0, Helium_Empty,  Helium_Empty.muon_PT,"muon_PT",title, "P_{T,#mu} [GeV]");
    Plot(pdf_label,  POT_ratio,  0, Helium_Empty,  Helium_Empty.muon_PZ,"muon_PZ",title, "P_{Z,#mu} [GeV]");
    Plot(pdf_label,  POT_ratio,  0, Helium_Empty,  Helium_Empty.muon_theta,"muon_theta",title, "#theta_{#mu} [Deg]");
    Plot(pdf_label,  POT_ratio,  0, Helium_Empty,  Helium_Empty.muon_E,"muon_E",title, "E_{#mu} [GeV]" );
    Plot(pdf_label,  POT_ratio,  0, Helium_Empty,  Helium_Empty.Vertex_X,"Vertex_X",title, "Vertex X [mm]" );
    Plot(pdf_label,  POT_ratio,  0, Helium_Empty,  Helium_Empty.Vertex_Y,"Vertex_Y",title, "Vertex Y [mm]" );
    Plot(pdf_label,  POT_ratio,  0, Helium_Empty,  Helium_Empty.Vertex_Z,"Vertex_Z",title, "Vertex Z [mm]" );
    Plot(pdf_label,  POT_ratio,  0, Helium_Empty,  Helium_Empty.DistancetoEdge,"DistancetoEdge",title, "Distance to Edge [mm]");

    title = "Before Fit [F())]";
    Plot(pdf_label,  POT_ratio,  0, Helium_Full,  Helium_Full.muon_PT,"muon_PT",title, "P_{T,#mu} [GeV]");
    Plot(pdf_label,  POT_ratio,  0, Helium_Full,  Helium_Full.muon_PZ,"muon_PZ",title, "P_{Z,#mu} [GeV]");
    Plot(pdf_label,  POT_ratio,  0, Helium_Full,  Helium_Full.muon_theta,"muon_theta",title, "#theta_{#mu} [Deg]");
    Plot(pdf_label,  POT_ratio,  0, Helium_Full,  Helium_Full.muon_E,"muon_E",title, "E_{#mu} [GeV]" );
    Plot(pdf_label,  POT_ratio,  0, Helium_Full,  Helium_Full.Vertex_X,"Vertex_X",title, "Vertex X [mm]" );
    Plot(pdf_label,  POT_ratio,  0, Helium_Full,  Helium_Full.Vertex_Y,"Vertex_Y",title, "Vertex Y [mm]" );
    Plot(pdf_label,  POT_ratio,  0, Helium_Full,  Helium_Full.Vertex_Z,"Vertex_Z",title, "Vertex Z [mm]" );
    Plot(pdf_label,  POT_ratio,  0, Helium_Full,  Helium_Full.DistancetoEdge,"DistancetoEdge",title, "Distance to Edge [mm]");

    return;

}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::FillHistName_Map(HeliumSideBand& sb, std::vector<std::string> histNames , std::vector<Fit_Parms_Names> FitParms ){
std::cout<<"Filling Map"<<std::endl;
  if(histNames.size() != FitParms.size()){std::cout<<"Error input for FillHistName_Map: vectors size is different , Opps !! "<<std::endl;assert(false);}

  for(int i = 0; i < histNames.size(); i++){
    std::cout<<"FIlline Hist Name: "<< histNames.at(i)<<std::endl;
    sb.HistName_Map.insert ( std::pair<Fit_Parms_Names,std::string>(FitParms.at(i),histNames.at(i)));
  }
  return;
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::FillPotScaler(HeliumSideBand& sb,double POTscalerdata, double POTscalerMC ){
  std::cout<<"Inside Set POT Scaler"<<std::endl;
  sb.POT_MC = POTscalerMC;
  sb.POT_Data = POTscalerdata;
  return;

}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::OpenRootFiles_Empty(std::string input_PathtoRootMC, std::string input_PathtoRootData)
{
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<std::endl;
  std::cout<<"Opening root Files for Empty "<<std::endl;
  std::cout<<"Opening MC root: "<<input_PathtoRootMC<<std::endl;
  Helium_Empty.f_mc_fit = new TFile(input_PathtoRootMC.c_str());
  Helium_Empty.f_mc_var = new TFile(input_PathtoRootMC.c_str());
  std::cout<<"Opening Data root: "<<input_PathtoRootData<<std::endl;
  Helium_Empty.f_data_fit = new TFile(input_PathtoRootData.c_str());
  Helium_Empty.f_data_var = new TFile(input_PathtoRootData.c_str());
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<std::endl;
  return;

}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::OpenRootFiles_Full(std::string input_PathtoRootMC, std::string input_PathtoRootData )
{
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<std::endl;
  std::cout<<"Opening root Files for Full "<<std::endl;
  std::cout<<"Opening MC root: "<<input_PathtoRootMC<<std::endl;
  Helium_Full.f_mc_fit = new TFile(input_PathtoRootMC.c_str());
  Helium_Full.f_mc_var = new TFile(input_PathtoRootMC.c_str());
  std::cout<<"Opening Data root: "<<input_PathtoRootData<<std::endl;
  Helium_Full.f_data_fit = new TFile(input_PathtoRootData.c_str());
  Helium_Full.f_data_var = new TFile(input_PathtoRootData.c_str());
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<std::endl;
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::OpenRootFiles_Full_Empty(std::string input_PathtoRootMC, std::string input_PathtoRootData )
{
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<std::endl;
  std::cout<<"Opening root Files for Full "<<std::endl;
  std::cout<<"Opening MC root: "<<input_PathtoRootMC<<std::endl;
  Helium_Full_Empty.f_mc_fit = new TFile(input_PathtoRootMC.c_str());
  Helium_Full_Empty.f_mc_var = new TFile(input_PathtoRootMC.c_str());
  std::cout<<"Opening Data root: "<<input_PathtoRootData<<std::endl;
  Helium_Full_Empty.f_data_fit = new TFile(input_PathtoRootData.c_str());
  Helium_Full_Empty.f_data_var = new TFile(input_PathtoRootData.c_str());
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<std::endl;

}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
MnvH1D* Helium_SideBandTool::GetMnvH1D(TFile* f, std::string var_name){
    std::cout<<"Initialize Hist Name: " << var_name<< std::endl;
    MnvH1D* h = new MnvH1D(*dynamic_cast<MnvH1D*>(f->Get(var_name.c_str())) );
    if (h==0) std::cout << "Could not get 1D hist " << var_name << "\n";
    h->SetDirectory(NULL);
    return h;
  }
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
std::string Helium_SideBandTool::GetName(){
  return Helium_Full.name;
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::initSideBands_2playlist(){
    std::cout<<"Inside:initSideBands_2playlist() "<<std::endl;

      SetNames(Helium_Full, "Helium_Full");
      SetNames(Helium_Empty, "Helium_Empty");
      SetNames(Helium_Full_Empty, "Helium_Full_Empty");
      std::cout<<"Finished SetNames() "<<std::endl;

      std::cout<<"initSideBand_FitHistograms : for Helium_Full "<<std::endl;
      initSideBand_FitHistograms(Helium_Full);
      std::cout<<"initSideBand_FitHistograms : for Helium_Empty "<<std::endl;
      initSideBand_FitHistograms(Helium_Empty);
      std::cout<<"initSideBand_FitHistograms : for Helium_Full_Empty "<<std::endl;
      initSideBand_FitHistograms(Helium_Full_Empty);
      std::cout<<"initSideBand_FitHistograms : POTNorm All hist "<<std::endl;


      std::cout<<"initSideBand_AllUniverses : for Helium_Full "<<std::endl;
      initSideBand_AllUniverses(Helium_Full);
      std::cout<<"initSideBand_AllUniverses : for Helium_Empty "<<std::endl;
      initSideBand_AllUniverses(Helium_Empty);


      std::cout<<"initSideBand_XSecHistograms : for Helium_Full "<<std::endl;
      initSideBand_XSecHistograms(Helium_Full);
      std::cout<<"initSideBand_XSecHistograms : for Helium_Empty "<<std::endl;
      initSideBand_XSecHistograms(Helium_Empty);
      std::cout<<"initSideBand_XSecHistograms : for Helium FUll minus Empty "<<std::endl;
      initSideBand_XSecHistograms(Helium_Full_Empty);
      std::cout<<"FINISHED Initialize Hist for SideBand Fit"<<std::endl;

      //Inti_Xaxis_labels(Helium_Full,  "Vertex R [mm]" );
      //Inti_Xaxis_labels(Helium_Empty,  "Vertex R [mm]" );
      //Inti_Xaxis_labels(Helium_Full_Empty,  "Vertex R [mm]" );

      init_POTScale_AllHist();
      std::cout<<"POT Scale All inti hist"<<std::endl;
      init_Hist_Full_minus_Empty();
      initSideBand_AllUniverses(Helium_Full_Empty);


      std::cout<<"GetStatistics : for Helium_Full "<<std::endl;
      GetStatistics(Helium_Full);
      std::cout<<"GetStatistics : for Helium_Empty "<<std::endl;
      GetStatistics(Helium_Empty);

      // Calc Global ChiSq Before Fit
      for (unsigned int i = 0; i < Helium_Full.data_all_universes.size(); ++i){
          double Global_ChiSq = calc_Global_ChiSq(i, 1.0);
          ChiSq_before_fit.push_back(Global_ChiSq);
      }
  }
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
MnvH2D* Helium_SideBandTool::GetMnvH2D(TFile* f, std::string var_name){
    std::cout<<"Initialize Hist Name: " << var_name<< std::endl;
    MnvH2D* h = new MnvH2D( * dynamic_cast<MnvH2D*>(f->Get(var_name.c_str())) );
    if (h==0) std::cout << "Could not get 1D hist " << var_name << "\n";
       h->SetDirectory(NULL);
       return h;

  }
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::initSideBand_FitHistograms(HeliumSideBand& sb )
{

    std::string var;
    std::cout<<"Inside:nitSideBand_FitHistograms "<<std::endl;
      std::cout<<"Geting HistName: "<<sb.HistName_Map[kh_Name_Data_fitTo] <<std::endl;
      sb.MnvH1D_data = GetMnvH1D(sb.f_data_fit, sb.HistName_Map[kh_Name_Data_fitTo]);
      std::cout<<"Geting HistName: "<<sb.HistName_Map[kh_Name_Data_fitTo] <<std::endl;
      sb.MnvH1D_mc_total = GetMnvH1D(sb.f_mc_fit, sb.HistName_Map[kh_Name_MC_fitting]);

      var = sb.HistName_Map[kh_Name_MC_fitting] + "_Material_Helium";
      sb.MnvH1D_Helium[0] = GetMnvH1D(sb.f_mc_fit, var);

      var = sb.HistName_Map[kh_Name_MC_fitting] + "_Material_Aluminium";
      sb.MnvH1D_Aluminium[0] = GetMnvH1D(sb.f_mc_fit, var);

      var = sb.HistName_Map[kh_Name_MC_fitting] + "_Material_Lead";
      sb.MnvH1D_Lead[0] = GetMnvH1D(sb.f_mc_fit, var);

      var = sb.HistName_Map[kh_Name_MC_fitting] + "_Material_Carbon";
      sb.MnvH1D_Carbon[0] = GetMnvH1D(sb.f_mc_fit, var);

      var = sb.HistName_Map[kh_Name_MC_fitting] + "_Material_Iron";
      sb.MnvH1D_Iron[0] = GetMnvH1D(sb.f_mc_fit, var);

      var = sb.HistName_Map[kh_Name_MC_fitting] + "_Material_Other";
      sb.MnvH1D_Other[0] = GetMnvH1D(sb.f_mc_fit, var);
  }
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::initSideBand_XSecHistograms(HeliumSideBand& sb,
     XSec_Var& xsec_var, std::string Data_hist, std::string MChist_name  )
{

      std::string var;
      std::cout<<"inside:initSideBand_XSecHistograms"<<std::endl;
      xsec_var.MnvH1D_data = GetMnvH1D(sb.f_data_var, Data_hist);

      xsec_var.MnvH1D_mc_total = GetMnvH1D(sb.f_mc_var, MChist_name);

      var = MChist_name + "_Material_Helium";
      xsec_var.MnvH1D_Helium[0] = GetMnvH1D(sb.f_mc_var, var);

      var = MChist_name + "_Material_Aluminium";
      xsec_var.MnvH1D_Aluminium[0] = GetMnvH1D(sb.f_mc_var, var);

      var = MChist_name + "_Material_Carbon";
      xsec_var.MnvH1D_Carbon[0] = GetMnvH1D(sb.f_mc_var, var);

      var = MChist_name + "_Material_Lead";
      xsec_var.MnvH1D_Lead[0] = GetMnvH1D(sb.f_mc_var, var);

      var = MChist_name + "_Material_Iron";
      xsec_var.MnvH1D_Iron[0] = GetMnvH1D(sb.f_mc_var, var);

      var = MChist_name + "_Material_Other";
      xsec_var.MnvH1D_Other[0] = GetMnvH1D(sb.f_mc_var, var);
  }
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::init_fitHist_Full_Empty(HeliumSideBand &sb_full_empty, HeliumSideBand &sb_full){
  std::string var;
  std::cout<<"Inside:nitSideBand_FitHistograms "<<std::endl;
    std::cout<<"Geting HistName: "<<sb_full.HistName_Map[kh_Name_Data_fitTo] <<std::endl;
    sb_full_empty.MnvH1D_data = GetMnvH1D(sb_full.f_data_fit, sb_full.HistName_Map[kh_Name_Data_fitTo]);
    std::cout<<"Geting HistName: "<<sb_full.HistName_Map[kh_Name_Data_fitTo] <<std::endl;
    sb_full_empty.MnvH1D_mc_total = GetMnvH1D(sb_full.f_mc_fit, sb_full.HistName_Map[kh_Name_MC_fitting]);

    var = sb_full.HistName_Map[kh_Name_MC_fitting] + "_Material_Helium";
    sb_full_empty.MnvH1D_Helium[0] = GetMnvH1D(sb_full.f_mc_fit, var);

    var = sb_full.HistName_Map[kh_Name_MC_fitting] + "_Material_Aluminium";
    sb_full_empty.MnvH1D_Aluminium[0] = GetMnvH1D(sb_full.f_mc_fit, var);

    var = sb_full.HistName_Map[kh_Name_MC_fitting] + "_Material_Lead";
    sb_full_empty.MnvH1D_Lead[0] = GetMnvH1D(sb_full.f_mc_fit, var);

    var = sb_full.HistName_Map[kh_Name_MC_fitting] + "_Material_Carbon";
    sb_full_empty.MnvH1D_Carbon[0] = GetMnvH1D(sb_full.f_mc_fit, var);

    var = sb_full.HistName_Map[kh_Name_MC_fitting] + "_Material_Iron";
    sb_full_empty.MnvH1D_Iron[0] = GetMnvH1D(sb_full.f_mc_fit, var);

    var = sb_full.HistName_Map[kh_Name_MC_fitting] + "_Material_Other";
    sb_full_empty.MnvH1D_Other[0] = GetMnvH1D(sb_full.f_mc_fit, var);
  }
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::Inti_Fit_Xaxis_label(HeliumSideBand &sb, std::string xaxislabel){
  sb.MnvH1D_data->GetXaxis()->SetTitle(xaxislabel.c_str());
  sb.MnvH1D_mc_total->GetXaxis()->SetTitle(xaxislabel.c_str());
  sb.MnvH1D_Helium[0]->GetXaxis()->SetTitle(xaxislabel.c_str());
  sb.MnvH1D_Aluminium[0]->GetXaxis()->SetTitle(xaxislabel.c_str());
  sb.MnvH1D_Carbon[0]->GetXaxis()->SetTitle(xaxislabel.c_str());
  sb.MnvH1D_Iron[0]->GetXaxis()->SetTitle(xaxislabel.c_str());
  sb.MnvH1D_Lead[0]->GetXaxis()->SetTitle(xaxislabel.c_str());
  sb.MnvH1D_Other[0]->GetXaxis()->SetTitle(xaxislabel.c_str());
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::Inti_XSec_Xaxis_label(XSec_Var& xsec_var, std::string xaxislabel){

  xsec_var.MnvH1D_data->GetXaxis()->SetTitle(xaxislabel.c_str());
  xsec_var.MnvH1D_mc_total->GetXaxis()->SetTitle(xaxislabel.c_str());
  xsec_var.MnvH1D_Helium[0]->GetXaxis()->SetTitle(xaxislabel.c_str());
  xsec_var.MnvH1D_Aluminium[0]->GetXaxis()->SetTitle(xaxislabel.c_str());
  xsec_var.MnvH1D_Carbon[0]->GetXaxis()->SetTitle(xaxislabel.c_str());
  xsec_var.MnvH1D_Iron[0]->GetXaxis()->SetTitle(xaxislabel.c_str());
  xsec_var.MnvH1D_Lead[0]->GetXaxis()->SetTitle(xaxislabel.c_str());
  xsec_var.MnvH1D_Other[0]->GetXaxis()->SetTitle(xaxislabel.c_str());
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::Inti_Xaxis_labels(HeliumSideBand &sb,  std::string xaxislabel ){

  Inti_Fit_Xaxis_label(sb, xaxislabel);
  Inti_XSec_Xaxis_label(sb.muon_PT, "P_{T,#mu} [GeV]");
  Inti_XSec_Xaxis_label(sb.muon_PZ, "P_{Z,#mu} [GeV]");
  Inti_XSec_Xaxis_label(sb.muon_theta, "#theta_{#mu} [Deg]");
  Inti_XSec_Xaxis_label(sb.muon_E, "E_{#mu} [GeV]" );
  Inti_XSec_Xaxis_label(sb.Vertex_X,"Vertex X [mm]" );
  Inti_XSec_Xaxis_label(sb.Vertex_Y,"Vertex Y [mm]" );
  Inti_XSec_Xaxis_label(sb.Vertex_Z,"Vertex Z [mm]" );
  Inti_XSec_Xaxis_label(sb.DistancetoEdge, "Distance to Edge [mm]");
  return;
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::initFull_EmptySideBand_XSecHistograms()
{
  initSideBand_XSecHistograms(Helium_Full, Helium_Full_Empty.muon_PT,    "h_Data_MuonPT",   "h_MuonPT");
  initSideBand_XSecHistograms(Helium_Full, Helium_Full_Empty.muon_PZ,    "h_Data_MuonPZ",   "h_MuonPZ");
  initSideBand_XSecHistograms(Helium_Full, Helium_Full_Empty.muon_theta, "h_Data_MuonTheta", "h_MuonTheta");
  initSideBand_XSecHistograms(Helium_Full, Helium_Full_Empty.muon_E,     "h_Data_MuonE",     "h_MuonE");
  initSideBand_XSecHistograms(Helium_Full, Helium_Full_Empty.Vertex_X,   "h_Data_CryoVertex_X", "h_CryoVertex_X");
  initSideBand_XSecHistograms(Helium_Full, Helium_Full_Empty.Vertex_Y,   "h_Data_CryoVertex_Y", "h_CryoVertex_Y");
  initSideBand_XSecHistograms(Helium_Full, Helium_Full_Empty.Vertex_Z,   "h_Data_CryoVertex_Z", "h_CryoVertex_Z");
  initSideBand_XSecHistograms(Helium_Full, Helium_Full_Empty.DistancetoEdge,   "h_Data_Distance_to_InnerTank", "h_Distance_to_InnerTank");
  return;
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::initSideBand_XSecHistograms(HeliumSideBand& sb)
{
      initSideBand_XSecHistograms(sb, sb.muon_PT,    "h_Data_MuonPT",   "h_MuonPT");
      initSideBand_XSecHistograms(sb, sb.muon_PZ,    "h_Data_MuonPZ",   "h_MuonPZ");
      initSideBand_XSecHistograms(sb, sb.muon_theta, "h_Data_MuonTheta", "h_MuonTheta");
      initSideBand_XSecHistograms(sb, sb.muon_E,     "h_Data_MuonE",     "h_MuonE");
      initSideBand_XSecHistograms(sb, sb.Vertex_X,   "h_Data_CryoVertex_X", "h_CryoVertex_X");
      initSideBand_XSecHistograms(sb, sb.Vertex_Y,   "h_Data_CryoVertex_Y", "h_CryoVertex_Y");
      initSideBand_XSecHistograms(sb, sb.Vertex_Z,   "h_Data_CryoVertex_Z", "h_CryoVertex_Z");
      initSideBand_XSecHistograms(sb, sb.DistancetoEdge,  "h_Data_Distance_to_InnerTank", "h_Distance_to_InnerTank");
      return;
  }
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::subtract_Data_total(HeliumSideBand& sb_toSubtract, HeliumSideBand& Empty){
  sb_toSubtract.MnvH1D_data->Add(Empty.MnvH1D_data,-1);
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::subtract_MC_total(HeliumSideBand& sb_toSubtract, HeliumSideBand& Empty){
  sb_toSubtract.MnvH1D_mc_total->Add(Empty.MnvH1D_mc_total,-1);
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::subtract_MC_Material(HeliumSideBand& sb_toSubtract, HeliumSideBand& Empty, int ind){
  sb_toSubtract.MnvH1D_Helium[ind]->Add(Empty.MnvH1D_Helium[ind],-1);
  sb_toSubtract.MnvH1D_Aluminium[ind]->Add(Empty.MnvH1D_Aluminium[ind],-1);
  sb_toSubtract.MnvH1D_Lead[ind]->Add(Empty.MnvH1D_Lead[ind],-1);
  sb_toSubtract.MnvH1D_Carbon[ind]->Add(Empty.MnvH1D_Carbon[ind],-1);
  sb_toSubtract.MnvH1D_Iron[ind]->Add(Empty.MnvH1D_Iron[ind],-1);
  sb_toSubtract.MnvH1D_Other[ind]->Add(Empty.MnvH1D_Other[ind],-1);
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::subtract_XSecHistograms_MCtotal(XSec_Var& xsec_var_Full, XSec_Var& xsec_var_Empty)
{
  xsec_var_Full.MnvH1D_mc_total->Add(xsec_var_Empty.MnvH1D_mc_total,-1.0);
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::subtract_XSecHistograms_datatotal(XSec_Var& xsec_var_Full, XSec_Var& xsec_var_Empty)
{
  xsec_var_Full.MnvH1D_data->Add(xsec_var_Empty.MnvH1D_data,-1.0);
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::subtract_XSecHistograms_MC_Material(XSec_Var& xsec_var_Full,
  XSec_Var& xsec_var_Empty , int ind)
{
  xsec_var_Full.MnvH1D_Helium[ind]->Add(xsec_var_Empty.MnvH1D_Helium[ind],-1);
  xsec_var_Full.MnvH1D_Aluminium[ind]->Add(xsec_var_Empty.MnvH1D_Aluminium[ind],-1);
  xsec_var_Full.MnvH1D_Lead[ind]->Add(xsec_var_Empty.MnvH1D_Lead[ind],-1);
  xsec_var_Full.MnvH1D_Carbon[ind]->Add(xsec_var_Empty.MnvH1D_Carbon[ind],-1);
  xsec_var_Full.MnvH1D_Iron[ind]->Add(xsec_var_Empty.MnvH1D_Iron[ind],-1);
  xsec_var_Full.MnvH1D_Other[ind]->Add(xsec_var_Empty.MnvH1D_Other[ind],-1);
  return;
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::init_subtract_XSecHistograms(XSec_Var& xsec_var_Full, XSec_Var& xsec_var_Empty){

  subtract_XSecHistograms_MCtotal( xsec_var_Full, xsec_var_Empty);
  subtract_XSecHistograms_datatotal(xsec_var_Full, xsec_var_Empty);
  subtract_XSecHistograms_MC_Material(xsec_var_Full, xsec_var_Empty , 0);
  return;
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::init_Hist_Full_minus_Empty(){

  subtract_Data_total(Helium_Full_Empty, Helium_Empty);
  subtract_MC_total(Helium_Full_Empty, Helium_Empty);
  subtract_MC_Material(Helium_Full_Empty, Helium_Empty, 0);

  init_subtract_XSecHistograms(Helium_Full_Empty.muon_PT, Helium_Empty.muon_PT);
  init_subtract_XSecHistograms(Helium_Full_Empty.muon_PZ, Helium_Empty.muon_PZ);
  init_subtract_XSecHistograms(Helium_Full_Empty.muon_theta, Helium_Empty.muon_theta);
  init_subtract_XSecHistograms(Helium_Full_Empty.muon_E, Helium_Empty.muon_E);
  init_subtract_XSecHistograms(Helium_Full_Empty.Vertex_X, Helium_Empty.Vertex_X);
  init_subtract_XSecHistograms(Helium_Full_Empty.Vertex_Y, Helium_Empty.Vertex_Y);
  init_subtract_XSecHistograms(Helium_Full_Empty.Vertex_Z, Helium_Empty.Vertex_Z);
  init_subtract_XSecHistograms(Helium_Full_Empty.DistancetoEdge, Helium_Empty.DistancetoEdge);
  return;
  }
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::GetAllUniverses(MnvH1D* mnvh1d_hist, std::vector<TH1D*> &all_universes, std::vector<std::string> &err_bands, std::vector<int> &hist_ind)
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
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::initSideBand_AllUniverses(HeliumSideBand& sb)
{
      GetAllUniverses(sb.MnvH1D_data,         sb.data_all_universes,      sb.err_bands_data_all_universes,      sb.hist_ind_data_all_universes);
      GetAllUniverses(sb.MnvH1D_mc_total,     sb.mc_total_all_universes,  sb.err_bands_mc_total_all_universes,  sb.hist_ind_mc_total_all_universes);
      GetAllUniverses(sb.MnvH1D_Helium[0],    sb.Helium_all_universes,    sb.err_bands_Helium_all_universes,    sb.hist_ind_Helium_all_universes);
      GetAllUniverses(sb.MnvH1D_Aluminium[0], sb.Aluminium_all_universes, sb.err_bands_Aluminium_all_universes, sb.hist_ind_Aluminium_all_universes);
      GetAllUniverses(sb.MnvH1D_Carbon[0],    sb.Carbon_all_universes,    sb.err_bands_Carbon_all_universes,    sb.hist_ind_Carbon_all_universes);
      GetAllUniverses(sb.MnvH1D_Iron[0],      sb.Iron_all_universes,      sb.err_bands_Iron_all_universes,      sb.hist_ind_Iron_all_universes);
      GetAllUniverses(sb.MnvH1D_Lead[0],      sb.Lead_all_universes,      sb.err_bands_Lead_all_universes,      sb.hist_ind_Lead_all_universes);
      GetAllUniverses(sb.MnvH1D_Other[0],     sb.Other_all_universes,     sb.err_bands_Other_all_universes,     sb.hist_ind_Other_all_universes);

      N_Universes = sb.data_all_universes.size();

      std::cout<<"initSideBand_AllUniverses::N_Universes = "<< N_Universes<<std::endl;
      return;
  }
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
double Helium_SideBandTool::calc_ChiSq(TH1D* data, TH1D* Helium, TH1D* Aluminium, TH1D* Carbon, TH1D* Lead, TH1D* Iron, TH1D* Other)
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
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
double Helium_SideBandTool::calc_ChiSq_SideBand(HeliumSideBand &sb, double POT_ratio, int unv, bool isPartial, int min_bin, int max_bin)
{
      if (!isPartial){
          min_bin = 1;
          max_bin = sb.MnvH1D_data->GetNbinsX();
      }

      if (min_bin == max_bin){
          std::cout<<"Wrong Range for Fit"<<std::endl;
          exit(EXIT_FAILURE);
      }

      double ChiSq = 0.0;

      for (int i = 1; i <= max_bin; ++i) {
          double nData = sb.data_all_universes[unv]->GetBinContent(i);
          if (nData == 0) continue;

          // Do not use Signal and Other in Fit
          double nHelium = sb.Helium_all_universes[unv]->GetBinContent(i) * POT_ratio;
          double nAluminium = sb.Aluminium_all_universes[unv]->GetBinContent(i) * POT_ratio;
          double nCarbon = sb.Carbon_all_universes[unv]->GetBinContent(i) * POT_ratio;
          double nIron = sb.Iron_all_universes[unv]->GetBinContent(i) * POT_ratio;
          double nLead = sb.Lead_all_universes[unv]->GetBinContent(i) * POT_ratio;
          double nOther = sb.Other_all_universes[unv]->GetBinContent(i) * POT_ratio;

          double nTotalMC = nHelium + nAluminium + nCarbon + nIron + nLead + nOther;

          double delta  = std::pow((nData - nTotalMC),2)/nData;
          ChiSq += delta;
      }

      return ChiSq;
  }
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
double Helium_SideBandTool::calc_Global_ChiSq(int unv, double POT_ratio)
{
      double ChiSq = 0;

      // Calculate ChiSq for Michel for ALL Bins
      ChiSq += calc_ChiSq_SideBand(Helium_Empty, POT_ratio, unv);

      return ChiSq;
  }
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::SetNames(HeliumSideBand &sb, std::string name)
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
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::GetStatistics(HeliumSideBand &sb)
{
    //int first_bin = 1; //don't include overflow
    //int last_bin = sb.nData->GetNbinsX() ;
std::cout<<"inside::GetStatistics "<<std::endl;
std::cout<<"sb.data_all_universes.size() = " << sb.data_all_universes.size()<<std::endl;


    for (unsigned int i = 0; i < sb.data_all_universes.size(); ++i){
        sb.nData.push_back(sb.data_all_universes[i]->Integral());//first_bin, last_bin));
        sb.nMC.push_back(sb.mc_total_all_universes[i]->Integral());//first_bin, last_bin));

        sb.nHelium.push_back(sb.Helium_all_universes[i]->Integral());//first_bin, last_bin));
        sb.nAluminium.push_back(sb.Aluminium_all_universes[i]->Integral());//first_bin, last_bin));
        sb.nCarbon.push_back(sb.Carbon_all_universes[i]->Integral());//first_bin, last_bin));
        sb.nIron.push_back(sb.Iron_all_universes[i]->Integral());//first_bin, last_bin));
        sb.nLead.push_back(sb.Lead_all_universes[i]->Integral());//first_bin, last_bin));
        sb.nOther.push_back(sb.Other_all_universes[i]->Integral());//first_bin, last_bin));
    }
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::WriteStatistics(HeliumSideBand &sb)
{
    // Open Text File
    std::string file_name = "EmptyFillResults.txt";
    std::ofstream file;
    file.open(file_name.c_str());

    // Write Header
    file<<std::left;
    file.width(12); file<<"Universe"<<" ";
    file.width(12); file<<"N(Data)"<<" ";
    file.width(12); file<<"N(MC)"<<" ";
    file.width(12); file<<"N(Helium)"<<" ";
    file.width(20); file<<"N(Aluminium)"<<" ";
    file.width(12); file<<"N(Carbon)"<<" ";
    file.width(12); file<<"N(Iron)"<<" ";
    file.width(12); file<<"N(Lead)"<<" ";
    file.width(12); file<<"N(Other)"<<" ";
    file<<std::endl;

    for (unsigned int i = 0; i < sb.nData.size(); ++i){
        file.width(12); file<<i<<" ";
        file.width(12); file<<sb.nData[i]<<" ";
        file.width(12); file<<sb.nMC[i]<<" ";
        file.width(12); file<<sb.nHelium[i]<<" ";
        file.width(20); file<<sb.nAluminium[i]<<" ";
        file.width(12); file<<sb.nCarbon[i]<<" ";
        file.width(12); file<<sb.nIron[i]<<" ";
        file.width(12); file<<sb.nLead[i]<<" ";
        file.width(12); file<<sb.nOther[i]<<" ";
        file<<std::endl;
    }

    std::cout<<"Writing "<<file_name<<std::endl;
    file.close();
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::WriteFitResults(std::string file_name)
{
    std::cout<<"Writing List of Weights for all Universes"<<std::endl;
    // Open Text File
    std::ofstream file;
    file.open(file_name.c_str());

    // Write Header
    file<<std::left;
    file.width(32); file<<"Error Band"<<" ";
    file.width(6);  file<<"Hist"<<" ";
    file.width(20); file<<"ChiSq Before Fit"<<" ";
    file.width(20); file<<"ChiSq After Fit"<<" ";
    file.width(20); file<<"wgt(Aluminium)"<<" ";
    file.width(20); file<<"err(Aluminium)"<<" ";
    file<<std::endl;

    for (unsigned int i = 0; i < ChiSq_after_fit.size(); ++i){
        file.width(32); file<< Helium_Full.err_bands_data_all_universes[i]<<" ";
        file.width(6); file<< Helium_Full.hist_ind_data_all_universes[i]<<" ";
        file.width(20); file<<ChiSq_before_fit[i]<<" ";
        file.width(20); file<<ChiSq_after_fit[i]<<" ";
        file.width(20); file<<wgt_Aluminium[i]<<" ";
        file.width(20); file<<err_Aluminium[i]<<" ";
        file<<std::endl;
    }

    std::cout<<"Writing "<<file_name<<std::endl;
    file.close();
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::ApplyFitResults(HeliumSideBand &sb)
{
    std::cout<<"Applying Fit Result to "<<sb.name<<std::endl;
    // Clone Original Histograms
    sb.MnvH1D_Helium[1] = new MnvH1D (*sb.MnvH1D_Helium[0]);
    sb.MnvH1D_Aluminium[1] = new MnvH1D (*sb.MnvH1D_Aluminium[0]);
    sb.MnvH1D_Carbon[1] = new MnvH1D (*sb.MnvH1D_Carbon[0]);
    sb.MnvH1D_Iron[1] = new MnvH1D (*sb.MnvH1D_Iron[0]);
    sb.MnvH1D_Lead[1] = new MnvH1D (*sb.MnvH1D_Lead[0]);
    sb.MnvH1D_Other[1] = new MnvH1D (*sb.MnvH1D_Other[0]);

    // Scale
    auto Nbins = sb.MnvH1D_Aluminium[1]->GetNbinsX();
    std::cout<<"applying scaler : "<< wgt_Aluminium[0]<< std::endl;
    std::cout<<"Checking bins  = " << Nbins<<std::endl;
    sb.MnvH1D_Aluminium[1]->Scale(wgt_Aluminium[0]);


    // Cross Section Variables
    ApplyFitResults(sb.muon_PT);
    ApplyFitResults(sb.muon_PZ);
    ApplyFitResults(sb.muon_theta);
    ApplyFitResults(sb.muon_E);
    ApplyFitResults(sb.Vertex_X);
    ApplyFitResults(sb.Vertex_Y);
    ApplyFitResults(sb.Vertex_Z);
    ApplyFitResults(sb.DistancetoEdge);

}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::ApplyFitResults(XSec_Var &xsec_var)
{
    // Clone Original Histograms
    xsec_var.MnvH1D_Helium[1] = new MnvH1D (*xsec_var.MnvH1D_Helium[0]);
    xsec_var.MnvH1D_Aluminium[1] = new MnvH1D (*xsec_var.MnvH1D_Aluminium[0]);
    xsec_var.MnvH1D_Carbon[1] = new MnvH1D (*xsec_var.MnvH1D_Carbon[0]);
    xsec_var.MnvH1D_Lead[1] = new MnvH1D (*xsec_var.MnvH1D_Lead[0]);
    xsec_var.MnvH1D_Iron[1] = new MnvH1D (*xsec_var.MnvH1D_Iron[0]);
    xsec_var.MnvH1D_Other[1] = new MnvH1D (*xsec_var.MnvH1D_Other[0]);

    // Scale
    xsec_var.MnvH1D_Aluminium[1]->Scale(wgt_Aluminium[0]);
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::ApplyFitResults_Int_Full_Empty(XSec_Var &xsec_var_Full_Empty, XSec_Var &xsec_var_Full, XSec_Var &xsec_var_Empty)
{
    // Clone Original Histograms
    xsec_var_Full_Empty.MnvH1D_Helium[1] = new MnvH1D (*xsec_var_Full.MnvH1D_Helium[0]);
    xsec_var_Full_Empty.MnvH1D_Aluminium[1] = new MnvH1D (*xsec_var_Full.MnvH1D_Aluminium[0]);
    xsec_var_Full_Empty.MnvH1D_Carbon[1] = new MnvH1D (*xsec_var_Full.MnvH1D_Carbon[0]);
    xsec_var_Full_Empty.MnvH1D_Lead[1] = new MnvH1D (*xsec_var_Full.MnvH1D_Lead[0]);
    xsec_var_Full_Empty.MnvH1D_Iron[1] = new MnvH1D (*xsec_var_Full.MnvH1D_Iron[0]);
    xsec_var_Full_Empty.MnvH1D_Other[1] = new MnvH1D (*xsec_var_Full.MnvH1D_Other[0]);

    // Scale

    xsec_var_Full_Empty.MnvH1D_Helium[1]->Add(xsec_var_Empty.MnvH1D_Helium[1],-1.0) ;
    xsec_var_Full_Empty.MnvH1D_Aluminium[1]->Add(xsec_var_Empty.MnvH1D_Aluminium[1],-1.0) ;
    xsec_var_Full_Empty.MnvH1D_Carbon[1]->Add(xsec_var_Empty.MnvH1D_Carbon[1],-1.0) ;
    xsec_var_Full_Empty.MnvH1D_Lead[1]->Add(xsec_var_Empty.MnvH1D_Lead[1],-1.0) ;
    xsec_var_Full_Empty.MnvH1D_Iron[1]->Add(xsec_var_Empty.MnvH1D_Iron[1],-1.0) ;
    xsec_var_Full_Empty.MnvH1D_Other[1]->Add(xsec_var_Empty.MnvH1D_Other[1],-1.0) ;
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::ApplyFitResults(HeliumSideBand &sb_Full_Empty, HeliumSideBand &sb_Full, HeliumSideBand &sb_Empty )
{
    std::cout<<"Applying Fit Result to contructed Full - Empty Hists "<<sb_Full_Empty.name<<std::endl;
    // Clone Original Histograms
    sb_Full_Empty.MnvH1D_Helium[1] = new MnvH1D (*sb_Full.MnvH1D_Helium[1]);
    sb_Full_Empty.MnvH1D_Aluminium[1] = new MnvH1D (*sb_Full.MnvH1D_Aluminium[1]);
    sb_Full_Empty.MnvH1D_Carbon[1] = new MnvH1D (*sb_Full.MnvH1D_Carbon[1]);
    sb_Full_Empty.MnvH1D_Iron[1] = new MnvH1D (*sb_Full.MnvH1D_Iron[1]);
    sb_Full_Empty.MnvH1D_Lead[1] = new MnvH1D (*sb_Full.MnvH1D_Lead[1]);
    sb_Full_Empty.MnvH1D_Other[1] = new MnvH1D (*sb_Full.MnvH1D_Other[1]);

    // Scale
    sb_Full_Empty.MnvH1D_Helium[1]->Add(sb_Empty.MnvH1D_Helium[1],-1.0);
    sb_Full_Empty.MnvH1D_Aluminium[1]->Add(sb_Empty.MnvH1D_Aluminium[1],-1.0);
    sb_Full_Empty.MnvH1D_Carbon[1]->Add(sb_Empty.MnvH1D_Carbon[1],-1.0);
    sb_Full_Empty.MnvH1D_Iron[1]->Add(sb_Empty.MnvH1D_Iron[1],-1.0);
    sb_Full_Empty.MnvH1D_Lead[1]->Add(sb_Empty.MnvH1D_Lead[1],-1.0);
    sb_Full_Empty.MnvH1D_Other[1]->Add(sb_Empty.MnvH1D_Other[1],-1.0);

    // Cross Section Variables
    ApplyFitResults_Int_Full_Empty(sb_Full_Empty.muon_PT,sb_Full.muon_PT,sb_Empty.muon_PT);
    ApplyFitResults_Int_Full_Empty(sb_Full_Empty.muon_PZ,sb_Full.muon_PZ,sb_Empty.muon_PZ);
    ApplyFitResults_Int_Full_Empty(sb_Full_Empty.muon_theta,sb_Full.muon_theta,sb_Empty.muon_theta);
    ApplyFitResults_Int_Full_Empty(sb_Full_Empty.muon_E,sb_Full.muon_E,sb_Empty.muon_E);
    ApplyFitResults_Int_Full_Empty(sb_Full_Empty.Vertex_X,sb_Full.Vertex_X,sb_Empty.Vertex_X);
    ApplyFitResults_Int_Full_Empty(sb_Full_Empty.Vertex_Y,sb_Full.Vertex_Y,sb_Empty.Vertex_Y);
    ApplyFitResults_Int_Full_Empty(sb_Full_Empty.Vertex_Z,sb_Full.Vertex_Z,sb_Empty.Vertex_Z);
    ApplyFitResults_Int_Full_Empty(sb_Full_Empty.DistancetoEdge,sb_Full.DistancetoEdge,sb_Empty.DistancetoEdge);

}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::ApplyFitResults()
{
  ApplyFitResults(Helium_Empty);
  ApplyFitResults(Helium_Full);
  ApplyFitResults(Helium_Full_Empty, Helium_Full, Helium_Empty);
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::WriteStatistics()
{
    WriteStatistics(Helium_Full);
    WriteStatistics(Helium_Empty);
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::SaveFitResults(double chisq, double par_values[1], double par_errors[1])
{
  std::cout<< "inside Helium_SideBandTool::SaveFitResults | chisq =  "<< chisq << " | par_values[1] =  "<< par_values[0] << " | par_errors[1] =  " << par_errors[0]<<std::endl;

    ChiSq_after_fit.push_back(chisq);
    wgt_Aluminium.push_back(par_values[0]);
    err_Aluminium.push_back(par_errors[0]);

}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
Helium_SideBandTool::~Helium_SideBandTool()
{

}
////////////////////////////////////////////////////////////
///Plotting
/////////////////////////////////////////////////////////////
void Helium_SideBandTool::DrawDataMCWithErrorBand(HeliumSideBand &sb, int toprint, double POT_ratio , std::string pdf_label, MnvPlotter* plotter, TCanvas* c, std::string Hist_title )
{
    // Get Histograms -- Use new Histograms not to change originals
    MnvH1D* h_data = new MnvH1D(*(sb.MnvH1D_data));
    MnvH1D* h_mc_total = new MnvH1D(*(sb.MnvH1D_mc_total));

    double mc_ratio = POT_ratio;

     //MnvPlotter* plotter= new MnvPlotter();
     //= new TCanvas("c","c",1280,1280);

    //plotter->DrawErrorSummary(h_mc_total);
    plotter->DrawDataMCWithErrorBand(h_data, h_mc_total, mc_ratio, "TR", false, NULL, NULL,false,true);

    MnvH1D* h_Helium = new MnvH1D(*(sb.MnvH1D_Helium[toprint]));
    MnvH1D* h_Aluminium = new MnvH1D(*(sb.MnvH1D_Aluminium[toprint]));
    MnvH1D* h_Carbon = new MnvH1D(*(sb.MnvH1D_Carbon[toprint]));
    MnvH1D* h_Iron = new MnvH1D(*(sb.MnvH1D_Iron[toprint]));
    MnvH1D* h_Lead = new MnvH1D(*(sb.MnvH1D_Lead[toprint]));
    MnvH1D* h_Other = new MnvH1D(*(sb.MnvH1D_Other[toprint]));

    MnvH1D* h_mc_total2 = new MnvH1D(*h_Helium);
    h_mc_total2->Add(h_Aluminium);
    h_mc_total2->Add(h_Carbon);
    h_mc_total2->Add(h_Iron);
    h_mc_total2->Add(h_Lead);
    h_mc_total2->Add(h_Other);

    double norm_bin_width = h_mc_total2->GetNormBinWidth();
    h_mc_total2->Scale(mc_ratio);
    h_mc_total2->Scale(norm_bin_width,"width");
    h_mc_total2->SetLineWidth(3);
    h_mc_total2->SetLineColor(kBlue);
    h_mc_total2->SetFillColor(kWhite);

    h_mc_total2->Draw("HIST SAME");

    // Plot Output

    plotter->AddHistoTitle(Hist_title.c_str(),.04);
    plotter->WritePreliminary("TL", .025, 0, 0, false);
    c->Print(pdf_label.c_str(),"pdf");

    delete h_data;
    delete h_mc_total;
    delete c;
    delete plotter;
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::Plot(std::string pdf_label, int ind, double POT_ratio, std::string sb_name,
   std::string var_name, MnvH1D* data, MnvH1D* mc_total, MnvH1D* Helium, MnvH1D* Aluminium, MnvH1D* Carbon,
    MnvH1D* Iron, MnvH1D* Lead, MnvH1D* Other, std::string Hist_title, std::string xaxislabel, int index)
{

    std::string type;
    if (ind == 0) type = "Nominal";
    else type = "Fitted";
    std::cout<<"Ploting type:  "<< type<<std::endl;

    std::string norm = "POT";
    std::string plot_title = "Side Band: " + sb_name + " " + type + " " + norm + " Normalized";
    //PlotUtils::MnvPlotter* plotter= new mnvPlotter();
     MnvPlotter* plotter = new MnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
    //plotter(PlotUtils::kCCInclusiveHeliumStyle);
    TH1D* h_data = new TH1D(data->GetBinNormalizedCopy().GetCVHistoWithError());
    TH1D* h_Helium = new TH1D(Helium->GetBinNormalizedCopy().GetCVHistoWithError());
    TH1D* h_Aluminium = new TH1D(Aluminium->GetBinNormalizedCopy().GetCVHistoWithError());
    TH1D* h_Carbon = new TH1D(Carbon->GetBinNormalizedCopy().GetCVHistoWithError());
    TH1D* h_Iron = new TH1D(Iron->GetBinNormalizedCopy().GetCVHistoWithError());
    TH1D* h_Lead = new TH1D(Lead->GetBinNormalizedCopy().GetCVHistoWithError());
    TH1D* h_Other = new TH1D(Other->GetBinNormalizedCopy().GetCVHistoWithError());

    ColorHists(h_data, h_Helium, h_Aluminium, h_Carbon, h_Iron,h_Lead,  h_Other);
    // MC Total depend on the Modification
    //      If Raws - take the mc_total directly
    //      If Modified - Add all mc models;
    TH1D* h_mc_total;
    if (ind == 0){
        h_mc_total = new TH1D(mc_total->GetBinNormalizedCopy().GetCVHistoWithError());
    }else{
        h_mc_total = new TH1D(*h_Helium);
        h_mc_total->Add(h_Aluminium);
        h_mc_total->Add(h_Carbon);
        h_mc_total->Add(h_Iron);
        h_mc_total->Add(h_Lead);
        h_mc_total->Add(h_Other);
    }

    // Scale Histograms
    double mc_ratio = POT_ratio;
    //h_mc_total->Scale(mc_ratio);
    //h_Helium->Scale(mc_ratio);
    //h_Aluminium->Scale(mc_ratio);
    //h_Carbon->Scale(mc_ratio);
    //h_Iron->Scale(mc_ratio);
    //h_Lead->Scale(mc_ratio);
    //h_Other->Scale(mc_ratio);

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
      std::cout<< "yaxis = "<< yaxis<<std::endl;
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

    std::cout<<"Finished adding hist to hs"<<std::endl;

    // Styling
    hs->Draw("HIST");
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
    hs->SetMaximum(hist_max * 1.85);



    //std::cout<<"Finshed Drawing Hist "<<std::endl;

    // Add Data Plot
    //h_data->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
    h_data->Draw("SAME E1 X0");

    std::cout<<"FInished Drawing h_data"<<std::endl;

    // Add Legend
    TLegend *legend = new TLegend(0.6,0.65,0.9,0.9);
    legend->AddEntry(h_data, "Data");
    legend->AddEntry(h_Helium,    "Signal Helium", "f");
    legend->AddEntry(h_Aluminium, "Bckg Aluminium: ", "f");
    legend->AddEntry(h_Carbon,    "Bckg Carbon: ", "f");
    legend->AddEntry(h_Iron,      "Bckg Iron: ", "f");
    legend->AddEntry(h_Lead,      "Bckg Lead: ", "f");
    legend->AddEntry(h_Other,     "Bckg Other: ", "f");
    legend->SetTextSize(0.04);
    legend->SetTextFont(42);
    legend->Draw();
    std::cout<<"FInished Drawing legend"<<std::endl;

    // Add Weights as Text to Modified Plot
    int nPoints = h_data->GetNbinsX()-1;

    std::cout<<"nPoints = "<<nPoints<< std::endl;

    // Add Plot-ChiSq
    TLatex* text = new TLatex;
    text->SetNDC();
    text->SetTextSize(0.04);
    text->SetTextColor(kBlue);
    //double plot_chisq = calc_ChiSq(data, signal, WithPi0, QELike, SinglePiPlus, Other);
    double plot_chisq = calc_ChiSq(h_data, h_Helium, h_Aluminium, h_Carbon, h_Lead, h_Iron, h_Other);
    if (ind == 0){ChiSq_before_fit_var.push_back(plot_chisq);}

    if (ind != 0){
        int nPars = 1;
        //int nPoints = 136;
        //ChiSq_after_fit[0] = plot_chisq;
        //ChiSq_before_fit[0]= 17.65;
        std::cout<<"making Fit info" <<  std::endl;
        //std::cout<<"ChiSq_before_fit[0] = "<< ChiSq_before_fit[0]<<std::endl;
          std::cout<<"ChiSq_after_fit[0] = "<< plot_chisq<<std::endl;
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

    text->DrawLatex(0.2, 0.83, Form("Plot #chi^{2} = %3.2f", plot_chisq));
    text->DrawLatex(0.2, 0.78, Form("Plot #chi^{2}/dof = %3.2f", plot_chisq / (double) nPoints));
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
    TH1D* h_data_mc_ratio = new TH1D(*(h_data));
    //h_data_mc_ratio->Divide(h_mc_total);

    // Style Ratio Plot
    //h_data_mc_ratio->SetTitle("");
    h_data_mc_ratio->SetLineColor(kRed);
    //h_data_mc_ratio->SetLineWidth(3);
    //h_data_mc_ratio->SetFillColor(kWhite);
    h_data_mc_ratio->SetMinimum(0.5);
    h_data_mc_ratio->SetMaximum(2.5);

    // X axis ratio plot settings
    //h_data_mc_ratio->GetXaxis()->SetTitle(data->GetXaxis()->GetTitle());
    //h_data_mc_ratio->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
    //h_data_mc_ratio->GetXaxis()->SetNdivisions(408);
    //h_data_mc_ratio->GetXaxis()->CenterTitle();
    //h_data_mc_ratio->GetXaxis()->SetTitleFont(62);
    //h_data_mc_ratio->GetXaxis()->SetTitleSize(0.18);
    //h_data_mc_ratio->GetXaxis()->SetTitleOffset(1.2);
    //h_data_mc_ratio->GetXaxis()->SetLabelFont(42); // Absolute font size in pixel (precision 3)
    //h_data_mc_ratio->GetXaxis()->SetLabelSize(0.12);

    // Y axis ratio plot settings
    h_data_mc_ratio->GetYaxis()->CenterTitle();
    h_data_mc_ratio->GetYaxis()->SetNdivisions(408);
    h_data_mc_ratio->GetYaxis()->SetTitle("Data/MC");
    h_data_mc_ratio->GetYaxis()->SetTitleFont(62);
    h_data_mc_ratio->GetYaxis()->SetTitleSize(0.18);
    h_data_mc_ratio->GetYaxis()->SetTitleOffset(0.35);
    h_data_mc_ratio->GetYaxis()->SetLabelFont(42); // Absolute font size in pixel (precision 3)
    //h_data_mc_ratio->GetYaxis()->SetLabelSize(0.12);
    h_data_mc_ratio->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
    // Add Ratio Plot
    //h_data_mc_ratio->Draw("HIST");
    plotter->axis_title_size_x = 0.1;
    //plotter->axis_title_offset_y = .35;
    plotter->axis_title_size_y = 0.12;
    plotter->axis_label_size = 0.12;
    plotter->axis_maximum = 2.5;
    plotter->axis_minimum = .5;
    plotter->DrawDataMCRatio(h_data_mc_ratio, h_mc_total);
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
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::Plot(std::string pdf_label, double POT_ratio, int ind,
  HeliumSideBand &sb, XSec_Var &xsec_var,  std::string var_name, std::string Hist_title, std::string xaxislabel, int index)
{
    Plot(pdf_label, ind, POT_ratio, sb.name, var_name,
                xsec_var.MnvH1D_data,
                xsec_var.MnvH1D_mc_total,
                xsec_var.MnvH1D_Helium[ind],
                xsec_var.MnvH1D_Aluminium[ind],
                xsec_var.MnvH1D_Carbon[ind],
                xsec_var.MnvH1D_Lead[ind],
                xsec_var.MnvH1D_Iron[ind],
                xsec_var.MnvH1D_Other[ind], Hist_title, xaxislabel, index);
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::Plot(HeliumSideBand &sb, double POT_ratio,
   std::string fitName, std::string pdf_label, std::string Hist_title, std::string xaxislabel)
{
    std::cout<<"Plotting "<<sb.name<<std::endl;

    // Fit Results

    Plot(sb, 1, POT_ratio , fitName, pdf_label, Hist_title, xaxislabel); // Modified

}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::Plot(HeliumSideBand &sb, int ind, double POT_ratio,
   std::string fitName, std::string pdf_label, std::string Hist_title, std::string xaxislabel, int index)
{
    //Plot_NoRatio(ind, sb.name, "pi0_InvMass",
    Plot(pdf_label, ind,POT_ratio, sb.name, fitName,
                sb.MnvH1D_data,
                sb.MnvH1D_mc_total,
                sb.MnvH1D_Helium[ind],
                sb.MnvH1D_Aluminium[ind],
                sb.MnvH1D_Carbon[ind],
                sb.MnvH1D_Iron[ind],
                sb.MnvH1D_Lead[ind],
                sb.MnvH1D_Other[ind], Hist_title, xaxislabel, index);
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::POTScale_SideBand_MC_total(HeliumSideBand &sb){
  if( sb.POT_MC == 9999  ){
    sb.POT_MC = 1.0;
  }
  sb.MnvH1D_mc_total->Scale(sb.POT_MC);
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::POTScale_SideBand_MC_Material(HeliumSideBand &sb, int ind ){
  if( sb.POT_MC == 9999  ){
    std::cout<<"POTScale_SideBand_MC_Material::POT Hasn't been set: returing and set values to 1.0 "<<std::endl;
    sb.POT_MC = 1.0;
  }
  sb.MnvH1D_Helium[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Aluminium[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Carbon[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Lead[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Iron[ind]->Scale(sb.POT_MC);
  sb.MnvH1D_Other[ind]->Scale(sb.POT_MC);

}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::POTScale_SideBand_Data(HeliumSideBand &sb){
  sb.MnvH1D_data->Scale(sb.POT_Data);
}

void Helium_SideBandTool::POTScale_Var_MC_total(XSec_Var &xsec_var, double POTscaler){
std::cout<<"Inside::POTScale_Var_MC_total- Scaling MnvH1D_mc_total "<<std::endl;
xsec_var.MnvH1D_mc_total->Scale( POTscaler);
std::cout<<"Finshed Scaling MC Total Var"<<std::endl;

}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::POTScale_Var_Data(XSec_Var &xsec_var, double POTscaler){
  xsec_var.MnvH1D_data->Scale( POTscaler);
  std::cout<<"Finshed Scaling data Var"<<std::endl;
}

/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::POTScale_Var_MC_Material(XSec_Var &xsec_var, double POTscaler, int ind){
  xsec_var.MnvH1D_Helium[ind]->Scale( POTscaler);
  xsec_var.MnvH1D_Aluminium[ind]->Scale( POTscaler);
  xsec_var.MnvH1D_Carbon[ind]->Scale( POTscaler);
  xsec_var.MnvH1D_Lead[ind]->Scale( POTscaler);
  xsec_var.MnvH1D_Iron[ind]->Scale( POTscaler);
  xsec_var.MnvH1D_Other[ind]->Scale( POTscaler);
    std::cout<<"Finshed Scaling MC material Var"<<std::endl;
}

/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::init_POTScale_Var(XSec_Var &xsec_var, double POTscaler_MC, double Potscaler_data){
  std::cout<<"inside::init_POTScale_Var"<<std::endl;

  POTScale_Var_MC_total(xsec_var, POTscaler_MC);
  POTScale_Var_MC_Material(xsec_var, POTscaler_MC, 0);
  POTScale_Var_Data(xsec_var,Potscaler_data);

}

/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////

void Helium_SideBandTool::init_POTScale_SideBand(HeliumSideBand &sb){
std::cout<<"inside::init_POTScale_SideBand"<<std::endl;
  POTScale_SideBand_MC_total(sb);
  POTScale_SideBand_MC_Material(sb, 0 );
  POTScale_SideBand_Data(sb);

std::cout<<"Scaling vars" <<std::endl;

  init_POTScale_Var(sb.muon_PT, sb.POT_MC ,sb.POT_Data );
  init_POTScale_Var(sb.muon_PZ, sb.POT_MC ,sb.POT_Data );
  init_POTScale_Var(sb.muon_theta, sb.POT_MC ,sb.POT_Data );
  init_POTScale_Var(sb.muon_E, sb.POT_MC ,sb.POT_Data );
  init_POTScale_Var(sb.Vertex_X, sb.POT_MC ,sb.POT_Data );
  init_POTScale_Var(sb.Vertex_Y, sb.POT_MC ,sb.POT_Data );
  init_POTScale_Var(sb.Vertex_Z, sb.POT_MC ,sb.POT_Data );
  init_POTScale_Var(sb.DistancetoEdge, sb.POT_MC ,sb.POT_Data );

}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////

void Helium_SideBandTool::init_POTScale_Full(){
  init_POTScale_SideBand(Helium_Full);
  return;
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::init_POTScale_Empty(){
  init_POTScale_SideBand(Helium_Empty);
  return;
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::init_POTScale_Full_Empty(){
  init_POTScale_SideBand(Helium_Full_Empty);
  return;
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::init_POTScale_AllHist(){
  std::cout<<"Scalling all Init Hist"<<std::endl;
init_POTScale_Full();
init_POTScale_Empty();
init_POTScale_Full_Empty();
return;
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Helium_SideBandTool::ColorHists(TH1D* data, TH1D* Helium, TH1D* Aluminium, TH1D* Carbon, TH1D* Iron, TH1D* Lead,  TH1D* Other)
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
    return;
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
