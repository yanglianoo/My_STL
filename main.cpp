#include <iostream>
#include "Vector.hpp"
#include "List.hpp"
using namespace my_stl;

void test_vector()
{
    std::cout<<"-------------------vector---------------------"<<std::endl;
    vector<int> a = {1,2,3,4,5};
    int b = a.at(2);
    std::cout<<"b:"<<b<<std::endl;
    a.resize(10);
    std::cout<<"a.size:"<<a.size()<<std::endl;
}

void test_list()
{
    std::cout<<"-------------------list---------------------"<<std::endl;
    // 创建含整数的 list
    list<int> l = {7, 5, 16, 8};
 
    // 添加整数到 list 开头
    l.push_front(25);
    // 添加整数到 list 结尾
    l.push_back(13);
 
    // 迭代并打印 list 的值
    std::cout << "l = { ";
    for (int n : l)
        std::cout << n << ", ";
    std::cout << "};\n";
}
int main(int argc, char const *argv[])
{
    test_vector();
    test_list();
}
