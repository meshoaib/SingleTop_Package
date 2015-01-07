#ifndef __SINGLETOP_SYST_TREES_DUMPER_H__
#define __SINGLETOP_SYST_TREES_DUMPER_H__

/* \Class SingleTopSystematicsDumper
 *
 * \Authors A. Orso M. Iorio
 *
 * Produces systematics histograms out of a standard Single Top n-tuple
 * \ version $Id: SingleTopSystematicsTreesDumper.h,v 1.11.2.13.2.14.2.4 2013/06/21 20:40:24 oiorio Exp $
 */


//----------------- system include files
#include <memory>
#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>

//----------------- cmssw includes

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include <FWCore/Framework/interface/Run.h>

#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Framework/interface/TriggerNamesService.h"

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "JetMETCorrections/JetVertexAssociation/interface/JetVertexMain.h"
#include "DataFormats/HepMCCandidate/interface/PdfInfo.h"

#include "FWCore/Framework/interface/ESHandle.h"
//#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"

#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"

//--------------------TQAF includes
/*
#include "AnalysisDataFormats/TopObjects/interface/TopObject.h"
#include "AnalysisDataFormats/TopObjects/interface/TopLepton.h"
#include "AnalysisDataFormats/TopObjects/interface/TopJet.h"
#include "AnalysisDataFormats/TopObjects/interface/TopMET.h"
#include "AnalysisDataFormats/TopObjects/interface/TopElectron.h"
#include "AnalysisDataFormats/TopObjects/interface/TopMuon.h"
*/

//--------------------PAT includes
#include "DataFormats/PatCandidates/interface/Particle.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Jet.h"


//--------------------ROOT includes
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TLorentzVector.h"
#include "TH1.h"
#include "TH2.h"

//lorentzVector
#include "DataFormats/Math/interface/LorentzVector.h"

//B Tag reading from DB
#include "RecoBTag/Records/interface/BTagPerformanceRecord.h"
#include "CondFormats/PhysicsToolsObjects/interface/BinningPointByMap.h"
#include "RecoBTag/PerformanceDB/interface/BtagPerformance.h"

#include "PhysicsTools/Utilities/interface/LumiReWeighting.h"

//#include "PhysicsTools/Utilities/interface/Lumi3DReWeighting.h"
//#include "TopQuarkAnalysis/SingleTop/interface/Lumi3DReWeighting.h"


using namespace std;
using namespace edm;
using namespace reco;



class SingleTopSystematicsTreesDumper : public edm::EDAnalyzer
{
public:
  explicit SingleTopSystematicsTreesDumper(const edm::ParameterSet &);
  //  ~SingleTopSystematicsTreesDumper();

  
private:
  virtual void analyze(const edm::Event &, const edm::EventSetup &);
  virtual void endJob();
  void initBranchVars();
  
  //void  EventInfo();
  
  //Find functions descriptions in .cc
  
  //Kinematic functions:
  math::PtEtaPhiELorentzVector top4Momentum(float leptonPx, float leptonPy, float leptonPz, float leptonE, float jetPx, float jetPy, float jetPz, float jetE, float metPx, float metPy);
  math::PtEtaPhiELorentzVector top4Momentum(math::PtEtaPhiELorentzVector lepton, math::PtEtaPhiELorentzVector jet, float metPx, float metPy);
  math::XYZTLorentzVector NuMomentum(float leptonPx, float leptonPy, float leptonPz, float leptonPt, float leptonE, float metPx, float metPy );
  float cosThetaLJ(math::PtEtaPhiELorentzVector lepton, math::PtEtaPhiELorentzVector jet, math::PtEtaPhiELorentzVector top);
  float cosTheta_eta_bl(math::PtEtaPhiELorentzVector lepton, math::PtEtaPhiELorentzVector jet, math::PtEtaPhiELorentzVector top);
  
  double topMtw(math::PtEtaPhiELorentzVector lepton, math::PtEtaPhiELorentzVector jet, float metPx, float metPy);

  float muonHLTEff(float etaMu,string period);
  void muonHLTSF(float etaMu, float ptMu);
  void electronHLTSF(float etaEle, float ptEle);

