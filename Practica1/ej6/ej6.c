#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>

void manejador();
void alarma(int segundos);
int cont=0;
int main(int argc, char* argv[]){
    if(signal(SIGALRM, manejador)==SIG_ERR){
        perror("Signal error");
        fprintf(stderr,"errno: %i\n",errno);
        exit(EXIT_FAILURE);
    }

    alarma(5);
    alarma(3);
    while(1){
        alarma(1);
    }
}

void alarma(int segundos){
    alarm(segundos);
    pause();
}

void manejador(){
    printf("RING\n");
    cont++;

    if(cont==4){
        kill(getpid(),SIGKILL);
    }
}