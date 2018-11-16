#pragma once
#include<iostream>
using namespace std;

template<typename T>

class Vec3d {
private:
    T x,y,z;
public:
    Vec3d(const T& x=0, const T& y=0, const T& z=0):x(x),y(y),z(z){}

    friend ostream& operator<<(ostream& s, const Vec3d& v){
        return s<<"("<<v.x<<","<<v.y<<","<<v.z<<")";
    }
    
    friend Vec3d operator+(const Vec3d& v1, const Vec3d& v2){
        Vec3d ans;
        ans.x = v1.x+v2.x;
        ans.y = v1.y+v2.y;
        ans.z = v1.z+v2.z;
        return ans;
    }
};
