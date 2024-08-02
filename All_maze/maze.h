#ifndef MAZE_H
#define MAZE_H

#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>


#define SCREEN_WIDTH 1204
#define SCREEN_HEIGHT 990
#define MAP_WIDTH 24
#define MAP_HEIGHT 24
#define NUM_TEXTURES 4
#define NUM_ENEMIES 5
#define TILE_SIZE 64
#define MAX_RAIN_DROPS 500

typedef struct {
    double x, y;        /*Position */
    double dirX, dirY;  /* Direction vector */
    SDL_Texture *texture; /* Enemy texture */
} Enemy;

typedef struct {
    double x;
    double y;
    double speed;
    int visible; /* Flag to indicate if raindrop is visible */
} Raindrop;

extern Raindrop raindrops[MAX_RAIN_DROPS]; /* Declare raindrops array as extern */


/* Functions prototype */

int init_sdl(SDL_Window **window, SDL_Renderer **renderer);
void close_sdl(SDL_Window *window, SDL_Renderer *renderer);
SDL_Texture *load_texture(SDL_Renderer *renderer, const char *file);
SDL_Texture *load_weapon_texture(SDL_Renderer *renderer, const char *file);

void handle_events(SDL_Event *event, int *running, double *posX, double *posY, double *dirX, double *dirY, double *planeX, double *planeY, double moveSpeed, double rotSpeed, int map[MAP_WIDTH][MAP_HEIGHT]);
void update_position(const Uint8 *keystate, double *posX, double *posY, double *dirX, double *dirY, double *planeX, double *planeY, int map[MAP_WIDTH][MAP_HEIGHT], double moveSpeed, double rotSpeed);
void render_scene(SDL_Renderer *renderer, SDL_Texture *textures[], SDL_Texture *weapon_texture, SDL_Window *window, Enemy enemies[], int num_enemies, double posX, double posY, double dirX, double dirY, double planeX, double planeY, int map[MAP_WIDTH][MAP_HEIGHT]);

void move_forward(double *posX, double *posY, double dirX, double dirY, double moveSpeed, int map[MAP_WIDTH][MAP_HEIGHT]);
void move_backward(double *posX, double *posY, double dirX, double dirY, double moveSpeed, int map[MAP_WIDTH][MAP_HEIGHT]);
void strafe_left(double *posX, double *posY, double planeX, double planeY, double moveSpeed, int map[MAP_WIDTH][MAP_HEIGHT]);
void strafe_right(double *posX, double *posY, double planeX, double planeY, double moveSpeed, int map[MAP_WIDTH][MAP_HEIGHT]);

void init_rain(void);
void toggle_rain(void);
int is_raining(void);
void update_raindrops(void);
void render_rain(SDL_Renderer *renderer);

void move_left(double *posX, double *posY, double dirX, double dirY, double planeX, double planeY, double moveSpeed, int map[MAP_WIDTH][MAP_HEIGHT]);
void move_right(double *posX, double *posY, double dirX, double dirY, double planeX, double planeY, double moveSpeed, int map[MAP_WIDTH][MAP_HEIGHT]);
void rotate_left(double *dirX, double *dirY, double *planeX, double *planeY, double rotSpeed);
void rotate_right(double *dirX, double *dirY, double *planeX, double *planeY, double rotSpeed);

void render_weapon(SDL_Renderer *renderer, SDL_Window *window, SDL_Texture *texture);
void render_enemies(SDL_Renderer *renderer, Enemy enemies[], int num_enemies);
void render_texture(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *src, SDL_Rect *dst);

void draw_walls(SDL_Renderer *renderer, int map[MAP_WIDTH][MAP_HEIGHT], double posX, double posY, double dirX, double dirY, double planeX, double planeY);
void calculate_step_direction(double rayDirX, double rayDirY, double posX, double posY, int *mapX, int *mapY, double *sideDistX, double *sideDistY, double deltaDistX, double deltaDistY, int *stepX, int *stepY);
void perform_dda(int map[MAP_WIDTH][MAP_HEIGHT], int *mapX, int *mapY, double *sideDistX, double *sideDistY, double deltaDistX, double deltaDistY, int *stepX, int *stepY, int *hit, int *side);
void set_wall_color(SDL_Renderer *renderer, int side);

#endif /* MAZE_H */

