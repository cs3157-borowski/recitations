# **Bit Operators**

Without using any arithmetic or comparison operators (e.g., `+`, `-`, `*`, `/`, `%`, `<`, `<=`, `>`, `>=`, `==`, or `!=`), fill in the blanks according to the description. Dont assume `sizeof(int) == 4`; make these methods work for any `int` size! 

**Exception:** you may use `-` only to account for off-by-one (e.g., `x - 1` is ok; `x - 32` or `x - n` is not).


- `mul8(num)` should return `num * 8`:
```
int mul8(int num) {
    return _______________; //
}
```

- `make_odd(num)` should return `num` if `num` is odd, and return `num + 1` otherwise:
```
unsigned int make_odd(unsigned int num) {
    return _______________;
}
```

- `is_negative(num)` should return `1` when `num` is negative, and `0` otherwise:
```
int is_negative(int num) {
    if (_______________)
        return 1;
    else
        return 0;
}
```

- `set_bit(num, n, b)` should return `num`, with its `n`-th bit is set to `1` if `b` is non-zero, and set to `0` otherwise (`n` is zero-indexed; `set_bit(0, 0 ,1)` should return `1`):
```
int set_bit(int num, int n, int b) {
    if (b)
        return _______________;
    else
        return _______________;
}
```
## Solutions


## Acknowledgements

The exercises were created by John Hui. They were modified by Stanley Lin in Spring 2023.
