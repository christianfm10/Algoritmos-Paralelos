#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
/*4.6	Después de haber hecho las pruebas, concluyo que el rendimiento es similar si usamos un read write lock con preferecia al reader o con preferencia al writer. Pero también noté que dar preferencia al writer es más equitativo que dar preferencia al reader, pues al dar preferencia al reader aplazarán a los writers hasta que terminen todos los readers.*/
typedef struct {
	int N_Readers;
	int N_Writers;
	int N_Writers_Waiting;
	pthread_mutex_t mutex;
	pthread_cond_t reader_gate;
	pthread_cond_t writer_gate;
}rwlock_t;

		
void rwlock_rdlock( rwlock_t* x){
	pthread_mutex_lock(&(x->mutex));
	//while(x->N_Writers>0 || x->N_WritersWaiting>0) //Preferencia al writer
	while(x->N_Writers > 0)
        {
            pthread_cond_wait(&(x->reader_gate), &(x->mutex));
        }
	x->N_Readers++;
	pthread_mutex_unlock(&(x->mutex));	
	
}
void rwlock_wrlock( rwlock_t* x)
{
        pthread_mutex_lock(&(x->mutex));
        x->N_Writers_Waiting++;
        while(x->N_Readers>0 || x->N_Writers>0)
        {
            pthread_cond_wait(&(x->writer_gate), &(x->mutex));
        }
        x->N_Writers_Waiting--; x->N_Writers++;
        pthread_mutex_unlock(&(x->mutex));
}
void rwlock_rdunlock( rwlock_t* x){
	pthread_mutex_lock(&(x->mutex));
        x->N_Readers--;
        if(x->N_Readers==0 && x->N_Writers_Waiting>0)
            pthread_cond_signal(&(x->writer_gate));
        pthread_mutex_unlock(&(x->mutex));
}
void rwlock_wrunlock( rwlock_t* x)
{
        pthread_mutex_lock(&(x->mutex));
        x->N_Writers--;
        if(x->N_Writers_Waiting>0)
            pthread_cond_signal(&(x->writer_gate));
        //else //Preferencia al Writer
        pthread_cond_broadcast(&(x->reader_gate));
        pthread_mutex_unlock(&(x->mutex));
}
int rwlock_initial( rwlock_t* x){
	x->N_Readers=0;
	x->N_Writers=0;
	x->N_Writers_Waiting=0;
	pthread_cond_init(&(x->reader_gate),NULL);
	pthread_cond_init(&(x->writer_gate),NULL);
	pthread_mutex_init(&(x->mutex),NULL);
	return 1;
}
int rwlock_destroy( rwlock_t* x){
	pthread_cond_destroy(&(x->reader_gate));
	pthread_cond_destroy(&(x->writer_gate));
	pthread_mutex_destroy(&(x->mutex));
	return 1;
}
int main(int argc, char *argv[])
{
	rwlock_t lock;
	rwlock_initial(&lock);
	rwlock_rdlock(&lock);
	rwlock_wrlock(&lock);
	rwlock_rdunlock(&lock);
	rwlock_wrunlock(&lock);
}
	

