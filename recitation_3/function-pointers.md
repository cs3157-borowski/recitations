
# Function Pointers #

All variables have a memory address, and we can reference the contents at that memory address by dereferncing them. However, functions also have an address, although it may not be as clear what dereferncing their memory address would do.

Function pointers are pointers that store the memory addresses of functions. This allows you to store references to functions and pass functions as arguments to other functions, enabling more dynamic and flexible code.

The syntax for declaring a function pointer is similar to declaring a normal pointer, with the type being the function signature. Here's an example:

```c
#include <stdio.h>

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int main() {
    // Declaring a function pointer that takes two int arguments and returns an int
    int (*p)(int, int);

    p = add; 
    printf("%d\n", p(2, 3)); // prints 5

    p = subtract;
    printf("%d\n", p(2, 3)); // prints -1

    return 0;
}
```

Here, `p` is our fuction pointer. Notice that we don't need to get the memory address of `add` or `subtract` when assigning it to the function pointer -- C provides syntatic sugar that lets away with assigning a function directly to a function pointer. The line `p = add` is the exactly same as `p = &add`.

The usual motivating example is qsort(); 
quicksort is tricky enough that we want to implement it generically for all types of arrays, but we can’t implement it without knowing how to compare elements of the array. So, we ask the caller to provide a pointer to the function used to compare two elements:

```c
void qsort(void *base, // the array we want to sort
           size_t nmemb, // how many elements in that array
           size_t size, // the size of each element in that array
           int (*compar)(const void *, const void *)); // how to compare
```

The declaration for compar:

```c
int (*compar)(const void *, const void *)
```

says that compar is a pointer to a function that receives two arguments (whose
types are both const void *), and returns an int.

Here an example of a comparison function:

```c
int compare_int(const void *v1, const void *v2) {
    int x = *(int *)v1;
    int y = *(int *)v2;
    if (x < y)
        return -1;
    else if (x > y)
        return 1;
    else
        return 0;
}
```

Now we can give it to `qsort()` to let it sort the array with the comparison that we specify:

```c
qsort(array_of_100_ints, 100, sizeof(int), &compare_int);
```

Function pointer syntax can be tricky to read and write! The following two
declarations are very different:

```c
    int (*f1)(float f);
    int *f2 (float f);
```

f1 is a pointer to a function that takes a float argument and returns an int;
f2 is a function that takes a float argument and returns a pointer to an int.
The parentheses surrounding f1 make a big difference here.