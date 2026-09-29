#include<iostream>
#include<string>

using std::cout;
using std::endl;

int main()
{
    
    for(int i = 0; i <= 100; i++)
    {
        if(i%10 == 1 && i != 11)
        {
            cout << "This is the: " + std::to_string(i) + "st iteration" << endl;
        }
        else
        {
            cout << "This is the: " + std::to_string(i) + "th iteration" << endl;
        }
    }
    /*
    for(int i = 0; i<5; i = i+1)
    {
        cout << i;
    }*/
    return 0;
}