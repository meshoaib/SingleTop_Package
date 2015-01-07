import FWCore.ParameterSet.Config as cms

TreesEle = cms.EDAnalyzer('SingleTopSystematicsTreesDumper',                              
#General Info
#systematics = cms.untracked.vstring("BTagUp","BTagDown","MisTagUp","MisTagDown","JESUp","JESDown","UnclusteredMETUp","UnclusteredMETDown","PUUp","PUDown"),
#systematics = cms.untracked.vstring("JESUp","JESDown","UnclusteredMETUp","UnclusteredMETDown","JERUp","JERDown"),
#systematics = cms.untracked.vstring("JESUp","JESDown","JERUp","JERDown"),

systematics = cms.untracked.vstring("JESUp","JESDown","UnclusteredMETUp","UnclusteredMETDown","JERUp","JERDown"),
#systematics = cms.untracked.vstring("JESUp","JESDown","JERUp","JERDown"),

#systematics = cms.untracked.vstring("UnclusteredMETUp","UnclusteredMETDown"),
#systematics = cms.untracked.vstring(""),
#rateSystematics = cms.untracked.vstring("WLightRateUp",                                        "WLightRateDown",                                        "TTBarRateUp",                                        "Ttbarratedown ",                                        "WHFRateUp",                                        "WHFRateDown"),
doPU = cms.untracked.bool(True),
doMCTruth = cms.untracked.bool(True),
doFullMCTruth = cms.untracked.bool(True),
doResol  = cms.untracked.bool(False),

doTopPtReweighting  = cms.untracked.bool(True),
doTopBestMass = cms.untracked.bool(True),
doAsymmetricPtCut = cms.untracked.bool(False),  # DISCUSS

algo  = cms.untracked.string("CSVT"),
#algo  = cms.untracked.string("TCHPT"),

takeBTagSFFromDB = cms.untracked.bool(False),
#dataPUFile = cms.untracked.string("pileUpDistr.root"),
#mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
#puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
#mode = cms.untracked.string("pt"),
#maxPtCut = cms.untracked.double("45"),

#x1/x2
x1 = cms.InputTag("PDFInfo","x1"),
x2 = cms.InputTag("PDFInfo","x2"),
id1 = cms.InputTag("PDFInfo","id1"),
id2 = cms.InputTag("PDFInfo","id2"),
scalePDF = cms.InputTag("PDFInfo","scalePDF"),
doPDF =cms.untracked.bool(True),

channelInfo = cms.PSet(
    crossSection = cms.untracked.double(20.93),
    channel = cms.untracked.string("TChannel"),
    originalEvents = cms.untracked.double(480000),
    finalLumi = cms.untracked.double(14.5),
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    loosePtCut = cms.untracked.double(30.0),#Default 30.0 GeV
    RelIsoCut = cms.untracked.double(0.1),
    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),

    ),

#Leptons
#leptonsEta = cms.InputTag("nTupleElectrons","tightElectronsPFEta"),  
#leptonsPt = cms.InputTag("nTupleElectrons","tightElectronsPFPt"),  
#leptonsPhi = cms.InputTag("nTupleElectrons","tightElectronsPFPhi"),  
#leptonsEnergy = cms.InputTag("nTupleElectrons","tightElectronsPFE"),  

leptonsEta = cms.InputTag("nTupleElectrons","tightElectronsEta"),  
leptonsPt = cms.InputTag("nTupleElectrons","tightElectronsPt"),  
leptonsPhi = cms.InputTag("nTupleElectrons","tightElectronsPhi"),  
leptonsEnergy = cms.InputTag("nTupleElectrons","tightElectronsE"),  

leptonsCharge = cms.InputTag("nTupleElectrons","tightElectronsCharge"),  

leptonsDeltaCorrectedRelIso = cms.InputTag("nTupleElectrons","tightElectronsPFDeltaCorrectedRelIso"),  
leptonsRhoCorrectedRelIso = cms.InputTag("nTupleElectrons","tightElectronsPFRhoCorrectedRelIso"),  

qcdLeptonsDeltaCorrectedRelIso = cms.InputTag("nTupleQCDElectrons","QCDElectronsPFDeltaCorrectedRelIso"),  
qcdLeptonsRhoCorrectedRelIso = cms.InputTag("nTupleQCDElectrons","QCDElectronsPFRhoCorrectedRelIso"),  

