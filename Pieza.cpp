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

bool Pieza::saltarsePiezas(Pieza*** tablero, int posibleMovF, int posibleMovC,Pieza* piezaN){
	bool condicion = false;
	int difC = posicionFila - posibleMovF;
    int difF = posicionColumna - posibleMovC;

	int mayorColumna = posicionColumna;
	int mayorFila = posicionFila;
	
	if(posicionColumna<posibleMovC)
		mayorColumna = posibleMovC;
	if(posicionFila<posibleMovF)
		mayorFila = posibleMovF;


	char tipoPieza = (tablero[posicionFila][posicionColumna]->getTipo())[0];
	if( tipoPieza == 'Q'  || tipoPieza == 'T'){
		if(((difF == 0) || (difC == 0))&&(piezaN->tipo=="V " || PiezaContraria(piezaN))){
			condicion = true;
			difC = abs(difC);
			if(difF==0){
				for (int i = 0; i < difC; i++){
					if(tablero[posicionFila][mayorColumna]-> getTipo() != "V ")
						condicion = false;
					mayorColumna--;
				}
			}
			difF = abs(difF);
			if(difC==0){
				for (int i = 0; i < difF; i++){
					if(tablero[mayorFila][posicionColumna]-> getTipo() != "V ")//revisaresto
						condicion = false;
					mayorFila--;
				}
			}
		}
	}
	if(tipoPieza == 'Q' || tipoPieza == 'A' ){
		if((abs(difF) == abs(difC)) && (piezaN->getTipo() == "V " || PiezaContraria(piezaN))){
			condicion = true;
			difF = abs(difF);
			if(posibleMovF > posicionFila && posibleMovC > posicionColumna){//ABAJO && DERECHA
				for (int i = 0; i < difF; i++){
					if(tablero[posicionFila][posicionColumna]-> getTipo() != "V ")
						condicion = false;
					posicionFila++;
					posicionColumna++;
				}
			}
			if(posibleMovF < posicionFila && posibleMovC > posicionColumna){//ARRIBA && DERECHA
				for (int i = 0; i < difF; i++){
					if(tablero[posicionFila][posicionColumna]-> getTipo() != "V ")
						condicion = false;
					posicionFila--;
					posicionColumna++;
				}
			}
			if(posibleMovF < posicionFila && posibleMovC < posicionColumna){//ARRIBA && IZQUIERDA
				for (int i = 0; i < difF; i++){
					if(tablero[posicionFila][posicionColumna]-> getTipo() != "V ")
						condicion = false;
					posicionFila--;
					posicionColumna--;
				}
			}
			if(posibleMovF > posicionFila && posibleMovC < posicionColumna){//ABAJO && IZQUIERDA
				for (int i = 0; i < difF; i++){
					if(tablero[posicionFila][posicionColumna]-> getTipo() != "V ")
						condicion = false;
					posicionFila++;
					posicionColumna--;
				}
			}
		}
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
	if(tipo[0]=='K'){
		piezaMovimiento = vRey(posibleMovF,posibleMovC, piezaN);
	}
	
	return piezaMovimiento;
}

bool Pieza::vPeon(int posibleMovF, int posibleMovC, Pieza* piezaN){
	bool condicion = false;
	int difC = posicionFila - posibleMovF;
    int difF = posicionColumna - posibleMovC;
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
	int difC = posicionFila - posibleMovF;
    int difF = posicionColumna - posibleMovC;
    if(difF == 0){//Movida VerticaL 
    	if(abs(difC) == 2 || abs(difC) == 1 ){ 	//Movida larga de peon
	        condicion = true;
	    }
	}
    return condicion;
}

bool Pieza::vCaballo(int posibleMovF, int posibleMovC, Pieza* piezaN){
	bool condicion = false;
	int difC = posicionColumna - posibleMovC;
    int difF = posicionFila - posibleMovF;
	if(((abs(difF) == 2) && (abs(difC) == 1)) || ((abs(difF) == 1) && (abs(difC) == 2)))
		condicion = true;
	return condicion;
}

bool Pieza::vRey(int posibleMovF, int posibleMovC, Pieza* piezaN){
	bool condicion = false;
	int difC = posicionFila - posibleMovF;
    int difF = posicionColumna - posibleMovC;

    if(((abs(difC) == 1)  && (abs(difF) == 1)))
    	condicion = true;
	return condicion;
}
