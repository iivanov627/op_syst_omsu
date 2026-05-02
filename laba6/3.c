#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

int global_var = 10;

int main() {
    int stack_var = 20;
    
    void *heap_mem = malloc(128);
    
    void *mmap_mem = mmap(NULL, 4096, PROT_READ, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

    printf("=== Адресное пространство процесса (PID: %d) ===\n", getpid());
    printf("Адрес функции main (код): %p\n", (void*)main);
    printf("Адрес глобальной переменной: %p\n", (void*)&global_var);
    printf("Адрес локальной переменной (стек): %p\n", (void*)&stack_var);
    printf("Адрес кучи (heap): %p\n", heap_mem);
    printf("Адрес mmap-сегмента: %p\n", mmap_mem);
    printf("--- (Содержимое /proc/self/maps) ---\n\n");

    FILE *maps = fopen("/proc/self/maps", "r");
    if (!maps) {
        perror("fopen /proc/self/maps");
        return 1;
    }

    char line[512];
    while (fgets(line, sizeof(line), maps)) {ы
        printf("%s", line);
    }
    fclose(maps);
    
    printf("\n--- (Конец /proc/self/maps) ---\n");
    printf("Сравните адреса с картой памяти выше.\n");

    free(heap_mem);
    munmap(mmap_mem, 4096);

    return 0;
}