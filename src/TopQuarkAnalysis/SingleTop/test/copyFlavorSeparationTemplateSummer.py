import FWCore.ParameterSet.Config as cms

process = cms.Process("SingleTopSkimMerge")

#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.source = cms.Source ("PoolSource",
                             fileNames = cms.untracked.vstring (
#'rfio:/castor/cern.ch/user/o/oiorio/SingleTop/SingleTop_tChan/TChanSampleTChanMu_9_1_S3X.root',
    #'file:/tmp/oiorio/00012F91-72E5-DF11-A763-00261834B5F1.root'
    #    'file:/tmp/oiorio/00012F91-72E5-DF11-A763-00261834B5F1.root'
    'file:/tmp/oiorio/TChannelMergedBig.root',
),
skipBadFiles = cms.untracked.bool(True),
duplicateCheckMode = cms.untracked.string('noDuplicateCheck')
)

process.options = cms.untracked.PSet(SkipEvent = cms.untracked.vstring('MismatchedInputFiles'))

## Load additional RECO config
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")

process.GlobalTag.globaltag = cms.string('START52_V9::All')

#from Configuration.PyReleaseValidation.autoCond import autoCond
#process.GlobalTag.globaltag = autoCond['startup']


process.counter = cms.EDFilter("SingleTopDoubleCounter",
                               src = cms.InputTag("nTupleTopJetsPF","topJetsPFPt"), 
                               min = cms.untracked.int32(2),
                               max = cms.untracked.int32(999),
                               )

switch = "switch_instruction" #SWITCH_INSTRUCTION

#process.TwoJetsCut = cms.Path(
#    process.counter
#    )
    
process.skimwall = cms.OutputModule("PoolOutputModule",
                                        fileName = cms.untracked.string('/tmp/oiorio/TChannelMerged.root'),
                                        outputCommands = cms.untracked.vstring(    'keep *',   ),
#                                    SelectEvents = cms.untracked.PSet( SelectEvents = cms.vstring('TwoJetsCut')),
                                        )
process.outpath = cms.EndPath( process.skimwall)
    #process.skimwall.fileName = "/tmp/oiorio//tmp/oiorio/TChannelMerged.root"

    
#process.source.fileNames = TChannel_ntuple
#process.skimwall.fileName = "/castor/cern.ch/user/o/oiorio/SingleTop/2011/MC2011/NewNtuples/Merged/TChannelMerged.root"

#Save the skims
#process.outpath = cms.EndPath( process.skimlight + process.skimwcc + process.skimwbb )
