#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void sigint_handler(int sig) {
    printf("Caught signal %d\n", sig);
    exit(0);
}

int main() {
    signal(SIGINT, sigint_handler);

    while(1) {
        // do something
    }

    return 0;
}