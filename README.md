# Pacman
## Introduction
Pakman was developed as an educational project to put into practice the knowledge gained during the OOP course by students of the CAD System Department of Bauman Moscow State Technical University. The project was divided into several modules, which were distributed among the developers.

In this game, the player controls a character named Pacman, who must collect points on the level, avoiding collisions with ghosts. The game ends when Pacman encounters a ghost or when the player decides to exit the game. 
The task is to collect the required number of points and not be eaten by Demons.

Program interface is implemented in UNIX console.

<img src='https://github.com/GR3gg0Ry/Pacman/blob/main/docs/pacman.gif?raw=true'/>

## Main features

1. Player can choose the difficulty level in the menu.
2. Player can select a map from the maps directory.
3. Player can move through free fields or fields with bonuses using the WASD keys.
4. Levels differ with game difficulty, they can be changed in settings.txt file.
5. With each turn of the Pacman, the Demons make one move.
6. The game can be stopped by pressing ESC.
7. User can upload their map by adding it to the maps directory.

## Assigning project directories:
+ `docs` - documentation files
+ `include` - header files
+ `src` - .cpp files

## Instructions for working with the project
+ [Menu](docs/menu.md)
+ [Game](docs/game.md)
+ [Installation](docs/installation.md)

## Requirements
The following must be installed on the device:
+ C++17
+ Cmake 3.16
+ Make
