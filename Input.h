#pragma once

class Input {
public:
    char getc();
    char readmenu();
    char readchar();
private:
    char c = '\0';
    char ch = '\0';
};
