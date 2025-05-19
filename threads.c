#include "shell.h"

char strings[MAX][130];
int numCopies = 0;

void aviso (char *mesg, int tempo)
{
 while (tempo > 0) {
 sleep (1);
 tempo--;
 }
 fprintf (stderr, "Aviso : %s\n", mesg );
}

void * avisowrapper(void *args) {
    aviso_t * ptr = (aviso_t *)args;
    aviso( ptr->msg, ptr->tempo ) ;
    free(ptr);
    return NULL;
}

void *socpthread_wrapper(void *arg) {
    copiar_t *data = (copiar_t *)arg;

    socp(data->fonte, data->destino);

    time_t tempoAtual;
    time(&tempoAtual);
    char *diaHora = ctime(&tempoAtual);
    if (diaHora[strlen(diaHora) - 1] == '\n')
        diaHora[strlen(diaHora) - 1] = '\0';

    snprintf(strings[numCopies++ % MAX], 130, "%s %s", diaHora, data->destino);
    free(data);
    return NULL;
}

void infoCopias() {
    for (int i = 0; i < numCopies && i < MAX; i++) {
        printf("%s\n", strings[i]);
    }
}
   