  //B-weight generating functions
  void setBTagWeights(double ptCorr, double eta, int flavour, bool , string, string);
  double resolSF(double eta, string syst);
  double pileUpSF(string syst);
  double bTagSF(int B);
  double bTagSF(int B, string syst);
  
  double EFFMap(string); double EFFMap(string, string);  double EFFErrMap(string);
  

  //Jet uncertainty as a function of eta pt and jet flavour
  double jetUncertainty(double eta, double ptCorr, int flavour);
  void getJetPtE(const Event &iEvent, string syst );
  void getMET(const Event &iEvent, string syst );



  double offlineJESJERApplicationPt(double ptUncorr,double energyUncorr,double eta,string syst);
  double offlineJESJERApplicationE(double ptUncorr,double energyUncorr,double eta,string syst);



  //  int nsrc;// = 16;
  //  std::vector<JetCorrectionUncertainty*> vsrc(16);
  
  bool flavourFilter(string c, int nb, int nc, int nl);
  int eventFlavour(string c, int nb, int nc, int nl);
  
  
  
  double BTagSFNew(double pt, string algo);
  double MisTagSFNew(double pt, double eta, string algo);

  double BTagSFErrNew(double pt, string algo);
  double MisTagSFErrNewUp(double pt, double eta, string algo);
  double MisTagSFErrNewDown(double pt, double eta, string algo);
  double EFFMapNew(double btag, string algo);
  
  double topPtReweighting(string channel, double pt);
  void fillMCTruth(const Event &iEvent);
  void resetWeightsDoubles();
  
  
  //Define vector of required systematics to loop on
  std::vector<std::string> systematics, rate_systematics;
  
  
    //Define parameterSet to change from channel to channel
  edm::ParameterSet channelInfo;
  std::string channel;
  double crossSection, originalEvents, finalLumi, MTWCut, RelIsoCut;
  edm::Event   *iEvent;
  
  //  std::vector<float> leptonsPt,leptonsPhi,leptonsPz,leptonsEta,jetsPt,jetsPx,jetsPy,jetsPz,jetsEta,jetEnergy,jetsBTagAlgo,jetsAntiBTagAlgo,METPt,METPhi;
  
      //InputTags
  edm::InputTag leptonsPt_,
    leptonsPhi_,
    leptonsEta_,
    leptonsEnergy_,
    leptonsCharge_,
    leptonsID_,
    leptonsDB_,
    leptonsDZ_,
    leptonsMVAID_,
    leptonsNHits_,
    
    vertexZ_,
    
    
    leptonsDeltaCorrectedRelIso_,
    leptonsRhoCorrectedRelIso_,
    
    qcdLeptonsMVAID_,
    qcdLeptonsPt_,
    qcdLeptonsPhi_,
    qcdLeptonsEta_,
    qcdLeptonsEnergy_,
    qcdLeptonsCharge_,
    qcdLeptonsID_,
    qcdLeptonsDB_,
    qcdLeptonsDZ_,
    
    qcdLeptonsDeltaCorrectedRelIso_,
    qcdLeptonsRhoCorrectedRelIso_,
    
    
    looseElectronsDeltaCorrectedRelIso_,
    looseElectronsRhoCorrectedRelIso_,
    
    looseMuonsDeltaCorrectedRelIso_,
    looseMuonsRhoCorrectedRelIso_,

  //Tops
    MCTopsPt_,
    MCTopsPhi_,
    MCTopsEta_,
    MCTopsEnergy_,
    MCTopsPdgId_,
    MCTopsMotherId_,

    MCTopBQuarksPt_,
    MCTopBQuarksPhi_,
    MCTopBQuarksEta_,
    MCTopBQuarksEnergy_,
    MCTopBQuarksPdgId_,

    MCTopQuarksPt_,
    MCTopQuarksPhi_,
    MCTopQuarksEta_,
    MCTopQuarksEnergy_,
    MCTopQuarksPdgId_,

    MCTopQuarkBarsPt_,
    MCTopQuarkBarsPhi_,
    MCTopQuarkBarsEta_,
    MCTopQuarkBarsEnergy_,
    MCTopQuarkBarsPdgId_,

