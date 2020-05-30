#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <iostream>
using namespace std;


int main(int argc, char** argv)
{
        // Умножение матрицы на вектор
        int rank, size;
        int i, j, n = 10;
        MPI_Init(&argc, &argv);
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        int n_partial = n / size;
        
        double * a_partial = new double[n_partial*n];//блоки строк исходной матрицы на каждом процессе
        double * x =  new double[n]; //исходный вектор
        double * y_partial = new double[n_partial];//блоки результирующего вектора на каждом процессе
        double * y_total = new double[n];// вектор-результат
        double * a = new double[n*n];//исходная матрица
        if (rank == 0)
        {
                FILE *f1 = fopen("matrix.txt", "w");
                fprintf(f1, "Matrix\n");
                //матрицу удобнее рассматривать как одномерный массив но с индексами i*n+j
                for (i = 0; i < n; i++)
                {
                        for (j = 0; j < n; j++)
                        {
                                if (i == j)
                                        a[i*n + j] = rand() % 1000;
                                else
                                        a[i*n + j] = rand() % 1000;
                                fprintf(f1, "%f\t", a[i*n + j]);
                        }
                        fprintf(f1, "\n");
                }
                fprintf(f1, "Vector\n");
                for (i = 0; i < n; i++)
                {
                        x[i] = i+1;
                        fprintf(f1, "%f\t", x[i]);
                }
                fclose(f1);
        }
        double t = MPI_Wtime();
        //рассылаем вектор x
        MPI_Bcast(x, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        for (i = 0; i < n; i++)
                cout << x[i] << "\t";
        cout << endl;
        //разделяем матрицу на горизонтальные полосы
        //шириной n_partial и отправляем процессам
        MPI_Scatter(a, n_partial * n, MPI_DOUBLE, a_partial, n_partial * n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        for (i = 0; i < n_partial; i++)
        {
                for (j = 0; j < n; j++)
                        cout << a_partial[i*n + j] << "\t";
                cout << "\n";
        }
        for (i = 0; i < n_partial; i++)
        {
                y_partial[i] = 0.0;
                for (j = 0; j < n; j++)
                        y_partial[i] += a_partial[i*n + j] * x[j];
        }
        for (i = 0; i < n_partial; i++)
                cout << y_partial[i] << "\t";
        cout << endl;
        //собираем результат в нулевом процессе
        MPI_Gather(y_partial, n_partial, MPI_DOUBLE, y_total, n_partial, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        t = MPI_Wtime() - t;
        if (rank == 0)
        {
                FILE *f2 = fopen("result.txt", "w");
                for (i = 0; i < n; i++)
                        fprintf(f2,"%10.5f\n", y_total[i]);
                fclose(f2);
        }
        delete[] a_partial;
        delete[] a;
        delete[] x;
        delete[] y_partial;
        delete[] y_total;

        MPI_Finalize();
        return 0;
}
