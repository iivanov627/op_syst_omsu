#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

int main() {
    printf("PID: %d\n", getpid());

    void *start = sbrk(0);
    void *mem1 = sbrk(4096);

    strcpy(mem1, "heap memory");

    void *mem2 = mmap(NULL, 4096,
                      PROT_READ | PROT_WRITE,
                      MAP_PRIVATE | MAP_ANONYMOUS,
                      -1, 0);

    strcpy(mem2, "mmap memory");

    printf("sbrk: %p -> %s\n", mem1, (char*)mem1);
    printf("mmap: %p -> %s\n", mem2, (char*)mem2);

    getchar();

    munmap(mem2, 4096);
    brk(start);

    return 0;
}