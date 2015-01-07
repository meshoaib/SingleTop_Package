import FWCore.ParameterSet.Config as cms

from TopQuarkAnalysis.SingleTop.SingleTopProducers_cff import *
from TopQuarkAnalysis.SingleTop.SingleTopSelectors_cff import *

#Veto leptons definition
muVetoCut = cms.string(" (isGlobalMuon || isTrackerMuon) " +
                       "& pt > 10 & abs(eta) < 2.5 " +
                       "& userFloat(\"DeltaCorrectedIso\") <0.2 ")

eleVetoCut = cms.string(" ecalDrivenMomentum.pt > 20 " +
                        "& abs(eta) < 2.5 " +
                        "& userFloat(\"RhoCorrectedIso\") <0.15" +
                        "& userFloat(\"PassesVetoID\") >0.0"
                        )

eleVetoCutMVA = cms.string(" ecalDrivenMomentum.pt > 20" +
                           "& abs(eta) < 2.5 && userFloat(\"RhoCorrectedIso\") <0.15" +
                           "& electronID('mvaTrigV0') >0.0")

#Tight leptons selection criteria
eleTightCut = cms.string(" ecalDrivenMomentum.pt > 30  && abs(eta)<2.5" +
                         "& ( abs(superCluster.eta)> 1.5660 || abs(superCluster.eta)<1.4442)" +
                         "& passConversionVeto")

muTightCut = cms.string(" pt > 26 & isGlobalMuon && isPFMuon & abs(eta) < 2.1 && normChi2 < 10 && track.hitPattern.trackerLayersWithMeasurement>5 "+
                        "& numberOfMatchedStations() > 1 && innerTrack.hitPattern.numberOfValidPixelHits > 0 " +
                        "& globalTrack.hitPattern.numberOfValidMuonHits > 0")
#Jet definition
jetLooseCut = cms.string(" numberOfDaughters()>1 & pt()> 20 && abs(eta())<5 " +
                         " & ((abs(eta())>=2.4) || ( chargedHadronEnergyFraction() > 0 & chargedMultiplicity()>0 & chargedEmEnergyFraction()<0.99))"+
                         " & neutralEmEnergyFraction() < 0.99 & neutralHadronEnergyFraction() < 0.99 "  )

#Requirement on the number of leptons in the event
#Loose: at least 1 tight lepton
minTightLeptons = cms.untracked.int32(1)
maxTightLeptons = cms.untracked.int32(99)

#Number of leptons that survive loose cuts and do not overlap with tight leptons
minVetoLeptons = cms.untracked.int32(0)
maxVetoLeptons = cms.untracked.int32(99)















### MC details that do not influence the selection  ###

#Check to see if it is signal channel ( MC only )
isMCSingleTopTChannel = cms.untracked.bool(False)

#definition: Leptons Veto for bet
vetoElectrons.cut =  eleVetoCut
vetoElectronsMVA.cut =  eleVetoCutMVA
vetoMuons.cut = muVetoCut

tightElectrons.cut =  eleTightCut
tightMuons.cut = muTightCut

tightElectronsZeroIso.cut =  eleTightCut
tightMuonsZeroIso.cut = muTightCut

#definition: Jets Loose
topJetsPF.cut = jetLooseCut

#tight leptons
countLeptons.minNumberLoose = minVetoLeptons
countLeptons.maxNumberLoose = maxVetoLeptons

#veto leptons
countLeptons.minNumberTight = minTightLeptons
countLeptons.maxNumberTight = maxTightLeptons

#QCD leptons 
countLeptons.minNumberQCD = minTightLeptons
countLeptons.maxNumberQCD = maxTightLeptons

#Count leptons returns:
# ( ( minTight < nTightLeptons < maxTight ) AND ( minLoose < nLooseLeptons < maxLoose) ) OR ( minQCD < nQCDLeptons < maxQCD )
