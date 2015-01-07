import FWCore.ParameterSet.Config as cms

#lumiMu = cms.untracked.double(869.129366562)
#lumiMu = cms.untracked.double(1078.75640263)
#lumiMu = cms.untracked.double(1496.275-368+179)
#lumiEle = cms.untracked.double(191.091)


lumiMu = cms.untracked.double(1)
lumiEle = cms.untracked.double(1)

#lumiEle = cms.untracked.double(1299.)
#lumiMu = cms.untracked.double(1496.275-368.88+179.35)


wToLNuBranchingRatio = 0.108+0.1075+0.1125



relIsoCutMuons = 0.12
relIsoCutElectrons = 0.1

PileUpSeason = "SummerFlatTail11"

PileUpSeason = "Summer12"
PileUpSeasonV6 = "Summer12V6"

PileUpNewWJets = "pileUpDistrNewWJets"
PileUpNewTTBar = "pileUpDistrNewTTBar"

PileUpSeasonFall = "Fall12"

TChannelMu = cms.PSet(
#    crossSection = cms.untracked.double(41.92*wToLNuBranchingRatio),
    crossSection = cms.untracked.double(18.2736),
    channel = cms.untracked.string("TChannel"),
    originalEvents = cms.untracked.double(3915598),
    finalLumi = lumiMu,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),
    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
#   Season = cms.untracked.string(""),
    )
    
    
TChannelEle = cms.PSet(
#    crossSection = cms.untracked.double(41.92*wToLNuBranchingRatio),
    crossSection = cms.untracked.double(18.2736),
    channel = cms.untracked.string("TChannel"),
    originalEvents = cms.untracked.double(3915598),
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
    MTWCut = cms.untracked.double(40.0),#Default 50.0 GeV
    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    )

TbarChannelMu = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(9.9468),
    channel = cms.untracked.string("TbarChannel"),
#    originalEvents = cms.untracked.double(1935072),
    originalEvents = cms.untracked.double(1711403),
    finalLumi = lumiMu,Season = cms.untracked.string(PileUpSeasonFall),
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    )


TbarChannelEle = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(9.9468),
    channel = cms.untracked.string("TbarChannel"),
#    originalEvents = cms.untracked.double(1935072),
    originalEvents = cms.untracked.double(1711403),
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
    MTWCut = cms.untracked.double(40.0),#Default 50.0 GeV
    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    )


TWChannelMu = cms.PSet(
        crossSection = cms.untracked.double(11.1),
        channel = cms.untracked.string("TWChannel"),
        #            originalEvents = cms.untracked.double(494961),
        originalEvents = cms.untracked.double(497658),
        finalLumi = lumiMu,Season = cms.untracked.string(PileUpSeasonFall),
        MTWCut = cms.untracked.double(40.0),#Default 50.0 GeV
        RelIsoCut = cms.untracked.double(relIsoCutMuons),
        mcPUFile = cms.untracked.string("pileupdistr_TWChannel.root"),
        puHistoName = cms.untracked.string("pileUpDumper/PileUpTWChannel"),
            )

TWChannelEle = cms.PSet(
        crossSection = cms.untracked.double(11.1),
        channel = cms.untracked.string("TWChannel"),
        RelIsoCut = cms.untracked.double(relIsoCutElectrons),
        finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
        originalEvents = cms.untracked.double(497658),
        #            originalEvents = cms.untracked.double(494961),
        mcPUFile = cms.untracked.string("pileupdistr_TWChannel.root"),
        puHistoName = cms.untracked.string("pileUpDumper/PileUpTWChannel"),

            )


TbarWChannelMu = cms.PSet(
        crossSection = cms.untracked.double(11.1),
            channel = cms.untracked.string("TbarWChannel"),
#            originalEvents = cms.untracked.double(494961),
            originalEvents = cms.untracked.double(493460),
            finalLumi = lumiMu,Season = cms.untracked.string(PileUpSeasonFall),
            MTWCut = cms.untracked.double(40.0),#Default 50.0 GeV
                RelIsoCut = cms.untracked.double(relIsoCutMuons),

        mcPUFile = cms.untracked.string("pileupdistr_TWChannel.root"),
        puHistoName = cms.untracked.string("pileUpDumper/PileUpTWChannel"),
            )

TbarWChannelEle = cms.PSet(
        crossSection = cms.untracked.double(11.1),
        channel = cms.untracked.string("TbarWChannel"),
        finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
        RelIsoCut = cms.untracked.double(relIsoCutElectrons),
        originalEvents = cms.untracked.double(493460),
        #            originalEvents = cms.untracked.double(494961),
        mcPUFile = cms.untracked.string("pileupdistr_TWChannel.root"),
        puHistoName = cms.untracked.string("pileUpDumper/PileUpTWChannel"),

            )

SChannelMu = cms.PSet(
#            crossSection = cms.untracked.double(4.63*wToLNuBranchingRatio),
            crossSection = cms.untracked.double(1.22796),
            channel = cms.untracked.string("SChannel"),
            originalEvents = cms.untracked.double(3932710),
            #                        originalEvents = cms.untracked.double(259971),
            finalLumi = lumiMu,Season = cms.untracked.string(PileUpSeasonFall),
            MTWCut = cms.untracked.double(40.0),#Default 50.0 GeV
            RelIsoCut = cms.untracked.double(relIsoCutMuons),
            mcPUFile = cms.untracked.string("pileupdistr_SChannel.root"),
#            mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
        puHistoName = cms.untracked.string("pileUpDumper/PileUpSChannel"),
                        )

SChannelEle = cms.PSet(
            crossSection = cms.untracked.double(1.22796),
            RelIsoCut = cms.untracked.double(relIsoCutElectrons),
            channel = cms.untracked.string("SChannel"),
            finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
            originalEvents = cms.untracked.double(3932710),
            #                        originalEvents = cms.untracked.double(259971),
            mcPUFile = cms.untracked.string("pileupdistr_SChannel.root"),
            #            mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
            puHistoName = cms.untracked.string("pileUpDumper/PileUpSChannel"),

                        )


SbarChannelMu = cms.PSet(
            crossSection = cms.untracked.double(0.57024),
            channel = cms.untracked.string("SbarChannel"),
            originalEvents = cms.untracked.double(1984430),
            finalLumi = lumiMu,Season = cms.untracked.string(PileUpSeasonFall),
            MTWCut = cms.untracked.double(40.0),#Default 50.0 GeV
            RelIsoCut = cms.untracked.double(relIsoCutMuons),
            mcPUFile = cms.untracked.string("pileupdistr_SChannel.root"),
            puHistoName = cms.untracked.string("pileUpDumper/PileUpSChannel"),
            )

SbarChannelEle = cms.PSet(
            crossSection = cms.untracked.double(0.57024),
            RelIsoCut = cms.untracked.double(relIsoCutElectrons),
            channel = cms.untracked.string("SbarChannel"),
            finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
            originalEvents = cms.untracked.double(1984430),
            mcPUFile = cms.untracked.string("pileupdistr_SChannel.root"),
            puHistoName = cms.untracked.string("pileUpDumper/PileUpSChannel"),
            )

#sf = 431/490 = 0,879591837* 25490579 = 22421305
ZJetsMu = cms.PSet(
    crossSection = cms.untracked.double(3503.71),
    channel = cms.untracked.string("ZJets"),
    finalLumi = lumiMu,Season = cms.untracked.string(PileUpSeasonFall),
    originalEvents = cms.untracked.double(30394503),
#    originalEvents = cms.untracked.double(25490579),
    MTWCut = cms.untracked.double(40.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),
    mcPUFile = cms.untracked.string("pileupdistr_ZJets.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpZJets"),
    PUFileNew = cms.untracked.string(PileUpNewTTBar),
)


ZJetsEle = cms.PSet(
    crossSection = cms.untracked.double(3503.71),
    channel = cms.untracked.string("ZJets"),
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
    originalEvents = cms.untracked.double(30394503),
#    originalEvents = cms.untracked.double(22421305),#3 6 277 961
    mcPUFile = cms.untracked.string("pileupdistr_ZJets.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpZJets"),
    PUFileNew = cms.untracked.string(PileUpNewTTBar),
)


smallWYield = 18393090
bigWYield = 57355131#57709905
#WYield = cms.untracked.double(smallWYield+bigWYield)
WYield = 18393090+57355131#57709905

WJetsMu = cms.PSet(
    crossSection = cms.untracked.double(36257.2),
    channel = cms.untracked.string("WJets"),
    finalLumi = lumiMu,Season = cms.untracked.string(PileUpSeasonFall),
#    originalEvents = cms.untracked.double(57709905),
    originalEvents = cms.untracked.double((WYield)),
    MTWCut = cms.untracked.double(40.0),#Default 50.0 GeV
        RelIsoCut = cms.untracked.double(relIsoCutMuons),

    mcPUFile = cms.untracked.string("pileupdistr_WJets.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpWJets"),
)


