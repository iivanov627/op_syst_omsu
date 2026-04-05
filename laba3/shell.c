#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CMD 256
#define MAX_ARGS 64


void parse(char *cmd, char **args) {
    int i = 0;
    args[i] = strtok(cmd, " \n");

    while (args[i] != NULL && i < MAX_ARGS - 1) {
        args[++i] = strtok(NULL, " \n");
    }
}

int main() {
    char cmd[MAX_CMD];
    char *args[MAX_ARGS];

    while (1) {
        printf("my_shell> ");
        fflush(stdout);

        if (!fgets(cmd, sizeof(cmd), stdin)) break;

        if (cmd[0] == '\n') continue;

        parse(cmd, args);

        if (!args[0]) continue;

        if (strcmp(args[0], "exit") == 0) {
            break;
        }

        if (strcmp(args[0], "cd") == 0) {
            if (args[1]) {
                if (chdir(args[1]) != 0)
                    perror("cd failed");
            } else {
                printf("cd: missing argument\n");
            }
            continue;
        }


        pid_t pid = fork();

        if (pid < 0) {
            perror("fork error");
            continue;
        }

        if (pid == 0) {
            execvp(args[0], args);
            perror("exec failed"); 
            exit(1);
        } else {
    
            int status;
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}