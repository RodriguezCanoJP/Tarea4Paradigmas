#include <iostream>
#include <SDL.h>
#include "constants.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
int juego_corriendo = FALSE;

int initializa_ventana(void){
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        fprintf(stderr, "Error initializing SDL.\n");
        return FALSE;
    };

    window = SDL_CreateWindow(
            NULL,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            SDL_WINDOW_BORDERLESS
    );

    if(!window){
        fprintf(stderr, "Error initializing the window./n");
        return FALSE;
    }



    renderer = SDL_CreateRenderer(window, -1, 0);
    if(!renderer){
        fprintf(stderr, "Error initializing renderer.'n");
        return FALSE;
    }

    return TRUE;
}

void procesa_input(){
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type){
        case SDL_QUIT:
            juego_corriendo = FALSE;
            break;
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_ESCAPE){
                juego_corriendo = FALSE;
            }
    }
}

void render(){
    SDL_SetRenderDrawColor(renderer, 80, 70, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void destruye_ventana(void){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

int main() {

    juego_corriendo = initializa_ventana();

    while(juego_corriendo){
        procesa_input();
        render();
    }
    destruye_ventana();


    return 0;
}
