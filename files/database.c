
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


char ** split(char * name){

    char ** splitted = malloc(sizeof(char *) * 2);
    
    char * delimiter  = ".";
    char * delimiter2 = "_";

    char * ptr = strtok(name, delimiter);
    ptr = strtok(name, delimiter2);

    for (int i = 0; i < 2; i++){
                    
        splitted[i] = malloc(sizeof(char) * strlen(ptr));

        char zero = ptr[0];
        if (i == 1 && atoi(&zero) == 0){
            strcpy(splitted[i], &ptr[1]);
            //printf("Conents of split[i]: %d\n", atoi(splitted[i]));
        }
        else {
            strcpy(splitted[i], ptr);
        }

        ptr = strtok(NULL, delimiter2);
    }

    return splitted;
}

void add(char * value, node_t * head){
    if (head->next == NULL){

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

char **  getStrokeFiles(int stroke, struct array_len * files){
    
    struct strokes_group * group = &(files->groups[stroke]);
    char ** strokeFiles;
    int count = 2;

    if (DEBUG){
        printf("There are %d characters with %d strokes:\n", group->count, group->strokes);
    }

    node_t * initial = group->names;
    while (1){
        if (initial->next == NULL){
            break;
        }
        initial = initial->next;
        count++;
    };

    strokeFiles = malloc(sizeof(char *) * count);

    initial = group->names;

    strokeFiles[count-1] = malloc(sizeof(char));
    strcpy(strokeFiles[count-1], "");
    --count;
    
    while (1){
        if (DEBUG){
            printf("-> %s\n", initial->val);
        }

        strokeFiles[count-1] = malloc(sizeof(char) * strlen(initial->val));
        strcpy(strokeFiles[count-1], initial->val);
        count--;

        if (initial->next == NULL){
            break;
        }
        initial = initial->next;
    };
    
    return strokeFiles;
}

void printArray(char ** array){
    int i = 0;

    printf("[");
    while (1){
        if (strcmp(array[i], "") == 0){
            break;
        }
        printf("%s, ", array[i]);
        i++;
    }
    printf("\b\b]\n");
}

/*
typedef struct node {
    char * val;
    struct node * next;
} node_t;

struct strokes_group {
    int strokes;
    int count;
    node_t * names;
};

struct array_len {
    struct strokes_group groups[MAX_STROKES];
    int length;
};

*/

struct array_len * getFiles(char * directory){

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

    struct array_len * array = malloc(sizeof(struct array_len));
    array->length = num_files;

    for (int i = 1; i < MAX_STROKES; i++){
        array->groups[i].strokes = i;

        node_t * head = NULL;
        head = malloc(sizeof(node_t));
        head->val = "XXX";
        head->next = NULL;
        
        array->groups[i].count = 0;
        array->groups[i].names = head;

    }

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

            char ** splitted = split(file->d_name);

            struct strokes_group * head = &array->groups[atoi(splitted[1])];

            if (strcmp(head->names->val, "XXX") == 0){
                head->names->val = splitted[0];
                head->names->next = NULL;
                head->count += 1;
            }
            else {
                add(splitted[0], head->names);
                head->count += 1;
            }


            iterator++;
        }
    }
    closedir(dir);

    return array;
}

int main(){

    struct array_len * files = getFiles("../chars/");

    printf("Total strokes: %d\n", files->length);
    for (int i = 1; i<MAX_STROKES; i++){
        printf("%d stroke(s): %d characters\n", files->groups[i].strokes, files->groups[i].count);
    }

    for (int strokes = 1; strokes < 16; strokes++){
    //int strokes = 15;

    char ** strokeFiles = getStrokeFiles(strokes, files);
    
    printArray(strokeFiles);
    }

    return 1;
}