

#include "display.h"

SDL_Renderer* renderer = NULL;
SDL_Window* window = NULL;
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

void draw_pixel(int x, int y, uint32_t color){
    if(x < window_width && y < window_height && x>= 0 && y >=0){
        color_buffer[(window_width * (y)) + (x)] = color;
    }
}

void draw_rectange(int x,int y,int w, int h,uint32_t color){
    for(int i = 0; i < w; i++ ){
        for(int j= 0; j < h; j++ ){
            draw_pixel((x+i), (y+j), color);
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

void destroy_all(void){
    free(color_buffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}