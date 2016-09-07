#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#define FROM_MASTER 1
#define FROM_WORKER 2

int main(int argc, char *argv[]) {
	int n=32;
	int B[n],A[n][n],V[n];
	int  rank,size,division,tipo,destino;

	MPI_Status status;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    	MPI_Comm_size(MPI_COMM_WORLD, &size);
        division = n/(size);
	if(rank==0){
	      for (int i=0; i<n; i++)
		    V[i]= 1;
	      for (int i=0; i<n; i++)
		 for (int j=0; j<n; j++)
		    A[i][j]= 2;



	      tipo = FROM_MASTER;
	      for (destino=1; destino<size; destino++)
	     	 MPI_Send(&V, n, MPI_INT, destino, tipo,MPI_COMM_WORLD);
	    
			
		for(int i=0;i<n;i++)
			for(int j=division,count=0,destino=1;j<n;j=j+division,destino++,count++)
				MPI_Send(&A[i][j], division, MPI_INT, destino, tipo,MPI_COMM_WORLD);


	      
	}
	else{
	      tipo=FROM_MASTER;	

	      MPI_Recv(&V, n, MPI_INT, 0, tipo, MPI_COMM_WORLD, &status);
              for(int i=0,count=0;count<n;i++,count++)
	    	  MPI_Recv(&A[i], division, MPI_INT, 0, tipo, MPI_COMM_WORLD, &status);

}
	MPI_Barrier(MPI_COMM_WORLD);	

	for(int i=0;i<n;i++){
		B[i]=0;
		for(int j=0;j<division;j++)
			B[i]+=A[i][j]*V[i];

	}
	MPI_Reduce(&B,&V,n,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);	
	if(rank==0)	
	for (int j=0; j<n; j++)
		 printf("GG :%d %d \n",V[j],rank);

}
	
