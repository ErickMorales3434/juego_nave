#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

void gotoxy(int x, int y) {
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;

    SetConsoleCursorPosition(hCon, dwPos);
}
int main() {

    int x = 10, y = 10;
    gotoxy(10, 10);
    cout << "*";
    bool game_over = false;
    while (!game_over) {


        if (_kbhit()) {
            char tecla = _getch();
            gotoxy(x, y);
            cout << " ";
            if (tecla == 'j') x--;
            if (tecla == 'l') x++;
            if (tecla == 'i') y--;
            if (tecla == 'k') y++;
            gotoxy(x, y);
            cout << "*";
        }
        Sleep(30);




    }
        return 0;
    
}
