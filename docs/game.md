# Game

The gameplay involves displaying a map represented as a two-dimensional array of symbols. 
Ghosts can follow Pacman or move randomly, depending on their behavior, which is set by the difficulty level. Ghosts can't pass through walls. 
When a Pacman collides with a ghost, the message "Game Over" and the current score are displayed.

|  Symbol |                      Designation                         |
| ------- | -------------------------------------------------------- |
|   `#`   |                       Walls                              |
|   `.`   |                    Small Bonuses                         |
|   `P`   |                      Pacman                              |
|   `G`   |                      Demons                              |
|   `O`   |                      Bonuses                             |

The winner is the one who collects all the bonuses. 

After defeat, the player returns to the menu. You can read about the menu here -> [Menu](menu.md)

<img src='https://github.com/GR3gg0Ry/Pacman/blob/main/docs/pacman.gif?raw=true'/>

|    Key  |                      Appointment                         |
| ------- | -------------------------------------------------------- |
|   `w`   |                       Move up                            |
|   `s`   |                      Move down                           |
|   `d`   |                      Move right                          |
|   `a`   |                      Move left                           |
|  `esc`  |                    Exit the game                         |
