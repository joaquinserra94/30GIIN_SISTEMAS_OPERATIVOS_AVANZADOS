#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main (int argc, char **argv) {
    int sfd, dfd;
    char *src, *dest;
    size_t filesize;
    int result;

    if (argc != 3) {
        printf("Uso: %s <archivo1> <archivo2>\n", argv[0]);
        return 1;
    }

    /* ORIGEN */
    sfd = open(argv[1], O_RDWR);
    if (sfd == -1) {
        perror("open");
        return 1;
    }
    filesize = lseek(sfd, 0, SEEK_END);
    src = mmap(NULL, filesize, PROT_READ | PROT_WRITE, MAP_PRIVATE, sfd, 0);
    if (src == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    /* DESTINO */
    dfd = open(argv[2], O_RDWR);
    if (dfd == -1) {
        perror("open");
        return 1;
    }
    dest = mmap(NULL, filesize, PROT_READ | PROT_WRITE, MAP_PRIVATE, dfd, 0);
    if (dest == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    /* COMPARACIÓN */
    result = memcmp(src, dest, filesize);
    if (result == 0) {
        printf("Los archivos son iguales\n");
    } else {
        printf("Los archivos son diferentes\n");
    }

    munmap(src, filesize);
    munmap(dest, filesize);
    close(sfd);
    close(dfd);
    return 0;
}

