import os
import sys

# How to run
# python run_TransWarpExtraction_f.py sys.argv[1] sys.argv[2] sys.argv[3] sys.argv[4] sys.argv[5] sys.argv[6] sys.argv[7]
# python run_TransWarpExtraction_f.py [NonRes1Pi] [RPA] [2p2h] [MK] [LowQ2Pi] [WarpFunc] [WarpedByVar]
# python run_TransWarpExtraction_f.py 1 1 1 0 0 0 x -> Closure test, MnvTune v1
# python run_TransWarpExtraction_f.py 1 1 1 0 1 0 x -> Closure test, MnvTune v2
#outdir="TransWarpStudies_210117"
outdir="/minerva/data/users/cnguyen/UnfoldingStudies/TransWarp_Closure/closure_"
inputdir="/minerva/data/users/cnguyen/UnfoldingStudies/TransWarp_Closure/closure_test_1/"

#targetID= int(sys.argv[1])
#targetZ= sys.argv[2]
mctype=""
#if(targetID<10 and not (os.environ.get('NONUKEMC')=='true')):
#  mctype="NukeOnlyMC"
#else:
#  mctype="MC"
#targetstr = "_t"+ str(targetID) +"_z" + str(targetZ)
F= 1e10 #no correction
#F=sys.argv[3]
F = 13.8
#--------------------------------------


#----------------------------
# Running TransWarpExtraction
#----------------------------
#variables = ["multiplicity"]
#variables = ["Q2", "pt", "pll"]
variables = [ "MuonTheta_Closure" ] # "MuonE_Closure","MuonPZ_Closure", "MuonTheta_Closure",,"MuonPT_Closure"
#variables = ["Enu"]
#variables = ["x", "xi", "Q2", "Ehad", "Enu", "y", "pmu", "pll", "pt", "Emu", "ThetaMu"]
#playlist = "AllNubarME"




for var in variables:
    #os.chdir("/minerva/data/users/" + str(os.getenv("USER")) + "/NukeHists/" + str(os.getenv("NUKECC_TAG")) + "/" + playlist)
    #if not os.path.exists('TransWarpOutput'):
    #   print("   The folder TransWarpOutput does not exit. Creating TransWarpOutput in /minerva/data/users/" + str(os.getenv("USER")) + "/NukeHists/" + str(os.getenv("NUKECC_TAG")) + "/" + playlist)
    #   os.mkdir('TransWarpOutput')

    #os.chdir(str(os.getenv("PLOTUTILSROOT")) + "/macros")
    print(" I'm going to run ProcessMCSampleSizeScan for " + var)

    for F in [22]:
        #[potscale]
        #[2.373465]:
        #[1, 2, 2.373465, 3, 4, 5, 6, 7, 8, 9, 10, 12, 15]:
        #input_file_name =  str(os.getenv("HISTS"))+"/"  + str(os.getenv("NUKECC_TAG")) + "/" + playlist + "/Hists_TrueEnergy_" + mctype+ targetstr + "_Nu_" + str(os.getenv("NUKECC_TAG")) + ".root"
        #mig_input_file_name =  str(os.getenv("HISTS"))+"/"  + str(os.getenv("NUKECC_TAG")) + "/" + playlist + "/Hists_Migration" + targetstr + "_Nu_" + str(os.getenv("NUKECC_TAG")) + ".root"
        #input_file_name =  str(os.getenv("HISTS")) +"/" + outdir + "/" + playlist + "/MnvGenie_"+var+"_"+"f"+str(f)+"_" + mctype+ targetstr + "_Nu_" + str(os.getenv("NUKECC_TAG")) + ".root"
        #input_file_name =  str(os.getenv("HISTS")) +"/" + outdir + "/" + playlist + "/MnvGenie_"+var+"_excludeBin1_"+"f"+str(f)+"_" + mctype+ targetstr + "_Nu_" + str(os.getenv("NUKECC_TAG")) + ".root"
        input_file_name =   inputdir + var + "_f_" + str(9.5813) + ".root "
        cmd = "python ProcessMCSampleSizeScan.py" \
              + " --n_uni                     1000" \
              + " --iters                     1,2,3,4,5,6,7,8,10,15,20" \
              + " --input                     " + input_file_name \
              + " --uncfactor                 " + str(F) \
              + " --f_option_used_transwarp   " + str(9.5813)
        print(cmd)
        os.system(cmd)
#----------------------------
#+ " --data_truth      sample_true_mat_" + var + targetstr \

#os.chdir(str(os.getenv("NUKECC_ANA")) + "/unfolding")
print("I'm in " + str(os.getcwd()))
print(" All done!!")
