#include <SDL.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include "constants.h"

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;
char server_response[32];
int newtwork_socket;
int juego_corriendo = FALSE;
int num_oponentes = 1;
float ultimo_tiempo = 0.0f;
float curvaturaActual = 0;
float curvaturaPista = 0;
float secciones[10][2] = {{1000.0f, 0.0f},
                   {200.0f, 0.3f},
                   {200.0f, -0.7f},
                   {800.0f, 0.6f},
                   {800.0f, 0.0f},
                   {400.0f, 1.0f},
                   {400.0f, 0.0f},
                   {200.0f, -1.0f},
                   {800.0f, 0.0f},
                   {400.0f, -0.2f}};

struct Car{
    float distancia;
    float velocidad;
    float posicion;
    int posx;
    float curvatura;
} car;

struct Opp{
    float distancia;
    float posicion;
    int posx;
};

struct Pista{
    int nseccion;
    float curvatura;
    float distancia;
} pista;

int initializa_ventana(){
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        fprintf(stderr, "Error al inicializar SDL.\n");
        return FALSE;
    }

    window = SDL_CreateWindow(
            nullptr,
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

 int conexion_socket(){
    newtwork_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = INADDR_ANY;

    int connection_status = connect(newtwork_socket, (struct sockaddr *)&server_address, sizeof(server_address));
    if(connection_status == -1){
        printf("No se pudo conectar con el servidor.\n");
        return FALSE;
    }
    return TRUE;
}

Opp* setup(int ncars){
    car.distancia=0.0f;
    car.velocidad=0.0f;
    pista.nseccion = 0;
    pista.curvatura = secciones[pista.nseccion][1];
    pista.distancia = secciones[pista.nseccion][0];

    Opp *opponents[ncars];
    for(int i = 0; i < ncars; i++){
        opponents[i] = new Opp;
        if(car.posicion != 0){
            opponents[i]->posicion = i;
        }
        opponents[i]->distancia = 0.0f;

    }

    return opponents[0];
}

void recibe_datos(){
    recv(newtwork_socket, &server_response, sizeof(server_response), 0);
    printf("%s\n", server_response);
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
                    if(car.velocidad < 360){
                        car.velocidad+=5.0f;
                        break;
                    }
                    else{
                        break;
                    }
                case SDLK_DOWN:
                    car.velocidad = abs(car.velocidad - 5.0f);
                    break;
                case SDLK_LEFT:
                    car.curvatura -= 10.7f;
                    break;
                case SDLK_RIGHT:
                    car.curvatura += 10.7f;
                    break;
                case SDLK_ESCAPE:
                    juego_corriendo = FALSE;
                    break;
                default:
                    break;
            }
        default:
            car.velocidad = abs(car.velocidad - 0.7f);
            break;
    }
}
void actualiza(Opp* opps){
    float tiempo_de_espera = FRAME_TARGET_TIME - ((float)SDL_GetTicks() - ultimo_tiempo);

    if(tiempo_de_espera>0 && tiempo_de_espera<=FRAME_TARGET_TIME) {
        SDL_Delay(FRAME_TARGET_TIME);
    }
    float delta_time = ((float)SDL_GetTicks() - ultimo_tiempo)/1000.0f;
    car.distancia += delta_time * car.velocidad;
    if(car.distancia >= pista.distancia){
        car.distancia = 0;
        pista.nseccion +=1;
        pista.curvatura = secciones[pista.nseccion][1];
    }
    ultimo_tiempo = (float)SDL_GetTicks();
    float diffCurvas = (pista.curvatura - curvaturaActual) * delta_time;
    curvaturaActual += diffCurvas;

    curvaturaPista += (pista.curvatura)* delta_time * car.velocidad;
    car.posx = 350 + car.curvatura - curvaturaPista;

    if(car.posx < 0 || car.posx >= WINDOW_WIDTH - CAR_WIDTH){
        car.velocidad = 5.0f;
    }

    recibe_datos();

    float distancia_temp = atof(server_response + 1);

    for(int i = 0; i < num_oponentes; i++){
        opps[i].distancia = distancia_temp + 100;
    }
}

void render(Opp *opps){
    SDL_SetRenderDrawColor(renderer, 80, 70, 255, 255);
    SDL_RenderClear(renderer);

    for(int y=0; y < WINDOW_HEIGHT/2; y++){
        float perspectiva = (float)y/ ((float)WINDOW_HEIGHT/2);
        float puntoMedio = 0.5f + curvaturaActual * pow((1-perspectiva),3);
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

        for(int x=0; x < WINDOW_WIDTH; x++){
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
    for (int i = 0; i < num_oponentes; ++i) {
        int diffDistance = (int) opps[i].distancia - car.distancia;
        if (diffDistance < WINDOW_HEIGHT/2 && diffDistance > 0) {
            int alpha = (2 * 80.0 / WINDOW_HEIGHT) * diffDistance;
            //opps[i].posx = car.posx + alpha;
            SDL_SetRenderDrawColor(renderer, 0, 0, 100, 100);
            SDL_Rect opp_sprite = {car.posx + alpha,
                                   CAR_Y_POS - diffDistance,
                                   CAR_WIDTH - alpha,
                                   CAR_HEIGHT - alpha};
            SDL_RenderFillRect(renderer, &opp_sprite);
        }
    }

    SDL_SetRenderDrawColor(renderer, 200, 20, 20, 100);
    SDL_Rect sprite = {car.posx, CAR_Y_POS, CAR_WIDTH, CAR_HEIGHT};
    SDL_RenderFillRect(renderer, &sprite);
    SDL_RenderPresent(renderer);
}



void enviar_datos(){
    sprintf(server_response, "%i%f", pista.nseccion, car.distancia);
    send(newtwork_socket, &server_response, sizeof(server_response), 0);
}

void destruye_ventana(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

int main() {
    juego_corriendo = initializa_ventana();
    Opp *oponentes = setup(num_oponentes);
    conexion_socket();

    while(juego_corriendo){
        procesa_input();
        actualiza(oponentes);
        render(oponentes);
        enviar_datos();
    }
    close(newtwork_socket);
    destruye_ventana();
    return 0;
}
