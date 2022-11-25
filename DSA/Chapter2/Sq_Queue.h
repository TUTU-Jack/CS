#pragma once
#include <iostream>

namespace Sq_Queue {

template <typename Elem>
class Queue;

template <typename Elem>
std::ostream & operator << (std::ostream &os,const Queue<Elem> &queue);

/*
 *  循环队列（顺序表实现队列数据结构） 先入先出
 *  插入时间复杂度 O(1)      
 *  删除时间复杂度 O(1) 
 *  查找时间复杂度 O(1)  返回队首元素和队尾元素
 *  空间占用不大
 *  需要事先规定元素个数
 */
template <typename Elem>
class Queue {
public:
    //创建循环队列，最后一个元素空着用于队列满判断
    Queue(int capacity):capacity(capacity),pdata(new Elem[capacity+1]),front(0),rear(0) { };
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
    int front;          //队首（指向队首元素）
    int rear;           //队尾（指向队列最后一个元素的后面）
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
    if(front  == rear)
        return true;
    
    return false;
}

template <typename Elem>
inline bool Queue<Elem>::isFull() const
{
    //队列满（循环队列，队尾的下一个元素为队首）
    if((rear + 1)%(capacity+1) == front)
        return true;
    
    return false;
}



template <typename Elem>
inline Queue<Elem>& Queue<Elem>::enQueue(const Elem &data)
{
    if(isFull())
        return *this;

    pdata[rear] = data;

    //入队列，队尾后移（循环队列，模运算控制在容量范围内 0 - capacity）
    rear = (rear + 1) % (capacity + 1);

    return *this;
}

template <typename Elem>
inline Queue<Elem>& Queue<Elem>::deQueue()
{
    if(isEmpty())
        return *this;
    
    //出队列，队首后移
    front = (front + 1) % (capacity + 1);

    return *this;
}

}

