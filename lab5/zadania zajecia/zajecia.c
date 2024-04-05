#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
int global = 0;
int sigCnt = 0;

void handler(int signum){
    printf("%d %d %f\n", global, sigCnt, (double)global/(double)sigCnt);
    global++;
}
int main(){
    pid_t child_pid;
    child_pid = fork();

    if (child_pid == 0){
        while(1) {
            signal(SIGUSR1, handler);
            sigCnt++;
        }
    }

    if (child_pid > 0){
        sleep(1);
        while (1){
            kill(child_pid,SIGUSR1);
        }
    }

    return 0;
}
