#include "bicgstab.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double dot_product(double *a, double *b, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += a[i] * b[i];
    }
    return sum;
}

void vector_subtract(double *result, double *a, double *b, int n) {
    for (int i = 0; i < n; i++) {
        result[i] = a[i] - b[i];
    }
}

void matrix_vector_multiply(double *result, double **A, double *x, int n) {
    for (int i = 0; i < n; i++) {
        result[i] = 0.0;
        for (int j = 0; j < n; j++) {
            result[i] += A[i][j] * x[j];
        }
    }
}

void scalar_multiply(double *result, double *a, double scalar, int n) {
    for (int i = 0; i < n; i++) {
        result[i] = a[i] * scalar;
    }
}

void vector_add(double *result, double *a, double *b, int n) {
    for (int i = 0; i < n; i++) {
        result[i] = a[i] + b[i];
    }
}

void bicgstab(double **A, double *b, double *x, int n, double tol, int max_iter) {
    double *r = create_vector(n);
    double *r_tilde = create_vector(n);
    double *p = create_vector(n);
    double *v = create_vector(n);
    double *s = create_vector(n);
    double *t = create_vector(n);
    double *temp = create_vector(n);

    matrix_vector_multiply(temp, A, x, n);
    vector_subtract(r, b, temp, n);

    for (int i = 0; i < n; i++) {
        r_tilde[i] = r[i];
    }

    double rho_prev = 1.0, alpha = 1.0, omega = 1.0;
    double rho, beta, norm_r;

    for (int iter = 0; iter < max_iter; iter++) {
        rho = dot_product(r_tilde, r, n);
        
        if (fabs(rho) < 1e-15) {
            printf("Method failed, rho = 0\n");
            break;
        }

        if (iter > 0) {
            beta = (rho / rho_prev) * (alpha / omega);
            scalar_multiply(temp, v, omega, n);
            vector_subtract(temp, p, temp, n);
            scalar_multiply(temp, temp, beta, n);
            vector_add(p, r, temp, n);
        } else {
            for (int i = 0; i < n; i++) {
                p[i] = r[i];
            }
        }

        matrix_vector_multiply(v, A, p, n);

        alpha = rho / dot_product(r_tilde, v, n);

        scalar_multiply(temp, v, alpha, n);
        vector_subtract(s, r, temp, n);

        norm_r = sqrt(dot_product(s, s, n));
        if (norm_r < tol) {
            scalar_multiply(temp, p, alpha, n);
            vector_add(x, x, temp, n);
            printf("Converged in %d iterations\n", iter + 1);
            break;
        }

        matrix_vector_multiply(t, A, s, n);

        omega = dot_product(t, s, n) / dot_product(t, t, n);

        scalar_multiply(temp, p, alpha, n);
        vector_add(x, x, temp, n);
        scalar_multiply(temp, s, omega, n);
        vector_add(x, x, temp, n);

        scalar_multiply(temp, t, omega, n);
        vector_subtract(r, s, temp, n);

        rho_prev = rho;

        norm_r = sqrt(dot_product(r, r, n));
        if (norm_r < tol) {
            printf("Converged in %d iterations\n", iter + 1);
            break;
        }

        if (fabs(omega) < 1e-15) {
            printf("Method failed, omega = 0\n");
            break;
        }
    }

    free(r);
    free(r_tilde);
    free(p);
    free(v);
    free(s);
    free(t);
    free(temp);
}

double** create_matrix(int n) {
    double **matrix = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (double*)malloc(n * sizeof(double));
    }
    return matrix;
}

void free_matrix(double **matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

double* create_vector(int n) {
    return (double*)malloc(n * sizeof(double));
}

void print_matrix(double **A, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%f ", A[i][j]);
        }
        printf("\n");
    }
}

void print_vector(double *v, int n) {
    for (int i = 0; i < n; i++) {
        printf("%f ", v[i]);
    }
    printf("\n");
}

void save_results(double **A, double *b, double *x, int n, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    fprintf(file, "Matrix A (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(file, "%f ", A[i][j]);
        }
        fprintf(file, "\n");
    }

    fprintf(file, "\nVector b (%d):\n", n);
    for (int i = 0; i < n; i++) {
        fprintf(file, "%f\n", b[i]);
    }

    fprintf(file, "\nSolution x (%d):\n", n);
    for (int i = 0; i < n; i++) {
        fprintf(file, "%f\n", x[i]);
    }

    fclose(file);
    printf("Results saved to %s\n", filename);
}