#leptonsDB = cms.InputTag("nTupleElectrons","tightElectronsAbsoluteDB"),  
leptonsDB = cms.InputTag("nTupleElectrons","tightElectronsPVDxy"),  
leptonsDZ = cms.InputTag("nTupleTightMuons","tightMuonsPVDz"),  

#leptonsID = cms.InputTag("nTupleElectrons","tightElectronsSimpleEleId70cIso"),  
leptonsID = cms.InputTag("nTupleElectrons","tightElectronsPassesTightID"),  
leptonsMVAID = cms.InputTag("nTupleElectrons","tightElectronsMvaTrigV0"),  
leptonsNHits = cms.InputTag("nTupleElectrons","tightElectronsMissingHits"),
#leptonsNHits = cms.InputTag("nTupleElectrons","tightElectronsPassesTightID"),  

#qcdLeptonsEta = cms.InputTag("nTupleQCDElectrons","QCDElectronsPFEta"),  
#qcdLeptonsPt = cms.InputTag("nTupleQCDElectrons","QCDElectronsPFPt"),  
#qcdLeptonsPhi = cms.InputTag("nTupleQCDElectrons","QCDElectronsPFPhi"),  
#qcdLeptonsEnergy = cms.InputTag("nTupleQCDElectrons","QCDElectronsPFE"),  

qcdLeptonsEta = cms.InputTag("nTupleQCDElectrons","QCDElectronsEta"),  
qcdLeptonsPt = cms.InputTag("nTupleQCDElectrons","QCDElectronsPt"),  
qcdLeptonsPhi = cms.InputTag("nTupleQCDElectrons","QCDElectronsPhi"),  
qcdLeptonsEnergy = cms.InputTag("nTupleQCDElectrons","QCDElectronsE"),  
qcdLeptonsCharge = cms.InputTag("nTupleQCDElectrons","QCDElectronsCharge"),  

qcdLeptonsDB = cms.InputTag("nTupleQCDElectrons","QCDElectronsPVDxy"),  
qcdLeptonsDZ = cms.InputTag("nTupleQCDMuons","QCDMuonsPVDz"),  

#qcdLeptonsID = cms.InputTag("nTupleQCDElectrons","QCDElectronsSimpleEleId70cIso"),
qcdLeptonsID = cms.InputTag("nTupleQCDElectrons","QCDElectronsPassesTightID"),  
qcdLeptonsMVAID = cms.InputTag("nTupleQCDElectrons","QCDElectronsMvaTrigV0"),  

#looseElectronsDeltaCorrectedRelIso = cms.InputTag("nTupleVetoElectrons","vetoElectronsPFDeltaCorrectedRelIso"),  
#looseElectronsRhoCorrectedRelIso = cms.InputTag("nTupleVetoElectrons","vetoElectronsPFRhoCorrectedRelIso"),  
#
#looseMuonsDeltaCorrectedRelIso = cms.InputTag("nTupleVetoMuons","vetoMuonsPFDeltaCorrectedRelIso"),  
#looseMuonsRhoCorrectedRelIso = cms.InputTag("nTupleVetoMuons","vetoMuonsPFRhoCorrectedRelIso"),  

looseElectronsDeltaCorrectedRelIso = cms.InputTag("nTupleVetoElectrons","vetoElectronsPFDeltaCorrectedRelIso"),  
looseElectronsRhoCorrectedRelIso = cms.InputTag("nTupleVetoElectrons","vetoElectronsPFRhoCorrectedRelIso"),  
looseMuonsDeltaCorrectedRelIso = cms.InputTag("nTupleVetoMuons","vetoMuonsPFDeltaCorrectedRelIso"),  
looseMuonsRhoCorrectedRelIso = cms.InputTag("nTupleVetoMuons","vetoMuonsPFRhoCorrectedRelIso"),  

leptonsFlavour = cms.untracked.string("electron"),

#Jets

#genJetsPt =cms.InputTag("genJetsPF","genJetsPt"),  
#genJetsEta =cms.InputTag("genJetsPF","genJetsEta"),  
#genAllJetsPt =cms.InputTag("genAllJetsPF","genJetsPt"),  
#genAllJetsEta =cms.InputTag("genAllJetsPF","genJetsEta"),  
#genJetsPt =cms.InputTag("nTupleTopJetsPF","topJetsPFPt"),  
#genJetsEta =cms.InputTag("nTupleTopJetsPF","topJetsPFEta"),  

