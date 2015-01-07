/*
*\Author:  O.Iorio
*
*
*
*\version  $Id: SingleTopSystematicsTreesDumper.cc,v 1.12.2.18.2.16.2.6 2013/06/21 20:40:25 oiorio Exp $
*/
// This analyzer dumps the histograms for all systematics listed in the cfg file
//
//
//

#define DEBUG    0 // 0=false
#define MC_DEBUG 0 // 0=false   else -> dont process preselection
#define C_DEBUG  0 // currently debuging

#include "TopQuarkAnalysis/SingleTop/interface/SingleTopSystematicsTreesDumper.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Common/interface/TriggerNames.h"
//#include "PhysicsTools/UtilAlgos/interface/TFileService.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
//#include "FWCore/Framework/interface/TriggerNames.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "DataFormats/Candidate/interface/NamedCompositeCandidate.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include <Math/VectorUtil.h>
//#include "CommonTools/CandUtils/interface/Booster.h"
#include <sstream> //libreria per usare stringstream
//#include "PhysicsTools/Utilities/interface/LumiReWeighting.h"
#include "DataFormats/Math/interface/deltaR.h"

#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "TopQuarkAnalysis/SingleTop/interface/EquationSolver.h"


namespace LHAPDF
{
void initPDFSet(int nset, const std::string &filename, int member = 0);
int numberPDF(int nset);
void usePDFMember(int nset, int member);
double xfx(int nset, double x, double Q, int fl);
double getXmin(int nset, int member);
double getXmax(int nset, int member);
double getQ2min(int nset, int member);
double getQ2max(int nset, int member);
void extrapolate(bool extrapolate = true);
}

