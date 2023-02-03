# Compilation and Makefiles

### Separate Compilation
Suppose we want to build an executable, `myprogram`, which comprises of:

`myprogram.c`:

```c
#include <stdio.h>
#include <stdlib.h>
#include "hello.h"
#include "goodbye.h"

int main(int argc, char **argv)
{
    printf("This is my program!\n");
    hello(argv[1]);
    goodbye(argv[1]);
    return EXIT_SUCCESS;
}

```

which takes the first command line argument, passes it to the `hello()` and `goodbye()` functions which print to the terminal. `hello()` and `goodbye()` are each defined in their respective `.c` files:

`hello.c`:

```c
#include <stdio.h>
#include "hello.h"

void hello(char *s)
{
    printf("Hello, %s!\n", s);
}

```

`goodbye.c`:

```c
#include <stdio.h>
#include "goodbye.h"

void goodbye(char *s)
{
    printf("Goodbye, %s!\n", s);
}

```

Because `hello()` and `goodbye()` are not defined in `myprogram.c`, we need to include their respective header files in `myprogram.c`  to let our program know that they are defined elsewhere:

`hello.h`:

```c
#ifndef _HELLO_H_
#define _HELLO_H_

void hello(char *s);

#endif

```

`goodbye.h`:

```c
#ifndef _GOODBYE_H_
#define _GOODBYE_H_

void goodbye(char *s);

#endif

```

- Once the header is included, it checks if a unique value (in this case `_GOODBYE_H_`) is defined. Then if it's not defined, it defines it and continues. If the code is included again, the first `ifndef` fails, resulting in a blank file. This is called an include guard and prevents double declarations.

### Compiling

```bash
$ ls
goodbye.c       goodbye.h       hello.c         hello.h         myprogram.c
```

The `.c` files need to be compiled into object files (`.o` files).

We can do this by using the `gcc -c` command.

```bash
$ gcc -c -o hello.o hello.c 
$ gcc -c -o goodbye.o goodbye.c 
$ gcc -c -o myprogram.o myprogram.c 
```

- `gcc` is the C compiler that we use
- `-c` specifies that we want to compile
- `-o <filename>.o` specifies that we want the output (the object file) to be named `<filename>.o`
  - The `.o` file should have the same name as the `.c` file
- `<filename>.c` is the `.c` file that we want to compile

Format: `gcc -c -o <output name> <ingredients>`

Now, we have the object files:

```bash
$ ls
goodbye.c       goodbye.o       hello.h         myprogram.c
goodbye.h       hello.c         hello.o         myprogram.o
```

- `gcc -c` will pre-process (ie. including the headers), compile, and assemble the files; taking in a `.c` file and outputing a `.o` file.

### Linking

Now, we need to link the `.o` files to create our executable.

To link:

```bash
$ gcc -o myprogram hello.o goodbye.o myprogram.o
```

Format: `gcc -o <output name> <ingredients>`

Now we have our executable, `myprogram`:

```bash
$ ls
goodbye.c       goodbye.o       hello.h         myprogram       myprogram.o
goodbye.h       hello.c         hello.o         myprogram.c
```

```bash
$ ./myprogram Faustina
This is my program!
Hello, Faustina! 
Goodbye, Faustina!
```

### Makefile

This process to produce our executable required many steps. We can streamline it by creating a `Makefile`, which gives us a simple way to organize code compilation.

Because `hello.o` is produced by including `hello.h` and compiling `hello.c`, we can say that `hello.o` depends on `hello.c` and `hello.h`. Similarly, `myprogram` is produced by linking `hello.o`, `goodbye.o`, and `myprogram.o`, so we say that `myprogram` depends on these object files.

We should only need to rebuild something if at least one of the files it depends on has changed. After all, part of the reason for separate compilation is to avoid the cost of rebuilding things we do not need to rebuild.

Make is a build system that helps us manage incremental builds. You can find its manual online here: https://www.gnu.org/software/make/manual/make.html.

