#define COLS 500
#define ROWS 500

double compareAlgorithm(int compareTo[500][500], int matrix[500][500], int initFlag, int mode);
void setCompareTo(int compareTo[500][500], int mode);

int canEnterCell(int matrix[ROWS][COLS], int isVisited[ROWS][COLS], int currentRow, int currentCol, int isWhite);
void expandSearch(int matrix[ROWS][COLS], int isVisited[ROWS][COLS], int currentRow, int currentCol, int isWhite);
int findIslands(int matrix[ROWS][COLS], int isWhite);

void countColsRows(int main[500][500], int rows[500], int cols[500]);
void countStartDirections(int main[500][500], int top[500], int right[500], int bottom[500], int left[500]);

double correlationCoefficient(int X[500], int Y[500], int n);
