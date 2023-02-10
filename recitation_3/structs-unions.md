
# Structs and Unions #

C is a language without many types of data structures. The most primitive data structure is an array, which stores the same element contingously. Often we want to represent different types of data in the same data structure, and C provides structs and unions to do so.

## Structs

Structs allow us to specify a data structure consisting of a fixed number of named elements:

```c
struct Point {
    int x;
    int y;
};
```

This struct definition must be written at the top-level (e.g., it cannot be
inside of a function body); don’t forget the trailing ’;’!

The above struct definition creates a new type named "struct Point", which we
can define and use like so:

```c
struct Point pt;

pt.x = 2;
pt.y = 3;
```

Structs are so-called because they describe the in-memory structure of a type.
This is what `pt` looks like in memory:

```
+---+---+---+---+---+---+---+---+
|    .x = 2     |    .y = 3     |
+---+---+---+---+---+---+---+---+
|----------- struct pt ---------|
```

### typedef

A `typedef` is a directive that creates an alias for an existing type. We can use this directive to simplify the syntax of declaring instances of a struct like so:

```c
typedef struct {
    int x;
    int y;
} Point;

Point pt;

pt.x = 2;
pt.y = 3;
```

Notice how we no longer need to write `struct` in the type of `pt`. The above code has the same effect as the equivalent code for structs. The advantage of using typedef structs is that it makes the code cleaner and easier to read.

An advatange of structs is that they don't need to have the same type of data; the above example could easily be expressed as an array since the struct only has members of type `int`. For example, the following
struct MyString allows us to quickly access the length of a string without
scanning it for a null terminator byte:

```c
struct MyString {
    unsigned int len;
    char *s = str;
};
 
struct MyString s;
s.str = "abc";
s.len = strlen("abc");
```

The size and layout of each struct is determined and fixed at compile time.
Struct definitions may contains fields of any type, including pointers, arrays,
and other structs (as long as they don’t contain themselves):

```c
struct TwoPoints {
    struct Point p1;
    struct Point p2;
};

struct Buffer {
    unsigned int len;
    char buf[1024];
};

struct Foo {
    struct TwoPoints pp;
    struct Foo f; // compiler error: a struct cannot contain itself
};
```

Even though a struct cannot contain itself, it can contain a pointer to itself. This can allow for self-referential structs like so:

```c
struct IntListNode {
    int data;
    struct IntListNode *next;
};
```

This can be helpful in creating more complex data structure such as linked lists -- a struct could contain a pointer to the next struct in its linked list.

### Struct Padding

In the `MyString` example above, the struct contains an `unsigned int` and a `char *`. We know that these types have different sizes -- an unsigned int is 4 bytes, while a pointer is always 8 bytes. 

It may be intuitive to think that the total size of this struct is 4 + 8 = 12 bytes. However due to struct padding, the size of the struct is actually more than the sum of each element. 

The layout would look like this:

```
 +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 | .len = 3      | (padding)     | .str = (points to "abc")      |
 +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 |--------------------- struct MyString -------------------------|
```

Struct padding occurs because C requires data elements within a struct to be stored in memory with a specific alignment. The alignment requirement depends on the data type and the architecture of the computer, but it is typically a multiple of the size of the largest data type.

In the above example, the largest type is `char *`. Therefore, an extra 4 bytes of space are padded after `int len`. `sizeof(struct MyString)` then would evaluate to 16.

A struct may pad differently depending on the order of elements. A poorly ordered struct may look something like this:

```c
struct MyStuff {
    char *str1;
    int s = len1;
    char *str2;
    int s len2;
};

Here, the two `char *`s are the largest type with 8 bytes. :

```
 +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 | .str1                         |  .len1        |  (padding)    | .str2                         |  .len2        | (padding)     |
 +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 |-------------------------------------------------------- struct MyStuff -------------------------------------------------------|
```

However, if we are to reorganize the struct like so:

```c
struct MyStuff2 {
    char *str1;
    char *str2;
    int len1;
    int len2;
};
```
The layout would look like this:

```
 +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 | .str1                         | .str2                         |  .len1        | .len2         |
 +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 |------------------------------------ struct MyStuff2 ---------------------- -------------------|
```

Try to guess what the size of each struct will be below:

```c
#include <stdio.h>

struct a {
    char *x;
    int y;
    char z;
};

struct b {
    int x;
    char *y;
    char z;
};

struct c {
    char *p;   
    char c;
    short x;
};

struct d {
    char w;
    int x;
    short y;
    char z;
};


int main() {
    printf("%lu\n", sizeof(struct a));
    printf("%lu\n", sizeof(struct b));
    printf("%lu\n", sizeof(struct c));
    printf("%lu\n", sizeof(struct d));
}
```

### Pointers to structs

Since structs may get very large in size (e.g., struct Buffer), it can be more
efficient to refer to them via pointers rather than copy them around by value:

```c
void inefficient_arg(struct Buffer buf) { ... }
void efficient_arg(struct Buffer *buf) { ... }
```

Thus, a common pattern when using a pointer to a struct is to first dereference
it, and then access the field:

```c
(*b).len
```

C provides syntactic sugar to make this look nicer:

```c
b->len
```

This notation should be read as, "dereference b, and access the len field."
Keep in mind that this notation still performs a dereference; if b is a NULL
pointer, this expression will segfault.

### Unions

Unions in C are similar to structs, but they differ in the way they allocate memory. A union defines a data structure that can store values of different data types at the same memory location. This allows the same memory location to be interpreted as different types. The size of a union is equal to the size of the largest member of the union. Here's an example:

```c
union Data {
    int i;
    float f;
};
```

With this definition, we can use the union like this:

```c
union Data data;

data.i = 10;
printf("data.i: %d\n", data.i);

data.f = 20.5;
printf("data.f: %f\n", data.f);
```

In this example, the same memory location is used to store both an integer and a float. The value of data.i will change after assigning a value to data.f, and vice versa. This is because the same memory location is being interpreted as different types.

This is what `data` looks like in memory:

```
+---+---+---+---+---+---+---+---+
|    .x     /    .y             |
+---+---+---+---+---+---+---+---+
|----------- union data -------|
```

.x and .y share the same 4 bytes, and that same memory location is overwritten between assignments. 

Unions can be useful for reinterpreting the bit
pattern of one type as another, without error-prone pointer casting:

```c
union LongDouble {
    unsigned long as_long;
    double as_double;
};

```c
union LongDouble v;
v.as_double = 3.14;
printf("%lu\n", v.as_long);

// equivalent to

printf("%lu\n", (unsigned long) v.as_double);
```
