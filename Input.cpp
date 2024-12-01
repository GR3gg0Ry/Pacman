#include "Input.h"

#include <iostream>
#include <conio.h>

char Input::read() {
    do {
        c = static_cast<char>(getch());
        if (c == 27) {
            std::cout << "The game was interrupted" << std::endl;
            exit(0);
        }
        if (c != 'w' && c != 'W' && c != 's' && c != 'S' && c != 'a' && c != 'A' && c != 'd' && c != 'D') {
            c = '\0';
        }
        fflush(stdin);
    } while (c == '\0');
    return c;
}

char Input::getc() {
    return c;
}