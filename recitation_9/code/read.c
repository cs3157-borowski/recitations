#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

void sig_handler(int signum) {
    printf("signal handled\n");
}

char buf[256];

int main() {

    if (signal(SIGINT, sig_handler) == SIG_ERR) {
        fprintf(stderr, "failed signal\n");
	    return 1;
    }
    
    int count = read(STDIN_FILENO, buf, 256);
    if (count > 0) {
        write(STDOUT_FILENO, buf, count);
    }
    
}