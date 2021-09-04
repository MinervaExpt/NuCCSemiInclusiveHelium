
#include "HeliumPlotUtils.h"


std::string replaceAll(std::string source, const char toReplace, const std::string& with)
{
  for(size_t found = source.find(toReplace); found != std::string::npos; found = source.find(toReplace))
  {
    source.replace(found, 1, with);
  }
  return source;
}



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


void SetHist(TH1F * hist, char *xaxislabel , char *yaxislabel){

  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->CenterTitle();
  hist->GetXaxis()->SetTitle(xaxislabel);
  hist->GetYaxis()->SetTitle(yaxislabel);
  hist->GetXaxis()->SetTitleSize(0.038);
  hist->GetYaxis()->SetTitleSize(0.038);
  hist->SetMaximum(hist->GetMaximum() * 1.25);
}


void SetHist_Data(PlotUtils::MnvH1D* hist, char *xaxislabel , char *yaxislabel){

  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->CenterTitle();
  hist->GetXaxis()->SetTitle(xaxislabel);
  hist->GetYaxis()->SetTitle(yaxislabel);
  hist->GetXaxis()->SetTitleSize(0.038);
  hist->GetYaxis()->SetTitleSize(0.038);
  //hist->SetMaximum(hist->GetMaximum() * 1.25);
}

void SetMaxforDraw(PlotUtils::MnvH1D* hist_to_Draw,PlotUtils::MnvH1D* hist){

if(hist_to_Draw->GetMaximum() > hist->GetMaximum() ){
 hist_to_Draw->SetMaximum(hist_to_Draw->GetMaximum() * 1.20);
 hist->SetMaximum(hist_to_Draw->GetMaximum() * 1.20);
}
else {
hist_to_Draw->SetMaximum(hist->GetMaximum() * 1.20);
hist->SetMaximum(hist->GetMaximum() * 1.20);
}

}//end of function

void SetMaxforDraw(PlotUtils::MnvH1D* hist_to_Draw, PlotUtils::MnvH1D* hist,PlotUtils::MnvH1D* hist3  ){

if(hist_to_Draw->GetMaximum() > hist->GetMaximum() && hist_to_Draw->GetMaximum() > hist3->GetMaximum() ){
 hist_to_Draw->SetMaximum(hist_to_Draw->GetMaximum() * 1.35);}
else if (hist_to_Draw->GetMaximum() > hist->GetMaximum() && hist_to_Draw->GetMaximum() < hist3->GetMaximum()) {hist_to_Draw->SetMaximum(hist3->GetMaximum() * 1.35);}
else if (hist_to_Draw->GetMaximum() < hist->GetMaximum() && hist->GetMaximum() > hist3->GetMaximum()) {hist_to_Draw->SetMaximum(hist->GetMaximum() * 1.35);}

}//end of function




void PlotTotalError(PlotUtils::MnvH1D* hist, std::string method_str ){
  TH1D *hTotalErr = (TH1D*)hist->GetTotalError( include_stat_error, do_fractional_uncertainty, do_cov_area_norm ).Clone( Form("h_total_err_errSum_%d", __LINE__) );
  TCanvas cF ("c4","c4");
  hTotalErr->SetTitle(Form("Total Uncertainty (%s);", method_str.c_str()));
  hTotalErr->Draw();
  cF.Print(Form("Enu_TotalUncertainty_%s_%s_%s.pdf", do_fractional_uncertainty_str.c_str(), do_cov_area_norm_str.c_str(), method_str.c_str()));
}



////////////////////////////////////////////////////
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
  mnvPlotter.error_summary_group_map["Genie_FSI"].push_back("genie_FrElas_N");
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

void PlotErrorSummaryNew(PlotUtils::MnvH1D* hist, std::string pdf, std::string title, std::string xaxis, TCanvas *cE,MnvPlotter *mnvPlotter, bool Debug ,bool PrintAllGroupErrors)
{

  if(Debug==true){
    const auto allBandNames = hist->GetVertErrorBandNames();
    for(const auto& name: allBandNames)
    {
      //std::cout << "name = " << name<< std::endl;
    }

      for(auto cat :mnvPlotter->error_summary_group_map)
      {
        //std::cout << "cat.first =  " << cat.first <<std::endl;
        for(auto cat2: cat.second)
        {
          //std::cout << "cat.second =  " << cat2 <<std::endl;
        }
      }
    }

    hist->GetXaxis()->SetTitle(xaxis.c_str());
    mnvPlotter->DrawErrorSummary(hist, "TL", true, true, .00001, false , "" , true, "" , false);
    mnvPlotter->AddHistoTitle(Form("Error Summary (%s)", title.c_str()) ,.03);
    mnvPlotter->WritePreliminary("TR", .025, 0, 0, false);
    mnvPlotter->MultiPrint(cE, pdf, "pdf");

    if(PrintAllGroupErrors==true){
      std::cout<<"Printing Error Groups"<<std::endl;
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
        else{mnvPlotter->legend_n_columns = 2;}


        mnvPlotter->DrawErrorSummary( hist, "TL", true, true, .00001, false , cat.first , true, "" , false);
        sprintf(ErrorTitle, "%s Error Group %s", title.c_str(), cat.first.c_str());
        mnvPlotter->AddHistoTitle(ErrorTitle,.03);
        mnvPlotter->WritePreliminary("TR", .025, 0, 0, false);
        mnvPlotter->MultiPrint(cE, pdf, "pdf");
      }
    }

    else{
      std::cout<<"Skipped Printing Individal Group Errors"<<std::endl;
    }

    cE->Closed();

  }

