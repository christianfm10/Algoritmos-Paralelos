#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define FROM_MASTER 1
#define FROM_WORKER 2
int main (int argc, char *argv[]){

	int Row=4,Column=4,Row1=4,Column1=4;

 	int  rank,tareas, destino, origen, tipo, mensaje,temp,division,extra, trabajadores; 
  	int A[Row][Column],B[Row1][Column1],C[Row][Column1];

	MPI_Status status;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&tareas);
	trabajadores = tareas-1;
	if (rank == 0)
	   {
	      for (int i=0; i<Row; i++)
		 for (int j=0; j<Column; j++)
		    A[i][j]= 1;
	      for (int i=0; i<Row1; i++)
		 for (int j=0; j<Column1; j++)
		    B[i][j]= 2;


	      division = Row/(trabajadores);
	      extra = Row%(trabajadores);
	      temp = 0;
	      tipo = FROM_MASTER;
	      for (destino=1; destino<tareas; destino++)
	      {

		 if(destino<=extra)
		 	mensaje=division+1;
		 else
			mensaje=division;
		 	
		 printf("Enviando %d filas a la tarea %d desde la fila %d\n",mensaje,destino,temp);
		 MPI_Send(&temp, 1, MPI_INT, destino, tipo, MPI_COMM_WORLD);
		 MPI_Send(&mensaje, 1, MPI_INT, destino, tipo, MPI_COMM_WORLD);
		 MPI_Send(&A[temp][0], mensaje*Column, MPI_INT, destino, tipo,
		           MPI_COMM_WORLD);
		 MPI_Send(&B, Row1*Column1, MPI_INT, destino, tipo, MPI_COMM_WORLD);
		 temp = temp + mensaje;
	      }


	      tipo = FROM_WORKER;
	      for (int i=1; i<tareas; i++)
	      {
		 origen = i;
		 MPI_Recv(&temp, 1, MPI_INT, origen, tipo, MPI_COMM_WORLD, &status);
		 MPI_Recv(&mensaje, 1, MPI_INT, origen, tipo, MPI_COMM_WORLD, &status);
		 MPI_Recv(&C[temp][0], mensaje*Column1, MPI_INT, origen, tipo, 
		          MPI_COMM_WORLD, &status);
		 printf("Recibiendo de la tarea %d\n",origen);
	      }




	      for (int i=0; i<Row; i++)
	      {
		 printf("\n"); 
		 for (int j=0; j<Column1; j++) 
		    printf("%d   ", C[i][j]);
	      }
	      printf("\n");
	   }
	   else
	   {
	      tipo = FROM_MASTER;
	      MPI_Recv(&temp, 1, MPI_INT, 0, tipo, MPI_COMM_WORLD, &status);
	      MPI_Recv(&mensaje, 1, MPI_INT, 0, tipo, MPI_COMM_WORLD, &status);
	      MPI_Recv(&A, mensaje*Column, MPI_INT, 0, tipo, MPI_COMM_WORLD, &status);
	      MPI_Recv(&B, Row1*Column1, MPI_INT, 0, tipo, MPI_COMM_WORLD, &status);

	      for (int k=0; k<Column1; k++)
		 for (int i=0; i<mensaje; i++)
		 {
		    C[i][k] = 0.0;
		    for (int j=0; j<Column; j++)
		       C[i][k] = C[i][k] + A[i][j] * B[j][k];
		 }
	      tipo = FROM_WORKER;
	      MPI_Send(&temp, 1, MPI_INT, 0, tipo, MPI_COMM_WORLD);
	      MPI_Send(&mensaje, 1, MPI_INT, 0, tipo, MPI_COMM_WORLD);
	      MPI_Send(&C, mensaje*Column1, MPI_INT, 0, tipo, MPI_COMM_WORLD);
	   }
	   MPI_Finalize();



}


