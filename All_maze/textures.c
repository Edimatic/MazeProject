#include "maze.h"

/**
 * load_texture - Loads a texture from a file
 * @renderer: SDL renderer
 * @file: File path to the image
 *
 * Return: SDL_Texture* on success, NULL on failure
 */

SDL_Texture *load_texture(SDL_Renderer *renderer, const char *file)
{
	SDL_Surface *surface = IMG_Load(file);

	if (!surface)
	{
	printf("Failed to load texture %s: %s\n", file, IMG_GetError());
return (NULL);
	}
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);

	if (!texture)
	{
	printf("Failed to create texture from %s: %s\n", file, SDL_GetError());
return (NULL);
}
return (texture);
}

void render_texture(SDL_Renderer *renderer, SDL_Texture *texture,
SDL_Rect *srcRect, SDL_Rect *destRect)
{
	SDL_RenderCopy(renderer, texture, srcRect, destRect);
}
