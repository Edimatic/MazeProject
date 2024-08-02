#include "maze.h"
#include <stdio.h>

/**
 * init_sdl - Initializes SDL and creates a window and renderer
 * @window: Pointer to the SDL_Window
 * @renderer: Pointer to the SDL_Renderer
 *
 * Return: 0 on success, 1 on error
 */
int init_sdl(SDL_Window **window, SDL_Renderer **renderer)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
{
	printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	return (1);
	}

	*window = SDL_CreateWindow("Maze Project",
	SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED,
	SCREEN_WIDTH, SCREEN_HEIGHT,
	SDL_WINDOW_SHOWN);
	if (*window == NULL)
	{
	printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
	SDL_Quit();
return (1);
}

	*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
	if (*renderer == NULL)
	{
	printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
	SDL_DestroyWindow(*window);
	SDL_Quit();
	return (1);
	}

return (0);
}

