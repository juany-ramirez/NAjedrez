#include "Pieza.h"
#include <string>
#include <cmath>


using std::string;
using std::abs;


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

string Pieza::toString(){
	return tipo;
}

bool Pieza::validacionesTodas(int posibleMovF, int posibleMovC, Pieza piezaN){
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

bool Pieza::vPeon(int posibleMovF, int posibleMovC, Pieza piezaN){
	bool condicion = false;
	//if peon si es el primer movimiento de un peon, entonces se mueve dos veces
	int difC = posicionColumna - posibleMovC;
    int difF = posicionFila - posibleMovF;
    if(difF == 0 && piezaN.tipo == "V") {//Movida VerticaL      
        if(abs(difC) == 1){//Si mueve un casillero
            condicion= true;
        }
        if(abs(difC) == 2){ //Movida larga de peon
            condicion = true;
        }
    }else{
   		if(difF == 1 && difC ==1){
   			condicion = true;
   		}
    }
	
	return condicion;
}

bool Pieza::vCaballo(int posibleMovF, int posibleMovC, Pieza piezaN){
	bool condicion = false;
	int movFila = 3;
	int movColumna = 3;
	return condicion;
}

bool Pieza::vTorre(int posibleMovF, int posibleMovC, Pieza piezaN){
	bool condicion = false;
	int movFila = 8;
	int movColumna = 0;
	return condicion;
}

bool Pieza::vReina(int posibleMovF, int posibleMovC, Pieza piezaN){
	bool condicion = false;
	int movFila = 8;
	int movColumna = 8;
	return condicion;
}

bool Pieza::vRey(int posibleMovF, int posibleMovC, Pieza piezaN){
	bool condicion = false;
	int movFila = 8;
	int movColumna = 8;
	return condicion;
}

bool Pieza::vAlfil(int posibleMovF, int posibleMovC, Pieza piezaN){
	// se puede mover si el numero de columna y fila es igual 
	bool condicion = false;
	int movFila = 8;
	int movColumna = 8;
	return condicion;
}