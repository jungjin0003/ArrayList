#include "ArrayList.hpp"

template <typename T>
class ArrayList
{
private:
    T *Buffer;
    int BufferSize;

    ArrayList(int Length, T *Buffer)
    {
        this->Length = Length;
        this->Buffer = Buffer;
        ChangeBufferSize();
    }

    void ChangeBufferSize()
    {
        BufferSize = _msize(Buffer) - ElementSize;
        // std::cout << "BufferSize : " << BufferSize << std::endl;
    }

public:
    int Length = 0;
    const int ElementSize = sizeof(T);
    
    template <typename U>
    friend std::ostream &operator<<(std::ostream &os, const ArrayList<U> &ref);
    template <typename U>
    friend std::istream &operator>>(std::istream &is, ArrayList<U> &ref);

    ArrayList()
    {
        Buffer = (T *)calloc(Length + 1, ElementSize);
        ChangeBufferSize();
    }

    ~ArrayList()
    {
        std::cout << "소멸자 호출" << std::endl;
        free(Buffer);
    }

    T &operator[](int index)
    {
        if (index < 0 || index >= Length)
        {
            throw index;
        }
        else
        {
            return Buffer[index];
        }
    }

    ArrayList<T> operator+(const ArrayList<T> &ref)
    {
        int Length = this->Length + ref.Length;
        T *NewBuffer = (T *)calloc(Length + 1, ElementSize);

        memcpy(NewBuffer, this->Buffer, this->Length * ElementSize);
        memcpy(NewBuffer + this->Length, ref.Buffer, ref.Length * ElementSize);
        return ArrayList<T>(Length, NewBuffer);
    }

    ArrayList<T> &operator=(const ArrayList<T> &ref)
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

    ArrayList<T> &operator+=(const ArrayList<T> &ref)
    {
        Buffer = (T *)realloc(Buffer, (Length + ref.Length + 1) * ElementSize);
        memcpy(Buffer + Length, ref.Buffer, ref.BufferSize);
        Length += ref.Length;
        ChangeBufferSize();
        return *this;
    }

    void add(T Element)
    {
        Buffer[Length++] = Element;
        Buffer = (T *)realloc(Buffer, (Length + 1) * ElementSize);
        ChangeBufferSize();
    }

    void remove(int index)
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
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const ArrayList<T> &ref)
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

void DestructorTest()
{
    ArrayList<int> arraylist1;
    ArrayList<int> arraylist2;
    arraylist1.add(10);
    arraylist1.add(20);
    arraylist1.add(30);
    arraylist2.add(40);
    arraylist2.add(50);
    arraylist2.add(60);

    std::cout << "Test" << std::endl;

    arraylist1 += arraylist2;
    
    std::cout << arraylist1;
}

int main()
{
    DestructorTest();
}