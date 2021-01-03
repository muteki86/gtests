
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "array.h"
#include "display.h"
#include "vector.h"
#include "mesh.h"
#include "triangle.h"

bool is_running = false;
int previous_frame_time = 0;

vect3_t camera_position = { 0, 0, -5 };

float fov_factor = 640;

triangle_t* triangles_to_render = NULL;

void setup(void){
    color_buffer = (uint32_t*) malloc( sizeof(uint32_t) * window_width * window_height);
    color_buffer_texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        window_width,
        window_height
    );
    load_cube_mesh_data();
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

    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - previous_frame_time);

    if(time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME){
        SDL_Delay(time_to_wait);
    }

    previous_frame_time = SDL_GetTicks();

    triangles_to_render = NULL;

    mesh.rotation.x += 0.03;
    mesh.rotation.y += 0.03;
    mesh.rotation.z += 0.03;

    int num_faces = array_length(mesh.faces);
    for(int i = 0; i< num_faces; ++i){
        
        face_t mesh_face = mesh.faces[i];
        vect3_t face_vert[3];
        face_vert[0] = mesh.vertices[mesh_face.a - 1];
        face_vert[1] = mesh.vertices[mesh_face.b - 1];
        face_vert[2] = mesh.vertices[mesh_face.c - 1];

        triangle_t projected_triangle;

        for(int j = 0; j<3; j++){
            vect3_t t_v = face_vert[j];

            //rotate
            t_v = vec3_rotate_y(t_v, mesh.rotation.y);
            t_v = vec3_rotate_x(t_v, mesh.rotation.x);
            t_v = vec3_rotate_z(t_v, mesh.rotation.z);

            // translate in z
            t_v.z -= camera_position.z;

            //project
            vect2_t point2d = project(t_v);

            //translate  in x,y
            point2d.x += (window_width/2);
            point2d.y += (window_height/2);

            projected_triangle.points[j] = point2d;

        }
        //triangles_to_render[i] = projected_triangle;
        array_push(triangles_to_render, projected_triangle);
    }
}

void render(void){
    
    draw_grid();
    
    int n_triag = array_length(triangles_to_render);
    
    for(int i = 0; i < n_triag; i++){

        triangle_t triangle = triangles_to_render[i]; 
        
        draw_rectange(triangle.points[0].x,triangle.points[0].y, 4, 4,0xFFFFFF00);
        draw_rectange(triangle.points[1].x,triangle.points[1].y, 4, 4,0xFFFFFF00);
        draw_rectange(triangle.points[2].x,triangle.points[2].y, 4, 4,0xFFFFFF00);
        
        draw_triangle(
            triangle.points[0].x,
            triangle.points[0].y,
            triangle.points[1].x,
            triangle.points[1].y,
            triangle.points[2].x,
            triangle.points[2].y,
            0xFF00FF00  
        );
    }

    array_free(triangles_to_render);

    render_color_buffer();
    clear_color_buffer(0x00000F00);

    SDL_RenderPresent(renderer);
}

void free_resources(void){
    
    //free(color_buffer);
    //array_free(triangles_to_render);
    array_free(mesh.faces);
    array_free(mesh.vertices);
    
}

int main(void){

    is_running = initialize_window();

    setup();

    while(is_running){
        process_input();
        update();
        render();
    }

    free_resources();
    destroy_all();
    
    return 0;
}
