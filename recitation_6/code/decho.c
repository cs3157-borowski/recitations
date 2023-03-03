// decho.c
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        unsigned char d = atoi(argv[i]);
        fwrite(&d, 1, 1, stdout);
    }
}
