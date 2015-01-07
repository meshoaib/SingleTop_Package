import FWCore.ParameterSet.Config as cms


nTupleTopJetsPF = cms.EDProducer(
    "CandViewNtpProducer",
    src = cms.InputTag("topJetsPF"),
    lazyParser = cms.untracked.bool(True),
    prefix = cms.untracked.string("topJetsPF"),
    eventInfo=cms.untracked.bool(True),    
    variables = cms.VPSet(
    cms.PSet(
    #B-Tagging
    tag = cms.untracked.string("TrackCountingHighPur"),
    quantity = cms.untracked.string("bDiscriminator('trackCountingHighPurBJetTags')"),
    ),
    cms.PSet(
    tag = cms.untracked.string("PUFullDiscriminant"),
    quantity = cms.untracked.string("userFloat(\"PUFullDiscriminant\")"),
    ),
    cms.PSet(
    tag = cms.untracked.string("PUChargedDiscriminant"),
    quantity = cms.untracked.string("userFloat(\"PUChargedDiscriminant\")"),
    ),
    cms.PSet(
    tag = cms.untracked.string("PUFullWorkingPoint"),
    quantity = cms.untracked.string("userFloat(\"PUFullWorkingPoint\")"),
    ),
    cms.PSet(
    tag = cms.untracked.string("PUChargedWorkingPoint"),
    quantity = cms.untracked.string("userFloat(\"PUChargedWorkingPoint\")"),
    ),
    cms.PSet(
    tag = cms.untracked.string("Beta"),
    quantity = cms.untracked.string("userFloat(\"beta\")"),
    ),
    cms.PSet(
    tag = cms.untracked.string("dZ"),
    quantity = cms.untracked.string("userFloat(\"dZ\")"),
    ),
    cms.PSet(
    tag = cms.untracked.string("BetaStar"),
    quantity = cms.untracked.string("userFloat(\"betaStar\")"),
    ),

    cms.PSet(
    tag = cms.untracked.string("ChargedMultiplicity"),
    quantity = cms.untracked.string("chargedMultiplicity"),
     ),

   cms.PSet(
    tag = cms.untracked.string("NeutralMultiplicity"),
    quantity = cms.untracked.string("neutralMultiplicity"),
     ),
 
    
    cms.PSet(
    tag = cms.untracked.string("RMS"),
    quantity = cms.untracked.string("userFloat(\"RMS\")"),
    ),

    cms.PSet(
    tag = cms.untracked.string("NeuHadEn"),
    quantity = cms.untracked.string("neutralHadronEnergyFraction"),
    ),

    cms.PSet(
    tag = cms.untracked.string("NeuEmEn"),
    quantity = cms.untracked.string("neutralEmEnergyFraction"),
    ),

    cms.PSet(
    tag = cms.untracked.string("CHEmEn"),
    quantity = cms.untracked.string("chargedEmEnergyFraction"),
    ),

    cms.PSet(
    tag = cms.untracked.string("CHHadEn"),
    quantity = cms.untracked.string("chargedHadronEnergyFraction"),
    ),

    cms.PSet(
    tag = cms.untracked.string("CombinedSecondaryVertexBJetTags"),
    quantity = cms.untracked.string("bDiscriminator('combinedSecondaryVertexBJetTags')"),
    ),
    ##    4-momentum
    cms.PSet(
    tag = cms.untracked.string("Pt"),
    quantity = cms.untracked.string("pt")
    ),
    cms.PSet(
    tag = cms.untracked.string("Eta"),
    quantity = cms.untracked.string("eta")
    ),
    cms.PSet(
    tag = cms.untracked.string("Phi"),
    quantity = cms.untracked.string("phi")
    ),
    cms.PSet(
    tag = cms.untracked.string("E"),
    quantity = cms.untracked.string("energy")
    ),
    #Flavour
    cms.PSet(
    tag = cms.untracked.string("Flavour"),
    quantity = cms.untracked.string("partonFlavour")
    ),
    #JEC factor to uncorrected jet
    cms.PSet(
    tag = cms.untracked.string("JetCorrTotal"),
    quantity = cms.untracked.string("jecFactor('Uncorrected')")
    ),
    #Smearing factor: by default the jet pt is smeared 
    cms.PSet(
    tag = cms.untracked.string("Smear"),
    quantity = cms.untracked.string("userFloat('jer_smear')")
    ),
    cms.PSet(
    tag = cms.untracked.string("GenPt"),
    quantity = cms.untracked.string("userFloat('gen_pt')")
    ), 
   cms.PSet(
    tag = cms.untracked.string("SmearUp"),
    quantity = cms.untracked.string("userFloat('jer_smear_up')")
    ),
    cms.PSet(
    tag = cms.untracked.string("SmearDown"),
    quantity = cms.untracked.string("userFloat('jer_smear_down')")
    ),
    #Total uncertainty
    cms.PSet(
    tag = cms.untracked.string("TotalUncertainty"),
    quantity = cms.untracked.string("userFloat('JESUncertaintyTotalShift')")
    ),
    #Systematics momenta:
    cms.PSet(
    tag = cms.untracked.string("PtJESUp"),
    quantity = cms.untracked.string("userFloat('pt_jes_up')")
    ),
    cms.PSet(
    tag = cms.untracked.string("PtJESDown"),
    quantity = cms.untracked.string("userFloat('pt_jes_down')")
    ),
    cms.PSet(
    tag = cms.untracked.string("EJESUp"),
    quantity = cms.untracked.string("userFloat('e_jes_up')")
    ),
    cms.PSet(
    tag = cms.untracked.string("EJESDown"),
    quantity = cms.untracked.string("userFloat('e_jes_down')")
    ),
    cms.PSet(
    tag = cms.untracked.string("PtJERUp"),
    quantity = cms.untracked.string("userFloat('pt_jer_up')")
    ),
    cms.PSet(
    tag = cms.untracked.string("PtJERDown"),
    quantity = cms.untracked.string("userFloat('pt_jer_down')")
    ),
    cms.PSet(
    tag = cms.untracked.string("EJERUp"),
    quantity = cms.untracked.string("userFloat('e_jer_up')")
    ),
    cms.PSet(
    tag = cms.untracked.string("EJERDown"),
    quantity = cms.untracked.string("userFloat('e_jer_down')")
    ),
    #no Jer Pt
    cms.PSet(
    tag = cms.untracked.string("PtNoJER"),
    quantity = cms.untracked.string("userFloat('pt_no_jer')")
    ),
    cms.PSet(
    tag = cms.untracked.string("ENoJER"),
    quantity = cms.untracked.string("userFloat('e_no_jer')")
    ),


    )
)

