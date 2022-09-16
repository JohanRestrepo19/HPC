#!/bin/bash
for i in 1000 5000 10000 20000 30000 40000 50000 60000
do 
  echo "Running script for array of length $i"
  for j in {1..10}
  do 
    echo "iteration #$j"
    ./jacobi-threads.out $i $i $1 >> resultado-hilos-$1.csv
  done
done
