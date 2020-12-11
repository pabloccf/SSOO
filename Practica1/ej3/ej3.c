#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void calculadora(char* ejecutable);
int main(int argc, char* argv[]){
    if(argc<4){
        fprintf(stderr,"Numero de argumentos invalido. Debe especificar al menos un fichero\n");
        exit(EXIT_FAILURE);
    }
    int status;
    pid_t pid;

    for(int i=0;i<2;i++){
        switch (fork()){
        case -1: //Error
            perror("Fork error");
            fprintf(stderr,"errno: %i\n",errno);
            exit(EXIT_FAILURE);

        case 0: //Hijo
            if(i==0){
                calculadora(argv[1]);
            }
            else{
                execlp(argv[2], argv[2], NULL);
            }
            exit(EXIT_SUCCESS);
        }
    }
    for(int i=0;i<2;i++){
        pid=wait(&status);
        if(pid<0){
            if(WIFEXITED(status)){
                printf("El hijo con PID %i ha salido con estado: %i\n",pid,WEXITSTATUS(status));
            }
            else if(WIFSIGNALED(status)){
                printf("El hijo con PID %i ha terminado con señal: %i\n",pid,WTERMSIG(status));
            }
            else if(WIFSTOPPED(status)){
                printf("El hijo con PID %i ha sido parado con una señal: %i\n",pid,WSTOPSIG(status));
            }
        }
        else{
            perror("Wait error");
            fprintf(stderr,"errno: %i",errno);
            exit(EXIT_FAILURE);
        }
    }
    exit(EXIT_SUCCESS);
}

void calculadora(char* ejecutable){
    execlp(ejecutable,ejecutable,NULL);
}

