
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "display.h"
#include "vector.h"

const int N_POINTS = 9*9*9;
bool is_running = false;
vec3_t cube_points[N_POINTS];

void setup(void){
    color_buffer = (uint32_t*) malloc( sizeof(uint32_t) * window_width * window_height);
    color_buffer_texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        window_width,
        window_height
    );

    int point_count = 0;
    for(float x = -1; x <= 1; x += 0.25){
        for(float y = -1; y <= 1; y += 0.25){
            for(float z = -1; z <= 1; z += 0.25){
                vec3_t np = {x,y,z};
                cube_points[point_count] = np;
                point_count++;
            }
        }
    }

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
    SDL_SetRenderDrawColor(renderer, 255,0,0,255);
    SDL_RenderClear(renderer);

    draw_grid();
    draw_rectange(300,200,300,150,0xfff00fff);
    draw_pixel(20, 20, 0xffffff00);
    render_color_buffer();
    clear_color_buffer(0x00000000);

    SDL_RenderPresent(renderer);
}

int main(void){

    is_running = initialize_window();

    setup();


    while(is_running){
        process_input();
        update();
        render();
    }

    destroy_all();
    
    return 0;
}
