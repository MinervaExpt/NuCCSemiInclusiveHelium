#ifndef GRIDCANVAS_H
#define GRIDCANVAS_H

#include "TCanvas.h"
#include "TString.h"
#include "plot.h"
#include <vector>

#include "TLatex.h"
#include "TPad.h"
#include "TH1.h"
#include "TAxis.h"
#include "TList.h"
#include "TGraph.h"
#include "TStyle.h"



#include <iostream>



class TLatex;
class TPad;
class TH1;

class GridCanvas : public TCanvas
{
public:
  GridCanvas() {}; // To shut ROOT up
  GridCanvas(const char* name, int nPadsX, int nPadsY, int ww=700, int wh=500);

  virtual ~GridCanvas();

  void SetXTitle(const char* xtitle);
  void SetYTitle(const char* ytitle);

  TLatex* GetXTitle();
  TLatex* GetYTitle();

  std::vector<TPad*> GetPads() const { return fPads; }


  void SetHistTexts();

  void SetXLimits(double xmin, double xmax);
  void SetYLimits(double ymin, double ymax);
  void SetYLabel_Size(double size);
  void SetXLabel_Size(double size);


  enum ETitleAlignment { kAlignRight, kAlignCenter };

  void SetTitleAlignment(ETitleAlignment alignment) { fTitleAlignment=alignment; }

  void SetInterpadSpace(double space) { fInterpadSpace=space; ResetPads(); }

  void Paint(Option_t*);

  virtual void SetLogx(Int_t value=1);
  virtual void SetLogy(Int_t value=1);
  virtual void SetLogz(Int_t value=1);

  virtual void SetGridx(Int_t value=1);
  virtual void SetGridy(Int_t value=1);

  virtual void SetLeftMargin(Float_t margin);
  virtual void SetRightMargin(Float_t margin);
  virtual void SetTopMargin(Float_t margin);
  virtual void SetBottomMargin(Float_t margin);

  void SetTicksx(const char* option);
  void SetTicksy(const char* option);

  void ResetPads();

  void SetTitleFont(int font) { fTitleFont=font; }
  int  GetTitleFont() const { return fTitleFont; }

  void   SetTitleSize(double size) { fTitleSize=size; }
  void   SetXTitleSize(double size) { fXTitleSize=size; }
  void   SetYTitleSize(double size) { fYTitleSize=size; }
  double GetTitleSize() const { return fTitleSize; }
  double GetXTitleSize() const { return fXTitleSize; }
  double GetYTitleSize() const { return fYTitleSize; }



  double GetPadMax();
  void Remax(double ymin=0);

  void SetManualXLabels(int nLabels, const double* positions, const char** valueStrings, double yoffset=0.1);
  void SetManualYLabels(int nLabels, const double* positions, const char** valueStrings, double xoffset=0.1);

private:

  TH1* GetPadHist(TPad* pad);

  void DrawTitles();

  int fNPadsX, fNPadsY;
  std::vector<TPad*> fPads;
  std::vector< std::vector<TPad*> > fPads2D;
  double fInterpadSpace;
  TLatex* fXTitleLatex;
  TLatex* fYTitleLatex;

  ETitleAlignment fTitleAlignment;
  TString fXTitle, fYTitle;
  bool fXTitleDrawn, fYTitleDrawn;

  int fTitleFont;
  double fTitleSize;
  bool UseIndividualTitlesize = true;
  double fXTitleSize = -1;
  double fYTitleSize = -1;

  bool fManualXLabels;
  bool fManualYLabels;

  ClassDef(GridCanvas, 0);
};

#endif
