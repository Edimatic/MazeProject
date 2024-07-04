#include "maze.h"

/**
 * close_sdl - Destroys the SDL window and renderer and quits SDL
 * @window: The SDL_Window to destroy
 * @renderer: The SDL_Renderer to destroy
 */
void close_sdl(SDL_Window *window, SDL_Renderer *renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

