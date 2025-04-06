#pragma once

#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include "Nodo.h"

using namespace std;

using namespace sf;

class pila
{
    public:
    //Constructor
    //Recibe un vector 
    pila(Vector2f posicion_ini);

    void copia_vent1(RenderWindow* ventana);//Recibe una variable de tipo ventana

    void agregarPila(Texture* txt_shells);//Recibe una textura y añade un nodo
    void agregarPila2(Texture* txt_shells);//Recibe una textura y añade un nodo

    void sacarPila();//Elimina un nodo de la lista
    void sacarPila2();//Elimina un nodo de la lista 2

    void mover_Shell();//Movimiento de los shells
    void admin_Shell();//Administra el estado de las listas

    bool sprt_limite();//Esta funcion sirve para darle un limite al shell

    Sprite mandar_spr();//Devuelve un sprite
private:
  
    bool en_mov = false;//Se utiliza para verificar que la shell este en movimiento 
    bool pila_vacia2 = false; //Verifica si la pila 2 esta vacia
    bool pila_vacia = false; //Verifica si la pila 1 esta vacia

    int direccion;//Indica la direccion del movimiento

    Texture* txt_shell[4];

    Sprite* spr_aux;
    Texture* txt_aux;

    Vector2f pos;

    //Punteros que marcan la lista vacia
    Nodo* pila1 = NULL;
    Nodo* pila2 = NULL;
};

