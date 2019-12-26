//
// Created by alexander on 12-Dec-19.
// Modified on 26-Dec-19
//

#ifndef COURSEWORK_2_PLANE3D_H
#define COURSEWORK_2_PLANE3D_H

#include<iostream>
#include<cmath>
#include<cassert>
#include "Vector3d.h"

using namespace std;
typedef double f;

class Plane3d {
public:
    f a,b,c,d;
    Plane3d()  //constructor
    {
        a=0;
        b=0;
        c=0;
        d=0;
    }

    Plane3d(f a1, f b1, f c1, f d1)     //initializing object with values.
    {
        a=a1;
        b=b1;
        c=c1;
        d=d1;
    }
    Plane3d(const Plane3d &plane);    //copy constructor

    static Plane3d midplane(Vector3d x, Vector3d y);

    static Vector3d intersection(Plane3d a, Plane3d b, Plane3d c);
    static f det3(f array[]);
    void disp();
};


#endif //COURSEWORK_2_PLANE3D_H
