#!/bin/bash

# mkdir -p ../out/greedy
# mkdir -p ../out/random

# for i in {1..500}; do
#     filename="input_$i.txt"
#     touch "../out/greedy/$filename"
#     touch "../out/random/$filename"
# done

for file in ../in/*.txt
do
    filename=$(basename -- "${file%.*}")
    ../bin/main 0 < "$file" > "../out/greedy/$filename.txt"
    ../bin/main 1 < "$file" > "../out/random/$filename.txt"
done