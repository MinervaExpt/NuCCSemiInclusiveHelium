import ROOT
import array
import sys


pdg_Pi0 = 111
pdg_neutron = 2112
pdg_antineutron = -2112
pdg_Genie_bindingE = 2000000101
pdg_Sigma0 =3212
pdg_antiSigma0 = -3212
pdg_Lambda0 =3122
pdg_antiLambda0 = -3122
pdg_Nu_e = 12
pdg_Nu_mu = 14
pdg_Photon = 22
pdg_Proton = 2212
pdg_Pion_neg = -211
pdg_Pion_pos = 211

Mmu = 105.6583745/1000;

MostCommonChargedParticle = [pdg_Proton, pdg_Pion_neg, pdg_Pion_pos, -13]
NeutralPartile_cantbe2ndtrkParticle = [pdg_Pi0, pdg_neutron, pdg_antineutron, pdg_Genie_bindingE, pdg_Sigma0, pdg_antiSigma0, pdg_Lambda0, pdg_antiLambda0, pdg_Nu_e, pdg_Nu_mu, pdg_Photon]

# Cut Values
SecondTrkAngle = 55

Output_fileName = "CrossSection_G18_02a_02_11a_new10"

RootFluxFile = "/minerva/app/users/cnguyen/cmtuser/Minerva_v22r1p1Helium_GIT/CCQENuInclusiveME/ana/plot_macros_pub/CrossSections/NuWro/nuwro_flux_rw.root"

#/pnfs/minerva/persistent/Models/GENIE/Medium_Energy/FHC/v3_0_6/nuclear_trackerFlux/G18_02a_02_11a/helium/flat_GENIE_tune_G18_02a_02_11a_50M.root
#/pnfs/minerva/persistent/Models/GENIE/Medium_Energy/FHC/v3_0_6/nuclear_trackerFlux/G18_02b_02_11a/helium/flat_GENIE_tune_G18_02b_02_11a_50M.root
#/pnfs/minerva/persistent/Models/GENIE/Medium_Energy/FHC/v3_0_6/nuclear_trackerFlux/G18_10a_02_11a/helium/flat_GENIE_tune_G18_10a_02_11a_50M.root
#/pnfs/minerva/persistent/Models/GENIE/Medium_Energy/FHC/v3_0_6/nuclear_trackerFlux/G18_10b_02_11a/helium/flat_GENIE_tune_G18_10b_02_11a_50M.root


def MakeKinetic_vector(Etotal, pdg_input):
    result = []
    # Example: Add corresponding elements from list1 and list2
    for E, pdg  in zip(Etotal, pdg_input):
        particle = pdg.GetParticle(pdg)
        mass = particle.Mass()  # Mass in GeV/c^2
        KE = ROOT.TMath.Sqrt(E * E - mass * mass)
        result.append(KE)

    return result




def isHeliumLike_with2fsp_with2ndTrkMeets_KEthreshold_Angle(mytree):

    #need 1 muon and NoneNeutral 2nd Trk with angle less than 60 and if p,pi, muon+ need to meet threshold
    n_muon   = 0
    n_2ndTrkType   = 0

    #Good_2ndtrk = [pdg_Proton, pdg_Pion_neg, pdg_Pion_pos]
    #NeutralPartile_cantbe2ndtrkParticle = [pdg_Pi0, pdg_neutron, pdg_antineutron, pdg_Genie_bindingE, pdg_Sigma0, pdg_antiSigma0, pdg_Lambda0, pdg_antiLambda0, pdg_Nu_e, pdg_Nu_mu, pdg_Photon]

    nfsp = mytree.nfsp
    Efsp = mytree.E
    pdg  = mytree.pdg
    px = mytree.px
    py = mytree.py
    pz = mytree.pz

    for p in range(0,nfsp):
        if(pdg[p] in NeutralPartile_cantbe2ndtrkParticle): continue
        momomentum = ROOT.TVector3()
        momomentum.SetX(px[p])
        momomentum.SetY(py[p])
        momomentum.SetZ(pz[p])
        #momomentum.SetE(Efsp[p]);
        if(pdg[p]==13): n_muon+=1
        elif(momomentum.Theta()*180/3.1415 < SecondTrkAngle): n_2ndTrkType+=1
    if(n_muon == 1 and n_2ndTrkType > 0 ) : return True
    else : return False

