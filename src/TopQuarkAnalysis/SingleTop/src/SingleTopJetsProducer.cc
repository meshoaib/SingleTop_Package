/*
 *\Author: A. Orso M. Iorio 
 *
 *
 *\version  $Id: SingleTopJetsProducer.cc,v 1.5.12.3.4.2 2013/06/21 20:40:25 oiorio Exp $ 
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

#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/JetReco/interface/JPTJet.h"
#include "DataFormats/JetReco/interface/CaloJet.h"

#include "DataFormats/PatCandidates/interface/JetCorrFactors.h"

#include "FWCore/ParameterSet/interface/ConfigurationDescriptions.h"
#include "FWCore/ParameterSet/interface/ParameterSetDescription.h"
#include "CMGTools/External/interface/PileupJetIdentifier.h"

#include "CMGTools/External/interface/PileupJetIdentifier.h"

#include "FWCore/Framework/interface/Selector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"

#include "TopQuarkAnalysis/SingleTop/interface/SingleTopJetsProducer.h"

#include <vector>
#include <memory>

#include "DataFormats/Math/interface/LorentzVector.h"
#include "FWCore/ParameterSet/interface/FileInPath.h"
#include "JetMETCorrections/Objects/interface/JetCorrector.h"

//using namespace pat;


SingleTopJetsProducer::SingleTopJetsProducer(const edm::ParameterSet& iConfig) 
{
  src_                 = iConfig.getParameter<edm::InputTag>	      ( "src" );

  PUFullDiscriminant_  = iConfig.getParameter<edm::InputTag>	      ( "puFullDiscriminant" );
  PUFullID_                 = iConfig.getParameter<edm::InputTag>	      ( "puFullID" );

  PUChargedDiscriminant_  = iConfig.getParameter<edm::InputTag>	      ( "puChargedDiscriminant" );
  PUChargedID_                 = iConfig.getParameter<edm::InputTag>	      ( "puChargedID" );

  PUIDVariables_                 = iConfig.getParameter<edm::InputTag>	      ( "puIDVariables" );

  isData_                 = iConfig.getUntrackedParameter< bool >	      ( "isData" ,false);
  
  JESUncertaintiesPath_ = iConfig.getParameter< edm::FileInPath >("JESUncertaintiesPath");
  //  cms.FileInPath('PhysicsTools/PatUtils/data/Summer12_V2_DATA_AK5PF_UncertaintySources.txt'),  
  cut_ = iConfig.getParameter< std::string >("cut"); 
  
  removeOverlap_ = iConfig.getUntrackedParameter< bool >("removeOverlap",true); 
  electronsSrc_ = iConfig.getParameter<edm::InputTag>("electronsSrc");

  produces<std::vector<pat::Jet> >();
  //produces<std::vector<pat::Jet> >();
  //JetCorrectorParameters* jetCorrParameters_ = new JetCorrectorParameters(jetCorrInputFileName_.fullPath().data(), "SubTotalDataMC");
  jecUnc  = new JetCorrectionUncertainty(*(new JetCorrectorParameters(JESUncertaintiesPath_.fullPath().data(), "Total")));
  //jecUnc  = new JetCorrectionUncertainty(*jetCorrParameters_);
  
  //  std::vector<edm::InputTag> names = overlapPSet.getParameterNamesForType< edm::InputTag >

}

void SingleTopJetsProducer::produce(edm::Event & iEvent, const edm::EventSetup & iEventSetup){
  
  
  
  //  for(std::vector<edm::InputTag>::const_iterator it=names.begin();it != names.end;++it){}

  iEvent.getByLabel(src_,jets);
  iEvent.getByLabel(src_,vjets);

  std::auto_ptr< std::vector< pat::Jet > > initialJets(new std::vector< pat::Jet >(*jets));
  std::auto_ptr< std::vector< pat::Jet > > finalJets(new std::vector< pat::Jet >);


  
  iEvent.getByLabel(PUFullDiscriminant_,puFullJetIdMVA);
  iEvent.getByLabel(PUFullID_,puFullJetIdFlag);  
  iEvent.getByLabel(PUChargedDiscriminant_,puChargedJetIdMVA);
  iEvent.getByLabel(PUChargedID_,puChargedJetIdFlag);  

  iEvent.getByLabel(PUIDVariables_, puIDVariables);  

  if(removeOverlap_)iEvent.getByLabel(electronsSrc_,electrons);

  
  for(size_t i = 0; i < jets->size(); ++i){
    //    pat::Jet & jet = (*initialJets)[i];
    pat::Jet & jet = (*initialJets)[i];
    
    bool isOverlapped = false;
    if(removeOverlap_){
      for(size_t e = 0; e < electrons->size(); ++e){
	if(deltaR(jets->at(i),electrons->at(e))<0.1) {
	  isOverlapped = true;
	  break;
	}
      }
    }
    if( isOverlapped)continue;
    
    Selector cut(cut_);
    if(!cut(jet))continue; 

    jet.addUserFloat("PUFullDiscriminant", (*puFullJetIdMVA)[(vjets->refAt(i))]);
    jet.addUserFloat("PUChargedDiscriminant", (*puChargedJetIdMVA)[(vjets->refAt(i))]);
    
    jet.addUserFloat("beta", ((*puIDVariables)[(vjets->refAt(i))]).beta());
    jet.addUserFloat("betaStar", ((*puIDVariables)[(vjets->refAt(i))]).betaStar());
    jet.addUserFloat("RMS", ((*puIDVariables)[(vjets->refAt(i))]).RMS());
    jet.addUserFloat("dZ", ((*puIDVariables)[(vjets->refAt(i))]).dZ());
    
    int wp = 0;
    
    int idflag = (*puFullJetIdFlag)[ (vjets->refAt(i))];
    if( PileupJetIdentifier::passJetId( idflag, PileupJetIdentifier::kLoose ) ) {
	  wp =1;
	}
    if( PileupJetIdentifier::passJetId( idflag, PileupJetIdentifier::kMedium )) {
	  wp =2;
	 }
    if( PileupJetIdentifier::passJetId( idflag, PileupJetIdentifier::kTight )) {
	   wp =3;
	 }
	
    
    jet.addUserFloat("PUFullWorkingPoint",wp);

    int wpchs =0; 
    
    //    int idflagchs = (*puChargedJetIdFlag)[ (vjets->refAt(i))];
    if( PileupJetIdentifier::passJetId( idflag, PileupJetIdentifier::kLoose ) ) {
	  wpchs =1;
	}
    if( PileupJetIdentifier::passJetId( idflag, PileupJetIdentifier::kMedium )) {
	  wpchs =2;
	 }
    if( PileupJetIdentifier::passJetId( idflag, PileupJetIdentifier::kTight )) {
	   wpchs =3;
	 }

    jet.addUserFloat("PUChargedWorkingPoint",wpchs);

    double ptCorr = jet.pt();
    double genpt = -1; 
    if(jet.genJet()!=0) genpt = jet.genJet()->pt();
    
    double resolScale = resolSF(fabs(jet.eta()),"");
    double smear = std::max((double)(0.0), (double)(ptCorr + (ptCorr - genpt) * resolScale) / ptCorr);
    //    std::cout << "test smear * ptCorr " << smear*ptCorr << " v2 "<< std::max(0.0,genpt+(1+resolScale)*(ptCorr-genpt))<< " difference " << smear*ptCorr-std::max(0.0,genpt+(1+resolScale)*(ptCorr-genpt)) << std::endl;
    
    double resolScaleUp = resolSF(fabs(jet.eta()),"up");
    double smearUp = std::max((double)(0.0), (double)(ptCorr + (ptCorr - genpt) * resolScaleUp) / ptCorr);
    
    double resolScaleDown = resolSF(fabs(jet.eta()),"down");
    double smearDown = std::max((double)(0.0), (double)(ptCorr + (ptCorr - genpt) * resolScaleDown) / ptCorr);


      if(jet.genJet()==0) {
	smear = 1;
	smearUp = 1;
	smearDown = 1;
      }
      
      jet.addUserFloat("gen_pt",genpt);
      jet.addUserFloat("jer_smear",smear);
      jet.addUserFloat("jer_smear_up",smearUp);
      jet.addUserFloat("jer_smear_down",smearDown);
      if(isData_) smear=1;
      if(isData_) smearUp=1;
      if(isData_) smearDown=1;
      
      jet.addUserFloat("pt_no_jer",(jet.p4()).pt());
      jet.addUserFloat("eta_no_jer",(jet.p4()).eta());
      jet.addUserFloat("phi_no_jer",(jet.p4()).phi());
      jet.addUserFloat("e_no_jer",(jet.p4()).e());
      
      
      jet.addUserFloat("pt_jer_up",(jet.p4()*smearUp).pt()); 
      jet.addUserFloat("eta_jer_up",(jet.p4()*smearUp).eta());
      jet.addUserFloat("phi_jer_up",(jet.p4()*smearUp).phi());
      jet.addUserFloat("e_jer_up",(jet.p4()*smearUp).e());
      
      jet.addUserFloat("pt_jer_down",(jet.p4()*smearDown).pt());
      jet.addUserFloat("eta_jer_down",(jet.p4()*smearDown).eta());
      jet.addUserFloat("phi_jer_down",(jet.p4()*smearDown).phi());
      jet.addUserFloat("e_jer_down",(jet.p4()*smearDown).e());
      
      jet.setP4(jet.p4()*smear);
      
      jecUnc->setJetEta(jet.eta());
      jecUnc->setJetPt(jet.pt());
      double JetCorrection = jecUnc->getUncertainty(true);

      if(isData_) JetCorrection=0;
      jet.addUserFloat("JESUncertaintyTotalShift",JetCorrection);
      
      jet.addUserFloat("pt_jes_up",(jet.p4()*(1+JetCorrection)).pt());
      jet.addUserFloat("eta_jes_up",(jet.p4()*(1+JetCorrection)).eta());
      jet.addUserFloat("phi_jes_up",(jet.p4()*(1+JetCorrection)).phi());
      jet.addUserFloat("e_jes_up",(jet.p4()*(1+JetCorrection)).e());
      
      jet.addUserFloat("pt_jes_down",(jet.p4()*(1-JetCorrection)).pt());
      jet.addUserFloat("eta_jes_down",(jet.p4()*(1-JetCorrection)).eta());
      jet.addUserFloat("phi_jes_down",(jet.p4()*(1-JetCorrection)).phi());
      jet.addUserFloat("e_jes_down",(jet.p4()*(1-JetCorrection)).e());
    
    finalJets->push_back(jet);
  } 
  
  iEvent.put(finalJets);

}

double SingleTopJetsProducer::resolSF(double eta, std::string syst)
{
    double fac = 0.;
    if (syst == "up")fac = 1.;
    if (syst == "down")fac = -1.;
    if (eta <= 0.5) return 0.052 + 0.063 * fac;
    else if ( eta > 0.5 && eta <= 1.1 ) return 0.057 + 0.057 * fac;
    else if ( eta > 1.1 && eta <= 1.7 ) return 0.096 + 0.065 * fac;
    else if ( eta > 1.7 && eta <= 2.3 ) return 0.134 + 0.093 * fac;
    else if ( eta > 2.3 && eta <= 5. ) return 0.288 + 0.200 * fac;
    return 0.1;
}


SingleTopJetsProducer::~SingleTopJetsProducer(){;}
DEFINE_FWK_MODULE(SingleTopJetsProducer);
