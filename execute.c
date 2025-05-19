/*
   execute . cria um processo prog�nito e executa um programa
*/
#include "shell.h"

int ultimo(int *numargs, char **args) {
    if (*numargs > 0 && args[*numargs - 1][0] == '&') {
        *numargs = *numargs - 1;
        args[*numargs] = NULL;
        return BG; // Processo em Background
    }
    return FG; // Processo em Foreground
}

// Verifica se há pipe
int containsPipe(int numargs, char **args) {
    for (int i = 0; i < numargs; i++) {
        if (args[i][0] == '|') return i;
    }
    return -1;
}


void execute(int numargs, char **args) {
    int pid, status;
    int mode = ultimo(&numargs, args);
    int indice = containsPipe(numargs, args);

    //Nao existe Pipe
    if (indice == -1) {
        if ((pid = fork()) < 0) {
            perror("Erro no fork");
            exit(1);
        }
        if (pid == 0) {
            numargs = redirects(numargs, args);
            execvp(args[0], args);
            perror(args[0]);
            exit(1);
        } else {
            if (mode == FG)
                while (wait(&status) != pid);
            else
                printf("[Processo em Background] PID: %d\n", pid);
        }
    } else {
        // Existe Pipe
        args[indice] = NULL;
        int fd[2];
        char **argsNeto = &args[indice + 1];
        int numArgsNeto = numargs - indice - 1;
        pipe(fd);
        
        if ((pid = fork()) == 0) {
            // Processo filho (escrita no pipe)
            close(fd[0]);
            dup2(fd[1], STDOUT_FILENO);
            close(fd[1]);
            numargs = redirects(indice, args);
            execvp(args[0], args);
            perror("Erro no execvp (parte antes do pipe)");
            exit(1);
        }
        // Processo filho cria neto (leitura do pipe)
        if (fork() == 0) {
            close(fd[1]);
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
            numArgsNeto = redirects(numArgsNeto, argsNeto);
            execvp(args[indice + 1], &args[indice + 1]);
            perror("Erro no execvp (parte depois do pipe)");
            exit(1);
        }
        // Processo pai
        close(fd[0]);
        close(fd[1]);
        if (mode == FG) {
            wait(&status);
            wait(&status);
        } else {
            printf("[Comando com pipe em Background]\n");
        }
    }
}