#include "shell.h"

char prompt[100];

int main()
{
  int len;
  char linha[1024]; /* um comando */
  char *args[64];   /* com um maximo de 64 argumentos */

  strcpy(prompt, "SOSHELL: Introduza um comando : prompt>");
  while (1)
  {
    printf("%s", prompt);
    if (fgets(linha, 1023, stdin) == NULL)
    {
      printf("\n");
      exit(0);
    }
    len = strlen(linha);
    if (1 == len)
      continue; /* linha é apenas \n */
    if (linha[len - 1] == '\n')
      linha[len - 1] = '\0';

    add_to_history(linha);

    int numargs = parse(linha, args);

    if (!builtin(args))
      execute(numargs, args); /* executa o comando */

    if (strcmp(args[0], "history") == 0) {
    show_history();
    continue; // Volta ao loop sem executar
    }
  }

  return 0;
}

int builtin(char **args)
{
  /* Toda a funcionalidade embutida deverá devolver 1 */
  if (strcmp(args[0], "sair") == 0)
  {
    exit(0);
    return 1; /* funcionalidade embutida */
  }
  if (strncmp(args[0], "42", 2) == 0)
  {
    printf("42 is the answer to life the universe and everything\n");
    printf("https://pt.wikipedia.org/wiki/The_Hitchhiker's_Guide_to_the_Galaxy\n");
    return 1; /* funcionalidade embutida */
  }
  if (0 == strcmp(args[0], "obterinfo"))
  {
    printf("SO Shell 2025 versaõ 1.0\n");
    return 1; // comando embutido
  }
  if (strlen(args[0]) > 4 && 0 == strncmp(args[0], "PS1=", 4))
  {
    strcpy(prompt, args[0] + 4);
    return 1; // comando embutido
  }
  if (0 == strcmp(args[0], "quemsoueu"))
  {
    system("id");
    return 1; // comando embutido
  }
  if (0 == strcmp(args[0], "cd"))
  {
    int err;
    if (args[1] == NULL || strcmp(args[1], "~") == 0 ||
        strcmp(args[1], "$HOME") == 0)
    {
      err = chdir(getenv("HOME"));
    }
    else
    {
      err = chdir(args[1]);
    }
    if (err < 0)
    {
      perror(args[1]);
    }
    return 1; // Comando embutido
  }

  if (0 == strcmp(args[0], "socp"))
  {
    if (args[1] != NULL && args[2] != NULL)
      socp(args[1], args[2]);
    else
      printf("Syntax Incorreto: Usage: socp fonte destino");
    return 1; // comando embutido
  }
     if (0 == strcmp(args[0], "calc"))
    {
      if (args[1] != NULL && args[2] != NULL && args[3] != NULL)
      {
        // chamar a função calc()
        calc(args[1], args[2], args[3]);
        return 1; // comando embutido
      }
      else
      {
        printf("%s\n", args[1]);
        printf("erro de argumentos\n");
      }
      return 1;
    }

    if (0 == strcmp(args[0], "bits"))
    {
      if (args[1] != NULL && args[2] != NULL && args[3] != NULL)
      {
        // chamar a função bits()
        bits(args[1], args[2], args[3]);
        return 1; // comando embutido

      }
      else
      {
        printf("erro de argumentos\n");
      }
      return 1;
    }

    if (strcmp(args[0], "isjpeg") == 0) {
      if (args[1] != NULL) {
          int fd = open(args[1], O_RDONLY);
          if (fd < 0) {
              perror("Erro ao abrir o ficheiro");
              return 1;
          }
          if (isjpg(fd)) {
              printf("O ficheiro %s é um JPEG.\n", args[1]);
          } else {
              printf("O ficheiro %s NÃO é um JPEG.\n", args[1]);
          }
          close(fd);
          return 1;
      } else {
          printf("Erro de argumentos para isjpeg.\n");
          return 1;
      }
  }

  if (strcmp(args[0], "displayBitsOps") == 0) {
    if (args[1] != NULL && args[2] != NULL) {
      tipo num1 = (tipo)atoi(args[1]);
      tipo num2 = (tipo)atoi(args[2]);
      displayBitOps(num1, num2);
      return 1;
    }else{
      printf("Uso: %s <numero1> <numero2>\n", args[0]);
      return 1;
    }
  }
  //Verificar se file descriptor é valido.
  if (strcmp (args[0], "isValid") == 0) {
    if (NULL!=args[1]) {
    int fd=atoi(args[1]);
    printf("O descritor %d é %s válido\n", fd, fd_is_valid(fd) ? "" : "não");
    }
    return 1;
   }
   //Abrir file Descriptor
   if (strcmp (args[0], "openfile") == 0) {
    if (NULL!=args[1] )
    openfile(args[1]);
    return 1;
   }
   
   //Fechar o filed escriptor.
   if (strcmp (args[0], "closefd") == 0) {
    if (NULL!=args[1])
    closefd( atoi(args[1]) );
    return 1;
   }
   //Ler o ficheiro.
   if (strcmp (args[0], "read") == 0) {
    if (NULL!=args[2] )
    readfile(args[1], args[2]);
    return 1;
   }
   //Ver o que está no ficheiro.
   if (strcmp (args[0], "fileinfo") == 0) {
    fileinfo();
    return 1;
   }
   //AVISOS ------------
   if ( 0 == strcmp (args[0], "aviso") ){
    pthread_t th;
    aviso_t * ptr = (aviso_t *)malloc( sizeof(aviso_t) );
    strcpy(ptr->msg, args[1]);
    ptr->tempo=atoi(args[2]);
    pthread_create(&th, NULL, avisowrapper, (void *)ptr);
    return 1;
   }
   //Copiar o ficheiro com Threads
   if (strcmp(args[0], "socpthread") == 0)
  {
    pthread_t th;
    copiar_t *ptr = (copiar_t *)malloc(sizeof(copiar_t));
    strcpy(ptr->fonte, args[1]);
    strcpy(ptr->destino, args[2]);
    pthread_create(&th, NULL, socpthread_wrapper, (void *)ptr);
    pthread_detach(th);
    return 1;
  }
  if (strcmp(args[0], "infoCopias") == 0) {
    infoCopias();
    return 1;
  }

  if (strcmp(args[0], "Maior") == 0)
  {
    if (args[1] == NULL || args[2] == NULL)
    printf("Erro");
    maior(args[1], args[2]);
    return 1;
  }

  if (strcmp(args[0], "setx") == 0)
  {
    if (args[1] == NULL)
    printf("Erro");
    setx(args[1]);
    return 1;
  }

  if (strcmp(args[0], "removerl") == 0)
  {
    if (args[1] == NULL)
    printf("Erro");
    removerl(args[1]);
    return 1;
  }

  if (strcmp(args[0], "sols") == 0)
  {
    if (args[1] == NULL)
    printf("Erro");
    sols(args[1]);
    return 1;
  }


  /* IMPORTANTE :
     Devolver 0 para indicar que não existe comando embutido e que
     será executado usando exec() na função execute.c
   */
  return 0;
}
