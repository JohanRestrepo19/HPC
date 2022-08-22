#! /bin/bash
for i in 10 100 200 400 600 800 1000 2000
do
  echo Ejecutando script para matrices de $i x $i
  for j in {1..10}
  do
    echo iteracion $j
    ./matriz-secuencial.out $i >> resultados-secuencial.csv
  done
done
