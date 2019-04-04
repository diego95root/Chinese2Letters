
typedef struct charScore {
    double score;
    char * name;
} charScore;

typedef struct charScoreList {
    charScore * elements;
    int count;
} charScoreList;

int ** image2matrix(char * name, int width, int height);
void writeMatrix(int ** matrix, int width, int height);
charScoreList * orderCompare(char ** chars, char * compareTo, int count);
void sortList(charScore * list, int count);
void sortListTest(double * list, int count);

charScoreList * parserInit(int stroke);

void freeCharScoreList(charScoreList * list);
void parserEnd();