#!/usr/bin/env cmsRun
import FWCore.ParameterSet.Config as cms
import os,sys,re,shutil


#Original config file
fileName = "SingleTopSystematicsJetsWithTrigger_cfg.py"
#fileName = "SingleTopPDFWithTrigger_cfg.py"
#fileName = "SingleTopSystematics_cfg.py"
#fileName = "SingleTopSystematics_split_cfg.py"
#fileName = "SingleTopNEvents_cfg.py"

#Channels to include
channels = [
# "SChannel",
# "SbarChannel",
 "TTBar_Q2Up",
 "TTBar_Q2Down",
# "TChannel",
# "TbarChannel",
# "TTBar",
# "TbarWChannel",
# "TWChannel",
## "TbarChannel_Q2Up",
 #"TbarChannel_Q2Down",
# "Ele_May10",
# "QCD_HT_40_100_GJets",
# "QCD_HT_100_200_GJets",
# "QCD_HT_200_inf_GJets",
# "WW",
# "ZZ",
# "WZ",
#  "DataMuHadMay10",
#  "Mu_v4_part_1",
#  "Mu_v4_part_2",
#  "Mu_v4_part_3",
#  "Mu_v4_part_4",
#  "Mu_v4_part_5",
#  "Mu_v4_part_6",
#  "Mu_v4_part_7",
#  "Mu_v4_part_8",
#  "Mu_v4_part_9",
#  "EleHad_v4_part_1",
#  "EleHad_v4_part_2",
#  "EleHad_v4_part_3",
#  "EleHad_v4_part_4",
#  "EleHad_v4_part_5",
#  "EleHad_v4_part_6",
#  "EleHad_v4_part_7",
#  "EleHad_v4_part_8",
#  "EleHad_v4_part_9",
#  "Mu_Aug05_part_1",
#  "Mu_Aug05_part_2",
#  "Mu_Aug05_part_3",
#  "Mu_May10",
#  "Ele_May10_part_1",
#  "Ele_May10_part_2",
#  "Ele_May10_part_3",
#  "Mu_May10_part_1",
#  "Mu_May10_part_2",
#  "Mu_May10_part_3",
#  "Mu_May10_part_4",
#  "Mu_May10_part_5",
#  "EleHad_Aug05_part_1",
#  "EleHad_Aug05_part_2",
#  "EleHad_Aug05_part_3",
#  "EleHad_Aug05_part_4",
#  "EleHad_Aug05_part_5",
#  "Ele_May10",
#  "EleHad_v4_part_1",
#  "EleHad_v4_part_2",
#  "EleHad_v4_part_3",
#  "EleHad_v4_part_4",
#  "EleHad_v4_part_5",
#  "EleHad_v4_part_6",
#  "EleHad_v4_part_7",
#  "DataEleV4",
##  "DataEleVControl",
##  "DataMuV12",
#Sin##  "DataMuQCDV12",
##  "DataEleQCDV4",
###  "DataEleQCDV12",
#####
# "SChannel",
# "SbarChannel",
# "TChannel",
# "TbarChannel",
# "SChannel",
# "SbarChannel",
####
#"QCDMu_part_1",
#"QCDMu_part_2",
#"QCDMu_part_3",
#"QCDMu_part_4",
#"QCDMu_part_5",
#"QCDMu_part_6",
#"QCDMu_part_7",
######
# "QCD_Pt_30to80_BCtoE",
## "QCD_Pt_20to30_BCtoE",
# "QCD_Pt_80to170_BCtoE",
####cc###
# "QCD_Pt_20to30_EMEnriched",
# "QCD_Pt_30to80_EMEnriched",
# "QCD_Pt_80to170_EMEnriched",
#####
# "HT_100_200",
# "HT_40_100",
# "HT_200",
#####
# "TTBar",
### 
# "ZJets",
# "ZJets_wlight",#
# "ZJets_wcc",
# "ZJets_wbb",
# "TChannel",
# "SChannel",#
###
#"ZJets_wlight_part_1",
#"ZJets_wlight_part_2",
#"ZJets_wlight_part_3",
#ZJets_wbb4",    
# "ZJets_wlight_part_1",#
# "ZJets_wcc_part_1",#
# "ZJets_wbb_part_1",#
# "ZJets_wcc",
# "ZJets_wbb",
# "TChannel",
# "SChannel",#
###
#"WJets_wbb_part_11",
#"WJets_wbb_part_12",
#"WJets_wbb_part_13",
#"WJets_wbb_part_14",
#"WJets_wbb_part_10",
#"WJets_wbb_part_15",
#"WJets_wbb_part_16",
#"WJets_wbb_part_17",
#"WJets_wbb_part_18",
#"WJets_wbb_part_19",
#"WJets_wbb_part_20",
#"WJets_wbb_part_21",
#"WJets_wbb_part_22",
#"WJets_wbb_part_9",
#"WJets_wbb_part_8",
#"WJets_wbb_part_7",
#"WJets_wbb_part_6",
#"WJets_wbb_part_5",
#"WJets_wbb_part_4",
#"WJets_wbb_part_3",
#"WJets_wbb_part_2",
#"WJets_wbb_part_1",
#"WJets_wcc_part_11 ",
#"WJets_wcc_part_12",
#"WJets_wcc_part_13",
#"WJets_wcc_part_14",
#"WJets_wcc_part_10",
#"WJets_wcc_part_9",
#"WJets_wcc_part_8",
#"WJets_wcc_part_7",
#"WJets_wcc_part_6",
#"WJets_wcc_part_5",
#"WJets_wcc_part_4",
#"WJets_wcc_part_3",
#"WJets_wcc_part_2",
#"WJets_wcc_part_1",
#"WJets_wlight_part_11 ",
#"WJets_wlight_part_12",
#"WJets_wlight_part_13",
#"WJets_wlight_part_14",
#"WJets_wlight_part_10",
#"WJets_wlight_part_9",
#"WJets_wlight_part_8",
#"WJets_wlight_part_7",
#"WJets_wlight_part_6",
#"WJets_wlight_part_5",
#"WJets_wlight_part_4",
#"WJets_wlight_part_3",
#"WJets_wlight_part_2",
#"WJets_wlight_part_1",
#"WJets_wcc_part_11",
#"WJets_wcc_part_12",
#"WJets_wcc_part_13",
#"WJets_wcc_part_14",
#"WJets_wbb_part_10",
#"WJets_wcc_part_9",
#"WJets_wcc_part_8",
#"WJets_wcc_part_7",
#"WJets_wcc_part_6",
#"WJets_wcc_part_5",
#"WJets_wcc_part_4",
#"WJets_wcc_part_3",
#"WJets_wcc_part_2",
#"WJets_wcc_part_1",
#"WJets",
#"Wc_wc",cfa
# "Vqq_wbbB",
# "Vqq_wcc",
# "WW",
# "WZ",
# "ZZ",
 ]

