#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include "database.h"

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


// Takes a filename of the format XXXXXX_XX.png where the first X's are
// hex chars and the second two X's are the number of strokes. Returns
// an array of the two strings: the first hex chars and the strokes.

char ** splitFilename(char * name){

    char ** splitted = malloc(sizeof(char *) * 2);
    
    char * delimiter  = ".";
    char * delimiter2 = "_";

    char * ptr = strtok(name, delimiter); // don't take extension
    ptr = strtok(name, delimiter2);

    for (int i = 0; i < 2; i++){
                    
        splitted[i] = malloc(sizeof(char) * strlen(ptr)+1);

        char zero = ptr[0]; 
        if (i == 1 && atoi(&zero) == 0){ // check if second number has leading zero
            strcpy(splitted[i], &ptr[1]);
        }
        else {
            strcpy(splitted[i], ptr);
        }

        ptr = strtok(NULL, delimiter2);
    }

    return splitted;
}

// Adds a value to a an array by checking which is the last
// element (the empty string)

void addValue(char * value, char ** head, int len){

    for (int i = 0; i < len; i++){
        if (strcmp(head[i], "") == 0){
            strcpy(head[i], value);
            break;
        }
    }
}


// Taking the number of strokes and the database structure, it
// returns an array of all the filenames that contain characters with
// that number of strokes.

char ** getStrokeFiles(int stroke, Database * files){

    if (stroke > MAX_STROKES || stroke == 0){ // empty array if stroke not valid
        
        char ** strokeFiles = malloc(sizeof(char *));
        strokeFiles[0] = malloc(sizeof(char)*2);
        strcpy(strokeFiles[0], "");
        return strokeFiles;
    
    }

    return files->groups[stroke-1].names;
}


// Returns the number of characters that have a specified stroke
// number from the database 


int getNumberByStroke(int stroke, Database * files){
    
    if (stroke > MAX_STROKES || stroke <= 0){
        return -1;
    }

    return files->groups[stroke-1].count;
}


// Prints an array of strings terminated with an empty string

void printArray(char ** array){
    
    int i = 0;

    printf("[*] [");
    while (1){
        if (strcmp(array[i], "") == 0){
            if (i == 0){ // handle empty lists
               printf("]\n"); 
               return;
            }
            break;
        }
        printf("%s, ", array[i]);
        i++;
    }
    printf("\b\b]\n");
}


// openDB gets all filenames from a directory and based on the stroke
// number of the character stores them in a different array, keeping 
//count of the length of that array and the total number of characters. 
// Sort of a python dictionary. It returns that structure.


Database * openDB(char * directory){

    DIR *dir;
    struct dirent *file;
    
    Database * array = malloc(sizeof(Database));

    // array with the number of characters with x strokes
    int arr[MAX_STROKES] = {0};

    int numFiles = 0;

    if ((dir = opendir(directory)) != NULL) {
        while ((file = readdir(dir)) != NULL) {
            if (file->d_type == DT_REG){ 
                
                char ** splitted = splitFilename(file->d_name);
                int strokes = atoi(splitted[1]);
                
                free(splitted[0]);
                free(splitted[1]);
                free(splitted);

                if (strokes > MAX_STROKES){
                    continue;
                }

                arr[strokes-1]++;

                numFiles++;

            }
        }
        closedir (dir);
    } 
    else {
        perror("[*] Directory cannot be opened or doesn't exist");
        exit(-1);
    }

    array->length = numFiles;


    // allocate memory for each array and each string on it
    for (int i = 0; i < MAX_STROKES; i++){

        strokesGroup * group = &array->groups[i];

        group->names = malloc(sizeof(char *) * arr[i]);
        group->strokes = i+1;
        group->count = 0;
        for (int x = 0; x < arr[i]; x++){
            group->names[x] = malloc(sizeof(char) * 15);
            strcpy(group->names[x], "");
        }
    }
    
    // fill the structure with all the data
    dir = opendir(directory);
    while ((file = readdir(dir)) != NULL) {
        if (file->d_type == DT_REG){ 

            char wholeName[20];
            strcpy(wholeName, file->d_name);

            char ** splitted = splitFilename(file->d_name);
            int strokes = atoi(splitted[1]);
            free(splitted[0]);
            free(splitted[1]);
            free(splitted);

            if (strokes > MAX_STROKES){
                continue;
            }

            strokesGroup * head = &array->groups[strokes-1];
            int length = arr[strokes-1];

            addValue(wholeName, head->names, length);
            head->count++; 
        }
    }
    closedir(dir);

    return array;
}

void closeDB(Database * files){

    for (int i = 0; i < MAX_STROKES; i++){
        
        strokesGroup * group = &files->groups[i];
        
        for (int x = 0; x < group->count; x++){
            free(group->names[x]);
        }
        
        free(group->names);
    }
    
    free(files);
}