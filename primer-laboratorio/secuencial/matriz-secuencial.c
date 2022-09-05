#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int **malloc_arreglo_2d_enteros(int filas, int columnas) {
  int **doble_puntero_entero;
  doble_puntero_entero = (int **)malloc(filas * sizeof(int *));

  for (int fila = 0; fila < filas; fila++) {
    doble_puntero_entero[fila] = (int *)malloc(columnas * sizeof(int));
  }

  return doble_puntero_entero;
}

void liberar_arreglo_2d_enteros(int **doble_puntero_entero, int filas,
                                int columnas) {
  for (int fila = 0; fila < filas; fila++) {
    free(doble_puntero_entero[fila]);
  }
  free(doble_puntero_entero);
}

void asignar_valores_aleatorios_matriz(int filas, int columnas, int **matriz) {
  for (int fila = 0; fila < filas; fila++) {
    for (int columna = 0; columna < columnas; columna++) {
      matriz[fila][columna] = (rand() % 1000) + 1;
    }
  }
}

void mostrar_matriz(int filas, int columnas, int **matriz) {
  for (int fila = 0; fila < filas; fila++) {
    for (int columna = 0; columna < columnas; columna++) {
      printf("%d\t", matriz[fila][columna]);
    }
    printf("\n");
  }
  printf("\n");
}

void multiplicar_matrices(int filas, int columnas, int **matrizA, int **matrizB,
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
  double tiempo_ejecucion = 0.0;
  clock_t inicio = clock();

  int filas, **matrizA, **matrizB, **resultado;
  filas = atoi(argv[1]);

  matrizA = malloc_arreglo_2d_enteros(filas, filas);
  matrizB = malloc_arreglo_2d_enteros(filas, filas);
  resultado = malloc_arreglo_2d_enteros(filas, filas);

  asignar_valores_aleatorios_matriz(filas, filas, matrizA);
  asignar_valores_aleatorios_matriz(filas, filas, matrizB);
  multiplicar_matrices(filas, filas, matrizA, matrizB, resultado);

  liberar_arreglo_2d_enteros(matrizA, filas, filas);
  liberar_arreglo_2d_enteros(matrizB, filas, filas);
  liberar_arreglo_2d_enteros(resultado, filas, filas);

  clock_t final = clock();

  tiempo_ejecucion = (double)(final - inicio) / CLOCKS_PER_SEC;

  printf("Multiplicando matrices de %i x %i\n", filas, filas);
  printf("Tiempo de ejecución: %f\n", tiempo_ejecucion);
  printf("\n");
}
