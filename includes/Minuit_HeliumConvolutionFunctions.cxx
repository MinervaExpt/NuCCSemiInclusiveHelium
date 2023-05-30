#include "Helium_ConvolutionTool.h"
using namespace std;


Convolution_Tool Convolution_Tool_GLOBAL;
///////////////////////

void SetConvolutionShiftMapTool(Convolution_Tool sbtool_input){
  //std::cout<<"inside setting ConvolutionShiftMapTool for Fitting "<< std::endl;
Convolution_Tool_GLOBAL = sbtool_input;
//std::cout<<"Tool has been SET !! Lets Go! "<<std::endl;
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

double calc_ChiSq_For_ConvolutionTool_CV_Vertex(
Convolution_CryoRegions &CryoRegions,
  double InPut_Alwgt_region1,
  double InPut_Alwgt_region2,
  double InPut_Alwgt_region3,
  double InPut_Alwgt_region4,
   int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1, bool removeFirstandLastBin= true, bool isVertexZ=false)
{
  //std::cout<<"inside:calc_ChiSq_For_ConvolutionTool_CV_Vertex_X"<<std::endl;

    if (!isPartial){
        min_bin = 1;
        max_bin = CryoRegions.Upstream.MnvH1D_data->GetNbinsX();
        if(removeFirstandLastBin==true){min_bin = min_bin + 1; max_bin = max_bin - 1;}
    }
    //std::cout<<"sb_region1.MnvH1D_Vertex_X_data"<<std::endl;
    if(isVertexZ==true){
      max_bin = CryoRegions.Upstream.MnvH1D_data->GetNbinsX();
    }



    if (min_bin == max_bin){
        cout<<"Wrong Range for Fit"<<endl;
        exit(EXIT_FAILURE);
    }

    double ChiSq = 0.0;


    for (int i = min_bin; i <= max_bin; ++i){
        // Get N(Events) in Single Bin
        double err_region1 = CryoRegions.Upstream.MnvH1D_data->GetBinError(i);
        double nData_region1 = CryoRegions.Upstream.MnvH1D_data->GetBinContent(i);
        double err_region2 = CryoRegions.Barrel.MnvH1D_data->GetBinError(i);
        double nData_region2 = CryoRegions.Barrel.MnvH1D_data->GetBinContent(i);
        double err_region3 = CryoRegions.Downstream.MnvH1D_data->GetBinError(i);
        double nData_region3 = CryoRegions.Downstream.MnvH1D_data->GetBinContent(i);
        double err_region4 = CryoRegions.Concave.MnvH1D_data->GetBinError(i);
        double nData_region4 = CryoRegions.Concave.MnvH1D_data->GetBinContent(i);
        double nData = nData_region1 + nData_region2 + nData_region3 + nData_region4;
        double err = err_region1 + err_region2 + err_region3 + err_region4;
        if (nData == 0 ) continue;
        double nHelium_region1 = CryoRegions.Upstream.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region1 = CryoRegions.Upstream.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region1 = CryoRegions.Upstream.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region1 = CryoRegions.Upstream.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region1 = CryoRegions.Upstream.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region1 = InPut_Alwgt_region1 * CryoRegions.Upstream.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        ////
        double nHelium_region2 = CryoRegions.Barrel.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region2 = CryoRegions.Barrel.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region2 = CryoRegions.Barrel.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region2 = CryoRegions.Barrel.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region2 = CryoRegions.Barrel.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region2 = InPut_Alwgt_region2 * CryoRegions.Barrel.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        ///////
        double nHelium_region3 = CryoRegions.Downstream.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region3 = CryoRegions.Downstream.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region3 = CryoRegions.Downstream.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region3 = CryoRegions.Downstream.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region3 = CryoRegions.Downstream.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region3 = InPut_Alwgt_region3 * CryoRegions.Downstream.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        ////
        double nHelium_region4 = CryoRegions.Concave.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region4 = CryoRegions.Concave.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region4 = CryoRegions.Concave.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region4 = CryoRegions.Concave.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region4 = CryoRegions.Concave.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region4 = InPut_Alwgt_region4 * CryoRegions.Concave.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        ////////
        double nHelium = nHelium_region1 + nHelium_region2 + nHelium_region3 + nHelium_region4;
        double nCarbon = nCarbon_region1 + nCarbon_region2 + nCarbon_region3 + nCarbon_region4;
        double nLead = nLead_region1 + nLead_region2 + nLead_region3 + nLead_region4;
        double nIron = nIron_region1 + nIron_region2 + nIron_region3 + nIron_region4;
        double nOther = nOther_region1 + nOther_region2 + nOther_region3 + nOther_region4;
        double nAluminium = nAluminium_region1 + nAluminium_region2 + nAluminium_region3 + nAluminium_region4;
        ///
        // Add All MC and scale them
        double nMC_total = (nHelium + nAluminium + nCarbon + nLead + nIron  + nOther);

        double delta = pow((nData-nMC_total),2) / pow(err,2);
        ChiSq += delta;
      }




    return ChiSq;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

double calc_LOG_ChiSq_For_ConvolutionTool_CV_Vertex(
Convolution_CryoRegions &CryoRegions,
  double InPut_Alwgt_region1,
  double InPut_Alwgt_region2,
  double InPut_Alwgt_region3,
  double InPut_Alwgt_region4,
   int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1, bool removeFirstandLastBin= true, bool isVertexZ=false)
{
    if (!isPartial){
        min_bin = 1;
        max_bin = CryoRegions.Upstream.MnvH1D_data->GetNbinsX();
        if(removeFirstandLastBin==true){min_bin = min_bin + 1; max_bin = max_bin - 1;}
    }

    if(isVertexZ==true){
      max_bin = CryoRegions.Upstream.MnvH1D_data->GetNbinsX();
    }

    if (min_bin == max_bin){
        cout<<"Wrong Range for Fit"<<endl;
        exit(EXIT_FAILURE);
    }

    double ChiSq = 0.0;


    for (int i = min_bin; i <= max_bin; ++i){
        // Get N(Events) in Single Bin
        double nData_region1 = CryoRegions.Upstream.MnvH1D_data->GetBinContent(i);
        double nData_region2 = CryoRegions.Barrel.MnvH1D_data->GetBinContent(i);
        double nData_region3 = CryoRegions.Downstream.MnvH1D_data->GetBinContent(i);
        double nData_region4 = CryoRegions.Concave.MnvH1D_data->GetBinContent(i);
        double nData = nData_region1 + nData_region2 + nData_region3 + nData_region4;
        if (nData == 0 ) continue;
        double nHelium_region1 = CryoRegions.Upstream.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region1 = CryoRegions.Upstream.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region1 = CryoRegions.Upstream.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region1 = CryoRegions.Upstream.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region1 = CryoRegions.Upstream.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region1 = InPut_Alwgt_region1 * CryoRegions.Upstream.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        ////

        double nHelium_region2 = CryoRegions.Barrel.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region2 = CryoRegions.Barrel.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region2 = CryoRegions.Barrel.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region2 = CryoRegions.Barrel.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region2 = CryoRegions.Barrel.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region2 = InPut_Alwgt_region2 * CryoRegions.Barrel.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        ///////
        double nHelium_region3 = CryoRegions.Downstream.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region3 = CryoRegions.Downstream.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region3 = CryoRegions.Downstream.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region3 = CryoRegions.Downstream.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region3 = CryoRegions.Downstream.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region3 = InPut_Alwgt_region3 * CryoRegions.Downstream.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        ////
        double nHelium_region4 = CryoRegions.Concave.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region4 = CryoRegions.Concave.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region4 = CryoRegions.Concave.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region4 = CryoRegions.Concave.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region4 = CryoRegions.Concave.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region4 = InPut_Alwgt_region4 * CryoRegions.Concave.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        ////////
        double nHelium = nHelium_region1 + nHelium_region2 + nHelium_region3 + nHelium_region4;
        double nCarbon = nCarbon_region1 + nCarbon_region2 + nCarbon_region3 + nCarbon_region4;
        double nLead = nLead_region1 + nLead_region2 + nLead_region3 + nLead_region4;
        double nIron = nIron_region1 + nIron_region2 + nIron_region3 + nIron_region4;
        double nOther = nOther_region1 + nOther_region2 + nOther_region3 + nOther_region4;
        double nAluminium = nAluminium_region1 + nAluminium_region2 + nAluminium_region3 + nAluminium_region4;
        ///
        // Add All MC and scale them
        double nMC_total = (nHelium + nAluminium + nCarbon + nLead + nIron  + nOther);

        double c = nData * log(nMC_total);
        double delta = 2 * (nMC_total - c);
        ChiSq += delta;
      }




    return ChiSq;
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

double calc_LOG_ChiSq_For_ConvolutionTool_CV_Vertex_Combined_Full_Empty(
Convolution_CryoRegions &CryoRegions_Empty,
Convolution_CryoRegions &CryoRegions_Full,
  double InPut_Alwgt_region1_Empty,
  double InPut_Alwgt_region2_Empty,
  double InPut_Alwgt_region3_Empty,
  double InPut_Alwgt_region4_Empty,
  double InPut_Alwgt_region1_Full,
  double InPut_Alwgt_region2_Full,
  double InPut_Alwgt_region3_Full,
  double InPut_Alwgt_region4_Full,

   int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1, bool removeFirstandLastBin= true, bool isVertexZ=false)
{
  //std::cout<<"inside:calc_ChiSq_For_ConvolutionTool_CV_Vertex_X"<<std::endl;

    if (!isPartial){
        min_bin = 1;
        max_bin = CryoRegions_Empty.Upstream.MnvH1D_data->GetNbinsX();
        if(removeFirstandLastBin==true){min_bin = min_bin + 1; max_bin = max_bin - 1;}
    }

    if(isVertexZ==true){
      max_bin = CryoRegions_Empty.Upstream.MnvH1D_data->GetNbinsX();
    }

    if (min_bin == max_bin){
        cout<<"Wrong Range for Fit"<<endl;
        exit(EXIT_FAILURE);
    }

    double ChiSq = 0.0;


    for (int i = min_bin; i <= max_bin; ++i){
        // Get N(Events) in Single Bin

        double nData_region1_Empty = CryoRegions_Empty.Upstream.MnvH1D_data->GetBinContent(i);

        double nData_region2_Empty = CryoRegions_Empty.Barrel.MnvH1D_data->GetBinContent(i);

        double nData_region3_Empty = CryoRegions_Empty.Downstream.MnvH1D_data->GetBinContent(i);

        double nData_region4_Empty = CryoRegions_Empty.Concave.MnvH1D_data->GetBinContent(i);

        double nData_region1_Full = CryoRegions_Full.Upstream.MnvH1D_data->GetBinContent(i);

        double nData_region2_Full = CryoRegions_Full.Barrel.MnvH1D_data->GetBinContent(i);

        double nData_region3_Full = CryoRegions_Full.Downstream.MnvH1D_data->GetBinContent(i);

        double nData_region4_Full = CryoRegions_Full.Concave.MnvH1D_data->GetBinContent(i);


        double nData = nData_region1_Empty + nData_region2_Empty + nData_region3_Empty + nData_region4_Empty +
                       nData_region1_Full + nData_region2_Full + nData_region3_Full + nData_region4_Full;

        if (nData == 0 ) continue;
        //////////////////////////////////////////
        //Empty MC
        ///////////////////////////////////////////
        double nHelium_region1_Empty = CryoRegions_Empty.Upstream.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region1_Empty = CryoRegions_Empty.Upstream.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region1_Empty = CryoRegions_Empty.Upstream.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region1_Empty = CryoRegions_Empty.Upstream.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region1_Empty = CryoRegions_Empty.Upstream.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region1_Empty = InPut_Alwgt_region1_Empty * CryoRegions_Empty.Upstream.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        ////
        double nHelium_region2_Empty = CryoRegions_Empty.Barrel.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region2_Empty = CryoRegions_Empty.Barrel.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region2_Empty = CryoRegions_Empty.Barrel.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region2_Empty = CryoRegions_Empty.Barrel.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region2_Empty = CryoRegions_Empty.Barrel.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region2_Empty = InPut_Alwgt_region2_Empty * CryoRegions_Empty.Barrel.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        ///////
        double nHelium_region3_Empty = CryoRegions_Empty.Downstream.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region3_Empty = CryoRegions_Empty.Downstream.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region3_Empty = CryoRegions_Empty.Downstream.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region3_Empty = CryoRegions_Empty.Downstream.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region3_Empty = CryoRegions_Empty.Downstream.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region3_Empty = InPut_Alwgt_region3_Empty * CryoRegions_Empty.Downstream.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        ////
        double nHelium_region4_Empty = CryoRegions_Empty.Concave.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region4_Empty = CryoRegions_Empty.Concave.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region4_Empty = CryoRegions_Empty.Concave.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region4_Empty = CryoRegions_Empty.Concave.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region4_Empty = CryoRegions_Empty.Concave.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region4_Empty = InPut_Alwgt_region4_Empty * CryoRegions_Empty.Concave.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        //////////////////////////////////////////
        //Full
        ///////////////////////////////////////////
        if (nData == 0 ) continue;
        double nHelium_region1_Full = CryoRegions_Full.Upstream.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region1_Full = CryoRegions_Full.Upstream.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region1_Full = CryoRegions_Full.Upstream.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region1_Full = CryoRegions_Full.Upstream.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region1_Full = CryoRegions_Full.Upstream.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region1_Full = InPut_Alwgt_region1_Full * CryoRegions_Full.Upstream.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        ////
        double nHelium_region2_Full = CryoRegions_Full.Barrel.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region2_Full = CryoRegions_Full.Barrel.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region2_Full = CryoRegions_Full.Barrel.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region2_Full = CryoRegions_Full.Barrel.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region2_Full = CryoRegions_Full.Barrel.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region2_Full = InPut_Alwgt_region2_Full * CryoRegions_Full.Barrel.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        ///////
        double nHelium_region3_Full = CryoRegions_Full.Downstream.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region3_Full = CryoRegions_Full.Downstream.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region3_Full = CryoRegions_Full.Downstream.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region3_Full = CryoRegions_Full.Downstream.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region3_Full = CryoRegions_Full.Downstream.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region3_Full = InPut_Alwgt_region3_Full * CryoRegions_Full.Downstream.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        ////
        double nHelium_region4_Full = CryoRegions_Full.Concave.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region4_Full = CryoRegions_Full.Concave.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region4_Full = CryoRegions_Full.Concave.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region4_Full = CryoRegions_Full.Concave.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region4_Full = CryoRegions_Full.Concave.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region4_Full = InPut_Alwgt_region4_Full * CryoRegions_Full.Concave.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);

        ///////////////////////////////////////////
        double nHelium_Combined = nHelium_region1_Empty + nHelium_region2_Empty + nHelium_region3_Empty + nHelium_region4_Empty+
                                 nHelium_region1_Full + nHelium_region2_Full + nHelium_region3_Full + nHelium_region4_Full;
        double nCarbon_Combined = nCarbon_region1_Empty + nCarbon_region2_Empty + nCarbon_region3_Empty + nCarbon_region4_Empty +
                                 nCarbon_region1_Full + nCarbon_region2_Full + nCarbon_region3_Full + nCarbon_region4_Full;
        double nLead_Combined   =   nLead_region1_Empty + nLead_region2_Empty + nLead_region3_Empty + nLead_region4_Empty+
                                 nLead_region1_Full + nLead_region2_Full + nLead_region3_Full + nLead_region4_Full;
        double nIron_Combined   =   nIron_region1_Empty + nIron_region2_Empty + nIron_region3_Empty + nIron_region4_Empty+
                                  nIron_region1_Full + nIron_region2_Full + nIron_region3_Full + nIron_region4_Full;
        double nOther_Combined  = nOther_region1_Empty + nOther_region2_Empty + nOther_region3_Empty + nOther_region4_Empty+
                                  nOther_region1_Full + nOther_region2_Full + nOther_region3_Full + nOther_region4_Full;
        double nAluminium_Combined = nAluminium_region1_Empty + nAluminium_region2_Empty + nAluminium_region3_Empty + nAluminium_region4_Empty +
                                    nAluminium_region1_Full + nAluminium_region2_Full + nAluminium_region3_Full + nAluminium_region4_Full;
        ///
        // Add All MC and scale them
        double nMC_total = (nHelium_Combined + nAluminium_Combined + nCarbon_Combined + nLead_Combined + nIron_Combined  + nOther_Combined);

        double c = nData * log(nMC_total);
        double delta = 2 * (nMC_total - c);
        ChiSq += delta;
      }




    return ChiSq;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
double calc_ChiSq_For_ConvolutionTool_CV_Vertex_Combined_Full_Empty(
Convolution_CryoRegions &CryoRegions_Empty,
Convolution_CryoRegions &CryoRegions_Full,
  double InPut_Alwgt_region1_Empty,
  double InPut_Alwgt_region2_Empty,
  double InPut_Alwgt_region3_Empty,
  double InPut_Alwgt_region4_Empty,
  double InPut_Alwgt_region1_Full,
  double InPut_Alwgt_region2_Full,
  double InPut_Alwgt_region3_Full,
  double InPut_Alwgt_region4_Full,

   int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1, bool removeFirstandLastBin= true, bool isVertexZ=false)
{
  //std::cout<<"inside:calc_ChiSq_For_ConvolutionTool_CV_Vertex_X"<<std::endl;

    if (!isPartial){
        min_bin = 1;
        max_bin = CryoRegions_Empty.Upstream.MnvH1D_data->GetNbinsX();
        if(removeFirstandLastBin==true){min_bin = min_bin + 1; max_bin = max_bin - 1;}
    }

    if(isVertexZ==true){
      max_bin = CryoRegions_Empty.Upstream.MnvH1D_data->GetNbinsX();
    }

    if (min_bin == max_bin){
        cout<<"Wrong Range for Fit"<<endl;
        exit(EXIT_FAILURE);
    }

    double ChiSq = 0.0;


    for (int i = min_bin; i <= max_bin; ++i){
        // Get N(Events) in Single Bin

        double nData_region1_Empty = CryoRegions_Empty.Upstream.MnvH1D_data->GetBinContent(i);

        double nData_region2_Empty = CryoRegions_Empty.Barrel.MnvH1D_data->GetBinContent(i);

        double nData_region3_Empty = CryoRegions_Empty.Downstream.MnvH1D_data->GetBinContent(i);

        double nData_region4_Empty = CryoRegions_Empty.Concave.MnvH1D_data->GetBinContent(i);

        double nData_region1_Full = CryoRegions_Full.Upstream.MnvH1D_data->GetBinContent(i);

        double nData_region2_Full = CryoRegions_Full.Barrel.MnvH1D_data->GetBinContent(i);

        double nData_region3_Full = CryoRegions_Full.Downstream.MnvH1D_data->GetBinContent(i);

        double nData_region4_Full = CryoRegions_Full.Concave.MnvH1D_data->GetBinContent(i);

        double err_region1_Empty = CryoRegions_Empty.Upstream.MnvH1D_data->GetBinError(i);
        double err_region2_Empty = CryoRegions_Empty.Barrel.MnvH1D_data->GetBinError(i);
        double err_region3_Empty = CryoRegions_Empty.Downstream.MnvH1D_data->GetBinError(i);
        double err_region4_Empty = CryoRegions_Empty.Concave.MnvH1D_data->GetBinError(i);

        double err_region1_Full = CryoRegions_Full.Upstream.MnvH1D_data->GetBinError(i);
        double err_region2_Full = CryoRegions_Full.Barrel.MnvH1D_data->GetBinError(i);
        double err_region3_Full = CryoRegions_Full.Downstream.MnvH1D_data->GetBinError(i);
        double err_region4_Full = CryoRegions_Full.Concave.MnvH1D_data->GetBinError(i);


        double err = err_region1_Empty + err_region2_Empty + err_region3_Empty + err_region4_Empty +
                     err_region1_Full + err_region2_Full + err_region3_Full + err_region4_Full;

        double nData = nData_region1_Empty + nData_region2_Empty + nData_region3_Empty + nData_region4_Empty +
                       nData_region1_Full + nData_region2_Full + nData_region3_Full + nData_region4_Full;

        if (nData == 0 ) continue;
        //////////////////////////////////////////
        //Empty MC
        ///////////////////////////////////////////
        double nHelium_region1_Empty = CryoRegions_Empty.Upstream.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region1_Empty = CryoRegions_Empty.Upstream.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region1_Empty = CryoRegions_Empty.Upstream.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region1_Empty = CryoRegions_Empty.Upstream.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region1_Empty = CryoRegions_Empty.Upstream.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region1_Empty = InPut_Alwgt_region1_Empty * CryoRegions_Empty.Upstream.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        ////
        double nHelium_region2_Empty = CryoRegions_Empty.Barrel.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region2_Empty = CryoRegions_Empty.Barrel.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region2_Empty = CryoRegions_Empty.Barrel.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region2_Empty = CryoRegions_Empty.Barrel.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region2_Empty = CryoRegions_Empty.Barrel.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region2_Empty = InPut_Alwgt_region2_Empty * CryoRegions_Empty.Barrel.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        ///////
        double nHelium_region3_Empty = CryoRegions_Empty.Downstream.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region3_Empty = CryoRegions_Empty.Downstream.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region3_Empty = CryoRegions_Empty.Downstream.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region3_Empty = CryoRegions_Empty.Downstream.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region3_Empty = CryoRegions_Empty.Downstream.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region3_Empty = InPut_Alwgt_region3_Empty * CryoRegions_Empty.Downstream.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        ////
        double nHelium_region4_Empty = CryoRegions_Empty.Concave.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region4_Empty = CryoRegions_Empty.Concave.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region4_Empty = CryoRegions_Empty.Concave.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region4_Empty = CryoRegions_Empty.Concave.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region4_Empty = CryoRegions_Empty.Concave.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region4_Empty = InPut_Alwgt_region4_Empty * CryoRegions_Empty.Concave.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        //////////////////////////////////////////
        //Full
        ///////////////////////////////////////////
        double nHelium_region1_Full = CryoRegions_Full.Upstream.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region1_Full = CryoRegions_Full.Upstream.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region1_Full = CryoRegions_Full.Upstream.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region1_Full = CryoRegions_Full.Upstream.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region1_Full = CryoRegions_Full.Upstream.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region1_Full = InPut_Alwgt_region1_Full * CryoRegions_Full.Upstream.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        ////
        double nHelium_region2_Full = CryoRegions_Full.Barrel.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region2_Full = CryoRegions_Full.Barrel.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region2_Full = CryoRegions_Full.Barrel.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region2_Full = CryoRegions_Full.Barrel.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region2_Full = CryoRegions_Full.Barrel.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region2_Full = InPut_Alwgt_region2_Full * CryoRegions_Full.Barrel.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        ///////
        double nHelium_region3_Full = CryoRegions_Full.Downstream.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region3_Full = CryoRegions_Full.Downstream.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region3_Full = CryoRegions_Full.Downstream.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region3_Full = CryoRegions_Full.Downstream.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region3_Full = CryoRegions_Full.Downstream.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region3_Full = InPut_Alwgt_region3_Full * CryoRegions_Full.Downstream.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        ////
        double nHelium_region4_Full = CryoRegions_Full.Concave.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region4_Full = CryoRegions_Full.Concave.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region4_Full = CryoRegions_Full.Concave.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region4_Full = CryoRegions_Full.Concave.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region4_Full = CryoRegions_Full.Concave.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region4_Full = InPut_Alwgt_region4_Full * CryoRegions_Full.Concave.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);

        ///////////////////////////////////////////
        double nHelium_Combined = nHelium_region1_Empty + nHelium_region2_Empty + nHelium_region3_Empty + nHelium_region4_Empty+
                                 nHelium_region1_Full + nHelium_region2_Full + nHelium_region3_Full + nHelium_region4_Full;
        double nCarbon_Combined = nCarbon_region1_Empty + nCarbon_region2_Empty + nCarbon_region3_Empty + nCarbon_region4_Empty +
                                 nCarbon_region1_Full + nCarbon_region2_Full + nCarbon_region3_Full + nCarbon_region4_Full;
        double nLead_Combined   =   nLead_region1_Empty + nLead_region2_Empty + nLead_region3_Empty + nLead_region4_Empty+
                                 nLead_region1_Full + nLead_region2_Full + nLead_region3_Full + nLead_region4_Full;
        double nIron_Combined   =   nIron_region1_Empty + nIron_region2_Empty + nIron_region3_Empty + nIron_region4_Empty+
                                  nIron_region1_Full + nIron_region2_Full + nIron_region3_Full + nIron_region4_Full;
        double nOther_Combined  = nOther_region1_Empty + nOther_region2_Empty + nOther_region3_Empty + nOther_region4_Empty+
                                  nOther_region1_Full + nOther_region2_Full + nOther_region3_Full + nOther_region4_Full;
        double nAluminium_Combined = nAluminium_region1_Empty + nAluminium_region2_Empty + nAluminium_region3_Empty + nAluminium_region4_Empty +
                                    nAluminium_region1_Full + nAluminium_region2_Full + nAluminium_region3_Full + nAluminium_region4_Full;
        ///
        // Add All MC and scale them
        double nMC_total = (nHelium_Combined + nAluminium_Combined + nCarbon_Combined + nLead_Combined + nIron_Combined  + nOther_Combined);

        double delta = pow((nData-nMC_total),2) / pow(err,2);

        ChiSq += delta;
      }




    return ChiSq;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
double calc_ChiSq_For_ConvolutionTool_CV_Vertex_Combined_Full_Empty_1set(
Convolution_CryoRegions &CryoRegions_Empty,
Convolution_CryoRegions &CryoRegions_Full,
  double InPut_Alwgt_region1,
  double InPut_Alwgt_region2,
  double InPut_Alwgt_region3,
  double InPut_Alwgt_region4,

   int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1, bool removeFirstandLastBin= true, bool isVertexZ=false)
{
  //std::cout<<"inside:calc_ChiSq_For_ConvolutionTool_CV_Vertex_X"<<std::endl;

    if (!isPartial){
        min_bin = 1;
        max_bin = CryoRegions_Empty.Upstream.MnvH1D_data->GetNbinsX();
        if(removeFirstandLastBin==true){min_bin = min_bin + 1; max_bin = max_bin - 1;}
    }

    if(isVertexZ==true){
      max_bin = CryoRegions_Empty.Upstream.MnvH1D_data->GetNbinsX();
    }

    if (min_bin == max_bin){
        cout<<"Wrong Range for Fit"<<endl;
        exit(EXIT_FAILURE);
    }

    double ChiSq = 0.0;


    for (int i = min_bin; i <= max_bin; ++i){
        // Get N(Events) in Single Bin

        double nData_region1_Empty = CryoRegions_Empty.Upstream.MnvH1D_data->GetBinContent(i);

        double nData_region2_Empty = CryoRegions_Empty.Barrel.MnvH1D_data->GetBinContent(i);

        double nData_region3_Empty = CryoRegions_Empty.Downstream.MnvH1D_data->GetBinContent(i);

        double nData_region4_Empty = CryoRegions_Empty.Concave.MnvH1D_data->GetBinContent(i);

        double nData_region1_Full = CryoRegions_Full.Upstream.MnvH1D_data->GetBinContent(i);

        double nData_region2_Full = CryoRegions_Full.Barrel.MnvH1D_data->GetBinContent(i);

        double nData_region3_Full = CryoRegions_Full.Downstream.MnvH1D_data->GetBinContent(i);

        double nData_region4_Full = CryoRegions_Full.Concave.MnvH1D_data->GetBinContent(i);

        double err_region1_Empty = CryoRegions_Empty.Upstream.MnvH1D_data->GetBinError(i);
        double err_region2_Empty = CryoRegions_Empty.Barrel.MnvH1D_data->GetBinError(i);
        double err_region3_Empty = CryoRegions_Empty.Downstream.MnvH1D_data->GetBinError(i);
        double err_region4_Empty = CryoRegions_Empty.Concave.MnvH1D_data->GetBinError(i);

        double err_region1_Full = CryoRegions_Full.Upstream.MnvH1D_data->GetBinError(i);
        double err_region2_Full = CryoRegions_Full.Barrel.MnvH1D_data->GetBinError(i);
        double err_region3_Full = CryoRegions_Full.Downstream.MnvH1D_data->GetBinError(i);
        double err_region4_Full = CryoRegions_Full.Concave.MnvH1D_data->GetBinError(i);


        double err = err_region1_Empty + err_region2_Empty + err_region3_Empty + err_region4_Empty +
                     err_region1_Full + err_region2_Full + err_region3_Full + err_region4_Full;

        double nData = nData_region1_Empty + nData_region2_Empty + nData_region3_Empty + nData_region4_Empty +
                       nData_region1_Full + nData_region2_Full + nData_region3_Full + nData_region4_Full;

        if (nData == 0 ) continue;
        //////////////////////////////////////////
        //Empty MC
        ///////////////////////////////////////////
        double nHelium_region1_Empty = CryoRegions_Empty.Upstream.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region1_Empty = CryoRegions_Empty.Upstream.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region1_Empty = CryoRegions_Empty.Upstream.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region1_Empty = CryoRegions_Empty.Upstream.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region1_Empty = CryoRegions_Empty.Upstream.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region1_Empty = InPut_Alwgt_region1 * CryoRegions_Empty.Upstream.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        ////
        double nHelium_region2_Empty = CryoRegions_Empty.Barrel.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region2_Empty = CryoRegions_Empty.Barrel.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region2_Empty = CryoRegions_Empty.Barrel.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region2_Empty = CryoRegions_Empty.Barrel.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region2_Empty = CryoRegions_Empty.Barrel.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region2_Empty = InPut_Alwgt_region2 * CryoRegions_Empty.Barrel.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        ///////
        double nHelium_region3_Empty = CryoRegions_Empty.Downstream.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region3_Empty = CryoRegions_Empty.Downstream.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region3_Empty = CryoRegions_Empty.Downstream.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region3_Empty = CryoRegions_Empty.Downstream.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region3_Empty = CryoRegions_Empty.Downstream.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region3_Empty = InPut_Alwgt_region3 * CryoRegions_Empty.Downstream.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        ////
        double nHelium_region4_Empty = CryoRegions_Empty.Concave.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region4_Empty = CryoRegions_Empty.Concave.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region4_Empty = CryoRegions_Empty.Concave.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region4_Empty = CryoRegions_Empty.Concave.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region4_Empty = CryoRegions_Empty.Concave.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region4_Empty = InPut_Alwgt_region4 * CryoRegions_Empty.Concave.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        //////////////////////////////////////////
        //Full
        ///////////////////////////////////////////
        double nHelium_region1_Full = CryoRegions_Full.Upstream.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region1_Full = CryoRegions_Full.Upstream.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region1_Full = CryoRegions_Full.Upstream.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region1_Full = CryoRegions_Full.Upstream.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region1_Full = CryoRegions_Full.Upstream.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region1_Full = InPut_Alwgt_region1 * CryoRegions_Full.Upstream.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        ////
        double nHelium_region2_Full = CryoRegions_Full.Barrel.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region2_Full = CryoRegions_Full.Barrel.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region2_Full = CryoRegions_Full.Barrel.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region2_Full = CryoRegions_Full.Barrel.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region2_Full = CryoRegions_Full.Barrel.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region2_Full = InPut_Alwgt_region2 * CryoRegions_Full.Barrel.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        ///////
        double nHelium_region3_Full = CryoRegions_Full.Downstream.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region3_Full = CryoRegions_Full.Downstream.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region3_Full = CryoRegions_Full.Downstream.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region3_Full = CryoRegions_Full.Downstream.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region3_Full = CryoRegions_Full.Downstream.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region3_Full = InPut_Alwgt_region3 * CryoRegions_Full.Downstream.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        ////
        double nHelium_region4_Full = CryoRegions_Full.Concave.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region4_Full = CryoRegions_Full.Concave.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region4_Full = CryoRegions_Full.Concave.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region4_Full = CryoRegions_Full.Concave.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region4_Full = CryoRegions_Full.Concave.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region4_Full = InPut_Alwgt_region4 * CryoRegions_Full.Concave.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);

        ///////////////////////////////////////////
        double nHelium_Combined = nHelium_region1_Empty + nHelium_region2_Empty + nHelium_region3_Empty + nHelium_region4_Empty+
                                 nHelium_region1_Full + nHelium_region2_Full + nHelium_region3_Full + nHelium_region4_Full;
        double nCarbon_Combined = nCarbon_region1_Empty + nCarbon_region2_Empty + nCarbon_region3_Empty + nCarbon_region4_Empty +
                                 nCarbon_region1_Full + nCarbon_region2_Full + nCarbon_region3_Full + nCarbon_region4_Full;
        double nLead_Combined   =   nLead_region1_Empty + nLead_region2_Empty + nLead_region3_Empty + nLead_region4_Empty+
                                 nLead_region1_Full + nLead_region2_Full + nLead_region3_Full + nLead_region4_Full;
        double nIron_Combined   =   nIron_region1_Empty + nIron_region2_Empty + nIron_region3_Empty + nIron_region4_Empty+
                                  nIron_region1_Full + nIron_region2_Full + nIron_region3_Full + nIron_region4_Full;
        double nOther_Combined  = nOther_region1_Empty + nOther_region2_Empty + nOther_region3_Empty + nOther_region4_Empty+
                                  nOther_region1_Full + nOther_region2_Full + nOther_region3_Full + nOther_region4_Full;
        double nAluminium_Combined = nAluminium_region1_Empty + nAluminium_region2_Empty + nAluminium_region3_Empty + nAluminium_region4_Empty +
                                    nAluminium_region1_Full + nAluminium_region2_Full + nAluminium_region3_Full + nAluminium_region4_Full;
        ///
        // Add All MC and scale them
        double nMC_total = (nHelium_Combined + nAluminium_Combined + nCarbon_Combined + nLead_Combined + nIron_Combined  + nOther_Combined);

        double delta = pow((nData-nMC_total),2) / pow(err,2);

        ChiSq += delta;
      }




    return ChiSq;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
double calc_ChiSq_For_ConvolutionTool_CV_Vertex_Combined_Full_Empty_1set_log(
Convolution_CryoRegions &CryoRegions_Empty,
Convolution_CryoRegions &CryoRegions_Full,
  double InPut_Alwgt_region1,
  double InPut_Alwgt_region2,
  double InPut_Alwgt_region3,
  double InPut_Alwgt_region4,

   int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1, bool removeFirstandLastBin= true, bool isVertexZ=false)
{
  //std::cout<<"inside:calc_ChiSq_For_ConvolutionTool_CV_Vertex_X"<<std::endl;

    if (!isPartial){
        min_bin = 1;
        max_bin = CryoRegions_Empty.Upstream.MnvH1D_data->GetNbinsX();
        if(removeFirstandLastBin==true){min_bin = min_bin + 1; max_bin = max_bin - 1;}
    }

    if(isVertexZ==true){
      max_bin = CryoRegions_Empty.Upstream.MnvH1D_data->GetNbinsX();
    }

    if (min_bin == max_bin){
        cout<<"Wrong Range for Fit"<<endl;
        exit(EXIT_FAILURE);
    }

    double ChiSq = 0.0;


    for (int i = min_bin; i <= max_bin; ++i){
        // Get N(Events) in Single Bin

        double nData_region1_Empty = CryoRegions_Empty.Upstream.MnvH1D_data->GetBinContent(i);

        double nData_region2_Empty = CryoRegions_Empty.Barrel.MnvH1D_data->GetBinContent(i);

        double nData_region3_Empty = CryoRegions_Empty.Downstream.MnvH1D_data->GetBinContent(i);

        double nData_region4_Empty = CryoRegions_Empty.Concave.MnvH1D_data->GetBinContent(i);

        double nData_region1_Full = CryoRegions_Full.Upstream.MnvH1D_data->GetBinContent(i);

        double nData_region2_Full = CryoRegions_Full.Barrel.MnvH1D_data->GetBinContent(i);

        double nData_region3_Full = CryoRegions_Full.Downstream.MnvH1D_data->GetBinContent(i);

        double nData_region4_Full = CryoRegions_Full.Concave.MnvH1D_data->GetBinContent(i);

        double err_region1_Empty = CryoRegions_Empty.Upstream.MnvH1D_data->GetBinError(i);
        double err_region2_Empty = CryoRegions_Empty.Barrel.MnvH1D_data->GetBinError(i);
        double err_region3_Empty = CryoRegions_Empty.Downstream.MnvH1D_data->GetBinError(i);
        double err_region4_Empty = CryoRegions_Empty.Concave.MnvH1D_data->GetBinError(i);

        double err_region1_Full = CryoRegions_Full.Upstream.MnvH1D_data->GetBinError(i);
        double err_region2_Full = CryoRegions_Full.Barrel.MnvH1D_data->GetBinError(i);
        double err_region3_Full = CryoRegions_Full.Downstream.MnvH1D_data->GetBinError(i);
        double err_region4_Full = CryoRegions_Full.Concave.MnvH1D_data->GetBinError(i);


        double err = err_region1_Empty + err_region2_Empty + err_region3_Empty + err_region4_Empty +
                     err_region1_Full + err_region2_Full + err_region3_Full + err_region4_Full;

        double nData = nData_region1_Empty + nData_region2_Empty + nData_region3_Empty + nData_region4_Empty +
                       nData_region1_Full + nData_region2_Full + nData_region3_Full + nData_region4_Full;

        if (nData == 0 ) continue;
        //////////////////////////////////////////
        //Empty MC
        ///////////////////////////////////////////
        double nHelium_region1_Empty = CryoRegions_Empty.Upstream.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region1_Empty = CryoRegions_Empty.Upstream.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region1_Empty = CryoRegions_Empty.Upstream.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region1_Empty = CryoRegions_Empty.Upstream.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region1_Empty = CryoRegions_Empty.Upstream.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region1_Empty = InPut_Alwgt_region1 * CryoRegions_Empty.Upstream.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        ////
        double nHelium_region2_Empty = CryoRegions_Empty.Barrel.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region2_Empty = CryoRegions_Empty.Barrel.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region2_Empty = CryoRegions_Empty.Barrel.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region2_Empty = CryoRegions_Empty.Barrel.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region2_Empty = CryoRegions_Empty.Barrel.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region2_Empty = InPut_Alwgt_region2 * CryoRegions_Empty.Barrel.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        ///////
        double nHelium_region3_Empty = CryoRegions_Empty.Downstream.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region3_Empty = CryoRegions_Empty.Downstream.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region3_Empty = CryoRegions_Empty.Downstream.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region3_Empty = CryoRegions_Empty.Downstream.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region3_Empty = CryoRegions_Empty.Downstream.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region3_Empty = InPut_Alwgt_region3 * CryoRegions_Empty.Downstream.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        ////
        double nHelium_region4_Empty = CryoRegions_Empty.Concave.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region4_Empty = CryoRegions_Empty.Concave.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region4_Empty = CryoRegions_Empty.Concave.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region4_Empty = CryoRegions_Empty.Concave.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region4_Empty = CryoRegions_Empty.Concave.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region4_Empty = InPut_Alwgt_region4 * CryoRegions_Empty.Concave.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        //////////////////////////////////////////
        //Full
        ///////////////////////////////////////////
        double nHelium_region1_Full = CryoRegions_Full.Upstream.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region1_Full = CryoRegions_Full.Upstream.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region1_Full = CryoRegions_Full.Upstream.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region1_Full = CryoRegions_Full.Upstream.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region1_Full = CryoRegions_Full.Upstream.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region1_Full = InPut_Alwgt_region1 * CryoRegions_Full.Upstream.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        ////
        double nHelium_region2_Full = CryoRegions_Full.Barrel.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region2_Full = CryoRegions_Full.Barrel.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region2_Full = CryoRegions_Full.Barrel.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region2_Full = CryoRegions_Full.Barrel.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region2_Full = CryoRegions_Full.Barrel.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region2_Full = InPut_Alwgt_region2 * CryoRegions_Full.Barrel.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        ///////
        double nHelium_region3_Full = CryoRegions_Full.Downstream.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region3_Full = CryoRegions_Full.Downstream.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region3_Full = CryoRegions_Full.Downstream.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region3_Full = CryoRegions_Full.Downstream.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region3_Full = CryoRegions_Full.Downstream.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region3_Full = InPut_Alwgt_region3 * CryoRegions_Full.Downstream.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        ////
        double nHelium_region4_Full = CryoRegions_Full.Concave.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region4_Full = CryoRegions_Full.Concave.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region4_Full = CryoRegions_Full.Concave.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region4_Full = CryoRegions_Full.Concave.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region4_Full = CryoRegions_Full.Concave.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region4_Full = InPut_Alwgt_region4 * CryoRegions_Full.Concave.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);

        ///////////////////////////////////////////
        double nHelium_Combined = nHelium_region1_Empty + nHelium_region2_Empty + nHelium_region3_Empty + nHelium_region4_Empty+
                                 nHelium_region1_Full + nHelium_region2_Full + nHelium_region3_Full + nHelium_region4_Full;
        double nCarbon_Combined = nCarbon_region1_Empty + nCarbon_region2_Empty + nCarbon_region3_Empty + nCarbon_region4_Empty +
                                 nCarbon_region1_Full + nCarbon_region2_Full + nCarbon_region3_Full + nCarbon_region4_Full;
        double nLead_Combined   =   nLead_region1_Empty + nLead_region2_Empty + nLead_region3_Empty + nLead_region4_Empty+
                                 nLead_region1_Full + nLead_region2_Full + nLead_region3_Full + nLead_region4_Full;
        double nIron_Combined   =   nIron_region1_Empty + nIron_region2_Empty + nIron_region3_Empty + nIron_region4_Empty+
                                  nIron_region1_Full + nIron_region2_Full + nIron_region3_Full + nIron_region4_Full;
        double nOther_Combined  = nOther_region1_Empty + nOther_region2_Empty + nOther_region3_Empty + nOther_region4_Empty+
                                  nOther_region1_Full + nOther_region2_Full + nOther_region3_Full + nOther_region4_Full;
        double nAluminium_Combined = nAluminium_region1_Empty + nAluminium_region2_Empty + nAluminium_region3_Empty + nAluminium_region4_Empty +
                                    nAluminium_region1_Full + nAluminium_region2_Full + nAluminium_region3_Full + nAluminium_region4_Full;
        ///
        // Add All MC and scale them
        double nMC_total = (nHelium_Combined + nAluminium_Combined + nCarbon_Combined + nLead_Combined + nIron_Combined  + nOther_Combined);

        double c = nData * log(nMC_total);
        double delta = 2 * (nMC_total - c);

        ChiSq += delta;
      }




    return ChiSq;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
double calc_ChiSq_For_ConvolutionTool_CV_Vertex_Combined_Full_Empty_Difference(
Convolution_CryoRegions &CryoRegions_Empty,
Convolution_CryoRegions &CryoRegions_Full,
  double InPut_Alwgt_region1,
  double InPut_Alwgt_region2,
  double InPut_Alwgt_region3,
  double InPut_Alwgt_region4,

   int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1, bool removeFirstandLastBin= true, bool isVertexZ=false)
{
  //std::cout<<"inside:calc_ChiSq_For_ConvolutionTool_CV_Vertex_X"<<std::endl;

    if (!isPartial){
        min_bin = 1;
        max_bin = CryoRegions_Empty.Upstream.MnvH1D_data->GetNbinsX();
        if(removeFirstandLastBin==true){min_bin = min_bin + 1; max_bin = max_bin - 1;}
    }

    if(isVertexZ==true){
      max_bin = CryoRegions_Empty.Upstream.MnvH1D_data->GetNbinsX();
    }

    if (min_bin == max_bin){
        cout<<"Wrong Range for Fit"<<endl;
        exit(EXIT_FAILURE);
    }

    double ChiSq = 0.0;


    for (int i = min_bin; i <= max_bin; ++i){
        // Get N(Events) in Single Bin

        double nData_region1_Empty = CryoRegions_Empty.Upstream.MnvH1D_data->GetBinContent(i);

        double nData_region2_Empty = CryoRegions_Empty.Barrel.MnvH1D_data->GetBinContent(i);

        double nData_region3_Empty = CryoRegions_Empty.Downstream.MnvH1D_data->GetBinContent(i);

        double nData_region4_Empty = CryoRegions_Empty.Concave.MnvH1D_data->GetBinContent(i);

        double nData_region1_Full = CryoRegions_Full.Upstream.MnvH1D_data->GetBinContent(i);

        double nData_region2_Full = CryoRegions_Full.Barrel.MnvH1D_data->GetBinContent(i);

        double nData_region3_Full = CryoRegions_Full.Downstream.MnvH1D_data->GetBinContent(i);

        double nData_region4_Full = CryoRegions_Full.Concave.MnvH1D_data->GetBinContent(i);
        ////////////////////////

        double nData_region1_Full_Empty = nData_region1_Full - nData_region1_Empty;

        double nData_region2_Full_Empty = nData_region2_Full - nData_region2_Empty;

        double nData_region3_Full_Empty = nData_region3_Full - nData_region3_Empty;

        double nData_region4_Full_Empty = nData_region4_Full - nData_region4_Empty;



        double err_region1_Empty = CryoRegions_Empty.Upstream.MnvH1D_data->GetBinError(i);
        double err_region2_Empty = CryoRegions_Empty.Barrel.MnvH1D_data->GetBinError(i);
        double err_region3_Empty = CryoRegions_Empty.Downstream.MnvH1D_data->GetBinError(i);
        double err_region4_Empty = CryoRegions_Empty.Concave.MnvH1D_data->GetBinError(i);

        double err_region1_Full = CryoRegions_Full.Upstream.MnvH1D_data->GetBinError(i);
        double err_region2_Full = CryoRegions_Full.Barrel.MnvH1D_data->GetBinError(i);
        double err_region3_Full = CryoRegions_Full.Downstream.MnvH1D_data->GetBinError(i);
        double err_region4_Full = CryoRegions_Full.Concave.MnvH1D_data->GetBinError(i);

        double err_region1_Full_Empty =  err_region1_Full - err_region1_Empty ;
        double err_region2_Full_Empty =  err_region2_Full - err_region2_Empty ;
        double err_region3_Full_Empty =  err_region3_Full - err_region3_Empty ;
        double err_region4_Full_Empty =  err_region4_Full - err_region4_Empty ;



        double err = err_region1_Full_Empty + err_region2_Full_Empty + err_region3_Full_Empty + err_region4_Full_Empty;

        double nData = nData_region1_Full_Empty + nData_region2_Full_Empty + nData_region3_Full_Empty + nData_region4_Full_Empty;

        if (nData == 0 ) continue;
        //////////////////////////////////////////
        //Empty MC
        ///////////////////////////////////////////
        double nHelium_region1_Empty = CryoRegions_Empty.Upstream.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region1_Empty = CryoRegions_Empty.Upstream.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region1_Empty = CryoRegions_Empty.Upstream.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region1_Empty = CryoRegions_Empty.Upstream.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region1_Empty = CryoRegions_Empty.Upstream.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region1_Empty = InPut_Alwgt_region1 * CryoRegions_Empty.Upstream.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        ////
        double nHelium_region2_Empty = CryoRegions_Empty.Barrel.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region2_Empty = CryoRegions_Empty.Barrel.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region2_Empty = CryoRegions_Empty.Barrel.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region2_Empty = CryoRegions_Empty.Barrel.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region2_Empty = CryoRegions_Empty.Barrel.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region2_Empty = InPut_Alwgt_region2 * CryoRegions_Empty.Barrel.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        ///////
        double nHelium_region3_Empty = CryoRegions_Empty.Downstream.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region3_Empty = CryoRegions_Empty.Downstream.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region3_Empty = CryoRegions_Empty.Downstream.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region3_Empty = CryoRegions_Empty.Downstream.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region3_Empty = CryoRegions_Empty.Downstream.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region3_Empty = InPut_Alwgt_region3 * CryoRegions_Empty.Downstream.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        ////
        double nHelium_region4_Empty = CryoRegions_Empty.Concave.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region4_Empty = CryoRegions_Empty.Concave.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region4_Empty = CryoRegions_Empty.Concave.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region4_Empty = CryoRegions_Empty.Concave.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region4_Empty = CryoRegions_Empty.Concave.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region4_Empty = InPut_Alwgt_region4 * CryoRegions_Empty.Concave.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);





        //////////////////////////////////////////
        //Full
        ///////////////////////////////////////////
        double nHelium_region1_Full = CryoRegions_Full.Upstream.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region1_Full = CryoRegions_Full.Upstream.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region1_Full = CryoRegions_Full.Upstream.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region1_Full = CryoRegions_Full.Upstream.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region1_Full = CryoRegions_Full.Upstream.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region1_Full = InPut_Alwgt_region1 * CryoRegions_Full.Upstream.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        ////
        double nHelium_region2_Full = CryoRegions_Full.Barrel.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region2_Full = CryoRegions_Full.Barrel.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region2_Full = CryoRegions_Full.Barrel.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region2_Full = CryoRegions_Full.Barrel.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region2_Full = CryoRegions_Full.Barrel.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region2_Full = InPut_Alwgt_region2 * CryoRegions_Full.Barrel.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        ///////
        double nHelium_region3_Full = CryoRegions_Full.Downstream.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region3_Full = CryoRegions_Full.Downstream.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region3_Full = CryoRegions_Full.Downstream.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region3_Full = CryoRegions_Full.Downstream.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region3_Full = CryoRegions_Full.Downstream.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region3_Full = InPut_Alwgt_region3 * CryoRegions_Full.Downstream.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        ////
        double nHelium_region4_Full = CryoRegions_Full.Concave.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region4_Full = CryoRegions_Full.Concave.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region4_Full = CryoRegions_Full.Concave.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region4_Full = CryoRegions_Full.Concave.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region4_Full = CryoRegions_Full.Concave.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region4_Full = InPut_Alwgt_region4 * CryoRegions_Full.Concave.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        ////////////////////////////////////////////
        double nHelium_region1_Full_Empty =  nHelium_region1_Full - nHelium_region1_Empty;
        double nCarbon_region1_Full_Empty =  nCarbon_region1_Full - nCarbon_region1_Empty;
        double nLead_region1_Full_Empty =  nLead_region1_Full - nLead_region1_Empty;
        double nIron_region1_Full_Empty =  nIron_region1_Full - nIron_region1_Empty;
        double nOther_region1_Full_Empty =  nOther_region1_Full - nOther_region1_Empty;
        double nAluminium_region1_Full_Empty =  nAluminium_region1_Full - nAluminium_region1_Empty;

        double nHelium_region2_Full_Empty =  nHelium_region2_Full - nHelium_region2_Empty;
        double nCarbon_region2_Full_Empty =  nCarbon_region2_Full - nCarbon_region2_Empty;
        double nLead_region2_Full_Empty =  nLead_region2_Full - nLead_region2_Empty;
        double nIron_region2_Full_Empty =  nIron_region2_Full - nIron_region2_Empty;
        double nOther_region2_Full_Empty =  nOther_region2_Full - nOther_region2_Empty;
        double nAluminium_region2_Full_Empty =  nAluminium_region2_Full - nAluminium_region2_Empty;

        double nHelium_region3_Full_Empty =  nHelium_region3_Full - nHelium_region3_Empty;
        double nCarbon_region3_Full_Empty =  nCarbon_region3_Full - nCarbon_region3_Empty;
        double nLead_region3_Full_Empty =  nLead_region3_Full - nLead_region3_Empty;
        double nIron_region3_Full_Empty =  nIron_region3_Full - nIron_region3_Empty;
        double nOther_region3_Full_Empty =  nOther_region3_Full - nOther_region3_Empty;
        double nAluminium_region3_Full_Empty =  nAluminium_region3_Full - nAluminium_region3_Empty;

        double nHelium_region4_Full_Empty =  nHelium_region4_Full - nHelium_region4_Empty;
        double nCarbon_region4_Full_Empty =  nCarbon_region4_Full - nCarbon_region4_Empty;
        double nLead_region4_Full_Empty =  nLead_region4_Full - nLead_region4_Empty;
        double nIron_region4_Full_Empty =  nIron_region4_Full - nIron_region4_Empty;
        double nOther_region4_Full_Empty =  nOther_region4_Full - nOther_region4_Empty;
        double nAluminium_region4_Full_Empty =  nAluminium_region4_Full - nAluminium_region4_Empty;



        ///////////////////////////////////////////
        double nHelium_Combined = nHelium_region1_Full_Empty + nHelium_region2_Full_Empty + nHelium_region3_Full_Empty + nHelium_region4_Full_Empty;

        double nCarbon_Combined = nCarbon_region1_Full_Empty + nCarbon_region2_Full_Empty + nCarbon_region3_Full_Empty + nCarbon_region4_Full_Empty;

        double nLead_Combined   =   nLead_region1_Full_Empty + nLead_region2_Full_Empty + nLead_region3_Full_Empty + nLead_region4_Full_Empty;

        double nIron_Combined   =   nIron_region1_Full_Empty + nIron_region2_Full_Empty + nIron_region3_Full_Empty + nIron_region4_Full_Empty;

        double nOther_Combined  = nOther_region1_Full_Empty + nOther_region2_Full_Empty + nOther_region3_Full_Empty + nOther_region4_Full_Empty;

        double nAluminium_Combined = nAluminium_region1_Full_Empty + nAluminium_region2_Full_Empty + nAluminium_region3_Full_Empty + nAluminium_region4_Full_Empty;

        ///
        // Add All MC and scale them
        double nMC_total = (nHelium_Combined + nAluminium_Combined + nCarbon_Combined + nLead_Combined + nIron_Combined  + nOther_Combined);

        double delta = pow((nData-nMC_total),2) / pow(err,2);

        ChiSq += delta;
      }




    return ChiSq;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
double calc_ChiSq_For_ConvolutionTool_CV_Vertex_Combined_Full_Empty_Difference_Log(
Convolution_CryoRegions &CryoRegions_Empty,
Convolution_CryoRegions &CryoRegions_Full,
  double InPut_Alwgt_region1,
  double InPut_Alwgt_region2,
  double InPut_Alwgt_region3,
  double InPut_Alwgt_region4,

   int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1, bool removeFirstandLastBin= true, bool isVertexZ=false)
{
  //std::cout<<"inside:calc_ChiSq_For_ConvolutionTool_CV_Vertex_X"<<std::endl;

    if (!isPartial){
        min_bin = 1;
        max_bin = CryoRegions_Empty.Upstream.MnvH1D_data->GetNbinsX();
        if(removeFirstandLastBin==true){min_bin = min_bin + 1; max_bin = max_bin - 1;}
    }

    if(isVertexZ==true){
      max_bin = CryoRegions_Empty.Upstream.MnvH1D_data->GetNbinsX();
    }

    if (min_bin == max_bin){
        cout<<"Wrong Range for Fit"<<endl;
        exit(EXIT_FAILURE);
    }

    double ChiSq = 0.0;


    for (int i = min_bin; i <= max_bin; ++i){
        // Get N(Events) in Single Bin

        double nData_region1_Empty = CryoRegions_Empty.Upstream.MnvH1D_data->GetBinContent(i);

        double nData_region2_Empty = CryoRegions_Empty.Barrel.MnvH1D_data->GetBinContent(i);

        double nData_region3_Empty = CryoRegions_Empty.Downstream.MnvH1D_data->GetBinContent(i);

        double nData_region4_Empty = CryoRegions_Empty.Concave.MnvH1D_data->GetBinContent(i);

        double nData_region1_Full = CryoRegions_Full.Upstream.MnvH1D_data->GetBinContent(i);

        double nData_region2_Full = CryoRegions_Full.Barrel.MnvH1D_data->GetBinContent(i);

        double nData_region3_Full = CryoRegions_Full.Downstream.MnvH1D_data->GetBinContent(i);

        double nData_region4_Full = CryoRegions_Full.Concave.MnvH1D_data->GetBinContent(i);
        ////////////////////////

        double nData_region1_Full_Empty = nData_region1_Full - nData_region1_Empty;

        double nData_region2_Full_Empty = nData_region2_Full - nData_region2_Empty;

        double nData_region3_Full_Empty = nData_region3_Full - nData_region3_Empty;

        double nData_region4_Full_Empty = nData_region4_Full - nData_region4_Empty;



        double err_region1_Empty = CryoRegions_Empty.Upstream.MnvH1D_data->GetBinError(i);
        double err_region2_Empty = CryoRegions_Empty.Barrel.MnvH1D_data->GetBinError(i);
        double err_region3_Empty = CryoRegions_Empty.Downstream.MnvH1D_data->GetBinError(i);
        double err_region4_Empty = CryoRegions_Empty.Concave.MnvH1D_data->GetBinError(i);

        double err_region1_Full = CryoRegions_Full.Upstream.MnvH1D_data->GetBinError(i);
        double err_region2_Full = CryoRegions_Full.Barrel.MnvH1D_data->GetBinError(i);
        double err_region3_Full = CryoRegions_Full.Downstream.MnvH1D_data->GetBinError(i);
        double err_region4_Full = CryoRegions_Full.Concave.MnvH1D_data->GetBinError(i);

        double err_region1_Full_Empty =  err_region1_Full - err_region1_Empty ;
        double err_region2_Full_Empty =  err_region2_Full - err_region2_Empty ;
        double err_region3_Full_Empty =  err_region3_Full - err_region3_Empty ;
        double err_region4_Full_Empty =  err_region4_Full - err_region4_Empty ;



        double err = err_region1_Full_Empty + err_region2_Full_Empty + err_region3_Full_Empty + err_region4_Full_Empty;

        double nData = nData_region1_Full_Empty + nData_region2_Full_Empty + nData_region3_Full_Empty + nData_region4_Full_Empty ;

        if (nData == 0 ) continue;
        //////////////////////////////////////////
        //Empty MC
        ///////////////////////////////////////////
        double nHelium_region1_Empty = CryoRegions_Empty.Upstream.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region1_Empty = CryoRegions_Empty.Upstream.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region1_Empty = CryoRegions_Empty.Upstream.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region1_Empty = CryoRegions_Empty.Upstream.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region1_Empty = CryoRegions_Empty.Upstream.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region1_Empty = InPut_Alwgt_region1 * CryoRegions_Empty.Upstream.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        ////
        double nHelium_region2_Empty = CryoRegions_Empty.Barrel.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region2_Empty = CryoRegions_Empty.Barrel.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region2_Empty = CryoRegions_Empty.Barrel.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region2_Empty = CryoRegions_Empty.Barrel.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region2_Empty = CryoRegions_Empty.Barrel.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region2_Empty = InPut_Alwgt_region2 * CryoRegions_Empty.Barrel.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        ///////
        double nHelium_region3_Empty = CryoRegions_Empty.Downstream.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region3_Empty = CryoRegions_Empty.Downstream.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region3_Empty = CryoRegions_Empty.Downstream.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region3_Empty = CryoRegions_Empty.Downstream.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region3_Empty = CryoRegions_Empty.Downstream.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region3_Empty = InPut_Alwgt_region3 * CryoRegions_Empty.Downstream.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        ////
        double nHelium_region4_Empty = CryoRegions_Empty.Concave.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region4_Empty = CryoRegions_Empty.Concave.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region4_Empty = CryoRegions_Empty.Concave.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region4_Empty = CryoRegions_Empty.Concave.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region4_Empty = CryoRegions_Empty.Concave.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region4_Empty = InPut_Alwgt_region4 * CryoRegions_Empty.Concave.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);





        //////////////////////////////////////////
        //Full
        ///////////////////////////////////////////
        double nHelium_region1_Full = CryoRegions_Full.Upstream.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region1_Full = CryoRegions_Full.Upstream.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region1_Full = CryoRegions_Full.Upstream.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region1_Full = CryoRegions_Full.Upstream.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region1_Full = CryoRegions_Full.Upstream.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region1_Full = InPut_Alwgt_region1 * CryoRegions_Full.Upstream.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        ////
        double nHelium_region2_Full = CryoRegions_Full.Barrel.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region2_Full = CryoRegions_Full.Barrel.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region2_Full = CryoRegions_Full.Barrel.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region2_Full = CryoRegions_Full.Barrel.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region2_Full = CryoRegions_Full.Barrel.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region2_Full = InPut_Alwgt_region2 * CryoRegions_Full.Barrel.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        ///////
        double nHelium_region3_Full = CryoRegions_Full.Downstream.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region3_Full = CryoRegions_Full.Downstream.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region3_Full = CryoRegions_Full.Downstream.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region3_Full = CryoRegions_Full.Downstream.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region3_Full = CryoRegions_Full.Downstream.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region3_Full = InPut_Alwgt_region3 * CryoRegions_Full.Downstream.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        ////
        double nHelium_region4_Full = CryoRegions_Full.Concave.MnvH1D_mc_Convoluted_Helium[0]->GetBinContent(i);
        double nCarbon_region4_Full = CryoRegions_Full.Concave.MnvH1D_mc_Convoluted_Carbon[0]->GetBinContent(i);
        double nLead_region4_Full = CryoRegions_Full.Concave.MnvH1D_mc_Convoluted_Lead[0]->GetBinContent(i);
        double nIron_region4_Full = CryoRegions_Full.Concave.MnvH1D_mc_Convoluted_Iron[0]->GetBinContent(i);
        double nOther_region4_Full = CryoRegions_Full.Concave.MnvH1D_mc_Convoluted_Other[0]->GetBinContent(i);
        double nAluminium_region4_Full = InPut_Alwgt_region4 * CryoRegions_Full.Concave.MnvH1D_mc_Convoluted_Aluminium[0]->GetBinContent(i);
        ////////////////////////////////////////////
        double nHelium_region1_Full_Empty =  nHelium_region1_Full - nHelium_region1_Empty;
        double nCarbon_region1_Full_Empty =  nCarbon_region1_Full - nCarbon_region1_Empty;
        double nLead_region1_Full_Empty =  nLead_region1_Full - nLead_region1_Empty;
        double nIron_region1_Full_Empty =  nIron_region1_Full - nIron_region1_Empty;
        double nOther_region1_Full_Empty =  nOther_region1_Full - nOther_region1_Empty;
        double nAluminium_region1_Full_Empty =  nAluminium_region1_Full - nAluminium_region1_Empty;

        double nHelium_region2_Full_Empty =  nHelium_region2_Full - nHelium_region2_Empty;
        double nCarbon_region2_Full_Empty =  nCarbon_region2_Full - nCarbon_region2_Empty;
        double nLead_region2_Full_Empty =  nLead_region2_Full - nLead_region2_Empty;
        double nIron_region2_Full_Empty =  nIron_region2_Full - nIron_region2_Empty;
        double nOther_region2_Full_Empty =  nOther_region2_Full - nOther_region2_Empty;
        double nAluminium_region2_Full_Empty =  nAluminium_region2_Full - nAluminium_region2_Empty;

        double nHelium_region3_Full_Empty =  nHelium_region3_Full - nHelium_region3_Empty;
        double nCarbon_region3_Full_Empty =  nCarbon_region3_Full - nCarbon_region3_Empty;
        double nLead_region3_Full_Empty =  nLead_region3_Full - nLead_region3_Empty;
        double nIron_region3_Full_Empty =  nIron_region3_Full - nIron_region3_Empty;
        double nOther_region3_Full_Empty =  nOther_region3_Full - nOther_region3_Empty;
        double nAluminium_region3_Full_Empty =  nAluminium_region3_Full - nAluminium_region3_Empty;

        double nHelium_region4_Full_Empty =  nHelium_region4_Full - nHelium_region4_Empty;
        double nCarbon_region4_Full_Empty =  nCarbon_region4_Full - nCarbon_region4_Empty;
        double nLead_region4_Full_Empty =  nLead_region4_Full - nLead_region4_Empty;
        double nIron_region4_Full_Empty =  nIron_region4_Full - nIron_region4_Empty;
        double nOther_region4_Full_Empty =  nOther_region4_Full - nOther_region4_Empty;
        double nAluminium_region4_Full_Empty =  nAluminium_region4_Full - nAluminium_region4_Empty;



        ///////////////////////////////////////////
        double nHelium_Combined = nHelium_region1_Full_Empty + nHelium_region2_Full_Empty + nHelium_region3_Full_Empty + nHelium_region4_Full_Empty;

        double nCarbon_Combined = nCarbon_region1_Full_Empty + nCarbon_region2_Full_Empty + nCarbon_region3_Full_Empty + nCarbon_region4_Full_Empty;

        double nLead_Combined   =   nLead_region1_Full_Empty + nLead_region2_Full_Empty + nLead_region3_Full_Empty + nLead_region4_Full_Empty;

        double nIron_Combined   =   nIron_region1_Full_Empty + nIron_region2_Full_Empty + nIron_region3_Full_Empty + nIron_region4_Full_Empty;

        double nOther_Combined  = nOther_region1_Full_Empty + nOther_region2_Full_Empty + nOther_region3_Full_Empty + nOther_region4_Full_Empty;

        double nAluminium_Combined = nAluminium_region1_Full_Empty + nAluminium_region2_Full_Empty + nAluminium_region3_Full_Empty + nAluminium_region4_Full_Empty;

        ///
        // Add All MC and scale them
        double nMC_total = (nHelium_Combined + nAluminium_Combined + nCarbon_Combined + nLead_Combined + nIron_Combined  + nOther_Combined);

        double c = nData * log(nMC_total);
        double delta = 2 * (nMC_total - c);

        ChiSq += delta;
      }




    return ChiSq;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void calc_ChiSq_ConvolutionTool_Empty(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
    // Silence Unused Variable Warning
    (void) npar;
    (void) gin;
    (void) iflag;

    double ChiSq = 0;
//std::cout<<"Chi  start"<<  ChiSq<<std::endl;
    // Calculate ChiSq for Empty for ALL Bins
    //ChiSq += calc_ChiSq_SideBand(Convolution_Tool_GLOBAL.Helium_Empty, par, Convolution_Tool_GLOBAL.current_unv);
    ChiSq +=calc_ChiSq_For_ConvolutionTool_CV_Vertex(Convolution_Tool_GLOBAL.Empty.Vertex_X_Regions,par[0],par[1],par[2],par[3]);

                                      //    std::cout<<"Chi  X "<<  ChiSq<<std::endl;

    ChiSq +=calc_ChiSq_For_ConvolutionTool_CV_Vertex(Convolution_Tool_GLOBAL.Empty.Vertex_Y_Regions,par[0],par[1],par[2],par[3]);


    ChiSq +=calc_ChiSq_For_ConvolutionTool_CV_Vertex(Convolution_Tool_GLOBAL.Empty.Vertex_Z_Regions,par[0],par[1],par[2],par[3], 0,  true, 5, 999,  true);

    f = ChiSq;
    return;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void calc_ChiSq_ConvolutionTool_Full(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
    // Silence Unused Variable Warning
    (void) npar;
    (void) gin;
    (void) iflag;

    double ChiSq = 0;
//std::cout<<"Chi  start"<<  ChiSq<<std::endl;
    // Calculate ChiSq for Empty for ALL Bins
    //ChiSq += calc_ChiSq_SideBand(Convolution_Tool_GLOBAL.Helium_Empty, par, Convolution_Tool_GLOBAL.current_unv);
    ChiSq +=calc_ChiSq_For_ConvolutionTool_CV_Vertex(Convolution_Tool_GLOBAL.Full.Vertex_X_Regions,par[0],par[1],par[2],par[3]);

                                      //    std::cout<<"Chi  X "<<  ChiSq<<std::endl;

    ChiSq +=calc_ChiSq_For_ConvolutionTool_CV_Vertex(Convolution_Tool_GLOBAL.Full.Vertex_Y_Regions,par[0],par[1],par[2],par[3]);


    ChiSq +=calc_ChiSq_For_ConvolutionTool_CV_Vertex(Convolution_Tool_GLOBAL.Full.Vertex_Z_Regions,par[0],par[1],par[2],par[3], 0,  true, 5, 999,  true);

    f = ChiSq;
    return;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void calc_ChiSq_ConvolutionTool_Combined(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
    // Silence Unused Variable Warning
    (void) npar;
    (void) gin;
    (void) iflag;

    double ChiSq = 0;
//std::cout<<"Chi  start"<<  ChiSq<<std::endl;
    // Calculate ChiSq for Empty for ALL Bins
    //ChiSq += calc_ChiSq_SideBand(Convolution_Tool_GLOBAL.Helium_Empty, par, Convolution_Tool_GLOBAL.current_unv);
    ChiSq +=calc_ChiSq_For_ConvolutionTool_CV_Vertex_Combined_Full_Empty(Convolution_Tool_GLOBAL.Empty.Vertex_X_Regions,Convolution_Tool_GLOBAL.Full.Vertex_X_Regions,par[0],par[1],par[2],par[3] , par[4],par[5],par[6],par[7]);


    ChiSq +=calc_ChiSq_For_ConvolutionTool_CV_Vertex_Combined_Full_Empty(Convolution_Tool_GLOBAL.Empty.Vertex_Y_Regions,Convolution_Tool_GLOBAL.Full.Vertex_Y_Regions,par[0],par[1],par[2],par[3] , par[4],par[5],par[6],par[7]);


    ChiSq +=calc_ChiSq_For_ConvolutionTool_CV_Vertex_Combined_Full_Empty(Convolution_Tool_GLOBAL.Empty.Vertex_Z_Regions,Convolution_Tool_GLOBAL.Full.Vertex_Z_Regions,par[0],par[1],par[2],par[3], par[4],par[5],par[6],par[7],
       0,  true, 5, 999,  true);

    f = ChiSq;

    return;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void calc_ChiSq_ConvolutionTool_Empty_RZ(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
    // Silence Unused Variable Warning
    (void) npar;
    (void) gin;
    (void) iflag;

    double ChiSq = 0;
//std::cout<<"Chi  start"<<  ChiSq<<std::endl;
    // Calculate ChiSq for Empty for ALL Bins
    //ChiSq += calc_ChiSq_SideBand(Convolution_Tool_GLOBAL.Helium_Empty, par, Convolution_Tool_GLOBAL.current_unv);

    ChiSq +=calc_ChiSq_For_ConvolutionTool_CV_Vertex(Convolution_Tool_GLOBAL.Empty.Vertex_Z_Regions,par[0],par[1],par[2],par[3],0,  true, 5, 999,  true);

                                              //  std::cout<<"Chi  Z "<<  ChiSq<<std::endl;

    ChiSq +=calc_ChiSq_For_ConvolutionTool_CV_Vertex(Convolution_Tool_GLOBAL.Empty.Vertex_R_Regions,par[0],par[1],par[2],par[3]);

                                          //      std::cout<<"Chi  R"<<  ChiSq<<std::endl;

    f = ChiSq;
    return;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

void calc_ChiSq_ConvolutionTool_EmptyLog(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
    // Silence Unused Variable Warning
    (void) npar;
    (void) gin;
    (void) iflag;

    double ChiSq = 0;
//std::cout<<"Chi  start"<<  ChiSq<<std::endl;
    // Calculate ChiSq for Empty for ALL Bins
    //ChiSq += calc_ChiSq_SideBand(Convolution_Tool_GLOBAL.Helium_Empty, par, Convolution_Tool_GLOBAL.current_unv);

    ChiSq +=calc_LOG_ChiSq_For_ConvolutionTool_CV_Vertex(Convolution_Tool_GLOBAL.Empty.Vertex_X_Regions,par[0],par[1],par[2],par[3]);


    ChiSq +=calc_LOG_ChiSq_For_ConvolutionTool_CV_Vertex(Convolution_Tool_GLOBAL.Empty.Vertex_Y_Regions,par[0],par[1],par[2],par[3]);


    ChiSq +=calc_LOG_ChiSq_For_ConvolutionTool_CV_Vertex(Convolution_Tool_GLOBAL.Empty.Vertex_Z_Regions,par[0],par[1],par[2],par[3], 0,  true, 5, 999,  true);

    f = ChiSq;
    return;
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void calc_ChiSq_ConvolutionTool_FullLog(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
    // Silence Unused Variable Warning
    (void) npar;
    (void) gin;
    (void) iflag;

    double ChiSq = 0;
//std::cout<<"Chi  start"<<  ChiSq<<std::endl;
    // Calculate ChiSq for Empty for ALL Bins
    //ChiSq += calc_ChiSq_SideBand(Convolution_Tool_GLOBAL.Helium_Empty, par, Convolution_Tool_GLOBAL.current_unv);
    ChiSq +=calc_LOG_ChiSq_For_ConvolutionTool_CV_Vertex(Convolution_Tool_GLOBAL.Full.Vertex_X_Regions,par[0],par[1],par[2],par[3]);


    ChiSq +=calc_LOG_ChiSq_For_ConvolutionTool_CV_Vertex(Convolution_Tool_GLOBAL.Full.Vertex_Y_Regions,par[0],par[1],par[2],par[3]);


    ChiSq +=calc_LOG_ChiSq_For_ConvolutionTool_CV_Vertex(Convolution_Tool_GLOBAL.Full.Vertex_Z_Regions,par[0],par[1],par[2],par[3], 0,  true, 5, 999,  true);

    f = ChiSq;
    return;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void calc_ChiSq_ConvolutionTool_Combined_Log(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
    // Silence Unused Variable Warning
    (void) npar;
    (void) gin;
    (void) iflag;

    double ChiSq = 0;
//std::cout<<"Chi  start"<<  ChiSq<<std::endl;
    // Calculate ChiSq for Empty for ALL Bins
    //ChiSq += calc_ChiSq_SideBand(Convolution_Tool_GLOBAL.Helium_Empty, par, Convolution_Tool_GLOBAL.current_unv);
    ChiSq +=calc_LOG_ChiSq_For_ConvolutionTool_CV_Vertex_Combined_Full_Empty(Convolution_Tool_GLOBAL.Empty.Vertex_X_Regions,Convolution_Tool_GLOBAL.Full.Vertex_X_Regions,par[0],par[1],par[2],par[3] , par[4],par[5],par[6],par[7]);


    ChiSq +=calc_LOG_ChiSq_For_ConvolutionTool_CV_Vertex_Combined_Full_Empty(Convolution_Tool_GLOBAL.Empty.Vertex_Y_Regions,Convolution_Tool_GLOBAL.Full.Vertex_Y_Regions,par[0],par[1],par[2],par[3] , par[4],par[5],par[6],par[7]);


    ChiSq +=calc_LOG_ChiSq_For_ConvolutionTool_CV_Vertex_Combined_Full_Empty(Convolution_Tool_GLOBAL.Empty.Vertex_Z_Regions,Convolution_Tool_GLOBAL.Full.Vertex_Z_Regions,par[0],par[1],par[2],par[3], par[4],par[5],par[6],par[7],
       0,  true, 5, 999,  true);



    return;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void calc_ChiSq_ConvolutionTool_Combined_1set(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
    // Silence Unused Variable Warning
    (void) npar;
    (void) gin;
    (void) iflag;

    double ChiSq = 0;
//std::cout<<"Chi  start"<<  ChiSq<<std::endl;
    // Calculate ChiSq for Empty for ALL Bins
    //ChiSq += calc_ChiSq_SideBand(Convolution_Tool_GLOBAL.Helium_Empty, par, Convolution_Tool_GLOBAL.current_unv);
    ChiSq +=calc_ChiSq_For_ConvolutionTool_CV_Vertex_Combined_Full_Empty_1set(Convolution_Tool_GLOBAL.Empty.Vertex_X_Regions,Convolution_Tool_GLOBAL.Full.Vertex_X_Regions,par[0],par[1],par[2],par[3] );


    ChiSq +=calc_ChiSq_For_ConvolutionTool_CV_Vertex_Combined_Full_Empty_1set(Convolution_Tool_GLOBAL.Empty.Vertex_Y_Regions,Convolution_Tool_GLOBAL.Full.Vertex_Y_Regions,par[0],par[1],par[2],par[3] );


    ChiSq +=calc_ChiSq_For_ConvolutionTool_CV_Vertex_Combined_Full_Empty_1set(Convolution_Tool_GLOBAL.Empty.Vertex_Z_Regions,Convolution_Tool_GLOBAL.Full.Vertex_Z_Regions,par[0],par[1],par[2],par[3],
       0,  true, 5, 999,  true);

    f = ChiSq;

    return;
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void calc_ChiSq_ConvolutionTool_Combined_1set_Log(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
    // Silence Unused Variable Warning
    (void) npar;
    (void) gin;
    (void) iflag;

    double ChiSq = 0;
//std::cout<<"Chi  start"<<  ChiSq<<std::endl;
    // Calculate ChiSq for Empty for ALL Bins
    //ChiSq += calc_ChiSq_SideBand(Convolution_Tool_GLOBAL.Helium_Empty, par, Convolution_Tool_GLOBAL.current_unv);
    ChiSq +=calc_ChiSq_For_ConvolutionTool_CV_Vertex_Combined_Full_Empty_1set_log(Convolution_Tool_GLOBAL.Empty.Vertex_X_Regions,Convolution_Tool_GLOBAL.Full.Vertex_X_Regions,par[0],par[1],par[2],par[3] );


    ChiSq +=calc_ChiSq_For_ConvolutionTool_CV_Vertex_Combined_Full_Empty_1set_log(Convolution_Tool_GLOBAL.Empty.Vertex_Y_Regions,Convolution_Tool_GLOBAL.Full.Vertex_Y_Regions,par[0],par[1],par[2],par[3] );


    ChiSq +=calc_ChiSq_For_ConvolutionTool_CV_Vertex_Combined_Full_Empty_1set_log(Convolution_Tool_GLOBAL.Empty.Vertex_Z_Regions,Convolution_Tool_GLOBAL.Full.Vertex_Z_Regions,par[0],par[1],par[2],par[3],
       0,  true, 5, 999,  true);

    f = ChiSq;

    return;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void calc_ChiSq_ConvolutionTool_Combined_Differece(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
    // Silence Unused Variable Warning
    (void) npar;
    (void) gin;
    (void) iflag;

    double ChiSq = 0;
//std::cout<<"Chi  start"<<  ChiSq<<std::endl;
    // Calculate ChiSq for Empty for ALL Bins
    //ChiSq += calc_ChiSq_SideBand(Convolution_Tool_GLOBAL.Helium_Empty, par, Convolution_Tool_GLOBAL.current_unv);
    ChiSq +=calc_ChiSq_For_ConvolutionTool_CV_Vertex_Combined_Full_Empty_Difference(Convolution_Tool_GLOBAL.Empty.Vertex_X_Regions,Convolution_Tool_GLOBAL.Full.Vertex_X_Regions,par[0],par[1],par[2],par[3] );


    ChiSq +=calc_ChiSq_For_ConvolutionTool_CV_Vertex_Combined_Full_Empty_Difference(Convolution_Tool_GLOBAL.Empty.Vertex_Y_Regions,Convolution_Tool_GLOBAL.Full.Vertex_Y_Regions,par[0],par[1],par[2],par[3] );


    ChiSq +=calc_ChiSq_For_ConvolutionTool_CV_Vertex_Combined_Full_Empty_Difference(Convolution_Tool_GLOBAL.Empty.Vertex_Z_Regions,Convolution_Tool_GLOBAL.Full.Vertex_Z_Regions,par[0],par[1],par[2],par[3],
       0,  true, 5, 999,  true);

    f = ChiSq;

    return;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void calc_ChiSq_ConvolutionTool_Combined_Differece_Log(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
    // Silence Unused Variable Warning
    (void) npar;
    (void) gin;
    (void) iflag;

    double ChiSq = 0;
//std::cout<<"Chi  start"<<  ChiSq<<std::endl;
    // Calculate ChiSq for Empty for ALL Bins
    //ChiSq += calc_ChiSq_SideBand(Convolution_Tool_GLOBAL.Helium_Empty, par, Convolution_Tool_GLOBAL.current_unv);
    ChiSq +=calc_ChiSq_For_ConvolutionTool_CV_Vertex_Combined_Full_Empty_Difference_Log(Convolution_Tool_GLOBAL.Empty.Vertex_X_Regions,Convolution_Tool_GLOBAL.Full.Vertex_X_Regions,par[0],par[1],par[2],par[3] );


    ChiSq +=calc_ChiSq_For_ConvolutionTool_CV_Vertex_Combined_Full_Empty_Difference_Log(Convolution_Tool_GLOBAL.Empty.Vertex_Y_Regions,Convolution_Tool_GLOBAL.Full.Vertex_Y_Regions,par[0],par[1],par[2],par[3] );


    ChiSq +=calc_ChiSq_For_ConvolutionTool_CV_Vertex_Combined_Full_Empty_Difference_Log(Convolution_Tool_GLOBAL.Empty.Vertex_Z_Regions,Convolution_Tool_GLOBAL.Full.Vertex_Z_Regions,par[0],par[1],par[2],par[3],
       0,  true, 5, 999,  true);

    f = ChiSq;

    return;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void FitMinuit_Convolution_Empty(Convolution_Tool sbtool, std::string fitName, std::string pdf_label, std::vector<double> &wgt_vector, std::vector<double> &wgt_error, double &chisqrt, double &chisqrt_error  )
{
    //cout<<"======================================================================"<<endl;
    //cout<<"Universe = "<<sbtool.current_unv<<endl;
    //cout<<"======================================================================"<<endl;

    TMinuit *ptMinuit = new TMinuit(4);  //initialize TMinuit with a maximum of 4 params
    //
    //  select verbose level:
    //    default :     (58 lines in this test)
    //    -1 : minimum  ( 4 lines in this test)
    //     0 : low      (31 lines)
    //     1 : medium   (61 lines)
    //     2 : high     (89 lines)
    //     3 : maximum (199 lines in this test)
    //
    ptMinuit->SetPrintLevel(-1);
    // set the user function that calculates chi_square (the value to minimize)
    ptMinuit->SetFCN(calc_ChiSq_ConvolutionTool_Empty);

    Double_t arglist[10];
    Int_t ierflg = 0;

    arglist[0] = 1;
    ptMinuit->mnexcm("SET ERR", arglist ,1,ierflg);

    // Set starting values and step sizes for parameters
    //      Start from 1.0 and step 0.01
    ptMinuit->mnparm(0, "FitParm_Aluminium_upstreamCap",          .05, 0.01, .01, 10.0 , ierflg);
    ptMinuit->mnparm(1, "FitParm_Aluminium_Barrel",               .05, 0.01, .01, 10.0 , ierflg);
    ptMinuit->mnparm(2, "FitParm_Aluminium_downstreamCap",        .05, 0.01, .01, 10.0 , ierflg);
    ptMinuit->mnparm(3, "FitParm_Aluminium_downstreamConcaveCap", .05, 0.01, .01, 10.0 , ierflg);

    // Now ready for minimization step
    arglist[0] = 20000;
    arglist[1] = 1.;
    ptMinuit->mnexcm("MIGRAD", arglist ,2,ierflg);

    // Print results
    //std::cout<<"\nPrint results from minuit\n";
    double fParamVal[4];
    double fParamErr[4];
    ptMinuit->GetParameter(0, fParamVal[0], fParamErr[0]);
    ptMinuit->GetParameter(1, fParamVal[1], fParamErr[1]);
    ptMinuit->GetParameter(2, fParamVal[2], fParamErr[2]);
    ptMinuit->GetParameter(3, fParamVal[3], fParamErr[3]);


    //std::cout << "MnvH1D_Aluminium Upstream = " << fParamVal[0] << "\n";
    //std::cout << "MnvH1D_Aluminium Barrel = " << fParamVal[1] << "\n";
    //std::cout << "MnvH1D_Aluminium Downstreamstream = " << fParamVal[2] << "\n";
    //std::cout << "MnvH1D_Aluminium Downstream concave  = " << fParamVal[3] << "\n";
    // if you want to access to these parameters, use:
    Double_t min_ChiSq,edm,errdef;
    Int_t nvpar,nparx,icstat;
    ptMinuit->mnstat(min_ChiSq,edm,errdef,nvpar,nparx,icstat);

    chisqrt = min_ChiSq;
    chisqrt_error = errdef;
    //void mnstat(Double_t &fmin, Double_t &fedm, Double_t &errdef, Int_t &npari, Int_t &nparx, Int_t &istat)
    //*-*-*-*-*Returns concerning the current status of the minimization*-*-*-*-*
    //*-*      =========================================================
    //*-*       User-called
    //*-*          Namely, it returns:
    //*-*        FMIN: the best function value found so far
    //*-*        FEDM: the estimated vertical distance remaining to minimum
    //*-*        ERRDEF: the value of UP defining parameter uncertainties
    //*-*        NPARI: the number of currently variable parameters
    //*-*        NPARX: the highest (external) parameter number defined by user
    //*-*        ISTAT: a status integer indicating how good is the covariance
    //*-*           matrix:  0= not calculated at all
    //*-*                    1= approximation only, not accurate
    //*-*                    2= full matrix, but forced positive-definite
    //*-*                    3= full accurate covariance matrix
    //*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

    //sbtool.SaveFitResults(min_ChiSq, fParamVal, fParamErr);

    // Plot only for Central Value

      //std::cout<<"running: setting fit values"<<std::endl;
      wgt_vector.push_back(fParamVal[0]);
      wgt_vector.push_back(fParamVal[1]);
      wgt_vector.push_back(fParamVal[2]);
      wgt_vector.push_back(fParamVal[3]);

      wgt_error.push_back(fParamErr[0]);
      wgt_error.push_back(fParamErr[1]);
      wgt_error.push_back(fParamErr[2]);
      wgt_error.push_back(fParamErr[3]);
        //sbtool.ApplyFitResults();
        //sbtool.Plot( fitName, pdf_label);
        //wgt = fParamVal[0];
        //wgt_error = fParamErr[0];logou



    //std::cout << "\n";
    //std::cout << " Minimum chi square = " << min_ChiSq<< "\n";
    //std::cout << " Estimated vert. distance to min. = " << edm << "\n";
    //std::cout << " Number of variable parameters = " << nvpar << "\n";
    //std::cout << " Highest number of parameters defined by user = " << nparx << "\n";
    //std::cout << " Status of covariance matrix = " << icstat << "\n";

    //std::cout << "\n";
    //ptMinuit->mnprin(1,min_ChiSq);
    //*-*-*-*Prints the values of the parameters at the time of the call*-*-*-*-*
    //*-*    ===========================================================
    //*-*        also prints other relevant information such as function value,
    //*-*        estimated distance to minimum, parameter errors, step sizes.
    //*-*
    //*-*         According to the value of IKODE, the printout is:
    //*-*    IKODE=INKODE= 0    only info about function value
    //*-*                  1    parameter values, errors, limits
    //*-*                  2    values, errors, step sizes, internal values
    //*-*                  3    values, errors, step sizes, first derivs.
    //*-*                  4    values, parabolic errors, MINOS errors
    //*-*    when INKODE=5, MNPRIN chooses IKODE=1,2, or 3, according to ISW(2)
    //*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

    delete ptMinuit;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void FitMinuit_Convolution_Full(Convolution_Tool sbtool, std::string fitName, std::string pdf_label, std::vector<double> &wgt_vector, std::vector<double> &wgt_error)
{
    //cout<<"======================================================================"<<endl;
    //cout<<"Universe = "<<sbtool.current_unv<<endl;
    //cout<<"======================================================================"<<endl;

    TMinuit *ptMinuit = new TMinuit(4);  //initialize TMinuit with a maximum of 4 params
    //
    //  select verbose level:
    //    default :     (58 lines in this test)
    //    -1 : minimum  ( 4 lines in this test)
    //     0 : low      (31 lines)
    //     1 : medium   (61 lines)
    //     2 : high     (89 lines)
    //     3 : maximum (199 lines in this test)
    //
    ptMinuit->SetPrintLevel(-1);
    // set the user function that calculates chi_square (the value to minimize)
    ptMinuit->SetFCN(calc_ChiSq_ConvolutionTool_Full);

    Double_t arglist[10];
    Int_t ierflg = 0;

    arglist[0] = 1;
    ptMinuit->mnexcm("SET ERR", arglist ,1,ierflg);

    // Set starting values and step sizes for parameters
    //      Start from 1.0 and step 0.01
    ptMinuit->mnparm(0, "FitParm_Aluminium_upstreamCap",          .05, 0.01, .01, 10.0 , ierflg);
    ptMinuit->mnparm(1, "FitParm_Aluminium_Barrel",               .05, 0.01, .01, 10.0 , ierflg);
    ptMinuit->mnparm(2, "FitParm_Aluminium_downstreamCap",        .05, 0.01, .01, 10.0 , ierflg);
    ptMinuit->mnparm(3, "FitParm_Aluminium_downstreamConcaveCap", .05, 0.01, .01, 10.0 , ierflg);

    // Now ready for minimization step
    arglist[0] = 20000;
    arglist[1] = 1.;
    ptMinuit->mnexcm("MIGRAD", arglist ,2,ierflg);

    // Print results
    //std::cout<<"\nPrint results from minuit\n";
    double fParamVal[4];
    double fParamErr[4];
    ptMinuit->GetParameter(0, fParamVal[0], fParamErr[0]);
    ptMinuit->GetParameter(1, fParamVal[1], fParamErr[1]);
    ptMinuit->GetParameter(2, fParamVal[2], fParamErr[2]);
    ptMinuit->GetParameter(3, fParamVal[3], fParamErr[3]);


    //std::cout << "MnvH1D_Aluminium Upstream = " << fParamVal[0] << "\n";
    //std::cout << "MnvH1D_Aluminium Barrel = " << fParamVal[1] << "\n";
    //std::cout << "MnvH1D_Aluminium Downstreamstream = " << fParamVal[2] << "\n";
    //std::cout << "MnvH1D_Aluminium Downstream concave  = " << fParamVal[3] << "\n";
    // if you want to access to these parameters, use:
    Double_t min_ChiSq,edm,errdef;
    Int_t nvpar,nparx,icstat;
    ptMinuit->mnstat(min_ChiSq,edm,errdef,nvpar,nparx,icstat);
    //void mnstat(Double_t &fmin, Double_t &fedm, Double_t &errdef, Int_t &npari, Int_t &nparx, Int_t &istat)
    //*-*-*-*-*Returns concerning the current status of the minimization*-*-*-*-*
    //*-*      =========================================================
    //*-*       User-called
    //*-*          Namely, it returns:
    //*-*        FMIN: the best function value found so far
    //*-*        FEDM: the estimated vertical distance remaining to minimum
    //*-*        ERRDEF: the value of UP defining parameter uncertainties
    //*-*        NPARI: the number of currently variable parameters
    //*-*        NPARX: the highest (external) parameter number defined by user
    //*-*        ISTAT: a status integer indicating how good is the covariance
    //*-*           matrix:  0= not calculated at all
    //*-*                    1= approximation only, not accurate
    //*-*                    2= full matrix, but forced positive-definite
    //*-*                    3= full accurate covariance matrix
    //*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

    //sbtool.SaveFitResults(min_ChiSq, fParamVal, fParamErr);

    // Plot only for Central Value

      //std::cout<<"running: setting fit values"<<std::endl;
      wgt_vector.push_back(fParamVal[0]);
      wgt_vector.push_back(fParamVal[1]);
      wgt_vector.push_back(fParamVal[2]);
      wgt_vector.push_back(fParamVal[3]);

      wgt_error.push_back(fParamErr[0]);
      wgt_error.push_back(fParamErr[1]);
      wgt_error.push_back(fParamErr[2]);
      wgt_error.push_back(fParamErr[3]);
        //sbtool.ApplyFitResults();
        //sbtool.Plot( fitName, pdf_label);
        //wgt = fParamVal[0];
        //wgt_error = fParamErr[0];



    //std::cout << "\n";
    //std::cout << " Minimum chi square = " << min_ChiSq<< "\n";
    //std::cout << " Estimated vert. distance to min. = " << edm << "\n";
    //std::cout << " Number of variable parameters = " << nvpar << "\n";
    //std::cout << " Highest number of parameters defined by user = " << nparx << "\n";
    //std::cout << " Status of covariance matrix = " << icstat << "\n";

    //std::cout << "\n";
    //ptMinuit->mnprin(1,min_ChiSq);
    //*-*-*-*Prints the values of the parameters at the time of the call*-*-*-*-*
    //*-*    ===========================================================
    //*-*        also prints other relevant information such as function value,
    //*-*        estimated distance to minimum, parameter errors, step sizes.
    //*-*
    //*-*         According to the value of IKODE, the printout is:
    //*-*    IKODE=INKODE= 0    only info about function value
    //*-*                  1    parameter values, errors, limits
    //*-*                  2    values, errors, step sizes, internal values
    //*-*                  3    values, errors, step sizes, first derivs.
    //*-*                  4    values, parabolic errors, MINOS errors
    //*-*    when INKODE=5, MNPRIN chooses IKODE=1,2, or 3, according to ISW(2)
    //*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

    delete ptMinuit;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void FitMinuit_Convolution_Empty_RZ(Convolution_Tool sbtool, std::string fitName, std::string pdf_label, std::vector<double> &wgt_vector, std::vector<double> &wgt_error)
{
    //cout<<"======================================================================"<<endl;
    //cout<<"Universe = "<<sbtool.current_unv<<endl;
    //cout<<"======================================================================"<<endl;

    TMinuit *ptMinuit = new TMinuit(4);  //initialize TMinuit with a maximum of 4 params
    //
    //  select verbose level:
    //    default :     (58 lines in this test)
    //    -1 : minimum  ( 4 lines in this test)
    //     0 : low      (31 lines)
    //     1 : medium   (61 lines)
    //     2 : high     (89 lines)
    //     3 : maximum (199 lines in this test)
    //
    ptMinuit->SetPrintLevel(-1);
    // set the user function that calculates chi_square (the value to minimize)
    ptMinuit->SetFCN(calc_ChiSq_ConvolutionTool_Empty_RZ);

    Double_t arglist[10];
    Int_t ierflg = 0;

    arglist[0] = 1;
    ptMinuit->mnexcm("SET ERR", arglist ,1,ierflg);

    // Set starting values and step sizes for parameters
    //      Start from 1.0 and step 0.01
    ptMinuit->mnparm(0, "FitParm_Aluminium_upstreamCap",          .05, 0.01, .01, 10.0 , ierflg);
    ptMinuit->mnparm(1, "FitParm_Aluminium_Barrel",               .05, 0.01, .01, 10.0 , ierflg);
    ptMinuit->mnparm(2, "FitParm_Aluminium_downstreamCap",        .05, 0.01, .01, 10.0 , ierflg);
    ptMinuit->mnparm(3, "FitParm_Aluminium_downstreamConcaveCap", .05, 0.01, .01, 10.0 , ierflg);

    // Now ready for minimization step
    arglist[0] = 20000;
    arglist[1] = 1.;
    ptMinuit->mnexcm("MIGRAD", arglist ,2,ierflg);

    // Print results
    //std::cout<<"\nPrint results from minuit\n";
    double fParamVal[4];
    double fParamErr[4];
    ptMinuit->GetParameter(0, fParamVal[0], fParamErr[0]);
    ptMinuit->GetParameter(1, fParamVal[1], fParamErr[1]);
    ptMinuit->GetParameter(2, fParamVal[2], fParamErr[2]);
    ptMinuit->GetParameter(3, fParamVal[3], fParamErr[3]);


    //std::cout << "MnvH1D_Aluminium Upstream = " << fParamVal[0] << "\n";
    //std::cout << "MnvH1D_Aluminium Barrel = " << fParamVal[1] << "\n";
    //std::cout << "MnvH1D_Aluminium Downstreamstream = " << fParamVal[2] << "\n";
    //std::cout << "MnvH1D_Aluminium Downstream concave  = " << fParamVal[3] << "\n";
    // if you want to access to these parameters, use:
    Double_t min_ChiSq,edm,errdef;
    Int_t nvpar,nparx,icstat;
    ptMinuit->mnstat(min_ChiSq,edm,errdef,nvpar,nparx,icstat);
    //void mnstat(Double_t &fmin, Double_t &fedm, Double_t &errdef, Int_t &npari, Int_t &nparx, Int_t &istat)
    //*-*-*-*-*Returns concerning the current status of the minimization*-*-*-*-*
    //*-*      =========================================================
    //*-*       User-called
    //*-*          Namely, it returns:
    //*-*        FMIN: the best function value found so far
    //*-*        FEDM: the estimated vertical distance remaining to minimum
    //*-*        ERRDEF: the value of UP defining parameter uncertainties
    //*-*        NPARI: the number of currently variable parameters
    //*-*        NPARX: the highest (external) parameter number defined by user
    //*-*        ISTAT: a status integer indicating how good is the covariance
    //*-*           matrix:  0= not calculated at all
    //*-*                    1= approximation only, not accurate
    //*-*                    2= full matrix, but forced positive-definite
    //*-*                    3= full accurate covariance matrix
    //*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

    //sbtool.SaveFitResults(min_ChiSq, fParamVal, fParamErr);

    // Plot only for Central Value

      //std::cout<<"running: setting fit values"<<std::endl;
      wgt_vector.push_back(fParamVal[0]);
      wgt_vector.push_back(fParamVal[1]);
      wgt_vector.push_back(fParamVal[2]);
      wgt_vector.push_back(fParamVal[3]);

      wgt_error.push_back(fParamErr[0]);
      wgt_error.push_back(fParamErr[1]);
      wgt_error.push_back(fParamErr[2]);
      wgt_error.push_back(fParamErr[3]);
        //sbtool.ApplyFitResults();
        //sbtool.Plot( fitName, pdf_label);
        //wgt = fParamVal[0];
        //wgt_error = fParamErr[0];



    //std::cout << "\n";
    //std::cout << " Minimum chi square = " << min_ChiSq<< "\n";
    //std::cout << " Estimated vert. distance to min. = " << edm << "\n";
    //std::cout << " Number of variable parameters = " << nvpar << "\n";
    //std::cout << " Highest number of parameters defined by user = " << nparx << "\n";
    //std::cout << " Status of covariance matrix = " << icstat << "\n";

    //std::cout << "\n";
    //ptMinuit->mnprin(1,min_ChiSq);
    //*-*-*-*Prints the values of the parameters at the time of the call*-*-*-*-*
    //*-*    ===========================================================
    //*-*        also prints other relevant information such as function value,
    //*-*        estimated distance to minimum, parameter errors, step sizes.
    //*-*
    //*-*         According to the value of IKODE, the printout is:
    //*-*    IKODE=INKODE= 0    only info about function value
    //*-*                  1    parameter values, errors, limits
    //*-*                  2    values, errors, step sizes, internal values
    //*-*                  3    values, errors, step sizes, first derivs.
    //*-*                  4    values, parabolic errors, MINOS errors
    //*-*    when INKODE=5, MNPRIN chooses IKODE=1,2, or 3, according to ISW(2)
    //*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

    delete ptMinuit;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void FitMinuit_Convolution_EmptyLogchi2(Convolution_Tool sbtool, std::string fitName, std::string pdf_label, std::vector<double> &wgt_vector, std::vector<double> &wgt_error, double &chisqrt, double &chisqrt_error)
{
    //cout<<"======================================================================"<<endl;
    //cout<<"Universe = "<<sbtool.current_unv<<endl;
    //cout<<"======================================================================"<<endl;

    TMinuit *ptMinuit = new TMinuit(4);  //initialize TMinuit with a maximum of 4 params
    //
    //  select verbose level:
    //    default :     (58 lines in this test)
    //    -1 : minimum  ( 4 lines in this test)
    //     0 : low      (31 lines)
    //     1 : medium   (61 lines)
    //     2 : high     (89 lines)
    //     3 : maximum (199 lines in this test)
    //
    ptMinuit->SetPrintLevel(-1);
    // set the user function that calculates chi_square (the value to minimize)
    ptMinuit->SetFCN(calc_ChiSq_ConvolutionTool_EmptyLog);

    Double_t arglist[10];
    Int_t ierflg = 0;

    arglist[0] = 1;
    ptMinuit->mnexcm("SET ERR", arglist ,1,ierflg);

    // Set starting values and step sizes for parameters
    //      Start from 1.0 and step 0.01
    ptMinuit->mnparm(0, "FitParm_Aluminium_upstreamCap",          .05, 0.01, .01, 10.0 , ierflg);
    ptMinuit->mnparm(1, "FitParm_Aluminium_Barrel",               .05, 0.01, .01, 10.0 , ierflg);
    ptMinuit->mnparm(2, "FitParm_Aluminium_downstreamCap",        .05, 0.01, .01, 10.0 , ierflg);
    ptMinuit->mnparm(3, "FitParm_Aluminium_downstreamConcaveCap", .05, 0.01, .01, 10.0 , ierflg);

    // Now ready for minimization step
    arglist[0] = 20000;
    arglist[1] = 1.;
    ptMinuit->mnexcm("MIGRAD", arglist ,2,ierflg);

    // Print results
    //std::cout<<"\nPrint results from minuit\n";
    double fParamVal[4];
    double fParamErr[4];
    ptMinuit->GetParameter(0, fParamVal[0], fParamErr[0]);
    ptMinuit->GetParameter(1, fParamVal[1], fParamErr[1]);
    ptMinuit->GetParameter(2, fParamVal[2], fParamErr[2]);
    ptMinuit->GetParameter(3, fParamVal[3], fParamErr[3]);


    //std::cout << "MnvH1D_Aluminium Upstream = " << fParamVal[0] << "\n";
    //std::cout << "MnvH1D_Aluminium Barrel = " << fParamVal[1] << "\n";
    //std::cout << "MnvH1D_Aluminium Downstreamstream = " << fParamVal[2] << "\n";
    //std::cout << "MnvH1D_Aluminium Downstream concave  = " << fParamVal[3] << "\n";
    // if you want to access to these parameters, use:
    Double_t min_ChiSq,edm,errdef;
    Int_t nvpar,nparx,icstat;
    ptMinuit->mnstat(min_ChiSq,edm,errdef,nvpar,nparx,icstat);
    chisqrt = min_ChiSq ;
    chisqrt_error = errdef;

    //void mnstat(Double_t &fmin, Double_t &fedm, Double_t &errdef, Int_t &npari, Int_t &nparx, Int_t &istat)
    //*-*-*-*-*Returns concerning the current status of the minimization*-*-*-*-*
    //*-*      =========================================================
    //*-*       User-called
    //*-*          Namely, it returns:
    //*-*        FMIN: the best function value found so far
    //*-*        FEDM: the estimated vertical distance remaining to minimum
    //*-*        ERRDEF: the value of UP defining parameter uncertainties
    //*-*        NPARI: the number of currently variable parameters
    //*-*        NPARX: the highest (external) parameter number defined by user
    //*-*        ISTAT: a status integer indicating how good is the covariance
    //*-*           matrix:  0= not calculated at all
    //*-*                    1= approximation only, not accurate
    //*-*                    2= full matrix, but forced positive-definite
    //*-*                    3= full accurate covariance matrix
    //*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

    //sbtool.SaveFitResults(min_ChiSq, fParamVal, fParamErr);

    // Plot only for Central Value

      //std::cout<<"running: setting fit values"<<std::endl;
      wgt_vector.push_back(fParamVal[0]);
      wgt_vector.push_back(fParamVal[1]);
      wgt_vector.push_back(fParamVal[2]);
      wgt_vector.push_back(fParamVal[3]);

      wgt_error.push_back(fParamErr[0]);
      wgt_error.push_back(fParamErr[1]);
      wgt_error.push_back(fParamErr[2]);
      wgt_error.push_back(fParamErr[3]);
        //sbtool.ApplyFitResults();
        //sbtool.Plot( fitName, pdf_label);
        //wgt = fParamVal[0];
        //wgt_error = fParamErr[0];



    //std::cout << "\n";
    //std::cout << " Minimum chi square = " << min_ChiSq<< "\n";
    //std::cout << " Estimated vert. distance to min. = " << edm << "\n";
    //std::cout << " Number of variable parameters = " << nvpar << "\n";
    //std::cout << " Highest number of parameters defined by user = " << nparx << "\n";
    //std::cout << " Status of covariance matrix = " << icstat << "\n";

    //std::cout << "\n";
    //ptMinuit->mnprin(1,min_ChiSq);
    //*-*-*-*Prints the values of the parameters at the time of the call*-*-*-*-*
    //*-*    ===========================================================
    //*-*        also prints other relevant information such as function value,
    //*-*        estimated distance to minimum, parameter errors, step sizes.
    //*-*
    //*-*         According to the value of IKODE, the printout is:
    //*-*    IKODE=INKODE= 0    only info about function value
    //*-*                  1    parameter values, errors, limits
    //*-*                  2    values, errors, step sizes, internal values
    //*-*                  3    values, errors, step sizes, first derivs.
    //*-*                  4    values, parabolic errors, MINOS errors
    //*-*    when INKODE=5, MNPRIN chooses IKODE=1,2, or 3, according to ISW(2)
    //*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

    delete ptMinuit;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void FitMinuit_Convolution_FullLogchi2(Convolution_Tool sbtool, std::string fitName, std::string pdf_label, std::vector<double> &wgt_vector, std::vector<double> &wgt_error)
{
    //cout<<"======================================================================"<<endl;
    //cout<<"Universe = "<<sbtool.current_unv<<endl;
    //cout<<"======================================================================"<<endl;

    TMinuit *ptMinuit = new TMinuit(4);  //initialize TMinuit with a maximum of 4 params
    //
    //  select verbose level:
    //    default :     (58 lines in this test)
    //    -1 : minimum  ( 4 lines in this test)
    //     0 : low      (31 lines)
    //     1 : medium   (61 lines)
    //     2 : high     (89 lines)
    //     3 : maximum (199 lines in this test)
    //
    ptMinuit->SetPrintLevel(-1);
    // set the user function that calculates chi_square (the value to minimize)
    ptMinuit->SetFCN(calc_ChiSq_ConvolutionTool_FullLog);

    Double_t arglist[10];
    Int_t ierflg = 0;

    arglist[0] = 1;
    ptMinuit->mnexcm("SET ERR", arglist ,1,ierflg);

    // Set starting values and step sizes for parameters
    //      Start from 1.0 and step 0.01
    ptMinuit->mnparm(0, "FitParm_Aluminium_upstreamCap",          .05, 0.01, .01, 10.0 , ierflg);
    ptMinuit->mnparm(1, "FitParm_Aluminium_Barrel",               .05, 0.01, .01, 10.0 , ierflg);
    ptMinuit->mnparm(2, "FitParm_Aluminium_downstreamCap",        .05, 0.01, .01, 10.0 , ierflg);
    ptMinuit->mnparm(3, "FitParm_Aluminium_downstreamConcaveCap", .05, 0.01, .01, 10.0 , ierflg);

    // Now ready for minimization step
    arglist[0] = 20000;
    arglist[1] = 1.;
    ptMinuit->mnexcm("MIGRAD", arglist ,2,ierflg);

    // Print results
    //std::cout<<"\nPrint results from minuit\n";
    double fParamVal[4];
    double fParamErr[4];
    ptMinuit->GetParameter(0, fParamVal[0], fParamErr[0]);
    ptMinuit->GetParameter(1, fParamVal[1], fParamErr[1]);
    ptMinuit->GetParameter(2, fParamVal[2], fParamErr[2]);
    ptMinuit->GetParameter(3, fParamVal[3], fParamErr[3]);


    //std::cout << "MnvH1D_Aluminium Upstream = " << fParamVal[0] << "\n";
    //std::cout << "MnvH1D_Aluminium Barrel = " << fParamVal[1] << "\n";
    //std::cout << "MnvH1D_Aluminium Downstreamstream = " << fParamVal[2] << "\n";
    //std::cout << "MnvH1D_Aluminium Downstream concave  = " << fParamVal[3] << "\n";
    // if you want to access to these parameters, use:
    Double_t min_ChiSq,edm,errdef;
    Int_t nvpar,nparx,icstat;
    ptMinuit->mnstat(min_ChiSq,edm,errdef,nvpar,nparx,icstat);
    //void mnstat(Double_t &fmin, Double_t &fedm, Double_t &errdef, Int_t &npari, Int_t &nparx, Int_t &istat)
    //*-*-*-*-*Returns concerning the current status of the minimization*-*-*-*-*
    //*-*      =========================================================
    //*-*       User-called
    //*-*          Namely, it returns:
    //*-*        FMIN: the best function value found so far
    //*-*        FEDM: the estimated vertical distance remaining to minimum
    //*-*        ERRDEF: the value of UP defining parameter uncertainties
    //*-*        NPARI: the number of currently variable parameters
    //*-*        NPARX: the highest (external) parameter number defined by user
    //*-*        ISTAT: a status integer indicating how good is the covariance
    //*-*           matrix:  0= not calculated at all
    //*-*                    1= approximation only, not accurate
    //*-*                    2= full matrix, but forced positive-definite
    //*-*                    3= full accurate covariance matrix
    //*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

    //sbtool.SaveFitResults(min_ChiSq, fParamVal, fParamErr);

    // Plot only for Central Value

      //std::cout<<"running: setting fit values"<<std::endl;
      wgt_vector.push_back(fParamVal[0]);
      wgt_vector.push_back(fParamVal[1]);
      wgt_vector.push_back(fParamVal[2]);
      wgt_vector.push_back(fParamVal[3]);

      wgt_error.push_back(fParamErr[0]);
      wgt_error.push_back(fParamErr[1]);
      wgt_error.push_back(fParamErr[2]);
      wgt_error.push_back(fParamErr[3]);
        //sbtool.ApplyFitResults();
        //sbtool.Plot( fitName, pdf_label);
        //wgt = fParamVal[0];
        //wgt_error = fParamErr[0];



    //std::cout << "\n";
    //std::cout << " Minimum chi square = " << min_ChiSq<< "\n";
    //std::cout << " Estimated vert. distance to min. = " << edm << "\n";
    //std::cout << " Number of variable parameters = " << nvpar << "\n";
    //std::cout << " Highest number of parameters defined by user = " << nparx << "\n";
    //std::cout << " Status of covariance matrix = " << icstat << "\n";

    //std::cout << "\n";
    //ptMinuit->mnprin(1,min_ChiSq);
    //*-*-*-*Prints the values of the parameters at the time of the call*-*-*-*-*
    //*-*    ===========================================================
    //*-*        also prints other relevant information such as function value,
    //*-*        estimated distance to minimum, parameter errors, step sizes.
    //*-*
    //*-*         According to the value of IKODE, the printout is:
    //*-*    IKODE=INKODE= 0    only info about function value
    //*-*                  1    parameter values, errors, limits
    //*-*                  2    values, errors, step sizes, internal values
    //*-*                  3    values, errors, step sizes, first derivs.
    //*-*                  4    values, parabolic errors, MINOS errors
    //*-*    when INKODE=5, MNPRIN chooses IKODE=1,2, or 3, according to ISW(2)
    //*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

    delete ptMinuit;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void FitMinuit_Convolution_CombinedLogchi2(Convolution_Tool sbtool, std::string fitName, std::string pdf_label, std::vector<double> &wgt_vector, std::vector<double> &wgt_error, double &chi2sqrtFit,  double &chi2sqrtFit_error)
{
    //cout<<"======================================================================"<<endl;
    //cout<<"Universe = "<<sbtool.current_unv<<endl;
    //cout<<"======================================================================"<<endl;

    TMinuit *ptMinuit = new TMinuit(8);  //initialize TMinuit with a maximum of 4 params
    //
    //  select verbose level:
    //    default :     (58 lines in this test)
    //    -1 : minimum  ( 4 lines in this test)
    //     0 : low      (31 lines)
    //     1 : medium   (61 lines)
    //     2 : high     (89 lines)
    //     3 : maximum (199 lines in this test)
    //
    ptMinuit->SetPrintLevel(-1);
    // set the user function that calculates chi_square (the value to minimize)
    ptMinuit->SetFCN(calc_ChiSq_ConvolutionTool_Combined_Log);

    Double_t arglist[10];
    Int_t ierflg = 0;

    arglist[0] = 1;
    ptMinuit->mnexcm("SET ERR", arglist ,1,ierflg);

    // Set starting values and step sizes for parameters
    //      Start from 1.0 and step 0.01
    ptMinuit->mnparm(0, "Empty_FitParm_Aluminium_upstreamCap",          .05, 0.01, .01, 10.0 , ierflg);
    ptMinuit->mnparm(1, "Empty_FitParm_Aluminium_Barrel",               .05, 0.01, .01, 10.0 , ierflg);
    ptMinuit->mnparm(2, "Empty_FitParm_Aluminium_downstreamCap",        .05, 0.01, .01, 10.0 , ierflg);
    ptMinuit->mnparm(3, "Empty_FitParm_Aluminium_downstreamConcaveCap", .05, 0.01, .01, 10.0 , ierflg);

    ptMinuit->mnparm(4, "Empty_FitParm_Aluminium_upstreamCap",          .05, 0.01, .01, 10.0 , ierflg);
    ptMinuit->mnparm(5, "Empty_FitParm_Aluminium_Barrel",               .05, 0.01, .01, 10.0 , ierflg);
    ptMinuit->mnparm(6, "Empty_FitParm_Aluminium_downstreamCap",        .05, 0.01, .01, 10.0 , ierflg);
    ptMinuit->mnparm(7, "Empty_FitParm_Aluminium_downstreamConcaveCap", .05, 0.01, .01, 10.0 , ierflg);


    // Now ready for minimization step
    arglist[0] = 20000;
    arglist[1] = 1.;
    ptMinuit->mnexcm("MIGRAD", arglist ,2,ierflg);

    // Print results
    //std::cout<<"\nPrint results from minuit\n";
    double fParamVal[8];
    double fParamErr[8];
    ptMinuit->GetParameter(0, fParamVal[0], fParamErr[0]);
    ptMinuit->GetParameter(1, fParamVal[1], fParamErr[1]);
    ptMinuit->GetParameter(2, fParamVal[2], fParamErr[2]);
    ptMinuit->GetParameter(3, fParamVal[3], fParamErr[3]);
    ptMinuit->GetParameter(4, fParamVal[4], fParamErr[4]);
    ptMinuit->GetParameter(5, fParamVal[5], fParamErr[5]);
    ptMinuit->GetParameter(6, fParamVal[6], fParamErr[6]);
    ptMinuit->GetParameter(7, fParamVal[7], fParamErr[7]);

    //std::cout << "MnvH1D_Aluminium Upstream = " << fParamVal[0] << "\n";
    //std::cout << "MnvH1D_Aluminium Barrel = " << fParamVal[1] << "\n";
    //std::cout << "MnvH1D_Aluminium Downstreamstream = " << fParamVal[2] << "\n";
    //std::cout << "MnvH1D_Aluminium Downstream concave  = " << fParamVal[3] << "\n";
    // if you want to access to these parameters, use:
    Double_t min_ChiSq,edm,errdef;
    Int_t nvpar,nparx,icstat;
    ptMinuit->mnstat(min_ChiSq,edm,errdef,nvpar,nparx,icstat);
    //void mnstat(Double_t &fmin, Double_t &fedm, Double_t &errdef, Int_t &npari, Int_t &nparx, Int_t &istat)
    //*-*-*-*-*Returns concerning the current status of the minimization*-*-*-*-*
    //*-*      =========================================================
    //*-*       User-called
    //*-*          Namely, it returns:
    //*-*        FMIN: the best function value found so far
    //*-*        FEDM: the estimated vertical distance remaining to minimum
    //*-*        ERRDEF: the value of UP defining parameter uncertainties
    //*-*        NPARI: the number of currently variable parameters
    //*-*        NPARX: the highest (external) parameter number defined by user
    //*-*        ISTAT: a status integer indicating how good is the covariance
    //*-*           matrix:  0= not calculated at all
    //*-*                    1= approximation only, not accurate
    //*-*                    2= full matrix, but forced positive-definite
    //*-*                    3= full accurate covariance matrix
    //*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
    chi2sqrtFit = min_ChiSq;
    chi2sqrtFit_error = errdef;


    //sbtool.SaveFitResults(min_ChiSq, fParamVal, fParamErr);

    // Plot only for Central Value

      //std::cout<<"running: setting fit values"<<std::endl;
      wgt_vector.push_back(fParamVal[0]);
      wgt_vector.push_back(fParamVal[1]);
      wgt_vector.push_back(fParamVal[2]);
      wgt_vector.push_back(fParamVal[3]);
      wgt_vector.push_back(fParamVal[4]);
      wgt_vector.push_back(fParamVal[5]);
      wgt_vector.push_back(fParamVal[6]);
      wgt_vector.push_back(fParamVal[7]);

      wgt_error.push_back(fParamErr[0]);
      wgt_error.push_back(fParamErr[1]);
      wgt_error.push_back(fParamErr[2]);
      wgt_error.push_back(fParamErr[3]);
      wgt_error.push_back(fParamErr[4]);
      wgt_error.push_back(fParamErr[5]);
      wgt_error.push_back(fParamErr[6]);
      wgt_error.push_back(fParamErr[7]);


        //sbtool.ApplyFitResults();
        //sbtool.Plot( fitName, pdf_label);
        //wgt = fParamVal[0];
        //wgt_error = fParamErr[0];



    //std::cout << "\n";
    //std::cout << " Minimum chi square = " << min_ChiSq<< "\n";
    //std::cout << " Estimated vert. distance to min. = " << edm << "\n";
    //std::cout << " Number of variable parameters = " << nvpar << "\n";
    //std::cout << " Highest number of parameters defined by user = " << nparx << "\n";
    //std::cout << " Status of covariance matrix = " << icstat << "\n";

    //std::cout << "\n";
    //ptMinuit->mnprin(1,min_ChiSq);
    //*-*-*-*Prints the values of the parameters at the time of the call*-*-*-*-*
    //*-*    ===========================================================
    //*-*        also prints other relevant information such as function value,
    //*-*        estimated distance to minimum, parameter errors, step sizes.
    //*-*
    //*-*         According to the value of IKODE, the printout is:
    //*-*    IKODE=INKODE= 0    only info about function value
    //*-*                  1    parameter values, errors, limits
    //*-*                  2    values, errors, step sizes, internal values
    //*-*                  3    values, errors, step sizes, first derivs.
    //*-*                  4    values, parabolic errors, MINOS errors
    //*-*    when INKODE=5, MNPRIN chooses IKODE=1,2, or 3, according to ISW(2)
    //*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

    delete ptMinuit;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void FitMinuit_Convolution_Combined_chi2(Convolution_Tool sbtool, std::string fitName, std::string pdf_label,
  std::vector<double> &wgt_vector, std::vector<double> &wgt_error, double &chisqrt, double &chisqrt_error)
{
    //cout<<"======================================================================"<<endl;
    //cout<<"Universe = "<<sbtool.current_unv<<endl;
    //cout<<"======================================================================"<<endl;

    TMinuit *ptMinuit = new TMinuit(8);  //initialize TMinuit with a maximum of 4 params
    //
    //  select verbose level:
    //    default :     (58 lines in this test)
    //    -1 : minimum  ( 4 lines in this test)
    //     0 : low      (31 lines)
    //     1 : medium   (61 lines)
    //     2 : high     (89 lines)
    //     3 : maximum (199 lines in this test)
    //
    ptMinuit->SetPrintLevel(-1);
    // set the user function that calculates chi_square (the value to minimize)
    ptMinuit->SetFCN(calc_ChiSq_ConvolutionTool_Combined);

    Double_t arglist[10];
    Int_t ierflg = 0;

    arglist[0] = 1;
    ptMinuit->mnexcm("SET ERR", arglist ,1,ierflg);

    // Set starting values and step sizes for parameters
    //      Start from 1.0 and step 0.01
    ptMinuit->mnparm(0, "Empty_FitParm_Aluminium_upstreamCap",          .05, 0.01, .01, 10.0 , ierflg);
    ptMinuit->mnparm(1, "Empty_FitParm_Aluminium_Barrel",               .05, 0.01, .01, 10.0 , ierflg);
    ptMinuit->mnparm(2, "Empty_FitParm_Aluminium_downstreamCap",        .05, 0.01, .01, 10.0 , ierflg);
    ptMinuit->mnparm(3, "Empty_FitParm_Aluminium_downstreamConcaveCap", .05, 0.01, .01, 10.0 , ierflg);

    ptMinuit->mnparm(4, "Empty_FitParm_Aluminium_upstreamCap",          .05, 0.01, .01, 10.0 , ierflg);
    ptMinuit->mnparm(5, "Empty_FitParm_Aluminium_Barrel",               .05, 0.01, .01, 10.0 , ierflg);
    ptMinuit->mnparm(6, "Empty_FitParm_Aluminium_downstreamCap",        .05, 0.01, .01, 10.0 , ierflg);
    ptMinuit->mnparm(7, "Empty_FitParm_Aluminium_downstreamConcaveCap", .05, 0.01, .01, 10.0 , ierflg);


    // Now ready for minimization step
    arglist[0] = 20000;
    arglist[1] = 1.;
    ptMinuit->mnexcm("MIGRAD", arglist ,2,ierflg);

    // Print results
    //std::cout<<"\nPrint results from minuit\n";
    double fParamVal[8];
    double fParamErr[8];
    ptMinuit->GetParameter(0, fParamVal[0], fParamErr[0]);
    ptMinuit->GetParameter(1, fParamVal[1], fParamErr[1]);
    ptMinuit->GetParameter(2, fParamVal[2], fParamErr[2]);
    ptMinuit->GetParameter(3, fParamVal[3], fParamErr[3]);
    ptMinuit->GetParameter(4, fParamVal[4], fParamErr[4]);
    ptMinuit->GetParameter(5, fParamVal[5], fParamErr[5]);
    ptMinuit->GetParameter(6, fParamVal[6], fParamErr[6]);
    ptMinuit->GetParameter(7, fParamVal[7], fParamErr[7]);

    //std::cout << "MnvH1D_Aluminium Upstream = " << fParamVal[0] << "\n";
    //std::cout << "MnvH1D_Aluminium Barrel = " << fParamVal[1] << "\n";
    //std::cout << "MnvH1D_Aluminium Downstreamstream = " << fParamVal[2] << "\n";
    //std::cout << "MnvH1D_Aluminium Downstream concave  = " << fParamVal[3] << "\n";
    // if you want to access to these parameters, use:
    Double_t min_ChiSq,edm,errdef;
    Int_t nvpar,nparx,icstat;
    ptMinuit->mnstat(min_ChiSq,edm,errdef,nvpar,nparx,icstat);
    //void mnstat(Double_t &fmin, Double_t &fedm, Double_t &errdef, Int_t &npari, Int_t &nparx, Int_t &istat)
    //*-*-*-*-*Returns concerning the current status of the minimization*-*-*-*-*
    //*-*      =========================================================
    //*-*       User-called
    //*-*          Namely, it returns:
    //*-*        FMIN: the best function value found so far
    //*-*        FEDM: the estimated vertical distance remaining to minimum
    //*-*        ERRDEF: the value of UP defining parameter uncertainties
    //*-*        NPARI: the number of currently variable parameters
    //*-*        NPARX: the highest (external) parameter number defined by user
    //*-*        ISTAT: a status integer indicating how good is the covariance
    //*-*           matrix:  0= not calculated at all
    //*-*                    1= approximation only, not accurate
    //*-*                    2= full matrix, but forced positive-definite
    //*-*                    3= full accurate covariance matrix
    //*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

    //sbtool.SaveFitResults(min_ChiSq, fParamVal, fParamErr);

    // Plot only for Central Value
    min_ChiSq = chisqrt;
    chisqrt_error = errdef;
      //std::cout<<"running: setting fit values"<<std::endl;
      wgt_vector.push_back(fParamVal[0]);
      wgt_vector.push_back(fParamVal[1]);
      wgt_vector.push_back(fParamVal[2]);
      wgt_vector.push_back(fParamVal[3]);
      wgt_vector.push_back(fParamVal[4]);
      wgt_vector.push_back(fParamVal[5]);
      wgt_vector.push_back(fParamVal[6]);
      wgt_vector.push_back(fParamVal[7]);

      wgt_error.push_back(fParamErr[0]);
      wgt_error.push_back(fParamErr[1]);
      wgt_error.push_back(fParamErr[2]);
      wgt_error.push_back(fParamErr[3]);
      wgt_error.push_back(fParamErr[4]);
      wgt_error.push_back(fParamErr[5]);
      wgt_error.push_back(fParamErr[6]);
      wgt_error.push_back(fParamErr[7]);


        //sbtool.ApplyFitResults();
        //sbtool.Plot( fitName, pdf_label);
        //wgt = fParamVal[0];
        //wgt_error = fParamErr[0];



    //std::cout << "\n";
    //std::cout << " Minimum chi square = " << min_ChiSq<< "\n";
    //std::cout << " Estimated vert. distance to min. = " << edm << "\n";
    //std::cout << " Number of variable parameters = " << nvpar << "\n";
    //std::cout << " Highest number of parameters defined by user = " << nparx << "\n";
    //std::cout << " Status of covariance matrix = " << icstat << "\n";

    //std::cout << "\n";
    //ptMinuit->mnprin(1,min_ChiSq);
    //*-*-*-*Prints the values of the parameters at the time of the call*-*-*-*-*
    //*-*    ===========================================================
    //*-*        also prints other relevant information such as function value,
    //*-*        estimated distance to minimum, parameter errors, step sizes.
    //*-*
    //*-*         According to the value of IKODE, the printout is:
    //*-*    IKODE=INKODE= 0    only info about function value
    //*-*                  1    parameter values, errors, limits
    //*-*                  2    values, errors, step sizes, internal values
    //*-*                  3    values, errors, step sizes, first derivs.
    //*-*                  4    values, parabolic errors, MINOS errors
    //*-*    when INKODE=5, MNPRIN chooses IKODE=1,2, or 3, according to ISW(2)
    //*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

    delete ptMinuit;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void FitMinuit_Convolution_Combined_1set(Convolution_Tool sbtool, std::string fitName, std::string pdf_label, std::vector<double> &wgt_vector, std::vector<double> &wgt_error)
{
    //cout<<"======================================================================"<<endl;
    //cout<<"Universe = "<<sbtool.current_unv<<endl;
    //cout<<"======================================================================"<<endl;

    TMinuit *ptMinuit = new TMinuit(4);  //initialize TMinuit with a maximum of 4 params
    //
    //  select verbose level:
    //    default :     (58 lines in this test)
    //    -1 : minimum  ( 4 lines in this test)
    //     0 : low      (31 lines)
    //     1 : medium   (61 lines)
    //     2 : high     (89 lines)
    //     3 : maximum (199 lines in this test)
    //
    ptMinuit->SetPrintLevel(-1);
    // set the user function that calculates chi_square (the value to minimize)
    ptMinuit->SetFCN(calc_ChiSq_ConvolutionTool_Combined_1set);

    Double_t arglist[10];
    Int_t ierflg = 0;

    arglist[0] = 1;
    ptMinuit->mnexcm("SET ERR", arglist ,1,ierflg);

    // Set starting values and step sizes for parameters
    //      Start from 1.0 and step 0.01
    ptMinuit->mnparm(0, "FitParm_Aluminium_upstreamCap",          .05, 0.01, .01, 10.0 , ierflg);
    ptMinuit->mnparm(1, "FitParm_Aluminium_Barrel",               .05, 0.01, .01, 10.0 , ierflg);
    ptMinuit->mnparm(2, "FitParm_Aluminium_downstreamCap",        .05, 0.01, .01, 10.0 , ierflg);
    ptMinuit->mnparm(3, "FitParm_Aluminium_downstreamConcaveCap", .05, 0.01, .01, 10.0 , ierflg);

    // Now ready for minimization step
    arglist[0] = 20000;
    arglist[1] = 1.;
    ptMinuit->mnexcm("MIGRAD", arglist ,2,ierflg);

    // Print results
    //std::cout<<"\nPrint results from minuit\n";
    double fParamVal[4];
    double fParamErr[4];
    ptMinuit->GetParameter(0, fParamVal[0], fParamErr[0]);
    ptMinuit->GetParameter(1, fParamVal[1], fParamErr[1]);
    ptMinuit->GetParameter(2, fParamVal[2], fParamErr[2]);
    ptMinuit->GetParameter(3, fParamVal[3], fParamErr[3]);


    //std::cout << "MnvH1D_Aluminium Upstream = " << fParamVal[0] << "\n";
    //std::cout << "MnvH1D_Aluminium Barrel = " << fParamVal[1] << "\n";
    //std::cout << "MnvH1D_Aluminium Downstreamstream = " << fParamVal[2] << "\n";
    //std::cout << "MnvH1D_Aluminium Downstream concave  = " << fParamVal[3] << "\n";
    // if you want to access to these parameters, use:
    Double_t min_ChiSq,edm,errdef;
    Int_t nvpar,nparx,icstat;
    ptMinuit->mnstat(min_ChiSq,edm,errdef,nvpar,nparx,icstat);
    //void mnstat(Double_t &fmin, Double_t &fedm, Double_t &errdef, Int_t &npari, Int_t &nparx, Int_t &istat)
    //*-*-*-*-*Returns concerning the current status of the minimization*-*-*-*-*
    //*-*      =========================================================
    //*-*       User-called
    //*-*          Namely, it returns:
    //*-*        FMIN: the best function value found so far
    //*-*        FEDM: the estimated vertical distance remaining to minimum
    //*-*        ERRDEF: the value of UP defining parameter uncertainties
    //*-*        NPARI: the number of currently variable parameters
    //*-*        NPARX: the highest (external) parameter number defined by user
    //*-*        ISTAT: a status integer indicating how good is the covariance
    //*-*           matrix:  0= not calculated at all
    //*-*                    1= approximation only, not accurate
    //*-*                    2= full matrix, but forced positive-definite
    //*-*                    3= full accurate covariance matrix
    //*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

    //sbtool.SaveFitResults(min_ChiSq, fParamVal, fParamErr);

    // Plot only for Central Value

      //std::cout<<"running: setting fit values"<<std::endl;
      wgt_vector.push_back(fParamVal[0]);
      wgt_vector.push_back(fParamVal[1]);
      wgt_vector.push_back(fParamVal[2]);
      wgt_vector.push_back(fParamVal[3]);

      wgt_error.push_back(fParamErr[0]);
      wgt_error.push_back(fParamErr[1]);
      wgt_error.push_back(fParamErr[2]);
      wgt_error.push_back(fParamErr[3]);
        //sbtool.ApplyFitResults();
        //sbtool.Plot( fitName, pdf_label);
        //wgt = fParamVal[0];
        //wgt_error = fParamErr[0];



    //std::cout << "\n";
    //std::cout << " Minimum chi square = " << min_ChiSq<< "\n";
    //std::cout << " Estimated vert. distance to min. = " << edm << "\n";
    //std::cout << " Number of variable parameters = " << nvpar << "\n";
    //std::cout << " Highest number of parameters defined by user = " << nparx << "\n";
    //std::cout << " Status of covariance matrix = " << icstat << "\n";

    //std::cout << "\n";
    //ptMinuit->mnprin(1,min_ChiSq);
    //*-*-*-*Prints the values of the parameters at the time of the call*-*-*-*-*
    //*-*    ===========================================================
    //*-*        also prints other relevant information such as function value,
    //*-*        estimated distance to minimum, parameter errors, step sizes.
    //*-*
    //*-*         According to the value of IKODE, the printout is:
    //*-*    IKODE=INKODE= 0    only info about function value
    //*-*                  1    parameter values, errors, limits
    //*-*                  2    values, errors, step sizes, internal values
    //*-*                  3    values, errors, step sizes, first derivs.
    //*-*                  4    values, parabolic errors, MINOS errors
    //*-*    when INKODE=5, MNPRIN chooses IKODE=1,2, or 3, according to ISW(2)
    //*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

    delete ptMinuit;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void FitMinuit_Convolution_Combined_1set_Log(Convolution_Tool sbtool, std::string fitName, std::string pdf_label, std::vector<double> &wgt_vector, std::vector<double> &wgt_error)
{
    //cout<<"======================================================================"<<endl;
    //cout<<"Universe = "<<sbtool.current_unv<<endl;
    //cout<<"======================================================================"<<endl;

    TMinuit *ptMinuit = new TMinuit(4);  //initialize TMinuit with a maximum of 4 params
    //
    //  select verbose level:
    //    default :     (58 lines in this test)
    //    -1 : minimum  ( 4 lines in this test)
    //     0 : low      (31 lines)
    //     1 : medium   (61 lines)
    //     2 : high     (89 lines)
    //     3 : maximum (199 lines in this test)
    //
    ptMinuit->SetPrintLevel(-1);
    // set the user function that calculates chi_square (the value to minimize)
    ptMinuit->SetFCN(calc_ChiSq_ConvolutionTool_Combined_1set_Log);

    Double_t arglist[10];
    Int_t ierflg = 0;

    arglist[0] = 1;
    ptMinuit->mnexcm("SET ERR", arglist ,1,ierflg);

    // Set starting values and step sizes for parameters
    //      Start from 1.0 and step 0.01
    ptMinuit->mnparm(0, "FitParm_Aluminium_upstreamCap",          .05, 0.01, .01, 10.0 , ierflg);
    ptMinuit->mnparm(1, "FitParm_Aluminium_Barrel",               .05, 0.01, .01, 10.0 , ierflg);
    ptMinuit->mnparm(2, "FitParm_Aluminium_downstreamCap",        .05, 0.01, .01, 10.0 , ierflg);
    ptMinuit->mnparm(3, "FitParm_Aluminium_downstreamConcaveCap", .05, 0.01, .01, 10.0 , ierflg);

    // Now ready for minimization step
    arglist[0] = 20000;
    arglist[1] = 1.;
    ptMinuit->mnexcm("MIGRAD", arglist ,2,ierflg);

    // Print results
    //std::cout<<"\nPrint results from minuit\n";
    double fParamVal[4];
    double fParamErr[4];
    ptMinuit->GetParameter(0, fParamVal[0], fParamErr[0]);
    ptMinuit->GetParameter(1, fParamVal[1], fParamErr[1]);
    ptMinuit->GetParameter(2, fParamVal[2], fParamErr[2]);
    ptMinuit->GetParameter(3, fParamVal[3], fParamErr[3]);


    //std::cout << "MnvH1D_Aluminium Upstream = " << fParamVal[0] << "\n";
    //std::cout << "MnvH1D_Aluminium Barrel = " << fParamVal[1] << "\n";
    //std::cout << "MnvH1D_Aluminium Downstreamstream = " << fParamVal[2] << "\n";
    //std::cout << "MnvH1D_Aluminium Downstream concave  = " << fParamVal[3] << "\n";
    // if you want to access to these parameters, use:
    Double_t min_ChiSq,edm,errdef;
    Int_t nvpar,nparx,icstat;
    ptMinuit->mnstat(min_ChiSq,edm,errdef,nvpar,nparx,icstat);
    //void mnstat(Double_t &fmin, Double_t &fedm, Double_t &errdef, Int_t &npari, Int_t &nparx, Int_t &istat)
    //*-*-*-*-*Returns concerning the current status of the minimization*-*-*-*-*
    //*-*      =========================================================
    //*-*       User-called
    //*-*          Namely, it returns:
    //*-*        FMIN: the best function value found so far
    //*-*        FEDM: the estimated vertical distance remaining to minimum
    //*-*        ERRDEF: the value of UP defining parameter uncertainties
    //*-*        NPARI: the number of currently variable parameters
    //*-*        NPARX: the highest (external) parameter number defined by user
    //*-*        ISTAT: a status integer indicating how good is the covariance
    //*-*           matrix:  0= not calculated at all
    //*-*                    1= approximation only, not accurate
    //*-*                    2= full matrix, but forced positive-definite
    //*-*                    3= full accurate covariance matrix
    //*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

    //sbtool.SaveFitResults(min_ChiSq, fParamVal, fParamErr);

    // Plot only for Central Value

      //std::cout<<"running: setting fit values"<<std::endl;
      wgt_vector.push_back(fParamVal[0]);
      wgt_vector.push_back(fParamVal[1]);
      wgt_vector.push_back(fParamVal[2]);
      wgt_vector.push_back(fParamVal[3]);

      wgt_error.push_back(fParamErr[0]);
      wgt_error.push_back(fParamErr[1]);
      wgt_error.push_back(fParamErr[2]);
      wgt_error.push_back(fParamErr[3]);
        //sbtool.ApplyFitResults();
        //sbtool.Plot( fitName, pdf_label);
        //wgt = fParamVal[0];
        //wgt_error = fParamErr[0];



    //std::cout << "\n";
    //std::cout << " Minimum chi square = " << min_ChiSq<< "\n";
    //std::cout << " Estimated vert. distance to min. = " << edm << "\n";
    //std::cout << " Number of variable parameters = " << nvpar << "\n";
    //std::cout << " Highest number of parameters defined by user = " << nparx << "\n";
    //std::cout << " Status of covariance matrix = " << icstat << "\n";

    //std::cout << "\n";
    //ptMinuit->mnprin(1,min_ChiSq);
    //*-*-*-*Prints the values of the parameters at the time of the call*-*-*-*-*
    //*-*    ===========================================================
    //*-*        also prints other relevant information such as function value,
    //*-*        estimated distance to minimum, parameter errors, step sizes.
    //*-*
    //*-*         According to the value of IKODE, the printout is:
    //*-*    IKODE=INKODE= 0    only info about function value
    //*-*                  1    parameter values, errors, limits
    //*-*                  2    values, errors, step sizes, internal values
    //*-*                  3    values, errors, step sizes, first derivs.
    //*-*                  4    values, parabolic errors, MINOS errors
    //*-*    when INKODE=5, MNPRIN chooses IKODE=1,2, or 3, according to ISW(2)
    //*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

    delete ptMinuit;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void FitMinuit_Convolution_Combined_difference(Convolution_Tool sbtool, std::string fitName, std::string pdf_label, std::vector<double> &wgt_vector, std::vector<double> &wgt_error)
{
    //cout<<"======================================================================"<<endl;
    //cout<<"Universe = "<<sbtool.current_unv<<endl;
    //cout<<"======================================================================"<<endl;

    TMinuit *ptMinuit = new TMinuit(4);  //initialize TMinuit with a maximum of 4 params
    //
    //  select verbose level:
    //    default :     (58 lines in this test)
    //    -1 : minimum  ( 4 lines in this test)
    //     0 : low      (31 lines)
    //     1 : medium   (61 lines)
    //     2 : high     (89 lines)
    //     3 : maximum (199 lines in this test)
    //
    ptMinuit->SetPrintLevel(-1);
    // set the user function that calculates chi_square (the value to minimize)
    ptMinuit->SetFCN(calc_ChiSq_ConvolutionTool_Combined_Differece);

    Double_t arglist[10];
    Int_t ierflg = 0;

    arglist[0] = 1;
    ptMinuit->mnexcm("SET ERR", arglist ,1,ierflg);

    // Set starting values and step sizes for parameters
    //      Start from 1.0 and step 0.01
    ptMinuit->mnparm(0, "FitParm_Aluminium_upstreamCap",          .05, 0.01, .01, 10.0 , ierflg);
    ptMinuit->mnparm(1, "FitParm_Aluminium_Barrel",               .05, 0.01, .01, 10.0 , ierflg);
    ptMinuit->mnparm(2, "FitParm_Aluminium_downstreamCap",        .05, 0.01, .01, 10.0 , ierflg);
    ptMinuit->mnparm(3, "FitParm_Aluminium_downstreamConcaveCap", .05, 0.01, .01, 10.0 , ierflg);

    // Now ready for minimization step
    arglist[0] = 20000;
    arglist[1] = 1.;
    ptMinuit->mnexcm("MIGRAD", arglist ,2,ierflg);

    // Print results
    //std::cout<<"\nPrint results from minuit\n";
    double fParamVal[4];
    double fParamErr[4];
    ptMinuit->GetParameter(0, fParamVal[0], fParamErr[0]);
    ptMinuit->GetParameter(1, fParamVal[1], fParamErr[1]);
    ptMinuit->GetParameter(2, fParamVal[2], fParamErr[2]);
    ptMinuit->GetParameter(3, fParamVal[3], fParamErr[3]);


    //std::cout << "MnvH1D_Aluminium Upstream = " << fParamVal[0] << "\n";
    //std::cout << "MnvH1D_Aluminium Barrel = " << fParamVal[1] << "\n";
    //std::cout << "MnvH1D_Aluminium Downstreamstream = " << fParamVal[2] << "\n";
    //std::cout << "MnvH1D_Aluminium Downstream concave  = " << fParamVal[3] << "\n";
    // if you want to access to these parameters, use:
    Double_t min_ChiSq,edm,errdef;
    Int_t nvpar,nparx,icstat;
    ptMinuit->mnstat(min_ChiSq,edm,errdef,nvpar,nparx,icstat);
    //void mnstat(Double_t &fmin, Double_t &fedm, Double_t &errdef, Int_t &npari, Int_t &nparx, Int_t &istat)
    //*-*-*-*-*Returns concerning the current status of the minimization*-*-*-*-*
    //*-*      =========================================================
    //*-*       User-called
    //*-*          Namely, it returns:
    //*-*        FMIN: the best function value found so far
    //*-*        FEDM: the estimated vertical distance remaining to minimum
    //*-*        ERRDEF: the value of UP defining parameter uncertainties
    //*-*        NPARI: the number of currently variable parameters
    //*-*        NPARX: the highest (external) parameter number defined by user
    //*-*        ISTAT: a status integer indicating how good is the covariance
    //*-*           matrix:  0= not calculated at all
    //*-*                    1= approximation only, not accurate
    //*-*                    2= full matrix, but forced positive-definite
    //*-*                    3= full accurate covariance matrix
    //*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

    //sbtool.SaveFitResults(min_ChiSq, fParamVal, fParamErr);

    // Plot only for Central Value

      //std::cout<<"running: setting fit values"<<std::endl;
      wgt_vector.push_back(fParamVal[0]);
      wgt_vector.push_back(fParamVal[1]);
      wgt_vector.push_back(fParamVal[2]);
      wgt_vector.push_back(fParamVal[3]);

      wgt_error.push_back(fParamErr[0]);
      wgt_error.push_back(fParamErr[1]);
      wgt_error.push_back(fParamErr[2]);
      wgt_error.push_back(fParamErr[3]);
        //sbtool.ApplyFitResults();
        //sbtool.Plot( fitName, pdf_label);
        //wgt = fParamVal[0];
        //wgt_error = fParamErr[0];



    //std::cout << "\n";
    //std::cout << " Minimum chi square = " << min_ChiSq<< "\n";
    //std::cout << " Estimated vert. distance to min. = " << edm << "\n";
    //std::cout << " Number of variable parameters = " << nvpar << "\n";
    //std::cout << " Highest number of parameters defined by user = " << nparx << "\n";
    //std::cout << " Status of covariance matrix = " << icstat << "\n";

    //std::cout << "\n";
    //ptMinuit->mnprin(1,min_ChiSq);
    //*-*-*-*Prints the values of the parameters at the time of the call*-*-*-*-*
    //*-*    ===========================================================
    //*-*        also prints other relevant information such as function value,
    //*-*        estimated distance to minimum, parameter errors, step sizes.
    //*-*
    //*-*         According to the value of IKODE, the printout is:
    //*-*    IKODE=INKODE= 0    only info about function value
    //*-*                  1    parameter values, errors, limits
    //*-*                  2    values, errors, step sizes, internal values
    //*-*                  3    values, errors, step sizes, first derivs.
    //*-*                  4    values, parabolic errors, MINOS errors
    //*-*    when INKODE=5, MNPRIN chooses IKODE=1,2, or 3, according to ISW(2)
    //*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

    delete ptMinuit;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void FitMinuit_Convolution_Combined_difference_Log(Convolution_Tool sbtool, std::string fitName, std::string pdf_label, std::vector<double> &wgt_vector, std::vector<double> &wgt_error)
{
    //cout<<"======================================================================"<<endl;
    //cout<<"Universe = "<<sbtool.current_unv<<endl;
    //cout<<"======================================================================"<<endl;

    TMinuit *ptMinuit = new TMinuit(4);  //initialize TMinuit with a maximum of 4 params
    //
    //  select verbose level:
    //    default :     (58 lines in this test)
    //    -1 : minimum  ( 4 lines in this test)
    //     0 : low      (31 lines)
    //     1 : medium   (61 lines)
    //     2 : high     (89 lines)
    //     3 : maximum (199 lines in this test)
    //
    ptMinuit->SetPrintLevel(-1);
    // set the user function that calculates chi_square (the value to minimize)
    ptMinuit->SetFCN(calc_ChiSq_ConvolutionTool_Combined_Differece_Log);

    Double_t arglist[10];
    Int_t ierflg = 0;

    arglist[0] = 1;
    ptMinuit->mnexcm("SET ERR", arglist ,1,ierflg);

    // Set starting values and step sizes for parameters
    //      Start from 1.0 and step 0.01
    ptMinuit->mnparm(0, "FitParm_Aluminium_upstreamCap",          .05, 0.01, .01, 10.0 , ierflg);
    ptMinuit->mnparm(1, "FitParm_Aluminium_Barrel",               .05, 0.01, .01, 10.0 , ierflg);
    ptMinuit->mnparm(2, "FitParm_Aluminium_downstreamCap",        .05, 0.01, .01, 10.0 , ierflg);
    ptMinuit->mnparm(3, "FitParm_Aluminium_downstreamConcaveCap", .05, 0.01, .01, 10.0 , ierflg);

    // Now ready for minimization step
    arglist[0] = 20000;
    arglist[1] = 1.;
    ptMinuit->mnexcm("MIGRAD", arglist ,2,ierflg);

    // Print results
    //std::cout<<"\nPrint results from minuit\n";
    double fParamVal[4];
    double fParamErr[4];
    ptMinuit->GetParameter(0, fParamVal[0], fParamErr[0]);
    ptMinuit->GetParameter(1, fParamVal[1], fParamErr[1]);
    ptMinuit->GetParameter(2, fParamVal[2], fParamErr[2]);
    ptMinuit->GetParameter(3, fParamVal[3], fParamErr[3]);


    //std::cout << "MnvH1D_Aluminium Upstream = " << fParamVal[0] << "\n";
    //std::cout << "MnvH1D_Aluminium Barrel = " << fParamVal[1] << "\n";
    //std::cout << "MnvH1D_Aluminium Downstreamstream = " << fParamVal[2] << "\n";
    //std::cout << "MnvH1D_Aluminium Downstream concave  = " << fParamVal[3] << "\n";
    // if you want to access to these parameters, use:
    Double_t min_ChiSq,edm,errdef;
    Int_t nvpar,nparx,icstat;
    ptMinuit->mnstat(min_ChiSq,edm,errdef,nvpar,nparx,icstat);
    //void mnstat(Double_t &fmin, Double_t &fedm, Double_t &errdef, Int_t &npari, Int_t &nparx, Int_t &istat)
    //*-*-*-*-*Returns concerning the current status of the minimization*-*-*-*-*
    //*-*      =========================================================
    //*-*       User-called
    //*-*          Namely, it returns:
    //*-*        FMIN: the best function value found so far
    //*-*        FEDM: the estimated vertical distance remaining to minimum
    //*-*        ERRDEF: the value of UP defining parameter uncertainties
    //*-*        NPARI: the number of currently variable parameters
    //*-*        NPARX: the highest (external) parameter number defined by user
    //*-*        ISTAT: a status integer indicating how good is the covariance
    //*-*           matrix:  0= not calculated at all
    //*-*                    1= approximation only, not accurate
    //*-*                    2= full matrix, but forced positive-definite
    //*-*                    3= full accurate covariance matrix
    //*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

    //sbtool.SaveFitResults(min_ChiSq, fParamVal, fParamErr);

    // Plot only for Central Value

      //std::cout<<"running: setting fit values"<<std::endl;
      wgt_vector.push_back(fParamVal[0]);
      wgt_vector.push_back(fParamVal[1]);
      wgt_vector.push_back(fParamVal[2]);
      wgt_vector.push_back(fParamVal[3]);

      wgt_error.push_back(fParamErr[0]);
      wgt_error.push_back(fParamErr[1]);
      wgt_error.push_back(fParamErr[2]);
      wgt_error.push_back(fParamErr[3]);
        //sbtool.ApplyFitResults();
        //sbtool.Plot( fitName, pdf_label);
        //wgt = fParamVal[0];
        //wgt_error = fParamErr[0];



    //std::cout << "\n";
    //std::cout << " Minimum chi square = " << min_ChiSq<< "\n";
    //std::cout << " Estimated vert. distance to min. = " << edm << "\n";
    //std::cout << " Number of variable parameters = " << nvpar << "\n";
    //std::cout << " Highest number of parameters defined by user = " << nparx << "\n";
    //std::cout << " Status of covariance matrix = " << icstat << "\n";

    //std::cout << "\n";
    //ptMinuit->mnprin(1,min_ChiSq);
    //*-*-*-*Prints the values of the parameters at the time of the call*-*-*-*-*
    //*-*    ===========================================================
    //*-*        also prints other relevant information such as function value,
    //*-*        estimated distance to minimum, parameter errors, step sizes.
    //*-*
    //*-*         According to the value of IKODE, the printout is:
    //*-*    IKODE=INKODE= 0    only info about function value
    //*-*                  1    parameter values, errors, limits
    //*-*                  2    values, errors, step sizes, internal values
    //*-*                  3    values, errors, step sizes, first derivs.
    //*-*                  4    values, parabolic errors, MINOS errors
    //*-*    when INKODE=5, MNPRIN chooses IKODE=1,2, or 3, according to ISW(2)
    //*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

    delete ptMinuit;
}
/////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

void FitConvolutionTool(Convolution_Tool sbtool, int FitFullorEmpty,
  std::string fitName, std::string file_name, std::string pdf_label,
  std::vector<double> &wgt_vector, std::vector<double> &wgt_error_vector ,
  double &chisqrt, double &chisqrt_error)
{
    //cout<<"======================================================================"<<endl;
    //cout<<"Fitting Side Bands..."<<endl;
    //cout<<"======================================================================"<<endl;
    //std::cout<< "Name of sideBand = "<< sbtool.GetName()<<std::endl;
    //std::cout << "sbtool.current_unv = " << sbtool.current_unv<<std::endl;
    //std::cout << "sbtool.N_Universes = " << sbtool.N_Universes<<std::endl;
      //std::cout<<"Current Unv"<<sbtool.current_unv<<std::endl;
      if(FitFullorEmpty==0){

      //  cout<<"======================================================================"<<endl;
      //  cout<<"Fitting TO EMPTY"<<endl;
      //  cout<<"======================================================================"<<endl;

        FitMinuit_Convolution_Empty(sbtool, fitName, pdf_label, wgt_vector, wgt_error_vector, chisqrt, chisqrt_error );



      }


      else if (FitFullorEmpty==1){
        FitMinuit_Convolution_EmptyLogchi2(sbtool, fitName, pdf_label, wgt_vector, wgt_error_vector, chisqrt, chisqrt_error );

      }

      else if(FitFullorEmpty==2){
        FitMinuit_Convolution_Empty_RZ(sbtool, fitName, pdf_label, wgt_vector, wgt_error_vector );
      }

      else if(FitFullorEmpty==3){

        FitMinuit_Convolution_Full(sbtool, fitName, pdf_label, wgt_vector, wgt_error_vector );

      }
      else if(FitFullorEmpty==4){

        FitMinuit_Convolution_FullLogchi2(sbtool, fitName, pdf_label, wgt_vector, wgt_error_vector );

      }

      else if(FitFullorEmpty==5){

        FitMinuit_Convolution_CombinedLogchi2(sbtool, fitName, pdf_label, wgt_vector, wgt_error_vector, chisqrt, chisqrt_error );

      }

      else if(FitFullorEmpty==6){

        FitMinuit_Convolution_Combined_chi2(sbtool, fitName, pdf_label, wgt_vector, wgt_error_vector, chisqrt, chisqrt_error );

      }


    //sbtool.WriteStatistics();
    //sbtool.WriteFitResults(file_name);

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void FitConvolutionTool(Convolution_Tool sbtool, int FitFullorEmpty,
  std::string fitName, std::string file_name, std::string pdf_label,
  std::vector<double> &wgt_vector, std::vector<double> &wgt_error_vector )
{

  double chisqrt, chisqrt_error;
    //cout<<"======================================================================"<<endl;
    //cout<<"Fitting Side Bands..."<<endl;
    //cout<<"======================================================================"<<endl;
    //std::cout<< "Name of sideBand = "<< sbtool.GetName()<<std::endl;
    //std::cout << "sbtool.current_unv = " << sbtool.current_unv<<std::endl;
    //std::cout << "sbtool.N_Universes = " << sbtool.N_Universes<<std::endl;
      //std::cout<<"Current Unv"<<sbtool.current_unv<<std::endl;
      if(FitFullorEmpty==0){

      //  cout<<"======================================================================"<<endl;
      //  cout<<"Fitting TO EMPTY"<<endl;
      //  cout<<"======================================================================"<<endl;

        FitMinuit_Convolution_Empty(sbtool, fitName, pdf_label, wgt_vector, wgt_error_vector, chisqrt, chisqrt_error );



      }


      else if (FitFullorEmpty==1){

        FitMinuit_Convolution_EmptyLogchi2(sbtool, fitName, pdf_label, wgt_vector, wgt_error_vector, chisqrt, chisqrt_error );

      }

      else if(FitFullorEmpty==2){
        FitMinuit_Convolution_Empty_RZ(sbtool, fitName, pdf_label, wgt_vector, wgt_error_vector );
      }

      else if(FitFullorEmpty==3){

        FitMinuit_Convolution_Full(sbtool, fitName, pdf_label, wgt_vector, wgt_error_vector );

      }
      else if(FitFullorEmpty==4){

        FitMinuit_Convolution_FullLogchi2(sbtool, fitName, pdf_label, wgt_vector, wgt_error_vector );

      }
      else if(FitFullorEmpty==4){

        FitMinuit_Convolution_Combined_1set(sbtool, fitName, pdf_label, wgt_vector, wgt_error_vector );

      }

      else if(FitFullorEmpty==5){

        FitMinuit_Convolution_Combined_1set_Log(sbtool, fitName, pdf_label, wgt_vector, wgt_error_vector );

      }
      else if(FitFullorEmpty==6){

        FitMinuit_Convolution_Combined_difference(sbtool, fitName, pdf_label, wgt_vector, wgt_error_vector );

      }

      else if(FitFullorEmpty==7){

        FitMinuit_Convolution_Combined_difference_Log(sbtool, fitName, pdf_label, wgt_vector, wgt_error_vector );

      }

    //sbtool.WriteStatistics();
    //sbtool.WriteFitResults(file_name);

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
