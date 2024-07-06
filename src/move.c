#include "maze.h"

/**
 * move_left - Moves the player left while handling wall collisions
 * @posX: Pointer to the player's x position
 * @posY: Pointer to the player's y position
 * @dirX: Player's direction x component
 * @dirY: Player's direction y component
 * @planeX: Player's plane x component
 * @planeY: Player's plane y component
 * @moveSpeed: Speed of the player's movement
 * @map: The game map
 */
void move_left(double *posX, double *posY, double dirX,
double dirY, double planeX, double planeY, double moveSpeed,
int map[MAP_WIDTH][MAP_HEIGHT])
{

	(void)dirX;
	(void)dirY;

	double newX = *posX - planeX * moveSpeed;
	double newY = *posY - planeY * moveSpeed;

	if (map[(int)newX][(int)*posY] == 0)
	*posX = newX;
	if (map[(int)*posX][(int)newY] == 0)
	*posY = newY;
}

/**
 * move_right - Moves the player right while handling wall collisions
 * @posX: Pointer to the player's x position
 * @posY: Pointer to the player's y position
 * @dirX: Player's direction x component
 * @dirY: Player's direction y component
 * @planeX: Player's plane x component
 * @planeY: Player's plane y component
 * @moveSpeed: Speed of the player's movement
 * @map: The game map
 */
void move_right(double *posX, double *posY, double dirX, double dirY,
double planeX, double planeY, double moveSpeed,
int map[MAP_WIDTH][MAP_HEIGHT])
{

	(void)dirX;
	(void)dirY;

	double newX = *posX + planeX * moveSpeed;
	double newY = *posY + planeY * moveSpeed;

	if (map[(int)newX][(int)*posY] == 0)
	*posX = newX;
	if (map[(int)*posX][(int)newY] == 0)
	*posY = newY;
}

