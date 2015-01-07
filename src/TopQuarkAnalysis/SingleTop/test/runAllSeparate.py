#!/usr/bin/env cmsRun
import FWCore.ParameterSet.Config as cms
import os,sys,re,shutil


#Original config file
fileName = "SingleTopSystematicsWithTrigger_cfg.py"
#fileName = "SingleTopPDFWithTrigger_cfg.py"
#fileName = "SingleTopSystematics_cfg.py"
#fileName = "SingleTopSystematics_split_cfg.py"
#fileName = "SingleTopNEvents_cfg.py"

nSimultaneous = 1

#Channels to include
channels = [

#"DataReRecoA",

    
#"TChannel_MassDown_part_1","TChannel_MassDown_part_2","TChannel_MassDown_part_3","TChannel_MassDown_part_4","TChannel_MassDown_part_5",
#"TChannel_MassUp_part_1","TChannel_MassUp_part_2","TChannel_MassUp_part_3","TChannel_MassUp_part_4","TChannel_MassUp_part_5",
#"TbarChannel_MassDown_part_1","TbarChannel_MassDown_part_2","TbarChannel_MassDown_part_3","TbarChannel_MassDown_part_4","TbarChannel_MassDown_part_5",
#"TbarChannel_MassUp_part_1","TbarChannel_MassUp_part_2","TbarChannel_MassUp_part_3","TbarChannel_MassUp_part_4","TbarChannel_MassUp_part_5",
#"TTBar_MassDown_part_1","TTBar_MassDown_part_2","TTBar_MassDown_part_3","TTBar_MassDown_part_4","TTBar_MassDown_part_5",
#"TTBar_MassUp_part_1","TTBar_MassUp_part_2","TTBar_MassUp_part_3","TTBar_MassUp_part_4","TTBar_MassUp_part_5",
#"TToBTauNu_unphys_part_1","TToBTauNu_unphys_part_2","TToBTauNu_unphys_part_3",
#"TToBTauNu_0100_part_1","TToBTauNu_0100_part_2","TToBTauNu_0100_part_3",
#"TToBMuNu_unphys_part_1","TToBMuNu_unphys_part_2","TToBMuNu_unphys_part_3",
#"TToBMuNu_0100_part_1","TToBMuNu_0100_part_2","TToBMuNu_0100_part_3",
#"TToBTauNu_0100",
#"TToBMuNu_unphys",
#"TToBMuNu_0100",
#"TToBTauNu_part_1","TToBTauNu_part_2","TToBTauNu_part_3",
#"TToBMuNu_part_1","TToBMuNu_part_2","TToBMuNu_part_3",
#"TToBENu_unphys",
#"TToBENu_0100",
#"TToBTauNu",
#"TToBENu",
#"TToBMuNu",

#"TbarWChannelTlepWhad_MassUp",
#"TbarWChannelThadWlep_MassDown",
#"TWChannelTlepWhad_MassUp",
#"TWChannelTlepWhad_MassDown",#
#
#"TbarWChannelThadWlep_MassUp",
#"TbarWChannelTlepWhad_MassDown",
#"TWChannelThadWlep_MassUp",
#"TWChannelThadWlep_MassDown",
#
#"TbarWChannelFullLep_MassDown",
#"TbarWChannelFullLep_MassUp",
#"TWChannelFullLep_MassDown",
#"TWChannelFullLep_MassUp",

#"TBMuNuChannel_Comphep",
#"TBTauNuChannel_Comphep",
#"TBENuChannel_Comphep",
#"QCD_Pt_30to80_EMEnriched","QCD_Pt_30to80_BCtoE","QCD_Pt_80to170_BCtoE",
#"TbarChannel",


#"TChannel_part_1","TChannel_part_2","TChannel_part_3","TChannel_part_4","TChannel_part_5",
#"TbarChannel_part_1","TbarChannel_part_2","TbarChannel_part_3","TbarChannel_part_4","TbarChannel_part_5",
#"TWChannel_part_1","TWChannel_part_2",
#"TbarWChannel_part_1","TbarWChannel_part_2",

"SChannel_part_1", #"SChannel_part_2", "SChannel_part_3", "SChannel_part_4", "SChannel_part_5",
#"SbarChannel_part_1", "SbarChannel_part_2", "SbarChannel_part_3", "SbarChannel_part_4", "SbarChannel_part_5",

#"ZZ_part_1", "ZZ_part_2", "ZZ_part_3", "ZZ_part_4", "ZZ_part_5",
#"WZ_part_1", "WZ_part_2", "WZ_part_3", "WZ_part_4", "WZ_part_5",
#"WW_part_1", "WW_part_2", "WW_part_3", "WW_part_4", "WW_part_5",

#"QCDMuBig_part_1","QCDMuBig_part_2","QCDMuBig_part_3","QCDMuBig_part_4","QCDMuBig_part_5",


#"ZJets_part_1", "ZJets_part_2", "ZJets_part_3", "ZJets_part_4", "ZJets_part_5",
#"W1Jet_part_1","W1Jet_part_2","W1Jet_part_3","W1Jet_part_4","W1Jet_part_5","W1Jet_part_6","W1Jet_part_7","W1Jet_part_8","W1Jet_part_9","W1Jet_part_10",
#"W2Jets_part_1","W2Jets_part_2","W2Jets_part_3","W2Jets_part_4",
#"W2Jets_part_5","W2Jets_part_6","W2Jets_part_7","W2Jets_part_8","W2Jets_part_9","W2Jets_part_10",
#"W3Jets_part_1","W3Jets_part_2","W3Jets_part_3","W3Jets_part_4","W3Jets_part_5","W3Jets_part_6","W3Jets_part_7","W3Jets_part_8","W3Jets_part_9","W3Jets_part_10",
#"W4Jets_part_1","W4Jets_part_2","W4Jets_part_3","W4Jets_part_4","W4Jets_part_5","W4Jets_part_6","W4Jets_part_7","W4Jets_part_8","W4Jets_part_9","W4Jets_part_10",




#"W2Jets_part_11","W2Jets_part_12","W2Jets_part_13","W2Jets_part_14","W2Jets_part_15","W2Jets_part_16","W2Jets_part_17","W2Jets_part_18","W2Jets_part_19","W2Jets_part_20",
#"W2Jets_part_21","W2Jets_part_22","W2Jets_part_23","W2Jets_part_24","W2Jets_part_25",


#"W3Jets_part_11","W3Jets_part_12","W3Jets_part_13","W3Jets_part_14","W3Jets_part_15","W3Jets_part_16","W3Jets_part_17","W3Jets_part_18","W3Jets_part_19","W3Jets_part_20",
#"W3Jets_part_21","W3Jets_part_22",


#"W4Jets_part_11","W4Jets_part_12","W4Jets_part_13","W4Jets_part_14","W4Jets_part_15","W4Jets_part_16","W4Jets_part_17","W4Jets_part_18","W4Jets_part_19","W4Jets_part_20",
#"W4Jets_part_21","W4Jets_part_22","W4Jets_part_23","W4Jets_part_24","W4Jets_part_25",

#"TTBarSemiLep_part_1", "TTBarSemiLep_part_2","TTBarSemiLep_part_3","TTBarSemiLep_part_4", "TTBarSemiLep_part_5", "TTBarSemiLep_part_6", "TTBarSemiLep_part_7", "TTBarSemiLep_part_8", "TTBarSemiLep_part_9","TTBarSemiLep_part_10","TTBarSemiLep_part_11","TTBarSemiLep_part_12", "TTBarSemiLep_part_13","TTBarSemiLep_part_14", "TTBarSemiLep_part_15", "TTBarSemiLep_part_16", "TTBarSemiLep_part_17", "TTBarSemiLep_part_18", "TTBarSemiLep_part_19","TTBarSemiLep_part_20","TTBarSemiLep_part_21","TTBarSemiLep_part_22","TTBarSemiLep_part_23","TTBarSemiLep_part_24","TTBarSemiLep_part_25",

#"TTBarFullLep_part_1", "TTBarFullLep_part_2","TTBarFullLep_part_3","TTBarFullLep_part_4", "TTBarFullLep_part_5", "TTBarFullLep_part_6", "TTBarFullLep_part_7", "TTBarFullLep_part_8", "TTBarFullLep_part_9","TTBarFullLep_part_10",
#"TTBarFullLep_part_11","TTBarFullLep_part_12","TTBarFullLep_part_13","TTBarFullLep_part_14", "TTBarFullLep_part_15", "TTBarFullLep_part_16", "TTBarFullLep_part_17", "TTBarFullLep_part_18", "TTBarFullLep_part_19","TTBarFullLep_part_20","TTBarFullLep_part_21","TTBarFullLep_part_22","TTBarFullLep_part_23","TTBarFullLep_part_24","TTBarFullLep_part_25",

#"TTBarFullLep_part_16","TTBarFullLep_part_25",

#"WJetsBig_part_1","WJetsBig_part_2","WJetsBig_part_3","WJetsBig_part_4","WJetsBig_part_5","WJetsBig_part_6","WJetsBig_part_7","WJetsBig_part_8","WJetsBig_part_9","WJetsBig_part_10",
#"WJetsBig_part_11","WJetsBig_part_12","WJetsBig_part_13","WJetsBig_part_14","WJetsBig_part_15","WJetsBig_part_16","WJetsBig_part_17","WJetsBig_part_18","WJetsBig_part_19","WJetsBig_part_20",
#"WJetsBig_part_21","WJetsBig_part_22",
#"WJets_part_1","WJets_part_2","WJets_part_3","WJets_part_4","WJets_part_5","WJets_part_6","WJets_part_7","WJets_part_8","WJets_part_9","WJets_part_10","WJets_part_11",




#"Mu_A_22Jan_part_1","Mu_A_22Jan_part_2","Mu_A_22Jan_part_3","Mu_A_22Jan_part_4","Mu_A_22Jan_part_5",
#"Mu_A_22Jan_part_6","Mu_A_22Jan_part_7","Mu_A_22Jan_part_8","Mu_A_22Jan_part_9","Mu_A_22Jan_part_10",
#"Mu_B1_22Jan_part_1","Mu_B1_22Jan_part_2","Mu_B1_22Jan_part_3","Mu_B1_22Jan_part_4","Mu_B1_22Jan_part_5",
#"Mu_B2_22Jan_part_1","Mu_B2_22Jan_part_2","Mu_B2_22Jan_part_3","Mu_B2_22Jan_part_4","Mu_B2_22Jan_part_5",
#"Mu_B3_22Jan_part_1","Mu_B3_22Jan_part_2","Mu_B3_22Jan_part_3","Mu_B3_22Jan_part_4","Mu_B3_22Jan_part_5",
#"Mu_B4_22Jan_part_1","Mu_B4_22Jan_part_2","Mu_B4_22Jan_part_3","Mu_B4_22Jan_part_4","Mu_B4_22Jan_part_5",


#"Mu_C1_22Jan_part_1","Mu_C1_22Jan_part_2","Mu_C1_22Jan_part_3","Mu_C1_22Jan_part_4","Mu_C1_22Jan_part_5",
#"Mu_C2_22Jan_part_1","Mu_C2_22Jan_part_2","Mu_C2_22Jan_part_3","Mu_C2_22Jan_part_4","Mu_C2_22Jan_part_5",
#"Mu_C3_22Jan_part_1","Mu_C3_22Jan_part_2","Mu_C3_22Jan_part_3","Mu_C3_22Jan_part_4","Mu_C3_22Jan_part_5",
#"Mu_C4_22Jan_part_1","Mu_C4_22Jan_part_2","Mu_C4_22Jan_part_3","Mu_C4_22Jan_part_4","Mu_C4_22Jan_part_5",
#"Mu_C5_22Jan_part_1","Mu_C5_22Jan_part_2","Mu_C5_22Jan_part_3","Mu_C5_22Jan_part_4","Mu_C5_22Jan_part_5",
#"Mu_C6_22Jan_part_1","Mu_C6_22Jan_part_2","Mu_C6_22Jan_part_3","Mu_C6_22Jan_part_4","Mu_C6_22Jan_part_5",

#"Mu_D1_22Jan_part_1","Mu_D1_22Jan_part_2","Mu_D1_22Jan_part_3","Mu_D1_22Jan_part_4","Mu_D1_22Jan_part_5","Mu_D1_22Jan_part_6",
#"Mu_D2_22Jan_part_1","Mu_D2_22Jan_part_2","Mu_D2_22Jan_part_3","Mu_D2_22Jan_part_4","Mu_D2_22Jan_part_5","Mu_D2_22Jan_part_6",
#"Mu_D3_22Jan_part_1","Mu_D3_22Jan_part_2","Mu_D3_22Jan_part_3","Mu_D3_22Jan_part_4","Mu_D3_22Jan_part_5","Mu_D3_22Jan_part_6",
#"Mu_D4_22Jan_part_1","Mu_D4_22Jan_part_2","Mu_D4_22Jan_part_3","Mu_D4_22Jan_part_4","Mu_D4_22Jan_part_5","Mu_D4_22Jan_part_6",
#"Mu_D5_22Jan_part_1","Mu_D5_22Jan_part_2","Mu_D5_22Jan_part_3","Mu_D5_22Jan_part_4","Mu_D5_22Jan_part_5","Mu_D5_22Jan_part_6",
#"Mu_D6_22Jan_part_1","Mu_D6_22Jan_part_2","Mu_D6_22Jan_part_3","Mu_D6_22Jan_part_4","Mu_D6_22Jan_part_5","Mu_D6_22Jan_part_6",


#"Mu_C2_part_1","Mu_C2_part_2","Mu_C2_part_3","Mu_C2_part_4","Mu_C2_part_5","Mu_C2_part_6","Mu_C2_part_7","Mu_C2_part_8","Mu_C2_part_9","Mu_C2_part_10","Mu_C2_part_11","Mu_C2_part_12","Mu_C2_part_13","Mu_C2_part_14","Mu_C2_part_15","Mu_C2_part_16","Mu_C2_part_17","Mu_C2_part_18","Mu_C2_part_19","Mu_C2_part_20","Mu_C2_part_21","Mu_C2_part_22",




#"Mu_A06Aug_part_1","Mu_A06Aug_part_2","Mu_A06Aug_part_3",

#"Ele_A06Aug_part_1","Ele_A06Aug_part_2","Ele_A06Aug_part_3",
#"Ele_B13Jul_part_1","Ele_B13Jul_part_2","Ele_B13Jul_part_3","Ele_B13Jul_part_4","Ele_B13Jul_part_5","Ele_B13Jul_part_6","Ele_B13Jul_part_7","Ele_B13Jul_part_8","Ele_B13Jul_part_9","Ele_B13Jul_part_10","Ele_B13Jul_part_11","Ele_B13Jul_part_12","Ele_B13Jul_part_13","Ele_B13Jul_part_14","Ele_B13Jul_part_15","Ele_B13Jul_part_16","Ele_B13Jul_part_17","Ele_B13Jul_part_18","Ele_B13Jul_part_19","Ele_B13Jul_part_20","Ele_B13Jul_part_21","Ele_B13Jul_part_22",    

#"Ele_A13Jul_part_1","Ele_A13Jul_part_2","Ele_A13Jul_part_3","Ele_A13Jul_part_4","Ele_A13Jul_part_5","Ele_A13Jul_part_6","Ele_A13Jul_part_7","Ele_A13Jul_part_8",

#"Ele_C2_part_1","Ele_C2_part_2","Ele_C2_part_3","Ele_C2_part_4","Ele_C2_part_5","Ele_C2_part_6","Ele_C2_part_7","Ele_C2_part_8","Ele_C2_part_9","Ele_C2_part_10","Ele_C2_part_11","Ele_C2_part_12","Ele_C2_part_13","Ele_C2_part_14","Ele_C2_part_15","Ele_C2_part_16","Ele_C2_part_17","Ele_C2_part_18","Ele_C2_part_19","Ele_C2_part_20","Ele_C2_part_21","Ele_C2_part_22",

#"Ele_C1_part_1","Ele_C1_part_2","Ele_C1_part_3","Ele_C1_part_4","Ele_C1_part_5","Ele_C1_part_6","Ele_C1_part_7","Ele_C1_part_8",

#"TChannel", "TbarChannel",
#"SChannel", "SbarChannel",
# "TTBar_MatchingUp", "TTBar_MatchingDown",
#"WW_part_1","WW_part_2","WW_part_3",
#"WW",
#"WZ","ZZ",

#"TTBar_part_1", "TTBar_part_2","TTBar_part_3","TTBar_part_4", "TTBar_part_5", "TTBar_part_6", "TTBar_part_7", "TTBar_part_11", "TTBar_part_10", "TTBar_part_8", "TTBar_part_9",
#"Mu_v1_A_part_1", "Mu_v1_A_part_2", "Mu_v1_A_part_3", "Mu_v1_A_part_4", "Mu_v1_A_part_5", "Mu_v1_A_part_6", "Mu_v1_A_part_7",

#"Mu_v1_B1_part_1", "Mu_v1_B1_part_2", "Mu_v1_B1_part_3", "Mu_v1_B1_part_4", "Mu_v1_B1_part_5", "Mu_v1_B1_part_6", "Mu_v1_B1_part_7", "Mu_v1_B1_part_8", "Mu_v1_B1_part_9","Mu_v1_B1_part_11", "Mu_v1_B1_part_12", "Mu_v1_B1_part_13", "Mu_v1_B1_part_14", "Mu_v1_B1_part_15", "Mu_v1_B1_part_16", "Mu_v1_B1_part_17", "Mu_v1_B1_part_18", "Mu_v1_B1_part_10", "Mu_v1_B1_part_20","Mu_v1_B1_part_19","Mu_v1_B1_part_21",

#"Ele_v1_A_part_1", "Ele_v1_A_part_2", "Ele_v1_A_part_3", "Ele_v1_A_part_4", "Ele_v1_A_part_5", "Ele_v1_A_part_6", "Ele_v1_A_part_7"
# "Mu_v1_B2_part_1", "Mu_v1_B2_part_2", "Mu_v1_B2_part_3", "Mu_v1_B2_part_4", "Mu_v1_B2_part_5", "Mu_v1_B2_part_6", "Mu_v1_B2_part_7", "Mu_v1_B2_part_8", "Mu_v1_B2_part_9","Mu_v1_B2_part_10","Mu_v1_B2_part_11",

# "Ele_v1_B2_part_1", "Ele_v1_B2_part_2", "Ele_v1_B2_part_3", "Ele_v1_B2_part_4", "Ele_v1_B2_part_5", "Ele_v1_B2_part_6", "Ele_v1_B2_part_7", "Ele_v1_B2_part_8", "Ele_v1_B2_part_9",

#"TChannel_Q2Up_part_1","TChannel_Q2Up_part_2","TChannel_Q2Up_part_3","TChannel_Q2Up_part_4","TChannel_Q2Up_part_5",
#"TChannel_Q2Down_part_1","TChannel_Q2Down_part_2","TChannel_Q2Down_part_3","TChannel_Q2Down_part_4","TChannel_Q2Down_part_5",
#"TbarChannel_Q2Up_part_1","TbarChannel_Q2Up_part_2","TbarChannel_Q2Up_part_3","TbarChannel_Q2Up_part_4","TbarChannel_Q2Up_part_5",
#"TbarChannel_Q2Down_part_1","TbarChannel_Q2Down_part_2","TbarChannel_Q2Down_part_3","TbarChannel_Q2Down_part_4","TbarChannel_Q2Down_part_5",
##"TbarWChannel", "TWChannel",
#"TTBar_Q2Up",
#"TTBar_Q2Down",
#"TTBar_Q2Up_part_1","TTBar_Q2Up_part_2","TTBar_Q2Up_part_3","TTBar_Q2Up_part_4","TTBar_Q2Up_part_5",
#"TTBar_Q2Down_part_1","TTBar_Q2Down_part_2","TTBar_Q2Down_part_3","TTBar_Q2Down_part_4","TTBar_Q2Down_part_5",
#"TbarChannel_Q2Up", "TbarChannel_Q2Down",
#"TChannel_Q2Up", "TChannel_Q2Down",
#"TbarWChannelFullLep_Q2Up",
#"TbarWChannelFullLep_Q2Down",
#"TWChannelFullLep_Q2Up",
#"TWChannelFullLep_Q2Down",
#"TWChannelTlepWhad_Q2Down",
#"TWChannelTlepWhad_Q2Up",
#"TbarWChannelTlepWhad_Q2Down",
#"TbarWChannelTlepWhad_Q2Up",
#"TWChannelThadWlep_Q2Down",
#"TWChannelThadWlep_Q2Up",
#"TbarWChannelThadWlep_Q2Down",
#"TbarWChannelThadWlep_Q2Up",
#"WJets_Q2Down_part_1","WJets_Q2Down_part_2","WJets_Q2Down_part_3","WJets_Q2Down_part_4","WJets_Q2Down_part_5",
#"WJets_Q2Up_part_1","WJets_Q2Up_part_2","WJets_Q2Up_part_3","WJets_Q2Up_part_4","WJets_Q2Up_part_5",
#"WJets_MatchingDown_part_1","WJets_MatchingDown_part_2","WJets_MatchingDown_part_3","WJets_MatchingDown_part_4","WJets_MatchingDown_part_5",
#"WJets_MatchingUp_part_1","WJets_MatchingUp_part_2","WJets_MatchingUp_part_3","WJets_MatchingUp_part_4","WJets_MatchingUp_part_5",
# "WW", "ZZ", "WZ",
#"ZJets",
 ]

