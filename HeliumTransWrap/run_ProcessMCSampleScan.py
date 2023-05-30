import os
import sys

# How to run
# python run_TransWarpExtraction_f.py sys.argv[1] sys.argv[2] sys.argv[3] sys.argv[4] sys.argv[5] sys.argv[6] sys.argv[7]
# python run_TransWarpExtraction_f.py [NonRes1Pi] [RPA] [2p2h] [MK] [LowQ2Pi] [WarpFunc] [WarpedByVar]
# python run_TransWarpExtraction_f.py 1 1 1 0 0 0 x -> Closure test, MnvTune v1
# python run_TransWarpExtraction_f.py 1 1 1 0 1 0 x -> Closure test, MnvTune v2
#outdir="TransWarpStudies_210117"
outdir="/minerva/data/users/cnguyen/UnfoldingStudies/TransWarp_Closure/"

F= 1e10 #no correction
#F=sys.argv[3]
#--------------------------------------


#----------------------------
# Running TransWarpExtraction
#----------------------------
#variables = ["multiplicity"]
#variables = ["Q2", "pt", "pll"]
variables = ["MuonPT_Closure"]
#variables = ["x"]
#variables = ["x", "xi", "Q2", "Ehad", "Enu", "y", "pmu", "pll", "pt", "Emu", "ThetaMu"]
#playlist = "AllNubarME"
playlist = "AllNuME"

#if( playlist == "AllNubarME" ):
#    label = "AntiNu"
#else:
label = "Nu"

for var in variables:
    #os.chdir("/minerva/data/users/" + str(os.getenv("USER")) + "/NukeHists/" + str(os.getenv("NUKECC_TAG")) + "/" + playlist)
    #if not os.path.exists('TransWarpOutput'):
    #   print("   The folder TransWarpOutput does not exit. Creating TransWarpOutput in /minerva/data/users/" + str(os.getenv("USER")) + "/NukeHists/" + str(os.getenv("NUKECC_TAG")) + "/" + playlist)
    #   os.mkdir('TransWarpOutput')

    #os.chdir(str(os.getenv("PLOTUTILSROOT")) + "/macros")
    print(" I'm going to run ProcessMCSampleSizeScan for " + var)

    #for f in [1, 2, 2.373465, 3, 4, 5, 6, 7, 8, 9, 10, 10.55408, 12, 15]:
    for f in  [1, 2, 3, 5, 8, 9.5813, 10, 15]:
        input_file_name =   outdir + "closure_test_1OutPutFile_f_" + str(f) + "_.root"

        cmd = "python ProcessMCSampleSizeScan.py" \
              + " --n_uni                     1000" \
              + " --iters                     1,2,3,4,5,6,7,8,9,10,11,12,15,20,50,100" \
              + " --input                     " + input_file_name \
              + " --uncfactor                 " + str(F) \
              + " --f_option_used_transwarp   " + str(format(f, '.3f'))
        print(cmd)
        os.system(cmd)
#----------------------------
#+ " --data_truth      sample_true_mat_" + var + targetstr \

#os.chdir(str(os.getenv("NUKECC_ANA")) + "/unfolding")
print("I'm in " + str(os.getcwd()))
print(" All done!!")