allJetsPt = cms.InputTag("nTupleAllJets","allJetsPt"),  
allJetsPhi = cms.InputTag("nTupleAllJets","allJetsPhi"),  
allJetsEta = cms.InputTag("nTupleAllJets","allJetsEta"),  
allJetsFlavour = cms.InputTag("nTupleAllJets","allJetsFlavour"),  


#jetsPt = cms.InputTag("nTupleTopJetsPF","topJetsPFPt"),
jetsPt = cms.InputTag("nTupleTopJetsPF","topJetsPFPt"),  
jetsEta = cms.InputTag("nTupleTopJetsPF","topJetsPFEta"),  
jetsPhi = cms.InputTag("nTupleTopJetsPF","topJetsPFPhi"),  
jetsEnergy = cms.InputTag("nTupleTopJetsPF","topJetsPFE"),  

jetsPtJESDown = cms.InputTag("nTupleTopJetsPF","topJetsPFPtJESDown"),  
jetsEnergyJESDown = cms.InputTag("nTupleTopJetsPF","topJetsPFEJESDown"),

jetsPtJERDown = cms.InputTag("nTupleTopJetsPF","topJetsPFPtJERDown"),  
jetsEnergyJERDown = cms.InputTag("nTupleTopJetsPF","topJetsPFEJERDown"),

jetsPtJERUp = cms.InputTag("nTupleTopJetsPF","topJetsPFPtJERUp"),  
jetsEnergyJERUp = cms.InputTag("nTupleTopJetsPF","topJetsPFEJERUp"),

jetsPtJESUp = cms.InputTag("nTupleTopJetsPF","topJetsPFPtJESUp"),  
jetsEnergyJESUp = cms.InputTag("nTupleTopJetsPF","topJetsPFEJESUp"),  


jetsDZ = cms.InputTag("nTupleTopJetsPF","topJetsPFdZ"),  
jetsBeta = cms.InputTag("nTupleTopJetsPF","topJetsPFBeta"),  
jetsRMS = cms.InputTag("nTupleTopJetsPF","topJetsPFRMS"),  

#jetsDZ = cms.InputTag("nTupleTopJetsPF","topJetsPFPt"),  
#jetsBeta = cms.InputTag("nTupleTopJetsPF","topJetsPFPt"),  
#jetsRMS = cms.InputTag("nTupleTopJetsPF","topJetsPFPt"),  


jetsPileUpDiscr = cms.InputTag("nTupleTopJetsPF","topJetsPFPUFullDiscriminant"),  
jetsPileUpWP = cms.InputTag("nTupleTopJetsPF","topJetsPFPUFullWorkingPoint"),  


jetsBTagAlgo = cms.InputTag("nTupleTopJetsPF","topJetsPFTrackCountingHighPur"),  
jetsAntiBTagAlgo =  cms.InputTag("nTupleTopJetsPF","topJetsPFCombinedSecondaryVertexBJetTags"),  
jetsFlavour = cms.InputTag("nTupleTopJetsPF","topJetsPFFlavour"),   

jetsCorrTotal = cms.InputTag("nTupleTopJetsPF","topJetsPFJetCorrTotal"), 

#MET 

METPhi = cms.InputTag("nTuplePatMETsPF","patMETsPFPhi"),
METPt = cms.InputTag("nTuplePatMETsPF","patMETsPFPt"),

UnclUpMETPt = cms.InputTag("nTuplePatMETsPF","patMETsPFPtUnclusteredUp"),
UnclUpMETPhi = cms.InputTag("nTuplePatMETsPF","patMETsPFPhiUnclusteredUp"),
UnclDownMETPt = cms.InputTag("nTuplePatMETsPF","patMETsPFPtUnclusteredDown"),
UnclDownMETPhi = cms.InputTag("nTuplePatMETsPF","patMETsPFPhiUnclusteredDown"),

JESUpMETPt = cms.InputTag("nTuplePatMETsPF","patMETsPFPtJESUp"),
JESUpMETPhi = cms.InputTag("nTuplePatMETsPF","patMETsPFPhiJESUp"),
JESDownMETPt = cms.InputTag("nTuplePatMETsPF","patMETsPFPtJESDown"),
JESDownMETPhi = cms.InputTag("nTuplePatMETsPF","patMETsPFPhiJESDown"),

JERUpMETPt = cms.InputTag("nTuplePatMETsPF","patMETsPFPtJERUp"),
JERUpMETPhi = cms.InputTag("nTuplePatMETsPF","patMETsPFPhiJERUp"),
JERDownMETPt = cms.InputTag("nTuplePatMETsPF","patMETsPFPtJERDown"),
JERDownMETPhi = cms.InputTag("nTuplePatMETsPF","patMETsPFPhiJERDown"),



