/*
 *\Author: A. Orso M. Iorio 
 *
 *
 *\version  $Id: SingleTopMETsProducer.cc,v 1.1.2.2 2013/06/21 20:40:25 oiorio Exp $ 
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

#include "TopQuarkAnalysis/SingleTop/interface/SingleTopMETsProducer.h"

#include <vector>
#include <memory>

#include "DataFormats/Math/interface/LorentzVector.h"


//using namespace pat;


SingleTopMETsProducer::SingleTopMETsProducer(const edm::ParameterSet& iConfig) 
{
  metsSrc_                 = iConfig.getParameter<edm::InputTag>	      ( "metsSrc" );
  metsUnclUpSrc_                 = iConfig.getParameter<edm::InputTag>	      ( "metsUnclUpSrc" );
  metsUnclDownSrc_                 = iConfig.getParameter<edm::InputTag>      ( "metsUnclDownSrc" );
  
  isData_                 = iConfig.getUntrackedParameter< bool >	      ( "isData" ,false);
  
  JESUncertaintiesPath_ = iConfig.getParameter< edm::FileInPath >("JESUncertaintiesPath");

  jetsSrc_ = iConfig.getParameter<edm::InputTag>("jetsSrc");
  
  electronsSrc_ = iConfig.getParameter<edm::InputTag>("electronsSrc");
  muonsSrc_ = iConfig.getParameter<edm::InputTag>("muonsSrc");
  photonsSrc_ = iConfig.getParameter<edm::InputTag>("photonsSrc");
  tausSrc_ = iConfig.getParameter<edm::InputTag>("tausSrc");

  pfCandsNotInJetSrc_ = iConfig.getParameter<edm::InputTag>("pfCandsNotInJetSrc");
  
  addExternalUnclusteredMET_ = iConfig.getUntrackedParameter< bool >             ( "addExternalUnclusteredMET" ,false);

  isReco_ = iConfig.getUntrackedParameter< bool >             ( "isReco" ,false);
  isPF_ = iConfig.getUntrackedParameter< bool >             ( "isPF" ,true);
  
  produces<std::vector<pat::MET> >();

  jecUnc  = new JetCorrectionUncertainty(*(new JetCorrectorParameters(JESUncertaintiesPath_.fullPath().data(), "Total")));
  
  //  std::vector<edm::InputTag> names = overlapPSet.getParameterNamesForType< edm::InputTag >

}

void SingleTopMETsProducer::produce(edm::Event & iEvent, const edm::EventSetup & iEventSetup){
    
  iEvent.getByLabel(metsSrc_,mets);
  if(mets->size()!=1){std::cout<<" not exactly 1 met: possible problem in configuration, metx mety not reliable!!!"<<std::endl; 
  }
  
  if(addExternalUnclusteredMET_){  
    iEvent.getByLabel(metsUnclUpSrc_,metsUnclUp);
    iEvent.getByLabel(metsUnclDownSrc_,metsUnclDown);
  }
  else{
    iEvent.getByLabel(metsSrc_,metsUnclUp);
    iEvent.getByLabel(metsSrc_,metsUnclDown);
    
    if(isReco_){
      
      iEvent.getByLabel(electronsSrc_,electrons);
      iEvent.getByLabel(muonsSrc_,muons); 
      iEvent.getByLabel(photonsSrc_,photons);
      iEvent.getByLabel(tausSrc_,taus); 
    }    
    
    if(isPF_){
      iEvent.getByLabel(pfCandsNotInJetSrc_,pfCandsNotInJet);
    }

  }
  iEvent.getByLabel(jetsSrc_,jets);
   
  std::auto_ptr< std::vector< pat::MET > > initialMETs(new std::vector< pat::MET >(*mets));
  std::auto_ptr< std::vector< pat::Jet > > initialJets(new std::vector< pat::Jet >(*jets));
  std::auto_ptr< std::vector< pat::MET > > finalMETs(new std::vector< pat::MET >);
  

  
  if(!isData_)if(metsUnclUp->size()!=1 )std::cout<<" not exactly 1 met: possible problem in configuration, uncl up metx mety not reliable!!!"<<std::endl; 
  if(!isData_)if(metsUnclDown->size()!=1 )std::cout<<" not exactly 1 met: possible problem in configuration, uncl down metx mety not reliable!!! "<<std::endl; 
  
  for(size_t i = 0; i < mets->size(); ++i){
    //    pat::Jet & jet = (*initialJets)[i];
    pat::MET & met = (*initialMETs)[i];

    double metx= met.px(), mety= met.py();
    double jer_metx = metx,jer_mety= mety;

    double jer_up_metx = metx,jer_up_mety= mety;
    double jer_down_metx = metx,jer_down_mety= mety;

    double jes_up_metx = metx,jes_up_mety= mety;
    double jes_down_metx = metx,jes_down_mety= mety;
    
    double uncl_up_metx = metx,uncl_up_mety= mety;
    double uncl_down_metx = metx,uncl_down_mety= mety;
    
    if(!isData_){
      
      if(metsUnclUp->size() <=mets->size()) { uncl_up_metx=metsUnclUp->at(i).px(); uncl_up_mety=metsUnclUp->at(i).py();}
      if(metsUnclDown->size() <=mets->size()) { uncl_down_metx=metsUnclDown->at(i).px(); uncl_down_mety=metsUnclDown->at(i).py();}
      //    std::cout << " metx "<<  metx << " uncl up size "<< metsUnclUp->size() <<" uncl_up_metx " << uncl_up_metx<< std::endl; 
      if(!addExternalUnclusteredMET_){
	if (isReco_){

	  for(size_t m = 0; m < muons->size(); ++m){
	    ;
	  }
	  for(size_t e = 0; e < electrons->size(); ++e){
	    ;
	  }
	  for(size_t ph = 0; ph < photons->size(); ++ph){
	    ;
	  }
	  for(size_t ta = 0; ta < taus->size(); ++ta){
	    ;
	  }
	}
	if (isPF_){
	  
	  //	  std::cout << " metx "<<met.px()<< " mety "<< met.py() << std::endl;
	  for ( edm::View<reco::Candidate>::const_iterator cand = pfCandsNotInJet->begin();
		 cand !=  pfCandsNotInJet->end(); ++cand ) {

	    uncl_up_metx += 0.1*cand->px();
	    uncl_up_mety += 0.1*cand->py();
	    uncl_down_metx -= 0.1*cand->px();
	    uncl_down_mety -= 0.1*cand->py();

	    //	    std::cout << " unclup_metx cand "<<uncl_up_metx<< std::endl;
	    //	    std::cout << " unclup_mety cand "<<uncl_up_mety<< std::endl;
	    //	    += cand->et();
	  }     
	}
      }
      for(size_t j = 0; j < jets->size(); ++j){
      pat::Jet & jet = (*initialJets)[j];
      
      float ptCorr = jet.pt(), genpt=-1;
      if(ptCorr<10){
	
	if(!addExternalUnclusteredMET_){
	  uncl_up_metx += ((0.1)*jet.p4()).px();
	  uncl_up_mety += ((0.1)*jet.p4()).py();
	  
	  uncl_down_metx -= ((0.1)*jet.p4()).px();
	  uncl_down_mety -= ((0.1)*jet.p4()).py();
	  
	  //	  std::cout << " unclup_metx jet "<<uncl_up_metx<< " jet px "<< ((1.)*jet.p4()).px() <<std::endl;
	  //	  std::cout << " unclup_mety jet "<<uncl_up_mety<< " jet py "<< ((1.)*jet.p4()).py() <<std::endl;
	}
	continue;
      }
            

      if(jet.genJet()==0) {
	genpt = ptCorr;
	//	std::cout<<" no jet... ptCorr "<< ptCorr<<" j index "<< j<< std::endl;
      }
      else genpt = jet.genJet()->pt();
      
      //      std::cout << " genpt = "<< genpt<<std::endl;

      float resolScale = resolSF(fabs(jet.eta()),"");
      float smear = 1-std::max((float)(0.0), (float)(ptCorr + (ptCorr - genpt) * resolScale) / ptCorr);
      float resolScaleUp = resolSF(fabs(jet.eta()),"up");
      float smearUp = 1-std::max((float)(0.0), (float)(ptCorr + (ptCorr - genpt) * resolScaleUp) / ptCorr);      
      float resolScaleDown = resolSF(fabs(jet.eta()),"down");
      float smearDown = 1-std::max((float)(0.0), (float)(ptCorr + (ptCorr - genpt) * resolScaleDown) / ptCorr);
      
      //      if(jet.genJet()==0) {smear=1;smearUp =1;smearDown=1;}
     
      jer_metx += (smear*jet.p4()).px();
      jer_mety += (smear*jet.p4()).py();

      //      std::cout << "metPt "<< met.pt() << " corr x "<< (smear*jet.p4()).px() << std::endl; 
      
  
     
      uncl_up_metx +=  (smear*jet.p4()).px();
      uncl_up_mety +=  (smear*jet.p4()).py();
      
      uncl_down_metx +=  (smear*jet.p4()).px();
      uncl_down_mety +=  (smear*jet.p4()).py();


      jer_up_metx += (smearUp*jet.p4()).px();
      jer_up_mety += (smearUp*jet.p4()).py();

      
      jer_down_metx += (smearDown*jet.p4()).px();
      jer_down_mety += (smearDown*jet.p4()).py();
      
      ptCorr = (jet.p4()*(1-smear)).pt();
      float eta = (jet.p4()*(1-smear)).eta();
      float jphi = (jet.p4()*(1-smear)).phi();
      
      jecUnc->setJetPt(ptCorr);
      jecUnc->setJetEta(eta);
      
      float unc = jecUnc->getUncertainty(true);
      
      jes_up_metx -= (ptCorr * cos(jphi)) * unc; 
      jes_down_metx -= -(ptCorr * cos(jphi)) * unc; 


      
      }

      //      met.addUserFloat("met_px_not_in_jet",uncl_down_metx);
      //met.addUserFloat("met_py_not_in_jet",uncl_down_mety);
    
      //      uncl_down_metx=met.px()-0.1*uncl_down_metx;
      //uncl_down_mety=met.py()-0.1*uncl_down_mety;

      //      uncl_up_metx=met.px()+0.1*uncl_up_metx;
      //uncl_up_mety=met.py()+0.1*uncl_up_mety;

      //      std::cout<< " now unclupx "<< uncl_up_metx << " unclupy "<< uncl_up_mety << std::endl; 

    }

  


    reco::Candidate::LorentzVector originalP4(met.p4());
    reco::Candidate::LorentzVector jerP4(jer_metx,jer_mety,met.p4().pz(),sqrt(jer_metx*jer_metx+jer_mety*jer_mety));
    
    reco::Candidate::LorentzVector jerUpP4(jer_up_metx,jer_up_mety,met.p4().pz(),sqrt(jer_up_metx*jer_up_metx+jer_up_mety*jer_up_mety));
    reco::Candidate::LorentzVector jerDownP4(jer_down_metx,jer_down_mety,met.p4().pz(),sqrt(jer_down_metx*jer_down_metx+jer_down_mety*jer_down_mety));

    reco::Candidate::LorentzVector jesUpP4(jes_up_metx,jes_up_mety,met.p4().pz(),sqrt(jes_up_metx*jes_up_metx+jes_up_mety*jes_up_mety));
    reco::Candidate::LorentzVector jesDownP4(jes_down_metx,jes_down_mety,met.p4().pz(),sqrt(jes_down_metx*jes_down_metx+jes_down_mety*jes_down_mety));
    
    reco::Candidate::LorentzVector UnclUpP4(uncl_up_metx,uncl_up_mety,met.p4().pz(),sqrt((uncl_up_metx)*(uncl_up_metx)+(uncl_up_mety)*(uncl_up_mety)));
    reco::Candidate::LorentzVector UnclDownP4(uncl_down_metx,uncl_down_mety,met.p4().pz(),sqrt((uncl_down_metx)*(uncl_down_metx)+(uncl_down_mety)*(uncl_down_mety)));

 
    
    //std::cout << " met pt " << met.pt() << " met phi " << met.phi()<< " met  eta " << met.eta()<< " met e "<< met.energy() <<std::endl; 

    
    met.addUserFloat("pt_no_jer",met.pt());
    met.addUserFloat("phi_no_jer",met.phi());
    
    met.addUserFloat("pt_jer_up",jerUpP4.pt());
    met.addUserFloat("phi_jer_up",jerUpP4.pt());
    
    met.addUserFloat("pt_jer_down",jerDownP4.pt());
    met.addUserFloat("phi_jer_down",jerDownP4.phi());

    met.addUserFloat("pt_jes_up",jesUpP4.pt());
    met.addUserFloat("phi_jes_up",jesUpP4.pt());
    
    met.addUserFloat("pt_jes_down",jesDownP4.pt());
    met.addUserFloat("phi_jes_down",jesDownP4.phi());

    met.addUserFloat("pt_uncl_up",UnclUpP4.pt());
    met.addUserFloat("phi_uncl_up",UnclUpP4.phi());
    
    met.addUserFloat("pt_uncl_down",UnclDownP4.pt());
    met.addUserFloat("phi_uncl_down",UnclDownP4.phi());
    
    met.setP4(jerP4);

    //    std::cout<< " met "  << met.pt()<<std::endl;
    finalMETs->push_back(met);
  } 
  
  iEvent.put(finalMETs);
  
}

double SingleTopMETsProducer::resolSF(double eta, std::string syst)
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


SingleTopMETsProducer::~SingleTopMETsProducer(){;}
DEFINE_FWK_MODULE(SingleTopMETsProducer);
