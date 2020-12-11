#include <stdio.h>
#include <stdlib.h>
#include <errno.h> 
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char* argv[]){
    if(argc<3){
        fprintf(stderr,"Numero de argumentos no valido. Introduzca dos numeros.\n");
        exit(EXIT_FAILURE);
    }
    
    int status;
    char* ejecutable="./factorial";
    pid_t pid;
    for(int i=1;i<3;i++){
        switch (fork()){
        case -1: //Error
            perror("Fork error");
            fprintf(stderr,"errno: %i\n",errno);
            exit(EXIT_FAILURE);
        
        case 0: //Hijo
            if(execlp(ejecutable, ejecutable, argv[i], NULL)==1){
                perror("Exec error");
                fprintf(stderr,"errno: %i\n", errno);
                exit(EXIT_FAILURE);
            }
            exit(EXIT_SUCCESS);
        }
    }

    for (int i = 0; i < 2; i++){ //Padre
        pid=wait(&status);
        if(pid>0){
            if(WIFEXITED(status)){
                printf("El hijo con PID %i ha salido con estado: %i\n",pid, WEXITSTATUS(status));
            }
            else if(WIFSIGNALED(status)){
                printf("El hijo con PID %i ha terminado con señal: %i\n",pid, WTERMSIG(status));
            }
            else if(WIFSTOPPED(status)){
                printf("El hijo con PID %i ha sido parado con señal: %i\n",pid, WSTOPSIG(status));
            }
        }
        else{
            fprintf(stderr,"Error en la llamada a la funcion wait\n");
            exit(EXIT_FAILURE);
        }
    }

    exit(EXIT_SUCCESS);
}