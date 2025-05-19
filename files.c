#include "shell.h"

int fd_is_valid(int fd) {
    return fcntl(fd, F_GETFD) != -1 || errno != EBADF;
}

void openfile(char *nome) {
    int fd = open(nome, O_RDONLY);
    if (fd >= 0)
        printf("Aberto %s para operações de leitura com descritor fd %d\n", nome, fd);
    else
        perror(nome);
}

void closefd(int fd) {
    if (close(fd) < 0)
        perror("Falha ao fechar o descritor de arquivo");
    else
        printf("Descritor de arquivo %d fechado com sucesso\n", fd);
}

void readfile(char *fd_str, char *nbytes_str) {
    if (fd_str == NULL || nbytes_str == NULL) {
        printf("Erro: Argumentos inválidos para readfile\n");
        return;
    }

    int fd = atoi(fd_str);           // Converte o descritor de arquivo para inteiro
    int nbytes = atoi(nbytes_str);   // Converte o número de bytes para inteiro

    if (!fd_is_valid(fd)) {
        printf("Erro: Descritor de arquivo inválido: %d\n", fd);
        return;
    }

    if (nbytes <= 0) {
        printf("Erro: Número inválido de bytes: %d\n", nbytes);
        return;
    }

    char *buffer = (char *)malloc(nbytes);
    if (!buffer) {
        perror("Erro ao alocar memória");
        return;
    }

    ssize_t bytesRead = read(fd, buffer, nbytes);
    if (bytesRead < 0) {
        perror("Erro ao ler arquivo");
        free(buffer);
        return;
    }

    printf("Conteúdo lido (ASCII): ");
    for (ssize_t i = 0; i < bytesRead; i++) {
        printf("%c", buffer[i]);
    }
    printf("\n");

    printf("Conteúdo lido (Hex): ");
    for (ssize_t i = 0; i < bytesRead; i++) {
        printf("%02X ", (unsigned char)buffer[i]);
    }
    printf("\n");

    free(buffer);
}

void fileinfo() {
    struct rlimit rl;
    getrlimit(RLIMIT_NOFILE, &rl);
    printf("Número máximo de arquivos abertos por processo: %ld\n", rl.rlim_cur);
    
    int total_open_fds = 0;
    printf("Descritores de arquivo abertos: ");
    for (int fd = 0; fd < rl.rlim_cur; fd++) {
        if (fd_is_valid(fd)) {
            printf("%d ", fd);
            total_open_fds++;
        }
    }
    printf("\nTotal de descritores abertos: %d\n", total_open_fds);
    
    if (stdout)
        printf("stdout está aberto com descritor %d\n", fileno(stdout));
    else
        printf("stdout está fechado\n");
}
