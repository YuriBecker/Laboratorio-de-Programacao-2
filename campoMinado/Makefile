CXX = gcc
CXXFLAGS =  -Wall
LDFLAGS = 

all: campoMinado

campoMinado.o: campoMinado.c handleScreen.h structs.h utils.h handleMatriz.h autoPlay.h
handleScreen.o: handleScreen.c handleScreen.h
utils.o: utils.c utils.h
handleMatriz.o: handleMatriz.c handleMatriz.h
autoPlay.o: autoPlay.c autoPlay.h

campoMinado: campoMinado.o autoPlay.o handleMatriz.o utils.o handleScreen.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
clean:
	rm -f campoMinado *.o