Make runs commands for you according to instructions specified in a Makefile. For example, it can help you run any of the GCC build commands shown before. A `Makefile` should specify one of more “rules” for building files; each rule looks like this:

```bash
myprogram: hello.o goodbye.o myprogram.o
	gcc -o myprogram hello.o goodbye.o myprogram.o
```

where:

- `myprogram` is the name of the target file this rule will build
- `hello.o`, `goodbye.o`, `myprogram.o` are the dependencies (prerequisites) that the target depends on
- `gcc -o myprogram hello.o goodbye.o myprogram.o` is the recipe (ie. the shell command that builds the target)
    - `goodbye.o` and `myprogram.o` are the ingredients for this recipe

Make uses the “last modified” timestamp of each file to figure out if a target needs to be rebuilt. Make will rebuild a target if it doesn’t exist, or if it was last modified earlier than one of its dependencies.

Creating our `Makefile` for `myprogram`:

```bash
myprogram: hello.o goodbye.o myprogram.o
	gcc -o myprogram hello.o goodbye.o myprogram.o

hello.o: hello.c hello.h
	gcc -c -o hello.o hello.c

goodbye.o: goodbye.c goodbye.h
	gcc -c -o goodbye.o goodbye.c

myprogram.o: myprogram.c hello.h goodbye.h
	gcc -c -o myprogram.o myprogram.c
```

Note: The space preceding your recipe needs to be a tab, not spaces.

Note: We include header files in our dependencies in the `Makefile`, but they do not need to be included in the recipe

We can run make according to our Makefile using the command `make`, which will complete all the steps we took above for us.

Starting again with only our `Makefile`, `.c` and `.h` files:

```bash
$ ls
Makefile        goodbye.c       goodbye.h       hello.c         hello.h         myprogram.c
```

```bash
$ make
gcc -c -o hello.o hello.c
gcc -c -o goodbye.o goodbye.c
gcc -c -o myprogram.o myprogram.c
gcc -o myprogram hello.o goodbye.o myprogram.o
```

```bash
$ ls
Makefile        goodbye.h       hello.c         hello.o         myprogram.c
goodbye.c       goodbye.o       hello.h         myprogram       myprogram.o
```



Make includes many useful features that we can make use of in our `Makefile`.

### Macros

If we look at our `Makefile`, we can see that a lot of text entries is repeated (ie. `gcc`, our object files). We can use macros to store these to make our `Makefile` less error-prone and easier to modify for different programs.

- Macro definitions have the form: `NAME = text string`

- Macros are referred to by placing the name in parentheses and preceding it with the `$` sign.

```bash
CC = gcc
TARGET = myprogram
C_FILES = hello.c goodbye.c myprogram.c
OBJS = hello.o goodbye.o myprogram.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

hello.o: hello.c hello.h
	$(CC) -c -o hello.o hello.c

goodbye.o: goodbye.c goodbye.h
	$(CC) -c -o goodbye.o goodbye.c

# target     --------dependencies---------
myprogram.o: myprogram.c hello.h goodbye.h
	$(CC) -c -o myprogram.o myprogram.c
#    recipe     output name  ingredient
```

### And More!

We can further generalize our `Makefile` by using functions, special macros and pattern matching.

**`wildcard` Function:**

Notice that our `C_FILES` are all the `.c` files in our current directory. We can use the `wildcard` function and pattern matching to get these instead. `$(wildcard *.c)` will give us a space-separated list of names of existing files that match the given file name pattern: `*.c`. `*.c` matches all file names that end with `.c`.

- Replace `C_FILES = hello.c goodbye.c myprogram.c` with `C_FILES = $(wildcard *.c)`

**`patsubst` Function:**

`OBJS` are all the `.c` files in our current directory, but with a `.o` extension instead of `.c`. We can use the `patsubst` function and pattern matching instead. `$(patsubst %.c,%.o,$(C_FILES))` takes all the file names in `C_FILES` and replaces `.c` with `.o`.

