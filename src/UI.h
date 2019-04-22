
typedef struct cursorData {
    SDL_Cursor * normal;
    SDL_Cursor * hand;
} cursorData;

typedef struct appData {
    int drawingGrid[500][500];
    SDL_Rect * pane1; // main left
    SDL_Rect * pane2; // main right
    SDL_Rect * pane3; // 3-5 are for top left buttons
    SDL_Rect * pane4;
    SDL_Rect * pane5;
    SDL_Rect * pane6; // top right clear button
    SDL_Texture * buttonsTex[6]; // 
    cursorData cursors;
} appData;

void initWindow(SDL_Window * window, SDL_Renderer ** renderer, int width, int height);
TTF_Font * initFont(char * font, int size);
void closeWindow(SDL_Window * window);

_Bool onFirstPane(SDL_Event event, int startX, int startY);
_Bool onSecondPane(SDL_Event event, int startX, int startY);
_Bool onButtonsPane(SDL_Event event);

appData initScene(SDL_Renderer * renderer, int startX, int startY);
void mainLoopWindow(Database * files, SDL_Renderer * renderer, TTF_Font * font, appData data, int startX, int startY);

void drawCircle(int pixels[500][500], int x, int y, int radius);
void freeAppData(appData data);
void freeIterationData(charScoreList * chars, SDL_Texture ** images);
void clearGrid(int matrix[500][500]);

void gridAdd(SDL_Renderer * renderer, SDL_Texture ** images, int length, int startX, int startY);
SDL_Rect * createPane(SDL_Renderer * renderer, int x, int y, int w, int h);
SDL_Texture * createImage(SDL_Renderer * renderer, char * source, char sourcePath[], int * width, int * height);
SDL_Texture * loadImage(SDL_Renderer * renderer, char * source);
SDL_Texture ** charScore2texture(SDL_Renderer * renderer, charScore ** charList, char sourcePath[], int count);

void loadMessage(SDL_Renderer * renderer, char * text, TTF_Font * font);

uint8_t * hex2byteArray(char* string);
