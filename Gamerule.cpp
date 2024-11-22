#include <iostream>
#include <fstream>
#include <string>

#include "View.h"
#include "Model.h"

std::string map_display;
std::string demon_movement;

class Input
{
    private:
    char c = '\0'; // Инициализация с использованием '\0' для символа
    public:
    char getc() { return c; }; // получение хода игрока
    char read() // чтение хода игрока
    {
        do
        {
            c = static_cast<char>(getchar()); // считывается первый символ входной строки
            if (c != 'w' && c != 'W' && c != 's' && c != 'S' && c != 'a' && c != 'A' && c != 'd' && c != 'D') {
                c = '\0'; // обнуление, если это не символ хода
            }
            while (getchar() != '\n'); // очистка буфера
        } while (c == '\0'); // считывается до тех пор, пока не будет введён ход
        return c;
    }
};


class Game                                                                                                      //класс Game
{
    private:
    Map M1;
    Pacman P1;
    Demon* En1;
    Input I1;
    BasicView BV1;
    int SC1 = 0;
    public:
    Game(Map& _M1, Pacman& _P1, Demon* _En1, Input& _I1,BasicView& _BV1): M1(_M1), P1(_P1), En1(_En1), I1(_I1),BV1(_BV1) {};   //конструктор
    void move()                                                                                                 //метод передвижения Пакмана
    {

            switch (I1.read())                                                                                  //обработка результата ввода
            {   
                case 'w':
                case 'W':
                    if(M1.getfield(P1.getx(0)-1,P1.gety(0))==EMPTY||M1.getfield(P1.getx(0)-1,P1.gety(0))==BONUS)        
                    {
                        if(M1.getfield(P1.getx(0)-1,P1.gety(0))==BONUS)
                            getScore(3);
                        P1.getx(-1);
                    };
                    break;
                case 's':
                case 'S':
                    if(M1.getfield(P1.getx(0)+1,P1.gety(0))==EMPTY||M1.getfield(P1.getx(0)+1,P1.gety(0))==BONUS)
                    {
                        if(M1.getfield(P1.getx(0),P1.gety(0)-1)==BONUS)
                            getScore(3);
                        P1.getx(1);
                    };
                    break;
                case 'a':
                case 'A':
                    if(M1.getfield(P1.getx(0),P1.gety(0)-1)==EMPTY||M1.getfield(P1.getx(0),P1.gety(0)-1)==BONUS)
                    {
                        if(M1.getfield(P1.getx(0),P1.gety(0)-1)==BONUS)
                            getScore(3);
                        P1.gety(-1);
                    };
                    break;
                case 'D':
                case 'd':
                    if(M1.getfield(P1.getx(0),P1.gety(0)+1)==EMPTY||M1.getfield(P1.getx(0),P1.gety(0)+1)==BONUS)
                    {
                        if(M1.getfield(P1.getx(0),P1.gety(0)+1)==BONUS)
                            getScore(3);
                        P1.gety(1);
                    };
                    break;
            };
        return;
    }

    void moveDemon(int num) {

        int dx = P1.getx(0) - En1[num].getx(0);   
        int dy = P1.gety(0) - En1[num].gety(0);   
        int new_x = En1[num].getx(0);
        int new_y = En1[num].gety(0);

        if ((abs(dx) < abs(dy))&&(abs(dx)!=0)&&(abs(dx)!=1))                                                                                      // Если Pacman выше или ниже демона, делаем вертикальный шаг
            new_x += (dx > 0) ? 1 : -1;
        else                                                                                                                        // Если Pacman левее или правее, делаем горизонтальный шаг
            new_y += (dy > 0) ? 1 : -1;    
        if (M1.getfield(new_x, new_y) == PACMAN) {
            printf("Gameover!");
            exit(0); }                                                                             
        if (M1.getfield(new_x, new_y) == EMPTY||M1.getfield(new_x, new_y) == BONUS) {                           // Проверка на стену перед движением демона
            if(M1.getfield(new_x, new_y) == BONUS)                                                              //Demon убавляет очки игрока
                getScore(-1);
            M1.change(En1[num].getx(0), En1[num].gety(0), EMPTY); // предыдущее поле освобождаем
            En1[num].getx(new_x - En1[num].getx(0));  // обновляем положение демона по x
            En1[num].gety(new_y - En1[num].gety(0));  // обновляем положение демона по y
            M1.change(En1[num].getx(0), En1[num].gety(0), DEMON); // новый код для демона
        }
    }
    
    void output()                                                                                               //вывод поля
    {
        int x,y;                                                    
        for(x=0;x<SIZE;x++)                                             
            for(y=0;y<SIZE;y++)
                BV1.Picture(M1.getfield(x,y));                        
        BV1.Score(getScore(0));                                                                                 //вывод счёта
    };

    void step()                                                                                                 //ход игрока
    {
        int x1 = P1.getx(0);                                                                                    //записываются координаты 
        int y1 = P1.gety(0);                                                                                    //Пакмана до хода
        move();                                                                                                 //совершение хода
        M1.change(x1,y1,EMPTY);                                                                                 //прежнее поле Пакмана становится пустым
        M1.change(P1.getx(0),P1.gety(0),PACMAN);                                                                //новое поле занимает Пакман
    };
    int getScore(int m)                                                                                         //метод получения/изменения счёта
    {
        SC1 +=m;
        return SC1;
    };
};

void loadConfig() {
    std::ifstream config("config.txt");
    if (!config.is_open()) {
        std::cerr << "Ошибка: Не удалось открыть файл конфигурации.\n";
        exit(1);
    }
    
    std::string line;
    while (std::getline(config, line)) {
        if (line.find("map_display") != std::string::npos) {
            map_display = line.substr(line.find("=") + 2);
        } else if (line.find("demon_movement") != std::string::npos) {
            demon_movement = line.substr(line.find("=") + 2);
        }
    }
    config.close();
}

int main() {
    loadConfig();  // Загружаем конфигурацию

    // Создаем объекты игры
    Map Map1;
    Map1.create();  // Заполняем карту

    Pacman C(SIZE / 2 + 1, SIZE / 2);  // Создаем Pacman
    Demon enemies[3] = { Demon(1, 2), Demon(17, 10), Demon(10, 18) };  // Создаем массив демонов

    Input input1;  // Создаем объект пользовательского ввода

    BasicView BView(SIZE);  // Создаем объект отрисовки
    if (map_display == "escape") {
        std::cout << "Используется карта с escape-кодами\n";
    } else {
        std::cout << "Используется карта с символами\n";
    }

    Game Game1(Map1, C, enemies, input1, BView);  // Создаем контроллер игры
    int i;
    while (Game1.getScore(0)<SIZE*SIZE/6) {
        Game1.output();  // Вывод карты
        Game1.step();    // Ход Pacman
        for(i=0;i<3;i++)
                Game1.moveDemon(i);
        // Двигаем демонов согласно выбранной тактике
/*          if (demon_movement == "towards_pacman") {
            for(i=0;i<3;i++)
                Game1.moveDemon(i);  // Двигаем демонов к Pacman
        } else if (demon_movement == "cyclic") {
            std::cout << "Реализуйте циклическое движение демонов\n";
            // Здесь можно реализовать циклическую тактику движения
        }*/
    }
    Game1.output();
    printf("You won! Congratulations!");
    return 0;
}
