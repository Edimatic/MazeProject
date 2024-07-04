#	Maze Game Project

#	Overview

This project is a 3D Maze Game implemented in C using the SDL2 library for rendering. The game features a raycasting engine to create a pseudo-3D first-person view, allowing the player to navigate through a maze. This project adheres to the "BETTY" coding style and includes various features such as player movement, maze rotation, and weapon textures.

#	Features

    Raycasting Engine: Utilizes a raycasting technique to render a 3D view from a 2D map.
    Player Movement: Allows the player to move forward, backward, and rotate left and right.
    Weapon Textures: Includes weapon textures that are displayed on the screen.
    Modular Code Structure: Organized code with a maximum of five functions per file and all function declarations in the maze.h header file.
    Error Handling: Compiled with strict flags to ensure robust and error-free code.

##	Requirements

    SDL2 Library: Ensure SDL2 is installed on your system.
    Compiler: GCC or any compiler supporting C11 standard.

##	Compilation

To compile the project, use the following command:

gcc -Wall -Werror -Wextra -pedantic *.c -o maze -lSDL2 -lSDL2_image -lm

Ensure all source files and the header file maze.h are in the directory.


Usage

Run the compiled executable to start the game using "make"

sh

./maze

##	Controls

    W: Move forward
    S: Move backward
    A: Rotate left
    D: Rotate right

#	File Structure
    main.c: Contains the main game loop and initialization code.
    raycasting.c: Implements the raycasting algorithm.
    player_movement.c: Handles player movement logic.
    texture.c: Manages texture loading and rendering.
    rotation.c: Implements player rotation logic.
    maze.h: Header file containing function declarations and necessary includes.

	MazeProject/
├── inc/
│   └── maze.h
├── src/
│   ├── main.c
│   ├── movement.c
│   ├── textures.c
│   ├── close_sdl.c
│   ├── init_sdl.c
│   ├── process.c
│   ├── enemy.c
│   ├── map.c
│   ├── rain.c
│   ├── raycasting.c
│   ├── rotation.c
│   ├── weapon.c
│   ├── ceiling_texture.png
│   ├── floor_texture.png
│   ├── wall_texture.png
│   ├── enemy_texture1.png
│   ├── weapon.png
│   ├── enemy_texture2.png
├── Makefile
└── obj/
	

##	Coding Style

The project follows the "BETTY" coding style, ensuring consistency and readability. Key aspects include:

    Maximum of five functions per file: To maintain modularity and ease of understanding.
    Function declarations in maze.h: All functions used across multiple files are declared in maze.h.
    Strict compilation flags: -Wall -Werror -Wextra -pedantic flags are used to catch potential errors and enforce good coding practices.

Future Enhancements

    Enhanced Graphics: Improve the visual quality with more detailed textures and lighting effects.
    Advanced Maze Generation: Implement procedural maze generation algorithms for varied gameplay.
    AI Enemies: Add AI-controlled enemies to increase the game's challenge.
    Sound Effects: Incorporate sound effects and background music for an immersive experience.

##	Contributing

Contributions are welcome! Please fork the repository and create a pull request with your changes. Ensure your code adheres to the "BETTY" coding style and includes appropriate documentation.
License

This project is licensed under the MIT License. See the LICENSE file for details.

##	Acknowledgments

    SDL2: For providing the graphics and input handling library.
    Raycasting Tutorials: Various online resources and tutorials on raycasting that guided the development process.


Thank you for checking out the Maze Game project! Enjoy navigating the maze and defeating enemies.


