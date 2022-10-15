#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

int **MATRIZ_A, **MATRIZ_B, **RESULTADO;
int CANT_HILOS;

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

void multiplicar_matrices(int filas, int columnas) {

#pragma omp parallel num_threads(CANT_HILOS)
  {
#pragma omp for
    for (int fila = 0; fila < filas; fila++) {
      for (int columna = 0; columna < columnas; columna++) {
        RESULTADO[fila][columna] = 0;
        for (int i = 0; i < columnas; i++) {
          RESULTADO[fila][columna] += MATRIZ_A[fila][i] * MATRIZ_B[i][columna];
        }
      }
    }
  }
}

int main(int argc, char *argv[]) {
  srand(time(0));

  struct timeval inicio, final;
  gettimeofday(&inicio, NULL);

  int filas;
  filas = atoi(argv[1]);
  CANT_HILOS = (argc > 2) ? atoi(argv[2]) : 8;

  MATRIZ_A = malloc_arreglo_2d_enteros(filas, filas);
  MATRIZ_B = malloc_arreglo_2d_enteros(filas, filas);
  RESULTADO = malloc_arreglo_2d_enteros(filas, filas);

  asignar_valores_aleatorios_matriz(filas, filas, MATRIZ_A);
  asignar_valores_aleatorios_matriz(filas, filas, MATRIZ_B);

  multiplicar_matrices(filas, filas);

  liberar_arreglo_2d_enteros(MATRIZ_A, filas, filas);
  liberar_arreglo_2d_enteros(MATRIZ_B, filas, filas);
  liberar_arreglo_2d_enteros(RESULTADO, filas, filas);

  gettimeofday(&final, NULL);
  double tiempo_ejecucion;
  tiempo_ejecucion =
      (final.tv_sec - inicio.tv_sec) + 1e-6 * (final.tv_usec - inicio.tv_usec);

  printf("Multiplicando matrices de %i x %i\n", filas, filas);
  printf("Tiempo de ejecución: %f\n", tiempo_ejecucion);
  printf("\n");
}
