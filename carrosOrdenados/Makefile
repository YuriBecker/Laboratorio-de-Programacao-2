CXX = gcc
CXXFLAGS =  -Wall
LDFLAGS = 

all: main

main.o: main.c Carro.h
Carro.o: Carro.c  
# time.o: time.c time.h jogador.h lista.h treinador.h
# jogador.o: jogador.c jogador.h lista.h 
# menu.o: menu.c menu.h lista.h time.h jogador.h treinador.h campeonato.h
# treinador.o: treinador.c treinador.h time.h lista.h
# partida.o: partida.c partida.h lista.h time.h jogador.h treinador.h 
# rodada.o: rodada.c rodada.h lista.h time.h jogador.h treinador.h partida.h
# campeonato.o: campeonato.c campeonato.h lista.h time.h jogador.h  treinador.h menu.h rodada.h partida.h

main: main.o Carro.o 
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
clean:
	rm -f main *.o

