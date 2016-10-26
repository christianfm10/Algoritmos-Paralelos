#include <iostream>
#include <stdio.h>
#include <cuda_runtime.h>
#include <cuda.h>
#include <device_launch_parameters.h>
#define BLOCK 10
using namespace std;

__global__
void matrizEscalar(float* A, float B, float* C, int fil,int col,int d3){
	int i = blockIdx.y*blockDim.y + threadIdx.y;
	int j = blockIdx.x*blockDim.x + threadIdx.x;
	int k = blockIdx.z*blockDim.z + threadIdx.z;
	if ((i < fil) && (j < col) && (k < d3)) {
		C[k*col*fil + i*col + j] = B * A[k*col*fil + i*col + j];
	}
}
void matrizescalar(float* A, float B, float* C, int fil,int col,int d3) {
	int size = fil * col * d3 *  sizeof(float);
	float *d_A, *d_C;
	cudaMalloc((void **)&d_A, size);
	cudaMemcpy(d_A, A, size, cudaMemcpyHostToDevice);
	cudaMalloc((void **)&d_C, size);
	dim3 DimGrid((col-1)/BLOCK+1, (fil-1)/BLOCK+1,(d3-1)/BLOCK+1);
	dim3 DimBlock(BLOCK, BLOCK, BLOCK);
	matrizEscalar <<< dime1, DimBlock >>> (d_A, B, d_C, fil, col,d3);
	cudaMemcpy(C, d_C, size, cudaMemcpyDeviceToHost);
	cudaFree(d_A); cudaFree(d_C);
}

int main() {
	int fila,columna,D3;
	float B;
	float *A;float *C;
	fila = 10;
	columna = 10;
	D3 = 10;
	B=2;	
	A = (float*)malloc(fila*columna*D3*sizeof(float));
	C = (float*)malloc(fila*columna*D3*sizeof(float));
	for (int i = 0; i < fila*columna*D3; i++)
		A[i] = 2;
	matrizescalar(A, B, C, fila,columna,D3);

}
