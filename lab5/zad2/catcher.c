#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_MODE 3

int mode = 1;

void sigusr1_handler(int sig, siginfo_t *info, void *ucontext) {
    pid_t sender_pid = info->si_pid;

    kill(sender_pid, SIGUSR1);

    printf("Catcher received SIGUSR1 from sender (PID: %d)\n", sender_pid);

    switch (mode) {
        case 1:
            for (int i = 1; i <= 100; ++i)
                printf("%d\n", i);
            break;
        case 2:
            printf("Received mode change request %d times\n", info->si_value.sival_int);
            break;
        case 3:
            printf("Catcher exiting...\n");
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
