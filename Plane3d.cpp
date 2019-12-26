//
// Created by alexander on 12-Dec-19.
// Modified on 26-Dec-19
//

#include "Plane3d.h"


Plane3d::Plane3d(const Plane3d &plane)
{
    a=plane.a;
    b=plane.b;
    c=plane.c;
    d=plane.d;
}

Vector3d Plane3d::intersection(Plane3d ff, Plane3d ss, Plane3d tt)
{
    f dd[] = {ff.a, ff.b, ff.c, ss.a, ss.b, ss.c, tt.a, tt.b, tt.c};

    f dd1[] = {ff.d, ff.b, ff.c, ss.d, ss.b, ss.c, tt.d, tt.b, tt.c};
    f x = det3(dd1) / det3(dd);

    f dd2[] = {ff.a, ff.d, ff.c, ss.a, ss.d, ss.c, tt.a, tt.d, tt.c};
    f y = det3(dd2) / det3(dd);

    f dd3[] = {ff.a, ff.b, ff.d, ss.a, ss.b, ss.d, tt.a, tt.b, tt.d};
    f z = det3(dd3) / det3(dd);

    return Vector3d(x, y, z);
}

f Plane3d::det3(f a[])
{
    return a[0]*(a[4]*a[8] - a[5]*a[7]) - a[1]*(a[3]*a[8] - a[5]*a[6]) + a[2]*(a[3]*a[7] - a[4]*a[6]);
}

Plane3d Plane3d::midplane(Vector3d a, Vector3d b) {
    return Plane3d(b.x - a.x, b.y - a.y, b.z - a.z,
                   (a.x*a.x - b.x*b.x + a.y*a.y - b.y*b.y + a.z*a.z - b.z*b.z) / 2);
}

void Plane3d::disp() {
    cout << a << ' ' << b << ' ' << c << ' ' << d << '\n';
}
