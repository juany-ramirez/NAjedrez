#include "Pieza.h"
#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <ncurses.h>
#include <curses.h>
#include <sstream>
#include <fstream>

using std::ifstream;
using std::ofstream;
using std::endl;
using std::cout;
using std::cin;
using std::strlen;
using std::string;
using std::stringstream;

void impresionTablero(Pieza***);
bool jaqueMate(Pieza***);
void impresionLinea();
int coordenadaConsonante(char);
void crearPiezas(Pieza***);
Pieza*** crearTablero();
void eliminarTablero(Pieza***);
void guardarTablero(Pieza***);
void abrirTablero(Pieza***);
bool saltarsePiezas(Pieza***);
void impresionMenu();


int main(int argc, char*argv[]){
	initscr();
	start_color();
	scrollok(curscr,TRUE);

	init_pair(1, COLOR_RED,     COLOR_BLACK);
    init_pair(2, COLOR_GREEN,   COLOR_BLACK);
    init_pair(3, COLOR_CYAN,    COLOR_BLACK);
    init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(5, COLOR_WHITE,   COLOR_BLACK);
	
    impresionMenu();

	noecho();
	char ans;
	bool validMenu = false;
	while (validMenu == false){
		ans = getch();
		if(ans >= '0' && ans <= '3'){
			echo();
			addch(ans);
			validMenu = true;
		}
	}
	Pieza*** tablero = NULL;
	char jugadorNum= '1';
	bool primerPeonGuardado = false;

	while(ans == '1' || ans == '2'){
		
		clear();
		refresh();
		
		if(ans == '1'){
			tablero = crearTablero();
			eliminarTablero(tablero);
			tablero = crearTablero();
		}
		if(ans == '2'){
			abrirTablero(tablero);
			primerPeonGuardado = true;
		}
		int turnoJugador=1;
		bool condicionGuardado = true;
		string cambioPieza;
		while((!jaqueMate(tablero)) && (condicionGuardado)){

			impresionTablero(tablero);
			
			int numberCounter = 0;
			char coordenadas[5];
			int opcionCoordenadas;

			//			 VALIDACION DE ENTRADA DE DATOS
			do{
				while(numberCounter < 5){
					noecho();
					char temp;
					temp = getch();
					if(numberCounter%2){
						if(temp >= '0' && temp <= '8'){
							echo();
							addch(temp);
							coordenadas[numberCounter] = temp;
							numberCounter++;
						}
					}else{
						if((temp >= 65 && temp <= 73) || (temp >= 97 && temp <= 105)){
							echo();
							addch(temp);
							coordenadas[numberCounter] = temp;
							numberCounter++;
						}
					}
					if(numberCounter==4){
						numberCounter++;
						coordenadas[4]='\0';
					}
				}
				numberCounter = 0;
				printw("\n");
				attron(COLOR_PAIR(4));
				printw(" 1. Ingresar coordenada ");
				attroff(COLOR_PAIR(4));
				attron(COLOR_PAIR(3));
				printw(" 2. Cambiar coordenada");
				attroff(COLOR_PAIR(3));
				attron(COLOR_PAIR(2));
				printw(" 3. Guardar Partida");	
				attroff(COLOR_PAIR(2));

				opcionCoordenadas = getch();
		
				impresionTablero(tablero);
			}while(opcionCoordenadas=='2');

			//							GUARDAR TABLERO
			if(opcionCoordenadas == '3'){
				guardarTablero(tablero);
				condicionGuardado = false;
			}

			int posCol = coordenadaConsonante(coordenadas[0]), posFila = coordenadas[1]-'0';
			int posibleMovC = coordenadaConsonante(coordenadas[2]), posibleMovF = coordenadas[3]-'0';
			/*
			printw("%s",tablero[posFila][posCol]->getTipo().c_str());
			printw("\n");
			printw("%c",(tablero[posFila][posCol]->getTipo())[1]);
			printw("\n");
*/
			bool movimientoValido = false;

			//							VALIDACIONES PARA MOVER PIEZAS
			char tipoPieza = (tablero[posFila][posCol]->getTipo())[0];
			if ((tablero[posFila][posCol]->getTipo()!="V ") && ((tablero[posFila][posCol]->getTipo())[1] == jugadorNum)) {
				if(turnoJugador<3 && (tipoPieza== 'P' && !primerPeonGuardado)){
					movimientoValido = tablero[posFila][posCol]->primeraVPeon(posibleMovF,posibleMovC);
				}else{
					if(tipoPieza == 'Q' || tipoPieza == 'T' || tipoPieza == 'A')
						movimientoValido = tablero[posFila][posCol]->saltarsePiezas(tablero,posibleMovF,posibleMovC,tablero[posibleMovF][posibleMovC]);
					else
						movimientoValido = tablero[posFila][posCol]->validacionesTodas(posibleMovF,posibleMovC,tablero[posibleMovF][posibleMovC]);
				}
			}else{
				printw("\n");
				printw("No se pueden mover las piezas del jugador opuesto ni posiciones vacias \n");
				printw("[Presionar cualquier tecla para continuar] \n");
			}

			//							INTERCAMBIO DE LAS PIEZAS

			if(movimientoValido){
				printw("%s",(tablero[posFila][posCol]->getTipo()).c_str());
				//cambioPieza = tablero[posFila][posCol]->toString();
				tablero[posibleMovF][posibleMovC]->setTipo(tablero[posFila][posCol]->toString());
				tablero[posFila][posCol]->setTipo("V ");
			}else{
				printw("validacion NO CUENTA");
			}
			printw("\n");
			printw("%s",(tablero[posibleMovF][posibleMovC]->getTipo()).c_str());
			printw("\n");
			printw("\n");
			printw("%s",(tablero[posFila][posCol]->getTipo()).c_str());
			printw("\n");

			if(turnoJugador%2){			//Turno Jugador 2
				turnoJugador = 1;
				jugadorNum= '1';
			}else{						//Turno Jugador 1
				turnoJugador = 2;
				jugadorNum= '2';
			}
			turnoJugador++;
			//if(!movimientoValido)
			getch();
		}

		impresionMenu();

		validMenu = false;
		while (validMenu == false){
			ans = getch();
			if(ans >= '0' && ans <= '3'){
				echo();
				addch(ans);
				validMenu = true;
			}
		}

	}

	eliminarTablero(tablero);
	endwin();
	return 0;
}


