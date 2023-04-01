#!/bin/bash

for i in {1..250}; do
    num_movies=$(( $i * 4000 ))
    num_categories=100
    filename="input_$i.txt"
    ../bin/generator $num_movies $num_categories $filename 0
done

for i in {251..500}; do
    num_movies=10000
    num_categories=$(( ($i - 250) * 4 ))
    filename="input_$i.txt"
    ../bin/generator $num_movies $num_categories $filename 0
done