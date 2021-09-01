
#ifndef HELIUM_RUNEVENTLOOP_EFFICIENCYSTUDY_H
#define HELIUM_RUNEVENTLOOP_EFFICIENCYSTUDY_H

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
#include "PlotUtils/Hist2DWrapper.h"
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
#include "PlotUtils/weightMK.h"



#include "../includes/HeliumCVUniverse.h"
#include "../includes/Helium_VertexSmearing_LateralSystematics_2XY_2Z.h"
#include "../includes/Helium_TargetMassSystematics.h"

#include "../includes/HeliumCuts.h"
#include "../includes/HeliumUtils.h"
#include "../includes/loadLibs.h"
#include "../includes/CryoTankUtils.h"
//#include <PlotUtils/POTCounter.h>
#include "TChain.h"
#include "EventCounting.h"

//#include "../src/loadLibs.h"
//#include "../src/Catgorized.h"

#include "PlotUtils/MnvH1D.h"
//#include "PlotUtils/MnvH2D.h"
#include <PlotUtils/MnvH2D.h>
#include <iostream>

#ifndef __CINT__
#include "../includes/HeliumPlotUtils.h"
#endif

#include "TSystem.h"
#include <TROOT.h>
#include <TFile.h>
#include <algorithm>
//class MnvH1D;
//class MnvH2D;

struct Vertex{
//Vertex_Plots(const std::string& name, const std::string& title);

MnvH1D* fVertex_X;
MnvH1D* fVertex_Y;
MnvH1D* fVertex_Z;

MnvH2D* fMigration_Vertex_Y;
MnvH2D* fMigration_Vertex_X;
MnvH2D* fMigration_Vertex_Z;

};

struct Muon_kinematics{
//Muon_kinematics_Plots(const std::string& name, const std::string& title);

MnvH1D* fMuonP_E;
MnvH1D* fMuonP_X;
MnvH1D* fMuonP_Y;
MnvH1D* fMuonP_T;
MnvH1D* fMuonP_Z;

MnvH2D* fMigration_MuonP_Y;
MnvH2D* fMigration_MuonP_X;
MnvH2D* fMigration_MuonP_Z;
MnvH2D* fMigration_MuonP_E;

};








//class TFile;
//class MnvH1D;
/*
class Helium_Analysis {
public:
  Helium_Analysis( const std::string& prefix, TFile& file);

  virtual ~Helium_Analysis() = default;

  template <class HIST, class ...ARGS>
       HIST* make(const std::string& name, ARGS... args)
       {
         DirSentry sentry(fParentFile);
         auto obj = new HIST(SafeROOTName(fPrefix + " " + name).c_str(), args...);
         return obj;
       }
     private:
       TFile& fParentFile; //All histograms created by make<>() will end up
                           //in this TFile
     protected:
       const std::string fPrefix; //This prefix will be added to the names of all histograms Fill()ed by
                                  //this Analysis

};//end of class
*/










#endif
