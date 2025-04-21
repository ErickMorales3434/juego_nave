#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <conio.h>


#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80

using namespace std;

void gotoxy(int x, int y) {
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;

    SetConsoleCursorPosition(hCon, dwPos);
}


void OcultarCursor() {
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 5;
    cci.bVisible = FALSE;

    SetConsoleCursorInfo(hCon,&cci);
}


int main() {
    OcultarCursor();
    int x = 10, y = 10;
    gotoxy(10, 10);
    cout << "*";
    bool game_over = false;
    while (!game_over) {


        if (_kbhit()) {
            char tecla = _getch();
            gotoxy(x, y);
            cout << " ";
            if (tecla == IZQUIERDA) x--;
            if (tecla == DERECHA) x++;
            if (tecla == ARRIBA) y--;
            if (tecla == ABAJO) y++;
            gotoxy(x, y);
            cout << "*";
        }
        Sleep(30);




    }
        return 0;
    
}
