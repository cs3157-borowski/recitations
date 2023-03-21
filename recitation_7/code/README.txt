Starfork
--------

Part 1
------

Running starfork <N> prints lines of *s until printing N *s; e.g.:

    $ ./starfork-s1 5
    *
    **
    ***
    ****
    *****

Part 2
------

Running starfork <N> will print 1 line with 1 *, 2 lines with 2 *s, 4 lines with
3 *s, etc. i.e., 2^i lines of i *s for i <= N.

starfork 1 and starfork 2 are predictable:

    $ ./starfork-s2 1
    *

    $ ./starfork-s2 2
    *
    **
    **

However, the output starts to become unpredictable starting from starfork 3,
because the grandchildren printing 3 *s are not synchronized with their uncles
printing 2 *s.  Thus the following outputs are possible:

    *
    **
    **
    ***
    ***
    ***
    ***

and
    *
    **
    ***
    **
    ***
    ***
    ***

But since a line with 3 *s must be preceded by a line with 2 *s, the following
output is impossible:

    *
    ***
    **
    ***
    **
    ***
    ***


Part 3
------

Each line with i *s is printed 2^(i-1) + 2^i times; for example, there are
3 lines with 1 *, 6 lines with 2 *s, etc.

The output is unpredictable starting from starfork <N> where N > 1.


Part 4
------

This program will just behave like starfork from Part 1, except it will print
two lines of each number of stars instead of one, e.g.:

    $ ./starfork-s4 4
    *
    *
    **
    **
    ***
    ***
    ****
    ****

The fork() and waitpid() pattern makes it equivalent to simply replacing mod
block with:

    star(i);
    star(i);


Part 5
------

This program will print a pyramid of *s, like this:

    $ ./starfork-s5 4
    *
    **
    ***
    ****
    ****
    ***
    **
    *

After each fork(), the parent will waitpid() for its child to terminate;
meanwhile the child will continue to the next iteration, and print more stars
before waiting for its child.  After a child unblocks, the parent prints out the
same number of stars it first printed, and then exit()s.


Part 6
------

This program will print a lines with a single * at a time, one second at a time,
forever.  It will look something like this:

    $ ./starfork-s6 5
    *
    *
    *
    (( etc. ))

When it exec()s itself, the newly executed instance of the program will restart
from the first loop iteration, printing 1 * and exec()ing again.  It doesn't
matter what command line argument this program is executed with (as long as its
a number), and "A STAR IS BORN" is never printed.


Part 7
------

This program will also create a pyramid, except the number of *s in each line
doubles rather than just increasing by 1, until reaching 100 *s.

No process actually enters the loop more than once; the child exec()s to become
a new instance of the program, while the parent exit()s before going to the next
loop iteration.


Part 8
------

This program will print something like:

    $ ./starfork-s7 4
    *
    @

    **
    @@
    @

    ***
    @@@
    @@
    @

    ****
    @@@@
    @@@
    @@
    @

The cascading @s are printed by the SIGCHLD handler after it reaps its
terminated child.

Note the blank lines in between the output aren't printed by the program, but
added there when I typed enter to unblock read().

If I type in extra characters before pressing enter, the parent will run for
several consecutive loop iterations without blocking on read(), leading to
unpredictable output.


Part 9
------

In part 8, we used SA_RESTART to ensure that the read() system call is
"restarted" after the parent receives a signal, meaning the parent will resume
blocking on read() after handling SIGCHLD.  If we don't specify SA_RESTART, the
parent will only block on read() until the child terminates, at which point it
will execute its signal handler, then immediately resume execution after read()
without waiting for any input.


Acknowledgement
---------------

This exercises was originally created by Prof. Jae Lee and John Hui for this
course. They were modified by Stanley Lin in Spring 2023.