WJetsEle = cms.PSet(
    crossSection = cms.untracked.double(36257.2),
    channel = cms.untracked.string("WJets"),
RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
#    originalEvents = cms.untracked.double(81352581),
#    originalEvents = cms.untracked.double(18393090),
    originalEvents = cms.untracked.double(WYield),
#    originalEvents = cms.untracked.double(76106157),
    mcPUFile = cms.untracked.string("pileupdistr_WJets.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpWJets"),
    )
  


W1JetMu = cms.PSet(
    crossSection = cms.untracked.double(5400.),
    channel = cms.untracked.string("WJets"),
    finalLumi = lumiMu,Season = cms.untracked.string(PileUpSeasonFall),
#    originalEvents = cms.untracked.double(18393090),
    originalEvents = cms.untracked.double(29704800),#originalEvents = cms.untracked.double(18393090),
    MTWCut = cms.untracked.double(40.0),#Default 50.0 GeV
        RelIsoCut = cms.untracked.double(relIsoCutMuons),

    mcPUFile = cms.untracked.string("pileupdistr_WJets.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpWJets"),
    )
W1JetEle = cms.PSet(
    crossSection = cms.untracked.double(5400.),
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    channel = cms.untracked.string("WJets"),
    finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
    originalEvents = cms.untracked.double(29704800),
    #originalEvents = cms.untracked.double(18393090),
    mcPUFile = cms.untracked.string("pileupdistr_WJets.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpWJets"),
    )

W2JetsMu = cms.PSet(
    crossSection = cms.untracked.double(1750.),
    channel = cms.untracked.string("WJets"),
    finalLumi = lumiMu,Season = cms.untracked.string(PileUpSeasonFall),
#    originalEvents = cms.untracked.double(18393090),
    originalEvents = cms.untracked.double(30693853),
    MTWCut = cms.untracked.double(40.0),#Default 50.0 GeV
        RelIsoCut = cms.untracked.double(relIsoCutMuons),

    mcPUFile = cms.untracked.string("pileupdistr_WJets.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpWJets"),
    )
W2JetsEle = cms.PSet(
    crossSection = cms.untracked.double(1750.),
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    channel = cms.untracked.string("WJets"),
    finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
    originalEvents = cms.untracked.double(30693853),
    #originalEvents = cms.untracked.double(18393090),
    mcPUFile = cms.untracked.string("pileupdistr_WJets.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpWJets"),
    )

W3JetsMu = cms.PSet(
    crossSection = cms.untracked.double(519.),
    channel = cms.untracked.string("WJets"),
    finalLumi = lumiMu,Season = cms.untracked.string(PileUpSeasonFall),
#    originalEvents = cms.untracked.double(18393090),
    originalEvents = cms.untracked.double(15241144),
    MTWCut = cms.untracked.double(40.0),#Default 50.0 GeV
        RelIsoCut = cms.untracked.double(relIsoCutMuons),

    mcPUFile = cms.untracked.string("pileupdistr_WJets.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpWJets"),
    )
W3JetsEle = cms.PSet(
    crossSection = cms.untracked.double(519.),
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    channel = cms.untracked.string("WJets"),
    finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
    originalEvents = cms.untracked.double(15241144),
    #originalEvents = cms.untracked.double(18393090),
    mcPUFile = cms.untracked.string("pileupdistr_WJets.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpWJets"),
    )

W4JetsMu = cms.PSet(
    crossSection = cms.untracked.double(214.),
    channel = cms.untracked.string("WJets"),
    finalLumi = lumiMu,Season = cms.untracked.string(PileUpSeasonFall),
#    originalEvents = cms.untracked.double(18393090),
    originalEvents = cms.untracked.double(13382803),#originalEvents = cms.untracked.double(18393090),
    MTWCut = cms.untracked.double(40.0),#Default 50.0 GeV
        RelIsoCut = cms.untracked.double(relIsoCutMuons),

    mcPUFile = cms.untracked.string("pileupdistr_WJets.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpWJets"),
    )

W4JetsEle = cms.PSet(
    crossSection = cms.untracked.double(214.),
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    channel = cms.untracked.string("WJets"),
    finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
    originalEvents = cms.untracked.double(13382803),
    #originalEvents = cms.untracked.double(18393090),
    mcPUFile = cms.untracked.string("pileupdistr_WJets.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpWJets"),
    )


WJetsSherpaMu = cms.PSet(
    crossSection = cms.untracked.double(36257.2),
    channel = cms.untracked.string("WJets"),
    finalLumi = lumiMu,Season = cms.untracked.string(PileUpSeasonFall),
#    originalEvents = cms.untracked.double(18393090),
    originalEvents = cms.untracked.double(97884800),
    MTWCut = cms.untracked.double(40.0),#Default 50.0 GeV
        RelIsoCut = cms.untracked.double(relIsoCutMuons),

    mcPUFile = cms.untracked.string("pileupdistr_WJets.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpWJets"),
    )

WJetsSherpaEle = cms.PSet(
    crossSection = cms.untracked.double(36257.2),
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    channel = cms.untracked.string("WJets"),
    finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
    originalEvents = cms.untracked.double(97884800),#originalEvents = cms.untracked.double(18393090),#originalEvents = cms.untracked.double(18393090),
    mcPUFile = cms.untracked.string("pileupdistr_WJets.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpWJets"),
    )


#Sf = 195/200=0,965346535;
#479/486*10000431=9856392;
WWMu = cms.PSet(
    crossSection = cms.untracked.double(57.1097),
    channel = cms.untracked.string("WW"),
    finalLumi = lumiMu,Season = cms.untracked.string(PileUpSeasonFall),
    originalEvents = cms.untracked.double(10000431),
#    originalEvents = cms.untracked.double(9856392),
    MTWCut = cms.untracked.double(40.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),
    mcPUFile = cms.untracked.string("pileupdistr_WW.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpWW"),
    )

WWEle = cms.PSet(
    crossSection = cms.untracked.double(57.1097),
RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    channel = cms.untracked.string("WW"),
    finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
    originalEvents = cms.untracked.double(10000431),
#    originalEvents = cms.untracked.double(9856392),
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    mcPUFile = cms.untracked.string("pileupdistr_WW.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpWW"),
    )

#sf 185/202 = 0,915841584
# 447/491 = 0.910386965*9799908 = 8921708
ZZMu = cms.PSet(
    crossSection = cms.untracked.double(8.25561),
    channel = cms.untracked.string("ZZ"),
    finalLumi = lumiMu,Season = cms.untracked.string(PileUpSeasonFall),
    originalEvents = cms.untracked.double(9799908),
 #   originalEvents = cms.untracked.double(8921708),
    MTWCut = cms.untracked.double(40.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),
    mcPUFile = cms.untracked.string("pileupdistr_ZZ.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpZZ"),
    )

ZZEle = cms.PSet(
    crossSection = cms.untracked.double(8.25561),
RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    channel = cms.untracked.string("ZZ"),
    finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
    originalEvents = cms.untracked.double(9799908),
 #   originalEvents = cms.untracked.double(8921708),
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    mcPUFile = cms.untracked.string("pileupdistr_ZZ.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpZZ"),
    )
#SF = 460/488=0.942622951*10000283
WZMu = cms.PSet(
    crossSection = cms.untracked.double(32.3161),
    channel = cms.untracked.string("WZ"),
    finalLumi = lumiMu,Season = cms.untracked.string(PileUpSeasonFall),
    originalEvents = cms.untracked.double(10000283),
#    originalEvents = cms.untracked.double(9426496),
    MTWCut = cms.untracked.double(40.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),
    mcPUFile = cms.untracked.string("pileupdistr_WZ.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpWZ"),
    )
WZEle = cms.PSet(
    crossSection = cms.untracked.double(32.3161),
RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    channel = cms.untracked.string("WZ"),
    finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
#    originalEvents = cms.untracked.double(9426496),
    originalEvents = cms.untracked.double(10000283),
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    mcPUFile = cms.untracked.string("pileupdistr_WZ.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpWZ"),
    )

TTBarFullLepEle = cms.PSet(
    #
    crossSection = cms.untracked.double(25.8),
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    channel = cms.untracked.string("TTBar"),
    finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
    originalEvents = cms.untracked.double(12011428),#1089625
    mcPUFile = cms.untracked.string("pileupdistr_TTBar.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTTBar"),
    PUFileNew = cms.untracked.string(PileUpNewTTBar),
    )

TTBarFullLepMu = cms.PSet(
    #    crossSection = cms.untracked.double(26.5484304),
    crossSection = cms.untracked.double(25.8),
    channel = cms.untracked.string("TTBar"),
    originalEvents = cms.untracked.double(12011428),#1089625
    finalLumi = lumiMu,Season = cms.untracked.string(PileUpSeasonFall),
    MTWCut = cms.untracked.double(40.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),
    mcPUFile = cms.untracked.string("pileupdistr_TTBar.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTTBar"),
    PUFileNew = cms.untracked.string(PileUpNewTTBar),
    )

TTBarSemiLepEle = cms.PSet(
    crossSection = cms.untracked.double(107.7),
    channel = cms.untracked.string("TTBar"),
    originalEvents = cms.untracked.double(24963676),
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
    mcPUFile = cms.untracked.string("pileupdistr_TTBar.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTTBar"),
    PUFileNew = cms.untracked.string(PileUpNewTTBar),
    )


