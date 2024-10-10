#!/bin/sh
export G4WORKDIR=~/geant4/ 
cd /local/cern/geant4.10.01.p03/install/share/Geant4-10.1.3/geant4make
source geant4make.sh 
cd
export G4UI_USE_TCSH=1
export G4ROOTLIBS=1
export G4VRMLFILE_VIEWER=freewrl
export PATH="$PATH":"$G4WORKDIR"/bin/
export LD_LIBRARY_PATH="$LD_LIBRARY_PATH":"$G4WORKDIR"/lib/

