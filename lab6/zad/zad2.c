#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

double rectangle(double a, double b) {
    return a * b;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <width> <n>\n", argv[0]);
        return 1;
    }

    mkfifo("./rura", 0666);
    int fd = open("./rura", O_RDWR);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    double result = 0;
    double width = atof(argv[1]);
    int n = atoi(argv[2]);

    for (int i = 1; i <= n; i++) {
        pid_t child = fork();
        if (child == -1) {
            perror("fork");
            return 1;
        } else if (child == 0) {
            double actual_width = i * width < 1.0 ? width : 1.0 - (i - 1) * width;
            double x = ((i - 1) * width * 2.0 + actual_width) / 2.0;
            double value = rectangle(actual_width, 4 / (x * x + 1));
            if (write(fd, &value, sizeof(double)) == -1) {
                perror("write");
                return 1;
            }
            exit(0);
        } else {
            double curr_res;
            if (read(fd, &curr_res, sizeof(double)) == -1) {
                perror("read");
                return 1;
            }
            result += curr_res;
        }
    }
    close(fd);
    remove("./rura");
    FILE * file = fopen("./p", "wb");
    fwrite(&result,sizeof(double), 1, file);
    fclose(file);
    return 0;
}
