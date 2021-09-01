#ifndef MYPLOTSTYLE_H
#define MYPLOTSTYLE_H

#include "TStyle.h"
#include "TColor.h"

#include "TList.h"
#include "TPad.h"
#include "TH1.h"
#include "TCanvas.h"

#include <iostream>

//======================================================================
void setRedPalette();

//======================================================================
void setCorrelationPalette(double whiteFrac=0.5);

//======================================================================
void setRainbowToWhitePalette();

//======================================================================
void setBlackbodyPalette();


//======================================================================
void myPlotStyle();


#endif
