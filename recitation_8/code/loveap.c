#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

volatile int sig_num = 0;

void sig_handler(int signum){
   sig_num = signum; 
}

int main()
{
    struct sigaction sa;
    sigemptyset (&sa.sa_mask);
    sa.sa_handler = sig_handler;
    sa.sa_flags = 0;
    
    for(int i=1; i< 65; i++){
		if(i == 9 || i == 19 || i == 32 || i == 33)
			continue;

		if (sigaction(i, &sa, NULL) == -1) {
			fprintf(stderr, "failed sigaction %d\n", i);
			return 1;
		}
    }

    while(1){
		if (sig_num) {
			printf("The signum is %d\n", sig_num);
			sig_num = 0;
		} else {
			printf("I ♥ AP\n");
		}
		sleep(1);
	}
    
	return 0;
}
