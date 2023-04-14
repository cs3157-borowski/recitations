#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

void sig_handler(int signum) {
    printf("interrupt handled\n");
}

int main() {
    struct sigaction sa;
    sa.sa_handler = sig_handler;
    /* automatically restarts slow system call */
    sa.sa_flags = SA_RESTART;

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        fprintf(stderr, "failed sigaction\n");
	    return 1;
    }

    printf("PID: %d\n", getpid());

    pid_t pid = fork();

    if (pid == 0) {
        sleep(1000);
    } else if (pid > 0) {
        wait(NULL);
    }
}