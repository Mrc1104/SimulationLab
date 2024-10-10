#!/bin/sh
export G4WORKDIR=~/geant4/ 
cd /local/cern/software/geant4/geant4.10.07.p02-install/share/Geant4-10.7.2/geant4make
source geant4make.sh 
cd
export G4UI_USE_TCSH=1
export G4ROOTLIBS=1
export G4VRMLFILE_VIEWER=freewrl
export PATH="$PATH":"$G4WORKDIR"/bin/
export LD_LIBRARY_PATH="$LD_LIBRARY_PATH":"$G4WORKDIR"/lib/

