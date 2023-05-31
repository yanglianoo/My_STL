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

/* 重载 [] */
template <typename T> 
T& Vector<T>::operator[] ( int r ) const
{
    return _elem[r];
}


template <typename T> 
void permute ( Vector<T>& V )
 {
    for(int i = V.size(); i > 0 ; i--)
    {
        swap(V[i-1], V[rand() % i]);  //V[i - 1]与 V[0, i)中某一随机元素交换
    }
 }

/* 区间置乱接口 */
template <typename T> 
void Vector<T>::unsort( int lo, int hi )
{
    T* V = _elem + lo;
    for( int i = hi - lo; i > 0 ; i--)
    {
        swap(V[i-1] , V[rand() % i]);
    }
}

/* 遍历查找 */
template <typename T> 
int Vector<T>::find ( T const& e, int lo, int hi ) const
{
    while (( lo < hi--) && e != _elem[hi])
    {
        return hi;
    } 
    /* 没找到返回 -1 */
    return -1;
}

/* 元素插入 */
template <typename T> 
int Vector<T>::insert ( int r, T const& e )
{
    expand();
    for( int i = _size; i > r; i--)
    {
        _elem[i] = _elem[i-1];
    }

    _elem[r] = e;
    _size++;

    return r;
}

/* 区间元素删除 */
template <typename T> 
int Vector<T>::remove ( int lo, int hi )
{
    if( lo == hi)  return 0;
    while (hi <  _size)
    {
        _elem[lo] = _elem[hi];
        lo++;
        hi++;
    }

    _size = _size + lo - hi;

    shrink();

    return hi-lo;
}

/* 删除单元素 */
template <typename T> 
T Vector<T>::remove( int r )
{
    T e = _elem[r];
    remove(r,r+1);
    return e;
}

/* 无序去重 */
template <typename T> 
int Vector<T>::deduplicate()
{
    int oldsize = _size;
    int i = 1;
    while (i < size)
    {
        if(find( _elem[i],0,i) < 0)
        {
            i++;
        } 
        else
        {
            remove(i);
        }
    }

    return oldsize - _size;
    
}

/* 利用函数指针遍历 */
template <typename T> 
void Vector<T>::traverse ( void (*visit ) ( T& ) )
{
    for(int i=0; i < _size; i++)
    {
        visit( _elem[i] );
    }
}

/* 利用模板函数引用遍历 */
template <typename T> template <typename VST>
void Vector<T>::traverse ( VST& visit)
{
    for(int i=0; i<_size; i++)
    {
        visit(_elem[i]);
    }
}

/* 判断是否有序 */
template <typename T> 
bool Vector<T>::disordered() const
{
    int n = 0;
    for(int i = 1; i < _size; i++)
    {
        if( _elem[i -1] > _elem[i]) n++;
    }

    return n;
}

/* 有序去重 */
template <typename T> 
int Vector<T>::uniquify()
{
    int oldsize = _size;
    int i = 1;
    while (i < _size)
    {
        _elem[i-1] == _elem[i] ? remove(i) : i++;
    }
    
    return oldsize - _size;
}

template <typename T> 
int Vector<T>::search ( T const& e, int lo, int hi ) const
{
    return (rand() % 2) ?
    binSearch ( _elem, e, lo, hi ) : fibSearch ( _elem, e, lo, hi );
}

/* 二分查找 */
template <typename T> 
static int binSearch(T* A,T const& e, int lo, int hi )
{
    while (lo < hi)
    {
        int mi = (lo + hi) >> 1;
        if( e < A[mi] ) hi = mi;
        else if (A[mi] < e) lo = mi + 1;
        else return mi;
    }

    return -1;
    
}