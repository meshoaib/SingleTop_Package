import FWCore.ParameterSet.Config as cms

topMETsPF = cms.EDProducer("SingleTopMETsProducer",
                         electronsSrc = cms.InputTag("selectedPatElectrons"),
                         metsSrc = cms.InputTag("patType1CorrectedPFMet"),
                         metsUnclUpSrc = cms.InputTag("patType1CorrectedPFMetUnclusteredEnUp"),
                         metsUnclDownSrc = cms.InputTag("patType1CorrectedPFMetUnclusteredEnDown"),
                         jetsSrc = cms.InputTag("selectedPatJets"),
                         muonsSrc = cms.InputTag("selectedPatMuons"),
                         tausSrc = cms.InputTag("selectedPatTaus"),
                         photonsSrc = cms.InputTag("selectedPatPhotons"),
                         pfCandsNotInJetSrc = cms.InputTag("pfCandsNotInJet"),
                         isData = cms.untracked.bool(False),
                         addExternalUnclusteredMET = cms.untracked.bool(False),
                         JESUncertaintiesPath = cms.FileInPath("TopQuarkAnalysis/SingleTop/data/Fall12_V7_DATA_UncertaintySources_AK5PFchs.txt")
#                         JESUncertaintiesPath = cms.FileInPath("TopQuarkAnalysis/SingleTop/data/START53_V22_Uncertainty_AK5PFchs.txt")
                         )

