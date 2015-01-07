import FWCore.ParameterSet.Config as cms

#Process name:
process = cms.Process("SingleTop")

#MessageLogger options:
process.load("FWCore.MessageLogger.MessageLogger_cfi")

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True),
    FailPath = cms.untracked.vstring('ProductNotFound','Type Mismatch')
    )

#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(400000) )
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

fs = "LO_4fs"
fs = "4fs"
fs = "POWHEG_5fs"

ChannelName = "TChannel_pythia_400k"+fs
#ChannelName = "TChannel_herwig"+fs

#Data or MC:
isData=False

#Input file:
process.source = cms.Source (
    "PoolSource",
    fileNames = cms.untracked.vstring (
#   "file:/tmp/oiorio/testherwig6_"+fs+".root",
    "file:/tmp/oiorio/testpythia4c_"+fs+"_long_5311.root",


#    "file:/tmp/oiorio/testherwig6_4fs.root",
#      "file:/afs/cern.ch/work/o/oiorio/public/xFrancescoFab/T_t-channel_Synch.root"
#      "file:/afs/cern.ch/work/o/oiorio/public/xFrancescoFab/DataReRecoA.root"
#      "file:8425E88A-AED7-E211-8067-002481E14F5C.root"
    ),
    duplicateCheckMode = cms.untracked.string('noDuplicateCheck')
)
#Geometry:
process.load("Configuration.Geometry.GeometryIdeal_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff") ### real data

#Tag:
### new GT - 10Sept2013
process.GlobalTag.globaltag = cms.string('START53_V27::All')

process.MCTruthParticles = cms.EDProducer(
    "SingleTopMCProducer",
    genParticlesSource = cms.InputTag("genParticles"),
    lhes = cms.InputTag("source"),
    usesPythiaStatusConvention = cms.untracked.bool(True)
)

process.MCTruthAnalysis = cms.EDProducer(
    "SingleTopPseudoAnalysisProducer",
    genJetsSource = cms.InputTag("ak5GenJets"),
    useFullSelection = cms.untracked.bool(False),
#    useFullSelection = cms.untracked.bool(True),
    matchWithLHE = cms.untracked.bool(True),
    jetThreshold = cms.untracked.double(40.0),
    metThreshold = cms.untracked.double(0.0),
    mtwThreshold = cms.untracked.double(50.0),
    leptonThreshold = cms.untracked.double(26.0),
    genJetsDeltarMatching = cms.untracked.double(0.5),
    bTagEfficiency = cms.untracked.double(1.0),

    MCQuarksEta = cms.InputTag("singleTopMCQuarks","MCquarksEta"),  
    MCQuarksPt = cms.InputTag("singleTopMCQuarks","MCquarksPt"),  
    MCQuarksPhi = cms.InputTag("singleTopMCQuarks","MCquarksPhi"),  
    MCQuarksEnergy = cms.InputTag("singleTopMCQuarks","MCquarksE"),
    MCQuarksPdgId = cms.InputTag("singleTopMCQuarks","MCquarksPdgId"),

    MCLeptonsEta = cms.InputTag("singleTopMCLeptons","MCleptonsEta"),  
    MCLeptonsPt = cms.InputTag("singleTopMCLeptons","MCleptonsPt"),  
    MCLeptonsPhi = cms.InputTag("singleTopMCLeptons","MCleptonsPhi"),  
    MCLeptonsEnergy = cms.InputTag("singleTopMCLeptons","MCleptonsE"),  
    MCLeptonsPdgId = cms.InputTag("singleTopMCLeptons","MCleptonsPdgId"),  
    
    MCNeutrinosEta = cms.InputTag("singleTopMCNeutrinos","mcNeutrinosEta"),  
    MCNeutrinosPt = cms.InputTag("singleTopMCNeutrinos","mcNeutrinosPt"),  
    MCNeutrinosPhi = cms.InputTag("singleTopMCNeutrinos","mcNeutrinosPhi"),  
    MCNeutrinosEnergy = cms.InputTag("singleTopMCNeutrinos","mcNeutrinosE"),
    MCNeutrinosPdgId = cms.InputTag("singleTopMCNeutrinos","mcNeutrinosPdgId"),
    
    #Top
    MCTopsEta = cms.InputTag("singleTopMCTops","MCtopsEta"),  
    MCTopsPt = cms.InputTag("singleTopMCTops","MCtopsPt"),  
    MCTopsPhi = cms.InputTag("singleTopMCTops","MCtopsPhi"),  
    MCTopsEnergy = cms.InputTag("singleTopMCTops","MCtopsE"),  
    MCTopsPdgId = cms.InputTag("singleTopMCTops","MCtopsPdgId")  ,
    
    #LHE counterparts
    LHEMCQuarksEta = cms.InputTag("MCTruthParticles","MCLHEquarksEta"),  
    LHEMCQuarksPt = cms.InputTag("MCTruthParticles","MCLHEquarksPt"),  
    LHEMCQuarksPhi = cms.InputTag("MCTruthParticles","MCLHEquarksPhi"),  
    LHEMCQuarksEnergy = cms.InputTag("MCTruthParticles","MCLHEquarksE"),
    LHEMCQuarksPdgId = cms.InputTag("MCTruthParticles","MCLHEquarksID"),

    LHEMCLeptonsEta = cms.InputTag("MCTruthParticles","MCLHEleptonsEta"),  
    LHEMCLeptonsPt = cms.InputTag("MCTruthParticles","MCLHEleptonsPt"),  
    LHEMCLeptonsPhi = cms.InputTag("MCTruthParticles","MCLHEleptonsPhi"),  
    LHEMCLeptonsEnergy = cms.InputTag("MCTruthParticles","MCLHEleptonsE"),  
    LHEMCLeptonsPdgId = cms.InputTag("MCTruthParticles","MCLHEleptonsID"),  
    
    LHEMCNeutrinosEta = cms.InputTag("MCTruthParticles","MCLHEneutrinosEta"),  
    LHEMCNeutrinosPt = cms.InputTag("MCTruthParticles","MCLHEneutrinosPt"),  
    LHEMCNeutrinosPhi = cms.InputTag("MCTruthParticles","MCLHEneutrinosPhi"),  
    LHEMCNeutrinosEnergy = cms.InputTag("MCTruthParticles","MCLHEneutrinosE"),
    LHEMCNeutrinosPdgId = cms.InputTag("MCTruthParticles","MCLHEneutrinosID"),

    #Top
    LHEMCTopsEta = cms.InputTag("MCTruthParticles","MCLHEtopsEta"),  
    LHEMCTopsPt = cms.InputTag("MCTruthParticles","MCLHEtopsPt"),  
    LHEMCTopsPhi = cms.InputTag("MCTruthParticles","MCLHEtopsPhi"),  
    LHEMCTopsEnergy = cms.InputTag("MCTruthParticles","MCLHEtopsE"),  
    LHEMCTopsPdgId = cms.InputTag("MCTruthParticles","MCLHEtopsID")  

    )

