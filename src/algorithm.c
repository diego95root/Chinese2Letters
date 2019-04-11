#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_NUM_COLS 500
#define MAX_NUM_ROWS 500

/*
Helper function that indicates if we can enter the cell or not
*/
int can_enter_cell(int matrix[][MAX_NUM_COLS], int is_visited[][MAX_NUM_COLS], 
        int cur_row, int cur_col, int n_rows, int n_cols){
    /*If we are outside the bounds of the matrix or
    if the cell is already visited or if the value in cell is 0
    then we shouldn't enter the cell */
    if (cur_row < 0 || cur_row >= n_rows 
        || cur_col < 0 || cur_col >= n_cols
        || is_visited[cur_row][cur_col] 
        || matrix[cur_row][cur_col] != 0) {
        return 0;
    }
 
    return 1;
}
 
 
/* Helper function to count the number of islands of 1's
matrix: 2d matrix consisting of 0's and 1's
is_visited: if cell (i, j) has been visited, is_visited[i][j] is set to 1
cur_row: row of the current cell being processed
cur_col: column of the current cell being processed
n_rows: number of rows in the matrix
n_cols: number of columns in the matrix 
*/
void expand_search(int matrix[][MAX_NUM_COLS], int is_visited[][MAX_NUM_COLS], 
    int cur_row, int cur_col, int n_rows, int n_cols){
    int i, j;
 
    is_visited[cur_row][cur_col] = 1;
 
    /*For the current cell, find out if we can continue the island of 1's
    with its neighbors. Each cell has 9 neighbors. The rows
    of neighbors will vary from cur_row - 1 to cur_row + 1
    The columns of the neighbors will vary from cur_col - 1
    to cur_col + 1*/
    for (i = -1; i <= 1; ++i) {
        for (j = -1; j <= 1; ++j) {
            int is_safe_cell = can_enter_cell(matrix, is_visited, cur_row+i, cur_col+j, n_rows, n_cols);
 
            if (is_safe_cell) {
                expand_search(matrix, is_visited, cur_row+i, cur_col+j, n_rows, n_cols);
            }
        }
    }
}
 
int find_islands(int matrix[500][500], int n_rows, int n_cols){

    int is_visited[500][500];
    int i, j, count;
 
    /*Initially all cells are not yet visited*/
    for (i = 0; i < n_rows; ++i)
        for (j = 0; j < n_cols; ++j) 
            is_visited[i][j] = 0;
 
    /*Search all the cells in matrix that are not yet visited*/
    count = 0;
    for (i = 0; i < n_rows; ++i) {
        for (j = 0; j < n_cols; ++j) {
            if (matrix[i][j] == 0 && !is_visited[i][j]) {

                /*We have found an island. Now expand the island 
                in all directions*/
                expand_search(matrix, is_visited, i, j, n_rows, n_cols);
                ++count;
            }
        }
    }
    return count;
}

double correlationCoefficient(int X[500], int Y[500], int n) { 
  
    double sum_X = 0, sum_Y = 0, sum_XY = 0; 
    double squareSum_X = 0, squareSum_Y = 0; 
  
    for (int i = 0; i < n; i++){ 
        // sum of elements of array X. 
        sum_X = sum_X + X[i]; 
  
        // sum of elements of array Y. 
        sum_Y = sum_Y + Y[i]; 
  
        // sum of X[i] * Y[i]. 
        sum_XY = sum_XY + X[i] * Y[i]; 
  
        // sum of square of array elements. 
        squareSum_X = squareSum_X + X[i] * X[i]; 
        squareSum_Y = squareSum_Y + Y[i] * Y[i]; 
    } 
  
    // use formula for calculating correlation coefficient. 
    double corr = (double)(n * sum_XY - sum_X * sum_Y)  
                  / sqrt((double)(n * squareSum_X - sum_X * sum_X)  
                      * (n * squareSum_Y - sum_Y * sum_Y)); 
  
    return corr; 
} 

