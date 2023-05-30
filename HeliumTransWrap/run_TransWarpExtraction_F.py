import os
import sys

# How to run
# python run_TransWarpExtraction_f.py sys.argv[1] sys.argv[2] sys.argv[3] sys.argv[4] sys.argv[5] sys.argv[6] sys.argv[7]5B
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
#variables = ["x"]
variables = ["x", "Enu"]
warp_variables=["x", "Enu", "Q2"]
#F=[0.4,0.4]
F=[4.2, 5.3]
if mctype=="NukeOnlyMC":
  F=[13.5 ,14.1]
if (mctype=="MC" and targetID<10):
  F=[3.4, 4.1]
  #F=[13.5 ,14.7]
Fex1=[4.2, 5.0]
Fex12=[4.5, 5.0]
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
    F_var=F[0]
    v=0
    if(var=="Enu"):
      F_var=F[1]
      v=1
    print(" I'm going to run TransWarpExtraction for " + var)
    
    for warpvar in warp_variables:
      #[1, 2, 2.373465, 3, 4, 5, 6, 7, 8, 9, 10, 10.55408, 11, 12, 15]: 
      input_file_name =  str(os.getenv("HISTS"))+"/"  + str(os.getenv("NUKECC_TAG")) + "/" + playlist + "/Hists_TrueEnergy_"+warpvar+"Warp_" + mctype+ targetstr + "_Nu_" + str(os.getenv("NUKECC_TAG")) + ".root"
      mig_input_file_name =  str(os.getenv("HISTS"))+"/"  + str(os.getenv("NUKECC_TAG")) + "/" + playlist + "/Hists_Migration" + targetstr + "_Nu_" + str(os.getenv("NUKECC_TAG")) + ".root"
      output_file_name_warp =  str(os.getenv("HISTS")) +"/" + outdir + "/" + playlist + "/"+warpvar+"Warp_"+var+"_F"+str(F_var)+"_" + mctype+ targetstr + "_Nu_" + str(os.getenv("NUKECC_TAG")) + ".root"
      output_file_name_mnv =  str(os.getenv("HISTS")) +"/" + outdir + "/" + playlist + "/MnvGenie_"+var+"_F"+str(F_var)+"_" + mctype+ targetstr + "_Nu_" + str(os.getenv("NUKECC_TAG")) + ".root"

      output_file_name_warpx1 =  str(os.getenv("HISTS")) +"/" + outdir + "/" + playlist + "/"+warpvar+"Warp_"+var+"_excludeBin1_F"+str(F_var)+"_" + mctype+ targetstr + "_Nu_" + str(os.getenv("NUKECC_TAG")) + ".root"
      output_file_name_mnvx1 =  str(os.getenv("HISTS")) +"/" + outdir + "/" + playlist + "/MnvGenie_"+var+"_excludeBin1_F"+str(F_var)+"_" + mctype+ targetstr + "_Nu_" + str(os.getenv("NUKECC_TAG")) + ".root"
      output_file_name_warpx12 =  str(os.getenv("HISTS")) +"/" + outdir + "/" + playlist + "/"+warpvar+"Warp_"+var+"_excludeBins1-2_F"+str(F_var)+"_" + mctype+ targetstr + "_Nu_" + str(os.getenv("NUKECC_TAG")) + ".root"
      output_file_name_mnvx12 =  str(os.getenv("HISTS")) +"/" + outdir + "/" + playlist + "/MnvGenie_"+var+"_excludeBins1-2_F"+str(F_var)+"_" + mctype+ targetstr + "_Nu_" + str(os.getenv("NUKECC_TAG")) + ".root"

      cmd_base = "./TransWarpExtraction" \
          + " --data_file       " + input_file_name \
          + " --data_truth_file " + input_file_name \
          + " --reco_file       " + input_file_name \
          + " --reco            sample_dis_reco_" + mctype + "_" + var + targetstr \
          + " --truth_file      " + input_file_name \
          + " --truth           sample_true_mat_"+ mctype + "_" + var + targetstr \
          + " --migration_file  " + mig_input_file_name \
          + " --migration       migration_" + var + targetstr \
          + " --num_iter        1,2,3,4,5,6,7,8,9,10,11,12,15,20,50,100" \
          + " --num_uni         1000" \
          + " --max_chi2        50" \
          + " --step_chi2       0.5" \
 

      cmd_mnv= cmd_base  + " --data            sample_dis_reco_" + mctype + "_" + var + targetstr \
               + " --data_truth      sample_true_mat_"+ mctype + "_" + var + targetstr \
               + " --corr_factor    "+str(F_var)\
               + " --output_file     " + output_file_name_mnv
      cmd_warp= cmd_base + " --data            sample_dis_rw_" + mctype+ "_" + var + targetstr \
                + " --data_truth      true_dis_rw_" + mctype + "_" + var + targetstr \
                + " --corr_factor    "+str(F_var)\
                + " --output_file     " + output_file_name_warp

      cmd_mnv_x1= cmd_base  + " --data            sample_dis_reco_" + mctype + "_" + var + targetstr \
               + " --data_truth      sample_true_mat_"+ mctype + "_" + var + targetstr \
               + " --corr_factor    "+str(Fex1[v])\
               + " --exclude_bins     1"\
               + " --output_file     " + output_file_name_mnvx1
      cmd_warp_x1= cmd_base + " --data            sample_dis_rw_" + mctype+ "_" + var + targetstr \
                + " --data_truth      true_dis_rw_" + mctype + "_" + var + targetstr \
                + " --corr_factor    "+str(Fex1[v])\
                + " --exclude_bins    1"\
                + " --output_file     " + output_file_name_warpx1

      cmd_mnv_x12= cmd_base  + " --data            sample_dis_reco_" + mctype + "_" + var + targetstr \
               + " --data_truth      sample_true_mat_"+ mctype + "_" + var + targetstr \
               + " --corr_factor    "+str(Fex12[v])\
               + " --exclude_bins     1,2"\
               + " --output_file     " + output_file_name_mnvx12
      cmd_warp_x12= cmd_base + " --data            sample_dis_rw_" + mctype+ "_" + var + targetstr \
                + " --data_truth      true_dis_rw_" + mctype + "_" + var + targetstr \
                + " --corr_factor    "+str(Fex12[v])\
                + " --exclude_bins    1,2"\
                + " --output_file     " + output_file_name_warpx12

      #+ " --stat_scale      " + str(format(f, '.3f'))
      os.system(cmd_warp_x1)
      os.system(cmd_warp)
      os.system(cmd_warp_x12)
    os.system(cmd_mnv)
    os.system(cmd_mnv_x1)
    os.system(cmd_mnv_x12)
#----------------------------
#+ " --data_truth      sample_true_mat_" + var + targetstr \

#os.chdir(str(os.getenv("NUKECC_ANA")) + "/unfolding")
print("I'm in " + str(os.getcwd()))
print(" All done!!")
