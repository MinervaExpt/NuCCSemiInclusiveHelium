#How to run
#python PlotMCSampleSizeScan_Adrian.py [variable] [ndf] [uncfactor] [file]
#python PlotMCSampleSizeScan_Zoom_f_Adrian_F.py pll 12 8.17 Hists_TransWarpOutput_MnvTunev2_MnvTunev2_pll_f4.437_t54_z82_AntiNu_v1_NX_Cal_SISInclusive_weights_TBV.root_8.170000_4.437000.txt

import os,sys
import ROOT
from ROOT import gStyle,gROOT
from ROOT import PlotUtils

ROOT.TH1.AddDirectory(False)


def sortInputFiles(filelist):
    newlist = []
    factors = []
    for f in filelist:
        fn = f.rstrip("\n")
        mcfactor = float(fn.split(".txt")[-2].split("_")[-1])
        factors.append(mcfactor)

    factors = sorted(factors)
    for f in factors:
        for fi in filelist:
            mcfactor = float(fi.split(".txt")[-2].split("_")[-1])
            if(f==mcfactor): newlist.append(fi)

    return newlist

colors = [50] #1 allowed input
styles = [1] #1 allowed input


inputfiles = sys.argv[1:]
newlist = sortInputFiles(inputfiles)
for el in newlist:
    print el.rstrip("\n")

var="PT_PZ"
Nbins = 42
NexcludedBins = 4
prefix=""
if var=="MnvGenie":
    var=newlist[0].split("_")[2]
    prefix=newlist[0].split("_")[0]
ndf= Nbins - NexcludedBins;
if var=="Enu":
    ndf=8;
excludebin=newlist[0].split("_")[2]
if excludebin=="excludeBin1":
    ndf=ndf-1
if excludebin=="excludeBins1-2":
    ndf=ndf-2
gROOT.SetBatch() #Don't display the canvas
canvas = ROOT.TCanvas("canvas", "canvas", 1200, 800)
#canvas.SetLogx()
legend = ROOT.TLegend(0.45, 0.8, 0.55, 0.86)
legend.SetTextFont(62)
legend.SetTextSize(0.03)
legend.SetFillStyle(0)
legend.SetBorderSize(0)

chi2_by_iter_by_file = []
for f in newlist:
    fn = f.rstrip("\n")
    temp_file = open(fn,"r").readlines()
    n_uni = 0
    current_iter = 0
    chi2_by_iter = []
    for l in temp_file:
        temp_line = l.split()
        chi2 = float(temp_line[0])
        iteration = int(temp_line[1])
        universe = int(temp_line[2])
        if(universe>n_uni):
            n_uni=universe+1
        if(iteration!=current_iter):
            if(current_iter!=0):
                chi2_by_iter[-1][1]/=n_uni
            chi2_by_iter.append([iteration,chi2])
            current_iter=iteration
        else:
            chi2_by_iter[-1][1]+=chi2
        if l == temp_file[-1]:
            chi2_by_iter[-1][1]/=n_uni
#            chi2_by_iter.append([iteration,chi2])

    print chi2_by_iter
    chi2_by_iter_by_file.append(chi2_by_iter)

mygraphs = []
for i in range(0,len(chi2_by_iter_by_file)):
    tmpgraph = ROOT.TGraph()
    for j,el in enumerate(chi2_by_iter_by_file[i]):
        tmpgraph.SetPoint(j,el[0],el[1])

    tmpgraph.SetLineColor(colors[i])
    tmpgraph.SetLineStyle(styles[i])
    tmpgraph.SetMarkerColor(colors[i])

    mygraphs.append(tmpgraph)

F=1e10
for i,g in enumerate(mygraphs):
    F=float(newlist[i].split("_")[-2])
    legend.AddEntry(g, "{:0.3f}".format(float(newlist[i].split(".txt")[-2].split("_")[-1])), "l")
    if(i==0):
        g.SetMarkerStyle(8)
        g.SetMarkerSize(2)
        g.Draw("APL")
        #g.SetMinimum(0.5 * float(sys.argv[2]))
        #g.SetMaximum(1.7 * float(sys.argv[2]))
        g.GetXaxis().SetTitle("(Unfolded Data:True Data) #bf{# of Iterations}")
        g.GetYaxis().SetTitle("Average #chi^{2}" + "( ndf("+str(Nbins)+") - excludedBins(" + str(NexcludedBins) + ") = "+ str(ndf) + ")" )
        g.GetXaxis().SetTitleOffset(1.15)
        g.GetXaxis().SetTitleSize(0.06)
        g.GetXaxis().SetTitleFont(62)
        g.GetXaxis().SetLabelFont(42)
        g.GetXaxis().SetLabelSize(0.05)
        g.GetYaxis().SetTitleOffset(1.2)
        g.GetYaxis().SetTitleSize(0.03)
        g.GetYaxis().SetTitleFont(62)
        g.GetYaxis().SetLabelFont(42)
        g.GetYaxis().SetLabelSize(0.05)
        g.GetYaxis().SetNdivisions(509)
        #g.GetYaxis().SetNdivisions(505)
        g.GetXaxis().CenterTitle()
        #g.GetXaxis().SetLimits(0.0, 11.0)
        g.GetYaxis().SetRangeUser(ndf - 4, ndf + 4)
        #g.GetXaxis().SetRangeUser(1, 50)
        #g.GetYaxis().SetRangeUser(0, 3)
        g.SetLineWidth(3)
        varformatted=var
        if var == "x":             varformatted = "Bjorken x"
        if var == "xi":            varformatted = "#xi"
        if var == "Q2":            varformatted = "Q^{2}"
        if var == "Ehad":          varformatted = "E_{had}"
        if var == "Enu":           varformatted = "E_{#nu}"
        if var == "y":             varformatted = "y"
        if var == "pmu":           varformatted = "p_{#mu}"
        if var == "pll":           varformatted = "p_{ll#kern[0.2]{#mu}}"
        if var == "pt":            varformatted = "p_{T#kern[0.1]{#mu}}"
        if var == "Emu":           varformatted = "E_{#mu}"
        if var == "ThetaMu":       varformatted = "#theta_{#mu}"
        if var == "W":             varformatted = "W"
        if var == "Multiplicity":  varformatted = "Multiplicity"

        #t = ROOT.TLatex(0.5, 1 - gStyle.GetPadTopMargin() + 0.04, varformatted)
        t = ROOT.TLatex(0.5, 1 - gStyle.GetPadTopMargin() + 0.04, varformatted + ", uncfactor = " + str(F) )
        t.SetNDC()
        t.SetTextSize(0.05)
        t.SetTextColor(1)
        t.SetTextFont(62)
        t.SetTextAlign(22)
        t.SetTextAngle(0)
        t.Draw()
    else:
        g.Draw("SAMEPL")

#Draw a dashed line y = 1
l = ROOT.TLine(1.0, ndf, 12.0, ndf)
#l = ROOT.TLine(1.0, ndf, 12.0, ndf)
l.SetLineStyle(7)
l.SetLineWidth(3)

l.SetLineColor(36)
l.Draw()

canvas.SetLeftMargin(0.16)
canvas.SetBottomMargin(0.16)
legend.Draw("SAME")
#targstring=newlist[0].split("MC_")[1].split("_Nu")[0]
#newlist[0]
#.split("_Nu")[0].split("MC_")[1]
#canvas.Print("Extra_UncFactor_"+targstring+"_Zoom_f_" + var + ".C")
canvas.Print("Extra_UncFactor_"+prefix+"_Zoom_f_" + var + "_22_.png")
#raw_input("DONE")
