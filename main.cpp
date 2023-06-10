#include <iostream>
#include "Vector.hpp"
using namespace my_stl;

int main(int argc, char const *argv[])
{
    vector<int> a = {1,2,3,4,5};
    int b = a.at(2);
    std::cout<<"b:"<<b<<std::endl;
    a.resize(10);
    std::cout<<"a.size:"<<a.size()<<std::endl;
}