nTupleVertices = cms.EDProducer(
        "SingleTopVertexInfoDumper",
            src = cms.InputTag("goodOfflinePrimaryVertices"),
        )

nTuplePatMETsPF = cms.EDProducer(
    "CandViewNtpProducer",
    src = cms.InputTag("topMETsPF"),
    lazyParser = cms.untracked.bool(True),
    prefix = cms.untracked.string("patMETsPF"),
    variables = cms.VPSet(
    
    cms.PSet(
    tag = cms.untracked.string("Pt"),
    quantity = cms.untracked.string("pt")
    ),
    cms.PSet(
    tag = cms.untracked.string("Phi"),
    quantity = cms.untracked.string("phi")
    ),

    cms.PSet(
    tag = cms.untracked.string("PtNoJER"),
    quantity = cms.untracked.string("userFloat(\"pt_no_jer\")")
    ),
    cms.PSet(
    tag = cms.untracked.string("PhiNoJER"),
    quantity = cms.untracked.string("userFloat(\"phi_no_jer\")")
    ),

    cms.PSet(
    tag = cms.untracked.string("PtUnclusteredUp"),
    quantity = cms.untracked.string("userFloat('pt_uncl_up')")
    ),
    cms.PSet(
    tag = cms.untracked.string("PhiUnclusteredUp"),
    quantity = cms.untracked.string("userFloat('phi_uncl_up')")
    ),

    cms.PSet(
    tag = cms.untracked.string("PtJESUp"),
    quantity = cms.untracked.string("userFloat('pt_jes_up')")
    ),
    cms.PSet(
    tag = cms.untracked.string("PhiJESUp"),
    quantity = cms.untracked.string("userFloat('phi_jes_up')")
    ),

    cms.PSet(
    tag = cms.untracked.string("PtJERUp"),
    quantity = cms.untracked.string("userFloat('pt_jer_up')")
    ),
    cms.PSet(
    tag = cms.untracked.string("PhiJERUp"),
    quantity = cms.untracked.string("userFloat('phi_jer_up')")
    ),
    
    cms.PSet(
    tag = cms.untracked.string("PtUnclusteredDown"),
    quantity = cms.untracked.string("userFloat('pt_uncl_down')")
    ),
    cms.PSet(
    tag = cms.untracked.string("PhiUnclusteredDown"),
    quantity = cms.untracked.string("userFloat('phi_uncl_down')")
    ),

    cms.PSet(
    tag = cms.untracked.string("PtJESDown"),
    quantity = cms.untracked.string("userFloat('pt_jes_down')")
    ),
    cms.PSet(
    tag = cms.untracked.string("PhiJESDown"),
    quantity = cms.untracked.string("userFloat('phi_jes_down')")
    ),

    cms.PSet(
    tag = cms.untracked.string("PtJERDown"),
    quantity = cms.untracked.string("userFloat('pt_jer_down')")
    ),
    cms.PSet(
    tag = cms.untracked.string("PhiJERDown"),
    quantity = cms.untracked.string("userFloat('phi_jer_down')")
    ),
    

    
    )
    )

