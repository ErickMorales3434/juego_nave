﻿#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <list>

#include <chrono>
#include <thread>
#include <SFML/Audio.hpp>



using namespace std;
using namespace std::chrono;

void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

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

    SetConsoleCursorInfo(hCon, &cci);
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
    int color;
public:
    NAVE(int _x, int _y, int _corazones, int _vidas, int _color = 12) : x(_x), y(_y), corazones(_corazones), vidas(_vidas), color(_color) {}
    int X() { return x; };
    int Y() { return y; };
    int Vidas() { return vidas; }
    void COR() {
        corazones--;
    }
    void pintar();
    void borrar();

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
    setColor(12);
    //printf(" /\\\n");
    cout << "  /\\";
    gotoxy(x, y + 1);
    //printf(" ||\n");
    cout << " /==\\";
    gotoxy(x, y + 2);
    //printf("/__\\\n");
    cout << " \\vv/";
    //gotoxy(x, y + 3);
    //printf(" vv\n");
    setColor(7);
}
void NAVE::borrar() {
    gotoxy(x, y);
    printf("      ");
    gotoxy(x, y + 1);
    printf("      ");
    gotoxy(x, y + 2);
    printf("      ");

}

//vidas en corazones
void NAVE::pintar_corazones() {

    gotoxy(50, 2);
    cout << "VIDAS: " << vidas;

    gotoxy(64, 2);
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
        gotoxy(x, y + 1);
        cout << "  ****   ";
        gotoxy(x, y + 2);
        cout << "   **   ";
        gotoxy(x, y + 3);
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
    int color;
public:
    ASTEROIDE(int _x, int _y, int _color = 'd') : x(_x), y(_y), color(_color) {}
    void pintar();
    void mover();
    void borrar();
    void reiniciar();
    void choque(class NAVE& N);

    bool colision_con_bala(int bx, int by) {
        return (bx >= x && bx <= x + 2 && by >= y && by <= y + 2);
    }
    
};

void ASTEROIDE::reiniciar() {
    x = rand() % 110 + 4; // posición aleatoria horizontal
    y = 4;                // arriba de la pantalla
}

void ASTEROIDE::pintar() {
    gotoxy(x, y);

    cout << " /**\\";
    gotoxy(x, y + 1);
    cout << " \\__/";
   /* gotoxy(x, y + 2);
    cout << " 0 ";*/

}
void ASTEROIDE::borrar() {
    gotoxy(x, y);     cout << "      ";
    gotoxy(x, y + 1); cout << "      ";
    //gotoxy(x, y + 2); cout << "    ";
}

void ASTEROIDE::mover() {
    borrar();
    gotoxy(x, y);
    y++;
    if (y > 48) {
        x = rand() % 110 + 4;
        y = 6;
    }
    pintar();
}

void ASTEROIDE::choque(class NAVE& N) {
    //verifica la posicion de la nave con el asteroide
    if (x >= N.X() && x <= N.X() + 6 && y >= N.Y() && y <= N.Y() + 2)
    {
        N.COR();
        N.borrar();
        N.pintar();
        N.pintar_corazones();
        x = rand() % 71 + 4;
        y = 4;
    }
}

class BALA {
    int x, y;
public:
    BALA(int _x, int _y) : x(_x), y(_y) {}
    int X() { return x; }
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
        cout << "      ";
        gotoxy(x, y - 1);
        cout << "      ";
        gotoxy(x, y - 2);
        cout << "      ";
    }

    bool fuera_de_pantalla() {
        return (y <= 7); // posicion donde la bala desaparece
    }
};


void mostrar_puntos(int puntos) {
    gotoxy(5, 2);
    cout << "Puntos: " << puntos;
}


