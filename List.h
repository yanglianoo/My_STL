#include "ListNode.h"

template <typename T>
class List
{
private:
    int _size; // 尺寸规模
    ListNodePosi(T) header; // 头
    ListNodePosi(T) trailer; // 尾

protected:
    void init(); // 列表初始化
    int clear(); // 清除所有节点
    void copyNode( ListNodePosi(T), int ); // 复制自定义位置起的n个节点
    void merge( ListNodePosi(T)&, int, List<T>&, ListNodePosi(T), int ); //归并
    void mergeSort( ListNodePosi(T)&, int ); // 对从自定义位置起的n个节点进行 归并排序
    void selectionSort( ListNodePosi(T)&, int ); // 对从自定义位置起的n个节点进行 选择排序
    void insertSort( ListNodePosi(T)&, int ); // 对从自定义位置起的n个节点进行 插入排序

public:
    // 构造函数
    List() { init(); } // 默认构造
    List( List<T>& L ); // 复制L, 拷贝构造 
    List( List<T>& L, Rank r, int n ); // 复制列表L 从第 r 项 复制 n 个
    List( ListNodePosi(T) p, int n ); // 复制从节点 p 开始的 n 个

    // 析构函数
    ~List(); 

    // 只读访问接口
    Rank size() const { return _size; } // 返回当前的规模 节点总数
    bool empty() const { return _size <= 0; } // 判断列表是否为空

    T& operator[]( Rank r ) const; // 重载操作符[] 支持按秩访问, 但是时间复杂度也是O(n)级别的

    ListNodePosi(T) first() const { return header->succ; } // 访问首节点
    ListNodePosi(T) last() const { return trailer->pred; } // 访问末节点

    bool valid( ListNodePosi(T) p ) // 判断节点p是否对外合法
    { return p && (header != p) && (trailer != p); }

    int disordered() const; // 判断是否有序
    ListNodePosi(T) find( T const& e) const // 无序列表查找
    { return find( e, _size, trailer ); }
    ListNodePosi(T) find( T const& e, int n, ListNodePosi(T) p ) const; // 无序区间查找
    ListNodePosi(T) search( T const& e ) const // 有序列表查找
    { return search( e, _size, trailer ); }
    ListNodePosi(T) search( T const& e, int n, ListNodePosi(T) p ) const; // 有序区间查找

    ListNodePosi(T) selectMax( ListNodePosi(T) p, int n ) const; // 在节点p后的 n - 1 个内找最大值
    ListNodePosi(T) selectMax() const // 找出列表的最大值
    { return selectMax( header->succ, _size ); } 

    // 可写访问接口
    ListNodePosi(T) insertAsFirst( T const& e ); // 在头节点后插入
    ListNodePosi(T) insertAsLast( T const& e);  // 在尾节点前插入
    ListNodePosi(T) insertAfter( ListNodePosi(T) p, T const& e); // 在节点p的后面插入
    ListNodePosi(T) insertBefore( ListNodePosi(T) p, T const& e); // 在节点p的前面插入

    T remove( ListNodePosi(T) p ); // 删除合法位置 p节点，并返回被删除的节点元素

    // TODO
    void merge( List<T>& L ) // 把列表L 进行归并
    { return merge( first(), _size, L, L.first(), L._size ); }

    void sort() // 列表整体排序
    { return sort( first(), _size); }
    void sort( ListNodePosi(T) p, int n ); // 列表区间排序

    int deduplicate(); // 无序去重
    int uniquify(); // 有序去重
    
    void reverse(); // 前后倒置

    // 遍历
    void traverse( void(*) (T&) ); // 遍历，依次visit（函数指针，只读或局部性修改）
    template <typename VST> // 操作器
    void traverse( VST& ); // 遍历，依次visit（函数对象，可全局修改）

};