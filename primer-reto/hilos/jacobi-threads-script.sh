#!/bin/bash
for i in 5000 25000 50000 100000 150000 200000 250000 300000
do 
  echo "Running script for array of length $i"
  for j in {1..10}
  do 
    echo "iteration #$j"
    ./jacobi-threads.out $i $i $1 >> resultado-hilos-$1.csv
  done
done
