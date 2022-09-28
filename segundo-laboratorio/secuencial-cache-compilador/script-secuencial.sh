#! /bin/bash
for i in 100 500 1000 2000 3000 4000 5000 6000
do
  echo Ejecutando script para matrices de $i x $i
  for j in {1..10}
  do
    echo iteracion $j
    ./matriz-secuencial.out $i >> resultados-secuencial.csv
  done
done
