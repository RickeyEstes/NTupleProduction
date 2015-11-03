from BristolAnalysis.NTupleTools.commonConfig import config

config.General.requestName = 'SingleMuon_ReReco_RunD'
config.JobType.pyCfgParams = ['isData=1','isReReco=1']
config.Data.inputDataset = '/SingleMuon/Run2015D-05Oct2015-v1/MINIAOD'
config.Data.splitting = 'EventAwareLumiBased'
config.Data.unitsPerJob = 500000
config.Data.publishDataName = 'SingleMuon_ReReco_RunD'
config.Data.lumiMask = 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions15/13TeV/Cert_246908-258750_13TeV_PromptReco_Collisions15_25ns_JSON.txt'