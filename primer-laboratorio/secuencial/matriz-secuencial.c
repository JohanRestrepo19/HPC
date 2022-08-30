#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

void multiplicarMatrices(int filas, int columnas, int **matrizA, int **matrizB,
                         int **resultado) {

  for (int fila = 0; fila < filas; fila++) {
    for (int columna = 0; columna < columnas; columna++) {
      resultado[fila][columna] = 0;
      for (int i = 0; i < columnas; i++) {
        resultado[fila][columna] += matrizA[fila][i] * matrizB[i][columna];
      }
    }
  }
}

int main(int argc, char *argv[]) {
  srand(time(0));
  double tiempoEjecucion = 0.0;
  clock_t inicio = clock();

  int filas, **matrizA, **matrizB, **resultado;
  filas = atoi(argv[1]);

  matrizA = mallocArreglo2dEnteros(filas, filas);
  matrizB = mallocArreglo2dEnteros(filas, filas);
  resultado = mallocArreglo2dEnteros(filas, filas);

  asignarValoresAleatoriosMatriz(filas, filas, matrizA);
  asignarValoresAleatoriosMatriz(filas, filas, matrizB);
  multiplicarMatrices(filas, filas, matrizA, matrizB, resultado);

  liberarArreglo2dEnteros(matrizA, filas, filas);
  liberarArreglo2dEnteros(matrizB, filas, filas);
  liberarArreglo2dEnteros(resultado, filas, filas);

  clock_t final = clock();

  tiempoEjecucion = (double)(final - inicio) / CLOCKS_PER_SEC;

  printf("Multiplicando matrices de %i x %i\n", filas, filas);
  printf("Tiempo de ejecución: %f\n", tiempoEjecucion);
  printf("\n");
}
