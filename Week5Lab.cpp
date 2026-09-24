#include<iostream>
#include<cmath>

using std::cout;
using std::endl;

int a_input(int p[2], int p2[2])
{
    return p2[1];
}

int get_A(int p1[2], int p2[2])
{
    int distx = abs(p1[0] - p2[0]);
    distx = distx * distx;
    return distx;
}

int get_B(int p1[2], int p2[2])
{
    int disty = abs(p1[1] - p2[1]);
    disty = disty*disty;
    return disty;
}

double get_C_Squared(int p1[2], int p2[2])
{
    int a = get_A(p1, p2);
    int b = get_B(p1, p2);
    int c_squared = a + b;
    return c_squared;
}

int main() {
    int p1[2] = {1,2};
    int p2[2] = {4,3};
    int p3[2] = {5, 4};
    int p4[2] = {1, 1};

    cout << get_C_Squared(p3, p4) << endl;
    return 0;
}