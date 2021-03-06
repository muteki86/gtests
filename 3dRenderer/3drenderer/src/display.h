
#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdbool.h>
#include <stdint.h>
#include <SDL2/SDL.h>

#define FPS 30
#define FRAME_TARGET_TIME (1000 / FPS)

extern SDL_Renderer* renderer ;
extern SDL_Window* window ;
extern uint32_t* color_buffer ;
extern SDL_Texture* color_buffer_texture ;
extern int window_width ;
extern int window_height ;

bool initialize_window(void);
void draw_grid(void);
void draw_pixel(int x, int y, uint32_t color);
void draw_line(int x0, int y0, int x1, int y1, uint32_t color);
void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
void draw_rectange(int x,int y,int w, int h,uint32_t color);
void render_color_buffer(void);
void clear_color_buffer(uint32_t color);
void destroy_all(void);


#endif