// dcat.c
#include <stdio.h>

int main(void) {

    unsigned char d;
    while (fread(&d, 1, 1, stdin))
        printf("%d, ", d);

    printf("\n");
}
