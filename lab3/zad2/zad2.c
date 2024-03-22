#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    long long total_size = 0;

    dir = opendir(".");

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        if (stat(entry->d_name, &file_stat) == -1) {
            continue;
        }

        if (!S_ISDIR(file_stat.st_mode)) {
            printf("Nazwa: %s, Rozmiar: %lld bytes\n", entry->d_name, (long long)file_stat.st_size);
            total_size += file_stat.st_size;
        }
    }

    closedir(dir);

    printf("Sumaryczny rozmiar wszystkich plików: %lld bytes\n", total_size);

    return 0;
}
