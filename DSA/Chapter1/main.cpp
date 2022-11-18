#include <iostream>
#include <cstring>

#include "Sqlist.h"
#include "Linklist.h"

void test1()
{
    Sqlist<int> sl(10,1);

    std::cout << sl.insert(0,2) << std::endl;
    std::cout << sl.insert(3,2) << std::endl;
    std::cout << sl.insert(4,2) << std::endl;
    std::cout << sl.insert(-1,2) << std::endl;

    std::cout << sl.insert(2,2) << std::endl;
    std::cout << sl.insert(3,4) << std::endl;
    std::cout << sl.insert(3,3) << std::endl;
    std::cout << sl.insert(1,5) << std::endl;
    std::cout << sl.insert(2,6) << std::endl;

    std::cout << sl.remove(0) << std::endl;
    std::cout << sl.remove(8) << std::endl;

    std::cout << sl.remove(1).FindX(5) << std::endl;
    std::cout << sl.remove(1).FindX(6) << std::endl;

    std::cout << sl.Find(4) << std::endl;
}

void test2()
{
    Linklist<int> linklist(1);

    std::cout << linklist.insert(-1,2) << std::endl;
    std::cout << linklist.insert(0,2) << std::endl;
    std::cout << linklist.insert(3,3) << std::endl;

    std::cout << linklist.insert(2,2) << std::endl;
    std::cout << linklist.insert(3,3) << std::endl;
    std::cout << linklist.insert(5,5) << std::endl;
    std::cout << linklist.insert(1,4) << std::endl;
    std::cout << linklist.insert(3,5) << std::endl;

    std::cout << linklist.remove(-1) << std::endl;
    std::cout << linklist.remove(0) << std::endl;
    std::cout << linklist.remove(6) << std::endl;
    std::cout << linklist.remove(7) << std::endl;
    std::cout << linklist.remove(1) << std::endl;
    std::cout << linklist.remove(2) << std::endl;
    std::cout << linklist.remove(3) << std::endl;
    std::cout << linklist.remove(2) << std::endl;

    std::cout << linklist.Length() << std::endl;
}

int main(int argc,char *argv[])
{

    if(argc < 2)
    {
        std::cout << "Usage:" << argv[0] << " <test>" << std::endl;
        return 1;
    }

    if(strcmp(argv[1],"test1") == 0)
        test1();
    else if(strcmp(argv[1],"test2") == 0)
        test2();

    return 0;
}