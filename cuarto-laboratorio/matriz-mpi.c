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
  int cant_elemen_por_proceso, cant_filas_por_proceso;
  int *matriz_b;

  // Obtencion de los parametros que se pasan en el llamado al ejecutable
  filas = atoi(argv[1]);
  columnas = filas;

  matriz_b = malloc_arreglo_1d_enteros(filas, columnas);

  asignar_valores_aleatorios_arreglo(filas, columnas, matriz_b);

  MPI_Init(&argc, &argv);

  MPI_Comm_size(MPI_COMM_WORLD, &cant_procesos);
  MPI_Comm_rank(MPI_COMM_WORLD, &idx_proceso);

  cant_elemen_por_proceso = filas * columnas / cant_procesos;
  cant_filas_por_proceso = filas / cant_procesos;

  int *matriz_a;
  int *resultado;

  if (idx_proceso == 0) {
    matriz_a = malloc_arreglo_1d_enteros(filas, columnas);
    asignar_valores_aleatorios_arreglo(filas, columnas, matriz_a);

    resultado = malloc_arreglo_1d_enteros(filas, columnas);
  }

  int *matriz_a_temp = malloc(cant_elemen_por_proceso * sizeof(int));
  int *resultado_temp = malloc(cant_elemen_por_proceso * sizeof(int));

  MPI_Scatter(matriz_a, cant_elemen_por_proceso, MPI_INT, matriz_a_temp,
              cant_elemen_por_proceso, MPI_INT, 0, MPI_COMM_WORLD);

  MPI_Barrier(MPI_COMM_WORLD);

  // Implementación de la multiplicación de la matriz
  for (int fila = 0; fila < cant_filas_por_proceso; fila++) {
    for (int columna = 0; columna < columnas; columna++) {
      resultado_temp[fila * columnas + columna] = 0;
      for (int k = 0; k < columnas; k++) {
        resultado_temp[fila * columnas + columna] +=
            matriz_a_temp[fila * columnas + k] * matriz_b[k * filas + columna];
      }
    }
  }

  MPI_Barrier(MPI_COMM_WORLD);

  MPI_Gather(resultado_temp, cant_elemen_por_proceso, MPI_INT, resultado,
             cant_elemen_por_proceso, MPI_INT, 0, MPI_COMM_WORLD);

  MPI_Barrier(MPI_COMM_WORLD);

  if (idx_proceso == 0) {
    printf("Matriz A: \n");
    mostrar_arreglo_como_matriz(filas, columnas, matriz_a);
    printf("Matriz B: \n");
    mostrar_arreglo_como_matriz(filas, columnas, matriz_b);
    printf("Matriz Resultado: \n");
    mostrar_arreglo_como_matriz(filas, columnas, resultado);

    free(matriz_a);
    free(matriz_b);
    free(resultado);
    free(matriz_a_temp);
    free(resultado_temp);
  }

  MPI_Finalize();

  return 0;
}