nTupleElectrons = cms.EDProducer(
    "CandViewNtpProducer",
    src = cms.InputTag("tightElectrons"),
    lazyParser = cms.untracked.bool(True),
    prefix = cms.untracked.string("tightElectrons"),
    variables = cms.VPSet(
    #4-momentum
    cms.PSet(
    tag = cms.untracked.string("Pt"),
    quantity = cms.untracked.string("ecalDrivenMomentum.pt")
    ),
    cms.PSet(
    tag = cms.untracked.string("Eta"),
    quantity = cms.untracked.string("ecalDrivenMomentum.eta")
    ),
    cms.PSet(
    tag = cms.untracked.string("Phi"),
    quantity = cms.untracked.string("ecalDrivenMomentum.phi")
    ),
    cms.PSet(
    tag = cms.untracked.string("E"),
    quantity = cms.untracked.string("ecalDrivenMomentum.energy")
    ),
    #Charge
    cms.PSet(
    tag = cms.untracked.string("Charge"),
    quantity = cms.untracked.string("charge")
    ),
    #Iso
    cms.PSet(
    tag = cms.untracked.string("PFDeltaCorrectedRelIso"),
    quantity = cms.untracked.string("userFloat(\"DeltaCorrectedIso\")"),
    ),
    cms.PSet(
    tag = cms.untracked.string("PFRelIso"),
    quantity = cms.untracked.string('(chargedHadronIso+ neutralHadronIso + photonIso)/pt'),
    ),
    #ID
    cms.PSet(
    tag = cms.untracked.string("PassesTrigTightID"),
    quantity = cms.untracked.string("userFloat(\"PassesTriggerTightID\")"),
    ),
    cms.PSet(
    tag = cms.untracked.string("PassesTightID"),
    quantity = cms.untracked.string("userFloat(\"PassesTightID\")"),
    ),
    cms.PSet(
    tag = cms.untracked.string("PassesLooseID"),
    quantity = cms.untracked.string("userFloat(\"PassesLooseID\")"),
    ),
    cms.PSet(
    tag = cms.untracked.string("PassesVetoID"),
    quantity = cms.untracked.string("userFloat(\"PassesVetoID\")"),
    ),
    cms.PSet(
    tag = cms.untracked.string("MvaTrigV0"),
    quantity = cms.untracked.string("electronID('mvaTrigV0')")
    ),
    cms.PSet(
    tag = cms.untracked.string("PFRhoCorrectedRelIso"),
    quantity = cms.untracked.string("userFloat(\"RhoCorrectedIso\")"),
    ),
    #Number of Hits 
    cms.PSet(
    tag = cms.untracked.string("MissingHits"),
    quantity = cms.untracked.string("gsfTrack.trackerExpectedHitsInner.numberOfHits"),
    ),
    #Vertex 
    cms.PSet(
    tag = cms.untracked.string("PVDxy"),
    quantity = cms.untracked.string("userFloat(\"VertexDxy\")"),
    ),
    cms.PSet(
    tag = cms.untracked.string("PVDz"),
    quantity = cms.untracked.string("userFloat(\"VertexDz\")"),
    ),
    cms.PSet(
    tag = cms.untracked.string("AbsoluteDB"),
    quantity = cms.untracked.string("dB"),
    ),
    )
    )

