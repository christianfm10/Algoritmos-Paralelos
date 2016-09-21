
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
double *A;
double *x;
double *y;
int m;
int n;
int thread_count;
double timeval_diff(struct timeval *a, struct timeval *b)
{
 return
   (double)(a->tv_sec + (double)a->tv_usec/1000000) -
   (double)(b->tv_sec + (double)b->tv_usec/1000000);
}
void *Mat_vect(void *rango){
    long my_rank = (long)rango;
    int i,j;
    int local_m=m/thread_count;
    int my_first_row =my_rank*local_m;
    int my_last_row = (my_rank+1)*local_m-1;
    for(i=my_first_row;i<=my_last_row;i++){
        y[i]=0.0;
        for(j=0;j<n;j++)
            y[i] += A[i*n+j]*x[j];
    }
    return NULL;
}
int main(int argc, char *argv[])
{	
    long thread;
    m=8000;
    n=8000;
    struct timeval t_ini, t_fin;
    double secs;
    pthread_t *thread_handles;
    thread_count = strtol(argv[1],NULL,10);
    thread_handles = malloc(sizeof(pthread_t)*thread_count);
    A = malloc(sizeof(double)*n*m);
    x = malloc(sizeof(double)*n);
    y = malloc(sizeof(double)*m);
    for(int i=0;i<m;i++)
        for(int j=0;j<n;j++)
            A[i*n+j]=24213144;
    for(int i=0;i<n;i++)
        x[i]=22423215;
    gettimeofday(&t_ini, NULL);	
    for(thread =0;thread<thread_count;thread++)
        pthread_create(&thread_handles[thread],NULL,Mat_vect,(void*)thread);
    for(thread=0;thread< thread_count;thread++)
        pthread_join(thread_handles[thread],NULL);
    gettimeofday(&t_fin, NULL);
    secs = timeval_diff(&t_fin, &t_ini);
    printf("%.16g milliseconds\n", secs * 1000.0);
   // for(int i=0;i<n;i++)
   //    printf("%lf,",y[i]);
   // printf("\n");
    return 0;
}

