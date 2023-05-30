#include "Helium2DPlotUtils.h"
using namespace PlotUtils;

const bool DeBug = true;

std::vector<double> GetScales_2d(std::vector< std::pair<TH2*, const char*> > histopts, bool pzProj)
{
	std::vector<double> tmpvect;
	int nbins = histopts[0].first->GetNbinsX() + 2;
	if (pzProj) nbins = histopts[0].first->GetNbinsY() + 2;
	for (int i = 1; i < nbins - 1; i++)
	{
		double maxval = 0;
		for (uint j = 0; j < histopts.size(); j++)
		{
			TH1D *tmp = pzProj ? histopts[j].first->ProjectionX("tmp", i, i) : histopts[j].first->ProjectionY("tmp", i, i);
			int maxbin = tmp->GetMaximumBin();
			double content = tmp->GetBinContent(maxbin);
			if (content > maxval) maxval = content;
		}

		//we want abaout 75% of the 1.49, so 1.15
		double scale = 150. / maxval;
		if (scale > 1)
		{
			int tmpscale = floor(scale *10);
			scale = tmpscale / 10.0;
		}
		else
		{
			int tmpscale = floor(scale *10);
			scale = tmpscale / 10.0;
		}

		if (DeBug == true) std::cout << scale << std::endl;
		if (scale < 0)
		{
			scale = 0;
		}

		tmpvect.push_back(scale);
	}

	return tmpvect;
}

std::vector<double> Normlized_to_lowest_Mulitplers_2d(std::vector<double> multiply_vector)
{
	std::vector<double> multiply_vector_return;
	double lowest = 9999.0;
	for (auto cat: multiply_vector)
	{
		if (cat > 0.0 && cat < lowest)
		{
			lowest = cat;
		}
	}

	for (auto cat: multiply_vector)
	{
		multiply_vector_return.push_back(cat / lowest);
	}

	return multiply_vector_return;
}

std::vector<double> GetScales_2d(std::vector< std::pair<TH2*, const char*> > histopts, bool pzProj, bool donormalized)
{
	auto double_vector = GetScales_2d(histopts, pzProj);
	auto Normal_vector = Normlized_to_lowest_Mulitplers_2d(double_vector);
	if (donormalized == true)
	{
		return Normal_vector;
	}
	else
	{
		return double_vector;
	}
}

void Draw2DCVAndError_FromTFile(TFile *inputFile_MCFULL, TFile *inputFile_MCEMPTY, char *histoName_MC, TFile *inputFile_DATAFULL, TFile *inputFile_DATAEMPTY,
	char *histoName_Data, Pot_MapStatusList POT_MC, Pot_MapStatusList POT_DATA, bool TrueifFullelseEmpty, char *histotitle,
	std::string xaxislabel, std::string yaxislabel, std::string yaxislabel_units, std::string pdf_label, bool DoBinwidthNorm, bool doSmallerrorgrounps, int Print_Error, bool Debug)
{
	PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
	double Ymax = 100.0;
	char pdf_label_char[pdf_label.length() + 1];
	strcpy(pdf_label_char, pdf_label.c_str());
	char yaxislabel_units_char[yaxislabel_units.length() + 1];
	strcpy(yaxislabel_units_char, yaxislabel_units.c_str());
	char yaxisUNITS[1024];
	sprintf(yaxisUNITS, "Event Rate per %s", yaxislabel_units_char);

	myPlotStyle();
	TH1::SetDefaultSumw2();
	gStyle->SetErrorX(0);
	gStyle->SetEndErrorSize(2);
	double scale_to_FULLData[4] = { POT_DATA[kFULL] / POT_MC[kFULL], POT_DATA[kFULL] / POT_MC[kEMPTY], 1.0, POT_DATA[kFULL] / POT_DATA[kEMPTY]
	};

	MnvH2D * mcFull;
	MnvH2D * mcEmpty;
	MnvH2D * dataFull;
	MnvH2D * dataEmpty;
	if (Debug == true)
	{
		std::cout << "trying to get Full MC " << std::endl;
	}

	mcFull = (MnvH2D*) inputFile_MCFULL->Get(histoName_MC);

	if (Debug == true)
	{
		std::cout << "trying to get Full Data " << std::endl;
	}

	dataFull = (MnvH2D*) inputFile_DATAFULL->Get(histoName_Data);
	if (Debug == true)
	{
		std::cout << "trying to get Empty MC " << std::endl;
	}

	mcEmpty = (MnvH2D*) inputFile_MCEMPTY->Get(histoName_MC);
	if (Debug == true)
	{
		std::cout << "trying to get Empty data " << std::endl;
	}

	dataEmpty = (MnvH2D*) inputFile_DATAEMPTY->Get(histoName_Data);

	if (Debug == true)
	{
		std::cout << "Pot Scaling " << std::endl;
	}

	if (Debug == true)
	{
		std::cout << " Scaling MC full =  " << scale_to_FULLData[0] << std::endl;
	}

	mcFull->Scale(scale_to_FULLData[0]);
	if (Debug == true)
	{
		std::cout << " Scaling MC empty =  " << scale_to_FULLData[1] << std::endl;
	}

	mcEmpty->Scale(scale_to_FULLData[1]);
	if (Debug == true)
	{
		std::cout << " Scaling data empty =  " << scale_to_FULLData[3] << std::endl;
	}

	dataEmpty->Scale(scale_to_FULLData[3]);
	//1e-3

	if (Debug == true)
	{
		std::cout << "Normalized scales to 1 " << std::endl;
	}

	mcFull->Scale(1, "width");	//
	mcEmpty->Scale(1, "width");

	dataFull->Scale(1, "width");	//1e-3
	dataEmpty->Scale(1, "width");

	dataFull->SetMarkerStyle(kFullCircle);
	dataFull->SetMarkerSize(0.7);
	dataFull->SetLineColor(kBlack);
	dataFull->SetLineWidth(2);

	if (Debug == true)
	{
		std::cout << "Making CVs with stat errors " << std::endl;
	}

	TH2 *mc_1Full = new TH2D(mcFull->GetCVHistoWithStatError());
	TH2 *dataStat_Full = new TH2D(dataFull->GetCVHistoWithStatError());
	TH2 *data_1Full = new TH2D(dataFull->GetCVHistoWithError());

	TH2 *mc_1Empty = new TH2D(mcEmpty->GetCVHistoWithStatError());
	TH2 *dataStat_Empty = new TH2D(dataEmpty->GetCVHistoWithStatError());
	TH2 *data_1Empty = new TH2D(dataEmpty->GetCVHistoWithError());

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

	std::vector< std::pair<TH2*, const char*> > histAndOpts_FULL;

	histAndOpts_FULL.push_back(std::make_pair(mc_1Full, "hist"));
	histAndOpts_FULL.push_back(std::make_pair(dataStat_Full, "graph e"));
	histAndOpts_FULL.push_back(std::make_pair(data_1Full, "graph ep"));

	std::vector< std::pair<TH2*, const char*> > histAndOpts_Empty;

	histAndOpts_Empty.push_back(std::make_pair(mc_1Empty, "hist"));
	histAndOpts_Empty.push_back(std::make_pair(dataStat_Empty, "graph e"));
	histAndOpts_Empty.push_back(std::make_pair(data_1Empty, "graph ep"));

	////////////////////////////////////////////
	//Full
	///////////////////////////////////////////
	TLegend *leg = new TLegend(0.7, 0.08, 0.9, 0.32);
	leg->SetFillStyle(0);
	leg->SetBorderSize(0);
	leg->SetTextSize(0.025);
	leg->AddEntry(data_1Full, "MINERvA data", "lpe");
	leg->AddEntry(mc_1Full, "MINERvA Tune", "l");

	data_1Full->SetLineWidth(2);
	bool doMultipliers = true;

	std::vector<double> multipliers = GetScales_2d(histAndOpts_FULL, false);
	GridCanvas *gc = plotYAxis1D(histAndOpts_FULL, xaxislabel, yaxislabel, doMultipliers ? &multipliers[0] : NULL);
	gc->SetYLabel_Size(.025);
	gc->SetXLabel_Size(.03);
	gc->SetYLimits(0, Ymax);
	gc->SetYTitle(yaxisUNITS);
	gc->Modified();

	leg->Draw("SAME");
	char pdf1[1024];
	char total_title[1024];
	sprintf(total_title, " %s[Full][Yproj]", histotitle);
	mnvPlotter.AddHistoTitle(total_title, .035);
	//char pdf_label_char[pdf_label.length()+1];
	//strcpy(pdf_label_char,pdf_label.c_str());
	sprintf(pdf1, "%s.pdf", pdf_label_char);
	gc->Print(pdf1);

	std::vector<double> multipliers2 = GetScales_2d(histAndOpts_FULL, true);
	GridCanvas *gc2 = plotYAxis1D(histAndOpts_FULL, xaxislabel, yaxislabel, doMultipliers ? &multipliers2[0] : NULL);
	gc2->SetYLabel_Size(.025);
	gc2->SetXLabel_Size(.03);
	gc2->SetYLimits(0, Ymax);
	gc2->SetYTitle(yaxisUNITS);
	gc2->Modified();
	sprintf(total_title, " %s[Full][Yproj][Scales]", histotitle);
	mnvPlotter.AddHistoTitle(total_title, .035);
	//sprintf(pdf2,  "%s_Full2_Yproj.pdf",pdf_label_char);
	gc2->Print(pdf1);

	std::vector<double> multipliers3 = GetScales_2d(histAndOpts_FULL, false);
	GridCanvas *gc3 = plotXAxis1D(histAndOpts_FULL, yaxislabel, xaxislabel, doMultipliers ? &multipliers3[0] : NULL);
	// Set the y range manually. Can also use gc3->Remax() to guess automatically
	gc3->SetYLabel_Size(.025);
	gc3->SetXLabel_Size(.03);
	gc3->SetYLimits(0, Ymax);
	gc3->SetYTitle(yaxisUNITS);
	gc3->Modified();
	leg->Draw("SAME");
	sprintf(total_title, " %s[Full][Xproj]", histotitle);
	mnvPlotter.AddHistoTitle(total_title, .035);
	gc3->Print(pdf1);
	/////////////////////////
	std::vector<double> multipliers4 = GetScales_2d(histAndOpts_FULL, true);
	GridCanvas *gc4 = plotXAxis1D(histAndOpts_FULL, yaxislabel, xaxislabel, doMultipliers ? &multipliers4[0] : NULL);
	gc4->SetYLabel_Size(.025);
	gc4->SetXLabel_Size(.03);
	gc4->SetYLimits(0, Ymax);
	gc4->SetYTitle(yaxisUNITS);
	sprintf(total_title, " %s[Full][Xproj][Scales]", histotitle);
	mnvPlotter.AddHistoTitle(total_title, .035);
	gc4->Modified();
	//char pdf4[1024];
	//sprintf(pdf4,  "%s_Full2_Xproj.pdf",pdf_label_char);
	gc4->Print(pdf1);
	/////////////////////////////////
	////// EMPTY
	//////////////////////////////
	TLegend *legEmpty = new TLegend(0.7, 0.08, 0.9, 0.32);
	legEmpty->SetFillStyle(0);
	legEmpty->SetBorderSize(0);
	legEmpty->SetTextSize(0.02);
	legEmpty->AddEntry(data_1Empty, "MINERvA data", "lpe");
	legEmpty->AddEntry(mc_1Empty, "MINERvA Tune V1", "l");

	data_1Empty->SetLineWidth(2);
	std::vector<double> multipliers5 = GetScales_2d(histAndOpts_Empty, false);
	GridCanvas *gc5 = plotYAxis1D(histAndOpts_Empty, xaxislabel, yaxislabel, doMultipliers ? &multipliers5[0] : NULL);

	gc5->SetYLabel_Size(.025);
	gc5->SetXLabel_Size(.03);
	gc5->SetYLimits(0, Ymax);
	gc5->SetYTitle(yaxisUNITS);
	sprintf(total_title, " %s[Full][Yproj]", histotitle);
	mnvPlotter.AddHistoTitle(total_title, .035);
	gc5->Modified();
	legEmpty->Draw("SAME");

	//char total_title[1024];
	//sprintf(total_title, "%s%s%s", histotitle, emptyFull," (POT Norm) ");
	//mnvPlotter.AddHistoTitle("COOL", .04);
	//char pdf5[1024];
	//sprintf(pdf5,  "%s_Empty1_Yproj.pdf",pdf_label_char);
	gc5->Print(pdf1);
	std::vector<double> multipliers6 = GetScales_2d(histAndOpts_Empty, true);
	GridCanvas *gc6 = plotYAxis1D(histAndOpts_Empty, xaxislabel, yaxislabel, doMultipliers ? &multipliers6[0] : NULL);
	gc6->SetYLabel_Size(.025);
	gc6->SetXLabel_Size(.03);
	gc6->SetYLimits(0, Ymax);
	gc6->SetYTitle(yaxisUNITS);
	gc6->Modified();
	sprintf(total_title, " %s[Empty][Yproj][Scales]", histotitle);
	mnvPlotter.AddHistoTitle(total_title, .035);
	gc6->Print(pdf1);

	std::vector<double> multipliers7 = GetScales_2d(histAndOpts_Empty, false);
	GridCanvas *gc7 = plotXAxis1D(histAndOpts_Empty, yaxislabel, xaxislabel, doMultipliers ? &multipliers7[0] : NULL);
	// Set the y range manually. Can also use gc3->Remax() to guess automatically
	gc7->SetYLabel_Size(.025);
	gc7->SetXLabel_Size(.03);
	gc7->SetYLimits(0, Ymax);
	gc7->SetYTitle(yaxisUNITS);
	sprintf(total_title, " %s[Empty][Xproj]", histotitle);
	mnvPlotter.AddHistoTitle(total_title, .035);
	gc7->Modified();
	legEmpty->Draw("SAME");
	gc7->Print(pdf1);

	std::vector<double> multipliers8 = GetScales_2d(histAndOpts_Empty, true);
	GridCanvas *gc8 = plotXAxis1D(histAndOpts_Empty, yaxislabel, xaxislabel, doMultipliers ? &multipliers8[0] : NULL);
	gc8->SetYLabel_Size(.025);
	gc8->SetXLabel_Size(.03);
	gc8->SetYLimits(0, Ymax);
	gc8->SetYTitle(yaxisUNITS);
	gc8->Modified();
	sprintf(total_title, " %s[Empty][Xproj][Scales]", histotitle);
	mnvPlotter.AddHistoTitle(total_title, .035);
	gc8->Print(pdf1);

	/////////////////////////////////
	//Full - Empty
	////////////////////////////////

	dataFull->Add(dataEmpty, -1);
	mcFull->Add(mcEmpty, -1);

	TH2 *mc_1Full_Empty = new TH2D(mcFull->GetCVHistoWithStatError());
	TH2 *dataStat_Full_Empty = new TH2D(dataFull->GetCVHistoWithStatError());
	TH2 *data_1Full_Empty = new TH2D(dataFull->GetCVHistoWithError());

	mc_1Full_Empty->SetLineColor(kRed);
	mc_1Full_Empty->SetLineWidth(2);

	dataStat_Full_Empty->SetMarkerStyle(1);
	dataStat_Full_Empty->SetLineColor(kBlack);
	dataStat_Full_Empty->SetLineWidth(2);

	data_1Full_Empty->SetMarkerStyle(kFullCircle);
	data_1Full_Empty->SetMarkerSize(0.7);
	data_1Full_Empty->SetLineColor(kBlack);

	std::vector< std::pair<TH2*, const char*> > histAndOpts_FULL_EMPTY;

	histAndOpts_FULL_EMPTY.push_back(std::make_pair(mc_1Full_Empty, "hist"));
	histAndOpts_FULL_EMPTY.push_back(std::make_pair(dataStat_Full_Empty, "graph e"));
	histAndOpts_FULL_EMPTY.push_back(std::make_pair(data_1Full_Empty, "graph ep"));

	TLegend *leg_full_empty = new TLegend(0.17, 0.7, 0.31, 0.9);
	leg_full_empty->SetFillStyle(0);
	leg_full_empty->SetBorderSize(0);
	leg_full_empty->SetTextSize(0.025);
	leg_full_empty->AddEntry(data_1Full_Empty, "MINERvA data", "lpe");
	leg_full_empty->AddEntry(mc_1Full_Empty, "MINERvA Tune", "l");

	data_1Full_Empty->SetLineWidth(2);

	std::vector<double> multipliers_full_empty_1 = GetScales_2d(histAndOpts_FULL_EMPTY, false);
	GridCanvas *gc_full_empty_1 = plotYAxis1D(histAndOpts_FULL_EMPTY, xaxislabel, yaxislabel, doMultipliers ? &multipliers_full_empty_1[0] : NULL);

	gc_full_empty_1->SetYLimits(0, Ymax);
	gc_full_empty_1->SetYTitle(yaxisUNITS);
	gc_full_empty_1->Modified();
	leg_full_empty->Draw("SAME");
	sprintf(total_title, " %s[F-E][Yproj]", histotitle);
	mnvPlotter.AddHistoTitle(total_title, .035);

	gc_full_empty_1->Print(pdf1);

	std::vector<double> multipliers_full_empty_2 = GetScales_2d(histAndOpts_FULL_EMPTY, true);
	GridCanvas *gc_full_empty_2 = plotYAxis1D(histAndOpts_FULL_EMPTY, xaxislabel, yaxislabel, doMultipliers ? &multipliers_full_empty_2[0] : NULL);
	gc_full_empty_2->SetYLabel_Size(.025);
	gc_full_empty_2->SetXLabel_Size(.03);
	gc_full_empty_2->SetYLimits(0, Ymax);
	gc_full_empty_2->SetYTitle(yaxisUNITS);
	gc_full_empty_2->Modified();
	sprintf(total_title, " %s[F-E][Yproj][Scales]", histotitle);
	mnvPlotter.AddHistoTitle(total_title, .035);

	leg_full_empty->Draw("SAME");
	gc_full_empty_1->Print(pdf1);

	std::vector<double> multipliers_full_empty_3 = GetScales_2d(histAndOpts_FULL_EMPTY, false);
	GridCanvas *gc_full_empty_3 = plotXAxis1D(histAndOpts_FULL_EMPTY, yaxislabel, xaxislabel, doMultipliers ? &multipliers_full_empty_3[0] : NULL);
	gc_full_empty_3->SetYLabel_Size(.025);
	gc_full_empty_3->SetXLabel_Size(.03);
	gc_full_empty_3->SetYLimits(0, Ymax);
	gc_full_empty_3->SetYTitle(yaxisUNITS);
	gc_full_empty_3->Modified();
	sprintf(total_title, " %s[F-E][Xproj]", histotitle);
	mnvPlotter.AddHistoTitle(total_title, .035);
	leg_full_empty->Draw("SAME");
	gc_full_empty_3->Print(pdf1);

	std::vector<double> multipliers_full_empty_4 = GetScales_2d(histAndOpts_FULL_EMPTY, true);
	GridCanvas *gc_full_empty_4 = plotXAxis1D(histAndOpts_FULL_EMPTY, yaxislabel, xaxislabel, doMultipliers ? &multipliers_full_empty_4[0] : NULL);
	gc_full_empty_4->SetYLabel_Size(.025);
	gc_full_empty_4->SetXLabel_Size(.03);
	gc_full_empty_4->SetYLimits(0, Ymax);
	gc_full_empty_4->SetYTitle(yaxisUNITS);
	gc_full_empty_4->Modified();
	sprintf(total_title, " %s[F-E][Xproj][Scales]", histotitle);
	mnvPlotter.AddHistoTitle(total_title, .035);
	leg_full_empty->Draw("SAME");
	gc_full_empty_4->Print(pdf1);

}	//end of function

std::vector< std::pair<TH2*, const char*> > Make_pannelhis_vector(MnvH2D *data, const TObjArray *mcHists, StackType STACKTYPE, TLegend *leg, int Plottype)
	{
		std::vector< std::pair<TH2*, const char*> > histAndOpts;
		TH2 *dataStat = new TH2D(data->GetCVHistoWithStatError());
		TH2 *data_1 = new TH2D(data->GetCVHistoWithError());

		dataStat->SetMarkerStyle(1);
		dataStat->SetLineColor(kBlack);
		dataStat->SetLineWidth(2);

		data_1->SetMarkerStyle(kFullCircle);
		data_1->SetMarkerSize(0.7);
		data_1->SetLineColor(kBlack);

		unsigned int nHists = mcHists->GetEntries();

		MnvH2D *mc_1 = (MnvH2D*) mcHists->At(0);

		for (unsigned int i = 1; i != nHists; ++i)
		{
			MnvH2D *mc_forloop = (MnvH2D*) mcHists->At(i);
			mc_1->Add(mc_forloop, 1.0);
		}

		//mc_1->SetLineColor(0);
		//mc_1->SetLineWidth(2);
		//mc_1->SetFillColor(0);
		//leg->AddEntry(mc_1, "MINERvA Tune", "l");
		//histAndOpts.push_back(std::make_pair(mc_1, "histl"));

		if (STACKTYPE == kMaterial)
		{
			//auto Vector_material_type = getMaterial_typeVector();
			//Material_color_map ColorMap = getColorMap_Material();
			std::cout << "the number of Hist in StackType kmaterial = " << nHists << std::endl;
			for (unsigned int i = 0; i != nHists; ++i)
			{
				MnvH2D *mnv = (MnvH2D*) mcHists->At(i);
				// Let's just make double sure you didn't pass an array of MnvH2D.
				// (Because if you did you'll get an indecipherable seg fault)
				if (std::string(typeid(*mnv).name()).find(std::string("MnvH2D")) ==
					std::string::npos)
				{
					throw std::runtime_error("The TObjArray you passed to DrawDataStackedMC does not contain all MnvH1Ds!");
				}

				//char *hist_name[*(mnv->GetTitle()).length()+1];
				const char *hist_name = mnv->GetTitle();
				auto material_type = getMaterial_fromstring(hist_name);
				std::cout << "checking material type  = " << GetNameMaterial(material_type) << std::endl;
				int color = GetColorNMaterial(material_type);
				TH2 *mc_hist = new TH2D(mnv->GetCVHistoWithStatError());
				mc_hist->SetFillColor(color);
				mc_hist->SetLineColor(color);
				mc_hist->SetLineWidth(2);
				std::cout << "inside Stack function" << std::endl;
				std::cout << "name of stack =  " << hist_name << " Color Number = " << color << std::endl;
				leg->AddEntry(mc_hist, hist_name, "l");
				histAndOpts.push_back(std::make_pair(mc_hist, "hist"));
			}
		}
		else if (STACKTYPE == kInteraction)
		{
			//Interaction_color_map ColorMap = getColorMap_Interaction();
			//auto Vector_Interaction_type = getInteraction_typeVector();

			for (unsigned int i = 0; i != nHists; ++i)
			{
				MnvH2D *mnv = (MnvH2D*) mcHists->At(i);
				// Let's just make double sure you didn't pass an array of MnvH2D.
				// (Because if you did you'll get an indecipherable seg fault)
				if (std::string(typeid(*mnv).name()).find(std::string("MnvH2D")) ==
					std::string::npos)
				{
					throw std::runtime_error("The TObjArray you passed to DrawDataStackedMC does not contain all MnvH1Ds!");
				}

				const char *hist_name = mnv->GetTitle();
				auto Interaction_type = getInteraction_fromstring(hist_name);
				int color = GetColorNInteraction(Interaction_type);
				TH2 *mc_hist = new TH2D(mnv->GetCVHistoWithStatError());
				mc_hist->SetFillColor(color);
				mc_hist->SetLineColor(color);
				mc_hist->SetLineWidth(2);
				leg->AddEntry(mc_hist, hist_name, "l");
				histAndOpts.push_back(std::make_pair(mc_hist, "hist"));
			}
		}
		else if (STACKTYPE == kParticle)
		{
			//Particle_color_map ColorMap = getColorMap_Particle();
			auto Vector_particle = getParticle_typeVector();

			for (unsigned int i = 0; i != nHists; ++i)
			{
				MnvH2D *mnv = (MnvH2D*) mcHists->At(i);
				// Let's just make double sure you didn't pass an array of MnvH2D.
				// (Because if you did you'll get an indecipherable seg fault)
				if (std::string(typeid(*mnv).name()).find(std::string("MnvH2D")) ==
					std::string::npos)
				{
					throw std::runtime_error("The TObjArray you passed to DrawDataStackedMC does not contain all MnvH1Ds!");
				}

				const char *hist_name = mnv->GetTitle();
				auto Particle_type = getParticle_fromstring(hist_name);
				int color = GetColorNParticle(Particle_type);
				TH2 *mc_hist = new TH2D(mnv->GetCVHistoWithStatError());
				mc_hist->SetFillColor(color);
				mc_hist->SetLineColor(color);
				mc_hist->SetLineWidth(2);
				leg->AddEntry(mc_hist, hist_name, "l");
				histAndOpts.push_back(std::make_pair(mc_hist, "hist"));
			}
		}

		leg->AddEntry(data_1, "MINERvA data", "lpe");
		histAndOpts.push_back(std::make_pair(dataStat, "graph e"));
		histAndOpts.push_back(std::make_pair(data_1, "graph ep"));

		return histAndOpts;
	}	//end of function
////////////////////////////////////////////////
std::vector< std::pair<TH2*, const char*> > Make_pannelhis_vector(MnvH2D *data, MnvH2D *MC_total, const TObjArray *mcHists, std::vector<int> color_vector, TLegend* &leg)
	{
		std::vector< std::pair<TH2*, const char*> > histAndOpts;
		TH2 *dataStat = new TH2D(data->GetCVHistoWithStatError());
		TH2 *data_1 = new TH2D(data->GetCVHistoWithError());
		TH2 *mc_1 = new TH2D(MC_total->GetCVHistoWithStatError());

		dataStat->SetMarkerStyle(1);
		dataStat->SetLineColor(kBlack);
		dataStat->SetLineWidth(2);

		data_1->SetMarkerStyle(kFullCircle);
		data_1->SetMarkerSize(0.7);
		data_1->SetLineColor(kBlack);

		unsigned int nHists = mcHists->GetEntries();

		leg->AddEntry(data_1, "MINERvA data", "lpe");
		mc_1->SetLineColor(0);
		mc_1->SetLineWidth(2);
		mc_1->SetFillColor(0);
		leg->AddEntry(mc_1, "MINERvA Tune", "l");

		for (unsigned int i = 0; i != nHists; ++i)
		{
			MnvH2D *mnv = (MnvH2D*) mcHists->At(i);
			// Let's just make double sure you didn't pass an array of MnvH2D.
			// (Because if you did you'll get an indecipherable seg fault)
			if (std::string(typeid(*mnv).name()).find(std::string("MnvH2D")) ==
				std::string::npos)
			{
				throw std::runtime_error("The TObjArray you passed to DrawDataStackedMC does not contain all MnvH1Ds!");
			}

			//char *hist_name[*(mnv->GetTitle()).length()+1];
			const char *hist_name = mnv->GetTitle();
			int color = color_vector.at(i);
			TH2 *mc_hist = new TH2D(mnv->GetCVHistoWithStatError());
			//  mc_hist->SetFillColor(color);
			mc_hist->SetLineColor(color);
			mc_hist->SetLineWidth(2);
			std::cout << "inside Stack function" << std::endl;
			std::cout << "name of stack =  " << hist_name << " Color Number = " << color << std::endl;
			leg->AddEntry(mc_hist, hist_name, "l");
			histAndOpts.push_back(std::make_pair(mc_hist, "hist"));
		}

		histAndOpts.push_back(std::make_pair(mc_1, "hist"));
		histAndOpts.push_back(std::make_pair(dataStat, "graph e"));
		histAndOpts.push_back(std::make_pair(data_1, "graph ep"));

		return histAndOpts;
	}	//end of function

