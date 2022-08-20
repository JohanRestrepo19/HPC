#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// NOTE: 835 es el maximo numero de filas que acepta la implementación
// secuencial de la multiplicacion de matrices a partir de 836 el programa
// presenta un segmentation fault (core dumped)

// TODO: Replantear el codigo para que funcione con vectores planos
// TODO: Implementar paralelismo del codigo hacinedo uso de los hilos con
// PThreads

void asignarValoresAleatoriosMatriz(int filas, int *matriz) {
  int cantidadElementos = filas * filas;
  for (int i = 0; i < cantidadElementos; i++) {
    matriz[i] = rand() % 20;
  }
}

void mostrarMatriz(int filas, int *matriz) {
  int cantidadElementos = filas * filas;
  for (int elemento = 0; elemento < cantidadElementos; elemento++) {
    if ((elemento % filas) == 0)
      printf("\n");

    printf("%d\t", matriz[elemento]);
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

int main(int argc, char *argv[]) {
  srand(time(0));

  int filas, cantidadElementos, *matrizA, *matrizB;
  filas = atoi(argv[1]);
  cantidadElementos = filas * filas;

  printf("El numero de filas es: %i\n", filas);

  matrizA = (int *)malloc(cantidadElementos * sizeof(int));
  matrizB = (int *)malloc(cantidadElementos * sizeof(int));

  asignarValoresAleatoriosMatriz(filas, matrizA);
  asignarValoresAleatoriosMatriz(filas, matrizB);

  mostrarMatriz(filas, matrizA);
  mostrarMatriz(filas, matrizB);
}
