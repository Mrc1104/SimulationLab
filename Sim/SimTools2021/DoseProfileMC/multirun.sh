#!/bin/bash

handle_error() {
    echo "An error occurred on line $1"
    exit 1
}

trap 'handle_error $LINENO' ERR

# Number of iterations
declare -i N=20

tnrfile=vals.txt
move_path=${HOME}/share/SimulationLab/Sim/TNR_values

# Photon Energies of Interest
energies=(1 10 20 30 40 50 60 70 80 87 88 89 90 91 92 93 100 110 120); btype=gamma
#energies=(100 110 120 130 132 133 134 135 136 137 138 140 150 160); btype=proton
#energies=(3000 3010 3020 3030 3040 3050 3060 3067 3068 3069 3070 3071 3072 3073 3080 3090 4000); btype=ion


# Construct where to move it at the end of the loop
full_move_path=${move_path}/${btype}
# Loop Through Energies
for i in "${energies[@]}"
do
	for it in $(seq $N)
	do
		./runsim.sh ${btype} $i
	done
	# Construct end file
	file=${btype}_${i}.txt
	if [ ! -f ${tnrfile} ]
	then
  		echo "#############################################################"
  		echo "FATAL: File ${tnrfile} containing energies and TNR for ${btype} does not exist..."
  		echo "Cannot move file!"
  		echo "------------------------------------------------------------"
  		echo "Error occured for '${btype} $i'"
  		echo "#############################################################"
  		exit -1
	else
		echo "Moving ${tnrfile} to: $full_move_path/$file"
		mv ${tnrfile} ${full_move_path}/${file}
	fi
done
