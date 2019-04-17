#define ROWS 500
#define COLS 500

typedef struct charScore {
    double score;
    char * name;
} charScore;

typedef struct charScoreList {
    charScore ** elements;
    int count;
} charScoreList;

void image2matrix(int matrix[ROWS][COLS], char * name);
void writeMatrix(int matrix[ROWS][COLS], char * outName);
void readMatrix(int matrix[ROWS][COLS], char *filename);

void sortList(charScore ** list, int count);
void sortListTest(double * list, int count);

charScoreList * orderCompare(char ** chars, char * directory, int matrix[ROWS][COLS], int count, int mode);
charScoreList * parserInit(Database * files, int stroke, int matrix[ROWS][COLS], int mode);

Database * parserGetDB(char * path);

void freeCharScoreList(charScoreList * list);
void parserEnd(Database * files);