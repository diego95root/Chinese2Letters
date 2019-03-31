#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "UI.h"

#define IMG_PATH "../de.png"

SDL_Rect * createPane(SDL_Renderer * renderer, int x, int y, int w, int h){

    SDL_Rect * pane = malloc(sizeof(SDL_Rect));
    pane->x = x;
    pane->y = y;
    pane->w = w;
    pane->h = h;

    SDL_RenderFillRect(renderer, pane);

    return pane;
}

void createDrawingPane(SDL_Renderer * renderer, SDL_Rect * pane){
    _Bool leftMouseButtonDown = 0;
    _Bool quit = 0;
    SDL_Event event;

    SDL_Texture * texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 500, 500);
    
    int pixels[500][500];
    
    memset(pixels, 255, 500 * 500 * sizeof(int));

    while (!quit){

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
            
            case SDL_MOUSEMOTION:
                if (leftMouseButtonDown){

                    int mouseX = event.motion.x - 20;
                    int mouseY = event.motion.y - 20;
                    pixels[mouseY][mouseX] = 0;

                    int size = 14;

                    for (int i = -size/2; i<=size/2; i++){ // come up with algo to draw circle
                        for (int j = -size/2; j<=size/2; j++){
                            pixels[mouseY+i][mouseX+j] = 0;
                        }
                    }
                }
                break;
        }

        SDL_RenderCopy(renderer, texture, NULL, pane);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(texture);
}

void gridAdd(SDL_Renderer * renderer, SDL_Texture * image){
    for (int i = 0; i < 7; i++){
        for (int j = 0; j < 7; j++){
            SDL_Rect rectangular;
            rectangular.x = 540 + 7 + i*67;
            rectangular.y = 27 + j*67;
            rectangular.w = 62;
            rectangular.h = 62;
            SDL_RenderCopy(renderer, image, NULL, &rectangular);
        }
    }
}

int main(int argc, char* args[]){

    SDL_Window* window = NULL;
    SDL_Surface* surface = NULL;
    SDL_Texture *img = NULL;
    SDL_Rect rects[14][12];
    int width = 1060;
    int height = 540;

    int w, h;

    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL_Error: %s\n", SDL_GetError());
    }

    else {
        
        window = SDL_CreateWindow("Chinese To Letters", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN); //Creates the window
        
        //SDL_SetWindowResizable(window, SDL_TRUE);
        
        if (window == NULL)
        {
            printf("SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //renderer used to color rects
            img = IMG_LoadTexture(renderer, IMG_PATH);
            SDL_QueryTexture(img, NULL, NULL, &w, &h);

            SDL_SetRenderDrawColor(renderer, 51, 102, 153, 255);
            SDL_RenderClear(renderer);


            SDL_SetRenderDrawColor(renderer, 255, 102, 100, 255);
            SDL_Rect * pane1 = createPane(renderer, 20, 20, 500, height - 40);



            SDL_SetRenderDrawColor(renderer, 100, 102, 200, 255);
            createPane(renderer, 540, 20, width - 560, height - 40);

            gridAdd(renderer, img);

            createDrawingPane(renderer, pane1);

            //SDL_RenderPresent(renderer);

            /*
            _Bool quit = 0;
            SDL_Event e;
            while( !quit ){
              while( SDL_PollEvent( &e ) != 0 )
                {
                    //User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = 1;
                    }
                }
            }
            */
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
