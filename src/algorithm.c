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

int rowPixels[ROWS]; 
int colPixels[ROWS]; 
int colTop[ROWS];    
int colBottom[ROWS]; 
int rowLeft[ROWS];   
int rowRight[ROWS];

// code main idea from http://www.interviewdruid.com/find-the-number-of-islands-in-a-matrix/

/*
Cell can be entered if within range, not visited and is black
*/

int canEnterCell(int matrix[ROWS][COLS], int isVisited[ROWS][COLS], int currentRow, int currentCol, int isWhite){
    
    if (matrix[currentRow][currentCol] == 0 && isWhite)
        return 0;
        
    else if (matrix[currentRow][currentCol] != 0 && !isWhite)
        return 0;

    if (currentRow < 0 || currentRow >= ROWS || currentCol < 0 || currentCol >= COLS 
        || isVisited[currentRow][currentCol]) {

        return 0;
    }
 
    return 1;
}
 
/* Helper function to count the number of islands of 1's
matrix: 2d matrix consisting of 0's and 1's
isVisited: if cell (i, j) has been visited, isVisited[i][j] is set to 1
currentRow: row of the current cell being processed
currentCol: column of the current cell being processed
*/

void expandSearch(int matrix[ROWS][COLS], int isVisited[ROWS][COLS], int currentRow, int currentCol, int isWhite){

    int i, j;
 
    isVisited[currentRow][currentCol] = 1;
 
    /*For the current cell, find out if we can continue the island of 1's
    with its neighbors. Each cell has 9 neighbors. The rows
    of neighbors will vary from currentRow - 1 to currentRow + 1
    The columns of the neighbors will vary from currentCol - 1
    to currentCol + 1*/

    for (i = -1; i <= 1; ++i) {
        for (j = -1; j <= 1; ++j) {

            int isSafeCell = canEnterCell(matrix, isVisited, currentRow+i, currentCol+j, isWhite);

            if (isSafeCell) {
                expandSearch(matrix, isVisited, currentRow+i, currentCol+j, isWhite);
            }
        }
    }
}

int findIslands(int matrix[ROWS][COLS], int isWhite){

    int isVisited[ROWS][COLS];
    int i, j, count;
 
    /*Initially all cells are not yet visited*/
    for (i = 0; i < ROWS; ++i)
        for (j = 0; j < COLS; ++j) 
            isVisited[i][j] = 0;
 
    /*Search all the cells in matrix that are not yet visited*/
    count = 0;

    // better perform the check outside the loop than inside

    if (isWhite){
        for (i = 0; i < ROWS; ++i) {
            for (j = 0; j < COLS; ++j) {

                // absolute value because in grid it is stored as -257 due to 2s complement
                if (abs(matrix[i][j]) > 254 && !isVisited[i][j]) {
                    
                    expandSearch(matrix, isVisited, i, j, 1); // island found
                    ++count;
                }
            }
        }
    }

    else { // look for black islands

        for (i = 0; i < ROWS; ++i) {
            for (j = 0; j < COLS; ++j) {

                if (matrix[i][j] == 0 && !isVisited[i][j]) {

                    expandSearch(matrix, isVisited, i, j, 0);
                    ++count;
                }
            }
        }
    }

    return count;

}

// function obtained from https://www.geeksforgeeks.org/program-find-correlation-coefficient/

