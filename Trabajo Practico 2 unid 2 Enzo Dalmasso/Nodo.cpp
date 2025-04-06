#include "Nodo.h"

//Va a recibir una posicion y una textura
Nodo::Nodo(Vector2f pos, Texture* txt_shell2)
{
    txt_shell1 = new Texture();//Inicializo una textura
    txt_shell1 = txt_shell2; //Uso la textura que recibo y la asigno a la del nodo
    spr_shell = new Sprite(*txt_shell2);//Inicializo el sprite con la textura recibida
    spr_shell->setPosition(pos);//Recibe una posicion y se la pasa al sprite
}

//Recibe la ventana 
void Nodo::copia_vent1(RenderWindow* ventana)
{
    ventana->draw(*spr_shell);//usa la ventana para dibujar  
}