- Replace `OBJS = hello.o goodbye.o myprogram.o` with `OBJS = $(patsubst %.c,%.o,$(C_FILES))`

**Special Macros:**

For our rules for `.o` targets, the output name of the recipe (what follows the `-o` flag) is always the same as the name of the target and the ingredient is always its corresponding `.c` file, which is the first dependency listed in our rule. We can use special macros to generalize this.

`$@` evaluates to the name of the current target.

`$<` evaluates to the first dependency.

- Replace `$(CC) -c -o <output name> <ingredient>` with `$(CC) $(CFLAGS) -c -o $@ $<`

**`%` (Pattern Matching):**

Our rules for `.o` targets all have dependencies for the corresponding `.c` and `.h` files (with the same file name before the extension). We can generalize this with pattern matching. `%.o: %.c %.h` means for every `.o` file that exists, its dependencies are the `.c` and `.h` files of the same file name (before the file extension).

- Replace `<filename>.o: <filename>.c <filename>.h` with `%.o: %.c %.h`



Altogether, we get this `Makefile`:

```bash
CC      = gcc
TARGET  = myprogram
C_FILES = $(wildcard *.c)
OBJS    = $(patsubst %.c,%.o,$(C_FILES))

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
    
%.o: %.c %.h
	$(CC) -c -o $@ $<
```



However, note that  `myprogram.o` doesn’t depend on `myprogram.h`, as no such file exists. 

So, we can filter out `myprogram.c` from our `C_FILES` with the **`filter-out`** function.

- Replace `C_FILES = $(wildcard *.c)` with `C_FILES = $(filter-out $(TARGET).c, $(wildcard *.c)) `

We then have to compile and link `myprogram.c` with the rest of the object files to produce `myprogram`, so we can change our rule for `myprogram` to:

```bash
$(TARGET): $(OBJS) $(TARGET).c
	$(CC) -o $(TARGET) $(OBJS) $(TARGET).c
```

This works because the command `gcc -o <output name> <ingredients>` will both compile (if needed for `.c` files) and link your ingredients.

Note: For multi-source programs, however, it is not good practice to compile and link all your files in one step because it defeats the purpose of incremental building and individual dependencies cannot be checked. In our `Makefile`, aside from the `.c` file containing the main function, all other `.o` objects are still built separately.

This gives us:

```bash
CC      = gcc
TARGET  = myprogram
C_FILES = $(filter-out $(TARGET).c, $(wildcard *.c)) # filters out myprogram.c
OBJS    = $(patsubst %.c,%.o,$(C_FILES))

$(TARGET): $(OBJS) $(TARGET).c # compiles and links myprogram.c with rest of .o files
	$(CC) -o $(TARGET) $(OBJS) $(TARGET).c
	
%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<
```



**Adding Flags:**

We want to pass compiler flags when we compile to get better debug messages to better catch errors in our code. To this, we use the flags: `-g -Wall -Werror -pedantic-errors`.

To compile `hello.c` separately to `hello.c` with the flags, for example, we would do:

```bash
$ gcc -c -g -Wall -Werror -pedantic-errors -o hello.o hello.c
```

Since our `Makefile` runs shell commands for us, we can save the flags into a macro and put it in the recipe of our rule.

Similarly, we might want to pass flags that enable options for linking.

This gives us:

```bash
CC      = gcc
TARGET  = myprogram
C_FILES = $(filter-out $(TARGET).c, $(wildcard *.c))
OBJS    = $(patsubst %.c,%.o,$(C_FILES))
CFLAGS  = -g -Wall -Werror -pedantic-errors # compiler flags
LDFLAGS = # linker flags

$(TARGET): $(OBJS) $(TARGET).c
	$(CC) -o $(TARGET) $(OBJS) $(TARGET).c $(LDFLAGS) # adding linker flags to recipe
%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $< # adding compiler flags to recipe
```

**`make all` and `make clean`:**