    MCTopLeptonsPt_,
    MCTopLeptonsPhi_,
    MCTopLeptonsEta_,
    MCTopLeptonsEnergy_,
    MCTopLeptonsPdgId_,

    MCTopNeutrinosPt_,
    MCTopNeutrinosPhi_,
    MCTopNeutrinosEta_,
    MCTopNeutrinosEnergy_,
    MCTopNeutrinosPdgId_,


    MCTopWsPt_,
    MCTopWsPhi_,
    MCTopWsEta_,
    MCTopWsEnergy_,
    MCTopWsPdgId_,

  //Other
    MCBQuarksPt_,
    MCBQuarksPhi_,
    MCBQuarksEta_,
    MCBQuarksEnergy_,
    MCBQuarksMotherId_,
    MCBQuarksPdgId_,
    
    MCQuarksPt_,
    MCQuarksPhi_,
    MCQuarksEta_,
    MCQuarksEnergy_,
    MCQuarksMotherId_,
    MCQuarksPdgId_,
    
    MCLeptonsPt_,
    MCLeptonsPhi_,
    MCLeptonsEta_,
    MCLeptonsEnergy_,
    MCLeptonsMotherId_,
    MCLeptonsPdgId_,

    MCNeutrinosPt_,
    MCNeutrinosPhi_,
    MCNeutrinosEta_,
    MCNeutrinosEnergy_,
    MCNeutrinosMotherId_,
    MCNeutrinosPdgId_,

    MCTopQuarksMotherId_,
    MCTopQuarkBarsMotherId_,
    MCTopLeptonsMotherId_,
    MCTopNeutrinosMotherId_,
    MCTopBQuarksMotherId_,
    MCTopWsMotherId_,
    MCTopWsDauOneId_,

    allJetsPt_,
    allJetsPhi_,
    allJetsEta_,
    allJetsFlavour_,
    
    genJetsPt_,
    genJetsEta_,

    genAllJetsPt_,
    genAllJetsEta_,
    jetsPt_,
    jetsPhi_,
    jetsEta_,
    jetsEnergy_,

    jetsPtJESDown_,
    jetsEnergyJESDown_,
    jetsPtJERDown_,
    jetsEnergyJERDown_,
    jetsPtJERUp_,
    jetsEnergyJERUp_,
    jetsPtJESUp_,
    jetsEnergyJESUp_,

    jetsBTagAlgo_,
    jetsCorrTotal_,
    jetsAntiBTagAlgo_,
    jetsPileUpID_,
    jetsPileUpWP_,
    jetsBeta_,
    jetsDZ_,
    jetsRMS_,
    METPt_,
    METPhi_,
    UnclDownMETPt_,
    UnclDownMETPhi_,
    UnclUpMETPt_,
    UnclUpMETPhi_,

    JESDownMETPt_,
    JESDownMETPhi_,
    JESUpMETPt_,
    JESUpMETPhi_,

    JERDownMETPt_,
    JERDownMETPhi_,
    JERUpMETPt_,
    JERUpMETPhi_,
    jetsFlavour_,
    npv_,
    n0_,
    np1_,
    nm1_,
    preWeights_,
    x1_,
    x2_,
    id1_,
    id2_,
    scalePDF_ ;
  



    // Handles
  edm::Handle<std::vector<float> >  leptonsPt,
    leptonsPhi,
    leptonsEta,
    leptonsEnergy,
    leptonsCharge,
    leptonsDeltaCorrectedRelIso,
    leptonsRhoCorrectedRelIso,
    leptonsID,
    leptonsMVAID,
    leptonsNHits,
    leptonsDB,
    leptonsDZ,
    vertexZ,

qcdLeptonsMVAID,    
qcdLeptonsPt,
    qcdLeptonsPhi,
    qcdLeptonsEta,
    qcdLeptonsEnergy,
    qcdLeptonsCharge,
    

    qcdLeptonsDeltaCorrectedRelIso,
    qcdLeptonsRhoCorrectedRelIso,
    
    qcdLeptonsID,
    qcdLeptonsDB,
    qcdLeptonsDZ,
    
    looseElectronsDeltaCorrectedRelIso,
    looseElectronsRhoCorrectedRelIso,
    
