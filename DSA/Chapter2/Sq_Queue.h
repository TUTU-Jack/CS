#pragma once
#include <iostream>

namespace Sq_Queue {

template <typename Elem>
class Queue;

template <typename Elem>
std::ostream & operator << (std::ostream &os,const Queue<Elem> &queue);

//循环队列
template <typename Elem>
class Queue {
public:
    Queue(int capacity):capacity(capacity),pdata(new Elem[capacity+1]),front(-1),rear(0) { };
    ~Queue() { delete[] pdata;};
public:
    //入队
    Queue &enQueue(const Elem &data);
    //出队
    Queue &deQueue();
    //队列是否空
    bool isEmpty() const;
    //队列是否满
    bool isFull() const;
    //返回队首元素
    Elem &getTop() const { if(isEmpty()) throw("Queue is empty!"); return pdata[front]; };
    //队列长度
    int getLength() const { if(isEmpty()) return 0; return rear - front;};

    friend std::ostream & operator << <Elem>(std::ostream &os,const Queue<Elem> &queue);
private:
    Elem *pdata;        //队列元素
    int capacity;       //队列容量
    int front;          //队首
    int rear;           //队尾
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
    //队列空（队首即队尾）
    if((front % (capacity + 1)) == rear)
        return true;
    
    return false;
}

template <typename Elem>
inline bool Queue<Elem>::isFull() const
{
    //队列满（循环队列，队尾的下一个元素为队首）
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

    //队尾后移
    rear = (rear + 1) % (capacity + 1);

    return *this;
}

template <typename Elem>
inline Queue<Elem>& Queue<Elem>::deQueue()
{
    if(isEmpty())
        return *this;
    
    //队首后移
    front = (front + 1) % (capacity + 1);

    return *this;
}

}

