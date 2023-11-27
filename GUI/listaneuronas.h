#ifndef LISTANEURONAS_H
#define LISTANEURONAS_H
#include<QVector>
#include"neurona.h"

class Neurona;
class Grafo;

class ListaNeuronas{
private:
    QVector<Neurona> neuronas;
public:
    Grafo *grafo;
    ListaNeuronas();
    void agregar_inicio(Neurona);
    void agregar_final(Neurona);
    int cant_neuronas();
    Neurona *getneurona(int);
    int getid(int);
    float getvoltaje(int);
    int getx(int);
    int gety(int);
    int getred(int);
    int getgreen(int);
    int getblue(int);
    void quickSort(int);
    void recursivo(int, int, int);
    int particion(int, int, int);
    bool comparar(float, float);
};

#endif // LISTANEURONAS_H
