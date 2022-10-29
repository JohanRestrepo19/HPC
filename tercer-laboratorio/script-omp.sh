#! /bin/bash
for cantidad_hilos in 4 8
do
  echo "Corriendo para $cantidad_hilos hilos"
  for i in 100 500 1000 2000 3000 4000 5000 6000
  do
    echo "Ejecutando script para matrices de $i x $i"
    for j in {1..10}
    do
      echo "iteracion $j"
      ./matriz-omp.out $i $cantidad_hilos >> resultados-hilos-$cantidad_hilos.csv
    done
  done
done
