#pragma once

#include <iostream>

template <typename T>
class ArrayList
{
private:
    T *Buffer;
    int BufferSize;

    ArrayList(int Length, T *Buffer);
    void ChangeBufferSize();

public:
    int Length = 0;
    const int ElementSize = sizeof(T);
    
    template <typename U>
    friend std::ostream &operator<<(std::ostream &os, const ArrayList<U> &ref);
    template <typename U>
    friend std::istream &operator>>(std::istream &is, ArrayList<U> &ref);

    ArrayList();
    ~ArrayList();

    T &operator[](int index);
    ArrayList<T> operator+(const ArrayList<T> &ref);
    ArrayList<T> &operator=(const ArrayList<T> &ref);
    ArrayList<T> &operator+=(const ArrayList<T> &ref);
    
    void add(T Element);
    void remove(int index);
    T pop(int index);
    void clear();
};