/**
 * @file		main.c
 * @author	Jiale Gao (gaojiale14@mails.ucas.ac.cn)
 * @version	0.1
 * @date		2024-10-10
 *
 * @brief	Brief description of the file
 *
 * @par		Project name:
 *			Project description
 *
 * @license	License: MIT
 *
 * @attention
 *			Any important notes or warnings
 */

#include <stdio.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define N 3 // 方程组的维数
#define MAX_ITERATIONS 100
#define EPSILON 1e-6 // 收敛精度

int a2;
int a3;

int b2;
int b3;


void jacobiIteration(double A[N][N], double b[N], double x[N])
{
    double x_new[N];
    int iterations = 0;
    double diff;

    do
    {
        for (int i = 0; i < N; i++)
        {
            double sum = b[i];
            for (int j = 0; j < N; j++)
            {
                if (j != i)
                {
                    sum -= A[i][j] * x[j];
                }
            }
            x_new[i] = sum / A[i][i];
        }

        // 检查收敛
        diff = 0.0;
        for (int i = 0; i < N; i++)
        {
            diff += fabs(x_new[i] - x[i]);
            x[i] = x_new[i];
        }

        iterations++;

    } while (diff > EPSILON && iterations < MAX_ITERATIONS);

    if (iterations == MAX_ITERATIONS)
    {
        printf("Did not converge within %d iterations.\n", MAX_ITERATIONS);
    }
    else
    {
        printf("Converged after %d iterations.\n", iterations);
    }
}

int main()
{
    double A[N][N] = {
        {5, -2, 3},
        {-3, 9, 1},
        {2, -1, -7}};
    double b[N] = {-1, 2, 3};
    double x[N] = {0, 0, 0}; // 初始猜测值

    jacobiIteration(A, b, x);

    printf("Solution:\n");
    for (int i = 0; i < N; i++)
    {
        printf("x[%d] = %f\n", i, x[i]);
    }

    return 0;
}