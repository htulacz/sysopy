#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * 1. Ojciec wysyła dany sygnał wraz wartością z argv[2]
 *    Dziecko blokuje wszystkie sygnały oprócz SIGUSR1,
 *    oraz wypisuje wiadaomość którą dostał wraz z sygnałem.
 *    sigqueue, siginfo itp.
 */

void sig_handler(int sig, siginfo_t* siginfo, void* context) {
    printf("Child: %d\n", siginfo->si_value.sival_int);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Not a suitable number of program parameters\n");
        return 1;
    }

    struct sigaction action;
    action.sa_sigaction = &sig_handler;
    action.sa_flags = SA_SIGINFO;

    sigemptyset(&action.sa_flags);

    sigset_t mask;

    if (sigfillset(&mask) == -1 ){
        perror("sigfill");
    }

    pid_t pid = fork();

    if (pid == 0){
        sigprocmask(SIG_BLOCK, &mask, NULL);
        sigaction(SIGUSR1, &action, NULL);
        pause();
    }else {
        sleep(1);
        union sigval sv;
        sv.sival_int = atoi(argv[1]);
        int signal = atoi(argv[2]);
        sigqueue(pid, signal, sv);
    }

    return 0;
}