////////////////////////////////////////////////
void DrawSTACKfromHistFilio_FromTFile2D(TFile *inputFile_MCFULL, TFile *inputFile_MCEMPTY, char *histoName_MC, TFile *inputFile_DATAFULL,
	TFile *inputFile_DATAEMPTY, char *histoName_Data, Pot_MapStatusList POT_MC, Pot_MapStatusList POT_DATA, bool TrueifFullelseEmpty, char *histotitle,
	std::string xaxislabel, std::string yaxislabel, const char *yaxisUNITS, std::string pdf_label, bool DoBinwidthNorm, bool doSmallerrorgrounps, StackType STACKTYPE, bool Debug)
{
	//helium_Status kEMPTY, kFULL;
	//PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCompactStyle);
	// PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCNuPionIncStyle);

	//PlotUtils::MnvPlotter mnvPlotter();

	double scale_to_FULLData[4] = { POT_DATA[kFULL] / POT_MC[kFULL], POT_DATA[kFULL] / POT_MC[kEMPTY], 1.0, POT_DATA[kFULL] / POT_DATA[kEMPTY]
	};

	TCanvas cE("cE", "cE");
	std::cout << "trying MC HisName = " << histoName_MC << std::endl;
	std::cout << "trying data HisName = " << histoName_Data << std::endl;

	char Stack_Name[1024];
	char pdf_label_char[pdf_label.length() + 1];
	strcpy(pdf_label_char, pdf_label.c_str());
	bool doMultipliers = true;

	if (STACKTYPE == kMaterial)
	{
		sprintf(Stack_Name, "%s_Material", histoName_MC);
	}
	else if (STACKTYPE == kInteraction)
	{
		sprintf(Stack_Name, "%s_Interaction", histoName_MC);
	}
	else if (STACKTYPE == kParticle)
	{
		sprintf(Stack_Name, "%s_Particle", histoName_MC);
	}
	else
	{
		std::cout << "Error unknown stack type: Ploting Failed" << std::endl;
		return;
	}

	if (Debug == true)
	{
		std::cout << "Getting Hist Using Name: " << Stack_Name << std::endl;
	}

	PlotUtils::HistFolio<PlotUtils::MnvH2D > Full_MC_Stack(		PlotUtils::LoadHistFolioFromFile<PlotUtils::MnvH2D > (*
			inputFile_MCFULL, std::string(Stack_Name)),
		"Full_MC_Stack");

	if (Debug == true)
	{
		std::cout << "Initialize Got FUll MC for Stacks   " << Stack_Name << std::endl;
	}

	PlotUtils::HistFolio<PlotUtils::MnvH2D > Empty_MC_Stack(		PlotUtils::LoadHistFolioFromFile<PlotUtils::MnvH2D > (*
			inputFile_MCEMPTY, std::string(Stack_Name)),
		"Empty_MC_Stack");

	if (Debug == true)
	{
		std::cout << "Initialize Got Empty MC for Stacks   " << Stack_Name << std::endl;
	}

	PlotUtils::HistFolio<PlotUtils::MnvH2D > Full_MC_Stack_FORSUBTRACTION(		PlotUtils::LoadHistFolioFromFile<PlotUtils::MnvH2D > (*
			inputFile_MCFULL, std::string(Stack_Name)),
		"Full_MC_Stack_FORSUBTRACTION");

	if (Debug == true)
	{
		std::cout << "Initialize Got FUll MC for Stacks   " << Stack_Name << std::endl;
	}

	PlotUtils::HistFolio<PlotUtils::MnvH2D > Empty_MC_Stack_FORSUBTRACTION(		PlotUtils::LoadHistFolioFromFile<PlotUtils::MnvH2D > (*
			inputFile_MCEMPTY, std::string(Stack_Name)),
		"Empty_MC_Stack_FORSUBTRACTION");

	if (Debug == true)
	{
		std::cout << "Initialize Got Emtpy MC for Stacks   " << Stack_Name << std::endl;
	}

	if (STACKTYPE == kParticle)
	{
		// Normal method doesn't have enought colors for particle type

		std::vector<int> Helium9_colorScheme = { TColor::GetColor("#D3D3D3"),	//'lightgrey'
			TColor::GetColor("#DA70D6"),	//'orchid'
			TColor::GetColor("#FFA500"),	//'orange'
			TColor::GetColor("#87CEEB"),	//'skyblue'
			TColor::GetColor("#6495ED"),	//'cornflowerblue'
			TColor::GetColor("#00FFFF"),	//'aqua'
			TColor::GetColor("#0000CD"),	//'blue'
			TColor::GetColor("#FF0000"),	//'red'
			TColor::GetColor("#32CD32"),	//'limegreen'
			TColor::GetColor("#FFD700"),	// Gold
			TColor::GetColor("#800000"),	// Maroon
			TColor::GetColor("#555555")	// dark grey
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
	if (Debug == true)
	{
		std::cout << "Passed Making Arrary of Full - Empty Hist " << Stack_Name << std::endl;
	}

	////////////////////////////////////////////////////////////////
	//// Time to PLot
	////////////////////////////////////////////////////////////////
	MnvH2D *hist_Full_data = NULL;
	MnvH2D *hist_Empty_data = NULL;
	MnvH2D *hist_Empty2_data = NULL;
	MnvH2D *hist_Full_Empty_data = NULL;

	if (Debug == true)
	{
		std::cout << "Starting Full, Empty, and Full - Empty plotting loop" << Stack_Name << std::endl;
	}

	for (int fullOrEmpty = 0; fullOrEmpty < 3; fullOrEmpty++)
	{
		if (fullOrEmpty == 0)
		{
			int j = 0;

			for (auto cat: Full_MC_Stack_array)
			{
				if (Debug == true)
				{
					std::cout << "In Loop On element For Full Stacks " << j << std::endl;
				}

				if (DoBinwidthNorm == true)
				{ 		((PlotUtils::MnvH2D *) Full_MC_Stack_array.At(j))->Scale(1.0, "width");
				}

				((PlotUtils::MnvH2D *) Full_MC_Stack_array.At(j))->Scale(scale_to_FULLData[0]);
				j++;
			}

			if (Debug == true)
			{
				std::cout << "inside plotting Loop on element:" << fullOrEmpty << std::endl;
			}

			hist_Full_data = (MnvH2D*) inputFile_DATAFULL->Get(histoName_Data);
			if (Debug == true)
			{
				std::cout << "Initialize Got Full Data for FULL Stacks   " << Stack_Name << std::endl;
			}

			if (DoBinwidthNorm == true)
			{
				hist_Full_data->Scale(1.0, "width");
			}
		}
		else if (fullOrEmpty == 1)
		{
			int k = 0;
			for (auto cat: Empty_MC_Stack_array)
			{
				if (Debug == true)
				{
					std::cout << "In Loop On element For Empty Stacks " << k << std::endl;
				}

				if (DoBinwidthNorm == true)
				{ 		((PlotUtils::MnvH2D *) Empty_MC_Stack_array.At(k))->Scale(1.0, "width");
				}

				((PlotUtils::MnvH2D *) Empty_MC_Stack_array.At(k))->Scale(scale_to_FULLData[1]);
				k++;
			}

			hist_Empty_data = (MnvH2D*) inputFile_DATAEMPTY->Get(histoName_Data);
			if (Debug == true)
			{
				std::cout << "Initialize Got Empty Data for EMTPY Stacks   " << Stack_Name << std::endl;
			}

			if (DoBinwidthNorm == true)
			{
				hist_Empty_data->Scale(1.0, "width");
			}

			hist_Empty_data->Scale(scale_to_FULLData[3]);
		}
		else if (fullOrEmpty == 2)
		{
			int i = 0;

			for (auto cat: FULL_EMPTY_MC_Stack_array)
			{
				if (Debug == true)
				{
					std::cout << "In Loop On element For Full - Empty Stacks " << i << std::endl;
				}

				if (DoBinwidthNorm == true)
				{ 		((PlotUtils::MnvH2D *) EMPTY_forsubtract_MC_Stack_array.At(i))->Scale(1.0, "width");
					((PlotUtils::MnvH2D *) FULL_EMPTY_MC_Stack_array.At(i))->Scale(1.0, "width");
				}

				((PlotUtils::MnvH2D *) FULL_EMPTY_MC_Stack_array.At(i))->Scale(scale_to_FULLData[0]);
				((PlotUtils::MnvH2D *) EMPTY_forsubtract_MC_Stack_array.At(i))->Scale(scale_to_FULLData[1]);

				((PlotUtils::MnvH2D *) FULL_EMPTY_MC_Stack_array.At(i))->Add(((PlotUtils::MnvH2D *) EMPTY_forsubtract_MC_Stack_array.At(i)), -1);
				i++;
			}

			hist_Full_Empty_data = (MnvH2D*) inputFile_DATAFULL->Get(histoName_Data);
			hist_Empty2_data = (MnvH2D*) inputFile_DATAEMPTY->Get(histoName_Data);
			if (Debug == true)
			{
				std::cout << "Initialize Got Empty + FULL Data for Full - EMTPY Stacks   " << Stack_Name << std::endl;
			}

			if (DoBinwidthNorm == true)
			{
				hist_Full_Empty_data->Scale(1.0, "width");
				hist_Empty2_data->Scale(1.0, "width");
			}

			hist_Empty2_data->Scale(scale_to_FULLData[3]);	// Empty Data
			hist_Full_Empty_data->Add(hist_Empty2_data, -1);	// data doesn't need to be scaled
		}

		if (Debug == true)
		{
			std::cout << "Done Scaling and Bin Width Normalization on element: " << fullOrEmpty << std::endl;
		}
	}

	TLegend *leg_full = new TLegend(0.7, 0.08, 0.9, 0.32);
	leg_full->SetFillStyle(0);
	leg_full->SetBorderSize(0);
	leg_full->SetTextSize(0.03);
	TLegend *leg_empty = new TLegend(0.7, 0.08, 0.9, 0.32);
	leg_empty->SetFillStyle(0);
	leg_empty->SetBorderSize(0);
	leg_empty->SetTextSize(0.03);
	TLegend *leg_full_empty = new TLegend(0.7, 0.08, 0.9, 0.32);
	leg_full_empty->SetFillStyle(0);
	leg_full_empty->SetBorderSize(0);
	leg_full_empty->SetTextSize(0.03);
	////////////////////////////////////////////////////////
	////
	////////////////////////////////////////////////////////
	std::vector< std::pair<TH2*, const char*> > histAndOpts_Full;
	std::vector< std::pair<TH2*, const char*> > histAndOpts_Empty;
	std::vector< std::pair<TH2*, const char*> > histAndOpts_Full_Empty;
	char type[1024];

	if (STACKTYPE == kMaterial)
	{
		histAndOpts_Full = Make_pannelhis_vector(hist_Full_data, &Full_MC_Stack_array, kMaterial, leg_full);
		histAndOpts_Empty = Make_pannelhis_vector(hist_Empty_data, &Empty_MC_Stack_array, kMaterial, leg_empty);
		histAndOpts_Full_Empty = Make_pannelhis_vector(hist_Full_Empty_data, &FULL_EMPTY_MC_Stack_array, kMaterial, leg_full_empty);

		sprintf(type, "%s", "material");
	}
	else if (STACKTYPE == kInteraction)
	{
		histAndOpts_Full = Make_pannelhis_vector(hist_Full_data, &Full_MC_Stack_array, kInteraction, leg_full);
		histAndOpts_Empty = Make_pannelhis_vector(hist_Empty_data, &Empty_MC_Stack_array, kInteraction, leg_empty);
		histAndOpts_Full_Empty = Make_pannelhis_vector(hist_Full_Empty_data, &FULL_EMPTY_MC_Stack_array, kInteraction, leg_full_empty);

		sprintf(type, "%s", "interaction");
	}
	else if (STACKTYPE == kParticle)
	{
		histAndOpts_Full = Make_pannelhis_vector(hist_Full_data, &Full_MC_Stack_array, kParticle, leg_full);
		histAndOpts_Empty = Make_pannelhis_vector(hist_Empty_data, &Empty_MC_Stack_array, kParticle, leg_empty);
		histAndOpts_Full_Empty = Make_pannelhis_vector(hist_Full_Empty_data, &FULL_EMPTY_MC_Stack_array, kParticle, leg_full_empty);

		sprintf(type, "%s", "Particle");
	}

	/////////////////////////
	///Full
	////////////////////////

	std::vector<double> multipliers_1 = GetScales_2d(histAndOpts_Full, false);
	GridCanvas *gc_full_1 = plotYAxis1D(histAndOpts_Full, xaxislabel, yaxislabel, doMultipliers ? &multipliers_1[0] : NULL);

	gc_full_1->SetYLimits(0, 300);
	gc_full_1->SetYTitle(yaxisUNITS);
	gc_full_1->Modified();
	leg_full->Draw("SAME");

	char pdf_full_1[1024];
	sprintf(pdf_full_1, "%s_%s_STACKS_Full_Yproj.pdf", pdf_label_char, type);
	gc_full_1->Print(pdf_full_1);

	std::vector<double> multipliers_2 = GetScales_2d(histAndOpts_Full, false);
	GridCanvas *gc_full_2 = plotXAxis1D(histAndOpts_Full, yaxislabel, xaxislabel, doMultipliers ? &multipliers_2[0] : NULL);

	gc_full_2->SetYLimits(0, 300);
	gc_full_2->SetYTitle(yaxisUNITS);
	gc_full_2->Modified();
	//leg_full->Draw("SAME");

	char pdf_full_2[1024];
	sprintf(pdf_full_2, "%s_%s_STACKS_Full_Xproj.pdf", pdf_label_char, type);
	gc_full_2->Print(pdf_full_2);
	/////////////////////////
	///Empty
	////////////////////////

	std::vector<double> multipliers_1empty = GetScales_2d(histAndOpts_Empty, false);
	GridCanvas *gc_empty_1 = plotYAxis1D(histAndOpts_Empty, xaxislabel, yaxislabel, doMultipliers ? &multipliers_1empty[0] : NULL);

	gc_empty_1->SetYLimits(0, 300);
	gc_empty_1->SetYTitle(yaxisUNITS);
	gc_empty_1->Modified();

	leg_empty->Draw("SAME");

	char pdf_empty_1[1024];
	sprintf(pdf_empty_1, "%s_%s_STACKS_Empty_Yproj.pdf", pdf_label_char, type);
	gc_empty_1->Print(pdf_empty_1);

	std::vector<double> multipliers_2empty = GetScales_2d(histAndOpts_Empty, false);
	GridCanvas *gc_empty_2 = plotXAxis1D(histAndOpts_Empty, yaxislabel, xaxislabel, doMultipliers ? &multipliers_2empty[0] : NULL);

	gc_empty_2->SetYLimits(0, 300);
	gc_empty_2->SetYTitle(yaxisUNITS);
	gc_empty_2->Modified();
	//leg_full->Draw("SAME");

	char pdf_empty_2[1024];
	sprintf(pdf_empty_2, "%s_%s_STACKS_Empty_Xproj.pdf", pdf_label_char, type);
	gc_empty_2->Print(pdf_empty_2);

	/////////////////////////
	///Full - Empty
	////////////////////////

	std::vector<double> multipliers_1full_empty = GetScales_2d(histAndOpts_Full_Empty, false);
	GridCanvas *gc_full_empty_1 = plotYAxis1D(histAndOpts_Full_Empty, xaxislabel, yaxislabel, doMultipliers ? &multipliers_1full_empty[0] : NULL);

	gc_full_empty_1->SetYLimits(0, 300);
	gc_full_empty_1->SetYTitle(yaxisUNITS);
	gc_full_empty_1->Modified();

	leg_full_empty->Draw("SAME");

	char pdf_full_empty_1[1024];
	sprintf(pdf_full_empty_1, "%s_%s_STACKS_Full_Empty_Yproj.pdf", pdf_label_char, type);
	gc_full_empty_1->Print(pdf_full_empty_1);

	std::vector<double> multipliers_2full_empty = GetScales_2d(histAndOpts_Full_Empty, false);
	GridCanvas *gc_full_empty_2 = plotXAxis1D(histAndOpts_Full_Empty, yaxislabel, xaxislabel, doMultipliers ? &multipliers_2full_empty[0] : NULL);

	gc_full_empty_2->SetYLimits(0, 300);
	gc_full_empty_2->SetYTitle(yaxisUNITS);
	gc_full_empty_2->Modified();
	//leg_full->Draw("SAME");

	char pdf_full_empty_2[1024];
	sprintf(pdf_full_empty_2, "%s_%s_STACKS_Full_Empty_Xproj.pdf", pdf_label_char, type);
	gc_full_empty_2->Print(pdf_full_empty_2);

}	// END of Function

void DrawSTACKfromHistFilio_FromTFile2D(TFile *inputFile_MC, char *histoName_MC, TFile *inputFile_DATA,
	char *histoName_Data, double POT_MC_to_Data, char *histotitle,
	std::string xaxislabel, std::string yaxislabel, char *zaxislabel_units,
	std::string pdf_label, bool DoBinwidthNorm, StackType STACKTYPE, bool Debug, bool doMultipliers,
	std::vector<double> YMultipliers, std::vector<double> XMultipliers)
{
	//helium_Status kEMPTY, kFULL;
	//PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCompactStyle);
	// PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCNuPionIncStyle);

	//PlotUtils::MnvPlotter mnvPlotter();

	TCanvas cE("cE", "cE");
	std::cout << "trying MC HisName = " << histoName_MC << std::endl;
	std::cout << "trying data HisName = " << histoName_Data << std::endl;

	char Stack_Name[1024];
	char pdf_label_char[pdf_label.length() + 1];
	strcpy(pdf_label_char, pdf_label.c_str());

	if (STACKTYPE == kMaterial)
	{
		sprintf(Stack_Name, "%s_Material", histoName_MC);
	}
	else if (STACKTYPE == kInteraction)
	{
		sprintf(Stack_Name, "%s_Interaction", histoName_MC);
	}
	else if (STACKTYPE == kParticle)
	{
		sprintf(Stack_Name, "%s_Particle", histoName_MC);
	}
	else if (STACKTYPE == kParticle)
	{
		sprintf(Stack_Name, "%s_Particle", histoName_MC);
	}
	else if (STACKTYPE == kCH_Signal_type)
	{
		sprintf(Stack_Name, "%s_SignalSelection", histoName_MC);
	}
	else
	{
		std::cout << "Error unknown stack type: Ploting Failed" << std::endl;
		sprintf(Stack_Name, "%s", histoName_MC);
		std::cout << "Trying to use name : " << histoName_MC << std::endl;
	}

	if (Debug == true)
	{
		std::cout << "Getting Hist Using Name: " << Stack_Name << std::endl;
	}

	PlotUtils::HistFolio<PlotUtils::MnvH2D > MC_Stack(		PlotUtils::LoadHistFolioFromFile<PlotUtils::MnvH2D > (*
			inputFile_MC, std::string(Stack_Name)),
		"MC_Stack");

	if (Debug == true)
	{
		std::cout << "Initialize Got FUll MC for Stacks   " << Stack_Name << std::endl;
	}

	std::vector<int> Helium9_colorScheme = { TColor::GetColor("#D3D3D3"),	//'lightgrey'
		TColor::GetColor("#DA70D6"),	//'orchid'
		TColor::GetColor("#FFA500"),	//'orange'
		TColor::GetColor("#87CEEB"),	//'skyblue'
		TColor::GetColor("#6495ED"),	//'cornflowerblue'
		TColor::GetColor("#00FFFF"),	//'aqua'
		TColor::GetColor("#0000CD"),	//'blue'
		TColor::GetColor("#FF0000"),	//'red'
		TColor::GetColor("#32CD32"),	//'limegreen'
		TColor::GetColor("#FFD700"),	// Gold
		TColor::GetColor("#800000"),	// Maroon
		TColor::GetColor("#555555")	// dark grey
	};

	//MC_Stack.ApplyColorPalette(Helium9_colorScheme);

	////////////////////////////////////////////////////////////////
	//// FUll and Empty
	////////////////////////////////////////////////////////////////
	auto MC_Stack_array = MC_Stack.GetHistArray();

	if (Debug == true)
	{
		std::cout << "Passed Making Arrary of Full - Empty Hist " << Stack_Name << std::endl;
	}

	////////////////////////////////////////////////////////////////
	//// Time to PLot
	////////////////////////////////////////////////////////////////
	MnvH2D *hist_data = NULL;

	if (Debug == true)
	{
		std::cout << "Starting Full, Empty, and Full - Empty plotting loop" << Stack_Name << std::endl;
	}

	int j = 0;

	for (auto cat: MC_Stack_array)
	{
		if (Debug == true)
		{
			std::cout << "In Loop On element For Full Stacks " << j << std::endl;
		}

		((PlotUtils::MnvH2D *) MC_Stack_array.At(j))->Scale(POT_MC_to_Data);
		j++;
	}

	hist_data = (MnvH2D*) inputFile_DATA->Get(histoName_Data);
	if (Debug == true)
	{
		std::cout << "Initialize Got Full Data for FULL Stacks   " << Stack_Name << std::endl;
	}

	bool setMaxY = false;
	////////////////////////////////////////////////////////
	////
	////////////////////////////////////////////////////////
	char xaxislabel_char[xaxislabel.length() + 1];
	strcpy(xaxislabel_char, xaxislabel.c_str());

	char yaxislabel_char[yaxislabel.length() + 1];
	strcpy(yaxislabel_char, yaxislabel.c_str());

	PlotDataStackedMC2D_ProjY(hist_data,
		MC_Stack_array,
		Helium9_colorScheme,
		pdf_label_char, histotitle,
		xaxislabel_char, yaxislabel_char,
		zaxislabel_units,
		99, setMaxY, doMultipliers,
		YMultipliers,
		DoBinwidthNorm, .3
);

	PlotDataStackedMC2D_ProjX(hist_data,
		MC_Stack_array,
		Helium9_colorScheme,
		pdf_label_char, histotitle,
		xaxislabel_char, yaxislabel_char,
		zaxislabel_units,
		99, setMaxY, doMultipliers,
		YMultipliers,
		DoBinwidthNorm, .3
);

}	// END of Function

void Draw2D_Migration_FromTFile(TFile *inputFile_MCFULL, TFile *inputFile_MCEMPTY, char *histoName_MC_Mig, char *histoName_MC_RECO, char *histoName_MC_TRUTH,
	Pot_MapStatusList POT_MC, char *histotitle, char *Fullplaylist_name, char *Emptyplaylist_name, std::string xaxislabel, std::string yaxislabel,
	std::string yaxislabel_units, std::string pdf_label, bool DoBinwidthNorm, bool Debug)
{
	double SCALER_MC_Empty_FUll = POT_MC[kFULL] / POT_MC[kEMPTY];
	PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
	TCanvas cE("", "");

	if (Debug == true)
	{
		std::cout << "trying MC HisName Mig = " << histoName_MC_Mig << std::endl;
		std::cout << "trying MC HisName RECO = " << histoName_MC_RECO << std::endl;
		std::cout << "trying MC HisName TRUTH = " << histoName_MC_TRUTH << std::endl;
	}

	char pdf_label_char[pdf_label.length() + 1];
	strcpy(pdf_label_char, pdf_label.c_str());

	char yaxislabel_char[yaxislabel.length() + 1];
	strcpy(yaxislabel_char, yaxislabel.c_str());

	char xaxislabel_char[xaxislabel.length() + 1];
	strcpy(xaxislabel_char, xaxislabel.c_str());

	MnvH2D *hist_Mig_Full = (MnvH2D*) inputFile_MCFULL->Get(histoName_MC_Mig);
	TH2D *hist_Reco_Full = (TH2D*) inputFile_MCFULL->Get(histoName_MC_RECO);
	TH2D *hist_Truth_Full = (TH2D*) inputFile_MCFULL->Get(histoName_MC_TRUTH);

	MnvH2D *hist_Mig_Empty = (MnvH2D*) inputFile_MCEMPTY->Get(histoName_MC_Mig);
	TH2D *hist_Reco_Empty = (TH2D*) inputFile_MCEMPTY->Get(histoName_MC_RECO);
	TH2D *hist_Truth_Empty = (TH2D*) inputFile_MCEMPTY->Get(histoName_MC_TRUTH);

	hist_Mig_Empty->Scale(SCALER_MC_Empty_FUll);
	hist_Reco_Empty->Scale(SCALER_MC_Empty_FUll);
	hist_Truth_Empty->Scale(SCALER_MC_Empty_FUll);

	char title_full[1024];
	sprintf(title_full, "2DMigration %s (Full)[%s]", histotitle, Fullplaylist_name);
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
	sprintf(pdf_start, "%s_MIGRATION.pdf(", pdf_label_char);
	cE.Print(pdf_start);
	cE.Closed();

	char pdf_middle[1024];
	sprintf(pdf_middle, "%s_MIGRATION.pdf", pdf_label_char);

	char title_other[1024];
	sprintf(title_other, "2DMig[RECO] %s[Full][%s]", histotitle, Fullplaylist_name);
	DrawMagration_heatMap(hist_Reco_Full, xaxislabel_char, yaxislabel_char, title_other, pdf_middle, &cE, &mnvPlotter);

	TH2D *h_Reco_Full_rowNorm = (TH2D*) hist_Reco_Full->Clone("h_Reco_Full_rowNorm");
	rowNormalize(*h_Reco_Full_rowNorm);
	sprintf(title_other, "2DMig[rowNorm][RECO] %s[Full][%s]", histotitle, Fullplaylist_name);
	DrawMagration_heatMap(h_Reco_Full_rowNorm, xaxislabel_char, yaxislabel_char, title_other, pdf_middle, &cE, &mnvPlotter);

	TH2D *h_Reco_Full_colNorm = (TH2D*) hist_Reco_Full->Clone("h_Reco_Full_colNorm");
	colNormalize(*h_Reco_Full_colNorm);
	sprintf(title_other, "2DMig[colNorm][RECO] %s[Full][%s]", histotitle, Fullplaylist_name);
	DrawMagration_heatMap(h_Reco_Full_colNorm, xaxislabel_char, yaxislabel_char, title_other, pdf_middle, &cE, &mnvPlotter);

	sprintf(title_other, "2DMig[TRUTH] %s[Full][%s]", histotitle, Fullplaylist_name);
	DrawMagration_heatMap(hist_Truth_Full, xaxislabel_char, yaxislabel_char, title_other, pdf_middle, &cE, &mnvPlotter);

	TH2D *h_Truth_Full_rowNorm = (TH2D*) hist_Truth_Full->Clone("h_Truth_Full_rowNorm");
	rowNormalize(*h_Truth_Full_rowNorm);
	sprintf(title_other, "2DMig[rowNorm][Truth] %s[Full][%s]", histotitle, Fullplaylist_name);
	DrawMagration_heatMap(h_Truth_Full_rowNorm, xaxislabel_char, yaxislabel_char, title_other, pdf_middle, &cE, &mnvPlotter);

	TH2D *h_Truth_Full_colNorm = (TH2D*) hist_Truth_Full->Clone("h_Truth_Full_colNorm");
	colNormalize(*h_Truth_Full_colNorm);
	sprintf(title_other, "2DMig[colNorm][Truth] %s[Full][%s]", histotitle, Fullplaylist_name);
	DrawMagration_heatMap(h_Truth_Full_colNorm, xaxislabel_char, yaxislabel_char, title_other, pdf_middle, &cE, &mnvPlotter);

	///////////////////////////////////
	//Empty
	///////////////////////////////////
	char title_Empty[1024];
	sprintf(title_Empty, "2DMigration %s (Empty)[%s]", histotitle, Emptyplaylist_name);
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

	sprintf(title_other, "2DMig[RECO] %s[Empty][%s]", histotitle, Emptyplaylist_name);
	DrawMagration_heatMap(hist_Reco_Empty, xaxislabel_char, yaxislabel_char, title_other, pdf_middle, &cE, &mnvPlotter);

	TH2D *h_Reco_Empty_rowNorm = (TH2D*) hist_Reco_Empty->Clone("h_Reco_Empty_rowNorm");
	rowNormalize(*h_Reco_Empty_rowNorm);
	sprintf(title_other, "2DMig[rowNorm][RECO] %s[Empty][%s]", histotitle, Emptyplaylist_name);
	DrawMagration_heatMap(h_Reco_Empty_rowNorm, xaxislabel_char, yaxislabel_char, title_other, pdf_middle, &cE, &mnvPlotter);

	TH2D *h_Reco_Empty_colNorm = (TH2D*) hist_Reco_Empty->Clone("h_Reco_Empty_colNorm");
	colNormalize(*h_Reco_Empty_colNorm);
	sprintf(title_other, "2DMig[colNorm][RECO] %s[Empty][%s]", histotitle, Emptyplaylist_name);
	DrawMagration_heatMap(h_Reco_Empty_colNorm, xaxislabel_char, yaxislabel_char, title_other, pdf_middle, &cE, &mnvPlotter);

	sprintf(title_other, "2DMig[TRUTH] %s[Empty][%s]", histotitle, Emptyplaylist_name);
	DrawMagration_heatMap(hist_Truth_Empty, xaxislabel_char, yaxislabel_char, title_other, pdf_middle, &cE, &mnvPlotter);

	TH2D *h_Truth_Empty_rowNorm = (TH2D*) hist_Truth_Empty->Clone("h_Truth_Empty_rowNorm");
	rowNormalize(*h_Truth_Empty_rowNorm);
	sprintf(title_other, "2DMig[rowNorm][Truth] %s[Empty][%s]", histotitle, Fullplaylist_name);
	DrawMagration_heatMap(h_Truth_Empty_rowNorm, xaxislabel_char, yaxislabel_char, title_other, pdf_middle, &cE, &mnvPlotter);

	TH2D *h_Truth_Empty_colNorm = (TH2D*) hist_Truth_Empty->Clone("h_Truth_Empty_colNorm");
	colNormalize(*h_Truth_Empty_colNorm);
	sprintf(title_other, "2DMig[colNorm][Truth] %s[Empty][%s]", histotitle, Fullplaylist_name);
	DrawMagration_heatMap(h_Truth_Empty_colNorm, xaxislabel_char, yaxislabel_char, title_other, pdf_middle, &cE, &mnvPlotter);

	///////////////
	////Full - Empty
	//////////////

	hist_Mig_Full->Add(hist_Mig_Empty, -1);
	hist_Reco_Full->Add(hist_Reco_Empty, -1);
	hist_Truth_Full->Add(hist_Truth_Empty, -1);

	char title_full_Empty[1024];
	sprintf(title_full_Empty, "2DMigration %s (F-E)[%s-%s]", histotitle, Fullplaylist_name, Emptyplaylist_name);
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

	sprintf(title_other, "2DMig[RECO] %s[F-E][%s-%s]", histotitle, Fullplaylist_name, Emptyplaylist_name);
	DrawMagration_heatMap(hist_Reco_Full, xaxislabel_char, yaxislabel_char, title_other, pdf_middle, &cE, &mnvPlotter);

	TH2D *h_Reco_Full_Empty_rowNorm = (TH2D*) hist_Reco_Full->Clone("h_Reco_Full_Empty_rowNorm");
	rowNormalize(*h_Reco_Full_Empty_rowNorm);
	sprintf(title_other, "2DMig[rowNorm][RECO] %s[F-E][%s-%s]", histotitle, Fullplaylist_name, Emptyplaylist_name);
	DrawMagration_heatMap(h_Reco_Full_Empty_rowNorm, xaxislabel_char, yaxislabel_char, title_other, pdf_middle, &cE, &mnvPlotter);

	TH2D *h_Reco_Full_Empty_colNorm = (TH2D*) hist_Reco_Full->Clone("h_Reco_Full_Empty_colNorm");
	colNormalize(*h_Reco_Full_colNorm);
	sprintf(title_other, "2DMig[colNorm][RECO] %s[F-E][%s-%s]", histotitle, Fullplaylist_name, Emptyplaylist_name);
	DrawMagration_heatMap(h_Reco_Full_Empty_colNorm, xaxislabel_char, yaxislabel_char, title_other, pdf_middle, &cE, &mnvPlotter);

	sprintf(title_other, "2DMig[TRUTH] %s[F-E][%s-%s]", histotitle, Fullplaylist_name, Emptyplaylist_name);
	DrawMagration_heatMap(hist_Truth_Empty, xaxislabel_char, yaxislabel_char, title_other, pdf_middle, &cE, &mnvPlotter);

	TH2D *h_Truth_Full_Empty_rowNorm = (TH2D*) hist_Truth_Full->Clone("h_Truth_Full_Empty_rowNorm");
	rowNormalize(*h_Truth_Full_Empty_rowNorm);
	sprintf(title_other, "2DMig[rowNorm][Truth] %s[F-E][%s-%s]", histotitle, Fullplaylist_name, Emptyplaylist_name);
	DrawMagration_heatMap(h_Truth_Full_Empty_rowNorm, xaxislabel_char, yaxislabel_char, title_other, pdf_middle, &cE, &mnvPlotter);

	char pdf_End[1024];
	sprintf(pdf_End, "%s_MIGRATION.pdf)", pdf_label_char);

	TH2D *h_Truth_Full_Empty_colNorm = (TH2D*) hist_Truth_Full->Clone("h_Truth_Full_Empty_colNorm");
	colNormalize(*h_Truth_Full_Empty_colNorm);
	sprintf(title_other, "2DMig[colNorm][Truth] %s[F-E][%s-%s]", histotitle, Fullplaylist_name, Emptyplaylist_name);
	DrawMagration_heatMap(h_Truth_Full_Empty_colNorm, xaxislabel_char, yaxislabel_char, title_other, pdf_End, &cE, &mnvPlotter);

}	//end function

void Draw2DFULLStat_CV_SystematicErr(ME_playlist_TFileMAP FullMCMap, Pot_MapList FullMC_scalerMap,
	ME_playlist_TFileMAP EmptyMCMap, Pot_MapList EmptyMC_scalerMap,
	ME_playlist_TFileMAP FullDataMap, Pot_MapList FullData_scalerMap,
	ME_playlist_TFileMAP EmptyDataMap, Pot_MapList EmptyData_scalerMap,
	char *histoName_MC, char *histoName_data, char *pdf_label, char *hist_title,
	char *xaxislabel, char *yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG,
	double max_x, double max_y, double x_projectionTxtsize, double y_projectionTxtsize)
{
	PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);

	Playlist_MnvH2D_Map FULLMC_HistMAP = Constuct_mvnH2DMap_FromME_playlist_TFileMAP(FullMCMap, histoName_MC);
	Playlist_MnvH2D_Map FULLData_HistMAP = Constuct_mvnH2DMap_FromME_playlist_TFileMAP(FullDataMap, histoName_data);

	Playlist_MnvH2D_Map FULLMC_HistMAPScaled = Scale_MnvH2D_Map_usingPot_MapList(FULLMC_HistMAP, FullMC_scalerMap, histoName_MC);
	Playlist_MnvH2D_Map FULLData_HistMAPScaled = Scale_MnvH2D_Map_usingPot_MapList(FULLData_HistMAP, FullData_scalerMap, histoName_data);

	Playlist_MnvH2D_Map EmptyMC_HistMAP = Constuct_mvnH2DMap_FromME_playlist_TFileMAP(EmptyMCMap, histoName_MC);
	Playlist_MnvH2D_Map EmptyData_HistMAP = Constuct_mvnH2DMap_FromME_playlist_TFileMAP(EmptyDataMap, histoName_data);

	Playlist_MnvH2D_Map EmptyMC_HistMAPScaled = Scale_MnvH2D_Map_usingPot_MapList(EmptyMC_HistMAP, EmptyMC_scalerMap, histoName_MC);
	Playlist_MnvH2D_Map EmptyData_HistMAPScaled = Scale_MnvH2D_Map_usingPot_MapList(EmptyData_HistMAP, EmptyData_scalerMap, histoName_data);

	typename std::map<ME_helium_Playlists, PlotUtils::MnvH2D*>::const_iterator catMC;
	typename std::map<ME_helium_Playlists, PlotUtils::MnvH2D*>::const_iterator dogData;

	for (catMC = FULLMC_HistMAPScaled.begin(), dogData = FULLData_HistMAPScaled.begin(); catMC != FULLMC_HistMAPScaled.end(); ++catMC, ++dogData)
	{
		std::string Playlist_Name = GetPlaylist_InitialName(catMC->first);
		char Playlist_Name_char[Playlist_Name.length() + 1];
		strcpy(Playlist_Name_char, Playlist_Name.c_str());

		std::string HeliumStatus_name = GetPlaylistStatusString(GetPlaylist_HeliumStatus(catMC->first));
		char HeliumStatus_name_char[HeliumStatus_name.length() + 1];
		strcpy(HeliumStatus_name_char, HeliumStatus_name.c_str());

		char playlist_title[1024];
		sprintf(playlist_title, "[%s(%s)]", Playlist_Name_char, HeliumStatus_name_char);

		Draw_2D_Panel_MC_andData_frompointer(dogData->second, catMC->second, playlist_title, xaxislabel, yaxislabel,
			"NEvents", max_x, max_y, pdf_label, DoBinwidthNorm, MakeXaxisLOG, x_projectionTxtsize, y_projectionTxtsize);
	}

	for (catMC = EmptyMC_HistMAPScaled.begin(), dogData = EmptyData_HistMAPScaled.begin(); catMC != EmptyMC_HistMAPScaled.end(); ++catMC, ++dogData)
	{
		std::string Playlist_Name = GetPlaylist_InitialName(catMC->first);
		char Playlist_Name_char[Playlist_Name.length() + 1];
		strcpy(Playlist_Name_char, Playlist_Name.c_str());

		std::string HeliumStatus_name = GetPlaylistStatusString(GetPlaylist_HeliumStatus(catMC->first));
		char HeliumStatus_name_char[HeliumStatus_name.length() + 1];
		strcpy(HeliumStatus_name_char, HeliumStatus_name.c_str());

		char playlist_title[1024];
		sprintf(playlist_title, "[%s(%s)]", Playlist_Name_char, HeliumStatus_name_char);

		Draw_2D_Panel_MC_andData_frompointer(dogData->second, catMC->second, playlist_title, xaxislabel, yaxislabel,
			"NEvents", max_x, max_y, pdf_label, DoBinwidthNorm, MakeXaxisLOG,
			x_projectionTxtsize, y_projectionTxtsize);
	}
}	//end of function
////////////////////////
//
/////////////////////////
void Draw2DFULLStat_CV_SystematicErrFromPointer(MnvH2D *hist_Data, MnvH2D *hist_MC, ME_helium_Playlists playlist, MnvPlotter *plot,
	char *pdf_label, char *hist_title, char *xaxislabel, char *yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG,
	double max_x, double max_y, double x_projectionTxtsize, double y_projectionTxtsize, double &chisqrt, int &ndf, bool TurnoffPrinting)
{
	PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);

	std::string Playlist_Name = GetPlaylist_InitialName(playlist);
	char Playlist_Name_char[Playlist_Name.length() + 1];
	strcpy(Playlist_Name_char, Playlist_Name.c_str());

	std::string HeliumStatus_name = GetPlaylistStatusString(GetPlaylist_HeliumStatus(playlist));
	char HeliumStatus_name_char[HeliumStatus_name.length() + 1];
	strcpy(HeliumStatus_name_char, HeliumStatus_name.c_str());

	char playlist_title[1024];
	sprintf(playlist_title, "%s[%s(%s)]", hist_title, Playlist_Name_char, HeliumStatus_name_char);
	chisqrt = plot->Chi2DataMC(hist_Data, hist_MC, ndf);

	if (TurnoffPrinting == false)
	{
		Draw_2D_Panel_MC_andData_frompointer(hist_Data, hist_MC, playlist_title, xaxislabel, yaxislabel,
			"NEvents", max_x, max_y, pdf_label, DoBinwidthNorm, MakeXaxisLOG, x_projectionTxtsize, y_projectionTxtsize);
	}
}	//end of function
////////////////////
//
/////////////////////
void Draw2D_Panel_CV_SystematicErrFromPointer(MnvH2D *hist_Data, MnvH2D *hist_MC, char *playlistInfo_char,
	char *HeliumStatus_name_char, MnvPlotter *mnvPlotter,
	char *pdf_label, char *hist_title, char *xaxislabel, char *yaxislabel,
	char *zaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG,
	double max_x, double max_y, double x_projectionTxtsize, double y_projectionTxtsize, double &chisqrt, int &ndf, bool doMultipliers)
{
	char playlist_title[1024];
	sprintf(playlist_title, "%s[%s(%s)]", hist_title, playlistInfo_char, HeliumStatus_name_char);
	chisqrt = mnvPlotter->Chi2DataMC(hist_Data, hist_MC, ndf);

	Draw_2D_Panel_MC_andData_frompointer(hist_Data, hist_MC, playlist_title, xaxislabel, yaxislabel,
		zaxislabel, max_x, max_y, pdf_label, DoBinwidthNorm, MakeXaxisLOG, x_projectionTxtsize, y_projectionTxtsize, doMultipliers);

}	//end of function

void Draw2D_Panel_CV_SystematicErrFromPointer_new(MnvH2D *hist_Data, MnvH2D *hist_MC, char *playlistInfo_char,
	char *HeliumStatus_name_char, MnvPlotter *mnvPlotter,
	char *pdf1, char *hist_title, char *xaxislabel, char *yaxislabel,
	char *zaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG,
	double max_x, double max_y, double x_projectionTxtsize, double y_projectionTxtsize, double &chisqrt, int &ndf)
{
	double Ymax = max_x;
	myPlotStyle();
	TH1::SetDefaultSumw2();
	gStyle->SetErrorX(0);
	gStyle->SetEndErrorSize(2);

	char playlist_title[1024];
	sprintf(playlist_title, "%s[%s(%s)]", hist_title, playlistInfo_char, HeliumStatus_name_char);
	chisqrt = mnvPlotter->Chi2DataMC(hist_Data, hist_MC, ndf);
	char yaxisUNITS[1024];
	sprintf(yaxisUNITS, "%s", zaxislabel);
	TH2 *mc_1Full = new TH2D(hist_MC->GetCVHistoWithStatError());
	TH2 *dataStat_Full = new TH2D(hist_Data->GetCVHistoWithStatError());
	TH2 *data_1Full = new TH2D(hist_Data->GetCVHistoWithError());

	mc_1Full->SetLineColor(kRed);
	mc_1Full->SetLineWidth(2);
	dataStat_Full->SetMarkerStyle(1);
	dataStat_Full->SetLineColor(kBlack);
	dataStat_Full->SetLineWidth(2);
	data_1Full->SetMarkerStyle(kFullCircle);
	data_1Full->SetMarkerSize(0.7);
	data_1Full->SetLineColor(kBlack);
	std::vector< std::pair<TH2*, const char*> > histAndOpts_FULL;
	histAndOpts_FULL.push_back(std::make_pair(mc_1Full, "hist"));
	histAndOpts_FULL.push_back(std::make_pair(dataStat_Full, "graph e"));
	histAndOpts_FULL.push_back(std::make_pair(data_1Full, "graph ep"));

	TLegend *leg = new TLegend(0.7, 0.08, 0.9, 0.32);
	leg->SetFillStyle(0);
	leg->SetBorderSize(0);
	leg->SetTextSize(0.025);
	leg->AddEntry(data_1Full, "MINERvA data", "lpe");
	leg->AddEntry(mc_1Full, "MINERvA Tune", "l");

	data_1Full->SetLineWidth(2);
	bool doMultipliers = true;

	std::vector<double> multipliers = GetScales_2d(histAndOpts_FULL, false);
	GridCanvas *gc = plotYAxis1D(histAndOpts_FULL, xaxislabel, yaxislabel, doMultipliers ? &multipliers[0] : NULL);
	gc->SetYLabel_Size(.025);
	gc->SetXLabel_Size(.03);
	gc->SetYLimits(0, Ymax);
	gc->SetYTitle(yaxisUNITS);
	gc->Modified();

	leg->Draw("SAME");
	//char pdf1[1024];
	char total_title[1024];
	sprintf(total_title, " %s[Yproj]", playlist_title);
	mnvPlotter->AddHistoTitle(total_title, .035);
	//char pdf_label_char[pdf_label.length()+1];
	//strcpy(pdf_label_char,pdf_label.c_str());
	//sprintf(pdf1,  "%s.pdf",pdf_label_char);
	gc->Print(pdf1);

	std::vector<double> multipliers2 = GetScales_2d(histAndOpts_FULL, true);
	GridCanvas *gc2 = plotYAxis1D(histAndOpts_FULL, xaxislabel, yaxislabel, doMultipliers ? &multipliers2[0] : NULL);
	gc2->SetYLabel_Size(.025);
	gc2->SetXLabel_Size(.03);
	gc2->SetYLimits(0, Ymax);
	gc2->SetYTitle(yaxisUNITS);
	gc2->Modified();
	sprintf(total_title, " %s[Yproj][Scales]", playlist_title);
	mnvPlotter->AddHistoTitle(total_title, .035);
	//sprintf(pdf2,  "%s_Full2_Yproj.pdf",pdf_label_char);
	gc2->Print(pdf1);

	std::vector<double> multipliers3 = GetScales_2d(histAndOpts_FULL, false);
	GridCanvas *gc3 = plotXAxis1D(histAndOpts_FULL, yaxislabel, xaxislabel, doMultipliers ? &multipliers3[0] : NULL);
	// Set the y range manually. Can also use gc3->Remax() to guess automatically
	gc3->SetYLabel_Size(.025);
	gc3->SetXLabel_Size(.03);
	gc3->SetYLimits(0, Ymax);
	gc3->SetYTitle(yaxisUNITS);
	gc3->Modified();
	//leg->Draw("SAME");
	sprintf(total_title, " %s[Xproj]", playlist_title);
	mnvPlotter->AddHistoTitle(total_title, .035);
	gc3->Print(pdf1);
	/////////////////////////
	std::vector<double> multipliers4 = GetScales_2d(histAndOpts_FULL, true);
	GridCanvas *gc4 = plotXAxis1D(histAndOpts_FULL, yaxislabel, xaxislabel, doMultipliers ? &multipliers4[0] : NULL);
	gc4->SetYLabel_Size(.025);
	gc4->SetXLabel_Size(.03);
	gc4->SetYLimits(0, Ymax);
	gc4->SetYTitle(yaxisUNITS);
	sprintf(total_title, " %s[Xproj][Scales]", playlist_title);
	mnvPlotter->AddHistoTitle(total_title, .035);
	gc4->Modified();
	//char pdf4[1024];
	//sprintf(pdf4,  "%s_Full2_Xproj.pdf",pdf_label_char);
	gc4->Print(pdf1);

}	//end of function

