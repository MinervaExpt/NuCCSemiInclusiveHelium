import os
import sys

# How to run
# python run_TransWarpExtraction_f.py sys.argv[1] sys.argv[2] sys.argv[3] sys.argv[4] sys.argv[5] sys.argv[6] sys.argv[7]
# python run_TransWarpExtraction_f.py [NonRes1Pi] [RPA] [2p2h] [MK] [LowQ2Pi] [WarpFunc] [WarpedByVar]
# python run_TransWarpExtraction_f.py 1 1 1 0 0 0 x -> Closure test, MnvTune v1
# python run_TransWarpExtraction_f.py 1 1 1 0 1 0 x -> Closure test, MnvTune v2
#outdir="TransWarpStudies_210117"
outdir="TransWarpStudies_Q2DIS4_220514"
targetID= int(sys.argv[1])
targetZ= sys.argv[2]
mctype=""
if(targetID<10 and not (os.environ.get('NONUKEMC')=='true') ):
  mctype="NukeOnlyMC"
else:
  mctype="MC"
targetstr = "_t"+ str(targetID) +"_z" + str(targetZ)

#--------------------------------------


#----------------------------
# Running TransWarpExtraction 
#----------------------------
#variables = ["multiplicity"]
#variables = ["Q2", "pt", "pll"]
variables = ["x", "Enu"]
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
    print(" I'm going to run TransWarpExtraction for " + var)

    #for f in  [1, 2, 2.373465, 3, 4, 5, 6, 7, 8, 9, 10, 10.55408, 12, 15]: 
    for f in  [1, 2, 2.373465, 3, 5,  8, 10, 15]: 
        input_file_name =  str(os.getenv("HISTS"))+"/"  + str(os.getenv("NUKECC_TAG")) + "/" + playlist + "/Hists_TrueEnergy_xWarp_" + mctype+ targetstr + "_Nu_" + str(os.getenv("NUKECC_TAG")) + ".root"
        mig_input_file_name =  str(os.getenv("HISTS"))+"/"  + str(os.getenv("NUKECC_TAG")) + "/" + playlist + "/Hists_Migration" + targetstr + "_Nu_" + str(os.getenv("NUKECC_TAG")) + ".root"
        output_file_name =  str(os.getenv("HISTS")) +"/" + outdir + "/" + playlist + "/MnvGenie_"+var+"_"+"f"+str(f)+"_" + mctype+ targetstr + "_Nu_" + str(os.getenv("NUKECC_TAG")) + ".root"
        output_file_namex1 =  str(os.getenv("HISTS")) +"/" + outdir + "/" + playlist + "/MnvGenie_"+var+"_excludeBin1_"+"f"+str(f)+"_" + mctype+ targetstr + "_Nu_" + str(os.getenv("NUKECC_TAG")) + ".root"
        output_file_namex12 =  str(os.getenv("HISTS")) +"/" + outdir + "/" + playlist + "/MnvGenie_"+var+"_excludeBins1-2_"+"f"+str(f)+"_" + mctype+ targetstr + "_Nu_" + str(os.getenv("NUKECC_TAG")) + ".root"

        cmd_base = "./TransWarpExtraction" \
            + " --data_file       " + input_file_name \
            + " --data            sample_dis_reco_" + mctype + "_" + var + targetstr \
            + " --data_truth_file " + input_file_name \
            + " --data_truth      sample_true_mat_"+ mctype + "_" + var + targetstr \
            + " --reco_file       " + input_file_name \
            + " --reco            sample_dis_reco_" + mctype + "_" + var + targetstr \
            + " --truth_file      " + input_file_name \
            + " --truth           sample_true_mat_"+ mctype + "_" + var + targetstr \
            + " --migration_file  " + mig_input_file_name \
            + " --migration       migration_" + var + targetstr \
            + " --num_iter        1,2,3,4,5,6,7,8,9,10,11,12,15,20,50,100" \
            + " --num_uni         1000" \
            + " --max_chi2        30" \
            + " --step_chi2       0.5" \
            + " --stat_scale      " + str(format(f, '.3f'))
        cmd=cmd_base + " --output_file     " + output_file_name
        cmdx1=cmd_base + " --output_file     " + output_file_namex1 \
        + " --exclude_bins        1" 
        cmdx12=cmd_base + " --output_file     " + output_file_namex12 \
        + " --exclude_bins        1,2" 

        os.system(cmd)
        os.system(cmdx1)
       # os.system(cmdx12)
        
#+ " --data            sample_dis_rw_" + mctype+ "_" + var + targetstr \
 #+ " --data_truth      true_dis_rw_" + mctype + "_" + var + targetstr \
#----------------------------
#+ " --data_truth      sample_true_mat_" + var + targetstr \

#os.chdir(str(os.getenv("NUKECC_ANA")) + "/unfolding")
print("I'm in " + str(os.getcwd()))
print(" All done!!")
