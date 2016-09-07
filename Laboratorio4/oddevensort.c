#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N 8
void OddEvenSort (int a[], int n)
{
    for (int i = 0 ; i < n ; i++)
    {
	 int temp;
         if (i & 1)
         {
             for (int j = 2 ; j < n ; j += 2)
             {     
		  temp = a[j-1];
                  if (a[j] < a[j-1]){
		      a[j-1]=a[j];
		      a[j]=temp;
		  }
                    
             }
          }
          else
          {  
              for (int j = 1 ; j < n ; j += 2)
              {
		   temp = a[j-1];
                   if (a[j] < a[j-1]){
		      a[j-1]=a[j];
		      a[j]=temp;
		   }
                     
              } 
          }
    }
}
int computeNeighbor(int phase, int rank, int size)
{
  int neighbor;
  if(phase % 2 != 0) {  
    if(rank % 2 != 0) {  
      neighbor = rank + 1;
    } else {  
      neighbor = rank - 1;
    }
  } else {  
    if(rank % 2 != 0) {  
      neighbor = rank - 1;
    } else {  
      neighbor = rank + 1;
    }    
}
  if(neighbor < 0 || neighbor >= size)
    neighbor = -1;
  return neighbor;
  }


void mergeArrays(int  arr[], int  neighborArr[], int  temp[], int size, int low_or_high)
{
  int i, j, k;
  i = j = k = 0;


  for(i = 0, j = 0, k = 0; i < size*2; i++)
  {
    if(j < size && k < size)
    {
      if(arr[j] < neighborArr[k])
      {
        temp[i] = arr[j];
        j++;
      } else {
        temp[i] = neighborArr[k];
        k++;
      }
    } else if(j < size) {
      temp[i] = arr[j];
      j++;
    } else {
      temp[i] = neighborArr[k];
      k++;
    }
  }

  if(low_or_high % 2 != 0)
    for(i = 0; i < size; i++)
      arr[i] = temp[i];
  else
    for(i = size, j=0; j < size; i++,j++)
      arr[j]= temp[i];
}

int main(int argc, char *argv[]) {
	int a[N];
	int recvArr[N];
	int temp[N*2];
	int fullArr[N*2];
	int  rank,size,numElements;
	MPI_Status status;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    	MPI_Comm_size(MPI_COMM_WORLD, &size);
	numElements = N/size;
	if(rank==0){
		for(int i=N,j=0;i>0;i--,j++)	
			a[j]=i;
		
		for(int start=numElements,destino=1;destino<size;start=start+numElements,destino++){
		 printf("Enviando %d elementos a la tarea %d desde la fila %d\n",numElements,destino,start);
			MPI_Send(&a[start], numElements, MPI_INT, destino, 1,MPI_COMM_WORLD);
		
}
		OddEvenSort(a,numElements);
		
			}
	else{

	    	MPI_Recv(&a, numElements, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
		OddEvenSort(a,numElements);

}	
	printf("\n");
    MPI_Barrier(MPI_COMM_WORLD);
      for(int phase=0;phase<size;phase++){
   	   int neighbor = computeNeighbor(phase, rank, size);
      if(neighbor >= 0 && neighbor < size)
      {

        MPI_Sendrecv(a, numElements, MPI_INT, neighbor, phase, 
               recvArr, numElements, MPI_INT, neighbor, phase, 
               MPI_COMM_WORLD, &status);


        if(rank < neighbor){
          mergeArrays(a, recvArr, temp, numElements, 1);

        } else {
          mergeArrays(a, recvArr, temp, numElements, 0);
        }
      }

	}	
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Gather(a, numElements, MPI_INT, fullArr, numElements, MPI_INT, 0, MPI_COMM_WORLD);
	if(rank==0)	
		for(int i=0;i<N;i++)
			printf("result: %d",fullArr[i]);
			
       MPI_Finalize();
}

