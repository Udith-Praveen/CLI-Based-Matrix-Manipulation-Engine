#include <stdio.h>
#include <stdlib.h> // Required for free
#include "matrix_toolkit.h"

int main() {
    int r, c;
    
    //Get Dimensions
    while(1){
        r = get_safe_int("Enter the number of Rows you require in the Matrix: ");
        c = get_safe_int("Enter the number of Columns you require in the Matrix: ");
        if (r > 0 && c > 0) break;
        printf("Dimensions must be > 0.\n");
    }

    //DYNAMIC ALLOCATION (Heap)
    int** matrix = create_matrix(r, c);

    printf("Enter the elements (%dx%d):\n", r, c);
    for(int i=0; i < r; i++){
        for(int j=0; j < c; j++){
            if (scanf("%d", &matrix[i][j]) != 1) {
                printf("Invalid input! Resetting element to 0.\n");
                matrix[i][j] = 0;
                int ch; while ((ch = getchar()) != '\n' && ch != EOF);
            }
        }
    }

    //Main Menu
    char ans;
    int reply;
    while(1){
        printf("\n--- Current Matrix (%dx%d) ---\n", r, c);
        for (int i = 0; i < r; i++) {
            for(int j=0; j < c ; j++){
                printf("%4d ", matrix[i][j]);
            }
            printf("\n"); 
        }

        printf("\nManipulate? (y/n): ");
        scanf(" %c", &ans);

        if(ans=='n'||ans=='N') break;
        else if(ans=='y'||ans=='Y'){
            printf("\n[OPERATIONS]\n");
            printf("1. Scalar Multiply\n");
            printf("2. Row/Col Sums\n");
            printf("3. Transpose (Reallocates Memory)\n");
            printf("4. Trace\n");
            printf("5. Rotate 90 deg (Reallocates Memory)\n");
            printf("6. Add Matrix\n");
            printf("7. Multiply Matrix (Reallocates Memory)\n");
            printf("8. Saddle Point\n");
            printf("9. Spiral Print\n");
            printf("10. Convolution (Apply Laplacian Filter!)\n");
            
            reply = get_safe_int("Choice (1-10): ");

            switch(reply){
                case 1: scalar_multi(matrix, r, c); break;
                case 2: rowandcolumn_sum(matrix, r, c); break;
                //For operations that change size of the matrix, use pointers
                case 3: matrix = transpose_matrix(matrix, &r, &c); break;
                case 4: trace_matrix(matrix, r, c); break;
                case 5: matrix = rotate_matrix_clock(matrix, &r, &c); break;
                case 6: add_matrix(matrix, r, c); break;
                case 7: matrix = multiply_matrix(matrix, r, &c); break;
                case 8: saddle_point(matrix, r, c); break;
                case 9: spiral_print(matrix, r, c); break;
                case 10: apply_convolution(matrix, r, c); break;
                default: printf("Invalid choice!\n");
            }
        }
    }

    //No Memory Leaks
    free_matrix(matrix, r);
    printf("Memory freed. Exiting.\n");

    return 0;

}
