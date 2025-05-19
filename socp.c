#include "shell.h"

#define BUFFER_SIZE 1024

void ioCopy(int IN, int OUT) {
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;
    
    while ((bytesRead = read(IN, buffer, BUFFER_SIZE)) > 0) {
        if (write(OUT, buffer, bytesRead) != bytesRead) {
            perror("Erro ao escrever no ficheiro de destino");
            exit(EXIT_FAILURE);
        }
    }
    
    if (bytesRead < 0) {
        perror("Erro ao ler o ficheiro de origem");
        exit(EXIT_FAILURE);
    }
}

void socp(char *fonte, char *destino) {
    int srcFD = open(fonte, O_RDONLY);
    if (srcFD < 0) {
        perror("Erro ao abrir o ficheiro de origem");
        exit(EXIT_FAILURE);
    }
    
    int destFD = open(destino, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (destFD < 0) {
        perror("Erro ao criar o ficheiro de destino");
        close(srcFD);
        exit(EXIT_FAILURE);
    }
    
    ioCopy(srcFD, destFD);
    
    close(srcFD);
    close(destFD);
}
