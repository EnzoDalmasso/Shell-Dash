#include "juego.h"
using namespace sf;

using namespace std;

juego::juego(Vector2i resolucion, string titulo)
{
	//Inicio lasvariables
	gameOver = 0;

	//Inicializo la ventana principal
	ventana = new RenderWindow(VideoMode(resolucion.x, resolucion.y), titulo);
	ventana->setFramerateLimit(60);

	//Inicializo las variables de tiempo
	reloj1 = new Clock();
	tiempo1 = new Time();
	evento1 = new Event;
	convertir_tiempo = 30;

	//Inicializo colas
	cola1 = new cola({ 130, 420 });
	cola2 = new cola({ 130, 270 });
	cola3 = new cola({ 130, 120 });


	//Inicializo pilas
	pila1 = new pila({ 50,345 });
	pila2 = new pila({ 50,190 });
	pila3 = new pila({ 50,40 });

	//Inicializo las fuentes
	fuente2 = new Font();
	fuente2->loadFromFile("Texto.ttf");


	for (int i = 0; i < 3; i++)
	{
		numeracion[i] = new Text();
		numeracion[i]->setFont(*fuente2);
		numeracion[i]->setFillColor(Color::White);
		numeracion[i]->setOrigin(numeracion[i]->getGlobalBounds().width / 2, numeracion[i]->getGlobalBounds().height / 2);
		numeracion[i]->setCharacterSize(20);
	
	}
	//Defino los textos a dibujar en pantalla
	numeracion[0]->setString(to_string(convertir_tiempo));
	numeracion[0]->setPosition(750, 20);

	numeracion[1]->setString("PERDISTE");
	numeracion[1]->setPosition(300, 250);
	numeracion[1]->setCharacterSize(40);
	numeracion[1]->setCharacterSize(40);

	numeracion[2]->setString("GANASTE");
	numeracion[2]->setPosition(300, 250);
	numeracion[2]->setCharacterSize(40);
	numeracion[2]->setCharacterSize(40);
	

	//Inicializo la textura de fondo
	fondo.loadFromFile("assets/fondo_plataformas.png");
	fondo_pantalla.setTexture(fondo);//Inicializo el sprite de fondo
	fondo_pantalla.setOrigin(fondo.getSize().x / 2.f, fondo.getSize().y / 2.f);//Seteo el origen del fondo
	fondo_pantalla.setPosition(400, 300);//Designo su posicion

	//Inicializo la textura de la puerta
	puerta.loadFromFile("assets/puerta.png");
	puerta_s.setTexture(puerta);//Inicializo el sprite de fondo
	puerta_s.setOrigin(puerta.getSize().x / 2.f, puerta.getSize().y / 2.f);//Seteo el origen del fondo
	puerta_s.setPosition(400, 45);//Designo su posicion

	gameLoop();//Empiezo el gameloop


}
//Bucle principal
void juego::gameLoop()
{
	while (ventana->isOpen())//Si la ventana esta abierta
	{

		while (convertir_tiempo >= 0)//Condiciones de fin de juego(que se acabe el tiempo)

		{
			//Recibo el tiempo de la maquina
			*tiempo1 = reloj1->getElapsedTime();
			if (tiempo2 + tiempoFrame < tiempo1->asSeconds())
			{

				ventana->clear();//Limpio la ventana

				ventana->draw(fondo_pantalla);//Dibujo el fondo
				ventana->draw(puerta_s);//Dibujo la puerta
				//Mientras la condicion de juego no cambie altera esas variables de tiempo
				if (gameOver == 0)
				{
				m1.copia_vent(ventana);//Llamo a la funcion de m1 para dibujar
				procesar_eventos();//Llamo a la funcion para procesar el teclado
				colision();//Reviso colision
				admin_pisos();

				//Texto del tiempo
				ventana->draw(*numeracion[0]);

					convertir_tiempo -= 0.02f;
					act_tiempo(convertir_tiempo);

				}
				if (gameOver==1)
				{
					ventana->draw(*numeracion[2]);
				}
				

				ventana->display();//Muestra en pantalla

			}
		}
		perdida();
		

	}
}

//Envio la ventana a las listas para imprimir nodos y sprites
void juego::admin_pisos()
{
	
	cola1->copia_vent1(ventana);
	spr_temporales[0] = cola1->mandar_spr();
	cola2->copia_vent1(ventana);
	spr_temporales[1] = cola2->mandar_spr();
	cola3->copia_vent1(ventana);
	spr_temporales[2] = cola3->mandar_spr();
	pila1->copia_vent1(ventana);
	spr_temporales[3] = pila1->mandar_spr();
	pila2->copia_vent1(ventana);
	spr_temporales[4] = pila2->mandar_spr();
	pila3->copia_vent1(ventana);
	spr_temporales[5] = pila3->mandar_spr();


}

//Procesa todos los eventos del teclado
void juego::procesar_eventos()
{
	while (ventana->pollEvent(*evento1))
	{
		switch (evento1->type)
		{
			//Cierra la ventana
			case Event::Closed:
			exit(1);
			break;
		
			case Event::KeyPressed:

			{
				if (gameOver == 0)//Si gameover se mantenga en 0 detecta el teclado
				{
					//Llama a la clase personaje y a la funcion mover mario
					if (Keyboard::isKeyPressed(Keyboard::A))
					{
						m1.mover_mario(1);//Para la izquierda

					}
					if (Keyboard::isKeyPressed(Keyboard::D))
					{

						m1.mover_mario(2);//Para la derecha
					}
					if (Keyboard::isKeyPressed(Keyboard::Space))
					{
						m1.mover_mario(3);//Para saltar
						
					}
					
				}
			}
				
		}

	}
}

//Detecta si el sprite del mario colisiona con la puerta o con los shells
void juego::colision()
{
	for (int i = 0; i < 6; i++)
		{
		//Si hay colision entre el mario y un shell 
		if (m1.spr_mario_b.getGlobalBounds().intersects(spr_temporales[i].getGlobalBounds()))
			{
			m1.caer();
			
			}
		}
		//Si hay colision entre el personaje y la puerta
		if (m1.spr_mario_b.getGlobalBounds().intersects(puerta_s.getGlobalBounds()))
		{
		gameOver=1;

		}
			

}
	




//Actializa el timepo acorde al reloj
void juego::act_tiempo(int tiempo)
{

	numeracion[0]->setString(to_string(tiempo));
	numeracion[0]->setPosition(750, 20);
}
//Pantalla game over
void juego::perdida()
{
	ventana->clear();
	ventana->draw(fondo_pantalla);
	ventana->draw(*numeracion[1]);
	ventana->display();

}

