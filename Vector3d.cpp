//
// Created by alexander on 12-Dec-19.
// Modified on 26-Dec-19
//
#include "Vector3d.h"


Vector3d::Vector3d(const Vector3d &vec)
{
    x=vec.x;
    y=vec.y;
    z=vec.z;
}

//addition

Vector3d Vector3d ::operator+(const Vector3d &vec)
{
    return Vector3d(x+vec.x,y+vec.y,z+vec.z);
}

Vector3d &Vector3d ::operator+=(const Vector3d &vec)
{
    x+=vec.x;
    y+=vec.y;
    z+=vec.z;
    return *this;
}
//substraction//
Vector3d Vector3d ::operator-(const Vector3d &vec)
{
    return Vector3d(x-vec.x,y-vec.y,z-vec.z);
}

Vector3d &Vector3d::operator-=(const Vector3d &vec)
{
    x-=vec.x;
    y-=vec.y;
    z-=vec.z;
    return *this;
}

//scalar multiplication

Vector3d Vector3d ::operator*(f value)
{
    return Vector3d(x*value,y*value,z*value);
}



Vector3d &Vector3d::operator*=(f value)
{
    x*=value;
    y*=value;
    z*=value;
    return *this;
}

//scalar division
Vector3d Vector3d ::operator/(f value)
{
    assert(value!=0);
    return Vector3d(x/value,y/value,z/value);
}

Vector3d &Vector3d ::operator/=(f value)
{
    assert(value!=0);
    x/=value;
    y/=value;
    z/=value;
    return *this;
}


Vector3d &Vector3d::operator=(const Vector3d &vec)
{
    x=vec.x;
    y=vec.y;
    z=vec.z;
    return *this;
}

//Dot product
f Vector3d::dot_product(const Vector3d &vec)
{
    return x*vec.x+vec.y*y+vec.z*z;
}

//cross product
Vector3d Vector3d ::cross_product(const Vector3d &vec)
{
    f ni=y*vec.z-z*vec.y;
    f nj=z*vec.x-x*vec.z;
    f nk=x*vec.y-y*vec.x;
    return Vector3d(ni,nj,nk);
}

f Vector3d::magnitude()
{
    return sqrt(square());
}

f Vector3d::square()
{
    return x*x+y*y+z*z;
}

Vector3d Vector3d:: normalization()
{
    assert(magnitude()!=0);
    *this/=magnitude();
    return *this;
}

f Vector3d::distance(const Vector3d &vec)
{
    Vector3d dist=*this-vec;
    return dist.magnitude();
}

f Vector3d::show_X()
{
    return x;
}

f Vector3d::show_Y()
{
    return y;
}

f Vector3d::show_Z()
{
    return z;
}

void Vector3d::disp()
{
    cout<<x<<" "<<y<<" "<<z<<endl;
}

