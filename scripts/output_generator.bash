#!/bin/bash

if [ ! -d "out" ]; then
    mkdir out
    mkdir out/greedy
    mkdir out/random
fi

for file in ../in/*.txt
do
    filename=$(basename -- "${file%.*}")
    ../bin/main < "$file" > "../out/greedy/$filename.txt"
    ../bin/main < "$file" > "../out/random/$filename.txt"
done