#pragma once
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>

using namespace std;

using namespace sf;

class Nodo
{
private:

    Sprite* spr_shell;

    Texture* txt_shell1;

    //Concede acceso a estas clases
    friend class cola;
    friend class pila;

public:
    //Constructor
    //Recibe un vector y una textura
    Nodo(Vector2f pos, Texture* txt_shell);

    //Recibe una variable de tipo ventana
    void copia_vent1(RenderWindow* ventana);

    //Es un puntero que apunta al siguiente nodo
    Nodo* siguiente;
};

