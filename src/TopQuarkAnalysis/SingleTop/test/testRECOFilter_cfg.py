#Bring in the configuration python objects
import FWCore.ParameterSet.Config as cms

process = cms.Process("TEST")
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger = cms.Service("MessageLogger",
  destinations   = cms.untracked.vstring(
    'detailedInfo'
    ,'critical'
    ,'cout'
    ),
  detailedInfo = cms.untracked.PSet(threshold  = cms.untracked.string('DEBUG')),
  debugModules = cms.untracked.vstring('filter')
)

process.source = cms.Source("PoolSource",
#    fileNames      = cms.untracked.vstring('file:/afs/cern.ch/user/j/jpata/work/public/stpol/testRECOfilter.root')
#    fileNames      = cms.untracked.vstring("file:/home/joosep/singletop/T_t-channel.root")
#    fileNames      = cms.untracked.vstring("file:/hdfs/cms/store/mc/Summer12/T_t-channel_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S7_START52_V9-v1/0000/8C021621-E39B-E111-875C-00151796C0FC.root")
    #fileNames      = cms.untracked.vstring("/store/mc/Summer12/T_t-channel_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S7_START52_V9-v1/0000/8C021621-E39B-E111-875C-00151796C0FC.root")
    fileNames      = cms.untracked.vstring("/store/mc/Summer12/WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball/AODSIM/PU_S7_START52_V9-v1/0001/FE8F81B3-C494-E111-B50D-003048D476BC.root")
  )

process.filter = cms.EDFilter("SingleTopRecoFilter",
 # minMuons = cms.untracked.int32(1),
 # minJets = cms.untracked.int32(2),
 # minMuonPt = cms.untracked.double(25.0),
 # minJetPt = cms.untracked.double(20.0),
 # maxMuonEta = cms.untracked.double(2.1),
 # maxMuonRelIso = cms.untracked.double(10000.0),
 # maxJetEta = cms.untracked.double(5.0)
  minMuons = cms.untracked.int32(1),
  minJets = cms.untracked.int32(2),
  minMuonPt = cms.untracked.double(25.0),
  minJetPt = cms.untracked.double(20.0),
  maxMuonEta = cms.untracked.double(2.1),
  maxMuonRelIso = cms.untracked.double(10000.0),
  maxJetEta = cms.untracked.double(5.0)
  )

process.filterPath = cms.Path(process.filter)
process.filterPath = cms.Path(process.filter)

process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('testFilter_out.root'),
    SelectEvents = cms.untracked.PSet( SelectEvents = cms.vstring('filterPath'))
  )

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.outpath = cms.EndPath(process.out)