SingleTopSystematicsTreesDumper::SingleTopSystematicsTreesDumper(const edm::ParameterSet &iConfig)
{
    systematics = iConfig.getUntrackedParameter<std::vector<std::string> >("systematics");

    //Channel information
    channelInfo = iConfig.getParameter<edm::ParameterSet>("channelInfo");
    //Cross section, name and number of events
    channel = channelInfo.getUntrackedParameter<string>("channel");
    crossSection = channelInfo.getUntrackedParameter<double>("crossSection");
    originalEvents = channelInfo.getUntrackedParameter<double>("originalEvents");
    finalLumi = channelInfo.getUntrackedParameter<double>("finalLumi");
    MTWCut = channelInfo.getUntrackedParameter<double>("MTWCut", 50);


    RelIsoCut = channelInfo.getUntrackedParameter<double>("RelIsoCut", 0.1);
    loosePtCut = channelInfo.getUntrackedParameter<double>("loosePtCut", 40);

    addPDFToNJets  =  channelInfo.getUntrackedParameter< bool >("addPDFToNJets", false);
    isSingleTopCompHEP_  =  channelInfo.getUntrackedParameter< bool >("isSingleTopCompHEP", false);
    maxPtCut = iConfig.getUntrackedParameter<double>("maxPtCut", 40);
    
    //tight leptons
    leptonsFlavour_ =  iConfig.getUntrackedParameter< std::string >("leptonsFlavour");


    leptonsPt_ =  iConfig.getParameter< edm::InputTag >("leptonsPt");
    leptonsPhi_ =  iConfig.getParameter< edm::InputTag >("leptonsPhi");
    leptonsEta_ =  iConfig.getParameter< edm::InputTag >("leptonsEta");
    leptonsEnergy_ =  iConfig.getParameter< edm::InputTag >("leptonsEnergy");
    leptonsCharge_ =  iConfig.getParameter< edm::InputTag >("leptonsCharge");

    leptonsDeltaCorrectedRelIso_ =  iConfig.getParameter< edm::InputTag >("leptonsDeltaCorrectedRelIso");
    leptonsRhoCorrectedRelIso_ =  iConfig.getParameter< edm::InputTag >("leptonsRhoCorrectedRelIso");

    leptonsDB_ =  iConfig.getParameter< edm::InputTag >("leptonsDB");
    leptonsDZ_ =  iConfig.getParameter< edm::InputTag >("leptonsDZ");
    leptonsID_ =  iConfig.getParameter< edm::InputTag >("leptonsID");
    leptonsMVAID_ =  iConfig.getParameter< edm::InputTag >("leptonsMVAID");
    leptonsNHits_ =  iConfig.getParameter< edm::InputTag >("leptonsNHits");
    
    //qcd leptons
    
    qcdLeptonsPt_ =  iConfig.getParameter< edm::InputTag >("qcdLeptonsPt");
    qcdLeptonsPhi_ =  iConfig.getParameter< edm::InputTag >("qcdLeptonsPhi");
    qcdLeptonsEta_ =  iConfig.getParameter< edm::InputTag >("qcdLeptonsEta");
    qcdLeptonsEnergy_ =  iConfig.getParameter< edm::InputTag >("qcdLeptonsEnergy");
    qcdLeptonsCharge_ =  iConfig.getParameter< edm::InputTag >("qcdLeptonsCharge");
    qcdLeptonsMVAID_ =  iConfig.getParameter< edm::InputTag >("qcdLeptonsMVAID");
    qcdLeptonsDeltaCorrectedRelIso_ =  iConfig.getParameter< edm::InputTag >("qcdLeptonsDeltaCorrectedRelIso");
    qcdLeptonsRhoCorrectedRelIso_ =  iConfig.getParameter< edm::InputTag >("qcdLeptonsRhoCorrectedRelIso");

    qcdLeptonsDB_ =  iConfig.getParameter< edm::InputTag >("qcdLeptonsDB");
    qcdLeptonsID_ =  iConfig.getParameter< edm::InputTag >("qcdLeptonsID");

    leptonsFlavour_ =  iConfig.getUntrackedParameter< std::string >("leptonsFlavour");

    looseMuonsDeltaCorrectedRelIso_ =  iConfig.getParameter< edm::InputTag >("looseMuonsDeltaCorrectedRelIso");
    looseMuonsRhoCorrectedRelIso_ =  iConfig.getParameter< edm::InputTag >("looseMuonsRhoCorrectedRelIso");

    looseElectronsDeltaCorrectedRelIso_ =  iConfig.getParameter< edm::InputTag >("looseElectronsDeltaCorrectedRelIso");
    looseElectronsRhoCorrectedRelIso_ =  iConfig.getParameter< edm::InputTag >("looseElectronsRhoCorrectedRelIso");


    //Jets
    jetsEta_ =  iConfig.getParameter< edm::InputTag >("jetsEta");
    jetsPt_ =  iConfig.getParameter< edm::InputTag >("jetsPt");
    jetsPhi_ =  iConfig.getParameter< edm::InputTag >("jetsPhi");
    jetsEnergy_ =  iConfig.getParameter< edm::InputTag >("jetsEnergy");

    jetsPtJESUp_ =  iConfig.getParameter< edm::InputTag >("jetsPtJESUp");
    jetsEnergyJESUp_ =  iConfig.getParameter< edm::InputTag >("jetsEnergyJESUp");

    jetsPtJERUp_ =  iConfig.getParameter< edm::InputTag >("jetsPtJERUp");
    jetsEnergyJERUp_ =  iConfig.getParameter< edm::InputTag >("jetsEnergyJERUp");

    jetsPtJERDown_ =  iConfig.getParameter< edm::InputTag >("jetsPtJERDown");
    jetsEnergyJERDown_ =  iConfig.getParameter< edm::InputTag >("jetsEnergyJERDown");

    jetsPtJESDown_ =  iConfig.getParameter< edm::InputTag >("jetsPtJESDown");
    jetsEnergyJESDown_ =  iConfig.getParameter< edm::InputTag >("jetsEnergyJESDown");


    allJetsPt_ =  iConfig.getParameter< edm::InputTag >("allJetsPt");
    allJetsPhi_ =  iConfig.getParameter< edm::InputTag >("allJetsPhi");
    allJetsEta_ =  iConfig.getParameter< edm::InputTag >("allJetsEta");
    allJetsFlavour_ =  iConfig.getParameter< edm::InputTag >("allJetsFlavour");
    
    jetsBTagAlgo_ =  iConfig.getParameter< edm::InputTag >("jetsBTagAlgo");
    jetsAntiBTagAlgo_ =  iConfig.getParameter< edm::InputTag >("jetsAntiBTagAlgo");
    
    jetsPileUpID_ =  iConfig.getParameter< edm::InputTag >("jetsPileUpDiscr");
    jetsPileUpWP_ =  iConfig.getParameter< edm::InputTag >("jetsPileUpWP");
    
    jetsBeta_ =  iConfig.getParameter< edm::InputTag >("jetsBeta");
    jetsDZ_ =  iConfig.getParameter< edm::InputTag >("jetsDZ");
    jetsRMS_ =  iConfig.getParameter< edm::InputTag >("jetsRMS");

    jetsFlavour_ =  iConfig.getParameter< edm::InputTag >("jetsFlavour");

    METPhi_ =  iConfig.getParameter< edm::InputTag >("METPhi");
    METPt_ =  iConfig.getParameter< edm::InputTag >("METPt");

    UnclUpMETPhi_ =  iConfig.getParameter< edm::InputTag >("UnclUpMETPhi");
    UnclUpMETPt_ =  iConfig.getParameter< edm::InputTag >("UnclUpMETPt");

    UnclDownMETPhi_ =  iConfig.getParameter< edm::InputTag >("UnclDownMETPhi");
    UnclDownMETPt_ =  iConfig.getParameter< edm::InputTag >("UnclDownMETPt");

    JESUpMETPhi_ =  iConfig.getParameter< edm::InputTag >("JESUpMETPhi");
    JESUpMETPt_ =  iConfig.getParameter< edm::InputTag >("JESUpMETPt");

    JESDownMETPhi_ =  iConfig.getParameter< edm::InputTag >("JESDownMETPhi");
    JESDownMETPt_ =  iConfig.getParameter< edm::InputTag >("JESDownMETPt");

    JERUpMETPhi_ =  iConfig.getParameter< edm::InputTag >("JERUpMETPhi");
    JERUpMETPt_ =  iConfig.getParameter< edm::InputTag >("JERUpMETPt");

    JERDownMETPhi_ =  iConfig.getParameter< edm::InputTag >("JERDownMETPhi");
    JERDownMETPt_ =  iConfig.getParameter< edm::InputTag >("JERDownMETPt");





    jetsCorrTotal_ =  iConfig.getParameter< edm::InputTag >("jetsCorrTotal");

    doQCD_  =  iConfig.getUntrackedParameter< bool >("doQCD", true);

    doPDF_  =  iConfig.getUntrackedParameter< bool >("doPDF", true);
    doBTagSF_  =  iConfig.getUntrackedParameter< bool >("doBTagSF", true);

    useMVAID_  =  iConfig.getUntrackedParameter< bool >("useMVAID", true);
    useCutBasedID_  =  iConfig.getUntrackedParameter< bool >("useCutBasedID", false);
    
    //    cout << " mva id " << useMVAID_ << " cutbased " << useCutBasedID_ << endl;

    if(useCutBasedID_ == useMVAID_){
      cout << " can't use cutBasedID and MVAID together! Choose one!"<<endl;
    }
    


    //Q2 part
    x1_ = iConfig.getParameter<edm::InputTag>("x1") ;
    x2_ = iConfig.getParameter<edm::InputTag>("x2") ;

    id1_ = iConfig.getParameter<edm::InputTag>("id1") ;
    id2_ = iConfig.getParameter<edm::InputTag>("id2") ;

    scalePDF_ = iConfig.getParameter<edm::InputTag>("scalePDF") ;
    //top pt reweighting
    doTopPtReweighting_ = iConfig.getUntrackedParameter<bool>("doTopPtReweighting", true);
   
    //Top mass method 
    doTopBestMass_ = iConfig.getUntrackedParameter<bool> ("doTopBestMass",true); 

   // Pt cut, asymmetric in the third jet (30 GeV)
    doAsymmetricPtCut_ = iConfig.getUntrackedParameter<bool> ("doAsymmetricPtCut",true);

    //Pile Up Part
    np1_ = iConfig.getParameter< edm::InputTag >("nVerticesPlus");//,"PileUpSync");
    nm1_ = iConfig.getParameter< edm::InputTag >("nVerticesMinus");//,"PileUpSync");
    n0_ = iConfig.getParameter< edm::InputTag >("nVertices");//,"PileUpSync");

    vertexZ_ = iConfig.getParameter< edm::InputTag >("vertexZ");//,"PileUpSync");

    doPU_ = iConfig.getUntrackedParameter< bool >("doPU", false);
    doResol_ = iConfig.getUntrackedParameter< bool >("doResol", false);

    doReCorrection_ = iConfig.getUntrackedParameter< bool >("doReCorrection", false);
    dataPUFile_ =  channelInfo.getUntrackedParameter< std::string >("Season", "Summer12");

    takeBTagSFFromDB_ = iConfig.getUntrackedParameter< bool >("takeBTagSFFromDB", true);

    doJetTrees_ = iConfig.getUntrackedParameter< bool >("doJetTrees", true);

    algo_ = iConfig.getUntrackedParameter< std::string >("algo", "CSVT");
//    algo_ = iConfig.getUntrackedParameter< std::string >("algo", "TCHPT");
    doLooseBJetVeto_ = iConfig.getUntrackedParameter< bool >("doLooseBJetVeto", false);

    //MC Truth part
    doMCTruth_ = iConfig.getUntrackedParameter< bool >("doMCTruth", true);
    doFullMCTruth_ = iConfig.getUntrackedParameter< bool >("doFullMCTruth", true); //use to fill trees MC truth for given control sample

    //Quarks/leptons
    MCQuarksEta_ =  iConfig.getParameter< edm::InputTag >("MCQuarksEta");
    MCQuarksPt_ =  iConfig.getParameter< edm::InputTag >("MCQuarksPt");
    MCQuarksPhi_ =  iConfig.getParameter< edm::InputTag >("MCQuarksPhi");
    MCQuarksEnergy_ =  iConfig.getParameter< edm::InputTag >("MCQuarksEnergy");
    MCQuarksPdgId_ =  iConfig.getParameter< edm::InputTag >("MCQuarksPdgId");
    MCQuarksMotherId_ =  iConfig.getParameter< edm::InputTag >("MCQuarksMotherId");
    
    MCBQuarksEta_ =  iConfig.getParameter< edm::InputTag >("MCBQuarksEta");
    MCBQuarksPt_ =  iConfig.getParameter< edm::InputTag >("MCBQuarksPt");
    MCBQuarksPhi_ =  iConfig.getParameter< edm::InputTag >("MCBQuarksPhi");
    MCBQuarksEnergy_ =  iConfig.getParameter< edm::InputTag >("MCBQuarksEnergy");
    MCBQuarksPdgId_ =  iConfig.getParameter< edm::InputTag >("MCBQuarksPdgId");
    MCBQuarksMotherId_ =  iConfig.getParameter< edm::InputTag >("MCBQuarksMotherId");
    
    MCLeptonsEta_ =  iConfig.getParameter< edm::InputTag >("MCLeptonsEta");
    MCLeptonsPt_ =  iConfig.getParameter< edm::InputTag >("MCLeptonsPt");
    MCLeptonsPhi_ =  iConfig.getParameter< edm::InputTag >("MCLeptonsPhi");
    MCLeptonsEnergy_ =  iConfig.getParameter< edm::InputTag >("MCLeptonsEnergy");
    MCLeptonsPdgId_ =  iConfig.getParameter< edm::InputTag >("MCLeptonsPdgId");
    MCLeptonsMotherId_ =  iConfig.getParameter< edm::InputTag >("MCLeptonsMotherId");
    
    MCNeutrinosEta_ =  iConfig.getParameter< edm::InputTag >("MCNeutrinosEta");
    MCNeutrinosPt_ =  iConfig.getParameter< edm::InputTag >("MCNeutrinosPt");
    MCNeutrinosPhi_ =  iConfig.getParameter< edm::InputTag >("MCNeutrinosPhi");
    MCNeutrinosEnergy_ =  iConfig.getParameter< edm::InputTag >("MCNeutrinosEnergy");
    MCNeutrinosPdgId_ =  iConfig.getParameter< edm::InputTag >("MCNeutrinosPdgId");
    MCNeutrinosMotherId_ =  iConfig.getParameter< edm::InputTag >("MCNeutrinosMotherId");

    //Top
    MCTopsEta_ =  iConfig.getParameter< edm::InputTag >("MCTopsEta");
    MCTopsPt_ =  iConfig.getParameter< edm::InputTag >("MCTopsPt");
    MCTopsPhi_ =  iConfig.getParameter< edm::InputTag >("MCTopsPhi");
    MCTopsEnergy_ =  iConfig.getParameter< edm::InputTag >("MCTopsEnergy");
    MCTopsPdgId_ =  iConfig.getParameter< edm::InputTag >("MCTopsPdgId");
    MCTopsMotherId_ =  iConfig.getParameter< edm::InputTag >("MCTopsMotherId");

    MCTopBQuarksEta_ =  iConfig.getParameter< edm::InputTag >("MCTopBQuarksEta");
    MCTopBQuarksPt_ =  iConfig.getParameter< edm::InputTag >("MCTopBQuarksPt");
    MCTopBQuarksPhi_ =  iConfig.getParameter< edm::InputTag >("MCTopBQuarksPhi");
    MCTopBQuarksEnergy_ =  iConfig.getParameter< edm::InputTag >("MCTopBQuarksEnergy");
    MCTopBQuarksPdgId_ =  iConfig.getParameter< edm::InputTag >("MCTopBQuarksPdgId");
    MCTopBQuarksMotherId_ =  iConfig.getParameter< edm::InputTag >("MCTopBQuarksMotherId");

    MCTopLeptonsEta_ =  iConfig.getParameter< edm::InputTag >("MCTopLeptonsEta");
    MCTopLeptonsPt_ =  iConfig.getParameter< edm::InputTag >("MCTopLeptonsPt");
    MCTopLeptonsPhi_ =  iConfig.getParameter< edm::InputTag >("MCTopLeptonsPhi");
    MCTopLeptonsEnergy_ =  iConfig.getParameter< edm::InputTag >("MCTopLeptonsEnergy");
    MCTopLeptonsPdgId_ =  iConfig.getParameter< edm::InputTag >("MCTopLeptonsPdgId");
    MCTopLeptonsMotherId_ =  iConfig.getParameter< edm::InputTag >("MCTopLeptonsMotherId");

    MCTopNeutrinosEta_ =  iConfig.getParameter< edm::InputTag >("MCTopNeutrinosEta");
    MCTopNeutrinosPt_ =  iConfig.getParameter< edm::InputTag >("MCTopNeutrinosPt");
    MCTopNeutrinosPhi_ =  iConfig.getParameter< edm::InputTag >("MCTopNeutrinosPhi");
    MCTopNeutrinosEnergy_ =  iConfig.getParameter< edm::InputTag >("MCTopNeutrinosEnergy");
    MCTopNeutrinosPdgId_ =  iConfig.getParameter< edm::InputTag >("MCTopNeutrinosPdgId");
    MCTopNeutrinosMotherId_ =  iConfig.getParameter< edm::InputTag >("MCTopNeutrinosMotherId");
    
    MCTopQuarksEta_ =  iConfig.getParameter< edm::InputTag >("MCTopQuarksEta");
    MCTopQuarksPt_ =  iConfig.getParameter< edm::InputTag >("MCTopQuarksPt");
    MCTopQuarksPhi_ =  iConfig.getParameter< edm::InputTag >("MCTopQuarksPhi");
    MCTopQuarksEnergy_ =  iConfig.getParameter< edm::InputTag >("MCTopQuarksEnergy");
    MCTopQuarksPdgId_ =  iConfig.getParameter< edm::InputTag >("MCTopQuarksPdgId");
    MCTopQuarksMotherId_ =  iConfig.getParameter< edm::InputTag >("MCTopQuarksMotherId");

    MCTopQuarkBarsEta_ =  iConfig.getParameter< edm::InputTag >("MCTopQuarkBarsEta");
    MCTopQuarkBarsPt_ =  iConfig.getParameter< edm::InputTag >("MCTopQuarkBarsPt");
    MCTopQuarkBarsPhi_ =  iConfig.getParameter< edm::InputTag >("MCTopQuarkBarsPhi");
    MCTopQuarkBarsEnergy_ =  iConfig.getParameter< edm::InputTag >("MCTopQuarkBarsEnergy");
    MCTopQuarkBarsPdgId_ =  iConfig.getParameter< edm::InputTag >("MCTopQuarkBarsPdgId");
    MCTopQuarkBarsMotherId_ =  iConfig.getParameter< edm::InputTag >("MCTopQuarkBarsMotherId");
    

    MCTopWsEta_ =  iConfig.getParameter< edm::InputTag >("MCTopWsEta");
    MCTopWsPt_ =  iConfig.getParameter< edm::InputTag >("MCTopWsPt");
    MCTopWsPhi_ =  iConfig.getParameter< edm::InputTag >("MCTopWsPhi");
    MCTopWsEnergy_ =  iConfig.getParameter< edm::InputTag >("MCTopWsEnergy");
    MCTopWsPdgId_ =  iConfig.getParameter< edm::InputTag >("MCTopWsPdgId");
    MCTopWsMotherId_ =  iConfig.getParameter< edm::InputTag >("MCTopWsMotherId");
    MCTopWsDauOneId_ =  iConfig.getParameter< edm::InputTag >("MCTopWsDauOneId");

    string season = "Fall12";
    season = dataPUFile_;
    
    string distr = "pileUpDistr" + season + ".root";
    if (doPU_)
    {
        LumiWeights_ = edm::LumiReWeighting(distr,
                                            "pileUpData.root",
                                            std::string("pileup"),
                                            std::string("pileup"));
        LumiWeightsUp_ = edm::LumiReWeighting(distr,
                                              "pileUpDataUp.root",
                                              std::string("pileup"),
                                              std::string("pileup"));
        LumiWeightsDown_ = edm::LumiReWeighting(distr,
                                                "pileUpDataDown.root",
                                                std::string("pileup"),
                                                std::string("pileup"));
    }

    Service<TFileService> fs;
    
    systematics.insert(systematics.begin(), "noSyst");
    
    std::vector<std::string> all_syst = systematics;


    TFileDirectory SingleTopSystematics = fs->mkdir( "systematics_histograms" );
    TFileDirectory SingleTopTrees = fs->mkdir( "systematics_trees" );
    

    for (size_t i = 0; i < all_syst.size(); ++i)
      {
	string syst = all_syst[i];
	//string treenameMCTruth = (channel + "_MCTruth_" + syst);
	//treesMCTruth = new TTree(treenameMCTruth.c_str(), treenameMCTruth.c_str());
	string treenameMCTruth = (channel + "_MCTruth_" + syst);
	treesMCTruth[syst] = new TTree(treenameMCTruth.c_str(), treenameMCTruth.c_str());
	
        if (doJetTrees_)//doingNJet trees
	  {
            string treenameJets = (channel + "_NJets_" + syst);
            treesNJets[syst] = new TTree(treenameJets.c_str(), treenameJets.c_str());
	    
	    
            //Create INT branches first
            treesNJets[syst]->Branch("charge", &chargeTree);
            treesNJets[syst]->Branch("runid", &runTree);
            treesNJets[syst]->Branch("lumiid", &lumiTree);
            treesNJets[syst]->Branch("eventid", &eventTree);
            treesNJets[syst]->Branch("weight", &weightTree);
            treesNJets[syst]->Branch("eventFlavour", &eventFlavourTree);
            treesNJets[syst]->Branch("nJ", &nJ);
            treesNJets[syst]->Branch("nJNoPU", &nJNoPU);
            treesNJets[syst]->Branch("nJCentral", &nJCentral);
            treesNJets[syst]->Branch("nJCentralNoPU", &nJCentralNoPU);
            treesNJets[syst]->Branch("nJForward", &nJForward);
            treesNJets[syst]->Branch("nJForwardNoPU", &nJForwardNoPU);
            treesNJets[syst]->Branch("nVertices", &nVertices);
            treesNJets[syst]->Branch("nGoodVertices", &npv);
            treesNJets[syst]->Branch("nTCHPT", &ntchpt_tags);
            treesNJets[syst]->Branch("nCSVT", &ncsvt_tags);
            treesNJets[syst]->Branch("nCSVL", &ncsvm_tags);
            treesNJets[syst]->Branch("secondJetFlavour", &secondJetFlavourTree);
            treesNJets[syst]->Branch("firstJetFlavour", &firstJetFlavourTree);
            treesNJets[syst]->Branch("thirdJetFlavour", &thirdJetFlavourTree);
	    
	    
            //Now create DOUBLE branches
            treesNJets[syst]->Branch("w1TCHPT", &w1TCHPT);
            treesNJets[syst]->Branch("w2TCHPT", &w2TCHPT);
            treesNJets[syst]->Branch("w1CSVT", &w1CSVT);
            treesNJets[syst]->Branch("w2CSVT", &w2CSVT);
            treesNJets[syst]->Branch("w1CSVL", &w1CSVM);
            treesNJets[syst]->Branch("w2CSVL", &w2CSVM);
            treesNJets[syst]->Branch("PUWeight", &PUWeightTree);
            treesNJets[syst]->Branch("leptonPt", &lepPt);
            treesNJets[syst]->Branch("leptonEta", &lepEta);
            treesNJets[syst]->Branch("leptonE", &lepE);
            treesNJets[syst]->Branch("leptonPhi", &lepPhi);
            treesNJets[syst]->Branch("leptonDeltaCorrectedRelIso", &lepDeltaCorrectedRelIso);
            treesNJets[syst]->Branch("leptonRhoCorrectedRelIso", &lepRhoCorrectedRelIso);
            treesNJets[syst]->Branch("leptonSF", &lepSF);
            treesNJets[syst]->Branch("leptonSFB", &lepSFB);
            treesNJets[syst]->Branch("leptonSFC", &lepSFC);
            treesNJets[syst]->Branch("leptonSFD", &lepSFD);
            treesNJets[syst]->Branch("ID", &electronID);
            treesNJets[syst]->Branch("MVAID", &leptonMVAID);
	    //            treesNJets[syst]->Branch("lepNH", &leptonNHits);
            treesNJets[syst]->Branch("mtwMass", &mtwMassTree);
            treesNJets[syst]->Branch("metPt", &metPt);
            treesNJets[syst]->Branch("metPhi", &metPhi);
            treesNJets[syst]->Branch("HT", &HT);
            treesNJets[syst]->Branch("H", &H);
            treesNJets[syst]->Branch("firstJetPt", &firstJetPt);
            treesNJets[syst]->Branch("firstJetEta", &firstJetEta);
            treesNJets[syst]->Branch("firstJetPhi", &firstJetPhi);
            treesNJets[syst]->Branch("firstJetE", &firstJetE);
	    // treesNJets[syst]->Branch("firstJetBtag", &firstJetBtag);
            treesNJets[syst]->Branch("thirdJetPt", &thirdJetPt);
            treesNJets[syst]->Branch("thirdJetEta", &thirdJetEta);
            treesNJets[syst]->Branch("thirdJetPhi", &thirdJetPhi);
            treesNJets[syst]->Branch("thirdJetE", &thirdJetE);
	    //  treesNJets[syst]->Branch("thirdJetBtag", &thirdJetBtag);
            treesNJets[syst]->Branch("looseJetPt", &looseJetPt);
            treesNJets[syst]->Branch("looseJetEta", &looseJetEta);
            treesNJets[syst]->Branch("looseJetPhi", &looseJetPhi);
            treesNJets[syst]->Branch("looseJetE", &looseJetE);
	    // treesNJets[syst]->Branch("looseJetBtag", &looseJetBtag);
            treesNJets[syst]->Branch("secondJetPt", &secondJetPt);
            treesNJets[syst]->Branch("secondJetEta", &secondJetEta);
            treesNJets[syst]->Branch("secondJetPhi", &secondJetPhi);
            treesNJets[syst]->Branch("secondJetE", &secondJetE);
            //treesNJets[syst]->Branch("secondJetBtag", &secondJetBtag);
            treesNJets[syst]->Branch("bJetPt", &bJetPt);
            treesNJets[syst]->Branch("fJetPt", &fJetPt);
            treesNJets[syst]->Branch("fJetEta", &fJetEta);
            treesNJets[syst]->Branch("bJetEta", &bJetEta);
            treesNJets[syst]->Branch("fJetPUID", &fJetPUID);
            treesNJets[syst]->Branch("fJetPUWP", &fJetPUWP);
            treesNJets[syst]->Branch("isQCD", &isQCDTree);
            //58 lines
            treesNJets[syst]->Branch("fJetBeta", &fJetBeta);
            treesNJets[syst]->Branch("fJetDZ", &fJetDZ);
            treesNJets[syst]->Branch("fJetRMS", &fJetRMS);
	    
            treesNJets[syst]->Branch("bJetBeta", &bJetBeta);
            treesNJets[syst]->Branch("bJetDZ", &bJetDZ);
            treesNJets[syst]->Branch("bJetRMS", &bJetRMS);
            
            treesNJets[syst]->Branch("nJLoose", &nJLoose);
            treesNJets[syst]->Branch("nJLooseCentral", &nJLooseCentral);
            treesNJets[syst]->Branch("nJLooseForward", &nJLooseForward);
            treesNJets[syst]->Branch("nJLooseMBTag", &nJLooseMBTag);
	    
	    
	    if(addPDFToNJets){
	      for (int p = 1; p <= 52; ++p)
		{
		  stringstream w_n;
		  w_n << p;
		  treesNJets[syst]->Branch(("PDFWeight" + w_n.str()).c_str(), &pdf_weights[p - 1]);
		}
	      
	      treesNJets[syst]->Branch("PDFWeight_MSTW", &pdf_weights_mstw);
	      treesNJets[syst]->Branch("PDFWeight_NNPDF21", &pdf_weights_nnpdf21);
	      treesNJets[syst]->Branch("PDFWeight_GJR_FV", &pdf_weights_gjr_fv);
	      treesNJets[syst]->Branch("PDFWeight_GJR_FF", &pdf_weights_gjr_ff);
	      treesNJets[syst]->Branch("PDFWeight_GJR_FDIS", &pdf_weights_gjr_fdis);
	      treesNJets[syst]->Branch("PDFWeight_HERAPDF", &pdf_weights_alekhin);
	    }
	    
	  }
	
        for (int bj = 0; bj <= 5; ++bj)
	  {
	    
            stringstream tags;
            int ntagss = bj;
            if (ntagss > 2 )
	      {
		
                ntagss = ntagss - 3;
                tags << ntagss;
                tags <<  "T_QCD";
	      }
            else
	      {
                tags << ntagss << "T";
	      }
	    //2J1T
	    
            string treename = (channel + "_2J_" + tags.str() + "_" + syst);
	    
            trees2J[bj][syst] = new TTree(treename.c_str(), treename.c_str());
	    
            //quantities for the analysis
	    
            trees2J[bj][syst]->Branch("eta", &etaTree);
            trees2J[bj][syst]->Branch("costhetalj", &cosTree);
            trees2J[bj][syst]->Branch("costhetalbl", &cosBLTree);

            trees2J[bj][syst]->Branch("costhetalj1", &cos1Tree);
            trees2J[bj][syst]->Branch("costhetalbl1", &cos1BLTree);

            trees2J[bj][syst]->Branch("costhetalj2", &cos2Tree);
            trees2J[bj][syst]->Branch("costhetalbl2", &cos2BLTree);
	    
	    //  trees2J[bj][syst]->Branch("costhetalj_best", &cosTree_best);
	    //   trees2J[bj][syst]->Branch("costhetalbl_best", &cosBLTree_best);
	    
            
	    trees2J[bj][syst]->Branch("Mlb1",&Mlb1Tree);
	    trees2J[bj][syst]->Branch("Mlb2",&Mlb2Tree);
	    trees2J[bj][syst]->Branch("b1b2Mass",&Mb1b2Tree);
	    trees2J[bj][syst]->Branch("b1b2Pt",&pTb1b2Tree);
	    
            trees2J[bj][syst]->Branch("mtwMass", &mtwMassTree);
	    
            trees2J[bj][syst]->Branch("charge", &chargeTree);
            trees2J[bj][syst]->Branch("runid", &runTree);
            trees2J[bj][syst]->Branch("lumiid", &lumiTree);
            trees2J[bj][syst]->Branch("eventid", &eventTree);
            trees2J[bj][syst]->Branch("weight", &weightTree);
	    
            trees2J[bj][syst]->Branch("totalWeight", &totalWeightTree);
	    
            trees2J[bj][syst]->Branch("bWeight", &bWeightTree);
	    
            //Systematics b weights
            trees2J[bj][syst]->Branch("bWeightBTagUp", &bWeightTreeBTagUp);
            trees2J[bj][syst]->Branch("bWeightBTagDown", &bWeightTreeBTagDown);
	    
            trees2J[bj][syst]->Branch("bWeightMisTagUp", &bWeightTreeMisTagUp);
            trees2J[bj][syst]->Branch("bWeightMisTagDown", &bWeightTreeMisTagDown);
	    
            //Systematics pile up weights
            trees2J[bj][syst]->Branch("PUWeight", &PUWeightTree);
	    
            trees2J[bj][syst]->Branch("PUWeightPUUp", &PUWeightTreePUUp);
            trees2J[bj][syst]->Branch("PUWeightPUDown", &PUWeightTreePUDown);
	    //Systematics toppt reweighting weights  
	    if(doTopPtReweighting_){
	      trees2J[bj][syst]->Branch("topPtReweightMCTruth", &topPtReweightMCTruth);
	      trees2J[bj][syst]->Branch("topPtReweight", &topPtReweight);
          trees2J[bj][syst]->Branch("topPtReweightMCTruthUp", &topPtReweightMCTruthUp);
	      trees2J[bj][syst]->Branch("topPtReweightUp", &topPtReweightUp);
		  trees2J[bj][syst]->Branch("topPtReweightMCTruthDown", &topPtReweightMCTruthDown);
	      trees2J[bj][syst]->Branch("topPtReweightDown", &topPtReweightDown);

	    }
            //other observables
            trees2J[bj][syst]->Branch("leptonPt", &lepPt);
            trees2J[bj][syst]->Branch("leptonEta", &lepEta);
            trees2J[bj][syst]->Branch("leptonPhi", &lepPhi);
            trees2J[bj][syst]->Branch("leptonE", &lepE);
            trees2J[bj][syst]->Branch("leptonDeltaCorrectedRelIso", &lepDeltaCorrectedRelIso);
            trees2J[bj][syst]->Branch("leptonRhoCorrectedRelIso", &lepRhoCorrectedRelIso);
	    
            trees2J[bj][syst]->Branch("leptonSF", &lepSF);
            trees2J[bj][syst]->Branch("leptonSFB", &lepSFB);
            trees2J[bj][syst]->Branch("leptonSFC", &lepSFC);
            trees2J[bj][syst]->Branch("leptonSFD", &lepSFD);
	    
            trees2J[bj][syst]->Branch("leptonSFIDUp", &lepSFIDUp);
            trees2J[bj][syst]->Branch("leptonSFIDUpB", &lepSFIDUpB);
            trees2J[bj][syst]->Branch("leptonSFIDUpC", &lepSFIDUpC);
            trees2J[bj][syst]->Branch("leptonSFIDUpD", &lepSFIDUpD);
	    
            trees2J[bj][syst]->Branch("leptonSFIDDown", &lepSFIDDown);
            trees2J[bj][syst]->Branch("leptonSFIDDownB", &lepSFIDDownB);
            trees2J[bj][syst]->Branch("leptonSFIDDownC", &lepSFIDDownC);
            trees2J[bj][syst]->Branch("leptonSFIDDownD", &lepSFIDDownD);
	    
	    trees2J[bj][syst]->Branch("leptonSFIsoUp", &lepSFIsoUp);
            trees2J[bj][syst]->Branch("leptonSFIsoUpB", &lepSFIsoUpB);
            trees2J[bj][syst]->Branch("leptonSFIsoUpC", &lepSFIsoUpC);
            trees2J[bj][syst]->Branch("leptonSFIsoUpD", &lepSFIsoUpD);
	    
            trees2J[bj][syst]->Branch("leptonSFIsoDown", &lepSFIsoDown);
            trees2J[bj][syst]->Branch("leptonSFIsoDownB", &lepSFIsoDownB);
            trees2J[bj][syst]->Branch("leptonSFIsoDownC", &lepSFIsoDownC);
            trees2J[bj][syst]->Branch("leptonSFIsoDownD", &lepSFIsoDownD);
	    
            trees2J[bj][syst]->Branch("leptonSFTrigUp", &lepSFTrigUp);
            trees2J[bj][syst]->Branch("leptonSFTrigUpB", &lepSFTrigUpB);
            trees2J[bj][syst]->Branch("leptonSFTrigUpC", &lepSFTrigUpC);
            trees2J[bj][syst]->Branch("leptonSFTrigUpD", &lepSFTrigUpD);
	    
            trees2J[bj][syst]->Branch("leptonSFTrigDown", &lepSFTrigDown);
            trees2J[bj][syst]->Branch("leptonSFTrigDownB", &lepSFTrigDownB);
            trees2J[bj][syst]->Branch("leptonSFTrigDownC", &lepSFTrigDownC);
            trees2J[bj][syst]->Branch("leptonSFTrigDownD", &lepSFTrigDownD);
	    
	    
            trees2J[bj][syst]->Branch("fJetPt", &fJetPt);
            trees2J[bj][syst]->Branch("fJetE", &fJetE);
            trees2J[bj][syst]->Branch("fJetEta", &fJetEta);
            trees2J[bj][syst]->Branch("fJetPhi", &fJetPhi);
            trees2J[bj][syst]->Branch("fJetBtag", &fJetBTag);
            trees2J[bj][syst]->Branch("fJetFlavour", &fJetFlavourTree);
            trees2J[bj][syst]->Branch("fJetPUID", &fJetPUID);
            trees2J[bj][syst]->Branch("fJetPUWP", &fJetPUWP);
	    
            trees2J[bj][syst]->Branch("fJetBeta", &fJetBeta);
            trees2J[bj][syst]->Branch("fJetDZ", &fJetDZ);
            trees2J[bj][syst]->Branch("fJetRMS", &fJetRMS);
	    
            trees2J[bj][syst]->Branch("bJetBeta", &bJetBeta);
            trees2J[bj][syst]->Branch("bJetDZ", &bJetDZ);
            trees2J[bj][syst]->Branch("bJetRMS", &bJetRMS);
	    
            trees2J[bj][syst]->Branch("bJetPt", &bJetPt);
            trees2J[bj][syst]->Branch("bJetE", &bJetE);
            trees2J[bj][syst]->Branch("bJetEta", &bJetEta);
            trees2J[bj][syst]->Branch("bJetPhi", &bJetPhi);
            trees2J[bj][syst]->Branch("bJetBtag", &bJetBTag);
            trees2J[bj][syst]->Branch("bJetFlavour", &bJetFlavourTree);
            trees2J[bj][syst]->Branch("bJetPUID", &bJetPUID);
            trees2J[bj][syst]->Branch("bJetPUWP", &bJetPUWP);
	    
            //trees2J[bj][syst]->Branch("bestJetFlavour", &bestJetFlavourTree);
	    // trees2J[bj][syst]->Branch("bJetIsbest", &bJetIsbest);
	    
            trees2J[bj][syst]->Branch("firstJetPt", &firstJetPt);
            trees2J[bj][syst]->Branch("firstJetEta", &firstJetEta);
            trees2J[bj][syst]->Branch("firstJetPhi", &firstJetPhi);
            trees2J[bj][syst]->Branch("firstJetE", &firstJetE);
            trees2J[bj][syst]->Branch("firstJetBtag", &firstJetBTag);
            trees2J[bj][syst]->Branch("firstJetFlavour", &firstJetFlavourTree);
	    
            trees2J[bj][syst]->Branch("secondJetPt", &secondJetPt);
            trees2J[bj][syst]->Branch("secondJetEta", &secondJetEta);
            trees2J[bj][syst]->Branch("secondJetPhi", &secondJetPhi);
            trees2J[bj][syst]->Branch("secondJetE", &secondJetE);
            trees2J[bj][syst]->Branch("secondJetBtag", &secondJetBTag);
            trees2J[bj][syst]->Branch("secondJetFlavour", &secondJetFlavourTree);
	    
            trees2J[bj][syst]->Branch("looseJetPt", &looseJetPt);
            trees2J[bj][syst]->Branch("looseJetEta", &looseJetEta);
            trees2J[bj][syst]->Branch("looseJetPhi", &looseJetPhi);
            trees2J[bj][syst]->Branch("looseJetE", &looseJetE);
            trees2J[bj][syst]->Branch("looseJetBtag", &looseJetBTag);
            trees2J[bj][syst]->Branch("looseJetFlavour", &looseJetFlavourTree);
	    
            trees2J[bj][syst]->Branch("bJet1Pt",&bJet1Pt);
	    trees2J[bj][syst]->Branch("bJet1E",&bJet1E);
	    trees2J[bj][syst]->Branch("bJet1Eta",&bJet1Eta);
	    trees2J[bj][syst]->Branch("bJet1Phi",&bJet1Phi);
            trees2J[bj][syst]->Branch("bJet1Btag", &bJet1BTag);
	    trees2J[bj][syst]->Branch("bJet1Flavour",&bJet1Flavour);
	    
	    trees2J[bj][syst]->Branch("bJet2Pt",&bJet2Pt);
	    trees2J[bj][syst]->Branch("bJet2E",&bJet2E);
	    trees2J[bj][syst]->Branch("bJet2Eta",&bJet2Eta);
	    trees2J[bj][syst]->Branch("bJet2Phi",&bJet2Phi);
            trees2J[bj][syst]->Branch("bJet2Btag", &bJet2BTag);
	    trees2J[bj][syst]->Branch("bJet2Flavour",&bJet2Flavour);
	    
	    trees2J[bj][syst]->Branch("bJetDecayPt",&bJetPt);
	    trees2J[bj][syst]->Branch("bJetDecayE",&bJetDecayE);
	    trees2J[bj][syst]->Branch("bJetDecayEta",&bJetDecayEta);
	    trees2J[bj][syst]->Branch("bJetDecayPhi",&bJetDecayPhi);
	    trees2J[bj][syst]->Branch("bJetDecayBtag", &bJetDecayBTag);
	    trees2J[bj][syst]->Branch("bJetDecayFlavour",&bJetDecayFlavour);
	    
	    trees2J[bj][syst]->Branch("bJetRecoilPt",&bJetRecoilPt);
	    trees2J[bj][syst]->Branch("bJetRecoilE",&bJetRecoilE);
	    trees2J[bj][syst]->Branch("bJetRecoilEta",&bJetRecoilEta);
	    trees2J[bj][syst]->Branch("bJetRecoilPhi",&bJetRecoilPhi);
	    trees2J[bj][syst]->Branch("bJetRecoilBtag", &bJetRecoilBTag);
	    trees2J[bj][syst]->Branch("bJetRecoilFlavour",&bJetRecoilFlavour);
	    
	    trees2J[bj][syst]->Branch("nJLoose",&nJLoose);
	    //	    trees2J[bj][syst]->Branch("nJ",&nJ);
	    trees2J[bj][syst]->Branch("nJLooseCentral",&nJLooseCentral);
	    trees2J[bj][syst]->Branch("nJLooseForward",&nJLooseForward);
	    trees2J[bj][syst]->Branch("nJLooseMBTag",&nJLooseMBTag);
	    
            
	    
            trees2J[bj][syst]->Branch("eventFlavour", &eventFlavourTree);
	    
            trees2J[bj][syst]->Branch("metPt", &metPt);
            trees2J[bj][syst]->Branch("metPhi", &metPhi);
	    
            trees2J[bj][syst]->Branch("HT", &HT);
      	    trees2J[bj][syst]->Branch("H", &H);
	    
	    
            trees2J[bj][syst]->Branch("topMass", &topMassTree);
            trees2J[bj][syst]->Branch("top1Mass", &top1MassTree);
            trees2J[bj][syst]->Branch("top2Mass", &top2MassTree);
            trees2J[bj][syst]->Branch("topMtw", &topMtwTree);
	    
            trees2J[bj][syst]->Branch("topPt"  , &topPt);
            trees2J[bj][syst]->Branch("topPhi" , &topPhi);
            trees2J[bj][syst]->Branch("topEta" , &topEta);
            trees2J[bj][syst]->Branch("topE"   , &topE);

            trees2J[bj][syst]->Branch("top1Pt"  , &top1Pt);
            trees2J[bj][syst]->Branch("top1Phi" , &top1Phi);
            trees2J[bj][syst]->Branch("top1Eta" , &top1Eta);
            trees2J[bj][syst]->Branch("top1E"   , &top1E);

            trees2J[bj][syst]->Branch("top2Pt"  , &top2Pt);
            trees2J[bj][syst]->Branch("top2Phi" , &top2Phi);
            trees2J[bj][syst]->Branch("top2Eta" , &top2Eta);
            trees2J[bj][syst]->Branch("top2E"   , &top2E);
            
	    
            trees2J[bj][syst]->Branch("ID", &electronID);
            trees2J[bj][syst]->Branch("MVAID", &leptonMVAID);
	    //            trees2J[bj][syst]->Branch("lepNH", &leptonNHits);
            trees2J[bj][syst]->Branch("nVertices", &nVertices);
            trees2J[bj][syst]->Branch("nGoodVertices", &npv);
	    
            trees2J[bj][syst]->Branch("totalEnergy", &totalEnergy);
            trees2J[bj][syst]->Branch("totalMomentum", &totalMomentum);
	    
            trees2J[bj][syst]->Branch("lowBTag", &lowBTagTree);
            trees2J[bj][syst]->Branch("highBTag", &highBTagTree);
	    
	    if(doMCTruth_ && (bj == 1 || bj == 2) && syst == "noSyst" ){
	      
	      for (int p = 1; p <= 2; ++p)
		{
		  stringstream w_n;
		  w_n << p;
		  TString num( w_n.str() );
		  num = "_"+num+"_";
		  
		  trees2J[bj][syst]->Branch("nMCTruthLeptons", &nMCTruthLeptons);
		  
		  trees2J[bj][syst]->Branch("MCTop"+num+"Pt", &MCTopsPtVec[p-1]);
		  trees2J[bj][syst]->Branch("MCTop"+num+"Phi", &MCTopsPhiVec[p-1]);
		  trees2J[bj][syst]->Branch("MCTop"+num+"Eta", &MCTopsEtaVec[p-1]);
		  trees2J[bj][syst]->Branch("MCTop"+num+"E", &MCTopsEnergyVec[p-1]);
		  trees2J[bj][syst]->Branch("MCTop"+num+"PdgId", &MCTopsPdgIdVec[p-1]);
		  trees2J[bj][syst]->Branch("MCTop"+num+"MotherId", &MCTopsMotherIdVec[p-1]);
		  
		  trees2J[bj][syst]->Branch("MCTopLepton"+num+"Pt", &MCTopLeptonsPtVec[p-1]);
		  trees2J[bj][syst]->Branch("MCTopLepton"+num+"Phi", &MCTopLeptonsPhiVec[p-1]);
		  trees2J[bj][syst]->Branch("MCTopLepton"+num+"Eta", &MCTopLeptonsEtaVec[p-1]);
		  trees2J[bj][syst]->Branch("MCTopLepton"+num+"E", &MCTopLeptonsEnergyVec[p-1]);
		  trees2J[bj][syst]->Branch("MCTopLepton"+num+"PdgId", &MCTopLeptonsPdgIdVec[p-1]);
		  trees2J[bj][syst]->Branch("MCTopLepton"+num+"MotherId", &MCTopLeptonsMotherIdVec[p-1]);
		  
		  trees2J[bj][syst]->Branch("MCTopNeutrino"+num+"Pt", &MCTopNeutrinosPtVec[p-1]);
		  trees2J[bj][syst]->Branch("MCTopNeutrino"+num+"Phi", &MCTopNeutrinosPhiVec[p-1]);
		  trees2J[bj][syst]->Branch("MCTopNeutrino"+num+"Eta", &MCTopNeutrinosEtaVec[p-1]);
		  trees2J[bj][syst]->Branch("MCTopNeutrino"+num+"E", &MCTopNeutrinosEnergyVec[p-1]);
		  trees2J[bj][syst]->Branch("MCTopNeutrino"+num+"PdgId", &MCTopNeutrinosPdgIdVec[p-1]);
		  trees2J[bj][syst]->Branch("MCTopNeutrino"+num+"MotherId", &MCTopNeutrinosMotherIdVec[p-1]);
		  
		  trees2J[bj][syst]->Branch("MCTopQuark"+num+"Pt", &MCTopQuarksPtVec[p-1]);
		  trees2J[bj][syst]->Branch("MCTopQuark"+num+"Phi", &MCTopQuarksPhiVec[p-1]);
		  trees2J[bj][syst]->Branch("MCTopQuark"+num+"Eta", &MCTopQuarksEtaVec[p-1]);
		  trees2J[bj][syst]->Branch("MCTopQuark"+num+"E", &MCTopQuarksEnergyVec[p-1]);
		  trees2J[bj][syst]->Branch("MCTopQuark"+num+"PdgId", &MCTopQuarksPdgIdVec[p-1]);
		  trees2J[bj][syst]->Branch("MCTopQuark"+num+"MotherId", &MCTopQuarksMotherIdVec[p-1]);
		  
		  trees2J[bj][syst]->Branch("MCTopQuarkBar"+num+"Pt", &MCTopQuarkBarsPtVec[p-1]);
		  trees2J[bj][syst]->Branch("MCTopQuarkBar"+num+"Phi", &MCTopQuarkBarsPhiVec[p-1]);
		  trees2J[bj][syst]->Branch("MCTopQuarkBar"+num+"Eta", &MCTopQuarkBarsEtaVec[p-1]);
		  trees2J[bj][syst]->Branch("MCTopQuarkBar"+num+"E", &MCTopQuarkBarsEnergyVec[p-1]);
		  trees2J[bj][syst]->Branch("MCTopQuarkBar"+num+"PdgId", &MCTopQuarkBarsPdgIdVec[p-1]);
		  trees2J[bj][syst]->Branch("MCTopQuarkBar"+num+"MotherId", &MCTopQuarkBarsMotherIdVec[p-1]);
		  
		  trees2J[bj][syst]->Branch("MCTopBQuark"+num+"Pt", &MCTopBQuarksPtVec[p-1]);
		  trees2J[bj][syst]->Branch("MCTopBQuark"+num+"Phi", &MCTopBQuarksPhiVec[p-1]);
		  trees2J[bj][syst]->Branch("MCTopBQuark"+num+"Eta", &MCTopBQuarksEtaVec[p-1]);
		  trees2J[bj][syst]->Branch("MCTopBQuark"+num+"E", &MCTopBQuarksEnergyVec[p-1]);
		  trees2J[bj][syst]->Branch("MCTopBQuark"+num+"PdgId", &MCTopBQuarksPdgIdVec[p-1]);
		  trees2J[bj][syst]->Branch("MCTopBQuark"+num+"MotherId", &MCTopBQuarksMotherIdVec[p-1]);
		  
		  trees2J[bj][syst]->Branch("MCTopW"+num+"Pt", &MCTopWsPtVec[p-1]);
		  trees2J[bj][syst]->Branch("MCTopW"+num+"Phi", &MCTopWsPhiVec[p-1]);
		  trees2J[bj][syst]->Branch("MCTopW"+num+"Eta", &MCTopWsEtaVec[p-1]);
		  trees2J[bj][syst]->Branch("MCTopW"+num+"E", &MCTopWsEnergyVec[p-1]);
		  trees2J[bj][syst]->Branch("MCTopW"+num+"PdgId", &MCTopWsPdgIdVec[p-1]);
		  trees2J[bj][syst]->Branch("MCTopW"+num+"DauOneId", &MCTopWsDauOneIdVec[p-1]);
		  
		}
	      
	      
	      for (int p = 1; p <= 12; ++p)
		{
		  stringstream w_n;
		  w_n << p;
		  TString num( w_n.str() );
		  num = "_"+num+"_";
		  
		  trees2J[bj][syst]->Branch("MCQuark"+num+"Pt", &MCQuarksPtVec[p-1]);
		  trees2J[bj][syst]->Branch("MCQuark"+num+"Phi", &MCQuarksPhiVec[p-1]);
		  trees2J[bj][syst]->Branch("MCQuark"+num+"Eta", &MCQuarksEtaVec[p-1]);
		  trees2J[bj][syst]->Branch("MCQuark"+num+"E", &MCQuarksEnergyVec[p-1]);
		  trees2J[bj][syst]->Branch("MCQuark"+num+"PdgId", &MCQuarksPdgIdVec[p-1]);
		  trees2J[bj][syst]->Branch("MCQuark"+num+"MotherId", &MCQuarksMotherIdVec[p-1]);
		}
	      
	      for (int p = 1; p <= 4; ++p)
		{
		  stringstream w_n;
		  w_n << p;
		  TString num( w_n.str() );
		  num = "_"+num+"_";
		  
		  trees2J[bj][syst]->Branch("MCBQuark"+num+"Pt", &MCBQuarksPtVec[p-1]);
		  trees2J[bj][syst]->Branch("MCBQuark"+num+"Phi", &MCBQuarksPhiVec[p-1]);
		  trees2J[bj][syst]->Branch("MCBQuark"+num+"Eta", &MCBQuarksEtaVec[p-1]);
		  trees2J[bj][syst]->Branch("MCBQuark"+num+"E", &MCBQuarksEnergyVec[p-1]);
		  trees2J[bj][syst]->Branch("MCBQuark"+num+"PdgId", &MCBQuarksPdgIdVec[p-1]);
		  trees2J[bj][syst]->Branch("MCBQuark"+num+"MotherId", &MCBQuarksMotherIdVec[p-1]);
		  
		  trees2J[bj][syst]->Branch("MCLepton"+num+"Pt", &MCLeptonsPtVec[p-1]);
		  trees2J[bj][syst]->Branch("MCLepton"+num+"Phi", &MCLeptonsPhiVec[p-1]);
		  trees2J[bj][syst]->Branch("MCLepton"+num+"Eta", &MCLeptonsEtaVec[p-1]);
		  trees2J[bj][syst]->Branch("MCLepton"+num+"E", &MCLeptonsEnergyVec[p-1]);
		  trees2J[bj][syst]->Branch("MCLepton"+num+"PdgId", &MCLeptonsPdgIdVec[p-1]);
		  trees2J[bj][syst]->Branch("MCLepton"+num+"MotherId", &MCLeptonsMotherIdVec[p-1]);
		  
		  trees2J[bj][syst]->Branch("MCNeutrino"+num+"Pt", &MCNeutrinosPtVec[p-1]);
		  trees2J[bj][syst]->Branch("MCNeutrino"+num+"Phi", &MCNeutrinosPhiVec[p-1]);
		  trees2J[bj][syst]->Branch("MCNeutrino"+num+"Eta", &MCNeutrinosEtaVec[p-1]);
		  trees2J[bj][syst]->Branch("MCNeutrino"+num+"E", &MCNeutrinosEnergyVec[p-1]);
		  trees2J[bj][syst]->Branch("MCNeutrino"+num+"PdgId", &MCNeutrinosPdgIdVec[p-1]);
		  trees2J[bj][syst]->Branch("MCNeutrino"+num+"MotherId", &MCNeutrinosMotherIdVec[p-1]);
		}
	    }	    
	    
	    for (int p = 1; p <= 52; ++p)
	      {
		stringstream w_n;
                w_n << p;
                trees2J[bj][syst]->Branch(("PDFWeight" + w_n.str()).c_str(), &pdf_weights[p - 1]);
	      }
	    
	    trees2J[bj][syst]->Branch("PDFWeight_MSTW", &pdf_weights_mstw);
	    trees2J[bj][syst]->Branch("PDFWeight_NNPDF21", &pdf_weights_nnpdf21);
	    trees2J[bj][syst]->Branch("PDFWeight_GJR_FV", &pdf_weights_gjr_fv);
	    trees2J[bj][syst]->Branch("PDFWeight_GJR_FF", &pdf_weights_gjr_ff);
	    trees2J[bj][syst]->Branch("PDFWeight_GJR_FDIS", &pdf_weights_gjr_fdis);
	    trees2J[bj][syst]->Branch("PDFWeight_HERAPDF", &pdf_weights_alekhin);
	    
	    treename = (channel + "_3J_" + tags.str() + "_" + syst);
	    trees3J[bj][syst] = new TTree(treename.c_str(), treename.c_str());
	    
            //basic quantities
	    
            trees3J[bj][syst]->Branch("eta", &etaTree);
            trees3J[bj][syst]->Branch("costhetalj", &cosTree);
            trees3J[bj][syst]->Branch("costhetalbl", &cosBLTree);

            trees3J[bj][syst]->Branch("costhetalj1", &cos1Tree);
            trees3J[bj][syst]->Branch("costhetalbl1", &cos1BLTree);

            trees3J[bj][syst]->Branch("costhetalj2", &cos2Tree);
            trees3J[bj][syst]->Branch("costhetalbl2", &cos2BLTree);

            trees3J[bj][syst]->Branch("topMass", &topMassTree);
            trees3J[bj][syst]->Branch("top1Mass", &top1MassTree);
            trees3J[bj][syst]->Branch("top2Mass", &top2MassTree);
            trees3J[bj][syst]->Branch("topMtw", &topMtwTree);
	    
	    //    trees3J[bj][syst]->Branch("costhetalj_best", &cosTree_best);
	    //    trees3J[bj][syst]->Branch("costhetalbl_best", &cosBLTree_best);
	    
            
	    trees3J[bj][syst]->Branch("Mlb1",&Mlb1Tree);
	    trees3J[bj][syst]->Branch("Mlb2",&Mlb2Tree);
	    trees3J[bj][syst]->Branch("b1b2Mass",&Mb1b2Tree);
	    trees3J[bj][syst]->Branch("b1b2Pt",&pTb1b2Tree);
	    
            trees3J[bj][syst]->Branch("mtwMass", &mtwMassTree);
	    
            trees3J[bj][syst]->Branch("charge", &chargeTree);
            trees3J[bj][syst]->Branch("runid", &runTree);
            trees3J[bj][syst]->Branch("lumiid", &lumiTree);
            trees3J[bj][syst]->Branch("eventid", &eventTree);
            trees3J[bj][syst]->Branch("weight", &weightTree);
            //trees2J[bj][syst]->Branch("weightTmp",&weightTree);
	    
            trees3J[bj][syst]->Branch("totalWeight", &totalWeightTree);
	    
            //Extra info
	    
            trees3J[bj][syst]->Branch("leptonPt", &lepPt);
            trees3J[bj][syst]->Branch("leptonEta", &lepEta);
            trees3J[bj][syst]->Branch("leptonPhi", &lepPhi);
            trees3J[bj][syst]->Branch("leptonE", &lepE);
            trees3J[bj][syst]->Branch("leptonDeltaCorrectedRelIso", &lepDeltaCorrectedRelIso);
            trees3J[bj][syst]->Branch("leptonRhoCorrectedRelIso", &lepRhoCorrectedRelIso);
	    
            trees3J[bj][syst]->Branch("leptonSF", &lepSF);
            trees3J[bj][syst]->Branch("leptonSFB", &lepSFB);
            trees3J[bj][syst]->Branch("leptonSFC", &lepSFC);
	    trees3J[bj][syst]->Branch("leptonSFD", &lepSFD);
	    
	    
            trees3J[bj][syst]->Branch("fJetPt", &fJetPt);
            trees3J[bj][syst]->Branch("fJetE", &fJetE);
            trees3J[bj][syst]->Branch("fJetEta", &fJetEta);
            trees3J[bj][syst]->Branch("fJetPhi", &fJetPhi);
            trees3J[bj][syst]->Branch("fJetBtag", &fJetBTag);
            trees3J[bj][syst]->Branch("fJetFlavour", &fJetFlavourTree);
            trees3J[bj][syst]->Branch("fJetPUID", &fJetPUID);
            trees3J[bj][syst]->Branch("fJetPUWP", &fJetPUWP);
	    
            trees3J[bj][syst]->Branch("fJetBeta", &fJetBeta);
            trees3J[bj][syst]->Branch("fJetDZ", &fJetDZ);
            trees3J[bj][syst]->Branch("fJetRMS", &fJetRMS);
	    
            trees3J[bj][syst]->Branch("bJetBeta", &bJetBeta);
            trees3J[bj][syst]->Branch("bJetDZ", &bJetDZ);
            trees3J[bj][syst]->Branch("bJetRMS", &bJetRMS);
	    
            trees3J[bj][syst]->Branch("bJetPt", &bJetPt);
            trees3J[bj][syst]->Branch("bJetE", &bJetE);
            trees3J[bj][syst]->Branch("bJetEta", &bJetEta);
            trees3J[bj][syst]->Branch("bJetPhi", &bJetPhi);
            trees3J[bj][syst]->Branch("bJetBtag", &bJetBTag);
            trees3J[bj][syst]->Branch("bJetFlavour", &bJetFlavourTree);
            trees3J[bj][syst]->Branch("bJetPUID", &bJetPUID);
            trees3J[bj][syst]->Branch("bJetPUWP", &bJetPUWP);
	    
            trees3J[bj][syst]->Branch("bJet1Pt",&bJet1Pt);
	    trees3J[bj][syst]->Branch("bJet1E",&bJet1E);
	    trees3J[bj][syst]->Branch("bJet1Eta",&bJet1Eta);
	    trees3J[bj][syst]->Branch("bJet1Phi",&bJet1Phi);
            trees3J[bj][syst]->Branch("bJet1Btag", &bJet1BTag);
	    trees3J[bj][syst]->Branch("bJet1Flavour",&bJet1Flavour);
	    
	    trees3J[bj][syst]->Branch("bJet2Pt",&bJet2Pt);
	    trees3J[bj][syst]->Branch("bJet2E",&bJet2E);
	    trees3J[bj][syst]->Branch("bJet2Eta",&bJet2Eta);
	    trees3J[bj][syst]->Branch("bJet2Phi",&bJet2Phi);
        trees3J[bj][syst]->Branch("bJet2Btag", &bJet2BTag);
	    trees3J[bj][syst]->Branch("bJet2Flavour",&bJet2Flavour);
	    
		
	    // trees3J[bj][syst]->Branch("bestJetFlavour", &bestJetFlavourTree);
	    //  trees3J[bj][syst]->Branch("bJetIsbest", &bJetIsbest);
	    
	    
            trees3J[bj][syst]->Branch("firstJetPt", &firstJetPt);
            trees3J[bj][syst]->Branch("firstJetEta", &firstJetEta);
            trees3J[bj][syst]->Branch("firstJetPhi", &firstJetPhi);
            trees3J[bj][syst]->Branch("firstJetE", &firstJetE);
            trees3J[bj][syst]->Branch("firstJetBtag", &firstJetBTag);
            trees3J[bj][syst]->Branch("firstJetFlavour", &firstJetFlavourTree);
	    
            trees3J[bj][syst]->Branch("secondJetPt", &secondJetPt);
            trees3J[bj][syst]->Branch("secondJetEta", &secondJetEta);
            trees3J[bj][syst]->Branch("secondJetPhi", &secondJetPhi);
            trees3J[bj][syst]->Branch("secondJetE", &secondJetE);
            trees3J[bj][syst]->Branch("secondJetBtag", &secondJetBTag);
            trees3J[bj][syst]->Branch("secondJetFlavour", &secondJetFlavourTree);
	    
            trees3J[bj][syst]->Branch("thirdJetPt", &thirdJetPt);
            trees3J[bj][syst]->Branch("thirdJetEta", &thirdJetEta);
            trees3J[bj][syst]->Branch("thirdJetPhi", &thirdJetPhi);
            trees3J[bj][syst]->Branch("thirdJetE", &thirdJetE);
            trees3J[bj][syst]->Branch("thirdJetBtag", &thirdJetBTag);
            trees3J[bj][syst]->Branch("thirdJetFlavour", &thirdJetFlavourTree);
            
            trees3J[bj][syst]->Branch("looseJetPt", &looseJetPt);
            trees3J[bj][syst]->Branch("looseJetEta", &looseJetEta);
            trees3J[bj][syst]->Branch("looseJetPhi", &looseJetPhi);
            trees3J[bj][syst]->Branch("looseJetE", &looseJetE);
            trees3J[bj][syst]->Branch("looseJetBtag", &looseJetBTag);
            trees3J[bj][syst]->Branch("looseJetFlavour", &looseJetFlavourTree);

	    trees3J[bj][syst]->Branch("bJetDecayPt",&bJetPt);
	    trees3J[bj][syst]->Branch("bJetDecayE",&bJetDecayE);
	    trees3J[bj][syst]->Branch("bJetDecayEta",&bJetDecayEta);
	    trees3J[bj][syst]->Branch("bJetDecayPhi",&bJetDecayPhi);
	    trees3J[bj][syst]->Branch("bJetDecayBtag", &bJetDecayBTag);
	    trees3J[bj][syst]->Branch("bJetDecayFlavour",&bJetDecayFlavour);
	    
	    trees3J[bj][syst]->Branch("bJetRecoilPt",&bJetRecoilPt);
	    trees3J[bj][syst]->Branch("bJetRecoilE",&bJetRecoilE);
	    trees3J[bj][syst]->Branch("bJetRecoilEta",&bJetRecoilEta);
	    trees3J[bj][syst]->Branch("bJetRecoilPhi",&bJetRecoilPhi);
	    trees3J[bj][syst]->Branch("bJetRecoilBtag", &bJetRecoilBTag);
	    trees3J[bj][syst]->Branch("bJetRecoilFlavour",&bJetRecoilFlavour);
	    
            trees3J[bj][syst]->Branch("nJLoose",&nJLoose);
	    //	    trees3J[bj][syst]->Branch("nJ",&nJ);
	    trees3J[bj][syst]->Branch("nJLooseCentral",&nJLooseCentral);
	    trees3J[bj][syst]->Branch("nJLooseForward",&nJLooseForward);
	    trees3J[bj][syst]->Branch("nJLooseMBTag",&nJLooseMBTag);
	    
	    
            trees3J[bj][syst]->Branch("eventFlavour", &eventFlavourTree);
	    
            trees3J[bj][syst]->Branch("HT", &HT);
      	    trees3J[bj][syst]->Branch("H", &H);
	    
            trees3J[bj][syst]->Branch("metPt", &metPt);
            trees3J[bj][syst]->Branch("metPhi", &metPhi);
	    
            trees3J[bj][syst]->Branch("topPt", &topPt);
            trees3J[bj][syst]->Branch("topPhi", &topPhi);
            trees3J[bj][syst]->Branch("topEta", &topEta);
            trees3J[bj][syst]->Branch("topE", &topE);

            trees3J[bj][syst]->Branch("top1Pt", &top1Pt);
            trees3J[bj][syst]->Branch("top1Phi", &top1Phi);
            trees3J[bj][syst]->Branch("top1Eta", &top1Eta);
            trees3J[bj][syst]->Branch("top1E", &top1E);

            trees3J[bj][syst]->Branch("top2Pt", &top2Pt);
            trees3J[bj][syst]->Branch("top2Phi", &top2Phi);
            trees3J[bj][syst]->Branch("top2Eta", &top2Eta);
            trees3J[bj][syst]->Branch("top2E", &top2E);
	    
            trees3J[bj][syst]->Branch("ID", &electronID);
            trees3J[bj][syst]->Branch("MVAID", &leptonMVAID);
            trees3J[bj][syst]->Branch("nVertices", &nVertices);
            trees3J[bj][syst]->Branch("nGoodVertices", &npv);
	    
	    
            trees3J[bj][syst]->Branch("totalEnergy", &totalEnergy);
            trees3J[bj][syst]->Branch("totalMomentum", &totalMomentum);
	    
            trees3J[bj][syst]->Branch("lowBTag", &lowBTagTree);
            trees3J[bj][syst]->Branch("highBTag", &highBTagTree);
            trees3J[bj][syst]->Branch("mediumBTag", &mediumBTagTree);
	    
            //Systematics b weights
	    
            trees3J[bj][syst]->Branch("bWeight", &bWeightTree);
	    
            trees3J[bj][syst]->Branch("bWeightBTagUp", &bWeightTreeBTagUp);
            trees3J[bj][syst]->Branch("bWeightBTagDown", &bWeightTreeBTagDown);
	    
            trees3J[bj][syst]->Branch("bWeightMisTagUp", &bWeightTreeMisTagUp);
            trees3J[bj][syst]->Branch("bWeightMisTagDown", &bWeightTreeMisTagDown);
	    
            //Systematics pile up weights
            trees3J[bj][syst]->Branch("PUWeight", &PUWeightTree);
	    
            trees3J[bj][syst]->Branch("PUWeightPUUp", &PUWeightTreePUUp);
            trees3J[bj][syst]->Branch("PUWeightPUDown", &PUWeightTreePUDown);
	    //Systematics toppt reweighting weights  
	    if(doTopPtReweighting_){
	      trees3J[bj][syst]->Branch("topPtReweightMCTruth", &topPtReweightMCTruth);
	      trees3J[bj][syst]->Branch("topPtReweight", &topPtReweight);
		  trees3J[bj][syst]->Branch("topPtReweightMCTruthUp", &topPtReweightMCTruthUp);
	      trees3J[bj][syst]->Branch("topPtReweightUp", &topPtReweightUp);
		  trees3J[bj][syst]->Branch("topPtReweightMCTruthDown", &topPtReweightMCTruthDown);
	      trees3J[bj][syst]->Branch("topPtReweightDown", &topPtReweightDown);

	    }
            for (int p = 1; p <= 52; ++p)
	      {
                stringstream w_n;
                w_n << p;
                trees3J[bj][syst]->Branch(("PDFWeight" + w_n.str()).c_str(), &pdf_weights[p - 1]);
	      }
	    
	    
            trees3J[bj][syst]->Branch("PDFWeight_MSTW", &pdf_weights_mstw);
	    trees3J[bj][syst]->Branch("PDFWeight_NNPDF21", &pdf_weights_nnpdf21);
	    trees3J[bj][syst]->Branch("PDFWeight_GJR_FV", &pdf_weights_gjr_fv);
	    trees3J[bj][syst]->Branch("PDFWeight_GJR_FF", &pdf_weights_gjr_ff);
	    trees3J[bj][syst]->Branch("PDFWeight_GJR_FDIS", &pdf_weights_gjr_fdis);
	    trees3J[bj][syst]->Branch("PDFWeight_HERAPDF", &pdf_weights_alekhin);
	    
	    
	    treename = (channel + "_4J_" + tags.str() + "_" + syst);
	    
	    
	    trees4J[bj][syst] = new TTree(treename.c_str(), treename.c_str());
	    
            //basic quantities
	    
            trees4J[bj][syst]->Branch("eta", &etaTree);
            trees4J[bj][syst]->Branch("costhetalj", &cosTree);
            trees4J[bj][syst]->Branch("costhetalbl", &cosBLTree);

            trees4J[bj][syst]->Branch("costhetalj1", &cos1Tree);
            trees4J[bj][syst]->Branch("costhetalbl1", &cos1BLTree);

            trees4J[bj][syst]->Branch("costhetalj2", &cos2Tree);
            trees4J[bj][syst]->Branch("costhetalbl2", &cos2BLTree);

            trees4J[bj][syst]->Branch("topMass", &topMassTree);
            trees4J[bj][syst]->Branch("top1Mass", &top1MassTree);
            trees4J[bj][syst]->Branch("top2Mass", &top2MassTree);
            trees4J[bj][syst]->Branch("topMtw", &topMtwTree);
	    
	    //    trees4J[bj][syst]->Branch("costhetalj_best", &cosTree_best);
	    //    trees4J[bj][syst]->Branch("costhetalbl_best", &cosBLTree_best);
	    
            
	    trees4J[bj][syst]->Branch("Mlb1",&Mlb1Tree);
	    trees4J[bj][syst]->Branch("Mlb2",&Mlb2Tree);
	    trees4J[bj][syst]->Branch("b1b2Mass",&Mb1b2Tree);
	    trees4J[bj][syst]->Branch("b1b2Pt",&pTb1b2Tree);
	    
            trees4J[bj][syst]->Branch("mtwMass", &mtwMassTree);
	    
            trees4J[bj][syst]->Branch("charge", &chargeTree);
            trees4J[bj][syst]->Branch("runid", &runTree);
            trees4J[bj][syst]->Branch("lumiid", &lumiTree);
            trees4J[bj][syst]->Branch("eventid", &eventTree);
            trees4J[bj][syst]->Branch("weight", &weightTree);
            //trees2J[bj][syst]->Branch("weightTmp",&weightTree);
	    
            trees4J[bj][syst]->Branch("totalWeight", &totalWeightTree);
	    
            //Extra info
	    
            trees4J[bj][syst]->Branch("leptonPt", &lepPt);
            trees4J[bj][syst]->Branch("leptonEta", &lepEta);
            trees4J[bj][syst]->Branch("leptonPhi", &lepPhi);
            trees4J[bj][syst]->Branch("leptonE", &lepE);
            trees4J[bj][syst]->Branch("leptonDeltaCorrectedRelIso", &lepDeltaCorrectedRelIso);
            trees4J[bj][syst]->Branch("leptonRhoCorrectedRelIso", &lepRhoCorrectedRelIso);
	    
            trees4J[bj][syst]->Branch("leptonSF", &lepSF);
            trees4J[bj][syst]->Branch("leptonSFB", &lepSFB);
            trees4J[bj][syst]->Branch("leptonSFC", &lepSFC);
	    trees4J[bj][syst]->Branch("leptonSFD", &lepSFD);
	    
	    
            trees4J[bj][syst]->Branch("fJetPt", &fJetPt);
            trees4J[bj][syst]->Branch("fJetE", &fJetE);
            trees4J[bj][syst]->Branch("fJetEta", &fJetEta);
            trees4J[bj][syst]->Branch("fJetPhi", &fJetPhi);
            trees4J[bj][syst]->Branch("fJetBtag", &fJetBTag);
            trees4J[bj][syst]->Branch("fJetFlavour", &fJetFlavourTree);
            trees4J[bj][syst]->Branch("fJetPUID", &fJetPUID);
            trees4J[bj][syst]->Branch("fJetPUWP", &fJetPUWP);
	    
            trees4J[bj][syst]->Branch("fJetBeta", &fJetBeta);
            trees4J[bj][syst]->Branch("fJetDZ", &fJetDZ);
            trees4J[bj][syst]->Branch("fJetRMS", &fJetRMS);
	    
            trees4J[bj][syst]->Branch("bJetBeta", &bJetBeta);
            trees4J[bj][syst]->Branch("bJetDZ", &bJetDZ);
            trees4J[bj][syst]->Branch("bJetRMS", &bJetRMS);
	    
            trees4J[bj][syst]->Branch("bJetPt", &bJetPt);
            trees4J[bj][syst]->Branch("bJetE", &bJetE);
            trees4J[bj][syst]->Branch("bJetEta", &bJetEta);
            trees4J[bj][syst]->Branch("bJetPhi", &bJetPhi);
            trees4J[bj][syst]->Branch("bJetBtag", &bJetBTag);
            trees4J[bj][syst]->Branch("bJetFlavour", &bJetFlavourTree);
            trees4J[bj][syst]->Branch("bJetPUID", &bJetPUID);
            trees4J[bj][syst]->Branch("bJetPUWP", &bJetPUWP);
	    
            trees4J[bj][syst]->Branch("bJet1Pt",&bJet1Pt);
	    trees4J[bj][syst]->Branch("bJet1E",&bJet1E);
	    trees4J[bj][syst]->Branch("bJet1Eta",&bJet1Eta);
	    trees4J[bj][syst]->Branch("bJet1Phi",&bJet1Phi);
            trees4J[bj][syst]->Branch("bJet1Btag", &bJet1BTag);
	    trees4J[bj][syst]->Branch("bJet1Flavour",&bJet1Flavour);
	    
	    trees4J[bj][syst]->Branch("bJet2Pt",&bJet2Pt);
	    trees4J[bj][syst]->Branch("bJet2E",&bJet2E);
	    trees4J[bj][syst]->Branch("bJet2Eta",&bJet2Eta);
	    trees4J[bj][syst]->Branch("bJet2Phi",&bJet2Phi);
            trees4J[bj][syst]->Branch("bJet2Btag", &bJet2BTag);
	    trees4J[bj][syst]->Branch("bJet2Flavour",&bJet2Flavour);
	    
        
	    // trees4J[bj][syst]->Branch("bestJetFlavour", &bestJetFlavourTree);
	    //  trees4J[bj][syst]->Branch("bJetIsbest", &bJetIsbest);
	    
	    
            trees4J[bj][syst]->Branch("firstJetPt", &firstJetPt);
            trees4J[bj][syst]->Branch("firstJetEta", &firstJetEta);
            trees4J[bj][syst]->Branch("firstJetPhi", &firstJetPhi);
            trees4J[bj][syst]->Branch("firstJetE", &firstJetE);
            trees4J[bj][syst]->Branch("firstJetBtag", &firstJetBTag);
            trees4J[bj][syst]->Branch("firstJetFlavour", &firstJetFlavourTree);
	    
            trees4J[bj][syst]->Branch("secondJetPt", &secondJetPt);
            trees4J[bj][syst]->Branch("secondJetEta", &secondJetEta);
            trees4J[bj][syst]->Branch("secondJetPhi", &secondJetPhi);
            trees4J[bj][syst]->Branch("secondJetE", &secondJetE);
            trees4J[bj][syst]->Branch("secondJetBtag", &secondJetBTag);
            trees4J[bj][syst]->Branch("secondJetFlavour", &secondJetFlavourTree);
	    
            trees4J[bj][syst]->Branch("thirdJetPt", &thirdJetPt);
            trees4J[bj][syst]->Branch("thirdJetEta", &thirdJetEta);
            trees4J[bj][syst]->Branch("thirdJetPhi", &thirdJetPhi);
            trees4J[bj][syst]->Branch("thirdJetE", &thirdJetE);
            trees4J[bj][syst]->Branch("thirdJetBtag", &thirdJetBTag);
            trees4J[bj][syst]->Branch("thirdJetFlavour", &thirdJetFlavourTree);
	    
            trees4J[bj][syst]->Branch("fourthJetPt", &fourthJetPt);
            trees4J[bj][syst]->Branch("fourthJetEta", &fourthJetEta);
            trees4J[bj][syst]->Branch("fourthJetPhi", &fourthJetPhi);
            trees4J[bj][syst]->Branch("fourthJetE", &fourthJetE);
            trees4J[bj][syst]->Branch("fourthJetBtag", &fourthJetBTag);
            trees4J[bj][syst]->Branch("fourthJetFlavour", &fourthJetFlavourTree);

	    trees4J[bj][syst]->Branch("bJetDecayPt",&bJetPt);
	    trees4J[bj][syst]->Branch("bJetDecayE",&bJetDecayE);
	    trees4J[bj][syst]->Branch("bJetDecayEta",&bJetDecayEta);
	    trees4J[bj][syst]->Branch("bJetDecayPhi",&bJetDecayPhi);
	    trees4J[bj][syst]->Branch("bJetDecayBtag", &bJetDecayBTag);
	    trees4J[bj][syst]->Branch("bJetDecayFlavour",&bJetDecayFlavour);
	    
	    trees4J[bj][syst]->Branch("bJetRecoilPt",&bJetRecoilPt);
	    trees4J[bj][syst]->Branch("bJetRecoilE",&bJetRecoilE);
	    trees4J[bj][syst]->Branch("bJetRecoilEta",&bJetRecoilEta);
	    trees4J[bj][syst]->Branch("bJetRecoilPhi",&bJetRecoilPhi);
	    trees4J[bj][syst]->Branch("bJetRecoilBtag", &bJetRecoilBTag);
	    trees4J[bj][syst]->Branch("bJetRecoilFlavour",&bJetRecoilFlavour);


	    
	    trees4J[bj][syst]->Branch("looseJetPt", &looseJetPt);
            trees4J[bj][syst]->Branch("looseJetEta", &looseJetEta);
            trees4J[bj][syst]->Branch("looseJetPhi", &looseJetPhi);
            trees4J[bj][syst]->Branch("looseJetE", &looseJetE);
            trees4J[bj][syst]->Branch("looseJetBtag", &looseJetBTag);
            trees4J[bj][syst]->Branch("looseJetFlavour", &looseJetFlavourTree);
	    
            trees4J[bj][syst]->Branch("nJLoose",&nJLoose);
	    //	    trees4J[bj][syst]->Branch("nJ",&nJ);
	    trees4J[bj][syst]->Branch("nJLooseCentral",&nJLooseCentral);
	    trees4J[bj][syst]->Branch("nJLooseForward",&nJLooseForward);
	    trees4J[bj][syst]->Branch("nJLooseMBTag",&nJLooseMBTag);
	    
	    
            trees4J[bj][syst]->Branch("eventFlavour", &eventFlavourTree);
	    
            trees4J[bj][syst]->Branch("HT", &HT);
      	    trees4J[bj][syst]->Branch("H", &H);
	    
            trees4J[bj][syst]->Branch("metPt", &metPt);
            trees4J[bj][syst]->Branch("metPhi", &metPhi);
	    
            trees4J[bj][syst]->Branch("topPt", &topPt);
            trees4J[bj][syst]->Branch("topPhi", &topPhi);
            trees4J[bj][syst]->Branch("topEta", &topEta);
            trees4J[bj][syst]->Branch("topE", &topE);

            trees4J[bj][syst]->Branch("top1Pt", &top1Pt);
            trees4J[bj][syst]->Branch("top1Phi", &top1Phi);
            trees4J[bj][syst]->Branch("top1Eta", &top1Eta);
            trees4J[bj][syst]->Branch("top1E", &top1E);

            trees4J[bj][syst]->Branch("top2Pt", &top2Pt);
            trees4J[bj][syst]->Branch("top2Phi", &top2Phi);
            trees4J[bj][syst]->Branch("top2Eta", &top2Eta);
            trees4J[bj][syst]->Branch("top2E", &top2E);
	    
            trees4J[bj][syst]->Branch("ID", &electronID);
            trees4J[bj][syst]->Branch("MVAID", &leptonMVAID);
	    //            trees4J[bj][syst]->Branch("lepNH", &leptonNHits);
            trees4J[bj][syst]->Branch("nVertices", &nVertices);
            trees4J[bj][syst]->Branch("nGoodVertices", &npv);
	    
	    
            trees4J[bj][syst]->Branch("totalEnergy", &totalEnergy);
            trees4J[bj][syst]->Branch("totalMomentum", &totalMomentum);
	    
            trees4J[bj][syst]->Branch("lowBTag", &lowBTagTree);
            trees4J[bj][syst]->Branch("highBTag", &highBTagTree);
            trees4J[bj][syst]->Branch("mediumBTag", &mediumBTagTree);
	    
            //Systematics b weights
	    
            trees4J[bj][syst]->Branch("bWeight", &bWeightTree);
            trees4J[bj][syst]->Branch("bWeightBTagUp", &bWeightTreeBTagUp);
            trees4J[bj][syst]->Branch("bWeightBTagDown", &bWeightTreeBTagDown);
	    
            trees4J[bj][syst]->Branch("bWeightMisTagUp", &bWeightTreeMisTagUp);
            trees4J[bj][syst]->Branch("bWeightMisTagDown", &bWeightTreeMisTagDown);
	    
            //Systematics pile up weights
            trees4J[bj][syst]->Branch("PUWeight", &PUWeightTree);
	    
            trees4J[bj][syst]->Branch("PUWeightPUUp", &PUWeightTreePUUp);
            trees4J[bj][syst]->Branch("PUWeightPUDown", &PUWeightTreePUDown);
	    //Systematics toppt reweighting weights  
	    if(doTopPtReweighting_){
	      trees4J[bj][syst]->Branch("topPtReweightMCTruth", &topPtReweightMCTruth);
	      trees4J[bj][syst]->Branch("topPtReweight", &topPtReweight);
		  trees4J[bj][syst]->Branch("topPtReweightMCTruthUp", &topPtReweightMCTruthUp);
	      trees4J[bj][syst]->Branch("topPtReweightUp", &topPtReweightUp);
		  trees4J[bj][syst]->Branch("topPtReweightMCTruthDown", &topPtReweightMCTruthDown);
	      trees4J[bj][syst]->Branch("topPtReweightDown", &topPtReweightDown);

	    }
            for (int p = 1; p <= 52; ++p)
	      {
                stringstream w_n;
                w_n << p;
                trees4J[bj][syst]->Branch(("PDFWeight" + w_n.str()).c_str(), &pdf_weights[p - 1]);
	      }
	    
	    
            trees4J[bj][syst]->Branch("PDFWeight_MSTW", &pdf_weights_mstw);
	    trees4J[bj][syst]->Branch("PDFWeight_NNPDF21", &pdf_weights_nnpdf21);
	    trees4J[bj][syst]->Branch("PDFWeight_GJR_FV", &pdf_weights_gjr_fv);
	    trees4J[bj][syst]->Branch("PDFWeight_GJR_FF", &pdf_weights_gjr_ff);
	    trees4J[bj][syst]->Branch("PDFWeight_GJR_FDIS", &pdf_weights_gjr_fdis);
	    trees4J[bj][syst]->Branch("PDFWeight_HERAPDF", &pdf_weights_alekhin);
	    
	  }
        //end 4jets
	
	if(doMCTruth_ && doFullMCTruth_ && syst == "noSyst" ){
	  
	  //	  string treenameMCTruth = (channel + "_MCTruth_" + syst);
	  //	  treesMCTruth = new TTree(treenameMCTruth.c_str(), treenameMCTruth.c_str());
	  if(doTopPtReweighting_){
	    treesMCTruth[syst]->Branch("topPtReweightMCTruth", &topPtReweightMCTruth);
	    treesMCTruth[syst]->Branch("topPtReweight", &topPtReweight);
		treesMCTruth[syst]->Branch("topPtReweightMCTruthUp", &topPtReweightMCTruthUp);
	    treesMCTruth[syst]->Branch("topPtReweightUp", &topPtReweightUp);
		treesMCTruth[syst]->Branch("topPtReweightMCTruthDown", &topPtReweightMCTruthDown);
	    treesMCTruth[syst]->Branch("topPtReweightDown", &topPtReweightDown);

	  }
	  //	  cout<<"here after"<<treesMCTruth[syst]->GetName()<<endl; 
	  
	  for (int p = 1; p <= 2; ++p)
	    {
	      stringstream w_n;
	      w_n << p;
	      TString num( w_n.str() );
	      num = "_"+num+"_";
	      
	      
	      treesMCTruth[syst]->Branch("runid", &runTree);
	      treesMCTruth[syst]->Branch("lumiid", &lumiTree);
	      treesMCTruth[syst]->Branch("eventid", &eventTree);
	      
	      treesMCTruth[syst]->Branch("nMCTruthLeptons", &nMCTruthLeptons);
	      
	      treesMCTruth[syst]->Branch("MCTop"+num+"Pt", &MCTopsPtVec[p-1]);
	      treesMCTruth[syst]->Branch("MCTop"+num+"Phi", &MCTopsPhiVec[p-1]);
	      treesMCTruth[syst]->Branch("MCTop"+num+"Eta", &MCTopsEtaVec[p-1]);
	      treesMCTruth[syst]->Branch("MCTop"+num+"E", &MCTopsEnergyVec[p-1]);
	      treesMCTruth[syst]->Branch("MCTop"+num+"PdgId", &MCTopsPdgIdVec[p-1]);
	      treesMCTruth[syst]->Branch("MCTop"+num+"MotherId", &MCTopsMotherIdVec[p-1]);
	      
	      treesMCTruth[syst]->Branch("MCTopLepton"+num+"Pt", &MCTopLeptonsPtVec[p-1]);
	      treesMCTruth[syst]->Branch("MCTopLepton"+num+"Phi", &MCTopLeptonsPhiVec[p-1]);
	      treesMCTruth[syst]->Branch("MCTopLepton"+num+"Eta", &MCTopLeptonsEtaVec[p-1]);
	      treesMCTruth[syst]->Branch("MCTopLepton"+num+"E", &MCTopLeptonsEnergyVec[p-1]);
	      treesMCTruth[syst]->Branch("MCTopLepton"+num+"PdgId", &MCTopLeptonsPdgIdVec[p-1]);
	      treesMCTruth[syst]->Branch("MCTopLepton"+num+"MotherId", &MCTopLeptonsMotherIdVec[p-1]);
	      
	      treesMCTruth[syst]->Branch("MCTopNeutrino"+num+"Pt", &MCTopNeutrinosPtVec[p-1]);
	      treesMCTruth[syst]->Branch("MCTopNeutrino"+num+"Phi", &MCTopNeutrinosPhiVec[p-1]);
	      treesMCTruth[syst]->Branch("MCTopNeutrino"+num+"Eta", &MCTopNeutrinosEtaVec[p-1]);
	      treesMCTruth[syst]->Branch("MCTopNeutrino"+num+"E", &MCTopNeutrinosEnergyVec[p-1]);
	      treesMCTruth[syst]->Branch("MCTopNeutrino"+num+"PdgId", &MCTopNeutrinosPdgIdVec[p-1]);
	      treesMCTruth[syst]->Branch("MCTopNeutrino"+num+"MotherId", &MCTopNeutrinosMotherIdVec[p-1]);
	      
	      treesMCTruth[syst]->Branch("MCTopQuark"+num+"Pt", &MCTopQuarksPtVec[p-1]);
	      treesMCTruth[syst]->Branch("MCTopQuark"+num+"Phi", &MCTopQuarksPhiVec[p-1]);
	      treesMCTruth[syst]->Branch("MCTopQuark"+num+"Eta", &MCTopQuarksEtaVec[p-1]);
	      treesMCTruth[syst]->Branch("MCTopQuark"+num+"E", &MCTopQuarksEnergyVec[p-1]);
	      treesMCTruth[syst]->Branch("MCTopQuark"+num+"PdgId", &MCTopQuarksPdgIdVec[p-1]);
	      treesMCTruth[syst]->Branch("MCTopQuark"+num+"MotherId", &MCTopQuarksMotherIdVec[p-1]);
	      
	      treesMCTruth[syst]->Branch("MCTopQuarkBar"+num+"Pt", &MCTopQuarkBarsPtVec[p-1]);
	      treesMCTruth[syst]->Branch("MCTopQuarkBar"+num+"Phi", &MCTopQuarkBarsPhiVec[p-1]);
	      treesMCTruth[syst]->Branch("MCTopQuarkBar"+num+"Eta", &MCTopQuarkBarsEtaVec[p-1]);
	      treesMCTruth[syst]->Branch("MCTopQuarkBar"+num+"E", &MCTopQuarkBarsEnergyVec[p-1]);
	      treesMCTruth[syst]->Branch("MCTopQuarkBar"+num+"PdgId", &MCTopQuarkBarsPdgIdVec[p-1]);
	      treesMCTruth[syst]->Branch("MCTopQuarkBar"+num+"MotherId", &MCTopQuarkBarsMotherIdVec[p-1]);
	      
	      treesMCTruth[syst]->Branch("MCTopBQuark"+num+"Pt", &MCTopBQuarksPtVec[p-1]);
	      treesMCTruth[syst]->Branch("MCTopBQuark"+num+"Phi", &MCTopBQuarksPhiVec[p-1]);
	      treesMCTruth[syst]->Branch("MCTopBQuark"+num+"Eta", &MCTopBQuarksEtaVec[p-1]);
	      treesMCTruth[syst]->Branch("MCTopBQuark"+num+"E", &MCTopBQuarksEnergyVec[p-1]);
	      treesMCTruth[syst]->Branch("MCTopBQuark"+num+"PdgId", &MCTopBQuarksPdgIdVec[p-1]);
	      treesMCTruth[syst]->Branch("MCTopBQuark"+num+"MotherId", &MCTopBQuarksMotherIdVec[p-1]);
	      
	      treesMCTruth[syst]->Branch("MCTopW"+num+"Pt", &MCTopWsPtVec[p-1]);
	      treesMCTruth[syst]->Branch("MCTopW"+num+"Phi", &MCTopWsPhiVec[p-1]);
	      treesMCTruth[syst]->Branch("MCTopW"+num+"Eta", &MCTopWsEtaVec[p-1]);
	      treesMCTruth[syst]->Branch("MCTopW"+num+"E", &MCTopWsEnergyVec[p-1]);
	      treesMCTruth[syst]->Branch("MCTopW"+num+"PdgId", &MCTopWsPdgIdVec[p-1]);
	      treesMCTruth[syst]->Branch("MCTopW"+num+"DauOneId", &MCTopWsDauOneIdVec[p-1]);
	      
	    }
	  for (int p = 1; p <= 12; ++p)
	    {
	      stringstream w_n;
	      w_n << p;
	      TString num( w_n.str() );
	      num = "_"+num+"_";
	      
	      treesMCTruth[syst]->Branch("MCQuark"+num+"Pt", &MCQuarksPtVec[p-1]);
	      treesMCTruth[syst]->Branch("MCQuark"+num+"Phi", &MCQuarksPhiVec[p-1]);
	      treesMCTruth[syst]->Branch("MCQuark"+num+"Eta", &MCQuarksEtaVec[p-1]);
	      treesMCTruth[syst]->Branch("MCQuark"+num+"E", &MCQuarksEnergyVec[p-1]);
	      treesMCTruth[syst]->Branch("MCQuark"+num+"PdgId", &MCQuarksPdgIdVec[p-1]);
	      treesMCTruth[syst]->Branch("MCQuark"+num+"MotherId", &MCQuarksMotherIdVec[p-1]);
	    }
	  
	  for (int p = 1; p <= 4; ++p)
	    {
	      stringstream w_n;
	      w_n << p;
	      TString num( w_n.str() );
	      num = "_"+num+"_";
	      
	      treesMCTruth[syst]->Branch("MCBQuark"+num+"Pt", &MCBQuarksPtVec[p-1]);
	      treesMCTruth[syst]->Branch("MCBQuark"+num+"Phi", &MCBQuarksPhiVec[p-1]);
	      treesMCTruth[syst]->Branch("MCBQuark"+num+"Eta", &MCBQuarksEtaVec[p-1]);
	      treesMCTruth[syst]->Branch("MCBQuark"+num+"E", &MCBQuarksEnergyVec[p-1]);
	      treesMCTruth[syst]->Branch("MCBQuark"+num+"PdgId", &MCBQuarksPdgIdVec[p-1]);
	      treesMCTruth[syst]->Branch("MCBQuark"+num+"MotherId", &MCBQuarksMotherIdVec[p-1]);
	      
	      treesMCTruth[syst]->Branch("MCLepton"+num+"Pt", &MCLeptonsPtVec[p-1]);
	      treesMCTruth[syst]->Branch("MCLepton"+num+"Phi", &MCLeptonsPhiVec[p-1]);
	      treesMCTruth[syst]->Branch("MCLepton"+num+"Eta", &MCLeptonsEtaVec[p-1]);
	      treesMCTruth[syst]->Branch("MCLepton"+num+"E", &MCLeptonsEnergyVec[p-1]);
	      treesMCTruth[syst]->Branch("MCLepton"+num+"PdgId", &MCLeptonsPdgIdVec[p-1]);
	      treesMCTruth[syst]->Branch("MCLepton"+num+"MotherId", &MCLeptonsMotherIdVec[p-1]);
	      
	      treesMCTruth[syst]->Branch("MCNeutrino"+num+"Pt", &MCNeutrinosPtVec[p-1]);
	      treesMCTruth[syst]->Branch("MCNeutrino"+num+"Phi", &MCNeutrinosPhiVec[p-1]);
	      treesMCTruth[syst]->Branch("MCNeutrino"+num+"Eta", &MCNeutrinosEtaVec[p-1]);
	      treesMCTruth[syst]->Branch("MCNeutrino"+num+"E", &MCNeutrinosEnergyVec[p-1]);
	      treesMCTruth[syst]->Branch("MCNeutrino"+num+"PdgId", &MCNeutrinosPdgIdVec[p-1]);
	      treesMCTruth[syst]->Branch("MCNeutrino"+num+"MotherId", &MCNeutrinosMotherIdVec[p-1]);
	    }
	}
	
	
      }
    
    passingLepton = 0;
    passingMuonVeto = 0;
    passingLeptonVeto = 0;
    passingJets = 0;
    passingBJets = 0;
    passingMET = 0;
    
    //TCHPT
    b_tchpt_0_tags = BTagWeight(0, 0);
    b_tchpt_1_tag = BTagWeight(1, 1);
    b_tchpt_2_tags = BTagWeight(2, 2);
    //CSVT
    b_csvt_0_tags = BTagWeight(0, 0);
    b_csvt_1_tag = BTagWeight(1, 1);
    b_csvt_2_tags = BTagWeight(2, 2);
    //CSVM
    b_csvm_0_tags = BTagWeight(0, 0);
    b_csvm_1_tag = BTagWeight(1, 1);
    b_csvm_2_tags = BTagWeight(2, 2);

    JEC_PATH = "./";

    //    jecUnc  = new JetCorrectionUncertainty(*(new JetCorrectorParameters("Summer12_V2_DATA_AK5PF_UncertaintySources.txt", "Total")));
    jecUnc  = new JetCorrectionUncertainty(*(new JetCorrectorParameters("Fall12_V7_DATA_UncertaintySources_AK5PFchs.txt", "Total")));
    JES_SW = 0.0;
    JES_b_cut = 0.0;
    JES_b_overCut = 0.0;


    //JetResolution part

    leptonRelIsoQCDCutUpper = 0.9, leptonRelIsoQCDCutLower = 0.2;

    //   LHAPDF::initPDFSet(1, "cteq66.LHgrid");
    LHAPDF::initPDFSet(1, "CT10.LHgrid");
    LHAPDF::initPDFSet(2, "MSTW2008nlo68cl.LHgrid");
    //    LHAPDF::initPDFSet(3, "CT10.LHgrid");

    //  //cout<< "I work for now but I do nothing. But again, if you gotta do nothing, you better do it right. To prove my good will I will provide you with somse numbers later."<<endl;
    isFirstEvent = true;
}

