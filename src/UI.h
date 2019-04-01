
_Bool onSecondPane(SDL_Event event);

void initWindow(SDL_Window ** window, int width, int height);
void closeWindow(SDL_Window * window);
void createDrawingPane(SDL_Renderer * renderer, SDL_Texture ** images, int length);
void gridAdd(SDL_Renderer * renderer, SDL_Texture ** images, int length);


SDL_Rect * createPane(SDL_Renderer * renderer, int x, int y, int w, int h);
SDL_Texture * createImage(SDL_Renderer * renderer, char * source, int * width, int * height);
SDL_Texture ** charScore2texture(SDL_Renderer * renderer, charScore * charList, int count);
