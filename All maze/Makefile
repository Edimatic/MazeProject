CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic
LIBS = -lSDL2 -lSDL2_image -lm
SRCS = main.c init_sdl.c close_sdl.c map.c movement.c raycasting.c rotation.c textures.c weapon.c enemy.c rain.c
OBJS = $(SRCS:.c=.o)
TARGET = maze

# List of PNG files
PNG_FILES = wall_texture.png floor_texture.png ceiling_texture.png wall_texture_2.png \
            weapon.png enemy_texture1.png enemy_texture2.png

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

# Target to copy PNG files to the executable directory
copy_png_files:
	cp $(PNG_FILES) ./   # Adjust this if PNG files are in a different directory

