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

struct msgbuf{ 
    long mtype;
    char mtext[SIZE]; 
}; 
   
   
int main() { 
    int msgid = msgget(MSG_KEY, 0666);

    struct msgbuf msg; 
    msg.mtype = 1; 

    strcpy(msg.mtext, "Hello, IPC world!"); 
    msgsnd(msgid, &msg, sizeof(msg.mtext), 0);// 0 -блокирует поток

    sleep(2); 
    int shmid = shmget(SHM_KEY, SIZE, 0666); 
    char *shm = shmat(shmid, NULL, 0); // 0 - rw

    printf("Из памяти: %s\n", shm); 
    shmdt(shm); 
    
    return 0; 
}