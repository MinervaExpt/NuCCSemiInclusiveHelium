
# Neutrino Charge Current(CC) Semi-Inclusive 4Helium GIT Marco Repository 
- Author: Christian Nguyen (University of Florida Graduate student, PhD Candidate )
* Email: Christian2nguyen@ufl.edu

## Description
 This repository contains MAT macros for analyzing ntuples created from HeAnaTupleTool.cpp using ME(1D/2D) and LE Nu flux epochs. This Anaylsis is to Produces a Nu-4Helium Semi-Inclusive cross-section from ME and LE MINERvA data.    These Marcos uses MakeFiles to compile and Run and is based on the MAT-Minerva EventLoop prescription.  
 
## Goals 
1. Produce Self-contain Anaylsis Package to Anaylze Helium Interactions from ntuples created by HeAnaTupleTool.cpp
2. Produce 1D and 2D differential Cross-Section measurement for Nu ME beam (FHC Mode) configuration 
   - FHC Mode - Forward Horn Current, foward Focusing of positively changed Pions and Kaons that dominantly decay to Nu mu's    
3. Produce 1D differential cross section measurement for FHC LE beam configuration
4. Gain a greater understanding of the Helium nucleus through different  &nu weak interaction pathways including QE, RES, Non-RES pion production, mult-nucleon (2p2h), and DIS. Along with the smearing and that come with FSI.   

## Installation
### Dependencies
1. [MAT-PlotUtils](https://github.com/MinervaExpt/MAT)
2. [MAT-MINERvA](https://github.com/MinervaExpt/MAT-MINERvA)
2. [UnfoldUtils](https://github.com/MinervaExpt/UnfoldUtils)
3. [ROOT 6](https://root.cern.ch/building-root)

- Install Package after the dependencies using [NuCCSemiInclusiveHelium](https://github.com/MinervaExpt/NuCCSemiInclusiveHelium).

## Macro FrameWork Structure
- `/playlists`  Currently for Pathways ME Nu Data and MC root ntulples created from HeAnaTupleTool.cpp for Event Selection scripts in  'eventselection' and 'eventselection2D'     
- `/includes` -  Shared .cxx files that use a Makefile to Compile and build .o libraries. These .cxx files  contain the Binning, Cuts, plotting functions, hist Naming, The Helium CVUniverse, CryoTank Fiduical functionality, and definitions Used for the ME 1D/2D anaylsis    
- `/eventselection`  - 1D Event Selection marcos to apply cuts to make hist for Semi-Incluive Helium Event Selection for RECO MC and, TRUE MC, and DATA 
- `/eventselection2D` - 2D Event Selection marcos to apply cuts and make hist for Semi-Incluive Helium Event Selection for RECO MC and, TRUE MC, and DATA
- `/Make_Plots` - To make Plots  from the Event Selection from `/eventselection`
- `/Make_2DPlots` - To make Plots from 2D Event Selection from `/eventselection2D` 
- `/Make_CrossSection` - Macros to Extract and Plot Helium Cross Section 

### Physics Analysis 

- Interaction Model - GENIE v2.12.6 
- Non Model Weights 
  - Minso Efficiency Correction  
- MINERvA-V1 tune
  - non-resonant pion reduction
  - 2p2h
  - 2p2h + neutrino Low Recoil Fit
  - Valencia RPA applied to QE  
  - Nu Flux constraint

### Error Systematic Universes 
*  GetFluxSystematicsMap
*  GetMinervaMuonSystematicsMap
*  GetMinosMuonSystematicsMap
*  GetMuonResolutionSystematicsMap
*  GetMinosEfficiencySystematicsMap
*  GetAngleSystematicsMap
*  GetGenieSystematicsMap
*  Get2p2hSystematicsMap
*  GetRPASystematicsMap
*  GetHeliumMassMap 
*  GetVertexSmearingRandZMap 

### Signal definition: Muon Neutrino Charge Current (CC) Semi-Inclusive Interaction with Helium (4^He) Nuclei 
- A Muon Neutrino CC Helium Interaction
  *  mccurrent = 1
  *  mcincoming = 14
  *  mctargetZ = 2 
- TRUE KE Detector Phase Space
  * leading Muon KE Cut 2 [GeV] < True KE<sub>&mu;</sub> < 50 [GeV]   
  * TRUE leading Muon Angle &theta;<sub> &mu;</sub> (wrtb)  <  12 [Degs]
- The TRUE vertex position is within the CryoTank's Fiducial Volume  
  * Fiducial Volume is smaller than the CryoTank's Volume
  *  Fiducial Volume surface is  concentric to the inner CryoTank's surface.
  * Fiducial Volume surface is defined to be 20 [mm] away from the inner CryoTank's surface 
- At least 2 TRUE Particles are in the Final State (leading Muon + leading recoil track ) 
- The non-muon track Candidates  with the greatest TRUE KE is selected as the `Leading` non-Muon FS particle (recoil System)
  * Is Not a Neutral Particle (Charge != 0)
  *  &theta;<sub>2ndTrk</sub> < 55 [Degs] (wrtb)
- TRUE particle types have TRUE KE thresholds 
  * Proton KE > 105.0 [MeV/c]
  * Pion KE > 60.0 [MeV/c]
  * Di-Muon KE > 60.0 [MeV/c]

### RECO Cuts 
* Helicity (+)
* Quality of the Muon 
 * Matched to a Minos track
 * Muon curvature significance cut (210 [mm] < Minos R < 2500 [mm])
 * Muon curvature significance cut  (&sigma; <= - 5)
 * &theta;<sub> &mu;</sub> < 12 [Degs] 
 * Muon KE Cut 2 [GeV] < KE<sub>&mu;</sub> < 50 [GeV] 
* Vertex Converges in Helium CyroTank  
  *  CryoTank Fiducial Volume  
  *  Vertex fit of candidate tracks converges
  *  Number of tracks in the vertex > 1
*  Tracks don't match to an active on voltage Veto Wall  scintillator paddle with hit activity 
*  Recoil Tracks are foward going and < 60 [Degs] 

### To Does
* add LE

### NOTES
* Migration Matrix ,  Signal then RECO Cuts should be applied before filling the Hist, this is because when we unfold the data we want to correct for Smearing created from the detector instrumentation there fore we only want to "Un-Smear" the data only using the sample set of the defined Signal otherwise only applying RECO cuts would cause the "Un-Smearing operation" using a sample with  multiple Signal definitions creating an uncertainty in the systematic error       
