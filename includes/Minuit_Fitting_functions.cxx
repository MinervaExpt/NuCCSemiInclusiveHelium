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

#include "HeliumPlotUtils.h"
#include "CryoTankUtils.h"
#include "HeliumDefaults.h"
#include "HeliumUtils.h"
#include "Helium2DUtils.h"
#include "Helium2DPlotUtils.h"

TH2D *h1_Gobal = nullptr;
TH2D *h2_Gobal = nullptr;
Int_t npfits;
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
double EllipticparaboloidFunction_miniut(Double_t *x, Double_t *par) {
  return ((x[0] * x[0]) / (par[0] * par[0])) +
         ((x[1] * x[1]) / (par[1] * par[1]));
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
double EllipticparaboloidFunction_miniut(double x, double y, double paraA,
                                         double paraB) {
  return ((x * x) / (paraA * paraA)) + ((y * y) / (paraB * paraB));
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void Set_h1_Gobal(TH2D *input) { h1_Gobal = input; }
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void Set_h2_Gobal(TH2D *input) { h2_Gobal = input; }
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void calc_h1_Gobal_ChiSq_2D_Ellipticparaboloid(Int_t &npar, Double_t *gin,
                                               Double_t &f, Double_t *par,
                                               Int_t iflag) {
  // Silence Unused Variable Warning
  (void)npar;
  (void)gin;
  (void)iflag;

  if (h1_Gobal == nullptr) {
    std::cout << "Hist was not correctly assigned" << std::endl;
    assert(false);
  }

  TAxis *xaxis1 = h1_Gobal->GetXaxis();
  TAxis *yaxis1 = h1_Gobal->GetYaxis();

  int nbinX1 = h1_Gobal->GetNbinsX();
  int nbinY1 = h1_Gobal->GetNbinsY();
  double chi2 = 0;
  double x[2];
  double tmp;
  double Bin = 99;
  double error = 99;
  double Model = 99;
  npfits = 0;

  for (int ix = 1; ix <= nbinX1; ++ix) {
    x[0] = xaxis1->GetBinCenter(ix);
    for (int iy = 1; iy <= nbinY1; ++iy) {
      // error = h1_Gobal->GetBinError(ix,iy);
      // std::cout << "error = "<< error << std::endl;

      x[1] = yaxis1->GetBinCenter(iy);
      Bin = h1_Gobal->GetBinContent(ix, iy);
      Model = EllipticparaboloidFunction_miniut(x, par);

      // std::cout<< "Bin : "<< Bin<<std::endl;
      // std::cout<< "error : "<< error<<std::endl;
      // std::cout<< "Model : "<< Model<<std::endl;
      if (Model > 0) {
        tmp = ((Bin - Model) * (Bin - Model)) / Model;
        chi2 += tmp;
        npfits++;
      }
    }
  }

  f = chi2;
  return;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void calc_h1_Gobal_ChiSqLOG_2D_Ellipticparaboloid(Int_t &npar, Double_t *gin,
                                                  Double_t &fvar, Double_t *par,
                                                  Int_t iflag) {
  // Silence Unused Variable Warning
  (void)npar;
  (void)gin;
  (void)iflag;

  double ChiSq = 0;

  TAxis *xaxis1 = h1_Gobal->GetXaxis();
  TAxis *yaxis1 = h1_Gobal->GetYaxis();

  int nbinX1 = h1_Gobal->GetNbinsX();
  int nbinY1 = h1_Gobal->GetNbinsY();

  double x[2];
  double tmp = 99;
  double c = 99;
  npfits = 0;

  for (int ix = 1; ix <= nbinX1; ++ix) {
    x[0] = xaxis1->GetBinCenter(ix);
    for (int iy = 1; iy <= nbinY1; ++iy) {
      if (h1_Gobal->GetBinError(ix, iy) > 0) {
        x[1] = yaxis1->GetBinCenter(iy);
        double nMC_total = EllipticparaboloidFunction_miniut(x, par);
        // double delta = pow((nData-nMC_total),2) / pow(err,2);
        c = h1_Gobal->GetBinContent(ix, iy) * log(nMC_total);
        tmp = 2 * (nMC_total - c);
        ChiSq += tmp;
        npfits++;
      }
    }
  }

  fvar = ChiSq;
  return;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void FillHist_Ellipticparaboloid(MnvH2D &h_Fill, double ParaA, double ParaB) {
  int nbinX1 = h_Fill.GetNbinsX();
  int nbinY1 = h_Fill.GetNbinsY();

  TAxis *xaxis1 = h_Fill.GetXaxis();
  TAxis *yaxis1 = h_Fill.GetYaxis();

  for (int ix = 1; ix <= nbinX1; ++ix) {
    double X_input = xaxis1->GetBinCenter(ix);
    for (int iy = 1; iy <= nbinY1; ++iy) {
      double Y_input = yaxis1->GetBinCenter(iy);
      double Zinput =
          EllipticparaboloidFunction_miniut(X_input, Y_input, ParaA, ParaB);
      h_Fill.Fill(X_input, Y_input, Zinput);
    }
  }

  return;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void FitMinuit_h1_Gobal_Ellipticparaboloid(
  std::vector<double> &FitParas, std::vector<double> &FitParas_error) {
    if (h1_Gobal == nullptr) {
      std::cout << "h1_Gobal not set Fit would do nothign " << std::endl;
      assert(false);
    }

    TMinuit *ptMinuit = new TMinuit(2);

    ptMinuit->SetPrintLevel(2);
    // set the user function that calculates chi_square (the value to minimize)
    ptMinuit->SetFCN(calc_h1_Gobal_ChiSq_2D_Ellipticparaboloid);

    Double_t arglist[10];
    Int_t ierflg = 0;

    arglist[0] = 1;
    ptMinuit->mnexcm("SET ERR", arglist, 1, ierflg);
    // Set starting values and step sizes for parameters
    //      Start from 1.0 and step 0.01
    ptMinuit->mnparm(0, "FitParm_A", 1, .01, .2, 3, ierflg);
    ptMinuit->mnparm(1, "FitParm_B", 1, .01, .2, 3, ierflg);
    //	ptMinuit->mnparm(par , "name ",   UK, WK, A, B , ierflg);
    // UK starting value
    // WK starting step size or uncertainty
    // A, B lower and upper physical parameter limits and sets up (updates) the
    // parameter lists. Output:
    // IERFLG=0 if no problems
    //>0 if MNPARM unable to implement definition

    arglist[0] = 500000;
    arglist[1] = .01;

    ptMinuit->mnexcm("SEEk", arglist, 2, ierflg);

    // Print results
    // std::cout<<"\nPrint results from minuit\n";
    double fParamVal[2];
    double fParamErr[2];
    ptMinuit->GetParameter(0, fParamVal[0], fParamErr[0]);
    ptMinuit->GetParameter(1, fParamVal[1], fParamErr[1]);

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

  FitParas.push_back(fParamVal[0]);
  FitParas.push_back(fParamVal[1]);

  FitParas_error.push_back(fParamErr[0]);
  FitParas_error.push_back(fParamErr[1]);

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
