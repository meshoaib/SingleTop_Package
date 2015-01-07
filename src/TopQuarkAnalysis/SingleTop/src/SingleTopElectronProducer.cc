/*
 *\Author: A. Orso M. Iorio 
 *
 *
 *\version  $Id: SingleTopElectronProducer.cc,v 1.7.12.4.4.6 2013/06/21 22:08:10 oiorio Exp $ 
 */

// Single Top producer: produces a top candidate made out of a Lepton, a B jet and a MET

#include "PhysicsTools/PatAlgos/plugins/PATJetProducer.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ParameterSet/interface/FileInPath.h"

#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/Common/interface/Association.h"
#include "DataFormats/Candidate/interface/CandAssociation.h"

#include "DataFormats/JetReco/interface/JetTracksAssociation.h"
#include "DataFormats/BTauReco/interface/JetTag.h"
#include "DataFormats/BTauReco/interface/TrackProbabilityTagInfo.h"
#include "DataFormats/BTauReco/interface/TrackIPTagInfo.h"
#include "DataFormats/BTauReco/interface/TrackCountingTagInfo.h"
#include "DataFormats/BTauReco/interface/SecondaryVertexTagInfo.h"
#include "DataFormats/BTauReco/interface/SoftLeptonTagInfo.h"

#include "DataFormats/Candidate/interface/CandMatchMap.h"
#include "SimDataFormats/JetMatching/interface/JetFlavourMatching.h"

#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "DataFormats/EgammaCandidates/interface/Conversion.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"


#include "EgammaAnalysis/ElectronTools/interface/EGammaCutBasedEleId.h"
#include "RecoEgamma/EgammaTools/interface/ConversionTools.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/Common/interface/ValueMap.h"


#include "DataFormats/Math/interface/deltaR.h"

#include "DataFormats/PatCandidates/interface/JetCorrFactors.h"

#include "FWCore/ParameterSet/interface/ConfigurationDescriptions.h"
#include "FWCore/ParameterSet/interface/ParameterSetDescription.h"


#include "FWCore/Framework/interface/Selector.h"

#include "TopQuarkAnalysis/SingleTop/interface/SingleTopElectronProducer.h"


#include "DataFormats/Scalers/interface/DcsStatus.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "RecoEgamma/EgammaTools/interface/ConversionFinder.h"
#include "EgammaAnalysis/ElectronTools/interface/ElectronEffectiveArea.h"
#include "PhysicsTools/SelectorUtils/interface/SimpleCutBasedElectronIDSelectionFunctor.h"

#include "EgammaAnalysis/ElectronTools/interface/EcalIsolationCorrector.h"

#include <vector>
#include <memory>

#include "DataFormats/Math/interface/LorentzVector.h"


//using namespace pat;

typedef std::vector< edm::Handle< edm::ValueMap<reco::IsoDeposit> > >   IsoDepositMaps;
typedef std::vector< edm::Handle< edm::ValueMap<double> > >             IsoDepositVals;


SingleTopElectronProducer::SingleTopElectronProducer(const edm::ParameterSet& iConfig)
{
  src_                 = iConfig.getParameter<edm::InputTag>( "src" );
  cut_ = iConfig.getParameter< std::string >("cut"); 
  rho_ = iConfig.getParameter<edm::InputTag> ("rho");
  deltaR_ = iConfig.getUntrackedParameter<double>         ( "deltaR",0.3 );
  isData_ = iConfig.getUntrackedParameter<bool> ("isData",false);
  

  
  produces<std::vector<pat::Electron> >();
}

