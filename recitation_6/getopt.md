# getopt #

The `getopt()` function is a standard library function in C that is used to parse command line arguments. It is typically used in C programs that take command line arguments to specify options or flags. It has a similar purpose and functionality to the `getopts` command line utility, that was used in HW1's shell script. The usage looks slightly different than it does in bash since a C program takes command line arguments differently than a shell script does.

The `getopt()` function takes the following parameters:

```c
int getopt(int argc, char *const argv[], const char *optstring);
```

- `argc`: The number of arguments passed to the program, including the name of the program itself.
- `argv`: An array of strings containing the arguments passed to the program.
- `optstring`: A string that specifies the options that the program accepts. Each character in the string represents a single option, and the character may be followed by a colon (:) if the option requires an argument.

The getopt() function returns the next option character from the optstring parameter. If there are no more options to process, it returns -1. It also updates the optind variable, which keeps track of the current index in the argv array.

A simple example:

```c
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int opt;
    opterr = 0;
    while ((opt = getopt(argc, argv, "abc:")) != -1) {
        switch (opt) {
        case 'a':
            printf("Option a was specified\n");
            break;
        case 'b':
            printf("Option b was specified\n");
            break;
        case 'c':
            printf("Option c was specified with argument %s\n", optarg);
            break;
        case '?':
            printf("Unknown option %c\n", optopt);
            break;
        default:
            break;
        }
    }

    return 0;
}
```

Notice a few things in this example. We never define a `optarg` variable, yet we are able to use it. This is because `getopt` maintains a few global variables:
- `optind`: This variable keeps track of the current index in the argv array. It is initialized to 1 by default, and is updated by `getopt()` as it processes options.
- `optarg`: This variable points to the argument for the current option, if the option requires an argument. It is set by `getopt()` when it processes an option that requires an argument.
- `optopt`: This variable holds the last option character that was processed by getopt(). It is also used to indicate an error when an unknown option is encountered.

You can read more about getopt on the man page at `man getopt`.