    looseMuonsDeltaCorrectedRelIso,
    looseMuonsRhoCorrectedRelIso,
    
    allJetsPt,
    allJetsPhi,
    allJetsEta,
    allJetsFlavour,    

    jetsEta,
    jetsPt,
    jetsPhi,
    jetsEnergy,
    jetsBTagAlgo,
    jetsAntiBTagAlgo,
    jetsFlavour,
    jetsCorrTotal,
    jetsPileUpID,
    jetsPileUpWP,
    
    jetsBeta,
    jetsDZ,
    jetsRMS,
    

    METPhi,
    METPt,
    UnclUpMETPhi,
    UnclUpMETPt,
    UnclDownMETPhi,
    UnclDownMETPt,

    JERUpMETPhi,
    JERUpMETPt,
    JERDownMETPhi,
    JERDownMETPt,

    JESUpMETPhi,
    JESUpMETPt,
    JESDownMETPhi,
    JESDownMETPt,
    
  //Tops
   
    MCTopsPt,
    MCTopsPhi,
    MCTopsEta,
    MCTopsEnergy,
    MCTopsPdgId,

    MCTopBQuarksPt,
    MCTopBQuarksPhi,
    MCTopBQuarksEta,
    MCTopBQuarksEnergy,
    MCTopBQuarksPdgId,

    MCTopQuarksPt,
    MCTopQuarksPhi,
    MCTopQuarksEta,
    MCTopQuarksEnergy,
    MCTopQuarksPdgId,
  
    MCTopQuarkBarsPt,
    MCTopQuarkBarsPhi,
    MCTopQuarkBarsEta,
    MCTopQuarkBarsEnergy,
    MCTopQuarkBarsPdgId,

    MCTopLeptonsPt,
    MCTopLeptonsPhi,
    MCTopLeptonsEta,
    MCTopLeptonsEnergy,
    MCTopLeptonsPdgId,
  
    MCTopNeutrinosPt,
    MCTopNeutrinosPhi,
    MCTopNeutrinosEta,
    MCTopNeutrinosEnergy,
    MCTopNeutrinosPdgId,

    MCTopWsPt,
    MCTopWsPhi,
    MCTopWsEta,
    MCTopWsEnergy,
    MCTopWsPdgId,

  //Other
    MCBQuarksPt,
    MCBQuarksPhi,
    MCBQuarksEta,
    MCBQuarksEnergy,
    MCBQuarksPdgId,
    
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
    MCNeutrinosPdgId  
    ;

  edm::Handle<std::vector<int> >  MCTopLeptonsMotherId,
    MCTopNeutrinosMotherId,
    MCTopQuarksMotherId,
    MCTopQuarkBarsMotherId,
    MCTopBQuarksMotherId,
    MCTopWsMotherId,
    MCTopWsDauOneId,
    MCNeutrinosMotherId,  
    MCBQuarksMotherId,
    MCTopsMotherId,
    MCQuarksMotherId,
    MCLeptonsMotherId ;
  
    edm::Handle<int > n0, nm1, np1;

  int npv, nMCTruthLeptons;

    int passingPreselection, passingLepton, passingMuonVeto, passingLeptonVeto, passingJets, passingBJets, passingMET;


    int nVertices, nGoodVertices;

    //Unclustered MET to take from the event
    edm::Handle< double > UnclMETPx, UnclMETPy, preWeights;
    edm::Handle< std::vector<double> > genJetsPt,genAllJetsPt;
    edm::Handle< float > x1h, x2h, scalePDFh;
    edm::Handle< int > id1h, id2h;
    std::string leptonsFlavour_, mode_;


    //Part for BTagging payloads
    edm::ESHandle<BtagPerformance> perfMHP;
    edm::ESHandle<BtagPerformance> perfMHPM;
    edm::ESHandle<BtagPerformance> perfMHE;
    edm::ESHandle<BtagPerformance> perfBHP;
    edm::ESHandle<BtagPerformance> perfBHPM;
    edm::ESHandle<BtagPerformance> perfBHE;


