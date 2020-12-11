#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* aleatorio();

int main(){
    int n=10;
    float total=0,*subtotal;
    pthread_t hilos[n];
    srand48(time(NULL));

    for (int i = 0; i < n; i++){
        if (pthread_create(&hilos[i],NULL,(void*) aleatorio,NULL)){
            perror("pthread_create error");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < n; i++){
        if (pthread_join(hilos[i],(void**) &subtotal)){
            perror("pthread_create error");
            exit(EXIT_FAILURE);
        }
        
        printf("Valor recibido: %0.2f\n",*subtotal);
        total+=*subtotal;
    }
    printf("La suma total es: %0.2f\n",total);
    
    exit(EXIT_SUCCESS);
}

void* aleatorio(){
    float f1=drand48()*10, f2=drand48()*10;
    float* f3=calloc(1,sizeof(float));
    *f3=f1+f2;
    printf("%0.2f + %0.2f = %0.2f\n",f1,f2,*f3);

    pthread_exit((void *)f3);
}