Compiling a program is not the only thing your might want to write rules for. Makefiles commonly provide instructions on a few other things besides compiling a program: 

- To delete all the object files and executables so that the directory is ‘clean’. We can create a rule with the target `clean`, then with a recipe to `rm` the object files and executables that we made.
- An easy-to-read `all` target that is usually the first rule in the `Makefile`. This is helpful because the `make` command will build the first target in your `Makefile` , so having the first target be `all` makes it easy to see what `make` will build.

**Phony Targets:**

- A phony target is one that is not really the name of a file. Rather, it is a target that will be executed unconditionally (even if a file with the same name as the target already exists and is up to date).
- `clean` and `all` are phony targets, so we specify that in our `Makefile` with `.PHONY: all clean`
  - Note: the `.` in front of `.PHONY` means that `make` will not attempt to build the target.

Adding `all` and `clean` to our `Makefile`:

```bash
CC      = gcc
TARGET  = myprogram
C_FILES = $(filter-out $(TARGET).c, $(wildcard *.c))
OBJS    = $(patsubst %.c,%.o,$(C_FILES))
CFLAGS  = -g -Wall -Werror -pedantic-errors
LDFLAGS =

.PHONY: all clean # specifies that all and clean are phony targets

all: $(TARGET) # running make will by default build our executable

$(TARGET): $(OBJS) $(TARGET).c
	$(CC) -o $(TARGET) $(OBJS) $(TARGET).c $(LDFLAGS)
	
%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<
	
clean: # removes object files and our executables
	rm -f $(OBJS) $(TARGET) $(TARGET).exe
	# -f flag silences errors if any of these files do not exist
```



---



# **Bit Operators**

C has two sets of operators that look and behave similarly: logical operators and bitwise operators. They are:

-   `&&` logical AND
-   `||` logical OR
-   `!` logical NOT

and:

-   `&` bitwise AND
-   `|` bitwise OR
-   `~` bitwise NOT
-   `^` bitwise XOR

(Note that there is no logical XOR.)

The difference is that the logical operators only consider whether their operands are zero or non-zero; bitwise operators operate on a per-bit level.

C also includes two bit-shift operators:

-   `<<` bitwise shift left
-   `>>` bitwise shift right

#### Bitwise AND `&`

Takes two integers as operands and returns a new integer where its bit pattern
consists of 1's only where both operands also have 1's in the same position.
For example:

    int x = 5;            // 0101 in binary
    int y = 12;           // 1100 in binary
    assert((x & y) == 4); // 0100 (4)

