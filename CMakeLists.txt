cmake_minimum_required(VERSION 3.10)

project(Pacman)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

set(SOURCES
    src/main.cpp
    src/Input.cpp
    src/Map.cpp
    src/Game.cpp
    src/Entity.cpp
    src/GameMenu.cpp
    src/Render.cpp
)

set(HEADERS
    include/Input.h
    include/Map.h
    include/ScoreCounter.h
    include/Entity.h
    include/Game.h
    include/GameUtils.h
    include/Render.h
    include/GameMenu.h
)
add_executable(Pacman ${SOURCES} ${HEADERS})
