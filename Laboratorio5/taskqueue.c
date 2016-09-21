#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>


pthread_cond_t *gate;
pthread_mutex_t mutex;
sem_t semaforo;
int termino;
void tareas(long thread){
	printf("Proceso %ld hara su tarea\n",thread);
 

}
void *dormir(void *thread){
	long my_rank = (long) thread;
	int p=my_rank;

	while(1){
		printf("Proceso %ld ira a dormir\n",my_rank);
		pthread_mutex_lock(&mutex);
		sem_post(&semaforo);	
		pthread_cond_wait(&gate[p], &mutex);
		pthread_mutex_unlock(&mutex);
		if(termino==0)
			tareas(my_rank);
		else
			break;
}
	return NULL;
}
int main (int argc, char * argv[])
{
	//pthread_cond_t *gate;
	int thread_count;
	long thread;		
	sem_init(&semaforo,1,0);
	termino=0;
	pthread_t* thread_handles;
	thread_count=strtol(argv[1],NULL,10);
	gate=malloc (thread_count*sizeof(pthread_cond_t));
	thread_handles=malloc (thread_count*sizeof(pthread_t));
	for (thread=0;thread<thread_count;thread++){
		pthread_create(&thread_handles[thread],NULL,dormir,(void*)thread);
		sem_wait(&semaforo);	
	}
	//sleep(3);
	for (thread=0;thread<thread_count;thread++)
		pthread_cond_signal(&gate[thread]);

	sleep(3);
	termino=1;
	for (thread=0;thread<thread_count;thread++)
		pthread_cond_signal(&gate[thread]);

	for (thread=0;thread<thread_count;thread++)
		pthread_join(thread_handles[thread],NULL);

	return 0;
}
