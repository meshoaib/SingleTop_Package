#!/usr/bin/env cmsRun
import FWCore.ParameterSet.Config as cms
import os,sys,re,shutil


#Castor directory with all sub-directories:
#inputDir = "/castor/cern.ch/user/o/oiorio/SingleTop/2011/MC2011/Summer11/"
inputDir = "/castor/cern.ch/user/o/oiorio/SingleTop/2011/MC2011/Summer11/Sep04"
inputDir = "/castor/cern.ch/user/o/oiorio/SingleTop/2011/MC2011/Summer11/Aug30"
inputDir = "/castor/cern.ch/user/o/oiorio/SingleTop/2012/MC2011/Fall11/Jan29"
inputDir = "/castor/cern.ch/user/o/oiorio/SingleTop/2012/MC2011/Fall11/Jan30"
#inputDir = "/castor/cern.ch/user/o/oiorio/SingleTop/2012/MC2011/Fall11/Feb04"
#inputDir = "/castor/cern.ch/user/m/mmerola/SingleTop_Moriond2012/Fall11/"
#inputDir = "/castor/cern.ch/user/m/mmerola/SingleTop_Moriond2012/Summer11/"

#Original config file
#fName = "copyTemplate.py"
#fName = "copyFlavorSeparationTemplateForSub.py"
#fName = "copyFlavorSeparationTemplateSummerForSub.py"
fName = "copyFlavorSeparationTemplateSummer.py"
#fName = "copyFlavorSeparationTemplate.py"
fNameBsub = "mergeBsub.py"
f = open(fName)



#Channels to include
channels = [
#"TbarChannel",
#"TbarChannel_Q2Down",
#"TbarChannel_Q2Up",
#    "QCDMu_part_1",
#    "QCDMu_part_2",
#    "QCDMu_part_3",
#    "QCDMu_part_4",
#    "QCDMu_part_5",
#    "QCDMu_part_6",
#    "QCDMu_part_7",
#"ZJets_part_1",
#"ZJets_part_2",
#"ZJets_part_3",
#"ZJets_part_4",
#"ZJets_part_5",
#"ZJets_part_6",
#"ZJets_part_7",
#"TTbar",
#"SChannel",
#"SbarChannel",
#"TWChannel",
#"TbarWChannel",
#"WW",
#"WZ",
#"ZZ",
#"QCD_Pt_20to30_EMEnriched",
#"QCD_Pt_30to80_EMEnriched",
#"QCD_Pt_80to170_EMEnriched",
#"QCD_Pt_20to30_BCtoE",
#"QCD_Pt_30to80_BCtoE",
#"QCD_Pt_80to170_BCtoE",
#"QCD_HT_200_GJets",
#"QCD_HT_100_200_GJets",
#"QCD_HT_40_100_GJets",
#"ZJets",
#"Mu_v4_part_1",
#"Mu_v4_part_2",
#"Mu_v4_part_3",
#"Mu_v4_part_4",
#"Mu_v4_part_5",
#"EleHad_v4_part_1",
#"EleHad_v4_part_2",
#"EleHad_v4_part_3",
#"EleHad_v4_part_4",
#"EleHad_v4_part_5",
#"Ele_May10",
#"EleHad_Aug05",
#"Mu_May10",
#"Mu_Aug05",
#   "TChannel",
#    "TbarChannel",
#   "TbarWChannel",
#    "ZJets_part_1",
#    "ZJets_part_2",
#    "ZJets_part_3",
#    "SbarChannel",
#    "SChannel",
#    "VV",
#    "TbarChannel",
#"HT_200",
#"HT_100To200",
#"HT_40To100",
#    '30to80_BCtoE',
#"QCD_Pt_20to30_EMEnriched",
#"QCD_Pt_30to80_EMEnriched",
#"QCD_Pt_80to170_EMEnriched",
#"WJets_Q2Down"
#"QCD_Pt_20to30_BCtoE",
#"QCD_Pt_30to80_BCtoE",
#"QCD_Pt_80to170_BCtoE",
#     "ZJets",
#    "QCDMu_part_1",
#    "QCDMu_part_2",
#    "QCDMu_part_3",
#    "QCDMu_part_4",
#    "QCDMu_part_5",
#    "QCDMu_part_6",
#    "QCDMu_part_7",
#     "Dataele",
#     "QCDMu",
#     "QCDEle",
     "WJets_part_1",
     "WJets_part_2",
     "WJets_part_3",
     "WJets_part_4",
     "WJets_part_5",
     "WJets_part_6",
     "WJets_part_7",
     "WJets_part_8",
     "WJets_part_9",
     "WJets_part_10",
     "WJets_part_11",
     "WJets_part_12",
     "WJets_part_13",
     "WJets_part_14",
     "WJets_part_15",
     "WJets_part_16",
     "WJets_part_17",
     "WJets_part_18",
     "WJets_part_19",
     "WJets_part_20",
     "WJets_part_21",
     "WJets_part_22",
#    "Mu",
#"Mu_v1",
# "Mu_v4_part_1",
# "Mu_v4_part_2",
# "Mu_v4_part_3",
#"EleHad_v4_part_1",
#"EleHad_v4_part_2",
#"EleHad_v4_part_3",
#"Mu_Aug05",
#"Mu_May10",
#"EleHad_Aug05",
#"EleHad_May10",
#"Mu_Aug05",
#"Ele_v1",
#"Ele_v2",
#"EleHad_Aug05",
#"EleHad_v4",
#"Ele_May10",
#    "Vqq",
#    "Wc",
    ]