#Path to take data merged files
dataPath = "file:/tmp/mmerola/"

#Choose if you want to run or just prepare the configuration files
mode = ""
mode = "cmsRun"


#Use mu , ele or both

channel_instruction = "all"

#Implementation:

#Function to replace a sequence of characters channelOld to channelNew in a file 
def changeChannel(fileName,channelOld,channelNew,switch,isMC): 
    print " Channel test " + channelNew
    channelToReplace = channelNew
    channelToReplaceInTree = channelNew
    if "Data" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "Data"
    if ("Mu" in channelNew or "Ele" in channelNew) and not "QCDMu" in channelNew and not "Channel" in channelNew and not "TTo" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "Data"
    if "WJets_wlight" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "WJets_wlight"
    if "WJets_wcc" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "WJets_wcc"
    if "WJets_wbb" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "WJets_wbb"
    if "ZJets_wlight" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "ZJets_wlight"
    if "ZJets_wcc" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "ZJets_wcc"
    if "ZJets_wbb" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "ZJets_wbb"
    #    if "TTBar" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
    #        channelToReplace = "TTBar"
    if "QCDMu" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "QCDMu"
    if "WJets" in channelNew and not ("Q2" in channelNew) and not ("Matching" in channelNew):# == "DataMu" or channelNew == "DataMuQCD":
        channelToReplace = "WJets"
    if "W1Jet" in channelNew and not ("Q2" in channelNew) and not ("Matching" in channelNew):# == "DataMu" or channelNew == "DataMuQCD":
        channelToReplace = "W1Jet"
    if "W2Jets" in channelNew and not ("Q2" in channelNew) and not ("Matching" in channelNew):# == "DataMu" or channelNew == "DataMuQCD":
        channelToReplace = "W2Jets"
    if "W3Jets" in channelNew and not ("Q2" in channelNew) and not ("Matching" in channelNew):# == "DataMu" or channelNew == "DataMuQCD":
        channelToReplace = "W3Jets"
    if "W4Jets" in channelNew and not ("Q2" in channelNew) and not ("Matching" in channelNew):# == "DataMu" or channelNew == "DataMuQCD":
        channelToReplace = "W4Jets"
    if "ZJets" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "ZJets"
