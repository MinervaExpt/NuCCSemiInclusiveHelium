#ifndef HELIUM2D_RUNTRUTHLOOP_H
#define HELIUM2D_RUNTRUTHLOOP_H

//ROOT includes
#include "Math/Vector3D.h"
#include "TDatabasePDG.h"
#include "TGeoElement.h"
//c++ includes
#include <memory>
#include <string>
#include <cstring>
#include "PlotUtils/ChainWrapper.h"
#include "PlotUtils/makeChainWrapper.h"
#include "PlotUtils/HistWrapper.h"
#include "PlotUtils/HistFolio.h"
#include "PlotUtils/MnvColors.h"
#include "PlotUtils/NamedCategory.h"
// Systematics lib
#include "PlotUtils/GenieSystematics.h"
#include "PlotUtils/FluxSystematics.h"
#include "PlotUtils/MnvTuneSystematics.h"
#include "PlotUtils/AngleSystematics.h"
#include "PlotUtils/MuonResolutionSystematics.h"
#include "PlotUtils/MinosEfficiencySystematics.h"
#include "PlotUtils/PlotUtilsPhysicalConstants.h"
#include "PlotUtils/ResponseSystematics.h"
#include "PlotUtils/MuonSystematics.h"
#include "PlotUtils/FluxReweighter.h"

#include "../includes/CVUniverse.h"
//#include "../includes/LateralSystematics.h"
#include "../includes/Cuts.h"
#include "../includes/common_stuff.h"
#include "../includes/common_functions.h"
#include "../includes/common_2Dfunctions.h"
#include "../includes/loadLibs.h"

#include "../includes/CryoTankGeometry.h"
#include <PlotUtils/POTCounter.h>
#include "TChain.h"
#include "../eventselection/EventCounting.h"
#include <PlotUtils/MnvH2D.h>
#include <iostream>

#ifndef __CINT__
#include "../includes/plotting_functions.h"
#endif

#include "TSystem.h"
#include <TROOT.h>
#include <TFile.h>
#include <algorithm>












#endif
