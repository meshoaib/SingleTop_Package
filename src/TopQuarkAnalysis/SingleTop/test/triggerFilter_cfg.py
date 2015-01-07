###########################################
###  Author: Annapaola de Cosa          ###
###          annapaola.de.cosa@cern.ch  ###
###                                     ###
###  Configuration file for filtering   ###
###  events on the base of HLT paths    ###
###########################################


import FWCore.ParameterSet.Config as cms

process = cms.Process("NTPFILT")

#### Simple cfg to apply event filter to ntuple
#### It just apply a filter on HLT trigger paths, but other filters can be added here

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.source = cms.Source("PoolSource")

### Indicate here the input file
process.source.fileNames=cms.untracked.vstring('file:singleTopEdmNtuple_TChannel.root')
#process.source.fileNames=cms.untracked.vstring('file:edmNtupleTest.root')

### Indicate here the number of events on which perform the selection
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.MessageLogger.cerr.FwkReport.reportEvery = 100

### HLT trigger path for muon channel
process.triggerMuSelection = cms.EDFilter( "TriggerResultsFilter",
                                     triggerConditions = cms.vstring(
                                     "HLT_IsoMu24_v*" ),
                                     hltResults = cms.InputTag( "TriggerResults", "", "HLT" ),
                                     l1tResults = cms.InputTag( "" ),
                                     l1tIgnoreMask = cms.bool( True ),
                                     l1techIgnorePrescales = cms.bool( True ),
                                     daqPartitions = cms.uint32( 1 ),
                                     throw = cms.bool( True )
                                 )


### HLT trigger path for muon channel
process.triggerElSelection = cms.EDFilter( "TriggerResultsFilter",
                                     triggerConditions = cms.vstring(
                                     "HLT_Ele27_WP80_v*"),
                                     hltResults = cms.InputTag( "TriggerResults", "", "HLT" ),
                                     l1tResults = cms.InputTag( "" ),
                                     l1tIgnoreMask = cms.bool( True ),
                                     l1techIgnorePrescales = cms.bool( True ),
                                     daqPartitions = cms.uint32( 1 ),
                                     throw = cms.bool( True )
                                 )


process.triggerMuFilter = cms.Path(
         process.triggerMuSelection
            )

process.triggerElFilter = cms.Path(
         process.triggerElSelection
            )


process.MuedmNtuplesOut = cms.OutputModule(
    "PoolOutputModule",
    fileName = cms.untracked.string('mu_edmntuples.root'),
    outputCommands = cms.untracked.vstring(
    "keep *",
    "drop *_TriggerResults_*_PAT",
    "drop *_TriggerResults_*_NTPFILT",
    )
    )

process.EledmNtuplesOut = cms.OutputModule(
    "PoolOutputModule",
    fileName = cms.untracked.string('el_edmntuples.root'),
    outputCommands = cms.untracked.vstring(
    "keep *",
    "drop *_TriggerResults_*_PAT",
    "drop *_TriggerResults_*_NTPFILT",
    )
    )

process.EledmNtuplesOut.SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('triggerElFilter')
            )


process.MuedmNtuplesOut.SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('triggerMuFilter')
            )

process.MuedmNtuplesOut.dropMetaData = cms.untracked.string('ALL')
process.EledmNtuplesOut.dropMetaData = cms.untracked.string('ALL')

process.endPath = cms.EndPath(process.EledmNtuplesOut + process.MuedmNtuplesOut)
