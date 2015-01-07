import FWCore.ParameterSet.Config as cms

process = cms.Process("SingleTopSkimMergeB")

#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.source = cms.Source ("PoolSource",
                             fileNames = cms.untracked.vstring (
#'rfio:/castor/cern.ch/user/o/oiorio/SingleTop/SingleTop_tChan/TChanSampleTChanMu_9_1_S3X.root',
    'file:/tmp/oiorio/00012F91-72E5-DF11-A763-00261834B5F1.root'

),
skipBadFiles = cms.untracked.bool(True),
duplicateCheckMode = cms.untracked.string('noDuplicateCheck')
)



## Load additional RECO config
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")

process.GlobalTag.globaltag = cms.string('START52_V9B::All')


process.pu = cms.EDProducer("SingleTopPileUpProducer")

process.pathPu = cms.Path( process.pu    )


process.skimwall = cms.OutputModule("PoolOutputModule",
                                    fileName = cms.untracked.string('TChannelSpring11Small.root'),
                                    outputCommands = cms.untracked.vstring(    'keep *',   )
)
#process.source.fileNames = TChannel_ntuple
#process.skimwall.fileName = "/tmp/oiorio/TChannelMerged.root"
#process.skimwall.fileName = "/castor/cern.ch/user/o/oiorio/SingleTop/2011/MC2011/NewNtuples/Merged/TChannelMerged.root"

#Save the skims
#process.outpath = cms.EndPath( process.skimlight + process.skimwcc + process.skimwbb )
process.source.fileNames = cms.untracked.vstring("file:/tmp/oiorio/TWChannelMerged.root")
process.outpath = cms.EndPath( process.skimwall)