////Beginning of main per-event loop:
//This is the function that is called event by event
void SingleTopSystematicsTreesDumper::analyze(const Event &iEvent, const EventSetup &iSetup)
{
  int  idele=0;
  int  mvaele=0;

  //cout<<"MVAID " <<  useMVAID_ <<" CUT BASEID"<< useCutBasedID_ <<  " doMCTruth" << doMCTruth_ << "algo " <<algo_ <<endl;

    initBranchVars();
    //cout <<" test 0 "<<endl;
    iEvent.getByLabel(jetsEta_, jetsEta);
    iEvent.getByLabel(jetsPt_, jetsPt);
    //  if(jetsPt->size() < 2)return;
    //    if (jetsPt->size() > 22 )return; //Crazy events with huge jet multiplicity in mc
    //if (jetsPt->size() > 20 && channel != "Data")return; //Crazy events with huge jet multiplicity in mc
    iEvent.getByLabel(jetsPhi_, jetsPhi);

    gotLeptons = 0;
    gotPV = 0;
    gotQCDLeptons = 0;
    gotLooseLeptons = 0;
    gotJets = 0;
    gotAllJets = 0;
    gotMets = 0;
    gotPU = 0;
    gotPDFs = 0;

    jsfshpt.clear();//  bjs.clear();cjs.clear();ljs.clear();

    jsfshpt_b_tag_up.clear();//  bjs.clear();cjs.clear();ljs.clear();
    jsfshpt_b_tag_down.clear();//  bjs.clear();cjs.clear();ljs.clear();

    jsfshpt_mis_tag_up.clear();//  bjs.clear();cjs.clear();ljs.clear();
    jsfshpt_mis_tag_down.clear();//  bjs.clear();cjs.clear();ljs.clear();

    jsfscsvt.clear();

    jsfscsvt_b_tag_up.clear();
    jsfscsvt_b_tag_down.clear();

    jsfscsvt_mis_tag_up.clear();
    jsfscsvt_mis_tag_down.clear();

    jsfscsvm.clear();

    jsfscsvm_b_tag_up.clear();
    jsfscsvm_b_tag_down.clear();

    jsfscsvm_mis_tag_up.clear();
    jsfscsvm_mis_tag_down.clear();


    iEvent.getByLabel(METPhi_, METPhi);
    iEvent.getByLabel(METPt_, METPt);
    iEvent.getByLabel(leptonsDeltaCorrectedRelIso_, leptonsDeltaCorrectedRelIso); ///FOR muons
    iEvent.getByLabel(leptonsRhoCorrectedRelIso_, leptonsRhoCorrectedRelIso);

    double PUWeight = 1;
    double PUWeightNoSyst = 1;
    double bWeightNoSyst = 1;

    float metPx = 0;
    float metPy = 0;

    //    metPx = METPt->at(0) * cos(METPhi->at(0));
    //metPy = METPt->at(0) * sin(METPhi->at(0));

    //    float metPtNom =0;
    //    float metPhiNom =0;
    
    float metPxTmp = metPx;
    float metPyTmp = metPy;

    size_t nLeptons = 0;//leptonsPt->size();
    size_t nQCDLeptons = 0;//leptonsPt->size();
    size_t nJets = 0;
    size_t nJetsTight = 0;
    size_t nJetsNoPU = 0;
    size_t nJetsCentralNoPU = 0;
    size_t nJetsCentral = 0;
    size_t nJetsForwardNoPU = 0;
    size_t nJetsForward = 0;
    size_t nJetsNoSyst = 0;
    size_t nJetsTightNoSyst = 0;
    
    int nJetsLoose = 0; 
    int nJetsLooseCentral = 0;
    int nJetsLooseForward = 0;
    int nJetsLooseMBTag= 0;
   
    //    size_t nLooseBJets = 0;


    double WeightLumi = finalLumi * crossSection / originalEvents;
    double Weight = 1;
    double MTWValue = 0;
    //    double MTWValueQCD = 0;
    //    double RelIsoQCDCut = 0.1;

    
    float ptCutLoose = 20;
    float ptCutTight = 40;
    float ptCut = 40; // if doAsymmetricPtCut,then it's 30
    if(doAsymmetricPtCut_) ptCut = 30;

    //    double myWeight = 1.;

    bool didLeptonLoop = false;
    bool passesLeptonStep = false;
    bool isQCD = false;


    //    bool didJetLoop = false;

    if (channel == "Data")WeightLumi = 1;

    int secondPtPosition = -1;
    int thirdPtPosition = -1;
    int fourthPtPosition = -1;
    double secondPt = -1;
    double thirdPt = -1;
    double fourthPt = -1;
 
    //    int lowBTagTreePositionNoSyst = -1;
    //    int highBTagTreePositionNoSyst = -1; // this vars don't set to -1 for each syst , so it keep the no syst information if we need them for other syst. 
    //    int maxPtTreePositionNoSyst = -1;   // we don't need them since we have no especial syst which is not in the list , when we want we should add same for medium and mediumlow.
    //    int minPtTreePositionNoSyst = -1;

    for (size_t s = 0; s < systematics.size(); ++s)
    {
        string syst_name =  systematics.at(s);
        string syst = syst_name;


        nLeptons = 0;
        nQCDLeptons = 0;
        nJets = 0;
        nJetsTight = 0; 
        nJetsTightNoSyst = 0;
        nJetsNoPU = 0;
        nJetsCentral = 0;
        nJetsCentralNoPU = 0;
        nJetsForward = 0;
        nJetsForwardNoPU = 0;
        nJetsLoose = 0; 
        nJetsLooseCentral = 0;
        nJetsLooseForward = 0;
        nJetsLooseMBTag =0;
        Weight = WeightLumi;

	HT = 0; H= 0;
	
        bool is_btag_relevant = ((syst_name == "noSyst" || syst_name == "BTagUp" || syst_name == "BTagDown"
                                  || syst_name == "MisTagUp" || syst_name == "MisTagDown"
                                  || syst_name == "JESUp" || syst_name == "JESDown"
                                  || syst_name == "JERUp" || syst_name == "JERDown"
                                 ) && channel != "Data"
                                );

//cout<<"TREEMCTRUE "<<"doMCTruth_  "<<doMCTruth_ <<"  doFullMCTruth_  "<< doFullMCTruth_<<endl;
	if( syst == "noSyst" && doMCTruth_ && doFullMCTruth_){	

	  fillMCTruth(iEvent);
	  //treesMCTruth->Fill();         cout<<" treesMCTruthEntries()      "<<treesMCTruth->GetEntries()<<endl;
	  treesMCTruth[syst]->Fill();      //   cout<<" treesMCTruthEntries()      "<<treesMCTruth[syst]->GetEntries()<<endl;
	}


        //Setup for systematics

        //Here we have vectors of weights
        //to be associated with the
        //b-jets selection in the sample according to algorythm X:
        //a b-tag requirement implies a b_weight_tag_algoX,
        //a b-veto requirement implies a b_weight_antitag_algoX

        //TCHPT
        b_weight_tchpt_1_tag = 1;
        b_weight_tchpt_0_tags = 1;
        b_weight_tchpt_2_tags = 1;
        //CSVT
        b_weight_csvm_1_tag = 1;
        b_weight_csvm_0_tags = 1;
        b_weight_csvm_2_tags = 1;
        //CSVT
        b_weight_csvt_1_tag = 1;
        b_weight_csvt_0_tags = 1;
        b_weight_csvt_2_tags = 1;

        nb = 0;
        nc = 0;
        nudsg = 0;

	//Clear the vector of objects to be used in the selection

        //Define - initialize some variables
        MTWValue = 0;


        //position of lowest and highest b-tag used to chose the top candidate
        int lowBTagTreePosition = -1;
        lowBTagTree = 99999;
	    int highBTagTreePosition = -1;
        highBTagTree = -9999;
        int mediumBTagTreePosition = -1;
        mediumBTagTree = -9999;
        int mediumlowBTagTreePosition = -1;
        mediumlowBTagTree = -9999;
        int maxPtTreePosition = -1;
        maxPtTree = -99999;
	//        int minPtTreePosition = -1;
        minPtTree = 99999;
        int maxLoosePtTreePosition = -1;
        maxLoosePtTree = -99999;

	    secondPt = -1;
        thirdPt = -1;
        fourthPt = -1;
        secondPtPosition = -1;
        thirdPtPosition = -1;
        fourthPtPosition = -1;

        //Define - initialize some variables
        float eta;
        float ptCorr;
        int flavour;
	//        double unc = 0;


        /////////
        ///Beginning of the standard lepton-jet loop:
        //Loops to apply systematics on jets-leptons
        /////////
	
	//Lepton loop
	//	cout << " getting leptons, syst "<<syst<<endl;
	if (!didLeptonLoop)
	  {
            for (size_t i = 0; i < leptonsDeltaCorrectedRelIso->size(); ++i)
	      {
		float leptonRelIsoDeltaCorr = 9999.,leptonRelIsoRhoCorr=9999.;
		float leptonMVAIDTemp = -1.1,leptonNHitsTemp=10.; 
                if (leptonsFlavour_ == "muon") {
		    leptonRelIsoDeltaCorr = leptonsDeltaCorrectedRelIso->at(i);
		    if (leptonRelIsoDeltaCorr > RelIsoCut)continue;
		  }
		if (leptonsFlavour_ == "electron") {
//                    iEvent.getByLabel(leptonsRhoCorrectedRelIso_, leptonsRhoCorrectedRelIso); 
		    leptonRelIsoRhoCorr = leptonsRhoCorrectedRelIso->at(i);//cout << " inside lepton loop: lepton n "<< i +1 << " reliso " <<  leptonsRhoCorrectedRelIso->at(i) <<endl;
		    if (leptonRelIsoRhoCorr > RelIsoCut)continue;
		    //		    cout << " inside lepton loop: lepton n "<< i +1 << " reliso " <<  leptonsRhoCorrectedRelIso->at(i) <<" nLeptons before: "<<nLeptons<<endl;                 
		}
		float leptonPt = 0.;
		iEvent.getByLabel(leptonsPt_, leptonsPt);
                leptonPt = leptonsPt->at(i)*1.;
                if ( leptonPt < 26.) continue;
                //Apply isolation cut
                if (!gotLeptons) {
		  if (leptonsFlavour_ == "muon") {
		     // iEvent.getByLabel(leptonsRhoCorrectedRelIso_, leptonsRhoCorrectedRelIso);   it's repeat 
		      lepRhoCorrectedRelIso = leptonsRhoCorrectedRelIso->at(i);
                    } //why? just to keep rho corr for muon ? 
		  iEvent.getByLabel(leptonsEta_, leptonsEta);
		  iEvent.getByLabel(leptonsPhi_, leptonsPhi);
		  iEvent.getByLabel(leptonsEnergy_, leptonsEnergy);
		  iEvent.getByLabel(leptonsCharge_, leptonsCharge);
		  iEvent.getByLabel(leptonsID_, leptonsID);
		  iEvent.getByLabel(leptonsDB_, leptonsDB);
		  gotLeptons = true;
                }
                //if electron apply ID cuts
                if (leptonsFlavour_ == "electron"  ) {
		  if (leptonsID->size() == 0)cout << "warning requiring ele id of collection which has no entries! Check the leptonsFlavour parameter " << endl;
		  //		  float leptonRelIsoRhoCorr = leptonsRhoCorrectedRelIso->at(i);
		  //		  float leptonRelIsoDeltaCorr = leptonsDeltaCorrectedRelIso->at(i);
		  //lepRhoCorrectedRelIso = leptonRelIsoRhoCorr; // repeat at 1742
		  iEvent.getByLabel(leptonsMVAID_, leptonsMVAID);
		  iEvent.getByLabel(leptonsNHits_, leptonsNHits);
		  float leptonID = leptonsID->at(i);
		  leptonMVAIDTemp = leptonsMVAID->at(i);
		  leptonNHitsTemp = leptonsNHits->at(i);
		  electronID = leptonID;
		  //		  cout<< "lepton properties: leptonID: " << leptonID<<"leptonNHitsTemp  " << leptonNHitsTemp << " leptonMVAIDTemp " <<leptonMVAIDTemp <<endl;
		  if(leptonID>0)++idele; if(leptonMVAIDTemp>0.9 && leptonNHitsTemp<=0.00001)++mvaele; //cout<<"mvaele:  "<<mvaele<< " idele"<<idele<<endl;
		  if(useCutBasedID_>0){
		    if(!(leptonID>0.0))continue; 
		  }
		  if(useMVAID_>0){
		    if(!(leptonMVAIDTemp>0.90))continue; 
		    if(!(leptonNHitsTemp<=0.00001))continue; 
		  }
                } ///if elecron
                if (leptonsFlavour_ == "muon"  )
		  {
                    iEvent.getByLabel(leptonsDZ_, leptonsDZ);
                    if ( leptonsDZ->at(i) > 0.5) continue;
		  }
                float leptonDB = leptonsDB->at(i);
                if ( fabs(leptonDB) > 0.02) continue;
		
		lepDeltaCorrectedRelIso = leptonRelIsoDeltaCorr;
		lepRhoCorrectedRelIso = leptonRelIsoRhoCorr;
		leptonMVAID = leptonMVAIDTemp;
		leptonNHits = leptonNHitsTemp;
                float leptonPhi = leptonsPhi->at(i);
                float leptonEta = leptonsEta->at(i);
                float leptonE = leptonsEnergy->at(i);
                //Build the lepton 4-momentum
                ++nLeptons;
		leptons[nLeptons - 1] = math::PtEtaPhiELorentzVector(leptonPt, leptonEta, leptonPhi, leptonE);
		if (nLeptons >= 3) break;
//		cout<< " lepton number " << nLeptons << " pt "<< leptonPt << " eta " << fabs(leptonEta)<< endl;
            }//loop on leptons line 1678 "leptonsDeltaCorrectedRelIso->size("
            bool passesLeptons = (nLeptons == 1);
	    //            bool passesOneLepton = (nLeptons == 1);
          if (passesLeptons) {
                //cout<< " nlepton==1,  pt "<< leptonPt << " eta " << fabs(leptonEta)<< "leptonID: " << leptonID<<"leptonNHits  " << leptonNHits << " leptonMVAID " <<leptonMVAID <<endl;
	      
if (passesLeptons && syst == "noSyst")++passingLepton;
	      iEvent.getByLabel(looseMuonsDeltaCorrectedRelIso_, looseMuonsDeltaCorrectedRelIso);
	      if (passesLeptons && syst == "noSyst" && looseMuonsDeltaCorrectedRelIso->size() == 1)++passingMuonVeto;
	      iEvent.getByLabel(looseElectronsDeltaCorrectedRelIso_, looseElectronsDeltaCorrectedRelIso);
	      bool passesLooseLeptons = (looseMuonsDeltaCorrectedRelIso->size() + looseElectronsDeltaCorrectedRelIso->size()) == 1;
	      passesLeptons = passesLeptons && passesLooseLeptons;
            }
            if (passesLeptons && syst == "noSyst")++passingLeptonVeto;
	      isQCD = (!passesLeptons);
            
	      //Loop for the qcd leptons
	      //	      cout << " getting qcd leptons, syst "<<syst<<endl;
            if (doQCD_ && isQCD)
            {
                iEvent.getByLabel(qcdLeptonsDeltaCorrectedRelIso_, qcdLeptonsDeltaCorrectedRelIso);
		iEvent.getByLabel(qcdLeptonsRhoCorrectedRelIso_, qcdLeptonsRhoCorrectedRelIso);
		//		cout << "qcd lep size " <<qcdLeptonsDeltaCorrectedRelIso->size()<<endl;
                for (size_t i = 0; i < qcdLeptonsDeltaCorrectedRelIso->size(); ++i)
                {
		  float leptonPt = 0.; float qcdleptonMVAIDTemp = -1.1;
		  iEvent.getByLabel(qcdLeptonsPt_, qcdLeptonsPt);
		  iEvent.getByLabel(qcdLeptonsMVAID_, qcdLeptonsMVAID);
		  leptonPt = qcdLeptonsPt->at(i);
		  if (leptonsFlavour_ == "electron")
		    qcdleptonMVAIDTemp = qcdLeptonsMVAID->at(i);
		  else if (leptonsFlavour_ == "muon"){
		    //		    qcdleptonMVAIDTemp = qcdLeptonsMVAID->at(0);
		  }
		  if ( leptonPt < 26.) continue;
		  float leptonQCDRelIso = qcdLeptonsDeltaCorrectedRelIso->at(i);
		  //float leptonRelIso = qcdLeptonsDeltaCorrectedRelIso->at(i);
		  //		  cout << "qcd lep " << i << "rel iso "<<leptonQCDRelIso<<endl;
		  //float leptonQCDRelIso = leptonRelIso;
		  //Use an anti-isolation requirement
		  
		  //		  lepDeltaCorrectedRelIso = leptonRelIso;
		  lepDeltaCorrectedRelIso = leptonQCDRelIso;
		  lepRhoCorrectedRelIso = qcdLeptonsRhoCorrectedRelIso->at(i) ;
		  
		  if (leptonsFlavour_ == "muon")
                    {
		      if ( leptonQCDRelIso > leptonRelIsoQCDCutUpper )continue;
		      if ( leptonQCDRelIso < leptonRelIsoQCDCutLower )continue;
		      
		      if (!gotQCDLeptons)
			{
			  iEvent.getByLabel(qcdLeptonsEta_, qcdLeptonsEta);
			  iEvent.getByLabel(qcdLeptonsPhi_, qcdLeptonsPhi);
			  iEvent.getByLabel(qcdLeptonsEnergy_, qcdLeptonsEnergy);
			  iEvent.getByLabel(qcdLeptonsCharge_, qcdLeptonsCharge);
			  iEvent.getByLabel(qcdLeptonsID_, qcdLeptonsID);
			  iEvent.getByLabel(qcdLeptonsDB_, qcdLeptonsDB);

			  gotQCDLeptons = true;

                        }
                    }// muon
		  if (leptonsFlavour_ == "electron"  )
                    {
		      bool QCDCondition = false;
		      iEvent.getByLabel(qcdLeptonsID_, qcdLeptonsID);
		      iEvent.getByLabel(qcdLeptonsDB_, qcdLeptonsDB);

		      float leptonID = qcdLeptonsID->at(i);
		      float beamspot  = fabs(qcdLeptonsDB->at(i));

	          bool isid = (leptonID ==  1 || leptonID == 3 || leptonID == 5 || leptonID == 7);
         //Legenda for eleId : 0 fail, 1 ID only, 2 iso Only, 3 ID iso only, 4 conv rej, 5 conv rej and ID, 6 conv rej and iso, 7 all
             if(useCutBasedID_ ) QCDCondition = (!(lepRhoCorrectedRelIso < 0.1) && !(beamspot < 0.02))  || (!(lepRhoCorrectedRelIso < 0.1) && !isid) || (!isid && !(beamspot < 0.02));
             if(useMVAID_)        QCDCondition = (!(lepRhoCorrectedRelIso < 0.1)|| !(qcdleptonMVAIDTemp>0.9));
		      electronID = leptonID;


              if (!QCDCondition) continue;
		      if (!gotQCDLeptons)
			{
			  iEvent.getByLabel(qcdLeptonsEta_, qcdLeptonsEta);
			  iEvent.getByLabel(qcdLeptonsPhi_, qcdLeptonsPhi);
			  iEvent.getByLabel(qcdLeptonsEnergy_, qcdLeptonsEnergy);
			  iEvent.getByLabel(qcdLeptonsCharge_, qcdLeptonsCharge);

			  gotQCDLeptons = true;
                        }
                    }// electron
		  
		  //lepRelIso = leptonRelIso; // for both ele and muon Delta corrected rel iso is used for qcd 
          leptonMVAID = qcdleptonMVAIDTemp;
		  float qcdLeptonPt = qcdLeptonsPt->at(i);
		  float qcdLeptonPhi = qcdLeptonsPhi->at(i);
		  float qcdLeptonEta = qcdLeptonsEta->at(i);
		  float qcdLeptonE = qcdLeptonsEnergy->at(i);

		  //Create the lepton
		  ++nQCDLeptons;
		  qcdLeptons[nQCDLeptons - 1] = math::PtEtaPhiELorentzVector(qcdLeptonPt, qcdLeptonEta, qcdLeptonPhi, qcdLeptonE);
		  if (nQCDLeptons == 3) break;
//		  if (nQCDLeptons == 3) break;
		} //loop on QCDleptons
            } //end if doqcd isQCD 
            didLeptonLoop = true;
	    isQCD = (nQCDLeptons == 1 && !passesLeptons);
	    passesLeptonStep = (passesLeptons || isQCD);
	    //	    	    cout << " nqcd lep "<<nQCDLeptons<< " passes leptons? " <<passesLeptons<<" passesLeptonStep? " <<passesLeptonStep <<" nLeptons  "<< nLeptons<<endl;
	} //  end didLeptonLoop
        if (!passesLeptonStep)continue;
	if (!gotPV)
        {   iEvent.getByLabel(vertexZ_, vertexZ);  npv = vertexZ->size();
        }
	
	//Getting the MET:
	//	cout << " getting mets, syst "<<syst<<endl;

	getMET(iEvent,syst);
	metPhi = METPhi->at(0);
	metPt = METPt->at(0);
	
	metPx = metPt * cos(metPhi);metPy = metPt * sin(metPhi);
	metPxTmp = metPx;metPyTmp = metPy;  
	//If metphi corrections are needed, apply in this point 
	metPx = metPxTmp; metPy = metPyTmp;
	
	//Initialization of number of b-tags before jet loop
        ntchpt_tags = 0;        ncsvl_tags = 0;        ncsvt_tags = 0;        ncsvm_tags = 0;        ntight_tags = 0;
	jsfshpt.clear();        jsfscsvt.clear();        jsfscsvm.clear();
	bWeightTree = 1;        bWeightTreeBTagUp = 1;        bWeightTreeMisTagUp = 1;        bWeightTreeBTagDown = 1;        bWeightTreeMisTagDown = 1;
	//	cout << " getting jets, syst "<<syst<<endl;
        if (!gotJets)
	  {
	    iEvent.getByLabel(jetsBTagAlgo_, jetsBTagAlgo);
	    iEvent.getByLabel(jetsAntiBTagAlgo_, jetsAntiBTagAlgo);
	    iEvent.getByLabel(jetsPileUpID_, jetsPileUpID);
	    iEvent.getByLabel(jetsPileUpWP_, jetsPileUpWP);
	    iEvent.getByLabel(jetsBeta_, jetsBeta);
	    iEvent.getByLabel(jetsDZ_, jetsDZ);
	    iEvent.getByLabel(jetsRMS_, jetsRMS);
	    iEvent.getByLabel(jetsFlavour_, jetsFlavour);
	    iEvent.getByLabel(jetsCorrTotal_, jetsCorrTotal);
	    iEvent.getByLabel(jetsEta_, jetsEta);
	    iEvent.getByLabel(jetsPhi_, jetsPhi);
	    gotJets = true;
	  }
	getJetPtE(iEvent,syst);//Pt and E change with JES/JER
	
	
	for (size_t i = 0; i < jetsPt->size(); ++i)
	  {
		  eta = jetsEta->at(i);
		  if (fabs(eta ) > 4.7)continue;
		  ptCorr = jetsPt->at(i);
		  flavour = jetsFlavour->at(i);
		  double energyCorr = jetsEnergy->at(i);
		  double ptUncorr=ptCorr, energyUncorr=energyCorr;
		  
		  //Part of JES and JER: not needed as it's included in the jets definition atm
		  //If need be, implement it here:
		  ptCorr = offlineJESJERApplicationPt(ptUncorr,energyUncorr,eta,syst);
		  energyCorr = offlineJESJERApplicationE(ptUncorr,energyUncorr,eta,syst);
		  HT+= (math::PtEtaPhiELorentzVector(ptCorr, jetsEta->at(i), jetsPhi->at(i), energyCorr)).Et();
  		  H+= energyCorr;	  
		  //b tag thresholds
		  double valueTCHPT = jetsBTagAlgo->at(i);
		  double valueCSV = jetsAntiBTagAlgo->at(i);
		  bool passesTCHPT = valueTCHPT > 3.41; //TCHPT Working point
		  bool passesCSVT = valueCSV > 0.898; //TCHPT Working point
		  bool passesCSVM = valueCSV >0.679;//CSVM Working point
		  double valueChosenAlgo = valueCSV;
		  if (algo_ == "TCHPT")valueChosenAlgo = valueTCHPT;
		  
		  //Pt cut
		  
		  bool passesPtCut = ptCorr > ptCut;
		  bool passesPtTightCut = ptCorr > ptCutTight;
		  bool passesPtLooseCut =( ptCorr > ptCutLoose &&  ptCorr <= ptCut);
		  
		  if (passesPtCut){
		    
		    if (passesPtTightCut) ++nJetsTight;
		    
		    ++nJets;
		    if ( fabs(eta) < 2.5)++nJetsCentral;
		    else ++nJetsForward;
		    if ( jetsPileUpWP->at(i) > 2.5)
		      {
			++nJetsNoPU;
			if ( fabs(eta) < 2.5)++nJetsCentralNoPU;
			else ++nJetsForwardNoPU;
		      }
		    jets[nJets - 1] = math::PtEtaPhiELorentzVector(ptCorr, jetsEta->at(i), jetsPhi->at(i), energyCorr);
		    flavours[nJets - 1] = flavour;
		    jetsBTag[nJets - 1] = valueChosenAlgo;
		    if (syst == "noSyst")
		      { 
			if (passesPtTightCut)
			  ++nJetsTightNoSyst;
			++nJetsNoSyst;
			jetsNoSyst[nJets - 1] = jets[nJets - 1];
			jetsBTagNoSyst[nJets - 1] = jetsBTag[nJets - 1];
			//			cout <<" jet no syst "<< nJets-1<<" pt "  <<jetsNoSyst[nJets-1].pt()<<endl;
		      }
		  }
		  
		  
		  if(passesPtLooseCut) {
		    ++nJetsLoose;
		    if ( fabs(eta) < 2.5)++nJetsLooseCentral;
		    else ++nJetsLooseForward;
		    if(passesCSVM) ++nJetsLooseMBTag;
		    ljets[nJetsLoose - 1] = math::PtEtaPhiELorentzVector(ptCorr, jetsEta->at(i), jetsPhi->at(i), energyCorr);
		    ljetsBTag[nJetsLoose - 1] = valueChosenAlgo;
		    lflavours[nJetsLoose - 1] = flavour;
		    if (ptCorr > maxLoosePtTree){
		      maxLoosePtTreePosition = nJetsLoose - 1;
		      maxLoosePtTree = ptCorr;
		      looseJetFlavourTree = flavour; }
		    
		    
		    // if(nJetsLoose>30) break;????
		  }
		  
		  if (!passesPtCut) continue;
		  
		  //max pt position:
		  //		  int pos = nJets - 1;
		  //		  cout << " j pt " << ptCorr << endl;
		  if (ptCorr > maxPtTree){
		    maxPtTreePosition = nJets - 1;
		    maxPtTree = ptCorr;
		    firstJetFlavourTree = flavour; }
		  //min pt position:
		  if (ptCorr < minPtTree) {
		    //		    minPtTreePosition = nJets - 1;
		    minPtTree = ptCorr;  }
		  
		  //Apply different SFs if it is b,c or light jet
		  setBTagWeights(ptCorr,fabs(eta),abs(flavour),is_btag_relevant,syst,channel);
		  
		  if (passesCSVT)++ncsvt_tags; if (passesCSVM)++ncsvm_tags; if (passesTCHPT)++ntchpt_tags;
		  
		  //		  bool passesAlgo = passesCSVT;
		  if(passesCSVM) ++ncsvl_tags;
		  //		  if (algo_ == "TCHPT" ) passesAlgo = passesTCHPT;
		  
		  //Condition to find the highest/lowest b-tag
		  //according to algo 1 (tchp)
		  //cout << " i "<< i <<" jets size "<< nJets << " btag  "<< valueAlgo1<<endl;
		  if (valueChosenAlgo >= highBTagTree) {
		    if (nJets==3){
		      mediumBTagTree = highBTagTree;
		      mediumBTagTreePosition = highBTagTreePosition;
		    }
		    if (nJets==4){ 
		      mediumlowBTagTree = mediumBTagTree;
		      mediumlowBTagTreePosition = mediumBTagTreePosition; 
		      mediumBTagTree = highBTagTree;
		      mediumBTagTreePosition = highBTagTreePosition;
		    }
		    highBTagTree = valueChosenAlgo;
		    highBTagTreePosition = nJets - 1;
		    bJetFlavourTree = jetsFlavour->at(i);
		    bJetPUID = jetsPileUpID->at(i);	bJetPUWP = jetsPileUpWP->at(i);
		    bJetBeta = jetsBeta->at(i); bJetDZ = jetsDZ->at(i); bJetRMS = jetsRMS->at(i);
		  }
		  if (valueChosenAlgo <= lowBTagTree)
		    {	 
		      mediumlowBTagTree = mediumBTagTree;
		      mediumlowBTagTreePosition = mediumBTagTreePosition;
		      if (nJets == 3){
			mediumBTagTree = lowBTagTree;
			mediumBTagTreePosition = lowBTagTreePosition;

		      }
		      if (nJets==4){ 
			mediumBTagTree = mediumlowBTagTree;
			mediumBTagTreePosition = mediumlowBTagTreePosition; 
			mediumlowBTagTree = lowBTagTree;
			mediumlowBTagTreePosition = lowBTagTreePosition;
			
		      }
		      lowBTagTree = valueChosenAlgo;
		      lowBTagTreePosition = nJets - 1;
		      fJetFlavourTree = jetsFlavour->at(i);
		      fJetPUID = jetsPileUpID->at(i);	fJetPUWP = jetsPileUpWP->at(i);
		      fJetBeta = jetsBeta->at(i); fJetDZ = jetsDZ->at(i); fJetRMS = jetsRMS->at(i);
		    }
		  
                  if ( (valueChosenAlgo == lowBTagTree) && (valueChosenAlgo == highBTagTree) && (nJets == 2 ) )
		    {
			highBTagTreePosition = nJets - 2; //two jets with same value
		    }
                  if ( (valueChosenAlgo == lowBTagTree) && (valueChosenAlgo == highBTagTree) && (valueChosenAlgo == mediumBTagTree) && (nJets == 3 ) )
		    {
			highBTagTreePosition = nJets - 3;
		    }

		  if  ( (valueChosenAlgo < highBTagTree) && (valueChosenAlgo > lowBTagTree)) // || ( (valueChosenAlgo == highBTagTree) || (valueChosenAlgo == lowBTagTree) ))
		    {
		      if (nJets == 3){
			mediumBTagTreePosition = nJets - 1;
			mediumBTagTree = valueChosenAlgo; }
		      if  (nJets==4){ 
			if(valueChosenAlgo < mediumBTagTree)  {
			  mediumlowBTagTreePosition = nJets - 1;
			  mediumlowBTagTree = valueChosenAlgo;
			}
			else{  //> or ==
			  mediumlowBTagTreePosition =mediumBTagTreePosition;
			  mediumlowBTagTree =mediumBTagTree; 
			  mediumBTagTreePosition = nJets - 1;
			  mediumBTagTree = valueChosenAlgo;
			}
			
		      }  
		    }
		  /*
		    cout << "i: "<< i  << "  nJets: " << nJets << "  nBJets csvt: " << ncsvt_tags << "  value: " << valueChosenAlgo
			 << "  high: "      << highBTagTree      << "  pos: " << highBTagTreePosition
			 << "  medium: "    << mediumBTagTree    << "  pos: " << mediumBTagTreePosition
			 << "  mediumlow: " << mediumlowBTagTree << "  pos: " << mediumlowBTagTreePosition
			 << "  low: "       << lowBTagTree       << "  pos: " << lowBTagTreePosition  <<endl;
		  */

		  

		  if (nJets >= 10 )break;
	  }  //cout<<"JetBtag ordering Done "<<endl;
        
	
	
	//If deltaR cut needed offline, apply here in the code
        if (passesLeptonStep == false)continue;
        eventFlavourTree = eventFlavour(channel, nb, nc, nudsg);
	
        /////////
        ///End of the standard lepton-jet loop
        /////////

	//Pile up weights
        if (doPU_) {
            if (!gotPU ) {
	      //	      cout << " before npv "<<endl;
                iEvent.getByLabel(n0_, n0);
                nVertices = *n0;
                gotPU = true;
            }
        }
        else(nVertices = -1);
        if (doPU_) {
            if (syst == "noSyst") {
                PUWeightNoSyst = pileUpSF(syst); PUWeight = PUWeightNoSyst;
                PUWeightTreePUUp = pileUpSF("PUUp");
                PUWeightTreePUDown = pileUpSF("PUDown");
		//		cout<< "n0 " << nVertices <<   " weight = "<< PUWeightNoSyst<< " cross-check "  <<endl;
            }
            else PUWeight = PUWeightNoSyst;
        }
        else PUWeight = 1;
        PUWeightTree = PUWeight;
        weightTree = Weight;

        /////////Fill jet trees:
        /////////
        ///This part does define the auxiliary quantities to fill the n-jets m-tags categories
        /////////

        if (isQCD) {
            leptonPFour = qcdLeptons[0];
            chargeTree = qcdLeptonsCharge->at(0) ;
        }
        else {  
            leptonPFour = leptons[0];
            chargeTree = leptonsCharge->at(0) ;
        }

        metPt = sqrt(metPx * metPx + metPy * metPy);
        MTWValue =  sqrt((leptonPFour.pt() + metPt) * (leptonPFour.pt() + metPt)  - (leptonPFour.px() + metPx) * (leptonPFour.px() + metPx) - (leptonPFour.py() + metPy) * (leptonPFour.py() + metPy));
        mtwMassTree = MTWValue;
        bool passesMet = false;
        runTree = iEvent.eventAuxiliary().run();
        lumiTree = iEvent.eventAuxiliary().luminosityBlock();
        eventTree = iEvent.eventAuxiliary().event();
        for (size_t J_ = 0; J_ < nJets; ++J_ )
        {
            double ptCorr = jets[J_].pt();
            if (ptCorr > secondPt &&  ptCorr < maxPtTree)
            {
                secondPt = ptCorr;
                secondPtPosition = J_ ;
                secondJetFlavourTree = flavours[J_];
            }
        }
        for (size_t J_ = 0; J_ < nJets; ++J_ )
        {
            double ptCorr = jets[J_].pt();
            if (ptCorr > thirdPt &&  ptCorr < secondPt)
            {
                thirdPt = ptCorr;
                thirdPtPosition = J_;
                thirdJetFlavourTree = flavours[J_];
	    }
        }
        for (size_t J_ = 0; J_ < nJets; ++J_ )
        {
            double ptCorr = jets[J_].pt();
            if (ptCorr > fourthPt &&  ptCorr < thirdPt)
            {
                fourthPt = ptCorr;
                fourthPtPosition = J_;
                fourthJetFlavourTree = flavours[J_];
	    }
        }
	if(secondPt < ptCutTight)  nJets = nJetsTight;  //this works for asymmetric cut, make njets=1 or 0 , in these case, trees are not saved at the end
	
	
	//	cout<<"nJetsLoose"<<nJetsLoose <<endl; 
	if(nJetsLoose > 0){
	  looseJetPt = ljets[maxLoosePtTreePosition].pt();
	  looseJetE = ljets[maxLoosePtTreePosition].energy();
	  looseJetEta = ljets[maxLoosePtTreePosition].eta();
	  looseJetPhi = ljets[maxLoosePtTreePosition].phi();
	  looseJetBTag = ljetsBTag[maxLoosePtTreePosition];
	}
	//if (thirdPt > secondPt ) cout << "  sanity check: Pt3 > Pt2 at event" << eventTree << " njets "<< nJets <<endl;
        //if (secondPt > maxPtTree ) cout << "  sanity check: Pt2 > Pt1 at event" << eventTree <<" njets "<< nJets <<endl;
        //if (thirdPt > maxPtTree ) cout << "  sanity check: Pt3 > Pt1 at event" << eventTree << " njets "<< nJets <<endl;
        if (nJetsTight > 0)
	  {
	    firstJetPt = jets[maxPtTreePosition].pt();
	    firstJetE = jets[maxPtTreePosition].energy();
	    firstJetEta = jets[maxPtTreePosition].eta();
	    firstJetPhi = jets[maxPtTreePosition].phi();
	    firstJetBTag = jetsBTag[maxPtTreePosition];
	    if (nJetsTight > 1)
	      {
		secondJetPt = jets[secondPtPosition].pt();
		secondJetE = jets[secondPtPosition].energy();
		secondJetEta = jets[secondPtPosition].eta();
		secondJetPhi = jets[secondPtPosition].phi();
		secondJetBTag = jetsBTag[secondPtPosition];
		
		if (nJets > 2)
		  {
		    thirdJetPt = jets[thirdPtPosition].pt();
		    thirdJetE = jets[thirdPtPosition].energy();
		    thirdJetEta = jets[thirdPtPosition].eta();
		    thirdJetPhi = jets[thirdPtPosition].phi();
		    thirdJetBTag = jetsBTag[thirdPtPosition];
		    //		    cout << "firstJetPt: " << firstJetPt << "  secondJetPt: " <<  secondJetPt << "  thirdJetPt: " << thirdJetPt << endl;

		  }
		if (nJets > 3)
		  {
		    fourthJetPt = jets[fourthPtPosition].pt();
		    fourthJetE = jets[fourthPtPosition].energy();
		    fourthJetEta = jets[fourthPtPosition].eta();
		    fourthJetPhi = jets[fourthPtPosition].phi();
		    fourthJetBTag = jetsBTag[fourthPtPosition];
		  }
		
	      }
	  }
        else
	  { firstJetFlavourTree = 0;  secondJetFlavourTree = 0;  thirdJetFlavourTree = 0;
            firstJetPt = 0;  firstJetE = 0;  firstJetEta = -99;  firstJetPhi = -99;firstJetBTag = -99;
	    secondJetPt = 0;  secondJetE = 0;   secondJetEta = -9;    secondJetPhi = -99;secondJetBTag= -99;
	    thirdJetPt = 0;  thirdJetE = 0;  thirdJetEta = -99;  thirdJetPhi = -99;thirdJetBTag = -99;
	    fourthJetPt = 0;  fourthJetE = 0;  fourthJetEta = -99;  fourthJetPhi = -99;fourthJetBTag = -99;
	  }
	
	
    
	//	cout<<" first sec third fourth " << endl;
	if(doJetTrees_)isQCDTree= isQCD;
        if (doJetTrees_ && !isQCD)
	  {
	    if (syst == "noSyst")
	      {
		if (leptonsFlavour_ == "muon" ) muonHLTSF(leptons[0].eta(),leptons[0].pt());
		if (leptonsFlavour_ == "electron" ) electronHLTSF(leptons[0].eta(),leptons[0].pt());
		
		lepPt = leptons[0].pt();
		
		if(doBTagSF_){w1TCHPT = b_tchpt_1_tag.weight(jsfshpt, ntchpt_tags);
		  w2TCHPT = b_tchpt_2_tags.weight(jsfshpt, ntchpt_tags);
		  w1CSVT = b_csvt_1_tag.weight(jsfscsvt, ncsvt_tags);
		  w2CSVT = b_csvt_2_tags.weight(jsfscsvt, ncsvt_tags);
		  w1CSVM = b_csvm_1_tag.weight(jsfscsvt, ncsvm_tags);
		  w2CSVM = b_csvm_2_tags.weight(jsfscsvt, ncsvm_tags);
		}
		nJ = nJets;
		nJNoPU = nJetsNoPU;
		
		nJCentralNoPU = nJetsCentralNoPU;
		nJCentral = nJetsCentral;
		
		nJForwardNoPU = nJetsForwardNoPU;
		nJForward = nJetsForward;
		
		if(addPDFToNJets){
		  iEvent.getByLabel(x1_, x1h);
		  iEvent.getByLabel(x2_, x2h);
		  
		  iEvent.getByLabel(scalePDF_, scalePDFh);
		  iEvent.getByLabel(id1_, id1h);
		  iEvent.getByLabel(id2_, id2h);
		  
		  x1 = *x1h;
		  x2 = *x2h;
		  
		  scalePDF = *scalePDFh;
		  
		  id1 = *id1h;
		  id2 = *id2h;
		  
		  LHAPDF::usePDFMember(1, 0);
		  double xpdf1 = LHAPDF::xfx(1, x1, scalePDF, id1);
		  double xpdf2 = LHAPDF::xfx(1, x2, scalePDF, id2);
		  double w0 = xpdf1 * xpdf2;
    
		  for (int p = 1; p <= 52; ++p)
		    {
		      LHAPDF::usePDFMember(1, p);
		      double xpdf1_new = LHAPDF::xfx(1, x1, scalePDF, id1);
		      double xpdf2_new = LHAPDF::xfx(1, x2, scalePDF, id2);
		      double pweight = xpdf1_new * xpdf2_new / w0;
		      pdf_weights[p - 1] = pweight;
		    }
		  LHAPDF::usePDFMember(2, 0);
		  double xpdf1_new = LHAPDF::xfx(2, x1, scalePDF, id1);
		  double xpdf2_new = LHAPDF::xfx(2, x2, scalePDF, id2);
		  pdf_weights_mstw= xpdf1_new * xpdf2_new / w0;
		  gotPDFs = true;
		} 
		treesNJets[syst]->Fill();
	      }
	  }
	if (doJetTrees_ && isQCD && doQCD_)
	  {
	    lepPt = qcdLeptons[0].pt();
	    lepEta = qcdLeptons[0].eta();
	    lepPhi = qcdLeptons[0].phi();
            lepE = qcdLeptons[0].energy();
	    nJ = nJets;
	    treesNJets[syst]->Fill();
	  }
	
        nJLoose = nJetsLoose;
        nJLooseCentral = nJetsLooseCentral;
        nJLooseForward = nJetsLooseForward;
        nJLooseMBTag = nJetsLooseMBTag;

	//	cout << "syst before is: "<< syst_name <<endl;

        ntight_tags = ncsvt_tags;
        if (algo_ == "TCHPT")ntight_tags = ntchpt_tags;
        if ( nJetsTight < 2 )continue;
	//        if (nJets > 3)continue; // I remove it to have 4j...trees
        if (nJets > 4)continue; // I add it to have 4j...trees

	//	cout << "syst after is: "<< syst_name <<endl;
    
	//Here we fill the trees for 2- and 3- jets and 0-2 tags.
	//LEGENDA for the value of B used in the following  
        //    0T = 0;
        //    1T = 1;
        //    2T = 2;
        //    0T_QCD=3;
        //    1T_QCD=4;
	//    2T_QCD=5;
        if (nJets == 2 || nJets == 3 || nJets == 4 ) 
	  {
	    int B;
	    if (ntight_tags == 0) B = 0 ;
	    else if (ntight_tags == 1)B = 1;
	    else if (ntight_tags == 2)B = 2;
	    else continue;
	    if(lepRhoCorrectedRelIso>0.1){
	      //	    cout<< "rho corr rel iso is: " <<lepRhoCorrectedRelIso<< " leptons size "<<nLeptons<< " B is " << B << " nJets is "  << nJets << " is qcd? "<< isQCD << " passes lepton? "<< passesLeptonStep <<endl;
	    }
	    
	    if (isQCD)
	      {
		B += 3;
	      }
	    
	    if ( syst == "noSyst" && nJets == 2 && B < 3)
	      {
		++passingJets;
	      }
	    
	    if ( (B == 0 || B == 3 ) && (ntchpt_tags != 0  || lowBTagTreePosition < 0 || lowBTagTreePosition == highBTagTreePosition) ) continue; //Sample A condition, ok for now
	    
	    if(doLooseBJetVeto_)if(nJets==2 && (B == 1 || B==4))if( ncsvl_tags != 1 )continue;
	    
	    //  cout << "test before bweight "<<endl;
	    
	    
	    if (syst == "noSyst")
	      {
		bWeightNoSyst = bTagSF(B);  bWeightTree = bWeightNoSyst;
		bWeightTreeBTagUp = bTagSF(B, "BTagUp");
		bWeightTreeBTagDown = bTagSF(B, "BTagDown");
		bWeightTreeMisTagUp = bTagSF(B, "MisTagUp");
		bWeightTreeMisTagDown = bTagSF(B, "MisTagDown");
	      }
	    else if (syst == "JESUp" || syst == "JESDown" ||
		     syst == "JERUp" || syst == "JERDown" ||
		     syst == "BTagUp" || syst == "BTagDown" ||
		     syst == "MisTagUp" || syst == "MisTagDown" ) bWeightTree = bTagSF(B);
	    else bWeightTree = bWeightNoSyst;
	    
	    //	  cout << "test before pdf "<<endl;
	    
	    if (syst == "noSyst" && doPDF_ )
	      {
		if (channel != "Data" && !gotPDFs)
		  {
		    iEvent.getByLabel(x1_, x1h);
		    iEvent.getByLabel(x2_, x2h);
		    
		    iEvent.getByLabel(scalePDF_, scalePDFh);
		    iEvent.getByLabel(id1_, id1h);
		    iEvent.getByLabel(id2_, id2h);
		    
		    x1 = *x1h;
		    x2 = *x2h;
		    
		    scalePDF = *scalePDFh;
		    
		    id1 = *id1h;
		    id2 = *id2h;
		    
		    //Q2 = x1 * x2 * 7000*7000;	
		    LHAPDF::usePDFMember(1, 0);
		    double xpdf1 = LHAPDF::xfx(1, x1, scalePDF, id1);
		    double xpdf2 = LHAPDF::xfx(1, x2, scalePDF, id2);
		    double w0 = xpdf1 * xpdf2;
		    //		    cout << "scale " << scalePDF<< " x1 "<< x1 <<" x2 "<< x2 <<endl;	
		    
		    //		  cout << "before error loop"<<endl;
		    for (int p = 1; p <= 52; ++p)
		      {
			LHAPDF::usePDFMember(1, p);
			double xpdf1_new = LHAPDF::xfx(1, x1, scalePDF, id1);
			double xpdf2_new = LHAPDF::xfx(1, x2, scalePDF, id2);
			double pweight = xpdf1_new * xpdf2_new / w0;
			pdf_weights[p - 1] = pweight;
		      }
		    //		  cout << "before second member"<<endl;
		    LHAPDF::usePDFMember(2, 0);
		    double xpdf1_new = LHAPDF::xfx(2, x1, scalePDF, id1);
		    double xpdf2_new = LHAPDF::xfx(2, x2, scalePDF, id2);
		    pdf_weights_mstw= xpdf1_new * xpdf2_new / w0;
		  }
	      }
	    
            if ( syst == "noSyst" && nJets == 2)
	      {
		if (leptonsFlavour_ == "muon" && MTWValue > 40 && B < 3 )
		  {
		    ++passingMET;
		    passesMet = true;
		  }
		if (leptonsFlavour_ == "electron" && metPt > 35 && B < 3)
		  {
		    ++passingMET;
		    passesMet = true;
		  }
		
		
		if ( B == 1 && passesMet)
		  ++passingBJets;
	      }
	    
	    //Top and costhetastar reconstruction
	    //	    cout << "test before top reco"<<endl;
	    math::PtEtaPhiELorentzVector top;
	    math::PtEtaPhiELorentzVector top1;
	    math::PtEtaPhiELorentzVector top2;
	    float fCosThetaLJ= 99999;
	    float fCosThetaLJ1 = 99999;
	    float fCosThetaLJ2 = 99999;
	    
	    float topmass_h,topmass_m ;
            if(!doTopBestMass_) {
	      //	      cout<<"!doTopBestMass_ "<<!doTopBestMass_ <<endl;
	      top = top4Momentum(leptonPFour, jets[highBTagTreePosition], metPx, metPy);
	      top1 = top;
	      top2 = top;
	      fCosThetaLJ =  cosThetaLJ(leptonPFour, jets[lowBTagTreePosition], top);
	      cosBLTree =  cosTheta_eta_bl(leptonPFour, jets[lowBTagTreePosition], top);
	    }
	    
            if(doTopBestMass_) {           
	      if(B == 1 || B==4){  //cout<<"!doTopBestMass_B1 "<<!doTopBestMass_ <<endl;
		
		if (nJets== 2 ){
		  math::PtEtaPhiELorentzVector top_h = top4Momentum(leptonPFour, jets[highBTagTreePosition], metPx, metPy);
		  math::PtEtaPhiELorentzVector top_l = top4Momentum(leptonPFour, jets[lowBTagTreePosition], metPx, metPy);		
		  top1 = top_h; 
		  top2 = top_l; 
		  topmass_h = top_h.mass(); 
		  topmass_m = top_l.mass();
		  bJetDecay= (fabs(topmass_h -172.5) < fabs(topmass_m-172.5))?jets[highBTagTreePosition]:jets[lowBTagTreePosition];
 		  bJetDecayFlavour = (fabs(topmass_h -172.5) < fabs(topmass_m-172.5))?flavours[highBTagTreePosition]:flavours[lowBTagTreePosition];
 		  bJetDecayBTag = (fabs(topmass_h -172.5) < fabs(topmass_m-172.5))?jetsBTag[highBTagTreePosition]:jetsBTag[lowBTagTreePosition];
		  bJetRecoil= (fabs(topmass_h -172.5) < fabs(topmass_m-172.5))?jets[lowBTagTreePosition]:jets[highBTagTreePosition];
		  bJetRecoilFlavour = (fabs(topmass_h -172.5) < fabs(topmass_m-172.5))?flavours[lowBTagTreePosition]:flavours[highBTagTreePosition];
		  bJetRecoilBTag = (fabs(topmass_h -172.5) < fabs(topmass_m-172.5))?jetsBTag[lowBTagTreePosition]:jetsBTag[highBTagTreePosition];
		}
		if (nJets== 3|| nJets==4 ){
		  math::PtEtaPhiELorentzVector top_h = top4Momentum(leptonPFour, jets[highBTagTreePosition], metPx, metPy);
		  math::PtEtaPhiELorentzVector top_m = top4Momentum(leptonPFour, jets[mediumBTagTreePosition], metPx, metPy);		
		  top1 = top_h;
		  top2 = top_m;
		  topmass_h = top_h.mass(); 
		  topmass_m = top_m.mass();
		  bJetDecay= (fabs(topmass_h -172.5) < fabs(topmass_m-172.5))?jets[highBTagTreePosition]:jets[mediumBTagTreePosition];
 		  bJetDecayFlavour = (fabs(topmass_h -172.5) < fabs(topmass_m-172.5))?flavours[highBTagTreePosition]:flavours[mediumBTagTreePosition];
 		  bJetDecayBTag = (fabs(topmass_h -172.5) < fabs(topmass_m-172.5))?jetsBTag[highBTagTreePosition]:jetsBTag[mediumBTagTreePosition];
		  bJetRecoil= (fabs(topmass_h -172.5) < fabs(topmass_m-172.5))?jets[mediumBTagTreePosition]:jets[highBTagTreePosition];
		  bJetRecoilFlavour = (fabs(topmass_h -172.5) < fabs(topmass_m-172.5))?flavours[mediumBTagTreePosition]:flavours[highBTagTreePosition];
		  bJetRecoilBTag = (fabs(topmass_h -172.5) < fabs(topmass_m-172.5))?jetsBTag[mediumBTagTreePosition]:jetsBTag[highBTagTreePosition];
		}
		top = top1;  // only 1 bjet
		
		fCosThetaLJ =  cosThetaLJ(leptonPFour, jets[lowBTagTreePosition], top);
		cosBLTree =  cosTheta_eta_bl(leptonPFour, jets[lowBTagTreePosition], top);
		
		fCosThetaLJ1 = cosThetaLJ(leptonPFour, jets[lowBTagTreePosition], top1);
		cos1BLTree =   cosTheta_eta_bl(leptonPFour, jets[lowBTagTreePosition], top1);
		
		fCosThetaLJ2 = cosThetaLJ(leptonPFour, jets[lowBTagTreePosition], top2);
		cos2BLTree =   cosTheta_eta_bl(leptonPFour, jets[lowBTagTreePosition], top2);
		
		//		cout<<"fCosThetaLJ" <<fCosThetaLJ<<"topmass" << top.mass()<<endl;
		//   cout<<"jets[lowBTagTreePosition].Pt()"<< jets[lowBTagTreePosition].Pt()<<endl;
	      }
	      else if(B==2 || B ==5) { // cout<<"!doTopBestMass_B2 "<<!doTopBestMass_ <<endl;
		math::PtEtaPhiELorentzVector top_h, top_m ;
		if(nJets==2){
		  math::PtEtaPhiELorentzVector top_h = top4Momentum(leptonPFour, jets[highBTagTreePosition], metPx, metPy);
		  math::PtEtaPhiELorentzVector top_m = top4Momentum(leptonPFour, jets[lowBTagTreePosition], metPx, metPy);
		  topmass_h = top_h.mass(); 
		  topmass_m = top_m.mass();
		  top = (fabs(topmass_h -172.5) < fabs(topmass_m-172.5))? top_h: top_m;
		  top1 = top_h;
		  top2 = top_m;
		  bJetDecay= (fabs(topmass_h -172.5) < fabs(topmass_m-172.5))?jets[highBTagTreePosition]:jets[lowBTagTreePosition];
 		  bJetDecayFlavour = (fabs(topmass_h -172.5) < fabs(topmass_m-172.5))?flavours[highBTagTreePosition]:flavours[lowBTagTreePosition];
 		  bJetDecayBTag = (fabs(topmass_h -172.5) < fabs(topmass_m-172.5))?jetsBTag[highBTagTreePosition]:jetsBTag[lowBTagTreePosition];
		  bJetRecoil= (fabs(topmass_h -172.5) < fabs(topmass_m-172.5))?jets[lowBTagTreePosition]:jets[highBTagTreePosition];
		  bJetRecoilFlavour = (fabs(topmass_h -172.5) < fabs(topmass_m-172.5))?flavours[lowBTagTreePosition]:flavours[highBTagTreePosition];
		  bJetRecoilBTag = (fabs(topmass_h -172.5) < fabs(topmass_m-172.5))?jetsBTag[lowBTagTreePosition]:jetsBTag[highBTagTreePosition];

		  //  cout<<"top_h, top_m, top"<< topmass_h<<topmass_m<<top.mass()<<endl;
		  if(fabs(topmass_h -172.5) < fabs(topmass_m-172.5)){
		    fCosThetaLJ =  cosThetaLJ(leptonPFour, jets[lowBTagTreePosition], top);
		    cosBLTree =  cosTheta_eta_bl(leptonPFour, jets[lowBTagTreePosition], top);}
		  else {
		    fCosThetaLJ =  cosThetaLJ(leptonPFour, jets[highBTagTreePosition], top);
		    cosBLTree =  cosTheta_eta_bl(leptonPFour, jets[highBTagTreePosition], top);}
		  //  cout<<"fCosThetaLJ" <<fCosThetaLJ<<"topmass_h" <<topmass_h <<endl;
		  //  cout<<"jets[lowBTagTreePosition].Pt()"<< jets[lowBTagTreePosition].Pt()<<endl;

		  fCosThetaLJ1 =  cosThetaLJ(leptonPFour, jets[lowBTagTreePosition], top1);
		  cos1BLTree =  cosTheta_eta_bl(leptonPFour, jets[lowBTagTreePosition], top1);
	  
		  //fCosThetaLJ2 =  cosThetaLJ(leptonPFour, jets[lowBTagTreePosition], top2);
		  //cos2BLTree =  cosTheta_eta_bl(leptonPFour, jets[lowBTagTreePosition], top2);
          fCosThetaLJ2 =  cosThetaLJ(leptonPFour, jets[highBTagTreePosition], top2);
		  cos2BLTree =  cosTheta_eta_bl(leptonPFour, jets[highBTagTreePosition], top2);
		
		}
		else if( (nJets==3 || nJets==4)  ){ //cout<<"nJets==4 ,3"<<endl;
		  math::PtEtaPhiELorentzVector top_h = top4Momentum(leptonPFour, jets[highBTagTreePosition], metPx, metPy);
		  math::PtEtaPhiELorentzVector top_m = top4Momentum(leptonPFour, jets[mediumBTagTreePosition], metPx, metPy);
		  topmass_h = top_h.mass();
		  topmass_m = top_m.mass();
		  top = (fabs(topmass_h -172.5) < fabs(topmass_m-172.5))? top_h: top_m;
		  top1 = top_h;
		  top2 = top_m;
		  fCosThetaLJ =  cosThetaLJ(leptonPFour, jets[lowBTagTreePosition], top); //low BTag is not contrbiute in top 
		  cosBLTree =  cosTheta_eta_bl(leptonPFour, jets[lowBTagTreePosition], top);
		
		  fCosThetaLJ1 =  cosThetaLJ(leptonPFour, jets[lowBTagTreePosition], top1);
		  cos1BLTree =  cosTheta_eta_bl(leptonPFour, jets[lowBTagTreePosition], top1);
		  
		  fCosThetaLJ2 =  cosThetaLJ(leptonPFour, jets[lowBTagTreePosition], top2);
		  cos2BLTree =  cosTheta_eta_bl(leptonPFour, jets[lowBTagTreePosition], top2);
		  
		  //  cout<<"fCosThetaLJ" <<fCosThetaLJ <<"topmass_h" <<topmass_h <<endl;
		  //  cout<<"jets[lowBTagTreePosition].Pt()"<< jets[lowBTagTreePosition].Pt()<<endl;
		}
	      }
	      else if( B == 0 || B == 3 ){
		if (nJets == 2){
		  math::PtEtaPhiELorentzVector top_h = top4Momentum(leptonPFour, jets[highBTagTreePosition], metPx, metPy);
		  math::PtEtaPhiELorentzVector top_m = top4Momentum(leptonPFour, jets[lowBTagTreePosition], metPx, metPy);
		  topmass_h = top_h.mass();
		  topmass_m = top_m.mass();
		  top = (fabs(topmass_h -172.5) < fabs(topmass_m-172.5))? top_h: top_m;
		  top1 = top_h;
		  top2 = top_m;
 		  bJetDecay= (fabs(topmass_h -172.5) < fabs(topmass_m-172.5))?jets[highBTagTreePosition]:jets[lowBTagTreePosition];
 		  bJetDecayFlavour = (fabs(topmass_h -172.5) < fabs(topmass_m-172.5))?flavours[highBTagTreePosition]:flavours[lowBTagTreePosition];
 		  bJetDecayBTag = (fabs(topmass_h -172.5) < fabs(topmass_m-172.5))?jetsBTag[highBTagTreePosition]:jetsBTag[lowBTagTreePosition];
		  bJetRecoil= (fabs(topmass_h -172.5) < fabs(topmass_m-172.5))?jets[lowBTagTreePosition]:jets[highBTagTreePosition];
		  bJetRecoilFlavour = (fabs(topmass_h -172.5) < fabs(topmass_m-172.5))?flavours[lowBTagTreePosition]:flavours[highBTagTreePosition];
		  bJetRecoilBTag = (fabs(topmass_h -172.5) < fabs(topmass_m-172.5))?jetsBTag[lowBTagTreePosition]:jetsBTag[highBTagTreePosition];
		  
                  if(fabs(topmass_h -172.5) < fabs(topmass_m-172.5)){
                    fCosThetaLJ =  cosThetaLJ(leptonPFour, jets[lowBTagTreePosition], top);
                    cosBLTree =  cosTheta_eta_bl(leptonPFour, jets[lowBTagTreePosition], top);}
                  else {
                    fCosThetaLJ =  cosThetaLJ(leptonPFour, jets[highBTagTreePosition], top);
                    cosBLTree =  cosTheta_eta_bl(leptonPFour, jets[highBTagTreePosition], top);}
		  
		  fCosThetaLJ1 =  cosThetaLJ(leptonPFour, jets[lowBTagTreePosition], top1);
		  cos1BLTree =  cosTheta_eta_bl(leptonPFour, jets[lowBTagTreePosition], top1);
		  
		  //fCosThetaLJ2 =  cosThetaLJ(leptonPFour, jets[lowBTagTreePosition], top2);
		  //cos2BLTree =  cosTheta_eta_bl(leptonPFour, jets[lowBTagTreePosition], top2);
		  fCosThetaLJ2 =  cosThetaLJ(leptonPFour, jets[highBTagTreePosition], top2);
		  cos2BLTree =  cosTheta_eta_bl(leptonPFour, jets[highBTagTreePosition], top2);
		  
		  
		}
		else if (nJets==3 || nJets==4){  //cout<<"nJets==4 ,3"<<endl;
		  math::PtEtaPhiELorentzVector top_h = top4Momentum(leptonPFour, jets[highBTagTreePosition], metPx, metPy);
		  math::PtEtaPhiELorentzVector top_m = top4Momentum(leptonPFour, jets[mediumBTagTreePosition], metPx, metPy);
		  topmass_h = top_h.mass();
		  topmass_m = top_m.mass();
		  top = (fabs(topmass_h -172.5) < fabs(topmass_m-172.5))? top_h: top_m;
		  top1 = top_h;
		  top2 = top_m;
		  
		  fCosThetaLJ =  cosThetaLJ(leptonPFour, jets[lowBTagTreePosition], top);
		  cosBLTree =  cosTheta_eta_bl(leptonPFour, jets[lowBTagTreePosition], top);
		  //  cout<<"fCosThetaLJ" <<fCosThetaLJ <<"topmass_h" <<topmass_h <<endl;
		  //  cout<<"jets[lowBTagTreePosition].Pt()"<< jets[lowBTagTreePosition].Pt()<<endl;
		  fCosThetaLJ1 =  cosThetaLJ(leptonPFour, jets[lowBTagTreePosition], top1);
		  cos1BLTree =  cosTheta_eta_bl(leptonPFour, jets[lowBTagTreePosition], top1);
		  
		  fCosThetaLJ2 =  cosThetaLJ(leptonPFour, jets[lowBTagTreePosition], top2);
		  cos2BLTree =  cosTheta_eta_bl(leptonPFour, jets[lowBTagTreePosition], top2);
		  
		}
	      }
	    }
	    
	    bjets[0] = jets[highBTagTreePosition];
	    bjets_flavours[0] = flavours[highBTagTreePosition];
	    if(nJets== 2){
	      bjets[1] = jets[lowBTagTreePosition];
	      bjets_flavours[1] = flavours[lowBTagTreePosition];
	    }
	    else if (nJets== 3 ||nJets== 4 ){
	      bjets[1] = jets[mediumBTagTreePosition];
	      bjets_flavours[1] = flavours[mediumBTagTreePosition];
	    }
	    
	    double Mlb1, Mlb2, Mb1b2, pTb1b2;
	    if(bjets[0].pt() > bjets[1].pt()){
	      
	      Mlb1 = (leptonPFour+bjets[0]).mass();
	      Mlb2 = (leptonPFour+bjets[1]).mass();
	      bJet1Pt      = bjets[0].pt();
	      bJet1E       = bjets[0].energy();
	      bJet1Eta     = bjets[0].eta();
	      bJet1Phi     = bjets[0].phi();
	      bJet1Flavour = bjets_flavours[0];
          bJet1BTag    = jetsBTag[highBTagTreePosition];
	      
	      bJet2Pt      = bjets[1].pt();
	      bJet2E       = bjets[1].energy();
	      bJet2Eta     = bjets[1].eta();
	      bJet2Phi     = bjets[1].phi();
	      bJet2Flavour = bjets_flavours[1];
          if(nJets== 2)                   bJet2BTag    = jetsBTag[lowBTagTreePosition];
          else if(nJets== 3 ||nJets== 4 ) bJet2BTag    = jetsBTag[mediumBTagTreePosition];
	     }
	    else{
	      Mlb1 = (leptonPFour+bjets[1]).mass();
	      Mlb2 = (leptonPFour+bjets[0]).mass();
	      bJet1Pt      = bjets[1].pt();
	      bJet1E       = bjets[1].energy();
	      bJet1Eta     = bjets[1].eta();
	      bJet1Phi     = bjets[1].phi();
	      bJet1Flavour = bjets_flavours[1];
          if(nJets== 2)                   bJet1BTag    = jetsBTag[lowBTagTreePosition];
          else if(nJets== 3 ||nJets== 4 ) bJet1BTag    = jetsBTag[mediumBTagTreePosition];

	      
	      bJet2Pt      = bjets[0].pt();
	      bJet2E       = bjets[0].energy();
	      bJet2Eta     = bjets[0].eta();
	      bJet2Phi     = bjets[0].phi();
	      bJet2Flavour = bjets_flavours[0];
          bJet2BTag    = jetsBTag[highBTagTreePosition];

	    }
	    Mb1b2  = (bjets[0] + bjets[1]).mass();
	    pTb1b2 = (bjets[0] + bjets[1]).pt();
	    
	    Mb1b2Tree  = Mb1b2;
	    pTb1b2Tree = pTb1b2;
	    Mlb1Tree = Mlb1;
	    Mlb2Tree = Mlb2;
		
        bJetDecayPt   = bJetDecay.pt();
		bJetDecayE   = bJetDecay.energy();
		bJetDecayPhi   = bJetDecay.phi();
		bJetDecayEta  = bJetDecay.eta();

		bJetRecoilPt   = bJetRecoil.pt();
   		bJetRecoilE   = bJetRecoil.energy();
   		bJetRecoilPhi   = bJetRecoil.phi();
   		bJetRecoilEta   = bJetRecoil.eta();

            etaTree = fabs(jets[lowBTagTreePosition].eta());
            cosTree = fCosThetaLJ;
            cos1Tree = fCosThetaLJ1;
            cos2Tree = fCosThetaLJ2;
	    
	    topMassTree = top.mass();
        top1MassTree = top1.mass();        
	    top2MassTree = top2.mass();

	    
            topMtwTree = topMtw(leptonPFour, jets[highBTagTreePosition], metPx, metPy);
	    
	    
            lepPt = leptonPFour.pt();
            lepEta = leptonPFour.eta();
            lepPhi = leptonPFour.phi();
            lepE = leptonPFour.energy();
	    if (leptonsFlavour_ == "muon" )muonHLTSF(leptons[0].eta(),leptons[0].pt());
	    if (leptonsFlavour_ == "electron" )electronHLTSF(leptons[0].eta(),leptons[0].pt());
	    
            bJetPt = jets[highBTagTreePosition].pt();
            bJetE = jets[highBTagTreePosition].energy();
            bJetEta = jets[highBTagTreePosition].eta();
            bJetPhi = jets[highBTagTreePosition].phi();
            bJetBTag = jetsBTag[highBTagTreePosition];
	    
            fJetPt = jets[lowBTagTreePosition].pt();
            fJetE = jets[lowBTagTreePosition].energy();
            fJetEta = jets[lowBTagTreePosition].eta();
            fJetPhi = jets[lowBTagTreePosition].phi();
            fJetBTag = jetsBTag[lowBTagTreePosition];
	    
            etaTree = fabs(jets[lowBTagTreePosition].eta());
            etaTree2 = fabs(jets[highBTagTreePosition].eta());
            cosTree = fCosThetaLJ;
            cos1Tree = fCosThetaLJ1;
            cos2Tree = fCosThetaLJ2;
	    
            topEta = top.eta();
            topPhi = top.phi();
	    topPt = top.pt();
	    topE = top.E();
            
	    top1Eta = top1.eta();
            top1Phi = top1.phi();
            top1Pt = top1.pt();
            top1E = top1.E();

	    top2Eta = top2.eta();
            top2Phi = top2.phi();
            top2Pt = top2.pt();
            top2E = top2.E();
	    
	    //	    cout << "test before mcTruth"<<endl;
	    
	    if((B==1 || B==2) && nJets ==2 && syst == "noSyst" && doMCTruth_ && ! doFullMCTruth_){ 
	      fillMCTruth(iEvent);
	      treesMCTruth[syst]->Fill();  	 //     cout<<" treesMCTruthEntries() 1 or 2 bjets      "<<treesMCTruth[syst]->GetEntries()<<endl;       
	    }

	    if (nJets == 2)
	      {
		//		cout << " B is "<< B<< " syst is "<<syst_name <<endl;
		//		cout<< " tree name "<< trees2J[B][syst_name]->GetName() <<endl;
		trees2J[B][syst_name]->Fill();
	      }
            if (nJets == 3)
	      {
		//cout << " B is "<< B<< " syst is "<<syst_name <<endl;
		//cout << " tree name "<< trees3J[B][syst_name]->GetName() <<endl;
                trees3J[B][syst_name]->Fill();
	      }
	    if (nJets == 4)  trees4J[B][syst_name]->Fill();
	    
	    }
	  }
    }

