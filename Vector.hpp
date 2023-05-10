/**
 * @File Name: Vector.hpp
 * @brief  Vector 模板类头文件
 * @Author : Timer email:330070781@qq.com
 * @Version : 1.0
 * @Creat Date : 2023-05-10
 * 
 */
#pragma once 


 #define DEFAULT_CAPACITY 3 //默认的初始容量（实际应用中可讴置为更大）


template <typename T> class Vector 
{ 

protected:
    int _size;  //大小
    int _capacity; //容量
    T* _elem;  //数据区
    void copyFrom ( T const* A, int lo, int hi ); //复制数组区间 A[lo, hi]
    void expand(); //空间不足时扩容
    void shrink(); //装填因子过小时压缩
    bool bubble ( int lo, int hi ); //扫描交换
    void bubbleSort ( int lo, int hi ); //起泡排序算法
    int max ( int lo, int hi ); //选取最大元素
    void selectionSort ( int lo, int hi ); //选择排序算法
    void merge ( int lo, int mi, int hi ); //归并算法
    void mergeSort ( int lo, int hi ); //归并排序算法
    int partition ( int lo, int hi ); //轴点构造算法
    void quickSort ( int lo, int hi ); //快速排序算法
    void heapSort ( int lo, int hi ); //堆排序

public:

// 极造函数
    Vector ( int c = DEFAULT_CAPACITY, int s = 0, T v = 0 ) //容量为c、规模为s、所有元素初始为v
    { 
        _elem = new T[_capacity = c]; for ( _size = 0; _size < s; _elem[_size++] = v ); //s<=c
    } 
    Vector ( T const* A, int n ) { copyFrom ( A, 0, n ); } //数组整体复制
    Vector ( T const* A, int lo, int hi ) { copyFrom ( A, lo, hi ); } //区间复制
    Vector ( Vector<T> const& V ) { copyFrom ( V._elem, 0, V._size ); } //向量整体复制
    Vector ( Vector<T> const& V, int lo, int hi ) { copyFrom ( V._elem, lo, hi ); } //区间

 // 析构函数
    ~Vector() { delete [] _elem; } //释放内部空间




};
