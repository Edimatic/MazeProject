# Compiler and flags
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic
LDFLAGS = -lSDL2 -lSDL2_image -lm

# Directories
SRCDIR = src
INCDIR = inc
OBJDIR = obj

# Source and object files
SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# List of PNG files
PNG_FILES = wall_texture.png floor_texture.png ceiling_texture.png wall_texture_2.png \
            weapon.png enemy_texture1.png enemy_texture2.png

# Target
TARGET = maze

# Phony targets
.PHONY: all clean copy_png_files

# Default target
all: $(TARGET)

# Linking the target
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	$(MAKE) copy_png_files

# Compiling source files to object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -o $@ -c $<

# Creating object directory if it does not exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Copy PNG files to the build directory
copy_png_files:
	@for file in $(PNG_FILES); do \
		cp $(SRCDIR)/$$file .; \
	done

# Clean up
clean:
	rm -rf $(OBJDIR) $(TARGET) $(PNG_FILES)