TTBarSemiLepMu = cms.PSet(
    #    crossSection = cms.untracked.double(110.7823392),
    crossSection = cms.untracked.double(107.7),
    channel = cms.untracked.string("TTBar"),
    originalEvents = cms.untracked.double(24963676),
    finalLumi = lumiMu,Season = cms.untracked.string(PileUpSeasonFall),
    MTWCut = cms.untracked.double(40.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),
    mcPUFile = cms.untracked.string("pileupdistr_TTBar.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTTBar"),
    PUFileNew = cms.untracked.string(PileUpNewTTBar),
    )


DataMu = cms.PSet(
    crossSection = cms.untracked.double(-1),
    channel = cms.untracked.string("Data"),
    originalEvents = cms.untracked.double(-1),
    finalLumi = cms.untracked.double(-1),
    MTWCut = cms.untracked.double(40.0),#Default 50.0 GeV
   RelIsoCut = cms.untracked.double(relIsoCutMuons),
    mcPUFile = cms.untracked.string("pileupdistr_VV.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpVV"),
    )

DataEle = cms.PSet(
    crossSection = cms.untracked.double(-1),
    channel = cms.untracked.string("Data"),
RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    originalEvents = cms.untracked.double(-1),
    finalLumi = cms.untracked.double(-1),
    mcPUFile = cms.untracked.string("pileupdistr_VV.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpVV"),
    )


QCD_Pt_20to30_EMEnrichedEle = cms.PSet(
    crossSection = cms.untracked.double(2454400.),
#    channel = cms.untracked.string("QCD_Pt_20to30_EMEnriched"),
    channel = cms.untracked.string("QCDEle"),
    finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
   RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    originalEvents = cms.untracked.double(35040695),
    mcPUFile = cms.untracked.string("pileupdistr_QCD_Pt_20to30_EMEnriched.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpQCD_Pt_20to30_EMEnriched"),
    )

#    originalEvents = cms.untracked.double(35040695),

QCD_Pt_20to30_EMEnrichedMu = cms.PSet(
    crossSection = cms.untracked.double(2454400.),
#    channel = cms.untracked.string("QCD_Pt_20to30_EMEnriched"),
    channel = cms.untracked.string("QCDEle"),
   RelIsoCut = cms.untracked.double(relIsoCutMuons),
    finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
    originalEvents = cms.untracked.double(35040695),
    mcPUFile = cms.untracked.string("pileupdistr_QCD_Pt_20to30_EMEnriched.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpQCD_Pt_20to30_EMEnriched"),
    )

QCD_Pt_30to80_EMEnrichedEle = cms.PSet(
    crossSection = cms.untracked.double(4615893.),#
    channel = cms.untracked.string("QCDEle"),
#    channel = cms.untracked.string("QCD_Pt_30to80_EMEnriched"),
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
#   originalEvents = cms.untracked.double(33088888),
    originalEvents = cms.untracked.double(17068476),
    mcPUFile = cms.untracked.string("pileupdistr_QCD_Pt_30to80_EMEnriched.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpQCD_Pt_30to80_EMEnriched"),
    )

QCD_Pt_30to80_EMEnrichedMu = cms.PSet(
        crossSection = cms.untracked.double(4615893.),
    channel = cms.untracked.string("QCDEle"),
#        channel = cms.untracked.string("QCD_Pt_30to80_EMEnriched"),
        RelIsoCut = cms.untracked.double(relIsoCutMuons),
            finalLumi = lumiMu,Season = cms.untracked.string(PileUpSeasonFall),
#            originalEvents = cms.untracked.double(33088888),
        originalEvents = cms.untracked.double(17068476),
        mcPUFile = cms.untracked.string("pileupdistr_QCD_Pt_30to80_EMEnriched.root"),
        puHistoName = cms.untracked.string("pileUpDumper/PileUpQCD_Pt_30to80_EMEnriched"),
            )


QCD_Pt_80to170_EMEnrichedEle = cms.PSet(
    crossSection = cms.untracked.double(183294.9),
    channel = cms.untracked.string("QCDEle"),
#    channel = cms.untracked.string("QCD_Pt_80to170_EMEnriched"),
RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
    originalEvents = cms.untracked.double(34542763),
    mcPUFile = cms.untracked.string("pileupdistr_QCD_Pt_80to170_EMEnriched.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpQCD_Pt_80to170_EMEnriched"),
    )

QCD_Pt_80to170_EMEnrichedMu = cms.PSet(
    crossSection = cms.untracked.double(183294.9),
    channel = cms.untracked.string("QCDEle"),
#    channel = cms.untracked.string("QCD_Pt_80to170_EMEnriched"),
    finalLumi = lumiMu,Season = cms.untracked.string(PileUpSeasonFall),
    RelIsoCut = cms.untracked.double(relIsoCutMuons),
    originalEvents = cms.untracked.double(34542763),
    mcPUFile = cms.untracked.string("pileupdistr_QCD_Pt_80to170_EMEnriched.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpQCD_Pt_80to170_EMEnriched"),
    )

QCD_Pt_170to250_EMEnrichedEle = cms.PSet(
    crossSection = cms.untracked.double(4586.52),
#    channel = cms.untracked.string("QCD_Pt_80to170_EMEnriched"),
    channel = cms.untracked.string("QCDEle"),
RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
    originalEvents = cms.untracked.double(31697066),
    mcPUFile = cms.untracked.string("pileupdistr_QCD_Pt_80to170_EMEnriched.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpQCD_Pt_80to170_EMEnriched"),
    )

QCD_Pt_170to250_EMEnrichedMu = cms.PSet(
    crossSection = cms.untracked.double(4586.52),
    channel = cms.untracked.string("QCDEle"),
#    channel = cms.untracked.string("QCD_Pt_80to170_EMEnriched"),
    finalLumi = lumiMu,Season = cms.untracked.string(PileUpSeasonFall),
    RelIsoCut = cms.untracked.double(relIsoCutMuons),
    originalEvents = cms.untracked.double(31697066),
    mcPUFile = cms.untracked.string("pileupdistr_QCD_Pt_80to170_EMEnriched.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpQCD_Pt_80to170_EMEnriched"),
    )



QCD_Pt_20to30_BCtoEEle = cms.PSet(
    crossSection = cms.untracked.double(132160.),
    channel = cms.untracked.string("QCDEle"),
#    channel = cms.untracked.string("QCD_Pt_20to30_BCtoE"),
RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
    originalEvents = cms.untracked.double(1740229),
    mcPUFile = cms.untracked.string("pileupdistr_QCD_Pt_20to30_BCtoE.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpQCD_Pt_20to30_BCtoE"),
    )

QCD_Pt_20to30_BCtoEMu = cms.PSet(
        crossSection = cms.untracked.double(132160.),
        channel = cms.untracked.string("QCDEle"),
#            channel = cms.untracked.string("QCD_Pt_20to30_BCtoE"),
 RelIsoCut = cms.untracked.double(relIsoCutMuons),
            finalLumi = lumiMu,Season = cms.untracked.string(PileUpSeasonFall),
            originalEvents = cms.untracked.double(1740229),
        mcPUFile = cms.untracked.string("pileupdistr_QCD_Pt_20to30_BCtoE.root"),
        puHistoName = cms.untracked.string("pileUpDumper/PileUpQCD_Pt_20to30_BCtoE"),
            )


QCD_Pt_30to80_BCtoEEle = cms.PSet(
    crossSection = cms.untracked.double(167040.),
    channel = cms.untracked.string("QCDEle"),
#    channel = cms.untracked.string("QCD_Pt_30to80_BCtoE"),
RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
    originalEvents = cms.untracked.double(2048152),
    mcPUFile = cms.untracked.string("pileupdistr_QCD_Pt_30to80_BCtoE.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpQCD_Pt_30to80_BCtoE"),
    )

QCD_Pt_30to80_BCtoEMu = cms.PSet(
        crossSection = cms.untracked.double(167040.),
    channel = cms.untracked.string("QCDEle"),
#            channel = cms.untracked.string("QCD_Pt_30to80_BCtoE"),
 RelIsoCut = cms.untracked.double(relIsoCutMuons),
            finalLumi = lumiMu,Season = cms.untracked.string(PileUpSeasonFall),
            originalEvents = cms.untracked.double(2048152),
        mcPUFile = cms.untracked.string("pileupdistr_QCD_Pt_30to80_BCtoE.root"),
        puHistoName = cms.untracked.string("pileUpDumper/PileUpQCD_Pt_30to80_BCtoE"),
            )


QCD_Pt_80to170_BCtoEEle = cms.PSet(
    crossSection = cms.untracked.double(12981),
    channel = cms.untracked.string("QCDEle"),
#    channel = cms.untracked.string("QCD_Pt_80to170_BCtoE"),
RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
    originalEvents = cms.untracked.double(1945525),
    mcPUFile = cms.untracked.string("pileupdistr_QCD_Pt_80to170_BCtoE.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpQCD_Pt_80to170_BCtoE"),
    )

