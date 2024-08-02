#include "maze.h"

/**
 * main - Entry point of the Maze project
 *
 * Return: 0 on success, 1 on error
 */
int main(void)
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture * textures[NUM_TEXTURES];
	SDL_Texture *weapon_texture;

	if (init_sdl(&window, &renderer) != 0)
	{
		return (1);
}
/* Load the weapon texture */
	weapon_texture = load_weapon_texture(renderer, "weapon.png");
	if (!weapon_texture)
	{
	close_sdl(window, renderer);
		return (1);
}
	textures[0] = load_texture(renderer, "wall_texture.png");
	textures[1] = load_texture(renderer, "floor_texture.png");
	textures[2] = load_texture(renderer, "ceiling_texture.png");
	textures[3] = load_texture(renderer, "wall_texture_2.png");
	if (!textures[0] || !textures[1] || !textures[2] || !textures[3])
	{
	close_sdl(window, renderer);
		return (1);
}
/* Example enemies */
	Enemy enemies[] = {
	{10.0, 10.0, 0.0, 0.0, load_texture(renderer, "enemy_texture1.png")},
	{15.0, 5.0, 0.0, 0.0, load_texture(renderer, "enemy_texture2.png")}
	};
	int num_enemies = sizeof(enemies) / sizeof(enemies[0]);
	int running = 1;
	const Uint8 *keystate;
	double moveSpeed = 0.1;
	double rotSpeed = 0.05;
	double posX = 22.0, posY = 12.0;  /* Player start position */
	double dirX = -1.0, dirY = 0.0;  /* Initial direction vector */
	double planeX = 0.0, planeY = 0.66;  /* Camera plane */
/* Example map */
	int map[MAP_WIDTH][MAP_HEIGHT] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};
/* Initialize rain */
	init_rain();
	SDL_Event event;
while (running)
	{
handle_events(&event, &running, &posX, &posY, &dirX, &dirY, &planeX, &planeY,
moveSpeed, rotSpeed, map);
	keystate = SDL_GetKeyboardState(NULL);
update_position(keystate, &posX, &posY, &dirX, &dirY, &planeX,
&planeY, map, moveSpeed, rotSpeed);
/* Update raindrops if it's raining */
	if (is_raining())
	{
		update_raindrops();
	}
render_scene(renderer, textures, weapon_texture, window, enemies,
num_enemies, posX, posY, dirX, dirY, planeX, planeY, map);
	}
/* Cleanup */
	for (int i = 0; i < NUM_TEXTURES; ++i)
	{
	SDL_DestroyTexture(textures[i]);
	}
	for (int i = 0; i < num_enemies; ++i)
	{
	SDL_DestroyTexture(enemies[i].texture);
	}
	SDL_DestroyTexture(weapon_texture);
	close_sdl(window, renderer);
	return (0);
}

/**
 * handle_events - Handles SDL events and updates game state
 * @event: SDL_Event structure pointer
 * @running: Pointer to the running flag
 * @posX: Pointer to player's X position
 * @posY: Pointer to player's Y position
 * @dirX: Pointer to player's direction vector X
 * @dirY: Pointer to player's direction vector Y
 * @planeX: Pointer to camera plane X
 * @planeY: Pointer to camera plane Y
 * @moveSpeed: Movement speed
 * @rotSpeed: Rotation speed
 * @map: Game map
 *
 * Return: void
 */
void handle_events(SDL_Event *event, int *running, double *posX, double *posY,
double *dirX, double *dirY, double *planeX, double *planeY, double moveSpeed,
double rotSpeed, int map[MAP_WIDTH][MAP_HEIGHT])
{
/* Marking parameters as unused */
	(void)posX;
	(void)posY;
	(void)dirX;
	(void)dirY;
	(void)planeX;
	(void)planeY;
	(void)moveSpeed;
	(void)rotSpeed;
	(void)map;

	while (SDL_PollEvent(event))
	{
	if (event->type == SDL_QUIT)
	{
	*running = 0;
	}
	else if (event->type == SDL_KEYDOWN)
	{
	if (event->key.keysym.sym == SDLK_ESCAPE)
	{
	*running = 0; /* Quit on ESC key */
		}
	if (event->key.keysym.sym == SDLK_r)
		{
		toggle_rain(); /* Toggle rain on/off with 'R' key */
			}
		}
	}
}

