String: main.o String.o
	g++ -o main main.o String.o

main.o: main.cpp String.hh
	g++ -c main.cpp

String.o: String.cpp String.hh
	g++ -c String.cpp

clean:
	rm *.o