QCD_Pt_80to170_BCtoEMu = cms.PSet(
        crossSection = cms.untracked.double(12981),
    channel = cms.untracked.string("QCDEle"),
#            channel = cms.untracked.string("QCD_Pt_80to170_BCtoE"),
 RelIsoCut = cms.untracked.double(relIsoCutMuons),
            finalLumi = lumiMu,Season = cms.untracked.string(PileUpSeasonFall),
            originalEvents = cms.untracked.double(1945525),
    mcPUFile = cms.untracked.string("pileupdistr_QCD_Pt_80to170_BCtoE.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpQCD_Pt_80to170_BCtoE"),
            )

QCD_Pt_170to250_BCtoEEle = cms.PSet(
    crossSection = cms.untracked.double( 631.992),
    channel = cms.untracked.string("QCDEle"),
#    channel = cms.untracked.string("QCD_Pt_80to170_BCtoE"),
    relIsoCut = cms.untracked.double(relIsoCutElectrons),
    finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
    originalEvents = cms.untracked.double(1948112),
    mcPUFile = cms.untracked.string("pileupdistr_QCD_Pt_80to170_BCtoE.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpQCD_Pt_80to170_BCtoE"),
    )

QCD_Pt_170to250_BCtoEMu = cms.PSet(
    crossSection = cms.untracked.double( 631.992),
    channel = cms.untracked.string("QCDEle"),
#    channel = cms.untracked.string("QCD_Pt_80to170_BCtoE"),
    RelIsoCut = cms.untracked.double(relIsoCutMuons),
    finalLumi = lumiMu,Season = cms.untracked.string(PileUpSeasonFall),
    originalEvents = cms.untracked.double(1948112),
    mcPUFile = cms.untracked.string("pileupdistr_QCD_Pt_80to170_BCtoE.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpQCD_Pt_80to170_BCtoE"),
            )


QCD_HT_40_100_GJetsEle = cms.PSet(
    crossSection = cms.untracked.double(20930.0),
    channel = cms.untracked.string("QCDEle"),
#    channel = cms.untracked.string("QCD_HT_40_100_GJets"),
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
    originalEvents = cms.untracked.double(19857930),
    mcPUFile = cms.untracked.string("pileupdistr_QCD_HT_40_100_GJets.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpQCD_HT_40_100_GJets"),
    )

QCD_HT_40_100_GJetsMu = cms.PSet(
    crossSection = cms.untracked.double(20930.0),
    channel = cms.untracked.string("QCDEle"),
#    channel = cms.untracked.string("QCD_HT_40_100_GJets"),
    RelIsoCut = cms.untracked.double(relIsoCutMuons),
    finalLumi = lumiMu,Season = cms.untracked.string(PileUpSeasonFall),
    originalEvents = cms.untracked.double(19857930),
    mcPUFile = cms.untracked.string("pileupdistr_QCD_HT_40_100_GJets.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpQCD_HT_40_100_GJets"),
    )


QCD_HT_100_200_GJetsMu = cms.PSet(
    crossSection = cms.untracked.double(5212.0),
    channel = cms.untracked.string("QCDEle"),
#    channel = cms.untracked.string("QCD_HT_100_200_GJets"),
    RelIsoCut = cms.untracked.double(relIsoCutMuons),
    finalLumi = lumiMu,Season = cms.untracked.string(PileUpSeasonFall),
    originalEvents = cms.untracked.double(9612703),
    mcPUFile = cms.untracked.string("pileupdistr_QCD_HT_100_200_GJets.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpQCD_HT_100_200_GJets"),
    )

QCD_HT_100_200_GJetsEle= cms.PSet(
    crossSection = cms.untracked.double(5212.0),
    channel = cms.untracked.string("QCDEle"),
#    channel = cms.untracked.string("QCD_HT_100_200_GJets"),
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    finalLumi = lumiMu,Season = cms.untracked.string(PileUpSeasonFall),
    originalEvents = cms.untracked.double(9612703),
    mcPUFile = cms.untracked.string("pileupdistr_QCD_HT_100_200_GJets.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpQCD_HT_100_200_GJets"),
    )


QCD_HT_200_400_GJetsMu = cms.PSet(
    crossSection = cms.untracked.double(960.5),
    channel = cms.untracked.string("QCDEle"),
#    channel = cms.untracked.string("QCD_HT_200_400_GJets"),
    RelIsoCut = cms.untracked.double(relIsoCutMuons),
    finalLumi = lumiMu,Season = cms.untracked.string(PileUpSeasonFall),
    originalEvents = cms.untracked.double(10494617),
    mcPUFile = cms.untracked.string("pileupdistr_QCD_HT_200_400_GJets.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpQCD_HT_200_400_GJets"),
    )

QCD_HT_200_400_GJetsEle= cms.PSet(
    crossSection = cms.untracked.double(960.5),
    channel = cms.untracked.string("QCDEle"),
#    channel = cms.untracked.string("QCD_HT_200_400_GJets"),
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    finalLumi = lumiMu,Season = cms.untracked.string(PileUpSeasonFall),
    originalEvents = cms.untracked.double(10494617),
    mcPUFile = cms.untracked.string("pileupdistr_QCD_HT_200_400_GJets.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpQCD_HT_200_400_GJets"),
    )


QCD_HT_400_inf_GJetsMu = cms.PSet(
    crossSection = cms.untracked.double(107.5),
     channel = cms.untracked.string("QCDEle"),
#   channel = cms.untracked.string("QCD_HT_400_inf_GJets"),
    RelIsoCut = cms.untracked.double(relIsoCutMuons),
    finalLumi = lumiMu,Season = cms.untracked.string(PileUpSeasonFall),
    originalEvents = cms.untracked.double(1611963),
    mcPUFile = cms.untracked.string("pileupdistr_QCD_HT_400_inf_GJets.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpQCD_HT_400_inf_GJets"),
    )

QCD_HT_400_inf_GJetsEle= cms.PSet(
    crossSection = cms.untracked.double(107.5),
    channel = cms.untracked.string("QCDEle"),
#    channel = cms.untracked.string("QCD_HT_400_inf_GJets"),
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    finalLumi = lumiMu,Season = cms.untracked.string(PileUpSeasonFall),
    originalEvents = cms.untracked.double(1611963),
    mcPUFile = cms.untracked.string("pileupdistr_QCD_HT_400_inf_GJets.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpQCD_HT_400_inf_GJets"),
    )


#sf = 398/432.=0.921296296
#sf = 398/432.=0.921296296
QCDMuMu = cms.PSet(
    crossSection = cms.untracked.double(134680.),
    channel = cms.untracked.string("QCDMu"),
    finalLumi = lumiMu,Season = cms.untracked.string(PileUpSeasonFall),
 RelIsoCut = cms.untracked.double(relIsoCutMuons),
    originalEvents = cms.untracked.double(21484602),
#    originalEvents = cms.untracked.double(19793684),
    mcPUFile = cms.untracked.string("pileupdistr_QCDMu.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpQCDMu"),
    )


QCDMuEle = cms.PSet(
    crossSection = cms.untracked.double(134680.),
    channel = cms.untracked.string("QCDMu"),
RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
#    originalEvents = cms.untracked.double(19793684),
    originalEvents = cms.untracked.double(21484602),
    mcPUFile = cms.untracked.string("pileupdistr_QCDMu.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpQCDMu"),
    )



#Comphep

TToBMuNuMu = cms.PSet(
#    crossSection = cms.untracked.double(41.92*wToLNuBranchingRatio),
    crossSection = cms.untracked.double(9.4176),
    #hannel = cms.untracked.string("TChannel"),
    channel = cms.untracked.string("TToBMuNu"),
    originalEvents = cms.untracked.double(305295),
    finalLumi = lumiMu,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),
    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    isSingleTopCompHEP = cms.untracked.bool(True),
#    Season = cms.untracked.string(""),
    )
    
    
TToBMuNuEle = cms.PSet(
#    crossSection = cms.untracked.double(41.92*wToLNuBranchingRatio),
    crossSection = cms.untracked.double(9.4176),
#   channel = cms.untracked.string("TChannel"),
    channel = cms.untracked.string("TToBMuNu"),
    originalEvents = cms.untracked.double(305295),
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
    MTWCut = cms.untracked.double(40.0),#Default 50.0 GeV
    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    isSingleTopCompHEP = cms.untracked.bool(True),
    )



TToBENuMu = cms.PSet(
#    crossSection = cms.untracked.double(41.92*wToLNuBranchingRatio),
    crossSection = cms.untracked.double(9.4176),
#   channel = cms.untracked.string("TChannel"),
    channel = cms.untracked.string("TToBENu"),
    originalEvents = cms.untracked.double(304318),
    finalLumi = lumiMu,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),
    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    isSingleTopCompHEP = cms.untracked.bool(True),
#    Season = cms.untracked.string(""),
    )
    
    
