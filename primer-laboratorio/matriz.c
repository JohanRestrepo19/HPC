#include <stdio.h>

// TODO: 1. Hacer parametrizable el el tamaño de las matrices.
// TODO: 2. Generar valores aleatorios para las matrices.

void display(int filas, int columnas, int matriz[filas][columnas]) {
  for (int fila = 0; fila < filas; fila++) {
    for (int columna = 0; columna < columnas; columna++) {
      printf("%d\t", matriz[fila][columna]);
    }
    printf("\n");
  }
}

//
// void multiply(int a[FILAS_MATRIZ_A][COLUMNAS_MATRIZ_A],
//               int b[FILAS_MATRIZ_B][COLUMNAS_MATRIZ_B],
//               int result[FILAS_MATRIZ_B][COLUMNAS_MATRIZ_A]) {
//   for (int fila = 0; fila < FILAS_MATRIZ_B; fila++) {
//     for (int columna = 0; columna < COLUMNAS_MATRIZ_A; columna++) {
//       result[fila][columna] = 0;
//       for (int i = 0; i < COLUMNAS_MATRIZ_A; i++) {
//         result[fila][columna] += a[fila][i] * b[i][columna];
//       }
//     }
//   }
// }

void generarMatriz(int filas, int columnas) {
  printf("filas: %d columnas: %d\n", filas, columnas);
}

int main() {
  int n;
  printf("Ingrese el valor de N: \n");
  scanf("%d", &n);
  generarMatriz(n, n);
  // int a[3][3] = {
  //     {1, 2, 3},
  //     {1, 1, 1},
  //     {0, 1, -1},
  // };
  // int b[FILAS_MATRIZ_B][COLUMNAS_MATRIZ_B] = {
  //     {1},
  //     {2},
  //     {1},
  // };
  // int c[FILAS_MATRIZ_B][COLUMNAS_MATRIZ_A];

  // multiply(a, b, c);
  return 0;
}