void SingleTopElectronProducer::produce(edm::Event & iEvent, const edm::EventSetup & iEventSetup){

  edm::Handle<edm::View<reco::Vertex> > vertices;
  iEvent.getByLabel("offlinePrimaryVertices",vertices);

  isMC_ = !isData_;

  ////std::cout << " mark 0 " << std::endl;

  ////std::cout << " mark 1 " << std::endl;
  //  edm::Handle<edm::View<pat::Electron> > electrons;
  edm::Handle<std::vector<pat::Electron> > electrons;
  iEvent.getByLabel(src_,electrons);
  iEvent.getByLabel(rho_,rho);
  double rhoD = *rho; 
  double energy_ = TMath::Pi()*deltaR_*deltaR_* (*rho);
  
  
  edm::Handle<reco::ConversionCollection> conversions;
  iEvent.getByLabel("allConversions", conversions);
  
  // iso deposits
  //IsoDepositVals isoVals(isoVals_.size());
  //for (size_t j = 0; j < isoVals_.size(); ++j) {
  //  iEvent.getByLabel(isoVals_[j], isoVals[j]);
  //}

  edm::Handle<reco::BeamSpot> beamspot;
  iEvent.getByLabel("offlineBeamSpot", beamspot);
  const reco::BeamSpot &beamSpot = *(beamspot.product());


  Selector cut(cut_);
  std::auto_ptr< std::vector< pat::Electron > > initialElectrons (new std::vector<pat::Electron>(*electrons));
  std::auto_ptr< std::vector< pat::Electron > > finalElectrons (new std::vector<pat::Electron>());

  ////std::cout << " mark 2 " << std::endl;
    
  //  std::cout << "size before "<< initialElectrons->size()<< std::endl;
  
  // Setup a corrector for electrons
  EcalIsolationCorrector ecalIsoCorr(true);


  for(size_t i = 0; i < initialElectrons->size(); ++i){
    
    bool passes = true;
    bool passesTriggerTight = true;    
    bool passesTight = true;    
    bool passesVeto = true; 
    bool passesLoose = true;
    bool trigPresel = false;

    pat::Electron & el = (*initialElectrons)[i];

    //    std::cout << "EA for ele iso = " << ElectronEffectiveArea::GetElectronEffectiveArea(ElectronEffectiveArea::kEleGammaAndNeutralHadronIso03, el.superCluster()->eta(), ElectronEffectiveArea::kEleEAData2012) << endl;

    energy_ =  ElectronEffectiveArea::GetElectronEffectiveArea(ElectronEffectiveArea::kEleGammaAndNeutralHadronIso03, el.superCluster()->eta(), ElectronEffectiveArea::kEleEAData2012)*(*rho);    

    el.addUserFloat("DeltaCorrectedIso",(el.chargedHadronIso() + std::max(0., el.neutralHadronIso() + el.photonIso() -0.5*el.puChargedHadronIso()))/el.et());
    
    el.addUserFloat("RhoCorrectedIso",(el.chargedHadronIso() + std::max(0., el.neutralHadronIso() + el.photonIso() -energy_))/el.et());

    //    cout << "electron rho is "<<  *rho << " earea is "<< ElectronEffectiveArea::GetElectronEffectiveArea(ElectronEffectiveArea::kEleGammaAndNeutralHadronIso03, el.superCluster()->eta(), ElectronEffectiveArea::kEleEAData2012) << " iso is part is "<< el.neutralHadronIso() + el.photonIso()

    
    double dxy= 9900;
    double dz= 9900;
    if(vertices->size()>0) {
      //      if(!(el.gsfTrack() == NULL)) 
      //else std::cout << "electron lost track ref!  Distance being set to an unphysical value (99 meters)."<<std::endl;
      dz = fabs(el.gsfTrack()->dz(vertices->at(0).position()));
      dxy = fabs(el.gsfTrack()->dxy(vertices->at(0).position()));
    }
    //    else std::cout<< "no offline primary vertex! Check again the collections. Distance being set to an unphysical value (99 meters)."<<std::endl;
    
    el.addUserFloat("VertexDz",dz);
    el.addUserFloat("VertexDxy",dxy);
    
    float mH = el.gsfTrack()->trackerExpectedHitsInner().numberOfHits(); 
    el.addUserFloat("mH",mH);



    // preselection to match the trigger condition

    //float uncorrIso = el.dr03EcalRecHitSumEt();
    float corrIso = ecalIsoCorr.correctForHLTDefinition(el, iEvent.id().run(), isData_);

    if(fabs(el.superCluster()->eta()) < 1.479) {
      if(el.sigmaIetaIeta() < 0.014 &&
	 el.hadronicOverEm() < 0.15 &&
	 el.dr03TkSumPt()/el.pt() < 0.2 &&
	 corrIso/el.pt() < 0.2 &&
	 el.dr03HcalTowerSumEt()/el.pt() < 0.2 &&
	 el.gsfTrack()->trackerExpectedHitsInner().numberOfLostHits() == 0)
	 trigPresel = true;
    }
    else {
      if(el.sigmaIetaIeta() < 0.035 &&
	 el.hadronicOverEm() < 0.10 &&
	 el.dr03TkSumPt()/el.pt() < 0.2 &&
	 corrIso/el.pt() < 0.2 &&
	 el.dr03HcalTowerSumEt()/el.pt() < 0.2 &&
	 el.gsfTrack()->trackerExpectedHitsInner().numberOfLostHits() == 0)
	trigPresel = true;
    }
    
    el.addUserFloat("trigPresel",trigPresel);


    // get the mask value
    double iso_ch = el.chargedHadronIso();
    double iso_em = el.photonIso();
    double iso_nh =  el.neutralHadronIso();

    float trackIso      = el.dr03TkSumPt();
    float ecalIso       = el.dr03EcalRecHitSumEt();
    float hcalIso       = el.dr03HcalTowerSumEt();
    
    bool isEB           = el.isEB() ? true : false;
    float pt            = el.ecalDrivenMomentum().pt();
    float eta           = el.superCluster()->eta();
    
    // id variables                                                                                                                                                    
    float dEtaIn        = el.deltaEtaSuperClusterTrackAtVtx();
    float dPhiIn        = el.deltaPhiSuperClusterTrackAtVtx();
    float sigmaIEtaIEta = el.sigmaIetaIeta();
    float hoe           = el.hadronicOverEm();
    float ooemoop       = (1.0/el.ecalEnergy() - el.eSuperClusterOverP()/el.ecalEnergy());
    // conversion rejection variables
    bool vtxFitConversion = ConversionTools::hasMatchedConversion(el, conversions, beamSpot.position());
    float mHits = el.gsfTrack()->trackerExpectedHitsInner().numberOfHits(); 
    
    //    std::cout << " test id: category "<< category_ << " isEB " << isEB << " pt " << pt << " eta "<< eta << 
    //  " dEtaIn " << dEtaIn << " dPhiIn " << dPhiIn << " sigmaIEtaIEta " << sigmaIEtaIEta << " hoe "<< hoe <<
    //  " ooemoop " << ooemoop << " dxy " << dxy  << " dz " << dz << " iso_ch " << iso_ch<< " iso_em " << iso_em<< " iso_nh "<< iso_nh <<
    //  " vtxFitConversion " << vtxFitConversion << " mHits " << mHits << " rhoD " <<rhoD <<  std::endl;
    
    
    bool id = EgammaCutBasedEleId::PassTriggerCuts(EgammaCutBasedEleId::TRIGGERTIGHT, isEB, pt, dEtaIn, dPhiIn, sigmaIEtaIEta, hoe, trackIso, ecalIso, hcalIso);
    passesTriggerTight = passesTriggerTight && id; 
    
    id = EgammaCutBasedEleId::PassWP(EgammaCutBasedEleId::TIGHT, isEB, pt, eta, dEtaIn, dPhiIn, sigmaIEtaIEta, hoe, ooemoop, dxy, dz, iso_ch, iso_em, iso_nh, vtxFitConversion, mHits, rhoD);
    passesTight = passesTight && id;
    
    id = EgammaCutBasedEleId::PassWP(EgammaCutBasedEleId::LOOSE, isEB, pt, eta, dEtaIn, dPhiIn, sigmaIEtaIEta, hoe, ooemoop, dxy, dz, iso_ch, iso_em, iso_nh, vtxFitConversion, mHits, rhoD);
    passesLoose = passesLoose && id;
    
    id = EgammaCutBasedEleId::PassWP(EgammaCutBasedEleId::VETO, isEB, pt, eta, dEtaIn, dPhiIn, sigmaIEtaIEta, hoe, ooemoop, dxy, dz, iso_ch, iso_em, iso_nh, vtxFitConversion, mHits, rhoD);
    passesVeto = passesVeto && id;

    
    el.addUserFloat("PassesTriggerTightID",(float)passesTriggerTight);
    el.addUserFloat("PassesTightID",(float)passesTight);
    el.addUserFloat("PassesVetoID",(float)passesVeto);
    el.addUserFloat("PassesLooseID",(float)passesLoose);

    if(!cut(el)) passes = false;
    if(passes)finalElectrons->push_back(el);
  } 
  
  //  std::cout << "size after "<< finalElectrons->size()<< std::endl;
  ////std::cout << " mark 7 " << std::endl;

  //std::auto_ptr< std::vector< pat::Electron > > finalElectronsPtr(finalElectrons);
 

iEvent.put(finalElectrons);

}

SingleTopElectronProducer::~SingleTopElectronProducer(){;}
DEFINE_FWK_MODULE(SingleTopElectronProducer);
