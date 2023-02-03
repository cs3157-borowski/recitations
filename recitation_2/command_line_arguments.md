# **Command Line Arguments**


Command line arguments are passed to main() as an array of char pointers.
When we define main() as:

    int main(int argc, char **argv) { ... }

instead of:

    int main(void) { ... }

we can access the command line arguments through argc ("argument count") and
argv ("argument vector").

argc is an integer that represents the number of arguments passed to the program
from the command line, including the name of the executable.

For example, when you run:

    echo hello world

the following data structure is passed to the main() of the echo program:

    argv -----> +---------------+       +---+---+---+---+---+
                |       --------|-----> |'e'|'c'|'h'|'o'| 0 |
                +---------------+       +---+---+---+---+---+---+
                |       --------|-----> |'h'|'e'|'l'|'l'|'o'| 0 |
                +---------------+       +---+---+---+---+---+---+
                |       --------|-----> |'w'|'o'|'r'|'l'|'d'| 0 |
                +---------------+       +---+---+---+---+---+---+
                |    0 (NULL)   |
                +---------------+

argc is set to 3, and argv[argc] is set to NULL (as illustrated).
Note that for the array of pointers, argv, we use a NULL pointer as a null
terminator for pointer array; for the array of chars, i.e., each of the argument
strings, we use a null character '\0' as a null terminator for each string.

Here's three different ways to implement the 'echo' program (K&R2, p115):

    for (i = 1; i < argc; i++)
        printf("%s\n", argv[i]);

    while (--argc > 0)
        printf("%s\n", *++argv;);

    argv++;
    while (*argv)
        printf("%s\n", *argv++);
        
        
Consider the following sample run and the different versions on main,
try to predict the output of main():

    $./main Welcome to AP!

After each version of main() write down the output of the program:

`You may assume that each main contains #include <stdio.h>`

-

    int main(int argc, char **argv)
    {
        for (int i = 0 ; i < argc ; i++)
            printf("%s\n",argv[i]);
        return 0;
    }
    
-

    int main(int argc, char **argv)
    {
        for (int i = 0 ; i < argc ; i++)
            printf("%c\n",argv[i][0]);
        return 0;
    }

-

    int main(int argc, char** argv)
    {
    printf("%s\n",*argv);
    printf("%s\n",argv[1]);
    printf("%ld\n",sizeof(argv));
    printf("%ld\n",sizeof(*argv));
    printf("%ld\n",sizeof(*argv[1]));
    printf("%ld\n",sizeof(argc));
    
    return 0;
    }
    
    
Answers:

1.

    ./a.out
    Welcome
    to
    AP!

2.

    
    .
    W
    t
    A
    
    
3.

    ./a.out
    Welcome
    8
    8
    1
    4
