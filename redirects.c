#include "shell.h"

int dupandclose(int fd, int fdold, int numargs, char *args[])
{
    if (fd < 0) {
        perror(NULL);
        exit(1); // indicar erro
    }
    dup2(fd, fdold);
    close(fd);
    args[numargs - 2] = NULL;
    return (numargs - 2);
}

int redirects(int numargs, char *args[])
{
    if (numargs < 3)
        return numargs;

    // 1. Redirecionamento de erro (2>)
    else if (strcmp(args[numargs - 2], "ERROS") == 0) {
        int fd = creat(args[numargs - 1], FILE_MODE);
        numargs = dupandclose(fd, STDERR_FILENO, numargs, args);

    }

    // 2. Redirecionamento de saída (>) ou (>>)
    if (numargs < 3)
        return numargs;
        
    else if (strcmp(args[numargs - 2], ">") == 0) {
        int fd = creat(args[numargs - 1], FILE_MODE);
        numargs = dupandclose(fd, STDOUT_FILENO, numargs, args);
    }

    else if (strcmp(args[numargs - 2], ">>") == 0) {
        int fd = open(args[numargs - 1], O_WRONLY | O_CREAT | O_APPEND, FILE_MODE);
        numargs = dupandclose(fd, STDOUT_FILENO, numargs, args);
    }


    if (numargs < 3)
        return numargs;

    // 3. Redirecionamento de entrada (<)
    else if (strcmp(args[numargs - 2], "<") == 0) {
        int fd = open(args[numargs - 1], O_RDONLY);
        numargs = dupandclose(fd, STDIN_FILENO, numargs, args);
    }

    return numargs;
}