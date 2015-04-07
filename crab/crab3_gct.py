"""
GCT-specific CRAB3 setup

Run with python crab3_gct.py
"""


from L1Trigger.L1JetEnergyCorrections.crab3_cfg import config
import L1Trigger.L1JetEnergyCorrections.samples as samples
from CRABAPI.RawCommand import crabCommand

# CHANGE ME - to make a unique indentifier for each set of jobs, e.g v2
job_append = "GCT_QCDPhys14_v2"

# CHANGE ME - select dataset(s) to run over - must be a list
datasets = samples.samples_qcd_Phys14_AVE30BX50.keys()

if __name__ == "__main__":

    # We want to put all the CRAB project directories from the tasks we submit
    # here into one common directory. That's why we need to set this parameter.
    config.General.workArea = 'l1ntuple_'+job_append

    config.JobType.psetName = '../python/l1Ntuple_GCT_cfg.py'

    for dset in datasets:
        if not dset in samples.samples.keys():
            raise KeyError("Wrong dataset name:", dset)

        # requestName will be used for name of folder inside workArea,
        # and the name of the jobs on monitoring page
        config.General.requestName = dset+"_"+job_append
        config.Data.inputDataset = samples.samples[dset].inputDataset
        config.Data.unitsPerJob = samples.samples[dset].unitsPerJob

        crabCommand('submit', config=config)