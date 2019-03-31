
typedef struct charScore {
    double score;
    char * name;
} charScore;

int ** image2matrix(char * name, int width, int height);
void writeMatrix(int ** matrix, int width, int height);
charScore * orderCompare(char ** chars, char * compareTo, int count);
void sortList(charScore * list, int count);
void sortListTest(double * list, int count);