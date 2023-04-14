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

    if (signal(SIGINT, sig_handler) == SIG_ERR) {
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