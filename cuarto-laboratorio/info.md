# Planteamientos para MPI

## Ideas

- [ ] Utilizar las funciones MPI_Scatter() y MPI_Gather para repartir y reunir la información respectivamente
      Nota: Al estar trabajando con matrices (arreglo de arreglos) se tiene que hallar la forma de pasar ese tipo de
      variable a las funciones para su correcto funcionamiento. :book:

## Notas

- Es una buena practica no hacer nada antes del MPI_Init() y después del MPI_Finalize()
