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

class NAVE {
    int x, y;
public:
    NAVE(int _x, int _y);
    void pintar();
    void borrar();
    void mover();
};

NAVE::NAVE(int _x, int _y) {
    x = _x;
    y = _y;
}

void NAVE::pintar() {
    gotoxy(x, y);
    cout << " % c",30;
    gotoxy(x, y+1);
    cout << "%c%c%c", 40, 207, 41;
    gotoxy(x, y+2);
    cout << "%c%c %c%c", 30, 190, 190,30;
}
void NAVE::borrar() {
    gotoxy(x, y);
    cout << "         ";
    gotoxy(x, y+1);
    cout << "         ";
    gotoxy(x, y+2);
    cout << "         ";
}
void NAVE::mover(){
    if (_kbhit()) {
        char tecla = _getch();
        borrar();
        if (tecla == IZQUIERDA) x--;
        if (tecla == DERECHA) x++;
        if (tecla == ARRIBA) y--;
        if (tecla == ABAJO) y++;
        pintar();
    }
 }


int main() {
    OcultarCursor();
    NAVE MINAVE(7, 7);
    MINAVE.pintar();


    bool game_over = false;
    while (!game_over) {


        MINAVE.mover();
        Sleep(30);




    }
        return 0;
    
}
