#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <list>

#include <chrono>
#include <thread>

#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80

using namespace std;
using namespace std::chrono;

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
    for (int i = 2; i < 130;i++) {
        gotoxy(i, 3);
        cout << (char)205;
        gotoxy(i, 50);
        cout << (char)205;
    }
    //pintar partes laterales de la pantalla
    for (int i = 4;i < 50;i++) {
        gotoxy(2, i);
        cout << (char)186;
        gotoxy(130, i);
        cout << (char)186;
    }
    //pintar extremos de la pantalla
    //arriba
    gotoxy(2, 3);
    cout << (char)201;
    //abajo
    gotoxy(2, 50);
    cout << (char)200;
    //derecha
    gotoxy(130, 3);
    cout << (char)187;
    //izquiera
    gotoxy(130, 50);
    cout << (char)188;
}

class NAVE {
    int x, y;
    int corazones;
    int vidas;
public:
    NAVE(int _x, int _y, int _corazones,int _vidas): x(_x),y(_y),corazones(_corazones),vidas(_vidas){}
    int X() { return x; };
    int Y() { return y; };
    void COR() {
        corazones--;
    }
    void pintar();
    void borrar();
    void mover();
    void pintar_corazones();
    void morir();

    void mover_izquierda() {
        if (x > 5) {
            borrar();
            x--;
            pintar();
        }
    }

    void mover_derecha() {
        if (x < 120) { //  según ancho de la consola
            borrar();
            x++;
            pintar();
        }
    }

    void mover_arriba() {
        if (y > 5) {
            borrar();
            y--;
            pintar();
        }
    }

    void mover_abajo() {
        if (y < 45) { // según alto de la consola
            borrar();
            y++;
            pintar();
        }
    }
 

};



void NAVE::pintar() {
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
    void borrar();
    void choque(class NAVE &N);

};

void ASTEROIDE::pintar() {
    gotoxy(x, y);
    cout << " () ";
    gotoxy(x, y+1);
    cout << "()()()";
}
void ASTEROIDE::borrar() {
    gotoxy(x, y);     cout << "      ";
    gotoxy(x, y + 1); cout << "      ";
}

void ASTEROIDE::mover() {
    borrar();
    gotoxy(x, y);
    cout << " ";
    y++;
    if (y > 32) {
        x = rand() % 110 + 4;
        y = 4;
    }
    pintar();
}

void ASTEROIDE::choque(class NAVE& N) {
    //verifica la posicion de la nave con el asteroide
    if (x >= N.X() && x <= N.X() + 7 && y >= N.Y() && y <= N.Y() + 2)
    {
        N.COR();
        N.borrar();
        N, pintar();
        N.pintar_corazones();
        x = rand() % 71 + 4;
        y = 4;
    }
}

class BALA {
    int x, y;
public:
    BALA(int _x, int _y) : x(_x), y(_y) {}

int Y() { return y; }

void mover() {
    borrar();

    y--; // sube la bala hasta la posicion  y = 4)

    if (y > 0) {
        pintar();
    }
}

void pintar() {
    gotoxy(x, y);
    cout << "*";
}

void borrar() {
    gotoxy(x, y);
    cout << " ";
}

bool fuera_de_pantalla() {
    return (y <= 4); // posicion donde la bala desaparece
}
};

int main() {


    OcultarCursor();
    pintar_limites();
    NAVE MINAVE(7, 7, 3, 3);
    MINAVE.pintar();
    MINAVE.pintar_corazones();

    ASTEROIDE EL_ASTEROIDE(10, 4), ast1(15, 10), ast2(1, 3), ast3(5, 4);

    list<BALA*> B;
    list<BALA*>::iterator it;

    int frameDelay = 33; // 33 ms para ~30 FPS
    bool game_over = false;
    while (!game_over) {
        auto frameStart = high_resolution_clock::now();

        // 👇 Detectar teclas presionadas
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            MINAVE.mover_izquierda();
        }
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            MINAVE.mover_derecha();
        }
        if (GetAsyncKeyState(VK_UP) & 0x8000) {
            MINAVE.mover_arriba();
        }
        if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
            MINAVE.mover_abajo();
        }
        if (GetAsyncKeyState('A') & 0x8000) {
            B.push_back(new BALA(MINAVE.X() + 2, MINAVE.Y() - 1));
        }

        for (it = B.begin(); it != B.end();) {
            (*it)->mover();

            if ((*it)->fuera_de_pantalla()) {
                (*it)->borrar();
                delete (*it);
                it = B.erase(it);  // borra de la lista y avanza
            }
            else {
                ++it;
            }
        }


                    EL_ASTEROIDE.mover();
                    EL_ASTEROIDE.choque(MINAVE);
            
                    ast1.mover();
                    ast1.choque(MINAVE);
                    ast2.mover();
                    ast2.choque(MINAVE);
                    ast3.mover();
                    ast3.choque(MINAVE);
            
                    MINAVE.morir();
                 
        auto frameEnd = high_resolution_clock::now();
        auto elapsed = duration_cast<milliseconds>(frameEnd - frameStart);

        if (elapsed.count() < frameDelay) {
           //delay en milisegundos
            std::this_thread::sleep_for(milliseconds(frameDelay - elapsed.count()));
        }

    }
        
return 0;
    
}
