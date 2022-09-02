#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int **MATRIZ_A, **MATRIZ_B, **RESULTADO;

struct informacionProceso {
  int filas, columnas, cantidadProcesos, indexProceso;
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
      matriz[fila][columna] = (rand() % 1000) + 1;
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

void multiplicarMatrices(struct informacionProceso infoProceso) {
  int filas, columnas, cantidadProcesos, indexProceso, fila, columna, i, desde,
      hasta;

  // Recuperacion de la informacion que se manda encapsulada en el argumento
  filas = infoProceso.filas;
  columnas = infoProceso.columnas;
  cantidadProcesos = infoProceso.cantidadProcesos;
  indexProceso = infoProceso.indexProceso;

  // calculo de filas a trabajar por el proceso
  desde = indexProceso * filas / cantidadProcesos;
  hasta = (indexProceso + 1) * filas / cantidadProcesos;
  printf("-----------------\n");
  printf("indexProceso: %d\n", indexProceso);
  printf("desde: %d\n", desde);
  printf("hasta: %d\n", hasta);
  printf("-----------------\n");

  // Comprobar si el proceso está calculando bien sus valores correspondientes

  // Implementación de la funcion para multiplicar matrices
  // for (fila = desde; fila < hasta; fila++) {
  //   for (columna = 0; columna < columnas; columna++) {
  //     RESULTADO[fila][columna] = 0;
  //     for (i = 0; i < columnas; i++) {
  //       RESULTADO[fila][columna] += MATRIZ_A[fila][i] * MATRIZ_B[i][columna];
  //     }
  //   }
  // }
}

int main(int argc, char *argv[]) {
  // Semilla para la generacion de numeros aleatorios
  srand(time(0));

  struct timeval inicio, final;
  gettimeofday(&inicio, NULL);

  int filas, columnas, cantidadProcesos, indexProceso;
  struct informacionProceso infoProcesos[cantidadProcesos];

  // Obtencion de los parametros que se pasan en el llamado al ejecutable
  filas = atoi(argv[1]);
  cantidadProcesos = atoi(argv[2]);
  columnas = filas; // Debido a que se está trabajando con matrices cuadradas

  // Creacion de los hilos
  for (indexProceso = 0; indexProceso < cantidadProcesos; indexProceso++) {
    // TODO: Remover la estructura
    //  infoProcesos[indexProceso].indexProceso = indexProceso;
    //  infoProcesos[indexProceso].cantidadProcesos = cantidadProcesos;
    //  infoProcesos[indexProceso].columnas = columnas;
    //  infoProcesos[indexProceso].filas = filas;

    // Actividad que realizan los procesos
    pid_t pid = fork();

    if (pid > 0) {
      continue;
    } else if (pid == 0) {
      printf("Hola matriz soy hijo\n");
    }
  }

  // Este wait hace que el proceso padre espere a que todos los procesos hijos
  // terminen antes de que se cierre el programa.
  wait(NULL);
  // for (indexProceso = 0; indexProceso < cantidadProcesos; indexProceso++) {
  // }

  return 0;
}
