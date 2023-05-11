/**
 * @File Name: Vector.hpp
 * @brief  Vector 模板类头文件
 * @Author : Timer email:330070781@qq.com
 * @Version : 1.0
 * @Creat Date : 2023-05-10
 * 
 */
#pragma once 


 #define DEFAULT_CAPACITY 3 //默认的初始容量（实际应用中可设置为更大）


template <typename T> class Vector 
{ 

protected:
    int _size;  //大小
    int _capacity; //容量
    T* _elem;  //数据区指针
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
    Vector ( int c = DEFAULT_CAPACITY, int s = 0, T v = 0 ) //容量为c、规模为s、所有元素初始为v ，默认构造函数
    { 
        _elem = new T[_capacity = c]; for ( _size = 0; _size < s; _elem[_size++] = v ); //s<=c
    } 
    Vector ( T const* A, int n ) { copyFrom ( A, 0, n ); } //数组整体复制
    Vector ( T const* A, int lo, int hi ) { copyFrom ( A, lo, hi ); } //区间复制
    Vector ( Vector<T> const& V ) { copyFrom ( V._elem, 0, V._size ); } //向量整体复制
    Vector ( Vector<T> const& V, int lo, int hi ) { copyFrom ( V._elem, lo, hi ); } //区间

 // 析构函数
    ~Vector() { delete [] _elem; } //释放内部空间
// 只读访问接口
    int size() const { return _size; } //返回 vector 数组大小
    bool empty() const { return !_size; } //判断是否为空
    int disordered() const; //刞断向量是否已排序
    int find ( T const& e ) const { return find ( e, 0, _size ); } //无序向量整体查找
    int find ( T const& e, int lo, int hi ) const; //无序向量区间查找
    int search ( T const& e ) const //有序向量整体查找
    { return ( 0 >= _size ) ? -1 : search ( e, 0, _size ); }
    int search ( T const& e, int lo, int hi ) const; //有序向量区间查找

//可写访问接口
    T& operator[] ( int r ) const; //重载下标操作符，可以类似于数组形式引用各元素
    Vector<T> & operator= ( Vector<T> const& ); //重载赋值操作符，以便直接克隆向量
    T remove ( int r ); //初除下标为r癿元素
    int remove ( int lo, int hi ); //删除区间[lo, hi)内的元素
    int insert ( int r, T const& e ); //插入元素
    int insert ( T const& e ) { return insert ( _size, e ); } //默认在数组末尾插入
    void sort ( int lo, int hi ); //对[lo, hi)排序
    void sort() { sort ( 0, _size ); } //整体排序
    void unsort ( int lo, int hi ); //对[lo, hi)置乱
    void unsort() { unsort ( 0, _size ); } //整体置乱
    int deduplicate(); //无序去重
    int uniquify(); //有序去重

//遍历
    void traverse ( void (* ) ( T& ) ); //遍历（使用函数指针，只读或局部性修改）
    template <typename VST> void traverse ( VST& ); //遍历（使用函数对象，可全局性修改）

}; //vector
