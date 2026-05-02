#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd = open("file.txt", O_RDWR | O_CREAT, 0644);
    write(fd, "hello world", 11);

    char *data = mmap(NULL, 11,
                      PROT_READ | PROT_WRITE,
                      MAP_SHARED,
                      fd, 0);

    data[0] = 'A';

    msync(data, 11, MS_SYNC);

    printf("Result: %s\n", data);

    munmap(data, 11);
    close(fd);

    return 0;
}