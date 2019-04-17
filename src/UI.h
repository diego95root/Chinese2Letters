void startApp(char sourcePath[]);

void initWindow(SDL_Window * window, SDL_Renderer ** renderer, int width, int height);
void closeWindow(SDL_Window * window);

_Bool onFirstPane(SDL_Event event, int startX, int startY);
_Bool onSecondPane(SDL_Event event, int startX, int startY);
_Bool onButtonsPane(SDL_Event event);

void mainLoopWindow(Database * files, SDL_Renderer * renderer, int startX, int startY);

void drawCircle(int pixels[500][500], int x, int y, int radius);
void freeIterationData(charScoreList * chars, SDL_Texture ** images);
void clearGrid(int matrix[500][500]);

void gridAdd(SDL_Renderer * renderer, SDL_Texture ** images, int length, int startX, int startY);
SDL_Rect * createPane(SDL_Renderer * renderer, int x, int y, int w, int h);
SDL_Texture * createImage(SDL_Renderer * renderer, char * source, char sourcePath[], int * width, int * height);
SDL_Texture * loadImage(SDL_Renderer * renderer, char * source);
SDL_Texture ** charScore2texture(SDL_Renderer * renderer, charScore ** charList, char sourcePath[], int count);

uint8_t * hex2byteArray(char* string);
