import FWCore.ParameterSet.Config as cms

def adaptPFMuonsAnd(process,module,postfix="" ):
    print "Adapting PF Muons "
    print "***************** "
#    warningIsolation()
    print
    module.useParticleFlow = True
    if(module.pfMuonSource==cms.InputTag("particleFlow")):
        #module.pfMuonSource    = cms.InputTag("pfIsolatedMuons" + postfix)
        module.userIsolation   = cms.PSet()
        module.isoDeposits = cms.PSet(
            pfChargedHadrons = cms.InputTag("muPFIsoDepositCharged" + postfix),
            pfChargedAll = cms.InputTag("muPFIsoDepositChargedAll" + postfix),
            pfPUChargedHadrons = cms.InputTag("muPFIsoDepositPU" + postfix),
            pfNeutralHadrons = cms.InputTag("muPFIsoDepositNeutral" + postfix),
            pfPhotons = cms.InputTag("muPFIsoDepositGamma" + postfix)
            )
        module.isolationValues = cms.PSet(
            pfChargedHadrons = cms.InputTag("muPFIsoValueCharged04"+ postfix),
            pfChargedAll = cms.InputTag("muPFIsoValueChargedAll04"+ postfix),
            pfPUChargedHadrons = cms.InputTag("muPFIsoValuePU04" + postfix),
            pfNeutralHadrons = cms.InputTag("muPFIsoValueNeutral04" + postfix),
            pfPhotons = cms.InputTag("muPFIsoValueGamma04" + postfix)
            )
        # matching the pfMuons, not the standard muons.
        applyPostfix(process,"muonMatch",postfix).src = module.pfMuonSource
        
        print " muon source:", module.pfMuonSource
        print " isolation  :",
        print module.isolationValues
        print " isodeposits: "
        print module.isoDeposits
        print
        
