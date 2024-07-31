#include "maze.h"

/**
 * load_weapon_texture - Load the weapon texture from a file
 * @renderer: The SDL renderer
 * @file_path: The file path to the weapon texture
 *
 * Return: A pointer to the SDL texture, or NULL on failure
 */
SDL_Texture *load_weapon_texture(SDL_Renderer *renderer,
const char *file_path)
{
	SDL_Texture *texture = IMG_LoadTexture(renderer, file_path);

	if (!texture)
	{
		printf("Failed to load texture: %s\n", IMG_GetError());
	}
	return (texture);
}

/**
 * render_weapon - Render the weapon texture on the screen
 * @renderer: The SDL renderer
 * @window: The SDL window
 * @weapon_texture: The SDL texture for the weapon
 */
void render_weapon(SDL_Renderer *renderer, SDL_Window *window,
SDL_Texture *weapon_texture)
{
	int w, h;

	SDL_GetWindowSize(window, &w, &h);
	int weapon_w = w / 4;
	int weapon_h = h / 4;

SDL_Rect dstrect = { w / 2 - weapon_w / 2, h - weapon_h, weapon_w, weapon_h };
SDL_RenderCopy(renderer, weapon_texture, NULL, &dstrect);
}

