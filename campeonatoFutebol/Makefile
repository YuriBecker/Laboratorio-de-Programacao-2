CXX = gcc
CXXFLAGS =  -Wall
LDFLAGS = 

all: main

main.o: main.c lista.h time.h jogador.h treinador.h rodada.h partida.h
lista.o: lista.c lista.h 
time.o: time.c time.h jogador.h lista.h treinador.h
jogador.o: jogador.c jogador.h lista.h 
menu.o: menu.c menu.h lista.h time.h jogador.h treinador.h
treinador.o: treinador.c treinador.h time.h lista.h
partida.o: partida.c partida.h lista.h time.h jogador.h treinador.h 
rodada.o: rodada.c rodada.h lista.h time.h jogador.h treinador.h partida.h

main: main.o lista.o time.o jogador.o menu.o treinador.o  rodada.o partida.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
clean:
	rm -f main *.o

