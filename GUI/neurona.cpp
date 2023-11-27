#include "neurona.h"

Neurona::Neurona(int id, float voltaje, int posicion_x, int posicion_y, int red, int green, int blue)
{
    this ->id =id;
    this ->voltaje =voltaje;
    this ->posicion_x =posicion_x;
    this ->posicion_y =posicion_y;
    this ->red =red;
    this ->green =green;
    this ->blue =blue;
}

int Neurona::getnid(){
    return this ->id;
}

int Neurona::getnvoltaje(){
    return this ->voltaje;
}

int Neurona::getnx(){
    return this ->posicion_x;
}

int Neurona::getny(){
    return this ->posicion_y;
}
