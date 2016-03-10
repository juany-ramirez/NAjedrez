main:	mainAjedrez.o Pieza.o
	g++ mainAjedrez.o Pieza.o -o  Juego.exe -lncurses
        
mainAjedrez.o:	mainAjedrez.cpp Pieza.h
	g++ -c mainAjedrez.cpp 

Pieza.o:	Pieza.cpp Pieza.h
	g++ -c Pieza.cpp 

clean:  
	rm *.o  Juego.exe
		clear

execute:
	./Juego.exe