(Note that `==` has higher precedence than `&`, `|`, `^`, `<<`, and `>>`. See [cppreference](https://en.cppreference.com/w/c/language/operator_precedence).)

This provides a handy way of checking the bit value at a given position,
using a **bitmask**:

    int mask = 0x8;         // 1000 in binary, for checking the 4th bit
    assert(!(x & mask));    // 5 (0101) doesn't contain a 1 in the 4th bit
    assert(y & mask);       // 12 (1100) contains a 1 in the 4th bit

It's called a bitmask because we place 0's in the digits we don't want to read,
which will _mask_ out the corresponding digits via the bitwise AND.

#### Bitwise OR `|`

Behaves just like the bitwise AND, except with an OR operation. Takes two integers as operands and returns a new integer where its bit pattern
consists of 1's where either operand also has a 1 in the same position.
For example:

    int x = 5;              // 0101 in binary
    int y = 12;             // 1100 in binary
    assert((x | y) == 13);  // 1101 (13)

#### Bitwise XOR `^`

Also known as a bitwise eXclusive OR; behaves just like the bitwise AND and OR, except with an XOR operation. Takes two integers as operands and returns a new integer where its bit pattern consists of 1's where only one of its operands has a 1 in the same position.
For example:

    int x = 6;            // 0110 in binary
    int y = 5;            // 0101 in binary
    assert((x ^ y) == 3); // 0011 (3)

#### Bitwise NOT `~`

Also known as a bitwise complement. Takes an integer as operand and returns an integer with all its bits flipped.

    unsigned int x = 5; // 0101 in binary, unsigned
    int y = 5;          // 0101 in binary, signed

    assert(~x == 10);   // 1010 (10, unsigned)
    assert(~y == -6);   // 1010 (-6, signed)

### Bit Shifting

Another useful operation is the bitshift. What we mean by "shifting bits" is pushing all the binary digits in a number. We can shift to the left, or shift to the right.

#### Leftshift `<<`

For `x << n`, each bit in `x` is shifted to the left (towards the Most Significant Bit, MSB) by `n` digits:

-   Left-shifting always fills the vacated bits on the right with 0's
-   The displaced bits beyond the size of the type on the left are discarded (aka. the bits shoved into the pool, see 2/1 lecture)

Note that this is equivalent to multiplying a number by 2^`n`!

    int x = 1;              // 0001 in binary
    assert((x << 2) == 4);  // 0100 (4)

#### Rightshift `>>`

For `x >> n`, each bit in `x` is shifted to the right (towards the Least Significant Bit, LSB) by `n` digits:

-   How the vacated bits get filled depends on what we're dealing with:
    -   Right-shifting unsigned numbers fills vacated bits on the left with 0's
    -   Right-shifting signed numbers produces results that vary
        depending on the machine and compiler, but on most modern computers, doing so will **sign extend** the number, i.e. the value of the MSB (the sign) will be used to pad the vacated bits (See [StackOverflow](https://stackoverflow.com/questions/15729765/sign-extension-with-bitwise-shift-operation))
-   The displaced bits on the right are discarded (aka. the bits shoved into the pool, see 2/1 lecture)

Note that this is equivalent to dividing a number by 2^`n`
(and discarding the remainder)!

    int x = 5;              // 0101 in binary
    assert((x >> 2) == 1);  // 0001 (1)

## Exercises

Without using any arithmetic or comparison operators (e.g., `+`, `-`, `*`, `/`, `%`, `<`, `<=`, `>`, `>=`, `==`, or `!=`), fill in the blanks according to the description. Don't assume `sizeof(int) == 4`; make these methods work for any `int` size!

**Exception:** you may use `-` only to account for off-by-one (e.g., `x - 1` is ok; `x - 32` or `x - n` is not).

1. `mul8(num)` should return `num * 8`:

```
    int mul8(int num) {
        return _______________;
    }
```

2. `make_odd(num)` should return `num` if `num` is odd, and return `num + 1` otherwise:

```
    unsigned int make_odd(unsigned int num) {
        return _______________;
    }
```

3. `is_negative(num)` should return `1` when `num` is negative, and `0` otherwise:

```
    int is_negative(int num) {
        if (_______________)
            return 1;
        else
            return 0;
    }
```

4. `set_bit(num, n, b)` should return `num`, with its `n`-th bit is set to `1` if `b` is non-zero, and set to `0` otherwise (`n` is zero-indexed; `set_bit(0, 0 ,1)` should return `1`):

```
    int set_bit(int num, int n, int b) {
        if (b)
            return _______________;
        else
            return _______________;
    }
```

5. `swap(num)` swaps the **bytes** of an unsigned short. For example, `swap(1)` should return `256`. Note that `sizeof(unsigned short)` returns `2` on the AP server, and 1 byte consists of 8 bits.

```
unsigned short swap(unsigned short num) {
    unsigned short a = _______________;
    unsigned short b = _______________;
    return (a << 8) | b;
}

unsigned short x = 1;   // 0000 0000 0000 0001 in binary
assert(swap(x) == 256); // 0000 0001 0000 0000 (256)
```

## Solutions

The solutions can be found in `bit_operators_sol` directory in the same repo. The solutions are written in `bitoperators-solutions.h`; you can fill in `bitoperators.c` yourself before looking at the solutions.

Build using `make` and test by running `./bitoperators`.
