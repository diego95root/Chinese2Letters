#include <stdlib.h>
#include <png.h>
#include <string.h>
#include "parser.h"
#include "database.h"

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

void writeMatrix(int ** matrix, int width, int height){
    FILE * out = fopen("data", "w");
    
    if (out == NULL){
        printf("File 'out' couldn't be opened\n");
        exit(1);
    }

    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j += 1){
            fprintf(out, "%d ", matrix[i][j]);
        }   
        fprintf(out, "\n");
    }

    fclose(out);
}

charScore * orderCompare(char ** chars, char * compareTo, int count){
    
    charScore * scoreList = malloc(sizeof(charScore *) * (count * 2));
    
    for (int i = 0; i < count; i++){
        if (strcmp(chars[i], "") == 0){
            break;
        }

        charScore * element = &scoreList[i];

        element->name = malloc(sizeof(char) * 15);
        element->score = 1.5;

        strcpy(scoreList[i].name, chars[i]);
    }

    return scoreList;
}


int main(){

    int width = 50;
    int height = 50;

    Database * files = openDB("../chars/");
    
    char filename[] = "../chars/5c55_10.png";

    //maybe join them together to return a structu
    char ** strokeFiles = getStrokeFiles(12, files);
    int count = getNumberByStroke(12, files);
    
    charScore * sortedChars = orderCompare(strokeFiles, count);

    for (int i = 0; i < count; i++){
        printf("Name removed: %s (score %.2f)\n", sortedChars[i].name, sortedChars[i].score);
        free(sortedChars[i].name);
        //free(sortedChars[i]);
    }
    free(sortedChars);

    /*

    int ** matrix = image2matrix(filename, width, height);
    
    writeMatrix(matrix, width, height);

    for (int i = 0; i<width; i++){
        free(matrix[i]);
    }
    free(matrix);
    */

    closeDB(files);

    return 1;
}