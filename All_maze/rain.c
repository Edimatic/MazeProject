#include "maze.h"

Raindrop raindrops[MAX_RAIN_DROPS];
double raindropSpeed = 1.0; /*Adjust speed as needed*/

/**
 * init_rain - Initializes raindrop positions and properties
 */
void init_rain(void)
{
for (int i = 0; i < MAX_RAIN_DROPS; ++i)
{
	raindrops[i].x = rand() % SCREEN_WIDTH;
	raindrops[i].y = -(rand() % SCREEN_HEIGHT); /* Start raindrops off-screen*/
	raindrops[i].speed = raindropSpeed;
	raindrops[i].visible = 1; /* Initially visible */
	}
}

/**
 * update_raindrops - Updates raindrop positions based on speed
 */
void update_raindrops(void)
{

for (int i = 0; i < MAX_RAIN_DROPS; ++i)
	{
	if (raindrops[i].visible)
	{
	raindrops[i].y += raindrops[i].speed;
	if (raindrops[i].y > SCREEN_HEIGHT)
	{
	raindrops[i].y = -(rand() % SCREEN_HEIGHT); /*Reset raindrop position*/
			}
		}
	}
}

/**
 * render_rain - Renders raindrops on the screen
 * @renderer: SDL_Renderer to draw raindrops on
 */
void render_rain(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255); /*Set raindrop color*/

	for (int i = 0; i < MAX_RAIN_DROPS; ++i)
	{
	if (raindrops[i].visible)
	{
	SDL_RenderDrawLine(renderer, (int)raindrops[i].x, (int)raindrops[i].y,
	(int)raindrops[i].x, (int)raindrops[i].y + 10); /* Adjust raindrops*/
		}
	}
}

static int raining = 1; /* Flag to track rain state */

/**
 * toggle_rain - Toggles the rain state
 */
void toggle_rain(void)
{
	raining = !raining; /*Toggle the rain flag*/
}

/**
 * is_raining - Checks if it's currently raining
 *
 * Return: 1 if raining, 0 otherwise
 */
int is_raining(void)
{
	return (raining); /* Return the current state of rain */
}

