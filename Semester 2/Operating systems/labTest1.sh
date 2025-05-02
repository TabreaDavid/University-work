#!/bin/bash

#This simple bash script excepts text files as args and prints for each file 
#the number of lines, the number of letters on each line and
#if each line has an even or uneven number of letters

if test $# -eq 0; then
    echo Not enough arguments!
    exit 0
fi

while test $# -gt 0; do
    fileName=$1
    lineCount=$(wc -l < "$fileName")

    ((lineCount++))
    echo "$fileName has $lineCount lines"

    i=1
    while IFS= read -r line || [ -n "$line" ]; do
        letterCount=$(echo "$line" | tr -dc '[A-Z][a-z]' |  wc -m)
    
        if ((letterCount % 2 == 0)); then
            echo "Line $i: $letterCount letters, it's an even letter line"

        else 
            echo "Line $i: $letterCount letters, it's an uneven letter line"

        fi
        ((i++))
    done < "$fileName"

    shift
done