#include "List.hpp"
#include <iostream>

// 实现 ListNode.h 的两个函数
template<typename T>
ListNodePosi(T) ListNode<T>::insertAsPred( T const& e )
{
    ListNodePosi(T) x = new ListNode<T>(e, pred,this); 
    pred->succ = x;
    pred = x;
    return x;
}

template<typename T>
ListNodePosi(T) ListNode<T>::insertAsSucc( T const& e)
{
    ListNodePosi(T) x = new ListNode<T>(e, this, succ);
    succ->pred = x;
    succ = x;
    return x;
}

// 实现List.h
template<typename T>
void List<T>::init()
{
    // 列表List中的header头节点、trailer尾节点对外是不可见的
    header = new ListNode<T>;
    trailer = new ListNode<T>;
    header->succ = trailer, header->pred = NULL;
    trailer->pred = header, trailer->succ = NULL;
    _size = 0; // 尺寸规模为 0
} 

template<typename T>
List<T>::List( List<T>& L ) // 复制L, 拷贝构造 
{
    init();
    copyNodes( L.first(), L._size);
}

template<typename T>
List<T>::List( List<T>& L, Rank r, int n ) // 复制列表L 从第 r 项 复制 n 个
{
    init();
    copyNodes( L[r], n ); // 因为用到了重载操作符[]，所以效率较低，复杂度是o(r + n + 1)
}

template<typename T>
List<T>::List( ListNodePosi(T) p, int n ) // 复制从节点 p 开始的 n 个
{
    init();
    copyNodes( p, n );
}

template<typename T>
T& List<T>::operator[]( Rank r ) const
{
    ListNodePosi(T) p = first();
    while ( r -- ) p = p->succ;
    return p->data;
}

template<typename T>
ListNodePosi(T) List<T>::find( T const& e, int n, ListNodePosi(T) p ) const // 查找 p 的前 n 个，不包含 p
{
    while ( n -- )
    {   
        p = p->pred;
        if (p->data == e) return p;
    }
    return NULL;
}

template<typename T>
ListNodePosi(T) List<T>::insertAsFirst( T const& e )
{
    _size ++;
    return header->insertAsSucc(e);
}

template<typename T>
ListNodePosi(T) List<T>::insertAsLast( T const& e)
{
    _size ++;
    return trailer->insertAsPred(e);
}

template<typename T>
ListNodePosi(T) List<T>::insertAfter( ListNodePosi(T) p, T const& e)
{
    _size ++;
    return p->insertAsSucc(e);
}

template<typename T>
ListNodePosi(T) List<T>::insertBefore( ListNodePosi(T) p, T const& e){
    _size ++;
    return p->insertAsPred(e);
}


template<typename T>
void List<T>::copyNodes( ListNodePosi(T) p, int n ) // 复制自定义位置起的n个节点
{
    init();
    while ( n -- )
    {
        insertAsLast(p->data);
        p = p->succ;
    }
}

template<typename T>
T List<T>::remove( ListNodePosi(T) p ) // 删除合法位置 p节点，并返回被删除的节点元素
{
    T e = p->data;
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    delete p;
    _size --;
    return e;
}

template<typename T>
int List<T>::clear()
{
    int oldSize = _size;
    while ( _size ) remove( header->succ );
    return oldSize;
}


template<typename T>
List<T>::~List()
{
    clear();
    delete header;
    delete trailer;
}

template<typename T>
int List<T>::deduplicate()
{
    if ( _size < 2 ) return 0; // 当_size为 0 或 1 时，肯定没有重复
    int oldSize = _size;
    Rank r = 0;
    ListNodePosi(T) p = header->succ;
    while ( p != trailer)
    {
        ListNodePosi(T) q = find( p->data, r, p ); // find函数为无序列表的查找
        q ? remove(q) : r ++ ;
        p = p->succ;
    }
    return oldSize - _size; // 返回值是删除的元素个数
}

template<typename T>
void List<T>::traverse( void(*visit) (T&) )
{
    for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ) visit(p->data);
}

template<typename T> template<typename VST>
void List<T>::traverse(VST& visit)
{
    for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ) visit(p->data);
}

template<typename T>
int List<T>::uniquify()
{
    if (_size < 2) return 0;
    int oldSize = _size;
    ListNodePosi(T) p = header->succ, q = p->succ;
    while (q->succ != trailer)
    {
        if (p->data != q->data) p = q;
        else remove(q);
        q = p->succ;
    }
    return oldSize - _size;
}

template<typename T>
ListNodePosi(T) List<T>::search( T const& e, int n, ListNodePosi(T) p ) const // 有序区间查找 查找成功时返回目标，失败时返回左边界前驱
{
    while ( n -- )
    {
        p = p->pred;
        if (p->data <= e) break;
    }
    return p;
}

template<typename T>
void List<T>::sort( ListNodePosi(T) p, int n ) // 列表区间排序
{
    switch ( rand() % 3)
    {
    case 1:
        insertSort(p, n);
        break;
    case 2:
        selectionSort(p, n);
        break;
    default:
        mergeSort(p, n);
        break;
    }
}

template<typename T>
void List<T>::insertSort( ListNodePosi(T)& p, int n )
{
    for (int r = 0; r < n; r ++)
    {
        insertAfter( search(p->data, r, p), p->data );
        p = p->succ;
        remove(p->pred);
    }
}

template<typename T>
void List<T>::selectionSort( ListNodePosi(T)& p, int n )
{
    ListNodePosi(T) head = p->pred, tail = p;
    for (int i = 0; i < n; i ++) tail = tail->succ;
    while (n > 1)
    {
        ListNodePosi(T) max = selectMax(head->succ, n);
        insertBefore(tail, remove(max));
        tail = tail->pred;
        n --;
    }
}

template<typename T>
ListNodePosi(T) List<T>::selectMax( ListNodePosi(T) p, int n ) const
{
    ListNodePosi(T) max = p;
    while ( -- n )
    {
        p = p->succ;
        if ( p->data >= max->data) max = p;
    }
    return max;
}

template<typename T>
void List<T>::merge( ListNodePosi(T)& p, int n, List<T>& L, ListNodePosi(T) q, int m)
{
    ListNodePosi(T) pp = p->pred; 
    while ( 0 < m )
    {
        if (( 0 < n ) && ( p->data <= q->data ))
        {
            p = p->succ;
            if (p == q) break;
            n --;
        }
        else
        {   
            q = q->succ;
            insertBefore(p, L.remove(q->pred)); 
            m--; 
        }
    }
    p = pp->succ;
}

template <typename T>
void List<T>::mergeSort ( ListNodePosi(T) & p, int n )
{
    if ( n < 2 ) return; 
    int m = n >> 1; 
    ListNodePosi(T) q = p;
    for ( int i = 0; i < m; i++ ) q = q->succ; 
    mergeSort ( p, m ); 
    mergeSort ( q, n - m ); 
    merge ( p, m, *this, q, n - m ); 
} 