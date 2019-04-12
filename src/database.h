#define MAX_STROKES 15 // remove from here

typedef struct strokesGroup {
    int strokes;
    int count;
    char ** names;
} strokesGroup;

typedef struct database {
    strokesGroup groups[MAX_STROKES];
    int length;
} Database;

char ** splitFilename(char * name);
char ** getStrokeFiles(int stroke, Database * files);

Database * openDB(char * directory);

void addValue(char * value, char ** head, int len);
void printArray(char ** array);
void closeDB(Database * files);

int getNumberByStroke(int stroke, Database * files);