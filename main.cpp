#include <iostream>
#include <SDL.h>
#include "constants.h"

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;
int juego_corriendo = FALSE;
float ultimo_tiempo = 0.0f;
float curvaturaActual = 0;
int curvatura;
int seccion = 0;
int secciones[10][2] =  {{2000, 0},
                              {1000, -1},
                              {1000, -2},
                              {3000, 0},
                              {700, 1},
                              {700, -1},
                              {2000, 0},
                              {1000, 1},
                              {1000, 2},
                              {4000, 0}};

struct car{
    float distancia;
    float velocidad;
} car;

int initializa_ventana(){
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        fprintf(stderr, "Error al inicializar SDL.\n");
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
        fprintf(stderr, "Error al inicializar la ventana.\n");
        return FALSE;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if(!renderer){
        fprintf(stderr, "Error al inicializar el renderer.\n");
        return FALSE;
    }
    return TRUE;
}

void setup(){
    car.distancia=0.0f;
    car.velocidad=0.0f;
    curvatura = secciones[seccion][1];
}

void procesa_input(){
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type){
        case SDL_QUIT:
            juego_corriendo = FALSE;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    car.velocidad+=5.0f;
                    break;
                case SDLK_DOWN:
                    car.velocidad = abs(car.velocidad - 5.0f);
                    break;
                case SDLK_ESCAPE:
                    juego_corriendo = FALSE;
                    break;
                default:
                    break;
            }
        default:
            car.velocidad = abs(car.velocidad - 1.0f);
            break;
    }
}
void actualiza(){
    float tiempo_de_espera = FRAME_TARGET_TIME - (SDL_GetTicks() - ultimo_tiempo);

    if(tiempo_de_espera>0 && tiempo_de_espera<=FRAME_TARGET_TIME) {
        SDL_Delay(FRAME_TARGET_TIME);
    }
    float delta_time = (SDL_GetTicks() - ultimo_tiempo)/1000.0f;
    car.distancia += delta_time * car.velocidad;
    if(car.distancia >= secciones[seccion][0]){
        car.distancia = 0;
        seccion +=1;
        curvatura = secciones[seccion][1];
    }
    ultimo_tiempo = SDL_GetTicks();
    float diffCurvas = (curvatura - curvaturaActual)*delta_time;
    curvaturaActual += diffCurvas;
}

void render(){
    SDL_SetRenderDrawColor(renderer, 80, 70, 255, 255);
    SDL_RenderClear(renderer);

    for(int y=0; y < WINDOW_HEIGHT/2; y++){
        for(int x=0; x < WINDOW_WIDTH; x++){
            float perspectiva = (float)y/ (WINDOW_HEIGHT/2);





            float puntoMedio = 0.5f + curvaturaActual * pow((1-perspectiva),2);
            float anchoCalle = 0.1f  + perspectiva * 0.8f;
            float anchoKerbs = anchoCalle * 0.15f;

            anchoCalle *= 0.5;

            int PastoIzquierda = (puntoMedio - anchoCalle - anchoKerbs) * WINDOW_WIDTH;
            int PastoDerecha = (puntoMedio + anchoCalle + anchoKerbs) * WINDOW_WIDTH;
            int KerbsIzquierda = (puntoMedio - anchoCalle) * WINDOW_WIDTH;
            int KerbsDerecha = (puntoMedio + anchoCalle ) * WINDOW_WIDTH;

            int row = WINDOW_HEIGHT/2 + y;
            int color = sinf(20.0f * powf(1-perspectiva, 3) + car.distancia * 0.1f) > 0.0f? 30:80;
            int kerbsColor = sinf(30.0f * powf(1-perspectiva, 3) + car.distancia * 0.3f) > 0.0f? 0:255;

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

    SDL_SetRenderDrawColor(renderer, 200, 20, 20, 100);
    SDL_Rect sprite = {350, 500, 100, 50};
    SDL_RenderFillRect(renderer, &sprite);
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