////End of main per-event loop

////Functions for the reconstruction of kinematic variables:

//CosThetalj given top quark, lepton and light jet
float SingleTopSystematicsTreesDumper::cosThetaLJ(math::PtEtaPhiELorentzVector lepton, math::PtEtaPhiELorentzVector jet, math::PtEtaPhiELorentzVector top)
{

    math::PtEtaPhiELorentzVector boostedLepton = ROOT::Math::VectorUtil::boost(lepton, top.BoostToCM());
    math::PtEtaPhiELorentzVector boostedJet = ROOT::Math::VectorUtil::boost(jet, top.BoostToCM());

    return  ROOT::Math::VectorUtil::CosTheta(boostedJet.Vect(), boostedLepton.Vect());

}
//CosTheta-lepton-beam-line, implementation by Joosep Pata
float SingleTopSystematicsTreesDumper::cosTheta_eta_bl(math::PtEtaPhiELorentzVector lepton, math::PtEtaPhiELorentzVector jet, math::PtEtaPhiELorentzVector top)
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

double SingleTopSystematicsTreesDumper::topMtw(math::PtEtaPhiELorentzVector lepton, math::PtEtaPhiELorentzVector jet, float metPx, float metPy)
{
    math::PtEtaPhiELorentzVector lb = lepton + jet;
    double mlb2 = lb.mass() * lb.mass();
    double etlb = sqrt(mlb2 + lb.pt() * lb.pt());
    double metPT = sqrt(metPx * metPx + metPy * metPy);

    return sqrt( mlb2 + 2 * ( etlb * metPT - lb.px() * metPx - lb.py() * metPy ) );
}

