
#include<bits/stdc++.h>
#include "Vector3d.h"
#include "Plane3d.h"

using namespace std;

//globals
vector<Vector3d> points;
vector<Vector3d> knownPoints;
double h = 0.001;
int N = 100;
double epsilon = 1e-10;
double lastDistance;
char* filename = "demo1.txt";
double psi = 1.3247179572;
double pi = 3.1415926;
/**
* initial point
*/
Vector3d initial(0, 0, 0);

//Vector3d initial1( psi / pi,  psi * psi / pi, 0);
//Vector3d initial2(3 * psi / 2 / pi,  3 * psi * psi / 2 / pi, 0);


/**
 * @param a, b, c - input vectors
 * @return  local optimum for placing next vector
 * @brief Method solves the equation: (x - x1)^2 + (y - y1)^2 + (H - z1)^2 = (x - x2)^2 + (y - y2)^2 + (H - z2)^2 =
 * (x - x3)^2 + (y - y3)^2 + (H - z3)^2, where x_i, y_i, z_i - coordinates of each given vector
 */
pair<Vector3d, double> SolveForThree(Vector3d a, Vector3d b, Vector3d c, double H)
{
       double A, B, C, D, E, F;
       A = 2 * (b.x - a.x);
       B = 2 * (b.y - a.y);
       C = pow(H - b.z, 2) - pow(H - a.z, 2) + pow(b.x, 2) -
               pow(a.x, 2) + pow(b.y, 2) - pow(a.y, 2);

       D = 2 * (c.x - a.x);
       E = 2 * (c.y - a.y);
       F = pow(H - c.z, 2) - pow(H - a.z, 2) + pow(c.x, 2) -
        pow(a.x, 2) + pow(c.y, 2) - pow(a.y, 2);

       double x, y;
       x = (C * E - F * B) / (A * E - D * B);
       y = (A * F - D * C) / (A * E - D * B);
       if(isnan(x) || isnan(y))
           return {Vector3d(-1, -1, -1), -1e9};

//       cerr << "debug " <<  sqrt(pow(x - a.x, 2) + pow(y - a.y, 2) + pow(H - a.z, 2)) << ' '
//       << sqrt(pow(x - b.x, 2) + pow(y - b.y, 2) + pow(H - b.z, 2)) << ' '
//       << sqrt(pow(x - c.x, 2) + pow(y - c.y, 2) + pow(H - c.z, 2)) << '\n';

       return {Vector3d(x, y, H), sqrt(pow(x - a.x, 2) + pow(y - a.y, 2) + pow(H - a.z, 2))};
}


Vector3d FindOpt(double H)
{
    int capacity = knownPoints.size();
    pair <Vector3d, double> candidate;

    Vector3d ans;
    double maxDist = -1;

    int startFrom = 0;
    for(int a = 0; a < capacity; a++)
    {

        if((H - knownPoints[a].z) > 2 * lastDistance)
        {
            startFrom = a;
            continue;
        }
        for (int b = a + 1; b < capacity; b++)
            for (int c = b + 1; c < capacity; c++)
            {
                candidate = SolveForThree(knownPoints[a], knownPoints[b], knownPoints[c], H);

                if (candidate.first.x < 0 - epsilon || candidate.first.x > 1 + epsilon || candidate.first.y < 0 - epsilon || candidate.first.y > 1 + epsilon)
                    continue;
                bool flag = true;
                for(int i = startFrom; i < capacity; i++)
                {
                    Vector3d v = knownPoints[i];
                    Vector3d u = candidate.first;
                    double rho = sqrt((v.x - u.x) * (v.x - u.x) + (v.y - u.y) * (v.y - u.y) + (v.z - u.z) * (v.z - u.z));
                    if(rho < candidate.second - epsilon)
                        flag = false;
                }
                if(flag && candidate.second > maxDist) {
                    maxDist = candidate.second;
                    ans = candidate.first;
                }

                //cerr << candidate.first.x << ' ' << candidate.first.y << ' ' << candidate.first.z << '\n';
            }
    }
    lastDistance = maxDist;
    cerr << "maxDist " << maxDist << '\n';
    return ans;
}

/** duplicating by modulo 1 */
void DuplicatePoint(double x, double y, double z)
{
    knownPoints.emplace_back(Vector3d(x, y, z));
    knownPoints.emplace_back(Vector3d(x+1, y, z));
    knownPoints.emplace_back(Vector3d(x + 1, y+1, z));
    knownPoints.emplace_back(Vector3d(x, y + 1, z));
    knownPoints.emplace_back(Vector3d(x - 1, y + 1, z));
    knownPoints.emplace_back(Vector3d(x - 1, y, z));
    knownPoints.emplace_back(Vector3d(x - 1, y - 1, z));
    knownPoints.emplace_back(Vector3d(x, y - 1, z));
    knownPoints.emplace_back(Vector3d(x + 1, y - 1, z));
}



int main()
{
    freopen(filename, "w", stdout);
    points.emplace_back(initial);
    double x = initial.x, y = initial.y, z = initial.z;
    DuplicatePoint(x, y, z);
    lastDistance = 1;

//    points.emplace_back(initial1);
//    x = initial1.x, y = initial1.y, z = initial1.z;
//    DuplicatePoint(x, y, z);
//
//    points.emplace_back(initial2);
//    x = initial2.x, y = initial2.y, z = initial2.z;
//    DuplicatePoint(x, y, z);


    /**
     * main loop
     */
    cout << N << '\n';
    for(int i = 1; i <= N; i++)
    {
        Vector3d next = FindOpt(i * h);
        cout << next.x << ' ' << next.y << '\n';
        double dx = abs(next.x - points.back().x);
        double dy = abs(next.y - points.back().y);
        dx = min(dx, 1 - dx);
        dy = min(dy, 1 - dy);
        //cout << dx << ' ' << dy << ' ' << next.z << '\n';
        points.emplace_back(next);
        cerr << points.back().x << ' ' << points.back().y << '\n';

        x = next.x, y = next.y, z = next.z;
        DuplicatePoint(x, y, z);



        cerr << i << endl;
    }







}