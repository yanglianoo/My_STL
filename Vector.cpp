/**
 * @File Name: Vector.cpp
 * @brief  
 * @Author : Timer email:330070781@qq.com
 * @Version : 1.0
 * @Creat Date : 2023-05-11
 * 
 */
#include "Vector.hpp"
#include <iostream>
/**
 * @brief  区间拷贝赋值
 */
template <typename T> 
void Vector<T>::copyFrom( T const* A, int lo, int hi )
{

    _capacity = 2 * (hi - lo);
    _elem = new T[_capacity];
    _size = 0;

    while (lo < hi)
    {
        _elem[_size] = A[lo];
        _size++;
        lo++;
    }
}

/**
 * @brief  拷贝赋值,重载 = 号
 */
template <typename T> 
Vector<T>& Vector<T>::operator=(Vector<T> const&v)
{
     //释放原有内容
    if( _elem != nullptr)
    {
        delete [] _elem;
    }
    // 元素拷贝
    copyFrom(v,_elem, 0 , v.size());

    //返回当前对象的引用
    return *this;
}

/**
 * @brief  内存扩充
 */
template <typename T> 
void Vector<T>::expand()
{
    if(_size < _capacity) return;   //尚未满员时，不必扩容
    if(_capacity < DEFAULT_CAPACITY ) _capacity = DEFAULT_CAPACITY; //不低于最小容量
    
    T* oldElem = _elem;
    _elem = new T[_capacity <<= 1]; //容量加倍

    for (size_t i = 0; i < _size; i++)
    {
        _elem[i] = oldElem[i];
    }
    
    delete [] oldElem;
}

/**
 * @brief  内存缩小
 */
template <typename T> 
void Vector<T>::shrink()
{
    if ( _capacity < DEFAULT_CAPACITY << 1 ) return; //不致收缩倒DEFAULT_CAPACITY以下
    if( _size << 2 > _capacity) return; //以25% 为边界
    T* oldElem = _elem;
    _elem = new T[_capacity >>= 1]; //容量减半

    for (size_t i = 0; i < _size; i++)
    {
        _elem[i] = oldElem[i];
    }
    
    delete [] oldElem;
}