#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <sys/wait.h> 
#include <math.h>
#include <errno.h>
#include <dirent.h>
#include <sys/resource.h>
#include <sys/stat.h>

#define MAX 100

typedef unsigned short tipo;

typedef struct { 
    char msg[100]; 
    int tempo;
} aviso_t;

typedef struct {
    char fonte[100];
    char destino[100];
} copiar_t;

int parse(char *buf, char **args);

void execute(int numargs, char **args);
int ultimo(int *numargs, char **args);
int containsPipe(int numargs, char **args);

int builtin (char **args);

void socp(char *fonte, char *destino) ;

void ioCopy(int IN,int OUT);

int ultimo(int *numargs, char **args);

void calc( char *value1, char *op, char *value2 );
void bits(char *op1, char *op, char *op2);
int isjpg(int fileDescriptor);
void displayBitOps(tipo um, tipo dois);

int fd_is_valid(int fd);
void openfile(char *nome);
void closefd(int fd);
void readfile(char *fd, char *nbytes);
void fileinfo();

int redirects(int numargs, char *args[]);
int dupandclose(int fd, int fdold, int numargs, char *args[]);

void aviso (char *mesg, int tempo);
void *avisowrapper(void *args);
void *socpthread_wrapper(void *arg);
void infoCopias();

void maior(char *file1, char *file2);
void setx(char *filename);
void removerl(char *filename);
void sols(char *pasta);

/* constantes que podem tornar uteis*/


#define BG 0
#define FG 1
#define FILE_MODE (S_IRUSR | S_IWUSR)
