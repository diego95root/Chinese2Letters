#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "database.h"
#include "parser.h"
#include "UI.h"

int strokes = 0;

// Initialise all necessary things for the main window, including its size

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

    int flags = IMG_INIT_PNG;
    int init = IMG_Init(flags);
    
    if(!(init & flags)) {
        printf("Images couldn't be loaded, %s!\n", IMG_GetError()); 
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED); //renderer used to color rects
    SDL_SetRenderDrawBlendMode(*renderer, SDL_BLENDMODE_BLEND);

}

// Free all elements created by the SDL library and quit the program

void closeWindow(SDL_Window * window){
    SDL_DestroyWindow(window);
    SDL_Quit();
}


// function that converts a hex string into a byte array
// source: https://stackoverflow.com/questions/3408706/hexadecimal-string-to-byte-array-in-c

uint8_t * hex2byteArray(char* string){

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

// Creates and returns a rectangle based on the coordinates and size provided

SDL_Rect * createPane(SDL_Renderer * renderer, int x, int y, int w, int h){

    SDL_Rect * pane = malloc(sizeof(SDL_Rect));
    pane->x = x;
    pane->y = y;
    pane->w = w;
    pane->h = h;

    SDL_RenderFillRect(renderer, pane);

    return pane;
}

// Given an SDL_Event, return true if the mouse is within some coordinates (second pane)

_Bool onSecondPane(SDL_Event event, int startX, int startY){
    return event.motion.x > startX + 540 && event.motion.x < startX + 1040 
            && event.motion.y > startY + 20 && event.motion.y < startY + 520;
}

// Same as the function above, but this one checks if in the first pane

_Bool onFirstPane(SDL_Event event, int startX, int startY){
    return event.motion.x < startX + 520 && event.motion.x > startX + 20 
            && event.motion.y < startY + 520 && event.motion.y > startY + 20;
}

// return true if mouse is on a button from the top bar

_Bool onButtonsPane(SDL_Event event){
    _Bool goodY = event.motion.y > 20 && event.motion.y < 60;
    _Bool goodX = event.motion.x > 20 && event.motion.x < 300;
    _Bool notSpaceX = event.motion.x % 100 > 20;
    return goodX && goodY && notSpaceX;
}

// draw a circle based on the circle's formula: (x - a)**2 + (y - b)**2 = r**2

void drawCircle(int pixels[500][500], int x, int y, int radius){

    for (int i = x - radius; i <= x + radius; i++){
        for (int j = y - radius; j <= y + radius; j++){
            if (pow(x-i, 2) + pow(y-j, 2) <= pow(radius, 2)){
                if (j >= 0 && j < 500 && i >= 0 && j < 500){ // checks to prevent segfaults when drawing outside
                    pixels[j][i] = 0;
                }
            }
        }    
    }
}

void createDrawingPane(Database * db, SDL_Renderer * renderer, int startX, int startY){
    _Bool leftMouseButtonDown = 0;
    _Bool quit = 0;
    _Bool notPressed = 1;
    SDL_Event event;

    int pixels[500][500];
    
    for (int i = 0; i < 500; i++){
        for (int j = 0; j < 500; j++){
            pixels[i][j] = -257;
        }
    }

    charScoreList * valueChars = parserInit(db, strokes, pixels);
    SDL_Texture ** images = charScore2texture(renderer, valueChars->elements, valueChars->count);
    SDL_Texture * texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 500, 500);

    SDL_Surface* loadedSurface = IMG_Load("../button.png");
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);

    while (!quit){

        SDL_SetRenderDrawColor(renderer, 51, 102, 153, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 102, 100, 255);
        SDL_Rect * pane1 = createPane(renderer, startX + 20, startY + 20, 500, 500);

        SDL_SetRenderDrawColor(renderer, 100, 102, 200, 255);
        SDL_Rect * pane2 = createPane(renderer, startX + 40 + 500, startY + 20, 500, 500);

        gridAdd(renderer, images, valueChars->count, startX, startY);

        SDL_Rect * pane3 = createPane(renderer, 20, 20, 80, 40);
        SDL_Rect * pane4 = createPane(renderer, 120, 20, 80, 40);
        SDL_Rect * pane5 = createPane(renderer, 220, 20, 80, 40);

        SDL_RenderCopy(renderer, tex, NULL, pane3);
        SDL_RenderCopy(renderer, tex, NULL, pane4);
        SDL_RenderCopy(renderer, tex, NULL, pane5); 

        SDL_UpdateTexture(texture, NULL, pixels, 500 * sizeof(int));

        SDL_WaitEvent(&event);

        switch (event.type){

            case SDL_QUIT:
                quit = 1;
                break;
            
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT && onFirstPane(event, startX, startY)){
                    leftMouseButtonDown = 0;
                    strokes++;
                    //printf("%d\n", strokes);

                    // Update in case of new stroke
        
                    if (valueChars->count != 0){ // free if there were any elements
                        freeCharScoreList(valueChars);
                        for (int i = 0; i < valueChars->count; i++){
                            free(images[i]);
                        }
                        free(images);
                    }
                    valueChars = parserInit(db, strokes, pixels);
                    images = charScore2texture(renderer, valueChars->elements, valueChars->count);
                    gridAdd(renderer, images, valueChars->count, startX, startY);

                    break;
                }
            
            case SDL_MOUSEBUTTONDOWN:
                
                if (event.button.button == SDL_BUTTON_LEFT){
                    
                    if (onSecondPane(event, startX, startY)){
                        
                        int x = round((event.motion.x - 547)/70);
                        int y = round((event.motion.y - 27)/70);
                        
                        if ( y * 7 + x < valueChars->count){ // only copy if over image

                            char message[7];
                            strncpy(message, valueChars->elements[y*7+x]->name, 6);

                            uint8_t * data = hex2byteArray(message);
                            char final[4];
                            strncpy(final, data, 3);

                            //printf("%s\n", final);
                            SDL_SetClipboardText(final);
                        }
                    }
                    else if (onFirstPane(event, startX, startY)){
                        leftMouseButtonDown = 1;
                    }

                    else if (onButtonsPane(event) && notPressed){

                        int x = event.motion.x / 100;

                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 140);
                        SDL_Rect rectangular;
                        rectangular.x = 20 + x*100;
                        rectangular.y = 20;
                        rectangular.w = 80;
                        rectangular.h = 40;
                        SDL_RenderFillRect(renderer, &rectangular);

                        notPressed = 0;
                    }

                    else {
                        notPressed = 1;
                    }
                }
            
            case SDL_MOUSEMOTION:
                if (onFirstPane(event, startX, startY) && leftMouseButtonDown){

                    int mouseX = event.motion.x - startX - 20;
                    int mouseY = event.motion.y - startY - 20;
                    
                    // free memory
                    // it stops painting when top left

                    int radius = 14;

                    drawCircle(pixels, mouseX, mouseY, radius);
                
                }
                else if (onSecondPane(event, startX, startY)){

                    int x = round((event.motion.x - startX - 547)/70);
                    int y = round((event.motion.y - startY - 27)/70);

                    if ( y * 7 + x < valueChars->count){ // only color if over image

                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
                        SDL_Rect rectangular;
                        rectangular.x = startX + 540 + 7 + x*70;
                        rectangular.y = startY + 27 + y*70;
                        rectangular.w = 65;
                        rectangular.h = 65;
                        SDL_RenderFillRect(renderer, &rectangular);
                    
                    }
                
                }
                else if (onButtonsPane(event)){

                    int x = event.motion.x / 100;

                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
                    SDL_Rect rectangular;
                    rectangular.x = 20 + x*100;
                    rectangular.y = 20;
                    rectangular.w = 80;
                    rectangular.h = 40;
                    SDL_RenderFillRect(renderer, &rectangular);
                }
                break;
        }

        SDL_RenderCopy(renderer, texture, NULL, pane1);
        SDL_RenderPresent(renderer);

        free(pane1);
        free(pane2);
        free(pane3);
        free(pane4);
        free(pane5);
    }

    writeMatrix(pixels, "data");

    freeCharScoreList(valueChars);
    for (int i = 0; i < valueChars->count; i++){
        free(images[i]);
    }
    free(images);
    SDL_DestroyTexture(texture);
}

