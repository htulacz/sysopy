#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
int global = 0;
int sigCnt = 0;

void handler(int signum){
//    printf("%d %d\n", global);
    global++;
}
int main(){
    pid_t child_pid;
    child_pid = fork();

    if (child_pid == 0){
        while(1) {
            signal(SIGUSR1, handler);
        }
    }

    if (child_pid > 0){
        sleep(1);
        union signal sv;
        while (1){
            sigCnt++;
            sv.sival_int =sigCnt;
            sigqueue(child_pid,SIGUSR1,sv);
        }
    }

    return 0;
}
