#ifndef Single_Top_TChannel_MC_Producer_h
#define Single_Top_TChannel_MC_Producer_h

/* \Class SingleTopPseudoAnalysisProducer
 *
 * \Authors: A. Giammanco, A. Orso M. Iorio
 * 
 * \ version $Id: SingleTopPseudoAnalysisProducer.h,v 1.1.2.2 2013/06/21 20:40:24 oiorio Exp $
 */

//Single Top MC Producer
// Original 
// Adapted by O.Iorio

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
//#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Common/interface/View.h"

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"

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
#include "TopQuarkAnalysis/SingleTop/interface/SingleTopSystematicsTreesDumper.h"



//class JetFlavourIdentifier;



  class SingleTopPseudoAnalysisProducer : public edm::EDProducer {

    public:

      explicit SingleTopPseudoAnalysisProducer(const edm::ParameterSet & iConfig);
      ~SingleTopPseudoAnalysisProducer();
      virtual void produce(edm::Event & iEvent, const edm::EventSetup & iSetup);
    //       static void fillDescriptions(edm::ConfigurationDescriptions & descriptions);
    private:

    //InputTags
    edm::InputTag genParticlesSrc_,genJetsSrc_,
      MCQuarksPt_,
      MCQuarksPhi_,
      MCQuarksEta_,
      MCQuarksEnergy_,
      MCQuarksPdgId_,      

      MCLeptonsPt_,
      MCLeptonsPhi_,
      MCLeptonsEta_,
      MCLeptonsEnergy_,
      MCLeptonsPdgId_,      

      MCNeutrinosPt_,
      MCNeutrinosPhi_,
      MCNeutrinosEta_,
      MCNeutrinosEnergy_,
      MCNeutrinosPdgId_,      

      MCTopsPt_,
      MCTopsPhi_,
      MCTopsEta_,
      MCTopsEnergy_,
      MCTopsPdgId_,

      LHEMCQuarksPt_,
      LHEMCQuarksPhi_,
      LHEMCQuarksEta_,
      LHEMCQuarksEnergy_,
      LHEMCQuarksPdgId_,      

      LHEMCLeptonsPt_,
      LHEMCLeptonsPhi_,
      LHEMCLeptonsEta_,
      LHEMCLeptonsEnergy_,
      LHEMCLeptonsPdgId_,      

      LHEMCNeutrinosPt_,
      LHEMCNeutrinosPhi_,
      LHEMCNeutrinosEta_,
      LHEMCNeutrinosEnergy_,
      LHEMCNeutrinosPdgId_,      

      LHEMCTopsPt_,
      LHEMCTopsPhi_,
      LHEMCTopsEta_,
      LHEMCTopsEnergy_,
      LHEMCTopsPdgId_;      
      


  edm::Handle<std::vector<float> > 
  MCQuarksPt,
    MCQuarksPhi,
    MCQuarksEta,
    MCQuarksEnergy,
    MCQuarksPdgId,
    
    MCLeptonsPt,
    MCLeptonsPhi,
    MCLeptonsEta,
    MCLeptonsEnergy,
    MCLeptonsPdgId,

    MCNeutrinosPt,
    MCNeutrinosPhi,
    MCNeutrinosEta,
    MCNeutrinosEnergy,
    MCNeutrinosPdgId,
    
    MCTopsPt,
    MCTopsPhi,
    MCTopsEta,
    MCTopsEnergy,
    MCTopsPdgId,

    LHEMCQuarksPt,
    LHEMCQuarksPhi,
    LHEMCQuarksEta,
    LHEMCQuarksEnergy,
    
    LHEMCLeptonsPt,
    LHEMCLeptonsPhi,
    LHEMCLeptonsEta,
    LHEMCLeptonsEnergy,

    LHEMCNeutrinosPt,
    LHEMCNeutrinosPhi,
    LHEMCNeutrinosEta,
    LHEMCNeutrinosEnergy,
    
    LHEMCTopsPt,
    LHEMCTopsPhi,
    LHEMCTopsEta,
    LHEMCTopsEnergy;

    edm::Handle<std::vector<int> > 
    LHEMCQuarksPdgId,
    LHEMCLeptonsPdgId,
    LHEMCNeutrinosPdgId,
    LHEMCTopsPdgId;
    
    //cuts for genJets Matching
    double genJetsDeltarMatching_,leptonThreshold_,jetThreshold_,metThreshold_,mtwThreshold_,bTagEfficiency_;
    
    bool  useFullSelection_,matchWithLHE_;
    int seed;
  //Kinematic functions:
  math::PtEtaPhiELorentzVector top4Momentum(float leptonPx, float leptonPy, float leptonPz, float leptonE, float jetPx, float jetPy, float jetPz, float jetE, float metPx, float metPy);
  math::PtEtaPhiELorentzVector top4Momentum(math::PtEtaPhiELorentzVector lepton, math::PtEtaPhiELorentzVector jet, float metPx, float metPy);
  math::XYZTLorentzVector NuMomentum(float leptonPx, float leptonPy, float leptonPz, float leptonPt, float leptonE, float metPx, float metPy );
  float cosThetaLJ(math::PtEtaPhiELorentzVector lepton, math::PtEtaPhiELorentzVector jet, math::PtEtaPhiELorentzVector top);
  float cosTheta_eta_bl(math::PtEtaPhiELorentzVector lepton, math::PtEtaPhiELorentzVector jet, math::PtEtaPhiELorentzVector top);
    
  };



#endif
