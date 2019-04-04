#include <stdlib.h>
#include <png.h>
#include <string.h>
#include "parser.h"
#include "database.h"

Database * files;
int init = 0;

charScoreList * parserInit(int stroke){
    
    if (init == 0){
        files = openDB("../chars2/");
        init = 1;
    }
    
    char filename[] = "../chars/5c55_10.png";

    char ** strokeFiles = getStrokeFiles(stroke, files);
    int count = getNumberByStroke(stroke, files);

    charScoreList * valueChars;

    if (count == -1){
        valueChars = orderCompare(strokeFiles, filename, 0);
        free(strokeFiles[0]);
        free(strokeFiles);
    }
    else {
        valueChars = orderCompare(strokeFiles, filename, count);
    }

    return valueChars;
}

void parserEnd(){
    closeDB(files);
}

int ** image2matrix(char * name, int width, int height){

    // allocate needed memory for the image

    int **matrix;
    matrix = malloc(sizeof(int[width][height]));

    for (int i = 0; i<width; i++){
        matrix[i] = malloc(sizeof(int) * height);
    }
    
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

    for (int i = 0; i < height; i++){
        for (int j = 0; j < width * 3; j += 3){ // each color stored as 3 contiguous values: R G B
            int val = (rows[i][j] + rows[i][j + 1] + rows[i][j + 2])/3;
            matrix[i][j/3] = val;
        }   
    }

    // free memory to avoid leaks
    
    png_destroy_read_struct(&pngptr, &pnginfo, NULL);
    fclose(fp);

    return matrix;
}

void writeMatrix(int matrix[][500], int width, int height){
    FILE * out = fopen("data", "w");
    
    if (out == NULL){
        printf("File 'out' couldn't be opened\n");
        exit(1);
    }

    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j += 1){
            if (matrix[i][j] < 0){
                matrix[i][j] = 255;
            }
            fprintf(out, "%d ", matrix[i][j]);
        }   
        fprintf(out, "\n");
    }

    fclose(out);
}

charScoreList * orderCompare(char ** chars, char * compareTo, int count){
    
    charScoreList * scoreList = malloc(sizeof(charScoreList *) + 8);

    scoreList->elements = malloc(sizeof(charScore *) * (count*2));

    scoreList->count = count;

    for (int i = 0; i < count; i++){

        if (strcmp(chars[i], "") == 0){
            break;
        }

        charScore * element = malloc(sizeof(charScore *) + 8);

        element->name = malloc(sizeof(char) * 15);
        element->score = 1.5;

        strcpy(element->name, chars[i]);

        scoreList->elements[i] = *element;

        free(element);

    }

    return scoreList;
}

void freeCharScoreList(charScoreList * list){

    for (int i = 0; i < list->count; i++){
        
        //printf("%s at %d\n", list->elements[i].name, i);
        
        free(list->elements[i].name);

        //free(&list->elements[i]);
    }
    free(list->elements);
    free(list);
}

void sortList(charScore * list, int count){
    int none;
    do {
        none = 0;
        for (int x = 0; x < count-1; x++){
            if (list[x].score > list[x+1].score){
                charScore a = list[x+1];
                list[x+1] = list[x];
                list[x] = a;
                none = 1;
            }
        }
    } while (none != 0);
}

void sortListTest(double * list, int count){
    int none;
    do {
        none = 0;
        for (int x = 0; x < count-1; x++){
            if (list[x] > list[x+1]){
                double a = list[x+1];
                list[x+1] = list[x];
                list[x] = a;
                none = 1;
            }
        }
    } while (none != 0);
}

/*
int main3(){

    int width = 50;
    int height = 50;

    Database * files = openDB("../chars/");
    
    char filename[] = "../chars/5c55_10.png";

    //maybe join them together to return a struct
    char ** strokeFiles = getStrokeFiles(12, files);
    int count = getNumberByStroke(12, files);
    
    charScore * valueChars = orderCompare(strokeFiles, filename, count);

    charScore * sortedChars = sortList(valueChars, count);


    for (int i = 0; i < count; i++){
        printf("Name removed: %s (score %.2f)\n", sortedChars[i].name, sortedChars[i].score);
        free(sortedChars[i].name);
    }
    free(sortedChars);

    /*

    int ** matrix = image2matrix(filename, width, height);
    
    writeMatrix(matrix, width, height);

    for (int i = 0; i<width; i++){
        free(matrix[i]);
    }
    free(matrix);
    

    closeDB(files);

    return 1;
}
*/