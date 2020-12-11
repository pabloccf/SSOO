#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> //Para cargar el tipo pid_t
#include <unistd.h> //Para utilizar la funcion fork
#include <errno.h> //Para utilizar la variable errno. 
#include <sys/wait.h> //Para utilizar la funcion wait

int main(){
    switch (fork()){
    case -1: //Error
        perror("Fork error\n");
        fprintf(stderr,"Errno: %i",errno);
        exit(EXIT_FAILURE);
    case 0: //Hijo
        printf("Soy el hijo con PID %i y mi padre tiene un PID %i\n",getpid(),getppid());
        exit(EXIT_SUCCESS);

    default: //Padre
        sleep(20);

        exit(EXIT_SUCCESS);
    }
}