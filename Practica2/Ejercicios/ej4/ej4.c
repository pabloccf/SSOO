#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int global=0;
void* incrementar();
int main(int argc, const char* argv[]){
    const int nhilos=2;
    pthread_t hilos[nhilos];
    for (int i = 0; i < nhilos; i++){
        if(pthread_create(&hilos[i],NULL,(void*)incrementar,NULL)){
            fprintf(stderr,"Error creando la hebra\n");
            exit(EXIT_FAILURE);
        }
    }
    for (int i = 0; i < nhilos; i++){
        if(pthread_join(hilos[i],NULL)){
            fprintf(stderr,"Error al esperar la hebra\n");
            exit(EXIT_FAILURE);
        }
        printf("Hebra %i recogida\n",i);
    }
    printf("El valor de la variable global es: %i\n",global);
    exit(EXIT_SUCCESS);
}

void* incrementar(){
    printf("Hola soy la hebra %lu\n",pthread_self());
    for (int i = 0; i < 10000; i++){
        global++;
    }
    pthread_exit(NULL);
}