///////////////////////

void Draw2D_Panel_CV_SystematicErrFromPointer_2(MnvH2D *hist_Data, MnvH2D *hist_MC, char *playlistInfo_char,
	char *HeliumStatus_name_char, MnvPlotter *mnvPlotter,
	char *pdf_label, char *hist_title, char *xaxislabel, char *yaxislabel,
	char *zaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG,
	double max_x, double max_y, double x_projectionTxtsize, double y_projectionTxtsize, double &chisqrt, int &ndf, bool doMultipliers)
{
	char playlist_title[1024];
	sprintf(playlist_title, "%s[%s(%s)]", hist_title, playlistInfo_char, HeliumStatus_name_char);
	chisqrt = mnvPlotter->Chi2DataMC(hist_Data, hist_MC, ndf);

	Draw_2D_Panel_MC_andData_frompointer(hist_Data, hist_MC, playlist_title, xaxislabel, yaxislabel,
		zaxislabel, max_x, max_y, pdf_label, DoBinwidthNorm, MakeXaxisLOG, x_projectionTxtsize, y_projectionTxtsize, doMultipliers);

}	//end of function

///////////////////////
void Draw2DFULLStatCOMBINED_CV_SystematicErr(ME_playlist_TFileMAP FullMCMap, Pot_MapList FullMC_POTMap,
	ME_playlist_TFileMAP EmptyMCMap, Pot_MapList EmptyMC_POTMap,
	ME_playlist_TFileMAP FullDataMap, Pot_MapList FullData_POTMap,
	ME_playlist_TFileMAP EmptyDataMap, Pot_MapList EmptyData_POTMap,
	char *histoName_MC, char *histoName_data, char *pdf_label, char *hist_title,
	char *xaxislabel, char *yaxislabel, bool DoBinwidthNorm, bool MakeXaxisLOG,
	double max_x, double max_y, double x_projectionTxtsize, double y_projectionTxtsize)
{
	PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);

	Playlist_MnvH2D_Map FULLMC_HistMAP = Constuct_mvnH2DMap_FromME_playlist_TFileMAP(FullMCMap, histoName_MC);
	Playlist_MnvH2D_Map FULLData_HistMAP = Constuct_mvnH2DMap_FromME_playlist_TFileMAP(FullDataMap, histoName_data);

	Playlist_MnvH2D_Map EmptyMC_HistMAP = Constuct_mvnH2DMap_FromME_playlist_TFileMAP(EmptyMCMap, histoName_MC);
	Playlist_MnvH2D_Map EmptyData_HistMAP = Constuct_mvnH2DMap_FromME_playlist_TFileMAP(EmptyDataMap, histoName_data);

	CyroStatusPot_MapList POTMAP_TOTAL = Constuct_TOTALPOT_cryostatusMap(FullMC_POTMap, EmptyMC_POTMap, FullData_POTMap, EmptyData_POTMap);

	CyroStatusPot_MapList POTMAP_TOTAL_scaler = MakeScaler_TOTALPOT_cryostatusMapTOFULLDATA(POTMAP_TOTAL);
	/////////////////////////////////
	/// Combined kMC_FULL, kMC_EMPTY, kDATA_FULL, kDATA_EMPTY
	/////////////////////////////////
	auto FULL_MC_Hist = Combine_2DHists_fromMAP(FULLMC_HistMAP, kME1F, "FULL_MC_Hist");
	auto FULL_Data_Hist = Combine_2DHists_fromMAP(FULLData_HistMAP, kME1F, "FULL_Data_Hist");

	auto FULL_EmptyMC_Hist = (MnvH2D*) FULL_MC_Hist->Clone("FULL_EmptyMC_Hist");
	auto FULL_EmptyData_Hist = (MnvH2D*) FULL_Data_Hist->Clone("FULL_EmptyData_Hist");

	FULL_MC_Hist->Scale(POTMAP_TOTAL_scaler[kMC_FULL]);
	FULL_EmptyMC_Hist->Scale(POTMAP_TOTAL_scaler[kMC_FULL]);

	char playlist_title[1024];
	sprintf(playlist_title, "%s[CombinedFull]", hist_title);

	Draw_2D_Panel_MC_andData_frompointer(FULL_Data_Hist, FULL_MC_Hist, playlist_title, xaxislabel, yaxislabel,
		"NEvents", max_x, max_y, pdf_label, DoBinwidthNorm, MakeXaxisLOG, x_projectionTxtsize, y_projectionTxtsize);

	auto Empty_MC_Hist = Combine_2DHists_fromMAP(EmptyMC_HistMAP, kME1M, "Empty_MC_Hist");
	auto Empty_MC_Hist_clone = (MnvH2D*) Empty_MC_Hist->Clone("Empty_MC_Hist_clone");

	auto Empty_Data_Hist = Combine_2DHists_fromMAP(EmptyData_HistMAP, kME1M, "Empty_Data_Hist");
	auto Empty_Data_Hist_clone = (MnvH2D*) Empty_Data_Hist->Clone("Empty_Data_Hist_clone");

	Empty_MC_Hist->Scale(POTMAP_TOTAL_scaler[kMC_EMPTY]);
	Empty_Data_Hist->Scale(POTMAP_TOTAL_scaler[kDATA_EMPTY]);
	Empty_MC_Hist_clone->Scale(POTMAP_TOTAL_scaler[kMC_EMPTY]);
	Empty_Data_Hist_clone->Scale(POTMAP_TOTAL_scaler[kDATA_EMPTY]);

	sprintf(playlist_title, "%s[CombinedEmpty]", hist_title);

	Draw_2D_Panel_MC_andData_frompointer(Empty_Data_Hist, Empty_MC_Hist, playlist_title, xaxislabel, yaxislabel,
		"NEvents", max_x, max_y, pdf_label, DoBinwidthNorm, MakeXaxisLOG, x_projectionTxtsize, y_projectionTxtsize);

	FULL_EmptyMC_Hist->Add(Empty_MC_Hist_clone, -1);
	FULL_EmptyData_Hist->Add(Empty_Data_Hist_clone, -1);
	sprintf(playlist_title, "%s[Combined(F-E)]", hist_title);

	Draw_2D_Panel_MC_andData_frompointer(FULL_EmptyData_Hist, FULL_EmptyMC_Hist, playlist_title, xaxislabel, yaxislabel,
		"NEvents", max_x, max_y, pdf_label, DoBinwidthNorm, MakeXaxisLOG, x_projectionTxtsize, y_projectionTxtsize);

}	//end of function

void Draw2DFULLStat_2dplotSingle(ME_playlist_TFileMAP FullMCMap, Pot_MapList FullMC_scalerMap,
	ME_playlist_TFileMAP EmptyMCMap, Pot_MapList EmptyMC_scalerMap,
	ME_playlist_TFileMAP FullDataMap, Pot_MapList FullData_scalerMap,
	ME_playlist_TFileMAP EmptyDataMap, Pot_MapList EmptyData_scalerMap,
	char *histoName_MC, char *histoName_data, char *pdf_label, char *hist_title,
	char *xaxislabel, char *yaxislabel)
{
	PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
	TCanvas cE("cE", "cE");

	Playlist_MnvH2D_Map FULLMC_HistMAP = Constuct_mvnH2DMap_FromME_playlist_TFileMAP(FullMCMap, histoName_MC);
	Playlist_MnvH2D_Map FULLData_HistMAP = Constuct_mvnH2DMap_FromME_playlist_TFileMAP(FullDataMap, histoName_data);

	Playlist_MnvH2D_Map FULLMC_HistMAPScaled = Scale_MnvH2D_Map_usingPot_MapList(FULLMC_HistMAP, FullMC_scalerMap, histoName_MC);
	Playlist_MnvH2D_Map FULLData_HistMAPScaled = Scale_MnvH2D_Map_usingPot_MapList(FULLData_HistMAP, FullData_scalerMap, histoName_data);

	Playlist_MnvH2D_Map EmptyMC_HistMAP = Constuct_mvnH2DMap_FromME_playlist_TFileMAP(EmptyMCMap, histoName_MC);
	Playlist_MnvH2D_Map EmptyData_HistMAP = Constuct_mvnH2DMap_FromME_playlist_TFileMAP(EmptyDataMap, histoName_data);

	Playlist_MnvH2D_Map EmptyMC_HistMAPScaled = Scale_MnvH2D_Map_usingPot_MapList(EmptyMC_HistMAP, EmptyMC_scalerMap, histoName_MC);
	Playlist_MnvH2D_Map EmptyData_HistMAPScaled = Scale_MnvH2D_Map_usingPot_MapList(EmptyData_HistMAP, EmptyData_scalerMap, histoName_data);

	typename std::map<ME_helium_Playlists, PlotUtils::MnvH2D*>::const_iterator catMC;
	typename std::map<ME_helium_Playlists, PlotUtils::MnvH2D*>::const_iterator dogData;

	for (catMC = FULLMC_HistMAPScaled.begin(), dogData = FULLData_HistMAPScaled.begin(); catMC != FULLMC_HistMAPScaled.end(); ++catMC, ++dogData)
	{
		std::string Playlist_Name = GetPlaylist_InitialName(catMC->first);
		char Playlist_Name_char[Playlist_Name.length() + 1];
		strcpy(Playlist_Name_char, Playlist_Name.c_str());

		std::string HeliumStatus_name = GetPlaylistStatusString(GetPlaylist_HeliumStatus(catMC->first));
		char HeliumStatus_name_char[HeliumStatus_name.length() + 1];
		strcpy(HeliumStatus_name_char, HeliumStatus_name.c_str());

		char playlist_title[1024];
		sprintf(playlist_title, " %s[MC][%s(%s)]", hist_title, Playlist_Name_char, HeliumStatus_name_char);
		DrawMagration_heatMap(catMC->second, xaxislabel, yaxislabel, playlist_title, pdf_label, &cE, &mnvPlotter);

		sprintf(playlist_title, "%s[Data][%s(%s)]", hist_title, Playlist_Name_char, HeliumStatus_name_char);
		DrawMagration_heatMap(dogData->second, xaxislabel, yaxislabel, playlist_title, pdf_label, &cE, &mnvPlotter);
	}

	for (catMC = EmptyMC_HistMAPScaled.begin(), dogData = EmptyData_HistMAPScaled.begin(); catMC != EmptyMC_HistMAPScaled.end(); ++catMC, ++dogData)
	{
		std::string Playlist_Name = GetPlaylist_InitialName(catMC->first);
		char Playlist_Name_char[Playlist_Name.length() + 1];
		strcpy(Playlist_Name_char, Playlist_Name.c_str());

		std::string HeliumStatus_name = GetPlaylistStatusString(GetPlaylist_HeliumStatus(catMC->first));
		char HeliumStatus_name_char[HeliumStatus_name.length() + 1];
		strcpy(HeliumStatus_name_char, HeliumStatus_name.c_str());

		char playlist_title[1024];
		sprintf(playlist_title, "%s[MC][%s(%s)]", hist_title, Playlist_Name_char, HeliumStatus_name_char);
		DrawMagration_heatMap(catMC->second, xaxislabel, yaxislabel, playlist_title, pdf_label, &cE, &mnvPlotter);

		sprintf(playlist_title, "%s[Data][%s(%s)]", hist_title, Playlist_Name_char, HeliumStatus_name_char);
		DrawMagration_heatMap(dogData->second, xaxislabel, yaxislabel, playlist_title, pdf_label, &cE, &mnvPlotter);
	}
}	//end of function

void Draw2DFULLStatCOMBINED_2dplotSingle(ME_playlist_TFileMAP FullMCMap, Pot_MapList FullMC_POTMap,
	ME_playlist_TFileMAP EmptyMCMap, Pot_MapList EmptyMC_POTMap,
	ME_playlist_TFileMAP FullDataMap, Pot_MapList FullData_POTMap,
	ME_playlist_TFileMAP EmptyDataMap, Pot_MapList EmptyData_POTMap,
	char *histoName_MC, char *histoName_data, char *pdf_label, char *hist_title,
	char *xaxislabel, char *yaxislabel)
{
	PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
	TCanvas cE("cE", "cE");

	Playlist_MnvH2D_Map FULLMC_HistMAP = Constuct_mvnH2DMap_FromME_playlist_TFileMAP(FullMCMap, histoName_MC);
	Playlist_MnvH2D_Map FULLData_HistMAP = Constuct_mvnH2DMap_FromME_playlist_TFileMAP(FullDataMap, histoName_data);

	Playlist_MnvH2D_Map EmptyMC_HistMAP = Constuct_mvnH2DMap_FromME_playlist_TFileMAP(EmptyMCMap, histoName_MC);
	Playlist_MnvH2D_Map EmptyData_HistMAP = Constuct_mvnH2DMap_FromME_playlist_TFileMAP(EmptyDataMap, histoName_data);

	CyroStatusPot_MapList POTMAP_TOTAL = Constuct_TOTALPOT_cryostatusMap(FullMC_POTMap, EmptyMC_POTMap, FullData_POTMap, EmptyData_POTMap);

	CyroStatusPot_MapList POTMAP_TOTAL_scaler = MakeScaler_TOTALPOT_cryostatusMapTOFULLDATA(POTMAP_TOTAL);
	/////////////////////////////////
	/// Combined kMC_FULL, kMC_EMPTY, kDATA_FULL, kDATA_EMPTY
	/////////////////////////////////
	auto FULL_MC_Hist = Combine_2DHists_fromMAP(FULLMC_HistMAP, kME1F, "FULL_MC_Hist");
	auto FULL_Data_Hist = Combine_2DHists_fromMAP(FULLData_HistMAP, kME1F, "FULL_Data_Hist");

	auto FULL_EmptyMC_Hist = (MnvH2D*) FULL_MC_Hist->Clone("FULL_EmptyMC_Hist");
	auto FULL_EmptyData_Hist = (MnvH2D*) FULL_Data_Hist->Clone("FULL_EmptyData_Hist");

	FULL_MC_Hist->Scale(POTMAP_TOTAL_scaler[kMC_FULL]);
	FULL_EmptyMC_Hist->Scale(POTMAP_TOTAL_scaler[kMC_FULL]);

	char playlist_title[1024];

	sprintf(playlist_title, "%s[MC][CombinedFull]", hist_title);
	DrawMagration_heatMap(FULL_MC_Hist, xaxislabel, yaxislabel, playlist_title, pdf_label, &cE, &mnvPlotter);

	sprintf(playlist_title, "%s[Data][CombinedFull]", hist_title);
	DrawMagration_heatMap(FULL_Data_Hist, xaxislabel, yaxislabel, playlist_title, pdf_label, &cE, &mnvPlotter);

	auto Empty_MC_Hist = Combine_2DHists_fromMAP(EmptyMC_HistMAP, kME1M, "Empty_MC_Hist");
	auto Empty_MC_Hist_clone = (MnvH2D*) Empty_MC_Hist->Clone("Empty_MC_Hist_clone");

	auto Empty_Data_Hist = Combine_2DHists_fromMAP(EmptyData_HistMAP, kME1M, "Empty_Data_Hist");
	auto Empty_Data_Hist_clone = (MnvH2D*) Empty_Data_Hist->Clone("Empty_Data_Hist_clone");

	Empty_MC_Hist->Scale(POTMAP_TOTAL_scaler[kMC_EMPTY]);
	Empty_Data_Hist->Scale(POTMAP_TOTAL_scaler[kDATA_EMPTY]);
	Empty_MC_Hist_clone->Scale(POTMAP_TOTAL_scaler[kMC_EMPTY]);
	Empty_Data_Hist_clone->Scale(POTMAP_TOTAL_scaler[kDATA_EMPTY]);

	sprintf(playlist_title, "%s[MC][CombinedEmpty]", hist_title);
	DrawMagration_heatMap(Empty_MC_Hist, xaxislabel, yaxislabel, playlist_title, pdf_label, &cE, &mnvPlotter);

	sprintf(playlist_title, "%s[Data][CombinedEmpty]", hist_title);
	DrawMagration_heatMap(Empty_Data_Hist, xaxislabel, yaxislabel, playlist_title, pdf_label, &cE, &mnvPlotter);

	FULL_EmptyMC_Hist->Add(Empty_MC_Hist_clone, -1);
	FULL_EmptyData_Hist->Add(Empty_Data_Hist_clone, -1);

	sprintf(playlist_title, "%s[MC][Combined(F-E)]", hist_title);
	DrawMagration_heatMap(FULL_EmptyMC_Hist, xaxislabel, yaxislabel, playlist_title, pdf_label, &cE, &mnvPlotter);

	sprintf(playlist_title, "%s[Data][Combined(F-E)]", hist_title);
	DrawMagration_heatMap(FULL_EmptyData_Hist, xaxislabel, yaxislabel, playlist_title, pdf_label, &cE, &mnvPlotter);

}	//end of function
double EllipticparaboloidFunction(Double_t *x, Double_t *par)
{
	return ((x[0] *x[0]) / (par[0] *par[0])) + ((x[1] *x[1]) / (par[1] *par[1]));
}

void DrawEllipticparaboloidFit(MnvH2D *hist, const char *xaxislabel, const char *yaxislabel, const char *zaxislabel, const char *Title, const char *pdf, TCanvas *can, MnvPlotter *plot, double MinX, double MaxX, double MinY, double MaxY)
{
	string TotalTitle = string(Title);
	gStyle->SetPalette(kCool);
	TH2F *h_clone = (TH2F*) hist->Clone("h_clone");

	hist->GetXaxis()->CenterTitle();
	hist->GetYaxis()->CenterTitle();
	hist->GetXaxis()->SetTitle(xaxislabel);
	hist->GetYaxis()->SetTitle(yaxislabel);
	hist->GetZaxis()->SetTitle(zaxislabel);
	hist->GetXaxis()->SetTitleSize(0.038);
	hist->GetYaxis()->SetTitleSize(0.038);
	hist->GetXaxis()->SetLabelSize(0.025);
	hist->GetYaxis()->SetLabelSize(0.025);
	hist->GetZaxis()->SetLabelSize(0.028);
	hist->GetXaxis()->SetTitleOffset(1.5);
	hist->GetYaxis()->SetTitleOffset(1.5);
	hist->GetZaxis()->SetTitleSize(0.03);

	hist->Draw("lego");

	//EllipticparaboloidFunction(Double_t *x, Double_t *par)

	TF2 *f2 = new TF2("f2", EllipticparaboloidFunction, MinX, MaxX, MinY, MaxY, 2);
	Double_t f2params[2] = { 4, 4 };

	f2->SetParameters(f2params);
	h_clone->Fit("f2");
	f2->SetParameters(f2params);
	gStyle->SetOptFit();
	f2->Draw("surf1 same");
	auto p0 = f2->GetParameter("p0");
	auto p1 = f2->GetParameter("p1");

	if (DeBug == true) std::cout << " P0 =  " << p0 << std::endl;
	if (DeBug == true) std::cout << " P1 =  " << p1 << std::endl;
	plot->AddHistoTitle(TotalTitle.c_str(), .035);
	plot->WritePreliminary("TL", .035, 0, 0, false);

	gPad->Update();
	can->Modified();
	can->Print(pdf);

	can->Closed();
}

void Draw2DLego(MnvH2D *hist, const char *xaxislabel, const char *yaxislabel, const char *zaxislabel, const char *Title, const char *pdf, TCanvas *can, MnvPlotter *plot)
{
	string TotalTitle = string(Title);
	gStyle->SetPalette(kCool);
	TH2F *h_clone = (TH2F*) hist->Clone("h_clone");

	hist->GetXaxis()->CenterTitle();
	hist->GetYaxis()->CenterTitle();
	hist->GetXaxis()->SetTitle(xaxislabel);
	hist->GetYaxis()->SetTitle(yaxislabel);
	hist->GetZaxis()->SetTitle(zaxislabel);
	hist->GetXaxis()->SetTitleSize(0.038);
	hist->GetXaxis()->SetTitleOffset(1.1);
	hist->GetYaxis()->SetTitleOffset(1.1);
	hist->GetYaxis()->SetTitleSize(0.038);
	hist->GetXaxis()->SetLabelSize(0.025);
	hist->GetYaxis()->SetLabelSize(0.025);

	hist->Draw("lego");

	//EllipticparaboloidFunction(Double_t *x, Double_t *par)
	plot->AddHistoTitle(TotalTitle.c_str(), .035);
	plot->WritePreliminary("TL", .035, 0, 0, false);

	gPad->Update();
	can->Modified();
	can->Print(pdf);

	can->Closed();
}

/////////////////////////////////////////////////////////////
std::vector< std::pair<TH2*, const char*> > getSystHistsAndOpts(MnvH2D *data, bool XprojectionTrue, TLegend* &leg, char *pdf, bool print1Dpanels)
	{
		MnvPlotter plotter;
		plotter.ApplyStyle(PlotUtils::kCCInclusiveHeliumStyle);
		plotter.error_color_map["cv"] = kYellow;
		//plotter.
		// For each bin in the other variable, make a vector of the
		// systematic histograms
		TH2D *histBin = (TH2D*) data->Clone("histBin");
		const int nBins = !XprojectionTrue ? data->GetXaxis()->GetNbins() : data->GetYaxis()->GetNbins();
		std::string VarName = !XprojectionTrue ? data->GetXaxis()->GetTitle() : data->GetYaxis()->GetTitle();
		if (DeBug == true) std::cout << "getSystHistsAndOpts: nBins = " << nBins << std::endl;
		std::vector<std::vector<TH1*>> histsPT;
		histsPT.resize(nBins);
		auto binvector_string = GetStringBinRanges(histBin, !XprojectionTrue, VarName);
		// Get MnvPlotter to plot all the histograms, and slurp them into histsPT
		for (int i = 0; i < nBins; ++i)
		{
			// First plot the histograms in the dummy canvas...
			TCanvas c;
			MnvH1D *proj = XprojectionTrue ? data->ProjectionX(uniq(), i + 1, i + 1) : data->ProjectionY(uniq(), i + 1, i + 1);
			plotter.DrawErrorSummary(proj, "TR", true, true, -1, false, "", true);
			//  mnvPlotter->DrawErrorSummary(hist, "TL", true, true, .00001, false, "", true, "", false);
			leg = new TLegend(*getPadLegend(&c));
			leg->SetName("MyLegend");
			//    c.Print("can.png");
			std::vector<TH1*> padHists = getPadHists(&c);
			histsPT[i] = padHists;
			if (print1Dpanels == true)
			{
				std::string total_title(binvector_string.at(i));
				plotter.AddHistoTitle(total_title.c_str(), .038);
				c.Print(pdf);
			}
		}

		// concatenateHists wants a vector of hists for each of the bins of
		// a given systematic. But histsPT is the other way round (the inner
		// vector loops over systematics).  So we have this fiddly loop to
		// make a transposed version of the vector-of-vector

		// It would have been easier to just pass the original
		// vector-of-vector into concatenateHists, and tell it which
		// systematic we wanted, but I've written and debugged this now, so
		// not changing it

		//  First index is systematic, second
		// index is bin
		std::vector<std::vector<TH1*>> histsPT_transpose;
		int nSyst = histsPT[0].size() - 1;
		if (DeBug == true) std::cout << "There are " << nSyst << " systematics" << std::endl;
		histsPT_transpose.resize(nSyst);

		for (int iSyst = 0; iSyst < nSyst; ++iSyst)
		{
			for (unsigned int iBin = 0; iBin < histsPT.size(); ++iBin)
			{
				histsPT_transpose[iSyst].push_back(histsPT[iBin][iSyst]);
			}
		}

		if (DeBug == true) std::cout << "concatenateHists:Starting Loop" << std::endl;
		std::vector< std::pair<TH2*, const char*> > histsPT2D;
		// TODO: Figure out why the last systematic is crashing
		if (DeBug == true) std::cout << " histsPT_transpose.size() = " << histsPT_transpose.size() << " nSyst = " << nSyst << std::endl;
		for (int iSyst = 0; iSyst < nSyst /*histsPT_transpose.size()*/ ; ++iSyst)
		{
			if (DeBug == true) std::cout << "iSyst = " << iSyst << std::endl;
			TH2 *h2d = concatenateHists(histsPT_transpose[iSyst], XprojectionTrue ? 1 : 2, data);
			// We want to draw all of these histograms as graphs, and exclude
			// the zero bins, to get rid of ROOT artifacts. The "graph0" draw
			// option does that (and I made it safe to pass all graphs)
			histsPT2D.push_back(std::make_pair(h2d, "graph0 l"));	// removed l
		}

		if (DeBug == true) std::cout << "Done getSystHistsAndOpts " << std::endl;
		return histsPT2D;
	}

///////////////////////////////////////////////////////
std::vector< std::pair<TH2*, const char*> > getSystHistsAndOpts_Model(MnvH2D *data, bool XprojectionTrue, TLegend* &leg, char *pdf, bool print1Dpanels)
	{
		MnvPlotter plotter;
		plotter.ApplyStyle(PlotUtils::kCCInclusiveHeliumStyle);
		MakeModelErrorGroups(plotter);
		plotter.error_color_map["cv"] = kYellow;
		//plotter.
		// For each bin in the other variable, make a vector of the
		// systematic histograms
		TH2D *histBin = (TH2D*) data->Clone("histBin");
		const int nBins = !XprojectionTrue ? data->GetXaxis()->GetNbins() : data->GetYaxis()->GetNbins();
		std::string VarName = !XprojectionTrue ? data->GetXaxis()->GetTitle() : data->GetYaxis()->GetTitle();
		if (DeBug == true) std::cout << "getSystHistsAndOpts: nBins = " << nBins << std::endl;
		std::vector<std::vector<TH1*>> histsPT;
		histsPT.resize(nBins);
		auto binvector_string = GetStringBinRanges(histBin, !XprojectionTrue, VarName);
		// Get MnvPlotter to plot all the histograms, and slurp them into histsPT
		for (int i = 0; i < nBins; ++i)
		{
			// First plot the histograms in the dummy canvas...
			TCanvas c;
			MnvH1D *proj = XprojectionTrue ? data->ProjectionX(uniq(), i + 1, i + 1) : data->ProjectionY(uniq(), i + 1, i + 1);
			plotter.DrawErrorSummary(proj, "TR", true, true, -1, false, "", true);
			//  mnvPlotter->DrawErrorSummary(hist, "TL", true, true, .00001, false, "", true, "", false);
			leg = new TLegend(*getPadLegend(&c));
			leg->SetName("MyLegend");
			//    c.Print("can.png");
			std::vector<TH1*> padHists = getPadHists(&c);
			histsPT[i] = padHists;
			if (print1Dpanels == true)
			{
				std::string total_title(binvector_string.at(i));
				plotter.AddHistoTitle(total_title.c_str(), .038);
				c.Print(pdf);
			}
		}

		// concatenateHists wants a vector of hists for each of the bins of
		// a given systematic. But histsPT is the other way round (the inner
		// vector loops over systematics).  So we have this fiddly loop to
		// make a transposed version of the vector-of-vector

		// It would have been easier to just pass the original
		// vector-of-vector into concatenateHists, and tell it which
		// systematic we wanted, but I've written and debugged this now, so
		// not changing it

		//  First index is systematic, second
		// index is bin
		std::vector<std::vector<TH1*>> histsPT_transpose;
		int nSyst = histsPT[0].size() - 1;
		if (DeBug == true) std::cout << "There are " << nSyst << " systematics" << std::endl;
		histsPT_transpose.resize(nSyst);

		for (int iSyst = 0; iSyst < nSyst; ++iSyst)
		{
			for (unsigned int iBin = 0; iBin < histsPT.size(); ++iBin)
			{
				histsPT_transpose[iSyst].push_back(histsPT[iBin][iSyst]);
			}
		}

		if (DeBug == true) std::cout << "concatenateHists:Starting Loop" << std::endl;
		std::vector< std::pair<TH2*, const char*> > histsPT2D;
		// TODO: Figure out why the last systematic is crashing
		if (DeBug == true) std::cout << " histsPT_transpose.size() = " << histsPT_transpose.size() << " nSyst = " << nSyst << std::endl;
		for (int iSyst = 0; iSyst < nSyst /*histsPT_transpose.size()*/ ; ++iSyst)
		{
			if (DeBug == true) std::cout << "iSyst = " << iSyst << std::endl;
			TH2 *h2d = concatenateHists(histsPT_transpose[iSyst], XprojectionTrue ? 1 : 2, data);
			// We want to draw all of these histograms as graphs, and exclude
			// the zero bins, to get rid of ROOT artifacts. The "graph0" draw
			// option does that (and I made it safe to pass all graphs)
			histsPT2D.push_back(std::make_pair(h2d, "graph0 l"));	// removed l
		}

		if (DeBug == true) std::cout << "Done getSystHistsAndOpts " << std::endl;
		return histsPT2D;
	}

///////////////////////////////////////////////////////
std::vector< std::pair<TH2*, const char*> > getSystHistsAndOpts_ErrorGroup(std::string ErrorGroup, MnvH2D *data, bool XprojectionTrue, TLegend* &leg, char *pdf, bool print1Dpanels, MnvPlotter &plotter)
	{
		//MnvPlotter plotter;
		//plotter.ApplyStyle(PlotUtils::kCCInclusiveHeliumStyle);

		// For each bin in the other variable, make a vector of the
		// systematic histograms
		TH2D *histBin = (TH2D*) data->Clone("histBin");
		const int nBins = !XprojectionTrue ? data->GetXaxis()->GetNbins() : data->GetYaxis()->GetNbins();
		std::string VarName = !XprojectionTrue ? data->GetXaxis()->GetTitle() : data->GetYaxis()->GetTitle();
		if (DeBug == true) std::cout << "getSystHistsAndOpts:ErrorGroup nBins = " << nBins << std::endl;
		std::vector<std::vector<TH1*>> histsPT;
		histsPT.resize(nBins);
		auto binvector_string = GetStringBinRanges(histBin, !XprojectionTrue, VarName);
		// Get MnvPlotter to plot all the histograms, and slurp them into histsPT
		for (int i = 0; i < nBins; ++i)
		{
			// First plot the histograms in the dummy canvas...
			TCanvas c;
			MnvH1D *proj = XprojectionTrue ? data->ProjectionX(uniq(), i + 1, i + 1) : data->ProjectionY(uniq(), i + 1, i + 1);
			plotter.DrawErrorSummary(proj, "TR", true, true, .00001, false, ErrorGroup, true, "", false);
			leg = new TLegend(*getPadLegend(&c));
			leg->SetName("MyLegend");
			//    c.Print("can.png");
			std::vector<TH1*> padHists = getPadHists(&c);
			histsPT[i] = padHists;
			if (print1Dpanels == true)
			{
				std::string total_title(binvector_string.at(i));
				plotter.AddHistoTitle(total_title.c_str(), .038);
				c.Print(pdf);
			}
		}

		// concatenateHists wants a vector of hists for each of the bins of
		// a given systematic. But histsPT is the other way round (the inner
		// vector loops over systematics).  So we have this fiddly loop to
		// make a transposed version of the vector-of-vector

		// It would have been easier to just pass the original
		// vector-of-vector into concatenateHists, and tell it which
		// systematic we wanted, but I've written and debugged this now, so
		// not changing it

		//  First index is systematic, second
		// index is bin
		std::vector<std::vector<TH1*>> histsPT_transpose;
		int nSyst = histsPT[0].size() - 1;
		if (DeBug == true) std::cout << "There are " << nSyst << " systematics" << std::endl;
		histsPT_transpose.resize(nSyst);

		for (int iSyst = 0; iSyst < nSyst; ++iSyst)
		{
			for (unsigned int iBin = 0; iBin < histsPT.size(); ++iBin)
			{
				histsPT_transpose[iSyst].push_back(histsPT[iBin][iSyst]);
			}
		}

		if (DeBug == true) std::cout << "getSystHistsAndOpts_ErrorGroup:concatenateHists:Starting Loop" << std::endl;
		std::vector< std::pair<TH2*, const char*> > histsPT2D;
		// TODO: Figure out why the last systematic is crashing
		if (DeBug == true) std::cout << " histsPT_transpose.size() = " << histsPT_transpose.size() << " nSyst = " << nSyst << std::endl;
		for (int iSyst = 0; iSyst < nSyst /*histsPT_transpose.size()*/ ; ++iSyst)
		{
			if (DeBug == true) std::cout << "iSyst = " << iSyst << std::endl;
			TH2 *h2d = concatenateHists(histsPT_transpose[iSyst], XprojectionTrue ? 1 : 2, data);
			// We want to draw all of these histograms as graphs, and exclude
			// the zero bins, to get rid of ROOT artifacts. The "graph0" draw
			// option does that (and I made it safe to pass all graphs)
			histsPT2D.push_back(std::make_pair(h2d, "graph0 l"));	// removed l
		}

		if (DeBug == true) std::cout << "Done getSystHistsAndOpts " << std::endl;
		return histsPT2D;
	}

