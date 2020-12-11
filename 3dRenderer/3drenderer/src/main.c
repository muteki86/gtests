
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

SDL_Renderer* renderer = NULL;
SDL_Window* window = NULL;

bool is_running = false;

bool initialize_window(void){
    
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        fprintf(stderr, "SDL is not working\n");
        return false;
    }

    window = SDL_CreateWindow(NULL, 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED,
        800,
        600,
        SDL_WINDOW_BORDERLESS
    );
    
    if(!window){
        fprintf(stderr, "Window broken\n");
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);

    if(!renderer){
        fprintf(stderr, "Renderer broken\n");
        return false;
    }

    return true;

} 

void setup(void){

}

void process_input(void){
    SDL_Event event;
    SDL_PollEvent(&event);

    switch(event.type){
        case SDL_QUIT:
            is_running = false;
            break;
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_ESCAPE){
                is_running = false;
                break;
            }
    }
}

void update(void){

}

void render(void){

}

int main(void){

    is_running = initialize_window();

    setup();

    while(is_running){
        process_input();
        update();
        render();

    }

    return 0;
}
