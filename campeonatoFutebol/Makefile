CXX = gcc
CXXFLAGS =  -Wall
LDFLAGS = 

all: main

main.o: main.c lista.h time.h jogador.h
lista.o: lista.c lista.h 
time.o: time.c time.h jogador.h lista.h
jogador.o: jogador.c jogador.h lista.h 

main: main.o lista.o time.o jogador.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
clean:
	rm -f main *.o

