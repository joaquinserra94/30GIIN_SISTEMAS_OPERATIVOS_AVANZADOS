#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Uso: %s <archivo1> <archivo2>\n", argv[0]);
    return EXIT_FAILURE;
  }

  // Abrir archivos
  int fd1 = open(argv[1], O_RDONLY);
  if (fd1 < 0) {
    perror("Error al abrir archivo 1");
    return EXIT_FAILURE;
  }
  int fd2 = open(argv[2], O_RDONLY);
  if (fd2 < 0) {
    perror("Error al abrir archivo 2");
    return EXIT_FAILURE;
  }

  // Obtener tamaños de archivo
  struct stat stat1, stat2;
  if (fstat(fd1, &stat1) < 0) {
    perror("Error al obtener tamaño de archivo 1");
    return EXIT_FAILURE;
  }
  if (fstat(fd2, &stat2) < 0) {
    perror("Error al obtener tamaño de archivo 2");
    return EXIT_FAILURE;
  }

  // Si los tamaños son diferentes, los archivos son diferentes
  if (stat1.st_size != stat2.st_size) {
    printf("Los archivos son diferentes\n");
    return EXIT_SUCCESS;
  }

  // Proyectar archivos en memoria
  void *ptr1 = mmap(NULL, stat1.st_size, PROT_READ, MAP_PRIVATE, fd1, 0);
  if (ptr1 == MAP_FAILED) {
    perror("Error al proyectar archivo 1 en memoria");
    return EXIT_FAILURE;
  }
  void *ptr2 = mmap(NULL, stat2.st_size, PROT_READ, MAP_PRIVATE, fd2, 0);
  if (ptr2 == MAP_FAILED) {
    perror("Error al proyectar archivo 2 en memoria");
    return EXIT_FAILURE;
  }

  // Comparar contenido de los archivos
  int cmp = memcmp(ptr1, ptr2, stat1.st_size);

  // Liberar recursos
  munmap(ptr1, stat1.st_size);
  munmap(ptr2, stat2.st_size);
  close(fd1);
  close(fd2);

  // Imprimir resultado
  if (cmp == 0) {
    printf("Los archivos son iguales\n");
  } else {
    printf("Los archivos son diferentes\n");
  }

  return EXIT_SUCCESS;
}