double compareAlgorithm(int compareTo[500][500], int ** matrix){


    int temp[500][500];

    for (int i = 0; i < 500; ++i)
        for (int j = 0; j < 500; ++j) 
            temp[i][j] = matrix[i][j];

    if (find_islands(temp, 500, 500) != find_islands(compareTo, 500, 500)){
        return 0;
    }


    double result1 = 0;

    double tolerance = 1;

    // actual character

    int row_pixels[500] = {0}; 
    int col_pixels[500] = {0}; 
    int col_top[500] = {0};    
    int col_bottom[500] = {0}; 
    int row_left[500] = {0};   
    int row_right[500] = {0};

    // sample

    int row_pixels2[500] = {0}; 
    int col_pixels2[500] = {0}; 
    int col_top2[500] = {0};    
    int col_bottom2[500] = {0}; 
    int row_left2[500] = {0};   
    int row_right2[500] = {0};

    for (int i = 5; i < 45; i ++){ // exclude borders
        for (int j = 5; j < 45; j ++){
            
            double sum1 = 0;

            double sum2 = 0;

            if (45 - i < 40 && 45 - i > 5 && 45 - j < 40 && 45 - j > 5){
                tolerance = 1;
            }
            else {
                tolerance = 0.8;
            }

            for (int x = i * 10; x < (i+1)*10; x++){
                for (int y = j * 10; y < (j+1)*10; y++){

                    sum1 += tolerance * (matrix[x][y] / 255);
                    if (compareTo[x][y] < 0){ // handle this somewhere else
                        sum2 += tolerance * 1;
                    }
                    else {
                        sum2 += tolerance * (compareTo[x][y] / 255);
                    }

                    // row_pixels & column pixels handled here

                    if (compareTo[x][y] == 0){
                        row_pixels[x]++;
                        col_pixels[y]++;
                    }

                    if (matrix[x][y] == 0){
                        row_pixels2[x]++;
                        col_pixels2[y]++;
                    }

                }
            }

            //average[i][j] = sum1/100;
            //printf("%f and %f\n", sum1, sum2);
            result1 += 1 - (abs(sum1-sum2)/100);
            
            /*
            printf("Sum1: %f\n", sum1);
            printf("Sum2: %f\n", sum2);
            printf("Formula: %f\n", 1-(abs(sum1-sum2)/100));
            */
        }
        //printf("\nRow: %f\n", result);
    }

    for (int i = 0; i < 500; i ++){
        for (int j = 0; j < 500; j ++){
            if (compareTo[i][j] == 0){
                row_left[i] = j;
                break;
            }
        }
        for (int j = 0; j < 500; j ++){
            if (compareTo[i][500-j-1] == 0){
                row_right[i] = j;
                break;
            }
        }
        for (int j = 0; j < 500; j ++){
            if (compareTo[j][i] == 0){
                col_top[i] = j;
                break;
            }
        }
        for (int j = 0; j < 500; j ++){
            if (compareTo[500-j-1][i] == 0){
                col_bottom[i] = j;
                break;
            }
        }

        for (int j = 0; j < 500; j ++){
            if (matrix[i][j] == 0){
                row_left2[i] = j;
                break;
            }
        }
        for (int j = 0; j < 500; j ++){
            if (matrix[i][500-j-1] == 0){
                row_right2[i] = j;
                break;
            }
        }
        for (int j = 0; j < 500; j ++){
            if (matrix[j][i] == 0){
                col_top2[i] = j;
                break;
            }
        }
        for (int j = 0; j < 500; j ++){
            if (matrix[500-j-1][i] == 0){
                col_bottom2[i] = j;
                break;
            }
        }
    }
    
    


    /*
    for (int i = 0; i < 500; i ++){
        printf("Pixels in %02d: %d\n", i, row_left[i]);
    }
    */

    double a = correlationCoefficient(row_pixels, row_pixels2, 500);
    double b = correlationCoefficient(col_pixels, col_pixels2, 500);
    double c = correlationCoefficient(col_top, col_top2, 500);
    double d = correlationCoefficient(col_bottom, col_bottom2, 500);
    double e = correlationCoefficient(row_left, row_left2, 500);
    double f = correlationCoefficient(row_right, row_right2, 500);

    //printf("Next:\n[*] %f\n[*] %f\n[*] %f\n[*] %f\n[*] %f\n[*] %f\n", a, b, c, d, e, f);

    //printf("Final result: %f\n", result/(50*50));
    //return result/(40*40);
    return ((result1/(40*40)) + ((a+b+c+d+e+f)/6))/2;
}

