//File: CrossSection_Normalization.cxx
//Brief: The Functions that deal with Cross section
//Author: Christian Nguyen christian2nguyen@ufl.edu

#include "CrossSection_Normalization.h"


/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////

void POT_Normalize_2DCrossSection_Hist_InteractionOnly_DISBreakdown(CrossSection2D_Hist &inputCross_Hist, double normalize_MC_data){

  inputCross_Hist.Interaction_HistMap[kElastic]->Scale(normalize_MC_data);
  inputCross_Hist.Interaction_HistMap[kdeltaRES]->Scale(normalize_MC_data);
  inputCross_Hist.Interaction_HistMap[kHeavierRES]->Scale(normalize_MC_data);
  inputCross_Hist.Interaction_HistMap[k2p2h]->Scale(normalize_MC_data);
  inputCross_Hist.Interaction_HistMap[kDISSIS]->Scale(normalize_MC_data);
  inputCross_Hist.Interaction_HistMap[kDISSoft]->Scale(normalize_MC_data);
  inputCross_Hist.Interaction_HistMap[kDISHard]->Scale(normalize_MC_data);
  inputCross_Hist.Interaction_HistMap[kInteraction_NONE]->Scale(normalize_MC_data);
  inputCross_Hist.Interaction_HistMap[kInteraction_OTHER]->Scale(normalize_MC_data);
	return;
}

