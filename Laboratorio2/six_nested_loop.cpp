//#include <iostream>
#define Block 4
#include <time.h>
#include <stdio.h>
#include <sys/time.h>
//using namespace std;

double timeval_diff(struct timeval *a, struct timeval *b)
{
 return
   (double)(a->tv_sec + (double)a->tv_usec/1000000) -
   (double)(b->tv_sec + (double)b->tv_usec/1000000);
}
int main()
{
    struct timeval t_ini, t_fin;
    int Row=100,Column=100,Row_1=100,Column_1=100;
    double secs;
    gettimeofday(&t_ini, NULL);
    /*cout<<"Ingrese numero de filas de la primera matriz:"<<endl;
    cin>>Row;
    cout<<"Ingrese numero de columnas de la primera matriz:"<<endl;
    cin>>Column;
    cout<<"Ingrese numero de filas de la segunda matriz:"<<endl;
    cin>>Row_1;
    cout<<"Ingrese numero de columnas de la segunda matriz:"<<endl;
    cin>>Column_1;*/
    int A[Row][Column],B[Row_1][Column_1],R[Row][Column_1];
    for(int i=0;i<Row;i++)
        for(int j=0;j<Column_1;j++){
            R[i][j]=0;}
    for(int i=0;i<Row;i++)
        for(int j=0;j<Column;j++){
            A[i][j]=1;}
    for(int i=0;i<Row_1;i++)
        for(int j=0;j<Column_1;j++){
            B[i][j]=2;}


    for(int i=0;i<Row;i=i+Block)
        for(int j=0;j<Column_1;j=j+Block)
            for(int k=0;k<Row_1;k=k+Block)
                for(int i1 = i ;i1<((i+Block)>Row?Row:(i+Block));i1++)
                    for(int j1=j ;j1<((j+Block)>Column_1?Column_1:(j+Block));j1++)
                        for(int k1=k;k1<((k+Block)>Row_1?Row_1:(k+Block));k1++)
                           R[i1][j1] = R[i1][j1] + A[i1][k1] * B[k1][j1];
   /* cout<<"Matriz 1: "<<endl;
    for(int i=0;i<Row;i++){
        for(int j=0;j<Column;j++)
            cout<<A[i][j]<<'\t';
        cout<<endl;}
    cout<<"Matriz 2: "<<endl;
    for(int i=0;i<Row_1;i++){
        for(int j=0;j<Column_1;j++)
            cout<<B[i][j]<<'\t';
        cout<<endl;}
    cout<<"Respuesta: "<<endl;
    for(int i=0;i<Row;i++){
        for(int j=0;j<Column_1;j++)
            cout<<R[i][j]<<'\t';
        cout<<endl;}*/
  gettimeofday(&t_fin, NULL);
    secs = timeval_diff(&t_fin, &t_ini);

    printf("%.16g milliseconds\n", secs * 1000.0);
    return 0;
}
