#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#define LIMITE 20
int main(int argc, char** argv) {
	MPI_Init(&argc,&argv);
	int rango, tareas;
	MPI_Comm_rank(MPI_COMM_WORLD, &rango);
  	MPI_Comm_size(MPI_COMM_WORLD, &tareas);
	if (tareas != 2) {
		printf("Deben de ser 2 procesos.");
		MPI_Abort(MPI_COMM_WORLD, 1);
	}
	int count=0;
	int otro=(rango + 1)%2;
	while(count < LIMITE){

		if(rango == count % 2){
			count++;
			MPI_Send(&count, 1, MPI_INT, otro, 0, MPI_COMM_WORLD);
			printf("%d envia e incrementa contador a %d para %d\n",rango, count, otro);
		}
		else{
			MPI_Recv(&count, 1, MPI_INT, otro, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		     	printf("%d recibe contador %d de %d\n",rango, count, otro);
		}
}

	MPI_Finalize();


	
}

//#include <mpi.h>
//#include <stdio.h>
//#include <stdlib.h>
//#define LIMITE 20
//int main(int argc, char** argv) {
//	MPI_Init(&argc,&argv);
//	int rango, tareas;
//	MPI_Comm_rank(MPI_COMM_WORLD, &rango);
//  	MPI_Comm_size(MPI_COMM_WORLD, &tareas);
//	if (tareas != 2) {
//		printf("Deben de ser 2 procesos.");
//		MPI_Abort(MPI_COMM_WORLD, 1);
//	}
//	int count=0;
//	int otro=(rango + 1)%2;
//	while(count < LIMITE){
//		while(rango!=count%2){
//			 MPI_Recv(&count, 1, MPI_INT, otro, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
//		}
		//if(count%2 == 0){
//			count++;
//			MPI_Send(&count, 1, MPI_INT, otro, 0, MPI_COMM_WORLD);
//			printf("%d envia e incrementa contador a %d para %d\n",rango, count, otro);
		//}
		//else{
		
//}
//	MPI_Finalize();
	
//}

