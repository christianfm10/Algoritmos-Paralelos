#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

//IMPLEMENTACIÓN DE MPI_BROADCAST


void broadcast(void* dato, int contador, MPI_Datatype tipo_dato, int raiz, MPI_Comm comunicador) {
  int rango;
  MPI_Comm_rank(comunicador, &rango);
  int size;
  MPI_Comm_size(comunicador, &size);
  if (rango == raiz) {
    for (int i = 1; i < size; i++) {
        MPI_Send(dato, contador, tipo_dato, i, 0, comunicador);
    }
  } else {
    MPI_Recv(dato, contador, tipo_dato, raiz, 0, comunicador, MPI_STATUS_IGNORE);
  }
}

int main(int argc, char** argv) {
  MPI_Init(&argc, &argv);
  int rango;
  MPI_Comm_rank(MPI_COMM_WORLD, &rango);
  int dato;
  if (rango == 0) {
    dato = 6;
    printf("Broadcast: Proceso 0 transmitiendo dato %d a los demás procesos\n", dato);
    broadcast(&dato, 1, MPI_INT, 0, MPI_COMM_WORLD);
  } else {
    broadcast(&dato, 1, MPI_INT, 0, MPI_COMM_WORLD);
    printf("Proceso %d recibe el dato %d del proceso raiz\n", rango, dato);
  }
  MPI_Finalize();
}








