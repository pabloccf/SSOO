#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void tratarSennal();

int main(){
    int status;
    pid_t pid;

    switch (fork()){
    case -1: //Error
        perror("Fork error");
        fprintf(stderr,"errno: %i\n",errno);
        exit(EXIT_FAILURE);

    case 0: //Hijo
        signal(SIGUSR1,tratarSennal);
        for (int i = 0; i < 5; i++){
            pause();
        }
        exit(EXIT_SUCCESS);
    
    default: //Padre
        for (int i = 0; i < 5; i++){
            sleep(1);
            kill(pid, SIGUSR1);
        }
        pid=wait(&status);
        if (pid>0){
            if(WIFEXITED(status)){
                printf("El hijo con PID %i ha salido con estado: %i\n",pid,WEXITSTATUS(status));
            }
            else if(WIFSIGNALED(status)){
                printf("El hijo con PID %i ha sido finalizado con la señal: %i\n",pid,WTERMSIG(status));
            }
            else if(WIFSTOPPED(status)){
                printf("El hijo con PID %i ha sido parado con una señal: %i\n",pid,WSTOPSIG(status));
            }
        }
        
        else{
            printf("Error en la llamada a la funcion wait\n");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }
}

void tratarSennal(){
    printf("Señal recibida\n");
}