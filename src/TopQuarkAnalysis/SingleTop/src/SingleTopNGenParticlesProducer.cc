/*
 *\Author: A. Orso M. Iorio 
 *
 *
 *\version  $Id: SingleTopNGenParticlesProducer.cc,v 1.1.2.1 2012/12/06 03:47:56 oiorio Exp $ 
 */

// Single Top producer: produces a top candidate made out of a Lepton, a B jet and a MET

#include "DataFormats/Candidate/interface/CandAssociation.h"

#include "TopQuarkAnalysis/SingleTop/interface/SingleTopNGenParticlesProducer.h"

#include "SimDataFormats/GeneratorProducts/interface/LHERunInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"

#include <vector>
#include <memory>

#include "DataFormats/Math/interface/LorentzVector.h"


//using namespace pat;


SingleTopNGenParticlesProducer::SingleTopNGenParticlesProducer(const edm::ParameterSet& iConfig) 
{
  // initialize the configurables
  
 
  //produces<std::vector< pat::TopLeptonic > >();
  produces< int >("NGenPartons");
 
}

void SingleTopNGenParticlesProducer::produce(edm::Event & iEvent, const edm::EventSetup & iEventSetup){

  int nup=0;

  edm::Handle<LHEEventProduct> infoHandleLHE;
  if (iEvent.getByLabel("source", infoHandleLHE))  nup = (*infoHandleLHE).hepeup().NUP;

  std::auto_ptr< int > nup_(new int( nup) );
  iEvent.put(nup_,"NGenPartons");

}

SingleTopNGenParticlesProducer::~SingleTopNGenParticlesProducer(){;}


DEFINE_FWK_MODULE( SingleTopNGenParticlesProducer );
