#include "maze.h"
#include <stdlib.h>

/**
 * init_enemies - Initializes enemy positions and properties
 * @enemies: Array of Enemy structures
 * @num_enemies: Number of enemies to initialize
 * @renderer: SDL_Renderer for loading enemy textures
 */
void init_enemies(Enemy enemies[], int num_enemies, SDL_Renderer *renderer)
{
	for (int i = 0; i < num_enemies; i++)
	{
	enemies[i].x = rand() % MAP_WIDTH;
	enemies[i].y = rand() % MAP_HEIGHT;
	enemies[i].dirX = 0;
	enemies[i].dirY = 0;
	enemies[i].texture = load_texture(renderer, "enemy_texture.png");
	}
}

/**
 * render_enemies - Renders enemies on the screen
 * @renderer: SDL_Renderer to draw enemies on
 * @enemies: Array of Enemy structures
 * @num_enemies: Number of enemies to render
 */
void render_enemies(SDL_Renderer *renderer, Enemy enemies[], int num_enemies)
{
	for (int i = 0; i < num_enemies; i++)
	{
	SDL_Rect dest = {(int)(enemies[i].x * TILE_SIZE),
	(int)(enemies[i].y * TILE_SIZE), TILE_SIZE, TILE_SIZE};
	SDL_RenderCopy(renderer, enemies[i].texture, NULL, &dest);
	}
}

/**
 * move_enemies - Moves enemies and checks for wall collisions
 * @enemies: Array of Enemy structures
 * @num_enemies: Number of enemies to move
 * @map: 2D array representing the map with walls
 */
void move_enemies(Enemy enemies[], int num_enemies,
	int map[MAP_WIDTH][MAP_HEIGHT])
{
	for (int i = 0; i < num_enemies; i++)
	{
	enemies[i].x += enemies[i].dirX;
	enemies[i].y += enemies[i].dirY;
	/* Collision detection with walls */
	if (map[(int)enemies[i].x][(int)enemies[i].y] > 0)
	{
	enemies[i].x -= enemies[i].dirX;
	enemies[i].y -= enemies[i].dirY;
		}
	}
}

/**
 * check_collision - Checks if two points are within a certain radius
 * @x1: X-coordinate of the first point
 * @y1: Y-coordinate of the first point
 * @x2: X-coordinate of the second point
 * @y2: Y-coordinate of the second point
 * @radius: Collision radius
 *
 * Return: 1 if points are within radius, 0 otherwise
 */
int check_collision(double x1, double y1, double x2, double y2, double radius)
{
	double distX = x1 - x2;
	double distY = y1 - y2;
	double distance = sqrt(distX * distX + distY * distY);

	return (distance < radius);
}
