#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

void sig_handler(int signum) {
    printf("interrupt handled\n");
}

char buf[256];
int iteration = 0;

int main() {

    if (signal(SIGINT, sig_handler) == SIG_ERR) {
        fprintf(stderr, "failed sigaction\n");
	    return 1;
    }

    while (1) {
        int count = read(STDIN_FILENO, buf, 256);
        iteration++;
        printf("iteration: %d\n", iteration);
    }
    
}