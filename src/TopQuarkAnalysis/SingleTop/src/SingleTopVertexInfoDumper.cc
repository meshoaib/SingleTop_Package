/*
 *\Author: A. Orso M. Iorio 
 *
 *
 *\version  $Id: SingleTopVertexInfoDumper.cc,v 1.1.2.1 2011/09/21 13:19:39 oiorio Exp $ 
 */

// Single Top producer: produces a top candidate made out of a Lepton, a B jet and a MET

#include "DataFormats/Candidate/interface/CandAssociation.h"

#include "TopQuarkAnalysis/SingleTop/interface/SingleTopVertexInfoDumper.h"
#include "DataFormats/VertexReco/interface/Vertex.h"

#include <vector>
#include <memory>

#include "DataFormats/Math/interface/LorentzVector.h"


//using namespace pat;


SingleTopVertexInfoDumper::SingleTopVertexInfoDumper(const edm::ParameterSet& iConfig) 
{
  // initialize the configurables
  
  
  src_                 = iConfig.getParameter<edm::InputTag>	      ( "src" );
   
  produces< std::vector<float> >("chi");
  produces< std::vector<float> >("rho");
  produces< std::vector<float> >("z");
  produces< std::vector< int> >("ndof");
 
}

void SingleTopVertexInfoDumper::produce(edm::Event & iEvent, const edm::EventSetup & iEventSetup){
  
  
 iEvent.getByLabel(src_,vertices);

  
 std::auto_ptr< std::vector< float > >chi_(new std::vector< float >) ;
 std::auto_ptr< std::vector< float > >rho_ (new std::vector< float >) ;
 std::auto_ptr< std::vector< float > >z_ (new std::vector< float >) ;
 std::auto_ptr< std::vector< int > >ndof_ (new std::vector< int >) ;
 
  
 for(size_t v = 0; v<vertices->size();++v){;
   chi_->push_back(vertices->at(v).chi2());
   ndof_->push_back(vertices->at(v).ndof());
   z_->push_back(vertices->at(v).position().z());
   rho_->push_back(vertices->at(v).position().rho());

 }
  
   
   iEvent.put(chi_,"chi");
   iEvent.put(rho_,"rho");
   iEvent.put(z_,"z");
   iEvent.put(ndof_,"ndof");
}

SingleTopVertexInfoDumper::~SingleTopVertexInfoDumper(){;}


DEFINE_FWK_MODULE( SingleTopVertexInfoDumper );
