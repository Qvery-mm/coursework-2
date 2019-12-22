//
// Created by alexander on 12-Dec-19.
//

#ifndef COURSEWORK_2_Vector3d_H
#define COURSEWORK_2_Vector3d_H

/*
I am creating a class Vector3d which will be used for vector operation . I have overloaded all the basic functions for the required for vector operation .
There is no need for extra class , so no inheritance was necessary .
*/
#include<iostream>
#include<cmath>
#include<cassert>
using namespace std;
typedef double f;
class Vector3d
{
public:
    f x,y,z;
    Vector3d()  //constructor
    {
        x=0;
        y=0;
        z=0;
    }

    Vector3d(f x1,f y1,f z1=0)     //initializing object with values.
    {
        x=x1;
        y=y1;
        z=z1;
    }
    Vector3d(const Vector3d &vec);    //copy constructor
    Vector3d operator+(const Vector3d &vec);    //addition
    Vector3d &operator+=(const Vector3d &vec);  //assigning new result to the vector
    Vector3d operator-(const Vector3d &vec);    //substraction
    Vector3d &operator-=(const Vector3d &vec);  //assigning new result to the vector
    Vector3d operator*(f value);    //multiplication
    Vector3d &operator*=(f value);  //assigning new result to the vector.
    Vector3d operator/(f value);    //division
    Vector3d &operator/=(f value);  //assigning new result to the vector
    Vector3d &operator=(const Vector3d &vec);
    f dot_product(const Vector3d &vec); //scalar dot_product
    Vector3d cross_product(const Vector3d &vec);    //cross_product
    f magnitude();  //magnitude of the vector
    Vector3d normalization();   //normalized vector
    f square(); //gives square of the vector

    f distance(const Vector3d &vec);    //gives distance between two vectors
    f show_X(); //return x
    f show_Y(); //return y
    f show_Z(); //return z
    void disp();    //display value of vectors
};


#endif //COURSEWORK_2_Vector3d_H
