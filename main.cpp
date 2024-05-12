#include <iostream>
#include <SDL.h>
#include "constants.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
int juego_corriendo = FALSE;

struct car{
    float distance;
    float speed;
} car;

int initializa_ventana(){
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

void setup(){
    car.distance=0.0f;
    car.speed=0.0f;
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
        default:
            break;
    }
}
void actualiza(){
    car.distance += 1;
}

void render(){
    SDL_SetRenderDrawColor(renderer, 80, 70, 255, 255);
    SDL_RenderClear(renderer);

    for(int y=0; y < WINDOW_HEIGHT/2; y++){
        for(int x=0; x < WINDOW_WIDTH; x++){
            float fPerspective = (float)y/ (WINDOW_HEIGHT/2);

            float fPuntoMedio = 0.5f;
            float fAnchoCalle = 0.1f  + fPerspective * 0.8f;
            float fAnchoKerbs = fAnchoCalle * 0.15f;


            fAnchoCalle *= 0.5;

            int PastoIzquierda = (fPuntoMedio - fAnchoCalle - fAnchoKerbs) * WINDOW_WIDTH;
            int PastoDerecha = (fPuntoMedio + fAnchoCalle + fAnchoKerbs) * WINDOW_WIDTH;
            int KerbsIzquierda = (fPuntoMedio - fAnchoCalle) * WINDOW_WIDTH;
            int KerbsDerecha = (fPuntoMedio + fAnchoCalle ) * WINDOW_WIDTH;

            int row = WINDOW_HEIGHT/2 + y;
            int color = sinf(20.0f * powf(1-fPerspective, 3) + car.distance * 0.1f) > 0.0f? 30:80;
            int kerbsColor = sinf(20.0f * powf(1-fPerspective, 3) + car.distance * 0.3f) > 0.0f? 0:255;


            if(x >=0 && x < PastoIzquierda){
                SDL_SetRenderDrawColor(renderer, color, 150, color, 56);
                SDL_RenderDrawPoint(renderer, x, row);
            }
            if(x >= PastoIzquierda && x<KerbsIzquierda){
                SDL_SetRenderDrawColor(renderer, 255, kerbsColor, kerbsColor, 255);
                SDL_RenderDrawPoint(renderer, x, row);
            }
            if(x >= KerbsIzquierda && x<KerbsDerecha){
                SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
                SDL_RenderDrawPoint(renderer, x, row);
            }
            if(x >= KerbsDerecha && x<PastoDerecha){
                SDL_SetRenderDrawColor(renderer, 255, kerbsColor, kerbsColor, 255);
                SDL_RenderDrawPoint(renderer, x, row);
            }
            if(x >= PastoDerecha){
                SDL_SetRenderDrawColor(renderer, color, 150, color, 56);
                SDL_RenderDrawPoint(renderer, x, row);
            }
        }
    }

    SDL_RenderPresent(renderer);
}

void destruye_ventana(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

int main() {

    juego_corriendo = initializa_ventana();
    setup();

    while(juego_corriendo){
        procesa_input();
        actualiza();
        render();
    }
    destruye_ventana();


    return 0;
}