#METPhi = cms.InputTag("nTuplePatMETsPF","patMETsPFPhi"),
#METPt = cms.InputTag("nTuplePatMETsPF","patMETsPFPt"),

#UnclusteredMETPx = cms.InputTag("nTuplePatMETsPF","patMETsPFPtUnclusteredUp"),
#UnclusteredMETPy = cms.InputTag("nTuplePatMETsPF","patMETsPFPtUnclusteredUp"),


#Vertices
vertexZ = cms.InputTag("nTupleVertices","z"),  

nVerticesPlus = cms.InputTag("NVertices","PileUpP1"),
nVerticesMinus = cms.InputTag("NVertices","PileUpM1"),
nVertices = cms.InputTag("NVertices","PileUpTrue"),

#MC part
MCQuarksEta = cms.InputTag("singleTopMCQuarks","MCquarksEta"),  
MCQuarksPt = cms.InputTag("singleTopMCQuarks","MCquarksPt"),  
MCQuarksPhi = cms.InputTag("singleTopMCQuarks","MCquarksPhi"),  
MCQuarksEnergy = cms.InputTag("singleTopMCQuarks","MCquarksE"),
MCQuarksPdgId = cms.InputTag("singleTopMCQuarks","MCquarksPdgId"),
MCQuarksMotherId= cms.InputTag("MCTruthParticles","MCquarksMotherID"),  

MCBQuarksEta = cms.InputTag("singleTopMCBQuarks","MCbquarksEta"),  
MCBQuarksPt = cms.InputTag("singleTopMCBQuarks","MCbquarksPt"),  
MCBQuarksPhi = cms.InputTag("singleTopMCBQuarks","MCbquarksPhi"),  
MCBQuarksEnergy = cms.InputTag("singleTopMCBQuarks","MCbquarksE"),
MCBQuarksPdgId = cms.InputTag("singleTopMCBQuarks","MCbquarksPdgId"),
MCBQuarksMotherId= cms.InputTag("MCTruthParticles","MCbquarksMotherID"),  

MCLeptonsEta = cms.InputTag("singleTopMCLeptons","MCleptonsEta"),  
MCLeptonsPt = cms.InputTag("singleTopMCLeptons","MCleptonsPt"),  
MCLeptonsPhi = cms.InputTag("singleTopMCLeptons","MCleptonsPhi"),  
MCLeptonsEnergy = cms.InputTag("singleTopMCLeptons","MCleptonsE"),  
MCLeptonsPdgId = cms.InputTag("singleTopMCLeptons","MCleptonsPdgId"),  
MCLeptonsMotherId= cms.InputTag("MCTruthParticles","MCleptonsMotherID"),  

MCNeutrinosEta = cms.InputTag("singleTopMCNeutrinos","mcNeutrinosEta"),  
MCNeutrinosPt = cms.InputTag("singleTopMCNeutrinos","mcNeutrinosPt"),  
MCNeutrinosPhi = cms.InputTag("singleTopMCNeutrinos","mcNeutrinosPhi"),  
MCNeutrinosEnergy = cms.InputTag("singleTopMCNeutrinos","mcNeutrinosE"),
MCNeutrinosPdgId = cms.InputTag("singleTopMCNeutrinos","mcNeutrinosPdgId"),
MCNeutrinosMotherId= cms.InputTag("MCTruthParticles","MCneutrinosMotherID"),  

#Top
MCTopsEta = cms.InputTag("singleTopMCTops","MCtopsEta"),  
MCTopsPt = cms.InputTag("singleTopMCTops","MCtopsPt"),  
MCTopsPhi = cms.InputTag("singleTopMCTops","MCtopsPhi"),  
MCTopsEnergy = cms.InputTag("singleTopMCTops","MCtopsE"),  
MCTopsPdgId = cms.InputTag("singleTopMCTops","MCtopsPdgId"),  
MCTopsMotherId= cms.InputTag("MCTruthParticles","MCtopsMotherID"),  


MCTopLeptonsEta = cms.InputTag("singleTopMCTopsLepton","MCtopsLeptonEta"),  
MCTopLeptonsPt = cms.InputTag("singleTopMCTopsLepton","MCtopsLeptonPt"),  
MCTopLeptonsPhi = cms.InputTag("singleTopMCTopsLepton","MCtopsLeptonPhi"),  
MCTopLeptonsEnergy = cms.InputTag("singleTopMCTopsLepton","MCtopsLeptonE"),  
MCTopLeptonsPdgId = cms.InputTag("singleTopMCTopsLepton","MCtopsLeptonPdgId"),  
MCTopLeptonsMotherId= cms.InputTag("MCTruthParticles","MCtopsLeptonMotherID"),  