/////////////////////////////////////////////////////
TH2* concatenateHists(std::vector<TH1*> &hists1D, int axis, TH2D *temp)
{
	assert(hists1D.size());

	TH2 *ret = 0;
	if (axis == 1)
	{
		ret = new TH2D(uniq(), TString::Format(";%s", hists1D[0]->GetXaxis()->GetTitle()),
			hists1D[0]->GetXaxis()->GetNbins(), hists1D[0]->GetXaxis()->GetXbins()->GetArray(),
			temp->GetYaxis()->GetNbins(), temp->GetYaxis()->GetXbins()->GetArray());
	}
	else
	{
		ret = new TH2D(uniq(), TString::Format(";;%s", hists1D[0]->GetXaxis()->GetTitle()),
			temp->GetXaxis()->GetNbins(), temp->GetXaxis()->GetXbins()->GetArray(),
			hists1D[0]->GetXaxis()->GetNbins(), hists1D[0]->GetXaxis()->GetXbins()->GetArray());
	}

	ret->SetLineColor(hists1D[0]->GetLineColor());
	ret->SetLineStyle(hists1D[0]->GetLineStyle());
	//std::cout << "hists1D.size() = " <<hists1D.size() << std::endl;
	for (unsigned int iHist = 0; iHist < hists1D.size(); ++iHist)
	{
		//std::cout<<"hists1D[0]->GetXaxis()->GetNbins()+1 = " << hists1D[0]->GetXaxis()->GetNbins()+1<<std::endl;
		//std::cout<<"hists1D[iHist]->GetXaxis()->GetNbins()+1 = " << hists1D[iHist]->GetXaxis()->GetNbins()+1<<std::endl;
		//  if((hists1D[iHist]->GetXaxis()->GetNbins())==0||hists1D[iHist]->GetXaxis()->GetNbins()!= hists1D[0]->GetXaxis()->GetNbins()) continue;
		for (int j = 0; j < hists1D[0]->GetXaxis()->GetNbins() + 1; ++j)
		{
			//std::cout <<"iHist = "<< iHist << "\t"<<" j=" << j << std::endl;
			int ixBin = axis == 1 ? j : iHist + 1;
			int iyBin = axis == 1 ? iHist + 1 : j;
			//  std::cout << hists1D[iHist]<c< std::endl;
			double content = hists1D[iHist]->GetBinContent(j);
			//std::cout << "\t  ixBin = " << ixBin << "\t iyBin =" << iyBin << "\t  content= " << content << std::endl;
			//std::cout<<"filling Bin Content"<<std::endl;
			ret->SetBinContent(ixBin, iyBin, content);
			//std::cout<<"finished Bin Content"<<std::endl;
		}
	}

	if (DeBug == true) std::cout << "about to return" << std::endl;
	return ret;
}

// =====================================================================
void DrawPanel_SystematicErrorPlots_ProjectionY(MnvH2D *data_input, std::string variablex, std::string variabley,
	char *title_char, char *pdf_label, double SetYmax, bool setMaxY, bool print1dPlots)
{
	myPlotStyle();
	TH1::SetDefaultSumw2();
	gStyle->SetErrorX(0);
	gStyle->SetEndErrorSize(2);
	MnvPlotter plotter;
	plotter.ApplyStyle(PlotUtils::kCCInclusiveHeliumStyle);
	//TLegend *leg1 = NULL;
	TLegend *leg2 = NULL;
	MnvH2D *data = (PlotUtils::MnvH2D *) data_input->Clone("data");
	//std::vector<std::pair<TH2*, const char*> > histsPT2D_Xproject=getSystHistsAndOpts(data,  true, *& leg1);
	if (DeBug == true) std::cout << "Starting to getSystHistsAndOpts" << std::endl;
	std::vector< std::pair<TH2*, const char*> > histsPT2D_Yproject = getSystHistsAndOpts(data, false, *& leg2, pdf_label, print1dPlots);
	//leg1->SetLineColor(kWhite);
	//leg1->SetFillColor(kWhite);
	leg2->SetLineColor(kWhite);
	leg2->SetFillColor(kWhite);
	if (DeBug == true) std::cout << "Starting to Plot" << std::endl;
	GridCanvas *gcPT_Y = plotYAxis1D(histsPT2D_Yproject, variabley.c_str(), variablex.c_str());

	gcPT_Y->SetYTitle("Fractional Uncertainty");
	double MaxY = gcPT_Y->GetPadMax();
	if (setMaxY == false) gcPT_Y->SetYLimits(0, MaxY *SetYmax);
	else gcPT_Y->SetYLimits(0, SetYmax);
	gcPT_Y->SetYLabel_Size(.025);
	gcPT_Y->SetXLabel_Size(.03);
	leg2->SetX1(0.43);
	leg2->SetY1(0.15);
	leg2->SetX2(0.98);
	leg2->SetY2(0.35);
	leg2->SetNColumns(3);
	leg2->SetTextSize(0.02);

	leg2->Draw("SAME");
	gcPT_Y->Modified();
	std::string TotalTitle(title_char);
	plotter.AddHistoTitle(TotalTitle.c_str(), .035);
	gcPT_Y->Print(pdf_label);

	delete gcPT_Y;
	//cdelete gcPT_X;

}

//=====================================================================
void DrawPanel_SystematicErrorPlots_ProjectionY_model(MnvH2D *data_input, std::string variablex, std::string variabley,
	char *title_char, char *pdf_label, double SetYmax, bool setMaxY, bool print1dPlots)
{
	myPlotStyle();
	TH1::SetDefaultSumw2();
	gStyle->SetErrorX(0);
	gStyle->SetEndErrorSize(2);
	MnvPlotter plotter;
	plotter.ApplyStyle(PlotUtils::kCCInclusiveHeliumStyle);

	//TLegend *leg1 = NULL;
	TLegend *leg2 = NULL;
	MnvH2D *data = (PlotUtils::MnvH2D *) data_input->Clone("data");
	//std::vector<std::pair<TH2*, const char*> > histsPT2D_Xproject=getSystHistsAndOpts(data,  true, *& leg1);
	if (DeBug == true) std::cout << "Starting to getSystHistsAndOpts" << std::endl;
	std::vector< std::pair<TH2*, const char*> > histsPT2D_Yproject = getSystHistsAndOpts_Model(data, false, *& leg2, pdf_label, print1dPlots);
	//leg1->SetLineColor(kWhite);
	//leg1->SetFillColor(kWhite);
	leg2->SetLineColor(kWhite);
	leg2->SetFillColor(kWhite);
	if (DeBug == true) std::cout << "Starting to Plot" << std::endl;
	GridCanvas *gcPT_Y = plotYAxis1D(histsPT2D_Yproject, variabley.c_str(), variablex.c_str());

	gcPT_Y->SetYTitle("Fractional Uncertainty");
	double MaxY = gcPT_Y->GetPadMax();
	if (setMaxY == false) gcPT_Y->SetYLimits(0, MaxY *SetYmax);
	else gcPT_Y->SetYLimits(0, SetYmax);
	gcPT_Y->SetYLabel_Size(.025);
	gcPT_Y->SetXLabel_Size(.03);
	leg2->SetX1(0.43);
	leg2->SetY1(0.15);
	leg2->SetX2(0.98);
	leg2->SetY2(0.35);
	leg2->SetNColumns(3);
	leg2->SetTextSize(0.02);

	leg2->Draw("SAME");
	gcPT_Y->Modified();
	std::string TotalTitle(title_char);
	plotter.AddHistoTitle(TotalTitle.c_str(), .035);
	gcPT_Y->Print(pdf_label);

	delete gcPT_Y;
	//cdelete gcPT_X;

}

//======================================================================
void DrawPanel_SystematicErrorPlots_ProjectionY_E_theta(MnvH2D *data_input, std::string variablex, std::string variabley,
	char *title_char, char *pdf_label, double SetYmax, bool setMaxY, bool print1dPlots)
{
	myPlotStyle();
	TH1::SetDefaultSumw2();
	gStyle->SetErrorX(0);
	gStyle->SetEndErrorSize(2);
	MnvPlotter plotter;
	plotter.ApplyStyle(PlotUtils::kCCInclusiveHeliumStyle);
	//TLegend *leg1 = NULL;
	TLegend *leg2 = NULL;
	MnvH2D *data = (PlotUtils::MnvH2D *) data_input->Clone("data");
	//std::vector<std::pair<TH2*, const char*> > histsPT2D_Xproject=getSystHistsAndOpts(data,  true, *& leg1);
	if (DeBug == true) std::cout << "Starting to getSystHistsAndOpts" << std::endl;
	std::vector< std::pair<TH2*, const char*> > histsPT2D_Yproject = getSystHistsAndOpts(data, false, *& leg2, pdf_label, print1dPlots);
	//leg1->SetLineColor(kWhite);
	//leg1->SetFillColor(kWhite);
	leg2->SetLineColor(kWhite);
	leg2->SetFillColor(kWhite);
	if (DeBug == true) std::cout << "Starting to Plot" << std::endl;
	GridCanvas *gcPT_Y = plotYAxis1D(histsPT2D_Yproject, variabley.c_str(), variablex.c_str());

	gcPT_Y->SetYTitle("Fractional Uncertainty");
	double MaxY = gcPT_Y->GetPadMax();
	if (setMaxY == false) gcPT_Y->SetYLimits(0, MaxY *SetYmax);
	else gcPT_Y->SetYLimits(0, SetYmax);
	gcPT_Y->SetYLabel_Size(.025);
	gcPT_Y->SetXLabel_Size(.03);
	leg2->SetX1(0.34);
	leg2->SetY1(0.15);
	leg2->SetX2(0.98);
	leg2->SetY2(0.30);
	leg2->SetNColumns(4);
	leg2->SetTextSize(0.02);

	//leg2->Draw("SAME");
	gcPT_Y->Modified();
	std::string TotalTitle(title_char);
	plotter.AddHistoTitle(TotalTitle.c_str(), .035);
	gcPT_Y->Print(pdf_label);

	delete gcPT_Y;
	//cdelete gcPT_X;

}

//=====================================================================
void DrawPanel_SystematicErrorPlots_ProjectionY_Groups(TCanvas *cE, MnvH2D *data_input, std::string variablex, std::string variabley,
	char *title_char, char *pdf_label, double SetYmax, bool setMaxY, bool print1dPlots, bool applyingModel)
{
	myPlotStyle();
	if (DeBug == true) std::cout << "inside:DrawPanel_SystematicErrorPlots_ProjectionY_Groups name:" << std::endl;

	TH1::SetDefaultSumw2();
	gStyle->SetErrorX(0);
	gStyle->SetEndErrorSize(2);
	MnvPlotter plotter;
	bool isXProjection = false;
	plotter.ApplyStyle(PlotUtils::kCCInclusiveHeliumStyle);

	if (applyingModel == true)
	{
		MakeModelErrorGroups(plotter);
	}

	//// adding this for now for debuging
	//plotter->error_color_map["cv"] = kYellow;
	//std::vector<std::string > input; input.push_back("cv");
	//plotter->error_summary_group_map["cv"] = input;
	//TLegend *leg1 = NULL;

	MnvH2D *data = (PlotUtils::MnvH2D *) data_input->Clone("data");
	//std::vector<std::pair<TH2*, const char*> > histsPT2D_Xproject=getSystHistsAndOpts(data,  true, *& leg1);
	if (DeBug == true) std::cout << "Starting to getSystHistsAndOpts For Groups" << std::endl;
	//auto groupNames=plotter.error_summary_group_map;
	GridCanvas * gcPT_Y;
	//for(auto cat: groupNames){std::cout<<"cat ="<<cat.first<<std::end;}

	//for(auto cat = plotter.error_summary_group_map.begin(); cat != plotter.error_summary_group_map.end(); cat++)
	for (auto
		const &cat: plotter.error_summary_group_map)
	{
		TLegend * leg2;
		std::string inputstring = cat.first;
		if (DeBug == true) std::cout << "Trying to Print Error Group Name: " << inputstring << std::endl;
		std::vector< std::pair<TH2*, const char*> > ErrorGroupYproject = getSystHistsAndOpts_ErrorGroup(inputstring, data, isXProjection, leg2, pdf_label, print1dPlots, plotter);
		leg2->SetLineColor(kWhite);
		leg2->SetFillColor(kWhite);
		gcPT_Y = plotYAxis1D(ErrorGroupYproject, variabley.c_str(), variablex.c_str());
		gcPT_Y->SetYTitle("Fractional Uncertainty");
		double MaxY = gcPT_Y->GetPadMax();
		if (setMaxY == false) gcPT_Y->SetYLimits(0, MaxY *SetYmax);
		else gcPT_Y->SetYLimits(0, SetYmax);
		gcPT_Y->SetYLabel_Size(.025);
		gcPT_Y->SetXLabel_Size(.035);
		leg2->SetX1(0.43);
		leg2->SetY1(0.15);
		leg2->SetX2(0.98);
		leg2->SetY2(0.35);
		leg2->SetNColumns(4);
		leg2->SetTextSize(0.015);
		leg2->Draw("SAME");
		gcPT_Y->Modified();

		char ErrorTitle[1024];
		sprintf(ErrorTitle, "%s Error Group %s", title_char, inputstring.c_str());
		std::string TotalTitle(ErrorTitle);
		plotter.AddHistoTitle(TotalTitle.c_str(), .035);
		gcPT_Y->Print(pdf_label);
	}

	delete gcPT_Y;

}

void DrawPanel_SystematicErrorPlots_ProjectionY_Groups(std::string groupName, MnvH2D *data_input, std::string variablex, std::string variabley,
	char *title_char, char *pdf_label, double SetYmax, bool setMaxY, bool print1dPlots, bool applyingModel)
{
	myPlotStyle();
	if (DeBug == true) std::cout << "inside:DrawPanel_SystematicErrorPlots_ProjectionY_Groups and making : " << groupName << std::endl;

	TH1::SetDefaultSumw2();
	gStyle->SetErrorX(0);
	gStyle->SetEndErrorSize(2);
	MnvPlotter plotter;
	bool isXProjection = false;
	plotter.ApplyStyle(PlotUtils::kCCInclusiveHeliumStyle);
	if (applyingModel)
	{
		MakeModelErrorGroups(plotter);
	}

	MnvH2D *data = (PlotUtils::MnvH2D *) data_input->Clone("data");
	TLegend *leg2 = NULL;

	if (DeBug == true) std::cout << "Starting to getSystHistsAndOpts For Groups" << std::endl;

	std::string inputstring = groupName;
	if (DeBug == true) std::cout << "Trying to Print Error Group Name: " << inputstring << std::endl;
	std::vector< std::pair<TH2*, const char*> > ErrorGroupYproject = getSystHistsAndOpts_ErrorGroup(inputstring, data, isXProjection, leg2, pdf_label, print1dPlots, plotter);
	leg2->SetLineColor(kWhite);
	leg2->SetFillColor(kWhite);
	GridCanvas *gcPT_Y = plotYAxis1D(ErrorGroupYproject, variabley.c_str(), variablex.c_str());
	gcPT_Y->SetYTitle("Fractional Uncertainty");
	double MaxY = gcPT_Y->GetPadMax();
	if (setMaxY == false) gcPT_Y->SetYLimits(0, MaxY *SetYmax);
	else gcPT_Y->SetYLimits(0, SetYmax);
	gcPT_Y->SetYLabel_Size(.025);
	gcPT_Y->SetXLabel_Size(.03);
	leg2->SetX1(0.43);
	leg2->SetY1(0.15);
	leg2->SetX2(0.98);
	leg2->SetY2(0.35);
	leg2->SetNColumns(3);
	leg2->SetTextSize(0.02);
	leg2->Draw("SAME");
	gcPT_Y->Modified();

	char ErrorTitle[1024];
	sprintf(ErrorTitle, "%s Error Group %s", title_char, inputstring.c_str());
	std::string TotalTitle(ErrorTitle);
	plotter.AddHistoTitle(TotalTitle.c_str(), .035);
	gcPT_Y->Print(pdf_label);

	delete gcPT_Y;

}

void DrawPanel_SystematicErrorPlots_ProjectionX_Groups(std::string groupName, MnvH2D *data_input, std::string variablex, std::string variabley,
	char *title_char, char *pdf_label, double SetXmax, bool setMaxX, bool print1dPlots, bool applyingModel)
{
	myPlotStyle();
	if (DeBug == true) std::cout << "inside:DrawPanel_SystematicErrorPlots_ProjectionX_Groups making error with name :  " << groupName << std::endl;

	TH1::SetDefaultSumw2();
	gStyle->SetErrorX(0);
	gStyle->SetEndErrorSize(2);
	MnvPlotter plotter;
	bool isXProjection = true;
	plotter.ApplyStyle(PlotUtils::kCCInclusiveHeliumStyle);
	if (applyingModel)
	{
		MakeModelErrorGroups(plotter);
	}

	MnvH2D *data = (PlotUtils::MnvH2D *) data_input->Clone("data");
	TLegend *leg2 = NULL;

	if (DeBug == true) std::cout << "Starting to getSystHistsAndOpts For Groups" << std::endl;

	std::string inputstring = groupName;
	if (DeBug == true) std::cout << "Trying to Print Error Group Name: " << inputstring << std::endl;
	std::vector< std::pair<TH2*, const char*> > ErrorGroupXproject = getSystHistsAndOpts_ErrorGroup(inputstring, data, isXProjection, leg2, pdf_label, print1dPlots, plotter);
	leg2->SetLineColor(kWhite);
	leg2->SetFillColor(kWhite);
	GridCanvas *gcPT_X = plotXAxis1D(ErrorGroupXproject, variabley.c_str(), variablex.c_str());
	gcPT_X->SetYTitle("Fractional Uncertainty");
	double MaxX = gcPT_X->GetPadMax();
	if (setMaxX == false) gcPT_X->SetYLimits(0, MaxX *SetXmax);
	else gcPT_X->SetYLimits(0, SetXmax);
	gcPT_X->SetYLabel_Size(.03);
	gcPT_X->SetXLabel_Size(.03);
	leg2->SetX1(0.43);
	leg2->SetY1(0.15);
	leg2->SetX2(0.98);
	leg2->SetY2(0.35);
	leg2->SetNColumns(4);
	leg2->SetTextSize(0.015);
	//leg2->Draw("SAME");
	gcPT_X->Modified();

	char ErrorTitle[1024];
	sprintf(ErrorTitle, "%s Error Group %s", title_char, inputstring.c_str());
	std::string TotalTitle(ErrorTitle);
	plotter.AddHistoTitle(TotalTitle.c_str(), .035);
	gcPT_X->Print(pdf_label);

	delete gcPT_X;

}

void DrawPanel_SystematicErrorPlots_ProjectionX(MnvH2D *data, std::string variablex, std::string variabley,
	char *title_char, char *pdf_label, double SetYmax, bool setMaxY, bool print1dPlots)
{
	myPlotStyle();
	TH1::SetDefaultSumw2();
	gStyle->SetErrorX(0);
	gStyle->SetEndErrorSize(2);
	MnvPlotter plotter;
	plotter.ApplyStyle(PlotUtils::kCCInclusiveHeliumStyle);
	TLegend *leg1 = NULL;
	if (DeBug == true) std::cout << "Starting to getSystHistsAndOpts" << std::endl;
	std::vector< std::pair<TH2*, const char*> > histsPT2D_Xproject = getSystHistsAndOpts(data, true, *& leg1, pdf_label, print1dPlots);
	leg1->SetLineColor(kWhite);
	leg1->SetFillColor(kWhite);
	//std::cout<< "Starting to Plot"<<std::endl;
	GridCanvas *gcPT_X = plotXAxis1D(histsPT2D_Xproject, variablex.c_str(), variabley.c_str());

	gcPT_X->SetYTitle("Fractional Uncertainty");
	double MaxX = gcPT_X->GetPadMax();
	double MaxY = gcPT_X->GetPadMax();
	if (setMaxY == false) gcPT_X->SetYLimits(0, MaxY *SetYmax);
	else gcPT_X->SetYLimits(0, SetYmax *.999);
	gcPT_X->SetYLabel_Size(.025);
	gcPT_X->SetXLabel_Size(.03);
	leg1->SetX1(0.43);
	leg1->SetY1(0.15);
	leg1->SetX2(0.98);
	leg1->SetY2(0.35);
	leg1->SetNColumns(3);
	leg1->SetTextSize(0.02);

	//leg1->Draw("SAME");
	gcPT_X->Modified();
	std::string TotalTitle(title_char);
	plotter.AddHistoTitle(TotalTitle.c_str(), .035);
	gcPT_X->Print(pdf_label);

	delete gcPT_X;

}

//=====================================================================
void DrawPanel_SystematicErrorPlots_ProjectionX_model(MnvH2D *data, std::string variablex, std::string variabley,
	char *title_char, char *pdf_label, double SetYmax, bool setMaxY, bool print1dPlots)
{
	myPlotStyle();
	TH1::SetDefaultSumw2();
	gStyle->SetErrorX(0);
	gStyle->SetEndErrorSize(2);
	MnvPlotter plotter;
	plotter.ApplyStyle(PlotUtils::kCCInclusiveHeliumStyle);
	TLegend *leg1 = NULL;
	if (DeBug == true) std::cout << "Starting to getSystHistsAndOpts" << std::endl;
	std::vector< std::pair<TH2*, const char*> > histsPT2D_Xproject = getSystHistsAndOpts_Model(data, true, *& leg1, pdf_label, print1dPlots);
	leg1->SetLineColor(kWhite);
	leg1->SetFillColor(kWhite);
	//std::cout<< "Starting to Plot"<<std::endl;
	GridCanvas *gcPT_X = plotXAxis1D(histsPT2D_Xproject, variablex.c_str(), variabley.c_str());

	gcPT_X->SetYTitle("Fractional Uncertainty");
	double MaxX = gcPT_X->GetPadMax();
	double MaxY = gcPT_X->GetPadMax();
	if (setMaxY == false) gcPT_X->SetYLimits(0, MaxY *SetYmax);
	else gcPT_X->SetYLimits(0, SetYmax *.999);
	gcPT_X->SetYLabel_Size(.025);
	gcPT_X->SetXLabel_Size(.03);
	leg1->SetX1(0.43);
	leg1->SetY1(0.15);
	leg1->SetX2(0.98);
	leg1->SetY2(0.35);
	leg1->SetNColumns(3);
	leg1->SetTextSize(0.02);

	//leg1->Draw("SAME");
	gcPT_X->Modified();
	std::string TotalTitle(title_char);
	plotter.AddHistoTitle(TotalTitle.c_str(), .035);
	gcPT_X->Print(pdf_label);

	delete gcPT_X;

}

//=====================================================================
void DrawPanel_SystematicErrorPlots_ProjectionX_E_theta(MnvH2D *data, std::string variablex, std::string variabley,
	char *title_char, char *pdf_label, double SetYmax, bool setMaxY, bool print1dPlots)
{
	myPlotStyle();
	TH1::SetDefaultSumw2();
	gStyle->SetErrorX(0);
	gStyle->SetEndErrorSize(2);
	MnvPlotter plotter;
	plotter.ApplyStyle(PlotUtils::kCCInclusiveHeliumStyle);
	TLegend *leg1 = NULL;
	if (DeBug == true) std::cout << "Starting to getSystHistsAndOpts" << std::endl;
	std::vector< std::pair<TH2*, const char*> > histsPT2D_Xproject = getSystHistsAndOpts(data, true, *& leg1, pdf_label, print1dPlots);
	leg1->SetLineColor(kWhite);
	leg1->SetFillColor(kWhite);
	//std::cout<< "Starting to Plot"<<std::endl;
	GridCanvas *gcPT_X = plotXAxis1D(histsPT2D_Xproject, variablex.c_str(), variabley.c_str());

	gcPT_X->SetYTitle("Fractional Uncertainty");
	double MaxX = gcPT_X->GetPadMax();
	double MaxY = gcPT_X->GetPadMax();
	if (setMaxY == false) gcPT_X->SetYLimits(0, MaxY *SetYmax);
	else gcPT_X->SetYLimits(0, SetYmax);
	gcPT_X->SetYLabel_Size(.025);
	gcPT_X->SetXLabel_Size(.03);
	leg1->SetX1(0.8);
	leg1->SetY1(0.05);
	leg1->SetX2(0.99);
	leg1->SetY2(0.38);
	leg1->SetNColumns(1);
	leg1->SetTextSize(0.015);

	leg1->Draw("SAME");
	gcPT_X->Modified();
	std::string TotalTitle(title_char);
	plotter.AddHistoTitle(TotalTitle.c_str(), .035);
	gcPT_X->Print(pdf_label);

	delete gcPT_X;

}

//=====================================================================
void DrawPanel_MC_dataErrorPlots_ProjectionY(MnvH2D *data, MnvH2D *h_MC, std::string variablex, std::string variabley,
	char *title_char, char *pdf_label, double Ymaxlimit)
{
	myPlotStyle();
	TH1::SetDefaultSumw2();
	gStyle->SetErrorX(0);
	gStyle->SetEndErrorSize(2);
	MnvPlotter plotter;
	plotter.ApplyStyle(PlotUtils::kCCInclusiveHeliumStyle);

	//TLegend *leg1 = NULL;
	TLegend *leg2 = NULL;
	//std::vector<std::pair<TH2*, const char*> > histsPT2D_Xproject=getSystHistsAndOpts(data,  true, *& leg1);
	if (DeBug == true) std::cout << "Starting to getSystHistsAndOpts" << std::endl;
	std::vector< std::pair<TH2*, const char*> > histsPT2D_Yproject = getSystHistsAndOpts_errorBand(data, h_MC, false, *& leg2, pdf_label, true);
	//leg1->SetLineColor(kWhite);
	//leg1->SetFillColor(kWhite);
	leg2->SetLineColor(kWhite);
	leg2->SetFillColor(kWhite);
	if (DeBug == true) std::cout << "Starting to Plot" << std::endl;
	GridCanvas *gcPT_Y = plotYAxis1D(histsPT2D_Yproject, variabley.c_str(), variablex.c_str());

	gcPT_Y->SetYTitle("NEvents");
	gcPT_Y->SetYLimits(0, Ymaxlimit);
	gcPT_Y->SetYLabel_Size(.025);
	gcPT_Y->SetXLabel_Size(.03);
	leg2->SetX1(0.34);
	leg2->SetY1(0.15);
	leg2->SetX2(0.98);
	leg2->SetY2(0.30);
	leg2->SetNColumns(4);
	leg2->SetTextSize(0.02);

	leg2->Draw("SAME");
	//gcPT_Y->Modified();
	std::string TotalTitle(title_char);
	plotter.AddHistoTitle(TotalTitle.c_str(), .035);
	gcPT_Y->Print(pdf_label);

	//GridCanvas* gcPT_X=plotXAxis1D(histsPT2D_Xproject ,variablex.c_str(),variabley.c_str());
	//gcPT=plotXAxis1D(histsPT2D,variablex.c_str(),variabley.c_str(),projx_column,projx_row,projx_pixelx,projx_pixely);

	//gcPT_X->SetYTitle("Fractional Uncertainty");
	//gcPT_X->SetYLimits(0, 0.3);
	//gcPT_X->SetYLabel_Size(.025);
	//gcPT_X->SetXLabel_Size(.03);
	////gcPT->SetLogx(true);

	//leg1->SetX1(0.02);
	//leg1->SetY1(0.92);
	//leg1->SetX2(0.98);
	//leg1->SetY2(1.0);
	//leg1->SetNColumns(3);
	//leg1->SetTextSize(0.025);

	//leg2->Draw("SAME");
	////gcPT_X->Modified();
	//plotter.AddHistoTitle(TotalTitle.c_str(), .035);
	//gcPT_X->Print(pdf_label);

	delete gcPT_Y;
	//cdelete gcPT_X;

}

//=====================================================================
void DrawPanel_MC_dataErrorPlots_ProjectionX(MnvH2D *data, MnvH2D *h_MC, std::string variablex, std::string variabley,
	char *title_char, char *pdf_label, double Ymaxlimit)
{
	myPlotStyle();
	TH1::SetDefaultSumw2();
	gStyle->SetErrorX(0);
	gStyle->SetEndErrorSize(2);
	MnvPlotter plotter;
	plotter.ApplyStyle(PlotUtils::kCCInclusiveHeliumStyle);

	//TLegend *leg1 = NULL;
	TLegend *leg2 = NULL;
	//std::vector<std::pair<TH2*, const char*> > histsPT2D_Xproject=getSystHistsAndOpts(data,  true, *& leg1);
	if (DeBug == true) std::cout << "Starting to getSystHistsAndOpts" << std::endl;
	std::vector< std::pair<TH2*, const char*> > histsPT2D_Yproject = getSystHistsAndOpts_errorBand(data, h_MC, false, *& leg2, pdf_label, true);
	//leg1->SetLineColor(kWhite);
	//leg1->SetFillColor(kWhite);
	leg2->SetLineColor(kWhite);
	leg2->SetFillColor(kWhite);
	if (DeBug == true) std::cout << "Starting to Plot" << std::endl;
	GridCanvas *gcPT_Y = plotYAxis1D(histsPT2D_Yproject, variabley.c_str(), variablex.c_str());

	gcPT_Y->SetYTitle("NEvents");
	gcPT_Y->SetYLimits(0, Ymaxlimit);
	gcPT_Y->SetYLabel_Size(.025);
	gcPT_Y->SetXLabel_Size(.03);
	leg2->SetX1(0.34);
	leg2->SetY1(0.15);
	leg2->SetX2(0.98);
	leg2->SetY2(0.30);
	leg2->SetNColumns(4);
	leg2->SetTextSize(0.02);

	leg2->Draw("SAME");
	//gcPT_Y->Modified();
	std::string TotalTitle(title_char);
	plotter.AddHistoTitle(TotalTitle.c_str(), .035);
	gcPT_Y->Print(pdf_label);

	delete gcPT_Y;
	//cdelete gcPT_X;

}

//=====================================================================
std::vector< std::pair<TH2*, const char*> > getSystHistsAndOpts_errorBand(MnvH2D *data, MnvH2D *h_mc, bool XprojectionTrue, TLegend* &leg, char *pdf, bool print1Dpanels)
	{
		MnvPlotter plotter;
		plotter.ApplyStyle(PlotUtils::kCCInclusiveHeliumStyle);

		// For each bin in the other variable, make a vector of the
		// systematic histograms
		const int nBins = XprojectionTrue ? data->GetXaxis()->GetNbins() : data->GetYaxis()->GetNbins();
		std::vector<std::vector<TH1*>> histsPT;
		histsPT.resize(nBins);

		// Get MnvPlotter to plot all the histograms, and slurp them into histsPT
		for (int i = 0; i < nBins; ++i)
		{
			// First plot the histograms in the dummy canvas...
			TCanvas c;
			MnvH1D *proj = XprojectionTrue ? data->ProjectionY(uniq(), i + 1, i + 1) : data->ProjectionX(uniq(), i + 1, i + 1);
			MnvH1D *projMC = XprojectionTrue ? h_mc->ProjectionY(uniq(), i + 1, i + 1) : h_mc->ProjectionX(uniq(), i + 1, i + 1);
			plotter.DrawDataMCWithErrorBand(proj, projMC, 1.0, "N");
			if (print1Dpanels == true) c.Print(pdf);
			leg = new TLegend(*getPadLegend(&c));
			leg->SetName("MyLegend");
			//    c.Print("can.png");
			std::vector<TH1*> padHists = getPadHists(&c);
			histsPT[i] = padHists;
		}

		// concatenateHists wants a vector of hists for each of the bins of
		// a given systematic. But histsPT is the other way round (the inner
		// vector loops over systematics).  So we have this fiddly loop to
		// make a transposed version of the vector-of-vector

		// It would have been easier to just pass the original
		// vector-of-vector into concatenateHists, and tell it which
		// systematic we wanted, but I've written and debugged this now, so
		// not changing it

		//  First index is systematic, second
		// index is bin
		std::vector<std::vector<TH1*>> histsPT_transpose;
		int nSyst = histsPT[0].size();
		if (DeBug == true) std::cout << "There are " << nSyst << " systematics" << std::endl;
		histsPT_transpose.resize(nSyst);

		for (int iSyst = 0; iSyst < nSyst; ++iSyst)
		{
			for (unsigned int iBin = 0; iBin < histsPT.size(); ++iBin)
			{
				histsPT_transpose[iSyst].push_back(histsPT[iBin][iSyst]);
			}
		}

		//std::cout <<"concatenateHists:Starting Loop"<<std::endl;
		std::vector< std::pair<TH2*, const char*> > histsPT2D;
		// TODO: Figure out why the last systematic is crashing
		for (int iSyst = 0; iSyst < histsPT_transpose.size(); ++iSyst)
		{
			TH2 *h2d = concatenateHists(histsPT_transpose[iSyst], XprojectionTrue ? 2 : 1, data);	// switch 2,1
			// We want to draw all of these histograms as graphs, and exclude
			// the zero bins, to get rid of ROOT artifacts. The "graph0" draw
			// option does that (and I made it safe to pass all graphs)
			histsPT2D.push_back(std::make_pair(h2d, "graph0 l"));
		}

		return histsPT2D;
	}

