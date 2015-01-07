#Setting up the correct directory:
cd $CMSSW_BASE/src

#Loading all packages:
#Not needed: automatically included in the branch CMSSW_5_3_X

#Adding lhapdf libraries: 
cmsenv
scram setup lhapdffull
cmsenv

#Compilation:
scram b -j 9 > & step1.log &
