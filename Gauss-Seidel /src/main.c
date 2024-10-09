/**
 * @file		main.c
 * @author	Jiale Gao (gaojiale14@mails.ucas.ac.cn)
 * @version	0.1
 * @date		2024-10-09
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
#include <math.h>
#include <stdlib.h>

#define N 3  // 方程组的维数
#define MAX_ITERATIONS 100
#define EPSILON 1e-6  // 收敛精度

void gaussSeidel(double A[N][N], double b[N], double x[N]) {
    int i, j, k;
    double sum, old_x;

    for (k = 0; k < MAX_ITERATIONS; k++) {
        for (i = 0; i < N; i++) {
            sum = b[i];
            for (j = 0; j < N; j++) {
                if (j != i) {
                    sum -= A[i][j] * x[j];
                }
            }
            old_x = x[i];
            x[i] = sum / A[i][i];
            
            // 检查收敛
            if (fabs(x[i] - old_x) < EPSILON) {
                printf("Converged after %d iterations.\n", k + 1);
                return;
            }
        }
    }
    printf("Did not converge within %d iterations.\n", MAX_ITERATIONS);
}

int main() {
    double A[N][N] = {{4, -1, 0}, {-1, 4, -1}, {0, -1, 4}};
    double b[N] = {15, 10, 10};
    double x[N] = {0, 0, 0};  // 初始猜测值

    gaussSeidel(A, b, x);

    printf("Solution:\n");
    for (int i = 0; i < N; i++) {
        printf("x[%d] = %f\n", i, x[i]);
    }

    return 0;
}