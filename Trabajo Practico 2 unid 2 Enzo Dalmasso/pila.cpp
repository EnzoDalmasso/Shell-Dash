#include "pila.h"

pila::pila(Vector2f posicion_ini)
{

    pos = posicion_ini;//Se utiliza para darle su posicion inicial a los shells

    //Inicializo las sprites
    for (int i = 0; i < 4; i++)
    {
        txt_shell[i] = new Texture();//Inicializo una textura
    }
    //Cargo las texturas de los sprites
    txt_shell[0]->loadFromFile("assets/shell_amarillo.png");
    txt_shell[1]->loadFromFile("assets/shell_rojo.png");
    txt_shell[2]->loadFromFile("assets/shell_azul.png");
    txt_shell[3]->loadFromFile("assets/shell_verde.png");

    //Inicializo los Nodos
    for (int i = 0; i < 4; i++)
    {
        agregarPila(txt_shell[i]);
        pos.x += 50;
    }


    spr_aux = NULL;//Inicializo el sprite vacio


}//Recibe la ventana
void pila::copia_vent1(RenderWindow *ventana)
{
    //Recorro la primera lista
    Nodo* aux;
    if (pila1)
    {
        aux = pila1;
        while (aux)
        {
            //Llamo a la funcion para dibujar y le paso la ventana
            aux->copia_vent1(ventana);
            aux = aux->siguiente;
        }
    }
    if (spr_aux)//Si existe el sprite auxiliar
    {
        mover_Shell();
        ventana->draw(*spr_aux);//Usa la ventana para dibujar el sprite auxiliar
    }
    admin_Shell();

    //Recorro la segunda lista
    Nodo* aux2;
    if (pila2)
    {
        aux2 = pila2;
        while (aux2)
        {
            //Llamo a la funcion para dibujar y le paso la ventana
            aux2->copia_vent1(ventana);
            aux2 = aux2->siguiente;
        }
    }
}

//Agrega un nodo a la lista
void pila::agregarPila(Texture* txt_shells)
{

    Nodo* nuevo_nodo = new Nodo(pos, txt_shells);//Al nuevo nodo le paso la posicion y una textura
    nuevo_nodo->siguiente = pila1;//El siguiente de nuevo_nodo apunta a pila1
    pila1 = nuevo_nodo;//Pila1 es igual a un nuevo_nodo

}

//Agrega un nodo a la segunda lista
void pila::agregarPila2(Texture* txt_shells)
{
    Nodo* nuevo_nodo = new Nodo(pos, txt_shells);
    nuevo_nodo->siguiente = pila2;
    pila2 = nuevo_nodo;

}

//Elimina un nodo de la lista
void pila::sacarPila()
{
    Nodo* aux = pila1;//Creo un auxiliar y lo igualo a la pila 1
    spr_aux = aux->spr_shell;//Guardamos el sprite del nodo en el sprite auxiliar
    txt_aux = aux->txt_shell1;//Guardamos la textura del nodo en la textura auxiliar
    pila1 = aux->siguiente;//Pila1 es igual al siguiente del auxiliar

}

//Elimina un nodo de la segunda lista
void pila::sacarPila2()
{
    Nodo* aux = pila2;
    spr_aux = aux->spr_shell;
    txt_aux = aux->txt_shell1;
    pila2 = aux->siguiente;

}

//Desplazo hacia los costados el sprite auxiliar
void pila::mover_Shell()
{
    
    if (pila_vacia2)//Si la segunda pila esta vacia
    {
        direccion = 1;//Se desplaza hacia la derecha
    }
    if (pila_vacia)//Si la primera pila esta vacia
    {
        direccion = -1;//Se desplaza hacia la izquierda
    }
    spr_aux->setPosition(spr_aux->getPosition().x + 3.5 * direccion, spr_aux->getPosition().y);

}

void pila::admin_Shell()
{
    int lista = 0;//Creo una variable lista para ver la cantidad de Nodos en una lista

    //Recorro la lista
    Nodo* aux;
    
    if (pila1)
    {

        aux = pila1;
        while (aux)//Mientras exista un nodo
        {
            lista++;//Se incrementa la lista
            aux = aux->siguiente;


        }

    }
    //Mismo proceso
    Nodo* aux2;
    int lista2 = 0;

    if (pila2)
    {

        aux2 = pila2;
        while (aux2)
        {
            lista2++;
            aux2 = aux2->siguiente;


        }

    }

    if (lista2 == 4)//Si la lista2 esta llena
    {
        pila_vacia = true;//La pila1 esta vacia
        pila_vacia2 = false;//la pila2 esta llena
        pos.x = 30;//Cambio la posicion donde se van a generar los nodos
    }
    if (lista == 4)//Si la lista1 esta llena
    {
        pos.x = 700;//Cambio la posicion donde se van a generar los nodos
        pila_vacia2 = true;//La pila2 esta vacia
        pila_vacia = false;//La pila1 esta llena
    }

    //Si el shell no esta en movimiento y si alguna de las listas existe
    if (en_mov == false && (pila1 || pila2))
    {
        if (pila_vacia2 == true)//Si pila2 esta vacia
        {
            sacarPila();//Elimina un nodo de la primera pila
        }
        if (pila_vacia == true)//Si pila esta vacia
        {

            sacarPila2();//Elimina un nodo de la segunda pila

        }
        en_mov = true;

    }
    if (spr_aux)//Si el sprite auxiliar existe
    {
        if (sprt_limite())//Paso el limite
        {
            spr_aux = NULL;//Vacio el sprite
            if (pila_vacia)//Si pila1 esta vacia
            {
                agregarPila(txt_aux);//Agrega un nuevo nodo
                pos.x += 50;//Separa del otro nodo
            }
            if (pila_vacia2)//Si pila2 esta vacia
            {
                agregarPila2(txt_aux);//Agrega un nuevo nodo
                pos.x -= 50;//Separa del otro nodo
            }

            en_mov = false;

        }
    }



}
//Detecta si el shell pasa cierta posicion 
bool pila::sprt_limite()
{
    //Si el sprite auxiliar es igual o mayor 750 o 5,y  pila1 o pila2 esta vacia
    if ((spr_aux->getPosition().x >= 750 && pila_vacia2) || (spr_aux->getPosition().x <= 5 && pila_vacia))
    {
        //Paso el limite
        return true;
    }
    return false;
}
Sprite pila::mandar_spr()
{
    if (spr_aux)
    {
        return *spr_aux;
    }
}
