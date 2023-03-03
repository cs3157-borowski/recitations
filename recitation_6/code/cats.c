// cats.c: cats play with strings!
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(void) {
	assert(atoi("10") == '\n'); // Important!
    char buf[8];

    fgets(buf, 8, stdin);
    fputs(buf, stdout);

    return 0;
}
