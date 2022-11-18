#pragma once
#include <iostream>

namespace Link_Stack {

template <typename Elem>
struct Node {
    Elem data;
    Node *next;

    Node(const Elem &data):data(data),next(nullptr) { };
};

template <typename Elem>
class Stack;

template <typename Elem>
std::ostream & operator << (std::ostream &os,const Stack<Elem> &st);

template <typename Elem>
class Stack {
public:
    Stack():top(nullptr) { };
    ~Stack() { delete[] top; };
public:
    Stack &push(const Elem &data);
    Stack &pop();
    bool isEmpty() const { if(top == nullptr) return true; return false; };
    int Length() const;
    Elem &getTop() const { if(isEmpty()) throw("Stack is empty!");return top->data;};

    friend std::ostream & operator << <Elem>(std::ostream &os,const Stack<Elem> &st);
private:
    Node<Elem> *top;

};

template <typename Elem>
std::ostream & operator << (std::ostream &os,const Stack<Elem> &st)
{
    Node<Elem> *temp = st.top;
    while(temp != nullptr)
    {
        os << temp->data << " ";
        temp = temp->next;
    }
    
    return os;
}

template <typename Elem>
Stack<Elem>& Stack<Elem>::push(const Elem &data)
{
    Node<Elem> *node = new Node<Elem>(data);

    node->next = top;
    top = node;

    return *this;
}

template <typename Elem>
Stack<Elem>& Stack<Elem>::pop()
{
    Node<Elem> *temp = top;

    if(isEmpty())
        return *this;

    top = temp->next;
    delete[] temp;

    return *this;
}

template <typename Elem>
int Stack<Elem>::Length() const
{
    int count = 0;
    Node<Elem> *temp = top;
    while(temp != nullptr)
    {
        count++;
        temp = temp->next;
    }

    return count;
}

}
