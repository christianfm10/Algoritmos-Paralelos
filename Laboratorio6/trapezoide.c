/*#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
//mpiexec -n 4 ./trapezoide
double f(double x){
	return 0.2+25*x-200*x*x+675*x*x*x-900*x*x*x*x+400*x*x*x*x*x;

}
double Trap(double left_endpt,double right_endpt,int trap_count, double base_len){
	double estimate,x;
	int i;
	estimate= (f(left_endpt) + f(right_endpt))/2.0;
	for(i = 1; i <=trap_count-1;i++){
		x= left_endpt+ i*base_len;
		estimate += f(x);
	}
	estimate = estimate*base_len;
	return estimate;
}

int main(int argc, char *argv[]){
	int my_rank, comm_sz, n=3,local_n;
	double a=0.0, b=0.8,h, local_a,local_b;
	double local_int, total_int;
	int source;
	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
	MPI_Comm_size(MPI_COMM_WORLD,&comm_sz);
	h=(b-a)/n;
	local_n = n/comm_sz;
	local_a = a+ my_rank*local_n*h;
	local_b = local_a + local_n*h;	
	local_int = Trap(local_a,local_b,local_n,h);
	if(my_rank != 0){
		MPI_Send(&local_int, 1 , MPI_DOUBLE,0,0,MPI_COMM_WORLD);
	} else{
		total_int= local_int;
		for(source = 1;source < comm_sz;source++){
			MPI_Recv(&local_int, 1,MPI_DOUBLE,source,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			total_int+= local_int;		
		}
	}
	if(my_rank == 0){
		printf("With n = %d trapezoids,our estimate\n",n);
		printf("of the integral from %f to %f = %.15e\n",a,b,total_int);
	}
	MPI_Finalize();
	return 0;

}

double h;
int local_n;
double a=0.0,b=0.8;
double total_int=0;
int n=3;
void *trap(void *thread){
	double local_a,local_b,local_int;
	long my_rank=(long)thread;
	local_a = a+ my_rank*local_n*h;
	local_b = local_a + local_n*h;	
	local_int= Trap(local_a,local_b,local_n,h);
	total_int+= local_int;		

}
int main(int argc, char *argv[])
{	
    long thread;
    h=(b-a)/n;

    pthread_t *thread_handles;
    thread_count = strtol(argv[1],NULL,10);
    thread_handles = malloc(sizeof(pthread_t)*thread_count);
    local_n = n/thread_count;
   
    for(thread =0;thread<thread_count;thread++)
        pthread_create(&thread_handles[thread],NULL,t,(void*)thread);
    for(thread=0;thread< thread_count;thread++)
        pthread_join(thread_handles[thread],NULL);
    printf("With n = %d trapezoids,our estimate\n",n);
    printf("of the integral from %f to %f = %.15e\n",a,b,total_int);
    return 0;
}

*/
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
pthread_mutex_t mutex;
sem_t *semaforo;
double h;
int local_n;
int thread_count;
double a=0.0,b=0.8;
double total_int=0;
int n=3;
double f(double x){
	return 0.2+25*x-200*x*x+675*x*x*x-900*x*x*x*x+400*x*x*x*x*x;

}
double Trap(double left_endpt,double right_endpt,int trap_count, double base_len){
	double estimate,x;
	int i;
	estimate= (f(left_endpt) + f(right_endpt))/2.0;
	for(i = 1; i <=trap_count-1;i++){
		x= left_endpt+ i*base_len;
		estimate += f(x);
	}
	estimate = estimate*base_len;
	return estimate;
}



int flag=0;
void *trap(void *thread){
	double local_a,local_b,local_int;
	long my_rank=(long)thread;
	local_a = a+ my_rank*local_n*h;
	local_b = local_a + local_n*h;	
	local_int= Trap(local_a,local_b,local_n,h);
	//while(flag!=my_rank);
	sem_wait(&semaforo[(int)my_rank]);	
	//pthread_mutex_lock(&mutex);
	total_int+= local_int;	
	//pthread_mutex_unlock(&mutex);
	sem_post(&semaforo[(int)my_rank+1]);
	//flag=(flag+1)%thread_count;	
	return NULL;	

}
int main(int argc, char *argv[])
{	
    long thread;
    h=(b-a)/n;
    pthread_mutex_init(&mutex,NULL);
    pthread_t *thread_handles;
    thread_count = strtol(argv[1],NULL,10);
    thread_handles = malloc(sizeof(pthread_t)*thread_count);
    local_n = n/thread_count;
    semaforo=malloc(sizeof(sem_t)*thread_count);
    sem_init(&semaforo[0],1,1);
    for(int i=1;i<thread_count;i++)
	sem_init(&semaforo[i],1,0);
    for(thread =0;thread<thread_count;thread++)
        pthread_create(&thread_handles[thread],NULL,trap,(void*)thread);
    for(thread=0;thread< thread_count;thread++)
        pthread_join(thread_handles[thread],NULL);
    printf("With n = %d trapezoids,our estimate\n",n);
    printf("of the integral from %f to %f = %.15e\n",a,b,total_int);
    return 0;
}


