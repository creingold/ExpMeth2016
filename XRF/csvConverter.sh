#! /bin/bash

args=("$@")

#COUNTER=0

for file in $*;
do
	sed -i 's/,/ /g' "$file"
	sed -i 's/;/ /g' "$file"
done

#while [ $COUNTER -lt $# ]; do
#	sed -i 's/,/ /g' ${args[COUNTER]}
#	sed -i 's/;/ /g' ${args[COUNTER]}
#	let COUNTER=COUNTER+1
#done
