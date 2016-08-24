//#include <iostream>

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

    /*cout<<"Ingrese numero de filas de la primera matriz:"<<endl;
    cin>>Row;
    cout<<"Ingrese numero de columnas de la primera matriz:"<<endl;
    cin>>Column;
    	cout<<"Ingrese numero de filas de la segunda matriz:"<<endl;
    cin>>Row_1;
    std::cout<<"Ingrese numero de columnas de la segunda matriz:"<<endl;
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
    gettimeofday(&t_ini, NULL);
    for(int i=0;i<Row;i++)
        for(int j=0;j<Column_1;j++)
            for(int k=0;k<Row_1;k++)
                R[i][j]+=A[i][k]*B[k][j];
    /*cout<<"Matriz 1: "<<endl;
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


	
