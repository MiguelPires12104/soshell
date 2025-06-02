#include "shell.h"

#define HISTORY_SIZE 10
char *history[HISTORY_SIZE];
int history_count = 0;

void maior(char *file1, char *file2) {
    struct stat stat1, stat2;
    stat(file1, &stat1);
    stat(file2, &stat2);

    if (stat1.st_size > stat2.st_size) {
        printf("Ficheiro maior: %s, Tamanho: %ld KB\n", file1, stat1.st_size / 1024);
    } else {
        printf("Ficheiro maior: %s, Tamanho: %ld KB\n", file2, stat2.st_size / 1024);
    }
}

void setx(char *filename) {
    struct stat st;
    stat(filename, &st);

    if (chmod(filename, st.st_mode | S_IXUSR) != 0) {
        perror("Erro ao alterar permissões do ficheiro");
    } else {
        printf("Permissão de execução atribuída ao dono do ficheiro %s\n", filename);
    }
}

void removerl(char *filename) {
    struct stat st;
    stat(filename, &st);

    if (chmod(filename, st.st_mode & -(S_IRGRP | S_IROTH)) != 0) {
        perror("Erro ao alterar permissões do ficheiro");
    } else {
        printf("Permissão de leitura removida para grupo e mundo no ficheiro %s\n", filename);
    }
}

void sols(char *file)
{
  DIR *dp;
  struct dirent *dirp;
  struct stat var;

  if ((dp = opendir(file)) == NULL)
  {
    fprintf(stderr, "Can't open %s\n", file);
    file = ".";
    printf("Opening current directory\n");
    dp = opendir(file);
  }
  while ((dirp = readdir(dp)) != NULL)
  {
    stat(file, &var);
    printf("Nome: %s INode: %ld  Tamanho: %ld Hora: %s \n", dirp->d_name, dirp->d_ino, var.st_size, ctime(&var.st_ctime));
  }
  closedir(dp);
}

void add_to_history(char *command) {
    int index = history_count % HISTORY_SIZE;
    if (history[index]) {
        free(history[index]);
    }
    history[index] = strdup(command);
    history_count++;
}

void show_history() {
    int start = (history_count >= HISTORY_SIZE) ? (history_count % HISTORY_SIZE) : 0;
    int count = (history_count >= HISTORY_SIZE) ? HISTORY_SIZE : history_count;

    for (int i = 0; i < count; i++) {
        int index = (start + i) % HISTORY_SIZE;
        printf("%d: %s\n", i + 1, history[index]);
    }
}