TToBENuEle = cms.PSet(
#    crossSection = cms.untracked.double(41.92*wToLNuBranchingRatio),
    crossSection = cms.untracked.double(9.4176),
#    channel = cms.untracked.string("TChannel"),
    channel = cms.untracked.string("TToBENu"),
    originalEvents = cms.untracked.double(304318),
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
    MTWCut = cms.untracked.double(40.0),#Default 50.0 GeV
    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    isSingleTopCompHEP = cms.untracked.bool(True),
    )

TToBTauNuMu = cms.PSet(
#    crossSection = cms.untracked.double(41.92*wToLNuBranchingRatio),
    crossSection = cms.untracked.double(9.4176),
#    channel = cms.untracked.string("TChannel"),
    channel = cms.untracked.string("TToBTauNu"),
    originalEvents = cms.untracked.double(304791),
    finalLumi = lumiMu,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),
    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    isSingleTopCompHEP = cms.untracked.bool(True),
#    Season = cms.untracked.string(""),
    )
    
    
TToBTauNuEle = cms.PSet(
#   crossSection = cms.untracked.double(41.92*wToLNuBranchingRatio),
    crossSection = cms.untracked.double(9.4176),
#   channel = cms.untracked.string("TChannel"),
    channel = cms.untracked.string("TToBTauNu"),
    originalEvents = cms.untracked.double(304791),
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
    MTWCut = cms.untracked.double(40.0),#Default 50.0 GeV
    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    isSingleTopCompHEP = cms.untracked.bool(True),
    )





#Comphep_unphys

TToBMuNu_unphysMu = cms.PSet(
#    crossSection = cms.untracked.double(41.92*wToLNu_unphysBranchingRatio),
    crossSection = cms.untracked.double(9.4176),
    #hannel = cms.untracked.string("TChannel"),
    channel = cms.untracked.string("TToBMuNu_unphys"),
    originalEvents = cms.untracked.double(277183),
    finalLumi = lumiMu,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),
    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    isSingleTopCompHEP = cms.untracked.bool(True),
#    Season = cms.untracked.string(""),
    )
    
    
TToBMuNu_unphysEle = cms.PSet(
#    crossSection = cms.untracked.double(41.92*wToLNu_unphysBranchingRatio),
    crossSection = cms.untracked.double(9.4176),
#   channel = cms.untracked.string("TChannel"),
    channel = cms.untracked.string("TToBMuNu_unphys"),
    originalEvents = cms.untracked.double(277183),
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
    MTWCut = cms.untracked.double(40.0),#Default 50.0 GeV
    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    isSingleTopCompHEP = cms.untracked.bool(True),
    )



TToBENu_unphysMu = cms.PSet(
#    crossSection = cms.untracked.double(41.92*wToLNu_unphysBranchingRatio),
    crossSection = cms.untracked.double(9.4176),
#   channel = cms.untracked.string("TChannel"),
    channel = cms.untracked.string("TToBENu_unphys"),
    originalEvents = cms.untracked.double(386000),
    finalLumi = lumiMu,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),
    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    isSingleTopCompHEP = cms.untracked.bool(True),
#    Season = cms.untracked.string(""),
    )
    
    
TToBENu_unphysEle = cms.PSet(
#    crossSection = cms.untracked.double(41.92*wToLNu_unphysBranchingRatio),
    crossSection = cms.untracked.double(9.4176),
#    channel = cms.untracked.string("TChannel"),
    channel = cms.untracked.string("TToBENu_unphys"),
    originalEvents = cms.untracked.double(386000),
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
    MTWCut = cms.untracked.double(40.0),#Default 50.0 GeV
    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    isSingleTopCompHEP = cms.untracked.bool(True),
    )

TToBTauNu_unphysMu = cms.PSet(
#    crossSection = cms.untracked.double(41.92*wToLNu_unphysBranchingRatio),
    crossSection = cms.untracked.double(9.4176),
#    channel = cms.untracked.string("TChannel"),
    channel = cms.untracked.string("TToBTauNu_unphys"),
    originalEvents = cms.untracked.double(389691),
    finalLumi = lumiMu,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),
    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    isSingleTopCompHEP = cms.untracked.bool(True),
#    Season = cms.untracked.string(""),
    )
    
    
TToBTauNu_unphysEle = cms.PSet(
#   crossSection = cms.untracked.double(41.92*wToLNu_unphysBranchingRatio),
    crossSection = cms.untracked.double(9.4176),
#   channel = cms.untracked.string("TChannel"),
    channel = cms.untracked.string("TToBTauNu_unphys"),
    originalEvents = cms.untracked.double(389691),
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
    MTWCut = cms.untracked.double(40.0),#Default 50.0 GeV
    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    isSingleTopCompHEP = cms.untracked.bool(True),
    )





#Comphep_0100

TToBMuNu_0100Mu = cms.PSet(
#    crossSection = cms.untracked.double(41.92*wToLNu_0100BranchingRatio),
    crossSection = cms.untracked.double(9.4176),
    #hannel = cms.untracked.string("TChannel"),
    channel = cms.untracked.string("TToBMuNu_0100"),
    originalEvents = cms.untracked.double(375847),
    finalLumi = lumiMu,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),
    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    isSingleTopCompHEP = cms.untracked.bool(True),
#    Season = cms.untracked.string(""),
    )
    
    
TToBMuNu_0100Ele = cms.PSet(
#    crossSection = cms.untracked.double(41.92*wToLNu_0100BranchingRatio),
    crossSection = cms.untracked.double(9.4176),
#   channel = cms.untracked.string("TChannel"),
    channel = cms.untracked.string("TToBMuNu_0100"),
    originalEvents = cms.untracked.double(375847),
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
    MTWCut = cms.untracked.double(40.0),#Default 50.0 GeV
    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    isSingleTopCompHEP = cms.untracked.bool(True),
    )



TToBENu_0100Mu = cms.PSet(
#    crossSection = cms.untracked.double(41.92*wToLNu_0100BranchingRatio),
    crossSection = cms.untracked.double(9.4176),
#   channel = cms.untracked.string("TChannel"),
    channel = cms.untracked.string("TToBENu_0100"),
    originalEvents = cms.untracked.double(391786),
    finalLumi = lumiMu,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),
    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    isSingleTopCompHEP = cms.untracked.bool(True),
#    Season = cms.untracked.string(""),
    )
    
    
TToBENu_0100Ele = cms.PSet(
#    crossSection = cms.untracked.double(41.92*wToLNu_0100BranchingRatio),
    crossSection = cms.untracked.double(9.4176),
#    channel = cms.untracked.string("TChannel"),
    channel = cms.untracked.string("TToBENu_0100"),
    originalEvents = cms.untracked.double(391786),
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
    MTWCut = cms.untracked.double(40.0),#Default 50.0 GeV
    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    isSingleTopCompHEP = cms.untracked.bool(True),
    )

TToBTauNu_0100Mu = cms.PSet(
#    crossSection = cms.untracked.double(41.92*wToLNu_0100BranchingRatio),
    crossSection = cms.untracked.double(9.4176),
#    channel = cms.untracked.string("TChannel"),
    channel = cms.untracked.string("TToBTauNu_0100"),
    originalEvents = cms.untracked.double(384151),
    finalLumi = lumiMu,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),
    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    isSingleTopCompHEP = cms.untracked.bool(True),
#    Season = cms.untracked.string(""),
    )
    
    
TToBTauNu_0100Ele = cms.PSet(
#   crossSection = cms.untracked.double(41.92*wToLNu_0100BranchingRatio),
    crossSection = cms.untracked.double(9.4176),
#   channel = cms.untracked.string("TChannel"),
    channel = cms.untracked.string("TToBTauNu_0100"),
    originalEvents = cms.untracked.double(384151),
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
    MTWCut = cms.untracked.double(40.0),#Default 50.0 GeV
    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    isSingleTopCompHEP = cms.untracked.bool(True),
    )






#Systs
#37/41=0.902439024
TChannel_Q2UpMu = cms.PSet(
#   crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(17.496),
    channel = cms.untracked.string("TChannel_Q2Up"),
#   originalEvents = cms.untracked.double(1945116),
    originalEvents = cms.untracked.double(1755349),
    finalLumi = lumiMu,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )


TChannel_Q2UpEle = cms.PSet(
#   crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(17.496),
    channel = cms.untracked.string("TChannel_Q2Up"),
#   originalEvents = cms.untracked.double(1945116),
    originalEvents = cms.untracked.double(1755349),
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    finalLumi = lumiEle,
    MTWCut = cms.untracked.double(40.0),#Default 50.0 GeV
    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )





TChannel_Q2DownMu = cms.PSet(
#   crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(17.496),
    channel = cms.untracked.string("TChannel_Q2Down"),
    originalEvents = cms.untracked.double(1901907),
    finalLumi = lumiMu,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),
    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )


TChannel_Q2DownEle = cms.PSet(
#   crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(17.496),
    channel = cms.untracked.string("TChannel_Q2Down"),
    originalEvents = cms.untracked.double(1901907),
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    finalLumi = lumiEle,
    MTWCut = cms.untracked.double(40.0),#Default 50.0 GeV
    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )




#18/21
TbarChannel_Q2UpMu = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(9.9468),
    channel = cms.untracked.string("TbarChannel_Q2Up"),
