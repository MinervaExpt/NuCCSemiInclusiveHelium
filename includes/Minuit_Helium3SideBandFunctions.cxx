#include "Helium_3CryoRegionsSideBandTool.h"
using namespace std;


Helium_3CryoRegionsSideBandTool sbtool3region_global;

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
double calc_ChiSq_For_SideBand_CV(Helium3SideBand  &sb, double InPut,
   int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1)
{
  //std::cout<<"inside:calc_ChiSq_SideBand"<<std::endl;

    if (!isPartial){
        min_bin = 1;
        max_bin = sb.MnvH1D_Vertex_X_data->GetNbinsX();
    }

    if (min_bin == max_bin){
        cout<<"Wrong Range for Fit"<<endl;
        exit(EXIT_FAILURE);
    }

    double ChiSq = 0.0;


    for (int i = 1; i <= sb.MnvH1D_Vertex_X_data->GetNbinsX(); ++i){
        // Get N(Events) in Single Bin
        double err = sb.MnvH1D_Vertex_X_data->GetBinError(i);
        double nData = sb.MnvH1D_Vertex_X_data->GetBinContent(i);
        if (nData == 0) continue;
        double nHelium = sb.MnvH1D_Vertex_X_Helium[0]->GetBinContent(i);
        double nCarbon = sb.MnvH1D_Vertex_X_Carbon[0]->GetBinContent(i);
        double nLead = sb.MnvH1D_Vertex_X_Lead[0]->GetBinContent(i);
        double nIron = sb.MnvH1D_Vertex_X_Iron[0]->GetBinContent(i);
        double nOther = sb.MnvH1D_Vertex_X_Other[0]->GetBinContent(i);
        double nAluminium = InPut * sb.MnvH1D_Vertex_X_Aluminium[0]->GetBinContent(i);

        // Add All MC and scale them
        double nMC_total = (nHelium + nAluminium + nCarbon + nLead + nIron  + nOther);

        double delta = pow((nData-nMC_total),2) / pow(err,2);
        ChiSq += delta;
      }


      if (!isPartial){
          min_bin = 1;
          max_bin = sb.MnvH1D_Vertex_Y_data->GetNbinsX();
      }

      if (min_bin == max_bin){
          cout<<"Wrong Range for Fit"<<endl;
          exit(EXIT_FAILURE);
      }


      for (int i = 1; i <= sb.MnvH1D_Vertex_Y_data->GetNbinsX(); ++i){
          // Get N(Events) in Single Bin
          double err = sb.MnvH1D_Vertex_Y_data->GetBinError(i);
          double nData = sb.MnvH1D_Vertex_Y_data->GetBinContent(i);
          if (nData == 0) continue;
          double nHelium = sb.MnvH1D_Vertex_Y_Helium[0]->GetBinContent(i);
          double nCarbon = sb.MnvH1D_Vertex_Y_Carbon[0]->GetBinContent(i);
          double nLead = sb.MnvH1D_Vertex_Y_Lead[0]->GetBinContent(i);
          double nIron = sb.MnvH1D_Vertex_Y_Iron[0]->GetBinContent(i);
          double nOther = sb.MnvH1D_Vertex_Y_Other[0]->GetBinContent(i);
          double nAluminium = InPut * sb.MnvH1D_Vertex_Y_Aluminium[0]->GetBinContent(i);

          // Add All MC and scale them
          double nMC_total = (nHelium + nAluminium + nCarbon + nLead + nIron  + nOther);

          double delta = pow((nData-nMC_total),2) / pow(err,2);
          ChiSq += delta;
        }


        for (int i = 1; i <= sb.MnvH1D_Vertex_Z_data->GetNbinsX(); ++i){
            // Get N(Events) in Single Bin
            double err = sb.MnvH1D_Vertex_Z_data->GetBinError(i);
            double nData = sb.MnvH1D_Vertex_Z_data->GetBinContent(i);
            if (nData == 0) continue;
            double nHelium = sb.MnvH1D_Vertex_Z_Helium[0]->GetBinContent(i);
            double nCarbon = sb.MnvH1D_Vertex_Z_Carbon[0]->GetBinContent(i);
            double nLead = sb.MnvH1D_Vertex_Z_Lead[0]->GetBinContent(i);
            double nIron = sb.MnvH1D_Vertex_Z_Iron[0]->GetBinContent(i);
            double nOther = sb.MnvH1D_Vertex_Z_Other[0]->GetBinContent(i);
            double nAluminium = InPut * sb.MnvH1D_Vertex_Z_Aluminium[0]->GetBinContent(i);

            // Add All MC and scale them
            double nMC_total = (nHelium + nAluminium + nCarbon + nLead + nIron  + nOther);

            double delta = pow((nData-nMC_total),2) / pow(err,2);
            ChiSq += delta;
          }


          for (int i = 1; i <= sb.MnvH1D_Vertex_R_data->GetNbinsX(); ++i){
              // Get N(Events) in Single Bin
              double err = sb.MnvH1D_Vertex_R_data->GetBinError(i);
              double nData = sb.MnvH1D_Vertex_R_data->GetBinContent(i);
              if (nData == 0) continue;
              double nHelium = sb.MnvH1D_Vertex_R_Helium[0]->GetBinContent(i);
              double nCarbon = sb.MnvH1D_Vertex_R_Carbon[0]->GetBinContent(i);
              double nLead = sb.MnvH1D_Vertex_R_Lead[0]->GetBinContent(i);
              double nIron = sb.MnvH1D_Vertex_R_Iron[0]->GetBinContent(i);
              double nOther = sb.MnvH1D_Vertex_R_Other[0]->GetBinContent(i);
              double nAluminium = InPut * sb.MnvH1D_Vertex_R_Aluminium[0]->GetBinContent(i);

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
double calc_ChiSq_For_SideBand_CV(Helium3SideBand  &sb, double InPut_Alwgt, double InPut_Hewgt,
   int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1)
{
  //std::cout<<"inside:calc_ChiSq_SideBand"<<std::endl;

    if (!isPartial){
        min_bin = 1;
        max_bin = sb.MnvH1D_Vertex_X_data->GetNbinsX();
    }

    if (min_bin == max_bin){
        cout<<"Wrong Range for Fit"<<endl;
        exit(EXIT_FAILURE);
    }

    double ChiSq = 0.0;


    for (int i = 1; i <= sb.MnvH1D_Vertex_X_data->GetNbinsX(); ++i){
        // Get N(Events) in Single Bin
        double err = sb.MnvH1D_Vertex_X_data->GetBinError(i);
        double nData = sb.MnvH1D_Vertex_X_data->GetBinContent(i);
        if (nData == 0) continue;
        double nHelium = InPut_Hewgt * sb.MnvH1D_Vertex_X_Helium[0]->GetBinContent(i);
        double nCarbon = sb.MnvH1D_Vertex_X_Carbon[0]->GetBinContent(i);
        double nLead = sb.MnvH1D_Vertex_X_Lead[0]->GetBinContent(i);
        double nIron = sb.MnvH1D_Vertex_X_Iron[0]->GetBinContent(i);
        double nOther = sb.MnvH1D_Vertex_X_Other[0]->GetBinContent(i);
        double nAluminium = InPut_Alwgt * sb.MnvH1D_Vertex_X_Aluminium[0]->GetBinContent(i);

        // Add All MC and scale them
        double nMC_total = (nHelium + nAluminium + nCarbon + nLead + nIron  + nOther);

        double delta = pow((nData-nMC_total),2) / pow(err,2);
        ChiSq += delta;
      }


      if (!isPartial){
          min_bin = 1;
          max_bin = sb.MnvH1D_Vertex_Y_data->GetNbinsX();
      }

      if (min_bin == max_bin){
          cout<<"Wrong Range for Fit"<<endl;
          exit(EXIT_FAILURE);
      }


      for (int i = 1; i <= sb.MnvH1D_Vertex_Y_data->GetNbinsX(); ++i){
          // Get N(Events) in Single Bin
          double err = sb.MnvH1D_Vertex_Y_data->GetBinError(i);
          double nData = sb.MnvH1D_Vertex_Y_data->GetBinContent(i);
          if (nData == 0) continue;
          double nHelium = InPut_Hewgt * sb.MnvH1D_Vertex_Y_Helium[0]->GetBinContent(i);
          double nCarbon = sb.MnvH1D_Vertex_Y_Carbon[0]->GetBinContent(i);
          double nLead = sb.MnvH1D_Vertex_Y_Lead[0]->GetBinContent(i);
          double nIron = sb.MnvH1D_Vertex_Y_Iron[0]->GetBinContent(i);
          double nOther = sb.MnvH1D_Vertex_Y_Other[0]->GetBinContent(i);
          double nAluminium = InPut_Alwgt * sb.MnvH1D_Vertex_Y_Aluminium[0]->GetBinContent(i);

          // Add All MC and scale them
          double nMC_total = (nHelium + nAluminium + nCarbon + nLead + nIron  + nOther);

          double delta = pow((nData-nMC_total),2) / pow(err,2);
          ChiSq += delta;
        }


        for (int i = 1; i <= sb.MnvH1D_Vertex_Z_data->GetNbinsX(); ++i){
            // Get N(Events) in Single Bin
            double err = sb.MnvH1D_Vertex_Z_data->GetBinError(i);
            double nData = sb.MnvH1D_Vertex_Z_data->GetBinContent(i);
            if (nData == 0) continue;
            double nHelium = InPut_Hewgt * sb.MnvH1D_Vertex_Z_Helium[0]->GetBinContent(i);
            double nCarbon = sb.MnvH1D_Vertex_Z_Carbon[0]->GetBinContent(i);
            double nLead = sb.MnvH1D_Vertex_Z_Lead[0]->GetBinContent(i);
            double nIron = sb.MnvH1D_Vertex_Z_Iron[0]->GetBinContent(i);
            double nOther = sb.MnvH1D_Vertex_Z_Other[0]->GetBinContent(i);
            double nAluminium = InPut_Alwgt * sb.MnvH1D_Vertex_Z_Aluminium[0]->GetBinContent(i);

            // Add All MC and scale them
            double nMC_total = (nHelium + nAluminium + nCarbon + nLead + nIron  + nOther);

            double delta = pow((nData-nMC_total),2) / pow(err,2);
            ChiSq += delta;
          }


          for (int i = 1; i <= sb.MnvH1D_Vertex_R_data->GetNbinsX(); ++i){
              // Get N(Events) in Single Bin
              double err = sb.MnvH1D_Vertex_R_data->GetBinError(i);
              double nData = sb.MnvH1D_Vertex_R_data->GetBinContent(i);
              if (nData == 0) continue;
              double nHelium = InPut_Hewgt * sb.MnvH1D_Vertex_R_Helium[0]->GetBinContent(i);
              double nCarbon = sb.MnvH1D_Vertex_R_Carbon[0]->GetBinContent(i);
              double nLead = sb.MnvH1D_Vertex_R_Lead[0]->GetBinContent(i);
              double nIron = sb.MnvH1D_Vertex_R_Iron[0]->GetBinContent(i);
              double nOther = sb.MnvH1D_Vertex_R_Other[0]->GetBinContent(i);
              double nAluminium = InPut_Alwgt * sb.MnvH1D_Vertex_R_Aluminium[0]->GetBinContent(i);

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
double calc_ChiSq_For_SideBand_CV_Vertex_X(
  Helium3SideBand  &sb_region1,
  Helium3SideBand  &sb_region2,
  Helium3SideBand  &sb_region3,
  Helium3SideBand  &sb_region4,
  double InPut_Alwgt_region1,
  double InPut_Alwgt_region2,
  double InPut_Alwgt_region3,
  double InPut_Alwgt_region4,
   int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1, bool removeFirstandLastBin= true)
{
  //std::cout<<"inside:calc_ChiSq_For_SideBand_CV_Vertex_X"<<std::endl;

    if (!isPartial){
        min_bin = 1;
        max_bin = sb_region1.MnvH1D_Vertex_X_data->GetNbinsX();
        if(removeFirstandLastBin==true){min_bin = min_bin + 1; max_bin = max_bin - 1;}
    }
    //std::cout<<"sb_region1.MnvH1D_Vertex_X_data"<<std::endl;


    if (min_bin == max_bin){
        cout<<"Wrong Range for Fit"<<endl;
        exit(EXIT_FAILURE);
    }

    double ChiSq = 0.0;


    for (int i = min_bin; i <= max_bin; ++i){
        // Get N(Events) in Single Bin
        double err_region1 = sb_region1.MnvH1D_Vertex_X_data->GetBinError(i);
        double nData_region1 = sb_region1.MnvH1D_Vertex_X_data->GetBinContent(i);
        double err_region2 = sb_region2.MnvH1D_Vertex_X_data->GetBinError(i);
        double nData_region2 = sb_region2.MnvH1D_Vertex_X_data->GetBinContent(i);
        double err_region3 = sb_region3.MnvH1D_Vertex_X_data->GetBinError(i);
        double nData_region3 = sb_region3.MnvH1D_Vertex_X_data->GetBinContent(i);
        double err_region4 = sb_region4.MnvH1D_Vertex_X_data->GetBinError(i);
        double nData_region4 = sb_region4.MnvH1D_Vertex_X_data->GetBinContent(i);
        double nData = nData_region1 + nData_region2 + nData_region3 + nData_region4;
        double err = err_region1 + err_region2 + err_region3 + err_region4;
        if (nData == 0 ) continue;
        double nHelium_region1 = sb_region1.MnvH1D_Vertex_X_Helium[0]->GetBinContent(i);
        double nCarbon_region1 = sb_region1.MnvH1D_Vertex_X_Carbon[0]->GetBinContent(i);
        double nLead_region1 = sb_region1.MnvH1D_Vertex_X_Lead[0]->GetBinContent(i);
        double nIron_region1 = sb_region1.MnvH1D_Vertex_X_Iron[0]->GetBinContent(i);
        double nOther_region1 = sb_region1.MnvH1D_Vertex_X_Other[0]->GetBinContent(i);
        double nAluminium_region1 = InPut_Alwgt_region1 * sb_region1.MnvH1D_Vertex_X_Aluminium[0]->GetBinContent(i);
        ////
        double nHelium_region2 = sb_region2.MnvH1D_Vertex_X_Helium[0]->GetBinContent(i);
        double nCarbon_region2 = sb_region2.MnvH1D_Vertex_X_Carbon[0]->GetBinContent(i);
        double nLead_region2 = sb_region2.MnvH1D_Vertex_X_Lead[0]->GetBinContent(i);
        double nIron_region2 = sb_region2.MnvH1D_Vertex_X_Iron[0]->GetBinContent(i);
        double nOther_region2 = sb_region2.MnvH1D_Vertex_X_Other[0]->GetBinContent(i);
        double nAluminium_region2 = InPut_Alwgt_region2 * sb_region2.MnvH1D_Vertex_X_Aluminium[0]->GetBinContent(i);
        ///////
        double nHelium_region3 = sb_region3.MnvH1D_Vertex_X_Helium[0]->GetBinContent(i);
        double nCarbon_region3 = sb_region3.MnvH1D_Vertex_X_Carbon[0]->GetBinContent(i);
        double nLead_region3 = sb_region3.MnvH1D_Vertex_X_Lead[0]->GetBinContent(i);
        double nIron_region3 = sb_region3.MnvH1D_Vertex_X_Iron[0]->GetBinContent(i);
        double nOther_region3 = sb_region3.MnvH1D_Vertex_X_Other[0]->GetBinContent(i);
        double nAluminium_region3 = InPut_Alwgt_region3 * sb_region3.MnvH1D_Vertex_X_Aluminium[0]->GetBinContent(i);
        ////
        double nHelium_region4 = sb_region4.MnvH1D_Vertex_X_Helium[0]->GetBinContent(i);
        double nCarbon_region4 = sb_region4.MnvH1D_Vertex_X_Carbon[0]->GetBinContent(i);
        double nLead_region4 = sb_region4.MnvH1D_Vertex_X_Lead[0]->GetBinContent(i);
        double nIron_region4 = sb_region4.MnvH1D_Vertex_X_Iron[0]->GetBinContent(i);
        double nOther_region4 = sb_region4.MnvH1D_Vertex_X_Other[0]->GetBinContent(i);
        double nAluminium_region4 = InPut_Alwgt_region4 * sb_region4.MnvH1D_Vertex_X_Aluminium[0]->GetBinContent(i);
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
double calc_ChiSqLog_For_SideBand_CV_Vertex_X(
  Helium3SideBand  &sb_region1,
  Helium3SideBand  &sb_region2,
  Helium3SideBand  &sb_region3,
  Helium3SideBand  &sb_region4,
  double InPut_Alwgt_region1,
  double InPut_Alwgt_region2,
  double InPut_Alwgt_region3,
  double InPut_Alwgt_region4,
   int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1, bool removeFirstandLastBin= true)
{
  //std::cout<<"inside:calc_ChiSq_For_SideBand_CV_Vertex_X"<<std::endl;

    if (!isPartial){
        min_bin = 1;
        max_bin = sb_region1.MnvH1D_Vertex_X_data->GetNbinsX();
        if(removeFirstandLastBin==true){min_bin = min_bin + 1; max_bin = max_bin - 1;}
    }
    //std::cout<<"sb_region1.MnvH1D_Vertex_X_data"<<std::endl;


    if (min_bin == max_bin){
        cout<<"Wrong Range for Fit"<<endl;
        exit(EXIT_FAILURE);
    }

    double ChiSq = 0.0;


    for (int i = min_bin; i <= max_bin; ++i){
        // Get N(Events) in Single Bin
        double err_region1 = sb_region1.MnvH1D_Vertex_X_data->GetBinError(i);
        double nData_region1 = sb_region1.MnvH1D_Vertex_X_data->GetBinContent(i);
        double err_region2 = sb_region2.MnvH1D_Vertex_X_data->GetBinError(i);
        double nData_region2 = sb_region2.MnvH1D_Vertex_X_data->GetBinContent(i);
        double err_region3 = sb_region3.MnvH1D_Vertex_X_data->GetBinError(i);
        double nData_region3 = sb_region3.MnvH1D_Vertex_X_data->GetBinContent(i);
        double err_region4 = sb_region4.MnvH1D_Vertex_X_data->GetBinError(i);
        double nData_region4 = sb_region4.MnvH1D_Vertex_X_data->GetBinContent(i);
        double nData = nData_region1 + nData_region2 + nData_region3 + nData_region4;
        double err = err_region1 + err_region2 + err_region3 + err_region4;
        if (nData == 0 ) continue;
        double nHelium_region1 = sb_region1.MnvH1D_Vertex_X_Helium[0]->GetBinContent(i);
        double nCarbon_region1 = sb_region1.MnvH1D_Vertex_X_Carbon[0]->GetBinContent(i);
        double nLead_region1 = sb_region1.MnvH1D_Vertex_X_Lead[0]->GetBinContent(i);
        double nIron_region1 = sb_region1.MnvH1D_Vertex_X_Iron[0]->GetBinContent(i);
        double nOther_region1 = sb_region1.MnvH1D_Vertex_X_Other[0]->GetBinContent(i);
        double nAluminium_region1 = InPut_Alwgt_region1 * sb_region1.MnvH1D_Vertex_X_Aluminium[0]->GetBinContent(i);
        ////
        double nHelium_region2 = sb_region2.MnvH1D_Vertex_X_Helium[0]->GetBinContent(i);
        double nCarbon_region2 = sb_region2.MnvH1D_Vertex_X_Carbon[0]->GetBinContent(i);
        double nLead_region2 = sb_region2.MnvH1D_Vertex_X_Lead[0]->GetBinContent(i);
        double nIron_region2 = sb_region2.MnvH1D_Vertex_X_Iron[0]->GetBinContent(i);
        double nOther_region2 = sb_region2.MnvH1D_Vertex_X_Other[0]->GetBinContent(i);
        double nAluminium_region2 = InPut_Alwgt_region2 * sb_region2.MnvH1D_Vertex_X_Aluminium[0]->GetBinContent(i);
        ///////
        double nHelium_region3 = sb_region3.MnvH1D_Vertex_X_Helium[0]->GetBinContent(i);
        double nCarbon_region3 = sb_region3.MnvH1D_Vertex_X_Carbon[0]->GetBinContent(i);
        double nLead_region3 = sb_region3.MnvH1D_Vertex_X_Lead[0]->GetBinContent(i);
        double nIron_region3 = sb_region3.MnvH1D_Vertex_X_Iron[0]->GetBinContent(i);
        double nOther_region3 = sb_region3.MnvH1D_Vertex_X_Other[0]->GetBinContent(i);
        double nAluminium_region3 = InPut_Alwgt_region3 * sb_region3.MnvH1D_Vertex_X_Aluminium[0]->GetBinContent(i);
        ////
        double nHelium_region4 = sb_region4.MnvH1D_Vertex_X_Helium[0]->GetBinContent(i);
        double nCarbon_region4 = sb_region4.MnvH1D_Vertex_X_Carbon[0]->GetBinContent(i);
        double nLead_region4 = sb_region4.MnvH1D_Vertex_X_Lead[0]->GetBinContent(i);
        double nIron_region4 = sb_region4.MnvH1D_Vertex_X_Iron[0]->GetBinContent(i);
        double nOther_region4 = sb_region4.MnvH1D_Vertex_X_Other[0]->GetBinContent(i);
        double nAluminium_region4 = InPut_Alwgt_region4 * sb_region4.MnvH1D_Vertex_X_Aluminium[0]->GetBinContent(i);
        ////////
        double nHelium = nHelium_region1 + nHelium_region2 + nHelium_region3 + nHelium_region4;
        double nCarbon = nCarbon_region1 + nCarbon_region2 + nCarbon_region3 + nCarbon_region4;
        double nLead   = nLead_region1   + nLead_region2   + nLead_region3   + nLead_region4;
        double nIron   = nIron_region1   + nIron_region2   + nIron_region3   + nIron_region4;
        double nOther  = nOther_region1  + nOther_region2  + nOther_region3  + nOther_region4;
        double nAluminium = nAluminium_region1 + nAluminium_region2 + nAluminium_region3 + nAluminium_region4;
        ///
        // Add All MC and scale them
        double nMC_total = (nHelium + nAluminium + nCarbon + nLead + nIron  + nOther);

        //double delta = pow((nData-nMC_total),2) / pow(err,2);
        double c = nData * log(nMC_total);
        double delta = 2 * (nMC_total - c);
        ChiSq += delta;
      }




    return ChiSq;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
double calc_ChiSq_For_SideBand_CV_Vertex_Y(
  Helium3SideBand  &sb_region1,
  Helium3SideBand  &sb_region2,
  Helium3SideBand  &sb_region3,
  Helium3SideBand  &sb_region4,
  double InPut_Alwgt_region1,
  double InPut_Alwgt_region2,
  double InPut_Alwgt_region3,
  double InPut_Alwgt_region4,
   int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1, bool removeFirstandLastBin= true)
{


    if (!isPartial){
        min_bin = 1;
        max_bin = sb_region1.MnvH1D_Vertex_Y_data->GetNbinsX();

        if(removeFirstandLastBin==true){min_bin = min_bin + 1; max_bin = max_bin - 1;}

    }


    if (min_bin == max_bin){
        cout<<"Wrong Range for Fit"<<endl;
        exit(EXIT_FAILURE);
    }

    double ChiSq = 0.0;


    for (int i = min_bin; i <= max_bin; ++i){
        // Get N(Events) in Single Bin
        double err_region1 = sb_region1.MnvH1D_Vertex_Y_data->GetBinError(i);
        double nData_region1 = sb_region1.MnvH1D_Vertex_Y_data->GetBinContent(i);
        double err_region2 = sb_region2.MnvH1D_Vertex_Y_data->GetBinError(i);
        double nData_region2 = sb_region2.MnvH1D_Vertex_Y_data->GetBinContent(i);
        double err_region3 = sb_region3.MnvH1D_Vertex_Y_data->GetBinError(i);
        double nData_region3 = sb_region3.MnvH1D_Vertex_Y_data->GetBinContent(i);
        double err_region4 = sb_region4.MnvH1D_Vertex_Y_data->GetBinError(i);
        double nData_region4 = sb_region4.MnvH1D_Vertex_Y_data->GetBinContent(i);
        double nData = nData_region1 + nData_region2 + nData_region3 + nData_region4;
        double err = err_region1 + err_region2 + err_region3 + err_region4;
        if (nData == 0 ) continue;
        double nHelium_region1 = sb_region1.MnvH1D_Vertex_Y_Helium[0]->GetBinContent(i);
        double nCarbon_region1 = sb_region1.MnvH1D_Vertex_Y_Carbon[0]->GetBinContent(i);
        double nLead_region1 = sb_region1.MnvH1D_Vertex_Y_Lead[0]->GetBinContent(i);
        double nIron_region1 = sb_region1.MnvH1D_Vertex_Y_Iron[0]->GetBinContent(i);
        double nOther_region1 = sb_region1.MnvH1D_Vertex_Y_Other[0]->GetBinContent(i);
        double nAluminium_region1 = InPut_Alwgt_region1 * sb_region1.MnvH1D_Vertex_Y_Aluminium[0]->GetBinContent(i);
        ////
        double nHelium_region2 = sb_region2.MnvH1D_Vertex_Y_Helium[0]->GetBinContent(i);
        double nCarbon_region2 = sb_region2.MnvH1D_Vertex_Y_Carbon[0]->GetBinContent(i);
        double nLead_region2 = sb_region2.MnvH1D_Vertex_Y_Lead[0]->GetBinContent(i);
        double nIron_region2 = sb_region2.MnvH1D_Vertex_Y_Iron[0]->GetBinContent(i);
        double nOther_region2 = sb_region2.MnvH1D_Vertex_Y_Other[0]->GetBinContent(i);
        double nAluminium_region2 = InPut_Alwgt_region2 * sb_region2.MnvH1D_Vertex_Y_Aluminium[0]->GetBinContent(i);
        ///////
        double nHelium_region3 = sb_region3.MnvH1D_Vertex_Y_Helium[0]->GetBinContent(i);
        double nCarbon_region3 = sb_region3.MnvH1D_Vertex_Y_Carbon[0]->GetBinContent(i);
        double nLead_region3 = sb_region3.MnvH1D_Vertex_Y_Lead[0]->GetBinContent(i);
        double nIron_region3 = sb_region3.MnvH1D_Vertex_Y_Iron[0]->GetBinContent(i);
        double nOther_region3 = sb_region3.MnvH1D_Vertex_Y_Other[0]->GetBinContent(i);
        double nAluminium_region3 = InPut_Alwgt_region3 * sb_region3.MnvH1D_Vertex_Y_Aluminium[0]->GetBinContent(i);
        ////
        double nHelium_region4 = sb_region4.MnvH1D_Vertex_Y_Helium[0]->GetBinContent(i);
        double nCarbon_region4 = sb_region4.MnvH1D_Vertex_Y_Carbon[0]->GetBinContent(i);
        double nLead_region4 = sb_region4.MnvH1D_Vertex_Y_Lead[0]->GetBinContent(i);
        double nIron_region4 = sb_region4.MnvH1D_Vertex_Y_Iron[0]->GetBinContent(i);
        double nOther_region4 = sb_region4.MnvH1D_Vertex_Y_Other[0]->GetBinContent(i);
        double nAluminium_region4 = InPut_Alwgt_region4 * sb_region4.MnvH1D_Vertex_Y_Aluminium[0]->GetBinContent(i);
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
double calc_ChiSqLog_For_SideBand_CV_Vertex_Y(
  Helium3SideBand  &sb_region1,
  Helium3SideBand  &sb_region2,
  Helium3SideBand  &sb_region3,
  Helium3SideBand  &sb_region4,
  double InPut_Alwgt_region1,
  double InPut_Alwgt_region2,
  double InPut_Alwgt_region3,
  double InPut_Alwgt_region4,
   int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1, bool removeFirstandLastBin= true)
{
  if (!isPartial){
    min_bin = 1;
    max_bin = sb_region1.MnvH1D_Vertex_Y_data->GetNbinsX();

    if(removeFirstandLastBin==true){min_bin = min_bin + 1; max_bin = max_bin - 1;}

  }

  if (min_bin == max_bin){
    cout<<"Wrong Range for Fit"<<endl;
    exit(EXIT_FAILURE);
  }

  double ChiSq = 0.0;


  for (int i = min_bin; i <= max_bin; ++i){
    // Get N(Events) in Single Bin
    double err_region1 = sb_region1.MnvH1D_Vertex_Y_data->GetBinError(i);
    double nData_region1 = sb_region1.MnvH1D_Vertex_Y_data->GetBinContent(i);
    double err_region2 = sb_region2.MnvH1D_Vertex_Y_data->GetBinError(i);
    double nData_region2 = sb_region2.MnvH1D_Vertex_Y_data->GetBinContent(i);
    double err_region3 = sb_region3.MnvH1D_Vertex_Y_data->GetBinError(i);
    double nData_region3 = sb_region3.MnvH1D_Vertex_Y_data->GetBinContent(i);
    double err_region4 = sb_region4.MnvH1D_Vertex_Y_data->GetBinError(i);
    double nData_region4 = sb_region4.MnvH1D_Vertex_Y_data->GetBinContent(i);
    double nData = nData_region1 + nData_region2 + nData_region3 + nData_region4;
    double err = err_region1 + err_region2 + err_region3 + err_region4;
    if (nData == 0 ) continue;
    double nHelium_region1 = sb_region1.MnvH1D_Vertex_Y_Helium[0]->GetBinContent(i);
    double nCarbon_region1 = sb_region1.MnvH1D_Vertex_Y_Carbon[0]->GetBinContent(i);
    double nLead_region1 = sb_region1.MnvH1D_Vertex_Y_Lead[0]->GetBinContent(i);
    double nIron_region1 = sb_region1.MnvH1D_Vertex_Y_Iron[0]->GetBinContent(i);
    double nOther_region1 = sb_region1.MnvH1D_Vertex_Y_Other[0]->GetBinContent(i);
    double nAluminium_region1 = InPut_Alwgt_region1 * sb_region1.MnvH1D_Vertex_Y_Aluminium[0]->GetBinContent(i);
    ////
    double nHelium_region2 = sb_region2.MnvH1D_Vertex_Y_Helium[0]->GetBinContent(i);
    double nCarbon_region2 = sb_region2.MnvH1D_Vertex_Y_Carbon[0]->GetBinContent(i);
    double nLead_region2 = sb_region2.MnvH1D_Vertex_Y_Lead[0]->GetBinContent(i);
    double nIron_region2 = sb_region2.MnvH1D_Vertex_Y_Iron[0]->GetBinContent(i);
    double nOther_region2 = sb_region2.MnvH1D_Vertex_Y_Other[0]->GetBinContent(i);
    double nAluminium_region2 = InPut_Alwgt_region2 * sb_region2.MnvH1D_Vertex_Y_Aluminium[0]->GetBinContent(i);
    ///////
    double nHelium_region3 = sb_region3.MnvH1D_Vertex_Y_Helium[0]->GetBinContent(i);
    double nCarbon_region3 = sb_region3.MnvH1D_Vertex_Y_Carbon[0]->GetBinContent(i);
    double nLead_region3 = sb_region3.MnvH1D_Vertex_Y_Lead[0]->GetBinContent(i);
    double nIron_region3 = sb_region3.MnvH1D_Vertex_Y_Iron[0]->GetBinContent(i);
    double nOther_region3 = sb_region3.MnvH1D_Vertex_Y_Other[0]->GetBinContent(i);
    double nAluminium_region3 = InPut_Alwgt_region3 * sb_region3.MnvH1D_Vertex_Y_Aluminium[0]->GetBinContent(i);
    ////
    double nHelium_region4 = sb_region4.MnvH1D_Vertex_Y_Helium[0]->GetBinContent(i);
    double nCarbon_region4 = sb_region4.MnvH1D_Vertex_Y_Carbon[0]->GetBinContent(i);
    double nLead_region4 = sb_region4.MnvH1D_Vertex_Y_Lead[0]->GetBinContent(i);
    double nIron_region4 = sb_region4.MnvH1D_Vertex_Y_Iron[0]->GetBinContent(i);
    double nOther_region4 = sb_region4.MnvH1D_Vertex_Y_Other[0]->GetBinContent(i);
    double nAluminium_region4 = InPut_Alwgt_region4 * sb_region4.MnvH1D_Vertex_Y_Aluminium[0]->GetBinContent(i);
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

    //double delta = pow((nData-nMC_total),2) / pow(err,2);
    double c = nData * log(nMC_total);
    double delta = 2 * (nMC_total - c);

    ChiSq += delta;
  }

  return ChiSq;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
double calc_ChiSq_For_SideBand_CV_Vertex_Z(
  Helium3SideBand  &sb_region1,
  Helium3SideBand  &sb_region2,
  Helium3SideBand  &sb_region3,
  Helium3SideBand  &sb_region4,
  double InPut_Alwgt_region1,
  double InPut_Alwgt_region2,
  double InPut_Alwgt_region3,
  double InPut_Alwgt_region4,
   int unv = 0, bool isPartial = false, int min_bin = 6, int max_bin = 1)/*removed First bin*/
{
  //std::cout<<"inside:calc_ChiSq_SideBand"<<std::endl;

    if (!isPartial){
        min_bin = 2; /*removed First bin*/
        max_bin = sb_region1.MnvH1D_Vertex_Z_data->GetNbinsX();
    }


    if (min_bin == max_bin){
        cout<<"Wrong Range for Fit"<<endl;
        exit(EXIT_FAILURE);
    }

    double ChiSq = 0.0;


    for (int i = min_bin; i <= max_bin; ++i){
        // Get N(Events) in Single Bin
        double err_region1 = sb_region1.MnvH1D_Vertex_Z_data->GetBinError(i);
        double nData_region1 = sb_region1.MnvH1D_Vertex_Z_data->GetBinContent(i);
        double err_region2 = sb_region2.MnvH1D_Vertex_Z_data->GetBinError(i);
        double nData_region2 = sb_region2.MnvH1D_Vertex_Z_data->GetBinContent(i);
        double err_region3 = sb_region3.MnvH1D_Vertex_Z_data->GetBinError(i);
        double nData_region3 = sb_region3.MnvH1D_Vertex_Z_data->GetBinContent(i);
        double err_region4 = sb_region4.MnvH1D_Vertex_Z_data->GetBinError(i);
        double nData_region4 = sb_region4.MnvH1D_Vertex_Z_data->GetBinContent(i);
        double nData = nData_region1 + nData_region2 + nData_region3 + nData_region4;
        double err = err_region1 + err_region2 + err_region3 + err_region4;
        if (nData == 0 ) continue;
        double nHelium_region1 = sb_region1.MnvH1D_Vertex_Z_Helium[0]->GetBinContent(i);
        double nCarbon_region1 = sb_region1.MnvH1D_Vertex_Z_Carbon[0]->GetBinContent(i);
        double nLead_region1 = sb_region1.MnvH1D_Vertex_Z_Lead[0]->GetBinContent(i);
        double nIron_region1 = sb_region1.MnvH1D_Vertex_Z_Iron[0]->GetBinContent(i);
        double nOther_region1 = sb_region1.MnvH1D_Vertex_Z_Other[0]->GetBinContent(i);
        double nAluminium_region1 = InPut_Alwgt_region1 * sb_region1.MnvH1D_Vertex_Z_Aluminium[0]->GetBinContent(i);
        ////
        double nHelium_region2 = sb_region2.MnvH1D_Vertex_Z_Helium[0]->GetBinContent(i);
        double nCarbon_region2 = sb_region2.MnvH1D_Vertex_Z_Carbon[0]->GetBinContent(i);
        double nLead_region2 = sb_region2.MnvH1D_Vertex_Z_Lead[0]->GetBinContent(i);
        double nIron_region2 = sb_region2.MnvH1D_Vertex_Z_Iron[0]->GetBinContent(i);
        double nOther_region2 = sb_region2.MnvH1D_Vertex_Z_Other[0]->GetBinContent(i);
        double nAluminium_region2 = InPut_Alwgt_region2 * sb_region2.MnvH1D_Vertex_Z_Aluminium[0]->GetBinContent(i);
        ///////
        double nHelium_region3 = sb_region3.MnvH1D_Vertex_Z_Helium[0]->GetBinContent(i);
        double nCarbon_region3 = sb_region3.MnvH1D_Vertex_Z_Carbon[0]->GetBinContent(i);
        double nLead_region3 = sb_region3.MnvH1D_Vertex_Z_Lead[0]->GetBinContent(i);
        double nIron_region3 = sb_region3.MnvH1D_Vertex_Z_Iron[0]->GetBinContent(i);
        double nOther_region3 = sb_region3.MnvH1D_Vertex_Z_Other[0]->GetBinContent(i);
        double nAluminium_region3 = InPut_Alwgt_region3 * sb_region3.MnvH1D_Vertex_Z_Aluminium[0]->GetBinContent(i);
        ////
        double nHelium_region4 = sb_region4.MnvH1D_Vertex_Z_Helium[0]->GetBinContent(i);
        double nCarbon_region4 = sb_region4.MnvH1D_Vertex_Z_Carbon[0]->GetBinContent(i);
        double nLead_region4 = sb_region4.MnvH1D_Vertex_Z_Lead[0]->GetBinContent(i);
        double nIron_region4 = sb_region4.MnvH1D_Vertex_Z_Iron[0]->GetBinContent(i);
        double nOther_region4 = sb_region4.MnvH1D_Vertex_Z_Other[0]->GetBinContent(i);
        double nAluminium_region4 = InPut_Alwgt_region4 * sb_region4.MnvH1D_Vertex_Z_Aluminium[0]->GetBinContent(i);
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
double calc_ChiSqLog_For_SideBand_CV_Vertex_Z(
  Helium3SideBand  &sb_region1,
  Helium3SideBand  &sb_region2,
  Helium3SideBand  &sb_region3,
  Helium3SideBand  &sb_region4,
  double InPut_Alwgt_region1,
  double InPut_Alwgt_region2,
  double InPut_Alwgt_region3,
  double InPut_Alwgt_region4,
   int unv = 0, bool isPartial = false, int min_bin = 6, int max_bin = 1)/*removed First bin*/
{
  //std::cout<<"inside:calc_ChiSq_SideBand"<<std::endl;

    if (!isPartial){
        min_bin = 2; /*removed First bin*/
        max_bin = sb_region1.MnvH1D_Vertex_Z_data->GetNbinsX();
    }


    if (min_bin == max_bin){
        cout<<"Wrong Range for Fit"<<endl;
        exit(EXIT_FAILURE);
    }

    double ChiSq = 0.0;


    for (int i = min_bin; i <= max_bin; ++i){
        // Get N(Events) in Single Bin
        double err_region1 = sb_region1.MnvH1D_Vertex_Z_data->GetBinError(i);
        double nData_region1 = sb_region1.MnvH1D_Vertex_Z_data->GetBinContent(i);
        double err_region2 = sb_region2.MnvH1D_Vertex_Z_data->GetBinError(i);
        double nData_region2 = sb_region2.MnvH1D_Vertex_Z_data->GetBinContent(i);
        double err_region3 = sb_region3.MnvH1D_Vertex_Z_data->GetBinError(i);
        double nData_region3 = sb_region3.MnvH1D_Vertex_Z_data->GetBinContent(i);
        double err_region4 = sb_region4.MnvH1D_Vertex_Z_data->GetBinError(i);
        double nData_region4 = sb_region4.MnvH1D_Vertex_Z_data->GetBinContent(i);
        double nData = nData_region1 + nData_region2 + nData_region3 + nData_region4;
        double err = err_region1 + err_region2 + err_region3 + err_region4;
        if (nData == 0 ) continue;
        double nHelium_region1 = sb_region1.MnvH1D_Vertex_Z_Helium[0]->GetBinContent(i);
        double nCarbon_region1 = sb_region1.MnvH1D_Vertex_Z_Carbon[0]->GetBinContent(i);
        double nLead_region1 = sb_region1.MnvH1D_Vertex_Z_Lead[0]->GetBinContent(i);
        double nIron_region1 = sb_region1.MnvH1D_Vertex_Z_Iron[0]->GetBinContent(i);
        double nOther_region1 = sb_region1.MnvH1D_Vertex_Z_Other[0]->GetBinContent(i);
        double nAluminium_region1 = InPut_Alwgt_region1 * sb_region1.MnvH1D_Vertex_Z_Aluminium[0]->GetBinContent(i);
        ////
        double nHelium_region2 = sb_region2.MnvH1D_Vertex_Z_Helium[0]->GetBinContent(i);
        double nCarbon_region2 = sb_region2.MnvH1D_Vertex_Z_Carbon[0]->GetBinContent(i);
        double nLead_region2 = sb_region2.MnvH1D_Vertex_Z_Lead[0]->GetBinContent(i);
        double nIron_region2 = sb_region2.MnvH1D_Vertex_Z_Iron[0]->GetBinContent(i);
        double nOther_region2 = sb_region2.MnvH1D_Vertex_Z_Other[0]->GetBinContent(i);
        double nAluminium_region2 = InPut_Alwgt_region2 * sb_region2.MnvH1D_Vertex_Z_Aluminium[0]->GetBinContent(i);
        ///////
        double nHelium_region3 = sb_region3.MnvH1D_Vertex_Z_Helium[0]->GetBinContent(i);
        double nCarbon_region3 = sb_region3.MnvH1D_Vertex_Z_Carbon[0]->GetBinContent(i);
        double nLead_region3 = sb_region3.MnvH1D_Vertex_Z_Lead[0]->GetBinContent(i);
        double nIron_region3 = sb_region3.MnvH1D_Vertex_Z_Iron[0]->GetBinContent(i);
        double nOther_region3 = sb_region3.MnvH1D_Vertex_Z_Other[0]->GetBinContent(i);
        double nAluminium_region3 = InPut_Alwgt_region3 * sb_region3.MnvH1D_Vertex_Z_Aluminium[0]->GetBinContent(i);
        ////
        double nHelium_region4 = sb_region4.MnvH1D_Vertex_Z_Helium[0]->GetBinContent(i);
        double nCarbon_region4 = sb_region4.MnvH1D_Vertex_Z_Carbon[0]->GetBinContent(i);
        double nLead_region4 = sb_region4.MnvH1D_Vertex_Z_Lead[0]->GetBinContent(i);
        double nIron_region4 = sb_region4.MnvH1D_Vertex_Z_Iron[0]->GetBinContent(i);
        double nOther_region4 = sb_region4.MnvH1D_Vertex_Z_Other[0]->GetBinContent(i);
        double nAluminium_region4 = InPut_Alwgt_region4 * sb_region4.MnvH1D_Vertex_Z_Aluminium[0]->GetBinContent(i);
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
double calc_ChiSq_For_SideBand_CV_Vertex_R(
  Helium3SideBand  &sb_region1,
  Helium3SideBand  &sb_region2,
  Helium3SideBand  &sb_region3,
  Helium3SideBand  &sb_region4,
  double InPut_Alwgt_region1,
  double InPut_Alwgt_region2,
  double InPut_Alwgt_region3,
  double InPut_Alwgt_region4,
   int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1)
{
  //std::cout<<"inside:calc_ChiSq_SideBand"<<std::endl;

    if (!isPartial){
        min_bin = 1;
        max_bin = sb_region1.MnvH1D_Vertex_R_data->GetNbinsX();
    }


    if (min_bin == max_bin){
        cout<<"Wrong Range for Fit"<<endl;
        exit(EXIT_FAILURE);
    }

    double ChiSq = 0.0;


    for (int i = min_bin; i <= max_bin; ++i){
        // Get N(Events) in Single Bin
        double err_region1 = sb_region1.MnvH1D_Vertex_R_data->GetBinError(i);
        double nData_region1 = sb_region1.MnvH1D_Vertex_R_data->GetBinContent(i);

        double err_region2 = sb_region2.MnvH1D_Vertex_R_data->GetBinError(i);
        double nData_region2 = sb_region2.MnvH1D_Vertex_R_data->GetBinContent(i);

        double err_region3 = sb_region3.MnvH1D_Vertex_R_data->GetBinError(i);
        double nData_region3 = sb_region3.MnvH1D_Vertex_R_data->GetBinContent(i);

        double err_region4 = sb_region4.MnvH1D_Vertex_R_data->GetBinError(i);
        double nData_region4 = sb_region4.MnvH1D_Vertex_R_data->GetBinContent(i);

        double nData = nData_region1 + nData_region2 + nData_region3 + nData_region4;
        double err = err_region1 + err_region2 + err_region3 + err_region4;
        if (nData == 0 ) continue;
        double nHelium_region1 = sb_region1.MnvH1D_Vertex_R_Helium[0]->GetBinContent(i);
        double nCarbon_region1 = sb_region1.MnvH1D_Vertex_R_Carbon[0]->GetBinContent(i);
        double nLead_region1 = sb_region1.MnvH1D_Vertex_R_Lead[0]->GetBinContent(i);
        double nIron_region1 = sb_region1.MnvH1D_Vertex_R_Iron[0]->GetBinContent(i);
        double nOther_region1 = sb_region1.MnvH1D_Vertex_R_Other[0]->GetBinContent(i);
        double nAluminium_region1 = InPut_Alwgt_region1 * sb_region1.MnvH1D_Vertex_R_Aluminium[0]->GetBinContent(i);
        ////
        double nHelium_region2 = sb_region2.MnvH1D_Vertex_R_Helium[0]->GetBinContent(i);
        double nCarbon_region2 = sb_region2.MnvH1D_Vertex_R_Carbon[0]->GetBinContent(i);
        double nLead_region2 = sb_region2.MnvH1D_Vertex_R_Lead[0]->GetBinContent(i);
        double nIron_region2 = sb_region2.MnvH1D_Vertex_R_Iron[0]->GetBinContent(i);
        double nOther_region2 = sb_region2.MnvH1D_Vertex_R_Other[0]->GetBinContent(i);
        double nAluminium_region2 = InPut_Alwgt_region2 * sb_region2.MnvH1D_Vertex_R_Aluminium[0]->GetBinContent(i);
        ///////
        double nHelium_region3 = sb_region3.MnvH1D_Vertex_R_Helium[0]->GetBinContent(i);
        double nCarbon_region3 = sb_region3.MnvH1D_Vertex_R_Carbon[0]->GetBinContent(i);
        double nLead_region3 = sb_region3.MnvH1D_Vertex_R_Lead[0]->GetBinContent(i);
        double nIron_region3 = sb_region3.MnvH1D_Vertex_R_Iron[0]->GetBinContent(i);
        double nOther_region3 = sb_region3.MnvH1D_Vertex_R_Other[0]->GetBinContent(i);
        double nAluminium_region3 = InPut_Alwgt_region3 * sb_region3.MnvH1D_Vertex_R_Aluminium[0]->GetBinContent(i);
        ////
        double nHelium_region4 = sb_region4.MnvH1D_Vertex_R_Helium[0]->GetBinContent(i);
        double nCarbon_region4 = sb_region4.MnvH1D_Vertex_R_Carbon[0]->GetBinContent(i);
        double nLead_region4 = sb_region4.MnvH1D_Vertex_R_Lead[0]->GetBinContent(i);
        double nIron_region4 = sb_region4.MnvH1D_Vertex_R_Iron[0]->GetBinContent(i);
        double nOther_region4 = sb_region4.MnvH1D_Vertex_R_Other[0]->GetBinContent(i);
        double nAluminium_region4 = InPut_Alwgt_region4 * sb_region4.MnvH1D_Vertex_R_Aluminium[0]->GetBinContent(i);
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
double calc_ChiSqLog_For_SideBand_CV_Vertex_R(
  Helium3SideBand  &sb_region1,
  Helium3SideBand  &sb_region2,
  Helium3SideBand  &sb_region3,
  Helium3SideBand  &sb_region4,
  double InPut_Alwgt_region1,
  double InPut_Alwgt_region2,
  double InPut_Alwgt_region3,
  double InPut_Alwgt_region4,
   int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1)
{
  //std::cout<<"inside:calc_ChiSq_SideBand"<<std::endl;

  if (!isPartial){
    min_bin = 1;
    max_bin = sb_region1.MnvH1D_Vertex_R_data->GetNbinsX();
  }


  if (min_bin == max_bin){
    cout<<"Wrong Range for Fit"<<endl;
    exit(EXIT_FAILURE);
  }

  double ChiSq = 0.0;


  for (int i = min_bin; i <= max_bin; ++i){
    // Get N(Events) in Single Bin
    double err_region1 = sb_region1.MnvH1D_Vertex_R_data->GetBinError(i);
    double nData_region1 = sb_region1.MnvH1D_Vertex_R_data->GetBinContent(i);

    double err_region2 = sb_region2.MnvH1D_Vertex_R_data->GetBinError(i);
    double nData_region2 = sb_region2.MnvH1D_Vertex_R_data->GetBinContent(i);

    double err_region3 = sb_region3.MnvH1D_Vertex_R_data->GetBinError(i);
    double nData_region3 = sb_region3.MnvH1D_Vertex_R_data->GetBinContent(i);

    double err_region4 = sb_region4.MnvH1D_Vertex_R_data->GetBinError(i);
    double nData_region4 = sb_region4.MnvH1D_Vertex_R_data->GetBinContent(i);

    double nData = nData_region1 + nData_region2 + nData_region3 + nData_region4;
    double err = err_region1 + err_region2 + err_region3 + err_region4;
    if (nData == 0 ) continue;
    double nHelium_region1 = sb_region1.MnvH1D_Vertex_R_Helium[0]->GetBinContent(i);
    double nCarbon_region1 = sb_region1.MnvH1D_Vertex_R_Carbon[0]->GetBinContent(i);
    double nLead_region1 = sb_region1.MnvH1D_Vertex_R_Lead[0]->GetBinContent(i);
    double nIron_region1 = sb_region1.MnvH1D_Vertex_R_Iron[0]->GetBinContent(i);
    double nOther_region1 = sb_region1.MnvH1D_Vertex_R_Other[0]->GetBinContent(i);
    double nAluminium_region1 = InPut_Alwgt_region1 * sb_region1.MnvH1D_Vertex_R_Aluminium[0]->GetBinContent(i);
    ////
    double nHelium_region2 = sb_region2.MnvH1D_Vertex_R_Helium[0]->GetBinContent(i);
    double nCarbon_region2 = sb_region2.MnvH1D_Vertex_R_Carbon[0]->GetBinContent(i);
    double nLead_region2 = sb_region2.MnvH1D_Vertex_R_Lead[0]->GetBinContent(i);
    double nIron_region2 = sb_region2.MnvH1D_Vertex_R_Iron[0]->GetBinContent(i);
    double nOther_region2 = sb_region2.MnvH1D_Vertex_R_Other[0]->GetBinContent(i);
    double nAluminium_region2 = InPut_Alwgt_region2 * sb_region2.MnvH1D_Vertex_R_Aluminium[0]->GetBinContent(i);
    ///////
    double nHelium_region3 = sb_region3.MnvH1D_Vertex_R_Helium[0]->GetBinContent(i);
    double nCarbon_region3 = sb_region3.MnvH1D_Vertex_R_Carbon[0]->GetBinContent(i);
    double nLead_region3 = sb_region3.MnvH1D_Vertex_R_Lead[0]->GetBinContent(i);
    double nIron_region3 = sb_region3.MnvH1D_Vertex_R_Iron[0]->GetBinContent(i);
    double nOther_region3 = sb_region3.MnvH1D_Vertex_R_Other[0]->GetBinContent(i);
    double nAluminium_region3 = InPut_Alwgt_region3 * sb_region3.MnvH1D_Vertex_R_Aluminium[0]->GetBinContent(i);
    ////
    double nHelium_region4 = sb_region4.MnvH1D_Vertex_R_Helium[0]->GetBinContent(i);
    double nCarbon_region4 = sb_region4.MnvH1D_Vertex_R_Carbon[0]->GetBinContent(i);
    double nLead_region4 = sb_region4.MnvH1D_Vertex_R_Lead[0]->GetBinContent(i);
    double nIron_region4 = sb_region4.MnvH1D_Vertex_R_Iron[0]->GetBinContent(i);
    double nOther_region4 = sb_region4.MnvH1D_Vertex_R_Other[0]->GetBinContent(i);
    double nAluminium_region4 = InPut_Alwgt_region4 * sb_region4.MnvH1D_Vertex_R_Aluminium[0]->GetBinContent(i);
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
double calc_ChiSq_SideBand_region1_CV(Helium3SideBand  &sb, Double_t *par,
   int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1){
     double value = calc_ChiSq_For_SideBand_CV(sb, par[0]);
     return value;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
double calc_ChiSq_SideBand_region2_CV(Helium3SideBand  &sb, Double_t *par,
  int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1){
    double value = calc_ChiSq_For_SideBand_CV(sb, par[1]);
    return value;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
double calc_ChiSq_SideBand_region3_CV(Helium3SideBand  &sb, Double_t *par,
  int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1){
    double value = calc_ChiSq_For_SideBand_CV(sb, par[2]);
    return value;
  }
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
double calc_ChiSq_SideBand_region4_CV(Helium3SideBand  &sb, Double_t *par,
  int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1){
    double value = calc_ChiSq_For_SideBand_CV(sb, par[3]);
    return value;
  }

///////////////////////////////////////////
// reweight Helium and Al
/////////////////////////////////////////

double calc_ChiSq_SideBand_UpstreamCap_He_Al_fit_CV(Helium3SideBand  &sb, Double_t *par,
  int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1){
    double value = calc_ChiSq_For_SideBand_CV(sb, par[0], par[4]);
    return value;
  }
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
double calc_ChiSq_SideBand_Barrel_He_Al_fit_CV(Helium3SideBand  &sb, Double_t *par,
  int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1){
    double value = calc_ChiSq_For_SideBand_CV(sb, par[1], par[5] );
    return value;
  }
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

double calc_ChiSq_SideBand_downstreamCap_He_Al_fit_CV(Helium3SideBand  &sb, Double_t *par,
  int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1){
    double value = calc_ChiSq_For_SideBand_CV(sb, par[2], par[6]);
    return value;
  }
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

double calc_ChiSq_SideBand_downstreamConcaveCap_He_Al_fit_CV(Helium3SideBand  &sb, Double_t *par,
  int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1){
    double value = calc_ChiSq_For_SideBand_CV(sb, par[3] , par[7]);
    return value;
  }
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
double calc_ChiSq_For_SideBand_CV_Vertex_Z_Region14(
CryoRegion_HeliumNSideBand_Map InputMap,
  Double_t *InPut_Alwgt,
   int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1)/*removed First bin*/
{
  //std::cout<<"inside:calc_ChiSq_SideBand"<<std::endl;

    if (!isPartial){
        min_bin = 1; /*removed First bin*/
        max_bin = InputMap.begin()->second.MnvH1D_Vertex_Z_data->GetNbinsX();
    }
    //if( InputMap.size() != InPut_Alwgt.size() ) {std::cout<<"ERROR input of fitting parameters are diffrerent to number of regions"<<std::endl;assert(false);}


    if (min_bin == max_bin){
        cout<<"Wrong Range for Fit"<<endl;
        exit(EXIT_FAILURE);
    }

    double ChiSq = 0.0;
    double err = 0.0;
    double nData = 0.0;
    double nHelium = 0.0;
    double nCarbon = 0.0;
    double nLead = 0.0;
    double nIron = 0.0;
    double nOther = 0.0;
    double nAluminium = 0.0;
    int Wgt_Region_couter = 0;




    for (int i = min_bin; i <= max_bin; ++i){
        // Get N(Events) in Single Bin


        err = 0.0;
        nData = 0.0;
        nHelium = 0.0;
        nCarbon = 0.0;
        nLead = 0.0;
        nIron = 0.0;
        nOther = 0.0;
        nAluminium = 0.0;


        Wgt_Region_couter = 0;
        for(auto Region : InputMap ){

         err += Region.second.MnvH1D_Vertex_Z_data->GetBinError(i);
         nData += Region.second.MnvH1D_Vertex_Z_data->GetBinContent(i);

         nHelium += Region.second.MnvH1D_Vertex_Z_Helium[0]->GetBinContent(i);
         nCarbon += Region.second.MnvH1D_Vertex_Z_Carbon[0]->GetBinContent(i);
         nLead += Region.second.MnvH1D_Vertex_Z_Lead[0]->GetBinContent(i);
         nIron += Region.second.MnvH1D_Vertex_Z_Iron[0]->GetBinContent(i);
         nOther += Region.second.MnvH1D_Vertex_Z_Other[0]->GetBinContent(i);
         nAluminium += InPut_Alwgt[Wgt_Region_couter] * Region.second.MnvH1D_Vertex_Z_Aluminium[0]->GetBinContent(i);
        ////
        // Add All MC and scale them
        Wgt_Region_couter++;
      }
      if (nData == 0 ) continue;
      double nMC_total = (nHelium + nAluminium + nCarbon + nLead + nIron  + nOther);
      double delta = pow((nData-nMC_total),2) / pow(err,2);
      ChiSq += delta;
      }

    return ChiSq;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
double calc_ChiSq_For_SideBand_CV_Vertex_Z_Region14_LOG(
CryoRegion_HeliumNSideBand_Map InputMap,
  Double_t *InPut_Alwgt,
   int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1)/*removed First bin*/
{
  //std::cout<<"inside:calc_ChiSq_SideBand"<<std::endl;

    if (!isPartial){
        min_bin = 1; /*removed First bin*/
        max_bin = InputMap.begin()->second.MnvH1D_Vertex_Z_data->GetNbinsX();
    }
    //if( InputMap.size() != InPut_Alwgt.size() ) {std::cout<<"ERROR input of fitting parameters are diffrerent to number of regions"<<std::endl;assert(false);}


    if (min_bin == max_bin){
        cout<<"Wrong Range for Fit"<<endl;
        exit(EXIT_FAILURE);
    }

    double ChiSq = 0.0;
    double err = 0.0;
    double nData = 0.0;
    double nHelium = 0.0;
    double nCarbon = 0.0;
    double nLead = 0.0;
    double nIron = 0.0;
    double nOther = 0.0;
    double nAluminium = 0.0;
    int Wgt_Region_couter = 0;




    for (int i = min_bin; i <= max_bin; ++i){
        // Get N(Events) in Single Bin


        err = 0.0;
        nData = 0.0;
        nHelium = 0.0;
        nCarbon = 0.0;
        nLead = 0.0;
        nIron = 0.0;
        nOther = 0.0;
        nAluminium = 0.0;


        Wgt_Region_couter = 0;
        for(auto Region : InputMap ){

         err += Region.second.MnvH1D_Vertex_Z_data->GetBinError(i);
         nData += Region.second.MnvH1D_Vertex_Z_data->GetBinContent(i);

         nHelium += Region.second.MnvH1D_Vertex_Z_Helium[0]->GetBinContent(i);
         nCarbon += Region.second.MnvH1D_Vertex_Z_Carbon[0]->GetBinContent(i);
         nLead += Region.second.MnvH1D_Vertex_Z_Lead[0]->GetBinContent(i);
         nIron += Region.second.MnvH1D_Vertex_Z_Iron[0]->GetBinContent(i);
         nOther += Region.second.MnvH1D_Vertex_Z_Other[0]->GetBinContent(i);
         nAluminium += InPut_Alwgt[Wgt_Region_couter] * Region.second.MnvH1D_Vertex_Z_Aluminium[0]->GetBinContent(i);
        ////
        // Add All MC and scale them
        Wgt_Region_couter++;
      }
      if (nData == 0 ) continue;
      double nMC_total = (nHelium + nAluminium + nCarbon + nLead + nIron  + nOther);
      if (nMC_total <= 0) continue;
      double c = nData * log(nMC_total);
      double delta = 2 * (nMC_total - c);

      ChiSq += delta;
      }

    return ChiSq;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
double calc_ChiSq_For_SideBand_CV_Vertex_X_Region14(
CryoRegion_HeliumNSideBand_Map InputMap,
  Double_t *InPut_Alwgt,
   int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1)/*removed First bin*/
{
  //std::cout<<"inside:calc_ChiSq_SideBand"<<std::endl;

    if (!isPartial){
        min_bin = 1; /*removed First bin*/
        max_bin = InputMap.begin()->second.MnvH1D_Vertex_X_data->GetNbinsX();
    }
    //if( InputMap.size() != InPut_Alwgt.size() ) {std::cout<<"ERROR input of fitting parameters are diffrerent to number of regions"<<std::endl;assert(false);}


    if (min_bin == max_bin){
        cout<<"Wrong Range for Fit"<<endl;
        exit(EXIT_FAILURE);
    }

    double ChiSq = 0.0;
    double err = 0.0;
    double nData = 0.0;
    double nHelium = 0.0;
    double nCarbon = 0.0;
    double nLead = 0.0;
    double nIron = 0.0;
    double nOther = 0.0;
    double nAluminium = 0.0;
    int Wgt_Region_couter = 0;




    for (int i = min_bin; i <= max_bin; ++i){
        // Get N(Events) in Single Bin


        err = 0.0;
        nData = 0.0;
        nHelium = 0.0;
        nCarbon = 0.0;
        nLead = 0.0;
        nIron = 0.0;
        nOther = 0.0;
        nAluminium = 0.0;


        Wgt_Region_couter = 0;
        for(auto Region : InputMap ){

         err += Region.second.MnvH1D_Vertex_X_data->GetBinError(i);
         nData += Region.second.MnvH1D_Vertex_X_data->GetBinContent(i);
         nHelium += Region.second.MnvH1D_Vertex_X_Helium[0]->GetBinContent(i);
         nCarbon += Region.second.MnvH1D_Vertex_X_Carbon[0]->GetBinContent(i);
         nLead += Region.second.MnvH1D_Vertex_X_Lead[0]->GetBinContent(i);
         nIron += Region.second.MnvH1D_Vertex_X_Iron[0]->GetBinContent(i);
         nOther += Region.second.MnvH1D_Vertex_X_Other[0]->GetBinContent(i);
         nAluminium += InPut_Alwgt[Wgt_Region_couter] * Region.second.MnvH1D_Vertex_X_Aluminium[0]->GetBinContent(i);
        ////
        // Add All MC and scale them
        Wgt_Region_couter++;
      }
      if (nData == 0 ) continue;

      double nMC_total = (nHelium + nAluminium + nCarbon + nLead + nIron  + nOther);
      double delta = pow((nData-nMC_total),2) / pow(err,2);
      ChiSq += delta;
      }

    return ChiSq;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
double calc_ChiSq_For_SideBand_CV_Vertex_X_Region14_LOG(
CryoRegion_HeliumNSideBand_Map InputMap,
  Double_t *InPut_Alwgt,
   int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1)/*removed First bin*/
{
  //std::cout<<"inside:calc_ChiSq_SideBand"<<std::endl;

    if (!isPartial){
        min_bin = 1; /*removed First bin*/
        max_bin = InputMap.begin()->second.MnvH1D_Vertex_X_data->GetNbinsX();
    }
    //if( InputMap.size() != InPut_Alwgt.size() ) {std::cout<<"ERROR input of fitting parameters are diffrerent to number of regions"<<std::endl;assert(false);}


    if (min_bin == max_bin){
        cout<<"Wrong Range for Fit"<<endl;
        exit(EXIT_FAILURE);
    }

    double ChiSq = 0.0;
    double err = 0.0;
    double nData = 0.0;
    double nHelium = 0.0;
    double nCarbon = 0.0;
    double nLead = 0.0;
    double nIron = 0.0;
    double nOther = 0.0;
    double nAluminium = 0.0;
    int Wgt_Region_couter = 0;




    for (int i = min_bin; i <= max_bin; ++i){
        // Get N(Events) in Single Bin


        err = 0.0;
        nData = 0.0;
        nHelium = 0.0;
        nCarbon = 0.0;
        nLead = 0.0;
        nIron = 0.0;
        nOther = 0.0;
        nAluminium = 0.0;


        Wgt_Region_couter = 0;
        for(auto Region : InputMap ){

         err += Region.second.MnvH1D_Vertex_X_data->GetBinError(i);
         nData +=  Region.second.MnvH1D_Vertex_X_data->GetBinContent(i);

         nHelium += Region.second.MnvH1D_Vertex_X_Helium[0]->GetBinContent(i);
         nCarbon += Region.second.MnvH1D_Vertex_X_Carbon[0]->GetBinContent(i);
         nLead += Region.second.MnvH1D_Vertex_X_Lead[0]->GetBinContent(i);
         nIron += Region.second.MnvH1D_Vertex_X_Iron[0]->GetBinContent(i);
         nOther += Region.second.MnvH1D_Vertex_X_Other[0]->GetBinContent(i);
         nAluminium += InPut_Alwgt[Wgt_Region_couter] * Region.second.MnvH1D_Vertex_X_Aluminium[0]->GetBinContent(i);
        ////
        // Add All MC and scale them
        Wgt_Region_couter++;
      }
        if (nData == 0 ) continue;
      double nMC_total = (nHelium + nAluminium + nCarbon + nLead + nIron  + nOther);
      if (nMC_total <= 0) continue;
      double c = nData * log(nMC_total);
      double delta = 2 * (nMC_total - c);

      ChiSq += delta;
      }

    return ChiSq;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
double calc_ChiSq_For_SideBand_CV_Vertex_Y_Region14(
CryoRegion_HeliumNSideBand_Map InputMap,
  double *InPut_Alwgt,
   int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1)/*removed First bin*/
{
  //std::cout<<"inside:calc_ChiSq_SideBand"<<std::endl;

    if (!isPartial){
        min_bin = 1; /*removed First bin*/
        max_bin = InputMap.begin()->second.MnvH1D_Vertex_Y_data->GetNbinsX();
    }
    //if( InputMap.size() != InPut_Alwgt.size() ) {std::cout<<"ERROR input of fitting parameters are diffrerent to number of regions"<<std::endl;assert(false);}


    if (min_bin == max_bin){
        cout<<"Wrong Range for Fit"<<endl;
        exit(EXIT_FAILURE);
    }

    double ChiSq = 0.0;
    double err = 0.0;
    double nData = 0.0;
    double nHelium = 0.0;
    double nCarbon = 0.0;
    double nLead = 0.0;
    double nIron = 0.0;
    double nOther = 0.0;
    double nAluminium = 0.0;
    int Wgt_Region_couter = 0;

    for (int i = min_bin; i <= max_bin; ++i){
        // Get N(Events) in Single Bin


        err = 0.0;
        nData = 0.0;
        nHelium = 0.0;
        nCarbon = 0.0;
        nLead = 0.0;
        nIron = 0.0;
        nOther = 0.0;
        nAluminium = 0.0;


        Wgt_Region_couter = 0;
        for(auto Region : InputMap ){

         err += Region.second.MnvH1D_Vertex_Y_data->GetBinError(i);
         nData += Region.second.MnvH1D_Vertex_Y_data->GetBinContent(i);

         nHelium += Region.second.MnvH1D_Vertex_Y_Helium[0]->GetBinContent(i);
         nCarbon += Region.second.MnvH1D_Vertex_Y_Carbon[0]->GetBinContent(i);
         nLead += Region.second.MnvH1D_Vertex_Y_Lead[0]->GetBinContent(i);
         nIron += Region.second.MnvH1D_Vertex_Y_Iron[0]->GetBinContent(i);
         nOther += Region.second.MnvH1D_Vertex_Y_Other[0]->GetBinContent(i);
         nAluminium += InPut_Alwgt[Wgt_Region_couter] * Region.second.MnvH1D_Vertex_Y_Aluminium[0]->GetBinContent(i);
        ////
        // Add All MC and scale them
        Wgt_Region_couter++;
      }
      if (nData == 0 ) continue;

      double nMC_total = (nHelium + nAluminium + nCarbon + nLead + nIron  + nOther);
      double delta = pow((nData-nMC_total),2) / pow(err,2);
      ChiSq += delta;
      }

    return ChiSq;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
double calc_ChiSq_For_SideBand_CV_Vertex_Y_Region14_LOG(
CryoRegion_HeliumNSideBand_Map InputMap,
  Double_t *InPut_Alwgt,
   int unv = 0, bool isPartial = false, int min_bin = 1, int max_bin = 1)/*removed First bin*/
{
  //std::cout<<"inside:calc_ChiSq_SideBand"<<std::endl;

    if (!isPartial){
        min_bin = 1; /*removed First bin*/
        max_bin = InputMap.begin()->second.MnvH1D_Vertex_Y_data->GetNbinsX();
    }
    //if( InputMap.size() != InPut_Alwgt.size() ) {std::cout<<"ERROR input of fitting parameters are diffrerent to number of regions"<<std::endl;assert(false);}


    if (min_bin == max_bin){
        cout<<"Wrong Range for Fit"<<endl;
        exit(EXIT_FAILURE);
    }

    double ChiSq = 0.0;
    double err = 0.0;
    double nData = 0.0;
    double nHelium = 0.0;
    double nCarbon = 0.0;
    double nLead = 0.0;
    double nIron = 0.0;
    double nOther = 0.0;
    double nAluminium = 0.0;
    int Wgt_Region_couter = 0;




    for (int i = min_bin; i <= max_bin; ++i){
        // Get N(Events) in Single Bin


        err = 0.0;
        nData = 0.0;
        nHelium = 0.0;
        nCarbon = 0.0;
        nLead = 0.0;
        nIron = 0.0;
        nOther = 0.0;
        nAluminium = 0.0;


        Wgt_Region_couter = 0;
        for(auto Region : InputMap ){

         err += Region.second.MnvH1D_Vertex_Y_data->GetBinError(i);
         nData +=  Region.second.MnvH1D_Vertex_Y_data->GetBinContent(i);

         nHelium += Region.second.MnvH1D_Vertex_Y_Helium[0]->GetBinContent(i);
         nCarbon += Region.second.MnvH1D_Vertex_Y_Carbon[0]->GetBinContent(i);
         nLead += Region.second.MnvH1D_Vertex_Y_Lead[0]->GetBinContent(i);
         nIron += Region.second.MnvH1D_Vertex_Y_Iron[0]->GetBinContent(i);
         nOther += Region.second.MnvH1D_Vertex_Y_Other[0]->GetBinContent(i);
         nAluminium += InPut_Alwgt[Wgt_Region_couter] * Region.second.MnvH1D_Vertex_Y_Aluminium[0]->GetBinContent(i);
        ////
        // Add All MC and scale them
        Wgt_Region_couter++;
      }
      if (nData == 0 ) continue;
      double nMC_total = (nHelium + nAluminium + nCarbon + nLead + nIron  + nOther);
      if (nMC_total <= 0) continue;
      double c = nData * log(nMC_total);
      double delta = 2 * (nMC_total - c);

      ChiSq += delta;
      }

    return ChiSq;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void SetHelium3SideBandTool(Helium_3CryoRegionsSideBandTool sbtool_input){
  std::cout<<"inside setting Tool"<< std::endl;
sbtool3region_global = sbtool_input;
std::cout<<"decleared Global Helium3SideBand for fitting "<<std::endl;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void calc_ChiSq_Empty(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
    // Silence Unused Variable Warning
    (void) npar;
    (void) gin;
    (void) iflag;

    double ChiSq = 0;
//std::cout<<"Chi  start"<<  ChiSq<<std::endl;
    // Calculate ChiSq for Empty for ALL Bins
    //ChiSq += calc_ChiSq_SideBand(sbtool3region_global.Helium_Empty, par, sbtool3region_global.current_unv);
    ChiSq +=calc_ChiSq_For_SideBand_CV_Vertex_X(sbtool3region_global.Empty_UpstreamCap,
                                          sbtool3region_global.Empty_Barrel,
                                          sbtool3region_global.Empty_DownstreamCap,
                                          sbtool3region_global.Empty_DownstreamConcaveCap,par[0],par[1],par[2],par[3]);

                                      //    std::cout<<"Chi  X "<<  ChiSq<<std::endl;

    ChiSq +=calc_ChiSq_For_SideBand_CV_Vertex_Y(sbtool3region_global.Empty_UpstreamCap,
                                                  sbtool3region_global.Empty_Barrel,
                                                  sbtool3region_global.Empty_DownstreamCap,
                                                  sbtool3region_global.Empty_DownstreamConcaveCap,par[0],par[1],par[2],par[3]);

                                              //    std::cout<<"Chi  Y"<<  ChiSq<<std::endl;

    ChiSq +=calc_ChiSq_For_SideBand_CV_Vertex_Z(sbtool3region_global.Empty_UpstreamCap,
                                                sbtool3region_global.Empty_Barrel,
                                                sbtool3region_global.Empty_DownstreamCap,
                                                sbtool3region_global.Empty_DownstreamConcaveCap,par[0],par[1],par[2],par[3]);

                                              //  std::cout<<"Chi  Z "<<  ChiSq<<std::endl;

  //  ChiSq +=calc_ChiSq_For_SideBand_CV_Vertex_R(sbtool3region_global.Empty_UpstreamCap,
  //                                              sbtool3region_global.Empty_Barrel,
  //                                              sbtool3region_global.Empty_DownstreamCap,
  //                                              sbtool3region_global.Empty_DownstreamConcaveCap,par[0],par[1],par[2],par[3]);

                                          //      std::cout<<"Chi  R"<<  ChiSq<<std::endl;

    f = ChiSq;
    return;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void calc_ChiSq_Empty_RZ(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
    // Silence Unused Variable Warning
    (void) npar;
    (void) gin;
    (void) iflag;

    double ChiSq = 0;
//std::cout<<"Chi  start"<<  ChiSq<<std::endl;
    // Calculate ChiSq for Empty for ALL Bins
    //ChiSq += calc_ChiSq_SideBand(sbtool3region_global.Helium_Empty, par, sbtool3region_global.current_unv);

    ChiSq +=calc_ChiSq_For_SideBand_CV_Vertex_Z(sbtool3region_global.Empty_UpstreamCap,
                                                sbtool3region_global.Empty_Barrel,
                                                sbtool3region_global.Empty_DownstreamCap,
                                                sbtool3region_global.Empty_DownstreamConcaveCap,par[0],par[1],par[2],par[3]);

                                              //  std::cout<<"Chi  Z "<<  ChiSq<<std::endl;

    ChiSq +=calc_ChiSq_For_SideBand_CV_Vertex_R(sbtool3region_global.Empty_UpstreamCap,
                                                sbtool3region_global.Empty_Barrel,
                                                sbtool3region_global.Empty_DownstreamCap,
                                               sbtool3region_global.Empty_DownstreamConcaveCap,par[0],par[1],par[2],par[3]);

                                          //      std::cout<<"Chi  R"<<  ChiSq<<std::endl;

    f = ChiSq;
    return;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void calc_ChiSq_EmptyLog(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
    // Silence Unused Variable Warning
    (void) npar;
    (void) gin;
    (void) iflag;

    double ChiSq = 0;
//std::cout<<"Chi  start"<<  ChiSq<<std::endl;
    // Calculate ChiSq for Empty for ALL Bins
    //ChiSq += calc_ChiSq_SideBand(sbtool3region_global.Helium_Empty, par, sbtool3region_global.current_unv);
    ChiSq +=calc_ChiSqLog_For_SideBand_CV_Vertex_X(sbtool3region_global.Empty_UpstreamCap,
                                          sbtool3region_global.Empty_Barrel,
                                          sbtool3region_global.Empty_DownstreamCap,
                                          sbtool3region_global.Empty_DownstreamConcaveCap,par[0],par[1],par[2],par[3]);

                                      //    std::cout<<"Chi  X "<<  ChiSq<<std::endl;

    ChiSq +=calc_ChiSqLog_For_SideBand_CV_Vertex_Y(sbtool3region_global.Empty_UpstreamCap,
                                                  sbtool3region_global.Empty_Barrel,
                                                  sbtool3region_global.Empty_DownstreamCap,
                                                  sbtool3region_global.Empty_DownstreamConcaveCap,par[0],par[1],par[2],par[3]);

                                              //    std::cout<<"Chi  Y"<<  ChiSq<<std::endl;

    ChiSq +=calc_ChiSqLog_For_SideBand_CV_Vertex_Z(sbtool3region_global.Empty_UpstreamCap,
                                                sbtool3region_global.Empty_Barrel,
                                                sbtool3region_global.Empty_DownstreamCap,
                                                sbtool3region_global.Empty_DownstreamConcaveCap,par[0],par[1],par[2],par[3]);

    //ChiSq +=calc_ChiSqLog_For_SideBand_CV_Vertex_R(sbtool3region_global.Empty_UpstreamCap,
      //                                          sbtool3region_global.Empty_Barrel,
        //                                        sbtool3region_global.Empty_DownstreamCap,
          //                                      sbtool3region_global.Empty_DownstreamConcaveCap,par[0],par[1],par[2],par[3]);

    f = ChiSq;
    return;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void calc_ChiSq_Empty_regionX(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
    // Silence Unused Variable Warning
    (void) npar;
    (void) gin;
    (void) iflag;

    double ChiSq = 0;

    // Calculate ChiSq for Empty for ALL Bins
    //ChiSq += calc_ChiSq_SideBand(sbtool3region_global.Helium_Empty, par, sbtool3region_global.current_unv);

  ChiSq +=calc_ChiSq_For_SideBand_CV_Vertex_X(sbtool3region_global.Empty_XCenter,
                                        sbtool3region_global.Empty_XLeftShelf,
                                        sbtool3region_global.Empty_XRightShelf,
                                        sbtool3region_global.Empty_XoutsideEdges,par[0],par[1],par[2],par[3]);

  ChiSq +=calc_ChiSq_For_SideBand_CV_Vertex_Y(sbtool3region_global.Empty_XCenter,
                                                sbtool3region_global.Empty_XLeftShelf,
                                                sbtool3region_global.Empty_XRightShelf,
                                                sbtool3region_global.Empty_XoutsideEdges,par[0],par[1],par[2],par[3]);

  ChiSq +=calc_ChiSq_For_SideBand_CV_Vertex_Z(sbtool3region_global.Empty_XCenter,
                                              sbtool3region_global.Empty_XLeftShelf,
                                              sbtool3region_global.Empty_XRightShelf,
                                              sbtool3region_global.Empty_XoutsideEdges,par[0],par[1],par[2],par[3]);

  ChiSq +=calc_ChiSq_For_SideBand_CV_Vertex_R(sbtool3region_global.Empty_XCenter,
                                              sbtool3region_global.Empty_XLeftShelf,
                                              sbtool3region_global.Empty_XRightShelf,
                                              sbtool3region_global.Empty_XoutsideEdges,par[0],par[1],par[2],par[3]);


    f = ChiSq;
    return;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void calc_ChiSq_Empty_regionXZ(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
    // Silence Unused Variable Warning
    (void) npar;
    (void) gin;
    (void) iflag;

    double ChiSq = 0;

    // Calculate ChiSq for Empty for ALL Bins
    //ChiSq += calc_ChiSq_SideBand(sbtool3region_global.Helium_Empty, par, sbtool3region_global.current_unv);

  ChiSq +=calc_ChiSq_For_SideBand_CV_Vertex_X(sbtool3region_global.Empty_XCenter,
                                        sbtool3region_global.Empty_XLeftShelf,
                                        sbtool3region_global.Empty_XRightShelf,
                                        sbtool3region_global.Empty_DownstreamConcaveCap,par[0],par[1],par[2],par[3]);

  ChiSq +=calc_ChiSq_For_SideBand_CV_Vertex_Y(sbtool3region_global.Empty_XCenter,
                                                sbtool3region_global.Empty_XLeftShelf,
                                                sbtool3region_global.Empty_XRightShelf,
                                                sbtool3region_global.Empty_DownstreamConcaveCap,par[0],par[1],par[2],par[3]);

  ChiSq +=calc_ChiSq_For_SideBand_CV_Vertex_Z(sbtool3region_global.Empty_XCenter,
                                              sbtool3region_global.Empty_XLeftShelf,
                                              sbtool3region_global.Empty_XRightShelf,
                                              sbtool3region_global.Empty_DownstreamConcaveCap,par[0],par[1],par[2],par[3]);

  ChiSq +=calc_ChiSq_For_SideBand_CV_Vertex_R(sbtool3region_global.Empty_XCenter,
                                              sbtool3region_global.Empty_XLeftShelf,
                                              sbtool3region_global.Empty_XRightShelf,
                                              sbtool3region_global.Empty_DownstreamConcaveCap,par[0],par[1],par[2],par[3]);


    f = ChiSq;
    return;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void calc_ChiSq_Empty_regionX_Zonly(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
    // Silence Unused Variable Warning
    (void) npar;
    (void) gin;
    (void) iflag;

    double ChiSq = 0;

    // Calculate ChiSq for Empty for ALL Bins
    //ChiSq += calc_ChiSq_SideBand(sbtool3region_global.Helium_Empty, par, sbtool3region_global.current_unv);



  ChiSq +=calc_ChiSq_For_SideBand_CV_Vertex_Z(sbtool3region_global.Empty_XCenter,
                                              sbtool3region_global.Empty_XLeftShelf,
                                              sbtool3region_global.Empty_XRightShelf,
                                              sbtool3region_global.Empty_XoutsideEdges,par[0],par[1],par[2],par[3]);

    f = ChiSq;
    return;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void calc_ChiSq_Empty_regionX_XandYOnly(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
    // Silence Unused Variable Warning
    (void) npar;
    (void) gin;
    (void) iflag;

    double ChiSq = 0;

    // Calculate ChiSq for Empty for ALL Bins
    //ChiSq += calc_ChiSq_SideBand(sbtool3region_global.Helium_Empty, par, sbtool3region_global.current_unv);
    ChiSq +=calc_ChiSq_For_SideBand_CV_Vertex_X(sbtool3region_global.Empty_XCenter,
                                          sbtool3region_global.Empty_XLeftShelf,
                                          sbtool3region_global.Empty_XRightShelf,
                                          sbtool3region_global.Empty_XoutsideEdges,par[0],par[1],par[2],par[3]);

    ChiSq +=calc_ChiSq_For_SideBand_CV_Vertex_Y(sbtool3region_global.Empty_XCenter,
                                                  sbtool3region_global.Empty_XLeftShelf,
                                                  sbtool3region_global.Empty_XRightShelf,
                                                  sbtool3region_global.Empty_XoutsideEdges,par[0],par[1],par[2],par[3]);

    f = ChiSq;
    return;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void calc_ChiSq_Full(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
    // Silence Unused Variable Warning
    (void) npar;
    (void) gin;
    (void) iflag;

    double ChiSq = 0;

    // Calculate ChiSq for Empty for ALL Bins
    //ChiSq += calc_ChiSq_SideBand(sbtool3region_global.Helium_Empty, par, sbtool3region_global.current_unv);
    ChiSq +=calc_ChiSq_SideBand_region1_CV(sbtool3region_global.Full_UpstreamCap, par);
    ChiSq +=calc_ChiSq_SideBand_region2_CV(sbtool3region_global.Full_Barrel, par);
    ChiSq +=calc_ChiSq_SideBand_region3_CV(sbtool3region_global.Full_DownstreamCap, par);
    ChiSq +=calc_ChiSq_SideBand_region4_CV(sbtool3region_global.Full_DownstreamConcaveCap, par);

    f = ChiSq;
    return;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void calc_ChiSq_Full_Empty(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
    // Silence Unused Variable Warning
    (void) npar;
    (void) gin;
    (void) iflag;

    double ChiSq = 0;

    // Calculate ChiSq for Empty for ALL Bins
    //ChiSq += calc_ChiSq_SideBand(sbtool3region_global.Helium_Empty, par, sbtool3region_global.current_unv);
    ChiSq +=calc_ChiSq_SideBand_region1_CV(sbtool3region_global.Full_Empty_UpstreamCap, par);
    ChiSq +=calc_ChiSq_SideBand_region2_CV(sbtool3region_global.Full_Empty_Barrel, par);
    ChiSq +=calc_ChiSq_SideBand_region3_CV(sbtool3region_global.Full_Empty_DownstreamCap, par);
    ChiSq +=calc_ChiSq_SideBand_region4_CV(sbtool3region_global.Full_Empty_DownstreamConcaveCap, par);

    f = ChiSq;
    return;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void calc_ChiSq_FullandEmptyCombinedFit(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
    // Silence Unused Variable Warning
    (void) npar;
    (void) gin;
    (void) iflag;

    double ChiSq = 0;

    // Calculate ChiSq for Empty for ALL Bins
    //ChiSq += calc_ChiSq_SideBand(sbtool3region_global.Helium_Empty, par, sbtool3region_global.current_unv);
    ChiSq +=calc_ChiSq_SideBand_UpstreamCap_He_Al_fit_CV(sbtool3region_global.Full_UpstreamCap, par);
    ChiSq +=calc_ChiSq_SideBand_Barrel_He_Al_fit_CV(sbtool3region_global.Full_Barrel, par);
    ChiSq +=calc_ChiSq_SideBand_downstreamCap_He_Al_fit_CV(sbtool3region_global.Full_DownstreamCap, par);
    ChiSq +=calc_ChiSq_SideBand_downstreamConcaveCap_He_Al_fit_CV(sbtool3region_global.Full_DownstreamConcaveCap, par);

    ChiSq +=calc_ChiSq_SideBand_UpstreamCap_He_Al_fit_CV(sbtool3region_global.Empty_UpstreamCap, par);
    ChiSq +=calc_ChiSq_SideBand_Barrel_He_Al_fit_CV(sbtool3region_global.Empty_Barrel, par);
    ChiSq +=calc_ChiSq_SideBand_downstreamCap_He_Al_fit_CV(sbtool3region_global.Empty_DownstreamCap, par);
    ChiSq +=calc_ChiSq_SideBand_downstreamConcaveCap_He_Al_fit_CV(sbtool3region_global.Empty_DownstreamConcaveCap, par);

    f = ChiSq;
    return;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void calc_ChiSq_Empty_Region14(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
    // Silence Unused Variable Warning
    (void) npar;
    (void) gin;
    (void) iflag;

    double ChiSq = 0;
//std::cout<<"Chi  start"<<  ChiSq<<std::endl;
    // Calculate ChiSq for Empty for ALL Bins
    //ChiSq += calc_ChiSq_SideBand(sbtool3region_global.Helium_Empty, par, sbtool3region_global.current_unv);


    ChiSq += calc_ChiSq_For_SideBand_CV_Vertex_Z_Region14(sbtool3region_global.CryoRegionMap_Empty, par);
    ChiSq += calc_ChiSq_For_SideBand_CV_Vertex_X_Region14(sbtool3region_global.CryoRegionMap_Empty, par);
    ChiSq += calc_ChiSq_For_SideBand_CV_Vertex_Y_Region14(sbtool3region_global.CryoRegionMap_Empty, par);

    f = ChiSq;
    return;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void calc_ChiSq_Empty_Region14_LOG(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
    // Silence Unused Variable Warning
    (void) npar;
    (void) gin;
    (void) iflag;

    double ChiSq = 0;
//std::cout<<"Chi  start"<<  ChiSq<<std::endl;
    // Calculate ChiSq for Empty for ALL Bins
    //ChiSq += calc_ChiSq_SideBand(sbtool3region_global.Helium_Empty, par, sbtool3region_global.current_unv);


    ChiSq += calc_ChiSq_For_SideBand_CV_Vertex_Z_Region14_LOG(sbtool3region_global.CryoRegionMap_Empty, par);
    ChiSq += calc_ChiSq_For_SideBand_CV_Vertex_X_Region14_LOG(sbtool3region_global.CryoRegionMap_Empty, par);
    ChiSq += calc_ChiSq_For_SideBand_CV_Vertex_Y_Region14_LOG(sbtool3region_global.CryoRegionMap_Empty, par);

    f = ChiSq;
    return;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void FitMinuit_Empty(Helium_3CryoRegionsSideBandTool sbtool, std::string fitName,
   std::string pdf_label, std::vector<double> &wgt_vector, std::vector<double> &wgt_error)
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
    ptMinuit->SetFCN(calc_ChiSq_Empty);

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

    sbtool.SaveFitResults(min_ChiSq, fParamVal, fParamErr);

    // Plot only for Central Value
    if (sbtool.current_unv == 0){
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
    }


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
void FitMinuit_Empty_RZ(Helium_3CryoRegionsSideBandTool sbtool, std::string fitName,
  std::string pdf_label, std::vector<double> &wgt_vector, std::vector<double> &wgt_error)
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
    ptMinuit->SetFCN(calc_ChiSq_Empty_RZ);

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

    sbtool.SaveFitResults(min_ChiSq, fParamVal, fParamErr);

    // Plot only for Central Value
    if (sbtool.current_unv == 0){
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
    }


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
void FitMinuit_EmptyLogchi2(Helium_3CryoRegionsSideBandTool sbtool, std::string fitName,
   std::string pdf_label, std::vector<double> &wgt_vector,
  std::vector<double> &wgt_error, double &errorofFit)
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
    ptMinuit->SetFCN(calc_ChiSq_EmptyLog);

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
    errorofFit = errdef;
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

    sbtool.SaveFitResults(min_ChiSq, fParamVal, fParamErr);

    // Plot only for Central Value
    if (sbtool.current_unv == 0){
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
    }


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
void FitMinuit_Empty_regionX(Helium_3CryoRegionsSideBandTool sbtool,
   std::string fitName, std::string pdf_label, std::vector<double> &wgt_vector, std::vector<double> &wgt_error)
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
    ptMinuit->SetPrintLevel(1);
    // set the user function that calculates chi_square (the value to minimize)
    ptMinuit->SetFCN(calc_ChiSq_Empty_regionX);

    Double_t arglist[10];
    Int_t ierflg = 0;

    arglist[0] = 1;
    ptMinuit->mnexcm("SET ERR", arglist ,1,ierflg);

    // Set starting values and step sizes for parameters
    //      Start from 1.0 and step 0.01
    ptMinuit->mnparm(0, "FitParm_Aluminium_XCenter",          .05, 0.05, .05, 10.0 , ierflg);
    ptMinuit->mnparm(1, "FitParm_Aluminium_XLeftShelf",       .05, 0.05, .05, 10.0 , ierflg);
    ptMinuit->mnparm(2, "FitParm_Aluminium_XRightShelf",      .05, 0.05, .05, 10.0 , ierflg);
    ptMinuit->mnparm(3, "FitParm_Aluminium_XoutsideEdges",    .05, 0.05, .05, 10.0 , ierflg);

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


    std::cout << "MnvH1D_Aluminium Center = " << fParamVal[0] << "\n";
    std::cout << "MnvH1D_Aluminium rightshelf = " << fParamVal[1] << "\n";
    std::cout << "MnvH1D_Aluminium Leftshelf = " << fParamVal[2] << "\n";
    std::cout << "MnvH1D_Aluminium XoutsideEdges  = " << fParamVal[3] << "\n";
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

    sbtool.SaveFitResults(min_ChiSq, fParamVal, fParamErr);

    // Plot only for Central Value
    if (sbtool.current_unv == 0){
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
    }


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
void FitMinuit_Empty_regionXZ(Helium_3CryoRegionsSideBandTool sbtool,
   std::string fitName, std::string pdf_label, std::vector<double> &wgt_vector, std::vector<double> &wgt_error)
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
    ptMinuit->SetPrintLevel(1);
    // set the user function that calculates chi_square (the value to minimize)
    ptMinuit->SetFCN(calc_ChiSq_Empty_regionXZ);

    Double_t arglist[10];
    Int_t ierflg = 0;

    arglist[0] = 1;
    ptMinuit->mnexcm("SET ERR", arglist ,1,ierflg);

    // Set starting values and step sizes for parameters
    //      Start from 1.0 and step 0.01
    ptMinuit->mnparm(0, "FitParm_Aluminium_XCenter",          .05, 0.05, .05, 10.0 , ierflg);
    ptMinuit->mnparm(1, "FitParm_Aluminium_XLeftShelf",       .05, 0.05, .05, 10.0 , ierflg);
    ptMinuit->mnparm(2, "FitParm_Aluminium_XRightShelf",      .05, 0.05, .05, 10.0 , ierflg);
    ptMinuit->mnparm(3, "FitParm_Aluminium_downstreamConcaveCap",    .05, 0.05, .05, 10.0 , ierflg);

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


    std::cout << "MnvH1D_Aluminium Center = " << fParamVal[0] << "\n";
    std::cout << "MnvH1D_Aluminium rightshelf = " << fParamVal[1] << "\n";
    std::cout << "MnvH1D_Aluminium Leftshelf = " << fParamVal[2] << "\n";
    std::cout << "MnvH1D_Aluminium downstreamConcaveCap  = " << fParamVal[3] << "\n";
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

    sbtool.SaveFitResults(min_ChiSq, fParamVal, fParamErr);

    // Plot only for Central Value
    if (sbtool.current_unv == 0){
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
    }


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
void FitMinuit_Empty_regionX_Vertex_Z_Only(Helium_3CryoRegionsSideBandTool sbtool,
   std::string fitName, std::string pdf_label, std::vector<double> &wgt_vector, std::vector<double> &wgt_error)
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
    ptMinuit->SetPrintLevel(0);
    // set the user function that calculates chi_square (the value to minimize)
    ptMinuit->SetFCN(calc_ChiSq_Empty_regionX_XandYOnly);  //calc_ChiSq_Empty_regionX_Zonly

    Double_t arglist[10];
    Int_t ierflg = 0;

    arglist[0] = 1;
    ptMinuit->mnexcm("SET ERR", arglist ,1,ierflg);

    // Set starting values and step sizes for parameters
    //      Start from 1.0 and step 0.01
    ptMinuit->mnparm(0, "FitParm_Aluminium_XCenter",          .05, 0.05, .1, 5.0 , ierflg);
    ptMinuit->mnparm(1, "FitParm_Aluminium_XLeftShelf",       .05, 0.05, .1, 5.0 , ierflg);
    ptMinuit->mnparm(2, "FitParm_Aluminium_XRightShelf",      .05, 0.05, .1, 5.0 , ierflg);
    ptMinuit->mnparm(3, "FitParm_Aluminium_XoutsideEdges",    .05, 0.05, .1, 5.0 , ierflg);

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


    std::cout << "MnvH1D_Aluminium Center = " << fParamVal[0] << "\n";
    std::cout << "MnvH1D_Aluminium rightshelf = " << fParamVal[1] << "\n";
    std::cout << "MnvH1D_Aluminium Leftshelf = " << fParamVal[2] << "\n";
    std::cout << "MnvH1D_Aluminium XoutsideEdges  = " << fParamVal[3] << "\n";
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

    sbtool.SaveFitResults(min_ChiSq, fParamVal, fParamErr);

    // Plot only for Central Value
    if (sbtool.current_unv == 0){
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
    }


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
void FitMinuit_Full(Helium_3CryoRegionsSideBandTool sbtool, std::string fitName,
   std::string pdf_label, std::vector<double> &wgt_vector, std::vector<double> &wgt_error)
{
    cout<<"======================================================================"<<endl;
    cout<<"Universe = "<<sbtool.current_unv<<endl;
    cout<<"======================================================================"<<endl;

    TMinuit *ptMinuit = new TMinuit(4);  //initialize TMinuit with a maximum of 3 params
    //
    //  select verbose level:
    //    default :     (58 lines in this test)
    //    -1 : minimum  ( 4 lines in this test)
    //     0 : low      (31 lines)
    //     1 : medium   (61 lines)
    //     2 : high     (89 lines)
    //     3 : maximum (199 lines in this test)
    //
    ptMinuit->SetPrintLevel();
    // set the user function that calculates chi_square (the value to minimize)
    ptMinuit->SetFCN(calc_ChiSq_Full);

    Double_t arglist[10];
    Int_t ierflg = 0;

    arglist[0] = 1;
    ptMinuit->mnexcm("SET ERR", arglist ,1,ierflg);

    // Set starting values and step sizes for parameters
    //      Start from 1.0 and step 0.01
    ptMinuit->mnparm(0, "FitParm_Aluminium_upstreamCap", .5, 0.01, .5, 10.0 , ierflg);
    ptMinuit->mnparm(1, "FitParm_Aluminium_Barrel", .5, 0.01, .5, 10.0 , ierflg);
    ptMinuit->mnparm(2, "FitParm_Aluminium_downstreamCap", .5, 0.01, .5, 10.0 , ierflg);
    ptMinuit->mnparm(3, "FitParm_Aluminium_downstreamConcaveCap", .05, 0.01, .05, 10.0 , ierflg);

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

    sbtool.SaveFitResults(min_ChiSq, fParamVal, fParamErr);

    // Plot only for Central Value
    if (sbtool.current_unv == 0){
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
    }


    //std::cout << "\n";
    //std::cout << " Minimum chi square = " << min_ChiSq<< "\n";
    //std::cout << " Estimated vert. distance to min. = " << edm << "\n";
    //std::cout << " Number of variable parameters = " << nvpar << "\n";
    //std::cout << " Highest number of parameters defined by user = " << nparx << "\n";
    //std::cout << " Status of covariance matrix = " << icstat << "\n";

    std::cout << "\n";
    ptMinuit->mnprin(1,min_ChiSq);
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
void FitMinuit_Full_Empty_Al_He_Combinedfit(Helium_3CryoRegionsSideBandTool sbtool,
  std::string fitName, std::string pdf_label, std::vector<double> &wgt_vector, std::vector<double> &wgt_error)
{
    cout<<"======================================================================"<<endl;
    cout<<"Universe = "<<sbtool.current_unv<<endl;
    cout<<"======================================================================"<<endl;

    TMinuit *ptMinuit = new TMinuit(8);  //initialize TMinuit with a maximum of 3 params
    //
    //  select verbose level:
    //    default :     (58 lines in this test)
    //    -1 : minimum  ( 4 lines in this test)
    //     0 : low      (31 lines)
    //     1 : medium   (61 lines)
    //     2 : high     (89 lines)
    //     3 : maximum (199 lines in this test)
    //
    ptMinuit->SetPrintLevel();
    // set the user function that calculates chi_square (the value to minimize)
    ptMinuit->SetFCN(calc_ChiSq_FullandEmptyCombinedFit);

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

    ptMinuit->mnparm(4, "FitParm_Helium_upstreamCap",          .05, 0.01, .01, 10.0 , ierflg);
    ptMinuit->mnparm(5, "FitParm_Helium_Barrel",               .05, 0.01, .01, 10.0 , ierflg);
    ptMinuit->mnparm(6, "FitParm_Helium_downstreamCap",        .05, 0.01, .01, 10.0 , ierflg);
    ptMinuit->mnparm(7, "FitParm_Helium_downstreamConcaveCap", .05, 0.01, .01, 10.0 , ierflg);



    // Now ready for minimization step
    arglist[0] = 50000;
    arglist[1] = 1.;
    ptMinuit->mnexcm("MIGRAD", arglist ,2,ierflg);

    // Print results
    std::cout<<"\nPrint results from minuit\n";
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





    std::cout << "MnvH1D_Aluminium Upstream = " << fParamVal[0] << "\n";
    std::cout << "MnvH1D_Aluminium Barrel = " << fParamVal[1] << "\n";
    std::cout << "MnvH1D_Aluminium Downstreamstream = " << fParamVal[2] << "\n";
    std::cout << "MnvH1D_Aluminium Downstream concave  = " << fParamVal[3] << "\n";
    // if you want to access to these parameters, use:

    std::cout << "MnvH1D_Helium Upstream = " << fParamVal[4] << "\n";
    std::cout << "MnvH1D_Helium Barrel = " << fParamVal[5] << "\n";
    std::cout << "MnvH1D_Helium Downstreamstream = " << fParamVal[6] << "\n";
    std::cout << "MnvH1D_Helium Downstream concave  = " << fParamVal[7] << "\n";


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

    sbtool.SaveFitResults_Al_and_He(min_ChiSq, fParamVal, fParamErr);

    // Plot only for Central Value
    if (sbtool.current_unv == 0){
      std::cout<<"running: setting fit values"<<std::endl;
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
    }


    std::cout << "\n";
    std::cout << " Minimum chi square = " << min_ChiSq<< "\n";
    std::cout << " Estimated vert. distance to min. = " << edm << "\n";
    std::cout << " Number of variable parameters = " << nvpar << "\n";
    std::cout << " Highest number of parameters defined by user = " << nparx << "\n";
    std::cout << " Status of covariance matrix = " << icstat << "\n";

    std::cout << "\n";
    ptMinuit->mnprin(1,min_ChiSq);
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
void FitMinuit_Full_Empty(Helium_3CryoRegionsSideBandTool sbtool,
   std::string fitName, std::string pdf_label, std::vector<double> &wgt_vector, std::vector<double> &wgt_error)
{
    cout<<"======================================================================"<<endl;
    cout<<"Universe = "<<sbtool.current_unv<<endl;
    cout<<"======================================================================"<<endl;

    TMinuit *ptMinuit = new TMinuit(4);  //initialize TMinuit with a maximum of 3 params
    //
    //  select verbose level:
    //    default :     (58 lines in this test)
    //    -1 : minimum  ( 4 lines in this test)
    //     0 : low      (31 lines)
    //     1 : medium   (61 lines)
    //     2 : high     (89 lines)
    //     3 : maximum (199 lines in this test)
    //
    ptMinuit->SetPrintLevel();
    // set the user function that calculates chi_square (the value to minimize)
    ptMinuit->SetFCN(calc_ChiSq_Full_Empty);

    Double_t arglist[10];
    Int_t ierflg = 0;

    arglist[0] = 1;
    ptMinuit->mnexcm("SET ERR", arglist ,1,ierflg);

    // Set starting values and step sizes for parameters
    //      Start from 1.0 and step 0.01
    ptMinuit->mnparm(0, "FitParm_Aluminium_upstreamCap", .5, 0.01, .01, 10.0 , ierflg);
    ptMinuit->mnparm(1, "FitParm_Aluminium_Barrel", .5, 0.01, .01, 10.0 , ierflg);
    ptMinuit->mnparm(2, "FitParm_Aluminium_downstreamCap", .5, 0.01, .01, 10.0 , ierflg);
    ptMinuit->mnparm(3, "FitParm_Aluminium_downstreamConcaveCap", .05, 0.01, .01, 10.0 , ierflg);

    // Now ready for minimization step
    arglist[0] = 20000;
    arglist[1] = 1.;
    ptMinuit->mnexcm("MIGRAD", arglist ,2,ierflg);

    // Print results
    std::cout<<"\nPrint results from minuit\n";
    double fParamVal[4];
    double fParamErr[4];
    ptMinuit->GetParameter(0, fParamVal[0], fParamErr[0]);
    ptMinuit->GetParameter(1, fParamVal[1], fParamErr[1]);
    ptMinuit->GetParameter(2, fParamVal[2], fParamErr[2]);
    ptMinuit->GetParameter(3, fParamVal[3], fParamErr[3]);


    std::cout << "MnvH1D_Aluminium Upstream = " << fParamVal[0] << "\n";
    std::cout << "MnvH1D_Aluminium Barrel = " << fParamVal[1] << "\n";
    std::cout << "MnvH1D_Aluminium Downstreamstream = " << fParamVal[2] << "\n";
    std::cout << "MnvH1D_Aluminium Downstream concave  = " << fParamVal[3] << "\n";
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

    sbtool.SaveFitResults(min_ChiSq, fParamVal, fParamErr);

    // Plot only for Central Value
    if (sbtool.current_unv == 0){
      std::cout<<"running: setting fit values"<<std::endl;
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
    }


    std::cout << "\n";
    std::cout << " Minimum chi square = " << min_ChiSq<< "\n";
    std::cout << " Estimated vert. distance to min. = " << edm << "\n";
    std::cout << " Number of variable parameters = " << nvpar << "\n";
    std::cout << " Highest number of parameters defined by user = " << nparx << "\n";
    std::cout << " Status of covariance matrix = " << icstat << "\n";

    std::cout << "\n";
    ptMinuit->mnprin(1,min_ChiSq);
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
void FitMinuit_Empty_Region14(Helium_3CryoRegionsSideBandTool sbtool,
   std::string fitName, std::string pdf_label, std::vector<double> &wgt_vector, std::vector<double> &wgt_error)
{
    //cout<<"======================================================================"<<endl;
    //cout<<"Universe = "<<sbtool.current_unv<<endl;
    //cout<<"======================================================================"<<endl;

    TMinuit *ptMinuit = new TMinuit(14);
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
    ptMinuit->SetFCN(calc_ChiSq_Empty_Region14);

    Double_t arglist[15];
    Int_t ierflg = 0;

    arglist[0] = 1;
    ptMinuit->mnexcm("SET ERR", arglist ,1,ierflg);

    // Set starting values and step sizes for parameters
    //      Start from 1.0 and step 0.01
    ptMinuit->mnparm(0, "FitParm_Aluminium_1",        .05, 0.01, .01, 8.0 , ierflg);
    ptMinuit->mnparm(1, "FitParm_Aluminium_2",        .05, 0.01, .01, 8.0 , ierflg);
    ptMinuit->mnparm(2, "FitParm_Aluminium_3",        .05, 0.01, .01, 8.0 , ierflg);
    ptMinuit->mnparm(3, "FitParm_Aluminium_4",        .05, 0.01, .01, 8.0 , ierflg);
    ptMinuit->mnparm(4, "FitParm_Aluminium_5",        .05, 0.01, .01, 8.0 , ierflg);
    ptMinuit->mnparm(5, "FitParm_Aluminium_6",        .05, 0.01, .01, 8.0 , ierflg);
    ptMinuit->mnparm(6, "FitParm_Aluminium_7",        .05, 0.01, .01, 8.0 , ierflg);
    ptMinuit->mnparm(7, "FitParm_Aluminium_8",        .05, 0.01, .01, 8.0 , ierflg);
    ptMinuit->mnparm(8, "FitParm_Aluminium_9",        .05, 0.01, .01, 8.0 , ierflg);
    ptMinuit->mnparm(9, "FitParm_Aluminium_10",        .05, 0.01, .01, 8.0 , ierflg);
    ptMinuit->mnparm(10, "FitParm_Aluminium_11",        .05, 0.01, .01, 8.0 , ierflg);
    ptMinuit->mnparm(11, "FitParm_Aluminium_12",        .05, 0.01, .01, 8.0 , ierflg);
    ptMinuit->mnparm(12, "FitParm_Aluminium_13",        .05, 0.01, .01, 8.0 , ierflg);
    ptMinuit->mnparm(13, "FitParm_Aluminium_14",        .05, 0.01, .01, 8.0 , ierflg);




    // Now ready for minimization step
    arglist[0] =80000;
    arglist[1] = 1.;
    ptMinuit->mnexcm("MIGRAD", arglist ,2,ierflg);

    // Print results
    //std::cout<<"\nPrint results from minuit\n";
    double fParamVal[14];
    double fParamErr[14];
    ptMinuit->GetParameter(0, fParamVal[0], fParamErr[0]);
    ptMinuit->GetParameter(1, fParamVal[1], fParamErr[1]);
    ptMinuit->GetParameter(2, fParamVal[2], fParamErr[2]);
    ptMinuit->GetParameter(3, fParamVal[3], fParamErr[3]);
    ptMinuit->GetParameter(4, fParamVal[4], fParamErr[4]);
    ptMinuit->GetParameter(5, fParamVal[5], fParamErr[5]);
    ptMinuit->GetParameter(6, fParamVal[6], fParamErr[6]);
    ptMinuit->GetParameter(7, fParamVal[7], fParamErr[7]);
    ptMinuit->GetParameter(8, fParamVal[8], fParamErr[8]);
    ptMinuit->GetParameter(9, fParamVal[9], fParamErr[9]);
    ptMinuit->GetParameter(10, fParamVal[10], fParamErr[10]);
    ptMinuit->GetParameter(11, fParamVal[11], fParamErr[11]);
    ptMinuit->GetParameter(12, fParamVal[12], fParamErr[12]);
    ptMinuit->GetParameter(13, fParamVal[13], fParamErr[13]);

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

    sbtool.SaveFitResults(min_ChiSq, fParamVal, fParamErr);

    // Plot only for Central Value
    if (sbtool.current_unv == 0){
      //std::cout<<"running: setting fit values"<<std::endl;
      wgt_vector.push_back(fParamVal[0]);
      wgt_vector.push_back(fParamVal[1]);
      wgt_vector.push_back(fParamVal[2]);
      wgt_vector.push_back(fParamVal[3]);
      wgt_vector.push_back(fParamVal[4]);
      wgt_vector.push_back(fParamVal[5]);
      wgt_vector.push_back(fParamVal[6]);
      wgt_vector.push_back(fParamVal[7]);
      wgt_vector.push_back(fParamVal[8]);
      wgt_vector.push_back(fParamVal[9]);
      wgt_vector.push_back(fParamVal[10]);
      wgt_vector.push_back(fParamVal[11]);
      wgt_vector.push_back(fParamVal[12]);
      wgt_vector.push_back(fParamVal[13]);




      wgt_error.push_back(fParamErr[0]);
      wgt_error.push_back(fParamErr[1]);
      wgt_error.push_back(fParamErr[2]);
      wgt_error.push_back(fParamErr[3]);
      wgt_error.push_back(fParamErr[4]);
      wgt_error.push_back(fParamErr[5]);
      wgt_error.push_back(fParamErr[6]);
      wgt_error.push_back(fParamErr[7]);
      wgt_error.push_back(fParamErr[8]);
      wgt_error.push_back(fParamErr[9]);
      wgt_error.push_back(fParamErr[10]);
      wgt_error.push_back(fParamErr[11]);
      wgt_error.push_back(fParamErr[12]);
      wgt_error.push_back(fParamErr[13]);


        //sbtool.ApplyFitResults();
        //sbtool.Plot( fitName, pdf_label);
        //wgt = fParamVal[0];
        //wgt_error = fParamErr[0];
    }


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
void FitMinuit_Empty_Region14_LOG(Helium_3CryoRegionsSideBandTool sbtool,
   std::string fitName, std::string pdf_label, std::vector<double> &wgt_vector, std::vector<double> &wgt_error)
{
    //cout<<"======================================================================"<<endl;
    //cout<<"Universe = "<<sbtool.current_unv<<endl;
    //cout<<"======================================================================"<<endl;

    TMinuit *ptMinuit = new TMinuit(14);
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
    ptMinuit->SetFCN(calc_ChiSq_Empty_Region14_LOG);

    Double_t arglist[15];
    Int_t ierflg = 0;

    arglist[0] = 1;
    ptMinuit->mnexcm("SET ERR", arglist ,1,ierflg);

    // Set starting values and step sizes for parameters
    //      Start from 1.0 and step 0.01
    ptMinuit->mnparm(0, "FitParm_Aluminium_1",        .05, 0.01, .01, 8.0 , ierflg);
    ptMinuit->mnparm(1, "FitParm_Aluminium_2",        .05, 0.01, .01, 8.0 , ierflg);
    ptMinuit->mnparm(2, "FitParm_Aluminium_3",        .05, 0.01, .01, 8.0 , ierflg);
    ptMinuit->mnparm(3, "FitParm_Aluminium_4",        .05, 0.01, .01, 8.0 , ierflg);
    ptMinuit->mnparm(4, "FitParm_Aluminium_5",        .05, 0.01, .01, 8.0 , ierflg);
    ptMinuit->mnparm(5, "FitParm_Aluminium_6",        .05, 0.01, .01, 8.0 , ierflg);
    ptMinuit->mnparm(6, "FitParm_Aluminium_7",        .05, 0.01, .01, 8.0 , ierflg);
    ptMinuit->mnparm(7, "FitParm_Aluminium_8",        .05, 0.01, .01, 8.0 , ierflg);
    ptMinuit->mnparm(8, "FitParm_Aluminium_9",        .05, 0.01, .01, 8.0 , ierflg);
    ptMinuit->mnparm(9, "FitParm_Aluminium_10",        .05, 0.01, .01, 8.0 , ierflg);
    ptMinuit->mnparm(10, "FitParm_Aluminium_11",        .05, 0.01, .01, 8.0 , ierflg);
    ptMinuit->mnparm(11, "FitParm_Aluminium_12",        .05, 0.01, .01, 8.0 , ierflg);
    ptMinuit->mnparm(12, "FitParm_Aluminium_13",        .05, 0.01, .01, 8.0 , ierflg);
    ptMinuit->mnparm(13, "FitParm_Aluminium_14",        .05, 0.01, .01, 8.0 , ierflg);




    // Now ready for minimization step
    arglist[0] =85000;
    arglist[1] = 1.;
    ptMinuit->mnexcm("MIGRAD", arglist ,2,ierflg);

    // Print results
    //std::cout<<"\nPrint results from minuit\n";
    double fParamVal[14];
    double fParamErr[14];
    ptMinuit->GetParameter(0, fParamVal[0], fParamErr[0]);
    ptMinuit->GetParameter(1, fParamVal[1], fParamErr[1]);
    ptMinuit->GetParameter(2, fParamVal[2], fParamErr[2]);
    ptMinuit->GetParameter(3, fParamVal[3], fParamErr[3]);
    ptMinuit->GetParameter(4, fParamVal[4], fParamErr[4]);
    ptMinuit->GetParameter(5, fParamVal[5], fParamErr[5]);
    ptMinuit->GetParameter(6, fParamVal[6], fParamErr[6]);
    ptMinuit->GetParameter(7, fParamVal[7], fParamErr[7]);
    ptMinuit->GetParameter(8, fParamVal[8], fParamErr[8]);
    ptMinuit->GetParameter(9, fParamVal[9], fParamErr[9]);
    ptMinuit->GetParameter(10, fParamVal[10], fParamErr[10]);
    ptMinuit->GetParameter(11, fParamVal[11], fParamErr[11]);
    ptMinuit->GetParameter(12, fParamVal[12], fParamErr[12]);
    ptMinuit->GetParameter(13, fParamVal[13], fParamErr[13]);

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

    sbtool.SaveFitResults(min_ChiSq, fParamVal, fParamErr);

    // Plot only for Central Value
    if (sbtool.current_unv == 0){
      //std::cout<<"running: setting fit values"<<std::endl;
      wgt_vector.push_back(fParamVal[0]);
      wgt_vector.push_back(fParamVal[1]);
      wgt_vector.push_back(fParamVal[2]);
      wgt_vector.push_back(fParamVal[3]);
      wgt_vector.push_back(fParamVal[4]);
      wgt_vector.push_back(fParamVal[5]);
      wgt_vector.push_back(fParamVal[6]);
      wgt_vector.push_back(fParamVal[7]);
      wgt_vector.push_back(fParamVal[8]);
      wgt_vector.push_back(fParamVal[9]);
      wgt_vector.push_back(fParamVal[10]);
      wgt_vector.push_back(fParamVal[11]);
      wgt_vector.push_back(fParamVal[12]);
      wgt_vector.push_back(fParamVal[13]);




      wgt_error.push_back(fParamErr[0]);
      wgt_error.push_back(fParamErr[1]);
      wgt_error.push_back(fParamErr[2]);
      wgt_error.push_back(fParamErr[3]);
      wgt_error.push_back(fParamErr[4]);
      wgt_error.push_back(fParamErr[5]);
      wgt_error.push_back(fParamErr[6]);
      wgt_error.push_back(fParamErr[7]);
      wgt_error.push_back(fParamErr[8]);
      wgt_error.push_back(fParamErr[9]);
      wgt_error.push_back(fParamErr[10]);
      wgt_error.push_back(fParamErr[11]);
      wgt_error.push_back(fParamErr[12]);
      wgt_error.push_back(fParamErr[13]);


        //sbtool.ApplyFitResults();
        //sbtool.Plot( fitName, pdf_label);
        //wgt = fParamVal[0];
        //wgt_error = fParamErr[0];
    }


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
void FitSideBands(Helium_3CryoRegionsSideBandTool sbtool, int FitFullorEmpty,
  std::string fitName, std::string file_name, std::string pdf_label,
  std::vector<double> &wgt_vector, std::vector<double> &wgt_error_vector, double &error_onFit)
{
    //cout<<"======================================================================"<<endl;
    //cout<<"Fitting Side Bands..."<<endl;
    //cout<<"======================================================================"<<endl;
    //std::cout<< "Name of sideBand = "<< sbtool.GetName()<<std::endl;
    //std::cout << "sbtool.current_unv = " << sbtool.current_unv<<std::endl;
    //std::cout << "sbtool.N_Universes = " << sbtool.N_Universes<<std::endl;

    while(sbtool.current_unv < sbtool.N_Universes){
      //std::cout<<"Current Unv"<<sbtool.current_unv<<std::endl;
      if(FitFullorEmpty==0){

      //  cout<<"======================================================================"<<endl;
      //  cout<<"Fitting TO EMPTY"<<endl;
      //  cout<<"======================================================================"<<endl;

        FitMinuit_Empty(sbtool, fitName, pdf_label, wgt_vector, wgt_error_vector );

        //FitMinuit_Empty_RZ(sbtool, fitName, pdf_label, wgt_vector, wgt_error_vector );

      }
      else if(FitFullorEmpty==1){
        cout<<"======================================================================"<<endl;
        cout<<"Fitting TO Full"<<endl;
        cout<<"======================================================================"<<endl;

        FitMinuit_Full(sbtool, fitName, pdf_label, wgt_vector, wgt_error_vector );
      }

      else if(FitFullorEmpty==2){
        cout<<"======================================================================"<<endl;
        cout<<"Fitting TO Full - Empty"<<endl;
        cout<<"======================================================================"<<endl;

        FitMinuit_Full_Empty(sbtool, fitName, pdf_label, wgt_vector, wgt_error_vector );
      }

      else if(FitFullorEmpty==3){
        cout<<"======================================================================"<<endl;
        cout<<"Fitting TO Full and Empty with Al and He wgts"<<endl;
        cout<<"======================================================================"<<endl;

        FitMinuit_Full_Empty_Al_He_Combinedfit(sbtool, fitName, pdf_label, wgt_vector, wgt_error_vector );
      }

      else if(FitFullorEmpty==4){
        cout<<"======================================================================"<<endl;
        cout<<"Fitting TO Full and Empty with Al and He wgts For Regions of X"<<endl;
        cout<<"======================================================================"<<endl;

        FitMinuit_Empty_regionX(sbtool, fitName, pdf_label, wgt_vector, wgt_error_vector );
      }

      else if(FitFullorEmpty==5){


        cout<<"======================================================================"<<endl;
        cout<<"Fitting TO Full and Empty with Al and He wgts For Regions of X Only looking at Vertex Z"<<endl;
        cout<<"======================================================================"<<endl;

        FitMinuit_Empty_regionX_Vertex_Z_Only(sbtool, fitName, pdf_label, wgt_vector, wgt_error_vector);

      }

      else if(FitFullorEmpty==6){
        cout<<"======================================================================"<<endl;
        cout<<"Fitting TO Full and Empty with Al and He wgts For Regions of X"<<endl;
        cout<<"======================================================================"<<endl;

        FitMinuit_Empty_regionXZ(sbtool, fitName, pdf_label, wgt_vector, wgt_error_vector );
      }
      else if (FitFullorEmpty==7){

        FitMinuit_EmptyLogchi2(sbtool, fitName, pdf_label, wgt_vector, wgt_error_vector , error_onFit  );

      }

      else if(FitFullorEmpty==8){
        FitMinuit_Empty_RZ(sbtool, fitName, pdf_label, wgt_vector, wgt_error_vector );
      }

      else if(FitFullorEmpty==9){
        FitMinuit_Empty_Region14(sbtool, fitName, pdf_label, wgt_vector, wgt_error_vector );
      }

      else if(FitFullorEmpty==10){
        FitMinuit_Empty_Region14_LOG(sbtool, fitName, pdf_label, wgt_vector, wgt_error_vector );
      }






        sbtool.current_unv++;
    }

    //sbtool.WriteStatistics();
    //sbtool.WriteFitResults(file_name);

}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
