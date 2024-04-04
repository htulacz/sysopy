#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argn, char * argv[]){
    int n = atoi(argv[1]);
    for (int i=0; i<n; i++){
        pid_t child = fork();
        if ((int) child == 0){
            printf("%d %d\n", (int) getppid(), (int) getpid());
            exit(0);
        }
    }
    while(wait(NULL) > 0){}
    printf("%d\n",n);
}