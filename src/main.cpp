#include "ArrayList.hpp"

int main()
{
    ArrayList<int>::ArrayList arraylist;

    arraylist.add(10);

    std::cout << arraylist.pop(0) << std::endl;
}