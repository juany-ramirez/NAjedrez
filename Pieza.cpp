#include "Pieza.h"
#include <string>
#include <cmath>
#include <iostream>
#include <curses.h>


using std::string;
using std::abs;
using std::cout;
using std::endl;

Pieza::Pieza(){
}

Pieza::Pieza(string tipo){
   this -> tipo = tipo;
}

Pieza::Pieza(string tipo, int posicionFila, int posicionColumna){
   this -> tipo = tipo;
   this -> posicionColumna = posicionColumna;
   this -> posicionFila = posicionFila;
}

Pieza::~Pieza(){

}

string Pieza::toString()const{
	return tipo;
}

string Pieza::getTipo(){
	return tipo;
}

void Pieza::setTipo(string tipo){
	this -> tipo = tipo;
}

bool Pieza::PiezaContraria(Pieza* p){
	bool condicion = false;
	if(tipo[1]== '1' && (p->tipo)[1]=='2'){
		condicion = true;
	}
	if(tipo[1]== '2' && (p->tipo)[1]=='1'){
		condicion = true;
	}
	return condicion;
}

bool Pieza::saltarsePiezas(Pieza*** tablero, int posibleMovF, int posibleMovC){
	bool condicion = false;
	int difC = posicionColumna - posibleMovC;
	int difF = posicionFila - posibleMovF;
	if(tipo[0] == 'A'){

	}
	return condicion;
}

bool Pieza::validacionesTodas(int posibleMovF, int posibleMovC, Pieza* piezaN){
	bool piezaMovimiento = false;
	if(tipo[0]=='P'){
		piezaMovimiento = vPeon(posibleMovF,posibleMovC, piezaN);
	}
	if(tipo[0]=='C'){
		piezaMovimiento = vCaballo(posibleMovF,posibleMovC, piezaN);
	}
	if(tipo[0]=='T'){
		piezaMovimiento = vTorre(posibleMovF,posibleMovC, piezaN);
	}
	if(tipo[0]=='Q'){
		piezaMovimiento = vReina(posibleMovF,posibleMovC, piezaN);
	}
	if(tipo[0]=='K'){
		piezaMovimiento = vRey(posibleMovF,posibleMovC, piezaN);
	}
	if(tipo[0]=='A'){
		piezaMovimiento = vAlfil(posibleMovF,posibleMovC, piezaN);
	}
	return piezaMovimiento;
}

bool Pieza::vPeon(int posibleMovF, int posibleMovC, Pieza* piezaN){
	bool condicion = false;
	int difC = posicionColumna - posibleMovC;
    int difF = posicionFila - posibleMovF;
    if(difF == 0 && piezaN->tipo == "V ") {//Movida VerticaL      
        if(abs(difC) == 1){		//Si mueve un casillero
            condicion= true;
        }
    }else{
   		if(difF == 1 && difC == 1){
   			if(PiezaContraria(piezaN))
   				condicion = true;
   		}
    }
	
	return condicion;
}

bool Pieza::primeraVPeon(int posibleMovF, int posibleMovC){
	bool condicion = false;
	int difC = posicionColumna - posibleMovC;
    int difF = posicionFila - posibleMovF;
    printw("%i", difF);
    printw("\n");
    printw("%i", difC);
    if(difF == 0){//Movida VerticaL 
    	if(abs(difC) == 2){ 	//Movida larga de peon
	        condicion = true;
	    }
	}
    return condicion;
}

bool Pieza::vCaballo(int posibleMovF, int posibleMovC, Pieza* piezaN){
	bool condicion = false;
	int movFila = 3;
	int movColumna = 3;
	return condicion;
}

bool Pieza::vTorre(int posibleMovF, int posibleMovC, Pieza* piezaN){
	bool condicion = false;
	int difC = posicionColumna - posibleMovC;
    int difF = posicionFila - posibleMovF;
	if(((difF == 0) || (difC == 0))&&(piezaN->tipo=="V "))

	return condicion;
}

bool Pieza::vReina(int posibleMovF, int posibleMovC, Pieza* piezaN){
	bool condicion = false;
	int movFila = 8;
	int movColumna = 8;
	return condicion;
}

bool Pieza::vRey(int posibleMovF, int posibleMovC, Pieza* piezaN){
	bool condicion = false;
	int movFila = 8;
	int movColumna = 8;
	return condicion;
}

bool Pieza::vAlfil(int posibleMovF, int posibleMovC, Pieza* piezaN){
	// se puede mover si el numero de columna y fila es igual 
	bool condicion = false;
	int difC = posicionColumna - posibleMovC;
    int difF = posicionFila - posibleMovF;
    if(abs(difF) == abs(difC) && piezaN->getTipo() == "V ")
    	condicion = true;
	return condicion;
}