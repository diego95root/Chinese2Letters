#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main(int argc, char ** argv)
{
    _Bool leftMouseButtonDown = 0;
    _Bool quit = 0;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window * window = SDL_CreateWindow("TEST WRITING", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture * texture = SDL_CreateTexture(renderer,
        SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 640, 480);
    int pixels[640][640];

    memset(pixels, 255, 640 * 640 * sizeof(int));

    while (!quit)
    {
        SDL_UpdateTexture(texture, NULL, pixels, 640 * sizeof(int));

        SDL_WaitEvent(&event);

        switch (event.type)
        {
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
                if (leftMouseButtonDown)
                {
                    int mouseX = event.motion.x;
                    int mouseY = event.motion.y;
                    pixels[mouseY][mouseX] = 0;

                    int size = 7;

                    for (int i = -size/2; i<=size/2; i++){ // come up with algo to draw circle
                        for (int j = -size/2; j<=size/2; j++){
                            pixels[mouseY+i][mouseX+j] = 0;
                        }
                    }
                }
                break;
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}