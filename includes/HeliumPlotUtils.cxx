////////////////////////////////////////////////////
//File: HeliumPlotUtils.cxx
//Brief: Helium Analysis Plotting functionality
//Author: Christian Nguyen christian2nguyen@ufl.edu
////////////////////////////////////////////////////
#include "HeliumPlotUtils.h"
#include "TRandom.h"
////////////////////////////////////////////////////
//////These Functions are
//////
////////////////////////////////////////////////////

std::vector<int> HeliumColors = {
  TColor::GetColor("#F1B6DA"),//pink 11

  TColor::GetColor("#DF00FF"), //'psychedelic Purple1
  TColor::GetColor(43,206,72 ), //green 2
  TColor::GetColor("#87CEEB"),//'skyblue' 3
  TColor::GetColor("#0859C6"), //blue 4
  TColor::GetColor("#654522"), // yellowishbrown,5
  TColor::GetColor("#ffc922"), //'sunset yellow'6
  TColor::GetColor("#FF0800"),//2 candy Apple7
  TColor::GetColor("#800000"),  // Maroon
  TColor::GetColor("#90AD1C"),//8
  TColor::GetColor("#BABABA"), //Gray 9
  TColor::GetColor("#00FFFF"),//'aqua' 10
  TColor::GetColor("#AAF0D1"), // mint green
  TColor::GetColor(kRed),//'Jade' 12
  TColor::GetColor("#FAFAD2"),  // LightGoldenRodYellow 13

  TColor::GetColor("#555555"),  // dark grey 15
  TColor::GetColor(0, 153, 143 ), //turquoise 16
  TColor::GetColor("#654522"), // yellowishbrown, 17
  TColor::GetColor("#8db600"), // yellowgreen, 18
  TColor::GetColor("#D3D3D3"),  //'lightgrey' 19
  TColor::GetColor("#90AD1C"), // 20
  TColor::GetColor("#CCDDAA"), //21
  TColor::GetColor(kMagenta), //22
  TColor::GetColor("#EEFF00") // neonyellow,0
};
/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////
std::string replaceAll(std::string source, const char toReplace, const std::string& with)
{
  for(size_t found = source.find(toReplace); found != std::string::npos; found = source.find(toReplace))
  {
    source.replace(found, 1, with);
  }
  return source;
}
/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////

void SetHist(PlotUtils::MnvH1D* hist, char *xaxislabel , char *yaxislabel){

  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->CenterTitle();
  hist->GetXaxis()->SetTitle(xaxislabel);
  hist->GetYaxis()->SetTitle(yaxislabel);
  hist->GetXaxis()->SetTitleSize(0.038);
  hist->GetYaxis()->SetTitleSize(0.038);
  hist->SetLineColor(kBlue);
  hist->SetLineWidth(5);
  hist->SetMaximum(hist->GetMaximum() * 1.25);
}

/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////

void SetHist(TH1F * hist, char *xaxislabel , char *yaxislabel){

  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->CenterTitle();
  hist->GetXaxis()->SetTitle(xaxislabel);
  hist->GetYaxis()->SetTitle(yaxislabel);
  hist->GetXaxis()->SetTitleSize(0.038);
  hist->GetYaxis()->SetTitleSize(0.038);
  hist->SetMaximum(hist->GetMaximum() * 1.25);
}

/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////

void SetHist_Data(PlotUtils::MnvH1D &hist, char *xaxislabel , char *yaxislabel){

  hist.GetXaxis()->CenterTitle();
  hist.GetYaxis()->CenterTitle();
  hist.GetXaxis()->SetTitle(xaxislabel);
  hist.GetYaxis()->SetTitle(yaxislabel);
  hist.GetXaxis()->SetTitleSize(0.038);
  hist.GetYaxis()->SetTitleSize(0.038);
  //hist->SetMaximum(hist->GetMaximum() * 1.25);
}

/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////

void SetMaxforDraw(PlotUtils::MnvH1D* hist_to_Draw,PlotUtils::MnvH1D* hist){

if(hist_to_Draw->GetMaximum() > hist->GetMaximum() ){
 hist_to_Draw->SetMaximum(hist_to_Draw->GetMaximum() * 1.25);
 hist->SetMaximum(hist_to_Draw->GetMaximum() * 1.25);
}
else {
hist_to_Draw->SetMaximum(hist->GetMaximum() * 1.25);
hist->SetMaximum(hist->GetMaximum() * 1.25);
}

}//end of function

/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////

void SetMaxforDraw(PlotUtils::MnvH1D* hist_to_Draw, PlotUtils::MnvH1D* hist,PlotUtils::MnvH1D* hist3  ){

if(hist_to_Draw->GetMaximum() > hist->GetMaximum() && hist_to_Draw->GetMaximum() > hist3->GetMaximum() ){
 hist_to_Draw->SetMaximum(hist_to_Draw->GetMaximum() * 1.35);}
else if (hist_to_Draw->GetMaximum() > hist->GetMaximum() && hist_to_Draw->GetMaximum() < hist3->GetMaximum()) {hist_to_Draw->SetMaximum(hist3->GetMaximum() * 1.35);}
else if (hist_to_Draw->GetMaximum() < hist->GetMaximum() && hist->GetMaximum() > hist3->GetMaximum()) {hist_to_Draw->SetMaximum(hist->GetMaximum() * 1.35);}

}//end of function

/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////


void PlotTotalError(PlotUtils::MnvH1D* hist, std::string method_str ){
  TH1D *hTotalErr = (TH1D*)hist->GetTotalError( include_stat_error, do_fractional_uncertainty, do_cov_area_norm ).Clone( Form("h_total_err_errSum_%d", __LINE__) );
  TCanvas cF ("c4","c4");
  hTotalErr->SetTitle(Form("Total Uncertainty (%s);", method_str.c_str()));
  hTotalErr->Draw();
  cF.Print(Form("Enu_TotalUncertainty_%s_%s_%s.pdf", do_fractional_uncertainty_str.c_str(), do_cov_area_norm_str.c_str(), method_str.c_str()));
}

/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////

void PlotErrorSummary(PlotUtils::MnvH1D* hist, std::string pdf, std::string title, std::string xaxis, TCanvas *cE){
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCompactStyle);
  //TCanvas cE ("c1","c1");
  //DecodePosition (const std::string &opts, double size, int &align, double &xLabel, double &yLabel)
  mnvPlotter.legend_n_columns = 2;
  //char* title_his = strcpy(new char[title.length() + 1], title.c_str());

  hist->GetXaxis()->SetTitle(xaxis.c_str());
	//mnvPlotter.AddHistoTitle (title_his);
  hist->SetTitle(Form("Error Summary(%s)", title.c_str()));

  mnvPlotter.error_summary_group_map.clear();
  mnvPlotter.error_summary_group_map["Genie_FSI"].push_back("genie_FrAbs_N");
  mnvPlotter.error_summary_group_map["Genie_FSI"].push_back("genie_FrAbs_pi");
  mnvPlotter.error_summary_group_map["Genie_FSI"].push_back("genie_FrCEx_N");
  mnvPlotter.error_summary_group_map["Genie_FSI"].push_back("genie_FrCEx_pi");
  //mnvPlotter.error_summary_group_map["Genie_FSI"].push_back("genie_FrElas_N");
  mnvPlotter.error_summary_group_map["Genie_FSI"].push_back("genie_FrElas_pi");
  mnvPlotter.error_summary_group_map["Genie_FSI"].push_back("genie_FrInel_N");
  mnvPlotter.error_summary_group_map["Genie_FSI"].push_back("genie_FrInel_pi");
  mnvPlotter.error_summary_group_map["Genie_FSI"].push_back("genie_FrPiProd_N");
  mnvPlotter.error_summary_group_map["Genie_FSI"].push_back("genie_FrPiProd_pi");
  mnvPlotter.error_summary_group_map["Genie_FSI"].push_back("genie_MFP_N");
  mnvPlotter.error_summary_group_map["Genie_FSI"].push_back("genie_MFP_pi");
  mnvPlotter.error_summary_group_map["Genie_InteractionModel"].push_back("genie_AGKYxF1pi");
  mnvPlotter.error_summary_group_map["Genie_InteractionModel"].push_back("genie_AhtBY");
  mnvPlotter.error_summary_group_map["Genie_InteractionModel"].push_back("genie_BhtBY");
  mnvPlotter.error_summary_group_map["Genie_InteractionModel"].push_back("genie_CCQEPauliSupViaKF");
  mnvPlotter.error_summary_group_map["Genie_InteractionModel"].push_back("genie_CV1uBY");
  mnvPlotter.error_summary_group_map["Genie_InteractionModel"].push_back("genie_CV2uBY");
  mnvPlotter.error_summary_group_map["Genie_InteractionModel"].push_back("genie_EtaNCEL");
  mnvPlotter.error_summary_group_map["Genie_InteractionModel"].push_back("genie_MaCCQE");
  mnvPlotter.error_summary_group_map["Genie_InteractionModel"].push_back("genie_MaCCQEshape");
  mnvPlotter.error_summary_group_map["Genie_InteractionModel"].push_back("genie_MaNCEL");
  mnvPlotter.error_summary_group_map["Genie_InteractionModel"].push_back("genie_MaRES");
  mnvPlotter.error_summary_group_map["Genie_InteractionModel"].push_back("genie_MvRES");
  mnvPlotter.error_summary_group_map["Genie_InteractionModel"].push_back("genie_NormCCQE");
  mnvPlotter.error_summary_group_map["Genie_InteractionModel"].push_back("genie_NormCCRES");
  mnvPlotter.error_summary_group_map["Genie_InteractionModel"].push_back("genie_NormDISCC");
  mnvPlotter.error_summary_group_map["Genie_InteractionModel"].push_back("genie_NormNCRES");
  mnvPlotter.error_summary_group_map["Genie_InteractionModel"].push_back("genie_RDecBR1gamma");
  mnvPlotter.error_summary_group_map["Genie_InteractionModel"].push_back("genie_Rvn1pi");
  mnvPlotter.error_summary_group_map["Genie_InteractionModel"].push_back("genie_Rvn2pi");
  mnvPlotter.error_summary_group_map["Genie_InteractionModel"].push_back("genie_Rvn3pi");
  mnvPlotter.error_summary_group_map["Genie_InteractionModel"].push_back("genie_Rvp1pi");
  mnvPlotter.error_summary_group_map["Genie_InteractionModel"].push_back("genie_Rvp2pi");
  mnvPlotter.error_summary_group_map["Genie_InteractionModel"].push_back("genie_Theta_Delta2Npi");
  mnvPlotter.error_summary_group_map["Genie_InteractionModel"].push_back("genie_VecFFCCQEshape");

  auto names = hist->GetErrorBandNames();
  for(auto cat : names){
    std::cout<< " name of Error Band Names= "<< cat <<std::endl;
  }


  mnvPlotter.DrawErrorSummary(hist,"TR",include_stat_error,true,0.0, do_cov_area_norm, "",do_fractional_uncertainty);
  mnvPlotter.WritePreliminary("TR", .03, 0, 0, false);
  mnvPlotter.AddHistoTitle(Form("Error Summary (%s)", title.c_str()), .04);

  //std::string plotname = Form("Enu_CV_w_err_%s",label.c_str());
  mnvPlotter.MultiPrint(cE, pdf, "pdf");

  //mnvPlotter.error_summary_group_map.clear();
  //mnvPlotter.error_summary_group_map = ::errorGroups;


  for(const auto& cat: mnvPlotter.error_summary_group_map)
  {cE->Clear();
     std::cout<< "cat.first = "<< cat.first<<std::endl;
     cE->SetTitle(cat.first.c_str());
     char ErrorTitle[1024];
     mnvPlotter.DrawErrorSummary( hist, "TR", true, true, .00001, false , cat.first , true, "" , false);
     sprintf(ErrorTitle, "(%s) Error Group %s", title.c_str(), cat.first.c_str());
     mnvPlotter.AddHistoTitle(ErrorTitle,.04);
     mnvPlotter.WritePreliminary("TR", .03, 0, 0, false);
     mnvPlotter.MultiPrint(cE, pdf, "pdf");
   }

   cE->Closed();

}

/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////

void MakeModelErrorGroups(MnvPlotter &mnvPlotter){

  mnvPlotter.ApplyStyle( kCompactStyle );
  //-- define colors of the standard errors
  mnvPlotter.draw_normalized_to_bin_width = false; //Bin width norm inside plotting function because we have substraction thus we bin_width normalize pot scale than substract
  mnvPlotter.error_color_map.clear();
  mnvPlotter.error_summary_group_map.clear();

  mnvPlotter.error_color_map["Flux"]                    =   kViolet+2;
  mnvPlotter.error_color_map["2p2h RPA Mvn1Tune"]       =   kRed;
  mnvPlotter.error_color_map["Reconstruction"]          =   kYellow+2;
  mnvPlotter.error_color_map["GENIE CrossSection QE"]    =   kOrange+2;
  mnvPlotter.error_color_map["GENIE CrossSection 1#pi"]  =   kGreen+2;
  mnvPlotter.error_color_map["GENIE CrossSection DIS"]   =   kCyan+2;
  mnvPlotter.error_color_map["GENIE CrossSection NC"]    =   kTeal+2;
  mnvPlotter.error_color_map["GENIE Nucleon FSI"]        =   kAzure+2;
  mnvPlotter.error_color_map["GENIE Pion FSI"]           =   kMagenta+2;
  mnvPlotter.error_color_map["Vertex Position"]          =   kViolet;
  mnvPlotter.error_color_map["Beam Angle"]               =   kPink;

  std::vector< string > flux;
  flux.push_back("Flux");
  flux.push_back("Flux_Tertiary");
  flux.push_back("Flux_BeamFocus");
  flux.push_back("Flux_NA49");

  mnvPlotter.error_summary_group_map["Flux"] = flux;

  std::vector< string > xsection_QE;
  std::vector< string > xsection_RES;
  std::vector< string > xsection_DIS;
  std::vector< string > xsection_NC;

  xsection_QE.push_back("GENIE_CCQEPauliSupViaKF" );
  xsection_QE.push_back("GENIE_MaZExpCCQE" ); //Changed to Z expanatio
  //xsection_QE.push_back( "GENIE_MaCCQEshape" );
  xsection_QE.push_back( "GENIE_NormCCQE" );
  xsection_QE.push_back( "GENIE_VecFFCCQEshape" );

  mnvPlotter.error_summary_group_map["GENIE CrossSection QE"]  = xsection_QE;

  xsection_NC.push_back( "GENIE_EtaNCEL" );
  xsection_NC.push_back( "GENIE_MaNCEL" );
  xsection_NC.push_back( "GENIE_NormNCRES" );

  mnvPlotter.error_summary_group_map["GENIE CrossSection NC"] = xsection_NC;

  xsection_RES.push_back( "GENIE_MaRES" );
  xsection_RES.push_back( "GENIE_MvRES" );
  xsection_RES.push_back( "GENIE_NormCCRES" );
  xsection_RES.push_back( "GENIE_Rvn1pi" );
  xsection_RES.push_back( "GENIE_Rvn2pi" );
  xsection_RES.push_back( "GENIE_Rvp1pi" );
  xsection_RES.push_back( "GENIE_Rvp2pi" );

  mnvPlotter.error_summary_group_map["GENIE CrossSection 1#pi"] = xsection_RES;

  xsection_DIS.push_back( "GENIE_AhtBY" );
  xsection_DIS.push_back( "GENIE_BhtBY" );
  xsection_DIS.push_back( "GENIE_CV1uBY" );
  xsection_DIS.push_back( "GENIE_CV2uBY" );
  xsection_DIS.push_back( "GENIE_NormDISCC" );

  mnvPlotter.error_summary_group_map["GENIE CrossSection DIS"]  = xsection_DIS;
  std::vector<std::string> genie_nucleon_fsi;
  genie_nucleon_fsi.push_back("GENIE_FrAbs_N");
  genie_nucleon_fsi.push_back("GENIE_FrCEx_N");
  genie_nucleon_fsi.push_back("GENIE_FrElas_N");
  genie_nucleon_fsi.push_back("GENIE_FrInel_N");
  genie_nucleon_fsi.push_back("GENIE_FrPiProd_N");
  genie_nucleon_fsi.push_back("GENIE_MFP_N");

  mnvPlotter.error_summary_group_map["GENIE Nucleon FSI"] = genie_nucleon_fsi;
  std::vector<std::string> genie_pion_fsi;
  genie_pion_fsi.push_back("GENIE_AGKYxF1pi");
  genie_pion_fsi.push_back("GENIE_FrAbs_pi");
  genie_pion_fsi.push_back("GENIE_FrCEx_pi");
  genie_pion_fsi.push_back("GENIE_FrElas_pi");
  genie_pion_fsi.push_back("GENIE_FrPiProd_pi");
  genie_pion_fsi.push_back("GENIE_MFP_pi");
  genie_pion_fsi.push_back("GENIE_RDecBR1gamma");
  genie_pion_fsi.push_back("GENIE_Theta_Delta2Npi");
  mnvPlotter.error_summary_group_map["GENIE Pion FSI"] = genie_pion_fsi;
  std::vector< string > lowrecoilfit;
  lowrecoilfit.push_back("Low_Recoil_2p2h_Tune");
  lowrecoilfit.push_back("RPA_LowQ2");
  lowrecoilfit.push_back("RPA_HighQ2");

  mnvPlotter.error_summary_group_map["2p2h RPA Mvn1Tune"] = lowrecoilfit;
  std::vector< string > RECOError_map;
  //    muon.push_back( "Muon_Energy" );
  RECOError_map.push_back( "Muon_Energy_MINOS" );
  RECOError_map.push_back( "Muon_Energy_MINERvA" );
  RECOError_map.push_back("MINOS_Reconstruction_Efficiency");
  RECOError_map.push_back( "Muon_Energy_Resolution" );
  RECOError_map.push_back( "MuonAngleXResolution" );
  RECOError_map.push_back( "MuonAngleYResolution" );
  RECOError_map.push_back( "HeliumTargetMass" );
  RECOError_map.push_back( "Target_Mass_CH" );
  mnvPlotter.error_summary_group_map["Reconstruction"] =RECOError_map;

  std::vector< string > beamAngleError_map;
  beamAngleError_map.push_back( "BeamAngleX" );
  beamAngleError_map.push_back( "BeamAngleY" );
  mnvPlotter.error_summary_group_map["Beam Angle"] =beamAngleError_map;

  std::vector< string > vertexError_map;
  vertexError_map.push_back( "VertexSmearingX" );
  vertexError_map.push_back( "VertexSmearingY" );
  vertexError_map.push_back( "VertexSmearingZ" );
  mnvPlotter.error_summary_group_map["Vertex Position"] =vertexError_map;



  std::vector< string > other;
  //    other.push_back( "Normalization_Factors" );
  //other.push_back( "MINOS_Reconstruction_Efficiency" );
  //other.push_back( "Michel_Efficiency");
  other.push_back( "Target_Mass" );
  other.push_back( "GENIE_nonreweightable" );
  other.push_back( "Muon_Response" );
  other.push_back( "Proton_Response" );
  other.push_back( "Low_Neutron_Response" );
  other.push_back( "Mid_Neutron_Response" );
  other.push_back( "High_Neutron_Response" );
  other.push_back( "Pion_Response" );
  other.push_back( "EM_Response" );
  other.push_back( "Other_Response" );
  other.push_back( "Crosstalk" );
  //other.push_back( "MEU_Recoil" );
  other.push_back( "Binding_Energy" );
  other.push_back( "Reweight_Pion" );
  other.push_back( "Reweight_Proton" );
  other.push_back( "Reweight_Neutron" );
  other.push_back( "Bethe_Bloch" );
  other.push_back( "MEU_Proton" );
  other.push_back( "Mass_Model_Proton" );
  other.push_back( "Birks_Response_Proton" );
  other.push_back( "Proton_TrackEff" );
  mnvPlotter.error_summary_group_map["Others"] = other;
return;
}

/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////


void PlotErrorSummaryNew(PlotUtils::MnvH1D* hist,
  std::string pdf, std::string title,
  std::string xaxis, TCanvas *cE,
   MnvPlotter *mnvPlotter, bool Debug ,bool PrintAllGroupErrors)
{

if(Debug==true){}
  const auto allBandNames = hist->GetVertErrorBandNames();
  for(const auto& name: allBandNames)
  {
    //std::cout << "name = " << name<< std::endl;
  }

//std::cout << "FINISHED PlotErrorSummaryNeW FOR" << name<< std::endl;


//  for(auto cat :mnvPlotter->error_summary_group_map)
//  {
//    std::cout << "cat.first =  " << cat.first <<std::endl;
//    for(auto cat2: cat.second)
//    {
//      std::cout << "cat.second =  " << cat2 <<std::endl;
//    }
//  }
//}




hist->GetXaxis()->SetTitle(xaxis.c_str());
mnvPlotter->DrawErrorSummary(hist, "TL", true, true, .00001, false , "" , true, "" , false);
mnvPlotter->AddHistoTitle(Form("Error Summary (%s)", title.c_str()) ,.03);
mnvPlotter->WritePreliminary("TR", .025, 0, 0, false);
mnvPlotter->MultiPrint(cE, pdf, "pdf");

double maxPlace = mnvPlotter->axis_maximum;
mnvPlotter->axis_maximum = .08;

if(PrintAllGroupErrors==true){
  //std::cout<<"Printing Error Groups"<<std::endl;
  for(const auto& cat: mnvPlotter->error_summary_group_map)
  {   cE->Clear();
    if(Debug==true){
      //  std::cout<< "Printing Error group: "<< cat.first<<std::endl;
    }

    cE->SetTitle(cat.first.c_str());
    char ErrorTitle[1024];
    if (cat.first=="Muon Reconstruction") {
      mnvPlotter->legend_n_columns = 1;
    }
    else {mnvPlotter->legend_n_columns = 2;}

  //  else{mnvPlotter->legend_n_columns = 2;}
  if (cat.first=="GENIE CrossSection RES") {
      mnvPlotter->axis_maximum = .1;
    }
    else if (cat.first=="GENIE CrossSection DIS"){
      mnvPlotter->axis_maximum = .1;
    }
    else if (cat.first=="GENIE CrossSection QE"){
      mnvPlotter->axis_maximum = .1;
    }
    else if (cat.first=="GENIE Nucleon FSI"){
      mnvPlotter->axis_maximum = .1;
    }
  else{mnvPlotter->axis_maximum = .1;
    }
    mnvPlotter->legend_text_size = .02;
    mnvPlotter->height_nspaces_per_hist = .9;

    mnvPlotter->DrawErrorSummary( hist, "TL", true, true, .00001, false , cat.first , true, "" , false);
    sprintf(ErrorTitle, "%s Error Group %s", title.c_str(), cat.first.c_str());
    mnvPlotter->AddHistoTitle(ErrorTitle,.025);
    mnvPlotter->WritePreliminary("TR", .025, 0, 0, false);
    mnvPlotter->MultiPrint(cE, pdf, "pdf");
  }
}

else{
  std::cout<<"Skipped Printing Individal Group Errors"<<std::endl;
}


mnvPlotter->axis_maximum = maxPlace;

cE->Closed();

}

/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////
void PlotErrorSummaryNew(
  PlotUtils::MnvH1D* hist, std::string pdf, std::string title,
  std::string xaxis, TCanvas *cE,MnvPlotter *mnvPlotter)
{
std::cout<< " title = "<< title<< std::endl;

   //const auto allBandNames = hist->GetVertErrorBandNames();
   //for(const auto& name: allBandNames){}

    // std::cout << "name = " << name<< std::endl;}
/*
     auto& other = ::errorGroups["Other"];
     for(const auto& name: allBandNames)
     {
       std::cout << "name = " << name<< std::endl;
       if(std::find_if(::errorGroups.begin(), errorGroups.end(),
                       [&name](const  std::pair<std::string, std::vector<std::string>>  &group)
                       { return std::find(group.second.begin(), group.second.end(), name) != group.second.end(); })
          == ::errorGroups.end())
       {
         other.push_back(name);
       }
     }
  */

// mnvPlotter->error_summary_group_map.clear();
//mnvPlotter->error_summary_group_map = ::errorGroups;


//std::cout<< "checking the names again 2"<<std::endl;
/*
auto names = hist->GetErrorBandNames();
for(auto cat : names){
  std::cout<< " name of Error Band Names= "<< cat <<std::endl;
}

for(auto cat : mnvPlotter->error_summary_group_map){
  std::cout << "cat.first =  " << cat.first <<std::endl;
  for(auto cat2: cat.second)
  {
    std::cout << "cat.second =  " << cat2 <<std::endl;
  }
}
*/
hist->GetXaxis()->SetTitle(xaxis.c_str());
mnvPlotter->DrawErrorSummary(hist, "TR", true, true, .00001, false , "" , true, "" , true);

mnvPlotter->AddHistoTitle(Form("Error Summary (%s)", title.c_str()) ,.04);
mnvPlotter->WritePreliminary("TR", .03, 0, 0, false);
mnvPlotter->MultiPrint(cE, pdf, "pdf");
mnvPlotter->legend_text_size = .02;

std::cout<<"printing error_summary_group_map "<< std::endl;
for(const auto& cat: mnvPlotter->error_summary_group_map)
{cE->Clear();
  std::cout<< "cat.first = "<< cat.first<<std::endl;
  cE->SetTitle(cat.first.c_str());
  char ErrorTitle[1024];
  mnvPlotter->DrawErrorSummary( hist, "TR", true, true, .0000001, false , cat.first , true, "" , false);
  sprintf(ErrorTitle, "(%s) Error Group %s", title.c_str(), cat.first.c_str());
  mnvPlotter->AddHistoTitle(ErrorTitle,.035);
  mnvPlotter->WritePreliminary("TR", .03, 0, 0, false);
  mnvPlotter->MultiPrint(cE, pdf, "pdf");
}

cE->Closed();

}

/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////


void PlotVertBand(std::string band,
  std::string method_str, PlotUtils::MnvH1D* hist){
  //TH1* h1 = (TH1*)hist->GetVertErrorBand(band.c_str())->GetErrorBand(do_fractional_uncertainty, do_cov_area_norm).Clone(Form("Enu_%s_%s", band.c_str(), method_str.c_str()));
  //TH1* h1 = (TH1*)hist->GetVertErrorBand(band.c_str());\

  auto Errorband = hist->GetVertErrorBand( band.c_str() );

  TCanvas cF ("c4","c4");
  //h1->SetTitle(Form("%s Uncertainty (%s); (GeV)", band.c_str(), method_str.c_str()));
  Errorband->DrawAll();
  cF.Print(Form("VertBand_%s_band_%s.pdf", band.c_str(), method_str.c_str()));
}

/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////

void PlotVertBand(std::string band,
  std::string method_str,
  std::string title, std::string Xaxis ,
  std::string Yaxis,  PlotUtils::MnvH1D* hist){
  //TH1* h1 = (TH1*)hist->GetVertErrorBand(band.c_str())->GetErrorBand(do_fractional_uncertainty, do_cov_area_norm).Clone(Form("Enu_%s_%s", band.c_str(), method_str.c_str()));
  //TH1* h1 = (TH1*)hist->GetVertErrorBand(band.c_str());

  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  auto Errorband = hist->GetVertErrorBand( band.c_str() );

  TCanvas cF ("c4","c4");
  Errorband->SetTitle(Form("%s", title.c_str()));

  Errorband->GetYaxis()->SetTitle(Form("%s",Yaxis.c_str()));
  Errorband->GetXaxis()->SetTitle(Form("%s",Xaxis.c_str()));

  Errorband->DrawAll();
  cF.Print();
  mnvPlotter.AddHistoTitle(title.c_str(), .04);
  mnvPlotter.WritePreliminary("TL", .035, 0, 0, false);
  //std::string plotname1 = Form("%s",pdf_label.c_str());
  mnvPlotter.MultiPrint(&cF, Form("VertBand_%s_band_%s", band.c_str(), method_str.c_str()), "pdf");


}

/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////


void PlotLatBand(std::string band,
   std::string method_str, PlotUtils::MnvH1D* hist){
  //TH1* h1 = (TH1*)hist->GetLatErrorBand(band.c_str())->GetErrorBand(do_fractional_uncertainty, do_cov_area_norm).Clone(Form("Enu_%s_%s", band.c_str(), method_str.c_str()));
  TH1* h1 = (TH1*)hist->GetLatErrorBand(band.c_str());
  TCanvas cF ("c1","c1");
  h1->SetTitle(Form("%s Uncertainty (%s); (GeV)", band.c_str(), method_str.c_str()));
  h1->Draw("h");
  cF.Print(Form("Lat_%s_band_%s.pdf", band.c_str(), method_str.c_str()));
}

/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////

void PlotVertUniverse(std::string band,
  unsigned int universe, std::string method_str, PlotUtils::MnvH1D* hist){
  TH1D* h1 = hist->GetVertErrorBand(band.c_str())->GetHist(universe);

  TCanvas cF ("c1","c1");
  h1->SetLineColor(kBlack);
  h1->SetLineStyle(1);
  h1->Draw("hist");
  cF.Print(Form("Enu_%s_band_universe%i_%s.pdf", band.c_str(), universe+1, method_str.c_str()));
}

/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////

void PlotLatUniverse(std::string band, unsigned int universe, std::string method_str, PlotUtils::MnvH1D* hist){
  TH1D* h1 = hist->GetLatErrorBand(band.c_str())->GetHist(universe);
  TCanvas cF ("c1","c1");
  h1->SetLineColor(kBlack);
  h1->SetLineStyle(1);
  h1->Draw("hist");
  cF.Print(Form("%s_band_universe%i_%s.pdf", band.c_str(), universe+1, method_str.c_str()));
}

/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////

void PlotCVAndError(PlotUtils::MnvH1D* hist, std::string label){
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCNuPionIncStyle);
  TCanvas cE ("c1","c1");
  hist->GetXaxis()->SetTitle(Form("%s",label.c_str()));
  PlotUtils::MnvH1D* datahist =new PlotUtils::MnvH1D("adsf", " ", nbins, xmin, xmax);
  bool statPlusSys           = true;
  int mcScale                = 1.;
  bool useHistTitles         = false;

  mnvPlotter.DrawDataMCWithErrorBand(datahist, hist, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);
  //mnvPlotter.DrawMCWithErrorBand(hist); //I think that this call only shows stat errors.
  std::string plotname = Form("%s",label.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");
}

/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////

void PlotCVAndError_second_Track(PlotUtils::MnvH1D* hist, std::string label, SecondTrkVar second_Track, TCanvas *can, std::string title){
auto axis_title = GetsecondTrk_AXIS_TitleName(second_Track);

  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kDefaultStyle );
  //TCanvas *cE ("c1","c1");

  hist->GetXaxis()->SetTitle(Form("%s",axis_title.c_str()));
  hist->GetXaxis()->CenterTitle();
  PlotUtils::MnvH1D* datahist =new PlotUtils::MnvH1D("fake", " ", nbins, xmin, xmax);
  bool statPlusSys           = true;
  int mcScale                = 1.;
  bool useHistTitles         = false;

  mnvPlotter.DrawDataMCWithErrorBand(datahist, hist, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);
  //mnvPlotter.DrawMCWithErrorBand(hist); //I think that this call only shows stat errors.
  std::string plotname = Form("%s",label.c_str());
  mnvPlotter.AddHistoTitle(title.c_str(), .04);
  mnvPlotter.MultiPrint(can, plotname, "pdf");

  PlotErrorSummary( hist, label.c_str(),label.c_str(), axis_title.c_str(),can);


}

/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////

void Plot_MuonCVAndErrorWITHDATA(
  PlotUtils::MnvH1D* histFullMC,PlotUtils::MnvH1D* histEmptyMC,
  PlotUtils::MnvH1D* datahist_Full,
  PlotUtils::MnvH1D* datahist_Empty,std::string label,
  double POT[], MuonVar Muontype, int order,TCanvas * cE)
{
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCNuPionIncStyle);
  std::string pdf;
  double MCemptyscaler = POT[0] / POT[1];
  double mcScale = POT[2] / POT[0];
  bool useHistTitles = true;
  bool statPlusSys   = true;

  PlotUtils::MnvH1D* EmptyMC     = histEmptyMC;
  PlotUtils::MnvH1D* EmptyData = datahist_Empty;
  //PlotUtils::MnvH1D* F_E_MC = histFullMC;
  EmptyData->Scale(MCemptyscaler);
  EmptyMC->Scale(MCemptyscaler);
  std::string FILLED;
  FILLED ="(FULL)";


  std::string MuonVarType;
  MuonVarType = GetMuonVarTitleName(Muontype);

  char xtitle[1024];
  std::string myunits;
  myunits = GetMuonUnitType(Muontype);
  sprintf(xtitle, "%s (%s)", MuonVarType.c_str(), myunits.c_str());

  histFullMC->GetXaxis()->SetTitle(xtitle);
  histFullMC->GetXaxis()->CenterTitle();
  histFullMC->GetXaxis()->SetTitleSize(0.038);

  char ytitle[100];
  char xError[100];

  sprintf(ytitle, "Number of Events "); // when you need decimals

  histFullMC->GetYaxis()->SetTitle(ytitle);
  histFullMC->GetYaxis()->CenterTitle();
  histFullMC->GetYaxis()->SetTitleSize(0.038);

  mnvPlotter.DrawDataMCWithErrorBand(datahist_Full, histFullMC, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);

  char total_title[1024];
  sprintf(total_title, "%s  %s", FILLED.c_str(), MuonVarType.c_str());
  mnvPlotter.AddHistoTitle(total_title, .04);


  mnvPlotter.WritePreliminary("TL", .03, 0, 0, false);
  //mnvPlotter.DrawMCWithErrorBand(hist); //I think that this call only shows stat errors.
  std::string plotname = Form("MuonVaribles_CV_w_err_%s",label.c_str());
  if(order==0){pdf = "pdf(";}
  else if(order==2||order==1){pdf = "pdf";}

  mnvPlotter.MultiPrint(cE, plotname, pdf);
  cE->Closed();
  pdf = "pdf";
  sprintf(xError, "%s (%s)(Full)", MuonVarType.c_str(), myunits.c_str());
  PlotErrorSummary(histFullMC, plotname,plotname, xError,cE);


  FILLED = "(EMPTY)";

  histEmptyMC->GetXaxis()->SetTitle(xtitle);
  histEmptyMC->GetXaxis()->CenterTitle();
  histEmptyMC->GetXaxis()->SetTitleSize(0.038);
  histEmptyMC->GetYaxis()->SetTitle(ytitle);
  histEmptyMC->GetYaxis()->CenterTitle();
  histEmptyMC->GetYaxis()->SetTitleSize(0.038);
  //histEmptyMC->GetYaxis()->SetTitleOffset(offset);
  //histEmptyMC->GetXaxis()->SetTitleOffset(offset);

  mnvPlotter.DrawDataMCWithErrorBand(datahist_Empty, histEmptyMC, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);

  sprintf(total_title, "%s  %s", FILLED.c_str(), MuonVarType.c_str());
  mnvPlotter.AddHistoTitle(total_title, .04);
  plotname = Form("MuonVaribles_CV_w_err_%s",label.c_str());
  pdf = "pdf";
  mnvPlotter.MultiPrint(cE, plotname, pdf);
  cE->Closed();

  sprintf(xError, "%s (%s)(Empty)", MuonVarType.c_str(), myunits.c_str());
  PlotErrorSummary(histEmptyMC, plotname,plotname, xError,cE);



  histFullMC->Add(EmptyMC,-1);
  datahist_Full->Add(EmptyData,-1);


  sprintf(xError, "%s (%s)(F-E)", MuonVarType.c_str(), myunits.c_str());
  PlotErrorSummary(histFullMC, plotname,plotname, xError,cE);



  if(order==1){pdf = "pdf)";}
  else if(order==2||order==0){pdf = "pdf";}
  FILLED = "(F-E)";
  sprintf(total_title, "%s  %s", FILLED.c_str(), MuonVarType.c_str());


  plotname = Form("MuonVaribles_CV_w_err_%s",label.c_str());

  histFullMC->GetXaxis()->SetTitle(xtitle);
  histFullMC->GetXaxis()->CenterTitle();
  histFullMC->GetXaxis()->SetTitleSize(0.038);
  histFullMC->GetYaxis()->SetTitle(ytitle);
  histFullMC->GetYaxis()->CenterTitle();
  histFullMC->GetYaxis()->SetTitleSize(0.038);

  mnvPlotter.DrawDataMCWithErrorBand(datahist_Full, histFullMC, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);
  mnvPlotter.AddHistoTitle(total_title, .04);
  mnvPlotter.MultiPrint(cE, plotname, pdf);
  cE->Closed();

}

/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////

void Plot_VectexCVAndErrorWITHDATA(
  PlotUtils::MnvH1D* histFullMC,PlotUtils::MnvH1D* histEmptyMC,
  PlotUtils::MnvH1D* datahist_Full,
  PlotUtils::MnvH1D* datahist_Empty,std::string label,
  double POT[], CryoVertex CryoVertex_type, int order,TCanvas * cE)
{
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCNuPionIncStyle );


  std::string pdf;
  //double dataemptyscaler = POT[2] / POT[3];
  double MCemptyscaler = POT[0] / POT[1];
  //double MCFULLdatascaler = POT[2] / POT[0];
  double mcScale = POT[2] / POT[0];
  bool useHistTitles         = true;
  bool statPlusSys           = true;
  PlotUtils::MnvH1D* EmptyMC     = histEmptyMC;
  PlotUtils::MnvH1D* EmptyData = datahist_Empty;

  EmptyData->Scale(MCemptyscaler);
  EmptyMC->Scale(MCemptyscaler);
  std::string FILLED;
  FILLED ="(FULL)";

  std::string MuonVarType;
  MuonVarType = GetVertexCryoTitleName(CryoVertex_type);

  char xtitle[1024];
  std::string myunits;
  myunits = "mm";
  sprintf(xtitle, "%s (%s)", MuonVarType.c_str(), myunits.c_str());

  histFullMC->GetXaxis()->SetTitle(xtitle);
  histFullMC->GetXaxis()->CenterTitle();
  histFullMC->GetXaxis()->SetTitleSize(0.038);
  char ytitle[100];
  char xError[100];


  sprintf(ytitle, "Number of Events "); // when you need decimals

  histFullMC->GetYaxis()->SetTitle(ytitle);
  histFullMC->GetYaxis()->CenterTitle();
  histFullMC->GetYaxis()->SetTitleSize(0.038);

  mnvPlotter.DrawDataMCWithErrorBand(datahist_Full, histFullMC, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);

  char total_title[1024];
  sprintf(total_title, "%s  %s", FILLED.c_str(), MuonVarType.c_str());
  mnvPlotter.AddHistoTitle(total_title, .04);


  mnvPlotter.WritePreliminary("TL", .03, 0, 0, false);
  mnvPlotter.AddPOTNormBox(POT[2],POT[0],0,0	);
  //mnvPlotter.DrawMCWithErrorBand(hist); //I think that this call only shows stat errors.
  std::string plotname = Form("MuonVaribles_CV_w_err_%s",label.c_str());
  if(order==0){pdf = "pdf(";}
  else if(order==2||order==1){pdf = "pdf";}

  mnvPlotter.MultiPrint(cE, plotname, pdf);
  cE->Closed();
  pdf = "pdf";
  sprintf(xError, "%s (%s)(Full)", MuonVarType.c_str(), myunits.c_str());
  PlotErrorSummary(histFullMC, plotname,plotname, xError,cE);


  FILLED = "(EMPTY)";

  histEmptyMC->GetXaxis()->SetTitle(xtitle);
  histEmptyMC->GetXaxis()->CenterTitle();
  histEmptyMC->GetXaxis()->SetTitleSize(0.038);
  histEmptyMC->GetYaxis()->SetTitle(ytitle);
  histEmptyMC->GetYaxis()->CenterTitle();
  histEmptyMC->GetYaxis()->SetTitleSize(0.038);

  mnvPlotter.DrawDataMCWithErrorBand(datahist_Empty, histEmptyMC, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);

  sprintf(total_title, "%s  %s", FILLED.c_str(), MuonVarType.c_str());
  mnvPlotter.AddHistoTitle(total_title, .04);
  plotname = Form("MuonVaribles_CV_w_err_%s",label.c_str());
  pdf = "pdf";
  mnvPlotter.MultiPrint(cE, plotname, pdf);
  cE->Closed();

  sprintf(xError, "%s (%s)(Empty)", MuonVarType.c_str(), myunits.c_str());
  PlotErrorSummary(histEmptyMC, plotname,plotname, xError,cE);



  histFullMC->Add(EmptyMC,-1);
  datahist_Full->Add(EmptyData,-1);


  sprintf(xError, "%s (%s)(F-E)", MuonVarType.c_str(), myunits.c_str());
  PlotErrorSummary(histFullMC, plotname,plotname, xError,cE);



  if(order==1){pdf = "pdf)";}
  else if(order==2||order==0){pdf = "pdf";}
  FILLED = "(F-E)";

  plotname = Form("MuonVaribles_CV_w_err_%s",label.c_str());

  histFullMC->GetXaxis()->SetTitle(xtitle);
  histFullMC->GetXaxis()->CenterTitle();
  histFullMC->GetXaxis()->SetTitleSize(0.038);
  histFullMC->GetYaxis()->SetTitle(ytitle);
  histFullMC->GetYaxis()->CenterTitle();
  histFullMC->GetYaxis()->SetTitleSize(0.038);

  mnvPlotter.DrawDataMCWithErrorBand(datahist_Full, histFullMC, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);
  sprintf(total_title, "%s  %s", FILLED.c_str(), MuonVarType.c_str());

  mnvPlotter.AddHistoTitle(total_title, .04);
  mnvPlotter.MultiPrint(cE, plotname, pdf);
  cE->Closed();


}

/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////

void Plot_SecTRKCVAndErrorWITHDATA(
  PlotUtils::MnvH1D* histFullMC,PlotUtils::MnvH1D* histEmptyMC,
  PlotUtils::MnvH1D* datahist_Full,
  PlotUtils::MnvH1D* datahist_Empty,
  std::string label, double POT[],
  SecondTrkVar SecondTrkVar_type, int order,TCanvas * cE)
{
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCNuPionIncStyle );

  std::string pdf;
  double MCemptyscaler = POT[0] / POT[1];
  double mcScale = POT[2] / POT[0];
  bool useHistTitles         = true;
  bool statPlusSys           = true;
  PlotUtils::MnvH1D* EmptyMC     = histEmptyMC;
  PlotUtils::MnvH1D* EmptyData = datahist_Empty;
  //PlotUtils::MnvH1D* F_E_MC = histFullMC;
  EmptyData->Scale(MCemptyscaler);
  EmptyMC->Scale(MCemptyscaler);
  std::string FILLED;
  FILLED ="(FULL)";


  std::string MuonVarType;
  MuonVarType = GetsecondTrkTitleName(SecondTrkVar_type);

  char xtitle[1024];
  std::string myunits;
  myunits = "mm";
  sprintf(xtitle, "%s (%s)", MuonVarType.c_str(), myunits.c_str());

  histFullMC->GetXaxis()->SetTitle(xtitle);
  histFullMC->GetXaxis()->CenterTitle();
  histFullMC->GetXaxis()->SetTitleSize(0.038);
  char ytitle[100];
  char xError[100];

  //double binwidth = hist -> GetBinWidth(3);

  sprintf(ytitle, "Number of Events "); // when you need decimals
  // else if (histUnits == 1 || histUnits == 2) sprintf(ytitle, "Number of Events / %d %s", binwidth, myunits); // when you need ints --> CHECK IF THIS WORKS RIGHT IT DOES NOT

  histFullMC->GetYaxis()->SetTitle(ytitle);
  histFullMC->GetYaxis()->CenterTitle();
  histFullMC->GetYaxis()->SetTitleSize(0.038);
  //histFullMC->GetYaxis()->SetTitleOffset(offset);
  //histFullMC->GetXaxis()->SetTitleOffset(offset);

  mnvPlotter.DrawDataMCWithErrorBand(datahist_Full, histFullMC, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);

  char total_title[1024];
  sprintf(total_title, "%s  %s", FILLED.c_str(), MuonVarType.c_str());
  mnvPlotter.AddHistoTitle(total_title, .04);


  mnvPlotter.WritePreliminary("TL", .03, 0, 0, false);
  mnvPlotter.AddPOTNormBox(POT[2],POT[0],0,0	);
  //mnvPlotter.DrawMCWithErrorBand(hist); //I think that this call only shows stat errors.
  std::string plotname = Form("SecodaryTRK_CV_w_err_%s",label.c_str());
  if(order==0){pdf = "pdf(";}
  else if(order==2||order==1){pdf = "pdf";}

  mnvPlotter.MultiPrint(cE, plotname, pdf);
  cE->Closed();
  pdf = "pdf";
  sprintf(xError, "%s (%s)(Full)", MuonVarType.c_str(), myunits.c_str());
  PlotErrorSummary(histFullMC, plotname,plotname, xError,cE);

  FILLED = "(EMPTY)";

  histEmptyMC->GetXaxis()->SetTitle(xtitle);
  histEmptyMC->GetXaxis()->CenterTitle();
  histEmptyMC->GetXaxis()->SetTitleSize(0.038);
  histEmptyMC->GetYaxis()->SetTitle(ytitle);
  histEmptyMC->GetYaxis()->CenterTitle();
  histEmptyMC->GetYaxis()->SetTitleSize(0.038);

  mnvPlotter.DrawDataMCWithErrorBand(datahist_Empty, histEmptyMC, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);

  sprintf(total_title, "%s  %s", FILLED.c_str(), MuonVarType.c_str());
  mnvPlotter.AddHistoTitle(total_title, .04);
  plotname = Form("SecodaryTRK_CV_w_err_%s",label.c_str());
  pdf = "pdf";
  mnvPlotter.MultiPrint(cE, plotname, pdf);
  cE->Closed();

  sprintf(xError, "%s (%s)(Empty)", MuonVarType.c_str(), myunits.c_str());
  PlotErrorSummary(histEmptyMC, plotname,plotname, xError,cE);


  histFullMC->Add(EmptyMC,-1);
  datahist_Full->Add(EmptyData,-1);


  sprintf(xError, "%s (%s)(F-E)", MuonVarType.c_str(), myunits.c_str());
  PlotErrorSummary(histFullMC, plotname,plotname, xError,cE);



  if(order==1){pdf = "pdf)";}
  else if(order==2||order==0){pdf = "pdf";}
  FILLED = "(F-E)";

  plotname = Form("SecodaryTRK_CV_w_err_%s",label.c_str());

  histFullMC->GetXaxis()->SetTitle(xtitle);
  histFullMC->GetXaxis()->CenterTitle();
  histFullMC->GetXaxis()->SetTitleSize(0.038);
  histFullMC->GetYaxis()->SetTitle(ytitle);
  histFullMC->GetYaxis()->CenterTitle();
  histFullMC->GetYaxis()->SetTitleSize(0.038);
  //histFullMC->GetYaxis()->SetTitleOffset(offset);
  //histFullMC->GetXaxis()->SetTitleOffset(offset);

  mnvPlotter.DrawDataMCWithErrorBand(datahist_Full, histFullMC, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);
  sprintf(total_title, "%s  %s", FILLED.c_str(), MuonVarType.c_str());

  mnvPlotter.AddHistoTitle(total_title, .04);
  mnvPlotter.MultiPrint(cE, plotname, pdf);
  cE->Closed();


}

/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////

void DrawStack_Material(bool my_debug, TFile *inputFile,  CryoVertex Vertex_type,
   ME_helium_Playlists PlayList, int doShape, int logScale, const char* title,
MnvPlotter *plot, TCanvas *can, const char *pdf)
{

  // set up legend, assuming this function only ever plots oodles of stacked histograms
  double x1, x2, y1, y2;
  plot->DecodeLegendPosition(x1, y1, x2, y2, "R", 7, 7, .03);
  TLegend *legend = new TLegend(x1 + .145, y1 + .2, x2 + .16, y2 + .2);
  legend->SetNColumns(1);
  legend->SetTextSize(.03);
  legend->SetFillColor(0);

  auto Material_vector = GetMaterial_typeList();
  auto label_title = GetVertexCryoTitleName(Vertex_type);
  auto xaxislabel = GetVertexCryoVarAxisTitle(Vertex_type);
  auto Var_Name =  GetVertexCryoVarHistName(Vertex_type);
  auto Playlist_name = GetPlaylist_Name(PlayList);
  auto CryoTankStatus = GetFULLorEmpty(GetPlaylist_HeliumStatus(PlayList));


  auto Fulltitle = title + label_title + "playlist: " + Playlist_name + " (" + CryoTankStatus + ") ";
  int Fulltitle_n = Fulltitle.length();
  char FinalTitle[Fulltitle_n + 1];
  strcpy(FinalTitle, Fulltitle.c_str());


  MnvH1D *hist_total;
  THStack *mystack[1];
  mystack[0] = new THStack("hs0", "Stacked");
  int fillCol=0;

  TIter Iter(inputFile->GetListOfKeys());
  TObject *key;

  while((key=Iter()))
  {
    const std::string histName = key->GetName();
    //std::cout<<"HistName = " << histName << std::endl;


    for(auto Material: Material_vector){auto MaterialName = GetNameMaterial(Material);//end of loop

      if(histName.find((Var_Name + "_material_"+ MaterialName)) != std::string::npos  ){

        std::cout<<" Total = " <<  Var_Name + "_material_"+ MaterialName<< std::endl;
        std::cout<<" Total(Key) = " << histName<< std::endl;
        hist_total = dynamic_cast< MnvH1D*>(((TKey*)key)->ReadObj());

      }
      else if(histName.find((MaterialName+"_"+ Var_Name + "_material")) != std::string::npos) //Then this is a NeutrinoEnergy histogram for some material
      {
        std::cout<<"Inside else IF  = " << MaterialName+"_"+ Var_Name + "_material"<<std::endl;

        auto hist = dynamic_cast<MnvH1D*>(((TKey*)key)->ReadObj());
        hist -> SetFillColor(CCNuPionIncPlotting::fill_colors[fillCol]);
        hist -> SetLineColor(CCNuPionIncPlotting::fill_colors[fillCol]);
        hist -> SetFillStyle(1001);
        hist -> SetLineWidth(1);
        fillCol++;
        if(hist == nullptr) //nullptr is the same as NULL effectively, but it does some cool type conversion for std::unique_ptr<>
        {
          std::cerr << histName << " is not a TH1, but it is a neutrinoEnergy histogram!  Skipping " << histName << "...\n";
        }
        hist->Scale(1.0,"width");
        mystack[0]->Add(hist); //This might want you to derefence hist first
        int n = MaterialName.length();
        char char_array[n + 1];
        strcpy(char_array, MaterialName.c_str());
        legend->AddEntry(hist, char_array);
      }
    }
  }

  legend->AddEntry(hist_total, "Total");
  hist_total->SetMaximum(hist_total->GetMaximum() * 1.45);
  int n = xaxislabel.length();
  char xtitle[n+1];
  strcpy(xtitle, xaxislabel.c_str());
  hist_total->GetXaxis()->SetTitle(xtitle);
  hist_total->GetYaxis()->SetTitle("NEvents");
  hist_total->GetXaxis()->CenterTitle();
  hist_total->GetXaxis()->SetTitleSize(0.038);
  hist_total->Scale(1.0,"width");
  hist_total->Draw("HIST");
  mystack[0]->Draw("HIST SAME");
  legend->Draw();

  plot->AddHistoTitle(FinalTitle, .04);
  plot->WritePreliminary("TL", .035, 0, 0, false);

  can -> Print(pdf);


}//ENd of DrawStack_Material

/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////

void DrawStack_Interaction(bool my_debug, TFile *inputFile,  CryoVertex Vertex_type ,
ME_helium_Playlists PlayList , int doShape, int logScale, const char* title,
MnvPlotter *plot, TCanvas *can, const char *pdf)
{

  // set up legend, assuming this function only ever plots oodles of stacked histograms
  double x1, x2, y1, y2;
  plot->DecodeLegendPosition(x1, y1, x2, y2, "R", 7, 7, .03);
  TLegend *legend = new TLegend(x1 + .145, y1 + .2, x2 + .16, y2 + .2);
  legend->SetNColumns(1);
  legend->SetTextSize(.03);
  legend->SetFillColor(0);

  auto Interaction_vector = GetInteraction_typeList();

  auto label_title = GetVertexCryoTitleName(Vertex_type);
  auto xaxislabel = GetVertexCryoVarAxisTitle(Vertex_type);
  auto Var_Name =  GetVertexCryoVarHistName(Vertex_type);
  auto Playlist_name = GetPlaylist_Name(PlayList);
  auto CryoTankStatus = GetFULLorEmpty(GetPlaylist_HeliumStatus(PlayList));


  auto Fulltitle = label_title + " playlist: " + Playlist_name + " (" + CryoTankStatus + ") ";
  int Fulltitle_n = Fulltitle.length();
  char FinalTitle[Fulltitle_n + 1];
  strcpy(FinalTitle, Fulltitle.c_str());


  MnvH1D *hist_total;
  THStack *mystack[1];
  mystack[0] = new THStack("hs0", "Stacked");
  int fillCol=0;


  TIter Iter(inputFile->GetListOfKeys());
  TObject *key;

  while((key=Iter()))
  {
    const std::string histName = key->GetName();
    //std::cout<<"HistName = " << histName << std::endl;


    for(auto Interaction: Interaction_vector){auto InteractionName = GetNameInteraction(Interaction);//end of loop

      if(histName.find((Var_Name + "_interaction_"+ InteractionName)) != std::string::npos  ){

        std::cout<<" Total = " <<  Var_Name + "_interaction_"+ InteractionName<< std::endl;
        std::cout<<" Total(Key) = " << histName<< std::endl;
        hist_total = dynamic_cast< MnvH1D*>(((TKey*)key)->ReadObj());

      }
      else if(histName.find((InteractionName+"_"+ Var_Name + "_interaction")) != std::string::npos) //Then this is a NeutrinoEnergy histogram for some material
      {
        std::cout<<"Inside else IF  = " << InteractionName+"_"+ Var_Name + "_interaction"<<std::endl;

        auto hist = dynamic_cast<MnvH1D*>(((TKey*)key)->ReadObj());
        hist -> SetFillColor(CCNuPionIncPlotting::fill_colors[fillCol]);
        hist -> SetLineColor(CCNuPionIncPlotting::fill_colors[fillCol]);
        hist -> SetFillStyle(1001);
        hist -> SetLineWidth(1);
        //
        fillCol++;
        if(hist == nullptr) //nullptr is the same as NULL effectively, but it does some cool type conversion for std::unique_ptr<>
        {
          std::cerr << histName << " is not a TH1, but it is a neutrinoEnergy histogram!  Skipping " << histName << "...\n";
        }
        hist->Scale(1.0,"width");
        mystack[0]->Add(hist); //This might want you to derefence hist first
        int n = InteractionName.length();
        char char_array[n + 1];
        strcpy(char_array, InteractionName.c_str());
        legend->AddEntry(hist, char_array);
      }
    }
  }
  legend->AddEntry(hist_total, "Total");
  hist_total->SetMaximum(hist_total->GetMaximum() * 1.45);
  int n = xaxislabel.length();
  char xtitle[n+1];
  strcpy(xtitle, xaxislabel.c_str());
  hist_total->GetXaxis()->SetTitle(xtitle);
  hist_total->GetYaxis()->SetTitle("NEvents");
  hist_total->GetXaxis()->CenterTitle();
  hist_total->GetXaxis()->SetTitleSize(0.038);
  hist_total->Scale(1.0,"width");
  hist_total->Draw("HIST");
  mystack[0]->Draw("HIST SAME");
  legend->Draw();

  plot->AddHistoTitle(FinalTitle, .04);
  plot->WritePreliminary("TL", .035, 0, 0, false);

  can -> Print(pdf);


}//ENd of DrawStack_Interaction

/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////

void DrawStack_Particle(
  bool my_debug, TFile *inputFile,
  CryoVertex Vertex_type, ME_helium_Playlists PlayList,
  int doShape, int logScale, const char* title,
  MnvPlotter *plot, TCanvas *can, const char *pdf){

    // set up legend, assuming this function only ever plots oodles of stacked histograms
    double x1, x2, y1, y2;
    plot->DecodeLegendPosition(x1, y1, x2, y2, "R", 7, 7, .03);
    TLegend *legend = new TLegend(x1 + .145, y1 + .2, x2 + .16, y2 + .2);
    legend->SetNColumns(1);
    legend->SetTextSize(.03);
    legend->SetFillColor(0);

    auto Particle_vector = GetParticle_typeList();

    auto xaxislabel = GetVertexCryoVarAxisTitle(Vertex_type);
    auto Var_Name =  GetVertexCryoVarHistName(Vertex_type);
    auto Playlist_name = GetPlaylist_Name(PlayList);
    auto CryoTankStatus = GetFULLorEmpty(GetPlaylist_HeliumStatus(PlayList));


    auto Fulltitle = title+ xaxislabel + "playlist: " + Playlist_name + " (" + CryoTankStatus + ") ";
    int Fulltitle_n = Fulltitle.length();
    char FinalTitle[Fulltitle_n + 1];
    strcpy(FinalTitle, Fulltitle.c_str());


    MnvH1D *hist_total;
    THStack *mystack[1];
    mystack[0] = new THStack("hs0", "Stacked");
    int fillCol=0;


    TIter Iter(inputFile->GetListOfKeys());
    TObject *key;

    while((key=Iter()))
    {
      const std::string histName = key->GetName();
      //std::cout<<"HistName = " << histName << std::endl;

for(auto Particle: Particle_vector){auto ParticleName = GetNameParticle(Particle);//end of loop

  if(histName.find((Var_Name + "_particle_"+ ParticleName)) != std::string::npos  ){

    std::cout<<" Total = " <<  Var_Name + "_particle_"+ ParticleName<< std::endl;
    std::cout<<" Total(Key) = " << histName<< std::endl;
    hist_total = dynamic_cast< MnvH1D*>(((TKey*)key)->ReadObj());

  }
  else if(histName.find((ParticleName+"_"+ Var_Name + "_particle")) != std::string::npos) //Then this is a NeutrinoEnergy histogram for some material
  {
    std::cout<<"Inside else IF  = " << ParticleName+"_"+ Var_Name + "_particle"<<std::endl;

    auto hist = dynamic_cast<MnvH1D*>(((TKey*)key)->ReadObj());
    hist -> SetFillColor(CCNuPionIncPlotting::fill_colors[fillCol]);
    hist -> SetLineColor(CCNuPionIncPlotting::fill_colors[fillCol]);
    hist -> SetFillStyle(1001);
    hist -> SetLineWidth(1);
    fillCol++;
    if(hist == nullptr) //nullptr is the same as NULL effectively, but it does some cool type conversion for std::unique_ptr<>
    {
      std::cerr << histName << " is not a TH1, but it is a neutrinoEnergy histogram!  Skipping " << histName << "...\n";
    }
    hist->Scale(1,"width");
    mystack[0]->Add(hist); //This might want you to derefence hist first
    int n = ParticleName.length();
    char char_array[n + 1];
    strcpy(char_array, ParticleName.c_str());
    legend->AddEntry(hist, char_array);
  }
}
}
legend->AddEntry(hist_total, "Total");
hist_total->SetMaximum(hist_total->GetMaximum() * 1.45);
int n = xaxislabel.length();
char xtitle[n+1];
strcpy(xtitle, xaxislabel.c_str());
hist_total->GetXaxis()->SetTitle(xtitle);
hist_total->GetYaxis()->SetTitle("NEvents");
hist_total->GetXaxis()->CenterTitle();
hist_total->GetXaxis()->SetTitleSize(0.038);
hist_total->Scale(1.0,"width");
hist_total->Draw("HIST");
mystack[0]->Draw("HIST SAME");
legend->Draw();

plot->AddHistoTitle(FinalTitle, .04);
plot->WritePreliminary("TL", .035, 0, 0, false);

can -> Print(pdf);


}//ENd of DrawStack_paricle

/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////
void DrawStack_secTrk_Particle_FUll_EMPTY(
  bool my_debug, TFile *inputFile_FULL, TFile *inputFile_EMPTY,
  Pot_MapList POT_MC, SecondTrkVar second_Trk_type,
  ME_helium_Playlists PlayListFULL,
  ME_helium_Playlists PlayListEmpty,
  int doShape, int logScale, std::string Hist_name_addON,
  MnvPlotter *plot, TCanvas *can, const char *pdf){

    // set up legend, assuming this function only ever plots oodles of stacked histograms
    double x1, x2, y1, y2;
    plot->DecodeLegendPosition(x1, y1, x2, y2, "R", 7, 7, .03);
    TLegend *legend = new TLegend(x1 + .145, y1 + .2, x2 + .16, y2 + .2);
    legend->SetNColumns(1);
    legend->SetTextSize(.03);
    legend->SetFillColor(0);

    auto Particle_vector = GetParticle_typeList();
    Particle_MnvH1D_Map FULL_HISTS,EMPTY_HISTS;
    std::vector<MnvH1D*>  FULL_HISTS_vector,EMPTY_HISTS_vector;

    auto xaxislabel = GetsecondTrk_AXIS_TitleName(second_Trk_type);
    auto Var_Name =  GetsecondTrakHistName(second_Trk_type) + Hist_name_addON;
    auto Var_title =  GetsecondTrkTitleName(second_Trk_type);
    auto Playlist_name_FULL = GetPlaylist_InitialName(PlayListFULL);
    auto Playlist_name_EMPTY = GetPlaylist_InitialName(PlayListEmpty);

    auto POT_scale_toFULL= POT_MC[PlayListFULL]/POT_MC[PlayListEmpty];

    std::cout<< "POT scaler = "<<  POT_scale_toFULL<<std::endl;

    auto Fulltitle =   Var_title  + " (" + Playlist_name_FULL + " - " + Playlist_name_EMPTY + ") ";
    int Fulltitle_n = Fulltitle.length();
    char FinalTitle[Fulltitle_n + 1];
    strcpy(FinalTitle, Fulltitle.c_str());



    MnvH1D *hist_totalFULL;
    MnvH1D *hist_totalEMPTY;
    THStack *mystack[2];
    mystack[0] = new THStack("hs0", "Stacked");
    int fillCol=0;


    TIter Iter(inputFile_FULL->GetListOfKeys());
    TObject *key;

    TIter Iter_empty(inputFile_EMPTY->GetListOfKeys());
    TObject *keyEMPTY;


std::cout<<"first Loop "<<std::endl;

    while((key=Iter()))
    {
      const std::string histName = key->GetName();
      //std::cout<<"HistName = " << histName << std::endl;


      for(auto Particle: Particle_vector){auto ParticleName = GetNameParticle(Particle);//end of loop

        if(histName.find((Var_Name + "_particle_"+ ParticleName)) != std::string::npos  ){

          std::cout<<" Total = " <<  Var_Name + "_particle_"+ ParticleName<< std::endl;
          std::cout<<" Total(Key) = " << histName<< std::endl;
          hist_totalFULL = dynamic_cast< MnvH1D*>(((TKey*)key)->ReadObj());

        }
        else if(histName.find((ParticleName+"_"+ Var_Name + "_particle")) != std::string::npos) //Then this is a NeutrinoEnergy histogram for some material
        {
          std::cout<<"Inside else IF  = " << ParticleName+"_"+ Var_Name + "_particle"<<std::endl;

          auto hist = dynamic_cast<MnvH1D*>(((TKey*)key)->ReadObj());
          hist -> SetFillColor(CCNuPionIncPlotting::fill_colors[fillCol]);
          hist -> SetLineColor(CCNuPionIncPlotting::fill_colors[fillCol]);
          hist -> SetFillStyle(1001);
          hist -> SetLineWidth(1);
          fillCol++;
          if(hist == nullptr) //nullptr is the same as NULL effectively, but it does some cool type conversion for std::unique_ptr<>
          {
            std::cerr << histName << " is not a TH1, but it is a neutrinoEnergy histogram!  Skipping " << histName << "...\n";
          }

          //hist->Scale(1,"width");
          //mystack[0]->Add(hist); //This might want you to derefence hist first
          //FULL_HISTS.insert({Particle, hist});
          FULL_HISTS_vector.push_back(hist);
          int n = ParticleName.length();
          char char_array[n + 1];
          strcpy(char_array, ParticleName.c_str());
          legend->AddEntry(hist, char_array);
        }
      }
    }

std::cout<<"2nd Loop "<<std::endl;

    while((keyEMPTY=Iter_empty()))
    {
      const std::string histName = keyEMPTY->GetName();
      //std::cout<<"HistName = " << histName << std::endl;


      for(auto Particle: Particle_vector){auto ParticleName = GetNameParticle(Particle);//end of loop
      //  std::cout<<"Loop2 Particle ="<<Particle<<std::endl;
        if(histName.find((Var_Name + "_particle_"+ ParticleName)) != std::string::npos  ){

          std::cout<<" Total = " <<  Var_Name + "_particle_"+ ParticleName<< std::endl;
          std::cout<<" Total(Key) = " << histName<< std::endl;
          hist_totalEMPTY = dynamic_cast< MnvH1D*>(((TKey*)keyEMPTY)->ReadObj());

        }
        else if(histName.find((ParticleName+"_"+ Var_Name + "_particle")) != std::string::npos) //Then this is a NeutrinoEnergy histogram for some material
        {
          std::cout<<"Inside else IF  = " << ParticleName+"_"+ Var_Name + "_particle"<<std::endl;

          auto hist = dynamic_cast<MnvH1D*>(((TKey*)keyEMPTY)->ReadObj());
          hist -> SetFillColor(CCNuPionIncPlotting::fill_colors[fillCol]);
          hist -> SetLineColor(CCNuPionIncPlotting::fill_colors[fillCol]);
          hist -> SetFillStyle(1001);
          hist -> SetLineWidth(1);
          fillCol++;
          if(hist == nullptr) //nullptr is the same as NULL effectively, but it does some cool type conversion for std::unique_ptr<>
          {
            std::cerr << histName << " is not a TH1, but it is a neutrinoEnergy histogram!  Skipping " << histName << "...\n";
          }

          EMPTY_HISTS_vector.push_back(hist);

        }
      }
    }


if(EMPTY_HISTS_vector.size()!=FULL_HISTS_vector.size()){std::cout<<"size BAD"<<std::endl;}
else{std::cout<<"Size of vectors good "<<std::endl;}
std::cout<<"3rd Loop "<<std::endl;

for(int i=0; i != FULL_HISTS_vector.size(); i++){
  //auto ParticleName = GetNameParticle(Particle_vector[i+1]);
  EMPTY_HISTS_vector[i]->Scale(POT_scale_toFULL);
  FULL_HISTS_vector[i]->Add(EMPTY_HISTS_vector[i],-1);
  FULL_HISTS_vector[i]->Scale(1,"width");
  mystack[0]->Add(FULL_HISTS_vector[i]);

}



    hist_totalEMPTY->Scale(POT_scale_toFULL);
    hist_totalFULL->Add(hist_totalEMPTY,-1);

    legend->AddEntry(hist_totalFULL, "Total");
     int n = xaxislabel.length();
     char xtitle[n+1];
      strcpy(xtitle, xaxislabel.c_str());
      hist_totalFULL->GetXaxis()->SetTitle(xtitle);
      hist_totalFULL->GetYaxis()->SetTitle("NEvents");
      hist_totalFULL->GetXaxis()->CenterTitle();
      hist_totalFULL->GetXaxis()->SetTitleSize(0.038);
      hist_totalFULL->Scale(1.0,"width");
      hist_totalFULL->SetMaximum(hist_totalFULL->GetMaximum() * 1.45);
      hist_totalFULL->Draw("HIST");
     mystack[0]->Draw("HIST SAME");
     legend->Draw();

     plot->AddHistoTitle(FinalTitle, .04);
     plot->WritePreliminary("TL", .035, 0, 0, false);

     can -> Print(pdf);


}//ENd of DrawStack_paricle

/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////

void DrawStack_secTrk_Particle_FUll_EMPTY_WITHDATA(
  bool my_debug, TFile *inputFile_FULL,
  TFile *inputFile_EMPTY,
  TFile *inputFile_DATA_FULL,
  TFile *inputFile_DATA_EMPTY,
  Pot_MapList POT_MC ,Pot_MapList POT_DATA,
  SecondTrkVar second_Trk_type,
  ME_helium_Playlists PlayListFULL,
  ME_helium_Playlists PlayListEmpty,int doShape,
  int logScale, std::string Hist_name_addON,
  MnvPlotter *plot, TCanvas *can, const char *pdf)
  {
    // set up legend, assuming this function only ever plots oodles of stacked histograms
    double x1, x2, y1, y2;
    plot->DecodeLegendPosition(x1, y1, x2, y2, "R", 7, 7, .03);
    TLegend *legend = new TLegend(x1 + .145, y1 + .2, x2 + .16, y2 + .2);
    legend->SetNColumns(1);
    legend->SetTextSize(.03);
    legend->SetFillColor(0);

    auto Particle_vector = GetParticle_typeList();
    Particle_MnvH1D_Map FULL_HISTS,EMPTY_HISTS;
    std::vector<MnvH1D*>  FULL_HISTS_vector,EMPTY_HISTS_vector;

    auto xaxislabel = GetsecondTrk_AXIS_TitleName(second_Trk_type);
    auto Var_Name =  GetsecondTrakHistName(second_Trk_type) + Hist_name_addON;
    auto Var_title =  GetsecondTrkTitleName(second_Trk_type);
    auto Playlist_name_FULL = GetPlaylist_InitialName(PlayListFULL);
    auto Playlist_name_EMPTY = GetPlaylist_InitialName(PlayListEmpty);

    auto Var_Name_DATA = GetsecondTrakHistName_DATA_Name(second_Trk_type);
    int n_Var_Name_DATA = Var_Name_DATA.length();
    char Var_Name_DATA_char[n_Var_Name_DATA+1];
    strcpy( Var_Name_DATA_char,Var_Name_DATA.c_str());
    PlotUtils::MnvH1D* datahist_FULL = (MnvH1D*)inputFile_DATA_FULL->Get(Var_Name_DATA_char);
    PlotUtils::MnvH1D* datahist_EMPTY = (MnvH1D*)inputFile_DATA_EMPTY->Get(Var_Name_DATA_char);
    auto POT_scale_toFULL= POT_MC[PlayListFULL]/POT_MC[PlayListEmpty];
    auto POT_scale_toFULLDATA= POT_DATA[PlayListFULL]/POT_DATA[PlayListEmpty];
    auto POT_scale_toFULL_MC_ToDATA= POT_DATA[PlayListFULL]/POT_MC[PlayListFULL];

    std::cout<<"scale to data = "<< POT_scale_toFULLDATA<<std::endl;
    datahist_EMPTY->Scale(POT_scale_toFULLDATA);
    datahist_FULL->Add(datahist_EMPTY,-1);
    legend->AddEntry(datahist_FULL, "DATA");

    std::cout<< "POT scaler = "<<  POT_scale_toFULL<<std::endl;

    auto Fulltitle =   Var_title  + "(DataOverlay) (" + Playlist_name_FULL + " - " + Playlist_name_EMPTY + ") ";
    int Fulltitle_n = Fulltitle.length();
    char FinalTitle[Fulltitle_n + 1];
    strcpy(FinalTitle, Fulltitle.c_str());



    MnvH1D *hist_totalFULL;
    MnvH1D *hist_totalEMPTY;
    THStack *mystack[2];
    mystack[0] = new THStack("hs0", "Stacked");
    int fillCol=0;


    TIter Iter(inputFile_FULL->GetListOfKeys());
    TObject *key;

    TIter Iter_empty(inputFile_EMPTY->GetListOfKeys());
    TObject *keyEMPTY;


std::cout<<"first Loop "<<std::endl;

    while((key=Iter()))
    {
      const std::string histName = key->GetName();
      //std::cout<<"HistName = " << histName << std::endl;


      for(auto Particle: Particle_vector){auto ParticleName = GetNameParticle(Particle);//end of loop

        if(histName.find((Var_Name + "_particle_"+ ParticleName)) != std::string::npos  ){

          std::cout<<" Total = " <<  Var_Name + "_particle_"+ ParticleName<< std::endl;
          std::cout<<" Total(Key) = " << histName<< std::endl;
          hist_totalFULL = dynamic_cast< MnvH1D*>(((TKey*)key)->ReadObj());

        }
        else if(histName.find((ParticleName+"_"+ Var_Name + "_particle")) != std::string::npos) //Then this is a NeutrinoEnergy histogram for some material
        {
          std::cout<<"Inside else IF  = " << ParticleName+"_"+ Var_Name + "_particle"<<std::endl;

          auto hist = dynamic_cast<MnvH1D*>(((TKey*)key)->ReadObj());
          hist -> SetFillColor(CCNuPionIncPlotting::fill_colors[fillCol]);
          hist -> SetLineColor(CCNuPionIncPlotting::fill_colors[fillCol]);
          hist -> SetFillStyle(1001);
          hist -> SetLineWidth(1);
          fillCol++;
          if(hist == nullptr) //nullptr is the same as NULL effectively, but it does some cool type conversion for std::unique_ptr<>
          {
            std::cerr << histName << " is not a TH1, but it is a neutrinoEnergy histogram!  Skipping " << histName << "...\n";
          }

          FULL_HISTS_vector.push_back(hist);
          int n = ParticleName.length();
          char char_array[n + 1];
          strcpy(char_array, ParticleName.c_str());
          legend->AddEntry(hist, char_array);
        }
      }
    }

std::cout<<"2nd Loop "<<std::endl;

    while((keyEMPTY=Iter_empty()))
    {
      const std::string histName = keyEMPTY->GetName();
      //std::cout<<"HistName = " << histName << std::endl;


      for(auto Particle: Particle_vector){auto ParticleName = GetNameParticle(Particle);//end of loop
      //  std::cout<<"Loop2 Particle ="<<Particle<<std::endl;
        if(histName.find((Var_Name + "_particle_"+ ParticleName)) != std::string::npos  ){

          std::cout<<" Total = " <<  Var_Name + "_particle_"+ ParticleName<< std::endl;
          std::cout<<" Total(Key) = " << histName<< std::endl;
          hist_totalEMPTY = dynamic_cast< MnvH1D*>(((TKey*)keyEMPTY)->ReadObj());

        }
        else if(histName.find((ParticleName+"_"+ Var_Name + "_particle")) != std::string::npos) //Then this is a NeutrinoEnergy histogram for some material
        {
          std::cout<<"Inside else IF  = " << ParticleName+"_"+ Var_Name + "_particle"<<std::endl;

          auto hist = dynamic_cast<MnvH1D*>(((TKey*)keyEMPTY)->ReadObj());
          hist -> SetFillColor(CCNuPionIncPlotting::fill_colors[fillCol]);
          hist -> SetLineColor(CCNuPionIncPlotting::fill_colors[fillCol]);
          hist -> SetFillStyle(1001);
          hist -> SetLineWidth(1);
          fillCol++;
          if(hist == nullptr) //nullptr is the same as NULL effectively, but it does some cool type conversion for std::unique_ptr<>
          {
            std::cerr << histName << " is not a TH1, but it is a neutrinoEnergy histogram!  Skipping " << histName << "...\n";
          }


          EMPTY_HISTS_vector.push_back(hist);

        }
      }
    }


if(EMPTY_HISTS_vector.size()!=FULL_HISTS_vector.size()){std::cout<<"size BAD"<<std::endl;}
else{std::cout<<"Size of vectors good "<<std::endl;}
std::cout<<"3rd Loop "<<std::endl;

for(int i=0; i != FULL_HISTS_vector.size(); i++){
  //auto ParticleName = GetNameParticle(Particle_vector[i+1]);

  EMPTY_HISTS_vector[i]->Scale(POT_scale_toFULL);
  FULL_HISTS_vector[i]->Add(EMPTY_HISTS_vector[i],-1);
  FULL_HISTS_vector[i]->Scale(POT_scale_toFULL_MC_ToDATA);
  FULL_HISTS_vector[i]->Scale(1,"width");
  mystack[0]->Add(FULL_HISTS_vector[i]);

}



    hist_totalEMPTY->Scale(POT_scale_toFULL);
    hist_totalFULL->Add(hist_totalEMPTY,-1);
    hist_totalFULL->Scale(POT_scale_toFULL_MC_ToDATA);
    hist_totalFULL->Scale(1.0,"width");
    legend->AddEntry(hist_totalFULL, "Total");

     int n = xaxislabel.length();
     char xtitle[n+1];
      strcpy(xtitle, xaxislabel.c_str());
      hist_totalFULL->GetXaxis()->SetTitle(xtitle);
      hist_totalFULL->GetYaxis()->SetTitle("NEvents");
      hist_totalFULL->GetXaxis()->CenterTitle();
      hist_totalFULL->GetXaxis()->SetTitleSize(0.038);

      datahist_FULL->Scale(1.0,"width");
      datahist_FULL->SetMarkerStyle(20);
      datahist_FULL->SetMarkerSize(1.25);
      if(hist_totalFULL->GetMaximum() > datahist_FULL->GetMaximum()){hist_totalFULL->SetMaximum(hist_totalFULL->GetMaximum() * 1.45);}
      else{hist_totalFULL->SetMaximum(datahist_FULL->GetMaximum() * 1.45);}

      hist_totalFULL->Draw("HIST");
      mystack[0]->Draw("HIST SAME");
      datahist_FULL->Draw(" SAME");
      legend->Draw();

     plot->AddHistoTitle(FinalTitle, .04);
     plot->WritePreliminary("TL", .035, 0, 0, false);

     can -> Print(pdf);


}//ENd of DrawStack_paricle

/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////

void DrawStack_Muon_Particle_FUll_EMPTY_WITHDATA(
  bool my_debug, TFile *inputFile_FULL,
  TFile *inputFile_EMPTY,
  TFile *inputFile_DATA_FULL,
  TFile *inputFile_DATA_EMPTY,
  Pot_MapList POT_MC ,Pot_MapList POT_DATA,
  SecondTrkVar second_Trk_type,
  ME_helium_Playlists PlayListFULL,
  ME_helium_Playlists PlayListEmpty, int doShape,
  int logScale, std::string Hist_name_addON,
  MnvPlotter *plot, TCanvas *can, const char *pdf)
{

  // set up legend, assuming this function only ever plots oodles of stacked histograms
  double x1, x2, y1, y2;
  plot->DecodeLegendPosition(x1, y1, x2, y2, "R", 7, 7, .03);
  TLegend *legend = new TLegend(x1 + .145, y1 + .2, x2 + .16, y2 + .2);
  legend->SetNColumns(1);
  legend->SetTextSize(.03);
  legend->SetFillColor(0);

  auto Particle_vector = GetParticle_typeList();
  Particle_MnvH1D_Map FULL_HISTS,EMPTY_HISTS;
  std::vector<MnvH1D*>  FULL_HISTS_vector,EMPTY_HISTS_vector;

  auto xaxislabel = GetsecondTrk_AXIS_TitleName(second_Trk_type);
  auto Var_Name =  GetsecondTrakHistName(second_Trk_type) + Hist_name_addON;
  auto Var_title =  GetsecondTrkTitleName(second_Trk_type);
  auto Playlist_name_FULL = GetPlaylist_InitialName(PlayListFULL);
  auto Playlist_name_EMPTY = GetPlaylist_InitialName(PlayListEmpty);

  auto Var_Name_DATA = GetsecondTrakHistName_DATA_Name(second_Trk_type);
  int n_Var_Name_DATA = Var_Name_DATA.length();
  char Var_Name_DATA_char[n_Var_Name_DATA+1];
  strcpy( Var_Name_DATA_char,Var_Name_DATA.c_str());
  PlotUtils::MnvH1D* datahist_FULL = (MnvH1D*)inputFile_DATA_FULL->Get(Var_Name_DATA_char);
  PlotUtils::MnvH1D* datahist_EMPTY = (MnvH1D*)inputFile_DATA_EMPTY->Get(Var_Name_DATA_char);
  //PlotUtils::MnvH1D* datahist_ALONE_FULL = (MnvH1D*)inputFile_DATA_FULL->Get(Var_Name_DATA_char);
  //PlotUtils::MnvH1D* datahist_ALONE_EMPTY = (MnvH1D*)inputFile_DATA_EMPTY->Get(Var_Name_DATA_char);

  auto POT_scale_toFULL= POT_MC[PlayListFULL]/POT_MC[PlayListEmpty];
  auto POT_scale_toFULLDATA= POT_DATA[PlayListFULL]/POT_DATA[PlayListEmpty];
  auto POT_scale_toFULL_MC_ToDATA= POT_DATA[PlayListFULL]/POT_MC[PlayListFULL];


  std::cout<<"scale to data = "<< POT_scale_toFULLDATA<<std::endl;
  datahist_EMPTY->Scale(POT_scale_toFULLDATA);
  datahist_FULL->Add(datahist_EMPTY,-1);
  legend->AddEntry(datahist_FULL, "DATA");

  std::cout<< "POT scaler = "<<  POT_scale_toFULL<<std::endl;

  auto Fulltitle =   Var_title  + "(DataOverlay) (" + Playlist_name_FULL + " - " + Playlist_name_EMPTY + ") ";
  int Fulltitle_n = Fulltitle.length();
  char FinalTitle[Fulltitle_n + 1];
  strcpy(FinalTitle, Fulltitle.c_str());



  MnvH1D *hist_totalFULL;
  MnvH1D *hist_totalEMPTY;
  THStack *mystack[2];
  mystack[0] = new THStack("hs0", "Stacked");
  int fillCol=0;


  TIter Iter(inputFile_FULL->GetListOfKeys());
  TObject *key;

  TIter Iter_empty(inputFile_EMPTY->GetListOfKeys());
  TObject *keyEMPTY;


  std::cout<<"first Loop "<<std::endl;

  while((key=Iter()))
  {
    const std::string histName = key->GetName();
    //std::cout<<"HistName = " << histName << std::endl;

    for(auto Particle: Particle_vector){auto ParticleName = GetNameParticle(Particle);//end of loop

      if(histName.find((Var_Name + "_particle_"+ ParticleName)) != std::string::npos  ){

        std::cout<<" Total = " <<  Var_Name + "_particle_"+ ParticleName<< std::endl;
        std::cout<<" Total(Key) = " << histName<< std::endl;
        hist_totalFULL = dynamic_cast< MnvH1D*>(((TKey*)key)->ReadObj());

      }
      else if(histName.find((ParticleName+"_"+ Var_Name + "_particle")) != std::string::npos) //Then this is a NeutrinoEnergy histogram for some material
      {
        std::cout<<"Inside else IF  = " << ParticleName+"_"+ Var_Name + "_particle"<<std::endl;

        auto hist = dynamic_cast<MnvH1D*>(((TKey*)key)->ReadObj());
        hist -> SetFillColor(CCNuPionIncPlotting::fill_colors[fillCol]);
        hist -> SetLineColor(CCNuPionIncPlotting::fill_colors[fillCol]);
        hist -> SetFillStyle(1001);
        hist -> SetLineWidth(1);
        fillCol++;
        if(hist == nullptr) //nullptr is the same as NULL effectively, but it does some cool type conversion for std::unique_ptr<>
        {
          std::cerr << histName << " is not a TH1, but it is a neutrinoEnergy histogram!  Skipping " << histName << "...\n";
        }

        //hist->Scale(1,"width");
        //mystack[0]->Add(hist); //This might want you to derefence hist first
        //FULL_HISTS.insert({Particle, hist});
        FULL_HISTS_vector.push_back(hist);
        int n = ParticleName.length();
        char char_array[n + 1];
        strcpy(char_array, ParticleName.c_str());
        legend->AddEntry(hist, char_array);
      }
    }
  }

std::cout<<"2nd Loop "<<std::endl;

while((keyEMPTY=Iter_empty()))
{
  const std::string histName = keyEMPTY->GetName();
  //std::cout<<"HistName = " << histName << std::endl;
  for(auto Particle: Particle_vector){auto ParticleName = GetNameParticle(Particle);//end of loop
    //  std::cout<<"Loop2 Particle ="<<Particle<<std::endl;
    if(histName.find((Var_Name + "_interaction_"+ ParticleName)) != std::string::npos  ){

      std::cout<<" Total = " <<  Var_Name + "_particle_"+ ParticleName<< std::endl;
      std::cout<<" Total(Key) = " << histName<< std::endl;
      hist_totalEMPTY = dynamic_cast< MnvH1D*>(((TKey*)keyEMPTY)->ReadObj());

    }
    else if(histName.find((ParticleName+"_"+ Var_Name + "_particle")) != std::string::npos) //Then this is a NeutrinoEnergy histogram for some material
    {
      std::cout<<"Inside else IF  = " << ParticleName+"_"+ Var_Name + "_particle"<<std::endl;

      auto hist = dynamic_cast<MnvH1D*>(((TKey*)keyEMPTY)->ReadObj());
      hist -> SetFillColor(CCNuPionIncPlotting::fill_colors[fillCol]);
      hist -> SetLineColor(CCNuPionIncPlotting::fill_colors[fillCol]);
      hist -> SetFillStyle(1001);
      hist -> SetLineWidth(1);
      fillCol++;
      if(hist == nullptr) //nullptr is the same as NULL effectively, but it does some cool type conversion for std::unique_ptr<>
      {
        std::cerr << histName << " is not a TH1, but it is a neutrinoEnergy histogram!  Skipping " << histName << "...\n";
      }

      EMPTY_HISTS_vector.push_back(hist);

    }
  }
}


if(EMPTY_HISTS_vector.size()!=FULL_HISTS_vector.size()){std::cout<<"size BAD"<<std::endl;}
else{std::cout<<"Size of vectors good "<<std::endl;}
std::cout<<"3rd Loop "<<std::endl;
//int count=0;


for(int i=0; i != FULL_HISTS_vector.size(); i++){
  //auto ParticleName = GetNameParticle(Particle_vector[i+1]);
  EMPTY_HISTS_vector[i]->Scale(POT_scale_toFULL);
  FULL_HISTS_vector[i]->Add(EMPTY_HISTS_vector[i],-1);
  FULL_HISTS_vector[i]->Scale(POT_scale_toFULL_MC_ToDATA);
  FULL_HISTS_vector[i]->Scale(1,"width");
  mystack[0]->Add(FULL_HISTS_vector[i]);
}


hist_totalEMPTY->Scale(POT_scale_toFULL);
hist_totalFULL->Add(hist_totalEMPTY,-1);
hist_totalFULL->Scale(POT_scale_toFULL_MC_ToDATA);
hist_totalFULL->Scale(1.0,"width");
legend->AddEntry(hist_totalFULL, "Total");

int n = xaxislabel.length();
char xtitle[n+1];
strcpy(xtitle, xaxislabel.c_str());
hist_totalFULL->GetXaxis()->SetTitle(xtitle);
hist_totalFULL->GetYaxis()->SetTitle("NEvents");
hist_totalFULL->GetXaxis()->CenterTitle();
hist_totalFULL->GetXaxis()->SetTitleSize(0.038);

datahist_FULL->Scale(1.0,"width");
datahist_FULL->SetMarkerStyle(20);
datahist_FULL->SetMarkerSize(1.25);
if(hist_totalFULL->GetMaximum() > datahist_FULL->GetMaximum()){hist_totalFULL->SetMaximum(hist_totalFULL->GetMaximum() * 1.45);}
else{hist_totalFULL->SetMaximum(datahist_FULL->GetMaximum() * 1.45);}

hist_totalFULL->Draw("HIST");
mystack[0]->Draw("HIST SAME");
datahist_FULL->Draw(" SAME");
legend->Draw();

plot->AddHistoTitle(FinalTitle, .04);
plot->WritePreliminary("TL", .035, 0, 0, false);
can -> Print(pdf);

}//ENd of DrawStack_paricle

//////////////////////////////////////////////////////////////////////////////
//////
//////////////////////////////////////////////////////////////////////////////

void DrawCVAndError_FromTFile(
  TFile *inputFile, char *histoName,
  char *histotitle ,std::string xaxislabel, std::string label){
  std::cout<<"trying HisName = "<< histoName<<std::endl;
  MnvH1D *hist = (MnvH1D*)inputFile -> Get(histoName);
  std::string yaxislabel = "Nevents";
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  hist->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));
  hist->SetTitle(histotitle);
  PlotUtils::MnvH1D* datahist =new PlotUtils::MnvH1D("adsf", "", nbins, xmin, xmax);
  bool statPlusSys           = true;
  int mcScale                = 1.;
  bool useHistTitles         = false;
  hist->Scale(1,"width");
  mnvPlotter.DrawDataMCWithErrorBand(datahist, hist, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);
  //mnvPlotter.DrawMCWithErrorBand(hist); //I think that this call only shows stat errors.
  mnvPlotter.AddHistoTitle(histotitle);
  std::string plotname = Form("%s",label.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");
  //PlotErrorSummaryNew(hist, plotname, histotitle, xaxislabel.c_str(), &cE,&mnvPlotter);
  std::vector<bool> Print_Vector = Print_Systematics(0);
  mnvPlotter.legend_n_columns = 2;
  // PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);
  PlotErrorSummaryNew(hist, plotname, histotitle, xaxislabel.c_str(), &cE, &mnvPlotter,true, false);
  mnvPlotter.legend_n_columns = 1;


}

/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////


void DrawCVAndError_FromTFile(bool PrintallErrors ,TFile *inputFile,
     char *histoName, char *histotitle ,std::string xaxislabel, std::string label)
{
  std::cout<<"trying HisName = "<< histoName<<std::endl;
  MnvH1D *hist = (MnvH1D*)inputFile -> Get(histoName);
  std::string yaxislabel = "Nevents";
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  hist->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));
  hist->SetTitle(histotitle);
  PlotUtils::MnvH1D* datahist =new PlotUtils::MnvH1D("adsf", "", nbins, xmin, xmax);
  bool statPlusSys           = true;
  int mcScale                = 1.;
  bool useHistTitles         = false;
  hist->Scale(1,"width");
  mnvPlotter.DrawDataMCWithErrorBand(datahist, hist, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);
  //mnvPlotter.DrawMCWithErrorBand(hist); //I think that this call only shows stat errors.
  mnvPlotter.AddHistoTitle(histotitle);
  std::string plotname = Form("%s",label.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");
  //PlotErrorSummaryNew(hist, plotname, histotitle, xaxislabel.c_str(), &cE,&mnvPlotter);
  std::vector<bool> Print_Vector = Print_Systematics(0);
  mnvPlotter.legend_n_columns = 2;
  // PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);
  PlotErrorSummaryNew(hist, plotname, histotitle, xaxislabel.c_str(), &cE, &mnvPlotter,true,PrintallErrors);
  mnvPlotter.legend_n_columns = 1;


}

/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////

void DrawCVAndError_FromHistPointer(
  MnvH1D *hist_input, char *histotitle,
   std::string xaxislabel, std::string yaxislabel,
  std::string label, bool doBinwidth, bool MakeXaxisLOG)
{

  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  MnvH1D *hist =  (MnvH1D*)hist_input->Clone(uniq());
  hist->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));
  if(doBinwidth==true){hist->Scale(1,"width");}
  hist->SetTitle(histotitle);
  PlotUtils::MnvH1D* datahist =new PlotUtils::MnvH1D("adsf", "", nbins, xmin, xmax);
  bool statPlusSys           = true;
  int mcScale                = 1.;
  bool useHistTitles         = false;


  if(MakeXaxisLOG==true){
    gPad->SetLogx();
  }
  else {
    gPad->SetLogx(0);
  }



  mnvPlotter.draw_normalized_to_bin_width=false;

  mnvPlotter.DrawDataMCWithErrorBand(datahist, hist, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);
  mnvPlotter.AddHistoTitle(histotitle, .035);
  std::string plotname = Form("%s",label.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");
  mnvPlotter.legend_n_columns = 2;
  mnvPlotter.axis_maximum = .3;
  mnvPlotter.axis_title_offset_y = 1.2;
  mnvPlotter.legend_text_size = mnvPlotter.legend_text_size * .8;
  // PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);
  PlotErrorSummaryNew(hist, plotname, histotitle, xaxislabel.c_str(), &cE, &mnvPlotter,true,false);
  mnvPlotter.legend_n_columns = 1;


  if(MakeXaxisLOG==true){
    gPad->SetLogx(0);
  }

  if(doBinwidth==true){mnvPlotter.draw_normalized_to_bin_width= false;}


}
//////////////////////////////////////////////////////////////////////////////
//////
//////////////////////////////////////////////////////////////////////////////
void DrawCovarientMatrix_FromHistPointer(
  MnvH1D *hist, char *histotitle,
  std::string xaxislabel, std::string yaxislabel, std::string pdf_label)
{

  TCanvas *can = new TCanvas("DrawCovarientMatrix_FromHistPointer:Can");
  MnvPlotter *mnvPlotter = new MnvPlotter();
  mnvPlotter->ApplyStyle( PlotUtils::kCCInclusiveHeliumStyle );
  char pdf_char[pdf_label.length()+1];
  strcpy( pdf_char,pdf_label.c_str());

  char Title[1024];
  //TH2D h_TotalCorrelationMatrix = hist->GetTotalCorrelationMatrixTH2D();
  auto matrix = hist->GetTotalCorrelationMatrix();
  TH2D* convertedCorrMx = new TH2D(matrix);
  convertedCorrMx->GetZaxis()->SetRangeUser(-1.0,1.0);

  auto matrix_errormatrix = hist->GetTotalErrorMatrix();
  TH2D* TotalErrorMx = new TH2D(matrix_errormatrix);
  TotalErrorMx->SetMaximum();
  TotalErrorMx->SetMinimum();

//TH1D h_TotalError =GetTotalError();
  //hist->SetTitle(histotitle);

  sprintf(Title,"Total Correlation Matrix: %s ",histotitle);
  Draw2DHist(convertedCorrMx,  "Bin N", "Bin N","", Title,  pdf_char, can, mnvPlotter);

  sprintf(Title,"Total Error Matrix: %s ",histotitle);
  Draw2DHist(TotalErrorMx,  "Bin N", "Bin N","", Title,  pdf_char, can, mnvPlotter);


delete can;
//delete mnvPlotter;

}



/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////

void DrawCVAndError_FromHistPointer(
  MnvH1D *hist_input, MnvH1D* datahist_input,
  MnvH1D *hist_inputBackground, MnvH1D* datahist_inputBackground,
  char *histotitle, std::string xaxislabel, std::string yaxislabel,
  std::string label, bool doBinwidth, bool MakeXaxisLOG,
  bool printErrors, double Ymax, bool PrintALLerrorGroups){

  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  MnvH1D *hist = (MnvH1D *)hist_input->Clone(uniq());
  hist->SetTitle("Minerva v1 (^{4}He Full)");
  MnvH1D* datahist = (MnvH1D *)datahist_input->Clone(uniq());
  datahist->SetTitle("Data (^{4}He Full)");
  MnvH1D *histBG = (MnvH1D *)hist_inputBackground->Clone(uniq());
  histBG->SetTitle("Minerva v1 (^{4}He Empty)");
  MnvH1D *datahistBG = (MnvH1D *)datahist_inputBackground->Clone(uniq());
  datahistBG->SetTitle("Data ((^{4}He Empty)");
  if(doBinwidth==true){
    hist->Scale(1,"width");
    datahist->Scale(1,"width");
    histBG->Scale(1,"width");
    datahistBG->Scale(1,"width");

  }


  TCanvas cE ("c1","c1");
  hist->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));
  //hist->SetTitleOffset(0.05);
  //hist->SetTitle(histotitle);

if(Ymax==-99){



  Ymax = datahist->GetMaximum()*1.35;
}

  hist->SetMaximum(Ymax);
  hist->GetYaxis()->CenterTitle();
  hist->GetYaxis()->SetLabelSize(0.05);
  datahist->SetMaximum(Ymax);
  bool statPlusSys           = true;
  int mcScale                = 1.;
  bool useHistTitles         = true;

  if(MakeXaxisLOG==true){
    gPad->SetLogx();
  }
  else {
    gPad->SetLogx(0);
  }
  mnvPlotter.axis_title_size_x = 0.04;
  mnvPlotter.axis_title_offset_y = 1.2;
  mnvPlotter.axis_maximum = Ymax;
  mnvPlotter.axis_title_size_y = 0.05;
  mnvPlotter.axis_label_size =  0.028;
  mnvPlotter.axis_draw_grid_x = true;
  mnvPlotter.axis_draw_grid_y = true;
  mnvPlotter.legend_offset_x = .18;
  mnvPlotter.legend_text_size = mnvPlotter.legend_text_size * .6;
  //mnvPlotter.draw_normalized_to_bin_width=doBinwidth;
  mnvPlotter.DrawDataMCWithErrorBand(datahist, hist, mcScale, "TR", useHistTitles, datahistBG, histBG, false, statPlusSys);
  mnvPlotter.AddHistoTitle(histotitle);
  std::string plotname = Form("%s",label.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");
  if(printErrors==true){
    mnvPlotter.legend_n_columns = 2;
    mnvPlotter.axis_title_offset_y = 1.2;
    mnvPlotter.axis_title_size_y = 0.03;
    mnvPlotter.axis_title_size_x = 0.038;
    mnvPlotter.axis_label_size = 0.03;
    mnvPlotter.axis_maximum = .3;
    mnvPlotter.axis_minimum = 0;
    // PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);
    PlotErrorSummaryNew(hist, plotname, histotitle, xaxislabel.c_str(), &cE, &mnvPlotter, true, PrintALLerrorGroups);
    mnvPlotter.legend_n_columns = 1;
  }

  if(MakeXaxisLOG==true){
    gPad->SetLogx(0);
  }

  if(doBinwidth==true){mnvPlotter.draw_normalized_to_bin_width= false;}


}

/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////


void DrawCVAndError_FromHistPointer(
  MnvH1D *hist_input, MnvH1D* datahist_input,
  char *histotitle, std::string xaxislabel, std::string yaxislabel,
  std::string label, bool doBinwidth,
  bool MakeXaxisLOG, bool printErrors, double Ymax, bool PrintALLerrorGroups){

  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  MnvH1D *hist = (MnvH1D *)hist_input->Clone(uniq());
  MnvH1D* datahist = (MnvH1D *)datahist_input->Clone(uniq());

  TCanvas cE ("c1","c1");
  hist->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));
  hist->SetTitleOffset(0.05);
  hist->SetTitle(histotitle);
  hist->SetMaximum(Ymax);
  hist->GetYaxis()->CenterTitle();
  hist->GetYaxis()->SetLabelSize(0.05);
  datahist->SetMaximum(Ymax);
  bool statPlusSys           = true;
  int mcScale                = 1.;
  bool useHistTitles         = false;

  if(MakeXaxisLOG==true){
    gPad->SetLogx();
  }
  else {
    gPad->SetLogx(0);
  }
  mnvPlotter.axis_title_size_x = 0.04;
  mnvPlotter.axis_title_offset_y = 1.2;
  //mnvPlotter.axis_maximum = Ymax;
  mnvPlotter.axis_title_size_y = 0.05;
  mnvPlotter.axis_label_size =  0.028;
  mnvPlotter.axis_draw_grid_x = true;
  mnvPlotter.axis_draw_grid_y = true;
  mnvPlotter.draw_normalized_to_bin_width=false;

  if(doBinwidth==true){
    datahist->Scale(1,"width");
    hist->Scale(1,"width");
  }
  mnvPlotter.DrawDataMCWithErrorBand(datahist, hist, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);
  mnvPlotter.AddHistoTitle(histotitle);
  std::string plotname = Form("%s",label.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");
  if(printErrors==true){
    mnvPlotter.legend_n_columns = 2;

    mnvPlotter.axis_title_size_y = 0.03;
    mnvPlotter.axis_title_size_x = 0.038;

    mnvPlotter.axis_title_offset_y = 1.2;
    mnvPlotter.legend_text_size = mnvPlotter.legend_text_size * .8;
    mnvPlotter.axis_label_size = 0.025;
    mnvPlotter.axis_maximum = .3;
    mnvPlotter.axis_minimum = 0;
    // PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);
    PlotErrorSummaryNew(hist, plotname, histotitle, xaxislabel.c_str(), &cE, &mnvPlotter, true, PrintALLerrorGroups);
    mnvPlotter.legend_n_columns = 1;
  }

  if(MakeXaxisLOG==true){
    gPad->SetLogx(0);
  }

  if(doBinwidth==true){mnvPlotter.draw_normalized_to_bin_width= false;}


}

/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////


void DrawCVAndError_FromHistPointer(
  MnvH1D *hist_input, char *histotitle,
  std::string xaxislabel, std::string yaxislabel,
  std::string label, bool doBinwidth,
  bool MakeXaxisLOG, bool printErrors, double Ymax){

    PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
    MnvH1D *hist = (MnvH1D *)hist_input->Clone(uniq());
    TCanvas cE ("c1","c1");
    hist->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
    hist->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));
    hist->SetTitleOffset(0.05);
    hist->SetTitle(histotitle);
    hist->GetYaxis()->CenterTitle();
    hist->GetYaxis()->SetLabelSize(0.05);
    hist->SetMaximum(Ymax);
    PlotUtils::MnvH1D* datahist =new PlotUtils::MnvH1D("adsf", "", nbins, xmin, xmax);
    datahist->SetMaximum(Ymax);
    bool statPlusSys           = true;
    int mcScale                = 1.;
    bool useHistTitles         = false;

    if(MakeXaxisLOG==true){
      gPad->SetLogx();
    }
    else {
      gPad->SetLogx(0);
    }


    mnvPlotter.axis_title_size_x = 0.04;
    mnvPlotter.axis_title_offset_y = 1.2;
    mnvPlotter.axis_maximum = Ymax;
    mnvPlotter.axis_title_size_y = 0.05;
    mnvPlotter.axis_label_size =  0.028;
    mnvPlotter.axis_title_size_y = 0.05;
    mnvPlotter.axis_draw_grid_x = true;
    mnvPlotter.axis_draw_grid_y = true;
    mnvPlotter.draw_normalized_to_bin_width=false;
    if(doBinwidth==true){hist->Scale(1,"width");}
    mnvPlotter.DrawDataMCWithErrorBand(datahist, hist, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);
    mnvPlotter.AddHistoTitle(histotitle,.038);
    mnvPlotter.WritePreliminary("TR", .03, 0, 0, false);
    std::string plotname = Form("%s",label.c_str());
    mnvPlotter.MultiPrint(&cE, plotname, "pdf");

    if(printErrors==true){
      mnvPlotter.legend_n_columns = 2;
      mnvPlotter.axis_title_offset_y = 1.2;
      mnvPlotter.axis_title_size_x = 0.038;
      mnvPlotter.axis_title_size_y = 0.03;
      mnvPlotter.axis_label_size = 0.03;
      mnvPlotter.axis_maximum = .3;
      mnvPlotter.axis_minimum = 0;
      PlotErrorSummaryNew(hist, plotname, histotitle, xaxislabel.c_str(), &cE, &mnvPlotter,true,false);
      mnvPlotter.legend_n_columns = 1;
    }

    if(MakeXaxisLOG==true){
      gPad->SetLogx(0);
    }

    if(doBinwidth==true){mnvPlotter.draw_normalized_to_bin_width= false;}


  }
/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////
void DrawCVAndError_FromHistPointer_FluxRatio(
  MnvH1D *hist_input, char *histotitle,
  std::string xaxislabel, std::string yaxislabel,
  std::string label, bool doBinwidth,
  bool MakeXaxisLOG, bool printErrors, double Ymax){

    PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
    MnvH1D *hist = (MnvH1D *)hist_input->Clone(uniq());
    TCanvas cE ("c1","c1");
    hist->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
    hist->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));
    hist->SetTitleOffset(0.05);
    hist->SetTitle(histotitle);
    hist->GetYaxis()->CenterTitle();
    hist->GetYaxis()->SetLabelSize(0.05);
    hist->SetMaximum(Ymax);
    PlotUtils::MnvH1D* datahist =new PlotUtils::MnvH1D("adsf", "", nbins, xmin, xmax);
    datahist->SetMaximum(Ymax);
    bool statPlusSys           = true;
    int mcScale                = 1.;
    bool useHistTitles         = false;

    if(MakeXaxisLOG==true){
      gPad->SetLogx();
    }
    else {
      gPad->SetLogx(0);
    }


    mnvPlotter.axis_title_size_x = 0.04;
    mnvPlotter.axis_title_offset_y = 1.2;
    mnvPlotter.axis_maximum = Ymax;
    mnvPlotter.axis_title_size_y = 0.05;
    mnvPlotter.axis_label_size =  0.028;
    mnvPlotter.axis_title_size_y = 0.05;
    mnvPlotter.axis_draw_grid_x = true;
    mnvPlotter.axis_draw_grid_y = true;
    mnvPlotter.draw_normalized_to_bin_width=false;
    if(doBinwidth==true){hist->Scale(1,"width");}
    mnvPlotter.DrawDataMCWithErrorBand(datahist, hist, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);
    mnvPlotter.AddHistoTitle(histotitle,.038);
    mnvPlotter.WritePreliminary("TR", .03, 0, 0, false);
    std::string plotname = Form("%s",label.c_str());
    mnvPlotter.MultiPrint(&cE, plotname, "pdf");

    if(printErrors==true){
      mnvPlotter.legend_n_columns = 2;
      mnvPlotter.axis_title_offset_y = 1.2;
      mnvPlotter.axis_title_size_x = 0.038;
      mnvPlotter.axis_title_size_y = 0.03;
      mnvPlotter.axis_label_size = 0.03;
      mnvPlotter.axis_maximum = .3;
      mnvPlotter.axis_minimum = 0;
      PlotErrorSummaryNew(hist, plotname, histotitle, xaxislabel.c_str(), &cE, &mnvPlotter,true,false);
      mnvPlotter.legend_n_columns = 1;
    }

    if(MakeXaxisLOG==true){
      gPad->SetLogx(0);
    }

    if(doBinwidth==true){mnvPlotter.draw_normalized_to_bin_width= false;}


  }
/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////
void DrawCVAndError_FromHistPointer(
  MnvH1D *hist_input, char *histotitle,
  std::string xaxislabel, std::string yaxislabel,
  std::string label, bool doBinwidth, bool MakeXaxisLOG, double maxY)
{
    MnvH1D *hist = (MnvH1D *)hist_input->Clone(uniq());
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  hist->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));
  hist->GetYaxis()->CenterTitle();
  hist->SetTitle(histotitle);
  hist->SetMaximum(maxY);
  PlotUtils::MnvH1D* datahist =new PlotUtils::MnvH1D("adsf", "", nbins, xmin, xmax);
  bool statPlusSys           = true;
  int mcScale                = 1.;
  bool useHistTitles         = false;


  if(MakeXaxisLOG==true){
    gPad->SetLogx();
  }
  else {
    gPad->SetLogx(0);
  }

  mnvPlotter.draw_normalized_to_bin_width=false;
  if(doBinwidth==true){hist->Scale(1,"width");}
  mnvPlotter.DrawDataMCWithErrorBand(datahist, hist, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);
  mnvPlotter.AddHistoTitle(histotitle);
  std::string plotname = Form("%s",label.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");
  mnvPlotter.legend_n_columns = 2;
  mnvPlotter.axis_title_offset_y = 1.2;
  mnvPlotter.axis_title_size_x = 0.038;
  mnvPlotter.axis_title_size_y = 0.03;
  mnvPlotter.axis_label_size = 0.03;
  mnvPlotter.axis_maximum = .3;
  mnvPlotter.axis_minimum = 0;
  // PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);
  PlotErrorSummaryNew(hist, plotname, histotitle, xaxislabel.c_str(), &cE, &mnvPlotter,true,false);
  mnvPlotter.legend_n_columns = 1;


  if(MakeXaxisLOG==true){
    gPad->SetLogx(0);
  }

  if(doBinwidth==true){mnvPlotter.draw_normalized_to_bin_width= false;}


}
/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////
void DrawCVAndError_FromHistPointer(
  MnvH1D *hist_input, char *histotitle,
  std::string xaxislabel, std::string yaxislabel,
  std::string label, bool doBinwidth, bool MakeXaxisLOG, bool MakeYaxisLOG)
{
    MnvH1D *hist = (MnvH1D *)hist_input->Clone(uniq());
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  hist->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));
  hist->GetYaxis()->CenterTitle();
  hist->SetTitle(histotitle);
  PlotUtils::MnvH1D* datahist =new PlotUtils::MnvH1D("adsf", "", nbins, xmin, xmax);
  bool statPlusSys           = true;
  int mcScale                = 1.;
  bool useHistTitles         = false;


  if(MakeXaxisLOG==true){
    gPad->SetLogx();
  }
  else {
    gPad->SetLogx(0);
  }


  if(MakeYaxisLOG==true){
    gPad->SetLogy();
    hist->SetMinimum(1);
  }
  else {
    gPad->SetLogx(0);
  }

  hist->SetMaximum(hist->GetMaximum()* 1.25);

  mnvPlotter.draw_normalized_to_bin_width=false;
  if(doBinwidth==true){hist->Scale(1,"width");}
  mnvPlotter.DrawDataMCWithErrorBand(datahist, hist, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);
  mnvPlotter.AddHistoTitle(histotitle);
  std::string plotname = Form("%s",label.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");

  if(MakeXaxisLOG==true){
    gPad->SetLogx(0);
  }
  if(MakeYaxisLOG==true){
    gPad->SetLogy(0);
}

  if(doBinwidth==true){mnvPlotter.draw_normalized_to_bin_width= false;}


}
/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////
void DrawCVAndError_FromHIST(MnvH1D *hist,
   char *histotitle ,std::string xaxislabel,std::string yaxislabel,
  std::string pdf_name, bool Setgrid)
{
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  if(Setgrid==true){cE.SetGrid();}
  else if (Setgrid==false){cE.Clear();}
  hist->GetXaxis()->SetTitleSize(0.035);
  hist->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));
  hist->GetYaxis()->CenterTitle();
  hist->SetTitle(histotitle);
  PlotUtils::MnvH1D* datahist =new PlotUtils::MnvH1D("adsf", "", nbins, xmin, xmax);
  bool statPlusSys           = true;
  int mcScale                = 1.;
  bool useHistTitles         = false;

  mnvPlotter.DrawDataMCWithErrorBand(datahist, hist, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);

  mnvPlotter.AddHistoTitle(histotitle);
  mnvPlotter.WritePreliminary("TR", .03, 0, 0, false);
  std::string plotname = Form("%s",pdf_name.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");
  //PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);

  mnvPlotter.legend_n_columns = 2;
  // PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);
  PlotErrorSummaryNew(hist, plotname, histotitle, xaxislabel.c_str(), &cE, &mnvPlotter,true,false);
  mnvPlotter.legend_n_columns = 1;


}

/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////

void DrawCVAndError_FromHIST(bool PrintALLerrorGroups,
   MnvH1D *hist_input, char *histotitle,
   std::string xaxislabel,std::string yaxislabel,
   std::string pdf_name, bool Setgrid,
   bool doBinwidth, bool SetYlimits,  double Ymin,  double Ymax)
   {
    MnvH1D *hist = (MnvH1D *)hist_input->Clone(uniq());
    PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
    TCanvas cE ("c1","c1");
    if(Setgrid==true){cE.SetGrid();}
    else if (Setgrid==false){cE.Clear();}
    hist->GetXaxis()->SetTitleSize(0.035);
    hist->GetYaxis()->SetTitleSize(0.015);
    hist->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
    hist->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));
    hist->GetYaxis()->CenterTitle();
    hist->SetTitle(histotitle);

    PlotUtils::MnvH1D* datahist =new PlotUtils::MnvH1D("adsf", "", nbins, xmin, xmax);
    bool statPlusSys           = false;
    int mcScale                = 1.;
    bool useHistTitles         = true;


    if(SetYlimits==true){
      hist->SetMaximum(Ymax);
      hist->SetMaximum(Ymin);
      datahist->SetMaximum(Ymax);
      datahist->SetMaximum(Ymin);
      mnvPlotter.axis_minimum = Ymin;
      mnvPlotter.axis_maximum = Ymax;
    }


    mnvPlotter.axis_title_size_x = 0.038;
    mnvPlotter.axis_title_size_y = 0.038;
    mnvPlotter.axis_label_size = 0.025;
    mnvPlotter.axis_title_offset_y = 1.5;
    mnvPlotter.draw_normalized_to_bin_width=false;

    if(doBinwidth==true){hist->Scale(1,"width");}
    mnvPlotter.DrawDataMCWithErrorBand(datahist, hist, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);
    //mnvPlotter.DrawMCWithErrorBand(hist); //I think that this call only shows stat errors.
    mnvPlotter.AddHistoTitle(histotitle, .03);
    mnvPlotter.WritePreliminary("TR", .03, 0, 0, false);
    std::string plotname = Form("%s",pdf_name.c_str());
    mnvPlotter.MultiPrint(&cE, plotname, "pdf");
    //PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);

    mnvPlotter.legend_n_columns = 2;

    if(SetYlimits==true){
      mnvPlotter.axis_minimum = 0.0;
      mnvPlotter.axis_maximum = .02;
    }
    // PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);
    PlotErrorSummaryNew(hist, plotname, histotitle, xaxislabel.c_str(), &cE, &mnvPlotter,true, PrintALLerrorGroups);
    mnvPlotter.legend_n_columns = 1;

    if(doBinwidth==true){mnvPlotter.draw_normalized_to_bin_width= false;}
  }

  /////////////////////////////////////////////////////////////////////////////////
  //
  /////////////////////////////////////////////////////////////////////////////////

  void DrawCVAndError_FromHIST(bool PrintALLerrorGroups , MnvH1D *hist_input, char *histotitle ,std::string xaxislabel,std::string yaxislabel,
    std::string pdf_name, bool Setgrid , bool doBinwidth, bool SetYlimits,  double Ymin,  double Ymax ,const double cut_location,
     const double y1_arrow, const double y2_arrow, const double arrow_length,  const std::string arrow_direction  )
    {

      MnvH1D *hist = (MnvH1D *)hist_input->Clone(uniq());
      PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
      TCanvas cE ("c1","c1");
      if(Setgrid==true){cE.SetGrid();}
      else if (Setgrid==false){cE.Clear();}
      hist->GetXaxis()->SetTitleSize(0.035);
      hist->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
      hist->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));
      hist->GetYaxis()->CenterTitle();
      hist->SetTitle(histotitle);

      PlotUtils::MnvH1D* datahist =new PlotUtils::MnvH1D("adsf", "", nbins, xmin, xmax);
      bool statPlusSys           = true;
      int mcScale                = 1.;
      bool useHistTitles         = false;


      if(SetYlimits==true){
        hist->SetMaximum(Ymax);
        hist->SetMaximum(Ymin);
        datahist->SetMaximum(Ymax);
        datahist->SetMaximum(Ymin);
        mnvPlotter.axis_minimum = Ymin;
        mnvPlotter.axis_maximum = Ymax;
      }

      mnvPlotter.axis_title_size_y = 0.05;
      mnvPlotter.axis_label_size =  0.028;

      mnvPlotter.draw_normalized_to_bin_width=false;
      if(doBinwidth==true){hist->Scale(1,"width");}
      mnvPlotter.DrawDataMCWithErrorBand(datahist, hist, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);
      mnvPlotter.AddCutArrow(cut_location, y1_arrow,  y2_arrow,  arrow_length, arrow_direction);
      //mnvPlotter.DrawMCWithErrorBand(hist); //I think that this call only shows stat errors.
      mnvPlotter.AddHistoTitle(histotitle);
      mnvPlotter.WritePreliminary("TR", .03, 0, 0, false);
      std::string plotname = Form("%s",pdf_name.c_str());
      mnvPlotter.MultiPrint(&cE, plotname, "pdf");
      //PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);

      mnvPlotter.legend_n_columns = 2;
      // PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);
      PlotErrorSummaryNew(hist, plotname, histotitle, xaxislabel.c_str(), &cE, &mnvPlotter,true, PrintALLerrorGroups);
      mnvPlotter.legend_n_columns = 1;

      if(doBinwidth==true){mnvPlotter.draw_normalized_to_bin_width= false;}
    }
/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////
void DrawCVAndError_FromHIST_withGaussianPeak(
  MnvH1D *hist_input, char *histotitle ,
  std::string xaxislabel,std::string yaxislabel,
  std::string pdf_name, bool Setgrid,
  double reduceSpread, double par1, double par2,
  double Scaleup, double range1, double range2 )
  {

      PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
      TCanvas cE ("c1","c1");
      double x1,y1,x2,y2;
      TLegend *legend = new TLegend (0.65,0.65,0.95,.85);
      mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", 6.5, 6., .025);
      if(Setgrid==true){cE.SetGrid();}
      else if (Setgrid==false){cE.Clear();}
      MnvH1D * hist = (PlotUtils::MnvH1D*)hist_input->Clone("hist");
      double min =  hist->GetXaxis()->GetXmin();
      double max =  hist->GetXaxis()->GetXmax();
      TF1 *gfit = new TF1("Gaussian","gaus",range1,range2);
      double sigma = hist->GetRMS() / reduceSpread ;

      gfit->SetParameter(0,par1);
      gfit->SetParameter(1,par2);
      gfit->SetParameter(2,sigma);
      gfit->SetLineColor(kBlue);
      hist->GetXaxis()->SetTitleSize(0.035);
      hist->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
      hist->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));
      hist->GetYaxis()->CenterTitle();
      int nbins = hist->GetNbinsX();

      gfit->SetParNames("Constant","Mean","Sigma");

      double areaGauss = gfit->Integral(range1,range2);
      double areaHist = hist->Integral();
      hist->Scale((areaGauss / areaHist)*Scaleup);

      hist->SetTitle(histotitle);
      PlotUtils::MnvH1D* datahist =new PlotUtils::MnvH1D("adsf", "", nbins, xmin, xmax);
      bool statPlusSys           = false;
      int mcScale                = 1.;
      bool useHistTitles         = false;
      mnvPlotter.axis_maximum = 1.5;

      //hist->Scale(1,"width");
      mnvPlotter.DrawDataMCWithErrorBand(datahist, hist, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);
      //mnvPlotter.DrawMCWithErrorBand(hist); //I think that this call only shows stat errors.

      gfit->Draw("same");

      char sigma_name[1024];
      char mean_name[1024];
      char contant_name[1024];
      legend->AddEntry(gfit, "Gaussian Weighted function", "l"); // to put fit param
      sprintf(sigma_name ,   "#sigma  = %.2f ",   sigma );
      sprintf(mean_name ,    "Mean  = %.2f ",     par2);
      sprintf(contant_name , "Peak  = %.2f ", par1);

      legend->AddEntry((TObject*)0, sigma_name, ""); // to put fit param
      legend->AddEntry((TObject*)0, mean_name, ""); // to put fit param
      legend->AddEntry((TObject*)0, contant_name, ""); // to put fit param
      sprintf(contant_name , "min  = %.2f ", range1);
      legend->AddEntry((TObject*)0, contant_name, ""); // to put fit param
      sprintf(contant_name , "max  = %.2f ", range2);
      legend->AddEntry((TObject*)0, contant_name, ""); // to put fit param
      legend->SetTextSize(0.02);
      legend->Draw("same");


      mnvPlotter.AddHistoTitle(histotitle,.025);
      mnvPlotter.WritePreliminary("TR", .03, 0, 0, false);
      std::string plotname = Form("%s",pdf_name.c_str());
      mnvPlotter.MultiPrint(&cE, plotname, "pdf");
      //PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);
      cE.Closed();
    }

/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////
void DrawCVAndError_FromHIST_withFit(MnvH1D *hist, char *histotitle ,std::string xaxislabel,std::string yaxislabel,
        std::string pdf_name, bool Setgrid, bool PrintErrors , bool PrintallErrorGroups )
{

  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  double x1,y1,x2,y2;
    mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "TR", 6.5, 6., .025);
  //TLegend *legend = new TLegend (0.65,0.70,0.95,.8);
  TLegend *legend = new TLegend(x1 - .15, y1 , x2 + .1 , y2   );
  if(Setgrid==true){cE.SetGrid();}
  else if (Setgrid==false){cE.Clear();}
  hist->GetXaxis()->SetTitleSize(0.02);
  hist->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));
  hist->GetYaxis()->CenterTitle();
  double min,max;
  min =  hist->GetXaxis()->GetXmin();
  max =  hist->GetXaxis()->GetXmax();
  double maxy =  hist->GetMaximum();
  int nbins = hist->GetNbinsX();
  TF1 *gfit = new TF1("Gaussian","gaus",min,max);

  gfit->SetParameters(maxy,hist->GetMean(),hist->GetRMS());
  gfit->SetParNames("Constant","Mean","Sigma");
  hist->Fit(gfit,"RQ");
  auto chi_sq = gfit->GetChisquare();
  auto NDF_int = gfit->GetNDF();

  auto constant_value = gfit->GetParameter(0);
  auto constant_value_error = gfit->GetParError(0);

  auto mean_value = gfit->GetParameter("Mean");
  auto mean_value_error = gfit->GetParError(1);

  auto sigma_value = gfit->GetParameter(2);
  auto sigma_value_error = gfit->GetParError(2);

  hist->SetTitle(histotitle);
  PlotUtils::MnvH1D* datahist =new PlotUtils::MnvH1D("adsf", "", nbins, xmin, xmax);
  bool statPlusSys           = true;
  int mcScale                = 1.;
  bool useHistTitles         = false;

  mnvPlotter.axis_label_size =  0.02;
  mnvPlotter.axis_title_size_y = 0.022;
  mnvPlotter.axis_title_size_x = 0.02;
  //hist->Scale(1,"width");
  mnvPlotter.DrawDataMCWithErrorBand(datahist, hist, mcScale, "N", useHistTitles, NULL, NULL, false, statPlusSys);
  //mnvPlotter.DrawMCWithErrorBand(hist); //I think that this call only shows stat errors.
  gfit->SetLineColor(4);
  gfit->Draw("same");
  gStyle->SetOptFit(1111);
  char chi_name[1024];
  char sigma_name[1024];
  char mean_name[1024];
  char contant_name[1024];

  sprintf(chi_name ,     "#chi^{2} / ndf = %.2f / %i = %.2f",chi_sq, NDF_int, chi_sq / (double)NDF_int );
  sprintf(sigma_name ,   "#sigma  = %.2f #pm %.2f",   sigma_value, sigma_value_error );
  sprintf(mean_name ,    "Mean  = %.2f #pm %.2f",     mean_value,mean_value_error );
  sprintf(contant_name , "Contant  = %.2f #pm %.2f", constant_value, constant_value_error  );

  legend->AddEntry(hist, "Minerva v1", "l"); // to put fit param
  legend->AddEntry(gfit, "Gassian Fit", "l"); // to put fit param
  legend->AddEntry((TObject*)0, chi_name, ""); // to put fit param
  legend->AddEntry((TObject*)0, sigma_name, ""); // to put fit param
  legend->AddEntry((TObject*)0, mean_name, ""); // to put fit param
  legend->AddEntry((TObject*)0, contant_name, ""); // to put fit param

  legend->SetTextSize(0.02);
  legend->Draw("same");


  mnvPlotter.AddHistoTitle(histotitle,.03);
  mnvPlotter.WritePreliminary("TL", .03, 0, 0, false);
  std::string plotname = Form("%s",pdf_name.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");
  //PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);
  if(PrintErrors==true){
    mnvPlotter.legend_n_columns = 2;
    // PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);
    PlotErrorSummaryNew(hist, plotname, histotitle, xaxislabel.c_str(), &cE, &mnvPlotter,true,PrintallErrorGroups);
    mnvPlotter.legend_n_columns = 1;
  }

  cE.Closed();
}
/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////
void DrawCVAndError_FromHIST_withFit_Npoly(
  MnvH1D *hist_input, char *histotitle,
  std::string xaxislabel,std::string yaxislabel,
  std::string pdf_name, bool Setgrid,
  char *functionName , const int N_funtion, char *Print_pars )
  {
  MnvH1D *hist =(PlotUtils::MnvH1D*)hist_input->Clone("hist");
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);

  TCanvas cE ("c1","c1");
  std::ofstream outfile (Print_pars);
  double x1,y1,x2,y2;
  TLegend *legend = new TLegend (0.8,0.8,0.95,.85);
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", 6.5, 6., .025);
  if(Setgrid==true){cE.SetGrid();}
  else if (Setgrid==false){cE.Clear();}
  hist->GetXaxis()->SetTitleSize(0.035);
  hist->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));
  hist->GetYaxis()->CenterTitle();
  double min,max;
  min =  hist->GetXaxis()->GetXmin();
  max =  hist->GetXaxis()->GetXmax();
  int nbins = hist->GetNbinsX();
  double ymax =  hist->GetMaximum();
  TF1 *gfit = new TF1("gfit",functionName,min,max);
  hist->Fit(gfit,"RQ");
  double  chi_sq = gfit->GetChisquare();
  int NDF_int = gfit->GetNDF();
  double chi_sq_ndf = chi_sq / (double)NDF_int;
  double par[N_funtion];
  double Errs;
  gfit->GetParameters(par);

  gfit->SetLineStyle(2);
  gfit->SetLineColor(kBlue);
  hist->SetTitle(histotitle);
  PlotUtils::MnvH1D* datahist =new PlotUtils::MnvH1D("adsf", "", nbins, xmin, xmax);
  bool statPlusSys           = false;
  int mcScale                = 1.;
  bool useHistTitles         = false;

  hist->SetMaximum(ymax * 1.5);
  mnvPlotter.axis_maximum = 1.5;
  mnvPlotter.axis_minimum = .7;
  //hist->Scale(1,"width");
  mnvPlotter.DrawDataMCWithErrorBand(datahist, hist, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);
  //mnvPlotter.DrawMCWithErrorBand(hist); //I think that this call only shows stat errors.

  gfit->Draw("same");
  gStyle->SetOptFit(1111);

  legend->AddEntry(gfit, "Fit", "l");
  legend->SetTextSize(0.024);
  legend->Draw("same");

  TLatex* text = new TLatex;
  text->SetNDC();
  text->SetTextSize(0.03);
  text->SetTextColor(kRed);
  text->DrawLatex(0.35, 0.85, Form("Plot #chi^{2} = %3.4f", chi_sq));
  text->DrawLatex(0.35, 0.82, Form("Plot #chi^{2}/dof[%d] = %3.4f", NDF_int, chi_sq_ndf ));

  if(N_funtion==3){
    double yplace = .78;
    yplace-=.03;
    text->DrawLatex(0.2, yplace, Form("a + bx + cx^{2} + dx^{3}"));
    yplace-=.03;
    text->SetTextSize(0.025);
    Errs = gfit->GetParError(0);
    text->SetTextColor(kBlue);
    text->DrawLatex(0.25, yplace, Form("a =  %3.3f #pm %3.3f", par[0], Errs));
    yplace-=.02;
    Errs = gfit->GetParError(1);
    text->DrawLatex(0.25, yplace, Form("b =  %3.3f #pm %3.3f", par[1], Errs));
    yplace-=.02;
    Errs = gfit->GetParError(2);
    text->DrawLatex(0.25, yplace, Form("c =  %3.3f #pm %3.3f", par[2], Errs));
    yplace-=.02;
    Errs = gfit->GetParError(3);
    text->DrawLatex(0.25, yplace, Form("d =  %3.4f #pm %3.4f", par[3], Errs));
    yplace-=.02;
    outfile<< par[0]<<std::endl;
    outfile<< par[1]<<std::endl;
    outfile<< par[2]<<std::endl;
    outfile<< par[3]<<std::endl;

  }
  if(N_funtion==4){
    double yplace = .78;
    yplace-=.03;
    text->DrawLatex(0.2, yplace, Form("a + bx + cx^{2} + dx^{3} + ex^{4}"));
    yplace-=.03;
    text->SetTextSize(0.025);
    Errs = gfit->GetParError(0);
    text->SetTextColor(kBlue);
    text->DrawLatex(0.25, yplace, Form("a =  %3.3f #pm %3.3f", par[0], Errs));
    yplace-=.02;
    Errs = gfit->GetParError(1);
    text->DrawLatex(0.25, yplace, Form("b =  %3.3f #pm %3.3f", par[1], Errs));
    yplace-=.02;
    Errs = gfit->GetParError(2);
    text->DrawLatex(0.25, yplace, Form("c =  %3.3f #pm %3.3f", par[2], Errs));
    yplace-=.02;
    Errs = gfit->GetParError(3);
    text->DrawLatex(0.25, yplace, Form("d =  %3.4f #pm %3.4f", par[3], Errs));
    yplace-=.02;
    Errs = gfit->GetParError(4);
    text->DrawLatex(0.25, yplace, Form("e =  %3.4f #pm %3.4f", par[4], Errs));
    outfile<< par[0]<<std::endl;
    outfile<< par[1]<<std::endl;
    outfile<< par[2]<<std::endl;
    outfile<< par[3]<<std::endl;
    outfile<< par[4]<<std::endl;


  }
  if(N_funtion==5){
    double yplace = .78;
    yplace-=.03;
    text->DrawLatex(0.2, yplace, Form("a + bx + cx^{2} + dx^{3} + ex^{4} + fx^{5}"));
    yplace-=.03;
    text->SetTextSize(0.025);
    Errs = gfit->GetParError(0);
    text->SetTextColor(kBlue);
    text->DrawLatex(0.25, yplace, Form("a =  %3.2f #pm %3.2f", par[0], Errs));
    yplace-=.02;
    Errs = gfit->GetParError(1);
    text->DrawLatex(0.25, yplace, Form("b =  %3.2f #pm %3.2f", par[1], Errs));
    yplace-=.02;
    Errs = gfit->GetParError(2);
    text->DrawLatex(0.25, yplace, Form("c =  %3.3f #pm %3.3f", par[2], Errs));
    yplace-=.02;
    Errs = gfit->GetParError(3);
    text->DrawLatex(0.25, yplace, Form("d =  %3.4f #pm %3.4f", par[3], Errs));
    yplace-=.02;
    Errs = gfit->GetParError(4);
    text->DrawLatex(0.25, yplace, Form("e =  %3.5f #pm %3.5f", par[4], Errs));
    yplace-=.02;
    Errs = gfit->GetParError(5);
    text->DrawLatex(0.25, yplace, Form("e =  %3.5f #pm %3.5f", par[5], Errs));

    outfile<< par[0]<<std::endl;
    outfile<< par[1]<<std::endl;
    outfile<< par[2]<<std::endl;
    outfile<< par[3]<<std::endl;
    outfile<< par[4]<<std::endl;
    outfile<< par[5]<<std::endl;

  }
  if(N_funtion==6){
    double yplace = .78;
    yplace-=.03;
    text->DrawLatex(0.2, yplace, Form("a + bx + cx^{2} + dx^{3} + ex^{4} + fx^{5} + gx^{6}"));
    yplace-=.03;
    text->SetTextSize(0.025);
    Errs = gfit->GetParError(0);
    text->SetTextColor(kBlue);
    text->DrawLatex(0.25, yplace, Form("a =  %3.2f #pm %3.2f", par[0], Errs));
    yplace-=.02;
    Errs = gfit->GetParError(1);
    text->DrawLatex(0.25, yplace, Form("b =  %3.2f #pm %3.2f", par[1], Errs));
    yplace-=.02;
    Errs = gfit->GetParError(2);
    text->DrawLatex(0.25, yplace, Form("c =  %3.3f #pm %3.3f", par[2], Errs));
    yplace-=.02;
    Errs = gfit->GetParError(3);
    text->DrawLatex(0.25, yplace, Form("d =  %3.4f #pm %3.4f", par[3], Errs));
    yplace-=.02;
    Errs = gfit->GetParError(4);
    text->DrawLatex(0.25, yplace, Form("e =  %3.5f #pm %3.5f", par[4], Errs));
    yplace-=.02;
    Errs = gfit->GetParError(5);
    text->DrawLatex(0.25, yplace, Form("f =  %3.6f #pm %3.6f", par[5], Errs));
    yplace-=.02;
    Errs = gfit->GetParError(6);
    text->DrawLatex(0.25, yplace, Form("g =  %3.6f #pm %3.6f", par[6], Errs));
    outfile<< par[0]<<std::endl;
    outfile<< par[1]<<std::endl;
    outfile<< par[2]<<std::endl;
    outfile<< par[3]<<std::endl;
    outfile<< par[4]<<std::endl;
    outfile<< par[5]<<std::endl;
    outfile<< par[6]<<std::endl;
  }
  if(N_funtion==7){
    double yplace = .78;
    yplace-=.03;
    text->DrawLatex(0.2, yplace, Form("a + bx + cx^{2} + dx^{3} + ex^{4} + fx^{5} + gx^{6} + wx^{6}"));
    yplace-=.03;
    text->SetTextSize(0.025);
    Errs = gfit->GetParError(0);
    text->SetTextColor(kBlue);
    text->DrawLatex(0.25, yplace, Form("a =  %3.2f #pm %3.2f", par[0], Errs));
    yplace-=.02;
    Errs = gfit->GetParError(1);
    text->DrawLatex(0.25, yplace, Form("b =  %3.2f #pm %3.2f", par[1], Errs));
    yplace-=.02;
    Errs = gfit->GetParError(2);
    text->DrawLatex(0.25, yplace, Form("c =  %3.3f #pm %3.3f", par[2], Errs));
    yplace-=.02;
    Errs = gfit->GetParError(3);
    text->DrawLatex(0.25, yplace, Form("d =  %3.4f #pm %3.4f", par[3], Errs));
    yplace-=.02;
    Errs = gfit->GetParError(4);
    text->DrawLatex(0.25, yplace, Form("e =  %3.5f #pm %3.5f", par[4], Errs));
    yplace-=.02;
    Errs = gfit->GetParError(5);
    text->DrawLatex(0.25, yplace, Form("f =  %3.6f #pm %3.6f", par[5], Errs));
    yplace-=.02;
    Errs = gfit->GetParError(6);
    text->DrawLatex(0.25, yplace, Form("g =  %3.6f #pm %3.6f", par[6], Errs));
    yplace-=.02;
    Errs = gfit->GetParError(7);
    text->DrawLatex(0.25, yplace, Form("w =  %3.6f #pm %3.6f", par[7], Errs));
    outfile<< par[0]<<std::endl;
    outfile<< par[1]<<std::endl;
    outfile<< par[2]<<std::endl;
    outfile<< par[3]<<std::endl;
    outfile<< par[4]<<std::endl;
    outfile<< par[5]<<std::endl;
    outfile<< par[6]<<std::endl;
    outfile<< par[7]<<std::endl;
  }


  mnvPlotter.AddHistoTitle(histotitle,.025);
  mnvPlotter.WritePreliminary("TR", .03, 0, 0, false);
  std::string plotname = Form("%s",pdf_name.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");
  //PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);

  outfile.close();
  cE.Closed();
}
//////////////////////////////////////////////////////////////////////////////
//////
//////////////////////////////////////////////////////////////////////////////

void DrawCVAndError_FromHIST_with_Make_Npoly(
  MnvH1D *hist_input, char *histotitle,
  std::string xaxislabel,std::string yaxislabel,
  std::string pdf_name, bool Setgrid, char *functionName,
  const int N_funtion )
{
  MnvH1D *hist =(PlotUtils::MnvH1D*)hist_input->Clone("hist");
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  double x1,y1,x2,y2;
  TLegend *legend = new TLegend (0.8,0.8,0.95,.85);
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", 6.5, 6., .025);
  if(Setgrid==true){cE.SetGrid();}
  else if (Setgrid==false){cE.Clear();}
  hist->GetXaxis()->SetTitleSize(0.035);
  hist->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));
  hist->GetYaxis()->CenterTitle();
  double min,max;
  min =  hist->GetXaxis()->GetXmin();
  max =  hist->GetXaxis()->GetXmax();
  int nbins = hist->GetNbinsX();
  double ymax =  hist->GetMaximum();
  TF1 *gfit = new TF1("gfit",functionName,min,max);
  hist->Fit(gfit,"RQ");
  double  chi_sq = gfit->GetChisquare();
  int NDF_int = gfit->GetNDF();
  double chi_sq_ndf = chi_sq / (double)NDF_int;
  double par[N_funtion];
  double Errs;
  gfit->GetParameters(par);

  gfit->SetLineStyle(2);
  gfit->SetLineColor(kBlue);
  hist->SetTitle(histotitle);
  PlotUtils::MnvH1D* datahist =new PlotUtils::MnvH1D("adsf", "", nbins, xmin, xmax);
  bool statPlusSys           = false;
  int mcScale                = 1.;
  bool useHistTitles         = false;

  //hist->SetMaximum(ymax * 1.5);
  //hist->Scale(1,"width");
    mnvPlotter.axis_maximum = 1.5;
  mnvPlotter.DrawDataMCWithErrorBand(datahist, hist, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);
  //mnvPlotter.DrawMCWithErrorBand(hist); //I think that this call only shows stat errors.

  gfit->Draw("same");
  gStyle->SetOptFit(1111);

  legend->AddEntry(gfit, "Fit", "l");
  legend->SetTextSize(0.024);
  legend->Draw("same");

  TLatex* text = new TLatex;
  text->SetNDC();
  text->SetTextSize(0.03);
  text->SetTextColor(kRed);
  text->DrawLatex(0.35, 0.85, Form("Plot #chi^{2} = %3.4f", chi_sq));
  text->DrawLatex(0.35, 0.82, Form("Plot #chi^{2}/dof[%d] = %3.4f", NDF_int, chi_sq_ndf ));
  if(N_funtion==4){
    double yplace = .78;
    yplace-=.03;
    text->DrawLatex(0.2, yplace, Form("a + bx + cx^{2} + dx^{3}"));
    yplace-=.03;
    text->SetTextSize(0.025);
    Errs = gfit->GetParError(0);
    text->SetTextColor(kBlue);
    text->DrawLatex(0.25, yplace, Form("a =  %3.3f #pm %3.3f", par[0], Errs));
    yplace-=.02;
    Errs = gfit->GetParError(1);
    text->DrawLatex(0.25, yplace, Form("b =  %3.3f #pm %3.3f", par[1], Errs));
    yplace-=.02;
    Errs = gfit->GetParError(2);
    text->DrawLatex(0.25, yplace, Form("c =  %3.3f #pm %3.3f", par[2], Errs));
    yplace-=.02;
    Errs = gfit->GetParError(3);
    text->DrawLatex(0.25, yplace, Form("d =  %3.4f #pm %3.4f", par[3], Errs));
  }
  if(N_funtion==5){
    double yplace = .78;
    yplace-=.03;
    text->DrawLatex(0.2, yplace, Form("a + bx + cx^{2} + dx^{3} + ex^{4}"));
    yplace-=.03;
    text->SetTextSize(0.025);
    Errs = gfit->GetParError(0);
    text->SetTextColor(kBlue);
    text->DrawLatex(0.25, yplace, Form("a =  %3.2f #pm %3.2f", par[0], Errs));
    yplace-=.02;
    Errs = gfit->GetParError(1);
    text->DrawLatex(0.25, yplace, Form("b =  %3.2f #pm %3.2f", par[1], Errs));
    yplace-=.02;
    Errs = gfit->GetParError(2);
    text->DrawLatex(0.25, yplace, Form("c =  %3.3f #pm %3.3f", par[2], Errs));
    yplace-=.02;
    Errs = gfit->GetParError(3);
    text->DrawLatex(0.25, yplace, Form("d =  %3.4f #pm %3.4f", par[3], Errs));
    yplace-=.02;
    Errs = gfit->GetParError(4);
    text->DrawLatex(0.25, yplace, Form("e =  %3.5f #pm %3.5f", par[4], Errs));
  }
  if(N_funtion==6){
    double yplace = .78;
    yplace-=.03;
    text->DrawLatex(0.2, yplace, Form("a + bx + cx^{2} + dx^{3} + ex^{4} + fx^{5}"));
    yplace-=.03;
    text->SetTextSize(0.025);
    Errs = gfit->GetParError(0);
    text->SetTextColor(kBlue);
    text->DrawLatex(0.25, yplace, Form("a =  %3.2f #pm %3.2f", par[0], Errs));
    yplace-=.02;
    Errs = gfit->GetParError(1);
    text->DrawLatex(0.25, yplace, Form("b =  %3.2f #pm %3.2f", par[1], Errs));
    yplace-=.02;
    Errs = gfit->GetParError(2);
    text->DrawLatex(0.25, yplace, Form("c =  %3.3f #pm %3.3f", par[2], Errs));
    yplace-=.02;
    Errs = gfit->GetParError(3);
    text->DrawLatex(0.25, yplace, Form("d =  %3.4f #pm %3.4f", par[3], Errs));
    yplace-=.02;
    Errs = gfit->GetParError(4);
    text->DrawLatex(0.25, yplace, Form("e =  %3.5f #pm %3.5f", par[4], Errs));
    yplace-=.02;
    Errs = gfit->GetParError(5);
    text->DrawLatex(0.25, yplace, Form("f =  %3.6f #pm %3.6f", par[5], Errs));

  }
  if(N_funtion==7){
    double yplace = .78;
    yplace-=.03;
    text->DrawLatex(0.2, yplace, Form("a + bx + cx^{2} + dx^{3} + ex^{4} + fx^{5} + gx^{6}"));
    yplace-=.03;
    text->SetTextSize(0.025);
    Errs = gfit->GetParError(0);
    text->SetTextColor(kBlue);
    text->DrawLatex(0.25, yplace, Form("a =  %3.2f #pm %3.2f", par[0], Errs));
    yplace-=.02;
    Errs = gfit->GetParError(1);
    text->DrawLatex(0.25, yplace, Form("b =  %3.2f #pm %3.2f", par[1], Errs));
    yplace-=.02;
    Errs = gfit->GetParError(2);
    text->DrawLatex(0.25, yplace, Form("c =  %3.3f #pm %3.3f", par[2], Errs));
    yplace-=.02;
    Errs = gfit->GetParError(3);
    text->DrawLatex(0.25, yplace, Form("d =  %3.4f #pm %3.4f", par[3], Errs));
    yplace-=.02;
    Errs = gfit->GetParError(4);
    text->DrawLatex(0.25, yplace, Form("e =  %3.5f #pm %3.5f", par[4], Errs));
    yplace-=.02;
    Errs = gfit->GetParError(5);
    text->DrawLatex(0.25, yplace, Form("f =  %3.6f #pm %3.6f", par[5], Errs));
    yplace-=.02;
    Errs = gfit->GetParError(6);
    text->DrawLatex(0.25, yplace, Form("6 =  %3.6f #pm %3.6f", par[6], Errs));
  }


  mnvPlotter.AddHistoTitle(histotitle,.025);
  mnvPlotter.WritePreliminary("TR", .03, 0, 0, false);
  std::string plotname = Form("%s",pdf_name.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");
  //PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);


  cE.Closed();
}
/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////
void DrawCVAndError_FromHIST_withFit_Npoly_PZ(
  MnvH1D *hist_input, char *histotitle,
  std::string xaxislabel,std::string yaxislabel,
  std::string pdf_name, bool Setgrid )
{
  MnvH1D *hist =(PlotUtils::MnvH1D*)hist_input->Clone("hist");
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  double x1,y1,x2,y2;
  TLegend *legend = new TLegend (0.72,0.79,0.93,.85);
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", 6.5, 6., .025);
  if(Setgrid==true){cE.SetGrid();}
  else if (Setgrid==false){cE.Clear();}
  hist->GetXaxis()->SetTitleSize(0.035);
  hist->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));
  hist->GetYaxis()->CenterTitle();
  double min,max;
  min =  hist->GetXaxis()->GetXmin();
  max =  hist->GetXaxis()->GetXmax();
  int nbins = hist->GetNbinsX();
  double ymax =  hist->GetMaximum();

  TF1 *gfit = new TF1("gfit","pol 5",min,max);

  TF1 *gfit_warping = new TF1("gfit_warping",WarpingFunctionPZ_GeV, min, max);
  std::cout<<"Finished intializing function"<<std::endl;
  hist->Fit(gfit,"RQ");
  double  chi_sq = gfit->GetChisquare();
  int NDF_int = gfit->GetNDF();
  double chi_sq_ndf = chi_sq / (double)NDF_int;
  double par[6];
  double Errs;
  gfit->GetParameters(par);

  gfit_warping->SetParameter(0,par[0]);
  gfit_warping->SetParameter(1,par[1]);
  gfit_warping->SetParameter(2,par[2]);
  gfit_warping->SetParameter(3,par[3]);
  gfit_warping->SetParameter(4,par[4]);
  gfit_warping->SetParameter(5,par[5]);

  gfit->SetLineStyle(2);
  gfit_warping->SetLineStyle(3);
  gfit->SetLineColor(kRed);
  gfit_warping->SetLineColor(kBlue);
  hist->SetTitle(histotitle);
  PlotUtils::MnvH1D* datahist =new PlotUtils::MnvH1D("adsf", "", nbins, xmin, xmax);
  bool statPlusSys           = false;
  int mcScale                = 1.;
  bool useHistTitles         = false;

  hist->SetMaximum(ymax * 1.5);
  mnvPlotter.axis_title_offset_y = 1.4;
  mnvPlotter.axis_title_size_y = 0.04;
  mnvPlotter.DrawDataMCWithErrorBand(datahist, hist, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);

  gfit->Draw("same");

  gfit_warping->Draw("same");
  gStyle->SetOptFit(1111);
  legend->AddEntry(gfit, "Fit", "l");
  legend->AddEntry(gfit_warping, "Warping Function", "l");


  legend->SetTextSize(0.024);
  legend->Draw("same");

  TLatex* text = new TLatex;
  text->SetNDC();
  text->SetTextSize(0.03);
  text->SetTextColor(kRed);
  text->DrawLatex(0.35, 0.85, Form("Plot #chi^{2} = %3.4f", chi_sq));
  text->DrawLatex(0.35, 0.82, Form("Plot #chi^{2}/dof[%d] = %3.4f", NDF_int, chi_sq_ndf ));

  double yplace = .78;
  yplace-=.03;
  text->DrawLatex(0.2, yplace, Form("a + bx + cx^{2} + dx^{3} + ex^{4}+  fx^{5}"));
  yplace-=.03;
  text->SetTextSize(0.025);
  Errs = gfit->GetParError(0);
  text->SetTextColor(kBlue);
  text->DrawLatex(0.25, yplace, Form("a =  %3.2f #pm %3.3f", par[0], Errs));
  yplace-=.02;
  Errs = gfit->GetParError(1);
  text->DrawLatex(0.25, yplace, Form("b =  %3.2f #pm %3.3f", par[1], Errs));
  yplace-=.02;
  Errs = gfit->GetParError(2);
  text->DrawLatex(0.25, yplace, Form("c =  %3.3f #pm %3.4f", par[2], Errs));
  yplace-=.02;
  Errs = gfit->GetParError(3);
  text->DrawLatex(0.25, yplace, Form("d =  %3.4f #pm %3.4f", par[3], Errs));
  yplace-=.02;
  Errs = gfit->GetParError(4);
  text->DrawLatex(0.25, yplace, Form("e =  %3.5f #pm %3.5f", par[4], Errs));
  yplace-=.02;
  Errs = gfit->GetParError(5);
  text->DrawLatex(0.25, yplace, Form("f =  %3.5f #pm %3.7f", par[5], Errs));


  mnvPlotter.AddHistoTitle(histotitle,.045);
  mnvPlotter.WritePreliminary("TR", .03, 0, 0, false);
  std::string plotname = Form("%s",pdf_name.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");
  //PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);


  cE.Closed();
}
/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////
void DrawCVAndError_FromHIST_withFit_3poly_PZ_Daisy(
  MnvH1D *hist_input, char *histotitle,
  std::string xaxislabel,std::string yaxislabel,
  std::string pdf_name, bool Setgrid, Double_t *par )
{
  MnvH1D *hist =(PlotUtils::MnvH1D*)hist_input->Clone("hist");
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  double x1,y1,x2,y2;
  TLegend *legend = new TLegend (0.72,0.79,0.93,.85);
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", 6.5, 6., .025);
  if(Setgrid==true){cE.SetGrid();}
  else if (Setgrid==false){cE.Clear();}
  hist->GetXaxis()->SetTitleSize(0.035);
  hist->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));
  hist->GetYaxis()->CenterTitle();
  double min,max;
  min =  hist->GetXaxis()->GetXmin();
  max =  hist->GetXaxis()->GetXmax();
  int nbins = hist->GetNbinsX();
  double ymax =  hist->GetMaximum();

  TF1 *gfit = new TF1("gfit","pol 3",min,max);

  TF1 *gfit_warping = new TF1("gfit_warping",WarpingFunction_DAISY_poly3_PZ_GeV, min, max,4);
  std::cout<<"Finished intializing function"<<std::endl;
  hist->Fit(gfit,"RQ");
  double  chi_sq = gfit->GetChisquare();
  int NDF_int = gfit->GetNDF();
  double chi_sq_ndf = chi_sq / (double)NDF_int;
  double Errs;
  gfit->GetParameters(par);

  gfit_warping->SetParameter(0,par[0]);
  gfit_warping->SetParameter(1,par[1]);
  gfit_warping->SetParameter(2,par[2]);
  gfit_warping->SetParameter(3,par[3]);


  gfit->SetLineStyle(2);
  gfit_warping->SetLineStyle(3);
  gfit->SetLineColor(kRed);
  gfit_warping->SetLineColor(kBlue);
  hist->SetTitle(histotitle);
  PlotUtils::MnvH1D* datahist =new PlotUtils::MnvH1D("adsf", "", nbins, xmin, xmax);
  bool statPlusSys           = false;
  int mcScale                = 1.;
  bool useHistTitles         = false;

  hist->SetMaximum(ymax * 1.5);
  mnvPlotter.axis_title_offset_y = 1.4;
  mnvPlotter.axis_title_size_y = 0.04;
  mnvPlotter.axis_maximum =  1.6;
  mnvPlotter.axis_minimum = .7;
  mnvPlotter.DrawDataMCWithErrorBand(datahist, hist, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);

  gfit->Draw("same");

  gfit_warping->Draw("same");
  gStyle->SetOptFit(1111);
  legend->AddEntry(gfit, "Fit", "l");
  legend->AddEntry(gfit_warping, "Warping Function", "l");


  legend->SetTextSize(0.024);
  legend->Draw("same");

  TLatex* text = new TLatex;
  text->SetNDC();
  text->SetTextSize(0.03);
  text->SetTextColor(kRed);
  text->DrawLatex(0.35, 0.85, Form("Plot #chi^{2} = %3.4f", chi_sq));
  text->DrawLatex(0.35, 0.82, Form("Plot #chi^{2}/dof[%d] = %3.4f", NDF_int, chi_sq_ndf ));

  double yplace = .78;
  yplace-=.03;
  text->DrawLatex(0.2, yplace, Form("a + bx + cx^{2} + dx^{3}"));
  yplace-=.03;
  text->SetTextSize(0.025);
  Errs = gfit->GetParError(0);
  text->SetTextColor(kBlue);
  text->DrawLatex(0.25, yplace, Form("a =  %3.4f #pm %3.4f", par[0], Errs));
  yplace-=.02;
  Errs = gfit->GetParError(1);
  text->DrawLatex(0.25, yplace, Form("b =  %3.4f #pm %3.4f", par[1], Errs));
  yplace-=.02;
  Errs = gfit->GetParError(2);
  text->DrawLatex(0.25, yplace, Form("c =  %3.4f #pm %3.4f", par[2], Errs));
  yplace-=.02;
  Errs = gfit->GetParError(3);
  text->DrawLatex(0.25, yplace, Form("d =  %3.4f #pm %3.4f", par[3], Errs));

  mnvPlotter.AddHistoTitle(histotitle,.045);
  mnvPlotter.WritePreliminary("TR", .03, 0, 0, false);
  std::string plotname = Form("%s",pdf_name.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");
  //PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);


  cE.Closed();
}
/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////
void DrawCVAndError_FromHIST_withFit_Npoly_PT(
  MnvH1D *hist_input, char *histotitle,
  std::string xaxislabel,std::string yaxislabel,
  std::string pdf_name, bool Setgrid )
{
  MnvH1D *hist =(PlotUtils::MnvH1D*)hist_input->Clone("hist");
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  double x1,y1,x2,y2;
  TLegend *legend = new TLegend (0.72,0.79,0.93,.85);
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", 6.5, 6., .025);
  if(Setgrid==true){cE.SetGrid();}
  else if (Setgrid==false){cE.Clear();}
  hist->GetXaxis()->SetTitleSize(0.035);
  hist->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));
  hist->GetYaxis()->CenterTitle();
  double min,max;
  min =  hist->GetXaxis()->GetXmin();
  max =  hist->GetXaxis()->GetXmax();
  int nbins = hist->GetNbinsX();
  double ymax =  hist->GetMaximum();

  TF1 *gfit = new TF1("gfit","pol 4",min,max);

  TF1 *gfit_warping = new TF1("gfit_warping",WarpingFunctionPT_GeV, min, max);
  std::cout<<"Finished intializing function"<<std::endl;
  hist->Fit(gfit,"RQ");
  double  chi_sq = gfit->GetChisquare();
  int NDF_int = gfit->GetNDF();
  double chi_sq_ndf = chi_sq / (double)NDF_int;
  double par[6];
  double Errs;
  gfit->GetParameters(par);

  gfit_warping->SetParameter(0,par[0]);
  gfit_warping->SetParameter(1,par[1]);
  gfit_warping->SetParameter(2,par[2]);
  gfit_warping->SetParameter(3,par[3]);
  gfit_warping->SetParameter(4,par[4]);


  gfit->SetLineStyle(2);
  gfit_warping->SetLineStyle(3);
  gfit->SetLineColor(kRed);
  gfit_warping->SetLineColor(kBlue);
  hist->SetTitle(histotitle);
  PlotUtils::MnvH1D* datahist =new PlotUtils::MnvH1D("adsf", "", nbins, xmin, xmax);
  bool statPlusSys           = false;
  int mcScale                = 1.;
  bool useHistTitles         = false;

  hist->SetMaximum(ymax * 1.5);
  mnvPlotter.axis_title_offset_y = 1.4;
  mnvPlotter.axis_title_size_y = 0.04;
  mnvPlotter.axis_maximum = 1.6;
  mnvPlotter.axis_minimum = .8;
  mnvPlotter.DrawDataMCWithErrorBand(datahist, hist, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);

  gfit->Draw("same");

  gfit_warping->Draw("same");
  gStyle->SetOptFit(1111);
  legend->AddEntry(gfit, "Fit", "l");
  legend->AddEntry(gfit_warping, "Warping Function", "l");


  legend->SetTextSize(0.024);
  legend->Draw("same");

  TLatex* text = new TLatex;
  text->SetNDC();
  text->SetTextSize(0.03);
  text->SetTextColor(kRed);
  text->DrawLatex(0.35, 0.85, Form("Plot #chi^{2} = %3.4f", chi_sq));
  text->DrawLatex(0.35, 0.82, Form("Plot #chi^{2}/dof[%d] = %3.4f", NDF_int, chi_sq_ndf ));

  double yplace = .78;
  yplace-=.03;
  text->DrawLatex(0.2, yplace, Form("a + bx + cx^{2} + dx^{3} + ex^{4}"));
  yplace-=.03;
  text->SetTextSize(0.025);
  Errs = gfit->GetParError(0);
  text->SetTextColor(kBlue);
  text->DrawLatex(0.25, yplace, Form("a =  %3.2f #pm %3.3f", par[0], Errs));
  yplace-=.02;
  Errs = gfit->GetParError(1);
  text->DrawLatex(0.25, yplace, Form("b =  %3.2f #pm %3.3f", par[1], Errs));
  yplace-=.02;
  Errs = gfit->GetParError(2);
  text->DrawLatex(0.25, yplace, Form("c =  %3.3f #pm %3.4f", par[2], Errs));
  yplace-=.02;
  Errs = gfit->GetParError(3);
  text->DrawLatex(0.25, yplace, Form("d =  %3.4f #pm %3.4f", par[3], Errs));
  yplace-=.02;
  Errs = gfit->GetParError(4);
  text->DrawLatex(0.25, yplace, Form("e =  %3.5f #pm %3.5f", par[4], Errs));



  mnvPlotter.AddHistoTitle(histotitle,.045);
  mnvPlotter.WritePreliminary("TR", .03, 0, 0, false);
  std::string plotname = Form("%s",pdf_name.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");
  //PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);


  cE.Closed();
}
/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////
void DrawCVAndError_FromHIST_withFit_3poly_PT_Daisy(
  MnvH1D *hist_input, char *histotitle,
  std::string xaxislabel,std::string yaxislabel,
  std::string pdf_name, bool Setgrid, Double_t *par )
{
  MnvH1D *hist =(PlotUtils::MnvH1D*)hist_input->Clone("hist");
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  double x1,y1,x2,y2;
  TLegend *legend = new TLegend (0.72,0.79,0.93,.85);
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", 6.5, 6., .025);
  if(Setgrid==true){cE.SetGrid();}
  else if (Setgrid==false){cE.Clear();}
  hist->GetXaxis()->SetTitleSize(0.035);
  hist->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));
  hist->GetYaxis()->CenterTitle();
  double min,max;
  double parlocal[4];
  min =  hist->GetXaxis()->GetXmin();
  max =  hist->GetXaxis()->GetXmax();
  int nbins = hist->GetNbinsX();
  double ymax =  hist->GetMaximum();
  std::cout<<"inside function"<< std::endl;
  for(int i =0; i< 4 ; i++){
  std::cout << "Par["<<i<<"] = " << par[i]<< std::endl;
}



  TF1 *gfit = new TF1("gfit","pol 3",min,max);
  gfit->GetParameters(parlocal);
  TF1 *gfit_warping = new TF1("gfit_warping",WarpingFunction_DAISY_poly3_PT_GeV, min, max,4);
  std::cout<<"Finished intializing function"<<std::endl;
  hist->Fit(gfit,"RQ");
  std::cout<<"1"<<std::endl;
  double  chi_sq = gfit->GetChisquare();
  int NDF_int = gfit->GetNDF();
  double chi_sq_ndf = chi_sq / (double)NDF_int;
  double Errs;
  gfit->GetParameters(parlocal);
  std::cout<<"2"<<std::endl;
  gfit_warping->SetParameter(0,par[0]);
  gfit_warping->SetParameter(1,par[1]);
  gfit_warping->SetParameter(2,par[2]);
  gfit_warping->SetParameter(3,par[3]);
  std::cout<<"3"<<std::endl;
  gfit->SetLineStyle(2);
  gfit_warping->SetLineStyle(3);
  gfit->SetLineColor(kRed);
  gfit_warping->SetLineColor(kBlue);
  hist->SetTitle(histotitle);
  PlotUtils::MnvH1D* datahist =new PlotUtils::MnvH1D("adsf", "", nbins, xmin, xmax);
  bool statPlusSys           = false;
  int mcScale                = 1.;
  bool useHistTitles         = false;

  //hist->SetMaximum(ymax * 1.5);
  mnvPlotter.axis_title_offset_y = 1.4;
  mnvPlotter.axis_title_size_y = 0.04;
  mnvPlotter.axis_maximum = 1.5;
  mnvPlotter.axis_minimum = .9;
  mnvPlotter.DrawDataMCWithErrorBand(datahist, hist, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);

  gfit->Draw("same");
  std::cout<<"4"<<std::endl;
  gfit_warping->Draw("same");
  //gStyle->SetOptFit(1111);
  legend->AddEntry(gfit, "Fit", "l");
  legend->AddEntry(gfit_warping, "Warping Function", "l");
  std::cout<<"5"<<std::endl;

  legend->SetTextSize(0.024);
  legend->Draw("same");

  TLatex* text = new TLatex;
  text->SetNDC();
  text->SetTextSize(0.03);
  text->SetTextColor(kRed);
  text->DrawLatex(0.35, 0.85, Form("Plot #chi^{2} = %3.4f", chi_sq));
  text->DrawLatex(0.35, 0.82, Form("Plot #chi^{2}/dof[%d] = %3.4f", NDF_int, chi_sq_ndf ));
  std::cout<<"6"<<std::endl;
  double yplace = .78;
  yplace-=.03;
  text->DrawLatex(0.2, yplace, Form("a + bx + cx^{2} + dx^{3}"));
  yplace-=.03;
  text->SetTextSize(0.025);
  Errs = gfit->GetParError(0);
  text->SetTextColor(kBlue);
  text->DrawLatex(0.25, yplace, Form("a =  %3.2f #pm %3.3f", par[0], Errs));
  yplace-=.02;
  Errs = gfit->GetParError(1);
  text->DrawLatex(0.25, yplace, Form("b =  %3.2f #pm %3.3f", par[1], Errs));
  yplace-=.02;
  Errs = gfit->GetParError(2);
  text->DrawLatex(0.25, yplace, Form("c =  %3.3f #pm %3.4f", par[2], Errs));
  yplace-=.02;
  Errs = gfit->GetParError(3);
  text->DrawLatex(0.25, yplace, Form("d =  %3.4f #pm %3.4f", par[3], Errs));
  std::cout<<"7"<<std::endl;


  mnvPlotter.AddHistoTitle(histotitle,.045);
  mnvPlotter.WritePreliminary("TR", .03, 0, 0, false);
  std::string plotname = Form("%s",pdf_name.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");
  //PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);


  cE.Closed();

  return;
}
/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////
void DrawCVAndError_FromHIST_withFit_Npoly_E(
  MnvH1D *hist_input, char *histotitle,
  std::string xaxislabel,std::string yaxislabel,
  std::string pdf_name, bool Setgrid )
{
  MnvH1D *hist =(PlotUtils::MnvH1D*)hist_input->Clone("hist");
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  double x1,y1,x2,y2;
  TLegend *legend = new TLegend (0.72,0.79,0.93,.85);
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", 6.5, 6., .025);
  if(Setgrid==true){cE.SetGrid();}
  else if (Setgrid==false){cE.Clear();}
  hist->GetXaxis()->SetTitleSize(0.035);
  hist->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));
  hist->GetYaxis()->CenterTitle();
  double min,max;
  min =  hist->GetXaxis()->GetXmin();
  max =  hist->GetXaxis()->GetXmax();
  int nbins = hist->GetNbinsX();
  double ymax =  hist->GetMaximum();

  TF1 *gfit = new TF1("gfit","pol 5",min,max);

  TF1 *gfit_warping = new TF1("gfit_warping",WarpingFunctionE_GeV, min, max);
  std::cout<<"Finished intializing function"<<std::endl;
  hist->Fit(gfit,"RQ");
  double  chi_sq = gfit->GetChisquare();
  int NDF_int = gfit->GetNDF();
  double chi_sq_ndf = chi_sq / (double)NDF_int;
  double par[6];
  double Errs;
  gfit->GetParameters(par);

  gfit_warping->SetParameter(0,par[0]);
  gfit_warping->SetParameter(1,par[1]);
  gfit_warping->SetParameter(2,par[2]);
  gfit_warping->SetParameter(3,par[3]);
  gfit_warping->SetParameter(4,par[4]);
  gfit_warping->SetParameter(5,par[5]);


  gfit->SetLineStyle(2);
  gfit_warping->SetLineStyle(3);
  gfit->SetLineColor(kRed);
  gfit_warping->SetLineColor(kBlue);
  hist->SetTitle(histotitle);
  PlotUtils::MnvH1D* datahist =new PlotUtils::MnvH1D("adsf", "", nbins, xmin, xmax);
  bool statPlusSys           = false;
  int mcScale                = 1.;
  bool useHistTitles         = false;

  hist->SetMaximum(ymax * 1.5);
  mnvPlotter.axis_title_offset_y = 1.4;
  mnvPlotter.axis_title_size_y = 0.04;
  mnvPlotter.DrawDataMCWithErrorBand(datahist, hist, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);

  gfit->Draw("same");

  gfit_warping->Draw("same");
  gStyle->SetOptFit(1111);
  legend->AddEntry(gfit, "Fit", "l");
  legend->AddEntry(gfit_warping, "Warping Function", "l");


  legend->SetTextSize(0.024);
  legend->Draw("same");

  TLatex* text = new TLatex;
  text->SetNDC();
  text->SetTextSize(0.03);
  text->SetTextColor(kRed);
  text->DrawLatex(0.35, 0.85, Form("Plot #chi^{2} = %3.4f", chi_sq));
  text->DrawLatex(0.35, 0.82, Form("Plot #chi^{2}/dof[%d] = %3.4f", NDF_int, chi_sq_ndf ));

  double yplace = .78;
  yplace-=.03;
  text->DrawLatex(0.2, yplace, Form("a + bx + cx^{2} + dx^{3} + ex^{4} + fx^{5}"));
  yplace-=.03;
  text->SetTextSize(0.025);
  Errs = gfit->GetParError(0);
  text->SetTextColor(kBlue);
  text->DrawLatex(0.25, yplace, Form("a =  %3.2f #pm %3.2f", par[0], Errs));
  yplace-=.02;
  Errs = gfit->GetParError(1);
  text->DrawLatex(0.25, yplace, Form("b =  %3.2f #pm %3.2f", par[1], Errs));
  yplace-=.02;
  Errs = gfit->GetParError(2);
  text->DrawLatex(0.25, yplace, Form("c =  %3.3f #pm %3.3f", par[2], Errs));
  yplace-=.02;
  Errs = gfit->GetParError(3);
  text->DrawLatex(0.25, yplace, Form("d =  %3.4f #pm %3.4f", par[3], Errs));
  yplace-=.02;
  Errs = gfit->GetParError(4);
  text->DrawLatex(0.25, yplace, Form("e =  %3.5f #pm %3.7f", par[4], Errs));
  yplace-=.02;
  Errs = gfit->GetParError(5);
  text->DrawLatex(0.25, yplace, Form("f =  %3.6f #pm %3.8f", par[5], Errs));
  //yplace-=.02;
  //Errs = gfit->GetParError(6);
  //text->DrawLatex(0.25, yplace, Form("g =  %3.6f #pm %3.10f", par[6], Errs));

  mnvPlotter.AddHistoTitle(histotitle,.045);
  mnvPlotter.WritePreliminary("TR", .03, 0, 0, false);
  std::string plotname = Form("%s",pdf_name.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");
  //PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);


  cE.Closed();
}
/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////
void DrawCVAndError_FromHIST_withFit_3poly_E_Daisy(
  MnvH1D *hist_input, char *histotitle,
  std::string xaxislabel,std::string yaxislabel,
  std::string pdf_name, bool Setgrid, Double_t *par )
{
  MnvH1D *hist =(PlotUtils::MnvH1D*)hist_input->Clone("hist");
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  double x1,y1,x2,y2;
  TLegend *legend = new TLegend (0.72,0.79,0.93,.85);
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", 6.5, 6., .025);
  if(Setgrid==true){cE.SetGrid();}
  else if (Setgrid==false){cE.Clear();}
  hist->GetXaxis()->SetTitleSize(0.035);
  hist->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));
  hist->GetYaxis()->CenterTitle();
  double min,max;
  min =  hist->GetXaxis()->GetXmin();
  max =  hist->GetXaxis()->GetXmax();
  int nbins = hist->GetNbinsX();
  double ymax =  hist->GetMaximum();

  TF1 *gfit = new TF1("gfit","pol 3",min,max);

  TF1 *gfit_warping = new TF1("gfit_warping",WarpingFunction_DAISY_poly3_E_GeV, min, max,4);
  std::cout<<"Finished intializing function"<<std::endl;
  hist->Fit(gfit,"RQ");
  double  chi_sq = gfit->GetChisquare();
  int NDF_int = gfit->GetNDF();
  double chi_sq_ndf = chi_sq / (double)NDF_int;

  double Errs;
  gfit->GetParameters(par);

  gfit_warping->SetParameter(0,par[0]);
  gfit_warping->SetParameter(1,par[1]);
  gfit_warping->SetParameter(2,par[2]);
  gfit_warping->SetParameter(3,par[3]);


  gfit->SetLineStyle(2);
  gfit_warping->SetLineStyle(3);
  gfit->SetLineColor(kRed);
  gfit_warping->SetLineColor(kBlue);
  hist->SetTitle(histotitle);
  PlotUtils::MnvH1D* datahist =new PlotUtils::MnvH1D("adsf", "", nbins, xmin, xmax);
  bool statPlusSys           = false;
  int mcScale                = 1.;
  bool useHistTitles         = false;

  hist->SetMaximum(ymax * 1.5);
  mnvPlotter.axis_title_offset_y = 1.4;
  mnvPlotter.axis_title_size_y = 0.04;
  mnvPlotter.axis_maximum =  1.8;
  mnvPlotter.axis_minimum = .9;
  mnvPlotter.DrawDataMCWithErrorBand(datahist, hist, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);

  gfit->Draw("same");

  gfit_warping->Draw("same");
  gStyle->SetOptFit(1111);
  legend->AddEntry(gfit, "Fit", "l");
  legend->AddEntry(gfit_warping, "Warping Function", "l");


  legend->SetTextSize(0.024);
  legend->Draw("same");

  TLatex* text = new TLatex;
  text->SetNDC();
  text->SetTextSize(0.03);
  text->SetTextColor(kRed);
  text->DrawLatex(0.35, 0.85, Form("Plot #chi^{2} = %3.4f", chi_sq));
  text->DrawLatex(0.35, 0.82, Form("Plot #chi^{2}/dof[%d] = %3.4f", NDF_int, chi_sq_ndf ));

  double yplace = .78;
  yplace-=.03;
  text->DrawLatex(0.2, yplace, Form("a + bx + cx^{2} + dx^{3}"));
  yplace-=.03;
  text->SetTextSize(0.025);
  Errs = gfit->GetParError(0);
  text->SetTextColor(kBlue);
  text->DrawLatex(0.25, yplace, Form("a =  %3.4f #pm %3.4f", par[0], Errs));
  yplace-=.02;
  Errs = gfit->GetParError(1);
  text->DrawLatex(0.25, yplace, Form("b =  %3.4f #pm %3.4f", par[1], Errs));
  yplace-=.02;
  Errs = gfit->GetParError(2);
  text->DrawLatex(0.25, yplace, Form("c =  %3.4f #pm %3.4f", par[2], Errs));
  yplace-=.02;
  Errs = gfit->GetParError(3);
  text->DrawLatex(0.25, yplace, Form("d =  %3.4f #pm %3.4f", par[3], Errs));

  mnvPlotter.AddHistoTitle(histotitle,.045);
  mnvPlotter.WritePreliminary("TR", .03, 0, 0, false);
  std::string plotname = Form("%s",pdf_name.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");
  //PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);


  cE.Closed();
}
/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////
void DrawCVAndError_FromHIST_withFit_Npoly_theta(MnvH1D *hist_input, char *histotitle,
  std::string xaxislabel,std::string yaxislabel,
        std::string pdf_name, bool Setgrid )
{
  MnvH1D *hist =(PlotUtils::MnvH1D*)hist_input->Clone("hist");
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  double x1,y1,x2,y2;
  TLegend *legend = new TLegend (0.72,0.79,0.93,.85);
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", 6.5, 6., .025);
  if(Setgrid==true){cE.SetGrid();}
  else if (Setgrid==false){cE.Clear();}
  hist->GetXaxis()->SetTitleSize(0.035);
  hist->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));
  hist->GetYaxis()->CenterTitle();
  double min,max;
  min =  hist->GetXaxis()->GetXmin();
  max =  hist->GetXaxis()->GetXmax();
  int nbins = hist->GetNbinsX();
  double ymax =  hist->GetMaximum();

  TF1 *gfit = new TF1("gfit","pol 4",min,max);

  TF1 *gfit_warping = new TF1("gfit_warping",WarpingFunctionTheta_Deg, min, max);
  std::cout<<"Finished intializing function"<<std::endl;
  hist->Fit(gfit,"RQ");
  double  chi_sq = gfit->GetChisquare();
  int NDF_int = gfit->GetNDF();
  double chi_sq_ndf = chi_sq / (double)NDF_int;
  double par[6];
  double Errs;
  gfit->GetParameters(par);

  gfit_warping->SetParameter(0,par[0]);
  gfit_warping->SetParameter(1,par[1]);
  gfit_warping->SetParameter(2,par[2]);
  gfit_warping->SetParameter(3,par[3]);
  gfit_warping->SetParameter(4,par[4]);


  gfit->SetLineStyle(2);
  gfit_warping->SetLineStyle(3);
  gfit->SetLineColor(kRed);
  gfit_warping->SetLineColor(kBlue);
  hist->SetTitle(histotitle);
  PlotUtils::MnvH1D* datahist =new PlotUtils::MnvH1D("adsf", "", nbins, xmin, xmax);
  bool statPlusSys           = false;
  int mcScale                = 1.;
  bool useHistTitles         = false;

  hist->SetMaximum(ymax * 1.5);
  mnvPlotter.axis_title_offset_y = 1.4;
  mnvPlotter.axis_title_size_y = 0.04;
  mnvPlotter.DrawDataMCWithErrorBand(datahist, hist, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);

  gfit->Draw("same");

  gfit_warping->Draw("same");
  gStyle->SetOptFit(1111);
  legend->AddEntry(gfit, "Fit", "l");
  legend->AddEntry(gfit_warping, "Warping Function", "l");


  legend->SetTextSize(0.024);
  legend->Draw("same");

  TLatex* text = new TLatex;
  text->SetNDC();
  text->SetTextSize(0.03);
  text->SetTextColor(kRed);
  text->DrawLatex(0.35, 0.85, Form("Plot #chi^{2} = %3.4f", chi_sq));
  text->DrawLatex(0.35, 0.82, Form("Plot #chi^{2}/dof[%d] = %3.4f", NDF_int, chi_sq_ndf ));

  double yplace = .78;
  yplace-=.03;
  text->DrawLatex(0.2, yplace, Form("a + bx + cx^{2} + dx^{3} + ex^{4}"));
  yplace-=.03;
  text->SetTextSize(0.025);
  Errs = gfit->GetParError(0);
  text->SetTextColor(kBlue);
  text->DrawLatex(0.25, yplace, Form("a =  %3.2f #pm %3.3f", par[0], Errs));
  yplace-=.02;
  Errs = gfit->GetParError(1);
  text->DrawLatex(0.25, yplace, Form("b =  %3.2f #pm %3.3f", par[1], Errs));
  yplace-=.02;
  Errs = gfit->GetParError(2);
  text->DrawLatex(0.25, yplace, Form("c =  %3.3f #pm %3.4f", par[2], Errs));
  yplace-=.02;
  Errs = gfit->GetParError(3);
  text->DrawLatex(0.25, yplace, Form("d =  %3.4f #pm %3.4f", par[3], Errs));
  yplace-=.02;
  Errs = gfit->GetParError(4);
  text->DrawLatex(0.25, yplace, Form("e =  %3.5f #pm %3.5f", par[4], Errs));



  mnvPlotter.AddHistoTitle(histotitle,.045);
  mnvPlotter.WritePreliminary("TR", .03, 0, 0, false);
  std::string plotname = Form("%s",pdf_name.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");
  //PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);


  cE.Closed();
}
/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////
void DrawCVAndError_FromHIST_withFit_3poly_theta_Daisy(
  MnvH1D *hist_input, char *histotitle, std::string xaxislabel,
  std::string yaxislabel, std::string pdf_name, bool Setgrid, Double_t *par )
{
  MnvH1D *hist =(PlotUtils::MnvH1D*)hist_input->Clone("hist");
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  double x1,y1,x2,y2;
  TLegend *legend = new TLegend (0.72,0.79,0.93,.85);
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", 6.5, 6., .025);
  if(Setgrid==true){cE.SetGrid();}
  else if (Setgrid==false){cE.Clear();}
  hist->GetXaxis()->SetTitleSize(0.035);
  hist->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));
  hist->GetYaxis()->CenterTitle();
  double min,max;
  min =  hist->GetXaxis()->GetXmin();
  max =  hist->GetXaxis()->GetXmax();
  int nbins = hist->GetNbinsX();
  double ymax =  hist->GetMaximum();

  TF1 *gfit = new TF1("gfit","pol 3",min,max);

  TF1 *gfit_warping = new TF1("gfit_warping",WarpingFunction_DAISY_poly3_Theta_Deg, min, max,4);
  std::cout<<"Finished intializing function"<<std::endl;
  hist->Fit(gfit,"RQ");
  double  chi_sq = gfit->GetChisquare();
  int NDF_int = gfit->GetNDF();
  double chi_sq_ndf = chi_sq / (double)NDF_int;
  double Errs;
  gfit->GetParameters(par);

  gfit_warping->SetParameter(0,par[0]);
  gfit_warping->SetParameter(1,par[1]);
  gfit_warping->SetParameter(2,par[2]);
  gfit_warping->SetParameter(3,par[3]);



  gfit->SetLineStyle(2);
  gfit_warping->SetLineStyle(3);
  gfit->SetLineColor(kRed);
  gfit_warping->SetLineColor(kBlue);
  hist->SetTitle(histotitle);
  PlotUtils::MnvH1D* datahist =new PlotUtils::MnvH1D("adsf", "", nbins, xmin, xmax);
  bool statPlusSys           = false;
  int mcScale                = 1.;
  bool useHistTitles         = false;

  hist->SetMaximum(ymax * 1.5);
  mnvPlotter.axis_title_offset_y = 1.4;
  mnvPlotter.axis_title_size_y = 0.04;
  mnvPlotter.axis_maximum =  1.6;
  mnvPlotter.axis_minimum = .8;
  mnvPlotter.DrawDataMCWithErrorBand(datahist, hist, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);

  gfit->Draw("same");

  gfit_warping->Draw("same");
  gStyle->SetOptFit(1111);
  legend->AddEntry(gfit, "Fit", "l");
  legend->AddEntry(gfit_warping, "Warping Function", "l");


  legend->SetTextSize(0.024);
  legend->Draw("same");

  TLatex* text = new TLatex;
  text->SetNDC();
  text->SetTextSize(0.03);
  text->SetTextColor(kRed);
  text->DrawLatex(0.35, 0.85, Form("Plot #chi^{2} = %3.4f", chi_sq));
  text->DrawLatex(0.35, 0.82, Form("Plot #chi^{2}/dof[%d] = %3.4f", NDF_int, chi_sq_ndf ));

  double yplace = .78;
  yplace-=.03;
  text->DrawLatex(0.2, yplace, Form("a + bx + cx^{2} + dx^{3}"));
  yplace-=.03;
  text->SetTextSize(0.025);
  Errs = gfit->GetParError(0);
  text->SetTextColor(kBlue);
  text->DrawLatex(0.25, yplace, Form("a =  %3.4f #pm %3.4f", par[0], Errs));
  yplace-=.02;
  Errs = gfit->GetParError(1);
  text->DrawLatex(0.25, yplace, Form("b =  %3.4f #pm %3.4f", par[1], Errs));
  yplace-=.02;
  Errs = gfit->GetParError(2);
  text->DrawLatex(0.25, yplace, Form("c =  %3.4f #pm %3.4f", par[2], Errs));
  yplace-=.02;
  Errs = gfit->GetParError(3);
  text->DrawLatex(0.25, yplace, Form("d =  %3.4f #pm %3.4f", par[3], Errs));


  mnvPlotter.AddHistoTitle(histotitle,.045);
  mnvPlotter.WritePreliminary("TR", .03, 0, 0, false);
  std::string plotname = Form("%s",pdf_name.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");
  //PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);


  cE.Closed();
}
/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////
void DrawCVAndError_FromHIST_withRMS(MnvH1D *hist_input, char *histotitle,
  std::string xaxislabel, std::string yaxislabel, char* Units,
  std::string pdf_name, bool Setgrid, bool doBinwidth,  bool PrintErrors,
   bool PrintallErrorGroups, bool PrintRMS_percentage, bool AreaNormalized )
{
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  double x1,y1,x2,y2;
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", .5, 10, .025);
  TLegend *legend = new TLegend(x1 - .1, y1 , x2 , y2   );
  legend->SetBorderSize(0);
  if(Setgrid==true){cE.SetGrid();}
  else if (Setgrid==false){cE.Clear();}

  MnvH1D *hist = (PlotUtils::MnvH1D*)hist_input->Clone("hist");
  hist->GetXaxis()->SetTitleSize(0.035);
  hist->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));

  if (AreaNormalized==true){
    double Area = hist->Integral(1, hist->GetNbinsX());
    hist->Scale(1.0/Area);

  }



  if(doBinwidth==true){
    double binwidth_title = hist -> GetBinWidth(5);
    char ytitle[1024];
    sprintf(ytitle, "NEvents / %.2f %s", binwidth_title, Units);

    hist->GetYaxis()->SetTitle(ytitle);//
  }
  else{
    hist->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));//
  }

  hist->GetYaxis()->SetLabelSize(0.035);
  hist->GetYaxis()->CenterTitle();

  double RMS_value;
  char RMSchar[1024];
  if(PrintRMS_percentage==true){
    RMS_value = 100 * hist->GetRMS();
    sprintf(RMSchar ,"RMS: %.2f %%",RMS_value );

  }
  else{
    RMS_value = hist->GetRMS();
    sprintf(RMSchar , "RMS: %.2f [%s]",RMS_value, Units );
  }


  hist->SetTitle(histotitle);
  PlotUtils::MnvH1D* datahist =new PlotUtils::MnvH1D("adsf", "", nbins, xmin, xmax);
  bool statPlusSys           = true;
  int mcScale                = 1.;
  bool useHistTitles         = false;
  if(doBinwidth==true){hist->Scale(1,"width");}
  hist->SetTitleOffset(1.2);
  hist->GetYaxis()->SetTitleOffset(1.5);
  mnvPlotter.axis_title_size_x = 0.03;
  //mnvPlotter.axis_title_offset_y = 1.0;
  mnvPlotter.axis_label_size =  0.025;
  mnvPlotter.axis_title_size_y = 0.025;
  mnvPlotter.axis_draw_grid_x = true;
  mnvPlotter.axis_draw_grid_y = true;
  //hist->Scale(1,"width");
  mnvPlotter.DrawDataMCWithErrorBand(datahist, hist, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);
  //mnvPlotter.DrawMCWithErrorBand(hist); //I think that this call only shows stat errors.

  TLatex* text = new TLatex;
  text->SetNDC();
  text->SetTextSize(0.05);
  text->SetTextColor(kBlue);
  double xplace = .2;
  double yplace = 0.75;

  if (AreaNormalized==true){
    text->DrawLatex(xplace, yplace, Form("Area Normalized"));
    //legend->AddEntry((TObject*)0, "Area normalized", ""); // to put fit param
    //legend->AddEntry((TObject*)0, " ", "");
  }

  yplace-=.05;
  text->DrawLatex(xplace, yplace , RMSchar);

  //legend->AddEntry((TObject*)0, RMSchar, ""); // to put fit param

  //legend->SetTextSize(0.04);
  //legend->Draw("same");
  delete text;
  mnvPlotter.AddHistoTitle(histotitle,.03);
  mnvPlotter.WritePreliminary("TR", .03, 0, 0, false);
  std::string plotname = Form("%s",pdf_name.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");
  if(PrintErrors==true){
    mnvPlotter.legend_n_columns = 2;
    PlotErrorSummaryNew(hist, plotname, histotitle, xaxislabel.c_str(), &cE, &mnvPlotter,true,PrintallErrorGroups);
    mnvPlotter.legend_n_columns = 1;
  }

  if(doBinwidth==true)mnvPlotter.draw_normalized_to_bin_width=!doBinwidth;
  cE.Closed();

}// End of function
/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////

void DrawCVAndError_3tankRegionsHIST_withRMS(
  MnvH1D *hist_upstreamCap_input,
   MnvH1D *hist_barrel_input,
   MnvH1D *hist_downstreamCap_input,
   char *histotitle ,std::string xaxislabel,
   std::string yaxislabel, char* Units,
  std::string pdf_name, bool Setgrid,
  bool doBinwidth, bool PrintRMS_percentage,
  bool AreaNormalized , double Ymax )
{
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  double x1,y1,x2,y2;
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", 5, 10, .025);
  TLegend *legend = new TLegend(x1-.13 , y1+.1 , x2-.125 , y2 + .1  );//x1 - .1, y1- .1 , x2 , y2+.1
  legend->SetBorderSize(0);
  //MnvH1D *hist = (PlotUtils::MnvH1D*)hist_input->Clone("hist");
  //hist->GetXaxis()->SetTitleSize(0.035);
  //hist->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));


  PlotUtils::MnvH1D* hist_upstreamCap =  (PlotUtils::MnvH1D*)hist_upstreamCap_input->Clone("hist_upstreamCap");
  PlotUtils::MnvH1D* hist_barrel =  (PlotUtils::MnvH1D*)hist_barrel_input->Clone("hist_barrel");
  PlotUtils::MnvH1D* hist_downstreamCap =  (PlotUtils::MnvH1D*)hist_downstreamCap_input->Clone("hist_downstreamCap");
  hist_upstreamCap->SetTitle(histotitle);

  if (AreaNormalized==true){
    double Areabarrel = hist_barrel->Integral(0, hist_barrel->GetNbinsX()+1);
    hist_barrel->Scale(1.0/Areabarrel);

    double AreaupstreamCap = hist_upstreamCap->Integral(0, hist_upstreamCap->GetNbinsX()+1);
    hist_upstreamCap->Scale(1.0 / AreaupstreamCap);

    double AreadownstreamCap = hist_downstreamCap->Integral(0, hist_downstreamCap->GetNbinsX()+1);
    hist_downstreamCap->Scale(1.0 / AreadownstreamCap);
  }



  if(doBinwidth==true){
    double binwidth_title = hist_upstreamCap -> GetBinWidth(5);
    char ytitle[1024];
    sprintf(ytitle, "NEvents / %.2f %s", binwidth_title, Units);
    hist_upstreamCap->GetYaxis()->SetTitle(ytitle);//
    hist_barrel->GetYaxis()->SetTitle(ytitle);//
    hist_downstreamCap->GetYaxis()->SetTitle(ytitle);//
  }
  else{
    hist_upstreamCap->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));//
    hist_barrel->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));//
    hist_downstreamCap->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));//
  }

  hist_upstreamCap->GetYaxis()->SetLabelSize(0.035);
  hist_upstreamCap->GetYaxis()->CenterTitle();

  hist_upstreamCap->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));//
  hist_barrel->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));//
  hist_downstreamCap->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist_upstreamCap->GetXaxis()->SetLabelSize(0.035);
  hist_upstreamCap->GetXaxis()->CenterTitle();

  hist_downstreamCap->GetXaxis()->SetLabelSize(0.035);
  hist_downstreamCap->GetXaxis()->CenterTitle();

  hist_barrel->GetXaxis()->SetLabelSize(0.035);
  hist_barrel->GetXaxis()->CenterTitle();

  double RMS_value_upstream;
  double RMS_value_barrel;
  double RMS_value_downstream;

  double RMS_value_upstream_Error;
  double RMS_value_barrel_Error;
  double RMS_value_downstream_Error;


  char RMSupstream_char[1024];
  char RMSbarrel_char[1024];
  char RMSdownstream_char[1024];

  if(PrintRMS_percentage==true){
    RMS_value_upstream = 100 * hist_upstreamCap->GetRMS();
    RMS_value_upstream_Error = 100 * hist_upstreamCap->GetRMSError();
    sprintf(RMSupstream_char ,"UpCap: %.2f #pm %.2f %%",RMS_value_upstream, RMS_value_upstream_Error );

    RMS_value_barrel = 100 * hist_barrel->GetRMS();
    RMS_value_barrel_Error = 100 * hist_barrel->GetRMSError();
    sprintf(RMSbarrel_char ,  "Barrel: %.2f #pm %.2f %%",RMS_value_barrel , RMS_value_barrel_Error );

    RMS_value_downstream = 100 * hist_downstreamCap->GetRMS();
    RMS_value_downstream_Error = 100 * hist_downstreamCap->GetRMSError();
    sprintf(RMSdownstream_char,"DownCap: %.2f #pm %.2f %%",RMS_value_downstream , RMS_value_downstream_Error );
  }

  else if (PrintRMS_percentage==false){
    RMS_value_upstream = hist_upstreamCap->GetRMS();
    RMS_value_upstream_Error = hist_upstreamCap->GetRMSError();
    sprintf(RMSupstream_char , "UpCap: %.2f #pm %.2f [%s]",RMS_value_upstream, RMS_value_upstream_Error, Units );

    RMS_value_barrel = hist_barrel->GetRMS();
    RMS_value_barrel_Error = hist_barrel->GetRMSError();
    sprintf(RMSbarrel_char , "Barrel: %.2f #pm %.2f [%s]",RMS_value_barrel,RMS_value_barrel_Error, Units );

    RMS_value_downstream = hist_downstreamCap->GetRMS();
    RMS_value_downstream_Error = hist_downstreamCap->GetRMSError();
    sprintf(RMSdownstream_char , "DownCap: %.2f #pm %.2f [%s]",RMS_value_downstream,RMS_value_downstream_Error, Units );
  }

  TObjArray m_hist_array;
  PlotUtils::MnvH1D* datahist =new PlotUtils::MnvH1D("adsf", "", nbins, xmin, xmax);

  hist_upstreamCap->SetTitle("Upstream Cap");
  hist_barrel->SetTitle("Barrel");
  hist_downstreamCap->SetTitle("Downstream Cap ");

  hist_upstreamCap->SetTitleOffset(1.2);
  hist_upstreamCap->GetYaxis()->SetTitleOffset(1.5);

  hist_upstreamCap->SetLineColor(3);
  hist_barrel->SetLineColor(kBlue);
  hist_downstreamCap->SetLineColor(kRed);

  hist_upstreamCap->SetLineStyle(2);
  hist_barrel->SetLineStyle(2);
  hist_downstreamCap->SetLineStyle(2);


  hist_upstreamCap->SetLineWidth(3);
  hist_barrel->SetLineWidth(3);
  hist_downstreamCap->SetLineWidth(3);

  hist_upstreamCap->SetMaximum(Ymax);
  hist_barrel->SetMaximum(Ymax);
  hist_downstreamCap->SetMaximum(Ymax);
  datahist->SetMaximum(Ymax);


  m_hist_array.Add(hist_upstreamCap);
  m_hist_array.Add(hist_barrel);
  m_hist_array.Add(hist_downstreamCap);


  bool statPlusSys           = true;
  int mcScale                = 1.;
  bool useHistTitles         = false;
  if(doBinwidth==true)mnvPlotter.draw_normalized_to_bin_width=doBinwidth;
  mnvPlotter.axis_title_size_x = 0.03;
  mnvPlotter.axis_maximum = Ymax;
  //mnvPlotter.axis_title_offset_y = 1.0;
  mnvPlotter.axis_title_size_y = 0.03;
  mnvPlotter.axis_label_size =  0.025;
  mnvPlotter.axis_title_size_y = 0.025;
  //mnvPlotter.axis_draw_grid_x = true;
  //mnvPlotter.axis_draw_grid_y = true;
  //hist->Scale(1,"width");
  bool dataAsPoints =false;
  bool allSolidLines = false;
  bool leaveStyleAlone = true;
  mnvPlotter.DrawDataMCVariations(datahist, &m_hist_array , 1.0, "TL", dataAsPoints, allSolidLines, leaveStyleAlone, false );

  //mnvPlotter.DrawMCWithErrorBand(hist); //I think that this call only shows stat errors.
legend->AddEntry((TObject*)0, "RMS Values", "");
legend->AddEntry((TObject*)0, RMSupstream_char, ""); //
legend->AddEntry((TObject*)0, RMSbarrel_char, ""); //
legend->AddEntry((TObject*)0, RMSdownstream_char, ""); //

  if (AreaNormalized==true){
    legend->AddEntry((TObject*)0, " ", "");
    legend->AddEntry((TObject*)0, "Area normalized", ""); //
  }

  legend->SetTextSize(0.027);
  legend->Draw("same");

  if(Setgrid==true){cE.SetGrid();}
  else if (Setgrid==false){cE.Clear();}
  mnvPlotter.AddHistoTitle(histotitle,.035);
  mnvPlotter.WritePreliminary("TR", .03, 0, 0, false);
  std::string plotname = Form("%s",pdf_name.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");
/*
  if(PrintErrors==true){
    mnvPlotter.legend_n_columns = 2;
    PlotErrorSummaryNew(hist, plotname, histotitle, xaxislabel.c_str(), &cE, &mnvPlotter,true,PrintallErrorGroups);
    mnvPlotter.legend_n_columns = 1;
  }
*/

  if(doBinwidth==true)mnvPlotter.draw_normalized_to_bin_width=!doBinwidth;
  cE.Closed();

}// End of function

/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////
void DrawCVAndError_FromHIST_withFit(
  MnvH1D *hist, char *histotitle,
  std::string xaxislabel,std::string yaxislabel,
  std::string pdf_name, bool Setgrid,
  double &sigma_return , double &TotalN_return,
  double &chi_sq_return, int &NDF_return,
  double &Mean_return,
  double &Constant_return, bool PrintErrors , bool PrintallErrorGroups )
  {

    PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
    TCanvas cE ("c1","c1");
    double x1,y1,x2,y2;
    TLegend *legend = new TLegend (0.65,0.70,0.95,.88);
    mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", 6.5, 6., .025);
    if(Setgrid==true){cE.SetGrid();}
    else if (Setgrid==false){cE.Clear();}
    hist->GetXaxis()->SetTitleSize(0.035);
    hist->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
    hist->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));
    hist->GetYaxis()->CenterTitle();
    double min,max;
    min =  hist->GetXaxis()->GetXmin();
    max =  hist->GetXaxis()->GetXmax();
    int nbins = hist->GetNbinsX();
    TF1 *gfit = new TF1("Gaussian","gaus",min,max);

    gfit->SetParameters(500,hist->GetMean(),hist->GetRMS());
    gfit->SetParNames("Constant","Mean","Sigma");
    hist->Fit(gfit,"RQ");
    auto chi_sq = gfit->GetChisquare();
    auto NDF_int = gfit->GetNDF();

    auto constant_value = gfit->GetParameter(0);
    auto constant_value_error = gfit->GetParError(0);

    auto mean_value = gfit->GetParameter("Mean");

    auto mean_value_error = gfit->GetParError(1);

    auto sigma_value = gfit->GetParameter(2);
    auto sigma_value_error = gfit->GetParError(2);

    //Things to return;
    TotalN_return = hist->Integral(1,nbins);
    std::cout<< "hist->GetIntegral(1,nbins)  = " << TotalN_return<<std::endl;
    //TotalN_return = *TotalN;
    sigma_return = sigma_value;
    Mean_return= mean_value;
    Constant_return = constant_value;
    NDF_return = NDF_int;
    chi_sq_return = chi_sq;


    hist->SetTitle(histotitle);
    PlotUtils::MnvH1D* datahist =new PlotUtils::MnvH1D("adsf", "", nbins, xmin, xmax);
    bool statPlusSys           = true;
    int mcScale                = 1.;
    bool useHistTitles         = false;

    //hist->Scale(1,"width");
    mnvPlotter.DrawDataMCWithErrorBand(datahist, hist, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);
    //mnvPlotter.DrawMCWithErrorBand(hist); //I think that this call only shows stat errors.

    gfit->Draw("same");
    gStyle->SetOptFit(1111);
    char chi_name[1024];
    sprintf(chi_name , "#chi^{2} / ndf = %.2f / %i",chi_sq, NDF_int );
    char sigma_name[1024];
    sprintf(sigma_name , "#sigma  = %.2f #pm %.2f", sigma_value, sigma_value_error );
    char mean_name[1024];
    sprintf(mean_name , "Mean  = %.2f #pm %.2f", mean_value,mean_value_error );
    char contant_name[1024];
    sprintf(contant_name , "Contant  = %.2f #pm %.2f", constant_value, constant_value_error  );


    legend->AddEntry((TObject*)0, chi_name, ""); // to put fit param
    legend->AddEntry((TObject*)0, sigma_name, ""); // to put fit param
    legend->AddEntry((TObject*)0, mean_name, ""); // to put fit param
    legend->AddEntry((TObject*)0, contant_name, ""); // to put fit param

    legend->SetTextSize(0.02);
    legend->Draw("same");


    mnvPlotter.AddHistoTitle(histotitle, .02);
    mnvPlotter.WritePreliminary("TR", .03, 0, 0, false);
    std::string plotname = Form("%s",pdf_name.c_str());
    mnvPlotter.MultiPrint(&cE, plotname, "pdf");
    //PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);
    if(PrintErrors==true){
    mnvPlotter.legend_n_columns = 2;
    // PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);
    PlotErrorSummaryNew(hist, plotname, histotitle, xaxislabel.c_str(), &cE, &mnvPlotter,true, PrintallErrorGroups);
    mnvPlotter.legend_n_columns = 1;
  }

    cE.Closed();

  }

/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////
void FillFitParms(TF1 *gfit, GaussianFitsParms &FitParms ){

    FitParms.ChiSqrt = gfit->GetChisquare();
    FitParms.NDF = gfit->GetNDF();
    FitParms.Constant = gfit->GetParameter(0);
    FitParms.Constant_Error = gfit->GetParError(0);
    FitParms.Mean = gfit->GetParameter("Mean");
    FitParms.Mean_Error = gfit->GetParError(1);
    FitParms.Sigma = gfit->GetParameter(2);
    FitParms.Sigma_Error = gfit->GetParError(2);

  }
/////////////////////////////////////////////////////////////////////////////
//////
//////////////////////////////////////////////////////////////////////////////

void DrawCVAndError_From2HIST_withFit(
  MnvH1D *hist_total, MnvH1D *histHelium,
  MnvH1D *histnonHelium, char *histotitle ,
  std::string xaxislabel,std::string yaxislabel,
  std::string pdf_name, bool Setgrid ,GaussianFitsParms &total_FitParms,
  GaussianFitsParms &helium_FitParms, GaussianFitsParms &nonhelium_FitParms,
  bool PrintErrors , bool PrintallErrorGroups , bool BinWidthNorm )
{
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  double x1,y1,x2,y2;
  TLegend *legend = new TLegend (0.62, 0.40, 0.98,.87);
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", 6.5, 6., .025);
  if(Setgrid==true){cE.SetGrid();}
  else if (Setgrid==false){cE.Clear();}
  //histHelium->GetXaxis()->SetTitleSize(0.035);
  hist_total->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist_total->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));

  histHelium->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  histHelium->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));

  histnonHelium->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  histnonHelium->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));

  hist_total->SetTitleOffset(1.2);
  histHelium->SetTitleOffset(1.2);
  histnonHelium->SetTitleOffset(1.2);


  hist_total->GetYaxis()->SetLabelSize(0.035);
  histHelium->GetYaxis()->SetLabelSize(0.035);
  histnonHelium->GetYaxis()->SetLabelSize(0.035);

  double min_helium =  histHelium->GetXaxis()->GetXmin();
  double max_helium =  histHelium->GetXaxis()->GetXmax();
  double min_nonhelium =  histnonHelium->GetXaxis()->GetXmin();
  double max_nonhelium =  histnonHelium->GetXaxis()->GetXmax();

  double min_Total =  hist_total->GetXaxis()->GetXmin();
  double max_Total =  hist_total->GetXaxis()->GetXmax();


  int nbins_Helium = histHelium->GetNbinsX();
  int nbins_nonHelium = histnonHelium->GetNbinsX();
  int nbins_total = hist_total->GetNbinsX();
  if (nbins_Helium!=nbins_nonHelium ||nbins_nonHelium != nbins_total ) {std::cout<< "ERROR - The Number of bins aren't the same for hist in DrawCVAndError_From2HIST_withFit"<< std::endl; assert(false);}


  TF1 *gfit_helium = new TF1("Gaussian","gaus",min_helium,max_helium);
  TF1 *gfit_nonhelium = new TF1("Gaussian","gaus",min_nonhelium,max_nonhelium);
  TF1 *gfit_total = new TF1("Gaussian","gaus",min_Total, max_Total);

  if(BinWidthNorm== true){
    histHelium->Scale(1,"width");
    histnonHelium->Scale(1,"width");
    hist_total->Scale(1,"width");
  }


  gfit_helium->SetParameters(500, histHelium->GetMean(),histHelium->GetRMS());
  gfit_helium->SetParNames("Constant","Mean","Sigma");
  histHelium->Fit(gfit_helium,"RQ");

  gfit_nonhelium->SetParameters(500,histnonHelium->GetMean(),histnonHelium->GetRMS());
  gfit_nonhelium->SetParNames("Constant","Mean","Sigma");
  histnonHelium->Fit(gfit_nonhelium,"RQ");

  gfit_total->SetParameters(500,hist_total->GetMean(),hist_total->GetRMS());
  gfit_total->SetParNames("Constant","Mean","Sigma");
  hist_total->Fit(gfit_total,"RQ");


  FillFitParms(gfit_helium, helium_FitParms );
  FillFitParms(gfit_nonhelium, nonhelium_FitParms );
  FillFitParms(gfit_total, total_FitParms );

  helium_FitParms.TotalN = histHelium->Integral(1,nbins);
  nonhelium_FitParms.TotalN = histnonHelium->Integral(1,nbins);
  total_FitParms.TotalN = hist_total->Integral(1,nbins);

  std::cout<< "histHelium->GetIntegral(1,nbins)  = " << helium_FitParms.TotalN<<std::endl;


  mnvPlotter.axis_title_size_x = 0.03;
  //mnvPlotter.axis_title_offset_y = 1.0;
  mnvPlotter.axis_title_size_y = 0.03;
  mnvPlotter.axis_label_size =  0.025;
  mnvPlotter.axis_title_size_y = 0.025;
  mnvPlotter.axis_draw_grid_x = true;
  mnvPlotter.axis_draw_grid_y = true;

  histHelium->SetTitle("{}^{4}He");
  histnonHelium->SetTitle("non-{}^{4}He");
  hist_total->SetTitle("Total");
  hist_total->SetLineColor(kBlack);
  histHelium->SetLineColor(kBlue);
  histnonHelium->SetLineColor(kRed);
  TObjArray m_hist_array;

  m_hist_array.Add(hist_total);
  m_hist_array.Add(histnonHelium);
  m_hist_array.Add(histHelium);

  PlotUtils::MnvH1D* datahist =new PlotUtils::MnvH1D("adsf", "", nbins, xmin, xmax);
  datahist->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  datahist->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));

  bool dataAsPoints =false;
  bool allSolidLines = true;
  bool leaveStyleAlone = true;
  mnvPlotter.DrawDataMCVariations(datahist, &m_hist_array , 1.0, "TL", dataAsPoints, allSolidLines, leaveStyleAlone, false );
  //hist->Scale(1,"width");
  gfit_helium->SetLineColor(kBlue);
  gfit_nonhelium->SetLineColor(kRed);
  gfit_total->SetLineColor(kBlack);


  gfit_helium->Draw("same");
  gfit_nonhelium->Draw("same");
  gfit_total->Draw("same");
  gStyle->SetOptFit(1111);

  char chi_name[1024];
  char sigma_name[1024];
  char mean_name[1024];
  char contant_name[1024];

  sprintf(chi_name,     "#chi^{2} / ndf = %.2f / %i = %.2f",total_FitParms.ChiSqrt, total_FitParms.NDF , total_FitParms.ChiSqrt /(double)total_FitParms.NDF);
  sprintf(sigma_name,   "#sigma  = %.2f #pm %.2f",   total_FitParms.Sigma,   total_FitParms.Sigma_Error);
  sprintf(mean_name,    "Mean  = %.2f #pm %.2f",     total_FitParms.Mean,    total_FitParms.Mean_Error);
  sprintf(contant_name, "Contant  = %.2f #pm %.2f",  total_FitParms.Constant,total_FitParms.Constant_Error);

  legend->AddEntry(gfit_total, "Total", "l");
  legend->AddEntry((TObject*)0, chi_name, ""); // to put fit param
  legend->AddEntry((TObject*)0, sigma_name, ""); // to put fit param
  legend->AddEntry((TObject*)0, mean_name, ""); // to put fit param
  legend->AddEntry((TObject*)0, contant_name, ""); // to put fit param

  sprintf(chi_name,    "#chi^{2} / ndf = %.2f / %i = %.2f",helium_FitParms.ChiSqrt, helium_FitParms.NDF , helium_FitParms.ChiSqrt / (double)helium_FitParms.NDF);
  sprintf(sigma_name,  "#sigma  = %.2f #pm %.2f",   helium_FitParms.Sigma,   helium_FitParms.Sigma_Error);
  sprintf(mean_name,   "Mean  = %.2f #pm %.2f",     helium_FitParms.Mean,    helium_FitParms.Mean_Error);
  sprintf(contant_name,"Contant  = %.2f #pm %.2f",  helium_FitParms.Constant,helium_FitParms.Constant_Error);

  legend->AddEntry(gfit_helium, "{}^{4}He Fit", "l");
  legend->AddEntry((TObject*)0, chi_name, ""); // to put fit param
  legend->AddEntry((TObject*)0, sigma_name, ""); // to put fit param
  legend->AddEntry((TObject*)0, mean_name, ""); // to put fit param
  legend->AddEntry((TObject*)0, contant_name, ""); // to put fit param

  sprintf(chi_name,    "#chi^{2} / ndf = %.2f / %i = %.2f",nonhelium_FitParms.ChiSqrt, nonhelium_FitParms.NDF,nonhelium_FitParms.ChiSqrt / (double)nonhelium_FitParms.NDF );
  sprintf(sigma_name,  "#sigma  = %.2f #pm %.2f",   nonhelium_FitParms.Sigma,   nonhelium_FitParms.Sigma_Error);
  sprintf(mean_name,   "Mean  = %.2f #pm %.2f",     nonhelium_FitParms.Mean,    nonhelium_FitParms.Mean_Error);
  sprintf(contant_name,"Contant  = %.2f #pm %.2f",  nonhelium_FitParms.Constant,nonhelium_FitParms.Constant_Error);

  legend->AddEntry((TObject*)0, " ", ""); // to put fit param
  legend->AddEntry(gfit_nonhelium, "Non-{}^{4}He Fit", "l");
  legend->AddEntry((TObject*)0, chi_name, ""); // to put fit param
  legend->AddEntry((TObject*)0, sigma_name, ""); // to put fit param
  legend->AddEntry((TObject*)0, mean_name, ""); // to put fit param
  legend->AddEntry((TObject*)0, contant_name, ""); // to put fit param


  legend->SetTextSize(0.025);
  legend->Draw("same");


  mnvPlotter.AddHistoTitle(histotitle, .028);
  mnvPlotter.WritePreliminary("TR", .03, 0, 0, false);
  std::string plotname = Form("%s",pdf_name.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");
  //PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);
  if(PrintErrors==true){
    mnvPlotter.legend_n_columns = 2;
    // PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);
    PlotErrorSummaryNew(histHelium, plotname, histotitle, xaxislabel.c_str(), &cE, &mnvPlotter,true, PrintallErrorGroups);
    mnvPlotter.legend_n_columns = 1;
  }

  mnvPlotter.axis_draw_grid_x = false;
  mnvPlotter.axis_draw_grid_y = false;
  cE.Closed();

}

/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////

void DrawCVAndError_From2HIST(
  MnvH1D *hist_total, MnvH1D *histHelium, MnvH1D *histnonHelium,
  char *histotitle ,std::string xaxislabel,std::string yaxislabel,
  std::string pdf_name, bool Setgrid , bool PrintErrors,
  bool PrintallErrorGroups , bool BinWidthNorm , double Ymax , bool setLogY)
{
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  double x1,y1,x2,y2;
  TLegend *legend = new TLegend (0.62, 0.40, 0.98,.87);
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", 6.5, 6., .025);
  if(Setgrid==true){cE.SetGrid();}
  else if (Setgrid==false){cE.Clear();}
  if (setLogY==true){gPad->SetLogy(1);}
  //histHelium->GetXaxis()->SetTitleSize(0.035);
  hist_total->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist_total->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));

  hist_total->SetMaximum(Ymax);
  histHelium->SetMaximum(Ymax);
  histnonHelium->SetMaximum(Ymax);


  histHelium->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  histHelium->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));

  histnonHelium->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  histnonHelium->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));

  hist_total->SetTitleOffset(1.2);
  histHelium->SetTitleOffset(1.2);
  histnonHelium->SetTitleOffset(1.2);

  double min_helium =  histHelium->GetXaxis()->GetXmin();
  double max_helium =  histHelium->GetXaxis()->GetXmax();
  double min_nonhelium =  histnonHelium->GetXaxis()->GetXmin();
  double max_nonhelium =  histnonHelium->GetXaxis()->GetXmax();

  double min_Total =  hist_total->GetXaxis()->GetXmin();
  double max_Total =  hist_total->GetXaxis()->GetXmax();


  int nbins_Helium = histHelium->GetNbinsX();
  int nbins_nonHelium = histnonHelium->GetNbinsX();
  int nbins_total = hist_total->GetNbinsX();
  if (nbins_Helium!=nbins_nonHelium ||nbins_nonHelium != nbins_total ) {std::cout<< "ERROR - The Number of bins aren't the same for hist in DrawCVAndError_From2HIST_withFit"<< std::endl; assert(false);}


  if(BinWidthNorm== true){
    histHelium->Scale(1,"width");
    histnonHelium->Scale(1,"width");
    hist_total->Scale(1,"width");
  }


  mnvPlotter.axis_title_size_x = 0.03;
  //mnvPlotter.axis_title_offset_y = 1.0;
  mnvPlotter.axis_title_size_y = 0.03;
  mnvPlotter.axis_label_size =  0.028;
  mnvPlotter.axis_title_size_y = 0.025;
  mnvPlotter.axis_draw_grid_x = true;
  mnvPlotter.axis_draw_grid_y = true;
  mnvPlotter.axis_maximum = Ymax;
  histHelium->SetTitle("{}^{4}He");
  histnonHelium->SetTitle("non-{}^{4}He");
  hist_total->SetTitle("Total");

  hist_total->SetLineColor(kBlack);
  histHelium->SetLineColor(kBlue);
  histnonHelium->SetLineColor(kRed);
  TObjArray m_hist_array;

  m_hist_array.Add(hist_total);
  m_hist_array.Add(histnonHelium);
  m_hist_array.Add(histHelium);

  PlotUtils::MnvH1D* datahist =new PlotUtils::MnvH1D("adsf", "", nbins, xmin, xmax);
  datahist->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  datahist->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));
  datahist->SetMaximum(Ymax);
  bool dataAsPoints =false;
  bool allSolidLines = true;
  bool leaveStyleAlone = true;
  mnvPlotter.DrawDataMCVariations(datahist, &m_hist_array , 1.0, "TL", dataAsPoints, allSolidLines, leaveStyleAlone, false );


  mnvPlotter.AddHistoTitle(histotitle, .028);
  mnvPlotter.WritePreliminary("TR", .03, 0, 0, false);
  std::string plotname = Form("%s",pdf_name.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");
  //PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);
  if(PrintErrors==true){
    mnvPlotter.legend_n_columns = 2;
    // PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);
    char ErrorTitles[1024];
    sprintf(ErrorTitles , "%s [Helium] ",histotitle );
    PlotErrorSummaryNew(histHelium, plotname, ErrorTitles, xaxislabel.c_str(), &cE, &mnvPlotter,true, PrintallErrorGroups);
    sprintf(ErrorTitles , "%s [nonHelium] ",histotitle );
    PlotErrorSummaryNew(histnonHelium, plotname, ErrorTitles, xaxislabel.c_str(), &cE, &mnvPlotter,true, PrintallErrorGroups);
    sprintf(ErrorTitles , "%s [Total] ",histotitle );
    PlotErrorSummaryNew(hist_total, plotname, ErrorTitles, xaxislabel.c_str(), &cE, &mnvPlotter,true, PrintallErrorGroups);

    mnvPlotter.legend_n_columns = 1;
  }
  if (setLogY==true){gPad->SetLogy(0);}
  mnvPlotter.axis_draw_grid_x = false;
  mnvPlotter.axis_draw_grid_y = false;
  cE.Closed();

}

//////////////////////////////////////////////////////////////////////////////
//////
//////////////////////////////////////////////////////////////////////////////

void DrawCVAndError_From6HIST_RECO_vs_TRUE(
  MnvH1D *hist_total_TRUE, MnvH1D *histHelium_TRUE,
   MnvH1D *histnonHelium_TRUE,
   MnvH1D *hist_total_RECO, MnvH1D *histHelium_RECO,
   MnvH1D *histnonHelium_RECO, char *histotitle,
   std::string xaxislabel,std::string yaxislabel,
   std::string pdf_name, bool Setgrid , bool PrintErrors,
    bool PrintallErrorGroups , bool BinWidthNorm , double Ymax , bool setLogY)
{

  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  double x1,y1,x2,y2;
  TLegend *legend = new TLegend (0.62, 0.40, 0.98,.87);
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", 6.5, 6., .025);
  if(Setgrid==true){cE.SetGrid();}
  else if (Setgrid==false){cE.Clear();}
  if (setLogY==true){gPad->SetLogy(1);}
  //histHelium->GetXaxis()->SetTitleSize(0.035);
  hist_total_TRUE->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist_total_TRUE->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));

  hist_total_TRUE->SetMaximum(Ymax);
  histHelium_TRUE->SetMaximum(Ymax);
  histnonHelium_TRUE->SetMaximum(Ymax);


  //hist_total_RECO->SetMaximum(Ymax);
  //histHelium_RECO->SetMaximum(Ymax);
  //histnonHelium_RECO->SetMaximum(Ymax);


  histHelium_TRUE->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  histHelium_TRUE->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));

  histnonHelium_TRUE->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  histnonHelium_TRUE->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));

  hist_total_TRUE->SetTitleOffset(1.2);
  histHelium_TRUE->SetTitleOffset(1.2);
  histnonHelium_TRUE->SetTitleOffset(1.2);

  //histHelium->SetTitleOffset(0.);
  //histnonHelium->SetTitleOffset(0.);

  double min_helium =  histHelium_TRUE->GetXaxis()->GetXmin();
  double max_helium =  histHelium_TRUE->GetXaxis()->GetXmax();
  double min_nonhelium =  histnonHelium_TRUE->GetXaxis()->GetXmin();
  double max_nonhelium =  histnonHelium_TRUE->GetXaxis()->GetXmax();

  double min_Total =  hist_total_TRUE->GetXaxis()->GetXmin();
  double max_Total =  hist_total_TRUE->GetXaxis()->GetXmax();


  int nbins_Helium = histHelium_TRUE->GetNbinsX();
  int nbins_nonHelium = histnonHelium_TRUE->GetNbinsX();
  int nbins_total = hist_total_TRUE->GetNbinsX();
  if (nbins_Helium!=nbins_nonHelium ||nbins_nonHelium != nbins_total ) {std::cout<< "ERROR - The Number of bins aren't the same for hist in DrawCVAndError_From2HIST_withFit"<< std::endl; assert(false);}


  if(BinWidthNorm== true){
    histHelium_TRUE->Scale(1,"width");
    histnonHelium_TRUE->Scale(1,"width");
    hist_total_TRUE->Scale(1,"width");
    histHelium_RECO->Scale(1,"width");
    histnonHelium_RECO->Scale(1,"width");
    hist_total_RECO->Scale(1,"width");
  }


  mnvPlotter.axis_title_size_x = 0.03;
  //mnvPlotter.axis_title_offset_y = 1.0;
  mnvPlotter.axis_title_size_y = 0.03;
  mnvPlotter.axis_label_size =  0.028;
  mnvPlotter.axis_title_size_y = 0.025;
  mnvPlotter.axis_draw_grid_x = true;
  mnvPlotter.axis_draw_grid_y = true;
  mnvPlotter.axis_maximum = Ymax;
  histHelium_TRUE->SetTitle("TRUE {}^{4}He");
  histnonHelium_TRUE->SetTitle("TRUE non-{}^{4}He");
  hist_total_TRUE->SetTitle("TRUE Total");

  histHelium_RECO->SetTitle("RECO {}^{4}He");
  histnonHelium_RECO->SetTitle("RECO non-{}^{4}He");
  hist_total_RECO->SetTitle("RECO Total");

  hist_total_TRUE->SetLineColor(28);
  histHelium_TRUE->SetLineColor(8);
  histnonHelium_TRUE->SetLineColor(6);

  hist_total_TRUE->SetLineStyle(1);
  histHelium_TRUE->SetLineStyle(2);
  histnonHelium_TRUE->SetLineStyle(2);

  hist_total_RECO->SetLineColor(kBlack);
  histHelium_RECO->SetLineColor(kBlue);
  histnonHelium_RECO->SetLineColor(kRed);

  hist_total_RECO->SetLineStyle(1);
  histHelium_RECO->SetLineStyle(7);
  histnonHelium_RECO->SetLineStyle(7);


  hist_total_TRUE->SetLineWidth(2);
  histHelium_TRUE->SetLineWidth(3);
  histnonHelium_TRUE->SetLineWidth(3);

  hist_total_RECO->SetLineWidth(2);
  histHelium_RECO->SetLineWidth(3);
  histnonHelium_RECO->SetLineWidth(3);


  TObjArray m_hist_array;

  m_hist_array.Add(hist_total_TRUE);
  m_hist_array.Add(histnonHelium_TRUE);
  m_hist_array.Add(histHelium_TRUE);

  m_hist_array.Add(hist_total_RECO);
  m_hist_array.Add(histnonHelium_RECO);
  m_hist_array.Add(histHelium_RECO);


  PlotUtils::MnvH1D* datahist =new PlotUtils::MnvH1D("adsf", "", nbins, xmin, xmax);
  datahist->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  datahist->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));
  datahist->SetMaximum(Ymax);
  bool dataAsPoints =false;
  bool allSolidLines = true;
  bool leaveStyleAlone = true;
  mnvPlotter.DrawDataMCVariations(datahist, &m_hist_array , 1.0, "TL", dataAsPoints, allSolidLines, leaveStyleAlone, false );


  mnvPlotter.AddHistoTitle(histotitle, .028);
  mnvPlotter.WritePreliminary("TR", .03, 0, 0, false);
  std::string plotname = Form("%s",pdf_name.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");
  //PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);
  if(PrintErrors==true){
    mnvPlotter.legend_n_columns = 2;
    // PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);
    char ErrorTitles[1024];
    sprintf(ErrorTitles , "%s [Helium] ",histotitle );
    PlotErrorSummaryNew(histHelium_TRUE, plotname, ErrorTitles, xaxislabel.c_str(), &cE, &mnvPlotter,true, PrintallErrorGroups);
    sprintf(ErrorTitles , "%s [nonHelium] ",histotitle );
    PlotErrorSummaryNew(histnonHelium_TRUE, plotname, ErrorTitles, xaxislabel.c_str(), &cE, &mnvPlotter,true, PrintallErrorGroups);
    sprintf(ErrorTitles , "%s [Total] ",histotitle );
    PlotErrorSummaryNew(hist_total_TRUE, plotname, ErrorTitles, xaxislabel.c_str(), &cE, &mnvPlotter,true, PrintallErrorGroups);

    mnvPlotter.legend_n_columns = 1;
  }
  if (setLogY==true){gPad->SetLogy(0);}
  mnvPlotter.axis_draw_grid_x = false;
  mnvPlotter.axis_draw_grid_y = false;
  cE.Closed();

}

/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////
void DrawCVAndError_From2HIST(
  MnvH1D *hist_1_input, char *legend_1_title,
  MnvH1D *hist_2_input, char *legend_2_title,
    char *histotitle ,std::string xaxislabel, std::string yaxislabel,
   std::string pdf_name, bool Setgrid, bool PrintErrors,
  bool PrintallErrorGroups, bool BinWidthNorm,
   double Ymax, bool setLogY,  bool setLogX)
{
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  double x1,y1,x2,y2;
  PlotUtils::MnvH1D* hist_1 = hist_1_input->Clone("hist_1");
  PlotUtils::MnvH1D* hist_2 = hist_2_input->Clone("hist_2");
  TLegend *legend = new TLegend (0.62, 0.40, 0.98,.87);
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", 6.5, 6., .025);
  if(Setgrid==true){cE.SetGrid();}
  else if (Setgrid==false){cE.Clear();}
  if (setLogY==true){
    hist_1->SetMinimum(.001);
    hist_2->SetMinimum(.001);
    gPad->SetLogy(1);}

if(setLogX==true){
  hist_1->GetXaxis()->SetRange(.001,20.0);
  hist_2->GetXaxis()->SetRange(.001,20.0);
gPad->SetLogx();

}


  //histHelium->GetXaxis()->SetTitleSize(0.035);
  hist_1->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist_1->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));

  hist_2->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist_2->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));

  hist_1->SetTitleOffset(1.2);
  hist_2->SetTitleOffset(1.2);
  if(Ymax != -99){
    hist_1->SetMaximum(Ymax);
    hist_2->SetMaximum(Ymax);
  }
else{
double max1 = hist_1->GetMaximum();
double max2 = hist_2->GetMaximum();

if(max1 > max2){
  hist_1->SetMaximum(max1* 1.25);
  hist_2->SetMaximum(max1* 1.25);

}
else{
  hist_1->SetMaximum(max2* 1.25);
  hist_2->SetMaximum(max2* 1.25);

}

}


  int nbins_1 = hist_1->GetNbinsX();
  int nbins_2 = hist_2->GetNbinsX();

  //if (nbins_1!=nbins_2 ) {std::cout<< "ERROR - The Number of bins aren't the same for hist in DrawCVAndError_From2HIST_withFit"<< std::endl; assert(false);}


  if(BinWidthNorm== true){
    hist_1->Scale(1,"width");
    hist_2->Scale(1,"width");
  }


  mnvPlotter.axis_title_size_x = 0.025;
  //mnvPlotter.axis_title_offset_y = 1.0;
  mnvPlotter.axis_title_size_y = 0.03;
  mnvPlotter.axis_label_size =  0.028;
  mnvPlotter.axis_title_size_y = 0.025;
  mnvPlotter.axis_draw_grid_x = true;
  mnvPlotter.axis_draw_grid_y = true;
  if(Ymax != -99) mnvPlotter.axis_maximum = Ymax;
  if(Ymax != -99) mnvPlotter.axis_minimum = .7;
  hist_1->SetTitle(legend_1_title);
  hist_2->SetTitle(legend_2_title);


  hist_1->SetLineColor(kBlue);
  hist_2->SetLineColor(kRed);
  TObjArray m_hist_array;

  m_hist_array.Add(hist_1);
  m_hist_array.Add(hist_2);

  PlotUtils::MnvH1D* datahist =new PlotUtils::MnvH1D("adsf", "", nbins, xmin, xmax);
  datahist->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  datahist->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));
  datahist->SetMaximum(Ymax);
  bool dataAsPoints =false;
  bool allSolidLines = true;
  bool leaveStyleAlone = true;
  mnvPlotter.DrawDataMCVariations(datahist, &m_hist_array , 1.0, "TL", dataAsPoints, allSolidLines, leaveStyleAlone, false );

  mnvPlotter.AddHistoTitle(histotitle, .028);
  mnvPlotter.WritePreliminary("TR", .03, 0, 0, false);
  std::string plotname = Form("%s",pdf_name.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");
  //PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);
  if(PrintErrors==true){
    mnvPlotter.legend_n_columns = 2;
    // PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);
    char ErrorTitles[1024];
    sprintf(ErrorTitles , "%s [%s] ",histotitle, legend_1_title );
    PlotErrorSummaryNew(hist_1, plotname, ErrorTitles, xaxislabel.c_str(), &cE, &mnvPlotter,true, PrintallErrorGroups);
    sprintf(ErrorTitles , "%s [%s] ",histotitle, legend_2_title );
    PlotErrorSummaryNew(hist_2, plotname, ErrorTitles, xaxislabel.c_str(), &cE, &mnvPlotter,true, PrintallErrorGroups);

    mnvPlotter.legend_n_columns = 1;
  }

  mnvPlotter.axis_draw_grid_x = false;
  mnvPlotter.axis_draw_grid_y = false;
  if(setLogY==true){gPad->SetLogy(0);}
  if(setLogX==true){gPad->SetLogx(0);}
  cE.Closed();

}
//////////////////////////////////////////////////////////////////////////////
//////
//////////////////////////////////////////////////////////////////////////////
void DrawCVAndError_From5HIST(
  MnvH1D *hist_1_input, char *legend_1_title ,
  MnvH1D *hist_2_input,char *legend_2_title,
  MnvH1D *hist_3_input,char *legend_3_title,
  MnvH1D *hist_4_input,char *legend_4_title,
  MnvH1D *hist_5_input,char *legend_5_title,
  char *histotitle ,std::string xaxislabel, std::string yaxislabel,
  std::string pdf_name, bool Setgrid, bool PrintErrors,
  bool PrintallErrorGroups, bool BinWidthNorm,
  double Ymax, double Ymin,  bool setLogY,  bool setLogX )
{

  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  double x1,y1,x2,y2;
    mnvPlotter.legend_n_columns = 2;
  PlotUtils::MnvH1D* hist_1 = hist_1_input->Clone("hist_1");
  PlotUtils::MnvH1D* hist_2 = hist_2_input->Clone("hist_2");
  PlotUtils::MnvH1D* hist_3 = hist_3_input->Clone("hist_3");
  PlotUtils::MnvH1D* hist_4 = hist_4_input->Clone("hist_4");
  PlotUtils::MnvH1D* hist_5 = hist_5_input->Clone("hist_5");


  TLegend *legend = new TLegend (0.62, 0.40, 0.98,.87);
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", 6.5, 6., .025);
  if(Setgrid==true){cE.SetGrid();}
  else if (Setgrid==false){cE.Clear();}
  if (setLogY==true){
    hist_1->SetMinimum(.001);
    hist_2->SetMinimum(.001);
    gPad->SetLogy(1);}

if(setLogX==true){
  hist_1->GetXaxis()->SetRange(.001,20.0);
  hist_2->GetXaxis()->SetRange(.001,20.0);
  hist_3->GetXaxis()->SetRange(.001,20.0);
  hist_4->GetXaxis()->SetRange(.001,20.0);
  hist_5->GetXaxis()->SetRange(.001,20.0);
  gPad->SetLogx();

}


  //histHelium->GetXaxis()->SetTitleSize(0.035);
  hist_1->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist_1->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));

  hist_2->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist_2->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));

  hist_1->SetTitleOffset(1.2);
  hist_2->SetTitleOffset(1.2);
  if(Ymax != -99){
    hist_1->SetMaximum(Ymax);
    hist_2->SetMaximum(Ymax);
  }
else{
double max1 = hist_1->GetMaximum();
double max2 = hist_2->GetMaximum();

if(max1 > max2){
  hist_1->SetMaximum(max1* 1.25);
  hist_2->SetMaximum(max1* 1.25);

}
else{
  hist_1->SetMaximum(max2* 1.25);
  hist_2->SetMaximum(max2* 1.25);

}

}

  int nbins_1 = hist_1->GetNbinsX();
  int nbins_2 = hist_2->GetNbinsX();

  if (nbins_1!=nbins_2 ) {std::cout<< "ERROR - The Number of bins aren't the same for hist in DrawCVAndError_From2HIST_withFit"<< std::endl; assert(false);}


  if(BinWidthNorm== true){
    hist_1->Scale(1,"width");
    hist_2->Scale(1,"width");
    hist_3->Scale(1,"width");
    hist_4->Scale(1,"width");
    hist_5->Scale(1,"width");
  }


  mnvPlotter.axis_title_size_x = 0.025;
  //mnvPlotter.axis_title_offset_y = 1.0;
  mnvPlotter.axis_label_size =  0.028;
  mnvPlotter.axis_title_size_y = 0.025;
  mnvPlotter.axis_draw_grid_x = true;
  mnvPlotter.axis_draw_grid_y = true;
  if(Ymax != -99) mnvPlotter.axis_maximum = Ymax;
  if(Ymax != -99) mnvPlotter.axis_minimum = Ymin;
  hist_1->SetTitle(legend_1_title);
  hist_2->SetTitle(legend_2_title);
  hist_3->SetTitle(legend_3_title);
  hist_4->SetTitle(legend_4_title);
  hist_5->SetTitle(legend_5_title);


  hist_1->SetLineColor(kBlack);
  hist_1->SetLineStyle(2);
  hist_2->SetLineColor(kRed);
  hist_3->SetLineColor(kGreen);
  hist_4->SetLineColor(kTeal);
  hist_5->SetLineColor(kBlue);


  hist_1->SetLineWidth(2);
  hist_2->SetLineWidth(2);
  hist_3->SetLineWidth(2);
  hist_4->SetLineWidth(2);
  hist_5->SetLineWidth(2);



  TObjArray m_hist_array;

  m_hist_array.Add(hist_1);
  m_hist_array.Add(hist_2);
  m_hist_array.Add(hist_3);
  m_hist_array.Add(hist_4);
  m_hist_array.Add(hist_5);


  PlotUtils::MnvH1D* datahist =new PlotUtils::MnvH1D("adsf", "", nbins, xmin, xmax);
  datahist->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  datahist->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));
  datahist->SetMaximum(Ymax);
  bool dataAsPoints =false;
  bool allSolidLines = true;
  bool leaveStyleAlone = true;
  mnvPlotter.DrawDataMCVariations(datahist, &m_hist_array , 1.0, "TL", dataAsPoints, allSolidLines, leaveStyleAlone, false );

  mnvPlotter.AddHistoTitle(histotitle, .028);
  mnvPlotter.WritePreliminary("TR", .03, 0, 0, false);
  std::string plotname = Form("%s",pdf_name.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");
  //PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);
  if(PrintErrors==true){
    mnvPlotter.legend_n_columns = 2;
    // PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);
    char ErrorTitles[1024];
    sprintf(ErrorTitles , "%s [%s] ",histotitle, legend_1_title );
    PlotErrorSummaryNew(hist_1, plotname, ErrorTitles, xaxislabel.c_str(), &cE, &mnvPlotter,true, PrintallErrorGroups);
    sprintf(ErrorTitles , "%s [%s] ",histotitle, legend_2_title );
    PlotErrorSummaryNew(hist_2, plotname, ErrorTitles, xaxislabel.c_str(), &cE, &mnvPlotter,true, PrintallErrorGroups);

    mnvPlotter.legend_n_columns = 1;
  }

  mnvPlotter.axis_draw_grid_x = false;
  mnvPlotter.axis_draw_grid_y = false;
  if(setLogY==true){gPad->SetLogy(0);}
  if(setLogX==true){gPad->SetLogx(0);}
  cE.Closed();
}
//////////////////////////////////////////////////////////////////////////////
//////
//////////////////////////////////////////////////////////////////////////////
void DrawCVAndError_From6HIST(
  MnvH1D *hist_1_input, char *legend_1_title ,
  MnvH1D *hist_2_input,char *legend_2_title,
  MnvH1D *hist_3_input,char *legend_3_title,
  MnvH1D *hist_4_input,char *legend_4_title,
  MnvH1D *hist_5_input,char *legend_5_title,
  MnvH1D *hist_6_input,char *legend_6_title,
  char *histotitle ,std::string xaxislabel, std::string yaxislabel,
  std::string pdf_name, bool Setgrid, bool PrintErrors,
  bool PrintallErrorGroups, bool BinWidthNorm, double Ymax , bool setLogY,  bool setLogX )
  {
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  double x1,y1,x2,y2;
  PlotUtils::MnvH1D* hist_1 = hist_1_input->Clone("hist_1");
  PlotUtils::MnvH1D* hist_2 = hist_2_input->Clone("hist_2");
  PlotUtils::MnvH1D* hist_3 = hist_3_input->Clone("hist_3");
  PlotUtils::MnvH1D* hist_4 = hist_4_input->Clone("hist_4");
  PlotUtils::MnvH1D* hist_5 = hist_5_input->Clone("hist_5");
  PlotUtils::MnvH1D* hist_6 = hist_6_input->Clone("hist_6");



  TLegend *legend = new TLegend (0.62, 0.40, 0.98,.87);
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", 6.5, 6., .025);
  if(Setgrid==true){cE.SetGrid();}
  else if (Setgrid==false){cE.Clear();}
  if (setLogY==true){
    hist_1->SetMinimum(.001);
    hist_2->SetMinimum(.001);
    gPad->SetLogy(1);}

if(setLogX==true){
  hist_1->GetXaxis()->SetRange(.001,20.0);
  hist_2->GetXaxis()->SetRange(.001,20.0);
  hist_3->GetXaxis()->SetRange(.001,20.0);
  hist_4->GetXaxis()->SetRange(.001,20.0);
  hist_5->GetXaxis()->SetRange(.001,20.0);
  hist_6->GetXaxis()->SetRange(.001,20.0);
  gPad->SetLogx();

}


  //histHelium->GetXaxis()->SetTitleSize(0.035);
  hist_1->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist_1->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));

  hist_2->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist_2->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));

  hist_1->SetTitleOffset(1.2);
  hist_2->SetTitleOffset(1.2);
  if(Ymax != -99){
    hist_1->SetMaximum(Ymax);
    hist_2->SetMaximum(Ymax);
  }
else{
double max1 = hist_1->GetMaximum();
double max2 = hist_2->GetMaximum();

if(max1 > max2){
  hist_1->SetMaximum(max1* 1.25);
  hist_2->SetMaximum(max1* 1.25);

}
else{
  hist_1->SetMaximum(max2* 1.25);
  hist_2->SetMaximum(max2* 1.25);

}

}


  int nbins_1 = hist_1->GetNbinsX();
  int nbins_2 = hist_2->GetNbinsX();

  //if (nbins_1!=nbins_2 ) {std::cout<< "ERROR - The Number of bins aren't the same for hist in DrawCVAndError_From2HIST_withFit"<< std::endl; assert(false);}


  if(BinWidthNorm== true){
    hist_1->Scale(1,"width");
    hist_2->Scale(1,"width");
    hist_3->Scale(1,"width");
    hist_4->Scale(1,"width");
    hist_5->Scale(1,"width");
    hist_6->Scale(1,"width");
  }


  mnvPlotter.axis_title_size_x = 0.025;
  //mnvPlotter.axis_title_offset_y = 1.0;
  mnvPlotter.axis_title_size_y = 0.03;
  mnvPlotter.axis_label_size =  0.028;
  mnvPlotter.axis_title_size_y = 0.025;
  mnvPlotter.axis_draw_grid_x = true;
  mnvPlotter.axis_draw_grid_y = true;
  if(Ymax != -99) mnvPlotter.axis_maximum = Ymax;
  if(Ymax != -99) mnvPlotter.axis_minimum = .7;
  hist_1->SetTitle(legend_1_title);
  hist_2->SetTitle(legend_2_title);
  hist_3->SetTitle(legend_3_title);
  hist_4->SetTitle(legend_4_title);
  hist_5->SetTitle(legend_5_title);
  hist_6->SetTitle(legend_6_title);

  hist_1->SetLineColor(kBlack);
  hist_1->SetLineStyle(2);
  hist_2->SetLineColor(kRed);
  hist_3->SetLineColor(kGreen);
  hist_4->SetLineColor(kTeal);
  hist_5->SetLineColor(kBlue);
  hist_6->SetLineColor(kViolet);

  hist_1->SetLineWidth(2);
  hist_2->SetLineWidth(2);
  hist_3->SetLineWidth(2);
  hist_4->SetLineWidth(2);
  hist_5->SetLineWidth(2);
  hist_6->SetLineWidth(2);


  TObjArray m_hist_array;

  m_hist_array.Add(hist_1);
  m_hist_array.Add(hist_2);
  m_hist_array.Add(hist_3);
  m_hist_array.Add(hist_4);
  m_hist_array.Add(hist_5);
  m_hist_array.Add(hist_6);



  PlotUtils::MnvH1D* datahist =new PlotUtils::MnvH1D("adsf", "", nbins, xmin, xmax);
  datahist->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  datahist->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));
  datahist->SetMaximum(Ymax);
  bool dataAsPoints =false;
  bool allSolidLines = true;
  bool leaveStyleAlone = true;
  mnvPlotter.DrawDataMCVariations(datahist, &m_hist_array , 1.0, "TL", dataAsPoints, allSolidLines, leaveStyleAlone, false );

  mnvPlotter.AddHistoTitle(histotitle, .028);
  mnvPlotter.WritePreliminary("TR", .03, 0, 0, false);
  std::string plotname = Form("%s",pdf_name.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");
  //PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);
  if(PrintErrors==true){
    mnvPlotter.legend_n_columns = 2;
    // PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);
    char ErrorTitles[1024];
    sprintf(ErrorTitles , "%s [%s] ",histotitle, legend_1_title );
    PlotErrorSummaryNew(hist_1, plotname, ErrorTitles, xaxislabel.c_str(), &cE, &mnvPlotter,true, PrintallErrorGroups);
    sprintf(ErrorTitles , "%s [%s] ",histotitle, legend_2_title );
    PlotErrorSummaryNew(hist_2, plotname, ErrorTitles, xaxislabel.c_str(), &cE, &mnvPlotter,true, PrintallErrorGroups);

    mnvPlotter.legend_n_columns = 1;
  }

  mnvPlotter.axis_draw_grid_x = false;
  mnvPlotter.axis_draw_grid_y = false;
  if(setLogY==true){gPad->SetLogy(0);}
  if(setLogX==true){gPad->SetLogx(0);}
  cE.Closed();

}
//////////////////////////////////////////////////////////////////////////////
//////
//////////////////////////////////////////////////////////////////////////////
void DrawCVAndError_FromDaisyHIST(
  MnvH1D *hist_tracker_input, char *legend_tracker_title ,
  MnvH1D *hist_0_input, char *legend_0_title,
  MnvH1D *hist_1_input, char *legend_1_title,
  MnvH1D *hist_2_input,char *legend_2_title,
  MnvH1D *hist_3_input,char *legend_3_title,
  MnvH1D *hist_4_input,char *legend_4_title,
  MnvH1D *hist_5_input,char *legend_5_title,
  MnvH1D *hist_6_input,char *legend_6_title,
  MnvH1D *hist_7_input,char *legend_7_title,
  MnvH1D *hist_8_input,char *legend_8_title,
  MnvH1D *hist_9_input,char *legend_9_title,
  MnvH1D *hist_10_input,char *legend_10_title,
  MnvH1D *hist_11_input,char *legend_11_title,
  char *histotitle ,std::string xaxislabel, std::string yaxislabel,
   std::string pdf_name, bool Setgrid,
 bool BinWidthNorm, double Ymax , bool setLogY,  bool setLogX )
{
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  double x1,y1,x2,y2;
  mnvPlotter.legend_n_columns = 3;
  mnvPlotter.legend_text_size = mnvPlotter.legend_text_size*.7;
  PlotUtils::MnvH1D* hist_tracker = hist_tracker_input->Clone("hist_tracker");
  PlotUtils::MnvH1D* hist_0 = hist_0_input->Clone("hist_0");
  PlotUtils::MnvH1D* hist_1 = hist_1_input->Clone("hist_1");
  PlotUtils::MnvH1D* hist_2 = hist_2_input->Clone("hist_2");
  PlotUtils::MnvH1D* hist_3 = hist_3_input->Clone("hist_3");
  PlotUtils::MnvH1D* hist_4 = hist_4_input->Clone("hist_4");
  PlotUtils::MnvH1D* hist_5 = hist_5_input->Clone("hist_5");
  PlotUtils::MnvH1D* hist_6 = hist_6_input->Clone("hist_6");
  PlotUtils::MnvH1D* hist_7 = hist_7_input->Clone("hist_7");
  PlotUtils::MnvH1D* hist_8 = hist_8_input->Clone("hist_8");
  PlotUtils::MnvH1D* hist_9 = hist_9_input->Clone("hist_9");
  PlotUtils::MnvH1D* hist_10 = hist_10_input->Clone("hist_10");
  PlotUtils::MnvH1D* hist_11 = hist_11_input->Clone("hist_11");
    mnvPlotter.legend_n_columns = 3;

  TLegend *legend = new TLegend (0.62, 0.40, 0.98,.8);
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", 6.5, 6., .025);
  if(Setgrid==true){cE.SetGrid();}
  else if (Setgrid==false){cE.Clear();}
  if (setLogY==true){
    hist_1->SetMinimum(.001);
    hist_2->SetMinimum(.001);
    gPad->SetLogy(1);}

if(setLogX==true){
  hist_tracker->GetXaxis()->SetRange(.001,20.0);
  hist_0->GetXaxis()->SetRange(.001,20.0);
  hist_1->GetXaxis()->SetRange(.001,20.0);
  hist_2->GetXaxis()->SetRange(.001,20.0);
  hist_3->GetXaxis()->SetRange(.001,20.0);
  hist_4->GetXaxis()->SetRange(.001,20.0);
  hist_5->GetXaxis()->SetRange(.001,20.0);
  hist_6->GetXaxis()->SetRange(.001,20.0);
  hist_7->GetXaxis()->SetRange(.001,20.0);
  hist_8->GetXaxis()->SetRange(.001,20.0);
  hist_9->GetXaxis()->SetRange(.001,20.0);
  hist_10->GetXaxis()->SetRange(.001,20.0);
  hist_11->GetXaxis()->SetRange(.001,20.0);

  gPad->SetLogx();

}


std::vector<int> DaisyColor = {
  TColor::GetColor("#e6194B"), // neonyellow,
  TColor::GetColor("#3cb44b"), //'psychedelic Purple
  TColor::GetColor("#ffe119"), //'sunset yellow'
  TColor::GetColor("#4363d8"),//'skyblue'
  TColor::GetColor("#f58231"), //blue
  TColor::GetColor("#42d4f4"), // yellowishbrown,
  TColor::GetColor("#fabed4"), //green
  TColor::GetColor("#469990"),//2 candy Apple
  TColor::GetColor("#dcbeff"),
  TColor::GetColor("#9A6324"), //Gray
  TColor::GetColor("#00FFFF"),//'aqua'
  TColor::GetColor("#fffac8"), //turquoise
  TColor::GetColor("#aaffc3"),//'Jade'
  TColor::GetColor("#FAFAD2"),  // LightGoldenRodYellow
  TColor::GetColor("#800000"),  // Maroon
  TColor::GetColor("#555555"),  // dark grey

    TColor::GetColor("#F1B6DA"),//pink
  TColor::GetColor("#654522"), // yellowishbrown,
  TColor::GetColor("#8db600"), // yellowgreen,
  TColor::GetColor("#D3D3D3"),  //'lightgrey'
   TColor::GetColor("#90AD1C"),
   TColor::GetColor("#CCDDAA")
};

  //histHelium->GetXaxis()->SetTitleSize(0.035);
  hist_tracker->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist_tracker->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));

  hist_0->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist_0->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));

  hist_tracker->SetTitleOffset(1.2);
  hist_0->SetTitleOffset(1.2);
  if(Ymax != -99){
    hist_tracker->SetMaximum(Ymax);
    hist_0->SetMaximum(Ymax);
  }
else{
double max1 = hist_1->GetMaximum();
double max2 = hist_2->GetMaximum();

if(max1 > max2){
  hist_tracker->SetMaximum(max1* 1.25);
  hist_0->SetMaximum(max1* 1.25);

}
else{
  hist_tracker->SetMaximum(max2* 1.25);
  hist_0->SetMaximum(max2* 1.25);
}

}


  int nbins_1 = hist_1->GetNbinsX();
  int nbins_2 = hist_2->GetNbinsX();

  //if (nbins_1!=nbins_2 ) {std::cout<< "ERROR - The Number of bins aren't the same for hist in DrawCVAndError_From2HIST_withFit"<< std::endl; assert(false);}


  if(BinWidthNorm== true){
    hist_tracker->Scale(1,"width");
    hist_0->Scale(1,"width");
    hist_1->Scale(1,"width");
    hist_2->Scale(1,"width");
    hist_3->Scale(1,"width");
    hist_4->Scale(1,"width");
    hist_5->Scale(1,"width");
    hist_6->Scale(1,"width");
    hist_7->Scale(1,"width");
    hist_8->Scale(1,"width");
    hist_9->Scale(1,"width");
    hist_10->Scale(1,"width");
    hist_11->Scale(1,"width");


  }


  mnvPlotter.axis_title_size_x = 0.025;
    mnvPlotter.axis_title_size_y = 0.025;
  //mnvPlotter.axis_title_offset_y = .8;
  //mnvPlotter.axis_title_offset_x = .8;
  mnvPlotter.axis_label_size =  0.028;

  mnvPlotter.axis_draw_grid_x = true;
  mnvPlotter.axis_draw_grid_y = true;
  if(Ymax != -99) mnvPlotter.axis_maximum = Ymax;
  if(Ymax != -99) mnvPlotter.axis_minimum = .7;
  hist_tracker->SetTitle(legend_tracker_title);
  hist_0->SetTitle(legend_0_title);
  hist_1->SetTitle(legend_1_title);
  hist_2->SetTitle(legend_2_title);
  hist_3->SetTitle(legend_3_title);
  hist_4->SetTitle(legend_4_title);
  hist_5->SetTitle(legend_5_title);
  hist_6->SetTitle(legend_6_title);
  hist_7->SetTitle(legend_7_title);
  hist_8->SetTitle(legend_8_title);
  hist_9->SetTitle(legend_9_title);
  hist_10->SetTitle(legend_10_title);
  hist_11->SetTitle(legend_11_title);

  hist_tracker->SetLineColor(kBlack);
  hist_tracker->SetLineStyle(2);

  hist_0->SetLineColor(DaisyColor.at(0));
  hist_1->SetLineColor(DaisyColor.at(1));
  hist_2->SetLineColor(DaisyColor.at(2));
  hist_3->SetLineColor(DaisyColor.at(3));
  hist_4->SetLineColor(DaisyColor.at(4));
  hist_5->SetLineColor(DaisyColor.at(5));
  hist_6->SetLineColor(DaisyColor.at(6));
  hist_7->SetLineColor(DaisyColor.at(7));
  hist_8->SetLineColor(DaisyColor.at(8));
  hist_9->SetLineColor(DaisyColor.at(9));
  hist_10->SetLineColor(DaisyColor.at(10));
  hist_11->SetLineColor(DaisyColor.at(11));

  hist_0->SetLineWidth(2);
  hist_1->SetLineWidth(2);
  hist_2->SetLineWidth(2);
  hist_3->SetLineWidth(2);
  hist_4->SetLineWidth(2);
  hist_5->SetLineWidth(2);
  hist_6->SetLineWidth(2);
  hist_7->SetLineWidth(2);
  hist_8->SetLineWidth(2);
  hist_9->SetLineWidth(2);
  hist_10->SetLineWidth(2);
  hist_11->SetLineWidth(2);

  TObjArray m_hist_array;

  m_hist_array.Add(hist_tracker);
  m_hist_array.Add(hist_0);
  m_hist_array.Add(hist_1);
  m_hist_array.Add(hist_2);
  m_hist_array.Add(hist_3);
  m_hist_array.Add(hist_4);
  m_hist_array.Add(hist_5);
  m_hist_array.Add(hist_6);
  m_hist_array.Add(hist_7);
  m_hist_array.Add(hist_8);
  m_hist_array.Add(hist_9);
  m_hist_array.Add(hist_10);
  m_hist_array.Add(hist_11);

  PlotUtils::MnvH1D* datahist =new PlotUtils::MnvH1D("adsf", "", nbins, xmin, xmax);
  datahist->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  datahist->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));
  datahist->SetMaximum(Ymax);
  bool dataAsPoints =false;
  bool allSolidLines = true;
  bool leaveStyleAlone = true;
  mnvPlotter.DrawDataMCVariations(datahist, &m_hist_array , 1.0, "TL", dataAsPoints, allSolidLines, leaveStyleAlone, false );

  mnvPlotter.AddHistoTitle(histotitle, .028);
  mnvPlotter.WritePreliminary("TR", .01, 0, 0, false);
  std::string plotname = Form("%s",pdf_name.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");


  mnvPlotter.axis_draw_grid_x = false;
  mnvPlotter.axis_draw_grid_y = false;
  if(setLogY==true){gPad->SetLogy(0);}
  if(setLogX==true){gPad->SetLogx(0);}
  cE.Closed();

}

void DrawCVAndError_From2HIST(TH1D *hist_1_input, char *legend_1_title ,TH1D *hist_2_input,
   char *legend_2_title,  char *histotitle ,std::string xaxislabel, std::string yaxislabel,
   std::string pdf_name, bool Setgrid, bool BinWidthNorm, double Ymax , bool setLogY )
{

  TH1D *hist_1 = (TH1D *)hist_1_input->Clone("");
  TH1D *hist_2 = (TH1D *)hist_2_input->Clone("");

  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  double x1,y1,x2,y2;
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "TL", 6.5, 6., .025);
  TLegend *legend = new TLegend(x1 , y1 , x2  , y2  );
  legend->SetTextSize(.03);
  if(Setgrid==true){cE.SetGrid();}
  else if (Setgrid==false){cE.Clear();}
  if (setLogY==true){
    hist_1->SetMinimum(1.0);
    hist_2->SetMinimum(1.0);
    gPad->SetLogy(1);}
  //histHelium->GetXaxis()->SetTitleSize(0.035);
  hist_1->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist_1->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));

  hist_2->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist_2->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));

  hist_1->SetTitleOffset(1.2);
  hist_2->SetTitleOffset(1.2);
  if(Ymax != -99){
    hist_1->SetMaximum(Ymax);
    hist_2->SetMaximum(Ymax);
  }
else{
double max1 = hist_1->GetMaximum();
double max2 = hist_2->GetMaximum();

if(max1 > max2){
  hist_1->SetMaximum(max1* 1.25);
  hist_2->SetMaximum(max1* 1.25);

}
else{
  hist_1->SetMaximum(max2* 1.25);
  hist_2->SetMaximum(max2* 1.25);

}

}
  int nbins_1 = hist_1->GetNbinsX();
  int nbins_2 = hist_2->GetNbinsX();

  //if (nbins_1!=nbins_2 ) {std::cout<< "ERROR - The Number of bins aren't the same for hist in DrawCVAndError_From2HIST_withFit"<< std::endl; assert(false);}


  if(BinWidthNorm== true){
    hist_1->Scale(1.0,"width");
    hist_2->Scale(1.0,"width");
  }

  legend->AddEntry(hist_1, legend_1_title, "l");
  legend->AddEntry(hist_2, legend_2_title,"l");

  hist_1->SetLineColor(kBlue);
  hist_2->SetLineColor(kRed);
  hist_1->GetXaxis()->SetTitleSize(0.03);
  hist_1->Draw("hist");
  hist_2->Draw("hist same");



  legend->Draw("same");
  mnvPlotter.AddHistoTitle(histotitle, .028);
  mnvPlotter.WritePreliminary("TR", .03, 0, 0, false);
  std::string plotname = Form("%s",pdf_name.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");

  if (setLogY==true){gPad->SetLogy(0);}

  cE.Closed();

}
//////////////////////////////////////////////////////////////////////////////
//////
//////////////////////////////////////////////////////////////////////////////
void DrawCVAndError_From2HIST_test(
  MnvH1D *hist_1_input, char *legend_1_title,
  MnvH1D *hist_2_input, char *legend_2_title,
  char *histotitle,  std::string xaxislabel,
  std::string yaxislabel, std::string pdf_name,
  bool Setgrid, bool BinWidthNorm, double Ymax,
  double Ymin , bool setLogY )
{

  MnvH1D *hist_1 = (MnvH1D *)hist_1_input->Clone("");
  MnvH1D *hist_2 = (MnvH1D *)hist_2_input->Clone("");

  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  double x1,y1,x2,y2;
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "TL", 6.5, 6., .025);
  TLegend *legend = new TLegend(x1 , y1 , x2  , y2  );
  legend->SetTextSize(.03);
  if(Setgrid==true){cE.SetGrid();}
  else if (Setgrid==false){cE.Clear();}
  if (setLogY==true){
    hist_1->SetMinimum(1.0);
    hist_2->SetMinimum(1.0);
    gPad->SetLogy(1);}
  //histHelium->GetXaxis()->SetTitleSize(0.035);
  hist_1->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist_1->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));

  hist_2->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist_2->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));

  hist_1->SetTitleOffset(1.2);
  hist_2->SetTitleOffset(1.2);
  if(Ymax != -99){
    hist_1->SetMaximum(Ymax);
    hist_2->SetMaximum(Ymax);
    hist_1->SetMinimum(Ymin);
    hist_2->SetMinimum(Ymin);
  }
else{
double max1 = hist_1->GetMaximum();
double max2 = hist_2->GetMaximum();

if(max1 > max2){
  hist_1->SetMaximum(max1* 1.25);
  hist_2->SetMaximum(max1* 1.25);

}
else{
  hist_1->SetMaximum(max2* 1.25);
  hist_2->SetMaximum(max2* 1.25);

}

}
  int nbins_1 = hist_1->GetNbinsX();
  int nbins_2 = hist_2->GetNbinsX();

  //if (nbins_1!=nbins_2 ) {std::cout<< "ERROR - The Number of bins aren't the same for hist in DrawCVAndError_From2HIST_withFit"<< std::endl; assert(false);}


  if(BinWidthNorm== true){
    hist_1->Scale(1.0,"width");
    hist_2->Scale(1.0,"width");
  }

  legend->AddEntry(hist_1, legend_1_title, "l");
  legend->AddEntry(hist_2, legend_2_title,"l");

  hist_1->SetLineColor(kBlue);
  hist_2->SetLineColor(kRed);
  hist_1->GetXaxis()->SetTitleSize(0.03);
  hist_1->Draw("hist");
  hist_2->Draw("hist same");
  int ndf=0;
  Double_t chi_2 = mnvPlotter.Chi2DataMC(hist_1,hist_2,ndf,1.0,false,false );
  char chi_label[1024];

  double ratio = chi_2 / (double)ndf;
  legend->Draw("same");

  TLatex* text = new TLatex;
  text->SetNDC();
  text->SetTextSize(0.03);
  text->SetTextColor(kRed);
  text->DrawLatex(0.45, 0.8, Form("#chi^{2}/ndf = %.2f / %i = %.2f ", chi_2,ndf,ratio));


  mnvPlotter.AddHistoTitle(histotitle, .028);
  mnvPlotter.WritePreliminary("TR", .03, 0, 0, false);
  std::string plotname = Form("%s",pdf_name.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");

  if (setLogY==true){gPad->SetLogy(0);}

  cE.Closed();

}
//////////////////////////////////////////////////////////////////////////////
//////
//////////////////////////////////////////////////////////////////////////////
void DrawCVAndError_From_L_2HIST_RHist_test(
  MnvH1D *hist_1_input, char *legend_1_title,
  MnvH1D *hist_2_input, char *legend_2_title,
   MnvH1D *hist_3_input, char *legend_3_title,
    char *histotitle ,std::string xaxislabel,
    std::string yaxislabel,std::string yaxislabel_right,
   std::string pdf_name, bool Setgrid, bool BinWidthNorm,
    double Ymax ,double Ymin , bool setLogY, bool setLogY_right)
{

  MnvH1D *hist_1 = (MnvH1D *)hist_1_input->Clone("");
  MnvH1D *hist_2 = (MnvH1D *)hist_2_input->Clone("");
  MnvH1D *hist_3 = (MnvH1D *)hist_3_input->Clone("");

  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  double x1,y1,x2,y2;
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "TL", 6.5, 6., .025);
  TLegend *legend = new TLegend(x1 , y1 , x2 +.1  , y2  );
  legend->SetBorderSize(0);
  legend->SetTextSize(.03);
  if(Setgrid==true){cE.SetGrid();}
  else if (Setgrid==false){cE.Clear();}
  if (setLogY==true){
    hist_1->SetMinimum(1.0);
    hist_2->SetMinimum(1.0);
    gPad->SetLogy(1);}
  //histHelium->GetXaxis()->SetTitleSize(0.035);
  hist_1->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist_1->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));

  hist_2->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist_2->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));

  hist_1->SetTitleOffset(1.2);
  hist_2->SetTitleOffset(1.2);
  if(Ymax != -99){
    hist_1->SetMaximum(Ymax);
    hist_2->SetMaximum(Ymax);
    hist_1->SetMinimum(Ymin);
    hist_2->SetMinimum(Ymin);
  }
else{
double max1 = hist_1->GetMaximum();
double max2 = hist_2->GetMaximum();

if(max1 > max2){
  hist_1->SetMaximum(max1* 1.25);
  hist_2->SetMaximum(max1* 1.25);

}
else{
  hist_1->SetMaximum(max2* 1.25);
  hist_2->SetMaximum(max2* 1.25);

}

}
  int nbins_1 = hist_1->GetNbinsX();
  int nbins_2 = hist_2->GetNbinsX();

  //if (nbins_1!=nbins_2 ) {std::cout<< "ERROR - The Number of bins aren't the same for hist in DrawCVAndError_From2HIST_withFit"<< std::endl; assert(false);}


  if(BinWidthNorm== true){
    hist_1->Scale(1.0,"width");
    hist_2->Scale(1.0,"width");
    hist_3->Scale(1.0,"width");
  }

  legend->AddEntry(hist_1, legend_1_title, "l");
  legend->AddEntry(hist_2, legend_2_title,"l");
  legend->AddEntry(hist_3, legend_3_title, "l");

  hist_1->SetLineColor(kBlue);
  hist_2->SetLineColor(kRed);
  hist_1->GetXaxis()->SetTitleSize(0.04);
  hist_1->GetXaxis()->SetTitleOffset(1.2);
  hist_1->Draw("hist");
  hist_2->Draw("hist same");

  legend->SetTextSize(.03);
  legend->SetFillColor(0);
  legend->Draw("same");
  mnvPlotter.AddHistoTitle(histotitle, .028);
  mnvPlotter.WritePreliminary("TR", .03, 0, 0, false);
  std::string plotname = Form("%s",pdf_name.c_str());
  cE.Update();



  Float_t rightmax = 1.1*hist_3->GetMaximum();
  Float_t scale = gPad->GetUymax()/rightmax;
/*
  TPad *pad = (TPad*)c1->GetPad(1);
  pad->cd();
  TGaxis *axis = new TGaxis(pad->GetUxmax(), pad->GetUymin(),
                            pad->GetUxmax(), pad->GetUymax(), .01, hist_3->GetMaximum(), 510, "+L");
*/

    if(setLogY_right==true){
      hist_3->SetMinimum(.01);
      gPad->SetLogy(1);}

  hist_3->SetLineColor(6);
  hist_3->Scale(scale);
  hist_3->SetLineStyle(2);
  //hist_3->GetXaxis()->SetRange(0,20);
  hist_3->Draw("hist same");
  hist_3->SetLineWidth(3);
  TGaxis *axis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),
  gPad->GetUxmax(), gPad->GetUymax(),0,rightmax,510,"+L");
  axis->SetLineColor(6);
  axis->SetTextColor(6);

  axis->SetTitle(Form("%s",yaxislabel_right.c_str()));
  axis->SetTitleOffset(1.5);
  axis->SetTitleSize(0.04);
  axis->SetLabelSize(0.03);
  axis->Draw();





  mnvPlotter.MultiPrint(&cE, plotname, "pdf");







  if (setLogY==true){gPad->SetLogy(0);}

  cE.Closed();

}
//////////////////////////////////////////////////////////////////////////////
//////
//////////////////////////////////////////////////////////////////////////////
void DrawCVAndError_From_L_2HIST_RHist_test2(
  MnvH1D *hist_1_input, char *legend_1_title,
  MnvH1D *hist_2_input, char *legend_2_title,
  MnvH1D *hist_3_input,
  char *legend_3_title, char *histotitle,
  std::string xaxislabel, std::string yaxislabel,
  std::string yaxislabel_right,
  std::string pdf_name, bool Setgrid, bool BinWidthNorm,
  double Ymax ,double Ymin , bool setLogY, bool setLogY_right )
{

  MnvH1D *hist_1 = (MnvH1D *)hist_1_input->Clone("");
  MnvH1D *hist_2 = (MnvH1D *)hist_2_input->Clone("");
  MnvH1D *hist_3 = (MnvH1D *)hist_3_input->Clone("");

  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  //TCanvas cE ("c1","c1");
  TCanvas *cE = new TCanvas("c1", "My Canvas", 800, 600);


  double x1,y1,x2,y2;
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "TL", 6.5, 6., .025);
  TLegend *legend = new TLegend(x1 , y1 , x2 +.1  , y2  );
  legend->SetBorderSize(0);
  legend->SetTextSize(.03);
  if(Setgrid==true){cE->SetGrid();}
  else if (Setgrid==false){cE->Clear();}
  if (setLogY==true){
    hist_1->SetMinimum(1.0);
    hist_2->SetMinimum(1.0);
    gPad->SetLogy(1);}
  //histHelium->GetXaxis()->SetTitleSize(0.035);
  hist_3->SetMinimum(1.0);
  hist_3->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist_3->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));

  hist_2->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist_2->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));

  hist_1->SetTitleOffset(1.2);
  hist_2->SetTitleOffset(1.2);
  if(Ymax != -99){
    hist_1->SetMaximum(Ymax);
    hist_2->SetMaximum(Ymax);
    hist_1->SetMinimum(Ymin);
    hist_2->SetMinimum(Ymin);
  }
else{
double max1 = hist_1->GetMaximum();
double max2 = hist_2->GetMaximum();

if(max1 > max2){
  hist_1->SetMaximum(max1* 1.25);
  hist_2->SetMaximum(max1* 1.25);

}
else{
  hist_1->SetMaximum(max2* 1.25);
  hist_2->SetMaximum(max2* 1.25);

}

}
  int nbins_1 = hist_1->GetNbinsX();
  int nbins_2 = hist_2->GetNbinsX();

  //if (nbins_1!=nbins_2 ) {std::cout<< "ERROR - The Number of bins aren't the same for hist in DrawCVAndError_From2HIST_withFit"<< std::endl; assert(false);}


  if(BinWidthNorm== true){
    hist_1->Scale(1.0,"width");
    hist_2->Scale(1.0,"width");
    hist_3->Scale(1.0,"width");
  }

  //legend->AddEntry(hist_1, legend_1_title, "l");
  //legend->AddEntry(hist_2, legend_2_title,"l");
  legend->AddEntry(hist_3, legend_3_title, "l");

  cE->cd();
  hist_3->SetLineWidth(3);
  hist_3->SetLineColor(6);
  hist_3->SetLineStyle(2);
  hist_3->Draw("hist");
  //hist_2->Draw("hist same");


  legend->SetTextSize(.03);
  legend->SetFillColor(0);
  //legend->Draw("same");
  mnvPlotter.AddHistoTitle(histotitle, .028);
  mnvPlotter.WritePreliminary("TR", .03, 0, 0, false);
  std::string plotname = Form("%s",pdf_name.c_str());
  //cE->Update();


  //Float_t rightmax = 1.1*Ymax;
  //Float_t scale = gPad->GetUymax()/rightmax;

  //TPad *pad2 = new TPad("pad2","pad2",0,0,1,1);
  //pad2->SetLeftMargin(0.1);
  //pad2->SetRightMargin(0.1);
  //pad2->SetFillColor(0);
  //pad2->SetFillStyle(0);
  //pad2->Draw();
  //pad2->cd();



  //hist_3->GetXaxis()->SetRange(0,20);

  //hist_1->Scale(scale);
  //hist_2->Scale(scale);
  gPad->SetLogy();



//
//  cE->Update();
//  TGaxis *axis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),
//  gPad->GetUxmax(), gPad->GetUymax(),0,hist_3->GetMaximum(),510,"+L");

//  pad2->SetLogy();
  //std::cout << "pad address: " << pad2 << std::endl;
  //pad2->cd();




//  axis->SetLineColor(6);
//  axis->SetTextColor(6);
//  axis->SetMoreLogLabels(kTRUE);
//  axis->SetTitle(Form("%s",yaxislabel_right.c_str()));
//  axis->SetTitleOffset(1.5);
//  axis->SetTitleSize(0.04);
//  axis->SetLabelSize(0.03);
//  axis->Draw();

  //pad1->cd();




  mnvPlotter.MultiPrint(cE, plotname, "pdf");







  if (setLogY==true){gPad->SetLogy(0);}

  cE->Closed();

}


void DrawCVAndError_From_R_2HIST_LHist_test(MnvH1D *hist_1_input, char *legend_1_title ,MnvH1D *hist_2_input,
   char *legend_2_title, MnvH1D *hist_3_input,
      char *legend_3_title, char *histotitle ,std::string xaxislabel, std::string yaxislabel,std::string yaxislabel_right,
   std::string pdf_name, bool Setgrid, bool BinWidthNorm, double Ymax ,double Ymin , bool setLogY, bool setLogY_right )
{

  MnvH1D *hist_1 = (MnvH1D *)hist_1_input->Clone("");
  MnvH1D *hist_2 = (MnvH1D *)hist_2_input->Clone("");
  MnvH1D *hist_3 = (MnvH1D *)hist_3_input->Clone("");

  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  double x1,y1,x2,y2;
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "TL", 6.5, 6., .025);
  TLegend *legend = new TLegend(x1 , y1 , x2 +.1  , y2  );
  legend->SetBorderSize(0);
  legend->SetTextSize(.03);
  if(Setgrid==true){cE.SetGrid();}
  else if (Setgrid==false){cE.Clear();}
  if (setLogY==true){
    hist_1->SetMinimum(1.0);
    hist_2->SetMinimum(1.0);
    gPad->SetLogy(1);}

  //histHelium->GetXaxis()->SetTitleSize(0.035);
  hist_3->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist_3->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));
  hist_3->SetTitleOffset(1.2);

  if(Ymax != -99){

    hist_3->SetMaximum(Ymax);
    hist_3->SetMinimum(Ymin);
  }
else{
double max1 = hist_3->GetMaximum();
hist_3->SetMaximum(max1*1.2);

}


  //if (nbins_1!=nbins_2 ) {std::cout<< "ERROR - The Number of bins aren't the same for hist in DrawCVAndError_From2HIST_withFit"<< std::endl; assert(false);}


  if(BinWidthNorm== true){
    hist_1->Scale(1.0,"width");
    hist_2->Scale(1.0,"width");
    hist_3->Scale(1.0,"width");
  }

  legend->AddEntry(hist_1, legend_1_title, "l");
  legend->AddEntry(hist_2, legend_2_title,"l");
  legend->AddEntry(hist_3, legend_3_title, "l");

  hist_3->SetLineColor(6);
  hist_3->SetLineStyle(2);
  //hist_1->Draw("hist");
  hist_3->Draw("hist");
  hist_3->SetLineWidth(3);

  legend->SetTextSize(.03);
  legend->SetFillColor(0);
  legend->Draw("same");
  mnvPlotter.AddHistoTitle(histotitle, .028);
  mnvPlotter.WritePreliminary("TR", .03, 0, 0, false);
  std::string plotname = Form("%s",pdf_name.c_str());
  cE.Update();

  if(setLogY_right==true){
    //hist_3->GetXaxis()->SetRange(0,20);
    hist_3->SetMinimum(.01);
    gPad->SetLogy(1);}

  Float_t rightmax = 1.1*hist_2->GetMaximum();
  Float_t scale = gPad->GetUymax()/rightmax;
  //hist_2->Scale(scale);
  //hist_1->Scale(scale);
  hist_1->SetLineColor(kBlue);
  hist_2->SetLineColor(kRed);

  hist_1->Draw("hist same");
  hist_2->Draw("hist same");

  TGaxis *axis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),
  gPad->GetUxmax(), gPad->GetUymax(),0,rightmax,510,"+L");
  axis->SetLineColor(6);
  axis->SetTextColor(6);

  axis->SetTitle(Form("%s",yaxislabel_right.c_str()));
  axis->SetTitleOffset(1.5);
  axis->SetTitleSize(0.04);
  axis->SetLabelSize(0.03);
  axis->Draw();





  mnvPlotter.MultiPrint(&cE, plotname, "pdf");







  if (setLogY==true){gPad->SetLogy(0);}

  cE.Closed();

}
//////////////////////////////////////////////////////////////////////////////
//////
//////////////////////////////////////////////////////////////////////////////

void DrawCVAndError_From5HIST(
  MnvH1D *hist_Data_input, char *legend_Data_title,
  TH1D *hist_1_input, char *legend_1_title,
  TH1D *hist_2_input, char *legend_2_title,
  TH1D *hist_3_input, char *legend_3_title,
  TH1D *hist_4_input, char *legend_4_title,
  TH1D *hist_5_input, char *legend_5_title,
  std::vector<int> fillColors,
  char *histotitle ,std::string xaxislabel,
  std::string yaxislabel,
   std::string pdf_name, bool Setgrid,
    bool BinWidthNorm, double Ymax , bool setLogY )
{

  MnvH1D *hist_Data = (MnvH1D *)hist_Data_input->Clone(uniq());
  TH1D *hist_1_clone = (TH1D *)hist_1_input->Clone(uniq());
  TH1D *hist_2_clone = (TH1D *)hist_2_input->Clone(uniq());
  TH1D *hist_3_clone = (TH1D *)hist_3_input->Clone(uniq());
  TH1D *hist_4_clone = (TH1D *)hist_4_input->Clone(uniq());
  TH1D *hist_5_clone = (TH1D *)hist_5_input->Clone(uniq());

  MnvH1D hist_1_new = MnvH1D( *hist_1_clone, false);
  MnvH1D hist_2_new = MnvH1D( *hist_2_clone, false);
  MnvH1D hist_3_new = MnvH1D( *hist_3_clone, false);
  MnvH1D hist_4_new = MnvH1D( *hist_4_clone, false);
  MnvH1D hist_5_new = MnvH1D( *hist_5_clone, false);
  MnvH1D *hist_1 = &hist_1_new;
  MnvH1D *hist_2 = &hist_2_new;
  MnvH1D *hist_3 = &hist_3_new;
  MnvH1D *hist_4 = &hist_4_new;
  MnvH1D *hist_5 = &hist_5_new;

  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  double x1,y1,x2,y2;
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "TR", 6.5, 6., .025);
  TLegend *legend = new TLegend(x1 - .2 , y1 , x2-.2  , y2  );
  legend->SetTextSize(.03);
  if(Setgrid==true){cE.SetGrid();}
  else if (Setgrid==false){cE.Clear();}
  if (setLogY==true){
    hist_1->SetMinimum(1.0);
    hist_2->SetMinimum(1.0);
    gPad->SetLogy(1);}
  //histHelium->GetXaxis()->SetTitleSize(0.035);
  hist_1->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist_1->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));

  if(BinWidthNorm== true){
     hist_Data->Scale(1.0,"width");
    hist_1->Scale(1.0,"width");
    hist_2->Scale(1.0,"width");
    hist_3->Scale(1.0,"width");
    hist_4->Scale(1.0,"width");
    hist_5->Scale(1.0,"width");
  }

  if(Ymax != -99){
    hist_1->SetMaximum(Ymax);
    hist_2->SetMaximum(Ymax);
  }
  else{
    //double max1 = hist_1->GetMaximum();
    double max = hist_Data->GetMaximum();
    double max1 = hist_1_new.GetMaximum();
    double max2 = hist_2_new.GetMaximum();
    double max3 = hist_3_new.GetMaximum();
    double max4 = hist_4_new.GetMaximum();
    double max5 = hist_5_new.GetMaximum();

    std::vector<double> input{max, max1, max2, max3, max4, max5};
    double MAX = *max_element(input.begin(), input.end());
    hist_1->SetMaximum(MAX* 1.35);

    if(max1 > max2){
      hist_1->SetMaximum(max1* 1.45);
      hist_2->SetMaximum(max1* 1.45);

    }
    else{
      hist_2->SetMaximum(max2* 1.45);
    }

  }
  int nbins_1 = hist_1->GetNbinsX();
  int nbins_2 = hist_2->GetNbinsX();

  if (nbins_1!=nbins_2 ) {std::cout<< "ERROR - The Number of bins aren't the same for hist in DrawCVAndError_From2HIST_withFit"<< std::endl; assert(false);}




double area = hist_1->Integral();
double area2 = hist_2->Integral();
double area3 = hist_3->Integral();
double area4 = hist_4->Integral();
double area5 = hist_5->Integral();



//hist_2->Scale(area/ area2);
//hist_3->Scale(area/ area3);
//hist_4->Scale(area/ area4);
//hist_5->Scale(area/ area5);


  legend->AddEntry(hist_Data, legend_Data_title, "lpe");
  legend->AddEntry(hist_1, legend_1_title, "l");
  legend->AddEntry(hist_2, legend_2_title, "l");
  legend->AddEntry(hist_3, legend_3_title, "l");
  legend->AddEntry(hist_4, legend_4_title, "l");
  legend->AddEntry(hist_5, legend_5_title, "l");
  legend->SetFillStyle(0);
  legend->SetBorderSize(0);
  legend->SetTextSize(0.028);
  legend->SetNColumns(1);

  hist_1->SetLineColor(fillColors.at(0));
  hist_2->SetLineColor(fillColors.at(1));
  hist_3->SetLineColor(fillColors.at(2));
  hist_4->SetLineColor(fillColors.at(3));
  hist_5->SetLineColor(fillColors.at(4));


hist_1->SetLineWidth(3);
hist_2->SetLineWidth(3);
hist_3->SetLineWidth(3);
hist_4->SetLineWidth(3);
hist_5->SetLineWidth(3);



 hist_2->SetLineStyle(2);
 hist_3->SetLineStyle(2);
 hist_4->SetLineStyle(2);
 hist_5->SetLineStyle(2);


  hist_1->GetXaxis()->SetTitleSize(0.03);
  hist_1->Draw("hist");
  hist_2->Draw("hist same");
  hist_3->Draw("hist same");
  hist_4->Draw("hist same");
  hist_5->Draw("hist same");

  hist_Data->SetMarkerStyle(mnvPlotter.data_marker);
  hist_Data->SetMarkerSize(mnvPlotter.data_marker_size);
  hist_Data->SetMarkerColor(mnvPlotter.data_color);
  hist_Data->SetLineWidth(mnvPlotter.data_line_width);
  hist_Data->SetLineStyle(mnvPlotter.data_line_style);
  hist_Data->SetLineColor(mnvPlotter.data_color);
  hist_Data->DrawCopy("SAME E1 X0");
  legend->Draw("same");
  mnvPlotter.AddHistoTitle(histotitle, .028);
  mnvPlotter.WritePreliminary("TL", .03, 0, 0, false);
  std::string plotname = Form("%s",pdf_name.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");

  if (setLogY==true){gPad->SetLogy(0);}
  cE.Closed();

}
//////////////////////////////////////////////////////////////////////////////
//////
//////////////////////////////////////////////////////////////////////////////
void DrawCVAndError_From2HIST_ndflines(TH1D *hist_1,
   char *legend_1_title ,TH1D *hist_2,
   char *legend_2_title,  char *histotitle,
   std::string xaxislabel, std::string yaxislabel,
   std::string pdf_name, bool Setgrid,
    bool BinWidthNorm, double Ymax , bool setLogY,  double  ndf )
{


  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  double x1,y1,x2,y2;
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "TL", 6.5, 6., .025);
  TLegend *legend = new TLegend(x1 , y1 , x2  , y2  );
  legend->SetTextSize(.03);
  if(Setgrid==true){cE.SetGrid();}
  else if (Setgrid==false){cE.Clear();}
  if (setLogY==true){
    hist_1->SetMinimum(1.0);
    hist_2->SetMinimum(1.0);
    gPad->SetLogy(1);}
  //histHelium->GetXaxis()->SetTitleSize(0.035);
  hist_1->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist_1->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));

  hist_2->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist_2->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));

  hist_1->SetTitleOffset(1.2);
  hist_2->SetTitleOffset(1.2);
  if(Ymax != -99){
    hist_1->SetMaximum(Ymax);
    hist_2->SetMaximum(Ymax);
  }
else{
double max1 = hist_1->GetMaximum();
double max2 = hist_2->GetMaximum();

if(max1 > max2){
  hist_1->SetMaximum(max1* 1.25);
  hist_2->SetMaximum(max1* 1.25);

}
else{
  hist_1->SetMaximum(max2* 1.25);
  hist_2->SetMaximum(max2* 1.25);

}

}
  int nbins_1 = hist_1->GetNbinsX();
  int nbins_2 = hist_2->GetNbinsX();

  if (nbins_1!=nbins_2 ) {std::cout<< "ERROR - The Number of bins aren't the same for hist in DrawCVAndError_From2HIST_withFit"<< std::endl; assert(false);}


  if(BinWidthNorm== true){
    hist_1->Scale(1,"width");
    hist_2->Scale(1,"width");
  }
  legend->AddEntry(hist_1, legend_1_title, "l");
  legend->AddEntry(hist_2, legend_2_title,"l");

  hist_1->SetLineColor(kBlue);
  hist_2->SetLineColor(kRed);
  hist_1->GetXaxis()->SetTitleSize(0.03);
  hist_1->Draw("hist");
  hist_2->Draw("hist same");

    double xmax = hist_2->GetBinCenter(hist_2->GetNbinsX());

    TLine l;  TLine l2;   TLine l3;
    l.SetLineWidth(4);
    l.SetLineStyle(2);
    l.SetLineColor(kBlack);
    l.DrawLine(1,ndf,xmax, ndf);
    l2.DrawLine(1,2*ndf,xmax, 2*ndf);



  legend->Draw("same");
  mnvPlotter.AddHistoTitle(histotitle, .028);
  mnvPlotter.WritePreliminary("TR", .03, 0, 0, false);
  std::string plotname = Form("%s",pdf_name.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");

  if (setLogY==true){gPad->SetLogy(0);}
  cE.Closed();

}
//////////////////////////////////////////////////////////////////////////////
//////
//////////////////////////////////////////////////////////////////////////////
void DrawCVAndError_FromHIST(MnvH1D *hist,
  char *histotitle, std::string xaxislabel,
  std::string yaxislabel,
  std::string pdf_name, bool Setgrid, bool LogX)
{
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  if(Setgrid==true){cE.SetGrid();}
  else if (Setgrid==false){cE.Clear();}

  hist->GetXaxis()->SetTitleSize(0.035);
  hist->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));
  hist->GetYaxis()->CenterTitle();

  hist->SetTitle(histotitle);
  PlotUtils::MnvH1D* datahist =new PlotUtils::MnvH1D("adsf", "", nbins, xmin, xmax);
  bool statPlusSys           = true;
  int mcScale                = 1.;
  bool useHistTitles         = false;

  //hist->Scale(1,"width");
  if (LogX==true){gPad->SetLogx(1);}
  else if (LogX==false){gPad->SetLogy(1);}
  mnvPlotter.DrawDataMCWithErrorBand(datahist, hist, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);
  //mnvPlotter.DrawMCWithErrorBand(hist); //I think that this call only shows stat errors.
  mnvPlotter.AddHistoTitle(histotitle);
  mnvPlotter.WritePreliminary("TR", .03, 0, 0, false);
  std::string plotname = Form("%s",pdf_name.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");

  //PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);

  mnvPlotter.legend_n_columns = 2;
  // PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);
  PlotErrorSummaryNew(hist, plotname, histotitle, xaxislabel.c_str(), &cE, &mnvPlotter,true,false);
  mnvPlotter.legend_n_columns = 1;


  if (LogX==true){gPad->SetLogx(0);}
  else if (LogX==false){gPad->SetLogy(0);}
}

//////////////////////////////////////////////////////////////////////////////
//////
//////////////////////////////////////////////////////////////////////////////

void DrawDATAWITHCV_AndError_FromTFile_Single_playlist(
  TFile *inputFile, TFile *inputFile_data,
  Pot_MapList POT_MC,Pot_MapList POT_DATA,
  ME_helium_Playlists playlist_name, char *histoName,
  char *histoName_data, char *histotitle,
  std::string xaxislabel, std::string label,
   bool MakeBinwidth_Norm)
{

  MnvH1D *hist = (MnvH1D*)inputFile -> Get(histoName);
  std::string yaxislabel = "Nevents";
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCNuPionIncStyle);
  TCanvas cE ("c1","c1");
  hist->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));
  hist->SetTitle(histotitle);
  PlotUtils::MnvH1D* datahist = (MnvH1D*)inputFile_data -> Get(histoName_data);

  if(MakeBinwidth_Norm==true)
  {
    datahist->Scale(1.0,"width");
    hist->Scale(1.0,"width");
  }

  bool statPlusSys           = true;
  double mcScale                = POT_DATA[playlist_name]/POT_MC[playlist_name];
  bool useHistTitles         = false;

  mnvPlotter.DrawDataMCWithErrorBand(datahist, hist, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);
  mnvPlotter.AddHistoTitle(histotitle);

  //mnvPlotter.DrawMCWithErrorBand(hist); //I think that this call only shows stat errors.
  std::string plotname = Form("%s",label.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");
}
//////////////////////////////////////////////////////////////////////////////
//////
//////////////////////////////////////////////////////////////////////////////

void DrawCVAndError_FromHIST_withVLine(
  MnvH1D *hist, char *histotitle,
  std::string xaxislabel,std::string yaxislabel,
  std::string pdf_name, bool Setgrid,
  bool LogX, bool LogY, double xAxis_Vline,
  const std::string &arrow_direction, double arrow_length)
  {
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  if(Setgrid==true){cE.SetGrid();}
  else if (Setgrid==false){cE.Clear();}

  hist->GetXaxis()->SetTitleSize(0.035);
  hist->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));
  hist->GetYaxis()->CenterTitle();

  TLine *Vert_line = new TLine(xAxis_Vline,hist->GetMinimum(),xAxis_Vline, 1.25*hist->GetMaximum());

  hist->SetTitle(histotitle);
  PlotUtils::MnvH1D* datahist =new PlotUtils::MnvH1D("adsf", "", nbins, xmin, xmax);
  bool statPlusSys           = true;
  int mcScale                = 1.;
  bool useHistTitles         = false;

  //hist->Scale(1,"width");
  if (LogX==true){gPad->SetLogx(1);}
  if (LogY==true){gPad->SetLogy(1);}
  mnvPlotter.DrawDataMCWithErrorBand(datahist, hist, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);
  //mnvPlotter.DrawMCWithErrorBand(hist); //I think that this call only shows stat errors.
  //Vert_line->SetLineColor(kBlue);
  //Vert_line->SetLineWidth(3);
  //Vert_line->Draw();
  mnvPlotter.AddCutArrow(xAxis_Vline, 0.0, 1.25*hist->GetMaximum(), arrow_length, arrow_direction) ;
  mnvPlotter.AddHistoTitle(histotitle);
  mnvPlotter.WritePreliminary("TR", .03, 0, 0, false);
  std::string plotname = Form("%s",pdf_name.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");

  //PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);

  mnvPlotter.legend_n_columns = 2;
  // PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);
  PlotErrorSummaryNew(hist, plotname, histotitle, xaxislabel.c_str(), &cE, &mnvPlotter,true,false);
  mnvPlotter.legend_n_columns = 1;


  if (LogX==true){gPad->SetLogx(0);}
  if (LogY==true){gPad->SetLogy(0);}


}

//////////////////////////////////////////////////////////////////////////////
//////
//////////////////////////////////////////////////////////////////////////////

void DrawDATAWITHCV_AndError_FromTFile_Single_playlist_Full_EMPTY(
  TFile *inputFileFULL,TFile *inputFileEMPTY,
  TFile *inputFile_Fulldata,TFile *inputFile_Emptydata,
  Pot_MapList POT_MC,Pot_MapList POT_DATA,
  ME_helium_Playlists playlist_name_FULL,
  ME_helium_Playlists playlist_name_EMPTY,
  char *histoName,char *histoName_data, char *histotitle,
  std::string xaxislabel, std::string label, bool MakeBinwidth_Norm)
{

  double mcScale                = POT_DATA[playlist_name_FULL]/POT_MC[playlist_name_FULL];
  double mcScaleEMPTYtoFULL     = POT_MC[playlist_name_FULL]/POT_MC[playlist_name_EMPTY];
  double dataScaleEMPTYtoFULL   = POT_DATA[playlist_name_FULL]/POT_DATA[playlist_name_EMPTY];

  PlotUtils::MnvH1D* hist_FULL  = (MnvH1D*)inputFileFULL -> Get(histoName);
  PlotUtils::MnvH1D* hist_EMPTY = (MnvH1D*)inputFileEMPTY -> Get(histoName);
  PlotUtils::MnvH1D* datahistFULL   = (MnvH1D*)inputFile_Fulldata -> Get(histoName_data);
  PlotUtils::MnvH1D* datahistEMPTY   = (MnvH1D*)inputFile_Emptydata -> Get(histoName_data);

  ////////////////////////////////////////////
  //FULL - EMPTY prscription
  ///////////////////////////////////////////
  hist_EMPTY->Scale(mcScaleEMPTYtoFULL);
  hist_FULL->Add(hist_EMPTY,-1);
  datahistEMPTY->Scale(dataScaleEMPTYtoFULL);
  datahistFULL->Add(datahistEMPTY,-1);
  ////////////////////////////////////////////


  std::string yaxislabel = "Nevents";
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCNuPionIncStyle);
  TCanvas cE ("c1","c1");
  hist_FULL->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist_FULL->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));
  hist_FULL->SetTitle(histotitle);


  if(MakeBinwidth_Norm==true)
  {
    datahistFULL->Scale(1.0,"width");
    hist_FULL->Scale(1.0,"width");
  }

  bool statPlusSys           = true;

  bool useHistTitles         = false;
  mnvPlotter.DrawDataMCWithErrorBand(datahistFULL, hist_FULL, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);
  mnvPlotter.AddHistoTitle(histotitle);
  mnvPlotter.WritePreliminary("TL", .035, 0, 0, false);
  //mnvPlotter.DrawMCWithErrorBand(hist); //I think that this call only shows stat errors.
  std::string plotname = Form("%s",label.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");

  PlotErrorSummary(hist_FULL, plotname, histotitle, xaxislabel.c_str(), &cE);
  //PlotErrorSummaryNew(hist_FULL, plotname, histotitle, xaxislabel.c_str(), &cE, &mnvPlotter);
  cE.Clear();
}
//////////////////////////////////////////////////////////////////////////////
//////
//////////////////////////////////////////////////////////////////////////////

void DrawCVAndError_FromTFile(TFile *inputFile_MCFULL,
  TFile *inputFile_MCEMPTY,  char *histoName_MC,
  TFile *inputFile_DATAFULL,TFile *inputFile_DATAEMPTY,
  char *histoName_Data,  Pot_MapStatusList POT_MC,
  Pot_MapStatusList POT_DATA, char *histotitle,
  std::string xaxislabel, std::string label, bool DoBinwidthNorm,
  bool doSmallerrorgrounps, std::string units)
{    //helium_Status kEMPTY, kFULL;
    //PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCompactStyle);
    PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCNuPionIncStyle);
    TCanvas cE ("c1","c1");
    std::cout<<"trying MC HisName = "<< histoName_MC<<std::endl;
    std::cout<<"trying data HisName = "<< histoName_Data<<std::endl;
    bool isfull= true;
    bool isempty = false;
    double x1, x2, y1, y2;
    double scale_to_FULLData[4] = {POT_DATA[kFULL]/POT_MC[kFULL],  POT_DATA[kFULL]/POT_MC[kEMPTY]  , 1.0 , POT_DATA[kFULL]/POT_DATA[kEMPTY]  };
    MnvH1D *hist_a;
    MnvH1D *hist_b;
    MnvH1D *hist_ap1;
    MnvH1D *hist_bp1;

for (int fullOrEmpty = 0; fullOrEmpty < 3; fullOrEmpty ++) {

  if(fullOrEmpty==0){
    hist_a = Get1DHist(*inputFile_MCFULL, histoName_MC, isfull);
    hist_b = Get1DHist(*inputFile_DATAFULL, histoName_Data, isfull);
    //hist_a = (MnvH1D*)inputFile_MCFULL -> Get(histoName_MC);

    //hist_b = (MnvH1D*)inputFile_DATAFULL -> Get(histoName_Data);

    hist_a->Scale(scale_to_FULLData[0]);

    if(DoBinwidthNorm==true){
      hist_a->Scale(1.0,"width");
      hist_b->Scale(1.0,"width");
    }
  }

  else if (fullOrEmpty==1)
  {
    //hist_a = (MnvH1D*)inputFile_MCEMPTY -> Get(histoName_MC);
    //hist_b = (MnvH1D*)inputFile_DATAEMPTY -> Get(histoName_Data);

    hist_a = Get1DHist(*inputFile_MCEMPTY, histoName_MC, isempty);
    hist_b = Get1DHist(*inputFile_DATAEMPTY, histoName_Data, isempty);

    hist_a->Scale(scale_to_FULLData[1]);
    hist_b->Scale(scale_to_FULLData[3]);

    if(DoBinwidthNorm==true){
      hist_a->Scale(1.0,"width");
      hist_b->Scale(1.0,"width");
    }
  }

  else if (fullOrEmpty==2){
    hist_a = Get1DHist(*inputFile_MCFULL, histoName_MC, isfull);
    hist_b = Get1DHist(*inputFile_DATAFULL, histoName_Data, isfull);
    hist_ap1 = Get1DHist(*inputFile_MCEMPTY, histoName_MC, isempty);
    hist_bp1 = Get1DHist(*inputFile_DATAEMPTY, histoName_Data, isempty);

    //  hist_a = (MnvH1D*)inputFile_MCFULL -> Get(histoName_MC);
    //  hist_ap1 = (MnvH1D*)inputFile_MCEMPTY -> Get(histoName_MC);
    //  hist_b = (MnvH1D*)inputFile_DATAFULL -> Get(histoName_Data);
    //  hist_bp1 = (MnvH1D*)inputFile_DATAEMPTY -> Get(histoName_Data);


    hist_a->Scale(scale_to_FULLData[0]); // Full MC
    //hist_b->Scale(scale_to_FULLData[2]); // FUll Data // dont really need to scale this
    hist_ap1->Scale(scale_to_FULLData[1]); //Empty MC
    hist_bp1->Scale(scale_to_FULLData[3]);  // Empty Data

    hist_a -> Add(hist_ap1, -1); // now both full and empty MC are scaled to the appropriate data size
    hist_b -> Add(hist_bp1, -1); // data doesn't need to be scaled


    if(DoBinwidthNorm==true){
      hist_a->Scale(1.0,"width");
      hist_b->Scale(1.0,"width");
      hist_ap1->Scale(1.0,"width");
      hist_bp1->Scale(1.0,"width");
    }
  } // end of F - E

  char emptyFull[1024];
  if (fullOrEmpty == 1) {sprintf(emptyFull, " (Empty) ");}
  else  if (fullOrEmpty == 0) {sprintf(emptyFull, " (Full) ");}
  else  if (fullOrEmpty == 2) {sprintf(emptyFull, " (Full - Empty) ");}


  //plot->DecodeLegendPosition(x1, y1, x2, y2, "R", 2, 2, .03);
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", .5, 10, .025);
  //TLegend *legend = new TLegend(x1 - .05, y1 + .1, x2 + .05, y2 + .1);
  TLegend *legend = new TLegend(x1 - .02, y1+.31 , x2 +.06 , y2 + .42  );
  legend->SetNColumns(1);
  legend->SetTextSize(.03);
  legend->SetFillColor(0);

  char ytitle[100];
  //int units_n = ;
  char units_char[units.length()+1];
  strcpy( units_char,units.c_str());

  double binwidth_title = hist_a -> GetBinWidth(3);
  sprintf(ytitle, "Number of Events / %.2f %s", binwidth_title, units_char); //
  //hist_a->SetFillColor(1);
  hist_a->SetLineWidth(3);
  hist_a->SetLineColor(2);
  hist_a->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  hist_a->GetYaxis()->SetTitle(ytitle);
  hist_a->GetXaxis()->CenterTitle();
  hist_a->GetYaxis()->CenterTitle();
  hist_a->GetYaxis()->SetTitleSize(0.038);
  hist_a->GetXaxis()->SetTitleSize(0.038);
  hist_a->SetTitle(histotitle);
  legend->Clear();
  legend->AddEntry(hist_a, "MC Simulation", "fl");
  legend->AddEntry(hist_b, "Data","lep");


  bool statPlusSys           = true;
  bool useHistTitles         = false;

  int ndf=0;
  Double_t chi_2 = mnvPlotter.Chi2DataMC(hist_b,hist_a,ndf,1.0,false,false );
  //Double_t chi_2 = hist_a ->Chi2Test(hist_b, "CHI2/NDF",0 );
  ndf = hist_a->GetNbinsX();
  //mnvPlotter.AddChi2Label	(hist_b,  hist_a);

  mnvPlotter.DrawDataMCWithErrorBand(hist_b, hist_a, 1.0, "N", useHistTitles, NULL, NULL, false, statPlusSys);

  //Double_t mcscale =1.0;

  char chi_label[1024];

  sprintf(chi_label, "#chi^{2}/ndf = %.2f / %i", chi_2,ndf);
  legend -> AddEntry((TObject*)0, chi_label, "");
  legend -> Draw();
  //mnvPlotter.AddPlotLabel (chi_label, const double x, const double y);
  char total_title[1024];
  sprintf(total_title, "%s%s%s", histotitle, emptyFull," (POT Norm) ");
  mnvPlotter.AddHistoTitle(total_title, .04);
  mnvPlotter.WritePreliminary("TL", .035, 0, 0, false);
  std::string plotname = Form("%s",label.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");
  //mnvPlotter.error_summary_group_map = ::errorGroups;
  mnvPlotter.legend_n_columns = 2;
  PlotErrorSummaryNew(hist_a, plotname, total_title, xaxislabel.c_str(), &cE,&mnvPlotter);
  mnvPlotter.legend_n_columns = 1;
  if (fullOrEmpty == 2) {
    hist_a -> Clear();
    hist_ap1 -> Clear();
    hist_b -> Clear();
    hist_bp1 -> Clear();
  }
  cE.Closed();
}

}

//////////////////////////////////////////////////////////////////////////////
//////
//////////////////////////////////////////////////////////////////////////////

void DrawStack_Material_MuonVar(bool my_debug,
  TFile *inputFile,  MuonVar MuonVar_type,
  ME_helium_Playlists PlayList , int doShape,
  int logScale, const char* title, MnvPlotter *plot,
   TCanvas *can, const char *pdf){

    // set up legend, assuming this function only ever plots oodles of stacked histograms
    double x1, x2, y1, y2;
    plot->DecodeLegendPosition(x1, y1, x2, y2, "R", 7, 7, .03);
    TLegend *legend = new TLegend(x1 + .145, y1 + .2, x2 + .16, y2 + .2);
    legend->SetNColumns(1);
    legend->SetTextSize(.03);
    legend->SetFillColor(0);

    auto Material_vector = GetMaterial_typeList();
    auto label_title = GetMuonVarTitleName(MuonVar_type);
    auto xaxislabel = GetMuonVarAXISName(MuonVar_type);
    auto Var_Name =  GetMuonVarHistName(MuonVar_type);

    auto Playlist_name = GetPlaylist_Name(PlayList);
    auto CryoTankStatus = GetFULLorEmpty(GetPlaylist_HeliumStatus(PlayList));



    auto Fulltitle = title + label_title + " playlist: " + Playlist_name + " (" + CryoTankStatus + ") ";
    int Fulltitle_n = Fulltitle.length();
    char FinalTitle[Fulltitle_n + 1];
    strcpy(FinalTitle, Fulltitle.c_str());


    MnvH1D *hist_total;
    THStack *mystack[1];
    mystack[0] = new THStack("hs0", "Stacked");
    int fillCol=0;


    TIter Iter(inputFile->GetListOfKeys());
    TObject *key;

    while((key=Iter()))
    {
      const std::string histName = key->GetName();
      //std::cout<<"HistName = " << histName << std::endl;


      for(auto Material: Material_vector){auto MaterialName = GetNameMaterial(Material);//end of loop

        if(histName.find((Var_Name + "_material_"+ MaterialName)) != std::string::npos  ){

          std::cout<<" Total = " <<  Var_Name + "_material_"+ MaterialName<< std::endl;
          std::cout<<" Total(Key) = " << histName<< std::endl;
          hist_total = dynamic_cast< MnvH1D*>(((TKey*)key)->ReadObj());

        }
        else if(histName.find((MaterialName+"_"+ Var_Name + "_material")) != std::string::npos) //Then this is a NeutrinoEnergy histogram for some material
        {
          std::cout<<"Inside else IF  = " << MaterialName+"_"+ Var_Name + "_material"<<std::endl;

          auto hist = dynamic_cast<MnvH1D*>(((TKey*)key)->ReadObj());
          hist -> SetFillColor(CCNuPionIncPlotting::fill_colors[fillCol]);
          hist -> SetLineColor(CCNuPionIncPlotting::fill_colors[fillCol]);
          hist -> SetFillStyle(1001);
          hist -> SetLineWidth(1);
          fillCol++;
          if(hist == nullptr) //nullptr is the same as NULL effectively, but it does some cool type conversion for std::unique_ptr<>
          {
            std::cerr << histName << " is not a TH1, but it is a neutrinoEnergy histogram!  Skipping " << histName << "...\n";
          }
          hist->Scale(1,"width");
          mystack[0]->Add(hist); //This might want you to derefence hist first
          int n = MaterialName.length();
          char char_array[n + 1];
          strcpy(char_array, MaterialName.c_str());
          legend->AddEntry(hist, char_array);
        }
      }
    }
    legend->AddEntry(hist_total, "Total");
    hist_total->SetMaximum(hist_total->GetMaximum() * 1.45);
    int n = xaxislabel.length();
    char xtitle[n+1];
    strcpy(xtitle, xaxislabel.c_str());
    hist_total->GetXaxis()->SetTitle(xtitle);
    hist_total->GetYaxis()->SetTitle("NEvents");
    hist_total->GetXaxis()->CenterTitle();
    hist_total->GetXaxis()->SetTitleSize(0.038);
    hist_total->Scale(1,"width");
    hist_total->Draw("HIST");
    mystack[0]->Draw("HIST SAME");
    legend->Draw();

    plot->AddHistoTitle(FinalTitle, .04);
    plot->WritePreliminary("TL", .035, 0, 0, false);

    can -> Print(pdf);


  }//ENd of DrawStack_Material

  //////////////////////////////////////////////////////////////////////////////
  //////
  //////////////////////////////////////////////////////////////////////////////

  void DrawStack_Interaction_MuonVar(bool my_debug,
    TFile *inputFile,  MuonVar MuonVar_type,
    ME_helium_Playlists PlayList , int doShape,
     int logScale, const char* title,
    MnvPlotter *plot, TCanvas *can, const char *pdf)
{

  // set up legend, assuming this function only ever plots oodles of stacked histograms
  double x1, x2, y1, y2;
  plot->DecodeLegendPosition(x1, y1, x2, y2, "R", 7, 7, .03);
  TLegend *legend = new TLegend(x1 + .145, y1 + .2, x2 + .16, y2 + .2);
  legend->SetNColumns(1);
  legend->SetTextSize(.03);
  legend->SetFillColor(0);

  auto Interaction_vector = GetInteraction_typeList();

  auto label_title = GetMuonVarTitleName(MuonVar_type);
  auto xaxislabel = GetMuonVarAXISName(MuonVar_type);
  auto Var_Name =  GetMuonVarHistName(MuonVar_type);

  auto Playlist_name = GetPlaylist_Name(PlayList);
  auto CryoTankStatus = GetFULLorEmpty(GetPlaylist_HeliumStatus(PlayList));


  auto Fulltitle = label_title + " playlist: " + Playlist_name + " (" + CryoTankStatus + ") ";
  int Fulltitle_n = Fulltitle.length();
  char FinalTitle[Fulltitle_n + 1];
  strcpy(FinalTitle, Fulltitle.c_str());


  MnvH1D *hist_total;
  THStack *mystack[1];
  mystack[0] = new THStack("hs0", "Stacked");
  int fillCol=0;


  TIter Iter(inputFile->GetListOfKeys());
  TObject *key;

  while((key=Iter()))
  {
    const std::string histName = key->GetName();



    for(auto Interaction: Interaction_vector){auto InteractionName = GetNameInteraction(Interaction);//end of loop

      if(histName.find((Var_Name + "_interaction_"+ InteractionName)) != std::string::npos  ){

        std::cout<<" Total = " <<  Var_Name + "_interaction_"+ InteractionName<< std::endl;
        std::cout<<" Total(Key) = " << histName<< std::endl;
        hist_total = dynamic_cast< MnvH1D*>(((TKey*)key)->ReadObj());

      }
      else if(histName.find((InteractionName+"_"+ Var_Name + "_interaction")) != std::string::npos) //Then this is a NeutrinoEnergy histogram for some material
      {
        std::cout<<"Inside else IF  = " << InteractionName+"_"+ Var_Name + "_interaction"<<std::endl;

        auto hist = dynamic_cast<MnvH1D*>(((TKey*)key)->ReadObj());
        hist -> SetFillColor(CCNuPionIncPlotting::fill_colors[fillCol]);
        hist -> SetLineColor(CCNuPionIncPlotting::fill_colors[fillCol]);
        hist -> SetFillStyle(1001);
        hist -> SetLineWidth(1);
        fillCol++;
        if(hist == nullptr) //nullptr is the same as NULL effectively, but it does some cool type conversion for std::unique_ptr<>
        {
          std::cerr << histName << " is not a TH1, but it is a neutrinoEnergy histogram!  Skipping " << histName << "...\n";
        }
        hist->Scale(1,"width");
        mystack[0]->Add(hist); //This might want you to derefence hist first
        int n = InteractionName.length();
        char char_array[n + 1];
        strcpy(char_array, InteractionName.c_str());
        legend->AddEntry(hist, char_array);
      }
    }
  }
  legend->AddEntry(hist_total, "Total");
  hist_total->SetMaximum(hist_total->GetMaximum() * 1.45);
  int n = xaxislabel.length();
  char xtitle[n+1];
  strcpy(xtitle, xaxislabel.c_str());
  hist_total->GetXaxis()->SetTitle(xtitle);
  hist_total->GetYaxis()->SetTitle("NEvents");
  hist_total->GetXaxis()->CenterTitle();
  hist_total->GetXaxis()->SetTitleSize(0.038);
  hist_total->Scale(1,"width");
  hist_total->Draw("HIST");
  mystack[0]->Draw("HIST SAME");
  legend->Draw();

  plot->AddHistoTitle(FinalTitle, .04);
  plot->WritePreliminary("TL", .035, 0, 0, false);

  can -> Print(pdf);


}//ENd of DrawStack_Interaction

//////////////////////////////////////////////////////////////////////////////
//////
//////////////////////////////////////////////////////////////////////////////

void DrawStack_Particle_MuonVar(bool my_debug,
  TFile *inputFile,  MuonVar MuonVar_type,
  ME_helium_Playlists PlayList ,
  int doShape, int logScale, const char* title,
  MnvPlotter *plot, TCanvas *can, const char *pdf)
{

  // set up legend, assuming this function only ever plots oodles of stacked histograms
  double x1, x2, y1, y2;
  plot->DecodeLegendPosition(x1, y1, x2, y2, "R", 7, 7, .03);
  TLegend *legend = new TLegend(x1 + .145, y1 + .2, x2 + .16, y2 + .2);
  legend->SetNColumns(1);
  legend->SetTextSize(.03);
  legend->SetFillColor(0);

  auto Particle_vector = GetParticle_typeList();

  auto label_title = GetMuonVarTitleName(MuonVar_type);
  auto xaxislabel = GetMuonVarAXISName(MuonVar_type);
  auto Var_Name =  GetMuonVarHistName(MuonVar_type);

  auto Playlist_name = GetPlaylist_Name(PlayList);

  auto CryoTankStatus = GetFULLorEmpty(GetPlaylist_HeliumStatus(PlayList));


  auto Fulltitle = title+ label_title + "playlist: " + Playlist_name + " (" + CryoTankStatus + ") ";
  int Fulltitle_n = Fulltitle.length();
  char FinalTitle[Fulltitle_n + 1];
  strcpy(FinalTitle, Fulltitle.c_str());


  MnvH1D *hist_total;
  THStack *mystack[1];
  mystack[0] = new THStack("hs0", "Stacked");
  int fillCol=0;


  TIter Iter(inputFile->GetListOfKeys());
  TObject *key;

  while((key=Iter()))
  {
    const std::string histName = key->GetName();
    //std::cout<<"HistName = " << histName << std::endl;


    for(auto Particle: Particle_vector){auto ParticleName = GetNameParticle(Particle);//end of loop

      if(histName.find((Var_Name + "_particle_"+ ParticleName)) != std::string::npos  ){

        std::cout<<" Total = " <<  Var_Name + "_particle_"+ ParticleName<< std::endl;
        std::cout<<" Total(Key) = " << histName<< std::endl;
        hist_total = dynamic_cast< MnvH1D*>(((TKey*)key)->ReadObj());

      }
      else if(histName.find((ParticleName+"_"+ Var_Name + "_particle")) != std::string::npos) //Then this is a NeutrinoEnergy histogram for some material
      {
        std::cout<<"Inside else IF  = " << ParticleName+"_"+ Var_Name + "_particle"<<std::endl;

        auto hist = dynamic_cast<MnvH1D*>(((TKey*)key)->ReadObj());
        hist -> SetFillColor(CCNuPionIncPlotting::fill_colors[fillCol]);
        hist -> SetLineColor(CCNuPionIncPlotting::fill_colors[fillCol]);
        hist -> SetFillStyle(1001);
        hist -> SetLineWidth(1);
        fillCol++;
        if(hist == nullptr) //nullptr is the same as NULL effectively, but it does some cool type conversion for std::unique_ptr<>
        {
          std::cerr << histName << " is not a TH1, but it is a neutrinoEnergy histogram!  Skipping " << histName << "...\n";
        }
        hist->Scale(1,"width");
        mystack[0]->Add(hist); //This might want you to derefence hist first
        char char_array[ParticleName.length() + 1];
        strcpy(char_array, ParticleName.c_str());
        legend->AddEntry(hist, char_array);
      }
    }
  }
  legend->AddEntry(hist_total, "Total");
  hist_total->SetMaximum(hist_total->GetMaximum() * 1.45);
  int n = xaxislabel.length();
  char xtitle[n+1];
  strcpy(xtitle, xaxislabel.c_str());
  hist_total->GetXaxis()->SetTitle(xtitle);
  hist_total->GetYaxis()->SetTitle("NEvents");
  hist_total->GetXaxis()->CenterTitle();
  hist_total->GetXaxis()->SetTitleSize(0.038);
  hist_total->Scale(1,"width");
  hist_total->Draw("HIST");
  mystack[0]->Draw("HIST SAME");
  legend->Draw();

  plot->AddHistoTitle(FinalTitle, .04);
  plot->WritePreliminary("TL", .035, 0, 0, false);

  can -> Print(pdf);


}//ENd of DrawStack_paricle

//////////////////////////////////////////////////////////////////////////////
//////
//////////////////////////////////////////////////////////////////////////////

void Draw2DHist(MnvH2D *hist, const char* xaxislabel,const char* yaxislabel,
                const char* Title, const char* pdf, TCanvas *can, MnvPlotter *plot)
{
  string TotalTitle = string(Title);
  gStyle->SetPalette(kCool);


  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->CenterTitle();
  hist->GetXaxis()->SetTitle(xaxislabel);
  hist->GetYaxis()->SetTitle(yaxislabel);
  hist->GetXaxis()->SetTitleSize(0.038);
  hist->GetYaxis()->SetTitleSize(0.038);
  hist->Draw("COLZ");

  plot->AddHistoTitle(TotalTitle.c_str(), .035);
  plot->WritePreliminary("TL", .035, 0, 0, false);

  gPad->Update();
  can->Modified();
  can->Print(pdf);
  can->Closed();


}//end of 2D draw function
//////////////////////////////////////////////////////////////////////////////
//////
//////////////////////////////////////////////////////////////////////////////

void Draw2DHist(
  MnvH2D *hist, const char* xaxislabel,
  const char* yaxislabel, const char* Title,
  const char* pdf, TCanvas *can,
   MnvPlotter *plot, double setMax)
{
  string TotalTitle = string(Title);
  gStyle->SetPalette(kCool);


  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->CenterTitle();
  hist->GetXaxis()->SetTitle(xaxislabel);
  hist->GetYaxis()->SetTitle(yaxislabel);
  hist->GetXaxis()->SetTitleSize(0.038);
  hist->GetYaxis()->SetTitleSize(0.038);
  hist->SetMaximum(setMax);
  hist->Draw("COLZ");

  plot->AddHistoTitle(TotalTitle.c_str(), .035);
  plot->WritePreliminary("TL", .035, 0, 0, false);

  gPad->Update();
  can->Modified();
  can->Print(pdf);
  can->Closed();


}//end of 2D draw function
//////////////////////////////////////////////////////////////////////////////
//////
//////////////////////////////////////////////////////////////////////////////
void Draw2DHist_warp(MnvH2D *hist_input,
   const char* xaxislabel,const char* yaxislabel,
   const char* Title, const char* pdf, TCanvas *can,
   MnvPlotter *plot)
{
  MnvH2D *hist =  (PlotUtils::MnvH2D*)hist_input->Clone("hist");

  string TotalTitle = string(Title);
  gStyle->SetPalette(kBird);


  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->CenterTitle();
  hist->GetXaxis()->SetTitle(xaxislabel);
  hist->GetYaxis()->SetTitle(yaxislabel);
  hist->GetXaxis()->SetTitleSize(0.038);
  hist->GetYaxis()->SetTitleSize(0.038);
  hist->Draw("CONT4Z");

  plot->AddHistoTitle(TotalTitle.c_str(), .035);
  plot->WritePreliminary("TL", .035, 0, 0, false);

  gPad->Update();
  can->Modified();
  can->Print(pdf);
  can->Closed();


}//end of 2D draw function
//////////////////////////////////////////////////////////////////////////////
//////
//////////////////////////////////////////////////////////////////////////////
void Draw2DHist_warpFit(MnvH2D *hist_input,
   const char* xaxislabel,const char* yaxislabel,
   const char* Title,
   const char* pdf, TCanvas *can, MnvPlotter *plot)
{
  MnvH2D *hist =  (PlotUtils::MnvH2D*)hist_input->Clone("hist");

  string TotalTitle = string(Title);
  gStyle->SetPalette(kBird);

  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->CenterTitle();
  hist->GetXaxis()->SetTitle(xaxislabel);
  hist->GetYaxis()->SetTitle(yaxislabel);
  hist->GetXaxis()->SetTitleSize(0.038);
  hist->GetYaxis()->SetTitleSize(0.038);
  hist->Draw("COLZ");
  plot->AddHistoTitle(TotalTitle.c_str(), .035);
  plot->WritePreliminary("TL", .035, 0, 0, false);


  int NBinsX = hist->GetNbinsX() ;
  int NBinsY = hist->GetNbinsY() ;

  double Xmin =  hist->GetXaxis()-> GetBinLowEdge(1);
  double Ymin =  hist->GetYaxis()-> GetBinLowEdge(1);

  double Xmax =  hist->GetXaxis()-> GetBinUpEdge(NBinsX);
  double Ymax =  hist->GetYaxis()-> GetBinUpEdge(NBinsY);
  const Int_t npar = 10;
  double par0 = 1;
  double par1 = 4;
  double par2 = 1;
  double par3 = .25;
  double par4 = 1;

  double par5 = 1;
  double par6 = 11;
  double par7 = 1;
  double par8 = 1.5;
  double par9 = 1;

  //double par10 = 1;
  //double par11 = 16;
  //double par12 = 1;
  //double par13 = .35;
  //double par14 = 1;




  Double_t f2params[npar] = {par0,par1,par2,par3,par4,par5,par6,par7,par8,par9}; // ,par10,par11,par12,par13,par14,par10,par11,par12,par13,par14
//  Double_t f2params[npar] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};


   TF2 *f2 = new TF2("f2",Gaussianfun3,Xmin,Xmax,Ymin,Ymax, npar);
   f2->SetParameters(f2params);
   //Int_t nentries = 500000;
   hist->Fit("f2");
   //f2->Draw("CONTZ Same");
   f2->DrawCopy("cont1 same");

   gStyle->SetOptStat(1111);
   gStyle->SetOptFit(1011);


   gPad->Update();
   can->Modified();
   can->Print(pdf);


   can->Closed();





}//end of 2D draw function
//////////////////////////////////////////////////////////////////////////////
//////
//////////////////////////////////////////////////////////////////////////////
void Draw2DHist_warpFit(MnvH2D *hist_input,
   const char* xaxislabel,const char* yaxislabel,
   const char* Title,
   const char* pdf, TCanvas *can,
   MnvPlotter *plot, char *Text_fitParms)
{
  MnvH2D *hist =  (PlotUtils::MnvH2D*)hist_input->Clone("hist");

  string TotalTitle = string(Title);
  gStyle->SetPalette(kBird);

  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->CenterTitle();
  hist->GetXaxis()->SetTitle(xaxislabel);
  hist->GetYaxis()->SetTitle(yaxislabel);
  hist->GetXaxis()->SetTitleSize(0.038);
  hist->GetYaxis()->SetTitleSize(0.038);
  hist->Draw("COLZ");
  plot->AddHistoTitle(TotalTitle.c_str(), .035);
  plot->WritePreliminary("TL", .035, 0, 0, false);


  int NBinsX = hist->GetNbinsX() ;
  int NBinsY = hist->GetNbinsY() ;

  double Xmin =  hist->GetXaxis()-> GetBinLowEdge(1);
  double Ymin =  hist->GetYaxis()-> GetBinLowEdge(1);

  double Xmax =  hist->GetXaxis()-> GetBinUpEdge(NBinsX);
  double Ymax =  hist->GetYaxis()-> GetBinUpEdge(NBinsY);
  const Int_t npar = 10;
  double par0 = 1;
  double par1 = 4;
  double par2 = 1;
  double par3 = .25;
  double par4 = 1;

  double par5 = 1;
  double par6 = 11;
  double par7 = 1;
  double par8 = 1.5;
  double par9 = 1;

  //double par10 = 1;
  //double par11 = 16;
  //double par12 = 1;
  //double par13 = .35;
  //double par14 = 1;
  Double_t f2params[npar] = {par0,par1,par2,par3,par4,par5,par6,par7,par8,par9}; // ,par10,par11,par12,par13,par14,par10,par11,par12,par13,par14


   TF2 *f2 = new TF2("f2",Gaussianfun3,Xmin,Xmax,Ymin,Ymax, npar);
   f2->SetParameters(f2params);
   //Int_t nentries = 500000;
   hist->Fit("f2");
   //f2->Draw("CONTZ Same");
   f2->DrawCopy("cont1 same");
   f2->GetParameters(f2params);
   gStyle->SetOptStat(1111);
   gStyle->SetOptFit(1011);

   std::ofstream outfile(Text_fitParms);
   outfile<<f2params[0]<<std::endl;
   outfile<<f2params[1]<<std::endl;
   outfile<<f2params[2]<<std::endl;
   outfile<<f2params[3]<<std::endl;
   outfile<<f2params[4]<<std::endl;
   outfile<<f2params[5]<<std::endl;
   outfile<<f2params[6]<<std::endl;
   outfile<<f2params[7]<<std::endl;
   outfile<<f2params[8]<<std::endl;
   outfile<<f2params[9]<<std::endl;
   outfile.close();

   gPad->Update();
   can->Modified();
   can->Print(pdf);






   can->Closed();





}//end of 2D draw function
//////////////////////////////////////////////////////////////////////////////
//////
//////////////////////////////////////////////////////////////////////////////
void Draw2DHist_warpFit2DGaussian(MnvH2D *hist_input,
  const char* xaxislabel,const char* yaxislabel,
  const char* Title, const char* pdf,
  TCanvas *can, MnvPlotter *plot)
{
  MnvH2D *hist =  (PlotUtils::MnvH2D*)hist_input->Clone("hist");

  string TotalTitle = string(Title);
  gStyle->SetPalette(kBird);

  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->CenterTitle();
  hist->GetXaxis()->SetTitle(xaxislabel);
  hist->GetYaxis()->SetTitle(yaxislabel);
  hist->GetXaxis()->SetTitleSize(0.038);
  hist->GetYaxis()->SetTitleSize(0.038);
  hist->Draw("COLZ");
  plot->AddHistoTitle(TotalTitle.c_str(), .035);
  plot->WritePreliminary("TL", .035, 0, 0, false);


  int NBinsX = hist->GetNbinsX() ;
  int NBinsY = hist->GetNbinsY() ;

  double Xmin =  hist->GetXaxis()-> GetBinLowEdge(1);
  double Ymin =  hist->GetYaxis()-> GetBinLowEdge(1);

  double Xmax =  hist->GetXaxis()-> GetBinUpEdge(NBinsX);
  double Ymax =  hist->GetYaxis()-> GetBinUpEdge(NBinsY);
  const Int_t npar = 5;

  double par0 = 300;
  double par1 = 6.5;
  double par2 = 1;
  double par3 = 1;
  double par4 = 1;


  //double par10 = 1;
  //double par11 = 16;
  //double par12 = 1;
  //double par13 = .35;
  //double par14 = 1;




  Double_t f2params[npar] = {par0,par1,par2,par3,par4}; //
//  Double_t f2params[npar] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};


   TF2 *f2 = new TF2("f2",Gaussian2D,Xmin,Xmax,Ymin,Ymax, npar);
   f2->SetParameters(f2params);
   f2->SetParNames("A","E_{#nu}","#sigma_{E_{#nu}}","X","#sigma_{X}");
   //Int_t nentries = 500000;
   hist->Fit("f2");
   //f2->Draw("CONTZ Same");
   f2->DrawCopy("cont1 same");

   double  chi_sq = f2->GetChisquare();
   int NDF_int = f2->GetNDF();
   double chi_sq_ndf = chi_sq / (double)NDF_int;

   gStyle->SetOptStat(1111);
   gStyle->SetOptFit(1011);
   TLatex* text = new TLatex;
   text->SetNDC();
   text->SetTextSize(0.03);
   text->SetTextColor(kRed);
   text->DrawLatex(0.35, 0.85, Form("Plot #chi^{2} = %3.4f", chi_sq));
   text->DrawLatex(0.35, 0.82, Form("Plot #chi^{2}/dof[%d] = %3.4f", NDF_int, chi_sq_ndf ));

   gPad->Update();
   can->Modified();
   can->Print(pdf);


   can->Closed();





}//end of 2D draw function
//////////////////////////////////////////////////////////////////////////////
//////
//////////////////////////////////////////////////////////////////////////////
void Draw2DHist_warpFit2DGaussian(MnvH2D *hist_input,
  const char* xaxislabel,const char* yaxislabel,
                const char* Title, const char* pdf,
                TCanvas *can, MnvPlotter *plot,
                double MinX, double MaxX)
{
  MnvH2D *hist =  (PlotUtils::MnvH2D*)hist_input->Clone("hist");

  string TotalTitle = string(Title);
  gStyle->SetPalette(kBird);

  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->CenterTitle();
  hist->GetXaxis()->SetTitle(xaxislabel);
  hist->GetYaxis()->SetTitle(yaxislabel);
  hist->GetXaxis()->SetTitleSize(0.038);
  hist->GetYaxis()->SetTitleSize(0.038);
  hist->Draw("COLZ");
  plot->AddHistoTitle(TotalTitle.c_str(), .035);
  plot->WritePreliminary("TL", .035, 0, 0, false);


  int NBinsX = hist->GetNbinsX() ;
  int NBinsY = hist->GetNbinsY() ;

  double Xmin =  hist->GetXaxis()-> GetBinLowEdge(1);
  double Ymin =  hist->GetYaxis()-> GetBinLowEdge(1);

  double Xmax =  hist->GetXaxis()-> GetBinUpEdge(NBinsX);
  double Ymax =  hist->GetYaxis()-> GetBinUpEdge(NBinsY);
  const Int_t npar = 5;

  double par0 = 300;
  double par1 = 6.5;
  double par2 = 1;
  double par3 = 1;
  double par4 = 1;


  //double par10 = 1;
  //double par11 = 16;
  //double par12 = 1;
  //double par13 = .35;
  //double par14 = 1;




  Double_t f2params[npar] = {par0,par1,par2,par3,par4}; //
//  Double_t f2params[npar] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};


   TF2 *f2 = new TF2("f2",Gaussian2D,MinX,MaxX,Ymin,Ymax, npar);
   f2->SetParameters(f2params);
   f2->SetParNames("A","E_{#nu}","#sigma_{E_{#nu}}","X","#sigma_{X}");
   //Int_t nentries = 500000;
   hist->Fit("f2");
   //f2->Draw("CONTZ Same");
   f2->DrawCopy("cont1 same");

   double  chi_sq = f2->GetChisquare();
   int NDF_int = f2->GetNDF();
   double chi_sq_ndf = chi_sq / (double)NDF_int;

   gStyle->SetOptStat(1111);
   gStyle->SetOptFit(1011);
   TLatex* text = new TLatex;
   text->SetNDC();
   text->SetTextSize(0.03);
   text->SetTextColor(kRed);
   text->DrawLatex(0.35, 0.85, Form("Plot #chi^{2} = %3.4f", chi_sq));
   text->DrawLatex(0.35, 0.82, Form("Plot #chi^{2}/dof[%d] = %3.4f", NDF_int, chi_sq_ndf ));

   gPad->Update();
   can->Modified();
   can->Print(pdf);


   can->Closed();





 }//end of 2D draw function
 //////////////////////////////////////////////////////////////////////////////
 //////
 //////////////////////////////////////////////////////////////////////////////
void Draw2DHist_warpFit2DGaussian(
  MnvH2D *hist_input,
  const char* xaxislabel,const char* yaxislabel,
   double chi2fit,double ndfinput,
   double par0, double par1,double par2,double par3,double par4,
   double par_Error0,double par_Error1,
   double par_Error2,double par_Error3,double par_Error4,
  const char* Title, const char* pdf,
   TCanvas *can, MnvPlotter *plot)
{
  MnvH2D *hist =  (PlotUtils::MnvH2D*)hist_input->Clone("hist");

  string TotalTitle = string(Title);
  gStyle->SetPalette(kBird);

  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->CenterTitle();
  hist->GetXaxis()->SetTitle(xaxislabel);
  hist->GetYaxis()->SetTitle(yaxislabel);
  hist->GetXaxis()->SetTitleSize(0.038);
  hist->GetYaxis()->SetTitleSize(0.038);
  hist->Draw("COLZ");
  plot->AddHistoTitle(TotalTitle.c_str(), .035);
  plot->WritePreliminary("TL", .035, 0, 0, false);


  int NBinsX = hist->GetNbinsX() ;
  int NBinsY = hist->GetNbinsY() ;

  double Xmin =  hist->GetXaxis()-> GetBinLowEdge(1);
  double Ymin =  hist->GetYaxis()-> GetBinLowEdge(1);

  double Xmax =  hist->GetXaxis()-> GetBinUpEdge(NBinsX);
  double Ymax =  hist->GetYaxis()-> GetBinUpEdge(NBinsY);
  const Int_t npar = 5;
  Double_t f2params[npar] = {par0,par1,par2,par3,par4}; //
//  Double_t f2params[npar] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};


   TF2 *f2 = new TF2("f2",Gaussian2D,Xmin,Xmax,Ymin,Ymax, npar);
   f2->SetParameters(f2params);
   f2->SetParNames("A","E_{#nu}","#sigma_{E_{#nu}}","X","#sigma_{X}");

   f2->DrawCopy("cont1 same");


   double chi_sq_ndf = chi2fit / ndfinput;

   //gStyle->SetOptStat(1111);
   //gStyle->SetOptFit(1111);
   TLatex* text = new TLatex;
   text->SetNDC();
   text->SetTextSize(0.03);
   text->SetTextColor(kRed);
   double yplace = .85;
   double xplace = .6;
   text->DrawLatex(xplace, yplace, Form("Plot #chi^{2} = %3.4f", chi2fit));
       yplace-=.05;
   text->DrawLatex(xplace, yplace, Form("Plot #chi^{2}/dof[%d] = %3.4f", (int)ndfinput, chi_sq_ndf ));
       yplace-=.08;
   text->DrawLatex(xplace, yplace, Form("A exp((#frac{X-E_{#nu}}{#sigma_{E}})^{2} + #frac{Y-X_{o}}{#sigma_{X}})^{2})"));
    yplace-=.06;
    text->DrawLatex(xplace, yplace, Form("A =  %3.3f #pm %3.3f", par0, par_Error0));
    yplace-=.03;
    text->DrawLatex(xplace, yplace, Form("E_{#nu} =  %3.3f #pm %3.3f", par1, par_Error1));
    yplace-=.03;
    text->DrawLatex(xplace, yplace, Form("#sigma_{E} =  %3.3f #pm %3.3f", par2, par_Error2));
    yplace-=.03;
    text->DrawLatex(xplace, yplace, Form("X_{o} =  %3.3f #pm %3.3f", par3, par_Error3));
    yplace-=.03;
    text->DrawLatex(xplace, yplace, Form("#sigma_{X} =  %3.3f #pm %3.3f", par4, par_Error4));
   gPad->Update();
   can->Modified();
   can->Print(pdf);


   can->Closed();





}//end of 2D draw function
//////////////////////////////////////////////////////////////////////////////
//////
//////////////////////////////////////////////////////////////////////////////
void Draw2DHist_warpFit2DGaussian_joint(MnvH2D *hist_input,
  MnvH2D *hist2_input, const char* xaxislabel,
  const char* yaxislabel,
  const char* Title, const char* pdf,
   TCanvas *can, MnvPlotter *plot)
{
  MnvH2D *hist =  (PlotUtils::MnvH2D*)hist_input->Clone("hist");

  string TotalTitle = string(Title);
  gStyle->SetPalette(kBird);

  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->CenterTitle();
  hist->GetXaxis()->SetTitle(xaxislabel);
  hist->GetYaxis()->SetTitle(yaxislabel);
  hist->GetXaxis()->SetTitleSize(0.038);
  hist->GetYaxis()->SetTitleSize(0.038);
  hist->Draw("COLZ");
  plot->AddHistoTitle(TotalTitle.c_str(), .035);
  plot->WritePreliminary("TL", .035, 0, 0, false);


  int NBinsX = hist->GetNbinsX() ;
  int NBinsY = hist->GetNbinsY() ;

  double Xmin =  hist->GetXaxis()-> GetBinLowEdge(1);
  double Ymin =  hist->GetYaxis()-> GetBinLowEdge(1);

  double Xmax =  hist->GetXaxis()-> GetBinUpEdge(NBinsX);
  double Ymax =  hist->GetYaxis()-> GetBinUpEdge(NBinsY);
  const Int_t npar = 5;
  double par0 = 1;
  double par1 = 5;
  double par2 = 1;
  double par3 = 6.5;
  double par4 = 1;


  //double par10 = 1;
  //double par11 = 16;
  //double par12 = 1;
  //double par13 = .35;
  //double par14 = 1;




  Double_t f2params[npar] = {par0,par1,par2,par3,par4}; //
//  Double_t f2params[npar] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};


   TF2 *f2 = new TF2("f2",Gaussian2D,Xmin,Xmax,Ymin,Ymax, npar);
   f2->SetParameters(f2params);
   //Int_t nentries = 500000;
   hist->Fit("f2");

   //f2->Draw("CONTZ Same");
   f2->DrawCopy("cont1 same");

   gStyle->SetOptStat(1111);
   gStyle->SetOptFit(1011);


   gPad->Update();
   can->Modified();
   can->Print(pdf);


   can->Closed();





}//end of 2D draw function

////////////////////////////////////////////////////////////////////////////////
//////
////////////////////////////////////////////////////////////////////////////////
void Draw2DHist_warpFit_show(MnvH2D *hist_input,
   const char* xaxislabel,const char* yaxislabel,
                const char* Title,
                const char* pdf,
                TCanvas *can, MnvPlotter *plot)
{
  MnvH2D *hist =  (PlotUtils::MnvH2D*)hist_input->Clone("hist");

  string TotalTitle = string(Title);
  gStyle->SetPalette(kBird);

  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->CenterTitle();
  hist->GetXaxis()->SetTitle(xaxislabel);
  hist->GetYaxis()->SetTitle(yaxislabel);
  hist->GetXaxis()->SetTitleSize(0.038);
  hist->GetYaxis()->SetTitleSize(0.038);
  hist->SetStats(0);
  hist->Draw("SCAT");
  plot->AddHistoTitle(TotalTitle.c_str(), .035);
  plot->WritePreliminary("TL", .035, 0, 0, false);

  int NBinsX = hist->GetNbinsX() ;
  int NBinsY = hist->GetNbinsY() ;

  double Xmin =  hist->GetXaxis()-> GetBinLowEdge(1);
  double Ymin =  hist->GetYaxis()-> GetBinLowEdge(1);

  double Xmax =  hist->GetXaxis()-> GetBinUpEdge(NBinsX);
  double Ymax =  hist->GetYaxis()-> GetBinUpEdge(NBinsY);
  const Int_t npar = 10;

  double par0 = 1;
  double par1 = 4;
  double par2 = 1;
  double par3 = .25;
  double par4 = 1;

  double par5 = 1;
  double par6 = 11;
  double par7 = 1;
  double par8 = 1.5;
  double par9 = 1;

  //double par10 = 1;
  //double par11 = 16;
  //double par12 = 1;
  //double par13 = .35;
  //double par14 = 1;




  Double_t f2params[npar] = {par0,par1,par2,par3,par4,par5,par6,par7,par8,par9}; // ,par10,par11,par12,par13,par14
  //  Double_t f2params[npar] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

  Double_t f2params_Get[npar];
   TF2 *f2 = new TF2("f2",Gaussianfun3,Xmin,Xmax, Ymin,Ymax, npar);
   f2->GetXaxis()->CenterTitle();
   f2->GetYaxis()->CenterTitle();
   f2->GetXaxis()->SetTitle(xaxislabel);
   f2->GetYaxis()->SetTitle(yaxislabel);
   f2->GetXaxis()->SetTitleSize(0.038);
   f2->GetYaxis()->SetTitleSize(0.038);
   f2->SetParameters(f2params);
   //Int_t nentries = 500000;
   hist->Fit("f2");
   f2->Draw("SAME COLZ");
   f2->GetParameters(f2params_Get);
   std::ofstream outfile("FitParams_2D.txt");
   outfile<<f2params_Get[0]<<std::endl;
   outfile<<f2params_Get[1]<<std::endl;
   outfile<<f2params_Get[2]<<std::endl;
   outfile<<f2params_Get[3]<<std::endl;
   outfile<<f2params_Get[4]<<std::endl;
   outfile<<f2params_Get[5]<<std::endl;
   outfile<<f2params_Get[6]<<std::endl;
   outfile<<f2params_Get[7]<<std::endl;
   outfile<<f2params_Get[8]<<std::endl;
   outfile<<f2params_Get[9]<<std::endl;
   outfile.close();

   //gStyle->SetOptStat(1111);
   //gStyle->SetOptFit(1011);


   gPad->Update();
   can->Modified();
   can->Print(pdf);


   can->Closed();





}//end of 2D draw function
////////////////////////////////////////////////////////////////////////////////
//////
////////////////////////////////////////////////////////////////////////////////
void Draw2DHist_warpFit_show(MnvH2D *hist_input,
   const char* xaxislabel,const char* yaxislabel,
                const char* Title,
                const char* pdf,
                TCanvas *can, MnvPlotter *plot, Double_t *pars)
{
  MnvH2D *hist =  (PlotUtils::MnvH2D*)hist_input->Clone("hist");

  string TotalTitle = string(Title);
  gStyle->SetPalette(kBird);

  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->CenterTitle();
  hist->GetXaxis()->SetTitle(xaxislabel);
  hist->GetYaxis()->SetTitle(yaxislabel);
  hist->GetXaxis()->SetTitleSize(0.038);
  hist->GetYaxis()->SetTitleSize(0.038);
  hist->SetStats(0);
  hist->Draw("SCAT");
  plot->AddHistoTitle(TotalTitle.c_str(), .035);
  plot->WritePreliminary("TL", .035, 0, 0, false);

  int NBinsX = hist->GetNbinsX() ;
  int NBinsY = hist->GetNbinsY() ;

  double Xmin =  hist->GetXaxis()-> GetBinLowEdge(1);
  double Ymin =  hist->GetYaxis()-> GetBinLowEdge(1);

  double Xmax =  hist->GetXaxis()-> GetBinUpEdge(NBinsX);
  double Ymax =  hist->GetYaxis()-> GetBinUpEdge(NBinsY);
  const Int_t npar = 10;


   TF2 *f2 = new TF2("f2",Gaussianfun3,Xmin,Xmax, Ymin,Ymax, npar);
   f2->GetXaxis()->CenterTitle();
   f2->GetYaxis()->CenterTitle();
   f2->GetXaxis()->SetTitle(xaxislabel);
   f2->GetYaxis()->SetTitle(yaxislabel);
   f2->GetXaxis()->SetTitleSize(0.038);
   f2->GetYaxis()->SetTitleSize(0.038);
   f2->SetParameters(pars);
   //Int_t nentries = 500000;
   f2->Draw("CONT4Z same");




   gPad->Update();
   can->Modified();
   can->Print(pdf);


   can->Closed();





}//end of 2D draw function
////////////////////////////////////////////////////////////////////////////////
//////
////////////////////////////////////////////////////////////////////////////////
Double_t Gaussian2D(Double_t *x, Double_t *par) {
   Double_t r1 = Double_t((x[0]-par[1])/par[2]);
   Double_t r2 = Double_t((x[1]-par[3])/par[4]);
   return par[0]*TMath::Exp(-0.5*(r1*r1+r2*r2));
}
////////////////////////////////////////////////////////////////////////////////
//////
////////////////////////////////////////////////////////////////////////////////
Double_t Gaussianfun3(Double_t *x, Double_t *par) {
   Double_t *p1 = &par[0];
   Double_t *p2 = &par[5];
   //Double_t *p3 = &par[10];
   Double_t result = Gaussian2D(x,p1) + Gaussian2D(x,p2); //+ Gaussian2D(x,p3);
   return result;
}
////////////////////////////////////////////////////////////////////////////////
//////
////////////////////////////////////////////////////////////////////////////////
Double_t WarpingFunctionPZ_PT_GeV(Double_t *x, Double_t *par) {
  Double_t inputpar[10]={1.09156, 1.3852, 2.12451, 0.140716, 0.253279, 1.31382, 13.7064, 9.94762, 1.35258, 1.22424};
  return Gaussianfun3(x, inputpar);
}
////////////////////////////////////////////////////////////////////////////////
//////
////////////////////////////////////////////////////////////////////////////////
Double_t WarpingFunctionPZ_PT_GeV_Daisy(Double_t *x, Double_t *par) {
  return Gaussianfun3(x, par);
}
////////////////////////////////////////////////////////////////////////////////
//////
////////////////////////////////////////////////////////////////////////////////
double WarpingFunctionPZ_PT_GeV(double True_PZ, double True_PT,Double_t *par) {
  Double_t x[2]; x[0]= True_PZ; x[1]= True_PT;
  return Gaussianfun3(x, par);
}
////////////////////////////////////////////////////////////////////////////////
//////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//////
////////////////////////////////////////////////////////////////////////////////
Double_t Poly6_1D(Double_t *x, Double_t *par) {
  return par[0] + par[1] * x[0] + pow(x[0],2) * par[2] + pow(x[0],3) * par[3] + pow(x[0],4) * par[4]+ pow(x[0],5) * par[5]+ pow(x[0],6) * par[6];
}
////////////////////////////////////////////////////////////////////////////////
//////
////////////////////////////////////////////////////////////////////////////////
Double_t Poly5_1D(Double_t *x, Double_t *par) {
   return par[0] + par[1] * x[0] + pow(x[0],2) * par[2] + pow(x[0],3) * par[3] + pow(x[0],4) * par[4] + pow(x[0],5) * par[5];
}
////////////////////////////////////////////////////////////////////////////////
//////
////////////////////////////////////////////////////////////////////////////////
Double_t Poly4_1D(Double_t *x, Double_t *par) {
   return par[0] + par[1] * x[0] + pow(x[0],2) * par[2] + pow(x[0],3) * par[3]  + pow(x[0],4) * par[4];

}
////////////////////////////////////////////////////////////////////////////////
//////
////////////////////////////////////////////////////////////////////////////////
Double_t Poly3_1D(Double_t *x, Double_t *par) {
   return par[0] + par[1] * x[0] + pow(x[0],2) * par[2] + pow(x[0],3) * par[3];
}
////////////////////////////////////////////////////////////////////////////////
//////
////////////////////////////////////////////////////////////////////////////////
Double_t WarpingFunctionPZ_GeV(Double_t *x, Double_t *par){

  Double_t inputpar[6]={2.99536, -1.31522, 0.299975, -0.0322951, 0.00168097, -.0000336038};

  if(x[0] >= 16 ){
    Double_t y[1]; y[0]= 16;
    return Poly5_1D(y, inputpar);
  }
  else{
    return  Poly5_1D(x, inputpar);
  }
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
Double_t WarpingFunction_DAISY_poly3_PZ_GeV(Double_t *x, Double_t *par){



  if(x[0] <= 5 ){
    Double_t y[1]; y[0]= 5;
    return Poly3_1D(y, par);
  }
  else if (x[0] >= 15){
    Double_t y[1]; y[0]= 15;
    return Poly3_1D(y, par);
  }
  else{
    return  Poly3_1D(x, par);
  }
}
////////////////////////////////////////////////////////////////////////////////
//////
////////////////////////////////////////////////////////////////////////////////
double WarpingFunctionPZ_GeV(double TruePZ){
  Double_t input[1]; input[0]= TruePZ;
  Double_t *par;
  return WarpingFunctionPZ_GeV(input, par);
}
////////////////////////////////////////////////////////////////////////////////
//////
////////////////////////////////////////////////////////////////////////////////
double WarpingFunction_Daisy_PZ_GeV(double TruePZ, Double_t *par ){
  Double_t input[1]; input[0]= TruePZ;
  return WarpingFunction_DAISY_poly3_PZ_GeV(input, par);
}
 ////////////////////////////////////////////////////////////////////////////////
 //////
 ////////////////////////////////////////////////////////////////////////////////
Double_t WarpingFunctionPT_GeV(Double_t *x, Double_t *par){

  Double_t inputpar[5]={0.81639,0.732951,-2.01992,2.05417,-0.580941};

  if(x[0] >= 1.75 ){
    Double_t y[1]; y[0]= 1.75;
    return Poly4_1D(y, inputpar);
  }
  else{
    return  Poly4_1D(x, inputpar);
  }
}
////////////////////////////////////////////////////////////////////////////////
//////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
Double_t WarpingFunction_DAISY_poly3_PT_GeV(Double_t *x, Double_t *par){
  if(x[0] >= 1.75 ){
    Double_t y[1]; y[0]= 1.75;
    return par[0] + par[1] * y[0] + pow(y[0],2) * par[2] + pow(y[0],3) * par[3];
  }
  else{
    return par[0] + par[1] * x[0] + pow(x[0],2) * par[2] + pow(x[0],3) * par[3];
  }
}
////////////////////////////////////////////////////////////////////////////////
//////
////////////////////////////////////////////////////////////////////////////////
double WarpingFunctionPT_GeV(double TruePT){
  Double_t input[1]; input[0]= TruePT;
     Double_t *par;
 return WarpingFunctionPT_GeV(input, par);

}
////////////////////////////////////////////////////////////////////////////////
//////
////////////////////////////////////////////////////////////////////////////////
double WarpingFunction_DAISY_PT_GeV(double TruePT, Double_t *par){
  Double_t input[1]; input[0]= TruePT;
 return WarpingFunction_DAISY_poly3_PT_GeV(input, par);

}
////////////////////////////////////////////////////////////////////////////////
//////
////////////////////////////////////////////////////////////////////////////////
Double_t WarpingFunctionE_GeV(Double_t *x, Double_t *par){

  Double_t inputpar[6]={1.22268,-0.203765,0.0318782,-0.00178157,4.13874e-05,-3.3933e-07};

  if(x[0] < 5.0 ){
    Double_t y[1]; y[0]= 5.0;
    double y1 = .7;
    double y2 =  Poly5_1D(y, inputpar);
    Double_t value =  ((y2 - y1 ) / 5.0) * x[0]  + y1;
    return value;
  }
  else if(x[0] > 44.0){
    Double_t y[1]; y[0]= 44.0;
    return Poly5_1D(y, inputpar);

  }
  else{
    return  Poly5_1D(x, inputpar);
  }
}
////////////////////////////////////////////////////////////////////////////////
//////
////////////////////////////////////////////////////////////////////////////////
Double_t WarpingFunction_DAISY_poly3_E_GeV(Double_t *x, Double_t *par){

  if(x[0] >= 35 ){
    Double_t y[1]; y[0]= 35;
    return Poly3_1D(y,par);
  }
  else{
    return  Poly3_1D(x,par);
  }
}
////////////////////////////////////////////////////////////////////////////////
//////
////////////////////////////////////////////////////////////////////////////////
double WarpingFunctionE_GeV(double TrueE){
    Double_t y[1]; y[0]= TrueE;
 Double_t *par;
return WarpingFunctionE_GeV(y, par);

}
////////////////////////////////////////////////////////////////////////////////
//////
////////////////////////////////////////////////////////////////////////////////
double WarpingFunction_Daisy_E_GeV(double TrueE, Double_t *par){
    Double_t y[1]; y[0]= TrueE;
return WarpingFunction_DAISY_poly3_E_GeV(y, par);

}
////////////////////////////////////////////////////////////////////////////////
//////
////////////////////////////////////////////////////////////////////////////////
Double_t WarpingFunctionTheta_Deg(Double_t *x, Double_t *par){

  Double_t inputpar[5]={1.23875,-0.287772,0.0832033,-0.00952066,0.000367046};


  if(x[0] >= 12.0 ){
    Double_t y[1]; y[0]= 12.0;
    return Poly4_1D(y, inputpar);
  }
  else{
    return  Poly4_1D(x, inputpar);
  }
}
////////////////////////////////////////////////////////////////////////////////
//////
////////////////////////////////////////////////////////////////////////////////
Double_t WarpingFunction_DAISY_poly3_Theta_Deg(Double_t *x, Double_t *par){
return  Poly3_1D(x, par);
}
////////////////////////////////////////////////////////////////////////////////
//////
////////////////////////////////////////////////////////////////////////////////
double WarpingFunctionTheta_Deg(double TrueTheta){
  Double_t y[1]; y[0]= TrueTheta;
 Double_t *par;
return WarpingFunctionTheta_Deg(y,par);
}

////////////////////////////////////////////////////////////////////////////////
//////
////////////////////////////////////////////////////////////////////////////////
double WarpingFunctionTheta_Deg(double TrueTheta,Double_t *par){
  Double_t y[1]; y[0]= TrueTheta;
return  WarpingFunction_DAISY_poly3_Theta_Deg(y,par);
}

////////////////////////////////////////////////////////////////////////////////
//////
////////////////////////////////////////////////////////////////////////////////
void Draw2DHist_MvR(MnvH2D *hist, const char* xaxislabel,const char* yaxislabel,char* zaxislabel,
                const char* Title, const char* pdf, TCanvas *can, MnvPlotter *plot,
                 std::vector<double> BigAxisX, std::vector<double> BigAxisY,
                std::vector<double> BigAxisX_small, std::vector<double> BigAxisY_small, bool setcolorMap)
{

  string TotalTitle = string(Title);

if(setcolorMap==true){gStyle->SetPalette(kGreenPink);}

  double Xstart = BigAxisX.front();
  double Xend = BigAxisX.back();
  double Ystart = BigAxisY.front();
  double Yend = BigAxisY.back();

  int N_XAxis = BigAxisX.size() + 2;
  int N_YAxis = BigAxisY.size() + 2;

  double Xstart_small = BigAxisX_small.front();
  double Xend_small   = BigAxisX_small.back();
  double Ystart_small = BigAxisY_small.front();
  double Yend_small   = BigAxisY_small.back();
  int N_XAxis_small   = BigAxisX_small.size() + 2;
  int N_YAxis_small   = BigAxisY_small.size() + 2;
  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->CenterTitle();
  hist->GetXaxis()->SetTitle(xaxislabel);
  hist->GetYaxis()->SetTitle(yaxislabel);
  hist->GetZaxis()->SetTitle(zaxislabel);
  hist->GetXaxis()->SetTitleSize(0.038);
  hist->GetXaxis()->SetLabelSize(0.01);
  hist->GetYaxis()->SetTitleSize(0.038);
  hist->GetYaxis()->SetLabelSize(0.01);
  hist->GetZaxis()->SetTitleSize(0.025);
  hist->GetZaxis()->SetLabelSize(0.015);
  hist->GetZaxis()->SetTitleOffset(.75);
  hist->GetYaxis()->SetRangeUser(-10,120);
  hist->GetXaxis()->SetRangeUser(-5, 60);
  hist->Draw("COLZ");

  TGaxis *A1 = new TGaxis(7,7,48,7,Xstart, Xend,-510,"");
  A1->SetTitle("#mu");
  A1->SetLabelSize(0.015);
  A1->SetTitleSize(0.03);
  A1->SetTitleOffset(.85);
  A1->SetMaxDigits(6);
  A1->SetNdivisions(6);
  A1->Draw();

  TGaxis *A2 = new TGaxis(7,7,7,83,Ystart,Yend,-510,"");
  A2->SetTitle("#sigma");
  A2->SetLabelSize(0.015);
  A2->SetTitleSize(0.03);
  A2->SetTitleOffset(.85);
  A2->SetNdivisions(18);
  A2->Draw();

  TGaxis *A3 = new TGaxis(2,3,15,3,Xstart_small, Xend_small,-510, "");
  A3->SetTitle("#mu");
  A3->SetLabelSize(0.012);
  A3->SetTitleSize(0.025);
  A3->SetTitleOffset(.65);
  A3->SetNdivisions(5);
  A3->Draw();

  TGaxis *A4 = new TGaxis(2,3,2,30,Ystart_small, Yend_small, -510, "");
  A4->SetTitle("#sigma");
  A4->SetLabelSize(0.012);
  A4->SetTitleSize(0.025);
  A4->SetTitleOffset(.65);
  A4->SetNdivisions(5);
  A4->Draw();

  plot->AddHistoTitle(TotalTitle.c_str(), .035);
  plot->WritePreliminary("TL", .02, 0, 0, false);

  gPad->Update();
  can->Modified();
  can->Print(pdf);
  can->Clear();
  can->Closed();

}//end of 2D draw function
////////////////////////////////////////////////////////////////////////////////
//////
////////////////////////////////////////////////////////////////////////////////
void Draw2DHist(TH2D *hist,  char* xaxislabel, char* yaxislabel,char* zaxislabel,
                 char* Title,  char* pdf, TCanvas *can, MnvPlotter *plot)
{

  std::cout<<"inside this function"<< std::endl;
  string TotalTitle = string(Title);
  gStyle->SetPalette(kCool);

  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->CenterTitle();
  hist->GetXaxis()->SetTitle(xaxislabel);
  hist->GetYaxis()->SetTitle(yaxislabel);
  hist->GetZaxis()->SetTitle(zaxislabel);
  hist->GetXaxis()->SetTitleSize(0.038);
  hist->GetYaxis()->SetTitleSize(0.038);
  hist->GetZaxis()->SetTitleSize(0.035);
  hist->GetZaxis()->SetLabelSize(0.025);
  hist->GetZaxis()->SetTitleOffset(.7);
  //hist->SetMinimum(.0001);
  hist->GetXaxis()->SetTitleOffset(.95);
  hist->Draw("COLZ");

  plot->AddHistoTitle(TotalTitle.c_str(), .035);
  plot->WritePreliminary("TL", .035, 0, 0, false);

  gPad->Update();
  can->Modified();
  can->Print(pdf);
  can->Closed();


}//end of 2D draw function
////////////////////////////////////////////////////////////////////////////////
//////
////////////////////////////////////////////////////////////////////////////////
void DrawMnvH2D(MnvH2D *hist,  char* xaxislabel, char* yaxislabel,char* zaxislabel,
                 char* Title,  char* pdf, TCanvas *can, MnvPlotter *plot, bool setMiniumTrue)
{

  std::cout<<"inside this function"<< std::endl;
  string TotalTitle = string(Title);
  gStyle->SetPalette(kCool); //kGreenPink

  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->CenterTitle();
  hist->GetXaxis()->SetTitle(xaxislabel);
  hist->GetYaxis()->SetTitle(yaxislabel);
  hist->GetZaxis()->SetTitle(zaxislabel);
  hist->GetXaxis()->SetTitleSize(0.038);
  hist->GetYaxis()->SetTitleSize(0.038);
  hist->GetZaxis()->SetTitleSize(0.032);
  hist->GetZaxis()->SetLabelSize(0.015);
  hist->GetZaxis()->SetTitleOffset(.65);
  if(setMiniumTrue==true){hist->SetMinimum(.0001);}
  hist->GetXaxis()->SetTitleOffset(.95);
  hist->GetZaxis()->SetTitleOffset(.95);
  hist->Draw("COLZ");

  plot->AddHistoTitle(TotalTitle.c_str(), .035);
  plot->WritePreliminary("TL", .035, 0, 0, false);

  gPad->Update();
  can->Modified();
  can->Print(pdf);
  can->Closed();


}//end of 2D draw function
////////////////////////////////////////////////////////////////////////////////
//////
////////////////////////////////////////////////////////////////////////////////
void Draw2DHistFit(MnvH2D *hist, const char* xaxislabel,const char* yaxislabel,
                const char* Title, const char* pdf, TCanvas *can, MnvPlotter *plot)
{
  string TotalTitle = string(Title);
  gStyle->SetPalette(kCool);


  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->CenterTitle();
  hist->GetXaxis()->SetTitle(xaxislabel);
  hist->GetYaxis()->SetTitle(yaxislabel);
  hist->GetXaxis()->SetTitleSize(0.038);
  hist->GetYaxis()->SetTitleSize(0.038);
  hist->Draw("COLZ");

  plot->AddHistoTitle(TotalTitle.c_str(), .035);
  plot->WritePreliminary("TL", .035, 0, 0, false);

  gPad->Update();
  can->Modified();
  can->Print(pdf);
  can->Closed();


}//end of 2D draw function
////////////////////////////////////////////////////////////////////////////////
//////
////////////////////////////////////////////////////////////////////////////////

void Draw2DHist_withEllipse(MnvH2D *hist,  char* xaxislabel, char* yaxislabel, char* zaxislabel,
                 char* Title,  char* pdf, TCanvas *can, MnvPlotter *plot , double r1 , double r2)
{
  string TotalTitle = string(Title);
  gStyle->SetPalette(kGreenPink);


  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->CenterTitle();
  hist->GetXaxis()->SetTitle(xaxislabel);
  hist->GetYaxis()->SetTitle(yaxislabel);
  hist->GetZaxis()->SetTitle(zaxislabel);
  hist->GetXaxis()->SetTitleSize(0.038);
  hist->GetYaxis()->SetTitleSize(0.038);
  hist->GetZaxis()->SetTitleSize(0.035);
  hist->GetZaxis()->SetLabelSize(0.022);
  hist->GetZaxis()->SetTitleOffset(.5);
  hist->GetXaxis()->SetTitleOffset(1.05);
  hist->Draw("COLZ");
   TEllipse *el = new TEllipse(0,0,r1,r2);
   el->SetLineColor(4);
   el->SetLineWidth(6);
   el->SetFillStyle(0);
   el->Draw();


  plot->AddHistoTitle(TotalTitle.c_str(), .035);
  plot->WritePreliminary("TL", .035, 0, 0, false);

  gPad->Update();
  can->Modified();
  can->Print(pdf);
  can->Closed();


}//end of 2D draw function


////////////////////////////////////////////////////////////////////////////////
//////
////////////////////////////////////////////////////////////////////////////////

void Draw2DHist_TFILE(TFile *inputFile, const char* histoName, const char *Title,
   const char* xaxislabel,const char* yaxislabel,
  const char* pdf, TCanvas *can, MnvPlotter *plot, bool PrintText)
  {
    gStyle->SetPalette(kBird);
    std::cout<<"trying 2D HisName  = "<< histoName<<std::endl;

    MnvH2D *hist = (MnvH2D*)inputFile -> Get(histoName);
    MnvH2D *histrowcol = (MnvH2D*)inputFile -> Get(histoName);
    colNormalize(*histrowcol);

    MnvH2D *histrownom = (MnvH2D*)inputFile -> Get(histoName);
    rowNormalize(*histrownom);
    std::string TotalTitle = string(Title);
    std::string TotalTitle_RowNorm = TotalTitle + " [RowNorm]";
    std::string TotalTitle_ColNorm = TotalTitle + " [ColNorm]";

    hist->Draw("COLZ");
    hist->GetXaxis()->CenterTitle();
    hist->GetYaxis()->CenterTitle();
    hist->GetXaxis()->SetTitle(xaxislabel);
    hist->GetYaxis()->SetTitle(yaxislabel);
    hist->GetXaxis()->SetTitleSize(0.038);
    hist->GetYaxis()->SetTitleSize(0.038);

    plot->AddHistoTitle(TotalTitle.c_str(), .04);
    plot->WritePreliminary("TL", .035, 0, 0, false);

    gPad->Update();
    can->Modified();
    can->Print(pdf);

    if(PrintText==false){
      histrownom->Draw("COLZ");
      histrownom->GetXaxis()->CenterTitle();
      histrownom->GetYaxis()->CenterTitle();
      histrownom->GetXaxis()->SetTitle(xaxislabel);
      histrownom->GetYaxis()->SetTitle(yaxislabel);
      histrownom->GetXaxis()->SetTitleSize(0.038);
      histrownom->GetYaxis()->SetTitleSize(0.038);

      plot->AddHistoTitle(TotalTitle_RowNorm.c_str(), .04);
      plot->WritePreliminary("TL", .035, 0, 0, false);

      gPad->Update();
      can->Modified();
      can->Print(pdf);
      //////////////

      histrowcol->Draw("COLZ");
      histrowcol->GetXaxis()->CenterTitle();
      histrowcol->GetYaxis()->CenterTitle();
      histrowcol->GetXaxis()->SetTitle(xaxislabel);
      histrowcol->GetYaxis()->SetTitle(yaxislabel);
      histrowcol->GetXaxis()->SetTitleSize(0.038);
      histrowcol->GetYaxis()->SetTitleSize(0.038);

      plot->AddHistoTitle(TotalTitle_ColNorm.c_str(), .04);
      plot->WritePreliminary("TL", .035, 0, 0, false);

      gPad->Update();
      can->Modified();
      can->Print(pdf);
    }


    else if(PrintText==true){

      DrawMagration_heatMap(hist, xaxislabel, yaxislabel, Title, pdf,can, plot );
      char TotalTitle_RowNorm_char_array[TotalTitle_RowNorm.length() + 1];
      strcpy(TotalTitle_RowNorm_char_array, TotalTitle_RowNorm.c_str());
      DrawMagration_heatMap(histrownom, xaxislabel, yaxislabel, TotalTitle_RowNorm_char_array, pdf,can, plot );

      char TotalTitle_ColNorm_char_array[TotalTitle_ColNorm.length() + 1];
      strcpy(TotalTitle_ColNorm_char_array, TotalTitle_ColNorm.c_str());
      DrawMagration_heatMap(histrowcol, xaxislabel, yaxislabel, TotalTitle_ColNorm_char_array, pdf,can, plot );
    }

    can->Closed();


  }//end of 2D draw function


  ////////////////////////////////////////////////////
  //////
  ////////////////////////////////////////////////////

void Draw2DHist_hist(MnvH2D *hist_input, const char *Title, const char* xaxislabel,
  const char* yaxislabel, const char* pdf, TCanvas *can, MnvPlotter *plot)
  {

  gStyle->SetPalette(kBird);
    MnvH2D *hist = (PlotUtils::MnvH2D*)hist_input->Clone("hist");
    MnvH2D *histrownom = (PlotUtils::MnvH2D*)hist_input->Clone("histrownom");
    MnvH2D *histrowcol = (PlotUtils::MnvH2D*)hist_input->Clone("histrowcol");

    colNormalize(*histrowcol);
    rowNormalize(*histrownom);
    string TotalTitle = string(Title);

    hist->Draw("COLZ");
    hist->GetXaxis()->CenterTitle();
    hist->GetYaxis()->CenterTitle();
    hist->GetXaxis()->SetTitle(xaxislabel);
    hist->GetYaxis()->SetTitle(yaxislabel);
    hist->GetXaxis()->SetTitleSize(0.038);
    hist->GetYaxis()->SetTitleSize(0.038);

    plot->AddHistoTitle(TotalTitle.c_str(), .04);
    plot->WritePreliminary("TL", .035, 0, 0, false);

    gPad->Update();
    can->Modified();
    can->Print(pdf);

    histrownom->Draw("COLZ");
    histrownom->GetXaxis()->CenterTitle();
    histrownom->GetYaxis()->CenterTitle();
    histrownom->GetXaxis()->SetTitle(xaxislabel);
    histrownom->GetYaxis()->SetTitle(yaxislabel);
    histrownom->GetZaxis()->SetTitle( "Row Normalize" );
    histrownom->GetXaxis()->SetTitleSize(0.038);
    histrownom->GetYaxis()->SetTitleSize(0.038);

    plot->AddHistoTitle(TotalTitle.c_str(), .04);
    plot->WritePreliminary("TL", .035, 0, 0, false);

    gPad->Update();
    can->Modified();
    can->Print(pdf);


    histrowcol->Draw("COLZ");
    histrowcol->GetXaxis()->CenterTitle();
    histrowcol->GetYaxis()->CenterTitle();
    histrowcol->GetXaxis()->SetTitle(xaxislabel);
    histrowcol->GetYaxis()->SetTitle(yaxislabel);
    histrowcol->GetZaxis()->SetTitle( "Column Normalize" );
    histrowcol->GetXaxis()->SetTitleSize(0.038);
    histrowcol->GetYaxis()->SetTitleSize(0.038);

    plot->AddHistoTitle(TotalTitle.c_str(), .04);
    plot->WritePreliminary("TL", .035, 0, 0, false);

    gPad->Update();
    can->Modified();
    can->Print(pdf);

    DrawMagration_heatMap(hist, xaxislabel, yaxislabel, Title, pdf,can, plot );
    DrawMagration_heatMap(histrownom, xaxislabel, yaxislabel, Title, pdf,can, plot );
    DrawMagration_heatMap(histrowcol, xaxislabel, yaxislabel, Title, pdf,can, plot );


    can->Closed();




  }//end of 2D draw function

  ////////////////////////////////////////////////////
  //////
  ////////////////////////////////////////////////////

void Draw2DHist_hist_notext(MnvH2D *hist_input, const char *Title, const char* xaxislabel,const char* yaxislabel,
         const char* pdf, TCanvas *can, MnvPlotter *plot, bool includeFlows)
{

  MnvH2D *hist = (PlotUtils::MnvH2D*)hist_input->Clone("hist");
  MnvH2D *histrownom = (PlotUtils::MnvH2D*)hist_input->Clone("histrownom");
  MnvH2D *histrowcol = (PlotUtils::MnvH2D*)hist_input->Clone("histrowcol");

  colNormalize(*histrowcol);
  rowNormalize(*histrownom);
  string TotalTitle = string(Title);
  char hist_Title[1024];

  DrawMagration_heatMap_noText(hist, xaxislabel, yaxislabel,
    Title, pdf, can, plot, includeFlows );

  sprintf(hist_Title, "%s [RowNorm]");
  DrawMagration_heatMap_noText(histrownom, xaxislabel, yaxislabel,
  Title, pdf, can, plot, includeFlows );

  sprintf(hist_Title, "%s [ColNorm]");
  DrawMagration_heatMap_noText(histrowcol, xaxislabel, yaxislabel,
  Title, pdf, can, plot, includeFlows );

  can->Closed();




}//end of 2D draw function

///////////////////
///
///////////////////

void Draw2DHist_Migration_TFILE(TFile *inputFile, const char* histoName,
  const char *Title, const char* xaxislabel,const char* yaxislabel,
  const char* pdf_label, TCanvas *can, MnvPlotter *plot, bool PrintText)
  {
    gStyle->SetPalette(kCool);
    gStyle->SetPaintTextFormat("g");
    gStyle->SetPaintTextFormat("2.0f");
    bool includeFlows = true;

    std::cout<<"trying 2D HisName  = "<< histoName<<std::endl;
    char pdf[1024];
    sprintf(pdf,"%s.pdf",pdf_label);

    MnvH2D *hist = (MnvH2D*)inputFile -> Get(histoName);
    MnvH2D *histrowcol = (MnvH2D*)inputFile -> Get(histoName);
    colNormalize(*histrowcol);

    MnvH2D *histrownom = (MnvH2D*)inputFile -> Get(histoName);
    rowNormalize(*histrownom);

    TH2D *hist_byBinN = ReturnTH2D_Migration_SingleCellBins(histrownom, includeFlows);

    Int_t nbins = includeFlows ? hist_byBinN->GetNbinsX()+2 : hist_byBinN->GetNbinsX();
    std::string TotalTitle = string(Title);
    std::string TotalTitle_RowNorm = TotalTitle + " [RowNorm]";
    std::string TotalTitle_ColNorm = TotalTitle + " [ColNorm]";

    TH2D * hist_pop = ReturnTH2D_Migration_removeZeros(hist, includeFlows);
    SetUpMigration(*hist_pop,  includeFlows, .5, xaxislabel, yaxislabel, "Population in cell");
    hist_pop->Draw("COLZ TEXT");

    plot->AddHistoTitle(TotalTitle.c_str(), .04);
    plot->WritePreliminary("TL", .035, 0, 0, false);

    gPad->Update();
    can->Modified();
    can->Print(pdf);

    if(PrintText==false){
      gStyle->SetPaintTextFormat("2.2f");
      TH2D *histrownom_clean = ReturnTH2D_Migration_removeZeros(histrownom, includeFlows);
      SetUpMigration(*histrownom_clean,  includeFlows, .42, xaxislabel, yaxislabel, "Fraction of Row in Cell");
      histrownom_clean->Draw("COLZ TEXT");
      plot->AddHistoTitle(TotalTitle_RowNorm.c_str(), .04);
      plot->WritePreliminary("TL", .035, 0, 0, false);
      gPad->Update();
      can->Modified();
      can->Print(pdf);
      ////////////////
      TH2D *histrowcol_clean = ReturnTH2D_Migration_removeZeros(histrowcol, includeFlows);
      SetUpMigration(*histrowcol_clean,  includeFlows, .42, xaxislabel, yaxislabel, "Fraction of Col in Cell");
      histrowcol_clean->Draw("COLZ TEXT");

      plot->AddHistoTitle(TotalTitle_ColNorm.c_str(), .04);
      plot->WritePreliminary("TL", .035, 0, 0, false);

      gPad->Update();
      can->Modified();
      can->Print(pdf);

      SetUpMigration_BybinN(*hist_byBinN, includeFlows, .55, "Fraction of Row in Cell");
      hist_byBinN->Draw("COLZ TEXT");

      plot->AddHistoTitle(TotalTitle.c_str(), .04);
      plot->WritePreliminary("TL", .035, 0, 0, false);
      gPad->Update();
      can->Modified();
      can->Print(pdf);
    }
    else if(PrintText==true){

      DrawMagration_heatMap(hist, xaxislabel, yaxislabel, Title, pdf,can, plot, true );
      char TotalTitle_RowNorm_char_array[TotalTitle_RowNorm.length() + 1];
      strcpy(TotalTitle_RowNorm_char_array, TotalTitle_RowNorm.c_str());
      DrawMagration_heatMap(histrownom, xaxislabel, yaxislabel, TotalTitle_RowNorm_char_array, pdf,can, plot, true );

      char TotalTitle_ColNorm_char_array[TotalTitle_ColNorm.length() + 1];
      strcpy(TotalTitle_ColNorm_char_array, TotalTitle_ColNorm.c_str());
      DrawMagration_heatMap(histrowcol, xaxislabel, yaxislabel, TotalTitle_ColNorm_char_array, pdf,can, plot, true );
    }

    can->Closed();


  }//end of 2D draw function

  ////////////////////////////////////////////////////
  //////
  ////////////////////////////////////////////////////

  void Draw2DHist_Migration_TFILE_FULL_EMPTY(TFile *inputFile_FULL,
                                             TFile *inputFile_EMPTY, double MCscale,
     const char* histoName, const char *Title, const char* xaxislabel,const char* yaxislabel,
    const char* pdf_label, TCanvas *can, MnvPlotter *plot, bool PrintText)
    {
      gStyle->SetPalette(kCool);
      gStyle->SetPaintTextFormat("g");
      gStyle->SetPaintTextFormat("2.0f");
      bool includeFlows = true;
      std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;
      std::cout<<"Inside: ~~~~Draw2DHist_Migration_TFILE_FULL_EMPTY~~~"<< std::endl;
      std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;

      std::cout<<"trying 2D HisName  = "<< histoName <<std::endl;
      char pdf[1024];
      sprintf(pdf,"%s.pdf",pdf_label);
      bool isFull = true;
      bool isEmpty = false;

      MnvH2D *hist = Get2DHist(*inputFile_FULL, histoName, isFull);
      MnvH2D *histcolnom = (PlotUtils::MnvH2D*)hist->Clone("histcolnom");
      MnvH2D *histrownom = (PlotUtils::MnvH2D*)hist->Clone("histrownom");

      MnvH2D *hist_FULL_EMPTY =  (PlotUtils::MnvH2D*)hist->Clone("hist_FULL_EMPTY");
      MnvH2D *histrownom_FULL_EMPTY = (PlotUtils::MnvH2D*)hist->Clone("histrownom_FULL_EMPTY");
      MnvH2D *histcolnom_FULL_EMPTY = (PlotUtils::MnvH2D*)hist->Clone("histcolnom_FULL_EMPTY");

      MnvH2D *hist_EMPTY = Get2DHist(*inputFile_EMPTY, histoName, isEmpty);
      MnvH2D *histcolnom_EMPTY = (PlotUtils::MnvH2D*)hist_EMPTY->Clone("histcolnom_EMPTY");
      MnvH2D *histrownom_EMPTY = (PlotUtils::MnvH2D*)hist_EMPTY->Clone("histrownom_EMPTY");

      hist_EMPTY->Scale(MCscale);
      histcolnom_EMPTY->Scale(MCscale);
      histrownom_EMPTY->Scale(MCscale);

      hist_FULL_EMPTY->Add(hist_EMPTY,-1);
      histrownom_FULL_EMPTY->Add(histrownom_EMPTY,-1);
      histcolnom_FULL_EMPTY->Add(histcolnom_EMPTY,-1);

      colNormalize_Mig(*histcolnom,includeFlows);
      colNormalize_Mig(*histcolnom_EMPTY,includeFlows);
      colNormalize_Mig(*histcolnom_FULL_EMPTY,includeFlows);

      rowNormalize_Mig(*histrownom,includeFlows);
      rowNormalize_Mig(*histrownom_EMPTY,includeFlows);
      rowNormalize_Mig(*histrownom_FULL_EMPTY,includeFlows);

      TH2D *hist_byBinN = ReturnTH2D_Migration_SingleCellBins(histrownom, includeFlows);
      TH2D *hist_byBinN_EMPTY = ReturnTH2D_Migration_SingleCellBins(histrownom_EMPTY, includeFlows);
      TH2D *hist_byBinN_FULL_EMPTY = ReturnTH2D_Migration_SingleCellBins(histrownom_FULL_EMPTY, includeFlows);



      Int_t nbins = includeFlows ? hist_byBinN->GetNbinsX()+2 : hist_byBinN->GetNbinsX();

      std::string TotalTitle = string(Title);
      std::string TotalTitle_FULL = TotalTitle + "[Full]";
      std::string TotalTitle_EMPTY = TotalTitle + "[EMPTY]";
      std::string TotalTitle_FULL_EMPTY = TotalTitle + "[F-E]";
      std::string TotalTitle_RowNorm = TotalTitle + " [Full] [RowNorm]";
      std::string TotalTitle_ColNorm = TotalTitle + " [Full] [ColNorm]";

      std::string TotalTitle_RowNorm_EMPTY = TotalTitle + "[EMPTY] [RowNorm]";
      std::string TotalTitle_ColNorm_EMPTY = TotalTitle + "[EMPTY] [ColNorm]";

      std::string TotalTitle_RowNorm_FULL_EMPTY = TotalTitle + "[F-E] [RowNorm]";
      std::string TotalTitle_ColNorm_FULL_EMPTY = TotalTitle + "[F-E] [ColNorm]";


      TH2D *hist_pop = ReturnTH2D_Migration_removeZeros(hist, includeFlows);
      SetUpMigration(*hist_pop,  includeFlows, .35, xaxislabel, yaxislabel, "Population in cell");
      hist_pop->Draw("COLZ TEXT");
      plot->AddHistoTitle(TotalTitle_FULL.c_str(), .04);
      plot->WritePreliminary("TL", .035, 0, 0, false);
      gPad->Update();
      can->Modified();
      can->Print(pdf);
      /////////////
      TH2D * hist_pop_EMPTY = ReturnTH2D_Migration_removeZeros(hist_EMPTY, includeFlows);
      SetUpMigration(*hist_pop_EMPTY,  includeFlows, .35, xaxislabel, yaxislabel, "Population in cell");
      hist_pop_EMPTY->Draw("COLZ TEXT");
      plot->AddHistoTitle(TotalTitle_EMPTY.c_str(), .04);
      plot->WritePreliminary("TL", .035, 0, 0, false);

      gPad->Update();
      can->Modified();
      can->Print(pdf);
      ////////////////////////////
      SetUpMigration(*hist_FULL_EMPTY,  includeFlows, .35, xaxislabel, yaxislabel, "Population in cell");
      hist_FULL_EMPTY->Draw("COLZ TEXT");
      plot->AddHistoTitle(TotalTitle_FULL_EMPTY.c_str(), .04);
      plot->WritePreliminary("TL", .035, 0, 0, false);
      gPad->Update();
      can->Modified();
      can->Print(pdf);



      TH2D * hist_pop_FULL_EMPTY = ReturnTH2D_Migration_removeZeros(hist_FULL_EMPTY, includeFlows);
      SetUpMigration(*hist_pop_FULL_EMPTY,  includeFlows, .35, xaxislabel, yaxislabel, "Population in cell");
      hist_pop_FULL_EMPTY->Draw("COLZ TEXT");
      plot->AddHistoTitle(TotalTitle_FULL_EMPTY.c_str(), .04);
      plot->WritePreliminary("TL", .035, 0, 0, false);
      gPad->Update();
      can->Modified();
      can->Print(pdf);

      TH2D *hist_byBinN_FULL_EMPTY_pop = ReturnTH2D_Migration_SingleCellBins(hist_FULL_EMPTY, includeFlows);
      SetUpMigration(*hist_byBinN_FULL_EMPTY_pop,  includeFlows, .35, xaxislabel, yaxislabel, "Population in cell");
      hist_pop_FULL_EMPTY->Draw("COLZ TEXT");
      plot->AddHistoTitle(TotalTitle_FULL_EMPTY.c_str(), .04);
      plot->WritePreliminary("TL", .035, 0, 0, false);

      gPad->Update();
      can->Modified();
      can->Print(pdf);





      if(PrintText==false){
        std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;
        std::cout<<"~~~~~~~ doing FUll, Empty , and full - empty ~~~~~~~~~~~~~"<< std::endl;
        std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;
        //////////
        ///FULL
        /////////
        gStyle->SetPaintTextFormat("2.2f");
        TH2D *histrownom_clean = ReturnTH2D_Migration_removeZeros(histrownom, includeFlows);
        SetUpMigration(*histrownom_clean,  includeFlows, .4, xaxislabel, yaxislabel, "Fraction of Row in Cell");
        histrownom_clean->Draw("COLZ TEXT");
        plot->AddHistoTitle(TotalTitle_RowNorm.c_str(), .04);
        plot->WritePreliminary("TL", .035, 0, 0, false);
        gPad->Update();
        can->Modified();
        can->Print(pdf);
        ////////////////

        TH2D *histcolnom_clean = ReturnTH2D_Migration_removeZeros(histcolnom, includeFlows);
        SetUpMigration(*histcolnom_clean,  includeFlows, .4, xaxislabel, yaxislabel, "Fraction of Col in Cell");
        histcolnom_clean->Draw("COLZ TEXT");
        plot->AddHistoTitle(TotalTitle_ColNorm.c_str(), .04);
        plot->WritePreliminary("TL", .035, 0, 0, false);

        gPad->Update();
        can->Modified();
        can->Print(pdf);

        SetUpMigration_BybinN(*hist_byBinN, includeFlows, .4, "Fraction of Row in Cell");
        hist_byBinN->Draw("COLZ TEXT");
        plot->AddHistoTitle(TotalTitle.c_str(), .04);
        plot->WritePreliminary("TL", .035, 0, 0, false);
        gPad->Update();
        can->Modified();
        can->Print(pdf);
        //////////
        ///EMPTY
        /////////
        TH2D *histrownom_clean_EMPTY = ReturnTH2D_Migration_removeZeros(histrownom_EMPTY, includeFlows);
        SetUpMigration(*histrownom_clean_EMPTY,  includeFlows, .42, xaxislabel, yaxislabel, "Fraction of Row in Cell");
        histrownom_clean_EMPTY->Draw("COLZ TEXT");
        plot->AddHistoTitle(TotalTitle_RowNorm_EMPTY.c_str(), .04);
        plot->WritePreliminary("TL", .035, 0, 0, false);
        gPad->Update();
        can->Modified();
        can->Print(pdf);
        ////////////////
        TH2D *histcolnom_clean_EMPTY = ReturnTH2D_Migration_removeZeros(histcolnom_EMPTY, includeFlows);
        SetUpMigration(*histcolnom_clean_EMPTY,  includeFlows, .42, xaxislabel, yaxislabel, "Fraction of Col in Cell");
        histcolnom_clean_EMPTY->Draw("COLZ TEXT");
        plot->AddHistoTitle(TotalTitle_ColNorm_EMPTY.c_str(), .04);
        plot->WritePreliminary("TL", .035, 0, 0, false);
        gPad->Update();
        can->Modified();
        can->Print(pdf);

        SetUpMigration_BybinN(*hist_byBinN_EMPTY, includeFlows, .4, "Fraction of Row in Cell");
        hist_byBinN_EMPTY->Draw("COLZ TEXT");

        plot->AddHistoTitle(TotalTitle_EMPTY.c_str(), .04);
        plot->WritePreliminary("TL", .035, 0, 0, false);
        gPad->Update();
        can->Modified();
        can->Print(pdf);

        //////////
        ///Full - EMPTY
        /////////

        TH2D *histrownom_clean_FULL_EMPTY = ReturnTH2D_Migration_removeZeros(histrownom_FULL_EMPTY, includeFlows);
        SetUpMigration(*histrownom_clean_FULL_EMPTY,  includeFlows, .4, xaxislabel, yaxislabel, "Fraction of Row in Cell");
        histrownom_clean_FULL_EMPTY->Draw("COLZ TEXT");
        plot->AddHistoTitle(TotalTitle_RowNorm_FULL_EMPTY.c_str(), .04);
        plot->WritePreliminary("TL", .035, 0, 0, false);
        gPad->Update();
        can->Modified();
        can->Print(pdf);

        ////////////////
        TH2D *histcolnom_clean_FULL_EMPTY = ReturnTH2D_Migration_removeZeros(histcolnom_FULL_EMPTY, includeFlows);
        SetUpMigration(*histcolnom_clean_FULL_EMPTY,  includeFlows, .4, xaxislabel, yaxislabel, "Fraction of Col in Cell");
        histcolnom_clean_FULL_EMPTY->Draw("COLZ TEXT");
        plot->AddHistoTitle(TotalTitle_ColNorm.c_str(), .04);
        plot->WritePreliminary("TL", .035, 0, 0, false);

        gPad->Update();
        can->Modified();
        can->Print(pdf);

        SetUpMigration_BybinN(*hist_byBinN_FULL_EMPTY, includeFlows, .42, "Fraction of Row in Cell");
        hist_byBinN_FULL_EMPTY->Draw("COLZ TEXT");
        plot->AddHistoTitle(TotalTitle_FULL_EMPTY.c_str(), .04);
        plot->WritePreliminary("TL", .035, 0, 0, false);
        gPad->Update();
        can->Modified();
        can->Print(pdf);


      }
      else if(PrintText==true){

        DrawMagration_heatMap(hist, xaxislabel, yaxislabel, Title, pdf,can, plot, true );
        char TotalTitle_RowNorm_char_array[TotalTitle_RowNorm.length() + 1];
        strcpy(TotalTitle_RowNorm_char_array, TotalTitle_RowNorm.c_str());
        DrawMagration_heatMap(histrownom, xaxislabel, yaxislabel, TotalTitle_RowNorm_char_array, pdf,can, plot, true );

        char TotalTitle_ColNorm_char_array[TotalTitle_ColNorm.length() + 1];
        strcpy(TotalTitle_ColNorm_char_array, TotalTitle_ColNorm.c_str());
        DrawMagration_heatMap(histcolnom, xaxislabel, yaxislabel, TotalTitle_ColNorm_char_array, pdf,can, plot, true );
      }

      can->Closed();


    }//end of 2D draw function

    ////////////////////////////////////////////////////
    //////
    ////////////////////////////////////////////////////

void Draw2DHist_Migration_Histpointer(MnvH2D *hist, const char *Title,
     const char* xaxislabel, const char* yaxislabel,  const char *zaxislabel,
  const char* pdf_label, TCanvas *can, MnvPlotter *plot )
  {
    gStyle->SetPalette(kCool);
    //TColor::InvertPalette();
    gStyle->SetPaintTextFormat("g");
    gStyle->SetPaintTextFormat("2.3f");
    bool includeFlows = true;

    char pdf[1024];
    sprintf(pdf,"%s.pdf",pdf_label);

    std::string TotalTitle = string(Title);

    TH2D * hist_pop = ReturnTH2D_Migration_removeZeros(hist, includeFlows);
    SetUpMigration(*hist_pop,  includeFlows, .6, xaxislabel, yaxislabel, zaxislabel);
    hist_pop->Draw("COLZ TEXT");

    plot->AddHistoTitle(TotalTitle.c_str(), .04);
    plot->WritePreliminary("TL", .035, 0, 0, false);

    gPad->Update();
    can->Modified();
    can->Print(pdf);
    can->Closed();


  }//end o

  void Draw2DHist_Migration_Histpointer(MnvH2D *hist, std::string Title_string,
       std::string xaxislabel_string, std::string yaxislabel_string,  std::string zaxislabel_string,
    std::string pdf_label_string, TCanvas *can, MnvPlotter *plot)
    {
      const char* pdf_label = pdf_label_string.c_str();
      const char* xaxislabel = xaxislabel_string.c_str();
      const char* yaxislabel = yaxislabel_string.c_str();
      const char* zaxislabel = zaxislabel_string.c_str();
      const char* Title = Title_string.c_str();

      Draw2DHist_Migration_Histpointer(hist, Title,
          xaxislabel, yaxislabel,  zaxislabel,
    pdf_label, can, plot);

    }//end o
  ////////////////////////////////////////////////////
  //////
  ////////////////////////////////////////////////////

  void Draw2DHist_HistpointernoText(MnvH2D *hist, const char *Title,
       const char* xaxislabel, const char* yaxislabel,  const char *zaxislabel,
    const char* pdf_label, TCanvas *can, MnvPlotter *plot)
    {
      gStyle->SetPalette(kCool);
      bool includeFlows = true;

      char pdf[1024];
      sprintf(pdf,"%s.pdf",pdf_label);

      std::string TotalTitle = string(Title);

      TH2D * hist_pop = ReturnTH2D_removeZeros(hist, includeFlows);
      SetUpMigration(*hist_pop,  includeFlows, .4, xaxislabel, yaxislabel, zaxislabel);
      hist_pop->Draw("COLZ");

      plot->AddHistoTitle(TotalTitle.c_str(), .04);
      plot->WritePreliminary("TL", .035, 0, 0, false);

      gPad->Update();
      can->Modified();
      can->Print(pdf);
      can->Closed();


    }//end o

    ////////////////////////////////////////////////////
    //////
    ////////////////////////////////////////////////////

  void SetUpMigration_BybinN(TH2D &hist, bool includeFlows, double markersize, const char*Ztitle){

    Int_t nbins = includeFlows ? hist.GetNbinsX()+2 : hist.GetNbinsX();
    hist.SetMarkerSize(markersize);
    hist.GetXaxis()->CenterTitle();
    hist.GetYaxis()->CenterTitle();
    hist.GetZaxis()->CenterTitle();
    hist.GetXaxis()->SetTitle("RECO Bins");
    hist.GetYaxis()->SetTitle("TRUE Bins");
    hist.GetXaxis()->SetTitleSize(0.038);
    hist.GetYaxis()->SetTitleSize(0.038);
    hist.GetZaxis()->SetLabelSize(0.035);
    hist.GetZaxis()->SetTitleSize(0.035);
    hist.GetZaxis()->SetTitle( Ztitle );
    hist.GetXaxis()->SetNdivisions(nbins, kTRUE);
    hist.GetYaxis()->SetNdivisions(nbins, kTRUE);
    hist.GetYaxis()->SetLabelSize(0.02);
    hist.GetXaxis()->SetLabelSize(0.02);
    hist.GetZaxis()->SetLabelSize(0.02);
    hist.GetZaxis()->SetTitleOffset(.7);
    hist.SetMinimum(.001);
    hist.SetMarkerColor(kBlack);
  }

  ////////////////////////////////////////////////////
  //////
  ////////////////////////////////////////////////////

  void SetUpMigration_BybinN(MnvH2D &hist, bool includeFlows, double markersize, const char*Ztitle){

    Int_t nbins = includeFlows ? hist.GetNbinsX()+2 : hist.GetNbinsX();
    hist.SetMarkerSize(markersize);
    hist.GetXaxis()->CenterTitle();
    hist.GetYaxis()->CenterTitle();
    hist.GetZaxis()->CenterTitle();
    hist.GetXaxis()->SetTitle("RECO Bins");
    hist.GetYaxis()->SetTitle("TRUE Bins");
    hist.GetXaxis()->SetTitleSize(0.038);
    hist.GetYaxis()->SetTitleSize(0.038);
    hist.GetZaxis()->SetLabelSize(0.035);
    hist.GetZaxis()->SetTitleSize(0.035);
    hist.GetZaxis()->SetTitle( Ztitle );
    hist.GetXaxis()->SetNdivisions(nbins, kTRUE);
    hist.GetYaxis()->SetNdivisions(nbins, kTRUE);
    hist.GetYaxis()->SetLabelSize(0.02);
    hist.GetXaxis()->SetLabelSize(0.02);
    hist.GetZaxis()->SetLabelSize(0.025);
    hist.GetZaxis()->SetTitleOffset(1.0);
    hist.SetMinimum(.01);
    hist.SetMarkerColor(kBlack);
  }

  ////////////////////////////////////////////////////
  //////
  ////////////////////////////////////////////////////

  void SetUpMigration(TH2D &hist, bool includeFlows, double markersize, const char*Xaxis, const char*Yaxis, const char*Ztitle){

    hist.SetMarkerSize(markersize);
    hist.GetXaxis()->CenterTitle();
    hist.GetYaxis()->CenterTitle();
    hist.GetZaxis()->CenterTitle();
    hist.GetXaxis()->SetTitle(Xaxis);
    hist.GetYaxis()->SetTitle(Yaxis);
    hist.GetXaxis()->SetTitleSize(0.04);
    hist.GetXaxis()->SetTitleOffset(.9);
    hist.GetYaxis()->SetTitleSize(0.04);
    hist.GetYaxis()->SetTitleOffset(.9);
    hist.GetZaxis()->SetLabelSize(0.035);
    hist.GetZaxis()->SetTitleSize(0.035);
    hist.GetZaxis()->SetTitle( Ztitle );
    hist.GetYaxis()->SetLabelSize(0.02);
    hist.GetXaxis()->SetLabelSize(0.02);
    hist.GetZaxis()->SetLabelSize(0.015);
    hist.GetZaxis()->SetTitleOffset(.7);
    hist.SetMinimum(.001);
    hist.SetMarkerColor(kBlack);
  }

  ////////////////////////////////////////////////////
  //////
  ////////////////////////////////////////////////////

  void SetUpMigration(MnvH2D &hist, bool includeFlows, double markersize, const char*Xaxis, const char*Yaxis, const char*Ztitle){

    hist.SetMarkerSize(markersize);
    hist.GetXaxis()->CenterTitle();
    hist.GetYaxis()->CenterTitle();
    hist.GetZaxis()->CenterTitle();
    hist.GetXaxis()->SetTitle(Xaxis);
    hist.GetYaxis()->SetTitle(Yaxis);
    hist.GetXaxis()->SetTitleSize(0.038);
    hist.GetYaxis()->SetTitleSize(0.038);
    hist.GetZaxis()->SetLabelSize(0.035);
    hist.GetZaxis()->SetTitleSize(0.035);
    hist.GetZaxis()->SetTitle( Ztitle );
    hist.GetYaxis()->SetLabelSize(0.02);
    hist.GetXaxis()->SetLabelSize(0.02);
    hist.GetZaxis()->SetLabelSize(0.025);
    hist.GetZaxis()->SetTitleOffset(1.0);
    //hist.SetMinimum(.0001);
    hist.SetMarkerColor(kBlack);
  }

  ////////////////////////////////////////////////////
  //////
  ////////////////////////////////////////////////////

  void Draw_TGraphs_fitParams(std::vector<GaussianFitsParms> GaussianFits_values_Resolution_vector,
      const char* pdf_label, char *histotitle, TCanvas *cE, MnvPlotter *mnvPlotter, bool Xlog ,bool Ylog)
  {

    std::string TotalTitle = string(histotitle);
    std::vector<double> X_axis_CutValue;
    std::vector<double> Y_axis_TotalN;
    std::vector<double> Y_axis_Sigma;
    std::vector<double> Y_axis_Sigma_Error;
    std::vector<double> Y_axis_Mean;
    std::vector<double> Y_axis_Mean_Error;


    for(auto fit_params : GaussianFits_values_Resolution_vector){
      X_axis_CutValue.push_back(fit_params.CutValue);
      Y_axis_TotalN.push_back(fit_params.TotalN);
      Y_axis_Sigma.push_back(fit_params.Sigma);
      Y_axis_Sigma_Error.push_back(fit_params.Sigma_Error);
      Y_axis_Mean.push_back(fit_params.Mean);
      Y_axis_Mean_Error.push_back(fit_params.Mean_Error);
    }

      TGraphErrors  *TG_TotalN = MakeTGraph_from_Vectors(Y_axis_TotalN,  X_axis_CutValue);
      TGraphErrors  *TG_Sigma = MakeTGraph_from_VectorsErrors(Y_axis_Sigma,Y_axis_Sigma_Error,  X_axis_CutValue);
      TGraphErrors  *TG_Mean = MakeTGraph_from_VectorsErrors(Y_axis_Mean, Y_axis_Mean_Error,  X_axis_CutValue);

  // need pdf format

      DrawTGraph(TG_TotalN,"Fiducial Cut to Edge [mm]","NEvnets", "NEvents Pass Fiducial Cut", "Nevents",pdf_label, cE, mnvPlotter, Xlog, Ylog );

      DrawTGraph(TG_Sigma,"Fiducial Cut to Edge [mm]","Sigma Gaussian Fits", "Change in #sigma Gaussian Fits Fiducial Cut", "#sigma",pdf_label, cE, mnvPlotter, Xlog, Ylog );

      DrawTGraph(TG_Mean,"Fiducial Cut to Edge [mm]","Mean ", "Change in mean Gaussian Fits as Fiducial Cut", "mean",  pdf_label, cE, mnvPlotter, Xlog, Ylog );



  }

  ////////////////////////////////////////////////////
  //////
  ////////////////////////////////////////////////////

  void Draw_TGraphs_fitParams(std::vector<GaussianFitsParms> GaussianFits_helium,
                           std::vector<GaussianFitsParms> GaussianFits_nonhelium,
                               std::vector<GaussianFitsParms> GaussianFits_total,
    const char* pdf_label, char *histotitle, TCanvas *cE, MnvPlotter *mnvPlotter,
    bool Xlog ,bool Ylog , bool setGrid , char *Playlist)
  {

  if(GaussianFits_helium.size() != GaussianFits_nonhelium.size() || GaussianFits_nonhelium.size()!= GaussianFits_total.size()){std::cout<<"Vectors for Draw_TGraphs_fitParams are not same size ERROR "<< std::endl; assert(false);}

    std::string TotalTitle = string(histotitle);
    std::vector<double> X_axis_CutValue_Helium;
    std::vector<double> Y_axis_TotalN_Helium;
    std::vector<double> Y_axis_Sigma_Helium;
    std::vector<double> Y_axis_Sigma_Error_Helium;
    std::vector<double> Y_axis_Mean_Helium;
    std::vector<double> Y_axis_Mean_Error_Helium;

    std::vector<double> X_axis_CutValue_nonHelium;
    std::vector<double> Y_axis_TotalN_nonHelium;
    std::vector<double> Y_axis_Sigma_nonHelium;
    std::vector<double> Y_axis_Sigma_Error_nonHelium;
    std::vector<double> Y_axis_Mean_nonHelium;
    std::vector<double> Y_axis_Mean_Error_nonHelium;

    std::vector<double> X_axis_CutValue_total;
    std::vector<double> Y_axis_TotalN_total;
    std::vector<double> Y_axis_Sigma_total;
    std::vector<double> Y_axis_Sigma_Error_total;
    std::vector<double> Y_axis_Mean_total;
    std::vector<double> Y_axis_Mean_Error_total;

  std::vector<double> X_axis_CutValue_Purity_Eff;
  std::vector<double> Y_axis_Purity;
  std::vector<double> Y_axis_Eff;
  std::vector<double> Y_axis_Puroty_Eff;


    for(int i=0 ; i< GaussianFits_helium.size();++i){

      X_axis_CutValue_Helium.push_back(GaussianFits_helium.at(i).CutValue);
      Y_axis_TotalN_Helium.push_back(GaussianFits_helium.at(i).TotalN);
      Y_axis_Sigma_Helium.push_back(GaussianFits_helium.at(i).Sigma);
      Y_axis_Mean_Helium.push_back(GaussianFits_helium.at(i).Mean);
      Y_axis_Sigma_Error_Helium.push_back(GaussianFits_helium.at(i).Sigma_Error);
      Y_axis_Mean_Error_Helium.push_back(GaussianFits_helium.at(i).Mean_Error);

      X_axis_CutValue_nonHelium.push_back(GaussianFits_nonhelium.at(i).CutValue);
      Y_axis_TotalN_nonHelium.push_back(GaussianFits_nonhelium.at(i).TotalN);
      Y_axis_Sigma_nonHelium.push_back(GaussianFits_nonhelium.at(i).Sigma);
      Y_axis_Mean_nonHelium.push_back(GaussianFits_nonhelium.at(i).Mean);
      Y_axis_Sigma_Error_nonHelium.push_back(GaussianFits_nonhelium.at(i).Sigma_Error);
      Y_axis_Mean_Error_nonHelium.push_back(GaussianFits_nonhelium.at(i).Mean_Error);

      X_axis_CutValue_total.push_back(GaussianFits_total.at(i).CutValue);
      Y_axis_TotalN_total.push_back(GaussianFits_total.at(i).TotalN);
      Y_axis_Sigma_total.push_back(GaussianFits_total.at(i).Sigma);
      Y_axis_Mean_total.push_back(GaussianFits_total.at(i).Mean);
      Y_axis_Sigma_Error_total.push_back(GaussianFits_total.at(i).Sigma_Error);
      Y_axis_Mean_Error_total.push_back(GaussianFits_total.at(i).Mean_Error);

      //X_axis_CutValue_Purity_Eff.push_back(GaussianFits_total.at(i).CutValue);
      //double purtiy = GaussianFits_helium.at(i).TotalN / GaussianFits_total.at(i).TotalN;
      //double purtiy = GaussianFits_helium.at(i).TotalN / GaussianFits_total.at(i).TotalN;

    }


      TGraphErrors  *TG_TotalN_Helium = MakeTGraph_from_Vectors(Y_axis_TotalN_Helium,  X_axis_CutValue_Helium);
      TGraphErrors  *TG_Sigma_Helium = MakeTGraph_from_VectorsErrors(Y_axis_Sigma_Helium, Y_axis_Sigma_Error_Helium,  X_axis_CutValue_Helium);
      TGraphErrors  *TG_Mean_Helium = MakeTGraph_from_VectorsErrors(Y_axis_Mean_Helium, Y_axis_Mean_Error_Helium,  X_axis_CutValue_Helium);

      TGraphErrors  *TG_TotalN_nonHelium = MakeTGraph_from_Vectors(Y_axis_TotalN_nonHelium,  X_axis_CutValue_nonHelium);
      TGraphErrors  *TG_Sigma_nonHelium = MakeTGraph_from_VectorsErrors(Y_axis_Sigma_nonHelium, Y_axis_Sigma_Error_nonHelium,  X_axis_CutValue_nonHelium);
      TGraphErrors  *TG_Mean_nonHelium = MakeTGraph_from_VectorsErrors(Y_axis_Mean_nonHelium,Y_axis_Mean_Error_nonHelium,  X_axis_CutValue_nonHelium);

      TGraphErrors  *TG_TotalN_total = MakeTGraph_from_Vectors(Y_axis_TotalN_total,  X_axis_CutValue_total);
      TGraphErrors  *TG_Sigma_total = MakeTGraph_from_VectorsErrors(Y_axis_Sigma_total, Y_axis_Sigma_Error_total,  X_axis_CutValue_total);
      TGraphErrors  *TG_Mean_total = MakeTGraph_from_VectorsErrors(Y_axis_Mean_total,Y_axis_Mean_Error_total,  X_axis_CutValue_total);


  // need pdf format

  char TGraph_name[1024];

  sprintf(TGraph_name, "NEvents Pass Fiducial Cut [%s]", Playlist );
  DrawTGraph(TG_TotalN_total, TG_TotalN_Helium, TG_TotalN_nonHelium,  "Fiducial Cut to Edge [mm]","NEvnets", TGraph_name, "Total", "{}^{4}He", "non-{}^{4}He" ,pdf_label, cE, mnvPlotter, false, false , setGrid, true  );

  DrawTGraph(TG_TotalN_total, TG_TotalN_Helium, TG_TotalN_nonHelium,  "Fiducial Cut to Edge [mm]","NEvnets", TGraph_name, "Total", "{}^{4}He", "non-{}^{4}He" ,pdf_label, cE, mnvPlotter, false, true, setGrid, true );

  sprintf(TGraph_name, "Change in #sigma Gaussian Fits Fiducial Cut [%s]", Playlist );
  DrawTGraph(TG_Sigma_total, TG_Sigma_Helium, TG_Sigma_nonHelium, "Fiducial Cut to Edge [mm]","Sigma Gaussian Fits", TGraph_name, "#sigma Total", "#sigma {}^{4}He","#sigma non-{}^{4}He",pdf_label, cE, mnvPlotter, false, false, setGrid );

  sprintf(TGraph_name, "Change in mean Gaussian Fits as Fiducial Cut [%s]", Playlist );
  DrawTGraph(TG_Mean_total, TG_Mean_Helium, TG_Mean_nonHelium, "Fiducial Cut to Edge [mm]","Mean ", TGraph_name, "#mu Total" ,"#mu {}^{4}He","#mu non-{}^{4}He",  pdf_label, cE, mnvPlotter, false, false, setGrid );

  }


  ////////////////////////////////////////////////////
  //////
  ////////////////////////////////////////////////////

  void Draw_TGraphs_NEvent_FidiucalCut(std::vector<NEvent_FidiucalCut> NEvent_FidiucalCut_vector,
      const char* pdf_label, char *histotitle, const char *playlist, TCanvas *cE, MnvPlotter *mnvPlotter, bool Xlog ,bool Ylog)
  {

    std::string TotalTitle = string(histotitle);
    std::vector<double> X_axis_CutValue;
    std::vector<double> Y_axis_NumeratorN;
    std::vector<double> Y_axis_DenominatorN;

    std::vector<double> Y_axis_HeliumN;
    std::vector<double> Y_axis_nonHeliumN;
    std::vector<double> Y_axis_HeliumPlusnonHeliumN;

    std::vector<double> Y_axis_Purity;
    std::vector<double> Y_axis_Purity_Error;
    std::vector<double> Y_axis_Eff;
    std::vector<double> Y_axis_Eff_Error;
    std::vector<double> Y_axis_Purity_Eff;
    std::vector<double> Y_axis_Purity_Eff_Error;
    std::vector<double> Y_axis_FOM;
  //  std::vector<double> Y_axis_FOM_percent;

    for(auto NEvent : NEvent_FidiucalCut_vector){
      X_axis_CutValue.push_back(NEvent.FidiucalCut);

      double HeliumN = NEvent.TotalN_RECO_Helium;
      double NonHeliumN = NEvent.TotalN_RECO_nonHelium;
      double Total_Helium_nonhelium = NEvent.TotalN_RECO_total;

      double Numerator = NEvent.TotalN_Numra;
      double Denominator = NEvent.TotalN_TRUE;

      double PurityN = HeliumN / Total_Helium_nonhelium;
      double Purity_ErrorN = eff_error(HeliumN, Total_Helium_nonhelium, 0);

      double EfficiencyN = Numerator / Denominator;
      double Efficiency_ErrorN = eff_error( Numerator, Denominator, 0);

      double PurityTimesEfficiencyN = PurityN*EfficiencyN;
      double PurityTimesEfficiency_Error =   Purity_eff_error(PurityN , Purity_ErrorN, EfficiencyN, Efficiency_ErrorN);

      double FOM =  (pow(Efficiency_ErrorN / EfficiencyN ,2) + pow(Purity_ErrorN / PurityN ,2));
      //double FOM_percent = FOM*500;
      Y_axis_NumeratorN.push_back(Numerator);
      Y_axis_DenominatorN.push_back(Denominator);

      Y_axis_HeliumN.push_back(HeliumN);
      Y_axis_nonHeliumN.push_back(NonHeliumN);

      Y_axis_HeliumPlusnonHeliumN.push_back(Total_Helium_nonhelium);
      Y_axis_Purity.push_back(PurityN);
      Y_axis_Purity_Error.push_back(Purity_ErrorN);
      Y_axis_Eff.push_back(EfficiencyN);
      Y_axis_Eff_Error.push_back(Efficiency_ErrorN);
      Y_axis_Purity_Eff.push_back(PurityTimesEfficiencyN);
      Y_axis_Purity_Eff_Error.push_back(PurityTimesEfficiency_Error);
      Y_axis_FOM.push_back(FOM);
    //  Y_axis_FOM_percent.push_back(FOM_percent);

    }


    TGraphErrors  *TG_Purity = MakeTGraph_from_VectorsErrors(Y_axis_Purity, Y_axis_Purity_Error,  X_axis_CutValue);
    TGraphErrors  *TG_Eff = MakeTGraph_from_VectorsErrors(Y_axis_Eff, Y_axis_Eff_Error,  X_axis_CutValue);
    TGraphErrors  *TG_Eff_Purity = MakeTGraph_from_VectorsErrors(Y_axis_Purity_Eff, Y_axis_Purity_Eff_Error,  X_axis_CutValue);

    TGraphErrors  *TG_TotalNumeratorN = MakeTGraph_from_Vectors(Y_axis_NumeratorN,  X_axis_CutValue);
    TGraphErrors  *TG_TotalDenominatorN = MakeTGraph_from_Vectors(Y_axis_DenominatorN,  X_axis_CutValue);

    TGraphErrors  *TG_FOM = MakeTGraph_from_VectorsNoErrors(Y_axis_FOM,  X_axis_CutValue);
    //TGraphErrors  *TG_FOM_percent = MakeTGraph_from_VectorsNoErrors(Y_axis_FOM_percent,  X_axis_CutValue);

    TGraphErrors  *TG_HeliumN = MakeTGraph_from_Vectors(Y_axis_HeliumN,  X_axis_CutValue);
    TGraphErrors  *TG_nonHeliumN = MakeTGraph_from_Vectors(Y_axis_nonHeliumN,  X_axis_CutValue);
    TGraphErrors  *TG_Total_Helium_nonHeliumN = MakeTGraph_from_Vectors(Y_axis_HeliumPlusnonHeliumN,  X_axis_CutValue);

    char hist_Title[1024];
    sprintf(hist_Title , "NEvents Pass Fiducial Cut [%s]",playlist );
  // need pdf format
  bool setGrid=true;
  DrawTGraph(TG_Total_Helium_nonHeliumN, TG_HeliumN, TG_nonHeliumN,  "Fiducial Cut to Edge [mm]","NEvents", hist_Title, "Total", "{}^{4}He", "non-{}^{4}He" ,pdf_label, cE, mnvPlotter, Xlog , Ylog , setGrid, true  );
  //DrawTGraph(TG_Eff, TG_Purity, TG_Eff_Purity,  "Fiducial Cut to Edge [mm]","NEvnets", "NEvents Pass Fiducial Cut", "Efficiency", "Purity", "Eff*Purity" ,pdf_label, cE, mnvPlotter, Xlog , Ylog , setGrid, true  );
  sprintf(hist_Title , "Purityfor Fiducial Cut to Edge[mm][%s]",playlist );
  DrawTGraph(TG_Purity, "Fiducial Cut to Edge [mm]", "Purity", hist_Title, "Purity", pdf_label, cE, mnvPlotter, Xlog , Ylog  );

  sprintf(hist_Title , "FOM (figure-of-merit) for Fiducial Cut to Edge[mm][%s]",playlist );
  DrawTGraph(TG_FOM, "Fiducial Cut to Edge [mm]", "FOM", hist_Title, "FOM", pdf_label, cE, mnvPlotter, Xlog , Ylog  );
  //DrawTGraph(TG_FOM_percent, "Fiducial Cut to Edge [mm]", "FOM[%]", hist_Title, "FOM", pdf_label, cE, mnvPlotter, Xlog , Ylog  );
  sprintf(hist_Title , "Efficiency for Fiducial Cut to Edge [mm][%s]",playlist );
  DrawTGraph(TG_Eff , TG_Eff_Purity, "Fiducial Cut to Edge [mm]" , "Efficiency",hist_Title, "Efficiency","Eff*purity",  pdf_label, cE, mnvPlotter, Xlog , Ylog, true );
  //sprintf(hist_Title , "Efficiency and FOM (%%) for Fiducial Cut to Edge [mm][%s]",playlist );
  //DrawTGraph(TG_FOM_percent, TG_Eff , TG_Eff_Purity,  "Fiducial Cut to Edge [mm]","Efficiency", hist_Title, "FOM(*500)", "Efficiency", "Eff*purity" ,pdf_label, cE, mnvPlotter, Xlog , Ylog , setGrid, true  );
  printf(hist_Title , "Efficiency's Numerator and Denominator [%s]",playlist );
  DrawTGraph(TG_TotalDenominatorN , TG_TotalNumeratorN, "Fiducial Cut to Edge [mm]" ,"NEvents", "Efficiency's Numerator and Denominator","Denominator", "Numerator",  pdf_label, cE, mnvPlotter, Xlog , true);

  }


  ////////////////////////////////////////////////////
  //////
  ////////////////////////////////////////////////////

  void Draw_TGraphs_NEventONLY_FidiucalCut(std::vector<NEvent_FidiucalCut> NEvent_FidiucalCut_vector,
      const char* pdf_label, char *histotitle, const char *playlist, TCanvas *cE, MnvPlotter *mnvPlotter, bool Xlog ,bool Ylog)
  {

    std::string TotalTitle = string(histotitle);
    std::vector<double> X_axis_CutValue;

    std::vector<double> Y_axis_HeliumN;
    std::vector<double> Y_axis_nonHeliumN;
    std::vector<double> Y_axis_HeliumPlusnonHeliumN;

    std::vector<double> Y_axis_Purity;
    std::vector<double> Y_axis_Purity_Error;

    for(auto NEvent : NEvent_FidiucalCut_vector){
      X_axis_CutValue.push_back(NEvent.FidiucalCut);

      double HeliumN = NEvent.TotalN_RECO_Helium;
      double NonHeliumN = NEvent.TotalN_RECO_nonHelium;
      double Total_Helium_nonhelium = NEvent.TotalN_RECO_total;
      double PurityN = HeliumN / Total_Helium_nonhelium;
      double Purity_ErrorN = eff_error(HeliumN, Total_Helium_nonhelium, 0);
      Y_axis_HeliumN.push_back(HeliumN);
      Y_axis_nonHeliumN.push_back(NonHeliumN);
      Y_axis_HeliumPlusnonHeliumN.push_back(Total_Helium_nonhelium);
      Y_axis_Purity.push_back(PurityN);
      Y_axis_Purity_Error.push_back(Purity_ErrorN);

    }


    TGraphErrors  *TG_Purity = MakeTGraph_from_VectorsErrors(Y_axis_Purity, Y_axis_Purity_Error,  X_axis_CutValue);

    TGraphErrors  *TG_HeliumN = MakeTGraph_from_Vectors(Y_axis_HeliumN,  X_axis_CutValue);
    TGraphErrors  *TG_nonHeliumN = MakeTGraph_from_Vectors(Y_axis_nonHeliumN,  X_axis_CutValue);
    TGraphErrors  *TG_Total_Helium_nonHeliumN = MakeTGraph_from_Vectors(Y_axis_HeliumPlusnonHeliumN,  X_axis_CutValue);
    bool setGrid=true;
    char hist_Title[1024];
    sprintf(hist_Title , "NEvents Pass Fiducial Cut [%s]",playlist );

  DrawTGraph(TG_Total_Helium_nonHeliumN, TG_HeliumN, TG_nonHeliumN,  "Fiducial Cut to Edge [mm]","NEvents", hist_Title, "Total", "{}^{4}He", "non-{}^{4}He" ,pdf_label, cE, mnvPlotter, Xlog , Ylog , setGrid, true  );

  sprintf(hist_Title , "Purity for Fiducial Cut to Edge[mm][%s]",playlist );
  DrawTGraph(TG_Purity, "Fiducial Cut to Edge [mm]", "Purity", hist_Title, "Purity", pdf_label, cE, mnvPlotter, Xlog , Ylog  );

  }

  ////////////////////////////////////////////////////
  //////
  ////////////////////////////////////////////////////

void Draw2DHist_histWithTProfile(MnvH2D *hist_input, const char *Title, const char* xaxislabel,const char* yaxislabel,
  const char* pdf, TCanvas *can, MnvPlotter *plot)
  {


    MnvH2D *hist = (PlotUtils::MnvH2D*)hist_input->Clone("hist");
    TProfile* prof = hist->ProfileX("prof", 1,  -1,  "s" );
    string TotalTitle = string(Title);

    prof->SetMarkerStyle(19);
    prof->SetMarkerColor(12);
    hist->GetXaxis()->CenterTitle();
    hist->GetYaxis()->CenterTitle();
    hist->GetXaxis()->SetTitle(xaxislabel);
    hist->GetYaxis()->SetTitle(yaxislabel);
    hist->GetXaxis()->SetTitleSize(0.038);
    hist->GetYaxis()->SetTitleSize(0.038);


    hist->Draw("COLZ");
    prof->Draw("same ap");

    plot->AddHistoTitle(TotalTitle.c_str(), .04);
    plot->WritePreliminary("TL", .035, 0, 0, false);

    gPad->Update();
    can->Modified();
    can->Print(pdf);

    can->Closed();

  }//end of 2D draw function

  void Draw2DHist_histWithTProfile_Y(MnvH2D *hist_input, const char *Title, const char* xaxislabel,const char* yaxislabel,
    const char* pdf, TCanvas *can, MnvPlotter *plot)
    {


      MnvH2D *hist = (PlotUtils::MnvH2D*)hist_input->Clone("hist");
      TProfile* prof = hist->ProfileY("prof", 1,  -1,  "s" );
      string TotalTitle = string(Title);

      prof->SetMarkerStyle(19);
      prof->SetMarkerColor(12);
      hist->GetXaxis()->CenterTitle();
      hist->GetYaxis()->CenterTitle();
      hist->GetXaxis()->SetTitle(xaxislabel);
      hist->GetYaxis()->SetTitle(yaxislabel);
      hist->GetXaxis()->SetTitleSize(0.038);
      hist->GetYaxis()->SetTitleSize(0.038);


      hist->Draw("COLZ");
      prof->Draw("same ap");

      plot->AddHistoTitle(TotalTitle.c_str(), .04);
      plot->WritePreliminary("TL", .035, 0, 0, false);

      gPad->Update();
      can->Modified();
      can->Print(pdf);

      can->Closed();

    }//end of 2D draw function


  ////////////////////////////////////////////////////
  //////
  ////////////////////////////////////////////////////

void Draw_XDistribution_PerBinWithGaussFit_2DHist(MnvH2D *hist_input,
  const char *Title, const char* xaxislabel,const char* yaxislabel,
  const char* pdf, TCanvas *can, MnvPlotter *plot, bool Setgrid, Double_t maxY )
{

  char hist_Title[1024];
  MnvH2D *hist = (PlotUtils::MnvH2D*)hist_input->Clone("hist");
  std::map<double, MnvH1D*> hist_CutMap;
  std::vector<GaussianFitsParms> GaussianFits_values_Resolution_vector;

  string TotalTitle = string(Title);
  int NXbins = hist->GetNbinsX();

  for(int i = 1 ; i< NXbins+1; i++ ){
    /* Not include unflow and over flow bins*/
    double CutValue = hist->GetXaxis()-> GetBinUpEdge(i);
    sprintf(hist_Title, "h_projection_Cut_%i",(int)CutValue);
    MnvH1D * h_projection = hist->ProjectionY(hist_Title,i,i,"");
    h_projection->SetMaximum(maxY);
    hist_CutMap.insert({CutValue, h_projection});

  }

  std::string xaxislabel_string(xaxislabel);
  std::string yaxislabel_string(yaxislabel);

  double sigma_return= 999;  double TotalN_return= 999;
  double chi_sq_return= 999; int NDF_return= 999;
  double Mean_return = 999;  double Constant_return = 999;
  bool printerrors= false; bool PrintAllgroups = false;
  for(const auto Hist_index :hist_CutMap ){
    sprintf(hist_Title , "%s [Fiducial Cut to Edge %.1f ]",Title , Hist_index.first);
    DrawCVAndError_FromHIST_withFit(Hist_index.second, hist_Title ,xaxislabel_string,yaxislabel_string,
      pdf,  Setgrid , sigma_return , TotalN_return, chi_sq_return, NDF_return,
      Mean_return,  Constant_return , printerrors, PrintAllgroups); // need no pdf format

    GaussianFitsParms Fits;

    Fits.CutValue=Hist_index.first;
    Fits.TotalN=TotalN_return;
    Fits.Sigma=sigma_return;
    Fits.Mean=Mean_return;
    Fits.Constant=Constant_return;
    Fits.ChiSqrt=chi_sq_return;
    Fits.NDF=NDF_return;

    GaussianFits_values_Resolution_vector.push_back(Fits);

  }

  char pdf_withTag[1024];
  sprintf(pdf_withTag, "%s.pdf", pdf);

  Draw_TGraphs_fitParams(GaussianFits_values_Resolution_vector,  pdf_withTag, "GaussianFits", can, plot);

  can->Closed();

}//end of Function


void Draw_XDistribution_PerBinWithGaussFit_2DHist(MnvH2D *hist_input_total, MnvH2D *hist_input_Helium,
  MnvH2D *hist_input_NonHelium, const char *Title, const char* xaxislabel,const char* yaxislabel,
  const char* pdf, char *Playlist, TCanvas *can, MnvPlotter *plot, bool Setgrid, Double_t maxY , bool LogX, bool LogY ){

    char hist_Title[1024];
    MnvH2D *hist_helium = (PlotUtils::MnvH2D*)hist_input_Helium->Clone("hist_helium");
    std::map<double, MnvH1D*> hist_CutMap_helium;
    std::vector<GaussianFitsParms> GaussianFits_values_Resolution_vector_helium;

    MnvH2D *hist_nonhelium = (PlotUtils::MnvH2D*)hist_input_NonHelium->Clone("hist_nonhelium");
    std::map<double, MnvH1D*> hist_CutMap_nonhelium;
    std::vector<GaussianFitsParms> GaussianFits_values_Resolution_vector_nonhelium;

    MnvH2D *hist_total = (PlotUtils::MnvH2D*)hist_input_total->Clone("hist_total");
    std::map<double, MnvH1D*> hist_CutMap_total;
    std::vector<GaussianFitsParms> GaussianFits_values_Resolution_vector_total;


    string TotalTitle = string(Title);
    int NXbins = hist_helium->GetNbinsX();

    for(int i = 1 ; i < NXbins+1; ++i ){
      /* Not include unflow and over flow bins*/
      double CutValue = hist_helium->GetXaxis()-> GetBinUpEdge(i);
      sprintf(hist_Title, "h_projection_HeliumCut_%i",(int)CutValue);
      MnvH1D * h_projection = hist_helium->ProjectionY(hist_Title,i,i,"");
      h_projection->SetMaximum(maxY);
      hist_CutMap_helium.insert({CutValue, h_projection});
    }

    for(int i = 1 ; i< NXbins+1; ++i ){
      /* Not include unflow and over flow bins*/
      double CutValue = hist_nonhelium->GetXaxis()-> GetBinUpEdge(i);
      sprintf(hist_Title, "h_projection_nonHeliumCut_%i",(int)CutValue);
      MnvH1D * h_projection = hist_nonhelium->ProjectionY(hist_Title,i,i,"");
      h_projection->SetMaximum(maxY);
      hist_CutMap_nonhelium.insert({CutValue, h_projection});
    }

    for(int i = 1 ; i< NXbins+1; ++i ){
      /* Not include unflow and over flow bins*/
      double CutValue = hist_total->GetXaxis()-> GetBinUpEdge(i);
      sprintf(hist_Title, "h_projection_totalCut_%i",(int)CutValue);
      MnvH1D * h_projection = hist_total->ProjectionY(hist_Title,i,i,"");
      h_projection->SetMaximum(maxY);
      hist_CutMap_total.insert({CutValue, h_projection});
    }

    std::string xaxislabel_string(xaxislabel);
    std::string yaxislabel_string(yaxislabel);

    bool printerrors= false; bool PrintAllgroups = false;

    std::map<double, MnvH1D*>::iterator it_helium;
    std::map<double, MnvH1D*>::iterator it_nonhelium;
    std::map<double, MnvH1D*>::iterator it_total;


    //for(const auto Hist_index :hist_CutMap_helium ){

    for(it_helium = hist_CutMap_helium.begin(),it_nonhelium = hist_CutMap_nonhelium.begin(), it_total =hist_CutMap_total.begin()  ;it_helium != hist_CutMap_helium.end(); ++it_helium, ++it_nonhelium , ++it_total){

      GaussianFitsParms FitsHelium;
      GaussianFitsParms FitsnonHelium;
      GaussianFitsParms FitsTotal;

      sprintf(hist_Title , "%s  [Fiducial Cut to Edge %.1f]",Title, it_helium->first);
      DrawCVAndError_From2HIST_withFit(it_total->second, it_helium->second, it_nonhelium->second, hist_Title ,xaxislabel_string,yaxislabel_string,
        pdf,  Setgrid ,  FitsTotal , FitsHelium, FitsnonHelium, printerrors, PrintAllgroups); // need no pdf format


        FitsHelium.CutValue=it_helium->first;
        FitsnonHelium.CutValue=it_nonhelium->first;
        FitsTotal.CutValue=it_nonhelium->first;

        GaussianFits_values_Resolution_vector_helium.push_back(FitsHelium);
        GaussianFits_values_Resolution_vector_nonhelium.push_back(FitsnonHelium);
        GaussianFits_values_Resolution_vector_total.push_back(FitsTotal);


      }

      char pdf_withTag[1024];
      sprintf(pdf_withTag, "%s.pdf", pdf);

      Draw_TGraphs_fitParams(GaussianFits_values_Resolution_vector_helium,
        GaussianFits_values_Resolution_vector_nonhelium,
        GaussianFits_values_Resolution_vector_total, pdf_withTag, "GaussianFits", can, plot, false, false, Setgrid , Playlist );

        if (LogX==true || LogY == true ){
          Draw_TGraphs_fitParams(GaussianFits_values_Resolution_vector_helium,
            GaussianFits_values_Resolution_vector_nonhelium,
            GaussianFits_values_Resolution_vector_total, pdf_withTag, "GaussianFits", can, plot, LogX, LogY, Setgrid, Playlist);
          }



          can->Closed();


      }//end of Function

////////////////////////////////////////////////////
//////
////////////////////////////////////////////////////


void Draw_YDistribution_PerBin_2DHist_Purity_Efficiency(MnvH2D *hist_input_Numerator,
                                                        MnvH2D *hist_input_Denominator,
                                                        MnvH2D *hist_input_Total,
                                                        MnvH2D *hist_input_Helium_RECO,
                                                        MnvH2D *hist_input_NonHelium_RECO,
const char *Title, const char* xaxislabel,const char* yaxislabel, const char* playlist,
const char* pdf, TCanvas *can, MnvPlotter *plot, bool Setgrid, double maxY_recoCuts, double maxY_TruthCuts , bool LogX, bool LogY ){

  char hist_Title[1024];
  MnvH2D *hist_helium = (PlotUtils::MnvH2D*)hist_input_Helium_RECO->Clone("hist_helium");
  std::map<double, MnvH1D*> hist_CutMap_helium_RECO;
  MnvH2D *hist_nonhelium = (PlotUtils::MnvH2D*)hist_input_NonHelium_RECO->Clone("hist_nonhelium");
  std::map<double, MnvH1D*> hist_CutMap_nonhelium_RECO;

  MnvH2D *hist_helium_nonhelium = (PlotUtils::MnvH2D*)hist_input_Total->Clone("hist_helium_nonhelium");
  std::map<double, MnvH1D*> hist_CutMap_helium_nonhelium_RECO;

  MnvH2D *hist_Numerator = (PlotUtils::MnvH2D*)hist_input_Numerator->Clone("hist_Numerator");
  std::map<double, MnvH1D*> hist_CutMap_total_RECO;
  MnvH2D *hist_Denominator = (PlotUtils::MnvH2D*)hist_input_Denominator->Clone("hist_Denominator");
  std::map<double, MnvH1D*> hist_CutMap_total_TRUE;

  std::vector<NEvent_FidiucalCut> NEvent_Fidiucal;

  string TotalTitle = string(Title);
  int NXbins = hist_helium->GetNbinsX();

  for(int i = 1 ; i < NXbins+1; ++i ){
    /* Not include unflow and over flow bins*/
    NEvent_FidiucalCut NEvent_index;

    double CutValue = hist_helium->GetXaxis()-> GetBinUpEdge(i);
    NEvent_index.FidiucalCut = CutValue;

    sprintf(hist_Title, "h_projection_Total_%i",(int)CutValue);
    MnvH1D * h_projection_hist_Numerator = hist_Numerator->ProjectionY(hist_Title,i,i,"");
    h_projection_hist_Numerator->SetMaximum(maxY_TruthCuts);
    hist_CutMap_total_RECO.insert({CutValue, h_projection_hist_Numerator});
    NEvent_index.TotalN_Numra =   h_projection_hist_Numerator->Integral(1,nbins);

    sprintf(hist_Title, "h_projection_Total_TRUECut_%i",(int)CutValue);
    MnvH1D *h_projection_Denominator = hist_Denominator->ProjectionY(hist_Title,i,i,"");
    h_projection_Denominator->SetMaximum(maxY_TruthCuts);
    hist_CutMap_total_TRUE.insert({CutValue, h_projection_Denominator});
    NEvent_index.TotalN_TRUE =   h_projection_Denominator->Integral(1,nbins);


    sprintf(hist_Title, "h_projection_HeliumCut_%i",(int)CutValue);
    MnvH1D * h_projection_helium = hist_helium->ProjectionY(hist_Title,i,i,"");
    h_projection_helium->SetMaximum(maxY_recoCuts);
    hist_CutMap_helium_RECO.insert({CutValue, h_projection_helium});
    NEvent_index.TotalN_RECO_Helium =   h_projection_helium->Integral(1,nbins);

    sprintf(hist_Title, "h_projection_nonHeliumCut_%i",(int)CutValue);
    MnvH1D * h_projection_nonhelium = hist_nonhelium->ProjectionY(hist_Title,i,i,"");
    h_projection_nonhelium->SetMaximum(maxY_recoCuts);
    hist_CutMap_nonhelium_RECO.insert({CutValue, h_projection_nonhelium});
    NEvent_index.TotalN_RECO_nonHelium =   h_projection_nonhelium->Integral(1,nbins);

    sprintf(hist_Title, "h_projection_Helium_nonHeliumCut_%i",(int)CutValue);
    MnvH1D *h_projection_helium_nonhelium = hist_helium_nonhelium->ProjectionY(hist_Title,i,i,"");
    h_projection_helium_nonhelium->SetMaximum(maxY_recoCuts);
    hist_CutMap_helium_nonhelium_RECO.insert({CutValue, h_projection_helium_nonhelium});
    NEvent_index.TotalN_RECO_total =  h_projection_helium_nonhelium->Integral(1,nbins);

    NEvent_Fidiucal.push_back(NEvent_index);

  }


  std::string xaxislabel_string(xaxislabel);
  std::string yaxislabel_string(yaxislabel);

  bool printerrors= false; bool PrintAllgroups = false;

  std::map<double, MnvH1D*>::iterator it_helium;
  std::map<double, MnvH1D*>::iterator it_nonhelium;
  std::map<double, MnvH1D*>::iterator it_total;

  std::map<double, MnvH1D*>::iterator it_Demontor;
  std::map<double, MnvH1D*>::iterator it_Numrator;

  // make Loop plots for RECO Helium and non Helium
  // make Loop plots for Total RECO and Total RECO
  bool do_binwidth= true;


  for(it_helium = hist_CutMap_helium_RECO.begin(),it_nonhelium = hist_CutMap_nonhelium_RECO.begin(), it_total =hist_CutMap_helium_nonhelium_RECO.begin()  ;it_helium != hist_CutMap_helium_RECO.end(); ++it_helium, ++it_nonhelium , ++it_total){

    sprintf(hist_Title , "%s [Fiducial Cut to Edge %.1f][Reco Cuts][%s]", Title , it_helium->first, playlist);
    DrawCVAndError_From2HIST(it_total->second, it_helium->second, it_nonhelium->second, hist_Title ,yaxislabel_string,"NEvents",
      pdf,  Setgrid ,printerrors, PrintAllgroups, do_binwidth, maxY_recoCuts ); // need no pdf forma

    }


    for(it_Demontor = hist_CutMap_total_TRUE.begin(),it_Numrator = hist_CutMap_total_RECO.begin(); it_Demontor != hist_CutMap_total_TRUE.end(); ++it_Demontor, ++it_Numrator){

      sprintf(hist_Title , "%s [Fiducial Cut to Edge %.1f][%s]",Title , it_Numrator->first,playlist );
      DrawCVAndError_From2HIST(it_Demontor->second, "Demonator", it_Numrator->second, "Numerator", hist_Title ,yaxislabel_string, "NEvents",
      pdf,  Setgrid ,printerrors, PrintAllgroups, do_binwidth, maxY_TruthCuts); // need no pdf forma

    }


    char pdf_withTag[1024];
    sprintf(pdf_withTag, "%s.pdf", pdf);

    Draw_TGraphs_NEvent_FidiucalCut(NEvent_Fidiucal, pdf_withTag, hist_Title, playlist, can, plot, LogX,  LogY);


    can->Closed();


  }//end of Function

  ////////////////////////////////////////////////////
  //////
  ////////////////////////////////////////////////////


void Draw_YDistribution_PerBin_2DHist_Purity_Efficiency(MnvH2D *hist_input_Numerator,
                                                        MnvH2D *hist_input_Denominator,
                                                        MnvH2D *hist_input_Total,
                                                        MnvH2D *hist_input_Helium_RECO,
                                                        MnvH2D *hist_input_NonHelium_RECO,
                                                        MnvH2D *hist_input_Efficiency,
const char *Title, const char* xaxislabel,const char* yaxislabel, const char* playlist,
const char* pdf, TCanvas *can, MnvPlotter *plot, bool Setgrid, double maxY_recoCuts, double maxY_TruthCuts, bool LogX, bool LogY ){

  char hist_Title[1024];
  MnvH2D *hist_helium = (PlotUtils::MnvH2D*)hist_input_Helium_RECO->Clone("hist_helium");
  std::map<double, MnvH1D*> hist_CutMap_helium_RECO;
  MnvH2D *hist_nonhelium = (PlotUtils::MnvH2D*)hist_input_NonHelium_RECO->Clone("hist_nonhelium");
  std::map<double, MnvH1D*> hist_CutMap_nonhelium_RECO;

  MnvH2D *hist_helium_nonhelium = (PlotUtils::MnvH2D*)hist_input_Total->Clone("hist_helium_nonhelium");
  std::map<double, MnvH1D*> hist_CutMap_helium_nonhelium_RECO;

  MnvH2D *hist_Numerator = (PlotUtils::MnvH2D*)hist_input_Numerator->Clone("hist_Numerator");
  std::map<double, MnvH1D*> hist_CutMap_total_RECO;
  MnvH2D *hist_Denominator = (PlotUtils::MnvH2D*)hist_input_Denominator->Clone("hist_Denominator");
  std::map<double, MnvH1D*> hist_CutMap_total_TRUE;

  MnvH2D *hist_Eff = (PlotUtils::MnvH2D*)hist_input_Efficiency->Clone("hist_Denominator");
  std::map<double, MnvH1D*> hist_CutMap_Efficiency;
  std::map<double, MnvH1D*> hist_CutMap_Purity;
  std::vector<NEvent_FidiucalCut> NEvent_Fidiucal;

  string TotalTitle = string(Title);
  int NXbins = hist_helium->GetNbinsX();

  for(int i = 1 ; i < NXbins+1; ++i ){
    /* Not include unflow and over flow bins*/
    NEvent_FidiucalCut NEvent_index;

    double CutValue = hist_helium->GetXaxis()-> GetBinUpEdge(i);
    NEvent_index.FidiucalCut = CutValue;

    sprintf(hist_Title, "h_projection_Total_%i",(int)CutValue);
    MnvH1D * h_projection_hist_Numerator = hist_Numerator->ProjectionY(hist_Title,i,i,"");
    h_projection_hist_Numerator->SetMaximum(maxY_TruthCuts);
    hist_CutMap_total_RECO.insert({CutValue, h_projection_hist_Numerator});
    NEvent_index.TotalN_Numra =   h_projection_hist_Numerator->Integral(1,nbins);

    sprintf(hist_Title, "h_projection_Total_TRUECut_%i",(int)CutValue);
    MnvH1D *h_projection_Denominator = hist_Denominator->ProjectionY(hist_Title,i,i,"");
    h_projection_Denominator->SetMaximum(maxY_TruthCuts);
    hist_CutMap_total_TRUE.insert({CutValue, h_projection_Denominator});
    NEvent_index.TotalN_TRUE =   h_projection_Denominator->Integral(1,nbins);

    sprintf(hist_Title, "h_projection_HeliumCut_%i",(int)CutValue);
    MnvH1D * h_projection_helium = hist_helium->ProjectionY(hist_Title,i,i,"");
    h_projection_helium->SetMaximum(maxY_recoCuts);
    hist_CutMap_helium_RECO.insert({CutValue, h_projection_helium});
    NEvent_index.TotalN_RECO_Helium =   h_projection_helium->Integral(1,nbins);

    sprintf(hist_Title, "h_projection_nonHeliumCut_%i",(int)CutValue);
    MnvH1D * h_projection_nonhelium = hist_nonhelium->ProjectionY(hist_Title,i,i,"");
    h_projection_nonhelium->SetMaximum(maxY_recoCuts);
    hist_CutMap_nonhelium_RECO.insert({CutValue, h_projection_nonhelium});
    NEvent_index.TotalN_RECO_nonHelium =   h_projection_nonhelium->Integral(1,nbins);

    sprintf(hist_Title, "h_projection_Helium_nonHeliumCut_%i",(int)CutValue);
    MnvH1D *h_projection_helium_nonhelium = hist_helium_nonhelium->ProjectionY(hist_Title,i,i,"");
    h_projection_helium_nonhelium->SetMaximum(maxY_recoCuts);
    hist_CutMap_helium_nonhelium_RECO.insert({CutValue, h_projection_helium_nonhelium});
    NEvent_index.TotalN_RECO_total =  h_projection_helium_nonhelium->Integral(1,nbins);

    sprintf(hist_Title, "h_projection_Eff_perCut_%i",(int)CutValue);
    MnvH1D *h_projection_Eff = hist_Eff->ProjectionY(hist_Title,i,i,"");
    h_projection_Eff->SetMaximum(maxY_recoCuts);
    hist_CutMap_Efficiency.insert({CutValue, h_projection_Eff});
    MnvH1D* h_projection_helium_clone  = (MnvH1D*) h_projection_helium->Clone("h_projection_helium_clone");
    MnvH1D *h_projection_helium_nonhelium_clone = hist_helium_nonhelium->ProjectionY(hist_Title,i,i,"");

    h_projection_helium_clone->Divide(h_projection_helium_clone, h_projection_helium_nonhelium_clone,1.0,1.0,"");
    hist_CutMap_Purity.insert({CutValue, h_projection_helium_clone});

    NEvent_Fidiucal.push_back(NEvent_index);

  }

  std::string xaxislabel_string(xaxislabel);
  std::string yaxislabel_string(yaxislabel);

  bool printerrors= false; bool PrintAllgroups = false; bool PrintEff_errors = false;

  std::map<double, MnvH1D*>::iterator it_helium;
  std::map<double, MnvH1D*>::iterator it_nonhelium;
  std::map<double, MnvH1D*>::iterator it_total;

  std::map<double, MnvH1D*>::iterator it_Demontor;
  std::map<double, MnvH1D*>::iterator it_Numrator;

  std::map<double, MnvH1D*>::iterator it_eff;
  std::map<double, MnvH1D*>::iterator it_purity;
  // make Loop plots for RECO Helium and non Helium
  // make Loop plots for Total RECO and Total RECO
  bool do_binwidth= true;

  for(it_helium = hist_CutMap_helium_RECO.begin(),it_nonhelium = hist_CutMap_nonhelium_RECO.begin(), it_total =hist_CutMap_helium_nonhelium_RECO.begin()  ;it_helium != hist_CutMap_helium_RECO.end(); ++it_helium, ++it_nonhelium , ++it_total){

    sprintf(hist_Title , "%s [Fiducial Cut to Edge %.1f][Reco Cuts][%s]", Title , it_helium->first, playlist);
    DrawCVAndError_From2HIST(it_total->second, it_helium->second, it_nonhelium->second, hist_Title ,yaxislabel_string, "NEvents",
      pdf,  Setgrid ,printerrors, PrintAllgroups, do_binwidth, maxY_recoCuts ); // need no pdf forma
    }

    for(it_Demontor = hist_CutMap_total_TRUE.begin(),it_Numrator = hist_CutMap_total_RECO.begin(); it_Demontor != hist_CutMap_total_TRUE.end(); ++it_Demontor, ++it_Numrator){

      sprintf(hist_Title , "%s [Fiducial Cut to Edge %.1f][%s]",Title , it_Numrator->first,playlist );
      DrawCVAndError_From2HIST(it_Demontor->second, "Demonator", it_Numrator->second, "Numerator", hist_Title ,yaxislabel_string, "NEvents",
      pdf,  Setgrid ,printerrors, PrintAllgroups, do_binwidth, maxY_TruthCuts); // need no pdf forma
    }


    char pdf_withTag[1024];
    sprintf(pdf_withTag, "%s.pdf", pdf);

    Draw_TGraphs_NEvent_FidiucalCut(NEvent_Fidiucal, pdf_withTag, hist_Title, playlist, can, plot, LogX,  LogY);

    for(it_eff = hist_CutMap_Efficiency.begin(),it_purity= hist_CutMap_Purity.begin(); it_eff != hist_CutMap_Efficiency.end(); ++it_eff, ++it_purity){
/*
      sprintf(hist_Title , "[Efficiency] [Fiducial Cut to Edge %.1f][%s]", it_eff->first, playlist );
      DrawCVAndError_FromHistPointer(it_eff->second, hist_Title ,yaxislabel_string, "Efficiency",
      pdf, do_binwidth, LogY, PrintEff_errors, .25);

      sprintf(hist_Title , "[Purity] [Fiducial Cut to Edge %.1f][%s]", it_eff->first, playlist );
      DrawCVAndError_FromHistPointer(it_purity->second, hist_Title ,yaxislabel_string, "Purity",
      pdf, do_binwidth, LogY, PrintEff_errors, .03);
      */
      MnvH1D* h_eff_clone  = (MnvH1D*)it_eff->second->Clone("h_eff_clone");

      it_purity->second->Multiply(it_purity->second, h_eff_clone,1.0,1.0);

      sprintf(hist_Title , "[Efficiency] [Fiducial Cut to Edge %.1f][%s]", it_eff->first, playlist );
      DrawCVAndError_From2HIST(it_eff->second, "Efficiency", it_purity->second, "Eff*Purity", hist_Title ,yaxislabel_string, "NEvents",
      pdf,  Setgrid ,printerrors, PrintAllgroups, do_binwidth, .01);

    }



    can->Closed();


  }//end of Function


  ////////////////////////////////////////////////////
  //////
  ////////////////////////////////////////////////////


void Draw_YDistribution_PerBin_2DHist(MnvH2D *hist_input_Total,
                                      MnvH2D *hist_input_Helium_RECO,
                                      MnvH2D *hist_input_NonHelium_RECO,
 const char *Title, const char* xaxislabel,const char* yaxislabel, const char* playlist,
 const char* pdf, TCanvas *can, MnvPlotter *plot, bool Setgrid, double maxY_recoCuts,
 bool LogX, bool LogY ){

   char hist_Title[1024];
   MnvH2D *hist_helium = (PlotUtils::MnvH2D*)hist_input_Helium_RECO->Clone("hist_helium");
   std::map<double, MnvH1D*> hist_CutMap_helium_RECO;
   MnvH2D *hist_nonhelium = (PlotUtils::MnvH2D*)hist_input_NonHelium_RECO->Clone("hist_nonhelium");
   std::map<double, MnvH1D*> hist_CutMap_nonhelium_RECO;

   MnvH2D *hist_helium_nonhelium = (PlotUtils::MnvH2D*)hist_input_Total->Clone("hist_helium_nonhelium");
   std::map<double, MnvH1D*> hist_CutMap_helium_nonhelium_RECO;

   std::vector<NEvent_FidiucalCut> NEvent_Fidiucal;

   string TotalTitle = string(Title);
   int NXbins = hist_helium->GetNbinsX();

   for(int i = 1 ; i < NXbins+1; ++i ){
     /* Not include unflow and over flow bins*/
     NEvent_FidiucalCut NEvent_index;

     double CutValue = hist_helium->GetXaxis()-> GetBinUpEdge(i);

     NEvent_index.FidiucalCut = CutValue;
     NEvent_index.TotalN_Numra =   -999;
     NEvent_index.TotalN_TRUE =  -999;


     sprintf(hist_Title, "h_projection_HeliumCut_%i",(int)CutValue);
     MnvH1D * h_projection_helium = hist_helium->ProjectionY(hist_Title,i,i,"");
     h_projection_helium->SetMaximum(maxY_recoCuts);
     hist_CutMap_helium_RECO.insert({CutValue, h_projection_helium});
     NEvent_index.TotalN_RECO_Helium =   h_projection_helium->Integral(1,nbins);

     sprintf(hist_Title, "h_projection_nonHeliumCut_%i",(int)CutValue);
     MnvH1D * h_projection_nonhelium = hist_nonhelium->ProjectionY(hist_Title,i,i,"");
     h_projection_nonhelium->SetMaximum(maxY_recoCuts);
     hist_CutMap_nonhelium_RECO.insert({CutValue, h_projection_nonhelium});
     NEvent_index.TotalN_RECO_nonHelium =   h_projection_nonhelium->Integral(1,nbins);

     sprintf(hist_Title, "h_projection_Helium_nonHeliumCut_%i",(int)CutValue);
     MnvH1D *h_projection_helium_nonhelium = hist_helium_nonhelium->ProjectionY(hist_Title,i,i,"");
     h_projection_helium_nonhelium->SetMaximum(maxY_recoCuts);
     hist_CutMap_helium_nonhelium_RECO.insert({CutValue, h_projection_helium_nonhelium});
     NEvent_index.TotalN_RECO_total =  h_projection_helium_nonhelium->Integral(1,nbins);

     NEvent_Fidiucal.push_back(NEvent_index);

   }


   std::string xaxislabel_string(xaxislabel);
   std::string yaxislabel_string(yaxislabel);

   bool printerrors= false; bool PrintAllgroups = false;

   std::map<double, MnvH1D*>::iterator it_helium;
   std::map<double, MnvH1D*>::iterator it_nonhelium;
   std::map<double, MnvH1D*>::iterator it_total;

   // make Loop plots for RECO Helium and non Helium
   // make Loop plots for Total RECO and Total RECO
   bool do_binwidth= true;

   for(it_helium = hist_CutMap_helium_RECO.begin(),it_nonhelium = hist_CutMap_nonhelium_RECO.begin(), it_total =hist_CutMap_helium_nonhelium_RECO.begin()  ;it_helium != hist_CutMap_helium_RECO.end(); ++it_helium, ++it_nonhelium , ++it_total){

     sprintf(hist_Title , "%s [Fiducial Cut to Edge %.1f][Reco Cuts][%s]", Title , it_helium->first, playlist);
     DrawCVAndError_From2HIST(it_total->second, it_helium->second, it_nonhelium->second, hist_Title ,yaxislabel_string, "NEvents",
       pdf,  Setgrid ,printerrors, PrintAllgroups, do_binwidth, maxY_recoCuts ); // need no pdf forma

     }




     char pdf_withTag[1024];
     sprintf(pdf_withTag, "%s.pdf", pdf);

     Draw_TGraphs_NEventONLY_FidiucalCut(NEvent_Fidiucal, pdf_withTag, hist_Title, playlist, can, plot, LogX,  LogY);


     can->Closed();


   }//end of Function


   ////////////////////////////////////////////////////
   //////
   ////////////////////////////////////////////////////


   void Draw2DHist_NumberFigures_TFILE(TFile *inputFile,
     const char* histoName, const char *Title, const char* xaxislabel,const char* yaxislabel,
     const char* pdf, TCanvas *can, MnvPlotter *plot){

       std::cout<<"trying 2D HisName  = "<< histoName<<std::endl;

       TH2D *h_mig = (TH2D*)inputFile -> Get(histoName);

       TH2D *h_mig_rowNorm = (TH2D*)h_mig->Clone("h_mig_rowNorm");
       rowNormalize(*h_mig_rowNorm);
       TH2D *h_mig_ColNorm = (TH2D*)h_mig->Clone("h_mig_ColNorm");
       colNormalize(*h_mig_ColNorm);

       string TotalTitle = string(Title);
       char Full_title[1024];
       DrawMagration_heatMap(h_mig,xaxislabel,yaxislabel,Title,pdf,can,plot);

       sprintf(Full_title, "%s (Row Norm)",Title);
       DrawMagration_heatMap(h_mig_rowNorm,xaxislabel,yaxislabel,Full_title,pdf,can,plot);

       sprintf(Full_title, "%s (Col) Norm)",Title);
       DrawMagration_heatMap(h_mig_ColNorm,xaxislabel,yaxislabel,Full_title,pdf,can,plot);




     }//end of 2D draw function

     ////////////////////////////////////////////////////
     //////
     ////////////////////////////////////////////////////

void DrawMagration_heatMap(TH2D *h_migration_input, const char* xaxislabel,const char* yaxislabel,
   const char* Title, const char* pdf, TCanvas *can, MnvPlotter *plotter , bool includeFlows  )
{
  TH2D *h_migration = (TH2D*)h_migration_input->Clone("h_migration");

  int first_bin = includeFlows ? 0 : 1;
  int last_bin_x = includeFlows ? h_migration->GetNbinsX()+1 : h_migration->GetNbinsX();
  int last_bin_y = includeFlows ? h_migration->GetNbinsY()+1 : h_migration->GetNbinsY();
  Int_t nbins_x = includeFlows ? h_migration->GetNbinsX()+2 : h_migration->GetNbinsX();
  Int_t nbins_y = includeFlows ? h_migration->GetNbinsY()+2 : h_migration->GetNbinsY();

  h_migration->GetXaxis()->SetTitle(xaxislabel);
  h_migration->GetXaxis()->CenterTitle();
  h_migration->GetYaxis()->SetTitle(yaxislabel);
  h_migration->GetYaxis()->CenterTitle();

  TMatrixD m_migration(nbins_x, nbins_y);
  TH2D tmp(*h_migration);
  tmp.Reset();

  for (int y = first_bin; y <= last_bin_y; ++y){
    for (int x = first_bin; x <= last_bin_x; ++x){

      double NumberperBin =  h_migration->GetBinContent(x,y);
      bool isnan_bool = std::isnan(NumberperBin);

      if(NumberperBin > 0.0 && isnan_bool == false)
      {
        if (includeFlows)
        {
          m_migration[x][y] = NumberperBin; //yeah that's right  y/x
        }
        else
        {
          m_migration[x-1][y-1] = NumberperBin; //yeah that's right  y/x
        }

        tmp.SetBinContent(x, y, NumberperBin);
      }

      else if (isnan_bool == true || NumberperBin < 0.0)
      {
        if (includeFlows){
          m_migration[x][y] = 0.0; //yeah that's right  y/x
        }
        else
        {
          m_migration[x-1][y-1] = 0.0; //yeah that's right  y/x
        }

        tmp.SetBinContent(x, y, 0.0);

      }

    }
  }


  gStyle->SetPaintTextFormat("2.2f");
  tmp.SetMarkerColor(kRed);
  tmp.SetMarkerSize(0.7);
  tmp.DrawCopy("colz text");

  //h_mig->Draw("COLZ");
  plotter->AddHistoTitle(Title, .04);
  can->Print(pdf);
}//end of function

////////////////////////////////////////////////////
//////
////////////////////////////////////////////////////

void DrawMagration_heatMap(MnvH2D *h_mig, const char* xaxislabel,const char* yaxislabel,
  const char* Title, const char* pdf, TCanvas *can, MnvPlotter *plotter, bool includeFlows )
{

  TH2D *h_migration = (TH2D*)h_mig->Clone("h_migration");


  int first_bin = includeFlows ? 0 : 1;
  int last_bin_x = includeFlows ? h_migration->GetNbinsX()+1 : h_migration->GetNbinsX();
  int last_bin_y = includeFlows ? h_migration->GetNbinsY()+1 : h_migration->GetNbinsY();

  Int_t nbins_x = includeFlows ? h_migration->GetNbinsX()+2 : h_migration->GetNbinsX();
  Int_t nbins_y = includeFlows ? h_migration->GetNbinsY()+2 : h_migration->GetNbinsY();


  h_migration->GetXaxis()->SetTitle(xaxislabel);
  h_migration->GetXaxis()->CenterTitle();
  h_migration->GetYaxis()->SetTitle(yaxislabel);
  h_migration->GetYaxis()->CenterTitle();
  h_migration->SetMinimum(0.0);
  TMatrixD m_migration(nbins_x, nbins_y);
  TH2D tmp(*h_migration);
  tmp.Reset();

  for (int y = first_bin; y <= last_bin_y; ++y){
    for (int x = first_bin; x <= last_bin_x; ++x){

      double NumberperBin =  h_migration->GetBinContent(x,y);
      bool isnan_bool = std::isnan(NumberperBin);
      //std::cout<< "Bin content for bin("<< x<<","<<y<<") has content = "<< NumberperBin<<std::endl;
      if(NumberperBin > 0.0 && isnan_bool == false)
      {
        if (includeFlows)
        {
          m_migration[x][y] = NumberperBin; //yeah that's right  y/x
        }
        else
        {
          m_migration[x-1][y-1] = NumberperBin; //yeah that's right  y/x
        }

        tmp.SetBinContent(x, y, NumberperBin);
      }

      else if (isnan_bool == true || NumberperBin < 0.0)
      {
        if (includeFlows){
          m_migration[x][y] = 0.0; //yeah that's right  y/x
        }
        else
        {
          m_migration[x-1][y-1] = 0.0; //yeah that's right  y/x
        }

        tmp.SetBinContent(x, y, 0.0);

      }

    }
  }
  tmp.SetMinimum(0.0);
  gStyle->SetTickLength(0.0,"x");
  gStyle->SetTickLength(0.0,"y");
  gStyle->SetPaintTextFormat("0.1f");
  gStyle->SetPalette(kBird);
  tmp.SetMarkerSize(.5);
  tmp.SetMarkerColor(kBlack);
  tmp.GetXaxis()->SetTickLength(0.);
  tmp.GetYaxis()->SetTickLength(0.);
  tmp.DrawCopy("colz text");


  //h_mig->Draw("COLZ");
  plotter->AddHistoTitle(Title, .04);
  can->Print(pdf);
}//end of function
////////////////////////////////////////////////////

void DrawMagration_heatMap_LabelBinNumber(MnvH2D *h_mig, const char* xaxislabel,const char* yaxislabel,
  const char* Title, const char* pdf, TCanvas *can, MnvPlotter *plotter, bool includeFlows )
{

  TH2D *h_migration = (TH2D*)h_mig->Clone("h_migration");


  int first_bin = includeFlows ? 0 : 1;
  int last_bin_x = includeFlows ? h_migration->GetNbinsX()+1 : h_migration->GetNbinsX();
  int last_bin_y = includeFlows ? h_migration->GetNbinsY()+1 : h_migration->GetNbinsY();

  Int_t nbins_x = includeFlows ? h_migration->GetNbinsX()+2 : h_migration->GetNbinsX();
  Int_t nbins_y = includeFlows ? h_migration->GetNbinsY()+2 : h_migration->GetNbinsY();


  h_migration->GetXaxis()->SetTitle(xaxislabel);
  h_migration->GetXaxis()->CenterTitle();
  h_migration->GetYaxis()->SetTitle(yaxislabel);
  h_migration->GetYaxis()->CenterTitle();
  h_migration->SetMinimum(0.0);
  TMatrixD m_migration(nbins_x, nbins_y);
  TH2D tmp(*h_migration);
  tmp.Reset();

  for (int y = first_bin; y <= last_bin_y; ++y){
    for (int x = first_bin; x <= last_bin_x; ++x){

      double NumberperBin =  h_migration->GetBinContent(x,y);
      bool isnan_bool = std::isnan(NumberperBin);
      //std::cout<< "Bin content for bin("<< x<<","<<y<<") has content = "<< NumberperBin<<std::endl;
      if(NumberperBin > 0.0 && isnan_bool == false)
      {
        if (includeFlows)
        {
          m_migration[x][y] = NumberperBin; //yeah that's right  y/x
        }
        else
        {
          m_migration[x-1][y-1] = NumberperBin; //yeah that's right  y/x
        }

        tmp.SetBinContent(x, y, NumberperBin);
      }

      else if (isnan_bool == true || NumberperBin < 0.0)
      {
        if (includeFlows){
          m_migration[x][y] = 0.0; //yeah that's right  y/x
        }
        else
        {
          m_migration[x-1][y-1] = 0.0; //yeah that's right  y/x
        }

        tmp.SetBinContent(x, y, 0.0);

      }

    }
  }
  tmp.SetMinimum(0.0);
  gStyle->SetTickLength(0.0,"x");
  gStyle->SetTickLength(0.0,"y");
  gStyle->SetPaintTextFormat("0.1f");
  gStyle->SetPalette(kBird);
  tmp.SetMarkerSize(.5);
  tmp.SetMarkerColor(kBlack);
  tmp.GetXaxis()->SetTickLength(0.);
  tmp.GetYaxis()->SetTickLength(0.);
  tmp.DrawCopy("colz text");


  //h_mig->Draw("COLZ");
  plotter->AddHistoTitle(Title, .04);
  can->Print(pdf);
}//end of function




////////////////////////////////////////////////////
//////
////////////////////////////////////////////////////

void DrawMagration_heatMap_noText(MnvH2D *h_mig, const char* xaxislabel, const char* yaxislabel,
   const char* Title, const char* pdf, TCanvas *can, MnvPlotter *plotter, bool includeFlows, const char* zaxislabel )
{

  TH2D *h_migration = (TH2D*)h_mig->Clone("h_migration");


  int first_bin = includeFlows ? 0 : 1;
  int last_bin_x = includeFlows ? h_migration->GetNbinsX()+1 : h_migration->GetNbinsX();
  int last_bin_y = includeFlows ? h_migration->GetNbinsY()+1 : h_migration->GetNbinsY();

  Int_t nbins_x = includeFlows ? h_migration->GetNbinsX()+2 : h_migration->GetNbinsX();
  Int_t nbins_y = includeFlows ? h_migration->GetNbinsY()+2 : h_migration->GetNbinsY();


  h_migration->GetXaxis()->SetTitle(xaxislabel);
  h_migration->GetXaxis()->CenterTitle();
  h_migration->GetYaxis()->SetTitle(yaxislabel);
  h_migration->GetYaxis()->CenterTitle();
  h_migration->GetZaxis()->SetLabelSize(0.035);
  h_migration->GetZaxis()->SetTitleSize(0.035);
  h_migration->GetZaxis()->SetTitle( zaxislabel );
  h_migration->GetZaxis()->CenterTitle();
  h_migration->GetYaxis()->SetLabelSize(0.02);
  h_migration->GetXaxis()->SetLabelSize(0.02);
  h_migration->GetZaxis()->SetLabelSize(0.025);

  TMatrixD m_migration(nbins_x, nbins_y);
  TH2D tmp(*h_migration);
  tmp.Reset();

  for (int y = first_bin; y <= last_bin_y; ++y){
    for (int x = first_bin; x <= last_bin_x; ++x){

      double NumberperBin =  h_migration->GetBinContent(x,y);
      bool isnan_bool = std::isnan(NumberperBin);
      //std::cout<< "Bin content for bin("<< x<<","<<y<<") has content = "<< NumberperBin<<std::endl;
      if(NumberperBin > 0.0 && isnan_bool == false)
      {
        if (includeFlows)
        {
          m_migration[x][y] = NumberperBin; //yeah that's right  y/x
        }
        else
        {
          m_migration[x-1][y-1] = NumberperBin; //yeah that's right  y/x
        }

        tmp.SetBinContent(x, y, NumberperBin);
      }

      else if (isnan_bool == true || NumberperBin < 0.0)
      {
        if (includeFlows){
          //m_migration[x][y] = 0.0; //yeah that's right  y/x
        }
        else
        {
          //m_migration[x-1][y-1] = 0.0; //yeah that's right  y/x
        }

        tmp.SetBinContent(x, y, 0.0);

      }

    }
  }

  gStyle->SetTickLength(0.0,"x");
  gStyle->SetTickLength(0.0,"y");
  tmp.SetMarkerSize(.7);
  tmp.GetXaxis()->SetTickLength(0.);
  tmp.GetYaxis()->SetTickLength(0.);
  tmp.DrawCopy("colz");


  //h_mig->Draw("COLZ");
  plotter->AddHistoTitle(Title, .04);
  can->Print(pdf);
}//end of function

//////////////////////////////////////////////////
/////
/////////////////////////////////////////////////

void DrawStack_Vertex_Material_FUll_EMPTY_WITHDATA(bool my_debug, TFile *inputFile_FULL,TFile *inputFile_EMPTY,TFile *inputFile_DATA_FULL,TFile *inputFile_DATA_EMPTY, Pot_MapList POT_MC ,Pot_MapList POT_DATA ,CryoVertex CryroVertex_type,ME_helium_Playlists PlayListFULL , ME_helium_Playlists PlayListEmpty,int doShape,
  int logScale, std::string Hist_name_addON, MnvPlotter *plot, TCanvas *can, const char *pdf){

    // set up legend, assuming this function only ever plots oodles of stacked histograms
    double x1, x2, y1, y2;
    plot->DecodeLegendPosition(x1, y1, x2, y2, "R", 7, 7, .03);
    TLegend *legend = new TLegend(x1 + .145, y1 + .2, x2 + .16, y2 + .2);
    legend->SetNColumns(1);
    legend->SetTextSize(.03);
    legend->SetFillColor(0);

    TLegend *legendFULL = new TLegend(x1 + .145, y1 + .2, x2 + .16, y2 + .2);
    legendFULL->SetNColumns(1);
    legendFULL->SetTextSize(.03);
    legendFULL->SetFillColor(0);

    TLegend *legendEMPTY = new TLegend(x1 + .145, y1 + .2, x2 + .16, y2 + .2);
    legendEMPTY->SetNColumns(1);
    legendEMPTY->SetTextSize(.03);
    legendEMPTY->SetFillColor(0);




    auto Material_vector = GetMaterial_typeList();
    Particle_MnvH1D_Map FULL_HISTS,EMPTY_HISTS;
    std::vector<MnvH1D*>  FULL_HISTS_vector,EMPTY_HISTS_vector,FULL_HISTS_Alone_vector,EMPTY_HISTS_Alone_vector;

    auto xaxislabel = GetVertexCryoVarAxisTitle(CryroVertex_type);
    auto Var_Name =  GetVertexCryoVarHistName(CryroVertex_type) + Hist_name_addON;
    auto Var_title =  GetVertexCryoTitleName(CryroVertex_type);
    auto Playlist_name_FULL = GetPlaylist_InitialName(PlayListFULL);
    auto Playlist_name_EMPTY = GetPlaylist_InitialName(PlayListEmpty);

    auto Var_Name_DATA = GetVertexCryoVarHist_DATA_Name(CryroVertex_type);
    int n_Var_Name_DATA = Var_Name_DATA.length();
    char Var_Name_DATA_char[n_Var_Name_DATA+1];
    strcpy( Var_Name_DATA_char,Var_Name_DATA.c_str());

    PlotUtils::MnvH1D* datahist_FULL = (MnvH1D*)inputFile_DATA_FULL->Get(Var_Name_DATA_char);
    PlotUtils::MnvH1D* datahist_EMPTY = (MnvH1D*)inputFile_DATA_EMPTY->Get(Var_Name_DATA_char);

    PlotUtils::MnvH1D* datahist_ALONE_FULL = (MnvH1D*)inputFile_DATA_FULL->Get(Var_Name_DATA_char);
    PlotUtils::MnvH1D* datahist_ALONE_EMPTY = (MnvH1D*)inputFile_DATA_EMPTY->Get(Var_Name_DATA_char);


    auto POT_scale_toFULL= POT_MC[PlayListFULL]/POT_MC[PlayListEmpty];
    auto POT_scale_toFULLDATA= POT_DATA[PlayListFULL]/POT_DATA[PlayListEmpty];
    auto POT_scale_toFULL_MC_ToDATA= POT_DATA[PlayListFULL]/POT_MC[PlayListFULL];
    auto POT_scale_toEMPY_MC_ToEMPTYDATA= POT_DATA[PlayListEmpty]/POT_MC[PlayListEmpty];

    double scale_to_FULLData[4] = {POT_DATA[PlayListFULL]/POT_MC[PlayListFULL] ,  POT_DATA[PlayListFULL]/POT_MC[PlayListEmpty]  , 1.0 , POT_DATA[PlayListFULL] / POT_DATA[PlayListEmpty]  }; // everything scaled to Full data

std::cout<< "POTscalers: FULLMC to FULLData: " << scale_to_FULLData[0]<< "EmptyMC to FULLData " << scale_to_FULLData[1]<< " Emptydata to FULLData " <<  scale_to_FULLData[3]<<std::endl;

    std::cout<<"POT_scale_toFULL = "<< POT_scale_toFULL<<std::endl;
    std::cout<<"POT_scale_toFULLDATA = "<< POT_scale_toFULLDATA<<std::endl;
    std::cout<<"POT_scale_toFULL_MC_ToDATA = "<< POT_scale_toFULL_MC_ToDATA<<std::endl;
    std::cout<<"POT_scale_toEMPY_MC_ToEMPTYDATA = "<< POT_scale_toEMPY_MC_ToEMPTYDATA<<std::endl;

    datahist_EMPTY->Scale(POT_scale_toFULLDATA);
    datahist_FULL->Add(datahist_EMPTY,-1);

    legend->AddEntry(datahist_FULL, "DATA");
    legendFULL->AddEntry(datahist_ALONE_FULL, "DATA");
    legendEMPTY->AddEntry(datahist_ALONE_EMPTY, "DATA");
    std::cout<< "POT scaler = "<<  POT_scale_toFULL<<std::endl;

    auto Fulltitle =   Var_title  +  "(" + Playlist_name_FULL + " - " + Playlist_name_EMPTY + ") ";
    auto FullALONEtitle =   Var_title  +  "(FULL) (" + Playlist_name_FULL +")";
    auto EmptyALONEtitle =   Var_title  +  "(EMPTY) (" + Playlist_name_EMPTY +")";
    int Fulltitle_n = Fulltitle.length();
    char FinalTitle[Fulltitle_n + 1];
    strcpy(FinalTitle, Fulltitle.c_str());

    int FullALONEtitle_n = FullALONEtitle.length();
    char FinalTitleFULL[FullALONEtitle_n + 1];
    strcpy(FinalTitleFULL, FullALONEtitle.c_str());

    int EmptyALONEtitle_n =EmptyALONEtitle.length();
    char FinalTitlEMPTY[EmptyALONEtitle_n + 1];
    strcpy(FinalTitlEMPTY,EmptyALONEtitle.c_str());

    MnvH1D *hist_totalFULL;
    MnvH1D *hist_totalEMPTY;
    //MnvH1D *hist_ALONE_totalFULL;
    MnvH1D *hist_ALONE_totalEMPTY;


    THStack *mystack[3];
    mystack[0] = new THStack("hs0", "Stacked");
    mystack[1] = new THStack("hs1", "Stacked");
    mystack[2] = new THStack("hs2", "Stacked");
    int fillCol=0;


    TIter Iter(inputFile_FULL->GetListOfKeys());
    TObject *key;

    TIter Iter_empty(inputFile_EMPTY->GetListOfKeys());
    TObject *keyEMPTY;


std::cout<<"first Loop "<<std::endl;

    while((key=Iter()))
    {
      const std::string histName = key->GetName();
      //std::cout<<"HistName = " << histName << std::endl;


      for(auto Material: Material_vector){auto MaterialeName = GetNameMaterial(Material);//end of loop

        if(histName.find((Var_Name + "_material_"+ MaterialeName)) != std::string::npos  ){

          std::cout<<" Total = " <<  Var_Name + "_material_"+ MaterialeName<< std::endl;
          std::cout<<" Total(Key) = " << histName<< std::endl;
          hist_totalFULL = dynamic_cast< MnvH1D*>(((TKey*)key)->ReadObj());
        //  hist_ALONE_totalFULL = dynamic_cast< MnvH1D*>(((TKey*)key)->ReadObj());
        }
        else if(histName.find((MaterialeName+"_"+ Var_Name + "_material")) != std::string::npos) //Then this is a NeutrinoEnergy histogram for some material
        {
          std::cout<<"Inside else IF  = " << MaterialeName+"_"+ Var_Name + "_material"<<std::endl;

          auto hist = dynamic_cast<MnvH1D*>(((TKey*)key)->ReadObj());
          hist -> SetFillColor(CCNuPionIncPlotting::fill_colors[fillCol]);
          hist -> SetLineColor(CCNuPionIncPlotting::fill_colors[fillCol]);
          hist -> SetFillStyle(1001);
          hist -> SetLineWidth(1);
          fillCol++;
          if(hist == nullptr) //nullptr is the same as NULL effectively, but it does some cool type conversion for std::unique_ptr<>
          {
            std::cerr << histName << " is not a TH1, but it is a neutrinoEnergy histogram!  Skipping " << histName << "...\n";
          }

          //hist->Scale(1,"width");
          //mystack[0]->Add(hist); //This might want you to derefence hist first
          //FULL_HISTS.insert({Particle, hist});
          FULL_HISTS_vector.push_back(hist);
          //FULL_HISTS_Alone_vector.push_back(hist);
          int n = MaterialeName.length();
          char char_array[n + 1];
          strcpy(char_array, MaterialeName.c_str());
          legend->AddEntry(hist, char_array);
          legendFULL->AddEntry(hist, char_array);
        }
      }
    }

std::cout<<"2nd Loop "<<std::endl;

fillCol=0;
    while((keyEMPTY=Iter_empty()))
    {
      const std::string histName = keyEMPTY->GetName();
      //std::cout<<"HistName = " << histName << std::endl;


      for(auto Material: Material_vector){auto MaterialeName = GetNameMaterial(Material);
      //  std::cout<<"Loop2 Particle ="<<Particle<<std::endl;
        if(histName.find((Var_Name + "_material_"+ MaterialeName)) != std::string::npos  ){

          std::cout<<" Total = " <<  Var_Name + "_material_"+ MaterialeName<< std::endl;
          std::cout<<" Total(Key) = " << histName<< std::endl;
          hist_totalEMPTY = dynamic_cast< MnvH1D*>(((TKey*)keyEMPTY)->ReadObj());
          hist_ALONE_totalEMPTY = dynamic_cast< MnvH1D*>(((TKey*)keyEMPTY)->ReadObj());

        }
        else if(histName.find((MaterialeName+"_"+ Var_Name + "_material")) != std::string::npos) //Then this is a NeutrinoEnergy histogram for some material
        {
          std::cout<<"Inside else IF  = " << MaterialeName +"_"+ Var_Name + "_material"<<std::endl;

          auto hist = dynamic_cast<MnvH1D*>(((TKey*)keyEMPTY)->ReadObj());
          hist -> SetFillColor(CCNuPionIncPlotting::fill_colors[fillCol]);
          hist -> SetLineColor(CCNuPionIncPlotting::fill_colors[fillCol]);
          hist -> SetFillStyle(1001);
          hist -> SetLineWidth(1);
          fillCol++;
          if(hist == nullptr) //nullptr is the same as NULL effectively, but it does some cool type conversion for std::unique_ptr<>
          {
            std::cerr << histName << " is not a TH1, but it is a neutrinoEnergy histogram!  Skipping " << histName << "...\n";
          }

          //hist->Scale(1,"width");
          //mystack[0]->Add(hist); //This might want you to derefence hist first
          //EMPTY_HISTS.insert({Particle, hist});
          int n = MaterialeName.length();
          char char_array[n + 1];
          strcpy(char_array, MaterialeName.c_str());
          EMPTY_HISTS_vector.push_back(hist);
          EMPTY_HISTS_Alone_vector.push_back(hist);
          legendEMPTY->AddEntry(hist, char_array);
          //int n = ParticleName.length();
          //char char_array[n + 1];
          //strcpy(char_array, ParticleName.c_str());
          //legend->AddEntry(hist, char_array);
        }
      }
    }


if(EMPTY_HISTS_vector.size()!=FULL_HISTS_vector.size()){std::cout<<"size BAD"<<std::endl;}
else{std::cout<<"Size of vectors good "<<std::endl;}
std::cout<<"3rd Loop "<<std::endl;


for(int i=0; i != FULL_HISTS_vector.size(); i++){
  //auto ParticleName = GetNameParticle(Particle_vector[i+1]);
  EMPTY_HISTS_vector[i]->Scale(POT_scale_toFULL);
  FULL_HISTS_vector[i]->Add(EMPTY_HISTS_vector[i],-1);
  FULL_HISTS_vector[i]->Scale(POT_scale_toFULL_MC_ToDATA);
  FULL_HISTS_vector[i]->Scale(1,"width");
  mystack[0]->Add(FULL_HISTS_vector[i]);
  //std::cout<<" FULL_HISTS_Alone_vector"<<std::endl;

  //FULL_HISTS_Alone_vector[i]->Scale(POT_scale_toFULL_MC_ToDATA);
  //FULL_HISTS_Alone_vector[i]->Scale(1,"width");
  //mystack[1]->Add(FULL_HISTS_Alone_vector[i]);
  //std::cout<<" EMPTY_HISTS_Alone_vector"<<std::endl;
  EMPTY_HISTS_Alone_vector[i]->Scale(POT_scale_toEMPY_MC_ToEMPTYDATA);
  EMPTY_HISTS_Alone_vector[i]->Scale(1,"width");
  mystack[2]->Add(EMPTY_HISTS_Alone_vector[i]);

  //int n = ParticleName.length();
  //char char_array[n + 1];
  //strcpy(char_array, ParticleName.c_str());
  //legend->AddEntry(FULL_HISTS_vector[i], char_array);

}

////////////////////////////////////////////////////////////



    hist_totalEMPTY->Scale(POT_scale_toFULL);
    hist_totalFULL->Add(hist_totalEMPTY,-1);
    hist_totalFULL->Scale(POT_scale_toFULL_MC_ToDATA);
  //

    legend->AddEntry(hist_totalFULL, "Total");
    //legendFULL->AddEntry(hist_ALONE_totalFULL, "Total");
    legendEMPTY->AddEntry(hist_ALONE_totalEMPTY, "Total");
     int n = xaxislabel.length();
     char xtitle[n+1];
      strcpy(xtitle, xaxislabel.c_str());

      hist_totalFULL->GetXaxis()->SetTitle(xtitle);
      hist_totalFULL->GetYaxis()->SetTitle("NEvents");
      hist_totalFULL->GetXaxis()->CenterTitle();
      hist_totalFULL->GetXaxis()->SetTitleSize(0.038);

    //  hist_ALONE_totalFULL->Scale(POT_scale_toFULL_MC_ToDATA);
    //  hist_ALONE_totalFULL->Scale(1.0,"width");
    //  hist_ALONE_totalFULL->GetXaxis()->SetTitle(xtitle);
    //  hist_ALONE_totalFULL->GetYaxis()->SetTitle("NEvents");
    //  hist_ALONE_totalFULL->GetXaxis()->CenterTitle();
    //  hist_ALONE_totalFULL->GetXaxis()->SetTitleSize(0.038);

      hist_ALONE_totalEMPTY->Scale(POT_scale_toEMPY_MC_ToEMPTYDATA);
      hist_ALONE_totalEMPTY->Scale(1.0,"width");

      hist_ALONE_totalEMPTY->GetXaxis()->SetTitle(xtitle);
      hist_ALONE_totalEMPTY->GetYaxis()->SetTitle("NEvents");
      hist_ALONE_totalEMPTY->GetXaxis()->CenterTitle();
      hist_ALONE_totalEMPTY->GetXaxis()->SetTitleSize(0.038);


      datahist_FULL->Scale(1.0,"width");
      datahist_FULL->SetMarkerStyle(20);
      datahist_FULL->SetMarkerSize(1.25);


      if(hist_totalFULL->GetMaximum() > datahist_FULL->GetMaximum()){hist_totalFULL->SetMaximum(hist_totalFULL->GetMaximum() * 1.45);}
      else{hist_totalFULL->SetMaximum(datahist_FULL->GetMaximum() * 1.45);}

      //datahist_ALONE_FULL->Scale(1.0,"width");
    //  datahist_ALONE_FULL->SetMarkerStyle(20);
    //  datahist_ALONE_FULL->SetMarkerSize(1.25);
    //  if(hist_ALONE_totalFULL->GetMaximum() > datahist_ALONE_FULL->GetMaximum()){hist_ALONE_totalFULL->SetMaximum(hist_ALONE_totalFULL->GetMaximum() * 1.45);}
      //else{hist_ALONE_totalFULL->SetMaximum(datahist_ALONE_FULL->GetMaximum() * 1.45);}

      datahist_ALONE_EMPTY->Scale(1.0,"width");
      datahist_ALONE_EMPTY->SetMarkerStyle(20);
      datahist_ALONE_EMPTY->SetMarkerSize(1.25);
      if(hist_ALONE_totalEMPTY->GetMaximum() > datahist_ALONE_EMPTY->GetMaximum()){hist_ALONE_totalEMPTY->SetMaximum(hist_ALONE_totalEMPTY->GetMaximum() * 1.45);}
      else{hist_ALONE_totalEMPTY->SetMaximum(datahist_ALONE_EMPTY->GetMaximum() * 1.45);}

      hist_totalFULL->Scale(1.0,"width");
      hist_totalFULL->Draw("HIST");
      mystack[0]->Draw("HIST SAME");
      datahist_FULL->Draw("SAME");
      legend->Draw();
     plot->AddHistoTitle(FinalTitle, .04);
     plot->WritePreliminary("TL", .035, 0, 0, false);
     can -> Print(pdf);



}//ENd of DrawStack_paricle

////////////////////////////////////////////////////
//////
////////////////////////////////////////////////////

void DrawCVAndError_FromTFile(TFile *inputFile_MCFULL, TFile *inputFile_MCEMPTY,  char *histoName_MC,
  TFile *inputFile_DATAFULL,TFile *inputFile_DATAEMPTY, char *histoName_Data,
  Pot_MapStatusList POT_MC, Pot_MapStatusList POT_DATA, bool TrueifFullelseEmpty, char *histotitle,
  std::string xaxislabel, std::string label, bool DoBinwidthNorm, bool doSmallerrorgrounps,
  std::string units, int Print_Error ,bool Debug)
{    //helium_Status kEMPTY, kFULL;

  std::vector<bool> Print_Vector = Print_Systematics(Print_Error);

  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  //PlotUtils::MnvPlotter mnvPlotter();
  TCanvas cE ("c1","c1");
  std::cout<<"trying MC HisName = "<< histoName_MC<<std::endl;
  std::cout<<"trying data HisName = "<< histoName_Data<<std::endl;
  bool MakeXaxisLOG = false;
  double scale_to_FULLData[4] = {POT_DATA[kFULL]/POT_MC[kFULL],  POT_DATA[kFULL]/POT_MC[kEMPTY]  , 1.0 , POT_DATA[kFULL]/POT_DATA[kEMPTY]  };
  MnvH1D *hist_a;
  MnvH1D *hist_b;
  MnvH1D *hist_ap1;
  MnvH1D *hist_bp1;
  bool isfull= true;
  bool isempty = false;

  for (int fullOrEmpty = 0; fullOrEmpty < 3; fullOrEmpty ++) {

    if(fullOrEmpty==0){
      if(Debug==true){std::cout<<"Starting to initialize FUll MC in DrawCVAndError_FromTFile for: " <<histoName_MC<<std::endl; }

      //hist_a = (MnvH1D*)inputFile_MCFULL -> Get(histoName_MC);
      hist_a = Get1DHist(*inputFile_MCFULL, histoName_MC, isfull);
      if(Debug==true){std::cout<<" Final initialize FUll MC in DrawCVAndError_FromTFile for: " <<histoName_MC<<std::endl; }

      if(Debug==true){std::cout<<"Starting to initialize FUll MC in DrawCVAndError_FromTFile for: " <<histoName_MC<<std::endl; }
      //hist_b = (MnvH1D*)inputFile_DATAFULL -> Get(histoName_Data);
      hist_b = Get1DHist(*inputFile_DATAFULL, histoName_Data, isfull);
      if(Debug==true){std::cout<<"initialize FUll data in DrawCVAndError_FromTFile for: " <<histoName_Data<<std::endl; }

      hist_a->Scale(scale_to_FULLData[0]);

      if(Debug==true){std::cout<<"POT scaled full MC " <<histoName_Data<<std::endl; }


      if(DoBinwidthNorm==true){
        if(Debug==true){std::cout<<"Bin Width Norm full MC and Data " <<histoName_Data<<std::endl; }


      }

    }

    else if (fullOrEmpty==1)
    { if(Debug==true){std::cout<<"Starting to initialize Empty MC in DrawCVAndError_FromTFile for: " <<histoName_MC<<std::endl; }
    //hist_a = (MnvH1D*)inputFile_MCEMPTY -> Get(histoName_MC);
    hist_a = Get1DHist(*inputFile_MCEMPTY, histoName_MC, isempty);
    if(Debug==true){std::cout<<"initialize Empty MC in DrawCVAndError_FromTFile for: " <<histoName_MC<<std::endl; }
    if(Debug==true){std::cout<<"Starting to initialize Empty Data in DrawCVAndError_FromTFile for: " <<histoName_MC<<std::endl; }
    //hist_b = (MnvH1D*)inputFile_DATAEMPTY -> Get(histoName_Data);
    hist_b = Get1DHist(*inputFile_DATAEMPTY, histoName_Data, isempty);
    if(Debug==true){std::cout<<"initialize EMTPY data in DrawCVAndError_FromTFile for: " <<histoName_Data<<std::endl; }

    hist_a->Scale(scale_to_FULLData[1]);
    hist_b->Scale(scale_to_FULLData[3]);
    if(Debug==true){std::cout<<"POT scaled Empty MC and Empty Data " <<histoName_Data<<std::endl; }

  }
  else if (fullOrEmpty==2){
    //hist_a = (MnvH1D*)inputFile_MCFULL -> Get(histoName_MC);
    //hist_ap1 = (MnvH1D*)inputFile_MCEMPTY -> Get(histoName_MC);
    //hist_b = (MnvH1D*)inputFile_DATAFULL -> Get(histoName_Data);
    //hist_bp1 = (MnvH1D*)inputFile_DATAEMPTY -> Get(histoName_Data);

    hist_a = Get1DHist(*inputFile_MCFULL, histoName_MC, isfull);
    hist_b = Get1DHist(*inputFile_DATAFULL, histoName_Data, isfull);
    hist_ap1 = Get1DHist(*inputFile_MCEMPTY, histoName_MC, isempty);
    hist_bp1 = Get1DHist(*inputFile_DATAEMPTY, histoName_Data, isempty);

    if(Debug==true){std::cout<<"initialize Full - EMTPY  MC/data in DrawCVAndError_FromTFile for: " <<histoName_Data<<std::endl; }


    hist_a->Scale(scale_to_FULLData[0]); // Full MC
    //hist_b->Scale(scale_to_FULLData[2]); // FUll Data // dont really need to scale this
    hist_ap1->Scale(scale_to_FULLData[1]); //Empty MC
    hist_bp1->Scale(scale_to_FULLData[3]);  // Empty Data



    hist_a -> Add(hist_ap1, -1); // now both full and empty MC are scaled to the appropriate data size
    hist_b -> Add(hist_bp1, -1); // data doesn't need to be scaled

  }

  char emptyFull[1024];
  if (fullOrEmpty == 1) {sprintf(emptyFull, " (Empty) ");}
  else  if (fullOrEmpty == 0) {sprintf(emptyFull, " (Full) ");}
  else  if (fullOrEmpty == 2) {sprintf(emptyFull, " (F-E) ");}


  //plot->DecodeLegendPosition(x1, y1, x2, y2, "R", 2, 2, .03);
  //mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", .5, 10, .025);
  //TLegend *legend = new TLegend(x1 - .05, y1 + .1, x2 + .05, y2 + .1);
  //TLegend *legend = new TLegend(x1 - .02, y1+.31 , x2 +.06 , y2 + .42  );
  //legend->SetNColumns(1);
  //legend->SetTextSize(.03);
  //legend->SetFillColor(0);

  char ytitle[100];
  char xaxislabel_char[xaxislabel.length()+1];
  strcpy( xaxislabel_char,xaxislabel.c_str());

  char units_char[units.length()+1];
  strcpy( units_char,units.c_str());


  double binwidth_title = hist_a -> GetBinWidth(3);
  sprintf(ytitle, "Number of Events"); //
  char total_title[1024];
  sprintf(total_title, "%s[%s] %s", histotitle, emptyFull," (POT Norm) ");

           //if(DoBinwidthNorm==true){
          //   hist_a->Scale(1.0,"width");
          //   hist_b->Scale(1.0,"width");
          // }

           Draw_DataWITHMC_SingleHistinput_withRatio(hist_a, hist_b,
            " ", label, total_title, "",
            xaxislabel_char,  ytitle, DoBinwidthNorm, MakeXaxisLOG);

           if (fullOrEmpty == 2) {
             hist_a -> Clear();
             hist_ap1 -> Clear();
             hist_b -> Clear();
             hist_bp1 -> Clear();
           }
           cE.Closed();
         }

       }

////////////////////////////////////////////////////
//////
////////////////////////////////////////////////////


void DrawCVAndError_FromTFile(TFile *inputFile_MCFULL, TFile *inputFile_MCEMPTY,  char *histoName_MC ,
                            TFile *inputFile_DATAFULL, TFile *inputFile_DATAEMPTY, char *histoName_Data,
                            Pot_MapStatusList POT_MC, Pot_MapStatusList POT_DATA, bool TrueifFullelseEmpty, char *histotitle,
                            std::string xaxislabel, std::string label, bool DoBinwidthNorm, bool doSmallerrorgrounps, std::string units,
                            int Print_Error, bool Debug, bool Makelogx, bool Makelogy )
 {    //helium_Status kEMPTY, kFULL;

   std::vector<bool> Print_Vector = Print_Systematics(Print_Error);


   PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
   //PlotUtils::MnvPlotter mnvPlotter();
   TCanvas cE ("c1","c1");
   std::cout<<"trying MC HisName = "<< histoName_MC<<std::endl;
   std::cout<<"trying data HisName = "<< histoName_Data<<std::endl;
   bool MakeXaxisLOG = Makelogx;
   bool isfull= true;
   bool isempty = false;
   double scale_to_FULLData[4] = {POT_DATA[kFULL]/POT_MC[kFULL],  POT_DATA[kFULL]/POT_MC[kEMPTY]  , 1.0 , POT_DATA[kFULL]/POT_DATA[kEMPTY]  };
   MnvH1D *hist_a;
   MnvH1D *hist_b;
   MnvH1D *hist_ap1;
   MnvH1D *hist_bp1;
   double PotScaler_data,PotScaler_MC;

for (int fullOrEmpty = 0; fullOrEmpty < 3;  ++fullOrEmpty) {

  if(fullOrEmpty==0){
    if(Debug==true){std::cout<<"Starting to initialize FUll MC in DrawCVAndError_FromTFile for: " <<histoName_MC<<std::endl; }
    PotScaler_data = POT_DATA[kFULL];
    PotScaler_MC = POT_MC[kFULL];
    //hist_a = (MnvH1D*)inputFile_MCFULL -> Get(histoName_MC);
    hist_a = Get1DHist(*inputFile_MCFULL, histoName_MC, isfull);
    if(Debug==true){std::cout<<" Final initialize FUll MC in DrawCVAndError_FromTFile for: " <<histoName_MC<<std::endl; }

    if(Debug==true){std::cout<<"Starting to initialize FUll MC in DrawCVAndError_FromTFile for: " <<histoName_MC<<std::endl; }
    //hist_b = (MnvH1D*)inputFile_DATAFULL -> Get(histoName_Data);
    hist_b = Get1DHist(*inputFile_DATAFULL, histoName_Data, isfull);
    if(Debug==true){std::cout<<"initialize FUll data in DrawCVAndError_FromTFile for: " <<histoName_Data<<std::endl; }

    hist_a->Scale(scale_to_FULLData[0]);

    if(Debug==true){std::cout<<"POT scaled full MC " <<histoName_Data<<std::endl; }


    if(DoBinwidthNorm==true){
      if(Debug==true){std::cout<<"Bin Width Norm full MC and Data " <<histoName_Data<<std::endl; }

    }

  }

  else if (fullOrEmpty==1)
  { if(Debug==true){std::cout<<"Starting to initialize Empty MC in DrawCVAndError_FromTFile for: " <<histoName_MC<<std::endl; }
  //hist_a = (MnvH1D*)inputFile_MCEMPTY -> Get(histoName_MC);
  hist_a = Get1DHist(*inputFile_MCEMPTY, histoName_MC, isempty);
  if(Debug==true){std::cout<<"initialize Empty MC in DrawCVAndError_FromTFile for: " <<histoName_MC<<std::endl; }
  if(Debug==true){std::cout<<"Starting to initialize Empty Data in DrawCVAndError_FromTFile for: " <<histoName_MC<<std::endl; }
  //hist_b = (MnvH1D*)inputFile_DATAEMPTY -> Get(histoName_Data);
  hist_b = Get1DHist(*inputFile_DATAEMPTY, histoName_Data, isempty);
  if(Debug==true){std::cout<<"initialize EMTPY data in DrawCVAndError_FromTFile for: " <<histoName_Data<<std::endl; }

  hist_a->Scale(scale_to_FULLData[1]);
  hist_b->Scale(scale_to_FULLData[3]);
  if(Debug==true){std::cout<<"POT scaled Empty MC and Empty Data " <<histoName_Data<<std::endl; }
  PotScaler_data = POT_DATA[kFULL];
  PotScaler_MC = POT_MC[kEMPTY];

}

else if (fullOrEmpty==2){
  //hist_a = (MnvH1D*)inputFile_MCFULL -> Get(histoName_MC);
  //hist_ap1 = (MnvH1D*)inputFile_MCEMPTY -> Get(histoName_MC);
  //hist_b = (MnvH1D*)inputFile_DATAFULL -> Get(histoName_Data);
  //hist_bp1 = (MnvH1D*)inputFile_DATAEMPTY -> Get(histoName_Data);

  hist_a = Get1DHist(*inputFile_MCFULL, histoName_MC, isfull);
  hist_b = Get1DHist(*inputFile_DATAFULL, histoName_Data, isfull);
  hist_ap1 = Get1DHist(*inputFile_MCEMPTY, histoName_MC, isempty);
  hist_bp1 = Get1DHist(*inputFile_DATAEMPTY, histoName_Data, isempty);

  if(Debug==true){std::cout<<"initialize Full - EMTPY  MC/data in DrawCVAndError_FromTFile for: " <<histoName_Data<<std::endl; }

  hist_a->Scale(scale_to_FULLData[0]); // Full MC
  //hist_b->Scale(scale_to_FULLData[2]); // FUll Data // dont really need to scale this
  hist_ap1->Scale(scale_to_FULLData[1]); //Empty MC
  hist_bp1->Scale(scale_to_FULLData[3]);  // Empty Data

  hist_a -> Add(hist_ap1, -1); // now both full and empty MC are scaled to the appropriate data size
  hist_b -> Add(hist_bp1, -1); // data doesn't need to be scaled
  PotScaler_data = POT_DATA[kFULL];
  PotScaler_MC = POT_MC[kFULL];
}

char emptyFull[1024];
if (fullOrEmpty == 1) {sprintf(emptyFull, " [E] ");}
else  if (fullOrEmpty == 0) {sprintf(emptyFull, " [F] ");}
else  if (fullOrEmpty == 2) {sprintf(emptyFull, " [F-E] ");}

char ytitle[100];
char xaxislabel_char[xaxislabel.length()+1];
strcpy( xaxislabel_char,xaxislabel.c_str());

sprintf(ytitle, "Number of Events"); //
char total_title[1024];
sprintf(total_title, "%s [%s]", histotitle, emptyFull);

Draw_DataWITHMC_SingleHistinput_withRatio(hist_a, hist_b,
  " ", label, total_title, units,
  xaxislabel_char,  ytitle, DoBinwidthNorm, MakeXaxisLOG, PotScaler_data, PotScaler_MC, doSmallerrorgrounps);

  if (fullOrEmpty == 2) {
    hist_a -> Clear();
    hist_ap1 -> Clear();
    hist_b -> Clear();
    hist_bp1 -> Clear();
  }
  cE.Closed();
}

}


////////////////////////////////////////////////////
//////
////////////////////////////////////////////////////



void DrawRatio_FromTFile(TFile *inputFile_numerator, TFile *inputFile_demonator,  char *histoName_num, char *histoName_dem ,char *histotitle,
  std::string xaxislabel, std::string pdf_label, std::string units)
  {    //helium_Status kEMPTY, kFULL;
    PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCompactStyle);
    //  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCNuPionIncStyle);
    TCanvas cE ("c1","c1");
    std::cout<<"Making ratio for  = "<< histoName_num<<std::endl;


    double x1, x2, y1, y2;
    // double scale_to_FULLData[4] = {POT_DATA[kFULL]/POT_MC[kFULL],  POT_DATA[kFULL]/POT_MC[kEMPTY]  , 1.0 , POT_DATA[kFULL]/POT_DATA[kEMPTY]  };
    TH1D *hist_numerator;
    TH1D *hist_demonator;

    hist_numerator = (TH1D*)inputFile_numerator -> Get(histoName_num);
    hist_demonator = (TH1D*)inputFile_demonator -> Get(histoName_dem);
    hist_numerator->Divide(hist_numerator, hist_demonator);

    // hist_numerator->Scale(1,"width");
    //plot->DecodeLegendPosition(x1, y1, x2, y2, "R", 2, 2, .03);
    mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", .5, 10, .025);
    //TLegend *legend = new TLegend(x1 - .05, y1 + .1, x2 + .05, y2 + .1);
    TLegend *legend = new TLegend(x1 - .02, y1+.31 , x2 +.06 , y2 + .42  );
    legend->SetNColumns(1);
    legend->SetTextSize(.03);
    legend->SetFillColor(0);


    char ytitle[100];
    //int units_n = ;
    char units_char[units.length()+1];
    strcpy( units_char,units.c_str());

    double binwidth_title = hist_numerator -> GetBinWidth(3);
    sprintf(ytitle, "Ratio / %.2f %s", binwidth_title, units_char); //
    //hist_a->SetFillColor(1);
    hist_numerator->SetLineWidth(3);
    hist_numerator->SetLineColor(2);
    hist_numerator->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
    hist_numerator->GetYaxis()->SetTitle(ytitle);
    hist_numerator->GetXaxis()->CenterTitle();
    hist_numerator->GetYaxis()->CenterTitle();
    hist_numerator->GetYaxis()->SetTitleSize(0.038);
    hist_numerator->GetXaxis()->SetTitleSize(0.038);
    hist_numerator->SetTitle(histotitle);
    hist_numerator->SetMaximum(1.04);
    hist_numerator->SetMinimum(.99);
    hist_numerator->Draw("HIST");
    legend->Clear();
    legend->AddEntry(hist_numerator, "#frac{nsf}{old}", "fl");

    //bool statPlusSys           = true;
    //bool useHistTitles         = false;

    //mnvPlotter.AddChi2Label	(hist_b,  hist_a);
    //TH1D* datahist =new TH1D("", "", 1, 0.0, 1.0);
    // mnvPlotter.DrawDataMCWithErrorBand( datahist, hist_numerator, 1.0, "N", useHistTitles, NULL, NULL, false, statPlusSys);


    legend -> Draw();
    //mnvPlotter.AddPlotLabel (chi_label, const double x, const double y);
    char total_title[1024];
    sprintf(total_title, "Ratio %s ", histotitle);
    mnvPlotter.AddHistoTitle(total_title, .04);
    mnvPlotter.WritePreliminary("TL", .035, 0, 0, false);
    std::string plotname = Form("%s",pdf_label.c_str());
    mnvPlotter.MultiPrint(&cE, plotname, "pdf");

    hist_numerator -> Clear();
    hist_demonator -> Clear();

    cE.Closed();

  }

  ////////////////////////////////////////////////////
  //////
  ////////////////////////////////////////////////////

void Draw2DRatio_FromTFile(TFile *inputFile_numerator, TFile *inputFile_demonator,char *histoName_num,char *histoName_dem,
                           char *num_labelname_y,char *dem_labelname_y, char *num_labelname_x, char *dem_labelname_x,
                           char *histotitle, const char* pdf,TCanvas *can, MnvPlotter *plot)
{    //helium_Status kEMPTY, kFULL;

  std::cout<<"Making ratio for  = "<< histoName_num<<std::endl;
  // double scale_to_FULLData[4] = {POT_DATA[kFULL]/POT_MC[kFULL],  POT_DATA[kFULL]/POT_MC[kEMPTY]  , 1.0 , POT_DATA[kFULL]/POT_DATA[kEMPTY]  };
  MnvH2D *hist_numerator;
  MnvH2D *hist_demonator;

  hist_numerator = (MnvH2D*)inputFile_numerator -> Get(histoName_num);
  hist_demonator = (MnvH2D*)inputFile_demonator -> Get(histoName_dem);
  hist_numerator->Divide(hist_numerator, hist_demonator);

  char ytitle[100];
  char xtitle[100];


  sprintf(ytitle, "Ratio %s / %s", num_labelname_y , dem_labelname_y ); //
  sprintf(xtitle, "Ratio %s / %s", num_labelname_x , dem_labelname_x ); //

  Draw2DHist_hist(hist_numerator, histotitle, xtitle, ytitle, pdf, can, plot);

}


Hist_phyiscs_map Make_Physics_distribution_map_FromTFile(TFile *inputTFile, char *histoName_MC , bool UsePotScaling, double POTScale, ME_helium_Playlists playlist, bool IsRecoOrTruth ){

  auto cryoTank_status = GetPlaylist_HeliumStatus(playlist);
  char Stack_Name_material[1024];
  sprintf(Stack_Name_material, "%s_Material",histoName_MC);

  char Stack_Name_particle[1024];
  sprintf(Stack_Name_particle, "%s_Particle",histoName_MC);

  char Stack_Name_interaction[1024];
  sprintf(Stack_Name_interaction, "%s_Interaction",histoName_MC);

  PlotUtils::HistFolio<PlotUtils::MnvH1D> MC_Stack_Material(
    PlotUtils::LoadHistFolioFromFile<PlotUtils::MnvH1D>(
      *inputTFile, std::string(Stack_Name_material)),
      "MC_Stack_Material");

  PlotUtils::HistFolio<PlotUtils::MnvH1D> MC_Stack_Particle(
    PlotUtils::LoadHistFolioFromFile<PlotUtils::MnvH1D>(
      *inputTFile, std::string(Stack_Name_particle)),
      "MC_Stack_Particle");

  PlotUtils::HistFolio<PlotUtils::MnvH1D> MC_Stack_Interaction(
    PlotUtils::LoadHistFolioFromFile<PlotUtils::MnvH1D>(
      *inputTFile, std::string(Stack_Name_interaction)),
      "MC_Stack_Interaction");

      auto MC_Stack_Material_array = MC_Stack_Material.GetHistArray();
      auto MC_Stack_Particle_array = MC_Stack_Particle.GetHistArray();
      auto MC_Stack_Interaction_array = MC_Stack_Interaction.GetHistArray();
      std::vector<Material_Map> Material_Map_vector = Material_vector( &MC_Stack_Material_array, false, 1.0);
      std::vector<Interaction_Map> Interaction_Map_vector = Interaction_vector( &MC_Stack_Interaction_array, false, 1.0);
      std::vector<Particle_Map> Particle_Map_vector = Particle_vector( &MC_Stack_Particle_array, false, 1.0);


      Hist_phyiscs_map HisMap_Return_stuct{histoName_MC,playlist,cryoTank_status,IsRecoOrTruth,Particle_Map_vector,Material_Map_vector,Interaction_Map_vector};



      return HisMap_Return_stuct;



}

Hist_phyiscs_map_withtrack Make_Physics_withTrack_distribution_map_FromTFile(TFile *inputTFile, char *histoName_MC , bool UsePotScaling, double POTScale, ME_helium_Playlists playlist, bool IsRecoOrTruth ){

  auto cryoTank_status = GetPlaylist_HeliumStatus(playlist);
  char Stack_Name_material[1024];
  sprintf(Stack_Name_material, "%s_Material",histoName_MC);

  char Stack_Name_particle[1024];
  sprintf(Stack_Name_particle, "%s_Particle",histoName_MC);

  char Stack_Name_interaction[1024];
  sprintf(Stack_Name_interaction, "%s_Interaction",histoName_MC);

  char Stack_Name_track[1024];
  sprintf(Stack_Name_track, "%s_Track",histoName_MC);

  PlotUtils::HistFolio<PlotUtils::MnvH1D> MC_Stack_Material(
    PlotUtils::LoadHistFolioFromFile<PlotUtils::MnvH1D>(
      *inputTFile, std::string(Stack_Name_material)),
      "MC_Stack_Material");

  PlotUtils::HistFolio<PlotUtils::MnvH1D> MC_Stack_Particle(
    PlotUtils::LoadHistFolioFromFile<PlotUtils::MnvH1D>(
      *inputTFile, std::string(Stack_Name_particle)),
      "MC_Stack_Particle");

  PlotUtils::HistFolio<PlotUtils::MnvH1D> MC_Stack_Interaction(
    PlotUtils::LoadHistFolioFromFile<PlotUtils::MnvH1D>(
      *inputTFile, std::string(Stack_Name_interaction)),
      "MC_Stack_Interaction");

      PlotUtils::HistFolio<PlotUtils::MnvH1D> MC_Stack_Track(
        PlotUtils::LoadHistFolioFromFile<PlotUtils::MnvH1D>(
          *inputTFile, std::string(Stack_Name_track)),
          "MC_Stack_track");



      auto MC_Stack_Material_array = MC_Stack_Material.GetHistArray();
      auto MC_Stack_Particle_array = MC_Stack_Particle.GetHistArray();
      auto MC_Stack_Interaction_array = MC_Stack_Interaction.GetHistArray();
      auto MC_Stack_Track_array = MC_Stack_Track.GetHistArray();

      std::vector<Material_Map> Material_Map_vector = Material_vector( &MC_Stack_Material_array, false, 1.0);
      std::vector<Interaction_Map> Interaction_Map_vector = Interaction_vector( &MC_Stack_Interaction_array, false, 1.0);
      std::vector<Particle_Map> Particle_Map_vector = Particle_vector( &MC_Stack_Particle_array, false, 1.0);
      std::vector<Track_Map> Track_Map_vector = Track_vector( &MC_Stack_Track_array, false, 1.0);


      Hist_phyiscs_map_withtrack HisMap_Return_stuct{histoName_MC,playlist,cryoTank_status,IsRecoOrTruth,Particle_Map_vector,Material_Map_vector,Interaction_Map_vector, Track_Map_vector};



      return HisMap_Return_stuct;



}

Hist_map_track Make_Track_distribution_map_FromTFile(TFile *inputTFile, char *histoName , bool UsePotScaling, double POTScale, ME_helium_Playlists playlist, bool IsRecoOrTruth , bool isData ){

  auto cryoTank_status = GetPlaylist_HeliumStatus(playlist);

  char Stack_Name_track[1024];
  sprintf(Stack_Name_track, "%s_Track",histoName);

  char Stack_Name_VertexOptions[1024];
  sprintf(Stack_Name_VertexOptions, "%s_VertexOptions",histoName);

  char Stack_Name_boolNTrack[1024];
  sprintf(Stack_Name_boolNTrack, "%s_boolNTrack",histoName);

  PlotUtils::HistFolio<PlotUtils::MnvH1D> MC_Stack_Track(
    PlotUtils::LoadHistFolioFromFile<PlotUtils::MnvH1D>(
      *inputTFile, std::string(Stack_Name_track)),
      "MC_Stack_Track");

  PlotUtils::HistFolio<PlotUtils::MnvH1D> MC_Stack_VertexOptions(
    PlotUtils::LoadHistFolioFromFile<PlotUtils::MnvH1D>(
      *inputTFile, std::string(Stack_Name_VertexOptions)),
      "MC_Stack_VertexOptions");

  PlotUtils::HistFolio<PlotUtils::MnvH1D> MC_Stack_boolNTrack(
    PlotUtils::LoadHistFolioFromFile<PlotUtils::MnvH1D>(
      *inputTFile, std::string(Stack_Name_boolNTrack)),
      "MC_Stack_boolNTrack");

      auto MC_Stack_Track_array = MC_Stack_Track.GetHistArray();
      std::vector<Track_Map> Track_Map_vector = Track_vector( &MC_Stack_Track_array, false, 1.0);

      auto MC_Stack_VertexOptions_array = MC_Stack_VertexOptions.GetHistArray();
      std::vector<VertexOptions_Map> VertexOptions_Map_vector = vertexOption_vector( &MC_Stack_VertexOptions_array, false, 1.0);

      auto MC_Stack_boolNTrack_array = MC_Stack_boolNTrack.GetHistArray();
      std::vector<boolNTrack_Map> boolNTrack_Map_vector = boolNTrack_vector( &MC_Stack_boolNTrack_array, false, 1.0);

      Hist_map_track HisMap_Return_stuct{histoName, playlist, cryoTank_status, IsRecoOrTruth, isData, Track_Map_vector,VertexOptions_Map_vector,boolNTrack_Map_vector};

      return HisMap_Return_stuct;

}


////////////////////////////////////////////////////
//////
////////////////////////////////////////////////////


void DrawSTACKfromHistFilio_FromTFile(TFile *inputFile_MCFULL, TFile *inputFile_MCEMPTY,  char *histoName_MC ,
  TFile *inputFile_DATAFULL,TFile *inputFile_DATAEMPTY, char *histoName_Data, Pot_MapStatusList POT_MC, Pot_MapStatusList POT_DATA, bool TrueifFullelseEmpty, char *histotitle,
  std::string xaxislabel, std::string pdf_label, bool DoBinwidthNorm, bool doSmallerrorgrounps, std::string units, StackType STACKTYPE, bool Debug )
  {    //helium_Status kEMPTY, kFULL;
    PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
    //PlotUtils::MnvPlotter mnvPlotter();
    mnvPlotter.legend_n_columns = 2;
    double scale_to_FULLData[4] = {POT_DATA[kFULL]/POT_MC[kFULL],  POT_DATA[kFULL]/POT_MC[kEMPTY]  , 1.0 , POT_DATA[kFULL]/POT_DATA[kEMPTY]  };

    TCanvas cE ("c1","c1");
    std::cout<<"trying MC HisName = "<< histoName_MC<<std::endl;
    std::cout<<"trying data HisName = "<< histoName_Data<<std::endl;

    char Stack_Name[1024];

    if(STACKTYPE==kMaterial){sprintf(Stack_Name, "%s_Material",histoName_MC);}
    else if(STACKTYPE==kInteraction){ sprintf(Stack_Name, "%s_Interaction",histoName_MC);}
    else if(STACKTYPE==kParticle){ sprintf(Stack_Name, "%s_Particle",histoName_MC);}
    else if(STACKTYPE==kTrackType){ sprintf(Stack_Name, "%s_Track",histoName_MC);}
    else if(STACKTYPE==kVertexOptions){ sprintf(Stack_Name, "%s_VertexOptions",histoName_MC);}
    else if(STACKTYPE==kboolNTrack){ sprintf(Stack_Name, "%s_boolNTrack",histoName_MC);}

    else{std::cout<<"Error unknown stack type: Ploting Failed"<<std::endl; return;}

    if(Debug == true){std::cout << "Getting Hist Using Name: "<< Stack_Name <<std::endl;}

    PlotUtils::HistFolio<PlotUtils::MnvH1D> Full_MC_Stack(
      PlotUtils::LoadHistFolioFromFile<PlotUtils::MnvH1D>(
        *inputFile_MCFULL, std::string(Stack_Name)),
        "Full_MC_Stack");

    if(Debug == true){std::cout << "Initialize Got FUll MC for Stacks   "<< Stack_Name<<std::endl;}


    PlotUtils::HistFolio<PlotUtils::MnvH1D> Empty_MC_Stack(
      PlotUtils::LoadHistFolioFromFile<PlotUtils::MnvH1D>(
        *inputFile_MCEMPTY, std::string(Stack_Name)),
        "Empty_MC_Stack");

    if(Debug == true){std::cout << "Initialize Got Empty MC for Stacks   "<< Stack_Name<<std::endl;}

    PlotUtils::HistFolio<PlotUtils::MnvH1D> Full_MC_Stack_FORSUBTRACTION(
      PlotUtils::LoadHistFolioFromFile<PlotUtils::MnvH1D>(
        *inputFile_MCFULL, std::string(Stack_Name)),
        "Full_MC_Stack_FORSUBTRACTION");

    if(Debug == true){std::cout << "Initialize Got FUll MC for Stacks   "<< Stack_Name<<std::endl;}

    PlotUtils::HistFolio<PlotUtils::MnvH1D> Empty_MC_Stack_FORSUBTRACTION(
      PlotUtils::LoadHistFolioFromFile<PlotUtils::MnvH1D>(
        *inputFile_MCEMPTY, std::string(Stack_Name)),
        "Empty_MC_Stack_FORSUBTRACTION");

    if(Debug == true){std::cout << "Initialize Got Emtpy MC for Stacks   "<< Stack_Name<<std::endl;}
    std::vector<int> Helium9_colorScheme = {
      TColor::GetColor("#EEFF00"), // neonyellow,
      TColor::GetColor("#DF00FF"), //'psychedelic Purple
      TColor::GetColor("#ffc922"), //'sunset yellow'
      TColor::GetColor("#87CEEB"),//'skyblue'
      TColor::GetColor("#0859C6"), //blue
      TColor::GetColor("#654522"), // yellowishbrown,
      TColor::GetColor(  43, 206,  72 ), //green
      TColor::GetColor("#FF0800"),//2 candy Apple
      TColor::GetColor("#90AD1C"),
      TColor::GetColor("#BABABA"), //Gray
      TColor::GetColor("#00FFFF"),//'aqua'
      TColor::GetColor("#F1B6DA"),//pink
      TColor::GetColor("#00A86B"),//'Jade'
      TColor::GetColor("#FAFAD2"),  // LightGoldenRodYellow
      TColor::GetColor("#800000"),  // Maroon
      TColor::GetColor("#555555"),  // dark grey
      TColor::GetColor(0, 153, 143 ), //turquoise
      TColor::GetColor("#654522"), // yellowishbrown,
      TColor::GetColor("#8db600"), // yellowgreen,
      TColor::GetColor("#D3D3D3"),  //'lightgrey'
       TColor::GetColor("#90AD1C"),
       TColor::GetColor("#CCDDAA")
    };

    if(STACKTYPE==kParticle)
    {
      Full_MC_Stack.ApplyColorPalette(Helium9_colorScheme);
      Empty_MC_Stack.ApplyColorPalette(Helium9_colorScheme);
      Full_MC_Stack_FORSUBTRACTION.ApplyColorPalette(Helium9_colorScheme);
      Empty_MC_Stack_FORSUBTRACTION.ApplyColorPalette(Helium9_colorScheme);
    }
  ////////////////////////////////////////////////////////////////
  //// FUll and Empty
  ////////////////////////////////////////////////////////////////
  auto Full_MC_Stack_array = Full_MC_Stack.GetHistArray();
  auto Empty_MC_Stack_array = Empty_MC_Stack.GetHistArray();
  ////////////////////////////////////////////////////////////////
  //// FUll - Empty
  ////////////////////////////////////////////////////////////////

  auto FULL_EMPTY_MC_Stack_array = Full_MC_Stack_FORSUBTRACTION.GetHistArray();
  auto EMPTY_forsubtract_MC_Stack_array = Empty_MC_Stack_FORSUBTRACTION.GetHistArray();

  if(Debug == true){std::cout << "Passed Making Arrary of Full - Empty Hist "<< Stack_Name<<std::endl;}
  ////////////////////////////////////////////////////////////////
  //// Scale and Normalization of Hist
  ////////////////////////////////////////////////////////////////

  double x1, x2, y1, y2;
  MnvH1D *hist_b;
  MnvH1D *hist_bp1;


  if(Debug == true){std::cout << "Starting Full, Empty, and Full - Empty plotting loop"<< Stack_Name<<std::endl;}


  for (int fullOrEmpty = 0; fullOrEmpty < 3; fullOrEmpty ++) {

    if(fullOrEmpty==0){
      int j=0;

      for(auto cat : Full_MC_Stack_array){

        if(Debug == true){std::cout << "In Loop On element For Full Stacks "<< j <<std::endl;}

        if(DoBinwidthNorm==true){
          ((PlotUtils::MnvH1D*)Full_MC_Stack_array.At(j))->Scale(1.0,"width");
        }

        ((PlotUtils::MnvH1D*)Full_MC_Stack_array.At(j))->Scale(scale_to_FULLData[0]);
        j++;
      }

      if(Debug == true){std::cout << "inside plotting Loop on element:"<< fullOrEmpty<<std::endl;}

      hist_b = (MnvH1D*)inputFile_DATAFULL -> Get(histoName_Data);
      if(Debug == true){std::cout << "Initialize Got Full Data for FULL Stacks   "<< Stack_Name<<std::endl;}

      if(DoBinwidthNorm==true)
      {
        hist_b->Scale(1.0,"width");
      }

    }

    else if (fullOrEmpty==1)
    {
      int k=0;
      for(auto cat : Empty_MC_Stack_array){

        if(Debug == true){std::cout << "In Loop On element For Empty Stacks "<< k <<std::endl;}

        if(DoBinwidthNorm==true){
          ((PlotUtils::MnvH1D*)Empty_MC_Stack_array.At(k))->Scale(1.0,"width");
        }

        ((PlotUtils::MnvH1D*)Empty_MC_Stack_array.At(k))->Scale(scale_to_FULLData[1]);
        k++;
      }

      hist_b = (MnvH1D*)inputFile_DATAEMPTY -> Get(histoName_Data);
      if(Debug == true){std::cout << "Initialize Got Empty Data for EMTPY Stacks   "<< Stack_Name<<std::endl;}

      if(DoBinwidthNorm==true){

        hist_b->Scale(1.0,"width");
      }
      hist_b->Scale(scale_to_FULLData[3]);
    }


    else if (fullOrEmpty==2)
    {

      int i=0;
      for(auto cat : FULL_EMPTY_MC_Stack_array) {

        if(Debug == true){std::cout << "In Loop On element For Full - Empty Stacks "<< i <<std::endl;}

        if(DoBinwidthNorm==true){
          ((PlotUtils::MnvH1D*)EMPTY_forsubtract_MC_Stack_array.At(i))->Scale(1.0,"width");
          ((PlotUtils::MnvH1D*)FULL_EMPTY_MC_Stack_array.At(i))->Scale(1.0,"width");


        }

        ((PlotUtils::MnvH1D*)FULL_EMPTY_MC_Stack_array.At(i))->Scale(scale_to_FULLData[0]);
        ((PlotUtils::MnvH1D*)EMPTY_forsubtract_MC_Stack_array.At(i))->Scale(scale_to_FULLData[1]);

        ((PlotUtils::MnvH1D*)FULL_EMPTY_MC_Stack_array.At(i))->Add(((PlotUtils::MnvH1D*)EMPTY_forsubtract_MC_Stack_array.At(i)), -1);
        i++;

      }

      hist_b = (MnvH1D*)inputFile_DATAFULL -> Get(histoName_Data);
      hist_bp1 = (MnvH1D*)inputFile_DATAEMPTY -> Get(histoName_Data);
      if(Debug == true){std::cout << "Initialize Got Empty + FULL Data for Full - EMTPY Stacks   "<< Stack_Name<<std::endl;}

      if(DoBinwidthNorm==true)
      {
        hist_b->Scale(1.0,"width");
        hist_bp1->Scale(1.0,"width");
      }

      hist_bp1->Scale(scale_to_FULLData[3]);  // Empty Data
      hist_b -> Add(hist_bp1, -1); // data doesn't need to be scaled


    }

    if(Debug == true){std::cout << "Done Scaling and Bin Width Normalization on element: "<< fullOrEmpty<<std::endl;}
    ////////////////////////////////////////////////////////////////
    ////Time to Plot
    ////////////////////////////////////////////////////////////////

    char emptyFull[1024];
    if (fullOrEmpty == 1) {sprintf(emptyFull, " (Empty) ");}
    else  if (fullOrEmpty == 0) {sprintf(emptyFull, " (Full) ");}
    else  if (fullOrEmpty == 2) {sprintf(emptyFull, " (F-E) ");}

    //plot->DecodeLegendPosition(x1, y1, x2, y2, "R", 2, 2, .03);
    mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", .5, 10, .025);
    //TLegend *legend = new TLegend(x1 - .05, y1 + .1, x2 + .05, y2 + .1);
    TLegend *legend = new TLegend(x1 - .02, y1+.31 , x2 +.06 , y2 + .42  );
    legend->SetNColumns(1);
    legend->SetTextSize(.03);
    legend->SetFillColor(0);

    char ytitle[100];
    //int units_n = ;
    char units_char[units.length()+1];
    strcpy( units_char,units.c_str());

    double binwidth_title = hist_b -> GetBinWidth(3);
    sprintf(ytitle, "Number of Events / %.2f %s", binwidth_title, units_char); //
    //hist_a->SetFillColor(1);


//    bool statPlusSys           = true;
  ///  bool useHistTitles         = false;

    if(Debug == true){std::cout << "in loop using DrawDataStackedMC function.  on loop Element: "<< fullOrEmpty<<std::endl;}

    if(fullOrEmpty==0){
      mnvPlotter.draw_normalized_to_bin_width=false;
      mnvPlotter.DrawDataStackedMC(hist_b, &Full_MC_Stack_array, 1.0, "TR", "Data", -1, -1,
      1001, xaxislabel.c_str(), ytitle, false);
      hist_b -> Clear();
    }

    else if(fullOrEmpty==1){
      mnvPlotter.draw_normalized_to_bin_width=false;
      mnvPlotter.DrawDataStackedMC(hist_b, &Empty_MC_Stack_array, 1.0, "TR", "Data", -1, -1,
      1001, xaxislabel.c_str(), ytitle, false);
      hist_b -> Clear();
    }

    else  if(fullOrEmpty==2){
      mnvPlotter.draw_normalized_to_bin_width=false;
      mnvPlotter.DrawDataStackedMC(hist_b, &FULL_EMPTY_MC_Stack_array, 1.0, "TR", "Data", -1, -1,
      1001, xaxislabel.c_str(), ytitle, false);
      hist_b -> Clear();
      hist_bp1 -> Clear();
    }

    //               char chi_label[1024];

    // sprintf(chi_label, "#chi^{2}/ndf = %.2f / %i", chi_2,ndf);
    //legend -> AddEntry((TObject*)0, chi_label, "");
    //legend -> Draw();
    //mnvPlotter.AddPlotLabel (chi_label, const double x, const double y);
    char total_title[1024];
    sprintf(total_title, "%s%s%s", histotitle, emptyFull,"(POT Norm)");
    mnvPlotter.AddHistoTitle(total_title, .04);
    mnvPlotter.WritePreliminary("TL", .035, 0, 0, false);
    std::string plotname = Form("%s",pdf_label.c_str());
    mnvPlotter.MultiPrint(&cE, plotname, "pdf");
    //mnvPlotter.error_summary_group_map = ::errorGroups;

  }

  cE.Closed();

}

///////////////////////////////////////////////////////////////////////////////

void DrawSTACK_FORDATAONLY_fromHistFilio_FromTFile( TFile *inputFile_DATAFULL,TFile *inputFile_DATAEMPTY, char *histoName_Data, Pot_MapStatusList POT_DATA, bool TrueifFullelseEmpty, char *histotitle,
  std::string xaxislabel, std::string pdf_label, bool DoBinwidthNorm, std::string units, StackType STACKTYPE, bool Debug )
  {    //helium_Status kEMPTY, kFULL;
    PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
    //PlotUtils::MnvPlotter mnvPlotter();
    mnvPlotter.legend_n_columns = 2;
    double ScaleTOEmptyTOFULL_Data = POT_DATA[kFULL]/POT_DATA[kEMPTY];

    TCanvas cE ("c1","c1");
    std::cout<<"trying data HisName = "<< histoName_Data<<std::endl;

    char Stack_Name[1024];


     if(STACKTYPE==kTrackType){ sprintf(Stack_Name, "%s_Track",histoName_Data);}
    else if(STACKTYPE==kVertexOptions){ sprintf(Stack_Name, "%s_VertexOptions",histoName_Data);}
    else if(STACKTYPE==kboolNTrack){ sprintf(Stack_Name, "%s_boolNTrack",histoName_Data);}
    else{std::cout<<"Error unknown stack type: Ploting Failed"<<std::endl; return;}

    if(Debug == true){std::cout << "Getting Hist Using Name: "<< Stack_Name <<std::endl;}

    PlotUtils::HistFolio<PlotUtils::MnvH1D> Full_DATA_Stack(
      PlotUtils::LoadHistFolioFromFile<PlotUtils::MnvH1D>(
        *inputFile_DATAFULL, std::string(Stack_Name)),
        "Full_DATA_Stack");

    if(Debug == true){std::cout << "Initialize Got FUll MC for Stacks   "<< Stack_Name<<std::endl;}


    PlotUtils::HistFolio<PlotUtils::MnvH1D> Empty_DATA_Stack(
      PlotUtils::LoadHistFolioFromFile<PlotUtils::MnvH1D>(
        *inputFile_DATAEMPTY, std::string(Stack_Name)),
        "Empty_DATA_Stack");

    if(Debug == true){std::cout << "Initialize Got Empty MC for Stacks   "<< Stack_Name<<std::endl;}

    PlotUtils::HistFolio<PlotUtils::MnvH1D> Full_DATA_Stack_FORSUBTRACTION(
      PlotUtils::LoadHistFolioFromFile<PlotUtils::MnvH1D>(
        *inputFile_DATAFULL, std::string(Stack_Name)),
        "Full_DATA_Stack_FORSUBTRACTION");

    if(Debug == true){std::cout << "Initialize Got FUll MC for Stacks   "<< Stack_Name<<std::endl;}

    PlotUtils::HistFolio<PlotUtils::MnvH1D> Empty_DATA_Stack_FORSUBTRACTION(
      PlotUtils::LoadHistFolioFromFile<PlotUtils::MnvH1D>(
        *inputFile_DATAEMPTY, std::string(Stack_Name)),
        "Empty_DATA_Stack_FORSUBTRACTION");

    if(Debug == true){std::cout << "Initialize Got Emtpy MC for Stacks   "<< Stack_Name<<std::endl;}
    std::vector<int> Helium9_colorScheme = {
      TColor::GetColor("#EEFF00"), // neonyellow,
      TColor::GetColor("#DF00FF"), //'psychedelic Purple
      TColor::GetColor("#ffc922"), //'sunset yellow'
      TColor::GetColor("#87CEEB"),//'skyblue'
      TColor::GetColor("#0859C6"), //blue
      TColor::GetColor("#654522"), // yellowishbrown,
      TColor::GetColor(  43, 206,  72 ), //green
      TColor::GetColor("#FF0800"),//2 candy Apple
      TColor::GetColor("#90AD1C"),
      TColor::GetColor("#BABABA"), //Gray
      TColor::GetColor("#00FFFF"),//'aqua'
      TColor::GetColor("#F1B6DA"),//pink
      TColor::GetColor("#00A86B"),//'Jade'
      TColor::GetColor("#FAFAD2"),  // LightGoldenRodYellow
      TColor::GetColor("#800000"),  // Maroon
      TColor::GetColor("#555555"),  // dark grey
      TColor::GetColor(0, 153, 143 ), //turquoise
      TColor::GetColor("#654522"), // yellowishbrown,
      TColor::GetColor("#8db600"), // yellowgreen,
      TColor::GetColor("#D3D3D3"),  //'lightgrey'
       TColor::GetColor("#90AD1C"),
       TColor::GetColor("#CCDDAA")
    };


  ////////////////////////////////////////////////////////////////
  //// FUll and Empty
  ////////////////////////////////////////////////////////////////
  auto Full_DATA_Stack_array = Full_DATA_Stack.GetHistArray();
  auto Empty_DATA_Stack_array = Empty_DATA_Stack.GetHistArray();
  ////////////////////////////////////////////////////////////////
  //// FUll - Empty
  ////////////////////////////////////////////////////////////////

  auto FULL_EMPTY_DATA_Stack_array = Full_DATA_Stack_FORSUBTRACTION.GetHistArray();
  auto EMPTY_forsubtract_DATA_Stack_array = Empty_DATA_Stack_FORSUBTRACTION.GetHistArray();

  if(Debug == true){std::cout << "Passed Making Arrary of Full - Empty Hist "<< Stack_Name<<std::endl;}
  ////////////////////////////////////////////////////////////////
  //// Scale and Normalization of Hist
  ////////////////////////////////////////////////////////////////

  double x1, x2, y1, y2;
  MnvH1D *hist_b;
  MnvH1D *hist_bp1;


  if(Debug == true){std::cout << "Starting Full, Empty, and Full - Empty plotting loop"<< Stack_Name<<std::endl;}


  for (int fullOrEmpty = 0; fullOrEmpty < 3; fullOrEmpty ++) {

    if(fullOrEmpty==0){
      int j=0;

      for(auto cat : Full_DATA_Stack_array){

        if(Debug == true){std::cout << "In Loop On element For Full Stacks "<< j <<std::endl;}

        if(DoBinwidthNorm==true){
          ((PlotUtils::MnvH1D*)Full_DATA_Stack_array.At(j))->Scale(1.0,"width");
        }

        j++;
      }

      if(Debug == true){std::cout << "inside plotting Loop on element:"<< fullOrEmpty<<std::endl;}

      hist_b = (MnvH1D*)inputFile_DATAFULL -> Get(histoName_Data);
      if(Debug == true){std::cout << "Initialize Got Full Data for FULL Stacks   "<< Stack_Name<<std::endl;}

      if(DoBinwidthNorm==true)
      {
        hist_b->Scale(1.0,"width");
      }

    }

    else if (fullOrEmpty==1)
    {
      int k=0;
      for(auto cat : Empty_DATA_Stack_array){

        if(Debug == true){std::cout << "In Loop On element For Empty Stacks "<< k <<std::endl;}



        ((PlotUtils::MnvH1D*)Empty_DATA_Stack_array.At(k))->Scale(ScaleTOEmptyTOFULL_Data);

        if(DoBinwidthNorm==true){
          ((PlotUtils::MnvH1D*)Empty_DATA_Stack_array.At(k))->Scale(1.0,"width");
        }


        k++;
      }

      hist_b = (MnvH1D*)inputFile_DATAEMPTY -> Get(histoName_Data);
      if(Debug == true){std::cout << "Initialize Got Empty Data for EMTPY Stacks   "<< Stack_Name<<std::endl;}

      if(DoBinwidthNorm==true){

        hist_b->Scale(1.0,"width");
      }
      hist_b->Scale(ScaleTOEmptyTOFULL_Data);
    }

    else if (fullOrEmpty==2)
    {

      int i=0;
      for(auto cat : FULL_EMPTY_DATA_Stack_array) {

        if(Debug == true){std::cout << "In Loop On element For Full - Empty Stacks "<< i <<std::endl;}

        ((PlotUtils::MnvH1D*)FULL_EMPTY_DATA_Stack_array.At(i))->Scale(1.0);
        ((PlotUtils::MnvH1D*)EMPTY_forsubtract_DATA_Stack_array.At(i))->Scale(ScaleTOEmptyTOFULL_Data);

        ((PlotUtils::MnvH1D*)FULL_EMPTY_DATA_Stack_array.At(i))->Add(((PlotUtils::MnvH1D*)EMPTY_forsubtract_DATA_Stack_array.At(i)), -1);

        if(DoBinwidthNorm==true){
          //((PlotUtils::MnvH1D*)EMPTY_forsubtract_MC_Stack_array.At(i))->Scale(1.0,"width");
          ((PlotUtils::MnvH1D*)FULL_EMPTY_DATA_Stack_array.At(i))->Scale(1.0,"width");
        }


        i++;

      }

      hist_b = (MnvH1D*)inputFile_DATAFULL -> Get(histoName_Data);
      hist_bp1 = (MnvH1D*)inputFile_DATAEMPTY -> Get(histoName_Data);
      if(Debug == true){std::cout << "Initialize Got Empty + FULL Data for Full - EMTPY Stacks   "<< Stack_Name<<std::endl;}

      if(DoBinwidthNorm==true)
      {
        hist_b->Scale(1.0,"width");
        hist_bp1->Scale(1.0,"width");
      }

      hist_bp1->Scale(ScaleTOEmptyTOFULL_Data);  // Empty Data
      hist_b -> Add(hist_bp1, -1); // data doesn't need to be scaled


    }

    if(Debug == true){std::cout << "Done Scaling and Bin Width Normalization on element: "<< fullOrEmpty<<std::endl;}
    ////////////////////////////////////////////////////////////////
    ////Time to Plot
    ////////////////////////////////////////////////////////////////

    char emptyFull[1024];
    if (fullOrEmpty == 1) {sprintf(emptyFull, " (Empty) ");}
    else  if (fullOrEmpty == 0) {sprintf(emptyFull, " (Full) ");}
    else  if (fullOrEmpty == 2) {sprintf(emptyFull, " (F-E) ");}

    //plot->DecodeLegendPosition(x1, y1, x2, y2, "R", 2, 2, .03);
    mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", .5, 10, .025);
    //TLegend *legend = new TLegend(x1 - .05, y1 + .1, x2 + .05, y2 + .1);
    TLegend *legend = new TLegend(x1 - .02, y1+.31 , x2 +.06 , y2 + .42  );
    legend->SetNColumns(1);
    legend->SetTextSize(.03);
    legend->SetFillColor(0);

    char ytitle[100];
    //int units_n = ;
    char units_char[units.length()+1];
    strcpy( units_char,units.c_str());

    double binwidth_title = hist_b -> GetBinWidth(3);
    sprintf(ytitle, "Number of Events / %.2f %s", binwidth_title, units_char); //
    //hist_a->SetFillColor(1);


    //bool statPlusSys           = true;
    //bool useHistTitles         = false;

    if(Debug == true){std::cout << "in loop using DrawDataStackedMC function.  on loop Element: "<< fullOrEmpty<<std::endl;}

    if(fullOrEmpty==0){
      mnvPlotter.draw_normalized_to_bin_width=false;
      mnvPlotter.DrawDataStackedMC(hist_b, &Full_DATA_Stack_array, 1.0, "TR", "Data", -1, -1,
      1001, xaxislabel.c_str(), ytitle, false);
      hist_b -> Clear();
    }

    else if(fullOrEmpty==1){
      mnvPlotter.draw_normalized_to_bin_width=false;
      mnvPlotter.DrawDataStackedMC(hist_b, &Empty_DATA_Stack_array, 1.0, "TR", "Data", -1, -1,
      1001, xaxislabel.c_str(), ytitle, false);
      hist_b -> Clear();
    }

    else  if(fullOrEmpty==2){
      mnvPlotter.draw_normalized_to_bin_width=false;
      mnvPlotter.DrawDataStackedMC(hist_b, &FULL_EMPTY_DATA_Stack_array, 1.0, "TR", "Data", -1, -1,
      1001, xaxislabel.c_str(), ytitle, false);
      hist_b -> Clear();
      hist_bp1 -> Clear();
    }

    //               char chi_label[1024];

    // sprintf(chi_label, "#chi^{2}/ndf = %.2f / %i", chi_2,ndf);
    //legend -> AddEntry((TObject*)0, chi_label, "");
    //legend -> Draw();
    //mnvPlotter.AddPlotLabel (chi_label, const double x, const double y);
    char total_title[1024];
    sprintf(total_title, "%s%s%s", histotitle, emptyFull,"(POT Norm)");
    mnvPlotter.AddHistoTitle(total_title, .04);
    mnvPlotter.WritePreliminary("TL", .035, 0, 0, false);
    std::string plotname = Form("%s",pdf_label.c_str());
    mnvPlotter.MultiPrint(&cE, plotname, "pdf");
    //mnvPlotter.error_summary_group_map = ::errorGroups;

  }

  cE.Closed();

}

////////////////////////////////////////////////////
//////
////////////////////////////////////////////////////


void DrawSTACKfromHistFilio_FromTFileNoData(TFile *inputFile_MCFULL, TFile *inputFile_MCEMPTY,  char *histoName_MC ,
  Pot_MapStatusList POT_MC, Pot_MapStatusList POT_DATA, char *histotitle, std::string xaxislabel, std::string pdf_label,
   bool DoBinwidthNorm, std::string units, StackType STACKTYPE, bool Debug, bool SetMaximum, double Maximum_group  )
  {    //helium_Status kEMPTY, kFULL;
    PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
    //PlotUtils::MnvPlotter mnvPlotter();
    mnvPlotter.legend_n_columns = 2;
    double scale_to_FULLData[4] = {POT_DATA[kFULL]/POT_MC[kFULL],  POT_DATA[kFULL]/POT_MC[kEMPTY]  , 1.0 , POT_DATA[kFULL]/POT_DATA[kEMPTY]  };

    TCanvas cE ("c1","c1");
    std::cout<<"Ploting MC only"<<std::endl;
    std::cout<<"trying MC HisName = "<< histoName_MC<<std::endl;

    char Stack_Name[1024];

    if(STACKTYPE==kMaterial){sprintf(Stack_Name, "%s_Material",histoName_MC);}
    else if(STACKTYPE==kInteraction){ sprintf(Stack_Name, "%s_Interaction",histoName_MC);}
    else if(STACKTYPE==kParticle){ sprintf(Stack_Name, "%s_Particle",histoName_MC);}
    else if(STACKTYPE==kCryoTankRegions){ sprintf(Stack_Name, "%s_REGION",histoName_MC);}
    else{std::cout<<"Error unknown stack type: Ploting Failed"<<std::endl; return;}

    if(Debug == true){std::cout << "Getting Hist Using Name: "<< Stack_Name <<std::endl;}

    PlotUtils::HistFolio<PlotUtils::MnvH1D> Full_MC_Stack(
      PlotUtils::LoadHistFolioFromFile<PlotUtils::MnvH1D>(
        *inputFile_MCFULL, std::string(Stack_Name)),
        "Full_MC_Stack");

    if(Debug == true){std::cout << "Initialize Got FUll MC for Stacks   "<< Stack_Name<<std::endl;}


    PlotUtils::HistFolio<PlotUtils::MnvH1D> Empty_MC_Stack(
      PlotUtils::LoadHistFolioFromFile<PlotUtils::MnvH1D>(
        *inputFile_MCEMPTY, std::string(Stack_Name)),
        "Empty_MC_Stack");

    if(Debug == true){std::cout << "Initialize Got Empty MC for Stacks   "<< Stack_Name<<std::endl;}

    PlotUtils::HistFolio<PlotUtils::MnvH1D> Full_MC_Stack_FORSUBTRACTION(
      PlotUtils::LoadHistFolioFromFile<PlotUtils::MnvH1D>(
        *inputFile_MCFULL, std::string(Stack_Name)),
        "Full_MC_Stack_FORSUBTRACTION");

    if(Debug == true){std::cout << "Initialize Got FUll MC for Stacks   "<< Stack_Name<<std::endl;}

    PlotUtils::HistFolio<PlotUtils::MnvH1D> Empty_MC_Stack_FORSUBTRACTION(
      PlotUtils::LoadHistFolioFromFile<PlotUtils::MnvH1D>(
        *inputFile_MCEMPTY, std::string(Stack_Name)),
        "Empty_MC_Stack_FORSUBTRACTION");

    if(Debug == true){std::cout << "Initialize Got Emtpy MC for Stacks   "<< Stack_Name<<std::endl;}
    std::vector<int> Helium9_colorScheme = {
      TColor::GetColor("#EEFF00"), // neonyellow,
      TColor::GetColor("#DF00FF"), //'psychedelic Purple
      TColor::GetColor("#ffc922"), //'sunset yellow'
      TColor::GetColor("#87CEEB"),//'skyblue'
      TColor::GetColor("#0859C6"), //blue
      TColor::GetColor("#654522"), // yellowishbrown,
      TColor::GetColor(  43, 206,  72 ), //green
      TColor::GetColor("#FF0800"),//2 candy Apple
      TColor::GetColor("#90AD1C"),
      TColor::GetColor("#BABABA"), //Gray
      TColor::GetColor("#00FFFF"),//'aqua'
      TColor::GetColor("#F1B6DA"),//pink
      TColor::GetColor("#00A86B"),//'Jade'
      TColor::GetColor("#FAFAD2"),  // LightGoldenRodYellow
      TColor::GetColor("#800000"),  // Maroon
      TColor::GetColor("#555555"),  // dark grey
      TColor::GetColor(0, 153, 143 ), //turquoise
      TColor::GetColor("#654522"), // yellowishbrown,
      TColor::GetColor("#8db600"), // yellowgreen,
      TColor::GetColor("#D3D3D3"),  //'lightgrey'
       TColor::GetColor("#90AD1C"),
       TColor::GetColor("#CCDDAA")
    };

    if(STACKTYPE==kParticle)
    {
      Full_MC_Stack.ApplyColorPalette(Helium9_colorScheme);
      Empty_MC_Stack.ApplyColorPalette(Helium9_colorScheme);
      Full_MC_Stack_FORSUBTRACTION.ApplyColorPalette(Helium9_colorScheme);
      Empty_MC_Stack_FORSUBTRACTION.ApplyColorPalette(Helium9_colorScheme);
    }
  ////////////////////////////////////////////////////////////////
  //// FUll and Empty
  ////////////////////////////////////////////////////////////////
  auto Full_MC_Stack_array = Full_MC_Stack.GetHistArray();
  auto Empty_MC_Stack_array = Empty_MC_Stack.GetHistArray();
  ////////////////////////////////////////////////////////////////
  //// FUll - Empty
  ////////////////////////////////////////////////////////////////

  auto FULL_EMPTY_MC_Stack_array = Full_MC_Stack_FORSUBTRACTION.GetHistArray();
  auto EMPTY_forsubtract_MC_Stack_array = Empty_MC_Stack_FORSUBTRACTION.GetHistArray();

  if(Debug == true){std::cout << "Passed Making Arrary of Full - Empty Hist "<< Stack_Name<<std::endl;}
  ////////////////////////////////////////////////////////////////
  //// Scale and Normalization of Hist
  ////////////////////////////////////////////////////////////////

  double x1, x2, y1, y2;

  if(Debug == true){std::cout << "Starting Full, Empty, and Full - Empty plotting loop"<< Stack_Name<<std::endl;}


  for (int fullOrEmpty = 0; fullOrEmpty < 3; fullOrEmpty ++) {

    if(fullOrEmpty==0){
      int j=0;

      for(auto cat : Full_MC_Stack_array){

        if(Debug == true){std::cout << "In Loop On element For Full Stacks "<< j <<std::endl;}

        if(DoBinwidthNorm==true){
          ((PlotUtils::MnvH1D*)Full_MC_Stack_array.At(j))->Scale(1.0,"width");
        }

        ((PlotUtils::MnvH1D*)Full_MC_Stack_array.At(j))->Scale(scale_to_FULLData[0]);
        j++;
      }

      if(Debug == true){std::cout << "inside plotting Loop on element:"<< fullOrEmpty<<std::endl;}


    }

    else if (fullOrEmpty==1)
    {
      int k=0;
      for(auto cat : Empty_MC_Stack_array){

        if(Debug == true){std::cout << "In Loop On element For Empty Stacks "<< k <<std::endl;}

        if(DoBinwidthNorm==true){
          ((PlotUtils::MnvH1D*)Empty_MC_Stack_array.At(k))->Scale(1.0,"width");
        }

        ((PlotUtils::MnvH1D*)Empty_MC_Stack_array.At(k))->Scale(scale_to_FULLData[1]);
        k++;
      }
    }


    else if (fullOrEmpty==2)
    {
      int i=0;
      for(auto cat : FULL_EMPTY_MC_Stack_array) {

        if(Debug == true){std::cout << "In Loop On element For Full - Empty Stacks "<< i <<std::endl;}

        if(DoBinwidthNorm==true){
          ((PlotUtils::MnvH1D*)EMPTY_forsubtract_MC_Stack_array.At(i))->Scale(1.0,"width");
          ((PlotUtils::MnvH1D*)FULL_EMPTY_MC_Stack_array.At(i))->Scale(1.0,"width");


        }

        ((PlotUtils::MnvH1D*)FULL_EMPTY_MC_Stack_array.At(i))->Scale(scale_to_FULLData[0]);
        ((PlotUtils::MnvH1D*)EMPTY_forsubtract_MC_Stack_array.At(i))->Scale(scale_to_FULLData[1]);

        ((PlotUtils::MnvH1D*)FULL_EMPTY_MC_Stack_array.At(i))->Add(((PlotUtils::MnvH1D*)EMPTY_forsubtract_MC_Stack_array.At(i)), -1);
        i++;

      }

    }

    if(Debug == true){std::cout << "Done Scaling and Bin Width Normalization on element: "<< fullOrEmpty<<std::endl;}
    ////////////////////////////////////////////////////////////////
    ////Time to Plot
    ////////////////////////////////////////////////////////////////

    char emptyFull[1024];
    if (fullOrEmpty == 1) {sprintf(emptyFull, " (Empty) ");}
    else  if (fullOrEmpty == 0) {sprintf(emptyFull, " (Full) ");}
    else  if (fullOrEmpty == 2) {sprintf(emptyFull, " (F-E) ");}

    //plot->DecodeLegendPosition(x1, y1, x2, y2, "R", 2, 2, .03);
    mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", .5, 10, .025);
    //TLegend *legend = new TLegend(x1 - .05, y1 + .1, x2 + .05, y2 + .1);
    TLegend *legend = new TLegend(x1 - .02, y1+.31 , x2 +.06 , y2 + .42  );
    legend->SetNColumns(1);
    legend->SetTextSize(.03);
    legend->SetFillColor(0);

    char ytitle[100];
    //int units_n = ;
    char units_char[units.length()+1];
    strcpy( units_char,units.c_str());

    double binwidth_title =   ((PlotUtils::MnvH1D*)Full_MC_Stack_array.At(0))->GetBinWidth(3);
    sprintf(ytitle, "Number of Events / %.2f %s", binwidth_title, units_char); //


    if(Debug == true){std::cout << "in loop using DrawDataStackedMC function.  on loop Element: "<< fullOrEmpty<<std::endl;}

    if(fullOrEmpty==0){
      mnvPlotter.draw_normalized_to_bin_width=false;
      if(SetMaximum==true){
        mnvPlotter.axis_maximum= Maximum_group;
        mnvPlotter.axis_maximum_group = Maximum_group;}
      mnvPlotter.DrawStackedMC(&Full_MC_Stack_array, 1.0, "TR", -1, -1,
      1001, xaxislabel.c_str(), ytitle);
    }

    else if(fullOrEmpty==1){
      mnvPlotter.draw_normalized_to_bin_width=false;
      if(SetMaximum==true){
          mnvPlotter.axis_maximum= Maximum_group;
          mnvPlotter.axis_maximum_group = Maximum_group;}
      mnvPlotter.DrawStackedMC(&Empty_MC_Stack_array, 1.0, "TR", -1, -1,
      1001, xaxislabel.c_str(), ytitle);
    }

    else  if(fullOrEmpty==2){
      mnvPlotter.draw_normalized_to_bin_width=false;
      if(SetMaximum==true){
        mnvPlotter.axis_maximum= Maximum_group;
        mnvPlotter.axis_maximum_group = Maximum_group;}

      mnvPlotter.DrawStackedMC(&FULL_EMPTY_MC_Stack_array, 1.0, "TR", -1, -1,
      1001, xaxislabel.c_str(), ytitle);
    }

    //               char chi_label[1024];

    // sprintf(chi_label, "#chi^{2}/ndf = %.2f / %i", chi_2,ndf);
    //legend -> AddEntry((TObject*)0, chi_label, "");
    //legend -> Draw();
    //mnvPlotter.AddPlotLabel (chi_label, const double x, const double y);
    char total_title[1024];
    sprintf(total_title, "%s%s%s", histotitle, emptyFull,"(POT Norm)");
    mnvPlotter.AddHistoTitle(total_title, .04);
    mnvPlotter.WritePreliminary("TL", .02, 0, 0, false);
    std::string plotname = Form("%s",pdf_label.c_str());
    mnvPlotter.MultiPrint(&cE, plotname, "pdf");
    //mnvPlotter.error_summary_group_map = ::errorGroups;

  }

  cE.Closed();

}


///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void DrawSINGLESTACKMCHistFilio_FromTFile(TFile *inputFile_MCinput,  char *histoName_MC ,
  char *histotitle, std::string xaxislabel, std::string pdf_label,
  bool DoBinwidthNorm, bool Debug )
  {    //helium_Status kEMPTY, kFULL;
    //PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCompactStyle);
    // PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCNuPionIncStyle);
    PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
    //PlotUtils::MnvPlotter mnvPlotter();
    mnvPlotter.legend_n_columns = 2;

    TCanvas cE ("c1","c1");
    std::cout<<"trying MC HisName = "<< histoName_MC<<std::endl;

    char Stack_Name[1024];
    sprintf(Stack_Name, "%s",histoName_MC);

    if(Debug == true){std::cout << "Getting Hist Using Name: "<< Stack_Name <<std::endl;}

    PlotUtils::HistFolio<PlotUtils::MnvH1D> MC_Stack(
      PlotUtils::LoadHistFolioFromFile<PlotUtils::MnvH1D>(
        *inputFile_MCinput, std::string(Stack_Name)),
        "MC_Stack");

std::vector<int> Helium9_colorScheme = {
  TColor::GetColor("#EEFF00"), // neonyellow,
  TColor::GetColor("#DF00FF"), //'psychedelic Purple
  TColor::GetColor("#ffc922"), //'sunset yellow'
  TColor::GetColor("#87CEEB"),//'skyblue'
  TColor::GetColor("#0859C6"), //blue
  TColor::GetColor("#654522"), // yellowishbrown,
  TColor::GetColor(  43, 206,  72 ), //green
  TColor::GetColor("#FF0800"),//2 candy Apple
  TColor::GetColor("#90AD1C"),
  TColor::GetColor("#BABABA"), //Gray
  TColor::GetColor("#00FFFF"),//'aqua'
  TColor::GetColor("#F1B6DA"),//pink
  TColor::GetColor("#00A86B"),//'Jade'
  TColor::GetColor("#FAFAD2"),  // LightGoldenRodYellow
  TColor::GetColor("#800000"),  // Maroon
  TColor::GetColor("#555555"),  // dark grey
  TColor::GetColor(0, 153, 143 ), //turquoise
  TColor::GetColor("#654522"), // yellowishbrown,
  TColor::GetColor("#8db600"), // yellowgreen,
  TColor::GetColor("#D3D3D3"),  //'lightgrey'
   TColor::GetColor("#90AD1C"),
   TColor::GetColor("#CCDDAA")
};

        MC_Stack.ApplyColorPalette(Helium9_colorScheme);

  ////////////////////////////////////////////////////////////////
  //// Get array of Stack MC
  ////////////////////////////////////////////////////////////////
  auto MC_Stack_array = MC_Stack.GetHistArray();


  if(Debug == true){std::cout << "Passed Making Arrary of stack Hist "<< Stack_Name<<std::endl;}



  ////////////////////////////////////////////////////////////////
  //// Time to PLot
  ////////////////////////////////////////////////////////////////
  double x1, x2, y1, y2;

  if(Debug == true){std::cout << "Starting draw Single stack named: "<< Stack_Name<<std::endl;}
  int j=0;

  if(DoBinwidthNorm==true){
    for(auto cat : MC_Stack_array){
      if(Debug == true){std::cout <<  "Bin width Normlized Set to True on Hist( "<< j << " )"<<std::endl;}
      ((PlotUtils::MnvH1D*)MC_Stack_array.At(j))->Scale(1.0,"width");
      j++;
    }
  }

  if(Debug == true){std::cout << "inside plotting Loop on element: Single Stack"<<std::endl;}


  //plot->DecodeLegendPosition(x1, y1, x2, y2, "R", 2, 2, .03);
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", .5, 10, .025);
  //TLegend *legend = new TLegend(x1 - .05, y1 + .1, x2 + .05, y2 + .1);
  TLegend *legend = new TLegend(x1 - .02, y1+.31 , x2 +.06 , y2 + .42  );
  legend->SetNColumns(1);
  legend->SetTextSize(.03);
  legend->SetFillColor(0);

  char ytitle[100];
  char Xaxis_label_char[ xaxislabel.length()+1];
  strcpy( Xaxis_label_char,xaxislabel.c_str());

  sprintf(ytitle, "Number of Events "); //
//hist_a->SetFillColor(1);


if(Debug == true){std::cout << "in loop using DrawDataStackedMC function.  on loop Element: "<<std::endl;}

mnvPlotter.draw_normalized_to_bin_width=false;
mnvPlotter.DrawStackedMC(&MC_Stack_array, 1.0, "TR" , 2, 1, 1001, Xaxis_label_char, ytitle);

char total_title[1024];
sprintf(total_title, "Stack: %s", histotitle);
mnvPlotter.AddHistoTitle(total_title, .04);
mnvPlotter.WritePreliminary("TL", .03, 0, 0, false);
std::string plotname = Form("%s",pdf_label.c_str());
mnvPlotter.MultiPrint(&cE, plotname, "pdf");
cE.Closed();

}

void Draw_FourFitRegion_CryoTank(std::string pdf, TCanvas *can, MnvPlotter *plot)
{
  can->Clear();
  std::string Title;
  double x1, x2, y1, y2;
  plot->DecodeLegendPosition(x1, y1, x2, y2, "R", 6.5, 6., .025);
  TLegend *legend = new TLegend(x1 - .075, y1 + .25, x2 + .075, y2 + .25);

  auto CryoTankTGraphX_Z = Tank_Z_X_or_Y(true);
  auto CryoTankTGraphY_Z = Tank_Z_X_or_Y(false);
  auto UpstreamStart = Make_VertLineTgraph(40 ,2491.17, -1100, 2000);
  auto EndBarrel = Make_VertLineTgraph(40 ,3283.84, -1100, 2000);
  auto EndDSCap = Make_VertLineTgraph(40 ,3687.0, -1100, 2000);
  auto FirstPlaneMinerva = Make_VertLineTgraph(40 ,4293.04, -1100, 2000);
  auto FirstTargetMinerva = Make_VertLineTgraph(40 ,4525.0, -1100, 2000);

  CryoTankTGraphX_Z->GetXaxis()->CenterTitle();
  CryoTankTGraphX_Z->GetYaxis()->CenterTitle();
  CryoTankTGraphX_Z->GetXaxis()->SetTitle("Z [mm]");
  CryoTankTGraphX_Z->GetYaxis()->SetTitle("X [mm]");
  CryoTankTGraphX_Z->GetXaxis()->SetTitleSize(0.038);
  CryoTankTGraphX_Z->GetYaxis()->SetTitleSize(0.038);
  CryoTankTGraphX_Z->SetLineColor(2);
  CryoTankTGraphX_Z->SetLineWidth(4);
  CryoTankTGraphX_Z->SetMarkerColor(1);
  CryoTankTGraphX_Z->SetMarkerSize(1);
  CryoTankTGraphX_Z->SetMarkerStyle(6);
  CryoTankTGraphX_Z->SetMaximum(1100.0);
  CryoTankTGraphX_Z->SetMinimum(-1100.0);
  TAxis *axis = CryoTankTGraphX_Z->GetXaxis();
  axis->SetLimits(2000.,5500.);



  CryoTankTGraphY_Z->GetXaxis()->CenterTitle();
  CryoTankTGraphY_Z->GetYaxis()->CenterTitle();
  CryoTankTGraphY_Z->GetXaxis()->SetTitle("Z [mm]");
  CryoTankTGraphY_Z->GetYaxis()->SetTitle("Y [mm]");
  CryoTankTGraphY_Z->GetXaxis()->SetTitleSize(0.038);
  CryoTankTGraphY_Z->GetYaxis()->SetTitleSize(0.038);
  CryoTankTGraphY_Z->SetLineColor(2);
  CryoTankTGraphY_Z->SetLineWidth(4);
  CryoTankTGraphY_Z->SetMarkerColor(1);
  CryoTankTGraphY_Z->SetMarkerSize(1);
  CryoTankTGraphY_Z->SetMarkerStyle(6);
  CryoTankTGraphY_Z->SetMaximum(1100.0);
  CryoTankTGraphY_Z->SetMinimum(-1100.0);
  TAxis *axis_2 = CryoTankTGraphY_Z->GetXaxis();
  axis_2->SetLimits(2000.,5500.);

  std::cout<<"starting CryoTank Interaction Plots"<<std::endl;

  SetLineForCryoPlots(*FirstPlaneMinerva, TColor::GetColor("#FF0800"));
  SetLineForCryoPlots(*FirstTargetMinerva, 1);

  SetLineForCryoPlots(*UpstreamStart, TColor::GetColor("#0859C6"));
  SetLineForCryoPlots(*EndBarrel,     TColor::GetColor("#DF00FF"));
  SetLineForCryoPlots(*EndDSCap,      TColor::GetColor("#ffc922"));


  legend->SetHeader("CryoTarget Fitting Regions","C");
  legend->AddEntry(UpstreamStart,"US Cap / Barrel","P");
  legend->AddEntry(EndBarrel,"Barrel / DS Cap","P");
  legend->AddEntry(EndDSCap,"DS Cap / DS Concave Cap","P");
  legend->AddEntry(FirstPlaneMinerva,"First Scintillator Plane","P");
  legend->AddEntry(FirstTargetMinerva,"MINER#nuA's Target 1","P");


  CryoTankTGraphX_Z->Draw("AP");
  FirstPlaneMinerva->Draw("Same P");
  FirstTargetMinerva->Draw("Same P");
  UpstreamStart->Draw("Same P");
  EndBarrel->Draw("Same P");
  EndDSCap->Draw("Same P");
  legend->SetTextSize(0.023);
  legend->Draw();

  Title = " X vs Z Cryo Fit Regions";
  plot->AddHistoTitle(Title.c_str(), .04);
  plot->WritePreliminary("TL", .035, 0, 0, false);


  gPad->Update();
  can->Modified();
  can->Print(pdf.c_str());

  can->Clear();


  CryoTankTGraphY_Z->Draw("AP");
  FirstPlaneMinerva->Draw("Same P");
  FirstTargetMinerva->Draw("Same P");
  UpstreamStart->Draw("Same P");
  EndBarrel->Draw("Same P");
  EndDSCap->Draw("Same P");
  Title = " Y vs Z Cryo Fit Regions";
  plot->AddHistoTitle(Title.c_str(), .04);
  plot->WritePreliminary("TL", .035, 0, 0, false);
  legend->SetTextSize(0.023);
  legend->Draw();

  gPad->Update();
  can->Modified();
  can->Print(pdf.c_str());

delete CryoTankTGraphY_Z;
delete CryoTankTGraphX_Z;
delete FirstPlaneMinerva;
delete FirstTargetMinerva;
delete UpstreamStart;
delete EndBarrel;
delete EndDSCap;

}



void SetLineForCryoPlots(TGraph &Tg_result, int color){

  Tg_result.SetMarkerColor(color);
  Tg_result.SetLineColor(color);
  Tg_result.SetMarkerSize(1);
  Tg_result.SetMarkerStyle(6);

}




void Draw2DHist_Full_Empty_TFILE(TFile *inputFile_Full,TFile *inputFile_Empty, const char* histoName,
  Pot_MapList POT_MC, ME_helium_Playlists PlayListFULL, ME_helium_Playlists PlayListEmpty,
  const char *Title, const char* xaxislabel,const char* yaxislabel, const char* pdf,
  TCanvas *can, MnvPlotter *plot)
{
  std::cout<<"trying 2D HisName  = "<< histoName<<std::endl;

  TH2D *h_mig_Full  = (TH2D*)inputFile_Full -> Get(histoName);
  TH2D *h_mig_Full_rowNorm = (TH2D*)h_mig_Full->Clone("h_mig_Full_rowNorm");
  rowNormalize(*h_mig_Full_rowNorm);
  TH2D *h_mig_Full_ColNorm = (TH2D*)h_mig_Full->Clone("h_mig_Full_ColNorm");
  colNormalize(*h_mig_Full_ColNorm);
  TH2D *h_mig_Empty  = (TH2D*)inputFile_Empty -> Get(histoName);
  TH2D *h_mig_Empty_rowNorm = (TH2D*)h_mig_Empty->Clone("h_mig_Empty_rowNorm");
  rowNormalize(*h_mig_Empty_rowNorm);
  TH2D *h_mig_Empty_ColNorm = (TH2D*)h_mig_Empty->Clone("h_mig_Empty_ColNorm");
  colNormalize(*h_mig_Empty_ColNorm);

  char Full_title[1024];
  auto Full_playlist_name = GetPlaylist_InitialName(PlayListFULL);
  auto Empty_playlist_name = GetPlaylist_InitialName(PlayListEmpty);

  char Full_playlist_name_char[Full_playlist_name.length()+1];
  strcpy(Full_playlist_name_char,Full_playlist_name.c_str());

  char Empty_playlist_name_char[Empty_playlist_name.length()+1];
  strcpy(Empty_playlist_name_char,Empty_playlist_name.c_str());



  sprintf(Full_title, "%s  (ME%s) (Full)",Title, Full_playlist_name_char);
  DrawMagration_heatMap(h_mig_Full,xaxislabel,yaxislabel,Full_title,pdf,can,plot);
  sprintf(Full_title, "%s (Row Norm) (ME%s) (Full)",Title, Full_playlist_name_char);
  DrawMagration_heatMap(h_mig_Full_rowNorm,xaxislabel,yaxislabel,Full_title,pdf,can,plot);
  sprintf(Full_title, "%s  (Column Norm) (ME%s) (Full)",Title, Full_playlist_name_char);
  DrawMagration_heatMap(h_mig_Full_ColNorm,xaxislabel,yaxislabel,Full_title,pdf,can,plot);

  sprintf(Full_title, "%s (ME%s) (Empty)",Title,Empty_playlist_name_char);
  DrawMagration_heatMap(h_mig_Empty,xaxislabel,yaxislabel,Full_title,pdf,can,plot);
  sprintf(Full_title, "%s (Row Norm) (ME%s)(Empty)",Title,Empty_playlist_name_char);
  DrawMagration_heatMap(h_mig_Empty_rowNorm,xaxislabel,yaxislabel,Full_title,pdf,can,plot);
  sprintf(Full_title, "%s (Column Norm) (ME%s) (Empty)",Title,Empty_playlist_name_char);
  DrawMagration_heatMap(h_mig_Empty_ColNorm,xaxislabel,yaxislabel,Full_title,pdf,can,plot);





  auto POT_scale_toFull= POT_MC[PlayListFULL]/POT_MC[PlayListEmpty];
  h_mig_Empty->Scale(POT_scale_toFull);
  h_mig_Full->Add(h_mig_Empty,-1);
  TH2D *h_mig_Full_EMPTY_rowNorm = (TH2D*)h_mig_Full->Clone("h_mig_Full_EMPTY_rowNorm");
  rowNormalize(*h_mig_Full_EMPTY_rowNorm);
  TH2D *h_mig_Full_EMPTY_ColNorm = (TH2D*)h_mig_Full->Clone("h_mig_Full_EMPTY_ColNorm");
  colNormalize(*h_mig_Full_EMPTY_ColNorm);

  sprintf(Full_title, "%s  (%s-%s)(F-E)",Title,Full_playlist_name_char,Empty_playlist_name_char);
  DrawMagration_heatMap(h_mig_Full,xaxislabel,yaxislabel,Full_title,pdf,can,plot);

  sprintf(Full_title, "%s  (Row Norm)(%s-%s)(F-E)",Title,Full_playlist_name_char, Empty_playlist_name_char);
  DrawMagration_heatMap(h_mig_Full_EMPTY_rowNorm,xaxislabel,yaxislabel,Full_title,pdf,can,plot);
  sprintf(Full_title, "%s  (Column Norm) (%s-%s)(F-E)",Title,Full_playlist_name_char,Empty_playlist_name_char);
  DrawMagration_heatMap(h_mig_Full_EMPTY_ColNorm,xaxislabel,yaxislabel,Full_title,pdf,can,plot);

}//end of 2D draw function


void MakeTrue_interactionPlots(std::vector <Trajector> input_vector,const char* Playlist ,double Spaceingcm ,const char* pdf, TCanvas *can, MnvPlotter *plot)
{
  char  pdf_mid[1024];
  char pdf_start[1024];
  char pdf_end[1024];
  //char XaxisName[1024];
  sprintf(pdf_start,"%s.pdf(",pdf);
  sprintf(pdf_mid,  "%s.pdf",pdf);
  sprintf(pdf_end,  "%s.pdf)",pdf);

  can -> Print(pdf_start);

  auto CryoTankTGraphX_Z = Tank_Z_X_or_Y(true);
  auto CryoTankTGraphY_Z = Tank_Z_X_or_Y(false);
  auto FirstPlaneMinerva = Make_VertLineTgraph(40 ,4293.04, -1100, 2000);
  auto FirstTargetMinerva = Make_VertLineTgraph(40 ,4525.0, -1100, 2000);

  CryoTankTGraphX_Z->GetXaxis()->CenterTitle();
  CryoTankTGraphX_Z->GetYaxis()->CenterTitle();
  CryoTankTGraphX_Z->GetXaxis()->SetTitle("Z [mm]");
  CryoTankTGraphX_Z->GetYaxis()->SetTitle("X [mm]");
  CryoTankTGraphX_Z->GetXaxis()->SetTitleSize(0.038);
  CryoTankTGraphX_Z->GetYaxis()->SetTitleSize(0.038);
  CryoTankTGraphX_Z->SetLineColor(2);
  CryoTankTGraphX_Z->SetLineWidth(4);
  CryoTankTGraphX_Z->SetMarkerColor(1);
  CryoTankTGraphX_Z->SetMarkerSize(1);
  CryoTankTGraphX_Z->SetMarkerStyle(20);
  CryoTankTGraphX_Z->SetMaximum(1100.0);
  CryoTankTGraphX_Z->SetMinimum(-1100.0);
  TAxis *axis = CryoTankTGraphX_Z->GetXaxis();
  axis->SetLimits(2000.,5500.);



  CryoTankTGraphY_Z->GetXaxis()->CenterTitle();
  CryoTankTGraphY_Z->GetYaxis()->CenterTitle();
  CryoTankTGraphY_Z->GetXaxis()->SetTitle("Z [mm]");
  CryoTankTGraphY_Z->GetYaxis()->SetTitle("X [mm]");
  CryoTankTGraphY_Z->GetXaxis()->SetTitleSize(0.038);
  CryoTankTGraphY_Z->GetYaxis()->SetTitleSize(0.038);
  CryoTankTGraphY_Z->SetLineColor(2);
  CryoTankTGraphY_Z->SetLineWidth(4);
  CryoTankTGraphY_Z->SetMarkerColor(1);
  CryoTankTGraphY_Z->SetMarkerSize(1);
  CryoTankTGraphY_Z->SetMarkerStyle(20);
  CryoTankTGraphY_Z->SetMaximum(1100.0);
  CryoTankTGraphY_Z->SetMinimum(-1100.0);
  TAxis *axis_2 = CryoTankTGraphY_Z->GetXaxis();
  axis_2->SetLimits(2000.,5500.);

  std::cout<<"starting CryoTank Interaction Plots"<<std::endl;

  FirstPlaneMinerva->SetLineColor(2);
  FirstTargetMinerva->SetLineColor(2);
  FirstPlaneMinerva->SetMarkerSize(1);
  FirstTargetMinerva->SetMarkerSize(1);
  FirstPlaneMinerva->SetMarkerStyle(1);
  FirstTargetMinerva->SetMarkerStyle(1);
  FirstPlaneMinerva->SetMarkerColor(1);
  FirstTargetMinerva->SetMarkerColor(1);



  for(auto cat : input_vector){
    // make vector of paramerization
    ////
    ///One Event for Single Plot
    ////
    //Run info
    auto  run = cat.RunInfo.run;
    auto  subrun = cat.RunInfo.subrun;
    auto  gate = cat.RunInfo.gate;
    auto  slice = cat.RunInfo.slice;

    char runinfo[1024];
    sprintf(runinfo, "(%i/%i/%i/%i)",run,subrun,gate,slice);





    double x1, x2, y1, y2;
    plot->DecodeLegendPosition(x1, y1, x2, y2, "R", 6.5, 6., .025);
    TLegend *legend = new TLegend(x1 + .075, y1 + .25, x2 + .075, y2 + .25);
    legend->AddEntry((TObject*)0, "Particle , KE[GeV]", "");
    TLegend *legend_2 = new TLegend(x1 + .075, y1 + .25, x2 + .075, y2 + .25);
    legend_2->AddEntry((TObject*)0, "Particle , KE[GeV]", "");


    auto Parameterizeparameters_ForEvent =  MakeParameterizelineParasTrajector_ParticeVectorForSingleTrajector(cat);
    char legend_title_x_z[1024];
    char legend_title_y_z[1024];
    char Full_title[1024];
    std::cout<<"Size of vector (Parameterizeparameters_ForEvent) =   "<< Parameterizeparameters_ForEvent.size()<<std::endl;
    CryoTankTGraphX_Z->Draw("AP");
    FirstPlaneMinerva->Draw("Same P");
    FirstTargetMinerva->Draw("Same P");
    int marker=2;
    for(auto dog :Parameterizeparameters_ForEvent ){
      //For a Single Particle in the Event
      //
      std::vector<Vertex_XYZ> PathVector_forParticle;

      auto Particle_name = GetcommonNamefromPDG(dog.pdg);
      char Particle_name_char[Particle_name.length()+1];
      strcpy(Particle_name_char,Particle_name.c_str());
      auto KE = dog.KE*.001;
      //std::cout<< "PDG in plotting pdg:"<< dog.pdg <<std::endl;
      //std::cout<< "PDG in plotting KE:"<< dog.KE <<std::endl;
      //std::cout<< "PDG in plotting Xo:"<< dog.Xo <<std::endl;
      //std::cout<< "PDG in plotting Yo:"<< dog.Yo <<std::endl;
      //std::cout<< "PDG in plotting Zo:"<< dog.Zo <<std::endl;

      //std::cout<< "PDG in plotting a"<< dog.a <<std::endl;
      //std::cout<< "PDG in plotting b"<< dog.b <<std::endl;
      //std::cout<< "PDG in plotting c"<< dog.c <<std::endl;

      if(dog.pdg==13)
      {
        PathVector_forParticle = MakeVectorofPath(dog, Spaceingcm, .40);
      }
      else {
        PathVector_forParticle = MakeVectorofPath(dog, Spaceingcm, 1.0);

      }

      //for(auto cat: PathVector_forParticle){std::cout<<"Printing out vector = (x,y,z) = ("<<cat.x <<","<<cat.y<<","<<cat.z<<") "<<"\n";}
      std::cout<<"~~~~~~~~~~~~~~~"<<std::endl;



      TGraph  *Tg_x = Make_X_vs_Z_Tgraph_fromVector(PathVector_forParticle);

      sprintf(legend_title_x_z, "%s , %.3f",Particle_name_char,KE);
      Tg_x->SetMarkerColor(marker);
      Tg_x->Draw("Same P");
      legend->AddEntry(Tg_x,legend_title_x_z,"p");
      marker++;
    }

    sprintf(Full_title, "Cryo True Trajectors X vs Z  %s",runinfo);
    string Title = string(Full_title);
    plot->AddHistoTitle(Title.c_str(), .04);
    plot->WritePreliminary("TL", .035, 0, 0, false);
    legend->SetTextSize(0.023);
    legend->Draw();

    gPad->Update();
    can->Modified();
    can->Print(pdf_mid);

    can->Clear();
    CryoTankTGraphY_Z->Draw("AP");
    FirstPlaneMinerva->Draw("Same P");
    FirstTargetMinerva->Draw("Same P");
    marker=2;
    for(auto dog :Parameterizeparameters_ForEvent ){
      //For a Single Particle in the Event
      //
      std::vector<Vertex_XYZ> PathVector_forParticle;

      auto Particle_name = GetcommonNamefromPDG(dog.pdg);
      char Particle_name_char[Particle_name.length()+1];
      strcpy(Particle_name_char,Particle_name.c_str());
      auto KE = dog.KE*.001;
      //std::cout<< "PDG in plotting pdg:"<< dog.pdg <<std::endl;
      //std::cout<< "PDG in plotting KE:"<< dog.KE <<std::endl;
      //std::cout<< "PDG in plotting Xo:"<< dog.Xo <<std::endl;
      //std::cout<< "PDG in plotting Yo:"<< dog.Yo <<std::endl;
      //std::cout<< "PDG in plotting Zo:"<< dog.Zo <<std::endl;

      //std::cout<< "PDG in plotting a"<< dog.a <<std::endl;
      //std::cout<< "PDG in plotting b"<< dog.b <<std::endl;
      //std::cout<< "PDG in plotting c"<< dog.c <<std::endl;
      if(dog.pdg==13)
      {
        PathVector_forParticle = MakeVectorofPath(dog, Spaceingcm, .40);
      }
      else {
        PathVector_forParticle = MakeVectorofPath(dog, Spaceingcm, 1.0);

      }

      TGraph  *Tg_y = Make_Y_vs_Z_Tgraph_fromVector(PathVector_forParticle);
      sprintf(legend_title_y_z, "%s , %.3f",Particle_name_char,KE);

      Tg_y->SetMarkerColor(marker);
      Tg_y->Draw("Same P");
      legend_2->AddEntry(Tg_y,legend_title_y_z,"p");
      marker++;
    }

    sprintf(Full_title, "Cryo True Trajectors Y vs Z  %s",runinfo);
    string thirdTitle = string(Full_title);
    plot->AddHistoTitle(thirdTitle.c_str(), .04);
    plot->WritePreliminary("TL", .035, 0, 0, false);
    legend_2->SetTextSize(0.023);
    legend_2->Draw();

    gPad->Update();
    can->Modified();
    can->Print(pdf_mid);

  }//end loop

  can->Print(pdf_end);

}//end of function;


void MakeTrue_interactionPlots_WithRECOtrajector(std::vector <Trajector> input_vector, std::vector <Trajector_withTrueEnergyFraction> input_vector_RECO,const char* Playlist ,double Spaceingcm ,const char* pdf, TCanvas *can, MnvPlotter *plot)
{
  char pdf_mid[1024];
  char pdf_start[1024];
  char pdf_end[1024];


  if (CheckIfTrajectors_VectorsHaveEqual_RunInfo(input_vector, input_vector_RECO)==true){std::cout<< "input trajector vector have same equal Run Info"<<std::endl;}
  else{std::cout<< "ERROR input trajector vector DONT have same equal Run Info ERROR "<<std::endl; return; }


  sprintf(pdf_start,"%s.pdf(",pdf);
  sprintf(pdf_mid,  "%s.pdf",pdf);
  sprintf(pdf_end,  "%s.pdf)",pdf);

  can -> Print(pdf_start);

  auto CryoTankTGraphX_Z = Tank_Z_X_or_Y(true);
  auto CryoTankTGraphY_Z = Tank_Z_X_or_Y(false);
  auto FirstPlaneMinerva = Make_VertLineTgraph(40 ,4293.04, -1100, 2000);
  auto FirstTargetMinerva = Make_VertLineTgraph(40 ,4525.0, -1100, 2000);

  CryoTankTGraphX_Z->GetXaxis()->CenterTitle();
  CryoTankTGraphX_Z->GetYaxis()->CenterTitle();
  CryoTankTGraphX_Z->GetXaxis()->SetTitle("Z [mm]");
  CryoTankTGraphX_Z->GetYaxis()->SetTitle("X [mm]");
  CryoTankTGraphX_Z->GetXaxis()->SetTitleSize(0.038);
  CryoTankTGraphX_Z->GetYaxis()->SetTitleSize(0.038);
  CryoTankTGraphX_Z->SetLineColor(2);
  CryoTankTGraphX_Z->SetLineWidth(4);
  CryoTankTGraphX_Z->SetMarkerColor(1);
  CryoTankTGraphX_Z->SetMarkerSize(1);
  CryoTankTGraphX_Z->SetMarkerStyle(20);
  CryoTankTGraphX_Z->SetMaximum(1100.0);
  CryoTankTGraphX_Z->SetMinimum(-1100.0);
  TAxis *axis = CryoTankTGraphX_Z->GetXaxis();
  axis->SetLimits(2000.,6500.);



  CryoTankTGraphY_Z->GetXaxis()->CenterTitle();
  CryoTankTGraphY_Z->GetYaxis()->CenterTitle();
  CryoTankTGraphY_Z->GetXaxis()->SetTitle("Z [mm]");
  CryoTankTGraphY_Z->GetYaxis()->SetTitle("Y [mm]");
  CryoTankTGraphY_Z->GetXaxis()->SetTitleSize(0.038);
  CryoTankTGraphY_Z->GetYaxis()->SetTitleSize(0.038);
  CryoTankTGraphY_Z->SetLineColor(2);
  CryoTankTGraphY_Z->SetLineWidth(4);
  CryoTankTGraphY_Z->SetMarkerColor(1);
  CryoTankTGraphY_Z->SetMarkerSize(1);
  CryoTankTGraphY_Z->SetMarkerStyle(20);
  CryoTankTGraphY_Z->SetMaximum(1100.0);
  CryoTankTGraphY_Z->SetMinimum(-1100.0);
  TAxis *axis_2 = CryoTankTGraphY_Z->GetXaxis();
  axis_2->SetLimits(2000.,6500.);

  std::cout<<"starting CryoTank Interaction Plots"<<std::endl;

  FirstPlaneMinerva->SetLineColor(2);
  FirstTargetMinerva->SetLineColor(2);
  FirstPlaneMinerva->SetMarkerSize(1);
  FirstTargetMinerva->SetMarkerSize(1);
  FirstPlaneMinerva->SetMarkerStyle(1);
  FirstTargetMinerva->SetMarkerStyle(1);
  FirstPlaneMinerva->SetMarkerColor(1);
  FirstTargetMinerva->SetMarkerColor(1);

  int Vector_count = 0;
  for(auto cat : input_vector){
    // make vector of paramerization
    ////
    ///One Event for Single Plot
    ////
    //Run info
    auto  run = cat.RunInfo.run;
    auto  subrun = cat.RunInfo.subrun;
    auto  gate = cat.RunInfo.gate;
    auto  slice = cat.RunInfo.slice;

    char runinfo[1024];
    sprintf(runinfo, "(%i/%i/%i/%i)",run,subrun,gate,slice);
    double x1, x2, y1, y2;
    plot->DecodeLegendPosition(x1, y1, x2, y2, "R", 6.5, 6., .025);
    TLegend *legend = new TLegend(x1 - .015, y1 + .25, x2 + .075, y2 + .3);
    legend->AddEntry((TObject*)0, "Particle , KE [GeV]", "");
    TLegend *legend_2 = new TLegend(x1 - .015, y1 + .25, x2 + .075, y2 + .3);
    legend_2->AddEntry((TObject*)0, "Particle , KE [GeV]", "");


    auto Parameterizeparameters_ForEvent =  MakeParameterizelineParasTrajector_ParticeVectorForSingleTrajector(cat);

    auto Parameterizeparameters_ForEvent_RECO =  MakeParameterizelineParasTrajector_ParticeVectorForSingleTrajector_withTRUEFraction(input_vector_RECO.at(Vector_count));

    char legend_title_x_z[1024];
    char legend_title_y_z[1024];
    char Full_title[1024];
    //std::cout<<"Size of vector (Parameterizeparameters_ForEvent) =   "<< Parameterizeparameters_ForEvent.size()<<std::endl;
    CryoTankTGraphX_Z->Draw("AP");
    FirstPlaneMinerva->Draw("Same P");
    FirstTargetMinerva->Draw("Same P");
    int marker=3;

    for(auto dog :Parameterizeparameters_ForEvent ){
      //For a Single Particle in the Event
      //
      std::vector<Vertex_XYZ> PathVector_forParticle;

      auto Particle_name = GetcommonNamefromPDG(dog.pdg);
      char Particle_name_char[Particle_name.length()+1];
      strcpy(Particle_name_char,Particle_name.c_str());
      auto KE = dog.KE*.001;
      //std::cout<< "PDG in plotting pdg:"<< dog.pdg <<std::endl;
      //std::cout<< "PDG in plotting KE:"<< dog.KE <<std::endl;
      //std::cout<< "PDG in plotting Xo:"<< dog.Xo <<std::endl;
      //std::cout<< "PDG in plotting Yo:"<< dog.Yo <<std::endl;
      //std::cout<< "PDG in plotting Zo:"<< dog.Zo <<std::endl;

      //std::cout<< "PDG in plotting a"<< dog.a <<std::endl;
      //std::cout<< "PDG in plotting b"<< dog.b <<std::endl;
      //std::cout<< "PDG in plotting c"<< dog.c <<std::endl;

      if(dog.pdg==13)
      {
        PathVector_forParticle = MakeVectorofPath(dog, Spaceingcm, .40);
      }
      else {
        PathVector_forParticle = MakeVectorofPath(dog, Spaceingcm, 1.0);

      }

      //for(auto cat: PathVector_forParticle){std::cout<<"Printing out vector = (x,y,z) = ("<<cat.x <<","<<cat.y<<","<<cat.z<<") "<<"\n";}
      std::cout<<"~~~~~~~~~~~~~~~"<<std::endl;



      TGraph  *Tg_x = Make_X_vs_Z_Tgraph_fromVector(PathVector_forParticle);

      sprintf(legend_title_x_z, "%s , %.2f",Particle_name_char,KE);
      if(marker==10){marker+=20;}
      Tg_x->SetMarkerColor(marker);
      Tg_x->Draw("Same P");
      legend->AddEntry(Tg_x,legend_title_x_z,"p");
      marker++;
    }
    ////////////////////
    legend->AddEntry((TObject*)0, "RECOtrks,KE [GeV], TrueEFrac , ", "");

    int shape=35;
    for(auto dog :Parameterizeparameters_ForEvent_RECO ){
      std::vector<Vertex_XYZ> PathVector_forParticle;

      auto Particle_name = GetcommonNamefromPDG(dog.pdg);
      char Particle_name_char[Particle_name.length()+1];
      strcpy(Particle_name_char,Particle_name.c_str());
      auto KE = dog.KE*.001;
      auto TrueEnergyFraction = dog.TRUE_Efraction;
      //std::cout<< "PDG in plotting pdg:"<< dog.pdg <<std::endl;
      //std::cout<< "PDG in plotting KE:"<< dog.KE <<std::endl;
      //std::cout<< "PDG in plotting Xo:"<< dog.Xo <<std::endl;
      //std::cout<< "PDG in plotting Yo:"<< dog.Yo <<std::endl;
      //std::cout<< "PDG in plotting Zo:"<< dog.Zo <<std::endl;

      //std::cout<< "PDG in plotting a"<< dog.a <<std::endl;
      //std::cout<< "PDG in plotting b"<< dog.b <<std::endl;
      //std::cout<< "PDG in plotting c"<< dog.c <<std::endl;

      if(dog.pdg==13)
      {
        PathVector_forParticle = MakeVectorofPath(dog, Spaceingcm, .40);
      }
      else {
        PathVector_forParticle = MakeVectorofPath(dog, Spaceingcm, 1.0);

      }

      //for(auto cat: PathVector_forParticle){
        //std::cout<<"Printing RECO out vector = (x,y,z) = ("<<cat.x <<","<<cat.y<<","<<cat.z<<") "<<"\n";}
      //std::cout<<"~~~~~~~~~~~~~~~"<<std::endl;



      TGraph  *Tg_x = Make_X_vs_Z_Tgraph_fromVector(PathVector_forParticle);

      sprintf(legend_title_x_z, "%s , %.3f, %.3f",Particle_name_char,KE, TrueEnergyFraction);
      Tg_x->SetMarkerColor(2);
      Tg_x->Draw("Same P");
      legend->AddEntry(Tg_x,legend_title_x_z,"p");
      shape++;
    }




    sprintf(Full_title, "Cryo True and Reco Trajectors X vs Z  %s",runinfo);
    string Title = string(Full_title);
    plot->AddHistoTitle(Title.c_str(), .04);
    plot->WritePreliminary("TL", .035, 0, 0, false);
    legend->SetTextSize(0.017);
    legend->Draw();

    gPad->Update();
    can->Modified();
    can->Print(pdf_mid);

///////////////////////////////////////////
/// New Plot
///////////////////////////////////////////
    CryoTankTGraphY_Z->Draw("AP");
    FirstPlaneMinerva->Draw("Same P");
    FirstTargetMinerva->Draw("Same P");
    marker=3;

    for(auto dog :Parameterizeparameters_ForEvent ){
      //For a Single Particle in the Event
      std::vector<Vertex_XYZ> PathVector_forParticle;

      auto Particle_name = GetcommonNamefromPDG(dog.pdg);
      char Particle_name_char[Particle_name.length()+1];
      strcpy(Particle_name_char,Particle_name.c_str());
      auto KE = dog.KE*.001;
      //std::cout<< "PDG in plotting pdg:"<< dog.pdg <<std::endl;
      //std::cout<< "PDG in plotting KE:"<< dog.KE <<std::endl;
      //std::cout<< "PDG in plotting Xo:"<< dog.Xo <<std::endl;
      //std::cout<< "PDG in plotting Yo:"<< dog.Yo <<std::endl;
      //std::cout<< "PDG in plotting Zo:"<< dog.Zo <<std::endl;

      //std::cout<< "PDG in plotting a"<< dog.a <<std::endl;
      //std::cout<< "PDG in plotting b"<< dog.b <<std::endl;
      //std::cout<< "PDG in plotting c"<< dog.c <<std::endl;
      if(dog.pdg==13)
      {
        PathVector_forParticle = MakeVectorofPath(dog, Spaceingcm, .40);
      }
      else {
        PathVector_forParticle = MakeVectorofPath(dog, Spaceingcm, 1.0);

      }

      TGraph  *Tg_y = Make_Y_vs_Z_Tgraph_fromVector(PathVector_forParticle);
      sprintf(legend_title_y_z, "%s , %.3f",Particle_name_char,KE);
      if(marker==10){marker+=20;}
      Tg_y->SetMarkerColor(marker);
      Tg_y->Draw("Same P");
      legend_2->AddEntry(Tg_y,legend_title_y_z,"p");
      marker++;
    }

    legend_2->AddEntry((TObject*)0, "RECO trks, KE[GeV], TrueEFrac" , "");


    for(auto dog :Parameterizeparameters_ForEvent_RECO ){
      std::vector<Vertex_XYZ> PathVector_forParticle;

      auto Particle_name = GetcommonNamefromPDG(dog.pdg);
      char Particle_name_char[Particle_name.length()+1];
      strcpy(Particle_name_char,Particle_name.c_str());
      auto KE = dog.KE*.001;
      auto TrueEnergyFraction = dog.TRUE_Efraction;
      //std::cout<< "PDG in plotting pdg:"<< dog.pdg <<std::endl;
      //std::cout<< "PDG in plotting KE:"<< dog.KE <<std::endl;
      //std::cout<< "PDG in plotting Xo:"<< dog.Xo <<std::endl;
      //std::cout<< "PDG in plotting Yo:"<< dog.Yo <<std::endl;
      //std::cout<< "PDG in plotting Zo:"<< dog.Zo <<std::endl;

      //std::cout<< "PDG in plotting a"<< dog.a <<std::endl;
      //std::cout<< "PDG in plotting b"<< dog.b <<std::endl;
      //std::cout<< "PDG in plotting c"<< dog.c <<std::endl;

      if(dog.pdg==13)
      {
        PathVector_forParticle = MakeVectorofPath(dog, Spaceingcm, .40);
      }
      else {
        PathVector_forParticle = MakeVectorofPath(dog, Spaceingcm, 1.0);

      }

      //for(auto cat: PathVector_forParticle){
        //std::cout<<"RECO Printing out vector = (x,y,z) = ("<<cat.x <<","<<cat.y<<","<<cat.z<<") "<<"\n";}
      //std::cout<<"~~~~~~~~~~~~~~~"<<std::endl;



      TGraph  *Tg_y = Make_Y_vs_Z_Tgraph_fromVector(PathVector_forParticle);

      sprintf(legend_title_y_z, "%s , %.3f, %.3f",Particle_name_char, KE, TrueEnergyFraction);
      Tg_y->SetMarkerColor(2);
      Tg_y->Draw("Same P");
      legend_2->AddEntry(Tg_y, legend_title_y_z,"p");
      shape++;
    }


    sprintf(Full_title, "Cryo True and RECO Trajectors Y vs Z  %s",runinfo);
    string thirdTitle = string(Full_title);
    plot->AddHistoTitle(thirdTitle.c_str(), .04);
    plot->WritePreliminary("TL", .035, 0, 0, false);
    legend_2->SetTextSize(0.0170);
    legend_2->Draw();

    gPad->Update();
    can->Modified();
    can->Print(pdf_mid);

    Vector_count++;

  }//end loop

  can->Print(pdf_end);



}//end of function;
////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

void MakeData_trajector(std::vector <Trajector_DATA> input_vector, const char* Playlist ,double Spaceingcm ,const char* pdf, TCanvas *can, MnvPlotter *plot)
{
  char pdf_mid[1024];
  char pdf_start[1024];
  char pdf_end[1024];
  //char XaxisName[1024];


  sprintf(pdf_start,"%s.pdf(",pdf);
  sprintf(pdf_mid,  "%s.pdf",pdf);
  sprintf(pdf_end,  "%s.pdf)",pdf);

  can -> Print(pdf_start);

  auto CryoTankTGraphX_Z = Tank_Z_X_or_Y(true);

  auto VtxZCryoTargetMinerva = Make_VertLineTgraph(40 ,4293.04, -1100, 2000);
  auto maxVtxZCryoTarget = Make_VertLineTgraph(40 ,4446.33, -1100, 2000);
  auto FirstTargetMinerva = Make_VertLineTgraph(40 ,4525.0, -1100, 2000);

  CryoTankTGraphX_Z->GetXaxis()->CenterTitle();
  CryoTankTGraphX_Z->GetYaxis()->CenterTitle();
  CryoTankTGraphX_Z->GetXaxis()->SetTitle("Z [mm]");
  CryoTankTGraphX_Z->GetYaxis()->SetTitle("X [mm]");
  CryoTankTGraphX_Z->GetXaxis()->SetTitleSize(0.038);
  CryoTankTGraphX_Z->GetYaxis()->SetTitleSize(0.038);
  CryoTankTGraphX_Z->SetLineColor(2);
  CryoTankTGraphX_Z->SetLineWidth(4);
  CryoTankTGraphX_Z->SetMarkerColor(1);
  CryoTankTGraphX_Z->SetMarkerSize(1);
  CryoTankTGraphX_Z->SetMarkerStyle(20);
  CryoTankTGraphX_Z->SetMaximum(1100.0);
  CryoTankTGraphX_Z->SetMinimum(-1100.0);
  TAxis *axis = CryoTankTGraphX_Z->GetXaxis();
  axis->SetLimits(4000.,6500.);

  std::cout<<"starting CryoTank Interaction Plots"<<std::endl;

  VtxZCryoTargetMinerva->SetLineColor(2);
  FirstTargetMinerva->SetLineColor(2);
  maxVtxZCryoTarget->SetLineColor(2);
  VtxZCryoTargetMinerva->SetMarkerSize(1);
  FirstTargetMinerva->SetMarkerSize(1);
  maxVtxZCryoTarget->SetMarkerSize(1);
  VtxZCryoTargetMinerva->SetMarkerStyle(1);
  FirstTargetMinerva->SetMarkerStyle(1);
  maxVtxZCryoTarget->SetMarkerStyle(1);
  VtxZCryoTargetMinerva->SetMarkerColor(1);
  FirstTargetMinerva->SetMarkerColor(1);

  for(auto cat : input_vector){
    //Run info
    auto  run = cat.RunInfo.run;
    auto  subrun = cat.RunInfo.subrun;
    auto  gate = cat.RunInfo.gate;
    auto  slice = cat.RunInfo.slice;

    char runinfo[1024];
    sprintf(runinfo, "(%i/%i/%i/%i)",run,subrun,gate,slice);
    double x1, x2, y1, y2;
    plot->DecodeLegendPosition(x1, y1, x2, y2, "R", 6.5, 6., .025);
    TLegend *legend = new TLegend(x1 - .015, y1 + .25, x2 + .075, y2 + .3);
    TLegend *legendU = new TLegend(x1 - .015, y1 + .25, x2 + .075, y2 + .3);
    TLegend *legendV = new TLegend(x1 - .015, y1 + .25, x2 + .075, y2 + .3);

    std::cout<< " Parameterizeparameters_ForEvent " <<std::endl;
    auto Parameterizeparameters_ForEvent =  MakeParameterizelineParasTrajector_ForDataStruct(cat);

    std::cout<< "passed Parameterizeparameters_ForEvent " <<std::endl;

    char legend_title_x_z[1024];
    char Full_title[1024];
    //std::cout<<"Size of vector (Parameterizeparameters_ForEvent) =   "<< Parameterizeparameters_ForEvent.size()<<std::endl;

    int marker=3;
    int firsttime=0;
    ///////////////////////////////////////////
    /// New Plot X vs Z
    ///////////////////////////////////////////

    CryoTankTGraphX_Z->Draw("AP");
    maxVtxZCryoTarget->Draw("Same P");
    VtxZCryoTargetMinerva->Draw("Same P");
    FirstTargetMinerva->Draw("Same P");


    for(auto dog :Parameterizeparameters_ForEvent ){
      //For a Single Particle in the Event

      std::vector<Vertex_XYZ> PathVector_forParticle;
      auto KE = dog.KE*.001;
      auto angle = dog.Angle*TMath::RadToDeg();
      auto length = dog.length;


      PathVector_forParticle = MakeVectorofPath(dog, Spaceingcm, .40);

      //for(auto cat: PathVector_forParticle){std::cout<<"Printing out vector = (x,y,z) = ("<<cat.x <<","<<cat.y<<","<<cat.z<<") "<<"\n";}
      std::cout<<"~~~~~~~~~~~~~~~"<<std::endl;



      TGraph  *Tg_x = Make_X_vs_Z_Tgraph_fromVector(PathVector_forParticle);
      if(firsttime==0){
        Tg_x->SetMarkerColor(2);
        sprintf(legend_title_x_z, "Muon track");
        legend->AddEntry(Tg_x,legend_title_x_z,"p");
        legend->AddEntry((TObject*)0, "Track, Angle[Deg], KE[GeV], L[cm]", "");
      }
      else if(firsttime==1){
        sprintf(legend_title_x_z, "Recoil, %.3f, %.3f, %.3f", KE, angle,length);
        if(marker==10){marker+=20;}
        Tg_x->SetMarkerColor(marker);
        Tg_x->SetMarkerStyle(kCircle);
      }
      else if(firsttime==2){
        sprintf(legend_title_x_z, "Recoil, %.3f, %.3f, %.3f", KE, angle,length);
        if(marker==10){marker+=20;}
        Tg_x->SetMarkerColor(marker);
        Tg_x->SetMarkerStyle(kOpenSquare);
      }

      else if(firsttime==3){
        sprintf(legend_title_x_z, "Recoil, %.3f, %.3f, %.3f", KE, angle,length);
        if(marker==10){marker+=20;}
        Tg_x->SetMarkerColor(marker);
        Tg_x->SetMarkerStyle(kOpenTriangleUp);
      }
      else{
        sprintf(legend_title_x_z, "Recoil, %.3f, %.3f, %.3f", KE, angle,length);
        if(marker==10){marker+=20;}
        Tg_x->SetMarkerColor(marker);
        Tg_x->SetMarkerStyle(kOpenDiamond);
      }

      Tg_x->Draw("Same P");
      legend->AddEntry(Tg_x,legend_title_x_z,"p");
      marker++;
      firsttime++;

    }// end of Loop



    ////////////////////
    sprintf(Full_title, "Data Trajectors X vs Z  %s",runinfo);
    string Title = string(Full_title);
    plot->AddHistoTitle(Title.c_str(), .04);
    plot->WritePreliminary("TL", .035, 0, 0, false);
    legend->SetTextSize(0.017);
    legend->Draw();

    gPad->Update();
    can->Modified();
    can->Print(pdf_mid);


  ///////////////////////////////////////////
  /// New Plot V vs Z
  ///////////////////////////////////////////


  CryoTankTGraphX_Z->Draw("AP");
  maxVtxZCryoTarget->Draw("Same P");
  VtxZCryoTargetMinerva->Draw("Same P");
  FirstTargetMinerva->Draw("Same P");

  marker=3;
  firsttime=0;

  for(auto dog :Parameterizeparameters_ForEvent ){
    //For a Single Particle in the Event
    std::vector<Vertex_XYZ> PathVector_forParticle;
    auto KE = dog.KE*.001;
    auto angle = dog.Angle*TMath::RadToDeg();
    auto length = dog.length;

    PathVector_forParticle = MakeVectorofPath(dog, Spaceingcm, .40);

    //for(auto cat: PathVector_forParticle){std::cout<<"Printing out vector = (x,y,z) = ("<<cat.x <<","<<cat.y<<","<<cat.z<<") "<<"\n";}
    std::cout<<"~~~~~~~~~~~~~~~"<<std::endl;


    TGraph  *Tg_v = Make_V_vs_Z_Tgraph_fromVector(PathVector_forParticle);

    if(firsttime==0){
      Tg_v->SetMarkerColor(2);
      sprintf(legend_title_x_z, "Muon track");
      legendV->AddEntry(Tg_v,legend_title_x_z,"p");
      legendV->AddEntry((TObject*)0, "Track, Angle[Deg], KE[GeV], L[cm]", "");
    }
    else if(firsttime==1){
      sprintf(legend_title_x_z, "Recoil, %.3f, %.3f, %.3f", KE, angle,length);
      if(marker==10){marker+=20;}
      Tg_v->SetMarkerColor(marker);
      Tg_v->SetMarkerStyle(kCircle);
    }
    else if(firsttime==2){
      sprintf(legend_title_x_z, "Recoil, %.3f, %.3f, %.3f", KE, angle,length);
      if(marker==10){marker+=20;}
      Tg_v->SetMarkerColor(marker);
      Tg_v->SetMarkerStyle(kOpenSquare);
    }

    else if(firsttime==3){
      sprintf(legend_title_x_z, "Recoil, %.3f, %.3f, %.3f", KE, angle,length);
      if(marker==10){marker+=20;}
      Tg_v->SetMarkerColor(marker);
      Tg_v->SetMarkerStyle(kOpenTriangleUp);
    }
    else{
      sprintf(legend_title_x_z, "Recoil, %.3f, %.3f, %.3f", KE, angle,length);
      if(marker==10){marker+=20;}
      Tg_v->SetMarkerColor(marker);
      Tg_v->SetMarkerStyle(kOpenDiamond);
    }


    Tg_v->Draw("Same P");
    legendV->AddEntry(Tg_v,legend_title_x_z,"p");
    marker++;
    firsttime++;

  }

  ////////////////////
  sprintf(Full_title, "Data Trajectors V vs Z  %s",runinfo);
  string TitleV = string(Full_title);
  plot->AddHistoTitle(TitleV.c_str(), .04);
  plot->WritePreliminary("TL", .035, 0, 0, false);
  legendV->SetTextSize(0.017);
  legendV->Draw();

  gPad->Update();
  can->Modified();
  can->Print(pdf_mid);

////////////////////////////////////////////
// New Plot V
////////////////////////////////////////////
  CryoTankTGraphX_Z->Draw("AP");
  maxVtxZCryoTarget->Draw("Same P");
  VtxZCryoTargetMinerva->Draw("Same P");
  FirstTargetMinerva->Draw("Same P");
  marker=3;
  firsttime=0;




for(auto dog :Parameterizeparameters_ForEvent ){
  //For a Single Particle in the Event

  std::vector<Vertex_XYZ> PathVector_forParticle;
  auto KE = dog.KE*.001;
  auto angle = dog.Angle*TMath::RadToDeg();
  auto length = dog.length;


  PathVector_forParticle = MakeVectorofPath(dog, Spaceingcm, .40);

  //for(auto cat: PathVector_forParticle){std::cout<<"Printing out vector = (x,y,z) = ("<<cat.x <<","<<cat.y<<","<<cat.z<<") "<<"\n";}
  std::cout<<"~~~~~~~~~~~~~~~"<<std::endl;

  TGraph  *Tg_u = Make_U_vs_Z_Tgraph_fromVector(PathVector_forParticle);
  if(firsttime==0){
    Tg_u->SetMarkerColor(2);
    sprintf(legend_title_x_z, "Muon track");
    legendU->AddEntry(Tg_u,legend_title_x_z,"p");
    legendU->AddEntry((TObject*)0, "Track, Angle[Deg], KE[GeV], L[cm]", "");
  }

  else if(firsttime==1){
    sprintf(legend_title_x_z, "Recoil, %.3f, %.3f, %.3f", KE, angle,length);
    if(marker==10){marker+=20;}
    Tg_u->SetMarkerColor(marker);
    Tg_u->SetMarkerStyle(kCircle);
  }
  else if(firsttime==2){
    sprintf(legend_title_x_z, "Recoil, %.3f, %.3f, %.3f", KE, angle,length);
    if(marker==10){marker+=20;}
    Tg_u->SetMarkerColor(marker);
    Tg_u->SetMarkerStyle(kOpenSquare);
  }

  else if(firsttime==3){
    sprintf(legend_title_x_z, "Recoil, %.3f, %.3f, %.3f", KE, angle,length);
    if(marker==10){marker+=20;}
    Tg_u->SetMarkerColor(marker);
    Tg_u->SetMarkerStyle(kOpenTriangleUp);
  }
  else{
    sprintf(legend_title_x_z, "Recoil, %.3f, %.3f, %.3f", KE, angle,length);
    if(marker==10){marker+=20;}
    Tg_u->SetMarkerColor(marker);
    Tg_u->SetMarkerStyle(kOpenDiamond);
  }

  Tg_u->Draw("Same P");
  legendU->AddEntry(Tg_u, legend_title_x_z,"p");
  marker++;
  firsttime++;

}

////////////////////
sprintf(Full_title, "Data Trajectors U vs Z  %s",runinfo);
string TitleU = string(Full_title);
plot->AddHistoTitle(TitleU.c_str(), .04);
plot->WritePreliminary("TL", .035, 0, 0, false);
legendU->SetTextSize(0.017);
legendU->Draw();

gPad->Update();
can->Modified();
can->Print(pdf_mid);


}//end loop


can->Print(pdf_end);



}//end of function;




//////////////////////////////////////////////////////////////////////////////////////////
std::vector<Particle_Map> Particle_vector( TObjArray * Hists_vector, bool doPOTscaling, double scaler){

  std::vector<Particle_Map> output_vector;


  int lowBin = 0;
  unsigned int nHists = Hists_vector->GetEntries();
  for ( unsigned int i = 0; i != nHists; ++i )
  {
    MnvH1D *mnv = (MnvH1D*)Hists_vector->At(i);
    if(doPOTscaling==true){mnv->Scale(scaler);}
    std::string Title = mnv->GetTitle();
    char Title_char[Title.length()+1];
    strcpy( Title_char,Title.c_str());
    Particle_type particle_type =  getParticle_fromstring(Title_char);
    int highBin_mc   = mnv->GetNbinsX()+1;
    double area = mnv->Integral( lowBin, highBin_mc);
    Particle_Map input_map{particle_type, area};
    output_vector.push_back(input_map);
  }//end of loop

  return output_vector;


}

std::vector<Material_Map> Material_vector( TObjArray * Hists_vector, bool doPOTscaling, double scaler){

  std::vector<Material_Map> output_vector;


  int lowBin = 0;
  unsigned int nHists = Hists_vector->GetEntries();
  for ( unsigned int i = 0; i != nHists; ++i )
  {
    MnvH1D *mnv = (MnvH1D*)Hists_vector->At(i);
    if(doPOTscaling==true){mnv->Scale(scaler);}
    std::string Title = mnv->GetTitle();
    char Title_char[Title.length()+1];
    strcpy( Title_char,Title.c_str());
    auto material_type =  getMaterial_fromstring(Title_char);
    int highBin_mc   = mnv->GetNbinsX()+1;
    double area = mnv->Integral( lowBin, highBin_mc);
    Material_Map input_map{material_type, area};
    output_vector.push_back(input_map);
  }//end of loop

  return output_vector;


}

std::vector<Interaction_Map> Interaction_vector( TObjArray * Hists_vector, bool doPOTscaling, double scaler){

  std::vector<Interaction_Map> output_vector;


  int lowBin = 0;
  unsigned int nHists = Hists_vector->GetEntries();
  for ( unsigned int i = 0; i != nHists; ++i )
  {
    MnvH1D *mnv = (MnvH1D*)Hists_vector->At(i);
    if(doPOTscaling==true){mnv->Scale(scaler);}


    std::string Title = mnv->GetTitle();
    char Title_char[Title.length()+1];
    strcpy( Title_char,Title.c_str());
    auto interaction_type =  getInteraction_fromstring(Title_char);
    int highBin_mc   = mnv->GetNbinsX()+1;
    double area = mnv->Integral( lowBin, highBin_mc);
    Interaction_Map input_map{interaction_type, area};
    output_vector.push_back(input_map);
  }//end of loop

  return output_vector;

}


std::vector<Track_Map> Track_vector( TObjArray * Hists_vector, bool doPOTscaling, double scaler){
  std::vector<Track_Map> output_vector;

  int lowBin = 0;
  unsigned int nHists = Hists_vector->GetEntries();
  for ( unsigned int i = 0; i != nHists; ++i )
  {
    MnvH1D *mnv = (MnvH1D*)Hists_vector->At(i);
    if(doPOTscaling==true){mnv->Scale(scaler);}


    std::string Title = mnv->GetTitle();
    char Title_char[Title.length()+1];
    strcpy( Title_char,Title.c_str());
    std::cout<<"Track name inside TrackVector : Name = " << Title_char << std::endl;
    auto Track_type =  getTrackType_fromstring(Title_char);
    int highBin_mc   = mnv->GetNbinsX()+1;
    double area = mnv->Integral( lowBin, highBin_mc);
    Track_Map input_map{Track_type, area};
    output_vector.push_back(input_map);
  }//end of loop

  return output_vector;
}

std::vector<VertexOptions_Map> vertexOption_vector( TObjArray * Hists_vector, bool doPOTscaling, double scaler){
  std::vector<VertexOptions_Map> output_vector;

  int lowBin = 0;
  unsigned int nHists = Hists_vector->GetEntries();
  for ( unsigned int i = 0; i != nHists; ++i )
  {
    MnvH1D *mnv = (MnvH1D*)Hists_vector->At(i);
    if(doPOTscaling==true){mnv->Scale(scaler);}


    std::string Title = mnv->GetTitle();
    char Title_char[Title.length()+1];
    strcpy( Title_char,Title.c_str());
    std::cout<<"Track name inside VertexOption : Name = " << Title_char << std::endl;
    auto Vertexoption_type =  getVertexOptions_fromstring(Title_char);
    int highBin_mc   = mnv->GetNbinsX()+1;
    double area = mnv->Integral( lowBin, highBin_mc);
    VertexOptions_Map input_map{Vertexoption_type, area};
    output_vector.push_back(input_map);
  }//end of loop

  return output_vector;
}

std::vector<boolNTrack_Map> boolNTrack_vector( TObjArray * Hists_vector, bool doPOTscaling, double scaler){
  std::vector<boolNTrack_Map> output_vector;

  int lowBin = 0;
  unsigned int nHists = Hists_vector->GetEntries();
  for ( unsigned int i = 0; i != nHists; ++i )
  {
    MnvH1D *mnv = (MnvH1D*)Hists_vector->At(i);
    if(doPOTscaling==true){mnv->Scale(scaler);}


    std::string Title = mnv->GetTitle();
    char Title_char[Title.length()+1];
    strcpy( Title_char,Title.c_str());
    std::cout<<"Track name inside VertexOption : Name = " << Title_char << std::endl;
    auto boolNTrack_type =  getboolNTrack_fromstring(Title_char);
    int highBin_mc   = mnv->GetNbinsX()+1;
    double area = mnv->Integral( lowBin, highBin_mc);
    boolNTrack_Map input_map{boolNTrack_type, area};
    output_vector.push_back(input_map);
  }//end of loop

  return output_vector;
}





void DrawVertex_Cryotank_X_Y_R_Vs_Z(std::vector<Vertex_XYZ> input_XYZ_vector ,
  const char* Playlist, const char* title ,const char* pdf, TCanvas *can, MnvPlotter *plot){

  char pdf_mid[1024];
  char pdf_start[1024];
  char pdf_end[1024];

  sprintf(pdf_start,"%s.pdf(",pdf);
  sprintf(pdf_mid,  "%s.pdf",pdf);
  sprintf(pdf_end,  "%s.pdf)",pdf);

  auto CryoTankTGraphX_Z = Tank_Z_X_or_Y(true);
  SetHist_CRYOTankXY(CryoTankTGraphX_Z, "Vertex Z [mm]" , "Vertex X [mm]");

  auto CryoTankTGraphY_Z = Tank_Z_X_or_Y(false);
  SetHist_CRYOTankXY(CryoTankTGraphY_Z, "Vertex Z [mm]" , "Vertex Y [mm]");

  auto CryoTankTGraphR_Z = Tank_Z_R_or_RR(0);
  SetHist_CRYOTankR(*CryoTankTGraphR_Z, "Vertex Z [mm]" , "Vertex R [mm]");

  auto CryoTankTGraphRR_Z =Tank_Z_R_or_RR(1);
  SetHist_CRYOTankRR(*CryoTankTGraphRR_Z, "Vertex Z [mm]" , "Vertex R^2 [mm]");


  auto FirstPlaneMinerva = Make_VertLineTgraph(40 ,4293.04, -1100, 2000);
  auto FirstTargetMinerva = Make_VertLineTgraph(40 ,4525.0, -1100, 2000);

  FirstPlaneMinerva->SetLineColor(2);
  FirstTargetMinerva->SetLineColor(2);
  FirstPlaneMinerva->SetMarkerSize(2);
  FirstTargetMinerva->SetMarkerSize(2);
  FirstPlaneMinerva->SetMarkerStyle(1);
  FirstTargetMinerva->SetMarkerStyle(1);
  FirstPlaneMinerva->SetMarkerColor(1);
  FirstTargetMinerva->SetMarkerColor(1);

  auto Y_vs_Z_Tgraph = Make_Y_vs_Z_Tgraph_fromVector(input_XYZ_vector);
  double NPointsY = Y_vs_Z_Tgraph->GetN();
  SetHist_SizeMarker(*Y_vs_Z_Tgraph);
  auto X_vs_Z_Tgraph = Make_X_vs_Z_Tgraph_fromVector(input_XYZ_vector);
  double NPointsX = X_vs_Z_Tgraph->GetN();
  SetHist_SizeMarker(*X_vs_Z_Tgraph);
  auto R_vs_Z_Tgraph = Make_R_vs_Z_Tgraph_fromVector(input_XYZ_vector);
  double NPointsR = R_vs_Z_Tgraph->GetN();
  SetHist_SizeMarker(*R_vs_Z_Tgraph);
  auto RR_vs_Z_Tgraph = Make_RR_vs_Z_Tgraph_fromVector(input_XYZ_vector);
  double NPointsRR = RR_vs_Z_Tgraph->GetN();
  SetHist_SizeMarker(*RR_vs_Z_Tgraph);
  //Y_vs_Z_Tgraph->SetMarkerSize(1);
  TAxis *axis1 = Y_vs_Z_Tgraph->GetXaxis();
  axis1->SetLimits(2000.,5000.);
  //X_vs_Z_Tgraph->SetMarkerSize(1);
  TAxis *axis2 = X_vs_Z_Tgraph->GetXaxis();
  axis2->SetLimits(2000.,5000.);
  //R_vs_Z_Tgraph->SetMarkerSize(1);
  TAxis *axis3 = R_vs_Z_Tgraph->GetXaxis();
  axis3->SetLimits(2000.,5000.);
  //RR_vs_Z_Tgraph->SetMarkerSize(1);
  TAxis *axis4 = RR_vs_Z_Tgraph->GetXaxis();
  axis4->SetLimits(2000.,5000.);

  //std::vector<TGraph*> CrytoTank_Figures;
  //std::vector<TGraph*> Input_figures;
  std::vector <std::string> Titles_vector;
  //CrytoTank_Figures.push_back(CryoTankTGraphX_Z);
  char Plot_title[1024];

  Y_vs_Z_Tgraph->SetMarkerColor(kRed);
  CryoTankTGraphY_Z->Draw("AP");
  Y_vs_Z_Tgraph->Draw("Same P");
  FirstPlaneMinerva->Draw("Same P");
  FirstTargetMinerva->Draw("Same P");
  sprintf(Plot_title,"%s [%s] [Y vs Z Vector Position] [Nevents: %.2f]",title, Playlist, NPointsX);
  plot->AddHistoTitle(Plot_title, .04);
  plot->WritePreliminary("TL", .035, 0, 0, false);
  gPad->Update();
  can->Modified();
  can->Print(pdf_mid);
  //NEW
  X_vs_Z_Tgraph->SetMarkerColor(kRed);
  CryoTankTGraphX_Z->Draw("AP");
  X_vs_Z_Tgraph->Draw("Same P");
  FirstPlaneMinerva->Draw("Same P");
  FirstTargetMinerva->Draw("Same P");
  sprintf(Plot_title,"%s [%s] [X vs Z Vector Position] [Nevents: %.2f]",title, Playlist, NPointsX);
  plot->AddHistoTitle(Plot_title, .04);
  plot->WritePreliminary("TL", .035, 0, 0, false);
  gPad->Update();
  can->Modified();
  can->Print(pdf_mid);
  //NEW
  R_vs_Z_Tgraph->SetMarkerColor(kRed);
  CryoTankTGraphR_Z->Draw("AP");
  R_vs_Z_Tgraph->Draw("Same P");
  FirstPlaneMinerva->Draw("Same P");
  FirstTargetMinerva->Draw("Same P");
  sprintf(Plot_title,"%s [%s] [R vs Z Vector Position] [Nevents: %.2f]",title, Playlist, NPointsR);
  plot->AddHistoTitle(Plot_title, .04);
  plot->WritePreliminary("TL", .035, 0, 0, false);
  gPad->Update();
  can->Modified();
  can->Print(pdf_mid);
  //NEW
  CryoTankTGraphRR_Z->Draw("AP");
  RR_vs_Z_Tgraph->SetMarkerColor(kRed);
  RR_vs_Z_Tgraph->Draw("Same P");
  FirstPlaneMinerva->Draw("Same P");
  FirstTargetMinerva->Draw("Same P");
  sprintf(Plot_title,"%s [%s] [R^{2} vs Z Vector Position] [Nevents: %.2f]",title, Playlist, NPointsRR);
  plot->AddHistoTitle(Plot_title, .04);
  plot->WritePreliminary("TL", .035, 0, 0, false);
  gPad->Update();
  can->Modified();
  can->Print(pdf_mid);
  //NEW

}//end of function

void DrawVertex_Cryotank_X_Y_R_Vs_Z(std::vector<Vertex_XYZ> input_XYZ_vector_He ,std::vector<Vertex_XYZ> input_XYZ_vector_Al,
  const char* Playlist, const char* title ,const char* pdf, TCanvas *can, MnvPlotter *plot){

  char pdf_mid[1024];
  char pdf_start[1024];
  char pdf_end[1024];

  sprintf(pdf_start,"%s.pdf(",pdf);
  sprintf(pdf_mid,  "%s.pdf",pdf);
  sprintf(pdf_end,  "%s.pdf)",pdf);

  auto CryoTankTGraphX_Z = Tank_Z_X_or_Y(true);
  SetHist_CRYOTankXY(CryoTankTGraphX_Z, "Vertex Z [mm]" , "Vertex X [mm]");

  auto CryoTankTGraphY_Z = Tank_Z_X_or_Y(false);
  SetHist_CRYOTankXY(CryoTankTGraphY_Z, "Vertex Z [mm]" , "Vertex Y [mm]");

  auto CryoTankTGraphR_Z =Tank_Z_R_or_RR(0);
  SetHist_CRYOTankR(*CryoTankTGraphR_Z, "Vertex Z [mm]" , "Vertex R [mm]");

  auto CryoTankTGraphRR_Z =Tank_Z_R_or_RR(1);
  SetHist_CRYOTankRR(*CryoTankTGraphRR_Z, "Vertex Z [mm]" , "Vertex R^2 [mm]");


  auto FirstPlaneMinerva = Make_VertLineTgraph(40 ,4293.04, -1100, 100000);
  auto FirstTargetMinerva = Make_VertLineTgraph(40 ,4525.0, -1100, 100000);

  auto FirstPlaneMinerva_short = Make_VertLineTgraph(40 ,4293.04, -1100, 2000);
  auto FirstTargetMinerva_short = Make_VertLineTgraph(40 ,4525.0, -1100, 2000);



  FirstPlaneMinerva->SetLineColor(2);
  FirstTargetMinerva->SetLineColor(2);
  FirstPlaneMinerva_short->SetLineColor(2);
  FirstTargetMinerva_short->SetLineColor(2);
  FirstPlaneMinerva->SetMarkerSize(2);
  FirstTargetMinerva->SetMarkerSize(2);
  FirstPlaneMinerva_short->SetMarkerSize(2);
  FirstTargetMinerva_short->SetMarkerSize(2);
  FirstPlaneMinerva->SetMarkerStyle(1);
  FirstTargetMinerva->SetMarkerStyle(1);
  FirstPlaneMinerva_short->SetMarkerStyle(2);
  FirstTargetMinerva_short->SetMarkerStyle(2);
  FirstPlaneMinerva->SetMarkerColor(1);
  FirstTargetMinerva->SetMarkerColor(1);




  auto Y_vs_Z_Tgraph_He = Make_Y_vs_Z_Tgraph_fromVector(input_XYZ_vector_He);
  double NPointsY = Y_vs_Z_Tgraph_He->GetN();
  SetHist_SizeMarker(*Y_vs_Z_Tgraph_He);
  auto X_vs_Z_Tgraph_He = Make_X_vs_Z_Tgraph_fromVector(input_XYZ_vector_He);
  double NPointsX = X_vs_Z_Tgraph_He->GetN();
  SetHist_SizeMarker(*X_vs_Z_Tgraph_He);
  auto R_vs_Z_Tgraph_He = Make_R_vs_Z_Tgraph_fromVector(input_XYZ_vector_He);
  double NPointsR = R_vs_Z_Tgraph_He->GetN();
  SetHist_SizeMarker(*R_vs_Z_Tgraph_He);
  auto RR_vs_Z_Tgraph_He = Make_RR_vs_Z_Tgraph_fromVector(input_XYZ_vector_He);
  SetHist_SizeMarker(*RR_vs_Z_Tgraph_He);
  double NPointsRR = RR_vs_Z_Tgraph_He->GetN();

  auto Y_vs_Z_Tgraph_Al = Make_Y_vs_Z_Tgraph_fromVector(input_XYZ_vector_Al);
  SetHist_SizeMarker(*Y_vs_Z_Tgraph_Al);
  auto X_vs_Z_Tgraph_Al = Make_X_vs_Z_Tgraph_fromVector(input_XYZ_vector_Al);
  SetHist_SizeMarker(*X_vs_Z_Tgraph_Al);
  auto R_vs_Z_Tgraph_Al = Make_R_vs_Z_Tgraph_fromVector(input_XYZ_vector_Al);
  SetHist_SizeMarker(*R_vs_Z_Tgraph_Al);
  auto RR_vs_Z_Tgraph_Al = Make_RR_vs_Z_Tgraph_fromVector(input_XYZ_vector_Al);
  SetHist_SizeMarker(*RR_vs_Z_Tgraph_Al);

  //Y_vs_Z_Tgraph->SetMarkerSize(1);
  TAxis *axis1 = CryoTankTGraphY_Z->GetXaxis();
  axis1->SetLimits(1500.,5000.);
  //X_vs_Z_Tgraph->SetMarkerSize(1);
  TAxis *axis2 = CryoTankTGraphX_Z->GetXaxis();
  axis2->SetLimits(1500.,5000.);
  //R_vs_Z_Tgraph->SetMarkerSize(1);
  TAxis *axis3 = CryoTankTGraphR_Z->GetXaxis();
  axis3->SetLimits(1500.,5000.);
  //RR_vs_Z_Tgraph->SetMarkerSize(1);
  TAxis *axis4 = CryoTankTGraphRR_Z->GetXaxis();
  axis4->SetLimits(1500.,5000.);

  //std::vector<TGraph*> CrytoTank_Figures;
  //std::vector<TGraph*> Input_figures;
  std::vector <std::string> Titles_vector;
  //CrytoTank_Figures.push_back(CryoTankTGraphX_Z);
  char Plot_title[1024];

  double x1, x2, y1, y2;
  plot->DecodeLegendPosition(x1, y1, x2, y2,"R", 6.5, 6., .025);
  TLegend *legend1 = new TLegend(x1 - .015, y1 + .15, x2 + .075, y2 + .3);
  Y_vs_Z_Tgraph_He->SetMarkerColor(kBlue);
  Y_vs_Z_Tgraph_Al->SetMarkerColor(kGreen);
  CryoTankTGraphY_Z->Draw("AP");
  Y_vs_Z_Tgraph_He->Draw("Same P");
  Y_vs_Z_Tgraph_Al->Draw("Same P");
  FirstPlaneMinerva_short->Draw("Same P");
  FirstTargetMinerva_short->Draw("Same P");
  legend1->AddEntry(CryoTankTGraphY_Z, "CryoTank geometry", "P");
  legend1->AddEntry(Y_vs_Z_Tgraph_He, "Helium", "P");
  legend1->AddEntry(Y_vs_Z_Tgraph_Al, "Aluminium", "P");
  legend1->SetBorderSize(0);
  legend1->Draw("Same");
  sprintf(Plot_title,"%s [%s] [X vs Z Vector Position][Nevents: %.2f]",title, Playlist, NPointsY);
  plot->AddHistoTitle(Plot_title, .04);
  plot->WritePreliminary("TL", .035, 0, 0, false);
  gPad->Update();
  can->Modified();
  can->Print(pdf_mid);
  can->Clear();
  //NEW

  TLegend *legend2 = new TLegend(x1 - .015, y1 + .15, x2 + .075, y2 + .3);
  X_vs_Z_Tgraph_He->SetMarkerColor(kBlue);
  X_vs_Z_Tgraph_Al->SetMarkerColor(kGreen);
  legend2->AddEntry(CryoTankTGraphX_Z, "CryoTank geometry","P");
  legend2->AddEntry(X_vs_Z_Tgraph_He, "Helium","P");
  legend2->AddEntry(X_vs_Z_Tgraph_Al, "Aluminium","P");
  CryoTankTGraphX_Z->Draw("AP");
  X_vs_Z_Tgraph_He->Draw("Same P");
  X_vs_Z_Tgraph_Al->Draw("Same P");
  FirstPlaneMinerva_short->Draw("Same P");
  FirstTargetMinerva_short->Draw("Same P");
  legend2->SetBorderSize(0);
  legend2->Draw("Same");
  sprintf(Plot_title,"%s [%s] [Y vs Z Vector Position]",title, Playlist);
  plot->AddHistoTitle(Plot_title, .04);
  plot->WritePreliminary("TL", .035, 0, 0, false);
  gPad->Update();
  can->Modified();
  can->Print(pdf_mid);
  can->Clear();
  //NEW

  TLegend *legend3 = new TLegend(x1 - .015, y1 + .15, x2 + .075, y2 + .3);
  R_vs_Z_Tgraph_He->SetMarkerColor(kBlue);
  R_vs_Z_Tgraph_Al->SetMarkerColor(kGreen);
  CryoTankTGraphR_Z->Draw("AP");
  R_vs_Z_Tgraph_He->Draw("Same P");
  R_vs_Z_Tgraph_Al->Draw("Same P");
  FirstPlaneMinerva_short->Draw("Same P");
  FirstTargetMinerva_short->Draw("Same P");
  legend3->AddEntry(CryoTankTGraphR_Z, "CryoTank geometry","P");
  legend3->AddEntry(R_vs_Z_Tgraph_He, "Helium","P");
  legend3->AddEntry(R_vs_Z_Tgraph_Al, "Aluminium","P");

  legend3->SetBorderSize(0);
  legend3->Draw("Same");
  sprintf(Plot_title,"%s [%s] [R vs Z Vector Position]",title, Playlist);
  plot->AddHistoTitle(Plot_title, .04);
  plot->WritePreliminary("TL", .035, 0, 0, false);
  gPad->Update();
  can->Modified();
  can->Print(pdf_mid);
  can->Clear();
  //NEW
  TLegend *legend4 = new TLegend(x1 - .015, y1 + .15, x2 + .075, y2 + .3);
  RR_vs_Z_Tgraph_He->SetMarkerColor(kBlue);
  RR_vs_Z_Tgraph_Al->SetMarkerColor(kGreen);
  CryoTankTGraphRR_Z->Draw("AP");
  RR_vs_Z_Tgraph_He->Draw("Same P");
  RR_vs_Z_Tgraph_Al->Draw("Same P");
  FirstPlaneMinerva->Draw("Same P");
  FirstTargetMinerva->Draw("Same P");
  legend4->AddEntry(CryoTankTGraphRR_Z, "CryoTank geometry","P");
  legend4->AddEntry(RR_vs_Z_Tgraph_He, "Helium","P");
  legend4->AddEntry(RR_vs_Z_Tgraph_Al, "Aluminium","P");
  legend4->SetBorderSize(0);
  legend4->Draw("Same");
  sprintf(Plot_title,"%s [%s] [R^{2} vs Z Vector Position]",title, Playlist);
  plot->AddHistoTitle(Plot_title, .04);
  plot->WritePreliminary("TL", .035, 0, 0, false);
  gPad->Update();
  can->Modified();
  can->Print(pdf_mid);
  can->Clear();
  //NEW

}//end of function


void DrawVertex_Cryotank_X_Y_R_Vs_Z_4regions(
  std::vector<Vertex_XYZ> input_XYZ_vectorupstream,
  std::vector<Vertex_XYZ> input_XYZ_vectorbarrel,
  std::vector<Vertex_XYZ> input_XYZ_vectordownstream,
  std::vector<Vertex_XYZ> input_XYZ_vectordownstreamconcave,
  const char* Playlist, const char* title ,const char* pdf, TCanvas *can, MnvPlotter *plot){

  char pdf_mid[1024];
  char pdf_start[1024];
  char pdf_end[1024];
  double x1, x2, y1, y2;
  plot->DecodeLegendPosition(x1, y1, x2, y2, "R", 6.5, 6., .025);
  TLegend *legend1 = new TLegend(x1 - .075, y1 + .25, x2 + .075, y2 + .25);
  TLegend *legend2 = new TLegend(x1 - .075, y1 + .25, x2 + .075, y2 + .25);
  TLegend *legend3 = new TLegend(x1 - .075, y1 + .25, x2 + .075, y2 + .25);
  TLegend *legend4 = new TLegend(x1 - .075, y1 + .25, x2 + .075, y2 + .25);

  sprintf(pdf_start,"%s.pdf(",pdf);
  sprintf(pdf_mid,  "%s.pdf",pdf);
  sprintf(pdf_end,  "%s.pdf)",pdf);

  auto CryoTankTGraphX_Z = Tank_Z_X_or_Y(true);
  SetHist_CRYOTank(*CryoTankTGraphX_Z, "Vertex Z [mm]", "Vertex X [mm]");

  auto CryoTankTGraphY_Z = Tank_Z_X_or_Y(false);
  SetHist_CRYOTank(*CryoTankTGraphY_Z, "Vertex Z [mm]", "Vertex Y [mm]");

  auto CryoTankTGraphR_Z = Tank_Z_R_or_RR(0);
  SetHist_CRYOTankR(*CryoTankTGraphR_Z, "Vertex Z [mm]", "Vertex R [mm]");

  auto CryoTankTGraphRR_Z =Tank_Z_R_or_RR(1);
  SetHist_CRYOTankRR(*CryoTankTGraphRR_Z, "Vertex Z [mm]", "Vertex R^2 [mm]");

  auto UpstreamStart = Make_VertLineTgraph(300 ,2491.17, -1100, 2000);
  auto EndBarrel = Make_VertLineTgraph(300 ,3283.84, -1100, 2000);
  auto EndDSCap = Make_VertLineTgraph(300 ,3687.0, -1100, 2000);
  auto FirstPlaneMinerva = Make_VertLineTgraph(300 ,4293.04, -1100, 2000);
  auto FirstTargetMinerva = Make_VertLineTgraph(300 ,4525.0, -1100, 2000);

  legend1->SetHeader("CryoTarget Fitting Regions","C");
  legend1->AddEntry(UpstreamStart,"US Cap / Barrel","P");
  legend1->AddEntry(EndBarrel,"Barrel / DS Cap","P");
  legend1->AddEntry(EndDSCap,"DS Cap / DS Concave Cap","P");
  legend1->AddEntry(FirstPlaneMinerva,"First Scintillator Plane","P");
  legend1->AddEntry(FirstTargetMinerva,"MINER#nuA's Target 1","P");

  legend2->SetHeader("CryoTarget Fitting Regions","C");
  legend2->AddEntry(UpstreamStart,"US Cap / Barrel","P");
  legend2->AddEntry(EndBarrel,"Barrel / DS Cap","P");
  legend2->AddEntry(EndDSCap,"DS Cap / DS Concave Cap","P");
  legend2->AddEntry(FirstPlaneMinerva,"First Scintillator Plane","P");
  legend2->AddEntry(FirstTargetMinerva,"MINER#nuA's Target 1","P");

  legend3->SetHeader("CryoTarget Fitting Regions","C");
  legend3->AddEntry(UpstreamStart,"US Cap / Barrel","P");
  legend3->AddEntry(EndBarrel,"Barrel / DS Cap","P");
  legend3->AddEntry(EndDSCap,"DS Cap / DS Concave Cap","P");
  legend3->AddEntry(FirstPlaneMinerva,"First Scintillator Plane","P");
  legend3->AddEntry(FirstTargetMinerva,"MINER#nuA's Target 1","P");

  legend4->SetHeader("CryoTarget Fitting Regions","C");
  legend4->AddEntry(UpstreamStart,"US Cap / Barrel","P");
  legend4->AddEntry(EndBarrel,"Barrel / DS Cap","P");
  legend4->AddEntry(EndDSCap,"DS Cap / DS Concave Cap","P");
  legend4->AddEntry(FirstPlaneMinerva,"First Scintillator Plane","P");
  legend4->AddEntry(FirstTargetMinerva,"MINER#nuA's Target 1","P");

  SetLineForCryoPlots(*FirstPlaneMinerva, TColor::GetColor("#FF0800"));
  SetLineForCryoPlots(*FirstTargetMinerva, 1);

  SetLineForCryoPlots(*UpstreamStart, TColor::GetColor("#0859C6"));
  SetLineForCryoPlots(*EndBarrel,     TColor::GetColor("#DF00FF"));
  SetLineForCryoPlots(*EndDSCap,      TColor::GetColor("#ffc922"));

  auto Y_vs_Z_Tgraph_upstreamCap          = Make_Y_vs_Z_Tgraph_fromVector(input_XYZ_vectorupstream);
  auto Y_vs_Z_Tgraph_barrel               = Make_Y_vs_Z_Tgraph_fromVector(input_XYZ_vectorbarrel);
  auto Y_vs_Z_Tgraph_downstreamCap        = Make_Y_vs_Z_Tgraph_fromVector(input_XYZ_vectordownstream);
  auto Y_vs_Z_Tgraph_downstreamconcaveCap = Make_Y_vs_Z_Tgraph_fromVector(input_XYZ_vectordownstreamconcave);

  SetHist_SizeMarker(*Y_vs_Z_Tgraph_upstreamCap);   SetHist_SizeMarker(*Y_vs_Z_Tgraph_barrel);
  SetHist_SizeMarker(*Y_vs_Z_Tgraph_downstreamCap); SetHist_SizeMarker(*Y_vs_Z_Tgraph_downstreamconcaveCap);

  auto X_vs_Z_Tgraph_upstreamCap          = Make_X_vs_Z_Tgraph_fromVector(input_XYZ_vectorupstream);
  auto X_vs_Z_Tgraph_barrel               = Make_X_vs_Z_Tgraph_fromVector(input_XYZ_vectorbarrel);
  auto X_vs_Z_Tgraph_downstreamCap        = Make_X_vs_Z_Tgraph_fromVector(input_XYZ_vectordownstream);
  auto X_vs_Z_Tgraph_downstreamconcaveCap = Make_X_vs_Z_Tgraph_fromVector(input_XYZ_vectordownstreamconcave);

  SetHist_SizeMarker(*X_vs_Z_Tgraph_upstreamCap);   SetHist_SizeMarker(*X_vs_Z_Tgraph_barrel);
  SetHist_SizeMarker(*X_vs_Z_Tgraph_downstreamCap); SetHist_SizeMarker(*X_vs_Z_Tgraph_downstreamconcaveCap);

  auto R_vs_Z_Tgraph_upstreamCap          = Make_R_vs_Z_Tgraph_fromVector(input_XYZ_vectorupstream);
  auto R_vs_Z_Tgraph_barrel               = Make_R_vs_Z_Tgraph_fromVector(input_XYZ_vectorbarrel);
  auto R_vs_Z_Tgraph_downstreamCap        = Make_R_vs_Z_Tgraph_fromVector(input_XYZ_vectordownstream);
  auto R_vs_Z_Tgraph_downstreamconcaveCap = Make_R_vs_Z_Tgraph_fromVector(input_XYZ_vectordownstreamconcave);

  SetHist_SizeMarker(*R_vs_Z_Tgraph_upstreamCap);   SetHist_SizeMarker(*R_vs_Z_Tgraph_barrel);
  SetHist_SizeMarker(*R_vs_Z_Tgraph_downstreamCap); SetHist_SizeMarker(*R_vs_Z_Tgraph_downstreamconcaveCap);


  auto RR_vs_Z_Tgraph_upstreamCap          = Make_RR_vs_Z_Tgraph_fromVector(input_XYZ_vectorupstream);
  auto RR_vs_Z_Tgraph_barrel               = Make_RR_vs_Z_Tgraph_fromVector(input_XYZ_vectorbarrel);
  auto RR_vs_Z_Tgraph_downstreamCap        = Make_RR_vs_Z_Tgraph_fromVector(input_XYZ_vectordownstream);
  auto RR_vs_Z_Tgraph_downstreamconcaveCap = Make_RR_vs_Z_Tgraph_fromVector(input_XYZ_vectordownstreamconcave);

  SetHist_SizeMarker(*RR_vs_Z_Tgraph_upstreamCap);   SetHist_SizeMarker(*RR_vs_Z_Tgraph_barrel);
  SetHist_SizeMarker(*RR_vs_Z_Tgraph_downstreamCap); SetHist_SizeMarker(*RR_vs_Z_Tgraph_downstreamconcaveCap);

  //Y_vs_Z_Tgraph->SetMarkerSize(1);
  TAxis *axis1 = CryoTankTGraphX_Z->GetXaxis();
  axis1->SetLimits(2000.,5000.);
  //X_vs_Z_Tgraph->SetMarkerSize(1);
  TAxis *axis2 = CryoTankTGraphY_Z->GetXaxis();
  axis2->SetLimits(2000.,5000.);
  //R_vs_Z_Tgraph->SetMarkerSize(1);
  TAxis *axis3 = CryoTankTGraphR_Z->GetXaxis();
  axis3->SetLimits(2000.,5000.);
  //RR_vs_Z_Tgraph->SetMarkerSize(1);
  TAxis *axis4 = CryoTankTGraphRR_Z->GetXaxis();
  axis4->SetLimits(2000.,5000.);

  //std::vector<TGraph*> CrytoTank_Figures;
  //std::vector<TGraph*> Input_figures;
  //CrytoTank_Figures.push_back(CryoTankTGraphX_Z);
  char Plot_title[1024];
  Y_vs_Z_Tgraph_upstreamCap->SetMarkerColor(kTeal);
  Y_vs_Z_Tgraph_barrel->SetMarkerColor(kGreen);
  Y_vs_Z_Tgraph_downstreamCap->SetMarkerColor(kBlue-7);
  Y_vs_Z_Tgraph_downstreamconcaveCap->SetMarkerColor(46);

  CryoTankTGraphY_Z->Draw("AP");
  Y_vs_Z_Tgraph_upstreamCap->Draw("Same P");
  Y_vs_Z_Tgraph_barrel->Draw("Same P");
  Y_vs_Z_Tgraph_downstreamCap->Draw("Same P");
  Y_vs_Z_Tgraph_downstreamconcaveCap->Draw("Same P");
  FirstPlaneMinerva->Draw("Same P");
  FirstTargetMinerva->Draw("Same P");
  UpstreamStart->Draw("Same P");
  EndBarrel->Draw("Same P");
  EndDSCap->Draw("Same P");
  legend1->AddEntry(Y_vs_Z_Tgraph_upstreamCap,"US Cap Events","P");
  legend1->AddEntry(Y_vs_Z_Tgraph_barrel,"Barrel Events","P");
  legend1->AddEntry(Y_vs_Z_Tgraph_downstreamCap,"DS Cap Events","P");
  legend1->AddEntry(Y_vs_Z_Tgraph_downstreamconcaveCap,"DS Concave Events","P");
  legend1->Draw();
  sprintf(Plot_title,"%s [%s] [Y vs Z Vector Position]",title, Playlist);
  plot->AddHistoTitle(Plot_title, .04);
  plot->WritePreliminary("TL", .035, 0, 0, false);
  gPad->Update();
  can->Modified();
  can->Print(pdf_mid);
  //////////////////////////////////////////////////////////////////
  X_vs_Z_Tgraph_upstreamCap->SetMarkerColor(kTeal);
  X_vs_Z_Tgraph_barrel->SetMarkerColor(kGreen);
  X_vs_Z_Tgraph_downstreamCap->SetMarkerColor(kBlue-7);
  X_vs_Z_Tgraph_downstreamconcaveCap->SetMarkerColor(46);
  legend2->AddEntry(X_vs_Z_Tgraph_upstreamCap,"US Cap Events","P");
  legend2->AddEntry(X_vs_Z_Tgraph_barrel,"Barrel Events","P");
  legend2->AddEntry(X_vs_Z_Tgraph_downstreamCap,"DS Cap Events","P");
  legend2->AddEntry(X_vs_Z_Tgraph_downstreamconcaveCap,"DS Concave Events","P");

  CryoTankTGraphX_Z->Draw("AP");
  X_vs_Z_Tgraph_upstreamCap->Draw("Same P");
  X_vs_Z_Tgraph_barrel->Draw("Same P");
  X_vs_Z_Tgraph_downstreamCap->Draw("Same P");
  X_vs_Z_Tgraph_downstreamconcaveCap->Draw("Same P");
  FirstPlaneMinerva->Draw("Same P");
  FirstTargetMinerva->Draw("Same P");
  UpstreamStart->Draw("Same P");
  EndBarrel->Draw("Same P");
  EndDSCap->Draw("Same P");
  legend2->Draw();
  sprintf(Plot_title,"%s [%s] [X vs Z Vector Position]",title, Playlist);
  plot->AddHistoTitle(Plot_title, .04);
  plot->WritePreliminary("TL", .035, 0, 0, false);
  gPad->Update();
  can->Modified();
  can->Print(pdf_mid);
  //NEW
  R_vs_Z_Tgraph_upstreamCap->SetMarkerColor(kTeal);
  R_vs_Z_Tgraph_barrel->SetMarkerColor(kGreen);
  R_vs_Z_Tgraph_downstreamCap->SetMarkerColor(kBlue-7);
  R_vs_Z_Tgraph_downstreamconcaveCap->SetMarkerColor(46);
  legend3->AddEntry(R_vs_Z_Tgraph_upstreamCap,         "US Cap Events","P");
  legend3->AddEntry(R_vs_Z_Tgraph_barrel,              "Barrel Events","P");
  legend3->AddEntry(R_vs_Z_Tgraph_downstreamCap,       "DS Cap Events","P");
  legend3->AddEntry(R_vs_Z_Tgraph_downstreamconcaveCap,"DS Concave Events","P");

  CryoTankTGraphR_Z->Draw("AP");
  R_vs_Z_Tgraph_upstreamCap->Draw("Same P");
  R_vs_Z_Tgraph_barrel->Draw("Same P");
  R_vs_Z_Tgraph_downstreamCap->Draw("Same P");
  R_vs_Z_Tgraph_downstreamconcaveCap->Draw("Same P");
  FirstPlaneMinerva->Draw("Same P");
  FirstTargetMinerva->Draw("Same P");
  UpstreamStart->Draw("Same P");
  EndBarrel->Draw("Same P");
  EndDSCap->Draw("Same P");
  legend3->Draw();
  sprintf(Plot_title,"%s [%s] [R vs Z Vector Position]",title, Playlist);
  plot->AddHistoTitle(Plot_title, .04);
  plot->WritePreliminary("TL", .035, 0, 0, false);
  gPad->Update();
  can->Modified();
  can->Print(pdf_mid);
  //NEW
  RR_vs_Z_Tgraph_upstreamCap->SetMarkerColor(kTeal);
  RR_vs_Z_Tgraph_barrel->SetMarkerColor(kGreen);
  RR_vs_Z_Tgraph_downstreamCap->SetMarkerColor(kBlue-7);
  RR_vs_Z_Tgraph_downstreamconcaveCap->SetMarkerColor(46);

  legend4->AddEntry(RR_vs_Z_Tgraph_upstreamCap,         "US Cap Events","P");
  legend4->AddEntry(RR_vs_Z_Tgraph_barrel,              "Barrel Events","P");
  legend4->AddEntry(RR_vs_Z_Tgraph_downstreamCap,       "DS Cap Events","P");
  legend4->AddEntry(RR_vs_Z_Tgraph_downstreamconcaveCap,"DS Concave Events","P");

  CryoTankTGraphRR_Z->Draw("AP");
  RR_vs_Z_Tgraph_upstreamCap->Draw("Same P");
  RR_vs_Z_Tgraph_barrel->Draw("Same P");
  RR_vs_Z_Tgraph_downstreamCap->Draw("Same P");
  RR_vs_Z_Tgraph_downstreamconcaveCap->Draw("Same P");
  FirstPlaneMinerva->Draw("Same P");
  FirstTargetMinerva->Draw("Same P");
  UpstreamStart->Draw("Same P");
  EndBarrel->Draw("Same P");
  EndDSCap->Draw("Same P");
  legend4->Draw();
  sprintf(Plot_title,"%s [%s] [R^{2} vs Z Vector Position]",title, Playlist);
  plot->AddHistoTitle(Plot_title, .04);
  plot->WritePreliminary("TL", .035, 0, 0, false);
  gPad->Update();
  can->Modified();
  can->Print(pdf_mid);
  //NEW

}//end of function

void DrawPieFigures(Hist_phyiscs_map Input_map,  const char* pdf, TCanvas *can, MnvPlotter *plotter, bool IsReco, bool MakCVS, const char* CVS_title ){

  std::string Data_type = String_Reco_orTruth(IsReco);
  std::string CVS_title_string = CVS_title;
  TCanvas *cpie = new TCanvas("cpie","TPie test",700,700);
  std::vector<int> PieColors = {
    TColor::GetColor("#EEFF00"), // neonyellow,
    TColor::GetColor("#DF00FF"), //'psychedelic Purple
    TColor::GetColor("#ffc922"), //'sunset yellow'
    TColor::GetColor("#87CEEB"),//'skyblue'
    TColor::GetColor("#0859C6"), //blue
    TColor::GetColor("#654522"), // yellowishbrown,
    TColor::GetColor(  43, 206,  72 ), //green
    TColor::GetColor("#FF0800"),//2 candy Apple
    TColor::GetColor("#90AD1C"),
    TColor::GetColor("#BABABA"), //Gray
    TColor::GetColor("#00FFFF"),//'aqua'
    TColor::GetColor("#F1B6DA"),//pink
    TColor::GetColor("#00A86B"),//'Jade'
    TColor::GetColor("#FAFAD2"),  // LightGoldenRodYellow
    TColor::GetColor("#800000"),  // Maroon
    TColor::GetColor("#555555"),  // dark grey
    TColor::GetColor(0, 153, 143 ), //turquoise
    TColor::GetColor("#654522"), // yellowishbrown,
    TColor::GetColor("#8db600"), // yellowgreen,
    TColor::GetColor("#D3D3D3"),  //'lightgrey'
     TColor::GetColor("#90AD1C"),
     TColor::GetColor("#CCDDAA")
  };

auto Particle_Map_vector = Input_map.Particle_vector;
auto Material_Map_vector = Input_map.Material_vector;
auto Interaction_Map_vector = Input_map.Interaction_vector;
auto playlist_name = GetPlaylist_InitialName(Input_map.playlist);
char playlist_name_char[playlist_name.length()+1]; strcpy(playlist_name_char,playlist_name.c_str());
unsigned int n_size_particle = Particle_Map_vector.size();
unsigned int n_size_material = Material_Map_vector.size();
unsigned int n_size_interaction = Interaction_Map_vector.size();


char CVS_name_material[1024];
char CVS_name_particle[1024];
char CVS_name_interaction[1024];
char Data_type_char[Data_type.length()+1];
strcpy(Data_type_char,Data_type.c_str());

sprintf(CVS_name_particle,   "%s_BREAKDOWNS_%s_Particle_ME%s.cvs"   , Data_type_char, CVS_title, playlist_name_char );
sprintf(CVS_name_material,   "%s_BREAKDOWNS_%s_Material_ME%s.cvs"   , Data_type_char, CVS_title, playlist_name_char );
sprintf(CVS_name_interaction,"%s_BREAKDOWNS_%s_Interaction_ME%s.cvs", Data_type_char, CVS_title, playlist_name_char );

  std::ofstream myfile_particle;
  std::ofstream myfile_material;
  std::ofstream myfile_interaction;


  if(MakCVS==true){
    myfile_particle.open(CVS_name_particle);
    myfile_material.open(CVS_name_material);
    myfile_interaction.open(CVS_name_interaction);
    myfile_particle<<"Particle, number events,percentage \n";
    myfile_material<<"Material , number events,percentage \n";
    myfile_interaction<<"Interaction, number events,percentage \n";

  }




double totalWeight_Particle=0.0;
for(unsigned int i = 0; i != n_size_particle; ++i){totalWeight_Particle+=Particle_Map_vector.at(i).Amount;}
double totalWeight_Material=0.0;
for(unsigned int i = 0; i != n_size_material; ++i){totalWeight_Material+=Material_Map_vector.at(i).Amount;}
double totalWeight_Interaction=0.0;
for(unsigned int i = 0; i != n_size_interaction; ++i){totalWeight_Interaction+=Interaction_Map_vector.at(i).Amount;}

TPie *pie_particle =    new TPie("pie_particle",    "pie_particle",n_size_particle);
TPie *pie_material =    new TPie("pie_material",    "pie_material",n_size_material);
TPie *pie_interaction = new TPie("pie_interaction", "pie_interaction",n_size_interaction);

for ( unsigned int i = 0; i != n_size_particle; ++i )
{
  auto type = Particle_Map_vector.at(i).type;
  auto Particle_name = GetParticle_group_Name(type);
  char Particle_name_char[Particle_name.length()+1];
  strcpy(Particle_name_char,Particle_name.c_str());
  double weight = Particle_Map_vector.at(i).Amount;
  double fraction = (weight / totalWeight_Particle)*100;
  char Legend_title_char[1024];
  sprintf(Legend_title_char,  "%s [%2.2f%%] (%2.1f)",Particle_name_char ,fraction,weight );
  char CVS_input_char[1024];
  if(MakCVS==true){
    sprintf(CVS_input_char,  "%s, %2.2f , %2.2f",Particle_name_char ,weight,fraction );
    myfile_particle<< CVS_input_char << "\n";
  }
  std::cout<<"Legend title Particle = "<< Legend_title_char<<std::endl;
  pie_particle->SetEntryVal(i,weight);
  pie_particle->SetEntryLabel(i, Legend_title_char);
  pie_particle->SetEntryFillColor(i,PieColors.at(i));


}



myfile_interaction<<"Interaction, number events,percentage \n";


for ( unsigned int i = 0; i != n_size_material; ++i )
{
  auto type = Material_Map_vector.at(i).type;
  auto matertial_name = GetNameMaterial(type);
  char matertial_name_char[matertial_name.length()+1];
  strcpy(matertial_name_char,matertial_name.c_str());

  double weight = Material_Map_vector.at(i).Amount;
  double fraction = 100*(weight / totalWeight_Material);
  char Legend_title_char[1024];
  sprintf(Legend_title_char,  "%s [%2.2f%%] (%2.1f)",matertial_name_char , fraction , weight );
  std::cout<<"Legend title Material = "<< Legend_title_char<<std::endl;
  char CVS_input_char[1024];
  if(MakCVS==true){
    sprintf(CVS_input_char,  "%s, %2.2f , %2.2f",matertial_name_char  ,weight,fraction );
    myfile_material<< CVS_input_char << "\n";
  }
  pie_material->SetEntryVal(i,weight);
  pie_material->SetEntryLabel(i, Legend_title_char);
  pie_material->SetEntryFillColor(i,PieColors.at(i));


}


for ( unsigned int i = 0; i != n_size_interaction; ++i )
{
  auto type = Interaction_Map_vector.at(i).type;
  auto interaction_name = GetNameInteraction(type);
  char interaction_name_char[interaction_name.length()+1];
  strcpy(interaction_name_char,interaction_name.c_str());
  double weight = Interaction_Map_vector.at(i).Amount;
  double fraction = 100*(weight / totalWeight_Interaction);
  char Legend_title_char[1024];
  sprintf(Legend_title_char,  "%s [%2.2f%%] (%2.1f)",interaction_name_char ,fraction , weight );
  std::cout<<"Legend title Particle = "<< Legend_title_char<<std::endl;
  char CVS_input_char[1024];
  if(MakCVS==true){
    sprintf(CVS_input_char,  "%s, %2.2f , %2.2f",interaction_name_char  ,weight,fraction );
    myfile_interaction<< CVS_input_char << "\n";
  }
  pie_interaction->SetEntryVal(i,weight);
  pie_interaction->SetEntryLabel(i, Legend_title_char);
  pie_interaction->SetEntryFillColor(i,PieColors.at(i));

}
if(MakCVS==true){
  myfile_particle.close();
  myfile_material.close();
  myfile_interaction.close();
}

 //pie_particle->SetRadius(.17);
 pie_particle->SetCircle(.68,.45,.31);
 pie_particle->SetLabelsOffset(.02);
 pie_particle->SetLabelFormat("");

 pie_particle->Draw("");
 TLegend *pieleg = pie_particle->MakeLegend();

 pieleg->SetX1(.01);
 pieleg->SetY1(.2);

 pieleg->SetX2(.35);
 pieleg->SetY2(.85);
 //pieleg->Draw();
 char Legend_total_char[1024];
 sprintf(Legend_total_char,  "[%2.1f]",totalWeight_Particle);
 std::string total_numberstring(Legend_total_char);

 std::string Title = "["+ Data_type + "] ["+ CVS_title_string + "][Particle]" +total_numberstring + "[" + playlist_name +"]";
 plotter->AddHistoTitle(Title.c_str(), .04);
 plotter->WritePreliminary("TR", .035, 0, 0, false);
 gPad->Update();
 cpie->Modified();
 char PrintLabel[1024];
 sprintf(PrintLabel,  "%s.pdf",pdf);
 cpie->Print(PrintLabel);
 //cpie->Clear();

/////////////////////////////////////////////////

 pie_material->SetCircle(.65,.45,.31);
 pie_material->SetLabelFormat("");

 pie_material->SetLabelsOffset(.02);
 pie_material->Draw("");
 TLegend *pieleg_m = pie_material->MakeLegend();

 pieleg_m->SetX1(.01);
 pieleg_m->SetY1(.4);

 pieleg_m->SetX2(.3);
 pieleg_m->SetY2(.85);
 //pieleg->Draw();

 std::string Title_m = "["+ Data_type + " Helium] ["+ CVS_title_string + "][Material] [Mvn-v1][" + playlist_name +"]";
 plotter->AddHistoTitle(Title_m.c_str(), .04);
 plotter->WritePreliminary("TR", .035, 0, 0, false);
 gPad->Update();
 cpie->Modified();
 cpie->Print(PrintLabel);
 //cpie->Clear();
//////////////////////////////

pie_interaction->SetCircle(.65,.45,.31);
pie_interaction->SetLabelFormat("");
pie_interaction->SetLabelsOffset(.02);
pie_interaction->Draw("");
TLegend *pieleg_i = pie_interaction->MakeLegend();

pieleg_i->SetX1(.01);
pieleg_i->SetY1(.5);

pieleg_i->SetX2(.3);
pieleg_i->SetY2(.85);
//pieleg->Draw();

std::string Title_i = "["+ Data_type + " Helium] ["+ CVS_title_string + "] [Interaction] [Mvn-v1][" + playlist_name +"]";
plotter->AddHistoTitle(Title_i.c_str(), .04);
plotter->WritePreliminary("TR", .035, 0, 0, false);
gPad->Update();
cpie->Modified();
cpie->Print(PrintLabel);

}// End of FUnction




void DrawPieFigures_Interaction(std::vector<Interaction_Map> Interaction_Map_vector,  const char* pdf,
   TCanvas *can, MnvPlotter *plotter, bool IsReco, bool MakCVS, const char* CVS_title, std::string Title_i ){

  std::string Data_type = String_Reco_orTruth(IsReco);
  std::string CVS_title_string = CVS_title;
  TCanvas *cpie = new TCanvas("cpie","TPie test",700,700);

  std::vector<int> PieColors = {
    TColor::GetColor("#F1B6DA"),//pink 11
    TColor::GetColor("#DF00FF"), //'psychedelic Purple1
    TColor::GetColor(43,206,72 ), //green 2
    TColor::GetColor("#87CEEB"),//'skyblue' 3
    TColor::GetColor("#0859C6"), //blue 4
    TColor::GetColor("#ffc922"), //'sunset yellow'6
    TColor::GetColor("#654522"), // yellowishbrown,5
    TColor::GetColor("#f47835"),//2 candy Apple7
    TColor::GetColor("#800000"),  // Maroon
    TColor::GetColor("#90AD1C"),//8
    TColor::GetColor("#BABABA"), //Gray 9
    TColor::GetColor("#00FFFF"),//'aqua' 10
    TColor::GetColor("#AAF0D1"), // mint green
    TColor::GetColor(kRed),//'Jade' 12
    TColor::GetColor("#FAFAD2"),  // LightGoldenRodYellow 13

    TColor::GetColor("#555555"),  // dark grey 15
    TColor::GetColor(0, 153, 143 ), //turquoise 16
    TColor::GetColor("#654522"), // yellowishbrown, 17
    TColor::GetColor("#8db600"), // yellowgreen, 18
    TColor::GetColor("#D3D3D3"),  //'lightgrey' 19
    TColor::GetColor("#90AD1C"), // 20
    TColor::GetColor("#CCDDAA"), //21
    TColor::GetColor(kMagenta), //22
    TColor::GetColor("#EEFF00") // neonyellow,0
  };
std::string playlist_name = "Combined";
char playlist_name_char[playlist_name.length()+1]; strcpy(playlist_name_char,playlist_name.c_str());
unsigned int n_size_interaction = Interaction_Map_vector.size();


char CVS_name_interaction[1024];
char Data_type_char[Data_type.length()+1];
strcpy(Data_type_char,Data_type.c_str());
sprintf(CVS_name_interaction,"%s_BREAKDOWNS_%s_Interaction_ME%s.cvs", Data_type_char, CVS_title, playlist_name_char );

  std::ofstream myfile_interaction;


  if(MakCVS==true){
    myfile_interaction.open(CVS_name_interaction);
    myfile_interaction<<"Interaction, number events,percentage \n";
  }


double totalWeight_Interaction=0.0;
for(unsigned int i = 0; i != n_size_interaction; ++i){totalWeight_Interaction+=Interaction_Map_vector.at(i).Amount;}

TPie *pie_interaction = new TPie("pie_interaction", "pie_interaction",n_size_interaction);


myfile_interaction<<"Interaction, number events,percentage \n";

for ( unsigned int i = 0; i != n_size_interaction; ++i )
{
  auto type = Interaction_Map_vector.at(i).type;
  auto interaction_name = GetNameInteraction(type);
  char interaction_name_char[interaction_name.length()+1];
  strcpy(interaction_name_char,interaction_name.c_str());
  double weight = Interaction_Map_vector.at(i).Amount;
  double fraction = 100*(weight / totalWeight_Interaction);
  char Legend_title_char[1024];
  sprintf(Legend_title_char,  "%s [%2.2f%%]",interaction_name_char ,fraction);
  std::cout<<"Legend title Particle = "<< Legend_title_char<<std::endl;
  char CVS_input_char[1024];
  if(MakCVS==true){
    sprintf(CVS_input_char,  "%s, %2.2f , %2.2f",interaction_name_char  ,weight,fraction );
    myfile_interaction<< CVS_input_char << "\n";
  }
  pie_interaction->SetEntryVal(i,weight);
  pie_interaction->SetEntryLabel(i, Legend_title_char);
  pie_interaction->SetEntryFillColor(i,PieColors.at(i));

}
if(MakCVS==true){
  myfile_interaction.close();
}

//////////////////////////////

pie_interaction->SetCircle(.65,.45,.31);
pie_interaction->SetLabelFormat("");
pie_interaction->SetLabelsOffset(.02);
pie_interaction->Draw("");
TLegend *pieleg_i = pie_interaction->MakeLegend();

pieleg_i->SetX1(.01);
pieleg_i->SetY1(.5);

pieleg_i->SetX2(.3);
pieleg_i->SetY2(.85);
//pieleg->Draw();

//std::string Title_i = "["+ Data_type + " Helium] ["+ CVS_title_string + "] [Interaction] [Mvn-v1][" + playlist_name +"]";
plotter->AddHistoTitle(Title_i.c_str(), .04);
plotter->WritePreliminary("TR", .035, 0, 0, false);
gPad->Update();
cpie->Modified();
char PrintLabel[1024];
sprintf(PrintLabel,  "%s.pdf",pdf);
cpie->Print(PrintLabel);

}// End of FUnction


void DrawPieFigures_withTrackType(Hist_phyiscs_map_withtrack Input_map,  const char* pdf, TCanvas *can, MnvPlotter *plotter, bool IsReco, bool MakCVS, const char* CVS_title, char * Title  ){

  std::string Data_type = String_Reco_orTruth(IsReco);
  std::string CVS_title_string = CVS_title;
  TCanvas *cpie = new TCanvas("cpie","TPie test",700,700);
  std::vector<int> PieColors = {
    TColor::GetColor("#EEFF00"), // neonyellow,
    TColor::GetColor("#DF00FF"), //'psychedelic Purple
    TColor::GetColor("#ffc922"), //'sunset yellow'
    TColor::GetColor("#87CEEB"),//'skyblue'
    TColor::GetColor("#0859C6"), //blue
    TColor::GetColor("#654522"), // yellowishbrown,
    TColor::GetColor(  43, 206,  72 ), //green
    TColor::GetColor("#FF0800"),//2 candy Apple
    TColor::GetColor("#90AD1C"),
    TColor::GetColor("#BABABA"), //Gray
    TColor::GetColor("#00FFFF"),//'aqua'
    TColor::GetColor("#F1B6DA"),//pink
    TColor::GetColor("#00A86B"),//'Jade'
    TColor::GetColor("#FAFAD2"),  // LightGoldenRodYellow
    TColor::GetColor("#800000"),  // Maroon
    TColor::GetColor("#555555"),  // dark grey
    TColor::GetColor(0, 153, 143 ), //turquoise
    TColor::GetColor("#654522"), // yellowishbrown,
    TColor::GetColor("#8db600"), // yellowgreen,
    TColor::GetColor("#D3D3D3"),  //'lightgrey'
     TColor::GetColor("#90AD1C"),
     TColor::GetColor("#CCDDAA")
  };

std::string HistTitle(Title);
auto Particle_Map_vector = Input_map.Particle_vector;
auto Material_Map_vector = Input_map.Material_vector;
auto Interaction_Map_vector = Input_map.Interaction_vector;
auto Track_Map_vector = Input_map.Track_vector;
auto playlist_name = GetPlaylist_InitialName(Input_map.playlist);
char playlist_name_char[playlist_name.length()+1]; strcpy(playlist_name_char,playlist_name.c_str());
unsigned int n_size_particle = Particle_Map_vector.size();
unsigned int n_size_material = Material_Map_vector.size();
unsigned int n_size_interaction = Interaction_Map_vector.size();
unsigned int n_size_track = Track_Map_vector.size();

char CVS_name_material[1024];
char CVS_name_particle[1024];
char CVS_name_interaction[1024];
char CVS_name_track[1024];
char Data_type_char[Data_type.length()+1];
strcpy(Data_type_char,Data_type.c_str());

sprintf(CVS_name_particle,   "%s_BREAKDOWNS_%s_Particle_ME%s.cvs"   , Data_type_char, CVS_title, playlist_name_char );
sprintf(CVS_name_material,   "%s_BREAKDOWNS_%s_Material_ME%s.cvs"   , Data_type_char, CVS_title, playlist_name_char );
sprintf(CVS_name_interaction,"%s_BREAKDOWNS_%s_Interaction_ME%s.cvs", Data_type_char, CVS_title, playlist_name_char );
sprintf(CVS_name_track,      "%s_BREAKDOWNS_%s_Track_ME%s.cvs", Data_type_char, CVS_title, playlist_name_char );


  std::ofstream myfile_particle;
  std::ofstream myfile_material;
  std::ofstream myfile_interaction;
  std::ofstream myfile_track;


  if(MakCVS==true){
    myfile_particle.open(CVS_name_particle);
    myfile_material.open(CVS_name_material);
    myfile_interaction.open(CVS_name_interaction);
    myfile_track.open(CVS_name_track);
    myfile_particle<<"Particle, number events,percentage \n";
    myfile_material<<"Material , number events,percentage \n";
    myfile_interaction<<"Interaction, number events,percentage \n";
    myfile_track<<"Track, number events, percentage \n";

  }

double totalWeight_Particle=0.0;
for(unsigned int i = 0; i != n_size_particle; ++i){totalWeight_Particle+=Particle_Map_vector.at(i).Amount;}
double totalWeight_Material=0.0;
for(unsigned int i = 0; i != n_size_material; ++i){totalWeight_Material+=Material_Map_vector.at(i).Amount;}
double totalWeight_Interaction=0.0;
for(unsigned int i = 0; i != n_size_interaction; ++i){totalWeight_Interaction+=Interaction_Map_vector.at(i).Amount;}
double totalWeight_Track=0.0;
for(unsigned int i = 0; i != n_size_track; ++i){totalWeight_Track+=Track_Map_vector.at(i).Amount;}


TPie *pie_particle =    new TPie("pie_particle",    "pie_particle",   n_size_particle);
TPie *pie_material =    new TPie("pie_material",    "pie_material",   n_size_material);
TPie *pie_interaction = new TPie("pie_interaction", "pie_interaction",n_size_interaction);
TPie *pie_Track       = new TPie("pie_Track",       "pie_Track",      n_size_track);

for ( unsigned int i = 0; i != n_size_particle; ++i )
{
  auto type = Particle_Map_vector.at(i).type;
  auto Particle_name = GetParticle_group_Name(type);
  char Particle_name_char[Particle_name.length()+1];
  strcpy(Particle_name_char,Particle_name.c_str());
  double weight = Particle_Map_vector.at(i).Amount;
  double fraction = (weight / totalWeight_Particle)*100;
  char Legend_title_char[1024];
  sprintf(Legend_title_char,  "%s [%2.2f%%] (%2.1f)",Particle_name_char ,fraction,weight );
  char CVS_input_char[1024];
  if(MakCVS==true){
    sprintf(CVS_input_char,  "%s, %2.2f , %2.2f",Particle_name_char ,weight,fraction );
    myfile_particle<< CVS_input_char << "\n";
  }
  std::cout<<"Legend title Particle = "<< Legend_title_char<<std::endl;
  pie_particle->SetEntryVal(i,weight);
  pie_particle->SetEntryLabel(i, Legend_title_char);
  pie_particle->SetEntryFillColor(i,PieColors.at(i));


}



myfile_interaction<<"Interaction, number events,percentage \n";


for ( unsigned int i = 0; i != n_size_material; ++i )
{
  auto type = Material_Map_vector.at(i).type;
  auto matertial_name = GetNameMaterial(type);
  char matertial_name_char[matertial_name.length()+1];
  strcpy(matertial_name_char,matertial_name.c_str());

  double weight = Material_Map_vector.at(i).Amount;
  double fraction = 100*(weight / totalWeight_Material);
  char Legend_title_char[1024];
  sprintf(Legend_title_char,  "%s [%2.2f%%] (%2.1f)",matertial_name_char , fraction , weight );
  std::cout<<"Legend title Material = "<< Legend_title_char<<std::endl;
  char CVS_input_char[1024];
  if(MakCVS==true){
    sprintf(CVS_input_char,  "%s, %2.2f , %2.2f",matertial_name_char  ,weight,fraction );
    myfile_material<< CVS_input_char << "\n";
  }
  pie_material->SetEntryVal(i,weight);
  pie_material->SetEntryLabel(i, Legend_title_char);
  pie_material->SetEntryFillColor(i,PieColors.at(i));


}


for ( unsigned int i = 0; i != n_size_interaction; ++i )
{
  auto type = Interaction_Map_vector.at(i).type;
  auto interaction_name = GetNameInteraction(type);
  char interaction_name_char[interaction_name.length()+1];
  strcpy(interaction_name_char,interaction_name.c_str());
  double weight = Interaction_Map_vector.at(i).Amount;
  double fraction = 100*(weight / totalWeight_Interaction);
  char Legend_title_char[1024];
  sprintf(Legend_title_char,  "%s [%2.2f%%] (%2.1f)",interaction_name_char ,fraction , weight );
  std::cout<<"Legend title Particle = "<< Legend_title_char<<std::endl;
  char CVS_input_char[1024];
  if(MakCVS==true){
    sprintf(CVS_input_char,  "%s, %2.2f , %2.2f",interaction_name_char  ,weight,fraction );
    myfile_interaction<< CVS_input_char << "\n";
  }
  pie_interaction->SetEntryVal(i,weight);
  pie_interaction->SetEntryLabel(i, Legend_title_char);
  pie_interaction->SetEntryFillColor(i,PieColors.at(i));

}

// Track type
for ( unsigned int i = 0; i != n_size_track; ++i )
{
  auto type = Track_Map_vector.at(i).type;
  auto track_name = GetNameTrack(type);
  char track_name_char[track_name.length()+1];
  strcpy(track_name_char,track_name.c_str());
  double weight = Track_Map_vector.at(i).Amount;
  double fraction = 100*(weight / totalWeight_Track);
  char Legend_title_char[1024];
  sprintf(Legend_title_char,  "%s [%2.2f%%] (%2.1f)",track_name_char ,fraction , weight );
  std::cout<<"Legend title Track = "<< Legend_title_char<<std::endl;
  char CVS_input_char[1024];
  if(MakCVS==true){
    sprintf(CVS_input_char,  "%s, %2.2f , %2.2f", track_name_char  ,weight,fraction );
    myfile_track<< CVS_input_char << "\n";
  }

  pie_Track->SetEntryVal(i,weight);
  pie_Track->SetEntryLabel(i, Legend_title_char);
  pie_Track->SetEntryFillColor(i,PieColors.at(i));

}






if(MakCVS==true){
  myfile_particle.close();
  myfile_material.close();
  myfile_interaction.close();
  myfile_track.close();
}

 //pie_particle->SetRadius(.17);

 //////////////////////////////
 //Particle Type
 ////////////////////////////
 pie_particle->SetCircle(.68,.45,.31);
 pie_particle->SetLabelsOffset(.02);
 pie_particle->SetLabelFormat("");

 pie_particle->Draw("");
 TLegend *pieleg = pie_particle->MakeLegend();

 pieleg->SetX1(.01);
 pieleg->SetY1(.2);

 pieleg->SetX2(.35);
 pieleg->SetY2(.85);
 //pieleg->Draw();
 char Legend_total_char[1024];
 sprintf(Legend_total_char,  "[%2.1f]",totalWeight_Particle);
 std::string total_numberstring(Legend_total_char);

 std::string Title_final = HistTitle + " ["+ Data_type + "] ["+ CVS_title_string + "][Particle]" + total_numberstring + "[" + playlist_name +"]";
 plotter->AddHistoTitle(Title_final.c_str(), .04);
 plotter->WritePreliminary("TR", .035, 0, 0, false);
 gPad->Update();
 cpie->Modified();
 char PrintLabel[1024];
 sprintf(PrintLabel,  "%s.pdf",pdf);
 cpie->Print(PrintLabel);
 //cpie->Clear();

//////////////////////////////
//Material Type
////////////////////////////

 pie_material->SetCircle(.65,.45,.31);
 pie_material->SetLabelFormat("");

 pie_material->SetLabelsOffset(.02);
 pie_material->Draw("");
 TLegend *pieleg_m = pie_material->MakeLegend();

 pieleg_m->SetX1(.01);
 pieleg_m->SetY1(.4);

 pieleg_m->SetX2(.3);
 pieleg_m->SetY2(.85);
 //pieleg->Draw();

 std::string Title_m = HistTitle + " ["+ Data_type + " Helium] ["+ CVS_title_string + "][Material] [Mvn-v1][" + playlist_name +"]";
 plotter->AddHistoTitle(Title_m.c_str(), .04);
 plotter->WritePreliminary("TR", .035, 0, 0, false);
 gPad->Update();
 cpie->Modified();
 cpie->Print(PrintLabel);
 //cpie->Clear();
 //////////////////////////////
 //interaction Type
 ////////////////////////////

pie_interaction->SetCircle(.65,.45,.31);
pie_interaction->SetLabelFormat("");
pie_interaction->SetLabelsOffset(.02);
pie_interaction->Draw("");
TLegend *pieleg_i = pie_interaction->MakeLegend();

pieleg_i->SetX1(.01);
pieleg_i->SetY1(.5);

pieleg_i->SetX2(.3);
pieleg_i->SetY2(.85);
//pieleg->Draw();

std::string Title_i = HistTitle + " ["+ Data_type + " Helium] ["+ CVS_title_string + "] [Interaction] [Mvn-v1][" + playlist_name +"]";
plotter->AddHistoTitle(Title_i.c_str(), .04);
plotter->WritePreliminary("TR", .035, 0, 0, false);
gPad->Update();
cpie->Modified();
cpie->Print(PrintLabel);

//////////////////////////////
//Track Type
////////////////////////////
pie_Track->SetCircle(.68,.45,.31);
pie_Track->SetLabelsOffset(.02);
pie_Track->SetLabelFormat("");

pie_Track->Draw("");
TLegend *pieleg_track = pie_Track->MakeLegend();

pieleg_track->SetX1(.01);
pieleg_track->SetY1(.2);

pieleg_track->SetX2(.35);
pieleg_track->SetY2(.85);
//pieleg->Draw();
char Legend_total_track_char[1024];
sprintf(Legend_total_track_char,  "[%2.1f]",totalWeight_Track);
std::string totalTrack_numberstring(Legend_total_track_char);

std::string Title_track = HistTitle + " ["+ Data_type + "] ["+ CVS_title_string + "][Track]" + totalTrack_numberstring + "[" + playlist_name +"]";
plotter->AddHistoTitle(Title_track.c_str(), .04);
plotter->WritePreliminary("TR", .035, 0, 0, false);
gPad->Update();
cpie->Modified();

sprintf(PrintLabel,  "%s.pdf",pdf);
cpie->Print(PrintLabel);




}// End of FUnction

void Draw_TrackTypePieFigures(Hist_map_track Input_map,  const char* pdf, TCanvas *can, MnvPlotter *plotter, bool IsRecoOrData, bool MakCVS, const char* CVS_title , char * Title){

  std::string Data_type = String_Reco_orData(IsRecoOrData);
  std::string CVS_title_string = CVS_title;
  TCanvas *cpie = new TCanvas("cpie","TPie test",700,700);
  std::vector<int> PieColors = {
    TColor::GetColor("#EEFF00"), // neonyellow,
    TColor::GetColor("#DF00FF"), //'psychedelic Purple
    TColor::GetColor("#ffc922"), //'sunset yellow'
    TColor::GetColor("#87CEEB"),//'skyblue'
    TColor::GetColor("#0859C6"), //blue
    TColor::GetColor("#654522"), // yellowishbrown,
  };


auto Track_Map_vector = Input_map.Track_vector;
auto VertexOptions_Map_vector = Input_map.VertexOptions_vector;
auto boolNTrack_Map_vector = Input_map.boolNTrack_vector;


auto playlist_name = GetPlaylist_InitialName(Input_map.playlist);
char playlist_name_char[playlist_name.length()+1]; strcpy(playlist_name_char,playlist_name.c_str());
unsigned int n_size_track = Track_Map_vector.size();
unsigned int n_size_VertexOptions = VertexOptions_Map_vector.size();
unsigned int n_size_boolNTrack = boolNTrack_Map_vector.size();


char CVS_name_track[1024];
char CVS_name_VertexOptions[1024];
char CVS_name_boolNTrack[1024];
char Data_type_char[Data_type.length()+1];
strcpy(Data_type_char,Data_type.c_str());

sprintf(CVS_name_track,      "%s_BREAKDOWNS_%s_Track_ME%s.cvs", Data_type_char, CVS_title, playlist_name_char );
sprintf(CVS_name_VertexOptions,      "%s_BREAKDOWNS_%s_VertexOptions_ME%s.cvs", Data_type_char, CVS_title, playlist_name_char );
sprintf(CVS_name_boolNTrack,      "%s_BREAKDOWNS_%s_boolNTrack_ME%s.cvs", Data_type_char, CVS_title, playlist_name_char );

  std::ofstream myfile_track;
  std::ofstream myfile_VertexOptions;
  std::ofstream myfile_boolNTrack;

  if(MakCVS==true){
    myfile_track.open(CVS_name_track);
    myfile_track<<"Track, number events, percentage \n";
    myfile_VertexOptions.open(CVS_name_VertexOptions);
    myfile_VertexOptions<<"VertexOptions, number events, percentage \n";
    myfile_boolNTrack.open(CVS_name_boolNTrack);
    myfile_boolNTrack<<"boolNTrack, number events, percentage \n";


  }

double totalWeight_Track=0.0;
for(unsigned int i = 0; i != n_size_track; ++i){totalWeight_Track+=Track_Map_vector.at(i).Amount;}
TPie *pie_Track       = new TPie("pie_Track",       "pie_Track",      n_size_track);

double totalWeight_VertexOptions=0.0;
for(unsigned int i = 0; i != n_size_VertexOptions; ++i){totalWeight_VertexOptions+=VertexOptions_Map_vector.at(i).Amount;}
TPie *pie_VertexOptions       = new TPie("pie_VertexOptions",       "pie_VertexOptions",      n_size_VertexOptions );

double totalWeight_boolNTrack=0.0;
for(unsigned int i = 0; i != n_size_boolNTrack; ++i){totalWeight_boolNTrack+=boolNTrack_Map_vector.at(i).Amount;}
TPie *pie_boolNTrack       = new TPie("pie_boolNTrack",       "pie_boolNTrack",      n_size_boolNTrack);


// Track type
for ( unsigned int i = 0; i != n_size_track; ++i )
{
  auto type = Track_Map_vector.at(i).type;
  auto track_name = GetNameTrack(type);
  char track_name_char[track_name.length()+1];
  strcpy(track_name_char,track_name.c_str());
  std::cout<<"Checking track name = "<< track_name_char<<std::endl;
  double weight = Track_Map_vector.at(i).Amount;
  double fraction = 100*(weight / totalWeight_Track);
  char Legend_title_char[1024];
  sprintf(Legend_title_char,  "%s [%2.2f%%] (%2.1f)",track_name_char ,fraction , weight );
  std::cout<<"Legend title Track = "<< Legend_title_char <<std::endl;
  char CVS_input_char[1024];

  if(MakCVS==true){
    sprintf(CVS_input_char,  "%s, %2.2f , %2.2f", track_name_char  ,weight,fraction );
    myfile_track<< CVS_input_char << "\n";
  }

  pie_Track->SetEntryVal(i,weight);
  pie_Track->SetEntryLabel(i, Legend_title_char);
  pie_Track->SetEntryFillColor(i,PieColors.at(i));

}


//  VertexOptions type
for ( unsigned int i = 0; i != n_size_VertexOptions; ++i )
{
  auto type = VertexOptions_Map_vector.at(i).type;
  auto VertexOptions_name = GetNameVertexOption(type);
  char VertexOptions_name_char[VertexOptions_name.length()+1];
  strcpy(VertexOptions_name_char,VertexOptions_name.c_str());
  std::cout<<"Checking VertexOptions name = "<< VertexOptions_name_char<<std::endl;
  double weight = VertexOptions_Map_vector.at(i).Amount;
  double fraction = 100*(weight / totalWeight_Track);
  char Legend_title_char[1024];
  sprintf(Legend_title_char,  "%s [%2.2f%%] (%2.1f)",VertexOptions_name_char ,fraction , weight );
  std::cout<<"Legend title Track = "<< Legend_title_char <<std::endl;
  char CVS_input_char[1024];

  if(MakCVS==true){
    sprintf(CVS_input_char,  "%s, %2.2f , %2.2f", VertexOptions_name_char  ,weight,fraction );
    myfile_VertexOptions<< CVS_input_char << "\n";
  }

  pie_VertexOptions->SetEntryVal(i,weight);
  pie_VertexOptions->SetEntryLabel(i, Legend_title_char);
  pie_VertexOptions->SetEntryFillColor(i,PieColors.at(i));

}
////

//  boolNTrack type
for ( unsigned int i = 0; i != n_size_boolNTrack; ++i )
{
  auto type = boolNTrack_Map_vector.at(i).type;
  auto boolNTrack_name = GetName_boolNTrack(type);
  char boolNTrack_name_char[boolNTrack_name.length()+1];
  strcpy(boolNTrack_name_char,boolNTrack_name.c_str());
  std::cout<<"Checking VertexOptions name = " << boolNTrack_name_char<<std::endl;
  double weight = boolNTrack_Map_vector.at(i).Amount;
  double fraction = 100*(weight / totalWeight_Track);
  char Legend_title_char[1024];
  sprintf(Legend_title_char,  "%s [%2.2f%%] (%2.1f)",boolNTrack_name_char ,fraction , weight );
  std::cout<<"Legend title Track = "<< Legend_title_char <<std::endl;
  char CVS_input_char[1024];

  if(MakCVS==true){
    sprintf(CVS_input_char,  "%s, %2.2f , %2.2f", boolNTrack_name_char  ,weight,fraction );
    myfile_boolNTrack<< CVS_input_char << "\n";
  }

  pie_boolNTrack->SetEntryVal(i,weight);
  pie_boolNTrack->SetEntryLabel(i, Legend_title_char);
  pie_boolNTrack->SetEntryFillColor(i,PieColors.at(i));

}




//
if(MakCVS==true){
  myfile_track.close();
  myfile_VertexOptions.close();
  myfile_boolNTrack.close();
}

//////////////////////////////
//Track Type
////////////////////////////
pie_Track->SetCircle(.68,.45,.31);
pie_Track->SetLabelsOffset(.02);
pie_Track->SetLabelFormat("");

pie_Track->Draw("");
TLegend *pieleg_track = pie_Track->MakeLegend();

pieleg_track->SetX1(.01);
pieleg_track->SetY1(.2);

pieleg_track->SetX2(.35);
pieleg_track->SetY2(.85);
//pieleg->Draw();
char Legend_total_track_char[1024];
sprintf(Legend_total_track_char,  "[%2.1f]",totalWeight_Track);
std::string totalTrack_numberstring(Legend_total_track_char);
std::string someString(Title);
std::string Title_track = someString + " ["+ Data_type + "] ["+ CVS_title_string + "][Track]" + totalTrack_numberstring + "[" + playlist_name +"]";
plotter->AddHistoTitle(Title_track.c_str(), .04);
plotter->WritePreliminary("TR", .035, 0, 0, false);
gPad->Update();
cpie->Modified();
char PrintLabel[1024];
sprintf(PrintLabel,  "%s.pdf",pdf);
cpie->Print(PrintLabel);

//////////////////////////////
//VertexOptions Type
////////////////////////////
pie_VertexOptions->SetCircle(.68,.45,.31);
pie_VertexOptions->SetLabelsOffset(.02);
pie_VertexOptions->SetLabelFormat("");

pie_VertexOptions->Draw("");
TLegend *pieleg_VertexOptions = pie_VertexOptions->MakeLegend();

pieleg_VertexOptions->SetX1(.01);
pieleg_VertexOptions->SetY1(.2);

pieleg_VertexOptions->SetX2(.35);
pieleg_VertexOptions->SetY2(.85);
//pieleg->Draw();
char Legend_total_VertexOptions_char[1024];
sprintf(Legend_total_VertexOptions_char,  "[%2.1f]",totalWeight_VertexOptions);
std::string totalVertexOptions_numberstring(Legend_total_VertexOptions_char);
std::string someString2(Title);
std::string Title_VertexOptions = someString2 + " ["+ Data_type + "] ["+ CVS_title_string + "][VertexOptions]" + totalVertexOptions_numberstring + "[" + playlist_name +"]";
plotter->AddHistoTitle(Title_VertexOptions.c_str(), .04);
plotter->WritePreliminary("TR", .035, 0, 0, false);
gPad->Update();
cpie->Modified();
sprintf(PrintLabel,  "%s.pdf",pdf);
cpie->Print(PrintLabel);



//////////////////////////////
//boolNTrack Type
////////////////////////////
pie_boolNTrack->SetCircle(.68,.45,.31);
pie_boolNTrack->SetLabelsOffset(.02);
pie_boolNTrack->SetLabelFormat("");

pie_boolNTrack->Draw("");
TLegend *pieleg_boolNTrack = pie_boolNTrack->MakeLegend();

pieleg_boolNTrack->SetX1(.01);
pieleg_boolNTrack->SetY1(.2);

pieleg_boolNTrack->SetX2(.35);
pieleg_boolNTrack->SetY2(.85);

sprintf(Legend_total_track_char,  "[%2.1f]",totalWeight_boolNTrack);
std::string totalboolNTrack_numberstring(Legend_total_VertexOptions_char);
std::string someString3(Title);
std::string Title_boolNTrack = someString3+ " ["+ Data_type + "] ["+ CVS_title_string + "][boolNTrack]" + totalboolNTrack_numberstring + "[" + playlist_name +"]";
plotter->AddHistoTitle(Title_boolNTrack.c_str(), .04);
plotter->WritePreliminary("TR", .035, 0, 0, false);
gPad->Update();
cpie->Modified();
sprintf(PrintLabel,  "%s.pdf",pdf);
cpie->Print(PrintLabel);



}// End of FUnction


void DrawPie_Figures_EventCutRate(EventCut_Rate_STRUCT Input_EventStuct,  const char* pdf,
  TCanvas *can, MnvPlotter *plotter, char * Title){


  TCanvas *cpie = new TCanvas("cpie","TPie test",700,700);
  std::vector<int> PieColors = {
    TColor::GetColor("#EEFF00"), // neonyellow,
    TColor::GetColor("#DF00FF"), //'psychedelic Purple
    TColor::GetColor("#ffc922"), //'sunset yellow'
    TColor::GetColor("#87CEEB"),//'skyblue'
    TColor::GetColor("#0859C6"), //blue
    TColor::GetColor("#654522"), // yellowishbrown,
    TColor::GetColor(  43, 206,  72 ), //green
    TColor::GetColor("#FF0800"),//2 candy Apple
    TColor::GetColor("#90AD1C"),
    TColor::GetColor("#BABABA"), //Gray
    TColor::GetColor("#00FFFF"),//'aqua'
    TColor::GetColor("#F1B6DA"),//pink
    TColor::GetColor("#00A86B"),//'Jade'
    TColor::GetColor("#FAFAD2"),  // LightGoldenRodYellow
    TColor::GetColor("#800000"),  // Maroon
    TColor::GetColor("#555555"),  // dark grey
    TColor::GetColor(0, 153, 143 ), //turquoise
    TColor::GetColor("#654522"), // yellowishbrown,
    TColor::GetColor("#8db600"), // yellowgreen,
    TColor::GetColor("#D3D3D3"),  //'lightgrey'
     TColor::GetColor("#90AD1C"),
     TColor::GetColor("#CCDDAA")
  };





auto playlist_name = GetPlaylist_InitialName(Input_EventStuct.playlist);
char playlist_name_char[playlist_name.length()+1]; strcpy(playlist_name_char,playlist_name.c_str());

int TRUTH_nsize = Input_EventStuct.TRUTHBRANCH_TRUE_EVENTSECTION_MAP.size();
int TRUTH_nsize_Helium = Input_EventStuct.TRUTHBRANCH_TRUE_EVENTSECTION_MAP.size() -  3;


TPie *pie_TRUTHBRANCH_ALLCUTS       = new TPie("pie_TRUTHBRANCH_ALLCUTS",       "pie_TRUTHBRANCH_ALLCUTS",      TRUTH_nsize);
TPie *pie_TRUTHBRANCH_TRUE_HELIUM       = new TPie("pie_TRUTHBRANCH_TRUE_HELIUM",       "pie_TRUTHBRANCH_TRUE_HELIUM",      TRUTH_nsize_Helium);
// ALL Cuts
 std::map<ECutsTRUTH, double >::iterator TRUTH_it;
 std::map<ECuts, double >::iterator RECO_it;

double totalWeight_Track = Input_EventStuct.TRUTHBRANCH_TRUE_EVENTSECTION_MAP[kTRUTHNoCuts];
double totalWeightHelium_Track = Input_EventStuct.TRUTHBRANCH_TRUE_EVENTSECTION_MAP[kTRUTHtarget];
TRUE_Cut_Map Helium_TRUE_MAP;
int i=0;


for ( TRUTH_it = Input_EventStuct.TRUTHBRANCH_TRUE_EVENTSECTION_MAP.begin(); TRUTH_it != Input_EventStuct.TRUTHBRANCH_TRUE_EVENTSECTION_MAP.end(); TRUTH_it++ )
{
  auto type = TRUTH_it->first;
  auto track_name = GetCutNameLatexforRootTRUTH(type);
  char track_name_char[track_name.length()+1];
  strcpy(track_name_char,track_name.c_str());
  //std::cout<<"Checking track name = "<< track_name_char<<std::endl;
  double weight = TRUTH_it->second;
  double fraction = 100 * (weight / totalWeight_Track);
  char Legend_title_char[1024];
  sprintf(Legend_title_char,  "%s [%2.2f%%] (%2.1f)",track_name_char , fraction , weight );
  std::cout<<"Legend title Track = "<< Legend_title_char <<std::endl;

  if(type >= kTRUTHtarget){
    Helium_TRUE_MAP.insert(std::make_pair(type, weight));
  }

  if(type ==kTRUTHNoCuts){
    pie_TRUTHBRANCH_ALLCUTS->SetEntryVal(i,0);
    pie_TRUTHBRANCH_ALLCUTS->SetEntryLabel(i, Legend_title_char);
    pie_TRUTHBRANCH_ALLCUTS->SetEntryFillColor(i,PieColors.at(i));
  }
  else{
    pie_TRUTHBRANCH_ALLCUTS->SetEntryVal(i,fraction);
    pie_TRUTHBRANCH_ALLCUTS->SetEntryLabel(i, Legend_title_char);
    pie_TRUTHBRANCH_ALLCUTS->SetEntryFillColor(i,PieColors.at(i));
  }
  i++;

}

i=0;

for ( TRUTH_it = Helium_TRUE_MAP.begin(); TRUTH_it != Helium_TRUE_MAP.end(); TRUTH_it++ )
{
  auto type = TRUTH_it->first;
  auto track_name = GetCutNameLatexforRootTRUTH(type);
  char track_name_char[track_name.length()+1];
  strcpy(track_name_char,track_name.c_str());
  //std::cout<<"Checking track name = "<< track_name_char<<std::endl;
  double weight = TRUTH_it->second;
  double fraction = 100* (weight / totalWeightHelium_Track);
  char Legend_title_char[1024];
  sprintf(Legend_title_char,  "%s [%2.2f%%] (%2.1f)",track_name_char ,fraction , weight );
  std::cout<<"Legend title Track = "<< Legend_title_char <<std::endl;

  if(type ==kTRUTHtarget){
    pie_TRUTHBRANCH_TRUE_HELIUM ->SetEntryVal(i,0);
    pie_TRUTHBRANCH_TRUE_HELIUM ->SetEntryLabel(i, Legend_title_char);
    pie_TRUTHBRANCH_TRUE_HELIUM ->SetEntryFillColor(i,PieColors.at(i));
  }
  else{
    pie_TRUTHBRANCH_TRUE_HELIUM ->SetEntryVal(i,fraction);
    pie_TRUTHBRANCH_TRUE_HELIUM ->SetEntryLabel(i, Legend_title_char);
    pie_TRUTHBRANCH_TRUE_HELIUM ->SetEntryFillColor(i,PieColors.at(i));
  }



  i++;



}
//  VertexOptions//


//////////////////////////////
//ALL CUTS TRUTH
////////////////////////////
pie_TRUTHBRANCH_ALLCUTS->SetCircle(.68,.45,.31);
pie_TRUTHBRANCH_ALLCUTS->SetLabelsOffset(.02);
pie_TRUTHBRANCH_ALLCUTS->SetLabelFormat("");

pie_TRUTHBRANCH_ALLCUTS->Draw("");
TLegend *pieleg_TRUTH = pie_TRUTHBRANCH_ALLCUTS->MakeLegend();

pieleg_TRUTH->SetX1(.01);
pieleg_TRUTH->SetY1(.2);

pieleg_TRUTH->SetX2(.35);
pieleg_TRUTH->SetY2(.85);
//pieleg->Draw();
char Legend_total_track_char[1024];
sprintf(Legend_total_track_char,  "[%2.1f]",totalWeight_Track);

std::string someString(Title);
std::string Title_track = someString + " [TRUTH] " + "[" + playlist_name +"][ALL Cuts]" ;
plotter->AddHistoTitle(Title_track.c_str(), .04);
plotter->WritePreliminary("TR", .035, 0, 0, false);
gPad->Update();
cpie->Modified();
char PrintLabel[1024];
sprintf(PrintLabel,  "%s.pdf",pdf);
cpie->Print(PrintLabel);

//////////////////////////////////////////////
// TRUTH  out of HELIUM
/////////////////////////////////////////////
pie_TRUTHBRANCH_TRUE_HELIUM->SetCircle(.68,.45,.31);
pie_TRUTHBRANCH_TRUE_HELIUM->SetLabelsOffset(.02);
pie_TRUTHBRANCH_TRUE_HELIUM->SetLabelFormat("");

pie_TRUTHBRANCH_TRUE_HELIUM->Draw("");
TLegend *pieleg_Helium = pie_TRUTHBRANCH_TRUE_HELIUM->MakeLegend();

pieleg_Helium->SetX1(.01);
pieleg_Helium->SetY1(.2);

pieleg_Helium->SetX2(.35);
pieleg_Helium->SetY2(.85);
char Legend_total_Helium_char[1024];
sprintf(Legend_total_Helium_char,  "[%2.1f]",totalWeightHelium_Track);

std::string someString_helium(Title);
std::string Title_track_Helium = someString_helium + " [TRUTH] " + "[" + playlist_name +"][CC Neutrino Helium: " + Legend_total_track_char +  "]" ;
plotter->AddHistoTitle(Title_track_Helium.c_str(), .04);
plotter->WritePreliminary("TR", .035, 0, 0, false);
gPad->Update();
cpie->Modified();
cpie->Print(PrintLabel);
//////////////////
//////////
////////////////

double totalWeight_RECO = Input_EventStuct.RECOBRANCH_TRUE_RECO_EVENTSECTION_MAP[kNoCuts];
int RECO_nsize = Input_EventStuct.RECOBRANCH_TRUE_RECO_EVENTSECTION_MAP.size();

double totalWeight_RECOBranch_TRUE = Input_EventStuct.TRUTHBRANCH_TRUE_EVENTSECTION_MAP[kTRUTHNoCuts];
//int TRUTH_RECO_nsize = Input_EventStuct.RECOBRANCH_TRUE_EVENTSECTION_MAP.size();

TPie *pie_RECOBRANCH_RECO       = new TPie("pie_RECOBRANCH_RECO",       "pie_RECOBRANCH_RECO",      RECO_nsize);
//TPie *pie_RECOBRANCH_TRUE_HELIUM       = new TPie("pie_TRUTHBRANCH_TRUE_HELIUM",       "pie_TRUTHBRANCH_TRUE_HELIUM",      TRUTH_RECO_nsize);

i=0;
for ( RECO_it = Input_EventStuct.RECOBRANCH_TRUE_RECO_EVENTSECTION_MAP.begin(); RECO_it != Input_EventStuct.RECOBRANCH_TRUE_RECO_EVENTSECTION_MAP.end(); RECO_it++ )
{
  auto type = RECO_it->first;
  auto track_name = GetCutNameforRootLatex(type);
  char track_name_char[track_name.length()+1];
  strcpy(track_name_char,track_name.c_str());
  //std::cout<<"Checking track name = "<< track_name_char<<std::endl;
  double weight = RECO_it->second;
  double fraction = 100*(weight / totalWeight_RECO );
  char Legend_title_char[1024];
  sprintf(Legend_title_char,  "%s [%2.2f%%] (%2.1f)",track_name_char , fraction , weight );
  std::cout<<"Legend title Track = "<< Legend_title_char <<std::endl;
if(type==kNoCuts){
  pie_RECOBRANCH_RECO->SetEntryVal(i,0);
  pie_RECOBRANCH_RECO->SetEntryLabel(i, Legend_title_char);
  pie_RECOBRANCH_RECO->SetEntryFillColor(i,PieColors.at(i));
}
else{
  pie_RECOBRANCH_RECO->SetEntryVal(i,fraction);
  pie_RECOBRANCH_RECO->SetEntryLabel(i, Legend_title_char);
  pie_RECOBRANCH_RECO->SetEntryFillColor(i,PieColors.at(i));
}


  i++;
}

//////////////////////////////////////////////
// RECO  out of HELIUM
/////////////////////////////////////////////
pie_RECOBRANCH_RECO->SetCircle(.68,.45,.31);
pie_RECOBRANCH_RECO->SetLabelsOffset(.02);
pie_RECOBRANCH_RECO->SetLabelFormat("");

pie_RECOBRANCH_RECO->Draw("");
TLegend *pieleg_RECO = pie_RECOBRANCH_RECO->MakeLegend();

pieleg_RECO->SetX1(.01);
pieleg_RECO->SetY1(.2);

pieleg_RECO->SetX2(.35);
pieleg_RECO->SetY2(.85);
char Legend_total_RECO_char[1024];
sprintf(Legend_total_RECO_char,  "[%2.1f]",totalWeight_RECOBranch_TRUE);

std::string someString_RECO(Title);
std::string Title_track_RECO = someString_RECO + " [RECO] " + "[" + playlist_name +"][" + Legend_total_track_char +  "]" ;
plotter->AddHistoTitle(Title_track_RECO.c_str(), .04);
plotter->WritePreliminary("TR", .035, 0, 0, false);
gPad->Update();
cpie->Modified();
cpie->Print(PrintLabel);





}// End of FUnction
//////////////////////////////////////////////
/////
/////////////////////////////////////////////
void Draw_MCHist_fromTFile(TFile *inputFile_MCinput,  char *histoName_MC, std::string pdf_label, char *histotitle, char *xaxislabel,char* yaxislabel, bool DoBinwidthNorm )
{
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  std::cout<<"trying to draw 1D, HisName  = "<< histoName_MC<<std::endl;
  MnvH1D *hist1 = (MnvH1D*)inputFile_MCinput -> Get(histoName_MC);
  auto hist = (PlotUtils::MnvH1D*)hist1->Clone("hist1");
  string TotalTitle = string(histotitle);


 hist->GetXaxis()->CenterTitle();
 hist->GetYaxis()->CenterTitle();
 hist->GetXaxis()->SetTitle(xaxislabel);
 hist->GetYaxis()->SetTitle(yaxislabel);
 hist->GetXaxis()->SetTitleSize(0.038);
 hist->GetYaxis()->SetTitleSize(0.038);
 hist->SetLineColor(kBlue);
 hist->SetFillColor(kRed);
 hist->SetMaximum(hist->GetMaximum() * 1.25);
 hist->Draw("Hist");

 char total_title[1024];
 sprintf(total_title, "%s", histotitle);
 mnvPlotter.AddHistoTitle(total_title, .04);
 mnvPlotter.WritePreliminary("TL", .035, 0, 0, false);
 std::string plotname = Form("%s",pdf_label.c_str());
 mnvPlotter.MultiPrint(&cE, plotname, "pdf");
 cE.Closed();

}




void Draw_DataHist_fromTFile(TFile *inputFile_DatainputFULL, TFile *inputFile_DatainputEmpty,
   char *histoName_data, char *Playlist_name_FULL, char *Playlist_name_EMPTY, std::string pdf_label,
    char *histotitle, char *xaxislabel,char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG, Pot_MapStatusList POT_DATA )
{
  double scale_to_FULL= POT_DATA[kFULL] / POT_DATA[kEMPTY];

  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  std::cout<<"trying to draw 1D, HisName  = "<<histoName_data<<std::endl;
  MnvH1D *hist_FULL = (MnvH1D*)inputFile_DatainputFULL -> Get(histoName_data);
  MnvH1D *hist_EMPTY = (MnvH1D*)inputFile_DatainputEmpty -> Get(histoName_data);
  auto hist_FULL_EMPTY = (PlotUtils::MnvH1D*)hist_FULL->Clone("hist_FULL");
  hist_EMPTY->Scale(scale_to_FULL);
  hist_FULL_EMPTY->Add(hist_EMPTY,-1);
  string TotalTitle = string(histotitle);

  SetHist_Data(*hist_FULL, xaxislabel , yaxislabel);
  SetHist_Data(*hist_EMPTY, xaxislabel , yaxislabel);
  SetHist_Data(*hist_FULL_EMPTY, xaxislabel , yaxislabel);


  if(DoBinwidthNorm==true){
    hist_FULL->Scale(1.0,"width");
    hist_EMPTY->Scale(1.0,"width");
    hist_FULL_EMPTY->Scale(1.0,"width");
  }

  if(MakeXaxisLOG==true){
    gPad->SetLogx();
  }


  hist_FULL->Draw("PEC");
 char total_title[1024];
 sprintf(total_title, "%s [DATA][FULL][%s]", histotitle, Playlist_name_FULL);
 mnvPlotter.AddHistoTitle(total_title, .04);
 mnvPlotter.WritePreliminary("TL", .035, 0, 0, false);
 std::string plotname = Form("%s",pdf_label.c_str());
 mnvPlotter.MultiPrint(&cE, plotname, "pdf");

 hist_EMPTY->Draw("PEC");
sprintf(total_title, "%s [DATA][Empty][%s]", histotitle, Playlist_name_EMPTY);
mnvPlotter.AddHistoTitle(total_title, .04);
mnvPlotter.WritePreliminary("TL", .035, 0, 0, false);
mnvPlotter.MultiPrint(&cE, plotname, "pdf");

hist_FULL_EMPTY->Draw("PEC");
sprintf(total_title, "%s [DATA][F-E][%s-%s]", histotitle, Playlist_name_FULL,Playlist_name_EMPTY);
mnvPlotter.AddHistoTitle(total_title, .04);
mnvPlotter.WritePreliminary("TL", .035, 0, 0, false);
mnvPlotter.MultiPrint(&cE, plotname, "pdf");
cE.Closed();

if(MakeXaxisLOG==true){
gPad->SetLogx(0);
}


}

void Draw_DataWITHMC_Hist_fromTFile(TFile *inputFile_MCinputFULL, TFile *inputFile_MCinputEmpty, char *histoName_MC,
  TFile *inputFile_DatainputFULL, TFile *inputFile_DatainputEmpty,char *histoName_data,
  char *Playlist_name_FULL, char *Playlist_name_EMPTY, std::string pdf_label, char *histotitle,
   char *xaxislabel,char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG, Pot_MapStatusList POT_DATA, Pot_MapStatusList POT_MC )
{
  double scale_to_FULL= POT_DATA[kFULL] / POT_DATA[kEMPTY];

  double MC_scale_to_FULL = POT_DATA[kFULL] / POT_MC[kFULL];

  double MC_EMPTYscale_to_FULL = POT_DATA[kFULL] / POT_MC[kEMPTY];


  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  std::cout<<"trying to draw 1D, HisName  = "<<histoName_data<<std::endl;
  //SCALING DATA
  MnvH1D *hist_FULL = (MnvH1D*)inputFile_DatainputFULL -> Get(histoName_data);
  std::cout<<"GOT  DATA FULL = "<<histoName_data<<std::endl;

  MnvH1D *hist_EMPTY = (MnvH1D*)inputFile_DatainputEmpty -> Get(histoName_data);
    std::cout<<"GOT DATA EMPTY = "<<histoName_data<<std::endl;
  auto hist_FULL_EMPTY = (PlotUtils::MnvH1D*)hist_FULL->Clone("hist_FULL");
    std::cout<<"Cloned FULL  "<<histoName_data <<std::endl;
  auto hist_COPYEMPTY = (PlotUtils::MnvH1D*)hist_EMPTY->Clone("hist_EMPTY");
  std::cout<<"Cloned Empty  "<<histoName_data <<std::endl;
  hist_EMPTY->Scale(scale_to_FULL);
  std::cout<<"scaled empty to full   "<<histoName_data <<std::endl;
  hist_COPYEMPTY->Scale(scale_to_FULL);
  std::cout<<"scaled empty copy to full   "<<histoName_data <<std::endl;
  hist_FULL_EMPTY->Add(hist_COPYEMPTY,-1);
  std::cout<<"subtracted empty copy to  from full   "<<histoName_data <<std::endl;

  // SCALING MC
  std::cout<<"Trying to get MC = "<<histoName_MC<<std::endl;
  MnvH1D *histMC_FULL = (MnvH1D*)inputFile_MCinputFULL->Get(histoName_MC);
  std::cout<<"GOT  MC  FULL = "<<histoName_MC<<std::endl;
  MnvH1D *histMC_EMPTY = (MnvH1D*)inputFile_MCinputEmpty->Get(histoName_MC);
  std::cout<<"GOT  MC  Empty = "<<histoName_MC<<std::endl;
  auto histMC_FULL_EMPTY = (PlotUtils::MnvH1D*)histMC_FULL->Clone("histMC_FULL");
  auto histMC_COPYEMPTY = (PlotUtils::MnvH1D*)histMC_EMPTY->Clone("histMC_EMPTY");
  histMC_FULL->Scale(MC_scale_to_FULL);
  histMC_FULL_EMPTY->Scale(MC_scale_to_FULL);
  histMC_EMPTY->Scale(MC_EMPTYscale_to_FULL);
  histMC_COPYEMPTY->Scale(MC_EMPTYscale_to_FULL);
  histMC_FULL_EMPTY->Add(histMC_COPYEMPTY,-1);

  string TotalTitle = string(histotitle);

  SetHist_Data(*hist_FULL, xaxislabel , yaxislabel);
  SetHist_Data(*hist_EMPTY, xaxislabel , yaxislabel);
  SetHist_Data(*hist_FULL_EMPTY, xaxislabel , yaxislabel);


  if(DoBinwidthNorm==true){
    hist_FULL->Scale(1.0,"width");
    histMC_FULL->Scale(1.0,"width");
    hist_EMPTY->Scale(1.0,"width");
    histMC_EMPTY->Scale(1.0,"width");
    hist_FULL_EMPTY->Scale(1.0,"width");
    histMC_FULL_EMPTY->Scale(1.0,"width");
  }

  if(MakeXaxisLOG==true){
    gPad->SetLogx();
  }

  SetMaxforDraw(hist_FULL,histMC_FULL);
  SetMaxforDraw(hist_EMPTY,histMC_EMPTY);
  SetMaxforDraw(hist_FULL_EMPTY, histMC_FULL_EMPTY);



  hist_FULL->SetMarkerColor(kBlack);
  hist_FULL->Draw("PEC");
  histMC_FULL->SetLineColor(kRed);
  histMC_FULL->Draw("Hist same");
  char total_title[1024];
  sprintf(total_title, "%s [FULL][%s]", histotitle, Playlist_name_FULL);
  mnvPlotter.AddHistoTitle(total_title, .04);
  mnvPlotter.WritePreliminary("TL", .035, 0, 0, false);
  std::string plotname = Form("%s",pdf_label.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");

  hist_EMPTY->SetMarkerColor(kBlack);
  hist_EMPTY->Draw("PEC");
  histMC_EMPTY->SetLineColor(kRed);
  histMC_EMPTY->Draw("Hist same");
  sprintf(total_title, "%s [Empty][%s]", histotitle, Playlist_name_EMPTY);
  mnvPlotter.AddHistoTitle(total_title, .04);
  mnvPlotter.WritePreliminary("TL", .035, 0, 0, false);
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");

  hist_FULL_EMPTY->SetMarkerColor(kBlack);
  hist_FULL_EMPTY->Draw("PEC");
  histMC_FULL_EMPTY->SetLineColor(kRed);
  histMC_FULL_EMPTY->Draw("Hist same");
  sprintf(total_title, "%s [F-E][%s-%s]", histotitle, Playlist_name_FULL,Playlist_name_EMPTY);
  mnvPlotter.AddHistoTitle(total_title, .04);
  mnvPlotter.WritePreliminary("TL", .035, 0, 0, false);
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");
  cE.Closed();

  if(MakeXaxisLOG==true){
    gPad->SetLogx(0);
  }
}

void Draw_DataWITHMC_SingleHistinput(MnvH1D *hist_MC_input, MnvH1D *hist_Data_input,
  char *Playlist_name, std::string pdf_label, char *histotitle, std::string units,
   char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG)
{

  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  double x1,x2,y1,y2;
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", .5, 10, .025);
  TLegend *legend = new TLegend(x1 - .02, y1+.31 , x2 +.06 , y2 + .42  );

  MnvH1D *hist_MC = (MnvH1D *)hist_MC_input->Clone(uniq());
  MnvH1D* hist_Data = (MnvH1D *)hist_Data_input->Clone(uniq());
  string TotalTitle = string(histotitle);

  SetHist_Data(*hist_MC, xaxislabel , yaxislabel);

  if(MakeXaxisLOG==true){
    gPad->SetLogx();
  }

  SetMaxforDraw(hist_MC,hist_Data);

  legend->SetNColumns(1);
  legend->SetTextSize(.03);
  legend->SetFillColor(0);

  char ytitle[100];
  //int units_n = ;
  char units_char[units.length()+1];
  strcpy( units_char,units.c_str());

  if(DoBinwidthNorm==true){
    double binwidth_title = hist_MC -> GetBinWidth(3);
    sprintf(ytitle, "Number of Events / %.2f %s", binwidth_title, units_char); //
    hist_MC->GetYaxis()->SetTitle(ytitle);
  }
  else{
    sprintf(ytitle, "Number of Events "); //
    hist_MC->GetYaxis()->SetTitle(ytitle);
  }

  //hist_a->SetFillColor(1);
  hist_MC->SetLineWidth(3);
  hist_MC->SetLineColor(2);
  hist_MC->GetXaxis()->SetTitle(xaxislabel);
  hist_MC->GetXaxis()->CenterTitle();
  hist_MC->GetYaxis()->CenterTitle();
  hist_MC->GetYaxis()->SetTitleSize(0.038);
  hist_MC->GetXaxis()->SetTitleSize(0.038);
  hist_MC->SetTitle(histotitle);
  legend->Clear();
  legend->AddEntry(hist_MC, "MC v1Tune", "fl");
  legend->AddEntry(hist_Data, "Data","lep");

  bool statPlusSys           = true;
  bool useHistTitles         = false;
  int mcScale                = 1.;
  int ndf=0;
  Double_t chi_2 = mnvPlotter.Chi2DataMC(hist_Data, hist_MC,ndf,1.0,false,false );
  ndf = hist_MC->GetNbinsX();
  if(DoBinwidthNorm==true){
    hist_MC->Scale(1,"width");
    hist_Data->Scale(1,"width");
  }
  mnvPlotter.DrawDataMCWithErrorBand(hist_Data, hist_MC, mcScale, "N", useHistTitles, NULL, NULL, false, statPlusSys);

  char chi_label[1024];

  sprintf(chi_label, "#chi^{2}/ndf = %.2f / %i", chi_2,ndf);
  legend -> AddEntry((TObject*)0, chi_label, "");
  legend -> Draw();
  mnvPlotter.WritePreliminary("TL", .03, 0, 0, false);
  char total_title[1024];
  sprintf(total_title, "%s  [%s]", histotitle, Playlist_name);
  mnvPlotter.AddHistoTitle(total_title, .04);


  std::string plotname = Form("%s",pdf_label.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");
  mnvPlotter.legend_n_columns = 2;
 // PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);
 std::string xaxislabel_string(xaxislabel);
  PlotErrorSummaryNew(hist_MC, plotname, histotitle, xaxislabel_string.c_str(), &cE, &mnvPlotter,true,false);
  mnvPlotter.legend_n_columns = 1;

  cE.Closed();

  if(MakeXaxisLOG==true){
    gPad->SetLogx(0);
  }


} // end of Function
///////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////
void Draw_DataWITHMC_SingleHistinput_withRatio(MnvH1D *hist_MC_input, MnvH1D *hist_Data_input,
  char *Playlist_name, std::string pdf_label, char *histotitle, std::string units,
  char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG,
  bool MakeYaxisLOG , bool drawAllErrorGroups )
  {
    PlotUtils::MnvH1D* hist_MC = (PlotUtils::MnvH1D*)hist_MC_input->Clone("hist_MC");
    PlotUtils::MnvH1D* hist_MC2 = (PlotUtils::MnvH1D*)hist_MC_input->Clone("hist_MC");
    PlotUtils::MnvH1D* hist_Data = (PlotUtils::MnvH1D*)hist_Data_input->Clone("hist_Data");

    PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
    TCanvas cE("cE","cE", 800, 800);
    double margin = 0.0;
    if(MakeYaxisLOG==true){
      margin = 1.E-8;
    }
    TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
    pad1->SetBottomMargin(margin); // Upper and lower plot are joined
    //pad1->SetGridx();         // Vertical grid
    pad1->Draw();             // Draw the upper pad: pad1
    pad1->cd();               // pad1 becomes the current pad
    double x1,x2,y1,y2;
    mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", .5, 10, .025);
    TLegend *legend = new TLegend(x1 - .02, y1+.28 , x2 +.075 , y2 + .4  );


    string TotalTitle = string(histotitle);

    SetHist_Data(*hist_MC, xaxislabel , yaxislabel);

    if(MakeXaxisLOG==true){
      gPad->SetLogx();
    }


    if(MakeYaxisLOG==true){
      gPad->SetLogy();
      mnvPlotter.axis_minimum = .01;
    }

    SetMaxforDraw(hist_MC,hist_Data);

    legend->SetNColumns(1);
    legend->SetTextSize(.03);
    legend->SetFillColor(0);

    char ytitle[100];
    //int units_n = ;
    char units_char[units.length()+1];
    strcpy( units_char,units.c_str());

    if(DoBinwidthNorm==true){
      double binwidth_title = hist_MC -> GetBinWidth(3);
      sprintf(ytitle, "%s / %.2f %s", yaxislabel, binwidth_title, units_char); //
      hist_MC->GetYaxis()->SetTitle(ytitle);
    }
    else{
      sprintf(ytitle, "%s",yaxislabel); //
      hist_MC->GetYaxis()->SetTitle(ytitle);
    }

    //hist_a->SetFillColor(1);
    hist_MC->SetLineWidth(3);
    hist_MC->SetLineColor(2);
    hist_MC->GetXaxis()->SetTitle(xaxislabel);
    hist_MC->GetXaxis()->CenterTitle();
    hist_MC->GetYaxis()->CenterTitle();
    hist_MC->GetYaxis()->SetTitleSize(0.037);
    hist_MC->GetXaxis()->SetTitleSize(0.038);
    hist_MC->SetTitle(histotitle);
    legend->Clear();
    hist_MC->SetLineColor(mnvPlotter.mc_color);
    hist_MC->SetLineWidth(mnvPlotter.mc_line_width);
    hist_MC->SetLineStyle(mnvPlotter.mc_line_style);
    hist_MC->SetFillColor(mnvPlotter.mc_error_color);
    hist_MC->SetFillStyle(mnvPlotter.mc_error_style);

    legend->AddEntry(hist_MC, "MINER#nuA v1-Tune", "fl");
    legend->AddEntry(hist_Data, "Data","lep");

    bool statPlusSys           = true;
    bool useHistTitles         = false;
    int mcScale                = 1.;
    int ndf=0;
    Double_t chi_2 = mnvPlotter.Chi2DataMC(hist_Data, hist_MC,ndf,1.0,false,false );
    ndf = hist_MC->GetNbinsX();
    mnvPlotter.draw_normalized_to_bin_width=false;
    //mnvPlotter.axis_title_size_y = 0.08;
     mnvPlotter.axis_title_offset_y = 1.5;
    mnvPlotter.axis_title_size_y = 0.037;
    if(DoBinwidthNorm==true){
      hist_Data->Scale(1,"width");
      hist_MC->Scale(1,"width");
      hist_MC2->Scale(1,"width");
    }
    double max;

    if(hist_MC->GetMaximum() >hist_Data->GetMaximum() ){max =hist_MC->GetMaximum(); }
    else {max =  hist_Data->GetMaximum(); }
    mnvPlotter.axis_maximum = max * 1.15;
    hist_Data->SetMaximum(max * 1.15);
    hist_MC->SetMaximum(max * 1.15);

    mnvPlotter.DrawDataMCWithErrorBand(hist_Data, hist_MC, mcScale, "N", useHistTitles, NULL, NULL, false, statPlusSys);

    char chi_label[1024];

    sprintf(chi_label, "#chi^{2}/ndf = %.2f / %i", chi_2,ndf);
    legend -> AddEntry((TObject*)0, chi_label, "");
    legend -> Draw();
    mnvPlotter.WritePreliminary("TL", .03, 0, 0, false);
    char total_title[1024];
    sprintf(total_title, "%s  [%s]", histotitle, Playlist_name);
    mnvPlotter.AddHistoTitle(total_title, .04);
    cE.cd();          // Go back to the main canvas before defining pad2
    TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
    pad2->SetTopMargin(0);
    pad2->SetBottomMargin(0.3); // vertical grid
    pad2->SetGridx(); // vertical grid
    pad2->SetGridy(); // vertical grid
    pad2->Draw();
    pad2->cd();       // pad2 becomes the current pad
    mnvPlotter.axis_title_size_x = 0.15;
    mnvPlotter.axis_title_offset_y = .4;
    mnvPlotter.axis_title_offset_x = .75;
    mnvPlotter.axis_title_size_y = 0.1;
    mnvPlotter.axis_label_size = 0.1;
    pad2->SetGridx();
    hist_MC2->GetXaxis()->SetTitle(xaxislabel);
    mnvPlotter.DrawDataMCRatio(hist_Data, hist_MC2, 1.0, true, true , -.5, 2, "#frac{Data}{MC}", false);
    cE.cd();

    std::string plotname = Form("%s",pdf_label.c_str());
    mnvPlotter.MultiPrint(&cE, plotname, "pdf");
    mnvPlotter.legend_n_columns = 2;
    // PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);
    std::string xaxislabel_string(xaxislabel);
    mnvPlotter.axis_title_size_x = 0.038;
    mnvPlotter.axis_title_size_y = 0.035;
    mnvPlotter.axis_label_size = 0.038;
    mnvPlotter.axis_title_offset_y = 1.5;
    mnvPlotter.axis_title_offset_x = 1;
    mnvPlotter.axis_maximum = .25;
    mnvPlotter.legend_text_size = mnvPlotter.legend_text_size*.7;
    PlotErrorSummaryNew(hist_MC2, plotname, histotitle, xaxislabel_string.c_str(), &cE, &mnvPlotter,true, drawAllErrorGroups);
    mnvPlotter.legend_n_columns = 1;

    cE.Closed();

    if(MakeXaxisLOG==true){
      gPad->SetLogx(0);
    }
    if(MakeYaxisLOG==true){
      gPad->SetLogy(0);
    }

  } // end of Function
//////////////////////////////////////////////////////////////////////////////
void Draw_DataWITHMC_SingleHistinput_withRatio(MnvH1D *hist_MC_input, MnvH1D *hist_Data_input,
  char *Playlist_name, std::string pdf_label, char *histotitle, std::string units,
  char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG,
  bool MakeYaxisLOG,bool drawErrors, bool drawAllErrorGroups , double Ymax,
  double &ChiSqr_return, int &ndf_return)
  {

  PlotUtils::MnvH1D* hist_MC = (PlotUtils::MnvH1D*)hist_MC_input->Clone("hist_MC");
  PlotUtils::MnvH1D* hist_Data = (PlotUtils::MnvH1D*)hist_Data_input->Clone("hist_Data");

    PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
    TCanvas cE("cE","cE", 800, 800);
    double margin = 0.0;
    if(MakeYaxisLOG==true){
      margin = 1.E-8;
    }
    TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
    pad1->SetBottomMargin(margin); // Upper and lower plot are joined
    //pad1->SetGridx();         // Vertical grid
    pad1->Draw();             // Draw the upper pad: pad1
    pad1->cd();               // pad1 becomes the current pad
    double x1,x2,y1,y2;
    mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", .5, 10, .025);
    TLegend *legend = new TLegend(x1 - .02, y1+.31 , x2 +.15 , y2 + .42  );


    string TotalTitle = string(histotitle);

    SetHist_Data(*hist_MC, xaxislabel , yaxislabel);

    if(MakeXaxisLOG==true){
      gPad->SetLogx();
    }


    if(MakeYaxisLOG==true){
      gPad->SetLogy();
      mnvPlotter.axis_minimum = .01;
    }

    SetMaxforDraw(hist_MC,hist_Data);

    legend->SetNColumns(1);
    legend->SetTextSize(.03);
    legend->SetFillColor(0);

    char ytitle[100];
    //int units_n = ;
    char units_char[units.length()+1];
    strcpy( units_char,units.c_str());

    if(DoBinwidthNorm==true){
      double binwidth_title = hist_MC -> GetBinWidth(3);
      sprintf(ytitle, "%s / %.2f %s", yaxislabel, binwidth_title, units_char); //
      hist_MC->GetYaxis()->SetTitle(ytitle);
    }
    else{
      sprintf(ytitle, "%s",yaxislabel); //
      hist_MC->GetYaxis()->SetTitle(ytitle);
    }

    //hist_a->SetFillColor(1);
    hist_MC->SetLineWidth(3);
    hist_MC->SetLineColor(2);
    hist_MC->GetXaxis()->SetTitle(xaxislabel);
    hist_MC->GetXaxis()->CenterTitle();
    hist_MC->GetYaxis()->CenterTitle();
    hist_MC->GetYaxis()->SetTitleSize(0.037);
    hist_MC->GetXaxis()->SetTitleSize(0.038);
    hist_MC->SetTitle(histotitle);
    legend->Clear();
    legend->AddEntry(hist_MC, "MINER#nuA v1-Tune", "fl");
    legend->AddEntry(hist_Data, "Data","lep");

    bool statPlusSys           = true;
    bool useHistTitles         = false;
    int mcScale                = 1.;
    int ndf=0;
    Double_t chi_2 = mnvPlotter.Chi2DataMC(hist_Data, hist_MC,ndf,1.0,false,false );

    ndf = hist_MC->GetNbinsX();
    ChiSqr_return = chi_2;
    ndf_return = ndf;
    double chi_dividendf = chi_2 / (double)ndf;
    if(DoBinwidthNorm==true){
      hist_MC->Scale(1.0,"width");
      hist_Data->Scale(1.0,"width");
    }

    //mnvPlotter.axis_title_size_y = 0.08;
    mnvPlotter.axis_title_size_y = 0.037;
    mnvPlotter.axis_maximum = Ymax;
    mnvPlotter.DrawDataMCWithErrorBand(hist_Data, hist_MC, mcScale, "N", useHistTitles, NULL, NULL, false, statPlusSys);

    char chi_label[1024];

    sprintf(chi_label, "#chi^{2}/ndf = %.2f / %i (%.2f)", chi_2,ndf ,chi_dividendf );
    legend -> AddEntry((TObject*)0, chi_label, "");
    legend -> Draw();
    mnvPlotter.WritePreliminary("TL", .03, 0, 0, false);
    char total_title[1024];
    sprintf(total_title, "%s [%s]", histotitle, Playlist_name);
    mnvPlotter.AddHistoTitle(total_title, .04);
    cE.cd();          // Go back to the main canvas before defining pad2
    TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
    pad2->SetTopMargin(0);
    pad2->SetBottomMargin(0.2);
    pad2->Draw();
    pad2->cd();       // pad2 becomes the current pad
    mnvPlotter.axis_title_size_x = 0.1;
    mnvPlotter.axis_title_offset_y = .4;
    mnvPlotter.axis_title_size_y = 0.1;
    mnvPlotter.axis_label_size = 0.1;
    pad2->SetGridx();
    mnvPlotter.DrawDataMCRatio(hist_Data, hist_MC, 1.0, true, true , -1, -1, "#frac{Data}{MC}", false);
    cE.cd();

    std::string plotname = Form("%s",pdf_label.c_str());
    mnvPlotter.MultiPrint(&cE, plotname, "pdf");
     if(drawErrors==true){
    mnvPlotter.legend_n_columns = 2;
    // PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);
    std::string xaxislabel_string(xaxislabel);
    mnvPlotter.axis_title_size_x = 0.038;
    mnvPlotter.axis_title_size_y = 0.038;
    mnvPlotter.axis_label_size = 0.038;

    PlotErrorSummaryNew(hist_MC, plotname, histotitle, xaxislabel_string.c_str(), &cE, &mnvPlotter,true, drawAllErrorGroups);
    mnvPlotter.legend_n_columns = 1;
  }
    cE.Closed();

    if(MakeXaxisLOG==true){
      gPad->SetLogx(0);
    }
    if(MakeYaxisLOG==true){
      gPad->SetLogy(0);
    }

  } // end of Function



/////////////////////////////////////////////////////////////////////////////////////////////
void Draw_DataWITHMC_SingleHistinput_withRatioCrossSection(MnvH1D *hist_MC_input, MnvH1D *hist_Data_input,
  char *Playlist_name, std::string pdf_label, char *histotitle, std::string units,
   char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG , bool drawAllErrorGroups )
{
  MnvH1D * hist_MC = (PlotUtils::MnvH1D*)hist_MC_input->Clone(uniq());
  MnvH1D * hist_MC2 = (PlotUtils::MnvH1D*)hist_MC_input->Clone(uniq());
  MnvH1D * hist_Data = (PlotUtils::MnvH1D*)hist_Data_input->Clone(uniq());
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE("cE","cE", 800, 800);
  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  double x1,x2,y1,y2;
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", .5, 10, .025);
  TLegend *legend = new TLegend(x1 - .02, y1+ .28 , x2 +.075 , y2 + .4 );


  string TotalTitle = string(histotitle);

  SetHist_Data(*hist_MC, xaxislabel , yaxislabel);

  if(MakeXaxisLOG==true){
    gPad->SetLogx();
  }

  SetMaxforDraw(hist_MC,hist_Data);

  legend->SetNColumns(1);
  legend->SetTextSize(.03);
  legend->SetFillColor(0);

  char ytitle[100];
  //int units_n = ;
  char units_char[units.length()+1];
  strcpy( units_char,units.c_str());

  if(DoBinwidthNorm==true){
    double binwidth_title = hist_MC -> GetBinWidth(3);
    sprintf(ytitle, "%s / %.2f [%s]", yaxislabel, binwidth_title, units_char); //
    hist_MC->GetYaxis()->SetTitle(ytitle);
  }
  else{
    sprintf(ytitle, "%s",yaxislabel); //
    hist_MC->GetYaxis()->SetTitle(ytitle);
  }

  //hist_a->SetFillColor(1);
  hist_MC->SetLineWidth(3);
  hist_MC->SetLineColor(2);
  hist_MC->GetXaxis()->SetTitle(xaxislabel);
  hist_MC2->GetXaxis()->SetTitle(xaxislabel);
  hist_MC->GetXaxis()->CenterTitle();
  hist_MC->GetYaxis()->CenterTitle();
  hist_MC->GetYaxis()->SetTitleSize(0.037);
  hist_MC->GetXaxis()->SetTitleSize(0.038);
  hist_MC->SetTitle(histotitle);
  legend->Clear();
  hist_MC->SetLineColor(mnvPlotter.mc_color);
  hist_MC->SetLineWidth(mnvPlotter.mc_line_width);
  hist_MC->SetLineStyle(mnvPlotter.mc_line_style);
  hist_MC->SetFillColor(mnvPlotter.mc_error_color);
  hist_MC->SetFillStyle(mnvPlotter.mc_error_style);
  legend->AddEntry(hist_MC, "MINER#nuA v1-Tune", "fl");
  legend->AddEntry(hist_Data, "Data","lep");

  bool statPlusSys           = true;
  bool useHistTitles         = false;
  int mcScale                = 1.;
  int ndf=0;
  Double_t chi_2 = mnvPlotter.Chi2DataMC(hist_Data, hist_MC,ndf,1.0,false,false );
  ndf = hist_MC->GetNbinsX();

  if(DoBinwidthNorm==true){
    hist_MC->Scale(1,"width");
    hist_Data->Scale(1,"width");
  }


  //mnvPlotter.axis_title_size_y = 0.08;
  mnvPlotter.axis_title_size_y = 0.05;
  mnvPlotter.axis_title_offset_y = 1.2;
  double max;


if(hist_MC->GetMaximum() > hist_Data->GetMaximum()){max = hist_MC->GetMaximum();}
else {max = hist_MC->GetMaximum();}

  mnvPlotter.axis_maximum = max*1.25;


  mnvPlotter.DrawDataMCWithErrorBand(hist_Data, hist_MC, mcScale, "N", useHistTitles, NULL, NULL, false, statPlusSys);

  char chi_label[1024];

  sprintf(chi_label, "#chi^{2}/ndf = %.2f / %i", chi_2, ndf);
  legend -> AddEntry((TObject*)0, chi_label, "");
  legend -> Draw();
  mnvPlotter.WritePreliminary("TL", .03, 0, 0, false);
  char total_title[1024];
  sprintf(total_title, "%s  [%s]", histotitle, Playlist_name);
  mnvPlotter.AddHistoTitle(total_title, .04);
  cE.cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.2);
  pad2->SetGridx(); // vertical grid
  pad2->SetGridy(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  double beforeparameters2 = mnvPlotter.axis_title_offset_y;

  mnvPlotter.axis_title_size_x = 0.08;
  mnvPlotter.axis_title_offset_y = .4;
  mnvPlotter.axis_title_offset_x = 1;
  mnvPlotter.axis_title_size_y = 0.12;
  mnvPlotter.axis_label_size = 0.1;
  hist_MC2->GetXaxis()->SetTitle(xaxislabel);
  hist_Data->GetXaxis()->SetTitle(xaxislabel);
  mnvPlotter.DrawDataMCRatio(hist_Data, hist_MC2 , 1.0, true, false, true , -1, -1, "#frac{Data}{MC}", false);

  TLine ratio_1;
  ratio_1.SetLineWidth(2);
  ratio_1.SetLineStyle(7);
  ratio_1.SetLineColor(kBlue);
  double line_min = hist_Data->GetBinLowEdge(1);
  double line_max = hist_Data->GetBinLowEdge(hist_Data->GetNbinsX()+1);
  ratio_1.DrawLine(line_min,1,line_max,1);

  cE.cd();

  std::string plotname = Form("%s",pdf_label.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");
  mnvPlotter.legend_n_columns = 2;
  mnvPlotter.axis_title_offset_y = beforeparameters2;


 // PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);
 std::string xaxislabel_string(xaxislabel);
 mnvPlotter.axis_title_offset_y = 1.5;
 mnvPlotter.axis_title_offset_x = 1.2;
 mnvPlotter.axis_title_size_x = 0.038;
 mnvPlotter.axis_title_size_y = 0.032;
 mnvPlotter.axis_label_size = 0.03;
 mnvPlotter.axis_maximum = .25;
 mnvPlotter.axis_minimum = 0;
 mnvPlotter.legend_text_size     = .022;
 mnvPlotter.height_nspaces_per_hist = .75;
 mnvPlotter.legend_offset_y = -.02;
 //std::cout<< "off set y axis = "<< mnvPlotter.axis_title_offset_y<< std::endl;
 bool debug = false;
   sprintf(total_title, "[MC] %s", histotitle);
  PlotErrorSummaryNew(hist_MC2, plotname, total_title, xaxislabel_string.c_str(), &cE, &mnvPlotter,debug,drawAllErrorGroups);

  sprintf(total_title, "[DATA] %s", histotitle);
  PlotErrorSummaryNew(hist_Data, plotname, total_title, xaxislabel_string.c_str(), &cE, &mnvPlotter,debug,drawAllErrorGroups);

  mnvPlotter.title_size = .06;
  mnvPlotter.legend_n_columns = 1;
  mnvPlotter.legend_offset_y = 0;
  cE.Closed();

  if(MakeXaxisLOG==true){
    gPad->SetLogx(0);
  }


} // end of Function
/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////
void Draw_DataWITHMC_SingleHistinput_withRatioCrossSection(MnvH1D *hist_MC_input, MnvH1D *hist_Data_input,
  char *Playlist_name, std::string pdf_label, char *histotitle, std::string units,
   char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG , bool drawAllErrorGroups , double MaxYvalue )
{
  MnvH1D * hist_MC = (PlotUtils::MnvH1D*)hist_MC_input->Clone(uniq());
  MnvH1D * hist_MC2 = (PlotUtils::MnvH1D*)hist_MC_input->Clone(uniq());
  MnvH1D * hist_Data = (PlotUtils::MnvH1D*)hist_Data_input->Clone(uniq());
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE("cE","cE", 800, 800);
  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  double x1,x2,y1,y2;
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", .5, 10, .025);
  TLegend *legend = new TLegend(x1 - .02, y1+ .28 , x2 +.075 , y2 + .4 );


  string TotalTitle = string(histotitle);

  SetHist_Data(*hist_MC, xaxislabel , yaxislabel);

  if(MakeXaxisLOG==true){
    gPad->SetLogx();
  }

  SetMaxforDraw(hist_MC,hist_Data);

  legend->SetNColumns(1);
  legend->SetTextSize(.03);
  legend->SetFillColor(0);

  char ytitle[100];
  //int units_n = ;
  char units_char[units.length()+1];
  strcpy( units_char,units.c_str());

  if(DoBinwidthNorm==true){
    double binwidth_title = hist_MC -> GetBinWidth(3);
    sprintf(ytitle, "%s / %.2f [%s]", yaxislabel, binwidth_title, units_char); //
    hist_MC->GetYaxis()->SetTitle(ytitle);
  }
  else{
    sprintf(ytitle, "%s",yaxislabel); //
    hist_MC->GetYaxis()->SetTitle(ytitle);
  }

  //hist_a->SetFillColor(1);
  hist_MC->SetLineWidth(3);
  hist_MC->SetLineColor(2);
  hist_MC->GetXaxis()->SetTitle(xaxislabel);
  hist_MC2->GetXaxis()->SetTitle(xaxislabel);
  hist_MC->GetXaxis()->CenterTitle();
  hist_MC->GetYaxis()->CenterTitle();
  hist_MC->GetYaxis()->SetTitleSize(0.037);
  hist_MC->GetXaxis()->SetTitleSize(0.038);
  hist_MC->SetTitle(histotitle);
  legend->Clear();
  hist_MC->SetLineColor(mnvPlotter.mc_color);
  hist_MC->SetLineWidth(mnvPlotter.mc_line_width);
  hist_MC->SetLineStyle(mnvPlotter.mc_line_style);
  hist_MC->SetFillColor(mnvPlotter.mc_error_color);
  hist_MC->SetFillStyle(mnvPlotter.mc_error_style);
  legend->AddEntry(hist_MC, "MINER#nuA v1-Tune", "fl");
  legend->AddEntry(hist_Data, "Data","lep");

  bool statPlusSys           = true;
  bool useHistTitles         = false;
  int mcScale                = 1.;
  int ndf=0;
  Double_t chi_2 = mnvPlotter.Chi2DataMC(hist_Data, hist_MC,ndf,1.0,false,false );
  ndf = hist_MC->GetNbinsX();

  if(DoBinwidthNorm==true){
    hist_MC->Scale(1,"width");
    hist_Data->Scale(1,"width");
  }


  //mnvPlotter.axis_title_size_y = 0.08;
  mnvPlotter.axis_title_size_y = 0.05;
  mnvPlotter.axis_title_offset_y = 1.2;
  double max;
if(hist_MC->GetMaximum() > hist_Data->GetMaximum()){max = hist_MC->GetMaximum();}
else {max = hist_Data->GetMaximum();}

  mnvPlotter.axis_maximum = MaxYvalue;
  mnvPlotter.DrawDataMCWithErrorBand(hist_Data, hist_MC, mcScale, "N", useHistTitles, NULL, NULL, false, statPlusSys);

  char chi_label[1024];

  sprintf(chi_label, "#chi^{2}/ndf = %.2f / %i", chi_2, ndf);
  legend -> AddEntry((TObject*)0, chi_label, "");
  legend -> Draw();
  mnvPlotter.WritePreliminary("TL", .03, 0, 0, false);
  char total_title[1024];
  sprintf(total_title, "%s  [%s]", histotitle, Playlist_name);
  mnvPlotter.AddHistoTitle(total_title, .04);
  cE.cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.2);
  pad2->SetGridx(); // vertical grid
  pad2->SetGridy(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  double beforeparameters2 = mnvPlotter.axis_title_offset_y;

  mnvPlotter.axis_title_size_x = 0.08;
  mnvPlotter.axis_title_offset_y = .4;
  mnvPlotter.axis_title_offset_x = 1;
  mnvPlotter.axis_title_size_y = 0.12;
  mnvPlotter.axis_label_size = 0.1;
  hist_MC2->GetXaxis()->SetTitle(xaxislabel);
  hist_Data->GetXaxis()->SetTitle(xaxislabel);
  mnvPlotter.DrawDataMCRatio(hist_Data, hist_MC2 , 1.0, true, false, true , -1, -1, "#frac{Data}{MC}", false);

  TLine ratio_1;
  ratio_1.SetLineWidth(2);
  ratio_1.SetLineStyle(7);
  ratio_1.SetLineColor(kBlue);
  double line_min = hist_Data->GetBinLowEdge(1);
  double line_max = hist_Data->GetBinLowEdge(hist_Data->GetNbinsX()+1);
  ratio_1.DrawLine(line_min,1,line_max,1);

  cE.cd();

  std::string plotname = Form("%s",pdf_label.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");
  mnvPlotter.legend_n_columns = 2;
  mnvPlotter.axis_title_offset_y = beforeparameters2;


 // PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);
 std::string xaxislabel_string(xaxislabel);
 mnvPlotter.axis_title_offset_y = 1.5;
 mnvPlotter.axis_title_offset_x = 1.2;
 mnvPlotter.axis_title_size_x = 0.038;
 mnvPlotter.axis_title_size_y = 0.032;
 mnvPlotter.axis_label_size = 0.03;
 mnvPlotter.axis_maximum = .25;
 mnvPlotter.axis_minimum = 0;
 mnvPlotter.legend_text_size     = .022;
 mnvPlotter.height_nspaces_per_hist = .75;
 mnvPlotter.legend_offset_y = -.02;
 //std::cout<< "off set y axis = "<< mnvPlotter.axis_title_offset_y<< std::endl;
 bool debug = false;
   sprintf(total_title, "[MC] %s", histotitle);
  PlotErrorSummaryNew(hist_MC2, plotname, total_title, xaxislabel_string.c_str(), &cE, &mnvPlotter,debug,drawAllErrorGroups);

 mnvPlotter.axis_maximum = .1;

  sprintf(total_title, "[DATA] %s", histotitle);
  PlotErrorSummaryNew(hist_Data, plotname, total_title, xaxislabel_string.c_str(), &cE, &mnvPlotter,debug,drawAllErrorGroups);

  mnvPlotter.title_size = .06;
  mnvPlotter.legend_n_columns = 1;
  mnvPlotter.legend_offset_y = 0;
  cE.Closed();

  if(MakeXaxisLOG==true){
    gPad->SetLogx(0);
  }


} // end of Function
//////////////////////////////////////////////////////////////////////////////////////////////////


void Draw_DataWITHMC_SingleHistinput_withRatioCrossSection(MnvH1D *hist_MC_input, MnvH1D *hist_Data_input,
  TObjArray  *modelHist_input, char *Playlist_name,
  std::string pdf_label, char *histotitle, std::string units,
  char *xaxislabel, char* yaxislabel, bool MakeXaxisLOG  )
{
  std::cout<<"inside: Draw_DataWITHMC_SingleHistinput_withRatioCrossSection"<<std::endl;
  std::cout<<"cloning hist "<< std::endl;
  MnvH1D *hist_MC = (PlotUtils::MnvH1D*)hist_MC_input->Clone(uniq());
  MnvH1D *hist_Data = (PlotUtils::MnvH1D*)hist_Data_input->Clone(uniq());
  TObjArray  *modelHist = (TObjArray*)modelHist_input->Clone();
  TObjArray  *modelHist_tofill;

std::cout<<" Finshed cloning hist "<< std::endl;
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE(uniq(),"cE", 800, 800);
  char chi_label[1024];
// pad1 becomes the current pad
  double x1,x2,y1,y2;
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", .5, 10, .025);
  TLegend *legend = new TLegend(x1 - .02, y1+.31 , x2 +.075 , y2 + .42  );
  TLegend *legendRatio = new TLegend(x1 - .02, y1+.31 , x2 +.075 , y2 + .42  );
  mnvPlotter.legend_n_columns = 1;
  string TotalTitle = string(histotitle);

  if(MakeXaxisLOG==true){
    gPad->SetLogx();
  }

  SetMaxforDraw(hist_MC,hist_Data);

  legend->SetNColumns(1);
  legend->SetTextSize(.03);
  legend->SetFillColor(0);

  char ytitle[100];
  //int units_n = ;
  char units_char[units.length()+1];
  strcpy( units_char,units.c_str());

  double binwidth_title = hist_MC -> GetBinWidth(3);
  sprintf(ytitle, "%s / %.2f %s", yaxislabel, binwidth_title, units_char); //
  hist_MC->GetYaxis()->SetTitle(ytitle);
  hist_Data->GetYaxis()->SetTitle(ytitle);

  //hist_a->SetFillColor(1);
  hist_MC->SetLineWidth(2);
  hist_MC->SetLineColor(2);
  hist_Data->GetXaxis()->SetTitle(xaxislabel);
  hist_Data->GetXaxis()->CenterTitle();
  hist_Data->GetYaxis()->CenterTitle();
  hist_Data->GetYaxis()->SetTitleSize(0.037);
  hist_Data->GetXaxis()->SetTitleSize(0.038);


  legend->AddEntry(hist_Data, "Data","lep");
  int ndf=0;
  std::cout<<" Chi2DataMC "<< std::endl;
  Double_t chi_2_mvnV1 = mnvPlotter.Chi2DataMC(hist_Data, hist_MC,ndf,1.0,false,false );

  hist_MC->Scale(1.0,"width");
  hist_Data->Scale(1.0,"width");

  TH1D*  hist_MC_clond = (TH1D*)hist_MC->Clone(uniq());
  modelHist_tofill->AddFirst(hist_MC);
  sprintf(chi_label, "MINER#nuA v1  #chi^{2}/ndf = %.2f / %i", chi_2_mvnV1, ndf);
  legend->AddEntry(hist_MC_clond, chi_label, "l");

  std::cout<<"inside: Draw_DataWITHMC_SingleHistinput_withRatioCrossSection::first loop "<<std::endl;
  int nVars = modelHist->GetEntries();

  for (int iHist = 0; iHist < nVars; ++iHist) {

    PlotUtils::MnvH1D*  hMC_Model_clone = (PlotUtils::MnvH1D*)modelHist_input->At(iHist)->Clone(uniq());
    TH1D*  hMC_Model_input = (TH1D*)modelHist_input->At(iHist)->Clone(uniq());
    Double_t chi_2_loop  = mnvPlotter.Chi2DataMC(hist_Data, hMC_Model_clone ,ndf,1.0,false,false );
    auto model_title = modelHist_input->At(iHist)->GetTitle();
    hMC_Model_input->SetTitle(model_title);
    sprintf(chi_label, "%s  #chi^{2}/ndf = %.2f / %i",model_title, chi_2_mvnV1, ndf);
    legend->AddEntry(hMC_Model_input, chi_label, "l");
    hMC_Model_input->Scale(1.0,"width");
    modelHist_tofill->Add(hMC_Model_input);
  }

  ndf = hist_MC->GetNbinsX();
  mnvPlotter.draw_normalized_to_bin_width=false;
  //mnvPlotter.axis_title_size_y = 0.08;
  mnvPlotter.axis_title_size_y = 0.045;
  mnvPlotter.axis_title_offset_y = 1.2;
  mnvPlotter.axis_maximum = hist_MC->GetMaximum() *1.15;
  mnvPlotter.DrawDataMCVariations(hist_Data, modelHist_tofill);

  legend -> Draw();
  mnvPlotter.WritePreliminary("TL", .03, 0, 0, false);
  char total_title[1024];
  sprintf(total_title, "%s  [%s]", histotitle, Playlist_name);
  mnvPlotter.AddHistoTitle(total_title, .04);


  std::string plotname = Form("%s",pdf_label.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");

  ///////////////////////////////////////////////////////////////
  ///// Draw Ratio now
  /////////////////////////////////////////////////////////////
  cE.Clear();
  //PlotUtils::MnvH1D*  hMC_nominal_model = (PlotUtils::MnvH1D*)modelHist_input->At(0)->Clone(uniq());
  //hist_Data->Divide(hist_Data,hMC_nominal_model);
  //legendRatio->AddEntry(hist_Data, "Data","lep");

  //for (int iHist = 0; iHist < nVars; ++iHist) {

  //  PlotUtils::MnvH1D*  hMC_Model_clone = (PlotUtils::MnvH1D*)modelHist_input->At(iHist)->Clone(uniq());
  //  auto model_title = modelHist_input->At(iHist)->GetTitle();
  //  hMC_Model_clone->Divide(hMC_Model_clone,hMC_nominal_model,1.0,1.0);
  //  sprintf(chi_label, "%s /  Nominal ",model_title);
  //  legendRatio->AddEntry(hMC_Model_clone, chi_label,"l");
  //  modelHist_ratio->Add(hMC_Model_clone);
  //}

  //hist_Data->GetYaxis()->SetTitle("Ratio Hist / nominal Genie[mvnTune-V1]");
  //mnvPlotter.DrawDataMCVariations(hist_Data,modelHist_ratio);

  //legend -> Draw();
  //mnvPlotter.WritePreliminary("TL", .03, 0, 0, false);
  //sprintf(total_title, "Model Ratio: %s  [%s]", histotitle, Playlist_name);
  //mnvPlotter.AddHistoTitle(total_title, .04);

  //cE.Closed();

  //if(MakeXaxisLOG==true){
  //  gPad->SetLogx(0);
  //}


} // end of Function
/////////////////////////////////////////////////////////////////////////////////////////////////
void Draw_MCInteractions_FractionEvents( MnvH1D *h_elastic,
   MnvH1D * h_2p2h,  MnvH1D *h_deltaRes, MnvH1D *h_heavierRes, MnvH1D *h_DISSIS,
   MnvH1D *h_DISSoft, MnvH1D *h_DIShard,  MnvH1D *h_None,  MnvH1D *h_Other,
    std::string pdf_label, char *histotitle,
   char *xaxislabel, char* yaxislabel){

     PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
     TCanvas cE("cE","cE", 800, 800);


     TObjArray  mcHists_Breakdown;

     MnvH1D *h_elastic_clone = (PlotUtils::MnvH1D*)h_elastic->Clone("h_elastic_clone");
     MnvH1D *h_2p2h_clone = (PlotUtils::MnvH1D*)h_2p2h->Clone("h_2p2h_clone");
     MnvH1D *h_deltaRes_clone = (PlotUtils::MnvH1D*)h_deltaRes->Clone("h_deltaRes_clone");
     MnvH1D *h_heavierRes_clone = (PlotUtils::MnvH1D*)h_heavierRes->Clone("h_heavierRes_clone");
     MnvH1D *h_DISSIS_clone = (PlotUtils::MnvH1D*)h_DISSIS->Clone("h_DISSIS_clone");
     MnvH1D *h_DISSoft_clone = (PlotUtils::MnvH1D*)h_DISSoft->Clone("h_DISSoft_clone");
     MnvH1D *h_DIShard_clone = (PlotUtils::MnvH1D*)h_DIShard->Clone("h_DIShard_clone");
     MnvH1D *h_None_clone = (PlotUtils::MnvH1D*)h_None->Clone("h_None_clone");
     MnvH1D *h_Other_clone = (PlotUtils::MnvH1D*)h_Other->Clone("h_Other_clone");

     mcHists_Breakdown.Add(h_elastic_clone);
     mcHists_Breakdown.Add(h_2p2h_clone);
     mcHists_Breakdown.Add(h_deltaRes_clone);
     mcHists_Breakdown.Add(h_heavierRes_clone);
     mcHists_Breakdown.Add(h_DISSIS_clone);
     mcHists_Breakdown.Add(h_DISSoft_clone);
     mcHists_Breakdown.Add(h_DIShard_clone);
     mcHists_Breakdown.Add(h_None_clone);
     mcHists_Breakdown.Add(h_Other_clone);

     BinNormalizeTOFractionOF_Events_mvnH1D(mcHists_Breakdown);

     for(int i = 0 ; i < mcHists_Breakdown.GetEntries(); i++){

       ((PlotUtils::MnvH1D*)mcHists_Breakdown.At(i))->SetFillStyle(1001);
       //((PlotUtils::MnvH1D*)mcHists_Breakdown.At(i))->SetLineWidth(0);
       ((PlotUtils::MnvH1D*)mcHists_Breakdown.At(i))->SetFillColor(HeliumColors.at(i));


     }

     mnvPlotter.legend_n_columns = 4;
     mnvPlotter.axis_title_size_x = 0.03;
     mnvPlotter.axis_title_offset_y = 1.2;
     mnvPlotter.axis_title_size_y = 0.05;
     mnvPlotter.axis_label_size =  0.028;
     mnvPlotter.axis_title_size_y = 0.025;
     mnvPlotter.axis_draw_grid_x = false;
     mnvPlotter.axis_draw_grid_y = false;
     mnvPlotter.axis_maximum = 1.2;
     PlotUtils::MnvH1D* datahist = new PlotUtils::MnvH1D("adsf", "", nbins, xmin, xmax);
     //PlotUtils::MnvH1D* hmc = new PlotUtils::MnvH1D("adsf", "", nbins, xmin, xmax);
     datahist->GetXaxis()->SetTitle(xaxislabel);
     datahist->GetYaxis()->SetTitle(yaxislabel);
     datahist->SetMaximum(mnvPlotter.axis_maximum);
     std::string xaxislabel_string(xaxislabel);

     mnvPlotter.DrawDataStackedMC(datahist, &mcHists_Breakdown , 1.0, "TR", "", -1, -1, 1001, xaxislabel_string.c_str(), "Fraction of Events", false);
     //mnvPlotter.DrawDataNonStackedMCWithErrorBand(datahist, hmc, mcHists_Breakdown, HeliumColors, useHistTitles, false, false);

     mnvPlotter.AddHistoTitle(histotitle, .028);
     mnvPlotter.WritePreliminary("TL", .02, 0, 0, false);
     //std::string plotname = Form("%s",pdf_label.c_str());
     mnvPlotter.MultiPrint(&cE, pdf_label, "pdf");
     cE.Closed();

   }


   void Draw_MCInteractions_FractionEvents( MnvH1D *h_Total, MnvH1D *h_elastic,
      MnvH1D * h_2p2h,  MnvH1D *h_deltaRes, MnvH1D *h_heavierRes, MnvH1D *h_DISSIS,
      MnvH1D *h_DISSoft, MnvH1D *h_DIShard,  MnvH1D *h_None,  MnvH1D *h_Other,
       std::string pdf_label, char *histotitle,
      char *xaxislabel, char* yaxislabel){

        PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
        TCanvas cE("cE","cE", 800, 800);

        std::vector<int> Helium9_colorScheme = {
          TColor::GetColor("#F1B6DA"),//pink 11
          TColor::GetColor("#DF00FF"), //'psychedelic Purple1
          TColor::GetColor(43,206,72 ), //green 2
          TColor::GetColor("#87CEEB"),//'skyblue' 3
          TColor::GetColor("#0859C6"), //blue 4
          TColor::GetColor("#de5c22"), // organgish,5
          TColor::GetColor("#ffc922"), //'sunset yellow'6
          TColor::GetColor("#25b5af"), // teal
          TColor::GetColor("#FF0800"),//2 candy Apple7
          TColor::GetColor("#800000"),  // Maroon
          TColor::GetColor("#90AD1C"),//8
          TColor::GetColor("#BABABA"), //Gray 9
          TColor::GetColor("#00FFFF"),//'aqua' 10
          TColor::GetColor("#AAF0D1"), // mint green
          TColor::GetColor(kRed),//'Jade' 12
          TColor::GetColor("#FAFAD2"),  // LightGoldenRodYellow 13

          TColor::GetColor("#555555"),  // dark grey 15
          TColor::GetColor(0, 153, 143 ), //turquoise 16
          TColor::GetColor("#654522"), // yellowishbrown, 17
          TColor::GetColor("#8db600"), // yellowgreen, 18
          TColor::GetColor("#D3D3D3"),  //'lightgrey' 19
          TColor::GetColor("#90AD1C"), // 20
          TColor::GetColor("#CCDDAA"), //21
          TColor::GetColor(kMagenta), //22
          TColor::GetColor("#EEFF00") // neonyellow,0
        };
                TObjArray  mcHists_Breakdown;


        MnvH1D *h_Total_clone = (PlotUtils::MnvH1D*)h_Total->Clone("h_elastic_clone");

        MnvH1D *h_elastic_clone = (PlotUtils::MnvH1D*)h_elastic->Clone("h_elastic_clone");
        MnvH1D *h_2p2h_clone = (PlotUtils::MnvH1D*)h_2p2h->Clone("h_2p2h_clone");
        MnvH1D *h_deltaRes_clone = (PlotUtils::MnvH1D*)h_deltaRes->Clone("h_deltaRes_clone");
        MnvH1D *h_heavierRes_clone = (PlotUtils::MnvH1D*)h_heavierRes->Clone("h_heavierRes_clone");
        MnvH1D *h_DISSIS_clone = (PlotUtils::MnvH1D*)h_DISSIS->Clone("h_DISSIS_clone");
        MnvH1D *h_DISSoft_clone = (PlotUtils::MnvH1D*)h_DISSoft->Clone("h_DISSoft_clone");
        MnvH1D *h_DIShard_clone = (PlotUtils::MnvH1D*)h_DIShard->Clone("h_DIShard_clone");
        MnvH1D *h_None_clone = (PlotUtils::MnvH1D*)h_None->Clone("h_None_clone");
        MnvH1D *h_Other_clone = (PlotUtils::MnvH1D*)h_Other->Clone("h_Other_clone");
        h_Other_clone->Add(h_None_clone);

        mcHists_Breakdown.Add(h_Other_clone);
        mcHists_Breakdown.Add(h_deltaRes_clone);
        mcHists_Breakdown.Add(h_heavierRes_clone);
        mcHists_Breakdown.Add(h_DISSIS_clone);
        mcHists_Breakdown.Add(h_DISSoft_clone);
        mcHists_Breakdown.Add(h_DIShard_clone);
        mcHists_Breakdown.Add(h_2p2h_clone);
        mcHists_Breakdown.Add(h_elastic_clone);




      //  mcHists_Breakdown.Add(h_None_clone);


        BinNormalizeTOFractionOF_Events_mvnH1D(mcHists_Breakdown);
        double area = h_Total_clone->Integral(1,h_Total_clone->GetNbinsX());
        h_Total_clone->Scale(1.0/area);
        for(int i = 0 ; i < mcHists_Breakdown.GetEntries(); i++){

          ((PlotUtils::MnvH1D*)mcHists_Breakdown.At(i))->SetFillStyle(1001);
          //((PlotUtils::MnvH1D*)mcHists_Breakdown.At(i))->SetLineWidth(0);
          ((PlotUtils::MnvH1D*)mcHists_Breakdown.At(i))->SetFillColor(Helium9_colorScheme.at(i));


        }




        mnvPlotter.legend_n_columns = 5;
        mnvPlotter.axis_title_size_x = 0.03;
        mnvPlotter.axis_title_offset_y = 1.2;
        mnvPlotter.axis_label_size =  0.028;
        mnvPlotter.axis_title_size_y = 0.045;
        mnvPlotter.axis_draw_grid_x = false;
        mnvPlotter.axis_draw_grid_y = false;
        mnvPlotter.axis_maximum = 1.2;
        mnvPlotter.legend_text_size = .025;
        //std::cout<<"mnvPlotter.legend_text_size = "<< mnvPlotter.legend_text_size<<std::endl;
      //  PlotUtils::MnvH1D* datahist = new PlotUtils::MnvH1D("adsf", "", nbins, xmin, xmax);
      h_Total_clone->SetTitle("Fractional");
        //PlotUtils::MnvH1D* hmc = new PlotUtils::MnvH1D("adsf", "", nbins, xmin, xmax);
        h_Total_clone->GetXaxis()->SetTitle(xaxislabel);
        h_Total_clone->GetYaxis()->SetTitle(yaxislabel);
        h_Total_clone->SetMaximum(mnvPlotter.axis_maximum);
        std::string xaxislabel_string(xaxislabel);
        mnvPlotter.mc_line_width = 0 ;
        mnvPlotter.DrawDataStackedMC(h_Total_clone, &mcHists_Breakdown , 1.0, "TR", "", -1, -1, 1001, xaxislabel_string.c_str(), "Fraction of Events", false);
        //mnvPlotter.DrawDataNonStackedMCWithErrorBand(datahist, hmc, mcHists_Breakdown, HeliumColors, useHistTitles, false, false);

        mnvPlotter.AddHistoTitle(histotitle, .028);
        mnvPlotter.WritePreliminary("TL", .03, -.08, 0.0, false);
        //std::string plotname = Form("%s",pdf_label.c_str());
        mnvPlotter.MultiPrint(&cE, pdf_label, "pdf");
        cE.Closed();

      }


void Draw_DataWITHMC_SingleHistinput_withRatioCrossSection_Interactions(MnvH1D *hist_MC, MnvH1D *hist_Data, MnvH1D *h_elastic,
   MnvH1D * h_2p2h,  MnvH1D *h_1pion, MnvH1D *h_DIS,  MnvH1D *h_None,  MnvH1D *h_Other,
  char *Playlist_name, std::string pdf_label, char *histotitle, std::string units,
   char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG , bool drawAllErrorGroups , double POT_MC, double POT_DATA )
{

  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE("cE","cE", 800, 800);
  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  double x1,x2,y1,y2;
  ///mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", .5, 10, .025);
  //TLegend *legend = new TLegend(x1 - .02, y1+.31 , x2 +.075 , y2 + .42  );
  TObjArray  mcHists_Breakdown;
  mcHists_Breakdown.Add(h_elastic);
  mcHists_Breakdown.Add(h_2p2h);
  h_1pion->SetTitle("Res + Coh Pion");
  mcHists_Breakdown.Add(h_1pion);
  mcHists_Breakdown.Add(h_DIS);
  mcHists_Breakdown.Add(h_None);
  mcHists_Breakdown.Add(h_Other);

  string TotalTitle = string(histotitle);

  SetHist_Data(*hist_MC, xaxislabel , yaxislabel);

  if(MakeXaxisLOG==true){
    gPad->SetLogx();
  }

  SetMaxforDraw(hist_MC,hist_Data);

  //legend->SetNColumns(1);
  //legend->SetTextSize(.03);
  //legend->SetFillColor(0);

  char ytitle[100];
  //int units_n = ;
  char units_char[units.length()+1];
  strcpy( units_char,units.c_str());

  if(DoBinwidthNorm==true){
    double binwidth_title = hist_MC -> GetBinWidth(3);
    sprintf(ytitle, "%s / %.2f %s", yaxislabel, binwidth_title, units_char); //
    hist_MC->GetYaxis()->SetTitle(ytitle);
  }
  else{
    sprintf(ytitle, "%s",yaxislabel); //
    hist_MC->GetYaxis()->SetTitle(ytitle);
  }

  //hist_a->SetFillColor(1);
  hist_MC->SetLineWidth(3);
  hist_MC->SetLineColor(2);
  hist_MC->GetXaxis()->SetTitle(xaxislabel);
  hist_MC->GetXaxis()->CenterTitle();
  hist_MC->GetYaxis()->CenterTitle();
  hist_MC->GetYaxis()->SetTitleSize(0.037);
  hist_MC->GetXaxis()->SetTitleSize(0.038);
  hist_MC->SetTitle("MINER#nuA v1 [Stat]");
  hist_Data->SetTitle("Data [Stat+Sys]");

  bool statPlusSysDATA           = true;
  bool statPlusSysMC           = false;
  bool useHistTitles         = true;
  int mcScale                = 1.;
  int ndf=0;
  Double_t chi_2 = mnvPlotter.Chi2DataMC(hist_Data, hist_MC,ndf,1.0,false,false );
  ndf = hist_MC->GetNbinsX();
  mnvPlotter.draw_normalized_to_bin_width=false;
  //mnvPlotter.axis_title_size_y = 0.08;
  //mnvPlotter.axis_title_size_y = 0.045;
  //mnvPlotter.axis_title_offset_y = 1.6;
  //mnvPlotter.DrawDataMCWithErrorBand(hist_Data, hist_MC, mcScale, "N", useHistTitles, NULL, NULL, false, statPlusSys);
  const TObjArray  *mcHists_Breakdown_input =  &mcHists_Breakdown ;
mnvPlotter.legend_n_columns = 2;
std::vector<int> Helium9_colorScheme = {
  TColor::GetColor("#AAF0D1"), // mint green
  TColor::GetColor("#DF00FF"), //'psychedelic Purple1
  TColor::GetColor(43,206,72 ), //green 2
  TColor::GetColor("#87CEEB"),//'skyblue' 3
  TColor::GetColor("#0859C6"), //blue 4
  TColor::GetColor("#654522"), // yellowishbrown,5
  TColor::GetColor("#ffc922"), //'sunset yellow'6
  TColor::GetColor("#FF0800"),//2 candy Apple7
  TColor::GetColor("#90AD1C"),//8
  TColor::GetColor("#BABABA"), //Gray 9
  TColor::GetColor("#00FFFF"),//'aqua' 10
  TColor::GetColor("#F1B6DA"),//pink 11
  TColor::GetColor(kRed),//'Jade' 12
  TColor::GetColor("#FAFAD2"),  // LightGoldenRodYellow 13
  TColor::GetColor("#800000"),  // Maroon 14
  TColor::GetColor("#555555"),  // dark grey 15
  TColor::GetColor(0, 153, 143 ), //turquoise 16
  TColor::GetColor("#654522"), // yellowishbrown, 17
  TColor::GetColor("#8db600"), // yellowgreen, 18
  TColor::GetColor("#D3D3D3"),  //'lightgrey' 19
  TColor::GetColor("#90AD1C"), // 20
  TColor::GetColor("#CCDDAA"), //21
  TColor::GetColor(kMagenta), //22
  TColor::GetColor("#EEFF00") // neonyellow,0
};
mnvPlotter.axis_maximum = hist_MC->GetMaximum();
mnvPlotter.axis_title_offset_y = .85;
mnvPlotter.DrawDataNonStackedMCWithErrorBand(hist_Data, hist_MC, mcHists_Breakdown_input, Helium9_colorScheme, useHistTitles,statPlusSysDATA, statPlusSysMC);


  char chi_label[1024];

  sprintf(chi_label, "#chi^{2}/ndf = %.2f / %i", chi_2, ndf);
  TLatex* text = new TLatex;
  text->SetNDC();
  text->SetTextColor(kBlue);
  text->SetTextSize(0.03);
  text->DrawLatex(0.2, 0.85, Form("#chi^{2}/ndf = %.2f / %i", chi_2, ndf));
  mnvPlotter.AddPOTNormBox(POT_DATA,POT_MC, 0.25, 0.82);

  mnvPlotter.WritePreliminary("TL", .025, 0, 0, false);
  char total_title[1024];
  sprintf(total_title, "%s  [%s]", histotitle, Playlist_name);
  mnvPlotter.AddHistoTitle(total_title, .04);
  cE.cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.2);
  pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  double beforeparameters1 = mnvPlotter.axis_title_size_x;
  double beforeparameters2 = mnvPlotter.axis_title_offset_y;
  double beforeparameters3 = mnvPlotter.axis_title_size_y;
  double beforeparameters4 = mnvPlotter.axis_label_size;
  double beforeparameters5 = mnvPlotter.axis_maximum;
  double beforeparameters6 = mnvPlotter.axis_minimum;

  mnvPlotter.axis_title_size_x = 0.1;
  mnvPlotter.axis_title_offset_y = .4;
  mnvPlotter.axis_title_size_y = 0.1;
  mnvPlotter.axis_label_size = 0.1;

  mnvPlotter.DrawDataMCRatio(hist_Data, hist_MC, 1.0, false, false , .5, 1.5, "#frac{Data}{MC}", false);
  TLine ratio_1;
  ratio_1.SetLineWidth(2);
  ratio_1.SetLineStyle(7);
  ratio_1.SetLineColor(kBlue);
  double line_min = hist_Data->GetBinLowEdge(1);
  double line_max = hist_Data->GetBinLowEdge(hist_Data->GetNbinsX()+1);
  ratio_1.DrawLine(line_min,1,line_max,1);
  cE.cd();

  mnvPlotter.axis_title_size_x = beforeparameters1;
  mnvPlotter.axis_title_offset_y = beforeparameters2;
  mnvPlotter.axis_title_size_y = beforeparameters3;
  mnvPlotter.axis_label_size = beforeparameters4;
  mnvPlotter.axis_maximum = .25;
  mnvPlotter.axis_minimum = 0;

  std::string plotname = Form("%s",pdf_label.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");
  mnvPlotter.legend_n_columns = 2;
 // PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);
 std::string xaxislabel_string(xaxislabel);
 mnvPlotter.axis_title_size_x = 0.038;
 mnvPlotter.axis_title_size_y = 0.03;
 mnvPlotter.axis_label_size = 0.03;
 std::cout<< "off set y axis = "<< mnvPlotter.axis_title_offset_y<< std::endl;
 bool debug = false;
  PlotErrorSummaryNew(hist_MC, plotname, histotitle, xaxislabel_string.c_str(), &cE, &mnvPlotter,debug,drawAllErrorGroups);

  std::string plotnamedata = Form("[Data] %s",pdf_label.c_str());

  PlotErrorSummaryNew(hist_Data, plotname, histotitle, xaxislabel_string.c_str(), &cE, &mnvPlotter,debug,drawAllErrorGroups);

  mnvPlotter.title_size = .06;
  mnvPlotter.legend_n_columns = 1;

  cE.Closed();

  if(MakeXaxisLOG==true){
    gPad->SetLogx(0);
  }



} // end of Function





void Draw_DataWITHMC_SingleHistinput_withRatioCrossSection_Interactions_DISbreakdown(MnvH1D *hhist_MC, MnvH1D *hhist_Data, MnvH1D *hh_elastic,
   MnvH1D * hh_2p2h,  MnvH1D *hh_deltaRes, MnvH1D *hh_heavierRes, MnvH1D *hh_DISSIS,MnvH1D *hh_DISSoft, MnvH1D *hh_DIShard,
    MnvH1D *hh_None,  MnvH1D *hh_Other, char *Playlist_name, std::string pdf_label, char *histotitle, std::string units,
   char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG , bool drawAllErrorGroups , double POT_MC, double POT_DATA )
{

   MnvH1D *hist_MC = (MnvH1D*)hhist_MC ->Clone("hist_MC");
   MnvH1D *hist_MC2 = (MnvH1D*)hhist_MC ->Clone("hist_MC2");
   MnvH1D *hist_Data = (MnvH1D*)hhist_Data ->Clone("hist_Data");

   MnvH1D *h_elastic = (MnvH1D*)hh_elastic ->Clone("h_elastic");
   MnvH1D *h_2p2h = (MnvH1D*)hh_2p2h ->Clone("h_2p2h");
   MnvH1D *h_deltaRes = (MnvH1D*)hh_deltaRes ->Clone("h_deltaRes");
   MnvH1D *h_heavierRes = (MnvH1D*)hh_heavierRes ->Clone("h_heavierRes");
   MnvH1D *h_DISSIS = (MnvH1D*)hh_DISSIS ->Clone("h_DISSIS");
   MnvH1D *h_DISSoft = (MnvH1D*)hh_DISSoft ->Clone("h_DISSoft");
   MnvH1D *h_DIShard= (MnvH1D*)hh_DIShard->Clone("h_DIShard");
   MnvH1D *h_None = (MnvH1D*)hh_None ->Clone("h_None ");
   MnvH1D *h_Other = (MnvH1D*)hh_Other->Clone("h_Other");

   h_Other->Add(h_None);

   h_elastic->SetLineWidth(0);
   h_2p2h->SetLineWidth(0);
   h_deltaRes->SetLineWidth(0);
   h_heavierRes->SetLineWidth(0);
   h_DISSIS->SetLineWidth(0);
   h_DISSoft->SetLineWidth(0);
   h_DIShard->SetLineWidth(0);
   //h_None->SetLineWidth(0);
   h_Other->SetLineWidth(0);

   if(DoBinwidthNorm==true){
     h_elastic->Scale(1,"width");
     h_2p2h->Scale(1,"width");
     h_deltaRes->Scale(1,"width");
     h_heavierRes->Scale(1,"width");
     h_DISSIS->Scale(1,"width");
     h_DISSoft->Scale(1,"width");
     h_DIShard->Scale(1,"width");
     h_None->Scale(1,"width");
     h_Other->Scale(1,"width");
   }



  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE("cE","cE", 800, 800);
  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  double x1,x2,y1,y2;
  ///mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", .5, 10, .025);
  //TLegend *legend = new TLegend(x1 - .02, y1+.31 , x2 +.075 , y2 + .42  );
  h_deltaRes->SetTitle("#DeltaRes");
  h_heavierRes->SetTitle("HeaverRes");
  h_DISSoft->SetTitle("SoftDIS");
  h_DIShard->SetTitle("HardDIS");
   TObjArray  mcHists_Breakdown;

  //mcHists_Breakdown.Add(h_None);
  mcHists_Breakdown.Add(h_Other);
  mcHists_Breakdown.Add(h_deltaRes);
  mcHists_Breakdown.Add(h_heavierRes);
  mcHists_Breakdown.Add(h_DISSIS);
  mcHists_Breakdown.Add(h_DISSoft);
  mcHists_Breakdown.Add(h_DIShard);
  mcHists_Breakdown.Add(h_2p2h);
  mcHists_Breakdown.Add(h_elastic);

  string TotalTitle = string(histotitle);
  //MnvH1D *hist_MC = (PlotUtils::MnvH1D*)hist_MC_input->GetCVHistoWithStatError().Clone("hist_MC");
  ///Only want Stat error on MC for Cross section

  SetHist_Data(*hist_MC, xaxislabel , yaxislabel);

  if(MakeXaxisLOG==true){
    gPad->SetLogx();
  }

  //SetMaxforDraw(hist_MC,hist_Data);

  //legend->SetNColumns(1);
  //legend->SetTextSize(.03);
  //legend->SetFillColor(0);

  char ytitle[100];
  //int units_n = ;
  char units_char[units.length()+1];
  strcpy( units_char,units.c_str());

  if(DoBinwidthNorm==true){
    double binwidth_title = hist_MC -> GetBinWidth(3);
    sprintf(ytitle, "%s", yaxislabel); //
    hist_MC->GetYaxis()->SetTitle(ytitle);
    hist_Data->GetYaxis()->SetTitle(ytitle);
  }
  else{
    sprintf(ytitle, "%s",yaxislabel); //
    hist_MC->GetYaxis()->SetTitle(ytitle);
    hist_Data->GetYaxis()->SetTitle(ytitle);
  }

  //hist_a->SetFillColor(1);
  hist_MC->SetLineWidth(3);
  hist_MC->SetLineColor(2);
  hist_MC->GetXaxis()->SetTitle(xaxislabel);
  hist_MC->GetXaxis()->CenterTitle();
  hist_MC->GetYaxis()->CenterTitle();
  hist_MC->GetYaxis()->SetTitleSize(0.037);
  hist_MC->GetXaxis()->SetTitleSize(0.038);
  hist_MC->SetTitle("MC v1 [Stat]");
  hist_Data->SetTitle("Data [Stat+Sys]");

  bool statPlusSysDATA       = true;
  bool statPlusSysMC         = false;
  bool useHistTitles         = true;
  int mcScale                = 1.;
  int ndf=0;
  Double_t chi_2 = mnvPlotter.Chi2DataMC(hist_Data, hist_MC,ndf,1.0,false,false );
  ndf = hist_MC->GetNbinsX();

if(DoBinwidthNorm==true){
  hist_Data->Scale(1,"width");
  hist_MC->Scale(1,"width");
  hist_MC2->Scale(1,"width");
}
double max;

if(hist_MC->GetMaximum() > hist_Data->GetMaximum()){
max = hist_MC->GetMaximum();

}
else{//max = hist_Data->GetMaximum();
  max = hist_MC->GetMaximum(); // I want the same max for MC and Data for different plots so making this change
}
  //mnvPlotter.axis_title_size_y = 0.08;
  //mnvPlotter.axis_title_size_y = 0.045;
  //mnvPlotter.axis_title_offset_y = 1.6;
  //mnvPlotter.DrawDataMCWithErrorBand(hist_Data, hist_MC, mcScale, "N", useHistTitles, NULL, NULL, false, statPlusSys);
  const TObjArray  *mcHists_Breakdown_input =  &mcHists_Breakdown ;
mnvPlotter.legend_n_columns = 2;
std::vector<int> Helium9_colorScheme = {
  TColor::GetColor("#F1B6DA"),//pink 11
  TColor::GetColor("#DF00FF"), //'psychedelic Purple1
  TColor::GetColor(43,206,72 ), //green 2
  TColor::GetColor("#87CEEB"),//'skyblue' 3
  TColor::GetColor("#0859C6"), //blue 4
  TColor::GetColor("#de5c22"), // organgish,5
  TColor::GetColor("#ffc922"), //'sunset yellow'6
  TColor::GetColor("#25b5af"), // teal
  TColor::GetColor("#FF0800"),//2 candy Apple7
  TColor::GetColor("#800000"),  // Maroon
  TColor::GetColor("#90AD1C"),//8
  TColor::GetColor("#BABABA"), //Gray 9
  TColor::GetColor("#00FFFF"),//'aqua' 10
  TColor::GetColor("#AAF0D1"), // mint green
  TColor::GetColor(kRed),//'Jade' 12
  TColor::GetColor("#FAFAD2"),  // LightGoldenRodYellow 13

  TColor::GetColor("#555555"),  // dark grey 15
  TColor::GetColor(0, 153, 143 ), //turquoise 16
  TColor::GetColor("#654522"), // yellowishbrown, 17
  TColor::GetColor("#8db600"), // yellowgreen, 18
  TColor::GetColor("#D3D3D3"),  //'lightgrey' 19
  TColor::GetColor("#90AD1C"), // 20
  TColor::GetColor("#CCDDAA"), //21
  TColor::GetColor(kMagenta), //22
  TColor::GetColor("#EEFF00") // neonyellow,0
};


mnvPlotter.axis_maximum = max * 1.38;
hist_MC->SetMaximum(max * 1.38);
mnvPlotter.headroom = 1.38;
mnvPlotter.axis_title_size_y = mnvPlotter.axis_title_size_y*.65;
mnvPlotter.axis_title_offset_y = 1.5;
mnvPlotter.mc_error_style_stack= 3001;
mnvPlotter.mc_error_color_stack = kRed;
mnvPlotter.axis_label_size = mnvPlotter.axis_label_size * .8;
mnvPlotter.draw_normalized_to_bin_width=false;
hist_MC->GetYaxis()->CenterTitle();
mnvPlotter.DrawDataStackedMCWithErrorBand(hist_Data, hist_MC, mcHists_Breakdown_input, Helium9_colorScheme, useHistTitles, statPlusSysDATA, statPlusSysMC);


  char chi_label[1024];

  sprintf(chi_label, "#chi^{2}/ndf = %.2f / %i", chi_2, ndf);
  TLatex* text = new TLatex;
  text->SetNDC();
  text->SetTextColor(kRed);
  text->SetTextSize(0.03);
  text->DrawLatex(0.2, 0.85, Form("#chi^{2}/ndf = %.2f / %i", chi_2, ndf));
  mnvPlotter.AddPOTNormBox(POT_DATA,POT_MC, 0.25, 0.82);

  mnvPlotter.WritePreliminary("TL", .025, 0, 0, false);
  char total_title[1024];
  sprintf(total_title, "%s  [%s]", histotitle, Playlist_name);
  mnvPlotter.AddHistoTitle(total_title, .04);
  cE.cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.3);
  pad2->SetGridx(); // vertical grid
  pad2->SetGridy();
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad

  mnvPlotter.axis_title_size_x = 0.15;
  mnvPlotter.axis_title_offset_y = .4;
  mnvPlotter.axis_title_offset_x = .75;
  mnvPlotter.axis_title_size_y = 0.12;
  mnvPlotter.axis_label_size = 0.1;
   bool     drawSysLine = true;
   bool     dataStatPlusSys = true;
   bool     drawOneLine = true;
   hist_MC2->GetXaxis()->SetTitle(xaxislabel);
  mnvPlotter.DrawDataMCRatio(hist_Data, hist_MC2, 1.0, drawSysLine, dataStatPlusSys, .5, 2.0, "#frac{Data}{MC}", false);

  cE.cd();

  mnvPlotter.axis_title_offset_y = 1.2;
  mnvPlotter.axis_maximum = .25;
  mnvPlotter.axis_minimum = 0;
  mnvPlotter.axis_label_size =  0.028;
  mnvPlotter.axis_title_size_x = 0.04;


  std::string plotname = Form("%s",pdf_label.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");
  mnvPlotter.legend_n_columns = 2;
 std::string xaxislabel_string(xaxislabel);
 //mnvPlotter.axis_title_size_x = 0.038;
 //mnvPlotter.axis_title_size_y = 0.038;
 mnvPlotter.axis_title_offset_y = 1.3;
 mnvPlotter.axis_title_size_y = 0.035;
 mnvPlotter.legend_text_size = mnvPlotter.legend_text_size * .75;
 mnvPlotter.axis_label_size= .02;
 std::cout<< "off set y axis = "<< mnvPlotter.axis_title_offset_y<< std::endl;
 bool debug = false;

  PlotErrorSummaryNew(hist_MC, plotname, total_title, xaxislabel_string.c_str(), &cE, &mnvPlotter,debug,drawAllErrorGroups);
  sprintf(total_title, " [Data] %s", histotitle);
  PlotErrorSummaryNew(hist_Data, plotname, total_title, xaxislabel_string.c_str(), &cE, &mnvPlotter,debug,drawAllErrorGroups);
  MakeModelErrorGroups(mnvPlotter);
  mnvPlotter.axis_label_size= .02;
  mnvPlotter.legend_n_columns = 2;
  mnvPlotter.legend_text_size = mnvPlotter.legend_text_size * .55;
  mnvPlotter.axis_title_offset_y = 1.3;
  mnvPlotter.axis_title_size_y = 0.035;
  mnvPlotter.width_xspace_per_letter = 0.35;
  mnvPlotter.height_nspaces_per_hist = .8;
  mnvPlotter.legend_offset_x = -.02;
  mnvPlotter.legend_offset_y = -.02;
  mnvPlotter.axis_maximum = .3;
  sprintf(total_title, "[Data] %s", xaxislabel);
  PlotErrorSummaryNew(hist_Data, plotname, total_title, xaxislabel_string.c_str(), &cE, &mnvPlotter,debug,true);
  sprintf(total_title, "[TRUE MC] %s ", xaxislabel);
  PlotErrorSummaryNew(hist_MC, plotname, total_title, xaxislabel_string.c_str(), &cE, &mnvPlotter,debug,true);


  mnvPlotter.title_size = .06;
  mnvPlotter.legend_n_columns = 1;

  cE.Closed();

  if(MakeXaxisLOG==true){
    gPad->SetLogx(0);
  }


} // end of Function

//////////////////////////////////////////////////////////////////////////////////////////////
void Draw_DataWITHMC_SingleHistinput(MnvH1D *hist_MC, MnvH1D *hist_Data,
  char *Playlist_name, std::string pdf_label, char *histotitle, std::string units,
   char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG, double POT_data, double POT_MC)
{

  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  double x1,x2,y1,y2;
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", .5, 10, .025);
  TLegend *legend = new TLegend(x1 - .02, y1 + .31 , x2 +.075 , y2 + .42  );


  string TotalTitle = string(histotitle);

  SetHist_Data(*hist_MC, xaxislabel , yaxislabel);

  if(MakeXaxisLOG==true){
    gPad->SetLogx();
  }

  SetMaxforDraw(hist_MC,hist_Data);

  legend->SetNColumns(1);
  legend->SetTextSize(.03);
  legend->SetFillColor(0);

  char ytitle[100];
  //int units_n = ;
  char units_char[units.length()+1];
  strcpy( units_char,units.c_str());

  if(DoBinwidthNorm==true){
    double binwidth_title = hist_MC -> GetBinWidth(3);
    sprintf(ytitle, "%s / %.2f %s", yaxislabel ,binwidth_title, units_char); //
    hist_MC->GetYaxis()->SetTitle(ytitle);
  }
  else{
    sprintf(ytitle, "%s",yaxislabel); //
    hist_MC->GetYaxis()->SetTitle(ytitle);
  }

  //hist_a->SetFillColor(1);
  hist_MC->SetLineWidth(3);
  hist_MC->SetLineColor(2);
  hist_MC->GetXaxis()->SetTitle(xaxislabel);
  hist_MC->GetXaxis()->CenterTitle();
  hist_MC->GetYaxis()->CenterTitle();
  hist_MC->GetYaxis()->SetTitleSize(0.038);
  hist_MC->GetXaxis()->SetTitleSize(0.038);
  hist_MC->SetTitle(histotitle);
  legend->Clear();
  legend->AddEntry(hist_MC, "MINER#nuA v1-Tune", "fl");
  legend->AddEntry(hist_Data, "Data","lep");

  bool statPlusSys           = true;
  bool useHistTitles         = false;
  int mcScale                = 1.;
  int ndf=0;
  Double_t chi_2 = mnvPlotter.Chi2DataMC(hist_Data, hist_MC,ndf,1.0,false,false );
  ndf = hist_MC->GetNbinsX();
  mnvPlotter.draw_normalized_to_bin_width=DoBinwidthNorm;
  mnvPlotter.DrawDataMCWithErrorBand(hist_Data, hist_MC, mcScale, "N", useHistTitles, NULL, NULL, false, statPlusSys);

  char chi_label[1024];

  sprintf(chi_label, "#chi^{2}/ndf = %.2f / %i", chi_2,ndf);
  legend -> AddEntry((TObject*)0, chi_label, "");
  legend -> Draw();
  mnvPlotter.WritePreliminary("TL", .02, 0, 0, false);
  int align;
  double xLabel, yLabel;
  mnvPlotter.DecodePosition( "TC", .03, align, xLabel, yLabel );
  mnvPlotter.AddPOTNormBox(POT_data, POT_MC, xLabel, yLabel); // , const double xLeft, const double yTop
  char total_title[1024];
  sprintf(total_title, "%s  [%s]", histotitle, Playlist_name);
  mnvPlotter.AddHistoTitle(total_title, .04);


  std::string plotname = Form("%s",pdf_label.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");
  mnvPlotter.legend_n_columns = 2;
 // PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);
 std::string xaxislabel_string(xaxislabel);
  PlotErrorSummaryNew(hist_MC, plotname, histotitle, xaxislabel_string.c_str(), &cE, &mnvPlotter,true,false);
  mnvPlotter.legend_n_columns = 1;

  cE.Closed();

  if(MakeXaxisLOG==true){
    gPad->SetLogx(0);
  }


} // end of Function

void Draw_DataWITHMC_SingleHistinput_withRatio(MnvH1D *hist_MC_input, MnvH1D *hist_Data_input,
  char *Playlist_name, std::string pdf_label, char *histotitle, std::string units,
   char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG,
    double POT_data, double POT_MC ,  bool drawAllErrorGroups)
{
  MnvH1D *hist_MC = (MnvH1D *)hist_MC_input->Clone(uniq());
  MnvH1D* hist_Data = (MnvH1D *)hist_Data_input->Clone(uniq());
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE("cE","cE", 800, 800);
  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  double x1,x2,y1,y2;
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", .5, 10, .025);
  TLegend *legend = new TLegend(x1 - .02, y1 + .31 , x2 +.075 , y2 + .42  );


  string TotalTitle = string(histotitle);

  SetHist_Data(*hist_MC, xaxislabel , yaxislabel);

  if(MakeXaxisLOG==true){
    gPad->SetLogx();
  }

  SetMaxforDraw(hist_MC,hist_Data);

  legend->SetNColumns(1);
  legend->SetTextSize(.03);
  legend->SetFillColor(0);

  char ytitle[100];
  char units_char[units.length()+1];
  strcpy( units_char,units.c_str());

  if(DoBinwidthNorm==true){
    double binwidth_title = hist_MC -> GetBinWidth(3);
    sprintf(ytitle, "Number of Events / %.2f %s", binwidth_title, units_char); //
    hist_MC->GetYaxis()->SetTitle(ytitle);
  }
  else{
    sprintf(ytitle, "Number of Events "); //
    hist_MC->GetYaxis()->SetTitle(ytitle);
  }

  //hist_a->SetFillColor(1);
  hist_MC->SetLineWidth(3);
  hist_MC->SetLineColor(2);
  hist_MC->GetXaxis()->SetTitle(xaxislabel);
  hist_MC->GetXaxis()->CenterTitle();
  hist_MC->GetYaxis()->CenterTitle();
  hist_MC->GetYaxis()->SetTitleSize(0.038);
  hist_MC->GetXaxis()->SetTitleSize(0.038);
  hist_MC->SetTitle(histotitle);
  legend->Clear();
  legend->AddEntry(hist_MC, "MINER#nuA v1-Tune", "fl");
  legend->AddEntry(hist_Data, "Data","lep");

  bool statPlusSys           = true;
  bool useHistTitles         = false;
  int mcScale                = 1.;
  int ndf=0;
  Double_t chi_2 = mnvPlotter.Chi2DataMC(hist_Data, hist_MC,ndf,1.0,false,false );
  ndf = hist_MC->GetNbinsX();
  mnvPlotter.draw_normalized_to_bin_width=false;
  if(DoBinwidthNorm==true){
    hist_Data->Scale(1,"width");
    hist_MC->Scale(1,"width");
  }



  mnvPlotter.DrawDataMCWithErrorBand(hist_Data, hist_MC, mcScale, "N", useHistTitles, NULL, NULL, false, statPlusSys);

  char chi_label[1024];

  sprintf(chi_label, "#chi^{2}/ndf = %.2f / %i", chi_2,ndf);
  legend -> AddEntry((TObject*)0, chi_label, "");
  legend -> Draw();
  mnvPlotter.WritePreliminary("TL", .025, 0, 0, false);
  int align;
  double xLabel, yLabel;
  mnvPlotter.DecodePosition( "TC", .03, align, xLabel, yLabel );
  mnvPlotter.AddPOTNormBox(POT_data, POT_MC, xLabel, yLabel); // , const double xLeft, const double yTop
  char total_title[1024];
  sprintf(total_title, "%s  [%s]", histotitle, Playlist_name);
  mnvPlotter.AddHistoTitle(total_title, .04);
  cE.cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.2);
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  mnvPlotter.axis_title_size_x = 0.2;
  mnvPlotter.axis_title_offset_y = .4;
  mnvPlotter.axis_title_offset_x = .4;
  mnvPlotter.axis_title_size_y = 0.1;
  mnvPlotter.axis_label_size = 0.1;
  pad2->SetGridx();
  mnvPlotter.DrawDataMCRatio(hist_Data, hist_MC, 1.0, true, true , -.5, 2, "#frac{Data}{MC}", false);
  cE.cd();
  std::string plotname = Form("%s",pdf_label.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");
  mnvPlotter.legend_n_columns = 2;
  mnvPlotter.axis_title_size_x = 0.038;
  mnvPlotter.axis_title_size_y = 0.038;
  mnvPlotter.axis_label_size = 0.038;
  mnvPlotter.axis_title_offset_y = 1.2;
  mnvPlotter.axis_maximum = .25;
  mnvPlotter.axis_minimum = 0;
 // PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);
 std::string xaxislabel_string(xaxislabel);
  PlotErrorSummaryNew(hist_MC, plotname, histotitle, xaxislabel_string.c_str(), &cE, &mnvPlotter,true,drawAllErrorGroups);
  mnvPlotter.legend_n_columns = 1;

  cE.Closed();

  if(MakeXaxisLOG==true){
    gPad->SetLogx(0);
  }


} // end of Function






/////////////////////////////////////////////////////////////////////////////////
void Draw_Data_RECO_TRUTH_Hist_fromTFile( char *histoName_TRUTH,
  TFile *inputFile_MCinputFULL, TFile *inputFile_MCinputEmpty, char *histoName_MC,
  TFile *inputFile_DatainputFULL, TFile *inputFile_DatainputEmpty,char *histoName_data,
  char *Playlist_name_FULL, char *Playlist_name_EMPTY, std::string pdf_label, char *histotitle,
   char *xaxislabel,char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG, Pot_MapStatusList POT_DATA, Pot_MapStatusList POT_MC )
{
  double scale_to_FULL= POT_DATA[kFULL] / POT_DATA[kEMPTY];

  double MC_scale_to_FULL = POT_DATA[kFULL] / POT_MC[kFULL];

  double MC_EMPTYscale_to_FULL = POT_DATA[kFULL] / POT_MC[kEMPTY];


  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  std::cout<<"trying to draw 1D, HisName  = "<<histoName_data<<std::endl;
  //Getting DATA
  MnvH1D *hist_FULL = (MnvH1D*)inputFile_DatainputFULL -> Get(histoName_data);
  std::cout<<"Finished Full  = "<<histoName_data<<std::endl;

  MnvH1D *hist_EMPTY = (MnvH1D*)inputFile_DatainputEmpty -> Get(histoName_data);
  std::cout<<"Finished Full  = "<<histoName_data<<std::endl;

  auto hist_FULL_EMPTY = (PlotUtils::MnvH1D*)hist_FULL->Clone("hist_FULL");
  auto hist_COPYEMPTY = (PlotUtils::MnvH1D*)hist_EMPTY->Clone("hist_EMPTY");
  std::cout<<"Made Clones "<<histoName_data<<std::endl;
  //SCALING DATA
  hist_EMPTY->Scale(scale_to_FULL);
  hist_COPYEMPTY->Scale(scale_to_FULL);
  hist_FULL_EMPTY->Add(hist_COPYEMPTY,-1);
  // GETTING RECO
  MnvH1D *histMC_FULL = (MnvH1D*)inputFile_MCinputFULL->Get(histoName_MC);
  std::cout<<"Got Hist Full MC   = "<<histoName_MC<<std::endl;
  MnvH1D *histMC_EMPTY = (MnvH1D*)inputFile_MCinputEmpty->Get(histoName_MC);
    std::cout<<"Got Hist EMPTY MC   = "<<histoName_MC<<std::endl;
  auto histMC_FULL_EMPTY = (PlotUtils::MnvH1D*)histMC_FULL->Clone("histMC_FULL");
  auto histMC_COPYEMPTY = (PlotUtils::MnvH1D*)histMC_EMPTY->Clone("histMC_EMPTY");

  // SCALING RECO
  histMC_FULL->Scale(MC_scale_to_FULL);
  histMC_FULL_EMPTY->Scale(MC_scale_to_FULL);
  histMC_EMPTY->Scale(MC_EMPTYscale_to_FULL);
  histMC_COPYEMPTY->Scale(MC_EMPTYscale_to_FULL);
  histMC_FULL_EMPTY->Add(histMC_COPYEMPTY,-1);
  //

  // TRUTH
  MnvH1D *histTRUTH_FULL = (MnvH1D*)inputFile_MCinputFULL->Get(histoName_TRUTH);
  std::cout<<"Got Hist FULL TRUTH MC   = "<<histoName_TRUTH<<std::endl;
  MnvH1D *histTRUTH_EMPTY = (MnvH1D*)inputFile_MCinputEmpty->Get(histoName_TRUTH);
    std::cout<<"Got Hist EMPTY  TRUTH MC   = "<<histoName_TRUTH<<std::endl;
  auto histTRUTH_FULL_EMPTY = (PlotUtils::MnvH1D*)histTRUTH_FULL->Clone("histTRUTH_FULL");
  auto histTRUTH_COPYEMPTY = (PlotUtils::MnvH1D*)histTRUTH_EMPTY->Clone("histTRUTH_EMPTY");
  // SCALLING TRUTH
  std::cout<<"Cloned TRUTH MC Hist for FUll - Empty    = "<<histoName_TRUTH<<std::endl;


  histTRUTH_FULL->Scale(MC_scale_to_FULL);
  histTRUTH_FULL_EMPTY->Scale(MC_scale_to_FULL);
  histTRUTH_EMPTY->Scale(MC_EMPTYscale_to_FULL);
  histTRUTH_COPYEMPTY->Scale(MC_EMPTYscale_to_FULL);
  histTRUTH_FULL_EMPTY->Add(histTRUTH_COPYEMPTY,-1);

  std::cout<<"Scaled TRUTH MC Hist for FUll - Empty    = "<<histoName_TRUTH<<std::endl;

  string TotalTitle = string(histotitle);

  SetHist_Data(*hist_FULL, xaxislabel , yaxislabel);
  SetHist_Data(*hist_EMPTY, xaxislabel , yaxislabel);
  SetHist_Data(*hist_FULL_EMPTY, xaxislabel , yaxislabel);


  if(DoBinwidthNorm==true){
    hist_FULL->Scale(1.0,"width");
    histMC_FULL->Scale(1.0,"width");
    histTRUTH_FULL->Scale(1.0,"width");
    hist_EMPTY->Scale(1.0,"width");
    histMC_EMPTY->Scale(1.0,"width");
    histTRUTH_EMPTY->Scale(1.0,"width");
    hist_FULL_EMPTY->Scale(1.0,"width");
    histMC_FULL_EMPTY->Scale(1.0,"width");
    histTRUTH_FULL_EMPTY->Scale(1.0,"width");
  }

  if(MakeXaxisLOG==true){
    gPad->SetLogx();
  }

  SetMaxforDraw(hist_FULL,histMC_FULL,histTRUTH_FULL);
  SetMaxforDraw(hist_EMPTY,histMC_EMPTY,histTRUTH_EMPTY);
  SetMaxforDraw(hist_FULL_EMPTY, histMC_FULL_EMPTY,histTRUTH_FULL_EMPTY);

  double x1, x2, y1, y2;
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", 6.5, 6., .025);
  TLegend *legend1 = new TLegend(x1 - .015, y1 + .32, x2 + .075, y2 + .3);

  hist_FULL->SetMarkerColor(kBlack);
  hist_FULL->Draw("PEC");
  histMC_FULL->SetLineColor(kRed);
  histMC_FULL->Draw("Hist same");
  histTRUTH_FULL->SetLineColor(kGreen);
  histTRUTH_FULL->Draw("Hist same");
  legend1->AddEntry(hist_FULL, "DATA", "P");
  legend1->AddEntry(histMC_FULL, "RECO MC", "l");
  legend1->AddEntry(histTRUTH_FULL, "TRUTH MC", "l");
  legend1->Draw("Same");
  char total_title[1024];
  sprintf(total_title, "%s [FULL][%s]", histotitle, Playlist_name_FULL);
  mnvPlotter.AddHistoTitle(total_title, .04);
  mnvPlotter.WritePreliminary("TL", .035, 0, 0, false);
  std::string plotname = Form("%s",pdf_label.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");


  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", 6.5, 6., .025);
  TLegend *legend2 = new TLegend(x1 - .015, y1 + .31, x2 + .075, y2 + .3);

  hist_EMPTY->SetMarkerColor(kBlack);
  hist_EMPTY->Draw("PEC");
  histMC_EMPTY->SetLineColor(kRed);
  histMC_EMPTY->Draw("Hist same");
  histTRUTH_EMPTY->SetLineColor(kGreen);
  histTRUTH_EMPTY->Draw("Hist same");
  legend2->AddEntry(hist_EMPTY, "DATA", "P");
  legend2->AddEntry(histMC_EMPTY, "RECO MC", "l");
  legend2->AddEntry(histTRUTH_EMPTY, "TRUTH MC", "l");
  legend2->Draw("Same");
  sprintf(total_title, "%s [Empty][%s]", histotitle, Playlist_name_EMPTY);
  mnvPlotter.AddHistoTitle(total_title, .04);
  mnvPlotter.WritePreliminary("TL", .035, 0, 0, false);
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");


  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", 6.5, 6., .025);
  TLegend *legend3 = new TLegend(x1 - .015, y1 + .32, x2 + .075, y2 + .3);

  hist_FULL_EMPTY->SetMarkerColor(kBlack);
  hist_FULL_EMPTY->Draw("PEC");
  histMC_FULL_EMPTY->SetLineColor(kRed);
  histMC_FULL_EMPTY->Draw("Hist same");
  histTRUTH_FULL_EMPTY->SetLineColor(kGreen);
  histTRUTH_FULL_EMPTY->Draw("Hist same");
  legend3->AddEntry(hist_FULL_EMPTY, "DATA", "P");
  legend3->AddEntry(histMC_FULL_EMPTY, "RECO MC", "l");
  legend3->AddEntry(histTRUTH_FULL_EMPTY, "TRUTH MC", "l");
  legend3->Draw("Same");
  sprintf(total_title, "%s [F-E][%s-%s]", histotitle, Playlist_name_FULL,Playlist_name_EMPTY);
  mnvPlotter.AddHistoTitle(total_title, .04);
  mnvPlotter.WritePreliminary("TL", .035, 0, 0, false);
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");
  cE.Closed();

  if(MakeXaxisLOG==true){
    gPad->SetLogx(0);
  }




}//END of Function
///////////////////////////////////////////////////////////
void Draw_Data_RECO_TRUTH_Hist_fromTFile_withConvolution( char *histoName_TRUTH,char *histoName_TRUTHConvolution,
  TFile *inputFile_MCinputFULL, TFile *inputFile_MCinputEmpty, char *histoName_MC,
  TFile *inputFile_DatainputFULL, TFile *inputFile_DatainputEmpty,char *histoName_data,
  char *Playlist_name_FULL, char *Playlist_name_EMPTY, std::string pdf_label, char *histotitle,
   char *xaxislabel,char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG, Pot_MapStatusList POT_DATA, Pot_MapStatusList POT_MC )
{
  double scale_to_FULL= POT_DATA[kFULL] / POT_DATA[kEMPTY];

  double MC_scale_to_FULL = POT_DATA[kFULL] / POT_MC[kFULL];

  double MC_EMPTYscale_to_FULL = POT_DATA[kFULL] / POT_MC[kEMPTY];


  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  std::cout<<"trying to draw 1D, HisName  = "<<histoName_data<<std::endl;
  //Getting DATA
  MnvH1D *hist_FULL = (MnvH1D*)inputFile_DatainputFULL -> Get(histoName_data);
  std::cout<<"Finished Full  = "<<histoName_data<<std::endl;

  MnvH1D *hist_EMPTY = (MnvH1D*)inputFile_DatainputEmpty -> Get(histoName_data);
  std::cout<<"Finished Full  = "<<histoName_data<<std::endl;

  auto hist_FULL_EMPTY = (PlotUtils::MnvH1D*)hist_FULL->Clone("hist_FULL");
  auto hist_COPYEMPTY = (PlotUtils::MnvH1D*)hist_EMPTY->Clone("hist_EMPTY");
  std::cout<<"Made Clones "<<histoName_data<<std::endl;
  //SCALING DATA
  hist_EMPTY->Scale(scale_to_FULL);
  hist_COPYEMPTY->Scale(scale_to_FULL);
  hist_FULL_EMPTY->Add(hist_COPYEMPTY,-1);
  // GETTING RECO
  MnvH1D *histMC_FULL = (MnvH1D*)inputFile_MCinputFULL->Get(histoName_MC);
  std::cout<<"Got Hist Full MC   = "<<histoName_MC<<std::endl;
  MnvH1D *histMC_EMPTY = (MnvH1D*)inputFile_MCinputEmpty->Get(histoName_MC);
    std::cout<<"Got Hist EMPTY MC   = "<<histoName_MC<<std::endl;
  auto histMC_FULL_EMPTY = (PlotUtils::MnvH1D*)histMC_FULL->Clone("histMC_FULL");
  auto histMC_COPYEMPTY = (PlotUtils::MnvH1D*)histMC_EMPTY->Clone("histMC_EMPTY");

  // SCALING RECO
  histMC_FULL->Scale(MC_scale_to_FULL);
  histMC_FULL_EMPTY->Scale(MC_scale_to_FULL);
  histMC_EMPTY->Scale(MC_EMPTYscale_to_FULL);
  histMC_COPYEMPTY->Scale(MC_EMPTYscale_to_FULL);
  histMC_FULL_EMPTY->Add(histMC_COPYEMPTY,-1);
  //

  // TRUTH
  MnvH1D *histTRUTH_FULL = (MnvH1D*)inputFile_MCinputFULL->Get(histoName_TRUTH);
  std::cout<<"Got Hist FULL TRUTH MC   = "<<histoName_TRUTH<<std::endl;
  MnvH1D *histTRUTH_EMPTY = (MnvH1D*)inputFile_MCinputEmpty->Get(histoName_TRUTH);
    std::cout<<"Got Hist EMPTY  TRUTH MC   = "<<histoName_TRUTH<<std::endl;
  auto histTRUTH_FULL_EMPTY = (PlotUtils::MnvH1D*)histTRUTH_FULL->Clone("histTRUTH_FULL");
  auto histTRUTH_COPYEMPTY = (PlotUtils::MnvH1D*)histTRUTH_EMPTY->Clone("histTRUTH_EMPTY");
  // SCALLING TRUTH
  std::cout<<"Cloned TRUTH MC Hist for FUll - Empty    = "<<histoName_TRUTH<<std::endl;
  //////
  MnvH1D *histTRUTH_FULL_Convolution = (MnvH1D*)inputFile_MCinputFULL->Get(histoName_TRUTHConvolution);
  std::cout<<"Got Hist FULL TRUTH MC   = "<<histoName_TRUTHConvolution<<std::endl;
  MnvH1D *histTRUTH_EMPTY_Convolution = (MnvH1D*)inputFile_MCinputEmpty->Get(histoName_TRUTHConvolution);
    std::cout<<"Got Hist EMPTY  TRUTH MC   = "<<histoName_TRUTHConvolution<<std::endl;
  auto histTRUTH_FULL_EMPTY_Convolution = (PlotUtils::MnvH1D*)histTRUTH_FULL_Convolution->Clone("histTRUTH_FULL_Convolution");
  auto histTRUTH_COPYEMPTY_Convolution = (PlotUtils::MnvH1D*)histTRUTH_EMPTY_Convolution->Clone("histTRUTH_EMPTY_Convolution");

  histTRUTH_FULL->Scale(MC_scale_to_FULL);
  histTRUTH_FULL_EMPTY->Scale(MC_scale_to_FULL);
  histTRUTH_EMPTY->Scale(MC_EMPTYscale_to_FULL);
  histTRUTH_COPYEMPTY->Scale(MC_EMPTYscale_to_FULL);
  histTRUTH_FULL_EMPTY->Add(histTRUTH_COPYEMPTY,-1);

  histTRUTH_FULL_Convolution->Scale(MC_scale_to_FULL);
  histTRUTH_FULL_EMPTY_Convolution->Scale(MC_scale_to_FULL);

  histTRUTH_EMPTY_Convolution->Scale(MC_EMPTYscale_to_FULL);
  histTRUTH_COPYEMPTY_Convolution->Scale(MC_EMPTYscale_to_FULL);
  histTRUTH_FULL_EMPTY_Convolution->Add(histTRUTH_COPYEMPTY_Convolution,-1);



  std::cout<<"Scaled TRUTH MC Hist for FUll - Empty    = "<<histoName_TRUTH<<std::endl;

  string TotalTitle = string(histotitle);

  SetHist_Data(*hist_FULL, xaxislabel , yaxislabel);
  SetHist_Data(*hist_EMPTY, xaxislabel , yaxislabel);
  SetHist_Data(*hist_FULL_EMPTY, xaxislabel , yaxislabel);


  if(DoBinwidthNorm==true){
    hist_FULL->Scale(1.0,"width");
    histMC_FULL->Scale(1.0,"width");
    histTRUTH_FULL->Scale(1.0,"width");
    histTRUTH_FULL_Convolution->Scale(1.0,"width");
    hist_EMPTY->Scale(1.0,"width");
    histMC_EMPTY->Scale(1.0,"width");
    histTRUTH_EMPTY->Scale(1.0,"width");
    histTRUTH_EMPTY_Convolution->Scale(1.0,"width");
    hist_FULL_EMPTY->Scale(1.0,"width");
    histMC_FULL_EMPTY->Scale(1.0,"width");
    histTRUTH_FULL_EMPTY->Scale(1.0,"width");
    histTRUTH_FULL_EMPTY_Convolution->Scale(1.0,"width");
  }

  if(MakeXaxisLOG==true){
    gPad->SetLogx();
  }

  SetMaxforDraw(hist_FULL,histMC_FULL,histTRUTH_FULL);
  SetMaxforDraw(hist_EMPTY,histMC_EMPTY,histTRUTH_EMPTY);
  SetMaxforDraw(hist_FULL_EMPTY, histMC_FULL_EMPTY,histTRUTH_FULL_EMPTY);

  double x1, x2, y1, y2;
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", 6.5, 6., .025);
  TLegend *legend1 = new TLegend(x1 - .015, y1 + .36, x2 + .075, y2 + .34);
  char chi_label[1024];

  hist_FULL->SetMarkerColor(kBlack);
  hist_FULL->Draw("PEC");
  histMC_FULL->SetLineColor(kRed);
  histMC_FULL->Draw("Hist same");
  histTRUTH_FULL->SetLineColor(kGreen);
  histTRUTH_FULL->Draw("Hist same");
  histTRUTH_FULL_Convolution->SetLineColor(kBlue);
  histTRUTH_FULL_Convolution->Draw("Hist same");
  int ndf_full=0;
  int ndf_full_data =0;
  int ndf_full_reco_data =0;
  double chi_full =  mnvPlotter.Chi2MCMC(histMC_FULL, histTRUTH_FULL_Convolution, ndf_full);
  double chi_full_data =  mnvPlotter.Chi2DataMC(hist_FULL, histTRUTH_FULL_Convolution, ndf_full_data);
  double chi_full_reco_data =  mnvPlotter.Chi2DataMC(hist_FULL, histMC_FULL, ndf_full_reco_data);
  legend1->AddEntry(hist_FULL, "DATA", "P");
  legend1->AddEntry(histMC_FULL, "RECO MC", "l");
  legend1->AddEntry(histTRUTH_FULL, "TRUTH MC", "l");
  legend1->AddEntry(histTRUTH_FULL_Convolution, "Convoluted TRUTH MC", "l");
  sprintf(chi_label, "Reco to Conv" );
  legend1 -> AddEntry((TObject*)0, chi_label, "");
  sprintf(chi_label, "#chi^{2}/ndf = %.2f / %i = %.2f", chi_full, ndf_full, chi_full / ndf_full);
  legend1 -> AddEntry((TObject*)0, chi_label, "");
  sprintf(chi_label, "Data to Conv");
  legend1 -> AddEntry((TObject*)0, chi_label, "");
  sprintf(chi_label, "#chi^{2}/ndf = %.2f / %i = %.2f ", chi_full_data, ndf_full_data, chi_full_data / ndf_full_data );
  legend1 -> AddEntry((TObject*)0, chi_label, "");
  sprintf(chi_label, "Data to Reco");
  legend1 -> AddEntry((TObject*)0, chi_label, "");
  sprintf(chi_label, "#chi^{2}/ndf = %.2f / %i = %.2f ", chi_full_reco_data, ndf_full_reco_data, chi_full_reco_data / ndf_full_reco_data );
  legend1 -> AddEntry((TObject*)0, chi_label, "");
  legend1->Draw("Same");

  char total_title[1024];
  sprintf(total_title, "%s [FULL][%s]", histotitle, Playlist_name_FULL);
  mnvPlotter.AddHistoTitle(total_title, .04);
  mnvPlotter.WritePreliminary("TL", .035, 0, 0, false);
  std::string plotname = Form("%s",pdf_label.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");


  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", 6.5, 6., .025);
  TLegend *legend2 = new TLegend(x1 - .015, y1 + .36, x2 + .075, y2 + .34);

  hist_EMPTY->SetMarkerColor(kBlack);
  hist_EMPTY->Draw("PEC");
  histMC_EMPTY->SetLineColor(kRed);
  histMC_EMPTY->Draw("Hist same");
  histTRUTH_EMPTY->SetLineColor(kGreen);
  histTRUTH_EMPTY->Draw("Hist same");
  histTRUTH_EMPTY_Convolution->SetLineColor(kBlue);

  int ndf_empty = 0;
  int ndf_empty_data = 0;
  int ndf_empty_reco_data = 0;
  double chi_empty =  mnvPlotter.Chi2MCMC(histMC_EMPTY, histTRUTH_EMPTY_Convolution, ndf_empty);
  double chi_empty_data =  mnvPlotter.Chi2DataMC(hist_EMPTY, histTRUTH_EMPTY_Convolution, ndf_empty_data);
  double chi_empty_reco_data =  mnvPlotter.Chi2DataMC(hist_EMPTY, histMC_EMPTY, ndf_empty_reco_data);


  histTRUTH_EMPTY_Convolution->Draw("Hist same");
  legend2->AddEntry(hist_EMPTY, "DATA", "P");
  legend2->AddEntry(histMC_EMPTY, "RECO MC", "l");
  legend2->AddEntry(histTRUTH_EMPTY, "TRUTH MC", "l");
  legend2->AddEntry(histTRUTH_EMPTY_Convolution, "Convoluted TRUTH MC", "l");
  sprintf(chi_label, "Reco to Conv" );
  legend2 -> AddEntry((TObject*)0, chi_label, "");
  sprintf(chi_label, "#chi^{2}/ndf = %.2f / %i = %.2f", chi_empty, ndf_empty, chi_empty / ndf_empty);
  legend2 -> AddEntry((TObject*)0, chi_label, "");
  sprintf(chi_label, "Data to Conv");
  legend2 -> AddEntry((TObject*)0, chi_label, "");
  sprintf(chi_label, "#chi^{2}/ndf = %.2f / %i = %.2f", chi_empty_data, ndf_empty_data, chi_empty_data / ndf_empty_data);
  legend2 -> AddEntry((TObject*)0, chi_label, "");
  sprintf(chi_label, "Data to Reco");
  legend2 -> AddEntry((TObject*)0, chi_label, "");
  sprintf(chi_label, "#chi^{2}/ndf = %.2f / %i = %.2f ", chi_empty_reco_data, ndf_empty_reco_data, chi_empty_reco_data / ndf_empty_reco_data );
  legend2 -> AddEntry((TObject*)0, chi_label, "");



  legend2->Draw("Same");
  sprintf(total_title, "%s [Empty][%s]", histotitle, Playlist_name_EMPTY);
  mnvPlotter.AddHistoTitle(total_title, .04);
  mnvPlotter.WritePreliminary("TL", .035, 0, 0, false);
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");


  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", 6.5, 6., .025);
  TLegend *legend3 = new TLegend(x1 - .015, y1 + .36, x2 + .075, y2 + .34);

  hist_FULL_EMPTY->SetMarkerColor(kBlack);
  hist_FULL_EMPTY->Draw("PEC");
  histMC_FULL_EMPTY->SetLineColor(kRed);
  histMC_FULL_EMPTY->Draw("Hist same");
  histTRUTH_FULL_EMPTY->SetLineColor(kGreen);
  histTRUTH_FULL_EMPTY->Draw("Hist same");
  histTRUTH_FULL_EMPTY_Convolution->SetLineColor(kBlue);
  //histTRUTH_FULL_EMPTY_Convolution->SetLineStyle(9);
  int ndf_full_empty = 0;
  int ndf_full_empty_data = 0;
  int ndf_full_empty_reco_data = 0;
  double chi_full_empty =  mnvPlotter.Chi2MCMC(histMC_FULL_EMPTY, histTRUTH_FULL_EMPTY_Convolution, ndf_full_empty);
  double chi_full_empty_data =  mnvPlotter.Chi2DataMC(hist_FULL_EMPTY, histTRUTH_FULL_EMPTY_Convolution, ndf_full_empty_data);
  double chi_full_empty_reco_data =  mnvPlotter.Chi2DataMC(hist_FULL_EMPTY, histMC_FULL_EMPTY, ndf_full_empty_reco_data);


  histTRUTH_FULL_EMPTY_Convolution->Draw("Hist same");
  legend3->AddEntry(hist_FULL_EMPTY, "DATA", "P");
  legend3->AddEntry(histMC_FULL_EMPTY, "RECO MC", "l");
  legend3->AddEntry(histTRUTH_FULL_EMPTY, "TRUTH MC", "l");
  legend3->AddEntry(histTRUTH_FULL_EMPTY_Convolution, "Convoluted TRUTH MC", "l");
  sprintf(chi_label, "Reco to Conv");
  legend3 -> AddEntry((TObject*)0, chi_label, "");
  sprintf(chi_label, "#chi^{2}/ndf = %.2f / %i = %.2f", chi_full_empty, ndf_full_empty, chi_full_empty/ ndf_full_empty);
  legend3 -> AddEntry((TObject*)0, chi_label, "");
  legend3->Draw("Same");
  sprintf(chi_label, "Data to Conv");
  legend3 -> AddEntry((TObject*)0, chi_label, "");
  sprintf(chi_label, "#chi^{2}/ndf = %.2f / %i = %.2f", chi_full_empty_data, ndf_full_empty_data, chi_full_empty_data / ndf_full_empty_data);
  legend3 -> AddEntry((TObject*)0, chi_label, "");
  sprintf(chi_label, "Data to Reco");
  legend3 -> AddEntry((TObject*)0, chi_label, "");
  sprintf(chi_label, "#chi^{2}/ndf = %.2f / %i = %.2f ", chi_full_empty_reco_data, ndf_full_empty_reco_data, chi_full_empty_reco_data / ndf_full_empty_reco_data);
  legend3 -> AddEntry((TObject*)0, chi_label, "");



  sprintf(total_title, "%s [F-E][%s-%s]", histotitle, Playlist_name_FULL,Playlist_name_EMPTY);
  mnvPlotter.AddHistoTitle(total_title, .04);
  mnvPlotter.WritePreliminary("TL", .035, 0, 0, false);
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");
  cE.Closed();

  if(MakeXaxisLOG==true){
    gPad->SetLogx(0);
  }
}//END of Function
///////////////////////////////////////////////////////////////////////////////
void Draw_Data_RECO_TRUTH_Hist_withConvolution_fromPointers(MnvH1D *hist_Data,
   MnvH1D *hist_RECOMC, MnvH1D *hist_TRUTH_Convolution, MnvH1D *hist_TRUTH,
  char *Playlist_name, std::string pdf_label, char *histotitle,char* playlist_status,
   char *xaxislabel,char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG, double Ymax, double Convoluted_Mean, double Convoluted_stddev ,
   double &ChiSqrt_Truth_toRECO,
   double &ChiSqrt_Truth_toData,
   double &ChiSqrt_Reco_toData

    )
{
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  mnvPlotter.axis_title_size_x = 0.09;
  mnvPlotter.axis_title_size_y = 0.09;
  mnvPlotter.axis_label_size = 0.1;

  TCanvas cE ("c1","c1");
  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad

  auto h_Data = (PlotUtils::MnvH1D*)hist_Data->Clone("hist_Data");
  auto h_RECO = (PlotUtils::MnvH1D*)hist_RECOMC->Clone("hist_RECOMC");
  auto h_TRUTH = (PlotUtils::MnvH1D*)hist_TRUTH->Clone("hist_TRUTH");
  auto h_TRUTH_Convol = (PlotUtils::MnvH1D*)hist_TRUTH_Convolution->Clone("hist_TRUTH_Convolution");

  string TotalTitle = string(histotitle);



char ytitle[100];

  if(DoBinwidthNorm==true){
    h_Data->Scale(1.0,"width");
    h_RECO->Scale(1.0,"width");
    h_TRUTH->Scale(1.0,"width");
    h_TRUTH_Convol->Scale(1.0,"width");

    Ymax = 1.45 *  maximum(h_Data->GetMaximum(),h_RECO->GetMaximum(),h_TRUTH->GetMaximum());
    double binwidth_title = hist_Data->GetBinWidth(5);
    sprintf(ytitle, "Number of Events / [%.2f %s] ", binwidth_title , yaxislabel);
  }
  else{
    sprintf(ytitle, "Number of Events");

  }

  if(MakeXaxisLOG==true){
    gPad->SetLogx();
  }
  SetHist_Data(*h_Data, xaxislabel , ytitle);
  SetHist_Data(*hist_Data, xaxislabel , ytitle);
  auto Data_Clone_1 = (PlotUtils::MnvH1D*)hist_Data->Clone("Data_Clone_1");
  auto Data_Clone_2 = (PlotUtils::MnvH1D*)hist_Data->Clone("Data_Clone_2");


  double x1, x2, y1, y2;
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", 6.5, 6., .025);
  TLegend *legend1 = new TLegend(x1 - .02, y1 + .15, x2 + .075, y2 + .3); // .2,.34
  char chi_label[1024];
  h_Data->SetMaximum(Ymax);
  h_Data->SetMarkerColor(kBlack);
  h_RECO->SetLineColor(49);
  h_RECO->SetLineWidth(3);
  h_TRUTH->SetLineColor(kGreen);
  h_TRUTH->SetLineWidth(3);
  //h_TRUTH_Convol->SetLineColor(kBlue);
  //h_TRUTH_Convol->SetFillStyle(3002);
  h_TRUTH_Convol->SetLineColor(kRed);
  h_TRUTH_Convol->SetLineWidth(3);

  h_Data->Draw("PEC");
  h_TRUTH->Draw("Hist same");
  h_RECO->Draw("Hist same");
  h_TRUTH_Convol->Draw("Hist same");
  h_Data->Draw("PEC Same");
  int ndf=0;
  int ndf_data_TRUTHConvol =0;
  int ndf_reco_data =0;
  double chi_MC_MC =  mnvPlotter.Chi2MCMC(h_RECO, h_TRUTH_Convol, ndf);
  double chi_data_TRUTHConvol =  mnvPlotter.Chi2DataMC(h_Data, h_TRUTH_Convol, ndf_data_TRUTHConvol);
  double chi_reco_data =  mnvPlotter.Chi2DataMC(h_Data, h_RECO, ndf_reco_data);
  ChiSqrt_Truth_toRECO = chi_MC_MC;
  ChiSqrt_Truth_toData = chi_data_TRUTHConvol;
  ChiSqrt_Reco_toData = chi_reco_data;


  legend1->AddEntry(h_Data, "DATA", "elp");
  legend1->AddEntry(h_RECO, "RECO MC", "l");
  legend1->AddEntry(h_TRUTH, "TRUTH MC", "l");
  legend1->AddEntry(h_TRUTH_Convol, "Convoluted TRUTH MC", "l");
  sprintf(chi_label, "Reco to Conv" );
  legend1 -> AddEntry((TObject*)0, chi_label, "");
  sprintf(chi_label, "#chi^{2}/ndf = %.2f / %i = %.2f", chi_MC_MC, ndf, chi_MC_MC / ndf);
  legend1 -> AddEntry((TObject*)0, chi_label, "");
  sprintf(chi_label, "Data to Conv");
  legend1 -> AddEntry((TObject*)0, chi_label, "");
  sprintf(chi_label, "#chi^{2}/ndf = %.2f / %i = %.2f ", chi_data_TRUTHConvol, ndf_data_TRUTHConvol, chi_data_TRUTHConvol / ndf_data_TRUTHConvol);
  legend1 -> AddEntry((TObject*)0, chi_label, "");
  sprintf(chi_label, "Data to Reco");
  legend1 -> AddEntry((TObject*)0, chi_label, "");
  sprintf(chi_label, "#chi^{2}/ndf = %.2f / %i = %.2f ", chi_reco_data, ndf_reco_data, chi_reco_data / ndf_reco_data );
  legend1 -> AddEntry((TObject*)0, chi_label, "");
  legend1->Draw("Same");
  double size = 0.03;
  int align;
  double xLabel, yLabel;
  mnvPlotter.DecodePosition("TL", size, align, xLabel, yLabel );
  char Covoluteed[1024];
  sprintf(Covoluteed, "(#mu, #sigma)[mm] = (%.1f, %.1f)", Convoluted_Mean, Convoluted_stddev);

  mnvPlotter.AddPlotLabel(Covoluteed, xLabel + .2 , yLabel - .13, .038);


  cE.cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.2);
  pad2->SetGridx(); // vertical grid
  pad2->SetGridy(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  Data_Clone_1->Divide(Data_Clone_1, h_TRUTH_Convol);
  Data_Clone_1->SetLineColor(kRed);
  Data_Clone_1->SetLineWidth(3);
  mnvPlotter.axis_title_offset_y = .4;
  Data_Clone_2->Divide(Data_Clone_2, h_RECO);
  Data_Clone_2->SetLineColor(49);
  Data_Clone_2->SetLineWidth(3);
  Data_Clone_1->GetYaxis()->SetTitle("#frac{Data}{MC}");
  Data_Clone_1->GetYaxis()->SetTitleOffset(mnvPlotter.axis_title_offset_y );
  Data_Clone_1->GetXaxis()->SetTitleFont(mnvPlotter.axis_title_font_x);
  Data_Clone_1->GetYaxis()->SetTitleFont(mnvPlotter.axis_title_font_y);
  Data_Clone_1->GetXaxis()->SetTitleSize(mnvPlotter.axis_title_size_x);
  Data_Clone_1->GetYaxis()->SetTitleSize(mnvPlotter.axis_title_size_y);
  Data_Clone_1->GetXaxis()->SetLabelFont(mnvPlotter.axis_label_font);
  Data_Clone_1->GetYaxis()->SetLabelFont(mnvPlotter.axis_label_font);
  Data_Clone_1->GetXaxis()->SetLabelSize(mnvPlotter.axis_label_size);
  Data_Clone_1->GetYaxis()->SetLabelSize(mnvPlotter.axis_label_size);
  Data_Clone_1->GetYaxis()->CenterTitle(kTRUE);
  Data_Clone_1->Draw("PEC");

  Data_Clone_2->Draw("SAME");
  cE.cd();

  char total_title[1024];
  sprintf(total_title, "%s [%s(%s)]", histotitle, Playlist_name, playlist_status);
  mnvPlotter.AddHistoTitle(total_title, .04);
  mnvPlotter.WritePreliminary("TL", .035, 0, 0, false);
  std::string plotname = Form("%s",pdf_label.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");
  cE.Closed();

  if(MakeXaxisLOG==true){
    gPad->SetLogx(0);
  }




}//END of Function
///////////////////////////////////////////////////////////////////////////////
void Draw_Data_RECO_TRUTH_Hist_withConvolutionRECO_fromPointers(
  MnvH1D *hist_Data,
  MnvH1D *hist_RECOMC,
  MnvH1D *hist_RECO_Convolution,
  MnvH1D *hist_TRUTH,
  bool AreaNorm_todata,
  char *Playlist_name,
  std::string pdf_label,
  char *histotitle,
  char* playlist_status,
  char *xaxislabel,
  char* yaxislabel,
  bool DoBinwidthNorm,
  bool MakeXaxisLOG,
  double Ymax,
  double Convoluted_Mean, double Convoluted_stddev ,
  double &ChiSqrt_ConvolRECOtoRECO,
  double &ChiSqrt_ConvolRECOtoData,
  double &ChiSqrt_RECO_toData

    )
{
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  mnvPlotter.axis_title_size_x = 0.09;
  mnvPlotter.axis_title_size_y = 0.09;
  mnvPlotter.axis_label_size = 0.1;

  TCanvas cE ("c1","c1");
  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad

  auto h_Data = (PlotUtils::MnvH1D*)hist_Data->Clone("h_Data");
  auto h_RECO = (PlotUtils::MnvH1D*)hist_RECOMC->Clone("h_RECO");
  auto h_TRUTH = (PlotUtils::MnvH1D*)hist_TRUTH->Clone("h_TRUTH");
  auto h_RECO_Convol = (PlotUtils::MnvH1D*)hist_RECO_Convolution->Clone("h_RECO_Convol");

  string TotalTitle = string(histotitle);

  if(AreaNorm_todata==true){

    int N_Data = h_Data->GetNbinsX();
    int N_RECO = h_RECO->GetNbinsX();
    int N_TRUTH = h_TRUTH->GetNbinsX();
    int N_RECO_Convol =h_RECO_Convol->GetNbinsX();

    if(N_Data != N_RECO || N_Data != N_TRUTH  || N_Data != N_RECO_Convol ) {
      std::cout<<"The Bins are different sizes for: Draw_Data_RECO_TRUTH_Hist_withConvolutionRECO_fromPointers"<<std::endl;
      std::cout<< "with Xaxis = "<< xaxislabel << std::endl;
      std::cout<< "N_Data = " <<  N_Data <<std::endl;
      std::cout<< "N_RECO = " <<  N_RECO <<std::endl;
      std::cout<< "N_TRUTH = " <<  N_TRUTH <<std::endl;
      assert(false);
    }

    double Area_Data = h_Data->Integral();
    double Area_RECO = h_RECO->Integral();
    double Area_TRUTH = h_TRUTH->Integral();
    double Area_RECO_Convol =h_RECO_Convol->Integral();

    h_RECO->Scale(Area_Data/Area_RECO);
    h_TRUTH->Scale(Area_Data/Area_TRUTH);
    h_RECO_Convol->Scale(Area_Data/Area_RECO_Convol);

  }

  char ytitle[100];



  if(DoBinwidthNorm==true){
    h_Data->Scale(1.0,"width");
    h_RECO->Scale(1.0,"width");
    h_TRUTH->Scale(1.0,"width");
    h_RECO_Convol->Scale(1.0,"width");

    Ymax = 1.65 *  maximum(h_Data->GetMaximum(),h_RECO->GetMaximum(),h_TRUTH->GetMaximum());
    double binwidth_title = hist_Data->GetBinWidth(5);
    sprintf(ytitle, "NEvents / [%.2f %s] ", binwidth_title , yaxislabel);
    if(AreaNorm_todata==true){sprintf(ytitle, "NEvents [AreaNorm to Data] / [%.2f %s] ", binwidth_title , yaxislabel);}
  }

  else{
    sprintf(ytitle, "NEvents");

  }

  if(MakeXaxisLOG==true){
    gPad->SetLogx();
  }

  SetHist_Data(*h_Data, xaxislabel , ytitle);
  SetHist_Data(*hist_Data, xaxislabel , ytitle);
  auto Data_Clone_1 = (PlotUtils::MnvH1D*)h_Data->Clone("Data_Clone_1");
  auto Data_Clone_2 = (PlotUtils::MnvH1D*)h_Data->Clone("Data_Clone_2");

  Data_Clone_1->SetLineColor(kBlue);
  Data_Clone_2->SetLineColor(kRed);
  Data_Clone_1->SetLineStyle(2);
  Data_Clone_2->SetLineStyle(2);

  auto MC_Clone_1 = (PlotUtils::MnvH1D*)h_RECO->Clone("MC_Clone_1");
  auto MC_Clone_2 = (PlotUtils::MnvH1D*)h_RECO_Convol->Clone("MC_Clone_2");

  double x1, x2, y1, y2;
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", 6.5, 6., .025);
  TLegend *legend1 = new TLegend(x1+.005 , y1 + .12, x2 + .095, y2 + .35); // .2,.34
  legend1->SetTextSize(0.023);
  char chi_label[1024];
  h_Data->SetMaximum(Ymax);
  h_Data->SetMarkerColor(kBlack);
  h_RECO->SetLineColor(kBlue);
  h_RECO->SetLineWidth(3);
  h_TRUTH->SetLineColor(kGreen);
  h_TRUTH->SetLineWidth(3);
  //h_TRUTH_Convol->SetLineColor(kBlue);
  //h_TRUTH_Convol->SetFillStyle(3002);
  h_RECO_Convol->SetLineColor(kRed);
  h_RECO_Convol->SetLineWidth(3);

  h_Data->Draw("PEC");
  h_TRUTH->Draw("Hist same");
  h_RECO->Draw("Hist same");
  h_RECO_Convol->Draw("Hist same");
  h_Data->Draw("PEC Same");
  int ndf=0;
  int ndf_data_RECOConvol =0;
  int ndf_reco_data =0;
  double chi_MC_MC =  mnvPlotter.Chi2MCMC(h_RECO, h_RECO_Convol, ndf);
  double chi_data_RECOConvol =  mnvPlotter.Chi2DataMC(h_Data, h_RECO_Convol, ndf_data_RECOConvol);
  double chi_reco_data =  mnvPlotter.Chi2DataMC(h_Data, h_RECO, ndf_reco_data);
  ChiSqrt_ConvolRECOtoRECO = chi_MC_MC;
  ChiSqrt_ConvolRECOtoData = chi_data_RECOConvol;
  ChiSqrt_RECO_toData = chi_reco_data;


  legend1->AddEntry(h_Data, "DATA", "elp");
  legend1->AddEntry(h_RECO, "RECO MC", "l");
  legend1->AddEntry(h_RECO_Convol, "Convoluted RECO MC", "l");
  legend1->AddEntry(h_TRUTH, "TRUTH MC", "l");
  legend1->AddEntry(Data_Clone_1, "Ratio #frac{Data}{Reco}", "l");
  legend1->AddEntry(Data_Clone_2, "Ratio #frac{Data}{ConvolutedReco}", "l");

  sprintf(chi_label, "Reco to Conv Reco" );
  legend1 -> AddEntry((TObject*)0, chi_label, "");
  sprintf(chi_label, "#chi^{2}/ndf = %.1f / %i = %.1f", chi_MC_MC, ndf, chi_MC_MC / ndf);
  legend1 -> AddEntry((TObject*)0, chi_label, "");
  sprintf(chi_label, "Data to Conv RECO");
  legend1 -> AddEntry((TObject*)0, chi_label, "");
  sprintf(chi_label, "#chi^{2}/ndf = %.1f / %i = %.1f ", chi_data_RECOConvol, ndf_data_RECOConvol, chi_data_RECOConvol / ndf_data_RECOConvol);
  legend1 -> AddEntry((TObject*)0, chi_label, "");
  sprintf(chi_label, "Data to Reco");
  legend1 -> AddEntry((TObject*)0, chi_label, "");
  sprintf(chi_label, "#chi^{2}/ndf = %.1f / %i = %.1f ", chi_reco_data, ndf_reco_data, chi_reco_data / ndf_reco_data );
  legend1 -> AddEntry((TObject*)0, chi_label, "");

  legend1->Draw("Same");
  double size = 0.035;
  int align;
  double xLabel, yLabel;
  mnvPlotter.DecodePosition("TL", size, align, xLabel, yLabel );
  char Covoluteed[1024];
  sprintf(Covoluteed, "#frac{1}{#sigma#sqrt{2#pi}} e #left( -#frac{1}{2}#left(#frac{x-#mu}{#sigma}#right)^{2}#right) = (#mu, #sigma)[mm] = (%.1f, %.1f)", Convoluted_Mean, Convoluted_stddev);

  mnvPlotter.AddPlotLabel(Covoluteed, xLabel + .21 , yLabel - .13, .038);


  cE.cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.2);
  pad2->SetGridx(); // vertical grid
  pad2->SetGridy(); // vertical grid
  pad2->Draw();
  pad2->cd();

  Data_Clone_1->SetLineStyle(2);
  Data_Clone_2->SetLineStyle(2);        // pad2 becomes the current pad
  Data_Clone_1->Divide(Data_Clone_1, MC_Clone_1);
  //Data_Clone_1->SetLineColor(kRed);
  Data_Clone_1->SetLineWidth(3);
  mnvPlotter.axis_title_offset_y = .4;
  Data_Clone_2->Divide(Data_Clone_2, MC_Clone_2);
  Data_Clone_2->SetLineWidth(3);
  Data_Clone_1->GetYaxis()->SetTitle("#frac{Data}{MC}");
  Data_Clone_1->GetYaxis()->SetTitleOffset(mnvPlotter.axis_title_offset_y );
  Data_Clone_1->GetXaxis()->SetTitleFont(mnvPlotter.axis_title_font_x);
  Data_Clone_1->GetYaxis()->SetTitleFont(mnvPlotter.axis_title_font_y);
  Data_Clone_1->GetXaxis()->SetTitleSize(mnvPlotter.axis_title_size_x);
  Data_Clone_1->GetYaxis()->SetTitleSize(mnvPlotter.axis_title_size_y);
  Data_Clone_1->GetXaxis()->SetLabelFont(mnvPlotter.axis_label_font);
  Data_Clone_1->GetYaxis()->SetLabelFont(mnvPlotter.axis_label_font);
  Data_Clone_1->GetXaxis()->SetLabelSize(mnvPlotter.axis_label_size);
  Data_Clone_1->GetYaxis()->SetLabelSize(mnvPlotter.axis_label_size);
  Data_Clone_1->GetYaxis()->CenterTitle(kTRUE);
  Data_Clone_1->SetMaximum(3.0);
  Data_Clone_1->SetMinimum(0.0);
  Data_Clone_1->Draw("PEC");
  Data_Clone_2->Draw("SAME");
  cE.cd();

  char total_title[1024];
  sprintf(total_title, "%s [%s(%s)]", histotitle, Playlist_name, playlist_status);
  mnvPlotter.AddHistoTitle(total_title, .04);
  mnvPlotter.WritePreliminary("TL", .032, 0, 0, false);
  std::string plotname = Form("%s",pdf_label.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");
  cE.Closed();

  if(MakeXaxisLOG==true){
    gPad->SetLogx(0);
  }

}//END of Function





void Draw_Data_RECO_TRUTH_Hist_withConvolutionRECO_fromPointers(
  MnvH1D *hist_Data,
  MnvH1D *hist_RECOMC,
  MnvH1D *hist_RECO_Convolution,
  MnvH1D *hist_TRUTH,
  bool AreaNorm_todata,
  char *Playlist_name,
  std::string pdf_label,
  char *histotitle,
  char* playlist_status,
  char *xaxislabel,
  char* yaxislabel,
  bool DoBinwidthNorm,
  bool MakeXaxisLOG,
  double Ymax,
  double Convoluted_MeanF, double Convoluted_stddevF,
  double Convoluted_MeanE, double Convoluted_stddevE,
  double &ChiSqrt_ConvolRECOtoRECO,
  double &ChiSqrt_ConvolRECOtoData,
  double &ChiSqrt_RECO_toData

    )
{
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  mnvPlotter.axis_title_size_x = 0.09;
  mnvPlotter.axis_title_size_y = 0.09;
  mnvPlotter.axis_label_size = 0.1;

  TCanvas cE ("c1","c1");
  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad

  auto h_Data = (PlotUtils::MnvH1D*)hist_Data->Clone("h_Data");
  auto h_RECO = (PlotUtils::MnvH1D*)hist_RECOMC->Clone("h_RECO");
  auto h_TRUTH = (PlotUtils::MnvH1D*)hist_TRUTH->Clone("h_TRUTH");
  auto h_RECO_Convol = (PlotUtils::MnvH1D*)hist_RECO_Convolution->Clone("h_RECO_Convol");

  string TotalTitle = string(histotitle);

  if(AreaNorm_todata==true){

    int N_Data = h_Data->GetNbinsX();
    int N_RECO = h_RECO->GetNbinsX();
    int N_TRUTH = h_TRUTH->GetNbinsX();
    int N_RECO_Convol =h_RECO_Convol->GetNbinsX();

    if(N_Data != N_RECO || N_Data != N_TRUTH  || N_Data != N_RECO_Convol ) {
      std::cout<<"The Bins are different sizes for: Draw_Data_RECO_TRUTH_Hist_withConvolutionRECO_fromPointers"<<std::endl;
      std::cout<< "with Xaxis = "<< xaxislabel << std::endl;
      std::cout<< "N_Data = " <<  N_Data <<std::endl;
      std::cout<< "N_RECO = " <<  N_RECO <<std::endl;
      std::cout<< "N_TRUTH = " <<  N_TRUTH <<std::endl;
      assert(false);
    }

    double Area_Data = h_Data->Integral();
    double Area_RECO = h_RECO->Integral();
    double Area_TRUTH = h_TRUTH->Integral();
    double Area_RECO_Convol =h_RECO_Convol->Integral();

    h_RECO->Scale(Area_Data/Area_RECO);
    h_TRUTH->Scale(Area_Data/Area_TRUTH);
    h_RECO_Convol->Scale(Area_Data/Area_RECO_Convol);

  }

  char ytitle[100];

  if(DoBinwidthNorm==true){
    h_Data->Scale(1.0,"width");
    h_RECO->Scale(1.0,"width");
    h_TRUTH->Scale(1.0,"width");
    h_RECO_Convol->Scale(1.0,"width");

    Ymax = 1.65 *  maximum(h_Data->GetMaximum(),h_RECO->GetMaximum(),h_TRUTH->GetMaximum());
    double binwidth_title = hist_Data->GetBinWidth(5);
    sprintf(ytitle, "NEvents / [%.2f %s] ", binwidth_title , yaxislabel);
    if(AreaNorm_todata==true){sprintf(ytitle, "NEvents [AreaNorm to Data] / [%.2f %s] ", binwidth_title , yaxislabel);}
  }

  else{
    sprintf(ytitle, "NEvents");

  }

  if(MakeXaxisLOG==true){
    gPad->SetLogx();
  }
  SetHist_Data(*h_Data, xaxislabel , ytitle);
  SetHist_Data(*hist_Data, xaxislabel , ytitle);
  auto Data_Clone_1 = (PlotUtils::MnvH1D*)h_Data->Clone("Data_Clone_1");
  auto Data_Clone_2 = (PlotUtils::MnvH1D*)h_Data->Clone("Data_Clone_2");

  Data_Clone_1->SetLineColor(kBlue);
  Data_Clone_2->SetLineColor(kRed);
  Data_Clone_1->SetLineStyle(2);
  Data_Clone_2->SetLineStyle(2);

  auto MC_Clone_1 = (PlotUtils::MnvH1D*)h_RECO->Clone("MC_Clone_1");
  auto MC_Clone_2 = (PlotUtils::MnvH1D*)h_RECO_Convol->Clone("MC_Clone_2");



  double x1, x2, y1, y2;
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", 6.5, 6., .025);
  TLegend *legend1 = new TLegend(x1 , y1 + .1, x2 + .085, y2 + .3); // .2,.34
  legend1->SetTextSize(0.023);
  char chi_label[1024];
  h_Data->SetMaximum(Ymax);
  h_Data->SetMarkerColor(kBlack);
  h_RECO->SetLineColor(kBlue);
  h_RECO->SetLineWidth(3);
  h_TRUTH->SetLineColor(kGreen);
  h_TRUTH->SetLineWidth(3);
  //h_TRUTH_Convol->SetLineColor(kBlue);
  //h_TRUTH_Convol->SetFillStyle(3002);
  h_RECO_Convol->SetLineColor(kRed);
  h_RECO_Convol->SetLineWidth(3);

  h_Data->Draw("PEC");
  h_TRUTH->Draw("Hist same");
  h_RECO->Draw("Hist same");
  h_RECO_Convol->Draw("Hist same");
  h_Data->Draw("PEC Same");
  int ndf=0;
  int ndf_data_RECOConvol =0;
  int ndf_reco_data =0;
  double chi_MC_MC =  mnvPlotter.Chi2MCMC(h_RECO, h_RECO_Convol, ndf);
  double chi_data_RECOConvol =  mnvPlotter.Chi2DataMC(h_Data, h_RECO_Convol, ndf_data_RECOConvol);
  double chi_reco_data =  mnvPlotter.Chi2DataMC(h_Data, h_RECO, ndf_reco_data);
  ChiSqrt_ConvolRECOtoRECO = chi_MC_MC;
  ChiSqrt_ConvolRECOtoData = chi_data_RECOConvol;
  ChiSqrt_RECO_toData = chi_reco_data;


  legend1->AddEntry(h_Data, "DATA", "elp");
  legend1->AddEntry(h_RECO, "RECO MC", "l");
  legend1->AddEntry(h_RECO_Convol, "Convoluted RECO MC", "l");
  legend1->AddEntry(h_TRUTH, "TRUTH MC", "l");
  legend1->AddEntry(Data_Clone_1, "Ratio #frac{Data}{Reco}", "l");
  legend1->AddEntry(Data_Clone_2, "Ratio #frac{Data}{ConvolutedReco}", "l");

  sprintf(chi_label, "Reco to Conv Reco" );
  legend1 -> AddEntry((TObject*)0, chi_label, "");
  sprintf(chi_label, "#chi^{2}/ndf = %.1f / %i = %.1f", chi_MC_MC, ndf, chi_MC_MC / ndf);
  legend1 -> AddEntry((TObject*)0, chi_label, "");
  sprintf(chi_label, "Data to Conv RECO");
  legend1 -> AddEntry((TObject*)0, chi_label, "");
  sprintf(chi_label, "#chi^{2}/ndf = %.1f / %i = %.1f ", chi_data_RECOConvol, ndf_data_RECOConvol, chi_data_RECOConvol / ndf_data_RECOConvol);
  legend1 -> AddEntry((TObject*)0, chi_label, "");
  sprintf(chi_label, "Data to Reco");
  legend1 -> AddEntry((TObject*)0, chi_label, "");
  sprintf(chi_label, "#chi^{2}/ndf = %.1f / %i = %.1f ", chi_reco_data, ndf_reco_data, chi_reco_data / ndf_reco_data );
  legend1 -> AddEntry((TObject*)0, chi_label, "");
  legend1->Draw("Same");
  double size = 0.035;
  int align;
  double xLabel, yLabel;
  mnvPlotter.DecodePosition("TL", size, align, xLabel, yLabel );
  char Covoluteed[1024];
  sprintf(Covoluteed, "#frac{1}{#sigma#sqrt{2#pi}} e #left( -#frac{1}{2}#left(#frac{x-#mu}{#sigma}#right)^{2}#right) = (#mu, #sigma)[F-E] = (%.1f, %.1f)-(%.1f, %.1f)", Convoluted_MeanF, Convoluted_stddevF, Convoluted_MeanE, Convoluted_stddevE);

  mnvPlotter.AddPlotLabel(Covoluteed, xLabel + .21 , yLabel - .13, .038);


  cE.cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.2);
  pad2->SetGridx(); // vertical grid
  pad2->SetGridy(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  Data_Clone_1->Divide(Data_Clone_1, MC_Clone_1);
  Data_Clone_1->SetLineWidth(3);
  mnvPlotter.axis_title_offset_y = .4;
  Data_Clone_2->Divide(Data_Clone_2, MC_Clone_2);
  Data_Clone_2->SetLineWidth(3);
  Data_Clone_1->GetYaxis()->SetTitle("#frac{Data}{MC}");
  Data_Clone_1->GetYaxis()->SetTitleOffset(mnvPlotter.axis_title_offset_y );
  Data_Clone_1->GetXaxis()->SetTitleFont(mnvPlotter.axis_title_font_x);
  Data_Clone_1->GetYaxis()->SetTitleFont(mnvPlotter.axis_title_font_y);
  Data_Clone_1->GetXaxis()->SetTitleSize(mnvPlotter.axis_title_size_x);
  Data_Clone_1->GetYaxis()->SetTitleSize(mnvPlotter.axis_title_size_y);
  Data_Clone_1->GetXaxis()->SetLabelFont(mnvPlotter.axis_label_font);
  Data_Clone_1->GetYaxis()->SetLabelFont(mnvPlotter.axis_label_font);
  Data_Clone_1->GetXaxis()->SetLabelSize(mnvPlotter.axis_label_size);
  Data_Clone_1->GetYaxis()->SetLabelSize(mnvPlotter.axis_label_size);
  Data_Clone_1->GetYaxis()->CenterTitle(kTRUE);
  Data_Clone_1->SetMaximum(3.0);
  Data_Clone_1->SetMinimum(0.0);
  Data_Clone_1->Draw("PEC");
  Data_Clone_1->Draw("PEC");
  Data_Clone_2->Draw("SAME");
  cE.cd();

  char total_title[1024];
  sprintf(total_title, "%s [%s(%s)]", histotitle, Playlist_name, playlist_status);
  mnvPlotter.AddHistoTitle(total_title, .04);
  mnvPlotter.WritePreliminary("TL", .035, 0, 0, false);
  std::string plotname = Form("%s",pdf_label.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");
  cE.Closed();

  if(MakeXaxisLOG==true){
    gPad->SetLogx(0);
  }




}//END of Function
//////////////////////////////////////////////////////////////////////////////
void Draw_Data_RECO_TRUTH_Hist_fromPointer( MnvH1D *histMC_TRUTH, MnvH1D *histMC_RECO,  MnvH1D *hist_Data,
  char *Playlist_name, char* playlist_status, std::string pdf_label, char *histotitle,
   char *xaxislabel,char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG , double Ymax )
{
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  mnvPlotter.axis_title_size_x = 0.09;
  mnvPlotter.axis_title_size_y = 0.09;
  mnvPlotter.axis_label_size = 0.1;
  TCanvas cE ("c1","c1");
  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  double x1,y1,x2,y2;
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", 6.5, 6., .025);
  TLegend *legend = new TLegend(x1 - .015, y1 + .32, x2 + .075, y2 + .3);

  std::string TotalTitle = string(histotitle);

  char ytitle[100];

  if(DoBinwidthNorm==true){
    histMC_TRUTH->Scale(1.0,"width");
    histMC_RECO->Scale(1.0,"width");
    hist_Data->Scale(1.0,"width");

    Ymax = 1.55 *  maximum(histMC_TRUTH->GetMaximum(),histMC_RECO->GetMaximum(),hist_Data->GetMaximum());
    double binwidth_title = hist_Data->GetBinWidth(5);
    sprintf(ytitle, "Number of Events / [%.2f %s] ", binwidth_title , yaxislabel);
  }
  else{
    sprintf(ytitle, "Number of Events");

  }



  SetHist_Data(*hist_Data, xaxislabel , ytitle);

  if(MakeXaxisLOG==true){
    gPad->SetLogx();
  }

  //SetMaxforDraw(hist_Data, histMC_TRUTH, histMC_RECO);
  hist_Data->SetMaximum(Ymax);
  hist_Data->SetMarkerColor(kBlack);
  hist_Data->Draw("PEC");
  histMC_RECO->SetLineColor(kRed);
  histMC_RECO->SetLineWidth(3);
  histMC_RECO->Draw("Hist same");
  histMC_TRUTH->SetLineColor(kGreen);
  histMC_TRUTH->SetLineWidth(3);
  histMC_TRUTH->Draw("Hist same");
  legend->AddEntry(hist_Data, "DATA", "P");
  legend->AddEntry(histMC_RECO, "RECO MC", "l");
  legend->AddEntry(histMC_TRUTH, "TRUTH MC", "l");
  legend->Draw("Same");

  cE.cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.2);
  pad2->SetGridx(); // vertical grid
  pad2->SetGridy(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  auto Data_Clone_1 = (PlotUtils::MnvH1D*)hist_Data->Clone("Data_Clone_1");
  auto Data_Clone_2 = (PlotUtils::MnvH1D*)hist_Data->Clone("Data_Clone_2");
  Data_Clone_1->Divide(Data_Clone_1, histMC_TRUTH);
  Data_Clone_1->SetLineColor(kGreen);
  Data_Clone_2->Divide(Data_Clone_2, histMC_RECO);
  Data_Clone_2->SetLineColor(kRed);
  mnvPlotter.axis_title_offset_y = .4;
  Data_Clone_1->GetYaxis()->SetTitle("#frac{Data}{MC}");
  Data_Clone_1->GetYaxis()->SetTitleOffset(mnvPlotter.axis_title_offset_y );
  Data_Clone_1->GetXaxis()->SetTitleFont(mnvPlotter.axis_title_font_x);
  Data_Clone_1->GetYaxis()->SetTitleFont(mnvPlotter.axis_title_font_y);
  Data_Clone_1->GetXaxis()->SetTitleSize(mnvPlotter.axis_title_size_x);
  Data_Clone_1->GetYaxis()->SetTitleSize(mnvPlotter.axis_title_size_y);
  Data_Clone_1->GetXaxis()->SetLabelFont(mnvPlotter.axis_label_font);
  Data_Clone_1->GetYaxis()->SetLabelFont(mnvPlotter.axis_label_font);
  Data_Clone_1->GetXaxis()->SetLabelSize(mnvPlotter.axis_label_size);
  Data_Clone_1->GetYaxis()->SetLabelSize(mnvPlotter.axis_label_size);
  Data_Clone_1->GetXaxis()->CenterTitle(kTRUE);
  Data_Clone_1->SetLineWidth(3);
  Data_Clone_2->SetLineWidth(3);
  Data_Clone_1->Draw("PEC");
  Data_Clone_2->Draw("SAME");


  cE.cd();
  char total_title[1024];
  sprintf(total_title, "%s [%s(%s)]", histotitle, Playlist_name, playlist_status);
  mnvPlotter.AddHistoTitle(total_title, .04);
  mnvPlotter.WritePreliminary("TL", .035, 0, 0, false);
  std::string plotname = Form("%s",pdf_label.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");

  cE.Closed();

  if(MakeXaxisLOG==true){
    gPad->SetLogx(0);
  }




}//END of Function


////////////////////////////////////////////////////////////////////////////////
void Draw_MCHist_fromTFile_SMEARING(TFile *inputFile_MCinput, char *histoName_MC_CV,
   char *histoName_MC_shifts, std::string pdf_label, char *histotitle, char *xaxislabel,char* yaxislabel )
{
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  std::cout<<"trying to draw 1D, HisName  = "<< histoName_MC_CV<<std::endl;
  char CV_char[1024];
  sprintf(CV_char, "%s_CV",histoName_MC_CV);
  char Neg_char[1024];
  sprintf(Neg_char, "%s_Neg",histoName_MC_shifts);
  char Pos_char[1024];
  sprintf(Pos_char, "%s_Pos",histoName_MC_shifts);

  MnvH1D *hist_CV = (MnvH1D*)inputFile_MCinput -> Get(CV_char);
  MnvH1D *hist_pos = (MnvH1D*)inputFile_MCinput -> Get(Pos_char);
  MnvH1D *hist_neg = (MnvH1D*)inputFile_MCinput -> Get(Neg_char);
  string TotalTitle = string(histotitle);
  double x1, x2, y1, y2;
  TLegend *legend = new TLegend (0.80,0.73,0.95,.88);
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", 6.5, 6., .025);


 hist_CV->GetXaxis()->CenterTitle();
 hist_CV->GetYaxis()->CenterTitle();
 hist_CV->GetXaxis()->SetTitle(xaxislabel);
 hist_CV->GetYaxis()->SetTitle(yaxislabel);
 hist_CV->GetXaxis()->SetTitleSize(0.038);
 hist_CV->GetYaxis()->SetTitleSize(0.038);
 hist_CV->SetLineColor(kBlack);
 hist_CV->SetLineWidth(5);
 hist_pos->SetLineColor(kBlue);
 hist_neg->SetLineColor(kRed);
 hist_pos->SetLineWidth(5);
 hist_neg->SetLineWidth(5);
 hist_pos->SetLineStyle(2);
 hist_neg->SetLineStyle(2);
 hist_CV->SetMaximum(hist_neg->GetMaximum() * 1.25);
 legend->AddEntry(hist_CV, "CV");
 legend->AddEntry(hist_pos, "Pos shift");
 legend->AddEntry(hist_neg, "Neg shift");
 hist_CV->Draw("HIST");
 hist_pos->Draw("HIST same");
 hist_neg->Draw("HIST same");
 legend->Draw("same");
 char total_title[1024];
 sprintf(total_title, "%s", histotitle);
 mnvPlotter.AddHistoTitle(total_title, .04);
 mnvPlotter.WritePreliminary("TL", .035, 0, 0, false);
 std::string plotname = Form("%s",pdf_label.c_str());
 mnvPlotter.MultiPrint(&cE, plotname, "pdf");
 cE.Closed();

}






TGraphErrors  *MakeTGraph_from_Mvn1HD(TFile *inputFile_MCinput,  char *histoName_MC)
{
  MnvH1D *hist = (MnvH1D*)inputFile_MCinput -> Get(histoName_MC);

  int N_bins = hist->GetNbinsX();
  std::vector<double> BinsEdges_vector;
  std::vector<double> Weights_vector;
  std::vector<double> Errors_vector;

  for(unsigned int i =0; i<N_bins+1;++i){
    double Weight = hist->GetBinContent(i);
    double error = hist->GetBinError(i);
    double edges = hist->GetBinLowEdge(i);

    Weights_vector.push_back(Weight);
    Errors_vector.push_back(error);
    BinsEdges_vector.push_back(edges);
  }

  double x[BinsEdges_vector.size()];
  double y[Weights_vector.size()];
  double ey[Errors_vector.size()];
  int n= N_bins+1;

  for(unsigned int i =0; i<n;i++){
    x[i]=BinsEdges_vector.at(i);
    y[i]=Weights_vector.at(i);
    ey[i]= Errors_vector.at(i);

  }



TGraphErrors *gr = new TGraphErrors(n,x,y,0,ey);

return gr;

}//end of function

TGraphErrors  *MakeTGraph_from_Vectors(std::vector<double> Y_para,  std::vector<double> X_para)
{

  if(Y_para.size() != X_para.size()) {std::cout<<"Oops X and Y Bins are different sizes can't make TGraph"<< " | Y_para.size() = " << Y_para.size() << "  | X_para.size() = "<< X_para.size()<<std::endl; assert(false);  }

  double x[X_para.size()];
  double y[Y_para.size()];
  double ey[Y_para.size()];
  int n= X_para.size();

  for(unsigned int i=0; i<n;i++){
    x[i]=X_para.at(i);
    y[i]=Y_para.at(i);
    ey[i]= TMath::Sqrt(Y_para.at(i));

  }



TGraphErrors *gr = new TGraphErrors(n,x,y,0,ey);

return gr;

}//end of function

TGraph  *MakeTGraph_NOERRORS_from_Vectors(std::vector<double> Y_para,  std::vector<double> X_para)
{

  if(Y_para.size() != X_para.size()) {std::cout<<"Oops X and Y Bins are different sizes can't make TGraph"<< " | Y_para.size() = " << Y_para.size() << "  | X_para.size() = "<< X_para.size()<<std::endl; assert(false);  }

  double x[X_para.size()];
  double y[Y_para.size()];
  int n= X_para.size();

  for(unsigned int i=0; i<n;i++){
    x[i]=X_para.at(i);
    y[i]=Y_para.at(i);
  }



TGraph *gr = new TGraph(n,x,y);

return gr;

}//end of function


TGraph* createTGraph(const std::vector<double> xValues, const std::vector<double> yValues) {
    int nPoints = xValues.size(); // Number of data points
    if (nPoints != yValues.size()) {
        // Check if the sizes of x and y vectors match
        std::cout << "Error: Sizes of x and y vectors do not match!" << std::endl;
        return nullptr; // Return nullptr to indicate error
    }

    // Create TGraph object with the same number of points as input vectors
    TGraph* graph = new TGraph(nPoints);

    // Loop over input vectors and set data points in TGraph
    for (int i = 0; i < nPoints; ++i) {
        graph->SetPoint(i, xValues[i], yValues[i]);
    }

    return graph;
}



TGraphErrors  *MakeTGraph_from_VectorsNoErrors(std::vector<double> Y_para,  std::vector<double> X_para)
{

  if(Y_para.size() != X_para.size()) {std::cout<<"Oops X and Y Bins are different sizes can't make TGraph"<< " | Y_para.size() = " << Y_para.size() << "  | X_para.size() = "<< X_para.size()<<std::endl; assert(false);  }

  double x[X_para.size()];
  double y[Y_para.size()];
  double ey[Y_para.size()];
  int n= X_para.size();

  for(unsigned int i=0; i<n;i++){
    x[i]=X_para.at(i);
    y[i]=Y_para.at(i);
    ey[i]= 0.0;

  }



TGraphErrors *gr = new TGraphErrors(n,x,y,0,ey);

return gr;

}//end of function

TGraphErrors  *MakeTGraph_from_VectorsErrors(std::vector<double> Y_para, std::vector<double> y_para_errors, std::vector<double> X_para)
{

  if(Y_para.size() != X_para.size() || Y_para.size() != y_para_errors.size()) {std::cout<<"Oops X and Y Bins are different sizes can't make TGraph"<< " | Y_para.size() = " << Y_para.size() << "  | X_para.size() = "<< X_para.size()<<std::endl; assert(false);  }

  double x[X_para.size()];
  double y[Y_para.size()];
  double ey[y_para_errors.size()];
  int n = X_para.size();

  for(unsigned int i=0; i<n;++i){
    x[i]=X_para.at(i);
    y[i]=Y_para.at(i);
    ey[i]= y_para_errors.at(i);

  }



TGraphErrors *gr = new TGraphErrors(n,x,y,0,ey);

return gr;

}//end of function

void Draw_TGraph_fit(TFile *inputFile_MCinput,  char *histoName_MC, std::string pdf_label, char *histotitle, char *xaxislabel,char* yaxislabel)
{
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  std::cout<<"trying to draw 1D, HisName  = "<< histoName_MC<<std::endl;
  std::string TotalTitle = string(histotitle);

  auto TGraph_object = MakeTGraph_from_Mvn1HD(inputFile_MCinput,  histoName_MC);

  double x1, x2, y1, y2;
  TLegend *legend = new TLegend (0.80,0.73,0.95,.88);
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", 6.5, 6., .025);



//  TF1 *gfit = new TF1("Gaussian","gaus",min,max); // Create the fit function
  //gfit->SetParameters(500,TGraph_object->GetMean(),TGraph_object->GetRMS());
  //gfit->SetParNames("Constant","Mean_value","Sigma");
  //TGraph_object->Fit(gfit);

   TGraph_object -> SetTitle("");
   TGraph_object -> GetXaxis() -> SetTitle(xaxislabel);
   TGraph_object -> GetYaxis() -> SetTitle(yaxislabel);
   TGraph_object -> GetXaxis() -> CenterTitle();
   TGraph_object -> GetYaxis() -> CenterTitle();
   TGraph_object -> GetXaxis() -> SetTitleSize(0.038);
   TGraph_object -> GetYaxis() -> SetTitleSize(0.038);

   TGraph_object -> SetLineColor (2);
   TGraph_object -> SetMarkerColor (2);

  //TCanvas *optcan = new TCanvas("optcan");
  TGraph_object -> Draw("AP");


  legend -> SetTextSize(0.02);
  legend -> SetFillColor(0);
  legend -> AddEntry(TGraph_object, "True - Reco", "LP");
  legend -> Draw();

  char total_title[1024];
  sprintf(total_title, "%s", histotitle);
  mnvPlotter.AddHistoTitle(total_title, .04);
  mnvPlotter.WritePreliminary("TL", .035, 0, 0, false);
  std::string plotname = Form("%s",pdf_label.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");
  cE.Closed();

}




void Draw_MCHist_fromTFile_andFIT(TFile *inputFile_MCinput,  char *histoName_MC, std::string pdf_label, char *histotitle, char *xaxislabel,char* yaxislabel)
{
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  std::cout<<"trying to draw 1D, HisName  = "<< histoName_MC<<std::endl;
  MnvH1D *hist = (MnvH1D*)inputFile_MCinput -> Get(histoName_MC);
  string TotalTitle = string(histotitle);

  double min,max;
  min =  hist->GetXaxis()->GetXmin();
  max =  hist->GetXaxis()->GetXmax();
  TF1 *gfit = new TF1("Gaussian","gaus",min,max); // Create the fit function
  //gStyle->SetOptFit(112);
  //TF1 *gfit = new TF1("f", "[0]*TMath::Power(([1]/[2]),(x/[2]))*(TMath::Exp(-([1]/[2])))/TMath::Gamma((x/[2])+1.)", xmin, xmax);
  //gfit->SetParameters(1, 1, 1); // you MUST set non-zero initial values for parameters
   // define and "fill" the histogram
  gfit->SetParameters(500,hist->GetMean(),hist->GetRMS());
  gfit->SetParNames("Constant","Mean_value","Sigma");
  hist->Fit(gfit,"RQ");
  gStyle->SetOptFit(1111);

  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->CenterTitle();
  hist->GetXaxis()->SetTitle(xaxislabel);
  hist->GetYaxis()->SetTitle(yaxislabel);
  hist->GetXaxis()->SetTitleSize(0.038);
  hist->GetYaxis()->SetTitleSize(0.038);
  hist->SetLineColor(kBlue);
  hist->SetFillColor(kRed);
  hist->SetMaximum(hist->GetMaximum() * 1.25);
  hist->Draw("Hist p e");
  gfit->Draw("same");

 char total_title[1024];
 sprintf(total_title, "%s", histotitle);
 mnvPlotter.AddHistoTitle(total_title, .04);
 mnvPlotter.WritePreliminary("TL", .035, 0, 0, false);
 std::string plotname = Form("%s",pdf_label.c_str());
 mnvPlotter.MultiPrint(&cE, plotname, "pdf");
 cE.Closed();

}
void Draw_MCHist_WithErrorBands_fromTFile_andFIT(TFile *inputFile_MCinput,  char *histoName_MC, std::string pdf_label, char *histotitle, char *xaxislabel,char* yaxislabel)
{
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  double x1,y1,x2,y2;
  TLegend *legend = new TLegend (0.65,0.70,0.95,.88);
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", 6.5, 6., .025);

  std::cout<<"trying to draw 1D, HisName  = "<< histoName_MC<<std::endl;
  MnvH1D *hist = (MnvH1D*)inputFile_MCinput -> Get(histoName_MC);
  //string TotalTitle = string(histotitle);

  double min,max;
  min =  hist->GetXaxis()->GetXmin();
  max =  hist->GetXaxis()->GetXmax();
  int nbins = hist->GetNbinsX();
  TF1 *gfit = new TF1("Gaussian","gaus",min,max); // Create the fit function
  //gStyle->SetOptFit(112);
  //TF1 *gfit = new TF1("f", "[0]*TMath::Power(([1]/[2]),(x/[2]))*(TMath::Exp(-([1]/[2])))/TMath::Gamma((x/[2])+1.)", xmin, xmax);
  //gfit->SetParameters(1, 1, 1); // you MUST set non-zero initial values for parameters
   // define and "fill" the histogram
  gfit->SetParameters(500,hist->GetMean(),hist->GetRMS());
  gfit->SetParNames("Constant","Mean","Sigma");
  hist->Fit(gfit,"RQ");
  auto chi_sq = gfit->GetChisquare();
  auto NDF_int = gfit->GetNDF();

  auto constant_value = gfit->GetParameter(0);
  auto constant_value_error = gfit->GetParError(0);

  auto mean_value = gfit->GetParameter("Mean");
  auto mean_value_error = gfit->GetParError(1);

  auto sigma_value = gfit->GetParameter(2);
  auto sigma_value_error = gfit->GetParError(2);

  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->CenterTitle();
  hist->GetXaxis()->SetTitle(xaxislabel);
  hist->GetYaxis()->SetTitle(yaxislabel);
  hist->GetXaxis()->SetTitleSize(0.038);
  hist->GetYaxis()->SetTitleSize(0.038);

  hist->SetMaximum(hist->GetMaximum() * 1.25);
  //hist->Draw("Hist p e");

  PlotUtils::MnvH1D* datahist =new PlotUtils::MnvH1D("adsf", "", nbins, min, max);
  bool statPlusSys           = true;
  int mcScale                = 1.0;
  bool useHistTitles         = false;

  mnvPlotter.DrawDataMCWithErrorBand(datahist, hist, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);

  gfit->Draw("same");
  gStyle->SetOptFit(1111);
  char chi_name[1024];
  sprintf(chi_name , "#chi^{2} / ndf = %.2f / %i",chi_sq, NDF_int );
  char sigma_name[1024];
  sprintf(sigma_name , "#sigma  = %.2f #pm %.2f", sigma_value, sigma_value_error );
  char mean_name[1024];
  sprintf(mean_name , "Mean  = %.2f #pm %.2f", mean_value,mean_value_error );
  char contant_name[1024];
  sprintf(contant_name , "Contant  = %.2f #pm %.2f", constant_value, constant_value_error  );


  legend->AddEntry((TObject*)0, chi_name, ""); // to put fit param
  legend->AddEntry((TObject*)0, sigma_name, ""); // to put fit param
  legend->AddEntry((TObject*)0, mean_name, ""); // to put fit param
  legend->AddEntry((TObject*)0, contant_name, ""); // to put fit param

  legend->SetTextSize(0.02);
  legend->Draw("same");

 //char total_title[1024];
 //sprintf(total_title, "%s", histotitle);
 mnvPlotter.AddHistoTitle(histotitle, .04);
 mnvPlotter.WritePreliminary("TL", .035, 0, 0, false);
 std::string plotname = Form("%s",pdf_label.c_str());
 mnvPlotter.MultiPrint(&cE, plotname, "pdf");

 std::vector<bool> Print_Vector = Print_Systematics(0);
 mnvPlotter.legend_n_columns = 2;
 cE.Clear();
 // PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);
 PlotErrorSummaryNew(hist, plotname, histotitle, xaxislabel, &cE, &mnvPlotter,true,true);
 mnvPlotter.legend_n_columns = 1;




 cE.Closed();




}

void Draw_MCHist_withErrorSys_fromTFile(TFile *inputFile_MCinput,  char *histoName_MC, std::string pdf_label, char *histotitle, char *xaxislabel,char* yaxislabel, bool DoBinwidthNorm )
{
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  std::cout<<"trying to draw 1D, HisName  = "<< histoName_MC<<std::endl;
  MnvH1D *hist1 = (MnvH1D*)inputFile_MCinput -> Get(histoName_MC);
  auto hist = (PlotUtils::MnvH1D*)hist1->Clone("hist1");
  string TotalTitle = string(histotitle);


 hist->GetXaxis()->CenterTitle();
 hist->GetYaxis()->CenterTitle();
 hist->GetXaxis()->SetTitle(xaxislabel);
 hist->GetYaxis()->SetTitle(yaxislabel);
 hist->GetXaxis()->SetTitleSize(0.038);
 hist->GetYaxis()->SetTitleSize(0.038);
 hist->SetLineColor(kBlue);
 hist->SetLineWidth(5);
 hist->SetMaximum(hist->GetMaximum() * 1.25);

 PlotUtils::MnvH1D* datahist =new PlotUtils::MnvH1D("adsf", " ", nbins, xmin, xmax);
 bool statPlusSys           = true;
 int mcScale                = 1.;
 bool useHistTitles         = false;

 mnvPlotter.DrawDataMCWithErrorBand(datahist, hist, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);



 char total_title[1024];
 sprintf(total_title, "%s", histotitle);
 mnvPlotter.AddHistoTitle(total_title, .04);
 mnvPlotter.WritePreliminary("TL", .035, 0, 0, false);
 std::string plotname = Form("%s",pdf_label.c_str());
 mnvPlotter.MultiPrint(&cE, plotname, "pdf");
 cE.Closed();

 std::vector<bool> Print_Vector = Print_Systematics(0);
 mnvPlotter.legend_n_columns = 2;
 cE.Clear();
 // PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);
 PlotErrorSummaryNew(hist, plotname, histotitle, xaxislabel, &cE, &mnvPlotter,true,true);
 mnvPlotter.legend_n_columns = 1;


}
void Draw_MCHist_withErrorSys_fromTFile(TFile *inputFile_MCFull,TFile *inputFile_MCEmpty,  char *histoName_MC,
  Pot_MapStatusList POT_MC, Pot_MapStatusList POT_DATA , std::string pdf_label, char *histotitle, char *xaxislabel,
  char* yaxislabel, bool DoBinwidthNorm )
{

  double scale_to_FULLMC= POT_MC[kFULL] / POT_MC[kEMPTY];

  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  std::cout<<"trying to draw 1D, HisName  = "<< histoName_MC<<std::endl;
  MnvH1D *hist1 = (MnvH1D*)inputFile_MCFull -> Get(histoName_MC);
  MnvH1D *hist2 = (MnvH1D*)inputFile_MCEmpty -> Get(histoName_MC);
  auto hist_Full = (PlotUtils::MnvH1D*)hist1->Clone("hist1");
  auto hist_Full_Empty = (PlotUtils::MnvH1D*)hist1->Clone("hist1");
  auto hist_Empty = (PlotUtils::MnvH1D*)hist2->Clone("hist2");
  hist_Empty->Scale(scale_to_FULLMC);
  if(DoBinwidthNorm==true){
    hist_Full->Scale(1.0,"width");
    hist_Empty->Scale(1.0,"width");
    hist_Full_Empty->Scale(1.0,"width");
  }


  string TotalTitle = string(histotitle);
  SetHist(hist_Full, xaxislabel , yaxislabel);
  SetHist(hist_Empty, xaxislabel , yaxislabel);
  SetHist(hist_Full_Empty, xaxislabel , yaxislabel);

 PlotUtils::MnvH1D* datahist =new PlotUtils::MnvH1D("adsf", " ", nbins, xmin, xmax);
 bool statPlusSys           = true;
 int mcScale                = 1.;
 bool useHistTitles         = false;



 mnvPlotter.DrawDataMCWithErrorBand(datahist, hist_Full, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);

 char total_title[1024];

 sprintf(total_title, "%s[Full]", histotitle);
 mnvPlotter.AddHistoTitle(total_title, .04);
 mnvPlotter.WritePreliminary("TL", .035, 0, 0, false);
 std::string plotname = Form("%s",pdf_label.c_str());
 mnvPlotter.MultiPrint(&cE, plotname, "pdf");

 std::vector<bool> Print_Vector = Print_Systematics(0);
 mnvPlotter.legend_n_columns = 2;
 cE.Clear();
 // PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);
 PlotErrorSummaryNew(hist_Full, plotname, histotitle, xaxislabel, &cE, &mnvPlotter,true,true);
 mnvPlotter.legend_n_columns = 1;
 cE.Clear();

 mnvPlotter.DrawDataMCWithErrorBand(datahist, hist_Empty, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);
 sprintf(total_title, "%s[Empty]", histotitle);
 mnvPlotter.AddHistoTitle(total_title, .04);
 mnvPlotter.WritePreliminary("TL", .035, 0, 0, false);
 mnvPlotter.MultiPrint(&cE, plotname, "pdf");

 mnvPlotter.legend_n_columns = 2;
 cE.Clear();
 // PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);
 PlotErrorSummaryNew(hist_Empty, plotname, histotitle, xaxislabel, &cE, &mnvPlotter,true,true);
 mnvPlotter.legend_n_columns = 1;



  hist_Full_Empty->Add(hist_Empty,-1);
  mnvPlotter.DrawDataMCWithErrorBand(datahist, hist_Full_Empty, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);

  sprintf(total_title, "%s[F-E]", histotitle);
  mnvPlotter.AddHistoTitle(total_title, .04);
  mnvPlotter.WritePreliminary("TL", .035, 0, 0, false);
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");


  mnvPlotter.legend_n_columns = 2;
  cE.Clear();
  // PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);
  PlotErrorSummaryNew(hist_Full_Empty, plotname, histotitle, xaxislabel, &cE, &mnvPlotter,true,true);
  mnvPlotter.legend_n_columns = 1;


 cE.Closed();


}// End of function



void Draw_RATIO_fromTFiles(TFile *inputFile_Top,  char *histoName_Top, char *histoName_TopLabel ,
  TFile *inputFile_Bottom,  char *histoName_Bottom,char *histoName_BottomLabel, char *histoName_Ratio, std::string pdf_label,
   char *histotitle, char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm )
{
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  TLegend *legend = new TLegend (0.65,0.70,0.95,.88);
  double x1,y1,x2,y2;
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", 6.5, 6., .025);

  std::cout<<"trying to draw Ratio, HisName top  = "<< histoName_Top<<"  HistName Bottom =  "<< histoName_BottomLabel<<std::endl;
  char total_title[1024];
  MnvH1D *Top_hist = (MnvH1D*)inputFile_Top -> Get(histoName_Top);
  auto Top_histcp = (PlotUtils::MnvH1D*)Top_hist->Clone("Top_hist");
  auto Top_histcp1 = (PlotUtils::MnvH1D*)Top_hist->Clone("Top_hist");

  MnvH1D *Bottom_hist = (MnvH1D*)inputFile_Bottom -> Get(histoName_Bottom);
  auto Bottom_histcp = (PlotUtils::MnvH1D*)Bottom_hist->Clone("Bottom_hist");

  double Top_norm_factor =  Bottom_histcp->Integral(0, Bottom_histcp -> GetNbinsX()+1) / Top_histcp->Integral(0, Top_histcp -> GetNbinsX()+1);
  Top_histcp->Scale(Top_norm_factor);
  Top_histcp1->Scale(Top_norm_factor);


//  double Bottom_norm_factor = 1.0 / ;
  //Bottom_histcp->Scale(Bottom_norm_factor);


// normalize both his to 1 then take ratio
  // Draw top and then draw bottom then draw ratio
// settting axis
  SetHist(Top_histcp, xaxislabel , yaxislabel);
  SetHist(Bottom_histcp, xaxislabel , yaxislabel);

  Top_histcp->SetLineColor(kBlue);
  Bottom_histcp->SetLineColor(kRed);

  Top_histcp->SetFillColor(0);
  Top_histcp1->SetFillColor(0);
  Bottom_histcp->SetFillColor(0);
  Top_histcp->SetMaximum(Top_histcp->GetMaximum() * 1.25);
  Top_histcp->SetLineWidth(2);
  Bottom_histcp->SetLineWidth(2);
  if(DoBinwidthNorm==true)  gPad->SetLogx(1);


  Top_histcp->Draw("Hist");
  Bottom_histcp->Draw("Hist SAME");
  legend->AddEntry(Top_histcp, histoName_TopLabel);
  legend->AddEntry(Bottom_histcp, histoName_BottomLabel);
  legend->Draw("SAME");
  sprintf(total_title, "%s", histotitle);
  mnvPlotter.AddHistoTitle(total_title, .04);
  mnvPlotter.WritePreliminary("TL", .035, 0, 0, false);
  std::string plotname1 = Form("%s",pdf_label.c_str());
  mnvPlotter.MultiPrint(&cE, plotname1, "pdf");


  /////


  ////

  Top_histcp1->Divide(Top_histcp1,Bottom_histcp);
  Top_histcp1->GetYaxis()->SetTitle(histoName_Ratio);
  Top_histcp1->SetMaximum(Top_histcp1->GetMaximum() * 1.25);
  Top_histcp1->Draw("Hist");


  sprintf(total_title, "%s [%s] ", histotitle, histoName_Ratio );
  mnvPlotter.AddHistoTitle(total_title, .04);
  mnvPlotter.WritePreliminary("TL", .035, 0, 0, false);
  std::string plotname3 = Form("%s",pdf_label.c_str());
  mnvPlotter.MultiPrint(&cE, plotname3, "pdf");
  cE.Closed();

  if(DoBinwidthNorm==true)  gPad->SetLogx(0);

}



void Draw_RATIO_fromTFiles(TFile *inputFile_Top,  char *histoName_Top, char *histoName_TopLabel ,
  TFile *inputFile_Bottom,  char *histoName_Bottom,char *histoName_BottomLabel, char *histoName_Ratio, std::string pdf_label,
   char *histotitle, char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm, double MinY, double MaxY  )
{
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  TLegend *legend = new TLegend (0.65,0.70,0.95,.88);
  double x1,y1,x2,y2;
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", 6.5, 6., .025);

  std::cout<<"trying to draw Ratio, HisName top  = "<< histoName_Top<<"  HistName Bottom =  "<< histoName_BottomLabel<<std::endl;
  char total_title[1024];
  MnvH1D *Top_hist = (MnvH1D*)inputFile_Top -> Get(histoName_Top);
  auto Top_histcp = (PlotUtils::MnvH1D*)Top_hist->Clone("Top_hist");
  auto Top_histcp1 = (PlotUtils::MnvH1D*)Top_hist->Clone("Top_hist");

  MnvH1D *Bottom_hist = (MnvH1D*)inputFile_Bottom -> Get(histoName_Bottom);
  auto Bottom_histcp = (PlotUtils::MnvH1D*)Bottom_hist->Clone("Bottom_hist");
  auto Bottom_histcp1 = (PlotUtils::MnvH1D*)Bottom_hist->Clone("Bottom_hist");

  double Top_norm_factor =  Bottom_histcp->Integral(0, Bottom_histcp -> GetNbinsX()+1) / Top_histcp->Integral(0, Top_histcp -> GetNbinsX()+1);
  Top_histcp->Scale(Top_norm_factor);
  Top_histcp1->Scale(Top_norm_factor);


//  double Bottom_norm_factor = 1.0 / ;
  //Bottom_histcp->Scale(Bottom_norm_factor);


// normalize both his to 1 then take ratio
  // Draw top and then draw bottom then draw ratio
// settting axis
  SetHist(Top_histcp, xaxislabel , yaxislabel);
  SetHist(Top_histcp1, xaxislabel , yaxislabel);
  SetHist(Bottom_histcp, xaxislabel , yaxislabel);

  Top_histcp->SetLineColor(kBlue);
  Bottom_histcp->SetLineColor(kRed);

  Top_histcp->SetFillColor(0);
  Top_histcp1->SetFillColor(0);
  Bottom_histcp->SetFillColor(0);
  Top_histcp->SetMaximum(Top_histcp->GetMaximum() * 1.25);
  Top_histcp->SetLineWidth(2);
  Bottom_histcp->SetLineWidth(2);
  if(DoBinwidthNorm==true)  gPad->SetLogx(1);


  Top_histcp->Draw("Hist");
  Bottom_histcp->Draw("Hist SAME");
  legend->AddEntry(Top_histcp, histoName_TopLabel);
  legend->AddEntry(Bottom_histcp, histoName_BottomLabel);
  legend->Draw("SAME");
  sprintf(total_title, "%s", histotitle);
  mnvPlotter.AddHistoTitle(total_title, .04);
  mnvPlotter.WritePreliminary("TL", .035, 0, 0, false);
  std::string plotname1 = Form("%s",pdf_label.c_str());
  mnvPlotter.MultiPrint(&cE, plotname1, "pdf");


////////////////
//Drawing Ratio
////////////////

  Top_histcp1->Divide(Top_histcp1,Bottom_histcp1);
  Top_histcp1->GetYaxis()->SetTitle(histoName_Ratio);
  Top_histcp1->SetLineWidth(2);
  Top_histcp1->SetLineColor(kRed);
  Top_histcp1->SetMaximum(MaxY);
  Top_histcp1->SetMinimum(MinY);
  Top_histcp1->Draw("E");


  sprintf(total_title, "%s [%s] ", histotitle, histoName_Ratio );
  mnvPlotter.AddHistoTitle(total_title, .04);
  mnvPlotter.WritePreliminary("TL", .035, 0, 0, false);
  std::string plotname3 = Form("%s",pdf_label.c_str());
  mnvPlotter.MultiPrint(&cE, plotname3, "pdf");
  cE.Closed();

  if(DoBinwidthNorm==true)  gPad->SetLogx(0);

}
/*
void DrawConvolutedGassian_SingleFit(TFile *input_TFile,  char *histoName, char *histoName_Label , std::string pdf_label,
   char *histotitle, char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm,
    double MinY, double MaxY, double FitRange_lowX, double FitRange_highX){

      PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
      TCanvas cE ("c1","c1");
      TLegend *legend = new TLegend (0.65,0.70,0.95,.88);
      double x1,y1,x2,y2;
      mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", 6.5, 6., .025);

      std::cout<<"trying to Fit with Covoluted Gassian; HistName  = "<< histoName<<std::endl;
      std::cout<<"Fit in Range (xlow, xhigh)  = "(<<FitRange_lowX <<","<< FitRange_highX<<")"<<std::endl;
      char total_title[1024];

      MnvH1D *h = (MnvH1D*)input_TFile -> Get(histoName);
      // make a th1D clone of this object
      TH1F *hist = (TH1F*)h->Clone("hist");

      SetHist(hist, xaxislabel , yaxislabel);





      hist->Fit("f");
      hist->Draw("EP");


      legend->Draw("SAME");
      sprintf(total_title, "%s", histotitle);
      mnvPlotter.AddHistoTitle(total_title, .04);
      mnvPlotter.WritePreliminary("TL", .035, 0, 0, false);
      std::string plotname1 = Form("%s",pdf_label.c_str());
      mnvPlotter.MultiPrint(&cE, plotname1, "pdf");



}//end of function
*/
void MakeCVS_from_hist(TFile *input_TFile,  char *histoName, char *histoName_Label ){

  MnvH1D *h = (MnvH1D*)input_TFile -> Get(histoName);
  h->MnvH1DToCSV(histoName_Label);

  return;

}//end of function


void MakeCVS_from_HISTS(char *histoName_TRUTH, TFile *inputFile_MCinputFULL, TFile *inputFile_MCinputEmpty, char *histoName_MC,
  TFile *inputFile_DatainputFULL, TFile *inputFile_DatainputEmpty,char *histoName_data,
  char *Playlist_name_FULL, char *Playlist_name_EMPTY, char *File_Title, char *varibleName, Pot_MapStatusList POT_DATA, Pot_MapStatusList POT_MC ){

    double scale_to_FULL= POT_DATA[kFULL] / POT_DATA[kEMPTY];

    double MC_scale_to_FULL = POT_DATA[kFULL] / POT_MC[kFULL];

    double MC_EMPTYscale_to_FULL = POT_DATA[kFULL] / POT_MC[kEMPTY];


    MnvH1D *hist_FULL = (MnvH1D*)inputFile_DatainputFULL -> Get(histoName_data);
    std::cout<<"Finished Full  = "<<histoName_data<<std::endl;

    MnvH1D *hist_EMPTY = (MnvH1D*)inputFile_DatainputEmpty -> Get(histoName_data);
    std::cout<<"Finished Full  = "<<histoName_data<<std::endl;


    auto hist_FULL_EMPTY = (PlotUtils::MnvH1D*)hist_FULL->Clone("hist_FULL");
    auto hist_COPYEMPTY = (PlotUtils::MnvH1D*)hist_EMPTY->Clone("hist_EMPTY");
    std::cout<<"Made Clones for DATA "<<histoName_data<<std::endl;
    ////////////////////
    ////SCALING DATA////
    ////////////////////

    hist_EMPTY->Scale(scale_to_FULL);
    hist_COPYEMPTY->Scale(scale_to_FULL);
    hist_FULL_EMPTY->Add(hist_COPYEMPTY,-1);
    // GETTING RECO
    MnvH1D *histMC_FULL = (MnvH1D*)inputFile_MCinputFULL->Get(histoName_MC);
    std::cout<<"Got Hist Full MC   = "<<histoName_MC<<std::endl;
    MnvH1D *histMC_EMPTY = (MnvH1D*)inputFile_MCinputEmpty->Get(histoName_MC);
      std::cout<<"Got Hist EMPTY MC   = "<<histoName_MC<<std::endl;
    auto histMC_FULL_EMPTY = (PlotUtils::MnvH1D*)histMC_FULL->Clone("histMC_FULL");
    auto histMC_COPYEMPTY = (PlotUtils::MnvH1D*)histMC_EMPTY->Clone("histMC_EMPTY");

    // SCALING RECO
    histMC_FULL->Scale(MC_scale_to_FULL);
    histMC_FULL_EMPTY->Scale(MC_scale_to_FULL);
    histMC_EMPTY->Scale(MC_EMPTYscale_to_FULL);
    histMC_COPYEMPTY->Scale(MC_EMPTYscale_to_FULL);
    histMC_FULL_EMPTY->Add(histMC_COPYEMPTY,-1);
    //

    // TRUTH
    MnvH1D *histTRUTH_FULL = (MnvH1D*)inputFile_MCinputFULL->Get(histoName_TRUTH);
    std::cout<<"Got Hist FULL TRUTH MC   = "<<histoName_TRUTH<<std::endl;
    MnvH1D *histTRUTH_EMPTY = (MnvH1D*)inputFile_MCinputEmpty->Get(histoName_TRUTH);
      std::cout<<"Got Hist EMPTY  TRUTH MC   = "<<histoName_TRUTH<<std::endl;
    auto histTRUTH_FULL_EMPTY = (PlotUtils::MnvH1D*)histTRUTH_FULL->Clone("histTRUTH_FULL");
    auto histTRUTH_COPYEMPTY = (PlotUtils::MnvH1D*)histTRUTH_EMPTY->Clone("histTRUTH_EMPTY");
    // SCALLING TRUTH
    std::cout<<"Cloned TRUTH MC Hist for FUll - Empty    = "<<histoName_TRUTH<<std::endl;


    histTRUTH_FULL->Scale(MC_scale_to_FULL);
    histTRUTH_FULL_EMPTY->Scale(MC_scale_to_FULL);
    histTRUTH_EMPTY->Scale(MC_EMPTYscale_to_FULL);
    histTRUTH_COPYEMPTY->Scale(MC_EMPTYscale_to_FULL);
    histTRUTH_FULL_EMPTY->Add(histTRUTH_COPYEMPTY,-1);


    std::ofstream myfile;
    char CVS_title[1024];
    sprintf(CVS_title , "%s.cvs",File_Title );
    myfile.open(CVS_title);

    myfile<<"#Varible "<< varibleName << "\n";

    int nbins_x= hist_FULL->GetNbinsX();
    int totalbins=(nbins_x+2);

    myfile<<"Number of Bins,  " <<totalbins<< "\n" ;

    /*
    for (int i=0;i<totalbins;i++)
    {

    myfile<<hist_FULL->GetBin(i)<<",";

  }
  */

    myfile<<"\n";

    myfile<<"Bin Centers = [ ";

    for (int i=0;i<totalbins;i++)
    {
      if(i < totalbins - 1 ){
      myfile<<hist_FULL->GetBinCenter(i)<<", ";
    }
    else{
      myfile<<hist_FULL->GetBinCenter(i);
    }


    }

    myfile<<" ]\n";



    myfile<<"FullData = [";
    for (int i=0;i<totalbins;i++)
    {
      if(i < totalbins - 1 ){
        myfile<<hist_FULL->GetBinContent(i)<<", ";
      }

      else{myfile<<hist_FULL->GetBinContent(i);
      }
    }

    myfile<<"]\n";


    myfile<<"EmptyData = [ ";
    for (int i=0;i<totalbins;i++)
    {
      if(i < totalbins - 1 ){
        myfile<<hist_EMPTY->GetBinContent(i)<<", ";
      }
      else{
        myfile<<hist_EMPTY->GetBinContent(i);

      }

    }

    myfile<<" ]\n";

    myfile<<"Full_EmptyData = [ ";
    for (int i=0;i<totalbins;i++)
    {
      if(i < totalbins - 1 ){
        myfile<<hist_FULL_EMPTY->GetBinContent(i)<<", ";
      }
      else {
        myfile<<hist_FULL_EMPTY->GetBinContent(i);
      }



    }

    myfile<<"]\n";

///////////////////////////////////////////////////////MC
    myfile<<"FullMC = [ ";
    for (int i=0;i<totalbins;i++)
    {
      if(i < totalbins - 1 ){
      myfile<<histMC_FULL->GetBinContent(i)<<", ";
    }
    else{
      myfile<<histMC_FULL->GetBinContent(i);
    }



    }

    myfile<<"] \n";


    myfile<<"EmptyMC = [";
    for (int i=0;i<totalbins;i++)
    {
      if(i < totalbins - 1 ){
        myfile<<histMC_EMPTY->GetBinContent(i)<<", ";
      }
      else {
        myfile<<histMC_EMPTY->GetBinContent(i);
      }


    }

    myfile<<"]\n";

    myfile<<"Full_EmptyMC = [  ";
    for (int i=0;i<totalbins;i++)
    {
      if(i < totalbins - 1 ){
        myfile<<histMC_FULL_EMPTY->GetBinContent(i)<<", ";
      }
      else{
        myfile<<histMC_FULL_EMPTY->GetBinContent(i);
      }



    }

    myfile<<"]\n";

    ///////////////////////////////////////////////////////TRUTH
        myfile<<"FullTruth = [";
        for (int i=0;i<totalbins;i++)
        {
          if(i < totalbins - 1 ){
            myfile<<histTRUTH_FULL->GetBinContent(i)<<", ";
          }
          else{
            myfile<<histTRUTH_FULL->GetBinContent(i);
          }


        }

        myfile<<"] \n";


        myfile<<"EmptyTruth = [ ";
        for (int i=0;i<totalbins;i++)
        {
          if(i < totalbins - 1 ){
          myfile<<histTRUTH_EMPTY->GetBinContent(i)<<", ";
        }
        else{
          myfile<<histTRUTH_EMPTY->GetBinContent(i);
        }



        }

        myfile<<"] \n";

        myfile<<"Full_EmptyTruth = [ ";
        for (int i=0;i<totalbins;i++)
        {
          if(i < totalbins - 1 ){
            myfile<<histTRUTH_FULL_EMPTY->GetBinContent(i)<<", ";
          }
          else{
            myfile<<histTRUTH_FULL_EMPTY->GetBinContent(i);
          }


        }

        myfile<<"] \n";


        myfile.close();
}//end of function




void DrawFULLStat_CV_SystematicErr( ME_playlist_TFileMAP FullMCMap,     Pot_MapList FullMC_scalerMap,
                                    ME_playlist_TFileMAP EmptyMCMap,   Pot_MapList EmptyMC_scalerMap,
                                    ME_playlist_TFileMAP FullDataMap,  Pot_MapList FullData_scalerMap,
                                    ME_playlist_TFileMAP EmptyDataMap, Pot_MapList EmptyData_scalerMap,
   char *histoName_MC ,char *histoName_data, std::string units, std::string pdf_label, char* hist_title,
   char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG, bool MakeYaxisLOG, bool DrawallErrorGroups
 )
{
 PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);

 Playlist_MnvH1D_Map FULLMC_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullMCMap, histoName_MC );
 Playlist_MnvH1D_Map FULLData_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullDataMap, histoName_data );

 Playlist_MnvH1D_Map FULLMC_HistMAPScaled =  Scale_MnvH1D_Map_usingPot_MapList(FULLMC_HistMAP , FullMC_scalerMap , histoName_MC  );
 Playlist_MnvH1D_Map FULLData_HistMAPScaled =  Scale_MnvH1D_Map_usingPot_MapList(FULLData_HistMAP , FullData_scalerMap , histoName_data  );

 Playlist_MnvH1D_Map EmptyMC_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(EmptyMCMap, histoName_MC );
 Playlist_MnvH1D_Map EmptyData_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(EmptyDataMap, histoName_data );

 Playlist_MnvH1D_Map EmptyMC_HistMAPScaled =  Scale_MnvH1D_Map_usingPot_MapList(EmptyMC_HistMAP , EmptyMC_scalerMap , histoName_MC  );
 Playlist_MnvH1D_Map EmptyData_HistMAPScaled =  Scale_MnvH1D_Map_usingPot_MapList(EmptyData_HistMAP , EmptyData_scalerMap , histoName_data  );


typename std::map<ME_helium_Playlists, PlotUtils::MnvH1D*>::const_iterator catMC;
typename std::map<ME_helium_Playlists, PlotUtils::MnvH1D*>::const_iterator dogData;

for (catMC = FULLMC_HistMAPScaled.begin(), dogData = FULLData_HistMAPScaled.begin(); catMC != FULLMC_HistMAPScaled.end(); ++catMC, ++dogData)
{
  std::string Playlist_Name = GetPlaylist_InitialName(catMC->first);
  char Playlist_Name_char[Playlist_Name.length()+1];
  strcpy(Playlist_Name_char,Playlist_Name.c_str());

  std::string HeliumStatus_name = GetPlaylistStatusString(GetPlaylist_HeliumStatus(catMC->first));
  char HeliumStatus_name_char[HeliumStatus_name.length()+1];
  strcpy(HeliumStatus_name_char,HeliumStatus_name.c_str());

char playlist_title[1024];
sprintf(playlist_title, "%s(%s)",Playlist_Name_char,HeliumStatus_name_char);


 Draw_DataWITHMC_SingleHistinput_withRatio(catMC->second, dogData->second,
  playlist_title, pdf_label, hist_title, units,
  xaxislabel,  yaxislabel, DoBinwidthNorm, MakeXaxisLOG,MakeYaxisLOG, DrawallErrorGroups);
}

for (catMC = EmptyMC_HistMAPScaled.begin(), dogData = EmptyData_HistMAPScaled.begin(); catMC != EmptyMC_HistMAPScaled.end(); ++catMC, ++dogData)
{
  std::string Playlist_Name = GetPlaylist_InitialName(catMC->first);
  char Playlist_Name_char[Playlist_Name.length()+1];
  strcpy(Playlist_Name_char,Playlist_Name.c_str());

  std::string HeliumStatus_name = GetPlaylistStatusString(GetPlaylist_HeliumStatus(catMC->first));
  char HeliumStatus_name_char[HeliumStatus_name.length()+1];
  strcpy(HeliumStatus_name_char,HeliumStatus_name.c_str());

char playlist_title[1024];
sprintf(playlist_title, "%s(%s)",Playlist_Name_char,HeliumStatus_name_char);


 Draw_DataWITHMC_SingleHistinput_withRatio(catMC->second, dogData->second,
  playlist_title, pdf_label, hist_title, units,
  xaxislabel,  yaxislabel, DoBinwidthNorm, MakeXaxisLOG,MakeYaxisLOG, DrawallErrorGroups);
}
}//end of function

void DrawFULLStat_CV_SystematicErr( ME_playlist_TFileMAP FullMCMap,    Pot_MapList FullMC_scalerMap,
                                    ME_playlist_TFileMAP EmptyMCMap,   Pot_MapList EmptyMC_scalerMap,
   char *histoName_MC, std::string pdf_label, char* hist_title,
   char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG
 )
{
 PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);

 Playlist_MnvH1D_Map FULLMC_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullMCMap, histoName_MC );

 Playlist_MnvH1D_Map FULLMC_HistMAPScaled =  Scale_MnvH1D_Map_usingPot_MapList(FULLMC_HistMAP , FullMC_scalerMap , histoName_MC  );

 Playlist_MnvH1D_Map EmptyMC_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(EmptyMCMap, histoName_MC );

 Playlist_MnvH1D_Map EmptyMC_HistMAPScaled =  Scale_MnvH1D_Map_usingPot_MapList(EmptyMC_HistMAP , EmptyMC_scalerMap , histoName_MC  );


typename std::map<ME_helium_Playlists, PlotUtils::MnvH1D*>::const_iterator catMC;
std::string xaxislabel_string(xaxislabel);
std::string yaxislabel_string(yaxislabel);

for (catMC = FULLMC_HistMAPScaled.begin(); catMC != FULLMC_HistMAPScaled.end(); ++catMC)
{
  std::string Playlist_Name = GetPlaylist_InitialName(catMC->first);
  char Playlist_Name_char[Playlist_Name.length()+1];
  strcpy(Playlist_Name_char,Playlist_Name.c_str());

  std::string HeliumStatus_name = GetPlaylistStatusString(GetPlaylist_HeliumStatus(catMC->first));
  char HeliumStatus_name_char[HeliumStatus_name.length()+1];
  strcpy(HeliumStatus_name_char,HeliumStatus_name.c_str());

char playlist_title[1024];
sprintf(playlist_title, "%s(%s)",Playlist_Name_char,HeliumStatus_name_char);

DrawCVAndError_FromHistPointer(catMC->second, playlist_title, xaxislabel_string, yaxislabel_string,
  pdf_label, DoBinwidthNorm, MakeXaxisLOG);

}

for (catMC = EmptyMC_HistMAPScaled.begin(); catMC != EmptyMC_HistMAPScaled.end(); ++catMC)
{
  std::string Playlist_Name = GetPlaylist_InitialName(catMC->first);
  char Playlist_Name_char[Playlist_Name.length()+1];
  strcpy(Playlist_Name_char,Playlist_Name.c_str());

  std::string HeliumStatus_name = GetPlaylistStatusString(GetPlaylist_HeliumStatus(catMC->first));
  char HeliumStatus_name_char[HeliumStatus_name.length()+1];
  strcpy(HeliumStatus_name_char,HeliumStatus_name.c_str());

char playlist_title[1024];
sprintf(playlist_title, "%s(%s)",Playlist_Name_char,HeliumStatus_name_char);

DrawCVAndError_FromHistPointer(catMC->second, playlist_title, xaxislabel_string, yaxislabel_string,
  pdf_label, DoBinwidthNorm, MakeXaxisLOG);

}

}//end of function



void DrawFULLStatCOMBINED_CV_SystematicErr(ME_playlist_TFileMAP FullMCMap, Pot_MapList FullMC_POTMap,
                                    ME_playlist_TFileMAP EmptyMCMap,       Pot_MapList EmptyMC_POTMap,
                                    ME_playlist_TFileMAP FullDataMap,      Pot_MapList FullData_POTMap,
                                    ME_playlist_TFileMAP EmptyDataMap,     Pot_MapList EmptyData_POTMap,
   char *histoName_MC ,char *histoName_data, std::string units, std::string pdf_label, char* hist_title,
   char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG,bool DrawallErrorGroups
 )
{
 PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);

 Playlist_MnvH1D_Map FULLMC_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullMCMap, histoName_MC );
 Playlist_MnvH1D_Map FULLData_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullDataMap, histoName_data );

 Playlist_MnvH1D_Map EmptyMC_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(EmptyMCMap, histoName_MC );
 Playlist_MnvH1D_Map EmptyData_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(EmptyDataMap, histoName_data );


 Pot_MapStatusList POTMAP_TOTAL =  Constuct_TOTALPOT_cryostatusMap(FullMC_POTMap, EmptyMC_POTMap, FullData_POTMap, EmptyData_POTMap);



 print_POT_ME_helium_Status(POTMAP_TOTAL);

 //PrintPot_MapList(POTMAP_TOTAL, "POTMAP totl inside funcition"  );



 Pot_MapStatusList POTMAP_TOTAL_scaler = MakeScaler_TOTALPOT_cryostatusMapTOFULLDATA(POTMAP_TOTAL);


 print_POT_ME_helium_Status(POTMAP_TOTAL_scaler);

 //PrintPot_MapList(POTMAP_TOTAL_scaler, "POTMAP scaler total inside funcition"  );

/////////////////////////////////
/// Combined kMC_FULL, kMC_EMPTY, kDATA_FULL, kDATA_EMPTY
/////////////////////////////////
auto FULL_MC_Hist = Combine_Hists_fromMAP(FULLMC_HistMAP , kME1F ,"FULL_MC_Hist");
auto FULL_Data_Hist = Combine_Hists_fromMAP(FULLData_HistMAP , kME1F ,"FULL_Data_Hist");



auto FULL_EmptyMC_Hist =(MnvH1D*) FULL_MC_Hist->Clone("FULL_EmptyMC_Hist");
auto FULL_EmptyData_Hist =(MnvH1D*) FULL_Data_Hist->Clone("FULL_EmptyData_Hist");

FULL_MC_Hist->Scale(POTMAP_TOTAL_scaler[kMC_FULL]);
FULL_EmptyMC_Hist->Scale(POTMAP_TOTAL_scaler[kMC_FULL]);

std::cout<< " POTMAP_TOTAL_scaler[kMC_FULL] = "<< POTMAP_TOTAL_scaler[kMC_FULL]<< std::endl;



char playlist_title_FULL[1024];
sprintf(playlist_title_FULL, "CombinedFull");
Draw_DataWITHMC_SingleHistinput_withRatio(FULL_MC_Hist, FULL_Data_Hist, playlist_title_FULL, pdf_label, hist_title, units,
 xaxislabel,  yaxislabel, DoBinwidthNorm, MakeXaxisLOG, POTMAP_TOTAL[kDATA_FULL], POTMAP_TOTAL[kMC_FULL], DrawallErrorGroups);

auto Empty_MC_Hist = Combine_Hists_fromMAP(EmptyMC_HistMAP , kME1M ,"Empty_MC_Hist");
auto Empty_MC_Hist_clone =(MnvH1D*) Empty_MC_Hist->Clone("Empty_MC_Hist_clone");

auto Empty_Data_Hist = Combine_Hists_fromMAP(EmptyData_HistMAP , kME1M ,"Empty_Data_Hist");
auto Empty_Data_Hist_clone =(MnvH1D*) Empty_Data_Hist->Clone("Empty_Data_Hist_clone");


Empty_MC_Hist->Scale(POTMAP_TOTAL_scaler[kMC_EMPTY]);
Empty_Data_Hist->Scale(POTMAP_TOTAL_scaler[kDATA_EMPTY]);
Empty_MC_Hist_clone->Scale(POTMAP_TOTAL_scaler[kMC_EMPTY]);
Empty_Data_Hist_clone->Scale(POTMAP_TOTAL_scaler[kDATA_EMPTY]);



char playlist_title_Empty[1024];
sprintf(playlist_title_Empty, "CombinedEmpty");
Draw_DataWITHMC_SingleHistinput_withRatio(Empty_MC_Hist, Empty_Data_Hist, playlist_title_Empty, pdf_label, hist_title, units,
 xaxislabel,  yaxislabel, DoBinwidthNorm, MakeXaxisLOG, POTMAP_TOTAL[kDATA_FULL], POTMAP_TOTAL[kMC_EMPTY], DrawallErrorGroups);

FULL_EmptyMC_Hist->Add(Empty_MC_Hist_clone,-1);
FULL_EmptyData_Hist->Add(Empty_Data_Hist_clone,-1);
 sprintf(playlist_title_FULL, "Combined(F-E)");
 Draw_DataWITHMC_SingleHistinput_withRatio(FULL_EmptyMC_Hist, FULL_EmptyData_Hist, playlist_title_FULL, pdf_label, hist_title, units,
  xaxislabel,  yaxislabel, DoBinwidthNorm, MakeXaxisLOG,POTMAP_TOTAL[kDATA_FULL],POTMAP_TOTAL[kMC_FULL], DrawallErrorGroups);

}//end of function


void DrawFULLStatCOMBINED_CV_SystematicErr(ME_playlist_TFileMAP FullMCMap,  Pot_MapList FullMC_POTMap, Pot_MapList FullData_POTMap,
                                           ME_playlist_TFileMAP EmptyMCMap, Pot_MapList EmptyMC_POTMap, Pot_MapList EmptyData_POTMap,
   char *histoName_MC ,  std::string pdf_label, char* hist_title,
   char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG
 )
{
 PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);

 Playlist_MnvH1D_Map FULLMC_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullMCMap, histoName_MC );
 Playlist_MnvH1D_Map EmptyMC_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(EmptyMCMap, histoName_MC );

 Pot_MapStatusList POTMAP_TOTAL =  Constuct_TOTALPOT_cryostatusMap(FullMC_POTMap, EmptyMC_POTMap, FullData_POTMap, EmptyData_POTMap);

 print_POT_ME_helium_Status(POTMAP_TOTAL);

 Pot_MapStatusList POTMAP_TOTAL_scaler = MakeScaler_TOTALPOT_cryostatusMapTOFULLDATA(POTMAP_TOTAL);


 print_POT_ME_helium_Status(POTMAP_TOTAL_scaler);

 //PrintPot_MapList(POTMAP_TOTAL_scaler, "POTMAP scaler total inside funcition"  );

/////////////////////////////////
/// Combined kMC_FULL, kMC_EMPTY, kDATA_FULL, kDATA_EMPTY
/////////////////////////////////
auto FULL_MC_Hist = Combine_Hists_fromMAP(FULLMC_HistMAP , kME1F ,"FULL_MC_Hist");


FULL_MC_Hist->Scale(POTMAP_TOTAL_scaler[kMC_FULL]);

auto FULL_EmptyMC_Hist =(MnvH1D*) FULL_MC_Hist->Clone("FULL_EmptyMC_Hist");
//FULL_EmptyMC_Hist->Scale(POTMAP_TOTAL_scaler[kMC_FULL]);

std::cout<< " POTMAP_TOTAL_scaler[kMC_FULL] = "<< POTMAP_TOTAL_scaler[kMC_FULL]<< std::endl;
std::string xaxislabel_string(xaxislabel);
std::string yaxislabel_string(yaxislabel);


char playlist_title_FULL[1024];
sprintf(playlist_title_FULL, "CombinedFull");

DrawCVAndError_FromHistPointer(FULL_MC_Hist, playlist_title_FULL, xaxislabel_string, yaxislabel_string,
  pdf_label, DoBinwidthNorm, MakeXaxisLOG);

auto Empty_MC_Hist = Combine_Hists_fromMAP(EmptyMC_HistMAP , kME1M ,"Empty_MC_Hist");
auto Empty_MC_Hist_clone =(MnvH1D*) Empty_MC_Hist->Clone("Empty_MC_Hist_clone");


Empty_MC_Hist->Scale(POTMAP_TOTAL_scaler[kMC_EMPTY]);
Empty_MC_Hist_clone->Scale(POTMAP_TOTAL_scaler[kMC_EMPTY]);


char playlist_title_Empty[1024];
sprintf(playlist_title_Empty, "CombinedEmpty");

 DrawCVAndError_FromHistPointer(Empty_MC_Hist, playlist_title_Empty, xaxislabel_string, yaxislabel_string,
   pdf_label, DoBinwidthNorm, MakeXaxisLOG);

FULL_EmptyMC_Hist->Add(Empty_MC_Hist_clone,-1);

 sprintf(playlist_title_FULL, "Combined(F-E)");

 DrawCVAndError_FromHistPointer(FULL_MC_Hist, playlist_title_FULL, xaxislabel_string, yaxislabel_string,
   pdf_label, DoBinwidthNorm, MakeXaxisLOG);

}//end of function



void DrawSTACKfromHistFilio_FULLStats(ME_playlist_TFileMAP FullMCMap, Pot_MapList FullMC_scalerMap,
                                     ME_playlist_TFileMAP EmptyMCMap,  Pot_MapList EmptyMC_scalerMap,
                                     ME_playlist_TFileMAP FullDataMap, Pot_MapList FullData_scalerMap,
                                     ME_playlist_TFileMAP EmptyDataMap, Pot_MapList EmptyData_scalerMap,
                                    char *histoName_MC , char *histoName_Data, char *histotitle,
  std::string xaxislabel, std::string pdf_label, bool DoBinwidthNorm, std::string units, StackType STACKTYPE, bool Debug )
  {    //helium_Status kEMPTY, kFULL;
    PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
    //PlotUtils::MnvPlotter mnvPlotter();
    mnvPlotter.legend_n_columns = 2;

    TCanvas cE ("c1","c1");
    std::cout<<"trying MC HisName = "<< histoName_MC<<std::endl;
    std::cout<<"trying data HisName = "<< histoName_Data<<std::endl;

    char Stack_Name[1024];
    if(STACKTYPE==kMaterial){sprintf(Stack_Name, "%s_Material",histoName_MC);}
    else if(STACKTYPE==kInteraction){ sprintf(Stack_Name, "%s_Interaction",histoName_MC);}
    else if(STACKTYPE==kParticle){ sprintf(Stack_Name, "%s_Particle",histoName_MC);
    mnvPlotter.legend_n_columns = 3;}
    else if(STACKTYPE==kCryoTankRegions){sprintf(Stack_Name, "%s_CryoRegion",histoName_MC);}
    else{std::cout<<"Error unknown stack type: Ploting Failed"<<std::endl; return;}

    if(Debug == true){std::cout << "Making HistFolio_PlaylistMap using name: "<< Stack_Name <<std::endl;}
    Playlist_HistFolio_MnvH1D_Map HistFolio_PlaylistMap_Full =  Constuct_HistFolio_mvnH1DMap_FromME_playlist_TFileMAP(FullMCMap, Stack_Name );
    Playlist_HistFolio_MnvH1D_Map HistFolio_PlaylistMap_Empty =  Constuct_HistFolio_mvnH1DMap_FromME_playlist_TFileMAP(EmptyMCMap, Stack_Name );
    //Playlist_HistFolio_MnvH1D_Map HistFolio_PlaylistMap_Full_clone =  Constuct_HistFolio_mvnH1DMap_FromME_playlist_TFileMAP(FullMCMap, Stack_Name );
    //Playlist_HistFolio_MnvH1D_Map HistFolio_PlaylistMap_Empty_clone =  Constuct_HistFolio_mvnH1DMap_FromME_playlist_TFileMAP(EmptyMCMap, Stack_Name );

    if(Debug == true){std::cout << "Initialize Got FUll Data for Stacks   "<< Stack_Name<<std::endl;}
    Playlist_MnvH1D_Map FULLData_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullDataMap, histoName_Data );
    Playlist_MnvH1D_Map FULLData_HistMAPScaled =  Scale_MnvH1D_Map_usingPot_MapList(FULLData_HistMAP , FullData_scalerMap , histoName_Data  );
    if(Debug == true){std::cout << "Initialize Got Empty Data for Stacks   "<< Stack_Name<<std::endl;}
    Playlist_MnvH1D_Map EmptyData_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(EmptyDataMap, histoName_Data );
    Playlist_MnvH1D_Map EmptyData_HistMAPScaled =  Scale_MnvH1D_Map_usingPot_MapList(EmptyData_HistMAP , EmptyData_scalerMap , histoName_Data  );





    std::vector<int> Helium9_colorScheme = {
      TColor::GetColor("#EEFF00"), // neonyellow,
      TColor::GetColor("#DF00FF"), //'psychedelic Purple
      TColor::GetColor("#ffc922"), //'sunset yellow'
      TColor::GetColor("#87CEEB"),//'skyblue'
      TColor::GetColor("#0859C6"), //blue
      TColor::GetColor("#654522"), // yellowishbrown,
      TColor::GetColor(43, 206,  72 ), //green
      TColor::GetColor("#FF0800"),//2 candy Apple
      TColor::GetColor("#90AD1C"),
      TColor::GetColor("#BABABA"), //Gray
      TColor::GetColor("#00FFFF"),//'aqua'
      TColor::GetColor("#F1B6DA"),//pink
      TColor::GetColor("#00A86B"),//'Jade'
      TColor::GetColor("#FAFAD2"),  // LightGoldenRodYellow
      TColor::GetColor("#800000"),  // Maroon
      TColor::GetColor("#555555"),  // dark grey
      TColor::GetColor(0, 153, 143 ), //turquoise
      TColor::GetColor("#654522"), // yellowishbrown,
      TColor::GetColor("#8db600"), // yellowgreen,
      TColor::GetColor("#D3D3D3"),  //'lightgrey'
       TColor::GetColor("#90AD1C"),
       TColor::GetColor("#CCDDAA")
    };



// Check if objects are same size and have playlists

if( CompareMap_ME_helium_PlaylistsKeys(HistFolio_PlaylistMap_Full,  FullMC_scalerMap) == false ){assert(false && "HistFolio_PlaylistMap_Full and FullMC_scalerMap have different Keys " );}
if( CompareMap_ME_helium_PlaylistsKeys(HistFolio_PlaylistMap_Full,  FULLData_HistMAPScaled) == false ){assert(false && "HistFolio_PlaylistMap_Full and FULLData_HistMAPScaled have different Keys " );}
//if( CompareMap_ME_helium_PlaylistsKeys(HistFolio_PlaylistMap_Full,  HistFolio_PlaylistMap_Full_clone) == false ){assert(false && "HistFolio_PlaylistMap_Full and HistFolio_PlaylistMap_Full_clone have different Keys " );}

double x1,x2,y1,y2;
mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", .5, 10, .025);
//TLegend *legend = new TLegend(x1 - .05, y1 + .1, x2 + .05, y2 + .1);
TLegend *legend = new TLegend(x1 - .02, y1+.31 , x2 +.06 , y2 + .42  );
legend->SetNColumns(1);
legend->SetTextSize(.03);
legend->SetFillColor(0);


typename std::map<ME_helium_Playlists, PlotUtils::HistFolio<PlotUtils::MnvH1D>>::const_iterator HistFoliocat;
//typename std::map<ME_helium_Playlists, PlotUtils::HistFolio<PlotUtils::MnvH1D>>::const_iterator HistFoliobird;
typename std::map<ME_helium_Playlists, PlotUtils::MnvH1D*>::const_iterator dogData;
typename std::map<ME_helium_Playlists, double>::const_iterator Scalecat;

  for(HistFoliocat = HistFolio_PlaylistMap_Full.begin(), dogData = FULLData_HistMAPScaled.begin(), Scalecat = FullMC_scalerMap.begin(); HistFoliocat != HistFolio_PlaylistMap_Full.end(); ++HistFoliocat, ++dogData, ++Scalecat)
  {

    auto Full_MC_Stack_array = (HistFoliocat->second).GetHistArray();
    auto Full_Empty_MC_Stack_array = (HistFoliocat->second).GetHistArray();

    if(Scalecat->first != HistFoliocat->first){assert(false && "FAILED Scalecat->first != HistFoliocat->first" );}
    //if(Scalecat->first != HistFoliobird->first){assert(false && "FAILED Scalecat->first != HistFoliobird->first" );}

    Scale_MnvH1D_Array(Full_MC_Stack_array , Scalecat->second);

    char ytitle[100];
    char units_char[units.length()+1];
    strcpy(units_char,units.c_str());
    double binwidth_title = (dogData->second)->GetBinWidth(3);

    std::string Playlist_Name = GetPlaylist_InitialName(HistFoliocat->first);
    char Playlist_Name_char[Playlist_Name.length()+1];
    strcpy(Playlist_Name_char,Playlist_Name.c_str());

    std::string HeliumStatus_name = GetPlaylistStatusString(GetPlaylist_HeliumStatus(HistFoliocat->first));
    char HeliumStatus_name_char[HeliumStatus_name.length()+1];
    strcpy(HeliumStatus_name_char,HeliumStatus_name.c_str());

    if(DoBinwidthNorm==true){
      //(dogData->second)->Scale(1.0,"width");
      //BinWidthNorm_MnvH1D_Array(Full_MC_Stack_array);
      sprintf(ytitle, "Number of Events / %.2f %s", binwidth_title, units_char);
    }
    else{
      sprintf(ytitle, "Number of Events");

    }
        mnvPlotter.draw_normalized_to_bin_width=DoBinwidthNorm;
    mnvPlotter.DrawDataStackedMC((dogData->second), &Full_MC_Stack_array, 1.0, "TR", "Data", -1, -1,
    1001, xaxislabel.c_str(), ytitle, false);

    char total_title[1024];
    sprintf(total_title, "Stack %s [%s(%s)]", histotitle, Playlist_Name_char, HeliumStatus_name_char);

    mnvPlotter.AddHistoTitle(total_title, .04);
    mnvPlotter.WritePreliminary("TL", .035, 0, 0, false);
    std::string plotname = Form("%s",pdf_label.c_str());
    mnvPlotter.MultiPrint(&cE, plotname, "pdf");

  }//end of Loop
  /////////////////////////////////////
  // Empty
  ////////////////////////////////////////////////////////////////
  if( CompareMap_ME_helium_PlaylistsKeys(HistFolio_PlaylistMap_Empty,  EmptyMC_scalerMap) == false ){assert(false && "HistFolio_PlaylistMap_Empty and EmptyMC_scalerMap have different Keys " );}
  if( CompareMap_ME_helium_PlaylistsKeys(HistFolio_PlaylistMap_Empty,  EmptyData_HistMAPScaled) == false ){assert(false && "HistFolio_PlaylistMap_Empty and EmptyData_HistMAPScaled have different Keys " );}
  //auto  Empty_Stats_MC_Stack_Array = ((HistFolio_PlaylistMap_Empty.begin())->second).GetHistArray();
  //const TObjArray Empty_Stats_MC_Stack_Array_clone = (TObjArray)Empty_Stats_MC_Stack_Array.Clone();
  //TObjArray*  Empty_Stats_MC_Stack_Array = (TObjArray*)(*(((HistFolio_PlaylistMap_Empty.begin())->second).GetHistArray())).Clone();


  for(HistFoliocat = HistFolio_PlaylistMap_Empty.begin(), dogData = EmptyData_HistMAPScaled.begin(), Scalecat = EmptyMC_scalerMap.begin() ; HistFoliocat != HistFolio_PlaylistMap_Empty.end(); ++HistFoliocat, ++dogData, ++Scalecat)
  {

  //  (HistFoliocat->second).ApplyColorPalette(Helium9_colorScheme);
    auto Empty_MC_Stack_array = (HistFoliocat->second).GetHistArray();

    if(Scalecat->first != HistFoliocat->first){assert(false && "FAILED Scalecat->first != HistFoliocat->first" );}
    Scale_MnvH1D_Array(Empty_MC_Stack_array , Scalecat->second);

/*
    if(HistFoliocat == HistFolio_PlaylistMap_Empty.begin())
    {
      Scale_MnvH1D_Array(Empty_Stats_MC_Stack_Array_clone , Scalecat->second);
    }
    else
    {
      AddFirst_toSecond_MnvH1D_Arrays(Empty_Stats_MC_Stack_Array_clone , Empty_MC_Stack_array);
    }
*/

    char ytitle[100];
    char units_char[units.length()+1];
    strcpy(units_char,units.c_str());
    double binwidth_title = (dogData->second)->GetBinWidth(3);

    std::string Playlist_Name = GetPlaylist_InitialName(HistFoliocat->first);
    char Playlist_Name_char[Playlist_Name.length()+1];
    strcpy(Playlist_Name_char,Playlist_Name.c_str());

    std::string HeliumStatus_name = GetPlaylistStatusString(GetPlaylist_HeliumStatus(HistFoliocat->first));
    char HeliumStatus_name_char[HeliumStatus_name.length()+1];
    strcpy(HeliumStatus_name_char,HeliumStatus_name.c_str());

    if(DoBinwidthNorm==true){
      //(dogData->second)->Scale(1.0,"width");
      //BinWidthNorm_MnvH1D_Array(Empty_MC_Stack_array);
      sprintf(ytitle, "Number of Events / %.2f %s", binwidth_title, units_char);
    }
    else{
      sprintf(ytitle, "Number of Events");

    }
    mnvPlotter.draw_normalized_to_bin_width=DoBinwidthNorm;
    mnvPlotter.DrawDataStackedMC((dogData->second), &Empty_MC_Stack_array, 1.0, "TR", "Data", -1, -1,
    1001, xaxislabel.c_str(), ytitle, false);

    char total_title[1024];
    sprintf(total_title, "Stack %s [%s(%s)]", histotitle, Playlist_Name_char, HeliumStatus_name_char);

    mnvPlotter.AddHistoTitle(total_title, .04);
    mnvPlotter.WritePreliminary("TL", .035, 0, 0, false);
    std::string plotname = Form("%s",pdf_label.c_str());
    mnvPlotter.MultiPrint(&cE, plotname, "pdf");

  }//end of Loop


  cE.Closed();

  delete legend;


}

void DrawSTACKfromHistFilio_FULLStatsCOMBINED(ME_playlist_TFileMAP FullMCMap, Pot_MapList FullMC_POTMap,
                                     ME_playlist_TFileMAP EmptyMCMap,         Pot_MapList EmptyMC_POTMap,
                                     ME_playlist_TFileMAP FullDataMap,        Pot_MapList FullData_POTMap,
                                     ME_playlist_TFileMAP EmptyDataMap,       Pot_MapList EmptyData_POTMap,
                                    char *histoName_MC , char *histoName_Data, char *histotitle,
  std::string xaxislabel, std::string pdf_label, bool DoBinwidthNorm, std::string units, StackType STACKTYPE, bool Debug, bool MakeYaxisLOG )
  {    //helium_Status kEMPTY, kFULL;
    PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
    mnvPlotter.legend_n_columns = 2;
    TCanvas cE ("c1","c1");
    std::cout<<"trying MC HisName = "<< histoName_MC<<std::endl;
    std::cout<<"trying data HisName = "<< histoName_Data<<std::endl;

    char Stack_Name[1024];
    if(STACKTYPE==kMaterial){sprintf(Stack_Name, "%s_Material",histoName_MC);}
    else if(STACKTYPE==kInteraction){ sprintf(Stack_Name, "%s_Interaction",histoName_MC);}
    else if(STACKTYPE==kParticle){ sprintf(Stack_Name, "%s_Particle",histoName_MC);
    mnvPlotter.legend_n_columns = 3;}
    else if(STACKTYPE==kCryoTankRegions){sprintf(Stack_Name, "%s_CryoRegion",histoName_MC);}
    else if(STACKTYPE==kTrackType){ sprintf(Stack_Name, "%s_TrackType",histoName_MC);}
    else if(STACKTYPE==kVertexOptions){ sprintf(Stack_Name, "%s_vertex",histoName_MC);}
    else if(STACKTYPE==kboolNTrack){ sprintf(Stack_Name, "%s_Ntracks",histoName_MC);}
    else if(STACKTYPE==kOpenAnglestack){ sprintf(Stack_Name, "%s_OpenAngle",histoName_MC);}
    else{std::cout<<"Error unknown stack type: Ploting Failed"<<std::endl; return;}

    if(Debug == true){std::cout << "Making HistFolio_PlaylistMap using name: "<< Stack_Name <<std::endl;}
    Playlist_HistFolio_MnvH1D_Map HistFolio_PlaylistMap_Full =  Constuct_HistFolio_mvnH1DMap_FromME_playlist_TFileMAP(FullMCMap, Stack_Name );
    Playlist_HistFolio_MnvH1D_Map HistFolio_PlaylistMap_Empty =  Constuct_HistFolio_mvnH1DMap_FromME_playlist_TFileMAP(EmptyMCMap, Stack_Name );
    //Playlist_HistFolio_MnvH1D_Map HistFolio_PlaylistMap_Full_clone =  Constuct_HistFolio_mvnH1DMap_FromME_playlist_TFileMAP(FullMCMap, Stack_Name );
    //Playlist_HistFolio_MnvH1D_Map HistFolio_PlaylistMap_Empty_clone =  Constuct_HistFolio_mvnH1DMap_FromME_playlist_TFileMAP(EmptyMCMap, Stack_Name );

    if(Debug == true){std::cout << "Initialize Got FUll Data for Stacks   "<< Stack_Name<<std::endl;}
    Playlist_MnvH1D_Map FULLData_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullDataMap, histoName_Data );
    if(Debug == true){std::cout << "Initialize Got Empty Data for Stacks   "<< Stack_Name<<std::endl;}
    Playlist_MnvH1D_Map EmptyData_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(EmptyDataMap, histoName_Data );

    Pot_MapStatusList POTMAP_TOTAL =  Constuct_TOTALPOT_cryostatusMap(FullMC_POTMap, EmptyMC_POTMap, FullData_POTMap, EmptyData_POTMap);
    Pot_MapStatusList POTMAP_TOTAL_scaler = MakeScaler_TOTALPOT_cryostatusMapTOFULLDATA(POTMAP_TOTAL);


    std::vector<int> Helium9_colorScheme = {
      TColor::GetColor("#EEFF00"), // neonyellow,
      TColor::GetColor("#DF00FF"), //'psychedelic Purple
      TColor::GetColor("#ffc922"), //'sunset yellow'
      TColor::GetColor("#87CEEB"),//'skyblue'
      TColor::GetColor("#0859C6"), //blue
      TColor::GetColor("#654522"), // yellowishbrown,
      TColor::GetColor(43, 206,  72 ), //green
      TColor::GetColor("#FF0800"),//2 candy Apple
      TColor::GetColor("#90AD1C"),
      TColor::GetColor("#BABABA"), //Gray
      TColor::GetColor("#00FFFF"),//'aqua'
      TColor::GetColor("#F1B6DA"),//pink
      TColor::GetColor("#00A86B"),//'Jade'
      TColor::GetColor("#FAFAD2"),  // LightGoldenRodYellow
      TColor::GetColor("#800000"),  // Maroon
      TColor::GetColor("#555555"),  // dark grey
      TColor::GetColor(0, 153, 143 ), //turquoise
      TColor::GetColor("#654522"), // yellowishbrown,
      TColor::GetColor("#8db600"), // yellowgreen,
      TColor::GetColor("#D3D3D3"),  //'lightgrey'
       TColor::GetColor("#90AD1C"),
       TColor::GetColor("#CCDDAA")
    };



// Check if objects are same size and have playlists

if( CompareMap_ME_helium_PlaylistsKeys(HistFolio_PlaylistMap_Full,  FullMC_POTMap) == false ){assert(false && "HistFolio_PlaylistMap_Full and FullMC_scalerMap have different Keys " );}
if( CompareMap_ME_helium_PlaylistsKeys(HistFolio_PlaylistMap_Full,  FullData_POTMap) == false ){assert(false && "HistFolio_PlaylistMap_Full and FULLData_HistMAPScaled have different Keys " );}
//if( CompareMap_ME_helium_PlaylistsKeys(HistFolio_PlaylistMap_Full,  HistFolio_PlaylistMap_Full_clone) == false ){assert(false && "HistFolio_PlaylistMap_Full and HistFolio_PlaylistMap_Full_clone have different Keys " );}

double x1,x2,y1,y2;
mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", .5, 10, .025);
//TLegend *legend = new TLegend(x1 - .05, y1 + .1, x2 + .05, y2 + .1);
TLegend *legend = new TLegend(x1 - .02, y1+.31 , x2 +.1 , y2 + .42  );
legend->SetNColumns(1);
legend->SetTextSize(.02);
legend->SetFillColor(0);


typename std::map<ME_helium_Playlists, PlotUtils::HistFolio<PlotUtils::MnvH1D>>::const_iterator HistFoliocat;
//typename std::map<ME_helium_Playlists, PlotUtils::HistFolio<PlotUtils::MnvH1D>>::const_iterator HistFoliobird;
//typename std::map<ME_helium_Playlists, PlotUtils::MnvH1D*>::const_iterator dogData;

   auto CombinedFULL = (HistFolio_PlaylistMap_Full.begin()->second).GetHistArray();

  for(HistFoliocat = HistFolio_PlaylistMap_Full.begin(); HistFoliocat != HistFolio_PlaylistMap_Full.end(); ++HistFoliocat)
  {

    if(HistFoliocat->first != HistFolio_PlaylistMap_Full.begin()->first ){
      auto Full_MC_Stack_array = (HistFoliocat->second).GetHistArray();
      AddFirst_toSecond_MnvH1D_Arrays(CombinedFULL, Full_MC_Stack_array );

  }


  }//end of Loop

//////////////////////////////////////////////////////////
////// Drawing Combind FUll
///////////////////////////////////////////
auto FULL_Data_Hist = Combine_Hists_fromMAP(FULLData_HistMAP , kME1F ,"FULL_Data_Hist");
Scale_MnvH1D_Array(CombinedFULL , POTMAP_TOTAL_scaler[kMC_FULL]);
  char ytitle[100];
  char units_char[units.length()+1];
  strcpy(units_char,units.c_str());
  double binwidth_title = FULL_Data_Hist->GetBinWidth(3);


  if(DoBinwidthNorm==true){
    //FULL_Data_Hist->Scale(1.0,"width");
    //BinWidthNorm_MnvH1D_Array(CombinedFULL);
    sprintf(ytitle, "Number of Events / %.2f %s", binwidth_title, units_char);
  }
  else{
    sprintf(ytitle, "Number of Events");

  }

  if(MakeYaxisLOG==false){
    gPad->SetLogy(0);
  }
  else if(MakeYaxisLOG==true){
    mnvPlotter.axis_minimum= .01;
    mnvPlotter.axis_maximum= 10000;
    gPad->SetLogy();
  }


  mnvPlotter.draw_normalized_to_bin_width=DoBinwidthNorm;
  mnvPlotter.DrawDataStackedMC(FULL_Data_Hist, &CombinedFULL, 1.0, "TR", "Data", -1, -1,
  1001, xaxislabel.c_str(), ytitle, false);

  char total_title[1024];
  sprintf(total_title, "Stack %s [Combined FULL]", histotitle);

  mnvPlotter.AddHistoTitle(total_title, .04);
  mnvPlotter.WritePreliminary("TL", .025, 0, 0, false);
  std::string plotname = Form("%s",pdf_label.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");

  /////////////////////////////////////
  // Empty
  ////////////////////////////////////////////////////////////////

  if( CompareMap_ME_helium_PlaylistsKeys(HistFolio_PlaylistMap_Empty,  EmptyMC_POTMap) == false ){assert(false && "HistFolio_PlaylistMap_Empty and EmptyMC_scalerMap have different Keys " );}
  if( CompareMap_ME_helium_PlaylistsKeys(HistFolio_PlaylistMap_Empty,  EmptyData_POTMap) == false ){assert(false && "HistFolio_PlaylistMap_Empty and EmptyData_HistMAPScaled have different Keys " );}
  //auto  Empty_Stats_MC_Stack_Array = ((HistFolio_PlaylistMap_Empty.begin())->second).GetHistArray();
  //const TObjArray Empty_Stats_MC_Stack_Array_clone = (TObjArray)Empty_Stats_MC_Stack_Array.Clone();
  //TObjArray*  Empty_Stats_MC_Stack_Array = (TObjArray*)(*(((HistFolio_PlaylistMap_Empty.begin())->second).GetHistArray())).Clone();
  auto CombinedEmpty = (HistFolio_PlaylistMap_Empty.begin()->second).GetHistArray();

  for(HistFoliocat = HistFolio_PlaylistMap_Empty.begin(); HistFoliocat != HistFolio_PlaylistMap_Empty.end(); ++HistFoliocat)
  {
    if(HistFoliocat->first != HistFolio_PlaylistMap_Empty.begin()->first ){
      auto Empty_MC_Stack_array = (HistFoliocat->second).GetHistArray();
      AddFirst_toSecond_MnvH1D_Arrays(CombinedEmpty, Empty_MC_Stack_array);
    }

  }

  auto Empty_Data_Hist = Combine_Hists_fromMAP(EmptyData_HistMAP , kME1M, "Empty_Data_Hist");
  Scale_MnvH1D_Array(CombinedEmpty , POTMAP_TOTAL_scaler[kMC_EMPTY]);
  Empty_Data_Hist->Scale(POTMAP_TOTAL_scaler[kDATA_EMPTY]);
  mnvPlotter.draw_normalized_to_bin_width=DoBinwidthNorm;

  mnvPlotter.DrawDataStackedMC(Empty_Data_Hist, &CombinedEmpty, 1.0, "TR", "Data", -1, -1,
  1001, xaxislabel.c_str(), ytitle, false);

  sprintf(total_title, "Stack %s [Combined Empty]", histotitle);

  mnvPlotter.AddHistoTitle(total_title, .04);
  mnvPlotter.WritePreliminary("TL", .02, 0, 0, false);
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");

  ///////////////////////////////////////////////////////////////
  //// FUll - Empty Getting combined data and Bin width Norm them
  ////////////////////////////////////////////////////////////////


SubractSecond_FromFirst_MnvH1D_Arrays(CombinedFULL, CombinedEmpty);
FULL_Data_Hist->Add(Empty_Data_Hist,-1);


mnvPlotter.draw_normalized_to_bin_width=DoBinwidthNorm;
mnvPlotter.DrawDataStackedMC(FULL_Data_Hist, &CombinedFULL, 1.0, "TR", "Data", -1, -1,
1001, xaxislabel.c_str(), ytitle, false);


sprintf(total_title, "Stack %s [Combined F-E]", histotitle);

mnvPlotter.AddHistoTitle(total_title, .04);
mnvPlotter.WritePreliminary("TL", .02, 0, 0, false);
mnvPlotter.MultiPrint(&cE, plotname, "pdf");

  cE.Closed();

  delete legend;
  delete FULL_Data_Hist;
  delete Empty_Data_Hist;



return ;

}



////////////////////////////////////////////////////////////////////////////////////////////
void DrawSTACKfromHistFilio_COMBINED(ME_playlist_TFileMAP MCMap, double POTScale_MC_To_DATA,
                                     ME_playlist_TFileMAP DataMap, double POTScale_Data_To_DATA,
                                    char *histoName_MC , char *histoName_Data, char *histotitle,
  std::string xaxislabel, std::string pdf_label, bool DoBinwidthNorm, std::string units, StackType STACKTYPE, bool Debug, bool MakeYaxisLOG )
  {    //helium_Status kEMPTY, kFULL;
    PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
    mnvPlotter.legend_n_columns = 2;
    TCanvas cE ("c1","c1");
    std::cout<<"trying MC HisName = "<< histoName_MC<<std::endl;
    std::cout<<"trying data HisName = "<< histoName_Data<<std::endl;

    char Stack_Name[1024];
    if(STACKTYPE==kMaterial){sprintf(Stack_Name, "%s_Material",histoName_MC);}
    else if(STACKTYPE==kInteraction){ sprintf(Stack_Name, "%s_Interaction",histoName_MC);}
    else if(STACKTYPE==kParticle){ sprintf(Stack_Name, "%s_Particle",histoName_MC);
    mnvPlotter.legend_n_columns = 3;}
    else if(STACKTYPE==kCryoTankRegions){sprintf(Stack_Name, "%s_CryoRegion",histoName_MC);}
    else if(STACKTYPE==kTrackType){ sprintf(Stack_Name, "%s_TrackType",histoName_MC);}
    else if(STACKTYPE==kVertexOptions){ sprintf(Stack_Name, "%s_vertex",histoName_MC);}
    else if(STACKTYPE==kboolNTrack){ sprintf(Stack_Name, "%s_Ntracks",histoName_MC);}
    else if(STACKTYPE==kOpenAnglestack){ sprintf(Stack_Name, "%s_OpenAngle",histoName_MC);}
    else if(STACKTYPE==kCH_Signal_type){ sprintf(Stack_Name, "%s_SignalSelection",histoName_MC);}
    else{std::cout<<"Error unknown stack type: Ploting Failed"<<std::endl; return;}

    if(Debug == true){std::cout << "Making HistFolio_PlaylistMap using name: "<< Stack_Name <<std::endl;}
    Playlist_HistFolio_MnvH1D_Map HistFolio_PlaylistMap =  Constuct_HistFolio_mvnH1DMap_FromME_playlist_TFileMAP(MCMap, Stack_Name );

    if(Debug == true){std::cout << "Initialize Got  Data for Stacks   "<< Stack_Name<<std::endl;}
    Playlist_MnvH1D_Map Data_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(DataMap, histoName_Data );



    std::vector<int> Helium9_colorScheme = {
      TColor::GetColor("#87CEEB"),//'skyblue'
      TColor::GetColor("#DF00FF"), //'psychedelic Purple
      TColor::GetColor("#ffc922"), //'sunset yellow'
      TColor::GetColor("#EEFF00"), // neonyellow,
      TColor::GetColor("#0859C6"), //blue
      TColor::GetColor("#654522"), // yellowishbrown,
      TColor::GetColor(43, 206,  72 ), //green
      TColor::GetColor("#FF0800"),//2 candy Apple
      TColor::GetColor("#90AD1C"),
      TColor::GetColor("#BABABA"), //Gray
      TColor::GetColor("#00FFFF"),//'aqua'
      TColor::GetColor("#F1B6DA"),//pink
      TColor::GetColor("#00A86B"),//'Jade'
      TColor::GetColor("#FAFAD2"),  // LightGoldenRodYellow
      TColor::GetColor("#800000"),  // Maroon
      TColor::GetColor("#555555"),  // dark grey
      TColor::GetColor(0, 153, 143 ), //turquoise
      TColor::GetColor("#654522"), // yellowishbrown,
      TColor::GetColor("#8db600"), // yellowgreen,
      TColor::GetColor("#D3D3D3"),  //'lightgrey'
       TColor::GetColor("#90AD1C"),
       TColor::GetColor("#CCDDAA")
    };



// Check if objects are same size and have playlists

double x1,x2,y1,y2;
mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", .5, 10, .025);
//TLegend *legend = new TLegend(x1 - .05, y1 + .1, x2 + .05, y2 + .1);
TLegend *legend = new TLegend(x1 - .02, y1+.25 , x2 +.075 , y2 + .35  );
legend->SetNColumns(1);
legend->SetTextSize(.03);
legend->SetFillColor(0);


typename std::map<ME_helium_Playlists, PlotUtils::HistFolio<PlotUtils::MnvH1D>>::const_iterator HistFoliocat;
//typename std::map<ME_helium_Playlists, PlotUtils::HistFolio<PlotUtils::MnvH1D>>::const_iterator HistFoliobird;
//typename std::map<ME_helium_Playlists, PlotUtils::MnvH1D*>::const_iterator dogData;

   auto CombinedFULL = (HistFolio_PlaylistMap.begin()->second).GetHistArray();

  for(HistFoliocat = HistFolio_PlaylistMap.begin(); HistFoliocat != HistFolio_PlaylistMap.end(); ++HistFoliocat)
  {

    if(HistFoliocat->first != HistFolio_PlaylistMap.begin()->first ){
      auto Full_MC_Stack_array = (HistFoliocat->second).GetHistArray();
      AddFirst_toSecond_MnvH1D_Arrays(CombinedFULL, Full_MC_Stack_array );

  }


  }//end of Loop

//////////////////////////////////////////////////////////
////// Drawing Combind FUll
///////////////////////////////////////////
auto FULL_Data_Hist = Combine_Hists_fromMAP(Data_HistMAP , kME1F ,"FULL_Data_Hist");
FULL_Data_Hist->Scale(POTScale_Data_To_DATA);
Scale_MnvH1D_Array(CombinedFULL , POTScale_MC_To_DATA);
  char ytitle[100];
  char units_char[units.length()+1];
  strcpy(units_char,units.c_str());
  double binwidth_title = FULL_Data_Hist->GetBinWidth(3);


  if(DoBinwidthNorm==true){
    //FULL_Data_Hist->Scale(1.0,"width");
    //BinWidthNorm_MnvH1D_Array(CombinedFULL);
    sprintf(ytitle, "Number of Events / %.2f %s", binwidth_title, units_char);
  }
  else{
    sprintf(ytitle, "Number of Events");

  }

  if(MakeYaxisLOG==false){
    gPad->SetLogy(0);
  }
  else if(MakeYaxisLOG==true){
    mnvPlotter.axis_minimum= .01;
    mnvPlotter.axis_maximum= 10000;
    gPad->SetLogy();
  }

  mnvPlotter.axis_label_size= .02;
  mnvPlotter.draw_normalized_to_bin_width=DoBinwidthNorm;
  mnvPlotter.DrawDataStackedMC(FULL_Data_Hist, &CombinedFULL, 1.0, "TR", "Data", -1, -1,
  1001, xaxislabel.c_str(), ytitle, false);

  char total_title[1024];
  sprintf(total_title, "Stack %s [Combined FULL]", histotitle);

  mnvPlotter.AddHistoTitle(total_title, .04);
  mnvPlotter.WritePreliminary("TL", .02, 0, 0, false);
  std::string plotname = Form("%s",pdf_label.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");

  cE.Closed();

  delete legend;
  delete FULL_Data_Hist;




return ;

}



void DrawNonSTACKfromHistFilio_FULLStatsCOMBINED(ME_playlist_TFileMAP FullMCMap, Pot_MapList FullMC_POTMap,
                                     ME_playlist_TFileMAP EmptyMCMap,         Pot_MapList EmptyMC_POTMap,
                                     ME_playlist_TFileMAP FullDataMap,        Pot_MapList FullData_POTMap,
                                     ME_playlist_TFileMAP EmptyDataMap,       Pot_MapList EmptyData_POTMap,
                                    char *histoName_MC , char *histoName_Data, char *histotitle,
  std::string xaxislabel, std::string pdf_label, bool DoBinwidthNorm, std::string units, StackType STACKTYPE, bool Debug )
  {    //helium_Status kEMPTY, kFULL;
    PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
    mnvPlotter.legend_n_columns = 2;

    TCanvas cE ("c1","c1");
    std::cout<<"trying MC HisName = "<< histoName_MC<<std::endl;
    std::cout<<"trying data HisName = "<< histoName_Data<<std::endl;

    char Stack_Name[1024];
    if(STACKTYPE==kMaterial){sprintf(Stack_Name, "%s_Material",histoName_MC);}
    else if(STACKTYPE==kInteraction){ sprintf(Stack_Name, "%s_Interaction",histoName_MC);}
    else if(STACKTYPE==kParticle){
      sprintf(Stack_Name, "%s_Particle",histoName_MC);
      mnvPlotter.legend_n_columns = 3;
  }
    else if(STACKTYPE==kCryoTankRegions){sprintf(Stack_Name, "%s_CryoRegion",histoName_MC);}
    else{std::cout<<"Error unknown stack type: Ploting Failed"<<std::endl; return;}

    if(Debug == true){std::cout << "Making HistFolio_PlaylistMap using name: "<< Stack_Name <<std::endl;}
    Playlist_HistFolio_MnvH1D_Map HistFolio_PlaylistMap_Full =  Constuct_HistFolio_mvnH1DMap_FromME_playlist_TFileMAP(FullMCMap, Stack_Name );
    Playlist_HistFolio_MnvH1D_Map HistFolio_PlaylistMap_Empty =  Constuct_HistFolio_mvnH1DMap_FromME_playlist_TFileMAP(EmptyMCMap, Stack_Name );
    //Playlist_HistFolio_MnvH1D_Map HistFolio_PlaylistMap_Full_clone =  Constuct_HistFolio_mvnH1DMap_FromME_playlist_TFileMAP(FullMCMap, Stack_Name );
    //Playlist_HistFolio_MnvH1D_Map HistFolio_PlaylistMap_Empty_clone =  Constuct_HistFolio_mvnH1DMap_FromME_playlist_TFileMAP(EmptyMCMap, Stack_Name );

    if(Debug == true){std::cout << "Initialize Got FUll Data for Stacks   "<< Stack_Name<<std::endl;}
    Playlist_MnvH1D_Map FULLData_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(FullDataMap, histoName_Data );
    if(Debug == true){std::cout << "Initialize Got Empty Data for Stacks   "<< Stack_Name<<std::endl;}
    Playlist_MnvH1D_Map EmptyData_HistMAP =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(EmptyDataMap, histoName_Data );

    Pot_MapStatusList POTMAP_TOTAL =  Constuct_TOTALPOT_cryostatusMap(FullMC_POTMap, EmptyMC_POTMap, FullData_POTMap, EmptyData_POTMap);
    Pot_MapStatusList POTMAP_TOTAL_scaler = MakeScaler_TOTALPOT_cryostatusMapTOFULLDATA(POTMAP_TOTAL);



    std::vector<int> Helium9_colorScheme = {
      TColor::GetColor("#EEFF00"), // neonyellow,
      TColor::GetColor("#DF00FF"), //'psychedelic Purple
      TColor::GetColor("#ffc922"), //'sunset yellow'
      TColor::GetColor("#87CEEB"),//'skyblue'
      TColor::GetColor("#0859C6"), //blue
      TColor::GetColor("#654522"), // yellowishbrown,
      TColor::GetColor(43, 206,  72 ), //green
      TColor::GetColor("#FF0800"),//2 candy Apple
      TColor::GetColor("#90AD1C"),
      TColor::GetColor("#BABABA"), //Gray
      TColor::GetColor("#00FFFF"),//'aqua'
      TColor::GetColor("#F1B6DA"),//pink
      TColor::GetColor("#00A86B"),//'Jade'
      TColor::GetColor("#FAFAD2"),  // LightGoldenRodYellow
      TColor::GetColor("#800000"),  // Maroon
      TColor::GetColor("#555555"),  // dark grey
      TColor::GetColor(0, 153, 143 ), //turquoise
      TColor::GetColor("#654522"), // yellowishbrown,
      TColor::GetColor("#8db600"), // yellowgreen,
      TColor::GetColor("#D3D3D3"),  //'lightgrey'
       TColor::GetColor("#90AD1C"),
       TColor::GetColor("#CCDDAA")
    };



// Check if objects are same size and have playlists

if( CompareMap_ME_helium_PlaylistsKeys(HistFolio_PlaylistMap_Full,  FullMC_POTMap) == false ){assert(false && "HistFolio_PlaylistMap_Full and FullMC_scalerMap have different Keys " );}
if( CompareMap_ME_helium_PlaylistsKeys(HistFolio_PlaylistMap_Full,  FullData_POTMap) == false ){assert(false && "HistFolio_PlaylistMap_Full and FULLData_HistMAPScaled have different Keys " );}
//if( CompareMap_ME_helium_PlaylistsKeys(HistFolio_PlaylistMap_Full,  HistFolio_PlaylistMap_Full_clone) == false ){assert(false && "HistFolio_PlaylistMap_Full and HistFolio_PlaylistMap_Full_clone have different Keys " );}

double x1,x2,y1,y2;
mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", .5, 10, .025);
//TLegend *legend = new TLegend(x1 - .05, y1 + .1, x2 + .05, y2 + .1);
TLegend *legend = new TLegend(x1 - .02, y1+.31 , x2 +.075 , y2 + .42  );
//legend->SetNColumns(1);
legend->SetTextSize(.03);
legend->SetFillColor(0);


typename std::map<ME_helium_Playlists, PlotUtils::HistFolio<PlotUtils::MnvH1D>>::const_iterator HistFoliocat;
//typename std::map<ME_helium_Playlists, PlotUtils::HistFolio<PlotUtils::MnvH1D>>::const_iterator HistFoliobird;
//typename std::map<ME_helium_Playlists, PlotUtils::MnvH1D*>::const_iterator dogData;

auto CombinedFULL = (HistFolio_PlaylistMap_Full.begin()->second).GetHistArray();

  for(HistFoliocat = HistFolio_PlaylistMap_Full.begin(); HistFoliocat != HistFolio_PlaylistMap_Full.end(); ++HistFoliocat)
  {

    if(HistFoliocat->first != HistFolio_PlaylistMap_Full.begin()->first ){
      auto Full_MC_Stack_array = (HistFoliocat->second).GetHistArray();
      AddFirst_toSecond_MnvH1D_Arrays(CombinedFULL, Full_MC_Stack_array );

    }


  }//end of Loop

//////////////////////////////////////////////////////////
////// Drawing Combind FUll
///////////////////////////////////////////
auto FULL_Data_Hist = Combine_Hists_fromMAP(FULLData_HistMAP , kME1F ,"FULL_Data_Hist");
Scale_MnvH1D_Array(CombinedFULL , POTMAP_TOTAL_scaler[kMC_FULL]);
  char ytitle[100];
  char units_char[units.length()+1];
  strcpy(units_char,units.c_str());
  double binwidth_title = FULL_Data_Hist->GetBinWidth(3);


  if(DoBinwidthNorm==true){
    //FULL_Data_Hist->Scale(1.0,"width");
    //BinWidthNorm_MnvH1D_Array(CombinedFULL);
    sprintf(ytitle, "Number of Events / %.2f %s", binwidth_title, units_char);
  }
  else{
    sprintf(ytitle, "Number of Events");

  }


  mnvPlotter.draw_normalized_to_bin_width=DoBinwidthNorm;
  mnvPlotter.DrawDataNonStackedMC(FULL_Data_Hist, &CombinedFULL, 1.0, "TR", "Data", -1, -1,
  1001, xaxislabel.c_str(), ytitle, false);

  char total_title[1024];
  sprintf(total_title, "Stack %s [Combined FULL]", histotitle);

  mnvPlotter.AddHistoTitle(total_title, .04);
  mnvPlotter.WritePreliminary("TL", .02, 0, 0, false);
  std::string plotname = Form("%s",pdf_label.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");

  /////////////////////////////////////
  // Empty
  ////////////////////////////////////////////////////////////////

  if( CompareMap_ME_helium_PlaylistsKeys(HistFolio_PlaylistMap_Empty,  EmptyMC_POTMap) == false ){assert(false && "HistFolio_PlaylistMap_Empty and EmptyMC_scalerMap have different Keys " );}
  if( CompareMap_ME_helium_PlaylistsKeys(HistFolio_PlaylistMap_Empty,  EmptyData_POTMap) == false ){assert(false && "HistFolio_PlaylistMap_Empty and EmptyData_HistMAPScaled have different Keys " );}
  //auto  Empty_Stats_MC_Stack_Array = ((HistFolio_PlaylistMap_Empty.begin())->second).GetHistArray();
  //const TObjArray Empty_Stats_MC_Stack_Array_clone = (TObjArray)Empty_Stats_MC_Stack_Array.Clone();
  //TObjArray*  Empty_Stats_MC_Stack_Array = (TObjArray*)(*(((HistFolio_PlaylistMap_Empty.begin())->second).GetHistArray())).Clone();
  auto CombinedEmpty = (HistFolio_PlaylistMap_Empty.begin()->second).GetHistArray();

  for(HistFoliocat = HistFolio_PlaylistMap_Empty.begin(); HistFoliocat != HistFolio_PlaylistMap_Empty.end(); ++HistFoliocat)
  {
    if(HistFoliocat->first != HistFolio_PlaylistMap_Empty.begin()->first ){
      auto Empty_MC_Stack_array = (HistFoliocat->second).GetHistArray();
      AddFirst_toSecond_MnvH1D_Arrays(CombinedEmpty, Empty_MC_Stack_array);
    }

  }

  auto Empty_Data_Hist = Combine_Hists_fromMAP(EmptyData_HistMAP , kME1M, "Empty_Data_Hist");
  Scale_MnvH1D_Array(CombinedEmpty , POTMAP_TOTAL_scaler[kMC_EMPTY]);
  Empty_Data_Hist->Scale(POTMAP_TOTAL_scaler[kDATA_EMPTY]);
  mnvPlotter.draw_normalized_to_bin_width=DoBinwidthNorm;
  mnvPlotter.DrawDataNonStackedMC(Empty_Data_Hist, &CombinedEmpty, 1.0, "TR", "Data", -1, -1,
  1001, xaxislabel.c_str(), ytitle, false);

  sprintf(total_title, "Stack %s [Combined Empty]", histotitle);

  mnvPlotter.AddHistoTitle(total_title, .04);
  mnvPlotter.WritePreliminary("TL", .02, 0, 0, false);
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");

  ///////////////////////////////////////////////////////////////
  //// FUll - Empty Getting combined data and Bin width Norm them
  ////////////////////////////////////////////////////////////////


SubractSecond_FromFirst_MnvH1D_Arrays(CombinedFULL, CombinedEmpty);
FULL_Data_Hist->Add(Empty_Data_Hist,-1);


mnvPlotter.draw_normalized_to_bin_width=DoBinwidthNorm;
mnvPlotter.DrawDataNonStackedMC(FULL_Data_Hist, &CombinedFULL, 1.0, "TR", "Data", -1, -1,
1001, xaxislabel.c_str(), ytitle, false);


sprintf(total_title, "Stack %s [Combined F-E]", histotitle);

mnvPlotter.AddHistoTitle(total_title, .04);
mnvPlotter.WritePreliminary("TL", .02, 0, 0, false);
mnvPlotter.MultiPrint(&cE, plotname, "pdf");

  cE.Closed();

  delete legend;
  delete FULL_Data_Hist;
  delete Empty_Data_Hist;

}


/////////////////////////////////////////
void Draw_2D_Panel_MC_andData_frompointer(MnvH2D *hist_Data, MnvH2D *hist_MC,
  char *histotitle, std::string xaxislabel,
   std::string yaxislabel,const char *Zaxislabel , double max_x, double max_y,
    char *pdf_label, bool doBinwidth, bool MakeXaxisLOG,
    double x_projectionTxtsize, double y_projectionTxtsize, bool doMultipliers ){

      bool setMaxY = false;
      double headroom = 1.5;
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  myPlotStyle();
  TH1::SetDefaultSumw2();
  gStyle->SetErrorX(0);
  gStyle->SetEndErrorSize(2);

  //if(doBinwidth==true){
  //  hist_MC->Scale(1.0,"width");
  //  hist_Data->Scale(1.0,"width");
  //}


  TH2* mc_hist=new TH2D(hist_MC->GetCVHistoWithStatError());
  TH2* data_Stathist=new TH2D(hist_Data->GetCVHistoWithStatError());
  TH2* data_hist_Error = new TH2D(hist_Data->GetCVHistoWithError());

  mc_hist->SetLineColor(kRed);
  mc_hist->SetLineWidth(2);

  data_Stathist->SetMarkerStyle(1);
  data_Stathist->SetLineColor(kBlack);
  data_Stathist->SetLineWidth(2);

  data_hist_Error->SetMarkerStyle(kFullCircle);
  data_hist_Error->SetMarkerSize(0.7);
  data_hist_Error->SetLineColor(kBlack);

  std::vector<std::pair<TH2*, const char*> > histAndOpts;
  histAndOpts.push_back(std::make_pair(mc_hist,"hist"));
  histAndOpts.push_back(std::make_pair(data_Stathist,"graph e"));
  histAndOpts.push_back(std::make_pair(data_hist_Error,"graph ep"));


  TLegend* leg=new TLegend(0.7, 0.05, 0.9, 0.25);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.025);
  leg->AddEntry(data_hist_Error, "data", "lpe");
  leg->AddEntry(mc_hist, "MINERvA v1Tune", "l");

  //bool doMultipliers=false;

  // I think if getscales is tru do Y projection if false do x projection
  //std::vector<double> multipliers_y = GetScales(histAndOpts, true, true);
  //std::vector<double> multipliers_y = GetScales_2d(histAndOpts, false);
  std::vector<double> multipliers_y =GetScales(histAndOpts, false, max_y, 1.2);
  //std::vector<double> multipliers_y =GetScales(histAndOpts,MaxY*1.1, 1.0);
  GridCanvas* gc_y=plotYAxis1D(histAndOpts, xaxislabel, yaxislabel, doMultipliers ? &multipliers_y[0] : NULL, y_projectionTxtsize, doBinwidth);
  gc_y->SetYLabel_Size(.015);
  gc_y->SetXLabel_Size(.025);
  double MaxY = gc_y->GetPadMax();
  if(setMaxY==false) gc_y->SetYLimits(0,MaxY*headroom);
  else gc_y->SetYLimits(0,max_y);
  gc_y->SetYTitle(Zaxislabel);
  //gc_y->SetLogx(0);
  gc_y->SetGridx();
  if(MakeXaxisLOG==true) gc_y->SetLogx(1);
  char total_title[1024];
  sprintf(total_title, " %s [Yproj]", histotitle);

  mnvPlotter.AddHistoTitle(total_title, .035);
  if(MakeXaxisLOG==true) gc_y->SetLogx(1);
  gc_y->Modified();
  //leg->Draw("SAME");
  gc_y->Print(pdf_label);
  /////////////////////////////////////////////////////////
  // I think if getscales is tru do Y projection if false do x projection
  //std::vector<double> multipliers_x = GetScales(histAndOpts, false, true);

  std::vector<double> multipliers_x =GetScales(histAndOpts, true, max_x, 1.2);
  //std::vector<double> multipliers_x =GetScales(histAndOpts,MaxY*1.1, 1.0);
  //std::vector<double> multipliers_x = GetScales_2d(histAndOpts,  true);
  //if(MakeXaxisLOG==true) gc_x->SetLogy(0);
  GridCanvas* gc_x=plotXAxis1D(histAndOpts, yaxislabel, xaxislabel, doMultipliers ? &multipliers_x[0] : NULL, doBinwidth); // , x_projectionTxtsizec
  // Set the y range manually. Can also use gc3->Remax() to guess automatically
  gc_x->SetYLabel_Size(.015);
  gc_x->SetXLabel_Size(.025);
  double MaxX = gc_x->GetPadMax();
  if(setMaxY==false) gc_x->SetYLimits(0,MaxX*headroom);
  else gc_x->SetYLimits(0,max_x);
  gc_x->SetYTitle(Zaxislabel);
  //if(MakeXaxisLOG==true) gc_x->SetLogx(0);
  sprintf(total_title, " %s [Xproj]", histotitle);
  mnvPlotter.AddHistoTitle(total_title, .038);
  //gc_x->SetYTitle(yaxisUNITS);
  if(MakeXaxisLOG==true) gc_x->SetLogx(1);
  gc_x->SetGridx();
  gc_x->Modified();
  //leg->Draw("SAME");
  gc_x->Print(pdf_label);

  delete gc_y;
  delete gc_x;

}//end of function
/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////
void Draw_2D_Panel_MC_andData_frompointer_DISbreakdown_E_theta(MnvH2D *hist_Data, MnvH2D *hist_MC,
  MnvH2D *hist_MC_QE,
  MnvH2D *hist_MC_HeavierRES,
  MnvH2D *hist_MC_deltaRES,
  MnvH2D *hist_MC_2p2h,
  MnvH2D *hist_MC_DISSIS,
  MnvH2D *hist_MC_DISHard,
  MnvH2D *hist_MC_DISSoft,
  MnvH2D *hist_MC_Other,
  MnvH2D *hist_MC_NONE,
  bool DataStat_SysError,
  bool MC_Stat_SysError,
  char *histotitle, std::string xaxislabel,
  std::string yaxislabel,const char *Zaxislabel , double max_x, double max_y, bool setMaxY,
  char *pdf_label, bool doBinwidth, bool MakeXaxisLOG,
  double x_projectionTxtsize, double y_projectionTxtsize, bool doMultipliers, bool MakeRatio){

//bool setMaxY = true;
double headroom = 1.5;
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  myPlotStyle();
  TH1::SetDefaultSumw2();
  gStyle->SetErrorX(0);
  gStyle->SetEndErrorSize(2);

  TLegend* leg=new TLegend(0.85, 0.005, 0.99, 0.30);
  leg->SetNColumns(1);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.02);


  TH2* h_QE = new TH2D(hist_MC_QE->GetCVHistoWithStatError());
  TH2* h_HeavierRES = new TH2D(hist_MC_HeavierRES->GetCVHistoWithStatError());
  TH2* h_deltaRES = new TH2D(hist_MC_deltaRES->GetCVHistoWithStatError());
  TH2* h_2p2h = new TH2D(hist_MC_2p2h->GetCVHistoWithStatError());
  TH2* h_DISSIS = new TH2D(hist_MC_DISSIS->GetCVHistoWithStatError());
  TH2* h_DISHard = new TH2D(hist_MC_DISHard->GetCVHistoWithStatError());
  TH2* h_DISSoft = new TH2D(hist_MC_DISSoft->GetCVHistoWithStatError());
  TH2* h_Other = new TH2D(hist_MC_Other->GetCVHistoWithStatError());
  TH2* h_NONE = new TH2D(hist_MC_NONE->GetCVHistoWithStatError());
  TH2* mc_hist = new TH2D(hist_MC->GetCVHistoWithStatError());
  TH2* mcTotalError =new TH2D(hist_MC->GetCVHistoWithError());

  //TH2* mc_hist_Divide = new TH2D(hist_MC->GetCVHistoWithStatError());
  //TH2* mcTotalError_Divide =new TH2D(hist_MC->GetCVHistoWithError());

  mc_hist->SetLineColor(kRed);
  mc_hist->SetLineWidth(2);
  mcTotalError->SetFillColorAlpha(kRed, 0.5);
  mcTotalError->SetFillStyle(3144);

  TH2* dataStat = new TH2D(hist_Data->GetCVHistoWithStatError());
  TH2* data_1 = new TH2D(hist_Data->GetCVHistoWithError());

  dataStat->SetMarkerStyle(1);
  dataStat->SetLineColor(kBlack);
  dataStat->SetLineWidth(2);

  data_1->SetMarkerStyle(kFullCircle);
  data_1->SetMarkerSize(0.7);
  data_1->SetLineColor(kBlack);

  std::vector<int> Helium9_colorScheme = {
    TColor::GetColor("#F1B6DA"),//pink 11

    TColor::GetColor("#DF00FF"), //'psychedelic Purple1
    TColor::GetColor(43,206,72 ), //green 2
    TColor::GetColor("#87CEEB"),//'skyblue' 3
    TColor::GetColor("#0859C6"), //blue 4
    TColor::GetColor("#654522"), // yellowishbrown,5
    TColor::GetColor("#ffc922"), //'sunset yellow'6
    TColor::GetColor("#FF0800"),//2 candy Apple7
    TColor::GetColor("#800000"),  // Maroon
    TColor::GetColor("#90AD1C"),//8
    TColor::GetColor("#BABABA"), //Gray 9
    TColor::GetColor("#00FFFF"),//'aqua' 10
    TColor::GetColor("#AAF0D1"), // mint green
    TColor::GetColor(kRed),//'Jade' 12
    TColor::GetColor("#FAFAD2"),  // LightGoldenRodYellow 13

    TColor::GetColor("#555555"),  // dark grey 15
    TColor::GetColor(0, 153, 143 ), //turquoise 16
    TColor::GetColor("#654522"), // yellowishbrown, 17
    TColor::GetColor("#8db600"), // yellowgreen, 18
    TColor::GetColor("#D3D3D3"),  //'lightgrey' 19
    TColor::GetColor("#90AD1C"), // 20
    TColor::GetColor("#CCDDAA"), //21
    TColor::GetColor(kMagenta), //22
    TColor::GetColor("#EEFF00") // neonyellow,0
  };

  h_QE->SetLineWidth(2);        h_QE->SetLineColor(Helium9_colorScheme.at(0));
  h_2p2h->SetLineWidth(2);      h_2p2h->SetLineColor(Helium9_colorScheme.at(3));
  h_HeavierRES->SetLineWidth(2);h_HeavierRES->SetLineColor(Helium9_colorScheme.at(1));
  h_deltaRES->SetLineWidth(2);  h_deltaRES->SetLineColor(Helium9_colorScheme.at(2));
  h_DISSIS->SetLineWidth(2);    h_DISSIS->SetLineColor(Helium9_colorScheme.at(4));
  h_DISHard->SetLineWidth(2);   h_DISHard->SetLineColor(kTeal);
  h_DISSoft->SetLineWidth(2);   h_DISSoft->SetLineColor(Helium9_colorScheme.at(6));
  h_Other->SetLineWidth(2);     h_Other->SetLineColor(Helium9_colorScheme.at(9));
  h_NONE->SetLineWidth(2);      h_NONE->SetLineColor(Helium9_colorScheme.at(8));

std::vector<std::pair<TH2*, const char*> > histAndOpts;


  if (MakeRatio==true){

    data_1->Divide(mc_hist);
    dataStat->Divide(mc_hist);
    h_QE->Divide(mc_hist);
    h_HeavierRES->Divide(mc_hist);
    h_deltaRES->Divide(mc_hist);
    h_2p2h->Divide(mc_hist);
    h_DISSIS->Divide(mc_hist);
    h_DISHard->Divide(mc_hist);
    h_DISSoft->Divide(mc_hist);
    h_Other->Divide(mc_hist);
    h_NONE->Divide(mc_hist);
    mc_hist->Divide(mc_hist);


  histAndOpts.push_back(std::make_pair(dataStat,     "histp"));
  histAndOpts.push_back(std::make_pair(mc_hist,      "graph0LX"));
  histAndOpts.push_back(std::make_pair(h_QE,         "graph0LX"));
  histAndOpts.push_back(std::make_pair(h_2p2h,       "graph0LX"));
  histAndOpts.push_back(std::make_pair(h_HeavierRES, "graph0LX"));
  histAndOpts.push_back(std::make_pair(h_deltaRES,   "graph0LX"));
  histAndOpts.push_back(std::make_pair(h_DISSIS,     "graph0LX"));
  histAndOpts.push_back(std::make_pair(h_DISHard,    "graph0LX"));
  histAndOpts.push_back(std::make_pair(h_DISSoft,    "graph0LX"));
  histAndOpts.push_back(std::make_pair(h_Other,      "graph0LX"));
  histAndOpts.push_back(std::make_pair(h_NONE,       "graph0LX"));
  if(DataStat_SysError==true) { histAndOpts.push_back(std::make_pair(data_1,"graph ep"));}


  }

else{

  histAndOpts.push_back(std::make_pair(mc_hist,"hist"));
  if(MC_Stat_SysError==true) histAndOpts.push_back(std::make_pair(mcTotalError,       "graphe3"));
  histAndOpts.push_back(std::make_pair(h_QE,         "graph0LX")); //
  histAndOpts.push_back(std::make_pair(h_2p2h,       "graph0LX"));
  histAndOpts.push_back(std::make_pair(h_HeavierRES, "graph0LX"));
  histAndOpts.push_back(std::make_pair(h_deltaRES,   "graph0LX"));
  histAndOpts.push_back(std::make_pair(h_DISSIS,     "graph0LX"));
  histAndOpts.push_back(std::make_pair(h_DISHard,    "graph0LX"));
  histAndOpts.push_back(std::make_pair(h_DISSoft,    "graph0LX"));
  histAndOpts.push_back(std::make_pair(h_Other,      "graph0LX"));
  histAndOpts.push_back(std::make_pair(h_NONE,       "graph0LX"));

  if(DataStat_SysError==true) { histAndOpts.push_back(std::make_pair(data_1,"graph ep"));}
  histAndOpts.push_back(std::make_pair(dataStat,"graph e"));
}

if(DataStat_SysError==true) {leg->AddEntry(data_1, "Data[Stat+Sys]", "lpe");}
else{leg->AddEntry(dataStat, "Data[Stat]", "lpe");}

if(MC_Stat_SysError==true) leg->AddEntry(mc_hist, "MINERvA v1 [Stat+Sys]", "l");
else leg->AddEntry(mc_hist, "MINERvA v1 [Stat]", "l");

leg->AddEntry(h_QE,         "QE" , "l");
leg->AddEntry(h_2p2h,       "2p2h" , "l");
leg->AddEntry(h_HeavierRES, "Heavier RES" , "l");
leg->AddEntry(h_deltaRES,   "#Delta RES" , "l");
leg->AddEntry(h_DISSIS,     "SIS" , "l");
leg->AddEntry(h_DISHard,    "Hard DIS" , "l");
leg->AddEntry(h_DISSoft,    "Soft DIS" , "l");
leg->AddEntry(h_Other,      "Other" , "l");
leg->AddEntry(h_NONE,       "NONE" , "l");


  // I think if getscales is tru do Y projection if false do x projection
  //std::vector<double> multipliers_y = GetScales(histAndOpts, true, true);
  std::vector<double> multipliers_y = GetScales_2d(histAndOpts, false);
  GridCanvas* gc_y=plotYAxis1D(histAndOpts, xaxislabel, yaxislabel, doMultipliers ? &multipliers_y[0] : NULL, y_projectionTxtsize, doBinwidth);
  gc_y->SetYLabel_Size(.025);
  gc_y->SetXLabel_Size(.03);
  double MaxY = gc_y->GetPadMax();
  if(setMaxY==false) gc_y->SetYLimits(0,MaxY*headroom);
  else gc_y->SetYLimits(0,max_y);
  gc_y->SetYTitle(Zaxislabel);
  //gc_y->SetLogx(0);
  gc_y->SetGridx();
  if (MakeRatio==true)gc_y->SetGridy();
  if(MakeXaxisLOG==true) gc_y->SetLogx(1);
  char total_title[1024];
  sprintf(total_title, " %s [Yproj]", histotitle);

  mnvPlotter.AddHistoTitle(total_title, .035);
  if(MakeXaxisLOG==true) gc_y->SetLogx(1);
  gc_y->Modified();
  //leg->Draw("SAME");
  gc_y->Print(pdf_label);
  /////////////////////////////////////////////////////////
  // I think if getscales is tru do Y projection if false do x projection
  //std::vector<double> multipliers_x = GetScales(histAndOpts, false, true);
  std::vector<double> multipliers_x = GetScales_2d(histAndOpts,  true);
  //if(MakeXaxisLOG==true) gc_x->SetLogy(0);
  GridCanvas* gc_x=plotXAxis1D(histAndOpts, yaxislabel, xaxislabel, doMultipliers ? &multipliers_x[0] : NULL, doBinwidth); // , x_projectionTxtsizec
  // Set the y range manually. Can also use gc3->Remax() to guess automatically
  gc_x->SetYLabel_Size(.025);
  gc_x->SetXLabel_Size(.03);
  double MaxX = gc_x->GetPadMax();
  if(setMaxY==false) gc_x->SetYLimits(0,MaxX*headroom);
  else gc_x->SetYLimits(0,max_x);
  gc_x->SetYTitle(Zaxislabel);
  //if(MakeXaxisLOG==true) gc_x->SetLogx(0);
  sprintf(total_title, " %s [Xproj]", histotitle);
  mnvPlotter.AddHistoTitle(total_title, .038);
  //gc_x->SetYTitle(yaxisUNITS);
  if(MakeXaxisLOG==true) gc_x->SetLogx(1);
  if (MakeRatio==true) gc_x->SetGridy();
  gc_x->SetGridx();
  gc_x->Modified();
  leg->Draw("SAME");
  gc_x->Print(pdf_label);

  delete gc_y;
  delete gc_x;

}//end of function
/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////
void Draw_2D_Panel_MC_andData_frompointer_DISbreakdown(MnvH2D *hist_Data, MnvH2D *hist_MC,
  MnvH2D *hist_MC_QE,
  MnvH2D *hist_MC_HeavierRES,
  MnvH2D *hist_MC_deltaRES,
  MnvH2D *hist_MC_2p2h,
  MnvH2D *hist_MC_DISSIS,
  MnvH2D *hist_MC_DISHard,
  MnvH2D *hist_MC_DISSoft,
  MnvH2D *hist_MC_Other,
  MnvH2D *hist_MC_NONE,
  bool DataStat_SysError,
  bool MC_Stat_SysError,
  char *histotitle, std::string xaxislabel,
  std::string yaxislabel,const char *Zaxislabel , double max_x, double max_y, bool setMaxY,
  char *pdf_label, bool doBinwidth, bool MakeXaxisLOG,
  double x_projectionTxtsize, double y_projectionTxtsize, bool doMultipliers, bool MakeRatio){

//bool setMaxY = true;
double headroom = 1.5;
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  myPlotStyle();
  TH1::SetDefaultSumw2();
  gStyle->SetErrorX(0);
  gStyle->SetEndErrorSize(2);

  TLegend* leg=new TLegend(0.43, 0.1, 0.98, 0.3);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.025);
  leg->SetNColumns(3);
  TH2* h_QE = new TH2D(hist_MC_QE->GetCVHistoWithStatError());
  TH2* h_HeavierRES = new TH2D(hist_MC_HeavierRES->GetCVHistoWithStatError());
  TH2* h_deltaRES = new TH2D(hist_MC_deltaRES->GetCVHistoWithStatError());
  TH2* h_2p2h = new TH2D(hist_MC_2p2h->GetCVHistoWithStatError());
  TH2* h_DISSIS = new TH2D(hist_MC_DISSIS->GetCVHistoWithStatError());
  TH2* h_DISHard = new TH2D(hist_MC_DISHard->GetCVHistoWithStatError());
  TH2* h_DISSoft = new TH2D(hist_MC_DISSoft->GetCVHistoWithStatError());
  TH2* h_Other = new TH2D(hist_MC_Other->GetCVHistoWithStatError());
  TH2* h_NONE = new TH2D(hist_MC_NONE->GetCVHistoWithStatError());
  TH2* mc_hist = new TH2D(hist_MC->GetCVHistoWithStatError());
  TH2* mcTotalError =new TH2D(hist_MC->GetCVHistoWithError());

  //TH2* mc_hist_Divide = new TH2D(hist_MC->GetCVHistoWithStatError());
  //TH2* mcTotalError_Divide =new TH2D(hist_MC->GetCVHistoWithError());

  mc_hist->SetLineColor(kRed);
  mc_hist->SetLineWidth(2);
  mcTotalError->SetFillColorAlpha(kRed, 0.5);
  mcTotalError->SetFillStyle(3144);

  TH2* dataStat = new TH2D(hist_Data->GetCVHistoWithStatError());
  TH2* data_1 = new TH2D(hist_Data->GetCVHistoWithError());

  dataStat->SetMarkerStyle(1);
  dataStat->SetLineColor(kBlack);
  dataStat->SetLineWidth(2);

  data_1->SetMarkerStyle(kFullCircle);
  data_1->SetMarkerSize(0.7);
  data_1->SetLineColor(kBlack);

  std::vector<int> Helium9_colorScheme = {
    TColor::GetColor("#F1B6DA"),//pink 11

    TColor::GetColor("#DF00FF"), //'psychedelic Purple1
    TColor::GetColor(43,206,72 ), //green 2
    TColor::GetColor("#87CEEB"),//'skyblue' 3
    TColor::GetColor("#0859C6"), //blue 4
    TColor::GetColor("#654522"), // yellowishbrown,5
    TColor::GetColor("#ffc922"), //'sunset yellow'6
    TColor::GetColor("#FF0800"),//2 candy Apple7
    TColor::GetColor("#800000"),  // Maroon
    TColor::GetColor("#90AD1C"),//8
    TColor::GetColor("#BABABA"), //Gray 9
    TColor::GetColor("#00FFFF"),//'aqua' 10
    TColor::GetColor("#AAF0D1"), // mint green
    TColor::GetColor(kRed),//'Jade' 12
    TColor::GetColor("#FAFAD2"),  // LightGoldenRodYellow 13

    TColor::GetColor("#555555"),  // dark grey 15
    TColor::GetColor(0, 153, 143 ), //turquoise 16
    TColor::GetColor("#654522"), // yellowishbrown, 17
    TColor::GetColor("#8db600"), // yellowgreen, 18
    TColor::GetColor("#D3D3D3"),  //'lightgrey' 19
    TColor::GetColor("#90AD1C"), // 20
    TColor::GetColor("#CCDDAA"), //21
    TColor::GetColor(kMagenta), //22
    TColor::GetColor("#EEFF00") // neonyellow,0
  };

  h_QE->SetLineWidth(2);        h_QE->SetLineColor(Helium9_colorScheme.at(0));
  h_2p2h->SetLineWidth(2);      h_2p2h->SetLineColor(Helium9_colorScheme.at(3));
  h_HeavierRES->SetLineWidth(2);h_HeavierRES->SetLineColor(Helium9_colorScheme.at(1));
  h_deltaRES->SetLineWidth(2);  h_deltaRES->SetLineColor(Helium9_colorScheme.at(2));
  h_DISSIS->SetLineWidth(2);    h_DISSIS->SetLineColor(Helium9_colorScheme.at(4));
  h_DISHard->SetLineWidth(2);   h_DISHard->SetLineColor(kTeal);
  h_DISSoft->SetLineWidth(2);   h_DISSoft->SetLineColor(Helium9_colorScheme.at(6));
  h_Other->SetLineWidth(2);     h_Other->SetLineColor(Helium9_colorScheme.at(9));
  h_NONE->SetLineWidth(2);      h_NONE->SetLineColor(Helium9_colorScheme.at(8));

std::vector<std::pair<TH2*, const char*> > histAndOpts;


  if (MakeRatio==true){

    data_1->Divide(mc_hist);
    dataStat->Divide(mc_hist);
    h_QE->Divide(mc_hist);
    h_HeavierRES->Divide(mc_hist);
    h_deltaRES->Divide(mc_hist);
    h_2p2h->Divide(mc_hist);
    h_DISSIS->Divide(mc_hist);
    h_DISHard->Divide(mc_hist);
    h_DISSoft->Divide(mc_hist);
    h_Other->Divide(mc_hist);
    h_NONE->Divide(mc_hist);
    mc_hist->Divide(mc_hist);


  histAndOpts.push_back(std::make_pair(dataStat,     "histp"));
  histAndOpts.push_back(std::make_pair(mc_hist,      "graph0LX"));
  histAndOpts.push_back(std::make_pair(h_QE,         "graph0LX"));
  histAndOpts.push_back(std::make_pair(h_2p2h,       "graph0LX"));
  histAndOpts.push_back(std::make_pair(h_HeavierRES, "graph0LX"));
  histAndOpts.push_back(std::make_pair(h_deltaRES,   "graph0LX"));
  histAndOpts.push_back(std::make_pair(h_DISSIS,     "graph0LX"));
  histAndOpts.push_back(std::make_pair(h_DISHard,    "graph0LX"));
  histAndOpts.push_back(std::make_pair(h_DISSoft,    "graph0LX"));
  histAndOpts.push_back(std::make_pair(h_Other,      "graph0LX"));
  histAndOpts.push_back(std::make_pair(h_NONE,       "graph0LX"));
  if(DataStat_SysError==true) { histAndOpts.push_back(std::make_pair(data_1,"graph ep"));}


  }

else{

  histAndOpts.push_back(std::make_pair(mc_hist,"hist"));
  if(MC_Stat_SysError==true) histAndOpts.push_back(std::make_pair(mcTotalError,       "graphe3"));
  histAndOpts.push_back(std::make_pair(h_QE,         "graph0LX")); //
  histAndOpts.push_back(std::make_pair(h_2p2h,       "graph0LX"));
  histAndOpts.push_back(std::make_pair(h_HeavierRES, "graph0LX"));
  histAndOpts.push_back(std::make_pair(h_deltaRES,   "graph0LX"));
  histAndOpts.push_back(std::make_pair(h_DISSIS,     "graph0LX"));
  histAndOpts.push_back(std::make_pair(h_DISHard,    "graph0LX"));
  histAndOpts.push_back(std::make_pair(h_DISSoft,    "graph0LX"));
  histAndOpts.push_back(std::make_pair(h_Other,      "graph0LX"));
  histAndOpts.push_back(std::make_pair(h_NONE,       "graph0LX"));

  if(DataStat_SysError==true) { histAndOpts.push_back(std::make_pair(data_1,"graph ep"));}
  histAndOpts.push_back(std::make_pair(dataStat,"graph e"));
}

if(DataStat_SysError==true) {leg->AddEntry(data_1, "Data[Stat+Sys]", "lpe");}
else{leg->AddEntry(dataStat, "Data[Stat]", "lpe");}

if(MC_Stat_SysError==true) leg->AddEntry(mc_hist, "MINERvA v1 [Stat+Sys]", "l");
else leg->AddEntry(mc_hist, "MINERvA v1 [Stat]", "l");

leg->AddEntry(h_QE,         "QE" , "l");
leg->AddEntry(h_2p2h,       "2p2h" , "l");
leg->AddEntry(h_HeavierRES, "Heavier RES" , "l");
leg->AddEntry(h_deltaRES,   "#Delta RES" , "l");
leg->AddEntry(h_DISSIS,     "SIS" , "l");
leg->AddEntry(h_DISHard,    "Hard DIS" , "l");
leg->AddEntry(h_DISSoft,    "Soft DIS" , "l");
leg->AddEntry(h_Other,      "Other" , "l");
leg->AddEntry(h_NONE,       "NONE" , "l");


  // I think if getscales is tru do Y projection if false do x projection
  //std::vector<double> multipliers_y = GetScales(histAndOpts, true, true);
  std::vector<double> multipliers_y = GetScales_2d(histAndOpts, false);
  GridCanvas* gc_y=plotYAxis1D(histAndOpts, xaxislabel, yaxislabel, doMultipliers ? &multipliers_y[0] : NULL, y_projectionTxtsize, doBinwidth);
  gc_y->SetYLabel_Size(.025);
  gc_y->SetXLabel_Size(.03);
  double MaxY = gc_y->GetPadMax();
  if(setMaxY==false) gc_y->SetYLimits(0,MaxY*headroom);
  else gc_y->SetYLimits(0,max_y);
  gc_y->SetYTitle(Zaxislabel);
  //gc_y->SetLogx(0);
  gc_y->SetGridx();
  if (MakeRatio==true)gc_y->SetGridy();
  if(MakeXaxisLOG==true) gc_y->SetLogx(1);
  char total_title[1024];
  sprintf(total_title, " %s [Yproj]", histotitle);

  mnvPlotter.AddHistoTitle(total_title, .035);
  if(MakeXaxisLOG==true) gc_y->SetLogx(1);
  gc_y->Modified();
  leg->Draw("SAME");
  gc_y->Print(pdf_label);
  /////////////////////////////////////////////////////////
  // I think if getscales is tru do Y projection if false do x projection
  //std::vector<double> multipliers_x = GetScales(histAndOpts, false, true);
  std::vector<double> multipliers_x = GetScales_2d(histAndOpts,  true);
  //if(MakeXaxisLOG==true) gc_x->SetLogy(0);
  GridCanvas* gc_x=plotXAxis1D(histAndOpts, yaxislabel, xaxislabel, doMultipliers ? &multipliers_x[0] : NULL, doBinwidth); // , x_projectionTxtsizec
  // Set the y range manually. Can also use gc3->Remax() to guess automatically
  gc_x->SetYLabel_Size(.025);
  gc_x->SetXLabel_Size(.03);
  double MaxX = gc_x->GetPadMax();
  if(setMaxY==false) gc_x->SetYLimits(0,MaxX*headroom);
  else gc_x->SetYLimits(0,max_x);
  gc_x->SetYTitle(Zaxislabel);
  //if(MakeXaxisLOG==true) gc_x->SetLogx(0);
  sprintf(total_title, " %s [Xproj]", histotitle);
  mnvPlotter.AddHistoTitle(total_title, .038);
  //gc_x->SetYTitle(yaxisUNITS);
  if(MakeXaxisLOG==true) gc_x->SetLogx(1);
  if (MakeRatio==true) gc_x->SetGridy();
  gc_x->SetGridx();
  gc_x->Modified();
  //leg->Draw("SAME");
  gc_x->Print(pdf_label);

  delete gc_y;
  delete gc_x;

}//end of function
/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////
void Draw_2D_Panel_MC_andData_frompointer_DISbreakdown(MnvH2D *hist_Data, MnvH2D *hist_MC,
  MnvH2D *hist_MC_QE,
  MnvH2D *hist_MC_HeavierRES,
  MnvH2D *hist_MC_deltaRES,
  MnvH2D *hist_MC_2p2h,
  MnvH2D *hist_MC_DISSIS,
  MnvH2D *hist_MC_DISHard,
  MnvH2D *hist_MC_DISSoft,
  MnvH2D *hist_MC_Other,
  MnvH2D *hist_MC_NONE,
  bool DataStat_SysError,
  bool MC_Stat_SysError,
  char *histotitle, std::string xaxislabel,
  std::string yaxislabel,const char *Zaxislabel , double max_x, double max_y, bool setMaxY,
  char *pdf_label, bool doBinwidth, bool MakeXaxisLOG,
  double x_projectionTxtsize, double y_projectionTxtsize, bool doMultipliers, std::vector<double> YMultipliers, std::vector<double> XMultipliers){

double headroom = 1.5;
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  myPlotStyle();
  TH1::SetDefaultSumw2();
  gStyle->SetErrorX(0);
  gStyle->SetEndErrorSize(2);
  TLegend* leg=new TLegend(0.43, 0.1, 0.98, 0.3);

  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.025);
  leg->SetNColumns(3);

  TH2* h_QE = new TH2D(hist_MC_QE->GetCVHistoWithStatError());
  TH2* h_HeavierRES = new TH2D(hist_MC_HeavierRES->GetCVHistoWithStatError());
  TH2* h_deltaRES = new TH2D(hist_MC_deltaRES->GetCVHistoWithStatError());
  TH2* h_2p2h = new TH2D(hist_MC_2p2h->GetCVHistoWithStatError());
  TH2* h_DISSIS = new TH2D(hist_MC_DISSIS->GetCVHistoWithStatError());
  TH2* h_DISHard = new TH2D(hist_MC_DISHard->GetCVHistoWithStatError());
  TH2* h_DISSoft = new TH2D(hist_MC_DISSoft->GetCVHistoWithStatError());
  TH2* h_Other = new TH2D(hist_MC_Other->GetCVHistoWithStatError());
  TH2* h_NONE = new TH2D(hist_MC_NONE->GetCVHistoWithStatError());

  TH2* mc_hist = new TH2D(hist_MC->GetCVHistoWithStatError());
  TH2* mcTotalError =new TH2D(hist_MC->GetCVHistoWithError());

  mc_hist->SetLineColor(kRed);
  mc_hist->SetLineWidth(2);
  mcTotalError->SetFillColorAlpha(kRed, 0.5);
  mcTotalError->SetFillStyle(3144);

  TH2* dataStat = new TH2D(hist_Data->GetCVHistoWithStatError());
  TH2* data_1 = new TH2D(hist_Data->GetCVHistoWithError());

  dataStat->SetMarkerStyle(1);
  dataStat->SetLineColor(kBlack);
  dataStat->SetLineWidth(2);

  data_1->SetMarkerStyle(kFullCircle);
  data_1->SetMarkerSize(0.7);
  data_1->SetLineColor(kBlack);

  std::vector<int> Helium9_colorScheme = {
    TColor::GetColor("#F1B6DA"),//pink 11

    TColor::GetColor("#DF00FF"), //'psychedelic Purple1
    TColor::GetColor(43,206,72 ), //green 2
    TColor::GetColor("#87CEEB"),//'skyblue' 3
    TColor::GetColor("#0859C6"), //blue 4
    TColor::GetColor("#654522"), // yellowishbrown,5
    TColor::GetColor("#ffc922"), //'sunset yellow'6
    TColor::GetColor("#FF0800"),//2 candy Apple7
    TColor::GetColor("#800000"),  // Maroon
    TColor::GetColor("#90AD1C"),//8
    TColor::GetColor("#BABABA"), //Gray 9
    TColor::GetColor("#00FFFF"),//'aqua' 10
    TColor::GetColor("#AAF0D1"), // mint green
    TColor::GetColor(kRed),//'Jade' 12
    TColor::GetColor("#FAFAD2"),  // LightGoldenRodYellow 13

    TColor::GetColor("#555555"),  // dark grey 15
    TColor::GetColor(0, 153, 143 ), //turquoise 16
    TColor::GetColor("#654522"), // yellowishbrown, 17
    TColor::GetColor("#8db600"), // yellowgreen, 18
    TColor::GetColor("#D3D3D3"),  //'lightgrey' 19
    TColor::GetColor("#90AD1C"), // 20
    TColor::GetColor("#CCDDAA"), //21
    TColor::GetColor(kMagenta), //22
    TColor::GetColor("#EEFF00") // neonyellow,0
  };

  h_QE->SetLineWidth(1.5);        h_QE->SetLineColor(Helium9_colorScheme.at(0));
  h_2p2h->SetLineWidth(1.5);      h_2p2h->SetLineColor(Helium9_colorScheme.at(3));
  h_HeavierRES->SetLineWidth(1.5);h_HeavierRES->SetLineColor(Helium9_colorScheme.at(1));
  h_deltaRES->SetLineWidth(1.5);  h_deltaRES->SetLineColor(Helium9_colorScheme.at(2));
  h_DISSIS->SetLineWidth(1.5);    h_DISSIS->SetLineColor(Helium9_colorScheme.at(4));
  h_DISHard->SetLineWidth(1.5);   h_DISHard->SetLineColor(kTeal);
  h_DISSoft->SetLineWidth(1.5);   h_DISSoft->SetLineColor(Helium9_colorScheme.at(6));
  h_Other->SetLineWidth(1.5);     h_Other->SetLineColor(Helium9_colorScheme.at(9));
  h_NONE->SetLineWidth(1.5);      h_NONE->SetLineColor(Helium9_colorScheme.at(8));

  std::vector<std::pair<TH2*, const char*> > histAndOpts;
  if(DataStat_SysError==true) {leg->AddEntry(data_1, "Data[Stat+Sys]", "lpe");}
  else{leg->AddEntry(dataStat, "Data[Stat]", "lpe");}
  histAndOpts.push_back(std::make_pair(mc_hist,"hist"));
  if(MC_Stat_SysError==true) histAndOpts.push_back(std::make_pair(mcTotalError,       "graphe3"));

  if(MC_Stat_SysError==true) leg->AddEntry(mc_hist, "MINERvA v1 [Stat+Sys]", "l");
  else leg->AddEntry(mc_hist, "MINERvA v1 [Stat]", "l");
  histAndOpts.push_back(std::make_pair(h_QE,         "graph0LX")); leg->AddEntry(h_QE,         "QE" , "l");
  histAndOpts.push_back(std::make_pair(h_2p2h,       "graph0LX")); leg->AddEntry(h_2p2h,       "2p2h" , "l");
  histAndOpts.push_back(std::make_pair(h_HeavierRES, "graph0LX")); leg->AddEntry(h_HeavierRES, "Heavier RES" , "l");
  histAndOpts.push_back(std::make_pair(h_deltaRES,   "graph0LX")); leg->AddEntry(h_deltaRES,   "#Delta RES" , "l");
  histAndOpts.push_back(std::make_pair(h_DISSIS,     "graph0LX")); leg->AddEntry(h_DISSIS,     "SIS" , "l");
  histAndOpts.push_back(std::make_pair(h_DISHard,    "graph0LX")); leg->AddEntry(h_DISHard,    "Hard DIS" , "l");
  histAndOpts.push_back(std::make_pair(h_DISSoft,    "graph0LX")); leg->AddEntry(h_DISSoft,    "Soft DIS" , "l");
  histAndOpts.push_back(std::make_pair(h_Other,      "graph0LX")); leg->AddEntry(h_Other,      "Other" , "l");
  histAndOpts.push_back(std::make_pair(h_NONE,       "graph0LX")); leg->AddEntry(h_NONE,       "NONE" , "l");

  if(DataStat_SysError==true) { histAndOpts.push_back(std::make_pair(data_1,"graph ep"));}
  histAndOpts.push_back(std::make_pair(dataStat,"graph e"));

  // I think if getscales is tru do Y projection if false do x projection
  //std::vector<double> multipliers_y = GetScales(histAndOpts, true, true);
  GridCanvas* gc_y=plotYAxis1D(histAndOpts, xaxislabel, yaxislabel, doMultipliers ? &YMultipliers[0] : NULL, y_projectionTxtsize, doBinwidth);
  gc_y->SetYLabel_Size(.025);
  gc_y->SetXLabel_Size(.03);
  double MaxY = gc_y->GetPadMax();
  std::cout<< "MaxY = "<< MaxY<<std::endl;
  if(setMaxY==false) gc_y->SetYLimits(0,MaxY*headroom);
  else gc_y->SetYLimits(0,max_y);
  gc_y->SetYTitle(Zaxislabel);
  //gc_y->SetLogx(0);
  gc_y->SetGridx();
  if(MakeXaxisLOG==true) gc_y->SetLogx(1);
  char total_title[1024];
  sprintf(total_title, " %s [Yproj]", histotitle);

  mnvPlotter.AddHistoTitle(total_title, .035);
  if(MakeXaxisLOG==true) gc_y->SetLogx(1);
  gc_y->Modified();
  leg->Draw("SAME");
  gc_y->Print(pdf_label);
  /////////////////////////////////////////////////////////
  // I think if getscales is tru do Y projection if false do x projection
  //std::vector<double> multipliers_x = GetScales(histAndOpts, false, true);
  //if(MakeXaxisLOG==true) gc_x->SetLogy(0);
  GridCanvas* gc_x=plotXAxis1D(histAndOpts, yaxislabel, xaxislabel, doMultipliers ? &XMultipliers[0] : NULL, doBinwidth); // , x_projectionTxtsizec
  // Set the y range manually. Can also use gc3->Remax() to guess automatically
  gc_x->SetYLabel_Size(.025);
  gc_x->SetXLabel_Size(.03);
  double MaxX = gc_x->GetPadMax();
    std::cout<< "MaxX = "<< MaxX<<std::endl;
  if(setMaxY==false) gc_x->SetYLimits(0,MaxX*headroom);
  else gc_x->SetYLimits(0,max_x);
  gc_x->SetYTitle(Zaxislabel);
  //if(MakeXaxisLOG==true) gc_x->SetLogx(0);
  sprintf(total_title, " %s [Xproj]", histotitle);
  mnvPlotter.AddHistoTitle(total_title, .038);
  //gc_x->SetYTitle(yaxisUNITS);
  if(MakeXaxisLOG==true) gc_x->SetLogx(1);
  gc_x->SetGridx();
  gc_x->Modified();
  //leg->Draw("SAME");
  gc_x->Print(pdf_label);

  delete gc_y;
  delete gc_x;

}//end of function
/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////
void Draw_2D_Panel_MC_andData_frompointer_DISbreakdown_STACK(MnvH2D *hist_Data, MnvH2D *hist_MC,
  MnvH2D *hist_MC_QE,
  MnvH2D *hist_MC_HeavierRES,
  MnvH2D *hist_MC_deltaRES,
  MnvH2D *hist_MC_2p2h,
  MnvH2D *hist_MC_DISSIS,
  MnvH2D *hist_MC_DISHard,
  MnvH2D *hist_MC_DISSoft,
  MnvH2D *hist_MC_Other,
  MnvH2D *hist_MC_NONE,
  bool DataStat_SysError,
  bool MC_Stat_SysError,
  char *histotitle, std::string xaxislabel,
  std::string yaxislabel,const char *Zaxislabel , double max_x, double max_y, bool setMaxY,
  char *pdf_label, bool doBinwidth, bool MakeXaxisLOG,
  double x_projectionTxtsize, double y_projectionTxtsize, bool doMultipliers,
   std::vector<double> YMultipliers, std::vector<double> XMultipliers){

double headroom = 1.5;
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  myPlotStyle();
  TH1::SetDefaultSumw2();
  gStyle->SetErrorX(0);
  gStyle->SetEndErrorSize(2);
  TLegend* leg=new TLegend(0.43, 0.1, 0.98, 0.3);

  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.025);
  leg->SetNColumns(3);

  TH2* h_QE = new TH2D(hist_MC_QE->GetCVHistoWithStatError());
  TH2* h_HeavierRES = new TH2D(hist_MC_HeavierRES->GetCVHistoWithStatError());
  TH2* h_deltaRES = new TH2D(hist_MC_deltaRES->GetCVHistoWithStatError());
  TH2* h_2p2h = new TH2D(hist_MC_2p2h->GetCVHistoWithStatError());
  TH2* h_DISSIS = new TH2D(hist_MC_DISSIS->GetCVHistoWithStatError());
  TH2* h_DISHard = new TH2D(hist_MC_DISHard->GetCVHistoWithStatError());
  TH2* h_DISSoft = new TH2D(hist_MC_DISSoft->GetCVHistoWithStatError());
  TH2* h_Other = new TH2D(hist_MC_Other->GetCVHistoWithStatError());
  TH2* h_NONE = new TH2D(hist_MC_NONE->GetCVHistoWithStatError());

  TH2* mc_hist = new TH2D(hist_MC->GetCVHistoWithStatError());
  TH2* mcTotalError =new TH2D(hist_MC->GetCVHistoWithError());


  mc_hist->SetLineColor(kRed);
  mc_hist->SetLineWidth(2);
  mcTotalError->SetFillColorAlpha(kRed, 0.5);
  mcTotalError->SetFillStyle(3144);

  TH2* dataStat = new TH2D(hist_Data->GetCVHistoWithStatError());
  TH2* data_1 = new TH2D(hist_Data->GetCVHistoWithError());

  dataStat->SetMarkerStyle(1);
  dataStat->SetLineColor(kBlack);
  dataStat->SetLineWidth(2);

  data_1->SetMarkerStyle(kFullCircle);
  data_1->SetMarkerSize(0.7);
  data_1->SetLineColor(kBlack);

  std::vector<int> Helium9_colorScheme = {
    TColor::GetColor("#F1B6DA"),//pink 11

    TColor::GetColor("#DF00FF"), //'psychedelic Purple1
    TColor::GetColor(43,206,72 ), //green 2
    TColor::GetColor("#87CEEB"),//'skyblue' 3
    TColor::GetColor("#0859C6"), //blue 4
    TColor::GetColor("#654522"), // yellowishbrown,5
    TColor::GetColor("#ffc922"), //'sunset yellow'6
    TColor::GetColor("#FF0800"),//2 candy Apple7
    TColor::GetColor("#800000"),  // Maroon
    TColor::GetColor("#90AD1C"),//8
    TColor::GetColor("#BABABA"), //Gray 9
    TColor::GetColor("#00FFFF"),//'aqua' 10
    TColor::GetColor("#AAF0D1"), // mint green
    TColor::GetColor(kRed),//'Jade' 12
    TColor::GetColor("#FAFAD2"),  // LightGoldenRodYellow 13

    TColor::GetColor("#555555"),  // dark grey 15
    TColor::GetColor(0, 153, 143 ), //turquoise 16
    TColor::GetColor("#654522"), // yellowishbrown, 17
    TColor::GetColor("#8db600"), // yellowgreen, 18
    TColor::GetColor("#D3D3D3"),  //'lightgrey' 19
    TColor::GetColor("#90AD1C"), // 20
    TColor::GetColor("#CCDDAA"), //21
    TColor::GetColor(kMagenta), //22
    TColor::GetColor("#EEFF00") // neonyellow,0
  };

  h_QE->SetLineWidth(1.5);        h_QE->SetLineColor(Helium9_colorScheme.at(0)); h_QE->SetFillColor(Helium9_colorScheme.at(0));
  h_2p2h->SetLineWidth(1.5);      h_2p2h->SetLineColor(Helium9_colorScheme.at(3)); h_2p2h->SetFillColor(Helium9_colorScheme.at(3));
  h_HeavierRES->SetLineWidth(1.5);h_HeavierRES->SetLineColor(Helium9_colorScheme.at(1)); h_HeavierRES->SetFillColor(Helium9_colorScheme.at(1));
  h_deltaRES->SetLineWidth(1.5);  h_deltaRES->SetLineColor(Helium9_colorScheme.at(2)); h_deltaRES->SetFillColor(Helium9_colorScheme.at(2));
  h_DISSIS->SetLineWidth(1.5);    h_DISSIS->SetLineColor(Helium9_colorScheme.at(4)); h_DISSIS->SetFillColor(Helium9_colorScheme.at(4));
  h_DISHard->SetLineWidth(1.5);   h_DISHard->SetLineColor(kTeal); h_DISHard->SetLineColor(kTeal);
  h_DISSoft->SetLineWidth(1.5);   h_DISSoft->SetLineColor(Helium9_colorScheme.at(6)); h_DISSoft->SetFillColor(Helium9_colorScheme.at(6));
  h_Other->SetLineWidth(1.5);     h_Other->SetLineColor(Helium9_colorScheme.at(9)); h_Other->SetFillColor(Helium9_colorScheme.at(9));
  h_NONE->SetLineWidth(1.5);      h_NONE->SetLineColor(Helium9_colorScheme.at(8)); h_NONE->SetFillColor(Helium9_colorScheme.at(8));





  std::vector<std::pair<TH2*, const char*> > histAndOpts;
  if(DataStat_SysError==true) {leg->AddEntry(data_1, "Data[Stat+Sys]", "lpe");}
  else{leg->AddEntry(dataStat, "Data[Stat]", "lpe");}
  histAndOpts.push_back(std::make_pair(mc_hist,"hist"));
  //if(MC_Stat_SysError==true) histAndOpts.push_back(std::make_pair(mcTotalError,       "graphe3"));

  if(MC_Stat_SysError==true) leg->AddEntry(mc_hist, "MINERvA v1 [Stat+Sys]", "l");
  else leg->AddEntry(mc_hist, "MINERvA v1 [Stat]", "l");
  histAndOpts.push_back(std::make_pair(h_QE,         "hist")); leg->AddEntry(h_QE,         "QE" , "l");
  histAndOpts.push_back(std::make_pair(h_2p2h,       "hist")); leg->AddEntry(h_2p2h,       "2p2h" , "l");
  histAndOpts.push_back(std::make_pair(h_HeavierRES, "hist")); leg->AddEntry(h_HeavierRES, "Heavier RES" , "l");
  histAndOpts.push_back(std::make_pair(h_deltaRES,   "hist")); leg->AddEntry(h_deltaRES,   "#Delta RES" , "l");
  histAndOpts.push_back(std::make_pair(h_DISSIS,     "hist")); leg->AddEntry(h_DISSIS,     "SIS" , "l");
  histAndOpts.push_back(std::make_pair(h_DISHard,    "hist")); leg->AddEntry(h_DISHard,    "Hard DIS" , "l");
  histAndOpts.push_back(std::make_pair(h_DISSoft,    "same hist")); leg->AddEntry(h_DISSoft,    "Soft DIS" , "l");
  histAndOpts.push_back(std::make_pair(h_Other,      "hist")); leg->AddEntry(h_Other,      "Other" , "l");
  histAndOpts.push_back(std::make_pair(h_NONE,       "hist")); leg->AddEntry(h_NONE,       "NONE" , "l");

  if(DataStat_SysError==true) { histAndOpts.push_back(std::make_pair(data_1,"graph ep"));}
  histAndOpts.push_back(std::make_pair(dataStat,"graph e"));


  // I think if getscales is tru do Y projection if false do x projection
  //std::vector<double> multipliers_y = GetScales(histAndOpts, true, true);
  GridCanvas* gc_y=plotYAxis1D(histAndOpts, xaxislabel, yaxislabel, doMultipliers ? &YMultipliers[0] : NULL, y_projectionTxtsize, doBinwidth);

  //GridCanvas* gc_y=plotYAxis1D(histAndOpts, xaxislabel, yaxislabel, doMultipliers ? &YMultipliers[0] : NULL);

  gc_y->SetYLabel_Size(.025);
  gc_y->SetXLabel_Size(.03);
  double MaxY = gc_y->GetPadMax();
  std::cout<< "MaxY = "<< MaxY<<std::endl;
  if(setMaxY==false) gc_y->SetYLimits(0,MaxY*headroom);
  else gc_y->SetYLimits(0,max_y);
  gc_y->SetYTitle(Zaxislabel);
  //gc_y->SetLogx(0);
  gc_y->SetGridx();
  if(MakeXaxisLOG==true) gc_y->SetLogx(1);
  char total_title[1024];
  sprintf(total_title, " %s [Yproj]", histotitle);

  mnvPlotter.AddHistoTitle(total_title, .035);
  if(MakeXaxisLOG==true) gc_y->SetLogx(1);
  gc_y->Modified();
  leg->Draw("SAME");
  gc_y->Print(pdf_label);
  /////////////////////////////////////////////////////////
  // I think if getscales is tru do Y projection if false do x projection
  //std::vector<double> multipliers_x = GetScales(histAndOpts, false, true);
  //if(MakeXaxisLOG==true) gc_x->SetLogy(0);
  GridCanvas* gc_x=plotXAxis1D(histAndOpts, yaxislabel, xaxislabel, doMultipliers ? &XMultipliers[0] : NULL, doBinwidth); // , x_projectionTxtsizec
  // Set the y range manually. Can also use gc3->Remax() to guess automatically
  gc_x->SetYLabel_Size(.025);
  gc_x->SetXLabel_Size(.03);
  double MaxX = gc_x->GetPadMax();
    std::cout<< "MaxX = "<< MaxX<<std::endl;
  if(setMaxY==false) gc_x->SetYLimits(0,MaxX*headroom);
  else gc_x->SetYLimits(0,max_x);
  gc_x->SetYTitle(Zaxislabel);
  //if(MakeXaxisLOG==true) gc_x->SetLogx(0);
  sprintf(total_title, " %s [Xproj]", histotitle);
  mnvPlotter.AddHistoTitle(total_title, .038);
  //gc_x->SetYTitle(yaxisUNITS);
  if(MakeXaxisLOG==true) gc_x->SetLogx(1);
  gc_x->SetGridx();
  gc_x->Modified();
  //leg->Draw("SAME");
  gc_x->Print(pdf_label);

  delete gc_y;
  delete gc_x;

}//end of function
/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////
void Draw_2D_Panel_MC_andData_frompointer_DISbreakdown_E_theta(MnvH2D *hist_Data, MnvH2D *hist_MC,
  MnvH2D *hist_MC_QE,
  MnvH2D *hist_MC_HeavierRES,
  MnvH2D *hist_MC_deltaRES,
  MnvH2D *hist_MC_2p2h,
  MnvH2D *hist_MC_DISSIS,
  MnvH2D *hist_MC_DISHard,
  MnvH2D *hist_MC_DISSoft,
  MnvH2D *hist_MC_Other,
  MnvH2D *hist_MC_NONE,
  bool DataStat_SysError,
  bool MC_Stat_SysError,
  char *histotitle, std::string xaxislabel,
  std::string yaxislabel,const char *Zaxislabel , double max_x, double max_y, bool setMaxY,
  char *pdf_label, bool doBinwidth, bool MakeXaxisLOG,
  double x_projectionTxtsize, double y_projectionTxtsize, bool doMultipliers, std::vector<double> YMultipliers, std::vector<double> XMultipliers){

double headroom = 1.5;
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  myPlotStyle();
  TH1::SetDefaultSumw2();
  gStyle->SetErrorX(0);
  gStyle->SetEndErrorSize(2);
  TLegend* leg=new TLegend(0.8, 0.01, 0.99, 0.30);

  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.025);
  leg->SetNColumns(1);

  TH2* h_QE = new TH2D(hist_MC_QE->GetCVHistoWithStatError());
  TH2* h_HeavierRES = new TH2D(hist_MC_HeavierRES->GetCVHistoWithStatError());
  TH2* h_deltaRES = new TH2D(hist_MC_deltaRES->GetCVHistoWithStatError());
  TH2* h_2p2h = new TH2D(hist_MC_2p2h->GetCVHistoWithStatError());
  TH2* h_DISSIS = new TH2D(hist_MC_DISSIS->GetCVHistoWithStatError());
  TH2* h_DISHard = new TH2D(hist_MC_DISHard->GetCVHistoWithStatError());
  TH2* h_DISSoft = new TH2D(hist_MC_DISSoft->GetCVHistoWithStatError());
  TH2* h_Other = new TH2D(hist_MC_Other->GetCVHistoWithStatError());
  TH2* h_NONE = new TH2D(hist_MC_NONE->GetCVHistoWithStatError());

  TH2* mc_hist = new TH2D(hist_MC->GetCVHistoWithStatError());
  TH2* mcTotalError =new TH2D(hist_MC->GetCVHistoWithError());

  mc_hist->SetLineColor(kRed);
  mc_hist->SetLineWidth(2);
  mcTotalError->SetFillColorAlpha(kRed, 0.5);
  mcTotalError->SetFillStyle(3144);

  TH2* dataStat = new TH2D(hist_Data->GetCVHistoWithStatError());
  TH2* data_1 = new TH2D(hist_Data->GetCVHistoWithError());

  dataStat->SetMarkerStyle(1);
  dataStat->SetLineColor(kBlack);
  dataStat->SetLineWidth(2);

  data_1->SetMarkerStyle(kFullCircle);
  data_1->SetMarkerSize(0.7);
  data_1->SetLineColor(kBlack);

  std::vector<int> Helium9_colorScheme = {
    TColor::GetColor("#F1B6DA"),//pink 11

    TColor::GetColor("#DF00FF"), //'psychedelic Purple1
    TColor::GetColor(43,206,72 ), //green 2
    TColor::GetColor("#87CEEB"),//'skyblue' 3
    TColor::GetColor("#0859C6"), //blue 4
    TColor::GetColor("#654522"), // yellowishbrown,5
    TColor::GetColor("#ffc922"), //'sunset yellow'6
    TColor::GetColor("#FF0800"),//2 candy Apple7
    TColor::GetColor("#800000"),  // Maroon
    TColor::GetColor("#90AD1C"),//8
    TColor::GetColor("#BABABA"), //Gray 9
    TColor::GetColor("#00FFFF"),//'aqua' 10
    TColor::GetColor("#AAF0D1"), // mint green
    TColor::GetColor(kRed),//'Jade' 12
    TColor::GetColor("#FAFAD2"),  // LightGoldenRodYellow 13

    TColor::GetColor("#555555"),  // dark grey 15
    TColor::GetColor(0, 153, 143 ), //turquoise 16
    TColor::GetColor("#654522"), // yellowishbrown, 17
    TColor::GetColor("#8db600"), // yellowgreen, 18
    TColor::GetColor("#D3D3D3"),  //'lightgrey' 19
    TColor::GetColor("#90AD1C"), // 20
    TColor::GetColor("#CCDDAA"), //21
    TColor::GetColor(kMagenta), //22
    TColor::GetColor("#EEFF00") // neonyellow,0
  };

  h_QE->SetLineWidth(1.5);        h_QE->SetLineColor(Helium9_colorScheme.at(0));
  h_2p2h->SetLineWidth(1.5);      h_2p2h->SetLineColor(Helium9_colorScheme.at(3));
  h_HeavierRES->SetLineWidth(1.5);h_HeavierRES->SetLineColor(Helium9_colorScheme.at(1));
  h_deltaRES->SetLineWidth(1.5);  h_deltaRES->SetLineColor(Helium9_colorScheme.at(2));
  h_DISSIS->SetLineWidth(1.5);    h_DISSIS->SetLineColor(Helium9_colorScheme.at(4));
  h_DISHard->SetLineWidth(1.5);   h_DISHard->SetLineColor(kTeal);
  h_DISSoft->SetLineWidth(1.5);   h_DISSoft->SetLineColor(Helium9_colorScheme.at(6));
  h_Other->SetLineWidth(1.5);     h_Other->SetLineColor(Helium9_colorScheme.at(9));
  h_NONE->SetLineWidth(1.5);      h_NONE->SetLineColor(Helium9_colorScheme.at(8));

  std::vector<std::pair<TH2*, const char*> > histAndOpts;
  if(DataStat_SysError==true) {leg->AddEntry(data_1, "Data[Stat+Sys]", "lpe");}
  else{leg->AddEntry(dataStat, "Data[Stat]", "lpe");}
  histAndOpts.push_back(std::make_pair(mc_hist,"hist"));
  if(MC_Stat_SysError==true) histAndOpts.push_back(std::make_pair(mcTotalError,       "graphe3"));

  if(MC_Stat_SysError==true) leg->AddEntry(mc_hist, "MINERvA v1 [Stat+Sys]", "l");
  else leg->AddEntry(mc_hist, "MINERvA v1 [Stat]", "l");
  histAndOpts.push_back(std::make_pair(h_QE,         "graph0LX")); leg->AddEntry(h_QE,         "QE" , "l");
  histAndOpts.push_back(std::make_pair(h_2p2h,       "graph0LX")); leg->AddEntry(h_2p2h,       "2p2h" , "l");
  histAndOpts.push_back(std::make_pair(h_HeavierRES, "graph0LX")); leg->AddEntry(h_HeavierRES, "Heavier RES" , "l");
  histAndOpts.push_back(std::make_pair(h_deltaRES,   "graph0LX")); leg->AddEntry(h_deltaRES,   "#Delta RES" , "l");
  histAndOpts.push_back(std::make_pair(h_DISSIS,     "graph0LX")); leg->AddEntry(h_DISSIS,     "SIS" , "l");
  histAndOpts.push_back(std::make_pair(h_DISHard,    "graph0LX")); leg->AddEntry(h_DISHard,    "Hard DIS" , "l");
  histAndOpts.push_back(std::make_pair(h_DISSoft,    "graph0LX")); leg->AddEntry(h_DISSoft,    "Soft DIS" , "l");
  histAndOpts.push_back(std::make_pair(h_Other,      "graph0LX")); leg->AddEntry(h_Other,      "Other" , "l");
  histAndOpts.push_back(std::make_pair(h_NONE,       "graph0LX")); leg->AddEntry(h_NONE,       "NONE" , "l");

  if(DataStat_SysError==true) { histAndOpts.push_back(std::make_pair(data_1,"graph ep"));}
  histAndOpts.push_back(std::make_pair(dataStat,"graph e"));

  // I think if getscales is tru do Y projection if false do x projection
  //std::vector<double> multipliers_y = GetScales(histAndOpts, true, true);
  GridCanvas* gc_y=plotYAxis1D(histAndOpts, xaxislabel, yaxislabel, doMultipliers ? &YMultipliers[0] : NULL, y_projectionTxtsize, doBinwidth);
  gc_y->SetYLabel_Size(.025);
  gc_y->SetXLabel_Size(.03);
  double MaxY = gc_y->GetPadMax();
  std::cout<< "MaxY = "<< MaxY<<std::endl;
  if(setMaxY==false) gc_y->SetYLimits(0,MaxY*headroom);
  else gc_y->SetYLimits(0,max_y);
  gc_y->SetYTitle(Zaxislabel);
  //gc_y->SetLogx(0);
  gc_y->SetGridx();
  if(MakeXaxisLOG==true) gc_y->SetLogx(1);
  char total_title[1024];
  sprintf(total_title, " %s [Yproj]", histotitle);

  mnvPlotter.AddHistoTitle(total_title, .035);
  if(MakeXaxisLOG==true) gc_y->SetLogx(1);
  gc_y->Modified();
  //leg->Draw("SAME");
  gc_y->Print(pdf_label);
  /////////////////////////////////////////////////////////
  // I think if getscales is tru do Y projection if false do x projection
  //std::vector<double> multipliers_x = GetScales(histAndOpts, false, true);
  //if(MakeXaxisLOG==true) gc_x->SetLogy(0);
  GridCanvas* gc_x=plotXAxis1D(histAndOpts, yaxislabel, xaxislabel, doMultipliers ? &XMultipliers[0] : NULL, doBinwidth); // , x_projectionTxtsizec
  // Set the y range manually. Can also use gc3->Remax() to guess automatically
  gc_x->SetYLabel_Size(.025);
  gc_x->SetXLabel_Size(.03);
  double MaxX = gc_x->GetPadMax();
    std::cout<< "MaxX = "<< MaxX<<std::endl;
  if(setMaxY==false) gc_x->SetYLimits(0,MaxX*headroom);
  else gc_x->SetYLimits(0,max_x);
  gc_x->SetYTitle(Zaxislabel);
  //if(MakeXaxisLOG==true) gc_x->SetLogx(0);
  sprintf(total_title, " %s [Xproj]", histotitle);
  mnvPlotter.AddHistoTitle(total_title, .038);
  //gc_x->SetYTitle(yaxisUNITS);
  if(MakeXaxisLOG==true) gc_x->SetLogx(1);
  gc_x->SetGridx();
  gc_x->Modified();
  leg->Draw("SAME");
  gc_x->Print(pdf_label);

  delete gc_y;
  delete gc_x;

}//end of function
/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////
void Draw_2D_Panel_MC_Only_frompointer(MnvH2D *hist, char *histotitle,
   char *legend_title, std::string xaxislabel, std::string Xunits,
   std::string yaxislabel, std::string Yunits,  std::string Zaxislabel ,
   double headroom, char *pdf_label, bool doBinwidth, bool MakeXaxisLOG,
    double x_projectionTxtsize, double y_projectionTxtsize,   bool doMultipliers ){

      PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
      myPlotStyle();
      TH1::SetDefaultSumw2();
      gStyle->SetErrorX(0);
      gStyle->SetEndErrorSize(2);

      TH2* mc_hist=new TH2D(hist->GetCVHistoWithStatError());

      mc_hist->SetLineColor(kRed);
      mc_hist->SetLineWidth(2);
      std::vector<std::pair<TH2*, const char*> > histAndOpts_MC;
      histAndOpts_MC.push_back(std::make_pair(mc_hist,"hist"));

      TLegend* leg=new TLegend(0.7, 0.08, 0.9, 0.32);
      leg->SetFillStyle(0);
      leg->SetBorderSize(0);
      leg->SetTextSize(0.025);
      leg->AddEntry(mc_hist, legend_title, "l");

      TLegend* leg2=new TLegend(0.7, 0.08, 0.9, 0.32);
      leg2->SetFillStyle(0);
      leg2->SetBorderSize(0);
      leg2->SetTextSize(0.025);
      leg2->AddEntry(mc_hist, legend_title, "l");

      //bool doMultipliers=true;

      // I think if getscales is tru do Y projection if false do x projection
      //std::vector<double> multipliers_y = GetScales(histAndOpts_MC, true, true);
      std::vector<double> multipliers_y = GetScales(histAndOpts_MC, true, true);
    //  std::reverse(multipliers_y.begin(), multipliers_y.end());
      GridCanvas* gc_y=plotYAxis1D(histAndOpts_MC, xaxislabel, yaxislabel, doMultipliers ? &multipliers_y[0] : NULL, y_projectionTxtsize, doBinwidth);
      gc_y->SetYLabel_Size(.025);
      gc_y->SetXLabel_Size(.03);
      double MaxY = gc_y->GetPadMax();
      gc_y->SetYLimits(0,MaxY*headroom);

      std::string Zaxislabel_stringY;
      if(doBinwidth==true)Zaxislabel_stringY = Zaxislabel + " /[" + Yunits + "]";
      else Zaxislabel_stringY = Zaxislabel;
      char Zaxislabel_stringY_char[Zaxislabel_stringY.length()+1];
      strcpy( Zaxislabel_stringY_char,Zaxislabel_stringY.c_str());
      gc_y->SetYTitle(Zaxislabel_stringY_char);
      //gc_y->SetLogx(0);
      gc_y->SetGridx();
      if(MakeXaxisLOG==true) gc_y->SetLogx(1);
      char total_title[1024];
      sprintf(total_title, " %s [Yproj]", histotitle);

      mnvPlotter.AddHistoTitle(total_title, .035);
      if(MakeXaxisLOG==true) gc_y->SetLogx(1);
      gc_y->Modified();
      leg->Draw("SAME");
      gc_y->Print(pdf_label);

      /////////////////////////////////////////////////////////
      // I think if getscales is tru do Y projection if false do x projection
      std::vector<double> multipliers_x = GetScales(histAndOpts_MC, false, true);
      //std::reverse(multipliers_x.begin(), multipliers_x.end());
      //if(MakeXaxisLOG==true) gc_x->SetLogy(0);
      GridCanvas* gc_x=plotXAxis1D(histAndOpts_MC, yaxislabel, xaxislabel, doMultipliers ? &multipliers_x[0] : NULL, doBinwidth); // , x_projectionTxtsize
      // Set the y range manually. Can also use gc3->Remax() to guess automatically
      gc_x->SetYLabel_Size(.025);
      gc_x->SetXLabel_Size(.03);
      double MaxX = gc_x->GetPadMax();
      gc_x->SetYLimits(0,MaxX*headroom);
      std::string Zaxislabel_stringX;
      if(doBinwidth==true)Zaxislabel_stringX = Zaxislabel + "/[" + Xunits + "]";
      else Zaxislabel_stringX = Zaxislabel;
      char Zaxislabel_stringX_char[Zaxislabel_stringX.length()+1];
      strcpy( Zaxislabel_stringX_char,Zaxislabel_stringX.c_str());
      gc_x->SetYTitle(Zaxislabel_stringX_char);
      //if(MakeXaxisLOG==true) gc_x->SetLogx(0);
      sprintf(total_title, " %s [Xproj]", histotitle);
      mnvPlotter.AddHistoTitle(total_title, .038);
      //gc_x->SetYTitle(yaxisUNITS);
      if(MakeXaxisLOG==true) gc_x->SetLogx(1);
      gc_x->SetGridx();
      gc_x->Modified();
      leg2->Draw("SAME");
      gc_x->Print(pdf_label);

      delete gc_x;
      delete gc_y;

}//end of function
/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////
void Draw_2D_Panel_MC_Only_frompointer_WithErrorBand(MnvH2D *hist, char *histotitle,
   char *legend_title, std::string xaxislabel, std::string Xunits,
   std::string yaxislabel, std::string Yunits,  std::string Zaxislabel ,
   double headroom, char *pdf_label, bool doBinwidth, bool MakeXaxisLOG,
    double x_projectionTxtsize, double y_projectionTxtsize,   bool doMultipliers ){

      PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
      myPlotStyle();
      TH1::SetDefaultSumw2();
      gStyle->SetErrorX(0);
      gStyle->SetEndErrorSize(2);

      TH2* mc_hist = new TH2D(hist->GetCVHistoWithStatError());
      TH2* mcTotalError =new TH2D(hist->GetCVHistoWithError());
      mcTotalError->SetLineColor(kRed);
      mcTotalError->SetLineWidth(2);
      mcTotalError->SetFillColorAlpha(kRed, 0.5);
      mcTotalError->SetFillStyle(3144);

      mc_hist->SetLineColor(kRed);
      mc_hist->SetLineWidth(2);
      std::vector<std::pair<TH2*, const char*> > histAndOpts_MC;

      histAndOpts_MC.push_back(std::make_pair(mcTotalError,       "graphe3"));
      histAndOpts_MC.push_back(std::make_pair(mc_hist,"hist"));

      TLegend* leg=new TLegend(0.7, 0.08, 0.9, 0.32);
      leg->SetFillStyle(0);
      leg->SetBorderSize(0);
      leg->SetTextSize(0.03);
      leg->AddEntry(mc_hist, legend_title, "l");

      TLegend* leg2=new TLegend(0.7, 0.08, 0.9, 0.32);
      leg2->SetFillStyle(0);
      leg2->SetBorderSize(0);
      leg2->SetTextSize(0.03);
      leg2->AddEntry(mc_hist, legend_title, "l");

      //bool doMultipliers=true;

      // I think if getscales is tru do Y projection if false do x projection
      //std::vector<double> multipliers_y = GetScales(histAndOpts_MC, true, true);
      std::vector<double> multipliers_y = GetScales(histAndOpts_MC, true, true);
    //  std::reverse(multipliers_y.begin(), multipliers_y.end());
      GridCanvas* gc_y=plotYAxis1D(histAndOpts_MC, xaxislabel, yaxislabel, doMultipliers ? &multipliers_y[0] : NULL, y_projectionTxtsize, doBinwidth);
      gc_y->SetYLabel_Size(.025);
      gc_y->SetXLabel_Size(.03);
      double MaxY = gc_y->GetPadMax();
      gc_y->SetYLimits(0,MaxY*headroom);

      std::string Zaxislabel_stringY;
      if(doBinwidth==true)Zaxislabel_stringY = Zaxislabel + " /[" + Yunits + "]";
      else Zaxislabel_stringY = Zaxislabel;
      char Zaxislabel_stringY_char[Zaxislabel_stringY.length()+1];
      strcpy( Zaxislabel_stringY_char,Zaxislabel_stringY.c_str());
      gc_y->SetYTitle(Zaxislabel_stringY_char);
      //gc_y->SetLogx(0);
      gc_y->SetGridx();
      if(MakeXaxisLOG==true) gc_y->SetLogx(1);
      char total_title[1024];
      sprintf(total_title, " %s [Yproj]", histotitle);

      mnvPlotter.AddHistoTitle(total_title, .035);
      if(MakeXaxisLOG==true) gc_y->SetLogx(1);
      gc_y->Modified();
      leg->Draw("SAME");
      gc_y->Print(pdf_label);

      /////////////////////////////////////////////////////////
      // I think if getscales is tru do Y projection if false do x projection
      std::vector<double> multipliers_x = GetScales(histAndOpts_MC, false, true);
      //std::reverse(multipliers_x.begin(), multipliers_x.end());
      //if(MakeXaxisLOG==true) gc_x->SetLogy(0);
      GridCanvas* gc_x=plotXAxis1D(histAndOpts_MC, yaxislabel, xaxislabel, doMultipliers ? &multipliers_x[0] : NULL, doBinwidth); // , x_projectionTxtsize
      // Set the y range manually. Can also use gc3->Remax() to guess automatically
      gc_x->SetYLabel_Size(.025);
      gc_x->SetXLabel_Size(.03);
      double MaxX = gc_x->GetPadMax();
      gc_x->SetYLimits(0,MaxX*headroom);
      std::string Zaxislabel_stringX;
      if(doBinwidth==true)Zaxislabel_stringX = Zaxislabel + "/[" + Xunits + "]";
      else Zaxislabel_stringX = Zaxislabel;
      char Zaxislabel_stringX_char[Zaxislabel_stringX.length()+1];
      strcpy( Zaxislabel_stringX_char,Zaxislabel_stringX.c_str());
      gc_x->SetYTitle(Zaxislabel_stringX_char);
      //if(MakeXaxisLOG==true) gc_x->SetLogx(0);
      sprintf(total_title, " %s [Xproj]", histotitle);
      mnvPlotter.AddHistoTitle(total_title, .038);
      //gc_x->SetYTitle(yaxisUNITS);
      if(MakeXaxisLOG==true) gc_x->SetLogx(1);
      gc_x->SetGridx();
      gc_x->Modified();
      leg2->Draw("SAME");
      gc_x->Print(pdf_label);

      delete gc_x;
      delete gc_y;

}//end of function
/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////
void Draw_2D_Panel_MC_Only_frompointer_XProjection(MnvH2D *hist,
  char *histotitle, char *legend_title, std::string xaxislabel,
   std::string yaxislabel, const char *Zaxislabel ,
  double max_x, char *pdf_label, bool doBinwidth, bool MakeXaxisLOG){
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  myPlotStyle();
  TH1::SetDefaultSumw2();
  gStyle->SetErrorX(0);
  gStyle->SetEndErrorSize(2);


  TH2* mc_hist=new TH2D(hist->GetCVHistoWithStatError());

  if(doBinwidth==true){
    mc_hist->Scale(1.0,"width");
  }

  mc_hist->SetLineColor(kRed);
  mc_hist->SetLineWidth(2);
  std::vector<std::pair<TH2*, const char*> > histAndOpts_MC;
  histAndOpts_MC.push_back(std::make_pair(mc_hist,"hist"));

  TLegend* leg=new TLegend(0.7, 0.08, 0.9, 0.32);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.025);
  leg->AddEntry(mc_hist, legend_title, "l");

  bool doMultipliers=true;
  /////////////////////////////////////////////////////////
  // I think if getscales is tru do Y projection if false do x projection
  std::vector<double> multipliers_x = GetScales(histAndOpts_MC, false, true);
  //if(MakeXaxisLOG==true) gc_x->SetLogy(0);
  GridCanvas* gc_x=plotXAxis1D(histAndOpts_MC, yaxislabel, xaxislabel, doMultipliers ? &multipliers_x[0] : NULL);
  // Set the y range manually. Can also use gc3->Remax() to guess automatically
  gc_x->SetYLimits(0,max_x);
  gc_x->SetYTitle(Zaxislabel);
  if(MakeXaxisLOG==true) gc_x->SetLogy(1);
  char total_title[1024];
  sprintf(total_title, " %s [Xproj]", histotitle);
  mnvPlotter.AddHistoTitle(total_title, .035);
  //gc_x->SetYTitle(yaxisUNITS);
  gc_x->Modified();
  leg->Draw("SAME");
  gc_x->Print(pdf_label);
  if(MakeXaxisLOG==true) gc_x->SetLogx(0);

delete gc_x;

}//end of function
/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////

void Draw_2D_Panel_MC_Only_frompointer_YProjection(MnvH2D *hist, char *histotitle,
  char *legend_title, std::string xaxislabel, std::string yaxislabel,
  const char *Zaxislabel, double max_y, char *pdf_label, bool doBinwidth, bool MakeXaxisLOG){
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  myPlotStyle();
  TH1::SetDefaultSumw2();
  gStyle->SetErrorX(0);
  gStyle->SetEndErrorSize(2);


  TH2* mc_hist=new TH2D(hist->GetCVHistoWithStatError());

  if(doBinwidth==true){
    mc_hist->Scale(1.0,"width");
  }

  mc_hist->SetLineColor(kRed);
  mc_hist->SetLineWidth(2);
  std::vector<std::pair<TH2*, const char*> > histAndOpts_MC;
  histAndOpts_MC.push_back(std::make_pair(mc_hist,"hist"));

  TLegend* leg=new TLegend(0.7, 0.08, 0.9, 0.32);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.025);
  leg->AddEntry(mc_hist, legend_title, "l");

  bool doMultipliers=true;

  // I think if getscales is tru do Y projection if false do x projection
  std::vector<double> multipliers_y = GetScales(histAndOpts_MC, true, true);

  GridCanvas* gc_y=plotYAxis1D(histAndOpts_MC, xaxislabel, yaxislabel, doMultipliers ? &multipliers_y[0] : NULL);
  gc_y->SetYLimits(0,max_y);
  gc_y->SetYTitle(Zaxislabel);

  if(MakeXaxisLOG==true) gc_y->SetLogy(0);
  char total_title[1024];
  sprintf(total_title, " %s [Yproj]", histotitle);

  mnvPlotter.AddHistoTitle(total_title, .035);
  gc_y->Modified();
  leg->Draw("SAME");
  gc_y->Print(pdf_label);
  if(MakeXaxisLOG==true) gc_y->SetLogx(1);

  delete gc_y;
}//end of function
///////////////////////////////////////////////////
void DrawTGraph(TGraphErrors *g_TGraph, const char* xaxislabel,const char* yaxislabel,
   const char* Title, const char* legend_Title,
   const char* pdf, TCanvas *can, MnvPlotter *plot, bool MakeXaxisLOG, bool MakeYaxisLOG ){
  double x1, x2, y1, y2;

    plot->DecodeLegendPosition(x1, y1, x2 , y2, "TR", 6.5, 6., .025);
    TLegend *legend = new TLegend (x1+.05, y1+.15, x2,y2);

    if(MakeXaxisLOG==true){
      gPad->SetLogx();
    }
    if(MakeYaxisLOG==true){
      gPad->SetLogy();
    }

    string TotalTitle = string(Title);

    g_TGraph -> SetTitle("");
    g_TGraph -> GetXaxis() -> SetTitle(xaxislabel);
    g_TGraph -> GetYaxis() -> SetTitle(yaxislabel);
    g_TGraph -> GetXaxis() -> CenterTitle();
    g_TGraph -> GetYaxis() -> CenterTitle();
    g_TGraph -> GetXaxis() -> SetTitleSize(0.038);
    g_TGraph -> GetYaxis() -> SetTitleSize(0.038);

    g_TGraph -> SetLineColor(2);
    g_TGraph -> SetMarkerColor(2);
    //TAxis *Xaxis = g_TGraph->GetXaxis();
    g_TGraph->GetXaxis()->SetNdivisions(30, kTRUE);
    g_TGraph->GetYaxis()->SetNdivisions(25, kTRUE);
    g_TGraph->GetYaxis()->SetLabelSize(0.025);
    g_TGraph->GetXaxis()->SetLabelSize(0.015);
   //TCanvas *optcan = new TCanvas("optcan");
   g_TGraph -> Draw("AP");

   legend -> SetTextSize(0.025);
   legend -> SetFillColor(0);
   legend -> AddEntry(g_TGraph, legend_Title, "P");
   legend -> Draw();
   plot -> AddHistoTitle(TotalTitle.c_str() , .04);
   plot -> WritePreliminary("TL", .035, 0, 0, false);

   gPad->Update();
   can->Modified();
   can->Print(pdf);
   can->Closed();


   if(MakeXaxisLOG==true){
     gPad->SetLogx(0);
   }
   if(MakeYaxisLOG==true){
     gPad->SetLogy(0);
   }




return;

}
/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////

void DrawTGraph(TGraph *g_TGraph, const char* xaxislabel,const char* yaxislabel,
   const char* Title, const char* legend_Title,
   const char* pdf, TCanvas *can, MnvPlotter *plot, bool MakeXaxisLOG, bool MakeYaxisLOG ){
  double x1, x2, y1, y2;

    plot->DecodeLegendPosition(x1, y1, x2 , y2, "TR", 6.5, 6., .025);
    TLegend *legend = new TLegend (x1+.05, y1+.15, x2,y2);

    if(MakeXaxisLOG==true){
      gPad->SetLogx();
    }
    if(MakeYaxisLOG==true){
      gPad->SetLogy();
    }

    string TotalTitle = string(Title);

    g_TGraph -> SetTitle("");
    g_TGraph -> GetXaxis() -> SetTitle(xaxislabel);
    g_TGraph -> GetYaxis() -> SetTitle(yaxislabel);
    g_TGraph -> GetXaxis() -> CenterTitle();
    g_TGraph -> GetYaxis() -> CenterTitle();
    g_TGraph -> GetXaxis() -> SetTitleSize(0.038);
    g_TGraph -> GetYaxis() -> SetTitleSize(0.038);

    g_TGraph -> SetLineColor(2);
    g_TGraph -> SetMarkerColor(2);
    //TAxis *Xaxis = g_TGraph->GetXaxis();
    g_TGraph->GetYaxis()->SetLabelSize(0.025);
    g_TGraph->GetXaxis()->SetLabelSize(0.015);
   //TCanvas *optcan = new TCanvas("optcan");
   g_TGraph -> Draw("AP");

   legend -> SetTextSize(0.025);
   legend -> SetFillColor(0);
   legend -> AddEntry(g_TGraph, legend_Title, "P");
   legend -> Draw();
   plot -> AddHistoTitle(TotalTitle.c_str() , .04);
   plot -> WritePreliminary("TL", .035, 0, 0, false);



   gPad->Update();
   can->Modified();
   can->Print(pdf);
   can->Closed();


   if(MakeXaxisLOG==true){
     gPad->SetLogx(0);
   }
   if(MakeYaxisLOG==true){
     gPad->SetLogy(0);
   }




return;

}
/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////


void DrawTGraph_GaussianFit(TGraph *g_TGraph, const char* xaxislabel,const char* yaxislabel,
   const char* Title, const char* legend_Title,
   const char* pdf, TCanvas *can, MnvPlotter *plot, bool MakeXaxisLOG, bool MakeYaxisLOG, double MinXfit, double MaxXfit ){
  double x1, x2, y1, y2;

    plot->DecodeLegendPosition(x1, y1, x2 , y2, "TR", 6.5, 6., .025);
    TLegend *legend = new TLegend (x1+.05, y1+.15, x2,y2);

    if(MakeXaxisLOG==true){
      gPad->SetLogx();
    }
    if(MakeYaxisLOG==true){
      gPad->SetLogy();
    }

    string TotalTitle = string(Title);

    g_TGraph -> SetTitle("");
    g_TGraph -> GetXaxis() -> SetTitle(xaxislabel);
    g_TGraph -> GetYaxis() -> SetTitle(yaxislabel);
    g_TGraph -> GetXaxis() -> CenterTitle();
    g_TGraph -> GetYaxis() -> CenterTitle();
    g_TGraph -> GetXaxis() -> SetTitleSize(0.038);
    g_TGraph -> GetYaxis() -> SetTitleSize(0.038);

    g_TGraph -> SetLineColor(2);
    g_TGraph -> SetMarkerColor(2);
    //TAxis *Xaxis = g_TGraph->GetXaxis();
    g_TGraph->GetYaxis()->SetLabelSize(0.025);
    g_TGraph->GetXaxis()->SetLabelSize(0.015);
   //TCanvas *optcan = new TCanvas("optcan");
   g_TGraph -> Draw("AP");

   legend -> SetTextSize(0.025);
   legend -> SetFillColor(0);
   legend -> AddEntry(g_TGraph, legend_Title, "P");
   //legend -> Draw();
   plot -> AddHistoTitle(TotalTitle.c_str() , .03);
   plot -> WritePreliminary("TL", .035, 0, 0, false);

     TF1 *gfit = new TF1("Gaussian","gaus",MinXfit,MaxXfit); // Create the fit function
     gfit->SetParNames("Constant","Mean_value","Sigma");
     gfit->SetParameters(g_TGraph->GetMaximum(),g_TGraph->GetMean(),g_TGraph->GetRMS());
     g_TGraph->Fit(gfit,"RQ");

     gfit->SetLineColor(4);



     //TPaveStats *st = (TPaveStats*)gfit->FindObject("stats");
     //st->SetY1NDC(.6);
     //st->SetY2NDC(.85);

     gStyle->SetOptFit(1111);
     gfit->Draw("same l");


   gPad->Update();
   can->Modified();
   can->Print(pdf);
   can->Closed();


   if(MakeXaxisLOG==true){
     gPad->SetLogx(0);
   }
   if(MakeYaxisLOG==true){
     gPad->SetLogy(0);
   }




return;

}

/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////

void DrawTGraph_PolyFit(TGraph *g_TGraph, const char* xaxislabel,const char* yaxislabel,
   const char* Title, const char* legend_Title,const char* legend_Title_fit,
   const char* pdf, TCanvas *can, MnvPlotter *plot, bool MakeXaxisLOG, bool MakeYaxisLOG, double MinXfit, double MaxXfit, char *functionName  ){
  double x1, x2, y1, y2;

    plot->DecodeLegendPosition(x1, y1, x2 , y2, "R", 6.5, 6., .025);
    TLegend *legend = new TLegend (x1-.06, y1-.2, x2+.01, y2-.2);
    legend->SetBorderSize(0);
    if(MakeXaxisLOG==true){
      gPad->SetLogx();
    }
    if(MakeYaxisLOG==true){
      gPad->SetLogy();
    }

    string TotalTitle = string(Title);

    g_TGraph -> SetTitle("");
    g_TGraph -> GetXaxis() -> SetTitle(xaxislabel);
    g_TGraph -> GetYaxis() -> SetTitle(yaxislabel);
    g_TGraph -> GetXaxis() -> CenterTitle();
    g_TGraph -> GetYaxis() -> CenterTitle();
    g_TGraph -> GetXaxis() -> SetTitleSize(0.038);
    g_TGraph -> GetYaxis() -> SetTitleSize(0.038);

    g_TGraph -> SetLineColor(2);
    g_TGraph -> SetMarkerColor(2);
    //TAxis *Xaxis = g_TGraph->GetXaxis();
    g_TGraph->GetYaxis()->SetLabelSize(0.025);
    g_TGraph->GetXaxis()->SetLabelSize(0.015);
   //TCanvas *optcan = new TCanvas("optcan");
   g_TGraph -> Draw("AP");
   legend -> SetTextSize(0.025);
   legend -> SetFillColor(0);

   //legend -> Draw();
   plot -> AddHistoTitle(TotalTitle.c_str() , .03);
   plot -> WritePreliminary("TL", .035, 0, 0, false);

   TF1 *gfit = new TF1("gfit",functionName,MinXfit,MaxXfit);
   g_TGraph->Fit(gfit,"RQ");
   double chi_2 = gfit->GetChisquare();
   int  ndf = gfit->GetNDF();
   double chi_ndf = chi_2 / (double)ndf;
   gfit->SetLineColor(4);
   gfit->Draw("same l");
   can->Update();
   //double step = 1;
   //std::vector<double> secondDerivatives;
   //std::vector<double> secondDerivativesInput;
   //for(double x = 25; x <= 100; x += step){
  //     double secondDeriv = gfit->Derivative2(x);
  //     secondDerivativesInput.push_back(secondDeriv);
  //     secondDerivatives.push_back(x);
   //}
   double maxElem =   FindMaxSecondDerivative(gfit, 10, 100);
   //auto  maxElem_ = std::max_element(secondDerivativesInput.begin(), secondDerivativesInput.end());
   //double maxElem = *maxElem_;
   TLine* line = new TLine(maxElem, can->GetUymin(), maxElem, can->GetUymax());
   line->SetLineColor(kRed);
   line->SetLineWidth(2);
   line->SetLineStyle(2);
   line->Draw("same");

   // Update the canvas
   can->Update();

   legend -> SetTextSize(0.025);
   legend -> SetFillColor(0);

   legend -> AddEntry(g_TGraph, legend_Title, "P");
   legend -> AddEntry(gfit, legend_Title_fit , "l");
   legend -> AddEntry(line, "Max Curvature" , "l");
   char label[1024];
   sprintf(label, "#lambda = %.2f ", maxElem);
   legend -> AddEntry((TObject*)0, label, "");
   sprintf(label, "#chi^{2}/ndf = %.2f / %i = %.2f ", chi_2,ndf,chi_ndf);
      legend -> AddEntry((TObject*)0, label, "");
   legend -> Draw();


     //TPaveStats *st = (TPaveStats*)gfit->FindObject("stats");
     //st->SetY1NDC(.6);
     //st->SetY2NDC(.85);

     gStyle->SetOptFit(1111);
     gfit->Draw("same l");
     line->Draw("same");

   gPad->Update();
   can->Modified();
   can->Print(pdf);
   can->Closed();


   if(MakeXaxisLOG==true){
     gPad->SetLogx(0);
   }
   if(MakeYaxisLOG==true){
     gPad->SetLogy(0);
   }




return;

}
/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////

void DrawTGraph_withArrow(TGraphErrors *g_TGraph, const char* xaxislabel,const char* yaxislabel, const char* Title,const char* legend_Title,
   const char* pdf, TCanvas *can, MnvPlotter *plot, bool MakeXaxisLOG, bool MakeYaxisLOG, const double cut_location,
    const double y1_arrow, const double y2_arrow, const double arrow_length,  const std::string arrow_direction ){
  double x1, x2, y1, y2;

    plot->DecodeLegendPosition(x1, y1, x2 , y2, "TR", 6.5, 6., .025);
    TLegend *legend = new TLegend (x1+.05, y1+.15, x2,y2);

    if(MakeXaxisLOG==true){
      gPad->SetLogx();
    }
    if(MakeYaxisLOG==true){
      gPad->SetLogy();
    }

    string TotalTitle = string(Title);

    g_TGraph -> SetTitle("");
    g_TGraph -> GetXaxis() -> SetTitle(xaxislabel);
    g_TGraph -> GetYaxis() -> SetTitle(yaxislabel);
    g_TGraph -> GetXaxis() -> CenterTitle();
    g_TGraph -> GetYaxis() -> CenterTitle();
    g_TGraph -> GetXaxis() -> SetTitleSize(0.038);
    g_TGraph -> GetYaxis() -> SetTitleSize(0.038);
    double max = g_TGraph->GetHistogram()->GetMaximum()*1.25;
    g_TGraph -> SetMaximum(max);
    g_TGraph -> SetLineColor(2);
    g_TGraph -> SetMarkerColor(2);
    //TAxis *Xaxis = g_TGraph->GetXaxis();
    g_TGraph->GetXaxis()->SetNdivisions(30, kTRUE);
    g_TGraph->GetYaxis()->SetNdivisions(25, kTRUE);
    g_TGraph->GetYaxis()->SetLabelSize(0.025);
    g_TGraph->GetXaxis()->SetLabelSize(0.015);
   //TCanvas *optcan = new TCanvas("optcan");
   g_TGraph -> Draw("AP");

   legend -> SetTextSize(0.025);
   legend -> SetFillColor(0);
   legend -> AddEntry(g_TGraph, legend_Title, "P");
   legend -> Draw();

   plot ->AddCutArrow(cut_location, y1_arrow,  y2_arrow,  arrow_length, arrow_direction);
   plot -> AddHistoTitle(TotalTitle.c_str() , .04);
   plot -> WritePreliminary("TL", .035, 0, 0, false);

   gPad->Update();
   can->Modified();
   can->Print(pdf);
   can->Closed();


   if(MakeXaxisLOG==true){
     gPad->SetLogx(0);
   }
   if(MakeYaxisLOG==true){
     gPad->SetLogy(0);
   }




return;

}

/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////

void Draw1DFit_withBand(std::vector<double> Axis_X, std::vector<double> Axis_Y,  char* xaxislabel, char* yaxislabel,
    char* Title, char* pdf, TCanvas *can, MnvPlotter *plot){

      //TCanvas cE ("c1","c1");

      TH1D *hist = new TH1D("hist","hist", Axis_X.size()-1, Axis_X.data());
      int NBins = hist->GetNbinsX();
      for(int i = 1; i <= NBins; ++i){
        hist->SetBinContent(i,Axis_Y.at(i-1));
    }

    hist->GetXaxis()->CenterTitle();
    hist->GetYaxis()->CenterTitle();
    hist->GetXaxis()->SetTitle(xaxislabel);
    hist->GetYaxis()->SetTitle(yaxislabel);
    hist->GetXaxis()->SetTitleSize(0.038);
    hist->GetYaxis()->SetTitleSize(0.038);
    hist->Draw();

    TF1 *parabola = new TF1("parabola", "[0]+[1]*x+[2]*x**2", Axis_Y.front(), Axis_Y.back());
    TF1 *parabola_1 = new TF1("parabola_1", "[0]+[1]*(x-[3])+[2]*(x-[3])**2", Axis_Y.front(), Axis_Y.back());
    TF1 *parabola_2 = new TF1("parabola_2", "[0]+[1]*(x+[3])+[2]*(x+[3])**2", Axis_Y.front(), Axis_Y.back());
    TF1 *line = new TF1("parabola_2", "[0]+[1]*x", Axis_Y.front(), Axis_Y.back());

    parabola->SetLineColor(kRed);
    parabola->SetLineWidth(2);
    hist->Fit(parabola, "Q");
    gStyle->SetOptFit(1111);
    gPad->Update();
    auto a = parabola->GetParameter(0);
    auto b = parabola->GetParameter(1);
    auto c = parabola->GetParameter(2);
    auto a_error =  parabola->GetParError(0);
    auto b_error =  parabola->GetParError(1);
    auto c_error =  parabola->GetParError(2);

    //parabola_1->SetParameters(a,b,c);
    //parabola_2->SetParameters(a,b,c);
    parabola_1->SetParameter(0,a);
    parabola_1->SetParameter(1,b);
    parabola_1->SetParameter(2,c);
    parabola_1->SetParameter(3,10);
    parabola_2->SetParameter(0,a);
    parabola_2->SetParameter(1,b);
    parabola_2->SetParameter(2,c);
    parabola_2->SetParameter(3,10);
    parabola_1->SetLineColor(kGreen);
    parabola_1->SetLineWidth(2);
    parabola_2->SetLineColor(kBlue);
    parabola_2->SetLineWidth(2);
    line->SetParameter(0,1);
    double slope = 1/50.0;
    line->SetParameter(1,slope);
    double x1,y1,x2,y2;
    plot->DecodeLegendPosition(x1, y1, x2, y2, "TR", 6.5, 6., .025);
    TLegend *legend = new TLegend(x1, y1 , x2 , y2   );
    char Fit[1024];
    legend->AddEntry(hist, "#chi^{2}", "fl");
    legend->AddEntry(parabola, "Fit parabola ", "fl");
    legend->AddEntry(parabola_2, "Fit parabola +4", "l");
    legend->AddEntry(parabola_1, "Fit parabola -4", "l");
    sprintf(Fit ,     "a+bx+cx^{2}" );
    legend->AddEntry((TObject*)0, Fit, ""); // to put fit param
     sprintf(Fit ,     "a=%.2f #pm %.3f",a, a_error );
     legend->AddEntry((TObject*)0, Fit, ""); // to put fit param
     sprintf(Fit ,     "b=%.2f #pm %.3f",b, b_error );
     legend->AddEntry((TObject*)0, Fit, ""); // to put fit param
     sprintf(Fit ,     "c=%.2f #pm %.3f",c, c_error );
     legend->AddEntry((TObject*)0, Fit, ""); // to put fit param


    //TH1D *hint = new TH1D("hint", "hint",  Axis_X.size()-1, Axis_X.data());
    //(TVirtualFitter::GetFitter())->GetConfidenceIntervals(hint);
    //Now the "hint" hisstogram has the fitted function values as the
    //bin contents and the confidence intervals as bin errors
    //hint->SetStats(false);
    //hint->SetFillColorAlpha(kRed, 0.60);
    //hint->SetMarkerStyle(1);
    //hint->Draw("e3 sames");
    //parabola->Draw("Same");

    //hist->Fit("parabola_1");
    //hist->Fit("parabola_2");
    //parabola_1->Draw("Same");
    //parabola_2->Draw("Same");
    line->Draw("SAME");
    legend->SetTextSize(0.02);
    legend->Draw("same");
    gStyle->SetOptFit(1111);
    std::string TotalTitle(Title);
    plot -> AddHistoTitle(TotalTitle.c_str() , .04);
    plot -> WritePreliminary("TL", .035, 0, 0, false);
    gPad->Update();
    can->Modified();
    can->Print(pdf);
    can->Clear();
    }


    /////////////////////////////////////////////////////////////////////////////////
    //
    /////////////////////////////////////////////////////////////////////////////////

void DrawTGraph(TGraphErrors *g_TGraph1, TGraphErrors *g_TGraph2, const char* xaxislabel,const char* yaxislabel,
   const char* Title,const char* legend_Title1,const char* legend_Title2,
   const char* pdf, TCanvas *can, MnvPlotter *plot, bool MakeXaxisLOG, bool MakeYaxisLOG, bool doMax ){
     double x1, x2, y1, y2;

     plot->DecodeLegendPosition(x1, y1, x2, y2, "TR", 6.5, 6., .025);
     TLegend *legend = new TLegend (x1 , y1 + .1, x2 + .1 , y2 );

     if(MakeXaxisLOG==true){
       gPad->SetLogx();
     }
     if(MakeYaxisLOG==true){
       gPad->SetLogy();
     }

     string TotalTitle = string(Title);

    g_TGraph1 -> SetTitle("");
    g_TGraph1 -> GetXaxis() -> SetTitle(xaxislabel);
    g_TGraph1 -> GetYaxis() -> SetTitle(yaxislabel);
    g_TGraph1 -> GetXaxis() -> CenterTitle();
    g_TGraph1 -> GetYaxis() -> CenterTitle();
    //g_TGraph1 -> GetXaxis() -> SetTitleSize(0.038);
    //g_TGraph1 -> GetYaxis() -> SetTitleSize(0.038);
    g_TGraph1->GetXaxis()->SetNdivisions(30, kTRUE);
    g_TGraph1->GetYaxis()->SetNdivisions(25, kTRUE);
    g_TGraph1->GetYaxis()->SetLabelSize(0.020);
    g_TGraph1->GetXaxis()->SetLabelSize(0.015);

    g_TGraph1 -> SetLineColor(2);
    g_TGraph1 -> SetMarkerColor(2);
    g_TGraph1-> SetMarkerStyle(6);
    //g_TGraph1->SetMarkerSize(5);
    g_TGraph2 -> SetLineColor(4);
    g_TGraph2 -> SetMarkerColor(4);
    g_TGraph2-> SetMarkerStyle(6);
    //g_TGraph2->SetMarkerSize(5);

    double SetMaxY, SetMinY;
    if(doMax==true){
      double Amax = g_TGraph1->GetHistogram()->GetMaximum();
      double Bmax = g_TGraph2->GetHistogram()->GetMaximum();
      if(Amax  >= Bmax){SetMaxY = Amax;}
      else{SetMaxY = Bmax;}
      g_TGraph1->SetMaximum(SetMaxY*1.025);

      double Amin = g_TGraph1->GetHistogram()->GetMinimum();
      double Bmin = g_TGraph2->GetHistogram()->GetMinimum();

      if(Amin  <= Bmin){SetMinY = Amin;}
      else{SetMinY = Bmin;}
      g_TGraph1->SetMinimum(SetMinY);
    }


   //TCanvas *optcan = new TCanvas("optcan");
   g_TGraph1 -> Draw("ALP");
   g_TGraph2 -> Draw("SAME");

   legend -> SetTextSize(0.03);
   legend -> SetFillColor(0);
   legend -> AddEntry(g_TGraph1, legend_Title1, "LP");
   legend -> AddEntry(g_TGraph2, legend_Title2, "LP");
   legend -> Draw();
   plot -> AddHistoTitle(TotalTitle.c_str() , .04);
   plot -> WritePreliminary("TL", .035, 0, 0, false);

   gPad->Update();
   can->Modified();
   can->Print(pdf);
   can->Closed();

   if(MakeXaxisLOG==true){
     gPad->SetLogx(0);
   }
   if(MakeYaxisLOG==true){
     gPad->SetLogy(0);
   }



return;

}

/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////

void DrawTGraph(TGraph *g_TGraph1, TGraph *g_TGraph2, const char* xaxislabel,const char* yaxislabel,
   const char* Title,const char* legend_Title1,const char* legend_Title2,
   const char* pdf, TCanvas *can, MnvPlotter *plot, bool MakeXaxisLOG, bool MakeYaxisLOG, bool doMax ){
     double x1, x2, y1, y2;

     plot->DecodeLegendPosition(x1, y1, x2, y2, "TR", 6.5, 6., .025);
     TLegend *legend = new TLegend (x1 , y1 + .1, x2 + .1 , y2 );

     if(MakeXaxisLOG==true){
       gPad->SetLogx();
     }
     if(MakeYaxisLOG==true){
       gPad->SetLogy();
     }

     can->SetGrid();

     string TotalTitle = string(Title);

    g_TGraph2 -> SetTitle("");
    g_TGraph2 -> GetXaxis() -> SetTitle(xaxislabel);
    g_TGraph2 -> GetYaxis() -> SetTitle(yaxislabel);
    g_TGraph2 -> GetXaxis() -> CenterTitle();
    g_TGraph2 -> GetYaxis() -> CenterTitle();
    g_TGraph2 -> GetXaxis() -> SetTitleSize(0.03);
    g_TGraph2 -> GetYaxis() -> SetTitleSize(0.03);
    g_TGraph2->GetYaxis()->SetLabelSize(0.025);
    g_TGraph2->GetXaxis()->SetLabelSize(0.025);

    g_TGraph1 -> SetLineColor(2);
    g_TGraph1 -> SetMarkerColor(2);
    g_TGraph1-> SetMarkerStyle(6);
    g_TGraph1->SetLineStyle(2);
    g_TGraph1->SetLineWidth(2);
    //g_TGraph1->SetMarkerSize(5);
    g_TGraph2 -> SetLineColor(4);
    g_TGraph2 -> SetMarkerColor(4);
    g_TGraph2-> SetMarkerStyle(6);
    g_TGraph2->SetLineStyle(2);
    g_TGraph2->SetLineWidth(2);
    //g_TGraph2->SetMarkerSize(5);

    double SetMaxY, SetMinY;
    if(doMax==true){
      double Amax = g_TGraph1->GetHistogram()->GetMaximum();
      double Bmax = g_TGraph2->GetHistogram()->GetMaximum();
      if(Amax  >= Bmax){SetMaxY = Amax;}
      else{SetMaxY = Bmax;}
      g_TGraph2->SetMaximum(SetMaxY*1.1);

      double Amin = g_TGraph1->GetHistogram()->GetMinimum();
      double Bmin = g_TGraph2->GetHistogram()->GetMinimum();

      if(Amin  <= Bmin){SetMinY = Amin;}
      else{SetMinY = Bmin;}
      g_TGraph2->SetMinimum(SetMinY*.9);
    }

    g_TGraph1->SetFillColor(42);
    g_TGraph2->SetFillColor(38);
    g_TGraph2 -> Draw("alf");
    g_TGraph1 -> Draw("lf");



   legend -> SetTextSize(0.035);
   legend -> SetFillColor(0);
   legend -> AddEntry(g_TGraph1, legend_Title1, "f");
   legend -> AddEntry(g_TGraph2, legend_Title2, "f");
   legend -> Draw();
   plot -> AddHistoTitle(TotalTitle.c_str() , .04);
   plot -> WritePreliminary("TL", .035, 0, 0, false);

   gPad->Update();
   can->Modified();
   can->Print(pdf);
   can->Closed();

   if(MakeXaxisLOG==true){
     gPad->SetLogx(0);
   }
   if(MakeYaxisLOG==true){
     gPad->SetLogy(0);
   }

   can->SetGrid(0,0);


return;

}

/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////

void DrawTGraph(TGraphErrors *g_TGraph1, TGraphErrors *g_TGraph2, TGraphErrors *g_TGraph3, const char* xaxislabel,const char* yaxislabel,
   const char* Title,const char* legend_Title1, const char* legend_Title2, const char* legend_Title3,
   const char* pdf, TCanvas *can, MnvPlotter *plot, bool MakeXaxisLOG, bool MakeYaxisLOG , bool setGrid , bool doMax ){
     double x1, x2, y1, y2;

     plot->DecodeLegendPosition(x1, y1, x2, y2, "TR", 6.5, 6., .025);
     TLegend *legend = new TLegend (x1, y1+.05 , x2, y2);
     if(MakeXaxisLOG==true){
       gPad->SetLogx();
     }
     if(MakeYaxisLOG==true){
       gPad->SetLogy();
     }

     if (setGrid==true) {can->SetGrid();}


     double SetMinY;
     double SetMaxY;

     if(doMax==true){
       std::cout << "g_TGraph1 Max = " << g_TGraph1->GetHistogram()->GetMaximum()<< std::endl;
       std::cout << "g_TGraph2 Max = " << g_TGraph2->GetHistogram()->GetMaximum()<< std::endl;
       std::cout << "g_TGraph3 Max = " << g_TGraph3->GetHistogram()->GetMaximum()<< std::endl;
       double Amax = g_TGraph1->GetHistogram()->GetMaximum();
       double Bmax = g_TGraph2->GetHistogram()->GetMaximum();
       double Cmax = g_TGraph3->GetHistogram()->GetMaximum();
       if(Amax  >= Bmax  && Amax >= Cmax){SetMaxY = Amax;}
       else if (Amax  <= Bmax && Cmax <= Bmax){SetMaxY = Bmax;}
       else{SetMaxY = Cmax;}
       g_TGraph1->SetMaximum(SetMaxY*1.2);

       double Amin = g_TGraph1->GetHistogram()->GetMinimum();
       double Bmin = g_TGraph2->GetHistogram()->GetMinimum();
       double Cmin = g_TGraph3->GetHistogram()->GetMinimum();

       if(Amin  <= Bmin && Amin <= Cmin){SetMinY = Amin;}
       else if (Bmin  <= Amin && Bmin <= Cmin){SetMinY = Bmin;}
       else{SetMinY = Cmin;}
       g_TGraph1->SetMinimum(SetMinY);
     }

     string TotalTitle = string(Title);

    g_TGraph1 -> SetTitle("");
    g_TGraph1 -> GetXaxis() -> SetTitle(xaxislabel);
    g_TGraph1 -> GetYaxis() -> SetTitle(yaxislabel);
    g_TGraph1 -> GetXaxis() -> CenterTitle();
    g_TGraph1 -> GetYaxis() -> CenterTitle();
    //g_TGraph1 -> GetXaxis() -> SetTitleSize(0.038);
    //g_TGraph1 -> GetYaxis() -> SetTitleSize(0.038);

    g_TGraph1->GetXaxis()->SetNdivisions(30, kTRUE);
    g_TGraph1->GetYaxis()->SetNdivisions(25, kTRUE);
    g_TGraph1->GetYaxis()->SetLabelSize(0.020);
    g_TGraph1->GetXaxis()->SetLabelSize(0.015);


    g_TGraph1 -> SetLineColor(2);
    g_TGraph1 -> SetMarkerColor(2);
    g_TGraph1-> SetMarkerStyle(6);
    //g_TGraph1->SetMarkerSize(5);
    g_TGraph2 -> SetLineColor(4);
    g_TGraph2 -> SetMarkerColor(4);
    g_TGraph2-> SetMarkerStyle(6);
    //g_TGraph2->SetMarkerSize(5);
    g_TGraph3 -> SetLineColor(8);
    g_TGraph3 -> SetMarkerColor(8);
    g_TGraph3-> SetMarkerStyle(6);
    //g_TGraph3->SetMarkerSize(5);
   //TCanvas *optcan = new TCanvas("optcan");

   g_TGraph1 -> Draw("ALP");
   g_TGraph2 -> Draw("SAME");
   g_TGraph3 -> Draw("SAME");

   legend -> SetTextSize(0.03);
   legend -> SetFillColor(0);
   legend -> AddEntry(g_TGraph1, legend_Title1, "LP");
   legend -> AddEntry(g_TGraph2, legend_Title2, "LP");
   legend -> AddEntry(g_TGraph3, legend_Title3, "LP");
   legend -> Draw();
   plot -> AddHistoTitle(TotalTitle.c_str() , .04);
   plot -> WritePreliminary("TL", .035, 0, 0, false);

   gPad->Update();
   can->Modified();
   can->Print(pdf);
   if (setGrid==true) {can->SetGrid();}
   can->Closed();

   if(MakeXaxisLOG==true){
     gPad->SetLogx(0);
   }
   if(MakeYaxisLOG==true){
     gPad->SetLogy(0);
   }


return;

}

void DrawPie_Figures_EventCutRate(TFile *inputFile_TRUTHBranch,  char* TGraphName_TRUTHBranch,
  TFile *inputFile_RECOBranch,  char* TGraphName_RECOBranch_TRUE ,  char* TGraphName_RECOBranch_TRUE_RECO,
  ME_helium_Playlists playlist, ME_helium_Status Crytank_status,  const char* pdf,
  TCanvas *can, MnvPlotter *plotter, char * Title){

    EventCut_Rate_STRUCT EventCut_Rate_STRUCT;

    MakeEventCut_Rate_STRUCT_fromTFiles(EventCut_Rate_STRUCT, inputFile_TRUTHBranch,  TGraphName_TRUTHBranch,
      inputFile_RECOBranch, TGraphName_RECOBranch_TRUE , TGraphName_RECOBranch_TRUE_RECO, playlist,  Crytank_status);

      DrawPie_Figures_EventCutRate(EventCut_Rate_STRUCT,  pdf,can, plotter,  Title);
}

/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////

void DrawCVAndError_eff_purity_EOM_ERROR(MnvH1D *hist_eff,  MnvH1D *hist_pur, char *histotitle ,std::string xaxislabel,
const char *pdf, bool doBinwidth, double Ymax , std::vector<double> BinsEdges_vector){

  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  double x1,x2,y1,y2;
  cE.SetGrid();
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", .5, 10, .025);
  //TLegend *legend = new TLegend(x1 - .05, y1 + .1, x2 + .05, y2 + .1);
  TLegend *legend = new TLegend(x1 - .02, y1+.31 , x2 + .15 , y2 + .42  );
  legend->SetNColumns(1);
  legend->SetTextSize(.03);
  legend->SetFillColor(0);

  bool includeStat = false;
  bool asfrac = false;
  bool covAreaNormalize = false;

  TH1D *h_eff_TotalErr = (TH1D*)hist_eff->GetTotalError( includeStat, asfrac, covAreaNormalize ).Clone("h_eff_TotalErr");
  TH1D *h_Pur_TotalErr = (TH1D*)hist_pur->GetTotalError( includeStat, asfrac, covAreaNormalize ).Clone("h_Pur_TotalErr");
  asfrac = true;
  TH1D *h_eff_TotalErr_toDraw = (TH1D*)hist_eff->GetTotalError( includeStat, asfrac, covAreaNormalize ).Clone("h_eff_TotalErr_toDraw");
  TH1D *h_Pur_TotalErr_toDraw = (TH1D*)hist_pur->GetTotalError( includeStat, asfrac, covAreaNormalize ).Clone("h_Pur_TotalErr_toDraw");

  TH1D* h_EOM =new TH1D("h_EOM", "h_EOM",  BinsEdges_vector.size()-1,  BinsEdges_vector.data());

  double Nbins = hist_eff->GetNbinsX();

  h_eff_TotalErr_toDraw->SetTitleOffset(0.05);
  h_eff_TotalErr_toDraw->SetTitle(histotitle);
  h_eff_TotalErr_toDraw->GetYaxis()->CenterTitle();
  h_eff_TotalErr_toDraw->GetYaxis()->SetLabelSize(0.05);
  h_eff_TotalErr_toDraw->GetXaxis()->SetTitleSize(0.038);
  h_eff_TotalErr_toDraw->GetXaxis()->SetNdivisions(30, kTRUE);
  h_eff_TotalErr_toDraw->GetYaxis()->SetNdivisions(25, kTRUE);
  h_eff_TotalErr_toDraw->GetXaxis()->SetLabelSize(0.015);
  h_eff_TotalErr_toDraw->GetYaxis()->SetLabelSize(0.025);

  h_eff_TotalErr_toDraw->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
  h_eff_TotalErr_toDraw->GetXaxis()->SetTitleOffset(1.0);
  h_eff_TotalErr_toDraw->GetXaxis()->CenterTitle();
  h_eff_TotalErr_toDraw->GetYaxis()->SetTitle("Fractional Uncertainty");
  h_eff_TotalErr_toDraw->SetMinimum( 0. );
  h_eff_TotalErr_toDraw->SetMaximum( Ymax );
  h_eff_TotalErr_toDraw->SetLineColor(kRed);
  h_eff_TotalErr_toDraw->SetLineWidth(3);
  h_eff_TotalErr_toDraw->SetLineStyle(2);

  h_Pur_TotalErr_toDraw->SetLineColor(kBlue);
  h_Pur_TotalErr_toDraw->SetLineWidth(3);
  h_Pur_TotalErr_toDraw->SetLineStyle(2);

  h_EOM->SetLineColor(kBlack);
  h_EOM->SetLineWidth(3);
  h_EOM->SetLineStyle(2);
// not include overflow and under
  for(int i = 1; i< Nbins; ++i){
    double Eff =hist_eff->GetBinContent(i);
    double Pur =hist_pur->GetBinContent(i);
    double delta_Eff  =  h_eff_TotalErr->GetBinContent(i);
    double delta_Pur  =  h_Pur_TotalErr->GetBinContent(i);
    double eom_bin = pow((delta_Eff / Eff),2) + pow((delta_Pur / Pur),2);
    h_EOM->SetBinContent(i,eom_bin);
  }

  hist_eff->Multiply(hist_eff,hist_pur ,1.0,1.0);
  TH1D *h_Mult_toDraw = (TH1D*)hist_eff->GetTotalError( includeStat, asfrac, covAreaNormalize ).Clone("h_Mult_toDraw");

  //h_eff_TotalErr_toDraw->SetMaximum(h_eff_TotalErr_toDraw->GetMaximum());

  legend->AddEntry(h_eff_TotalErr_toDraw, "Total Uncertainty Eff", "l");
  legend->AddEntry(h_Pur_TotalErr_toDraw, "Total Uncertainty Purity", "l");
  legend->AddEntry(h_Mult_toDraw, "Total Uncertainty Purity*eff", "l");
  legend->AddEntry(h_EOM, "EOM", "l");

  h_eff_TotalErr_toDraw->Draw("HIST");
  h_Pur_TotalErr_toDraw->Draw("SAME");
  h_Mult_toDraw->Draw("SAME");
  h_EOM->Draw("SAME");


  legend->Draw();

  mnvPlotter.AddHistoTitle(histotitle, .04);
  mnvPlotter.WritePreliminary("TL", .035, 0, 0, false);

  cE.Print(pdf);


}

/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////

void Draw_2DPlotFromVectors(std::vector<double> Xaxis, std::vector<double> Yaxis,
  std::vector<double> Zaxis,char *histotitle, char* xaxislabel,  char* yaxislabel, char* zaxislabel,
  MnvPlotter *plot ,TCanvas *can, char *pdf ){


if (Xaxis.size() != Yaxis.size() ||  Xaxis.size() != Zaxis.size() ){
  std::cout<< " input vectors for Draw_2DPlotFromVectors are of different sizes, this makes no sence something is wrong "<< std::endl; assert(false);
}
can->SetGrid();
TGraph2D *g = new TGraph2D();
//TH2D *h = new TH2D("h","", Xaxis.size()-1, Xaxis.data(), Yaxis.size()-1, Yaxis.data());


for (unsigned int i = 0; i<Xaxis.size(); i++) {
g->SetPoint(i,Xaxis.at(i),Yaxis.at(i),Zaxis.at(i));
}

/*
int count=0;
for(int j = 0; j < Yaxis.size(); ++j ){
  for(int i = 0; i < Xaxis.size(); ++i ){
      h->SetBinContent(i, j, Zaxis.at(count));
      count++;
  }
}
*/
//g->SetHistogram(h);
g->Draw("PCOL");
g->GetXaxis()->SetTitle(xaxislabel);
g->GetYaxis()->SetTitle(yaxislabel);
g->GetZaxis()->SetTitle(zaxislabel);


plot -> AddHistoTitle(histotitle , .03);
//plot -> WritePreliminary("TL", .035, 0, 0, false);
gPad->Update();
can->Modified();
can->Print(pdf);

//Draw2DHist(h, xaxislabel,  yaxislabel, zaxislabel, histotitle, pdf, can, plot);


can->Clear();

}


/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////


void Draw_inputTranswarpHist_fromPointers(
  MnvH1D *h_data,
  MnvH1D *h_data_true,
  MnvH1D *h_mc_reco,
  MnvH1D *h_mc_true,
  bool AreaNorm_todata,
  std::string pdf_label,
  char *histotitle,
  char *xaxislabel,
  char *yaxislabel_units,
  bool DoBinwidthNorm,
  bool MakeXaxisLOG,
  double Ymax, bool makeYmax)
{
std::cout<<"Inside::Draw_inputTranswarpHist_fromPointers "<<std::endl;

  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  mnvPlotter.axis_title_size_x = 0.015;
  mnvPlotter.axis_title_size_y = 0.025;
  mnvPlotter.axis_label_size = 0.1;

  TCanvas cE ("c1","c1");
  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  std::cout<< "Starting to clone"<<std::endl;
  auto h_Data = (PlotUtils::MnvH1D*)h_data->Clone("h_Data");
  std::cout<< "Finished :: Clone(h_Data);"<<std::endl;
  std::cout<< "Starting to clone"<<std::endl;
  auto h_Data_TRUE = (PlotUtils::MnvH1D*)h_data_true->Clone("h_Data_TRUE");
  std::cout<< "Finished :: Clone(h_Data);"<<std::endl;
  std::cout<< "Starting to clone"<<std::endl;
  auto h_MC_RECO = (PlotUtils::MnvH1D*)h_mc_reco->Clone("h_MC_RECO");
    std::cout<< "Finished :: Clone(h_mc_reco);"<<std::endl;
    std::cout<< "Starting to clone"<<std::endl;
  auto h_MC_TRUE = (PlotUtils::MnvH1D*)h_mc_true->Clone("h_MC_TRUE");
    std::cout<< "Finished :: Clone(h_mc_true);"<<std::endl;

  string TotalTitle = string(histotitle);

    int N_Data =      h_Data->GetNbinsX();
    int N_Data_TRUE = h_Data_TRUE->GetNbinsX();
    int N_MC_RECO =   h_MC_RECO->GetNbinsX();
    int N_MC_TRUE =   h_MC_TRUE->GetNbinsX();

    if(N_Data != N_Data_TRUE || N_Data != N_MC_RECO  || N_Data != N_MC_TRUE ) {
      std::cout<<"The Bins are different sizes for: Draw_inputTranswarpHist_fromPointers"<<std::endl;
      std::cout<< "with Xaxis = "<< xaxislabel << std::endl;
      std::cout<< "N_Data = " <<  N_Data <<std::endl;
      std::cout<< "N_Data_TRUE = " <<  N_Data_TRUE <<std::endl;
      std::cout<< "N_MC_RECO = " <<  N_MC_RECO <<std::endl;
      std::cout<< "N_MC_TRUE = " <<  N_MC_TRUE <<std::endl;
      assert(false);
    }

    if(AreaNorm_todata==true){
    double Area_Data = h_Data->Integral();
    double Area_Data_TRUE = h_Data_TRUE->Integral();
    double Area_MC_RECO = h_MC_RECO->Integral();
    double Area_MC_TRUE =h_MC_TRUE->Integral();

    h_Data_TRUE->Scale(Area_Data/Area_Data_TRUE);
    h_MC_RECO->Scale(Area_Data/Area_MC_RECO);
    h_MC_TRUE->Scale(Area_Data/Area_MC_TRUE);

  }

  char ytitle[100];



  if(DoBinwidthNorm==true){
    h_Data->Scale(1.0,"width");
    h_Data_TRUE->Scale(1.0,"width");
    h_MC_RECO->Scale(1.0,"width");
    h_MC_TRUE->Scale(1.0,"width");

    if(makeYmax==false) Ymax = 1.45 * GetMax(h_Data, h_Data_TRUE,h_MC_RECO,h_MC_TRUE  );;

    double binwidth_title = h_Data->GetBinWidth(5);
    sprintf(ytitle, "NEvents / [%.2f %s] ", binwidth_title , yaxislabel_units);
    if(AreaNorm_todata==true){sprintf(ytitle, "NEvents [AreaNorm to Data] / [%.2f %s] ", binwidth_title , yaxislabel_units);}
  }

  else{
    sprintf(ytitle, "NEvents");

  }

  if(MakeXaxisLOG==true){
    gPad->SetLogx();
  }

  auto Data_Clone_1 = (PlotUtils::MnvH1D*)h_Data->Clone("Data_Clone_1");
  auto Data_Clone_2 = (PlotUtils::MnvH1D*)h_Data_TRUE->Clone("Data_Clone_2");
  auto mc_Clone_1 =  (PlotUtils::MnvH1D*)h_MC_RECO->Clone("mc_Clone_1");
  auto mc_Clone_2 =  (PlotUtils::MnvH1D*)h_MC_TRUE->Clone("mc_Clone_2");

  Data_Clone_1->Divide(Data_Clone_1, Data_Clone_2);
  Data_Clone_1->SetLineColor(TColor::GetColor("#1e90ff"));
  Data_Clone_1->SetLineStyle(1);
  Data_Clone_1->SetLineWidth(3);

  mc_Clone_1->Divide(mc_Clone_1,mc_Clone_2);
  mc_Clone_1->SetLineColor(TColor::GetColor("#ff1493"));
  mc_Clone_1->SetLineStyle(2);
  mc_Clone_1->SetLineWidth(3);

  double x1, x2, y1, y2;
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", 6.5, 6., .025);
  TLegend *legend1 = new TLegend(x1 - .01 , y1 - .025, x2 + .095, y2 + .25); // .2,.34
  legend1->SetTextSize(0.025);
  char chi_label[1024];

  h_Data->GetYaxis()->SetTitle(ytitle);
  h_Data->SetLineColor(TColor::GetColor("#66cdaa"));
  h_Data_TRUE->SetLineColor(TColor::GetColor("#ffa500"));
  h_MC_RECO->SetLineColor(TColor::GetColor("#00ff00"));
  h_MC_TRUE->SetLineColor(TColor::GetColor("#0000ff"));

  h_Data->SetLineWidth(3);
  h_Data_TRUE->SetLineWidth(3);
  h_MC_RECO->SetLineWidth(3);
  h_MC_TRUE->SetLineWidth(3);

  h_Data->SetMaximum(Ymax);
  h_Data->SetLineStyle(1);
  h_Data->Draw("Hist");


  h_Data_TRUE->SetLineStyle(3);
  h_Data_TRUE->Draw("Hist same");

  h_MC_RECO->SetLineStyle(1);
  h_MC_RECO->Draw("Hist same");

  h_MC_TRUE->SetLineStyle(5);
  h_MC_TRUE->Draw("Hist same");

  int ndf=0;
  int ndf_h_MC_TRUE =0;

  double chi_MC_MC_1 =  mnvPlotter.Chi2MCMC(h_Data, h_Data_TRUE, ndf);
  double chi_MC_RECO_TRUTH =  mnvPlotter.Chi2DataMC(h_MC_RECO, h_MC_TRUE, ndf_h_MC_TRUE);


  legend1->AddEntry(h_Data, "h_data", "l");
  legend1->AddEntry(h_Data_TRUE, "h_data_true", "l");
  legend1->AddEntry(h_MC_RECO, "h_mc_reco", "l");
  legend1->AddEntry(h_MC_TRUE, "h_mc_true", "l");


  legend1->AddEntry(Data_Clone_1, "Ratio #frac{h_data_true}{h_data}", "l");
  legend1->AddEntry(mc_Clone_1, "Ratio #frac{h_mc_reco}{h_mc_true}", "l");

  sprintf(chi_label, "Data to data_true" );
  legend1 -> AddEntry((TObject*)0, chi_label, "");
  sprintf(chi_label, "#chi^{2}/ndf = %.1f / %i = %.1f", chi_MC_MC_1, ndf, chi_MC_MC_1 / ndf);
  legend1 -> AddEntry((TObject*)0, chi_label, "");
  sprintf(chi_label, "mc_reco to mc_true");
  legend1 -> AddEntry((TObject*)0, chi_label, "");
  sprintf(chi_label, "#chi^{2}/ndf = %.1f / %i = %.1f ", chi_MC_RECO_TRUTH, ndf, chi_MC_RECO_TRUTH / ndf_h_MC_TRUE);
  legend1 -> AddEntry((TObject*)0, chi_label, "");
  legend1->Draw("Same");


  cE.cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.2);
  pad2->SetGridx(); // vertical grid
  pad2->SetGridy(); // vertical grid
  pad2->Draw();
  pad2->cd();
  TLine l;
  l.SetLineWidth(2);
  l.SetLineStyle(3);
  l.SetLineColor(kRed);
  double xmax = Data_Clone_1->GetXaxis()->GetXmax();
  double xmin = Data_Clone_1->GetXaxis()->GetXmin();
  mnvPlotter.axis_title_offset_y = 1.2;
  mnvPlotter.axis_title_size_y = 0.12;
  Data_Clone_1->GetYaxis()->SetTitle("#frac{Data}{MC}");
  Data_Clone_1->GetXaxis()->SetTitle(xaxislabel);
  Data_Clone_1->GetYaxis()->SetTitleOffset(mnvPlotter.axis_title_offset_y );
  Data_Clone_1->GetXaxis()->SetTitleOffset(.7);
  Data_Clone_1->GetYaxis()->SetTitleOffset(.5);
  //Data_Clone_1->GetXaxis()->SetTitleFont(mnvPlotter.axis_title_font_x);
  //Data_Clone_1->GetYaxis()->SetTitleFont(mnvPlotter.axis_title_font_y);
  Data_Clone_1->GetXaxis()->SetTitleSize(.125);
  Data_Clone_1->GetYaxis()->SetTitleSize(.1);
  //Data_Clone_1->GetXaxis()->SetLabelFont(mnvPlotter.axis_label_font);
  //Data_Clone_1->GetYaxis()->SetLabelFont(mnvPlotter.axis_label_font);
  Data_Clone_1->GetXaxis()->SetLabelSize(mnvPlotter.axis_label_size);
  Data_Clone_1->GetYaxis()->SetLabelSize(mnvPlotter.axis_label_size);
  Data_Clone_1->GetYaxis()->CenterTitle(kTRUE);
  Data_Clone_1->GetXaxis()->CenterTitle(kTRUE);
  Data_Clone_1->SetMaximum(1.5);
  Data_Clone_1->SetMinimum(0.5);
  Data_Clone_1->Draw("PEC");
  l.DrawLine(xmin,1,xmax, 1);
  mc_Clone_1->Draw("SAME");
  cE.cd();

  char total_title[1024];
  sprintf(total_title, "%s ", histotitle);
  mnvPlotter.AddHistoTitle(total_title, .04);
  mnvPlotter.WritePreliminary("TL", .032, 0, 0, false);
  std::string plotname = Form("%s",pdf_label.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");
  cE.Closed();

  if(MakeXaxisLOG==true){
    gPad->SetLogx(0);
  }

}//END of Function

/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////

void Draw_TransWarp_converage(MnvH2D *hist2D, MnvH1D *hist1D_mean,  MnvH1D *hist1D_median, int var_ndf ,  char* xaxislabel, char* yaxislabel, char* zaxislabel,
                 char* Title,  char* pdf, TCanvas *can, MnvPlotter *plot , double SetZMax , bool MakeLogY )
{
  string TotalTitle = string(Title);
  gStyle->SetPalette(kCool);

  TPad *pad1 = new TPad("pad1","",0,0,1,1);
  pad1->Draw();
  pad1->cd();

  if(MakeLogY==true){gPad->SetLogy();}

  double x1, x2, y1, y2;
  plot->DecodeLegendPosition(x1, y1, x2, y2,"R", 6.5, 6., .025);
  TLegend *legend1 = new TLegend(x1 - .1, y1+.3 , x2 , y2+.3 );

  hist2D->GetXaxis()->CenterTitle();
  hist2D->GetYaxis()->CenterTitle();
  hist2D->GetXaxis()->SetTitle(xaxislabel);
  hist2D->GetYaxis()->SetTitle(yaxislabel);
  hist2D->GetZaxis()->SetTitle(zaxislabel);
  hist2D->GetXaxis()->SetTitleSize(0.038);
  hist2D->GetYaxis()->SetTitleSize(0.06);
  hist2D->GetZaxis()->SetTitleSize(0.035);
  hist2D->GetZaxis()->SetLabelSize(0.022);
  hist2D->GetZaxis()->SetTitleOffset(.5);
  hist2D->GetXaxis()->SetTitleOffset(1.05);
  //hist2D->GetYaxis()->SetLimits(0,SetYMax);
  hist2D->SetMaximum(SetZMax);
  int Nybins = hist2D->GetNbinsY();
  int Nxbins = hist2D->GetNbinsX();
  double HistmaxY = hist2D->GetYaxis()->GetBinUpEdge( Nybins);
  double HistmaxX = hist2D->GetXaxis()->GetBinUpEdge( Nxbins);
  hist1D_mean->SetLineWidth(4);
  hist1D_median->SetLineWidth(4);
  hist1D_mean->SetLineStyle(1);
  hist1D_median->SetLineStyle(1);

  hist1D_mean->SetLineColor(TColor::GetColor("#07A620")); //  #b82716
  hist1D_median->SetLineColor(TColor::GetColor("#ffb90f"));


  TLine *Ndf = new TLine(1, var_ndf, HistmaxX, var_ndf);
  Ndf->SetLineWidth(4);
  Ndf->SetLineStyle(2);
  Ndf->SetLineColor(kBlack);

  TLine *Ndf2 = new TLine(1, 2*var_ndf, HistmaxX, 2*var_ndf);
  Ndf2->SetLineWidth(4);
  Ndf2->SetLineStyle(2);
  Ndf2->SetLineColor(TColor::GetColor("#8b4513"));

  TLine *Ndf3 = new TLine(3,0,3, HistmaxY );
  Ndf3->SetLineWidth(4);
  Ndf3->SetLineStyle(3);
  Ndf3->SetLineColor(TColor::GetColor("#c63200"));

  legend1->AddEntry(hist1D_mean, "#chi^{2} Mean", "l");
  legend1->AddEntry(hist1D_median, "#chi^{2} median", "l");
  legend1->AddEntry(Ndf, "Number of Bins (Ndf)", "l");
  legend1->AddEntry(Ndf2, "2x Number of Bins", "l");
  legend1->AddEntry(Ndf3, "3 Itrations", "l");
  legend1->SetTextSize(.02);

  hist2D->Draw("colz");
  gPad->Update();

  Double_t bm = gPad->GetBottomMargin();
  Double_t lm = gPad->GetLeftMargin();
  Double_t rm = gPad->GetRightMargin();
  Double_t tm = gPad->GetTopMargin();

   TPad *null=new TPad("null", "null",0,0, 1, 1);
   null->SetFillStyle(0); /* a transparent pad */
   null->SetFrameFillStyle(0);
   null->Draw();
   null->cd();

   // drawing a line on th2d seems to be troublesome trying this method

     Double_t xx1 = hist2D->GetXaxis()->GetXmin();
     Double_t yy1 = hist2D->GetYaxis()->GetXmin();
     Double_t xx2 = hist2D->GetXaxis()->GetXmax();
     Double_t yy2 = hist2D->GetYaxis()->GetXmax();


     null->Range( xx1-(xx2-xx1)*(lm/(1-rm-lm)),
                  yy1-(yy2-yy1)*(bm/(1-tm-bm)),
                  xx2+(xx2-xx1)*(rm/(1-rm-lm)),
                  yy2+(yy2-yy1)*(tm/(1-tm-bm)));



    gPad->Update();

    //TLine l;  TLine l2;   TLine l3;
    //l.SetLineWidth(4);
    //l.SetLineStyle(2);
    //l.SetLineColor(kBlack);
    //l.DrawLine(1,var_ndf,25, var_ndf);
    Ndf->Draw();
    Ndf2->Draw();
    Ndf3->Draw();
    pad1->cd();
    hist1D_mean->Draw("Hist same");
    hist1D_median->Draw("Hist same");
    if(MakeLogY==true){gPad->SetLogy();}
    legend1->Draw("same");

    //can->cd();
    plot->AddHistoTitle(TotalTitle.c_str(), .035);
    plot->WritePreliminary("TL", .035, 0, 0, false);

  can->Print(pdf);
  can->Closed();
  if(MakeLogY==true){gPad->SetLogy(1);}


}//end of 2D draw function


/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////

void test2(char * pdf, MnvH2D *hist2D  ){
std::cout<<"inside test2"<<std::endl;
  TCanvas *c1 = new TCanvas("c1","c1",200,10,700,500);
  c1->cd();
    // Make a test histogram
    TH2F *h1 = new TH2F("h1","h1",40,-4,4,40,-4,4);
    Double_t a,b;
    for (Int_t i=0;i<306500;i++) {gRandom->Rannor(a,b);h1->Fill(a-1.5,b-1.5);}

    for (Int_t i=0;i<550;i++) {h1->Fill(3.5,3);}
    for (Int_t i=0;i<450;i++) {h1->Fill(3.5,2);}
    for (Int_t i=0;i<350;i++) {h1->Fill(3.5,1);}
    for (Int_t i=0;i<250;i++) {h1->Fill(3.5,0);}
    for (Int_t i=0;i<150;i++) {h1->Fill(3.5,-1);}
    for (Int_t i=0;i< 50;i++) {h1->Fill(3.5,-2);}
    for (Int_t i=0;i<  5;i++) {h1->Fill(3.5,-3);}


    // The histogram is drawn in pad1, any option can be used.
    TPad *pad1 = new TPad("pad1","",0,0,1,1);
    pad1->Draw();
    pad1->cd();

    hist2D->Draw("colz");
    //h1->Draw("colz");
  gPad->Update();

    // Create a transparent "null" pad on top of pad1 with exactly the same
    // geometry but with the histogram coordinates. In case CONT4 is used to
    // draw the histogram any additionnal graaphics drawn in "null" will
    // appeared as drawn in the histograms coordinates.
    TPad *null = new TPad("null","",0,0,1,1);
    null->SetFillStyle(0);
    null->SetFrameFillStyle(0);
    null->Draw();
    null->cd();

    Double_t bm = pad1->GetBottomMargin();
    Double_t lm = pad1->GetLeftMargin();
    Double_t rm = pad1->GetRightMargin();
    Double_t to = pad1->GetTopMargin();
    Double_t x1 = hist2D->GetXaxis()->GetXmin();
    Double_t yf = hist2D->GetYaxis()->GetXmin();
    Double_t x2 = hist2D->GetXaxis()->GetXmax();
    Double_t y2 = hist2D->GetYaxis()->GetXmax();


    std::cout<<"bm = "<< bm << std::endl;
    std::cout<<"lm = "<< lm << std::endl;
    std::cout<<"rm = "<< rm << std::endl;
    std::cout<<"to = "<< to << std::endl;

    Double_t Xa = (x2-x1)/(1-lm-rm)-(x2-x1);
    Double_t Ya = (y2-yf)/(1-bm-to)-(y2-yf);
    Double_t LM = Xa*(lm/(lm+rm));
    Double_t RM = Xa*(rm/(lm+rm));
    Double_t BM = Ya*(bm/(bm+to));
    Double_t TM = Ya*(to/(bm+to));
    null->Range(x1-LM,yf-BM,x2+RM,y2+TM);

std::cout<<"x1-LM = " << x1-LM << std::endl;
std::cout<<"yf-BM = " << yf-BM << std::endl;
std::cout<<"x2+RM = " << x2+RM << std::endl;
std::cout<<"y2+TM = " << y2+TM << std::endl;




    // Some graphics in histogram's coordinates.
    TLine l;
    l.SetLineWidth(4);
    l.SetLineStyle(2);
    l.SetLineColor(kBlack);
    l.DrawLine(-3,-3,3,-3);
    l.DrawLine(-3,-3,-3,3);
    l.DrawLine(-3,3,3,3);
    l.DrawLine(3,3,3,-3);
    l.DrawLine(-2,-2,2,-2);
    l.DrawLine(-2,-2,-2,2);
    l.DrawLine(-2,2,2,2);
    l.DrawLine(2,2,2,-2);
    l.DrawLine(-1,-1,1,-1);
    l.DrawLine(-1,-1,-1,1);
    l.DrawLine(-1,1,1,1);
    l.DrawLine(1,1,1,-1);
    l.DrawLine(1,13,30, 13);
    //int yNDF = hist2D->GetNbinsY();

    //TLine *Ndf = new TLine(1,yNDF,hist2D->GetXaxis()->GetXmax(), yNDF);
  //  Ndf->SetLineWidth(4);
  //  Ndf->SetLineStyle(2);
  //  Ndf->SetLineColor(kBlack);
  //  Ndf->Draw();

  c1->Print(pdf);
}
/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////
void DrawMagration_heatMap_Label(MnvH2D *h_mig, const char* xaxislabel,const char* yaxislabel,
  const char* Title, const char* pdf, TCanvas *can, MnvPlotter *plotter, int rownormtype)
{

  TH2D *h_migration = (TH2D*)h_mig->Clone("h_migration");

  //RooUnfoldResponse UnfoldTool;

  int first_bin =  1;
  int last_bin_x =  h_migration->GetNbinsX();
  int last_bin_y =  h_migration->GetNbinsY();

  Int_t nbins_x =  h_migration->GetNbinsX();
  Int_t nbins_y =  h_migration->GetNbinsY();


  h_migration->GetXaxis()->SetTitle(xaxislabel);
  h_migration->GetXaxis()->CenterTitle();
  h_migration->GetYaxis()->SetTitle(yaxislabel);
  h_migration->GetYaxis()->CenterTitle();
  h_migration->SetMinimum(0.0);

  TMatrixD m_migration2(nbins_x, nbins_y);

  TH2D tmp2(*h_migration);
  tmp2.Reset();

  for (int y = first_bin; y <= last_bin_y; ++y){
    for (int x = first_bin; x <= last_bin_x; ++x){

      double bcx = ((TAxis*)h_migration->GetXaxis())->GetBinCenter(x);
      double bcy = ((TAxis*)h_migration->GetYaxis())->GetBinCenter(y);
      //int global_bin =   UnfoldTool.FindBin(h_migration, bcx,  bcy);
      double NumberperBin =  h_migration->GetBinContent(x,y);
      int global_bin = h_migration->GetBin(x, y);
      tmp2.SetBinContent(x, y, NumberperBin);

    }
  }

  tmp2.SetMinimum(0.0001);
  gStyle->SetTickLength(0.0,"x");
  gStyle->SetTickLength(0.0,"y");
  gStyle->SetPaintTextFormat("3.2f");
  gStyle->SetPalette(kBird);


  tmp2.SetMarkerSize(.42);
  tmp2.SetMarkerColor(kBlack);
  tmp2.GetXaxis()->SetTickLength(0.);
  tmp2.GetYaxis()->SetTickLength(0.);
  tmp2.SetBarOffset(-0.05);

  if(rownormtype==2)  colNormalize(tmp2);
  else if(rownormtype==3)  rowNormalize(tmp2);
  else{std::cout<<"Normtype none"<<std::endl;}


  tmp2.DrawCopy("colz text");

  plotter->AddHistoTitle(Title, .04);
  can->Print(pdf);
}//end of function
/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////
void DrawMagration_heatMap_Label(MnvH2D *h_mig, const char* xaxislabel,const char* yaxislabel,
  const char* Title, const char* pdf, TCanvas *can, MnvPlotter *plotter, int rownormtype, double Zmax)
{

  TH2D *h_migration = (TH2D*)h_mig->Clone("h_migration");

  //RooUnfoldResponse UnfoldTool;

  int first_bin =  1;
  int last_bin_x =  h_migration->GetNbinsX();
  int last_bin_y =  h_migration->GetNbinsY();

  Int_t nbins_x =  h_migration->GetNbinsX();
  Int_t nbins_y =  h_migration->GetNbinsY();


  h_migration->GetXaxis()->SetTitle(xaxislabel);
  h_migration->GetXaxis()->CenterTitle();
  h_migration->GetYaxis()->SetTitle(yaxislabel);
  h_migration->GetYaxis()->CenterTitle();
  h_migration->SetMinimum(0.0);
  h_migration->SetMaximum(Zmax);
  TMatrixD m_migration2(nbins_x, nbins_y);

  TH2D tmp2(*h_migration);
  tmp2.Reset();

  for (int y = first_bin; y <= last_bin_y; ++y){
    for (int x = first_bin; x <= last_bin_x; ++x){

      double bcx = ((TAxis*)h_migration->GetXaxis())->GetBinCenter(x);
      double bcy = ((TAxis*)h_migration->GetYaxis())->GetBinCenter(y);
      //int global_bin =   UnfoldTool.FindBin(h_migration, bcx,  bcy);
      double NumberperBin =  h_migration->GetBinContent(x,y);
      int global_bin = h_migration->GetBin(x, y);
      tmp2.SetBinContent(x, y, NumberperBin);

    }
  }

  tmp2.SetMinimum(0.0001);
  tmp2.SetMaximum(Zmax);
  gStyle->SetTickLength(0.0,"x");
  gStyle->SetTickLength(0.0,"y");
  gStyle->SetPaintTextFormat("3.2f");
  gStyle->SetPalette(kBird);


  tmp2.SetMarkerSize(.42);
  tmp2.SetMarkerColor(kBlack);
  tmp2.GetXaxis()->SetTickLength(0.);
  tmp2.GetYaxis()->SetTickLength(0.);
  tmp2.SetBarOffset(-0.05);

  if(rownormtype==2)  colNormalize(tmp2);
  else if(rownormtype==3)  rowNormalize(tmp2);
  else{std::cout<<"Normtype none"<<std::endl;}


  tmp2.DrawCopy("colz text");

  plotter->AddHistoTitle(Title, .04);
  can->Print(pdf);
}//end of function
/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////
void DrawMagration_heatMap_LabelBinNumber(MnvH2D *h_mig, const char* xaxislabel,const char* yaxislabel,
  const char* Title, const char* pdf, TCanvas *can, MnvPlotter *plotter)
{

  TH2D *h_migration = (TH2D*)h_mig->Clone("h_migration");

  //RooUnfoldResponse UnfoldTool;

  int first_bin =  1;
  int last_bin_x =  h_migration->GetNbinsX();
  int last_bin_y =  h_migration->GetNbinsY();

  Int_t nbins_x =  h_migration->GetNbinsX();
  Int_t nbins_y =  h_migration->GetNbinsY();


  h_migration->GetXaxis()->SetTitle(xaxislabel);
  h_migration->GetXaxis()->CenterTitle();
  h_migration->GetYaxis()->SetTitle(yaxislabel);
  h_migration->GetYaxis()->CenterTitle();
  h_migration->SetMinimum(0.0);

  TMatrixD m_migration(nbins_x, nbins_y);
  TMatrixD m_migration2(nbins_x, nbins_y);
  TH2D tmp(*h_migration);
  TH2D tmp2(*h_migration);
  tmp.Reset();
  tmp2.Reset();

  for (int y = first_bin; y <= last_bin_y; ++y){
    for (int x = first_bin; x <= last_bin_x; ++x){

      double bcx = ((TAxis*)h_migration->GetXaxis())->GetBinCenter(x);
      double bcy = ((TAxis*)h_migration->GetYaxis())->GetBinCenter(y);
      //int global_bin =   UnfoldTool.FindBin(h_migration, bcx,  bcy);
      double NumberperBin =  h_migration->GetBinContent(x,y);
      int global_bin = h_migration->GetBin(x, y);
      tmp.SetBinContent(x, y, global_bin);
      tmp2.SetBinContent(x, y, NumberperBin);

    }
  }

  tmp.SetMinimum(0.0);
  gStyle->SetTickLength(0.0,"x");
  gStyle->SetTickLength(0.0,"y");
  gStyle->SetPaintTextFormat("3.1f");
  gStyle->SetPalette(kBird);
  tmp.SetMarkerSize(.42);
  tmp.SetMarkerColor(kBlack);
  tmp.GetXaxis()->SetTickLength(0.);
  tmp.GetYaxis()->SetTickLength(0.);
  tmp.SetBarOffset(0.05);

  tmp2.SetMarkerSize(.42);
  tmp2.SetMarkerColor(kRed);
  tmp2.GetXaxis()->SetTickLength(0.);
  tmp2.GetYaxis()->SetTickLength(0.);
  tmp2.SetBarOffset(-0.05);

  tmp2.DrawCopy("colz text");
  tmp.DrawCopy("text Same");

  //h_mig->Draw("COLZ");
  plotter->AddHistoTitle(Title, .04);
  can->Print(pdf);
}//end of function

/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////
void DrawMagration_heatMap_LabelBinNumber_new(MnvH2D *h_mig,  const char* xaxislabel,const char* yaxislabel,
  const char* Title, const char* pdf, TCanvas *can, MnvPlotter *plotter,
   MnvH2D *h_binning ,int bini, int binningtype, int rownormtype, double text_size )
{

  TH2D *h_migration = (TH2D*)h_mig->Clone("h_migration");

  //RooUnfoldResponse UnfoldTool;

  int first_bin =  1;
  int last_bin_x =  h_migration->GetNbinsX();
  int last_bin_y =  h_migration->GetNbinsY();

  Int_t nbins_x =  h_migration->GetNbinsX();
  Int_t nbins_y =  h_migration->GetNbinsY();


  h_migration->GetXaxis()->SetTitle(xaxislabel);
  h_migration->GetXaxis()->CenterTitle();
  h_migration->GetYaxis()->SetTitle(yaxislabel);
  h_migration->GetYaxis()->CenterTitle();
  h_migration->SetMinimum(0.001);

  TMatrixD m_migration(nbins_x, nbins_y);
  TMatrixD m_migration2(nbins_x, nbins_y);
  TH2D tmp(*h_migration);
  TH2D tmp2(*h_migration);
  tmp.Reset();
  tmp2.Reset();

  for (int y = first_bin; y <= last_bin_y; ++y){
    for (int x = first_bin; x <= last_bin_x; ++x){

      double bcx = ((TAxis*)h_migration->GetXaxis())->GetBinCenter(x);
      double bcy = ((TAxis*)h_migration->GetYaxis())->GetBinCenter(y);
      //int global_bin =   UnfoldTool.FindBin(h_migration, bcx,  bcy);
      double NumberperBin =  h_migration->GetBinContent(x,y);
      int global_bin = h_migration->GetBin(x, y);
      tmp.SetBinContent(x, y, global_bin);
      bool isnan_bool = std::isnan(NumberperBin);
      if(isnan_bool == false)tmp2.SetBinContent(x, y, NumberperBin);
      else {tmp2.SetBinContent(x, y, 0.0);}

    }
  }



  tmp.SetMinimum(0.001);
  gStyle->SetTickLength(0.0,"x");
  gStyle->SetTickLength(0.0,"y");
  gStyle->SetPaintTextFormat("3.2f");
  gStyle->SetPalette(kBird);
  tmp.SetMarkerSize(.42);
  tmp.SetMarkerColor(kBlack);
  tmp.GetXaxis()->SetTickLength(0.);
  tmp.GetYaxis()->SetTickLength(0.);
  tmp.SetBarOffset(0.05);

  tmp2.SetMarkerSize(.42);
  tmp2.SetMarkerColor(kBlack);
  tmp2.GetXaxis()->SetTickLength(0.);
  tmp2.GetYaxis()->SetTickLength(0.);
  tmp2.SetBarOffset(-0.05);
  tmp2.GetZaxis()->SetLabelSize(0.01);

  if(rownormtype==2)  colNormalize(tmp2);
  else if(rownormtype==3)  rowNormalize(tmp2);
  else{std::cout<<"Normtype none"<<std::endl;}

  tmp2.DrawCopy("colz text");
  //tmp.DrawCopy("text Same");
  //drawBinRange(h_binning, binningtype, bini, xaxislabel, ".2f", true);
  drawBinRange(h_binning, binningtype, bini, xaxislabel, text_size, ".2f", true);
  //h_mig->Draw("COLZ");
  //plotter->AddHistoTitle(Title, .04);
  //can->Print(pdf);
}//end of function

/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////
void DrawMagration_heatMap_Mig(MnvH2D *h_mig, const char* xaxislabel,const char* yaxislabel,
  const char* Title, const char* pdf, TCanvas *can, MnvPlotter *plotter)
{

  TH2D *h_migration = (TH2D*)h_mig->Clone("h_migration");

  //RooUnfoldResponse UnfoldTool;

  int first_bin =  1;
  int last_bin_x =  h_migration->GetNbinsX();
  int last_bin_y =  h_migration->GetNbinsY();

  Int_t nbins_x =  h_migration->GetNbinsX();
  Int_t nbins_y =  h_migration->GetNbinsY();


  h_migration->GetXaxis()->SetTitle(xaxislabel);
  h_migration->GetXaxis()->CenterTitle();
  h_migration->GetYaxis()->SetTitle(yaxislabel);
  h_migration->GetYaxis()->CenterTitle();
  h_migration->SetMinimum(0.0);

  TMatrixD m_migration(nbins_x, nbins_y);
  TH2D tmp(*h_migration);
  tmp.Reset();


  for (int y = first_bin; y <= last_bin_y; ++y){
    for (int x = first_bin; x <= last_bin_x; ++x){

      double bcx = ((TAxis*)h_migration->GetXaxis())->GetBinCenter(x);
      double bcy = ((TAxis*)h_migration->GetYaxis())->GetBinCenter(y);
      //int global_bin =   UnfoldTool.FindBin(h_migration, bcx,  bcy);
      double NumberperBin =  h_migration->GetBinContent(x,y);
      int global_bin = h_migration->GetBin(x, y);
      tmp.SetBinContent(x, y, NumberperBin);

    }
  }

  tmp.SetMinimum(0.0);
  gStyle->SetTickLength(0.0,"x");
  gStyle->SetTickLength(0.0,"y");
  gStyle->SetPaintTextFormat("3.1f");
  gStyle->SetPalette(kBird);
  tmp.SetMarkerSize(.42);
  tmp.SetMarkerColor(kBlack);
  tmp.GetXaxis()->SetTickLength(0.);
  tmp.GetYaxis()->SetTickLength(0.);
  tmp.SetBarOffset(0.05);

  tmp.DrawCopy("colz text");

  //h_mig->Draw("COLZ");
  plotter->AddHistoTitle(Title, .04);
  can->Print(pdf);
}//end of function

/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////
void DrawMagration_heatMap_MigBinN(MnvH2D *h_mig, const char* xaxislabel,const char* yaxislabel,
  const char* Title, const char* pdf, TCanvas *can, MnvPlotter *plotter, int rownormtype)
{

  TH2D *h_migration = (TH2D*)h_mig->Clone("h_migration");

  //RooUnfoldResponse UnfoldTool;

  int first_bin =  1;
  int last_bin_x =  h_migration->GetNbinsX();
  int last_bin_y =  h_migration->GetNbinsY();

  Int_t nbins_x =  h_migration->GetNbinsX();
  Int_t nbins_y =  h_migration->GetNbinsY();


  h_migration->GetXaxis()->SetTitle(xaxislabel);
  h_migration->GetXaxis()->CenterTitle();
  h_migration->GetYaxis()->SetTitle(yaxislabel);
  h_migration->GetYaxis()->CenterTitle();
  h_migration->SetMinimum(0.0);

  TMatrixD m_migration(nbins_x, nbins_y);
  std::vector<double>BinN; BinN.push_back(.5);
  for(int i=1; i<=nbins_x;i++){BinN.push_back(i+.5);}
  TH2D *tmp =  new TH2D("tmp","tmp", BinN.size()-1, BinN.data(),BinN.size()-1, BinN.data()  );


  for (int y = first_bin; y <= last_bin_y; ++y){
    for (int x = first_bin; x <= last_bin_x; ++x){

      double bcx = ((TAxis*)h_migration->GetXaxis())->GetBinCenter(x);
      double bcy = ((TAxis*)h_migration->GetYaxis())->GetBinCenter(y);
      double NumberperBin =  h_migration->GetBinContent(x,y);
      tmp->SetBinContent(x, y, NumberperBin);

    }
  }

  if(rownormtype==2)  colNormalize(*tmp);
  else if(rownormtype==3)  rowNormalize(*tmp);


  tmp->SetMinimum(0.01);
  gStyle->SetTickLength(0.0,"x");
  gStyle->SetTickLength(0.0,"y");
  gStyle->SetPaintTextFormat("3.2f");
  gStyle->SetPalette(kBird);
  tmp->SetMarkerSize(1.1);
  tmp->SetMarkerColor(kBlack);
  tmp->GetXaxis()->SetTickLength(0.);
  tmp->GetYaxis()->SetTickLength(0.);
  //tmp->SetBarOffset(0.05);
  tmp->GetZaxis()->SetTitleSize(0.015);
  tmp->GetZaxis()->SetLabelSize(0.015);
  tmp->SetNdivisions(510);
  tmp->DrawCopy("colz text");

  //h_mig->Draw("COLZ");
  plotter->AddHistoTitle(Title, .04);
  can->Print(pdf);
}//end of function
/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////
void DrawMagration_heatMap_MigBinN(MnvH2D* h_mig, const char* xaxislabel, const char* yaxislabel,
    TCanvas* can, MnvPlotter* plotter, MnvH2D* h_binning, int bini, int binningtype,
    int rownormtype, double text_size_label, double marker_size_label, double setMax)
{

    TH2D* h_migration = (TH2D*)h_mig->Clone("h_migration");

    //RooUnfoldResponse UnfoldTool;

    int first_bin = 1;
    int last_bin_x = h_migration->GetNbinsX();
    int last_bin_y = h_migration->GetNbinsY();

    Int_t nbins_x = h_migration->GetNbinsX();
    Int_t nbins_y = h_migration->GetNbinsY();

    h_migration->GetXaxis()->SetTitle(xaxislabel);
    h_migration->GetXaxis()->CenterTitle();
    h_migration->GetYaxis()->SetTitle(yaxislabel);
    h_migration->GetYaxis()->CenterTitle();
    h_migration->SetMinimum(0.01);

    TMatrixD m_migration(nbins_x, nbins_y);
    std::vector<double> BinN;
    BinN.push_back(.5);
    for (int i = 1; i <= nbins_x; i++) {
        BinN.push_back(i + .5);
    }
    TH2D* tmp = new TH2D("tmp", "tmp", BinN.size() - 1, BinN.data(), BinN.size() - 1, BinN.data());

    for (int y = first_bin; y <= last_bin_y; ++y) {
        for (int x = first_bin; x <= last_bin_x; ++x) {

            double bcx = ((TAxis*)h_migration->GetXaxis())->GetBinCenter(x);
            double bcy = ((TAxis*)h_migration->GetYaxis())->GetBinCenter(y);
            double NumberperBin = h_migration->GetBinContent(x, y);
            tmp->SetBinContent(x, y, NumberperBin);
        }
    }

    if (rownormtype == 2)
        colNormalize(*tmp);
    else if (rownormtype == 3)
        rowNormalize(*tmp);

    tmp->SetMinimum(0.01);
    tmp->SetMaximum(setMax);
    gStyle->SetTickLength(0.0, "x");
    gStyle->SetTickLength(0.0, "y");
    gStyle->SetPaintTextFormat("3.2f");
    gStyle->SetPalette(kBird);
    tmp->SetMarkerSize(marker_size_label);
    tmp->SetMarkerColor(kBlack);
    tmp->GetXaxis()->SetTickLength(0.);
    tmp->GetYaxis()->SetTickLength(0.);
    //tmp->SetBarOffset(0.05);
    tmp->GetZaxis()->SetTitleSize(0.015);
    tmp->GetZaxis()->SetLabelSize(0.015);
    tmp->SetNdivisions(510);
    tmp->DrawCopy("colz text");
    drawBinRange_Red(h_binning, binningtype, bini, xaxislabel, text_size_label, ".2f", true);
    //h_mig->Draw("COLZ");
    //plotter->AddHistoTitle(Title, .04);

} //end of function
/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////
TF1* createPolynomialFunction(int N, double xmin, double xmax, double* parameters) {
    // Define the lambda function for the polynomial
    auto polynomial = [N](double* x, double* par) {
        double result = 0.0;
        for(int i=0; i<=N; i++) {
            result += par[i] * pow(x[0], i);
        }
        return result;
    };

    // Create a TF1 object with the polynomial function and set its name
    TString name = Form("polynomial%d", N);
    TF1* func = new TF1(name, polynomial, xmin, xmax, N+1);

    // Set the parameters of the polynomial function
    func->SetParameters(parameters);

    // Set the range of the function
    func->SetRange(xmin, xmax);

    return func;
}
/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////
double FindMaxSecondDerivative(TF1* fitFunc, double range_min, double range_max)
{
    // Define a new TF1 function that calculates the second derivative of the input TF1 function
    auto fitFunc2D = [&](double* x, double* p) {
        return fitFunc->Derivative2(x[0]);
    };

    // Create a new TF1 object that wraps the lambda function
    TF1* fitFunc2D_tf1 = new TF1("fitFunc2D", fitFunc2D, range_min, range_max, 0);

    // Use TF1::GetX() method to find the value of x where fitFunc2D_tf1 is maximum in the specified range
    double x_max = fitFunc2D_tf1->GetX(range_min, range_max, 0.0, 0.0);

    // Delete the temporary TF1 object
    delete fitFunc2D_tf1;

    // Return the value of x where the second derivative is maximum
    return x_max;
}
