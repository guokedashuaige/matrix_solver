#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bicgstab.h"

int main() {
    int n = 100;  // 矩阵大小
    int max_iter = 1000;  // 最大迭代次数
    double tol = 1e-6;  // 收敛容差

    double **A = create_matrix(n);
    double *b = create_vector(n);
    double *x = create_vector(n);
    double *x_exact = create_vector(n);

    // 构造对角占优矩阵 A
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                A[i][j] = n + 1;  // 对角元素
            } else {
                A[i][j] = 1.0 / (1 + abs(i - j));  // 非对角元素
            }
        }
    }

    // 构造精确解 x_exact
    for (int i = 0; i < n; i++) {
        x_exact[i] = sin(i);  // 使用正弦函数生成精确解
    }

    // 计算右侧向量 b = A * x_exact
    matrix_vector_multiply(b, A, x_exact, n);

    // 初始化解向量 x 为 0
    for (int i = 0; i < n; i++) {
        x[i] = 0.0;
    }

    // 调用 BiCGSTAB 求解
    bicgstab(A, b, x, n, tol, max_iter);

    // 计算并输出相对误差
    double error = 0.0, norm_exact = 0.0;
    for (int i = 0; i < n; i++) {
        error += (x[i] - x_exact[i]) * (x[i] - x_exact[i]);
        norm_exact += x_exact[i] * x_exact[i];
    }
    error = sqrt(error);
    norm_exact = sqrt(norm_exact);
    double relative_error = error / norm_exact;

    printf("Relative error: %e\n", relative_error);

    // 打印结果或保存到文件
    char choice;
    printf("Do you want to (p)rint results or (s)ave to file? ");
    scanf(" %c", &choice);

    if (choice == 'p' || choice == 'P') {
        printf("Matrix A (%d x %d):\n", n, n);
        print_matrix(A, n);
        printf("\nVector b (%d):\n", n);
        print_vector(b, n);
        printf("\nSolution x (%d):\n", n);
        print_vector(x, n);
    } else if (choice == 's' || choice == 'S') {
        save_results(A, b, x, n, "bicgstab_results.txt");
    } else {
        printf("Invalid choice. Results not saved or printed.\n");
    }

    // 释放内存
    free_matrix(A, n);
    free(b);
    free(x);
    free(x_exact);

    return 0;
}