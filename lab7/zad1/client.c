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

void SIGNAL_handler(int signum) {
    should_run = false;
}

int main(){
    pid_t pid = getpid();
    char queue_name[CLIENT_QUEUE_NAME_SIZE] = {0};
    sprintf(queue_name, "/simple_chat_client_queue_%d", pid);
    struct mq_attr attrubutes = {
        .mq_flags = 0,
        .mq_msgsize = sizeof(message_t),
        .mq_maxmsg = 10
    };
    mqd_t mq_server_descriptor = 
}