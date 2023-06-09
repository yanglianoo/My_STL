#include <iostream>
#include "Vector.hpp"


int main(int argc, char const *argv[])
{
    vector<int> a = {1,2,3,4,5};
    int b = a.at(2);
    std::cout<<"b:"<<b<<std::endl;
}