nTupleMuons = nTupleElectrons.clone(
    src = cms.InputTag("tightMuons"),
    lazyParser = cms.untracked.bool(True),
    prefix = cms.untracked.string("tightMuons"),
    variables = cms.VPSet(
    #4-momentum
    cms.PSet(
    tag = cms.untracked.string("Pt"),
    quantity = cms.untracked.string("pt")
    ),
    cms.PSet(
    tag = cms.untracked.string("Eta"),
    quantity = cms.untracked.string("eta")
    ),
    cms.PSet(
    tag = cms.untracked.string("Phi"),
    quantity = cms.untracked.string("phi")
    ),
    cms.PSet(
    tag = cms.untracked.string("E"),
    quantity = cms.untracked.string("energy")
    ),
    #Charge
    cms.PSet(
    tag = cms.untracked.string("Charge"),
    quantity = cms.untracked.string("charge")
    ),
    #Iso
    cms.PSet(
    tag = cms.untracked.string("PFRelIso"),
    quantity = cms.untracked.string('(chargedHadronIso+ neutralHadronIso + photonIso)/pt'),
    ),
    cms.PSet(
    tag = cms.untracked.string("PFDeltaCorrectedRelIso"),
    quantity = cms.untracked.string("userFloat(\"DeltaCorrectedIso\")"),
    ),
    cms.PSet(
    tag = cms.untracked.string("PFRhoCorrectedRelIso"),
    quantity = cms.untracked.string("userFloat(\"RhoCorrectedIso\")"),
    ),
    #Vertex
    cms.PSet(
    tag = cms.untracked.string("PVDz"),
    quantity = cms.untracked.string("userFloat(\"VertexDz\")"),
    ),
    cms.PSet(
    tag = cms.untracked.string("PVDxy"),
    quantity = cms.untracked.string("userFloat(\"VertexDxy\")"),
    ),
    cms.PSet(
    tag = cms.untracked.string("AbsoluteDB"),
    quantity = cms.untracked.string("dB"),
    ),
    )
    )

nTupleVetoMuons = nTupleMuons.clone(
    src = cms.InputTag("vetoMuons"),
    lazyParser = cms.untracked.bool(True),
    prefix = cms.untracked.string("vetoMuons"),
    variables = cms.VPSet(
    #4-momentum
    cms.PSet(
    tag = cms.untracked.string("Pt"),
    quantity = cms.untracked.string("pt")
    ),
    cms.PSet(
    tag = cms.untracked.string("Eta"),
    quantity = cms.untracked.string("eta")
    ),
    cms.PSet(
    tag = cms.untracked.string("Phi"),
    quantity = cms.untracked.string("phi")
    ),
    cms.PSet(
    tag = cms.untracked.string("E"),
    quantity = cms.untracked.string("energy")
    ),
    #Charge
    cms.PSet(
    tag = cms.untracked.string("Charge"),
    quantity = cms.untracked.string("charge")
    ),
    #Iso
    cms.PSet(
    tag = cms.untracked.string("PFRelIso"),
    quantity = cms.untracked.string('(chargedHadronIso+ neutralHadronIso + photonIso)/pt'),
    ),
    cms.PSet(
    tag = cms.untracked.string("PFDeltaCorrectedRelIso"),
    quantity = cms.untracked.string("userFloat(\"DeltaCorrectedIso\")"),
    ),
    cms.PSet(
    tag = cms.untracked.string("PFRhoCorrectedRelIso"),
    quantity = cms.untracked.string("userFloat(\"RhoCorrectedIso\")"),
    ),
    #Vertex
    cms.PSet(
    tag = cms.untracked.string("PVDz"),
    quantity = cms.untracked.string("userFloat(\"VertexDz\")"),
    ),
    cms.PSet(
    tag = cms.untracked.string("PVDxy"),
    quantity = cms.untracked.string("userFloat(\"VertexDxy\")"),
    ),
    cms.PSet(
    tag = cms.untracked.string("AbsoluteDB"),
    quantity = cms.untracked.string("dB"),
    ),
    )
    )

