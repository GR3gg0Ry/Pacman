# Build and launch the game

You need to install the game:
+ ```` git clone https://github.com/GR3gg0Ry/Pacman.git ````

You need to perform the following actions:
````
git clone https://github.com/GR3gg0Ry/Pacman
mkdir -p Pacman/build
mkdir -p Pacman/build/Maps
cp -a /Pacman/Maps /Pacman/build/Maps
cd Pacman/build
cmake ..
make
./Pacman
````
Сommand to copy:
```` 
cd git clone https://github.com/GR3gg0Ry/Pacman && mkdir -p Pacman/build && mkdir -p Pacman/build/Maps && cp -a /Pacman/Maps /Pacman/build/Maps && cd Pacman/build && cmake .. && make && ./Pacman
````
