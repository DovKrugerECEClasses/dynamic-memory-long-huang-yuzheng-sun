Targets: templatefunctions.o Vec3d.o
	g++ -o templatefunctions templatefunctions.o
	g++ -o Vec3d Vec3d.o

templatefunctions.o: templatefunctions.cpp
	g++ -c templatefunctions.cpp

Vec3d.o: Vec3d.cpp Vec3d.hh
	g++ -c Vec3d.cpp

clean:
	rm *.o

