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

Also known as a bitwise eXclusive OR; it behaves just like the bitwise AND and OR, except with an XOR operation. Takes two integers as operands and returns a new integer where its bit pattern consists of 1's where only one of its operands has a 1 in the same position.
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

## Data Types in C and sizeof

C types tell you precisely how much memory a variable of that type occupies; however, the C standard does **NOT** specify the byte sizes of these types! On most systems:

-   `char`:         1 byte
-   `short`:        2 bytes
-   `int`:          4 bytes
-   `long`:         8 bytes on 64-bit UNIX systems (such as AP server); 4 bytes on most 32-bit systems and 64-bit Windows
-   `long long`:    8 bytes

You can use `sizeof` operator to obtain the size of a type:
```
printf("size of long: %lu\n", sizeof(long));
```
Or the size of the type of an expression:
```
long i;
printf("size of i: %lu\n", sizeof(i));
printf("size of some arithmetic: %lu\n", sizeof(i + 2));
```
Some quirks about `sizeof`:
-   `sizeof` isn't a function. It just looks like one! `sizeof` is an operator
-   The `sizeof` of any type is known at complie time
-   `sizeof` does **NOT** evaluate its argument:
```
int foo(void) {
    printf("foo() was called\n"); // never printed
}

printf("size of foo's return type: %lu\n", sizeof(foo()));
```

## Exercises

Without using any arithmetic or comparison operators (e.g., `+`, `-`, `*`, `/`, `%`, `<`, `<=`, `>`, `>=`, `==`, or `!=`), fill in the blanks according to the description. Don't assume `sizeof(int) == 4`; make these methods work for any `int` size!

**Exception:** you may use `-` only to account for off-by-one (e.g., `num - 1` is ok; `num - 32` or `num - n` is not).

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

## Acknowledgements

Parts of this note and exercises were originally created by Prof. Jae Lee and John Hui for this course. They were modified by Stanley Lin in Spring 2023.