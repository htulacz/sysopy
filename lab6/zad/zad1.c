#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define PIPE_r "./rura1"

double rectangle(double a, double b) {
    return a * b;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        return 1;
    }

    FILE * file = fopen(PIPE_r, "r");
    int toParent[2];
    pipe(toParent);
    double result = 0;
    double width = atof(argv[1]);
    int n = atoi(argv[2]);

    for (int i = 1; i <= n; i++) {
        pid_t child = fork();
        if (child == 0) {
            close(toParent[0]);
            double actual_width = i * width < 1.0 ? width : 1.0 - (i-1) * width;
            double x = ((i-1) * width * 2.0 + actual_width) / 2.0;
            double value = rectangle(actual_width, 4 / (x * x + 1));
            write(toParent[1], &value, sizeof(value));
            close(toParent[1]);
            exit(0);
        }
    }

    close(toParent[1]);

    for (int i = 0; i < n; i++) {
        double curr_res;
        read(toParent[0], &curr_res, sizeof(double));
        result += curr_res;
    }
    double result_named = getw(file);
    fclose(file);
    remove(PIPE_r);
    printf("Basic Pipe: %f  Named Pipe: %f\n", result, result_named);
    return 0;
}
