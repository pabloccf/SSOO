#include <pthread.h> 
#include <stdio.h> 
#include <unistd.h>

void *thread(void *vargp) 
{ 
    int error = 0; 

   /*En cuanto se haga el pthread_detach() se eliminará el estado de esta hebra. 
     Hacer un join() de esta hebra puede  provocar estados impredecibles*/ 
   error = pthread_detach(pthread_self()); 
   /* Manejar el error */ 
   //...	 
   sleep(2);   

   printf("Hebra que ha llamado a pthread_detach()\n"); 
   pthread_exit(NULL); 
} 

int main() 
{ 
   pthread_t tid; 

   pthread_create(&tid, NULL, thread, NULL); 
   
   printf("Soy el main() o hilo principal, invocando a pthread_exit(NULL)...\n");
   pthread_exit(NULL); 
   
   //¿Se imprime esta linea?
   /*
   Se ha invocado a pthread_exit(NULL); por lo que como cualquier otro hilo se termina (aunque sea el main() o hilo principal).
   El main() es el hilo principal o contenedor del resto de hilos, por lo que teóricamente todos los hilos
   deberían acabar al finalizar el main(), pero la invocación de  pthread_exit(NULL); está preparada para ello
   en conjunción con pthread_detach(),
   */
   printf("Soy el main() o hilo principal, terminando...\n");
}
