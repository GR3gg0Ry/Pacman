#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define SIZE 20

enum MapObject {
    EMPTY = 0,
    WALL = 1,
    BONUS = 2,   
    PACMAN = 3, 
    DEMON = 4
};

class Map                                                           //класс Map 
{
    friend class Game;
    private:
    int map[SIZE][SIZE];                                            //матрица карты                                        
    public:
    Map() {};                                                       //конструктор по умолчанию
    int getfield(int x,int y)                                       //метод получения состояния поля (стенка/нет стенки)
    {
        return map[x][y];                                           //есть стенка - 1, нет стенки - 0
    };
    void create() {
        int i, j,bonuses=0;
        for(i = 0; i < SIZE; i++) 
            for(j = 0; j < SIZE; j++)
                map[i][j] = EMPTY;                                  // Заполняем карту пустыми полями

        for(i = 0; i < SIZE; i++) {                                 // Создаем боковые стенки карты
            map[i][0] = WALL;
            map[0][i] = WALL;
            map[i][SIZE - 1] = WALL;
            map[SIZE - 1][i] = WALL;
        }
        for(i = 3; i < SIZE - 3; i += 3)                            // Заполняем внутреннюю часть карты
            for(j = 4; j < SIZE - 4; j++)
                map[i][j] = WALL;

        map[SIZE / 2 + 1][SIZE / 2] = PACMAN;                       // Положение Pacman
        map[1][2] = DEMON;                                          // Положение Demon
        map[17][10] = DEMON;
        map[10][18] = DEMON;
        srand(time(NULL));
        while(bonuses<SIZE*SIZE/6)                                  //Заполнение карты бонусами
        {
            i = rand()%20;
            j = rand()%20;
            if (map[i][j] == EMPTY)
            {
                map[i][j] = BONUS; 
                bonuses+=1;
            }
        }
        return;
    }

    int chek(int* point)                                            //метод ПРОВЕРКИ на наличие стенки
    {
        return map[point[0]][point[1]];                             //есть стенка - 1, нет стенки - 0
    };
    void change(int x,int y,int code)                               //метод изменения поля
    {
        map[x][y]=code;                                             //присваивание нового объекта полю
    };
};

class Gambler
{
    friend class Game;
    private:
    int x;                                                          //координаты Pacman
    int y;
    public:
    Gambler(int _x, int _y): x(_x),y(_y) {};                        //конструктор    
    int getx(int n) {x+=n; return x;};
    int gety(int n) {y+=n; return y;};
    int* getloc(int* loc) {loc[0] = x; loc[1] = y; return loc;};    //метод получения координат
};

class Pacman: public Gambler                                        //класс Pacman (информация о Pacman)
{
    private:
    int exist = 1;                                                  //состояние живой/мёртвый
    public:
    int getexist() {return exist;};                                 //метод получения состояния Pacman    
    Pacman(int _x, int _y): Gambler(_x,_y) {};                      //конструктор
};

class Demon: public Gambler                                         //класс Demon (информация о Demon)
{
    public:
    Demon(int _x, int _y): Gambler(_x,_y) {};                       //конструктор
};