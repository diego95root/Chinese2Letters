#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "database.h"
#include "parser.h"
#include "UI.h"

int main(int argc, char* args[]){

    char sourcePath[] = "../chars3/";

    startApp(sourcePath);

    return 0;
}