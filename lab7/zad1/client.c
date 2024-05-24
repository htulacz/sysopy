#include "specs.h"

#include <stdio.h>
#include <mqueue.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>

volatile bool should_run = true;

void handler(int signum) {
    should_run = false;
}

int min(a,b){
    if (a < b){
        return a;
    } else {
        return b;
    }
}

int main(){
    pid_t pid = getpid();
    char queue_name[CLIENT_QUEUE_NAME_SIZE] = {0};
    sprintf(queue_name, "/simple_chat_client_queue_%d", pid);
    struct mq_attr attributes = {
        .mq_flags = 0,
        .mq_msgsize = sizeof(message_t),
        .mq_maxmsg = 10
    };
    mqd_t mq_client_descriptor = mq_open(queue_name, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR, &attributes);
    mqd_t mq_server_descriptor = mq_open(SERVER_QUEUE_NAME, O_RDWR, S_IRUSR | S_IWUSR, NULL);
    message_t message_init = {
        .type = INIT,
        .identifier = -1
    };
    memcpy(message_init.text, queue_name, min(CLIENT_QUEUE_NAME_SIZE-1, strlen(queue_name)));
    mq_send(mq_server_descriptor, (char*)&message_init, sizeof(message_init), 10);
    int to_parent[2];
    pipe(to_parent);
    for (int sig=1; sig < SIGRTMAX; sig++){
        signal(sig,handler);
    }
    pid_t listener = fork();
    if (listener == 0){
        close(to_parent[0]);
        message_t receive_message;
        while (should_run){
            mq_receive(mq_client_descriptor,(char*)&receive_message, sizeof(receive_message), NULL);
            switch(receive_message.type){
                case MESSAGE_TEXT:
                    printf("Received from id: %d message: %s\n", receive_message.identifier, receive_message.text);
                    break;
                case IDENTIFIER:
                    printf("Received identifier from server: %d\n", receive_message.identifier);
                    write(to_parent[1], &receive_message.identifier, sizeof(receive_message.identifier));
                    break;
                default:
                    printf("Unknown message type in client queue: %d", receive_message.type);
                    break;
            }
        }
        exit(0);
    } else {
        close(to_parent[1]);
        int id = -1;
        read(to_parent[0],&id,sizeof(id));
        char* buffer = NULL;
        while (should_run){
            mq_getattr(mq_server_descriptor,&attributes);
            if(attributes.mq_curmsgs >= attributes.mq_maxmsg) {
                printf("Server is busy, please wait\n");
                continue;
            }
            if(scanf("%ms", &buffer) == 1) {
                message_t send_message = {
                    .type = MESSAGE_TEXT,
                    .identifier = id
                };
                memcpy(send_message.text, buffer, MIN(MESSAGE_BUFFER_SIZE - 1, strlen(buffer)));

                mq_send(mq_server_descriptor, (char*)&send_message, sizeof(send_message), 10);

                free(buffer);
                buffer = NULL;
            } else
                perror("scanf input");
        }
        if(id != -1){
            message_t message_close = {
                .type = CLIENT_CLOSE,
                .identifier = id
            };
            mq_send(mq_server_descriptor, (char*)&message_close, sizeof(message_close), 10);
        }

        mq_close(mq_server_descriptor);
        mq_close(mq_client_descriptor);

        mq_unlink(queue_name);
    }
}