int main() {

   
    

    sf::Music music;
        if (!music.openFromFile("sonido_espacio.ogg")) {
            std::cerr << "Error al abrir archivo de música\n";
            return -1;
        }
    music.setLooping(true);
    // 🔁 Repetir música automáticamente
    music.play();
    //cout << "ESCRIBE 'Y' Y PRESIONA ENTER PARA INICIAR";
    //cin.get();



    // Cargar el buffer de sonido
    sf::SoundBuffer buffer1;
    if (!buffer1.loadFromFile("disparo.wav")) {
        std::cerr << "Error al cargar disparo.wav\n";
        return -1;
    }

    // Crear el sonido con el buffer cargado
    sf::Sound disparo(buffer1);





    sf::Clock relojDisparo;
    float tiempoEntreDisparos = 0.3f; // en segundos

    // Cargar el buffer de sonido
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("explosion.wav")) {
        std::cerr << "Error al cargar disparo.wav\n";
        return -1;
    }

    // Crear el sonido con el buffer cargado
    sf::Sound explosion(buffer);

  








    int puntos = 0;
    OcultarCursor();
    pintar_limites();
    NAVE MINAVE(40, 30, 3, 3);

    MINAVE.pintar();

    MINAVE.pintar_corazones();
    mostrar_puntos(puntos);
    //Sleep(5000);

    ASTEROIDE EL_ASTEROIDE(10, 4), ast1(15, 10), ast2(8, 4), ast3(17, 4);

    list<BALA*> B;
    list<BALA*>::iterator it;

    int frameDelay = 33; // 33 ms para ~30 FPS
    bool game_over = false;
    while (!game_over) {
        auto frameStart = high_resolution_clock::now();

        // Detectar teclas presionadas
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
            if (relojDisparo.getElapsedTime().asSeconds() >= tiempoEntreDisparos) {
                disparo.play(); // Reproduce el sonido de disparo
                B.push_back(new BALA(MINAVE.X() + 2, MINAVE.Y() - 1)); // Crea la bala
                relojDisparo.restart(); // Reinicia el temporizador
            }
        }
        //detecta tecla espacio para disparar
        //if (GetAsyncKeyState('A') & 0x8000) {
        //    sonido.play();    //reproduce el disparo
        //    B.push_back(new BALA(MINAVE.X() + 2, MINAVE.Y() - 1));
        //}

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
        // colision de las balas
        for (it = B.begin(); it != B.end();) {
            (*it)->mover();

            bool colision = false;

            if (EL_ASTEROIDE.colision_con_bala((*it)->X(), (*it)->Y())) {
                EL_ASTEROIDE.reiniciar();
                colision = true;
            }
            else if (ast1.colision_con_bala((*it)->X(), (*it)->Y())) {
                ast1.reiniciar();
                colision = true;
            }
            else if (ast2.colision_con_bala((*it)->X(), (*it)->Y())) {
                ast2.reiniciar();
                colision = true;
            }
            else if (ast3.colision_con_bala((*it)->X(), (*it)->Y())) {
                ast3.reiniciar();
                colision = true;
            }

            if (colision) {
                (*it)->borrar();
                delete (*it);
                it = B.erase(it);
                puntos += 10;
                mostrar_puntos(puntos);
            }
            else if ((*it)->fuera_de_pantalla()) {
                (*it)->borrar();
                delete (*it);
                it = B.erase(it);
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
        if (MINAVE.Vidas() == 0) {
            explosion.play(); // Reproduce el sonido de disparo
            
            game_over = true;
            music.setLooping(false); //detener la musica
        }
        if (game_over) {
            system("cls"); // Limpia la pantalla
            gotoxy(50, 20);
            cout << "     G A M E   O V E R";
            gotoxy(48, 22);
            cout << "Puntaje final: " << puntos;
            gotoxy(45, 24);
            cout << "Presiona una tecla para salir...";
            
        }

        auto frameEnd = high_resolution_clock::now();
        auto elapsed = duration_cast<milliseconds>(frameEnd - frameStart);

        if (elapsed.count() < frameDelay) {
            //delay en milisegundos
            std::this_thread::sleep_for(milliseconds(frameDelay - elapsed.count()));
        }

    }
    return 0;

}