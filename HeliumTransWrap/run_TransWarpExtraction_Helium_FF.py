import os
import sys

# How to run
# python run_TransWarpExtraction_f.py sys.argv[1] sys.argv[2] sys.argv[3] sys.argv[4] sys.argv[5] sys.argv[6] sys.argv[7]
# python run_TransWarpExtraction_f.py [NonRes1Pi] [RPA] [2p2h] [MK] [LowQ2Pi] [WarpFunc] [WarpedByVar]
# python run_TransWarpExtraction_f.py 1 1 1 0 0 0 x -> Closure test, MnvTune v1
# python run_TransWarpExtraction_f.py 1 1 1 0 1 0 x -> Closure test, MnvTune v2
outdir ="/minerva/data/users/cnguyen/UnfoldingStudies/TransWarp_Closure/closure_test_2"

#--------------------------------------


#----------------------------
# Running TransWarpExtraction
#----------------------------
#variables = ["multiplicity"]
#variables = ["Q2", "pt", "pll"]
variables = ["MuonPT_Closure"]

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
    for f in  [1, 2, 3, 5, 8, 9.5813, 10, 15]:

        output_file_name =  output_file_name_base + "_f_"+str(f)+ "_.root"
        #output_file_namex1 =  output_file_namex1_base +"_f_"+str(f)+ "_.root"
        #output_file_namex12 =  output_file_namex12_base "+"_f_"+str(f) + "_.root"
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
            + " --migration_file  " + mig_input_file_name \
            + " --migration       " + var + "_h_Mig"  \
            + " --num_iter        1,2,3,4,5,6,7,8,9,10,11,12,15,20" \
            + " --num_uni         1000" \
            + " --max_chi2        30" \
            + " --step_chi2       0.5" \
            + " --stat_scale      " + str(format(f, '.3f'))
        cmd=cmd_base + " --output_file     " + outdir +  output_file_name
        os.system(cmd)


#os.chdir(str(os.getenv("NUKECC_ANA")) + "/unfolding")
print("I'm in " + str(os.getcwd()))
print(" All done!!")
