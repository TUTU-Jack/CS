#include "priority_queue.h"


int main(int argc,char *argv[])
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
    return 0;
}