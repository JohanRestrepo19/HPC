#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

void *thread_routine(void *arg) {
  int nr_lines = *((int *)arg);
  int fd;
  char buffer[] = "Nueva linea \n";

  printf("El hilo comienza a ejecutarse... \n");
  for (int i = 0; i < nr_lines; i++) {
    fd = open("/home/johan/Escritorio/decimo-semestre/HPC/pruebas/file.txt",
              O_WRONLY | O_APPEND);
    write(fd, buffer, sizeof(buffer) - 1);
  }
  close(fd);
  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  pthread_t thread1;
  int value = 0;

  if (argc > 1) {
    value = atoi(argv[1]);
  } else {
    printf("Se te olvidó pasar un argumento, numero de lineas a escribir. \n");
  }

  if (pthread_create(&thread1, NULL, thread_routine, &value) != 0) {
    exit(-1);
  }
  pthread_join(thread1, NULL);
}
