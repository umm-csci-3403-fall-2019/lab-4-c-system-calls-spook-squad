#!/usr/bin/env bash

numFiles=0
numDir=0

for _ in $(find "$1" -type d)
do
  numDir=$((numDir+1))	
done
for _ in $(find "$1" -type f)
do
  numFiles=$((numFiles+1))
done

echo "There were $numDir directories."
echo "There were $numFiles regular files."

