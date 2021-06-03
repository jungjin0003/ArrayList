#include "ArrayList.hpp"

template <typename T>
ArrayList<T>::ArrayList()
{
    Buffer = (T *)calloc(Length + 1, ElementSize);
    ChangeBufferSize();
}

template <typename T>
ArrayList<T>::ArrayList(int Length, T *Buffer)
{
    this->Length = Length;
    this->Buffer = Buffer;
    ChangeBufferSize();
}

template <typename T>
ArrayList<T>::~ArrayList()
{
    std::cout << "소멸자 호출" << std::endl;
    free(Buffer);
}

template <typename T>
void ArrayList<T>::ChangeBufferSize()
{
    BufferSize = _msize(Buffer) - ElementSize;
}

template <typename T>
ArrayList<T> ArrayList<T>::operator+(const ArrayList<T> &ref)
{
    int Length = this->Length + ref.Length;
    T *NewBuffer = (T *)calloc(Length + 1, ElementSize);

    memcpy(NewBuffer, this->Buffer, this->Length * ElementSize);
    memcpy(NewBuffer + this->Buffer, ref.Buffer, ref.Length * ElementSize);

    return ArrayList<T>(Length, NewBuffer);
}

template <typename T>
ArrayList<T> &ArrayList<T>::operator=(const ArrayList<T> &ref)
{
    if (this == &ref)
    {
        return *this;
    }

    free(Buffer);

    Buffer = (T *)calloc(ref.Length + 1, ElementSize);
    memcpy(Buffer, ref.Buffer, ref.BufferSize);
    Length = ref.Length;
    BufferSize = ref.BufferSize;

    return *this;
}

template <typename T>
ArrayList<T> &ArrayList<T>::operator+=(const ArrayList<T> &ref)
{
    Buffer = (T *)realloc(Buffer, (Length + ref.Length + 1) * ElementSize);
    memcpy(Buffer + Length, ref.Buffer, ref.BufferSize);
    Length += ref.Length;
    ChangeBufferSize();
    return *this;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, ArrayList<T> &ref)
{
    os << "[";

    for (int i = 0; i < ref.Length - 1; i++)
    {
        os << ref.Buffer[i] << ", ";
    }

    os << ref.Buffer[ref.Length - 1] << "]" << std::endl;
    return os;
}

template <typename T>
std::istream &operator>>(std::istream &is, ArrayList<T> &ref)
{
    T temp;
    is >> temp;
    ref.add(temp);
    return is;
}

template <typename T>
void ArrayList<T>::add(T Element)
{
    Buffer[Length++] = Element;
    Buffer = (T *)realloc(Buffer, (Length + 1) * ElementSize);
    ChangeBufferSize();
}

template <typename T>
void ArrayList<T>::remove(int index)
{
    if (index < 0 || index >= Length)
    {
        throw index;
    }

    T *temp = (T *)calloc(Length--, ElementSize);
    int i;

    if (index == Length)
    {
        for (i = 0; i < Length; i++)
        {
            temp[i] = Buffer[i];
        }
    }
    else
    {
        for (i = 0; i < index; i++)
        {
            temp[i] = Buffer[i];
        }

        for (; i < Length; i++)
        {
            temp[i] = Buffer[i + 1];
        }
    }
    free(Buffer);
    Buffer = temp;
    ChangeBufferSize();
}
int main()
{
    ArrayList<std::tuple<int, int, int>> aa;
}