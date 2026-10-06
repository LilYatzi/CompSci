#include <iostream>
#include <bitset>


int main(){
    char c = (1<<0);
    std::cout << std::bitset<8>(c) << std::endl;
    return 0;
}