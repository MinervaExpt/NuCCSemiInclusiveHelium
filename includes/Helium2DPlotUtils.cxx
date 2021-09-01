#include "Helium2DPlotUtils.h"

using namespace PlotUtils;
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
 //Particle_Tcolor;
//std::map<Particle_type,  TColor>  Particle_COLORMAP;
//Particle_COLORMAP.insert({kElectron, colorScheme[3]});
/*
vector<int> Particle_COLORMAP(9,1);
Particle_COLORMAP[kElectron]=TColor::GetColor("#FFD700");
Particle_COLORMAP[kPion] = TColor::GetColor("#32CD32");
Particle_COLORMAP[kKaon]=TColor::GetColor("#DA70D6");
Particle_COLORMAP[kProton]=TColor::GetColor("#87CEEB");
Particle_COLORMAP[kMuon]=TColor::GetColor("#D3D3D3");
Particle_COLORMAP[kGamma]=TColor::GetColor("#555555");
Particle_COLORMAP[kNeutrino]=TColor::GetColor("#32CD32");
Particle_COLORMAP[kParticle_OTHER]=TColor::GetColor("#800000");
Particle_COLORMAP[kParticle_N_A]=TColor::GetColor("#00FFFF");
*/
/*
std::vector<int> Material_COLORMAP(9,1);
Material_COLORMAP[kIron] = TColor::GetColor("#FFD700");
Material_COLORMAP[kHelium] = TColor::GetColor("#87CEEB");
Material_COLORMAP[kCarbon] = TColor::GetColor("#DA70D6");
Material_COLORMAP[kLead] = TColor::GetColor("#D3D3D3");
Material_COLORMAP[kAluminium]=TColor::GetColor("#555555");
Material_COLORMAP[kMaterial_OTHER] = TColor::GetColor("#FF0000");
*/

std::vector<double> GetScales_2d(std::vector<std::pair<TH2*, const char*> >histopts, bool pzProj){
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
    cout << scale << endl;
    if(scale < 0){scale = 0;}
    tmpvect.push_back(scale);
  }
    return tmpvect;
}


