#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>

int main(int argc, char **argv)
{
    int fd, nread, i;
    struct stat sb;
    char *mapped;

    if (argc <= 1) {
        printf("%s: Need file path!\n", argv[0]);
        exit(-1);
    }

    if ((fd = open(argv[1], O_RDWR)) < 0) {
        perror("open");
    }

    if ((fstat(fd, &sb)) == -1) {
        perror("fstat");
    }

    if ((mapped = (char *)mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == (void *)-1) {
        perror("mmap");
    }

    close(fd);

    printf("%s", mapped);
    sprintf(mapped, "%s", "this is the first code");
    
    if ((msync((void *)mapped, sb.st_size, MS_SYNC)) == -1) {
        perror("msync");
    }

    if ((munmap((void *)mapped, sb.st_size)) == -1) {
        perror("munmap");
    }

    return 0;
}
