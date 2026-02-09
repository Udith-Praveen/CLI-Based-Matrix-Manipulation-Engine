#include <stdio.h>
#include <stdlib.h>
#include "matrix_toolkit.h"

//Memory management

//Allocates memory on the HEAP
int** create_matrix(int rows, int cols) {
    //Allocate the array of row pointers
    int** matrix = (int**)malloc(rows * sizeof(int*));
    if (matrix == NULL) {
        fprintf(stderr, "Heap allocation failed (Spine).\n");
        exit(1);
    }

    //Allocate each row
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            fprintf(stderr, "Heap allocation failed (Row %d).\n", i);
            exit(1);
        }
    }
    return matrix;
}

//Prevents Memory Leaks
void free_matrix(int** matrix, int rows) {
    if (matrix == NULL) return;
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

//Helper function
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

//Operations
void scalar_multi(int** matrix, int r, int c) {
    int scale = get_safe_int("Enter the integer you want to multiply the matrix by: ");
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            matrix[i][j] = scale * matrix[i][j];
        }
    }
}

void rowandcolumn_sum(int** matrix, int r, int c) {
    printf("\n--- Row Sums ---\n");
    for(int i=0; i<r; i++){
        int row_sum=0;
        for(int j=0; j<c; j++){
            row_sum += matrix[i][j];
        }
        printf("Row %d: %d\n", i+1, row_sum);
    }
    printf("\n--- Column Sums ---\n");
    for (int j=0; j<c; j++) {
        int col_sum=0;
        for (int i=0; i<r; i++) { 
            col_sum += matrix[i][j];
        }
        printf("Column %d: %d\n", j+1, col_sum);
    }
}

//Returns new pointer because dimensions might change
int** transpose_matrix(int** matrix, int *r, int *c) {
    int new_r = *c;
    int new_c = *r;
    
    // Allocate NEW matrix
    int** new_matrix = create_matrix(new_r, new_c);

    for(int i=0; i<*r; i++){
        for(int j=0; j<*c; j++){
            new_matrix[j][i] = matrix[i][j];
        }
    }
    free_matrix(matrix, *r);

    *r = new_r;
    *c = new_c;

    printf("\nMatrix Transposed Successfully! New dims: %dx%d\n", *r, *c);
    return new_matrix;
}

void trace_matrix(int** matrix, int r, int c) {
    if (r != c) {
        printf("\nError: Trace is ONLY defined for Square Matrices.\n");
        return;
    }
    int diagonal_sum = 0;
    for(int i=0; i<r; i++) {
        diagonal_sum += matrix[i][i];
    }
    printf("\nThe Trace is: %d\n", diagonal_sum);
}

int** rotate_matrix_clock(int** matrix, int *r, int *c) {
    //Rotate = Transpose + Reverse Rows
    matrix = transpose_matrix(matrix, r, c);
    
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
    printf("The matrix has been rotated Clockwise!\n");
    return matrix;
}

void add_matrix(int** matrix, int r, int c) {
    printf("Enter elements of the second matrix (%dx%d):\n", r, c);

    //Safer input with relloc
    int** temp = create_matrix(r, c);

    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            printf("[%d][%d]: ", i, j);
            scanf("%d", &temp[i][j]);
        }
    }

    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            matrix[i][j] += temp[i][j];
        }
    }
    
    free_matrix(temp, r);
    printf("Addition successful!\n");
}

int** multiply_matrix(int** matrix, int r, int *c) {
    int rows_b, cols_b;
    while(1) {
        rows_b = get_safe_int("\nEnter rows for Matrix B: ");
        cols_b = get_safe_int("Enter columns for Matrix B: ");
        if (rows_b == *c && cols_b > 0) break;
        printf("Invalid! Rows of B (%d) must match Cols of A (%d).\n", rows_b, *c);
    }

    int** matrix_b = create_matrix(rows_b, cols_b);
    printf("Enter elements of Matrix B:\n");
    for(int i=0; i<rows_b; i++){
        for(int j=0; j<cols_b; j++){
            printf("[%d][%d]: ", i, j);
            scanf("%d", &matrix_b[i][j]);
        }
    }

    //Result matrix size is r x cols_b
    int** result = create_matrix(r, cols_b);

    //Initialize with 0
    for(int i=0; i<r; i++)
        for(int j=0; j<cols_b; j++) 
            result[i][j] = 0;

    //Multiplication Logic
    for(int i=0; i<r; i++){
        for(int j=0; j<cols_b; j++){
            for(int k=0; k<*c; k++){
                result[i][j] += matrix[i][k] * matrix_b[k][j];
            }
        }
    }

    //Cleanup
    free_matrix(matrix, r);   //Free old A
    free_matrix(matrix_b, rows_b); //Free B

    *c = cols_b; //Update col dimension
    printf("Multiplication successful!\n");
    return result;
}

void saddle_point(int** matrix, int r, int c) {
    int found_any = 0;
    for (int i=0; i<r; i++) {
        int min_val = matrix[i][0];
        int col_index = 0;
        for (int j=1; j<c; j++) {
            if (matrix[i][j] < min_val) {
                min_val = matrix[i][j];
                col_index = j;
            }
        }
        
        //Checking if min_val is Max in its column
        int is_max_in_col = 1; 
        for (int k=0; k<r; k++) {
            if (matrix[k][col_index] > min_val) {
                is_max_in_col = 0;
                break;
            }
        }
        if (is_max_in_col) {
            printf("Saddle Point at [%d][%d]: %d\n", i, col_index, min_val);
            found_any = 1;
        }
    }
    if (!found_any) printf("No Saddle Points found.\n");
}

void spiral_print(int** matrix, int r, int c) {
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

void apply_convolution(int** matrix, int r, int c) {
    //temporary buffer
    int** temp = create_matrix(r, c);

    printf("Edge detection Convolution (Laplacian)\n");
    //Copy borders
    for(int i=0; i<r; i++) {
        for(int j=0; j<c; j++) temp[i][j] = matrix[i][j];
    }

    for(int i=1; i<r-1; i++){
        for(int j=1; j<c-1; j++){
            // Laplacian Kernel:
            //  0 -1  0
            // -1  4 -1
            //  0 -1  0
            int sum = (4 * matrix[i][j]) 
                    - matrix[i-1][j] - matrix[i+1][j] 
                    - matrix[i][j-1] - matrix[i][j+1];
            temp[i][j] = sum;
        }
    }

    //Copy back to main matrix
    for (int i=0; i<r; i++) {
        for (int j=0; j<c; j++) {
            matrix[i][j] = temp[i][j];
        }
    }
    free_matrix(temp, r); // Clean up temp
    printf("Edge detection applied successfully!\n");
}