#    if "TTBar" in channelNew and not ("Q2" in channelNew) and not ("Matching" in channelNew) and not ("Mass" in channelNew):# == "DataMu" or channelNew == "DataMuQCD":
#        channelToReplace = "TTBar"
    if "TChannel" in channelNew and not ("Q2" in channelNew) and not ("Matching" in channelNew) and not ("Mass" in channelNew):# == "DataMu" or channelNew == "DataMuQCD":
        channelToReplace = "TChannel"
    if "TbarChannel" in channelNew and not ("Q2" in channelNew) and not ("Matching" in channelNew) and not ("Mass" in channelNew):# == "DataMu" or channelNew == "DataMuQCD"::# == "DataMu" or channelNew == "DataMuQCD":
        channelToReplace = "TbarChannel"
    if "TWChannel" in channelNew and not ("Q2" in channelNew) and not ("Matching" in channelNew) and not ("Mass" in channelNew):# == "DataMu" or channelNew == "DataMuQCD":
        channelToReplace = "TWChannel"
    if "TbarWChannel" in channelNew and not ("Q2" in channelNew) and not ("Matching" in channelNew) and not ("Mass" in channelNew):# == "DataMu" or channelNew == "DataMuQCD"::# == "DataMu" or channelNew == "DataMuQCD":
        channelToReplace = "TbarWChannel"        
    if "SChannel" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "SChannel"
    if "SbarChannel" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "SbarChannel"
    if "ToBMuNu" in channelNew and not ("unphys" in channelNew) and not ("0100" in channelNew):# == "DataMu" or channelNew == "DataMuQCD":
        channelToReplace = "TToBMuNu"
    if "ToBMuNu_unphys" in channelNew:
        channelToReplace = "TToBMuNu_unphys"
    if "ToBMuNu_0100" in channelNew:
        channelToReplace = "TToBMuNu_0100"
    if "ToBTauNu" in channelNew and not ("unphys" in channelNew) and not ("0100" in channelNew):# == "DataTau" or channelNew == "DataTauQCD":
        channelToReplace = "TToBTauNu"
    if "ToBTauNu_unphys" in channelNew:
        channelToReplace = "TToBTauNu_unphys"
    if "ToBTauNu_0100" in channelNew:
        channelToReplace = "TToBTauNu_0100"
    if "TTBarFullLep" in channelNew:
        channelToReplace = "TTBarFullLep"
    if "TTBarSemiLep" in channelNew:
        channelToReplace = "TTBarSemiLep"
    if "WJets_Q2Up" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "WJets_Q2Up"
    if "WJets_Q2Down" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "WJets_Q2Down"
    if "TTBar_Q2Up" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "TTBar_Q2Up"
    if "TTBar_Q2Down" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "TTBar_Q2Down"
    if "TTBar_MassUp" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "TTBar_MassUp"
    if "TTBar_MassDown" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "TTBar_MassDown"
    if "TChannel_Q2Up" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "TChannel_Q2Up"
    if "TChannel_Q2Down" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "TChannel_Q2Down"
    if "TbarChannel_Q2Up" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "TbarChannel_Q2Up"
    if "TbarChannel_Q2Down" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "TbarChannel_Q2Down"
    if "TChannel_MassUp" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "TChannel_MassUp"
    if "TChannel_MassDown" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "TChannel_MassDown"
    if "TbarChannel_MassUp" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "TbarChannel_MassUp"
    if "TbarChannel_MassDown" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "TbarChannel_MassDown"
    if "WJets_MatchingUp" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "WJets_MatchingUp"
    if "WJets_MatchingDown" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "WJets_MatchingDown"
    if "WW" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "WW"
    if "WZ" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "WZ"
    if "ZZ" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "ZZ"
          #if channelNew=="DataEle":
       # channelNew_2 = "Data"
    file = open(fileName)
    lines = file.readlines()
    o = open(channelNew+"_cfg.py","w") 
    for line in lines:
        if '"channel_instruction"' in line:
            print line
            line = line.replace('"channel_instruction"','"'+switch+'"')
            print line
        if "MC_instruction" in line and "False" in line:
       #     if "False" in line:
                print line
                line = line.replace("False",isMC)
                print line
        words = line.split()
        for word in words:
            if channelOld in word:  
                #                print " line old " + line
                if (not switch == "all") and ("process.TFileService" in line):
                    line = line.replace(word,word.replace(channelOld,channelNew))
                    print "process.TFileService in line,switch " + switch +" line: \n" +line
                    
                else:
                    line = line.replace(word,word.replace(channelOld,channelToReplace))
                
        o.write(line)   
    #if channel == "Data":#Temporary inelegant solution due to the separation of mu/e: will fix it at some point
        #        line = "process.source.fileNames = cms.untracked.vstring('"+dataPath+"DataMuMerged.root','"+dataPath+"DataEleMerged.root',)"
        #        line = "process.source.fileNames = cms.untracked.vstring('"+dataPath+"DataMuMerged.root',)"
        #       line = "process.source.fileNames = cms.untracked.vstring('"+dataPath+"Mu_v1Merged.root','"+dataPath+"Mu_v2Merged.root','"+dataPath+"Ele_v1Merged.root','"+dataPath+"Ele_v2Merged.root',)"
    if "WJets" in channelNew and not ("Q2" in channelNew) and not ("Matching" in channelNew):# == "DataMu" or channelNew == "DataMuQCD":
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"WJets")
        inputs = inputs +")"
        o.write(inputs)
    if "W1Jet" in channelNew and not ("Q2" in channelNew) and not ("Matching" in channelNew):# == "DataMu" or channelNew == "DataMuQCD":
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"W1Jet")
        inputs = inputs +")"
        o.write(inputs)
    if "W2Jets" in channelNew and not ("Q2" in channelNew) and not ("Matching" in channelNew):# == "DataMu" or channelNew == "DataMuQCD":
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"W2Jets")
        inputs = inputs +")"
        o.write(inputs)
    if "W3Jets" in channelNew and not ("Q2" in channelNew) and not ("Matching" in channelNew):# == "DataMu" or channelNew == "DataMuQCD":
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"W3Jets")
        inputs = inputs +")"
        o.write(inputs)
    if "W4Jets" in channelNew and not ("Q2" in channelNew) and not ("Matching" in channelNew):# == "DataMu" or channelNew == "DataMuQCD":
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"W4Jets")
        inputs = inputs +")"
        o.write(inputs)
        
    if "WJets_Q2Down" in channelNew:
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"WJets_Q2Down")
        inputs = inputs +")"
        o.write(inputs)
    if "WJets_Q2Up" in channelNew:
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"WJets_Q2Up")
        inputs = inputs +")"
        o.write(inputs)
    if "TTBar_Q2Down" in channelNew:
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"TTBar_Q2Down")
        inputs = inputs +")"
        o.write(inputs)
    if "TTBar_Q2Up" in channelNew:
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"TTBar_Q2Up")
        inputs = inputs +")"
        o.write(inputs)
    if "TTBar_MassDown" in channelNew:
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"TTBar_MassDown")
        inputs = inputs +")"
        o.write(inputs)
    if "TTBar_MassUp" in channelNew:
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"TTBar_MassUp")
        inputs = inputs +")"
        o.write(inputs)
    if "WJets_MatchingDown" in channelNew:
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"WJets_MatchingDown")
        inputs = inputs +")"
        o.write(inputs)
    if "WJets_MatchingUp" in channelNew:
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"WJets_MatchingUp")
        inputs = inputs +")"
        o.write(inputs)
    if "TChannel" in channelNew and not ("Q2" in channelNew) and not ("Matching" in channelNew) and not ("Mass" in channelNew):# == "DataMu" or channelNew == "DataMuQCD":
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"TChannel")
        inputs = inputs +")"
        o.write(inputs)
    if "TbarChannel" in channelNew and not ("Q2" in channelNew) and not ("Matching" in channelNew) and not ("Mass" in channelNew):# == "DataMu" or channelNew == "DataMuQCD":
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"TbarChannel")
        inputs = inputs +")"
        o.write(inputs)
    if "TWChannel" in channelNew and not ("Q2" in channelNew) and not ("Matching" in channelNew) and not ("Mass" in channelNew):# == "DataMu" or channelNew == "DataMuQCD":
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"TWChannel")
        inputs = inputs +")"
        o.write(inputs)
    if "TbarWChannel" in channelNew and not ("Q2" in channelNew) and not ("Matching" in channelNew) and not ("Mass" in channelNew):# == "DataMu" or channelNew == "DataMuQCD":
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"TbarWChannel")
        inputs = inputs +")"
        o.write(inputs)        
    if "SChannel" in channelNew:# == "DataMu" or channelNew == "DataMuQCD":
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"SChannel")
        inputs = inputs +")"
        o.write(inputs)
    if "SbarChannel" in channelNew:# == "DataMu" or channelNew == "DataMuQCD":
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"SbarChannel")
        inputs = inputs +")"
        o.write(inputs)
    if "TChannel_Q2Down" in channelNew:
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"TChannel_Q2Down")
        inputs = inputs +")"
        o.write(inputs)
    if "TChannel_Q2Up" in channelNew:
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"TChannel_Q2Up")
        inputs = inputs +")"
        o.write(inputs)
    if "TbarChannel_Q2Down" in channelNew:
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"TbarChannel_Q2Down")
        inputs = inputs +")"
        o.write(inputs)
    if "TbarChannel_Q2Up" in channelNew:
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"TbarChannel_Q2Up")
        inputs = inputs +")"
        o.write(inputs)
    if "TChannel_MassDown" in channelNew:
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"TChannel_MassDown")
        inputs = inputs +")"
        o.write(inputs)
    if "TChannel_MassUp" in channelNew:
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"TChannel_MassUp")
        inputs = inputs +")"
        o.write(inputs)
    if "TbarChannel_MassDown" in channelNew:
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"TbarChannel_MassDown")
        inputs = inputs +")"
        o.write(inputs)
    if "TbarChannel_MassUp" in channelNew:
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"TbarChannel_MassUp")
        inputs = inputs +")"
        o.write(inputs)
    if "ZJets" in channelNew:# == "DataMu" or channelNew == "DataMuQCD":
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"ZJets")
        inputs = inputs +")"
        o.write(inputs)
    if "TTBarFullLep" in channelNew and not ("Q2" in channelNew) and not ("Matching" in channelNew):# == "DataMu" or channelNew == "DataMuQCD":
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"TTBarFullLep")
        inputs = inputs +")"
        o.write(inputs)
    if "TTBarSemiLep" in channelNew and not ("Q2" in channelNew) and not ("Matching" in channelNew):# == "DataMu" or channelNew == "DataMuQCD":
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"TTBarSemiLep")
        inputs = inputs +")"
        o.write(inputs)