#Path to take data merged files
dataPath = "file:/tmp/oiorio/"

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
    if "Data" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "Data"
    if ("Mu" in channelNew or "Ele" in channelNew) and not "QCDMu" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
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
    if "TTBar" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "TTBar"
    if "QCDMu" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "QCDMu"
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
    if "WJets" in channelNew:# == "DataMu" or channelNew == "DataMuQCD":
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"WJets")
        inputs = inputs +")"
        o.write(inputs)
    if "ZJets" in channelNew:# == "DataMu" or channelNew == "DataMuQCD":
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"ZJets")
        inputs = inputs +")"
        o.write(inputs)
    if "Mu" in channelNew or "Ele" in channelNew:# == "DataMu" or channelNew == "DataMuQCD":
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
#        inputs = inputs +"'"+dataPath+"Mu_v4p1Merged.root',"
#        inputs = inputs +"'"+dataPath+"Mu_v4p2Merged.root',"
#        inputs = inputs +"'"+dataPath+"Mu_v4p3Merged.root',"
#        inputs = inputs +"'"+dataPath+"Mu_v4Merged.root',"
#        inputs = inputs +"'"+dataPath+"Mu_v2Merged.root',"
        inputs = inputs +")"
        o.write(inputs)
    if "TTBar" in channelNew:# == "DataMu" or channelNew == "DataMuQCD":
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"TTBar")
        inputs = inputs +")"
        o.write(inputs)
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

f= open(fileName)

tmpName = "temp.py"
shutil.copy(fileName,tmpName)

for channel in channels:

    isMC = "False"
    if "Mu" in channel and not "QCD" in channel:
        channel_instruction = "mu"
    elif "Ele" in channel and not "QCD" in channel:
        channel_instruction = "ele"
    elif "Ele" in channel and not "QCD" in channel:
        channel_instruction = "ele"
    elif "Mu" in channel and ("QCD" in channel or "Had" in channel) and not "QCDMu" in channel:
        channel_instruction = "muqcd"
    elif "Ele" in channel and "QCD" in channel:
        channel_instruction = "eleqcd"
    else : 
        channel_instruction = "allmc"   
        isMC = "True"
    channelOld = startChannel
    
    cfg_file = changeChannel(tmpName,channelOld,channel,channel_instruction,isMC)
    command = 'nohup cmsRun ./' + channel+'_cfg.py > /tmp/oiorio/'+channel+'.log &'
    
    print command

    if mode == "cmsRun":
        os.system(command ) 
#    os.system("bg") 
#    os.system('rm '+channel+'_cfg.py' ) 

os.system('rm '+tmpName) 
#changeChannel(f,aChannel,startChannel)

#os.system(command)