nTupleAllMuons = nTupleVetoMuons.clone(
    src = cms.InputTag("selectedPatMuons"),
    lazyParser = cms.untracked.bool(True),
    prefix = cms.untracked.string("allMuons"),
    )


nTupleElectrons.variables += (
    cms.PSet(
    tag = cms.untracked.string("TrigPresel"),
    quantity = cms.untracked.string("userFloat(\"trigPresel\")"),
    ),
    )
    

    
nTupleVetoElectrons = nTupleElectrons.clone(
    src = cms.InputTag("vetoElectrons"),
    lazyParser = cms.untracked.bool(True),
    prefix = cms.untracked.string("vetoElectrons"),
    variables = cms.VPSet(
    #4-momentum
    cms.PSet(
    tag = cms.untracked.string("Pt"),
    quantity = cms.untracked.string("ecalDrivenMomentum.pt")
    ),
    cms.PSet(
    tag = cms.untracked.string("Eta"),
    quantity = cms.untracked.string("ecalDrivenMomentum.eta")
    ),
    cms.PSet(
    tag = cms.untracked.string("Phi"),
    quantity = cms.untracked.string("ecalDrivenMomentum.phi")
    ),
    cms.PSet(
    tag = cms.untracked.string("E"),
    quantity = cms.untracked.string("ecalDrivenMomentum.energy")
    ),
    #Charge
    cms.PSet(
    tag = cms.untracked.string("Charge"),
    quantity = cms.untracked.string("charge")
    ),
    #ID
    cms.PSet(
    tag = cms.untracked.string("PassesVetoID"),
    quantity = cms.untracked.string("userFloat(\"PassesVetoID\")"),
    ),
    cms.PSet(
    tag = cms.untracked.string("MvaTrigV0"),
    quantity = cms.untracked.string("electronID('mvaTrigV0')")
    ),
    #Iso
    cms.PSet(
    tag = cms.untracked.string("PFRelIso"),
    quantity = cms.untracked.string('(chargedHadronIso+ neutralHadronIso + photonIso)/pt'),
    ),
    cms.PSet(
    tag = cms.untracked.string("PFDeltaCorrectedRelIso"),
    quantity = cms.untracked.string("userFloat(\"DeltaCorrectedIso\")"),
    ),
    cms.PSet(
    tag = cms.untracked.string("PFRhoCorrectedRelIso"),
    quantity = cms.untracked.string("userFloat(\"RhoCorrectedIso\")"),
    ),
    #Number of Hits 
    cms.PSet(
    tag = cms.untracked.string("MissingHits"),
    quantity = cms.untracked.string("gsfTrack.trackerExpectedHitsInner.numberOfHits"),
    ),
    #Vertex
    cms.PSet(
    tag = cms.untracked.string("PVDxy"),
    quantity = cms.untracked.string("userFloat(\"VertexDxy\")"),
    ),
    cms.PSet(
    tag = cms.untracked.string("PVDz"),
    quantity = cms.untracked.string("userFloat(\"VertexDz\")"),
    ),
    )
    )

nTupleVetoElectrons.variables += (
    cms.PSet(
    tag = cms.untracked.string("TrigPresel"),
    quantity = cms.untracked.string("userFloat(\"trigPresel\")"),
    ),
    )

nTupleAllElectrons = nTupleVetoElectrons.clone(
    src = cms.InputTag("selectedPatElectrons"),
    lazyParser = cms.untracked.bool(True),
    prefix = cms.untracked.string("allElectrons"),
    )

nTupleVetoElectronsMVA = nTupleVetoElectrons.clone(
    src = cms.InputTag("vetoElectronsMVA"),
    lazyParser = cms.untracked.bool(True),
    prefix = cms.untracked.string("vetoElectronsMVA"),
    )

nTupleZVetoElectrons = nTupleVetoElectrons.clone(
    src = cms.InputTag("zVetoElectrons"),
    lazyParser = cms.untracked.bool(True),
    prefix = cms.untracked.string("zVetoElectrons"),
    )

