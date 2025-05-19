#include "shell.h"

int isjpg(int fileDescriptor) {
    unsigned char b[4];
    int n = read(fileDescriptor, b, 4);
    
    if (n < 4) {
        return 0; 
    }
    
    // Voltar ao início do ficheiro
    lseek(fileDescriptor, 0, SEEK_SET);
    
    // Verificar assinatura do JPG
    if (b[0] == 0xFF && b[1] == 0xD8 && b[2] == 0xFF && 
        (b[3] == 0xE0 || b[3] == 0xE1 || b[3] == 0xE2 || b[3] == 0xE8)) {
        return 1;
    }
    
    return 0;
}