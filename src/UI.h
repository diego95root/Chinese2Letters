uint8_t * hex2byteArray(char* string);

_Bool onFirstPane(SDL_Event event, int startX, int startY);
_Bool onSecondPane(SDL_Event event, int startX, int startY);

void initWindow(SDL_Window ** window, SDL_Renderer ** renderer, int width, int height);
void closeWindow(SDL_Window * window);
void createDrawingPane(Database * files, SDL_Renderer * renderer, int startX, int startY);
void gridAdd(SDL_Renderer * renderer, SDL_Texture ** images, int length, int startX, int startY);

void drawCircle(int pixels[500][500], int x, int y, int radius);


SDL_Rect * createPane(SDL_Renderer * renderer, int x, int y, int w, int h);
SDL_Texture * createImage(SDL_Renderer * renderer, char * source, int * width, int * height);
SDL_Texture ** charScore2texture(SDL_Renderer * renderer, charScore ** charList, int count);
