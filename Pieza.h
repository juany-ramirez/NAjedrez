#pragma once

#include <string>

using std::string;

class Pieza{
        string tipo;
        int posicionFila;
        int posicionColumna;

public://constructores con 
	Pieza(string);
	Pieza(string, int, int);
        ~Pieza();
        string toString()const;
        bool validacionesTodas(int, int, Pieza);
        bool vPeon(int, int, Pieza);
        bool vCaballo(int, int, Pieza);
        bool vTorre(int, int, Pieza);
        bool vReina(int, int, Pieza);
        bool vRey(int, int, Pieza);
        bool vAlfil(int, int, Pieza);
};

