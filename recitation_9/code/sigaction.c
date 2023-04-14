#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sig_handler(int signum) {
    printf("starting handler\n");
    sleep(3);
    /* some important code */
    printf("signal handled\n");
}

int main() {

    struct sigaction sa;
    sa.sa_handler = sig_handler;
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGQUIT);

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        fprintf(stderr, "failed sigaction\n");
	    return 1;
    }

    while (1) {
        sleep(1);
    }
}