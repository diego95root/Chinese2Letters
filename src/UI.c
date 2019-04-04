#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "database.h"
#include "parser.h"
#include "UI.h"

int strokes = 0;

uint8_t * datahex(char* string) {

    if(string == NULL) 
       return NULL;

    size_t slength = strlen(string);
    if((slength % 2) != 0) // must be even
       return NULL;

    size_t dlength = slength / 2;

    uint8_t* data = malloc(dlength);
    memset(data, 0, dlength);

    size_t index = 0;
    while (index < slength) {
        char c = string[index];
        int value = 0;
        if(c >= '0' && c <= '9')
          value = (c - '0');
        else if (c >= 'A' && c <= 'F') 
          value = (10 + (c - 'A'));
        else if (c >= 'a' && c <= 'f')
          value = (10 + (c - 'a'));
        else {
          free(data);
          return NULL;
        }

        data[(index/2)] += value << (((index + 1) % 2) * 4);

        index++;
    }

    return data;
}

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

_Bool onFirstPane(SDL_Event event){
    return event.motion.x < 520 && event.motion.x > 20 && event.motion.y < 520 && event.motion.y > 20;
}

void createDrawingPane(SDL_Renderer * renderer){
    _Bool leftMouseButtonDown = 0;
    _Bool quit = 0;
    SDL_Event event;

    charScoreList * valueChars = parserInit(strokes);
    SDL_Texture ** images = charScore2texture(renderer, valueChars->elements, valueChars->count);

    int changedStrokes = 1;

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

        if (changedStrokes){ // Update in case of new stroke
        
            if (valueChars->count != 0){ // free if there were any elements
                freeCharScoreList(valueChars);
                for (int i = 0; i < valueChars->count; i++){
                    free(images[i]);
                }
                free(images);
            }

            valueChars = parserInit(strokes);
            images = charScore2texture(renderer, valueChars->elements, valueChars->count);
            changedStrokes = 0;
        }

        gridAdd(renderer, images, valueChars->count);

        SDL_UpdateTexture(texture, NULL, pixels, 500 * sizeof(int));

        SDL_WaitEvent(&event);

        switch (event.type){

            case SDL_QUIT:
                quit = 1;
                break;
            
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT && onFirstPane(event)){
                    leftMouseButtonDown = 0;
                    strokes++;
                    changedStrokes = 1;
                    //printf("%d\n", strokes);
                    break;
                }
            
            case SDL_MOUSEBUTTONDOWN:
                
                if (event.button.button == SDL_BUTTON_LEFT){
                    
                    if (onSecondPane(event)){
                        
                        int x = round((event.motion.x - 547)/70);
                        int y = round((event.motion.y - 27)/70);
                        
                        if ( y * 7 + x < valueChars->count){ // only copy if over image

                            char message[7];
                            strncpy(message, valueChars->elements[y*7+x].name, 6);

                            uint8_t * data = datahex(message);
                            char final[4];
                            strncpy(final, data, 3);

                            //printf("%s\n", final);
                            SDL_SetClipboardText(final);
                        }
                    }
                    else if (onFirstPane(event)){
                        leftMouseButtonDown = 1;
                    }
                }
            
            case SDL_MOUSEMOTION:
                if (onFirstPane(event) && leftMouseButtonDown){

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

                    int x = round((event.motion.x - 547)/70);
                    int y = round((event.motion.y - 27)/70);

                    if ( y * 7 + x < valueChars->count){ // only color if over image

                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
                        SDL_Rect rectangular;
                        rectangular.x = 540 + 7 + x*70;
                        rectangular.y = 27 + y*70;
                        rectangular.w = 65;
                        rectangular.h = 65;
                        SDL_RenderFillRect(renderer, &rectangular);
                    
                    }
                
                }
                break;
        }

        SDL_RenderCopy(renderer, texture, NULL, pane1);
        SDL_RenderPresent(renderer);

        free(pane1);
        free(pane2);
    }
    freeCharScoreList(valueChars);
    for (int i = 0; i < valueChars->count; i++){
        free(images[i]);
    }
    free(images);
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

    char sourcePath[30] = "../chars2/";
    strcat(sourcePath, source);

    SDL_Texture * img = IMG_LoadTexture(renderer, sourcePath);
    SDL_QueryTexture(img, NULL, NULL, width, height);
    return img;
}

void initWindow(SDL_Window ** window, SDL_Renderer ** renderer, int width, int height){
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0){

        printf("SDL_Error: %s\n", SDL_GetError());

    }

    *window = SDL_CreateWindow("Chinese To Letters", SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    
    //SDL_SetWindowResizable(window, SDL_TRUE);

    if (window == NULL){

        printf("SDL_Error: %s\n", SDL_GetError());
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED); //renderer used to color rects
    SDL_SetRenderDrawBlendMode(*renderer, SDL_BLENDMODE_BLEND);

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

    SDL_Window   * window   = NULL;
    SDL_Renderer * renderer = NULL;
    
    int width = 1060;
    int height = 540;
    
    initWindow(&window, &renderer, width, height);

    createDrawingPane(renderer);
    
    closeWindow(window);

    parserEnd();

    return 0;
}
