cmake_minimum_required(VERSION 3.26)

project(game)
add_executable(game main.cpp
        texture.cpp
        texture.h
        tile.cpp
        tile.h
        collision.cpp
        collision.h
        dot.cpp
        dot.h
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
)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})