#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

void reverse(char array[], int length) {
    for (int i = 0; i < length / 2; i++) {
        char temp = array[i];
        array[i] = array[length - i - 1];
        array[length - i - 1] = temp;
    }
}

int main() {
    char buffer[1024];
    int source, outcome;
    int counter;
    source = open("s", O_RDONLY);
    outcome = open("o", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    off_t p = lseek(source, -1024, SEEK_END);
    while ((counter = read(source, buffer, sizeof(buffer))) > 0) {
        reverse(buffer, counter);
        write(outcome, buffer, counter);
        p = lseek(source, p, SEEK_SET);
        p -= 1024;
    }

    close(source);
    close(outcome);
    return 0;
}
