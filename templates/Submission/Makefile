Targets: templatefunctions.o TestVec3d.o
	g++ -o templatefunctions templatefunctions.o
	g++ -o Vec3d TestVec3d.o

templatefunctions.o: templatefunctions.cpp
	g++ -c templatefunctions.cpp

TestVec3d.o: TestVec3d.cpp Vec3d.hh
	g++ -c TestVec3d.cpp

clean:
	rm *.o