#   originalEvents = cms.untracked.double(979898),
    originalEvents = cms.untracked.double(839913),
    finalLumi = lumiMu,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )


TbarChannel_Q2UpEle = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(9.9468),
    channel = cms.untracked.string("TbarChannel_Q2Up"),
#   originalEvents = cms.untracked.double(979898),
    originalEvents = cms.untracked.double(839913),
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    finalLumi = lumiEle,
    MTWCut = cms.untracked.double(40.0),#Default 50.0 GeV
    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )




TbarChannel_Q2DownMu = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(9.9468),
    channel = cms.untracked.string("TbarChannel_Q2Down"),
    originalEvents = cms.untracked.double(979359),
    finalLumi = lumiMu,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )


TbarChannel_Q2DownEle = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(9.9468),
    channel = cms.untracked.string("TbarChannel_Q2Down"),
    originalEvents = cms.untracked.double(979359),
RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    finalLumi = lumiEle,
    MTWCut = cms.untracked.double(40.0),#Default 50.0 GeV
    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )


#.108/110=0,981818182
TTBar_Q2DownMu = cms.PSet(
    crossSection = cms.untracked.double(245.8),
    channel = cms.untracked.string("TTBar_Q2Down"),
#   originalEvents = cms.untracked.double(5387181),
    originalEvents = cms.untracked.double(5289232),
    finalLumi = lumiMu,Season = cms.untracked.string(PileUpSeasonFall),
    MTWCut = cms.untracked.double(40.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),
    mcPUFile = cms.untracked.string("pileupdistr_TTBar_Q2Down.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTTBar_Q2Down"),
    )

TTBar_Q2DownEle = cms.PSet(
    crossSection = cms.untracked.double(245.8),
RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    channel = cms.untracked.string("TTBar_Q2Down"),
    finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
#   originalEvents = cms.untracked.double(5387181),
    originalEvents = cms.untracked.double(5289232),
    mcPUFile = cms.untracked.string("pileupdistr_TTBar_Q2Down.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTTBar_Q2Down"),
    )



TTBar_Q2UpMu = cms.PSet(
    crossSection = cms.untracked.double(245.8),
    channel = cms.untracked.string("TTBar_Q2Up"),
    originalEvents = cms.untracked.double(5009488),#3701947),#1089625
    finalLumi = lumiMu,Season = cms.untracked.string(PileUpSeasonFall),
    MTWCut = cms.untracked.double(40.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),
    mcPUFile = cms.untracked.string("pileupdistr_TTBar_Q2Up.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTTBar_Q2Up"),
    )

TTBar_Q2UpEle = cms.PSet(
    crossSection = cms.untracked.double(245.8),
RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    channel = cms.untracked.string("TTBar_Q2Up"),
    finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
    originalEvents = cms.untracked.double(5009488),#3701947),#1089625
    mcPUFile = cms.untracked.string("pileupdistr_TTBar_Q2Up.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTTBar_Q2Up"),
    )



TTBar_MatchingDownMu = cms.PSet(
    crossSection = cms.untracked.double(245.8),
    channel = cms.untracked.string("TTBar_MatchingDown"),
    originalEvents = cms.untracked.double(5476728),#3701947),#1089625
    finalLumi = lumiMu,Season = cms.untracked.string(PileUpSeasonFall),
    MTWCut = cms.untracked.double(40.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),
    mcPUFile = cms.untracked.string("pileupdistr_TTBar_MatchingDown.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTTBar_MatchingDown"),
    )

TTBar_MatchingDownEle = cms.PSet(
    crossSection = cms.untracked.double(245.8),
RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    channel = cms.untracked.string("TTBar_MatchingDown"),
    finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
    originalEvents = cms.untracked.double(5476728),#3701947),#1089625
    mcPUFile = cms.untracked.string("pileupdistr_TTBar_MatchingDown.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTTBar_MatchingDown"),
    )


#107/119=0,899159664
TTBar_MatchingUpMu = cms.PSet(
    crossSection = cms.untracked.double(245.8),
    channel = cms.untracked.string("TTBar_MatchingUp"),
#    originalEvents = cms.untracked.double(5415010),#3701947),#1089625
    originalEvents = cms.untracked.double(4868959),#3701947),#1089625
    finalLumi = lumiMu,Season = cms.untracked.string(PileUpSeasonFall),
    MTWCut = cms.untracked.double(40.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),
    mcPUFile = cms.untracked.string("pileupdistr_TTBar_MatchingUp.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTTBar_MatchingUp"),
    )

TTBar_MatchingUpEle = cms.PSet(
    crossSection = cms.untracked.double(245.8),
RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    channel = cms.untracked.string("TTBar_MatchingUp"),
    finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
#    originalEvents = cms.untracked.double(5415010),#3701947),#1089625
    originalEvents = cms.untracked.double(4868959),#3701947),#1089625
    mcPUFile = cms.untracked.string("pileupdistr_TTBar_MatchingUp.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTTBar_MatchingUp"),
    )


#Systs WJets

WJets_Q2DownMu = cms.PSet(
    crossSection = cms.untracked.double(36257.2),
    channel = cms.untracked.string("WJets_Q2Down"),
    originalEvents = cms.untracked.double(20640884),#3701947),#1089625
    finalLumi = lumiMu,Season = cms.untracked.string(PileUpSeasonFall),
    MTWCut = cms.untracked.double(40.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),
    mcPUFile = cms.untracked.string("pileupdistr_WJets_Q2Down.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpWJets_Q2Down"),
    )

WJets_Q2DownEle = cms.PSet(
    crossSection = cms.untracked.double(36257.2),
RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    channel = cms.untracked.string("WJets_Q2Down"),
    finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
    originalEvents = cms.untracked.double(20640884),#3701947),#1089625
    mcPUFile = cms.untracked.string("pileupdistr_WJets_Q2Down.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpWJets_Q2Down"),
    )



WJets_Q2UpMu = cms.PSet(
    crossSection = cms.untracked.double(36257.2),
    channel = cms.untracked.string("WJets_Q2Up"),
    originalEvents = cms.untracked.double(20664770),#3701947),#1089625
    finalLumi = lumiMu,Season = cms.untracked.string(PileUpSeasonFall),
    MTWCut = cms.untracked.double(40.0),#Default 50.0 GeV
   RelIsoCut = cms.untracked.double(relIsoCutMuons),
    mcPUFile = cms.untracked.string("pileupdistr_WJets_Q2Up.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpWJets_Q2Up"),
    )

WJets_Q2UpEle = cms.PSet(
    crossSection = cms.untracked.double(36257.2),
RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    channel = cms.untracked.string("WJets_Q2Up"),
    finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
    originalEvents = cms.untracked.double(20664770),#3701947),#1089625
    mcPUFile = cms.untracked.string("pileupdistr_WJets_Q2Up.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpWJets_Q2Up"),
    )



WJets_MatchingDownMu = cms.PSet(
    crossSection = cms.untracked.double(36257.2),
    channel = cms.untracked.string("WJets_MatchingDown"),
    originalEvents = cms.untracked.double(21364637),#3701947),#1089625
    finalLumi = lumiMu,Season = cms.untracked.string(PileUpSeasonFall),
    MTWCut = cms.untracked.double(40.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),
    mcPUFile = cms.untracked.string("pileupdistr_WJets_MatchingDown.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpWJets_MatchingDown"),
    )

WJets_MatchingDownEle = cms.PSet(
    crossSection = cms.untracked.double(36257.2),
RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    channel = cms.untracked.string("WJets_MatchingDown"),
    finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
    originalEvents = cms.untracked.double(21364637),#3701947),#1089625
    mcPUFile = cms.untracked.string("pileupdistr_WJets_MatchingDown.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpWJets_MatchingDown"),
    )



WJets_MatchingUpMu = cms.PSet(
    crossSection = cms.untracked.double(36257.2),
    channel = cms.untracked.string("WJets_MatchingUp"),
    originalEvents = cms.untracked.double(20976082),#3701947),#1089625
    finalLumi = lumiMu,Season = cms.untracked.string(PileUpSeasonFall),
    MTWCut = cms.untracked.double(40.0),#Default 50.0 GeV
   RelIsoCut = cms.untracked.double(relIsoCutMuons),
    mcPUFile = cms.untracked.string("pileupdistr_WJets_MatchingUp.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpWJets_MatchingUp"),
    )

WJets_MatchingUpEle = cms.PSet(
    crossSection = cms.untracked.double(36257.2),
RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    channel = cms.untracked.string("WJets_MatchingUp"),
    finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
    originalEvents = cms.untracked.double(20976082),#3701947),#1089625
    mcPUFile = cms.untracked.string("pileupdistr_WJets_MatchingUp.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpWJets_MatchingUp"),
    )



#Systs TW Q2

TWChannelFullLep_Q2UpMu = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(1.1652336),
    channel = cms.untracked.string("TWChannel_Q2Up"),
#    originalEvents = cms.untracked.double(1492816),
    originalEvents = cms.untracked.double(1298750),
    finalLumi = lumiMu,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )

