#include <mpi.h>
#include <string.h>
#include <stdio.h>
const int  MAX_STRING=100;

int main(int argc, char *argv[])
{
    int a=0;
    int comm_sz;
    int my_rank;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
    if(my_rank == 0){
	printf("Proceso %d of %d!\n",my_rank,comm_sz);
        MPI_Send(&a,1,MPI_INT,1,0,MPI_COMM_WORLD);

    } 
    else{
      
        MPI_Recv(&a,1,MPI_INT,my_rank-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	printf("Proceso %d of %d!\n",my_rank,comm_sz);
	if(my_rank!=comm_sz-1)
        	MPI_Send(&a,1,MPI_INT,my_rank+1,0,MPI_COMM_WORLD);
   
    }
    MPI_Finalize();
    return 0;
}

