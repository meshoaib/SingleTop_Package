/*
 *\Authors:A.Giammanco, A. Orso M. Iorio 
 *
 *
 *\version  $Id: SingleTopMCProducer.cc,v 1.1.2.2 2013/06/21 20:40:25 oiorio Exp $ 
 */

// Single Top MC producer 


#define DEBUG    0 // 0=false

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
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "DataFormats/Math/interface/deltaR.h"

#include "DataFormats/PatCandidates/interface/JetCorrFactors.h"

#include "FWCore/ParameterSet/interface/ConfigurationDescriptions.h"
#include "DataFormats/Math/interface/LorentzVector.h"

#include <Math/VectorUtil.h>
#include "FWCore/ParameterSet/interface/ParameterSetDescription.h"
#include "TopQuarkAnalysis/SingleTop/interface/SingleTopSystematicsTreesDumper.h"

#include "FWCore/Framework/interface/Selector.h"
#include "TopQuarkAnalysis/SingleTop/interface/EquationSolver.h"


#include "TVector3.h"
#include "TRandom3.h"

////////Part to be made official
#include "../interface/SingleTopPseudoAnalysisProducer.h"

#include <vector>
#include <memory>



//using namespace pat;
//Note: very simple code, just does a trivial selection of 2 jets


using namespace std;
using namespace edm;
using namespace reco;

