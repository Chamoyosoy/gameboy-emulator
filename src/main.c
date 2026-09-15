#include <stdio.h>
#include <stdbool.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

int main(int argc, char* argv[]) {
    // 1. Initialize SDL3 Video subsystem
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    // 2. Create the window
    SDL_Window* window = SDL_CreateWindow(
        "Hello SDL3",       // Title
        640,                // Width
        480,                // Height
        SDL_WINDOW_OPENGL   // Flags
    );

    if (!window) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // 3. Main loop
    bool done = false;
    SDL_Event event;
    while (!done) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                done = true;
            }
        }
        // Game logic and rendering go here
    }

    // 4. Cleanup
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}   