nTupleAllJets = nTupleTopJetsPF.clone(
    src = cms.InputTag("selectedPatJets"),
    lazyParser = cms.untracked.bool(True),
    prefix = cms.untracked.string("allJets"),
    variables = cms.VPSet(
    cms.PSet(
    #B-Tagging
    tag = cms.untracked.string("TrackCountingHighPur"),
    quantity = cms.untracked.string("bDiscriminator('trackCountingHighPurBJetTags')")
    ),
#    cms.PSet(
#    tag = cms.untracked.string("TrackCountingHighEff"),
#    quantity = cms.untracked.string("bDiscriminator('trackCountingHighEffBJetTags')")
#    ),
    cms.PSet(
    tag = cms.untracked.string("CombinedSecondaryVertexBJetTags"),
    quantity = cms.untracked.string("bDiscriminator('combinedSecondaryVertexBJetTags')"),
    ),
    cms.PSet(
    tag = cms.untracked.string("isMatchedByHLTMu17eta2p1CentralPFNoPUJet30BTagIPIter"),
    quantity = cms.untracked.string("1-triggerObjectMatchesByPath(\"HLT_Mu17_eta2p1_CentralPFNoPUJet30_BTagIPIter_v*\").empty()"),
    ),
#    cms.PSet(
#    tag = cms.untracked.string("SecondaryVertexHighPurBJetTags"),
#    quantity = cms.untracked.string("bDiscriminator('simpleSecondaryVertexHighPurBJetTags')"),
#    ),
    #4-momentum
    cms.PSet(
    tag = cms.untracked.string("Pt"),
    quantity = cms.untracked.string("pt")
    ),
    cms.PSet(
    tag = cms.untracked.string("Eta"),
    quantity = cms.untracked.string("eta")
    ),
    cms.PSet(
    tag = cms.untracked.string("Phi"),
    quantity = cms.untracked.string("phi")
    ),
    cms.PSet(
    tag = cms.untracked.string("E"),
    quantity = cms.untracked.string("energy")
    ),
    #Flavour
    cms.PSet(
    tag = cms.untracked.string("Flavour"),
    quantity = cms.untracked.string("partonFlavour")
    ),
    #ID 
#    cms.PSet(
#    tag = cms.untracked.string("NumberOfDaughters"),
#    quantity = cms.untracked.string("numberOfDaughters")
#    ),
#    cms.PSet(
#    tag = cms.untracked.string("ChargedMultiplicity"),
#    quantity = cms.untracked.string("chargedMultiplicity")
#    ),
#    cms.PSet(
#    tag = cms.untracked.string("ChargedHadronEnergyFraction"),
 #   quantity = cms.untracked.string("chargedHadronEnergyFraction")
 #   ),
 #   cms.PSet(
 #   tag = cms.untracked.string("ChargedEmEnergyFraction"),
 #   quantity = cms.untracked.string("chargedEmEnergyFraction")
 #   ),:
 #   cms.PSet(
 #   tag = cms.untracked.string("NeutralHadronEnergyFraction"),
 #   quantity = cms.untracked.string("neutralHadronEnergyFraction")
 #   ),
 #   cms.PSet(
 #   tag = cms.untracked.string("NeutralEmEnergyFraction"),
 #   quantity = cms.untracked.string("neutralEmEnergyFraction")
 #   ),
 #   #JEC factor to uncorrected jet
    cms.PSet(
    tag = cms.untracked.string("JetCorrTotal"),
    quantity = cms.untracked.string("jecFactor('Uncorrected')")
    ),
    )
    )