SingleTopPseudoAnalysisProducer::SingleTopPseudoAnalysisProducer(const edm::ParameterSet& iConfig) 
{
  // initialize the configurables

  //GenJets for matching
  genJetsSrc_ = iConfig.getParameter<edm::InputTag>( "genJetsSource" );
  //  genParticlesSrc_ = iConfig.getParameter<edm::InputTag>( "genParticlesSource" );
  genJetsDeltarMatching_ = iConfig.getUntrackedParameter<double> ( "genJetsDeltarMatching", 0.3 );
  leptonThreshold_ = iConfig.getUntrackedParameter<double> ( "leptonThreshold", 26.0);
  jetThreshold_ = iConfig.getUntrackedParameter<double> ( "jetThreshold", 40.0 );
  metThreshold_ = iConfig.getUntrackedParameter<double> ( "metThreshold", 0.0 );
  mtwThreshold_ = iConfig.getUntrackedParameter<double> ( "mtwThreshold", 50.0 );
  bTagEfficiency_ = iConfig.getUntrackedParameter<double> ( "bTagEfficiency", 0.4 );

  useFullSelection_  =  iConfig.getUntrackedParameter< bool >("useFullSelection", false);
  matchWithLHE_  =  iConfig.getUntrackedParameter< bool >("matchWithLHE", false);
  
  //Get already identified status 3 leptons, quarks(including b-s), neutrinos and tops
  MCQuarksEta_ =  iConfig.getParameter< edm::InputTag >("MCQuarksEta");
  MCQuarksPt_ =  iConfig.getParameter< edm::InputTag >("MCQuarksPt");
  MCQuarksPhi_ =  iConfig.getParameter< edm::InputTag >("MCQuarksPhi");
  MCQuarksEnergy_ =  iConfig.getParameter< edm::InputTag >("MCQuarksEnergy");
  MCQuarksPdgId_ =  iConfig.getParameter< edm::InputTag >("MCQuarksPdgId");
  //  MCQuarksMotherId_ =  iConfig.getParameter< edm::InputTag >("MCQuarksMotherId");

  MCLeptonsEta_ =  iConfig.getParameter< edm::InputTag >("MCLeptonsEta");
  MCLeptonsPt_ =  iConfig.getParameter< edm::InputTag >("MCLeptonsPt");
  MCLeptonsPhi_ =  iConfig.getParameter< edm::InputTag >("MCLeptonsPhi");
  MCLeptonsEnergy_ =  iConfig.getParameter< edm::InputTag >("MCLeptonsEnergy");
  MCLeptonsPdgId_ =  iConfig.getParameter< edm::InputTag >("MCLeptonsPdgId");
  //  MCLeptonsMotherId_ =  iConfig.getParameter< edm::InputTag >("MCLeptonsMotherId");
  
  MCNeutrinosEta_ =  iConfig.getParameter< edm::InputTag >("MCNeutrinosEta");
  MCNeutrinosPt_ =  iConfig.getParameter< edm::InputTag >("MCNeutrinosPt");
  MCNeutrinosPhi_ =  iConfig.getParameter< edm::InputTag >("MCNeutrinosPhi");
  MCNeutrinosEnergy_ =  iConfig.getParameter< edm::InputTag >("MCNeutrinosEnergy");
  MCNeutrinosPdgId_ =  iConfig.getParameter< edm::InputTag >("MCNeutrinosPdgId");
  //  MCNeutrinosMotherId_ =  iConfig.getParameter< edm::InputTag >("MCNeutrinosMotherId");
  
  
  MCTopsEta_ =  iConfig.getParameter< edm::InputTag >("MCTopsEta");
  MCTopsPt_ =  iConfig.getParameter< edm::InputTag >("MCTopsPt");
  MCTopsPhi_ =  iConfig.getParameter< edm::InputTag >("MCTopsPhi");
  MCTopsEnergy_ =  iConfig.getParameter< edm::InputTag >("MCTopsEnergy");
  MCTopsPdgId_ =  iConfig.getParameter< edm::InputTag >("MCTopsPdgId");
  //  MCTopsMotherId_ =  iConfig.getParameter< edm::InputTag >("MCTopsMotherId");


  //LHE counterparts

  //Get already identified status 3 leptons, quarks(including b-s), neutrinos and tops
  LHEMCQuarksEta_ =  iConfig.getParameter< edm::InputTag >("LHEMCQuarksEta");
  LHEMCQuarksPt_ =  iConfig.getParameter< edm::InputTag >("LHEMCQuarksPt");
  LHEMCQuarksPhi_ =  iConfig.getParameter< edm::InputTag >("LHEMCQuarksPhi");
  LHEMCQuarksEnergy_ =  iConfig.getParameter< edm::InputTag >("LHEMCQuarksEnergy");
  LHEMCQuarksPdgId_ =  iConfig.getParameter< edm::InputTag >("LHEMCQuarksPdgId");
  //  LHEMCQuarksMotherId_ =  iConfig.getParameter< edm::InputTag >("LHEMCQuarksMotherId");

  LHEMCLeptonsEta_ =  iConfig.getParameter< edm::InputTag >("LHEMCLeptonsEta");
  LHEMCLeptonsPt_ =  iConfig.getParameter< edm::InputTag >("LHEMCLeptonsPt");
  LHEMCLeptonsPhi_ =  iConfig.getParameter< edm::InputTag >("LHEMCLeptonsPhi");
  LHEMCLeptonsEnergy_ =  iConfig.getParameter< edm::InputTag >("LHEMCLeptonsEnergy");
  LHEMCLeptonsPdgId_ =  iConfig.getParameter< edm::InputTag >("LHEMCLeptonsPdgId");
  //  LHEMCLeptonsMotherId_ =  iConfig.getParameter< edm::InputTag >("LHEMCLeptonsMotherId");
  
  LHEMCNeutrinosEta_ =  iConfig.getParameter< edm::InputTag >("LHEMCNeutrinosEta");
  LHEMCNeutrinosPt_ =  iConfig.getParameter< edm::InputTag >("LHEMCNeutrinosPt");
  LHEMCNeutrinosPhi_ =  iConfig.getParameter< edm::InputTag >("LHEMCNeutrinosPhi");
  LHEMCNeutrinosEnergy_ =  iConfig.getParameter< edm::InputTag >("LHEMCNeutrinosEnergy");
  LHEMCNeutrinosPdgId_ =  iConfig.getParameter< edm::InputTag >("LHEMCNeutrinosPdgId");
  //  LHEMCNeutrinosMotherId_ =  iConfig.getParameter< edm::InputTag >("LHEMCNeutrinosMotherId");
  
  
  LHEMCTopsEta_ =  iConfig.getParameter< edm::InputTag >("LHEMCTopsEta");
  LHEMCTopsPt_ =  iConfig.getParameter< edm::InputTag >("LHEMCTopsPt");
  LHEMCTopsPhi_ =  iConfig.getParameter< edm::InputTag >("LHEMCTopsPhi");
  LHEMCTopsEnergy_ =  iConfig.getParameter< edm::InputTag >("LHEMCTopsEnergy");
  LHEMCTopsPdgId_ =  iConfig.getParameter< edm::InputTag >("LHEMCTopsPdgId");
  //  MCTopsMotherId_ =  iConfig.getParameter< edm::InputTag >("MCTopsMotherId");
  
  produces<std::vector< float> >("PseudoTopsPt").setBranchAlias("PseudoTopsPt");
  produces<std::vector< float> >("PseudoTopsEta").setBranchAlias("PseudoTopsEta");
  produces<std::vector< float> >("PseudoTopsPhi").setBranchAlias("PseudoTopsPhi");
  produces<std::vector< float> >("PseudoTopsEnergy").setBranchAlias("PseudoTopsEnergy");
  produces<std::vector< float> >("PseudoTopsMass").setBranchAlias("PseudoTopsMass");

  produces<std::vector< float> >("PseudoBJetsPt").setBranchAlias("PseudoBJetsPt");
  produces<std::vector< float> >("PseudoBJetsEta").setBranchAlias("PseudoBJetsEta");
  produces<std::vector< float> >("PseudoBJetsPhi").setBranchAlias("PseudoBJetsPhi");
  produces<std::vector< float> >("PseudoBJetsEnergy").setBranchAlias("PseudoBJetsEnergy");
  produces<std::vector< float> >("PseudoBJetsFlavour").setBranchAlias("PseudoBJetsFlavour");


  produces<std::vector< float> >("PseudoFJetsPt").setBranchAlias("PseudoFJetsPt");
  produces<std::vector< float> >("PseudoFJetsEta").setBranchAlias("PseudoFJetsEta");
  produces<std::vector< float> >("PseudoFJetsPhi").setBranchAlias("PseudoFJetsPhi");
  produces<std::vector< float> >("PseudoFJetsEnergy").setBranchAlias("PseudoFJetsEnergy");
  produces<std::vector< float> >("PseudoFJetsFlavour").setBranchAlias("PseudoFJetsFlavour");

  produces<std::vector< float> >("PseudoJetsPt").setBranchAlias("PseudoJetsPt");
  produces<std::vector< float> >("PseudoJetsEta").setBranchAlias("PseudoJetsEta");
  produces<std::vector< float> >("PseudoJetsPhi").setBranchAlias("PseudoJetsPhi");
  produces<std::vector< float> >("PseudoJetsEnergy").setBranchAlias("PseudoJetsEnergy");
  produces<std::vector< float> >("PseudoJetsFlavour").setBranchAlias("PseudoJetsFlavour");


  produces<std::vector< float> >("PseudoLeptonsPt").setBranchAlias("PseudoLeptonsPt");
  produces<std::vector< float> >("PseudoLeptonsEta").setBranchAlias("PseudoLeptonsEta");
  produces<std::vector< float> >("PseudoLeptonsPhi").setBranchAlias("PseudoLeptonsPhi");
  produces<std::vector< float> >("PseudoLeptonsEnergy").setBranchAlias("PseudoLeptonsEnergy");

  //  produces<std::vector< float> >("LightJetEta").setBranchAlias("LightJetEta");
  produces<std::vector< float> >("PseudoMTW").setBranchAlias("PseudoMTW");
  produces<std::vector< float> >("PseudoMET").setBranchAlias("PseudoMET");
  produces<std::vector< float> >("CosThetaStarLJ").setBranchAlias("CosThetaStarLJ");
  seed =1; 
}

