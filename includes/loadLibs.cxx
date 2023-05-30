#include "loadLibs.h"

void loadLibs() {
#ifdef __CINT__
  std::cout << "Run loadLibs.C+" << std::endl;
  exit(1);
#else
  gSystem->SetAclicMode(TSystem::kDebug);

  // MnvH1D hides approximately everything, so just turn off the pages
  // of compiler warnings. It would have been easier to do this by
  // using SetFlagsDebug(), but those flags get put before the default
  // settings in the compile line, and so the default settings win
  TString makeSharedLib(gSystem->GetMakeSharedLib());
  makeSharedLib.ReplaceAll("-Woverloaded-virtual", "-Wno-overloaded-virtual");
  gSystem->SetMakeSharedLib(makeSharedLib);
  gSystem->Load("libMinuit");
  // Compile local scripts
  // gInterpreter->ExecuteMacro("loadCuts.C");

  // Add to include dirs
  const int kNIncDirs = 2;
  TString incDirs[kNIncDirs] = {
      TString::Format("%s", gSystem->Getenv("PLOTUTILSROOT")),
      TString::Format("%s", gSystem->Getenv("UNFOLDUTILSROOT")),
  };

  for (int i = 0; i < kNIncDirs; ++i) {
    // cout << "Adding " << incDirs[i] << endl;
    gInterpreter->AddIncludePath(incDirs[i]);
  }

  // Link plotutils, mcreweight, and others
  const int kNLibs = 2;
  // TODO: Will probably need to add T2KReweight and the neut reweight library
  // to this
  const char* libs[kNLibs] = {"libMAT.so",
                              // "libCintex.so", for root 5
                              "libUnfoldUtils.so"};

  for (int i = 0; i < kNLibs; ++i) {
    std::cout << "Loading " << libs[i] << std::endl;
    gSystem->Load(libs[i]);
  }

// gSystem->CompileMacro("util/plot/GridCanvas.cxx", "k");
// Long complicated reason to do this because of using TExec to set colour
// palettes
// gSystem->CompileMacro("util/plot/myPlotStyle.h", "k");
#endif
}
