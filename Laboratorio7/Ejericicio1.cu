#include <iostream>
#include <stdio.h>
#include <cuda_runtime.h>
#include <cuda.h>
#include <device_launch_parameters.h>


using namespace std;
__global__
void matrixAddKernel(float* A, float* B, float* C, int n){
	int i = threadIdx.x + blockDim.x * blockIdx.x;
	if (i < n*n) C[i] = A[i] + B[i];
}
__global__
void matrixAddKernel2(float* A, float* B, float* C, int n){
	int i = threadIdx.x + blockDim.x * blockIdx.x;
	if (i < n){
		for (int j = i * n; j < i * n + n; j++)
			C[j] = A[j] + B[j];
	}
}
__global__
void matrixAddKernel3(float* A, float* B, float* C, int n){
	int i = threadIdx.x + blockDim.x * blockIdx.x;
	if (i < n)
		for (int j = i; j < n*n; j += n)
			C[j] = A[j] + B[j];
}
void matrixAdd(float* A, float* B, float* C, int n) {
	int size = n * n * sizeof(float);
	float *d_A, *d_B, *d_C;
	cudaMalloc((void **)&d_A, size);
	cudaMemcpy(d_A, A, size, cudaMemcpyHostToDevice);
	cudaMalloc((void **)&d_B, size);
	cudaMemcpy(d_B, B, size, cudaMemcpyHostToDevice);
	cudaMalloc((void **)&d_C, size);
	matrixAddKernel <<< ceil((n*n) / 256.0), 256 >>> (d_A, d_B, d_C, n);
	cudaMemcpy(C, d_C, size, cudaMemcpyDeviceToHost);
	cudaFree(d_A); cudaFree(d_B); cudaFree(d_C);
}

int main() {
	int n;
	float *B;
	float *A;float *C;
	n=100;
	A = (float*)malloc(n*n*sizeof(float));
	B = (float*)malloc(n*sizeof(float));
	C = (float*)malloc(n*sizeof(float));
	for (int i = 0; i < n*n; i++)
	{
		A[i] = 1;
		B[i] = 2;
	}
	matrixAdd(A, B, C, n);

}