Prefix = "edmntuple_"
PrefixHisto = "pileupdistr_"
#Prefix = ""

Switch = "None"

#Choose if you want to do bsub, run or just prepare the configuration files
#if none of those is chosen, it just produces the cfg files to run and bsub
mode = ""
mode = "cmsRun"
#mode = "bsub"
#mode = "hadd"

#Function to replace a sequence of characters channelOld to channelNew in a file 
def changeChannel(fileName,channelOld,channelNew,switch,suffix): 
    print " Channel test " + channelNew
    file = open (fileName)
    lines = file.readlines()
    o = open(channelNew+suffix,"w") 
    for line in lines:
        if '"switch_instruction"' in line:
            print line
            line = line.replace('"switch_instruction"','"'+switch+'"')
            print line

        words = line.split()
        for word in words:
            if channelOld in word: 
                #                print " line old " + line
                line = line.replace(word,word.replace(channelOld,channelNew))
                #                print " line new " + line
        o.write(line)
    o.close()    
    return o

#Function to append new input
def appendInput(fileName,directory,channel,prefix,parts): 
    import os,sys,re,shutil
    o = open (fileName,"a")

    o.write("process.source.fileNames = cms.untracked.vstring()\n")
    o.write("process.source.fileNames.extend([")

    number = 1
    if parts != -1 and "_part_" in channel:
        channel_number = channel.split("_part_")
        print "channel before: " + channel
        channel = channel_number[0]
        if parts > 1:
            number = int(channel_number[1])
        print "split channel + number "+ channel + " , " + str(number)  
    print " outsude channel " + channel     
    inputRedirect = "rfdir "+directory +"/"+channel+"/ | grep " + prefix + " | cut -c68-200 > "+ channel+"_input.py"
    if channel == "Data" or "QCDEleNew" in directory or "V2" in directory:
        inputRedirect = "rfdir "+directory +"| grep " + prefix + " | cut  -c68-200 > "+ channel+"_input.py"
    if "HT_" in channel or "QCD_Pt" in channel:
        inputRedirect = "rfdir "+directory +"/QCDEleNew | grep " + prefix + " | cut  -c68-200 > "+ channel+"_input.py"
    os.system(inputRedirect)
    
    tmp = open(channel+"_input.py","rw")
    raws = tmp.readlines()
    nraws = len(raws)/(parts) 
    nr = 0
    tmp2 = open(channel+"_input_part"+str(number),"w") 
    for raw in raws: 
        nr= nr+1
        #        print "raw " + raw
        #isInRange = nr > nraws * (number -1)# and  nr <= nraws *number
        #   isInRange = ( (nr > nraws * (number -1))
        #print " nr "+str(nr) +" nraws "+str(nraws) +" nraws * number "+ str(nraws*number) +" nraws * (number -1) "+ str(nraws*(number - 1)) + " passes ? " + isInRange
        if number == parts:
            if nr > nraws * (number -1):                      
                tmp2.write(raw)
        elif  nr > nraws * (number -1) and  nr <= nraws *number:
            tmp2.write(raw)
    if parts!=-1:
        tmp.close()
        os.system("rm "+channel+ "_input.py")
        # tmp2.close()
        # shutil.copy("tmp2.py",channel+"_input.py")
        print "ok!" + str(number)


#            print " raw: " + str(nr) + " passes the cut! " 
    tmp2.close()
    tmp2=open(channel+"_input_part"+str(number),"r")
    #Tmp (em) = open(channel+"_input.py","rw")
    print "opening file: "+channel+"_input_part"+str(number)
    lines = tmp2.readlines()
    lin =0;
    for line in lines:
        lin = lin+1
        lintemp = line.replace(os.linesep,"")
        print " line: " +str(lin)+" "+ lintemp
        words = line.split()
        hasWord = "true" 
        for word in words:
            beginName = prefix+channel
            #print "beginName is " + beginName +" word is "+ word
            if beginName in word:
                #print " word ok , is it true? " + hasWord 
                if channel != "Data" and not "QCDEleNew" in directory and not "V2" in directory:
                    if "HT_" in channel or "QCD_Pt" in channel:
                        line = "'"+line.replace(word,word.replace(beginName,"rfio:"+directory+"/QCDEleNew/"+beginName))
                    else:    
                        line = "'"+line.replace(word,word.replace(beginName,"rfio:"+directory+"/"+channel+"/"+beginName))
                else:
                    line = "'"+line.replace(word,word.replace(beginName,"rfio:"+directory+"/"+beginName))
                if ".root" in word:
                    line = line.replace(word,word.replace(".root",".root',"))
