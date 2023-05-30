import os
import sys

# How to run
# python run_TransWarpExtraction_f.py sys.argv[1] sys.argv[2] sys.argv[3] sys.argv[4] sys.argv[5] sys.argv[6] sys.argv[7]
# python run_TransWarpExtraction_f.py [NonRes1Pi] [RPA] [2p2h] [MK] [LowQ2Pi] [WarpFunc] [WarpedByVar]
# python run_TransWarpExtraction_f.py 1 1 1 0 0 0 x -> Closure test, MnvTune v1
# python run_TransWarpExtraction_f.py 1 1 1 0 1 0 x -> Closure test, MnvTune v2
outdir ="/minerva/data/users/cnguyen/UnfoldingStudies/TransWarp_Closure/closure_test_1_BigF/"

#--------------------------------------


#----------------------------
# Running TransWarpExtraction
#----------------------------

variables = ["Muon_2DClosure"]

input_file_name = "TransWarp_Hists.root"
mig_input_file_name = input_file_name
output_file_name_base  = "OutPutFile"
output_file_namex1_base = "OutPutFile_1_"
output_file_namex12_base = "OutPutFile_2_"



for var in variables:
    #os.chdir("/minerva/data/users/" + str(os.getenv("USER")) + "/NukeHists/" + str(os.getenv("NUKECC_TAG")) + "/" + playlist)
    #if not os.path.exists('TransWarpOutput'):
    #   print("   The folder TransWarpOutput does not exit. Creating TransWarpOutput in /minerva/data/users/" + str(os.getenv("USER")) + "/NukeHists/" + str(os.getenv("NUKECC_TAG")) + "/" + playlist)
    #   os.mkdir('TransWarpOutput')

    #os.chdir(str(os.getenv("PLOTUTILSROOT")) + "/macros")
    print(" I'm going to run TransWarpExtraction for " + var)
    # The crazy number is the MCPOT / Data
    #for f in  [1, 2, 2.373465, 3, 4, 5, 6, 7, 8, 9, 10, 10.55408, 12, 15]: # 1, 2, 2.373465, 3, 5,  8, 10, 15 not sure whats up with these s numbher esp  2.373465
    for F in  [5, 8, 10, 12, 14]:

        output_file_name =  output_file_name_base + "_BigF_"+str(F)+ "_.root"

        # old number iter 1,2,3,4,5,6,7,8,9,10,11,12,15,20,50,100"
        cmd_base = "./TransWarpExtraction" \
            + " --data_file       " + input_file_name \
            + " --data            " + var + "_data_reco" \
            + " --data_truth_file " + input_file_name \
            + " --data_truth      " + var + "_data_truth" \
            + " --reco_file       " + input_file_name \
            + " --reco            " + var + "_mc_reco" \
            + " --truth_file      " + input_file_name \
            + " --truth           " + var + "_mc_truth"  \
            + " --migration_file  " + input_file_name \
            + " --migration       " + var + "_h_Mig"  \
            + " --num_iter        1,2,3,4,5,6,7" \
            + " --num_uni         300" \
            + " --max_chi2        1000000" \
            + " --step_chi2       25" \
            + " --stat_scale      9.5813 " \
            + " --num_dim         2" \
            + " --exclude_bins 23,24,25,26,27,39,40,41,42,56,57,72" \
            + " --corr_factor      " + str(format(F, '.3f'))
        cmd=cmd_base + " --output_file     " + outdir +  output_file_name
        os.system(cmd)


#os.chdir(str(os.getenv("NUKECC_ANA")) + "/unfolding")
print("I'm in " + str(os.getcwd()))
print(" All done!!")
