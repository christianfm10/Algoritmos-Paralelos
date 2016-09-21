
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#define MAX 40
/*char *strtok(char *str, const char *delim);
No se debe usar strtok en un ámbito multithreading, debido a que el prámetro “str” es una variable en caché compartida entre todos los threads. Por lo cual se puede dar el caso que un thread sobrescriba los datos que eran usados por otro thread.
Una solución para este problema es el uso de strtok_r el cual dispone de un puntero para no perder de vista que la función se encuentra en la cadena de entrada.*/
int thread_count;
sem_t *sems;
void *Tokenize(void* rango){
    long my_rank = (long) rango;
    int count;
    int next = (my_rank + 1)%thread_count ;
    char *fg_rv;
    char my_line[MAX];
    char *my_string;
    sem_wait(&sems[my_rank]);
//    char *saveptr;	
    fg_rv = fgets(my_line,MAX,stdin);
    sem_post(&sems[next]);

    while(fg_rv != NULL){
        printf("Thread %ld > my line  = %s",my_rank,my_line);
        count=0;
        my_string = strtok(my_line,"\t \n");
//        my_string = strtok_r(my_line, "\t \n", &saveptr);
        while(my_string !=NULL){
            count++;
            printf("Thread %ld > string %d = %s \n",my_rank,count,my_string);
            my_string=strtok(NULL," \t \n");
//            my_string = strtok_r(NULL, "\t \n", &saveptr);

        }
        sem_wait(&sems[my_rank]);
        fg_rv=fgets(my_line,MAX,stdin);
        sem_post(&sems[next]);

    }
    return NULL;
}

int main()
{
    long thread;
    pthread_t *thread_handles;
    thread_count = 2;
    thread_handles = new pthread_t[thread_count];
    sems = new sem_t[thread_count];
    sem_init(&sems[0],0,1);
    for(int i=1;i<thread_count;i++)
        sem_init(&sems[i],0,0);

    for(thread =0;thread<thread_count;thread++)
        pthread_create(&thread_handles[thread],NULL,Tokenize,(void*)thread);
    for(thread=0;thread< thread_count;thread++)
        pthread_join(thread_handles[thread],NULL);
    return 0;
}