void Draw_inputTranswarp2DHist_fromPointers(	MnvH2D *h_data,
	MnvH2D *h_data_true,
	MnvH2D *h_mc_reco,
	MnvH2D *h_mc_true,
	bool AreaNorm_todata,
	char *pdf_label,
	char *histotitle,
	char *xaxislabel,
	char *yaxislabel,
	char *zaxislabel_units,
	bool DoBinwidthNorm,
	bool MakeXaxisLOG,
	double Ymax, bool setMaxY, bool doMultipliers, std::vector<double> YMultipliers, std::vector<double> XMultipliers)
{
	std::cout << "Inside::Draw_inputTranswarp2DHist_fromPointers " << std::endl;

	PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);

	myPlotStyle();
	TH1::SetDefaultSumw2();
	gStyle->SetErrorX(0);
	gStyle->SetEndErrorSize(2);

	double y_projectionTxtsize = .03;
	double headroom = 1.7;

	TLegend *leg = new TLegend(0.8, 0.01, 0.99, 0.30);

	leg->SetFillStyle(0);
	leg->SetBorderSize(0);
	leg->SetTextSize(0.025);
	leg->SetNColumns(1);

	TH2D *h_Data = new TH2D(h_data->GetCVHistoWithStatError());
	TH2D *h_Data_true = new TH2D(h_data_true->GetCVHistoWithStatError());
	TH2D *h_MC_reco = new TH2D(h_mc_reco->GetCVHistoWithStatError());
	TH2D *h_MC_true = new TH2D(h_mc_true->GetCVHistoWithStatError());

	h_Data->SetLineColor(kBlack);
	h_Data->SetLineWidth(2);

	h_Data_true->SetLineColor(kBlue);
	h_Data_true->SetLineWidth(2);

	h_MC_reco->SetLineColor(kGreen);
	h_MC_reco->SetLineWidth(2);
	h_MC_true->SetLineColor(kRed);

	h_MC_true->SetLineWidth(2);

	h_Data_true->SetLineStyle(2);
	h_MC_true->SetLineStyle(2);

	h_Data->SetLineStyle(3);
	h_MC_reco->SetLineStyle(4);

	leg->AddEntry(h_Data, "h_data", "l");
	leg->AddEntry(h_Data_true, "h_data_true", "l");
	leg->AddEntry(h_MC_reco, "h_MC_reco", "l");
	leg->AddEntry(h_MC_true, "h_MC_true", "l");

	string TotalTitle = string(histotitle);

	int N_Data = h_Data->GetNbinsX();
	int N_Data_TRUE = h_Data_true->GetNbinsX();
	int N_MC_RECO = h_MC_reco->GetNbinsX();
	int N_MC_TRUE = h_MC_true->GetNbinsX();

	if (N_Data != N_Data_TRUE || N_Data != N_MC_RECO || N_Data != N_MC_TRUE)
	{
		std::cout << "The Bins are different sizes for: Draw_inputTranswarp2DHist_fromPointers" << std::endl;
		std::cout << "with Xaxis = " << xaxislabel << std::endl;
		std::cout << "N_Data = " << N_Data << std::endl;
		std::cout << "N_Data_TRUE = " << N_Data_TRUE << std::endl;
		std::cout << "N_MC_RECO = " << N_MC_RECO << std::endl;
		std::cout << "N_MC_TRUE = " << N_MC_TRUE << std::endl;
		assert(false);
	}

	if (AreaNorm_todata == true)
	{
		double Area_Data = h_Data->Integral();
		double Area_Data_TRUE = h_Data_true->Integral();
		double Area_MC_RECO = h_MC_reco->Integral();
		double Area_MC_TRUE = h_MC_true->Integral();

		h_Data_true->Scale(Area_Data / Area_Data_TRUE);
		h_MC_reco->Scale(Area_Data / Area_MC_RECO);
		h_MC_true->Scale(Area_Data / Area_MC_TRUE);
	}

	char ztitle[100];

	if (MakeXaxisLOG == true)
	{
		gPad->SetLogx();
	}

	if (DoBinwidthNorm == true)
	{
		h_Data->Scale(1.0, "width");
		h_Data_true->Scale(1.0, "width");
		h_MC_reco->Scale(1.0, "width");
		h_MC_true->Scale(1.0, "width");

		if (setMaxY == false) Ymax = 1.85* maximum(h_Data->GetMaximum(), h_Data_true->GetMaximum(), h_MC_true->GetMaximum());

		sprintf(ztitle, "NEvents /[%s] ", zaxislabel_units);
		if (AreaNorm_todata == true)
		{
			sprintf(ztitle, "NEvents[AreaNorm to Data] /[%s] ", zaxislabel_units);
		}
	}
	else
	{
		sprintf(ztitle, "NEvents");
	}

	std::vector< std::pair<TH2*, const char*> > histAndOpts;

	histAndOpts.push_back(std::make_pair(h_Data, "hist"));
	histAndOpts.push_back(std::make_pair(h_Data_true, "hist"));
	histAndOpts.push_back(std::make_pair(h_MC_reco, "hist"));
	histAndOpts.push_back(std::make_pair(h_MC_true, "hist"));
	GridCanvas *gc_y = plotYAxis1D(histAndOpts, xaxislabel, yaxislabel, doMultipliers ? &YMultipliers[0] : NULL, y_projectionTxtsize, DoBinwidthNorm);

	gc_y->SetYLabel_Size(.025);
	gc_y->SetXLabel_Size(.03);
	double MaxY = gc_y->GetPadMax();
	std::cout << "MaxY = " << MaxY << std::endl;
	if (setMaxY == false) gc_y->SetYLimits(0, MaxY *headroom);
	else gc_y->SetYLimits(0, MaxY);
	gc_y->SetYTitle(ztitle);
	gc_y->SetGridx();
	if (MakeXaxisLOG == true) gc_y->SetLogx(1);
	char total_title[1024];
	sprintf(total_title, " %s[Yproj]", histotitle);

	mnvPlotter.AddHistoTitle(total_title, .035);
	if (MakeXaxisLOG == true) gc_y->SetLogx(1);
	gc_y->Modified();
	leg->Draw("SAME");
	gc_y->Print(pdf_label);

	GridCanvas *gc_x = plotXAxis1D(histAndOpts, yaxislabel, xaxislabel, doMultipliers ? &XMultipliers[0] : NULL, DoBinwidthNorm);	//, x_projectionTxtsize
	// Set the y range manually. Can also use gc3->Remax() to guess automatically
	gc_x->SetYLabel_Size(.025);
	gc_x->SetXLabel_Size(.03);
	double MaxX = gc_x->GetPadMax();
	gc_x->SetYLimits(0, MaxX *headroom);

	gc_x->SetYTitle(ztitle);
	//if(MakeXaxisLOG==true) gc_x->SetLogx(0);
	sprintf(total_title, " %s[Xproj]", histotitle);
	mnvPlotter.AddHistoTitle(total_title, .038);
	//gc_x->SetYTitle(yaxisUNITS);
	if (MakeXaxisLOG == true) gc_x->SetLogx(1);
	gc_x->SetGridx();
	gc_x->Modified();
	leg->Draw("SAME");
	gc_x->Print(pdf_label);

	delete gc_x;
	delete gc_y;

}	//END of Function
void PlotDataStackedMC2D_ProjY(PlotUtils::MnvH2D *data, PlotUtils::MnvH2D *mc, const TObjArray *stack,
		std::vector<int> fillColors, bool DoBinwidthNorm,
		char *pdf_label, char *histotitle, char *xaxislabel,
		char *yaxislabel, char *zaxislabel_units,
		double Ymax, bool setMaxY, bool doMultipliers,
		std::vector<double> YMultipliers,
		bool statPlusSysDATA, bool statPlusSysMC,
		bool do_bin_width_norm, bool useHistTitles)
{
	PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
	PlotUtils::MnvH2D *dataHist = data->Clone("tmpData");
	TH2 *dataHist_clone = data->Clone("dataHist_clone");
	PlotUtils::MnvH2D *mcHist_clone = mc->Clone("mcHist_clone");
	mnvPlotter.mc_error_style_stack = 3001;
	mnvPlotter.mc_error_color_stack = kRed;

	int nVars = stack->GetEntries();
	int nbins_X = data->GetNbinsX();
	int nbins_Y = data->GetNbinsY();
	std::cout << "The NEntries for TObjArray: " << nVars << std::endl;
	int nbins_X_mc = mcHist_clone->GetNbinsX();
	int nbins_Y_mc = mcHist_clone->GetNbinsY();

	TLegend *leg = new TLegend(0.43, 0.1, 0.98, 0.3);

	leg->SetFillStyle(0);
	leg->SetBorderSize(0);
	leg->SetTextSize(0.025);
	leg->SetNColumns(3);

	double maxmax = 1.25 *dataHist->GetMaximum();
	int grid_x;
	int grid_y;
	int Nbins;
	std::string xaxislabel_string(xaxislabel);

	grid_x = sqrt(nbins_X) + 1;
	grid_y = nbins_X / (grid_x - 1);
	Nbins = dataHist->GetNbinsX();

	if (DeBug == true) std::cout << nbins_X - grid_x * grid_y << std::endl;
	if (DeBug == true) std::cout << "Plotting plotYAxis1D with a grid of " << nbins_X << "\t" << nbins_Y << "\t" << grid_x << "\t" << grid_y << std::endl;

	std::vector<int> bins;	// = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	GridCanvas *gc = new GridCanvas(uniq(), grid_x, grid_y, 800, 550);
	TCanvas cE("c1", "c1");
	gc->SetRightMargin(0.01);
	gc->SetLeftMargin(0.1);
	gc->ResetPads();

	for (int i = 1; i <= Nbins; ++i)
	{
		bins.push_back(i);

		TObjArray *mcprojyArr = new TObjArray();
		mcprojyArr->SetOwner(kTRUE);
		PlotUtils::MnvH1D *hdatayproj =
			dataHist->ProjectionY(uniq(), i, i)->Clone();

		PlotUtils::MnvH1D *hMCyproj =
			mcHist_clone->ProjectionY(uniq(), i, i)->Clone();

		hdatayproj->Scale(1., "width");
		hMCyproj->Scale(1., "width");

		hMCyproj->SetMaximum(maxmax);
		hdatayproj->SetMaximum(maxmax);

		if (doMultipliers == true)
		{
			hdatayproj->Scale(YMultipliers.at(i - 1));
			hMCyproj->Scale(YMultipliers.at(i - 1));
		}

		if (i == 1)
		{
			if (statPlusSysDATA == true)
			{
				leg->AddEntry(hdatayproj, "Data[Stat+Sys]", "lpe");
			}
			else
			{
				leg->AddEntry(hdatayproj, "Data[Stat]", "lpe");
			}

			if (statPlusSysMC == true)
			{
				hMCyproj->SetFillColorAlpha(mnvPlotter.mc_error_color_stack, 0.55);
				hMCyproj->SetFillStyle(mnvPlotter.mc_error_style_stack);
				hMCyproj->SetMarkerStyle(0);
				hMCyproj->SetLineWidth(0);
				leg->AddEntry(hMCyproj, "Error Band[Stat+Sys]", "f");
			}
			else leg->AddEntry(hMCyproj, "MINERvA v1[Stat]", "l");
		}

		for (int iHist = 0; iHist < nVars; ++iHist)
		{
			PlotUtils::MnvH2D *mcHist_stack = (PlotUtils::MnvH2D *) stack->At(iHist)->Clone("mcHist_stack");
			//int ndf;
			std::string words = mcHist_stack->GetTitle();
			std::cout << "iHist  = " << iHist << " words = " << words << std::endl;

			PlotUtils::MnvH1D *mcHist_stack_ProjectionY = mcHist_stack->ProjectionY(uniq(), i, i)->Clone();
			mcHist_stack_ProjectionY->Scale(1., "width");
			if (doMultipliers == true)
			{
				mcHist_stack_ProjectionY->Scale(YMultipliers.at(i - 1));
			}

			mcHist_stack_ProjectionY->SetTitle(words.c_str());
			mcHist_stack_ProjectionY->SetXTitle("");

			mcHist_stack_ProjectionY->SetFillColor(fillColors.at(iHist));
			mcHist_stack_ProjectionY->SetLineWidth(0);

			if (i == 1)
			{
				char words_char[words.length() + 1];
				strcpy(words_char, words.c_str());
				leg->AddEntry(mcHist_stack_ProjectionY, words_char, "f");
			}

			mcprojyArr->Add(mcHist_stack_ProjectionY);
		}

		gc->cd(i);
		mnvPlotter.axis_label_size = 0.02;
		mnvPlotter.legend_text_size = 0.02;
		mnvPlotter.data_marker_size = 0.3;
		const Int_t mcFillStyle = 1001;
		const Double_t mcScale = 1.0;
		//const std::string& legPos = "N";
		mnvPlotter.axis_maximum = maxmax;
		//mnvPlotter.mc_error_color_stack=kRed;
		//mnvPlotter.mc_error_color_stack=kRed;
		hMCyproj->SetLineWidth(3);
		hMCyproj->SetLineColor(2);
		mnvPlotter.draw_normalized_to_bin_width = false;
		mnvPlotter.DrawDataStackedMCWithErrorBand(hdatayproj, hMCyproj, mcprojyArr, fillColors, useHistTitles, statPlusSysDATA, statPlusSysMC, mcFillStyle, mcScale, "N");
		//mnvPlotter.DrawDataStackedMC(hdatayproj, mcprojyArr,
		//&fillColors[0], 1.0, legPos, "Data",  -1);

		drawBinRange(dataHist_clone, 1, i, xaxislabel, ".1f", false);
		if (i == 1) mnvPlotter.WritePreliminary("TL", .015, -.01, -0.05, false);
		if (doMultipliers && YMultipliers.at(i - 1) != 1)
		{
			auto pad = gc->cd(i);
			TLatex *la2 = new TLatex(1 - pad->GetRightMargin() - 0.02,
				1 - pad->GetTopMargin() - 0.08,
				TString::Format("#times %.1f", YMultipliers.at(i - 1)));
			la2->SetTextAlign(33);	// top right
			la2->SetNDC();
			la2->SetTextFont(42);
			la2->SetTextSize(0.03);
			la2->Draw();
		}
	}	/// End of Loop

	// gc->DrawBinRanges(dataHist, 2, bins, dataHist->GetYaxis()->GetTitle(), binCenter, .02);
	gc->SetYLabel_Size(.015);
	gc->SetXLabel_Size(.02);
	double MaxY = gc->GetPadMax();
	if (setMaxY == false) gc->SetYLimits(0, MaxY *1.35);
	else
	{
		gc->SetYLimits(0, Ymax);
	}

	gc->SetXTitle(yaxislabel);
	gc->SetYTitleSize(15);
	gc->SetYTitle(zaxislabel_units);
	gc->SetHistTexts();
	leg->Draw("SAME");
	mnvPlotter.AddHistoTitle(histotitle, .04);
	gc->Modified();
	gc->Print(pdf_label);

	delete gc;

}

//////////////////////////////////////////////////
void PlotDataStackedMC2D_ProjY(PlotUtils::MnvH2D *data, TObjArray stack_input,
	std::vector<int> fillColors,
	char *pdf_label, char *histotitle, char *xaxislabel,
	char *yaxislabel, char *zaxislabel_units,
	double Ymax, bool setMaxY, bool doMultipliers,
	std::vector<double> YMultipliers,
	bool do_bin_width_norm, double text_size)
{
	PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
	PlotUtils::MnvH2D *dataHist = data->Clone("tmpData");
	TH2 *dataHist_clone = data->Clone("dataHist_clone");
	//TObjArray *stack =  &stack_input;
	TObjArray *stack = (TObjArray*) stack_input.Clone();
	stack->SetOwner(kTRUE);
	int nVars = stack->GetEntries();
	int nbins_X = data->GetNbinsX();
	int nbins_Y = data->GetNbinsY();
	std::cout << "The NEntries for TObjArray: " << nVars << std::endl;

	TLegend *leg = new TLegend(0.43, 0.1, 0.98, 0.3);

	leg->SetFillStyle(0);
	leg->SetBorderSize(0);
	leg->SetTextSize(0.025);
	leg->SetNColumns(3);

	//std::cout<<"nbins_X = " << nbins_X << std::endl;
	//std::cout<<"nbins_Y = " << nbins_Y << std::endl;
	//std::cout<<"nbins_X_mc = " << nbins_X_mc << std::endl;
	//std::cout<<"nbins_Y_mc = " << nbins_Y_mc << std::endl;

	double maxmax = 1.25* GetMaxFromProjectionY(dataHist, do_bin_width_norm);

	int grid_x;
	int grid_y;
	int Nbins;
	std::string xaxislabel_string(xaxislabel);

	grid_x = sqrt(nbins_X) + 1;
	grid_y = nbins_X / (grid_x - 1);
	Nbins = dataHist->GetNbinsX();

	if (DeBug == true) std::cout << nbins_X - grid_x * grid_y << std::endl;
	if (DeBug == true) std::cout << "Plotting plotYAxis1D with a grid of " << nbins_X << "\t" << nbins_Y << "\t" << grid_x << "\t" << grid_y << std::endl;

	GridCanvas *gc = new GridCanvas(uniq(), grid_x, grid_y, 800, 550);
	TCanvas cE("c1", "c1");
	gc->SetRightMargin(0.01);
	gc->SetLeftMargin(0.1);
	gc->ResetPads();

	for (int i = 1; i <= Nbins; ++i)
	{
		TObjArray *mcprojyArr = new TObjArray();
		mcprojyArr->SetOwner(kTRUE);

		PlotUtils::MnvH1D *hdatayproj =
			dataHist->ProjectionY(uniq(), i, i)->Clone();

		if (do_bin_width_norm == true) hdatayproj->Scale(1., "width");
		if (doMultipliers == true) hdatayproj->Scale(YMultipliers.at(i - 1));

		hdatayproj->SetMaximum(maxmax);
		if (i == 1) leg->AddEntry(hdatayproj, "Data[Stat]", "lpe");

		for (int iHist = 0; iHist < nVars; ++iHist)
		{
			PlotUtils::MnvH2D *mcHist_stack = (PlotUtils::MnvH2D *) stack->At(iHist)->Clone("mcHist_stack");
			//int ndf;
			std::string words = mcHist_stack->GetTitle();
			std::cout << "iHist  = " << iHist << " words = " << words << std::endl;

			PlotUtils::MnvH1D *mcHist_stack_ProjectionY = mcHist_stack->ProjectionY(uniq(), i, i)->Clone();
			if (do_bin_width_norm == true) mcHist_stack_ProjectionY->Scale(1., "width");
			if (doMultipliers == true) mcHist_stack_ProjectionY->Scale(YMultipliers.at(i - 1));

			mcHist_stack_ProjectionY->SetTitle(words.c_str());
			mcHist_stack_ProjectionY->SetXTitle("");

			mcHist_stack_ProjectionY->SetFillColor(fillColors.at(iHist));
			mcHist_stack_ProjectionY->SetLineWidth(0);

			if (i == 1)
			{
				char words_char[words.length() + 1];
				strcpy(words_char, words.c_str());
				leg->AddEntry(mcHist_stack_ProjectionY, words_char, "f");
			}

			mcprojyArr->Add(mcHist_stack_ProjectionY);
		}

		gc->cd(i);
		mnvPlotter.axis_label_size = 0.02;
		mnvPlotter.legend_text_size = 0.02;
		mnvPlotter.data_marker_size = 0.3;
		mnvPlotter.axis_maximum = maxmax;
		mnvPlotter.draw_normalized_to_bin_width = false;
		mnvPlotter.mc_line_width = 0;
		mnvPlotter.DrawDataStackedMC(hdatayproj, mcprojyArr);

		//drawBinRange(dataHist_clone, 1, i, xaxislabel, ".1f", false);
		drawBinRange(dataHist, 1, i, xaxislabel, text_size, ".2f", false);

		if (doMultipliers && YMultipliers.at(i - 1) != 1)
		{
			auto pad = gc->cd(i);
			TLatex *la2 = new TLatex(1 - pad->GetRightMargin() - 0.02,
				1 - pad->GetTopMargin() - 0.08,
				TString::Format("#times %.1f", YMultipliers.at(i - 1)));
			la2->SetTextAlign(33);	// top right
			la2->SetNDC();
			la2->SetTextFont(42);
			la2->SetTextSize(0.03);
			la2->Draw();
		}

		//mcprojyArr->Clear();
	}	/// End of Loop

	gc->SetYLabel_Size(.015);
	gc->SetXLabel_Size(.02);
	double MaxY = gc->GetPadMax();
	if (setMaxY == false) gc->SetYLimits(0, MaxY *1.35);
	else
	{
		gc->SetYLimits(0, Ymax);
	}

	gc->SetXTitle(yaxislabel);
	gc->SetYTitleSize(25);
	gc->SetYTitle(zaxislabel_units);
	gc->SetHistTexts();
	leg->Draw("SAME");
	mnvPlotter.AddHistoTitle(histotitle, .04);
	gc->Modified();
	gc->Print(pdf_label);
	//leg->Clear();
	mnvPlotter.CleanTmp();
	stack->Delete();
	delete gc;

}

//////////////////////////////////////////////////
void PlotDataMC_ErrorBand2D_ProjY(PlotUtils::MnvH2D *data, PlotUtils::MnvH2D *mc,
	char *pdf_label, char *histotitle, char *xaxislabel,
	char *yaxislabel, char *zaxislabel_units,
	double Ymax, bool setMaxY, bool doMultipliers,
	std::vector<double> XMultipliers,
	bool statPlusSysDATA, bool statPlusSysMC,
	bool do_bin_width_norm, bool useHistTitles, double text_size)
{
	PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
	PlotUtils::MnvH2D *dataHist = data->Clone("dataHist");
	PlotUtils::MnvH2D *mcHist_clone = mc->Clone("mcHist_clone");

	int NDF_2d;
	double chi2_2d = mnvPlotter.Chi2DataMC(dataHist, mcHist_clone, NDF_2d);

	int nbins_X = data->GetNbinsX();
	int nbins_Y = data->GetNbinsY();

	double MinX = mcHist_clone->GetYaxis()->GetBinLowEdge(1);
	double MaxX = 1.2 *mcHist_clone->GetYaxis()->GetBinLowEdge(nbins_Y);

	int nbins_X_mc = mcHist_clone->GetNbinsX();
	int nbins_Y_mc = mcHist_clone->GetNbinsY();

	//double maxmax = 1.2 *dataHist->GetMaximum();

	double maxmax = 1.4* GetMaxFromProjectionY(dataHist, mcHist_clone, do_bin_width_norm);
	int grid_x;
	int grid_y;
	int Nbins;
	std::string xaxislabel_string(xaxislabel);

	grid_x = sqrt(nbins_X) + 1;
	grid_y = nbins_X / (grid_x - 1);
	Nbins = dataHist->GetNbinsX();
	if (nbins_X_mc != Nbins)
	{
		std::cout << "MC and Data have different nBinX: PlotDataMC_ErrorBand2D_ProjY" << std::endl;
	}

	if (DeBug == true) std::cout << nbins_X - grid_x * grid_y << std::endl;
	if (DeBug == true) std::cout << "Plotting plotYAxis1D with a grid of " << nbins_X << "\t" << nbins_Y << "\t" << grid_x << "\t" << grid_y << std::endl;
	TLegend * leg;
	if (Nbins == 5 || Nbins == 11)
	{
		leg = new TLegend(0.78, 0.1, 0.98, 0.35);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextSize(0.015);
		leg->SetNColumns(1);
	}
	else
	{
		leg = new TLegend(0.43, 0.1, 0.98, 0.3);

		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextSize(0.025);
		leg->SetNColumns(3);
	}

	GridCanvas *gc = new GridCanvas(uniq(), grid_x, grid_y, 800, 500);
	TCanvas cE("c1", "c1");
	gc->SetRightMargin(0.06);
	gc->SetLeftMargin(0.06);
	gc->ResetPads();

	for (int i = 1; i <= Nbins; ++i)
	{
		PlotUtils::MnvH1D *hdatayproj =
			dataHist->ProjectionY(uniq(), i, i)->Clone();

		PlotUtils::MnvH1D *hMCyproj =
			mcHist_clone->ProjectionY(uniq(), i, i)->Clone();

		hMCyproj->SetMaximum(maxmax);
		hdatayproj->SetMaximum(maxmax);

		if (do_bin_width_norm == true)
		{
			hdatayproj->Scale(1., "width");
			hMCyproj->Scale(1., "width");
		}

		if (doMultipliers == true)
		{
			hdatayproj->Scale(XMultipliers.at(i - 1));
			hMCyproj->Scale(XMultipliers.at(i - 1));
		}

		if (i == 1)
		{
			if (statPlusSysDATA == true)
			{
				leg->AddEntry(hdatayproj, "Data[Stat+Sys]", "lpe");
			}
			else
			{
				leg->AddEntry(hdatayproj, "Data[Stat]", "lpe");
			}

			if (statPlusSysMC == true)
			{
				hMCyproj->SetMarkerStyle(0);
				hMCyproj->SetLineColor(mnvPlotter.mc_color);
				hMCyproj->SetLineWidth(mnvPlotter.mc_line_width);
				hMCyproj->SetLineStyle(mnvPlotter.mc_line_style);
				hMCyproj->SetFillStyle(mnvPlotter.mc_error_style);
				leg->AddEntry(hMCyproj, "Error Band [Stat+Sys]", "lf");
			}
			else leg->AddEntry(hMCyproj, "MINERvA v1[Stat]", "l");
			hMCyproj->SetFillColorAlpha(mnvPlotter.mc_error_color, 0.65);
			hMCyproj->SetFillStyle(mnvPlotter.mc_error_style);
			hMCyproj->SetMarkerStyle(0);
			hMCyproj->SetLineWidth(0);
		}

		gc->cd(i);
		mnvPlotter.axis_label_size = 0.02;
		mnvPlotter.legend_text_size = 0.02;
		mnvPlotter.data_marker_size = 0.3;
		const Double_t mcScale = 1.0;
		mnvPlotter.axis_maximum = maxmax;
		//mnvPlotter.mc_error_color_stack=kRed;
		//mnvPlotter.mc_error_color_stack=kRed;
		hMCyproj->SetLineWidth(2);
		hMCyproj->SetLineColor(2);
		mnvPlotter.draw_normalized_to_bin_width = false;
		const bool covAreaNormalize = false;
		const bool statPlusSys = false;
		const bool isSmooth = false;

		mnvPlotter.DrawDataMCWithErrorBand(			hdatayproj,
			hMCyproj,
			1.0,
			"N",
			false,	//default is to use Data/MC/Background
			NULL,
			NULL,
			covAreaNormalize,
			statPlusSys,
			isSmooth
	);

		//drawBinRange(dataHist_clone, 2, i, yaxislabel, ".2f", false);
		drawBinRange(dataHist, 1, i, yaxislabel, text_size, ".2f", false);
		if (i == 1) mnvPlotter.WritePreliminary("TL", .015, -.01, -.115, false);
		if (doMultipliers && XMultipliers.at(i - 1) != 1)
		{
			auto pad = gc->cd(i);
			TLatex *la2 = new TLatex(1 - pad->GetRightMargin() - 0.03,
				1 - pad->GetTopMargin() - 0.04,
				TString::Format("#times %.1f", XMultipliers.at(i - 1)));
			la2->SetTextAlign(33);	// top right
			la2->SetNDC();
			la2->SetTextFont(42);
			la2->SetTextSize(0.025);
			la2->Draw();
		}

		int ndf_panel;
		double Chisqt_panel = mnvPlotter.Chi2DataMC(hdatayproj, hMCyproj, ndf_panel);
		TLatex *Chisqt_latex = new TLatex(gPad->GetLeftMargin() + .01,
			1 - gPad->GetTopMargin() - 0.035,
			TString::Format("#chi^{2}/ndf = %.1f / %i = %.1f", Chisqt_panel, ndf_panel, Chisqt_panel / ndf_panel));
		Chisqt_latex->SetTextAlign(13);	// top left
		Chisqt_latex->SetNDC();
		Chisqt_latex->SetTextFont(42);
		Chisqt_latex->SetTextSize(text_size *.8);
		Chisqt_latex->SetTextColor(kBlue);
		Chisqt_latex->Draw();
	}	/// End of Loop
	char chi_label[1024];

	sprintf(chi_label, "#chi^{2}/ndf = %.1f / %i = %.1f", chi2_2d, NDF_2d, chi2_2d / NDF_2d);
	leg->AddEntry((TObject*) 0, chi_label, "");

	gc->SetYLabel_Size(.015);
	gc->SetXLabel_Size(.02);
	double MaxY = gc->GetPadMax();
	if (setMaxY == false) gc->SetYLimits(0, MaxY *1.25);
	else
	{
		gc->SetYLimits(0, Ymax);
	}

	gc->SetXLimits(MinX, MaxX);
	gc->SetXTitle(xaxislabel);
	gc->SetYTitleSize(10);
	gc->SetYTitle(zaxislabel_units);
	gc->SetHistTexts();
	leg->Draw("SAME");
	mnvPlotter.AddHistoTitle(histotitle, .04);
	gc->Modified();
	gc->ResetPads();
	gc->Print(pdf_label);
	delete gc;

}

////////////////////////////////////////////////
void PlotDataMC_ErrorBand2D_ProjY(PlotUtils::MnvH2D *data, PlotUtils::MnvH2D *mc,
	PlotUtils::MnvH2D *data_BG_input, PlotUtils::MnvH2D *mc_BG_input,
	char *pdf_label, char *histotitle, char *xaxislabel,
	char *yaxislabel, char *zaxislabel_units,
	double Ymax, bool setMaxY, bool doMultipliers,
	std::vector<double> XMultipliers,
	bool statPlusSysDATA, bool statPlusSysMC,
	bool do_bin_width_norm, bool useHistTitles, double text_size)
{
	PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
	PlotUtils::MnvH2D *dataHist = data->Clone("dataHist");
	PlotUtils::MnvH2D *mcHist_clone = mc->Clone("mcHist_clone");

	PlotUtils::MnvH2D *dataHistBG = data_BG_input->Clone("dataHistBG");
	PlotUtils::MnvH2D *mcHistBG = mc_BG_input->Clone("mcHistBG");
	mnvPlotter.data_bkgd_style = 22;

	int NDF_2d;
	double chi2_2d = mnvPlotter.Chi2DataMC(dataHist, mcHist_clone, NDF_2d);

	int nbins_X = data->GetNbinsX();
	int nbins_Y = data->GetNbinsY();

	double MinX = mcHist_clone->GetYaxis()->GetBinLowEdge(1);
	double MaxX = 1.2 *mcHist_clone->GetYaxis()->GetBinLowEdge(nbins_Y);

	int nbins_X_mc = mcHist_clone->GetNbinsX();
	int nbins_Y_mc = mcHist_clone->GetNbinsY();

	//double maxmax = 1.2 *dataHist->GetMaximum();

	double maxmax = 1.4* GetMaxFromProjectionY(dataHist, mcHist_clone, do_bin_width_norm);
	int grid_x;
	int grid_y;
	int Nbins;
	std::string xaxislabel_string(xaxislabel);

	grid_x = sqrt(nbins_X) + 1;
	grid_y = nbins_X / (grid_x - 1);
	Nbins = dataHist->GetNbinsX();
	if (nbins_X_mc != Nbins)
	{
		std::cout << "MC and Data have different nBinX: PlotDataMC_ErrorBand2D_ProjY" << std::endl;
	}

	if (DeBug == true) std::cout << nbins_X - grid_x * grid_y << std::endl;
	if (DeBug == true) std::cout << "Plotting plotYAxis1D with a grid of " << nbins_X << "\t" << nbins_Y << "\t" << grid_x << "\t" << grid_y << std::endl;
	TLegend * leg;

	if (Nbins == 5 || Nbins == 11)
	{
		leg = new TLegend(0.75, 0.1, 0.98, 0.35);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextSize(0.02);
		leg->SetNColumns(1);
	}
	else
	{
		leg = new TLegend(0.43, 0.1, 0.98, 0.3);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextSize(0.02);
		leg->SetNColumns(3);
	}

	GridCanvas *gc = new GridCanvas(uniq(), grid_x, grid_y, 800, 500);
	TCanvas cE("c1", "c1");
	gc->SetRightMargin(0.06);
	gc->SetLeftMargin(0.06);
	gc->ResetPads();

	for (int i = 1; i <= Nbins; ++i)
	{
		PlotUtils::MnvH1D *hdatayproj =
			dataHist->ProjectionY(uniq(), i, i)->Clone();

		PlotUtils::MnvH1D *hMCyproj =
			mcHist_clone->ProjectionY(uniq(), i, i)->Clone();

		PlotUtils::MnvH1D *hdataBGyproj =
			dataHistBG->ProjectionY(uniq(), i, i)->Clone();

		PlotUtils::MnvH1D *hMCBGyproj =
			mcHistBG->ProjectionY(uniq(), i, i)->Clone();

		hMCyproj->SetMaximum(maxmax);
		hdatayproj->SetMaximum(maxmax);

		if (do_bin_width_norm == true)
		{
			hdatayproj->Scale(1., "width");
			hMCyproj->Scale(1., "width");
			hdataBGyproj->Scale(1., "width");
			hMCBGyproj->Scale(1., "width");
		}

		if (doMultipliers == true)
		{
			hdatayproj->Scale(XMultipliers.at(i - 1));
			hMCyproj->Scale(XMultipliers.at(i - 1));
			hdataBGyproj->Scale(XMultipliers.at(i - 1));
			hMCBGyproj->Scale(XMultipliers.at(i - 1));
		}

		if (i == 1)
		{
			hdataBGyproj->SetMarkerColor(mnvPlotter.data_bkgd_color);
			hdataBGyproj->SetMarkerStyle(mnvPlotter.data_bkgd_style);
			hdataBGyproj->SetMarkerSize(mnvPlotter.data_bkgd_size *.7);

			if (statPlusSysDATA == true)
			{
				leg->AddEntry(hdatayproj, "Data(^{4}He Full)[Stat+Sys]", "lpe");
				leg->AddEntry(hdataBGyproj, "Data (Empty)", "p");
			}
			else
			{
				leg->AddEntry(hdatayproj, "Data(^{4}He Full)[Stat]", "lpe");
				leg->AddEntry(hdataBGyproj, "Data (Empty)", "p");
			}

			if (statPlusSysMC == true)
			{
				hMCyproj->SetMarkerStyle(0);
				hMCyproj->SetLineColor(mnvPlotter.mc_color);
				hMCyproj->SetLineWidth(mnvPlotter.mc_line_width);
				hMCyproj->SetLineStyle(mnvPlotter.mc_line_style);
				hMCyproj->SetFillStyle(mnvPlotter.mc_error_style);
				leg->AddEntry(hMCyproj, "Error Band [Stat+Sys]", "lf");
			}
			else leg->AddEntry(hMCyproj, "MINERvA v1 (^{4}He Full)[Stat]", "l");

			hMCyproj->SetFillColorAlpha(mnvPlotter.mc_error_color, 0.65);
			hMCyproj->SetFillStyle(mnvPlotter.mc_error_style);
			hMCyproj->SetMarkerStyle(0);
			hMCyproj->SetLineWidth(0);

			hMCBGyproj->SetFillColor(mnvPlotter.mc_bkgd_color);
			hMCBGyproj->SetFillStyle(mnvPlotter.mc_bkgd_style);
			hMCBGyproj->SetLineColor(mnvPlotter.mc_bkgd_line_color);
			hMCBGyproj->SetLineWidth(mnvPlotter.mc_bkgd_width);
			leg->AddEntry(hMCBGyproj, "MINERvA v1 Empty", "f");
		}

		gc->cd(i);
		mnvPlotter.axis_label_size = 0.02;
		mnvPlotter.legend_text_size = 0.02;
		mnvPlotter.data_marker_size = 0.3;
		const Double_t mcScale = 1.0;
		mnvPlotter.axis_maximum = maxmax;
		//mnvPlotter.mc_error_color_stack=kRed;
		//mnvPlotter.mc_error_color_stack=kRed;
		hMCyproj->SetLineWidth(2);
		hMCyproj->SetLineColor(2);
		mnvPlotter.draw_normalized_to_bin_width = false;
		const bool covAreaNormalize = false;
		const bool statPlusSys = false;
		const bool isSmooth = false;

		mnvPlotter.DrawDataMCWithErrorBand(			hdatayproj,
			hMCyproj,
			1.0,
			"N",
			false,	//default is to use Data/MC/Background
			hdataBGyproj,
			hMCBGyproj,
			covAreaNormalize,
			statPlusSys,
			isSmooth
	);

		//drawBinRange(dataHist_clone, 2, i, yaxislabel, ".2f", false);
		drawBinRange(dataHist, 1, i, yaxislabel, text_size, ".2f", false);
		if (i == 1) mnvPlotter.WritePreliminary("TL", .015, -.01, -.115, false);
		if (doMultipliers && XMultipliers.at(i - 1) != 1)
		{
			auto pad = gc->cd(i);
			TLatex *la2 = new TLatex(1 - pad->GetRightMargin() - 0.03,
				1 - pad->GetTopMargin() - 0.04,
				TString::Format("#times %.1f", XMultipliers.at(i - 1)));
			la2->SetTextAlign(33);	// top right
			la2->SetNDC();
			la2->SetTextFont(42);
			la2->SetTextSize(0.025);
			la2->Draw();
		}

		int ndf_panel;
		double Chisqt_panel = mnvPlotter.Chi2DataMC(hdatayproj, hMCyproj, ndf_panel);
		TLatex *Chisqt_latex = new TLatex(gPad->GetLeftMargin() + .01,
			1 - gPad->GetTopMargin() - 0.035,
			TString::Format("#chi^{2}/ndf = %.1f / %i = %.1f", Chisqt_panel, ndf_panel, Chisqt_panel / ndf_panel));
		Chisqt_latex->SetTextAlign(13);	// top left
		Chisqt_latex->SetNDC();
		Chisqt_latex->SetTextFont(42);
		Chisqt_latex->SetTextSize(text_size *.8);
		Chisqt_latex->SetTextColor(kBlue);
		Chisqt_latex->Draw();
	}	/// End of Loop
	char chi_label[1024];

	sprintf(chi_label, "#chi^{2}/ndf = %.1f / %i = %.1f", chi2_2d, NDF_2d, chi2_2d / NDF_2d);
	leg->AddEntry((TObject*) 0, chi_label, "");

	gc->SetYLabel_Size(.015);
	gc->SetXLabel_Size(.02);
	double MaxY = gc->GetPadMax();
	if (setMaxY == false) gc->SetYLimits(0, MaxY *1.25);
	else
	{
		gc->SetYLimits(0, Ymax);
	}

	gc->SetXLimits(MinX, MaxX);
	gc->SetXTitle(xaxislabel);
	gc->SetYTitleSize(25);
	gc->SetYTitle(zaxislabel_units);
	gc->SetHistTexts();
	leg->Draw("SAME");
	mnvPlotter.AddHistoTitle(histotitle, .04);
	gc->Modified();
	gc->ResetPads();
	gc->Print(pdf_label);
	delete gc;

}

