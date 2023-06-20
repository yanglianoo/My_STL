#pragma once 
#include <iostream>

namespace my_stl
{


template <typename T> struct list_node
{
    T _data;
    list_node<T>* _prev;
    list_node<T>* _next;
    list_node(const T& value)
            :_next(nullptr)
            ,_prev(nullptr)
            ,_data(value)
    {}
};


template<class T, class Ref, class ptr>
struct list_iterator
{
	typedef list_iterator<T, Ref, ptr> self;
	typedef list_node<T> Node;
	Node* _node;
		 
	list_iterator(Node* node)
		:_node(node)
		{}
 
		//拷贝构造、赋值重载，默认浅拷贝即可
		//析构函数，指针指向的节点不属于迭代器的，无需自己销毁
 
	//解引用,*it = it.operator*()
	Ref& operator* ()
	{
		return _node->_data;
	}
	ptr operator-> () //本来调用为it->->_vale,编译器通过处理省略了一个->
	{
		return &(_node->_data);
	}
	//前置++
	self& operator++()
	{
		_node = _node->_next;
		return *this;
	}
	//后置++
	self operator++(int)
	{
		self tmp = *this;
		_node = _node->_next;
		return tmp;
	}
	//前置--
	self& operator--()
	{
		_node = _node->_prev;
		return *this;
	}
	//后置--
	self operator--(int)
	{
		self tmp = *this;
		_node = _node->_prev;
		return *this;
	}
 
	//比较
	bool operator != (const self& it) const
	{
		return _node != it._node;
	}
	bool operator == (const self& it) const
	{
		return _node == it._node;
	}
};

template <typename T> class list{
    typedef list_node<T> Node;
private:
    Node* _head;
    size_t _size;
    void empty_initialize()
    {
        _head = new Node(T());
        _head->_next = _head;
        _head->_prev = _head;

        _size = 0;
    }
/* 迭代器 */
public:
	typedef list_iterator<T, T&, T*> iterator;
	typedef list_iterator<T, const T&, const T*> const_iterator; 
public:
    list(){ empty_initialize(); }

    list(size_t count, const T& value)
    {
        for (size_t i = 0; i < count; ++i) {
            push_back(value);
            _size++;
        }
    }

    list(size_t count)
    {
        for (size_t i = 0; i < count; ++i) {
            push_back(T());
            _size++;
        }
    }
    template <typename InputIt>
    list(InputIt first, InputIt last) : list() 
    {
		while (first != last)
		{
			push_back(*first);
			++first;
            _size++;
		}
    }

    list(const list& other): list() 
    {
		list<T> tmp(other.begin(), other.end());
		swap(_head, tmp._head);
    }

    list(std::initializer_list<T> init) : list()
    {
        for (const T& value : init) {
            push_back(value);
            _size++;
        }
    }
    list<T>& operator=(const list<T> & other)
    {
        if (this == &other) 
        {
            return *this;
        }
        clear();
        for(const T& value : other)
        {
            push_back(value);
            _size++;
        }
        return *this;
    }
    list<T>& operator=( std::initializer_list<T> ilist )
    {
        clear();
        for (const T& value : ilist) 
        {
            push_back(value);
            _size++;
        }
        return *this;

    }

    ~list()
    {
        clear();
        delete[] _head;
        _head = nullptr;
    }
public:

    const_iterator begin() const
    {
        return const_iterator(_head->_next);
    }
    iterator begin()
    {
        return iterator(_head->_next);
    }

    iterator end()
    {
        return iterator(_head);
    }

    const_iterator end() const
    {
        return const_iterator(_head);
    }

    iterator insert(iterator pos, const T& value )
    {
        Node* cur = pos._node;
        Node* prev = cur->_prev;

        Node* new_node = new Node(value);
        new_node->_prev = prev;
        new_node->_next = cur;

        
        prev->_next = new_node;
        cur->_prev = new_node;

        _size++;
        //隐式转换为iterator
        return new_node;
    }

    iterator erase(iterator pos)
    {
        assert(pos != end());

        Node* cur = pos._node;
        Node* prev = cur->_prev;
        Node* next = cur->next;

        prev->_next = next;
        next->_prev = prev;

        _size--;
        delete [] cur;

        return next;

    }

    // 移除范围为 [first, last) 的元素
    iterator erase( iterator first, iterator last )
    {
        if(first == last) { return last;}

        Node* first_node = first._node;
        Node* last_node = last._node;

        Node* prev = first_node->_prev;
        Node* next = last_node;

        prev->_next = next;
        next->_prev = prev;

        size_t count = 0;
        while (first_node != last_node)
        {
            Node* cur = first_node;
            first_node = first_node->_next;
            delete [] cur;
            count++; 
        }
        _size-=count;
        return next;
    }
public:
    size_t size()
    {
        return _size;
    }

    bool empty()
    {
        return begin() == end();
    }

public:
    void clear()
    {
        erase(begin(),end());
    }

    void push_back(const T& value)
    {
        insert(end(),value);
    }

    void push_front(const T& value)
    {
        insert(begin(),value);
    }

    void pop_back()
    {
        erase(--end());
    }

    void pop_front()
    {
        erase(begin());
    }
public:

    T& front()
    {
        return *begin();
    }

    T& back()
    {
        return *(--end());
    }
};


}

