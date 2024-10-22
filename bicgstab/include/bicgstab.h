/**
 * @file		bicgstab.h
 * @author	Jiale Gao (gaojiale14@mails.ucas.ac.cn)
 * @version	0.1
 * @date		2024-10-22
 *
 * @brief	Brief description of the header file
 *
 * @par		Project name:
 *			Project description
 *
 * @license	License: MIT
 *
 * @attention
 *			Any important notes or warnings
 */

#ifndef BICGSTAB_H
#define BICGSTAB_H

#ifdef __cplusplus
extern "C" {
#endif

// Your code here
// 向量点积
double dot_product(double *a, double *b, int n);

// 向量减法: result = a - b
void vector_subtract(double *result, double *a, double *b, int n);

// 矩阵-向量乘法: result = A * x
void matrix_vector_multiply(double *result, double **A, double *x, int n);

// 向量标量乘法: result = a * scalar
void scalar_multiply(double *result, double *a, double scalar, int n);

// 向量加法: result = a + b
void vector_add(double *result, double *a, double *b, int n);

// BiCGSTAB算法实现
void bicgstab(double **A, double *b, double *x, int n, double tol, int max_iter);

// 创建矩阵函数
double** create_matrix(int n);

// 释放矩阵内存函数
void free_matrix(double **matrix, int n);

// 创建向量函数
double* create_vector(int n);

// 打印矩阵函数
void print_matrix(double **A, int n);

// 打印向量函数
void print_vector(double *v, int n);

// 在 bicgstab.h 中添加
void save_results(double **A, double *b, double *x, int n, const char *filename);
#ifdef __cplusplus
}
#endif

#endif // BICGSTAB_H