#include <stdio.h>
#include <sys/ipc.h>


struct msgbuf {
    long mtype;
    char mtext[100];
};


int main(){
    key_t key = ftok(".", "1");
    int id = msgget(key,0666 | IPC_CREAT);
    struct msgbuf buffer;
    buffer.mtype = 1;
    strcpy(buffer.mtext, "witaj swiecie");
    msgsnd(id, &buffer, sizeof(buffer), 0);
    printf("wyslano 1\n");
    
    buffer.mtype = 2;
    strcpy(buffer.mtext, "druga wiadomosc");
    msgsnd(id, &buffer, sizeof(buffer), 0);
    printf("wyslano 2\n");
    
    
    struct msgbuf receiver;
    msgrcv(id, &receiver, sizeof(receiver), 1, 0);
    printf("%s ", receiver.mtext);
    
    msgrcv(id, &receiver, sizeof(receiver), 2, 0);
    printf("%s\n", receiver.mtext);
    
    msgctl(id, IPC_RMID, NULL);
    return 0;
}