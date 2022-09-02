#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int **mallocArreglo2dEnteros(int filas, int columnas) {
  int **doblePunteroEntero;
  doblePunteroEntero = (int **)malloc(filas * sizeof(int *));

  for (int fila = 0; fila < filas; fila++) {
    doblePunteroEntero[fila] = (int *)malloc(columnas * sizeof(int));
  }

  return doblePunteroEntero;
}

void liberarArreglo2dEnteros(int **doblePunteroEntero, int filas,
                             int columnas) {
  for (int fila = 0; fila < filas; fila++) {
    free(doblePunteroEntero[fila]);
  }
  free(doblePunteroEntero);
}

void asignarValoresAleatoriosMatriz(int filas, int columnas, int **matriz) {
  for (int fila = 0; fila < filas; fila++) {
    for (int columna = 0; columna < columnas; columna++) {
      matriz[fila][columna] = (rand() % 1000) + 1;
    }
  }
}

void mostrarMatriz(int filas, int columnas, int **matriz) {
  for (int fila = 0; fila < filas; fila++) {
    for (int columna = 0; columna < columnas; columna++) {
      printf("%d\t", matriz[fila][columna]);
    }
    printf("\n");
  }
  printf("\n");
}

void multiplicarMatrices() {}

int main(int argc, char *argv[]) {
  // Semilla para la generacion de numeros aleatorios
  srand(time(0));

  struct timeval inicio, final;
  gettimeofday(&inicio, NULL);

  int filas, columnas, cantidadProcesos, indexProceso;

  // TODO: Definir si cambiar la estrategia de la estructura para el paso de
  // parametros al proceso.

  // Creacion de los hilos
  for (int i = 1; i < 5; i++) {
    if (fork() == 0) {
      exit(0);
    }
  }

  // Este wait hace que el proceso padre espere a que todos los procesos hijos
  // terminen antes de que se cierre el programa.
  wait(NULL);

  return 0;
}
