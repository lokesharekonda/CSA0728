#include <stdio.h>

#define FLAG 0x7E
#define ESC 0x7D
#define XOR 0x20
#define MAX_LEN 1024 
int stuff_bits(unsigned char* data, int len) {
    int i, j, count;
    for (i = 0, count = 0; i < len; i++) {
        if (data[i] == FLAG || data[i] == ESC) {
            count++;
        }
    }
    if (count == 0) {
        return len;
    }
    j = len + count;
    for (i = len - 1; i >= 0; i--) {
        if (data[i] == FLAG || data[i] == ESC) {
            data[--j] = data[i] ^ XOR;
        } else {
            data[--j] = data[i];
        }
    }

    return j;
}
int unstuff_bits(unsigned char* data, int len) {
    int i, j, count;
    for (i = 0, count = 0; i < len; i++) {
        if (data[i] == ESC) {
            count++;
        }
    }
    if (count == 0) {
        return len;
    }
    j = len - count;
    for (i = 0; i < j; i++) {
        if (data[i] == ESC) {
            data[i] = data[++i] ^ XOR;
        }
    }
    return j;
}
int main() {
    unsigned char data[MAX_LEN] = {0x01, 0x02, 0x03, FLAG, ESC, 0x04};
    int len = 6;
    printf("Data before stuffing: ");
    for (int i = 0; i < len; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
    len = stuff_bits(data, len);
    printf("Data after stuffing: ");
    for (int i = 0; i < len; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
    len = unstuff_bits(data, len);
    printf("Data after unstuffing: ");
    for (int i = 0; i < len; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
    return 0;
}