//////////////////////////////////////////////////
void PlotMC_ErrorBand2D_ProjY(PlotUtils::MnvH2D *mc,
	char *pdf_label, char *histotitle, char *xaxislabel,
	char *yaxislabel, char *zaxislabel_units,
	double Ymax, bool setMaxY, bool doMultipliers,
	std::vector<double> XMultipliers,
	bool statPlusSysDATA, bool statPlusSysMC,
	bool do_bin_width_norm, bool useHistTitles, double text_size)
{
	PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
	PlotUtils::MnvH1D *datahist = new PlotUtils::MnvH1D("adsf", " ", nbins, xmin, xmax);
	PlotUtils::MnvH2D *mcHist_clone = mc->Clone("mcHist_clone");

	int nbins_X = mcHist_clone->GetNbinsX();
	int nbins_Y = mcHist_clone->GetNbinsY();

	double MinX = mcHist_clone->GetYaxis()->GetBinLowEdge(1);
	double MaxX = 1.2 *mcHist_clone->GetYaxis()->GetBinLowEdge(nbins_Y);

	int nbins_X_mc = mcHist_clone->GetNbinsX();
	int nbins_Y_mc = mcHist_clone->GetNbinsY();

	double maxmax = 1.38* GetMaxFromProjectionY(mcHist_clone, do_bin_width_norm);
	int grid_x;
	int grid_y;
	int Nbins;
	std::string xaxislabel_string(xaxislabel);

	grid_x = sqrt(nbins_X) + 1;
	grid_y = nbins_X / (grid_x - 1);
	Nbins = mcHist_clone->GetNbinsX();
	if (nbins_X_mc != Nbins)
	{
		std::cout << "MC and Data have different nBinX: PlotDataMC_ErrorBand2D_ProjY" << std::endl;
	}

	if (DeBug == true) std::cout << nbins_X - grid_x * grid_y << std::endl;
	if (DeBug == true) std::cout << "Plotting plotYAxis1D with a grid of " << nbins_X << "\t" << nbins_Y << "\t" << grid_x << "\t" << grid_y << std::endl;
	TLegend * leg;

	if (Nbins == 5)
	{
		leg = new TLegend(0.75, 0.1, 0.98, 0.35);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextSize(0.02);
		leg->SetNColumns(1);
	}
	else
	{
		leg = new TLegend(0.43, 0.1, 0.98, 0.3);

		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextSize(0.025);
		leg->SetNColumns(3);
	}

	GridCanvas *gc = new GridCanvas(uniq(), grid_x, grid_y, 800, 500);
	TCanvas cE("c1", "c1");
	gc->SetRightMargin(0.06);
	gc->SetLeftMargin(0.06);
	gc->ResetPads();

	for (int i = 1; i <= Nbins; ++i)
	{
		PlotUtils::MnvH1D *hMCyproj =
			mcHist_clone->ProjectionY(uniq(), i, i)->Clone();

		hMCyproj->SetMaximum(maxmax);

		if (do_bin_width_norm == true)
		{
			hMCyproj->Scale(1., "width");
		}

		if (doMultipliers == true)
		{
			hMCyproj->Scale(XMultipliers.at(i - 1));
		}

		if (i == 1)
		{
			if (statPlusSysMC == true)
			{
				hMCyproj->SetMarkerStyle(0);
				hMCyproj->SetLineColor(mnvPlotter.mc_color);
				hMCyproj->SetLineWidth(mnvPlotter.mc_line_width);
				hMCyproj->SetLineStyle(mnvPlotter.mc_line_style);
				hMCyproj->SetFillStyle(mnvPlotter.mc_error_style);
				leg->AddEntry(hMCyproj, "Error Band [Stat+Sys]", "fl");
			}
			else leg->AddEntry(hMCyproj, "MINERvA v1[Stat]", "l");
			hMCyproj->SetFillColorAlpha(mnvPlotter.mc_error_color, 0.65);
			hMCyproj->SetFillStyle(mnvPlotter.mc_error_style);
			hMCyproj->SetMarkerStyle(0);
			hMCyproj->SetLineWidth(0);
		}

		gc->cd(i);
		mnvPlotter.axis_label_size = 0.02;
		mnvPlotter.legend_text_size = 0.02;
		mnvPlotter.data_marker_size = 0.3;
		const Double_t mcScale = 1.0;
		mnvPlotter.axis_maximum = maxmax;
		//mnvPlotter.mc_error_color_stack=kRed;
		//mnvPlotter.mc_error_color_stack=kRed;
		hMCyproj->SetLineWidth(2);
		hMCyproj->SetLineColor(2);
		mnvPlotter.draw_normalized_to_bin_width = false;
		const bool covAreaNormalize = false;
		const bool statPlusSys = false;
		const bool isSmooth = false;

		mnvPlotter.axis_draw_grid_x = true;     ///< Set to true to get grid drawn for X axis
		mnvPlotter.axis_draw_grid_y = true;

		mnvPlotter.DrawDataMCWithErrorBand(			datahist,
			hMCyproj,
			1.0,
			"N",
			false,	//default is to use Data/MC/Background
			NULL,
			NULL,
			covAreaNormalize,
			statPlusSys,
			isSmooth
	);

		//drawBinRange(dataHist_clone, 2, i, yaxislabel, ".2f", false);
		drawBinRange(mcHist_clone, 1, i, yaxislabel, text_size, ".2f", false);
		if (i == 1) mnvPlotter.WritePreliminary("TL", .015, -.01, -.115, false);
		if (doMultipliers && XMultipliers.at(i - 1) != 1)
		{
			auto pad = gc->cd(i);
			TLatex *la2 = new TLatex(1 - pad->GetRightMargin() - 0.03,
				1 - pad->GetTopMargin() - 0.04,
				TString::Format("#times %.1f", XMultipliers.at(i - 1)));
			la2->SetTextAlign(33);	// top right
			la2->SetNDC();
			la2->SetTextFont(42);
			la2->SetTextSize(0.025);
			la2->Draw();
		}
	}	/// End of Loop

	gc->SetYLabel_Size(.015);
	gc->SetXLabel_Size(.02);
	double MaxY = gc->GetPadMax();
	if (setMaxY == false) gc->SetYLimits(0, MaxY *1.25);
	else
	{
		gc->SetYLimits(0, Ymax);
	}

	gc->SetXLimits(MinX, MaxX);
	gc->SetXTitle(xaxislabel);
	gc->SetYTitleSize(25);
	gc->SetYTitle(zaxislabel_units);
	gc->SetHistTexts();
	leg->Draw("SAME");
	mnvPlotter.AddHistoTitle(histotitle, .04);
	gc->Modified();
	gc->ResetPads();
	gc->Print(pdf_label);
	delete gc;

}

//////////////////////////////////////////////////
//////////////////////////////////////////////////
void Plot2MC_ErrorBand2D_ProjY(PlotUtils::MnvH2D *mc1, char *mc1_legendName,
	PlotUtils::MnvH2D *mc2, char *mc2_legendName,
	char *pdf_label, char *histotitle, char *xaxislabel,
	char *yaxislabel, char *zaxislabel_units,
	double Ymax, bool setMaxY, bool doMultipliers,
	std::vector<double> XMultipliers,
	bool statPlusSysDATA, bool statPlusSysMC,
	bool do_bin_width_norm, bool useHistTitles, double text_size)
{
	PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);

	PlotUtils::MnvH2D *mcHist1 = mc1->Clone("mcHist1");
	PlotUtils::MnvH2D *mcHist2 = mc2->Clone("mcHist2");
	PlotUtils::MnvH1D *datahistPlaceholder = new PlotUtils::MnvH1D("adsf", " ", nbins, xmin, xmax);
	int NDF_2d;

	int nbins_X = mcHist1->GetNbinsX();
	int nbins_Y = mcHist1->GetNbinsY();

	double MinX = mcHist1->GetYaxis()->GetBinLowEdge(1);
	double MaxX = 1.2 *mcHist1->GetYaxis()->GetBinLowEdge(nbins_Y);

	int nbins_X_mc = mcHist1->GetNbinsX();
	int nbins_Y_mc = mcHist1->GetNbinsY();

	TLegend *leg = new TLegend(0.43, 0.1, 0.98, 0.3);

	leg->SetFillStyle(0);
	leg->SetBorderSize(0);
	leg->SetTextSize(0.025);
	leg->SetNColumns(3);

	double maxmax = 1.35* GetMaxFromProjectionY(mcHist1, mcHist2, do_bin_width_norm);
	int grid_x;
	int grid_y;
	int Nbins;
	std::string xaxislabel_string(xaxislabel);

	grid_x = sqrt(nbins_X) + 1;
	grid_y = nbins_X / (grid_x - 1);
	Nbins = mcHist1->GetNbinsX();

	if (DeBug == true) std::cout << nbins_X - grid_x * grid_y << std::endl;
	if (DeBug == true) std::cout << "Plotting plotYAxis1D with a grid of " << nbins_X << "\t" << nbins_Y << "\t" << grid_x << "\t" << grid_y << std::endl;

	GridCanvas *gc = new GridCanvas(uniq(), grid_x, grid_y, 800, 500);
	TCanvas cE("c1", "c1");
	gc->SetRightMargin(0.06);
	gc->SetLeftMargin(0.06);
	gc->ResetPads();

	for (int i = 1; i <= Nbins; ++i)
	{
		PlotUtils::MnvH1D *hMCyproj1 =
			mcHist1->ProjectionY(uniq(), i, i)->Clone();

		PlotUtils::MnvH1D *hMCyproj2 =
			mcHist2->ProjectionY(uniq(), i, i)->Clone();

		hMCyproj1->SetMaximum(maxmax);
		hMCyproj2->SetMaximum(maxmax);

		if (doMultipliers == true)
		{
			hMCyproj1->Scale(XMultipliers.at(i - 1));
			hMCyproj2->Scale(XMultipliers.at(i - 1));
		}

		if (do_bin_width_norm == true)
		{
			hMCyproj1->Scale(1., "width");
			hMCyproj2->Scale(1., "width");
		}

		hMCyproj1->SetMarkerStyle(0);
		hMCyproj1->SetLineColor(mnvPlotter.mc_color);
		hMCyproj1->SetLineWidth(mnvPlotter.mc_line_width);
		hMCyproj1->SetLineStyle(mnvPlotter.mc_line_style);
		hMCyproj1->SetFillStyle(mnvPlotter.mc_error_style);
		hMCyproj2->SetMarkerStyle(0);
		hMCyproj2->SetLineColor(kBlue);
		hMCyproj2->SetLineWidth(mnvPlotter.mc_line_width);
		hMCyproj2->SetLineStyle(mnvPlotter.mc_line_style);
		hMCyproj2->SetFillStyle(mnvPlotter.mc_error_style);

		if (i == 1)
		{
			leg->AddEntry(hMCyproj1, mc1_legendName, "fl");
			leg->AddEntry(hMCyproj2, mc2_legendName, "fl");
		}

		gc->cd(i);
		mnvPlotter.axis_label_size = 0.02;
		mnvPlotter.legend_text_size = 0.02;
		mnvPlotter.data_marker_size = 0.3;
		const Double_t mcScale = 1.0;
		mnvPlotter.axis_maximum = maxmax;
		if(setMaxY==true) mnvPlotter.axis_maximum =Ymax;
		//mnvPlotter.mc_error_color_stack=kRed;
		//mnvPlotter.mc_error_color_stack=kRed;
		hMCyproj1->SetLineWidth(2);
		hMCyproj1->SetLineColor(2);
		mnvPlotter.draw_normalized_to_bin_width = false;
		const bool covAreaNormalize = false;
		const bool statPlusSys = false;
		const bool isSmooth = false;

		mnvPlotter.DrawDataMCWithErrorBand(			datahistPlaceholder,
			hMCyproj1,
			1.0,
			"N",
			false,	//default is to use Data/MC/Background
			NULL,
			NULL,
			covAreaNormalize,
			statPlusSys,
			isSmooth
	);

		//  mnvPlotter.DrawDataMCWithErrorBand(		//    datahistPlaceholder,
		//    hMCyproj2,
		//    1.0,
		//    "N",
		//    false, 	//default is to use Data/MC/Background
		//    NULL,
		//    NULL,
		//    covAreaNormalize, 		//    statPlusSys, 		//    isSmooth
		// );
		hMCyproj2->Draw("SAME");
		//drawBinRange(dataHist_clone, 2, i, yaxislabel, ".2f", false);
		drawBinRange(mcHist1, 1, i, yaxislabel, text_size, ".2f", false);
		if (i == 1) mnvPlotter.WritePreliminary("TL", .015, -.01, -.115, false);
		if (doMultipliers && XMultipliers.at(i - 1) != 1)
		{
			auto pad = gc->cd(i);
			TLatex *la2 = new TLatex(1 - pad->GetRightMargin() - 0.03,
				1 - pad->GetTopMargin() - 0.04,
				TString::Format("#times %.1f", XMultipliers.at(i - 1)));
			la2->SetTextAlign(33);	// top right
			la2->SetNDC();
			la2->SetTextFont(42);
			la2->SetTextSize(0.025);
			la2->Draw();
		}

		int ndf_panel;
		double Chisqt_panel = mnvPlotter.Chi2DataMC(hMCyproj2, hMCyproj1, ndf_panel);
		TLatex *Chisqt_latex = new TLatex(gPad->GetLeftMargin() + .01,
			1 - gPad->GetTopMargin() - 0.035,
			TString::Format("#chi^{2}/ndf = %.1f / %i = %.1f", Chisqt_panel, ndf_panel, Chisqt_panel / ndf_panel));
		Chisqt_latex->SetTextAlign(13);	// top left
		Chisqt_latex->SetNDC();
		Chisqt_latex->SetTextFont(42);
		Chisqt_latex->SetTextSize(text_size *.8);
		Chisqt_latex->SetTextColor(kBlue);
		Chisqt_latex->Draw();
	}	/// End of Loop
	char chi_label[1024];

	//sprintf(chi_label, "#chi^{2}/ndf = %.1f / %i = %.1f", chi2_2d,   NDF_2d, chi2_2d /   NDF_2d);
	//leg -> AddEntry((TObject*)0, chi_label, "");

	gc->SetYLabel_Size(.015);
	gc->SetXLabel_Size(.02);
	double MaxY = gc->GetPadMax();
	if (setMaxY == false) gc->SetYLimits(0, MaxY *1.25);
	else
	{
		gc->SetYLimits(0, Ymax);
	}

	gc->SetXLimits(MinX, MaxX);
	gc->SetXTitle(xaxislabel);
	gc->SetYTitleSize(25);
	gc->SetYTitle(zaxislabel_units);
	gc->SetHistTexts();
	leg->Draw("SAME");
	mnvPlotter.AddHistoTitle(histotitle, .04);
	gc->Modified();
	gc->ResetPads();
	gc->Print(pdf_label);
	delete gc;

}

//////////////////////////////////////////////////

void Plot2D_FractionError_ProjY(PlotUtils::MnvH2D *HistInput,
	char *pdf_label, char *histotitle, char *xaxislabel,
	char *yaxislabel,
	double Ymax,
	double text_size)
{
	PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
	PlotUtils::MnvH2D *Hist = HistInput->Clone("mcHist_clone");
	mnvPlotter.mc_line_width = 2;
	int nbins_X = Hist->GetNbinsX();
	int nbins_Y = Hist->GetNbinsY();
	double MinX = Hist->GetYaxis()->GetBinLowEdge(1);
	double MaxX = 1.2 *Hist->GetYaxis()->GetBinLowEdge(nbins_Y);
	TLegend * leg;

	int grid_x;
	int grid_y;
	int Nbins;
	std::string xaxislabel_string(xaxislabel);

	grid_x = sqrt(nbins_X) + 1;
	grid_y = nbins_X / (grid_x - 1);
	Nbins = Hist->GetNbinsX();

	if (DeBug == true) std::cout << nbins_X - grid_x * grid_y << std::endl;
	if (DeBug == true) std::cout << "Plotting plotYAxis1D with a grid of " << nbins_X << "\t" << nbins_Y << "\t" << grid_x << "\t" << grid_y << std::endl;

	GridCanvas *gc = new GridCanvas(uniq(), grid_x, grid_y, 800, 500);
	TCanvas cE("c1", "c1");
	gc->SetRightMargin(0.06);
	gc->SetLeftMargin(0.06);
	gc->ResetPads();

	if (Nbins == 5)
	{
		leg = new TLegend(0.75, 0.1, 0.98, 0.5);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextSize(0.015);
		leg->SetNColumns(1);
	}
	else
	{
		leg = new TLegend(0.43, 0.1, 0.98, 0.3);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextSize(0.025);
		leg->SetNColumns(3);
	}

	for (int i = 1; i <= Nbins; ++i)
	{
		//bins.push_back(i);

		PlotUtils::MnvH1D *Hist_Y_proj =
			Hist->ProjectionY(uniq(), i, i)->Clone();
		//Hist_X_proj->SetMaximum(setMaxY);
		gc->cd(i);
		mnvPlotter.axis_label_size = 0.015;
		const Double_t mcScale = 1.0;
		const std::string &legPos = "N";
		mnvPlotter.axis_maximum = Ymax;
		mnvPlotter.draw_normalized_to_bin_width = false;
		if (i == 1) mnvPlotter.DrawErrorSummary(Hist_Y_proj, *leg, "N", true, true, .00001, false, "", true, "", false);
		else mnvPlotter.DrawErrorSummary(Hist_Y_proj, "N", true, true, .00001, false, "", true, "", false);

		drawBinRange(Hist, 1, i, yaxislabel, text_size, ".2f", false);

		if (i == 1) mnvPlotter.WritePreliminary("TL", .015, -.01, -.115, false);
	}	/// End of Loop

	gc->SetYLabel_Size(.01);
	gc->SetXLabel_Size(.015);
	gc->SetYLimits(0, Ymax *1.25);
	gc->SetXLimits(MinX, MaxX);
	gc->SetXTitle(xaxislabel);
	gc->SetYTitleSize(25);
	gc->SetYTitle("Fractional Uncertainty");
	gc->SetHistTexts();
	leg->Draw("SAME");
	mnvPlotter.AddHistoTitle(histotitle, .04);
	gc->Modified();
	gc->ResetPads();
	gc->Print(pdf_label);
	delete gc;

}

//////////////////////////////////////////////////

void Plot2D_FractionError_ProjY_Group(PlotUtils::MnvH2D *HistInput,
	char *pdf_label, char *histotitle, char *xaxislabel, char *GroupName,
	char *yaxislabel,
	double Ymax,
	double text_size, bool doErrorModelGroups)
{
	PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
	if (doErrorModelGroups == true) MakeModelErrorGroups(mnvPlotter);
	PlotUtils::MnvH2D *Hist = HistInput->Clone("mcHist_clone");
	mnvPlotter.mc_line_width = 2;
	int nbins_X = Hist->GetNbinsX();
	int nbins_Y = Hist->GetNbinsY();
	double MinX = Hist->GetYaxis()->GetBinLowEdge(1);
	double MaxX = 1.2 *Hist->GetYaxis()->GetBinLowEdge(nbins_Y);
	TLegend * leg;

	int grid_x;
	int grid_y;
	int Nbins;
	std::string xaxislabel_string(xaxislabel);

	grid_x = sqrt(nbins_X) + 1;
	grid_y = nbins_X / (grid_x - 1);
	Nbins = Hist->GetNbinsX();

	if (DeBug == true) std::cout << nbins_X - grid_x * grid_y << std::endl;
	if (DeBug == true) std::cout << "Plotting plotYAxis1D with a grid of " << nbins_X << "\t" << nbins_Y << "\t" << grid_x << "\t" << grid_y << std::endl;

	GridCanvas *gc = new GridCanvas(uniq(), grid_x, grid_y, 800, 500);
	TCanvas cE("c1", "c1");
	gc->SetRightMargin(0.06);
	gc->SetLeftMargin(0.06);
	gc->ResetPads();

	if (Nbins == 5)
	{
		leg = new TLegend(0.75, 0.1, 0.98, 0.5);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextSize(0.015);
		leg->SetNColumns(1);
	}
	else
	{
		leg = new TLegend(0.43, 0.1, 0.98, 0.3);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextSize(0.02);
		leg->SetNColumns(3);
	}

	for (int i = 1; i <= Nbins; ++i)
	{
		//bins.push_back(i);

		PlotUtils::MnvH1D *Hist_Y_proj =
			Hist->ProjectionY(uniq(), i, i)->Clone();
		//Hist_X_proj->SetMaximum(setMaxY);
		gc->cd(i);
		mnvPlotter.axis_label_size = 0.02;
		const Double_t mcScale = 1.0;
		const std::string &legPos = "N";
		mnvPlotter.axis_maximum = Ymax;
		mnvPlotter.draw_normalized_to_bin_width = false;
		if (i == 1) mnvPlotter.DrawErrorSummary(Hist_Y_proj, *leg, "N", true, true, .00001, false, GroupName, true, "", false);
		else mnvPlotter.DrawErrorSummary(Hist_Y_proj, "N", true, true, .00001, false, GroupName, true, "", false);

		drawBinRange(Hist, 1, i, yaxislabel, text_size, ".2f", false);

		if (i == 1) mnvPlotter.WritePreliminary("TL", .015, -.01, -.115, false);
	}	/// End of Loop

	gc->SetYLabel_Size(.02);
	gc->SetXLabel_Size(.02);
	gc->SetYLimits(0, Ymax *1.25);
	gc->SetXLimits(MinX, MaxX);
	gc->SetXTitle(xaxislabel);
	gc->SetYTitleSize(18);
	gc->SetYTitle("Fractional Uncertainty");
	gc->SetHistTexts();
	leg->Draw("SAME");
	mnvPlotter.AddHistoTitle(histotitle, .04);
	gc->Modified();
	gc->ResetPads();
	gc->Print(pdf_label);
	delete gc;

}

//////////////////////////////////////////////////
void PlotDataStackedMC2D_ProjX(PlotUtils::MnvH2D *data, PlotUtils::MnvH2D *mc, const TObjArray *stack,
		std::vector<int> fillColors, bool DoBinwidthNorm,
		char *pdf_label, char *histotitle, char *xaxislabel,
		char *yaxislabel, char *zaxislabel_units,
		double Ymax, bool setMaxY, bool doMultipliers,
		std::vector<double> XMultipliers,
		bool statPlusSysDATA, bool statPlusSysMC,
		bool do_bin_width_norm, bool useHistTitles)
{
	PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
	PlotUtils::MnvH2D *dataHist = data->Clone("tmpData");
	TH2 *dataHist_clone = data->Clone("dataHist_clone");
	PlotUtils::MnvH2D *mcHist_clone = mc->Clone("mcHist_clone");
	mnvPlotter.mc_error_style_stack = 3001;
	mnvPlotter.mc_error_color_stack = kRed;
	int nVars = stack->GetEntries();
	int nbins_X = data->GetNbinsX();
	int nbins_Y = data->GetNbinsY();

	double MinX = mcHist_clone->GetXaxis()->GetBinLowEdge(1);
	double MaxX = 1.1 *mcHist_clone->GetXaxis()->GetBinLowEdge(nbins_X);
	std::cout << "The NEntries for TObjArray: " << nVars << std::endl;
	int nbins_X_mc = mcHist_clone->GetNbinsX();
	int nbins_Y_mc = mcHist_clone->GetNbinsY();

	TLegend *leg = new TLegend(0.43, 0.1, 0.98, 0.3);

	leg->SetFillStyle(0);
	leg->SetBorderSize(0);
	leg->SetTextSize(0.025);
	leg->SetNColumns(3);

	//  std::cout<<"nbins_X = " << nbins_X << std::endl;
	//  std::cout<<"nbins_Y = " << nbins_Y << std::endl;
	//  std::cout<<"nbins_X_mc = " << nbins_X_mc << std::endl;
	//  std::cout<<"nbins_Y_mc = " << nbins_Y_mc << std::endl;

	double maxmax = 1.2 *dataHist->GetMaximum();
	int grid_x;
	int grid_y;
	int Nbins;
	std::string xaxislabel_string(xaxislabel);

	grid_x = sqrt(nbins_Y) + 1;
	grid_y = nbins_Y / (grid_x - 1);
	Nbins = dataHist->GetNbinsY();

	if (DeBug == true) std::cout << nbins_X - grid_x * grid_y << std::endl;
	if (DeBug == true) std::cout << "Plotting plotYAxis1D with a grid of " << nbins_X << "\t" << nbins_Y << "\t" << grid_x << "\t" << grid_y << std::endl;

	std::vector<int> bins;	// = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	if (Nbins == 11)
	{
		leg = new TLegend(0.85, 0.005, 0.99, 0.30);
		leg->SetNColumns(1);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextSize(0.015);
	}

	GridCanvas *gc = new GridCanvas(uniq(), grid_x, grid_y, 800, 500);
	TCanvas cE("c1", "c1");
	gc->SetRightMargin(0.01);
	gc->SetLeftMargin(0.1);
	gc->ResetPads();

	for (int i = 1; i <= Nbins; ++i)
	{
		bins.push_back(i);

		TObjArray *mcprojyArr = new TObjArray();
		mcprojyArr->SetOwner(kTRUE);
		PlotUtils::MnvH1D *hdataxproj =
			dataHist->ProjectionX(uniq(), i, i)->Clone();

		PlotUtils::MnvH1D *hMCxproj =
			mcHist_clone->ProjectionX(uniq(), i, i)->Clone();

		hMCxproj->SetMaximum(maxmax);
		hdataxproj->SetMaximum(maxmax);

		if (doMultipliers == true)
		{
			hdataxproj->Scale(XMultipliers.at(i - 1));
			hMCxproj->Scale(XMultipliers.at(i - 1));
		}

		hdataxproj->Scale(1., "width");
		hMCxproj->Scale(1., "width");

		if (i == 1)
		{
			if (statPlusSysDATA == true)
			{
				leg->AddEntry(hdataxproj, "Data[Stat+Sys]", "lpe");
			}
			else
			{
				leg->AddEntry(hdataxproj, "Data[Stat]", "lpe");
			}

			if (statPlusSysMC == true)
			{
				hMCxproj->SetFillColorAlpha(mnvPlotter.mc_error_color_stack, 0.55);
				hMCxproj->SetFillStyle(mnvPlotter.mc_error_style_stack);
				hMCxproj->SetMarkerStyle(0);
				hMCxproj->SetLineWidth(0);
				leg->AddEntry(hMCxproj, "Error Band [Stat+Sys]", "f");
			}
			else leg->AddEntry(hMCxproj, "MINERvA v1[Stat]", "l");
		}

		for (int iHist = 0; iHist < nVars; ++iHist)
		{
			PlotUtils::MnvH2D *mcHist_stack = (PlotUtils::MnvH2D *) stack->At(iHist)->Clone("mcHist_stack");
			//int ndf;
			std::string words = mcHist_stack->GetTitle();
			std::cout << "iHist  = " << iHist << " words = " << words << std::endl;

			PlotUtils::MnvH1D *mcHist_stack_ProjectionX = mcHist_stack->ProjectionX(uniq(), i, i)->Clone();
			mcHist_stack_ProjectionX->Scale(1., "width");
			if (doMultipliers == true)
			{
				mcHist_stack_ProjectionX->Scale(XMultipliers.at(i - 1));
			}

			mcHist_stack_ProjectionX->SetTitle(words.c_str());
			mcHist_stack_ProjectionX->SetXTitle("");

			mcHist_stack_ProjectionX->SetFillColor(fillColors.at(iHist));
			mcHist_stack_ProjectionX->SetLineWidth(0);

			if (i == 1)
			{
				char words_char[words.length() + 1];
				strcpy(words_char, words.c_str());
				leg->AddEntry(mcHist_stack_ProjectionX, words_char, "f");
			}

			mcprojyArr->Add(mcHist_stack_ProjectionX);
		}

		gc->cd(i);
		mnvPlotter.axis_label_size = 0.02;
		mnvPlotter.legend_text_size = 0.02;
		mnvPlotter.data_marker_size = 0.3;
		const Int_t mcFillStyle = 1001;
		const Double_t mcScale = 1.0;
		//const std::string& legPos = "N";
		mnvPlotter.axis_maximum = maxmax;
		//mnvPlotter.mc_error_color_stack=kRed;
		//mnvPlotter.mc_error_color_stack=kRed;
		hMCxproj->SetLineWidth(3);
		hMCxproj->SetLineColor(2);
		mnvPlotter.draw_normalized_to_bin_width = false;
		mnvPlotter.DrawDataStackedMCWithErrorBand(hdataxproj, hMCxproj, mcprojyArr, fillColors, useHistTitles, statPlusSysDATA, statPlusSysMC, mcFillStyle, mcScale, "N");
		//mnvPlotter.DrawDataStackedMC(hdataxproj, mcprojyArr,
		//&fillColors[0], 1.0, legPos, "Data",  -1);

		drawBinRange(dataHist_clone, 2, i, xaxislabel, ".2f", false);
		if (i == 1) mnvPlotter.WritePreliminary("TL", .015, -.01, -.05, false);
		if (doMultipliers && XMultipliers.at(i - 1) != 1)
		{
			auto pad = gc->cd(i);
			TLatex *la2 = new TLatex(1 - pad->GetRightMargin() - 0.02,
				1 - pad->GetTopMargin() - 0.08,
				TString::Format("#times %.1f", XMultipliers.at(i - 1)));
			la2->SetTextAlign(33);	// top right
			la2->SetNDC();
			la2->SetTextFont(42);
			la2->SetTextSize(0.03);
			la2->Draw();
		}

		//mcprojyArr->Delete();
	}	/// End of Loop

	// gc->DrawBinRanges(dataHist, 2, bins, dataHist->GetYaxis()->GetTitle(), binCenter, .02);
	gc->SetYLabel_Size(.015);
	gc->SetXLabel_Size(.025);
	double MaxY = gc->GetPadMax();
	if (setMaxY == false) gc->SetYLimits(0, MaxY *1.25);
	else
	{
		gc->SetYLimits(0, Ymax);
	}

	gc->SetXLimits(MinX, MaxX);
	gc->SetXTitle(yaxislabel);
	gc->SetYTitleSize(15);
	gc->SetYTitle(zaxislabel_units);
	gc->SetHistTexts();
	leg->Draw("SAME");
	mnvPlotter.AddHistoTitle(histotitle, .04);
	gc->Modified();
	gc->ResetPads();
	gc->Print(pdf_label);
	delete gc;

}

//////////////////////////////////////////////////////
void PlotDataStackedMC2D_ProjX(PlotUtils::MnvH2D *data, TObjArray stack_input,
	std::vector<int> fillColors,
	char *pdf_label, char *histotitle, char *xaxislabel,
	char *yaxislabel, char *zaxislabel_units,
	double Ymax, bool setMaxY, bool doMultipliers,
	std::vector<double> XMultipliers,
	bool do_bin_width_norm, double text_size)
{
	PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
	PlotUtils::MnvH2D *dataHist = data->Clone("tmpData");
	TH2 *dataHist_clone = data->Clone("dataHist_clone");
	//TObjArray *stack =  &stack_input;
	TObjArray *stack = (TObjArray*) stack_input.Clone();
	stack->SetOwner(kTRUE);
	int nVars = stack->GetEntries();
	int nbins_X = data->GetNbinsX();
	int nbins_Y = data->GetNbinsY();

	double MinX = dataHist_clone->GetXaxis()->GetBinLowEdge(1);
	double MaxX = 1.1 *dataHist_clone->GetXaxis()->GetBinLowEdge(nbins_X);
	std::cout << "The NEntries for TObjArray: " << nVars << std::endl;

	TLegend *leg = new TLegend(0.43, 0.1, 0.98, 0.3);

	leg->SetFillStyle(0);
	leg->SetBorderSize(0);
	leg->SetTextSize(0.025);
	leg->SetNColumns(3);

	double maxmax = 1.35* GetMaxFromProjectionX(dataHist, do_bin_width_norm);
	int grid_x;
	int grid_y;
	int Nbins;
	std::string xaxislabel_string(xaxislabel);

	grid_x = sqrt(nbins_Y) + 1;
	grid_y = nbins_Y / (grid_x - 1);
	Nbins = dataHist->GetNbinsY();

	if (DeBug == true) std::cout << nbins_X - grid_x * grid_y << std::endl;
	if (DeBug == true) std::cout << "Plotting plotYAxis1D with a grid of " << nbins_X << "\t" << nbins_Y << "\t" << grid_x << "\t" << grid_y << std::endl;

	GridCanvas *gc = new GridCanvas(uniq(), grid_x, grid_y, 800, 500);
	TCanvas cE("c1", "c1");
	gc->SetRightMargin(0.01);
	gc->SetLeftMargin(0.1);
	gc->ResetPads();

	for (int i = 1; i <= Nbins; ++i)
	{
		TObjArray *mcprojyArr = new TObjArray();
		mcprojyArr->SetOwner(kTRUE);

		PlotUtils::MnvH1D *hdataxproj =
			dataHist->ProjectionX(uniq(), i, i)->Clone();
		hdataxproj->SetMaximum(maxmax);

		if (doMultipliers == true)
		{
			hdataxproj->Scale(XMultipliers.at(i - 1));
		}

		if (do_bin_width_norm == true) hdataxproj->Scale(1., "width");

		if (i == 1)
		{
			leg->AddEntry(hdataxproj, "Data[Stat]", "lpe");
		}

		for (int iHist = 0; iHist < nVars; ++iHist)
		{
			PlotUtils::MnvH2D *mcHist_stack = (PlotUtils::MnvH2D *) stack->At(iHist)->Clone("mcHist_stack");
			//int ndf;
			std::string words = mcHist_stack->GetTitle();
			//  std::cout<<"iHist  = "<< iHist <<" words = "<< words<<std::endl;

			PlotUtils::MnvH1D *mcHist_stack_ProjectionX = mcHist_stack->ProjectionX(uniq(), i, i)->Clone();

			if (do_bin_width_norm == true) mcHist_stack_ProjectionX->Scale(1., "width");
			if (doMultipliers == true)
			{
				mcHist_stack_ProjectionX->Scale(XMultipliers.at(i - 1));
			}

			mcHist_stack_ProjectionX->SetTitle(words.c_str());
			mcHist_stack_ProjectionX->SetXTitle("");

			mcHist_stack_ProjectionX->SetFillColor(fillColors.at(iHist));
			mcHist_stack_ProjectionX->SetLineWidth(0);

			if (i == 1)
			{
				char words_char[words.length() + 1];
				strcpy(words_char, words.c_str());
				leg->AddEntry(mcHist_stack_ProjectionX, words_char, "f");
			}

			mcprojyArr->Add(mcHist_stack_ProjectionX);
		}

		gc->cd(i);
		mnvPlotter.axis_label_size = 0.02;
		mnvPlotter.legend_text_size = 0.02;
		mnvPlotter.data_marker_size = 0.3;
		mnvPlotter.axis_maximum = maxmax;
		mnvPlotter.draw_normalized_to_bin_width = false;
		mnvPlotter.mc_line_width = 0;
		mnvPlotter.DrawDataStackedMC(hdataxproj, mcprojyArr);
		drawBinRange(dataHist_clone, 2, i, xaxislabel, text_size, ".2f", false);

		if (doMultipliers && XMultipliers.at(i - 1) != 1)
		{
			auto pad = gc->cd(i);
			TLatex *la2 = new TLatex(1 - pad->GetRightMargin() - 0.02,
				1 - pad->GetTopMargin() - 0.08,
				TString::Format("#times %.1f", XMultipliers.at(i - 1)));
			la2->SetTextAlign(33);	// top right
			la2->SetNDC();
			la2->SetTextFont(42);
			la2->SetTextSize(0.03);
			la2->Draw();
			if (i == 1) mnvPlotter.WritePreliminary("TL", .015, -.01, -.115, false);
		}

		//mcprojyArr->Clear();
		//mcprojyArr->Delete();
	}	/// End of Loop

	// gc->DrawBinRanges(dataHist, 2, bins, dataHist->GetYaxis()->GetTitle(), binCenter, .02);
	gc->SetYLabel_Size(.015);
	gc->SetXLabel_Size(.025);
	double MaxY = gc->GetPadMax();
	if (setMaxY == false) gc->SetYLimits(0, MaxY *1.25);
	else
	{
		gc->SetYLimits(0, Ymax);
	}

	gc->SetXLimits(MinX, MaxX);
	gc->SetXTitle(yaxislabel);
	gc->SetYTitleSize(25);
	gc->SetYTitle(zaxislabel_units);
	gc->SetHistTexts();
	leg->Draw("SAME");
	mnvPlotter.AddHistoTitle(histotitle, .04);
	gc->Modified();
	gc->ResetPads();
	gc->Print(pdf_label);
	//leg->Clear();
	mnvPlotter.CleanTmp();
	stack->Delete();
	delete gc;
	//mcprojyArr->Delete();

}

