#include <stdio.h>

void wrapper(void (*f)(char *s), char *name) {
    f(name);
}

void hello_name(char *name) {
    if (name == NULL) {
        printf("Hello world!\n");
    } else {
        printf("Hello %s\n", name);
    }
}


int main(int argc, char **argv) {
    wrapper(hello_name, argv[1]);
}