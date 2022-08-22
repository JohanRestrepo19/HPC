#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// NOTE: 835 es el maximo numero de filas que acepta la implementación
// secuencial de la multiplicacion de matrices a partir de 836 el programa
// presenta un segmentation fault (core dumped)

// TODO: Replantear el codigo para que funcione con vectores planos

int **mallocArreglo2dEnteros(int filas, int columnas) {
  int **punteroPunteroEntero;
  punteroPunteroEntero = (int **)malloc(filas * sizeof(int *));

  for (int fila = 0; fila < filas; fila++) {
    punteroPunteroEntero[fila] = (int *)malloc(columnas * sizeof(int));
  }

  return punteroPunteroEntero;
}

void liberarArreglo2dEnteros(int **ipp, int filas, int columnas) {
  for (int fila = 0; fila < filas; fila++) {
    free(ipp[fila]);
  }
  free(ipp);
}

void asignarValoresAleatoriosMatriz(int filas, int columnas, int **matriz) {
  for (int fila = 0; fila < filas; fila++) {
    for (int columna = 0; columna < columnas; columna++) {
      matriz[fila][columna] = rand() % 20;
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

  int filas, **matrizA, **matrizB, **resultado;
  filas = atoi(argv[1]);

  matrizA = mallocArreglo2dEnteros(filas, filas);
  matrizB = mallocArreglo2dEnteros(filas, filas);
  resultado = mallocArreglo2dEnteros(filas, filas);

  asignarValoresAleatoriosMatriz(filas, filas, matrizA);
  asignarValoresAleatoriosMatriz(filas, filas, matrizB);
  multiplicarMatrices(filas, filas, matrizA, matrizB, resultado);

  printf("matriz A\n");
  mostrarMatriz(filas, filas, matrizA);
  printf("matriz B\n");
  mostrarMatriz(filas, filas, matrizB);
  printf("matriz Resultado\n");
  mostrarMatriz(filas, filas, resultado);

  liberarArreglo2dEnteros(matrizA, filas, filas);
  liberarArreglo2dEnteros(matrizB, filas, filas);
  liberarArreglo2dEnteros(resultado, filas, filas);
}