    //Part for JEC and JES
    //Part for JEC and JES
    string JEC_PATH;
    //  JetResolution *ptResol;
    edm::FileInPath fip;
    JetCorrectionUncertainty *jecUnc;
    double JES_SW, JES_b_cut, JES_b_overCut;
double jetsBTagNoSyst[10],jetsBTag[10], ljetsBTag[10] ;


    //4-momenta vectors definition
    /*  std::vector<math::PtEtaPhiELorentzVector>
      jets,
      loosejets,
      bjets,
      antibjets;*/
    math::PtEtaPhiELorentzVector leptons[3],
         qcdLeptons[3],
         jets[10],
         jetsNoSyst[10],         
         ljets[30],
         bjets[10],bJetDecay,bJetRecoil,
         antibjets[10];
    int flavours[10];
    int bjets_flavours[10];
    int lflavours[10];

    float pdf_weights[52];
  float  pdf_weights_mstw, pdf_weights_nnpdf21, pdf_weights_gjr_ff, pdf_weights_gjr_fv, pdf_weights_gjr_fdis, pdf_weights_alekhin ;

  //Tops
   
float    MCTopsPtVec[2],
    MCTopsPhiVec[2],
    MCTopsEtaVec[2],
    MCTopsEnergyVec[2],
    MCTopsPdgIdVec[2],
    MCTopsMotherIdVec[2],

    MCTopBQuarksPtVec[2],
    MCTopBQuarksPhiVec[2],
    MCTopBQuarksEtaVec[2],
    MCTopBQuarksEnergyVec[2],
    MCTopBQuarksPdgIdVec[2],
    MCTopBQuarksMotherIdVec[2],

    MCTopQuarksPtVec[2],
    MCTopQuarksPhiVec[2],
    MCTopQuarksEtaVec[2],
    MCTopQuarksEnergyVec[2],
    MCTopQuarksPdgIdVec[2],
    MCTopQuarksMotherIdVec[2],

    MCTopQuarkBarsPtVec[2],
    MCTopQuarkBarsPhiVec[2],
    MCTopQuarkBarsEtaVec[2],
    MCTopQuarkBarsEnergyVec[2],
    MCTopQuarkBarsPdgIdVec[2],
    MCTopQuarkBarsMotherIdVec[2],

    MCTopLeptonsPtVec[2],
    MCTopLeptonsPhiVec[2],
    MCTopLeptonsEtaVec[2],
    MCTopLeptonsEnergyVec[2],
    MCTopLeptonsPdgIdVec[2],
    MCTopLeptonsMotherIdVec[2],

    MCTopNeutrinosPtVec[2],
    MCTopNeutrinosPhiVec[2],
    MCTopNeutrinosEtaVec[2],
    MCTopNeutrinosEnergyVec[2],
    MCTopNeutrinosPdgIdVec[2],
    MCTopNeutrinosMotherIdVec[2],

    MCTopWsPtVec[2],
    MCTopWsPhiVec[2],
    MCTopWsEtaVec[2],
    MCTopWsEnergyVec[2],
    MCTopWsPdgIdVec[2],
    MCTopWsDauOneIdVec[2],

  //Other
    MCBQuarksPtVec[4],
    MCBQuarksPhiVec[4],
    MCBQuarksEtaVec[4],
    MCBQuarksEnergyVec[4],
    MCBQuarksPdgIdVec[4],
    MCBQuarksMotherIdVec[4],
    
    MCQuarksPtVec[12],
    MCQuarksPhiVec[12],
    MCQuarksEtaVec[12],
    MCQuarksEnergyVec[12],
    MCQuarksPdgIdVec[12],
    MCQuarksMotherIdVec[12],
    
    MCLeptonsPtVec[4],
    MCLeptonsPhiVec[4],
    MCLeptonsEtaVec[4],
    MCLeptonsEnergyVec[4],
    MCLeptonsPdgIdVec[4],
    MCLeptonsMotherIdVec[4],

    MCNeutrinosPtVec[4],
    MCNeutrinosPhiVec[4],
    MCNeutrinosEtaVec[4],
    MCNeutrinosEnergyVec[4],
    MCNeutrinosPdgIdVec[4],
    MCNeutrinosMotherIdVec[4]
    ;

  
    //  float recorrection_weights[7][7];
    //  float pt_bin_extremes[8];
    //  float tchpt_bin_extremes[8];

