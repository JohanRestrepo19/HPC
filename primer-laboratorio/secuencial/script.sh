#! /bin/bash
for j in {1..10} 
do
  echo Iteracion $j
  for i in 10 100 200 400 600 800 1000 2000
  do
    echo Ejecutando matrices de $i X $i
    ./matriz-secuencial.out $i >> times2.csv
  done
done


# for j in {1..10}
# do
# echo iteración $j
# for i in 10 100 200 400 600 800 1000 2000
# do
# echo Ejecutando con matrices de $i x $i
# ./matriz-secuencial.out $i >> times2.csv
# done
# done
