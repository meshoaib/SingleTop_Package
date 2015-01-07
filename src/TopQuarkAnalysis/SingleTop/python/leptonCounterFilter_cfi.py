import FWCore.ParameterSet.Config as cms

countLeptons = cms.EDFilter(
    "SingleTopLeptonCounter",
    looseMuons = cms.InputTag("vetoMuons"),
    looseElectrons = cms.InputTag("vetoElectrons"),
    tightMuons = cms.InputTag("tightMuons"),
    tightElectrons = cms.InputTag("tightElectrons"),
    qcdMuons = cms.InputTag("tightMuonsZeroIso"),
    qcdElectrons = cms.InputTag("tightElectronsZeroIso"),
    minNumberTight = cms.untracked.int32(1),
    maxNumberTight = cms.untracked.int32(1),
    minNumberLoose = cms.untracked.int32(0),
    maxNumberLoose = cms.untracked.int32(0),
    minNumberQCD = cms.untracked.int32(1),
    maxNumberQCD = cms.untracked.int32(1),
    rejectOverlap = cms.untracked.bool(True),
    doQCD = cms.untracked.bool(True)
)