def isHeliumLike_with2fsp_withAtleast1chargeParcle_Angle(mytree, Database):

    #need 1 muon and NoneNeutral 2nd Trk with angle less than 60 and if p,pi, muon+ need to meet threshold
    n_muon   = 0
    n_2ndTrkType   = 0

    nfsp = mytree.nfsp
    Efsp = mytree.E
    pdg  = mytree.pdg
    px = mytree.px
    py = mytree.py
    pz = mytree.pz

    for p in range(0,nfsp):
        if(pdg[p] in NeutralPartile_cantbe2ndtrkParticle): continue
        momomentum = ROOT.TVector3()
        momomentum.SetX(px[p])
        momomentum.SetY(py[p])
        momomentum.SetZ(pz[p])
        #momomentum.RotateX(0.05887); # rotate into Dectector space to apply the TRUE cut
        #momomentum.SetE(Efsp[p]);
        if(pdg[p]==13): n_muon+=1
        elif(pdg[p] in MostCommonChargedParticle and IsGood2ndTrkKETheshold(pdg[p], Efsp[p], Database) and IsGood2ndAngle(momomentum.Theta()*180/3.1415)): n_2ndTrkType+=1
        elif(momomentum.Theta()*180/3.1415 < SecondTrkAngle) : n_2ndTrkType+=1

    if(n_muon == 1 and n_2ndTrkType >= 1 ) : return True
    else : return False

def getMuonMomentum(mytree):
    muon_mom = ROOT.TVector3()

    nfsp = mytree.nfsp
    #Efsp = mytree.E
    pdg  = mytree.pdg
    px = mytree.px
    py = mytree.py
    pz = mytree.pz

    for p in range(0,nfsp):
        if(pdg[p]==13):
            muon_mom.SetX(px[p])
            muon_mom.SetY(py[p])
            muon_mom.SetZ(pz[p])
            #muon_mom.SetE(Efsp[p])
            break
    return muon_mom


def isInclusiveFHC(mytree):
    nu_pdg = mytree.PDGnu
    lep_pdg = mytree.PDGLep #TODO: I don't normally check the true lepton PDG
    if(nu_pdg == 14 and lep_pdg == 13): return True
    else: return False


def isGoodHeliumMuon(mytree):
    #<20 degree muon
    #2 to 50 muonE
    TotalE = mytree.ELep
    KE = ROOT.TMath.Sqrt(TotalE * TotalE - Mmu * Mmu)
    goodMuonMom   = KE > 2 and KE < 50
    angle = ROOT.TMath.ACos(mytree.CosLep) * 180.0/3.14159
    goodMuonAngle = angle > 0.0 and angle < 12.0
    # muon angle less than 12 Deg where cos(12)~ 0.97814760
    if goodMuonMom and goodMuonAngle: return True
    else: return False


def IsGood2ndTrkKETheshold(pdg, Etotal, DataBase):
    particle = DataBase.GetParticle(pdg)
    mass = particle.Mass()  # Mass in GeV/c^2
    KE_GeV = ROOT.TMath.Sqrt(Etotal * Etotal - mass * mass)
    if pdg==pdg_Proton and KE_GeV > .105 : return True
    elif abs(pdg) == pdg_Pion_pos and KE_GeV > .060 : return True
    elif pdg == -13 and KE_GeV > .060 : return True
    else : return False

def IsGood2ndAngle(angle):
    if angle < SecondTrkAngle: return True
    else: return False


#Output_fileName = sys.argv[2]
print("Trying to write to file: %s", Output_fileName)
mytree = ROOT.TChain("FlatTree_VARS")
for filename in sys.argv[1:]:
  mytree.Add(filename)

ptbins = [0.0, 0.075, 0.15, 0.25, 0.325, 0.4, 0.475, 0.55, 0.7, 0.85, 1.0, 1.25, 1.5, 2.5]

pt2Dbins = [0.0, 0.25, 0.4, 0.55, 0.7, 0.85, 2.5]

