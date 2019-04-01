#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "database.h"
#include "parser.h"
#include "UI.h"


SDL_Rect * createPane(SDL_Renderer * renderer, int x, int y, int w, int h){

    SDL_Rect * pane = malloc(sizeof(SDL_Rect));
    pane->x = x;
    pane->y = y;
    pane->w = w;
    pane->h = h;

    SDL_RenderFillRect(renderer, pane);

    return pane;
}

_Bool onSecondPane(SDL_Event event){
    return event.motion.x > 540 && event.motion.x < 1040 && event.motion.y > 20 && event.motion.y < 520;
}

void createDrawingPane(SDL_Renderer * renderer, SDL_Texture ** images, int length){
    _Bool leftMouseButtonDown = 0;
    _Bool quit = 0;
    SDL_Event event;

    SDL_Texture * texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 500, 500);
    int pixels[500][500];
    memset(pixels, 255, 500 * 500 * sizeof(int));

    while (!quit){

        SDL_SetRenderDrawColor(renderer, 51, 102, 153, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 102, 100, 255);
        SDL_Rect * pane1 = createPane(renderer, 20, 20, 500, 500);

        SDL_SetRenderDrawColor(renderer, 100, 102, 200, 255);
        SDL_Rect * pane2 = createPane(renderer, 540, 20, 500, 500);

        gridAdd(renderer, images, length);

        SDL_UpdateTexture(texture, NULL, pixels, 500 * sizeof(int));

        SDL_WaitEvent(&event);

        switch (event.type){

            case SDL_QUIT:
                quit = 1;
                break;
            
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT)
                    leftMouseButtonDown = 0;
                    break;
            
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                    leftMouseButtonDown = 1;
                    if (onSecondPane(event)){
                        double x = (event.motion.x - 547)/70;
                        double y = (event.motion.y - 27)/70;
                        
                        char *message;
                        asprintf(&message, "Clicked on image at (%f, %f)\n", round(x), round(y));
                        
                        printf("%s", message);
                        SDL_SetClipboardText(message);
                    }
            
            case SDL_MOUSEMOTION:
                if (leftMouseButtonDown && event.motion.x - 20 < 500 && event.motion.y - 20 < 500){

                    int mouseX = event.motion.x - 20;
                    int mouseY = event.motion.y - 20;
                    
                    // check segfaults when approach border quickly
                    // free memory
                    // it stops painting when top left

                    pixels[mouseY][mouseX] = 0;

                    int size = 20;

                    for (int i = -size/2; i<=size/2; i++){ // come up with algo to draw circle
                        for (int j = -size/2; j<=size/2; j++){
                            pixels[mouseY+i][mouseX+j] = 0;
                        }
                    }
                
                }
                else if (onSecondPane(event)){

                    double x = (event.motion.x - 547)/70;
                    double y = (event.motion.y - 27)/70;

                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
                    SDL_Rect rectangular;
                    rectangular.x = 540 + 7 + round(x)*70;
                    rectangular.y = 27 + round(y)*70;
                    rectangular.w = 65;
                    rectangular.h = 65;
                    SDL_RenderFillRect(renderer, &rectangular);
                }
                break;
        }

        SDL_RenderCopy(renderer, texture, NULL, pane1);
        SDL_RenderPresent(renderer);

        free(pane1);
        free(pane2);
    }
    SDL_DestroyTexture(texture);
}

void gridAdd(SDL_Renderer * renderer, SDL_Texture ** images, int length){
    
    if (length > 49){
        length = 49;
    }

    int x = length / 7;
    int y = length % 7;

    int count = 0;
    int i;

    for (i = 0; i < x; i++){
        for (int j = 0; j < 7; j++){
            SDL_Rect rectangular;
            rectangular.x = 540 + 7 + j*70;
            rectangular.y = 27 + i*70;
            rectangular.w = 65;
            rectangular.h = 65;
            SDL_RenderCopy(renderer, images[count], NULL, &rectangular);
            count++;
        }
    }

    if (y != 0){
        for (int j = 0; j < y; j++){
            SDL_Rect rectangular;
            rectangular.x = 540 + 7 + j*70;
            rectangular.y = 27 + i*70;
            rectangular.w = 65;
            rectangular.h = 65;
            SDL_RenderCopy(renderer, images[count], NULL, &rectangular);
            count++;
        }
    }
}

SDL_Texture * createImage(SDL_Renderer * renderer, char * source, int * width, int * height){

    char sourcePath[30] = "../chars/";
    strcat(sourcePath, source);

    SDL_Texture * img = IMG_LoadTexture(renderer, sourcePath);
    SDL_QueryTexture(img, NULL, NULL, width, height);
    return img;
}

void initWindow(SDL_Window ** window, int width, int height){
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0){

        printf("SDL_Error: %s\n", SDL_GetError());

    }

    *window = SDL_CreateWindow("Chinese To Letters", SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    
    //SDL_SetWindowResizable(window, SDL_TRUE);

    if (window == NULL){

        printf("SDL_Error: %s\n", SDL_GetError());
    }

}

void closeWindow(SDL_Window * window){
    SDL_DestroyWindow(window);
    SDL_Quit();
}

/*

From a sorted array of images and scores (charScore), return ordered array of SDL_textures

*/

SDL_Texture ** charScore2texture(SDL_Renderer * renderer, charScore * charList, int count){
    SDL_Texture ** textureList = malloc(sizeof(SDL_Texture *) * count);
    int w, h;
    for (int i = 0; i < count; i++){
        textureList[i] = malloc(sizeof(textureList[0])); // SDL_Texture is opaque so bypass with pointer
        textureList[i] = createImage(renderer, charList[i].name, &w, &h);
    }
    return textureList;
}


int main(int argc, char* args[]){


    Database * files = openDB("../chars/");
    char filename[] = "../chars/5c55_10.png";

    int stroke = 6;

    char ** strokeFiles = getStrokeFiles(stroke, files);
    int count = getNumberByStroke(stroke, files);
    
    charScore * valueChars = orderCompare(strokeFiles, filename, count);

    SDL_Window * window = NULL;
    SDL_Surface * surface = NULL;
    SDL_Rect rects[14][12];
    int width = 1060;
    int height = 540;

    initWindow(&window, width, height);

    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //renderer used to color rects
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            
    SDL_Texture ** images = charScore2texture(renderer, valueChars, count);

    createDrawingPane(renderer, images, count);

    SDL_FreeSurface(surface);
    
    closeWindow(window);

    closeDB(files);

    return 0;
}
