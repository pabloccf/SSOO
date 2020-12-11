#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

void* cuentalineas(void* fichero);

int main(int argc, char* argv[]){
    if(argc<2){
        fprintf(stderr,"Numero de argumentos invalido. Debes pasarle al menos un fichero\n");
        exit(EXIT_FAILURE);
    }

    const int nhilos=argc-1;
    int total=0;
    int*  nlineas;
    pthread_t hilos[nhilos];
    for (int i = 0; i < nhilos; i++){
        if(pthread_create(&hilos[i],NULL,cuentalineas,(void*) argv[i+1])){
            fprintf(stderr,"Error creando el hilo %i\n",i);
            exit(EXIT_FAILURE);
        }
    }
    
    for (int i = 0; i < nhilos; i++){
        if (pthread_join(hilos[i],(void**) &nlineas)){
            fprintf(stderr,"Error recogiendo el hilo %i\n",i);
            exit(EXIT_FAILURE);
        }

        printf("El fichero %s tiene %i lineas\n",argv[i+1],*nlineas);
        total+= *nlineas;
    }
    
    printf("Entre todos los ficheros hay %i lineas\n",total);
}

void* cuentalineas(void* fichero){
    printf("Contando las lineas del fichero %s\n",fichero);
    int* nlineas=malloc(sizeof(int));
    FILE* f= fopen(fichero, "r");
    *nlineas=0;
    char s[128];

    if(f==NULL){
        perror("Error al abrir el fichero");
        fprintf(stderr,"errno: %i\n",errno);
        exit(EXIT_FAILURE);
    }

    while(fgets(s,128,f)){
        *nlineas=*nlineas+1;
    }
    pthread_exit((void*)nlineas);
}