//top quark 4-momentum given lepton, met and b-jet
math::PtEtaPhiELorentzVector SingleTopSystematicsTreesDumper::top4Momentum(math::PtEtaPhiELorentzVector lepton, math::PtEtaPhiELorentzVector jet, float metPx, float metPy)
{
    return top4Momentum(lepton.px(), lepton.py(), lepton.pz(), lepton.energy(), jet.px(), jet.py(), jet.pz(), jet.energy(), metPx, metPy);
}

//top quark 4-momentum original function given the necessary parameters
math::PtEtaPhiELorentzVector SingleTopSystematicsTreesDumper::top4Momentum(float leptonPx, float leptonPy, float leptonPz, float leptonE, float jetPx, float jetPy, float jetPz, float jetE, float metPx, float metPy)
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
//To solve this: put mtw = mw
//Solve the equations
//In this way we must
//drop the constraints px_Nu = MET_x and py_Nu = MET_y
//Solve this by chosing the px_Nu and py_Nu that
//minimize the distance from the MET in the px-py plane
//Such minimization can be done analytically with derivatives
//and much patience. Here we exploit such analytical minimization
/////
//More detailed inline description: work in progress!
math::XYZTLorentzVector SingleTopSystematicsTreesDumper::NuMomentum(float leptonPx, float leptonPy, float leptonPz, float leptonPt, float leptonE, float metPx, float metPy )
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
	//        nNuSol = 2;

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


////Function for getting MC truth observables:

