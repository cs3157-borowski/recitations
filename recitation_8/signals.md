# **Signals**

## Overview

A signal is a notification of an event that gains the attention of the OS.
They can be hardware, OS generated, or triggered by other processes.
When a process receives a signal, control is passed to the signal handler, which then executes.
After the signal handler terminates, it returns to the next instruction.

## Signal Handlers

When a signal is received, the process will execute the default signal handler.
However, a process can change the disposition of a signal using
`signal()` or `sigaction()`. 

``` c
/* returns the old signal handler on success, SIG_ERR on error*/
sighandler_t signal(int signum, sighandler_t handler);
```

```c
/* returns 0 on success, -1 on error */
int sigaction(int signum, const struct sigaction *restrict act,
                struct sigaction *restrict oldact);
```

Usually we would use `sigaction` for a couple of reasons:
- `signal()` does not block other signals from arriving. Therefore,
if another signal can arrive during the execution of the signal handler. 
`sigaction()` blocks other signals until the signal handler finishes 
executing.
- `signal()` usually resets signal action back to `SIG_DFL`
so the signal handler must reinstall itself as its first action.
Therefore, the default action may be execution if the signal arrives 
in between signal detection and handler reinstallation.
- `signal()` may not automatically restart "slow" system calls.

Suppose we had a critical section of code that we want to execute on a 3 second delay every time we receive `SIGINT`. 
This can be implemented as follows.

``` c
void sig_handler(int signum) {
    printf("starting handler\n");
    sleep(3);
    /* some important code */
    printf("interrupt handled\n");
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
```

Whenever `SIGINT` is received, the body of sig_handler will begin to execute.

*Note: in the following example shell sessions, ^C denotes SIGINT
being sent from the keyboard and ^\ denotes SIGQUIT being sent from
the keyboard*

``` bash
$ ./a.out
^Cstarting handler
interrupt handled
```

However, consider what happens if we send `SIGINT` immediately followed by `SIGQUIT`.

``` bash 
$ ./a.out
^Cstarting handler
^\Quit: 3
$
```

Once `SIGINT` is received, the signal handler begins executing.
However, `SIGQUIT` is received before the signal handler finishes
executing so the program terminates prematurely.

In order to ensure that the signal handler executes to completion,
we must use `sigaction()`.

``` c
void sig_handler(int signum) {
    printf("starting handler\n");
    sleep(3);
    /* some important code */
    printf("interrupt handled\n");
}

int main() {

    struct sigaction sa;
    sa.sa_handler = sig_handler;

    /* sets up the mask to block SIGQUIT */
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
```

Now, we observe what happens if we send `SIGINT` immediately followed by `SIGQUIT`.

``` bash 
$ ./a.out
^Cstarting handler
^\interrupt handled
Quit: 3
$
```

As before, the `SIGINT` is received and the handler begins to execute.
However, when `SIGQUIT` is received, it is blocked because we have
added it to the mask. When the handler finishes executing, the 
default handler for `SIGQUIT` executes, which is program termination
in this case.

Note that this code block only blocks `SIGQUIT` from causing premature
termination. Any other signals could still terminate the program
before the signal handler finishes executing.

In order to abstract this code to block other signals, you can change

``` c 
sigemptyset(&sa.sa_mask);
sigaddset(&sa.sa_mask, SIGQUIT);
```

to 

``` c
sigfillset(&sa.sa_mask);
```

***IMPORTANT: SIGKILL and SIGSTOP cannot be blocked, so if the these
signals are delivered, the program will execute their default handlers***

Another problem with signal that we will cover is portability across
systems. In particular, we will look at system call restarts. In
the standard, there is no convention for how `signal()` should be
behave when a signal is received when a blocking system call is
running.

Suppose we wanted to read one line from stdin and then write to stdout,
and ignore any `SIGINT`. With `signal()` this could be implemented as follows.

``` c

void sig_handler(int signum) {
    printf("interrupt handled\n");
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
```

However, if we run this on different machines, we could see different behavior. 
On some machines this could be equivalent to the following code.

``` c
void sig_handler(int signum) {
    printf("interrupt handled\n");
}

char buf[256];

int main() {

    struct sigaction sa;
    sa.sa_handler = sig_handler;

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        fprintf(stderr, "failed sigaction\n");
	    return 1;
    }
    
    int count = read(STDIN_FILENO, buf, 256);
    if (count > 0) {
        write(STDOUT_FILENO, buf, count);
    }
    
}
```

Observe the following shell session running this code.

``` bash
$ ./a.out
^C interrupt handled
$
```

The signal is handled which causes `read` to fail. However,
this call never restarts so this code does not work as intended.

On other machines, such as Linux, the first block of code would be equivalent to the following.

``` c
void sig_handler(int signum) {
    printf("interrupt handled\n");
}

char buf[256];

int main() {

    struct sigaction sa;
    sa.sa_handler = sig_handler;
    /* automatically restarts slow system call */
    sa.sa_flags = SA_RESTART;

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        fprintf(stderr, "failed sigaction\n");
	    return 1;
    }

    int count = read(STDIN_FILENO, buf, 256);
    if (count > 0) {
        write(STDOUT_FILENO, buf, count);
    }
    
}
```

We can then run the following shell session.

``` bash
$ ./a.out
^Cinterrupt handled
^Cinterrupt handled
^Cinterrupt handled
hello
hello
$
```
