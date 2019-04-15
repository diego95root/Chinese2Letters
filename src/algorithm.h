#define COLS 500
#define ROWS 500

double compareAlgorithm(int compareTo[500][500], int matrix[500][500], int initFlag, int mode);
void setCompareTo(int compareTo[500][500], int mode);

int can_enter_cell(int matrix[ROWS][COLS], int is_visited[ROWS][COLS], int cur_row, int cur_col);
void expand_search(int matrix[ROWS][COLS], int is_visited[ROWS][COLS], int cur_row, int cur_col);
int find_islands(int matrix[ROWS][COLS]);

double correlationCoefficient(int X[500], int Y[500], int n);
