#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>

int main() {
    int fd;
    struct stat dstat;
    int i, n=0;
    char c, *vec;

    fd = open("ejemplo.txt", O_RDONLY);

    fstat(fd, &dstat);
    printf("Tamaño del buffer = %d\n", dstat.st_size);

    vec = mmap(NULL, dstat.st_size, PROT_READ, MAP_SHARED, fd, 0);
    printf("Vector leido del fichero = %s\n", vec);
    printf("Vector posicion memoria = %p\n", vec);

    close(fd);
    c=*vec;
    for (i=1; i<dstat.st_size; i++) {
        printf("c=%s\n", &c);
        if (c==' ') {
            n++;
        }
        c=vec[i];
}

munmap(vec, dstat.st_size);
printf("\nNumero de blancos = %d\n", n);
return 0;
}


