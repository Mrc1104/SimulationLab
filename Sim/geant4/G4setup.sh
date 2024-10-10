#!/bin/sh
export G4WORKDIR=./geant4/ 
source ${HOME}/Programs/geant4/share/Geant4/geant4make/geant4make.sh
export G4UI_USE_TCSH=1
export G4ROOTLIBS=1
export G4VRMLFILE_VIEWER=freewrl
export PATH="$PATH":"$G4WORKDIR"/bin/
export LD_LIBRARY_PATH="$LD_LIBRARY_PATH":"$G4WORKDIR"/lib/
