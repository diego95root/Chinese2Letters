#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "database.h"
#include "parser.h"
#include "UI.h"

void startApp(char sourcePath[]){

    SDL_Window   * window   = NULL;
    SDL_Renderer * renderer = NULL;
    
    int width = 1060;
    int height = 600; // 540 + 60 for above bar

    Database * db = parserGetDB(sourcePath);

    initWindow(window, &renderer, width, height);

    TTF_Font * font = initFont("../chineseBold.ttf", 20);

    mainLoopWindow(db, renderer, font, 0, 60);

    closeWindow(window);

    parserEnd(db);
}

int main(int argc, char* args[]){

    char sourcePath[] = "../chars3/";

    startApp(sourcePath);

    return 0;
}