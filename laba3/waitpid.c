#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork error");
        exit(1);
    }

    if (pid == 0) {
        printf("[Child] Running sleep 2...\n");
        execlp("sleep", "sleep", "2", NULL);

        perror("exec failed");
        exit(1);
    } else {
        int status;

        printf("[Parent] Waiting for child...\n");

        pid_t result = waitpid(pid, &status, 0);

        if (result == -1) {
            perror("waitpid error");
            exit(1);
        }

        if (WIFEXITED(status)) {
            printf("[Parent] Child exited with code %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("[Parent] Child killed by signal %d\n", WTERMSIG(status));
        }
    }

    return 0;
}