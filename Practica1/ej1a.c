#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> //Para cargar el tipo pid_t
#include <unistd.h> //Para utilizar la funcion fork
#include <errno.h> //Para utilizar la variable errno. 
#include <sys/wait.h> //Para utilizar la funcion wait

int main(){
    int n, status;
    pid_t pid;

    printf("Introduce el numero de procesos totales: ");
    scanf("%i", &n);

    for(int i=0;i<n;i++){
        switch (fork()){
        case -1: //Error
            perror("Fork error\n");
            fprintf(stderr,"errno: %i\n",errno);
            exit(EXIT_FAILURE);

        case 0: //Hijo
            printf("Soy el hijo con PID %i. El PID de mi padre es %i\n",getpid(),getppid());
            exit(EXIT_SUCCESS);
            break;
        }
    }

    for(int i=0;i<n;i++){
        pid=wait(&status); //Almacena en la variable pid 
        if(pid>0){
            if(WIFEXITED(status)){
                printf("El hijo con PID %i ha salido con estado: %i\n",pid,WEXITSTATUS(status));
            }
            else if(WIFSIGNALED(status)){
                printf("El hijo con PID %i ha sido finalizado con la señal: %i\n",pid,WTERMSIG(status));
            }
            else if(WIFSTOPPED(status)){
                printf("El hijo con PID %i ha sido parado con la señal: %i\n",pid,WSTOPSIG(status));
            }
        }
        else{
            printf("El proceso padre no ha esperado a que acabe el proceso hijo\n");
            exit(EXIT_FAILURE);
        }
    }

    exit(EXIT_SUCCESS);
}