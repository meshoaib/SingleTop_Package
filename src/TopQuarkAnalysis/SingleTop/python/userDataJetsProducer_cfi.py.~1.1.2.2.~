import FWCore.ParameterSet.Config as cms

topJetsPF = cms.EDProducer(
    "SingleTopJetsProducer",
    electronsSrc = cms.InputTag("selectedPatElectrons"),
    src = cms.InputTag("selectedPatJets"),
    cut = cms.string('pt >  20 & abs(eta) < 5.'),
    puFullDiscriminant = cms.InputTag("puJetMva","fullDiscriminant"),
    puFullID  = cms.InputTag("puJetMva","fullId"),
    puChargedDiscriminant = cms.InputTag("puJetMvaChs","fullDiscriminant"),
    puChargedID  = cms.InputTag("puJetMvaChs","fullId"),
    puIDVariables  = cms.InputTag("puJetId"),
    removeOverlap = cms.untracked.bool(False),
    isData = cms.untracked.bool(False),
#    JESUncertaintiesPath = cms.FileInPath("TopQuarkAnalysis/SingleTop/data/Fall12_V7_DATA_UncertaintySources_AK5PFchs.txt")
    JESUncertaintiesPath = cms.FileInPath("TopQuarkAnalysis/SingleTop/data/START53_V22_Uncertainty_AK5PFchs.txt")
)

