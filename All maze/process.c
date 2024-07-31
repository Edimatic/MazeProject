#include "maze.h"

/**
 * process_input - Process SDL events and handle input
 * @event: SDL event
 * @running: Pointer to running flag
 * @posX: Pointer to player's x position
 * @posY: Pointer to player's y position
 * @dirX: Pointer to player's direction x
 * @dirY: Pointer to player's direction y
 * @planeX: Pointer to camera plane x
 * @planeY: Pointer to camera plane y
 * @moveSpeed: Move speed
 * @rotSpeed: Rotation speed
 * @map: The game map
 */
void process_input(SDL_Event *event, int *running, double *posX,
double *posY, double *dirX, double *dirY, double *planeX, double *planeY,
double moveSpeed, double rotSpeed, int map[MAP_WIDTH][MAP_HEIGHT])
{
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	while (SDL_PollEvent(event))
	{
	if (event->type == SDL_QUIT)
	{
	*running = 0;
	}
	}

	if (state[SDL_SCANCODE_W])
	{
	move_forward(posX, posY, *dirX, *dirY, moveSpeed, map);
	}
	if (state[SDL_SCANCODE_S])
	{
	move_backward(posX, posY, *dirX, *dirY, moveSpeed, map);
	}
	if (state[SDL_SCANCODE_A])
	{
	move_left(posX, posY, *dirX, *dirY, *planeX, *planeY, moveSpeed, map);
	}
	if (state[SDL_SCANCODE_D])
	{
	move_right(posX, posY, *dirX, *dirY, *planeX, *planeY, moveSpeed, map);
	}
	if (state[SDL_SCANCODE_LEFT])
	{
	rotate_left(dirX, dirY, planeX, planeY, rotSpeed);
}
	if (state[SDL_SCANCODE_RIGHT])
	{
	rotate_right(dirX, dirY, planeX, planeY, rotSpeed);
	}
}