void SingleTopSystematicsTreesDumper::fillMCTruth(const Event &iEvent ){
    iEvent.getByLabel(MCTopQuarksEta_, MCTopQuarksEta); iEvent.getByLabel(MCTopQuarksPt_, MCTopQuarksPt); iEvent.getByLabel(MCTopQuarksPhi_, MCTopQuarksPhi); iEvent.getByLabel(MCTopQuarksEnergy_, MCTopQuarksEnergy); iEvent.getByLabel(MCTopQuarksMotherId_, MCTopQuarksMotherId);
    
    iEvent.getByLabel(MCTopQuarkBarsEta_, MCTopQuarkBarsEta); iEvent.getByLabel(MCTopQuarkBarsPt_, MCTopQuarkBarsPt); iEvent.getByLabel(MCTopQuarkBarsPhi_, MCTopQuarkBarsPhi); iEvent.getByLabel(MCTopQuarkBarsEnergy_, MCTopQuarkBarsEnergy); iEvent.getByLabel(MCTopQuarkBarsMotherId_, MCTopQuarkBarsMotherId);
    
    iEvent.getByLabel(MCTopLeptonsEta_, MCTopLeptonsEta); iEvent.getByLabel(MCTopLeptonsPt_, MCTopLeptonsPt); iEvent.getByLabel(MCTopLeptonsPhi_, MCTopLeptonsPhi); iEvent.getByLabel(MCTopLeptonsEnergy_, MCTopLeptonsEnergy); iEvent.getByLabel(MCTopLeptonsMotherId_, MCTopLeptonsMotherId);
    
    iEvent.getByLabel(MCTopNeutrinosEta_, MCTopNeutrinosEta); iEvent.getByLabel(MCTopNeutrinosPt_, MCTopNeutrinosPt); iEvent.getByLabel(MCTopNeutrinosPhi_, MCTopNeutrinosPhi); iEvent.getByLabel(MCTopNeutrinosEnergy_, MCTopNeutrinosEnergy); iEvent.getByLabel(MCTopNeutrinosMotherId_, MCTopNeutrinosMotherId);
    
    iEvent.getByLabel(MCTopBQuarksEta_, MCTopBQuarksEta); iEvent.getByLabel(MCTopBQuarksPt_, MCTopBQuarksPt); iEvent.getByLabel(MCTopBQuarksPhi_, MCTopBQuarksPhi); iEvent.getByLabel(MCTopBQuarksEnergy_, MCTopBQuarksEnergy); iEvent.getByLabel(MCTopBQuarksMotherId_, MCTopBQuarksMotherId);
    
    iEvent.getByLabel(MCTopWsEta_, MCTopWsEta); iEvent.getByLabel(MCTopWsPt_, MCTopWsPt); iEvent.getByLabel(MCTopWsPhi_, MCTopWsPhi); iEvent.getByLabel(MCTopWsEnergy_, MCTopWsEnergy); iEvent.getByLabel(MCTopWsDauOneId_, MCTopWsDauOneId);
    
    
    
    iEvent.getByLabel(MCLeptonsEta_, MCLeptonsEta); iEvent.getByLabel(MCLeptonsPt_, MCLeptonsPt); iEvent.getByLabel(MCLeptonsPhi_, MCLeptonsPhi); iEvent.getByLabel(MCLeptonsEnergy_, MCLeptonsEnergy);
    iEvent.getByLabel(MCNeutrinosEta_, MCNeutrinosEta); iEvent.getByLabel(MCNeutrinosPt_, MCNeutrinosPt); iEvent.getByLabel(MCNeutrinosPhi_, MCNeutrinosPhi); iEvent.getByLabel(MCNeutrinosEnergy_, MCNeutrinosEnergy);
    iEvent.getByLabel(MCBQuarksEta_, MCBQuarksEta); iEvent.getByLabel(MCBQuarksPt_, MCBQuarksPt); iEvent.getByLabel(MCBQuarksPhi_, MCBQuarksPhi); iEvent.getByLabel(MCBQuarksEnergy_, MCBQuarksEnergy);
    iEvent.getByLabel(MCQuarksEta_, MCQuarksEta); iEvent.getByLabel(MCQuarksPt_, MCQuarksPt); iEvent.getByLabel(MCQuarksPhi_, MCQuarksPhi); iEvent.getByLabel(MCQuarksEnergy_, MCQuarksEnergy);
    
    iEvent.getByLabel(MCTopBQuarksPdgId_, MCTopBQuarksPdgId);iEvent.getByLabel(MCTopWsPdgId_, MCTopWsPdgId);
    iEvent.getByLabel(MCTopQuarksPdgId_, MCTopQuarksPdgId);iEvent.getByLabel(MCTopsPdgId_, MCTopsPdgId);
    iEvent.getByLabel(MCTopQuarkBarsPdgId_, MCTopQuarkBarsPdgId);
    iEvent.getByLabel(MCTopLeptonsPdgId_, MCTopLeptonsPdgId);
    iEvent.getByLabel(MCTopNeutrinosPdgId_, MCTopNeutrinosPdgId);
    
    iEvent.getByLabel(MCBQuarksPdgId_, MCBQuarksPdgId); iEvent.getByLabel(MCQuarksPdgId_, MCQuarksPdgId);
    iEvent.getByLabel(MCLeptonsPdgId_, MCLeptonsPdgId); iEvent.getByLabel(MCNeutrinosPdgId_, MCNeutrinosPdgId);
    
    iEvent.getByLabel(MCBQuarksMotherId_, MCBQuarksMotherId); iEvent.getByLabel(MCQuarksMotherId_, MCQuarksMotherId);
    iEvent.getByLabel(MCLeptonsMotherId_, MCLeptonsMotherId); iEvent.getByLabel(MCNeutrinosMotherId_, MCNeutrinosMotherId);
    
    for (size_t p = 1; p <= 12; ++p){
      
      if(!(MCQuarksEta->size() < p) ){
	MCQuarksEtaVec[p-1]=MCQuarksEta->at(p-1);
	MCQuarksPhiVec[p-1]=MCQuarksPhi->at(p-1);
	MCQuarksPtVec[p-1]=MCQuarksPt->at(p-1);
	MCQuarksEnergyVec[p-1]=MCQuarksEnergy->at(p-1);
	MCQuarksPdgIdVec[p-1]=MCQuarksPdgId->at(p-1);
	MCQuarksMotherIdVec[p-1]=MCQuarksMotherId->at(p-1);
      }
      else{
	MCQuarksEtaVec[p-1]=-999;
	MCQuarksPhiVec[p-1]=-999;
	MCQuarksPtVec[p-1]=-999;
	MCQuarksEnergyVec[p-1]=-999;
	MCQuarksPdgIdVec[p-1]=-999;
	MCQuarksMotherIdVec[p-1]=-999;
      }
    }
    for (size_t p = 1; p <= 4; ++p){
      if(!(MCLeptonsEta->size() < p) ){
	MCLeptonsEtaVec[p-1]=MCLeptonsEta->at(p-1);
	MCLeptonsPhiVec[p-1]=MCLeptonsPhi->at(p-1);
	MCLeptonsPtVec[p-1]=MCLeptonsPt->at(p-1);
	MCLeptonsEnergyVec[p-1]=MCLeptonsEnergy->at(p-1);
	MCLeptonsPdgIdVec[p-1]=MCLeptonsPdgId->at(p-1);
	MCLeptonsMotherIdVec[p-1]=MCLeptonsMotherId->at(p-1);
	
      }
      else{
	MCLeptonsEtaVec[p-1]=-999;
	MCLeptonsPhiVec[p-1]=-999;
	MCLeptonsPtVec[p-1]=-999;
	MCLeptonsEnergyVec[p-1]=-999;
	MCLeptonsPdgIdVec[p-1]=-999;
	MCLeptonsMotherIdVec[p-1]=-999;
	
      }
      if(!(MCBQuarksEta->size() < p) ){
	MCBQuarksEtaVec[p-1]=MCBQuarksEta->at(p-1);
	MCBQuarksPhiVec[p-1]=MCBQuarksPhi->at(p-1);
	MCBQuarksPtVec[p-1]=MCBQuarksPt->at(p-1);
	MCBQuarksEnergyVec[p-1]=MCBQuarksEnergy->at(p-1);
	MCBQuarksPdgIdVec[p-1]=MCBQuarksPdgId->at(p-1);
	MCBQuarksMotherIdVec[p-1]=MCBQuarksMotherId->at(p-1);
      }
      else{
	MCBQuarksEtaVec[p-1]=-999;
	MCBQuarksPhiVec[p-1]=-999;
	MCBQuarksPtVec[p-1]=-999;
	MCBQuarksEnergyVec[p-1]=-999;
	MCBQuarksPdgIdVec[p-1]=-999;
	MCBQuarksMotherIdVec[p-1]=-999;
      }
      if(!(MCNeutrinosEta->size() < p) ){
	MCNeutrinosEtaVec[p-1]=MCNeutrinosEta->at(p-1);
	MCNeutrinosPhiVec[p-1]=MCNeutrinosPhi->at(p-1);
	MCNeutrinosPtVec[p-1]=MCNeutrinosPt->at(p-1);
	MCNeutrinosEnergyVec[p-1]=MCNeutrinosEnergy->at(p-1);
	MCNeutrinosPdgIdVec[p-1]=MCNeutrinosPdgId->at(p-1);
	MCNeutrinosMotherIdVec[p-1]=MCNeutrinosMotherId->at(p-1);
      }
      else{
	MCNeutrinosEtaVec[p-1]=-999;
	MCNeutrinosPhiVec[p-1]=-999;
	MCNeutrinosPtVec[p-1]=-999;
	MCNeutrinosEnergyVec[p-1]=-999;
	MCNeutrinosPdgIdVec[p-1]=-999;
	MCNeutrinosMotherIdVec[p-1]=-999;
      }
    }
    nMCTruthLeptons = 0;
    
    for (size_t p = 1; p <= 2; ++p){
      
      bool isLeptonic = false;
      bool isHadronic = false;
      topPtReweight =1.;
	  topPtReweightUp =1.;
	  topPtReweightDown =1.;
	  topPtReweightMCTruth =1.;
      topPtReweightMCTruthUp =1.;
      topPtReweightMCTruthDown =1.;	  
      size_t position = 0;
      
      if(isSingleTopCompHEP_){
	if (MCTopLeptonsEta->size() < p)continue;
	position = p;
	MCTopLeptonsEtaVec[p-1]=MCTopLeptonsEta->at(position-1);
	MCTopLeptonsPhiVec[p-1]=MCTopLeptonsPhi->at(position-1);
	MCTopLeptonsPtVec[p-1]=MCTopLeptonsPt->at(position-1);
	MCTopLeptonsEnergyVec[p-1]=MCTopLeptonsEnergy->at(position-1);
	MCTopLeptonsPdgIdVec[p-1]=MCTopLeptonsPdgId->at(position-1);
	MCTopLeptonsMotherIdVec[p-1]=MCTopLeptonsMotherId->at(position-1);
	
	MCTopNeutrinosEtaVec[p-1]=MCTopNeutrinosEta->at(position-1);
	MCTopNeutrinosPhiVec[p-1]=MCTopNeutrinosPhi->at(position-1);
	MCTopNeutrinosPtVec[p-1]=MCTopNeutrinosPt->at(position-1);
	MCTopNeutrinosEnergyVec[p-1]=MCTopNeutrinosEnergy->at(position-1);
	MCTopNeutrinosPdgIdVec[p-1]=MCTopNeutrinosPdgId->at(position-1);
	MCTopNeutrinosMotherIdVec[p-1]=MCTopNeutrinosMotherId->at(position-1);
	
	if(!(MCTopBQuarksEta->size() < p) ){
	  MCTopBQuarksEtaVec[p-1]=MCTopBQuarksEta->at(p-1);
	  MCTopBQuarksPhiVec[p-1]=MCTopBQuarksPhi->at(p-1);
	  MCTopBQuarksPtVec[p-1]=MCTopBQuarksPt->at(p-1);
	  MCTopBQuarksEnergyVec[p-1]=MCTopBQuarksEnergy->at(p-1);
	  MCTopBQuarksPdgIdVec[p-1]=MCTopBQuarksPdgId->at(p-1);
	  MCTopBQuarksMotherIdVec[p-1]=MCTopBQuarksMotherId->at(p-1);
	}
	
	
      }
      else{
	if (MCTopWsEta->size() < p)continue;
	if(MCTopNeutrinosEta->size()!=MCTopLeptonsEta->size())continue;
	if(MCTopQuarksEta->size()!=MCTopQuarkBarsEta->size())continue;
	
	for (size_t l = 1; l <= MCTopQuarksEta->size();++l ){
	  
	  //	  cout << " quark id "<<   MCTopQuarksPdgId->at(l-1) << " quarkbar id "<< MCTopQuarkBarsPdgId->at(l-1) <<
	  //  " W dau one id "<< MCTopWsDauOneId->at(p-1) << endl;
	  
	  //	  cout  << " quark mother id "<<  MCTopQuarksMotherId->at(l-1) << " quarkbar id "<< MCTopQuarkBarsMotherId->at(l-1) << 
	  //  " W  id "<< MCTopWsPdgId->at(p-1) << endl;
	  if(  MCTopQuarksPdgId->at(l-1) == MCTopWsDauOneId->at(p-1) ||  MCTopQuarkBarsPdgId->at(l-1) == MCTopWsDauOneId->at(p-1) ){
	    position = l;
	    isHadronic = true;
	  }
	}
	for (size_t l = 1; l <= MCTopLeptonsEta->size();++l ){
	  
	  // cout << " lepton id "<<  MCTopLeptonsPdgId->at(l-1) << " neutrino id "<< MCTopNeutrinosPdgId->at(l-1)<< 
	  //  " W dau one id "<< MCTopWsDauOneId->at(p-1) << endl;
	  
	  //cout << " lepton mother id "<<  MCTopLeptonsMotherId->at(l-1) << " neutrino id "<< MCTopNeutrinosMotherId->at(l-1) << 
	  //  " W  id "<< MCTopWsPdgId->at(p-1) << endl;
	  
	  if(  MCTopLeptonsPdgId->at(l-1) == MCTopWsDauOneId->at(p-1) ||  MCTopNeutrinosPdgId->at(l-1) == MCTopWsDauOneId->at(p-1) ){
	    position = l;
	    ++nMCTruthLeptons;
	    isLeptonic = true;
	  }
	}
		  
	//	cout <<" pos "<<  position <<"  islep "<<  isLeptonic<< " lep size "<< MCTopLeptonsEta->size()<< " neu size "<< MCTopNeutrinosEta->size()<< endl;
	//	cout <<" pos "<<  position <<"  ishad "<<  isHadronic<< " quark size"<< MCTopQuarksEta->size()<< " qbar size "<< MCTopQuarkBarsEta->size()<< endl;
	if(isLeptonic){
	  MCTopLeptonsEtaVec[p-1]=MCTopLeptonsEta->at(position-1);
	  MCTopLeptonsPhiVec[p-1]=MCTopLeptonsPhi->at(position-1);
	  MCTopLeptonsPtVec[p-1]=MCTopLeptonsPt->at(position-1);
	  MCTopLeptonsEnergyVec[p-1]=MCTopLeptonsEnergy->at(position-1);
	  MCTopLeptonsPdgIdVec[p-1]=MCTopLeptonsPdgId->at(position-1);
	  MCTopLeptonsMotherIdVec[p-1]=MCTopLeptonsMotherId->at(position-1);
	  
	  MCTopNeutrinosEtaVec[p-1]=MCTopNeutrinosEta->at(position-1);
	  MCTopNeutrinosPhiVec[p-1]=MCTopNeutrinosPhi->at(position-1);
	  MCTopNeutrinosPtVec[p-1]=MCTopNeutrinosPt->at(position-1);
	  MCTopNeutrinosEnergyVec[p-1]=MCTopNeutrinosEnergy->at(position-1);
	  MCTopNeutrinosPdgIdVec[p-1]=MCTopNeutrinosPdgId->at(position-1);
	  MCTopNeutrinosMotherIdVec[p-1]=MCTopNeutrinosMotherId->at(position-1);
	  
	}
	else{
	  MCTopLeptonsEtaVec[p-1]=-999;
	  MCTopLeptonsPhiVec[p-1]=-999;
	  MCTopLeptonsPtVec[p-1]=-999;
	  MCTopLeptonsEnergyVec[p-1]=-999;
	  MCTopLeptonsPdgIdVec[p-1]=-999;
	  MCTopLeptonsMotherIdVec[p-1]=-999;
		    
	  MCTopNeutrinosEtaVec[p-1]=-999;
	  MCTopNeutrinosPhiVec[p-1]=-999;
	  MCTopNeutrinosPtVec[p-1]=-999;
	  MCTopNeutrinosEnergyVec[p-1]=-999;
	  MCTopNeutrinosPdgIdVec[p-1]=-999;
	  MCTopNeutrinosMotherIdVec[p-1]=-999;
	}
	if(isHadronic){
	  
	  MCTopQuarksEtaVec[p-1]=MCTopQuarksEta->at(position-1);
	  MCTopQuarksPhiVec[p-1]=MCTopQuarksPhi->at(position-1);
	  MCTopQuarksPtVec[p-1]=MCTopQuarksPt->at(position-1);
	  MCTopQuarksEnergyVec[p-1]=MCTopQuarksEnergy->at(position-1);
	  MCTopQuarksPdgIdVec[p-1]=MCTopQuarksPdgId->at(position-1);
	  MCTopQuarksMotherIdVec[p-1]=MCTopQuarksMotherId->at(position-1);
	  
	  MCTopQuarkBarsEtaVec[p-1]=MCTopQuarkBarsEta->at(position-1);
	  MCTopQuarkBarsPhiVec[p-1]=MCTopQuarkBarsPhi->at(position-1);
	  MCTopQuarkBarsPtVec[p-1]=MCTopQuarkBarsPt->at(position-1);
	  MCTopQuarkBarsEnergyVec[p-1]=MCTopQuarkBarsEnergy->at(position-1);
	  MCTopQuarkBarsPdgIdVec[p-1]=MCTopQuarkBarsPdgId->at(position-1);
	  MCTopQuarkBarsMotherIdVec[p-1]=MCTopQuarkBarsMotherId->at(position-1);
	  
	}
	else{
	  MCTopQuarksEtaVec[p-1]=-999;
	  MCTopQuarksPhiVec[p-1]=-999;
	  MCTopQuarksPtVec[p-1]=-999;
	  MCTopQuarksEnergyVec[p-1]=-999;
	  MCTopQuarksPdgIdVec[p-1]=-999;
	  MCTopQuarksMotherIdVec[p-1]=-999;
	  
	  MCTopQuarkBarsEtaVec[p-1]=-999;
	  MCTopQuarkBarsPhiVec[p-1]=-999;
	  MCTopQuarkBarsPtVec[p-1]=-999;
	  MCTopQuarkBarsEnergyVec[p-1]=-999;
	  MCTopQuarkBarsPdgIdVec[p-1]=-999;
	  MCTopQuarkBarsMotherIdVec[p-1]=-999;
	  
	}
	if(!(MCTopWsEta->size() < p) ){
	  MCTopWsEtaVec[p-1]=MCTopWsEta->at(p-1);
	  MCTopWsPhiVec[p-1]=MCTopWsPhi->at(p-1);
	  MCTopWsPtVec[p-1]=MCTopWsPt->at(p-1);
	  MCTopWsEnergyVec[p-1]=MCTopWsEnergy->at(p-1);
	  MCTopWsPdgIdVec[p-1]=MCTopWsPdgId->at(p-1);
	}
	else{
	  MCTopWsEtaVec[p-1]=-999;
	  MCTopWsPhiVec[p-1]=-999;
	  MCTopWsPtVec[p-1]=-999;
	  MCTopWsEnergyVec[p-1]=-999;
	  MCTopWsPdgIdVec[p-1]=-999;
	}
	if(!(MCTopBQuarksEta->size() < p) ){
	  MCTopBQuarksEtaVec[p-1]=MCTopBQuarksEta->at(p-1);
	  MCTopBQuarksPhiVec[p-1]=MCTopBQuarksPhi->at(p-1);
	  MCTopBQuarksPtVec[p-1]=MCTopBQuarksPt->at(p-1);
	  MCTopBQuarksEnergyVec[p-1]=MCTopBQuarksEnergy->at(p-1);
	  MCTopBQuarksPdgIdVec[p-1]=MCTopBQuarksPdgId->at(p-1);
	  MCTopBQuarksMotherIdVec[p-1]=MCTopBQuarksMotherId->at(p-1);
	}
	else{
	  MCTopBQuarksEtaVec[p-1]=-999;
	  MCTopBQuarksPhiVec[p-1]=-999;
	  MCTopBQuarksPtVec[p-1]=-999;
	  MCTopBQuarksEnergyVec[p-1]=-999;
	  MCTopBQuarksPdgIdVec[p-1]=-999;
	  MCTopBQuarksMotherIdVec[p-1]=-999;
	}
	if( (!(MCBQuarksEta->size() < p)) && (!(MCTopWsEta->size() < p))){
	  math::PtEtaPhiELorentzVector mctop = math::PtEtaPhiELorentzVector(
									    (MCTopBQuarksPtVec[p-1]+MCTopWsPtVec[p-1]),
									    (MCTopBQuarksEtaVec[p-1]+MCTopWsEtaVec[p-1]),
									    (MCTopBQuarksPhiVec[p-1]+MCTopWsPhiVec[p-1]),
									    (MCTopBQuarksEnergyVec[p-1]+MCTopWsEnergyVec[p-1]) );
	  MCTopsPtVec[p-1]=mctop.pt();
	  MCTopsEtaVec[p-1]=mctop.eta();
	  MCTopsPhiVec[p-1]=mctop.phi();
	  MCTopsEnergyVec[p-1]=mctop.energy();
	  MCTopsPdgIdVec[p-1]=6* MCTopBQuarksPdgIdVec[p-1]/5.;
	  topPtReweight*=topPtReweighting("semilepton",MCTopsPtVec[p-1]);
	}
	else{
	  MCTopsEtaVec[p-1]=-999;
	  MCTopsPhiVec[p-1]=-999;
	  MCTopsPtVec[p-1]=-999;
	  MCTopsEnergyVec[p-1]=-999;
	  MCTopsPdgIdVec[p-1]=-999;
	}
}
      } 
        for (size_t p = 1; p <= 2; ++p){
		string chanrew = "semilepton";
		if(nMCTruthLeptons == 2 ){
		  chanrew = "dilepton";
		}
		if(nMCTruthLeptons == 1 ){
		  chanrew = "semilepton";
		}
		if(MCTopsPtVec[p-1]>-1){topPtReweightMCTruth*=topPtReweighting(chanrew,MCTopsPtVec[p-1]);}
	      }
	      if(doTopPtReweighting_  && channel != "Data"){
	       topPtReweight = sqrt(topPtReweight);
           topPtReweightUp = topPtReweight*topPtReweight ;
           topPtReweightDown = 1.;
	       topPtReweightMCTruth = sqrt(topPtReweightMCTruth); 
           topPtReweightMCTruthUp = topPtReweightMCTruth*topPtReweightMCTruth ; 
           topPtReweightMCTruthDown = 1.;
           }else{
            topPtReweight =1.;
           topPtReweightUp = 1.;
           topPtReweightDown = 1.;
	       topPtReweightMCTruth = 1.;
           topPtReweightMCTruthUp = 1.; 
           topPtReweightMCTruthDown = 1.;
           }

}


////Functions for experimental effects (JECs/JERs. b-tag SFs, lepton SFs):

//JES uncertainty as a function of pt, eta and jet flavour
double SingleTopSystematicsTreesDumper::jetUncertainty(double eta, double ptCorr, int flavour)
{
    jecUnc->setJetEta(eta);
    jecUnc->setJetPt(ptCorr);
    double JetCorrection = jecUnc->getUncertainty(true);
    return JetCorrection;
}

//When in need to recalculate offline the corrections:
double SingleTopSystematicsTreesDumper::offlineJESJERApplicationPt(double ptUncorr,double energyUncorr,double eta,string syst){
  return ptUncorr;
}

double SingleTopSystematicsTreesDumper::offlineJESJERApplicationE(double ptUncorr,double energyUncorr,double eta,string syst){
  return energyUncorr;
}

void  SingleTopSystematicsTreesDumper::getJetPtE(const Event &iEvent, string syst){
  if(syst=="noSyst" || (
			syst != "JESUp" && syst != "JESDown" &&
			syst != "JERUp" && syst != "JERDown" 
			)) {
      iEvent.getByLabel(jetsPt_, jetsPt);
      iEvent.getByLabel(jetsEnergy_, jetsEnergy);
    }
  /*  if (syst == "UnclusteredMETUp" || syst == "UnclusteredMETDown")
    {
      iEvent.getByLabel(jetsPt_, jetsPt);
      iEvent.getByLabel(jetsEnergy_, jetsEnergy);
      //      iEvent.getByLabel(jetsPtJERUp_, jetsPt);
      //      iEvent.getByLabel(jetsEnergyJERUp_, jetsEnergy);
      }*/
  if (syst == "JERUp")
    {
      iEvent.getByLabel(jetsPtJERUp_, jetsPt);
      iEvent.getByLabel(jetsEnergyJERUp_, jetsEnergy);
    }
  if (syst == "JERDown")
    {
      iEvent.getByLabel(jetsPtJERDown_, jetsPt);
      iEvent.getByLabel(jetsEnergyJERDown_, jetsEnergy);
    }
  if (syst == "JESUp")
    {
      iEvent.getByLabel(jetsPtJESUp_, jetsPt);
      iEvent.getByLabel(jetsEnergyJESUp_, jetsEnergy);
    }
  if (syst == "JESDown")
    {
      iEvent.getByLabel(jetsPtJESDown_, jetsPt);
      iEvent.getByLabel(jetsEnergyJESDown_, jetsEnergy);
    }
}

void  SingleTopSystematicsTreesDumper::getMET(const Event &iEvent, string syst){
  if(syst=="noSyst" || (syst != "UnclusteredMETUp" && syst != "UnclusteredMETDown" &&  
			syst != "JESUp" && syst != "JESDown" &&
			syst != "JERUp" && syst != "JERDown" 
			))
    {
      iEvent.getByLabel(METPhi_, METPhi);
      iEvent.getByLabel(METPt_, METPt);
    }
  if (syst == "UnclusteredMETUp")
    {
      iEvent.getByLabel(UnclUpMETPt_, METPt);
      iEvent.getByLabel(UnclUpMETPhi_, METPhi);
    }
  if (syst == "UnclusteredMETDown")
    {
      iEvent.getByLabel(UnclDownMETPt_, METPt);
      iEvent.getByLabel(UnclDownMETPhi_, METPhi);
    }
  if (syst == "JERUp")
    {
      iEvent.getByLabel(JERUpMETPt_, METPt);
      iEvent.getByLabel(JERUpMETPhi_, METPhi);
    }
  if (syst == "JERDown")
    {
      iEvent.getByLabel(JERDownMETPt_, METPt);
      iEvent.getByLabel(JERDownMETPhi_, METPhi);
    }
  if (syst == "JESUp")
    {
      iEvent.getByLabel(JESUpMETPt_, METPt);
      iEvent.getByLabel(JESUpMETPhi_, METPhi);
    }
  if (syst == "JESDown")
    {
      iEvent.getByLabel(JESDownMETPt_, METPt);
      iEvent.getByLabel(JESDownMETPhi_, METPhi);
    }
}




void SingleTopSystematicsTreesDumper::setBTagWeights(double pt, double eta, int flavour, bool is_btag_relevant=true,string syst="noSyst",string channel = "TChannel"){
  double hptSF = 1;		      double hptSFErr = 0;
  double csvtSF = 1;		      double csvtSFErr = 0;
  double csvmSF = 1;		      double csvmSFErr = 0;

  double hptSFErrUp = 0;
  double hptSFErrDown = 0;
  // double csvtSFErrUp = 0;
  //  double csvtSFErrDown = 0;
  //  double csvmSFErrUp = 0;
  //  double csvmSFErrDown = 0;
  
  if (abs(flavour) == 4)
    {
      ++nc;
      if (is_btag_relevant )
	{
	  
	  double hpteff = EFFMap("TCHPT_C", channel);
	  double csvteff = EFFMap("CSVT_C", channel);
	  double csvmeff = EFFMap("CSVL_C", channel);
	  if (fabs(eta) > 2.6)
	    {
	      hpteff = 0;			  csvteff = 0;			  csvmeff = 0;
	    }
	  
	  hptSF = BTagSFNew(pt, "TCHPT");
	  csvtSF = BTagSFNew(pt, "CSVT");
	  csvmSF = BTagSFNew(pt, "CSVL");
	  
	  hptSFErr = BTagSFErrNew(pt, "TCHPT") ;
	  csvtSFErr = BTagSFErrNew(pt, "CSVT") ;
	  csvmSFErr = BTagSFErrNew(pt, "CSVL") ;
	  
	  jsfshpt.push_back(BTagWeight::JetInfo(hpteff, hptSF));
	  jsfshpt_mis_tag_up.push_back(BTagWeight::JetInfo(hpteff, hptSF));
	  jsfshpt_mis_tag_down.push_back(BTagWeight::JetInfo(hpteff, hptSF));
	  
	  jsfscsvt.push_back(BTagWeight::JetInfo(csvteff, csvtSF));
	  jsfscsvt_mis_tag_up.push_back(BTagWeight::JetInfo(csvteff, csvtSF));
	  jsfscsvt_mis_tag_down.push_back(BTagWeight::JetInfo(csvteff, csvtSF));
	  
	  jsfscsvm.push_back(BTagWeight::JetInfo(csvmeff, csvmSF));
	  jsfscsvm_mis_tag_up.push_back(BTagWeight::JetInfo(csvmeff, csvmSF));
	  jsfscsvm_mis_tag_down.push_back(BTagWeight::JetInfo(csvmeff, csvmSF));
	  
	  
	  if (syst == "noSyst")
	    {
	      jsfshpt_b_tag_up.push_back(BTagWeight::JetInfo(hpteff, hptSF + 2 * hptSFErr));
	      jsfshpt_b_tag_down.push_back(BTagWeight::JetInfo(hpteff, hptSF - 2 * hptSFErr));
	      
	      jsfscsvt_b_tag_up.push_back(BTagWeight::JetInfo(csvteff, csvtSF + 2 * csvtSFErr));
	      jsfscsvt_b_tag_down.push_back(BTagWeight::JetInfo(csvteff, csvtSF - 2 * csvtSFErr));
	      
	      jsfscsvm_b_tag_up.push_back(BTagWeight::JetInfo(csvmeff, csvmSF + 2 * csvmSFErr));
	      jsfscsvm_b_tag_down.push_back(BTagWeight::JetInfo(csvmeff, csvmSF - 2 * csvmSFErr));
	      
	    }
	}
    }
  else if (abs(flavour) == 5)
    {
      ++nb;
      if (is_btag_relevant )
	{
	  
	  double hpteff = EFFMap("TCHPT_B", channel);
	  double csvteff = EFFMap("CSVT_B", channel);
	  double csvmeff = EFFMap("CSVL_B", channel);
	  if (fabs(eta) > 2.6)
	    {
	      hpteff = 0;                            csvteff = 0;                            csvmeff = 0;
	    }
	  
	  hptSF = BTagSFNew(pt, "TCHPT");
	  csvtSF = BTagSFNew(pt, "CSVT");
	  csvmSF = BTagSFNew(pt, "CSVL");
			
	  hptSFErr = BTagSFErrNew(pt, "TCHPT") ;
	  csvtSFErr = BTagSFErrNew(pt, "CSVT") ;
	  csvmSFErr = BTagSFErrNew(pt, "CSVL") ;
	  
	  jsfshpt.push_back(BTagWeight::JetInfo(hpteff, hptSF));
	  jsfshpt_mis_tag_up.push_back(BTagWeight::JetInfo(hpteff, hptSF));
	  jsfshpt_mis_tag_down.push_back(BTagWeight::JetInfo(hpteff, hptSF));
	  
	  jsfscsvt.push_back(BTagWeight::JetInfo(csvteff, csvtSF));
	  jsfscsvt_mis_tag_up.push_back(BTagWeight::JetInfo(csvteff, csvtSF));
	  jsfscsvt_mis_tag_down.push_back(BTagWeight::JetInfo(csvteff, csvtSF));
	  
	  jsfscsvm.push_back(BTagWeight::JetInfo(csvmeff, csvmSF));
	  jsfscsvm_mis_tag_up.push_back(BTagWeight::JetInfo(csvmeff, csvmSF));
	  jsfscsvm_mis_tag_down.push_back(BTagWeight::JetInfo(csvmeff, csvmSF));
	  
	  
	  if (syst == "noSyst")
	    {
	      jsfshpt_b_tag_up.push_back(BTagWeight::JetInfo(hpteff, hptSF + hptSFErr));
	      jsfshpt_b_tag_down.push_back(BTagWeight::JetInfo(hpteff, hptSF - hptSFErr));
	      
	      jsfscsvt_b_tag_up.push_back(BTagWeight::JetInfo(csvteff, csvtSF + csvtSFErr));
	      jsfscsvt_b_tag_down.push_back(BTagWeight::JetInfo(csvteff, csvtSF - csvtSFErr));
	      
	      jsfscsvm_b_tag_up.push_back(BTagWeight::JetInfo(csvmeff, csvmSF + csvmSFErr));
	      jsfscsvm_b_tag_down.push_back(BTagWeight::JetInfo(csvmeff, csvmSF - csvmSFErr));
	      
	    }
	}
      
    }
  else
    {
      if (is_btag_relevant )
	{
	  double csvtSF = 1;
	  double csvtSFErrUp = 0;
	  double csvtSFErrDown = 0;
	  
	  double csvmSF = 1;
	  double csvmSFErrUp = 0;
	  double csvmSFErrDown = 0;
	  
	  double hpteff = EFFMap("TCHPT_L", channel);
	  double csvteff = EFFMap("CSVT_L", channel);
	  double csvmeff = EFFMap("CSVL_L", channel);
	  
	  if (fabs(eta) > 2.6)
	    {
	      hpteff = 0;
	      csvteff = 0;
	      csvmeff = 0;
	    }
	  
	  hptSF = MisTagSFNew(pt, eta, "TCHPT");
	  hptSFErrUp = MisTagSFErrNewUp(pt, eta, "TCHPT");
	  hptSFErrDown = MisTagSFErrNewDown(pt, eta, "TCHPT");
	  
	  csvmSF = MisTagSFNew(pt, eta, "CSVL");
	  csvmSFErrUp = MisTagSFErrNewUp(pt, eta, "CSVL");
	  csvmSFErrDown = MisTagSFErrNewDown(pt, eta, "CSVL");
	  
	  csvtSF = MisTagSFNew(pt, eta, "CSVT");
	  csvtSFErrUp = MisTagSFErrNewUp(pt, eta, "CSVT");
	  csvtSFErrDown = MisTagSFErrNewDown(pt, eta, "CSVT");
	  
	  jsfshpt.push_back(BTagWeight::JetInfo(hpteff, hptSF));
	  jsfshpt_b_tag_up.push_back(BTagWeight::JetInfo(hpteff, hptSF));
	  jsfshpt_b_tag_down.push_back(BTagWeight::JetInfo(hpteff, hptSF));
	  
	  jsfscsvt.push_back(BTagWeight::JetInfo(csvteff, csvtSF));
	  jsfscsvt_b_tag_up.push_back(BTagWeight::JetInfo(csvteff, csvtSF));
	  jsfscsvt_b_tag_down.push_back(BTagWeight::JetInfo(csvteff, csvtSF));
	  
	  jsfscsvm.push_back(BTagWeight::JetInfo(csvmeff, csvmSF));
	  jsfscsvm_b_tag_up.push_back(BTagWeight::JetInfo(csvmeff, csvmSF));
	  jsfscsvm_b_tag_down.push_back(BTagWeight::JetInfo(csvmeff, csvmSF));
	  
	  if (syst == "noSyst")
	    {
	      jsfshpt_mis_tag_up.push_back(BTagWeight::JetInfo(hpteff, hptSFErrUp));
	      jsfshpt_mis_tag_down.push_back(BTagWeight::JetInfo(hpteff, hptSFErrDown));
	      
	      jsfscsvt_mis_tag_up.push_back(BTagWeight::JetInfo(csvteff, csvtSFErrUp));
	      jsfscsvt_mis_tag_down.push_back(BTagWeight::JetInfo(csvteff, csvtSFErrDown));
	      
	      jsfscsvm_mis_tag_up.push_back(BTagWeight::JetInfo(csvmeff, csvmSFErrUp));
	      jsfscsvm_mis_tag_down.push_back(BTagWeight::JetInfo(csvmeff, csvmSFErrDown));
	      
	    }
	}
      ++nudsg;
    }
}

//B-C weight as function of jet flavour, systematics and scale factors:
double SingleTopSystematicsTreesDumper::BTagSFNew(double pt, string algo)
{
    if (algo == "CSVM")return 0.6981 * ((1. + (0.414063 * pt)) / (1. + (0.300155 * pt)));
    if (algo == "CSVT")return 0.901615 * ((1. + (0.552628 * pt)) / (1. + (0.547195 * pt)));
    if (algo == "TCHPT")return 0.305208*((1.+(0.595166*pt))/(1.+(0.186968*pt)));
    //old prescription    if (algo == "TCHPT")return 0.895596 * ((1. + (9.43219e-05 * pt)) / (1. + (-4.63927e-05 * pt)));
    if (algo == "CSVL") return 1.02658 * ((1. + (0.0195388 * pt)) / (1. + (0.0209145 * pt)));
    return 1;
}

double SingleTopSystematicsTreesDumper::BTagSFErrNew(double pt, string algo)
{
    if (algo == "TCHPT")
    {
      //        if (pt > 30 && pt < 40)return 0.0543376;        if (pt > 40 && pt < 50)return 0.0534339;        if (pt > 50 && pt < 60)return 0.0266156;        if (pt > 60 && pt < 70)return 0.0271337;        if (pt > 70 && pt < 80)return 0.0276364;        if (pt > 80 && pt < 100)return 0.0308838;        if (pt > 100 && pt < 120)return 0.0381656;        if (pt > 120 && pt < 160)return 0.0336979;        if (pt > 160 && pt < 210)return 0.0336773;        if (pt > 210 && pt < 260)return 0.0347688;        if (pt > 260 && pt < 320)return 0.0376865;        if (pt > 320 && pt < 400)return 0.0556052;        if (pt > 400 && pt < 500)return 0.0598105;        if (pt > 500 && pt < 670)return 0.0861122;
      
      if (pt > 20 && pt < 30)return 0.0725549;
      if (pt > 30 && pt < 40)return 0.0275189;
      if (pt > 40 && pt < 50)return 0.0279695;
      if (pt > 50 && pt < 60)return 0.028065;
      if (pt > 60 && pt < 70)return 0.0270752;
      if (pt > 70 && pt < 80)return 0.0254934;
      if (pt > 80 && pt < 100)return 0.0262087;
      if (pt > 100 && pt < 120)return 0.0230919;
      if (pt > 120 && pt < 160)return 0.0294829;
      if (pt > 160 && pt < 210)return 0.0226487;
      if (pt > 210 && pt < 260)return 0.0272755;
      if (pt > 260 && pt < 320)return 0.0303747;
      if (pt > 320 && pt < 400)return 0.051223;
      if (pt > 400 && pt < 500)return 0.0542895;
      if (pt > 500 && pt < 600)return 0.0589887;
      if (pt > 600 && pt < 800)return 0.0584216;
    }
    if (algo == "TCHEL")
    {
        if (pt > 30 && pt < 40)return 0.0244956;
        if (pt > 40 && pt < 50)return 0.0237293;
        if (pt > 50 && pt < 60)return 0.0180131;
        if (pt > 60 && pt < 70)return 0.0182411;
        if (pt > 70 && pt < 80)return 0.0184592;
        if (pt > 80 && pt < 100)return 0.0106444;
        if (pt > 100 && pt < 120)return 0.0110736;
        if (pt > 120 && pt < 160)return 0.0106296;
        if (pt > 160 && pt < 210)return 0.0175259;
        if (pt > 210 && pt < 260)return 0.0161566;
        if (pt > 260 && pt < 320)return 0.0158973;
        if (pt > 320 && pt < 400)return 0.0186782;
        if (pt > 400 && pt < 500)return 0.0371113;
        if (pt > 500 && pt < 670)return 0.0289788;
    }
    if (algo == "CSVM")
    {
        if (pt > 30 && pt < 40)return 0.0295675;
        if (pt > 40 && pt < 50)return 0.0295095;
        if (pt > 50 && pt < 60)return 0.0210867;
        if (pt > 60 && pt < 70)return 0.0219349;
        if (pt > 70 && pt < 80)return 0.0227033;
        if (pt > 80 && pt < 100)return 0.0204062;
        if (pt > 100 && pt < 120)return 0.0185857;
        if (pt > 120 && pt < 160)return 0.0256242;
        if (pt > 160 && pt < 210)return 0.0383341;
        if (pt > 210 && pt < 260)return 0.0409675;
        if (pt > 260 && pt < 320)return 0.0420284;
        if (pt > 320 && pt < 400)return 0.0541299;
        if (pt > 400 && pt < 500)return 0.0578761;
        if (pt > 500 && pt < 670)return 0.0655432;
    }

    if (algo == "CSVT")
    {
        if (pt > 30 && pt < 40)return 0.0364717;
        if (pt > 40 && pt < 50)return 0.0362281;
        if (pt > 50 && pt < 60)return 0.0232876;
        if (pt > 60 && pt < 70)return 0.0249618;
        if (pt > 70 && pt < 80)return 0.0261482;
        if (pt > 80 && pt < 100)return 0.0290466;
        if (pt > 100 && pt < 120)return 0.0300033;
        if (pt > 120 && pt < 160)return 0.0453252;
        if (pt > 160 && pt < 210)return 0.0685143;
        if (pt > 210 && pt < 260)return 0.0653621;
        if (pt > 260 && pt < 320)return 0.0712586;
        if (pt > 320 && pt < 400)return 0.0945892;
        if (pt > 400 && pt < 500)return 0.0777011;
        if (pt > 500 && pt < 670)return 0.0866563;
    }

    if (algo == "CSVL")
    {
        if (pt > 30 && pt < 40)return     0.0188743;
        if (pt > 40 && pt < 50)return     0.0161816;
        if (pt > 50 && pt < 60)return     0.0139824;
        if (pt > 60 && pt < 70)return     0.0152644;
        if (pt > 70 && pt < 80)return     0.0161226;
        if (pt > 80 && pt < 100)return     0.0157396;
        if (pt > 100 && pt < 120)return     0.0161619;
        if (pt > 120 && pt < 160)return     0.0168747;
        if (pt > 160 && pt < 210)return     0.0257175;
        if (pt > 210 && pt < 260)return     0.026424;
        if (pt > 260 && pt < 320)return     0.0264928;
        if (pt > 320 && pt < 400)return     0.0315127;
        if (pt > 400 && pt < 500)return     0.030734;
        if (pt > 500 && pt < 670)return     0.0438259 ;
    }


    return 0;

}

double SingleTopSystematicsTreesDumper::MisTagSFNew(double pt, double eta, string algo)
{
  if (algo == "TCHPT")return ((1.1676+(0.00136673*pt))+(-3.51053e-06*(pt*pt)))+(2.4966e-09*(pt*(pt*pt)));
  if (algo == "CSVM")return ((1.20711 + (0.000681067 * pt)) + (-1.57062e-06 * (pt * pt))) + (2.83138e-10 * (pt * (pt * pt))) * (1.10422 + -0.000523856 * pt + 1.14251e-06 * pt * pt);
  if (algo == "CSVT") return (1.10649 * ((1 + (-9.00297e-05 * pt)) + (2.32185e-07 * (pt * pt)))) + (-4.04925e-10 * (pt * (pt * (pt / (1 + (-0.00051036 * pt)))))) * (1.19275 + -0.00191042 * pt + 2.92205e-06 * pt * pt);
  
  if (algo == "CSVL")return ((1.0344 + (0.000962994 * pt)) + (-3.65392e-06 * (pt * pt))) + (3.23525e-09 * (pt * (pt * pt))) * (0.979396 + 0.000205898 * pt + 2.49868e-07 * pt * pt);
  
    return 0;
}

double SingleTopSystematicsTreesDumper::MisTagSFErrNewUp(double pt, double eta, string algo)
{
    double x = pt;

    if (algo == "TCHPT")return ((1.34691+(0.00181637*pt))+(-4.64484e-06*(pt*pt)))+(3.27122e-09*(pt*(pt*pt)));
    if (algo == "TCHEL")return (1.19751 * ((1 + (-0.000114197 * pt)) + (3.08558e-07 * (pt * pt)))) + (-5.27598e-10 * (pt * (pt * (pt / (1 + (-0.000422372 * pt)))))) ;

    if (algo == "CSVT") return ((0.997077 + (0.00473953 * x)) + (-1.34985e-05 * (x * x))) + (1.0032e-08 * (x * (x * x)));
    if (algo == "CSVL")return ((1.11272 + (0.00110104 * x)) + (-4.11956e-06 * (x * x))) + (3.65263e-09 * (x * (x * x)));

    return 0;
}

double SingleTopSystematicsTreesDumper::MisTagSFErrNewDown(double pt, double eta, string algo)
{
    double x = pt;
    if (algo == "TCHPT")return ((0.988346+(0.000914722*pt))+(-2.37077e-06*(pt*pt)))+(1.72082e-09*(pt*(pt*pt)));
    if (algo == "TCHEL")return (1.01541 * ((1 + (-6.04627e-05 * pt)) + (1.38195e-07 * (pt * pt)))) + (-2.83043e-10 * (pt * (pt * (pt / (1 + (-0.000633609 * pt))))));

    if (algo == "CSVT") return ((0.899715 + (0.00102278 * x)) + (-2.46335e-06 * (x * x))) + (9.71143e-10 * (x * (x * x)));
    if (algo == "CSVL")return ((0.956023 + (0.000825106 * x)) + (-3.18828e-06 * (x * x))) + (2.81787e-09 * (x * (x * x)));

    return 0;
}


