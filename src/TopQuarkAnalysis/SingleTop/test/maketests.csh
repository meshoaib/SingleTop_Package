setenv isData 'isData=True'
setenv isMC 'isData=False'

setenv isGsf 'doGsfElectrons=True'
setenv isPF 'doGsfElectrons=False'

setenv hasTaus 'EnablePFTaus=True'
setenv notHasTaus 'EnablePFTaus=False'

setenv isHermetic 'hermeticTopProjection=True'
setenv notIsHermetic 'hermeticTopProjection=False'

setenv hasRunMETUnc 'doRunMETUncertainties=True'
setenv hasMETPat 'doRunMETUncertainties=False'

setenv chanName 'ChannelName = "TChannel"'


#echo $OLD
#echo $NEW
#sed "s|$OLD|$NEW|g" EgammaAnalysis/ElectronTools/python/electronIdMVAProducer_cfi.py > tmp.log

foreach i ($isData $isMC)
  echo $i
  setenv it `echo $i | cut -c 8-19`
  foreach j ($isGsf $isPF)
    echo $j
    setenv jt `echo $j | cut -c 16-30`
#    rm SingleTopSkim_TChannel_Data$it\_isGsf_$jt\_cfg.py 
#    sed "s|$isMC|$j|g" SingleTopSkim_TChannel_cfg.py | sed "s|$isGsf$j|g"  SingleTopSkim_TChannel_Data$it\_isGsf_$jt\_hasTaus_$kt\_isHermetic_$l\_hasrunMETUnc_$mt\_cfg.py
    foreach k ($hasTaus $notHasTaus )
      echo $k
      setenv kt `echo $k | cut -c 14-40`
      foreach l ($isHermetic $notIsHermetic)
	echo $l
	setenv lt `echo $l | cut -c 23-40`
	foreach m ($hasRunMETUnc $hasMETPat)
	  echo $m
	  setenv mt `echo $m | cut -c 23-40`
	  rm SingleTopSkim_TChannel_Data_$it\_isGsf_$jt\_hasPFTaus_$kt\_isHermetic_$lt\_hasRunMETUnc_$mt\_cfg.py  
	  setenv chanNameNew 'ChannelName = "TChannel_'SingleTopSkim_TChannel_Data_$it\_isGsf_$jt\_hasPFTaus_$kt\_isHermetic_$lt\_hasRunMETUnc_$mt'"'
	  echo $chanNameNew
          sed "s|$isMC|$i|g" SingleTopSkim_TChannel_cfg.py | sed "s|$isPF|$j|g" | sed "s|$notHasTaus|$k|g" | sed "s|$isHermetic|$l|g"  | sed "s|$hasRunMETUnc|$m|g" | sed "s|$chanName|$chanNameNew|g" > SingleTopSkim_TChannel_Data_$it\_isGsf_$jt\_hasPFTaus_$kt\_isHermetic_$lt\_hasRunMETUnc_$mt\_cfg.py
	  rm /tmp/oiorio/SingleTopSkim_TChannel_Data_$it\_isGsf_$jt\_hasPFTaus_$kt\_isHermetic_$lt\_hasRunMETUnc_$mt\_cfg.log
	  nohup cmsRun SingleTopSkim_TChannel_Data_$it\_isGsf_$jt\_hasPFTaus_$kt\_isHermetic_$lt\_hasRunMETUnc_$mt\_cfg.py > & /tmp/oiorio/SingleTopSkim_TChannel_Data_$it\_isGsf_$jt\_hasPFTaus_$kt\_isHermetic_$lt\_hasRunMETUnc_$mt\_cfg.log &
#          cp singleTopEdmNtuple_TChannel.root /tmp/oiorio/singleTopEdmNtuple_Data_$it\_isGsf_$jt\_hasPFTaus_$kt\_isHermetic_$lt\_hasRunMETUnc_$mt\_TChannel.root
	end
      end
    end
  end
end
