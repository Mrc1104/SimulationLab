#!/bin/bash

files=''
btype=gamma; 
#btype=proton
#btype=ion
save=\"../TNR_values/${btype}/stats.txt\"
for i in ../TNR_values/${btype}/${btype}*
do
	files=$files$i'\n'
done
files=\"$files\"

root "../Rootscripts/tnr_avg.C($files, $save)"