void SingleTopPseudoAnalysisProducer::produce(edm::Event & iEvent, const edm::EventSetup & iEventSetup){
  seed = seed+1;
  //edm::Handle<edm::View<reco::genParticle> > looseJets;
  //iEvent.getByLabel(looseJetsSrc_, looseJets);

#if DEBUG
  std::cout << "producer 1" << std::endl;
#endif

  edm::Handle<std::vector<reco::GenJet> > genJets;
  iEvent.getByLabel(genJetsSrc_, genJets);
  std::vector<int> associatedId;


 if(!matchWithLHE_){
  iEvent.getByLabel(MCQuarksEta_, MCQuarksEta); iEvent.getByLabel(MCQuarksPt_, MCQuarksPt); iEvent.getByLabel(MCQuarksPhi_, MCQuarksPhi); iEvent.getByLabel(MCQuarksEnergy_, MCQuarksEnergy); iEvent.getByLabel(MCQuarksPdgId_, MCQuarksPdgId);
  iEvent.getByLabel(MCLeptonsEta_, MCLeptonsEta); iEvent.getByLabel(MCLeptonsPt_, MCLeptonsPt); iEvent.getByLabel(MCLeptonsPhi_, MCLeptonsPhi); iEvent.getByLabel(MCLeptonsEnergy_, MCLeptonsEnergy); 
  //iEvent.getByLabel(MCQuarksPdgId_, MCQuarksPdgId);

  iEvent.getByLabel(MCNeutrinosEta_, MCNeutrinosEta); iEvent.getByLabel(MCNeutrinosPt_, MCNeutrinosPt); iEvent.getByLabel(MCNeutrinosPhi_, MCNeutrinosPhi); iEvent.getByLabel(MCNeutrinosEnergy_, MCNeutrinosEnergy); 
  //iEvent.getByLabel(MCQuarksPdgId_, MCQuarksPdgId);
  
  iEvent.getByLabel(MCTopsEta_, MCTopsEta); iEvent.getByLabel(MCTopsPt_, MCTopsPt); iEvent.getByLabel(MCTopsPhi_, MCTopsPhi); iEvent.getByLabel(MCTopsEnergy_, MCTopsEnergy); 
  //iEvent.getByLabel(MCQuarksPdgId_, MCQuarksPdgId);
 }
 
 if(matchWithLHE_){
   iEvent.getByLabel(LHEMCQuarksEta_, LHEMCQuarksEta); iEvent.getByLabel(LHEMCQuarksPt_, LHEMCQuarksPt); iEvent.getByLabel(LHEMCQuarksPhi_, LHEMCQuarksPhi); iEvent.getByLabel(LHEMCQuarksEnergy_, LHEMCQuarksEnergy); iEvent.getByLabel(LHEMCQuarksPdgId_, LHEMCQuarksPdgId);

  iEvent.getByLabel(LHEMCLeptonsEta_, LHEMCLeptonsEta); iEvent.getByLabel(LHEMCLeptonsPt_, LHEMCLeptonsPt); iEvent.getByLabel(LHEMCLeptonsPhi_, LHEMCLeptonsPhi); iEvent.getByLabel(LHEMCLeptonsEnergy_, LHEMCLeptonsEnergy); 
  //iEvent.getByLabel(LHEMCQuarksPdgId_, LHEMCQuarksPdgId);

  iEvent.getByLabel(LHEMCNeutrinosEta_, LHEMCNeutrinosEta); iEvent.getByLabel(LHEMCNeutrinosPt_, LHEMCNeutrinosPt); iEvent.getByLabel(LHEMCNeutrinosPhi_, LHEMCNeutrinosPhi); iEvent.getByLabel(LHEMCNeutrinosEnergy_, LHEMCNeutrinosEnergy); 
  //iEvent.getByLabel(LHEMCQuarksPdgId_, LHEMCQuarksPdgId);
  
  iEvent.getByLabel(LHEMCTopsEta_, LHEMCTopsEta); iEvent.getByLabel(LHEMCTopsPt_, LHEMCTopsPt); iEvent.getByLabel(LHEMCTopsPhi_, LHEMCTopsPhi); iEvent.getByLabel(LHEMCTopsEnergy_, LHEMCTopsEnergy); 
  //iEvent.getByLabel(MCQuarksPdgId_, MCQuarksPdgId);
 }



  std::vector< math::PtEtaPhiELorentzVector> tops;
  std::vector< math::PtEtaPhiELorentzVector> quarks;
  std::vector< math::PtEtaPhiELorentzVector> leptons;
  std::vector< math::PtEtaPhiELorentzVector> neutrinos;

  math::PtEtaPhiELorentzVector pseudomet;
  std::vector< float > pseudomtw, pseudojetsflavour, pseudofjetsflavour, pseudobjetsflavour;
  std::vector< math::PtEtaPhiELorentzVector> pseudojets;
  std::vector< math::PtEtaPhiELorentzVector> pseudobjets;
  std::vector< math::PtEtaPhiELorentzVector> pseudofjets;
  std::vector< math::PtEtaPhiELorentzVector> pseudotops;

  std::auto_ptr< std::vector< float > > CosThetaStarLJ ( new std::vector<float> );

  if(!matchWithLHE_){
    for (size_t i =0; i < MCQuarksPt->size();++i ){
      math::PtEtaPhiELorentzVector quark = math::PtEtaPhiELorentzVector(
									(MCQuarksPt->at(i)),
									(MCQuarksEta->at(i)),
									(MCQuarksPhi->at(i)),
									(MCQuarksEnergy->at(i))
									);
      quarks.push_back(quark);
    }		    

   
    
    for (size_t i =0; i < MCNeutrinosPt->size();++i ){
      math::PtEtaPhiELorentzVector neutrino = math::PtEtaPhiELorentzVector(
									   (MCNeutrinosPt->at(i)),
									   (MCNeutrinosEta->at(i)),
									   (MCNeutrinosPhi->at(i)),
									   (MCNeutrinosEnergy->at(i))
									   );
      
      pseudomet = pseudomet + neutrino;
      neutrinos.push_back(neutrino);
    }
    
    
    for (size_t i =0; i < MCTopsPt->size();++i ){
      math::PtEtaPhiELorentzVector top = math::PtEtaPhiELorentzVector(
								      (MCTopsPt->at(i)),
								      (MCTopsEta->at(i)),
								      (MCTopsPhi->at(i)),
								      (MCTopsEnergy->at(i))
								      );
      tops.push_back(top);
    } 
  }
  else{
    for (size_t i =0; i < LHEMCQuarksPt->size();++i ){
      math::PtEtaPhiELorentzVector quark = math::PtEtaPhiELorentzVector(
									(LHEMCQuarksPt->at(i)),
									(LHEMCQuarksEta->at(i)),
									(LHEMCQuarksPhi->at(i)),
									(LHEMCQuarksEnergy->at(i))
									);
      quarks.push_back(quark);
    }		    
    
    
    for (size_t i =0; i < LHEMCNeutrinosPt->size();++i ){
      math::PtEtaPhiELorentzVector neutrino = math::PtEtaPhiELorentzVector(
									   (LHEMCNeutrinosPt->at(i)),
									   (LHEMCNeutrinosEta->at(i)),
									   (LHEMCNeutrinosPhi->at(i)),
									   (LHEMCNeutrinosEnergy->at(i))
									   );
      
      pseudomet = pseudomet + neutrino;
      neutrinos.push_back(neutrino);
    }		    
    
    
    for (size_t i =0; i < LHEMCTopsPt->size();++i ){
      math::PtEtaPhiELorentzVector top = math::PtEtaPhiELorentzVector(
								      (LHEMCTopsPt->at(i)),
								      (LHEMCTopsEta->at(i)),
								      (LHEMCTopsPhi->at(i)),
								      (LHEMCTopsEnergy->at(i))
								      );
      tops.push_back(top);
      
    }
  }
  //  cout << " bef genjets "<<endl;
  
  for (size_t i=0; i < genJets->size();++i){
    float corrFactor = 1.0;//0.5;
    float corrPt = genJets->at(i).p4().pt()*corrFactor;
    if(corrPt<jetThreshold_)continue;
    
    math::PtEtaPhiELorentzVector jet = math::PtEtaPhiELorentzVector(
								      (genJets->at(i).pt()*corrFactor),
								      (genJets->at(i).p4().eta()),
								      (genJets->at(i).p4().phi()),
								      (genJets->at(i).p4().energy()*corrFactor)
								      );
      pseudojets.push_back(jet);  
  }
  
  if(!matchWithLHE_){
    for (size_t i =0; i < MCLeptonsPt->size();++i ){
      math::PtEtaPhiELorentzVector lepton = math::PtEtaPhiELorentzVector(
									 (MCLeptonsPt->at(i)),
									 (MCLeptonsEta->at(i)),
									 (MCLeptonsPhi->at(i)),
									 (MCLeptonsEnergy->at(i))
									 );
    
      if(lepton.pt()<leptonThreshold_)continue;
      bool passesdrj=true; 
      for(size_t j=0; ((j < pseudojets.size()) && passesdrj);++j){
	double deltar = deltaR(pseudojets.at(j),lepton);
	if (deltar<0.3){
	  passesdrj=false;
	}
	cout << " deltar lepton " << i <<" jet "<< j << " is "<< deltar;
	
      }
      //    if(!passesdrj)continue; 
      double metPx = pseudomet.px();
      double metPy = pseudomet.py();
      double mtw = sqrt((lepton.pt() + pseudomet.pt()) * (lepton.pt() + pseudomet.pt()) - (lepton.px() + metPx) * (lepton.px() + metPx) - (lepton.py() + metPy) * (lepton.py() + metPy));
      pseudomtw.push_back(mtw);
      leptons.push_back(lepton);    
      
    }
  }
  else{
    for (size_t i =0; i < LHEMCLeptonsPt->size();++i ){
      math::PtEtaPhiELorentzVector lepton = math::PtEtaPhiELorentzVector(
									 (LHEMCLeptonsPt->at(i)),
									 (LHEMCLeptonsEta->at(i)),
									 (LHEMCLeptonsPhi->at(i)),
									 (LHEMCLeptonsEnergy->at(i))
									 );
      if(lepton.pt()<leptonThreshold_)continue;
      bool passesdrj=true; 
      for(size_t j=0; ((j < pseudojets.size()) && passesdrj);++j){
	double deltar = deltaR(pseudojets.at(j),lepton);
	if (deltar<0.3){
	  passesdrj=false;
	}
	cout << " deltar lepton " << i <<" jet "<< j << " is "<< deltar;
	
      }
      double metPx = pseudomet.px();
      double metPy = pseudomet.py();
      double mtw = sqrt((lepton.pt() + pseudomet.pt()) * (lepton.pt() + pseudomet.pt()) - (lepton.px() + metPx) * (lepton.px() + metPx) - (lepton.py() + metPy) * (lepton.py() + metPy));
      pseudomtw.push_back(mtw);
      //    if(!passesdrj)continue; 
      leptons.push_back(lepton);
    }
  }

  //  cout << " lep size "<<leptons.size()<< " met px "<< pseudomet.pt()<<  endl; 

    
  for (size_t i=0; i < pseudojets.size();++i){
    int pos = -1;
    double minDeltaR= genJetsDeltarMatching_;
    int id =0;
    cout << " assjet "<< i << " pt "<< pseudojets.at(i).pt()<<endl;
    
    //    int qid =0;
    for (size_t j = 0; j < quarks.size();++j){
      double deltar=deltaR(pseudojets.at(i),quarks.at(j));
      if(deltar< minDeltaR ){
	pos = j;
	minDeltaR = deltar;
      }
      //      cout << " is there LHEMC "<< LHEMCQuarksPdgId<< endl;
      //      qid = 0;
      //      if(!matchWithLHE_){ qid = MCQuarksPdgId->at(j);}
      //     else{ qid = LHEMCQuarksPdgId->at(j);}
      //cout << " quark " <<  qid
      //	   << " q eta " << quarks.at(j).eta()<< " phi "<< quarks.at(j).phi() 
      //	   << " j eta " << pseudojets.at(i).eta()<< " phi "<< pseudojets.at(i).phi()
      //	   << " deltar " << deltar<< " mindeltar " <<  minDeltaR <<" pos "<< pos << endl;
    }

    if( pos >=0){
      if(!matchWithLHE_){ id = MCQuarksPdgId->at(pos);}
      else{ id = LHEMCQuarksPdgId->at(pos);
	//cout << " id to associate "<< id <<  " pt "<< LHEMCQuarksPt->at(pos)<<endl; 
      }
    }
    
    //    int id =0;
    //    if( pos > 0) id = qid;
    pseudojetsflavour.push_back(id);
    associatedId.push_back(id);
  }
  
  cout<<" #assjets " << pseudojets.size()<<endl;

  cout << " bef bjet "<<endl;
  
  TRandom3 pseudoBTagging(seed);
  
  for (size_t i=0; i < pseudojets.size();++i){
    cout << " jet # " << i<< " associated id "<< associatedId.at(i)<<endl;
    if(abs(associatedId.at(i))==5) {
      double p = pseudoBTagging.Uniform();
      cout <<" bTag thr: " << bTagEfficiency_<< " p: "<<p<<endl;
      if(p<bTagEfficiency_){pseudobjets.push_back(pseudojets.at(i));
	pseudobjetsflavour.push_back(abs(associatedId.at(i)));
      }
    }
    else {
      pseudofjets.push_back(pseudojets.at(i));
      pseudofjetsflavour.push_back(abs(associatedId.at(i)));
    }
    
  }
  
  cout << "#bjets " << pseudobjets.size()<<endl;
  bool passescuts = true;

  cout << " cuts njets " <<  pseudojets.size() << " bjsie "<<pseudobjets.size() << " leptnos "<<  leptons.size() <<endl;   
  if(useFullSelection_){
    passescuts = (pseudojets.size()==2 && leptons.size()==1 );
    passescuts = passescuts && (pseudomet.pt()> metThreshold_);
    double mtw = 0;
    if(passescuts){
      double metPx = pseudomet.px();
      double metPy = pseudomet.py();
      mtw = sqrt((leptons.at(0).pt() + pseudomet.pt()) * (leptons.at(0).pt() + pseudomet.pt()) - (leptons.at(0).px() + metPx) * (leptons.at(0).px() + metPx) - (leptons.at(0).py() + metPy) * (leptons.at(0).py() + metPy));
    }
    passescuts = passescuts && (mtw > mtwThreshold_);
    
    //    passescuts = (pseudojets.size()==2 && pseudobjets.size()==1 && leptons.size()==1 && pseudomet.pt()>45);
  }

  double metPx = pseudomet.px();
  double metPy = pseudomet.py();
  
  cout << " metpx,py "<< metPx <<"," <<metPy<<endl;
  
 /*  if(passescuts)for (size_t i=0; i < pseudobjets.size();++i){
    for (size_t j = 0; j < leptons.size();++j){
      math::PtEtaPhiELorentzVector pseudotop = top4Momentum(leptons.at(j), pseudobjets.at(i), metPx, metPy);
      for (size_t k = 0; k < pseudofjets.size();++k){
	float fCosThetaLJ = cosThetaLJ(leptons.at(j), pseudofjets.at(k), pseudotop);
	float cosBLTree =  cosTheta_eta_bl(leptons.at(j), pseudofjets.at(k), pseudotop);
	CosThetaStarLJ->push_back(fCosThetaLJ);
      }
      pseudotops.push_back(pseudotop);
      //      costhetabl.push_back(cosBLTree);
    }
    }

  if(passescuts)for (size_t i=0; i < pseudobjets.size();++i){
    for (size_t j = 0; j < leptons.size();++j){
      if (tops.size()==1) {    math::PtEtaPhiELorentzVector pseudotop = tops.at(0);
	for (size_t k = 0; k < pseudofjets.size();++k){
	  float fCosThetaLJ = cosThetaLJ(leptons.at(j), pseudofjets.at(k), pseudotop);
	  CosThetaStarLJ->push_back(fCosThetaLJ);
	}
      }
      //      costhetabl.push_back(cosBLTree);
    }
 */

  cout << " passes cuts? "<< passescuts<<endl; 
  if(passescuts)  for (size_t i=0; i < pseudobjets.size();++i){
    for (size_t j = 0; j < leptons.size();++j){
      if (tops.size()==1) {    
	math::PtEtaPhiELorentzVector pseudotop = top4Momentum(leptons.at(j), pseudobjets.at(i), metPx, metPy);
	//math::PtEtaPhiELorentzVector pseudotop = tops.at(0);
	pseudotops.push_back(pseudotop);
	int qid = 0;
	for (size_t k = 0; k < quarks.size();++k){
	  if(!matchWithLHE_) qid = MCQuarksPdgId->at(k);
	  else qid = LHEMCQuarksPdgId->at(k);
	  if(abs(qid)==1){
	    float fCosThetaLJ = cosThetaLJ(leptons.at(j), quarks.at(k), pseudotop);
	    CosThetaStarLJ->push_back(fCosThetaLJ);
	  }
	}
      }
      //costhetabl.push_back(cosBLTree);
    }
  

  }



#if DEBUG
  std::cout << "producer 2" << std::endl;
#endif

  std::auto_ptr< std::vector< float > > PseudoTopsPt ( new std::vector<float> );
  std::auto_ptr< std::vector< float > > PseudoTopsEta ( new std::vector<float> );
  std::auto_ptr< std::vector< float > > PseudoTopsPhi ( new std::vector<float> );
  std::auto_ptr< std::vector< float > > PseudoTopsEnergy ( new std::vector<float> );
  std::auto_ptr< std::vector< float > > PseudoTopsMass ( new std::vector<float> );

  std::auto_ptr< std::vector< float > > PseudoFJetsPt ( new std::vector<float> );
  std::auto_ptr< std::vector< float > > PseudoFJetsEta ( new std::vector<float> );
  std::auto_ptr< std::vector< float > > PseudoFJetsPhi ( new std::vector<float> );
  std::auto_ptr< std::vector< float > > PseudoFJetsEnergy ( new std::vector<float> );
  std::auto_ptr< std::vector< float > > PseudoFJetsFlavour ( new std::vector<float> );

  std::auto_ptr< std::vector< float > > PseudoJetsPt ( new std::vector<float> );
  std::auto_ptr< std::vector< float > > PseudoJetsEta ( new std::vector<float> );
  std::auto_ptr< std::vector< float > > PseudoJetsPhi ( new std::vector<float> );
  std::auto_ptr< std::vector< float > > PseudoJetsEnergy ( new std::vector<float> );
  std::auto_ptr< std::vector< float > > PseudoJetsFlavour ( new std::vector<float> );

  std::auto_ptr< std::vector< float > > PseudoBJetsPt ( new std::vector<float> );
  std::auto_ptr< std::vector< float > > PseudoBJetsEta ( new std::vector<float> );
  std::auto_ptr< std::vector< float > > PseudoBJetsPhi ( new std::vector<float> );
  std::auto_ptr< std::vector< float > > PseudoBJetsEnergy ( new std::vector<float> );
  std::auto_ptr< std::vector< float > > PseudoBJetsFlavour ( new std::vector<float> );


  std::auto_ptr< std::vector< float > > PseudoLeptonsPt ( new std::vector<float> );
  std::auto_ptr< std::vector< float > > PseudoLeptonsEta ( new std::vector<float> );
  std::auto_ptr< std::vector< float > > PseudoLeptonsPhi ( new std::vector<float> );
  std::auto_ptr< std::vector< float > > PseudoLeptonsEnergy ( new std::vector<float> );

  std::auto_ptr< std::vector< float > > PseudoMET ( new std::vector<float> );  
  std::auto_ptr< std::vector< float > > PseudoMTW ( new std::vector<float> );  
  for (size_t i = 0; i < pseudotops.size();++i){
    PseudoTopsPt->push_back(pseudotops.at(i).pt());
    PseudoTopsEta->push_back(pseudotops.at(i).eta());
    PseudoTopsPhi->push_back(pseudotops.at(i).phi());
    PseudoTopsEnergy->push_back(pseudotops.at(i).energy());
    PseudoTopsMass->push_back(pseudotops.at(i).mass());
  }

  for (size_t i = 0; i < pseudofjets.size();++i){
    PseudoFJetsPt->push_back(pseudofjets.at(i).pt());
    PseudoFJetsEta->push_back(pseudofjets.at(i).eta());
    PseudoFJetsPhi->push_back(pseudofjets.at(i).phi());
    PseudoFJetsEnergy->push_back(pseudofjets.at(i).energy());
    PseudoFJetsFlavour->push_back(pseudofjetsflavour.at(i));
  }

  for (size_t i = 0; i < pseudojets.size();++i){
    PseudoJetsPt->push_back(pseudojets.at(i).pt());
    PseudoJetsEta->push_back(pseudojets.at(i).eta());
    PseudoJetsPhi->push_back(pseudojets.at(i).phi());
    PseudoJetsEnergy->push_back(pseudojets.at(i).energy());
    PseudoJetsFlavour->push_back(pseudojetsflavour.at(i));
  }

  for (size_t i = 0; i < leptons.size();++i){
    PseudoLeptonsPt->push_back(leptons.at(i).pt());
    PseudoLeptonsEta->push_back(leptons.at(i).eta());
    PseudoLeptonsPhi->push_back(leptons.at(i).phi());
    PseudoLeptonsEnergy->push_back(leptons.at(i).energy());
    PseudoMTW->push_back(pseudomtw.at(i));
  }

for (size_t i = 0; i < pseudobjets.size();++i){
    PseudoBJetsPt->push_back(pseudobjets.at(i).pt());
    PseudoBJetsEta->push_back(pseudobjets.at(i).eta());
    PseudoBJetsPhi->push_back(pseudobjets.at(i).phi());
    PseudoBJetsEnergy->push_back(pseudobjets.at(i).energy());
    PseudoBJetsFlavour->push_back(pseudobjetsflavour.at(i));
 }

 PseudoMET->push_back(pseudomet.pt());
  //  std::auto_ptr< std::vector< float > > LightJetEta ( new std::vector<float> );
  
 if(passescuts){
  
  //  iEvent.put(MCstops,"MCstops");

  iEvent.put(PseudoTopsPt,"PseudoTopsPt");
  iEvent.put(PseudoTopsEta,"PseudoTopsEta");
  iEvent.put(PseudoTopsPhi,"PseudoTopsPhi");
  iEvent.put(PseudoTopsEnergy,"PseudoTopsEnergy");
  iEvent.put(PseudoTopsMass,"PseudoTopsMass");

  iEvent.put(PseudoBJetsPt,"PseudoBJetsPt");
  iEvent.put(PseudoBJetsEta,"PseudoBJetsEta");
  iEvent.put(PseudoBJetsPhi,"PseudoBJetsPhi");
  iEvent.put(PseudoBJetsEnergy,"PseudoBJetsEnergy");
  iEvent.put(PseudoBJetsFlavour,"PseudoBJetsFlavour");
  
  iEvent.put(PseudoFJetsPt,"PseudoFJetsPt");
  iEvent.put(PseudoFJetsEta,"PseudoFJetsEta");
  iEvent.put(PseudoFJetsPhi,"PseudoFJetsPhi");
  iEvent.put(PseudoFJetsEnergy,"PseudoFJetsEnergy");
  iEvent.put(PseudoFJetsFlavour,"PseudoFJetsFlavour");

  iEvent.put(PseudoJetsPt,"PseudoJetsPt");
  iEvent.put(PseudoJetsEta,"PseudoJetsEta");
  iEvent.put(PseudoJetsPhi,"PseudoJetsPhi");
  iEvent.put(PseudoJetsEnergy,"PseudoJetsEnergy");
  iEvent.put(PseudoJetsFlavour,"PseudoJetsFlavour");


  iEvent.put(PseudoLeptonsPt,"PseudoLeptonsPt");
  iEvent.put(PseudoLeptonsEta,"PseudoLeptonsEta");
  iEvent.put(PseudoLeptonsPhi,"PseudoLeptonsPhi");
  iEvent.put(PseudoLeptonsEnergy,"PseudoLeptonsEnergy");

  iEvent.put(CosThetaStarLJ,"CosThetaStarLJ");
  iEvent.put(PseudoMET,"PseudoMET");
  iEvent.put(PseudoMTW,"PseudoMTW");
 }
  //  iEvent.put(LightJetEta,"LightJetEta");

  //  produces<std::vector< float> >("LightJetEta").setBranchAlias("LightJetEta");
 //  produces<std::vector< float > >("CosThetaStarLJ").setBranchAlias("CosThetaStarLJ");

}


