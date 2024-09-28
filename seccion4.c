//sudo su
//apt install stress

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

long nucle;

void *stress(void *data) {   
  long thread_id = (long)data;   
  char command[256];   
  snprintf(command, sizeof(command), "sudo stress --cpu %ld --timeout 120", nucle);

   printf("Hilo %ld: %s'\n", thread_id, command);   
  system(command);      
  printf("Hilo %ld: terminado.\n", thread_id);   
  return NULL;
}

int main(void) 
{   
  nucle = sysconf(_SC_NPROCESSORS_ONLN);   
  printf("ncleos: %ld\n", nucle);

   pthread_t *threads = malloc(nucle * sizeof(pthread_t));

   for (long i = 0; i < nucle; i++) {       
     pthread_create(&threads[i], NULL, stress, (void *)i);   
   
   }   
  
  for (long i = 0; i < nucle; i++) {       
    
    pthread_join(threads[i], NULL);   
  
  }

   printf("FIN.\n");   
  free(threads);    
  return 0;


}
