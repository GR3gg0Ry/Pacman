#include <stdio.h>

class BasicView                                                 //класс BasicView 
{
    private:
    int n=0,size,score;
    public:
    BasicView(int _size): size(_size) {};                       //конструктор
    void Picture(int m) {
        switch(m)
        {
        case 1:
            printf("\033[47m#\033[0m");  // Белая стенка
            break;
        case 2:
            printf("\033[43m.\033[0m");  // Желтый бонус
            break;
        case 3:
            printf("\033[42mC\033[0m");  // Зеленый Pacman
            break;
        case 4:
            printf("\033[41mD\033[0m");  // Красный Demon
            break;
        default:
            printf(" ");                 // пустое поле
        }
        n++;
        if (n == size) {                 
            printf("\n");
            n = 0;
        }
    }

    void Score(int currentScore)                                       //метод вывода счёта
    {
        printf("Score: %d/%d\n", currentScore,size*size/6);
    };
};