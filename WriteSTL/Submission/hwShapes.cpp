/*
	Cube
	Cylinder
	Sphere (optional)

https://en.wikipedia.org/wiki/STL_(file_format)

*/
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
using namespace std;

const double PI = 3.1415926;

class Vector {
private:
    double x,y,z;
public:
    Vector(double x=0, double y=0, double z=0): x(x), y(y), z(z){}
    Vector minus(const Vector& v) const{
        return Vector(this->x-v.x, this->y-v.y, this->z-v.z);
    }
    Vector divide(double l) const{
        return Vector(this->x/l, this->y/l, this->z/l);
    }
    Vector crossMulti(const Vector& v) const{
        return Vector(this->y*v.z-v.y*this->z, this->z*v.x-v.z*this->x, this->x*v.y-v.x*this->y);
    }
    double length() const{
        return sqrt(x*x+y*y+z*z);
    }
    double getX(){
        return x;
    }
    double getY(){
        return y;
    }
    double getZ(){
        return z;
    }
};

class Facet{
private:
    Vector v1,v2,v3;
public:
    Facet(Vector v1, Vector v2, Vector v3): v1(v1), v2(v2), v3(v3){}
    Vector getV1() const{
        return v1;
    }
    Vector getV2() const{
        return v2;
    }
    Vector getV3() const{
        return v3;
    }
    Vector getNormal() const{
        Vector v12 = v2.minus(v1);
        Vector v13 = v3.minus(v1);
        Vector n1 = v12.crossMulti(v13);
        Vector n2 = n1.divide(n1.length());
        return n2;
    }
};

class shape3D {
private:
    double x,y,z;
public:
    shape3D(double x, double y, double z): x(x), y(y), z(z) {}
    void translate(double dx=0, double dy=0, double dz=0){
        x += dx;
        y += dy;
        z += dz;
    }
    double getX(){
        return x;
    }
    double getY(){
        return y;
    }
    double getZ(){
        return z;
    }
    virtual double volume()=0;
    virtual vector<Facet> getFacets()=0;
    void writeIn(ofstream &file){
        vector<Facet> facets = this->getFacets();
        for(int i=0;i<facets.size();i++){
            file<<"facet normal "<<facets[i].getNormal().getX()<<" "<<facets[i].getNormal().getY()
            <<" "<<facets[i].getNormal().getZ()<<'\n';
            file<<"outer loop\n";
            file<<"vertex "<<facets[i].getV1().getX()<<" "<<facets[i].getV1().getY()
            <<" "<<facets[i].getV1().getZ()<<'\n';
            file<<"vertex "<<facets[i].getV2().getX()<<" "<<facets[i].getV2().getY()
                <<" "<<facets[i].getV2().getZ()<<'\n';
            file<<"vertex "<<facets[i].getV3().getX()<<" "<<facets[i].getV3().getY()
                <<" "<<facets[i].getV3().getZ()<<'\n';
            file<<"endloop\n";
            file<<"endfacet\n";
        }
    }
    void write(string filename){
        ofstream file;
        file.open(filename);
        file<<"solid "<<filename<<'\n';
        writeIn(file);
        file<<"endsolid "<<filename<<'\n';
        file.close();
    }
};


class Cube: public shape3D {
private:
    double s;
public:
    Cube(double s): shape3D(0,0,0), s(s) {}
    double volume(){
        return s*s*s;
    }
    vector<Facet> getFacets(){
        double x = this->getX();
        double y = this->getY();
        double z = this->getZ();
        Vector v1(x,y,z);
        Vector v2(x,y+s,z);
        Vector v3(x+s,y+s,z);
        Vector v4(x+s,y,z);
        Vector v5(x,y,z+s);
        Vector v6(x+s,y,z+s);
        Vector v7(x+s,y+s,z+s);
        Vector v8(x,y+s,z+s);

        vector<Facet> facets;
        facets.push_back(Facet(v1,v2,v3));
        facets.push_back(Facet(v1,v3,v4));
        facets.push_back(Facet(v8,v5,v6));
        facets.push_back(Facet(v8,v6,v7));
        facets.push_back(Facet(v2,v8,v7));
        facets.push_back(Facet(v2,v7,v3));
        facets.push_back(Facet(v4,v6,v5));
        facets.push_back(Facet(v4,v5,v1));
        facets.push_back(Facet(v1,v5,v8));
        facets.push_back(Facet(v1,v8,v2));
        facets.push_back(Facet(v1,v5,v8));
        facets.push_back(Facet(v3,v6,v4));
        facets.push_back(Facet(v3,v7,v6));

        return facets;
    }
};