std::vector<double> Normlized_to_lowest_Mulitplers_2d(std::vector <double> multiply_vector){
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

std::vector<double> GetScales_2d(std::vector<std::pair<TH2*, const char*> >histopts, bool pzProj, bool  donormalized){

  auto double_vector = GetScales_2d(histopts ,pzProj);
  auto Normal_vector =  Normlized_to_lowest_Mulitplers_2d(double_vector);
  if(donormalized==true)
  {
    return Normal_vector;
  }
  else
  {
    return double_vector;
  }
}







void Draw2DCVAndError_FromTFile(TFile *inputFile_MCFULL, TFile *inputFile_MCEMPTY,  char *histoName_MC ,TFile *inputFile_DATAFULL,TFile *inputFile_DATAEMPTY,
                char *histoName_Data, Pot_MapStatusList POT_MC, Pot_MapStatusList POT_DATA,bool TrueifFullelseEmpty, char *histotitle,
                std::string xaxislabel,  std::string yaxislabel,std::string yaxislabel_units ,std::string pdf_label, bool DoBinwidthNorm, bool doSmallerrorgrounps, int Print_Error ,bool Debug)
      {
        PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
        double Ymax = 100.0;
        char pdf_label_char[pdf_label.length()+1];
        strcpy( pdf_label_char,pdf_label.c_str());
        char yaxislabel_units_char[yaxislabel_units.length()+1];
        strcpy( yaxislabel_units_char,yaxislabel_units.c_str());
        char yaxisUNITS[1024];
        sprintf(yaxisUNITS,  "Event Rate per %s", yaxislabel_units_char);

        myPlotStyle();
        TH1::SetDefaultSumw2();
        gStyle->SetErrorX(0);
        gStyle->SetEndErrorSize(2);
        double scale_to_FULLData[4] = {POT_DATA[kFULL]/POT_MC[kFULL],  POT_DATA[kFULL]/POT_MC[kEMPTY]  , 1.0 , POT_DATA[kFULL]/POT_DATA[kEMPTY]  };


        MnvH2D* mcFull;
        MnvH2D* mcEmpty;
        MnvH2D* dataFull;
        MnvH2D* dataEmpty;
        if(Debug==true){std::cout<< "trying to get Full MC "<<std::endl;}

        mcFull = (MnvH2D*)inputFile_MCFULL -> Get(histoName_MC);

        if(Debug==true){std::cout<< "trying to get Full Data "<<std::endl;}

        dataFull = (MnvH2D*)inputFile_DATAFULL -> Get(histoName_Data);
        if(Debug==true){std::cout<< "trying to get Empty MC "<<std::endl;}
        mcEmpty = (MnvH2D*)inputFile_MCEMPTY -> Get(histoName_MC);
        if(Debug==true){std::cout<< "trying to get Empty data "<<std::endl;}
        dataEmpty = (MnvH2D*)inputFile_DATAEMPTY -> Get(histoName_Data);


        if(Debug==true){std::cout<< "Pot Scaling "<<std::endl;}

        if(Debug==true){std::cout<< " Scaling MC full =  "<< scale_to_FULLData[0]<<std::endl;}

        mcFull->Scale(scale_to_FULLData[0]);
        if(Debug==true){std::cout<< " Scaling MC empty =  "<< scale_to_FULLData[1]<<std::endl;}

        mcEmpty->Scale(scale_to_FULLData[1]);
        if(Debug==true){std::cout<< " Scaling data empty =  "<< scale_to_FULLData[3]<<std::endl;}

        dataEmpty->Scale(scale_to_FULLData[3]);
        //1e-3

        if(Debug==true){std::cout<< "Normalized scales to 1 "<<std::endl;}
        mcFull->Scale(1,"width"); //
        mcEmpty->Scale(1,"width");

        dataFull->Scale(1,"width");//1e-3
        dataEmpty->Scale(1,"width");


        dataFull->SetMarkerStyle(kFullCircle);
        dataFull->SetMarkerSize(0.7);
        dataFull->SetLineColor(kBlack);
        dataFull->SetLineWidth(2);


        if(Debug==true){std::cout<< "Making CVs with stat errors "<<std::endl;}

        TH2* mc_1Full=new TH2D(mcFull->GetCVHistoWithStatError());
        TH2* dataStat_Full=new TH2D(dataFull->GetCVHistoWithStatError());
        TH2* data_1Full=new TH2D(dataFull->GetCVHistoWithError());

        TH2* mc_1Empty=new TH2D(mcEmpty->GetCVHistoWithStatError());
        TH2* dataStat_Empty=new TH2D(dataEmpty->GetCVHistoWithStatError());
        TH2* data_1Empty=new TH2D(dataEmpty->GetCVHistoWithError());


        //vector<int> mycolors = getColors(2);
        mc_1Full->SetLineColor(kRed);
        mc_1Full->SetLineWidth(2);
        mc_1Empty->SetLineColor(kRed);
        mc_1Empty->SetLineWidth(2);


        dataStat_Full->SetMarkerStyle(1);
        dataStat_Full->SetLineColor(kBlack);
        dataStat_Full->SetLineWidth(2);

        data_1Full->SetMarkerStyle(kFullCircle);
        data_1Full->SetMarkerSize(0.7);
        data_1Full->SetLineColor(kBlack);

        dataStat_Empty->SetMarkerStyle(1);
        dataStat_Empty->SetLineColor(kBlack);
        dataStat_Empty->SetLineWidth(2);

        data_1Empty->SetMarkerStyle(kFullCircle);
        data_1Empty->SetMarkerSize(0.7);
        data_1Empty->SetLineColor(kBlack);


        std::vector<std::pair<TH2*, const char*> > histAndOpts_FULL;

        histAndOpts_FULL.push_back(std::make_pair(mc_1Full,"hist"));
        histAndOpts_FULL.push_back(std::make_pair(dataStat_Full,"graph e"));
        histAndOpts_FULL.push_back(std::make_pair(data_1Full,"graph ep"));


        std::vector<std::pair<TH2*, const char*> > histAndOpts_Empty;

        histAndOpts_Empty.push_back(std::make_pair(mc_1Empty,"hist"));
        histAndOpts_Empty.push_back(std::make_pair(dataStat_Empty,"graph e"));
        histAndOpts_Empty.push_back(std::make_pair(data_1Empty,"graph ep"));

        ////////////////////////////////////////////
        //Full
        ///////////////////////////////////////////
        TLegend* leg=new TLegend(0.7, 0.08, 0.9, 0.32);
        leg->SetFillStyle(0);
        leg->SetBorderSize(0);
        leg->SetTextSize(0.025);
        leg->AddEntry(data_1Full, "MINERvA data", "lpe");
        leg->AddEntry(mc_1Full, "MINERvA Tune", "l");


        data_1Full->SetLineWidth(2);
        bool doMultipliers=true;

       std::vector<double> multipliers = GetScales_2d(histAndOpts_FULL, false);
        GridCanvas* gc=plotYAxis1D(histAndOpts_FULL, xaxislabel, yaxislabel, doMultipliers ? &multipliers[0] : NULL);
        gc->SetYLabel_Size(.025);
        gc->SetXLabel_Size(.03);
        gc->SetYLimits(0, Ymax);
        gc->SetYTitle(yaxisUNITS);
        gc->Modified();

        leg->Draw("SAME");
        char pdf1[1024];
        char total_title[1024];
        sprintf(total_title, " %s [Full][Yproj]", histotitle);
        mnvPlotter.AddHistoTitle(total_title, .035);
        //char pdf_label_char[pdf_label.length()+1];
        //strcpy( pdf_label_char,pdf_label.c_str());
        sprintf(pdf1,  "%s.pdf",pdf_label_char);
        gc->Print(pdf1);

       std::vector<double> multipliers2 = GetScales_2d(histAndOpts_FULL, true);
        GridCanvas* gc2=plotYAxis1D(histAndOpts_FULL, xaxislabel, yaxislabel, doMultipliers ? &multipliers2[0] : NULL);
        gc2->SetYLabel_Size(.025);
        gc2->SetXLabel_Size(.03);
        gc2->SetYLimits(0, Ymax);
        gc2->SetYTitle(yaxisUNITS);
        gc2->Modified();
        sprintf(total_title, " %s [Full][Yproj][Scales]", histotitle);
        mnvPlotter.AddHistoTitle(total_title, .035);
        //sprintf(pdf2,  "%s_Full2_Yproj.pdf",pdf_label_char);
        gc2->Print(pdf1);

       std::vector<double> multipliers3 = GetScales_2d( histAndOpts_FULL, false);
        GridCanvas* gc3=plotXAxis1D(histAndOpts_FULL, yaxislabel, xaxislabel, doMultipliers ? &multipliers3[0] : NULL);
        // Set the y range manually. Can also use gc3->Remax() to guess automatically
        gc3->SetYLabel_Size(.025);
        gc3->SetXLabel_Size(.03);
        gc3->SetYLimits(0, Ymax);
        gc3->SetYTitle(yaxisUNITS);
        gc3->Modified();
        leg->Draw("SAME");
        sprintf(total_title, " %s [Full][Xproj]", histotitle);
        mnvPlotter.AddHistoTitle(total_title, .035);
        gc3->Print(pdf1);
        /////////////////////////
       std::vector<double> multipliers4 = GetScales_2d( histAndOpts_FULL, true);
        GridCanvas* gc4=plotXAxis1D(histAndOpts_FULL,yaxislabel,xaxislabel, doMultipliers ? &multipliers4[0] : NULL);
        gc4->SetYLabel_Size(.025);
        gc4->SetXLabel_Size(.03);
        gc4->SetYLimits(0, Ymax);
        gc4->SetYTitle(yaxisUNITS);
        sprintf(total_title, " %s [Full][Xproj][Scales]", histotitle);
        mnvPlotter.AddHistoTitle(total_title, .035);
        gc4->Modified();
        //char pdf4[1024];
        //sprintf(pdf4,  "%s_Full2_Xproj.pdf",pdf_label_char);
        gc4->Print(pdf1);
        /////////////////////////////////
        ////// EMPTY
        //////////////////////////////
        TLegend* legEmpty=new TLegend(0.7, 0.08, 0.9, 0.32);
        legEmpty->SetFillStyle(0);
        legEmpty->SetBorderSize(0);
        legEmpty->SetTextSize(0.02);
        legEmpty->AddEntry(data_1Empty, "MINERvA data", "lpe");
        legEmpty->AddEntry(mc_1Empty, "MINERvA Tune V1", "l");


        data_1Empty->SetLineWidth(2);
       std::vector<double> multipliers5 = GetScales_2d(histAndOpts_Empty, false);
        GridCanvas* gc5=plotYAxis1D(histAndOpts_Empty, xaxislabel, yaxislabel, doMultipliers ? &multipliers5[0] : NULL);

        gc5->SetYLabel_Size(.025);
        gc5->SetXLabel_Size(.03);
        gc5->SetYLimits(0, Ymax);
        gc5->SetYTitle(yaxisUNITS);
        sprintf(total_title, " %s [Full][Yproj]", histotitle);
        mnvPlotter.AddHistoTitle(total_title, .035);
        gc5->Modified();
        legEmpty->Draw("SAME");


        //char total_title[1024];
        //sprintf(total_title, "%s%s%s", histotitle, emptyFull," (POT Norm) ");
        //mnvPlotter.AddHistoTitle("COOL", .04);
        //char pdf5[1024];
        //sprintf(pdf5,  "%s_Empty1_Yproj.pdf",pdf_label_char);
        gc5->Print(pdf1);
       std::vector<double> multipliers6 = GetScales_2d( histAndOpts_Empty, true);
        GridCanvas* gc6=plotYAxis1D(histAndOpts_Empty, xaxislabel, yaxislabel, doMultipliers ? &multipliers6[0] : NULL);
        gc6->SetYLabel_Size(.025);
        gc6->SetXLabel_Size(.03);
        gc6->SetYLimits(0, Ymax);
        gc6->SetYTitle(yaxisUNITS);
        gc6->Modified();
        sprintf(total_title, " %s [Empty][Yproj][Scales]", histotitle);
        mnvPlotter.AddHistoTitle(total_title, .035);
        gc6->Print(pdf1);

       std::vector<double> multipliers7 = GetScales_2d(histAndOpts_Empty, false);
        GridCanvas* gc7=plotXAxis1D(histAndOpts_Empty, yaxislabel, xaxislabel, doMultipliers ? &multipliers7[0] : NULL);
        // Set the y range manually. Can also use gc3->Remax() to guess automatically
        gc7->SetYLabel_Size(.025);
        gc7->SetXLabel_Size(.03);
        gc7->SetYLimits(0, Ymax);
        gc7->SetYTitle(yaxisUNITS);
        sprintf(total_title, " %s [Empty][Xproj]", histotitle);
        mnvPlotter.AddHistoTitle(total_title, .035);
        gc7->Modified();
        legEmpty->Draw("SAME");
        gc7->Print(pdf1);

       std::vector<double> multipliers8 = GetScales_2d( histAndOpts_Empty, true);
        GridCanvas* gc8=plotXAxis1D(histAndOpts_Empty,yaxislabel,xaxislabel, doMultipliers ? &multipliers8[0] : NULL);
        gc8->SetYLabel_Size(.025);
        gc8->SetXLabel_Size(.03);
        gc8->SetYLimits(0, Ymax);
        gc8->SetYTitle(yaxisUNITS);
        gc8->Modified();
        sprintf(total_title, " %s [Empty][Xproj][Scales]", histotitle);
        mnvPlotter.AddHistoTitle(total_title, .035);
        gc8->Print(pdf1);

        /////////////////////////////////
        //Full - Empty
        ////////////////////////////////

        dataFull->Add(dataEmpty,-1);
        mcFull->Add(mcEmpty,-1);

        TH2* mc_1Full_Empty =new TH2D(mcFull->GetCVHistoWithStatError());
        TH2* dataStat_Full_Empty =new TH2D(dataFull->GetCVHistoWithStatError());
        TH2* data_1Full_Empty =new TH2D(dataFull->GetCVHistoWithError());

        mc_1Full_Empty->SetLineColor(kRed);
        mc_1Full_Empty->SetLineWidth(2);

        dataStat_Full_Empty->SetMarkerStyle(1);
        dataStat_Full_Empty->SetLineColor(kBlack);
        dataStat_Full_Empty->SetLineWidth(2);

        data_1Full_Empty->SetMarkerStyle(kFullCircle);
        data_1Full_Empty->SetMarkerSize(0.7);
        data_1Full_Empty->SetLineColor(kBlack);

        std::vector<std::pair<TH2*, const char*> > histAndOpts_FULL_EMPTY;

        histAndOpts_FULL_EMPTY.push_back(std::make_pair(mc_1Full_Empty,"hist"));
        histAndOpts_FULL_EMPTY.push_back(std::make_pair(dataStat_Full_Empty,"graph e"));
        histAndOpts_FULL_EMPTY.push_back(std::make_pair(data_1Full_Empty,"graph ep"));


        TLegend* leg_full_empty=new TLegend(0.17, 0.7, 0.31, 0.9);
        leg_full_empty->SetFillStyle(0);
        leg_full_empty->SetBorderSize(0);
        leg_full_empty->SetTextSize(0.025);
        leg_full_empty->AddEntry(data_1Full_Empty, "MINERvA data", "lpe");
        leg_full_empty->AddEntry(mc_1Full_Empty, "MINERvA Tune", "l");

        data_1Full_Empty->SetLineWidth(2);

       std::vector<double> multipliers_full_empty_1 = GetScales_2d( histAndOpts_FULL_EMPTY, false);
        GridCanvas* gc_full_empty_1=plotYAxis1D(histAndOpts_FULL_EMPTY, xaxislabel, yaxislabel, doMultipliers ? &multipliers_full_empty_1[0] : NULL);

        gc_full_empty_1->SetYLimits(0, Ymax);
        gc_full_empty_1->SetYTitle(yaxisUNITS);
        gc_full_empty_1->Modified();
        leg_full_empty->Draw("SAME");
        sprintf(total_title, " %s [F-E][Yproj]", histotitle);
        mnvPlotter.AddHistoTitle(total_title, .035);

        gc_full_empty_1->Print(pdf1);

       std::vector<double> multipliers_full_empty_2 = GetScales_2d( histAndOpts_FULL_EMPTY, true);
        GridCanvas* gc_full_empty_2=plotYAxis1D(histAndOpts_FULL_EMPTY, xaxislabel, yaxislabel, doMultipliers ? &multipliers_full_empty_2[0] : NULL);
        gc_full_empty_2->SetYLabel_Size(.025);
        gc_full_empty_2->SetXLabel_Size(.03);
        gc_full_empty_2->SetYLimits(0, Ymax);
        gc_full_empty_2->SetYTitle(yaxisUNITS);
        gc_full_empty_2->Modified();
        sprintf(total_title, " %s [F-E][Yproj][Scales]", histotitle);
        mnvPlotter.AddHistoTitle(total_title, .035);

        leg_full_empty->Draw("SAME");
        gc_full_empty_1->Print(pdf1);

       std::vector<double> multipliers_full_empty_3 = GetScales_2d( histAndOpts_FULL_EMPTY, false);
        GridCanvas* gc_full_empty_3=plotXAxis1D(histAndOpts_FULL_EMPTY, yaxislabel, xaxislabel, doMultipliers ? &multipliers_full_empty_3[0] : NULL);
        gc_full_empty_3->SetYLabel_Size(.025);
        gc_full_empty_3->SetXLabel_Size(.03);
        gc_full_empty_3->SetYLimits(0, Ymax);
        gc_full_empty_3->SetYTitle(yaxisUNITS);
        gc_full_empty_3->Modified();
        sprintf(total_title, " %s [F-E][Xproj]", histotitle);
        mnvPlotter.AddHistoTitle(total_title, .035);
        leg_full_empty->Draw("SAME");
        gc_full_empty_3->Print(pdf1);

       std::vector<double> multipliers_full_empty_4= GetScales_2d(histAndOpts_FULL_EMPTY, true);
        GridCanvas* gc_full_empty_4=plotXAxis1D(histAndOpts_FULL_EMPTY, yaxislabel, xaxislabel, doMultipliers ? &multipliers_full_empty_4[0] : NULL);
        gc_full_empty_4->SetYLabel_Size(.025);
        gc_full_empty_4->SetXLabel_Size(.03);
        gc_full_empty_4->SetYLimits(0, Ymax);
        gc_full_empty_4->SetYTitle(yaxisUNITS);
        gc_full_empty_4->Modified();
        sprintf(total_title, " %s [F-E][Xproj][Scales]", histotitle);
        mnvPlotter.AddHistoTitle(total_title, .035);
        leg_full_empty->Draw("SAME");
        gc_full_empty_4->Print(pdf1);

      }//end of function



std::vector<std::pair<TH2*, const char*> > Make_pannelhis_vector(MnvH2D* data,
   const TObjArray *mcHists, StackType STACKTYPE, TLegend* leg, int Plottype)
{

  std::vector<std::pair<TH2*, const char*> > histAndOpts;
  TH2* dataStat = new TH2D(data->GetCVHistoWithStatError());
  TH2* data_1 = new TH2D(data->GetCVHistoWithError());


  dataStat->SetMarkerStyle(1);
  dataStat->SetLineColor(kBlack);
  dataStat->SetLineWidth(2);

  data_1->SetMarkerStyle(kFullCircle);
  data_1->SetMarkerSize(0.7);
  data_1->SetLineColor(kBlack);



  unsigned int nHists = mcHists->GetEntries();

  MnvH2D *mc_1 = (MnvH2D*)mcHists->At(0);

  for ( unsigned int i = 1; i != nHists; ++i )
  {
    MnvH2D *mc_forloop = (MnvH2D*)mcHists->At(i);
    mc_1->Add(mc_forloop, 1.0);
  }

  //mc_1->SetLineColor(0);
  //mc_1->SetLineWidth(2);
  //mc_1->SetFillColor(0);
  //leg->AddEntry(mc_1, "MINERvA Tune", "l");
  //histAndOpts.push_back(std::make_pair(mc_1, "histl"));

  if(STACKTYPE==kMaterial){

    //auto Vector_material_type = getMaterial_typeVector();
    //Material_color_map ColorMap = getColorMap_Material();
    std::cout<< "the number of Hist in StackType kmaterial = "<< nHists<<std::endl;
    for ( unsigned int i = 0; i != nHists; ++i )
    {
      MnvH2D *mnv = (MnvH2D*)mcHists->At(i);
      // Let's just make double sure you didn't pass an array of MnvH2D.
      // (Because if you did you'll get an indecipherable seg fault)
      if (std::string(typeid(*mnv).name()).find(std::string("MnvH2D"))
      == std::string::npos) {
        throw std::runtime_error("The TObjArray you passed to DrawDataStackedMC does not contain all MnvH1Ds!");
      }
      //char *hist_name[*(mnv->GetTitle()).length()+1];
      const char *hist_name = mnv->GetTitle();
      auto material_type = getMaterial_fromstring(hist_name);
      std::cout<<"checking material type  = " << GetNameMaterial(material_type)<<std::endl;
      int color = GetColorNMaterial(material_type);
      TH2* mc_hist = new TH2D(mnv->GetCVHistoWithStatError());
      mc_hist->SetFillColor(color);
      mc_hist->SetLineColor(color);
      mc_hist->SetLineWidth(2);
      std::cout<< "inside Stack function"<<std::endl;
      std::cout<< "name of stack =  "<<hist_name << " Color Number = "<< color<<std::endl;
      leg->AddEntry(mc_hist, hist_name , "l");
      histAndOpts.push_back(std::make_pair(mc_hist,"hist"));

    }

  }


  else if(STACKTYPE==kInteraction){
    //Interaction_color_map ColorMap = getColorMap_Interaction();
    //auto Vector_Interaction_type = getInteraction_typeVector();

    for ( unsigned int i = 0; i != nHists; ++i )
    {
      MnvH2D *mnv = (MnvH2D*)mcHists->At(i);
      // Let's just make double sure you didn't pass an array of MnvH2D.
      // (Because if you did you'll get an indecipherable seg fault)
      if (std::string(typeid(*mnv).name()).find(std::string("MnvH2D"))
      == std::string::npos) {
        throw std::runtime_error("The TObjArray you passed to DrawDataStackedMC does not contain all MnvH1Ds!");
      }
      const char *hist_name = mnv->GetTitle();
      auto Interaction_type = getInteraction_fromstring(hist_name);
      int color = GetColorNInteraction(Interaction_type);
      TH2* mc_hist = new TH2D(mnv->GetCVHistoWithStatError());
      mc_hist->SetFillColor(color);
      mc_hist->SetLineColor(color);
      mc_hist->SetLineWidth(2);
      leg->AddEntry(mc_hist, hist_name , "l");
      histAndOpts.push_back(std::make_pair(mc_hist,"hist" ));
    }

  }

  else if(STACKTYPE==kParticle){
    //Particle_color_map ColorMap = getColorMap_Particle();
    auto Vector_particle = getParticle_typeVector();

    for ( unsigned int i = 0; i != nHists; ++i )
    {
      MnvH2D *mnv = (MnvH2D*)mcHists->At(i);
      // Let's just make double sure you didn't pass an array of MnvH2D.
      // (Because if you did you'll get an indecipherable seg fault)
      if (std::string(typeid(*mnv).name()).find(std::string("MnvH2D"))
      == std::string::npos) {
        throw std::runtime_error("The TObjArray you passed to DrawDataStackedMC does not contain all MnvH1Ds!");
      }

      const char *hist_name = mnv->GetTitle();
      auto Particle_type = getParticle_fromstring(hist_name);
      int color = GetColorNParticle(Particle_type);
      TH2* mc_hist = new TH2D(mnv->GetCVHistoWithStatError());
      mc_hist->SetFillColor(color);
      mc_hist->SetLineColor(color);
      mc_hist->SetLineWidth(2);
      leg->AddEntry(mc_hist, hist_name , "l");
      histAndOpts.push_back(std::make_pair(mc_hist, "hist"));
    }
}


leg->AddEntry(data_1, "MINERvA data", "lpe");
histAndOpts.push_back(std::make_pair(dataStat,"graph e"));
histAndOpts.push_back(std::make_pair(data_1,"graph ep"));



 return histAndOpts;


}//end of function

void DrawSTACKfromHistFilio_FromTFile2D(TFile *inputFile_MCFULL, TFile *inputFile_MCEMPTY,  char *histoName_MC ,  TFile *inputFile_DATAFULL,
  TFile *inputFile_DATAEMPTY, char *histoName_Data, Pot_MapStatusList POT_MC, Pot_MapStatusList POT_DATA, bool TrueifFullelseEmpty, char *histotitle,
  std::string xaxislabel, std::string yaxislabel, const char* yaxisUNITS,std::string pdf_label, bool DoBinwidthNorm, bool doSmallerrorgrounps,  StackType STACKTYPE, bool Debug )
  {    //helium_Status kEMPTY, kFULL;
    //PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCompactStyle);
    // PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCNuPionIncStyle);

    //PlotUtils::MnvPlotter mnvPlotter();

    double scale_to_FULLData[4] = {POT_DATA[kFULL]/POT_MC[kFULL],  POT_DATA[kFULL]/POT_MC[kEMPTY]  , 1.0 , POT_DATA[kFULL]/POT_DATA[kEMPTY]  };

    TCanvas cE ("c1","c1");
    std::cout<<"trying MC HisName = "<< histoName_MC<<std::endl;
    std::cout<<"trying data HisName = "<< histoName_Data<<std::endl;

    char Stack_Name[1024];
    char pdf_label_char[pdf_label.length()+1];
    strcpy(pdf_label_char, pdf_label.c_str());
    bool doMultipliers = true;


    if(STACKTYPE==kMaterial){sprintf(Stack_Name, "%s_Material",histoName_MC);}
    else if(STACKTYPE==kInteraction){ sprintf(Stack_Name, "%s_Interaction",histoName_MC);}
    else if(STACKTYPE==kParticle){ sprintf(Stack_Name, "%s_Particle",histoName_MC);}
    else{std::cout<<"Error unknown stack type: Ploting Failed"<<std::endl; return;}

    if(Debug == true){std::cout << "Getting Hist Using Name: "<< Stack_Name <<std::endl;}

    PlotUtils::HistFolio<PlotUtils::MnvH2D> Full_MC_Stack(
      PlotUtils::LoadHistFolioFromFile<PlotUtils::MnvH2D>(
        *inputFile_MCFULL, std::string(Stack_Name)),
        "Full_MC_Stack");

    if(Debug == true){std::cout << "Initialize Got FUll MC for Stacks   "<< Stack_Name<<std::endl;}


    PlotUtils::HistFolio<PlotUtils::MnvH2D> Empty_MC_Stack(
      PlotUtils::LoadHistFolioFromFile<PlotUtils::MnvH2D>(
        *inputFile_MCEMPTY, std::string(Stack_Name)),
        "Empty_MC_Stack");

    if(Debug == true){std::cout << "Initialize Got Empty MC for Stacks   "<< Stack_Name<<std::endl;}

    PlotUtils::HistFolio<PlotUtils::MnvH2D> Full_MC_Stack_FORSUBTRACTION(
      PlotUtils::LoadHistFolioFromFile<PlotUtils::MnvH2D>(
        *inputFile_MCFULL, std::string(Stack_Name)),
        "Full_MC_Stack_FORSUBTRACTION");

    if(Debug == true){std::cout << "Initialize Got FUll MC for Stacks   "<< Stack_Name<<std::endl;}

    PlotUtils::HistFolio<PlotUtils::MnvH2D> Empty_MC_Stack_FORSUBTRACTION(
      PlotUtils::LoadHistFolioFromFile<PlotUtils::MnvH2D>(
        *inputFile_MCEMPTY, std::string(Stack_Name)),
        "Empty_MC_Stack_FORSUBTRACTION");

    if(Debug == true){std::cout << "Initialize Got Emtpy MC for Stacks   "<< Stack_Name<<std::endl;}

    if(STACKTYPE==kParticle)
    {// Normal method doesn't have enought colors for particle type

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
  ////////////////////////////////////////////////////////////////
  //// FUll Bin Width
  ////////////////////////////////////////////////////////////////
  if(Debug == true){std::cout << "Passed Making Arrary of Full - Empty Hist "<< Stack_Name<<std::endl;}
  ////////////////////////////////////////////////////////////////
  //// Time to PLot
  ////////////////////////////////////////////////////////////////
  MnvH2D *hist_Full_data = NULL;
  MnvH2D *hist_Empty_data = NULL;
  MnvH2D *hist_Empty2_data = NULL;
  MnvH2D *hist_Full_Empty_data = NULL;

  if(Debug == true){std::cout << "Starting Full, Empty, and Full - Empty plotting loop"<< Stack_Name<<std::endl;}


  for (int fullOrEmpty = 0; fullOrEmpty < 3; fullOrEmpty ++) {

    if(fullOrEmpty==0){
      int j=0;

      for(auto cat : Full_MC_Stack_array){

        if(Debug == true){std::cout << "In Loop On element For Full Stacks "<< j <<std::endl;}

        if(DoBinwidthNorm==true){
          ((PlotUtils::MnvH2D*)Full_MC_Stack_array.At(j))->Scale(1.0,"width");
        }

        ((PlotUtils::MnvH2D*)Full_MC_Stack_array.At(j))->Scale(scale_to_FULLData[0]);
        j++;
      }

      if(Debug == true){std::cout << "inside plotting Loop on element:"<< fullOrEmpty<<std::endl;}

      hist_Full_data = (MnvH2D*)inputFile_DATAFULL -> Get(histoName_Data);
      if(Debug == true){std::cout << "Initialize Got Full Data for FULL Stacks   "<< Stack_Name<<std::endl;}

      if(DoBinwidthNorm==true)
      {
        hist_Full_data->Scale(1.0,"width");
      }

    }

    else if (fullOrEmpty==1)
    {
      int k=0;
      for(auto cat : Empty_MC_Stack_array){

        if(Debug == true){std::cout << "In Loop On element For Empty Stacks "<< k <<std::endl;}

        if(DoBinwidthNorm==true){
          ((PlotUtils::MnvH2D*)Empty_MC_Stack_array.At(k))->Scale(1.0,"width");
        }

        ((PlotUtils::MnvH2D*)Empty_MC_Stack_array.At(k))->Scale(scale_to_FULLData[1]);
        k++;
      }

      hist_Empty_data = (MnvH2D*)inputFile_DATAEMPTY -> Get(histoName_Data);
      if(Debug == true){std::cout << "Initialize Got Empty Data for EMTPY Stacks   "<< Stack_Name<<std::endl;}

      if(DoBinwidthNorm==true){

        hist_Empty_data->Scale(1.0,"width");
      }
      hist_Empty_data->Scale(scale_to_FULLData[3]);
    }


    else if (fullOrEmpty==2)
    {

      int i=0;

      for(auto cat : FULL_EMPTY_MC_Stack_array) {

        if(Debug == true){std::cout << "In Loop On element For Full - Empty Stacks "<< i <<std::endl;}

        if(DoBinwidthNorm==true){
          ((PlotUtils::MnvH2D*)EMPTY_forsubtract_MC_Stack_array.At(i))->Scale(1.0,"width");
          ((PlotUtils::MnvH2D*)FULL_EMPTY_MC_Stack_array.At(i))->Scale(1.0,"width");

        }

        ((PlotUtils::MnvH2D*)FULL_EMPTY_MC_Stack_array.At(i))->Scale(scale_to_FULLData[0]);
        ((PlotUtils::MnvH2D*)EMPTY_forsubtract_MC_Stack_array.At(i))->Scale(scale_to_FULLData[1]);

        ((PlotUtils::MnvH2D*)FULL_EMPTY_MC_Stack_array.At(i))->Add(((PlotUtils::MnvH2D*)EMPTY_forsubtract_MC_Stack_array.At(i)), -1);
        i++;

      }

      hist_Full_Empty_data = (MnvH2D*)inputFile_DATAFULL -> Get(histoName_Data);
      hist_Empty2_data = (MnvH2D*)inputFile_DATAEMPTY -> Get(histoName_Data);
      if(Debug == true){std::cout << "Initialize Got Empty + FULL Data for Full - EMTPY Stacks   "<< Stack_Name<<std::endl;}

      if(DoBinwidthNorm==true)
      {
        hist_Full_Empty_data->Scale(1.0,"width");
        hist_Empty2_data->Scale(1.0,"width");
      }

      hist_Empty2_data->Scale(scale_to_FULLData[3]);  // Empty Data
      hist_Full_Empty_data->Add(hist_Empty2_data, -1); // data doesn't need to be scaled
    }
    if(Debug == true){std::cout << "Done Scaling and Bin Width Normalization on element: "<< fullOrEmpty<<std::endl;}
  }

  TLegend* leg_full=new TLegend(0.7, 0.08, 0.9, 0.32);
  leg_full->SetFillStyle(0);
  leg_full->SetBorderSize(0);
  leg_full->SetTextSize(0.03);
  TLegend* leg_empty=new TLegend(0.7, 0.08, 0.9, 0.32);
  leg_empty->SetFillStyle(0);
  leg_empty->SetBorderSize(0);
  leg_empty->SetTextSize(0.03);
  TLegend* leg_full_empty=new TLegend(0.7, 0.08, 0.9, 0.32);
  leg_full_empty->SetFillStyle(0);
  leg_full_empty->SetBorderSize(0);
  leg_full_empty->SetTextSize(0.03);
  ////////////////////////////////////////////////////////
  ////
  ////////////////////////////////////////////////////////
  std::vector<std::pair<TH2*, const char*> >  histAndOpts_Full;
  std::vector<std::pair<TH2*, const char*> >  histAndOpts_Empty;
  std::vector<std::pair<TH2*, const char*> >  histAndOpts_Full_Empty;
  char type[1024];

  if(STACKTYPE==kMaterial){
    histAndOpts_Full = Make_pannelhis_vector(hist_Full_data, &Full_MC_Stack_array, kMaterial, leg_full);
    histAndOpts_Empty = Make_pannelhis_vector(hist_Empty_data, &Empty_MC_Stack_array, kMaterial, leg_empty);
    histAndOpts_Full_Empty = Make_pannelhis_vector(hist_Full_Empty_data, &FULL_EMPTY_MC_Stack_array, kMaterial, leg_full_empty);

    sprintf(type,  "%s","material");
     }
  else if(STACKTYPE==kInteraction){
    histAndOpts_Full = Make_pannelhis_vector(hist_Full_data, &Full_MC_Stack_array, kInteraction, leg_full);
    histAndOpts_Empty = Make_pannelhis_vector(hist_Empty_data, &Empty_MC_Stack_array, kInteraction, leg_empty);
    histAndOpts_Full_Empty = Make_pannelhis_vector(hist_Full_Empty_data, &FULL_EMPTY_MC_Stack_array, kInteraction, leg_full_empty);

    sprintf(type,  "%s","interaction");
  }
  else if(STACKTYPE==kParticle){
    histAndOpts_Full = Make_pannelhis_vector(hist_Full_data, &Full_MC_Stack_array, kParticle, leg_full);
    histAndOpts_Empty = Make_pannelhis_vector(hist_Empty_data, &Empty_MC_Stack_array, kParticle, leg_empty);
    histAndOpts_Full_Empty = Make_pannelhis_vector(hist_Full_Empty_data, &FULL_EMPTY_MC_Stack_array, kParticle, leg_full_empty);

    sprintf(type,  "%s","Particle");
  }


  /////////////////////////
  ///Full
  ////////////////////////

 std::vector<double> multipliers_1 = GetScales_2d(histAndOpts_Full, false);
  GridCanvas* gc_full_1=plotYAxis1D(histAndOpts_Full, xaxislabel, yaxislabel, doMultipliers ? &multipliers_1[0] : NULL);

  gc_full_1->SetYLimits(0, 300);
  gc_full_1->SetYTitle(yaxisUNITS);
  gc_full_1->Modified();
  leg_full->Draw("SAME");

  char pdf_full_1[1024];
  sprintf(pdf_full_1,  "%s_%s_STACKS_Full_Yproj.pdf",pdf_label_char, type);
  gc_full_1->Print(pdf_full_1);


 std::vector<double> multipliers_2 = GetScales_2d(histAndOpts_Full, false);
  GridCanvas* gc_full_2 = plotXAxis1D(histAndOpts_Full, yaxislabel, xaxislabel, doMultipliers ? &multipliers_2[0] : NULL);

  gc_full_2->SetYLimits(0, 300);
  gc_full_2->SetYTitle(yaxisUNITS);
  gc_full_2->Modified();
  //leg_full->Draw("SAME");

  char pdf_full_2[1024];
  sprintf(pdf_full_2,  "%s_%s_STACKS_Full_Xproj.pdf", pdf_label_char, type);
  gc_full_2->Print(pdf_full_2);
/////////////////////////
///Empty
////////////////////////

std::vector<double> multipliers_1empty = GetScales_2d(histAndOpts_Empty, false);
GridCanvas* gc_empty_1=plotYAxis1D(histAndOpts_Empty, xaxislabel, yaxislabel, doMultipliers ? &multipliers_1empty[0] : NULL);

gc_empty_1->SetYLimits(0, 300);
gc_empty_1->SetYTitle(yaxisUNITS);
gc_empty_1->Modified();

leg_empty->Draw("SAME");

char pdf_empty_1[1024];
sprintf(pdf_empty_1,  "%s_%s_STACKS_Empty_Yproj.pdf",pdf_label_char,type);
gc_empty_1->Print(pdf_empty_1);


std::vector<double> multipliers_2empty = GetScales_2d(histAndOpts_Empty, false);
GridCanvas* gc_empty_2 = plotXAxis1D(histAndOpts_Empty, yaxislabel, xaxislabel, doMultipliers ? &multipliers_2empty[0] : NULL);

gc_empty_2->SetYLimits(0, 300);
gc_empty_2->SetYTitle(yaxisUNITS);
gc_empty_2->Modified();
//leg_full->Draw("SAME");

char pdf_empty_2[1024];
sprintf(pdf_empty_2,  "%s_%s_STACKS_Empty_Xproj.pdf", pdf_label_char, type);
gc_empty_2->Print(pdf_empty_2);

/////////////////////////
///Full - Empty
////////////////////////

std::vector<double> multipliers_1full_empty = GetScales_2d(histAndOpts_Full_Empty, false);
GridCanvas* gc_full_empty_1=plotYAxis1D(histAndOpts_Full_Empty, xaxislabel, yaxislabel, doMultipliers ? &multipliers_1full_empty[0] : NULL);

gc_full_empty_1->SetYLimits(0, 300);
gc_full_empty_1->SetYTitle(yaxisUNITS);
gc_full_empty_1->Modified();

leg_full_empty->Draw("SAME");

char pdf_full_empty_1[1024];
sprintf(pdf_full_empty_1,  "%s_%s_STACKS_Full_Empty_Yproj.pdf",pdf_label_char,type);
gc_full_empty_1->Print(pdf_full_empty_1);


std::vector<double> multipliers_2full_empty = GetScales_2d(histAndOpts_Full_Empty, false);
GridCanvas* gc_full_empty_2 = plotXAxis1D(histAndOpts_Full_Empty, yaxislabel, xaxislabel, doMultipliers ? &multipliers_2full_empty[0] : NULL);

gc_full_empty_2->SetYLimits(0, 300);
gc_full_empty_2->SetYTitle(yaxisUNITS);
gc_full_empty_2->Modified();
//leg_full->Draw("SAME");

char pdf_full_empty_2[1024];
sprintf(pdf_full_empty_2,  "%s_%s_STACKS_Full_Empty_Xproj.pdf", pdf_label_char, type);
gc_full_empty_2->Print(pdf_full_empty_2);




}// END of Function


void Draw2D_Migration_FromTFile(TFile *inputFile_MCFULL, TFile *inputFile_MCEMPTY,  char *histoName_MC_Mig,char *histoName_MC_RECO, char *histoName_MC_TRUTH,
   Pot_MapStatusList POT_MC, char *histotitle,char *Fullplaylist_name, char *Emptyplaylist_name, std::string xaxislabel, std::string yaxislabel,
   std::string yaxislabel_units, std::string pdf_label, bool DoBinwidthNorm ,bool Debug){

     double SCALER_MC_Empty_FUll = POT_MC[kFULL] / POT_MC[kEMPTY];
     PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
     TCanvas cE("c1","c1");

     if(Debug==true){
       std::cout<<"trying MC HisName Mig = "<< histoName_MC_Mig<<std::endl;
       std::cout<<"trying MC HisName RECO = "<< histoName_MC_RECO<<std::endl;
       std::cout<<"trying MC HisName TRUTH = "<< histoName_MC_TRUTH<<std::endl;
     }


     char pdf_label_char[pdf_label.length()+1];
     strcpy(pdf_label_char, pdf_label.c_str());

     char yaxislabel_char[yaxislabel.length()+1];
     strcpy(yaxislabel_char, yaxislabel.c_str());

     char xaxislabel_char[xaxislabel.length()+1];
     strcpy(xaxislabel_char, xaxislabel.c_str());


     MnvH2D *hist_Mig_Full = (MnvH2D*)inputFile_MCFULL -> Get(histoName_MC_Mig);
     TH2D *hist_Reco_Full = (TH2D*)inputFile_MCFULL -> Get(histoName_MC_RECO);
     TH2D *hist_Truth_Full = (TH2D*)inputFile_MCFULL -> Get(histoName_MC_TRUTH);

     MnvH2D *hist_Mig_Empty = (MnvH2D*)inputFile_MCEMPTY -> Get(histoName_MC_Mig);
     TH2D *hist_Reco_Empty = (TH2D*)inputFile_MCEMPTY -> Get(histoName_MC_RECO);
     TH2D *hist_Truth_Empty = (TH2D*)inputFile_MCEMPTY -> Get(histoName_MC_TRUTH);

     hist_Mig_Empty->Scale(SCALER_MC_Empty_FUll);
     hist_Reco_Empty->Scale(SCALER_MC_Empty_FUll);
     hist_Truth_Empty->Scale(SCALER_MC_Empty_FUll);


     char title_full[1024];
     sprintf(title_full,  "2DMigration %s (Full)[%s]", histotitle, Fullplaylist_name);
     string FullTitle = string(title_full);

     hist_Mig_Full->Draw("COLZ");
     hist_Mig_Full->GetXaxis()->CenterTitle();
     hist_Mig_Full->GetYaxis()->CenterTitle();
     hist_Mig_Full->GetXaxis()->SetTitle(xaxislabel_char);
     hist_Mig_Full->GetYaxis()->SetTitle(yaxislabel_char);
     hist_Mig_Full->GetXaxis()->SetTitleSize(0.038);
     hist_Mig_Full->GetYaxis()->SetTitleSize(0.038);

     mnvPlotter.AddHistoTitle(FullTitle.c_str(), .04);
     mnvPlotter.WritePreliminary("TL", .035, 0, 0, false);

     gPad->Update();
     cE.Modified();
     char pdf_start[1024];
     sprintf(pdf_start,  "%s_MIGRATION.pdf(", pdf_label_char);
     cE.Print(pdf_start);
     cE.Closed();

     char pdf_middle[1024];
     sprintf(pdf_middle,  "%s_MIGRATION.pdf", pdf_label_char);

     char title_other[1024];
     sprintf(title_other,  "2DMig[RECO] %s [Full][%s]", histotitle, Fullplaylist_name);
     DrawMagration_heatMap(hist_Reco_Full,xaxislabel_char,yaxislabel_char,title_other,pdf_middle,&cE,&mnvPlotter);

     TH2D *h_Reco_Full_rowNorm = (TH2D*)hist_Reco_Full->Clone("h_Reco_Full_rowNorm");
     rowNormalize(*h_Reco_Full_rowNorm );
     sprintf(title_other,  "2DMig[rowNorm][RECO] %s [Full][%s]", histotitle, Fullplaylist_name);
     DrawMagration_heatMap(h_Reco_Full_rowNorm ,xaxislabel_char,yaxislabel_char,title_other,pdf_middle,&cE,&mnvPlotter);

     TH2D *h_Reco_Full_colNorm = (TH2D*)hist_Reco_Full->Clone("h_Reco_Full_colNorm");
     colNormalize(*h_Reco_Full_colNorm);
     sprintf(title_other,  "2DMig[colNorm][RECO] %s [Full][%s]", histotitle, Fullplaylist_name);
     DrawMagration_heatMap(h_Reco_Full_colNorm,xaxislabel_char,yaxislabel_char,title_other,pdf_middle,&cE,&mnvPlotter);


     sprintf(title_other,  "2DMig[TRUTH] %s [Full][%s]", histotitle, Fullplaylist_name);
     DrawMagration_heatMap(hist_Truth_Full,xaxislabel_char,yaxislabel_char,title_other,pdf_middle,&cE,&mnvPlotter);

     TH2D *h_Truth_Full_rowNorm = (TH2D*)hist_Truth_Full->Clone("h_Truth_Full_rowNorm");
     rowNormalize(*h_Truth_Full_rowNorm);
     sprintf(title_other,  "2DMig[rowNorm][Truth] %s [Full][%s]", histotitle, Fullplaylist_name);
     DrawMagration_heatMap(h_Truth_Full_rowNorm,xaxislabel_char,yaxislabel_char,title_other,pdf_middle,&cE,&mnvPlotter);

     TH2D *h_Truth_Full_colNorm = (TH2D*)hist_Truth_Full->Clone("h_Truth_Full_colNorm");
     colNormalize(*h_Truth_Full_colNorm);
     sprintf(title_other,  "2DMig[colNorm][Truth] %s [Full][%s]", histotitle, Fullplaylist_name);
     DrawMagration_heatMap(h_Truth_Full_colNorm,xaxislabel_char,yaxislabel_char,title_other,pdf_middle,&cE,&mnvPlotter);

     ///////////////////////////////////
     //Empty
     ///////////////////////////////////
     char title_Empty[1024];
     sprintf(title_Empty,  "2DMigration %s (Empty)[%s]", histotitle, Emptyplaylist_name);
     string EmptyTitle = string(title_Empty);

     hist_Mig_Empty->Draw("COLZ");
     hist_Mig_Empty->GetXaxis()->CenterTitle();
     hist_Mig_Empty->GetYaxis()->CenterTitle();
     hist_Mig_Empty->GetXaxis()->SetTitle(xaxislabel_char);
     hist_Mig_Empty->GetYaxis()->SetTitle(yaxislabel_char);
     hist_Mig_Empty->GetXaxis()->SetTitleSize(0.038);
     hist_Mig_Empty->GetYaxis()->SetTitleSize(0.038);

     mnvPlotter.AddHistoTitle(EmptyTitle.c_str(), .04);
     mnvPlotter.WritePreliminary("TL", .035, 0, 0, false);

     gPad->Update();
     cE.Modified();

     cE.Print(pdf_middle);
     cE.Closed();

     sprintf(title_other,  "2DMig[RECO] %s [Empty][%s]", histotitle, Emptyplaylist_name);
     DrawMagration_heatMap(hist_Reco_Empty,xaxislabel_char,yaxislabel_char,title_other,pdf_middle,&cE,&mnvPlotter);

     TH2D *h_Reco_Empty_rowNorm = (TH2D*)hist_Reco_Empty->Clone("h_Reco_Empty_rowNorm");
     rowNormalize(*h_Reco_Empty_rowNorm );
     sprintf(title_other,  "2DMig[rowNorm][RECO] %s [Empty][%s]", histotitle, Emptyplaylist_name);
     DrawMagration_heatMap(h_Reco_Empty_rowNorm ,xaxislabel_char,yaxislabel_char,title_other,pdf_middle,&cE,&mnvPlotter);

     TH2D *h_Reco_Empty_colNorm = (TH2D*)hist_Reco_Empty->Clone("h_Reco_Empty_colNorm");
     colNormalize(*h_Reco_Empty_colNorm);
     sprintf(title_other,  "2DMig[colNorm][RECO] %s [Empty][%s]", histotitle, Emptyplaylist_name);
     DrawMagration_heatMap(h_Reco_Empty_colNorm, xaxislabel_char,yaxislabel_char,title_other,pdf_middle,&cE,&mnvPlotter);

     sprintf(title_other,  "2DMig[TRUTH] %s [Empty][%s]", histotitle, Emptyplaylist_name);
     DrawMagration_heatMap(hist_Truth_Empty,xaxislabel_char,yaxislabel_char,title_other,pdf_middle,&cE,&mnvPlotter);

     TH2D *h_Truth_Empty_rowNorm = (TH2D*)hist_Truth_Empty->Clone("h_Truth_Empty_rowNorm");
     rowNormalize(*h_Truth_Empty_rowNorm);
     sprintf(title_other,  "2DMig[rowNorm][Truth] %s [Empty][%s]", histotitle, Fullplaylist_name);
     DrawMagration_heatMap(h_Truth_Empty_rowNorm,xaxislabel_char,yaxislabel_char,title_other,pdf_middle,&cE,&mnvPlotter);

     TH2D *h_Truth_Empty_colNorm = (TH2D*)hist_Truth_Empty->Clone("h_Truth_Empty_colNorm");
     colNormalize(*h_Truth_Empty_colNorm);
     sprintf(title_other,  "2DMig[colNorm][Truth] %s [Empty][%s]", histotitle, Fullplaylist_name);
     DrawMagration_heatMap(h_Truth_Empty_colNorm, xaxislabel_char,yaxislabel_char,title_other,pdf_middle,&cE,&mnvPlotter);


     ///////////////
     ////Full - Empty
     //////////////

     hist_Mig_Full->Add(hist_Mig_Empty,-1);
     hist_Reco_Full->Add(hist_Reco_Empty,-1);
     hist_Truth_Full->Add(hist_Truth_Empty,-1);

     char title_full_Empty[1024];
     sprintf(title_full_Empty,  "2DMigration %s (F-E)[%s-%s]", histotitle, Fullplaylist_name, Emptyplaylist_name);
     string Full_EmptyTitle = string(title_full_Empty);

     hist_Mig_Full->Draw("COLZ");
     hist_Mig_Full->GetXaxis()->CenterTitle();
     hist_Mig_Full->GetYaxis()->CenterTitle();
     hist_Mig_Full->GetXaxis()->SetTitle(xaxislabel_char);
     hist_Mig_Full->GetYaxis()->SetTitle(yaxislabel_char);
     hist_Mig_Full->GetXaxis()->SetTitleSize(0.038);
     hist_Mig_Full->GetYaxis()->SetTitleSize(0.038);

     mnvPlotter.AddHistoTitle(Full_EmptyTitle.c_str(), .04);
     mnvPlotter.WritePreliminary("TL", .035, 0, 0, false);

     gPad->Update();
     cE.Modified();
     cE.Print(pdf_middle);
     cE.Closed();



     sprintf(title_other,  "2DMig[RECO] %s [F-E][%s-%s]", histotitle,Fullplaylist_name, Emptyplaylist_name);
     DrawMagration_heatMap(hist_Reco_Full,xaxislabel_char,yaxislabel_char,title_other,pdf_middle,&cE,&mnvPlotter);

     TH2D *h_Reco_Full_Empty_rowNorm = (TH2D*)hist_Reco_Full->Clone("h_Reco_Full_Empty_rowNorm");
     rowNormalize(*h_Reco_Full_Empty_rowNorm );
     sprintf(title_other,  "2DMig[rowNorm][RECO] %s [F-E][%s-%s]", histotitle, Fullplaylist_name, Emptyplaylist_name);
     DrawMagration_heatMap(h_Reco_Full_Empty_rowNorm ,xaxislabel_char,yaxislabel_char,title_other,pdf_middle,&cE,&mnvPlotter);

     TH2D *h_Reco_Full_Empty_colNorm = (TH2D*)hist_Reco_Full->Clone("h_Reco_Full_Empty_colNorm");
     colNormalize(*h_Reco_Full_colNorm);
     sprintf(title_other,  "2DMig[colNorm][RECO] %s [F-E][%s-%s]", histotitle, Fullplaylist_name, Emptyplaylist_name);
     DrawMagration_heatMap(h_Reco_Full_Empty_colNorm,xaxislabel_char,yaxislabel_char,title_other,pdf_middle,&cE,&mnvPlotter);


     sprintf(title_other,  "2DMig[TRUTH] %s [F-E][%s-%s]", histotitle,Fullplaylist_name, Emptyplaylist_name);
     DrawMagration_heatMap(hist_Truth_Empty,xaxislabel_char,yaxislabel_char,title_other,pdf_middle,&cE,&mnvPlotter);



     TH2D *h_Truth_Full_Empty_rowNorm = (TH2D*)hist_Truth_Full->Clone("h_Truth_Full_Empty_rowNorm");
     rowNormalize(*h_Truth_Full_Empty_rowNorm);
     sprintf(title_other,  "2DMig[rowNorm][Truth] %s [F-E][%s-%s]", histotitle, Fullplaylist_name,Emptyplaylist_name);
     DrawMagration_heatMap(h_Truth_Full_Empty_rowNorm,xaxislabel_char,yaxislabel_char,title_other,pdf_middle,&cE,&mnvPlotter);


     char pdf_End[1024];
     sprintf(pdf_End,  "%s_MIGRATION.pdf)", pdf_label_char);

     TH2D *h_Truth_Full_Empty_colNorm = (TH2D*)hist_Truth_Full->Clone("h_Truth_Full_Empty_colNorm");
     colNormalize(*h_Truth_Full_Empty_colNorm);
     sprintf(title_other,  "2DMig[colNorm][Truth] %s [F-E][%s-%s]", histotitle, Fullplaylist_name,Emptyplaylist_name);
     DrawMagration_heatMap(h_Truth_Full_Empty_colNorm,xaxislabel_char,yaxislabel_char,title_other,pdf_End,&cE,&mnvPlotter);

   }//end function



   void Draw2DFULLStat_CV_SystematicErr(ME_playlist_TFileMAP FullMCMap,     Pot_MapList FullMC_scalerMap,
                                       ME_playlist_TFileMAP EmptyMCMap,   Pot_MapList EmptyMC_scalerMap,
                                       ME_playlist_TFileMAP FullDataMap,  Pot_MapList FullData_scalerMap,
                                       ME_playlist_TFileMAP EmptyDataMap, Pot_MapList EmptyData_scalerMap,
      char *histoName_MC ,char *histoName_data, char* pdf_label, char* hist_title,
      char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG,
       double max_x, double max_y, double x_projectionTxtsize, double y_projectionTxtsize )
   {
    PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);

    Playlist_MnvH2D_Map FULLMC_HistMAP =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(FullMCMap, histoName_MC );
    Playlist_MnvH2D_Map FULLData_HistMAP =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(FullDataMap, histoName_data );

    Playlist_MnvH2D_Map FULLMC_HistMAPScaled =  Scale_MnvH2D_Map_usingPot_MapList(FULLMC_HistMAP , FullMC_scalerMap , histoName_MC  );
    Playlist_MnvH2D_Map FULLData_HistMAPScaled =  Scale_MnvH2D_Map_usingPot_MapList(FULLData_HistMAP , FullData_scalerMap , histoName_data  );

    Playlist_MnvH2D_Map EmptyMC_HistMAP =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(EmptyMCMap, histoName_MC );
    Playlist_MnvH2D_Map EmptyData_HistMAP =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(EmptyDataMap, histoName_data );

    Playlist_MnvH2D_Map EmptyMC_HistMAPScaled =  Scale_MnvH2D_Map_usingPot_MapList(EmptyMC_HistMAP , EmptyMC_scalerMap , histoName_MC  );
    Playlist_MnvH2D_Map EmptyData_HistMAPScaled =  Scale_MnvH2D_Map_usingPot_MapList(EmptyData_HistMAP , EmptyData_scalerMap , histoName_data  );


   typename std::map<ME_helium_Playlists, PlotUtils::MnvH2D*>::const_iterator catMC;
   typename std::map<ME_helium_Playlists, PlotUtils::MnvH2D*>::const_iterator dogData;

   for (catMC = FULLMC_HistMAPScaled.begin(), dogData = FULLData_HistMAPScaled.begin(); catMC != FULLMC_HistMAPScaled.end(); ++catMC, ++dogData)
   {
     std::string Playlist_Name = GetPlaylist_InitialName(catMC->first);
     char Playlist_Name_char[Playlist_Name.length()+1];
     strcpy(Playlist_Name_char,Playlist_Name.c_str());

     std::string HeliumStatus_name = GetPlaylistStatusString(GetPlaylist_HeliumStatus(catMC->first));
     char HeliumStatus_name_char[HeliumStatus_name.length()+1];
     strcpy(HeliumStatus_name_char,HeliumStatus_name.c_str());

   char playlist_title[1024];
   sprintf(playlist_title, "[%s(%s)]",Playlist_Name_char,HeliumStatus_name_char);

   Draw_2D_Panel_MC_andData_frompointer(dogData->second, catMC->second, playlist_title, xaxislabel,  yaxislabel,
     "NEvents", max_x,  max_y, pdf_label,  DoBinwidthNorm, MakeXaxisLOG, x_projectionTxtsize,  y_projectionTxtsize );

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
     sprintf(playlist_title, "[%s(%s)]",Playlist_Name_char,HeliumStatus_name_char);

     Draw_2D_Panel_MC_andData_frompointer(dogData->second, catMC->second, playlist_title, xaxislabel,  yaxislabel,
       "NEvents" ,  max_x,  max_y, pdf_label,  DoBinwidthNorm, MakeXaxisLOG,
       x_projectionTxtsize,  y_projectionTxtsize );
     }
   }//end of function


   void Draw2DFULLStatCOMBINED_CV_SystematicErr(ME_playlist_TFileMAP FullMCMap, Pot_MapList FullMC_POTMap,
                                       ME_playlist_TFileMAP EmptyMCMap,       Pot_MapList EmptyMC_POTMap,
                                       ME_playlist_TFileMAP FullDataMap,     Pot_MapList FullData_POTMap,
                                       ME_playlist_TFileMAP EmptyDataMap,    Pot_MapList EmptyData_POTMap,
      char *histoName_MC ,char *histoName_data, char* pdf_label, char* hist_title,
      char *xaxislabel, char* yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG,
      double max_x, double max_y, double x_projectionTxtsize, double y_projectionTxtsize
    )
   {
    PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);

    Playlist_MnvH2D_Map FULLMC_HistMAP =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(FullMCMap, histoName_MC );
    Playlist_MnvH2D_Map FULLData_HistMAP =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(FullDataMap, histoName_data );

    Playlist_MnvH2D_Map EmptyMC_HistMAP =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(EmptyMCMap, histoName_MC );
    Playlist_MnvH2D_Map EmptyData_HistMAP =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(EmptyDataMap, histoName_data );

    CyroStatusPot_MapList POTMAP_TOTAL =  Constuct_TOTALPOT_cryostatusMap(FullMC_POTMap, EmptyMC_POTMap, FullData_POTMap, EmptyData_POTMap);

    CyroStatusPot_MapList POTMAP_TOTAL_scaler = MakeScaler_TOTALPOT_cryostatusMapTOFULLDATA(POTMAP_TOTAL);
   /////////////////////////////////
   /// Combined kMC_FULL, kMC_EMPTY, kDATA_FULL, kDATA_EMPTY
   /////////////////////////////////
   auto FULL_MC_Hist = Combine_2DHists_fromMAP(FULLMC_HistMAP , kME1F ,"FULL_MC_Hist");
   auto FULL_Data_Hist = Combine_2DHists_fromMAP(FULLData_HistMAP , kME1F ,"FULL_Data_Hist");

   auto FULL_EmptyMC_Hist =(MnvH2D*) FULL_MC_Hist->Clone("FULL_EmptyMC_Hist");
   auto FULL_EmptyData_Hist =(MnvH2D*) FULL_Data_Hist->Clone("FULL_EmptyData_Hist");

   FULL_MC_Hist->Scale(POTMAP_TOTAL_scaler[kMC_FULL]);
   FULL_EmptyMC_Hist->Scale(POTMAP_TOTAL_scaler[kMC_FULL]);


   char playlist_title[1024];
   sprintf(playlist_title, "%s [CombinedFull]", hist_title);



   Draw_2D_Panel_MC_andData_frompointer(FULL_Data_Hist, FULL_MC_Hist, playlist_title, xaxislabel,  yaxislabel,
     "NEvents" ,  max_x,  max_y, pdf_label,  DoBinwidthNorm, MakeXaxisLOG, x_projectionTxtsize,  y_projectionTxtsize );

   auto Empty_MC_Hist = Combine_2DHists_fromMAP(EmptyMC_HistMAP , kME1M ,"Empty_MC_Hist");
   auto Empty_MC_Hist_clone =(MnvH2D*) Empty_MC_Hist->Clone("Empty_MC_Hist_clone");

   auto Empty_Data_Hist = Combine_2DHists_fromMAP(EmptyData_HistMAP , kME1M ,"Empty_Data_Hist");
   auto Empty_Data_Hist_clone =(MnvH2D*) Empty_Data_Hist->Clone("Empty_Data_Hist_clone");




   Empty_MC_Hist->Scale(POTMAP_TOTAL_scaler[kMC_EMPTY]);
   Empty_Data_Hist->Scale(POTMAP_TOTAL_scaler[kDATA_EMPTY]);
   Empty_MC_Hist_clone->Scale(POTMAP_TOTAL_scaler[kMC_EMPTY]);
   Empty_Data_Hist_clone->Scale(POTMAP_TOTAL_scaler[kDATA_EMPTY]);




   sprintf(playlist_title, "%s [CombinedEmpty]", hist_title);

   Draw_2D_Panel_MC_andData_frompointer(Empty_Data_Hist, Empty_MC_Hist, playlist_title, xaxislabel,  yaxislabel,
     "NEvents" ,  max_x,  max_y, pdf_label,  DoBinwidthNorm, MakeXaxisLOG, x_projectionTxtsize,  y_projectionTxtsize );


   FULL_EmptyMC_Hist->Add(Empty_MC_Hist_clone,-1);
   FULL_EmptyData_Hist->Add(Empty_Data_Hist_clone,-1);
      sprintf(playlist_title, "%s [Combined(F-E)]", hist_title);

      Draw_2D_Panel_MC_andData_frompointer(FULL_EmptyData_Hist, FULL_EmptyMC_Hist, playlist_title, xaxislabel,  yaxislabel,
        "NEvents" ,  max_x,  max_y, pdf_label,  DoBinwidthNorm, MakeXaxisLOG, x_projectionTxtsize,  y_projectionTxtsize );


   }//end of function


   void Draw2DFULLStat_2dplotSingle(ME_playlist_TFileMAP FullMCMap,     Pot_MapList FullMC_scalerMap,
                                       ME_playlist_TFileMAP EmptyMCMap,   Pot_MapList EmptyMC_scalerMap,
                                       ME_playlist_TFileMAP FullDataMap,  Pot_MapList FullData_scalerMap,
                                       ME_playlist_TFileMAP EmptyDataMap, Pot_MapList EmptyData_scalerMap,
      char *histoName_MC ,char *histoName_data, char* pdf_label, char* hist_title,
      char *xaxislabel, char* yaxislabel)
   {

     PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
     TCanvas cE("c1","c1");

    Playlist_MnvH2D_Map FULLMC_HistMAP =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(FullMCMap, histoName_MC );
    Playlist_MnvH2D_Map FULLData_HistMAP =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(FullDataMap, histoName_data );

    Playlist_MnvH2D_Map FULLMC_HistMAPScaled =  Scale_MnvH2D_Map_usingPot_MapList(FULLMC_HistMAP , FullMC_scalerMap , histoName_MC  );
    Playlist_MnvH2D_Map FULLData_HistMAPScaled =  Scale_MnvH2D_Map_usingPot_MapList(FULLData_HistMAP , FullData_scalerMap , histoName_data  );

    Playlist_MnvH2D_Map EmptyMC_HistMAP =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(EmptyMCMap, histoName_MC );
    Playlist_MnvH2D_Map EmptyData_HistMAP =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(EmptyDataMap, histoName_data );

    Playlist_MnvH2D_Map EmptyMC_HistMAPScaled =  Scale_MnvH2D_Map_usingPot_MapList(EmptyMC_HistMAP , EmptyMC_scalerMap , histoName_MC  );
    Playlist_MnvH2D_Map EmptyData_HistMAPScaled =  Scale_MnvH2D_Map_usingPot_MapList(EmptyData_HistMAP , EmptyData_scalerMap , histoName_data  );


   typename std::map<ME_helium_Playlists, PlotUtils::MnvH2D*>::const_iterator catMC;
   typename std::map<ME_helium_Playlists, PlotUtils::MnvH2D*>::const_iterator dogData;

   for (catMC = FULLMC_HistMAPScaled.begin(), dogData = FULLData_HistMAPScaled.begin(); catMC != FULLMC_HistMAPScaled.end(); ++catMC, ++dogData)
   {
     std::string Playlist_Name = GetPlaylist_InitialName(catMC->first);
     char Playlist_Name_char[Playlist_Name.length()+1];
     strcpy(Playlist_Name_char,Playlist_Name.c_str());

     std::string HeliumStatus_name = GetPlaylistStatusString(GetPlaylist_HeliumStatus(catMC->first));
     char HeliumStatus_name_char[HeliumStatus_name.length()+1];
     strcpy(HeliumStatus_name_char,HeliumStatus_name.c_str());

     char playlist_title[1024];
     sprintf(playlist_title, " %s [MC][%s(%s)]", hist_title,Playlist_Name_char, HeliumStatus_name_char);
     DrawMagration_heatMap(catMC->second,   xaxislabel, yaxislabel, playlist_title, pdf_label, &cE, &mnvPlotter);

     sprintf(playlist_title, "%s [Data][%s(%s)]",hist_title, Playlist_Name_char,HeliumStatus_name_char);
     DrawMagration_heatMap(dogData->second,   xaxislabel, yaxislabel,playlist_title, pdf_label, &cE, &mnvPlotter);

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
     sprintf(playlist_title, "%s [MC][%s(%s)]", hist_title, Playlist_Name_char,HeliumStatus_name_char);
     DrawMagration_heatMap(catMC->second,   xaxislabel, yaxislabel,playlist_title, pdf_label, &cE, &mnvPlotter);

     sprintf(playlist_title, "%s [Data][%s(%s)]", hist_title, Playlist_Name_char,HeliumStatus_name_char);
     DrawMagration_heatMap(dogData->second, xaxislabel, yaxislabel,playlist_title, pdf_label, &cE, &mnvPlotter);

     }
   }//end of function



       void Draw2DFULLStatCOMBINED_2dplotSingle(ME_playlist_TFileMAP FullMCMap, Pot_MapList FullMC_POTMap,
                                           ME_playlist_TFileMAP EmptyMCMap,       Pot_MapList EmptyMC_POTMap,
                                           ME_playlist_TFileMAP FullDataMap,     Pot_MapList FullData_POTMap,
                                           ME_playlist_TFileMAP EmptyDataMap,    Pot_MapList EmptyData_POTMap,
          char *histoName_MC ,char *histoName_data, char* pdf_label, char* hist_title,
          char *xaxislabel, char* yaxislabel)
       {

         PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
         TCanvas cE("c1","c1");

        Playlist_MnvH2D_Map FULLMC_HistMAP =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(FullMCMap, histoName_MC );
        Playlist_MnvH2D_Map FULLData_HistMAP =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(FullDataMap, histoName_data );

        Playlist_MnvH2D_Map EmptyMC_HistMAP =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(EmptyMCMap, histoName_MC );
        Playlist_MnvH2D_Map EmptyData_HistMAP =  Constuct_mvnH2DMap_FromME_playlist_TFileMAP(EmptyDataMap, histoName_data );

        CyroStatusPot_MapList POTMAP_TOTAL =  Constuct_TOTALPOT_cryostatusMap(FullMC_POTMap, EmptyMC_POTMap, FullData_POTMap, EmptyData_POTMap);

        CyroStatusPot_MapList POTMAP_TOTAL_scaler = MakeScaler_TOTALPOT_cryostatusMapTOFULLDATA(POTMAP_TOTAL);
       /////////////////////////////////
       /// Combined kMC_FULL, kMC_EMPTY, kDATA_FULL, kDATA_EMPTY
       /////////////////////////////////
       auto FULL_MC_Hist = Combine_2DHists_fromMAP(FULLMC_HistMAP , kME1F ,"FULL_MC_Hist");
       auto FULL_Data_Hist = Combine_2DHists_fromMAP(FULLData_HistMAP , kME1F ,"FULL_Data_Hist");

       auto FULL_EmptyMC_Hist =(MnvH2D*) FULL_MC_Hist->Clone("FULL_EmptyMC_Hist");
       auto FULL_EmptyData_Hist =(MnvH2D*) FULL_Data_Hist->Clone("FULL_EmptyData_Hist");

       FULL_MC_Hist->Scale(POTMAP_TOTAL_scaler[kMC_FULL]);
       FULL_EmptyMC_Hist->Scale(POTMAP_TOTAL_scaler[kMC_FULL]);

       char playlist_title[1024];

       sprintf(playlist_title, "%s [MC][CombinedFull]", hist_title);
       DrawMagration_heatMap(FULL_MC_Hist,   xaxislabel, yaxislabel,playlist_title, pdf_label, &cE, &mnvPlotter);

       sprintf(playlist_title, "%s [Data][CombinedFull]", hist_title);
       DrawMagration_heatMap(FULL_Data_Hist,   xaxislabel, yaxislabel,playlist_title, pdf_label, &cE, &mnvPlotter);


       auto Empty_MC_Hist = Combine_2DHists_fromMAP(EmptyMC_HistMAP , kME1M ,"Empty_MC_Hist");
       auto Empty_MC_Hist_clone =(MnvH2D*) Empty_MC_Hist->Clone("Empty_MC_Hist_clone");

       auto Empty_Data_Hist = Combine_2DHists_fromMAP(EmptyData_HistMAP , kME1M ,"Empty_Data_Hist");
       auto Empty_Data_Hist_clone =(MnvH2D*) Empty_Data_Hist->Clone("Empty_Data_Hist_clone");

       Empty_MC_Hist->Scale(POTMAP_TOTAL_scaler[kMC_EMPTY]);
       Empty_Data_Hist->Scale(POTMAP_TOTAL_scaler[kDATA_EMPTY]);
       Empty_MC_Hist_clone->Scale(POTMAP_TOTAL_scaler[kMC_EMPTY]);
       Empty_Data_Hist_clone->Scale(POTMAP_TOTAL_scaler[kDATA_EMPTY]);


       sprintf(playlist_title, "%s [MC][CombinedEmpty]", hist_title);
       DrawMagration_heatMap(Empty_MC_Hist,   xaxislabel, yaxislabel,playlist_title, pdf_label, &cE, &mnvPlotter);


       sprintf(playlist_title, "%s [Data][CombinedEmpty]", hist_title);
       DrawMagration_heatMap(Empty_Data_Hist,   xaxislabel, yaxislabel,playlist_title, pdf_label, &cE, &mnvPlotter);

       FULL_EmptyMC_Hist->Add(Empty_MC_Hist_clone,-1);
       FULL_EmptyData_Hist->Add(Empty_Data_Hist_clone,-1);

       sprintf(playlist_title, "%s [MC][Combined(F-E)]", hist_title);
       DrawMagration_heatMap(FULL_EmptyMC_Hist,   xaxislabel, yaxislabel,playlist_title, pdf_label, &cE, &mnvPlotter);

       sprintf(playlist_title, "%s [Data][Combined(F-E)]", hist_title);
       DrawMagration_heatMap(FULL_EmptyData_Hist,   xaxislabel, yaxislabel,playlist_title, pdf_label, &cE, &mnvPlotter);

       }//end of function