//Kin functions, cloned from TreesDumper:

//CosThetalj given top quark, lepton and light jet
float SingleTopPseudoAnalysisProducer::cosThetaLJ(math::PtEtaPhiELorentzVector lepton, math::PtEtaPhiELorentzVector jet, math::PtEtaPhiELorentzVector top)
{

    math::PtEtaPhiELorentzVector boostedLepton = ROOT::Math::VectorUtil::boost(lepton, top.BoostToCM());
    math::PtEtaPhiELorentzVector boostedJet = ROOT::Math::VectorUtil::boost(jet, top.BoostToCM());

    return  ROOT::Math::VectorUtil::CosTheta(boostedJet.Vect(), boostedLepton.Vect());

}
//CosTheta-lepton-beam-line, implementation by Joosep Pata
float SingleTopPseudoAnalysisProducer::cosTheta_eta_bl(math::PtEtaPhiELorentzVector lepton, math::PtEtaPhiELorentzVector jet, math::PtEtaPhiELorentzVector top)
{

    double eta = jet.eta();
    double z;
    if (eta > 0)
    {
        z = 1.0;
    }
    else
    {
        z = -1.0;
    }
    math::XYZTLorentzVector beamLine = math::XYZTLorentzVector(0.0, 0.0, z, 1.0);
    math::PtEtaPhiELorentzVector boostedLepton = ROOT::Math::VectorUtil::boost(lepton, top.BoostToCM());
    math::XYZTLorentzVector boostedBeamLine = ROOT::Math::VectorUtil::boost(beamLine, top.BoostToCM());

    return ROOT::Math::VectorUtil::CosTheta(boostedBeamLine.Vect(), boostedLepton.Vect());

}

