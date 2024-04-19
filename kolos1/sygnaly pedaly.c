#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int fd[2];
/*program tworzy dwa procesy potomne. Proces macierzysty co sekund� wysy�a
SIGUSR1 do procesu potomnego 1. Proces potomny 1 po otrzymaniu sygna�u przesy�a
kolejn� liczb� przez potok nienazwany do procesu potomnego 2, kt�ry wyswietla
te liczbe */

//

int count = 0;
void handle (int id) {
    char * buf[1];
    sprintf(buf, "%d", count);
    count++;
    write(fd[1], buf, 1);
}

//
int main (int lpar, char *tab[]){
    pid_t pid1, pid2;
    int d,i;
    int res = pipe(fd);

    if (res == -1){
        return 1;
    }
    //
    //
    pid1 = fork();
    if (pid1 < 0){
        perror("fork1");
        return 1;
    } else if (pid1 == 0){
        close(fd[0]);
        signal(SIGUSR1, handle);
        while (1){
            pause();
        }
        return 0;
    }
    pid2 = fork();
    if (pid2 < 0){
        perror("fork2");
        return 1;
    } else if (pid2 == 0){
        close(fd[1]);
        while(1){
            char buf[1];
            int d = read(fd[0], buf, sizeof(buf));
            if (d > 0){
                int i = atoi(buf[0]);
                printf("%d", i);
            }
        }
    }

    close(fd[0]);
    close(fd[1]);
    while(1){
        kill(pid1, SIGUSR1);
        sleep(1);
    }
    return 0;
}