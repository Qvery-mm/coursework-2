
#include<bits/stdc++.h>
#include "Vector3d.h"
#include "Plane3d.h"

using namespace std;

//globals
vector<Vector3d> points;


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
       x = (C * B - F * E) / (A * E - D * B);
       y = (A * F - D * C) / (A * E - D * B);
       return {Vector3d(x, y, H), sqrt(pow(y - a.y, 2) + pow(H - a.z, 2))};
}


pair<Vector3d, double> FindOpt(int _a, int _b, int _c, double H)
{
    vector<Vector3d> knownPoints;
    knownPoints.emplace_back(points[_a]);
    knownPoints.emplace_back(points[_b]);
    knownPoints.emplace_back(points[_c]);

    /** duplicating by modulo 2 */
    for(int i = 0; i < 3; i++)
    {
        double x = knownPoints[i].x, y = knownPoints[i].y, z = knownPoints[i].z;
        knownPoints.emplace_back(Vector3d(x+1, y, z));
        knownPoints.emplace_back(Vector3d(x + 1, y+1, z));
        knownPoints.emplace_back(Vector3d(x, y + 1, z));
        knownPoints.emplace_back(Vector3d(x - 1, y + 1, z));
        knownPoints.emplace_back(Vector3d(x - 1, y, z));
        knownPoints.emplace_back(Vector3d(x - 1, y - 1, z));
        knownPoints.emplace_back(Vector3d(x, y - 1, z));
        knownPoints.emplace_back(Vector3d(x + 1, y - 1, z));
    }
    /**
     * main loop
     */
    int capacity = knownPoints.size();
    pair <Vector3d, double> candidate;
    Vector3d ans;
    double minDist = 1e9;
    for(int a = 0; a < capacity; a++)
        for (int b = a + 1; b < capacity; b++)
            for (int c = b + 1; c < capacity; c++)
            {
                candidate = SolveForThree(knownPoints[a], knownPoints[b], knownPoints[c], H);
                if(candidate.first.x < 0 || candidate.first.x >= 1 || candidate.first.y < 0 || candidate.first.y >= 1)
                    continue;

                if(candidate.second < minDist)
                {
                    minDist = candidate.second;
                    ans = candidate.first;
                }
            }

    return {ans, minDist};
}



int main()
{
    freopen("data.txt", "w", stdout);
    double h = 0.02;

    /**
     * initial points
     */
    points.emplace_back(Vector3d(0, 0, 0));
    points.emplace_back(0.5, 0.5, h);
    if(h > sqrt(1./2))
    {
        cout << "too large h";
        return 0;
    }
    double y = (1./2 - 3 * h*h)/sqrt(2);
    double p = y * sqrt(2);
    points.emplace_back(0, p, 2 * h);

    /**
     * main loop
     */
    int N = 25;
    for(int i = 3; i <= N; i++)
    {
        vector<pair<Vector3d, int> > candidates;
        int capacity = points.size();
        for(int a = 0; a < capacity; a++) {
            if((i-a)*h > 2 * sqrt(1.0/sqrt(2) + h*h))
                continue;
            for (int b = a + 1; b < capacity; b++)
                for (int c = b + 1; c < capacity; c++) {
                    candidates.emplace_back(FindOpt(a, b, c, i * h));
                }
        }
        double minDist = 1e9;
        Vector3d next;
        for(auto i: candidates)
        {
            if(i.second < minDist)
            {
                minDist = i.second;
                next = i.first;
            }
        }
        points.emplace_back(next);
        cerr << i << endl;
    }
    for(int i = 1; i < points.size(); i++)
    {
        double dx = abs(points[i].x - points[i-1].x);
        double dy = abs(points[i].x - points[i-1].x);
        dx = min(dx, 1 - dx);
        dy = min(dy, 1 - dy);
        cout << dx << ' ' << dy << ' ' << points[i].z << '\n';
    }





}