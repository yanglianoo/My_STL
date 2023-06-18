#pragma once 
#include <iostream>

template <typename T> class list{
public:
    T data;
    list<T>* pre;
    list<T>* next;
public:
    list();
    list(size_t count, const T& value);
    list(size_t count);
    list(const list& other);
    list(std::initializer_list<T> init);
public:
    ~list();
public:
    list<T>& operator=(list<T> & other);
    list& operator=( std::initializer_list<T> ilist );
    
};

