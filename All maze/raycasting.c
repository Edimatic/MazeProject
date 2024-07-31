#include "maze.h"

/**
 * draw_walls - Draws the walls of the maze using raycasting
 * @renderer: The SDL_Renderer to use
 * @map: The map of the maze
 * @posX: The player's X position
 * @posY: The player's Y position
 * @dirX: The player's direction vector X
 * @dirY: The player's direction vector Y
 * @planeX: The camera plane X
 * @planeY: The camera plane Y
 */
void draw_walls(SDL_Renderer *renderer, int map[MAP_WIDTH][MAP_HEIGHT],
double posX, double posY, double dirX, double dirY, double planeX,
double planeY)
{
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
	double cameraX = 2 * x / (double)SCREEN_WIDTH - 1;/*x-coordinate in camera*/
	double rayDirX = dirX + planeX * cameraX;
	double rayDirY = dirY + planeY * cameraX;
	int mapX = (int)posX;
	int mapY = (int)posY;
/* Length of ray from current position to next x or y-side */
	double sideDistX;
	double sideDistY;
	double deltaDistX = fabs(1 / rayDirX);
	double deltaDistY = fabs(1 / rayDirY);
	double perpWallDist;
	int stepX;
	int stepY;
	int hit = 0; /* was there a wall hit? */
	int side; /* was a NS or a EW wall hit? */

calculate_step_direction(rayDirX, rayDirY, posX, posY, &mapX, &mapY,
&sideDistX, &sideDistY, deltaDistX, deltaDistY, &stepX, &stepY);
perform_dda(map, &mapX, &mapY, &sideDistX, &sideDistY, deltaDistX,
deltaDistY, &stepX, &stepY, &hit, &side);
/* Calculate distance projected on camera direction */
	if (side == 0)
		perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
	else
		perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;
	int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);
/* Calculate lowest and highest pixel to fill in current stripe */
	int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;

	if (drawStart < 0)
		drawStart = 0;
	int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;

	if (drawEnd >= SCREEN_HEIGHT)
		drawEnd = SCREEN_HEIGHT - 1;
	set_wall_color(renderer, side);
	SDL_RenderDrawLine(renderer, x, drawStart, x, drawEnd);
	}
}


/**
 * calculate_step_direction - Calculates step and initial sideDist values
 * @rayDirX: Ray direction X
 * @rayDirY: Ray direction Y
 * @posX: Player's X position
 * @posY: Player's Y position
 * @mapX: Map X position
 * @mapY: Map Y position
 * @sideDistX: Initial side distance X
 * @sideDistY: Initial side distance Y
 * @deltaDistX: Distance between x-sides
 * @deltaDistY: Distance between y-sides
 * @stepX: Step direction X
 * @stepY: Step direction Y
 */

void calculate_step_direction(double rayDirX, double rayDirY,
double posX, double posY, int *mapX, int *mapY, double *sideDistX,
double *sideDistY, double deltaDistX, double deltaDistY, int *stepX,
int *stepY)
{
	if (rayDirX < 0)
	{
	*stepX = -1;
	*sideDistX = (posX - *mapX) * deltaDistX;
	}
	else
	{
	*stepX = 1;
	*sideDistX = (*mapX + 1.0 - posX) * deltaDistX;
	}
	if (rayDirY < 0)
	{
	*stepY = -1;
	*sideDistY = (posY - *mapY) * deltaDistY;
	}
	else
	{
	*stepY = 1;
	*sideDistY = (*mapY + 1.0 - posY) * deltaDistY;
	}
}

/**
 * perform_dda - Performs Digital Differential Analysis (DDA) algorithm
 * @map: The map of the maze
 * @mapX: Map X position
 * @mapY: Map Y position
 * @sideDistX: Initial side distance X
 * @sideDistY: Initial side distance Y
 * @deltaDistX: Distance between x-sides
 * @deltaDistY: Distance between y-sides
 * @stepX: Step direction X
 * @stepY: Step direction Y
 * @hit: Pointer to hit flag
 * @side: Pointer to side flag
 */

void perform_dda(int map[MAP_WIDTH][MAP_HEIGHT], int *mapX,
int *mapY, double *sideDistX, double *sideDistY, double deltaDistX,
double deltaDistY, int *stepX, int *stepY, int *hit, int *side)
{
	while (*hit == 0)
	{
/* Jump to next map square, OR in x-direction, OR in y-direction */
	if (*sideDistX < *sideDistY)
	{
	*sideDistX += deltaDistX;
	*mapX += *stepX;
	*side = 0;
	}
	else
	{
		*sideDistY += deltaDistY;
		*mapY += *stepY;
		*side = 1;
	}
/* Check if ray has hit a wall */
	if (map[*mapX][*mapY] > 0)
	*hit = 1;
	}
}


/**
 * set_wall_color - Sets the color of the wall based on its side
 * @renderer: The SDL_Renderer to use
 * @side: The side of the wall (0 for NS, 1 for EW)
 */

void set_wall_color(SDL_Renderer *renderer, int side)
{
	if (side == 0)
	{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); /* Red for NS walls */
	}
	else
{
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); /* Green for EW walls */
	}
}
