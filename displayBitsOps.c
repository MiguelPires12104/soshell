#include "shell.h"

tipo mask = 0x8000;

void printBits(tipo numero, tipo mascara) {
    while (mascara > 0) {
        if (0 == (numero & mascara)) putchar('0');
        else putchar('1');
        mascara = mascara >> 1;
    }
}

void printBitsLn(tipo numero, tipo mascara) {
    printBits(numero, mascara);
    putchar('\n');
}

void displayBitOps(tipo um, tipo dois) {
    printf("Número 1: %d (decimal), %o (octal), 0x%X (hex)\n", um, um, um);
    printBitsLn(um, mask);
    
    printf("Número 2: %d (decimal), %o (octal), 0x%X (hex)\n", dois, dois, dois);
    printBitsLn(dois, mask);
    
    printf("AND: %d\n", um & dois);
    printBitsLn(um & dois, mask);
    
    printf("OR: %d\n", um | dois);
    printBitsLn(um | dois, mask);
    
    printf("XOR: %d\n", um ^ dois);
    printBitsLn(um ^ dois, mask);
    
    printf("Clear Bits: %d\n", um & ~dois);
    printBitsLn(um & ~dois, mask);
}