
#include<bits/stdc++.h>
#include "Vector3d.h"
#include "Plane3d.h"

using namespace std;

double Distanse(vector<Vector3d> array, pair<int, Vector3d> prob)
{
    Vector3d p1 = array[prob.first];
    Vector3d p2 = prob.second;
    double dx = 1e9, dy = 1e9;
    double dz = abs(p1.z - p2.z);
    for(int i = -1000; i <= 1000; i++) {
        dx = min(dx, abs(p1.x - p2.x + i));
        dy = min(dy, abs(p1.y - p2.y + i));
    }

    return sqrt(dx*dx + dy*dy + dz*dz);
}

Vector3d ArgMin(vector<Vector3d> array, vector<pair<vector<int>, Vector3d> > candidates)
{
    Vector3d cand;
    double dist = 1e9, newD, newD1, newD2;
    for(auto i: candidates)
    {
        pair<int, Vector3d> ff, ss, tt;
        ff.first = i.first[0];
        ff.second = i.second;

        ss.first = i.first[1];
        ss.second = i.second;

        tt.first = i.first[2];
        tt.second = i.second;

        newD = Distanse(array, ff);
        newD1 = Distanse(array, ss);
        newD2 = Distanse(array, tt);
        //cout << "candidate " << newD << ' ' << newD1 << ' ' << newD2 << '\n';
        if(newD < dist)
        {
            dist = newD;
            cand = i.second;
        }
    }
    return cand;
}


int main()
{
    //freopen("data.txt", "w", stdout);
    double h = 0.2;
    vector<Vector3d> array;
    array.emplace_back(Vector3d(0, 0, 0));
    array.emplace_back(0.5, 0.5, h);
    if(h > sqrt(1./2))
    {
        cout << "too large h";
        return 0;
    }
    //array.emplace_back(0, 1 - sqrt(h*h + 1.0 / 2) * sqrt(1 + 2 * h * h) / sqrt(2) , 2 * h);
    double y = (1./2 - 3 * h*h)/sqrt(2);
    //double z = 1/sqrt(2) - y;
    double p = y * sqrt(2);
    array.emplace_back(0, p, 2 * h);
    //array.emplace_back(1.0/2 - sqrt(h*h + 1.0 / 2) * sqrt(1 + 2 * h * h) / 2 / sqrt(2), 1./2 - sqrt(h*h + 1.0 / 2) * sqrt(1 + 2 * h * h) / 2 / sqrt(2) , 2 * h);

    //cout << Distanse(array, {0, array[1]}) << '\n';
    //cout << Distanse(array, {0, array[2]}) << '\n';
    //cout << Distanse(array, {1, array[2]}) << '\n';
    int N = 1000;
    for(int i = 3; i <= N; i++)
    {
        vector<pair<vector<int>, Vector3d> > candidates;
        Vector3d prob;
        int capacity = array.size();
        for(int a = 0; a < capacity; a++) {
            if((i-a)*h > 2 * sqrt(1.0/sqrt(2) + h*h))
                continue;
            for (int b = a + 1; b < capacity; b++)
                for (int c = b + 1; c < capacity; c++) {
                    Plane3d p1 = Plane3d::midplane(array[a], array[b]);
                    Plane3d p2 = Plane3d::midplane(array[a], array[c]);
                    Plane3d p3 = Plane3d(0, 0, 1, i * h);
                    prob = Plane3d::intersection(p1, p2, p3);
//                    prob.x = prob.x - (long long) prob.x;
//                    prob.y = prob.y - (long long) prob.y;
//                    if(prob.x < 0) prob.x+=1;
//                    if(prob.y < 0) prob.y+=1;
                    //if (0 <= prob.x && prob.x < 1 && 0 <= prob.y && prob.y < 1)
                    vector<int> abc = {a, b, c};
                    candidates.emplace_back(make_pair(abc, prob));

                }
        }
        prob = ArgMin(array, candidates);
        prob.x = prob.x - (long long) prob.x;
        prob.y = prob.y - (long long) prob.y;
        if(prob.x < 0) prob.x+=1;
        if(prob.y < 0) prob.y+=1;
        array.emplace_back(prob);
    }
    for(int i = 1; i < array.size(); i++)
    {

        double dx = abs(array[i-1].x - array[i].x);
        double dy = abs(array[i-1].y - array[i].y);
//        dx = min(dx, 1 - dx);
//        dy = min(dy, 1 - dy);
        cout << dx << " " << dy << " " << array[i].z << '\n';
    }



}