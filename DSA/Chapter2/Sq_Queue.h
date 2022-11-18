#pragma once
#include <iostream>

namespace Sq_Queue {

template <typename Elem>
class Queue;

template <typename Elem>
std::ostream & operator << (std::ostream &os,const Queue<Elem> &queue);

template <typename Elem>
class Queue {
public:
    Queue(int capacity):capacity(capacity),pdata(new Elem[capacity+1]),front(-1),rear(0) { };
    ~Queue() { delete[] pdata;};
public:
    Queue &enQueue(const Elem &data);
    Queue &deQueue();
    bool isEmpty() const;
    bool isFull() const;
    Elem &getTop() const { if(isEmpty()) throw("Queue is empty!"); return pdata[front]; };
    int getLength() const { if(isEmpty()) return 0; return rear - front;};

    friend std::ostream & operator << <Elem>(std::ostream &os,const Queue<Elem> &queue);
private:
    Elem *pdata;
    int capacity;
    int front;
    int rear;
};

template <typename Elem>
std::ostream & operator << (std::ostream &os,const Queue<Elem> &queue)
{
    for(int i = queue.front;i < queue.rear;i++)
        os << queue.pdata[i] << " ";
    
    return os;
}

template <typename Elem>
inline bool Queue<Elem>::isEmpty() const 
{
    if((front % (capacity + 1)) == rear)
        return true;
    
    return false;
}

template <typename Elem>
inline bool Queue<Elem>::isFull() const
{
    if(((rear + 1) % (capacity + 1)) == front)
        return true;
    
    return false;
}



template <typename Elem>
inline Queue<Elem>& Queue<Elem>::enQueue(const Elem &data)
{
    if(isFull())
        return *this;
    
    if(front == -1)
        front++;

    pdata[rear] = data;

    rear = (rear + 1) % (capacity + 1);

    return *this;
}

template <typename Elem>
inline Queue<Elem>& Queue<Elem>::deQueue()
{
    if(isEmpty())
        return *this;
    
    front = (front + 1) % (capacity + 1);

    return *this;
}

}

