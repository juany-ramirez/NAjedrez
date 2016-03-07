#include "Partida.h"
#include "Pieza.h"
#include "Jugador.h"
#include <string>
#include <sstream>

using std::stringstream;
using std::string;

Partida::Partida(Jugador jugador1, Jugador jugador2):
	jugador1(jugador1), jugador2(jugador2){}

Partida::Partida(Jugador jugador1, Jugador jugador2, Pieza*** tablero):
	jugador1(jugador1), jugador2(jugador2), tablero(tablero){}

Partida::~Partida(){

}

Pieza*** Partida::getTablero(){
	return tablero;
}

void Partida::guardarTablero(Pieza*** tablero){

}

Pieza*** Partida::recuperarTablero(){
	
	return tablero;
}






bool Partida::ganadorJuego (Pieza*** tablero){
	bool condicion = false;
	return condicion;
}
