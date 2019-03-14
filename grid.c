#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#define IMG_PATH "de.png"

int main(int argc, char* args[]){

    SDL_Window* window = NULL;
    SDL_Surface* surface = NULL;
    SDL_Texture *img = NULL;
    SDL_Rect rects[14][12];
    int width = 1040;
    int height = 560;

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
            SDL_Renderer* renderer = NULL;
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //renderer used to color rects
            img = IMG_LoadTexture(renderer, IMG_PATH);
            SDL_QueryTexture(img, NULL, NULL, &w, &h);

            SDL_SetRenderDrawColor(renderer, 51, 102, 153, 255);
            SDL_RenderClear(renderer);

            SDL_SetRenderDrawColor(renderer, 255, 102, 100, 255);

            SDL_Rect pane1;
            pane1.x = 20;
            pane1.y = 20;
            pane1.w = 600;
            pane1.h = height - 40;

            SDL_RenderFillRect(renderer, &pane1);

            SDL_SetRenderDrawColor(renderer, 100, 102, 200, 255);

            SDL_Rect pane2;
            pane2.x = pane1.w + 40;
            pane2.y = 20;
            pane2.w = width - pane1.w - 60;
            pane2.h = height - 40;

            SDL_RenderFillRect(renderer, &pane2);


            for (int i = 0; i < 14; i++)
                for (int j = 0; j < 12; j++)
                {
                    SDL_Rect rectangular;
                    rectangular.x = 27 + i*42;
                    rectangular.y = 27 + j*42;
                    rectangular.w = 40;
                    rectangular.h = 40;
                    SDL_RenderCopy(renderer, img, NULL, &rectangular);
                }

            SDL_RenderPresent(renderer);

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
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
