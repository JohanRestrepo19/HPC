#include <omp.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

#pragma omp parallel num_threads(7)
  {
    int ID = omp_get_thread_num();
    int num_threads = omp_get_num_threads();
    printf("hola mundo desde %d de %d\n", ID, num_threads);
  }
  return 0;
}
