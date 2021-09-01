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


//Particle_color_map getColorMap_Particle();
//Interaction_color_map getColorMap_Interaction();
//Material_color_map getColorMap_Material();

//======================================================================
/* void autoColorHists(TPad* pad, int whichColours=kBrewerSet1Palette) */
/* { */
/*   const std::vector<int>& colours=getColors(whichColours); */

/*   std::vector<TH1*> hists=getPadHists(pad); */
/*   for(unsigned int i=0; i<hists.size(); ++i){ */
/*     hists[i]->SetLineColor(colours[i%colours.size()]); */
/*   } */
/*   pad->Draw(); */
/* } */







#endif
