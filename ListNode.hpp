#pragma once

typedef int Rank; //秩
#define ListNodePosi(T) ListNode<T>* // 列表节点，通俗地说就是存 节点 的指针，ListNode是后面定义的一个结构体
#define NULL 0

template <typename T>
struct ListNode
{
    // 成员
    T data; // 数据，类型为 T
    ListNodePosi(T) pred; // 前驱元素 类型为ListNode<T>*
    ListNodePosi(T) succ; // 后继元素 类型为ListNode<T>*  后面就不再说明了

    // 构造函数
    ListNode() {} // 针对header和trailer的构造 
    ListNode( T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL )
        :data(e), pred(p), succ(s) {} //默认构造
    
    // 操作接口
    ListNodePosi(T) insertAsPred( T const& e ); // 在当前元素之前插入元素 返回插入元素的地址
    ListNodePosi(T) insertAsSucc( T const& e ); // 在当前元素之后插入元素 返回插入元素的地址
};
