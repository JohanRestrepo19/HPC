#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void asignarValoresAleatoriosMatriz(int cantidadElementos, int *matriz) {
  for (int i = 0; i < cantidadElementos; i++) {
    matriz[i] = rand() % 20;
  }
}

void mostrarMatriz(int n, int cantidadElementos, int *matriz) {
  for (int elemento = 0; elemento < cantidadElementos; elemento++) {
    if ((elemento % n) == 0)
      printf("\n");

    printf("%d\t", matriz[elemento]);
  }
  printf("\n");
}

int main(int argc, char *argv[]) {
  srand(time(0));
  int n, *matriz;
  printf("Ingrese la cantidad de elementos de filas de la matriz: ");
  scanf("%i", &n);

  matriz = (int *)malloc((n * n) * sizeof(int));
  asignarValoresAleatoriosMatriz(n * n, matriz);
  mostrarMatriz(n, n * n, matriz);

  return 0;
}
