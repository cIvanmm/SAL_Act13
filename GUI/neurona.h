#ifndef NEURONA_H
#define NEURONA_H
#include<map>
#include<vector>
#include<iostream>
#include<stack>
#include"listaneuronas.h"

using namespace std;

class ListaNeuronas;

class Neurona{
private:
    int id;
    float voltaje;
    int posicion_x;
    int posicion_y;
    int red;
    int green;
    int blue;
    friend class ListaNeuronas;
public:
    Neurona(int, float, int, int, int, int, int);
    void print();
    int getnid();
    int getnvoltaje();
    int getnx();
    int getny();
};

class Grafo{
public:
    std::map<Neurona*, std::vector<std::pair<Neurona*, int>>> listaAdyacencia;
    void vaciarListaAdyacencia(){
        listaAdyacencia.clear();
    }
    QString profundidad(Neurona *origen){
        std::map<Neurona *, bool> visitado;
        std::stack<Neurona *> pila;
        pila.push(origen);
        QString cadena, aux;
        cout <<"Las neuronas visitadas son:\n\n";
        cadena =QString("Las neuronas visitadas son:\n\n");
        while(!pila.empty()){
            Neurona *actual =pila.top();
            pila.pop();
            visitado[actual] =true;
            cout <<actual ->getnid() <<"  ";
            aux =QString("%1  ").arg(actual ->getnid());
            cadena +=aux;
            for(const auto &vecino :listaAdyacencia[actual]){
                Neurona *nodoVecino =vecino.first;
                if(!visitado[nodoVecino]){
                    pila.push(nodoVecino);
                }
            }
        }
        cout <<endl;
        return cadena;
    }
};

#endif // NEURONA_H
