#include <omp.h>
#include <stdio.h>
static long num_steps = 100000;
double step;

// int main(int argc, char *argv[]) {
//
// #pragma omp parallel num_threads(7)
//   {
//     int ID = omp_get_thread_num();
//     int num_threads = omp_get_num_threads();
//     printf("hola mundo desde %d de %d\n", ID, num_threads);
//   }
//   return 0;
// }

int main(int argc, char *argv[]) {
  int i;
  double x, pi, sum = 0.0;
  step = 1.0 / (double)num_steps;

  for (i = 0; i < num_steps; i++) {
    x = (i + 0.5) * step;
    sum = sum + 4.0 / (1.0 + x * x);
  }
  pi = step * sum;
  printf("Pi = %f\n", pi);

  return 0;
}
