#!/bin/bash
for number_threads in 4 8
do
  echo "Running for $number_threads threads"
  for i in 5000 25000 50000 100000 150000 200000 250000 300000
  do 
    echo "Running script for array of length $i"
    for j in {1..10}
    do 
      echo "iteration #$j"
      ./jacobi-omp.out $i $i $number_threads >> resultado-hilos-$number_threads.csv
    done
  done
done