void PlotErrorSummaryNew(PlotUtils::MnvH1D* hist, std::string pdf, std::string title, std::string xaxis, TCanvas *cE,MnvPlotter *mnvPlotter)
{

  //PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCompactStyle);
  //PlotUtils::MnvPlotter mnvPlotter;

  //DecodePosition (const std::string &opts, double size, int &align, double &xLabel, double &yLabel)
/*
   const auto allBandNames = hist->GetVertErrorBandNames();
   for(const auto& name: allBandNames)
   {
     std::cout << "name = " << name<< std::endl;}

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


     std::cout<< "checking the names again 2"<<std::endl;

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

       hist->GetXaxis()->SetTitle(xaxis.c_str());
       mnvPlotter->DrawErrorSummary(hist, "TR", true, true, .00001, false , "" , true, "" , true);

       mnvPlotter->AddHistoTitle(Form("Error Summary (%s)", title.c_str()) ,.04);
       mnvPlotter->WritePreliminary("TR", .03, 0, 0, false);
       mnvPlotter->MultiPrint(cE, pdf, "pdf");



  for(const auto& cat: mnvPlotter->error_summary_group_map)
  {cE->Clear();
     std::cout<< "cat.first = "<< cat.first<<std::endl;
     cE->SetTitle(cat.first.c_str());
     char ErrorTitle[1024];
     mnvPlotter->DrawErrorSummary( hist, "TR", true, true, .00001, false , cat.first , true, "" , false);
     sprintf(ErrorTitle, "(%s) Error Group %s", title.c_str(), cat.first.c_str());
     mnvPlotter->AddHistoTitle(ErrorTitle,.04);
     mnvPlotter->WritePreliminary("TR", .03, 0, 0, false);
     mnvPlotter->MultiPrint(cE, pdf, "pdf");
   }

   cE->Closed();

  //mnvPlotter.WritePreliminary("TR", .03, 0, 0, false);t
  //mnvPlotter.AddHistoTitle(Form("Error Summary (%s)", title.c_str()), .04);

  //std::string plotname = Form("Enu_CV_w_err_%s",label.c_str());
  //mnvPlotter.MultiPrint(&cE, pdf, "pdf");
}
///////////////////////////////////////////////////////////////////////////////


void PlotVertBand(std::string band, std::string method_str, PlotUtils::MnvH1D* hist){
  TH1* h1 = (TH1*)hist->GetVertErrorBand(band.c_str())->GetErrorBand(do_fractional_uncertainty, do_cov_area_norm).Clone(Form("Enu_%s_%s", band.c_str(), method_str.c_str()));
  //TH1* h1 = (TH1*)hist->GetVertErrorBand(band.c_str());
  TCanvas cF ("c4","c4");
  h1->SetTitle(Form("%s Uncertainty (%s); (GeV)", band.c_str(), method_str.c_str()));
  h1->Draw("h");
  cF.Print(Form("Enu_%s_band_%s.pdf", band.c_str(), method_str.c_str()));
}

void PlotLatBand(std::string band, std::string method_str, PlotUtils::MnvH1D* hist){
  TH1* h1 = (TH1*)hist->GetLatErrorBand(band.c_str())->GetErrorBand(do_fractional_uncertainty, do_cov_area_norm).Clone(Form("Enu_%s_%s", band.c_str(), method_str.c_str()));
  //TH1* h1 = (TH1*)hist->GetLatErrorBand(band.c_str());
  TCanvas cF ("c1","c1");
  h1->SetTitle(Form("%s Uncertainty (%s); (GeV)", band.c_str(), method_str.c_str()));
  h1->Draw("h");
  cF.Print(Form("Enu_%s_band_%s.pdf", band.c_str(), method_str.c_str()));
}

void PlotVertUniverse(std::string band, unsigned int universe, std::string method_str, PlotUtils::MnvH1D* hist){
  TH1D* h1 = hist->GetVertErrorBand(band.c_str())->GetHist(universe);

  TCanvas cF ("c1","c1");
  h1->SetLineColor(kBlack);
  h1->SetLineStyle(1);
  h1->Draw("hist");
  cF.Print(Form("Enu_%s_band_universe%i_%s.pdf", band.c_str(), universe+1, method_str.c_str()));
}

void PlotLatUniverse(std::string band, unsigned int universe, std::string method_str, PlotUtils::MnvH1D* hist){
  TH1D* h1 = hist->GetLatErrorBand(band.c_str())->GetHist(universe);
  TCanvas cF ("c1","c1");
  h1->SetLineColor(kBlack);
  h1->SetLineStyle(1);
  h1->Draw("hist");
  cF.Print(Form("%s_band_universe%i_%s.pdf", band.c_str(), universe+1, method_str.c_str()));
}

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








void Plot_MuonCVAndErrorWITHDATA(PlotUtils::MnvH1D* histFullMC,PlotUtils::MnvH1D* histEmptyMC, PlotUtils::MnvH1D* datahist_Full, PlotUtils::MnvH1D* datahist_Empty,std::string label,
  double POT[], MuonVar Muontype, int order,TCanvas * cE){
    PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCNuPionIncStyle  );
        std::string pdf;
    //double dataemptyscaler = POT[2] / POT[3];
    double MCemptyscaler = POT[0] / POT[1];
    //double MCFULLdatascaler = POT[2] / POT[0];
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
    //histFullMC->GetYaxis()->SetTitleOffset(offset);
    //histFullMC->GetXaxis()->SetTitleOffset(offset);

    mnvPlotter.DrawDataMCWithErrorBand(datahist_Full, histFullMC, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);
    mnvPlotter.AddHistoTitle(total_title, .04);
    mnvPlotter.MultiPrint(cE, plotname, pdf);
    cE->Closed();


  }



  void Plot_VectexCVAndErrorWITHDATA(PlotUtils::MnvH1D* histFullMC,PlotUtils::MnvH1D* histEmptyMC, PlotUtils::MnvH1D* datahist_Full, PlotUtils::MnvH1D* datahist_Empty,std::string label,
    double POT[], CryoVertex CryoVertex_type, int order,TCanvas * cE){
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

    //  ga->SetLabelSize(0.07*f);
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
      //histFullMC->GetYaxis()->SetTitleOffset(offset);
      //histFullMC->GetXaxis()->SetTitleOffset(offset);

      mnvPlotter.DrawDataMCWithErrorBand(datahist_Full, histFullMC, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);
      sprintf(total_title, "%s  %s", FILLED.c_str(), MuonVarType.c_str());

      mnvPlotter.AddHistoTitle(total_title, .04);
      mnvPlotter.MultiPrint(cE, plotname, pdf);
      cE->Closed();


    }


    void Plot_SecTRKCVAndErrorWITHDATA(PlotUtils::MnvH1D* histFullMC,PlotUtils::MnvH1D* histEmptyMC, PlotUtils::MnvH1D* datahist_Full, PlotUtils::MnvH1D* datahist_Empty,std::string label,
      double POT[], SecondTrkVar SecondTrkVar_type, int order,TCanvas * cE){
        PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCNuPionIncStyle );
        //float offset =.2;

        std::string pdf;
        //double dataemptyscaler = POT[2] / POT[3];
        double MCemptyscaler = POT[0] / POT[1];
        //double MCFULLdatascaler = POT[2] / POT[0];
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
        //histEmptyMC->GetYaxis()->SetTitleOffset(offset);
        //histEmptyMC->GetXaxis()->SetTitleOffset(offset);

      //  ga->SetLabelSize(0.07*f);
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

      void DrawStack_Material(bool my_debug, TFile *inputFile,  CryoVertex Vertex_type , ME_helium_Playlists PlayList , int doShape,
        int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf){

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

      void DrawStack_Interaction(bool my_debug, TFile *inputFile,  CryoVertex Vertex_type , ME_helium_Playlists PlayList , int doShape,
        int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf){

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

      void DrawStack_Particle(bool my_debug, TFile *inputFile,  CryoVertex Vertex_type , ME_helium_Playlists PlayList , int doShape,
        int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf){

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
/////////////////////////////////////////////////////////
void DrawStack_secTrk_Particle_FUll_EMPTY(bool my_debug, TFile *inputFile_FULL,TFile *inputFile_EMPTY, Pot_MapList POT_MC ,SecondTrkVar second_Trk_type ,ME_helium_Playlists PlayListFULL , ME_helium_Playlists PlayListEmpty,int doShape,
  int logScale, std::string Hist_name_addON, MnvPlotter *plot, TCanvas *can, const char *pdf){

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

          //hist->Scale(1,"width");
          //mystack[0]->Add(hist); //This might want you to derefence hist first
          //EMPTY_HISTS.insert({Particle, hist});
          EMPTY_HISTS_vector.push_back(hist);
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
  FULL_HISTS_vector[i]->Scale(1,"width");
  mystack[0]->Add(FULL_HISTS_vector[i]);
  //int n = ParticleName.length();
  //char char_array[n + 1];
  //strcpy(char_array, ParticleName.c_str());
  //legend->AddEntry(FULL_HISTS_vector[i], char_array);

}

/*
    for(auto Particle: Particle_vector){
      std::cout<<"count = "<< count<<" Particle ="<<Particle<<std::endl;
      auto ParticleName = GetNameParticle(Particle);
      EMPTY_HISTS_vector[count]->Scale(POT_scale_toFULL);
      FULL_HISTS_vector[count]->Add(EMPTY_HISTS_vector[count],-1);
      FULL_HISTS_vector[count]->Scale(1,"width");
      mystack[0]->Add(FULL_HISTS_vector[count]);
      int n = ParticleName.length();
      char char_array[n + 1];
      strcpy(char_array, ParticleName.c_str());
      legend->AddEntry(FULL_HISTS_vector[count], char_array);
      count++;
      std::cout<<"Bottom 3rd Loop count = "<< count<<" Particle ="<<Particle<<std::endl;
    }//end of  function
*/

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

void DrawStack_secTrk_Particle_FUll_EMPTY_WITHDATA(bool my_debug, TFile *inputFile_FULL,TFile *inputFile_EMPTY,TFile *inputFile_DATA_FULL,TFile *inputFile_DATA_EMPTY, Pot_MapList POT_MC ,Pot_MapList POT_DATA ,SecondTrkVar second_Trk_type ,ME_helium_Playlists PlayListFULL , ME_helium_Playlists PlayListEmpty,int doShape,
  int logScale, std::string Hist_name_addON, MnvPlotter *plot, TCanvas *can, const char *pdf){

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

          //hist->Scale(1,"width");
          //mystack[0]->Add(hist); //This might want you to derefence hist first
          //EMPTY_HISTS.insert({Particle, hist});

          EMPTY_HISTS_vector.push_back(hist);
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
  //int n = ParticleName.length();
  //char char_array[n + 1];
  //strcpy(char_array, ParticleName.c_str());
  //legend->AddEntry(FULL_HISTS_vector[i], char_array);

}

/*
    for(auto Particle: Particle_vector){
      std::cout<<"count = "<< count<<" Particle ="<<Particle<<std::endl;
      auto ParticleName = GetNameParticle(Particle);
      EMPTY_HISTS_vector[count]->Scale(POT_scale_toFULL);
      FULL_HISTS_vector[count]->Add(EMPTY_HISTS_vector[count],-1);
      FULL_HISTS_vector[count]->Scale(1,"width");
      mystack[0]->Add(FULL_HISTS_vector[count]);
      int n = ParticleName.length();
      char char_array[n + 1];
      strcpy(char_array, ParticleName.c_str());
      legend->AddEntry(FULL_HISTS_vector[count], char_array);
      count++;
      std::cout<<"Bottom 3rd Loop count = "<< count<<" Particle ="<<Particle<<std::endl;
    }//end of  function
*/

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

void DrawStack_Muon_Particle_FUll_EMPTY_WITHDATA(bool my_debug, TFile *inputFile_FULL,TFile *inputFile_EMPTY,TFile *inputFile_DATA_FULL,TFile *inputFile_DATA_EMPTY, Pot_MapList POT_MC ,Pot_MapList POT_DATA ,SecondTrkVar second_Trk_type ,ME_helium_Playlists PlayListFULL , ME_helium_Playlists PlayListEmpty,int doShape,
  int logScale, std::string Hist_name_addON, MnvPlotter *plot, TCanvas *can, const char *pdf){

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

          //hist->Scale(1,"width");
          //mystack[0]->Add(hist); //This might want you to derefence hist first
          //EMPTY_HISTS.insert({Particle, hist});
          EMPTY_HISTS_vector.push_back(hist);
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
//int count=0;





for(int i=0; i != FULL_HISTS_vector.size(); i++){
  //auto ParticleName = GetNameParticle(Particle_vector[i+1]);
  EMPTY_HISTS_vector[i]->Scale(POT_scale_toFULL);
  FULL_HISTS_vector[i]->Add(EMPTY_HISTS_vector[i],-1);
  FULL_HISTS_vector[i]->Scale(POT_scale_toFULL_MC_ToDATA);
  FULL_HISTS_vector[i]->Scale(1,"width");
  mystack[0]->Add(FULL_HISTS_vector[i]);

  //int n = ParticleName.length();
  //char char_array[n + 1];
  //strcpy(char_array, ParticleName.c_str());
  //legend->AddEntry(FULL_HISTS_vector[i], char_array);

}

/*
    for(auto Particle: Particle_vector){
      std::cout<<"count = "<< count<<" Particle ="<<Particle<<std::endl;
      auto ParticleName = GetNameParticle(Particle);
      EMPTY_HISTS_vector[count]->Scale(POT_scale_toFULL);
      FULL_HISTS_vector[count]->Add(EMPTY_HISTS_vector[count],-1);
      FULL_HISTS_vector[count]->Scale(1,"width");
      mystack[0]->Add(FULL_HISTS_vector[count]);
      int n = ParticleName.length();
      char char_array[n + 1];
      strcpy(char_array, ParticleName.c_str());
      legend->AddEntry(FULL_HISTS_vector[count], char_array);
      count++;
      std::cout<<"Bottom 3rd Loop count = "<< count<<" Particle ="<<Particle<<std::endl;
    }//end of  function
*/




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

/////////////////////////////////////////////////////////
      void DrawCVAndError_FromTFile( TFile *inputFile, char *histoName, char *histotitle ,std::string xaxislabel, std::string label){
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

      /////////////////////////////////////////////////////////
            void DrawCVAndError_FromTFile(bool PrintallErrors ,TFile *inputFile, char *histoName, char *histotitle ,std::string xaxislabel, std::string label){
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


//////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
      void DrawCVAndError_FromHistPointer(MnvH1D *hist, char *histotitle ,std::string xaxislabel, std::string yaxislabel,
         std::string label, bool doBinwidth, bool MakeXaxisLOG){

        PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
        TCanvas cE ("c1","c1");
        hist->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
        hist->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));
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



        mnvPlotter.draw_normalized_to_bin_width=doBinwidth;
        mnvPlotter.DrawDataMCWithErrorBand(datahist, hist, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);
        mnvPlotter.AddHistoTitle(histotitle);
        std::string plotname = Form("%s",label.c_str());
        mnvPlotter.MultiPrint(&cE, plotname, "pdf");
       mnvPlotter.legend_n_columns = 2;
      // PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);
       PlotErrorSummaryNew(hist, plotname, histotitle, xaxislabel.c_str(), &cE, &mnvPlotter,true,false);
       mnvPlotter.legend_n_columns = 1;


       if(MakeXaxisLOG==true){
       gPad->SetLogx(0);
       }

       if(doBinwidth==true){mnvPlotter.draw_normalized_to_bin_width= false;}


      }

      ////////////////////////////////
      void DrawCVAndError_FromHistPointer(MnvH1D *hist, char *histotitle ,std::string xaxislabel, std::string yaxislabel,
         std::string label, bool doBinwidth, bool MakeXaxisLOG, double maxY){

        PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
        TCanvas cE ("c1","c1");
        hist->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
        hist->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));
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

        mnvPlotter.draw_normalized_to_bin_width=doBinwidth;
        mnvPlotter.DrawDataMCWithErrorBand(datahist, hist, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);
        mnvPlotter.AddHistoTitle(histotitle);
        std::string plotname = Form("%s",label.c_str());
        mnvPlotter.MultiPrint(&cE, plotname, "pdf");
       mnvPlotter.legend_n_columns = 2;
      // PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);
       PlotErrorSummaryNew(hist, plotname, histotitle, xaxislabel.c_str(), &cE, &mnvPlotter,true,false);
       mnvPlotter.legend_n_columns = 1;


       if(MakeXaxisLOG==true){
       gPad->SetLogx(0);
       }

       if(doBinwidth==true){mnvPlotter.draw_normalized_to_bin_width= false;}


      }




      void DrawCVAndError_FromHIST(MnvH1D *hist, char *histotitle ,std::string xaxislabel,std::string yaxislabel,
        std::string pdf_name, bool Setgrid){



        PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
        TCanvas cE ("c1","c1");
        if(Setgrid==true){cE.SetGrid();}
        else if (Setgrid==false){cE.Clear();}
        hist->GetXaxis()->SetTitleSize(0.035);
        hist->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
        hist->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));

        hist->SetTitle(histotitle);
        PlotUtils::MnvH1D* datahist =new PlotUtils::MnvH1D("adsf", "", nbins, xmin, xmax);
        bool statPlusSys           = true;
        int mcScale                = 1.;
        bool useHistTitles         = false;


        //hist->Scale(1,"width");
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


      }

      void DrawCVAndError_FromHIST(bool PrintALLerrorGroups , MnvH1D *hist, char *histotitle ,std::string xaxislabel,std::string yaxislabel,
        std::string pdf_name, bool Setgrid){



        PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
        TCanvas cE ("c1","c1");
        if(Setgrid==true){cE.SetGrid();}
        else if (Setgrid==false){cE.Clear();}
        hist->GetXaxis()->SetTitleSize(0.035);
        hist->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
        hist->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));

        hist->SetTitle(histotitle);
        PlotUtils::MnvH1D* datahist =new PlotUtils::MnvH1D("adsf", "", nbins, xmin, xmax);
        bool statPlusSys           = true;
        int mcScale                = 1.;
        bool useHistTitles         = false;


        //hist->Scale(1,"width");
        mnvPlotter.DrawDataMCWithErrorBand(datahist, hist, mcScale, "TL", useHistTitles, NULL, NULL, false, statPlusSys);
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


      }
