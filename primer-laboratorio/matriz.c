#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// NOTE: 835 es el maximo numero de filas que acepta la implementación
// secuencial de la multiplicacion de matrices a partir de 836 el programa
// presenta un segmentation fault (core dumped)

// TODO: Replantear el codigo para que funcione con vectores planos
// TODO: Implementar paralelismo del codigo hacinedo uso de los hilos con
// PThreads

void mostrarMatriz(int filas, int columnas, int matriz[filas][columnas]) {
  for (int fila = 0; fila < filas; fila++) {
    for (int columna = 0; columna < columnas; columna++) {
      printf("%d\t", matriz[fila][columna]);
    }
    printf("\n");
  }
  printf("\n");
}

void multiplicarMatrices(int filas, int columnas, int a[filas][columnas],
                         int b[filas][columnas], int result[filas][columnas]) {
  for (int fila = 0; fila < filas; fila++) {
    for (int columna = 0; columna < columnas; columna++) {
      result[fila][columna] = 0;
      for (int i = 0; i < columnas; i++) {
        result[fila][columna] += a[fila][i] * b[i][columna];
      }
    }
  }
}

void asignarValoresAleatoriosMatriz(int filas, int columnas,
                                    int matriz[filas][columnas]) {
  for (int fila = 0; fila < filas; fila++) {
    for (int columna = 0; columna < columnas; columna++) {
      matriz[fila][columna] = rand() % 50;
    }
  }
}

void asignarValoresMatriz(int filas, int columnas,
                          int matriz[filas][columnas]) {
  for (int fila = 0; fila < filas; fila++) {
    printf("Valores fila [%i]\n", (fila + 1));
    for (int columna = 0; columna < columnas; columna++) {
      scanf("%i", &matriz[fila][columna]);
    }
  }
}

int main() {
  int n, filas, columnas;

  printf("Ingrese la cantidad de filas: \n");
  scanf("%i", &n);
  filas = columnas = n;

  int matrizA[filas][columnas];
  int matrizB[filas][columnas];
  int resultado[filas][columnas];

  asignarValoresAleatoriosMatriz(filas, columnas, matrizA);
  asignarValoresAleatoriosMatriz(filas, columnas, matrizB);
  multiplicarMatrices(filas, columnas, matrizA, matrizB, resultado);

  mostrarMatriz(filas, columnas, matrizA);
  mostrarMatriz(filas, columnas, matrizB);
  mostrarMatriz(filas, columnas, resultado);
}
