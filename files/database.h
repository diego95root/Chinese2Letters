#define MAX_STROKES 15 // remove from here
#define DEBUG 0

typedef struct strokesGroup {
    int strokes;
    int count;
    char ** names;
} strokesGroup;

typedef struct database {
    struct strokesGroup groups[MAX_STROKES];
    int length;
} Database;

char ** splitFilename(char * name);
char ** getStrokeFiles(int stroke, Database * files);

Database * getFiles(char * directory);

void addValue(char * value, char ** head, int len);
void printArray(char ** array);
