#include <stdio.h>
#include <iostream>
#include <omp.h>
#include <vector>
#include <random>
#include <fstream>
#include <float.h>
#include <algorithm>
using namespace std;

#define NTHREADS 8

double fRand()
{
    double fMin = -100.0, fMax = 100.0;
    double f = (double)rand() / (fMax + fMin + 1);
    return fMin + f * (fMax - fMin);
}

vector<vector<double>> getMatrix(int n, int m)
{
    vector<vector<double>> matrix(n, vector<double>(m));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            matrix[i][j] = fRand();
    return matrix;
}

void printMatrix(vector<vector<double>> matrix)
{
    for (int i = 0; i < matrix.size(); ++i)
    {
        for (int j = 0; j < matrix[i].size(); ++j)
            printf("%8.2lf ", matrix[i][j]);
        printf("\n");
    }
}

int main()
{
    setlocale(0, "ru");
    srand(time(0));
    omp_set_num_threads(NTHREADS);
    double start_time, run_time;
    start_time = omp_get_wtime();
    ifstream fin("input_data/input.txt");

    int n, m;
    fin >> n >> m;

    // printf("%10d %10d\n", n, m);
    vector<vector<double>> matrix = getMatrix(n, m);

    double firstMin = matrix[0][0];
    for (int j = 1; j < m; ++j)
        if (matrix[0][j] < firstMin)
            firstMin = matrix[0][j];
    double maxV = firstMin;

    for (int i = 1; i < n; ++i)
    {
        double min = matrix[i][0];
        for (int j = 1; j < m; ++j)
            if (matrix[i][j] < min)
                min = matrix[i][j];
        if (min > maxV)
            maxV = min;
    }
    run_time = omp_get_wtime() - start_time;
    printf("%10lf\n", run_time);

    maxV = firstMin;
    start_time = omp_get_wtime();

#pragma omp parallel for
    for (int i = 1; i < n; ++i)
    {
        double min = matrix[i][0];
        for (int j = 1; j < m; ++j)
            if (matrix[i][j] < min)
                min = matrix[i][j];
#pragma omp critical
        {
            if (min > maxV)
                maxV = min;
        }
    }
    run_time = omp_get_wtime() - start_time;
    printf("%10lf\n", run_time);

    start_time = omp_get_wtime();
    maxV = firstMin;
#pragma omp parallel for reduction(max : maxV)
    for (int i = 0; i < n; i++)
    {
        double min = matrix[i][0];
        for (int j = 1; j < m; ++j)
            if (matrix[i][j] < min)
                min = matrix[i][j];
        maxV = min;
    }
    run_time = omp_get_wtime() - start_time;
    printf("%10lf\n", run_time);

    start_time = omp_get_wtime();
    vector<double> mins(n);
    for (int i = 0; i < n; i++)
    {
#pragma omp parallel shared(mins)
        {
            double min = matrix[i][0];
            for (int j = 1; j < m; ++j)
                if (matrix[i][j] < min)
                    min = matrix[i][j];
            mins[i] = min;
        }
    }

    vector<double> maxs(NTHREADS);
    int limit = (int)(n / NTHREADS);
#pragma omp parallel sections
    {
#if NTHREADS > 0
#pragma omp section
        {
            int id = omp_get_thread_num();
            // printf("Поток %d\n", id);
            maxs[id] = mins[limit * id];
            for (int i = limit * id; i < limit * (id + 1); ++i)
                if (mins[i] > maxs[id])
                    maxs[id] = mins[i];
        }
#endif // NTHREADS > 0

#if NTHREADS > 1
#pragma omp section
        {
            int id = omp_get_thread_num();
            // printf("Поток %d\n", id);
            maxs[id] = mins[limit * id];
            for (int i = limit * id; i < limit * (id + 1); ++i)
                if (mins[i] > maxs[id])
                    maxs[id] = mins[i];
        }
#endif // NTHREADS > 1

#if NTHREADS > 2
#pragma omp section
        {
            int id = omp_get_thread_num();
            // printf("Поток %d\n", id);
            maxs[id] = mins[limit * id];
            for (int i = limit * id; i < limit * (id + 1); ++i)
                if (mins[i] > maxs[id])
                    maxs[id] = mins[i];
        }
#endif // NTHREADS > 2

#if NTHREADS > 3
#pragma omp section
        {
            int id = omp_get_thread_num();
            // printf("Поток %d\n", id);
            maxs[id] = mins[limit * id];
            for (int i = limit * id; i < limit * (id + 1); ++i)
                if (mins[i] > maxs[id])
                    maxs[id] = mins[i];
        }
#endif // NTHREADS > 3

#if NTHREADS > 4
#pragma omp section
        {
            int id = omp_get_thread_num();
            // printf("Поток %d\n", id);
            maxs[id] = mins[limit * id];
            for (int i = limit * id; i < limit * (id + 1); ++i)
                if (mins[i] > maxs[id])
                    maxs[id] = mins[i];
        }
#endif // NTHREADS > 4

#if NTHREADS > 5
#pragma omp section
        {
            int id = omp_get_thread_num();
            // printf("Поток %d\n", id);
            maxs[id] = mins[limit * id];
            for (int i = limit * id; i < limit * (id + 1); ++i)
                if (mins[i] > maxs[id])
                    maxs[id] = mins[i];
        }
#endif // NTHREADS > 5

#if NTHREADS > 6
#pragma omp section
        {
            int id = omp_get_thread_num();
            // printf("Поток %d\n", id);
            maxs[id] = mins[limit * id];
            for (int i = limit * id; i < limit * (id + 1); ++i)
                if (mins[i] > maxs[id])
                    maxs[id] = mins[i];
        }
#endif // NTHREADS > 6

#if NTHREADS > 7
#pragma omp section
        {
            int id = omp_get_thread_num();
            // printf("Поток %d\n", id);
            maxs[id] = mins[limit * id];
            for (int i = limit * id; i < limit * (id + 1); ++i)
                if (mins[i] > maxs[id])
                    maxs[id] = mins[i];
        }
#endif // NTHREADS > 7
    }
    maxV = maxs[0];
    for (int i = 1; i < NTHREADS; ++i)
    {
        if (maxs[i] > maxV)
            maxV = maxs[i];
    }
    run_time = omp_get_wtime() - start_time;
    printf("%10lf\n", run_time);

    matrix.clear();
    fin.close();

    return 0;
}