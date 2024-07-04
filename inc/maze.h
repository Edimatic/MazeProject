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
void init_map(int map[MAP_WIDTH][MAP_HEIGHT]);

void close_sdl(SDL_Window *window, SDL_Renderer *renderer);

int init_sdl(SDL_Window **window, SDL_Renderer **renderer);

void draw_walls(SDL_Renderer *renderer, int map[MAP_WIDTH][MAP_HEIGHT], double posX, double posY, double dirX, double dirY, double planeX, double planeY);

void move_forward(double *posX, double *posY, double dirX, double dirY, double moveSpeed, int map[MAP_WIDTH][MAP_HEIGHT]);

void move_backward(double *posX, double *posY, double dirX, double dirY, double moveSpeed, int map[MAP_WIDTH][MAP_HEIGHT]);

void strafe_left(double *posX, double *posY, double planeX, double planeY, double moveSpeed, int map[MAP_WIDTH][MAP_HEIGHT]);

void strafe_right(double *posX, double *posY, double planeX, double planeY, double moveSpeed, int map[MAP_WIDTH][MAP_HEIGHT]);

SDL_Texture* load_texture(SDL_Renderer *renderer, const char *file_path);

void render_texture(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *srcRect, SDL_Rect *destRect);

void process_input(SDL_Event *event, int *running, double *posX, double *posY,
                   double *dirX, double *dirY, double *planeX, double *planeY,
                   double moveSpeed, double rotSpeed, int map[MAP_WIDTH][MAP_HEIGHT]);

void move_left(double *posX, double *posY, double dirX, double dirY, double planeX, double planeY, double moveSpeed, int map[MAP_WIDTH][MAP_HEIGHT]);

void move_right(double *posX, double *posY, double dirX, double dirY, double planeX, double planeY, double moveSpeed, int map[MAP_WIDTH][MAP_HEIGHT]);

/* Rotation functions */
void rotate_left(double *dirX, double *dirY, double *planeX, double *planeY, double rotSpeed);
void rotate_right(double *dirX, double *dirY, double *planeX, double *planeY, double rotSpeed);

void handle_events(SDL_Event *event, int *running, double *posX, double *posY, double *dirX, double *dirY, double *planeX, double *planeY, double moveSpeed, double rotSpeed, int map[MAP_WIDTH][MAP_HEIGHT]);

/* Weapon functions */
SDL_Texture* load_weapon_texture(SDL_Renderer *renderer, const char *file_path);

void render_weapon(SDL_Renderer *renderer, SDL_Window *window, SDL_Texture *weapon_texture);

/*enemies */
void render_enemies(SDL_Renderer *renderer, Enemy enemies[], int num_enemies);
void move_enemies(Enemy enemies[], int num_enemies, int map[MAP_WIDTH][MAP_HEIGHT]);
int check_collision(double x1, double y1, double x2, double y2, double radius);
void init_enemies(Enemy enemies[], int num_enemies, SDL_Renderer *renderer);

/* Rain */
void init_rain();
void update_raindrops();
void render_rain(SDL_Renderer *renderer);

 void toggle_rain();
int is_raining();

#endif /* MAZE_H */

