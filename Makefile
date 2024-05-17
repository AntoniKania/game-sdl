OBJS = main.cpp texture.cpp tile.cpp collision.cpp player.cpp shotgun.cpp cursor.cpp map.cpp camera.cpp enemy.cpp path.cpp vector2.cpp

CC = g++

#COMPILER_FLAGS = -w

LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

OBJ_NAME = game

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)