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
    Node<Elem> *front;
    Node<Elem> *rear;
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

    if(isEmpty())
    {
        front = node;
        rear = node;

        return *this;
    }

    rear->next = node;
    rear = node;

    return *this;

}

template <typename Elem>
inline Queue<Elem>& Queue<Elem>::deQueue()
{
    if(isEmpty())
        return *this;
    
    Node<Elem> *temp = front;
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