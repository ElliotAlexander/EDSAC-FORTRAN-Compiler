#!/bin/bash

for f in Scripts/*.sh 
do 
    echo "Running $f"
    chmod +x $f
    bash "$f" -H | break 
done