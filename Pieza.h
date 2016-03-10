#pragma once

#include <string>

using std::string;

class Pieza{
        string tipo;
        int posicionFila;
        int posicionColumna;

public://constructores con 
        Pieza();
        Pieza(string);
        Pieza(string, int, int);
        ~Pieza();
        string toString()const;
        string getTipo();
        void setTipo(string);
        bool saltarsePiezas(Pieza***, int, int,Pieza*);
        bool PiezaContraria(Pieza*);
        bool validacionesTodas(int, int, Pieza*);
        bool vPeon(int, int, Pieza*);
        bool primeraVPeon(int, int);
        bool vCaballo(int, int, Pieza*);
        bool vRey(int, int, Pieza*);
};

