#include <mpi/mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

int **MATRIZ_A, **MATRIZ_B, **RESULTADO;

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
      matriz[fila][columna] = (rand() % 3) + 1;
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

void multiplicar_matrices(int filas, int columnas, int cant_procesos,
                          int idx_proceso) {
  int fila, columna, i, desde, hasta;

  // calculo de filas a trabajar por el proceso
  desde = idx_proceso * filas / cant_procesos;
  hasta = (idx_proceso + 1) * filas / cant_procesos;

  // Implementación de la funcion para multiplicar matrices
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

  int filas, columnas, idx_proceso, cant_procesos;

  // Obtencion de los parametros que se pasan en el llamado al ejecutable
  filas = columnas =
      atoi(argv[1]); // Debido a que se está trabajando con matrices cuadradas

  MATRIZ_A = malloc_arreglo_2d_enteros(filas, columnas);
  MATRIZ_B = malloc_arreglo_2d_enteros(filas, columnas);
  RESULTADO = malloc_arreglo_2d_enteros(filas, columnas);

  asignar_valores_aleatorios_matriz(filas, columnas, MATRIZ_A);
  asignar_valores_aleatorios_matriz(filas, columnas, MATRIZ_B);

  // NOTE: Solo medir el tiempo en la región de procesos
  MPI_Init(&argc, &argv);

  MPI_Comm_size(MPI_COMM_WORLD, &cant_procesos);
  MPI_Comm_rank(MPI_COMM_WORLD, &idx_proceso);
  multiplicar_matrices(filas, columnas, cant_procesos, idx_proceso);
  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();

  mostrar_matriz(filas, columnas, MATRIZ_A);
  mostrar_matriz(filas, columnas, MATRIZ_B);
  mostrar_matriz(filas, columnas, RESULTADO);

  // Tomar el tiempo de ejecución
  gettimeofday(&final, NULL);
  double tiempo_ejecucion;
  tiempo_ejecucion =
      (final.tv_sec - inicio.tv_sec) + 1e-6 * (final.tv_usec - inicio.tv_usec);

  printf("Multiplicando matrices de %i x %i\n", filas, columnas);
  printf("Tiempo de ejecución: %f\n", tiempo_ejecucion);
  printf("\n");
  return 0;
}
