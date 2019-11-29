all: project

project: cargaDiccionario.o
	g++ cargaDiccionario.o ../Libraries/Trie.cpp ../Libraries/Node.cpp -o cargaDiccionario.out -std=c++14

cargaDiccionario.o: cargaDiccionario.cpp
	g++ cargaDiccionario.cpp -c -std=c++14