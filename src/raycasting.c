#include "maze.h"

/**
 * draw_walls - Draws walls using raycasting
 * @renderer: SDL renderer
 * @map: 2D map array
 * @posX: Player X position
 * @posY: Player Y position
 * @dirX: Player direction vector X
 * @dirY: Player direction vector Y
 * @planeX: Camera plane X
 * @planeY: Camera plane Y
 * @textures: Array of wall textures
 */
#include "maze.h"

void draw_walls(SDL_Renderer *renderer, int map[MAP_WIDTH][MAP_HEIGHT],
double posX, double posY, double dirX, double dirY, double planeX,
double planeY)
{
for (int x = 0; x < SCREEN_WIDTH; x++)
	{
/* Calculate ray position and direction */
double cameraX = 2 * x / (double)SCREEN_WIDTH - 1; /*x-coordinate in camera*/
	double rayDirX = dirX + planeX * cameraX;
	double rayDirY = dirY + planeY * cameraX;

/* Which box of the map we're in */
	int mapX = (int)posX;
	int mapY = (int)posY;

/* Length of ray from current position to next x or y-side */
	double sideDistX;
	double sideDistY;

/* Length of ray from one x or y-side to next x or y-side */
	double deltaDistX = fabs(1 / rayDirX);
	double deltaDistY = fabs(1 / rayDirY);
	double perpWallDist;

/* Direction to go in x and y */
	int stepX;
	int stepY;

	int hit = 0; /* Was there a wall hit? */
	int side; /* Was a NS or a EW wall hit? */

/* Calculate step and initial sideDist */
	if (rayDirX < 0)
	{
	stepX = -1;
	sideDistX = (posX - mapX) * deltaDistX;
	}
	else
	{
	stepX = 1;
		sideDistX = (mapX + 1.0 - posX) * deltaDistX;
	}
	if (rayDirY < 0)
	{
	stepY = -1;
	sideDistY = (posY - mapY) * deltaDistY;
	}
	else
	{
	stepY = 1;
	sideDistY = (mapY + 1.0 - posY) * deltaDistY;
	}

/* Perform DDA */
	while (hit == 0)
	{
/* Jump to next map square, OR in x-direction, OR in y-direction */
	if (sideDistX < sideDistY)
	{
		sideDistX += deltaDistX;
	mapX += stepX;
		side = 0;
	}
	else
	{
	sideDistY += deltaDistY;
	mapY += stepY;
		side = 1;
	}
/* Check if ray has hit a wall */
	if (map[mapX][mapY] > 0)
	hit = 1;
	}

/* Calculate distance projected on camera direction */
/*(Euclidean distance will give fisheye effect!) */

	if (side == 0)
	perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
	else
		perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

/* Calculate height of line to draw on screen */
	int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

/* Calculate lowest and highest pixel to fill in current stripe */
	int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;

	if (drawStart < 0)
	drawStart = 0;
	int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;

	if (drawEnd >= SCREEN_HEIGHT)
	drawEnd = SCREEN_HEIGHT - 1;

/* Choose wall color */
	SDL_Color wallColor;

	if (side == 0) /* North-South wall */
	{
	wallColor.r = 255;
	wallColor.g = 0;
	wallColor.b = 0;
	}
		else /* East-West wall*/
	{
		wallColor.r = 0;
		wallColor.g = 0;
		wallColor.b = 255;
	}

/* Set the color and draw the vertical stripe */
SDL_SetRenderDrawColor(renderer, wallColor.r, wallColor.g, wallColor.b, 255);
	SDL_RenderDrawLine(renderer, x, drawStart, x, drawEnd);
	}
}
