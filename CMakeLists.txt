cmake_minimum_required(VERSION 3.10)

project(Pacman)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    main.cpp
    Input.cpp
    Map.cpp
    Game.cpp
    
)

set(HEADERS
    Input.h
    Map.h
    ScoreCounter.h
    Entity.h
    Game.h
    GameUtils.h
    
)
add_executable(Pacman ${SOURCES} ${HEADERS})
