#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_MODE 3

int mode = 1;
int changes = 0;

void sigusr1_handler(int sig, siginfo_t *info, void *ucontext) {
    pid_t sender_pid = info->si_pid;

    kill(sender_pid, SIGUSR1);
    if (mode != info->si_value.sival_int){
        changes++;
    }
    mode = info->si_value.sival_int;

    printf("Catcher received SIGUSR1 from sender (PID: %d) with mode: %d\n", sender_pid, mode);

    switch (mode) {
        case 1:
            printf("Mode 1: Printing numbers 1 to 100\n");
            for (int i = 1; i <= 100; ++i)
                printf("%d\n", i);
            break;
        case 2:
            printf("Mode 2: Number of mode change requests: %d\n", changes);
            break;
        case 3:
            printf("Mode 3: Exiting catcher...\n");
            exit(0);
            break;
        default:
            break;
    }
}

int main() {
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = sigusr1_handler;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);

    printf("Catcher PID: %d\n", getpid());

    while (1)
        pause();

    return 0;
}
