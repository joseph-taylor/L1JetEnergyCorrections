#!/bin/bash

# To submit lots of makeResolutionPlots jobs on lxbatch system (or any bsub)
# Splits it up by eta bin
#
# Change pairs variable to full path of pairs file you want to run over
# The output files from makeResolutionPlots.py will be made in the same directory

declare -a pairsFiles=(
/afs/cern.ch/work/r/raggleto/L1JEC/CMSSW_7_4_2/src/L1Trigger/L1JetEnergyCorrections/Stage1_QCDSpring15_AVE20BX25_newRCTv2_oldCalibrated_31_Jul_15_Bristol/pairs_QCD_Pt-50to800_Spring15_AVE20BX25_Stage1_QCDSpring15_AVE20BX25_newRCTv2_oldCalibrated_31_Jul_15_Bristol_stage1_ak4_ref14to1000_l10to500_not170to300.root
# /afs/cern.ch/work/r/raggleto/L1JEC/CMSSW_7_4_2/src/L1Trigger/L1JetEnergyCorrections/Stage1_QCDSpring15_AVE20BX25_newRCTv2_calibrated_31_Jul_15_Bristol/pairs_QCD_Pt-30to800_Spring15_AVE20BX25_Stage1_QCDSpring15_AVE20BX25_newRCTv2_calibrated_31_Jul_15_Bristol_stage1_ak4_ref14to1000_l10to500.root
)

declare -a etaBins=(
0
0.348
0.695
1.044
1.392
1.74
2.172
3.0
3.5
4.0
4.5
5
) 

# update the CMSSW area in the batch script
sed -i s@CMSSW_.*\/src@${CMSSW_VERSION}/src@g resolution_batch.sh
for pairs in "${pairsFiles[@]}"
do
    fdir=`dirname $pairs`
    fname=`basename $pairs`

    echo "Using pairs file $pairs"
    echo "Writing output to directory: $fdir"

    len=${#etaBins[@]}
    len=$(( len - 1 ))
    for ((i=0;i<$len;++i));
    do
        j=$(( i + 1 ))
        etamin=${etaBins[i]}
        etamax=${etaBins[j]}
        jobname="${etamin}to${etamax}"
        outname=${fname#pairs_}
        outname=${outname%.root}
        outname="res_${outname}_${i}.root"
        echo "$jobname"
        echo "$outname"
        # bsub -q 1nh -J $jobname "sh resolution_batch.sh ${fdir}/${fname} ${fdir}/${outname} --excl --etaInd ${i}"
        # ./resolution_batch.sh ${fdir}/${fname} ${fdir}/${outname} --excl --etaInd ${i}
    done

    outname=${fname#pairs_}
    outname=${outname%.root}
    bsub -q 1nh -J allCentral "sh resolution_batch.sh ${fdir}/${fname} ${fdir}/res_${outname}_central.root --incl --central"
    # ./resolution_batch.sh ${fdir}/${fname} ${fdir}/res_${outname}_central.root --incl --central
    bsub -q 8nh -J allForward "sh resolution_batch.sh ${fdir}/${fname} ${fdir}/res_${outname}_forward.root --incl --forward"
    # ./resolution_batch.sh ${fdir}/${fname} ${fdir}/res_${outname}_forward.root --incl --forward
    bsub -q 8nh -J all "sh resolution_batch.sh ${fdir}/${fname} ${fdir}/res_${outname}_allEta.root --incl"
    # ./resolution_batch.sh ${fdir}/${fname} ${fdir}/res_${outname}_allEta.root --incl
done