    TH2D histoSFs;

    math::PtEtaPhiELorentzVector leptonPFour;
math::PtEtaPhiELorentzVector top;
    //Definition of trees

    map<string, TTree *> trees2J[6];
    map<string, TTree *> trees3J[6];
    map<string, TTree *> trees4J[6];
    map<string, TTree *> treesNJets;
//    TTree * treesMCTruth;
map<string, TTree *> treesMCTruth;
  
  bool doJetTrees_, isSingleTopCompHEP_;



    enum Bin
    {
        ZeroT = 0,
        OneT = 1,
        TwoT = 2,
        ZeroT_QCD = 3,
        OneT_QCD = 4,
        TwoT_QCD = 5
    };


    //Other variables definitions
    double bTagThreshold, maxPtCut;
    size_t bScanSteps;


  bool doBScan_, doQCD_, doPDF_, takeBTagSFFromDB_, addPDFToNJets, doMCTruth_, doFullMCTruth_, doTopPtReweighting_, doTopBestMass_, doAsymmetricPtCut_;
    //To be changed in 1 tree, now we keep
    //because we have no time to change and debug
    map<string, TTree *> treesScan[10];
    map<string, TTree *> treesScanQCD[10];
    //Vectors of b-weights
    vector< double > b_weight_tag_algo1,
    b_weight_tag_algo2,
    b_weight_antitag_algo1,
    b_weight_antitag_algo2,
    b_discriminator_value_tag_algo1,
    b_discriminator_value_antitag_algo2;

    //Variables to use as trees references

    //Variables to use as trees references
    double etaTree, etaTree2, cosTree, cosBLTree, cos1Tree, cos1BLTree, cos2Tree, cos2BLTree, topMassTree, top1MassTree, top2MassTree, totalWeightTree, weightTree, mtwMassTree, lowBTagTree, highBTagTree, mediumBTagTree,mediumlowBTagTree ,maxPtTree, minPtTree,maxLoosePtTree, topMassLowBTagTree, topMassBestTopTree, topMassMeas, bWeightTree, PUWeightTree, limuWeightTree, miscWeightTree, lepEff, lepEffB,lepSF,lepSFB,lepSFC , lepSFD, 
         topMtwTree, HT , H ,
    lepSFIDUp,
    lepSFIDDown,
    lepSFIsoUp,
    lepSFIsoDown,
    lepSFTrigUp,
    lepSFTrigDown,

    lepSFIDUpB,
    lepSFIDDownB,
    lepSFIsoUpB,
    lepSFIsoDownB,
    lepSFTrigUpB,
    lepSFTrigDownB,
    lepSFIDUpC,
    lepSFIDDownC,
    lepSFIsoUpC,
    lepSFIsoDownC,
    lepSFTrigUpC,
    lepSFTrigDownC,

    lepSFIDUpD,
    lepSFIDDownD,
    lepSFIsoUpD,
    lepSFIsoDownD,
    lepSFTrigUpD,
    lepSFTrigDownD,
    
    sfID,sfIDup,sfIDdown,  
    sfIso,sfIsoup,sfIsodown,  
    sfTrig,sfTrigup,sfTrigdown  
    ;
    //Weights for systematics
    double bWeightTreeBTagUp,
           bWeightTreeMisTagUp,
           bWeightTreeBTagDown,
           bWeightTreeMisTagDown,
           PUWeightTreePUUp,
           PUWeightTreePUDown;
  
  double topPtReweight, topPtReweightMCTruth,topPtReweightNorm, topPtReweightMCTruthNorm;
  double topPtReweightUp, topPtReweightMCTruthUp,topPtReweightNormUp, topPtReweightMCTruthNormUp;
  double topPtReweightDown, topPtReweightMCTruthDown,topPtReweightNormDown, topPtReweightMCTruthNormDown;

   int nJ, nJNoPU, nJCentral, nJCentralNoPU, nJForward, nJForwardNoPU, nTCHPT, nCSVT, nCSVM, nJLoose,nJLooseCentral , nJLooseForward, nJLooseMBTag;



    double w1TCHPT, w2TCHPT, w1CSVT, w2CSVT, w1CSVM, w2CSVM;

