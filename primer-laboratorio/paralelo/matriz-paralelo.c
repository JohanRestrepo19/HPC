#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// NOTE: 835 es el maximo numero de filas que acepta la implementación
// secuencial de la multiplicacion de matrices a partir de 836 el programa
// presenta un segmentation fault (core dumped)

// TODO: Replantear el codigo para que funcione con vectores planos
// TODO: Implementar paralelismo del codigo hacinedo uso de los hilos con
// PThreads

void mostrarMatriz(int n, int cantidadElementos, int matriz[n * n]) {
  for (int elemento = 0; elemento < cantidadElementos; elemento++) {
    if ((elemento % n) == 0)
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

void asignarValoresAleatoriosMatriz(int cantidadElementos,
                                    int matriz[cantidadElementos]) {
  for (int i = 0; i < cantidadElementos; i++) {
    matriz[i] = rand() % 20;
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

int main(int argc, char *argv[]) {

  srand(time(0));
  int n, cantidadElementos;
  n = atoi(argv[1]);

  printf("El numero de filas es: %i\n", n);

  int matrizA[cantidadElementos];
  int matrizB[cantidadElementos];

  asignarValoresAleatoriosMatriz(cantidadElementos, matrizA);
  mostrarMatriz(n, n * n, matrizA);

  asignarValoresAleatoriosMatriz(cantidadElementos, matrizB);
  mostrarMatriz(n, n * n, matrizB);
}
