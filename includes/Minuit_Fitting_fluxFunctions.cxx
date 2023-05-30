
#include "TH2D.h"
#include "TF2.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TRandom3.h"
#include "TVirtualFitter.h"
#include "TList.h"

#include "TMinuit.h"
#include "TFitter.h"
#include "TFractionFitter.h"

#include "PlotUtils/MnvApplication.h"
#include <PlotUtils/MnvH1D.h>
#include <PlotUtils/MnvH2D.h>
#include <PlotUtils/MnvPlotter.h>
#include <MinervaUnfold/MnvUnfold.h>
#include <PlotUtils/MnvVertErrorBand.h>
#include <PlotUtils/MnvLatErrorBand.h>
#include <PlotUtils/MnvNormalization.h>
#include <PlotUtils/FluxReweighter.h>
#include <PlotUtils/POTCounter.h>
#include <vector>

#include "HeliumPlotUtils.h"
#include "CryoTankUtils.h"
#include "HeliumDefaults.h"
#include "HeliumUtils.h"
#include "Helium2DUtils.h"
#include "Helium2DPlotUtils.h"

TH2D *h1_Gobal_flux = nullptr;
TH2D *h2_Gobal_flux = nullptr;

TH1D *h_Gobal_flux_Tracker = nullptr;
TH1D *h_Gobal_flux_Helium = nullptr;
TH1D *h_Gobal_flux_Target = nullptr;
TH1D *h_Gobal_flux_Ratio = nullptr;
TH2D *h_Gobal_flux_Tracker_Daisy = nullptr;

