#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sigusr1_handler(int signal) {
    printf("Received SIGUSR1 signal\n");
}

void check_pending_signal() {
    sigset_t pending_signals;
    sigpending(&pending_signals);
    if (sigismember(&pending_signals, SIGUSR1)) {
        printf("Pending SIGUSR1 signal is visible\n");
    } else {
        printf("No pending SIGUSR1 signal\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s [none|ignore|handler|mask]\n", argv[0]);
        return 1;
    }

    char *action = argv[1];

    if (strcmp(action, "none") == 0) {

    } else if (strcmp(action, "ignore") == 0) {
        signal(SIGUSR1, SIG_IGN);
    } else if (strcmp(action, "handler") == 0) {
        signal(SIGUSR1, sigusr1_handler);
    } else if (strcmp(action, "mask") == 0) {
        sigset_t mask;
        sigemptyset(&mask);
        sigaddset(&mask, SIGUSR1);
        sigprocmask(SIG_BLOCK, &mask, NULL);
    } else {
        printf("Invalid argument\n");
        return 1;
    }

    raise(SIGUSR1);

    if (strcmp(action, "none") != 0) {
        check_pending_signal();
    }

    return 0;
}
