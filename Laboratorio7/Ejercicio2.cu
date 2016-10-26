#include <iostream>
#include <stdio.h>
#include <cuda_runtime.h>
#include <cuda.h>
#include <device_launch_parameters.h>

using namespace std;
__global__
void vecMultKernel(float* A, float* B, float* C, int n){
	int i = threadIdx.x + blockDim.x * blockIdx.x;
	if (i<n){
		C[i] = 0;
		for (int j = 0; j<n; j++)
			C[i] += A[i*n + j] * B[j];
	}
}
void matrizescalar(float* A, float* B, float* C, int n) {
	int size = n * n * sizeof(float);
	int sizevect = n * sizeof(float);
	float *d_A, *d_B, *d_C;
	cudaMalloc((void **)&d_A, size);
	cudaMemcpy(d_A, A, size, cudaMemcpyHostToDevice);
	cudaMalloc((void **)&d_B, sizevect);
	cudaMemcpy(d_B, B, sizevect, cudaMemcpyHostToDevice);
	cudaMalloc((void **)&d_C, sizevect);
	vecMultKernel <<< ceil((n*n) / 256.0), 256 >>> (d_A, d_B, d_C, n);
	cudaMemcpy(C, d_C, sizevect, cudaMemcpyDeviceToHost);
	cudaFree(d_A); cudaFree(d_B); cudaFree(d_C);
}

int main() {
	int n;
	float *B;
	float *A;float *C;
	n=100;
	A = (float*)malloc(fila*columna*sizeof(float));
	B = (float*)malloc(fila*sizeof(float));
	C = (float*)malloc(fila*sizeof(float));
	for (int i = 0; i < fila*columna; i++)
		A[i] = 2;
	for (int i = 0; i < fila; i++)
		B[i] = 3;
	matrizescalar(A, B, C, n);

	
}
