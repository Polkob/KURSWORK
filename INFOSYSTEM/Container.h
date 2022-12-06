#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "MusicCollection.h"

template <class T>
class  my_vector
{
public:

    typedef T* iterator;

    my_vector();
    my_vector(unsigned int size);
    my_vector(unsigned int size, const T& initial);
    my_vector(const my_vector<T>& v);
    ~my_vector();

    unsigned int capacity() const;
    unsigned int size() const;
    bool empty() const;
    iterator begin();
    iterator end();
    iterator erase();
    T& front();
    T& back();
    void push_back(const T& value);
    void pop_back();

    void reserve(unsigned int capacity);
    void resize(unsigned int size);


    T& operator[](unsigned int index);
    my_vector<T>& operator=(const my_vector<T>&);
    void clear();
    void remove(int index) 
    {
       
        for (size_t i = index+1; i < my_size; ++i)
        {
            arr[i - 1] = arr[i];
        }
        --my_size;
    }
private:
    size_t my_size;
    size_t my_capacity;
    T* arr;
};

template<class T>
my_vector<T>::my_vector()
{
    my_capacity = 0;
    my_size = 0;
    arr = 0;
}

template<class T>
my_vector<T>::my_vector(const my_vector<T>& v)
{
    my_size = v.my_size;

    my_capacity = v.my_capacity;

    arr = new T[my_size];

    for (unsigned int i = 0; i < my_size; i++)
    {
        arr[i] = v.arr[i];
    }
}

template<class T>
my_vector<T>::my_vector(unsigned int size)
{
    my_capacity = size;
    my_size = size;
    arr = new T[size];
}

template<class T>
my_vector<T>::my_vector(unsigned int size, const T& initial)
{
    my_size = size;

    my_capacity = size;

    arr = new T[size];

    for (unsigned int i = 0; i < size; i++)
    {
        arr[i] = initial;
    }
}

template<class T>
my_vector<T>& my_vector<T>::operator = (const my_vector<T>& v)
{
    delete[] arr;

    my_size = v.my_size;

    my_capacity = v.my_capacity;

    arr = new T[my_size];

    for (unsigned int i = 0; i < my_size; i++)
    {
        arr[i] = v.arr[i];
    }

    return *this;
}

template<class T>
typename my_vector<T>::iterator my_vector<T>::begin()
{
    return arr;
}

template<class T>
typename my_vector<T>::iterator my_vector<T>::end()
{
    return arr + size();
}

template<class T>
T& my_vector<T>::front()
{
    return arr[0];
}

template<class T>
T& my_vector<T>::back()
{
    return arr[my_size - 1];
}

template<class T>
void my_vector<T>::push_back(const T& v)
{
    if (my_size >= my_capacity)
        reserve(my_capacity + 5);
    arr[my_size++] = v;
}

template<class T>
void my_vector<T>::pop_back()
{
    my_size--;
}

template<class T>
void my_vector<T>::reserve(unsigned int capacity)
{
    if (arr == 0)
    {
        my_size = 0;
        my_capacity = 0;
    }

    T* Newbuffer = new T[capacity];

    unsigned int l_Size = capacity < my_size ? capacity : my_size;

    for (unsigned int i = 0; i < l_Size; i++)
    {
        Newbuffer[i] = arr[i];
    }

    my_capacity = capacity;
    delete[] arr;
    arr = Newbuffer;
}

template<class T>
unsigned int my_vector<T>::size()const
{
    return my_size;
}

template<class T>
void my_vector<T>::resize(unsigned int size)
{
    reserve(size);

    my_size = size;
}


template<class T>
T& my_vector<T>::operator[](unsigned int index)
{
    return arr[index];
}

template <class T>
void my_vector<T>::clear()
{
    my_capacity = 0;
    my_size = 0;
    arr = 0;
}

template<class T>
unsigned int my_vector<T>::capacity()const
{
    return my_capacity;
}

template<class T>
my_vector<T>::~my_vector()
{
    delete[] arr;
}


