#ifndef LOCALCOLOR_H
#define LOCALCOLOR_H

#include "TColor.h"
#include <assert.h>


//======================================================================
enum EColorPalettes
{
  kAlphabetPalette, kKellyPalette, k36Palette, kGlasbeyPalette, kBrewerSet1Palette, kBrewerDark2Palette, kdarker36Palette
};

//======================================================================
const std::vector<int>& getColors(int whichColours);









#endif
