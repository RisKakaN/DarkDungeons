cmake_minimum_required(VERSION 3.7)
project(DarkDungeons)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES source/main.cpp source/tinyxml2Lib/tinyxml2.h source/tinyxml2Lib/tinyxml2.cpp source/include/graphics.h source/src/graphics.cpp source/include/game.h source/src/game.cpp source/include/input.h source/src/input.cpp source/include/globals.h source/include/sprite.h source/src/sprite.cpp source/include/animatedSprite.h source/src/animatedSprite.cpp source/include/player.h source/src/player.cpp source/include/room.h source/src/room.cpp source/include/tile.h source/src/tile.cpp source/include/rectangle.h source/include/door.h source/include/enemy.h source/include/enemyLevel1.h source/src/enemy.cpp source/src/enemyLevel1.cpp source/include/hud.h source/src/hud.cpp)
add_executable(DarkDungeons ${SOURCE_FILES})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${DarkDungeons_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(
        ${DarkDungeons_SOURCE_DIR}/source/include
        ${DarkDungeons_SOURCE_DIR}/source/tinyxml2Lib
        ${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR})

target_link_libraries(DarkDungeons
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES})