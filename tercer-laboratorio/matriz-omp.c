#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

int **MATRIZ_A, **MATRIZ_B, **RESULTADO;

struct informacion_hilo {
  int filas, columnas, cant_hilos, idx_hilo;
};

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
      matriz[fila][columna] = (rand() % 4) + 1;
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

void multiplicar_matrices(void *threadarg) {
  struct informacion_hilo *info_hilo;
  int filas, columnas, cant_hilos, idx_hilo, fila, columna, i, desde, hasta;

  // Recuperación de la información que se manda encapsulada en el argumento
  info_hilo = (struct informacion_hilo *)threadarg;
  filas = info_hilo->filas;
  columnas = info_hilo->columnas;
  cant_hilos = info_hilo->cant_hilos;
  idx_hilo = info_hilo->idx_hilo;

  // calculo de filas a trabajar por el hilo
  desde = idx_hilo * filas / cant_hilos;
  hasta = (idx_hilo + 1) * filas / cant_hilos;

  // Implementación de la función de multiplicación
  for (fila = desde; fila < hasta; fila++) {
    for (columna = 0; columna < columnas; columna++) {
      RESULTADO[fila][columna] = 0;
      for (i = 0; i < columnas; i++) {
        RESULTADO[fila][columna] += MATRIZ_A[fila][i] * MATRIZ_B[i][columna];
      }
    }
  }
}

int main(int argc, char *argv[]) {
  // Semilla para la generacion de numeros aleatorios
  srand(time(0));

  struct timeval inicio, final;
  gettimeofday(&inicio, NULL);

  int filas, columnas, cant_hilos;
  filas = atoi(argv[1]);
  cant_hilos = atoi(argv[2]);
  columnas = filas;

  struct informacion_hilo info_hilos[cant_hilos];

  MATRIZ_A = malloc_arreglo_2d_enteros(filas, columnas);
  MATRIZ_B = malloc_arreglo_2d_enteros(filas, columnas);
  RESULTADO = malloc_arreglo_2d_enteros(filas, columnas);

  asignar_valores_aleatorios_matriz(filas, columnas, MATRIZ_A);
  asignar_valores_aleatorios_matriz(filas, columnas, MATRIZ_B);

#pragma omp parallel num_threads(cant_hilos)
  {
    int ID = omp_get_thread_num();
    info_hilos[ID].idx_hilo = ID;
    info_hilos[ID].cant_hilos = cant_hilos;
    info_hilos[ID].columnas = columnas;
    info_hilos[ID].filas = filas;

    multiplicar_matrices((void *)&info_hilos[ID]);
  }

  // Liberar la memoria
  liberar_arreglo_2d_enteros(MATRIZ_A, filas, columnas);
  liberar_arreglo_2d_enteros(MATRIZ_B, filas, columnas);
  liberar_arreglo_2d_enteros(RESULTADO, filas, columnas);

  // Tomar el tiempo de ejecución
  gettimeofday(&final, NULL);
  double tiempo_ejecucion;
  tiempo_ejecucion =
      (final.tv_sec - inicio.tv_sec) + 1e-6 * (final.tv_usec - inicio.tv_usec);

  printf("Multiplicando matrices de %i x %i\n", filas, columnas);
  printf("Tiempo de ejecución: %f\n", tiempo_ejecucion);
  printf("\n");
}
