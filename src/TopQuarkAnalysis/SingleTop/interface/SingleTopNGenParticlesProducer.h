#ifndef _SingleTopNGenParticles_Producer_h
#define _SingleTopNGenParticles_Producer_h


/**
 *\Class SingleTopNGenParticlesProducer
 *
 * \Author A. Orso M. Iorio
 * 
 *
 *\version  $Id: SingleTopNGenParticlesProducer.h,v 1.1.2.1 2012/12/06 03:48:04 oiorio Exp $
 *
 *
*/


#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include <FWCore/Framework/interface/Run.h>

#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/ServiceRegistry/interface/Service.h" 

#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
//#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "DataFormats/Common/interface/View.h"

#include "DataFormats/Candidate/interface/NamedCompositeCandidate.h"

//#include "TLorentzVector.h"
#include "TopQuarkAnalysis/SingleTop/interface/EquationSolver.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h" 


//class JetFlavourIdentifier;


//namespace pat {

class SingleTopNGenParticlesProducer : public edm::EDProducer {
public:
  explicit SingleTopNGenParticlesProducer(const edm::ParameterSet & iConfig);
  ~SingleTopNGenParticlesProducer();
  virtual void produce(edm::Event & iEvent, const edm::EventSetup & iSetup);
  //       static void fillDescriptions(edm::ConfigurationDescriptions & descriptions);
  private:
   
  
};
//}


#endif