#                if "\n" in word:
#                    line = line.replace(word,word.replace("\n",""))
#                print "line after " + line
            else:
                #print ("error! please, check that either the path : \n" +directory +"\n is correct or that the file name contains files starting with '"+beginName+"' \n (try rfdir "+directory +" | grep "+beginName+") \n")
                hasWord = "false" 
        if hasWord == "true":
            o.write(line)
    o.write("])")       
    o.close()    
    #    os.system("rm "+channel+"_input.py")
    return o


def haddInput(directory,channel,prefix): 
    o = open (channel+"_hadd.py","w")

    if "_part_" in channel:
        channel = (channel.split("_part_"))[0] 
    inputRedirect = "rfdir "+directory +"/"+channel+"/ | cut -c68-200 > "+ channel+"_input.py"
    if channel == "Data":
        inputRedirect = "rfdir "+directory +"| cut -c68-200 > "+ channel+"_input.py"
    if "HT_" in channel or "QCD_Pt" in channel:
        inputRedirect = "rfdir "+directory +"/QCDEleNew | cut -c68-200 > "+ channel+"_input.py"
    os.system(inputRedirect)
    tmp = open(channel+"_input.py")
    lines = tmp.readlines()
    command = ("hadd -f pileupdistr_"+channel+".root ")
    for line in lines:
        words = line.split()
        hasWord = "true" 
        for word in words:
            beginName = prefix+channel
            if beginName in word:
            #print " word ok , is it true? " + hasWord 
                if channel != "Data" and not "QCDEleNew" in directory :
                    if "HT_" in channel or "QCD_Pt" in channel:
                        line = line.replace(word,word.replace(beginName,"rfio:"+directory+"/QCDEleNew/"+beginName))
                    else:    
                        line = line.replace(word,word.replace(beginName,"rfio:"+directory+"/"+channel+"/"+beginName))
                else:
                    line = line.replace(word,word.replace(beginName,"rfio:"+directory+"/"+beginName))
                if ".root" in word:
                    line = line.replace(word,word.replace(".root",".root "))
                if "\n" in word:
                    line =(line.replace(word,word.replace("\n"," ")))
#                print "line after " + line
            else:
                #print ("error! please, check that either the path : \n" +directory +"\n is correct or that the file name contains files starting with '"+beginName+"' \n (try rfdir "+directory +" | grep "+beginName+") \n")
                hasWord = "false" 
        if hasWord == "true":
            command +=(line)
    s = command.replace(os.linesep," ")
    #sys.stdout.write(command)
    o.write(s)
    o.close()    
    #    os.system("rm "+channel+"_input.py")
    return o




#Implementation of the loop part:

#Channel in the original file
startChannel = "TChannel"#channels[0]

tmpName = "temp.py"
tmpNameBsub = "tempBsub.py"

shutil.copy(fName,tmpName)
shutil.copy(fNameBsub,tmpNameBsub)

for channel in channels:

    #tmp_file = open(tmpName)

    print "channel is:\n"+ channel
        
    if channel == "WJets" or channel == "ZJets":
        Switch = "wlight"
    elif channel == "Vqq":
        Switch = "vqq"
    elif channel == "Wc":
        Switch = "wc"
    else:
        Switch = "None"
    Switch = "None"
    channelOld = startChannel

    SuffixCfg = "_cfg.py"
    SuffixBsub = "_sub.py"
    
    cfg_file = changeChannel(tmpName,channelOld,channel,Switch,SuffixCfg)
    
    cfg_file = appendInput("./"+channel+"_cfg.py",inputDir,channel,Prefix,1)

    bsub_file = changeChannel(tmpNameBsub,channelOld,channel,Switch,SuffixBsub)

    hadd_file = haddInput(inputDir,channel,PrefixHisto)
    command = 'nohup cmsRun ./' + channel+SuffixCfg+' > /tmp/oiorio/'+channel+'_merge.log &'
    command_bsub = 'bsub -q1nd ' + channel + SuffixBsub
    command_hadd = 'nohup ./'+channel+'_hadd.py > /tmp/oiorio/'+channel+'_hadd.log &' 
    
    
    print command +"\n"
    print command_bsub

    os.system("chmod 777 "+ channel + SuffixBsub)
    os.system("chmod 777 "+ channel + "_hadd.py")


    if mode == "bsub":
        os.system(command_bsub ) 
    if mode == "cmsRun":
        os.system(command )
    if mode == "hadd":
        os.system(command_hadd )

    
    
    #os.system("rm "+channel+"_cfg.py") 
    
#    os.system('rm '+tmpName) 
#    os.system('rm '+tmpNameBsub) 
#changeChannel(f,aChannel,startChannel)

#os.system(command)



