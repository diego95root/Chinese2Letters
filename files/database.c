
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include "database.h"

#define DEBUG 0

struct array_len {
    char ** names;
    int length;
};

/*
struct dirfile {
    ino_t d_ino;
    char d_name[NAME_MAX]; // NAME_MAX defined in stdio.h (or FILENAME_MAX)
    off_t d_off;
    unsigned short int d_reclen;
    unsigned int d_type;
};

enum
  {
    DT_UNKNOWN = 0,
# define DT_UNKNOWN        DT_UNKNOWN
    DT_FIFO = 1,
# define DT_FIFO        DT_FIFO
    DT_CHR = 2,
# define DT_CHR                DT_CHR
    DT_DIR = 4,
# define DT_DIR                DT_DIR
    DT_BLK = 6,
# define DT_BLK                DT_BLK
    DT_REG = 8,
# define DT_REG                DT_REG
    DT_LNK = 10,
# define DT_LNK                DT_LNK
    DT_SOCK = 12,
# define DT_SOCK        DT_SOCK
    DT_WHT = 14
# define DT_WHT                DT_WHT
  };
*/

struct array_len getFiles(char * directory){

    DIR *dir;
    struct dirent *file;
    
    int num_files = 0;

    if ((dir = opendir(directory)) != NULL) {
        while ((file = readdir(dir)) != NULL) {
            if (file->d_type == DT_REG){ 
                
                num_files++;

            }
        }
        closedir (dir);
    } 
    else {
        perror("");
    }

    if (DEBUG){
        printf("Number of files: %d\n", num_files);
    }

    struct array_len array;
    array.names = malloc(num_files * sizeof(char *));
    array.length = num_files;

    int iterator = 0;

    dir = opendir(directory);
    while ((file = readdir(dir)) != NULL) {
        if (file->d_type == DT_REG){ 
            if (DEBUG){
                printf("---------------\n");
                printf("d_ino: %d\n", file->d_ino);
                printf("d_name: %s\n", file->d_name);
                printf("d_off: %d\n", file->d_off);
                printf("d_reclen: %d\n", file->d_reclen);
                printf("d_type: %d\n", file->d_type);
            }
            
            array.names[iterator] = malloc(file->d_reclen * sizeof(char));
            strcpy(array.names[iterator], file->d_name);

            iterator++;
        }
    }
    closedir(dir);

    return array;
}

int array2struct(){
    /*
    char * delimiter  = ".";
    char * delimiter2 = "_";

    char * ptr = strtok(file->d_name, delimiter);
    ptr = strtok(file->d_name, delimiter2);

    while (ptr != NULL){
                    
        printf("'%s'\n", ptr);
        ptr = strtok(NULL, delimiter2);
    */
    return 1;
}

int main(){
    struct array_len files = getFiles("../chars/");
    for (int i = 0; i < files.length; i++){
        printf("File %d: %s\n", i+1, files.names[i]);
    }
    return 1;
}