#include <stdio.h>
#include "bitoperators-solutions.h"

int mul8(int num) {
     return ANSWER_1;
}

unsigned int make_odd(unsigned int num) {
    return ANSWER_2;
}

int is_negative(int num) {
    if (ANSWER_3)
        return 1;
    else
        return 0;
}

int set_bit(int num, int n, int b) {
    if (b)
        return ANSWER_4_1;
    else
        return ANSWER_4_2;
}

unsigned short swap(unsigned short num) {
    unsigned short a = ANSWER_5_1;
    unsigned short b = ANSWER_5_2;
    return (a << 8) | b;
}

int main(void) {

    printf("Testing bit-manipulating functions...\n");

    printf("mul8(0)                     = %d\n", mul8(0));
    printf("mul8(1)                     = %d\n", mul8(1));
    printf("mul8(3)                     = %d\n", mul8(3));
    printf("mul8(8)                     = %d\n", mul8(8));
    printf("mul8(-1)                    = %d\n", mul8(-1));
    printf("mul8(-2)                    = %d\n", mul8(-2));
    printf("mul8(-32)                   = %d\n", mul8(-32));
    printf("\n");
    printf("-----------------------------\n");
    printf("\n");

    printf("make_odd(0)                 = %u\n", make_odd(0));
    printf("make_odd(1)                 = %u\n", make_odd(1));
    printf("make_odd(5)                 = %u\n", make_odd(5));
    printf("make_odd(32)                = %u\n", make_odd(32));
    printf("make_odd(128)               = %u\n", make_odd(128));
    printf("make_odd(256)               = %u\n", make_odd(256));
    printf("\n");
    printf("make_odd(0x0)               = 0x%08x\n", make_odd(0x0));
    printf("make_odd(0x1)               = 0x%08x\n", make_odd(0x1));
    printf("make_odd(0x7)               = 0x%08x\n", make_odd(0x7));
    printf("make_odd(0x8)               = 0x%08x\n", make_odd(0x8));
    printf("make_odd(0xfffffffe)        = 0x%08x\n", make_odd(0xfffffffe));
    printf("make_odd(0xffffffff)        = 0x%08x\n", make_odd(0xffffffff));
    printf("\n");
    printf("-----------------------------\n");
    printf("\n");

    printf("is_negative(0)              = %d\n", is_negative(0));
    printf("is_negative(1)              = %d\n", is_negative(1));
    printf("is_negative(2)              = %d\n", is_negative(2));
    printf("is_negative(-1)             = %d\n", is_negative(-1));
    printf("is_negative(-3)             = %d\n", is_negative(-3));
    printf("\n");
    printf("is_negative(0x00000000)     = %d\n", is_negative(0x00000000));
    printf("is_negative(0x7fffffff)     = %d\n", is_negative(0x7fffffff));
    printf("is_negative(0x80000000)     = %d\n", is_negative(0x80000000));
    printf("is_negative(0xffffffff)     = %d\n", is_negative(0xffffffff));
    printf("\n");
    printf("-----------------------------\n");
    printf("\n");

    printf("set_bit(0x0, 0, 1)          = 0x%08x\n", set_bit(0x0, 0, 1));
    printf("set_bit(0x0, 1, 1)          = 0x%08x\n", set_bit(0x0, 1, 1));
    printf("set_bit(0x0, 2, 1)          = 0x%08x\n", set_bit(0x0, 2, 1));
    printf("set_bit(0x0, 3, 1)          = 0x%08x\n", set_bit(0x0, 3, 1));
    printf("set_bit(0x0, 30, 1)         = 0x%08x\n", set_bit(0x0, 30, 1));
    printf("set_bit(0x0, 31, 1)         = 0x%08x\n", set_bit(0x0, 31, 1));
    printf("\n");
    printf("set_bit(0xffffffff, 0, 0)   = 0x%08x\n", set_bit(0xffffffff, 0, 0));
    printf("set_bit(0xffffffff, 1, 0)   = 0x%08x\n", set_bit(0xffffffff, 1, 0));
    printf("set_bit(0xffffffff, 30, 0)  = 0x%08x\n", set_bit(0xffffffff, 30, 0));
    printf("set_bit(0xffffffff, 31, 0)  = 0x%08x\n", set_bit(0xffffffff, 31, 0));
    printf("\n");
    printf("set_bit(0x0, 0, 0)          = 0x%08x\n", set_bit(0x0, 0, 0));
    printf("set_bit(0x0, 3, 0)          = 0x%08x\n", set_bit(0x0, 3, 0));
    printf("set_bit(0x0, 8, 0)          = 0x%08x\n", set_bit(0x0, 8, 0));
    printf("set_bit(0x0, 31, 0)         = 0x%08x\n", set_bit(0x0, 31, 0));
    printf("set_bit(0xffffffff, 0, 1)   = 0x%08x\n", set_bit(0xffffffff, 0, 1));
    printf("set_bit(0xffffffff, 6, 1)   = 0x%08x\n", set_bit(0xffffffff, 6, 1));
    printf("set_bit(0xffffffff, 9, 1)   = 0x%08x\n", set_bit(0xffffffff, 9, 1));
    printf("set_bit(0xffffffff, 31, 1)  = 0x%08x\n", set_bit(0xffffffff, 31, 1));
    printf("\n");
    printf("-----------------------------\n");
    printf("\n");

    printf("swap(0)                     = %u\n", swap(0));
    printf("swap(1)                     = %u\n", swap(1));
    printf("swap(7)                     = %u\n", swap(7));
    printf("swap(8)                     = %u\n", swap(8));
    printf("swap(256)                   = %u\n", swap(256));
    printf("\n");
    printf("swap(0x0)                   = 0x%04x\n", swap(0x0));
    printf("swap(0x1)                   = 0x%04x\n", swap(0x1));
    printf("swap(0x7)                   = 0x%04x\n", swap(0x7));
    printf("swap(0x8)                   = 0x%04x\n", swap(0x8));
    printf("swap(0xfffe)                = 0x%04x\n", swap(0xfffe));
    printf("swap(0xffff)                = 0x%04x\n", swap(0xffff));

    return 0;
}
