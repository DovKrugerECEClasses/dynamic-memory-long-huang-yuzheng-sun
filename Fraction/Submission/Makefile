DEBUG	:= -g

fraction: Fraction.o main.o
	g++ $(DEBUG) Fraction.o main.o -o fraction

Fraction.o: Fraction.hh Fraction.cpp
	g++ $(DEBUG) -c Fraction.cpp # creates Fraction.o

main.o: main.cpp Fraction.hh
	g++ $(DEBUG) -c main.cpp # creates main.o
