#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    if(argc!=2){
        fprintf(stderr,"Numero de argumentos no validos. Introduzca el numero al que desea calcularle el factorial\n");
        exit(EXIT_FAILURE);
    }
    int numero=atoi(argv[1]);
    int fact=1;
    for(int i=2;i<=numero;i++){
        fact*=i;
    }
    printf("El factorial de %i es %i.\n", numero, fact);
}