import FWCore.ParameterSet.Config as cms

userDataMuons = cms.EDProducer("SingleTopMuonProducer",
  src = cms.InputTag("selectedPatMuons"),
  cut = cms.string('pt >  20 & abs(eta) < 2.4'),
  rho = cms.InputTag("kt6PFJets","rho"),
)

userDataElectrons = cms.EDProducer("SingleTopElectronProducer",
  src = cms.InputTag("selectedPatElectrons"),
  cut = cms.string('pt >  20 & abs(eta) < 2.4'),
  rho = cms.InputTag("kt6PFJets","rho"),
)
