#include "mario.h"
using namespace sf;

using namespace std;

mario::mario()
{
	//Cargo e inicializo las texturas del Mario
	txt_mario.loadFromFile("assets/jumper.png");
	spr_mario_b.setTexture(txt_mario);
	spr_mario_b.setOrigin(txt_mario.getSize().x / 2.f, txt_mario.getSize().y / 2.f);//Seteo el origen de la sprite
	spr_mario_b.setScale(0.9, 0.9);//Seteo la escala del Mario
	spr_mario_b.setPosition(400, 495);//Asigno la posicon al Mario

	//Inicializo las alturas de las plataformas
	plataformas[0] = 493;
	plataformas[1] = 417;
	plataformas[2] = 342;
	plataformas[3] = 265;
	plataformas[4] = 192;
	plataformas[5] = 120;
	plataformas[6] = 44;
	plataformas[7] = 0;

	//Inicializo los limites en donde debe arrancar el personaje
	minimo = plataformas[0];
	maximo = plataformas[1];

	
}


//Recibo la ventana principal para dibujar el sprite
void mario::copia_vent(RenderWindow* ventana)
{
	ventana->draw(spr_mario_b);//usa la ventana para dibujar
	admin_salto();//Llama a la funcion de administrar salto 
}

//Recine una variable entera 
void mario::mover_mario(int desplazamiento)
{
	switch (desplazamiento)//Usa la variable para definir que tipo de desplazamiento
	{
	case 1:
		//Desplazamiento del mario a su izquierda
		spr_mario_b.setPosition(spr_mario_b.getPosition().x - 10.f, spr_mario_b.getPosition().y);
		break;
	case 2:
		//Desplazamiento del mario a su derecha
		spr_mario_b.setPosition(spr_mario_b.getPosition().x + 10.f, spr_mario_b.getPosition().y);
		break;

	case 3:
		//Si esta en el piso
		if (detectar_suelo == true)
		{
			//Cambia el estado a saltando
			detectar_suelo = false;
			personaje_saltando = true;
			
		}

	}
}

//administra la posicion del personaje durante un salto segun su estado
void mario::admin_salto()
{
	detectar_altura();
	//Si se encuentra en el aire sube
	if (personaje_saltando == true)
	{
		spr_mario_b.setPosition(spr_mario_b.getPosition().x, spr_mario_b.getPosition().y - 4);
	}
	//si a colisionado con el limite, pero no toco el piso, baja
	if (personaje_saltando == false && detectar_suelo == false)
	{
		spr_mario_b.setPosition(spr_mario_b.getPosition().x, spr_mario_b.getPosition().y + 4);
	}

}

//administra los cambios de estado segun la posicion en Y
void mario::detectar_altura()
{
	//Si el personaje no esta saltando y esta tocando el suelo
	if (personaje_saltando == false && spr_mario_b.getPosition().y >= minimo)
	{
		detectar_suelo = true;//El personaje esta tocando el suelo o el limite minimo
		
	}
	//Si el personaje esta saltando y llega a su maximo en Y
	if (personaje_saltando == true && spr_mario_b.getPosition().y <= maximo)
	{
		personaje_saltando = false;//El personaje deja de saltar
		actualizar_limites();

	}
	
}
//Esta funcion se utiliza para actualizar los valores requeridos para el salto
void mario::actualizar_limites()
{
	for (int i = 0; i < 8; i++)
	{
		//Si la posicion del mario en Y es mayor a la proxima plataforma
		if (spr_mario_b.getPosition().y <= plataformas[i]&& spr_mario_b.getPosition().y >= plataformas[i + 1])
		{
			minimo = plataformas[i];//Actualiza la posicion minima
			maximo = plataformas[i + 1];//actualiza la posicion maxima

		
		}
	}
}

void mario::caer()
{
	//Reinicio los limites con los valores que se inicializaron en el constructor
	minimo = plataformas[0];
	maximo = plataformas[1];
	detectar_suelo = false;//Fuerza al personaje a caer

}