singleTopMCNeutrinos = cms.EDProducer(
    "CandViewNtpProducer",
    src = cms.InputTag("MCTruthParticles","MCneutrinos"),
    prefix = cms.untracked.string("mcNeutrinos"),

    variables = cms.VPSet(

    cms.PSet(
    tag = cms.untracked.string("PdgId"),
    quantity = cms.untracked.string("pdgId")
    ),


    cms.PSet(
    tag = cms.untracked.string("Pt"),
    quantity = cms.untracked.string("pt")
    ),

        cms.PSet(
    tag = cms.untracked.string("Eta"),
    quantity = cms.untracked.string("eta")
    ),

        cms.PSet(
    tag = cms.untracked.string("Phi"),
    quantity = cms.untracked.string("phi")
    ),

        cms.PSet(
    tag = cms.untracked.string("E"),
    quantity = cms.untracked.string("energy")
    ),

        cms.PSet(
    tag = cms.untracked.string("Charge"),
    quantity = cms.untracked.string("charge")
    ),

        cms.PSet(
    tag = cms.untracked.string("Status"),
    quantity = cms.untracked.string("status")
    ),

    ),

)

nTuplePatType1METsPF = cms.EDProducer(
          "CandViewNtpProducer",
          src = cms.InputTag("patType1CorrectedPFMet"),
          lazyParser = cms.untracked.bool(True),
          prefix = cms.untracked.string("patType1METsPF"),
          variables = cms.VPSet(
    
          cms.PSet(
          tag = cms.untracked.string("Pt"),
          quantity = cms.untracked.string("pt")
          ),
    
          cms.PSet(
          tag = cms.untracked.string("Phi"),
          quantity = cms.untracked.string("phi")
          ),
    
         )
         )
  

nTupleQCDMuons = nTupleMuons.clone(
     src = cms.InputTag("tightMuonsZeroIso"),
     lazyParser = cms.untracked.bool(True),
     prefix = cms.untracked.string("QCDMuons"),
 )

nTupleQCDElectrons = nTupleElectrons.clone(
    src = cms.InputTag("tightElectronsZeroIso"),
    lazyParser = cms.untracked.bool(True),
    prefix = cms.untracked.string("QCDElectrons"),
)
 


#singleTopMCLeptons = singleTopMCNeutrinos.clone( src = cms.InputTag("MCTruthParticles","topLeptons"), prefix = cms.untracked.string("mcLeptons"))
#
#singleTopMCRecoilQuark = singleTopMCNeutrinos.clone( src = cms.InputTag("MCTruthParticles","singleTopRecoilQuark"), prefix = cms.untracked.string("mcRecoilQuark"))
#singleTopMCBQuark = singleTopMCNeutrinos.clone( src = cms.InputTag("MCTruthParticles","bGenParticles"), prefix = cms.untracked.string("mcBQuark"))

singleTopMCLeptons = singleTopMCNeutrinos.clone( src = cms.InputTag("MCTruthParticles","MCleptons"), prefix = cms.untracked.string("MCleptons"))
singleTopMCWs = singleTopMCNeutrinos.clone( src = cms.InputTag("MCTruthParticles","MCws"), prefix = cms.untracked.string("MCws"))
singleTopMCQuarks = singleTopMCNeutrinos.clone( src = cms.InputTag("MCTruthParticles","MCquarks"), prefix = cms.untracked.string("MCquarks"))
singleTopMCBQuarks = singleTopMCNeutrinos.clone( src = cms.InputTag("MCTruthParticles","MCbquarks"), prefix = cms.untracked.string("MCbquarks"))
singleTopMCTops = singleTopMCNeutrinos.clone( src = cms.InputTag("MCTruthParticles","MCtops"), prefix = cms.untracked.string("MCtops"))
singleTopMCTopsW = singleTopMCNeutrinos.clone( src = cms.InputTag("MCTruthParticles","MCtopsW"), prefix = cms.untracked.string("MCtopsW"))
singleTopMCTopsBQuark = singleTopMCNeutrinos.clone( src = cms.InputTag("MCTruthParticles","MCtopsBQuark"), prefix = cms.untracked.string("MCtopsBQuark"))
singleTopMCTopsQuark = singleTopMCNeutrinos.clone( src = cms.InputTag("MCTruthParticles","MCtopsQuark"), prefix = cms.untracked.string("MCtopsQuark"))
singleTopMCTopsQuarkBar = singleTopMCNeutrinos.clone( src = cms.InputTag("MCTruthParticles","MCtopsQuarkBar"), prefix = cms.untracked.string("MCtopsQuarkBar"))
singleTopMCTopsLepton = singleTopMCNeutrinos.clone( src = cms.InputTag("MCTruthParticles","MCtopsLepton"), prefix = cms.untracked.string("MCtopsLepton"))
singleTopMCTopsNeutrino = singleTopMCNeutrinos.clone( src = cms.InputTag("MCTruthParticles","MCtopsNeutrino"), prefix = cms.untracked.string("MCtopsNeutrino"))

