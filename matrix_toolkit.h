#ifndef MATRIX_TOOLKIT_H
#define MATRIX_TOOLKIT_H

//Memory management
int** create_matrix(int rows, int cols);
void free_matrix(int** matrix, int rows);

//Input helper
int get_safe_int(const char *prompt);


//Operations that modify data in place
void scalar_multi(int** matrix, int r, int c);
void rowandcolumn_sum(int** matrix, int r, int c);
void trace_matrix(int** matrix, int r, int c);
void saddle_point(int** matrix, int r, int c);
void spiral_print(int** matrix, int r, int c);
void apply_convolution(int** matrix, int r, int c);
void add_matrix(int** matrix, int r, int c);

//Operations that might resize/reallocate the matrix (Must return new pointer)
int** transpose_matrix(int** matrix, int *r, int *c);
int** rotate_matrix_clock(int** matrix, int *r, int *c);
int** multiply_matrix(int** matrix, int r, int *c);

#endif