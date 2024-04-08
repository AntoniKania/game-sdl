OBJS = main.cpp texture.cpp tile.cpp collision.cpp dot.cpp map.cpp camera.cpp

CC = g++

#COMPILER_FLAGS = -w

LINKER_FLAGS = -lSDL2 -lSDL2_image

OBJ_NAME = game

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)