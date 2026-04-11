#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <unistd.h>

#define MSG_KEY 1234
#define SHM_KEY 4321
#define SIZE 256

struct msgbuf {
    long mtype;
    char mtext[SIZE];
};

int main() {
    int msgid = msgget(MSG_KEY, IPC_CREAT | 0666);
    int shmid = shmget(SHM_KEY, SIZE, IPC_CREAT | 0666);

    char *shm = shmat(shmid, NULL, 0);

    struct msgbuf msg;

    msgrcv(msgid, &msg, sizeof(msg.mtext), 1, 0);

    printf("Получено: %s\n", msg.mtext);

    strcpy(shm, msg.mtext);

    sleep(5);

    shmdt(shm);
    shmctl(shmid, IPC_RMID, NULL);
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}