double correlationCoefficient(int X[ROWS], int Y[COLS], int n) { 
  
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

// helper function that takes a matrix of NxM dimensions and updates two arrays
// of size N and M with the number of black elements in the rows N and cols M

void countColsRows(int main[ROWS][COLS], int rows[ROWS], int cols[COLS]){
    
    for (int x = 0; x < ROWS; x++){
        for (int y = 0; y < COLS; y++){

            // rowPixels & column pixels handled here

            if (main[x][y] == 0){
                rows[x]++;
                cols[y]++;
            }

        }
    }
}

void countStartDirections(int main[ROWS][COLS], int top[COLS], int right[ROWS], int bottom[COLS], int left[ROWS]){

    int leftFound; 
    int rightFound; 
    int topFound;
    int bottomFound;

    for (int i = 0; i < ROWS; i ++){
        
        leftFound = 0;
        rightFound = 0;
        topFound = 0;
        bottomFound = 0;

        for (int j = 0; j < COLS; j ++){
            if (leftFound && rightFound && topFound && bottomFound){
                break;
            }
            if (main[i][j] == 0 && !leftFound){
                left[i] = j;
                leftFound = 1;
            }
            if (main[i][COLS-j-1] == 0 && !rightFound){
                right[i] = j;
                rightFound = 1;
            }
            if (main[j][i] == 0 && !topFound){
                top[i] = j;
                topFound = 1;
            }
            if (main[ROWS-j-1][i] == 0 && !bottomFound){
                bottom[i] = j;
                bottomFound = 1;
            }
        }
    }
}

// set data for the drawn image on the grid, only needs to be calculated once per round of strokes

void setCompareTo(int compareTo[ROWS][COLS], int mode){

    // depending on the mode do different operations, but always correlation

    if (mode > 0){

        mainIslandsBlack = findIslands(compareTo, 0);  // 0 to get black islands
    
    }
    
    if (mode > 1){
     
        mainIslandsWhite = findIslands(compareTo, 1); // 1 to get white islands

    }

    // reset all arrays to 0

    memset(rowPixels, 0, sizeof(rowPixels));
    memset(colPixels, 0, sizeof(colPixels));
    memset(colBottom, 0, sizeof(colBottom));
    memset(colTop, 0, sizeof(colTop));
    memset(rowLeft, 0, sizeof(rowLeft));
    memset(rowRight, 0, sizeof(rowRight));

    countColsRows(compareTo, rowPixels, colPixels);

    countStartDirections(compareTo, colTop, rowRight, colBottom, rowLeft);

}

// main function that controls the algorithm behaviour

double compareAlgorithm(int compareTo[ROWS][COLS], int matrix[ROWS][COLS], int initFlag, int mode){

    // To improve efficiency calculations on compareTo should only be done once,
    // as they are expensive and all the matrices are being compared to the same.
    // if flag then calculate compareTo for all the rest of the set or if mode
    // has been changed from the UI
    
    if (initFlag || mode != initMode){

        setCompareTo(compareTo, mode);
        initMode = mode;

    }

    if (mode == 1){
        
        int blacks = findIslands(matrix, 0);

        if (blacks != mainIslandsBlack){

            // return difference so that results with more different
            // islands have lower scores than those that differ by 
            // one or two

            return 0.35 - 0.01 * abs(blacks - mainIslandsBlack);
        }
    }

    else if (mode == 2){

        int blacks = findIslands(matrix, 0);
        int whites = findIslands(matrix, 1);

        // same as above but with both blacks and whites

        if (whites != mainIslandsWhite || blacks != mainIslandsBlack){
            return 0.35 - 0.01 * (abs(blacks - mainIslandsBlack) 
                                + abs(whites - mainIslandsWhite));
        }
    }

    // idea for the arrays and the correlation taken from 
    // https://stackoverflow.com/questions/22786288/ocr-and-character-similarity

    int rowPixels2[ROWS] = {0}; 
    int colPixels2[COLS] = {0}; 
    int colTop2[COLS] = {0};    
    int colBottom2[COLS] = {0}; 
    int rowLeft2[ROWS] = {0};   
    int rowRight2[ROWS] = {0};

    countColsRows(matrix, rowPixels2, colPixels2);
        
    countStartDirections(matrix, colTop2, rowRight2, colBottom2, rowLeft2);

    double a = correlationCoefficient(rowPixels, rowPixels2, ROWS);
    double b = correlationCoefficient(colPixels, colPixels2, COLS);
    double c = correlationCoefficient(colTop, colTop2, COLS);
    double d = correlationCoefficient(colBottom, colBottom2, COLS);
    double e = correlationCoefficient(rowLeft, rowLeft2, ROWS);
    double f = correlationCoefficient(rowRight, rowRight2, ROWS);

    return (a+b+c+d+e+f)/6;
}

