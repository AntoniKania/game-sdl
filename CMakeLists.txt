cmake_minimum_required(VERSION 3.24)
project(game)

set(CMAKE_CXX_STANDARD 17)

set(SDL2_INCLUDE_DIR "C:\\LibSDL\\VC\\SDL2-2.26.3\\include")
set(SDL2_LIB_DIR "C:\\LibSDL\\VC\\SDL2-2.26.3\\lib\\x64")

include_directories(${SDL2_INCLUDE_DIR})
add_executable(${PROJECT_NAME} main.cpp
        texture.cpp
        texture.h
        tile.cpp
        tile.h
        collision.cpp
        collision.h
        player.cpp
        player.h
        map.cpp
        map.h
        camera.cpp
        camera.h
        enemy.cpp
        enemy.h
        path.cpp
        path.h
        shotgun.cpp
        shotgun.h
        vector2.h
        vector2.cpp
        cursor.cpp
        cursor.h
        blood_effect.cpp
        blood_effect.h
        timer.cpp
        timer.h
        button.cpp
        button.h)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIB_DIR}/SDL2.lib ${SDL2_LIB_DIR}/SDL2main.lib)