//top quark 4-momentum given lepton, met and b-jet
math::PtEtaPhiELorentzVector SingleTopPseudoAnalysisProducer::top4Momentum(math::PtEtaPhiELorentzVector lepton, math::PtEtaPhiELorentzVector jet, float metPx, float metPy)
{
    return top4Momentum(lepton.px(), lepton.py(), lepton.pz(), lepton.energy(), jet.px(), jet.py(), jet.pz(), jet.energy(), metPx, metPy);
}

//top quark 4-momentum original function given the necessary parameters
math::PtEtaPhiELorentzVector SingleTopPseudoAnalysisProducer::top4Momentum(float leptonPx, float leptonPy, float leptonPz, float leptonE, float jetPx, float jetPy, float jetPz, float jetE, float metPx, float metPy)
{
    float lepton_Pt = sqrt( (leptonPx * leptonPx) +  (leptonPy * leptonPy) );

    math::XYZTLorentzVector neutrino = NuMomentum(leptonPx, leptonPy, leptonPz, lepton_Pt, leptonE, metPx, metPy); //.at(0);;

    math::XYZTLorentzVector lep(leptonPx, leptonPy, leptonPz, leptonE);
    math::XYZTLorentzVector jet(jetPx, jetPy, jetPz, jetE);

    math::XYZTLorentzVector top = lep + jet + neutrino;
    return math::PtEtaPhiELorentzVector(top.pt(), top.eta(), top.phi(), top.E());
}