/**
 * update_position - Updates player's position and direction based on input
 * @keystate: SDL keyboard state
 * @posX: Pointer to player's X position
 * @posY: Pointer to player's Y position
 * @dirX: Pointer to player's direction vector X
 * @dirY: Pointer to player's direction vector Y
 * @planeX: Pointer to camera plane X
 * @planeY: Pointer to camera plane Y
 * @map: Game map
 * @moveSpeed: Movement speed
 * @rotSpeed: Rotation speed
 *
 * Return: void
 */
void update_position(const Uint8 *keystate, double *posX, double *posY,
double *dirX, double *dirY, double *planeX, double *planeY,
int map[MAP_WIDTH][MAP_HEIGHT], double moveSpeed, double rotSpeed)
{
	if (keystate[SDL_SCANCODE_W])
	{
	move_forward(posX, posY, *dirX, *dirY, moveSpeed, map);
	}
	if (keystate[SDL_SCANCODE_S])
	{
	move_backward(posX, posY, *dirX, *dirY, moveSpeed, map);
	}
	if (keystate[SDL_SCANCODE_A])
	{
	strafe_left(posX, posY, *planeX, *planeY, moveSpeed, map);
	}
	if (keystate[SDL_SCANCODE_D])
	{
	strafe_right(posX, posY, *planeX, *planeY, moveSpeed, map);
	}
	if (keystate[SDL_SCANCODE_LEFT])
	{
	double oldDirX = *dirX;
	*dirX = *dirX * cos(rotSpeed) - *dirY * sin(rotSpeed);
	*dirY = oldDirX * sin(rotSpeed) + *dirY * cos(rotSpeed);
	double oldPlaneX = *planeX;
	*planeX = *planeX * cos(rotSpeed) - *planeY * sin(rotSpeed);
	*planeY = oldPlaneX * sin(rotSpeed) + *planeY * cos(rotSpeed);
	}
	if (keystate[SDL_SCANCODE_RIGHT])
	{
	double oldDirX = *dirX;
	*dirX = *dirX * cos(-rotSpeed) - *dirY * sin(-rotSpeed);
	*dirY = oldDirX * sin(-rotSpeed) + *dirY * cos(-rotSpeed);
	double oldPlaneX = *planeX;
	*planeX = *planeX * cos(-rotSpeed) - *planeY * sin(-rotSpeed);
	*planeY = oldPlaneX * sin(-rotSpeed) + *planeY * cos(-rotSpeed);
	}
}

/**
 * render_scene - Renders the game scene
 * @renderer: SDL_Renderer pointer
 * @textures: Array of textures
 * @weapon_texture: Texture for the weapon
 * @window: SDL_Window pointer
 * @enemies: Array of enemies
 * @num_enemies: Number of enemies
 * @posX: Player's X position
 * @posY: Player's Y position
 * @dirX: Player's direction vector X
 * @dirY: Player's direction vector Y
 * @planeX: Camera plane X
 * @planeY: Camera plane Y
 * @map: Game map
 *
 * Return: void
 */

void render_scene(SDL_Renderer *renderer, SDL_Texture *textures[],
SDL_Texture *weapon_texture, SDL_Window *window, Enemy enemies[],
int num_enemies, double posX, double posY, double dirX, double dirY,
double planeX, double planeY, int map[MAP_WIDTH][MAP_HEIGHT])
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_Rect floorRect = {0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2};

	render_texture(renderer, textures[1], NULL, &floorRect);
	SDL_Rect ceilRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT / 2};

	render_texture(renderer, textures[2], NULL, &ceilRect);
	draw_walls(renderer, map, posX, posY, dirX, dirY, planeX, planeY);

/* Render raindrops if it's raining */
	if (is_raining())
	{
	render_rain(renderer);
	}
	render_weapon(renderer, window, weapon_texture);
	render_enemies(renderer, enemies, num_enemies);

	SDL_RenderPresent(renderer);
}
