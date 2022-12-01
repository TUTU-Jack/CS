#include "priority_queue.h"
#include "disJoinSet.h"
#include <cstring>

void test1()
{
    PriorityQueue<int> pq(10);
    pq.insertHeap(10);
    pq.insertHeap(5);
    pq.insertHeap(15);
    pq.insertHeap(3);
    pq.insertHeap(12);
    pq.insertHeap(16);
    pq.insertHeap(7);

    pq.removeHeap();
    std::cout << pq << std::endl;
}

void test2()
{
    DisJoinSet<int> djset;
    for(int i = 10;i < 15;i++)
        djset.insertSet(i);
    djset.insertSet(11);
    djset.insertSet(999);
    std::cout << djset;

    djset.unionSet(11,12);
    djset.unionSet(12,13);
    
    djset.unionSet(13,14);
    djset.unionSet(10,999);
    djset.unionSet(999,11);
    std::cout << djset.findElem(999) << std::endl;
    std::cout << djset.findElem(999) << std::endl;
    std::cout << djset;
    
}

int main(int argc,char *argv[])
{
    if(argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " <test> " << std::endl;
        return 1;
    }

    if(strcmp(argv[1],"test1") == 0)
        test1();
    if(strcmp(argv[1],"test2") == 0)
        test2();
        
    return 0;
}