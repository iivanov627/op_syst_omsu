#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork error");
        exit(1);
    }

    if (pid == 0) {
        printf("[Child] PID=%d, PPID=%d\n", getpid(), getppid());

        execlp("ls", "ls", "-l", NULL);

        perror("exec failed");
        exit(1);
    } else {
        printf("[Parent] PID=%d created child PID=%d\n", getpid(), pid);
    }

    return 0;
}