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

    if (signal(SIGINT, sig_handler) == SIG_ERR) {
        fprintf(stderr, "failed sigaction\n");
	    return 1;
    }

    while (1) {
        sleep(1);
    }
}