Int_t npfits_flux;
double reg_lambda;
std::vector<double> y_bins;
std::vector<double> x_bins;
std::vector<double> stats_vector;
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::vector<double> get_axis_bins(TH2D *hist, bool is_x_axis) {
  std::vector<double> axis_bins;
  if (hist) {
    TAxis *axis;
    if (is_x_axis) {
      axis = hist->GetXaxis();
    } else {
      axis = hist->GetYaxis();
    }
    const int num_bins = axis->GetNbins();
    for (int i = 1; i <= num_bins; ++i) {
      axis_bins.push_back(axis->GetBinLowEdge(i));
    }
    axis_bins.push_back(axis->GetBinUpEdge(num_bins));
  }
  return axis_bins;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
std::vector<double> getYProjectionStats(TH2D *hist) {
  std::vector<double> stats_vector;
  if (hist) {
    TH1D *stats_hist = hist->ProjectionY();
    const int num_bins_y = hist->GetNbinsY();
    const double total_stats = stats_hist->Integral();

    for (int b = 1; b <= num_bins_y; ++b) {
      double relative_stats = stats_hist->GetBinContent(b) / total_stats;
      stats_vector.push_back(relative_stats);
    }
    delete stats_hist;
  }
  return stats_vector;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
double Gaussian2D_miniut(double x, double y, double A, double Xo, double sigmaX,
                         double Yo, double sigmaY) {
  Double_t r1 = Double_t((x - Xo) / sigmaX);
  Double_t r2 = Double_t((y - Yo) / sigmaY);
  return A * TMath::Exp(-0.5 * (r1 * r1 + r2 * r2));
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void Set_Lambda_Penity(double input) { reg_lambda = input; }
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void Set_h1_Gobal_flux(TH2D *input) { h1_Gobal_flux = input; }
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void Set_h2_Gobal_flux(TH2D *input) { h2_Gobal_flux = input; }
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void Set_Tracker_Gobal_flux(TH1D *input) { h_Gobal_flux_Tracker = input; }
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void Set_Helium_Gobal_flux(TH1D *input) { h_Gobal_flux_Helium = input; }
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void Set_Target_Gobal_flux(TH1D *input) { h_Gobal_flux_Target = input; }
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void Set_Tracker_Daisy_Gobal_flux(TH2D *input) {
  h_Gobal_flux_Tracker_Daisy = input;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void Set_Gobal_Ratio(TH1D *input) { h_Gobal_flux_Ratio = input; }
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void Set_Daisy_fit(TH1D *input_helium_flux, TH1D *input_tracker_flux,
                   TH2D *Daisy_slices_flux) {
  Set_Tracker_Gobal_flux(input_tracker_flux);
  Set_Helium_Gobal_flux(input_helium_flux);
  Set_Tracker_Daisy_Gobal_flux(Daisy_slices_flux);

  TH1D *h_Gobal_flux_Target_clone = Daisy_slices_flux->ProjectionX();

  TH1D *h_ratio = (TH1D *)input_helium_flux->Clone("h_ratio");
  h_ratio->Divide(h_ratio, input_tracker_flux);
  Set_Gobal_Ratio(h_ratio);

  h_Gobal_flux_Target_clone->Multiply(h_Gobal_flux_Target_clone, h_ratio);

  Set_Target_Gobal_flux(h_Gobal_flux_Target_clone);
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void setYbins(TH2D *h_input) { y_bins = get_axis_bins(h_input, false); }
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void setXbins(TH2D *h_input) { x_bins = get_axis_bins(h_input, true); }
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void SetBins_usingflux_Tracker_Daisy() {
  setYbins(h_Gobal_flux_Tracker_Daisy);
  setXbins(h_Gobal_flux_Tracker_Daisy);
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void SetStatvector(TH2D *hist) { stats_vector = getYProjectionStats(hist); }
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void SetStatvector_usingflux_Tracker_Daisy() {
  SetStatvector(h_Gobal_flux_Tracker_Daisy);
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void clearStatvector() { stats_vector.clear(); }
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void calc_two2D_Gobal_ChiSq_2DGaussian2D(Int_t &npar, Double_t *gin,
                                         Double_t &f, Double_t *par,
                                         Int_t iflag) {
  // Silence Unused Variable Warning
  (void)npar;
  (void)gin;
  (void)iflag;

  if (h1_Gobal_flux == nullptr) {
    std::cout << "Hist was not correctly assigned" << std::endl;
    assert(false);
  }
  if (h2_Gobal_flux == nullptr) {
    std::cout << "Hist was not correctly assigned" << std::endl;
    assert(false);
  }

  TAxis *xaxis1 = h1_Gobal_flux->GetXaxis();
  TAxis *yaxis1 = h1_Gobal_flux->GetYaxis();

  int nbinX1 = h1_Gobal_flux->GetNbinsX();
  int nbinY1 = h1_Gobal_flux->GetNbinsY();

  TAxis *xaxis2 = h2_Gobal_flux->GetXaxis();
  TAxis *yaxis2 = h2_Gobal_flux->GetYaxis();

  int nbinX2 = h2_Gobal_flux->GetNbinsX();
  int nbinY2 = h2_Gobal_flux->GetNbinsY();

  double chi2 = 0;
  double x[2];
  double tmp;
  double Bin = 99;
  double error = 99;
  double Model = 99;
  npfits_flux = 0;

  for (int ix = 1; ix <= nbinX1; ++ix) {
    x[0] = xaxis1->GetBinCenter(ix);
    for (int iy = 1; iy <= nbinY1; ++iy) {
      // error = h1_Gobal_flux->GetBinError(ix,iy);
      // std::cout << "error = "<< error << std::endl;

      x[1] = yaxis1->GetBinCenter(iy);
      Bin = h1_Gobal_flux->GetBinContent(ix, iy);
      error = h1_Gobal_flux->GetBinError(ix, iy);
      Model =
          Gaussian2D_miniut(x[0], x[1], par[0], par[1] /*this is the joint*/,
                            par[2], par[3], par[4]);

      // std::cout<< "Bin : "<< Bin<<std::endl;
      // std::cout<< "error : "<< error<<std::endl;
      // std::cout<< "Model : "<< Model<<std::endl;
      if (error > 0) {
        tmp = (Bin - Model) / error;
        chi2 += tmp * tmp;
        npfits_flux++;
      }
    }
  }

  for (int ix = 1; ix <= nbinX2; ++ix) {
    x[0] = xaxis2->GetBinCenter(ix);
    for (int iy = 1; iy <= nbinY2; ++iy) {
      // error = h1_Gobal->GetBinError(ix,iy);
      // std::cout << "error = "<< error << std::endl;

      x[1] = yaxis2->GetBinCenter(iy);
      Bin = h2_Gobal_flux->GetBinContent(ix, iy);
      error = h2_Gobal_flux->GetBinError(ix, iy);
      Model =
          Gaussian2D_miniut(x[0], x[1], par[5], par[1] /*this is the joint*/,
                            par[6], par[7], par[8]);

      // std::cout<< "Bin : "<< Bin<<std::endl;
      // std::cout<< "error : "<< error<<std::endl;
      // std::cout<< "Model : "<< Model<<std::endl;
      if (error > 0) {
        tmp = (Bin - Model) / error;
        chi2 += tmp * tmp;
        npfits_flux++;
      }
    }
  }

  f = chi2;
  return;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void calc_two2D_Gobal_ChiSq_2DGaussian2D_LOG(Int_t &npar, Double_t *gin,
                                             Double_t &f, Double_t *par,
                                             Int_t iflag) {
  // Silence Unused Variable Warning
  (void)npar;
  (void)gin;
  (void)iflag;

  if (h1_Gobal_flux == nullptr) {
    std::cout << "Hist was not correctly assigned" << std::endl;
    assert(false);
  }
  if (h2_Gobal_flux == nullptr) {
    std::cout << "Hist was not correctly assigned" << std::endl;
    assert(false);
  }

  TAxis *xaxis1 = h1_Gobal_flux->GetXaxis();
  TAxis *yaxis1 = h1_Gobal_flux->GetYaxis();

  int nbinX1 = h1_Gobal_flux->GetNbinsX();
  int nbinY1 = h1_Gobal_flux->GetNbinsY();

  TAxis *xaxis2 = h2_Gobal_flux->GetXaxis();
  TAxis *yaxis2 = h2_Gobal_flux->GetYaxis();

  int nbinX2 = h2_Gobal_flux->GetNbinsX();
  int nbinY2 = h2_Gobal_flux->GetNbinsY();

  double chi2 = 0;
  double x[2];
  double tmp;
  double Bin = 99;
  double error = 99;
  double Model = 99;
  npfits_flux = 0;

  for (int ix = 1; ix <= nbinX1; ++ix) {
    x[0] = xaxis1->GetBinCenter(ix);
    for (int iy = 1; iy <= nbinY1; ++iy) {
      // error = h1_Gobal_flux->GetBinError(ix,iy);
      // std::cout << "error = "<< error << std::endl;

      x[1] = yaxis1->GetBinCenter(iy);
      Bin = h1_Gobal_flux->GetBinContent(ix, iy);
      error = h1_Gobal_flux->GetBinError(ix, iy);
      Model =
          Gaussian2D_miniut(x[0], x[1], par[0], par[1] /*this is the joint*/,
                            par[2], par[3], par[4]);

      // std::cout<< "Bin : "<< Bin<<std::endl;
      // std::cout<< "error : "<< error<<std::endl;
      // std::cout<< "Model : "<< Model<<std::endl;
      if (error > 0) {
        tmp = (Bin - Model) / error;
        chi2 += tmp * tmp;
        npfits_flux++;
      }
    }
  }

  for (int ix = 1; ix <= nbinX2; ++ix) {
    x[0] = xaxis2->GetBinCenter(ix);
    for (int iy = 1; iy <= nbinY2; ++iy) {
      // error = h1_Gobal->GetBinError(ix,iy);
      // std::cout << "error = "<< error << std::endl;

      x[1] = yaxis2->GetBinCenter(iy);
      Bin = h2_Gobal_flux->GetBinContent(ix, iy);
      Model =
          Gaussian2D_miniut(x[0], x[1], par[5], par[1] /*this is the joint*/,
                            par[6], par[7], par[8]);

      // std::cout<< "Bin : "<< Bin<<std::endl;
      // std::cout<< "error : "<< error<<std::endl;
      // std::cout<< "Model : "<< Model<<std::endl;
      if (Model > 0) {
        double c = Bin * log(Model);
        double delta = 2 * (Model - c);
        chi2 += delta;
        npfits_flux++;
      }
    }
  }

  f = chi2;
  return;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void FitMinuit_h1_Gobal__2DGaussian2D(std::vector<double> &FitParas,
                                      std::vector<double> &FitParas_error,
                                      double &chi_2,
                                      std::vector<TGraph *> &outputTGraphs) {
  if (h1_Gobal_flux == nullptr) {
    std::cout << "h1_Gobal not set Fit would do nothign " << std::endl;
    assert(false);
  }

  TMinuit *ptMinuit = new TMinuit(9);

  ptMinuit->SetPrintLevel(2);
  // set the user function that calculates chi_square (the value to minimize)
  ptMinuit->SetFCN(calc_two2D_Gobal_ChiSq_2DGaussian2D_LOG);
  // calc_two2D_Gobal_ChiSq_2DGaussian2D

  Double_t arglist[10];
  Int_t ierflg = 0;

  arglist[0] = 1;
  ptMinuit->mnexcm("SET ERR", arglist, 1, ierflg);
  // Set starting values and step sizes for parameters
  //      Start from 1.0 and step 0.01
  ptMinuit->mnparm(0, "AGaussian1", .1, .1, 0, 5, ierflg);
  ptMinuit->mnparm(1, "AGaussian1Xo", 5, .1, 5, 7, ierflg);
  ptMinuit->mnparm(2, "AGaussian1XoSigma", 1, .1, 0, 3, ierflg);
  ptMinuit->mnparm(3, "AGaussian1Yo", 1, .1, 1, 30, ierflg);
  ptMinuit->mnparm(4, "AGaussian1YoSigma", 1, .1, 0, 200, ierflg);

  ptMinuit->mnparm(5, "AGaussian2", .1, .1, 0, 5, ierflg);
  ptMinuit->mnparm(6, "AGaussian2XoSigma", 1, .1, 0, 3, ierflg);
  ptMinuit->mnparm(7, "AGaussian2Yo", 1, .1, 1, 30, ierflg);
  ptMinuit->mnparm(8, "AGaussian2YoSigma", 1, .1, 0, 200, ierflg);
  //	ptMinuit->mnparm(par , "name ",   UK, WK, A, B , ierflg);
  // UK starting value
  // WK starting step size or uncertainty
  // A, B lower and upper physical parameter limits and sets up (updates) the
  // parameter lists. Output:
  // IERFLG=0 if no problems
  //>0 if MNPARM unable to implement definition

  arglist[0] = 90000;
  arglist[1] = .1;

  ptMinuit->mnexcm("MINImize", arglist, 2, ierflg);  // SEE, MINImize , MIGRAD"

  // Print results
  // std::cout<<"\nPrint results from minuit\n";
  double fParamVal[9];
  double fParamErr[9];
  ptMinuit->GetParameter(0, fParamVal[0], fParamErr[0]);
  ptMinuit->GetParameter(1, fParamVal[1], fParamErr[1]);
  ptMinuit->GetParameter(2, fParamVal[2], fParamErr[2]);
  ptMinuit->GetParameter(3, fParamVal[3], fParamErr[3]);
  ptMinuit->GetParameter(4, fParamVal[4], fParamErr[4]);
  ptMinuit->GetParameter(5, fParamVal[5], fParamErr[5]);
  ptMinuit->GetParameter(6, fParamVal[6], fParamErr[6]);
  ptMinuit->GetParameter(7, fParamVal[7], fParamErr[7]);
  ptMinuit->GetParameter(8, fParamVal[8], fParamErr[8]);

  if (ierflg = !0) {
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    std::cout << "Did not FIT " << std::endl;
    std::cout << "~~~~~~~ierflg = " << ierflg << std::endl;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
  }

  Double_t min_ChiSq, edm, errdef;
  Int_t nvpar, nparx, icstat;
  ptMinuit->mnstat(min_ChiSq, edm, errdef, nvpar, nparx, icstat);

  std::cout << "inside: min_ChiSq =" << min_ChiSq << std::endl;
  std::cout << "inside:  edm = " << edm << std::endl;
  std::cout << "inside:  errdef = " << errdef << std::endl;
  std::cout << "inside:  nvpar = " << nvpar << std::endl;
  std::cout << "inside:  nparx = " << nparx << std::endl;
  std::cout << "inside:  icstat = " << icstat << std::endl;

  chi_2 = min_ChiSq;

  FitParas.push_back(fParamVal[0]);
  FitParas.push_back(fParamVal[1]);
  FitParas.push_back(fParamVal[2]);
  FitParas.push_back(fParamVal[3]);
  FitParas.push_back(fParamVal[4]);
  FitParas.push_back(fParamVal[5]);
  FitParas.push_back(fParamVal[6]);
  FitParas.push_back(fParamVal[7]);
  FitParas.push_back(fParamVal[8]);

  FitParas_error.push_back(fParamErr[0]);
  FitParas_error.push_back(fParamErr[1]);
  FitParas_error.push_back(fParamErr[2]);
  FitParas_error.push_back(fParamErr[3]);
  FitParas_error.push_back(fParamErr[4]);
  FitParas_error.push_back(fParamErr[5]);
  FitParas_error.push_back(fParamErr[6]);
  FitParas_error.push_back(fParamErr[7]);
  FitParas_error.push_back(fParamErr[8]);

  // gMinuit->SetErrorDef(1);
  // TGraph *gr1 = (TGraph*)gMinuit->Contour(60,3,7);
  // TGraph *gr2 = (TGraph*)gMinuit->Contour(60,1,3);
  // TGraph *gr3 = (TGraph*)gMinuit->Contour(60,1,7);

  // gMinuit->SetErrorDef(4);
  // TGraph *gr4 = (TGraph*)gMinuit->Contour(60,3,7);
  // TGraph *gr5 = (TGraph*)gMinuit->Contour(60,1,3);
  // TGraph *gr6 = (TGraph*)gMinuit->Contour(60,1,7);

  // outputTGraphs.push_back(gr1);
  // outputTGraphs.push_back(gr2);
  // outputTGraphs.push_back(gr3);
  // outputTGraphs.push_back(gr4);
  // outputTGraphs.push_back(gr5);
  // outputTGraphs.push_back(gr6);

  delete ptMinuit;

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
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void Fit2Dhist(TH2D *HistA, TH2D *HistB, std::vector<double> &para_vector,
               std::vector<double> &wgt_error_vector, double &chi2,
               std::vector<TGraph *> &outputTGraphs) {
  std::cout << "Seting Hist to Gobal" << std::endl;
  Set_h1_Gobal_flux(HistA);
  Set_h2_Gobal_flux(HistB);
  std::cout << "Trying to Fit" << std::endl;
  FitMinuit_h1_Gobal__2DGaussian2D(para_vector, wgt_error_vector, chi2,
                                   outputTGraphs);
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void Fit2DPatals_fluxratioAttachhist(TH2D *HistPatalFlux, TH1D *HistTrackerFlux,
                                     TH1D *HistHeliumFlux) {
  Set_Daisy_fit(HistHeliumFlux, HistTrackerFlux, HistPatalFlux);
  SetBins_usingflux_Tracker_Daisy();
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void Daisyfit_function(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par,
                       Int_t iflag) {
  double chi2 = 0;

  int nbinsx = h_Gobal_flux_Tracker_Daisy->GetNbinsX();
  int nbinsy = h_Gobal_flux_Tracker_Daisy->GetNbinsY();

  for (int binx = 1; binx <= nbinsx; ++binx) {
    // int bx = x_bins[x];
    double target = h_Gobal_flux_Target->GetBinContent(binx);
    double total_content = 0;
    double total_error = pow(h_Gobal_flux_Target->GetBinError(binx), 2);

    for (int biny = 1; biny <= nbinsy; ++biny) {
      // int by = y_bins[y];
      int global_bin = h_Gobal_flux_Tracker_Daisy->GetBin(binx, biny);
      double current_content =
          h_Gobal_flux_Tracker_Daisy->GetBinContent(global_bin);
      double current_error =
          h_Gobal_flux_Tracker_Daisy->GetBinError(global_bin);
      double p = par[biny - 1];
      total_content += current_content * p;
      total_error += pow(current_error, 2) * p;
    }

    double chi2_bin = 0;
    if (total_error > 0) {
      chi2_bin = pow(target - total_content, 2) / total_error;
    } else {
      assert(abs(total_content) + abs(target) == 0);
    }

    chi2 += chi2_bin;
  }

  double regularization = 0;
  for (int b = 0; b < stats_vector.size(); ++b) {
    double relative_stats = stats_vector[b];
    double p = par[b];
    double foo = relative_stats * pow(p - 1, 2);
    regularization += foo * 1000;
  }

  double output = chi2 + reg_lambda * regularization;
  f = output;
}

void FitMinuit_h1_Gobal__FluxPatals(std::vector<double> &FitParas,
                                    std::vector<double> &FitParas_error,
                                    double &chi_2) {
  if (h_Gobal_flux_Tracker_Daisy == nullptr) {
    std::cout << "h_Gobal_flux_Tracker_Daisy not set Fit would do nothign "
              << std::endl;
    assert(false);
  }
  if (h_Gobal_flux_Target == nullptr) {
    std::cout << "h_Gobal_flux_Target not set Fit would do nothign "
              << std::endl;
    assert(false);
  }

  TMinuit *ptMinuit = new TMinuit(12);

  ptMinuit->SetPrintLevel(2);
  // set the user function that calculates chi_square (the value to minimize)
  ptMinuit->SetFCN(Daisyfit_function);
  // calc_two2D_Gobal_ChiSq_2DGaussian2D

  Double_t arglist[12];
  Int_t ierflg = 0;

  arglist[0] = 1;
  ptMinuit->mnexcm("SET ERR", arglist, 1, ierflg);
  // Set starting values and step sizes for parameters
  //      Start from 1.0 and step 0.01

  double default_step = 0.001;
  double default_Max = 5.0;
  double default_Min = 0.0;
  double defalt_Start = 1;
  double defalt_Start2 = 2;

  ptMinuit->mnparm(0, "p0", 1, default_step, default_Min, default_Max, ierflg);
  ptMinuit->mnparm(1, "p1", 1, default_step, default_Min, default_Max, ierflg);
  ptMinuit->mnparm(2, "p2", 1, default_step, default_Min, default_Max, ierflg);
  ptMinuit->mnparm(3, "p3", 1, default_step, default_Min, default_Max, ierflg);
  ptMinuit->mnparm(4, "p4", 1, default_step, default_Min, default_Max, ierflg);
  ptMinuit->mnparm(5, "p5", 1, default_step, default_Min, default_Max, ierflg);
  ptMinuit->mnparm(6, "p6", defalt_Start2, default_step, default_Min,
                   default_Max, ierflg);
  ptMinuit->mnparm(7, "p7", defalt_Start2, default_step, default_Min,
                   default_Max, ierflg);
  ptMinuit->mnparm(8, "p8", defalt_Start2, default_step, default_Min,
                   default_Max, ierflg);
  ptMinuit->mnparm(9, "p9", defalt_Start2, default_step, default_Min,
                   default_Max, ierflg);
  ptMinuit->mnparm(10, "p10", defalt_Start2, default_step, default_Min,
                   default_Max, ierflg);
  ptMinuit->mnparm(11, "p11", defalt_Start2, default_step, default_Min,
                   default_Max, ierflg);
  //	ptMinuit->mnparm(par , "name ",   UK, WK, A, B , ierflg);
  // UK starting value
  // WK starting step size or uncertainty
  // A, B lower and upper physical parameter limits and sets up (updates) the
  // parameter lists. Output:
  // IERFLG=0 if no problems
  //>0 if MNPARM unable to implement definition

  arglist[0] = 500000;
  arglist[1] = 1;

  ptMinuit->mnexcm("MIGRAD", arglist, 12, ierflg);  // SEE, MINImize , MIGRAD"

  // Print results
  // std::cout<<"\nPrint results from minuit\n";
  double fParamVal[12];
  double fParamErr[12];
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

  if (ierflg = !0) {
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    std::cout << "Did not FIT " << std::endl;
    std::cout << "~~~~~~~ierflg = " << ierflg << std::endl;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
  }

  Double_t min_ChiSq, edm, errdef;
  Int_t nvpar, nparx, icstat;
  ptMinuit->mnstat(min_ChiSq, edm, errdef, nvpar, nparx, icstat);

  std::cout << "inside: min_ChiSq =" << min_ChiSq << std::endl;
  std::cout << "inside:  edm = " << edm << std::endl;
  std::cout << "inside:  errdef = " << errdef << std::endl;
  std::cout << "inside:  nvpar = " << nvpar << std::endl;
  std::cout << "inside:  nparx = " << nparx << std::endl;
  std::cout << "inside:  icstat = " << icstat << std::endl;

  chi_2 = min_ChiSq;

  FitParas.push_back(fParamVal[0]);
  FitParas.push_back(fParamVal[1]);
  FitParas.push_back(fParamVal[2]);
  FitParas.push_back(fParamVal[3]);
  FitParas.push_back(fParamVal[4]);
  FitParas.push_back(fParamVal[5]);
  FitParas.push_back(fParamVal[6]);
  FitParas.push_back(fParamVal[7]);
  FitParas.push_back(fParamVal[8]);
  FitParas.push_back(fParamVal[9]);
  FitParas.push_back(fParamVal[10]);
  FitParas.push_back(fParamVal[11]);

  FitParas_error.push_back(fParamErr[0]);
  FitParas_error.push_back(fParamErr[1]);
  FitParas_error.push_back(fParamErr[2]);
  FitParas_error.push_back(fParamErr[3]);
  FitParas_error.push_back(fParamErr[4]);
  FitParas_error.push_back(fParamErr[5]);
  FitParas_error.push_back(fParamErr[6]);
  FitParas_error.push_back(fParamErr[7]);
  FitParas_error.push_back(fParamErr[8]);
  FitParas_error.push_back(fParamErr[9]);
  FitParas_error.push_back(fParamErr[10]);
  FitParas_error.push_back(fParamErr[11]);

  // gMinuit->SetErrorDef(1);
  // TGraph *gr1 = (TGraph*)gMinuit->Contour(60,3,7);
  // TGraph *gr2 = (TGraph*)gMinuit->Contour(60,1,3);
  // TGraph *gr3 = (TGraph*)gMinuit->Contour(60,1,7);

  // gMinuit->SetErrorDef(4);
  // TGraph *gr4 = (TGraph*)gMinuit->Contour(60,3,7);
  // TGraph *gr5 = (TGraph*)gMinuit->Contour(60,1,3);
  // TGraph *gr6 = (TGraph*)gMinuit->Contour(60,1,7);

  // outputTGraphs.push_back(gr1);
  // outputTGraphs.push_back(gr2);
  // outputTGraphs.push_back(gr3);
  // outputTGraphs.push_back(gr4);
  // outputTGraphs.push_back(gr5);
  // outputTGraphs.push_back(gr6);

  delete ptMinuit;

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
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void Fit2DPatals_fluxratio(std::vector<double> &FitParas,
                           std::vector<double> &FitParas_error, double &chi_2,
                           double Lambda) {
  Set_Lambda_Penity(Lambda);
  SetStatvector_usingflux_Tracker_Daisy();
  FitMinuit_h1_Gobal__FluxPatals(FitParas, FitParas_error, chi_2);
  clearStatvector();
}

PlotUtils::MnvH1D *make_param_hist(std::string name,
                                   std::vector<double> parameters,
                                   std::vector<double> parameter_errors) {
  std::vector<double> bins{0,   1.0, 2.0, 3.0,  4.0,  5.0, 6.0,
                           7.0, 8.0, 9.0, 10.0, 11.0, 12.0};

  PlotUtils::MnvH1D *param_hist =
      new PlotUtils::MnvH1D(name.c_str(), "param_hist;Daisy Bin;Weight",
                            bins.size() - 1, bins.data());

  for (size_t i = 0; i < parameters.size(); ++i) {
    int b = i + 1;
    double p = parameters.at(i);
    double perr = parameter_errors.at(i);
    param_hist->SetBinContent(b, p);
    param_hist->SetBinError(b, perr);
  }
  return param_hist;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
