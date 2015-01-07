import FWCore.ParameterSet.Config as cms

# scraping filter
scrapingVeto = cms.EDFilter(
    "FilterOutScraping",
    applyfilter=cms.untracked.bool(True),
    debugOn=cms.untracked.bool(False),
    numtrack=cms.untracked.uint32(10),
    thresh=cms.untracked.double(0.2)
)

# HB + HE noise filtering
from CommonTools.RecoAlgos.HBHENoiseFilter_cfi import HBHENoiseFilter
from RecoMET.METAnalyzers.CSCHaloFilter_cfi import CSCTightHaloFilter
from RecoMET.METFilters.hcalLaserEventFilter_cfi import hcalLaserEventFilter
from RecoMET.METFilters.trackingFailureFilter_cfi import trackingFailureFilter
from RecoMET.METFilters.eeBadScFilter_cfi import eeBadScFilter
from RecoMET.METFilters.ecalLaserCorrFilter_cfi import ecalLaserCorrFilter
from RecoMET.METFilters.EcalDeadCellBoundaryEnergyFilter_cfi import EcalDeadCellBoundaryEnergyFilter
from RecoMET.METFilters.EcalDeadCellTriggerPrimitiveFilter_cfi import EcalDeadCellTriggerPrimitiveFilter
from RecoMET.METFilters.trackingPOGFilters_cfi import manystripclus53X
from RecoMET.METFilters.trackingPOGFilters_cfi import toomanystripclus53X
from RecoMET.METFilters.trackingPOGFilters_cfi import logErrorTooManyClusters

EcalDeadCellTriggerPrimitiveFilter.tpDigiCollection = cms.InputTag("ecalTPSkimNA")
EcalDeadCellBoundaryEnergyFilter.taggingMode = cms.bool(False)
EcalDeadCellBoundaryEnergyFilter.cutBoundEnergyDeadCellsEB=cms.untracked.double(10)
EcalDeadCellBoundaryEnergyFilter.cutBoundEnergyDeadCellsEE=cms.untracked.double(10)
EcalDeadCellBoundaryEnergyFilter.cutBoundEnergyGapEB=cms.untracked.double(100)
EcalDeadCellBoundaryEnergyFilter.cutBoundEnergyGapEE=cms.untracked.double(100)
EcalDeadCellBoundaryEnergyFilter.enableGap=cms.untracked.bool(False)
EcalDeadCellBoundaryEnergyFilter.limitDeadCellToChannelStatusEB = cms.vint32(12,14)
EcalDeadCellBoundaryEnergyFilter.limitDeadCellToChannelStatusEE = cms.vint32(12,14)

goodVertices = cms.EDFilter(
    "VertexSelector" ,
    filter = cms.bool(False),
    src = cms.InputTag("offlinePrimaryVertices"),
    cut = cms.string("!isFake && ndof > 4 && abs(z) <= 24 && position.rho < 2")
)


