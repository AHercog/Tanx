cmake_minimum_required(VERSION 3.13)

add_subdirectory(dependencies/random)
project(czolgi)
set(CMAKE_CXX_STANDARD 17)

include_directories(include /home/xaaq/other-projects/assimp/include)
link_directories(/home/xaaq/other-projects/assimp/lib)

add_executable(czolgi src/main.cpp src/player.cpp include/player.h src/vector_3d.cpp include/vector_3d.h
        src/environment.cpp include/environment.h src/camera.cpp include/camera.h include/constants.h src/bullet.cpp
        include/bullet.h src/wall.cpp include/wall.h include/enemies/enemy_like.h src/enemies/basic_enemy_tank.cpp
        include/enemies/basic_enemy_tank.h src/enemies/enemy_factory.cpp include/enemies/enemy_factory.h
        include/collidable.h src/model_handler.cpp include/model_handler.h)

target_link_libraries(czolgi glut GL GLU effolkronium_random assimp)
