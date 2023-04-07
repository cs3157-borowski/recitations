# **Signal**

In this example, we will study the `starfork` program. You can obtain the code in the `code` directory in the same repo.

When you run `make` in here, it will build seven different version of starfork, named `starfork-s1` through `starfork-s7`. You should try to first predict the output of each part before running the executable to validate (or disprove) your hypothesis. Keep in mind that some of these parts are actually unpredictable, so you may need to run them multiple times to see different behavior.

## Part 1

For starters, let’s make sure you understand the skeleton code:

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static void exit_report(void) {
    fprintf(stderr, "Process [%d] finished.\n", getpid());
}

void star(int numstar) {
    if (numstar >= 100)
        exit(EXIT_FAILURE);

    char star = '*';

    if (numstar < 0) {
        numstar = -numstar;
        star = '@';
    }

    char line[100];

    line[numstar] = 0;

    while (0 <= --numstar)
        line[numstar] = star;

    printf("%s\n", line);
}

int main(int argc, char **argv) 
{
    assert(argc == 2);
    int n = atoi(argv[1]);

    if (atexit(exit_report) != 0)
        perror("Can't register exit function");

    for (int i = 1; i <= n; i++) {
        // BEGIN MOD BLOCK

        star(i);

        // END MOD BLOCK
    }
}
```
How does this code behave? How many arguments does this program expect, and what do those arguments do?  
When will the `exit_report` function be invoked? How many times will its content be printed?

In subsequent parts, we will modify the “mod block”, the portion of the code between `// BEGIN MOD BLOCK` and `// END MOD BLOCK`.

## Part 2

Change the main function to:
```c
int main(int argc, char **argv) 
{
    assert(argc == 2);
    int n = atoi(argv[1]);

    if (atexit(exit_report) != 0)
        perror("Can't register exit function");

    for (int i = 1; i <= n; i++) {
        star(i);
        fork();
    }
}
```
Run it with different command line arguments, `1`, `2`, `3`, etc.

- Can you predict the output of stars? How many lines are printed, and how many stars are printed? 
- How many times will the "Process xxx finished." be printed?
- Is the output of stars always the same? And if not, are there any kinds of patterns you can find among possible outputs?
- Is the following output possible:
```
*
**
***
**
***
***
***
```
- What about this output:
```
*
***
**
***
**
***
***
```
- Sometimes you’ll see output that looks like this:
```
$ ./starfork-s2 3
*
**
**
***
$ ***
***
***
```
Note that stars were printed even after the shell prompt `$` was shown. Why might this happen? (Hint: what is the parent process of `starfork`?)

> Note that while the exit function can help us understand how many processes are being used, in order to deepen our understanding of `fork` and `exec`, we will only consider the `stdout` output in the later sections (i.e., attaching `2>/dev/null` in your command when running them.)

## Part 3

What about the following modification?
```c
int main(int argc, char **argv) 
{
    assert(argc == 2);
    int n = atoi(argv[1]);

    for (int i = 1; i <= n; i++) {
        star(i);
        fork();
        star(i);
    }
}
```
- Try to predict the output with command line argument `1`; identify which process prints each line.
- What about with arguments `2` or `3`? Are they predictable?

## Part 4
Let’s add some synchronization by having the parent process wait for its child. What would be the output if you change the main function to the following?
```c
int main(int argc, char **argv) 
{
    assert(argc == 2);
    int n = atoi(argv[1]);

    for (int i = 1; i <= n; i++) {
        star(i);
        pid_t pid = fork();
        if (pid == 0) { // Child process
            star(i);
            exit(EXIT_SUCCESS);
        }
        waitpid(pid, NULL, 0); // No status, no options
    }
}
```
- Is the output predictable?
- Could you rewrite this modification block to produce the same output, without using `fork()` and `waitpid()`?

## Part 5

Now what about this version?
```c
int main(int argc, char **argv) 
{
    assert(argc == 2);
    int n = atoi(argv[1]);

    for (int i = 1; i <= n; i++) {
        star(i);
        pid_t pid = fork();
        if (pid > 0) { // Parent process
            waitpid(pid, NULL, 0); // No status, no options
            star(i);
            exit(EXIT_SUCCESS);
        }
    }
}
```
- Is the output predictable?
- Explain the output of this program using a fork diagram or process tree. Which process prints each line?

## Part 6

Now let’s understand what `exec()` does. How would the following block behave?
```c
int main(int argc, char **argv) 
{
    assert(argc == 2);
    int n = atoi(argv[1]);

    for (int i = 1; i <= n; i++) {
        star(i);
        sleep(1);
        char *a[] = { argv[0], argv[1], NULL };
        execv(*a, a);
        printf("%s\n", "A STAR IS BORN");
        exit(EXIT_SUCCESS);
    }
}
```
- Is `A STAR IS BORN` ever printed?
- Are any new processes ever created?
- How does the command line argument affect the behavior of the program, if at all?

## Part 7

Now let’s see if you really understood `exec()`. What would be the output for the following block when you run `starfork` with arguments `2`, `10`, and `50`?
```c
int main(int argc, char **argv) 
{
    assert(argc == 2);
    int n = atoi(argv[1]);

    for (int i = 1; i <= n; i++) {
        star(n);
        pid_t pid = fork();
        if (pid == 0) { // Child process
            char buf[100];
            sprintf(buf, "%d", 2 * n);
            char *a[] = { argv[0], buf, NULL };
            execv(*a, a);
        }
        waitpid(pid, NULL, 0); // No status, no options
        star(n);
        exit(EXIT_SUCCESS);
    }
}
```
Some hints and guiding questions:

- How many loop iterations does each process execute?
- Note that we call `star()` with `n` instead of `i`!
- Try to justify your explanation with a fork diagram; when `starfork` executes itself, make a note of what argument it is called with.


# Modern Family

Is the output of this program predictable? Why or why not?
Try to predict the output before you run the program.

## modern_family.c
```c
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i;
    pid_t p;

    p = fork();

    if (p > 0) {
        for (i = 0; i < 10; i++) {
            printf("Listen to me\n");
            sleep(1);
        }
        printf("I give up...\n");
        return 0;
    }
    else if (p == 0) {
        for (i = 0; i < 10; i++) {
            printf("No way\n");
            sleep(1);
        }
        printf("Whatever.\n");
        return 1;
    }
    else {
        perror("fork failed");
        return -1;
    }
}
```
What is the effect of removing the sleep statements in the parent and child processes on the program's output?
Will the program's output change? Why or why not?

## Acknowledgements

Parts of this note and exercises were originally created by Prof. Jae Lee and John Hui for this course. They were modified by Stanley Lin, Alex Xu and Noam Zaid in Spring 2023.
