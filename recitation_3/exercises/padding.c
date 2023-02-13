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