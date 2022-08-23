#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct thread_data {
  int filas;
  int columnas;
  int desde;
  int hasta;
};

int **MATRIZ_A, **MATRIZ_B, **RESULTADO;

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

  struct thread_data *myData;
  int desde, hasta, filas, columnas;
  myData = (struct thread_data *)threadarg;

  filas = myData->filas;
  columnas = myData->columnas;
  desde = myData->desde;
  hasta = myData->hasta;

  for (int fila = desde; fila < hasta; fila++) {
    for (int columna = 0; columna < columnas; columna++) {
      RESULTADO[fila][columna] = 0;
      for (int i = 0; i < columnas; i++) {
        RESULTADO[fila][columna] += MATRIZ_A[fila][i] * MATRIZ_B[i][columna];
      }
    }
  }
  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  clock_t inicio = clock();

  double tiempoEjecucion = 0.0;
  srand(time(0));

  int filas = atoi(argv[1]);
  int nroHilos = atoi(argv[2]);
  pthread_t hilos[nroHilos];
  int rc;

  MATRIZ_A = mallocArreglo2dEnteros(filas, filas);
  MATRIZ_B = mallocArreglo2dEnteros(filas, filas);
  RESULTADO = mallocArreglo2dEnteros(filas, filas);

  asignarValoresAleatoriosMatriz(filas, filas, MATRIZ_A);
  asignarValoresAleatoriosMatriz(filas, filas, MATRIZ_B);

  for (int indexHilo = 0; indexHilo < nroHilos; indexHilo++) {
    struct thread_data infoHilo;
    infoHilo.columnas = filas;
    infoHilo.filas = filas;
    infoHilo.desde = (indexHilo * filas) / nroHilos;
    infoHilo.hasta = ((indexHilo + 1) * filas) / nroHilos;

    rc = pthread_create(&hilos[indexHilo], NULL, multiplicarMatrices,
                        (void *)&infoHilo);

    if (rc) {
      printf("ERROR; el codigo de retorno desde pthread_create() is %d \n", rc);
      exit(-1);
    }
  }

  for (int indexHilo = 0; indexHilo < nroHilos; indexHilo++) {
    rc = pthread_join(hilos[indexHilo], NULL);
    if (rc) {
      printf("ERROR; el codigo de retorno desde pthread_join() is %d \n", rc);
      exit(-1);
    }
  }

  pthread_exit(NULL);

  mostrarMatriz(filas, filas, MATRIZ_A);
  mostrarMatriz(filas, filas, MATRIZ_B);
  mostrarMatriz(filas, filas, RESULTADO);

  liberarArreglo2dEnteros(MATRIZ_A, filas, filas);
  liberarArreglo2dEnteros(MATRIZ_B, filas, filas);
  liberarArreglo2dEnteros(RESULTADO, filas, filas);

  clock_t final = clock();

  tiempoEjecucion = (double)(final - inicio) / CLOCKS_PER_SEC;

  printf("Multiplicando matrices de %i x %i\n", filas, filas);
  printf("Tiempo de ejecución: %f\n", tiempoEjecucion);
  printf("\n");
}
