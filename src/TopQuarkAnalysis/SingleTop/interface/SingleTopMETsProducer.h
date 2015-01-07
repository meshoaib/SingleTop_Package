#ifndef _Top_Jet_Producer_h
#define _Top_Jet_Producer_h



/**
 *\Class TopProducer
 *
 * \Author A. Orso M. Iorio
 * 
 *
 *\version  $Id: SingleTopMETsProducer.h,v 1.1.2.1 2013/04/19 15:30:08 oiorio Exp $
 *
 *
*/



#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include <FWCore/Framework/interface/Run.h>

#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Framework/interface/TriggerNamesService.h"
#include "FWCore/ServiceRegistry/interface/Service.h" 


#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Common/interface/View.h"

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Photon.h"

#include "DataFormats/PatCandidates/interface/UserData.h"
#include "PhysicsTools/PatAlgos/interface/PATUserDataHelper.h"

#include "DataFormats/PatCandidates/interface/Lepton.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/CompositeCandidate.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/PATObject.h"

#include "DataFormats/Candidate/interface/NamedCompositeCandidate.h"
#include "DataFormats/Common/interface/View.h"


#include "CommonTools/Utils/interface/StringObjectFunction.h"
#include "CommonTools/Utils/interface/StringCutObjectSelector.h"

#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"

#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"


//#include "TLorentzVector.h"
#include "TopQuarkAnalysis/SingleTop/interface/EquationSolver.h"

#include "CMGTools/External/interface/PileupJetIdentifier.h"

//class JetFlavourIdentifier;


//namespace pat {

  class SingleTopMETsProducer : public edm::EDProducer {

    public:

      explicit SingleTopMETsProducer(const edm::ParameterSet & iConfig);
      ~SingleTopMETsProducer();
      virtual void produce(edm::Event & iEvent, const edm::EventSetup & iSetup);
    //       static void fillDescriptions(edm::ConfigurationDescriptions & descriptions);
    private:
  
    edm::InputTag   metsSrc_,  metsUnclUpSrc_, metsUnclDownSrc_, jetsSrc_,  electronsSrc_, muonsSrc_, photonsSrc_, tausSrc_, pfCandsNotInJetSrc_;
    
    edm::Handle<std::vector<pat::MET> > mets,metsUnclUp,metsUnclDown;
    edm::Handle<std::vector<pat::Jet> > jets;
    edm::Handle<std::vector<pat::Tau> > taus;
    edm::Handle<std::vector<pat::Photon> > photons;
    edm::Handle<std::vector<pat::Electron> > electrons;
    edm::Handle<std::vector<pat::Muon> > muons;

    edm::Handle<edm::View<reco::Candidate> > pfCandsNotInJet;
    
    JetCorrectionUncertainty *jecUnc;
    edm::FileInPath JESUncertaintiesPath_;
    
    bool isData_, addExternalUnclusteredMET_,isReco_,isPF_;
    
    double resolSF(double eta, std::string syst);
    
  };
//}


#endif