TWChannelFullLep_Q2UpEle = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(1.1652336),
    channel = cms.untracked.string("TWChannel_Q2Up"),
#    originalEvents = cms.untracked.double(1492816),
    originalEvents = cms.untracked.double(1298750),
    finalLumi = lumiEle,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )

TbarWChannelFullLep_Q2UpMu = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(1.1652336),
    channel = cms.untracked.string("TbarWChannel_Q2Up"),
#    originalEvents = cms.untracked.double(1492534),
    originalEvents = cms.untracked.double(1194027),
    finalLumi = lumiMu,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )

TbarWChannelFullLep_Q2UpEle = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(1.1652336),
    channel = cms.untracked.string("TbarWChannel_Q2Up"),
#   originalEvents = cms.untracked.double(1492534),
    originalEvents = cms.untracked.double(1194027),
    finalLumi = lumiEle,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )



TWChannelFullLep_Q2DownMu = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(1.1652336),
    channel = cms.untracked.string("TWChannel_Q2Down"),
#   originalEvents = cms.untracked.double(1493130),
    originalEvents = cms.untracked.double(827874),
    finalLumi = lumiMu,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileDownDumper/PileDownTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )

TWChannelFullLep_Q2DownEle = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(1.1652336),
    channel = cms.untracked.string("TWChannel_Q2Down"),
#   originalEvents = cms.untracked.double(1493130),
    originalEvents = cms.untracked.double(827874),
    finalLumi = lumiEle,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileDownDumper/PileDownTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )

TbarWChannelFullLep_Q2DownMu = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(1.1652336),
    channel = cms.untracked.string("TbarWChannel_Q2Down"),
#    originalEvents = cms.untracked.double(1493101),
    originalEvents = cms.untracked.double(1345269),
    finalLumi = lumiMu,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileDownDumper/PileDownTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )

TbarWChannelFullLep_Q2DownEle = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(1.1652336),
    channel = cms.untracked.string("TbarWChannel_Q2Down"),
#    originalEvents = cms.untracked.double(1493101),
    originalEvents = cms.untracked.double(1345269),
    finalLumi = lumiEle,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileDownDumper/PileDownTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )
####
#


TbarWChannelTlepWhad_Q2DownMu = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(2.4311664),
    channel = cms.untracked.string("TbarWChannel_Q2Down"),
#   originalEvents = cms.untracked.double(497674),
    originalEvents = cms.untracked.double(322024),
    finalLumi = lumiMu,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileDownDumper/PileDownTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )

TbarWChannelTlepWhad_Q2DownEle = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(2.4311664),
    channel = cms.untracked.string("TbarWChannel_Q2Down"),
#   originalEvents = cms.untracked.double(497674),
    originalEvents = cms.untracked.double(322024),
    finalLumi = lumiEle,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileDownDumper/PileDownTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )


TbarWChannelTlepWhad_Q2UpMu = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(2.4311664),
    channel = cms.untracked.string("TbarWChannel_Q2Up"),
#   originalEvents = cms.untracked.double(497376),
    originalEvents = cms.untracked.double(482747),
    finalLumi = lumiMu,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )

TbarWChannelTlepWhad_Q2UpEle = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(2.4311664),
    channel = cms.untracked.string("TbarWChannel_Q2Up"),
#   originalEvents = cms.untracked.double(497376),
    originalEvents = cms.untracked.double(482747),
    finalLumi = lumiEle,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )


TWChannelTlepWhad_Q2DownMu = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(2.4311664),
    channel = cms.untracked.string("TWChannel_Q2Down"),
#   originalEvents = cms.untracked.double(453233),
    originalEvents = cms.untracked.double(190065),
    finalLumi = lumiMu,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileDownDumper/PileDownTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )

TWChannelTlepWhad_Q2DownEle = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(2.4311664),
    channel = cms.untracked.string("TWChannel_Q2Down"),
#    originalEvents = cms.untracked.double(453233),
    originalEvents = cms.untracked.double(190065),
    finalLumi = lumiEle,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileDownDumper/PileDownTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )


TWChannelTlepWhad_Q2UpMu = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(2.4311664),
    channel = cms.untracked.string("TWChannel_Q2Up"),
#   originalEvents = cms.untracked.double(442237),
    originalEvents = cms.untracked.double(250601),
    finalLumi = lumiMu,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )

TWChannelTlepWhad_Q2UpEle = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(2.4311664),
    channel = cms.untracked.string("TWChannel_Q2Up"),
#   originalEvents = cms.untracked.double(442237),
    originalEvents = cms.untracked.double(250601),
    finalLumi = lumiEle,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )

####
#

TbarWChannelThadWlep_Q2DownMu = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(2.4311664),
    channel = cms.untracked.string("TbarWChannel_Q2Down"),
#   originalEvents = cms.untracked.double(497682),
    originalEvents = cms.untracked.double(453769),
    finalLumi = lumiMu,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileDownDumper/PileDownTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )

TbarWChannelThadWlep_Q2DownEle = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(2.4311664),
    channel = cms.untracked.string("TbarWChannel_Q2Down"),
#   originalEvents = cms.untracked.double(497682),
    originalEvents = cms.untracked.double(453769),
    finalLumi = lumiEle,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileDownDumper/PileDownTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )


TbarWChannelThadWlep_Q2UpMu = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(2.4311664),
    channel = cms.untracked.string("TbarWChannel_Q2Up"),
#    originalEvents = cms.untracked.double(497676),
    originalEvents = cms.untracked.double(307388),
    finalLumi = lumiMu,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )

TbarWChannelThadWlep_Q2UpEle = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(2.4311664),
    channel = cms.untracked.string("TbarWChannel_Q2Up"),
#   originalEvents = cms.untracked.double(497676),
    originalEvents = cms.untracked.double(307388),
    finalLumi = lumiEle,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )





TWChannelThadWlep_Q2DownMu = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(2.4311664),
    channel = cms.untracked.string("TWChannel_Q2Down"),
#   originalEvents = cms.untracked.double(496818),
    originalEvents = cms.untracked.double(301102),
    finalLumi = lumiMu,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileDownDumper/PileDownTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )

TWChannelThadWlep_Q2DownEle = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(2.4311664),
    channel = cms.untracked.string("TWChannel_Q2Down"),
#   originalEvents = cms.untracked.double(496818),
    originalEvents = cms.untracked.double(301102),
    finalLumi = lumiEle,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileDownDumper/PileDownTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )


TWChannelThadWlep_Q2UpMu = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(2.4311664),
    channel = cms.untracked.string("TWChannel_Q2Up"),
#    originalEvents = cms.untracked.double(455270),
    originalEvents = cms.untracked.double(205606),
    finalLumi = lumiMu,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )

TWChannelThadWlep_Q2UpEle = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(2.4311664),
    channel = cms.untracked.string("TWChannel_Q2Up"),
#    originalEvents = cms.untracked.double(455270),
    originalEvents = cms.untracked.double(205606),
    finalLumi = lumiEle,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )





#Systs TW Mass

TWChannelFullLep_MassUpMu = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(1.1652336),
    channel = cms.untracked.string("TWChannel_MassUp"),
    originalEvents = cms.untracked.double(1493428),
    finalLumi = lumiMu,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )

TWChannelFullLep_MassUpEle = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(1.1652336),
    channel = cms.untracked.string("TWChannel_MassUp"),
    originalEvents = cms.untracked.double(1493428),
    finalLumi = lumiEle,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )

TbarWChannelFullLep_MassUpMu = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(1.1652336),
    channel = cms.untracked.string("TbarWChannel_MassUp"),
#    originalEvents = cms.untracked.double(1493389),
    originalEvents = cms.untracked.double(1393389),
    finalLumi = lumiMu,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )

TbarWChannelFullLep_MassUpEle = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(1.1652336),
    channel = cms.untracked.string("TbarWChannel_MassUp"),
#   originalEvents = cms.untracked.double(1493389),
    originalEvents = cms.untracked.double(1393389),
    finalLumi = lumiEle,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )



TWChannelFullLep_MassDownMu = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(1.1652336),
    channel = cms.untracked.string("TWChannel_MassDown"),
    originalEvents = cms.untracked.double(1489880),
    finalLumi = lumiMu,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileDownDumper/PileDownTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )

TWChannelFullLep_MassDownEle = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(1.1652336),
    channel = cms.untracked.string("TWChannel_MassDown"),
    originalEvents = cms.untracked.double(1489880),
    finalLumi = lumiEle,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileDownDumper/PileDownTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )

TbarWChannelFullLep_MassDownMu = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(1.1652336),
    channel = cms.untracked.string("TbarWChannel_MassDown"),
#   originalEvents = cms.untracked.double(1478200),
    originalEvents = cms.untracked.double(1428200),
    finalLumi = lumiMu,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileDownDumper/PileDownTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )

TbarWChannelFullLep_MassDownEle = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(1.1652336),
    channel = cms.untracked.string("TbarWChannel_MassDown"),
#    originalEvents = cms.untracked.double(1478200),
    originalEvents = cms.untracked.double(1428200),
    finalLumi = lumiEle,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileDownDumper/PileDownTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )
