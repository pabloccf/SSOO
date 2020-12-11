#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>

typedef struct{
    int* vector;
    int hebras;
    int i;
}Vector;

void rellenaVector(int* vector){
    srand(time(NULL));
    for (int i = 0; i < 10; i++){
        vector[i]=((rand()%9)+1);
    }
}

void imprimeVector(int* vector){
    printf("El vector es:\n");
    printf("| ");
    for (int i = 0; i < 10; i++){
        printf("%d | ",vector[i]);
    }
    printf("\n");
}

void* sumaVector(void* d){
    int* suma=malloc(sizeof(int));
    *suma=0;
    Vector *v;
    v=(Vector*) d;
    if(v->hebras==2){
        int j=v->i;
        for ( j = 0; (v->i)+5; j++){
            printf("Hola, soy la hebra %lu\n", pthread_self());
            *suma=*suma+v->vector[j];
            sleep(1);
        }
        
        v->i=v->i+5;
        pthread_exit((void**)suma);
    }
    else{
        printf("Hola, soy la hebra %lu\n", pthread_self());
        int j=v->i;
        for(j;j<(v->i)+2;j++){
            printf("Hola, soy la hebra %lu\n", pthread_self());
            *suma=*suma+v->vector[j];
            sleep(1);
        }
        v->i=v->i+2;
        pthread_exit((void**)suma);
    }
}

int main(int argc, char const *argv[]){
    Vector* v=malloc(sizeof(Vector));
    if(argc!=2){
        printf("Error, numero de argumentos no validos\n");
        exit(EXIT_FAILURE);
    }
    v->hebras = atoi(argv[1]);                          //Guardamos en v->hebras el numero de hebras que queremos hacer
    v->i = 0;                                           //Ponemos el iterador a 0 para luego en la funcion sumaVector comenzar desde la posicion 0 del vector 

    if (v->hebras != 2 && v->hebras != 5){              //Comprobamos que se haya llamado al programa de forma adecuada introduciendo un 2 o un 5
        printf("Error, llame al programa asi:\n");
        printf("./ej3 2 o /ej3 5\n");
        exit(EXIT_FAILURE);
    }
    
    v->vector = (int *)malloc (10*sizeof(int));         //Reservamos memoria para el vector v->vector
    rellenaVector(v->vector);                           //Rellenamos el vector con numeros aleatorios del 1 al 9
    imprimeVector(v->vector);                           //Imprimimos el vector para comprobar luego el resultado

    pthread_t thread[v->hebras];                        //Creamos un vector para almacenar los identificadores de los hilos, que seran 2 o 5 segun haya indicado el usuario
    int *sumaLinea, suma = 0;                           //sumaLinea es el puntero que recibirá los valores devueltos por los hilos, suma almacenará la suma de los 10 valores del vector
    
    printf("Se pasaran a crear %d hebras para sumar los valores del vector\n", v->hebras);

    for (int i = 0; i < v->hebras; i++){                //Crearemos tantos hilos como haya indicado el usuario por linea de argumentos
        if(pthread_create(&(thread[i]), NULL, (void*) sumaVector, (void*) v)){
            printf("Error en la creacion de la hebra. Codigo de error %d\n", errno);
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < v->hebras; i++){                //Crearemos tantos hilos como haya indicado el usuario por linea de argumentos
        if(pthread_join(thread[i], (void**) &sumaLinea)){
            printf("Error al esperar la hebra. Codigo de error %d\n", errno);
            exit(EXIT_FAILURE);
        } 
        suma = suma + *sumaLinea;                       //En cada iteración del bucle sumamos el valor devuelto por la hebra recogida a la suma total de valores
    }

    printf("La suma de los numeros de todos los valores es: %d\n", suma);
    exit(EXIT_SUCCESS);
}     


