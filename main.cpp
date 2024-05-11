#include <iostream>
#include <SDL.h>
#include "constants.h"


int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow(
            NULL,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            SDL_WINDOW_BORDERLESS
    );

    if(!window){
        fprintf(stderr, "Error al inicalizar ventana.\n");
        return 0;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    if(!renderer){
        fprintf(stderr, "Error initializing renderer.'n");
        return 0;
    }
    while(SDL_GetTicks() < 3000){
        SDL_SetRenderDrawColor(renderer, 80, 70, 255, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }


    SDL_Delay(3000);

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}
