#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 256

int main() {
    int fd[2];
    pipe(fd);

    pid_t pid = fork();

    if (pid == 0) {
        close(fd[1]);

        char buffer[BUFFER_SIZE];
        int bytes;

        while ((bytes = read(fd[0], buffer, BUFFER_SIZE - 1)) > 0) {
            buffer[bytes] = '\0';
            printf("[PID %d]: %s", getpid(), buffer);
        }

        close(fd[0]);
    } else {
        close(fd[0]);

        char line[BUFFER_SIZE];

        while (fgets(line, BUFFER_SIZE, stdin)) {
            write(fd[1], line, strlen(line));

            if (strncmp(line, "exit", 4) == 0)
                break;
        }

        close(fd[1]);
        wait(NULL);
    }

    return 0;
}