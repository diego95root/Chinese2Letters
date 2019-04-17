#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "algorithm.h"

// to avoid calculating things twice, store data for grid in global variables,
// and update it whenever a new stroke is drawn. It will be compared to all the 
// images so it makes no sense to calculate it every time.

int mainIslandsWhite;
int mainIslandsBlack;
int initMode;

int row_pixels[500]; 
int col_pixels[500]; 
int col_top[500];    
int col_bottom[500]; 
int row_left[500];   
int row_right[500];

// code main idea from http://www.interviewdruid.com/find-the-number-of-islands-in-a-matrix/

/*
Cell can be entered if within range, not visited and is black
*/

int can_enter_cell(int matrix[ROWS][COLS], int is_visited[ROWS][COLS], int cur_row, int cur_col, int isWhite){
    
    if (matrix[cur_row][cur_col] == 0 && isWhite)
        return 0;
        
    else if (matrix[cur_row][cur_col] != 0 && !isWhite)
        return 0;

    if (cur_row < 0 || cur_row >= ROWS || cur_col < 0 || cur_col >= COLS || is_visited[cur_row][cur_col]) {

        return 0;
    }
 
    return 1;
}
 
/* Helper function to count the number of islands of 1's
matrix: 2d matrix consisting of 0's and 1's
is_visited: if cell (i, j) has been visited, is_visited[i][j] is set to 1
cur_row: row of the current cell being processed
cur_col: column of the current cell being processed
*/

void expand_search(int matrix[ROWS][COLS], int is_visited[ROWS][COLS], int cur_row, int cur_col, int isWhite){

    int i, j;
 
    is_visited[cur_row][cur_col] = 1;
 
    /*For the current cell, find out if we can continue the island of 1's
    with its neighbors. Each cell has 9 neighbors. The rows
    of neighbors will vary from cur_row - 1 to cur_row + 1
    The columns of the neighbors will vary from cur_col - 1
    to cur_col + 1*/

    for (i = -1; i <= 1; ++i) {
        for (j = -1; j <= 1; ++j) {

            int is_safe_cell = can_enter_cell(matrix, is_visited, cur_row+i, cur_col+j, isWhite);

            if (is_safe_cell) {
                expand_search(matrix, is_visited, cur_row+i, cur_col+j, isWhite);
            }
        }
    }
}

int find_islands(int matrix[ROWS][COLS], int isWhite){

    int is_visited[ROWS][COLS];
    int i, j, count;
 
    /*Initially all cells are not yet visited*/
    for (i = 0; i < ROWS; ++i)
        for (j = 0; j < COLS; ++j) 
            is_visited[i][j] = 0;
 
    /*Search all the cells in matrix that are not yet visited*/
    count = 0;

    // better perform the check outside the loop than inside

    if (isWhite){
        for (i = 0; i < ROWS; ++i) {
            for (j = 0; j < COLS; ++j) {

                // absolute value because in grid it is stored as -257 due to 2s complement
                if (abs(matrix[i][j]) > 254 && !is_visited[i][j]) {
                    
                    expand_search(matrix, is_visited, i, j, 1); // island found
                    ++count;
                }
            }
        }
    }

    else { // look for black islands

        for (i = 0; i < ROWS; ++i) {
            for (j = 0; j < COLS; ++j) {

                if (matrix[i][j] == 0 && !is_visited[i][j]) {

                    expand_search(matrix, is_visited, i, j, 0);
                    ++count;
                }
            }
        }
    }

    return count;

}

// function obtained from https://www.geeksforgeeks.org/program-find-correlation-coefficient/

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

// set data for the drawn image on the grid, only needs to be calculated once per round of strokes