void gridAdd(SDL_Renderer * renderer, SDL_Texture ** images, int length, int startX, int startY){
    
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
            rectangular.x = startX + 540 + 7 + j*70;
            rectangular.y = startY + 27 + i*70;
            rectangular.w = 65;
            rectangular.h = 65;
            SDL_RenderCopy(renderer, images[count], NULL, &rectangular);
            count++;
        }
    }

    if (y != 0){
        for (int j = 0; j < y; j++){
            SDL_Rect rectangular;
            rectangular.x = startX + 540 + 7 + j*70;
            rectangular.y = startY + 27 + i*70;
            rectangular.w = 65;
            rectangular.h = 65;
            SDL_RenderCopy(renderer, images[count], NULL, &rectangular);
            count++;
        }
    }
}

SDL_Texture * createImage(SDL_Renderer * renderer, char * source, int * width, int * height){

    char sourcePath[30] = "../chars3/"; // REMOVE THIS; PERFORM THE CONCAT BEFORE?
    strcat(sourcePath, source);

    SDL_Texture * img = IMG_LoadTexture(renderer, sourcePath);
    SDL_QueryTexture(img, NULL, NULL, width, height);
    return img;
}

// From a sorted array of images and scores (charScore), return ordered array 
// of SDL_textures

SDL_Texture ** charScore2texture(SDL_Renderer * renderer, charScore ** charList, int count){

    SDL_Texture ** textureList = malloc(sizeof(SDL_Texture *) * count);
    
    int w, h;

    // seems as if only 1 alloc wtf
    
    for (int i = 0; i < count; i++){
        textureList[i] = malloc(sizeof(textureList[0])); // SDL_Texture is opaque so bypass with pointer
        textureList[i] = createImage(renderer, charList[i]->name, &w, &h);
    }
    return textureList;
}

int main(int argc, char* args[]){

    SDL_Window   * window   = NULL;
    SDL_Renderer * renderer = NULL;
    
    int width = 1060;
    int height = 600; // 540 + 60 for above bar

    Database * db = parserGetDB("../chars3/");
    
    initWindow(&window, &renderer, width, height);

    createDrawingPane(db, renderer, 0, 60);
    
    closeWindow(window);

    parserEnd(db);

    return 0;
}
