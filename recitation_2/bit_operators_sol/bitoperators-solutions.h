// Multiplying by 2^n is the same as bit-shifting to the left by n;
// 8 is 2^3, so num * 8 is the same as num << 3.
// Also note that dividing 2^n is the same as bit-shifting to the right by n.
#define ANSWER_1      (num << 3)

// 0x1 looks like 0000.....0001 in binary; bitwise ORing it with num set the LSB
// to 1, and leaves the other bits untouched.
#define ANSWER_2      (num | 0x1)

// To determine if a signed two's complement integer is negative, we just need
// to test its MSB. We construct a bitmask that looks like 1000...0000 by
// left-shifting 0x1 by 31 (i.e., 1 less than the size of num in bits).
// sizeof(num) gives us the size of num in bytes, so we need to multiply it by
// 8 (equivalently, bit-shift left by 3) to obtain its size in bits.
#define ANSWER_3      (num & (0x1 << ((sizeof(num) << 3) - 1)))

// To set the nth bit of num to 1, create a bitmask with the nth bit as 1 and
// 0 everywhere else, and bit-wise OR it with num.
#define ANSWER_4_1    (num | (0x1 << n))

// To set the nth bit of num to 0, create a bitmask where all the bits are
// 1 except for the nth bit, and bit-wise AND it with num.
#define ANSWER_4_2    (num & ~(0x1 << n))

// (a << 8) is num being shoved 8 bits (1 byte) to the left, whereas b is num being 
// shoved 8 bits (1 byte) to the right.
#define ANSWER_5_1    (num) 
#define ANSWER_5_2    (num >> 8)
