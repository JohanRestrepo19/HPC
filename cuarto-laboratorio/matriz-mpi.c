#include <mpi/mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

int *malloc_arreglo_1d_enteros(int filas, int columnas) {
  int *puntero_enteros;
  puntero_enteros = malloc(filas * columnas * sizeof(int));
  return puntero_enteros;
}

void asignar_valores_aleatorios_arreglo(int filas, int columnas, int *matriz) {
  for (int idx = 0; idx < filas * columnas; idx++) {
    matriz[idx] = (rand() % 3) + 1;
  }
}

void mostrar_arreglo(int cant_elementos, int *arreglo) {
  for (int idx = 0; idx < cant_elementos; idx++) {
    printf("%d\t", arreglo[idx]);
  }
  printf("\n");
}

void mostrar_arreglo_como_matriz(int filas, int columnas, int *arreglo) {
  int contador_elementos = 0;

  for (int idx = 0; idx < filas * columnas; idx++) {
    printf("%d\t", arreglo[idx]);
    contador_elementos++;
    if (contador_elementos == columnas) {
      printf("\n");
      contador_elementos = 0;
    }
  }
  printf("\n");
}

int main(int argc, char *argv[]) {
  // Semilla para la generacion de numeros aleatorios
  srand(time(0));
  int filas, columnas, idx_proceso, cant_procesos;
  int i, j, sum = 0;
  int cant_elemen_por_proceso;
  int *matriz_a, *matriz_b, *resultado;

  // Obtencion de los parametros que se pasan en el llamado al ejecutable
  filas = atoi(argv[1]);
  columnas = filas;

  matriz_a = malloc_arreglo_1d_enteros(filas, columnas);
  matriz_b = malloc_arreglo_1d_enteros(filas, columnas);
  resultado = malloc_arreglo_1d_enteros(filas, columnas);
  asignar_valores_aleatorios_arreglo(filas, columnas, matriz_a);
  asignar_valores_aleatorios_arreglo(filas, columnas, matriz_b);

  MPI_Init(&argc, &argv);

  MPI_Comm_size(MPI_COMM_WORLD, &cant_procesos);
  MPI_Comm_rank(MPI_COMM_WORLD, &idx_proceso);

  cant_elemen_por_proceso = filas * columnas / cant_procesos;

  if (idx_proceso == 0) {
    printf("Matriz a desde proceso 0:\n");
    mostrar_arreglo_como_matriz(filas, columnas, matriz_a);
  }

  MPI_Barrier(MPI_COMM_WORLD);

  if (idx_proceso == 1) {
    printf("Matriz b desde proceso 1:\n");
    mostrar_arreglo_como_matriz(filas, columnas, matriz_b);
  }

  int *matriz_a_temp = malloc(cant_elemen_por_proceso * sizeof(int));

  MPI_Scatter(matriz_a, cant_elemen_por_proceso, MPI_INT, matriz_a_temp,
              cant_elemen_por_proceso, MPI_INT, 0, MPI_COMM_WORLD);

  MPI_Barrier(MPI_COMM_WORLD);

  printf("El procesos %d recibió los siguientes elementos: ", idx_proceso);
  mostrar_arreglo((filas * columnas / cant_procesos), matriz_a_temp);
  MPI_Finalize();

  return 0;
}