double SingleTopSystematicsTreesDumper::EFFMapNew(double btag, string algo)
{
    if (algo == "TCHP_B")return 1.26119661124e-05 * btag * btag * btag * btag +  -0.000683198597977 * btag * btag * btag +  0.0145106168149 * btag * btag +  -0.159575511553 * btag +  0.887707865272;
    if (algo == "TCHP_C")
    {
        if (btag < 0.54) return 0.451288118581 * exp(-0.0213290505241 * btag * btag * btag + 0.356020789904 * btag * btag + -2.20158883207 * btag + 1.84838018633 );
        else return 0.99;
    }
    if (algo == "TCHP_L")return (-0.00101 + (4.70405e-05 * btag)) + (8.3338e-09 * (btag * btag));

    if (algo == "TCHE_B")return 3.90732786802e-06 * btag * btag * btag * btag +  -0.000239934437355 * btag * btag * btag +  0.00664986827287 * btag * btag +  -0.112578996016 * btag +  1.00775721404;
    if (algo == "TCHE_C")
    {
        if (btag > 0.46 ) return 0.343760640168 * exp(-0.00315525164823 * btag * btag * btag + 0.0805427315196 * btag * btag + -0.867625139194 * btag + 1.44815935164 );
        else return 0.99;//EFFMap("TCHEL_C");
    }

    if (algo == "TCHE_L")return(((-0.0276197 + (0.00291907 * btag)) + (-7.51594e-06 * (btag * btag))) + (9.82128e-09 * (btag * (btag * btag)))) + (-5.33759e-12 * (btag * (btag * (btag * btag))));
    return 1;
}

double SingleTopSystematicsTreesDumper::EFFMap(string algo ){

  if (algo == "TCHPT_B")return 0.365 * 1.;
  if (algo == "TCHPT_C")return 0.0365;
  if (algo == "TCHPT_L")return 0.0017;
  
  if (algo == "CSVT_B")return 0.54;
  if (algo == "CSVT_C")return 0.037;
  if (algo == "CSVT_L")return 0.002;
  
  
  if (algo == "CSVL_B")return 0.8;
  if (algo == "CSVL_C")return 0.36;
  if (algo == "CSVL_L")return 0.2;
  
  return 0.36;
}

double SingleTopSystematicsTreesDumper::EFFMap(string algo, string channel )
{
    if (channel == "TChannel" || channel == "TbarChannel" || channel == "SChannel" || channel == "SbarChannel" || channel == "TWChannel" || channel == "TbarWChannel")
      {
	if (algo == "TCHPT_B")return 0.365 * 1.;
	if (algo == "TCHPT_C")return 0.0365;
	if (algo == "TCHPT_L")return 0.0017;
	
	if (algo == "CSVT_B")return 0.54;
	if (algo == "CSVT_C")return 0.037;
	if (algo == "CSVT_L")return 0.002;
	
	if (algo == "CSVL_B")return 0.84;
	if (algo == "CSVL_C")return 0.33;
	if (algo == "CSVL_L")return 0.2;
	
      }
    
    if (channel == "TTBar")
      {
	if (algo == "TCHPT_B")return 0.365 * 1.;
	if (algo == "TCHPT_C")return 0.0365;
	if (algo == "TCHPT_L")return 0.0017;
	
	if (algo == "CSVT_B")return 0.66;
	if (algo == "CSVT_C")return 0.052;
	if (algo == "CSVT_L")return 0.047;
	
	if (algo == "CSVL_B")return 0.92;
	if (algo == "CSVL_C")return 0.44;
	if (algo == "CSVL_L")return 0.3;
	
      }
    
    if (channel == "WJets")
      {
	
	if (algo == "TCHPT_B")return 0.365 * 1.;
	if (algo == "TCHPT_C")return 0.0365;
	if (algo == "TCHPT_L")return 0.0017;
	
	if (algo == "CSVT_B")return 0.31;
	if (algo == "CSVT_C")return 0.046;
	if (algo == "CSVT_L")return 0.0015;
	
	if (algo == "CSVL_B")return 0.63;
	if (algo == "CSVL_C")return 0.40;
	if (algo == "CSVL_L")return 0.14;
	
      }
    
    if (channel == "ZJets")
      {
	
	if (algo == "TCHPT_B")return 0.365 * 1.;
	if (algo == "TCHPT_C")return 0.0365;
	if (algo == "TCHPT_L")return 0.0017;
	
	if (algo == "CSVT_B")return 0.41;
	if (algo == "CSVT_C")return 0.047;
	if (algo == "CSVT_L")return 0.002;
	
	if (algo == "CSVL_B")return 0.76;
	if (algo == "CSVL_C")return 0.41;
	if (algo == "CSVL_L")return 0.2;
	
      }
    return EFFMap(algo);
}

double SingleTopSystematicsTreesDumper::EFFErrMap(string algo )
{
    if (algo == "TCHPT_B")return 0.05;
    if (algo == "TCHPT_C")return 0.05;
    if (algo == "TCHPT_L")return 0.0004;

    if (algo == "TCHEL_B")return 0.05;
    if (algo == "TCHEL_C")return 0.05;
    if (algo == "TCHEL_L")return 0.03;

    if (algo == "TCHEL_B")return 0.05;
    if (algo == "TCHEL_C")return 0.05;
    if (algo == "TCHEL_L")return 0.004;

    return 0.05;
}


int SingleTopSystematicsTreesDumper::eventFlavour(string ch, int nb, int nc, int nl)
{
    if (ch !=  "WJets" && ch != "ZJets") return 0;
    else
    {
        if ( flavourFilter("WJets_wlight", nb, nc, nl) ) return 1;
        if ( flavourFilter("WJets_wcc", nb, nc, nl) ) return 2;
        if ( flavourFilter("WJets_wbb", nb, nc, nl) ) return 3;
    }
    return 0;
}

bool SingleTopSystematicsTreesDumper::flavourFilter(string ch, int nb, int nc, int nl)
{

    if (ch == "WJets_wbb" || ch == "ZJets_wbb") return (nb > 0 );
    if (ch == "WJets_wcc" || ch == "ZJets_wcc") return (nb == 0 && nc > 0);
    if (ch == "WJets_wlight" || ch == "ZJets_wlight") return (nb == 0 && nc == 0);

    return true;
}

/*double SingleTopSystematicsTreesDumper::jetprob(double pt, double btag){
  double prob=0.993*(exp(-51.0*exp(-0.160*pt)));
  prob*=0.902*exp((-5.995*exp(-0.604*btag)));
  return prob;
  }*/

double SingleTopSystematicsTreesDumper::bTagSF(int B)
{
  if (doBTagSF_ == false )return 1.0;

    if (algo_ == "TCHPT")
    {
        if (B == 0 || B == 3)
	  {
	    return b_tchpt_0_tags.weight(jsfshpt, ntchpt_tags); //*b_tchel_0_tags.weight(jsfshel,ntchel_tags);
	  }
        if (B == 1 || B == 4)
        {
	  return b_tchpt_1_tag.weight(jsfshpt, ntchpt_tags);
        }
        if (B == 2 || B == 5)
        {
	  return b_tchpt_2_tags.weight(jsfshpt, ntchpt_tags);
        }
    }

    if(doLooseBJetVeto_){
     if(B==1 || B == 4) return b_csvt_1_tag.weightWithVeto(jsfscsvt,ncsvt_tags,jsfscsvm,ncsvl_tags);
    }


    if (B == 0 || B == 3)
    {
        return b_csvt_0_tags.weight(jsfscsvt, ncsvt_tags); //*b_tchel_0_tags.weight(jsfshel,ntchel_tags);
    }
    if (B == 1 || B == 4)
    {
        return b_csvt_1_tag.weight(jsfscsvt, ncsvt_tags);
    }
    if (B == 2 || B == 5)
    {
        return b_csvt_2_tags.weight(jsfscsvt, ncsvt_tags);
    }
    return 1.;
}

double SingleTopSystematicsTreesDumper::bTagSF(int B, string syst)
{
  if (doBTagSF_ == false )return 1.0;
  //  cout<< " B " << " ntchhpt "<<   ntchpt_tags << " jsfshpt size "<<
  // jsfshpt.size() << " ntchel " << ntchel_tags<< " jsfshel size " << jsfshel.size()<<endl;
  if (algo_ == "TCHPT")
    {
      if (B == 0 || B == 3)
        {
	  if (syst == "BTagUp")    return b_tchpt_0_tags.weight(jsfshpt_b_tag_up, ntchpt_tags); //*b_tchel_0_tags.weight(jsfshel_b_tag_up,ntchel_tags);
	  if (syst == "BTagDown")    return b_tchpt_0_tags.weight(jsfshpt_b_tag_down, ntchpt_tags); //*b_tchel_0_tags.weight(jsfshel_b_tag_down,ntchel_tags);
	  if (syst == "MisTagUp")    return b_tchpt_0_tags.weight(jsfshpt_mis_tag_up, ntchpt_tags); //*b_tchel_0_tags.weight(jsfshel_mis_tag_up,ntchel_tags);
	  if (syst == "MisTagDown")    return b_tchpt_0_tags.weight(jsfshpt_mis_tag_down, ntchpt_tags); //*b_tchel_0_tags.weight(jsfshel_mis_tag_down,ntchel_tags);
	  return b_tchpt_0_tags.weight(jsfshpt, ntchpt_tags); //*b_tchel_0_tags.weight(jsfshel,ntchel_tags);
        }
      if (B == 1 || B == 4)
        {
	  
	  if (syst == "BTagUp")    return b_tchpt_1_tag.weight(jsfshpt_b_tag_up, ntchpt_tags);
	  if (syst == "BTagDown")    return b_tchpt_1_tag.weight(jsfshpt_b_tag_down, ntchpt_tags);
	  if (syst == "MisTagUp")    return b_tchpt_1_tag.weight(jsfshpt_mis_tag_up, ntchpt_tags);
	  if (syst == "MisTagDown")    return b_tchpt_1_tag.weight(jsfshpt_mis_tag_down, ntchpt_tags);
	  
	  return b_tchpt_1_tag.weight(jsfshpt, ntchpt_tags);
        }
        if (B == 2 || B == 5)
        {

            if (syst == "BTagUp")    return b_tchpt_2_tags.weight(jsfshpt_b_tag_up, ntchpt_tags);
            if (syst == "BTagDown")    return b_tchpt_2_tags.weight(jsfshpt_b_tag_down, ntchpt_tags);
            if (syst == "MisTagUp")    return b_tchpt_2_tags.weight(jsfshpt_mis_tag_up, ntchpt_tags);
            if (syst == "MisTagDown")    return b_tchpt_2_tags.weight(jsfshpt_mis_tag_down, ntchpt_tags);
	    
            return b_tchpt_2_tags.weight(jsfshpt, ntchpt_tags);
        }
    }
  
  //Loose jet veto:
  if(doLooseBJetVeto_){
    if (B == 1 || B == 4)
      {
	//	  if(syst ) return b_csvt_1_tag.weightWithVeto(jsfscsvt,ncsvt_tags,jsfscsvm,ncsvl_tags);	  
	if (syst == "BTagUp")    return b_csvt_1_tag.weightWithVeto(jsfscsvt_b_tag_up, ncsvt_tags,jsfscsvm_b_tag_up, ncsvl_tags);
	if (syst == "BTagDown")    return b_csvt_1_tag.weightWithVeto(jsfscsvt_b_tag_down, ncsvt_tags,jsfscsvm_b_tag_down, ncsvl_tags);
	if (syst == "MisTagUp")    return b_csvt_1_tag.weightWithVeto(jsfscsvt_mis_tag_up, ncsvt_tags,jsfscsvm_mis_tag_up, ncsvl_tags);
	if (syst == "MisTagDown")    return b_csvt_1_tag.weightWithVeto(jsfscsvt_mis_tag_down, ncsvt_tags,jsfscsvm_mis_tag_down, ncsvl_tags);
	return b_csvt_1_tag.weightWithVeto(jsfscsvt,ncsvt_tags,jsfscsvm,ncsvl_tags);	  
	
      }
  }
  //Default case: use csvt
  
  if (B == 0 || B == 3)
    {
      if (syst == "BTagUp")    return b_csvt_0_tags.weight(jsfscsvt_b_tag_up, ncsvt_tags); //*b_tchel_0_tags.weight(jsfshel_b_tag_up,ntchel_tags);
      if (syst == "BTagDown")    return b_csvt_0_tags.weight(jsfscsvt_b_tag_down, ncsvt_tags); //*b_tchel_0_tags.weight(jsfshel_b_tag_down,ntchel_tags);
      if (syst == "MisTagUp")    return b_csvt_0_tags.weight(jsfscsvt_mis_tag_up, ncsvt_tags); //*b_tchel_0_tags.weight(jsfshel_mis_tag_up,ntchel_tags);
      if (syst == "MisTagDown")    return b_csvt_0_tags.weight(jsfscsvt_mis_tag_down, ncsvt_tags); //*b_tchel_0_tags.weight(jsfshel_mis_tag_down,ntchel_tags);
      return b_csvt_0_tags.weight(jsfscsvt, ncsvt_tags); //*b_tchel_0_tags.weight(jsfshel,ntchel_tags);
    }
  
  if (B == 1 || B == 4)
    {
      
      if (syst == "BTagUp")    return b_csvt_1_tag.weight(jsfscsvt_b_tag_up, ncsvt_tags);
      if (syst == "BTagDown")    return b_csvt_1_tag.weight(jsfscsvt_b_tag_down, ncsvt_tags);
      if (syst == "MisTagUp")    return b_csvt_1_tag.weight(jsfscsvt_mis_tag_up, ncsvt_tags);
      if (syst == "MisTagDown")    return b_csvt_1_tag.weight(jsfscsvt_mis_tag_down, ncsvt_tags);
      
      return b_csvt_1_tag.weight(jsfscsvt, ncsvt_tags);
    }
  if (B == 2 || B == 5)
    {
      
      if (syst == "BTagUp")    return b_csvt_2_tags.weight(jsfscsvt_b_tag_up, ncsvt_tags);
      if (syst == "BTagDown")    return b_csvt_2_tags.weight(jsfscsvt_b_tag_down, ncsvt_tags);
        if (syst == "MisTagUp")    return b_csvt_2_tags.weight(jsfscsvt_mis_tag_up, ncsvt_tags);
        if (syst == "MisTagDown")    return b_csvt_2_tags.weight(jsfscsvt_mis_tag_down, ncsvt_tags);

        return b_csvt_2_tags.weight(jsfscsvt, ncsvt_tags);
    }

    return 1.;
}

double SingleTopSystematicsTreesDumper::pileUpSF(string syst)
{
    if (syst == "PUUp" )return LumiWeightsUp_.weight( *n0);
    if (syst == "PUDown" )return LumiWeightsDown_.weight( *n0);
    return LumiWeights_.weight( *n0);
}

double SingleTopSystematicsTreesDumper::resolSF(double eta, string syst)
{
    double fac = 0.;
    if (syst == "JERUp")fac = 1.;
    if (syst == "JERDown")fac = -1.;
    if (eta <= 0.5) return 0.052 + 0.063 * fac;
    else if ( eta > 0.5 && eta <= 1.1 ) return 0.057 + 0.057 * fac;
    else if ( eta > 1.1 && eta <= 1.7 ) return 0.096 + 0.065 * fac;
    else if ( eta > 1.7 && eta <= 2.3 ) return 0.134 + 0.093 * fac;
    else if ( eta > 2.3 && eta <= 5. ) return 0.288 + 0.200 * fac;
    return 0.1;
}

//BTag weighter
bool SingleTopSystematicsTreesDumper::BTagWeight::filter(int t)
{
    return (t >= minTags && t <= maxTags);
}

float SingleTopSystematicsTreesDumper::BTagWeight::weight(vector<JetInfo> jets, int tags)
{
    if (!filter(tags))
    {
        //   std::cout << "nThis event should not pass the selection, what is it doing here?" << std::endl;
        return 0;
    }
    int njets = jets.size();
    int comb = 1 << njets;
    float pMC = 0;
    float pData = 0;
    for (int i = 0; i < comb; i++)
    {
        float mc = 1.;
        float data = 1.;
        int ntagged = 0;
        for (int j = 0; j < njets; j++)
        {
            bool tagged = ((i >> j) & 0x1) == 1;
            if (tagged)
            {
                ntagged++;
                mc *= jets[j].eff;
                data *= jets[j].eff * jets[j].sf;
            }
            else
            {
                mc *= (1. - jets[j].eff);
                data *= (1. - jets[j].eff * jets[j].sf);
            }
        }
        if (filter(ntagged))
        {
            //  std::cout << mc << " " << data << endl;
            pMC += mc;
            pData += data;
        }
    }
    if (pMC == 0) return 0;
    return pData / pMC;
}

float SingleTopSystematicsTreesDumper::BTagWeight::weightWithVeto(vector<JetInfo> jetsTags, int tags, vector<JetInfo> jetsVetoes, int vetoes)
{//This function takes into account cases where you have n b-tags and m vetoes, but they have different thresholds. 
    if (!filter(tags))
    {   //   std::cout << "nThis event should not pass the selection, what is it doing here?" << std::endl;
        return 0;
    }
    int njets = jetsTags.size();
    if(njets != (int)(jetsVetoes.size()))return 0;//jets tags and vetoes must have same size!
    int comb = 1 << njets;
    float pMC = 0;
    float pData = 0;
    for (int i = 0; i < comb; i++)
    {
        float mc = 1.;
        float data = 1.;
        int ntagged = 0;
        for (int j = 0; j < njets; j++)
        {
            bool tagged = ((i >> j) & 0x1) == 1;
            if (tagged)
            {
                ntagged++;
                mc *= jetsTags[j].eff;
                data *= jetsTags[j].eff * jetsTags[j].sf;
            }
            else
            {
                mc *= (1. - jetsVetoes[j].eff);
                data *= (1. - jetsVetoes[j].eff * jetsVetoes[j].sf);
            }
        }

        if (filter(ntagged))
        {
            //  std::cout << mc << " " << data << endl;
            pMC += mc;
            pData += data;
        }
    }

    if (pMC == 0) return 0;
    return pData / pMC;
}


void SingleTopSystematicsTreesDumper::muonHLTSF(float etaMu, float ptMu){//Muon scale factors 

  double pt = ptMu;
  double eta = etaMu;
  sfID=1;sfIDup=1;sfIDdown=1;  
  sfIso=1;sfIsoup=1;sfIsodown=1;  
  sfTrig=1;sfTrigup=1;sfTrigdown=1;  

//ID Iso SF for ABCD
if(fabs(eta)<=0.9) {  if (pt > 10 && pt <  20){sfID = 0.984868; sfIDup = 0.990827; sfIDdown = 0.978922 ; } 
 if (pt > 20 && pt <  25){sfID = 0.988681; sfIDup = 0.990443; sfIDdown = 0.986914 ; } 
 if (pt > 25 && pt <  30){sfID = 0.993889; sfIDup = 0.994673; sfIDdown = 0.9931 ; } 
 if (pt > 30 && pt <  35){sfID = 0.994164; sfIDup = 0.994709; sfIDdown = 0.993617 ; } 
 if (pt > 35 && pt <  40){sfID = 0.994084; sfIDup = 0.994505; sfIDdown = 0.993662 ; } 
 if (pt > 40 && pt <  50){sfID = 0.99247; sfIDup = 0.992741; sfIDdown = 0.992199 ; } 
 if (pt > 50 && pt <  60){sfID = 0.990978; sfIDup = 0.991644; sfIDdown = 0.990308 ; } 
 if (pt > 60 && pt <  90){sfID = 0.990444; sfIDup = 0.991505; sfIDdown = 0.989377 ; } 
 if (pt > 90 && pt <  140){sfID = 1.00385; sfIDup = 1.00714; sfIDdown = 1.00055 ; } 
 if (pt > 140 && pt <  300){sfID = 1.02798; sfIDup = 1.04694; sfIDdown = 1.00922 ; } 
 if (pt > 300 && pt <  500){sfID = 1; sfIDup = 1; sfIDdown = 0.67606 ; } 
 if (pt > 10 && pt <  20){sfIso = 0.94705; sfIsoup = 0.949803; sfIsodown = 0.944293 ; } 
 if (pt > 20 && pt <  25){sfIso = 0.974978; sfIsoup = 0.976512; sfIsodown = 0.97344 ; } 
 if (pt > 25 && pt <  30){sfIso = 0.997129; sfIsoup = 0.998065; sfIsodown = 0.99619 ; } 
 if (pt > 30 && pt <  35){sfIso = 0.993863; sfIsoup = 0.994484; sfIsodown = 0.993242 ; } 
 if (pt > 35 && pt <  40){sfIso = 0.993442; sfIsoup = 0.993872; sfIsodown = 0.993009 ; } 
 if (pt > 40 && pt <  50){sfIso = 0.994101; sfIsoup = 0.994322; sfIsodown = 0.993878 ; } 
 if (pt > 50 && pt <  60){sfIso = 0.995544; sfIsoup = 0.995948; sfIsodown = 0.995137 ; } 
 if (pt > 60 && pt <  90){sfIso = 0.999036; sfIsoup = 0.999501; sfIsodown = 0.998565 ; } 
 if (pt > 90 && pt <  140){sfIso = 1.00104; sfIsoup = 1.00192; sfIsodown = 1.00013 ; } 
 if (pt > 140 && pt <  300){sfIso = 1.0003; sfIsoup = 1.00201; sfIsodown = 0.998474 ; } 
 if (pt > 300 && pt <  500){sfIso = 1.01977; sfIsoup = 1.02914; sfIsodown = 1.00747 ; } 
 }
if(fabs(eta)<=1.2&& fabs(eta)>0.9) {  if (pt > 10 && pt <  20){sfID = 0.986855; sfIDup = 0.993819; sfIDdown = 0.979939 ; } 
 if (pt > 20 && pt <  25){sfID = 0.987375; sfIDup = 0.989974; sfIDdown = 0.984765 ; } 
 if (pt > 25 && pt <  30){sfID = 0.994212; sfIDup = 0.995638; sfIDdown = 0.992776 ; } 
 if (pt > 30 && pt <  35){sfID = 0.990593; sfIDup = 0.991663; sfIDdown = 0.989516 ; } 
 if (pt > 35 && pt <  40){sfID = 0.990353; sfIDup = 0.991142; sfIDdown = 0.989559 ; } 
 if (pt > 40 && pt <  50){sfID = 0.989641; sfIDup = 0.990134; sfIDdown = 0.989147 ; } 
 if (pt > 50 && pt <  60){sfID = 0.991311; sfIDup = 0.992578; sfIDdown = 0.990035 ; } 
 if (pt > 60 && pt <  90){sfID = 0.98631; sfIDup = 0.988322; sfIDdown = 0.98428 ; } 
 if (pt > 90 && pt <  140){sfID = 1.01191; sfIDup = 1.01838; sfIDdown = 1.00536 ; } 
 if (pt > 140 && pt <  300){sfID = 0.955563; sfIDup = 0.990509; sfIDdown = 0.921661 ; } 
 if (pt > 300 && pt <  500){sfID = 1; sfIDup = 1; sfIDdown = 0.489937 ; } 
 if (pt > 10 && pt <  20){sfIso = 0.951836; sfIsoup = 0.954998; sfIsodown = 0.948665 ; } 
 if (pt > 20 && pt <  25){sfIso = 0.988368; sfIsoup = 0.99068; sfIsodown = 0.986047 ; } 
 if (pt > 25 && pt <  30){sfIso = 1.00083; sfIsoup = 1.00248; sfIsodown = 0.999185 ; } 
 if (pt > 30 && pt <  35){sfIso = 0.998546; sfIsoup = 0.999708; sfIsodown = 0.997378 ; } 
 if (pt > 35 && pt <  40){sfIso = 0.99914; sfIsoup = 0.999886; sfIsodown = 0.998392 ; } 
 if (pt > 40 && pt <  50){sfIso = 0.998176; sfIsoup = 0.998528; sfIsodown = 0.997824 ; } 
 if (pt > 50 && pt <  60){sfIso = 0.998696; sfIsoup = 0.999342; sfIsodown = 0.99804 ; } 
 if (pt > 60 && pt <  90){sfIso = 0.999132; sfIsoup = 0.999902; sfIsodown = 0.998346 ; } 
 if (pt > 90 && pt <  140){sfIso = 0.999559; sfIsoup = 1.00095; sfIsodown = 0.998088 ; } 
 if (pt > 140 && pt <  300){sfIso = 0.996767; sfIsoup = 0.999567; sfIsodown = 0.993535 ; } 
 if (pt > 300 && pt <  500){sfIso = 1.00784; sfIsoup = 1.02465; sfIsodown = 0.981759 ; } 
}
if(fabs(eta)<2.1&& fabs(eta)>1.2) {  if (pt > 10 && pt <  20){sfID = 1.01235; sfIDup = 1.01633; sfIDdown = 1.00839 ; } 
 if (pt > 20 && pt <  25){sfID = 1.00155; sfIDup = 1.00304; sfIDdown = 1.00006 ; } 
 if (pt > 25 && pt <  30){sfID = 0.999149; sfIDup = 1.00003; sfIDdown = 0.998262 ; } 
 if (pt > 30 && pt <  35){sfID = 0.997573; sfIDup = 0.998294; sfIDdown = 0.99685 ; } 
 if (pt > 35 && pt <  40){sfID = 0.996585; sfIDup = 0.997183; sfIDdown = 0.995984 ; } 
 if (pt > 40 && pt <  50){sfID = 0.997431; sfIDup = 0.997804; sfIDdown = 0.997056 ; } 
 if (pt > 50 && pt <  60){sfID = 0.997521; sfIDup = 0.998468; sfIDdown = 0.996571 ; } 
 if (pt > 60 && pt <  90){sfID = 0.993942; sfIDup = 0.995548; sfIDdown = 0.992327 ; } 
 if (pt > 90 && pt <  140){sfID = 1.01922; sfIDup = 1.02491; sfIDdown = 1.0135 ; } 
 if (pt > 140 && pt <  300){sfID = 1.01648; sfIDup = 1.04966; sfIDdown = 0.982238 ; } 
 if (pt > 300 && pt <  500){sfID = 0.608799; sfIDup = 1; sfIDdown = 0.169285 ; } 
 if (pt > 10 && pt <  20){sfIso = 0.980045; sfIsoup = 0.981666; sfIsodown = 0.978421 ; } 
 if (pt > 20 && pt <  25){sfIso = 0.997342; sfIsoup = 0.998548; sfIsodown = 0.996133 ; } 
 if (pt > 25 && pt <  30){sfIso = 1.00784; sfIsoup = 1.00871; sfIsodown = 1.00696 ; } 
 if (pt > 30 && pt <  35){sfIso = 1.00685; sfIsoup = 1.00752; sfIsodown = 1.00618 ; } 
 if (pt > 35 && pt <  40){sfIso = 1.0037; sfIsoup = 1.00416; sfIsodown = 1.00323 ; } 
 if (pt > 40 && pt <  50){sfIso = 1.00209; sfIsoup = 1.0023; sfIsodown = 1.00188 ; } 
 if (pt > 50 && pt <  60){sfIso = 1.00125; sfIsoup = 1.00163; sfIsodown = 1.00086 ; } 
 if (pt > 60 && pt <  90){sfIso = 1.00065; sfIsoup = 1.00112; sfIsodown = 1.00018 ; } 
 if (pt > 90 && pt <  140){sfIso = 0.999878; sfIsoup = 1.00081; sfIsodown = 0.998902 ; } 
 if (pt > 140 && pt <  300){sfIso = 0.99989; sfIsoup = 1.00205; sfIsodown = 0.997507 ; } 
 if (pt > 300 && pt <  500){sfIso = 1.01392; sfIsoup = 1.02575; sfIsodown = 0.995749 ; } 
 }
//ABCD

//Trigger Run D
if(fabs(eta)<=0.9) {  if (pt > 25 && pt <  30){sfTrig = 0.979145; sfTrigup = 0.980946; sfTrigdown = 0.977338 ; } 
 if (pt > 30 && pt <  35){sfTrig = 0.980195; sfTrigup = 0.981314; sfTrigdown = 0.979072 ; } 
 if (pt > 35 && pt <  40){sfTrig = 0.981218; sfTrigup = 0.981981; sfTrigdown = 0.980454 ; } 
 if (pt > 40 && pt <  50){sfTrig = 0.982317; sfTrigup = 1.06112; sfTrigdown = 0.981954 ; } 
 if (pt > 50 && pt <  60){sfTrig = 0.981793; sfTrigup = 0.982783; sfTrigdown = 0.980797 ; } 
 if (pt > 60 && pt <  90){sfTrig = 0.985262; sfTrigup = 0.98673; sfTrigdown = 0.983781 ; } 
 if (pt > 90 && pt <  140){sfTrig = 0.985298; sfTrigup = 0.990194; sfTrigdown = 0.980271 ; } 
 if (pt > 140 && pt <  500){sfTrig = 0.986012; sfTrigup = 0.999074; sfTrigdown = 0.971938 ; } 
}
if(fabs(eta)<=1.2&& fabs(eta)>0.9) {  if (pt > 25 && pt <  30){sfTrig = 0.962613; sfTrigup = 0.966528; sfTrigdown = 0.958684 ; } 
 if (pt > 30 && pt <  35){sfTrig = 0.959007; sfTrigup = 0.961889; sfTrigdown = 0.956115 ; } 
 if (pt > 35 && pt <  40){sfTrig = 0.9618; sfTrigup = 0.963988; sfTrigdown = 0.959605 ; } 
 if (pt > 40 && pt <  50){sfTrig = 0.962938; sfTrigup = 0.964187; sfTrigdown = 0.961686 ; } 
 if (pt > 50 && pt <  60){sfTrig = 0.960298; sfTrigup = 0.96326; sfTrigdown = 0.95732 ; } 
 if (pt > 60 && pt <  90){sfTrig = 0.956722; sfTrigup = 0.961223; sfTrigdown = 0.952188 ; } 
 if (pt > 90 && pt <  140){sfTrig = 0.962339; sfTrigup = 0.976841; sfTrigdown = 0.947468 ; } 
 if (pt > 140 && pt <  500){sfTrig = 0.99289; sfTrigup = 1.02694; sfTrigdown = 0.955269 ; } 
}
if(fabs(eta)<2.1&& fabs(eta)>1.2) {  if (pt > 25 && pt <  30){sfTrig = 1.00472; sfTrigup = 1.00727; sfTrigdown = 1.00218 ; } 
 if (pt > 30 && pt <  35){sfTrig = 1.00194; sfTrigup = 1.00392; sfTrigdown = 0.999953 ; } 
 if (pt > 35 && pt <  40){sfTrig = 0.998212; sfTrigup = 0.999835; sfTrigdown = 0.996586 ; } 
 if (pt > 40 && pt <  50){sfTrig = 0.996583; sfTrigup = 0.997588; sfTrigdown = 0.995575 ; } 
 if (pt > 50 && pt <  60){sfTrig = 0.991098; sfTrigup = 0.993481; sfTrigdown = 0.988707 ; } 
 if (pt > 60 && pt <  90){sfTrig = 0.983799; sfTrigup = 0.987389; sfTrigdown = 0.980192 ; } 
 if (pt > 90 && pt <  140){sfTrig = 0.983428; sfTrigup = 0.995422; sfTrigdown = 0.971255 ; } 
 if (pt > 140 && pt <  500){sfTrig = 0.944096; sfTrigup = 0.983253; sfTrigdown = 0.903315 ; } 
}

 lepSFD=sfTrig*sfIso*sfID;
 lepSFIDUpD=sfTrig*sfIso*sfIDup;
 lepSFIDDownD=sfTrig*sfIso*sfIDdown;

 lepSFIsoUpD=sfTrig*sfID*sfIsoup;
 lepSFIsoDownD=sfTrig*sfID*sfIsodown;

 lepSFTrigUpD=sfID*sfIso*sfTrigup;
 lepSFTrigDownD=sfID*sfIso*sfTrigdown;


//Trigger Run C
if(fabs(eta)<=0.9) {  if (pt > 25 && pt <  30){sfTrig = 0.986052; sfTrigup = 0.987446; sfTrigdown = 0.98465 ; } 
 if (pt > 30 && pt <  35){sfTrig = 0.985515; sfTrigup = 0.98642; sfTrigdown = 0.984605 ; } 
 if (pt > 35 && pt <  40){sfTrig = 0.984947; sfTrigup = 0.985592; sfTrigdown = 0.984298 ; } 
 if (pt > 40 && pt <  50){sfTrig = 0.983213; sfTrigup = 0.983753; sfTrigdown = 0.982674 ; } 
 if (pt > 50 && pt <  60){sfTrig = 0.983801; sfTrigup = 0.984719; sfTrigdown = 0.982878 ; } 
 if (pt > 60 && pt <  90){sfTrig = 0.983397; sfTrigup = 0.984783; sfTrigdown = 0.982 ; } 
 if (pt > 90 && pt <  140){sfTrig = 0.977086; sfTrigup = 0.981907; sfTrigdown = 0.972136 ; } 
 if (pt > 140 && pt <  500){sfTrig = 0.983315; sfTrigup = 0.995474; sfTrigdown = 0.970149 ; } 
}
if(fabs(eta)<=1.2&& fabs(eta)>0.9) {  if (pt > 25 && pt <  30){sfTrig = 0.9761; sfTrigup = 0.979632; sfTrigdown = 0.97255 ; } 
 if (pt > 30 && pt <  35){sfTrig = 0.969575; sfTrigup = 0.972217; sfTrigdown = 0.966921 ; } 
 if (pt > 35 && pt <  40){sfTrig = 0.971727; sfTrigup = 0.973774; sfTrigdown = 0.969673 ; } 
 if (pt > 40 && pt <  50){sfTrig = 0.968551; sfTrigup = 0.969478; sfTrigdown = 0.967617 ; } 
 if (pt > 50 && pt <  60){sfTrig = 0.966893; sfTrigup = 0.969728; sfTrigdown = 0.964041 ; } 
 if (pt > 60 && pt <  90){sfTrig = 0.959999; sfTrigup = 0.964271; sfTrigdown = 0.955696 ; } 
 if (pt > 90 && pt <  140){sfTrig = 0.959322; sfTrigup = 0.973596; sfTrigdown = 0.944637 ; } 
 if (pt > 140 && pt <  500){sfTrig = 1.0146; sfTrigup = 1.05261; sfTrigdown = 0.97273 ; } 
 }


 lepSFC=sfTrig*sfIso*sfID;
 lepSFIDUpC=sfTrig*sfIso*sfIDup;
 lepSFIDDownC=sfTrig*sfIso*sfIDdown;

 lepSFIsoUpC=sfTrig*sfID*sfIsoup;
 lepSFIsoDownC=sfTrig*sfID*sfIsodown;

 lepSFTrigUpC=sfID*sfIso*sfTrigup;
 lepSFTrigDownC=sfID*sfIso*sfTrigdown;

//Trigger Run B
if(fabs(eta)<=0.9) {  if (pt > 25 && pt <  30){sfTrig = 0.978858; sfTrigup = 0.980843; sfTrigdown = 0.976865 ; } 
 if (pt > 30 && pt <  35){sfTrig = 0.979803; sfTrigup = 0.981049; sfTrigdown = 0.978553 ; } 
 if (pt > 35 && pt <  40){sfTrig = 0.979755; sfTrigup = 0.980612; sfTrigdown = 0.978895 ; } 
 if (pt > 40 && pt <  50){sfTrig = 0.979681; sfTrigup = 0.980176; sfTrigdown = 0.979433 ; } 
 if (pt > 50 && pt <  60){sfTrig = 0.978707; sfTrigup = 0.979846; sfTrigdown = 0.97756 ; } 
 if (pt > 60 && pt <  90){sfTrig = 0.981103; sfTrigup = 0.982791; sfTrigdown = 0.9794 ; } 
 if (pt > 90 && pt <  140){sfTrig = 0.98042; sfTrigup = 0.986075; sfTrigdown = 0.9746 ; } 
 if (pt > 140 && pt <  500){sfTrig = 0.974405; sfTrigup = 0.988661; sfTrigdown = 0.959129 ; } 
}
if(fabs(eta)<=1.2&& fabs(eta)>0.9) {  if (pt > 25 && pt <  30){sfTrig = 0.97007; sfTrigup = 0.974442; sfTrigdown = 0.965677 ; } 
 if (pt > 30 && pt <  35){sfTrig = 0.962694; sfTrigup = 0.965879; sfTrigdown = 0.959495 ; } 
 if (pt > 35 && pt <  40){sfTrig = 0.960235; sfTrigup = 0.962675; sfTrigdown = 0.957787 ; } 
 if (pt > 40 && pt <  50){sfTrig = 0.962149; sfTrigup = 0.963544; sfTrigdown = 0.960747 ; } 
 if (pt > 50 && pt <  60){sfTrig = 0.959086; sfTrigup = 0.962429; sfTrigdown = 0.955723 ; } 
 if (pt > 60 && pt <  90){sfTrig = 0.952173; sfTrigup = 0.957241; sfTrigdown = 0.94706 ; } 
 if (pt > 90 && pt <  140){sfTrig = 0.949186; sfTrigup = 0.965981; sfTrigdown = 0.931917 ; } 
 if (pt > 140 && pt <  500){sfTrig = 0.953607; sfTrigup = 0.999454; sfTrigdown = 0.903591 ; } 
}
if(fabs(eta)<2.1&& fabs(eta)>1.2) {  if (pt > 25 && pt <  30){sfTrig = 0.995013; sfTrigup = 0.997841; sfTrigdown = 0.992179 ; } 
 if (pt > 30 && pt <  35){sfTrig = 0.986493; sfTrigup = 0.988727; sfTrigdown = 0.984256 ; } 
 if (pt > 35 && pt <  40){sfTrig = 0.9815; sfTrigup = 0.983319; sfTrigdown = 0.979677 ; } 
 if (pt > 40 && pt <  50){sfTrig = 0.978702; sfTrigup = 0.979837; sfTrigdown = 0.977566 ; } 
 if (pt > 50 && pt <  60){sfTrig = 0.97745; sfTrigup = 0.980154; sfTrigdown = 0.974737 ; } 
 if (pt > 60 && pt <  90){sfTrig = 0.975728; sfTrigup = 0.979825; sfTrigdown = 0.971608 ; } 
 if (pt > 90 && pt <  140){sfTrig = 0.955204; sfTrigup = 0.968591; sfTrigdown = 0.941583 ; } 
 if (pt > 140 && pt <  500){sfTrig = 0.982866; sfTrigup = 1.02659; sfTrigdown = 0.936749 ; } 
}

 lepSFB=sfTrig*sfIso*sfID;
 lepSFIDUpB=sfTrig*sfIso*sfIDup;
 lepSFIDDownB=sfTrig*sfIso*sfIDdown;

 lepSFIsoUpB=sfTrig*sfID*sfIsoup;
 lepSFIsoDownB=sfTrig*sfID*sfIsodown;

 lepSFTrigUpB=sfID*sfIso*sfTrigup;
 lepSFTrigDownB=sfID*sfIso*sfTrigdown;

//Trigger Run A

if(fabs(eta)<=0.9) {  if (pt > 25 && pt <  30){sfTrig = 0.938137; sfTrigup = 0.94254; sfTrigdown = 0.933702 ; } 
 if (pt > 30 && pt <  35){sfTrig = 0.942347; sfTrigup = 0.945148; sfTrigdown = 0.939526 ; } 
 if (pt > 35 && pt <  40){sfTrig = 0.951167; sfTrigup = 0.953089; sfTrigdown = 0.949232 ; } 
 if (pt > 40 && pt <  50){sfTrig = 0.960094; sfTrigup = 0.961208; sfTrigdown = 0.958976 ; } 
 if (pt > 50 && pt <  60){sfTrig = 0.97344; sfTrigup = 0.975881; sfTrigdown = 0.970964 ; } 
 if (pt > 60 && pt <  90){sfTrig = 0.975737; sfTrigup = 0.979319; sfTrigdown = 0.972082 ; } 
 if (pt > 90 && pt <  140){sfTrig = 0.980291; sfTrigup = 0.992657; sfTrigdown = 0.96703 ; } 
 if (pt > 140 && pt <  500){sfTrig = 1.00399; sfTrigup = 1.02648; sfTrigdown = 0.97399 ; } 
 }
if(fabs(eta)<=1.2&& fabs(eta)>0.9) {  if (pt > 25 && pt <  30){sfTrig = 0.940447; sfTrigup = 0.949624; sfTrigdown = 0.931184 ; } 
 if (pt > 30 && pt <  35){sfTrig = 0.941756; sfTrigup = 0.948636; sfTrigdown = 0.93482 ; } 
 if (pt > 35 && pt <  40){sfTrig = 0.961844; sfTrigup = 0.96685; sfTrigdown = 0.956797 ; } 
 if (pt > 40 && pt <  50){sfTrig = 0.958809; sfTrigup = 0.961669; sfTrigdown = 0.955932 ; } 
 if (pt > 50 && pt <  60){sfTrig = 0.943967; sfTrigup = 0.950932; sfTrigdown = 0.936907 ; } 
 if (pt > 60 && pt <  90){sfTrig = 0.944023; sfTrigup = 0.954631; sfTrigdown = 0.933205 ; } 
 if (pt > 90 && pt <  140){sfTrig = 0.985552; sfTrigup = 1.01463; sfTrigdown = 0.954264 ; } 
 if (pt > 140 && pt <  500){sfTrig = 0.879259; sfTrigup = 0.975855; sfTrigdown = 0.763416 ; } 
}
if(fabs(eta)<2.1&& fabs(eta)>1.2) {  if (pt > 25 && pt <  30){sfTrig = 0.980088; sfTrigup = 0.985963; sfTrigdown = 0.974184 ; } 
 if (pt > 30 && pt <  35){sfTrig = 0.989347; sfTrigup = 0.993926; sfTrigdown = 0.984746 ; } 
 if (pt > 35 && pt <  40){sfTrig = 0.98464; sfTrigup = 0.988287; sfTrigdown = 0.980976 ; } 
 if (pt > 40 && pt <  50){sfTrig = 0.979771; sfTrigup = 0.982028; sfTrigdown = 0.977509 ; } 
 if (pt > 50 && pt <  60){sfTrig = 0.982233; sfTrigup = 0.987606; sfTrigdown = 0.976813 ; } 
 if (pt > 60 && pt <  90){sfTrig = 0.965242; sfTrigup = 0.973585; sfTrigdown = 0.956801 ; } 
 if (pt > 90 && pt <  140){sfTrig = 0.977609; sfTrigup = 1.00735; sfTrigdown = 0.946395 ; } 
 if (pt > 140 && pt <  500){sfTrig = 1.02767; sfTrigup = 1.08628; sfTrigdown = 0.956645 ; } 
}

 lepSF=sfTrig*sfIso*sfID;
 lepSFIDUp=sfTrig*sfIso*sfIDup;
 lepSFIDDown=sfTrig*sfIso*sfIDdown;

 lepSFIsoUp=sfTrig*sfID*sfIsoup;
 lepSFIsoDown=sfTrig*sfID*sfIsodown;

 lepSFTrigUp=sfID*sfIso*sfTrigup;
 lepSFTrigDown=sfID*sfIso*sfTrigdown;
}