MCTopBQuarksEta = cms.InputTag("singleTopMCTopsBQuark","MCtopsBQuarkEta"),  
MCTopBQuarksPt = cms.InputTag("singleTopMCTopsBQuark","MCtopsBQuarkPt"),  
MCTopBQuarksPhi = cms.InputTag("singleTopMCTopsBQuark","MCtopsBQuarkPhi"),  
MCTopBQuarksEnergy = cms.InputTag("singleTopMCTopsBQuark","MCtopsBQuarkE"),  
MCTopBQuarksPdgId = cms.InputTag("singleTopMCTopsBQuark","MCtopsBQuarkPdgId"),  
MCTopBQuarksMotherId= cms.InputTag("MCTruthParticles","MCtopsBQuarkMotherID"),  

MCTopNeutrinosEta = cms.InputTag("singleTopMCTopsNeutrino","MCtopsNeutrinoEta"),  
MCTopNeutrinosPt = cms.InputTag("singleTopMCTopsNeutrino","MCtopsNeutrinoPt"),  
MCTopNeutrinosPhi = cms.InputTag("singleTopMCTopsNeutrino","MCtopsNeutrinoPhi"),  
MCTopNeutrinosEnergy = cms.InputTag("singleTopMCTopsNeutrino","MCtopsNeutrinoE"),  
MCTopNeutrinosPdgId = cms.InputTag("singleTopMCTopsNeutrino","MCtopsNeutrinoPdgId"),  
MCTopNeutrinosMotherId= cms.InputTag("MCTruthParticles","MCtopsNeutrinoMotherID"),  

MCTopQuarksEta = cms.InputTag("singleTopMCTopsQuark","MCtopsQuarkEta"),  
MCTopQuarksPt = cms.InputTag("singleTopMCTopsQuark","MCtopsQuarkPt"),  
MCTopQuarksPhi = cms.InputTag("singleTopMCTopsQuark","MCtopsQuarkPhi"),  
MCTopQuarksEnergy = cms.InputTag("singleTopMCTopsQuark","MCtopsQuarkE"),  
MCTopQuarksPdgId = cms.InputTag("singleTopMCTopsQuark","MCtopsQuarkPdgId"),  
MCTopQuarksMotherId= cms.InputTag("MCTruthParticles","MCtopsQuarkMotherID"),  

MCTopQuarkBarsEta = cms.InputTag("singleTopMCTopsQuarkBar","MCtopsQuarkBarEta"),  
MCTopQuarkBarsPt = cms.InputTag("singleTopMCTopsQuarkBar","MCtopsQuarkBarPt"),  
MCTopQuarkBarsPhi = cms.InputTag("singleTopMCTopsQuarkBar","MCtopsQuarkBarPhi"),  
MCTopQuarkBarsEnergy = cms.InputTag("singleTopMCTopsQuarkBar","MCtopsQuarkBarE"),  
MCTopQuarkBarsPdgId = cms.InputTag("singleTopMCTopsQuarkBar","MCtopsQuarkBarPdgId"),  
MCTopQuarkBarsMotherId= cms.InputTag("MCTruthParticles","MCtopsQuarkBarMotherID"),  

MCTopWsEta = cms.InputTag("singleTopMCTopsW","MCtopsWEta"),  
MCTopWsPt = cms.InputTag("singleTopMCTopsW","MCtopsWPt"),  
MCTopWsPhi = cms.InputTag("singleTopMCTopsW","MCtopsWPhi"),  
MCTopWsEnergy = cms.InputTag("singleTopMCTopsW","MCtopsWE"),  
MCTopWsPdgId = cms.InputTag("singleTopMCTopsW","MCtopsWPdgId"),  
MCTopWsMotherId = cms.InputTag("MCTruthParticles","MCtopsWMotherID"),
MCTopWsDauOneId= cms.InputTag("MCTruthParticles","MCtopsWDauOneID"),  




)

