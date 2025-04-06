#include <SFML/Graphics.hpp>
#include <iostream>
#include "mario.h"
#include "cola.h"
#include "pila.h"

using namespace sf;

using namespace std;


class juego
{
public:
	//Constructor
	//Recibe un vector y una variable
	juego(Vector2i resolucion, string titulo);

	//Dibujar en pantalla y el bucle principal(cuando la ventana esta abierta)
	void gameLoop();

	void procesar_eventos();//Procesa el teclado

	void colision();//Procesa la colision del los sprites
	void act_tiempo(int tiempo);//Procesa las variables del tiempo 
	
	void admin_pisos();//Administra 
	void perdida();//Condicion de perder



private:

	RenderWindow* ventana;//Crea pantalla

	//variables para el tiempo global del juego
	Time* tiempo1;
	Clock* reloj1;
	float fps, tiempoFrame, tiempo2;
	float convertir_tiempo;

	//Variable para el teclado(en este caso el mouse y r)
	Event* evento1;
	
	
	//Cargo textura y sprite del fondo de pantalla
	Texture fondo;
	Sprite fondo_pantalla;

	//Cargo textura y sprite de la puerta
	Texture puerta;
	Sprite puerta_s;


	int gameOver;//Variable para perder

	//Variables adicionales de texto
	Text* numeracion[3];
	Font* fuente2;

	//Divide entre //Niveles y //Personaje
	cola* cola1;
	cola* cola2;
	cola* cola3;
	pila* pila1;
	pila* pila2;
	pila* pila3;
	mario m1;


	Sprite spr_temporales[6];// Guardo el sprite activo de cada lista
};