/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void POT_Normalize_CrossSection_Hist_InteractionOnly_DISBreakdown(CrossSection_Hist &inputCross_Hist, double normalize_MC_data){

  inputCross_Hist.Interaction_HistMap[kElastic]->Scale(normalize_MC_data);
  inputCross_Hist.Interaction_HistMap[kdeltaRES]->Scale(normalize_MC_data);
  inputCross_Hist.Interaction_HistMap[kHeavierRES]->Scale(normalize_MC_data);
  inputCross_Hist.Interaction_HistMap[k2p2h]->Scale(normalize_MC_data);

  inputCross_Hist.Interaction_HistMap[kDISSIS]->Scale(normalize_MC_data);
  inputCross_Hist.Interaction_HistMap[kDISSoft]->Scale(normalize_MC_data);
  inputCross_Hist.Interaction_HistMap[kDISHard]->Scale(normalize_MC_data);
  inputCross_Hist.Interaction_HistMap[kInteraction_NONE]->Scale(normalize_MC_data);
  inputCross_Hist.Interaction_HistMap[kInteraction_OTHER]->Scale(normalize_MC_data);

	return;
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////

void POT_Normalize_CrossSection_Hist_InteractionOnly(CrossSection_Hist &inputCross_Hist, double normalize_MC_data){

  inputCross_Hist.Interaction_HistMap[kElastic]->Scale(normalize_MC_data);
  inputCross_Hist.Interaction_HistMap[kRes_Coh_Pion]->Scale(normalize_MC_data);
  inputCross_Hist.Interaction_HistMap[k2p2h]->Scale(normalize_MC_data);
  inputCross_Hist.Interaction_HistMap[kDIS]->Scale(normalize_MC_data);
  inputCross_Hist.Interaction_HistMap[kInteraction_NONE]->Scale(normalize_MC_data);
  inputCross_Hist.Interaction_HistMap[kInteraction_OTHER]->Scale(normalize_MC_data);

}

/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void POT_Normalize_CrossSection_Hist(CrossSection_Hist &inputCross_Hist, double normalize_MC_data, double normalize_fullData_emptyData, bool dodata){
  if(dodata==true){
    inputCross_Hist.h_Data_Signal->Scale(normalize_fullData_emptyData);
  }

  inputCross_Hist.h_RECO_Signal->Scale(normalize_MC_data);
  inputCross_Hist.h_RECO_BG->Scale(normalize_MC_data);
  inputCross_Hist.h_effNum->Scale(normalize_MC_data);
  inputCross_Hist.h_effDom->Scale(normalize_MC_data);
  //inputCross_Hist.h_Mig->Scale(normalize_MC_data);

}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void POT_Normalize_CrossSection_Hist_Daisy(CrossSection_Hist_Daisy &inputCross_Hist,double normalize_MC_data  ){

	POT_Normalize_CrossSection_Hist(inputCross_Hist.Daisy0, normalize_MC_data, 1.0, false);
	POT_Normalize_CrossSection_Hist(inputCross_Hist.Daisy1, normalize_MC_data, 1.0, false);
	POT_Normalize_CrossSection_Hist(inputCross_Hist.Daisy2, normalize_MC_data, 1.0, false);
	POT_Normalize_CrossSection_Hist(inputCross_Hist.Daisy3, normalize_MC_data, 1.0, false);
	POT_Normalize_CrossSection_Hist(inputCross_Hist.Daisy4, normalize_MC_data, 1.0, false);
	POT_Normalize_CrossSection_Hist(inputCross_Hist.Daisy5, normalize_MC_data, 1.0, false);
	POT_Normalize_CrossSection_Hist(inputCross_Hist.Daisy6, normalize_MC_data, 1.0, false);
	POT_Normalize_CrossSection_Hist(inputCross_Hist.Daisy7, normalize_MC_data, 1.0, false);
	POT_Normalize_CrossSection_Hist(inputCross_Hist.Daisy8, normalize_MC_data, 1.0, false);
	POT_Normalize_CrossSection_Hist(inputCross_Hist.Daisy9, normalize_MC_data, 1.0, false);
	POT_Normalize_CrossSection_Hist(inputCross_Hist.Daisy10,normalize_MC_data, 1.0, false);
	POT_Normalize_CrossSection_Hist(inputCross_Hist.Daisy11,normalize_MC_data, 1.0, false);

}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void POT_Normalize_2DCrossSection_Hist(CrossSection2D_Hist &inputCross_Hist, double normalize_MC_data, double normalize_fullData_emptyData, bool dodata){
  if(dodata==true){
    inputCross_Hist.h_Data_Signal->Scale(normalize_fullData_emptyData);
  }

  inputCross_Hist.h_effNum->Scale(normalize_MC_data);
  inputCross_Hist.h_effDom->Scale(normalize_MC_data);
  inputCross_Hist.h_mvnreponse_Mig->Scale(normalize_MC_data); // in CCQENuPion2D then seem to also scale the Mig
  inputCross_Hist.h_mvnreponse_RECO->Scale(normalize_MC_data);
  inputCross_Hist.h_mvnreponse_TRUE->Scale(normalize_MC_data);
  inputCross_Hist.h_RECO->Scale(normalize_MC_data);
	inputCross_Hist.h_RECO_BG->Scale(normalize_MC_data);

}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void POT_Normalize_CrossSection2D_Hist_Daisy(CrossSection2D_Hist_Daisy &inputCross_Hist,double normalize_MC_data  ){

	POT_Normalize_2DCrossSection_Hist(inputCross_Hist.Daisy0, normalize_MC_data, 1.0, false);
	POT_Normalize_2DCrossSection_Hist(inputCross_Hist.Daisy1, normalize_MC_data, 1.0, false);
	POT_Normalize_2DCrossSection_Hist(inputCross_Hist.Daisy2, normalize_MC_data, 1.0, false);
	POT_Normalize_2DCrossSection_Hist(inputCross_Hist.Daisy3, normalize_MC_data, 1.0, false);
	POT_Normalize_2DCrossSection_Hist(inputCross_Hist.Daisy4, normalize_MC_data, 1.0, false);
	POT_Normalize_2DCrossSection_Hist(inputCross_Hist.Daisy5, normalize_MC_data, 1.0, false);
	POT_Normalize_2DCrossSection_Hist(inputCross_Hist.Daisy6, normalize_MC_data, 1.0, false);
	POT_Normalize_2DCrossSection_Hist(inputCross_Hist.Daisy7, normalize_MC_data, 1.0, false);
	POT_Normalize_2DCrossSection_Hist(inputCross_Hist.Daisy8, normalize_MC_data, 1.0, false);
	POT_Normalize_2DCrossSection_Hist(inputCross_Hist.Daisy9, normalize_MC_data, 1.0, false);
	POT_Normalize_2DCrossSection_Hist(inputCross_Hist.Daisy10,normalize_MC_data, 1.0, false);
	POT_Normalize_2DCrossSection_Hist(inputCross_Hist.Daisy11,normalize_MC_data, 1.0, false);

}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void AddErrorBands_TOEffDom(CrossSection_Hist &inputCross_Hist){
	inputCross_Hist.h_effDom->AddMissingErrorBandsAndFillWithCV(*inputCross_Hist.h_effNum);
	return;
}// end of function
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void AddErrorBands_TOEffDom(CrossSection2D_Hist &inputCross_Hist){
	inputCross_Hist.h_effDom->AddMissingErrorBandsAndFillWithCV(*inputCross_Hist.h_effNum);
	return;
}// end of function
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Subtract_CrossSection_Hist(CrossSection_Hist &inputCross_Hist_Full, CrossSection_Hist &inputCross_Hist_Empty){

  inputCross_Hist_Full.h_Data_Signal->Add(inputCross_Hist_Empty.h_Data_Signal,-1);
  inputCross_Hist_Full.h_RECO_Signal->Add(inputCross_Hist_Empty.h_RECO_Signal,-1);
  inputCross_Hist_Full.h_RECO_BG->Add(inputCross_Hist_Empty.h_RECO_BG,-1);
  inputCross_Hist_Full.h_effDom->Add(inputCross_Hist_Empty.h_effDom,-1);
  inputCross_Hist_Full.h_effNum->Add(inputCross_Hist_Empty.h_effNum,-1);
	return;
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Subtract_CrossSection_Hist_Interaction(CrossSection_Hist &inputCross_Hist_Full, CrossSection_Hist &inputCross_Hist_Empty){
  inputCross_Hist_Full.Interaction_HistMap[kElastic]->Add(inputCross_Hist_Empty.Interaction_HistMap[kElastic],-1);
  inputCross_Hist_Full.Interaction_HistMap[kRes_Coh_Pion]->Add(inputCross_Hist_Empty.Interaction_HistMap[kRes_Coh_Pion],-1);
  inputCross_Hist_Full.Interaction_HistMap[k2p2h]->Add(inputCross_Hist_Empty.Interaction_HistMap[k2p2h],-1);
  inputCross_Hist_Full.Interaction_HistMap[kDIS]->Add(inputCross_Hist_Empty.Interaction_HistMap[kDIS],-1);
  inputCross_Hist_Full.Interaction_HistMap[kInteraction_NONE]->Add(inputCross_Hist_Empty.Interaction_HistMap[kInteraction_NONE],-1);
  inputCross_Hist_Full.Interaction_HistMap[kInteraction_OTHER]->Add(inputCross_Hist_Empty.Interaction_HistMap[kInteraction_OTHER],-1);
	return;
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Subtract_CrossSection_Hist(CrossSection2D_Hist &inputCross_Hist_Full, CrossSection2D_Hist &inputCross_Hist_Empty){

  inputCross_Hist_Full.h_Data_Signal->Add(inputCross_Hist_Empty.h_Data_Signal,-1);
  inputCross_Hist_Full.h_effNum->Add(inputCross_Hist_Empty.h_effNum,-1);
  inputCross_Hist_Full.h_effDom->Add(inputCross_Hist_Empty.h_effDom,-1);
  inputCross_Hist_Full.h_mvnreponse_Mig->Add(inputCross_Hist_Empty.h_mvnreponse_Mig, -1);
  inputCross_Hist_Full.h_mvnreponse_RECO->Add(inputCross_Hist_Empty.h_mvnreponse_RECO, -1);
  inputCross_Hist_Full.h_mvnreponse_TRUE->Add(inputCross_Hist_Empty.h_mvnreponse_TRUE, -1);
  inputCross_Hist_Full.h_RECO->Add(inputCross_Hist_Empty.h_RECO, -1);
	inputCross_Hist_Full.h_RECO_BG->Add(inputCross_Hist_Empty.h_RECO_BG,-1);
	return;
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Subtract_CrossSection_Hist_Interaction(CrossSection2D_Hist &inputCross_Hist_Full, CrossSection2D_Hist &inputCross_Hist_Empty){

  inputCross_Hist_Full.Interaction_HistMap[kElastic]->Add(inputCross_Hist_Empty.Interaction_HistMap[kElastic],-1);
  inputCross_Hist_Full.Interaction_HistMap[kRes_Coh_Pion]->Add(inputCross_Hist_Empty.Interaction_HistMap[kRes_Coh_Pion],-1);
  inputCross_Hist_Full.Interaction_HistMap[k2p2h]->Add(inputCross_Hist_Empty.Interaction_HistMap[k2p2h],-1);
  inputCross_Hist_Full.Interaction_HistMap[kDIS]->Add(inputCross_Hist_Empty.Interaction_HistMap[kDIS],-1);
  inputCross_Hist_Full.Interaction_HistMap[kInteraction_NONE]->Add(inputCross_Hist_Empty.Interaction_HistMap[kInteraction_NONE],-1);
  inputCross_Hist_Full.Interaction_HistMap[kInteraction_OTHER]->Add(inputCross_Hist_Empty.Interaction_HistMap[kInteraction_OTHER],-1);
	return;
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void Subtract_CrossSection_Hist_Interaction_DISBreakdown(CrossSection2D_Hist &inputCross_Hist_Full, CrossSection2D_Hist &inputCross_Hist_Empty){

  inputCross_Hist_Full.Interaction_HistMap[kElastic]->Add(inputCross_Hist_Empty.Interaction_HistMap[kElastic],-1);
  inputCross_Hist_Full.Interaction_HistMap[kdeltaRES]->Add(inputCross_Hist_Empty.Interaction_HistMap[kdeltaRES],-1);
  inputCross_Hist_Full.Interaction_HistMap[kHeavierRES]->Add(inputCross_Hist_Empty.Interaction_HistMap[kHeavierRES],-1);
  inputCross_Hist_Full.Interaction_HistMap[k2p2h]->Add(inputCross_Hist_Empty.Interaction_HistMap[k2p2h],-1);
  inputCross_Hist_Full.Interaction_HistMap[kDISSIS]->Add(inputCross_Hist_Empty.Interaction_HistMap[kDISSIS],-1);
  inputCross_Hist_Full.Interaction_HistMap[kDISSoft]->Add(inputCross_Hist_Empty.Interaction_HistMap[kDISSoft],-1);
  inputCross_Hist_Full.Interaction_HistMap[kDISHard]->Add(inputCross_Hist_Empty.Interaction_HistMap[kDISHard],-1);
  inputCross_Hist_Full.Interaction_HistMap[kInteraction_NONE]->Add(inputCross_Hist_Empty.Interaction_HistMap[kInteraction_NONE],-1);
  inputCross_Hist_Full.Interaction_HistMap[kInteraction_OTHER]->Add(inputCross_Hist_Empty.Interaction_HistMap[kInteraction_OTHER],-1);
	return;
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void POT_Normalize_CrossSection_Hist_noBG(CrossSection_Hist &inputCross_Hist, double normalize_MC_data, double normalize_fullData_emptyData, bool dodata){
  if(dodata==true){
    inputCross_Hist.h_Data_Signal->Scale(normalize_fullData_emptyData);
  }

  inputCross_Hist.h_RECO_Signal->Scale(normalize_MC_data);
  inputCross_Hist.h_effNum->Scale(normalize_MC_data);
  inputCross_Hist.h_effDom->Scale(normalize_MC_data);
  //inputCross_Hist.h_Mig->Scale(normalize_MC_data);
	return;
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void POT_Normalize_2DCrossSection_Hist_RECO_Data(CrossSection2D_Hist &inputCross_Hist, double normalize_MC_data, double normalize_fullData_emptyData, bool dodata){
  if(dodata==true){
    inputCross_Hist.h_Data_Signal->Scale(normalize_fullData_emptyData);
  }

  inputCross_Hist.h_RECO->Scale(normalize_MC_data);

}

/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void POT_Normalize_2DCrossSection_Hist_InteractionOnly(CrossSection2D_Hist &inputCross_Hist, double normalize_MC_data){

  inputCross_Hist.Interaction_HistMap[kElastic]->Scale(normalize_MC_data);
  inputCross_Hist.Interaction_HistMap[kRes_Coh_Pion]->Scale(normalize_MC_data);
  inputCross_Hist.Interaction_HistMap[k2p2h]->Scale(normalize_MC_data);
  inputCross_Hist.Interaction_HistMap[kDIS]->Scale(normalize_MC_data);
  inputCross_Hist.Interaction_HistMap[kInteraction_NONE]->Scale(normalize_MC_data);
  inputCross_Hist.Interaction_HistMap[kInteraction_OTHER]->Scale(normalize_MC_data);

}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
PlotUtils::MnvH2D* normalize2D(PlotUtils::MnvH2D* efficiencyCorrected, PlotUtils::MnvH2D* fluxIntegral, const double nNucleons, const double POT)
{
  efficiencyCorrected->Divide(efficiencyCorrected, fluxIntegral);

  efficiencyCorrected->Scale(1./nNucleons/POT);
  efficiencyCorrected->Scale(1.e4); //Flux histogram is in m^-2, but convention is to report cm^2
  //efficiencyCorrected->Scale(1., "width");

  return efficiencyCorrected;
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
PlotUtils::MnvH2D* UnfoldHistOld( PlotUtils::MnvH2D* h_data_nobck, PlotUtils::MnvH2D* h_mc_nobck,
   PlotUtils::MnvH2D* h_reco, PlotUtils::MnvH2D* h_generated, PlotUtils::MnvH2D* h_migration, int num_iter, MnvPlotter *mnvPlotter, char *pdf )
{
  /*TParameter<double> *pot_mc = (TParameter<double>*)f2.Get("MCPOT");
 *   TParameter<double> *pot_data = (TParameter<double>*)f2.Get("DataPOT");
 *     double MCPOT = pot_mc->GetVal();
 *       double DataPOT = pot_data->GetVal();
 *         double pot_scale = DataPOT/MCPOT;
 *           h_migration->Scale(pot_scale);
 *             h_reco->Scale(pot_scale);
 *               h_generated->Scale(pot_scale);
 // POT normalization done later */

  MnvH2D *h_data_unfolded = NULL, *h_mc_unfolded = NULL;
  //int num_iter=2;
  MinervaUnfold::MnvUnfold unfold;
  bool data_unfolded = unfold.UnfoldHisto2D(h_data_unfolded, h_migration, h_reco, h_generated, h_data_nobck, num_iter, true, true); // last input variable = true makes sure that each universe of the distribution is getting unfolded with its corresponding universe in the migration matrix
  bool mc_unfolded = unfold.UnfoldHisto2D(h_mc_unfolded, h_migration, h_reco, h_generated, h_mc_nobck, num_iter, true, true);

  if(!data_unfolded || !mc_unfolded){
    std::cout << "Unfolding failed for either data or MC" << std::endl;
  }

  TCanvas c;
  h_data_unfolded->Draw("COLZ");
  mnvPlotter->AddHistoTitle("h_data_unfolded:inside unFolding", .04);
  c.Print(pdf);
  c.Clear();
  h_mc_unfolded->Draw("COLZ");
  mnvPlotter->AddHistoTitle("h_mc_unfolded:inside unFolding", .04);
  c.Print(pdf);

  // NOW we have to get the covariance of the unfolding which means doing the unfolding again
  // only need this on the data as the MC is used as CV only
  std::cout << "Getting the covariance of the unfolding" << std::endl;
  TH2D* hUnfoldedDummy=new TH2D(h_data_unfolded->GetCVHistoWithStatError());
  TH2D* hMigrationDummy=new TH2D(h_migration->GetCVHistoWithStatError());
  TH2D* hRecoDummy=new TH2D(h_reco->GetCVHistoWithStatError());
  TH2D* hTruthDummy=new TH2D(h_generated->GetCVHistoWithStatError());
  TH2D* hBGSubDataDummy=new TH2D(h_data_nobck->GetCVHistoWithStatError());

  TMatrixD unfoldingCovMatrixOrig;
  unfold.UnfoldHisto2D(hUnfoldedDummy, unfoldingCovMatrixOrig, hMigrationDummy, hRecoDummy, hTruthDummy, hBGSubDataDummy, num_iter);

  // There's a bug in RooUnfold that's making it return covariance matriced with two extra bins. Kill them here, wiht a check. Conveniently, this bug was being hidden by an offsetting bug in MnvH2D, which is now fixed (Dan)
  int correctNbins=hUnfoldedDummy->fN;
  int  matrixRows=unfoldingCovMatrixOrig.GetNrows();
  if(correctNbins!=matrixRows){
		std::cout <<"*************************************************************************" << std::endl;
		std::cout << "* Fixing unfolding matrix size because of RooUnfold bug. From " << matrixRows << " to " << correctNbins << std::endl;
		std::cout <<"*************************************************************************" << std::endl;
   unfoldingCovMatrixOrig.ResizeTo(correctNbins, correctNbins);
  }

  for(int i=0; i<unfoldingCovMatrixOrig.GetNrows(); ++i)
    unfoldingCovMatrixOrig(i,i)=0; //subtract off the diagonal errors on the covariance matrix b/c those are already included elsewhere, we don't want to double count the stat error

  delete hUnfoldedDummy;
  delete hMigrationDummy;
  delete hRecoDummy;
  delete hTruthDummy;
  delete hBGSubDataDummy;

  h_data_unfolded->PushCovMatrix("unfoldingCov", unfoldingCovMatrixOrig);

  c.Clear();
  unfoldingCovMatrixOrig.Draw("COLZ");
  //unfoldingCovMatrixOrig.Print();
  mnvPlotter->AddHistoTitle("unfoldingCovMatrixOrig:inside unFolding", .04);
  c.Print(pdf);

  return h_data_unfolded;

} //end UnfoldHisto

PlotUtils::MnvH2D* UnfoldHist2D_new( PlotUtils::MnvH2D* h_folded,  PlotUtils::MnvH2D* h_RECO, PlotUtils::MnvH2D* h_TRUTH,
   PlotUtils::MnvH2D* h_migration, int num_iter,  bool addSystematics, bool useSysVariatedMigrations )
{
  static MinervaUnfold::MnvUnfold unfold;
  PlotUtils::MnvH2D *h_unfolded = nullptr;
  //unfold.setUseBetterStatErrorCalc(true);



  if(!unfold.UnfoldHisto2D(h_unfolded, h_migration ,h_RECO, h_TRUTH, h_folded, num_iter, addSystematics, useSysVariatedMigrations))
    {PlotUtils::MnvH1D* h_unfolded = nullptr;
      std::cout << "****************************************************************************" << std::endl;
      std::cout << "*  THIS IS MY LOCAL FUNCTION UnfoldHist2D returns nullptr: UnFolding Failed  " << std::endl;
      std::cout << "****************************************************************************" << std::endl;


    }



  /////////////////////////////////////////////////////////////////////////////////////////
  return h_unfolded;
}
PlotUtils::MnvH2D* UnfoldHist2D_new( PlotUtils::MnvH2D* h_folded, PlotUtils::MnvH2D* h_folded_MC,  PlotUtils::MnvH2D* h_RECO, PlotUtils::MnvH2D* h_TRUTH,
   PlotUtils::MnvH2D* h_migration, int num_iter,  bool addSystematics, bool useSysVariatedMigrations)
{
  static MinervaUnfold::MnvUnfold unfold;
  MnvH2D *h_data_unfolded = new MnvH2D(*h_folded_MC);
  h_data_unfolded->SetName("h_data_unfolded");
  h_data_unfolded->AddMissingErrorBandsAndFillWithCV(*h_migration);

  if(!unfold.UnfoldHisto2D(h_data_unfolded, h_migration ,h_RECO, h_TRUTH, h_folded, num_iter, addSystematics, useSysVariatedMigrations))
    {PlotUtils::MnvH1D* h_unfolded = nullptr;
      std::cout << "****************************************************************************" << std::endl;
      std::cout << "*  THIS IS MY LOCAL FUNCTION UnfoldHist2D returns nullptr: UnFolding Failed  " << std::endl;
      std::cout << "****************************************************************************" << std::endl;


    }

  /////////////////////////////////////////////////////////////////////////////////////////
  return h_data_unfolded;
}



PlotUtils::MnvH1D* UnfoldHist( PlotUtils::MnvH1D* h_folded, PlotUtils::MnvH2D* h_migration, int num_iter )
{
  static MinervaUnfold::MnvUnfold unfold;
  PlotUtils::MnvH1D* h_unfolded = nullptr;

	bool addSystematics = true;
	bool useSysVariatedMigrations = true;
	h_migration->AddMissingErrorBandsAndFillWithCV(*h_folded);


  TMatrixD dummyCovMatrix;
  if(!unfold.UnfoldHisto( h_unfolded, dummyCovMatrix, h_migration, h_folded, RooUnfold::kBayes, num_iter, addSystematics, useSysVariatedMigrations ))
    return nullptr;

  /////////////////////////////////////////////////////////////////////////////////////////
  //No idea if this is still needed
  //Probably.  This gets your stat unfolding covariance matrix
  /*
  TMatrixD unfoldingCovMatrixOrig;
  int correctNbins;
  int matrixRows;
  TH1D* hUnfoldedDummy  = new TH1D(h_unfolded->GetCVHistoWithStatError());
  TH1D* hRecoDummy      = new TH1D(h_migration->ProjectionX()->GetCVHistoWithStatError());
  TH1D* hTruthDummy     = new TH1D(h_migration->ProjectionY()->GetCVHistoWithStatError());
  TH1D* hBGSubDataDummy = new TH1D(h_folded->GetCVHistoWithStatError());
  TH2D* hMigrationDummy = new TH2D(h_migration->GetCVHistoWithStatError());
  unfold.UnfoldHisto(hUnfoldedDummy, unfoldingCovMatrixOrig, hMigrationDummy, hRecoDummy, hTruthDummy, hBGSubDataDummy,RooUnfold::kBayes, num_iter);//Stupid RooUnfold.  This is dummy, we don't need iterations

  correctNbins=hUnfoldedDummy->fN;
  matrixRows=unfoldingCovMatrixOrig.GetNrows();
  if(correctNbins!=matrixRows){
    std::cout << "****************************************************************************" << std::endl;
    std::cout << "*  Fixing unfolding matrix size because of RooUnfold bug. From " << matrixRows << " to " << correctNbins << std::endl;
    std::cout << "****************************************************************************" << std::endl;
    // It looks like this, since the extra last two bins don't have any content
    unfoldingCovMatrixOrig.ResizeTo(correctNbins, correctNbins);
  }

  for(int i=0; i<unfoldingCovMatrixOrig.GetNrows(); ++i) unfoldingCovMatrixOrig(i,i)=0;
  delete hUnfoldedDummy;
  delete hMigrationDummy;
  delete hRecoDummy;
  delete hTruthDummy;
  delete hBGSubDataDummy;
  h_unfolded->PushCovMatrix("unfoldingCov",unfoldingCovMatrixOrig);
*/
  /////////////////////////////////////////////////////////////////////////////////////////
  return h_unfolded;
}
/////////////////////////////////////////////////////////////////////////////////////////
// Unfold Daisy
/////////////////////////////////////////////////////////////////////////////////////////
void UnfoldHist_Daisy( CrossSection_Hist_Daisy &inputCross_Hists_Daisy, int num_iter ){

	auto unfoldedDaisy_0 = UnfoldHist(inputCross_Hists_Daisy.Daisy0.h_Data_Signal, inputCross_Hists_Daisy.Daisy0.h_Mig,num_iter);
	auto unfoldedDaisy_1 = UnfoldHist(inputCross_Hists_Daisy.Daisy1.h_Data_Signal, inputCross_Hists_Daisy.Daisy1.h_Mig,num_iter);
	auto unfoldedDaisy_2 = UnfoldHist(inputCross_Hists_Daisy.Daisy2.h_Data_Signal, inputCross_Hists_Daisy.Daisy2.h_Mig,num_iter);
	auto unfoldedDaisy_3 = UnfoldHist(inputCross_Hists_Daisy.Daisy3.h_Data_Signal, inputCross_Hists_Daisy.Daisy3.h_Mig,num_iter);
	auto unfoldedDaisy_4 = UnfoldHist(inputCross_Hists_Daisy.Daisy4.h_Data_Signal, inputCross_Hists_Daisy.Daisy4.h_Mig,num_iter);
	auto unfoldedDaisy_5 = UnfoldHist(inputCross_Hists_Daisy.Daisy5.h_Data_Signal, inputCross_Hists_Daisy.Daisy5.h_Mig,num_iter);
	auto unfoldedDaisy_6 = UnfoldHist(inputCross_Hists_Daisy.Daisy6.h_Data_Signal, inputCross_Hists_Daisy.Daisy6.h_Mig,num_iter);
	auto unfoldedDaisy_7 = UnfoldHist(inputCross_Hists_Daisy.Daisy7.h_Data_Signal, inputCross_Hists_Daisy.Daisy7.h_Mig,num_iter);
	auto unfoldedDaisy_8 = UnfoldHist(inputCross_Hists_Daisy.Daisy8.h_Data_Signal, inputCross_Hists_Daisy.Daisy8.h_Mig,num_iter);
	auto unfoldedDaisy_9 = UnfoldHist(inputCross_Hists_Daisy.Daisy9.h_Data_Signal, inputCross_Hists_Daisy.Daisy9.h_Mig,num_iter);
	auto unfoldedDaisy_10 = UnfoldHist(inputCross_Hists_Daisy.Daisy10.h_Data_Signal, inputCross_Hists_Daisy.Daisy10.h_Mig,num_iter);
	auto unfoldedDaisy_11 = UnfoldHist(inputCross_Hists_Daisy.Daisy11.h_Data_Signal, inputCross_Hists_Daisy.Daisy11.h_Mig,num_iter);

	inputCross_Hists_Daisy.Daisy0.h_Data_Signal_Unfolded = unfoldedDaisy_0;
	inputCross_Hists_Daisy.Daisy1.h_Data_Signal_Unfolded = unfoldedDaisy_1;
	inputCross_Hists_Daisy.Daisy2.h_Data_Signal_Unfolded = unfoldedDaisy_2;
	inputCross_Hists_Daisy.Daisy3.h_Data_Signal_Unfolded = unfoldedDaisy_3;
	inputCross_Hists_Daisy.Daisy4.h_Data_Signal_Unfolded = unfoldedDaisy_4;
	inputCross_Hists_Daisy.Daisy5.h_Data_Signal_Unfolded = unfoldedDaisy_5;
	inputCross_Hists_Daisy.Daisy6.h_Data_Signal_Unfolded = unfoldedDaisy_6;
	inputCross_Hists_Daisy.Daisy7.h_Data_Signal_Unfolded = unfoldedDaisy_7;
	inputCross_Hists_Daisy.Daisy8.h_Data_Signal_Unfolded = unfoldedDaisy_8;
	inputCross_Hists_Daisy.Daisy9.h_Data_Signal_Unfolded = unfoldedDaisy_9;
	inputCross_Hists_Daisy.Daisy10.h_Data_Signal_Unfolded = unfoldedDaisy_10;
	inputCross_Hists_Daisy.Daisy11.h_Data_Signal_Unfolded = unfoldedDaisy_11;
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void UnfoldHist_Daisy2D( CrossSection2D_Hist_Daisy &inputCross_Hists_Daisy, int num_iter ){

	bool addSystematics = true;
	bool useSysVariatedMigrations = false;

	auto unfoldedDaisy_0 =  UnfoldHist2D_new( inputCross_Hists_Daisy.Daisy0.h_Data_Signal,inputCross_Hists_Daisy.Daisy0.h_mvnreponse_RECO,  inputCross_Hists_Daisy.Daisy0.h_mvnreponse_TRUE,  inputCross_Hists_Daisy.Daisy0.h_mvnreponse_Mig,num_iter,addSystematics, useSysVariatedMigrations);
	auto unfoldedDaisy_1 =  UnfoldHist2D_new( inputCross_Hists_Daisy.Daisy1.h_Data_Signal,inputCross_Hists_Daisy.Daisy1.h_mvnreponse_RECO,  inputCross_Hists_Daisy.Daisy1.h_mvnreponse_TRUE,  inputCross_Hists_Daisy.Daisy1.h_mvnreponse_Mig,num_iter,addSystematics, useSysVariatedMigrations);
	auto unfoldedDaisy_2 =  UnfoldHist2D_new( inputCross_Hists_Daisy.Daisy2.h_Data_Signal,inputCross_Hists_Daisy.Daisy2.h_mvnreponse_RECO,  inputCross_Hists_Daisy.Daisy2.h_mvnreponse_TRUE,  inputCross_Hists_Daisy.Daisy2.h_mvnreponse_Mig,num_iter,addSystematics, useSysVariatedMigrations);
	auto unfoldedDaisy_3 =  UnfoldHist2D_new( inputCross_Hists_Daisy.Daisy3.h_Data_Signal,inputCross_Hists_Daisy.Daisy3.h_mvnreponse_RECO,  inputCross_Hists_Daisy.Daisy3.h_mvnreponse_TRUE,  inputCross_Hists_Daisy.Daisy3.h_mvnreponse_Mig,num_iter,addSystematics, useSysVariatedMigrations);
	auto unfoldedDaisy_4 =  UnfoldHist2D_new( inputCross_Hists_Daisy.Daisy4.h_Data_Signal,inputCross_Hists_Daisy.Daisy4.h_mvnreponse_RECO,  inputCross_Hists_Daisy.Daisy4.h_mvnreponse_TRUE,  inputCross_Hists_Daisy.Daisy4.h_mvnreponse_Mig,num_iter,addSystematics, useSysVariatedMigrations);
	auto unfoldedDaisy_5 =  UnfoldHist2D_new( inputCross_Hists_Daisy.Daisy5.h_Data_Signal,inputCross_Hists_Daisy.Daisy5.h_mvnreponse_RECO,  inputCross_Hists_Daisy.Daisy5.h_mvnreponse_TRUE,  inputCross_Hists_Daisy.Daisy5.h_mvnreponse_Mig,num_iter,addSystematics, useSysVariatedMigrations);
	auto unfoldedDaisy_6 =  UnfoldHist2D_new( inputCross_Hists_Daisy.Daisy6.h_Data_Signal,inputCross_Hists_Daisy.Daisy6.h_mvnreponse_RECO,  inputCross_Hists_Daisy.Daisy6.h_mvnreponse_TRUE,  inputCross_Hists_Daisy.Daisy6.h_mvnreponse_Mig,num_iter,addSystematics, useSysVariatedMigrations);
	auto unfoldedDaisy_7 =  UnfoldHist2D_new( inputCross_Hists_Daisy.Daisy7.h_Data_Signal,inputCross_Hists_Daisy.Daisy7.h_mvnreponse_RECO,  inputCross_Hists_Daisy.Daisy7.h_mvnreponse_TRUE,  inputCross_Hists_Daisy.Daisy7.h_mvnreponse_Mig,num_iter,addSystematics, useSysVariatedMigrations);
	auto unfoldedDaisy_8 =  UnfoldHist2D_new( inputCross_Hists_Daisy.Daisy8.h_Data_Signal,inputCross_Hists_Daisy.Daisy8.h_mvnreponse_RECO,  inputCross_Hists_Daisy.Daisy8.h_mvnreponse_TRUE,  inputCross_Hists_Daisy.Daisy8.h_mvnreponse_Mig,num_iter,addSystematics, useSysVariatedMigrations);
	auto unfoldedDaisy_9 =  UnfoldHist2D_new( inputCross_Hists_Daisy.Daisy9.h_Data_Signal,inputCross_Hists_Daisy.Daisy9.h_mvnreponse_RECO,  inputCross_Hists_Daisy.Daisy9.h_mvnreponse_TRUE,  inputCross_Hists_Daisy.Daisy9.h_mvnreponse_Mig,num_iter,addSystematics, useSysVariatedMigrations);
	auto unfoldedDaisy_10 = UnfoldHist2D_new(inputCross_Hists_Daisy.Daisy10.h_Data_Signal, inputCross_Hists_Daisy.Daisy10.h_mvnreponse_RECO,inputCross_Hists_Daisy.Daisy10.h_mvnreponse_TRUE, inputCross_Hists_Daisy.Daisy10.h_mvnreponse_Mig,num_iter,addSystematics, useSysVariatedMigrations);
	auto unfoldedDaisy_11 = UnfoldHist2D_new(inputCross_Hists_Daisy.Daisy11.h_Data_Signal, inputCross_Hists_Daisy.Daisy11.h_mvnreponse_RECO,inputCross_Hists_Daisy.Daisy11.h_mvnreponse_TRUE, inputCross_Hists_Daisy.Daisy11.h_mvnreponse_Mig,num_iter,addSystematics, useSysVariatedMigrations);

	inputCross_Hists_Daisy.Daisy0.h_Data_Signal_Unfolded = unfoldedDaisy_0;
	inputCross_Hists_Daisy.Daisy1.h_Data_Signal_Unfolded = unfoldedDaisy_1;
	inputCross_Hists_Daisy.Daisy2.h_Data_Signal_Unfolded = unfoldedDaisy_2;
	inputCross_Hists_Daisy.Daisy3.h_Data_Signal_Unfolded = unfoldedDaisy_3;
	inputCross_Hists_Daisy.Daisy4.h_Data_Signal_Unfolded = unfoldedDaisy_4;
	inputCross_Hists_Daisy.Daisy5.h_Data_Signal_Unfolded = unfoldedDaisy_5;
	inputCross_Hists_Daisy.Daisy6.h_Data_Signal_Unfolded = unfoldedDaisy_6;
	inputCross_Hists_Daisy.Daisy7.h_Data_Signal_Unfolded = unfoldedDaisy_7;
	inputCross_Hists_Daisy.Daisy8.h_Data_Signal_Unfolded = unfoldedDaisy_8;
	inputCross_Hists_Daisy.Daisy9.h_Data_Signal_Unfolded = unfoldedDaisy_9;
	inputCross_Hists_Daisy.Daisy10.h_Data_Signal_Unfolded = unfoldedDaisy_10;
	inputCross_Hists_Daisy.Daisy11.h_Data_Signal_Unfolded = unfoldedDaisy_11;
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void MakeNumeratorEff_Daisy( CrossSection_Hist_Daisy &inputCross_Hists_Daisy ){

	AddErrorBands_TOEffDom(inputCross_Hists_Daisy.Daisy0);
	inputCross_Hists_Daisy.Daisy0.h_effNum->Divide(inputCross_Hists_Daisy.Daisy0.h_effNum, inputCross_Hists_Daisy.Daisy0.h_effDom);

	AddErrorBands_TOEffDom(inputCross_Hists_Daisy.Daisy1);
	inputCross_Hists_Daisy.Daisy1.h_effNum->Divide(inputCross_Hists_Daisy.Daisy1.h_effNum, inputCross_Hists_Daisy.Daisy1.h_effDom);

	AddErrorBands_TOEffDom(inputCross_Hists_Daisy.Daisy2);
	inputCross_Hists_Daisy.Daisy2.h_effNum->Divide(inputCross_Hists_Daisy.Daisy2.h_effNum, inputCross_Hists_Daisy.Daisy2.h_effDom);

	AddErrorBands_TOEffDom(inputCross_Hists_Daisy.Daisy3);
	inputCross_Hists_Daisy.Daisy3.h_effNum->Divide(inputCross_Hists_Daisy.Daisy3.h_effNum, inputCross_Hists_Daisy.Daisy3.h_effDom);

	AddErrorBands_TOEffDom(inputCross_Hists_Daisy.Daisy4);
	inputCross_Hists_Daisy.Daisy4.h_effNum->Divide(inputCross_Hists_Daisy.Daisy4.h_effNum, inputCross_Hists_Daisy.Daisy4.h_effDom);

	AddErrorBands_TOEffDom(inputCross_Hists_Daisy.Daisy5);
	inputCross_Hists_Daisy.Daisy5.h_effNum->Divide(inputCross_Hists_Daisy.Daisy5.h_effNum, inputCross_Hists_Daisy.Daisy5.h_effDom);

	AddErrorBands_TOEffDom(inputCross_Hists_Daisy.Daisy6);
	inputCross_Hists_Daisy.Daisy6.h_effNum->Divide(inputCross_Hists_Daisy.Daisy6.h_effNum, inputCross_Hists_Daisy.Daisy6.h_effDom);

	AddErrorBands_TOEffDom(inputCross_Hists_Daisy.Daisy7);
	inputCross_Hists_Daisy.Daisy7.h_effNum->Divide(inputCross_Hists_Daisy.Daisy7.h_effNum, inputCross_Hists_Daisy.Daisy7.h_effDom);

	AddErrorBands_TOEffDom(inputCross_Hists_Daisy.Daisy8);
	inputCross_Hists_Daisy.Daisy8.h_effNum->Divide(inputCross_Hists_Daisy.Daisy8.h_effNum, inputCross_Hists_Daisy.Daisy8.h_effDom);

	AddErrorBands_TOEffDom(inputCross_Hists_Daisy.Daisy9);
	inputCross_Hists_Daisy.Daisy9.h_effNum->Divide(inputCross_Hists_Daisy.Daisy9.h_effNum, inputCross_Hists_Daisy.Daisy9.h_effDom);

	AddErrorBands_TOEffDom(inputCross_Hists_Daisy.Daisy10);
	inputCross_Hists_Daisy.Daisy10.h_effNum->Divide(inputCross_Hists_Daisy.Daisy10.h_effNum, inputCross_Hists_Daisy.Daisy10.h_effDom);

	AddErrorBands_TOEffDom(inputCross_Hists_Daisy.Daisy11);
	inputCross_Hists_Daisy.Daisy11.h_effNum->Divide(inputCross_Hists_Daisy.Daisy11.h_effNum, inputCross_Hists_Daisy.Daisy11.h_effDom);

}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void MakeNumeratorEff_Daisy( CrossSection2D_Hist_Daisy &inputCross_Hists_Daisy ){

	AddErrorBands_TOEffDom(inputCross_Hists_Daisy.Daisy0);
	inputCross_Hists_Daisy.Daisy0.h_effNum->Divide(inputCross_Hists_Daisy.Daisy0.h_effNum, inputCross_Hists_Daisy.Daisy0.h_effDom);

	AddErrorBands_TOEffDom(inputCross_Hists_Daisy.Daisy1);
	inputCross_Hists_Daisy.Daisy1.h_effNum->Divide(inputCross_Hists_Daisy.Daisy1.h_effNum, inputCross_Hists_Daisy.Daisy1.h_effDom);

	AddErrorBands_TOEffDom(inputCross_Hists_Daisy.Daisy2);
	inputCross_Hists_Daisy.Daisy2.h_effNum->Divide(inputCross_Hists_Daisy.Daisy2.h_effNum, inputCross_Hists_Daisy.Daisy2.h_effDom);

	AddErrorBands_TOEffDom(inputCross_Hists_Daisy.Daisy3);
	inputCross_Hists_Daisy.Daisy3.h_effNum->Divide(inputCross_Hists_Daisy.Daisy3.h_effNum, inputCross_Hists_Daisy.Daisy3.h_effDom);

	AddErrorBands_TOEffDom(inputCross_Hists_Daisy.Daisy4);
	inputCross_Hists_Daisy.Daisy4.h_effNum->Divide(inputCross_Hists_Daisy.Daisy4.h_effNum, inputCross_Hists_Daisy.Daisy4.h_effDom);

	AddErrorBands_TOEffDom(inputCross_Hists_Daisy.Daisy5);
	inputCross_Hists_Daisy.Daisy5.h_effNum->Divide(inputCross_Hists_Daisy.Daisy5.h_effNum, inputCross_Hists_Daisy.Daisy5.h_effDom);

	AddErrorBands_TOEffDom(inputCross_Hists_Daisy.Daisy6);
	inputCross_Hists_Daisy.Daisy6.h_effNum->Divide(inputCross_Hists_Daisy.Daisy6.h_effNum, inputCross_Hists_Daisy.Daisy6.h_effDom);

	AddErrorBands_TOEffDom(inputCross_Hists_Daisy.Daisy7);
	inputCross_Hists_Daisy.Daisy7.h_effNum->Divide(inputCross_Hists_Daisy.Daisy7.h_effNum, inputCross_Hists_Daisy.Daisy7.h_effDom);

	AddErrorBands_TOEffDom(inputCross_Hists_Daisy.Daisy8);
	inputCross_Hists_Daisy.Daisy8.h_effNum->Divide(inputCross_Hists_Daisy.Daisy8.h_effNum, inputCross_Hists_Daisy.Daisy8.h_effDom);

	AddErrorBands_TOEffDom(inputCross_Hists_Daisy.Daisy9);
	inputCross_Hists_Daisy.Daisy9.h_effNum->Divide(inputCross_Hists_Daisy.Daisy9.h_effNum, inputCross_Hists_Daisy.Daisy9.h_effDom);

	AddErrorBands_TOEffDom(inputCross_Hists_Daisy.Daisy10);
	inputCross_Hists_Daisy.Daisy10.h_effNum->Divide(inputCross_Hists_Daisy.Daisy10.h_effNum, inputCross_Hists_Daisy.Daisy10.h_effDom);

	AddErrorBands_TOEffDom(inputCross_Hists_Daisy.Daisy11);
	inputCross_Hists_Daisy.Daisy11.h_effNum->Divide(inputCross_Hists_Daisy.Daisy11.h_effNum, inputCross_Hists_Daisy.Daisy11.h_effDom);

}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
std::map<int, MnvH1D*> GetDaisyUnfoldedData(CrossSection_Hist_Daisy &inputCross_Hists_Daisy){

	std::map<int, MnvH1D*> outputMap;
	outputMap.insert({0,inputCross_Hists_Daisy.Daisy0.h_Data_Signal_Unfolded});
	outputMap.insert({1,inputCross_Hists_Daisy.Daisy1.h_Data_Signal_Unfolded});
	outputMap.insert({2,inputCross_Hists_Daisy.Daisy2.h_Data_Signal_Unfolded});
	outputMap.insert({3,inputCross_Hists_Daisy.Daisy3.h_Data_Signal_Unfolded});
	outputMap.insert({4,inputCross_Hists_Daisy.Daisy4.h_Data_Signal_Unfolded});
	outputMap.insert({5,inputCross_Hists_Daisy.Daisy5.h_Data_Signal_Unfolded});
	outputMap.insert({6,inputCross_Hists_Daisy.Daisy6.h_Data_Signal_Unfolded});
	outputMap.insert({7,inputCross_Hists_Daisy.Daisy7.h_Data_Signal_Unfolded});
	outputMap.insert({8,inputCross_Hists_Daisy.Daisy8.h_Data_Signal_Unfolded});
	outputMap.insert({9,inputCross_Hists_Daisy.Daisy9.h_Data_Signal_Unfolded});
	outputMap.insert({10,inputCross_Hists_Daisy.Daisy10.h_Data_Signal_Unfolded});
	outputMap.insert({11,inputCross_Hists_Daisy.Daisy11.h_Data_Signal_Unfolded});

	return outputMap;

}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
std::map<int, MnvH2D*> GetDaisyUnfoldedData(CrossSection2D_Hist_Daisy &inputCross_Hists_Daisy){

	std::map<int, MnvH2D*> outputMap;
	outputMap.insert({0,inputCross_Hists_Daisy.Daisy0.h_Data_Signal_Unfolded});
	outputMap.insert({1,inputCross_Hists_Daisy.Daisy1.h_Data_Signal_Unfolded});
	outputMap.insert({2,inputCross_Hists_Daisy.Daisy2.h_Data_Signal_Unfolded});
	outputMap.insert({3,inputCross_Hists_Daisy.Daisy3.h_Data_Signal_Unfolded});
	outputMap.insert({4,inputCross_Hists_Daisy.Daisy4.h_Data_Signal_Unfolded});
	outputMap.insert({5,inputCross_Hists_Daisy.Daisy5.h_Data_Signal_Unfolded});
	outputMap.insert({6,inputCross_Hists_Daisy.Daisy6.h_Data_Signal_Unfolded});
	outputMap.insert({7,inputCross_Hists_Daisy.Daisy7.h_Data_Signal_Unfolded});
	outputMap.insert({8,inputCross_Hists_Daisy.Daisy8.h_Data_Signal_Unfolded});
	outputMap.insert({9,inputCross_Hists_Daisy.Daisy9.h_Data_Signal_Unfolded});
	outputMap.insert({10,inputCross_Hists_Daisy.Daisy10.h_Data_Signal_Unfolded});
	outputMap.insert({11,inputCross_Hists_Daisy.Daisy11.h_Data_Signal_Unfolded});

	return outputMap;

}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
std::map<int, MnvH1D*> GetDaisyEff(CrossSection_Hist_Daisy &inputCross_Hists_Daisy){

	std::map<int, MnvH1D*> outputMap;
	outputMap.insert({0,inputCross_Hists_Daisy.Daisy0.h_effNum});
	outputMap.insert({1,inputCross_Hists_Daisy.Daisy1.h_effNum});
	outputMap.insert({2,inputCross_Hists_Daisy.Daisy2.h_effNum});
	outputMap.insert({3,inputCross_Hists_Daisy.Daisy3.h_effNum});
	outputMap.insert({4,inputCross_Hists_Daisy.Daisy4.h_effNum});
	outputMap.insert({5,inputCross_Hists_Daisy.Daisy5.h_effNum});
	outputMap.insert({6,inputCross_Hists_Daisy.Daisy6.h_effNum});
	outputMap.insert({7,inputCross_Hists_Daisy.Daisy7.h_effNum});
	outputMap.insert({8,inputCross_Hists_Daisy.Daisy8.h_effNum});
	outputMap.insert({9,inputCross_Hists_Daisy.Daisy9.h_effNum});
	outputMap.insert({10,inputCross_Hists_Daisy.Daisy10.h_effNum});
	outputMap.insert({11,inputCross_Hists_Daisy.Daisy11.h_effNum});

	return outputMap;

}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
std::map<int, MnvH2D*> GetDaisyEff(CrossSection2D_Hist_Daisy &inputCross_Hists_Daisy){

	std::map<int, MnvH2D*> outputMap;
	outputMap.insert({0,inputCross_Hists_Daisy.Daisy0.h_effNum});
	outputMap.insert({1,inputCross_Hists_Daisy.Daisy1.h_effNum});
	outputMap.insert({2,inputCross_Hists_Daisy.Daisy2.h_effNum});
	outputMap.insert({3,inputCross_Hists_Daisy.Daisy3.h_effNum});
	outputMap.insert({4,inputCross_Hists_Daisy.Daisy4.h_effNum});
	outputMap.insert({5,inputCross_Hists_Daisy.Daisy5.h_effNum});
	outputMap.insert({6,inputCross_Hists_Daisy.Daisy6.h_effNum});
	outputMap.insert({7,inputCross_Hists_Daisy.Daisy7.h_effNum});
	outputMap.insert({8,inputCross_Hists_Daisy.Daisy8.h_effNum});
	outputMap.insert({9,inputCross_Hists_Daisy.Daisy9.h_effNum});
	outputMap.insert({10,inputCross_Hists_Daisy.Daisy10.h_effNum});
	outputMap.insert({11,inputCross_Hists_Daisy.Daisy11.h_effNum});

	return outputMap;

}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
//The final step of cross section extraction: normalize by flux, bin width, POT, and number of targets
PlotUtils::MnvH1D* normalize(PlotUtils::MnvH1D* efficiencyCorrected, PlotUtils::MnvH1D* fluxIntegral, const double nNucleons, const double POT)
{
  efficiencyCorrected->Divide(efficiencyCorrected, fluxIntegral);
  efficiencyCorrected->Scale(1./nNucleons/POT);
  efficiencyCorrected->Scale(1.e4); //Flux histogram is in m^-2, but convention is to report cm^2
  efficiencyCorrected->Scale(1., "width");

  return efficiencyCorrected;
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void ZeroDiagonal(TMatrixD &m){
  std::cout << " TRACE: enter ZeroDiagonal  "   << std::endl;
  int n = m.GetNrows();
  for (int i = 0; i < n; i++){
    m[i][i] = 0;
  }
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
TMatrixD divideCovByHists(TMatrixD m, TH2D* num, TH2D* dem)
{

  TH2D *tmp = new TH2D(*num);
  tmp->Divide(dem);
  TMatrixD ret(m);
  std::cout << "Dividing cov by hists" << num->fN << std::endl;
  for(int i=0; i<num->fN; ++i){
    for(int j=0; j<num->fN; ++j){
      int x,y,z,usex1,usey1,usex2,usey2;
      num->GetBinXYZ(i,x,y,z);
      usex1=x;
      usey1=y;
      num->GetBinXYZ(j,x,y,z);
      usex2=x;
      usey2=y;
      double eff1 = tmp->GetBinContent(usex1,usey1);
      double eff2 = tmp->GetBinContent(usex2,usey2);
      double val = eff1*eff2;
      if(val!=0)ret(i,j)=m(i,j)/(eff1*eff2);
    }
  }
  return ret;
}

/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
CrossSection_MnvH2D_Map Generate_2DCrossSection_Hist_Map(TFile& file, CrossSection_name_Map Map){
   CrossSection_MnvH2D_Map Hist_Map;
std::cout<<"Inside:Generate_2DCrossSection_Hist_Map"<<std::endl;
  std::map<CrossSectionHist, std::string>::iterator it;
  for (it = Map.begin(); it != Map.end(); it++)
  {std::cout<<"Name = "<< it->second << std::endl;
    MnvH2D *hist = Get2DHist(file, it->second );
   Hist_Map.insert(std::make_pair(it->first, hist));

    std::cout<< "name: "<< it->second<< ": hist title"<<hist->GetTitle()<<std::endl;

  }

  return Hist_Map;

}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
TF1* GetSpline(std::string material) {
	//std::assert(std::find(supported_materials.begin(), supported_materials.end(), material) != supported_materials.end(),
	//     ("Can't find material " + material + " in supported_materials").c_str());

	TFile* tf = new TFile("$MPARAMFILESROOT/data/GENIE/spline_files/gxspl-nuclear-MINERVA_Full_v2126.root");
	std::string splinename;
	if (material == "tracker" || material == "carbon") {
		splinename = "nu_mu_C12/tot_cc";
	}
	else if (material == "lead") {
		splinename = "nu_mu_Pb207/tot_cc";
	}
	else if (material == "iron") {
		splinename = "nu_mu_Fe56/tot_cc";
	}
	else if (material == "oxygen") {
		splinename = "nu_mu_O16/tot_cc";
	}
	else if (material == "helium") {
		splinename = "nu_mu_He4/tot_cc";
	}

	std::cout<<"splinename = " << splinename << std::endl;
	if(splinename == ""){std::cout<<"Wasn't able to get a spline name from material name"<<std::endl;}

	TGraph* out = GetTGraph(*tf, splinename );
	if(out == nullptr){std::cout<<"Wasn't able to th1d "<<std::endl;}

	// Convert to actual function so that integrals are smoother
	TF1* func = new TF1("func", "pol 6", 0, 100);
	std::cout<<"made Function"<< std::endl;
	//out->Fit(funcname.c_str());
	out->Fit(func,"RQ");
	return func;
}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
MnvH1D* MakeCrossSectionSpineHist( MnvH1D *originalHist, std::string material){

	MnvH1D *emptyHist = new MnvH1D(originalHist->GetName(), originalHist->GetTitle(), originalHist->GetNbinsX(), originalHist->GetXaxis()->GetXbins()->GetArray());

	TF1* SpineFunction = GetSpline(material);
	double units = 1e-38; //# converts to 1e-38cm
	units *= 1.0 / (100.0 * 100.0);

	for (int i = 1; i <= emptyHist->GetNbinsX(); ++i) {
		double binlowedge = emptyHist->GetBinLowEdge(i);
		double binwidth = emptyHist->GetBinWidth(i);

		double xsecInt = SpineFunction->Integral(binlowedge, binlowedge + binwidth);
		emptyHist->SetBinContent(i, (xsecInt / binwidth ) *units);
	}


	//emptyHist->Scale(1,"width");
	//emptyHist->Scale(units);

	return emptyHist;

}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
MnvH1D* GetCrossSection_hist(MnvH1D *originalHist, std::string material){
	MnvH1D *clonedHist =(PlotUtils::MnvH1D*)originalHist->Clone("clonedHist");
	MnvH1D * Avg_crosssection = MakeCrossSectionSpineHist(clonedHist,  material);
	Avg_crosssection->AddMissingErrorBandsAndFillWithCV(*clonedHist);
return Avg_crosssection;

}
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
MnvH1D* MakeFluxHist(MnvH1D *originalHist, std::string material, double ntargets, double potnorm){
	MnvH1D *clonedHist =(PlotUtils::MnvH1D*)originalHist->Clone("clonedHist");
	MnvH1D * Avg_crosssection = MakeCrossSectionSpineHist( clonedHist,  material);
	Avg_crosssection->AddMissingErrorBandsAndFillWithCV(*clonedHist);
	clonedHist->Divide(clonedHist, Avg_crosssection);
	clonedHist->Scale(1.0 / (ntargets * potnorm ));
	clonedHist->Scale(1.0,"width");
	return clonedHist;

}

/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_Daisy(CrossSection_Hist &Constuct_crosssection_Hists, TFile& file, char* Name){

file.cd(); // write to this Tfile

char Print_Name[2024];
sprintf(Print_Name, "%s_Data_Signal",Name);
Constuct_crosssection_Hists.h_Data_Signal ->Clone()->Write(Print_Name);
sprintf(Print_Name, "%s_RECO_Signal",Name);
  std::cout<<"writing : "<< Print_Name<<std::endl;
Constuct_crosssection_Hists.h_RECO_Signal ->Clone()->Write(Print_Name);
sprintf(Print_Name, "%s_RECO_BG",Name);
  std::cout<<"writing : "<< Print_Name<<std::endl;
Constuct_crosssection_Hists.h_RECO_BG ->Clone()->Write(Print_Name);
sprintf(Print_Name, "%s_effNum",Name);
 std::cout<<"writing : "<< Print_Name<<std::endl;
Constuct_crosssection_Hists.h_effNum ->Clone()->Write(Print_Name);
sprintf(Print_Name, "%s_effDom",Name);
  std::cout<<"writing : "<< Print_Name<<std::endl;
Constuct_crosssection_Hists.h_effDom ->Clone()->Write(Print_Name);
sprintf(Print_Name, "%s_Mig",Name);
  std::cout<<"writing : "<< Print_Name<<std::endl;
Constuct_crosssection_Hists.h_Mig ->Clone()->Write(Print_Name);

return;

}//end of function
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_2DDaisy(CrossSection2D_Hist &Constuct_crosssection_Hists, TFile& file, char* Name){

file.cd(); // write to this Tfile

char Print_Name[2024];
sprintf(Print_Name, "%s_Data_Signal",Name);
Constuct_crosssection_Hists.h_Data_Signal ->Clone()->Write(Print_Name);
sprintf(Print_Name, "%s_RECO",Name);
  std::cout<<"writing : "<< Print_Name<<std::endl;
Constuct_crosssection_Hists.h_RECO ->Clone()->Write(Print_Name);
sprintf(Print_Name, "%s_RECO_BG",Name);
  std::cout<<"writing : "<< Print_Name<<std::endl;
Constuct_crosssection_Hists.h_RECO_BG ->Clone()->Write(Print_Name);
sprintf(Print_Name, "%s_effNum",Name);
 std::cout<<"writing : "<< Print_Name<<std::endl;
Constuct_crosssection_Hists.h_effNum ->Clone()->Write(Print_Name);
sprintf(Print_Name, "%s_effDom",Name);
  std::cout<<"writing : "<< Print_Name<<std::endl;
Constuct_crosssection_Hists.h_effDom ->Clone()->Write(Print_Name);
sprintf(Print_Name, "%s_Mig",Name);
  std::cout<<"writing : "<< Print_Name<<std::endl;
Constuct_crosssection_Hists.h_mvnreponse_Mig ->Clone()->Write(Print_Name);
sprintf(Print_Name, "%s_mvnreponse_TRUE",Name);
  std::cout<<"writing : "<< Print_Name<<std::endl;
Constuct_crosssection_Hists.h_mvnreponse_TRUE ->Clone()->Write(Print_Name);
sprintf(Print_Name, "%s_mvnreponse_RECO",Name);
  std::cout<<"writing : "<< Print_Name<<std::endl;
Constuct_crosssection_Hists.h_mvnreponse_RECO ->Clone()->Write(Print_Name);


//sprintf(Print_Name, "%s_",Name);
  //std::cout<<"writing : "<< Print_Name<<std::endl;
//Constuct_crosssection_Hists.h_mvnreponse_RECO ->Clone()->Write(Print_Name);
//h_mvnreponse_TRUE


return;

}//end of function
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_Daisy_Efficiency(CrossSection_Hist &Constuct_crosssection_Hists, TFile& file, char* Name){

file.cd(); // write to this Tfile

char Print_Name[2024];
sprintf(Print_Name, "%s_Efficiency",Name);
 std::cout<<"writing : "<< Print_Name<<std::endl;
Constuct_crosssection_Hists.h_effNum ->Clone()->Write(Print_Name);

return;

}//end of function
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_2DDaisy_Efficiency(CrossSection2D_Hist &Constuct_crosssection_Hists, TFile& file, char* Name){

file.cd(); // write to this Tfile

char Print_Name[2024];
sprintf(Print_Name, "%s_Efficiency",Name);
 std::cout<<"writing : "<< Print_Name<<std::endl;
Constuct_crosssection_Hists.h_effNum ->Clone()->Write(Print_Name);

return;

}//end of function
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_Daisy_Signal(CrossSection_Hist &Constuct_crosssection_Hists, TFile& file, char* Name, char *ProcessedName){

	file.cd(); // write to this Tfile

	char Print_Name[2024];

	sprintf(Print_Name, "%s_Data_%s",Name, ProcessedName);
	Constuct_crosssection_Hists.h_Data_Signal ->Clone()->Write(Print_Name);
	sprintf(Print_Name, "%s_RECO_%s",Name, ProcessedName );
	std::cout<<"writing : "<< Print_Name<<std::endl;
	Constuct_crosssection_Hists.h_RECO_Signal ->Clone()->Write(Print_Name);

	return;

}//end of function


/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_Daisy_RECO(CrossSection_Hist &Constuct_crosssection_Hists, TFile& file, char* Name, char *ProcessedName){

	file.cd(); // write to this Tfile

	char Print_Name[2024];

	sprintf(Print_Name, "%s_RECO_%s",Name, ProcessedName );
	std::cout<<"writing : "<< Print_Name<<std::endl;
	Constuct_crosssection_Hists.h_RECO_Signal ->Clone()->Write(Print_Name);

	return;

}//end of function


/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_2DDaisy_Signal(CrossSection2D_Hist &Constuct_crosssection_Hists, TFile& file, char* Name, char *ProcessedName){

	file.cd(); // write to this Tfile

	char Print_Name[2024];

	sprintf(Print_Name, "%s_Data_%s",Name, ProcessedName);
	Constuct_crosssection_Hists.h_Data_Signal ->Clone()->Write(Print_Name);
	sprintf(Print_Name, "%s_RECO_%s",Name, ProcessedName );
	std::cout<<"writing : "<< Print_Name<<std::endl;
	Constuct_crosssection_Hists.h_RECO ->Clone()->Write(Print_Name);


	return;

}//end of function

/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_Daisy_Data(CrossSection_Hist &Constuct_crosssection_Hists, TFile& file, char* Name, char *ProcessedName){

	file.cd(); // write to this Tfile

	char Print_Name[2024];

	sprintf(Print_Name, "%s_Data_%s",Name, ProcessedName);
	Constuct_crosssection_Hists.h_Data_Signal ->Clone()->Write(Print_Name);

	return;

}//end of function
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_Daisy_UnfoldedData(CrossSection_Hist &Constuct_crosssection_Hists, TFile& file, char* Name, char *ProcessedName){

	file.cd(); // write to this Tfile

	char Print_Name[2024];

	sprintf(Print_Name, "%s_Data_%s",Name, ProcessedName);
	Constuct_crosssection_Hists.h_Data_Signal_Unfolded ->Clone()->Write(Print_Name);

	return;

}//end of function
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_2DDaisy_Data(CrossSection2D_Hist &Constuct_crosssection_Hists, TFile& file, char* Name, char *ProcessedName){

	file.cd(); // write to this Tfile

	char Print_Name[2024];

	sprintf(Print_Name, "%s_Data_%s",Name, ProcessedName);
	Constuct_crosssection_Hists.h_Data_Signal ->Clone()->Write(Print_Name);

	return;

}//end of function
//////////////////
void WritetoTFile_2DDaisy_UnfoldedData(CrossSection2D_Hist &Constuct_crosssection_Hists, TFile& file, char* Name, char *ProcessedName){

	file.cd(); // write to this Tfile

	char Print_Name[2024];

	sprintf(Print_Name, "%s_Data_%s",Name, ProcessedName);
	Constuct_crosssection_Hists.h_Data_Signal_Unfolded ->Clone()->Write(Print_Name);

	return;

}//end of function

///////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_Daisy(CrossSection_Hist_Daisy &Daisy_crosssection_Hists, TFile& file, char* Name){

	char Print_Name[2024];
	sprintf(Print_Name, "%s_Daisy0",Name);
	WritetoTFile_Daisy(Daisy_crosssection_Hists.Daisy0, file, Print_Name);

	sprintf(Print_Name, "%s_Daisy1",Name);
	WritetoTFile_Daisy(Daisy_crosssection_Hists.Daisy1, file, Print_Name);
	sprintf(Print_Name, "%s_Daisy2",Name);
	WritetoTFile_Daisy(Daisy_crosssection_Hists.Daisy2, file, Print_Name);
	sprintf(Print_Name, "%s_Daisy3",Name);
	WritetoTFile_Daisy(Daisy_crosssection_Hists.Daisy3, file, Print_Name);
	sprintf(Print_Name, "%s_Daisy4",Name);
	WritetoTFile_Daisy(Daisy_crosssection_Hists.Daisy4, file, Print_Name);
	sprintf(Print_Name, "%s_Daisy5",Name);
	WritetoTFile_Daisy(Daisy_crosssection_Hists.Daisy5, file, Print_Name);
	sprintf(Print_Name, "%s_Daisy6",Name);
	WritetoTFile_Daisy(Daisy_crosssection_Hists.Daisy6, file, Print_Name);
	sprintf(Print_Name, "%s_Daisy7",Name);
	WritetoTFile_Daisy(Daisy_crosssection_Hists.Daisy7, file, Print_Name);
	sprintf(Print_Name, "%s_Daisy8",Name);
	WritetoTFile_Daisy(Daisy_crosssection_Hists.Daisy8, file, Print_Name);
	sprintf(Print_Name, "%s_Daisy9",Name);
	WritetoTFile_Daisy(Daisy_crosssection_Hists.Daisy9, file, Print_Name);
	sprintf(Print_Name, "%s_Daisy10",Name);
	WritetoTFile_Daisy(Daisy_crosssection_Hists.Daisy10, file, Print_Name);
	sprintf(Print_Name, "%s_Daisy11",Name);
	WritetoTFile_Daisy(Daisy_crosssection_Hists.Daisy11, file, Print_Name);


return;

}//end of function
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_2DDaisy(CrossSection2D_Hist_Daisy &Daisy_crosssection_Hists, TFile& file, char* Name){

	char Print_Name[2024];
	sprintf(Print_Name, "%s_Daisy0",Name);
	WritetoTFile_2DDaisy(Daisy_crosssection_Hists.Daisy0, file, Print_Name);

	sprintf(Print_Name, "%s_Daisy1",Name);
	WritetoTFile_2DDaisy(Daisy_crosssection_Hists.Daisy1, file, Print_Name);
	sprintf(Print_Name, "%s_Daisy2",Name);
	WritetoTFile_2DDaisy(Daisy_crosssection_Hists.Daisy2, file, Print_Name);
	sprintf(Print_Name, "%s_Daisy3",Name);
	WritetoTFile_2DDaisy(Daisy_crosssection_Hists.Daisy3, file, Print_Name);
	sprintf(Print_Name, "%s_Daisy4",Name);
	WritetoTFile_2DDaisy(Daisy_crosssection_Hists.Daisy4, file, Print_Name);
	sprintf(Print_Name, "%s_Daisy5",Name);
	WritetoTFile_2DDaisy(Daisy_crosssection_Hists.Daisy5, file, Print_Name);
	sprintf(Print_Name, "%s_Daisy6",Name);
	WritetoTFile_2DDaisy(Daisy_crosssection_Hists.Daisy6, file, Print_Name);
	sprintf(Print_Name, "%s_Daisy7",Name);
	WritetoTFile_2DDaisy(Daisy_crosssection_Hists.Daisy7, file, Print_Name);
	sprintf(Print_Name, "%s_Daisy8",Name);
	WritetoTFile_2DDaisy(Daisy_crosssection_Hists.Daisy8, file, Print_Name);
	sprintf(Print_Name, "%s_Daisy9",Name);
	WritetoTFile_2DDaisy(Daisy_crosssection_Hists.Daisy9, file, Print_Name);
	sprintf(Print_Name, "%s_Daisy10",Name);
	WritetoTFile_2DDaisy(Daisy_crosssection_Hists.Daisy10, file, Print_Name);
	sprintf(Print_Name, "%s_Daisy11",Name);
	WritetoTFile_2DDaisy(Daisy_crosssection_Hists.Daisy11, file, Print_Name);


return;

}//end of function
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_Daisy_Efficiency(CrossSection_Hist_Daisy &Daisy_crosssection_Hists, TFile& file, char* Name){

	char Print_Name[2024];
	sprintf(Print_Name, "%s_Daisy0",Name);
	WritetoTFile_Daisy_Efficiency(Daisy_crosssection_Hists.Daisy0, file, Print_Name);
	sprintf(Print_Name, "%s_Daisy1",Name);
	WritetoTFile_Daisy_Efficiency(Daisy_crosssection_Hists.Daisy1, file, Print_Name);
	sprintf(Print_Name, "%s_Daisy2",Name);
	WritetoTFile_Daisy_Efficiency(Daisy_crosssection_Hists.Daisy2, file, Print_Name);
	sprintf(Print_Name, "%s_Daisy3",Name);
	WritetoTFile_Daisy_Efficiency(Daisy_crosssection_Hists.Daisy3, file, Print_Name);
	sprintf(Print_Name, "%s_Daisy4",Name);
	WritetoTFile_Daisy_Efficiency(Daisy_crosssection_Hists.Daisy4, file, Print_Name);
	sprintf(Print_Name, "%s_Daisy5",Name);
	WritetoTFile_Daisy_Efficiency(Daisy_crosssection_Hists.Daisy5, file, Print_Name);
	sprintf(Print_Name, "%s_Daisy6",Name);
	WritetoTFile_Daisy_Efficiency(Daisy_crosssection_Hists.Daisy6, file, Print_Name);
	sprintf(Print_Name, "%s_Daisy7",Name);
	WritetoTFile_Daisy_Efficiency(Daisy_crosssection_Hists.Daisy7, file, Print_Name);
	sprintf(Print_Name, "%s_Daisy8",Name);
	WritetoTFile_Daisy_Efficiency(Daisy_crosssection_Hists.Daisy8, file, Print_Name);
	sprintf(Print_Name, "%s_Daisy9",Name);
	WritetoTFile_Daisy_Efficiency(Daisy_crosssection_Hists.Daisy9, file, Print_Name);
	sprintf(Print_Name, "%s_Daisy10",Name);
	WritetoTFile_Daisy_Efficiency(Daisy_crosssection_Hists.Daisy10, file, Print_Name);
	sprintf(Print_Name, "%s_Daisy11",Name);
	WritetoTFile_Daisy_Efficiency(Daisy_crosssection_Hists.Daisy11, file, Print_Name);


return;

}//end of function
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_2D_Daisy_Efficiency(CrossSection2D_Hist_Daisy &Daisy_crosssection_Hists, TFile& file, char* Name){

	char Print_Name[2024];
	sprintf(Print_Name, "%s_Daisy0",Name);
	WritetoTFile_2DDaisy_Efficiency(Daisy_crosssection_Hists.Daisy0, file, Print_Name);
	sprintf(Print_Name, "%s_Daisy1",Name);
	WritetoTFile_2DDaisy_Efficiency(Daisy_crosssection_Hists.Daisy1, file, Print_Name);
	sprintf(Print_Name, "%s_Daisy2",Name);
	WritetoTFile_2DDaisy_Efficiency(Daisy_crosssection_Hists.Daisy2, file, Print_Name);
	sprintf(Print_Name, "%s_Daisy3",Name);
	WritetoTFile_2DDaisy_Efficiency(Daisy_crosssection_Hists.Daisy3, file, Print_Name);
	sprintf(Print_Name, "%s_Daisy4",Name);
	WritetoTFile_2DDaisy_Efficiency(Daisy_crosssection_Hists.Daisy4, file, Print_Name);
	sprintf(Print_Name, "%s_Daisy5",Name);
	WritetoTFile_2DDaisy_Efficiency(Daisy_crosssection_Hists.Daisy5, file, Print_Name);
	sprintf(Print_Name, "%s_Daisy6",Name);
	WritetoTFile_2DDaisy_Efficiency(Daisy_crosssection_Hists.Daisy6, file, Print_Name);
	sprintf(Print_Name, "%s_Daisy7",Name);
	WritetoTFile_2DDaisy_Efficiency(Daisy_crosssection_Hists.Daisy7, file, Print_Name);
	sprintf(Print_Name, "%s_Daisy8",Name);
	WritetoTFile_2DDaisy_Efficiency(Daisy_crosssection_Hists.Daisy8, file, Print_Name);
	sprintf(Print_Name, "%s_Daisy9",Name);
	WritetoTFile_2DDaisy_Efficiency(Daisy_crosssection_Hists.Daisy9, file, Print_Name);
	sprintf(Print_Name, "%s_Daisy10",Name);
	WritetoTFile_2DDaisy_Efficiency(Daisy_crosssection_Hists.Daisy10, file, Print_Name);
	sprintf(Print_Name, "%s_Daisy11",Name);
	WritetoTFile_2DDaisy_Efficiency(Daisy_crosssection_Hists.Daisy11, file, Print_Name);


return;

}//end of function
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_Daisy_Data_RECO(CrossSection_Hist_Daisy &Daisy_crosssection_Hists, TFile& file, char* Name, char *ProcessedName){

	char Print_Name[2024];
	sprintf(Print_Name, "%s_Daisy0",Name);
	WritetoTFile_Daisy_Signal(Daisy_crosssection_Hists.Daisy0, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy1",Name);
	WritetoTFile_Daisy_Signal(Daisy_crosssection_Hists.Daisy1, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy2",Name);
	WritetoTFile_Daisy_Signal(Daisy_crosssection_Hists.Daisy2, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy3",Name);
	WritetoTFile_Daisy_Signal(Daisy_crosssection_Hists.Daisy3, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy4",Name);
	WritetoTFile_Daisy_Signal(Daisy_crosssection_Hists.Daisy4, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy5",Name);
	WritetoTFile_Daisy_Signal(Daisy_crosssection_Hists.Daisy5, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy6",Name);
	WritetoTFile_Daisy_Signal(Daisy_crosssection_Hists.Daisy6, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy7",Name);
	WritetoTFile_Daisy_Signal(Daisy_crosssection_Hists.Daisy7, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy8",Name);
	WritetoTFile_Daisy_Signal(Daisy_crosssection_Hists.Daisy8, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy9",Name);
	WritetoTFile_Daisy_Signal(Daisy_crosssection_Hists.Daisy9, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy10",Name);
	WritetoTFile_Daisy_Signal(Daisy_crosssection_Hists.Daisy10, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy11",Name);
	WritetoTFile_Daisy_Signal(Daisy_crosssection_Hists.Daisy11, file, Print_Name, ProcessedName);


return;

}//end of function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_Daisy_RECO(CrossSection_Hist_Daisy &Daisy_crosssection_Hists,
	TFile& file, char* Name, char *ProcessedName){


	char Print_Name[2024];
	sprintf(Print_Name, "%s_Daisy0",Name);
	WritetoTFile_Daisy_RECO(Daisy_crosssection_Hists.Daisy0, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy1",Name);
	WritetoTFile_Daisy_RECO(Daisy_crosssection_Hists.Daisy1, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy2",Name);
	WritetoTFile_Daisy_RECO(Daisy_crosssection_Hists.Daisy2, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy3",Name);
	WritetoTFile_Daisy_RECO(Daisy_crosssection_Hists.Daisy3, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy4",Name);
	WritetoTFile_Daisy_RECO(Daisy_crosssection_Hists.Daisy4, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy5",Name);
	WritetoTFile_Daisy_RECO(Daisy_crosssection_Hists.Daisy5, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy6",Name);
	WritetoTFile_Daisy_RECO(Daisy_crosssection_Hists.Daisy6, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy7",Name);
	WritetoTFile_Daisy_RECO(Daisy_crosssection_Hists.Daisy7, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy8",Name);
	WritetoTFile_Daisy_RECO(Daisy_crosssection_Hists.Daisy8, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy9",Name);
	WritetoTFile_Daisy_RECO(Daisy_crosssection_Hists.Daisy9, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy10",Name);
	WritetoTFile_Daisy_RECO(Daisy_crosssection_Hists.Daisy10, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy11",Name);
	WritetoTFile_Daisy_RECO(Daisy_crosssection_Hists.Daisy11, file, Print_Name, ProcessedName);


return;

}//end of function
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_2DDaisy_Data_RECO(CrossSection2D_Hist_Daisy &Daisy_crosssection_Hists, TFile& file, char* Name, char *ProcessedName){
	char Print_Name[2024];
	sprintf(Print_Name, "%s_Daisy0",Name);
	WritetoTFile_2DDaisy_Signal(Daisy_crosssection_Hists.Daisy0, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy1",Name);
	WritetoTFile_2DDaisy_Signal(Daisy_crosssection_Hists.Daisy1, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy2",Name);
	WritetoTFile_2DDaisy_Signal(Daisy_crosssection_Hists.Daisy2, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy3",Name);
	WritetoTFile_2DDaisy_Signal(Daisy_crosssection_Hists.Daisy3, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy4",Name);
	WritetoTFile_2DDaisy_Signal(Daisy_crosssection_Hists.Daisy4, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy5",Name);
	WritetoTFile_2DDaisy_Signal(Daisy_crosssection_Hists.Daisy5, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy6",Name);
	WritetoTFile_2DDaisy_Signal(Daisy_crosssection_Hists.Daisy6, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy7",Name);
	WritetoTFile_2DDaisy_Signal(Daisy_crosssection_Hists.Daisy7, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy8",Name);
	WritetoTFile_2DDaisy_Signal(Daisy_crosssection_Hists.Daisy8, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy9",Name);
	WritetoTFile_2DDaisy_Signal(Daisy_crosssection_Hists.Daisy9, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy10",Name);
	WritetoTFile_2DDaisy_Signal(Daisy_crosssection_Hists.Daisy10, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy11",Name);
	WritetoTFile_2DDaisy_Signal(Daisy_crosssection_Hists.Daisy11, file, Print_Name, ProcessedName);


return;

}//end of function
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_Daisy_Data(CrossSection_Hist_Daisy &Daisy_crosssection_Hists, TFile& file, char* Name, char *ProcessedName){

	char Print_Name[2024];
	sprintf(Print_Name, "%s_Daisy0",Name);
	WritetoTFile_Daisy_Data(Daisy_crosssection_Hists.Daisy0, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy1",Name);
	WritetoTFile_Daisy_Data(Daisy_crosssection_Hists.Daisy1, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy2",Name);
	WritetoTFile_Daisy_Data(Daisy_crosssection_Hists.Daisy2, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy3",Name);
	WritetoTFile_Daisy_Data(Daisy_crosssection_Hists.Daisy3, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy4",Name);
	WritetoTFile_Daisy_Data(Daisy_crosssection_Hists.Daisy4, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy5",Name);
	WritetoTFile_Daisy_Data(Daisy_crosssection_Hists.Daisy5, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy6",Name);
	WritetoTFile_Daisy_Data(Daisy_crosssection_Hists.Daisy6, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy7",Name);
	WritetoTFile_Daisy_Data(Daisy_crosssection_Hists.Daisy7, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy8",Name);
	WritetoTFile_Daisy_Data(Daisy_crosssection_Hists.Daisy8, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy9",Name);
	WritetoTFile_Daisy_Data(Daisy_crosssection_Hists.Daisy9, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy10",Name);
	WritetoTFile_Daisy_Data(Daisy_crosssection_Hists.Daisy10, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy11",Name);
	WritetoTFile_Daisy_Data(Daisy_crosssection_Hists.Daisy11, file, Print_Name, ProcessedName);


	return;

}//end of function
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_Daisy_UnfoldedData(CrossSection_Hist_Daisy &Daisy_crosssection_Hists, TFile& file, char* Name, char *ProcessedName){


	char Print_Name[2024];
	sprintf(Print_Name, "%s_Daisy0",Name);
	WritetoTFile_Daisy_UnfoldedData(Daisy_crosssection_Hists.Daisy0, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy1",Name);
	WritetoTFile_Daisy_UnfoldedData(Daisy_crosssection_Hists.Daisy1, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy2",Name);
	WritetoTFile_Daisy_UnfoldedData(Daisy_crosssection_Hists.Daisy2, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy3",Name);
	WritetoTFile_Daisy_UnfoldedData(Daisy_crosssection_Hists.Daisy3, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy4",Name);
	WritetoTFile_Daisy_UnfoldedData(Daisy_crosssection_Hists.Daisy4, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy5",Name);
	WritetoTFile_Daisy_UnfoldedData(Daisy_crosssection_Hists.Daisy5, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy6",Name);
	WritetoTFile_Daisy_UnfoldedData(Daisy_crosssection_Hists.Daisy6, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy7",Name);
	WritetoTFile_Daisy_UnfoldedData(Daisy_crosssection_Hists.Daisy7, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy8",Name);
	WritetoTFile_Daisy_UnfoldedData(Daisy_crosssection_Hists.Daisy8, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy9",Name);
	WritetoTFile_Daisy_UnfoldedData(Daisy_crosssection_Hists.Daisy9, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy10",Name);
	WritetoTFile_Daisy_UnfoldedData(Daisy_crosssection_Hists.Daisy10, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy11",Name);
	WritetoTFile_Daisy_UnfoldedData(Daisy_crosssection_Hists.Daisy11, file, Print_Name, ProcessedName);


	return;

}//end of function
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_2DDaisy_Data(CrossSection2D_Hist_Daisy &Daisy_crosssection_Hists, TFile& file, char* Name, char *ProcessedName){

	char Print_Name[2024];
	sprintf(Print_Name, "%s_Daisy0",Name);
	 WritetoTFile_2DDaisy_Data(Daisy_crosssection_Hists.Daisy0, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy1",Name);
	 WritetoTFile_2DDaisy_Data(Daisy_crosssection_Hists.Daisy1, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy2",Name);
	 WritetoTFile_2DDaisy_Data(Daisy_crosssection_Hists.Daisy2, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy3",Name);
	 WritetoTFile_2DDaisy_Data(Daisy_crosssection_Hists.Daisy3, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy4",Name);
	 WritetoTFile_2DDaisy_Data(Daisy_crosssection_Hists.Daisy4, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy5",Name);
	 WritetoTFile_2DDaisy_Data(Daisy_crosssection_Hists.Daisy5, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy6",Name);
	 WritetoTFile_2DDaisy_Data(Daisy_crosssection_Hists.Daisy6, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy7",Name);
	 WritetoTFile_2DDaisy_Data(Daisy_crosssection_Hists.Daisy7, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy8",Name);
	WritetoTFile_2DDaisy_Data(Daisy_crosssection_Hists.Daisy8, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy9",Name);
	 WritetoTFile_2DDaisy_Data(Daisy_crosssection_Hists.Daisy9, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy10",Name);
	 WritetoTFile_2DDaisy_Data(Daisy_crosssection_Hists.Daisy10, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy11",Name);
	 WritetoTFile_2DDaisy_Data(Daisy_crosssection_Hists.Daisy11, file, Print_Name, ProcessedName);


	return;

}//end of function
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
void WritetoTFile_2DDaisy_UnfoldedData(CrossSection2D_Hist_Daisy &Daisy_crosssection_Hists, TFile& file, char* Name, char *ProcessedName){

	char Print_Name[2024];
	sprintf(Print_Name, "%s_Daisy0",Name);
	 WritetoTFile_2DDaisy_UnfoldedData(Daisy_crosssection_Hists.Daisy0, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy1",Name);
	 WritetoTFile_2DDaisy_UnfoldedData(Daisy_crosssection_Hists.Daisy1, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy2",Name);
	 WritetoTFile_2DDaisy_UnfoldedData(Daisy_crosssection_Hists.Daisy2, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy3",Name);
	 WritetoTFile_2DDaisy_UnfoldedData(Daisy_crosssection_Hists.Daisy3, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy4",Name);
	 WritetoTFile_2DDaisy_UnfoldedData(Daisy_crosssection_Hists.Daisy4, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy5",Name);
	 WritetoTFile_2DDaisy_UnfoldedData(Daisy_crosssection_Hists.Daisy5, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy6",Name);
	 WritetoTFile_2DDaisy_UnfoldedData(Daisy_crosssection_Hists.Daisy6, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy7",Name);
	 WritetoTFile_2DDaisy_UnfoldedData(Daisy_crosssection_Hists.Daisy7, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy8",Name);
	WritetoTFile_2DDaisy_UnfoldedData(Daisy_crosssection_Hists.Daisy8, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy9",Name);
	 WritetoTFile_2DDaisy_UnfoldedData(Daisy_crosssection_Hists.Daisy9, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy10",Name);
	 WritetoTFile_2DDaisy_UnfoldedData(Daisy_crosssection_Hists.Daisy10, file, Print_Name, ProcessedName);
	sprintf(Print_Name, "%s_Daisy11",Name);
	 WritetoTFile_2DDaisy_UnfoldedData(Daisy_crosssection_Hists.Daisy11, file, Print_Name, ProcessedName);


	return;

}//end of function
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
