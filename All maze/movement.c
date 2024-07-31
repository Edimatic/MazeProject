#include "maze.h"

/**
 * move_forward - Moves the player forward if no collision
 * @posX: Pointer to player's X position
 * @posY: Pointer to player's Y position
 * @dirX: Direction vector X component
 * @dirY: Direction vector Y component
 * @moveSpeed: Movement speed
 * @map: The game map
 */
void move_forward(double *posX, double *posY, double dirX,
double dirY, double moveSpeed, int map[MAP_WIDTH][MAP_HEIGHT])
{

	double newX = *posX + dirX * moveSpeed;
	double newY = *posY + dirY * moveSpeed;

	if (map[(int)(newX)][(int)(*posY)] == 0)
	*posX = newX;
	if (map[(int)(*posX)][(int)(newY)] == 0)
	*posY = newY;
}

/**
 * move_backward - Moves the player backward if no collision
 * @posX: Pointer to player's X position
 * @posY: Pointer to player's Y position
 * @dirX: Direction vector X component
 * @dirY: Direction vector Y component
 * @moveSpeed: Movement speed
 * @map: The game map
 */
void move_backward(double *posX, double *posY, double dirX,
double dirY, double moveSpeed, int map[MAP_WIDTH][MAP_HEIGHT])
{

	double newX = *posX - dirX * moveSpeed;
	double newY = *posY - dirY * moveSpeed;

	if (map[(int)(newX)][(int)(*posY)] == 0)
	*posX = newX;
	if (map[(int)(*posX)][(int)(newY)] == 0)
	*posY = newY;
}

/**
 * strafe_left - Moves the player to the left if no collision
 * @posX: Pointer to player's X position
 * @posY: Pointer to player's Y position
 * @planeX: Camera plane X component
 * @planeY: Camera plane Y component
 * @moveSpeed: Movement speed
 * @map: The game map
 */
void strafe_left(double *posX, double *posY, double planeX, double planeY,
double moveSpeed, int map[MAP_WIDTH][MAP_HEIGHT])
{

	double newX = *posX - planeX * moveSpeed;
	double newY = *posY - planeY * moveSpeed;

	if (map[(int)(newX)][(int)(*posY)] == 0)
	*posX = newX;
	if (map[(int)(*posX)][(int)(newY)] == 0)
	*posY = newY;
}

/**
 * strafe_right - Moves the player to the right if no collision
 * @posX: Pointer to player's X position
 * @posY: Pointer to player's Y position
 * @planeX: Camera plane X component
 * @planeY: Camera plane Y component
 * @moveSpeed: Movement speed
 * @map: The game map
 */
void strafe_right(double *posX, double *posY, double planeX,
double planeY, double moveSpeed, int map[MAP_WIDTH][MAP_HEIGHT])
{

	double newX = *posX + planeX * moveSpeed;
	double newY = *posY + planeY * moveSpeed;

	if (map[(int)(newX)][(int)(*posY)] == 0)
	*posX = newX;
	if (map[(int)(*posX)][(int)(newY)] == 0)
	*posY = newY;
}
