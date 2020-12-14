
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "display.h"
#include "vector.h"

#define N_POINTS  9*9*9

bool is_running = false;
vect3_t cube_points[N_POINTS];
vect2_t projected_points[N_POINTS];

vect3_t camera_position = { 0,0,-5 };
vect3_t cube_rotation = {0, 0, 0};

float fov_factor = 640;

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
                vect3_t np = {x,y,z};
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


vect2_t project(vect3_t point){
    vect2_t projected_point = {
        .x = (fov_factor * (point.x)) / point.z,
        .y = (fov_factor * (point.y)) / point.z
    };
    return projected_point;
}


void update(void){

    cube_rotation.x += 0.01;
    cube_rotation.y += 0.01;
    cube_rotation.z += 0.01;

    for(int i = 0; i< N_POINTS; ++i){
        vect3_t point = cube_points[i];

        vect3_t tp = vec3_rotate_y(point, cube_rotation.y);
        tp = vec3_rotate_x(tp, cube_rotation.x);
        tp = vec3_rotate_z(tp, cube_rotation.z);

        tp.z -= camera_position.z;

        vect2_t point2d = project(tp);
        projected_points[i] = point2d;
    }
}

void render(void){
    
    draw_grid();
    
    for(int i = 0; i<N_POINTS; i++){
        vect2_t ppoint2d = projected_points[i];
        draw_rectange(
            ppoint2d.x + (window_width/2),
            ppoint2d.y + (window_height/2),
        4, 4,0xFFFFFF00);
    }

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
