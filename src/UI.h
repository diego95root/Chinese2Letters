uint8_t * hex2byteArray(char* string);

_Bool onFirstPane(SDL_Event event);
_Bool onSecondPane(SDL_Event event);

void initWindow(SDL_Window ** window, SDL_Renderer ** renderer, int width, int height);
void closeWindow(SDL_Window * window);
void createDrawingPane(Database * files, SDL_Renderer * renderer);
void gridAdd(SDL_Renderer * renderer, SDL_Texture ** images, int length);

SDL_Rect * createPane(SDL_Renderer * renderer, int x, int y, int w, int h);
SDL_Texture * createImage(SDL_Renderer * renderer, char * source, int * width, int * height);
SDL_Texture ** charScore2texture(SDL_Renderer * renderer, charScore ** charList, int count);
