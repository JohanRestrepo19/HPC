#! /bin/bash
for cant_procesos in 2 4 8 16 32
do
  for tam_matriz in 1000 2000 3000 4000 5000 6000
  do
    echo "Ejecutanco script para matrices de $tam_matriz x $tam_matriz con $cant_procesos procesos "
    for iteracion in {1..10} 
    do
      echo "iteracion $iteracion"
      mpiexec -np $cant_procesos -hosts head,wn1,wn2,wn3 ./matriz-mpi.out $tam_matriz >> resultados-mpi-np-$cant_procesos.csv
    done
  done
done
