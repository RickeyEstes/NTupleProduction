from BristolAnalysis.NTupleTools.commonConfig import config

config.General.requestName = 'SingleElectron_PromptReco'
config.JobType.pyCfgParams = ['isData=1']
config.Data.inputDataset = '/SingleElectron/Run2015B-PromptReco-v1/MINIAOD'
config.Data.splitting = 'EventAwareLumiBased'
config.Data.runRange = '251643-251883'
config.Data.unitsPerJob = 250000
config.Data.publishDataName = 'SingleElectron_PromptReco'
config.Data.lumiMask = '/hdfs/TopQuarkGroup/run2/json/Cert_246908-251883_13TeV_PromptReco_Collisions15_JSON_v2.txt'
