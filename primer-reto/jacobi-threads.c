
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

double *u, *f, *utmp;

struct thread_info {
  int from, to, h2;
};

/* --
 * Do nsweeps sweeps of Jacobi iteration on a 1D Poisson problem
 *
 *    -u'' = f
 *
 * discretized by n+1 equally spaced mesh points on [0,1].
 * u is subject to Dirichlet boundary conditions specified in
 * the u[0] and u[n] entries of the initial vector.
 */

void *thread_subroutine(void *threadarg) {
  struct thread_info *thread_info;
  int h2, from, to, i;

  thread_info = (struct thread_info *)threadarg;
  h2 = thread_info->h2;
  from = thread_info->from;
  to = thread_info->to;

  /* Old data in u; new data in utmp */
  for (i = from; i < to; ++i)
    utmp[i] = (u[i - 1] + u[i + 1] + h2 * f[i]) / 2;

  /* Old data in utmp; new data in u */
  for (i = from; i < to; ++i)
    u[i] = (utmp[i - 1] + utmp[i + 1] + h2 * f[i]) / 2;

  pthread_exit(NULL);
}

void jacobi(int nsweeps, int size, int threads_ammount) {
  int i, sweep, thread_idx;
  double h = 1.0 / size;
  double h2 = h * h;

  struct thread_info threads_info[threads_ammount];
  pthread_t threads[threads_ammount];

  utmp[0] = u[0];
  utmp[size] = u[size];

  for (sweep = 0; sweep < nsweeps; sweep += 2) {
    for (thread_idx = 0; thread_idx < threads_ammount; thread_idx++) {

      threads_info[thread_idx].h2 = h2;
      threads_info[thread_idx].from = thread_idx * (size - 1) / threads_ammount;
      threads_info[thread_idx].to =
          (thread_idx + 1) * (size - 1) / threads_ammount;

      if (thread_idx == 0) {
        threads_info[thread_idx].from = 1;
      }
      if (pthread_create(&threads[thread_idx], NULL, thread_subroutine,
                         (void *)&threads_info[thread_idx])) {
        printf("There was an error creating a thread\n");
        exit(-1);
      }
    }

    for (thread_idx = 0; thread_idx < threads_ammount; thread_idx++) {
      if (pthread_join(threads[thread_idx], NULL)) {
        printf("There was an error joining a thread\n");
        exit(-1);
      }
    }
  }
}

void write_solution(int n, double *u, const char *fname) {
  int i;
  double h = 1.0 / n;
  FILE *fp = fopen(fname, "w+");
  for (i = 0; i <= n; ++i)
    fprintf(fp, "%g %g\n", i * h, u[i]);
  fclose(fp);
}

int main(int argc, char **argv) {
  int i, n, nsteps, threads_ammount;
  // double *u, *f, h;
  double h;
  char *fname;
  struct timeval tstart, tend;

  /* Process arguments */
  n = (argc > 1) ? atoi(argv[1]) : 100;
  nsteps = (argc > 2) ? atoi(argv[2]) : 100;
  threads_ammount = (argc > 3) ? atoi(argv[3]) : 4;
  fname = (argc > 4) ? argv[4] : NULL;
  h = 1.0 / n;

  /* Allocate and initialize arrays */
  u = (double *)malloc((n + 1) * sizeof(double));
  f = (double *)malloc((n + 1) * sizeof(double));
  utmp = (double *)malloc((n + 1) * sizeof(double));

  memset(u, 0, (n + 1) * sizeof(double));

  for (i = 0; i <= n; ++i)
    f[i] = i * h;

  /* Run the solver */
  gettimeofday(&tstart, NULL);
  // jacobi(nsteps, n, u, f);
  jacobi(nsteps, n, threads_ammount);
  gettimeofday(&tend, NULL);

  double exec_time =
      (tend.tv_sec - tstart.tv_sec) + 1e-6 * (tend.tv_usec - tstart.tv_usec);

  /* Run the solver */
  printf("n: %d\n"
         "nsteps: %d\n"
         "threads_ammount: %d\n"
         "Elapsed time: %f s\n",
         n, nsteps, threads_ammount, exec_time);

  /* Write the results */
  if (fname)
    write_solution(n, u, fname);

  free(f);
  free(u);
  free(utmp);
  return 0;
}