pzbins = [1.5, 3.0, 4.0, 5.0, 6.0, 8.0, 10.0, 15.0, 20.0]
pZ2Dbins = [1.5, 3.0, 4.0, 5.0, 6.0, 8.0, 10.0, 20.0]

Ebins = [2.0, 4.0, 5.0, 6.0, 8.0, 10.0, 12.0, 16.0, 20.0, 26.0, 32.0, 42.0, 50.0]
E2Dbins = [2.0, 4.0, 5.0, 6.0, 8.0, 10.0, 20.0, 50.0]

Anglebins = [0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 12.0]

mypt = ROOT.TH1D("pt","pt",len(ptbins)-1,array.array("d",ptbins))
mypz = ROOT.TH1D("pz","pz",len(pzbins)-1,array.array("d",pzbins))
myE = ROOT.TH1D("E","E",len(Ebins)-1,array.array("d",Ebins))
myAngle = ROOT.TH1D("Angle","Angle",len(Anglebins)-1,array.array("d",Anglebins))
mypzpt = ROOT.TH2D("ptpz","ptpz",len(pZ2Dbins)-1, array.array("d",pZ2Dbins), len(pt2Dbins)-1,array.array("d",pt2Dbins))
myE_angle = ROOT.TH2D("E_angle","E_angle",len(E2Dbins)-1, array.array("d",E2Dbins), len(Anglebins)-1, array.array("d",Anglebins))

inputrw = ROOT.TFile(RootFluxFile)
rwhist = inputrw.Get("flux2")

dataBase_pdg = ROOT.TDatabasePDG.Instance()

for index, e in enumerate(mytree):
#for e in mytree:
    if index % 200000 == 0 : print('Event: ' + str(index/10000) + " 10K")
    #if (isInclusiveFHC(e) and isGoodHeliumMuon(e) and isHeliumLike_with2fsp_withAtleast1chargeParcle_Angle(e, dataBase_pdg)): continue
    if not (isInclusiveFHC(e)): continue;
    if not (isGoodHeliumMuon(e)): continue;
    if not (isHeliumLike_with2fsp_withAtleast1chargeParcle_Angle(e, dataBase_pdg)): continue;

    coslep = e.CosLep
    elep= e.ELep
    fScaleFactor = e.fScaleFactor
    extra = rwhist.GetBinContent(rwhist.FindBin(e.Enu_true))
    fScaleFactor_fluxcorrected = fScaleFactor * extra
    P = ROOT.TMath.Sqrt(elep*elep-0.105*0.105)
    Pl = coslep*P
    Pt = ROOT.TMath.Sqrt(1-coslep*coslep)*P

    muonmom = getMuonMomentum(mytree)
    TotalE = mytree.ELep
    KE = ROOT.TMath.Sqrt(TotalE * TotalE - Mmu * Mmu)
    muonAngle =ROOT.TMath.ACos(coslep) * 180.0/3.14159
    #print("Muon Angle is : {}".format(muonAngle))
    #print("Muon KE is : {}".format(KE))
    mypt.Fill(Pt,fScaleFactor_fluxcorrected)
    mypz.Fill(Pl,fScaleFactor_fluxcorrected)
    mypzpt.Fill(Pl,Pt,fScaleFactor_fluxcorrected)
    myAngle.Fill(muonAngle,fScaleFactor_fluxcorrected)
    myE.Fill(KE,fScaleFactor_fluxcorrected)
    myE_angle.Fill(KE,muonAngle,fScaleFactor_fluxcorrected)

#mypt.Scale(1./mytree.GetNtrees())
#mypz.Scale(1./mytree.GetNtrees())
#mypzpt.Scale(1./mytree.GetNtrees())
#myAngle.Scale(1./mytree.GetNtrees())
#myE.Scale(1./mytree.GetNtrees())
#myE_angle.Scale(1./mytree.GetNtrees())

outFileName = Output_fileName + ".root"
myoutput = ROOT.TFile(outFileName,"RECREATE")
mypt.Write()
mypz.Write()

mypzpt.Write()
myAngle.Write()
myE.Write()
myE_angle.Write()




#Remember to bin-width normalize before plotting!
