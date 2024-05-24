#include <stdio.h>
#include <mqueue.h>



int main(){
    mqd_t id = mq_open("/mq", O_RDWR | O_CREAT, 0666, NULL);
    
    char msg[] = "witaj swiecie\n";
    
    mq_send(id, msg, sizeof(msg), 1);
    printf("wyslano 1\n");

    char msg1[] = "druga wiadomosc\n";
    mq_send(id, msg1, sizeof(msg1), 1);
    printf("wyslano 2\n");

    char rcv[8192], rcv1[8192];
    mq_receive(id, rcv, sizeof(rcv), NULL);
    printf("%s", rcv);

    mq_receive(id, rcv1, sizeof(rcv1), NULL);
    printf("%s", rcv1);
    mq_close(id);
    mq_unlink("/mq");

    return 0;
}