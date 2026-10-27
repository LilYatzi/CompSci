#include<iostream>

using std::cout;
using std::endl;

//middle weight dog
class Pet {
public:
    Pet();
    Pet(int s, int l, char c);
    int accident(int n);
private:
    int size;
    int leg_length;
    char color;


};

Pet::Pet() {
    size = 0;
    leg_length = 0;
    color = 'B';

}


//n = 1 -> Nuke, 2 -> train, 3 -> drown
int Pet::accident(int n) {
    /*if(n == 1)
    {

    }
    else if (n == 2)
    {

    }
    else if (n == 3)
    {

    }
    else{
        //go fuck yourself
    }*/


   switch (n)
   {
   case 1:
        size = 0;
        leg_length = 0;
        color = '-';
        return 0;
   
   case 2:
        size = size-2;
        leg_length = leg_length - 1;
        return 0;

   case 3:
        size = size + 1;
        return 0;
   
   default:
   return 0;
   }
    return 1;
}

Pet::Pet(int s, int l, char c) {
    size = s;
    leg_length = l;
    color = c;
}