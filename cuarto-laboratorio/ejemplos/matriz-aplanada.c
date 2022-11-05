#include <stdio.h>
#include <stdlib.h>
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

void multiplicar_matrices(int filas, int columnas, int *matriz_a, int *matriz_b,
                          int *resultado) {
  for (int fila = 0; fila < filas; fila++) {
    for (int columna = 0; columna < columnas; columna++) {
      resultado[fila * columnas + columna] = 0;
      for (int i = 0; i < columnas; i++) {
        resultado[fila * columnas + columna] +=
            matriz_a[fila * columnas + i] * matriz_b[i * filas + columna];
      }
    }
  }
}

int main(int argc, char *argv[]) {
  srand(time(0));
  double tiempo_ejecucion = 0.0;
  clock_t inicio = clock();

  int filas, *matriz_a, *matriz_b, *resultado;
  filas = atoi(argv[1]);

  matriz_a = malloc_arreglo_1d_enteros(filas, filas);
  matriz_b = malloc_arreglo_1d_enteros(filas, filas);
  resultado = malloc_arreglo_1d_enteros(filas, filas);

  asignar_valores_aleatorios_arreglo(filas, filas, matriz_a);
  asignar_valores_aleatorios_arreglo(filas, filas, matriz_b);
  multiplicar_matrices(filas, filas, matriz_a, matriz_b, resultado);

  mostrar_arreglo_como_matriz(filas, filas, matriz_a);
  mostrar_arreglo_como_matriz(filas, filas, matriz_b);
  mostrar_arreglo_como_matriz(filas, filas, resultado);

  free(matriz_a);
  free(matriz_b);
  free(resultado);

  clock_t final = clock();

  tiempo_ejecucion = (double)(final - inicio) / CLOCKS_PER_SEC;

  printf("Multiplicando matrices de %i x %i\n", filas, filas);
  printf("Tiempo de ejecución: %f\n", tiempo_ejecucion);
  printf("\n");
}