####
#


TbarWChannelTlepWhad_MassDownMu = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(2.4311664),
    channel = cms.untracked.string("TbarWChannel_MassDown"),
    originalEvents = cms.untracked.double(450000),
    finalLumi = lumiMu,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileDownDumper/PileDownTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )

TbarWChannelTlepWhad_MassDownEle = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(2.4311664),
    channel = cms.untracked.string("TbarWChannel_MassDown"),
    originalEvents = cms.untracked.double(450000),
    finalLumi = lumiEle,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileDownDumper/PileDownTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )


TbarWChannelTlepWhad_MassUpMu = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(2.4311664),
    channel = cms.untracked.string("TbarWChannel_MassUp"),
    originalEvents = cms.untracked.double(497376),
    finalLumi = lumiMu,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )

TbarWChannelTlepWhad_MassUpEle = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(2.4311664),
    channel = cms.untracked.string("TbarWChannel_MassUp"),
    originalEvents = cms.untracked.double(497376),
    finalLumi = lumiEle,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )


TWChannelTlepWhad_MassDownMu = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(2.4311664),
    channel = cms.untracked.string("TWChannel_MassDown"),
    originalEvents = cms.untracked.double(403233),
    finalLumi = lumiMu,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileDownDumper/PileDownTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )

TWChannelTlepWhad_MassDownEle = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(2.4311664),
    channel = cms.untracked.string("TWChannel_MassDown"),
    originalEvents = cms.untracked.double(403233),
    finalLumi = lumiEle,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileDownDumper/PileDownTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )


TWChannelTlepWhad_MassUpMu = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(2.4311664),
    channel = cms.untracked.string("TWChannel_MassUp"),
    originalEvents = cms.untracked.double(442237),
    finalLumi = lumiMu,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )

TWChannelTlepWhad_MassUpEle = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(2.4311664),
    channel = cms.untracked.string("TWChannel_MassUp"),
    originalEvents = cms.untracked.double(442237),
    finalLumi = lumiEle,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )

####
#

TbarWChannelThadWlep_MassDownMu = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(2.4311664),
    channel = cms.untracked.string("TbarWChannel_MassDown"),
    originalEvents = cms.untracked.double(497614),
    finalLumi = lumiMu,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileDownDumper/PileDownTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )

TbarWChannelThadWlep_MassDownEle = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(2.4311664),
    channel = cms.untracked.string("TbarWChannel_MassDown"),
    originalEvents = cms.untracked.double(497614),
    finalLumi = lumiEle,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileDownDumper/PileDownTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )


TbarWChannelThadWlep_MassUpMu = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(2.4311664),
    channel = cms.untracked.string("TbarWChannel_MassUp"),
    originalEvents = cms.untracked.double(497828),
    finalLumi = lumiMu,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )

TbarWChannelThadWlep_MassUpEle = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(2.4311664),
    channel = cms.untracked.string("TbarWChannel_MassUp"),
    originalEvents = cms.untracked.double(497828),
    finalLumi = lumiEle,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )





TWChannelThadWlep_MassDownMu = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(2.4311664),
    channel = cms.untracked.string("TWChannel_MassDown"),
    originalEvents = cms.untracked.double(497598),
    finalLumi = lumiMu,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileDownDumper/PileDownTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )

TWChannelThadWlep_MassDownEle = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(2.4311664),
    channel = cms.untracked.string("TWChannel_MassDown"),
    originalEvents = cms.untracked.double(497598),
    finalLumi = lumiEle,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileDownDumper/PileDownTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )


TWChannelThadWlep_MassUpMu = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(2.4311664),
    channel = cms.untracked.string("TWChannel_MassUp"),
    originalEvents = cms.untracked.double(489678),
    finalLumi = lumiMu,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )

TWChannelThadWlep_MassUpEle = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(2.4311664),
    channel = cms.untracked.string("TWChannel_MassUp"),
    originalEvents = cms.untracked.double(489678),
    finalLumi = lumiEle,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )




######Mass Systematics samples

TTBar_MassDownMu = cms.PSet(
    crossSection = cms.untracked.double(248.),
    channel = cms.untracked.string("TTBar_MassDown"),
#   originalEvents = cms.untracked.double(4469095),#3701947),#1089625
#   originalEvents = cms.untracked.double(909639),#*446/476
   originalEvents = cms.untracked.double(4469095),#*446/476
    finalLumi = lumiMu,Season = cms.untracked.string(PileUpSeasonFall),
    MTWCut = cms.untracked.double(40.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),
    mcPUFile = cms.untracked.string("pileupdistr_TTBar_MassDown.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTTBar_MassDown"),
    )

TTBar_MassDownEle = cms.PSet(
    crossSection = cms.untracked.double(248.),
RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    channel = cms.untracked.string("TTBar_MassDown"),
    finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
#   originalEvents = cms.untracked.double(4469095),#3701947),#1089625
    originalEvents = cms.untracked.double(4469095),#*446/476
#    originalEvents = cms.untracked.double(909639),#*428/452
    mcPUFile = cms.untracked.string("pileupdistr_TTBar_MassDown.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTTBar_MassDown"),
    )


#474/476=0,995798319
TTBar_MassUpMu = cms.PSet(
    crossSection = cms.untracked.double(248.),
    channel = cms.untracked.string("TTBar_MassUp"),
#   originalEvents = cms.untracked.double(4733483),
   originalEvents = cms.untracked.double(4713594),
    finalLumi = lumiMu,Season = cms.untracked.string(PileUpSeasonFall),
    MTWCut = cms.untracked.double(40.0),#Default 50.0 GeV
   RelIsoCut = cms.untracked.double(relIsoCutMuons),
    mcPUFile = cms.untracked.string("pileupdistr_TTBar_MassUp.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTTBar_MassUp"),
    )

TTBar_MassUpEle = cms.PSet(
    crossSection = cms.untracked.double(248.),
RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    channel = cms.untracked.string("TTBar_MassUp"),
    finalLumi = lumiEle,Season = cms.untracked.string(PileUpSeasonFall),
#   originalEvents = cms.untracked.double(4733483),
    originalEvents = cms.untracked.double(4713594),
    mcPUFile = cms.untracked.string("pileupdistr_TTBar_MassUp.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTTBar_MassUp"),
    )



#195/195 0.989847716
TbarChannel_MassUpMu = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(9.9468),
    channel = cms.untracked.string("TbarChannel_MassUp"),
    originalEvents = cms.untracked.double(967539),
    finalLumi = lumiMu,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )


TbarChannel_MassUpEle = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(9.9468),
    channel = cms.untracked.string("TbarChannel_MassUp"),
    originalEvents = cms.untracked.double(967539),
RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    finalLumi = lumiEle,
    MTWCut = cms.untracked.double(40.0),#Default 50.0 GeV
    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )



#
TbarChannel_MassDownMu = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(9.9468),
    channel = cms.untracked.string("TbarChannel_MassDown"),
    originalEvents = cms.untracked.double(891031),
    finalLumi = lumiMu,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )


TbarChannel_MassDownEle = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(9.9468),
    channel = cms.untracked.string("TbarChannel_MassDown"),
    originalEvents = cms.untracked.double(891031),
RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    finalLumi = lumiEle,
    MTWCut = cms.untracked.double(40.0),#Default 50.0 GeV
    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )


#376/379. 1891106
TChannel_MassUpMu = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(17.496),
    channel = cms.untracked.string("TChannel_MassUp"),
#   originalEvents = cms.untracked.double(1891106),
    originalEvents = cms.untracked.double(1876137),
    finalLumi = lumiMu,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )


TChannel_MassUpEle = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(17.496),
    channel = cms.untracked.string("TChannel_MassUp"),
#   originalEvents = cms.untracked.double(1891106),
    originalEvents = cms.untracked.double(1876137),
    RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    finalLumi = lumiEle,
    MTWCut = cms.untracked.double(40.0),#Default 50.0 GeV
    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )



#389/389
TChannel_MassDownMu = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(17.496),
    channel = cms.untracked.string("TChannel_MassDown"),
    originalEvents = cms.untracked.double(1944483),
    finalLumi = lumiMu,
    MTWCut = cms.untracked.double(50.0),#Default 50.0 GeV
    RelIsoCut = cms.untracked.double(relIsoCutMuons),

    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )


TChannel_MassDownEle = cms.PSet(
#    crossSection = cms.untracked.double(22.65 *wToLNuBranchingRatio),
    crossSection = cms.untracked.double(17.496),
    channel = cms.untracked.string("TChannel_MassDown"),
    originalEvents = cms.untracked.double(1944483),
RelIsoCut = cms.untracked.double(relIsoCutElectrons),
    finalLumi = lumiEle,
    MTWCut = cms.untracked.double(40.0),#Default 50.0 GeV
    mcPUFile = cms.untracked.string("pileupdistr_TChannel.root"),
    puHistoName = cms.untracked.string("pileUpDumper/PileUpTChannel"),
    Season = cms.untracked.string(PileUpSeasonFall),
    )