bool jaqueMate(Pieza*** tablero){
	int cont=0;
	for (int i = 0; i < 8; ++i){
		for (int j = 0; j < 8; ++j){
			if((tablero[i][j]->toString() == "K1") || (tablero[i][j]->toString() == "K2")){
				cont++;
			}
		}
	}
	if (cont==1)
	{
		return true;
	}
	return false;
}

void impresionTablero(Pieza*** matriz){
	clear();
	attroff(A_BOLD);
	int width, height;

	init_pair(1, COLOR_CYAN,    COLOR_BLACK);
    init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(3, COLOR_BLACK,	COLOR_WHITE);
	init_pair(4, COLOR_RED,		COLOR_BLACK);

	getmaxyx(curscr,height,width);
	int move_this_y_1 = (height/2)-1;
	int move_this_y_2 = (height/2)+1;
	move(move_this_y_1-8,(width/2)-20);

	char letras[] = "ABCDEFGH";
	printw ("\n\t\t");
	for(int i=0; i<8; i++){
		printw("%i",i);
		printw("\t\t");
	}
	printw ("\n\n");
	int bandera=3;
	for(int i=0; i<8; i++){
		printw("%c",letras[i]);
		printw("\t");
        for(int j=0; j<8; j++){
            printw("|");
            attron(COLOR_PAIR(bandera));
            printw("       ");
            if(matriz[i][j]->toString() != "V ")
            	addstr (matriz[i][j] -> toString().c_str());
            else
            	printw("  ");
            printw("       ");
            attroff(COLOR_PAIR(bandera));
            if(bandera%2)//Turno jugador 2
            	bandera = 4;
			else
				bandera = 3;
		}
        if(i%2)
        	bandera=3;
        else
        	bandera=4;
        printw("|");
    	impresionLinea();
    }
    return;
}

void impresionMenu(){
	
    init_pair(2, COLOR_GREEN,   COLOR_BLACK);
    init_pair(3, COLOR_CYAN,    COLOR_BLACK);
    init_pair(4, COLOR_MAGENTA, COLOR_BLACK);

    int width, height;
	getmaxyx(curscr,height,width);
	int move_this_y_1 = (height/2)-1;
	int move_this_y_2 = (height/2)+1;


	clear();
	refresh();

	attron(A_BOLD);

	attron(COLOR_PAIR(4));
	mvprintw(move_this_y_1-1,(width-strlen(" JUEGO DE AJEDREZ "))/2," JUEGO DE AJEDREZ ");
	attroff(COLOR_PAIR(4));
	attron(COLOR_PAIR(3));
	mvprintw(move_this_y_1,(width-strlen("1.-) Nueva Partida"))/2,"1.-) Nueva Partida");
	attroff(COLOR_PAIR(3));
	attron(COLOR_PAIR(2));
	mvprintw(height/2,(width-strlen("2.-) Abrir Partida"))/2,"2.-) Abrir Partida");	
	attroff(COLOR_PAIR(2));
	attron(COLOR_PAIR(1));
	mvprintw(move_this_y_2,(width-strlen("3.-) Salir."))/2,"3.-) Salir.");
	attroff(COLOR_PAIR(1));

}

