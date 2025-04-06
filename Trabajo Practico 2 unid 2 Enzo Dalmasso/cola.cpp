#include "cola.h"

//Va a recibir una posicion
cola::cola(Vector2f posicion_ini)
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
        insertarCola(pos, txt_shell[i]);
        pos.x -= 50;
    }

    
    spr_aux = NULL;//Inicializo el sprite vacio

}
//Recibe la ventana
void cola::copia_vent1(RenderWindow* ventana)
{
    Nodo* aux;//Creo un nodo auxiliar

    if (principio != NULL)//Si existe la lista
    {
        aux = principio;//Auxiliar iguala el primer nodo de la lista

        while (aux)//Mientras auxiliar exista
        {
            aux->copia_vent1(ventana);//Llamo a la funcion para dibujar y le paso la ventana
            aux = aux->siguiente;//Pasa al siguiente nodo
        }

    }
    if (spr_aux)//Si existe el sprite auxiliar
    {
        mover_Shell();
        ventana->draw(*spr_aux);//Usa la ventana para dibujar el sprite auxiliar
    }
    admin_Shell();
}

//Agrega un nodo a la lista
void cola::insertarCola(Vector2f pos, Texture* txt_shells)
{
    Nodo* nuevo_nodo = new Nodo(pos, txt_shells);//Al nuevo nodo le paso una posicion y una textura

    nuevo_nodo->siguiente = NULL;//Hacemos que el puntero apunte a null

    if (principio == NULL)//Si la lista no existe
    {
        principio = nuevo_nodo;//El nuevo nodo sera el principio
    }
    else
    {
        fin->siguiente = nuevo_nodo;//El fin apunta a este nodo 
    }
    fin = nuevo_nodo;//El nuevo nodo ahora es el ultimo
}


void cola::eliminarCola()
{

    Nodo* aux = principio;//Creo un nodo auxiliar y lo iguala al primer nodo
    spr_aux = aux->spr_shell;//Guardamos el sprite del nodo en el sprite auxiliar
    txt_aux = principio->txt_shell1;//Guardamos la textura del nodo en la textura auxiliar


    if (principio == fin)//Si es el unico nodo 
    {

        //Vacia la lista
        principio = NULL;
        fin = NULL;

    }
    else
    {
        
        principio = principio->siguiente;//En caso contrario igualka al nodo siguiente
    }
    delete aux;//Elimina el auxiliar
}

//Desplazo hacia los costados el sprite auxiliar
void cola::mover_Shell()
{
    spr_aux->setPosition(spr_aux->getPosition().x + 3.5, spr_aux->getPosition().y);
}

void cola::admin_Shell()
{
    //Si el shell no esta en movimiento y si la lista existe
    if (en_mov == false && principio)
    {
        eliminarCola();//Elimino un nodo
        empujarNodo();//Empuja a los nodos
        en_mov = true;//Movimiento es verdadero

    }
    if (spr_aux)//Si existe el sprite auxiliar
    {
        if (sprt_limite())//Paso el limite
        {
            spr_aux = NULL;//Vacio el sprite
            pos.x = 0;
            insertarCola(pos, txt_aux);//Agrega un nodo a la lista
            en_mov = false;//Avisa que el sprite deja de moverse
        }
    }


}

//Detecta si el shell pasa cierta posicion 
bool cola::sprt_limite()
{
    if (spr_aux->getPosition().x >= 750)//Si el sprite auxiliar es igual o mayor a 750
    {
        //Paso el limite
        return true;
    }
    return false;
}

void cola::empujarNodo()
{
    //Recorre la lista
    Nodo* aux;

    if (principio != NULL)
    {
        aux = principio;

        while (aux)
        {
            //Le indico al sprite del nodo que se tiene que desplazar hacia el costado
            aux->spr_shell->setPosition(aux->spr_shell->getPosition().x + 50, aux->spr_shell->getPosition().y);
            aux = aux->siguiente;
        }
    }

}

Sprite cola::mandar_spr()
{
    if (spr_aux)
    {
        return *spr_aux;
    }
}
