#include "specs.h"

#include <stdio.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <signal.h>

volatile bool should_run = true;

void handler(int signum){
    should_run = false;
}

int main(){
    
    struct mq_attr attributes = {
        .mq_flags = 0,
        .mq_msgsize = sizeof(message_t),
        .mq_maxmsg = 10
    };

    mqd_t mq_descriptor = mq_open(SERVER_QUEUE_NAME, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR, &attributes);
    message_t receive_message;

    mqd_t client_queues[MAX_CLIENTS_COUNT];
    for (int i=0; i < MAX_CLIENTS_COUNT; i++){
        client_queues[i] = -1;
    }

    for (int sig=1; sig < SIGRTMAX; sig++){
        signal(sig, handler);
    }

    while (should_run){
        mq_receive(mq_descriptor, (char*) &receive_message, sizeof(receive_message), NULL);
        switch(receive_message.type){
            case INIT:
                int id = 0;
                while (client_queues[id] != -1 && id < MAX_CLIENTS_COUNT) {
                    id++;
                }
                client_queues[id] = mq_open(receive_message.text,O_RDWR, S_IRUSR | S_IWUSR, NULL);
                message_t send_message = {
                    .type = IDENTIFIER,
                    .identifier = id
                };
                mq_send(client_queues[id], (char*)&send_message, sizeof(send_message), 10);
                break;
            case MESSAGE_TEXT:
                for (int i=0; i < MAX_CLIENTS_COUNT; i++){
                    if (i != receive_message.identifier && client_queues[i] != -1){
                        mq_send(client_queues[i], (char*)&receive_message, sizeof(receive_message), 10);
                    }
                }
                break;
            case CLIENT_CLOSE:
                mq_close(client_queues[receive_message.identifier]);
                client_queues[receive_message.identifier] = -1;
                break;
            default:
                printf("unexpected message type\n");
                break;
        }
    }

    for (int i = 0; i < MAX_CLIENTS_COUNT; i++){
        if (client_queues[i] != -1){
            mq_close(client_queues[i]);
        }
    }

    mq_close(mq_descriptor);
    mq_unlink(SERVER_QUEUE_NAME);
    return 0;
}