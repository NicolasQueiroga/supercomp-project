#!/bin/bash

if [ ! -d "../out" ]; then
    mkdir ../out
    mkdir ../out/greedy ../out/random
    mkdir ../out/greedy/cat_fixed ../out/greedy/mov_fixed
    mkdir ../out/random/cat_fixed ../out/random/mov_fixed
fi

for i in {1..250}; do
    filename="input_$i.txt"
    ../bin/main 0 < "../in/$filename" > "../out/greedy/cat_fixed/$filename"
    ../bin/main 1 < "../in/$filename" > "../out/random/cat_fixed/$filename"
done

for i in {251..501}; do
    filename="input_$i.txt"
    ../bin/main 0 < "../in/$filename" > "../out/greedy/mov_fixed/$filename"
    ../bin/main 1 < "../in/$filename" > "../out/random/mov_fixed/$filename"
done