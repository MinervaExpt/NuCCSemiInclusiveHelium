
# Neutrino Charge Current(CC) Semi-Inclusive 4Helium GIT Marco Repository 
- Author Christian Nguyen (PhD Candidate University of Florida  Graduate student )
* Email Christian2nguyen@ufl.edu

## Description
 This repository contains MAT macros for analyzing ntuples created from HeAnaTupleTool.cpp using ME(1D/2D) and LE Nu flux epochs. This Anaylsis is to Produces a Nu-4Helium Semi-Inclusive cross-section from ME and LE MINERvA data.    These Marcos uses MakeFiles to compile and Run and is based on the MAT-Minerva EventLoop prescription.  
 
## Goals 
1. Produce Self-contain Anaylsis Package to Anaylze Helium Interactions
2. Produce 1D and 2D differential cross section measurement for ME beam configuration
3. Produce 1D differential cross section measurement for LE beam configuration
4. Gain a greater understanding of the Helium nucleus through different  &nu weak interaction pathways including QE, RES, Non-RES pion production, mult-nucleon (2p2h), and DIS. Along with the smearing and that come with FSI.   

## Installation
NEW: Install all dependencies using [NuCCSemiInclusiveHelium](https://github.com/MinervaExpt/NuCCSemiInclusiveHelium).

## Dependencies
1. [MAT-PlotUtils](https://github.com/MinervaExpt/MAT)
2. [MAT-MINERvA](https://github.com/MinervaExpt/MAT-MINERvA)
2. [UnfoldUtils](https://github.com/MinervaExpt/UnfoldUtils)
3. [ROOT 6](https://root.cern.ch/building-root)

## Macro FrameWork Structure
- `/playlists`  Currently for Pathways ME Nu Data and MC root ntulples created from HeAnaTupleTool.cpp for Event Selection scripts in  'eventselection' and 'eventselection2D'     
- `/includes` -  Shared .cxx files that use a Makefile to Compile and build .o libraries. These .cxx files  contain the Binning, Cuts, plotting functions, hist Naming, The Helium CVUniverse, CryoTank Fiduical functionality, and definitions Used for the ME 1D/2D anaylsis    
- `/eventselection`  - 1D Event Selection marcos to apply cuts to make hist for Semi-Incluive Helium Event Selection for RECO MC and, TRUE MC, and DATA 
- `/eventselection2D` - 2D Event Selection marcos to apply cuts and make hist for Semi-Incluive Helium Event Selection for RECO MC and, TRUE MC, and DATA
- `/Make_Plots` - To make Plots from the Event Selection from 'eventselection' and 'eventselection2D' 
- `/Make_CrossSection` - macros to make Helium Cross Section 

### Physics Analysis 

- Interaction Model - GENIE v2.12.6 
- MINERvA-V1 tune
 * non-resonant pion reduction
 * 2p2h
 * 2p2h + neutrino Low Recoil Fit
 * Valencia RPA applied to QE  

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

### `Signal Def for Muon Neutrino Charge Current (CC) Semi-Inclusive Interaction with Helium Nuclei'  
- A Muon Neutrino CC Helium Interaction
  *  mccurrent = 1
  *  mcincoming = 14
  *  mctargetZ = 2 
- TRUE KE Detector Phase Space
  * leading Muon KE Cut 2 [GeV] < True KE < 50 [GeV]   
  * TRUE leading Muon Angle &theta &mu (wrtb)  <  12 [Degs]
- The TRUE vertex position is within the CryoTank's Fiducial Volume  
  * Fiducial Volume is smaller than the CryoTank's Volume
  *  Fiducial Volume surface is  concentric to the inner CryoTank's surface.
  * Fiducial Volume surface is defined to be 20 [mm] away from the inner CryoTank's surface 
- At least 2 TRUE Particles are in the Final State (leading Muon + leading recoil track ) 
- The non-muon track Candidates  with the greatest TRUE KE is selected as the `Leading` non-Muon FS particle (recoil System)
 * Is Not a Neutral Particle (Charge != 0)
 * TRUE Angle < 55 [Degs] (wrtb)
* TRUE particle types have TRUE KE thresholds 
 * Proton KE > 105.0 [MeV/c]
 * Pion KE > 60.0 [MeV/c]
 * Di-Muon KE > 60.0 [MeV/c]

### RECO Cuts 
* Helicity (+)
* Quality of the Muon 
 * Matched to a Minos track
 * Muon curvature significance cut (210 [mm] < Minos R < 2500 [mm])
 * Muon curvature significance cut  ($\sigma$<= - 5)
 * Muon Angle < 12 [Degs] 
 * Muon KE Cut 2 [GeV] < Muon KE < 50 [GeV] 
* Vertex Converges in Helium CyroTank  
  * CryoTank Fiducial Volume  
  *  Vertex fit of candidate tracks converges
  *  Number of tracks in the vertex > 1
* Tracks don't match to an active on voltage Veto Wall  scintillator paddle with hit activity 
*  Recoil Tracks are foward going and < 60 [Degs] 

### To Does
* add LE  
