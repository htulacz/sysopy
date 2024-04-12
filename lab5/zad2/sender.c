#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

#define NUM_SIGNALS 3

void send_signal(pid_t catcher_pid) {
    kill(catcher_pid, SIGUSR1);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <catcher_pid> <mode>\n", argv[0]);
        exit(1);
    }

    pid_t catcher_pid = atoi(argv[1]);
    int mode = atoi(argv[2]);

    if (mode < 1 || mode > 3) {
        printf("Invalid mode. Mode must be between 1 and 3\n");
        exit(1);
    }

    for (int i = 0; i < NUM_SIGNALS; ++i) {
        send_signal(catcher_pid);
        pause();
    }

    return 0;
}
