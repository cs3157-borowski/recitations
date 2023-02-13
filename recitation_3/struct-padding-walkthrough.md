# Struct Padding Walkthrough

## Basic Rules

1. There is no padding at the beginning of a struct.
2. All elements of the struct need to be aligned according to their size.
3. All bytes of an element are stored contiguously.
4. The total size of the struct must be a multiple of the size of the largest element.

## Methodology
Let's go through the basic methodology to obtain the memory layout of a struct according to the rules stated above.

```c
struct my_struct{
    char a;
    short b;
    char c;
    long d;
    int e;
};
```

Since it is forbidden to have any padding at the beginning of a struct (**Rule 1**), the first step to obtain the memory layout, is to "place" the first element, `char a`, to do that, we need to know the size of its type, in this case is just 1 since `sizeof(char) == 1`; therefore, so far we just have:

```
+-+
|a|
+-+
```


We go on to the second element, `short b`, now we are no longer at the beginning of the struct, so we must worry about alignment and padding. To figure out where to "place" the second element, again, we need to know the size of its type. In this case is 2 since `sizeof(short) == 2` and we know that it must be aligned to its size (**Rule 2**)-- this just means that it must be placed at an address that is divisible by the size. To ease this, we can always think about 0 being the starting address; if we add addresses to our diagram, we have the following (I am adding a few more memory blocks that are not filled yet, just so this is easier to follow)

```
+-+-+-+-+
|a| | | |
+-+-+-+-+
0 1 2 3 4
```

Back to placing the short, we have currently only filled address 0, so the next address to fill is 1, but 1 is not divisible by 2 (`sizeof(short)`), so let's start padding until we get to an address that is divisible by 2:

```
+-+-+-+-+
|a|-| | |
+-+-+-+-+
 0 1 2 3 
```

We only needed one byte of padding, since 2 is divisible by 2, so let's place the short, since we know the bytes of an element need to be stored contiguously (**Rule 3**), we would just get the following:

```
+-+-+-+-+
|a|-|b|b|
+-+-+-+-+
 0 1 2 3
```

On to `char c`, again size is 1 and the next empty address we are working with is now 4, that is divisible by 1, so we just add it:

```
+-+-+-+-+-+
|a|-|b|b|c|
+-+-+-+-+-+
 0 1 2 3 4 
 ```

Moving on to `long d` , the size is now 8 since `sizeof(long) == 8` and the next  empty address is 5, which is not divisible by 8, so we must pad until an address divisible by 8:

```
+-+-+-+-+-+-+-+-+
|a|-|b|b|c|-|-|-|
+-+-+-+-+-+-+-+-+
 0 1 2 3 4 5 6 7
```

and then place the element (I am increasing the box size just because the indices have two digits and is easier to see)

```
+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
| a | - | b | b | c | - | - | - | d | d | d | d | d | d | d | d |
+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
  0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15 
```

For the last element, `int e`, the size is 4 since `sizeof(int) == 4` and our next working address is 16, which is divisible by 4, so we can just place it:

```
+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
| a | - | b | b | c | - | - | - | d | d | d | d | d | d | d | d | e | e | e | e |
+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
  0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19
```

We are almost there, but we haven't seen **Rule 4** yet, our current size is 20, but the size of the largest element, `long d`, is 8, and 20 is not divisible by 8, so we must pad again until reaching a multiple of 8:

```
+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
| a | - | b | b | c | - | - | - | d | d | d | d | d | d | d | d | e | e | e | e | - | - | - | - |
+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
  0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19  20  21  22  23
```

We are now done! 
One last thing is that usually you would see it represented with each row being the width of the largest element, so the memory layout above would usually look like this:

```
+---+---+---+---+---+---+---+---+
| a | - | b | b | c | - | - | - | 
+---+---+---+---+---+---+---+---+
| d | d | d | d | d | d | d | d |
+---+---+---+---+---+---+---+---+
| e | e | e | e | - | - | - | - |
+---+---+---+---+---+---+---+---+
```
