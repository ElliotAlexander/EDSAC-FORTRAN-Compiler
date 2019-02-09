#!/bin/bash

for f in scripts/*.sh 
do 
    echo "Running $f"
    chmod +x $f
    bash "$f" -H | break 
done