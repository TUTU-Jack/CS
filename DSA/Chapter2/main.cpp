#include <iostream>
#include <cstring>

#include "Sq_Stack.h"
#include "Link_Stack.h"
#include "Sq_Queue.h"
#include "Link_Queue.h"

void test1()
{
    Sq_Stack::Stack<int> stack(10);

    for(int i = 0;i < 5;i++)
        std::cout << stack.push(i) << std::endl;

    std::cout << stack.Length() << std::endl;

    std::cout << stack.getTop() << std::endl;

    for(int i = 0;i < 5;i++)
        std::cout << stack.pop() << std::endl;

    
    std::cout << stack.Length() << std::endl;
}

void test2()
{
    Link_Stack::Stack<int> stack;

    for(int i = 0;i < 5;i++)
        std::cout << stack.push(i) << std::endl;

    std::cout << stack.Length() << std::endl;

    std::cout << stack.getTop() << std::endl;

    for(int i = 0;i < 5;i++)
        std::cout << stack.pop() << std::endl;

    std::cout << stack.Length() << std::endl;
}

void test3()
{
    Sq_Queue::Queue<int> queue(5);


    for(int i = 0;i < 6;i++)
        std::cout << queue.enQueue(i) << std::endl;

    std::cout << queue.getTop() << std::endl;
    std::cout << queue.getLength() << std::endl;
    
    for(int i = 0;i < 6;i++)
        std::cout << queue.deQueue() << std::endl;

    std::cout << queue.getLength() << std::endl;
}

void test4()
{
    Link_Queue::Queue<int> queue;

    for(int i = 0;i < 6;i++)
        std::cout << queue.enQueue(i) << std::endl;

    std::cout << queue.getTop() << std::endl;
    std::cout << queue.getLength() << std::endl;
    
    for(int i = 0;i < 6;i++)
        std::cout << queue.deQueue() << std::endl;

    std::cout << queue.getLength() << std::endl;

}

int main(int argc,char *argv[])
{
    if(argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " <test>" << std::endl;
        return 1;
    }

    if(strcmp(argv[1],"test1") == 0)
        test1();
    else if(strcmp(argv[1],"test2") == 0)
        test2();
    else if(strcmp(argv[1],"test3") == 0)
        test3();
    else if(strcmp(argv[1],"test4") == 0)
        test4();

    return 0;
}