void SingleTopSystematicsTreesDumper::electronHLTSF(float etaEle, float ptEle){// Electron scale factors

  double pt = ptEle;
  double eta = etaEle;
  sfID=1;sfIDup=1;sfIDdown=1;  
  sfIso=1;sfIsoup=1;sfIsodown=1;  
  sfTrig=1;sfTrigup=1;sfTrigdown=1;  
  
  //  cout << " cutbased "<< useCutBasedID_<< " mnva "<< useMVAID_<<endl; 
  if(useMVAID_>0){ // id and iso together
    if(fabs(eta)<0.8){
      if(pt>30 && pt <40 ){sfID=0.939;	sfIDdown=sfID-0.003;sfIDup=sfID+0.003;
      }
      if(pt>40 && pt <50 ){sfID=0.950;	sfTrigdown=sfTrig-0.001;sfTrigup=sfTrig+0.001;
      }
      if(pt>50 ){sfID=0.957;	sfIDdown=sfID-0.001;sfIDup=sfID+0.001;
      }
    }
    if(fabs(eta)>0.8&&fabs(eta)<1.478){
      if(pt>30 && pt <40 ){sfID=0.920;	sfIDdown=sfID-0.001;sfIDup=sfID+0.002;
      }
      if(pt>40 && pt <50 ){sfID=0.949;	sfIDdown=sfID-0.002;sfIDup=sfID+0.002;
      }
      if(pt>50 ){sfID=0.959;	sfIDdown=sfID-0.003;sfIDup=sfID+0.003;
      }
    }
    if(fabs(eta)>1.478){
      if(pt>30 && pt <40 ){sfID=0.907;	sfIDdown=sfID-0.005;sfIDup=sfID+0.005;
      }
      if(pt>40 && pt <50 ){sfID=0.937;	sfIDdown=sfID-0.008;sfIDup=sfID+0.008;
      }
      if(pt>50 ){sfID=0.954;	sfIDdown=sfID-0.010;sfIDup=sfID+0.011;
      }
    }
  }
  // cout << "tccc"<<endl;
  if(useCutBasedID_>0) {
    //    cout << " using cutbased, eta "<<eta << " pt "<<pt<<" sfID "<< sfID <<endl; 
    if(fabs(eta)<0.8){
      if(pt>30 && pt <40 ){
	sfID=0.976;	sfIDdown=sfID-0.001;sfIDup=sfID+0.001;
      } 
      if(pt>40 && pt <50 ){
	sfID=0.983;	sfIDdown=sfID-0.001;sfIDup=sfID+0.001;
      } 
      if(pt>50){
	sfID=0.980;	sfIDdown=sfID-0.001;sfIDup=sfID+0.001;
      } 
    }	
    if(fabs(eta)>0.8&&fabs(eta)<1.442){
      if(pt>30 && pt <40 ){
	sfID=0.967;	sfIDdown=sfID-0.001;sfIDup=sfID+0.001;
      } 
      if(pt>40 && pt <50 ){
	sfID=0.981;	sfIDdown=sfID-0.001;sfIDup=sfID+0.001;
      } 
      if(pt>50){
	sfID=0.980;	sfIDdown=sfID-0.001;sfIDup=sfID+0.001;
      } 
    }	
    if(fabs(eta)>1.442&&fabs(eta)<1.556){
      if(pt>30 && pt <40 ){
	sfID=0.966;	sfIDdown=sfID-0.008;sfIDup=sfID+0.008;
      } 
      if(pt>40 && pt <50 ){
	sfID=0.951;	sfIDdown=sfID-0.006;sfIDup=sfID+0.006;
      } 
      if(pt>50){
	sfID=0.942;	sfIDdown=sfID-0.017;sfIDup=sfID+0.017;
      } 
    }	
    if(fabs(eta)>1.556&&fabs(eta)<2.0){
      if(pt>30 && pt <40 ){
	sfID=0.961;	sfIDdown=sfID-0.001;sfIDup=sfID+0.003;
      } 
      if(pt>40 && pt <50 ){
	sfID=0.982;	sfIDdown=sfID-0.002;sfIDup=sfID+0.002;
      } 
      if(pt>50){
	sfID=0.986;	sfIDdown=sfID-0.001;sfIDup=sfID+0.001;
      } 
    }	
    if(fabs(eta)>2.0&&fabs(eta)<2.5){
      if(pt>30 && pt <40 ){
	sfID=1.006;	sfIDdown=sfID-0.001;sfIDup=sfID+0.003;
      } 
      if(pt>40 && pt <50 ){
	sfID=1.012;	sfIDdown=sfID-0.001;sfIDup=sfID+0.001;
      } 
      if(pt>50){
	sfID=1.016;	sfIDdown=sfID-0.002;sfIDup=sfID+0.002;
      } 
    }	
  }
  //  cout << " after cutbased, eta "<<eta << " pt "<<pt<<" sfID after "<< sfID <<endl; 
  //they are for MVAID
  if(fabs(eta)<0.8){
    if(pt>30 && pt <40 ){sfTrig=0.987;      sfTrigdown=sfTrig-0.017;sfTrigup=sfTrig+0.012;//sfTrigdown=sfTrig-0.003;sfTrigup=sfTrig+0.003;
    }
    if(pt>40 && pt <50 ){sfTrig=0.997;      sfTrigdown=sfTrig-0.001;sfTrigup=sfTrig+0.001;
    }
    if(pt>50 ){sfTrig=0.998;      sfTrigdown=sfTrig-0.002;sfTrigup=sfTrig+0.002;
    }
  }
  if(fabs(eta)>0.8&&fabs(eta)<1.478){
    if(pt>30 && pt <40 ){sfTrig=0.964;      sfTrigdown=sfTrig-0.001;sfTrigup=sfTrig+0.002;
    }
    if(pt>40 && pt <50 ){sfTrig=0.980;      sfTrigdown=sfTrig-0.001;sfTrigup=sfTrig+0.001;
    }
    if(pt>50 ){sfTrig=0.988;      sfTrigdown=sfTrig-0.002;sfTrigup=sfTrig+0.002;
    }
  }
  if(fabs(eta)>1.478){
    if(pt>30 && pt <40 ){sfTrig=1.004;      sfTrigdown=sfTrig-0.006;sfTrigup=sfTrig+0.006;
    }
    if(pt>40 && pt <50 ){sfTrig=1.033;      sfTrigdown=sfTrig-0.007;sfTrigup=sfTrig+0.007;
    }
    if(pt>50 ){sfTrig=0.976;      sfTrigdown=sfTrig-0.012;sfTrigup=sfTrig+0.015;
    }
  }
  lepSF=sfTrig*sfIso*sfID;
  lepSFIDUp=sfTrig*sfIso*sfIDup;
  lepSFIDDown=sfTrig*sfIso*sfIDdown;
  
  lepSFIsoUp=sfTrig*sfID*sfIsoup;
  lepSFIsoDown=sfTrig*sfID*sfIsodown;
  
  lepSFTrigUp=sfID*sfIso*sfTrigup;
  lepSFTrigDown=sfID*sfIso*sfTrigdown;

}

double SingleTopSystematicsTreesDumper::topPtReweighting(string chanrew, double pt){
  if((channel == "TTBar") || 
     (channel == "TTBarFullLep") ||
     (channel == "TTBarSemiLep") ||
     (channel == "TTBar_Q2Up") ||
     (channel == "TTBar_Q2Down") ||
     (channel == "TTBar_MassUp") ||
     (channel == "TTBar_MassDown") ||
     (channel == "TTBar_MatchingUp") ||
     (channel == "TTBar_MatchingDown") 
     ){
  double a = 0.156, b =-0.00137;
  if(chanrew == "semilepton"){a=0.159;b=-0.00141;}
  if(chanrew == "dilepton"){a=0.148;b=-0.00129;}
  return exp(a+b*pt);
  }
  return 1.0;
}

void SingleTopSystematicsTreesDumper::resetWeightsDoubles()
{

  //cout<<"inresetWeight"<<endl;
  double baseWeight=0.0,baseWeightMCTruth=0.0;
  double baseWeightUp=0.0,baseWeightMCTruthUp=0.0;
 // double baseWeightDown=0.0,baseWeightMCTruthDown=0.0; Down is actually 1 , then no change
  long int ngood=0,ngoodmctruth=0; //double topPtReweight2=0;
  //  cout<<"inresetWeight"<<endl;
 /* int nentriestot = treesMCTruth->GetEntries();     cout<<"nentriestot  "<<nentriestot<<endl;

  for (int i =0; i< nentriestot;++i){     
    treesMCTruth->GetEntry(i);  cout<<"i: "<<i<<" topPtReweight IN treesMCTruth"<<topPtReweight<<endl;
    if(topPtReweight<1.5){++ngood;
      baseWeight+=topPtReweight;
      baseWeightUp+=topPtReweightUp; 
      }
    if(topPtReweightMCTruth<1.5){++ngoodmctruth;
      baseWeightMCTruth+=topPtReweightMCTruth;
      baseWeightMCTruthUp+=topPtReweightMCTruthUp;
    }
  }
cout<<"baseWeightUp  1 : "<<baseWeightUp<< "   baseWeightMCTruthUp 1  :  "<<baseWeightMCTruthUp<<endl;
  if(ngood ==0){baseWeight=1.0;}
  else {baseWeight=baseWeight/(double)ngood;
        baseWeightUp=baseWeightUp/(double)ngood;

   }
  
  if(ngoodmctruth==0){baseWeightMCTruth=1.0;}
  else {baseWeightMCTruth=baseWeightMCTruth/(double)ngoodmctruth;
        baseWeightMCTruthUp=baseWeightMCTruthUp/(double)ngoodmctruth;
  }*/



  for (int bj = 0; bj <= 5; ++bj)  {
    for (size_t j = 0; j < systematics.size();++j){
      string syst = systematics[j];
      
      int nentries = trees3J[bj][syst]->GetEntries();
      
      trees3J[bj][syst]->Branch("topPtReweightMCTruthNorm", &topPtReweightMCTruthNorm);
      trees3J[bj][syst]->Branch("topPtReweightNorm", &topPtReweightNorm);
      trees3J[bj][syst]->Branch("topPtReweightMCTruthNormUp", &topPtReweightMCTruthNormUp);
      trees3J[bj][syst]->Branch("topPtReweightNormUp", &topPtReweightNormUp);
      trees3J[bj][syst]->Branch("topPtReweightMCTruthNormDown", &topPtReweightMCTruthNormDown);
      trees3J[bj][syst]->Branch("topPtReweightNormDown", &topPtReweightNormDown);

      


  baseWeight=0.0,baseWeightMCTruth=0.0;
  baseWeightUp=0.0,baseWeightMCTruthUp=0.0;
  ngood=0,ngoodmctruth=0; 
  for (int i =0; i< nentries;++i){     
    trees3J[bj][syst]->GetEntry(i);  //cout<<"i: "<<i<<" topPtReweight IN treesMCTruth"<<topPtReweight<<endl;
    if(topPtReweight<1.5){++ngood;
      baseWeight+=topPtReweight;
      baseWeightUp+=topPtReweightUp; 
      }
    if(topPtReweightMCTruth<1.5){++ngoodmctruth;
      baseWeightMCTruth+=topPtReweightMCTruth;
      baseWeightMCTruthUp+=topPtReweightMCTruthUp;
    }
  }
  //cout<<"baseWeightUp  1 : "<<baseWeightUp<< "   baseWeightMCTruthUp 1  :  "<<baseWeightMCTruthUp<<endl;
  if(ngood ==0){baseWeight=1.0;}
  else {baseWeight=baseWeight/(double)ngood;
        baseWeightUp=baseWeightUp/(double)ngood;
        }
  
  if(ngoodmctruth==0){baseWeightMCTruth=1.0;}
  else {baseWeightMCTruth=baseWeightMCTruth/(double)ngoodmctruth;
        baseWeightMCTruthUp=baseWeightMCTruthUp/(double)ngoodmctruth;
       }
for (int i =0; i<nentries;++i){
  trees3J[bj][syst]->GetEntry(i);//cout<<"i: "<<i<<" topPtReweight IN trees3J[bj][syst] "<<topPtReweight<<"  topPtReweightUp "<< topPtReweightUp<<endl;
	topPtReweightNorm = topPtReweight/baseWeight;
	topPtReweightNormUp = topPtReweightUp/baseWeightUp; //cout<<" trees3J[bj][syst]->GetName()   "<< trees3J[bj][syst]->GetName()<<" topPtReweightNorm:  "<<topPtReweightNorm<<" topPtReweightNormUp:  "<<topPtReweightNormUp<<endl;
	topPtReweightNormDown = 1.;
	topPtReweightMCTruthNorm = topPtReweightMCTruth/baseWeightMCTruth;
	topPtReweightMCTruthNormUp = topPtReweightMCTruthUp/baseWeightMCTruthUp;
	topPtReweightMCTruthNormDown = 1.;//topPtReweightMCTruthDown;
	//cout <<  " test 3J " << bj<<" T, syst"<< syst  << "evt # "<<i << "ptrew" << topPtReweight<<" ptrew Norm"<< topPtReweightNorm<<endl;
	trees3J[bj][syst]->GetBranch("topPtReweightMCTruthNorm")->Fill();
	trees3J[bj][syst]->GetBranch("topPtReweightNorm")->Fill();
    trees3J[bj][syst]->GetBranch("topPtReweightMCTruthNormUp")->Fill();
	trees3J[bj][syst]->GetBranch("topPtReweightNormUp")->Fill();
    trees3J[bj][syst]->GetBranch("topPtReweightMCTruthNormDown")->Fill();
	trees3J[bj][syst]->GetBranch("topPtReweightNormDown")->Fill();
      }
      
      nentries =  trees2J[bj][syst]->GetEntries();
      
      trees2J[bj][syst]->Branch("topPtReweightMCTruthNorm", &topPtReweightMCTruthNorm);
      trees2J[bj][syst]->Branch("topPtReweightNorm", &topPtReweightNorm);
      trees2J[bj][syst]->Branch("topPtReweightMCTruthNormUp", &topPtReweightMCTruthNormUp);
      trees2J[bj][syst]->Branch("topPtReweightNormUp", &topPtReweightNormUp);
      trees2J[bj][syst]->Branch("topPtReweightMCTruthNormDown", &topPtReweightMCTruthNormDown);
      trees2J[bj][syst]->Branch("topPtReweightNormDown", &topPtReweightNormDown);
      baseWeight=0.0,baseWeightMCTruth=0.0;
  baseWeightUp=0.0,baseWeightMCTruthUp=0.0;
  ngood=0,ngoodmctruth=0; 
  for (int i =0; i< nentries;++i){     
    trees2J[bj][syst]->GetEntry(i);  
    if(topPtReweight<1.5){++ngood;
      baseWeight+=topPtReweight;
      baseWeightUp+=topPtReweightUp; 
      }
    if(topPtReweightMCTruth<1.5){++ngoodmctruth;
      baseWeightMCTruth+=topPtReweightMCTruth;
      baseWeightMCTruthUp+=topPtReweightMCTruthUp;
    }
  }
  //cout<<"baseWeightUp  1 : "<<baseWeightUp<< "   baseWeightMCTruthUp 1  :  "<<baseWeightMCTruthUp<<endl;
  if(ngood ==0){baseWeight=1.0;}
  else {baseWeight=baseWeight/(double)ngood;
        baseWeightUp=baseWeightUp/(double)ngood;
        }
  
  if(ngoodmctruth==0){baseWeightMCTruth=1.0;}
  else {baseWeightMCTruth=baseWeightMCTruth/(double)ngoodmctruth;
        baseWeightMCTruthUp=baseWeightMCTruthUp/(double)ngoodmctruth;
       }
      for (int i =0; i< nentries;++i){
	trees2J[bj][syst]->GetEntry(i); //cout<<"i: "<<i<<" topPtReweight IN trees3J[bj][syst] "<<topPtReweight<<"  topPtReweightUp "<< topPtReweightUp<<endl;
	topPtReweightNorm = topPtReweight/baseWeight;
    topPtReweightNormUp = topPtReweightUp/baseWeightUp;
	topPtReweightNormDown = topPtReweightDown;
	topPtReweightMCTruthNorm = topPtReweightMCTruth/baseWeightMCTruth;
    topPtReweightMCTruthNormUp = topPtReweightMCTruthUp/baseWeightMCTruthUp;
	topPtReweightMCTruthNormDown = topPtReweightMCTruthDown;

//	cout <<  " test 2J " << bj<<" T, syst"<< syst  << "evt # "<<i << "ptrew" << topPtReweight<<" ptrew Norm"<< topPtReweightNorm<<endl;
	trees2J[bj][syst]->GetBranch("topPtReweightMCTruthNorm")->Fill();
	trees2J[bj][syst]->GetBranch("topPtReweightNorm")->Fill();
    trees2J[bj][syst]->GetBranch("topPtReweightMCTruthNormUp")->Fill();
	trees2J[bj][syst]->GetBranch("topPtReweightNormUp")->Fill();
    trees2J[bj][syst]->GetBranch("topPtReweightMCTruthNormDown")->Fill();
	trees2J[bj][syst]->GetBranch("topPtReweightNormDown")->Fill();
      }

      nentries =  trees4J[bj][syst]->GetEntries();
      
      trees4J[bj][syst]->Branch("topPtReweightMCTruthNorm", &topPtReweightMCTruthNorm);
      trees4J[bj][syst]->Branch("topPtReweightNorm", &topPtReweightNorm);
      trees4J[bj][syst]->Branch("topPtReweightMCTruthNormUp", &topPtReweightMCTruthNormUp);
      trees4J[bj][syst]->Branch("topPtReweightNormUp", &topPtReweightNormUp);
      trees4J[bj][syst]->Branch("topPtReweightMCTruthNormDown", &topPtReweightMCTruthNormDown);
      trees4J[bj][syst]->Branch("topPtReweightNormDown", &topPtReweightNormDown);
  baseWeight=0.0,baseWeightMCTruth=0.0;
  baseWeightUp=0.0,baseWeightMCTruthUp=0.0;
  ngood=0,ngoodmctruth=0; 
  for (int i =0; i< nentries;++i){     
    trees4J[bj][syst]->GetEntry(i);  
    if(topPtReweight<1.5){++ngood;
      baseWeight+=topPtReweight;
      baseWeightUp+=topPtReweightUp; 
      }
    if(topPtReweightMCTruth<1.5){++ngoodmctruth;
      baseWeightMCTruth+=topPtReweightMCTruth;
      baseWeightMCTruthUp+=topPtReweightMCTruthUp;
    }
  }
  //cout<<"baseWeightUp  1 : "<<baseWeightUp<< "   baseWeightMCTruthUp 1  :  "<<baseWeightMCTruthUp<<endl;
  if(ngood ==0){baseWeight=1.0;}
  else {baseWeight=baseWeight/(double)ngood;
        baseWeightUp=baseWeightUp/(double)ngood;
        }
  
  if(ngoodmctruth==0){baseWeightMCTruth=1.0;}
  else {baseWeightMCTruth=baseWeightMCTruth/(double)ngoodmctruth;
        baseWeightMCTruthUp=baseWeightMCTruthUp/(double)ngoodmctruth;
       }

      for (int i =0; i< nentries;++i){
	trees4J[bj][syst]->GetEntry(i);
	topPtReweightNorm = topPtReweight/baseWeight;
    topPtReweightNormUp = topPtReweightUp/baseWeightUp;
	topPtReweightNormDown = topPtReweightDown;
	topPtReweightMCTruthNorm = topPtReweightMCTruth/baseWeightMCTruth;
    topPtReweightMCTruthNormUp = topPtReweightMCTruthUp/baseWeightMCTruthUp;
	topPtReweightMCTruthNormDown = topPtReweightMCTruthDown;

	//cout <<  " test 4J " << bj<<" T, syst"<< syst  << "evt # "<<i << "ptrew" << topPtReweight<<" ptrew Norm"<< topPtReweightNorm<<endl;
	trees4J[bj][syst]->GetBranch("topPtReweightMCTruthNorm")->Fill();
	trees4J[bj][syst]->GetBranch("topPtReweightNorm")->Fill();
    trees4J[bj][syst]->GetBranch("topPtReweightMCTruthNormUp")->Fill();
	trees4J[bj][syst]->GetBranch("topPtReweightNormUp")->Fill();
    trees4J[bj][syst]->GetBranch("topPtReweightMCTruthNormDown")->Fill();
	trees4J[bj][syst]->GetBranch("topPtReweightNormDown")->Fill();
      }
      
    }
  }

}



//Other utilities:

//Variables initialization at nan
void SingleTopSystematicsTreesDumper::initBranchVars()
{
#define INT_NAN 9999
#define FLOAT_NAN 9999.0  
#define DOUBLE_NAN 9999.0


    //ints
    chargeTree = INT_NAN;    runTree = INT_NAN;
    lumiTree = INT_NAN;    eventTree = INT_NAN;
    eventFlavourTree = INT_NAN;    firstJetFlavourTree = INT_NAN;
    secondJetFlavourTree = INT_NAN;       nJ = INT_NAN;
    nJNoPU = INT_NAN;    nJCentral = INT_NAN;    nJCentralNoPU = INT_NAN;
    nJForward = INT_NAN;    nJForwardNoPU = INT_NAN;    nVertices = INT_NAN;
    nJLoose = INT_NAN;    nJLooseCentral = INT_NAN;    nJLooseForward = INT_NAN; nJLooseMBTag = INT_NAN;
    npv = INT_NAN;    ntchpt_tags = INT_NAN;    ncsvt_tags = INT_NAN;    ncsvm_tags = INT_NAN;
    fJetFlavourTree = INT_NAN;    bJetFlavourTree = INT_NAN;    eventFlavourTree = INT_NAN;    nVertices = INT_NAN;
    npv = INT_NAN;    firstJetFlavourTree = INT_NAN;    secondJetFlavourTree = INT_NAN;    thirdJetFlavourTree = INT_NAN;
      fourthJetFlavourTree = INT_NAN;looseJetFlavourTree = INT_NAN;
   
    //doubles
    weightTree = DOUBLE_NAN;    w1TCHPT = DOUBLE_NAN;    w2TCHPT = DOUBLE_NAN;    
    w1CSVT = DOUBLE_NAN;    w2CSVT = DOUBLE_NAN;    w1CSVM = DOUBLE_NAN;    w2CSVM = DOUBLE_NAN;  
    PUWeightTree = DOUBLE_NAN;    lepPt = DOUBLE_NAN;    lepEta = DOUBLE_NAN; lepE = DOUBLE_NAN;   lepPhi = DOUBLE_NAN;    lepDeltaCorrectedRelIso = DOUBLE_NAN;
    lepRhoCorrectedRelIso = DOUBLE_NAN;          lepDeltaCorrectedRelIso = DOUBLE_NAN;
    bJetPt = DOUBLE_NAN;    fJetPt = DOUBLE_NAN;    bJetEta = DOUBLE_NAN;    fJetEta = DOUBLE_NAN;    fJetPUID = DOUBLE_NAN;
    fJetPUWP = DOUBLE_NAN;
    etaTree = DOUBLE_NAN;    cosTree = DOUBLE_NAN;    cosBLTree = DOUBLE_NAN;    mtwMassTree = DOUBLE_NAN;
    chargeTree = INT_NAN;    runTree = INT_NAN;    lumiTree = INT_NAN;    eventTree = INT_NAN;
    weightTree = DOUBLE_NAN;     bWeightTreeBTagUp = DOUBLE_NAN;    bWeightTreeBTagDown = DOUBLE_NAN;    bWeightTreeMisTagUp = DOUBLE_NAN;    bWeightTreeMisTagDown = DOUBLE_NAN;
    PUWeightTree = DOUBLE_NAN;    PUWeightTreePUUp = DOUBLE_NAN;    PUWeightTreePUDown = DOUBLE_NAN;
    fJetPt = DOUBLE_NAN;    fJetE = DOUBLE_NAN;    fJetEta = DOUBLE_NAN;    fJetPhi = DOUBLE_NAN;    fJetBTag = DOUBLE_NAN;
    fJetPUID = DOUBLE_NAN;    fJetPUWP = DOUBLE_NAN;
    bJetPt = DOUBLE_NAN;    bJetE = DOUBLE_NAN;    bJetEta = DOUBLE_NAN;    bJetPhi = DOUBLE_NAN;    bJetBTag = DOUBLE_NAN;
    bJetPUID = DOUBLE_NAN;    bJetPUWP = DOUBLE_NAN;
    firstJetPt = DOUBLE_NAN;    firstJetEta = DOUBLE_NAN;    firstJetPhi = DOUBLE_NAN;    firstJetE = DOUBLE_NAN; firstJetBTag = DOUBLE_NAN;
    secondJetPt = DOUBLE_NAN;    secondJetEta = DOUBLE_NAN;    secondJetPhi = DOUBLE_NAN;    secondJetE = DOUBLE_NAN; secondJetBTag = DOUBLE_NAN;
    thirdJetPt = DOUBLE_NAN;    thirdJetEta = DOUBLE_NAN;    thirdJetPhi = DOUBLE_NAN;    thirdJetE = DOUBLE_NAN; thirdJetBTag = DOUBLE_NAN;
    fourthJetPt = DOUBLE_NAN;    fourthJetEta = DOUBLE_NAN;    fourthJetPhi = DOUBLE_NAN;    fourthJetE = DOUBLE_NAN; fourthJetBTag = DOUBLE_NAN;
    metPt = DOUBLE_NAN;    metPhi = DOUBLE_NAN;
    topMassTree = DOUBLE_NAN;    topMtwTree = DOUBLE_NAN;    topPt = DOUBLE_NAN;    topPhi = DOUBLE_NAN;    topEta = DOUBLE_NAN;    topE = DOUBLE_NAN;
    top1MassTree = DOUBLE_NAN;   top1Pt = DOUBLE_NAN;    top1Phi = DOUBLE_NAN;    top1Eta = DOUBLE_NAN;    top1E = DOUBLE_NAN;
    top2MassTree = DOUBLE_NAN;   top2Pt = DOUBLE_NAN;    top2Phi = DOUBLE_NAN;    top2Eta = DOUBLE_NAN;    top2E = DOUBLE_NAN;
   cos1Tree = DOUBLE_NAN;    cos1BLTree = DOUBLE_NAN; cos2Tree = DOUBLE_NAN;    cos2BLTree = DOUBLE_NAN;
    electronID = DOUBLE_NAN; leptonMVAID = DOUBLE_NAN ;
    totalEnergy = DOUBLE_NAN;    totalMomentum = DOUBLE_NAN;    lowBTagTree = DOUBLE_NAN;    highBTagTree = DOUBLE_NAN;   mediumBTagTree = DOUBLE_NAN; mediumlowBTagTree = DOUBLE_NAN;
    pdf_weights_mstw =FLOAT_NAN;    pdf_weights_nnpdf21=FLOAT_NAN;    pdf_weights_gjr_ff=FLOAT_NAN;    pdf_weights_gjr_fv=FLOAT_NAN;    pdf_weights_gjr_fdis=FLOAT_NAN;    pdf_weights_alekhin=FLOAT_NAN;
    Mlb1Tree= DOUBLE_NAN;         Mlb2Tree= DOUBLE_NAN;            Mb1b2Tree= DOUBLE_NAN;         pTb1b2Tree= DOUBLE_NAN;
    topPtReweightMCTruth = DOUBLE_NAN; topPtReweightMCTruthUp = DOUBLE_NAN;  topPtReweightMCTruthDown = DOUBLE_NAN;
    topPtReweight = DOUBLE_NAN;    topPtReweightUp = DOUBLE_NAN;     topPtReweightDown = DOUBLE_NAN;
    looseJetPt = DOUBLE_NAN;    looseJetEta = DOUBLE_NAN;    looseJetPhi = DOUBLE_NAN;    looseJetE = DOUBLE_NAN; looseJetBTag = DOUBLE_NAN;

    HT = DOUBLE_NAN;
    H = DOUBLE_NAN;
    bJet1Pt = DOUBLE_NAN;
    bJet1Eta = DOUBLE_NAN;
    bJet1Phi = DOUBLE_NAN;
    bJet1E = DOUBLE_NAN;
    bJet2Pt = DOUBLE_NAN;
    bJet2Eta = DOUBLE_NAN;
    bJet2Phi = DOUBLE_NAN;
    bJet2E = DOUBLE_NAN;
bJetRecoilPt = DOUBLE_NAN; bJetRecoilEta = DOUBLE_NAN; bJetRecoilPhi = DOUBLE_NAN; bJetRecoilE = DOUBLE_NAN; bJetRecoilFlavour = DOUBLE_NAN;bJetRecoilBTag = DOUBLE_NAN;
bJetDecayPt = DOUBLE_NAN; bJetDecayEta = DOUBLE_NAN; bJetDecayPhi = DOUBLE_NAN; bJetDecayE = DOUBLE_NAN; bJetDecayFlavour = DOUBLE_NAN;bJetDecayBTag = DOUBLE_NAN;  

    //66 lines

   // topMassTree_best = DOUBLE_NAN;
   // cosTree_best = DOUBLE_NAN;
   // cosBLTree_best = DOUBLE_NAN;

    for (int i = 0; i < 52; i++)
    {
        pdf_weights[i] = FLOAT_NAN;
    }

}

//EndJob 
void SingleTopSystematicsTreesDumper::endJob()
{
  cout << endl << passingLepton << " | " << passingMuonVeto << " | " << passingLeptonVeto << " | "  << passingJets << " | " << passingMET << " | " << passingBJets<< endl;
cout<<"leptonsFlavour_    :"<<leptonsFlavour_<<endl;
cout<<"if(doTopPtReweighting_ && channel != Data)" << doTopPtReweighting_  << " & " << channel <<endl;
   if(doTopPtReweighting_ && channel != "Data") resetWeightsDoubles();

}

//define this as a plug-in
DEFINE_FWK_MODULE(SingleTopSystematicsTreesDumper);
