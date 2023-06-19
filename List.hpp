#pragma once 
#include <iostream>

namespace my_stl
{


template <typename T> struct list_node
{
    T data;
    list_node<T>* prev;
    list_node<T>* next;
    list_node(const T& value)
            :next(nullptr)
            ,prev(nullptr)
            ,data(value)
    {}
};


template <typename T> class list{
    typedef list_node<T> Node;
private:
    Node* _head;
    size_t _size;
    void empty_initialize();
/* 迭代器 */
public:
    class Iterator {
    private:
        list_node<T>* current;
    public:
        Iterator(list_node<T>* node): current(node){}
        /* 重载*  */
        T& operator*() const
        {
            return current->data;
        }

        /* 前++ */
        Iterator operator++()
        {
            current = current->next;
            return *this;
        }

        /* 后++ */
        Iterator operator++(int)
        {
            Iterator temp(*this);
            current = current->next;
            return temp;
        }

        /* 前-- */
        Iterator operator--()
        {
            current = current->prev;
            return *this;
        }

        /* 后-- */
        Iterator operator--(int)
        {
            Iterator temp(*this);
            current = current->prev;
            return temp;
        }

        /* == */
        bool operator==(const Iterator& other) const
        {
            return current == other.current;
        }

        /* != */
        bool operator!=(const Iterator& other) const
        {
            return !(current == other.current);
        }


    };


public:
    list();
    list(size_t count, const T& value);
    list(size_t count);
    list(const list& other);
    list(std::initializer_list<T> init);
    ~list();
    list<T>& operator=(list<T> & other);
    list& operator=( std::initializer_list<T> ilist );
public:

    Iterator begin()
    {
        return Iterator(_head->next);
    }

    Iterator end()
    {
        return Iterator(_head);
    }

    
};

template <typename T>
void list<T>::empty_initialize()
{
    _head = new Node(T());
	_head->_next = _head;
	_head->_prev = _head;

	_size = 0;
}
template <typename T>
list<T>::list()
{
    empty_initialize();
}
}

