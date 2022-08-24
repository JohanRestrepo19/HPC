#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int **MATRIZ_A, **MATRIZ_B, **RESULTADO;

struct informacionHilo {
  int filas, columnas, cantidadHilos, indexHilo;
};

int **mallocArreglo2dEnteros(int filas, int columnas) {
  int **doblePunteroEntero;
  doblePunteroEntero = (int **)malloc(filas * sizeof(int *));

  for (int fila = 0; fila < filas; fila++) {
    doblePunteroEntero[fila] = (int *)malloc(columnas * sizeof(int));
  }

  return doblePunteroEntero;
}

void liberarArreglo2dEnteros(int **doblePunteroEntero, int filas,
                             int columnas) {
  for (int fila = 0; fila < filas; fila++) {
    free(doblePunteroEntero[fila]);
  }
  free(doblePunteroEntero);
}

void asignarValoresAleatoriosMatriz(int filas, int columnas, int **matriz) {
  for (int fila = 0; fila < filas; fila++) {
    for (int columna = 0; columna < columnas; columna++) {
      matriz[fila][columna] = rand() % 20;
    }
  }
}

void mostrarMatriz(int filas, int columnas, int **matriz) {
  for (int fila = 0; fila < filas; fila++) {
    for (int columna = 0; columna < columnas; columna++) {
      printf("%d\t", matriz[fila][columna]);
    }
    printf("\n");
  }
  printf("\n");
}

void *multiplicarMatrices(void *threadarg) {
  struct informacionHilo *infoHilo;
  int filas, columnas, cantidadHilos, indexHilo, fila, columna, i, desde, hasta;

  // Recuperación de la información que se manda encapsulada en el argumento
  infoHilo = (struct informacionHilo *)threadarg;
  filas = infoHilo->filas;
  columnas = infoHilo->columnas;
  cantidadHilos = infoHilo->cantidadHilos;
  indexHilo = infoHilo->indexHilo;

  // calculo de filas a trabar por el hilo
  desde = indexHilo * filas / cantidadHilos;
  hasta = (indexHilo + 1) * filas / cantidadHilos;

  // Implementación de la función de multiplicación
  for (fila = desde; fila < hasta; fila++) {
    for (columna = 0; columna < columnas; columna++) {
      RESULTADO[fila][columna] = 0;
      for (i = 0; i < columnas; i++) {
        RESULTADO[fila][columna] += MATRIZ_A[fila][i] * MATRIZ_B[i][columna];
      }
    }
  }
  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  clock_t inicioEjecucion = clock();
  // Semilla para la generación de numeros aleatorios
  srand(time(0));

  double tiempoEjecucion = 0.0;
  int filas, columnas, cantidadHilos, indexHilo;
  struct informacionHilo infoHilos[cantidadHilos];
  pthread_t hilos[cantidadHilos];

  filas = atoi(argv[1]);
  cantidadHilos = atoi(argv[2]);
  columnas = filas;

  MATRIZ_A = mallocArreglo2dEnteros(filas, columnas);
  MATRIZ_B = mallocArreglo2dEnteros(filas, columnas);
  RESULTADO = mallocArreglo2dEnteros(filas, columnas);

  asignarValoresAleatoriosMatriz(filas, columnas, MATRIZ_A);
  asignarValoresAleatoriosMatriz(filas, columnas, MATRIZ_B);

  printf("Matriz A\n");
  mostrarMatriz(filas, columnas, MATRIZ_A);
  printf("Matriz B\n");
  mostrarMatriz(filas, columnas, MATRIZ_B);
  // Creacion de los hilos
  for (indexHilo = 0; indexHilo < cantidadHilos; indexHilo++) {
    // NOTE: Posible solución: crear la estructura de tipo puntero
    infoHilos[indexHilo].indexHilo = indexHilo;
    infoHilos[indexHilo].cantidadHilos = cantidadHilos;
    infoHilos[indexHilo].columnas = columnas;
    infoHilos[indexHilo].filas = filas;

    // TODO: Implementar el paso de argumentos utilizando un array, ver el
    // ejemplo de la pagina hpc-tutorials llnl
    if (pthread_create(&hilos[indexHilo], NULL, multiplicarMatrices,
                       (void *)&infoHilos[indexHilo]) != 0) {
      printf("Hubo un error al crear el hilo\n");
      exit(-1);
    }
  }

  // Hacer el join de los hilos
  for (indexHilo = 0; indexHilo < cantidadHilos; indexHilo++) {
    if (pthread_join(hilos[indexHilo], NULL)) {
      printf("Hubo un error al crear el hilo\n");
      exit(-1);
    }
  }

  printf("Resultado\n");
  mostrarMatriz(filas, columnas, RESULTADO);

  // Liberar la memoria
  // liberarArreglo2dEnteros(MATRIZ_A, filas, columnas);
  // liberarArreglo2dEnteros(MATRIZ_B, filas, columnas);
  // liberarArreglo2dEnteros(RESULTADO, filas, columnas);

  // Tomar el tiempo de ejecución
  clock_t finalEjecucion = clock();
  //
  tiempoEjecucion = (double)(finalEjecucion - inicioEjecucion) / CLOCKS_PER_SEC;
  printf("Multiplicando matrices de %i x %i\n", filas, filas);
  printf("Tiempo de ejecución: %f\n", tiempoEjecucion);
  printf("\n");
}
