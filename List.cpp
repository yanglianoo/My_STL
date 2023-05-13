#include "List.h"

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
    copyNode( L.first(), L._size);
}

template<typename T>
List<T>::List( List<T>& L, Rank r, int n ) // 复制列表L 从第 r 项 复制 n 个
{
    init();
    copyNode( L[r], n ); // 因为用到了重载操作符[]，所以效率较低，复杂度是o(r + n + 1)
}

template<typename T>
List<T>::List( ListNodePosi(T) p, int n ) // 复制从节点 p 开始的 n 个
{
    init();
    copyNode( p, n );
}

template<typename T>
T& List<T>::operator[]( Rank r ) const
{
    ListNodePosi(T) p = first();
    while ( r -- ) p = p->succ;
    return p->data;
}

template<typename T>
ListNodePosi(T) List<T>::find( T const& e, int n, ListNodePosi(T) p ) const
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
void List<T>::copyNode( ListNodePosi(T) p, int n ) // 复制自定义位置起的n个节点
{
    init();
    while ( n -- )
    {
        insertAsLast(p->data);
        p = p->succ;
    }
}