  int runTree, eventTree, lumiTree, chargeTree, electronID,bJet1Flavour,bJet2Flavour ,looseJetFlavourTree ,bJetFlavourTree, fJetFlavourTree, eventFlavourTree, puZero, firstJetFlavourTree, secondJetFlavourTree, thirdJetFlavourTree,fourthJetFlavourTree, isQCDTree;

  double lepPt, lepEta,lepE, lepPhi, lepRelIso, lepDeltaCorrectedRelIso, lepRhoCorrectedRelIso, fJetPhi, fJetPt, fJetEta, fJetE,fJetBTag, bJetPt, bJetEta, bJetPhi, bJetE, bJetBTag, metPt, metPhi, topPt, topPhi, topEta, topE, top1Pt, top1Phi, top1Eta, top1E, top2Pt, top2Phi, top2Eta, top2E, totalEnergy, totalMomentum,  vtxZ, fJetPUID, fJetPUWP;
double bJetPUID, bJetPUWP, firstJetPt, firstJetEta, firstJetPhi, firstJetE,firstJetBTag, secondJetPt, secondJetEta, secondJetPhi, secondJetE, secondJetBTag, thirdJetPt, thirdJetEta, thirdJetPhi, thirdJetE, thirdJetBTag, fourthJetPt, fourthJetEta, fourthJetPhi, fourthJetE, fourthJetBTag, fJetBeta, fJetDZ, fJetRMS, bJetBeta, bJetDZ, bJetRMS; 
double leptonMVAID,leptonNHits ,looseJetPt, looseJetEta, looseJetPhi, looseJetE, looseJetBTag, Mlb1Tree, Mlb2Tree, Mb1b2Tree, pTb1b2Tree, bJet1Pt, bJet1Eta, bJet1Phi, bJet1E, bJet1BTag, bJet2Pt, bJet2Eta, bJet2Phi, bJet2E, bJet2BTag;
double bJetDecayPt, bJetDecayEta, bJetDecayPhi, bJetDecayE, bJetDecayFlavour,bJetDecayBTag;
double bJetRecoilPt, bJetRecoilEta, bJetRecoilPhi, bJetRecoilE, bJetRecoilFlavour,bJetRecoilBTag;

 //Not used anymore:
    double loosePtCut, resolScale ;
    bool doPU_, doResol_ ;

    edm::LumiReWeighting LumiWeights_, LumiWeightsUp_, LumiWeightsDown_;
    std::string mcPUFile_, dataPUFile_, puHistoName_;

    std::vector<double> jetprobs,
        jetprobs_j1up,
        jetprobs_j2up,
        jetprobs_j3up,
        jetprobs_b1up,
        jetprobs_b2up,
        jetprobs_b3up,
        jetprobs_j1down,
        jetprobs_j2down,
        jetprobs_j3down,
        jetprobs_b1down,
        jetprobs_b2down,
        jetprobs_b3down ;

    double leptonRelIsoQCDCutUpper, leptonRelIsoQCDCutLower;
  bool gotLeptons, gotJets, gotAllJets, gotMets, gotLooseLeptons, gotPU, gotQCDLeptons, gotPV,gotPDFs;

  int nb, nc, nudsg, ntchpt_tags, ncsvm_tags, ncsvt_tags,ncsvl_tags,
        nbNoSyst, ncNoSyst, nudsgNoSyst,
        ntchpt_antitags, ntchpm_tags, ntchel_tags, ntche_antitags, ntight_tags;

    string algo_;
  
    double TCHPM_LMisTagUp,  TCHPM_BBTagUp, TCHPM_CBTagUp, TCHPM_LMisTagDown, TCHPM_BBTagDown, TCHPM_CBTagDown;
    double TCHPM_LAntiMisTagUp,  TCHPM_BAntiBTagUp, TCHPM_CAntiBTagUp, TCHPM_LAntiMisTagDown, TCHPM_BAntiBTagDown, TCHPM_CAntiBTagDown;
    double TCHPM_C,  TCHPM_B, TCHPM_L;
    double TCHPM_CAnti,  TCHPM_BAnti, TCHPM_LAnti;

