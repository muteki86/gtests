
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <SDL2/SDL.h>

SDL_Renderer* renderer = NULL;
SDL_Window* window = NULL;
bool is_running = false;

uint32_t* color_buffer = NULL;
SDL_Texture* color_buffer_texture = NULL;

int window_width = 800;
int window_height = 600;

bool initialize_window(void){
    
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        fprintf(stderr, "SDL is not working\n");
        return false;
    }

    SDL_DisplayMode display_mode;
    SDL_GetCurrentDisplayMode(0, &display_mode);
    window_width = display_mode.w;
    window_height = display_mode.h;
        
    window = SDL_CreateWindow(NULL, 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED,
        window_width,
        window_height,
        SDL_WINDOW_BORDERLESS
    );
    
    if(!window){
        fprintf(stderr, "Window broken\n");
        return false;
    }
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    renderer = SDL_CreateRenderer(window, -1, 0);

    if(!renderer){
        fprintf(stderr, "Renderer broken\n");
        return false;
    }

    return true;

} 

void setup(void){
    color_buffer = (uint32_t*) malloc( sizeof(uint32_t) * window_width * window_height);
    color_buffer_texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        window_width,
        window_height
    );
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

void clear_color_buffer(uint32_t color){
    for(int y= 0; y < window_height; y++ ){
        for(int x= 0; x < window_width; x++ ){
            color_buffer[(window_width * y) + x] = color;
        }
    }
}

void draw_grid(void){
    for(int y= 0; y < window_height; y+=10 ){
        for(int x= 0; x < window_width; x+=10 ){
            color_buffer[(window_width * y) + x] = 0xff333333;   
        }
    }
}

void draw_rectange(int x,int y,int w, int h,uint32_t color){
    for(int i = 0; i < w; i++ ){
        for(int j= 0; j < h; j++ ){
            color_buffer[(window_width * (y+j)) + (x+i)] = color;
        }
    }
}

void render_color_buffer(void){
    SDL_UpdateTexture(
        color_buffer_texture,
        NULL,
        color_buffer,
        (int)(window_width * sizeof(uint32_t))
    );
    SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void render(void){
    SDL_SetRenderDrawColor(renderer, 255,0,0,255);
    SDL_RenderClear(renderer);

    draw_grid();
    draw_rectange(300,200,300,150,0xfff00fff);
    render_color_buffer();
    clear_color_buffer(0x00000000);

    SDL_RenderPresent(renderer);
}

void destroy_all(void){
    free(color_buffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

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
