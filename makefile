all: hw4

hw4: main.cpp interpreter.o line.o command.o bool.o arithmetic.o
	g++ -g -Wall main.cpp interpreter.o line.o command.o bool.o arithmetic.o -o hw4 -std=c++11

interpreter.o: interpreter.h interpreter.cpp
	g++ -g -c -Wall interpreter.cpp -o interpreter.o -std=c++11

line.o: line.h line.cpp
	g++ -g -c -Wall line.cpp -o line.o -std=c++11

command.o: command.h command.cpp
	g++ -g -c -Wall command.cpp -o command.o -std=c++11

bool.o: Bool.h Bool.cpp
	g++ -g -c -Wall Bool.cpp -o bool.o -std=c++11

arithmetic.o: arithmetic.h arithmetic.cpp
	g++ -g -c -Wall arithmetic.cpp -o arithmetic.o -std=c++11
