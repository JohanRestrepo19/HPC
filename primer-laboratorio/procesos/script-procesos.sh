#! /bin/bash
for i in 5000 25000 50000 100000 150000 200000 250000 300000
do
  echo "Ejecutando script para matrices de $i x $i"
  for j in {1..10}
  do
    echo "iteracion $j"
    ./matriz-procesos.out $i $1 >> resultados-procesos-$1.csv
  done
done
