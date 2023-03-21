#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void star(int numstar) {
    char star = '*';

    if (numstar < 0) {
        numstar = -numstar;
        star = '@';
    }

    if (numstar >= 100)
        exit(1);

    char line[100];

    line[numstar] = 0;

    while (0 <= --numstar)
        line[numstar] = star;

    printf("%s\n", line);
}

void supernova(int sig) {
    int wstatus;
    while (waitpid(-1, &wstatus, WNOHANG) > 0)
        for (int i = WEXITSTATUS(wstatus); i > 0; i--)
            star(-i);
}

void setup_supernova(int sa_restart) {
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sigemptyset(&sa.sa_mask);
    sa.sa_handler = supernova;
    if (sa_restart)
        sa.sa_flags = SA_RESTART;
    sigaction(SIGCHLD, &sa, NULL);
}

int main(int argc, char **argv)
{
    assert(argc == 2);
    int n = atoi(argv[1]);

#ifdef S8
    setup_supernova(1);
#endif

#ifdef S9
    setup_supernova(0);
#endif

    for (int i = 1; i <= n; i++) {

        // You can enable each code block below by defining S1, S2, etc.
        // at the preprocessing stage using -D option in gcc. For example:
        //
        //     gcc -Wall -g -D S1 starfork.c && ./a.out 3
        //
        // will run the program with the code in S1 block.

#ifdef S1
        star(i);
#endif

#ifdef S2
        star(i);
        fork();
#endif

#ifdef S3
        star(i);
        fork();
        star(i);
#endif

#ifdef S4
        star(i);
        pid_t pid = fork();
        if (pid == 0) { // Child process
            star(i);
            exit(0);
        }
        waitpid(pid, NULL, 0); // No status, no options
#endif

#ifdef S5
        star(i);
        pid_t pid = fork();
        if (pid > 0) { // Parent process
            waitpid(pid, NULL, 0); // No status, no options
            star(i);
            exit(0);
        }
#endif

#ifdef S6
        star(i);
        sleep(1);
        char *a[] = { argv[0], argv[1], NULL };
        execv(*a, a);
        printf("%s\n", "A STAR IS BORN");
        exit(0);
#endif

#ifdef S7
        star(n);
        pid_t pid = fork();
        if (pid == 0) { // Child process
            char buf[100];
            sprintf(buf, "%d", 2 * n);
            char *a[] = { argv[0], buf, NULL };
            execv(*a, a);
        }
        waitpid(pid, NULL, 0); // no status, no options
        star(n);
        exit(0);
#endif

#ifdef S8
        star(i);
        pid_t pid = fork();
        if (pid == 0) // Child process
            exit(i);

        char c;
        read(0, &c, sizeof(char)); // Block until we can read a byte from stdin
                                   // (fd=0)
#endif

#ifdef S9
        star(i);
        pid_t pid = fork();
        if (pid == 0) // Child process
            exit(i);

        char c;
        read(0, &c, sizeof(char)); // Block until we can read a byte from stdin
                                   // (fd=0), or we are interrupted by a signal
#endif
    }
}

