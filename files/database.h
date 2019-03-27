#define MAX_STROKES 15 // remove from here
#define DEBUG 0

typedef struct node {
    char * val;
    struct node * next;
} node_t;

struct strokes_group {
    int strokes;
    int count;
    node_t * names;
};

typedef struct database {
    struct strokes_group groups[MAX_STROKES];
    int length;
} Database;

char ** splitFilename(char * name);
Database * getFiles(char * directory);
void add(char * value, node_t * head);
char ** getStrokeFiles(int stroke, Database * files);
void printArray(char ** array);