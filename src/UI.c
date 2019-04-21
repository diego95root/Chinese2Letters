#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include "database.h"
#include "parser.h"
#include "UI.h"

// Initialise all necessary things for the main window, including its size

void initWindow(SDL_Window * window, SDL_Renderer ** renderer, int width, int height){
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0){

        printf("SDL_Error: %s\n", SDL_GetError());

    }

    window = SDL_CreateWindow("Chinese To Letters", SDL_WINDOWPOS_UNDEFINED, 
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

    *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //renderer used to color rects
    SDL_SetRenderDrawBlendMode(*renderer, SDL_BLENDMODE_BLEND);

}

// Initialise font given the source

TTF_Font * initFont(char * font, int size){

    if (TTF_Init() < 0) {
        printf("Error: couldn't load font from %s\n");
    }

    TTF_Font * fontPtr = TTF_OpenFont(font, size);
    return fontPtr;
}

// Free all elements created by the SDL library and quit the program

void closeWindow(SDL_Window * window){
    TTF_Quit(); // close font data
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

// Same as the function above, but this one checks if in the first pane

_Bool onFirstPane(SDL_Event event, int startX, int startY){
    return event.motion.x < startX + 520 && event.motion.x > startX + 20 
            && event.motion.y < startY + 520 && event.motion.y > startY + 20;
}

// Given an SDL_Event, return true if the mouse is within some coordinates (second pane)

_Bool onSecondPane(SDL_Event event, int startX, int startY){
    
    int x = event.motion.x;
    int y = event.motion.y;

    _Bool goodX = x > startX + 540 && x < startX + 1040;
    _Bool goodY = y > startY + 20 && y < startY + 520;
    
    return goodX && goodY;
}

// return true if mouse is on a button from the top bar

_Bool onButtonsPane(SDL_Event event){
    _Bool goodY = event.motion.y > 20 && event.motion.y < 60;
    _Bool goodX = event.motion.x > 20 && event.motion.x < 450;
    _Bool clearX = event.motion.x > 910 && event.motion.x < 1040;
    _Bool notSpaceX = event.motion.x % 150 > 20;
    return (goodX && notSpaceX || clearX) && goodY;
}

// draw a circle based on the circle's equation: (x - a)**2 + (y - b)**2 = r**2

void drawCircle(int pixels[500][500], int x, int y, int radius){

    for (int i = x - radius; i <= x + radius; i++){
        for (int j = y - radius; j <= y + radius; j++){

            // use circle equation
            if (pow(x-i, 2) + pow(y-j, 2) <= pow(radius, 2)){

                // checks to prevent segfaults when drawing outside
                if (j >= 0 && j < 500 && i >= 0 && i < 500){ 
                    pixels[j][i] = 0;
                }
            }
        }    
    }
}

SDL_Texture * loadImage(SDL_Renderer * renderer, char * source){
    SDL_Surface * loadedSurface = IMG_Load(source);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);
    return texture;
}

