#pragma once 
#include <iostream>

namespace Link_Queue {

template <typename Elem>
struct Node {
    
    Elem data;
    Node *next;
    Node(const Elem &data):data(data),next(nullptr) { };
};

template <typename Elem>
class Queue;

template <typename Elem>
std::ostream & operator << (std::ostream &os,const Queue<Elem> &queue);


/*
 *  链表实现队列数据结构 先入先出
 *  插入时间复杂度 O(1)      
 *  删除时间复杂度 O(1) 
 *  查找时间复杂度 O(1)  返回队首元素和队尾元素
 *  空间占用节点占用一个指针空间
 *  不用事先规定元素个数
 */
template <typename Elem>
class Queue {
public:
    Queue():front(nullptr),rear(nullptr) { };
    ~Queue() { delete[] front;};
public:
    Queue &enQueue(const Elem &data);
    Queue &deQueue();
    bool isEmpty() const;
    Elem &getTop() const { if(isEmpty()) throw("Queue is empty!"); else return front->data; };
    int getLength() const;

    friend std::ostream & operator << <Elem>(std::ostream &os,const Queue<Elem> &queue);
private:
    Node<Elem> *front;              //队首指针
    Node<Elem> *rear;               //队尾指针
};

template <typename Elem>
std::ostream & operator << (std::ostream &os,const Queue<Elem> &queue)
{
    for(auto it = queue.front;it != queue.rear && it != nullptr;it = it->next)
        os << it->data << " ";
    
    return os;
}

template <typename Elem>
inline bool Queue<Elem>::isEmpty() const 
{
    if(front == nullptr)
        return true;
    
    return false;
}


template <typename Elem>
inline Queue<Elem>& Queue<Elem>::enQueue(const Elem &data)
{
    Node<Elem> *node = new Node<Elem>(data);
    //队列为空
    if(isEmpty())
    {
        //队首指针指向新节点（第一个节点）
        front = node;
        //队尾指针指向新节点（以便链接一下节点）
        rear = node;

        return *this;
    }
    //入队列，队尾节点指针指向新节点
    rear->next = node;
    //队尾指针指向新节点
    rear = node;

    return *this;

}

template <typename Elem>
inline Queue<Elem>& Queue<Elem>::deQueue()
{
    if(isEmpty())
        return *this;
    
    Node<Elem> *temp = front;
    //出队列，队首指针指向队首节点下一节点
    front = front->next;

    delete[] temp;

    return *this;
}

template <typename Elem>
inline int Queue<Elem>::getLength() const
{
    int count = 0;
    for(auto it = front;it != rear && it != nullptr;it = it->next)
        count++;
    
    return count;
}

}