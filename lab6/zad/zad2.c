#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define PIPE "./rura"
#define PIPE_r "./rura1"

double rectangle(double a, double b) {
    return a * b;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        return 1;
    }

    mkfifo(PIPE, 0666);
    mkfifo(PIPE_r,0666);

    int fd = open(PIPE, O_RDWR);
    FILE * file = fopen(PIPE_r,"w");


    double result = 0;
    double width = atof(argv[1]);
    int n = atoi(argv[2]);

    for (int i = 1; i <= n; i++) {
        pid_t child = fork();
        if (child == 0) {
            double actual_width = i * width < 1.0 ? width : 1.0 - (i-1) * width;
            double x = ((i-1) * width * 2.0 + actual_width) / 2.0;
            double value = rectangle(actual_width, 4 / (x * x + 1));
            write(fd, &value, sizeof(double));
            exit(0);
        }
        else {
            double curr_res;
            read(fd,&curr_res,sizeof(double));
            result += curr_res;
        }
    }
    putw(result,file);
    fclose(file);
    close(fd);
    return 0;
}
