#include <stdlib.h>
#include <png.h>

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

int main(){

    int width = 50;
    int height = 50;

    char filename[] = "../chars/4e8b_08.png";

    int ** matrix = image2matrix(filename, width, height);
    
    /*
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j += 1){
            printf("%d ", matrix[i][j]);
        }   
        printf("\n");
    }
    */

    for (int i = 0; i<width; i++){
        free(matrix[i]);
    }
    free(matrix);
    
    return 1;
}