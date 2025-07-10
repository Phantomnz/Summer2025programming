#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int a = 13; // 0b1101
int b = 11; // 0b1011

int main() {
    int result = a & b; // Bitwise AND operation, result will be 9 (0b1001)
    int result2 = a | b; // Bitwise OR operation, result will be 15 (0b1111)
    int result3 = a ^ b; // Bitwise XOR operation, result will be 6 (0b0110)
    int y = 12 >> 2; // Bitwise right shift, 12/4 = 3 (0b0011)
    int x = 3 << 2; // Bitwise left shift, 3*4 = 12 (0b1100)

    printf("Bitwise AND of %d and %d is %d\n", a, b, result);
    printf("Bitwise OR of %d and %d is %d\n", a, b, result2);
    printf("Bitwise XOR of %d and %d is %d\n", a, b, result3);
    printf("Right shift 12 by 2 gives: %d\n", y);
    printf("Left shift 3 by 2 gives: %d\n", x);
    
    return 0;
}