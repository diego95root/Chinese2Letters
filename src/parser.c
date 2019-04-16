#include <stdlib.h>
#include <png.h>
#include <string.h>
#include "database.h"
#include "parser.h"
#include "algorithm.h"


// Creates and returns a database structure from the given path as 
// a string

Database * parserGetDB(char * path){

    Database * files = openDB(path);

    return files;
}

// Closes the database structure freeing everything to prevent leaks

void parserEnd(Database * files){
    closeDB(files);
}

// Given a database pointer and the number of strokes drawn and the
// matrix where they are drawn, returns a list of sorted results
// (chinese characters and their index of similarity) in a structure 
// called charScoreList

charScoreList * parserInit(Database * files, int stroke, int matrix[ROWS][COLS], int mode){
    
    char ** strokeFiles = getStrokeFiles(stroke, files);
    int count = getNumberByStroke(stroke, files);

    charScoreList * valueChars;

    if (count == -1){
        valueChars = orderCompare(strokeFiles, matrix, 0, mode);
        free(strokeFiles[0]);
        free(strokeFiles);
    }
    else {
        valueChars = orderCompare(strokeFiles, matrix, count, mode);
    }

    return valueChars;
}

// Writes the bytes from an image from a specified path into a matrix,
// both passed as arguments

void image2matrix(int matrix[ROWS][COLS], char * name){

    
    FILE *fp = fopen(name, "r");
    
    // set up necessary vars for libpng to work

    png_structp pngptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop pnginfo = png_create_info_struct(pngptr);

    png_set_palette_to_rgb(pngptr);
    png_init_io(pngptr, fp);

    png_bytepp rows;
    png_read_png(pngptr, pnginfo, PNG_TRANSFORM_IDENTITY, NULL);
    rows = png_get_rows(pngptr, pnginfo);

    // traverse png file and copy values to array

    for (int i = 0; i < ROWS; i++){
        for (int j = 0; j < COLS * 3; j += 3){ // each color stored as 3 contiguous values: R G B
            int val = (rows[i][j] + rows[i][j + 1] + rows[i][j + 2])/3;
            matrix[i][j/3] = val;
        }   
    }

    // free memory to avoid leaks
    
    png_destroy_read_struct(&pngptr, &pnginfo, NULL);
    fclose(fp);
}

// Writes a matrix to a file that has the name from outName

void writeMatrix(int matrix[ROWS][COLS], char * outName){
    FILE * out = fopen(outName, "w");
    
    if (out == NULL){
        printf("File 'out' couldn't be opened\n");
        exit(1);
    }

    for (int i = 0; i < ROWS; i++){
        for (int j = 0; j < COLS; j += 1){
            if (matrix[i][j] < 0){
                matrix[i][j] = 255;
            }
            fprintf(out, "%d ", matrix[i][j]);
        }   
        fprintf(out, "\n");
    }

    fclose(out);
}

// Reads the data from a file specified as filename and writes
// it into a matrix

void readMatrix(int matrix[ROWS][COLS], char *filename){
    
    FILE * file;
    file = fopen(filename, "r");

    int i = 0;
    int count = 0;

    fscanf (file, "%d", &i);    
    while (!feof (file)){  
        matrix[count/COLS][count%COLS] = i;
        fscanf (file, "%d", &i); 
        count++;
    }
    fclose (file);  
}

// Given an array of strings of length count, each one being the
// name of a file with a chinese character, and a matrix with a 
// character drawn, it returns a structure containing the strings with
// a score (of type double). The score means the similarity of the 
// image in the file to the matrix (drawn by the user). The structure
// contains the results in sorted order (highest similarity to lowest).

charScoreList * orderCompare(char ** chars, int compareTo[ROWS][COLS], int count, int mode){
    
    charScoreList * scoreList = malloc(sizeof(charScoreList));

    scoreList->elements = malloc(sizeof(charScore *) * count);

    scoreList->count = count;

    for (int i = 0; i < count; i++){

        scoreList->elements[i] = malloc(sizeof(charScore));

        scoreList->elements[i]->name = malloc(sizeof(char) * 15);

        strcpy(scoreList->elements[i]->name, chars[i]);
        
        char sourcePath[30] = "../chars3/";
        int matrix[ROWS][COLS];

        strcat(sourcePath, chars[i]);
        image2matrix(matrix, sourcePath);

        // algorithm HERE returns double as score
        // the last parameter indicates if new set of strokes to
        // recalculate the data from the drawing pane

        double score = compareAlgorithm(compareTo, matrix, (i == 0), mode);

        //printf("%f for %s\n", score, sourcePath);        

        scoreList->elements[i]->score = score;

    }

    sortList(scoreList->elements, count);

    return scoreList;
}


void freeCharScoreList(charScoreList * list){

    for (int i = 0; i < list->count; i++){
        printf("Now freeing %s", list->elements[i]->name);
        free(list->elements[i]->name);
        printf(", freeing all element.");
        free(list->elements[i]);
        printf("Everything freed!\n");
    }
    
    free(list->elements);
    free(list);
}

// Bubble sort implementation, as lists are not too big and the difference
// in performance is not comparable. From a list with charscores and its 
// length order it based on the score of each element.

void sortList(charScore ** list, int count){
    
    int none;
    
    do {

        none = 0; // if not changed then everything is ordered
        
        for (int x = 0; x < count-1; x++){
            
            if (list[x]->score < list[x+1]->score){
                
                charScore * a = list[x+1];
                list[x+1] = list[x];
                list[x] = a;
                none = 1;

            }
        }

    } while (none != 0);
}

// Basically same function as before, but tested with an array of doubles,
// so that I know it works. The only thing that changes is that I don't
// compare the score of the element of charScore, but the element itself,
// which is a double.

void sortListTest(double * list, int count){
    int none;
    do {
        none = 0;
        for (int x = 0; x < count-1; x++){
            if (list[x] < list[x+1]){
                double a = list[x+1];
                list[x+1] = list[x];
                list[x] = a;
                none = 1;
            }
        }
    } while (none != 0);
}