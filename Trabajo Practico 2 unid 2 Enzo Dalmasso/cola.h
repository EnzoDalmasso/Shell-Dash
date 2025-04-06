#pragma once
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include "Nodo.h"


using namespace std;

using namespace sf;

class cola
{

public:
    //Constructor
   //Recibe un vector 
    cola(Vector2f posicion_ini);

    void copia_vent1(RenderWindow* ventana);//Recibe una variable de tipo ventana

    void insertarCola(Vector2f pos, Texture* txt_shells);//Recibe un vector y una textura y añade un nodo
    void eliminarCola();//Elimina un nodo de la lista
    void mover_Shell();//Movimiento de los shells
    void admin_Shell();//Administra el estado de las listas
    bool sprt_limite();//Esta funcion sirve para darle un limite al shell
    void empujarNodo();//Mueve todos los nodos hacia los costados

    Sprite mandar_spr();//Devuelve un sprite

private:
    bool en_mov = false;//Se utiliza para verificar que la shell este en movimiento 

    Texture* txt_shell[4];

    Vector2f pos;//Variable para almacenar una pos


    Sprite* spr_aux;
    Texture* txt_aux;

    //Punteros que marcan el principio y el fin de la lista
    Nodo* principio = NULL;
    Nodo* fin = NULL;


};


