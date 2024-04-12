// sender.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

#define NUM_SIGNALS 3

// Funkcja wysyłająca sygnał SIGUSR1 do catcher
void send_signal(pid_t catcher_pid, int mode) {
    union sigval sv;
    sv.sival_int = mode;
    sigqueue(catcher_pid, SIGUSR1, sv);
}

int main(int argc, char *argv[]) {
    // Sprawdzenie poprawności liczby argumentów
    if (argc != 3) {
        printf("Usage: %s <catcher_pid> <mode>\n", argv[0]);
        exit(1);
    }

    // Pobranie PID catcher z argumentu linii poleceń
    pid_t catcher_pid = atoi(argv[1]);
    // Pobranie trybu pracy z argumentu linii poleceń
    int mode = atoi(argv[2]);

    // Weryfikacja poprawności trybu pracy
    if (mode < 1 || mode > 3) {
        printf("Invalid mode. Mode must be between 1 and 3\n");
        exit(1);
    }

    // Wysłanie sygnałów do catcher z odpowiednim trybem pracy
    for (int i = 0; i < NUM_SIGNALS; ++i) {
        send_signal(catcher_pid, mode);
        // Oczekiwanie na potwierdzenie odebrania sygnału przez catcher
        pause();
    }

    return 0;
}
