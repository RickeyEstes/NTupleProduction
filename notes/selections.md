# Requirements
1) need to store the selection used
2) need to store the individual cutsa s well as cutflow (unweighted)
3) need to be as general as possible
4) needs tagging mode
5) easy to invert a step
6) easy to repeat for different scale factors

Selections should not
1) require weights
2) apply scale factors
3) apply corrections

The workflow should be
MiniAOD => apply corrections => calculate & store weights


# current selections
 - e + jets (signal)
 "AllEvents", //
				"EventCleaningAndTrigger", //
				"ExactlyOneSignalElectron", //
				"LooseMuonVeto", //
				"LooseElectronVeto", //
				"ConversionVeto", //
				"AtLeastOneGoodJet", //
				"AtLeastTwoGoodJets", //
				"AtLeastThreeGoodJets", //
				"AtLeastFourGoodJets", //
				"AtLeastOneBtag", //
				"AtLeastTwoBtags" //
		};
	- inverted isolation
	- inverted conversion veto
 - mu + jets (signal)
 "AllEvents", //
				"EventCleaningAndTrigger", //
				"ExactlyOneSignalMuon", //
				"LooseMuonVeto", //
				"LooseElectronVeto", //
				"AtLeastOneGoodJet", //
				"AtLeastTwoGoodJets", //
				"AtLeastThreeGoodJets", //
				"AtLeastFourGoodJets", //
				"AtLeastOneBtag", //
				"AtLeastTwoBtags" //
		};
		
		
		
		
https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuidePythonTips


Filtering with JSON: https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideGoodLumiSectionsJSONFile#filterJSON_py
1) curl https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions16/13TeV/ to get available JSONs
2) regex for JSONs and 'last modified'
3) pick latest JSON.txt


import FWCore.PythonUtilities.LumiList as LumiList
process.source.lumisToProcess = LumiList.LumiList(filename = 'goodList.json').getVLuminosityBlockRange()