//////////////////////////////////////////////////
void PlotDataMC_ErrorBand2D_ProjX(PlotUtils::MnvH2D *data, PlotUtils::MnvH2D *mc,
	char *pdf_label, char *histotitle, char *xaxislabel,
	char *yaxislabel, char *zaxislabel_units,
	double Ymax, bool setMaxY, bool doMultipliers,
	std::vector<double> XMultipliers,
	bool statPlusSysDATA, bool statPlusSysMC,
	bool do_bin_width_norm, bool useHistTitles, double text_size)
{
	PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
	PlotUtils::MnvH2D *dataHist = data->Clone("dataHist");
	PlotUtils::MnvH2D *mcHist_clone = mc->Clone("mcHist_clone");

	int nbins_X = data->GetNbinsX();
	int nbins_Y = data->GetNbinsY();
	double MinX = mcHist_clone->GetXaxis()->GetBinLowEdge(1);
	double MaxX = 1.1 *mcHist_clone->GetXaxis()->GetBinLowEdge(nbins_X);

	int nbins_X_mc = mcHist_clone->GetNbinsX();
	int nbins_Y_mc = mcHist_clone->GetNbinsY();

	int NDF_2d;
	double chi2_2d = mnvPlotter.Chi2DataMC(dataHist, mcHist_clone, NDF_2d);

	//  std::cout<<"nbins_X = " << nbins_X << std::endl;
	//  std::cout<<"nbins_Y = " << nbins_Y << std::endl;
	//  std::cout<<"nbins_X_mc = " << nbins_X_mc << std::endl;
	//  std::cout<<"nbins_Y_mc = " << nbins_Y_mc << std::endl;

	//double maxmax = 1.2 *dataHist->GetMaximum();
	double maxmax = 1.38* GetMaxFromProjectionX(dataHist, mcHist_clone, do_bin_width_norm);
	int grid_x;
	int grid_y;
	int Nbins;
	std::string xaxislabel_string(xaxislabel);

	grid_x = sqrt(nbins_Y) + 1;
	grid_y = nbins_Y / (grid_x - 1);
	Nbins = dataHist->GetNbinsY();

	if (DeBug == true) std::cout << nbins_X - grid_x * grid_y << std::endl;
	if (DeBug == true) std::cout << "Plotting plotYAxis1D with a grid of " << nbins_X << "\t" << nbins_Y << "\t" << grid_x << "\t" << grid_y << std::endl;

	TLegend * leg;
	if (Nbins == 5 || Nbins == 11)
	{
		leg = new TLegend(0.78, 0.1, 0.98, 0.4);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextSize(0.015);
		leg->SetNColumns(1);
	}
	else
	{
		leg = new TLegend(0.43, 0.1, 0.98, 0.3);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextSize(0.025);
		leg->SetNColumns(3);
	}

	GridCanvas *gc = new GridCanvas(uniq(), grid_x, grid_y, 800, 500);
	TCanvas cE("c1", "c1");
	gc->SetRightMargin(0.06);
	gc->SetLeftMargin(0.06);
	gc->ResetPads();

	for (int i = 1; i <= Nbins; ++i)
	{
		//bins.push_back(i);

		PlotUtils::MnvH1D *hdataxproj =
			dataHist->ProjectionX(uniq(), i, i)->Clone();

		PlotUtils::MnvH1D *hMCxproj =
			mcHist_clone->ProjectionX(uniq(), i, i)->Clone();

		hMCxproj->SetMaximum(maxmax);
		hdataxproj->SetMaximum(maxmax);

		if (do_bin_width_norm == true)
		{
			hdataxproj->Scale(1., "width");
			hMCxproj->Scale(1., "width");
		}

		if (doMultipliers == true)
		{
			hdataxproj->Scale(XMultipliers.at(i - 1));
			hMCxproj->Scale(XMultipliers.at(i - 1));
		}

		if (i == 1)
		{
			if (statPlusSysDATA == true)
			{
				leg->AddEntry(hdataxproj, "Data[Stat+Sys]", "lpe");
			}
			else
			{
				leg->AddEntry(hdataxproj, "Data[Stat]", "lpe");
			}

			if (statPlusSysMC == true)
			{
				hMCxproj->SetMarkerStyle(0);
				hMCxproj->SetLineColor(mnvPlotter.mc_color);
				hMCxproj->SetLineWidth(mnvPlotter.mc_line_width);
				hMCxproj->SetLineStyle(mnvPlotter.mc_line_style);
				hMCxproj->SetFillStyle(mnvPlotter.mc_error_style);
				leg->AddEntry(hMCxproj, "MINERvA v1[Stat+Sys]", "fl");
			}
			else
			{
				leg->AddEntry(hMCxproj, "MINERvA v1[Stat]", "fl");
			}

			hMCxproj->SetFillColorAlpha(mnvPlotter.mc_error_color, 0.65);
			hMCxproj->SetFillStyle(mnvPlotter.mc_error_style);
			hMCxproj->SetMarkerStyle(0);
			hMCxproj->SetLineWidth(0);
		}

		gc->cd(i);
		mnvPlotter.axis_label_size = 0.02;
		mnvPlotter.legend_text_size = 0.02;
		mnvPlotter.data_marker_size = 0.3;
		const Double_t mcScale = 1.0;
		//const std::string& legPos = "N";
		mnvPlotter.axis_maximum = maxmax;
		//mnvPlotter.mc_error_color_stack=kRed;
		//mnvPlotter.mc_error_color_stack=kRed;
		hMCxproj->SetLineWidth(2);
		hMCxproj->SetLineColor(2);
		mnvPlotter.draw_normalized_to_bin_width = false;
		const bool covAreaNormalize = false;
		const bool statPlusSys = false;
		const bool isSmooth = false;
		mnvPlotter.DrawDataMCWithErrorBand(			hdataxproj,
			hMCxproj,
			1.0,
			"N",
			false,	//default is to use Data/MC/Background
			NULL,
			NULL,
			covAreaNormalize,
			statPlusSys,
			isSmooth
	);
		drawBinRange(dataHist, 2, i, yaxislabel, text_size, ".2f", false);

		if (i == 1) mnvPlotter.WritePreliminary("TL", .015, -.01, -.115, false);

		if (doMultipliers && XMultipliers.at(i - 1) != 1)
		{
			auto pad = gc->cd(i);
			TLatex *la2 = new TLatex(1 - pad->GetRightMargin() - 0.03,
				1 - pad->GetTopMargin() - 0.04,
				TString::Format("#times %.1f", XMultipliers.at(i - 1)));
			la2->SetTextAlign(33);	// top right
			la2->SetNDC();
			la2->SetTextFont(42);
			la2->SetTextSize(0.025);
			la2->Draw();
		}

		int ndf_panel;
		double Chisqt_panel = mnvPlotter.Chi2DataMC(hdataxproj, hMCxproj, ndf_panel);
		TLatex *Chisqt_latex = new TLatex(gPad->GetLeftMargin() + .01,
			1 - gPad->GetTopMargin() - 0.035,
			TString::Format("#chi^{2}/ndf = %.1f / %i = %.1f", Chisqt_panel, ndf_panel, Chisqt_panel / ndf_panel));
		Chisqt_latex->SetTextAlign(13);	// top left
		Chisqt_latex->SetNDC();
		Chisqt_latex->SetTextFont(42);
		Chisqt_latex->SetTextSize(text_size *.8);
		Chisqt_latex->SetTextColor(kBlue);
		Chisqt_latex->Draw();
	}	/// End of Loop

	char chi_label[1024];

	sprintf(chi_label, "#chi^{2}/ndf = %.1f / %i = %.1f", chi2_2d, NDF_2d, chi2_2d / NDF_2d);
	leg->AddEntry((TObject*) 0, chi_label, "");

	gc->SetYLabel_Size(.015);
	gc->SetXLabel_Size(.02);
	double MaxY = gc->GetPadMax();
	if (setMaxY == false) gc->SetYLimits(0, MaxY *1.25);
	else
	{
		gc->SetYLimits(0, Ymax);
	}

	gc->SetXLimits(MinX, MaxX);
	gc->SetXTitle(xaxislabel);
	gc->SetYTitleSize(10);
	gc->SetYTitle(zaxislabel_units);
	gc->SetHistTexts();
	leg->Draw("SAME");
	mnvPlotter.AddHistoTitle(histotitle, .04);
	gc->Modified();
	gc->ResetPads();
	gc->Print(pdf_label);
	delete gc;

}

void PlotDataMC_ErrorBand2D_ProjX(PlotUtils::MnvH2D *data, PlotUtils::MnvH2D *mc,
	PlotUtils::MnvH2D *data_BG_input, PlotUtils::MnvH2D *mc_BG_input,
	char *pdf_label, char *histotitle, char *xaxislabel,
	char *yaxislabel, char *zaxislabel_units,
	double Ymax, bool setMaxY, bool doMultipliers,
	std::vector<double> XMultipliers,
	bool statPlusSysDATA, bool statPlusSysMC,
	bool do_bin_width_norm, bool useHistTitles, double text_size)
{
	PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
	PlotUtils::MnvH2D *dataHist = data->Clone("dataHist");
	PlotUtils::MnvH2D *mcHist_clone = mc->Clone("mcHist_clone");

	PlotUtils::MnvH2D *dataHistBG = data_BG_input->Clone("dataHistBG");
	PlotUtils::MnvH2D *mcHistBG = mc_BG_input->Clone("mcHistBG");

	mnvPlotter.data_bkgd_style = 22;
	int nbins_X = data->GetNbinsX();
	int nbins_Y = data->GetNbinsY();
	double MinX = mcHist_clone->GetXaxis()->GetBinLowEdge(1);
	double MaxX = 1.1 *mcHist_clone->GetXaxis()->GetBinLowEdge(nbins_X);

	int nbins_X_mc = mcHist_clone->GetNbinsX();
	int nbins_Y_mc = mcHist_clone->GetNbinsY();

	int NDF_2d;
	double chi2_2d = mnvPlotter.Chi2DataMC(dataHist, mcHist_clone, NDF_2d);

	//  std::cout<<"nbins_X = " << nbins_X << std::endl;
	//  std::cout<<"nbins_Y = " << nbins_Y << std::endl;
	//  std::cout<<"nbins_X_mc = " << nbins_X_mc << std::endl;
	//  std::cout<<"nbins_Y_mc = " << nbins_Y_mc << std::endl;

	//double maxmax = 1.2 *dataHist->GetMaximum();
	double maxmax = 1.4* GetMaxFromProjectionX(dataHist, mcHist_clone, do_bin_width_norm);
	int grid_x;
	int grid_y;
	int Nbins;
	std::string xaxislabel_string(xaxislabel);

	grid_x = sqrt(nbins_Y) + 1;
	grid_y = nbins_Y / (grid_x - 1);
	Nbins = dataHist->GetNbinsY();

	if (DeBug == true) std::cout << nbins_X - grid_x * grid_y << std::endl;
	if (DeBug == true) std::cout << "Plotting plotYAxis1D with a grid of " << nbins_X << "\t" << nbins_Y << "\t" << grid_x << "\t" << grid_y << std::endl;

	TLegend * leg;
	if (Nbins == 5 || Nbins == 11)
	{
		leg = new TLegend(0.78, 0.1, 0.98, 0.35);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextSize(0.015);
		leg->SetNColumns(1);
	}
	else
	{
		leg = new TLegend(0.43, 0.1, 0.98, 0.3);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextSize(0.02);
		leg->SetNColumns(3);
	}

	GridCanvas *gc = new GridCanvas(uniq(), grid_x, grid_y, 800, 500);
	TCanvas cE("c1", "c1");
	gc->SetRightMargin(0.06);
	gc->SetLeftMargin(0.06);
	gc->ResetPads();

	for (int i = 1; i <= Nbins; ++i)
	{
		//bins.push_back(i);

		PlotUtils::MnvH1D *hdataxproj =
			dataHist->ProjectionX(uniq(), i, i)->Clone();

		PlotUtils::MnvH1D *hMCxproj =
			mcHist_clone->ProjectionX(uniq(), i, i)->Clone();

		PlotUtils::MnvH1D *hdataBGxproj =
			dataHistBG->ProjectionX(uniq(), i, i)->Clone();

		PlotUtils::MnvH1D *hMCBGxproj =
			mcHistBG->ProjectionX(uniq(), i, i)->Clone();

		hMCxproj->SetMaximum(maxmax);
		hdataxproj->SetMaximum(maxmax);

		if (do_bin_width_norm == true)
		{
			hdataxproj->Scale(1., "width");
			hMCxproj->Scale(1., "width");
			hdataBGxproj->Scale(1., "width");
			hMCBGxproj->Scale(1., "width");
		}

		if (doMultipliers == true)
		{
			hdataxproj->Scale(XMultipliers.at(i - 1));
			hMCxproj->Scale(XMultipliers.at(i - 1));
			hdataBGxproj->Scale(XMultipliers.at(i - 1));
			hMCBGxproj->Scale(XMultipliers.at(i - 1));
		}

		if (i == 1)
		{
			hdataBGxproj->SetMarkerColor(mnvPlotter.data_bkgd_color);
			hdataBGxproj->SetMarkerStyle(mnvPlotter.data_bkgd_style);
			hdataBGxproj->SetMarkerSize(mnvPlotter.data_bkgd_size *.7);

			if (statPlusSysDATA == true)
			{
				leg->AddEntry(hdataxproj, "Data (^{4}He Full)[Stat+Sys]", "lpe");
				leg->AddEntry(hdataBGxproj, "Data (Empty)", "p");
			}
			else
			{
				leg->AddEntry(hdataxproj, "Data (^{4}He Full)[Stat]", "lpe");
				leg->AddEntry(hdataBGxproj, "Data (Empty)", "p");
			}

			if (statPlusSysMC == true)
			{
				hMCxproj->SetMarkerStyle(0);
				hMCxproj->SetLineColor(mnvPlotter.mc_color);
				hMCxproj->SetLineWidth(mnvPlotter.mc_line_width);
				hMCxproj->SetLineStyle(mnvPlotter.mc_line_style);
				hMCxproj->SetFillStyle(mnvPlotter.mc_error_style);
				leg->AddEntry(hMCxproj, "MINERvA v1(^{4}He Full) [Stat+Sys]", "fl");
			}
			else leg->AddEntry(hMCxproj, "MINERvA v1(^{4}He Full)[Stat]", "l");
			hMCxproj->SetFillColorAlpha(mnvPlotter.mc_error_color, 0.65);
			hMCxproj->SetFillStyle(mnvPlotter.mc_error_style);
			hMCxproj->SetMarkerStyle(0);
			hMCxproj->SetLineWidth(0);

			hMCBGxproj->SetFillColor(mnvPlotter.mc_bkgd_color);
			hMCBGxproj->SetFillStyle(mnvPlotter.mc_bkgd_style);
			hMCBGxproj->SetLineColor(mnvPlotter.mc_bkgd_line_color);
			hMCBGxproj->SetLineWidth(mnvPlotter.mc_bkgd_width);
			leg->AddEntry(hMCBGxproj, "MINERvA v1 (Empty)", "f");
		}

		gc->cd(i);
		mnvPlotter.axis_label_size = 0.02;
		mnvPlotter.legend_text_size = 0.015;
		mnvPlotter.data_marker_size = 0.3;
		const Double_t mcScale = 1.0;
		//const std::string& legPos = "N";
		mnvPlotter.axis_maximum = maxmax;
		//mnvPlotter.mc_error_color_stack=kRed;
		//mnvPlotter.mc_error_color_stack=kRed;
		hMCxproj->SetLineWidth(2);
		hMCxproj->SetLineColor(2);
		mnvPlotter.draw_normalized_to_bin_width = false;
		const bool covAreaNormalize = false;
		const bool statPlusSys = false;
		const bool isSmooth = false;
		mnvPlotter.DrawDataMCWithErrorBand(			hdataxproj,
			hMCxproj,
			1.0,
			"N",
			false,	//default is to use Data/MC/Background
			hdataBGxproj,
			hMCBGxproj,
			covAreaNormalize,
			statPlusSys,
			isSmooth
	);
		drawBinRange(dataHist, 2, i, yaxislabel, text_size, ".2f", false);

		if (i == 1) mnvPlotter.WritePreliminary("TL", .015, -.01, -.115, false);

		if (doMultipliers && XMultipliers.at(i - 1) != 1)
		{
			auto pad = gc->cd(i);
			TLatex *la2 = new TLatex(1 - pad->GetRightMargin() - 0.03,
				1 - pad->GetTopMargin() - 0.04,
				TString::Format("#times %.1f", XMultipliers.at(i - 1)));
			la2->SetTextAlign(33);	// top right
			la2->SetNDC();
			la2->SetTextFont(42);
			la2->SetTextSize(0.02);
			la2->Draw();
		}

		int ndf_panel;
		double Chisqt_panel = mnvPlotter.Chi2DataMC(hdataxproj, hMCxproj, ndf_panel);
		TLatex *Chisqt_latex = new TLatex(gPad->GetLeftMargin() + .01,
			1 - gPad->GetTopMargin() - 0.035,
			TString::Format("#chi^{2}/ndf = %.1f / %i = %.1f", Chisqt_panel, ndf_panel, Chisqt_panel / ndf_panel));
		Chisqt_latex->SetTextAlign(13);	// top left
		Chisqt_latex->SetNDC();
		Chisqt_latex->SetTextFont(42);
		Chisqt_latex->SetTextSize(text_size *.8);
		Chisqt_latex->SetTextColor(kBlue);
		Chisqt_latex->Draw();
	}	/// End of Loop

	char chi_label[1024];

	sprintf(chi_label, "#chi^{2}/ndf = %.1f / %i = %.1f", chi2_2d, NDF_2d, chi2_2d / NDF_2d);
	leg->AddEntry((TObject*) 0, chi_label, "");

	gc->SetYLabel_Size(.015);
	gc->SetXLabel_Size(.02);
	double MaxY = gc->GetPadMax();
	if (setMaxY == false) gc->SetYLimits(0, MaxY *1.25);
	else
	{
		gc->SetYLimits(0, Ymax);
	}

	gc->SetXLimits(MinX, MaxX);
	gc->SetXTitle(xaxislabel);
	gc->SetYTitleSize(25);
	gc->SetYTitle(zaxislabel_units);
	gc->SetHistTexts();
	leg->Draw("SAME");
	mnvPlotter.AddHistoTitle(histotitle, .04);
	gc->Modified();
	gc->ResetPads();
	gc->Print(pdf_label);
	delete gc;

}

///////////////////////////////////////////////////////
void PlotMC_ErrorBand2D_ProjX(PlotUtils::MnvH2D *mc,
	char *pdf_label, char *histotitle, char *xaxislabel,
	char *yaxislabel, char *zaxislabel_units,
	double Ymax, bool setMaxY, bool doMultipliers,
	std::vector<double> XMultipliers,
	bool statPlusSysDATA, bool statPlusSysMC,
	bool do_bin_width_norm, bool useHistTitles, double text_size)
{
	PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
	PlotUtils::MnvH2D *mcHist_clone = mc->Clone("mcHist_clone");
	PlotUtils::MnvH1D *datahist = new PlotUtils::MnvH1D("adsf", " ", nbins, xmin, xmax);
	int nbins_X = mcHist_clone->GetNbinsX();
	int nbins_Y = mcHist_clone->GetNbinsY();
	double MinX = mcHist_clone->GetXaxis()->GetBinLowEdge(1);
	double MaxX = 1.1 *mcHist_clone->GetXaxis()->GetBinLowEdge(nbins_X);

	int nbins_X_mc = mcHist_clone->GetNbinsX();
	int nbins_Y_mc = mcHist_clone->GetNbinsY();

	double maxmax = 1.38* GetMaxFromProjectionX(mcHist_clone, do_bin_width_norm);
	int grid_x;
	int grid_y;
	int Nbins;
	std::string xaxislabel_string(xaxislabel);

	grid_x = sqrt(nbins_Y) + 1;
	grid_y = nbins_Y / (grid_x - 1);
	Nbins = mcHist_clone->GetNbinsY();

	if (DeBug == true) std::cout << nbins_X - grid_x * grid_y << std::endl;
	if (DeBug == true) std::cout << "Plotting plotYAxis1D with a grid of " << nbins_X << "\t" << nbins_Y << "\t" << grid_x << "\t" << grid_y << std::endl;

	TLegend * leg;
	if (Nbins == 5 || Nbins == 11)
	{
		leg = new TLegend(0.78, 0.1, 0.98, 0.35);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextSize(0.015);
		leg->SetNColumns(1);
	}
	else
	{
		leg = new TLegend(0.43, 0.1, 0.98, 0.3);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextSize(0.025);
		leg->SetNColumns(3);
	}

	GridCanvas *gc = new GridCanvas(uniq(), grid_x, grid_y, 800, 500);
	TCanvas cE("c1", "c1");
	gc->SetRightMargin(0.06);
	gc->SetLeftMargin(0.06);
	gc->ResetPads();

	for (int i = 1; i <= Nbins; ++i)
	{
		PlotUtils::MnvH1D *hMCxproj =
			mcHist_clone->ProjectionX(uniq(), i, i)->Clone();

		hMCxproj->SetMaximum(maxmax);

		if (do_bin_width_norm == true)
		{
			hMCxproj->Scale(1., "width");
		}

		if (doMultipliers == true)
		{
			hMCxproj->Scale(XMultipliers.at(i - 1));
		}

		if (i == 1)
		{
			if (statPlusSysMC == true)
			{
				hMCxproj->SetMarkerStyle(0);
				hMCxproj->SetLineColor(mnvPlotter.mc_color);
				hMCxproj->SetLineWidth(mnvPlotter.mc_line_width);
				hMCxproj->SetLineStyle(mnvPlotter.mc_line_style);
				hMCxproj->SetFillStyle(mnvPlotter.mc_error_style);
				leg->AddEntry(hMCxproj, "Error Band [Stat+Sys]", "fl");
			}
			else leg->AddEntry(hMCxproj, "MINERvA v1[Stat]", "l");
			hMCxproj->SetFillColorAlpha(mnvPlotter.mc_error_color, 0.65);
			hMCxproj->SetFillStyle(mnvPlotter.mc_error_style);
			hMCxproj->SetMarkerStyle(0);
			hMCxproj->SetLineWidth(0);
		}

		gc->cd(i);
		mnvPlotter.axis_label_size = 0.02;
		mnvPlotter.legend_text_size = 0.02;
		mnvPlotter.data_marker_size = 0.3;
		const Double_t mcScale = 1.0;
		//const std::string& legPos = "N";
		mnvPlotter.axis_maximum = maxmax;
		//mnvPlotter.mc_error_color_stack=kRed;
		//mnvPlotter.mc_error_color_stack=kRed;
		hMCxproj->SetLineWidth(2);
		hMCxproj->SetLineColor(2);
		mnvPlotter.draw_normalized_to_bin_width = false;
		const bool covAreaNormalize = false;
		const bool statPlusSys = false;
		const bool isSmooth = false;
		  mnvPlotter.axis_draw_grid_x = true;     ///< Set to true to get grid drawn for X axis
		  mnvPlotter.axis_draw_grid_y = true;
		mnvPlotter.DrawDataMCWithErrorBand(			datahist,
			hMCxproj,
			1.0,
			"N",
			false,	//default is to use Data/MC/Background
			NULL,
			NULL,
			covAreaNormalize,
			statPlusSys,
			isSmooth
	);
		drawBinRange(mcHist_clone, 2, i, yaxislabel, text_size, ".2f", false);

		if (i == 1) mnvPlotter.WritePreliminary("TL", .015, -.01, -.115, false);

		if (doMultipliers && XMultipliers.at(i - 1) != 1)
		{
			auto pad = gc->cd(i);
			TLatex *la2 = new TLatex(1 - pad->GetRightMargin() - 0.03,
				1 - pad->GetTopMargin() - 0.04,
				TString::Format("#times %.1f", XMultipliers.at(i - 1)));
			la2->SetTextAlign(33);	// top right
			la2->SetNDC();
			la2->SetTextFont(42);
			la2->SetTextSize(0.025);
			la2->Draw();
		}
	}	/// End of Loop

	gc->SetYLabel_Size(.015);
	gc->SetXLabel_Size(.02);
	double MaxY = gc->GetPadMax();
	if (setMaxY == false) gc->SetYLimits(0, MaxY *1.25);
	else
	{
		gc->SetYLimits(0, Ymax);
	}

	gc->SetXLimits(MinX, MaxX);
	gc->SetXTitle(xaxislabel);
	gc->SetYTitleSize(25);
	gc->SetYTitle(zaxislabel_units);
	gc->SetHistTexts();
	leg->Draw("SAME");
	mnvPlotter.AddHistoTitle(histotitle, .04);
	gc->Modified();
	gc->ResetPads();
	gc->Print(pdf_label);
	delete gc;

}

/////////////////////////////////////////////////
void Plot2MC_ErrorBand2D_ProjX(PlotUtils::MnvH2D *mc1, char *mc1_legendName,
	PlotUtils::MnvH2D *mc2, char *mc2_legendName,
	char *pdf_label, char *histotitle, char *xaxislabel,
	char *yaxislabel, char *zaxislabel_units,
	double Ymax, bool setMaxY, bool doMultipliers,
	std::vector<double> XMultipliers,
	bool statPlusSysDATA, bool statPlusSysMC,
	bool do_bin_width_norm, bool useHistTitles, double text_size)
{
	PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);

	PlotUtils::MnvH2D *mcHist1 = mc1->Clone("mcHist_clone");
	PlotUtils::MnvH2D *mcHist2 = mc2->Clone("mcHist_clone");
	PlotUtils::MnvH1D *datahistPlaceholder = new PlotUtils::MnvH1D("adsf", " ", nbins, xmin, xmax);
	int NDF_2d;

	int nbins_X = mcHist1->GetNbinsX();
	int nbins_Y = mcHist1->GetNbinsY();

	double MinX = mcHist1->GetYaxis()->GetBinLowEdge(1);
	double MaxX = 1.2 *mcHist1->GetYaxis()->GetBinLowEdge(nbins_Y);

	int nbins_X_mc = mcHist1->GetNbinsX();
	int nbins_Y_mc = mcHist1->GetNbinsY();

	TLegend *leg = new TLegend(0.43, 0.1, 0.98, 0.3);

	leg->SetFillStyle(0);
	leg->SetBorderSize(0);
	leg->SetTextSize(0.025);
	leg->SetNColumns(3);

	double maxmax = 1.38* GetMaxFromProjectionX(mcHist1, mcHist2, do_bin_width_norm);
	int grid_x;
	int grid_y;
	int Nbins;
	std::string xaxislabel_string(xaxislabel);

	grid_x = sqrt(nbins_Y) + 1;
	grid_y = nbins_Y / (grid_x - 1);
	Nbins = mcHist1->GetNbinsY();

	if (DeBug == true) std::cout << nbins_X - grid_x * grid_y << std::endl;
	if (DeBug == true) std::cout << "Plotting plotYAxis1D with a grid of " << nbins_X << "\t" << nbins_Y << "\t" << grid_x << "\t" << grid_y << std::endl;

	GridCanvas *gc = new GridCanvas(uniq(), grid_x, grid_y, 800, 500);
	TCanvas cE("c1", "c1");
	gc->SetRightMargin(0.06);
	gc->SetLeftMargin(0.06);
	gc->ResetPads();

	for (int i = 1; i <= Nbins; ++i)
	{
		PlotUtils::MnvH1D *hMCxproj1 =
			mcHist1->ProjectionX(uniq(), i, i)->Clone();

		PlotUtils::MnvH1D *hMCxproj2 =
			mcHist2->ProjectionX(uniq(), i, i)->Clone();

		hMCxproj1->SetMaximum(maxmax);
		hMCxproj2->SetMaximum(maxmax);

		if (doMultipliers == true)
		{
			hMCxproj1->Scale(XMultipliers.at(i - 1));
			hMCxproj2->Scale(XMultipliers.at(i - 1));
		}

		if (do_bin_width_norm == true)
		{
			hMCxproj1->Scale(1., "width");
			hMCxproj2->Scale(1., "width");
		}

		hMCxproj1->SetMarkerStyle(0);
		hMCxproj1->SetLineColor(mnvPlotter.mc_color);
		hMCxproj1->SetLineWidth(mnvPlotter.mc_line_width);
		hMCxproj1->SetLineStyle(mnvPlotter.mc_line_style);
		hMCxproj1->SetFillStyle(mnvPlotter.mc_error_style);
		hMCxproj2->SetMarkerStyle(0);
		hMCxproj2->SetLineColor(kBlue);
		hMCxproj2->SetLineWidth(mnvPlotter.mc_line_width);
		hMCxproj2->SetLineStyle(mnvPlotter.mc_line_style);
		hMCxproj2->SetFillStyle(mnvPlotter.mc_error_style);

		if (i == 1)
		{
			leg->AddEntry(hMCxproj1, mc1_legendName, "fl");
			leg->AddEntry(hMCxproj2, mc2_legendName, "fl");
		}

		gc->cd(i);
		mnvPlotter.axis_label_size = 0.02;
		mnvPlotter.legend_text_size = 0.02;
		mnvPlotter.data_marker_size = 0.3;
		const Double_t mcScale = 1.0;
		mnvPlotter.axis_maximum = maxmax;
		if(setMaxY==true) mnvPlotter.axis_maximum =Ymax;
		//mnvPlotter.mc_error_color_stack=kRed;
		//mnvPlotter.mc_error_color_stack=kRed;
		hMCxproj1->SetLineWidth(2);
		hMCxproj1->SetLineColor(2);
		mnvPlotter.draw_normalized_to_bin_width = false;
		const bool covAreaNormalize = false;
		const bool statPlusSys = false;
		const bool isSmooth = false;

		mnvPlotter.DrawDataMCWithErrorBand(			datahistPlaceholder,
			hMCxproj1,
			1.0,
			"N",
			false,	//default is to use Data/MC/Background
			NULL,
			NULL,
			covAreaNormalize,
			statPlusSys,
			isSmooth
	);

		//  mnvPlotter.DrawDataMCWithErrorBand(		//    datahistPlaceholder,
		//    hMCxproj2,
		//    1.0,
		//    "N",
		//    false, 	//default is to use Data/MC/Background
		//    NULL,
		//    NULL,
		//    covAreaNormalize, 		//    statPlusSys, 		//    isSmooth
		// );

		hMCxproj2->Draw("SAME");
		//drawBinRange(dataHist_clone, 2, i, yaxislabel, ".2f", false);
		drawBinRange(mcHist1, 1, i, yaxislabel, text_size, ".2f", false);
		if (i == 1) mnvPlotter.WritePreliminary("TL", .015, -.01, -.115, false);
		if (doMultipliers && XMultipliers.at(i - 1) != 1)
		{
			auto pad = gc->cd(i);
			TLatex *la2 = new TLatex(1 - pad->GetRightMargin() - 0.03,
				1 - pad->GetTopMargin() - 0.04,
				TString::Format("#times %.1f", XMultipliers.at(i - 1)));
			la2->SetTextAlign(33);	// top right
			la2->SetNDC();
			la2->SetTextFont(42);
			la2->SetTextSize(0.025);
			la2->Draw();
		}

		int ndf_panel;
		double Chisqt_panel = mnvPlotter.Chi2DataMC(hMCxproj2, hMCxproj1, ndf_panel);
		TLatex *Chisqt_latex = new TLatex(gPad->GetLeftMargin() + .01,
			1 - gPad->GetTopMargin() - 0.035,
			TString::Format("#chi^{2}/ndf = %.1f / %i = %.1f", Chisqt_panel, ndf_panel, Chisqt_panel / ndf_panel));
		Chisqt_latex->SetTextAlign(13);	// top left
		Chisqt_latex->SetNDC();
		Chisqt_latex->SetTextFont(42);
		Chisqt_latex->SetTextSize(text_size *.8);
		Chisqt_latex->SetTextColor(kBlue);
		Chisqt_latex->Draw();
	}	/// End of Loop
	char chi_label[1024];

	//sprintf(chi_label, "#chi^{2}/ndf = %.1f / %i = %.1f", chi2_2d,   NDF_2d, chi2_2d /   NDF_2d);
	//leg -> AddEntry((TObject*)0, chi_label, "");

	gc->SetYLabel_Size(.015);
	gc->SetXLabel_Size(.02);
	double MaxY = gc->GetPadMax();
	if (setMaxY == false) gc->SetYLimits(0, MaxY *1.25);
	else
	{
		gc->SetYLimits(0, Ymax);
	}

	gc->SetXLimits(MinX, MaxX);
	gc->SetXTitle(xaxislabel);
	gc->SetYTitleSize(25);
	gc->SetYTitle(zaxislabel_units);
	gc->SetHistTexts();
	leg->Draw("SAME");
	mnvPlotter.AddHistoTitle(histotitle, .04);
	gc->Modified();
	gc->ResetPads();
	gc->Print(pdf_label);
	delete gc;

}

/////////////////////////////////////////////////
void Plot2D_FractionError_ProjX(PlotUtils::MnvH2D *HistInput,
	char *pdf_label, char *histotitle, char *xaxislabel,
	char *yaxislabel,
	double Ymax,
	double text_size)
{
	PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
	PlotUtils::MnvH2D *Hist = HistInput->Clone("mcHist_clone");
	mnvPlotter.mc_line_width = 2;
	int nbins_X = Hist->GetNbinsX();
	int nbins_Y = Hist->GetNbinsY();
	double MinX = Hist->GetXaxis()->GetBinLowEdge(1);
	double MaxX = 1.2 *Hist->GetXaxis()->GetBinLowEdge(nbins_X);
	TLegend * leg;

	//  std::cout<<"nbins_X = " << nbins_X << std::endl;
	//  std::cout<<"nbins_Y = " << nbins_Y << std::endl;

	//double maxmax = 1.2 *dataHist->GetMaximum();
	//double maxmax = 1.2* GetMaxFromProjectionX(dataHist, mcHist_clone, do_bin_width_norm);
	int grid_x;
	int grid_y;
	int Nbins;
	std::string xaxislabel_string(xaxislabel);

	grid_x = sqrt(nbins_Y) + 1;
	grid_y = nbins_Y / (grid_x - 1);
	Nbins = Hist->GetNbinsY();

	if (DeBug == true) std::cout << nbins_X - grid_x * grid_y << std::endl;
	if (DeBug == true) std::cout << "Plotting plotYAxis1D with a grid of " << nbins_X << "\t" << nbins_Y << "\t" << grid_x << "\t" << grid_y << std::endl;

	if (Nbins == 5)
	{
		leg = new TLegend(0.75, 0.1, 0.98, 0.5);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextSize(0.015);
		leg->SetNColumns(1);
	}
	else
	{
		leg = new TLegend(0.43, 0.1, 0.98, 0.3);

		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextSize(0.025);
		leg->SetNColumns(3);
	}

	GridCanvas *gc = new GridCanvas(uniq(), grid_x, grid_y, 800, 500);
	TCanvas cE("c1", "c1");
	gc->SetRightMargin(0.06);
	gc->SetLeftMargin(0.06);
	gc->ResetPads();

	for (int i = 1; i <= Nbins; ++i)
	{
		//bins.push_back(i);

		PlotUtils::MnvH1D *Hist_X_proj =
			Hist->ProjectionX(uniq(), i, i)->Clone();
		//Hist_X_proj->SetMaximum(setMaxY);
		gc->cd(i);
		mnvPlotter.axis_label_size = 0.02;
		const Double_t mcScale = 1.0;
		const std::string &legPos = "N";
		mnvPlotter.axis_maximum = Ymax;
		mnvPlotter.draw_normalized_to_bin_width = false;
		if (i == 1) mnvPlotter.DrawErrorSummary(Hist_X_proj, *leg, "N", true, true, .00001, false, "", true, "", false);
		else mnvPlotter.DrawErrorSummary(Hist_X_proj, "N", true, true, .00001, false, "", true, "", false);

		drawBinRange(Hist, 2, i, yaxislabel, text_size, ".2f", false);

		if (i == 1) mnvPlotter.WritePreliminary("TL", .015, -.01, -.115, false);

		/* if(doMultipliers && XMultipliers.at(i-1)!=1){
		    auto pad = gc->cd(i);
		    TLatex* la2=new TLatex(1-pad->GetRightMargin()-0.03,
		                           1-pad->GetTopMargin()-0.04,
		                           TString::Format("#times %.1f", XMultipliers.at(i-1)));
		    la2->SetTextAlign(33);	// top right
		    la2->SetNDC();
		    la2->SetTextFont(42);
		    la2->SetTextSize(0.025);
		    la2->Draw();
		  }*/

	}	/// End of Loop

	gc->SetYLabel_Size(.015);
	gc->SetXLabel_Size(.02);
	gc->SetYLimits(0, Ymax *1.25);
	gc->SetXLimits(MinX, MaxX);
	gc->SetXTitle(xaxislabel);
	gc->SetYTitleSize(25);
	gc->SetYTitle("Fractional Uncertainty");
	gc->SetHistTexts();
	leg->Draw("SAME");
	mnvPlotter.AddHistoTitle(histotitle, .04);
	gc->Modified();
	gc->ResetPads();
	gc->Print(pdf_label);
	delete gc;

}

