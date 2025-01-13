#include "Input.h"

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>

char Input::readchar() {
    termios old_settings;
    tcgetattr(STDIN_FILENO, &old_settings);
    termios new_settings = old_settings;
    new_settings.c_lflag &= ~ICANON; 
    new_settings.c_lflag &= ~ECHO;   
    new_settings.c_cc[VMIN] = 1;     

    new_settings.c_cc[VTIME] = 0;    // Без таймаута
    tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
    do {
        read(STDIN_FILENO, &c, 1);
        if (c == 27) {
            std::cout << "The game was interrupted" << std::endl;
            tcsetattr(STDIN_FILENO, TCSANOW, &old_settings);
            exit(0);
        }
        if (c != 'w' && c != 'W' && c != 's' && c != 'S' && c != 'a' && c != 'A' && c != 'd' && c != 'D') {
            c = '\0';
        }
        fflush(stdin);
    } while (c == '\0');
    tcsetattr(STDIN_FILENO, TCSANOW, &old_settings);
    return c;
}

char Input::readmenu() {
    termios old_settings;
    tcgetattr(STDIN_FILENO, &old_settings);
    termios new_settings = old_settings;

    new_settings.c_lflag &= ~ICANON; 
    new_settings.c_lflag &= ~ECHO;
    new_settings.c_cc[VMIN] = 1;   

    new_settings.c_cc[VTIME] = 0;    // Без таймаута
    tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
    do {
        read(STDIN_FILENO, &ch, 1);
        if (ch != 'w' && ch != 's' && ch != '\n') {
            ch = '\0';
        }
        fflush(stdin);
    } while (ch == '\0');
    tcsetattr(STDIN_FILENO, TCSANOW, &old_settings);
    return ch;
}