#    if "TTBar" in channelNew and not ("Q2" in channelNew) and not ("Matching" in channelNew) and not ("Mass" in channelNew):# == "DataMu" or channelNew == "DataMuQCD"::# == "DataMu" or channelNew == "DataMuQCD":
#        inputs = "process.source.fileNames = cms.untracked.vstring("
#        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
#        inputs = inputs.replace(channelToReplace,"TTBar")
#        inputs = inputs +")"
#        o.write(inputs)
    if "WW" in channelNew:# == "DataMu" or channelNew == "DataMuQCD":
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"WW")
        inputs = inputs +")"
        o.write(inputs)
    if "WZ" in channelNew:# == "DataMu" or channelNew == "DataMuQCD":
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"WZ")
        inputs = inputs +")"
        o.write(inputs)
    if "ZZ" in channelNew:# == "DataMu" or channelNew == "DataMuQCD":
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"ZZ")
        inputs = inputs +")"
        o.write(inputs)
    if "TToBMuNu" in channelNew and not ("unphys" in channelNew or "0100" in channelNew ):# == "DataMu" or channelNew == "DataMuQCD":
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"TToBMuNu")
        inputs = inputs +")"
        o.write(inputs)
    if "TToBMuNu_0100" in channelNew:
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"TToBMuNu_0100")
        inputs = inputs +")"
        o.write(inputs)
    if "TToBMuNu_unphys" in channelNew:
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"TToBMuNu_unphys")
        inputs = inputs +")"
        o.write(inputs)
    if "TToBTauNu" in channelNew and not ("unphys" in channelNew or "0100" in channelNew ):# == "DataTau" or channelNew == "DataTauQCD":
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"TToBTauNu")
        inputs = inputs +")"
        o.write(inputs)
    if "TToBTauNu_0100" in channelNew:
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"TToBTauNu_0100")
        inputs = inputs +")"
        o.write(inputs)
    if "TToBTauNu_unphys" in channelNew:
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"TToBTauNu_unphys")
        inputs = inputs +")"
        o.write(inputs)
    if ("Mu" in channelNew or "Ele" in channelNew) and not "TTo" in channelNew:# == "DataMu" or channelNew == "DataMuQCD":
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
#        inputs = inputs +"'"+dataPath+"Mu_v4p1Merged.root',"
#        inputs = inputs +"'"+dataPath+"Mu_v4p2Merged.root',"
#        inputs = inputs +"'"+dataPath+"Mu_v4p3Merged.root',"
#        inputs = inputs +"'"+dataPath+"Mu_v4Merged.root',"
#        inputs = inputs +"'"+dataPath+"Mu_v2Merged.root',"
        inputs = inputs +")"
        o.write(inputs)
    #if "TTBar" in channelNew:# == "DataMu" or channelNew == "DataMuQCD":
    #    inputs = "process.source.fileNames = cms.untracked.vstring("
    #    inputs = inputs +"'"+dataPath+channel+"Merged.root',"
    #    inputs = inputs.replace(channelToReplace,"TTBar")
    #    inputs = inputs +")"
    #    o.write(inputs)