class Cylinder: public shape3D {
private:
    double r,height;
public:
    Cylinder(double r=1, double height=1): shape3D(0,0,0), r(r), height(height) {}
    double volume(){
        return PI*r*r*height;
    }
    vector<Facet> getFacets(){
        Vector bottomCenter(this->getX(),this->getY(),this->getZ());
        Vector topCenter(this->getX(),this->getY(),this->getZ()+height);
        vector<Vector> bottomVectors;
        vector<Vector> topVectors;
        //set precision to 10
        double step = 2*PI/10;
        for(int i=0;i<10;i++){
            double angle = step*i;
            bottomVectors.push_back(Vector(r*cos(angle),r*sin(angle),0));
            topVectors.push_back(Vector(r*cos(angle),r*sin(angle),height));
        }

        vector<Facet> facets;
        for(int i=0;i<9;i++){
            facets.push_back(Facet(bottomCenter,bottomVectors[i+1],bottomVectors[i]));
            facets.push_back(Facet(topCenter,topVectors[i],topVectors[i+1]));
            facets.push_back(Facet(bottomVectors[i],bottomVectors[i+1],topVectors[i]));
            facets.push_back(Facet(bottomVectors[i+1],topVectors[i+1],topVectors[i]));
        }
        facets.push_back(Facet(bottomCenter,bottomVectors[0],bottomVectors[9]));
        facets.push_back(Facet(topCenter,topVectors[9],topVectors[0]));
        facets.push_back(Facet(bottomVectors[9],bottomVectors[0],topVectors[9]));
        facets.push_back(Facet(bottomVectors[0],topVectors[0],topVectors[9]));

        return facets;
    }
};

class Sphere: public shape3D {
private:
    double r;
    int horizPrecision, verticalPrecision;
public:
    Sphere(double r=10, int horizPrecision=10, int verticalPrecision=10): shape3D(0,0,0),
    r(r), horizPrecision(horizPrecision), verticalPrecision(verticalPrecision) {
    }
    double volume(){
        return 4.0/3*PI*r*r;
    }
    vector<Facet> getFacets(){
        Vector Center(this->getX(),this->getY(),this->getZ());
        Vector bottomCenter(this->getX(),this->getY(),this->getZ()-r);
        Vector topCenter(this->getX(),this->getY(),this->getZ()+r);

        vector< vector<Vector> > vectors;
        double horizStep = 2*PI/horizPrecision;
        double verticalStep = PI/verticalPrecision;
        for(int i=1;i<verticalPrecision;i++){
            double verticalAngle = i*verticalStep;
            double radius = r*sin(verticalAngle);
            double height = r*cos(verticalAngle);
            vector<Vector> horizVectors;
            for(int j=0;j<horizPrecision;j++){
                double horizAngle = j*horizStep;
                horizVectors.push_back(Vector(radius*cos(horizAngle),radius*sin(horizAngle),height));
            }
            vectors.push_back(horizVectors);
        }

        vector<Facet> facets;
        cout<<vectors.size()<<endl;
        cout<<vectors[8][19].getX()<<endl;
        //out of bound could make you stuck in the loop!!!
        for(int i=0;i<verticalPrecision-2;i++){
            for(int j=0;j<horizPrecision-1;j++){
                facets.push_back(Facet(vectors[i][j],vectors[i+1][j],vectors[i+1][j+1]));
                facets.push_back(Facet(vectors[i][j],vectors[i+1][j+1],vectors[i][j+1]));
            }
            facets.push_back(Facet(vectors[i][horizPrecision-1],vectors[i+1][horizPrecision-1],vectors[i+1][0]));
            facets.push_back(Facet(vectors[i][horizPrecision-1],vectors[i+1][0],vectors[i][0]));
        }

        for(int j=0;j<horizPrecision-1;j++){
            facets.push_back(Facet(topCenter,vectors[0][j],vectors[0][j+1]));
        }
        facets.push_back(Facet(topCenter,vectors[0][horizPrecision-1],vectors[0][0]));

        for(int j=0;j<horizPrecision-1;j++){
            facets.push_back(Facet(bottomCenter,vectors[verticalPrecision-2][j+1],vectors[verticalPrecision-2][j]));
        }
        facets.push_back(Facet(bottomCenter,vectors[verticalPrecision-2][0],vectors[verticalPrecision-2][horizPrecision-1]));

        return facets;
    }
};

class Design{
private:
    vector<shape3D*> sps;
public:
    void add(shape3D* s){
        sps.push_back(s);
    }

    void write(string filename){
        ofstream file;
        file.open(filename);
        file<<"solid "<<filename<<'\n';
        for(int i=0;i<sps.size();i++){
            sps[i]->writeIn(file);
        }
        file<<"endsolid "<<filename<<'\n';
        file.close();
    }
};

int main() {
    Design d;
    double s = 10;
    Cube c(s);
    c.translate(-10,10,20);
    // rotate??
    cout << c.volume() << '\n';
    c.write("out.stl"); // how to get all my shapes into the same file
    d.add(&c);
    double r = 10, height  = 20;
    Cylinder cyl(r, height);
    d.add(&c);
    d.write("test.stl");
    Sphere sph(100,20,10);
    d.add(&sph);
    d.write("addingSphere.stl");
}