////////////////////////////////////////////////////
      void DrawCVAndError_FromHIST_withFit(MnvH1D *hist, char *histotitle ,std::string xaxislabel,std::string yaxislabel,
        std::string pdf_name, bool Setgrid, bool PrintErrors , bool PrintallErrorGroups ){



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


        mnvPlotter.AddHistoTitle(histotitle,.025);
        mnvPlotter.WritePreliminary("TR", .03, 0, 0, false);
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

void DrawCVAndError_FromHIST_withFit(MnvH1D *hist, char *histotitle ,std::string xaxislabel,std::string yaxislabel,
  std::string pdf_name, bool Setgrid , double &sigma_return , double &TotalN_return, double &chi_sq_return, int &NDF_return,
  double &Mean_return,  double &Constant_return, bool PrintErrors , bool PrintallErrorGroups )
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


      void DrawCVAndError_FromHIST(MnvH1D *hist, char *histotitle ,std::string xaxislabel,std::string yaxislabel,
         std::string pdf_name, bool Setgrid, bool LogX){
        //MnvH1D *hist=(MnvH1D*)hist_INCOMING->Clone();
        //MnvH1D *hist;
        //hist = hist_INCOMING->Clone("hist");


        PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
        TCanvas cE ("c1","c1");
        if(Setgrid==true){cE.SetGrid();}
        else if (Setgrid==false){cE.Clear();}

        hist->GetXaxis()->SetTitleSize(0.035);
        hist->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
        hist->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));

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




      void DrawDATAWITHCV_AndError_FromTFile_Single_playlist(TFile *inputFile, TFile *inputFile_data,Pot_MapList POT_MC,Pot_MapList POT_DATA,
        ME_helium_Playlists playlist_name, char *histoName,char *histoName_data, char *histotitle ,std::string xaxislabel, std::string label, bool MakeBinwidth_Norm){

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

      void DrawCVAndError_FromHIST_withVLine(MnvH1D *hist, char *histotitle ,std::string xaxislabel,std::string yaxislabel,
         std::string pdf_name, bool Setgrid, bool LogX, bool LogY, double xAxis_Vline){
        //MnvH1D *hist=(MnvH1D*)hist_INCOMING->Clone();
        //MnvH1D *hist;
        //hist = hist_INCOMING->Clone("hist");


        PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
        TCanvas cE ("c1","c1");
        if(Setgrid==true){cE.SetGrid();}
        else if (Setgrid==false){cE.Clear();}

        hist->GetXaxis()->SetTitleSize(0.035);
        hist->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
        hist->GetYaxis()->SetTitle(Form("%s",yaxislabel.c_str()));

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
        Vert_line->SetLineColor(kBlue);
        Vert_line->SetLineWidth(3);
        Vert_line->Draw();
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


      void DrawDATAWITHCV_AndError_FromTFile_Single_playlist_Full_EMPTY(TFile *inputFileFULL,TFile *inputFileEMPTY, TFile *inputFile_Fulldata,TFile *inputFile_Emptydata,Pot_MapList POT_MC,Pot_MapList POT_DATA,
        ME_helium_Playlists playlist_name_FULL,ME_helium_Playlists playlist_name_EMPTY, char *histoName,char *histoName_data, char *histotitle ,std::string xaxislabel, std::string label, bool MakeBinwidth_Norm){

          double mcScale                = POT_DATA[playlist_name_FULL]/POT_MC[playlist_name_FULL];
          double mcScaleEMPTYtoFULL                = POT_MC[playlist_name_FULL]/POT_MC[playlist_name_EMPTY];
          double dataScaleEMPTYtoFULL                = POT_DATA[playlist_name_FULL]/POT_DATA[playlist_name_EMPTY];

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


      void DrawCVAndError_FromTFile(TFile *inputFile_MCFULL, TFile *inputFile_MCEMPTY,  char *histoName_MC ,TFile *inputFile_DATAFULL,TFile *inputFile_DATAEMPTY,
                char *histoName_Data, Pot_MapStatusList POT_MC, Pot_MapStatusList POT_DATA, char *histotitle,
                std::string xaxislabel, std::string label, bool DoBinwidthNorm, bool doSmallerrorgrounps, std::string units)
      {    //helium_Status kEMPTY, kFULL;
          //PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCompactStyle);
          PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCNuPionIncStyle);
           TCanvas cE ("c1","c1");
           std::cout<<"trying MC HisName = "<< histoName_MC<<std::endl;
           std::cout<<"trying data HisName = "<< histoName_Data<<std::endl;

           double x1, x2, y1, y2;
           double scale_to_FULLData[4] = {POT_DATA[kFULL]/POT_MC[kFULL],  POT_DATA[kFULL]/POT_MC[kEMPTY]  , 1.0 , POT_DATA[kFULL]/POT_DATA[kEMPTY]  };
           MnvH1D *hist_a;
           MnvH1D *hist_b;
           MnvH1D *hist_ap1;
           MnvH1D *hist_bp1;


           for (int fullOrEmpty = 0; fullOrEmpty < 3; fullOrEmpty ++) {

             if(fullOrEmpty==0){
               hist_a = (MnvH1D*)inputFile_MCFULL -> Get(histoName_MC);
               hist_b = (MnvH1D*)inputFile_DATAFULL -> Get(histoName_Data);

               hist_a->Scale(scale_to_FULLData[0]);

               if(DoBinwidthNorm==true){
                 hist_a->Scale(1.0,"width");
                 hist_b->Scale(1.0,"width");
               }
             }

             else if (fullOrEmpty==1)
             {
               hist_a = (MnvH1D*)inputFile_MCEMPTY -> Get(histoName_MC);
               hist_b = (MnvH1D*)inputFile_DATAEMPTY -> Get(histoName_Data);

               hist_a->Scale(scale_to_FULLData[1]);
               hist_b->Scale(scale_to_FULLData[3]);

               if(DoBinwidthNorm==true){
                 hist_a->Scale(1.0,"width");
                 hist_b->Scale(1.0,"width");
               }


             }



             else if (fullOrEmpty==2){
               hist_a = (MnvH1D*)inputFile_MCFULL -> Get(histoName_MC);
               hist_ap1 = (MnvH1D*)inputFile_MCEMPTY -> Get(histoName_MC);
               hist_b = (MnvH1D*)inputFile_DATAFULL -> Get(histoName_Data);
               hist_bp1 = (MnvH1D*)inputFile_DATAEMPTY -> Get(histoName_Data);


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

             }




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
           int units_n = units.length();
           char units_char[units_n+1];
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




      void DrawStack_Material_MuonVar(bool my_debug, TFile *inputFile,  MuonVar MuonVar_type , ME_helium_Playlists PlayList , int doShape,
        int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf){

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

      void DrawStack_Interaction_MuonVar(bool my_debug, TFile *inputFile,  MuonVar MuonVar_type , ME_helium_Playlists PlayList , int doShape,
        int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf){

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

      void DrawStack_Particle_MuonVar(bool my_debug, TFile *inputFile,  MuonVar MuonVar_type , ME_helium_Playlists PlayList , int doShape,
        int logScale, const char* title, MnvPlotter *plot, TCanvas *can, const char *pdf){

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


void Draw2DHist(MnvH2D *hist, const char* xaxislabel,const char* yaxislabel,
                const char* Title, const char* pdf, TCanvas *can, MnvPlotter *plot)
    {


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
          can->Closed();


        }//end of 2D draw function


void Draw2DHist_TFILE(TFile *inputFile, const char* histoName, const char *Title, const char* xaxislabel,const char* yaxislabel,
  const char* pdf, TCanvas *can, MnvPlotter *plot, bool PrintText)
  {

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

  void Draw2DHist_hist(MnvH2D *hist_input, const char *Title, const char* xaxislabel,const char* yaxislabel,
           const char* pdf, TCanvas *can, MnvPlotter *plot){


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

void Draw2DHist_histWithTProfile(MnvH2D *hist_input, const char *Title, const char* xaxislabel,const char* yaxislabel,
  const char* pdf, TCanvas *can, MnvPlotter *plot){


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


  void Draw_XDistribution_PerBinWithGaussFit_2DHist(MnvH2D *hist_input, const char *Title, const char* xaxislabel,const char* yaxislabel,
    const char* pdf, TCanvas *can, MnvPlotter *plot, bool Setgrid, Double_t maxY ){

      char hist_Title[1024];
      MnvH2D *hist = (PlotUtils::MnvH2D*)hist_input->Clone("hist");
      std::map<double, MnvH1D*> hist_CutMap;
      std::vector<GaussianResolutionFits> GaussianFits_values_Resolution_vector;

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

          GaussianResolutionFits Fits;

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


        void Draw2DHist_NumberFigures_TFILE(TFile *inputFile, const char* histoName, const char *Title, const char* xaxislabel,const char* yaxislabel,
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



void DrawMagration_heatMap(TH2D *h_migration, const char* xaxislabel,const char* yaxislabel, const char* Title, const char* pdf, TCanvas *can, MnvPlotter *plotter )
{

  //std::vector<double> Binning_vector = DetermineBinning(h_migration, .5);
  //std::cout << "Made bins for"<<Title << std::endl;
  //std::cout << "double binLowEdges[] = { ";
  //for( std::vector<double>::iterator ibin = Binning_vector.begin(); ibin != Binning_vector.end(); ++ibin )
  //std::cout << *ibin << ",";
  //std::cout << " };" << std::endl;

  bool includeFlows = true;

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

  tmp.SetMarkerSize(0.7);
  tmp.DrawCopy("colz text");

  //h_mig->Draw("COLZ");
  plotter->AddHistoTitle(Title, .04);
  can->Print(pdf);
}//end of function

void DrawMagration_heatMap(MnvH2D *h_mig, const char* xaxislabel,const char* yaxislabel, const char* Title, const char* pdf, TCanvas *can, MnvPlotter *plotter )
{

  TH2D *h_migration = (TH2D*)h_mig->Clone("h_migration");
  //std::vector<double> Binning_vector = DetermineBinning(h_migration, .5);
  //std::cout << "Made bins for"<<Title << std::endl;
  //std::cout << "double binLowEdges[] = { ";
  //for( std::vector<double>::iterator ibin = Binning_vector.begin(); ibin != Binning_vector.end(); ++ibin )
  //std::cout << *ibin << ",";
  //std::cout << " };" << std::endl;

  bool includeFlows =false;

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

  gStyle->SetTickLength(0.0,"x");
  gStyle->SetTickLength(0.0,"y");
  gStyle->SetPaintTextFormat("0.2f");
  tmp.SetMarkerSize(.7);
  tmp.GetXaxis()->SetTickLength(0.);
  tmp.GetYaxis()->SetTickLength(0.);
  tmp.DrawCopy("colz text");


  //h_mig->Draw("COLZ");
  plotter->AddHistoTitle(Title, .04);
  can->Print(pdf);
}//end of function
//////////////////////////////////////////////////

void DrawMagration_heatMap_noText(MnvH2D *h_mig, const char* xaxislabel,const char* yaxislabel, const char* Title, const char* pdf, TCanvas *can, MnvPlotter *plotter )
{

  TH2D *h_migration = (TH2D*)h_mig->Clone("h_migration");
  //std::vector<double> Binning_vector = DetermineBinning(h_migration, .5);
  //std::cout << "Made bins for"<<Title << std::endl;
  //std::cout << "double binLowEdges[] = { ";
  //for( std::vector<double>::iterator ibin = Binning_vector.begin(); ibin != Binning_vector.end(); ++ibin )
  //std::cout << *ibin << ",";
  //std::cout << " };" << std::endl;

  bool includeFlows =false;

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

/*
     hist_ALONE_totalFULL->Draw("HIST");
     mystack[1]->Draw("HIST SAME");
     datahist_ALONE_FULL->Draw(" SAME");
     legendFULL->Draw();
     plot->AddHistoTitle(FinalTitleFULL, .04);
     plot->WritePreliminary("TL", .035, 0, 0, false);
     can -> Print(pdf);

     hist_ALONE_totalEMPTY->Draw("HIST");
     mystack[2]->Draw("HIST SAME");
     datahist_ALONE_EMPTY->Draw(" SAME");
     legendEMPTY->Draw();
     plot->AddHistoTitle(FinalTitlEMPTY, .04);
     plot->WritePreliminary("TL", .035, 0, 0, false);
     can -> Print(pdf);

*/

}//ENd of DrawStack_paricle

void DrawCVAndError_FromTFile(TFile *inputFile_MCFULL, TFile *inputFile_MCEMPTY,  char *histoName_MC ,TFile *inputFile_DATAFULL,TFile *inputFile_DATAEMPTY,
                char *histoName_Data, Pot_MapStatusList POT_MC, Pot_MapStatusList POT_DATA,bool TrueifFullelseEmpty, char *histotitle,
                std::string xaxislabel, std::string label, bool DoBinwidthNorm, bool doSmallerrorgrounps, std::string units, int Print_Error ,bool Debug)
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


           for (int fullOrEmpty = 0; fullOrEmpty < 3; fullOrEmpty ++) {

             if(fullOrEmpty==0){
               if(Debug==true){std::cout<<"Starting to initialize FUll MC in DrawCVAndError_FromTFile for: " <<histoName_MC<<std::endl; }

               hist_a = (MnvH1D*)inputFile_MCFULL -> Get(histoName_MC);
               if(Debug==true){std::cout<<" Final initialize FUll MC in DrawCVAndError_FromTFile for: " <<histoName_MC<<std::endl; }

               if(Debug==true){std::cout<<"Starting to initialize FUll MC in DrawCVAndError_FromTFile for: " <<histoName_MC<<std::endl; }
               hist_b = (MnvH1D*)inputFile_DATAFULL -> Get(histoName_Data);
               if(Debug==true){std::cout<<"initialize FUll data in DrawCVAndError_FromTFile for: " <<histoName_Data<<std::endl; }

               hist_a->Scale(scale_to_FULLData[0]);

               if(Debug==true){std::cout<<"POT scaled full MC " <<histoName_Data<<std::endl; }


               if(DoBinwidthNorm==true){
                 if(Debug==true){std::cout<<"Bin Width Norm full MC and Data " <<histoName_Data<<std::endl; }


               }

             }

             else if (fullOrEmpty==1)
             { if(Debug==true){std::cout<<"Starting to initialize Empty MC in DrawCVAndError_FromTFile for: " <<histoName_MC<<std::endl; }
               hist_a = (MnvH1D*)inputFile_MCEMPTY -> Get(histoName_MC);
               if(Debug==true){std::cout<<"initialize Empty MC in DrawCVAndError_FromTFile for: " <<histoName_MC<<std::endl; }
               if(Debug==true){std::cout<<"Starting to initialize Empty Data in DrawCVAndError_FromTFile for: " <<histoName_MC<<std::endl; }
               hist_b = (MnvH1D*)inputFile_DATAEMPTY -> Get(histoName_Data);
               if(Debug==true){std::cout<<"initialize EMTPY data in DrawCVAndError_FromTFile for: " <<histoName_Data<<std::endl; }

               hist_a->Scale(scale_to_FULLData[1]);
               hist_b->Scale(scale_to_FULLData[3]);
               if(Debug==true){std::cout<<"POT scaled Empty MC and Empty Data " <<histoName_Data<<std::endl; }

             }

             else if (fullOrEmpty==2){
               hist_a = (MnvH1D*)inputFile_MCFULL -> Get(histoName_MC);
               hist_ap1 = (MnvH1D*)inputFile_MCEMPTY -> Get(histoName_MC);
               hist_b = (MnvH1D*)inputFile_DATAFULL -> Get(histoName_Data);
               hist_bp1 = (MnvH1D*)inputFile_DATAEMPTY -> Get(histoName_Data);

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
           sprintf(ytitle, "Number of Events / %.2f %s", binwidth_title, units_char); //
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

       void DrawCVAndError_FromTFile(TFile *inputFile_MCFULL, TFile *inputFile_MCEMPTY,  char *histoName_MC ,
                                     TFile *inputFile_DATAFULL,TFile *inputFile_DATAEMPTY,
                       char *histoName_Data, Pot_MapStatusList POT_MC, Pot_MapStatusList POT_DATA,bool TrueifFullelseEmpty, char *histotitle,
                       std::string xaxislabel, std::string label, bool DoBinwidthNorm, bool doSmallerrorgrounps, std::string units,
                       int Print_Error,bool Debug, bool Makelogx, bool Makelogy )
             {    //helium_Status kEMPTY, kFULL;

               std::vector<bool> Print_Vector = Print_Systematics(Print_Error);


                PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
                //PlotUtils::MnvPlotter mnvPlotter();
                  TCanvas cE ("c1","c1");
                  std::cout<<"trying MC HisName = "<< histoName_MC<<std::endl;
                  std::cout<<"trying data HisName = "<< histoName_Data<<std::endl;
                  bool MakeXaxisLOG = Makelogx;
                  double scale_to_FULLData[4] = {POT_DATA[kFULL]/POT_MC[kFULL],  POT_DATA[kFULL]/POT_MC[kEMPTY]  , 1.0 , POT_DATA[kFULL]/POT_DATA[kEMPTY]  };
                  MnvH1D *hist_a;
                  MnvH1D *hist_b;
                  MnvH1D *hist_ap1;
                  MnvH1D *hist_bp1;


                  for (int fullOrEmpty = 0; fullOrEmpty < 3; fullOrEmpty ++) {

                    if(fullOrEmpty==0){
                      if(Debug==true){std::cout<<"Starting to initialize FUll MC in DrawCVAndError_FromTFile for: " <<histoName_MC<<std::endl; }

                      hist_a = (MnvH1D*)inputFile_MCFULL -> Get(histoName_MC);
                      if(Debug==true){std::cout<<" Final initialize FUll MC in DrawCVAndError_FromTFile for: " <<histoName_MC<<std::endl; }

                      if(Debug==true){std::cout<<"Starting to initialize FUll MC in DrawCVAndError_FromTFile for: " <<histoName_MC<<std::endl; }
                      hist_b = (MnvH1D*)inputFile_DATAFULL -> Get(histoName_Data);
                      if(Debug==true){std::cout<<"initialize FUll data in DrawCVAndError_FromTFile for: " <<histoName_Data<<std::endl; }

                      hist_a->Scale(scale_to_FULLData[0]);

                      if(Debug==true){std::cout<<"POT scaled full MC " <<histoName_Data<<std::endl; }


                      if(DoBinwidthNorm==true){
                        if(Debug==true){std::cout<<"Bin Width Norm full MC and Data " <<histoName_Data<<std::endl; }


                      }

                    }

                    else if (fullOrEmpty==1)
                    { if(Debug==true){std::cout<<"Starting to initialize Empty MC in DrawCVAndError_FromTFile for: " <<histoName_MC<<std::endl; }
                      hist_a = (MnvH1D*)inputFile_MCEMPTY -> Get(histoName_MC);
                      if(Debug==true){std::cout<<"initialize Empty MC in DrawCVAndError_FromTFile for: " <<histoName_MC<<std::endl; }
                      if(Debug==true){std::cout<<"Starting to initialize Empty Data in DrawCVAndError_FromTFile for: " <<histoName_MC<<std::endl; }
                      hist_b = (MnvH1D*)inputFile_DATAEMPTY -> Get(histoName_Data);
                      if(Debug==true){std::cout<<"initialize EMTPY data in DrawCVAndError_FromTFile for: " <<histoName_Data<<std::endl; }

                      hist_a->Scale(scale_to_FULLData[1]);
                      hist_b->Scale(scale_to_FULLData[3]);
                      if(Debug==true){std::cout<<"POT scaled Empty MC and Empty Data " <<histoName_Data<<std::endl; }

                    }

                    else if (fullOrEmpty==2){
                      hist_a = (MnvH1D*)inputFile_MCFULL -> Get(histoName_MC);
                      hist_ap1 = (MnvH1D*)inputFile_MCEMPTY -> Get(histoName_MC);
                      hist_b = (MnvH1D*)inputFile_DATAFULL -> Get(histoName_Data);
                      hist_bp1 = (MnvH1D*)inputFile_DATAEMPTY -> Get(histoName_Data);

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

                  char ytitle[100];
                  char xaxislabel_char[xaxislabel.length()+1];
                  strcpy( xaxislabel_char,xaxislabel.c_str());

                  char units_char[units.length()+1];
                  strcpy( units_char,units.c_str());


                  double binwidth_title = hist_a -> GetBinWidth(3);
                  sprintf(ytitle, "Number of Events / %.2f %s", binwidth_title, units_char); //
                  char total_title[1024];
                  sprintf(total_title, "%s[%s] %s", histotitle, emptyFull," (POT Norm) ");

                  //if(DoBinwidthNorm==true){
                 //   hist_a->Scale(1.0,"width");
                 //   hist_b->Scale(1.0,"width");
                 // }

                  Draw_DataWITHMC_SingleHistinput_withRatio(hist_a, hist_b,
                   " ", label, total_title, units,
                   xaxislabel_char,  ytitle, DoBinwidthNorm, MakeXaxisLOG, Makelogy, doSmallerrorgrounps);

                  if (fullOrEmpty == 2) {
                    hist_a -> Clear();
                    hist_ap1 -> Clear();
                    hist_b -> Clear();
                    hist_bp1 -> Clear();
                  }
                  cE.Closed();
                }

              }





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
            int units_n = units.length();
            char units_char[units_n+1];
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


        void Draw2DRatio_FromTFile(TFile *inputFile_numerator, TFile *inputFile_demonator,char *histoName_num,char *histoName_dem,
           char *num_labelname_y,char *dem_labelname_y, char *num_labelname_x, char *dem_labelname_x,char *histotitle, const char* pdf,TCanvas *can, MnvPlotter *plot)
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
    int units_n = units.length();
    char units_char[units_n+1];
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
    int units_n = units.length();
    char units_char[units_n+1];
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

//////////////////////////////////////////////////////////////////////////////


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
    int units_n = units.length();
    char units_char[units_n+1];
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










void Draw2DHist_Full_Empty_TFILE(TFile *inputFile_Full,TFile *inputFile_Empty, const char* histoName, Pot_MapList POT_MC, ME_helium_Playlists PlayListFULL, ME_helium_Playlists PlayListEmpty,
      const char *Title, const char* xaxislabel,const char* yaxislabel, const char* pdf, TCanvas *can, MnvPlotter *plot){
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
  SetHist_CRYOTankR(CryoTankTGraphR_Z, "Vertex Z [mm]" , "Vertex R [mm]");

  auto CryoTankTGraphRR_Z =Tank_Z_R_or_RR(1);
  SetHist_CRYOTankRR(CryoTankTGraphRR_Z, "Vertex Z [mm]" , "Vertex R^2 [mm]");


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
  SetHist_SizeMarker(Y_vs_Z_Tgraph);
  auto X_vs_Z_Tgraph = Make_X_vs_Z_Tgraph_fromVector(input_XYZ_vector);
  SetHist_SizeMarker(X_vs_Z_Tgraph);
  auto R_vs_Z_Tgraph = Make_R_vs_Z_Tgraph_fromVector(input_XYZ_vector);
  SetHist_SizeMarker(R_vs_Z_Tgraph);
  auto RR_vs_Z_Tgraph = Make_RR_vs_Z_Tgraph_fromVector(input_XYZ_vector);
  SetHist_SizeMarker(RR_vs_Z_Tgraph);
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
  sprintf(Plot_title,"%s [%s] [X vs Z Vector Position]",title, Playlist);
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
  sprintf(Plot_title,"%s [%s] [Y vs Z Vector Position]",title, Playlist);
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
  sprintf(Plot_title,"%s [%s] [R vs Z Vector Position]",title, Playlist);
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
  sprintf(Plot_title,"%s [%s] [R^{2} vs Z Vector Position]",title, Playlist);
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
  SetHist_CRYOTankR(CryoTankTGraphR_Z, "Vertex Z [mm]" , "Vertex R [mm]");

  auto CryoTankTGraphRR_Z =Tank_Z_R_or_RR(1);
  SetHist_CRYOTankRR(CryoTankTGraphRR_Z, "Vertex Z [mm]" , "Vertex R^2 [mm]");


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
  SetHist_SizeMarker(Y_vs_Z_Tgraph_He);
  auto X_vs_Z_Tgraph_He = Make_X_vs_Z_Tgraph_fromVector(input_XYZ_vector_He);
  SetHist_SizeMarker(X_vs_Z_Tgraph_He);
  auto R_vs_Z_Tgraph_He = Make_R_vs_Z_Tgraph_fromVector(input_XYZ_vector_He);
  SetHist_SizeMarker(R_vs_Z_Tgraph_He);
  auto RR_vs_Z_Tgraph_He = Make_RR_vs_Z_Tgraph_fromVector(input_XYZ_vector_He);
  SetHist_SizeMarker(RR_vs_Z_Tgraph_He);

  auto Y_vs_Z_Tgraph_Al = Make_Y_vs_Z_Tgraph_fromVector(input_XYZ_vector_Al);
  SetHist_SizeMarker(Y_vs_Z_Tgraph_Al);
  auto X_vs_Z_Tgraph_Al = Make_X_vs_Z_Tgraph_fromVector(input_XYZ_vector_Al);
  SetHist_SizeMarker(X_vs_Z_Tgraph_Al);
  auto R_vs_Z_Tgraph_Al = Make_R_vs_Z_Tgraph_fromVector(input_XYZ_vector_Al);
  SetHist_SizeMarker(R_vs_Z_Tgraph_Al);
  auto RR_vs_Z_Tgraph_Al = Make_RR_vs_Z_Tgraph_fromVector(input_XYZ_vector_Al);
  SetHist_SizeMarker(RR_vs_Z_Tgraph_Al);

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
  plot->DecodeLegendPosition(x1, y1, x2, y2, "R", 6.5, 6., .025);
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
  sprintf(Plot_title,"%s [%s] [X vs Z Vector Position]",title, Playlist);
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

  SetHist_Data(hist_FULL, xaxislabel , yaxislabel);
  SetHist_Data(hist_EMPTY, xaxislabel , yaxislabel);
  SetHist_Data(hist_FULL_EMPTY, xaxislabel , yaxislabel);


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

  SetHist_Data(hist_FULL, xaxislabel , yaxislabel);
  SetHist_Data(hist_EMPTY, xaxislabel , yaxislabel);
  SetHist_Data(hist_FULL_EMPTY, xaxislabel , yaxislabel);


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

void Draw_DataWITHMC_SingleHistinput(MnvH1D *hist_MC, MnvH1D *hist_Data,
  char *Playlist_name, std::string pdf_label, char *histotitle, std::string units,
   char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG)
{

  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE ("c1","c1");
  double x1,x2,y1,y2;
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", .5, 10, .025);
  TLegend *legend = new TLegend(x1 - .02, y1+.31 , x2 +.06 , y2 + .42  );


  string TotalTitle = string(histotitle);

  SetHist_Data(hist_MC, xaxislabel , yaxislabel);

  if(MakeXaxisLOG==true){
    gPad->SetLogx();
  }

  SetMaxforDraw(hist_MC,hist_Data);

  legend->SetNColumns(1);
  legend->SetTextSize(.03);
  legend->SetFillColor(0);

  char ytitle[100];
  int units_n = units.length();
  char units_char[units_n+1];
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
  mnvPlotter.draw_normalized_to_bin_width=DoBinwidthNorm;
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
void Draw_DataWITHMC_SingleHistinput_withRatio(MnvH1D *hist_MC, MnvH1D *hist_Data,
  char *Playlist_name, std::string pdf_label, char *histotitle, std::string units,
   char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG, bool MakeYaxisLOG , bool drawAllErrorGroups )
{

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
  TLegend *legend = new TLegend(x1 - .02, y1+.31 , x2 +.075 , y2 + .42  );


  string TotalTitle = string(histotitle);

  SetHist_Data(hist_MC, xaxislabel , yaxislabel);

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
  int units_n = units.length();
  char units_char[units_n+1];
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
  mnvPlotter.draw_normalized_to_bin_width=DoBinwidthNorm;
  //mnvPlotter.axis_title_size_y = 0.08;
  mnvPlotter.axis_title_size_y = 0.037;
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
  pad2->SetBottomMargin(0.2);
  pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  mnvPlotter.axis_title_size_x = 0.09;
  mnvPlotter.axis_title_size_y = 0.08;
  mnvPlotter.axis_label_size = 0.09;
  mnvPlotter.DrawDataMCRatio(hist_Data, hist_MC);
  cE.cd();

  std::string plotname = Form("%s",pdf_label.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");
  mnvPlotter.legend_n_columns = 2;
 // PlotErrorSummary(hist, plotname, histotitle, xaxislabel.c_str(), &cE);
 std::string xaxislabel_string(xaxislabel);
 mnvPlotter.axis_title_size_x = 0.038;
 mnvPlotter.axis_title_size_y = 0.038;
 mnvPlotter.axis_label_size = 0.038;
  PlotErrorSummaryNew(hist_MC, plotname, histotitle, xaxislabel_string.c_str(), &cE, &mnvPlotter,true, drawAllErrorGroups);
  mnvPlotter.legend_n_columns = 1;

  cE.Closed();

  if(MakeXaxisLOG==true){
    gPad->SetLogx(0);
  }
  if(MakeYaxisLOG==true){
    gPad->SetLogy(0);
  }

} // end of Function
/////////////////////////////////////////////////////////////////////////////////////////////
void Draw_DataWITHMC_SingleHistinput_withRatioCrossSection(MnvH1D *hist_MC, MnvH1D *hist_Data,
  char *Playlist_name, std::string pdf_label, char *histotitle, std::string units,
   char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG , bool drawAllErrorGroups )
{

  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  TCanvas cE("cE","cE", 800, 800);
  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  double x1,x2,y1,y2;
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", .5, 10, .025);
  TLegend *legend = new TLegend(x1 - .02, y1+.31 , x2 +.075 , y2 + .42  );


  string TotalTitle = string(histotitle);

  SetHist_Data(hist_MC, xaxislabel , yaxislabel);

  if(MakeXaxisLOG==true){
    gPad->SetLogx();
  }

  SetMaxforDraw(hist_MC,hist_Data);

  legend->SetNColumns(1);
  legend->SetTextSize(.03);
  legend->SetFillColor(0);

  char ytitle[100];
  int units_n = units.length();
  char units_char[units_n+1];
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
  mnvPlotter.draw_normalized_to_bin_width=DoBinwidthNorm;
  //mnvPlotter.axis_title_size_y = 0.08;
  mnvPlotter.axis_title_size_y = 0.045;
  mnvPlotter.axis_title_offset_y = 1.6;
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
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  mnvPlotter.axis_title_size_x = 0.09;
  mnvPlotter.axis_title_size_y = 0.09;
  mnvPlotter.axis_label_size = 0.09;
  mnvPlotter.DrawDataMCRatio(hist_Data, hist_MC);
  cE.cd();

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

  SetHist_Data(hist_MC, xaxislabel , yaxislabel);

  if(MakeXaxisLOG==true){
    gPad->SetLogx();
  }

  SetMaxforDraw(hist_MC,hist_Data);

  legend->SetNColumns(1);
  legend->SetTextSize(.03);
  legend->SetFillColor(0);

  char ytitle[100];
  int units_n = units.length();
  char units_char[units_n+1];
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

void Draw_DataWITHMC_SingleHistinput_withRatio(MnvH1D *hist_MC, MnvH1D *hist_Data,
  char *Playlist_name, std::string pdf_label, char *histotitle, std::string units,
   char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG, double POT_data, double POT_MC ,  bool drawAllErrorGroups)
{

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

  SetHist_Data(hist_MC, xaxislabel , yaxislabel);

  if(MakeXaxisLOG==true){
    gPad->SetLogx();
  }

  SetMaxforDraw(hist_MC,hist_Data);

  legend->SetNColumns(1);
  legend->SetTextSize(.03);
  legend->SetFillColor(0);

  char ytitle[100];
  int units_n = units.length();
  char units_char[units_n+1];
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
  mnvPlotter.draw_normalized_to_bin_width=DoBinwidthNorm;
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
  pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  mnvPlotter.axis_title_size_x = 0.09;
  mnvPlotter.axis_title_size_y = 0.08;
  mnvPlotter.axis_label_size = 0.09;
  mnvPlotter.DrawDataMCRatio(hist_Data, hist_MC);
  cE.cd();
  std::string plotname = Form("%s",pdf_label.c_str());
  mnvPlotter.MultiPrint(&cE, plotname, "pdf");
  mnvPlotter.legend_n_columns = 2;
  mnvPlotter.axis_title_size_x = 0.038;
  mnvPlotter.axis_title_size_y = 0.038;
  mnvPlotter.axis_label_size = 0.038;
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

  SetHist_Data(hist_FULL, xaxislabel , yaxislabel);
  SetHist_Data(hist_EMPTY, xaxislabel , yaxislabel);
  SetHist_Data(hist_FULL_EMPTY, xaxislabel , yaxislabel);


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

  SetHist_Data(hist_FULL, xaxislabel , yaxislabel);
  SetHist_Data(hist_EMPTY, xaxislabel , yaxislabel);
  SetHist_Data(hist_FULL_EMPTY, xaxislabel , yaxislabel);


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
   MnvH1D *hist_RECOMC, MnvH1D *hist_TRUTH_Convolution,MnvH1D *hist_TRUTH,
  char *Playlist_name, std::string pdf_label, char *histotitle,char* playlist_status,
   char *xaxislabel,char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG, double Ymax, double ConvolutedBymm )
{
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  mnvPlotter.axis_title_size_x = 0.09;
  mnvPlotter.axis_title_size_y = 0.09;
  mnvPlotter.axis_label_size = 0.09;

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
  SetHist_Data(h_Data, xaxislabel , yaxislabel);




  if(DoBinwidthNorm==true){
    h_Data->Scale(1.0,"width");
    h_RECO->Scale(1.0,"width");
    h_TRUTH->Scale(1.0,"width");
    h_TRUTH_Convol->Scale(1.0,"width");
  }

  if(MakeXaxisLOG==true){
    gPad->SetLogx();
  }
  SetHist_Data(hist_Data, xaxislabel , yaxislabel);
  auto Data_Clone_1 = (PlotUtils::MnvH1D*)hist_Data->Clone("Data_Clone_1");
  auto Data_Clone_2 = (PlotUtils::MnvH1D*)hist_Data->Clone("Data_Clone_2");


  double x1, x2, y1, y2;
  mnvPlotter.DecodeLegendPosition(x1, y1, x2, y2, "R", 6.5, 6., .025);
  TLegend *legend1 = new TLegend(x1 - .02, y1 + .18, x2 + .075, y2 + .3); // .2,.34
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
  sprintf(Covoluteed, "Convoluted by %.1f [mm]",ConvolutedBymm);

  mnvPlotter.AddPlotLabel(Covoluteed, xLabel + .2 , yLabel - .13);


  cE.cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.2);
  pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  Data_Clone_1->Divide(Data_Clone_1, h_TRUTH_Convol);
  Data_Clone_1->SetLineColor(kRed);
  mnvPlotter.axis_title_offset_y = .4;
  Data_Clone_2->Divide(Data_Clone_2, h_RECO);
  Data_Clone_2->SetLineColor(49);
  Data_Clone_1->GetYaxis()->SetTitle("Ratio[#frac{Data}{MC}]");
  Data_Clone_1->GetYaxis()->SetTitleOffset(mnvPlotter.axis_title_offset_y );
  Data_Clone_1->GetXaxis()->SetTitleSize(mnvPlotter.axis_title_size_x);
  Data_Clone_1->GetYaxis()->SetTitleSize(mnvPlotter.axis_title_size_y);
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


//////////////////////////////////////////////////////////////////////////////
void Draw_Data_RECO_TRUTH_Hist_fromPointer( MnvH1D *histMC_TRUTH, MnvH1D *histMC_RECO,  MnvH1D *hist_Data,
  char *Playlist_name, char* playlist_status, std::string pdf_label, char *histotitle,
   char *xaxislabel,char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG , double Ymax )
{
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  mnvPlotter.axis_title_size_x = 0.09;
  mnvPlotter.axis_title_size_y = 0.09;
  mnvPlotter.axis_label_size = 0.09;
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
  SetHist_Data(hist_Data, xaxislabel , yaxislabel);



  if(DoBinwidthNorm==true){
    histMC_TRUTH->Scale(1.0,"width");
    histMC_RECO->Scale(1.0,"width");
    hist_Data->Scale(1.0,"width");
  }

  if(MakeXaxisLOG==true){
    gPad->SetLogx();
  }

  //SetMaxforDraw(hist_Data, histMC_TRUTH, histMC_RECO);
  hist_Data->SetMaximum(Ymax);
  hist_Data->SetMarkerColor(kBlack);
  hist_Data->Draw("PEC");
  histMC_RECO->SetLineColor(kRed);
  histMC_RECO->Draw("Hist same");
  histMC_TRUTH->SetLineColor(kGreen);
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
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  auto Data_Clone_1 = (PlotUtils::MnvH1D*)hist_Data->Clone("Data_Clone_1");
  auto Data_Clone_2 = (PlotUtils::MnvH1D*)hist_Data->Clone("Data_Clone_2");
  Data_Clone_1->Divide(Data_Clone_1,histMC_TRUTH);
  Data_Clone_1->SetLineColor(kGreen);

  Data_Clone_2->Divide(Data_Clone_2,histMC_RECO);
  Data_Clone_2->SetLineColor(kRed);
  mnvPlotter.axis_title_offset_y = .4;
  Data_Clone_1->GetYaxis()->SetTitle("Ratio[#frac{Data}{MC}]");
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
void Draw_MCHist_fromTFile_SMEARING(TFile *inputFile_MCinput, char *histoName_MC_CV, char *histoName_MC_shifts, std::string pdf_label, char *histotitle, char *xaxislabel,char* yaxislabel )
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

  for(unsigned int i =0; i<N_bins+1;i++){
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

void Draw_TGraphs_fitParams(std::vector<GaussianResolutionFits> GaussianFits_values_Resolution_vector,  const char* pdf_label, char *histotitle, TCanvas *cE, MnvPlotter *mnvPlotter)
{

  std::string TotalTitle = string(histotitle);
  std::vector<double> X_axis_CutValue;
  std::vector<double> Y_axis_TotalN;
  std::vector<double> Y_axis_Sigma;
  std::vector<double> Y_axis_Mean;


  for(auto fit_params : GaussianFits_values_Resolution_vector){
    X_axis_CutValue.push_back(fit_params.CutValue);
    Y_axis_TotalN.push_back(fit_params.TotalN);
    Y_axis_Sigma.push_back(fit_params.Sigma);
    Y_axis_Mean.push_back(fit_params.Mean);
  }

    TGraphErrors  *TG_TotalN = MakeTGraph_from_Vectors(Y_axis_TotalN,  X_axis_CutValue);
    TGraphErrors  *TG_Sigma = MakeTGraph_from_VectorsNoErrors(Y_axis_Sigma,  X_axis_CutValue);
    TGraphErrors  *TG_Mean = MakeTGraph_from_VectorsNoErrors(Y_axis_Mean,  X_axis_CutValue);

// need pdf format

    DrawTGraph(TG_TotalN,"Fiducial Cut to Edge [mm]","NEvnets", "NEvents Pass Fiducial Cut", "Nevents",pdf_label, cE, mnvPlotter, false, false );

    DrawTGraph(TG_Sigma,"Fiducial Cut to Edge [mm]","Sigma Gaussian Fits", "Change in #sigma Gaussian Fits Fiducial Cut", "#sigma",pdf_label, cE, mnvPlotter, false, false );

    DrawTGraph(TG_Mean,"Fiducial Cut to Edge [mm]","Mean ", "Change in mean Gaussian Fits as Fiducial Cut", "mean",  pdf_label, cE, mnvPlotter, false, false );



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




void DrawFULLStat_CV_SystematicErr(ME_playlist_TFileMAP FullMCMap,     Pot_MapList FullMC_scalerMap,
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
    else if(STACKTYPE==kParticle){ sprintf(Stack_Name, "%s_Particle",histoName_MC);}
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

}

void DrawSTACKfromHistFilio_FULLStatsCOMBINED(ME_playlist_TFileMAP FullMCMap, Pot_MapList FullMC_POTMap,
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
    else if(STACKTYPE==kParticle){ sprintf(Stack_Name, "%s_Particle",histoName_MC);}
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
legend->SetNColumns(1);
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
  mnvPlotter.DrawDataStackedMC(FULL_Data_Hist, &CombinedFULL, 1.0, "TR", "Data", -1, -1,
  1001, xaxislabel.c_str(), ytitle, false);

  char total_title[1024];
  sprintf(total_title, "Stack %s [Combined FULL]", histotitle);

  mnvPlotter.AddHistoTitle(total_title, .04);
  mnvPlotter.WritePreliminary("TL", .035, 0, 0, false);
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
  mnvPlotter.WritePreliminary("TL", .035, 0, 0, false);
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
mnvPlotter.WritePreliminary("TL", .035, 0, 0, false);
mnvPlotter.MultiPrint(&cE, plotname, "pdf");

  cE.Closed();

}



/////////////////////////////////////////
void Draw_2D_Panel_MC_andData_frompointer(MnvH2D *hist_Data, MnvH2D *hist_MC, char *histotitle, std::string xaxislabel,
   std::string yaxislabel,const char *Zaxislabel , double max_x, double max_y, char *pdf_label, bool doBinwidth, bool MakeXaxisLOG,
    double x_projectionTxtsize, double y_projectionTxtsize ){
  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
  myPlotStyle();
  TH1::SetDefaultSumw2();
  gStyle->SetErrorX(0);
  gStyle->SetEndErrorSize(2);

  if(doBinwidth==true){
    hist_MC->Scale(1.0,"width");
    hist_Data->Scale(1.0,"width");
  }


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


  TLegend* leg=new TLegend(0.7, 0.08, 0.9, 0.32);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.025);
  leg->AddEntry(data_hist_Error, "MINERvA data", "lpe");
  leg->AddEntry(mc_hist, "MINERvA Tune", "l");

  bool doMultipliers=false;

  // I think if getscales is tru do Y projection if false do x projection
  std::vector<double> multipliers_y = GetScales(histAndOpts, true, true);

  GridCanvas* gc_y=plotYAxis1D(histAndOpts, xaxislabel, yaxislabel, doMultipliers ? &multipliers_y[0] : NULL, y_projectionTxtsize);
  gc_y->SetYLabel_Size(.025);
  gc_y->SetXLabel_Size(.03);
  gc_y->SetYLimits(0,max_y);
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
  std::vector<double> multipliers_x = GetScales(histAndOpts, false, true);
  //if(MakeXaxisLOG==true) gc_x->SetLogy(0);
  GridCanvas* gc_x=plotXAxis1D(histAndOpts, yaxislabel, xaxislabel, doMultipliers ? &multipliers_x[0] : NULL, x_projectionTxtsize);
  // Set the y range manually. Can also use gc3->Remax() to guess automatically
  gc_x->SetYLabel_Size(.025);
  gc_x->SetXLabel_Size(.03);
  gc_x->SetYLimits(0,max_x);
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
}//end of function

/////////////////////////////////////////////////////
void Draw_2D_Panel_MC_Only_frompointer(MnvH2D *hist, char *histotitle, char *legend_title, std::string xaxislabel,
   std::string yaxislabel,const char *Zaxislabel , double max_x, double max_y, char *pdf_label, bool doBinwidth, bool MakeXaxisLOG,
    double x_projectionTxtsize, double y_projectionTxtsize ){
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

  bool doMultipliers=false;

  // I think if getscales is tru do Y projection if false do x projection
  std::vector<double> multipliers_y = GetScales(histAndOpts_MC, true, true);

  GridCanvas* gc_y=plotYAxis1D(histAndOpts_MC, xaxislabel, yaxislabel, doMultipliers ? &multipliers_y[0] : NULL, y_projectionTxtsize);
  gc_y->SetYLabel_Size(.025);
  gc_y->SetXLabel_Size(.03);
  gc_y->SetYLimits(0,max_y);
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
  std::vector<double> multipliers_x = GetScales(histAndOpts_MC, false, true);
  //if(MakeXaxisLOG==true) gc_x->SetLogy(0);
  GridCanvas* gc_x=plotXAxis1D(histAndOpts_MC, yaxislabel, xaxislabel, doMultipliers ? &multipliers_x[0] : NULL, x_projectionTxtsize);
  // Set the y range manually. Can also use gc3->Remax() to guess automatically
  gc_x->SetYLabel_Size(.025);
  gc_x->SetXLabel_Size(.03);
  gc_x->SetYLimits(0,max_x);
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
}//end of function
/////////////////////////////////////////////////////
void Draw_2D_Panel_MC_Only_frompointer_XProjection(MnvH2D *hist, char *histotitle, char *legend_title, std::string xaxislabel, std::string yaxislabel,const char *Zaxislabel , double max_x, char *pdf_label, bool doBinwidth, bool MakeXaxisLOG){
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

  bool doMultipliers=false;
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
}//end of function

void Draw_2D_Panel_MC_Only_frompointer_YProjection(MnvH2D *hist, char *histotitle, char *legend_title, std::string xaxislabel, std::string yaxislabel,const char *Zaxislabel, double max_y, char *pdf_label, bool doBinwidth, bool MakeXaxisLOG){
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

  bool doMultipliers=false;

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
}//end of function
///////////////////////////////////////////////////
void DrawTGraph(TGraphErrors *g_TGraph, const char* xaxislabel,const char* yaxislabel, const char* Title,const char* legend_Title,
   const char* pdf, TCanvas *can, MnvPlotter *plot, bool MakeXaxisLOG, bool MakeYaxisLOG ){
  double x1, x2, y1, y2;
    TLegend *legend = new TLegend (0.80,0.73,0.95,.88);
    plot->DecodeLegendPosition(x1, y1, x2, y2, "R", 6.5, 6., .025);

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

   //TCanvas *optcan = new TCanvas("optcan");
   g_TGraph -> Draw("AP");

   legend -> SetTextSize(0.02);
   legend -> SetFillColor(0);
   legend -> AddEntry(g_TGraph, legend_Title, "LP");
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


void DrawTGraph(TGraphErrors *g_TGraph1, TGraphErrors *g_TGraph2, const char* xaxislabel,const char* yaxislabel,
   const char* Title,const char* legend_Title1,const char* legend_Title2,
   const char* pdf, TCanvas *can, MnvPlotter *plot, bool MakeXaxisLOG, bool MakeYaxisLOG ){
     double x1, x2, y1, y2;
     TLegend *legend = new TLegend (0.80,0.73,0.95,.88);
     plot->DecodeLegendPosition(x1, y1, x2, y2, "R", 6.5, 6., .025);


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
    g_TGraph1 -> GetXaxis() -> SetTitleSize(0.038);
    g_TGraph1 -> GetYaxis() -> SetTitleSize(0.038);

    g_TGraph1 -> SetLineColor(2);
    g_TGraph1 -> SetMarkerColor(2);

   //TCanvas *optcan = new TCanvas("optcan");
   g_TGraph1 -> Draw("AP");
   g_TGraph2 -> Draw("P");

   legend -> SetTextSize(0.02);
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

void DrawTGraph(TGraphErrors *g_TGraph1, TGraphErrors *g_TGraph2, TGraphErrors *g_TGraph3, const char* xaxislabel,const char* yaxislabel,
   const char* Title,const char* legend_Title1, const char* legend_Title2, const char* legend_Title3,
   const char* pdf, TCanvas *can, MnvPlotter *plot, bool MakeXaxisLOG, bool MakeYaxisLOG ){
     double x1, x2, y1, y2;
     TLegend *legend = new TLegend (0.80,0.73,0.95,.88);
     plot->DecodeLegendPosition(x1, y1, x2, y2, "R", 6.5, 6., .025);

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
    g_TGraph1 -> GetXaxis() -> SetTitleSize(0.038);
    g_TGraph1 -> GetYaxis() -> SetTitleSize(0.038);

    g_TGraph1 -> SetLineColor(2);
    g_TGraph1 -> SetMarkerColor(2);
    g_TGraph1->SetMarkerStyle(6);

    g_TGraph2 -> SetLineColor(4);
    g_TGraph2 -> SetMarkerColor(4);
    g_TGraph2->SetMarkerStyle(6);
    g_TGraph3 -> SetLineColor(3);
    g_TGraph3 -> SetMarkerColor(3);
    g_TGraph3->SetMarkerStyle(6);
   //TCanvas *optcan = new TCanvas("optcan");
   g_TGraph1 -> Draw("ALP");
   g_TGraph2 -> Draw("Same");
   g_TGraph3 -> Draw("Same");

   legend -> SetTextSize(0.02);
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
