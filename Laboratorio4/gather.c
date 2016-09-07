#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#define FROM_MASTER 1
#define FROM_WORKER 2
double timeval_diff(struct timeval *a, struct timeval *b)
{
 return
   (double)(a->tv_sec + (double)a->tv_usec/1000000) -
   (double)(b->tv_sec + (double)b->tv_usec/1000000);
}
int main (int argc, char *argv[]){
    struct timeval t_ini, t_fin;
    double secs;
	int Row=1024, Column=1024;
	//int A[Row][Column];
	//int local_x[Column];		//int *matrix = malloc(R * P * sizeof(int));
        int *local_x=malloc(Column*sizeof(int));//malloc(sizeof(int)*Column);
	 int *local_y=malloc(Column*sizeof(int));
	int *A=malloc(Row*Column*sizeof(int));
	int destino, tipo, mensaje,temp,extra,division,tareas,rank;
	//int *local_x=int 
    gettimeofday(&t_ini, NULL);	
	MPI_Status status;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&tareas);
//int m;//filas
//int n;//columnas;

  		      division = Row/(tareas);
  for (int j=0; j<Column/tareas; j++)
		    local_x[j]= 2;


	if (rank == 0)
	   {
	      for (int i=0; i<Row; i++){
		 for (int j=0; j<Column; j++){

			int a=rand()%50;
			while(a<=0){
				a=rand()%50;}
		   	A[i*Column+j]=1;
		
	
		}
	 }

	      extra = Row%(tareas);
	      temp = 1;
	      tipo = FROM_MASTER;
	
	  //    for (destino=1; destino<tareas; destino++)
	  //   	 MPI_Send(local_x, Column, MPI_INT, destino, tipo,MPI_COMM_WORLD);
	    
	      for (destino=1; destino<tareas; destino++)
	      {

		 if(destino<=extra)
		 	mensaje=division+1;
		 else
			mensaje=division;
		 	
		// printf("Enviando %d filas a la tarea %d desde la fila %d\n",mensaje,destino,temp);
		 MPI_Send(&temp, 1, MPI_INT, destino, tipo, MPI_COMM_WORLD);
		 MPI_Send(&mensaje, 1, MPI_INT, destino, tipo, MPI_COMM_WORLD);
		 MPI_Send(&A[temp], mensaje*Column, MPI_INT, destino, tipo, MPI_COMM_WORLD);
		 temp = temp + mensaje;
	      }



	      
	   }
	   else
	   {
	      tipo=FROM_MASTER;	
		// printf("GG :%d ",rank);
	    //  MPI_Recv(local_x, Column, MPI_INT, 0, tipo, MPI_COMM_WORLD, &status);
	      MPI_Recv(&temp, 1, MPI_INT, 0, tipo, MPI_COMM_WORLD, &status);
	      MPI_Recv(&mensaje, 1, MPI_INT, 0, tipo, MPI_COMM_WORLD, &status);
	      MPI_Recv(A, mensaje*Column, MPI_INT, 0, tipo, MPI_COMM_WORLD, &status);
	}
//	int *x;
	
//	x=new int[Column];	
	int *x=malloc(sizeof(int)*Column);
	//if(x ==NULL)
//		return 1;
//	int x[Column];
//	int local_i=j;
//	int local_ok=1;
	

	//for(int i=0;i<8;i=i+1)
	//if(rank==0)		
	MPI_Allgather(local_x,Column/tareas,MPI_INT,x,Column/tareas,MPI_INT,MPI_COMM_WORLD);
		// printf("Easdsa \n");
		MPI_Barrier(MPI_COMM_WORLD);	
	//for (int j=0; j<Column; j++)
	//	 printf("%d %d \n",x[j],rank);


	for(int local_i=0;local_i < mensaje;local_i++){
		local_y[local_i] = 0;

		for(int j=0;j<Column;j++)
			local_y[local_i]+=A[local_i*Column+j]*x[j];
	}
	 printf("hola");
	MPI_Gather(local_y,division,MPI_INT,local_x,division,MPI_INT,0,MPI_COMM_WORLD);
	if(rank==0)	
	for (int j=0; j<1000; j++)
		 printf("GG :%d %d \n",local_x[j],rank);

	if(rank==0);
	free(x);
	free(local_y);
	free(local_x);
	free(A);
	MPI_Finalize();
    gettimeofday(&t_fin, NULL);
    secs = timeval_diff(&t_fin, &t_ini);

    printf("%.16g milliseconds\n", secs * 1000.0);
  
}
