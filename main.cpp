#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>


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
void pintar_limites() {
    //pintar parte superior e inferior de la pantalla
    for (int i = 2; i < 78;i++) {
        gotoxy(i, 3);
        cout << (char)205;
        gotoxy(i, 33);
        cout << (char)205;
    }
    //pintar partes laterales de la pantalla
    for (int i = 4;i < 33;i++) {
        gotoxy(2, i);
        cout << (char)186;
        gotoxy(77, i);
        cout << (char)186;
    }
    //pintar extremos de la pantalla
    //arriba
    gotoxy(2, 3);
    cout << (char)201;
    //abajo
    gotoxy(2, 33);
    cout << (char)200;
    //derecha
    gotoxy(77, 3);
    cout << (char)187;
    //izquiera
    gotoxy(77, 33);
    cout << (char)188;
}

class NAVE {
    int x, y;
    int corazones;
    int vidas;
public:
    NAVE(int _x, int _y, int _corazones,int _vidas): x(_x),y(_y),corazones(_corazones),vidas(_vidas){}
    void pintar();
    void borrar();
    void mover();
    void pintar_corazones();
    void morir();
};


void NAVE::pintar() {
    //cout << " % c",30;
    //cout << "%c%c%c", 40, 207, 41;
    //cout << "%c%c %c%c", 30, 190, 190,30;
    gotoxy(x, y);
    printf(" /\\\n");
    gotoxy(x, y+1);
    printf(" ||\n");
    gotoxy(x, y+2);
    printf("/__\\\n");
    gotoxy(x, y + 3);
    printf(" vv\n");

}
void NAVE::borrar() {
    gotoxy(x, y);
    printf("          ");
    gotoxy(x, y + 1);
    printf("          ");
    gotoxy(x, y + 2);
    printf("         ");
    gotoxy(x, y + 3);
    printf("         ");
}
void NAVE::mover(){
    if (_kbhit()) {
        char tecla = _getch();
        borrar();
        if (tecla == IZQUIERDA && x>3) x--;
        if (tecla == DERECHA && x+6 <77) x++;
        if (tecla == ARRIBA && y > 4) y--;
        if (tecla == ABAJO && y+3 < 33) y++;
        if (tecla == 'e') corazones--;
        pintar();
        pintar_corazones();
    }
 }
//vidas en corazones
void NAVE::pintar_corazones() {

    gotoxy(50, 2);
    cout << "VIDAS: " << vidas;

    gotoxy(64,2);
    cout << "Salud: ";
    gotoxy(70, 2);
    cout << "    ";
    for (int i = 0; i < corazones; i++) {
        gotoxy(70 + i, 2);
        cout << (char)3;
    }
}
void NAVE::morir() {
    if (corazones == 0) {
        borrar();
        gotoxy(x, y);
        cout << "   **   ";
        gotoxy(x, y+1);
        cout << "  ****   ";
        gotoxy(x, y+2);
        cout << "   **   ";
        gotoxy(x, y+3);
        cout << "      ";
        Sleep(200);


        borrar();
        gotoxy(x, y);
        cout << " * ** *";
        gotoxy(x, y + 1);
        cout << "  **** ";
        gotoxy(x, y + 2);
        cout << " * ** *";
        gotoxy(x, y + 3);
        cout << "      ";
        Sleep(200);

        borrar();
        vidas--;
        corazones = 3;
        pintar_corazones();
        pintar();

    }
}

class ASTEROIDE {
    int x, y;
public:
    ASTEROIDE(int _x, int _y) : x(_x), y(_y) {}
    void pintar();
    void mover();
};

void ASTEROIDE::pintar() {
    gotoxy(x, y);
    cout << (char)184;
}

void ASTEROIDE::mover() {
    gotoxy(x, y);
    cout << " ";
    y++;
    if (y > 32) {
        x = rand() % 71 + 4;
        y = 4;
    }
    pintar();
}

int main() {

    OcultarCursor();
    pintar_limites();
    NAVE MINAVE(7, 7,3,3);
    MINAVE.pintar();
    MINAVE.pintar_corazones();

    ASTEROIDE EL_ASTEROIDE(10, 4);



    bool game_over = false;
    while (!game_over) {

        EL_ASTEROIDE.mover();
        MINAVE.morir();
        MINAVE.mover();
        Sleep(30);




    }
        return 0;
    
}
