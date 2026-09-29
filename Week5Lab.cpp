#include<iostream>
#include<cmath>
#include<string>


using std::string;
using std::cout;
using std::cin;
using std::endl;


int get_abs(int n)
{
    if (n < 0)
    {
        return -n;
    }
    return n;
}

string reduced_sqrt(int n)
{
    int root = static_cast<int>(sqrt(n));
    if (n/static_cast<double>(root) == static_cast<double>(root))
    {
        return std::to_string(root);
    }
    int num = n;
    for(int i = root; i > 1; i--)
    {
        int sq = i * i;
        if (num%sq == 0)
        {
            return std::to_string(i) + "√(" + std::to_string(num/sq)+ ")";
        }
    }
    return "√(" + std::to_string(n) +")";
}

int get_A(int p1[2], int p2[2])
{
    int distx = get_abs(p1[0] - p2[0]);
    distx = distx * distx;
    return distx;
}

int get_B(int p1[2], int p2[2])
{
    int disty = get_abs(p1[1] - p2[1]);
    disty = disty*disty;
    return disty;
}

int get_C_Squared(int p1[2], int p2[2])
{
    int a = get_A(p1, p2);
    int b = get_B(p1, p2);
    int c_squared = a + b;
    return c_squared;
}

string get_pythag(int p1[2], int p2[2])
{
    return reduced_sqrt(get_C_Squared(p1,p2));
}

int main() {
    int p1[2];
    int p2[2];
    cout << "Please enter first point" << endl;
    cin >> p1[0] >> p1[1];
    cout << "Please enter second point" << endl;
    cin >> p2[0] >> p2[1];
    cout << "The hypotenuse is: " + get_pythag(p1, p2) + " units in length" << endl;
    return 0;
}