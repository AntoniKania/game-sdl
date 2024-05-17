OBJS = main.cpp texture.cpp tile.cpp collision.cpp player.cpp shotgun.cpp cursor.cpp map.cpp camera.cpp enemy.cpp path.cpp vector2.cpp button.cpp timer.cpp blood_effect.cpp


CC = g++

COMPILER_FLAGS = -I/usr/include/SDL2

LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

OBJ_NAME = game

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)