//top neutrino 4-momentum function given the parameters
//In brief:
//Works for top->1l+1neutrino+1bjet
//Assuming all met comes from neutrino
/////What it does:
//w boson mass put to pdg value
//obtained neutrino pz from kinematics
//We get a second order equation
/////In case of two positive Delta solutions:
//we choose solution with minimum |pz|
/////In case of two negative Delta solutions:
//in such case: mtw > mw
//To sove this: put mtw = mw
//Solve the equations
//In this way we must
//drop the constraints px_Nu = MET_x and py_Nu = MET_y
//Solve this by chosing the px_Nu and py_Nu that
//minimize the distance from the MET in the px-py plane
//Such minimization can be done analytically with derivatives
//and much patience. Here we exploit such analytical minimization
/////
//More detailed inline description: work in progress!
math::XYZTLorentzVector SingleTopPseudoAnalysisProducer::NuMomentum(float leptonPx, float leptonPy, float leptonPz, float leptonPt, float leptonE, float metPx, float metPy )
{

    double  mW = 80.399;

    math::XYZTLorentzVector result;

    //  double Wmt = sqrt(pow(Lepton.et()+MET.pt(),2) - pow(Lepton.px()+metPx,2) - pow(leptonPy+metPy,2) );

    double MisET2 = (metPx * metPx + metPy * metPy);
    double mu = (mW * mW) / 2 + metPx * leptonPx + metPy * leptonPy;
    double a  = (mu * leptonPz) / (leptonE * leptonE - leptonPz * leptonPz);
    double a2 = TMath::Power(a, 2);
    double b  = (TMath::Power(leptonE, 2.) * (MisET2) - TMath::Power(mu, 2.)) / (TMath::Power(leptonE, 2) - TMath::Power(leptonPz, 2));
    double pz1(0), pz2(0), pznu(0);
    //    int nNuSol(0);

    
    math::XYZTLorentzVector p4nu_rec;
    math::XYZTLorentzVector p4W_rec;
    math::XYZTLorentzVector p4b_rec;
    math::XYZTLorentzVector p4Top_rec;
    math::XYZTLorentzVector p4lep_rec;

    p4lep_rec.SetPxPyPzE(leptonPx, leptonPy, leptonPz, leptonE);

    math::XYZTLorentzVector p40_rec(0, 0, 0, 0);

    if (a2 - b > 0 )
    {
        //if(!usePositiveDeltaSolutions_)
        //  {
        //  result.push_back(p40_rec);
        //  return result;
        //  }
        double root = sqrt(a2 - b);
        pz1 = a + root;
        pz2 = a - root;
	//	nNuSol = 2;

        //    if(usePzPlusSolutions_)pznu = pz1;
        //    if(usePzMinusSolutions_)pznu = pz2;
        //if(usePzAbsValMinimumSolutions_){
        pznu = pz1;
        if (fabs(pz1) > fabs(pz2)) pznu = pz2;
        //}


        double Enu = sqrt(MisET2 + pznu * pznu);

        p4nu_rec.SetPxPyPzE(metPx, metPy, pznu, Enu);

        //    result =.push_back(p4nu_rec);
        result = p4nu_rec;

    }
    else
    {

        // if(!useNegativeDeltaSolutions_){
        //result.push_back(p40_rec);
        //  return result;
        //    }
        //    double xprime = sqrt(mW;


        double ptlep = leptonPt, pxlep = leptonPx, pylep = leptonPy, metpx = metPx, metpy = metPy;

        double EquationA = 1;
        double EquationB = -3 * pylep * mW / (ptlep);
        double EquationC = mW * mW * (2 * pylep * pylep) / (ptlep * ptlep) + mW * mW - 4 * pxlep * pxlep * pxlep * metpx / (ptlep * ptlep) - 4 * pxlep * pxlep * pylep * metpy / (ptlep * ptlep);
        double EquationD = 4 * pxlep * pxlep * mW * metpy / (ptlep) - pylep * mW * mW * mW / ptlep;

        std::vector<long double> solutions = EquationSolve<long double>((long double)EquationA, (long double)EquationB, (long double)EquationC, (long double)EquationD);

        std::vector<long double> solutions2 = EquationSolve<long double>((long double)EquationA, -(long double)EquationB, (long double)EquationC, -(long double)EquationD);


        double deltaMin = 14000 * 14000;
        double zeroValue = -mW * mW / (4 * pxlep);
        double minPx = 0;
        double minPy = 0;

        //    std::cout<<"a "<<EquationA << " b " << EquationB  <<" c "<< EquationC <<" d "<< EquationD << std::endl;

        //  if(usePxMinusSolutions_){
        for ( int i = 0; i < (int)solutions.size(); ++i)
        {
            if (solutions[i] < 0 ) continue;
            double p_x = (solutions[i] * solutions[i] - mW * mW) / (4 * pxlep);
            double p_y = ( mW * mW * pylep + 2 * pxlep * pylep * p_x - mW * ptlep * solutions[i]) / (2 * pxlep * pxlep);
            double Delta2 = (p_x - metpx) * (p_x - metpx) + (p_y - metpy) * (p_y - metpy);

            //      std:://cout<<"intermediate solution1 met x "<<metpx << " min px " << p_x  <<" met y "<<metpy <<" min py "<< p_y << std::endl;

            if (Delta2 < deltaMin && Delta2 > 0)
            {
                deltaMin = Delta2;
                minPx = p_x;
                minPy = p_y;
            }
            //     std:://cout<<"solution1 met x "<<metpx << " min px " << minPx  <<" met y "<<metpy <<" min py "<< minPy << std::endl;
        }

        //    }

        //if(usePxPlusSolutions_){
        for ( int i = 0; i < (int)solutions2.size(); ++i)
        {
            if (solutions2[i] < 0 ) continue;
            double p_x = (solutions2[i] * solutions2[i] - mW * mW) / (4 * pxlep);
            double p_y = ( mW * mW * pylep + 2 * pxlep * pylep * p_x + mW * ptlep * solutions2[i]) / (2 * pxlep * pxlep);
            double Delta2 = (p_x - metpx) * (p_x - metpx) + (p_y - metpy) * (p_y - metpy);
            //  std:://cout<<"intermediate solution2 met x "<<metpx << " min px " << minPx  <<" met y "<<metpy <<" min py "<< minPy << std::endl;
            if (Delta2 < deltaMin && Delta2 > 0)
            {
                deltaMin = Delta2;
                minPx = p_x;
                minPy = p_y;
            }
            //  std:://cout<<"solution2 met x "<<metpx << " min px " << minPx  <<" met y "<<metpy <<" min py "<< minPy << std::endl;
        }
        //}

        double pyZeroValue = ( mW * mW * pxlep + 2 * pxlep * pylep * zeroValue);
        double delta2ZeroValue = (zeroValue - metpx) * (zeroValue - metpx) + (pyZeroValue - metpy) * (pyZeroValue - metpy);

        if (deltaMin == 14000 * 14000)return result;
        //    else std:://cout << " test " << std::endl;

        if (delta2ZeroValue < deltaMin)
        {
            deltaMin = delta2ZeroValue;
            minPx = zeroValue;
            minPy = pyZeroValue;
        }

        //    std:://cout<<" MtW2 from min py and min px "<< sqrt((minPy*minPy+minPx*minPx))*ptlep*2 -2*(pxlep*minPx + pylep*minPy)  <<std::endl;
        ///    ////Y part

        double mu_Minimum = (mW * mW) / 2 + minPx * pxlep + minPy * pylep;
        double a_Minimum  = (mu_Minimum * leptonPz) / (leptonE * leptonE - leptonPz * leptonPz);
        pznu = a_Minimum;

        //if(!useMetForNegativeSolutions_){
        double Enu = sqrt(minPx * minPx + minPy * minPy + pznu * pznu);
        p4nu_rec.SetPxPyPzE(minPx, minPy, pznu , Enu);

        //    }
        //    else{
        //      pznu = a;
        //      double Enu = sqrt(metpx*metpx+metpy*metpy + pznu*pznu);
        //      p4nu_rec.SetPxPyPzE(metpx, metpy, pznu , Enu);
        //    }

        //      result.push_back(p4nu_rec);
        result = p4nu_rec;
    }
    return result;
}

SingleTopPseudoAnalysisProducer::~SingleTopPseudoAnalysisProducer(){;}

DEFINE_FWK_MODULE( SingleTopPseudoAnalysisProducer );

//  LocalWords:  MCtopsQuarkBar
