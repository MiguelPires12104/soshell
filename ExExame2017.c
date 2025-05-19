#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>      
#include <sys/wait.h>   

int main() {
    char *args[2] = {"date", NULL};
    int status, pid, x = 9;
    pid = fork();
    if (0 == pid) {      
        x++;
        pid = fork();
        if (0 == pid) {  
            execvp(args[0], args);
        } else {         
            wait(&status);
        }
    } else {             
        x--;
    }
    printf("x=%d\n", x);
    return 0;
}