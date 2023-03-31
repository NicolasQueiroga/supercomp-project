#!/bin/bash

if [ ! -d "in" ]; then
    mkdir in
fi

for i in {1..500}; do
    num_movies=$(( $RANDOM % 9999991 + 10 ))
    num_categories=$(( $RANDOM % 46 + 5 ))
    filename="input_$i.txt"
    ../bin $num_movies $num_categories $filename 0
done