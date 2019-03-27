
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

int x = 0;
/*

Takes a filename of the format XXXX_XX.png where the first X's are
hex chars and the second two X's are the number of strokes. Returns
an array of the two strings: the hex representation and the strokes.

*/

char ** splitFilename(char * name){

    char ** splitted = malloc(sizeof(char *) * 2);
    
    char * delimiter  = ".";
    char * delimiter2 = "_";

    char * ptr = strtok(name, delimiter); // don't take extension
    ptr = strtok(name, delimiter2);

    for (int i = 0; i < 2; i++){
                    
        splitted[i] = malloc(sizeof(char) * strlen(ptr));

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

/*

Adds a value to a linked list

*/

void add(char * value, node_t * head){

    printf("Adding: %s\n", head->val);
    x++;
    if (strcmp(head->val, "") == 0){
        head->val = value;
        head->next = NULL;
    }

    else if (head->next == NULL){
        node_t * element;
        element = malloc(sizeof(node_t));
        element->val = value;
        head->next = NULL;

        head->next = element;
        return;
    }

    else {
        add(value, head->next);
    }
}

/*

Taking the number of strokes and the database structure, it
returns an array of all the filenames that contain characters with
that number of strokes.

*/

char **  getStrokeFiles(int stroke, Database * files){

    if (stroke > MAX_STROKES || stroke == 0){ // empty array if stroke not valid
        char ** strokeFiles = malloc(sizeof(char *));
        strcpy(strokeFiles[0], "");
        return strokeFiles;
    }

    struct strokes_group * group = &(files->groups[stroke]);
    int count = group->count + 1; // one more because start at count - 1 and "" at the end 
    
    char ** strokeFiles;
    strokeFiles = malloc(sizeof(char *) * count);
    
    if (DEBUG){
        printf("[*] There are %d characters with %d strokes:\n", group->count, group->strokes);
    }

    node_t * initial = group->names;

    for (int i = 0; i<count-1; i++){
        
        if (DEBUG){
            printf("[*] -> %s\n", initial->val);
        }
        // allocate and copy each element
        strokeFiles[i] = malloc(sizeof(char) * strlen(initial->val));
        strcpy(strokeFiles[i], initial->val);
        initial = initial->next;
    };

    // terminate with null string
    strokeFiles[count-1] = malloc(sizeof(char));
    strcpy(strokeFiles[count-1], "");
    
    return strokeFiles;
}

/*

Prints an array of strings terminated with an empty string

*/

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


/*

getFiles gets all filenames from a directory and based on the stroke
number of the character stores them in a different linked list. Sort 
of a python dictionary. It returns that structure.

*/

Database * getFiles(char * directory){

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
        perror("[*] Directory cannot be opened or doesn't exist");
        exit(-1);
    }

    if (DEBUG){
        printf("[*] Number of files: %d\n", num_files);
    }

    Database * array = malloc(sizeof(Database));
    array->length = num_files;

    for (int i = 1; i <= MAX_STROKES; i++){
        array->groups[i].strokes = i;

        node_t * head = NULL;
        head = malloc(sizeof(node_t));
        head->val = "";
        head->next = NULL;
        
        array->groups[i].count = 0;
        array->groups[i].names = head;

    }

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

            char ** splitted = splitFilename(file->d_name);
            int strokes = atoi(splitted[1]);
            char * hex = splitted[0];

            if (strokes > MAX_STROKES){
                continue;
            }

            struct strokes_group * head = &array->groups[strokes];

            add(hex, head->names);
            head->count += 1;

        }
    }
    closedir(dir);

    printf("Number of iterations: %d\n", x);

    return array;
}

int main(){

    Database * files = getFiles("../chars/");

    printf("[*] Total strokes: %d\n", files->length);
    for (int i = 1; i <= MAX_STROKES; i++){
        printf("[*] %d stroke(s): %d characters\n", files->groups[i].strokes, files->groups[i].count);
    }

    int strokes = 15;

    char ** strokeFiles = getStrokeFiles(strokes, files);

    printArray(strokeFiles);

    return 1;
}