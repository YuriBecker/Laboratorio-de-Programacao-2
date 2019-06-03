CXX = gcc
CXXFLAGS =  -Wall
LDFLAGS = 

all: main

main.o: main.c Carro.h Menu.h
Carro.o: Carro.c Carro.h
Menu.o: Menu.c Menu.h Carro.h ArvBinBusca.h
ArvBinBusca.o: ArvBinBusca.c ArvBinBusca.h Carro.h

main: main.o Carro.o Menu.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
clean:
	rm -f main *.o

