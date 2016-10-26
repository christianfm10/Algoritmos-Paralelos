#include <iostream>
#include <stdio.h>
#include <cuda_runtime.h>
#include <cuda.h>
#include <device_launch_parameters.h>
#define BLOCK 8
using namespace std;

__global__
void matrizEscalar(float* A, float B, float* C, int fil,int col){
	int i = blockIdx.y*blockDim.y + threadIdx.y;
	int j = blockIdx.x*blockDim.x + threadIdx.x;
	if ((i < fil) && (j < col))
		C[i*col + j] = B * A[i*col + j];
	
}
void matrizescalar(float* A, float B, float* C, int fil,int col) {
	int size = fil * col * sizeof(float);
	float *d_A, *d_C;
	cudaMalloc((void **)&d_A, size);
	cudaMemcpy(d_A, A, size, cudaMemcpyHostToDevice);
	cudaMalloc((void **)&d_C, size);
	dim3 DimGrid((col-1)/BLOCK+1, (fil-1)/BLOCK+1);
	dim3 DimBlock(BLOCK, BLOCK);
	matrizEscalar <<< DimGrid, DimBlock >>> (d_A, B, d_C, fil, ccol);
	cudaMemcpy(C, d_C, size, cudaMemcpyDeviceToHost);
	cudaFree(d_A); cudaFree(d_C);
}
int main() {
	int fila,columna;
	float B;
	float *A;float *C;
	fila = 512;
	columna = 512;
	B = 4;
	A = (float*)malloc(fila*columna*sizeof(float));
	C = (float*)malloc(fila*columna*sizeof(float));
	for (int i = 0; i < fila*columna; i++)
		A[i] = 2;
	mostrarM(A, fila, columna);
	for (int i = 0; i < fila; i++){
		for (int j = 0; j < columna; j++)
			printf("%3.0f ", A[x*columna + y]);
		printf("\n");
	}
	matrizescalar(A, B, C, fila,columna);
	for (int i = 0; i < fila; i++){
		for (int j = 0; j < columna; j++)
			printf("%3.0f ", C[i*columna + j]);
		printf("\n");
	}
}