void setCompareTo(int compareTo[500][500], int mode){

    // depending on the mode do different operations, but always correlation

    if (mode > 0){

        mainIslandsBlack = find_islands(compareTo, 0);  // 0 to get black islands
    
    }
    
    if (mode > 1){
     
        mainIslandsWhite = find_islands(compareTo, 1); // 1 to get white islands

    }

    // reset all arrays to 0

    memset(row_pixels, 0, sizeof(row_pixels));
    memset(col_pixels, 0, sizeof(col_pixels));
    memset(col_bottom, 0, sizeof(col_bottom));
    memset(col_top, 0, sizeof(col_top));
    memset(row_left, 0, sizeof(row_left));
    memset(row_right, 0, sizeof(row_right));

    for (int x = 0; x < 500; x++){
        for (int y = 0; y < 500; y++){

            // row_pixels & column pixels handled here

            if (compareTo[x][y] == 0){
                row_pixels[x]++;
                col_pixels[y]++;
            }
        }
    }
        

    int left_found; 
    int right_found; 
    int colT_found;
    int colB_found;

    for (int i = 0; i < 500; i ++){
        
        left_found = 0;
        right_found = 0;
        colT_found = 0;
        colB_found = 0;

        for (int j = 0; j < 500; j ++){
            if (left_found && right_found && colT_found && colB_found){
                break;
            }
            if (compareTo[i][j] == 0 && !left_found){
                row_left[i] = j;
                left_found = 1;
            }
            if (compareTo[i][500-j-1] == 0 && !right_found){
                row_right[i] = j;
                right_found = 1;
            }
            if (compareTo[j][i] == 0 && !colT_found){
                col_top[i] = j;
                colT_found = 1;
            }
            if (compareTo[500-j-1][i] == 0 && !colB_found){
                col_bottom[i] = j;
                colB_found = 1;
            }
        }
    }

}

// helper function that takes a matrix of NxM dimensions and updates two arrays
// of size N and M with the number of black elements in the rows N and cols M

void countColsRows(int main[500][500], int rows[500], int cols[500]){
    
    for (int x = 0; x < 500; x++){
        for (int y = 0; y < 500; y++){

            // row_pixels & column pixels handled here

            if (main[x][y] == 0){
                rows[x]++;
                cols[y]++;
            }

        }
    }
}

// main function that controls the algorithm behaviour

double compareAlgorithm(int compareTo[500][500], int matrix[500][500], int initFlag, int mode){

    // To improve efficiency calculations on compareTo should only be done once,
    // as they are expensive and all the matrices are being compared to the same.
    // if flag then calculate compareTo for all the rest of the set or if mode
    // has been changed from the UI
    
    if (initFlag || mode != initMode){

        setCompareTo(compareTo, mode);
        initMode = mode;

    }

    if (mode == 1){
        
        int blacks = find_islands(matrix, 0);

        if (blacks != mainIslandsBlack){

            // return difference so that results with more different
            // islands have lower scores than those that differ by 
            // one or two

            return 0.4 - 0.01 * abs(blacks-mainIslandsBlack);
        }
    }

    else if (mode == 2){

        int blacks = find_islands(matrix, 0);
        int whites = find_islands(matrix, 1);

        // same as above but with both blacks and whites

        if (whites != mainIslandsWhite || blacks != mainIslandsBlack){
            return 0.4 - 0.01 * (abs(blacks-mainIslandsBlack) 
                                + abs(whites-mainIslandsWhite));
        }
    }

    // idea for the arrays and the correlation taken from 
    // https://stackoverflow.com/questions/22786288/ocr-and-character-similarity

    int row_pixels2[500] = {0}; 
    int col_pixels2[500] = {0}; 
    int col_top2[500] = {0};    
    int col_bottom2[500] = {0}; 
    int row_left2[500] = {0};   
    int row_right2[500] = {0};

    countColsRows(matrix, row_pixels2, col_pixels2);
        
    int left_found; 
    int right_found; 
    int colT_found;
    int colB_found;

    for (int i = 0; i < 500; i ++){
        
        left_found = 0;
        right_found = 0;
        colT_found = 0;
        colB_found = 0;

        for (int j = 0; j < 500; j ++){
            if (left_found && right_found && colT_found && colB_found){
                break;
            }
            if (matrix[i][j] == 0 && !left_found){
                row_left2[i] = j;
                left_found = 1;
            }
            if (matrix[i][500-j-1] == 0 && !right_found){
                row_right2[i] = j;
                right_found = 1;
            }
            if (matrix[j][i] == 0 && !colT_found){
                col_top2[i] = j;
                colT_found = 1;
            }
            if (matrix[500-j-1][i] == 0 && !colB_found){
                col_bottom2[i] = j;
                colB_found = 1;
            }
        }
    }

    double a = correlationCoefficient(row_pixels, row_pixels2, 500);
    double b = correlationCoefficient(col_pixels, col_pixels2, 500);
    double c = correlationCoefficient(col_top, col_top2, 500);
    double d = correlationCoefficient(col_bottom, col_bottom2, 500);
    double e = correlationCoefficient(row_left, row_left2, 500);
    double f = correlationCoefficient(row_right, row_right2, 500);

    return (a+b+c+d+e+f)/6;
}

