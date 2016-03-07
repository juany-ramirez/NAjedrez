#include "Pieza.h"
#include <iostream>
#include <string>
#include <cstring>
#include <ncurses.h>
#include <curses.h>
#include <sstream>

using std::endl;
using std::cout;
using std::strlen;
using std::string;
using std::stringstream;

void impresionTablero(Pieza***);
bool jaqueMate(Pieza***);
void impresionLinea();

/*
	como se crea de manera dinamica un arreglo de objetos

	*****ACORDARME QUE ESTOY HACIENDO USO DE LA MEMORIA DINAMICA // Hay que delete
	la pieza nula por defecto es la V
	el constructor por defecto tiene que tener el colochito? se lo quite

							VALIDACIONES
	-Ver si se puede mover la pieza (porque al principio no se puede)
	-Validacion de movimientos para cada pieza.
	-Metodo de condiciones, if (posicion=='L'){llamar a getPeon() retorne coordenadas con un struct}
	-Validaciones de comerse la pieza, esto depende de si se puede mover a ese lugar.
	-Validacion de que no se puede mover a una posicion de su mismo equipo.
	-Validacion de Jaque, tiene que revisar todos los movimientos de todas las piezas para saber si se puede comer a la reina.
	-Jaque mate, cuando se comen al rey.

*****USAR LA VALIDACION DEL LAB PARA INGRESAR LOS DATOS
*/
void crearPiezas(Pieza***);
Pieza*** crearTablero();
void eliminarTablero(Pieza***);

int main(int argc, char*argv[]){

    int width, height;
	initscr();
	start_color();
	scrollok(curscr,TRUE);


	init_pair(1, COLOR_RED,     COLOR_BLACK);
    init_pair(2, COLOR_GREEN,   COLOR_BLACK);
    init_pair(3, COLOR_CYAN,    COLOR_BLACK);
    init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(5, COLOR_WHITE,   COLOR_BLACK);


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

	char ans = getch();

	while(ans == '1' || ans == '2'){
		clear();
		refresh();
		Pieza*** tablero = NULL;
		if(ans == '1'){
			tablero = crearTablero();
		}
		if(ans == '2'){

		}
		int turnoJugador=1;
		while(!jaqueMate(tablero)){//cambiar a while
			clear();
			
			impresionTablero(tablero);
			
			int numberCounter = 0;
			char coordenadas[5];
			while(numberCounter < 5){
				noecho();
				char temp;
				temp = getch();
				if(!temp%2){
					if(temp >= '0' && temp <= '9' && numberCounter != 2){
						echo();
						addch(temp);
						coordenadas[numberCounter] = temp;
						numberCounter++;
					}
					if(numberCounter == 2  && temp == '-'){
						echo();
						addch(temp);
						coordenadas[numberCounter] = temp;
						numberCounter++;
					}
				}else{
					if(temp >= 65 && temp <= 90){
						echo();
						addch(temp);
						coordenadas[numberCounter] = temp;
						numberCounter++;
					}
				}
			}
			if(turnoJugador%2){//Turno jugador 2


			}else{//Turno jugador 1

			}
			turnoJugador++;
		}

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

		char ans = getch();
	}
	return 0;
}


bool jaqueMate(Pieza*** tablero){
	bool jaqueM = false;
	return jaqueM;
}
/*
void impresionTablero(Pieza*** matriz){
	int x,y;
	getmaxyx(stdscr,y,x);
	move(y/2,(x/2)-20);	
	int charAscii = 65;
	init_pair(3,COLOR_BLACK,COLOR_WHITE);
	init_pair(4,COLOR_RED,COLOR_BLACK);
	for(int i=0; i<8; i++){
		printw("%c",(char)(i+charAscii));
		printw("\t\t");
	}
	printw ("\n\n");
	charAscii = 65;
	int bandera=3;
	for(int i=0; i<8; i++){
		printw("%i",i);
		printw("\t");
        for(int j=0; j<8; j++){
            printw("|");
            attron(COLOR_PAIR(bandera));
            printw("       ");
            printw("%s",matriz[i][j]->toString());
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
}*/
void impresionTablero(Pieza*** matriz){
	attroff(A_BOLD);
	int width, height;
	init_pair(3,COLOR_BLACK,COLOR_WHITE);
	init_pair(4,COLOR_RED,COLOR_BLACK);

	getmaxyx(curscr,height,width);
	int move_this_y_1 = (height/2)-1;
	int move_this_y_2 = (height/2)+1;
	int charAscii = 65;
	move(move_this_y_1-10,(width/2)-20);
	for(int i=0; i<8; i++){
		printw("%c",(char)(i+charAscii));
		printw("\t\t");
	}
	printw ("\n\n");
	//impresionLinea();
	charAscii = 65;
	int bandera=3;
	for(int i=0; i<8; i++){
		printw("%i",i);
		printw("\t");
        for(int j=0; j<8; j++){
            printw("|");
            attron(COLOR_PAIR(bandera));
            printw("       ");
            printw("%s",matriz[i][j]->toString());
            printw("       ");
            attroff(COLOR_PAIR(bandera));
            //attron(COLOR_PAIR(bandera));
            //attroff(COLOR_PAIR(bandera));
       
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
			if(tablero[i][j]== NULL)
				tablero[i][j] = new Pieza("V",i,j);
		}
	}
	for(int i=0; i<8; i++)
        for(int j=0; j<8; j++){
        	tablero[i][j] -> toString();
	return;
	}
}