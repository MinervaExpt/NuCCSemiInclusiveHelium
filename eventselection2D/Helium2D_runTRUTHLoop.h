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
#include "PlotUtils/TargetMassSystematics.h"
#include "PlotUtils/FluxReweighter.h"
#include "PlotUtils/TargetUtils.h"
#include "../includes/Helium_VertexSmearing_LateralSystematics_2XY_2Z.h"
#include "../includes/Helium_TargetMassSystematics.h"
//local Helium Tools
#include "../includes/HeliumDefaults.h"
#include "../includes/HeliumCVUniverse.h"
#include "../includes/HeliumCuts.h"
#include "../includes/HeliumUtils.h"
#include "../includes/loadLibs.h"
#include "../includes/CryoTankUtils.h"
#include "../includes/Helium2DUtils.h"
#include "../includes/loadLibs.h"

#include <PlotUtils/POTCounter.h>
#include "TChain.h"
#include "../eventselection/EventCounting.h"
#include <PlotUtils/MnvH2D.h>
#include <iostream>

#ifndef __CINT__
#include "../includes/HeliumPlotUtils.h"
#endif

#include "TSystem.h"
#include <TROOT.h>
#include <TFile.h>
#include <algorithm>




#endif