void loadMessage(SDL_Renderer * renderer, char * text, TTF_Font * font){
    
    SDL_SetRenderDrawColor(renderer, 51, 102, 153, 255);
    createPane(renderer, 480, 20, 400, 40);

    SDL_Color White = {255, 255, 255};
    SDL_Surface* surfaceMessage = TTF_RenderUTF8_Blended(font, text, White);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(Message, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = {480, 30, texW, texH };

    SDL_RenderCopy(renderer, Message, NULL, &dstrect);
}

// Copies images (passed in a pointer to an array of SDL_Textures) to a location
// in the window (second pane)

void gridAdd(SDL_Renderer * renderer, SDL_Texture ** images, int length, int startX, int startY){
    
    if (length > 49){ // maximum number of individual cells
        length = 49;
    }

    for (int i = 0; i < length; i++){

        int x = i % 7;
        int y = i / 7;

        // background pane for blackish border around picture

        createPane(renderer, startX + 540 + 5 + x*70, startY + 25 + y*70, 69, 69);

        // image inside rect
        
        SDL_Rect rectangular;
        rectangular.x = startX + 540 + 7 + x*70;
        rectangular.y = startY + 27 + y*70;
        rectangular.w = 65;
        rectangular.h = 65;
        SDL_RenderCopy(renderer, images[i], NULL, &rectangular);

    }
}

// Create an image texture from the directory and the name of the file provided,
// it returns a pointer to that SDL_Texture.

SDL_Texture * createImage(SDL_Renderer * renderer, char * source, char sourcePath[], int * width, int * height){

    char join[30] = "";
    strcat(join, sourcePath);
    strcat(join, source);

    SDL_Texture * img = IMG_LoadTexture(renderer, join);
    SDL_QueryTexture(img, NULL, NULL, width, height);
    return img;
}

// From an array of images and scores (charScore) with their directory, return pointer to an array 
// of SDL_textures

SDL_Texture ** charScore2texture(SDL_Renderer * renderer, charScore ** charList, char sourcePath[], int count){

    SDL_Texture ** textureList = malloc(sizeof(SDL_Texture *) * count);
    
    int w, h;
    
    for (int i = 0; i < count; i++){
        textureList[i] = createImage(renderer, charList[i]->name, sourcePath, &w, &h);
    }
    return textureList;
}

// Destory all data from images (stored in a pointer to an array of SDL_Textures) and
// free all data in the charScoreList structure

void freeIterationData(charScoreList * chars, SDL_Texture ** images){
    if (chars->count != 0){
        for (int i = 0; i < chars->count; i++){
            SDL_DestroyTexture(images[i]);
        }                
        free(images);
        freeCharScoreList(chars);
    }
}

// Set drawing grid to be all white

void clearGrid(int matrix[500][500]){
    for (int i = 0; i < 500; i++){
        for (int j = 0; j < 500; j++){
            matrix[i][j] = -257;
        }
    }
}

// Main loop of the app

void mainLoopWindow(Database * db, SDL_Renderer * renderer, TTF_Font * font, int startX, int startY){
    
    // control flags

    _Bool leftMouseButtonDown = 0;
    _Bool quit = 0;
    _Bool modifiedButtons = 1;

    _Bool activeOne = 1;
    _Bool activeTwo = 0;
    _Bool activeThree = 0;

    int mode = 0;
    int strokes = 0;

    SDL_Event event;

    // set up different cursors

    SDL_Cursor * initialCursor = SDL_GetCursor();
    SDL_Surface * image = IMG_Load("../images/mouse.png");
    SDL_Cursor * sdlMouseCursor = SDL_CreateColorCursor(image, 14, 8);

    // create and set grid to white

    int pixels[500][500];
    
    clearGrid(pixels); // set all to white

    // get all data for the grid

    charScoreList * valueChars = parserInit(db, strokes, pixels, mode);
    SDL_Texture ** images = charScore2texture(renderer, valueChars->elements, db->sourcePath, valueChars->count);
    SDL_Texture * texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 500, 500);

    // load all images in an array of sdl textures 

    char imagesArray[][20] = {"../images/m1.png", "../images/m1b.png", 
                              "../images/m2.png", "../images/m2b.png",
                              "../images/m3.png", "../images/m3b.png",
                              "../images/clear.png"
                            };

    SDL_Texture * loadedTextures[6];

    for (int i = 0; i < 7; i++){
        loadedTextures[i] = loadImage(renderer, imagesArray[i]);
    }

    // set background color for window

    SDL_SetRenderDrawColor(renderer, 51, 102, 153, 255);
    SDL_RenderClear(renderer);

    // set first pane, where drawings will be done

    SDL_SetRenderDrawColor(renderer, 255, 102, 100, 255);
    SDL_Rect * pane1 = createPane(renderer, startX + 20, startY + 20, 500, 500);

    // simulate background for first and second pane

    SDL_SetRenderDrawColor(renderer, 60, 60, 60, 255);
    SDL_Rect * paneSub1 = createPane(renderer, startX + 18, startY + 18, 504, 504);
    SDL_Rect * paneSub2 = createPane(renderer, startX + 38 + 500, startY + 18, 504, 504);

    // four top panes, one for each button

    SDL_Rect * pane2; // pane for images
    SDL_Rect * pane3 = createPane(renderer, 20, 20, 130, 40);
    SDL_Rect * pane4 = createPane(renderer, 170, 20, 130, 40);
    SDL_Rect * pane5 = createPane(renderer, 320, 20, 130, 40);
    SDL_Rect * pane6 = createPane(renderer, 910, 20, 130, 40);

    while (!quit){

        // update drawing pane on each iteration

        SDL_UpdateTexture(texture, NULL, pixels, 500 * sizeof(int));

        // second pane, where images will be presented, needs rendering on every cycle 
        // due to the rectangle over images to simulate hover (if not rendered again it
        // stays there)

        SDL_SetRenderDrawColor(renderer, 100, 102, 200, 255);
        pane2 = createPane(renderer, startX + 40 + 500, startY + 20, 500, 500);
        SDL_SetRenderDrawColor(renderer, 60, 60, 60, 255); // reset color back to blackish
        
        // add images to new pane

        gridAdd(renderer, images, valueChars->count, startX, startY);
        
        
        if (modifiedButtons){ // only load buttons again if they have been modified

            // load blue or black depending on active flag

            SDL_RenderCopy(renderer,  loadedTextures[0 + activeOne], NULL, pane3);
            SDL_RenderCopy(renderer, loadedTextures[2 + activeTwo], NULL, pane4);
            SDL_RenderCopy(renderer, loadedTextures[4 + activeThree], NULL, pane5);

            // always same button, but needs rendering again to remove black hover rect

            SDL_RenderCopy(renderer, loadedTextures[6], NULL, pane6);

            mode = activeTwo + activeThree * 2; // calculate new mode for algorithm
            modifiedButtons = 0;

        }

        SDL_WaitEvent(&event);

        switch (event.type){

            case SDL_QUIT:
                quit = 1;
                break;
            
            case SDL_MOUSEBUTTONUP:

                if (event.button.button == SDL_BUTTON_LEFT && onFirstPane(event, startX, startY)){
                    
                    leftMouseButtonDown = 0;
                    strokes++;

                    // Update in case of new stroke by freeing previous elements first

                    freeIterationData(valueChars, images);

                    // get new elements

                    valueChars = parserInit(db, strokes, pixels, mode);
                    images = charScore2texture(renderer, valueChars->elements, db->sourcePath, valueChars->count);
                    gridAdd(renderer, images, valueChars->count, startX, startY);

                    // add message to indicate number of strokes

                    char textMessage[24];
                    sprintf(textMessage, "Number of strokes: %d", strokes);

                    loadMessage(renderer, textMessage, font);

                    break;
                }
            
            case SDL_MOUSEBUTTONDOWN:
                
                if (event.button.button == SDL_BUTTON_LEFT){
                    
                    if (onFirstPane(event, startX, startY)){

                        // Flag to know if we can draw 

                        leftMouseButtonDown = 1;                        
                    
                    }

                    else if (onSecondPane(event, startX, startY)){
                        
                        int x = round((event.motion.x - 547)/70);
                        int y = round((event.motion.y - startY - 27)/70);
                        
                        if ( y * 7 + x < valueChars->count){ // only copy if over image

                            // Copy name to array of chars

                            char message[7];
                            strncpy(message, valueChars->elements[y*7+x]->name, 6);

                            // Convert char array to a byte array

                            uint8_t * data = hex2byteArray(message);

                            // Convert pointer to string in order to copy to clipboard

                            char final[4];
                            strncpy(final, data, 3);

                            // set up message to be printed on the screen

                            char textMessage[25] = "Copied to clipboard: ";
                            strcat(textMessage, final);

                            loadMessage(renderer, textMessage, font);
                            SDL_SetClipboardText(final);
                        }
                    }

                    else if (onButtonsPane(event)){

                        // Draw semi visible rectangle in black to simulate button click

                        int x = event.motion.x / 150;

                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 140);
                        
                        // subtract 10 if on clear button (it doesn't match otherwise)

                        SDL_Rect * rectangular = createPane(renderer, 
                                                            (x+1)*20 + x*130 - ((x==6) * 10),
                                                            20, 
                                                            130, 
                                                            40);

                        SDL_RenderFillRect(renderer, rectangular);

                        // detect button and set flags to know which images to render

                        if (x == 0){
                            activeOne = 1;
                            activeTwo = 0;
                            activeThree = 0;
                            loadMessage(renderer, "Changed mode to Quick", font);
                        }
                        else if (x == 1){
                            activeOne = 0;
                            activeTwo = 1;
                            activeThree = 0;
                            loadMessage(renderer, "Changed mode to Normal", font);
                        }
                        else if (x == 2){
                            activeOne = 0;
                            activeTwo = 0;
                            activeThree = 1;
                            loadMessage(renderer, "Changed mode to Exhaustive", font);
                        }
                        else if (x == 6){

                            // Reset app to start again everything 
                            
                            strokes = 0; // reset strokes to 0

                            clearGrid(pixels); // clear drawing grid

                            loadMessage(renderer, "", font); // clear message area

                            // Update in case of new stroke by freeing previous elements first

                            freeIterationData(valueChars, images);

                            // get new elements

                            valueChars = parserInit(db, strokes, pixels, mode);
                            images = charScore2texture(renderer, valueChars->elements, 
                                                       db->sourcePath, valueChars->count);
                            gridAdd(renderer, images, valueChars->count, startX, startY);

                        }

                        // Flag to render buttons again but with different images

                        modifiedButtons = 1;
                    }
                }
            
            case SDL_MOUSEMOTION:

                if (onFirstPane(event, startX, startY) && leftMouseButtonDown){

                    // Calculate coordinates to draw circle on pane

                    int mouseX = event.motion.x - startX - 20;
                    int mouseY = event.motion.y - startY - 20;

                    int radius = 18;

                    drawCircle(pixels, mouseX, mouseY, radius);
                
                }

                else if (onSecondPane(event, startX, startY)){

                    // Draw semi visible rectangle on top of 
                    // character image to simulate hover effect

                    int x = round((event.motion.x - startX - 547)/70);
                    int y = round((event.motion.y - startY - 27)/70);

                    if ( y * 7 + x < valueChars->count){ // only color if over image

                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
                        SDL_Rect * rectangular = createPane(renderer, 
                                                            startX + 540 + 7 + x*70,
                                                            startY + 27 + y*70, 
                                                            65, 
                                                            65);
                        SDL_RenderFillRect(renderer, rectangular);

                        SDL_SetCursor(sdlMouseCursor); // change cursor to hand
                    }

                    else {
                        
                        // if on second pane but not on image then normal cursor

                        SDL_SetCursor(initialCursor);
                    
                    }
                
                }

                else if (onButtonsPane(event)){

                    // if over button set cursor to normal

                    SDL_SetCursor(sdlMouseCursor);
                
                }

                else {
                
                    // if not over anything normal cursor. Prevents cursor 
                    // from staying hand when it stops being over button

                    SDL_SetCursor(initialCursor);
                
                }

                break;
        }

        // copy drawing grid to texture and render everything

        SDL_RenderCopy(renderer, texture, NULL, pane1);
        SDL_RenderPresent(renderer);
    }

    //writeMatrix(pixels, "data");

    // free all panes and data before exiting

    free(pane1);
    free(pane2);
    free(pane3);
    free(pane4);
    free(pane5);
    free(pane6);

    freeIterationData(valueChars, images);

    SDL_FreeSurface(image);
    SDL_FreeCursor(sdlMouseCursor);
    SDL_FreeCursor(initialCursor);
}

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
