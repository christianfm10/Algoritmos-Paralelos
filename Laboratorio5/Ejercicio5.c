#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
/*4.4 El número de threads si afecta el tiempo de ejecución, esto se debe a que la creación de un thread tiene un costo ya que implica la asignación de un contador de programa, una pila de ejecuión, separar espacio de memoria para el uso del thread, etc. De igual manera el destruir un thread conlleva un costo. Es por eso mientras más es el número de threads el tiempo de ejecuión promedio se ve más afectado.*/
int thread_count;
void *Hello(void *rank);
double timeval_diff(struct timeval *a, struct timeval *b)
{
 return
   (double)(a->tv_sec + (double)a->tv_usec/1000000) -
   (double)(b->tv_sec + (double)b->tv_usec/1000000);
}
int main(int argc, char *argv[]){
	struct timeval t_ini, t_fin;
	double secs;
	long thread;
	pthread_t* thread_handles;
	thread_count = strtol(argv[1],NULL,10);
	thread_handles = malloc(thread_count*sizeof(pthread_t));
	gettimeofday(&t_ini, NULL);	
	for(thread=0;thread<thread_count;thread++)
		pthread_create(&thread_handles[thread],NULL,Hello,(void*)thread);
	printf("Hello from the main thread\n");
	for(thread=0;thread<thread_count;thread++)
		pthread_join(thread_handles[thread],NULL);
	free(thread_handles);
        gettimeofday(&t_fin, NULL);
	secs = timeval_diff(&t_fin, &t_ini);
	printf("%.16g milliseconds\n", secs * 1000.0);

	return 0;
}

void *Hello(void *rank){
	return NULL; 	
}
