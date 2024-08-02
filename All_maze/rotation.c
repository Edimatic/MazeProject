#include "maze.h"
#include <math.h>

/**
 * rotate_left - Rotates the player's direction and camera plane to the left
 * @dirX: Pointer to the player's direction x component
 * @dirY: Pointer to the player's direction y component
 * @planeX: Pointer to the player's plane x component
 * @planeY: Pointer to the player's plane y component
 * @rotSpeed: Speed of the rotation
 */
void rotate_left(double *dirX, double *dirY, double *planeX,
double *planeY, double rotSpeed)
{
	double oldDirX = *dirX;
	*dirX = *dirX * cos(-rotSpeed) - *dirY * sin(-rotSpeed);
	*dirY = oldDirX * sin(-rotSpeed) + *dirY * cos(-rotSpeed);

	double oldPlaneX = *planeX;
	*planeX = *planeX * cos(-rotSpeed) - *planeY * sin(-rotSpeed);
	*planeY = oldPlaneX * sin(-rotSpeed) + *planeY * cos(-rotSpeed);
}

/**
 * rotate_right - Rotates the player's direction and camera plane to the right
 * @dirX: Pointer to the player's direction x component
 * @dirY: Pointer to the player's direction y component
 * @planeX: Pointer to the player's plane x component
 * @planeY: Pointer to the player's plane y component
 * @rotSpeed: Speed of the rotation
 */
void rotate_right(double *dirX, double *dirY, double *planeX,
double *planeY, double rotSpeed)
{
	double oldDirX = *dirX;
	*dirX = *dirX * cos(rotSpeed) - *dirY * sin(rotSpeed);
	*dirY = oldDirX * sin(rotSpeed) + *dirY * cos(rotSpeed);

	double oldPlaneX = *planeX;
	*planeX = *planeX * cos(rotSpeed) - *planeY * sin(rotSpeed);
	*planeY = oldPlaneX * sin(rotSpeed) + *planeY * cos(rotSpeed);
}

