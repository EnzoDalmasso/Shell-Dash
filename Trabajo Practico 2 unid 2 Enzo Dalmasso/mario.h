#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

using namespace std;

class mario
{
public:
	//Constructor
	mario();

	//Recibe una variable de tipo ventana
	void copia_vent(RenderWindow* ventana);

	//Esta funcion realiza el desplazamiento del mario
	void mover_mario(int desplazamiento);

	void admin_salto();//Esta funcion administra el salto
	void detectar_altura();//Detecta la altura del mario
	void actualizar_limites();//Actualiza el limite minimo y maximo para el salto del personaje
	void caer();//Esta funcion se utiliza para reiniciar los limites y hacer que el personaje caiga




	Sprite spr_mario_b;

	

private:
	bool detectar_suelo = true;//Booleano que detecta si el personaje esta en el suelo
	bool personaje_saltando = false;//Booleano que detecta si el personaje esta  saltando
	bool toco_puerta = false;//Booleano que detecta si el personaje esta colisionando con el sprite de la puerta
	
	
	int plataformas[8];//Posicion en Y de las plataformas
	
	//variables para establecer limites
	int minimo;
	int maximo;

	Texture txt_mario;

};

