import FWCore.ParameterSet.Config as cms

process = cms.Process("SingleTopSkimMerge")

#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.source = cms.Source ("PoolSource",
                             fileNames = cms.untracked.vstring (
#'rfio:/castor/cern.ch/user/o/oiorio/SingleTop/SingleTop_tChan/TChanSampleTChanMu_9_1_S3X.root',
    #'file:/tmp/oiorio/00012F91-72E5-DF11-A763-00261834B5F1.root'
    #    'file:/tmp/oiorio/00012F91-72E5-DF11-A763-00261834B5F1.root'
    'file:/tmp/oiorio/TTBarMerged.root',
),
skipBadFiles = cms.untracked.bool(True),
duplicateCheckMode = cms.untracked.string('noDuplicateCheck')
)


## Load additional RECO config
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")

from Configuration.PyReleaseValidation.autoCond import autoCond
process.GlobalTag.globaltag = autoCond['startup']


process.load("PhysicsTools.HepMCCandAlgos.flavorHistoryPaths_cfi")

process.wlightFilter = process.flavorHistoryFilter.clone(pathToSelect = cms.int32(11))

process.wccFilter = process.flavorHistoryFilter.clone(pathToSelect = cms.int32(6))

process.wccFilter1 = process.flavorHistoryFilter.clone(pathToSelect = cms.int32(3))
process.wccFilter2 = process.flavorHistoryFilter.clone(pathToSelect = cms.int32(4))

process.wcFilter = process.flavorHistoryFilter.clone(pathToSelect = cms.int32(4))

process.wbbFilter = process.flavorHistoryFilter.clone(pathToSelect = cms.int32(5))

process.wbbFilter1 = process.flavorHistoryFilter.clone(pathToSelect = cms.int32(1))
process.wbbFilter2 = process.flavorHistoryFilter.clone(pathToSelect = cms.int32(2))


switch = "switch_instruction" #SWITCH_INSTRUCTION

if switch == "None":
    process.skimwall = cms.OutputModule("PoolOutputModule",
                                        fileName = cms.untracked.string('/tmp/oiorio/TChannelMerged.root'),
                                        outputCommands = cms.untracked.vstring(    'keep *',   ),
#                                        SelectEvents = cms.untracked.PSet( SelectEvents = cms.vstring('*')),
                                        )
    process.outpath = cms.EndPath( process.skimwall)
    #process.skimwall.fileName = "/tmp/oiorio//tmp/oiorio/TChannelMerged.root"

    
#process.source.fileNames = TChannel_ntuple
#process.skimwall.fileName = "/castor/cern.ch/user/o/oiorio/SingleTop/2011/MC2011/NewNtuples/Merged/TChannelMerged.root"

#Save the skims
#process.outpath = cms.EndPath( process.skimlight + process.skimwcc + process.skimwbb )
