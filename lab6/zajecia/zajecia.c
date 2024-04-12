#include <stdio.h>
#include <sys/types.h>
#include <string.h>


int main(){
    int fd[2], fd1[2];
    pipe(fd);
    pipe(fd1);
    pid_t pid = fork();
    if (pid == 0) { // dziecko
        close(fd[1]);
        close(fd1[0]);
        char input[20];
        read(fd[0], input, sizeof(input));
        printf("%s",input);
        input[0] = 'H';
        write(fd1[1],input);
    } else { // rodzic
        close(fd[0]);
        close(fd1[1]);
        write(fd[1], "hello world\n");
        char input[20];
        read(fd1[0],input,sizeof(input));
        printf("%s",input);
    }
    return 0;
}