    double TCHPT_LMisTagUp,  TCHPT_BBTagUp, TCHPT_CBTagUp, TCHPT_LMisTagDown, TCHPT_BBTagDown, TCHPT_CBTagDown;
    double TCHPT_LAntiMisTagUp,  TCHPT_BAntiBTagUp, TCHPT_CAntiBTagUp, TCHPT_LAntiMisTagDown, TCHPT_BAntiBTagDown, TCHPT_CAntiBTagDown;
    double TCHPT_C,  TCHPT_B, TCHPT_L;
    double TCHPT_CAnti,  TCHPT_BAnti, TCHPT_LAnti;


    double TCHEL_LMisTagUp,  TCHEL_BBTagUp, TCHEL_CBTagUp, TCHEL_LMisTagDown, TCHEL_BBTagDown, TCHEL_CBTagDown;
    double TCHEL_LAntiMisTagUp,  TCHEL_BAntiBTagUp, TCHEL_CAntiBTagUp, TCHEL_LAntiMisTagDown, TCHEL_BAntiBTagDown, TCHEL_CAntiBTagDown;
    double TCHEL_C,  TCHEL_B, TCHEL_L;
    double TCHEL_CAnti,  TCHEL_BAnti, TCHEL_LAnti;
    
    double facBTagErr;
    bool useMVAID_, useCutBasedID_;

    class BTagWeight
    {
    public:
      
    BTagWeight():
      minTags(0), maxTags(0)
	{
	  ;
	}
      struct JetInfo
      {
      JetInfo(float mceff, float datasf) : eff(mceff), sf(datasf) {}
	float eff;
	float sf;
      };
      
    BTagWeight(int jmin, int jmax) :
      minTags(jmin),maxTags(jmax) {}
      
      bool filter(int t);
      float weight(vector<JetInfo> jets, int tags);
      float weightWithVeto(vector<JetInfo> jetsTags, int tags, vector<JetInfo> jetsVetoes, int vetoes);
      
    private:
      int minTags;
      int maxTags;
      
      
    };
    
    vector<BTagWeight::JetInfo> jsfshpt, jsfshel,
      jsfshpt_b_tag_up, jsfshel_b_tag_up,
      jsfshpt_mis_tag_up, jsfshel_mis_tag_up,
      jsfshpt_b_tag_down, jsfshel_b_tag_down,
      jsfshpt_mis_tag_down, jsfshel_mis_tag_down,
      jsfshptNoSyst, jsfshelNoSyst; // bjs,cjs,ljs;
    
    
    vector<BTagWeight::JetInfo> jsfscsvt, jsfscsvm,
      jsfscsvt_b_tag_up, jsfscsvm_b_tag_up,
      jsfscsvt_mis_tag_up, jsfscsvm_mis_tag_up,
      jsfscsvt_b_tag_down, jsfscsvm_b_tag_down,
      jsfscsvt_mis_tag_down, jsfscsvm_mis_tag_down,
      jsfscsvtNoSyst, jsfscsvmNoSyst; // bjs,cjs,ljs;
    
    

    BTagWeight b_tchpt_0_tags,
               b_tchpt_1_tag,
               b_tchpt_2_tags;

    BTagWeight b_csvm_0_tags,
               b_csvm_1_tag,
               b_csvm_2_tags;

    BTagWeight b_csvt_0_tags,
               b_csvt_1_tag,
               b_csvt_2_tags;

    double b_weight_tchpt_0_tags,
           b_weight_tchpt_1_tag,
           b_weight_tchpt_2_tags;

    double b_weight_csvm_0_tags,
           b_weight_csvm_1_tag,
           b_weight_csvm_2_tags;

    double b_weight_csvt_0_tags,
           b_weight_csvt_1_tag,
           b_weight_csvt_2_tags;

  bool doBTagSF_;
    float x1, x2, Q2, scalePDF;
    int id1, id2;

  bool isFirstEvent, doReCorrection_, doLooseBJetVeto_;

    vector<JetCorrectorParameters > *vParData;
    FactorizedJetCorrector *JetCorrectorData;
    vector<JetCorrectorParameters > vParMC;
    FactorizedJetCorrector *JetCorrectorMC;
};

#endif