TreesMu = TreesEle.clone(

#Leptons
leptonsEta = cms.InputTag("nTupleMuons","tightMuonsEta"),  
leptonsPt = cms.InputTag("nTupleMuons","tightMuonsPt"),  
leptonsPhi = cms.InputTag("nTupleMuons","tightMuonsPhi"),  
leptonsEnergy = cms.InputTag("nTupleMuons","tightMuonsE"),  
leptonsCharge = cms.InputTag("nTupleMuons","tightMuonsCharge"),  

#leptonsDeltaCorrectedRelIso = cms.InputTag("nTupleMuons","tightMuonsPFRelIso"),  
leptonsDeltaCorrectedRelIso = cms.InputTag("nTupleMuons","tightMuonsPFDeltaCorrectedRelIso"),  
leptonsRhoCorrectedRelIso = cms.InputTag("nTupleMuons","tightMuonsPFRhoCorrectedRelIso"),  

leptonsDB = cms.InputTag("nTupleMuons","tightMuonsPVDxy"),  
leptonsDZ = cms.InputTag("nTupleMuons","tightMuonsPVDz"),  
#leptonsDB = cms.InputTag("nTupleMuons","tightMuonsAbsoluteDB"),  

#leptonsMVAID = cms.InputTag("nTupleElectrons","tightElectronsMvaTrigV0"),  
qcdLeptonsMVAID = cms.InputTag("nTupleQCDElectrons","QCDElectronsMvaTrigV0"),

qcdLeptonsEta = cms.InputTag("nTupleQCDMuons","QCDMuonsEta"),  
qcdLeptonsPt = cms.InputTag("nTupleQCDMuons","QCDMuonsPt"),  
qcdLeptonsPhi = cms.InputTag("nTupleQCDMuons","QCDMuonsPhi"),  
qcdLeptonsEnergy = cms.InputTag("nTupleQCDMuons","QCDMuonsE"),  
qcdLeptonsCharge = cms.InputTag("nTupleQCDMuons","QCDMuonsCharge"),  

qcdLeptonsDB = cms.InputTag("nTupleQCDMuons","QCDMuonsPVDxy"),  
qcdLeptonsDZ = cms.InputTag("nTupleQCDMuons","QCDMuonsPVDz"),  

qcdLeptonsDeltaCorrectedRelIso = cms.InputTag("nTupleQCDMuons","QCDMuonsPFDeltaCorrectedRelIso"),  
qcdLeptonsRhoCorrectedRelIso = cms.InputTag("nTupleQCDMuons","QCDMuonsPFRhoCorrectedRelIso"),  

#qcdLeptonsID = cms.InputTag("nTupleMuons","tightMuonsSimpleEleId70cIso"),  

looseElectronsDeltaCorrectedRelIso = cms.InputTag("nTupleVetoElectrons","vetoElectronsPFDeltaCorrectedRelIso"),  
looseElectronsRhoCorrectedRelIso = cms.InputTag("nTupleVetoElectrons","vetoElectronsPFRhoCorrectedRelIso"),  

looseMuonsDeltaCorrectedRelIso = cms.InputTag("nTupleVetoMuons","vetoMuonsPFDeltaCorrectedRelIso"),  
looseMuonsRhoCorrectedRelIso = cms.InputTag("nTupleVetoMuons","vetoMuonsPFRhoCorrectedRelIso"),  

#looseElectronsDeltaCorrectedRelIso = cms.InputTag("nTupleVetoElectrons","vetoElectronsPFDeltaCorrectedRelIso"),  
#vetoElectronsRhoCorrectedRelIso = cms.InputTag("nTupleVetoElectrons","vetoElectronsPFRhoCorrectedRelIso"),  
#
#looseMuonsDeltaCorrectedRelIso = cms.InputTag("nTupleVetoMuons","vetoMuonsPFDeltaCorrectedRelIso"),  
#Loosemuonsrhocorrectedreliso = cms.InputTag("nTupleVetoMuons","vetoMuonsPFRhoCorrectedRelIso"),  

#looseElectronsDeltaCorrectedRelIso = cms.InputTag("nTupleVetoElectrons","vetoElectronsPFDeltaCorrectedRelIso"),  


leptonsFlavour = cms.untracked.string("muon"),

    channelInfo = cms.PSet(
        crossSection = cms.untracked.double(20.93),
        channel = cms.untracked.string("TChannel"),
        #    originalEvents = cms.untracked.double(14800000),
        originalEvents = cms.untracked.double(480000),
        finalLumi = cms.untracked.double(14.5),
        MTWCut = cms.untracked.double(40.0),#Default 50.0 GeV
        RelIsoCut = cms.untracked.double(0.05),
        ),

    
    )


