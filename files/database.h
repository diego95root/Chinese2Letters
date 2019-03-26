#define MAX_STROKES 16 // remove from here
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

struct array_len {
    struct strokes_group groups[MAX_STROKES];
    int length;
};

char ** split(char * name);
struct array_len * getFiles(char * directory); // change to return array of strings
void add(char * value, node_t * head);
char ** getStrokeFiles(int stroke, struct array_len * files);
void printArray(char ** array);