#Higgs
singleTopMCHiggs = singleTopMCNeutrinos.clone( src = cms.InputTag("MCTruthParticles","MCHiggs"), prefix = cms.untracked.string("MCHiggs"))
singleTopMCHiggsBQuark = singleTopMCNeutrinos.clone( src = cms.InputTag("MCTruthParticles","MCHiggsBQuark"), prefix = cms.untracked.string("MCHiggsBQuark"))



nTuplesSkimMCTruth =  cms.Sequence(
    singleTopMCLeptons +
    singleTopMCNeutrinos +
    singleTopMCQuarks +
    singleTopMCBQuarks +
    singleTopMCTops +
    singleTopMCTopsBQuark +
    singleTopMCTopsW +
    singleTopMCTopsLepton +
    singleTopMCTopsNeutrino +
    singleTopMCTopsQuark +
    singleTopMCTopsQuarkBar +
    singleTopMCHiggs +
    singleTopMCHiggsBQuark
)


nTuplesSkim = cms.Sequence(
    nTupleTopJetsPF +
    nTupleAllJets +
    nTuplePatMETsPF +
#    nTuplePatType1METsPF +
    nTupleAllElectrons +
    nTupleAllMuons +
    nTupleVetoElectrons +
    nTupleVetoElectronsMVA +
    nTupleVetoMuons +
    nTupleElectrons +
    nTupleMuons +
    nTupleQCDElectrons +
    nTupleQCDMuons +
    nTupleVertices
    )

saveNTuplesSkim = cms.untracked.vstring(
    'drop *',
#    'keep *_nTupleGenerator_*_*',
    'keep *_PDFInfo_*_*',
    
    'keep *_cFlavorHistoryProducer_*_*',
    'keep *_bFlavorHistoryProducer_*_*',

    'keep floats_nTupleAllJets_*_*',
    'keep floats_nTuplePatMETsPF_*_*',
    'keep *_nTupleTopJetsPF_*_*',
    'keep *_NVertices_*_*',
    'keep *_NGenParticles_*_*',
    'keep floats_nTuplePatType1METsPF_*_*',
    'keep *_UnclusteredType1METPF_*_*',
    'keep *_genJetsPF_*_*',
    'keep *_genAllJetsPF_*_*',
    'keep *_nTupleVertices_*_*',
    'keep *_kt6PFJetsForIsolation_rho_*',
     'keep *_UnclusteredMETPF_*_*'
         )



saveNTuplesSkimMu = cms.untracked.vstring(saveNTuplesSkim)
saveNTuplesSkimEle = cms.untracked.vstring(saveNTuplesSkim)

saveNTuplesSkimLoose = cms.untracked.vstring(saveNTuplesSkim)

saveNTuplesSkimMu.append('keep floats_nTupleMuons_*_*')
saveNTuplesSkimEle.append('keep floats_nTupleElectrons_*_*')


##Skimmed Ntuple
saveNTuplesSkimLoose.append('keep floats_nTupleMuons_*_*')
saveNTuplesSkimLoose.append('keep floats_nTupleElectrons_*_*')

saveNTuplesSkimLoose.append('keep floats_nTupleAllMuons_*_*')
saveNTuplesSkimLoose.append('keep floats_nTupleAllElectrons_*_*')

saveNTuplesSkimLoose.append('keep floats_nTupleVetoMuons_*_*')
saveNTuplesSkimLoose.append('keep floats_nTupleVetoElectrons_*_*')
saveNTuplesSkimLoose.append('keep floats_nTupleVetoElectronsMVA_*_*')
#saveNTuplesSkimLoose.append('keep floats_nTupleZVetoElectrons_*_*')

saveNTuplesSkimLoose.append('keep floats_nTupleQCDMuons_*_*')
saveNTuplesSkimLoose.append('keep floats_nTupleQCDElectrons_*_*')
  

saveNTuplesSkimLoose.append('keep *_TriggerResults_*_*')