void impresionLinea(){
	printw ("\n\t");
	for(int j=0; j<129; j++){
		printw("-");
	}
	printw ("\n");
}

///*********************PARTE DE CLASE PARTIDA
void eliminarTablero(Pieza*** tablero){
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			delete tablero[i][j];
		}		
	}
	for(int i=0;i<8;i++){
		delete[] tablero[i];
	}
	delete[] tablero;
}

Pieza*** crearTablero(){
	Pieza*** tablero = new Pieza**[8];
	for(int i=0;i<8;i++){
		tablero[i]= new Pieza*[8];		
	}
	for(int i=0 ; i<8 ; i++){
		for(int j=0 ; j<8 ; j++){
			tablero[i][j] = NULL;
		}
	}
	crearPiezas(tablero);
	return tablero;
}

void crearPiezas(Pieza*** tablero){
	for(int i=0 ; i<8 ; i++){
		tablero[1][i] = new Pieza("P1",1,i);
	}
	tablero[0][0] = new Pieza("T1",0,0);
	tablero[0][7] = new Pieza("T1",0,7);
	tablero[0][1] = new Pieza("C1",0,1);
	tablero[0][6] = new Pieza("C1",0,6);
	tablero[0][2] = new Pieza("A1",0,2);
	tablero[0][5] = new Pieza("A1",0,5);
	tablero[0][3] = new Pieza("K1",0,3);
	tablero[0][4] = new Pieza("Q1",0,4);
	for(int i=0 ; i<8 ; i++){
		tablero[6][i] = new Pieza("P2",6,i);
	}
	tablero[7][0] = new Pieza("T2",7,0);
	tablero[7][7] = new Pieza("T2",7,7);
	tablero[7][1] = new Pieza("C2",7,1);
	tablero[7][6] = new Pieza("C2",7,6);
	tablero[7][2] = new Pieza("A2",7,2);
	tablero[7][5] = new Pieza("A2",7,5);
	tablero[7][3] = new Pieza("K2",7,3);
	tablero[7][4] = new Pieza("Q2",7,4);
	for(int i=0 ; i<8 ; i++){
		for(int j=0 ; j<8 ; j++){
			if(tablero[i][j]=='\0')
				tablero[i][j] = new Pieza("V ",i,j);
		}
	}
	for(int i=0; i<8; i++)
        for(int j=0; j<8; j++){
        	tablero[i][j] -> toString();
	return;
	}
}

int coordenadaConsonante(char coordenada){
	int fila=0;
	if(coordenada == 'a' || coordenada == 'A')
		return 0;
	if(coordenada == 'b' || coordenada == 'B')
		return 1;
	if(coordenada == 'c' || coordenada == 'C')
		return 2;
	if(coordenada == 'd' || coordenada == 'D')
		return 3;
	if(coordenada == 'e' || coordenada == 'E')
		return 4;
	if(coordenada == 'f' || coordenada == 'F')
		return 5;
	if(coordenada == 'g' || coordenada == 'G')
		return 6;
	if(coordenada == 'h' || coordenada == 'H')
		return 7;
}


void guardarTablero(Pieza*** tablero){
	ofstream datos;
	datos.open("Tablero.txt");
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++){
			datos<< i;
			datos<< j;
			datos<< tablero[i][j] -> toString();
		}
	}
	datos.close();
}

void abrirTablero(Pieza*** tablero){
	int fila, columna;
	string tipo;
	ifstream datos("Tablero.txt");
	datos>> tipo;
	datos>> fila;
	datos>> columna;
	while(!datos.eof()){
		tablero[fila][columna] = new Pieza(tipo, fila, columna);
		datos>> tipo;
		datos>> fila;
		datos>> columna;
	}
	datos.close();
}

bool saltarsePiezas(Pieza*** tablero, Pieza p, int i, int j, int pI, int pJ){

}


