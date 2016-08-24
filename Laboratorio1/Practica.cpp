#include <iostream>
#include <time.h>
#include <stdio.h>
#include <sys/time.h>
using namespace std;
double timeval_diff(struct timeval *a, struct timeval *b)
{
 return
   (double)(a->tv_sec + (double)a->tv_usec/1000000) -
   (double)(b->tv_sec + (double)b->tv_usec/1000000);
}
int main()
{   int MAX=1000;
    double secs;
    struct timeval t_ini, t_fin;
    double A[MAX][MAX], x[MAX],y[MAX];
    gettimeofday(&t_ini, NULL);
    for(int i=0; i<MAX;i++)
        for(int j=0; j <MAX; j++)
            y[i] += A[i][j]*x[j];
    gettimeofday(&t_fin, NULL);
    secs = timeval_diff(&t_fin, &t_ini);
    printf("%.16g milliseconds\n", secs * 1000.0);
    gettimeofday(&t_ini, NULL);
    for(int j=0; j<MAX;j++)
        for(int i=0; i<MAX; i++)
            y[i] += A[i][j]*x[j];
    gettimeofday(&t_fin, NULL);
    secs = timeval_diff(&t_fin, &t_ini);
    printf("%.16g milliseconds\n", secs * 1000.0);
    return 0;
}
