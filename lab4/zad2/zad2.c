#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int global = 0;


int main(int argc, char * argv[]){
    int local = 0;
    pid_t pid = fork();

    if (pid == 0){
        printf("childs process\n");
        global ++;
        local ++;
        printf("child pid = %d, parent pid = %d\n", getpid(), getppid());
        printf("child's local = %d, child's global = %d\n", local, global);

        execl("/bin/ls", "ls", argv[1], NULL);
        return EXIT_FAILURE;
    } else {
        wait(NULL);
        printf("parent process\n");
        printf("parent pid = %d, child pid = %d\n", getpid(), pid);

        int status;
        wait(&status);

        if (WIFEXITED(status)) {
            printf("Child exit code: %d\n", WEXITSTATUS(status));
        }

        printf("Parent's local = %d, parent's global = %d\n", local, global);

        return EXIT_SUCCESS;
    }
}