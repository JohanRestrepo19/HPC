#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int **MATRIZ_A, **MATRIZ_B, **RESULTADO;

int **asignar_matriz_enteros_globalmente(int filas, int columnas) {
  int fila, **doble_puntero_entero;
  doble_puntero_entero =
      (int **)mmap(NULL, filas * sizeof(int *), PROT_READ | PROT_WRITE,
                   MAP_SHARED | MAP_ANONYMOUS, -1, 0);

  for (fila = 0; fila < filas; fila++) {
    doble_puntero_entero[fila] =
        (int *)mmap(NULL, columnas * sizeof(int), PROT_READ | PROT_WRITE,
                    MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  }

  return doble_puntero_entero;
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
  gettimeofday(&inicio, NULL);

  int filas, columnas, cant_procesos, idx_proceso, status;
  pid_t pidC;

  // Obtencion de los parametros que se pasan en el llamado al ejecutable
  filas = atoi(argv[1]);
  cant_procesos = atoi(argv[2]);
  columnas = filas; // Debido a que se está trabajando con matrices cuadradas

  MATRIZ_A = asignar_matriz_enteros_globalmente(filas, columnas);
  MATRIZ_B = asignar_matriz_enteros_globalmente(filas, columnas);
  RESULTADO = asignar_matriz_enteros_globalmente(filas, columnas);

  asignar_valores_aleatorios_matriz(filas, columnas, MATRIZ_A);
  asignar_valores_aleatorios_matriz(filas, columnas, MATRIZ_B);

  // Creacion de los procesos
  for (idx_proceso = 0; idx_proceso < cant_procesos; idx_proceso++) {
    pidC = fork();
    if (pidC > 0)
      continue;
    else if (pidC == 0) {
      multiplicar_matrices(filas, columnas, cant_procesos, idx_proceso);
      exit(0);
    } else {
      printf("Hubo un error creando el hilo\n");
    }
  }

  // Esperar la ejecución de los procesos hijos
  for (idx_proceso = 0; idx_proceso < cant_procesos; idx_proceso++) {
    pidC = wait(&status);
    // printf("PADRE de PID = %d, hijo de PID = %d terminado, st = %d \n",
    //        getpid(), pidC, WEXITSTATUS(status));
  }

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
