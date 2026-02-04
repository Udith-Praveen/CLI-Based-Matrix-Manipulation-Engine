#include <stdio.h>
#include "matrix_toolkit.h"

int main() {
    printf("Welcome to the Matrix manipulation toolkit!\n");

    int matrix[CAPACITY][CAPACITY];
    int r, c;
    
    //Initial Dimensions Check
    while(1){
        r = get_safe_int("Enter the number of rows you require in the matrix: \n");
        c = get_safe_int("Enter the number of columns you require in the matrix: \n");
        if (r > 0 && r <= CAPACITY && c > 0 && c <= CAPACITY) {
            break;
        }
        printf("Invalid dimensions! Must be between 1 and %d.\n", CAPACITY);
    }

    //Input Loop
    printf("Enter the elements of the matrix: \n");
    for(int i=0; i < r; i++){
        for(int j=0; j < c; j++){
            if (scanf("%d", &matrix[i][j]) != 1) {
                printf("That's not a number! Try again.\n");
                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF);
                j--; 
            }
        }
        printf("\n");
    }

    //Main Menu Loop
    char ans;
    int reply;
    while(1){
        printf("\nCurrent Matrix: \n");
        for (int i = 0; i < r; i++) {
            for(int j=0; j < c ; j++){
                printf("%4d ", matrix[i][j]);
            }
            printf("\n"); 
        }
        printf("\n");
        printf("Manipulate the Matrix? (y/n): ");
        scanf(" %c", &ans);

        if(ans=='n'||ans=='N'){
            printf("\nSee you again later! ");
            break;
        }
        else if(ans=='y'||ans=='Y'){
            printf(" MATRIX MANIPULATION TOOLKIT \n");
            printf("Choose an operation to perform:\n");
            printf("1. Multiply the matrix by a scalar constant\n");
            printf("2. Calculate sums of individual rows and columns\n");
            printf("3. Find the Transpose of the matrix\n");
            printf("4. Calculate the Trace (Sum of main diagonal)\n");
            printf("5. Rotate the matrix 90 degrees clockwise\n");
            printf("6. Add a second matrix to the current one\n");
            printf("7. Multiply the current matrix by a second matrix\n");
            printf("8. Find the Saddle Point (Min in row, Max in col)\n");
            printf("9. Print the matrix in Spiral Order\n");
            printf("10. Convolution (Use the Laplacian filter!)\n");
            
            reply = get_safe_int(" Enter your choice (1-10): ");

            switch(reply){
                case 1: scalar_multi(matrix, r, c); break;
                case 2: rowandcolumn_sum(matrix, r, c); break;
                case 3: transpose_matrix(matrix, &r, &c); break;
                case 4: trace_matrix(matrix, r, c); break;
                case 5: rotate_matrix_clock(matrix, &r, &c); break;
                case 6: add_matrix(matrix, r, c); break;
                case 7: multiply_matrix(matrix, r, &c); break;
                case 8: saddle_point(matrix, r, c); break;
                case 9: spiral_print(matrix, r, c); break;
                case 10: apply_convolution(matrix, r, c); break;
                default: printf("Invalid choice!\n");
            }
        }
    }
    return 0;
}