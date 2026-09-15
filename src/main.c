#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>

int main(void) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Error inicializando SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Hola, SDL2 en macOS",
                                           SDL_WINDOWPOS_CENTERED,
                                           SDL_WINDOWPOS_CENTERED,
                                           640, 480, 0);
    if (!window) {
        printf("Error creando ventana: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Mantener la ventana abierta
    bool running = true;
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