#    if "Ele" in channelNew:#channelNew == "DataEle" or channelNew == "DataEleQCD":
#        inputs = "process.source.fileNames = cms.untracked.vstring("
#        inputs = inputs +"'"+dataPath+"Merged.root',"
##        inputs = inputs +"'"+dataPath+"Ele_v4.root',"
##        inputs = inputs +"'"+dataPath+"Ele_v2Merged.root',"
##        inputs = inputs +"'"+dataPath+"Ele_v1Merged.root',"
#        inputs = inputs +")"
#        o.write(inputs)
    o.close()
    return o

#Implementation of the loop part:

#Channel in the original file
startChannel = "TChannel"#channels[0]
nstart = 0;

f= open(fileName)

tmpName = "temp.py"
shutil.copy(fileName,tmpName)

for channel in channels:

    isMC = "False"
    if "Mu" in channel and not "QCD" in channel and not "TTo" in channel:
        channel_instruction = "mu"
    elif "Ele" in channel and not "QCD" in channel and not "TTo" in channel:
        channel_instruction = "ele"
    elif "Ele" in channel and not "QCD" in channel and not "TTo" in channel:
        channel_instruction = "ele"
    elif "Mu" in channel and ("QCD" in channel or "Had" in channel) and not "QCDMu" in channel and not "TTo" in channel:
        channel_instruction = "muqcd"
    elif "Ele" in channel and "QCD" in channel and not "TTo" in channel:
        channel_instruction = "eleqcd"
    else : 
        channel_instruction = "allmc"   
        isMC = "True"
    channelOld = startChannel
    
    cfg_file = changeChannel(tmpName,channelOld,channel,channel_instruction,isMC)
    command = 'nohup cmsRun ./' + channel+'_cfg.py > /tmp/mmerola/'+channel+'.log &'
    
    print command

    nstart = nstart +1
    if mode == "cmsRun":
        if nstart % nSimultaneous ==0 :
            command = 'nohup cmsRun ./' + channel+'_cfg.py > /tmp/mmerola/'+channel+'.log '
        else:
            command = 'nohup cmsRun ./' + channel+'_cfg.py > /tmp/mmerola/'+channel+'.log &'
            
        os.system(command)
                                                        

#os.system('rm '+tmpName) 



