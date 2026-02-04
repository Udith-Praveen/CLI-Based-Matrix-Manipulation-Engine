#include <stdio.h>
#include "matrix_toolkit.h"

//Helper Implementation to handle buffer overflows.
int get_safe_int(const char *prompt) {
    int value;
    int status;
    while (1) {
        printf("%s", prompt);
        status = scanf("%d", &value);
        if (status == 1) {
            char next_char = getchar();
            if (next_char == '\n' || next_char == EOF) {
                return value;
            } else {
                ungetc(next_char, stdin);
            }
        }
        printf("Invalid input! Please enter a valid integer.\n");
        int c;
        while ((c = getchar()) != '\n' && c != EOF); 
    }
}

//Matrix Operations Implementations

void scalar_multi(int matrix[CAPACITY][CAPACITY], int r, int c) {
    int scale = get_safe_int("Enter the integer you want to multiply the matrix by: ");
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            matrix[i][j] = scale * matrix[i][j];
        }
    }
}

void rowandcolumn_sum(int matrix[CAPACITY][CAPACITY], int r, int c) {
    for(int i=0; i<r; i++){
        int row_sum=0;
        for(int j=0; j<c; j++){
            row_sum += matrix[i][j];
        }
        printf("Row %d's sum is: %d\n", i+1, row_sum);
    }
    for (int j=0; j<c; j++) {
        int col_sum=0;
        for (int i=0; i<r; i++) { 
            col_sum += matrix[i][j];
        }
        printf("Column %d Sum: %d\n", j+1, col_sum);
    }
}

void transpose_matrix(int matrix[CAPACITY][CAPACITY], int *r, int *c) {
    int temp[CAPACITY][CAPACITY];
    for(int i=0; i<*r; i++){
        for(int j=0; j<*c; j++){
            temp[j][i] = matrix[i][j];
        }
    }
    int old_rows = *r;
    int old_columns = *c;
    *r = old_columns;
    *c = old_rows;
    for(int i=0; i<*r; i++){
        for(int j=0; j<*c; j++){
            matrix[i][j] = temp[i][j];
        }
    }
    printf("\nMatrix Transposed Successfully! New dimensions: %dx%d\n", *r, *c);
}

void trace_matrix(int matrix[CAPACITY][CAPACITY], int r, int c) {
    if (r != c) {
        printf("\nError: Trace is ONLY defined for Square Matrices.\n");
        return;
    }
    int diagonal_sum = 0;
    for(int i=0; i<r; i++) {
        diagonal_sum += matrix[i][i];
    }
    printf("\nThe Trace of the matrix is: %d\n", diagonal_sum);
}

void rotate_matrix_clock(int matrix[CAPACITY][CAPACITY], int *r, int *c) {
    transpose_matrix(matrix, r, c);
    for(int i=0; i<*r; i++){
        int start=0;
        int end=*c-1;
        while(start < end){
            int aux = matrix[i][start];
            matrix[i][start] = matrix[i][end];
            matrix[i][end] = aux;
            start++;
            end--;
        }
    }
    printf("\nThe matrix has been rotated Clockwise once!\n");
}

void add_matrix(int matrix[CAPACITY][CAPACITY], int r, int c) {
    int temp[CAPACITY][CAPACITY];
    printf("Enter the elements of the second matrix:\n");
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            printf("Element [%d][%d]: ", i, j);
            if (scanf("%d", &temp[i][j]) != 1) {
                printf("Invalid input. Try again.\n");
                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF);
                j--;
            }
        }
    }
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            matrix[i][j] += temp[i][j];
        }
    }
    printf("Addition successful!\n");
}

void multiply_matrix(int matrix[CAPACITY][CAPACITY], int r, int *c) {
    int x, y;
    while(1) {
        x = get_safe_int("\nEnter rows for Matrix B: ");
        y = get_safe_int("Enter columns for Matrix B: ");
        if (x == *c && y > 0 && y <= CAPACITY) break;
        if (x != *c) printf("Invalid! Rows of B (%d) must match Cols of A (%d).\n", x, *c);
        else printf("Invalid! Columns must be between 1 and %d.\n", CAPACITY);
    }
    int temp[CAPACITY][CAPACITY]; // Using fixed size for safety
    for(int i=0; i<x; i++){
        for(int j=0; j<y; j++){
            printf("Element [%d][%d]: ", i, j);
            if (scanf("%d", &temp[i][j]) != 1) {
                printf("Invalid input.\n");
                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF);
                j--;
            }
        }
    }
    int aux[CAPACITY][CAPACITY] = {0};
    for(int i=0; i<r; i++){
        for(int j=0; j<y; j++){
            for(int k=0; k<*c; k++){
                aux[i][j] += matrix[i][k] * temp[k][j];
            }
        }
    }
    *c = y;
    for(int i=0; i<r; i++){
        for(int j=0; j<*c; j++){
            matrix[i][j] = aux[i][j];
        }
    }
    printf("Multiplication successful!\n");
}

void saddle_point(int matrix[CAPACITY][CAPACITY], int r, int c) {
    int found_any = 0;
    for (int i=0; i<r; i++) {
        int min_val = matrix[i][0];
        for (int j=1; j<c; j++) {
            if (matrix[i][j] < min_val) min_val = matrix[i][j];
        }
        for (int j=0; j<c; j++) {
            if (matrix[i][j] == min_val) {
                int is_max_in_col = 1; 
                for (int k=0; k<r; k++) {
                    if (matrix[k][j] > min_val) {
                        is_max_in_col = 0;
                        break;
                    }
                }
                if (is_max_in_col) {
                    printf("Saddle Point found at [%d][%d]: %d\n", i, j, min_val);
                    found_any = 1;
                }
            }
        }
    }
    if (!found_any) printf("No Saddle Points found.\n");
}

void spiral_print(int matrix[CAPACITY][CAPACITY], int r, int c) {
    int left=0, right=c-1, top=0, bottom=r-1;
    printf("\n--- Spiral Order ---\n");
    while(top <= bottom && left <= right){
        for(int i=left; i<=right; i++) printf("%d ", matrix[top][i]);
        top++;
        for(int j=top; j<=bottom; j++) printf("%d ", matrix[j][right]);
        right--;
        if (top <= bottom) {
            for (int k=right; k>=left; k--) printf("%d ", matrix[bottom][k]);
            bottom--;
        }
        if (left <= right) {
            for (int l=bottom; l>=top; l--) printf("%d ", matrix[l][left]);
            left++;
        }
    }
    printf("\n");
}

void apply_convolution(int matrix[CAPACITY][CAPACITY], int r, int c) {
    int result[CAPACITY][CAPACITY] = {0};
    printf("Edge detection Convolution\n");
    for(int i=1; i<r-1; i++){
        for(int j=1; j<c-1; j++){
            int sum = (4 * matrix[i][j]) 
                    - matrix[i-1][j] - matrix[i+1][j] 
                    - matrix[i][j-1] - matrix[i][j+1];
            result[i][j] = sum;
        }
    }
    for (int i=0; i<r; i++) {
        for (int j=0; j<c; j++) {
            matrix[i][j] = result[i][j];
        }
    }
    printf("Edge detection applied successfully!\n");
}