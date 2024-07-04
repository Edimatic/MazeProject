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
	SDL_Texture *textures[NUM_TEXTURES];
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

/* Add more enemies as needed */
};
	int num_enemies = sizeof(enemies) / sizeof(enemies[0]);

	int running = 1;
	SDL_Event event;
	const Uint8 *keystate;
	double moveSpeed = 0.1;
	double rotSpeed = 0.05;
	double posX = 22.0, posY = 12.0;  /* Player start position */
	double dirX = -1.0, dirY = 0.0;   /* Initial direction vector */
	double planeX = 0.0, planeY = 0.66; /* Camera plane */

/* Example map */
	int map[MAP_WIDTH][MAP_HEIGHT] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
/* Add more rows as needed */
};

/* Initialize rain */
init_rain();

	while (running)
	{
while (SDL_PollEvent(&event))
	{
	    if (event.type == SDL_QUIT)
	{
		running = (0);
	}
	else if (event.type == SDL_KEYDOWN)
	{
	if (event.key.keysym.sym == SDLK_ESCAPE)
	{
	running = 0; /* Quit on ESC key */
	}
	if (event.key.keysym.sym == SDLK_r)
	{
	toggle_rain(); /* Toggle rain on/off with 'R' key */
		}
	}
}

	keystate = SDL_GetKeyboardState(NULL);

	if (keystate[SDL_SCANCODE_W])
		move_forward(&posX, &posY, dirX, dirY, moveSpeed, map);
	if (keystate[SDL_SCANCODE_S])
		move_backward(&posX, &posY, dirX, dirY, moveSpeed, map);
	if (keystate[SDL_SCANCODE_A])
		strafe_left(&posX, &posY, planeX, planeY, moveSpeed, map);
	if (keystate[SDL_SCANCODE_D])
		strafe_right(&posX, &posY, planeX, planeY, moveSpeed, map);
	if (keystate[SDL_SCANCODE_LEFT])
	{
		double oldDirX = dirX;
		dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
		dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
		double oldPlaneX = planeX;
		planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
		planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
}
	if (keystate[SDL_SCANCODE_RIGHT])
	{
		double oldDirX = dirX;
	dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
	dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
	double oldPlaneX = planeX;
	planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
	planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
	}

	/* Update raindrops if it's raining */
	if (is_raining())
	{
		update_raindrops();
	}

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

/* Clean up resources */
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