######### EdmNtuples production ##############

process.load("TopQuarkAnalysis.SingleTop.SingleTopNtuplizers_cff")

# Ntuple sequence
process.MCTruth = cms.Path(
    process.MCTruthParticles *
    process.nTuplesSkimMCTruth *
    process.MCTruthAnalysis
    )


from TopQuarkAnalysis.SingleTop.SingleTopNtuplizers_cff import saveNTuplesSkimLoose

saveNTuplesSkimLoose.append('keep  floats_MCTruthParticles_*_*')
saveNTuplesSkimLoose.append('keep  *_MCTruthAnalysis_*_*')
saveNTuplesSkimLoose.append('keep  ints_MCTruthParticles_*_*')
saveNTuplesSkimLoose.append('keep  floats_singleTopMCLeptons_*_*')
saveNTuplesSkimLoose.append('keep  floats_singleTopMCQuarks_*_*')
saveNTuplesSkimLoose.append('keep  floats_singleTopMCNeutrinos_*_*')
saveNTuplesSkimLoose.append('keep  floats_singleTopMCBQuarks_*_*')
saveNTuplesSkimLoose.append('keep  floats_singleTopMCTops_*_*')
saveNTuplesSkimLoose.append('keep  floats_singleTopMCTopsW_*_*')
saveNTuplesSkimLoose.append('keep  floats_singleTopMCTopsBQuark_*_*')
saveNTuplesSkimLoose.append('keep  floats_singleTopMCTopsLepton_*_*')
saveNTuplesSkimLoose.append('keep  floats_singleTopMCTopsNeutrino_*_*')
saveNTuplesSkimLoose.append('keep  floats_singleTopMCTopsQuark_*_*')
saveNTuplesSkimLoose.append('keep  floats_singleTopMCTopsQuarkBar_*_*')
#Higgs
saveNTuplesSkimLoose.append('keep  floats_singleTopMCHiggs_*_*')
saveNTuplesSkimLoose.append('keep  floats_singleTopMCHiggsBQuark_*_*')
saveNTuplesSkimLoose.append('keep  float_*_*_*')


## Output module configuration
process.singleTopNTupleOut = cms.OutputModule(
    "PoolOutputModule",
    fileName = cms.untracked.string('singleTopMCAnalysisEdmNtuple_'+ChannelName+'.root'),
    #SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('preselection')),
    outputCommands = saveNTuplesSkimLoose,
    )

process.singleTopNTupleOut.dropMetaData = cms.untracked.string("ALL")

process.outpath = cms.EndPath(
    process.singleTopNTupleOut
    )

