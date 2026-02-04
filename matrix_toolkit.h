#ifndef MATRIX_TOOLKIT_H
#define MATRIX_TOOLKIT_H

#define CAPACITY 100

//Helper Function
int get_safe_int(const char *prompt);

//Matrix Operations
void scalar_multi(int matrix[CAPACITY][CAPACITY], int r, int c);
void rowandcolumn_sum(int matrix[CAPACITY][CAPACITY], int r, int c);
void transpose_matrix(int matrix[CAPACITY][CAPACITY], int *r, int *c);
void trace_matrix(int matrix[CAPACITY][CAPACITY], int r, int c);
void rotate_matrix_clock(int matrix[CAPACITY][CAPACITY], int *r, int *c);
void add_matrix(int matrix[CAPACITY][CAPACITY], int r, int c);
void multiply_matrix(int matrix[CAPACITY][CAPACITY], int r, int *c);
void saddle_point(int matrix[CAPACITY][CAPACITY], int r, int c);
void spiral_print(int matrix[CAPACITY][CAPACITY], int r, int c);
void apply_convolution(int matrix[CAPACITY][CAPACITY], int r, int c);

#endif