/////////////////////////////////////////////////
void Plot2D_FractionError_ProjX_Group(PlotUtils::MnvH2D *HistInput,
	char *pdf_label, char *histotitle, char *xaxislabel, char *GroupName,
	char *yaxislabel,
	double Ymax,
	double text_size, bool doErrorModelGroups)
{
	PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
	if (doErrorModelGroups == true) MakeModelErrorGroups(mnvPlotter);
	PlotUtils::MnvH2D *Hist = HistInput->Clone("mcHist_clone");
	mnvPlotter.mc_line_width = 2;
	int nbins_X = Hist->GetNbinsX();
	int nbins_Y = Hist->GetNbinsY();
	double MinX = Hist->GetXaxis()->GetBinLowEdge(1);
	double MaxX = 1.2 *Hist->GetXaxis()->GetBinLowEdge(nbins_X);
	TLegend * leg;

	//  std::cout<<"nbins_X = " << nbins_X << std::endl;
	//  std::cout<<"nbins_Y = " << nbins_Y << std::endl;

	//double maxmax = 1.2 *dataHist->GetMaximum();
	//double maxmax = 1.2* GetMaxFromProjectionX(dataHist, mcHist_clone, do_bin_width_norm);
	int grid_x;
	int grid_y;
	int Nbins;
	std::string xaxislabel_string(xaxislabel);

	grid_x = sqrt(nbins_Y) + 1;
	grid_y = nbins_Y / (grid_x - 1);
	Nbins = Hist->GetNbinsY();

	if (DeBug == true) std::cout << nbins_X - grid_x * grid_y << std::endl;
	if (DeBug == true) std::cout << "Plotting plotYAxis1D with a grid of " << nbins_X << "\t" << nbins_Y << "\t" << grid_x << "\t" << grid_y << std::endl;

	if (Nbins == 5)
	{
		leg = new TLegend(0.75, 0.1, 0.98, 0.5);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextSize(0.015);
		leg->SetNColumns(1);
	}
	else
	{
		leg = new TLegend(0.43, 0.1, 0.98, 0.3);

		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextSize(0.02);
		leg->SetNColumns(3);
	}

	GridCanvas *gc = new GridCanvas(uniq(), grid_x, grid_y, 800, 500);
	TCanvas cE("c1", "c1");
	gc->SetRightMargin(0.06);
	gc->SetLeftMargin(0.06);
	gc->ResetPads();

	for (int i = 1; i <= Nbins; ++i)
	{
		//bins.push_back(i);

		PlotUtils::MnvH1D *Hist_X_proj =
			Hist->ProjectionX(uniq(), i, i)->Clone();
		//Hist_X_proj->SetMaximum(setMaxY);
		gc->cd(i);
		mnvPlotter.axis_label_size = 0.02;
		const Double_t mcScale = 1.0;
		const std::string &legPos = "N";
		mnvPlotter.axis_maximum = Ymax;
		mnvPlotter.draw_normalized_to_bin_width = false;
		if (i == 1) mnvPlotter.DrawErrorSummary(Hist_X_proj, *leg, "N", true, true, .00001, false, GroupName, true, "", false);
		else mnvPlotter.DrawErrorSummary(Hist_X_proj, "N", true, true, .00001, false, GroupName, true, "", false);

		drawBinRange(Hist, 2, i, yaxislabel, text_size, ".2f", false);

		if (i == 1) mnvPlotter.WritePreliminary("TL", .015, -.01, -.115, false);

		/* if(doMultipliers && XMultipliers.at(i-1)!=1){
		    auto pad = gc->cd(i);
		    TLatex* la2=new TLatex(1-pad->GetRightMargin()-0.03,
		                           1-pad->GetTopMargin()-0.04,
		                           TString::Format("#times %.1f", XMultipliers.at(i-1)));
		    la2->SetTextAlign(33);	// top right
		    la2->SetNDC();
		    la2->SetTextFont(42);
		    la2->SetTextSize(0.025);
		    la2->Draw();
		  }*/

	}	/// End of Loop

	gc->SetYLabel_Size(.02);
	gc->SetXLabel_Size(.02);
	gc->SetYLimits(0, Ymax *1.25);
	gc->SetXLimits(MinX, MaxX);
	gc->SetXTitle(xaxislabel);
	gc->SetYTitleSize(20);
	gc->SetYTitle("Fractional Uncertainty");
	gc->SetHistTexts();
	leg->Draw("SAME");
	mnvPlotter.AddHistoTitle(histotitle, .04);
	gc->Modified();
	gc->ResetPads();
	gc->Print(pdf_label);
	delete gc;

}

/////////////////////////////////////////////////
void PlotFractionofEvents2D_ProjY(PlotUtils::MnvH2D *mc, const TObjArray *stack,
		std::vector<int> fillColors, char *dataname, char *dataname_total,
		char *pdf_label, char *histotitle, char *xaxislabel,
		char *yaxislabel, char *zaxislabel_units
)
{
	PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
	TH2 *mc_clone = mc->Clone("mcth1");
	PlotUtils::MnvH2D *mcHist_clone = mc->Clone("mcHist_clone");
	double CompleteTotal = mcHist_clone->Integral();
	int nVars = stack->GetEntries();
	int nbins_X = mcHist_clone->GetNbinsX();
	int nbins_Y = mcHist_clone->GetNbinsY();
	std::cout << "The NEntries for TObjArray: " << nVars << std::endl;
	int nbins_X_mc = mcHist_clone->GetNbinsX();
	int nbins_Y_mc = mcHist_clone->GetNbinsY();

	TLegend *leg = new TLegend(0.43, 0.1, 0.98, 0.3);

	leg->SetFillStyle(0);
	leg->SetBorderSize(0);
	leg->SetTextSize(0.025);
	leg->SetNColumns(3);

	//  std::cout<<"nbins_X = " << nbins_X << std::endl;
	//  std::cout<<"nbins_Y = " << nbins_Y << std::endl;
	//  std::cout<<"nbins_X_mc = " << nbins_X_mc << std::endl;
	//  std::cout<<"nbins_Y_mc = " << nbins_Y_mc << std::endl;

	int grid_x;
	int grid_y;
	int Nbins;
	std::string xaxislabel_string(xaxislabel);

	//   grid_x = sqrt(nbins_Y)+1;
	// grid_y = nbins_Y/(grid_x-1);
	// Nbins = dataHist->GetNbinsY();

	grid_x = sqrt(nbins_X) + 1;
	grid_y = nbins_X / (grid_x - 1);
	Nbins = mcHist_clone->GetNbinsX();

	if (DeBug == true) std::cout << nbins_X - grid_x * grid_y << std::endl;
	if (DeBug == true) std::cout << "Plotting plotYAxis1D with a grid of " << nbins_X << "\t" << nbins_Y << "\t" << grid_x << "\t" << grid_y << std::endl;

	std::vector<int> bins;	// = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	GridCanvas *gc = new GridCanvas(uniq(), grid_x, grid_y, 800, 550);
	TCanvas cE("c1", "c1");
	gc->SetRightMargin(0.01);
	gc->SetLeftMargin(0.1);
	gc->ResetPads();

	for (int i = 1; i <= Nbins; ++i)
	{
		bins.push_back(i);

		TObjArray *mcprojyArr = new TObjArray();

		PlotUtils::MnvH1D *hMCyproj =
			mcHist_clone->ProjectionY(uniq(), i, i)->Clone();
		PlotUtils::MnvH1D *hMCyproj_clone = (PlotUtils::MnvH1D *) hMCyproj->Clone("hMCyproj_clone");

		hMCyproj->ClearAllErrorBands();

		double area = hMCyproj->Integral(1, hMCyproj->GetNbinsX());
		hMCyproj->Scale(1.0 / area);
		hMCyproj_clone->Scale(1.0 / CompleteTotal);

		hMCyproj->SetMaximum(1.25);
		hMCyproj->SetMarkerStyle(20);
		hMCyproj_clone->SetMarkerStyle(21);
		hMCyproj_clone->SetMarkerSize(.5);
		if (i == 1)
		{
			leg->AddEntry(hMCyproj, dataname, "p");

			leg->AddEntry(hMCyproj_clone, dataname_total, "p");
		}

		for (int iHist = 0; iHist < nVars; ++iHist)
		{
			PlotUtils::MnvH2D *mcHist_stack = (PlotUtils::MnvH2D *) stack->At(iHist)->Clone("mcHist_stack");
			//int ndf;
			std::string words = mcHist_stack->GetTitle();
			std::cout << "iHist  = " << iHist << " words = " << words << std::endl;

			PlotUtils::MnvH1D *mcHist_stack_ProjectionY = mcHist_stack->ProjectionY(uniq(), i, i)->Clone();

			mcHist_stack_ProjectionY->SetTitle(words.c_str());
			mcHist_stack_ProjectionY->SetXTitle("");

			mcHist_stack_ProjectionY->SetFillStyle(1001);
			mcHist_stack_ProjectionY->SetFillColor(fillColors.at(iHist));
			mcHist_stack_ProjectionY->SetLineWidth(0);

			if (i == 1)
			{
				char words_char[words.length() + 1];
				strcpy(words_char, words.c_str());
				leg->AddEntry(mcHist_stack_ProjectionY, words_char, "f");
			}

			mcprojyArr->Add(mcHist_stack_ProjectionY);
		}

		gc->cd(i);
		mnvPlotter.axis_label_size = 0.02;
		mnvPlotter.legend_text_size = 0.02;
		mnvPlotter.data_marker_size = 0.4;
		const Int_t mcFillStyle = 1001;
		const Double_t mcScale = 1.0;
		//const std::string& legPos = "N";
		mnvPlotter.axis_maximum = 1.35;

		BinNormalizeTOFractionOF_Events_mvnH1D(*mcprojyArr);

		mnvPlotter.mc_line_width = 0;
		mnvPlotter.DrawDataStackedMC(hMCyproj, mcprojyArr, 1.0, "N", "", -1, -1, 1001);
		hMCyproj_clone->Draw("SAME E1 X0");

		drawBinRange(mc_clone, 1, i, xaxislabel, ".1f", false);

		if (i == 1) mnvPlotter.WritePreliminary("TL", .015, -.01, -.06, false);
	}	/// End of Loop

	// gc->DrawBinRanges(dataHist, 2, bins, dataHist->GetYaxis()->GetTitle(), binCenter, .02);
	gc->SetYLabel_Size(.015);
	gc->SetXLabel_Size(.02);
	gc->SetYLimits(0, 1.15);
	gc->SetXTitle(yaxislabel);
	gc->SetYTitleSize(25);
	gc->SetYTitle(zaxislabel_units);
	gc->SetHistTexts();
	leg->Draw("SAME");
	mnvPlotter.AddHistoTitle(histotitle, .04);
	gc->Modified();
	gc->Print(pdf_label);

	delete gc;

}

//////////////////////////////////////////////////
void PlotFractionofEvents2D_ProjX(PlotUtils::MnvH2D *mc, const TObjArray *stack,
		std::vector<int> fillColors, char *dataname, char *dataname_total,
		char *pdf_label, char *histotitle, char *xaxislabel,
		char *yaxislabel, char *zaxislabel_units
)
{
	PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
	TH2 *mc_clone = mc->Clone("mcth1");
	PlotUtils::MnvH2D *mcHist_clone = mc->Clone("mcHist_clone");
	double CompleteTotal = mcHist_clone->Integral();
	int nVars = stack->GetEntries();
	int nbins_X = mcHist_clone->GetNbinsX();
	int nbins_Y = mcHist_clone->GetNbinsY();
	std::cout << "The NEntries for TObjArray: " << nVars << std::endl;
	int nbins_X_mc = mcHist_clone->GetNbinsX();
	int nbins_Y_mc = mcHist_clone->GetNbinsY();

	//std::cout<<"nbins_X = " << nbins_X << std::endl;
	//std::cout<<"nbins_Y = " << nbins_Y << std::endl;
	//std::cout<<"nbins_X_mc = " << nbins_X_mc << std::endl;
	//std::cout<<"nbins_Y_mc = " << nbins_Y_mc << std::endl;

	int grid_x;
	int grid_y;
	int Nbins;
	std::string xaxislabel_string(xaxislabel);

	//   grid_x = sqrt(nbins_Y)+1;
	// grid_y = nbins_Y/(grid_x-1);
	// Nbins = dataHist->GetNbinsY();

	grid_x = sqrt(nbins_Y) + 1;
	grid_y = nbins_Y / (grid_x - 1);
	Nbins = mcHist_clone->GetNbinsY();

	TLegend * leg;
	if (Nbins == 5 || Nbins == 11)
	{
		leg = new TLegend(0.78, 0.1, 0.98, 0.35);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextSize(0.015);
		leg->SetNColumns(1);
	}
	else
	{
		leg = new TLegend(0.43, 0.1, 0.98, 0.3);

		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextSize(0.025);
		leg->SetNColumns(3);
	}

	if (DeBug == true) std::cout << nbins_X - grid_x * grid_y << std::endl;
	if (DeBug == true) std::cout << "Plotting plotYAxis1D with a grid of " << nbins_X << "\t" << nbins_Y << "\t" << grid_x << "\t" << grid_y << std::endl;

	std::vector<int> bins;	// = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	GridCanvas *gc = new GridCanvas(uniq(), grid_x, grid_y, 800, 550);
	TCanvas cE("c1", "c1");
	gc->SetRightMargin(0.01);
	gc->SetLeftMargin(0.1);
	gc->ResetPads();

	for (int i = 1; i <= Nbins; ++i)
	{
		bins.push_back(i);

		TObjArray *mcprojyArr = new TObjArray();

		PlotUtils::MnvH1D *hMCxproj =
			mcHist_clone->ProjectionX(uniq(), i, i)->Clone();
		PlotUtils::MnvH1D *hMCxproj_clone = (PlotUtils::MnvH1D *) hMCxproj->Clone("hMCxproj_clone");

		hMCxproj->ClearAllErrorBands();

		double area = hMCxproj->Integral(1, hMCxproj->GetNbinsX());
		hMCxproj->Scale(1.0 / area);
		hMCxproj_clone->Scale(1.0 / CompleteTotal);

		hMCxproj->SetMaximum(1.25);
		hMCxproj->SetMarkerStyle(20);
		hMCxproj_clone->SetMarkerStyle(21);
		hMCxproj_clone->SetMarkerSize(.5);
		if (i == 1)
		{
			leg->AddEntry(hMCxproj, dataname, "p");

			leg->AddEntry(hMCxproj_clone, dataname_total, "p");
		}

		for (int iHist = 0; iHist < nVars; ++iHist)
		{
			PlotUtils::MnvH2D *mcHist_stack = (PlotUtils::MnvH2D *) stack->At(iHist)->Clone("mcHist_stack");
			//int ndf;
			std::string words = mcHist_stack->GetTitle();
			std::cout << "iHist  = " << iHist << " words = " << words << std::endl;

			PlotUtils::MnvH1D *mcHist_stack_ProjectionY = mcHist_stack->ProjectionX(uniq(), i, i)->Clone();

			mcHist_stack_ProjectionY->SetTitle(words.c_str());
			mcHist_stack_ProjectionY->SetXTitle("");

			mcHist_stack_ProjectionY->SetFillStyle(1001);
			mcHist_stack_ProjectionY->SetFillColor(fillColors.at(iHist));
			mcHist_stack_ProjectionY->SetLineWidth(0);

			if (i == 1)
			{
				char words_char[words.length() + 1];
				strcpy(words_char, words.c_str());
				leg->AddEntry(mcHist_stack_ProjectionY, words_char, "f");
			}

			mcprojyArr->Add(mcHist_stack_ProjectionY);
		}

		gc->cd(i);
		mnvPlotter.axis_label_size = 0.02;
		mnvPlotter.legend_text_size = 0.02;
		mnvPlotter.data_marker_size = 0.4;
		const Int_t mcFillStyle = 1001;
		const Double_t mcScale = 1.0;
		//const std::string& legPos = "N";
		mnvPlotter.axis_maximum = 1.35;

		BinNormalizeTOFractionOF_Events_mvnH1D(*mcprojyArr);

		mnvPlotter.mc_line_width = 0;
		mnvPlotter.DrawDataStackedMC(hMCxproj, mcprojyArr, 1.0, "N", "", -1, -1, 1001);
		hMCxproj_clone->Draw("SAME E1 X0");

		drawBinRange(mc_clone, 2, i, yaxislabel, ".2f", false);

		if (i == 1) mnvPlotter.WritePreliminary("TL", .015, -.01, -.06, false);
	}	/// End of Loop

	// gc->DrawBinRanges(dataHist, 2, bins, dataHist->GetYaxis()->GetTitle(), binCenter, .02);
	gc->SetYLabel_Size(.015);
	gc->SetXLabel_Size(.02);
	gc->SetYLimits(0, 1.15);
	gc->SetXTitle(yaxislabel);
	gc->SetYTitleSize(25);
	gc->SetYTitle(zaxislabel_units);
	gc->SetHistTexts();
	leg->Draw("SAME");
	mnvPlotter.AddHistoTitle(histotitle, .04);
	gc->Modified();
	gc->Print(pdf_label);

	delete gc;

}

//////////////////////////////////////////////////
void PlotDataMC_Migration_ProjX(PlotUtils::MnvH2D *migration, PlotUtils::MnvH2D *reco, PlotUtils::MnvH2D *truth, std::vector<double> ProjectBinning,
	char *pdf_label, char *histotitle, char *xaxislabel,
	char *yaxislabel, char *zaxislabel_units,
	double Zmax, MnvPlotter *mnvPlotter, TCanvas *cE, int normtype, double txtsize, double markertxtsize, bool doBinN)
{
	//PlotUtils::MnvPlotter *mnvPlotter = new MnvPlotter();
	//  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
	PlotUtils::MnvH2D *h_migration = migration->Clone("h_migration");
	PlotUtils::MnvH2D *h_reco = reco->Clone("h_reco");
	PlotUtils::MnvH2D *h_truth = truth->Clone("h_truth");

	//GetMigration_Projection_Y_forBinN(MnvH2D *migration, MnvH2D *h_reco, MnvH2D *h_truth, std::vector<double> ProjectBinning, int BinN_project);

	int nbins_X = h_reco->GetNbinsX();
	int nbins_Y = h_reco->GetNbinsY();

	TLegend *leg = new TLegend(0.43, 0.1, 0.98, 0.3);

	leg->SetFillStyle(0);
	leg->SetBorderSize(0);
	leg->SetTextSize(0.025);
	leg->SetNColumns(3);

	//std::cout<<"nbins_X = " << nbins_X << std::endl;
	//std::cout<<"nbins_Y = " << nbins_Y << std::endl;

	int grid_x;
	int grid_y;
	int Nbins;
	std::string xaxislabel_string(xaxislabel);

	grid_x = sqrt(nbins_Y) + 1;
	grid_y = nbins_Y / (grid_x - 1);
	Nbins = h_reco->GetNbinsY();

	if (DeBug == true) std::cout << nbins_X - grid_x * grid_y << std::endl;
	if (DeBug == true) std::cout << "Plotting plotYAxis1D with a grid of " << nbins_X << "\t" << nbins_Y << "\t" << grid_x << "\t" << grid_y << std::endl;

	GridCanvas *gc = new GridCanvas(uniq(), grid_x, grid_y, 800, 750);
	//TCanvas cE("c1", "c1");
	//TCanvas *cE = new TCanvas("can");
	gc->SetRightMargin(0.08);
	gc->SetLeftMargin(0.06);
	gc->SetBottomMargin(.1);
	gc->ResetPads();

	for (int i = 1; i <= nbins_Y; ++i)
	{
		//MnvH2D *ProjectMig = GetMigration_Projection_X_forBinN(h_migration, h_reco, h_truth, ProjectBinning, i);
		//ProjectMig->SetMaximum(Zmax);
		gc->cd(i);

		MnvH2D *h_return = new MnvH2D("h_return", "h_return", ProjectBinning.size() - 1, ProjectBinning.data(), ProjectBinning.size() - 1, ProjectBinning.data());

		for (int XTruthbinN = 1; XTruthbinN <= h_truth->GetNbinsX(); XTruthbinN++)
		{
			for (int XRecobinN = 1; XRecobinN <= h_reco->GetNbinsX(); XRecobinN++)
			{
				int globalBin = GetGlobalBinNFrom2DMig_BinN(migration, h_reco, h_truth, XRecobinN, i, XTruthbinN, i);
				double content = migration->GetBinContent(globalBin);

				int Global_hreturn_binN = XTruthbinN *(h_return->GetNbinsX() + 2) + XRecobinN;	// Assuming Truth is Y axis
				//std::cout<< "Global_hreturn_binN = " << Global_hreturn_binN << " content = " << content << std::endl;
				h_return->AddBinContent(Global_hreturn_binN, content);
			}
		}

		h_return->SetMaximum(Zmax);
		if (doBinN == true)
		{
			DrawMagration_heatMap_MigBinN(h_return, yaxislabel, "",
				cE, mnvPlotter, h_reco, i, 2, normtype, txtsize, markertxtsize, Zmax);
		}
		else
		{
			DrawMagration_heatMap_LabelBinNumber_new(h_return, yaxislabel, "",
				"title", pdf_label, cE, mnvPlotter, h_reco, i, 2, normtype, txtsize);
		}

		if (i == 1) mnvPlotter->WritePreliminary("TL", .015, -.02, -.025, false);
	}	/// End of Loop

	// gc->DrawBinRanges(dataHist, 2, bins, dataHist->GetYaxis()->GetTitle(), binCenter, .02);
	gc->SetYLabel_Size(.01);
	gc->SetXLabel_Size(.01);
	//  double MaxY = gc->GetPadMax();
	//if(setMaxY==false) gc->SetYLimits(0,MaxY*1.25);
	//else {gc->SetYLimits(0,Ymax);}

	//gc->SetXLimits(MinX,MaxX);
	gc->SetXTitleSize(25);
	gc->SetXTitle(xaxislabel);
	gc->SetYTitleSize(25);
	gc->SetYTitle(zaxislabel_units);
	gc->SetHistTexts();
	//leg->Draw("SAME");
	mnvPlotter->AddHistoTitle(histotitle, .04);
	gc->Modified();
	gc->ResetPads();
	gc->Print(pdf_label);
	delete gc;

}

/////////////////////////////////////////////////
void PlotDataMC_Migration_ProjY(PlotUtils::MnvH2D *migration, PlotUtils::MnvH2D *reco, PlotUtils::MnvH2D *truth, std::vector<double> ProjectBinning,
	char *pdf_label, char *histotitle, char *xaxislabel,
	char *yaxislabel, char *zaxislabel_units,
	double Zmax, MnvPlotter *mnvPlotter, TCanvas *cE, int normtype, double txtsize, double markertxtsize, bool doBinN)
{
	//PlotUtils::MnvPlotter *mnvPlotter = new MnvPlotter();
	//  PlotUtils::MnvPlotter mnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
	PlotUtils::MnvH2D *h_migration = migration->Clone("h_migration");
	PlotUtils::MnvH2D *h_reco = reco->Clone("h_reco");
	PlotUtils::MnvH2D *h_truth = truth->Clone("h_truth");

	//GetMigration_Projection_Y_forBinN(MnvH2D *migration, MnvH2D *h_reco, MnvH2D *h_truth, std::vector<double> ProjectBinning, int BinN_project);

	int nbins_X = h_reco->GetNbinsX();
	int nbins_Y = h_reco->GetNbinsY();

	TLegend *leg = new TLegend(0.43, 0.1, 0.98, 0.3);

	leg->SetFillStyle(0);
	leg->SetBorderSize(0);
	leg->SetTextSize(0.025);
	leg->SetNColumns(3);

	//  std::cout<<"nbins_X = " << nbins_X << std::endl;
	//  std::cout<<"nbins_Y = " << nbins_Y << std::endl;

	int grid_x;
	int grid_y;
	int Nbins;
	std::string xaxislabel_string(xaxislabel);

	grid_x = sqrt(nbins_X) + 1;
	grid_y = nbins_X / (grid_x - 1);
	Nbins = h_reco->GetNbinsX();

	if (DeBug == true) std::cout << nbins_X - grid_x * grid_y << std::endl;
	if (DeBug == true) std::cout << "Plotting plotYAxis1D with a grid of " << nbins_X << "\t" << nbins_Y << "\t" << grid_x << "\t" << grid_y << std::endl;

	GridCanvas *gc = new GridCanvas(uniq(), grid_x, grid_y, 800, 750);
	//TCanvas cE("c1", "c1");
	//TCanvas *cE = new TCanvas("can");
	gc->SetRightMargin(0.08);
	gc->SetLeftMargin(0.06);
	gc->SetBottomMargin(.1);
	gc->ResetPads();

	for (int i = 1; i <= nbins_X; ++i)
	{
		//MnvH2D *ProjectMig = GetMigration_Projection_X_forBinN(h_migration, h_reco, h_truth, ProjectBinning, i);
		//ProjectMig->SetMaximum(Zmax);
		gc->cd(i);

		MnvH2D *h_return = new MnvH2D("h_return", "h_return", ProjectBinning.size() - 1, ProjectBinning.data(), ProjectBinning.size() - 1, ProjectBinning.data());

		//GetMigration_Projection_Y_forBinN_input(h_return, CrossSection_map[mvnreponse_Mig], h_reco,h_truth, 1);

		for (int XTruthbinN = 1; XTruthbinN <= h_truth->GetNbinsY(); XTruthbinN++)
		{
			for (int XRecobinN = 1; XRecobinN <= h_reco->GetNbinsY(); XRecobinN++)
			{
				int globalBin = GetGlobalBinNFrom2DMig_BinN(migration, h_reco, h_truth, i, XRecobinN, i, XTruthbinN);
				double content = migration->GetBinContent(globalBin);

				int Global_hreturn_binN = XTruthbinN *(h_return->GetNbinsX() + 2) + XRecobinN;	// Assuming Truth is Y axis
				//  std::cout<< "Global_hreturn_binN = " << Global_hreturn_binN << " content = " << content << std::endl;
				h_return->AddBinContent(Global_hreturn_binN, content);
			}
		}

		h_return->SetMaximum(Zmax);

		//  DrawMagration_heatMap_LabelBinNumber_new(h_return, yaxislabel, "",
		//    "title", pdf_label, cE, mnvPlotter ,h_reco, i, 1, normtype, txtsize);

		if (doBinN == true)
		{
			DrawMagration_heatMap_MigBinN(h_return, yaxislabel, "",
				cE, mnvPlotter, h_reco, i, 1, normtype, txtsize, markertxtsize, Zmax);
		}
		else
		{
			DrawMagration_heatMap_LabelBinNumber_new(h_return, yaxislabel, "",
				"title", pdf_label, cE, mnvPlotter, h_reco, i, 1, normtype, txtsize);
		}

		if (i == 1) mnvPlotter->WritePreliminary("TL", .015, -.02, -.025, false);
	}	/// End of Loop

	// gc->DrawBinRanges(dataHist, 2, bins, dataHist->GetYaxis()->GetTitle(), binCenter, .02);
	gc->SetYLabel_Size(.01);
	gc->SetXLabel_Size(.01);
	//  double MaxY = gc->GetPadMax();
	//if(setMaxY==false) gc->SetYLimits(0,MaxY*1.25);
	//else {gc->SetYLimits(0,Ymax);}

	//gc->SetXLimits(MinX,MaxX);
	gc->SetXTitleSize(25);
	gc->SetXTitle(xaxislabel);
	gc->SetYTitleSize(25);
	gc->SetYTitle(zaxislabel_units);
	gc->SetHistTexts();
	//leg->Draw("SAME");
	mnvPlotter->AddHistoTitle(histotitle, .04);
	gc->Modified();
	gc->ResetPads();
	gc->Print(pdf_label);
	delete gc;

}

void Draw2DPlots_Panel(ME_playlist_TFileMAP Full_Map, ME_playlist_TFileMAP Full_Data_Map,
	ME_playlist_TFileMAP Empty_Map, ME_playlist_TFileMAP Empty_Data_Map,
	double Full_MC_Full_Data,
	double Empty_MC_Full_Data,
	double Empty_Data_Full_Data,
	char *hist_MCName,
	char *hist_DataName,
	char *xaxis, char *yaxis, char *unitsX, char *unitsY, char *Plot_title, std::vector<double> YMultipliers, std::vector<double> XMultipliers,
	bool do_bin_width_norm, bool statPlusSysDATA, bool statPlusSysMC,
	MnvPlotter *mnvPlotter, TCanvas *can, char *pdf, double XprotextSize, double YprotextSize)
{
	std::string pdf_string(pdf);
	char pdf_char[1024];
	sprintf(pdf_char, "%s.pdf", pdf);
	char ZaxisTitle[1024];
	char Title[1024];

	Playlist_MnvH2D_Map Full_MnvH2D_Map = Constuct_mvnH2DMap_FromME_playlist_TFileMAP(Full_Map, hist_MCName);
	Playlist_MnvH2D_Map Empty_MnvH2D_Map = Constuct_mvnH2DMap_FromME_playlist_TFileMAP(Empty_Map, hist_MCName);

	Playlist_MnvH2D_Map Full_MnvH2D_Data_Map = Constuct_mvnH2DMap_FromME_playlist_TFileMAP(Full_Data_Map, hist_DataName);
	Playlist_MnvH2D_Map Empty_MnvH2D_Data_Map = Constuct_mvnH2DMap_FromME_playlist_TFileMAP(Empty_Data_Map, hist_DataName);

	auto h_Full_Combined = Combine_2DHists_fromMAP(Full_MnvH2D_Map, kME1F, "h_Full_Combined");
	auto h_Empty_Combined = Combine_2DHists_fromMAP(Empty_MnvH2D_Map, kME1M, "h_Empty_Combined");

	auto h_Full_Combined_Data = Combine_2DHists_fromMAP(Full_MnvH2D_Data_Map, kME1F, "h_Full_Data_Combined");
	auto h_Empty_Combined_Data = Combine_2DHists_fromMAP(Empty_MnvH2D_Data_Map, kME1M, "h_EmptyData_Combined");

	Full_MnvH2D_Map.clear();
	Empty_MnvH2D_Map.clear();
	Full_MnvH2D_Data_Map.clear();
	Empty_MnvH2D_Data_Map.clear();

	////
	//Scale
	//
	h_Full_Combined->Scale(Full_MC_Full_Data);
	h_Empty_Combined->Scale(Empty_MC_Full_Data);
	h_Empty_Combined_Data->Scale(Empty_Data_Full_Data);

	MnvH2D *h_Full_Combined_clone = (PlotUtils::MnvH2D *) h_Full_Combined->Clone("h_Full_Combined_Clone");
	MnvH2D *h_Empty_Combined_clone = (PlotUtils::MnvH2D *) h_Empty_Combined->Clone("h_Empty_Combined_Clone");

	MnvH2D *h_Full_Combined_Dataclone = (PlotUtils::MnvH2D *) h_Full_Combined_Data->Clone("h_Full_Combined_DataClone");
	MnvH2D *h_Empty_Combined_Dataclone = (PlotUtils::MnvH2D *) h_Empty_Combined_Data->Clone("h_Empty_Combined_DataClone");

	sprintf(ZaxisTitle, "Event /  %s ", unitsY);
	sprintf(Title, "%s[Full][ProjY]", Plot_title);
	PlotDataMC_ErrorBand2D_ProjY(h_Full_Combined_Data, h_Full_Combined,
		pdf, Title, xaxis, yaxis, ZaxisTitle,
		99, false, true, YMultipliers,
		statPlusSysDATA, statPlusSysMC, do_bin_width_norm, false, YprotextSize);

	sprintf(Title, "Fractional Error %s[Full][ProjY]", Plot_title);
	Plot2D_FractionError_ProjY(h_Full_Combined,
		pdf, Title, xaxis, yaxis, .25, .02);

	sprintf(ZaxisTitle, "Event /  %s ", unitsX);
	sprintf(Title, "%s[Full][ProjX]", Plot_title);
	PlotDataMC_ErrorBand2D_ProjX(h_Full_Combined_Data, h_Full_Combined,
		pdf, Title, yaxis, xaxis, ZaxisTitle,
		99, false, true, XMultipliers,
		statPlusSysDATA, statPlusSysMC, do_bin_width_norm, false, XprotextSize);

	sprintf(Title, "Fractional Error %s[Full][ProjX]", Plot_title);
	Plot2D_FractionError_ProjX(h_Full_Combined,
		pdf, Title, xaxis, yaxis, .25, .02);

	sprintf(Title, "%s[Empty][ProjY]", Plot_title);
	sprintf(ZaxisTitle, "Event /  %s ", unitsY);
	PlotDataMC_ErrorBand2D_ProjY(h_Empty_Combined_Data, h_Empty_Combined,
		pdf, Title, xaxis, yaxis, ZaxisTitle,
		99, false, true, YMultipliers,
		statPlusSysDATA, statPlusSysMC, do_bin_width_norm, false, YprotextSize);

	sprintf(Title, "Fractional Error %s[Empty][ProjY]", Plot_title);
	Plot2D_FractionError_ProjY(h_Empty_Combined, pdf, Title, xaxis, yaxis, .25, .02);

	sprintf(Title, "%s[Empty][ProjX]", Plot_title);
	sprintf(ZaxisTitle, "Event /  %s ", unitsX);
	PlotDataMC_ErrorBand2D_ProjX(h_Empty_Combined_Data, h_Empty_Combined,
		pdf, Title, yaxis, xaxis, ZaxisTitle,
		99, false, true, XMultipliers,
		statPlusSysDATA, statPlusSysMC, do_bin_width_norm, false, XprotextSize);

	sprintf(Title, "Fractional Error %s[Empty][ProjY]", Plot_title);
	Plot2D_FractionError_ProjX(h_Empty_Combined, pdf, Title, xaxis, yaxis, .25, .02);

	h_Full_Combined_clone->Add(h_Empty_Combined_clone, -1);
	h_Full_Combined_Dataclone->Add(h_Empty_Combined_Dataclone, -1);

	sprintf(Title, "%s[F-E][ProjY]", Plot_title);
	sprintf(ZaxisTitle, "Event /  %s ", unitsY);
	PlotDataMC_ErrorBand2D_ProjY(h_Full_Combined_Dataclone, h_Full_Combined_clone,
		pdf, Title, xaxis, yaxis, ZaxisTitle,
		99, false, true, YMultipliers,
		statPlusSysDATA, statPlusSysMC, do_bin_width_norm, false, YprotextSize);

	printf(Title, "Fractional Error %s[F-E][ProjY]", Plot_title);
	Plot2D_FractionError_ProjY(h_Empty_Combined, pdf, Title, xaxis, yaxis, .25, .02);

	sprintf(Title, "%s[F-E][ProjX]", Plot_title);
	sprintf(ZaxisTitle, "Event /  %s ", unitsX);
	PlotDataMC_ErrorBand2D_ProjX(h_Full_Combined_Dataclone, h_Full_Combined_clone,
		pdf, Title, yaxis, xaxis, ZaxisTitle,
		99, false, true, XMultipliers,
		statPlusSysDATA, statPlusSysMC, do_bin_width_norm, false, XprotextSize);

}
