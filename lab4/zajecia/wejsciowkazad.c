#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    int a = 1;
    for (int i=0; i<1;i++) {
        pid_t child_pid;
        child_pid = fork();
        if ((int) child_pid == 0){
            sleep(3);
            a++;
            printf("%d",a);
            exit(0);
        }
        printf("%d",a);
    }
    while (wait(NULL) > 0){}
}