#include "Helium_SideBandTool.h"
using namespace std;

Helium_SideBandTool sbtool_global;
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
double calc_ChiSq_SideBand(HeliumSideBand &sb, Double_t *par, int unv = 0,
                           bool isPartial = false, int min_bin = 1,
                           int max_bin = 1) {
  std::cout << "inside:calc_ChiSq_SideBand" << std::endl;
  if (!isPartial) {
    min_bin = 1;
    max_bin = sb.MnvH1D_data->GetNbinsX();
  }

  if (min_bin == max_bin) {
    cout << "Wrong Range for Fit" << endl;
    exit(EXIT_FAILURE);
  }

  double ChiSq = 0.0;

  for (int i = 1; i <= max_bin; ++i) {
    double nData = sb.data_all_universes[unv]->GetBinContent(i);
    if (nData == 0) continue;

    // Do not use Signal and Other in Fit  had * sbtool.POT_ratio;planning to
    // scale beforehand
    double nHelium = sb.Helium_all_universes[unv]->GetBinContent(i);
    double nCarbon = sb.Carbon_all_universes[unv]->GetBinContent(i);
    double nIron = sb.Iron_all_universes[unv]->GetBinContent(i);
    double nLead = sb.Lead_all_universes[unv]->GetBinContent(i);
    double nOther = sb.Other_all_universes[unv]->GetBinContent(i);

    // par[] will be the weights associated with that background
    std::cout << "scaling par[0] = " << par[0] << std::endl;
    double nAluminium =
        par[0] * sb.Aluminium_all_universes[unv]->GetBinContent(i);
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    std::cout << "nData " << nData << std::endl;
    std::cout << "nHelium " << nHelium << std::endl;
    std::cout << "nCarbon " << nCarbon << std::endl;
    std::cout << "nIron " << nIron << std::endl;
    std::cout << "nLead " << nLead << std::endl;
    std::cout << "nOther " << nOther << std::endl;
    std::cout << "nAluminium " << nAluminium << std::endl;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

    double nTotalMC = nHelium + nCarbon + nIron + nLead + nOther + nAluminium;
    std::cout << "nTotalMC " << nTotalMC << std::endl;

    double delta = std::pow((nData - nTotalMC), 2) / nData;
    ChiSq += delta;
  }

  return ChiSq;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
double calc_ChiSq_SideBand_CV(HeliumSideBand &sb, Double_t *par, int unv = 0,
                              bool isPartial = false, int min_bin = 1,
                              int max_bin = 1) {
  std::cout << "inside:calc_ChiSq_SideBand" << std::endl;
  if (!isPartial) {
    min_bin = 1;
    max_bin = sb.MnvH1D_data->GetNbinsX();
  }

  if (min_bin == max_bin) {
    cout << "Wrong Range for Fit" << endl;
    exit(EXIT_FAILURE);
  }

  double ChiSq = 0.0;

  for (int i = 1; i <= sb.MnvH1D_data->GetNbinsX(); ++i) {
    // Get N(Events) in Single Bin
    double err = sb.MnvH1D_data->GetBinError(i);
    double nData = sb.MnvH1D_data->GetBinContent(i);
    if (nData == 0) continue;
    double nHelium = sb.MnvH1D_Helium[0]->GetBinContent(i);
    double nCarbon = sb.MnvH1D_Carbon[0]->GetBinContent(i);
    double nLead = sb.MnvH1D_Lead[0]->GetBinContent(i);
    double nIron = sb.MnvH1D_Iron[0]->GetBinContent(i);
    double nOther = sb.MnvH1D_Other[0]->GetBinContent(i);
    double nAluminium = par[0] * sb.MnvH1D_Aluminium[0]->GetBinContent(i);

    // Add All MC and scale them
    double nMC_total =
        (nHelium + nAluminium + nCarbon + nLead + nIron + nOther);

    double delta = pow((nData - nMC_total), 2) / pow(err, 2);
    ChiSq += delta;
  }
  return ChiSq;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void SetHeliumSideBandTool(Helium_SideBandTool sbtool_input) {
  sbtool_global = sbtool_input;
  std::cout << "decleared Global Helium_SideBandTool for fitting " << std::endl;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void calc_ChiSq(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par,
                Int_t iflag) {
  // Silence Unused Variable Warning
  (void)npar;
  (void)gin;
  (void)iflag;

  double ChiSq = 0;

  // Calculate ChiSq for Empty for ALL Bins
  // ChiSq += calc_ChiSq_SideBand(sbtool_global.Helium_Empty, par,
  // sbtool_global.current_unv);
  ChiSq += calc_ChiSq_SideBand_CV(sbtool_global.Helium_Empty, par);

  f = ChiSq;
  return;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void FitMinuit(Helium_SideBandTool sbtool, std::string fitName,
               std::string pdf_label, double &wgt, double &wgt_error) {
  cout << "===================================================================="
          "=="
       << endl;
  cout << "Universe = " << sbtool.current_unv << endl;
  cout << "===================================================================="
          "=="
       << endl;

  TMinuit *ptMinuit =
      new TMinuit(1);  // initialize TMinuit with a maximum of 3 params
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
  ptMinuit->SetFCN(calc_ChiSq);

  Double_t arglist[10];
  Int_t ierflg = 0;

  arglist[0] = 1;
  ptMinuit->mnexcm("SET ERR", arglist, 1, ierflg);

  // Set starting values and step sizes for parameters
  //      Start from 1.0 and step 0.01
  ptMinuit->mnparm(0, "FitParm_Aluminium", 1.0, 0.01, 1.0, 2.0, ierflg);

  // Now ready for minimization step
  arglist[0] = 500;
  arglist[1] = 1.;
  ptMinuit->mnexcm("MIGRAD", arglist, 2, ierflg);

  // Print results
  std::cout << "\nPrint results from minuit\n";
  double fParamVal[3];
  double fParamErr[3];
  ptMinuit->GetParameter(0, fParamVal[0], fParamErr[0]);

  std::cout << "MnvH1D_Aluminium = " << fParamVal[0] << "\n";
  // if you want to access to these parameters, use:
  Double_t min_ChiSq, edm, errdef;
  Int_t nvpar, nparx, icstat;
  ptMinuit->mnstat(min_ChiSq, edm, errdef, nvpar, nparx, icstat);
  // void mnstat(Double_t &fmin, Double_t &fedm, Double_t &errdef, Int_t &npari,
  // Int_t &nparx, Int_t &istat)
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
  if (sbtool.current_unv == 0) {
    std::cout << "running: setting fit values" << std::endl;
    // sbtool.wgt_Aluminium.push_back(fParamVal[0]);
    // sbtool.err_Aluminium.push_back(fParamErr[0]);
    // sbtool.ApplyFitResults();
    // sbtool.Plot( fitName, pdf_label);
    wgt = fParamVal[0];
    wgt_error = fParamErr[0];
  }

  std::cout << "\n";
  std::cout << " Minimum chi square = " << min_ChiSq << "\n";
  std::cout << " Estimated vert. distance to min. = " << edm << "\n";
  std::cout << " Number of variable parameters = " << nvpar << "\n";
  std::cout << " Highest number of parameters defined by user = " << nparx
            << "\n";
  std::cout << " Status of covariance matrix = " << icstat << "\n";

  std::cout << "\n";
  ptMinuit->mnprin(1, min_ChiSq);
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
void FitSideBands(Helium_SideBandTool sbtool, std::string fitName,
                  std::string file_name, std::string pdf_label, double &wgt,
                  double &wgt_error) {
  cout << "===================================================================="
          "=="
       << endl;
  cout << "Fitting Side Bands..." << endl;
  cout << "===================================================================="
          "=="
       << endl;
  std::cout << "Name of sideBand = " << sbtool.GetName() << std::endl;
  std::cout << "sbtool.current_unv = " << sbtool.current_unv << std::endl;
  std::cout << "sbtool.N_Universes = " << sbtool.N_Universes << std::endl;

  while (sbtool.current_unv < sbtool.N_Universes) {
    std::cout << "Current Unv" << sbtool.current_unv << std::endl;
    FitMinuit(sbtool, fitName, pdf_label, wgt, wgt_error);
    sbtool.current_unv++;
  }

  sbtool.WriteStatistics();
  sbtool.WriteFitResults(file_name);
}
